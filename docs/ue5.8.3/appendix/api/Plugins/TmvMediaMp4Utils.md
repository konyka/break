# Plugins / TmvMediaMp4Utils

- module root: `Plugins/Media/TmvMedia/Source/TmvMediaMp4Utils`
- headers: 5; symbols: 67
- symbol kinds: class=4, delegate=1, member=20, namespace=4, prototype=37, struct=1
- PrivateDependencyModuleNames: Core, MP4Boxes, MP4Muxer, MP4Utilities, TmvMedia

### `Plugins/Media/TmvMedia/Source/TmvMediaMp4Utils/Private/TmvMediaMp4Demuxer.h` (Private)


#### class `UE::TmvMedia::FTmvMediaMp4Demuxer`  
`class FTmvMediaMp4Demuxer : public ITmvMediaDemuxer`  
_L18-79_
- inherits: `ITmvMediaDemuxer`
- desc: MP4 container demuxer implementation. Wraps MP4Boxes/MP4Utilities for box tree parsing and sample iteration.
- L21 _public prototype_ `FTmvMediaMp4Demuxer() = default;`
- L25 _public prototype_ `virtual ETmvMediaContainerResult OpenFile(const FString& InFilePath) override;` — ITmvMediaDemuxer interface
- L26 _public prototype_ `virtual ETmvMediaContainerResult OpenBuffer(TConstArrayView<uint8> InData) override;`
- L27 _public prototype_ `virtual int32 GetTrackCount() const override;`
- L28 _public prototype_ `virtual ETmvMediaContainerResult GetTrackInfo(int32 InTrackIndex, FTmvMediaDemuxerTrackInfo& OutTrackInfo) const override;`
- L29 _public prototype_ `virtual ETmvMediaContainerResult ReadSample(int32 InTrackIndex, FTmvMediaDemuxerSample& OutSample) override;`
- L30 _public prototype_ `virtual ETmvMediaContainerResult ReadSampleInfo(int32 InTrackIndex, FTmvMediaDemuxerSample& OutSample) override;`
- L31 _public prototype_ `virtual ETmvMediaContainerResult Seek(int32 InTrackIndex, FTimespan InTime, FTimespan InLaterTimeThreshold) override;`
- L32 _public prototype_ `virtual ETmvMediaContainerResult SeekToSample(int32 InTrackIndex, uint32 InSampleNumber) override;`
- L33 _public prototype_ `virtual void Close() override;`
- L34 _public prototype_ `virtual FString GetLastError() const override;`
- L35 _public prototype_ `virtual TOptional<FString> GetStartTimecode() const override;`
- L36 _public prototype_ `virtual TOptional<FString> GetStartTimecodeRate() const override;`
- L40 _private prototype_ `ETmvMediaContainerResult ParseContainer();` — Parse the box tree from loaded root boxes and build tracks.
- L43 _private prototype_ `void ParseStartTimecode(const TSharedPtr<MP4Boxes::FMP4BoxBase, ESPMode::ThreadSafe>& InMoovTree);` — Extract start timecode from tmcd tracks or udta metadata.
- L46 _private prototype_ `ETmvMediaContainerResult PopulateSampleFromIterator( const TSharedPtr<MP4Boxes::FMP4Track::FIterator, ESPMode::ThreadSafe>& InIterator, FTmvMediaDemuxerSample& OutSample, bool bReadData);` — Populate an FTmvMediaDemuxerSample from the current iterator position. Optionally reads sample data.
- L60 _private member_ `TSharedPtr<MP4Utilities::IMP4DataReaderBase, ESPMode::ThreadSafe> DataReader;` — Data reader for file or buffer access.
- L63 _private member_ `TArray<TSharedPtr<MP4Utilities::FMP4BoxData, ESPMode::ThreadSafe>> RootBoxes;` — Parsed root boxes.
- L66 _private member_ `TArray<FTrackState> TrackStates;` — Track states.
- L69 _private member_ `MP4Utilities::FFractionalTime MovieDuration;` — Movie duration from mvhd.
- L72 _private member_ `TOptional<FString> StartTimecodeString;` — Parsed start timecode string (e.g., "01:00:00:00"), if available.
- L75 _private member_ `TOptional<FString> StartTimecodeRateString;` — Parsed start timecode frame rate string (e.g., "30000/1001"), if available.
- L78 _private member_ `FString LastError;` — Last error message.

#### struct `UE::TmvMedia::FTmvMediaMp4Demuxer::FTrackState`  
`struct FTrackState`  
_L52-57_
- desc: Per-track state.
- L54 _public member_ `TSharedPtr<MP4Boxes::FMP4Track, ESPMode::ThreadSafe> Track;`
- L55 _public member_ `TSharedPtr<MP4Boxes::FMP4Track::FIterator, ESPMode::ThreadSafe> Iterator;`
- L56 _public member_ `FTmvMediaDemuxerTrackInfo CachedInfo;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace TmvMedia` (scope `UE`)

### `Plugins/Media/TmvMedia/Source/TmvMediaMp4Utils/Private/TmvMediaMp4DemuxerFactory.h` (Private)


#### class `FTmvMediaMp4DemuxerFactory`  
`class FTmvMediaMp4DemuxerFactory : public ITmvMediaDemuxerFactory`  
_L7-17_
- inherits: `ITmvMediaDemuxerFactory`
- L10 _public prototype_ `virtual ~FTmvMediaMp4DemuxerFactory() override = default;`
- L13 _public prototype_ `virtual FName GetName() const override;` — ITmvMediaDemuxerFactory interface
- L14 _public prototype_ `virtual FText GetDisplayName() const override;`
- L15 _public prototype_ `virtual TArray<FString> GetSupportedContainerFormats() const override;`
- L16 _public prototype_ `virtual TSharedPtr<ITmvMediaDemuxer, ESPMode::ThreadSafe> CreateDemuxer() override;`

### `Plugins/Media/TmvMedia/Source/TmvMediaMp4Utils/Private/TmvMediaMp4Muxer.h` (Private)


#### class `UE::TmvMedia::FTmvMediaMp4Muxer`  
`class FTmvMediaMp4Muxer : public ITmvMediaMuxer, public TSharedFromThis<FTmvMediaMp4Muxer, ESPMode::ThreadSafe>`  
_L15-57_
- inherits: `ITmvMediaMuxer,TSharedFromThis<FTmvMediaMp4Muxer,ESPMode::ThreadSafe>`
- desc: MP4 container muxer implementation. Wraps IMP4RawMuxer from the MP4Muxer module.
- L18 _public prototype_ `FTmvMediaMp4Muxer() = default;`
- L22 _public prototype_ `virtual ETmvMediaContainerResult Configure(const FTmvMediaMuxerConfig& InConfig) override;` — ITmvMediaMuxer interface
- L23 _public prototype_ `virtual int32 AddTrack(const FTmvMediaMuxerTrackConfig& InTrackConfig) override;`
- L24 _public prototype_ `virtual bool SupportsStartTimecode() const override;`
- L25 _public prototype_ `virtual bool SetStartTimecode(const FTimecode& InTimecode, const FFrameRate& InFrameRate) override;`
- L26 _public prototype_ `virtual ETmvMediaContainerResult Start(FSampleRequestDelegate InSampleRequestDelegate, FStatusDelegate InStatusDelegate) override;`
- L27 _public prototype_ `virtual ETmvMediaContainerResult AddSample(int32 InTrackIndex, const FTmvMediaMuxerSample& InSample) override;`
- L28 _public prototype_ `virtual ETmvMediaContainerResult Finalize() override;`
- L29 _public prototype_ `virtual FString GetLastError() const override;`
- L33 _private member_ `TSharedPtr<IMP4RawMuxer, ESPMode::ThreadSafe> Mp4Muxer;` — The underlying MP4 raw muxer.
- L36 _private member_ `FString LastError;` — Last error message.
- L39 _private member_ `bool bStarted = false;` — Whether Start() has been called on the underlying muxer.
- L42 _private member_ `TArray<int32> VideoTrackIndices;` — Track indices of video tracks added by the caller (for timecode track references).
- L45 _private member_ `FTimecode StoredTimecode;` — Stored timecode set via SetTimecode().
- L46 _private member_ `FFrameRate StoredFrameRate;`
- L47 _private member_ `bool bHasTimecode = false;`
- L50 _private member_ `int32 InternalTimecodeTrackIndex = -1;` — Internal timecode track index, or -1 if not created.
- L53 _private member_ `TArray<uint8> TimecodeSampleData;` — Pre-built 4-byte big-endian timecode sample data.
- L56 _private member_ `bool bTimecodeSampleDelivered = false;` — Whether the single timecode sample has been delivered to the underlying muxer.

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace TmvMedia` (scope `UE`)

### `Plugins/Media/TmvMedia/Source/TmvMediaMp4Utils/Private/TmvMediaMp4MuxerFactory.h` (Private)


#### class `FTmvMediaMp4MuxerFactory`  
`class FTmvMediaMp4MuxerFactory : public ITmvMediaMuxerFactory`  
_L7-18_
- inherits: `ITmvMediaMuxerFactory`
- L10 _public prototype_ `virtual ~FTmvMediaMp4MuxerFactory() override = default;`
- L13 _public prototype_ `virtual FName GetName() const override;` — ITmvMediaMuxerFactory interface
- L14 _public prototype_ `virtual FText GetDisplayName() const override;`
- L15 _public prototype_ `virtual TArray<FString> GetSupportedContainerFormats() const override;`
- L16 _public prototype_ `virtual FString GetFileExtension() const override;`
- L17 _public prototype_ `virtual TSharedPtr<ITmvMediaMuxer, ESPMode::ThreadSafe> CreateMuxer() override;`

### `Plugins/Media/TmvMedia/Source/TmvMediaMp4Utils/Private/TmvMediaMp4UtilsLog.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogTmvMediaMp4Utils, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogTmvMediaMp4Utils, Log, All);`
