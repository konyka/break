# Runtime / AVIWriter

- module root: `Source/Runtime/AVIWriter`
- headers: 3; symbols: 88
- symbol kinds: class=3, delegate=2, function=13, member=34, prototype=31, struct=3, typedef=2
- PublicDependencyModuleNames: Core

### `Source/Runtime/AVIWriter/Private/CapturePin.h` (Private)


#### class `FCapturePin`  
`class FCapturePin : public CSourceStream`  
_L47-96_
- inherits: `CSourceStream`
- L52 _protected member_ `const REFERENCE_TIME FrameLength;` — The length of the frame, used for playback
- L54 _protected member_ `int32 ImageHeight;` — The current image height
- L56 _protected member_ `int32 ImageWidth;` — And current image width
- L58 _protected member_ `CCritSec SharedState;` — Protects our internal state
- L61 _protected member_ `const FAVIWriter& Writer;` — The writer to which we belong
- L64 _protected member_ `const FCapturedFrame* CurrentFrame;` — The frame we're currently processing
- L66 _protected prototype_ `TOptional<HRESULT> ProcessFrames();`
- L70 _public prototype_ `FCapturePin(HRESULT *phr, CSource *pFilter, const FAVIWriter& InWriter);`
- L71 _public prototype_ `~FCapturePin();`
- L74 _public prototype_ `HRESULT DecideBufferSize(IMemAllocator *pAlloc, ALLOCATOR_PROPERTIES *pRequest);` — Override the version that offers exactly one media type
- L75 _public prototype_ `HRESULT FillBuffer(IMediaSample *pSample);`
- L78 _public prototype_ `HRESULT DoBufferProcessingLoop(void);` — the loop executed while running
- L81 _public prototype_ `HRESULT SetMediaType(const CMediaType *pMediaType);` — Set the agreed media type and set up the necessary parameters
- L84 _public prototype_ `HRESULT CheckMediaType(const CMediaType *pMediaType);` — Support multiple display formats
- L85 _public prototype_ `HRESULT GetMediaType(int32 iPosition, CMediaType *pmt);`
- L91 _public function_ `STDMETHODIMP Notify(IBaseFilter *pSelf, Quality q)` — Quality control Not implemented because we aren't going in real time. If the file-writing filter slows the graph down, we just do nothing, which means wait until we're unblocked. No frames are ever dropped.

#### Free symbols / members of external scopes

- L18 _typedef_ `typedef TCHAR* PTCHAR;`

### `Source/Runtime/AVIWriter/Private/CaptureSource.h` (Private)


#### class `FCaptureSource`  
`class FCaptureSource : public CSource`  
_L40-53_
- inherits: `CSource`
- L43 _public prototype_ `FCaptureSource(const FAVIWriter& Writer);`
- L44 _public prototype_ `~FCaptureSource();`
- L46 _public prototype_ `void StopCapturing();`
- L47 _public prototype_ `void OnFinishedCapturing();`
- L48 _public function_ `bool ShouldCapture() const`
- L51 _private member_ `FEvent* ShutdownEvent;`
- L52 _private member_ `FThreadSafeBool bShutdownRequested;`

#### Free symbols / members of external scopes

- L16 _typedef_ `typedef TCHAR* PTCHAR;`

### `Source/Runtime/AVIWriter/Public/AVIWriter.h` (Public)


#### struct `FAVIWriterOptions`  
`struct FAVIWriterOptions`  
_L33-65_
- desc: Creation options for the AVI writer
- L35 _public function_ `FAVIWriterOptions() : OutputFilename(FPaths::VideoCaptureDir() / TEXT("Capture.avi")) , CaptureFramerateNumerator(30) , CaptureFramerateDenominator(1) , bSynchronizeFrames(false) , Width(0) , Height(0)`
- L45 _public member_ `FString OutputFilename;` — Output filename
- L48 _public member_ `int32 CaptureFramerateNumerator;` — The numerator of the captured video, ie (30/1) will capture at 30 frames per second.
- L51 _public member_ `int32 CaptureFramerateDenominator;` — The denominator of the captured video, ie (30/1) will capture at 30 frames per second.
- L54 _public member_ `TOptional<float> CompressionQuality;` — Optional compression quality, as a value between 0 and 1
- L57 _public member_ `FString CodecName;` — Optional codec to use for compression
- L60 _public member_ `bool bSynchronizeFrames;` — When true, the game thread will block until captured frames have been processed by the avi writer
- L62 _public member_ `uint32 Width;`
- L64 _public member_ `uint32 Height;`

#### struct `FCapturedFrame`  
`struct FCapturedFrame`  
_L68-91_
- desc: Data structure representing a captured frame
- L70 _public function_ `FCapturedFrame() : StartTimeSeconds(), EndTimeSeconds(), FrameIndex(), FrameProcessedEvent(nullptr)`
- L75 _public prototype_ `FCapturedFrame(double InStartTimeSeconds, double InEndTimeSeconds, uint32 InFrameIndex, TArray<FColor> InFrameData);`
- L76 _public prototype_ `~FCapturedFrame();`
- L78 _public function_ `FCapturedFrame(FCapturedFrame&& In) : StartTimeSeconds(In.StartTimeSeconds), EndTimeSeconds(In.EndTimeSeconds), FrameIndex(In.FrameIndex), FrameData(MoveTemp(In.FrameData)), FrameProcessedEvent(In.FrameProcessedEvent)`
- L79 _public function_ `FCapturedFrame& operator=(FCapturedFrame&& In)`
- L82 _public member_ `double StartTimeSeconds;` — The start time of this frame
- L84 _public member_ `double EndTimeSeconds;` — The End time of this frame
- L86 _public member_ `uint32 FrameIndex;` — The frame index of this frame in the stream
- L88 _public member_ `TArray<FColor> FrameData;` — The frame data itself (empty for a dropped frame)
- L90 _public member_ `FEvent* FrameProcessedEvent;` — Triggered when the frame has been processed

#### struct `FCapturedFrames`  
`struct FCapturedFrames`  
_L94-144_
- desc: Container for managing captured frames. Temporarily archives frames to the file system when capture rate drops.
- L97 _public prototype_ `FCapturedFrames(const FString& InArchiveDirectory, int32 InMaxInMemoryFrames);` — Construct from a directory to place archives in, and a maximum number of frames we can hold in
- L98 _public prototype_ `~FCapturedFrames();`
- L101 _public prototype_ `void Add(FCapturedFrame Frame);` — Add a captured frame to this container. Only to be called from the owner tasread.
- L104 _public prototype_ `TArray<FCapturedFrame> ReadFrames(uint32 WaitTimeMs);` — Read frames from this container (potentially from a thread)
- L107 _public prototype_ `int32 GetNumOutstandingFrames() const;` — Retrieve the number of oustanding frames we have not processed yet
- L112 _private prototype_ `void ArchiveFrame(FCapturedFrame Frame);` — Archive a frame
- L115 _private prototype_ `TOptional<FCapturedFrame> UnArchiveFrame(uint32 FrameIndex) const;` — Unarchive a frame represented by the given unique index
- L118 _private prototype_ `void StartUnArchiving();` — Start a task to unarchive some frames
- L121 _private member_ `FString ArchiveDirectory;` — The directory in which we will place temporarily archived frames
- L124 _private member_ `mutable FCriticalSection ArchiveFrameMutex;` — A mutex to protect the archived frame indices
- L126 _private member_ `TArray<uint32> ArchivedFrames;` — Array of unique frame indices that have been archived
- L129 _private member_ `uint32 TotalArchivedFrames;` — The total number of frames that have been archived since capturing started
- L132 _private member_ `FEvent* FrameReady;` — An event that triggers when there are in-memory frames ready for collection
- L135 _private member_ `mutable FCriticalSection InMemoryFrameMutex;` — Mutex to protect the in memory frames
- L137 _private member_ `TArray<FCapturedFrame> InMemoryFrames;` — Array of in-memory captured frames
- L140 _private member_ `int32 MaxInMemoryFrames;` — The maximum number of frames we are to store in memory before archiving
- L143 _private member_ `TOptional<TFuture<void>> UnarchiveTask;` — Unarchive task result

#### class `FAVIWriter`  
`class FAVIWriter`  
_L147-216_
- desc: Class responsible for writing frames out to an AVI file
- L151 _protected function_ `FAVIWriter(const FAVIWriterOptions& InOptions) : bCapturing(false) , FrameNumber(0) , Options(InOptions)` — Protected constructor to avoid abuse.
- L159 _protected member_ `FThreadSafeBool bCapturing;` — Whether we are capturing or not
- L162 _protected member_ `int32 FrameNumber;` — The current frame number
- L165 _protected member_ `mutable TUniquePtr<FCapturedFrames> CapturedFrames;` — Container that manages frames that we have already captured
- L170 _public prototype_ `virtual ~FAVIWriter();` — Public destruction
- L173 _public member_ `FAVIWriterOptions Options;` — Creation options
- L176 _public prototype_ `static FAVIWriter* CreateInstance(const FAVIWriterOptions& InOptions);` — Create a new avi writer from the specified options
- L179 _public function_ `TArray<FCapturedFrame> GetFrameData(uint32 WaitTimeMs) const` — Access captured frame data. Safe to be called from any thread.
- L185 _public function_ `int32 GetNumOutstandingFrames() const` — Retrieve the number of oustanding frames we have not processed yet
- L190 _public function_ `uint32 GetWidth() const`
- L195 _public function_ `uint32 GetHeight() const`
- L200 _public function_ `int32 GetFrameNumber() const`
- L205 _public function_ `bool IsCapturing() const`
- L210 _public prototype_ `void Update(double FrameTimeSeconds, TArray<FColor> FrameData);`
- L212 _public prototype_ `virtual void Initialize() = 0;`
- L213 _public prototype_ `virtual void Finalize() = 0;`
- L215 _public prototype_ `virtual void DropFrames(int32 NumFramesToDrop) = 0;`

#### Free symbols / members of external scopes

- L28 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogMovieCapture, Warning, All);`
- L28 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogMovieCapture, Warning, All);`
- L30 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(FString, FResolveFileFormat, const FString&, const FString&);`
- L30 _prototype_ `DECLARE_DELEGATE_RetVal_TwoParams(FString, FResolveFileFormat, const FString&, const FString&);`
