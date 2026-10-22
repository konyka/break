# Programs / UbaVisualizer

- module root: `Source/Programs/UnrealBuildAccelerator/Visualizer`
- headers: 7; symbols: 603
- symbol kinds: class=7, enum=2, enumerator=5, function=63, macro=9, member=343, namespace=7, prototype=130, struct=29, typedef=8
- PrivateDependencyModuleNames: UbaCommon

### `Source/Programs/UnrealBuildAccelerator/Visualizer/Private/UbaTraceReader.h` (Private)


#### class `uba::TraceView`  
`class TraceView`  
_L18-228_
- L179 _public prototype_ `const Process& GetProcess(const ProcessLocation& loc);`
- L180 _public prototype_ `const Session& GetSession(const ProcessLocation& loc);`
- L181 _public prototype_ `void Clear();`
- L201 _public member_ `Vector<Session> sessions;`
- L202 _public member_ `Vector<CacheSummary> cacheSummaries;`
- L203 _public member_ `Vector<WorkTrack> workTracks;`
- L204 _public member_ `Vector<tchar*> strings;`
- L205 _public member_ `Vector<ActiveProcessCount> activeProcessCounts;`
- L206 _public member_ `Map<u64, StatusUpdate> statusMap;`
- L207 _public member_ `Map<u32, CacheWrite> cacheWrites;`
- L208 _public member_ `Map<u32, Table> tables;`
- L209 _public member_ `u64 realStartTime = 0;`
- L210 _public member_ `u64 traceSystemStartTimeUs = 0;`
- L211 _public member_ `u64 startTime = 0;`
- L212 _public member_ `u64 frequency = 0;`
- L213 _public member_ `double timeMultiplier = 0;`
- L214 _public member_ `u64 lastKillProcessTime = 0;`
- L215 _public member_ `const tchar* lastKillReason = nullptr;`
- L216 _public member_ `u64 lastSpawningDelayStartTime = 0;`
- L217 _public member_ `u64 lastSpawningDelayEndTime = 0;`
- L218 _public member_ `u32 totalProcessActiveCount = 0;`
- L219 _public member_ `u32 totalProcessExitedCount = 0;`
- L220 _public member_ `u32 activeSessionCount = 0;`
- L221 _public member_ `u32 version = 0;`
- L222 _public member_ `u32 progressProcessesTotal = 0;`
- L223 _public member_ `u32 progressProcessesDone = 0;`
- L224 _public member_ `u32 progressErrorCount = 0;`
- L225 _public member_ `u16 maxActiveProcessCount = 0;`
- L226 _public member_ `bool remoteExecutionDisabled = false;`
- L227 _public member_ `bool finished = true;`

#### enum `uba::TraceView::ProcessType`  
`enum ProcessType : u8`  
_L21-21_
- L21 _public enumerator_ `enum ProcessType : u8 { ProcessType_Normal, ProcessType_CacheFetchTest, ProcessType_CacheFetchDownload, ProcessType_Task }; struct BitmapCache { HBITMAP bitmap = 0; u32 bitmapOffset = 0; bool bitmapDirty = true; };`
- L21 _public enumerator_ `enum ProcessType : u8 { ProcessType_Normal, ProcessType_CacheFetchTest, ProcessType_CacheFetchDownload, ProcessType_Task }; struct BitmapCache { HBITMAP bitmap = 0; u32 bitmapOffset = 0; bool bitmapDirty = true; };`
- L21 _public enumerator_ `enum ProcessType : u8 { ProcessType_Normal, ProcessType_CacheFetchTest, ProcessType_CacheFetchDownload, ProcessType_Task }; struct BitmapCache { HBITMAP bitmap = 0; u32 bitmapOffset = 0; bool bitmapDirty = true; };`
- L21 _public enumerator_ `enum ProcessType : u8 { ProcessType_Normal, ProcessType_CacheFetchTest, ProcessType_CacheFetchDownload, ProcessType_Task }; struct BitmapCache { HBITMAP bitmap = 0; u32 bitmapOffset = 0; bool bitmapDirty = true; };`

#### struct `uba::TraceView::BitmapCache`  
`struct BitmapCache`  
_L23-28_
- L25 _public member_ `HBITMAP bitmap = 0;`
- L26 _public member_ `u32 bitmapOffset = 0;`
- L27 _public member_ `bool bitmapDirty = true;`

#### struct `uba::TraceView::Process`  
`struct Process : BitmapCache`  
_L30-49_
- inherits: `BitmapCache`
- L32 _public member_ `u32 id = 0;`
- L33 _public member_ `u32 exitCode = ~0u;`
- L34 _public member_ `u64 start = 0;`
- L35 _public member_ `u64 stop = 0;`
- L36 _public member_ `TString description;`
- L37 _public member_ `TString returnedReason;`
- L38 _public member_ `TString breadcrumbs;`
- L39 _public member_ `ProcessType type = ProcessType_Normal;`
- L40 _public member_ `bool isRemote = false;`
- L41 _public member_ `bool isReuse = false;`
- L42 _public member_ `bool isRacing = false;`
- L43 _public member_ `bool isIdle = false;`
- L44 _public member_ `u64 createFilesTime = 0;`
- L45 _public member_ `u64 writeFilesTime = 0;`
- L46 _public member_ `Vector<u8> stats;`
- L47 _public member_ `Vector<ProcessLogLine> logLines;`
- L48 _public member_ `const tchar* killReason = nullptr;`

#### struct `uba::TraceView::Processor`  
`struct Processor`  
_L51-54_
- L53 _public member_ `Vector<Process> processes;`

#### struct `uba::TraceView::WorkRecordLogEntry`  
`struct WorkRecordLogEntry`  
_L56-62_
- L58 _public member_ `u64 time = 0;`
- L59 _public member_ `u64 startTime = 0;`
- L60 _public member_ `const tchar* text;`
- L61 _public member_ `u32 count = 1;`

#### struct `uba::TraceView::WorkRecord`  
`struct WorkRecord : BitmapCache`  
_L64-71_
- inherits: `BitmapCache`
- L66 _public member_ `const tchar* description = nullptr;`
- L67 _public member_ `u64 start = 0;`
- L68 _public member_ `u64 stop = 0;`
- L69 _public member_ `Vector<WorkRecordLogEntry> entries;`
- L70 _public member_ `u32 color = ColorWork;`

#### struct `uba::TraceView::WorkTrack`  
`struct WorkTrack`  
_L73-76_
- L75 _public member_ `Vector<WorkRecord> records;`

#### struct `uba::TraceView::FileTransfer`  
`struct FileTransfer`  
_L79-86_
- L81 _public member_ `CasKey key;`
- L82 _public member_ `u64 size;`
- L83 _public member_ `TString hint;`
- L84 _public member_ `u64 start;`
- L85 _public member_ `u64 stop;`

#### struct `uba::TraceView::StatusUpdate`  
`struct StatusUpdate`  
_L88-93_
- L90 _public member_ `TString text;`
- L91 _public member_ `LogEntryType type;`
- L92 _public member_ `TString link;`

#### struct `uba::TraceView::Drive`  
`struct Drive`  
_L95-107_
- L97 _public member_ `u8 busyHighest = 0;`
- L98 _public member_ `u32 totalReadCount = 0;`
- L99 _public member_ `u32 totalWriteCount = 0;`
- L100 _public member_ `u64 totalReadBytes = 0;`
- L101 _public member_ `u64 totalWriteBytes = 0;`
- L102 _public member_ `Vector<u8> busyPercent;`
- L103 _public member_ `Vector<u32> readCount;`
- L104 _public member_ `Vector<u32> writeCount;`
- L105 _public member_ `Vector<u64> readBytes;`
- L106 _public member_ `Vector<u64> writeBytes;`

#### struct `uba::TraceView::SessionInfo`  
`struct SessionInfo`  
_L109-113_
- L111 _public member_ `TString text;`
- L112 _public member_ `TString hyperlink;`

#### struct `uba::TraceView::Session`  
`struct Session`  
_L115-161_
- L117 _public member_ `TString name;`
- L118 _public member_ `TString machineId;`
- L119 _public member_ `List<SessionInfo> infos;`
- L120 _public member_ `Guid clientUid;`
- L121 _public member_ `Vector<Processor> processors;`
- L122 _public member_ `Vector<u64> updates;`
- L123 _public member_ `Vector<u64> networkSend;`
- L124 _public member_ `Vector<u64> networkRecv;`
- L125 _public member_ `Vector<u64> ping;`
- L126 _public member_ `Vector<u64> memAvail;`
- L127 _public member_ `Vector<float> cpuLoad;`
- L128 _public member_ `Vector<u16> connectionCount;`
- L129 _public member_ `Vector<u32> reconnectIndices;`
- L131 _public member_ `Vector<TString> summary;`
- L132 _public member_ `UnorderedMap<CasKey, u32> fetchedFilesActive;`
- L133 _public member_ `Vector<FileTransfer> fetchedFiles;`
- L134 _public member_ `UnorderedMap<CasKey, u32> storedFilesActive;`
- L135 _public member_ `Vector<FileTransfer> storedFiles;`
- L136 _public member_ `Map<char, Drive> drives;`
- L137 _public member_ `TString notification;`
- L138 _public member_ `u64 fetchedFilesBytes = 0;`
- L139 _public member_ `u64 storedFilesBytes = 0;`
- L140 _public member_ `u32 fetchedFilesCount = 0;`
- L141 _public member_ `u32 storedFilesCount = 0;`
- L142 _public member_ `u32 maxVisibleFiles = 0;`
- L143 _public member_ `u32 fullNameWidth = 0;`
- L145 _public member_ `float highestSendPerS = 0;`
- L146 _public member_ `float highestRecvPerS = 0;`
- L148 _public member_ `bool isReset = true;`
- L149 _public member_ `u64 disconnectTime = ~u64(0);`
- L150 _public member_ `u64 prevUpdateTime = 0;`
- L151 _public member_ `u64 prevSend = 0;`
- L152 _public member_ `u64 prevRecv = 0;`
- L153 _public member_ `u64 memTotal = 0;`
- L154 _public member_ `u32 processActiveCount = 0;`
- L155 _public member_ `u32 processExitedCount = 0;`
- L157 _public member_ `TString proxyName;`
- L158 _public member_ `bool proxyCreated = false;`
- L160 _public prototype_ `void GetFullName(StringBufferBase& out);`

#### struct `uba::TraceView::ProcessLocation`  
`struct ProcessLocation`  
_L163-169_
- L165 _public member_ `u32 sessionIndex = 0;`
- L166 _public member_ `u32 processorIndex = 0;`
- L167 _public member_ `u32 processIndex = 0;`
- L168 _public function_ `bool operator==(const ProcessLocation& o) const`

#### struct `uba::TraceView::CacheWrite`  
`struct CacheWrite`  
_L171-177_
- L173 _public member_ `u64 start = 0;`
- L174 _public member_ `u64 end = 0;`
- L175 _public member_ `Vector<u8> stats;`
- L176 _public member_ `bool success = false;`

#### struct `uba::TraceView::ActiveProcessCount`  
`struct ActiveProcessCount`  
_L183-187_
- L185 _public member_ `u64 time;`
- L186 _public member_ `u16 count;`

#### struct `uba::TraceView::CacheSummary`  
`struct CacheSummary`  
_L189-192_
- L191 _public member_ `Vector<TString> lines;`

#### struct `uba::TraceView::Table`  
`struct Table`  
_L194-199_
- L196 _public member_ `Vector<const tchar*> items;`
- L197 _public member_ `u32 rowCharWidth;`
- L198 _public member_ `u32 rowMaxCount;`

#### class `uba::TraceReader`  
`class TraceReader`  
_L231-288_
- L234 _public prototype_ `TraceReader(Logger& logger);`
- L235 _public prototype_ `~TraceReader();`
- L238 _public prototype_ `bool ReadFile(TraceView& out, const tchar* fileName, bool replay);` — Use for file read
- L239 _public prototype_ `bool UpdateReadFile(TraceView& out, u64 maxTime, bool& outChanged);`
- L242 _public prototype_ `bool StartReadClient(TraceView& out, NetworkClient& client);` — Use for network
- L243 _public prototype_ `bool UpdateReadClient(TraceView& out, NetworkClient& client, bool& outChanged);`
- L244 _public prototype_ `bool UpdateReceiveClient(NetworkClient& client);`
- L247 _public prototype_ `bool StartReadNamed(TraceView& out, const tchar* namedTrace, bool silentFail = false, bool replay = false);` — Use for local
- L248 _public prototype_ `bool UpdateReadNamed(TraceView& out, u64 maxTime, bool& outChanged);`
- L250 _public prototype_ `bool ReadMemory(TraceView& out, bool trackHost, u64 maxTime);`
- L251 _public prototype_ `bool ReadTrace(TraceView& out, BinaryReader& reader, u64 maxTime);`
- L252 _public prototype_ `void StopAllActive(TraceView& out, u64 stopTime);`
- L253 _public prototype_ `void Reset(TraceView& out);`
- L254 _public prototype_ `void Unmap();`
- L256 _public prototype_ `bool SaveAs(const tchar* fileName);`
- L258 _public prototype_ `Guid ReadClientId(TraceView& out, BinaryReader& reader);`
- L259 _public prototype_ `TraceView::Session& GetSession(TraceView& out, u32 sessionIndex);`
- L260 _public prototype_ `TraceView::Session* GetSession(TraceView& out, const Guid& clientUid);`
- L262 _public prototype_ `TraceView::Process* ProcessBegin(TraceView& out, u32 sessionIndex, u32 id, u64 time, TString&& description, TString&& breadcrumbs, TraceView::ProcessType type);`
- L263 _public prototype_ `TraceView::Process* ProcessEnd(TraceView& out, u32& outSessionIndex, u32 id, u64 time);`
- L265 _public prototype_ `TraceView::SessionInfo ReadSessionInfo(StringBufferBase& info);`
- L267 _public member_ `UnorderedMap<u32, TraceView::ProcessLocation> m_activeProcesses;`
- L270 _public member_ `UnorderedMap<u32, WorkRecordLocation> m_activeWorkRecords;`
- L272 _public member_ `Vector<u32> m_sessionIndexToSession;`
- L274 _public member_ `Logger& m_logger;`
- L275 _public member_ `TraceChannel m_channel;`
- L276 _public member_ `FileMappingHandle m_memoryHandle;`
- L277 _public member_ `TString m_namedTrace;`
- L278 _public member_ `u8* m_memoryBegin = nullptr;`
- L279 _public member_ `u8* m_memoryPos = nullptr;`
- L280 _public member_ `u8* m_memoryEnd = nullptr;`
- L281 _public member_ `Futex m_memoryFutex;`
- L284 _public member_ `HANDLE m_hostProcess = NULL;`
- L286 _public member_ `pid_t m_hostProcess = 0;`

#### struct `uba::TraceReader::WorkRecordLocation`  
`struct WorkRecordLocation`  
_L269-269_
- L269 _public member_ `struct WorkRecordLocation { u32 track; u32 index; };`
- L269 _public member_ `struct WorkRecordLocation { u32 track; u32 index; };`

#### Free symbols / members of external scopes

- L11 _typedef_ `typedef void* HBITMAP;`
- L14 _namespace_ `namespace uba`

### `Source/Programs/UnrealBuildAccelerator/Visualizer/Private/UbaVisualizer.h` (Private)


#### class `uba::Visualizer`  
`class Visualizer`  
_L13-227_
- L16 _public prototype_ `Visualizer(VisualizerConfig& config, Logger& logger, VisualizerBackend& backend);`
- L17 _public prototype_ `void InitBrushes();`
- L19 _public prototype_ `u64 GetPlayTime();`
- L20 _public prototype_ `int GetTimelineHeight();`
- L21 _public prototype_ `int GetTimelineTop();`
- L22 _public prototype_ `StringBufferBase& GetTitlePrefix(StringBufferBase& out);`
- L23 _public prototype_ `StringBuffer<128> GetWorldTime(u64 time);`
- L24 _public prototype_ `StringBuffer<128> GetWorldTime(float seconds);`
- L25 _public prototype_ `bool ActiveProcessesShouldFillHeight();`
- L27 _public typedef_ `using Font = VisualizerBackend::Font;`
- L28 _public typedef_ `using PaintContext = VisualizerBackend::PaintContext;`
- L31 _public prototype_ `void HitTest(HitTestResult& outResult, PaintContext& context, const POINT& pos);`
- L32 _public prototype_ `void PaintAll(PaintContext& context, const RECT& clientRect);`
- L33 _public prototype_ `void PaintProcessRect(PaintContext& context, TraceView::Process& process, RECT rect, const RECT& progressRect, bool selected, bool writingBitmap);`
- L34 _public prototype_ `void PaintActiveProcesses(PaintContext& context, int& posY, const Function<void(TraceView::ProcessLocation&, u32, bool)>& drawProcess);`
- L35 _public prototype_ `void PaintTimeline(PaintContext& context);`
- L36 _public typedef_ `using DrawTextFunc = Function<void(const StringBufferBase& text, RECT& rect, u32* outWidth)>;`
- L37 _public prototype_ `void PaintDetailedStats(PaintContext& context, int& posY, const RECT& progressRect, TraceView::Session& session, bool isRemote, u64 playTime, const DrawTextFunc& drawTextFunc);`
- L38 _public prototype_ `void PrintCacheWriteStats(Logger& logger, u32 processId);`
- L39 _public prototype_ `void WriteProcessStats(Logger& out, const TraceView::Process& process);`
- L40 _public prototype_ `void WriteWorkStats(Logger& out, const TraceView::WorkRecord& record);`
- L42 _public prototype_ `virtual void PaintEmptyScreen(PaintContext& context);`
- L43 _public prototype_ `virtual void FinishIncompatible();`
- L44 _public prototype_ `virtual void Redraw(bool now);`
- L45 _public prototype_ `virtual void UpdateScrollbars(bool redraw);`
- L46 _public prototype_ `virtual void PostNewTitle(const StringView& title);`
- L47 _public prototype_ `virtual bool UpdateSelection();`
- L48 _public prototype_ `virtual void StopUpdate();`
- L49 _public prototype_ `virtual void GetFontMetrics(int& outFh, int& outOffset, int height);`
- L51 _public prototype_ `bool NewTrace(u32 replay, bool paused);`
- L52 _public prototype_ `bool UpdateTrace();`
- L53 _public prototype_ `bool UpdateAutoscroll();`
- L54 _public prototype_ `void Reset();`
- L55 _public prototype_ `bool Unselect();`
- L56 _public prototype_ `void UpdateFont(Font& font, int height, bool createUnderline);`
- L57 _public prototype_ `void UpdateDefaultFont();`
- L58 _public prototype_ `void UpdateProcessFont();`
- L59 _public prototype_ `void DirtyBitmaps(bool full);`
- L60 _public prototype_ `bool UpdateSelection(POINT pos);`
- L61 _public prototype_ `void UnselectAndRedraw();`
- L129 _public member_ `Logger& m_logger;`
- L130 _public member_ `VisualizerConfig m_config;`
- L131 _public member_ `TraceReader m_trace;`
- L132 _public member_ `TraceView m_traceView;`
- L133 _public member_ `VisualizerBackend& m_backend;`
- L135 _public member_ `StringBuffer<256> m_namedTrace;`
- L136 _public member_ `StringBuffer<256> m_fileName;`
- L137 _public member_ `NetworkClient* m_client = nullptr;`
- L138 _public member_ `Event m_clientDisconnect;`
- L139 _public member_ `Event m_listenTimeout;`
- L140 _public member_ `StringBuffer<256>m_listenChannel;`
- L141 _public member_ `StringBuffer<256> m_newTraceName;`
- L142 _public member_ `bool m_usingNamed = false;`
- L145 _public member_ `int m_clientWidth;`
- L146 _public member_ `int m_clientHeight;`
- L148 _public member_ `ProcessBrushes m_processBrushes[2];` — Non-selected and selected
- L150 _public member_ `static constexpr int GraphHeight = 30;`
- L152 _public member_ `COLORREF m_textColor = {};`
- L153 _public member_ `COLORREF m_textWarningColor = {};`
- L154 _public member_ `COLORREF m_textErrorColor = {};`
- L155 _public member_ `COLORREF m_sendColor = {};`
- L156 _public member_ `COLORREF m_recvColor = {};`
- L157 _public member_ `COLORREF m_cpuColor = {};`
- L158 _public member_ `COLORREF m_memColor = {};`
- L159 _public member_ `COLORREF m_driveColor = {};`
- L160 _public member_ `COLORREF m_activeProcColor = {};`
- L161 _public member_ `BrushHandle m_backgroundBrush = 0;`
- L162 _public member_ `BrushHandle m_tooltipBackgroundBrush = 0;`
- L163 _public member_ `PenHandle m_textPen = 0;`
- L164 _public member_ `PenHandle m_separatorPen = 0;`
- L165 _public member_ `PenHandle m_sendPen = 0;`
- L166 _public member_ `PenHandle m_recvPen = 0;`
- L167 _public member_ `PenHandle m_cpuPen = 0;`
- L168 _public member_ `PenHandle m_memPen = 0;`
- L169 _public member_ `PenHandle m_drivePen = 0;`
- L170 _public member_ `PenHandle m_activeProcPen = 0;`
- L171 _public member_ `PenHandle m_processUpdatePen = 0;`
- L172 _public member_ `PenHandle m_checkboxPen = 0;`
- L173 _public member_ `int m_sessionStepY = 0;`
- L175 _public member_ `int m_processFontOffsetY = 0;`
- L177 _public member_ `Font m_defaultFont;`
- L178 _public member_ `Font m_processFont;`
- L179 _public member_ `Font m_timelineFont;`
- L180 _public member_ `Font m_popupFont;`
- L182 _public member_ `Font m_activeProcessFont[32];`
- L183 _public member_ `u32 m_activeProcessCountHistory[5];`
- L184 _public member_ `u32 m_activeProcessCountHistoryIterator = 0;`
- L186 _public member_ `bool m_autoScroll = true;`
- L187 _public member_ `bool m_paused = false;`
- L188 _public member_ `u32 m_replay = 0;`
- L189 _public member_ `u64 m_startTime = 0;`
- L190 _public member_ `u64 m_pauseTime = 0;`
- L191 _public member_ `u64 m_pauseStart = 0;`
- L193 _public member_ `bool m_mouseOverWindow = false;`
- L195 _public member_ `int m_progressRectLeft = 30;`
- L196 _public member_ `int m_contentWidth = 0;`
- L197 _public member_ `int m_contentHeight = 0;`
- L199 _public member_ `float m_scrollPosX = 0;`
- L200 _public member_ `float m_scrollPosY = 0;`
- L201 _public member_ `float m_zoomValue = 0.5f;`
- L202 _public member_ `float m_horizontalScaleValue = 0.5f;`
- L204 _public member_ `u32 m_activeSection = ~0u;`
- L205 _public member_ `TraceView::ProcessLocation m_processSelectedLocation;`
- L206 _public member_ `bool m_processSelected = false;`
- L207 _public member_ `u32 m_sessionSelectedIndex = ~0u;`
- L208 _public member_ `bool m_statsSelected = false;`
- L209 _public member_ `bool m_activeProcessGraphSelected = false;`
- L210 _public member_ `u64 m_activeProcessCount = 0u;`
- L211 _public member_ `Stats m_stats;`
- L212 _public member_ `u32 m_buttonSelected = ~0u;`
- L213 _public member_ `float m_timelineSelected = 0;`
- L214 _public member_ `u32 m_fetchedFilesSelected = ~0u;`
- L215 _public member_ `TString m_hyperLinkSelected;`
- L217 _public member_ `TString m_filterString;`
- L219 _public member_ `UnorderedMap<Color, BrushHandle> m_coloredBrushes;`
- L221 _public member_ `bool m_workSelected = false;`
- L222 _public member_ `u32 m_workTrack = ~0u;`
- L223 _public member_ `u32 m_workIndex = ~0u;`
- L226 _public prototype_ `void DrawCenteredText(VisualizerBackend::PaintContext& context, const StringBuffer<>* rows, u32 rowCount, BrushHandle backgroundBrush);`

#### enum `uba::Visualizer::VisualizerFlag`  
`enum VisualizerFlag`  
_L63-69_
- L66 _public enumerator_ `UBA_VISUALIZER_FLAGS1 #undef UBA_VISUALIZER_FLAG VisualizerFlag_Count`

#### struct `uba::Visualizer::Stats`  
`struct Stats`  
_L71-92_
- L73 _public member_ `u64 recvBytesPerSecond = 0;`
- L74 _public member_ `u64 sendBytesPerSecond = 0;`
- L75 _public member_ `u64 ping = 0;`
- L76 _public member_ `u64 memAvail = 0;`
- L77 _public member_ `u64 memTotal = 0;`
- L78 _public member_ `u64 recvBytes = 0;`
- L79 _public member_ `u64 sendBytes = 0;`
- L80 _public member_ `u64 procActive = 0;`
- L81 _public member_ `float cpuLoad = 0;`
- L82 _public member_ `u16 connectionCount = 0;`
- L90 _public member_ `Map<char, Drive> drives;`
- L91 _public prototype_ `bool operator==(const Stats& o) const;`

#### struct `uba::Visualizer::Stats::Drive`  
`struct Drive`  
_L84-89_
- L86 _public member_ `u8 busyPercent;`
- L87 _public member_ `u32 readPerSecond = 0;`
- L88 _public member_ `u32 writePerSecond = 0;`

#### struct `uba::Visualizer::HitTestResult`  
`struct HitTestResult`  
_L94-111_
- L96 _public member_ `u32 section = ~0u;`
- L97 _public member_ `TraceView::ProcessLocation processLocation;`
- L98 _public member_ `bool processSelected = false;`
- L99 _public member_ `u32 sessionSelectedIndex = ~0u;`
- L100 _public member_ `bool statsSelected = false;`
- L101 _public member_ `Stats stats;`
- L102 _public member_ `u32 buttonSelected = ~0u;`
- L103 _public member_ `float timelineSelected = 0;`
- L104 _public member_ `u32 fetchedFilesSelected = ~0u;`
- L105 _public member_ `bool workSelected = false;`
- L106 _public member_ `u32 workTrack = ~0u;`
- L107 _public member_ `u32 workIndex = ~0u;`
- L108 _public member_ `bool activeProcessGraphSelected = false;`
- L109 _public member_ `u16 activeProcessCount = 0u;`
- L110 _public member_ `TString hyperLink;`

#### struct `uba::Visualizer::ProcessBrushes`  
`struct ProcessBrushes`  
_L113-127_
- L115 _public member_ `BrushHandle inProgress = 0;`
- L116 _public member_ `BrushHandle inProgressRace = 0;`
- L117 _public member_ `BrushHandle success = 0;`
- L118 _public member_ `BrushHandle error = 0;`
- L119 _public member_ `BrushHandle returned = 0;`
- L120 _public member_ `BrushHandle recv = 0;`
- L121 _public member_ `BrushHandle send = 0;`
- L122 _public member_ `BrushHandle cacheFetchTest = 0;`
- L123 _public member_ `BrushHandle cacheFetchDownload = 0;`
- L124 _public member_ `BrushHandle cacheMiss = 0;`
- L125 _public member_ `BrushHandle warning = 0;`
- L126 _public member_ `BrushHandle idle = 0;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace uba`
- L65 _macro_ `#define UBA_VISUALIZER_FLAG(name, defaultValue, desc) VisualizerFlag_##name,`

### `Source/Programs/UnrealBuildAccelerator/Visualizer/Private/UbaVisualizerBackend.h` (Private)


#### struct `uba::POINT`  
`struct POINT`  
_L12-12_
- L12 _public member_ `struct POINT { int x; int y; };`
- L12 _public member_ `struct POINT { int x; int y; };`

#### struct `uba::SIZE`  
`struct SIZE`  
_L13-13_
- L13 _public member_ `struct SIZE { int cx; int cy; };`
- L13 _public member_ `struct SIZE { int cx; int cy; };`

#### struct `uba::RECT`  
`struct RECT`  
_L14-14_
- L14 _public member_ `struct RECT { int left; int top; int right; int bottom; };`
- L14 _public member_ `struct RECT { int left; int top; int right; int bottom; };`
- L14 _public member_ `struct RECT { int left; int top; int right; int bottom; };`
- L14 _public member_ `struct RECT { int left; int top; int right; int bottom; };`

#### class `uba::VisualizerBackend`  
`class VisualizerBackend`  
_L28-76_
- L61 _public prototype_ `virtual const tchar* GetName() = 0;`
- L62 _public prototype_ `virtual void Init(void* windowHandle) = 0;`
- L63 _public prototype_ `virtual void Reset() = 0;`
- L65 _public prototype_ `virtual void Resize(int width, int height) = 0;`
- L66 _public prototype_ `virtual void Paint(const Function<void(PaintContext& context, RECT rect)>& func) = 0;`
- L68 _public prototype_ `virtual PaintContext* CreateContext(int clientWidth, int clientHeight) = 0;`
- L69 _public prototype_ `virtual void DeleteContext(PaintContext*) = 0;`
- L71 _public prototype_ `virtual BrushHandle CreateSolidBrush(COLORREF color) = 0;`
- L72 _public prototype_ `virtual PenHandle CreatePen(COLORREF color) = 0;`
- L74 _public prototype_ `virtual FontHandle CreateFont(const tchar* font, int height, bool createUnderline) = 0;`
- L75 _public prototype_ `virtual void DeleteFont(FontHandle font) = 0;`

#### struct `uba::VisualizerBackend::Font`  
`struct Font`  
_L31-37_
- L33 _public member_ `FontHandle handle = 0;`
- L34 _public member_ `FontHandle handleUnderlined = 0;`
- L35 _public member_ `int height = 0;`
- L36 _public member_ `int offset = 0;`

#### struct `uba::VisualizerBackend::PaintContext`  
`struct PaintContext`  
_L39-59_
- L41 _public prototype_ `virtual SIZE GetClientSize() = 0;`
- L42 _public prototype_ `virtual void SetPen(PenHandle pen) = 0;`
- L43 _public prototype_ `virtual void SetBrush(BrushHandle b) = 0;`
- L44 _public prototype_ `virtual void SetFont(const Font& font, bool underlined = false) = 0;`
- L45 _public prototype_ `virtual void SetTextColor(COLORREF color) = 0;`
- L46 _public prototype_ `virtual void Text(int x, int y, StringView str, const RECT* clipRect) = 0;`
- L47 _public prototype_ `virtual COLORREF GetTextColor() = 0;`
- L48 _public prototype_ `virtual Font& GetFont() = 0;`
- L49 _public prototype_ `virtual void FillRect(const RECT& r, BrushHandle b) = 0;`
- L50 _public prototype_ `virtual void Rectangle(int left, int top, int right, int bottom) = 0;`
- L51 _public prototype_ `virtual void Line(int fromX, int fromY, int toX, int toY) = 0;`
- L52 _public prototype_ `virtual void Polyline(u32 cacheId, const Vector<POINT>& polyLine) = 0;`
- L53 _public prototype_ `virtual void PolyPolyline(const POINT* points, const u32* lines, u32 lineCount) = 0;`
- L54 _public prototype_ `virtual SIZE GetTextSize(StringView str) = 0;`
- L55 _public prototype_ `virtual void DrawCached(TraceView::BitmapCache& process, RECT rect, int offsetY, int textHeight, Font& processFont, RECT clippingRect, const Function<void(PaintContext& textCacheContext)>& func) = 0;`
- L56 _public function_ `virtual void EndCached()`
- L58 _public prototype_ `virtual POINT GetCursorClientPos() = 0;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace uba`
- L15 _typedef_ `using COLORREF = u32;` (scope `uba`)
- L16 _macro_ `#define RGB(r,g,b) ((COLORREF)((u8(r)|(u16(u8(g))<<8))|(u32(u8(b))<<16)))`
- L17 _macro_ `#define GET_RED(c) u8(c & 0xff)`
- L18 _macro_ `#define GET_GREEN(c) u8((c >> 8) & 0xff)`
- L19 _macro_ `#define GET_BLUE(c) u8((c >> 16) & 0xff)`
- L22 _typedef_ `using BrushHandle = void*;` (scope `uba`)
- L23 _typedef_ `using PenHandle = void*;` (scope `uba`)
- L24 _typedef_ `using FontHandle = void*;` (scope `uba`)

### `Source/Programs/UnrealBuildAccelerator/Visualizer/Private/UbaVisualizerConfig.h` (Private)


#### struct `uba::VisualizerConfig`  
`struct VisualizerConfig`  
_L40-70_
- L42 _public prototype_ `VisualizerConfig(const tchar* filename);`
- L44 _public prototype_ `bool Load(Logger& logger);`
- L45 _public prototype_ `bool Save(Logger& logger);`
- L47 _public member_ `TString filename;`
- L49 _public member_ `int x = 100;`
- L50 _public member_ `int y = 100;`
- L51 _public member_ `u32 width = 1500;`
- L52 _public member_ `u32 height = 1500;`
- L53 _public member_ `u32 fontSize = 13;`
- L54 _public member_ `TString fontName;`
- L55 _public member_ `u32 maxActiveVisible = 5;`
- L56 _public member_ `u32 maxActiveProcessHeight = 16;`
- L57 _public member_ `u32 boxHeight = 12;`
- L58 _public member_ `float horizontalScaleValue = 0.5f;`
- L59 _public member_ `bool useGDI = false;`
- L69 _public member_ `u64 parent = 0;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace uba`
- L13 _macro_ `#define UBA_VISUALIZER_FLAGS1 \`
- L29 _macro_ `#define UBA_VISUALIZER_FLAGS2 \`
- L61 _macro_ `#define UBA_VISUALIZER_FLAG(name, defaultValue, desc) bool show##name = defaultValue;`
- L65 _macro_ `#define UBA_VISUALIZER_FLAG(name, defaultValue, desc) bool name = defaultValue;`

### `Source/Programs/UnrealBuildAccelerator/Visualizer/Private/Windows/UbaVisualizerBackendD2D.h` (Private)


#### class `uba::VisualizerBackendD2D`  
`class VisualizerBackendD2D final : public VisualizerBackend`  
_L20-408_
- inherits: `VisualizerBackend`
- L23 _public member_ `static constexpr int BitmapCacheHeight = 16*1024;`
- L25 _public function_ `static inline D2D1::ColorF ToRgbD2D(COLORREF c)`
- L263 _public function_ `VisualizerBackendD2D(VisualizerWin& o) : m_owner(o)`
- L267 _public function_ `virtual const tchar* GetName() override`
- L269 _public function_ `bool Create()`
- L280 _public function_ `virtual void Init(void* windowHandle) override`
- L284 _public function_ `virtual void Reset() override`
- L297 _public function_ `virtual void Resize(int width, int height) override`
- L303 _public function_ `virtual void Paint(const Function<void(PaintContext& context, RECT rect)>& func) override`
- L353 _public function_ `virtual PaintContext* CreateContext(int clientWidth, int clientHeight) override`
- L358 _public function_ `virtual void DeleteContext(PaintContext* context) override`
- L363 _public function_ `virtual BrushHandle CreateSolidBrush(COLORREF color) override`
- L371 _public function_ `virtual PenHandle CreatePen(COLORREF color) override`
- L376 _public function_ `virtual FontHandle CreateFont(const tchar* font, int height, bool createUnderline) override`
- L389 _public function_ `virtual void DeleteFont(FontHandle font)`
- L394 _public member_ `VisualizerWin& m_owner;`
- L395 _public member_ `ID2D1Factory* m_d2dFactory = nullptr;`
- L396 _public member_ `ID2D1HwndRenderTarget* m_d2dRenderTarget = nullptr;`
- L397 _public member_ `List<ID2D1SolidColorBrush*> m_brushes;`
- L399 _public member_ `IDWriteFactory* m_dwFactory = nullptr;`
- L400 _public member_ `ID2D1SolidColorBrush* m_textBrush = nullptr;`
- L402 _public member_ `ID2D1BitmapRenderTarget* m_lastBitmap = 0;`
- L403 _public member_ `int m_bitmapCacheHeight = BitmapCacheHeight;`
- L404 _public member_ `int m_lastBitmapOffset = BitmapCacheHeight;`
- L405 _public member_ `Vector<ID2D1BitmapRenderTarget*> m_textBitmaps;`
- L407 _public member_ `bool m_dirty = true;`

#### struct `uba::VisualizerBackendD2D::PaintContextD2D`  
`struct PaintContextD2D final : public PaintContext`  
_L30-261_
- inherits: `PaintContext`
- L32 _public function_ `PaintContextD2D(VisualizerBackendD2D& o, ID2D1RenderTarget& rt, SIZE cs) : owner(o) , renderTarget(rt) , clientSize(cs)`
- L39 _public function_ `virtual SIZE GetClientSize() override`
- L43 _public function_ `virtual void SetPen(PenHandle pen) override`
- L47 _public function_ `virtual void SetBrush(BrushHandle b) override`
- L51 _public function_ `virtual void SetFont(const Font& font, bool underlined = false) override`
- L56 _public function_ `virtual void SetTextColor(COLORREF color) override`
- L64 _public function_ `virtual void Text(int x, int y, StringView str, const RECT* clipRect) override`
- L102 _public function_ `virtual COLORREF GetTextColor() override`
- L106 _public function_ `virtual Font& GetFont() override`
- L110 _public function_ `virtual void FillRect(const RECT& r, BrushHandle b) override`
- L115 _public function_ `virtual void Rectangle(int left, int top, int right, int bottom) override`
- L121 _public function_ `virtual void Line(int fromX, int fromY, int toX, int toY) override`
- L128 _public function_ `virtual void Polyline(u32 cacheId, const Vector<POINT>& polyLine) override`
- L142 _public function_ `virtual void PolyPolyline(const POINT* points, const u32* lines, u32 lineCount) override`
- L161 _public function_ `virtual SIZE GetTextSize(StringView str) override`
- L172 _public function_ `virtual void DrawCached(TraceView::BitmapCache& process, RECT rect, int offsetY, int textHeight, Font& processFont, RECT clippingRect, const Function<void(PaintContext& textCacheContext)>& func) override`
- L244 _public function_ `virtual POINT GetCursorClientPos() override`
- L252 _public member_ `VisualizerBackendD2D& owner;`
- L253 _public member_ `ID2D1RenderTarget& renderTarget;`
- L254 _public member_ `SIZE clientSize;`
- L255 _public member_ `PenHandle activePen = 0;`
- L256 _public member_ `BrushHandle activeBrush = 0;`
- L257 _public member_ `Font activeFont;`
- L258 _public member_ `IDWriteTextFormat* activeFontHandle = nullptr;`
- L259 _public member_ `COLORREF activeTextColor = 0;`
- L260 _public member_ `ID2D1BitmapRenderTarget* lastSelectedBitmap = 0;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace uba`
- L82 _function_ `auto g = MakeGuard([&]() { if (clipRect) renderTarget.PopAxisAlignedClip(); });` (scope `uba::VisualizerBackendD2D::PaintContextD2D::Text`)

### `Source/Programs/UnrealBuildAccelerator/Visualizer/Private/Windows/UbaVisualizerBackendGDI.h` (Private)


#### class `uba::VisualizerBackendGDI`  
`class VisualizerBackendGDI final : public VisualizerBackend`  
_L13-295_
- inherits: `VisualizerBackend`
- L16 _public member_ `static constexpr int BitmapCacheHeight = 1024*1024;`
- L181 _public function_ `VisualizerBackendGDI(VisualizerWin& owner) : m_owner(owner)`
- L185 _public function_ `virtual const tchar* GetName() override`
- L187 _public function_ `virtual void Init(void* windowHandle) override`
- L192 _public function_ `virtual void Reset() override`
- L203 _public function_ `virtual void Resize(int width, int height) override`
- L207 _public function_ `virtual void Paint(const Function<void(PaintContext& context, RECT rect)>& func) override`
- L256 _public function_ `virtual PaintContext* CreateContext(int clientWidth, int clientHeight) override`
- L261 _public function_ `virtual void DeleteContext(PaintContext* context) override`
- L266 _public function_ `virtual BrushHandle CreateSolidBrush(COLORREF color) override`
- L271 _public function_ `virtual PenHandle CreatePen(COLORREF color) override`
- L276 _public function_ `FontHandle CreateFont(const tchar* font, int height, bool createUnderline) override`
- L282 _public function_ `void DeleteFont(FontHandle font)`
- L287 _public member_ `VisualizerWin& m_owner;`
- L289 _public member_ `HBITMAP m_cachedBitmap = 0;`
- L290 _public member_ `SIZE m_cachedBitmapSize = { INT_MIN, INT_MIN };`
- L292 _public member_ `HBITMAP m_lastBitmap = 0;`
- L293 _public member_ `int m_lastBitmapOffset = BitmapCacheHeight;`
- L294 _public member_ `Vector<HBITMAP> m_textBitmaps;`

#### struct `uba::VisualizerBackendGDI::PaintContextGDI`  
`struct PaintContextGDI final : public PaintContext`  
_L18-179_
- inherits: `PaintContext`
- L20 _public function_ `virtual SIZE GetClientSize() override`
- L21 _public function_ `virtual void SetTextColor(COLORREF color) override`
- L22 _public function_ `virtual COLORREF GetTextColor() override`
- L23 _public function_ `virtual void SetPen(PenHandle pen) override`
- L24 _public function_ `virtual void Text(int x, int y, StringView str, const RECT* clipRect) override`
- L29 _public function_ `virtual void SetFont(const Font& font, bool underlined) override`
- L46 _public function_ `virtual Font& GetFont() override`
- L51 _public function_ `virtual void SetBrush(BrushHandle b) override`
- L60 _public function_ `virtual void FillRect(const RECT& r, BrushHandle b) override`
- L66 _public function_ `virtual void Rectangle(int left, int top, int right, int bottom) override`
- L72 _public function_ `virtual void Line(int fromX, int fromY, int toX, int toY) override`
- L78 _public function_ `virtual void Polyline(u32 cacheId, const Vector<POINT>& polyLine) override`
- L83 _public function_ `virtual void PolyPolyline(const POINT* points, const u32* lines, u32 lineCount) override`
- L88 _public function_ `virtual SIZE GetTextSize(StringView str) override`
- L94 _public function_ `virtual void DrawCached(TraceView::BitmapCache& process, RECT rect, int offsetY, int textHeight, Font& processFont, RECT clippingRect, const Function<void(PaintContext& textCacheContext)>& func) override`
- L157 _public function_ `virtual POINT GetCursorClientPos() override`
- L165 _public function_ `PaintContextGDI(VisualizerBackendGDI& o, HWND hw, HDC dc, SIZE cs, HDC tdc = 0) : owner(o), hwnd(hw), hdc(dc), clientSize(cs), textDC(tdc)`
- L168 _public member_ `VisualizerBackendGDI& owner;`
- L169 _public member_ `HWND hwnd;`
- L170 _public member_ `HDC hdc;`
- L171 _public member_ `SIZE clientSize;`
- L173 _public member_ `Font activeFont;`
- L174 _public member_ `FontHandle activeFontHandle;`
- L176 _public member_ `HDC textDC = NULL;`
- L177 _public member_ `BrushHandle lastSelectedBrush = 0;`
- L178 _public member_ `HBITMAP lastSelectedBitmap = 0;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace uba`

### `Source/Programs/UnrealBuildAccelerator/Visualizer/Private/Windows/UbaVisualizerWin.h` (Private)


#### class `uba::VisualizerWin`  
`class VisualizerWin : public Visualizer, public IDropTarget`  
_L14-93_
- inherits: `Visualizer,IDropTarget`
- L17 _public prototype_ `VisualizerWin(VisualizerConfig& config, Logger& logger);`
- L18 _public prototype_ `~VisualizerWin();`
- L20 _public prototype_ `bool ShowUsingListener(const wchar_t* channelName);`
- L21 _public prototype_ `bool ShowUsingNamedTrace(const wchar_t* namedTrace);`
- L22 _public prototype_ `bool ShowUsingSocket(NetworkBackend& backend, const wchar_t* host, u16 port = DefaultPort);`
- L23 _public prototype_ `bool ShowUsingFile(const wchar_t* fileName, u32 replay);`
- L25 _public prototype_ `bool HasWindow();`
- L26 _public prototype_ `HWND GetHwnd();`
- L27 _public prototype_ `void Lock(bool lock);`
- L30 _public prototype_ `bool StartHwndThread();` — private:
- L31 _public prototype_ `virtual void PaintEmptyScreen(PaintContext& context) override;`
- L32 _public prototype_ `virtual void FinishIncompatible() override;`
- L34 _public prototype_ `void CopyTextToClipboard(const TString& str);`
- L35 _public prototype_ `virtual bool UpdateSelection() override;`
- L36 _public prototype_ `virtual void UpdateScrollbars(bool redraw) override;`
- L37 _public prototype_ `void ThreadLoop();`
- L38 _public prototype_ `void Pause(bool pause);`
- L39 _public prototype_ `void StartDragToScroll(const POINT& anchor);`
- L40 _public prototype_ `void StopDragToScroll();`
- L41 _public prototype_ `void SaveSettings();`
- L43 _public prototype_ `void ChangeFontSize(int offset);`
- L44 _public prototype_ `virtual void Redraw(bool now) override;`
- L45 _public prototype_ `virtual void StopUpdate() override;`
- L46 _public prototype_ `void UpdateTheme();`
- L49 _public prototype_ `virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void** ppvObject) override;` — IUnknown interface
- L50 _public prototype_ `virtual ULONG STDMETHODCALLTYPE AddRef(void) override;`
- L51 _public prototype_ `virtual ULONG STDMETHODCALLTYPE Release(void) override;`
- L53 _public prototype_ `virtual HRESULT STDMETHODCALLTYPE DragEnter(__RPC__in_opt IDataObject* pDataObj, ::DWORD grfKeyState, POINTL pt, __RPC__inout::DWORD* pdwEffect) override;` — IDropTarget interface
- L54 _public prototype_ `virtual HRESULT STDMETHODCALLTYPE DragOver(::DWORD grfKeyState, POINTL pt, __RPC__inout::DWORD* pdwEffect) override;`
- L55 _public prototype_ `virtual HRESULT STDMETHODCALLTYPE DragLeave(void) override;`
- L56 _public prototype_ `virtual HRESULT STDMETHODCALLTYPE Drop(__RPC__in_opt IDataObject* pDataObj, ::DWORD grfKeyState, POINTL pt, __RPC__inout::DWORD* pdwEffect) override;`
- L58 _public member_ `ULONG m_OLEReferenceCount = 0;`
- L60 _public member_ `u64 m_lastPaintTimeMs = 0;`
- L62 _public member_ `Atomic<bool> m_looping = false;`
- L63 _public member_ `HWND m_hwnd = 0;`
- L64 _public member_ `HWND m_parentHwnd = 0;`
- L66 _public member_ `int m_contentWidthWhenThumbTrack = 0;`
- L68 _public member_ `bool m_isInPaint = false;`
- L70 _public member_ `bool m_showPopup = false;`
- L71 _public member_ `bool m_locked = false;`
- L72 _public member_ `bool m_handlingTimer = false;`
- L73 _public member_ `bool m_settingsDirty = false;`
- L75 _public member_ `POINT m_mouseAnchor = {};`
- L76 _public member_ `float m_scrollAtAnchorX = 0;`
- L77 _public member_ `float m_scrollAtAnchorY = 0;`
- L78 _public member_ `int m_dragToScrollCounter = 0;`
- L80 _public member_ `bool m_horizontalScrollBarEnabled = true;`
- L81 _public member_ `bool m_verticalScrollBarEnabled = true;`
- L83 _public member_ `Thread m_thread;`
- L85 _public prototype_ `void PostNewTrace(u32 replay, bool paused);`
- L86 _public prototype_ `virtual void PostNewTitle(const StringView& title);`
- L87 _public prototype_ `void PostQuit();`
- L88 _public prototype_ `LRESULT WinProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);`
- L89 _public prototype_ `static LRESULT CALLBACK StaticWinProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace uba`
