# Plugins / MP4Boxes

- module root: `Plugins/Media/MP4Utilities/Source/MP4Boxes`
- headers: 6; symbols: 1177
- symbol kinds: class=97, delegate=1, enum=4, enumerator=20, function=367, macro=3, member=283, namespace=5, prototype=367, struct=28, typedef=2
- PrivateDependencyModuleNames: Core, MP4Utilities

### `Plugins/Media/MP4Utilities/Source/MP4Boxes/Private/MP4BoxesModule.h` (Private)


#### Free symbols / members of external scopes

- L8 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogMP4Boxes, Log, All);`
- L8 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogMP4Boxes, Log, All);`

### `Plugins/Media/MP4Utilities/Source/MP4Boxes/Public/MP4BoxBase.h` (Public)


#### class `MP4Boxes::FMP4BoxBase`  
`class FMP4BoxBase : public TSharedFromThis<FMP4BoxBase>`  
_L20-195_
- inherits: `TSharedFromThis<FMP4BoxBase>`
- L23 _public function_ `static TSharedPtr<FMP4BoxBase, ESPMode::ThreadSafe> Create(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo)`
- L25 _public prototype_ `virtual ~FMP4BoxBase() = default;`
- L27 _public prototype_ `virtual TArray<uint8> GetBoxDataRAW() const;`
- L28 _public function_ `virtual const MP4Utilities::FMP4BoxInfo& GetBoxInfo() const`
- L30 _public function_ `virtual uint32 GetType() const`
- L32 _public function_ `virtual int64 GetBoxSize() const`
- L34 _public function_ `virtual TConstArrayView<uint8> GetBoxData() const`
- L36 _public function_ `virtual int64 GetBoxFileOffset() const`
- L38 _public function_ `virtual int64 GetBoxDataOffset() const`
- L40 _public function_ `virtual bool IsLeafBox() const`
- L42 _public function_ `virtual bool IsListOfEntries() const`
- L44 _public function_ `virtual bool IsSampleDescription() const`
- L50 _public function_ `TSharedPtr<FMP4BoxBase, ESPMode::ThreadSafe> GetParentBox() const` — Parent box query methods
- L56 _public function_ `template<typename T> TSharedPtr<T, ESPMode::ThreadSafe> FindParentBox(uint32 InType) const`
- L73 _public function_ `const TArray<TSharedPtr<FMP4BoxBase, ESPMode::ThreadSafe>> GetChildren() const` — Child box query methods
- L78 _public function_ `template<typename T> TSharedPtr<T, ESPMode::ThreadSafe> FindBoxRecursive(uint32 InType, int32 InMaxDepth=8) const` — Find the first box of the given type being a child of this box, or any child of a child box.
- L104 _public function_ `template<typename T, typename Predicate> TSharedPtr<T, ESPMode::ThreadSafe> FindBoxRecursiveByPredicate(uint32 InType, Predicate InPredicate, int32 InMaxDepth=8) const`
- L136 _public function_ `template<typename T> void GetAllBoxInstances(TArray<TSharedPtr<T, ESPMode::ThreadSafe>>& OutAllBoxes, uint32 InType) const` — Returns all instances of a given box type from the direct children of THIS BOX ONLY.
- L148 _public function_ `template<typename T, typename Predicate> void GetAllBoxInstancesByPredicate(TArray<TSharedPtr<T, ESPMode::ThreadSafe>>& OutAllBoxes, uint32 InType, Predicate InPredicate, int32 InMaxDepth=8) const`
- L173 _public function_ `virtual bool AddChildBox(TSharedPtr<FMP4BoxBase, ESPMode::ThreadSafe> InChildBox)` — Called by building the box tree. Not to be called by user code.
- L183 _public prototype_ `virtual void ProcessBoxChildrenRecursively(MP4Utilities::FMP4AtomReader& InOutReader, const MP4Utilities::FMP4BoxInfo& InCurrentBoxInfo);`
- L185 _public function_ `void SetRootBoxData(const TSharedPtr<MP4Utilities::FMP4BoxInfo, ESPMode::ThreadSafe>& InRootBoxData)`
- L188 _protected function_ `FMP4BoxBase(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo) : ParentBox(InParent), BoxInfo(InBoxInfo)`
- L191 _protected member_ `TSharedPtr<MP4Utilities::FMP4BoxInfo, ESPMode::ThreadSafe> RootBoxData;`
- L192 _protected member_ `TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe> ParentBox;`
- L193 _protected member_ `TArray<TSharedPtr<FMP4BoxBase, ESPMode::ThreadSafe>> Children;`
- L194 _protected member_ `MP4Utilities::FMP4BoxInfo BoxInfo;`

#### class `MP4Boxes::FMP4BoxTreeParser`  
`class FMP4BoxTreeParser`  
_L199-208_
- L202 _public prototype_ `bool ParseBoxTree(const TSharedPtr<MP4Utilities::FMP4BoxInfo, ESPMode::ThreadSafe>& InRootBox);`
- L203 _public function_ `TSharedPtr<FMP4BoxBase, ESPMode::ThreadSafe> GetBoxTree() const`
- L206 _private prototype_ `bool ParseBoxTreeInternal(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBox);`
- L207 _private member_ `TSharedPtr<FMP4BoxBase, ESPMode::ThreadSafe> BoxTree;`

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API MP4BOXES_API`
- L17 _namespace_ `namespace MP4Boxes`

### `Plugins/Media/MP4Utilities/Source/MP4Boxes/Public/MP4BoxIterators.h` (Public)


#### struct `MP4Boxes::FSTTSBoxIterator`  
`struct FSTTSBoxIterator`  
_L19-128_
- L21 _public function_ `void SetBox(const TSharedPtr<FMP4BoxSTTS, ESPMode::ThreadSafe>& InSttsBox)`
- L33 _public function_ `void SetToSampleNumber(uint32 InSampleNum)`
- L57 _public function_ `bool Next()`
- L78 _public function_ `bool Prev()`
- L104 _public function_ `int64 GetCurrentTime() const`
- L106 _public function_ `int64 GetConstantSampleDuration() const`
- L108 _public function_ `uint32 GetCurrentDuration() const`
- L110 _public function_ `uint32 GetCurrentSampleNum() const`
- L112 _public function_ `uint32 GetNumTotalSamples() const`
- L114 _public function_ `bool IsFirst() const`
- L116 _public function_ `bool IsLast() const`
- L120 _private member_ `TSharedPtr<FMP4BoxSTTS, ESPMode::ThreadSafe> SttsBox;`
- L121 _private member_ `int64 Time = 0;`
- L122 _private member_ `int64 ConstantSampleDuration = 0;`
- L123 _private member_ `uint32 CurrentSampleNum = 0;`
- L124 _private member_ `uint32 NumTotalSamples = 0;`
- L125 _private member_ `uint32 LocalPosInCurrent = 0;`
- L126 _private member_ `uint32 CurrentDuration = 0;`
- L127 _private member_ `int32 CurrentEntryIndex = 0;`

#### struct `MP4Boxes::FCTTSBoxIterator`  
`struct FCTTSBoxIterator`  
_L132-240_
- L134 _public function_ `void SetBox(const TSharedPtr<FMP4BoxCTTS, ESPMode::ThreadSafe>& InCttsBox, uint32 InMaxSamples)`
- L152 _public function_ `void SetToSampleNumber(uint32 InSampleNum)`
- L175 _public function_ `bool Next()`
- L197 _public function_ `bool Prev()`
- L224 _public function_ `int64 GetCurrentOffset() const`
- L226 _public function_ `uint32 GetCurrentSampleNum() const`
- L228 _public function_ `bool IsFirst() const`
- L230 _public function_ `bool IsLast() const`
- L234 _private member_ `TSharedPtr<FMP4BoxCTTS, ESPMode::ThreadSafe> CttsBox;`
- L235 _private member_ `int64 CurrentOffset = 0;`
- L236 _private member_ `uint32 CurrentSampleNum = 0;`
- L237 _private member_ `uint32 NumTotalSamples = 0;`
- L238 _private member_ `uint32 LocalPosInCurrent = 0;`
- L239 _private member_ `int32 CurrentEntryIndex = 0;`

#### struct `MP4Boxes::FSTSCBoxIterator`  
`struct FSTSCBoxIterator`  
_L244-406_
- L246 _public function_ `void SetBox(const TSharedPtr<FMP4BoxSTSC, ESPMode::ThreadSafe>& InStscBox, uint32 InMaxSamples)`
- L268 _public function_ `void SetToSampleNumber(uint32 InSampleNum)`
- L304 _public function_ `bool Next()`
- L334 _public function_ `bool Prev()`
- L373 _public function_ `uint32 GetCurrentChunkIndex() const` — Note: The chunk index is 1-based, so you need to subtract 1 to use as an index into the `stco` box.
- L375 _public function_ `uint32 GetNumSamplesInCurrentChunk() const`
- L377 _public function_ `uint32 GetSampleIndexInCurrentChunk() const`
- L379 _public function_ `uint32 GetCurrentSampleNum() const`
- L381 _public function_ `bool IsFirst() const`
- L383 _public function_ `bool IsLast() const`
- L386 _public function_ `bool IsFinalChunk() const`
- L397 _private member_ `TSharedPtr<FMP4BoxSTSC, ESPMode::ThreadSafe> StscBox;`
- L398 _private member_ `uint32 Current_first_chunk = 0;`
- L399 _private member_ `uint32 Current_samples_per_chunk = 0;`
- L400 _private member_ `uint32 Current_sample_description_index = 0;`
- L402 _private member_ `uint32 CurrentSampleNum = 0;`
- L403 _private member_ `uint32 NumTotalSamples = 0;`
- L404 _private member_ `uint32 LocalSampleInChunk = 0;`
- L405 _private member_ `uint32 CurrentEntryIndex = 0;`

#### struct `MP4Boxes::FSTSZBoxIterator`  
`struct FSTSZBoxIterator`  
_L410-483_
- L412 _public function_ `void SetBox(const TSharedPtr<FMP4BoxSTSZ, ESPMode::ThreadSafe>& InStszBox)`
- L420 _public function_ `TSharedPtr<FMP4BoxSTSZ, ESPMode::ThreadSafe> GetBox() const`
- L425 _public function_ `void SetToSampleNumber(uint32 InSampleNum)`
- L430 _public function_ `bool Next()`
- L444 _public function_ `bool Prev()`
- L458 _public function_ `uint32 GetCurrentSampleSize() const`
- L464 _public function_ `uint32 GetSampleSizeForSampleNum(uint32 InForSampleNum) const`
- L470 _public function_ `uint32 GetNumTotalSamples() const`
- L472 _public function_ `uint32 GetCurrentSampleNum() const`
- L474 _public function_ `bool IsFirst() const`
- L476 _public function_ `bool IsLast() const`
- L480 _private member_ `TSharedPtr<FMP4BoxSTSZ, ESPMode::ThreadSafe> StszBox;`
- L481 _private member_ `uint32 NumTotalSamples = 0;`
- L482 _private member_ `uint32 CurrentSampleNum = 0;`

#### struct `MP4Boxes::FSTCOBoxIterator`  
`struct FSTCOBoxIterator`  
_L488-506_
- desc: This is not so much an iterator than a holder of the box.
- L490 _public function_ `void SetBox(const TSharedPtr<FMP4BoxSTCO, ESPMode::ThreadSafe>& InStcoBox)`
- L496 _public function_ `void SetToSampleNumber(uint32 InSampleNum)`
- L500 _public function_ `uint64 GetOffsetForChunkIndex(uint32 InChunkIndex) const`
- L505 _private member_ `TSharedPtr<FMP4BoxSTCO, ESPMode::ThreadSafe> StcoBox;`

#### struct `MP4Boxes::FSTSSBoxIterator`  
`struct FSTSSBoxIterator`  
_L510-604_
- L512 _public function_ `void SetBox(const TSharedPtr<FMP4BoxSTSS, ESPMode::ThreadSafe>& InStssBox, uint32 InMaxSamples)`
- L521 _public function_ `void SetToSampleNumber(uint32 InSampleNum)`
- L540 _public function_ `bool Next()`
- L560 _public function_ `bool Prev()`
- L584 _public function_ `bool IsSyncSample() const`
- L589 _public function_ `uint32 GetNumTotalSamples() const`
- L591 _public function_ `uint32 GetCurrentSampleNum() const`
- L593 _public function_ `bool IsFirst() const`
- L595 _public function_ `bool IsLast() const`
- L599 _private member_ `TSharedPtr<FMP4BoxSTSS, ESPMode::ThreadSafe> StssBox;`
- L600 _private member_ `uint32 NumTotalSamples = 0;`
- L601 _private member_ `uint32 CurrentSampleNum = 0;`
- L602 _private member_ `uint32 CurrentEntryIndex = 0;`
- L603 _private member_ `bool bCurrentIsSyncSample = true;`

#### struct `MP4Boxes::FSBGPBoxIterator`  
`struct FSBGPBoxIterator`  
_L608-771_
- L610 _public function_ `void SetBox(const TSharedPtr<FMP4BoxSBGP, ESPMode::ThreadSafe>& InSbgpBox, uint32 InDefaultSampleGroupDescriptionIndex, uint32 InMaxSamples)`
- L633 _public function_ `void SetToSampleNumber(uint32 InSampleNum)`
- L679 _public function_ `bool Next()`
- L713 _public function_ `bool Prev()`
- L747 _public function_ `uint32 GetCurrentGroupDescriptionIndex() const`
- L749 _public function_ `uint32 GetNumSamplesInCurrentGroup() const`
- L751 _public function_ `uint32 GetSampleIndexInCurrentGroup() const`
- L753 _public function_ `uint32 GetCurrentSampleNum() const`
- L755 _public function_ `bool IsFirst() const`
- L757 _public function_ `bool IsLast() const`
- L761 _private member_ `TSharedPtr<FMP4BoxSBGP, ESPMode::ThreadSafe> SbgpBox;`
- L762 _private member_ `uint32 Current_sample_count = 0;`
- L763 _private member_ `uint32 Current_group_description_index = 0;`
- L764 _private member_ `uint32 DefaultSampleGroupDescriptionIndex = 0;`
- L766 _private member_ `uint32 NumTotalSamples = 0;`
- L767 _private member_ `uint32 NumDescribedSamples = 0;`
- L768 _private member_ `uint32 CurrentSampleNum = 0;`
- L769 _private member_ `uint32 LocalSampleInGroup = 0;`
- L770 _private member_ `uint32 CurrentEntryIndex = 0;`

#### struct `MP4Boxes::FSUBSBoxIterator`  
`struct FSUBSBoxIterator`  
_L775-926_
- L777 _public function_ `void SetBox(const TSharedPtr<FMP4BoxSUBS, ESPMode::ThreadSafe>& InSubsBox, uint32 InMaxSamples)`
- L796 _public function_ `void SetToSampleNumber(uint32 InSampleNum)`
- L828 _public function_ `bool Next()`
- L862 _public function_ `bool Prev()`
- L891 _public function_ `TOptional<uint32> GetSubsampleBoxFlags() const`
- L896 _public function_ `bool HaveSubsamplesForCurrent() const`
- L905 _public function_ `const FMP4BoxSUBS::FSubsampleList& GetCurrentSubsamples() const`
- L910 _public function_ `uint32 GetCurrentSampleNum() const`
- L912 _public function_ `bool IsFirst() const`
- L914 _public function_ `bool IsLast() const`
- L918 _private member_ `TSharedPtr<FMP4BoxSUBS, ESPMode::ThreadSafe> SubsBox;`
- L919 _private member_ `FMP4BoxSUBS::FSubsampleList EmptySubsampleList;`
- L921 _private member_ `uint32 NumTotalSamples = 0;`
- L922 _private member_ `uint32 FirstDescribedSampleNum = 0;`
- L923 _private member_ `uint32 LastDescribedSampleNum = 0;`
- L924 _private member_ `uint32 CurrentSampleNum = 0;`
- L925 _private member_ `int32 CurrentEntryIndex = 0;`

#### struct `MP4Boxes::FSENCBoxIterator`  
`struct FSENCBoxIterator`  
_L930-989_
- L932 _public function_ `void SetBox(const TSharedPtr<FMP4BoxTENC, ESPMode::ThreadSafe>& InTencBox, const TSharedPtr<FMP4BoxSENC, ESPMode::ThreadSafe>& InSencBox, uint32 InMaxSamples)`
- L947 _public function_ `void SetToSampleNumber(uint32 InSampleNum)`
- L953 _public function_ `bool Next()`
- L963 _public function_ `bool Prev()`
- L973 _public function_ `bool IsFirst() const`
- L975 _public function_ `bool IsLast() const`
- L978 _public function_ `const FMP4BoxSENC::FEntry& GetCurrentEntry() const`
- L984 _private member_ `TSharedPtr<FMP4BoxSENC, ESPMode::ThreadSafe> SencBox;`
- L985 _private member_ `FMP4BoxSENC::FEntry DefaultEntry;`
- L986 _private member_ `uint32 NumTotalSamples = 0;`
- L987 _private member_ `uint32 NumBoxSamples = 0;`
- L988 _private member_ `uint32 CurrentSampleNum = 0;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace MP4Boxes`

### `Plugins/Media/MP4Utilities/Source/MP4Boxes/Public/MP4BoxMetadata.h` (Public)


#### struct `MP4Boxes::FMP4TrackMetadataCommon`  
`struct FMP4TrackMetadataCommon`  
_L12-18_
- L14 _public member_ `FString LanguageCode;` — 3 letter ISO 639-2T
- L15 _public member_ `FString LanguageTag;` — BCP47 language tag if available
- L16 _public member_ `FString Name;`
- L17 _public member_ `FString HandlerName;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace MP4Boxes`

### `Plugins/Media/MP4Utilities/Source/MP4Boxes/Public/MP4Boxes.h` (Public)


#### class `MP4Boxes::FMP4BoxFREE`  
`class FMP4BoxFREE : public FMP4BoxBase`  
_L23-33_
- inherits: `FMP4BoxBase`
- desc: `free` and `skip` box ISO/IEC 14496-12:2022 - 8.1.2 Free space box
- L26 _public function_ `static TSharedPtr<FMP4BoxBase, ESPMode::ThreadSafe> Create(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo)`
- L28 _public prototype_ `virtual ~FMP4BoxFREE() = default;`
- L30 _protected function_ `FMP4BoxFREE(const TWeakPtr<FMP4BoxBase>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo) : FMP4BoxBase(InParent, InBoxInfo)`

#### class `MP4Boxes::FMP4BoxFTYP`  
`class FMP4BoxFTYP : public FMP4BoxBase`  
_L40-57_
- inherits: `FMP4BoxBase`
- desc: `ftyp` box ISO/IEC 14496-12:2022 - 4.3 File-type box
- L43 _public function_ `static TSharedPtr<FMP4BoxBase, ESPMode::ThreadSafe> Create(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo)`
- L45 _public prototype_ `virtual ~FMP4BoxFTYP() = default;`
- L46 _public prototype_ `uint32 GetMajorBrand();`
- L47 _public prototype_ `uint32 GetMinorVersion();`
- L48 _public prototype_ `TConstArrayView<uint32> GetCompatibleBrands();`
- L49 _public prototype_ `TConstArrayView<uint32> GetAllBrands();`
- L51 _protected function_ `FMP4BoxFTYP(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo) : FMP4BoxBase(InParent, InBoxInfo)`
- L54 _protected prototype_ `void ParseIfRequired();`
- L56 _protected member_ `TPimplPtr<FParsed> Parsed;`

#### class `MP4Boxes::FMP4BoxSTYP`  
`class FMP4BoxSTYP : public FMP4BoxFTYP`  
_L64-74_
- inherits: `FMP4BoxFTYP`
- desc: `styp` box ISO/IEC 14496-12:2022 - 8.16.2 Segment type box
- L67 _public function_ `static TSharedPtr<FMP4BoxBase, ESPMode::ThreadSafe> Create(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo)`
- L69 _public prototype_ `virtual ~FMP4BoxSTYP() = default;`
- L71 _protected function_ `FMP4BoxSTYP(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo) : FMP4BoxFTYP(InParent, InBoxInfo)`

#### class `MP4Boxes::FMP4BoxMOOV`  
`class FMP4BoxMOOV : public FMP4BoxBase`  
_L81-92_
- inherits: `FMP4BoxBase`
- desc: `moov` box ISO/IEC 14496-12:2022 - 8.2.1 Movie box
- L84 _public function_ `static TSharedPtr<FMP4BoxBase, ESPMode::ThreadSafe> Create(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo)`
- L86 _public prototype_ `virtual ~FMP4BoxMOOV() = default;`
- L87 _public function_ `bool IsLeafBox() const override`
- L89 _protected function_ `FMP4BoxMOOV(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo) : FMP4BoxBase(InParent, InBoxInfo)`

#### class `MP4Boxes::FMP4BoxMVHD`  
`class FMP4BoxMVHD : public FMP4BoxBase`  
_L99-115_
- inherits: `FMP4BoxBase`
- desc: `mvhd` box ISO/IEC 14496-12:2022 - 8.2.2 Movie header box
- L102 _public function_ `static TSharedPtr<FMP4BoxBase, ESPMode::ThreadSafe> Create(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo)`
- L104 _public prototype_ `virtual ~FMP4BoxMVHD() = default;`
- L106 _public prototype_ `MP4Utilities::FFractionalTime GetDuration();`
- L107 _public prototype_ `uint32 GetTimescale();`
- L109 _protected function_ `FMP4BoxMVHD(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo) : FMP4BoxBase(InParent, InBoxInfo)`
- L112 _protected prototype_ `void ParseIfRequired();`
- L114 _protected member_ `TPimplPtr<FParsed> Parsed;`

#### class `MP4Boxes::FMP4BoxTRAK`  
`class FMP4BoxTRAK : public FMP4BoxBase`  
_L122-133_
- inherits: `FMP4BoxBase`
- desc: `trak` box ISO/IEC 14496-12:2022 - 8.3.1 Track box
- L125 _public function_ `static TSharedPtr<FMP4BoxBase, ESPMode::ThreadSafe> Create(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo)`
- L127 _public prototype_ `virtual ~FMP4BoxTRAK() = default;`
- L128 _public function_ `bool IsLeafBox() const override`
- L130 _protected function_ `FMP4BoxTRAK(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo) : FMP4BoxBase(InParent, InBoxInfo)`

#### class `MP4Boxes::FMP4BoxTKHD`  
`class FMP4BoxTKHD : public FMP4BoxBase`  
_L140-183_
- inherits: `FMP4BoxBase`
- desc: `tkhd` box ISO/IEC 14496-12:2022 - 8.3.2 Track header box
- L143 _public function_ `static TSharedPtr<FMP4BoxBase, ESPMode::ThreadSafe> Create(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo)`
- L145 _public prototype_ `virtual ~FMP4BoxTKHD() = default;`
- L147 _public prototype_ `uint32 GetFlags();`
- L149 _public function_ `bool IsEnabled()`
- L152 _public function_ `bool IsInMovie()`
- L155 _public function_ `bool IsInPreview()`
- L158 _public function_ `bool IsTrackSizeAspectRatio()`
- L165 _public prototype_ `int64 GetDuration();` — Returns the duration of this track, measured in the timescale of the `mvhd` box. This is just the value as stored in the box. You need to apply the timescale yourself.
- L167 _public prototype_ `uint32 GetTrackID();`
- L169 _public prototype_ `uint16 GetWidth();`
- L170 _public prototype_ `uint16 GetHeight();`
- L172 _public prototype_ `TArray<int32> GetMatrix();`
- L173 _public prototype_ `uint32 GetWidthRaw();`
- L174 _public prototype_ `uint32 GetHeightRaw();`
- L175 _public prototype_ `uint16 GetVolumeRaw();`
- L177 _protected function_ `FMP4BoxTKHD(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo) : FMP4BoxBase(InParent, InBoxInfo)`
- L180 _protected prototype_ `void ParseIfRequired();`
- L182 _protected member_ `TPimplPtr<FParsed> Parsed;`

#### class `MP4Boxes::FMP4BoxTREF`  
`class FMP4BoxTREF : public FMP4BoxBase`  
_L190-214_
- inherits: `FMP4BoxBase`
- desc: `tref` box ISO/IEC 14496-12:2022 - 8.3.3 Track reference box
- L193 _public function_ `static TSharedPtr<FMP4BoxBase, ESPMode::ThreadSafe> Create(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo)`
- L195 _public prototype_ `virtual ~FMP4BoxTREF() = default;`
- L196 _public function_ `bool IsLeafBox() const override`
- L197 _public function_ `bool IsListOfEntries() const override`
- L205 _public prototype_ `const TArray<FEntry>& GetEntries();`
- L206 _public prototype_ `TArray<FEntry> GetEntriesOfType(uint32 InType);`
- L208 _protected function_ `FMP4BoxTREF(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo) : FMP4BoxBase(InParent, InBoxInfo)`
- L211 _protected prototype_ `void ParseIfRequired();`
- L213 _protected member_ `TPimplPtr<FParsed> Parsed;`

#### struct `MP4Boxes::FMP4BoxTREF::FEntry`  
`struct FEntry`  
_L199-203_
- L201 _public member_ `uint32 Type = 0;`
- L202 _public member_ `TArray<uint32> TrackIDs;`

#### class `MP4Boxes::FMP4BoxEDTS`  
`class FMP4BoxEDTS : public FMP4BoxBase`  
_L221-232_
- inherits: `FMP4BoxBase`
- desc: `edts` box ISO/IEC 14496-12:2022 - 8.6.5 Edit box
- L224 _public function_ `static TSharedPtr<FMP4BoxBase, ESPMode::ThreadSafe> Create(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo)`
- L226 _public prototype_ `virtual ~FMP4BoxEDTS() = default;`
- L227 _public function_ `bool IsLeafBox() const override`
- L229 _protected function_ `FMP4BoxEDTS(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo) : FMP4BoxBase(InParent, InBoxInfo)`

#### class `MP4Boxes::FMP4BoxELST`  
`class FMP4BoxELST : public FMP4BoxBase`  
_L239-266_
- inherits: `FMP4BoxBase`
- desc: `elst` box ISO/IEC 14496-12:2022 - 8.6.6 Edit list box
- L242 _public function_ `static TSharedPtr<FMP4BoxBase, ESPMode::ThreadSafe> Create(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo)`
- L244 _public prototype_ `virtual ~FMP4BoxELST() = default;`
- L256 _public prototype_ `const TArray<FEntry>& GetEntries();`
- L257 _public prototype_ `bool RepeatEdits();`
- L260 _protected function_ `FMP4BoxELST(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo) : FMP4BoxBase(InParent, InBoxInfo)`
- L263 _protected prototype_ `void ParseIfRequired();`
- L265 _protected member_ `TPimplPtr<FParsed> Parsed;`

#### struct `MP4Boxes::FMP4BoxELST::FEntry`  
`struct FEntry`  
_L246-254_
- L249 _public member_ `int64 edit_duration = 0;` — Specified in units of timescale of the `mvhd` box.
- L251 _public member_ `int64 media_time = 0;` — Specified in units of timescale of the `mdhd` box of this track.
- L252 _public member_ `int16 media_rate_integer = 0;`
- L253 _public member_ `int16 media_rate_fraction = 0;`

#### class `MP4Boxes::FMP4BoxMDIA`  
`class FMP4BoxMDIA : public FMP4BoxBase`  
_L273-284_
- inherits: `FMP4BoxBase`
- desc: `mdia` box ISO/IEC 14496-12:2022 - 8.4.1 Media box
- L276 _public function_ `static TSharedPtr<FMP4BoxBase, ESPMode::ThreadSafe> Create(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo)`
- L278 _public prototype_ `virtual ~FMP4BoxMDIA() = default;`
- L279 _public function_ `bool IsLeafBox() const override`
- L281 _protected function_ `FMP4BoxMDIA(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo) : FMP4BoxBase(InParent, InBoxInfo)`

#### class `MP4Boxes::FMP4BoxMDHD`  
`class FMP4BoxMDHD : public FMP4BoxBase`  
_L291-309_
- inherits: `FMP4BoxBase`
- desc: `mdhd` box ISO/IEC 14496-12:2022 - 8.4.2 Media header box
- L294 _public function_ `static TSharedPtr<FMP4BoxBase, ESPMode::ThreadSafe> Create(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo)`
- L296 _public prototype_ `virtual ~FMP4BoxMDHD() = default;`
- L298 _public prototype_ `MP4Utilities::FFractionalTime GetDuration();`
- L299 _public prototype_ `uint32 GetTimescale();`
- L300 _public prototype_ `FString GetLanguageCode639_2T();`
- L303 _protected function_ `FMP4BoxMDHD(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo) : FMP4BoxBase(InParent, InBoxInfo)`
- L306 _protected prototype_ `void ParseIfRequired();`
- L308 _protected member_ `TPimplPtr<FParsed> Parsed;`

#### class `MP4Boxes::FMP4BoxHDLR`  
`class FMP4BoxHDLR : public FMP4BoxBase`  
_L316-333_
- inherits: `FMP4BoxBase`
- desc: `hdlr` box ISO/IEC 14496-12:2022 - 8.4.3 Handler reference box
- L319 _public function_ `static TSharedPtr<FMP4BoxBase, ESPMode::ThreadSafe> Create(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo)`
- L321 _public prototype_ `virtual ~FMP4BoxHDLR() = default;`
- L323 _public prototype_ `uint32 GetHandlerType();`
- L324 _public prototype_ `FString GetHandlerName();`
- L325 _public prototype_ `uint32 GetReservedValue(int32 InIndex0to2);`
- L327 _protected function_ `FMP4BoxHDLR(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo) : FMP4BoxBase(InParent, InBoxInfo)`
- L330 _protected prototype_ `void ParseIfRequired();`
- L332 _protected member_ `TPimplPtr<FParsed> Parsed;`

#### class `MP4Boxes::FMP4BoxMINF`  
`class FMP4BoxMINF : public FMP4BoxBase`  
_L340-351_
- inherits: `FMP4BoxBase`
- desc: `minf` box ISO/IEC 14496-12:2022 - 8.4.4 Media information box
- L343 _public function_ `static TSharedPtr<FMP4BoxBase, ESPMode::ThreadSafe> Create(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo)`
- L345 _public prototype_ `virtual ~FMP4BoxMINF() = default;`
- L346 _public function_ `bool IsLeafBox() const override`
- L348 _protected function_ `FMP4BoxMINF(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo) : FMP4BoxBase(InParent, InBoxInfo)`

#### class `MP4Boxes::FMP4BoxELNG`  
`class FMP4BoxELNG : public FMP4BoxBase`  
_L358-373_
- inherits: `FMP4BoxBase`
- desc: `elng` box ISO/IEC 14496-12:2022 - 8.4.6 Extended language tag
- L361 _public function_ `static TSharedPtr<FMP4BoxBase, ESPMode::ThreadSafe> Create(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo)`
- L363 _public prototype_ `virtual ~FMP4BoxELNG() = default;`
- L365 _public prototype_ `FString GetLanguageTag();`
- L367 _protected function_ `FMP4BoxELNG(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo) : FMP4BoxBase(InParent, InBoxInfo)`
- L370 _protected prototype_ `void ParseIfRequired();`
- L372 _protected member_ `TPimplPtr<FParsed> Parsed;`

#### class `MP4Boxes::FMP4BoxDINF`  
`class FMP4BoxDINF : public FMP4BoxBase`  
_L380-391_
- inherits: `FMP4BoxBase`
- desc: `dinf` box ISO/IEC 14496-12:2022 - 8.7.1 Data information box
- L383 _public function_ `static TSharedPtr<FMP4BoxBase, ESPMode::ThreadSafe> Create(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo)`
- L385 _public prototype_ `virtual ~FMP4BoxDINF() = default;`
- L386 _public function_ `bool IsLeafBox() const override`
- L388 _protected function_ `FMP4BoxDINF(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo) : FMP4BoxBase(InParent, InBoxInfo)`

#### class `MP4Boxes::FMP4BoxDREF`  
`class FMP4BoxDREF : public FMP4BoxBase`  
_L398-410_
- inherits: `FMP4BoxBase`
- desc: `dref` box ISO/IEC 14496-12:2022 - 8.7.2 Data reference box
- L401 _public function_ `static TSharedPtr<FMP4BoxBase, ESPMode::ThreadSafe> Create(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo)`
- L403 _public prototype_ `virtual ~FMP4BoxDREF() = default;`
- L404 _public function_ `bool IsLeafBox() const override`
- L405 _public function_ `bool IsListOfEntries() const override`
- L407 _protected function_ `FMP4BoxDREF(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo) : FMP4BoxBase(InParent, InBoxInfo)`

#### class `MP4Boxes::FMP4BoxSTBL`  
`class FMP4BoxSTBL : public FMP4BoxBase`  
_L417-428_
- inherits: `FMP4BoxBase`
- desc: `stbl` box ISO/IEC 14496-12:2022 - 8.5.1 Sample table box
- L420 _public function_ `static TSharedPtr<FMP4BoxBase, ESPMode::ThreadSafe> Create(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo)`
- L422 _public prototype_ `virtual ~FMP4BoxSTBL() = default;`
- L423 _public function_ `bool IsLeafBox() const override`
- L425 _protected function_ `FMP4BoxSTBL(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo) : FMP4BoxBase(InParent, InBoxInfo)`

#### class `MP4Boxes::FMP4BoxSampleEntry`  
`class FMP4BoxSampleEntry : public FMP4BoxBase`  
_L435-460_
- inherits: `FMP4BoxBase`
- desc: Sample entry base class ISO/IEC 14496-12:2022 - 8.5.2 Sample description box
- L438 _public prototype_ `virtual ~FMP4BoxSampleEntry() = default;`
- L439 _public function_ `bool IsSampleDescription() const override`
- L452 _public function_ `virtual ESampleType GetSampleType()`
- L454 _public prototype_ `virtual uint16 GetDataReferenceIndex() = 0;`
- L457 _protected function_ `FMP4BoxSampleEntry(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo) : FMP4BoxBase(InParent, InBoxInfo)`

#### enum `MP4Boxes::FMP4BoxSampleEntry::ESampleType`  
`enum class ESampleType`  
_L442-451_
- L444 _public enumerator_ `Video`
- L445 _public enumerator_ `Audio`
- L446 _public enumerator_ `Subtitles`
- L447 _public enumerator_ `QTFFTimecode`
- L448 _public enumerator_ `TimedMetadata`
- L449 _public enumerator_ `TimedText`
- L450 _public enumerator_ `Unsupported`

#### class `MP4Boxes::FMP4BoxBTRT`  
`class FMP4BoxBTRT : public FMP4BoxBase`  
_L467-483_
- inherits: `FMP4BoxBase`
- desc: `btrt` box ISO/IEC 14496-12:2022 - 8.5.2 Sample description box (8.5.2.2 Bitrate box)
- L470 _public function_ `static TSharedPtr<FMP4BoxBase, ESPMode::ThreadSafe> Create(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo)`
- L472 _public prototype_ `virtual ~FMP4BoxBTRT() = default;`
- L473 _public prototype_ `uint32 GetBufferSizeDB();`
- L474 _public prototype_ `uint32 GetMaxBitrate();`
- L475 _public prototype_ `uint32 GetAverageBitrate();`
- L477 _protected function_ `FMP4BoxBTRT(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo) : FMP4BoxBase(InParent, InBoxInfo)`
- L480 _protected prototype_ `void ParseIfRequired();`
- L482 _protected member_ `TPimplPtr<FParsed> Parsed;`

#### class `MP4Boxes::FMP4BoxSRAT`  
`class FMP4BoxSRAT : public FMP4BoxBase`  
_L490-504_
- inherits: `FMP4BoxBase`
- desc: `srat` box ISO/IEC 14496-12:2022 - 12.2.3 AudioSampleEntry (12.2.3.2 Syntax)
- L493 _public function_ `static TSharedPtr<FMP4BoxBase, ESPMode::ThreadSafe> Create(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo)`
- L495 _public prototype_ `virtual ~FMP4BoxSRAT() = default;`
- L496 _public prototype_ `uint32 GetSampleRate();`
- L498 _protected function_ `FMP4BoxSRAT(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo) : FMP4BoxBase(InParent, InBoxInfo)`
- L501 _protected prototype_ `void ParseIfRequired();`
- L503 _protected member_ `TPimplPtr<FParsed> Parsed;`

#### class `MP4Boxes::FMP4BoxVisualSampleEntry`  
`class FMP4BoxVisualSampleEntry : public FMP4BoxSampleEntry`  
_L511-532_
- inherits: `FMP4BoxSampleEntry`
- desc: Visual sample entry ISO/IEC 14496-12:2022 - 12.1.3 Sample entry
- L514 _public function_ `static TSharedPtr<FMP4BoxBase, ESPMode::ThreadSafe> Create(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo)`
- L516 _public prototype_ `virtual ~FMP4BoxVisualSampleEntry() = default;`
- L517 _public function_ `ESampleType GetSampleType() override`
- L519 _public prototype_ `uint16 GetDataReferenceIndex() override;`
- L520 _public prototype_ `uint16 GetWidth();`
- L521 _public prototype_ `uint16 GetHeight();`
- L522 _public prototype_ `uint16 GetFrameCount();`
- L523 _public prototype_ `uint16 GetDepth();`
- L524 _public prototype_ `FString GetCompressorName();`
- L526 _protected function_ `FMP4BoxVisualSampleEntry(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo) : FMP4BoxSampleEntry(InParent, InBoxInfo)`
- L529 _protected prototype_ `void ParseIfRequired();`
- L531 _protected member_ `TPimplPtr<FParsed> Parsed;`

#### class `MP4Boxes::FMP4BoxAudioSampleEntry`  
`class FMP4BoxAudioSampleEntry : public FMP4BoxSampleEntry`  
_L539-562_
- inherits: `FMP4BoxSampleEntry`
- desc: Audio sample entry ISO/IEC 14496-12:2022 - 12.2.3 Sample entry
- L542 _public function_ `static TSharedPtr<FMP4BoxBase, ESPMode::ThreadSafe> Create(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo)`
- L544 _public prototype_ `virtual ~FMP4BoxAudioSampleEntry() = default;`
- L545 _public function_ `ESampleType GetSampleType() override`
- L547 _public prototype_ `uint16 GetDataReferenceIndex() override;`
- L548 _public prototype_ `uint32 GetSampleRate();`
- L549 _public prototype_ `int32 GetChannelCount();`
- L550 _public prototype_ `int32 GetSampleSize();`
- L551 _public prototype_ `bool HaveFormatSpecificFlags();`
- L552 _public prototype_ `int32 GetFormatSpecificFlags();`
- L553 _public prototype_ `uint32 GetConstBytesPerAudioPacket();`
- L554 _public prototype_ `uint32 GetConstLPCMFramesPerAudioPacket();`
- L556 _protected function_ `FMP4BoxAudioSampleEntry(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo) : FMP4BoxSampleEntry(InParent, InBoxInfo)`
- L559 _protected prototype_ `void ParseIfRequired();`
- L561 _protected member_ `TPimplPtr<FParsed> Parsed;`

#### class `MP4Boxes::FMP4BoxXMLSubtitleSampleEntry`  
`class FMP4BoxXMLSubtitleSampleEntry : public FMP4BoxSampleEntry`  
_L569-584_
- inherits: `FMP4BoxSampleEntry`
- desc: XML subtitle sample entry ISO/IEC 14496-12:2022 - 12.6.3 Sample entry
- L572 _public function_ `static TSharedPtr<FMP4BoxBase, ESPMode::ThreadSafe> Create(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo)`
- L574 _public prototype_ `virtual ~FMP4BoxXMLSubtitleSampleEntry() = default;`
- L575 _public prototype_ `ESampleType GetSampleType() override;`
- L576 _public prototype_ `uint16 GetDataReferenceIndex() override;`
- L578 _protected function_ `FMP4BoxXMLSubtitleSampleEntry(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo) : FMP4BoxSampleEntry(InParent, InBoxInfo)`
- L581 _protected prototype_ `void ParseIfRequired();`
- L583 _protected member_ `TPimplPtr<FParsed> Parsed;`

#### class `MP4Boxes::FMP4BoxWVTTSampleEntry`  
`class FMP4BoxWVTTSampleEntry : public FMP4BoxSampleEntry`  
_L591-606_
- inherits: `FMP4BoxSampleEntry`
- desc: WebVTT sample entry ISO/IEC 14496-30:2018 - 6.5 Sample entry format
- L594 _public function_ `static TSharedPtr<FMP4BoxBase, ESPMode::ThreadSafe> Create(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo)`
- L596 _public prototype_ `virtual ~FMP4BoxWVTTSampleEntry() = default;`
- L597 _public prototype_ `ESampleType GetSampleType() override;`
- L598 _public prototype_ `uint16 GetDataReferenceIndex() override;`
- L600 _protected function_ `FMP4BoxWVTTSampleEntry(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo) : FMP4BoxSampleEntry(InParent, InBoxInfo)`
- L603 _protected prototype_ `void ParseIfRequired();`
- L605 _protected member_ `TPimplPtr<FParsed> Parsed;`

#### class `MP4Boxes::FMP4BoxQTFFTimecodeSampleEntry`  
`class FMP4BoxQTFFTimecodeSampleEntry : public FMP4BoxSampleEntry`  
_L613-642_
- inherits: `FMP4BoxSampleEntry`
- desc: Timecode sample entry Apple QuickTime: https://developer.apple.com/documentation/quicktime-file-format/timecode_sample_description
- L616 _public function_ `static TSharedPtr<FMP4BoxBase, ESPMode::ThreadSafe> Create(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo)`
- L618 _public prototype_ `virtual ~FMP4BoxQTFFTimecodeSampleEntry() = default;`
- L619 _public function_ `ESampleType GetSampleType() override`
- L621 _public prototype_ `uint16 GetDataReferenceIndex() override;`
- L631 _public prototype_ `uint32 GetFlags();`
- L632 _public prototype_ `uint32 GetTimescale();`
- L633 _public prototype_ `uint32 GetFrameDuration();`
- L634 _public prototype_ `uint32 GetNumberOfFrames();`
- L636 _protected function_ `FMP4BoxQTFFTimecodeSampleEntry(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo) : FMP4BoxSampleEntry(InParent, InBoxInfo)`
- L639 _protected prototype_ `void ParseIfRequired();`
- L641 _protected member_ `TPimplPtr<FParsed> Parsed;`

#### enum `MP4Boxes::FMP4BoxQTFFTimecodeSampleEntry::EFlags`  
`enum EFlags : uint32`  
_L624-630_
- desc: See: https://developer.apple.com/documentation/quicktime-file-format/timecode_sample_description/flags
- L626 _public enumerator_ `DropFrame = 0x0001` — Indicates whether the timecode is drop frame. Set it to 1 if the timecode is drop frame.
- L627 _public enumerator_ `Max24Hour = 0x0002` — Indicates whether the timecode wraps after 24 hours. Set it to 1 if the timecode wraps.
- L628 _public enumerator_ `AllowNegativeTimes = 0x0004` — Indicates whether negative time values are allowed. Set it to 1 if the timecode supports negative values.
- L629 _public enumerator_ `Counter = 0x0008` — Indicates whether the time value corresponds to a tape counter value. Set it to 1 if the timecode values are tape counter values.

#### class `MP4Boxes::FMP4BoxTX3GSampleEntry`  
`class FMP4BoxTX3GSampleEntry : public FMP4BoxSampleEntry`  
_L648-663_
- inherits: `FMP4BoxSampleEntry`
- desc: 3GPP / TX3G Text sample entry (ETSI TS 126 245 V11.0.0 - 5.16 Sample Description Format)
- L651 _public function_ `static TSharedPtr<FMP4BoxBase, ESPMode::ThreadSafe> Create(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo)`
- L653 _public prototype_ `virtual ~FMP4BoxTX3GSampleEntry() = default;`
- L654 _public prototype_ `ESampleType GetSampleType() override;`
- L655 _public prototype_ `uint16 GetDataReferenceIndex() override;`
- L657 _protected function_ `FMP4BoxTX3GSampleEntry(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo) : FMP4BoxSampleEntry(InParent, InBoxInfo)`
- L660 _protected prototype_ `void ParseIfRequired();`
- L662 _protected member_ `TPimplPtr<FParsed> Parsed;`

#### class `MP4Boxes::FMP4BoxPASP`  
`class FMP4BoxPASP : public FMP4BoxBase`  
_L670-680_
- inherits: `FMP4BoxBase`
- desc: `pasp` box ISO/IEC 14496-12:2022 - 12.1.4 Pixel Aspect Ratio
- L673 _public function_ `static TSharedPtr<FMP4BoxBase, ESPMode::ThreadSafe> Create(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo)`
- L675 _public prototype_ `virtual ~FMP4BoxPASP() = default;`
- L677 _protected function_ `FMP4BoxPASP(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo) : FMP4BoxBase(InParent, InBoxInfo)`

#### class `MP4Boxes::FMP4BoxCOLR`  
`class FMP4BoxCOLR : public FMP4BoxBase`  
_L687-716_
- inherits: `FMP4BoxBase`
- desc: `colr` box ISO/IEC 14496-12:2022 - 12.1.5 Colour information
- L690 _public function_ `static TSharedPtr<FMP4BoxBase, ESPMode::ThreadSafe> Create(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo)`
- L692 _public prototype_ `virtual ~FMP4BoxCOLR() = default;`
- L707 _public prototype_ `EColorType GetColorType();`
- L708 _public prototype_ `const FColorNCLX& GetColorNCLX();`
- L710 _protected function_ `FMP4BoxCOLR(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo) : FMP4BoxBase(InParent, InBoxInfo)`
- L713 _protected prototype_ `void ParseIfRequired();`
- L715 _protected member_ `TPimplPtr<FParsed> Parsed;`

#### enum `MP4Boxes::FMP4BoxCOLR::EColorType`  
`enum class EColorType`  
_L693-699_
- L695 _public enumerator_ `nclx`
- L696 _public enumerator_ `rICC`
- L697 _public enumerator_ `prof`
- L698 _public enumerator_ `Unsupported`

#### struct `MP4Boxes::FMP4BoxCOLR::FColorNCLX`  
`struct FColorNCLX`  
_L700-706_
- L702 _public member_ `uint16 colour_primaries = 0;`
- L703 _public member_ `uint16 transfer_characteristics = 0;`
- L704 _public member_ `uint16 matrix_coefficients;`
- L705 _public member_ `uint8 full_range_flag = 0;`

#### class `MP4Boxes::FMP4BoxCLLI`  
`class FMP4BoxCLLI : public FMP4BoxBase`  
_L723-737_
- inherits: `FMP4BoxBase`
- desc: `clli` box ISO/IEC 14496-12:2022 - 12.1.6 Content light level
- L726 _public function_ `static TSharedPtr<FMP4BoxBase, ESPMode::ThreadSafe> Create(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo)`
- L728 _public prototype_ `virtual ~FMP4BoxCLLI() = default;`
- L731 _protected function_ `FMP4BoxCLLI(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo) : FMP4BoxBase(InParent, InBoxInfo)`
- L734 _protected prototype_ `void ParseIfRequired();`
- L736 _protected member_ `TPimplPtr<FParsed> Parsed;`

#### class `MP4Boxes::FMP4BoxMDCV`  
`class FMP4BoxMDCV : public FMP4BoxBase`  
_L744-758_
- inherits: `FMP4BoxBase`
- desc: `mdcv` box ISO/IEC 14496-12:2022 - 12.1.7 Mastering display colour volume
- L747 _public function_ `static TSharedPtr<FMP4BoxBase, ESPMode::ThreadSafe> Create(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo)`
- L749 _public prototype_ `virtual ~FMP4BoxMDCV() = default;`
- L752 _protected function_ `FMP4BoxMDCV(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo) : FMP4BoxBase(InParent, InBoxInfo)`
- L755 _protected prototype_ `void ParseIfRequired();`
- L757 _protected member_ `TPimplPtr<FParsed> Parsed;`

#### class `MP4Boxes::FMP4BoxSTSD`  
`class FMP4BoxSTSD : public FMP4BoxBase`  
_L765-801_
- inherits: `FMP4BoxBase`
- desc: `stsd` box ISO/IEC 14496-12:2022 - 8.5.2 Sample description box
- L768 _public function_ `static TSharedPtr<FMP4BoxBase, ESPMode::ThreadSafe> Create(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo)`
- L770 _public prototype_ `virtual ~FMP4BoxSTSD() = default;`
- L771 _public function_ `bool IsLeafBox() const override`
- L772 _public function_ `bool IsListOfEntries() const override`
- L774 _public prototype_ `uint8 GetBoxVersion();`
- L775 _public prototype_ `FMP4BoxSampleEntry::ESampleType GetSampleType();`
- L778 _public function_ `template<typename T> void GetSampleDescriptions(TArray<TSharedPtr<T, ESPMode::ThreadSafe>>& OutChildren)`
- L795 _protected function_ `FMP4BoxSTSD(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo) : FMP4BoxBase(InParent, InBoxInfo)`
- L798 _protected prototype_ `void ParseIfRequired();`
- L800 _protected member_ `TPimplPtr<FParsed> Parsed;`

#### class `MP4Boxes::FMP4BoxSTTS`  
`class FMP4BoxSTTS : public FMP4BoxBase`  
_L808-831_
- inherits: `FMP4BoxBase`
- desc: `stts` box ISO/IEC 14496-12:2022 - 8.6.1.2 Decoding time to sample box
- L811 _public function_ `static TSharedPtr<FMP4BoxBase, ESPMode::ThreadSafe> Create(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo)`
- L813 _public prototype_ `virtual ~FMP4BoxSTTS() = default;`
- L819 _public prototype_ `const TArray<FEntry>& GetEntries();`
- L820 _public prototype_ `uint32 GetNumTotalSamples();`
- L821 _public prototype_ `int64 GetTotalDuration();`
- L822 _public prototype_ `bool HasConstantSampleDuration();`
- L823 _public prototype_ `int64 GetConstantSampleDuration();`
- L825 _protected function_ `FMP4BoxSTTS(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo) : FMP4BoxBase(InParent, InBoxInfo)`
- L828 _protected prototype_ `void ParseIfRequired();`
- L830 _protected member_ `TPimplPtr<FParsed> Parsed;`

#### struct `MP4Boxes::FMP4BoxSTTS::FEntry`  
`struct FEntry`  
_L814-818_
- L816 _public member_ `uint32 sample_count = 0;`
- L817 _public member_ `uint32 sample_delta = 0;`

#### class `MP4Boxes::FMP4BoxCTTS`  
`class FMP4BoxCTTS : public FMP4BoxBase`  
_L838-860_
- inherits: `FMP4BoxBase`
- desc: `ctts` box ISO/IEC 14496-12:2022 - 8.6.1.3 Composition time to sample box
- L841 _public function_ `static TSharedPtr<FMP4BoxBase, ESPMode::ThreadSafe> Create(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo)`
- L843 _public prototype_ `virtual ~FMP4BoxCTTS() = default;`
- L850 _public prototype_ `uint8 GetBoxVersion();`
- L851 _public prototype_ `const TArray<FEntry>& GetEntries();`
- L852 _public prototype_ `uint32 GetNumTotalSamples();`
- L854 _protected function_ `FMP4BoxCTTS(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo) : FMP4BoxBase(InParent, InBoxInfo)`
- L857 _protected prototype_ `void ParseIfRequired();`
- L859 _protected member_ `TPimplPtr<FParsed> Parsed;`

#### struct `MP4Boxes::FMP4BoxCTTS::FEntry`  
`struct FEntry`  
_L844-849_
- L847 _public member_ `int64 sample_offset = 0;` — A 64 bit value used here to hold both signed values (version 1) and 32 bit unsigned values (version 0).
- L848 _public member_ `uint32 sample_count = 0;`

#### class `MP4Boxes::FMP4BoxCSLG`  
`class FMP4BoxCSLG : public FMP4BoxBase`  
_L867-877_
- inherits: `FMP4BoxBase`
- desc: `cslg` box ISO/IEC 14496-12:2022 - 8.6.1.4 Composition to decode box
- L870 _public function_ `static TSharedPtr<FMP4BoxBase, ESPMode::ThreadSafe> Create(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo)`
- L872 _public prototype_ `virtual ~FMP4BoxCSLG() = default;`
- L874 _protected function_ `FMP4BoxCSLG(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo) : FMP4BoxBase(InParent, InBoxInfo)`

#### class `MP4Boxes::FMP4BoxSTSS`  
`class FMP4BoxSTSS : public FMP4BoxBase`  
_L884-898_
- inherits: `FMP4BoxBase`
- desc: `stss` box ISO/IEC 14496-12:2022 - 8.6.2 Sync sample box
- L887 _public function_ `static TSharedPtr<FMP4BoxBase, ESPMode::ThreadSafe> Create(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo)`
- L889 _public prototype_ `virtual ~FMP4BoxSTSS() = default;`
- L890 _public prototype_ `const TArray<uint32>& GetEntries();`
- L892 _protected function_ `FMP4BoxSTSS(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo) : FMP4BoxBase(InParent, InBoxInfo)`
- L895 _protected prototype_ `void ParseIfRequired();`
- L897 _protected member_ `TPimplPtr<FParsed> Parsed;`

#### class `MP4Boxes::FMP4BoxSDTP`  
`class FMP4BoxSDTP : public FMP4BoxBase`  
_L905-919_
- inherits: `FMP4BoxBase`
- desc: `sdtp` box ISO/IEC 14496-12:2022 - 8.6.4 Independent and disposable samples box
- L908 _public function_ `static TSharedPtr<FMP4BoxBase, ESPMode::ThreadSafe> Create(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo)`
- L910 _public prototype_ `virtual ~FMP4BoxSDTP() = default;`
- L911 _public prototype_ `TConstArrayView<uint8> GetEntries();`
- L913 _protected function_ `FMP4BoxSDTP(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo) : FMP4BoxBase(InParent, InBoxInfo)`
- L916 _protected prototype_ `void ParseIfRequired();`
- L918 _protected member_ `TPimplPtr<FParsed> Parsed;`

#### class `MP4Boxes::FMP4BoxSTSC`  
`class FMP4BoxSTSC : public FMP4BoxBase`  
_L926-946_
- inherits: `FMP4BoxBase`
- desc: `stsc` box ISO/IEC 14496-12:2022 - 8.7.4 Sample to chunk box
- L929 _public function_ `static TSharedPtr<FMP4BoxBase, ESPMode::ThreadSafe> Create(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo)`
- L931 _public prototype_ `virtual ~FMP4BoxSTSC() = default;`
- L938 _public prototype_ `const TArray<FEntry>& GetEntries();`
- L940 _protected function_ `FMP4BoxSTSC(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo) : FMP4BoxBase(InParent, InBoxInfo)`
- L943 _protected prototype_ `void ParseIfRequired();`
- L945 _protected member_ `TPimplPtr<FParsed> Parsed;`

#### struct `MP4Boxes::FMP4BoxSTSC::FEntry`  
`struct FEntry`  
_L932-937_
- L934 _public member_ `uint32 first_chunk = 0;`
- L935 _public member_ `uint32 samples_per_chunk = 0;`
- L936 _public member_ `uint32 sample_description_index = 0;`

#### class `MP4Boxes::FMP4BoxSTSZ`  
`class FMP4BoxSTSZ : public FMP4BoxBase`  
_L953-977_
- inherits: `FMP4BoxBase`
- desc: `stsz` / `stz2` box ISO/IEC 14496-12:2022 - 8.7.3 Sample size boxes
- L956 _public function_ `static TSharedPtr<FMP4BoxBase, ESPMode::ThreadSafe> Create(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo)`
- L958 _public prototype_ `virtual ~FMP4BoxSTSZ() = default;`
- L959 _public function_ `uint32 GetType() const override`
- L966 _public prototype_ `uint32 GetNumberOfSamples();`
- L967 _public prototype_ `uint32 GetSizeOfSample(uint32 InIndex);`
- L968 _public prototype_ `bool HasConstantSampleSize();`
- L969 _public prototype_ `uint32 GetConstantSampleSize();`
- L971 _protected function_ `FMP4BoxSTSZ(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo) : FMP4BoxBase(InParent, InBoxInfo)`
- L974 _protected prototype_ `void ParseIfRequired();`
- L976 _protected member_ `TPimplPtr<FParsed> Parsed;`

#### class `MP4Boxes::FMP4BoxSTCO`  
`class FMP4BoxSTCO : public FMP4BoxBase`  
_L984-1006_
- inherits: `FMP4BoxBase`
- desc: `stco` box, `co64` box ISO/IEC 14496-12:2022 - 8.7.5 Chunk offset box
- L987 _public function_ `static TSharedPtr<FMP4BoxBase, ESPMode::ThreadSafe> Create(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo)`
- L989 _public prototype_ `virtual ~FMP4BoxSTCO() = default;`
- L990 _public function_ `uint32 GetType() const override`
- L997 _public prototype_ `uint32 GetNumberOfEntries();`
- L998 _public prototype_ `uint64 GetChunkOffset(uint32 InIndex);`
- L1000 _protected function_ `FMP4BoxSTCO(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo) : FMP4BoxBase(InParent, InBoxInfo)`
- L1003 _protected prototype_ `void ParseIfRequired();`
- L1005 _protected member_ `TPimplPtr<FParsed> Parsed;`

#### class `MP4Boxes::FMP4BoxSUBS`  
`class FMP4BoxSUBS : public FMP4BoxBase`  
_L1013-1049_
- inherits: `FMP4BoxBase`
- desc: `subs` box ISO/IEC 14496-12:2022 - 8.7.7 Sub-sample information box
- L1016 _public function_ `static TSharedPtr<FMP4BoxBase, ESPMode::ThreadSafe> Create(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo)`
- L1018 _public prototype_ `virtual ~FMP4BoxSUBS() = default;`
- L1020 _public prototype_ `uint32 GetFlags();`
- L1030 _public typedef_ `using FSubsampleList = TChunkedArray<FSubsample, 16>;`
- L1040 _public prototype_ `const TArray<FEntry>& GetEntries();`
- L1043 _protected function_ `FMP4BoxSUBS(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo) : FMP4BoxBase(InParent, InBoxInfo)`
- L1046 _protected prototype_ `void ParseIfRequired();`
- L1048 _protected member_ `TPimplPtr<FParsed> Parsed;`

#### struct `MP4Boxes::FMP4BoxSUBS::FSubsample`  
`struct FSubsample`  
_L1022-1029_
- L1024 _public member_ `uint32 codec_specific_parameters = 0;`
- L1025 _public member_ `uint32 subsample_size = 0;`
- L1026 _public member_ `uint32 subsample_offset = 0;` — calculated for convenience.
- L1027 _public member_ `uint8 subsample_priority = 0;`
- L1028 _public member_ `uint8 discardable = 0;`

#### struct `MP4Boxes::FMP4BoxSUBS::FEntry`  
`struct FEntry`  
_L1031-1039_
- L1033 _public member_ `uint32 FirstSampleNumber = 0;` — Sample number starts at 1, so 0 is not valid.
- L1034 _public member_ `FSubsampleList SubSamples;`
- L1035 _public function_ `uint32 GetSampleNumber() const`
- L1037 _public function_ `const FSubsampleList& GetEntries() const`

#### class `MP4Boxes::FMP4BoxSAIZ`  
`class FMP4BoxSAIZ : public FMP4BoxBase`  
_L1056-1074_
- inherits: `FMP4BoxBase`
- desc: `saiz` box ISO/IEC 14496-12:2022 - 8.7.8 Sample auxiliary information sizes box
- L1059 _public function_ `static TSharedPtr<FMP4BoxBase, ESPMode::ThreadSafe> Create(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo)`
- L1061 _public prototype_ `virtual ~FMP4BoxSAIZ() = default;`
- L1062 _public prototype_ `bool HasAuxInfoType();`
- L1063 _public prototype_ `uint32 GetAuxInfoType();`
- L1064 _public prototype_ `uint32 GetAuxInfoTypeParameter();`
- L1065 _public prototype_ `uint32 GetSampleCount();`
- L1066 _public prototype_ `uint8 GetSampleInfoSize(uint32 InForSampleNumber);`
- L1068 _protected function_ `FMP4BoxSAIZ(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo) : FMP4BoxBase(InParent, InBoxInfo)`
- L1071 _protected prototype_ `void ParseIfRequired();`
- L1073 _protected member_ `TPimplPtr<FParsed> Parsed;`

#### class `MP4Boxes::FMP4BoxSAIO`  
`class FMP4BoxSAIO : public FMP4BoxBase`  
_L1081-1099_
- inherits: `FMP4BoxBase`
- desc: `saio` box ISO/IEC 14496-12:2022 - 8.7.9 Sample auxiliary information offsets box
- L1084 _public function_ `static TSharedPtr<FMP4BoxBase, ESPMode::ThreadSafe> Create(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo)`
- L1086 _public prototype_ `virtual ~FMP4BoxSAIO() = default;`
- L1087 _public prototype_ `bool HasAuxInfoType();`
- L1088 _public prototype_ `uint32 GetAuxInfoType();`
- L1089 _public prototype_ `uint32 GetAuxInfoTypeParameter();`
- L1090 _public prototype_ `uint32 GetEntryCount();`
- L1091 _public prototype_ `uint64 GetEntry(uint32 InForEntryNumber);`
- L1093 _protected function_ `FMP4BoxSAIO(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo) : FMP4BoxBase(InParent, InBoxInfo)`
- L1096 _protected prototype_ `void ParseIfRequired();`
- L1098 _protected member_ `TPimplPtr<FParsed> Parsed;`

#### class `MP4Boxes::FMP4BoxSGPD`  
`class FMP4BoxSGPD : public FMP4BoxBase`  
_L1106-1123_
- inherits: `FMP4BoxBase`
- desc: `sgpd` box ISO/IEC 14496-12:2022 - 8.9.3 Sample group description box
- L1109 _public function_ `static TSharedPtr<FMP4BoxBase, ESPMode::ThreadSafe> Create(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo)`
- L1111 _public prototype_ `virtual ~FMP4BoxSGPD() = default;`
- L1113 _public prototype_ `uint32 GetGroupingType();`
- L1114 _public prototype_ `const TArray<TConstArrayView<uint8>>& GetGroupDescriptionEntries();`
- L1115 _public prototype_ `uint32 GetDefaultGroupDescriptionIndex();`
- L1117 _protected function_ `FMP4BoxSGPD(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo) : FMP4BoxBase(InParent, InBoxInfo)`
- L1120 _protected prototype_ `void ParseIfRequired();`
- L1122 _protected member_ `TPimplPtr<FParsed> Parsed;`

#### class `MP4Boxes::FMP4BoxSBGP`  
`class FMP4BoxSBGP : public FMP4BoxBase`  
_L1130-1154_
- inherits: `FMP4BoxBase`
- desc: `sbgp` box ISO/IEC 14496-12:2022 - 8.9.2 Sample to group box
- L1133 _public function_ `static TSharedPtr<FMP4BoxBase, ESPMode::ThreadSafe> Create(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo)`
- L1135 _public prototype_ `virtual ~FMP4BoxSBGP() = default;`
- L1143 _public prototype_ `uint32 GetGroupingType();`
- L1144 _public prototype_ `uint32 GetGroupingTypeParameter();`
- L1145 _public prototype_ `const TArray<FEntry>& GetEntries();`
- L1146 _public prototype_ `uint32 GetNumTotalSamples();`
- L1148 _protected function_ `FMP4BoxSBGP(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo) : FMP4BoxBase(InParent, InBoxInfo)`
- L1151 _protected prototype_ `void ParseIfRequired();`
- L1153 _protected member_ `TPimplPtr<FParsed> Parsed;`

#### struct `MP4Boxes::FMP4BoxSBGP::FEntry`  
`struct FEntry`  
_L1137-1141_
- L1139 _public member_ `uint32 sample_count = 0;`
- L1140 _public member_ `uint32 group_description_index = 0;`

#### class `MP4Boxes::FMP4BoxMVEX`  
`class FMP4BoxMVEX : public FMP4BoxBase`  
_L1161-1172_
- inherits: `FMP4BoxBase`
- desc: `mvex` box ISO/IEC 14496-12:2022 - 8.8.1 Movie extends box
- L1164 _public function_ `static TSharedPtr<FMP4BoxBase, ESPMode::ThreadSafe> Create(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo)`
- L1166 _public prototype_ `virtual ~FMP4BoxMVEX() = default;`
- L1167 _public function_ `bool IsLeafBox() const override`
- L1169 _protected function_ `FMP4BoxMVEX(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo) : FMP4BoxBase(InParent, InBoxInfo)`

#### class `MP4Boxes::FMP4BoxMEHD`  
`class FMP4BoxMEHD : public FMP4BoxBase`  
_L1179-1197_
- inherits: `FMP4BoxBase`
- desc: `mehd` box ISO/IEC 14496-12:2022 - 8.8.2 Movie extends header box
- L1182 _public function_ `static TSharedPtr<FMP4BoxBase, ESPMode::ThreadSafe> Create(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo)`
- L1184 _public prototype_ `virtual ~FMP4BoxMEHD() = default;`
- L1189 _public prototype_ `int64 GetFragmentDuration();` — Returns the fragment duration in the timescale of the `mvhd` box. This is just the value as stored in the box. You need to apply the timescale yourself.
- L1191 _protected function_ `FMP4BoxMEHD(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo) : FMP4BoxBase(InParent, InBoxInfo)`
- L1194 _protected prototype_ `void ParseIfRequired();`
- L1196 _protected member_ `TPimplPtr<FParsed> Parsed;`

#### class `MP4Boxes::FMP4BoxTREX`  
`class FMP4BoxTREX : public FMP4BoxBase`  
_L1204-1222_
- inherits: `FMP4BoxBase`
- desc: `trex` box ISO/IEC 14496-12:2022 - 8.8.3 Track extends box
- L1207 _public function_ `static TSharedPtr<FMP4BoxBase, ESPMode::ThreadSafe> Create(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo)`
- L1209 _public prototype_ `virtual ~FMP4BoxTREX() = default;`
- L1210 _public prototype_ `uint32 GetTrackID();`
- L1211 _public prototype_ `uint32 GetDefaultSampleDescriptionIndex();`
- L1212 _public prototype_ `uint32 GetDefaultSampleDuration();`
- L1213 _public prototype_ `uint32 GetDefaultSampleSize();`
- L1214 _public prototype_ `uint32 GetDefaultSampleFlags();`
- L1216 _protected function_ `FMP4BoxTREX(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo) : FMP4BoxBase(InParent, InBoxInfo)`
- L1219 _protected prototype_ `void ParseIfRequired();`
- L1221 _protected member_ `TPimplPtr<FParsed> Parsed;`

#### class `MP4Boxes::FMP4BoxLEVA`  
`class FMP4BoxLEVA : public FMP4BoxBase`  
_L1229-1239_
- inherits: `FMP4BoxBase`
- desc: `leva` box ISO/IEC 14496-12:2022 - 8.8.13 Level assignment box
- L1232 _public function_ `static TSharedPtr<FMP4BoxBase, ESPMode::ThreadSafe> Create(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo)`
- L1234 _public prototype_ `virtual ~FMP4BoxLEVA() = default;`
- L1236 _protected function_ `FMP4BoxLEVA(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo) : FMP4BoxBase(InParent, InBoxInfo)`

#### class `MP4Boxes::FMP4BoxPRFT`  
`class FMP4BoxPRFT : public FMP4BoxBase`  
_L1246-1282_
- inherits: `FMP4BoxBase`
- desc: `prft` box ISO/IEC 14496-12:2022 - 8.16.5 Producer reference time box
- L1249 _public function_ `static TSharedPtr<FMP4BoxBase, ESPMode::ThreadSafe> Create(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo)`
- L1251 _public prototype_ `virtual ~FMP4BoxPRFT() = default;`
- L1262 _public prototype_ `uint32 GetFlags();`
- L1263 _public prototype_ `uint32 GetReferenceTrackID();`
- L1264 _public prototype_ `uint64 GetNTPTimestamp();`
- L1265 _public prototype_ `uint64 GetMediaTime();`
- L1266 _public function_ `EReferenceType GetReferenceType()`
- L1276 _protected function_ `FMP4BoxPRFT(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo) : FMP4BoxBase(InParent, InBoxInfo)`
- L1279 _protected prototype_ `void ParseIfRequired();`
- L1281 _protected member_ `TPimplPtr<FParsed> Parsed;`

#### enum `MP4Boxes::FMP4BoxPRFT::EReferenceType`  
`enum class EReferenceType`  
_L1253-1260_
- L1255 _public enumerator_ `Undefined`
- L1256 _public enumerator_ `Encoder` — Input or output. If distinction is needed, look at the flags.
- L1257 _public enumerator_ `Writer` — Fragment written or finalized. If distinction is needed, look at the flags.
- L1258 _public enumerator_ `Captured` — Flags == 8|16
- L1259 _public enumerator_ `Application` — Flags == 8 (also Flags == 16 despite this not being defined to be set alone)

#### class `MP4Boxes::FMP4BoxMOOF`  
`class FMP4BoxMOOF : public FMP4BoxBase`  
_L1289-1300_
- inherits: `FMP4BoxBase`
- desc: `moof` box ISO/IEC 14496-12:2022 - 8.8.4 Movie fragment box
- L1292 _public function_ `static TSharedPtr<FMP4BoxBase, ESPMode::ThreadSafe> Create(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo)`
- L1294 _public prototype_ `virtual ~FMP4BoxMOOF() = default;`
- L1295 _public function_ `bool IsLeafBox() const override`
- L1297 _protected function_ `FMP4BoxMOOF(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo) : FMP4BoxBase(InParent, InBoxInfo)`

#### class `MP4Boxes::FMP4BoxMFHD`  
`class FMP4BoxMFHD : public FMP4BoxBase`  
_L1307-1321_
- inherits: `FMP4BoxBase`
- desc: `mfhd` box ISO/IEC 14496-12:2022 - 8.8.5 Movie fragment header box
- L1310 _public function_ `static TSharedPtr<FMP4BoxBase, ESPMode::ThreadSafe> Create(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo)`
- L1312 _public prototype_ `virtual ~FMP4BoxMFHD() = default;`
- L1313 _public prototype_ `uint32 GetSequenceNumber();`
- L1315 _protected function_ `FMP4BoxMFHD(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo) : FMP4BoxBase(InParent, InBoxInfo)`
- L1318 _protected prototype_ `void ParseIfRequired();`
- L1320 _protected member_ `TPimplPtr<FParsed> Parsed;`

#### class `MP4Boxes::FMP4BoxTRAF`  
`class FMP4BoxTRAF : public FMP4BoxBase`  
_L1328-1339_
- inherits: `FMP4BoxBase`
- desc: `traf` box ISO/IEC 14496-12:2022 - 8.8.6 Track fragment box
- L1331 _public function_ `static TSharedPtr<FMP4BoxBase, ESPMode::ThreadSafe> Create(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo)`
- L1333 _public prototype_ `virtual ~FMP4BoxTRAF() = default;`
- L1334 _public function_ `bool IsLeafBox() const override`
- L1336 _protected function_ `FMP4BoxTRAF(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo) : FMP4BoxBase(InParent, InBoxInfo)`

#### class `MP4Boxes::FMP4BoxTFHD`  
`class FMP4BoxTFHD : public FMP4BoxBase`  
_L1346-1373_
- inherits: `FMP4BoxBase`
- desc: `tfhd` box ISO/IEC 14496-12:2022 - 8.8.7 Track fragment header box
- L1349 _public function_ `static TSharedPtr<FMP4BoxBase, ESPMode::ThreadSafe> Create(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo)`
- L1351 _public prototype_ `virtual ~FMP4BoxTFHD() = default;`
- L1353 _public prototype_ `uint32 GetTrackID();`
- L1354 _public prototype_ `bool HasBaseDataOffset();`
- L1355 _public prototype_ `uint64 GetBaseDataOffset();`
- L1356 _public prototype_ `bool HasSampleDescriptionIndex();`
- L1357 _public prototype_ `uint32 GetSampleDescriptionIndex();`
- L1358 _public prototype_ `bool HasDefaultSampleDuration();`
- L1359 _public prototype_ `uint32 GetDefaultSampleDuration();`
- L1360 _public prototype_ `bool HasDefaultSampleSize();`
- L1361 _public prototype_ `uint32 GetDefaultSampleSize();`
- L1362 _public prototype_ `bool HasDefaultSampleFlags();`
- L1363 _public prototype_ `uint32 GetDefaultSampleFlags();`
- L1364 _public prototype_ `bool IsDurationEmpty();`
- L1365 _public prototype_ `bool IsMoofDefaultBase();`
- L1367 _protected function_ `FMP4BoxTFHD(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo) : FMP4BoxBase(InParent, InBoxInfo)`
- L1370 _protected prototype_ `void ParseIfRequired();`
- L1372 _protected member_ `TPimplPtr<FParsed> Parsed;`

#### class `MP4Boxes::FMP4BoxTRUN`  
`class FMP4BoxTRUN : public FMP4BoxBase`  
_L1380-1408_
- inherits: `FMP4BoxBase`
- desc: `trun` box ISO/IEC 14496-12:2022 - 8.8.8 Track fragment run box
- L1383 _public function_ `static TSharedPtr<FMP4BoxBase, ESPMode::ThreadSafe> Create(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo)`
- L1385 _public prototype_ `virtual ~FMP4BoxTRUN() = default;`
- L1386 _public prototype_ `uint32 GetNumberOfSamples();`
- L1387 _public prototype_ `bool HasSampleOffset();`
- L1388 _public prototype_ `int32 GetSampleOffset();`
- L1389 _public prototype_ `bool HasFirstSampleFlags();`
- L1390 _public prototype_ `uint32 GetFirstSampleFlags();`
- L1391 _public prototype_ `bool HasSampleDurations();`
- L1392 _public prototype_ `const TArray<uint32>& GetSampleDurations();`
- L1393 _public prototype_ `bool HasSampleSizes();`
- L1394 _public prototype_ `const TArray<uint32>& GetSampleSizes();`
- L1395 _public prototype_ `int64 GetTotalSampleSize();`
- L1396 _public prototype_ `bool HasSampleFlags();`
- L1397 _public prototype_ `const TArray<uint32>& GetSampleFlags();`
- L1398 _public prototype_ `bool HasSampleCompositionTimeOffsets();`
- L1399 _public prototype_ `const TArray<int32>& GetSampleCompositionTimeOffsets();`
- L1400 _public prototype_ `int64 GetTotalDuration();`
- L1402 _protected function_ `FMP4BoxTRUN(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo) : FMP4BoxBase(InParent, InBoxInfo)`
- L1405 _protected prototype_ `void ParseIfRequired();`
- L1407 _protected member_ `TPimplPtr<FParsed> Parsed;`

#### class `MP4Boxes::FMP4BoxMFRA`  
`class FMP4BoxMFRA : public FMP4BoxBase`  
_L1415-1426_
- inherits: `FMP4BoxBase`
- desc: `mfra` box ISO/IEC 14496-12:2022 - 8.8.9 Movie fragment random access box
- L1418 _public function_ `static TSharedPtr<FMP4BoxBase, ESPMode::ThreadSafe> Create(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo)`
- L1420 _public prototype_ `virtual ~FMP4BoxMFRA() = default;`
- L1421 _public function_ `bool IsLeafBox() const override`
- L1423 _protected function_ `FMP4BoxMFRA(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo) : FMP4BoxBase(InParent, InBoxInfo)`

#### class `MP4Boxes::FMP4BoxTFRA`  
`class FMP4BoxTFRA : public FMP4BoxBase`  
_L1433-1443_
- inherits: `FMP4BoxBase`
- desc: `tfra` box ISO/IEC 14496-12:2022 - 8.8.10 Track fragment random access box
- L1436 _public function_ `static TSharedPtr<FMP4BoxBase, ESPMode::ThreadSafe> Create(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo)`
- L1438 _public prototype_ `virtual ~FMP4BoxTFRA() = default;`
- L1440 _protected function_ `FMP4BoxTFRA(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo) : FMP4BoxBase(InParent, InBoxInfo)`

#### class `MP4Boxes::FMP4BoxMFRO`  
`class FMP4BoxMFRO : public FMP4BoxBase`  
_L1450-1460_
- inherits: `FMP4BoxBase`
- desc: `mfro` box ISO/IEC 14496-12:2022 - 8.8.11 Movie fragment random access offset box
- L1453 _public function_ `static TSharedPtr<FMP4BoxBase, ESPMode::ThreadSafe> Create(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo)`
- L1455 _public prototype_ `virtual ~FMP4BoxMFRO() = default;`
- L1457 _protected function_ `FMP4BoxMFRO(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo) : FMP4BoxBase(InParent, InBoxInfo)`

#### class `MP4Boxes::FMP4BoxTFDT`  
`class FMP4BoxTFDT : public FMP4BoxBase`  
_L1467-1481_
- inherits: `FMP4BoxBase`
- desc: `tfdt` box ISO/IEC 14496-12:2022 - 8.8.12 Track fragment decode time box
- L1470 _public function_ `static TSharedPtr<FMP4BoxBase, ESPMode::ThreadSafe> Create(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo)`
- L1472 _public prototype_ `virtual ~FMP4BoxTFDT() = default;`
- L1473 _public prototype_ `uint64 GetBaseMediaDecodeTime();`
- L1475 _protected function_ `FMP4BoxTFDT(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo) : FMP4BoxBase(InParent, InBoxInfo)`
- L1478 _protected prototype_ `void ParseIfRequired();`
- L1480 _protected member_ `TPimplPtr<FParsed> Parsed;`

#### class `MP4Boxes::FMP4BoxSIDX`  
`class FMP4BoxSIDX : public FMP4BoxBase`  
_L1488-1516_
- inherits: `FMP4BoxBase`
- desc: `sidx` box ISO/IEC 14496-12:2022 - 8.16.3 Segment index box
- L1491 _public function_ `static TSharedPtr<FMP4BoxBase, ESPMode::ThreadSafe> Create(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo)`
- L1493 _public prototype_ `virtual ~FMP4BoxSIDX() = default;`
- L1503 _public typedef_ `using FEntryList = TChunkedArray<FEntry, 1024>;`
- L1504 _public prototype_ `uint32 GetReferenceID();`
- L1505 _public prototype_ `uint32 GetTimescale();`
- L1506 _public prototype_ `uint64 GetEarliestPresentationTime();`
- L1507 _public prototype_ `uint64 GetFirstOffset();`
- L1508 _public prototype_ `const FEntryList& GetEntries();`
- L1510 _protected function_ `FMP4BoxSIDX(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo) : FMP4BoxBase(InParent, InBoxInfo)`
- L1513 _protected prototype_ `void ParseIfRequired();`
- L1515 _protected member_ `TPimplPtr<FParsed> Parsed;`

#### struct `MP4Boxes::FMP4BoxSIDX::FEntry`  
`struct FEntry`  
_L1494-1502_
- L1496 _public member_ `uint32 SubSegmentDuration;`
- L1497 _public member_ `uint32 IsReferenceType : 1;`
- L1498 _public member_ `uint32 Size : 31;`
- L1499 _public member_ `uint32 StartsWithSAP : 1;`
- L1500 _public member_ `uint32 SAPType : 3;`
- L1501 _public member_ `uint32 SAPDeltaTime : 28;`

#### class `MP4Boxes::FMP4BoxSSIX`  
`class FMP4BoxSSIX : public FMP4BoxBase`  
_L1523-1533_
- inherits: `FMP4BoxBase`
- desc: `ssix` box ISO/IEC 14496-12:2022 - 8.16.4 Subsegment index box
- L1526 _public function_ `static TSharedPtr<FMP4BoxBase, ESPMode::ThreadSafe> Create(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo)`
- L1528 _public prototype_ `virtual ~FMP4BoxSSIX() = default;`
- L1530 _protected function_ `FMP4BoxSSIX(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo) : FMP4BoxBase(InParent, InBoxInfo)`

#### class `MP4Boxes::FMP4BoxVMHD`  
`class FMP4BoxVMHD : public FMP4BoxBase`  
_L1540-1550_
- inherits: `FMP4BoxBase`
- desc: `vmhd` box ISO/IEC 14496-12:2022 - 12.1.2 Video media header
- L1543 _public function_ `static TSharedPtr<FMP4BoxBase, ESPMode::ThreadSafe> Create(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo)`
- L1545 _public prototype_ `virtual ~FMP4BoxVMHD() = default;`
- L1547 _protected function_ `FMP4BoxVMHD(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo) : FMP4BoxBase(InParent, InBoxInfo)`

#### class `MP4Boxes::FMP4BoxSMHD`  
`class FMP4BoxSMHD : public FMP4BoxBase`  
_L1557-1567_
- inherits: `FMP4BoxBase`
- desc: `smhd` box ISO/IEC 14496-12:2022 - 12.2.2 Sound media header
- L1560 _public function_ `static TSharedPtr<FMP4BoxBase, ESPMode::ThreadSafe> Create(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo)`
- L1562 _public prototype_ `virtual ~FMP4BoxSMHD() = default;`
- L1564 _protected function_ `FMP4BoxSMHD(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo) : FMP4BoxBase(InParent, InBoxInfo)`

#### class `MP4Boxes::FMP4BoxSTHD`  
`class FMP4BoxSTHD : public FMP4BoxBase`  
_L1574-1584_
- inherits: `FMP4BoxBase`
- desc: `sthd` box ISO/IEC 14496-12:2022 - 12.6.2 Subtitle media header
- L1577 _public function_ `static TSharedPtr<FMP4BoxBase, ESPMode::ThreadSafe> Create(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo)`
- L1579 _public prototype_ `virtual ~FMP4BoxSTHD() = default;`
- L1581 _protected function_ `FMP4BoxSTHD(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo) : FMP4BoxBase(InParent, InBoxInfo)`

#### class `MP4Boxes::FMP4BoxNMHD`  
`class FMP4BoxNMHD : public FMP4BoxBase`  
_L1591-1601_
- inherits: `FMP4BoxBase`
- desc: `nmhd` box ISO/IEC 14496-12:2022 - 8.4.5.2 Null media header box
- L1594 _public function_ `static TSharedPtr<FMP4BoxBase, ESPMode::ThreadSafe> Create(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo)`
- L1596 _public prototype_ `virtual ~FMP4BoxNMHD() = default;`
- L1598 _protected function_ `FMP4BoxNMHD(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo) : FMP4BoxBase(InParent, InBoxInfo)`

#### class `MP4Boxes::FMP4BoxGMHD`  
`class FMP4BoxGMHD : public FMP4BoxBase`  
_L1608-1618_
- inherits: `FMP4BoxBase`
- desc: `gmhd` box Apple QuickTime: https://developer.apple.com/documentation/quicktime-file-format/base_media_information_header_atom
- L1611 _public function_ `static TSharedPtr<FMP4BoxBase, ESPMode::ThreadSafe> Create(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo)`
- L1613 _public prototype_ `virtual ~FMP4BoxGMHD() = default;`
- L1615 _protected function_ `FMP4BoxGMHD(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo) : FMP4BoxBase(InParent, InBoxInfo)`

#### class `MP4Boxes::FMP4BoxUDTA`  
`class FMP4BoxUDTA : public FMP4BoxBase`  
_L1625-1636_
- inherits: `FMP4BoxBase`
- desc: `udta` box ISO/IEC 14496-12:2022 - 8.10.1 User data box
- L1628 _public function_ `static TSharedPtr<FMP4BoxBase, ESPMode::ThreadSafe> Create(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo)`
- L1630 _public prototype_ `virtual ~FMP4BoxUDTA() = default;`
- L1631 _public function_ `bool IsLeafBox() const override`
- L1633 _protected function_ `FMP4BoxUDTA(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo) : FMP4BoxBase(InParent, InBoxInfo)`

#### class `MP4Boxes::FMP4BoxMETA`  
`class FMP4BoxMETA : public FMP4BoxBase`  
_L1643-1659_
- inherits: `FMP4BoxBase`
- desc: `meta` box ISO/IEC 14496-12:2022 - 8.11.1 MetaBox
- L1646 _public function_ `static TSharedPtr<FMP4BoxBase, ESPMode::ThreadSafe> Create(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo)`
- L1648 _public prototype_ `virtual ~FMP4BoxMETA() = default;`
- L1649 _public function_ `bool IsLeafBox() const override`
- L1650 _public function_ `bool IsListOfEntries() const override`
- L1651 _public prototype_ `TSharedPtr<FMP4BoxHDLR, ESPMode::ThreadSafe> GetHandler();`
- L1653 _protected function_ `FMP4BoxMETA(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo) : FMP4BoxBase(InParent, InBoxInfo)`
- L1656 _protected prototype_ `void ParseIfRequired();`
- L1658 _protected member_ `TPimplPtr<FParsed> Parsed;`

#### class `MP4Boxes::FMP4BoxSINF`  
`class FMP4BoxSINF : public FMP4BoxBase`  
_L1666-1677_
- inherits: `FMP4BoxBase`
- desc: `sinf` box ISO/IEC 14496-12:2022 - 8.12.2 Protection scheme information box
- L1669 _public function_ `static TSharedPtr<FMP4BoxBase, ESPMode::ThreadSafe> Create(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo)`
- L1671 _public prototype_ `virtual ~FMP4BoxSINF() = default;`
- L1672 _public function_ `bool IsLeafBox() const override`
- L1674 _protected function_ `FMP4BoxSINF(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo) : FMP4BoxBase(InParent, InBoxInfo)`

#### class `MP4Boxes::FMP4BoxFRMA`  
`class FMP4BoxFRMA : public FMP4BoxBase`  
_L1684-1698_
- inherits: `FMP4BoxBase`
- desc: `frma` box ISO/IEC 14496-12:2022 - 8.12.3 Original format box
- L1687 _public function_ `static TSharedPtr<FMP4BoxBase, ESPMode::ThreadSafe> Create(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo)`
- L1689 _public prototype_ `virtual ~FMP4BoxFRMA() = default;`
- L1690 _public prototype_ `uint32 GetOriginalFormat();`
- L1692 _protected function_ `FMP4BoxFRMA(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo) : FMP4BoxBase(InParent, InBoxInfo)`
- L1695 _protected prototype_ `void ParseIfRequired();`
- L1697 _protected member_ `TPimplPtr<FParsed> Parsed;`

#### class `MP4Boxes::FMP4BoxSCHM`  
`class FMP4BoxSCHM : public FMP4BoxBase`  
_L1705-1720_
- inherits: `FMP4BoxBase`
- desc: `schm` box ISO/IEC 14496-12:2022 - 8.12.6 Scheme type box
- L1708 _public function_ `static TSharedPtr<FMP4BoxBase, ESPMode::ThreadSafe> Create(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo)`
- L1710 _public prototype_ `virtual ~FMP4BoxSCHM() = default;`
- L1711 _public prototype_ `uint32 GetSchemeType();`
- L1712 _public prototype_ `uint32 GetSchemeVersion();`
- L1714 _protected function_ `FMP4BoxSCHM(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo) : FMP4BoxBase(InParent, InBoxInfo)`
- L1717 _protected prototype_ `void ParseIfRequired();`
- L1719 _protected member_ `TPimplPtr<FParsed> Parsed;`

#### class `MP4Boxes::FMP4BoxSCHI`  
`class FMP4BoxSCHI : public FMP4BoxBase`  
_L1727-1738_
- inherits: `FMP4BoxBase`
- desc: `schi` box ISO/IEC 14496-12:2022 - 8.12.7 Scheme information box
- L1730 _public function_ `static TSharedPtr<FMP4BoxBase, ESPMode::ThreadSafe> Create(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo)`
- L1732 _public prototype_ `virtual ~FMP4BoxSCHI() = default;`
- L1733 _public function_ `bool IsLeafBox() const override`
- L1735 _protected function_ `FMP4BoxSCHI(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo) : FMP4BoxBase(InParent, InBoxInfo)`

#### class `MP4Boxes::FMP4BoxPSSH`  
`class FMP4BoxPSSH : public FMP4BoxBase`  
_L1745-1761_
- inherits: `FMP4BoxBase`
- desc: `pssh` box ISO/IEC 23001-7:2023 - 8.1 Protection system specific header box
- L1748 _public function_ `static TSharedPtr<FMP4BoxBase, ESPMode::ThreadSafe> Create(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo)`
- L1750 _public prototype_ `virtual ~FMP4BoxPSSH() = default;`
- L1751 _public prototype_ `TConstArrayView<uint8> GetSystemID();`
- L1752 _public prototype_ `const TArray<TConstArrayView<uint8>>& GetKIDs();`
- L1753 _public prototype_ `TConstArrayView<uint8> GetData();`
- L1755 _protected function_ `FMP4BoxPSSH(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo) : FMP4BoxBase(InParent, InBoxInfo)`
- L1758 _protected prototype_ `void ParseIfRequired();`
- L1760 _protected member_ `TPimplPtr<FParsed> Parsed;`

#### class `MP4Boxes::FMP4BoxTENC`  
`class FMP4BoxTENC : public FMP4BoxBase`  
_L1768-1788_
- inherits: `FMP4BoxBase`
- desc: `tenc` box ISO/IEC 23001-7:2023 - 8.2 Track Encryption box
- L1771 _public function_ `static TSharedPtr<FMP4BoxBase, ESPMode::ThreadSafe> Create(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo)`
- L1773 _public prototype_ `virtual ~FMP4BoxTENC() = default;`
- L1774 _public prototype_ `bool HasDefaultCryptBlockValues();`
- L1775 _public prototype_ `uint8 GetDefaultCryptByteBlock();`
- L1776 _public prototype_ `uint8 GetDefaultSkipByteBlock();`
- L1777 _public prototype_ `uint8 GetDefaultIsProtected();`
- L1778 _public prototype_ `uint8 GetDefaultPerSampleIVSize();`
- L1779 _public prototype_ `TConstArrayView<uint8> GetDefaultKID();`
- L1780 _public prototype_ `TConstArrayView<uint8> GetDefaultConstantIV();`
- L1782 _protected function_ `FMP4BoxTENC(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo) : FMP4BoxBase(InParent, InBoxInfo)`
- L1785 _protected prototype_ `void ParseIfRequired();`
- L1787 _protected member_ `TPimplPtr<FParsed> Parsed;`

#### class `MP4Boxes::FMP4BoxSENC`  
`class FMP4BoxSENC : public FMP4BoxBase`  
_L1795-1823_
- inherits: `FMP4BoxBase`
- desc: `senc` box ISO/IEC 23001-7:2023 - 7.2.1 Sample encryption box - Definition
- L1798 _public function_ `static TSharedPtr<FMP4BoxBase, ESPMode::ThreadSafe> Create(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo)`
- L1800 _public prototype_ `virtual ~FMP4BoxSENC() = default;`
- L1802 _public prototype_ `void Prepare(TWeakPtr<FMP4BoxTENC, ESPMode::ThreadSafe> InTENCBox);`
- L1814 _public prototype_ `const TArray<FEntry>& GetEntries();`
- L1816 _protected function_ `FMP4BoxSENC(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo) : FMP4BoxBase(InParent, InBoxInfo)`
- L1819 _protected prototype_ `void ParseIfRequired();`
- L1821 _protected member_ `TPimplPtr<FParsed> Parsed;`
- L1822 _protected member_ `TWeakPtr<FMP4BoxTENC, ESPMode::ThreadSafe> ParentTENCBox;`

#### struct `MP4Boxes::FMP4BoxSENC::FSubSample`  
`struct FSubSample`  
_L1804-1808_
- L1806 _public member_ `uint32 NumEncryptedBytes = 0;`
- L1807 _public member_ `uint16 NumClearBytes = 0;`

#### struct `MP4Boxes::FMP4BoxSENC::FEntry`  
`struct FEntry`  
_L1809-1813_
- L1811 _public member_ `TArray<uint8> IV;`
- L1812 _public member_ `TArray<FSubSample> SubSamples;`

#### class `MP4Boxes::FMP4BoxEMSG`  
`class FMP4BoxEMSG : public FMP4BoxBase`  
_L1830-1853_
- inherits: `FMP4BoxBase`
- desc: `emsg` box ISO/IEC 23009-1:2022 - 5.10.3.3 Event message box
- L1833 _public function_ `static TSharedPtr<FMP4BoxBase, ESPMode::ThreadSafe> Create(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo)`
- L1835 _public prototype_ `virtual ~FMP4BoxEMSG() = default;`
- L1837 _public prototype_ `uint8 GetVersion();` — version 0: GetPresentationTimeDelta(); version 1: GetPresentationTime()
- L1838 _public prototype_ `FString GetSchemeIdUri();`
- L1839 _public prototype_ `FString GetValue();`
- L1840 _public prototype_ `uint32 GetTimescale();`
- L1841 _public prototype_ `uint32 GetPresentationTimeDelta();`
- L1842 _public prototype_ `uint64 GetPresentationTime();`
- L1843 _public prototype_ `uint32 GetEventDuration();`
- L1844 _public prototype_ `uint32 GetID();`
- L1845 _public prototype_ `TConstArrayView<uint8> GetMessageData();`
- L1847 _protected function_ `FMP4BoxEMSG(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo) : FMP4BoxBase(InParent, InBoxInfo)`
- L1850 _protected prototype_ `void ParseIfRequired();`
- L1852 _protected member_ `TPimplPtr<FParsed> Parsed;`

#### class `MP4Boxes::FMP4BoxAVCC`  
`class FMP4BoxAVCC : public FMP4BoxBase`  
_L1860-1874_
- inherits: `FMP4BoxBase`
- desc: `avcC` box ISO/IEC 14496-15:2022 - 5.4.2 AVC video stream definition
- L1863 _public function_ `static TSharedPtr<FMP4BoxBase, ESPMode::ThreadSafe> Create(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo)`
- L1865 _public prototype_ `virtual ~FMP4BoxAVCC() = default;`
- L1866 _public prototype_ `TConstArrayView<uint8> GetAVCDecoderConfigurationRecord();`
- L1868 _protected function_ `FMP4BoxAVCC(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo) : FMP4BoxBase(InParent, InBoxInfo)`
- L1871 _protected prototype_ `void ParseIfRequired();`
- L1873 _protected member_ `TPimplPtr<FParsed> Parsed;`

#### class `MP4Boxes::FMP4BoxHVCC`  
`class FMP4BoxHVCC : public FMP4BoxBase`  
_L1881-1895_
- inherits: `FMP4BoxBase`
- desc: `hvcC` box ISO/IEC 14496-15:2022 - 8.3 Sample and configuration definition
- L1884 _public function_ `static TSharedPtr<FMP4BoxBase, ESPMode::ThreadSafe> Create(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo)`
- L1886 _public prototype_ `virtual ~FMP4BoxHVCC() = default;`
- L1887 _public prototype_ `TConstArrayView<uint8> GetHEVCDecoderConfigurationRecord();`
- L1889 _protected function_ `FMP4BoxHVCC(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo) : FMP4BoxBase(InParent, InBoxInfo)`
- L1892 _protected prototype_ `void ParseIfRequired();`
- L1894 _protected member_ `TPimplPtr<FParsed> Parsed;`

#### class `MP4Boxes::FMP4BoxVPCC`  
`class FMP4BoxVPCC : public FMP4BoxBase`  
_L1903-1917_
- inherits: `FMP4BoxBase`
- desc: `vpcC` box VP Codec ISO Media File Format Binding See: https://www.webmproject.org/vp9/mp4/#syntax_1
- L1906 _public function_ `static TSharedPtr<FMP4BoxBase, ESPMode::ThreadSafe> Create(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo)`
- L1908 _public prototype_ `virtual ~FMP4BoxVPCC() = default;`
- L1909 _public prototype_ `TConstArrayView<uint8> GetVPCodecConfigurationRecord();`
- L1911 _protected function_ `FMP4BoxVPCC(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo) : FMP4BoxBase(InParent, InBoxInfo)`
- L1914 _protected prototype_ `void ParseIfRequired();`
- L1916 _protected member_ `TPimplPtr<FParsed> Parsed;`

#### class `MP4Boxes::FMP4BoxAV1C`  
`class FMP4BoxAV1C : public FMP4BoxBase`  
_L1925-1939_
- inherits: `FMP4BoxBase`
- desc: `av1C` box AV1 Codec ISO Media File Format Binding See: https://aomediacodec.github.io/av1-isobmff/#av1codecconfigurationbox-syntax
- L1928 _public function_ `static TSharedPtr<FMP4BoxBase, ESPMode::ThreadSafe> Create(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo)`
- L1930 _public prototype_ `virtual ~FMP4BoxAV1C() = default;`
- L1931 _public prototype_ `TConstArrayView<uint8> GetAV1CodecConfigurationRecord();`
- L1933 _protected function_ `FMP4BoxAV1C(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo) : FMP4BoxBase(InParent, InBoxInfo)`
- L1936 _protected prototype_ `void ParseIfRequired();`
- L1938 _protected member_ `TPimplPtr<FParsed> Parsed;`

#### class `MP4Boxes::FMP4BoxAPVC`  
`class FMP4BoxAPVC : public FMP4BoxBase`  
_L1947-1961_
- inherits: `FMP4BoxBase`
- desc: `apvC` box APV Codec ISO Media File Format Binding See: https://github.com/AcademySoftwareFoundation/openapv/blob/main/readme/apv_isobmff.md#apv-codec-configuration-box
- L1950 _public function_ `static TSharedPtr<FMP4BoxBase, ESPMode::ThreadSafe> Create(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo)`
- L1952 _public prototype_ `virtual ~FMP4BoxAPVC() = default;`
- L1953 _public prototype_ `TConstArrayView<uint8> GetAVPCCodecConfigurationRecord();`
- L1955 _protected function_ `FMP4BoxAPVC(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo) : FMP4BoxBase(InParent, InBoxInfo)`
- L1958 _protected prototype_ `void ParseIfRequired();`
- L1960 _protected member_ `TPimplPtr<FParsed> Parsed;`

#### class `MP4Boxes::FMP4BoxIODS`  
`class FMP4BoxIODS : public FMP4BoxBase`  
_L1968-1982_
- inherits: `FMP4BoxBase`
- desc: `iods` box ISO/IEC 14496-14:2020 - 6.2 Object Descriptor Box
- L1971 _public function_ `static TSharedPtr<FMP4BoxBase, ESPMode::ThreadSafe> Create(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo)`
- L1973 _public prototype_ `virtual ~FMP4BoxIODS() = default;`
- L1974 _public prototype_ `TConstArrayView<uint8> GetObjectDescriptor();`
- L1976 _protected function_ `FMP4BoxIODS(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo) : FMP4BoxBase(InParent, InBoxInfo)`
- L1979 _protected prototype_ `void ParseIfRequired();`
- L1981 _protected member_ `TPimplPtr<FParsed> Parsed;`

#### class `MP4Boxes::FMP4BoxESDS`  
`class FMP4BoxESDS : public FMP4BoxBase`  
_L1989-2003_
- inherits: `FMP4BoxBase`
- desc: `esds` box ISO/IEC 14496-14:2020 - 6.7.2
- L1992 _public function_ `static TSharedPtr<FMP4BoxBase, ESPMode::ThreadSafe> Create(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo)`
- L1994 _public prototype_ `virtual ~FMP4BoxESDS() = default;`
- L1995 _public prototype_ `TConstArrayView<uint8> GetESDescriptor();`
- L1997 _protected function_ `FMP4BoxESDS(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo) : FMP4BoxBase(InParent, InBoxInfo)`
- L2000 _protected prototype_ `void ParseIfRequired();`
- L2002 _protected member_ `TPimplPtr<FParsed> Parsed;`

#### class `MP4Boxes::FMP4BoxDVCC`  
`class FMP4BoxDVCC : public FMP4BoxBase`  
_L2010-2024_
- inherits: `FMP4BoxBase`
- desc: `dvcC` box, `dvvC` box, `dvwC` box Dolby Vision Streams Within the ISO Base:2023 - 2.2 Dolby Vision configuration boxes
- L2013 _public function_ `static TSharedPtr<FMP4BoxBase, ESPMode::ThreadSafe> Create(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo)`
- L2015 _public prototype_ `virtual ~FMP4BoxDVCC() = default;`
- L2016 _public prototype_ `TConstArrayView<uint8> GetDOVIDecoderConfigurationRecord();`
- L2018 _protected function_ `FMP4BoxDVCC(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo) : FMP4BoxBase(InParent, InBoxInfo)`
- L2021 _protected prototype_ `void ParseIfRequired();`
- L2023 _protected member_ `TPimplPtr<FParsed> Parsed;`

#### class `MP4Boxes::FMP4BoxDAC3`  
`class FMP4BoxDAC3 : public FMP4BoxBase`  
_L2031-2045_
- inherits: `FMP4BoxBase`
- desc: `dac3` box Annex F.4 of ETSI TS 102 366 - AC3SpecificBox
- L2034 _public function_ `static TSharedPtr<FMP4BoxBase, ESPMode::ThreadSafe> Create(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo)`
- L2036 _public prototype_ `virtual ~FMP4BoxDAC3() = default;`
- L2037 _public prototype_ `TConstArrayView<uint8> GetAC3SpecificBox();`
- L2039 _protected function_ `FMP4BoxDAC3(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo) : FMP4BoxBase(InParent, InBoxInfo)`
- L2042 _protected prototype_ `void ParseIfRequired();`
- L2044 _protected member_ `TPimplPtr<FParsed> Parsed;`

#### class `MP4Boxes::FMP4BoxDEC3`  
`class FMP4BoxDEC3 : public FMP4BoxBase`  
_L2052-2066_
- inherits: `FMP4BoxBase`
- desc: `dec3` box Annex F.6 of ETSI TS 102 366 - EC3SpecificBox
- L2055 _public function_ `static TSharedPtr<FMP4BoxBase, ESPMode::ThreadSafe> Create(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo)`
- L2057 _public prototype_ `virtual ~FMP4BoxDEC3() = default;`
- L2058 _public prototype_ `TConstArrayView<uint8> GetEC3SpecificBox();`
- L2060 _protected function_ `FMP4BoxDEC3(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo) : FMP4BoxBase(InParent, InBoxInfo)`
- L2063 _protected prototype_ `void ParseIfRequired();`
- L2065 _protected member_ `TPimplPtr<FParsed> Parsed;`

#### class `MP4Boxes::FMP4BoxDFLA`  
`class FMP4BoxDFLA : public FMP4BoxBase`  
_L2073-2087_
- inherits: `FMP4BoxBase`
- desc: `dfLa` box FLAC (https://github.com/xiph/flac/blob/master/doc/isoflac.txt) specific box - 3.3.2 FLAC Specific Box
- L2076 _public function_ `static TSharedPtr<FMP4BoxBase, ESPMode::ThreadSafe> Create(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo)`
- L2078 _public prototype_ `virtual ~FMP4BoxDFLA() = default;`
- L2079 _public prototype_ `TConstArrayView<uint8> GetFLACSpecificBox();`
- L2081 _protected function_ `FMP4BoxDFLA(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo) : FMP4BoxBase(InParent, InBoxInfo)`
- L2084 _protected prototype_ `void ParseIfRequired();`
- L2086 _protected member_ `TPimplPtr<FParsed> Parsed;`

#### class `MP4Boxes::FMP4BoxDOPS`  
`class FMP4BoxDOPS : public FMP4BoxBase`  
_L2094-2108_
- inherits: `FMP4BoxBase`
- desc: `dOps` box Opus (https://opus-codec.org/docs/opus_in_isobmff.html#4.3.2) specific box - 4.3.2 Opus Specific Bo
- L2097 _public function_ `static TSharedPtr<FMP4BoxBase, ESPMode::ThreadSafe> Create(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo)`
- L2099 _public prototype_ `virtual ~FMP4BoxDOPS() = default;`
- L2100 _public prototype_ `TConstArrayView<uint8> GetOpusSpecificBox();`
- L2102 _protected function_ `FMP4BoxDOPS(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo) : FMP4BoxBase(InParent, InBoxInfo)`
- L2105 _protected prototype_ `void ParseIfRequired();`
- L2107 _protected member_ `TPimplPtr<FParsed> Parsed;`

#### class `MP4Boxes::FMP4BoxWAVE`  
`class FMP4BoxWAVE : public FMP4BoxBase`  
_L2115-2126_
- inherits: `FMP4BoxBase`
- desc: `wave` box Apple Quicktime: https://developer.apple.com/documentation/quicktime-file-format/sidecompressionparam_atom
- L2118 _public function_ `static TSharedPtr<FMP4BoxBase, ESPMode::ThreadSafe> Create(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo)`
- L2120 _public prototype_ `virtual ~FMP4BoxWAVE() = default;`
- L2121 _public function_ `bool IsLeafBox() const override`
- L2123 _protected function_ `FMP4BoxWAVE(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo) : FMP4BoxBase(InParent, InBoxInfo)`

#### class `MP4Boxes::FMP4BoxTAPT`  
`class FMP4BoxTAPT : public FMP4BoxBase`  
_L2133-2144_
- inherits: `FMP4BoxBase`
- desc: `tapt` box Apple Quicktime: https://developer.apple.com/documentation/quicktime-file-format/track_aperture_mode_dimensions_atom
- L2136 _public function_ `static TSharedPtr<FMP4BoxBase, ESPMode::ThreadSafe> Create(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo)`
- L2138 _public prototype_ `virtual ~FMP4BoxTAPT() = default;`
- L2139 _public function_ `bool IsLeafBox() const override`
- L2141 _protected function_ `FMP4BoxTAPT(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo) : FMP4BoxBase(InParent, InBoxInfo)`

#### class `MP4Boxes::FMP4BoxFactory`  
`class FMP4BoxFactory`  
_L2147-2155_
- L2150 _public prototype_ `static FMP4BoxFactory& Get();`
- L2151 _public prototype_ `TSharedPtr<FMP4BoxBase, ESPMode::ThreadSafe> Create(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& InParent, const MP4Utilities::FMP4BoxInfo& InBoxInfo);`
- L2153 _private prototype_ `FMP4BoxFactory();`
- L2154 _private member_ `TMap<uint32, TSharedPtr<FMP4BoxBase, ESPMode::ThreadSafe>(*)(const TWeakPtr<FMP4BoxBase, ESPMode::ThreadSafe>& , const MP4Utilities::FMP4BoxInfo& )> FactoryMap;`

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API MP4BOXES_API`
- L17 _namespace_ `namespace MP4Boxes`

### `Plugins/Media/MP4Utilities/Source/MP4Boxes/Public/MP4Track.h` (Public)


#### class `MP4Boxes::FMP4Track`  
`class FMP4Track : public TSharedFromThis<FMP4Track>`  
_L20-389_
- inherits: `TSharedFromThis<FMP4Track>`
- L95 _public function_ `static TSharedPtr<FMP4Track, ESPMode::ThreadSafe> Create(const TSharedPtr<FMP4BoxTRAK, ESPMode::ThreadSafe>& InTrakBox, const TSharedPtr<FMP4Track::FFragmentInfo, ESPMode::ThreadSafe>& InFragmentInfo)`
- L97 _public prototype_ `virtual ~FMP4Track() = default;`
- L99 _public prototype_ `bool Prepare(MP4Utilities::FFractionalTime InFullMovieDuration, MP4Utilities::FFractionalTime InAdjustedMovieDuration);`
- L100 _public prototype_ `FString GetLastError();`
- L101 _public prototype_ `const FMP4TrackMetadataCommon& GetCommonMetadata();`
- L326 _public prototype_ `TSharedPtr<FIterator, ESPMode::ThreadSafe> CreateIterator();` — Create an interator starting at the first sample.
- L328 _public prototype_ `TSharedPtr<FIterator, ESPMode::ThreadSafe> CreateIteratorAtLastFrame();` — Create an interator starting at the last sample (used when iterating in reverse, crossing back from the beginning to the end)
- L331 _public prototype_ `TSharedPtr<FIterator, ESPMode::ThreadSafe> CreateIteratorAtKeyframe(FTimespan InForTime, FTimespan InLaterTimeThreshold);` — Create an iterator starting at a keyframe on or before the given time, or at a later time within the given threshold should one be right after the given time and would not be selected due to timescale rounding issues.
- L333 _public prototype_ `TSharedPtr<FIterator, ESPMode::ThreadSafe> CreateIterator(uint32 InAtSampleNumber);` — Create an interator starting at a given sample number.
- L336 _public prototype_ `uint32 GetNumberOfSamples();` — Returns the number of samples in this track.
- L339 _public function_ `const FFirstSample& GetFirstSampleInfo() const` — Returns information about the first sample that is mapped to the 0-based timeline via `elst` box.
- L342 _public function_ `const FLastSample& GetLastSampleInfo() const` — Returns information about the last sample that is mapped to the 0-based timeline via `elst` box.
- L346 _public function_ `const MP4Utilities::FFractionalTime& GetFullMovieDuration() const` — Returns the duration of the movie as a whole, which is set from the longest track.
- L350 _public function_ `const MP4Utilities::FFractionalTime& GetMappedTrackDuration() const` — Returns the duration of this track as mapped onto the media internal timeline (edit list).
- L353 _public function_ `const MP4Utilities::FFractionalTime& GetTrackDuration() const` — Returns the duration of this track media.
- L357 _protected function_ `FMP4Track(const TSharedPtr<FMP4BoxTRAK, ESPMode::ThreadSafe>& InTrakBox, const TSharedPtr<FMP4Track::FFragmentInfo, ESPMode::ThreadSafe>& InFragmentInfo) : TrakBox(InTrakBox) , FragmentInfo(InFragmentInfo)`
- L362 _protected member_ `TSharedPtr<FMP4BoxTRAK, ESPMode::ThreadSafe> TrakBox;`
- L363 _protected member_ `TSharedPtr<FMP4Track::FFragmentInfo, ESPMode::ThreadSafe> FragmentInfo;`
- L365 _protected member_ `TSharedPtr<FMP4BoxTKHD, ESPMode::ThreadSafe> TkhdBox;`
- L366 _protected member_ `TSharedPtr<FMP4BoxELST, ESPMode::ThreadSafe> ElstBox;`
- L367 _protected member_ `TSharedPtr<FMP4BoxMDHD, ESPMode::ThreadSafe> MdhdBox;`
- L368 _protected member_ `TSharedPtr<FMP4BoxSTTS, ESPMode::ThreadSafe> SttsBox;`
- L369 _protected member_ `TSharedPtr<FMP4BoxCTTS, ESPMode::ThreadSafe> CttsBox;`
- L370 _protected member_ `TSharedPtr<FMP4BoxSTSC, ESPMode::ThreadSafe> StscBox;`
- L371 _protected member_ `TSharedPtr<FMP4BoxSTSZ, ESPMode::ThreadSafe> StszBox;`
- L372 _protected member_ `TSharedPtr<FMP4BoxSTCO, ESPMode::ThreadSafe> StcoBox;`
- L373 _protected member_ `TSharedPtr<FMP4BoxSTSS, ESPMode::ThreadSafe> StssBox;`
- L374 _protected member_ `TSharedPtr<FMP4BoxTENC, ESPMode::ThreadSafe> TencBox;`
- L375 _protected member_ `TSharedPtr<FMP4BoxSENC, ESPMode::ThreadSafe> SencBox;`
- L376 _protected member_ `TSharedPtr<FMP4BoxUDTA, ESPMode::ThreadSafe> UdtaBox;`
- L378 _protected member_ `TArray<TSharedPtr<FMP4BoxSUBS, ESPMode::ThreadSafe>> SubsBoxes;`
- L379 _protected member_ `TArray<TSharedPtr<FMP4BoxSGPD, ESPMode::ThreadSafe>> SgpdBoxes;`
- L380 _protected member_ `TArray<TSharedPtr<FMP4BoxSBGP, ESPMode::ThreadSafe>> SbgpBoxes;`
- L382 _protected member_ `FConvenience Convs;`
- L384 _protected member_ `FMP4TrackMetadataCommon CommonMetadata;`
- L386 _protected member_ `bool bHasBeenPrepared = false;`
- L388 _protected member_ `FString LastErrorMessage;`

#### struct `MP4Boxes::FMP4Track::FFirstSample`  
`struct FFirstSample`  
_L23-29_
- L25 _public member_ `int64 SamplePTS = 0;`
- L26 _public member_ `int64 StartPTS = 0;`
- L27 _public member_ `uint32 SampleNumber = 0;`
- L28 _public member_ `uint32 SyncSampleNumber = 0;`

#### struct `MP4Boxes::FMP4Track::FLastSample`  
`struct FLastSample`  
_L31-37_
- L33 _public member_ `int64 SamplePTS = 0;`
- L34 _public member_ `int64 EndPTS = 0;`
- L35 _public member_ `uint32 SampleNumber = 0;`
- L36 _public member_ `uint32 LastSampleNumber = 0;`

#### struct `MP4Boxes::FMP4Track::FConvenience`  
`struct FConvenience`  
_L40-54_
- L42 _public member_ `FFirstSample FirstSample;`
- L43 _public member_ `FLastSample LastSample;`
- L44 _public member_ `MP4Utilities::FFractionalTime FullMovieDuration;`
- L45 _public member_ `MP4Utilities::FFractionalTime DurationFromMvhdBox;`
- L46 _public member_ `MP4Utilities::FFractionalTime DurationFromTkhdBox;`
- L47 _public member_ `MP4Utilities::FFractionalTime DurationFromMdhdBox;`
- L48 _public member_ `MP4Utilities::FFractionalTime MappedDurationFromElstBox;`
- L49 _public member_ `int64 CompositionTimeAtZeroPoint = 0;`
- L50 _public member_ `int64 DTSShiftAtZeroPoint = 0;`
- L51 _public member_ `uint32 TrackID = 0;`
- L52 _public member_ `uint32 NumTotalSamples = 0;`
- L53 _public member_ `uint32 NumMoovSamples = 0;`

#### class `MP4Boxes::FMP4Track::FFragmentInfo`  
`class FFragmentInfo`  
_L57-93_
- L75 _public member_ `TArray<TSharedPtr<FTrackTrafs, ESPMode::ThreadSafe>> TrackFragments;`
- L76 _public member_ `TSharedPtr<FMP4BoxTKHD, ESPMode::ThreadSafe> TkhdBox;`
- L77 _public member_ `TSharedPtr<FMP4BoxMDHD, ESPMode::ThreadSafe> MdhdBox;`
- L78 _public member_ `TSharedPtr<FMP4BoxTREX, ESPMode::ThreadSafe> TrexBox;`
- L79 _public member_ `TSharedPtr<FMP4BoxTENC, ESPMode::ThreadSafe> TencBox;`
- L80 _public member_ `uint32 NumTotalFragmentSamples = 0;`
- L82 _public function_ `bool HasBeenPrepared() const`
- L84 _public prototype_ `bool Prepare(const TSharedPtr<FMP4BoxTRAK, ESPMode::ThreadSafe>& InTrakBox, const TSharedPtr<FMP4BoxMVEX, ESPMode::ThreadSafe>& InMvexBox, const TArray<TSharedPtr<FMP4BoxBase>>& InAllRootBoxes);`
- L85 _public prototype_ `int64 GetTotalDuration();`
- L87 _private prototype_ `void CalculateDurations();`
- L88 _private member_ `int64 BaseTrackDuration = 0;`
- L89 _private member_ `int64 SumOfFragmentDurations = 0;`
- L90 _private member_ `uint32 NumBaseTrackSamples = 0;`
- L91 _private member_ `bool bDidCalculateDuration = false;`
- L92 _private member_ `bool bHasBeenPrepared = false;`

#### struct `MP4Boxes::FMP4Track::FFragmentInfo::FTrackTrafs`  
`struct FTrackTrafs`  
_L60-74_
- L62 _public member_ `TSharedPtr<FMP4BoxMOOF, ESPMode::ThreadSafe> MoofBox;`
- L63 _public member_ `TSharedPtr<FMP4BoxTRAF, ESPMode::ThreadSafe> TrafBox;`
- L64 _public member_ `TSharedPtr<FMP4BoxTFHD, ESPMode::ThreadSafe> TfhdBox;`
- L65 _public member_ `TSharedPtr<FMP4BoxSENC, ESPMode::ThreadSafe> SencBox;`
- L66 _public member_ `TArray<TSharedPtr<FMP4BoxTRUN, ESPMode::ThreadSafe>> TrunBoxes;`
- L67 _public member_ `TArray<TSharedPtr<FMP4BoxSUBS, ESPMode::ThreadSafe>> SubsBoxes;`
- L68 _public member_ `TOptional<uint64> BaseMediaDecodeTime;`
- L69 _public member_ `uint32 AbsoluteFirstSampleNumber = 0;`
- L70 _public member_ `int64 FirstTrackTotalDTS = 0;`
- L71 _public member_ `int64 LastTrackTotalDTSAndDur = 0;`
- L72 _public member_ `int64 Duration = 0;`
- L73 _public member_ `uint32 NumSamples = 0;`

#### class `MP4Boxes::FMP4Track::FIterator`  
`class FIterator`  
_L103-323_
- L106 _public prototype_ `virtual ~FIterator() = default;`
- L108 _public function_ `bool IsValid() const`
- L110 _public function_ `TWeakPtr<FMP4Track, ESPMode::ThreadSafe> GetTrack() const`
- L112 _public function_ `uint32 GetTrackID() const`
- L114 _public function_ `uint32 GetSampleNumber() const`
- L117 _public function_ `MP4Utilities::FFractionalTime GetDTS() const` — Returns the DTS without mapping to the timeline.
- L120 _public function_ `MP4Utilities::FFractionalTime GetEffectiveDTS() const` — Returns the effective DTS, which has the timeline mapping applied. This may result in a negative value.
- L123 _public function_ `MP4Utilities::FFractionalTime GetPTS() const` — Returns the PTS as the sum of the DTS and the composition time offset, without mapping to the timeline.
- L126 _public function_ `MP4Utilities::FFractionalTime GetEffectivePTS() const` — Returns the effective PTS, which is the media time mapped into the 0-based timeline.
- L128 _public function_ `MP4Utilities::FFractionalTime GetDuration() const`
- L131 _public function_ `FTimespan GetDurationAsTimespan() const` — Returns the duration as an FTimespan, which may be slightly more accurate than as a fraction.
- L133 _public function_ `bool IsSyncOrRAPSample() const`
- L135 _public function_ `int64 GetSampleSize() const`
- L137 _public function_ `int64 GetSampleFileOffset() const`
- L139 _public function_ `uint32 GetTimescale() const`
- L141 _public function_ `uint32 GetNumSamples() const`
- L144 _public function_ `MP4Utilities::FFractionalTime GetTrackDuration() const` — Returns the track's entire media duration, not affected by an edit list. Timescale comes from `mdhd` box.
- L147 _public function_ `MP4Utilities::FFractionalTime GetEffectiveTrackDuration() const` — Returns the effective track's duration, as specified by an edit list. Timescale has been converted into `mdhd` timescale!
- L150 _public function_ `TOptional<MP4Utilities::FFractionalTime> GetBaseMediaDecodeTime() const` — Returns the base media decode time for the current fragment.
- L153 _public function_ `TOptional<uint32> GetSubsampleBoxFlags() const` — Returns the flags from the `subs` full box. Unset if there is no subsample box.
- L156 _public function_ `const FMP4BoxSUBS::FSubsampleList& GetSubsampleList() const` — Returns the list of subsamples for this sample, if there are any.
- L159 _public function_ `const FMP4BoxSENC::FEntry& GetEncryptionInfo() const` — Returns the encryption information for this sample.
- L164 _public prototype_ `bool Next();` — Advances this iterator to the next sample. Returns true if there is one, false if not. This iterates over the entire track, ignoring timeline mapping.
- L168 _public prototype_ `bool Prev();` — Recedes this iterator to the previous sample. Returns true if there is one, false if not. This iterates over the entire track, ignoring timeline mapping.
- L171 _public function_ `bool IsFirst() const` — Returns whether the iterator points to the first overall sample, ignoring mapping to the timeline.
- L174 _public function_ `bool IsLast() const` — Returns whether the iterator points to the last overall sample, ignoring mapping to the timeline.
- L179 _public prototype_ `bool NextEffective();` — Same as above, but obeying the timeline mapping and taking into consideration any required earlier sync frame and later frames due to reordering.
- L180 _public prototype_ `bool PrevEffective();`
- L181 _public function_ `bool IsFirstEffective() const`
- L183 _public function_ `bool IsLastEffective() const`
- L195 _public prototype_ `bool GetCurrentChunkRemainingSampleInfo(FChunkInfo& OutInfo) const;` — Returns information about the samples that are remaining in the current chunk. This is intended only for forward playback, not reverse.
- L198 _public function_ `TSharedPtr<FIterator, ESPMode::ThreadSafe> Clone()` — Creates a copy of this iterator.
- L282 _protected prototype_ `FIterator() = default;`
- L283 _protected prototype_ `FIterator(const FIterator& InOther) = default;`
- L284 _protected prototype_ `FIterator& operator = (const FIterator&) = delete;`
- L287 _protected prototype_ `void StartAt(uint32 InFrameNumber);`
- L288 _protected prototype_ `void Update();`
- L290 _protected member_ `TWeakPtr<FMP4Track, ESPMode::ThreadSafe> Track;`
- L291 _protected member_ `FConvenience Convs;`
- L292 _protected member_ `FSTSZBoxIterator stszIt;`
- L293 _protected member_ `FSTTSBoxIterator sttsIt;`
- L294 _protected member_ `FCTTSBoxIterator cttsIt;`
- L295 _protected member_ `FSTSCBoxIterator stscIt;`
- L296 _protected member_ `FSTSSBoxIterator stssIt;`
- L297 _protected member_ `FSTCOBoxIterator stcoIt;`
- L298 _protected member_ `FSBGPBoxIterator rapIt;`
- L299 _protected member_ `FSUBSBoxIterator subsIt;`
- L300 _protected member_ `FSENCBoxIterator sencIt;`
- L301 _protected member_ `uint32 SampleNumber = 0;`
- L308 _protected member_ `FFragmentVars FragmentVars;`
- L310 _protected member_ `MP4Utilities::FFractionalTime CurrentDTS;`
- L311 _protected member_ `MP4Utilities::FFractionalTime CurrentPTS;`
- L312 _protected member_ `MP4Utilities::FFractionalTime CurrentEffectiveDTS;`
- L313 _protected member_ `MP4Utilities::FFractionalTime CurrentEffectivePTS;`
- L314 _protected member_ `MP4Utilities::FFractionalTime CurrentDuration;`
- L315 _protected member_ `TOptional<MP4Utilities::FFractionalTime> CurrentBaseMediaDecodeTime;`
- L316 _protected member_ `FTimespan CurrentDurationTS;`
- L317 _protected member_ `int64 CurrentSampleFileOffset = 0;`
- L318 _protected member_ `int64 CurrentSampleSize = 0;`
- L319 _protected member_ `bool bCurrentIsSyncOrRAP = false;`
- L320 _protected member_ `FMP4BoxSUBS::FSubsampleList CurrentSubsampleList;`
- L321 _protected member_ `TOptional<uint32> CurrentSubsampleBoxFlags;`
- L322 _protected member_ `FMP4BoxSENC::FEntry EncryptionEntry;`

#### struct `MP4Boxes::FMP4Track::FIterator::FChunkInfo`  
`struct FChunkInfo`  
_L186-192_
- L188 _public member_ `uint32 NumSamples = 0;`
- L189 _public member_ `int64 SizeInBytes = 0;`
- L190 _public member_ `int64 Duration = 0;`
- L191 _public member_ `bool bIsLastChunk = false;`

#### class `MP4Boxes::FMP4Track::FIterator::FTrafTrunIterator`  
`class FTrafTrunIterator`  
_L201-280_
- L204 _public prototype_ `FTrafTrunIterator() = default;`
- L205 _public prototype_ `void SetFragmentInfo(const TSharedPtr<FFragmentInfo, ESPMode::ThreadSafe>& InFragmentInfo);`
- L206 _public function_ `bool IsSetup() const`
- L209 _public prototype_ `bool StartAt(uint32 InSampleNum);`
- L210 _public prototype_ `bool Prev();`
- L211 _public prototype_ `bool Next();`
- L213 _public function_ `int64 GetStartDTS() const`
- L215 _public function_ `uint32 GetAbsoluteSampleNumber() const`
- L217 _public function_ `int64 GetAbsoluteOffset() const`
- L219 _public function_ `int32 GetSampleNumber() const`
- L221 _public function_ `int64 GetSampleSize() const`
- L223 _public function_ `int64 GetDTS() const`
- L225 _public function_ `int64 GetPTS() const`
- L227 _public function_ `int64 GetDuration() const`
- L229 _public function_ `bool IsSyncSample() const`
- L231 _public function_ `TOptional<uint64> GetBaseMediaDecodeTime() const`
- L234 _public function_ `TOptional<uint32> GetSubsampleBoxFlags() const`
- L236 _public function_ `const FMP4BoxSUBS::FSubsampleList& GetSubsampleList() const`
- L239 _public function_ `const FMP4BoxSENC::FEntry& GetEncryptionInfo() const`
- L242 _public prototype_ `bool GetCurrentTrafRemainingSampleInfo(FChunkInfo& OutInfo) const;`
- L244 _private prototype_ `void Update(const TSharedPtr<FMP4BoxTRUN, ESPMode::ThreadSafe>& InTrun);`
- L245 _private prototype_ `void Update(const TSharedPtr<FFragmentInfo::FTrackTrafs, ESPMode::ThreadSafe>& InTraf);`
- L246 _private member_ `TSharedPtr<FFragmentInfo, ESPMode::ThreadSafe> FragmentInfo;`
- L247 _private member_ `uint32 TrexDefaultSampleDescriptionIndex = 0;`
- L248 _private member_ `uint32 TrexDefaultSampleDuration = 0;`
- L249 _private member_ `uint32 TrexDefaultSampleSize = 0;`
- L250 _private member_ `uint32 TrexDefaultSampleFlags = 0;`
- L252 _private member_ `TOptional<uint64> BaseMediaDecodeTime;`
- L253 _private member_ `int64 TrunStartDTS = 0;`
- L254 _private member_ `int64 BaseOffset = 0;`
- L255 _private member_ `int64 DataOffset = 0;`
- L256 _private member_ `uint32 FirstAbsoluteSampleNumber = 0;`
- L257 _private member_ `uint32 DefaultSampleDescriptionIndex = 0;`
- L258 _private member_ `uint32 DefaultSampleDuration = 0;`
- L259 _private member_ `uint32 DefaultSampleSize = 0;`
- L260 _private member_ `uint32 DefaultSampleFlags = 0;`
- L261 _private member_ `int32 TrafNumber = -1;`
- L262 _private member_ `int32 TrunNumber = -1;`
- L263 _private member_ `int32 SampleNumber = -1;`
- L265 _private member_ `uint32 SampleFlags = 0;`
- L266 _private member_ `int64 AbsoluteSampleByteOffset = 0;`
- L267 _private member_ `int64 SampleSize = 0;`
- L268 _private member_ `int64 DTS = 0;`
- L269 _private member_ `int64 PTS = 0;`
- L270 _private member_ `int64 Duration = 0;`
- L272 _private member_ `int64 TrunFirstSampleAbsoluteByteOffset = -1;`
- L273 _private member_ `int64 TrunLastSampleAbsoluteByteOffset = -1;`
- L275 _private member_ `FSUBSBoxIterator subsIt;`
- L276 _private member_ `FMP4BoxSUBS::FSubsampleList SubsampleList;`
- L278 _private member_ `FSENCBoxIterator sencIt;`
- L279 _private member_ `FMP4BoxSENC::FEntry EncryptionEntry;`

#### struct `MP4Boxes::FMP4Track::FIterator::FFragmentVars`  
`struct FFragmentVars`  
_L303-307_
- L305 _public member_ `FTrafTrunIterator TrafTrunIterator;`
- L306 _public member_ `bool bInFragments = false;`

#### Free symbols / members of external scopes

- L16 _macro_ `#define UE_API MP4BOXES_API`
- L18 _namespace_ `namespace MP4Boxes`
