# Plugins / MP4Muxer

- module root: `Plugins/Media/MP4Utilities/Source/MP4Muxer`
- headers: 3; symbols: 545
- symbol kinds: class=51, delegate=5, enum=2, enumerator=5, function=168, macro=1, member=175, namespace=1, prototype=122, struct=14, typedef=1
- PrivateDependencyModuleNames: Core, MP4Utilities

### `Plugins/Media/MP4Utilities/Source/MP4Muxer/Private/MP4MuxerBoxes.h` (Private)


#### class `MP4MuxerBoxes::FBoxBuilderData`  
`class FBoxBuilderData`  
_L23-28_
- L26 _public prototype_ `FBoxBuilderData() = default;`
- L27 _public prototype_ `~FBoxBuilderData() = default;`

#### class `MP4MuxerBoxes::FBoxBase`  
`class FBoxBase`  
_L30-105_
- L33 _public function_ `FBoxBase(uint32 InType) : Type(InType)`
- L35 _public prototype_ `virtual ~FBoxBase();`
- L36 _public prototype_ `virtual void ClearBuiltBoxData();`
- L37 _public prototype_ `virtual bool BuildData(const FBoxBuilderData& InOutBuilderData);`
- L38 _public prototype_ `virtual void CalculateBoxSizes();`
- L39 _public function_ `void AddChild(FBoxBase* InChild)`
- L44 _public function_ `void AddChildAfter(FBoxBase* InChild, FBoxBase* InAfter)`
- L57 _public function_ `FBoxBase* GetParent() const`
- L59 _public function_ `void RemoveChild(FBoxBase* InChild)`
- L62 _public function_ `template <typename Predicate> bool VisitForWriting(Predicate Pred)`
- L77 _public function_ `int64 GetSize() const`
- L79 _public function_ `const TArray<uint8>& GetCompiledBoxData() const`
- L82 _public function_ `void SetAbsoluteFileOffset(int64 InAbsoluteFileOffset)` — Gets set while writing
- L84 _public function_ `int64 GetAbsoluteFileOffset() const`
- L87 _public prototype_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FRewriteBoxChangeDelegate, int64 , TConstArrayView<uint8> );`
- L88 _public function_ `virtual bool RewriteChanges(FRewriteBoxChangeDelegate InRewriteBoxChangeDelegate)`
- L92 _protected function_ `void SetType(uint32 InType)`
- L94 _protected function_ `void SetSize(uint32 InSize)`
- L96 _protected prototype_ `void AddSizeOfChildren();`
- L97 _protected member_ `uint32 Type = 0;`
- L98 _protected member_ `uint32 Size = 0;`
- L99 _protected member_ `FBoxBase* Parent = nullptr;`
- L100 _protected member_ `TArray<FBoxBase*> Children;`
- L101 _protected member_ `TArray<uint8> CompiledBoxData;`
- L102 _protected member_ `uint32 CompiledBoxData_Offset_Size = 0;`
- L103 _protected member_ `int64 AbsoluteFileOffset = -1;`
- L104 _protected member_ `bool bWasBuilt = false;`

#### class `MP4MuxerBoxes::FBoxFull`  
`class FBoxFull : public FBoxBase`  
_L107-119_
- inherits: `FBoxBase`
- L110 _public function_ `FBoxFull(uint32 InType) : FBoxBase(InType)`
- L112 _public prototype_ `virtual ~FBoxFull() = default;`
- L113 _public prototype_ `bool BuildData(const FBoxBuilderData& InOutBuilderData) override;`
- L114 _public function_ `void SetFlags(uint32 InFlags)`
- L117 _protected member_ `uint8 Version = 0;`
- L118 _protected member_ `uint32 Flags = 0;`

#### class `MP4MuxerBoxes::FBoxFTYP`  
`class FBoxFTYP : public FBoxBase`  
_L122-144_
- inherits: `FBoxBase`
- L125 _public function_ `FBoxFTYP() : FBoxBase(BoxAtom('f','t','y','p'))`
- L127 _public prototype_ `virtual ~FBoxFTYP() = default;`
- L129 _public function_ `void SetMajorBrand(uint32 InMajorBrand)`
- L131 _public function_ `void SetMinorVersion(uint32 InMinorVersion)`
- L133 _public function_ `void AddCompatibleBrand(uint32 InCompatibleBrand)`
- L136 _public prototype_ `bool BuildData(const FBoxBuilderData& InOutBuilderData) override;`
- L137 _public prototype_ `bool UpdateMajorBrand(uint32 InMajorBrand);`
- L138 _public prototype_ `bool RewriteChanges(FRewriteBoxChangeDelegate InRewriteBoxChangeDelegate) override;`
- L140 _protected member_ `uint32 MajorBrand = 0;`
- L141 _protected member_ `uint32 MinorVersion = 0;`
- L142 _protected member_ `TArray<uint32> CompatibleBrands;`
- L143 _protected member_ `int64 MajorBrandPatchOffset = -1;`

#### class `MP4MuxerBoxes::FBoxFREE`  
`class FBoxFREE : public FBoxBase`  
_L147-158_
- inherits: `FBoxBase`
- L150 _public function_ `FBoxFREE() : FBoxBase(BoxAtom('f','r','e','e'))`
- L152 _public prototype_ `virtual ~FBoxFREE() = default;`
- L153 _public function_ `void SetNumberOfEmptyBytes(uint32 InNumEmptyBytes)`
- L155 _public prototype_ `bool BuildData(const FBoxBuilderData& InOutBuilderData) override;`
- L157 _protected member_ `uint32 NumEmptyBytes = 0;`

#### class `MP4MuxerBoxes::FBoxMDAT`  
`class FBoxMDAT : public FBoxBase`  
_L161-168_
- inherits: `FBoxBase`
- L164 _public function_ `FBoxMDAT() : FBoxBase(BoxAtom('m','d','a','t'))`
- L166 _public prototype_ `virtual ~FBoxMDAT() = default;`

#### class `MP4MuxerBoxes::FBoxMOOV`  
`class FBoxMOOV : public FBoxBase`  
_L171-178_
- inherits: `FBoxBase`
- L174 _public function_ `FBoxMOOV() : FBoxBase(BoxAtom('m','o','o','v'))`
- L176 _public prototype_ `virtual ~FBoxMOOV() = default;`

#### class `MP4MuxerBoxes::FBoxMVHD`  
`class FBoxMVHD : public FBoxFull`  
_L181-215_
- inherits: `FBoxFull`
- L184 _public function_ `FBoxMVHD() : FBoxFull(BoxAtom('m','v','h','d'))`
- L186 _public prototype_ `virtual ~FBoxMVHD() = default;`
- L188 _public function_ `void SetCreationTime(uint64 InCreationTime)`
- L190 _public function_ `void SetModificationTime(uint64 InModificationTime)`
- L192 _public function_ `void SetTimescale(uint32 InTimescale)`
- L194 _public function_ `uint32 GetTimescale() const`
- L196 _public function_ `void SetDuration(uint64 InDuration)`
- L198 _public function_ `uint64 GetDuration() const`
- L200 _public function_ `void SetNextTrackID(uint32 InNextTrackID)`
- L203 _public prototype_ `bool BuildData(const FBoxBuilderData& InOutBuilderData) override;`
- L204 _public prototype_ `bool UpdateTimescale(uint32 InTimescale);`
- L205 _public prototype_ `bool UpdateDuration(uint64 InDuration);`
- L206 _public prototype_ `bool RewriteChanges(FRewriteBoxChangeDelegate InRewriteBoxChangeDelegate) override;`
- L208 _protected member_ `uint64 CreationTime = 0;`
- L209 _protected member_ `uint64 ModificationTime = 0;`
- L210 _protected member_ `uint64 Duration = 0;`
- L211 _protected member_ `uint32 Timescale = 0;`
- L212 _protected member_ `uint32 NextTrackID = 0;`
- L213 _protected member_ `int64 TimescalePatchOffset = -1;`
- L214 _protected member_ `int64 DurationPatchOffset = -1;`

#### class `MP4MuxerBoxes::FBoxTRAK`  
`class FBoxTRAK : public FBoxBase`  
_L218-225_
- inherits: `FBoxBase`
- L221 _public function_ `FBoxTRAK() : FBoxBase(BoxAtom('t','r','a','k'))`
- L223 _public prototype_ `virtual ~FBoxTRAK() = default;`

#### class `MP4MuxerBoxes::FBoxTKHD`  
`class FBoxTKHD : public FBoxFull`  
_L228-287_
- inherits: `FBoxFull`
- L231 _public function_ `FBoxTKHD() : FBoxFull(BoxAtom('t','k','h','d'))`
- L233 _public prototype_ `virtual ~FBoxTKHD() = default;`
- L235 _public function_ `void SetCreationTime(uint64 InCreationTime)`
- L237 _public function_ `void SetModificationTime(uint64 InModificationTime)`
- L239 _public function_ `void SetDuration(uint64 InDuration)`
- L241 _public function_ `void SetTrackID(uint32 InTrackID)`
- L243 _public function_ `void SetTrackEnabled(bool bIsEnabled)`
- L245 _public function_ `void SetTrackInMovie(bool bIsInMovie)`
- L247 _public function_ `void SetTrackInPreview(bool bIsInPreview)`
- L249 _public function_ `void SetWidth(uint32 InWidth)`
- L251 _public function_ `void SetHeight(uint32 InHeight)`
- L253 _public function_ `void SetVolume(uint8 InVolume)`
- L255 _public function_ `void SetWidthRaw(uint32 InWidth)`
- L257 _public function_ `void SetHeightRaw(uint32 InHeight)`
- L259 _public function_ `void SetVolumeRaw(int16 InVolume)`
- L261 _public function_ `void SetLayer(uint16 InLayer)`
- L263 _public function_ `void SetAlternateGroup(uint16 InAlternateGroup)`
- L265 _public function_ `void SetMatrix(const int32 InMatrix[9])`
- L267 _public function_ `void SetCustomFlags(uint32 InFlags)`
- L270 _public prototype_ `bool BuildData(const FBoxBuilderData& InOutBuilderData) override;`
- L272 _public prototype_ `bool UpdateDuration(uint64 InDuration);`
- L273 _public prototype_ `bool RewriteChanges(FRewriteBoxChangeDelegate InRewriteBoxChangeDelegate) override;`
- L275 _protected member_ `int32 Matrix[9] { 0x00010000,0,0,0,0x00010000,0,0,0,0x40000000 };`
- L276 _protected member_ `uint64 CreationTime = 0;`
- L277 _protected member_ `uint64 ModificationTime = 0;`
- L278 _protected member_ `uint64 Duration = 0;`
- L279 _protected member_ `uint32 CustomFlags = 0;`
- L280 _protected member_ `uint32 TrackID = 0;`
- L281 _protected member_ `uint32 Width = 0;`
- L282 _protected member_ `uint32 Height = 0;`
- L283 _protected member_ `uint16 Volume = 0;`
- L284 _protected member_ `uint16 Layer = 0;`
- L285 _protected member_ `uint16 AlternateGroup = 0;`
- L286 _protected member_ `int64 DurationPatchOffset = -1;`

#### class `MP4MuxerBoxes::FBoxMDIA`  
`class FBoxMDIA : public FBoxBase`  
_L290-297_
- inherits: `FBoxBase`
- L293 _public function_ `FBoxMDIA() : FBoxBase(BoxAtom('m','d','i','a'))`
- L295 _public prototype_ `virtual ~FBoxMDIA() = default;`

#### class `MP4MuxerBoxes::FBoxMDHD`  
`class FBoxMDHD : public FBoxFull`  
_L300-333_
- inherits: `FBoxFull`
- L303 _public function_ `FBoxMDHD() : FBoxFull(BoxAtom('m','d','h','d'))`
- L305 _public prototype_ `virtual ~FBoxMDHD() = default;`
- L307 _public function_ `void SetCreationTime(uint64 InCreationTime)`
- L309 _public function_ `void SetModificationTime(uint64 InModificationTime)`
- L311 _public function_ `void SetDuration(uint64 InDuration)`
- L313 _public function_ `void SetTimescale(uint32 InTimescale)`
- L315 _public function_ `void SetLanguage(uint8 In1, uint8 In2, uint8 In3)`
- L323 _public prototype_ `bool BuildData(const FBoxBuilderData& InOutBuilderData) override;`
- L324 _public prototype_ `bool UpdateDuration(uint64 InDuration);`
- L325 _public prototype_ `bool RewriteChanges(FRewriteBoxChangeDelegate InRewriteBoxChangeDelegate) override;`
- L327 _protected member_ `uint64 CreationTime = 0;`
- L328 _protected member_ `uint64 ModificationTime = 0;`
- L329 _protected member_ `uint64 Duration = 0;`
- L330 _protected member_ `uint32 Timescale = 0;`
- L331 _protected member_ `uint8 LanguageCode[3] {};`
- L332 _protected member_ `int64 DurationPatchOffset = -1;`

#### class `MP4MuxerBoxes::FBoxHDLR`  
`class FBoxHDLR : public FBoxFull`  
_L336-352_
- inherits: `FBoxFull`
- L339 _public function_ `FBoxHDLR() : FBoxFull(BoxAtom('h','d','l','r'))`
- L341 _public prototype_ `virtual ~FBoxHDLR() = default;`
- L343 _public function_ `void SetHandlerType(uint32 InHandlerType)`
- L345 _public function_ `void SetName(const FString& InName)`
- L348 _public prototype_ `bool BuildData(const FBoxBuilderData& InOutBuilderData) override;`
- L350 _protected member_ `FString Name;`
- L351 _protected member_ `uint32 HandlerType = 0;`

#### class `MP4MuxerBoxes::FBoxMINF`  
`class FBoxMINF : public FBoxBase`  
_L355-362_
- inherits: `FBoxBase`
- L358 _public function_ `FBoxMINF() : FBoxBase(BoxAtom('m','i','n','f'))`
- L360 _public prototype_ `virtual ~FBoxMINF() = default;`

#### class `MP4MuxerBoxes::FBoxVMHD`  
`class FBoxVMHD : public FBoxFull`  
_L365-376_
- inherits: `FBoxFull`
- L368 _public function_ `FBoxVMHD() : FBoxFull(BoxAtom('v','m','h','d'))`
- L370 _public prototype_ `virtual ~FBoxVMHD() = default;`
- L372 _public prototype_ `bool BuildData(const FBoxBuilderData& InOutBuilderData) override;`
- L374 _protected member_ `uint16 GraphicsMode = 0;`
- L375 _protected member_ `uint16 OpColor[3] { };`

#### class `MP4MuxerBoxes::FBoxSMHD`  
`class FBoxSMHD : public FBoxFull`  
_L379-389_
- inherits: `FBoxFull`
- L382 _public function_ `FBoxSMHD() : FBoxFull(BoxAtom('s','m','h','d'))`
- L384 _public prototype_ `virtual ~FBoxSMHD() = default;`
- L386 _public prototype_ `bool BuildData(const FBoxBuilderData& InOutBuilderData) override;`
- L388 _protected member_ `uint16 Balance = 0;`

#### class `MP4MuxerBoxes::FBoxNMHD`  
`class FBoxNMHD : public FBoxFull`  
_L392-399_
- inherits: `FBoxFull`
- L395 _public function_ `FBoxNMHD() : FBoxFull(BoxAtom('n','m','h','d'))`
- L397 _public prototype_ `virtual ~FBoxNMHD() = default;`

#### class `MP4MuxerBoxes::FBoxDINF`  
`class FBoxDINF : public FBoxBase`  
_L402-409_
- inherits: `FBoxBase`
- L405 _public function_ `FBoxDINF() : FBoxBase(BoxAtom('d','i','n','f'))`
- L407 _public prototype_ `virtual ~FBoxDINF() = default;`

#### class `MP4MuxerBoxes::FBoxDREF`  
`class FBoxDREF : public FBoxFull`  
_L412-420_
- inherits: `FBoxFull`
- L415 _public function_ `FBoxDREF() : FBoxFull(BoxAtom('d','r','e','f'))`
- L417 _public prototype_ `virtual ~FBoxDREF() = default;`
- L418 _public prototype_ `bool BuildData(const FBoxBuilderData& InOutBuilderData) override;`

#### class `MP4MuxerBoxes::FBoxURL`  
`class FBoxURL : public FBoxFull`  
_L423-431_
- inherits: `FBoxFull`
- L426 _public function_ `FBoxURL() : FBoxFull(BoxAtom('u','r','l',' '))`
- L428 _public prototype_ `virtual ~FBoxURL() = default;`
- L429 _public prototype_ `bool BuildData(const FBoxBuilderData& InOutBuilderData) override;`

#### class `MP4MuxerBoxes::FBoxSTBL`  
`class FBoxSTBL : public FBoxBase`  
_L434-441_
- inherits: `FBoxBase`
- L437 _public function_ `FBoxSTBL() : FBoxBase(BoxAtom('s','t','b','l'))`
- L439 _public prototype_ `virtual ~FBoxSTBL() = default;`

#### class `MP4MuxerBoxes::FBoxSampleEntry`  
`class FBoxSampleEntry : public FBoxBase`  
_L444-457_
- inherits: `FBoxBase`
- L447 _public function_ `FBoxSampleEntry(uint32 InFormat) : FBoxBase(InFormat)`
- L449 _public prototype_ `virtual ~FBoxSampleEntry() = default;`
- L450 _public function_ `void SetAdditionalBoxes(const TArray<TArray<uint8>>& InAdditionalBoxes)`
- L452 _public prototype_ `bool BuildData(const FBoxBuilderData& InOutBuilderData) override;`
- L454 _protected prototype_ `bool AppendAdditionalBoxes();`
- L455 _protected member_ `TArray<TArray<uint8>> AdditionalBoxes;`
- L456 _protected member_ `uint16 DataReferenceIndex = 1;`

#### class `MP4MuxerBoxes::FBoxVisualSampleEntry`  
`class FBoxVisualSampleEntry : public FBoxSampleEntry`  
_L460-477_
- inherits: `FBoxSampleEntry`
- L463 _public function_ `FBoxVisualSampleEntry(uint32 InFormat) : FBoxSampleEntry(InFormat)`
- L465 _public prototype_ `virtual ~FBoxVisualSampleEntry() = default;`
- L466 _public function_ `void SetWidth(uint16 InWidth)`
- L468 _public function_ `void SetHeight(uint16 InHeight)`
- L470 _public function_ `void SetCompressorName(const FString& InCompressorName)`
- L472 _public prototype_ `bool BuildData(const FBoxBuilderData& InOutBuilderData) override;`
- L474 _protected member_ `FString CompressorName;`
- L475 _protected member_ `uint16 Width = 0;`
- L476 _protected member_ `uint16 Height = 0;`

#### class `MP4MuxerBoxes::FBoxAudioSampleEntry`  
`class FBoxAudioSampleEntry : public FBoxSampleEntry`  
_L480-494_
- inherits: `FBoxSampleEntry`
- L483 _public function_ `FBoxAudioSampleEntry(uint32 InFormat) : FBoxSampleEntry(InFormat)`
- L485 _public prototype_ `virtual ~FBoxAudioSampleEntry() = default;`
- L486 _public function_ `void SetChannelCount(uint16 InChannelCount)`
- L488 _public function_ `bool SetSampleRate(uint32 InSampleRate)`
- L490 _public prototype_ `bool BuildData(const FBoxBuilderData& InOutBuilderData) override;`
- L492 _protected member_ `uint32 SampleRate = 0;`
- L493 _protected member_ `uint16 ChannelCount = 0;`

#### class `MP4MuxerBoxes::FBoxTimecodeSampleEntry`  
`class FBoxTimecodeSampleEntry : public FBoxSampleEntry`  
_L497-527_
- inherits: `FBoxSampleEntry`
- L500 _public function_ `FBoxTimecodeSampleEntry(uint32 InFormat) : FBoxSampleEntry(InFormat)`
- L502 _public prototype_ `virtual ~FBoxTimecodeSampleEntry() = default;`
- L504 _public function_ `void SetTimescale(int32 InTimescale)`
- L506 _public function_ `void SetFrameDuration(int32 InFrameDuration)`
- L508 _public function_ `void SetFramesPerSecond(int8 InFramesPerSecond)`
- L510 _public function_ `void SetDropFrame(bool bInDropFrame)`
- L512 _public function_ `void SetMax24Hours(bool bInMax24h)`
- L514 _public function_ `void SetAllowNegativeTimes(bool bInAllowNegativeTimes)`
- L517 _public prototype_ `bool BuildData(const FBoxBuilderData& InOutBuilderData) override;`
- L520 _protected member_ `int32 Timescale = 0;` — These values are defined to be signed integers!
- L521 _protected member_ `int32 FrameDuration = 0;`
- L522 _protected member_ `int8 FramesPerSecond = 0;`
- L524 _protected member_ `bool bDropFrame = false;`
- L525 _protected member_ `bool bMax24Hours = false;`
- L526 _protected member_ `bool bAllowNegativeTimes = false;`

#### class `MP4MuxerBoxes::FBoxSTSD`  
`class FBoxSTSD : public FBoxFull`  
_L530-540_
- inherits: `FBoxFull`
- L533 _public function_ `FBoxSTSD() : FBoxFull(BoxAtom('s','t','s','d'))`
- L535 _public prototype_ `virtual ~FBoxSTSD() = default;`
- L536 _public function_ `void SetVersion(uint8 InVersion)`
- L538 _public prototype_ `bool BuildData(const FBoxBuilderData& InOutBuilderData) override;`

#### class `MP4MuxerBoxes::FBoxSTTS`  
`class FBoxSTTS : public FBoxFull`  
_L543-572_
- inherits: `FBoxFull`
- L546 _public function_ `FBoxSTTS() : FBoxFull(BoxAtom('s','t','t','s'))`
- L548 _public prototype_ `virtual ~FBoxSTTS() = default;`
- L549 _public function_ `void AddSampleDuration(uint32 InSampleDuration)`
- L564 _public prototype_ `bool BuildData(const FBoxBuilderData& InOutBuilderData) override;`
- L571 _protected member_ `TChunkedArray<FEntry, 64> SampleDurations;`

#### struct `MP4MuxerBoxes::FBoxSTTS::FEntry`  
`struct FEntry`  
_L566-570_
- L568 _public member_ `uint32 Count;`
- L569 _public member_ `uint32 Delta;`

#### class `MP4MuxerBoxes::FBoxSTSS`  
`class FBoxSTSS : public FBoxFull`  
_L575-586_
- inherits: `FBoxFull`
- L578 _public function_ `FBoxSTSS() : FBoxFull(BoxAtom('s','t','s','s'))`
- L580 _public prototype_ `virtual ~FBoxSTSS() = default;`
- L581 _public function_ `void AddSampleIndex(uint32 InSampleNumber)`
- L583 _public prototype_ `bool BuildData(const FBoxBuilderData& InOutBuilderData) override;`
- L585 _protected member_ `TChunkedArray<uint32, 240> SyncSampleIndices;`

#### class `MP4MuxerBoxes::FBoxCTTS`  
`class FBoxCTTS : public FBoxFull`  
_L589-626_
- inherits: `FBoxFull`
- L592 _public function_ `FBoxCTTS() : FBoxFull(BoxAtom('c','t','t','s'))`
- L594 _public prototype_ `virtual ~FBoxCTTS() = default;`
- L595 _public function_ `void AddSampleCompositionOffset(int32 InCompositionTimeOffset)`
- L613 _public function_ `bool HaveCompositionOffsets() const`
- L615 _public function_ `bool HasNegativeCompositionOffsets() const`
- L617 _public prototype_ `bool BuildData(const FBoxBuilderData& InOutBuilderData) override;`
- L624 _protected member_ `TChunkedArray<FEntry, 64> CompositionTimeOffsets;`
- L625 _protected member_ `bool bHasNegativeEntries = false;`

#### struct `MP4MuxerBoxes::FBoxCTTS::FEntry`  
`struct FEntry`  
_L619-623_
- L621 _public member_ `uint32 Count;`
- L622 _public member_ `int32 Delta;`

#### class `MP4MuxerBoxes::FBoxSTSC`  
`class FBoxSTSC : public FBoxFull`  
_L629-657_
- inherits: `FBoxFull`
- L632 _public function_ `FBoxSTSC() : FBoxFull(BoxAtom('s','t','s','c'))`
- L634 _public prototype_ `virtual ~FBoxSTSC() = default;`
- L635 _public function_ `void AddEntry(uint32 InFirstChunk, uint32 InSamplesPerChunk, uint32 InSampleDescriptionIndex)`
- L648 _public prototype_ `bool BuildData(const FBoxBuilderData& InOutBuilderData) override;`
- L656 _protected member_ `TChunkedArray<FEntry, 32> SampleToChunkEntries;`

#### struct `MP4MuxerBoxes::FBoxSTSC::FEntry`  
`struct FEntry`  
_L650-655_
- L652 _public member_ `uint32 first_chunk = 0;`
- L653 _public member_ `uint32 samples_per_chunk = 0;`
- L654 _public member_ `uint32 sample_description_index = 0;`

#### class `MP4MuxerBoxes::FBoxSTSZ`  
`class FBoxSTSZ : public FBoxFull`  
_L660-683_
- inherits: `FBoxFull`
- L663 _public function_ `FBoxSTSZ() : FBoxFull(BoxAtom('s','t','s','z'))`
- L665 _public prototype_ `virtual ~FBoxSTSZ() = default;`
- L666 _public function_ `void SetConstantSampleSize(uint32 InConstantSampleSize)`
- L668 _public function_ `void AddSampleSize(uint32 InSampleSize)`
- L674 _public function_ `uint32 GetNumberOfSamples() const`
- L676 _public prototype_ `bool BuildData(const FBoxBuilderData& InOutBuilderData) override;`
- L678 _protected member_ `TChunkedArray<uint32, 240> SampleSizes;`
- L679 _protected member_ `uint32 ConstantSampleSize = 0;`
- L680 _protected member_ `uint32 LargestSampleSize = 0;`
- L681 _protected member_ `bool bHasVaryingSizes = false;`
- L682 _protected member_ `bool bUseSmallSizeBox = false;`

#### class `MP4MuxerBoxes::FBoxSTCO`  
`class FBoxSTCO : public FBoxFull`  
_L686-713_
- inherits: `FBoxFull`
- L689 _public function_ `FBoxSTCO() : FBoxFull(BoxAtom('s','t','c','o'))`
- L691 _public prototype_ `virtual ~FBoxSTCO() = default;`
- L692 _public function_ `void AddChunkOffset(int64 InChunkOffset)`
- L700 _public function_ `uint32 GetNumberOfChunkOffsets() const`
- L702 _public function_ `const TChunkedArray<int64, 32>& GetChunkOffsets() const`
- L704 _public function_ `bool Needs64Bits() const`
- L706 _public function_ `void Force64Bits()`
- L708 _public prototype_ `bool AddFileOffset(int64 InOffsetToAdd);`
- L709 _public prototype_ `bool BuildData(const FBoxBuilderData& InOutBuilderData) override;`
- L711 _protected member_ `TChunkedArray<int64, 32> ChunkOffsets;`
- L712 _protected member_ `bool bNeeds64Bits = false;`

#### class `MP4MuxerBoxes::FBoxMVEX`  
`class FBoxMVEX : public FBoxBase`  
_L716-723_
- inherits: `FBoxBase`
- L719 _public function_ `FBoxMVEX() : FBoxBase(BoxAtom('m','v','e','x'))`
- L721 _public prototype_ `virtual ~FBoxMVEX() = default;`

#### class `MP4MuxerBoxes::FBoxMEHD`  
`class FBoxMEHD : public FBoxFull`  
_L726-740_
- inherits: `FBoxFull`
- L729 _public function_ `FBoxMEHD() : FBoxFull(BoxAtom('m','e','h','d'))`
- L731 _public prototype_ `virtual ~FBoxMEHD() = default;`
- L732 _public function_ `void SetFragmentDuration(uint64 InFragmentDuration)`
- L734 _public prototype_ `bool BuildData(const FBoxBuilderData& InOutBuilderData) override;`
- L735 _public prototype_ `bool UpdateFragmentDuration(uint64 InFragmentDuration);`
- L736 _public prototype_ `bool RewriteChanges(FRewriteBoxChangeDelegate InRewriteBoxChangeDelegate) override;`
- L738 _protected member_ `uint64 FragmentDuration = 0;`
- L739 _protected member_ `int64 FragmentDurationPatchOffset = -1;`

#### class `MP4MuxerBoxes::FBoxTREX`  
`class FBoxTREX : public FBoxFull`  
_L743-766_
- inherits: `FBoxFull`
- L746 _public function_ `FBoxTREX() : FBoxFull(BoxAtom('t','r','e','x'))`
- L748 _public prototype_ `virtual ~FBoxTREX() = default;`
- L749 _public function_ `void SetTrackID(uint32 InTrackID)`
- L751 _public function_ `void SetDefaultSampleDuration(uint32 InDefaultSampleDuration)`
- L753 _public function_ `void SetDefaultSampleSize(uint32 InDefaultSampleSize)`
- L755 _public function_ `void SetDefaultSampleFlags(uint32 InDefaultSampleFlags)`
- L757 _public function_ `uint32 GetDefaultSampleFlags() const`
- L759 _public prototype_ `bool BuildData(const FBoxBuilderData& InOutBuilderData) override;`
- L761 _protected member_ `uint32 TrackID = 0;`
- L762 _protected member_ `uint32 default_sample_description_index = 1;`
- L763 _protected member_ `uint32 default_sample_duration = 0;`
- L764 _protected member_ `uint32 default_sample_size = 0;`
- L765 _protected member_ `uint32 default_sample_flags = 0;`

#### class `MP4MuxerBoxes::FBoxMOOF`  
`class FBoxMOOF : public FBoxBase`  
_L769-776_
- inherits: `FBoxBase`
- L772 _public function_ `FBoxMOOF() : FBoxBase(BoxAtom('m','o','o','f'))`
- L774 _public prototype_ `virtual ~FBoxMOOF() = default;`

#### class `MP4MuxerBoxes::FBoxMFHD`  
`class FBoxMFHD : public FBoxFull`  
_L779-790_
- inherits: `FBoxFull`
- L782 _public function_ `FBoxMFHD() : FBoxFull(BoxAtom('m','f','h','d'))`
- L784 _public prototype_ `virtual ~FBoxMFHD() = default;`
- L785 _public function_ `void SetSequenceNumber(uint32 InSequenceNumber)`
- L787 _public prototype_ `bool BuildData(const FBoxBuilderData& InOutBuilderData) override;`
- L789 _protected member_ `uint32 SequenceNumber = 0;`

#### class `MP4MuxerBoxes::FBoxTRAF`  
`class FBoxTRAF : public FBoxBase`  
_L793-800_
- inherits: `FBoxBase`
- L796 _public function_ `FBoxTRAF() : FBoxBase(BoxAtom('t','r','a','f'))`
- L798 _public prototype_ `virtual ~FBoxTRAF() = default;`

#### class `MP4MuxerBoxes::FBoxTFHD`  
`class FBoxTFHD : public FBoxFull`  
_L803-838_
- inherits: `FBoxFull`
- L806 _public function_ `FBoxTFHD() : FBoxFull(BoxAtom('t','f','h','d'))`
- L808 _public prototype_ `virtual ~FBoxTFHD() = default;`
- L809 _public function_ `void SetTrackID(uint32 InTrackID)`
- L811 _public function_ `void SetDefaultBaseIsMoof(bool bInDefaultBaseIsMoof)`
- L813 _public function_ `void SetBaseDataOffset(uint64 InBaseDataOffset)`
- L815 _public function_ `void SetSampleDescriptionIndex(uint32 InSampleDescriptionIndex)`
- L817 _public function_ `void SetDefaultSampleDuration(uint32 InDefaultSampleDuration)`
- L819 _public function_ `void SetDefaultSampleSize(uint32 InDefaultSampleSize)`
- L821 _public function_ `void SetDefaultSampleFlags(uint32 InDefaultSampleFlags)`
- L823 _public function_ `TOptional<uint32> GetDefaultSampleFlags() const`
- L826 _public prototype_ `bool BuildData(const FBoxBuilderData& InOutBuilderData) override;`
- L827 _public prototype_ `bool UpdateBaseDataOffset(uint64 InBaseDataOffset);`
- L828 _public prototype_ `bool RewriteChanges(FRewriteBoxChangeDelegate InRewriteBoxChangeDelegate) override;`
- L830 _protected member_ `uint32 TrackID = 0;`
- L831 _protected member_ `bool bDefaultBaseIsMoof = false;`
- L832 _protected member_ `TOptional<uint64> base_data_offset;`
- L833 _protected member_ `TOptional<uint32> sample_description_index;`
- L834 _protected member_ `TOptional<uint32> default_sample_duration;`
- L835 _protected member_ `TOptional<uint32> default_sample_size;`
- L836 _protected member_ `TOptional<uint32> default_sample_flags;`
- L837 _protected member_ `int64 BaseDataPatchOffset = -1;`

#### class `MP4MuxerBoxes::FBoxTFDT`  
`class FBoxTFDT : public FBoxFull`  
_L841-854_
- inherits: `FBoxFull`
- L844 _public function_ `FBoxTFDT() : FBoxFull(BoxAtom('t','f','d','t'))`
- L846 _public prototype_ `virtual ~FBoxTFDT() = default;`
- L848 _public function_ `void SetBaseMediaDecodeTime(uint64 InBaseMediaDecodeTime)`
- L851 _public prototype_ `bool BuildData(const FBoxBuilderData& InOutBuilderData) override;`
- L853 _protected member_ `uint64 BaseMediaDecodeTime = 0;`

#### class `MP4MuxerBoxes::FBoxTRUN`  
`class FBoxTRUN : public FBoxFull`  
_L857-942_
- inherits: `FBoxFull`
- L860 _public function_ `FBoxTRUN() : FBoxFull(BoxAtom('t','r','u','n'))`
- L862 _public prototype_ `virtual ~FBoxTRUN() = default;`
- L864 _public function_ `void SetDataOffset(int32 InDataOffset)`
- L868 _public function_ `void SetDefaultSampleFlagsForTesting(uint32 InDefaultSampleFlags)` — Set default flags as they appear in the `trex` or `tfhd` box. The `trun` has no default flags and we use this value only as a convenience for testing.
- L870 _public function_ `void SetFirstSampleFlags(uint32 InFirstSampleFlags)`
- L872 _public function_ `void AddSample(uint32 InSampleDuration, uint32 InSampleSize, uint32 InSampleFlags, int32 InSampleCompositionTimeOffset)`
- L901 _public function_ `uint32 GetFirstSampleFlagsOrDefault() const`
- L903 _public function_ `uint32 GetSubsequentSampleFlagsOrDefault() const`
- L905 _public function_ `bool AreFlagsAfterFirstSampleDifferent() const`
- L908 _public function_ `bool RequiresCompositionTimeOffsets() const`
- L910 _public function_ `bool HasDifferentSizes() const`
- L912 _public function_ `bool HasDifferentDurations() const`
- L914 _public function_ `void DoNotWriteDurations()`
- L916 _public function_ `void DoNotWriteSizes()`
- L918 _public function_ `void DoNotWriteFlags()`
- L921 _public prototype_ `bool BuildData(const FBoxBuilderData& InOutBuilderData) override;`
- L930 _protected member_ `TChunkedArray<FEntry, 64> Samples;`
- L931 _protected member_ `TOptional<int32> DataOffset;`
- L932 _protected member_ `TOptional<uint32> first_sample_flags;`
- L933 _protected member_ `uint32 DefaultSampleFlags = 0;`
- L934 _protected member_ `bool bRequiresCompositionTimeOffsets = false;`
- L935 _protected member_ `bool bHasDifferentSizes = false;`
- L936 _protected member_ `bool bHasDifferentDurations = false;`
- L937 _protected member_ `bool bFlagsAfterFirstAreDifferent = false;`
- L938 _protected member_ `bool bDoNotWriteDurations = false;`
- L939 _protected member_ `bool bDoNotWriteSizes = false;`
- L940 _protected member_ `bool bDoNotWriteFlags = false;`
- L941 _protected member_ `int64 DataOffsetPatchOffset = -1;`

#### struct `MP4MuxerBoxes::FBoxTRUN::FEntry`  
`struct FEntry`  
_L923-929_
- L925 _public member_ `uint32 sample_duration = 0;`
- L926 _public member_ `uint32 sample_size = 0;`
- L927 _public member_ `uint32 sample_flags = 0;`
- L928 _public member_ `int32 sample_composition_time_offset = 0;`

#### class `MP4MuxerBoxes::FBoxSUBS`  
`class FBoxSUBS : public FBoxFull`  
_L945-972_
- inherits: `FBoxFull`
- L948 _public function_ `FBoxSUBS() : FBoxFull(BoxAtom('s','u','b','s'))`
- L950 _public prototype_ `virtual ~FBoxSUBS() = default;`
- L952 _public typedef_ `using FSubSampleInfo = IMP4RawMuxer::FTrackSample::FSubSampleInfo;`
- L954 _public function_ `void AddSubsamplesForSample(uint32 InSampleNumber, const TArray<FSubSampleInfo>& InSubsampleInfo)`
- L964 _public prototype_ `bool BuildData(const FBoxBuilderData& InOutBuilderData) override;`
- L971 _protected member_ `TChunkedArray<FSSI, 32> SubSamples;`

#### struct `MP4MuxerBoxes::FBoxSUBS::FSSI`  
`struct FSSI`  
_L966-970_
- L968 _public member_ `uint32 SampleNumber = 0;`
- L969 _public member_ `TArray<FSubSampleInfo> Subs;`

#### class `MP4MuxerBoxes::FBoxEDTS`  
`class FBoxEDTS : public FBoxBase`  
_L975-982_
- inherits: `FBoxBase`
- L978 _public function_ `FBoxEDTS() : FBoxBase(BoxAtom('e','d','t','s'))`
- L980 _public prototype_ `virtual ~FBoxEDTS() = default;`

#### class `MP4MuxerBoxes::FBoxELST`  
`class FBoxELST : public FBoxFull`  
_L985-1002_
- inherits: `FBoxFull`
- L988 _public function_ `FBoxELST() : FBoxFull(BoxAtom('e','l','s','t'))`
- L990 _public prototype_ `virtual ~FBoxELST() = default;`
- L991 _public function_ `void SetEditDuration(uint64 InEditDuration)`
- L993 _public function_ `void SetMediaTime(int64 InMediaTime)`
- L995 _public prototype_ `bool UpdateEditDuration(uint64 InEditDuration);`
- L996 _public prototype_ `bool RewriteChanges(FRewriteBoxChangeDelegate InRewriteBoxChangeDelegate) override;`
- L997 _public prototype_ `bool BuildData(const FBoxBuilderData& InOutBuilderData) override;`
- L999 _protected member_ `uint64 EditDuration = 0;`
- L1000 _protected member_ `int64 MediaTime = 0;`
- L1001 _protected member_ `int64 EditDurationPatchOffset = -1;`

#### class `MP4MuxerBoxes::FBoxUDTA`  
`class FBoxUDTA : public FBoxBase`  
_L1005-1012_
- inherits: `FBoxBase`
- L1008 _public function_ `FBoxUDTA() : FBoxBase(BoxAtom('u','d','t','a'))`
- L1010 _public prototype_ `virtual ~FBoxUDTA() = default;`

#### class `MP4MuxerBoxes::FBoxNAMEbase`  
`class FBoxNAMEbase : public FBoxBase`  
_L1015-1028_
- inherits: `FBoxBase`
- L1018 _public function_ `FBoxNAMEbase() : FBoxBase(BoxAtom('n','a','m','e'))`
- L1020 _public prototype_ `virtual ~FBoxNAMEbase() = default;`
- L1022 _public function_ `void SetName(const FString& InName)`
- L1025 _public prototype_ `bool BuildData(const FBoxBuilderData& InOutBuilderData) override;`
- L1027 _protected member_ `FString Name;`

#### class `MP4MuxerBoxes::FBoxNAME`  
`class FBoxNAME : public FBoxFull`  
_L1030-1043_
- inherits: `FBoxFull`
- L1033 _public function_ `FBoxNAME() : FBoxFull(BoxAtom('n','a','m','e'))`
- L1035 _public prototype_ `virtual ~FBoxNAME() = default;`
- L1037 _public function_ `void SetName(const FString& InName)`
- L1040 _public prototype_ `bool BuildData(const FBoxBuilderData& InOutBuilderData) override;`
- L1042 _protected member_ `FString Name;`

#### class `MP4MuxerBoxes::FBoxTREF`  
`class FBoxTREF : public FBoxBase`  
_L1046-1053_
- inherits: `FBoxBase`
- L1049 _public function_ `FBoxTREF() : FBoxBase(BoxAtom('t','r','e','f'))`
- L1051 _public prototype_ `virtual ~FBoxTREF() = default;`

#### class `MP4MuxerBoxes::FBoxTREFType`  
`class FBoxTREFType : public FBoxBase`  
_L1055-1070_
- inherits: `FBoxBase`
- L1058 _public function_ `FBoxTREFType() : FBoxBase(0)`
- L1060 _public prototype_ `virtual ~FBoxTREFType() = default;`
- L1062 _public function_ `void SetReferenceType(uint32 InReferenceType)`
- L1064 _public function_ `void AddReferencedTrackNumber(uint32 InReferencedTrackNumber)`
- L1066 _public prototype_ `bool BuildData(const FBoxBuilderData& InOutBuilderData) override;`
- L1068 _protected member_ `uint32 ReferenceType = 0;`
- L1069 _protected member_ `TArray<uint32> ReferencedTrackNumbers;`

#### class `MP4MuxerBoxes::FBoxOpaqueData`  
`class FBoxOpaqueData : public FBoxBase`  
_L1073-1085_
- inherits: `FBoxBase`
- L1076 _public function_ `FBoxOpaqueData(uint32 InType) : FBoxBase(InType)`
- L1078 _public prototype_ `virtual ~FBoxOpaqueData() = default;`
- L1080 _public function_ `void SetRawBoxData(TConstArrayView<uint8> InRawBoxData)`
- L1082 _public prototype_ `bool BuildData(const FBoxBuilderData& InOutBuilderData) override;`
- L1084 _protected member_ `TArray<uint8> RawBoxData;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace MP4MuxerBoxes`
- L12 _function_ `static constexpr uint16 EndianSwap(uint16 value)` (scope `MP4MuxerBoxes`)
- L13 _function_ `static constexpr int16 EndianSwap(int16 value)` (scope `MP4MuxerBoxes`)
- L14 _function_ `static constexpr uint32 EndianSwap(uint32 value)` (scope `MP4MuxerBoxes`)
- L15 _function_ `static constexpr int32 EndianSwap(int32 value)` (scope `MP4MuxerBoxes`)
- L16 _function_ `static constexpr uint64 EndianSwap(uint64 value)` (scope `MP4MuxerBoxes`)
- L17 _function_ `static constexpr int64 EndianSwap(int64 value)` (scope `MP4MuxerBoxes`)
- L19 _function_ `static constexpr uint32 BoxAtom(const uint8 A, const uint8 B, const uint8 C, const uint8 D)` (scope `MP4MuxerBoxes`)
- L87 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FRewriteBoxChangeDelegate, int64 , TConstArrayView<uint8> );`

### `Plugins/Media/MP4Utilities/Source/MP4Muxer/Private/MP4MuxerModule.h` (Private)


#### Free symbols / members of external scopes

- L8 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogMP4Muxer, Log, All);`
- L8 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogMP4Muxer, Log, All);`

### `Plugins/Media/MP4Utilities/Source/MP4Muxer/Public/MP4Muxer.h` (Public)


#### class `IMP4RawMuxer`  
`class IMP4RawMuxer`  
_L33-463_
- desc: This module implements a basic mp4 file multiplexer/writer. The data to be written is handled as RAW data and is not checked for validity. Data is also expected to be framed already, that is, one data packet corresponds to one media sample. If the packet data requires internal sample sizes, eg. NAL unit start codes to be replaced with the NAL size for AVC/HEVC video, this needs to have been done already as well. Codec specific data, like configuration boxes, also need to be set up already in an mp4 box structure and provided per box, which will also just be written as raw data.
- L36 _public prototype_ `virtual ~IMP4RawMuxer() = default;`
- L38 _public prototype_ `static TSharedRef<IMP4RawMuxer, ESPMode::ThreadSafe> Create();`
- L41 _public prototype_ `static TArray<uint8> WrapDataInBox(uint32 InBoxAtom, const TConstArrayView<uint8> InBoxData);` — Wraps binary data in a box. Useful for creating the additional FTrackSpec::SampleEntryBoxes
- L44 _public prototype_ `static TArray<uint8> WrapDataInBox(uint32 InBoxAtom, uint8 InBoxVersion, uint32 InBoxFlags, const TConstArrayView<uint8> InBoxData);` — Wraps binary data in a full box. Useful for creating the additional FTrackSpec::SampleEntryBoxes
- L278 _public prototype_ `virtual bool Configure(const FConfiguration& InConfiguration) = 0;` — Configures the muxer.
- L285 _public prototype_ `virtual int32 AddTrack(const FTrackSpec& InTrackSpec) = 0;` — Adds a track to be written. Returns a track index used during muxing or -1 if the track cannot be added.
- L296 _public prototype_ `virtual bool AddTrackReference(int32 InTrackIndexToAddReferenceTo, int32 InTrackIndexBeingReferenced, uint32 InReferenceType) = 0;` — Adds a track reference. This is usually only done for timecode tracks being referenced by one or more video tracks. See ISO/IEC 14496-12:2022 section 8.3.3 Track reference box Example: If you added a video track (track index 1) and a timecode track (track index 3) and you wish the video to reference the timecode track you call AddTrackReference(1, 3, MakeBoxAtom('t','m','c','d'))
- L308 _public prototype_ `DECLARE_DELEGATE_OneParam(FStatusDelegate, EStatus );`
- L321 _public prototype_ `DECLARE_DELEGATE_OneParam(FRequestTrackDataDelegate, const TArray<FSampleRequest>& );`
- L364 _public prototype_ `virtual bool Start(FRequestTrackDataDelegate InSampleRequestDelegate, FStatusDelegate InStatusDelegate) = 0;` — This method starts the muxing process. While there are samples to be muxed: The muxer invokes the `FRequestTrackDataDelegate`, providing an array of track indices (the value returned by `AddTrack`) and the sample number needed. The delegate is invoked from a muxer internal worker thread and is called at any time the muxer needs (or still needs) another sample for the particular track. NOTE: Due to the asynchronous nature it will happen that the `FRequestTrackDataDelegate` asks for the same sample of a track more than once. For example, if you want to mux three tracks with the track indices 0, 1 and 2 the first invocation of the delegate will ask for sample number 0 of tracks 0, 1 and 2. As soon as you provide sample 0 of track 0 by calling `AddTrackSample()` the delegate will be invoked again, this time asking for track 0 sample 1 and *still* for track 1 sample 0 and track 2 sample 0 because these samples have not been received yet. As a result this means that even if you are currently in the process of gathering sample 0 of track 1 in another parallel worker thread of your own you must not take this new sample request as a new workload. You have to keep track which track samples are currently being worked on and ignore any sample request that pops up twice (or more). You provide the requested sample by calling `AddTrackSample()`. If this is the last sample for this track you need to set the `bIsFinalSample` flag. If you do not know that this will be the last sample at that p
- L450 _public prototype_ `virtual bool AddTrackSample(int32 InTrack, const FTrackSample& InTrackSample) = 0;` — Adds a sample to be written into the specified track as a response to a sample request made by the `FRequestTrackDataDelegate`. Data provided by the ArrayView will be copied into the muxer and can be released on the user side.
- L457 _public prototype_ `virtual bool StopAndClose() = 0;` — Stops muxing and closes the output file. This can be called at any time to abort the process and must be called when muxing is complete (either with or without error).
- L462 _public prototype_ `virtual FString GetLastError() = 0;` — Returns a human readable error message if muxing failed.

#### struct `IMP4RawMuxer::FTrackSpec`  
`struct FTrackSpec`  
_L46-205_
- L134 _public member_ `uint32 SampleEntryFormat = 0;` — ISO/IEC 14496-12 Section 8.5.2.1 "format"
- L141 _public member_ `bool bIsAllKeyframes = true;` — Set to `true` if every sample in this track is independently decodable and is a sync sample (keyframe). Set to `false` if samples depend on other samples.
- L149 _public member_ `uint32 Timescale = 0;` — The number of ticks per second in which this tracks sample decode and presentation time as well as the sample duration is measured in. Must not be zero.
- L156 _public member_ `uint32 ConstantSampleDuration = 0;` — If every sample has the same duration you can set this fixed value here for convenience and then specify 0 for duration in the FTrackSample structure.
- L165 _public member_ `TVariant<FVideo,FAudio,FTimecode,FOpaqueData> Properties;` — Track type specific values that need to be set. The type this variant contains determines if the track contains video, audio, timecode or other. The values in these structures are written as-is and should therefore be set correctly.
- L173 _public member_ `TArray<TArray<uint8>> SampleEntryBoxes;` — Additional pre-built boxes to be added to the sample type (see `SampleEntryFormat` above) that is written to the `stsd` box. This should contain codec specific data like the configuration record and other (optional) boxes.
- L183 _public member_ `TOptional<uint32> SubSampleFlags;` — If set, a subsample box `subs` will be added to the `stsd` or `traf` box with subsample information provided for each sample when adding it to the track. This value contains the 24 bit flags value for the `subs` box. When written the `subs` box will always be of version 1 to use 32 bit subsample sizes.
- L189 _public member_ `uint16 Layer = 0;` — Various flags to set in the `tkhd` box. See ISO/IEC 14496-12:2022 - 8.3.2 Track header box
- L190 _public member_ `uint16 AlternateGroup = 0;`
- L191 _public member_ `bool bEnabled = true;`
- L192 _public member_ `bool bInMovie = true;`
- L198 _public member_ `uint8 Language[3] { 'u','n','d' };` — Language tag to set in the `mvhd` box. Must be a 3 letter ISO-639-2/T code.
- L204 _public member_ `FString Name;` — If set this gets written as an `udta`/`name` box into the track to give the track a human readable label.

#### struct `IMP4RawMuxer::FTrackSpec::FVideo`  
`struct FVideo`  
_L48-53_
- L50 _public member_ `uint32 DisplayWidth = 0;`
- L51 _public member_ `uint32 DisplayHeight = 0;`
- L52 _public member_ `FString CompressorName;`

#### struct `IMP4RawMuxer::FTrackSpec::FAudio`  
`struct FAudio`  
_L54-58_
- L56 _public member_ `uint32 SamplingRate = 0;`
- L57 _public member_ `uint16 NumberOfChannels = 0;`

#### struct `IMP4RawMuxer::FTrackSpec::FTimecode`  
`struct FTimecode`  
_L59-86_
- L79 _public member_ `bool bDropFrame = false;` — Timecode is always written as `tmcd` so this are its parameters See https://developer.apple.com/documentation/quicktime-file-format/timecode_sample_description Please note that the "tape counter" flag is no longer mentioned in https://developer.apple.com/library/archive/technotes/tn2310/_index.html and the technote seems to suggest that only frame counter values are written. Also see https://developer.apple.com/documentation/coremedia/time-code-flags?changes=_5_3&language=objc As such the deprecated "counter" flag (value was 0x8) will not be written. You can write timecode tracks with as many samples as the associated video track or write only single timecode sample that is associated with the first video frame. This is what most writing programs do since the timecode of subsequent frames simply follows from the first and videos usually do not have discontinuties. When writing multiple video tracks and their associated timecode tracks you need to add a reference to the timecode track to the video by calling `AddTrackReference()`. If there is only a single timecode track that applies to all video tracks (or there is only one video track) you should still associate the tracks but this is not strictly necessary.
- L80 _public member_ `bool bMax24Hours = false;`
- L81 _public member_ `bool bAllowNegativeTimes = false;`
- L83 _public member_ `int32 Timescale = 0;` — These values are defined to be signed integers!
- L84 _public member_ `int32 FrameDuration = 0;`
- L85 _public member_ `int8 FramesPerSecond = 0;`

#### struct `IMP4RawMuxer::FTrackSpec::FOpaqueData`  
`struct FOpaqueData`  
_L87-129_
- L104 _public member_ `int32 matrix[9] { 0x00010000,0,0,0,0x00010000,0,0,0,0x40000000 };` — Values to put into the `tkhd` box.
- L105 _public member_ `uint32 width = 0;`
- L106 _public member_ `uint32 height = 0;`
- L107 _public member_ `uint32 flags = 0;` — the track's `bEnabled` and `bInMovie` will overwrite what is set here.
- L108 _public member_ `int16 volume = 0;`
- L112 _public member_ `uint32 mdia_hdlr_Type = 0;` — Type of handler to write to the `mdia`/`hdlr` box.
- L114 _public member_ `FString mdia_hdlr_Name;` — Name of the handler to write to the `mdia`/`hdlr` box.
- L117 _public member_ `uint32 minf_MediaHeader_Type = 0;` — Type of media header box to write into the `minf` box (eg `nmhd`)
- L122 _public member_ `TArray<uint8> minf_MediaHeader_RawBoxData;` — Raw data of the media header box (excluding the box size and box type) to write into the `minf` box. If this box is a full box, then the raw data needs to include the version and flags right before the payload.
- L128 _public member_ `TArray<uint8> stsd_SampleEntry_RawBoxData;` — Raw `SampleEntry` (ISO/IEC 14496-12:2022 - 8.5.2.2 Syntax) data (excluding the box size and box type) to write into the `stsd` box. This sample entry data MUST include the base `SampleEntry` data members! The sample entry type is given by the track's `SampleEntryFormat` parameter (see below).

#### struct `IMP4RawMuxer::FConfiguration`  
`struct FConfiguration`  
_L208-273_
- L223 _public member_ `FString OutputFilename;` — Filename of the file to write.
- L230 _public member_ `FString TemporaryFilename;` — Filename for the temporary file in `WebOptimized` mode. It will be deleted after optimization unless an error occurred or you have aborted muxing by calling `StopAndClose()`.
- L241 _public member_ `uint32 TemporaryOptimizationBufferSize = 0;` — Size of the temporary buffer used to read-write data to and from during the optimization phase in `WebOptimized` mode. Data of the unoptimized file is read into this buffer and written into the optimized file from here. The larger the buffer the fewer read/writes are necessary. If kept at zero a suitable buffer size is chosen automatically. This is only allocated in `WebOptimized` mode.
- L247 _public member_ `EMuxMode MuxMode = EMuxMode::Standard;` — Whether to write a standard mp4 (`moov` box will be placed at the end) or a fragmented mp4.
- L259 _public member_ `FTimespan InterleaveDuration;` — Duration for each chunk of sample data. Samples of each track will be collected until this duration is reached (or the track has no more samples to write) and then written to disk as a group of samples per track. This value must not less or equal to zero. A typical value is 500ms. The larger the value the more data the muxer needs to collect and keep, requiring more memory.
- L271 _public prototype_ `DECLARE_DELEGATE_OneParam(FOptimizeProgressDelegate, float );` — Optional progress delegate to invoke periodically during the optimization phase in `WebOptimized` mode. There is no progress delegate for `Standard` or `Fragmented` mode since the muxer does no know how many samples will be written. If you want to display progress you can do this during the muxing process by tracking which sample number (out of however many, which you should know) is currently being written into the file.
- L272 _public member_ `FOptimizeProgressDelegate OptimizeProgressDelegate;`

#### enum `IMP4RawMuxer::FConfiguration::EMuxMode`  
`enum class EMuxMode`  
_L210-218_
- L213 _public enumerator_ `Standard` — Standard file, `moov` box at the end.
- L215 _public enumerator_ `WebOptimized` — Optimized file, `moov` box in front. Requires a temporary file and a 2nd cleanup pass.
- L217 _public enumerator_ `Fragmented` — Fragmented file

#### enum `IMP4RawMuxer::EStatus`  
`enum class EStatus`  
_L301-307_
- desc: State value reported to the registered `FStatusDelegate`.
- L304 _public enumerator_ `Failed` — Failure.
- L306 _public enumerator_ `Finished` — Multiplexing completed successfully.

#### struct `IMP4RawMuxer::FSampleRequest`  
`struct FSampleRequest`  
_L316-320_
- desc: Defines an entry in the sample request array the registered `FRequestTrackDataDelegate` provides indicating for which track(s) another sample is needed before a new chunk (a group of samples) can be written.
- L318 _public member_ `int32 TrackIndex = -1;`
- L319 _public member_ `uint32 SampleNumber = 0;`

#### struct `IMP4RawMuxer::FTrackSample`  
`struct FTrackSample`  
_L375-442_
- desc: This structure defines the sample to be added to a track during the muxing process. All members should be set correctly as no plausibility checks are performed except for - `Data.Num()` being less than 2^32. A single sample cannot be larger than 4 GiB in an ISO/IEC 14496-12:2022 file.
- L384 _public member_ `TArray<FSubSampleInfo> SubSamples;`
- L390 _public member_ `TConstArrayView64<uint8> Data;` — The sample data to be written. Must already be in the final format as it is written verbatim.
- L400 _public member_ `uint32 Duration = 0;` — Presentation duration of this sample, given in the tracks timescale units. Must not be zero unless a constant duration has been set for the track which must not be zero. The value may be zero for the last sample although this is not recommended. This value is the most important value as it is written to the `stts` box directly and their relative sum determines the decode time (DTS).
- L412 _public member_ `int64 DTS = 0;` — Decode time, given in the tracks timescale units. This value is NOT written into the file directly. An ISO/IEC 14496-12:2022 file only stores DTS differences between samples, implicitly starting at zero. The first DTS may be used to generate an `elst` box if not zero. For keyframe-only tracks that do not need a time offset in an edit list you can leave both DTS and PTS set to zero for every sample and only specify the sample duration.
- L418 _public member_ `int64 PTS = 0;` — Presentation (composition) time, given in the tracks timescale units. This value is ignored for keyframe-only tracks.
- L426 _public member_ `uint32 SampleNumber = 0;` — The sequential number of the sample. This value is not written to the file. It is used only as a verification that this is the sample the `FRequestTrackDataDelegate` has requested and should be set to that value when adding the sample.
- L433 _public member_ `bool bIsKeyframe = false;` — Indicates whether or not this sample is a sync sample that is independently decodable. If this is a keyframe-only track this value is implicitly handled as `true` and does not need to be set.
- L441 _public member_ `bool bIsFinalSample = false;` — Set to `true` when this is the final sample to be added to the track. Set to `false` if more samples follow or if you cannot make that determination at this point in time. You may provide an empty sample later that has this flag set and provides no sample data in `Data`.

#### struct `IMP4RawMuxer::FTrackSample::FSubSampleInfo`  
`struct FSubSampleInfo`  
_L377-383_
- L379 _public member_ `uint32 codec_specific_parameters = 0;`
- L380 _public member_ `uint32 subsample_size = 0;`
- L381 _public member_ `uint8 subsample_priority = 0;`
- L382 _public member_ `uint8 discardable = 0;`

#### Free symbols / members of external scopes

- L16 _macro_ `#define UE_API MP4MUXER_API`
- L271 _delegate_ `DECLARE_DELEGATE_OneParam(FOptimizeProgressDelegate, float );` — Optional progress delegate to invoke periodically during the optimization phase in `WebOptimized` mode. There is no progress delegate for `Standard` or `Fragmented` mode since the muxer does no know how many samples will be written. If you want to display progress you can do this during the muxing process by tracking which sample number (out of however many, which you should know) is currently being written into the file.
- L308 _delegate_ `DECLARE_DELEGATE_OneParam(FStatusDelegate, EStatus );`
- L321 _delegate_ `DECLARE_DELEGATE_OneParam(FRequestTrackDataDelegate, const TArray<FSampleRequest>& );`
