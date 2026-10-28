# Runtime / AVEncoder

- module root: `Source/Runtime/AVEncoder`
- headers: 51; symbols: 1265
- symbol kinds: class=36, delegate=10, enum=20, enumerator=94, function=142, macro=30, member=429, namespace=48, prototype=344, struct=50, typedef=25, union=1, variable=36
- PrivateDependencyModuleNames: Engine, SignalProcessing
- PublicDependencyModuleNames: CUDA, Core, RHI, RenderCore
- PublicIncludePathModuleNames: VulkanRHI

### `Source/Runtime/AVEncoder/Private/AVEncoder.h` (Private)


#### Free symbols / members of external scopes

- L8 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogAVEncoder, Log, All);`
- L8 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogAVEncoder, Log, All);`
- L9 _prototype_ `CSV_DECLARE_CATEGORY_EXTERN(AVEncoder);`

### `Source/Runtime/AVEncoder/Private/Decoders/VideoDecoderH264_Dummy.h` (Private)


#### class `AVEncoder::FVideoDecoderH264_Dummy`  
`class FVideoDecoderH264_Dummy : public FVideoDecoder PRAGMA_ENABLE_DEPRECATION_WARNINGS`  
_L16-40_
- inherits: `FVideoDecoderPRAGMA_ENABLE_DEPRECATION_WARNINGS`
- L22 _public prototype_ `static void Register(FVideoDecoderFactory& InFactory);` — register decoder with video decoder factory
- L23 _public prototype_ `virtual bool Setup(const FInit& InInit) override;`
- L24 _public prototype_ `virtual EDecodeResult Decode(const FVideoDecoderInput* InInput) override;`
- L27 _public prototype_ `virtual void Shutdown() override;`
- L36 _private prototype_ `FVideoDecoderH264_Dummy();`
- L37 _private prototype_ `virtual ~FVideoDecoderH264_Dummy();`
- L38 _private member_ `uint8_t YOffset = 0;`
- L39 _private member_ `bool bIsInitialized = false;`

#### Free symbols / members of external scopes

- L5 _macro_ `#define AVENCODER_VIDEO_DECODER_AVAILABLE_H264_DUMMY // enable dummy h264 decoder`
- L12 _namespace_ `namespace AVEncoder`

### `Source/Runtime/AVEncoder/Private/Decoders/VideoDecoderH264_Impl.h` (Private)


#### class `AVEncoder::FVideoDecoderH264_Impl`  
`class FVideoDecoderH264_Impl : public FVideoDecoder PRAGMA_ENABLE_DEPRECATION_WARNINGS`  
_L12-29_
- inherits: `FVideoDecoderPRAGMA_ENABLE_DEPRECATION_WARNINGS`
- L18 _public prototype_ `static void Register(FVideoDecoderFactory& InFactory);` — register decoder with video decoder factory
- L19 _public prototype_ `virtual bool Setup(const FInit& InInit) = 0;`
- L20 _public prototype_ `virtual EDecodeResult Decode(const FVideoDecoderInput* InInput) = 0;`
- L23 _public prototype_ `virtual void Shutdown() = 0;`
- L27 _protected prototype_ `virtual ~FVideoDecoderH264_Impl() = default;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace AVEncoder`

### `Source/Runtime/AVEncoder/Private/Decoders/VideoDecoderMpeg4.h` (Private)


#### class `AVEncoder::FVideoDecoderMPEG4`  
`class FVideoDecoderMPEG4 : public FVideoDecoder PRAGMA_ENABLE_DEPRECATION_WARNINGS`  
_L12-31_
- inherits: `FVideoDecoderPRAGMA_ENABLE_DEPRECATION_WARNINGS`
- L18 _public prototype_ `static void Register(FVideoDecoderFactory& InFactory);` — register decoder with video decoder factory
- L19 _public prototype_ `virtual bool Setup(const FInit& InInit) = 0;`
- L20 _public prototype_ `virtual EDecodeResult Decode(const FVideoDecoderInput* InInput) = 0;`
- L23 _public prototype_ `virtual void Shutdown() = 0;`
- L28 _protected prototype_ `virtual ~FVideoDecoderMPEG4() = default;`
- L29 _protected prototype_ `FVideoDecoderMPEG4() = default;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace AVEncoder`

### `Source/Runtime/AVEncoder/Private/Decoders/VideoDecoderVP8.h` (Private)


#### class `AVEncoder::FVideoDecoderVP8`  
`class FVideoDecoderVP8 : public FVideoDecoder PRAGMA_ENABLE_DEPRECATION_WARNINGS`  
_L12-27_
- inherits: `FVideoDecoderPRAGMA_ENABLE_DEPRECATION_WARNINGS`
- L18 _public prototype_ `static void Register(FVideoDecoderFactory& InFactory);` — register decoder with video decoder factory
- L19 _public prototype_ `virtual bool Setup(const FInit& InInit) = 0;`
- L20 _public prototype_ `virtual EDecodeResult Decode(const FVideoDecoderInput* InInput) = 0;`
- L23 _public prototype_ `virtual void Shutdown() = 0;`
- L26 _protected prototype_ `virtual ~FVideoDecoderVP8() = default;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace AVEncoder`

### `Source/Runtime/AVEncoder/Private/Decoders/Windows/VideoDecoderH264_Windows.h` (Private)


#### class `AVEncoder::FVideoDecoderH264_Windows`  
`class FVideoDecoderH264_Windows : public FVideoDecoderH264_Impl`  
_L11-25_
- inherits: `FVideoDecoderH264_Impl`
- L16 _public prototype_ `static void Register(FVideoDecoderFactory& InFactory);` — register decoder with video decoder factory
- L17 _public prototype_ `virtual bool Setup(const FInit& InInit) = 0;`
- L18 _public prototype_ `virtual EDecodeResult Decode(const FVideoDecoderInput* InInput) = 0;`
- L21 _public prototype_ `virtual void Shutdown() = 0;`
- L24 _protected prototype_ `virtual ~FVideoDecoderH264_Windows() = default;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace AVEncoder`

### `Source/Runtime/AVEncoder/Private/Decoders/vdecmpeg4/M4Bitstream.h` (Private)


#### class `vdecmpeg4::M4Bitstream`  
`class M4Bitstream`  
_L21-106_
- L25 _public prototype_ `M4Bitstream();` — Construction of bitstream object
- L28 _public prototype_ `~M4Bitstream();` — Destructor
- L31 _public prototype_ `void setMemoryHook(M4MemHandler& memSys);` — Set memory allocator
- L34 _public prototype_ `void init(const uint8* bitstream, uint32 length);` — Link bitstream to provided byte sequence
- L37 _public prototype_ `void init(VIDStreamIO* pStream, uint32 streamBufferBytes);` — Link bitstream to stream interface
- L40 _public prototype_ `uint32 show(const uint32 bits);` — Show indicated bit from stream without moving file position
- L43 _public prototype_ `void skip(const uint32 bits);` — Skip indicated bits in stream
- L46 _public prototype_ `void align();` — Align bitstream to next byte boundary
- L49 _public prototype_ `void nextStartCode();` — implements next_start_code()
- L50 _public prototype_ `void nextResyncMarker();`
- L51 _public prototype_ `void skipResyncMarker();`
- L54 _public prototype_ `uint32 showBitsByteAligned(const uint32 bits);` — implements nextbits_bytealigned()
- L56 _public prototype_ `bool validStuffingBits();`
- L59 _public prototype_ `uint32 getBits(const uint32 bits);` — Return indicated # of bits from stream
- L62 _public prototype_ `uint32 getBit();` — Return 1 bit from stream
- L65 _public prototype_ `bool isEof();` — Check eof
- L68 _public prototype_ `void totalBitsClear();` — Clear the byte counter
- L71 _public prototype_ `uint32 totalBitsGet() const;` — Read the byte counter
- L74 _public prototype_ `const uint32* getBaseAddr() const;` — Return memory base addres of stream
- L78 _private prototype_ `VIDError ReadStreamBuffered(uint32& value);` — Read from stream in buffered way
- L81 _private prototype_ `M4Bitstream(const M4Bitstream& pObj);` — Copy-constructor is private to prevent usage
- L84 _private prototype_ `const M4Bitstream& operator=(const M4Bitstream& pObj);` — Assignment operator is private to prevent usage
- L86 _private member_ `uint32 mAWord;`
- L87 _private member_ `uint32 mBWord;`
- L89 _private member_ `uint32 mPos;`
- L90 _private member_ `uint32* mTail;`
- L92 _private member_ `uint32 mLength;` — length of bitstream in bytes
- L93 _private member_ `uint32* mStart;` — pointer to start of data
- L95 _private member_ `VIDStreamIO* mpStreamIO;` — pointer to stream interface for 'pulling' data
- L97 _private member_ `uint8* mpInternalBuffer;`
- L98 _private member_ `uint32 mInternalBufferBytes;`
- L99 _private member_ `uint32 mInternalBufferCurrentBytes;`
- L100 _private member_ `uint32 mInternalBufferIndex;`
- L102 _private member_ `M4MemHandler* mpMemSys;` — memory system used for allocations
- L104 _private member_ `uint32 mTotalBits;` — total consumed bits (reset via M4Bitstream::totalBitsClear())
- L118 _function_ `inline void M4Bitstream::totalBitsClear()` — Clear byte counter for statistics @return		none
- L130 _function_ `inline M4Bitstream::M4Bitstream() : mTail(nullptr) , mLength(0) , mStart(nullptr) , mpStreamIO(nullptr) , mpInternalBuffer(nullptr) , mInternalBufferBytes(0) , mInternalBufferCurrentBytes(0) , mInternalBufferIndex(0) , mpMemSys(nullptr) , mTotalBits(0)` — Ctor
- L149 _function_ `inline M4Bitstream::~M4Bitstream()` — Destructor
- L166 _function_ `inline void M4Bitstream::setMemoryHook(M4MemHandler& memSys)` — Set memory hook for bitstream @param		memSys @return		none
- L180 _function_ `inline void M4Bitstream::init(const uint8* bitstream, uint32 length)` — Link bitstream to indicated byte sequence @param bitstream ptr to input bytes @param length number of bytes in input stream
- L206 _function_ `inline VIDError M4Bitstream::ReadStreamBuffered(uint32& value)` — Read uint32 via stream iterator @return		VIDError
- L239 _function_ `inline void M4Bitstream::init(VIDStreamIO* pStreamIO, uint32 streamBufferBytes)` — Handle stream via stream iterator @param		pStream				stream to use @param		streamBufferBytes 	size of intermediate buffer
- L279 _function_ `inline uint32 M4Bitstream::show(const uint32 bits)` — Read # bits from stream, but DON'T move stream pointer @param bits number of bits to read @return Bits to use 'together'
- L302 _function_ `inline void M4Bitstream::skip(uint32 bits)` — Skip indicated number of bits in stream @param bits number of bits to skip
- L332 _function_ `inline bool M4Bitstream::isEof()` — Check end of file operation @return		none
- L342 _function_ `inline void M4Bitstream::align()` — Align bitstream pointer to next byte in stream
- L356 _function_ `inline void M4Bitstream::nextStartCode()` — implements next_start_code()
- L369 _function_ `inline void M4Bitstream::nextResyncMarker()`
- L375 _function_ `inline void M4Bitstream::skipResyncMarker()`
- L394 _function_ `inline uint32 M4Bitstream::showBitsByteAligned(const uint32 bits)` — implements nextbits_bytealigned() @param bits @return
- L426 _function_ `inline bool M4Bitstream::validStuffingBits()` — implements valid_stuffing_bits() @return
- L451 _function_ `inline uint32 M4Bitstream::getBits(const uint32 bits)` — Return indicated # of bits from stream and move foreward in stream @param bits Number of bits to get @return requested 'bitword'
- L463 _function_ `inline uint32 M4Bitstream::getBit()` — Return NEXT bit from stream
- L474 _function_ `inline uint32 M4Bitstream::totalBitsGet() const` — Return bits read @return		bit count since last totalBitsClear
- L483 _function_ `inline const uint32* M4Bitstream::getBaseAddr() const` — Return pointer to stream data in memory

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace vdecmpeg4`
- L12 _function_ `inline uint32 XSWAP(uint32 value)` (scope `vdecmpeg4`)

### `Source/Runtime/AVEncoder/Private/Decoders/vdecmpeg4/M4BitstreamHeaderInfo.h` (Private)


#### struct `vdecmpeg4::M4BitstreamHeaderInfo`  
`struct M4BitstreamHeaderInfo`  
_L10-23_
- L16 _public member_ `} mFlags;`
- L18 _public member_ `uint16 mQuant;` — 1-31
- L20 _public member_ `uint8* mInvQuantIntra;` — dequantizer matrix for INTRA block
- L21 _public member_ `uint8* mInvQuantInter;` — dequantizer matrix for INTER block

#### struct `vdecmpeg4::M4BitstreamHeaderInfo::(anonymous)`  
``  
_L13-16_

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace vdecmpeg4`
- L14 _member_ `uint16 mQuantType : 1;` (scope `vdecmpeg4::M4BitstreamHeaderInfo::__anond320c8760108`)
- L15 _member_ `uint32 mRounding : 1;` (scope `vdecmpeg4::M4BitstreamHeaderInfo::__anond320c8760108`)

### `Source/Runtime/AVEncoder/Private/Decoders/vdecmpeg4/M4BitstreamParser.h` (Private)


#### enum `vdecmpeg4::M4PictureType`  
`enum M4PictureType`  
_L20-27_
- desc: Picture type in input stream to decode
- L22 _public enumerator_ `M4PIC_I_VOP = 0`
- L23 _public enumerator_ `M4PIC_P_VOP`
- L24 _public enumerator_ `M4PIC_B_VOP`
- L25 _public enumerator_ `M4PIC_S_VOP`
- L26 _public enumerator_ `M4PIC_VOL`

#### class `vdecmpeg4::M4BitstreamParser`  
`class M4BitstreamParser`  
_L38-465_
- desc: This class handles the entire parsing process of the input stream. Currently, we're reading an MPEG4 compatible bitstream. Note: This class is not designed for inheritance.
- L42 _public prototype_ `M4BitstreamParser();` — Default constructor
- L45 _public prototype_ `~M4BitstreamParser();` — Destructor
- L48 _public prototype_ `VIDError init(M4Decoder* decoder, M4Bitstream* bitstream);` — Perform initialization of data structures
- L51 _public prototype_ `VIDError reset();` — Attach parser to new stream
- L54 _public prototype_ `void initFrame(int16 width, int16 height);` — Handle change/update of frame parameters
- L57 _public prototype_ `VIDError parseMPEG4ES(M4PictureType& pictureType);` — Parsing of full MPEG4-ES
- L60 _public prototype_ `VIDError findNextStartCode(uint32& absolutePos);` — Scan stream for next valid startcode
- L62 _public function_ `int32 getCbpCIntra()`
- L74 _public function_ `int32 getCbpCInter()`
- L85 _public function_ `uint8 getMBType()`
- L108 _public function_ `uint32 getCbpy(bool intra)` — get CBPY from stream This variable length code represents a pattern of non-transparent blocks with at least one non intra DC transform coefficient, in a macroblock.
- L117 _public function_ `uint16 getDCScaler(uint8 quant, bool luminance)`
- L138 _public function_ `int32 getDCSize(bool luminance)`
- L173 _public function_ `int32 getDCDiff(uint32 dc_size)`
- L181 _public function_ `void decodeInterBlock(int16* block)`
- L186 _public function_ `void decodeIntraBlock(int16* block, uint32 direction, uint32 startCoeff)`
- L191 _public function_ `int32 getQuantiserChange()`
- L223 _public function_ `void getIntraBlockNoAsm(int16* block, uint32 direction, uint32 startCoeff)` — Get a coded INTRA block from bitstream Note: We assume that the input block is set to 0. @param block ptr to int16 to receive coefficients from from bitstream @param direction 0: zigZag scan 1: horizontal scan 2: vertical scan @param startCoeff where to start in block
- L242 _public function_ `void getInterBlockNoAsm(int16* block)`
- L261 _public function_ `int32 getMv(const uint16 code)`
- L282 _public function_ `int16 GetWidth() const`
- L287 _public function_ `int16 GetHeight() const`
- L292 _public function_ `double GetLastVopTime() const`
- L297 _public function_ `const VIDStreamEvents::VOLInfo& GetVOLInfo() const`
- L302 _public prototype_ `VIDError videoPacketHeader();`
- L306 _private prototype_ `void readGMCSprite();` — Read the data from the vidConv stream
- L309 _private prototype_ `void decodeGMCSprite();` — Decode GMC sprite
- L312 _private function_ `void setMatrix(uint8* matrixOut, const uint8* matrixIn)` — Install dequant matrix
- L321 _private function_ `uint32 log2bin(uint32 value)` — Convert from log to binary
- L333 _private function_ `void getMatrix(uint8* matrix)` — Read matrix from stream
- L354 _private prototype_ `int32 getTrajaPoint();`
- L355 _private function_ `int32 getMvVlc()`
- L386 _private prototype_ `M4BitstreamParser(const M4BitstreamParser& pObj);` — Copy-constructor not implemented
- L389 _private prototype_ `const M4BitstreamParser& operator=(const M4BitstreamParser& pObj);` — Assignment operator not implemented
- L392 _public member_ `M4BitstreamHeaderInfo mHeaderInfo;`
- L393 _public member_ `VIDStreamEvents::VOLInfo mVOLInfo;`
- L395 _public member_ `uint16 mLowDelay;` — set to '1' indicates the VOL contains **NO** B-VOPs!
- L396 _public member_ `uint16 mFcodeForward;`
- L397 _public member_ `uint16 mFcodeBackward;`
- L399 _public member_ `uint32 mIntraDCThreshold;`
- L400 _public member_ `uint32 mScalability;`
- L402 _public member_ `uint16 mVopTimeIncrementBits;`
- L403 _public member_ `uint16 mVopTimeIncrementResolution;`
- L404 _public member_ `uint32 mVopTimeFixedIncrement;`
- L405 _public member_ `bool mbVopTimeFixedRate;`
- L407 _public member_ `double mTicksPerSecond;`
- L408 _public member_ `double mVopTime;`
- L410 _public member_ `uint32 mLastTimeBase;`
- L411 _public member_ `uint32 mTimeBase;`
- L413 _public member_ `uint64 mTime;`
- L414 _public member_ `uint64 mLastNonBTime;`
- L416 _public member_ `uint64 mTimePP;`
- L417 _public member_ `uint64 mTimeBP;`
- L419 _public member_ `uint32 mResyncMacroblockNumber;`
- L421 _public member_ `uint32 mSpriteUsage;`
- L423 _public member_ `uint16 mSpriteWarpingPoints;`
- L424 _public member_ `uint16 mSpriteWarpingPointsUsed;`
- L426 _public member_ `int16 mSpriteWarpingAccuracy;`
- L427 _public member_ `int16 _free;`
- L429 _public member_ `M4_VECTOR mSpriteOffset[2];`
- L430 _public member_ `M4_VECTOR mSpriteDelta[2];`
- L431 _public member_ `M4_VECTOR mSpriteShift;`
- L434 _private member_ `M4Bitstream* mBitstream;` — ptr to bitstream object
- L436 _private member_ `uint32 mShape;`
- L437 _private member_ `uint32 mQuantBits;`
- L438 _private member_ `uint32 mQuarterpel;`
- L439 _private member_ `uint32 mNewPredEnable;`
- L441 _private member_ `uint8* mScanTable[3];` — scan table relocated into locked cache
- L443 _private member_ `bool mVOLfound;`
- L444 _private member_ `uint64 mVOLCounter;`
- L446 _private member_ `bool mLoadIntraQuant;`
- L447 _private member_ `bool mLoadInterQuant;`
- L449 _private member_ `uint8 mIntraMatrix[64];`
- L450 _private member_ `uint8 mInterMatrix[64];`
- L452 _private member_ `M4_VECTOR mSprite[4];`
- L454 _private member_ `M4VlcDecoder mVLCDecoder;`
- L456 _private member_ `M4_VECTOR mRefVop[4];`
- L458 _private member_ `static uint8 mScanTableInput[3][64];`
- L460 _private member_ `static const uint32 mIntraDCThresholdTable[8];`
- L461 _private member_ `static const uint8 mDefaultIntraMatrix[64];`
- L462 _private member_ `static const uint8 mDefaultInterMatrix[64];`
- L464 _private member_ `M4Decoder* mDecoder;`

#### class `vdecmpeg4::M4BitstreamCache`  
`class M4BitstreamCache`  
_L475-492_
- L478 _public prototype_ `M4BitstreamCache();`
- L479 _public prototype_ `~M4BitstreamCache();`
- L481 _public prototype_ `VIDError Init(M4MemHandler& memSys);`
- L482 _public prototype_ `void Exit(M4MemHandler& memSys);`
- L484 _public function_ `M4BitstreamCacheEntry& Alloc()`
- L491 _private member_ `M4BitstreamCacheEntry* mpCacheEntry;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace vdecmpeg4`
- L13 _macro_ `#define M4_CLIP(X,A) (X > A) ? (A) : (X)`
- L14 _macro_ `#define M4_ABS(X) (((X)>0)?(X):-(X))`

### `Source/Runtime/AVEncoder/Private/Decoders/vdecmpeg4/M4Decoder.h` (Private)


#### class `vdecmpeg4::M4Decoder`  
`class M4Decoder`  
_L29-186_
- desc: Main decoder interface Note: This class is not designed for inheritance.
- L33 _public prototype_ `static M4Decoder* create(M4MemHandler& memHandler);` — Static creation
- L36 _public prototype_ `static void destroy(M4Decoder*& pDecoder, M4MemHandler& memHandler);` — Static destruction
- L39 _public prototype_ `VIDError init(const VIDDecoderSetup* setup);` — Initialize decoder
- L42 _public prototype_ `VIDError initBuffers(int16 width, int16 height);` — Init decoder for indicated image res
- L48 _public prototype_ `VIDError StreamSet(VIDStreamIO* pStream, VIDStreamEvents* pEvents);` — Attach a new stream interface
- L51 _public prototype_ `VIDError StreamDecode(float time, const VIDImage** result);` — Handle Stream
- L58 _public function_ `VIDError StreamEventsSet(VIDStreamEvents* pEvents)` — Attach a new event interface
- L68 _public prototype_ `VIDError StreamSeekNotify();` — Do some reset stuff if seeking happens
- L72 _private prototype_ `M4Decoder(M4MemHandler& memHandler);` — Default constructor
- L75 _private prototype_ `~M4Decoder();` — Destructor
- L78 _private prototype_ `VIDError iFrame();` — Decode I-frame
- L81 _private prototype_ `VIDError pFrame(bool gmc);` — Decode p-frame
- L84 _private prototype_ `VIDError bFrame();` — Decode B-frame
- L87 _private prototype_ `void mbIntra(M4_MB* mb, int32 x, int32 y, bool useACPredition, uint32 cbp, uint8 quant);` — Decode INTRA macroblock
- L90 _private prototype_ `void mbInter(M4_MB* mb, int32 x, int32 y, uint32 cbp, MV_PREDICTION mvPrediction, uint32 refImgNo);` — Decode INTER macroblock
- L93 _private prototype_ `void mbInterpolate(uint32 refImgForward, uint32 refImgBackward, M4_MB* mb, int32 mbx, int32 mby, uint32 cbp, uint16 mbLastIdx = 0);` — Decode INTER macroblock using interpolation for B frames
- L96 _private prototype_ `M4Decoder();` — Block usage of default constructor
- L99 _private prototype_ `M4Decoder(const M4Decoder& pObj);` — Copy-constructor is private to prevent usage!
- L102 _private prototype_ `void freeStuff();` — Helper to free resources
- L105 _private prototype_ `void freeBuffers();` — Just release buffer stuff
- L108 _private prototype_ `M4Image* AllocVidFrame();` — Try to allocate a free frame buffer
- L111 _private prototype_ `const M4Decoder& operator=(const M4Decoder& pObj);` — Assignment operator is private to prevent usage!
- L114 _private member_ `int16 mWidth;` — original image width in pixel
- L115 _private member_ `int16 mHeight;` — original image height in pixel
- L117 _private member_ `uint16 mMBWidth;` — # of horizonal 16x16 macro blocks
- L118 _private member_ `uint16 mMBHeight;` — # of vertical 16x16 macro blocks
- L120 _private member_ `uint32 mDecoderFlags;` — decoder creation flags and modes
- L122 _private member_ `M4Image* mCurrent;`
- L126 _private member_ `M4Image* mReference[2];` — 0: last I or P for backward prediction 1: forward reference VOP (most recently decoded VOP in the past)
- L130 _private member_ `M4Image* mTempImage[2];` — mTempImage[0] is used for B frame interpolation mTempImage[1] is used as additional output buffer, because Flipper works asynchronously
- L132 _private member_ `M4_MB* mIPMacroblocks;` — macroblocks for I- or P-Frame
- L133 _private member_ `M4_MB* mBMacroblocks;` — macroblocks for B-Frame
- L135 _private member_ `M4MotionVectorMgr* mMotVecMgr;`
- L137 _private member_ `M4Bitstream mBitstream;`
- L138 _private member_ `M4BitstreamParser mBitstreamParser;` — connection to our bitstream
- L140 _private member_ `M4Image** mpVidImage;`
- L141 _private member_ `uint32 mNumVidImages;`
- L144 _private member_ `uint32 mFrameCounter;`
- L145 _private member_ `M4BitstreamCache mBitstreamCache;`
- L147 _private member_ `VIDStreamIO* mpStreamIO;` — new stream interface
- L148 _private member_ `VIDStreamEvents* mpStreamEvents;`
- L150 _private member_ `M4XCmdSingleThread mXCommand;`
- L158 _public function_ `void* operator new(size_t sz, M4MemHandler& memSys)`
- L162 _public function_ `void operator delete(void* ptr)`
- L166 _public member_ `static const int32 mDequantTable[4];`
- L167 _public member_ `static const uint32 mRoundtab[16];`
- L168 _public member_ `static const uint8 mIntraMacroBlocks[8];`
- L171 _public member_ `M4MemHandler mMemSys;` — local copy of memory hooks
- L178 _public prototype_ `void SetVideoOutToBMP(const char* pFileBaseName);`
- L179 _public member_ `char mBaseName[256];`
- L184 _public member_ `void (*mCbPrintf)(const char *pMessage);`
- L185 _public prototype_ `void VIDPrintf(const char *pFormat, ...);`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace vdecmpeg4`
- L17 _macro_ `#define M4_MEM_OFFSET_LEFT_BLOCK 8 // 8 bytes` — Linear texture
- L18 _macro_ `#define M4_MEM_SHIFT_MB_TO_Y 4 // * 16`
- L19 _macro_ `#define M4_MEM_SHIFT_MB_TO_UV 3 // * 8`

### `Source/Runtime/AVEncoder/Private/Decoders/vdecmpeg4/M4Global.h` (Private)


#### enum `vdecmpeg4::M4_MBMODE`  
`enum M4_MBMODE`  
_L12-22_
- desc: supported macroblock coding types
- L14 _public enumerator_ `M4_MBMODE_INTER = 0`
- L15 _public enumerator_ `M4_MBMODE_INTER_Q = 1`
- L16 _public enumerator_ `M4_MBMODE_INTER4V = 2`
- L17 _public enumerator_ `M4_MBMODE_INTRA = 3`
- L18 _public enumerator_ `M4_MBMODE_INTRA_Q = 4`
- L19 _public enumerator_ `M4_MBMODE_STUFFING = 7`
- L20 _public enumerator_ `M4_MBMODE_NOT_CODED_PVOP = 16`
- L21 _public enumerator_ `M4_MBMODE_NOT_CODED_SVOP = 17`

#### enum `vdecmpeg4::M4_MBFLAGS`  
`enum M4_MBFLAGS`  
_L25-38_
- desc: macroblock additional flags
- L27 _public enumerator_ `M4_MBFLAG_MVTYPE_DIRECT = 0` — 00
- L28 _public enumerator_ `M4_MBFLAG_MVTYPE_INTERPOLATE = 1` — 01
- L29 _public enumerator_ `M4_MBFLAG_MVTYPE_BACKWARD = 2` — 10
- L30 _public enumerator_ `M4_MBFLAG_MVTYPE_FORWARD = 3` — 11
- L31 _public enumerator_ `M4_MBFLAG_MVTYPE_MASK = 0x03`
- L33 _public enumerator_ `M4_MBFLAG_FIELD_DCT_BIT = 0x04`
- L34 _public enumerator_ `M4_MBFLAG_FIELD_PREDICTION_BIT = 0x08`
- L36 _public enumerator_ `M4_MBFLAG_FIELD_REF_FWD_MASK = 0x30` — we use 2 bits storing the latest ref_field_top/bottom
- L37 _public enumerator_ `M4_MBFLAG_HAS_MOTION_VECTOR = 0x80`

#### struct `vdecmpeg4::M4BitstreamCacheEntry`  
`struct M4BitstreamCacheEntry`  
_L53-58_
- desc: Information per macroblock filled-in by the bitstream parser
- L55 _public member_ `uint32 mState;` — a value != 0 means that this entry is currently used
- L56 _public member_ `uint16 mDcScaler[6];` — temporary calculated dc prediction values
- L57 _public member_ `int16 mDctFromBitstream[6*64];` — parsed idct coefficients from the bitstream (6 blocks (4:1:1) by 8x8 values)

#### enum `vdecmpeg4::MV_PREDICTION`  
`enum MV_PREDICTION`  
_L61-67_
- desc: Possible motion vector prediction
- L63 _public enumerator_ `MV_PREDICTION_NONE`
- L64 _public enumerator_ `MV_PREDICTION_P_FORWARD`
- L65 _public enumerator_ `MV_PREDICTION_B_FORWARD`
- L66 _public enumerator_ `MV_PREDICTION_B_BACKWARD`

#### struct `vdecmpeg4::M4_VECTOR`  
`struct M4_VECTOR`  
_L70-74_
- desc: Motion vector
- L72 _public member_ `int32 x;`
- L73 _public member_ `int32 y;`

#### struct `vdecmpeg4::M4_MB`  
`struct M4_MB`  
_L88-103_
- L90 _public member_ `uint8 mMode : 7;` — 0
- L91 _public member_ `uint8 mModeIntra : 1;`
- L93 _public member_ `uint8 mQuant : 5;` — 1
- L94 _public member_ `uint8 mMvResidual : 1;`
- L95 _public member_ `uint8 _free : 2;`
- L97 _public member_ `uint8 mACPredDirections[6];` — 2 + 6
- L98 _public member_ `M4_VECTOR mFMv[4];` — forward motion vectors		// 8 + (4*8)
- L99 _public member_ `int16 mPredictedValues[6][M4_MBPRED_SIZE];` — 40
- L100 _public member_ `uint8 mFlags;`
- L101 _public member_ `uint8 mCbp;`
- L102 _public member_ `M4_VECTOR mBMv[4];` — backward motion vectors

#### Free symbols / members of external scopes

- L6 _namespace_ `namespace vdecmpeg4`
- L41 _macro_ `#define M4MAX(A,B) ((A)>(B)?(A):(B))`
- L45 _macro_ `#define M4MIN(A,B) ((A)<(B)?(A):(B))`
- L48 _macro_ `#define M4_MBPRED_SIZE 15`

### `Source/Runtime/AVEncoder/Private/Decoders/vdecmpeg4/M4Image.h` (Private)


#### class `vdecmpeg4::M4Image`  
`class M4Image`  
_L21-147_
- L26 _public member_ `VIDImage mImage;` — original image (without edges) A pointer to this will be returned to the caller
- L29 _public member_ `VIDImageInfo mImageInfo;` — Image information
- L32 _private function_ `M4Image()`
- L42 _public prototype_ `static M4Image* create(M4Decoder* decoder, int16 width, int16 height, bool poolMem = true);` — Construction and allocation of image helper
- L45 _public prototype_ `static void destroy(M4Image*& pImage, M4Decoder* decoder);` — Destruction
- L48 _public prototype_ `void Black();` — Clear buffer
- L51 _public function_ `void RefAdd()` — Reference increase
- L57 _public function_ `void RefRemove()` — Reference decrease and free mem if drops to 0 references
- L70 _public function_ `int32 RefGet() const` — Return current reference value
- L76 _public function_ `M4Decoder& getDecoder() const` — Return reference to our decoder
- L82 _public prototype_ `static void poolMemCb(void* memPtr, uint32 size, uint32 poolFlags, void* userData);` — Pool mem allocation callback
- L84 _public function_ `void* operator new(size_t sz, M4MemHandler& memSys)`
- L94 _public function_ `void operator delete(void* ptr)`
- L101 _private member_ `uint8* mBaseMem;` — Ptr to allocated private base mem
- L104 _private member_ `M4Decoder* mDecoder;` — Reference to our handling decoder
- L107 _private member_ `volatile int32 mRefCount;` — Actual reference count
- L111 _private prototype_ `~M4Image();` — Destructor. Regular destruction happens from static method
- L114 _private prototype_ `void setup(uint8* ptr, uint32 flags);` — Perform memory ptr setup and initialization
- L117 _private prototype_ `M4Image(const M4Image& pObj);` — Copy Constructor [not implemented]
- L120 _private prototype_ `const M4Image &operator=(const M4Image& pObj);` — Assignment operator [not implemented]
- L131 _private prototype_ `void saveBMP(const char* pBaseName, uint32 frameCounter);` — Save image to file on host
- L135 _private prototype_ `void getRGB(uint8* dst, int32 dstStride);` — get image as bgr
- L138 _private prototype_ `void initImageSave();` — init image save routines
- L140 _private member_ `static int32 mTabRgbY[256];`
- L141 _private member_ `static int32 mTabBU[256];`
- L142 _private member_ `static int32 mTabGU[256];`
- L143 _private member_ `static int32 mTabGV[256];`
- L144 _private member_ `static int32 mTabRV[256];`
- L145 _private member_ `static bool mInitImageSave;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace vdecmpeg4`
- L12 _macro_ `#define EDGE_SIZE 32` — image buffer top, left, right and bottom edge size. Must be 32 in this version.
- L15 _macro_ `#define EDGE_SIZE2 (EDGE_SIZE/2)` — image buffer edge size for u and v buffer (half resolution)
- L18 _macro_ `#define ALIGNMENT_TRASH (64)` — some additional bytes required for allocation alignment
- L153 _function_ `inline void swapM4Image(M4Image*& img1, M4Image*& img2)` (scope `vdecmpeg4`)

### `Source/Runtime/AVEncoder/Private/Decoders/vdecmpeg4/M4InvQuant.h` (Private)


#### Free symbols / members of external scopes

- L6 _namespace_ `namespace vdecmpeg4`
- L9 _prototype_ `void M4InvQuantType0Intra(int16* output, const int16* input, uint8 quantiserScale, uint16 DCScaler);` (scope `vdecmpeg4`)
- L10 _prototype_ `void M4InvQuantType0Inter(int16* output, const int16* input, uint8 quantiserScale);` (scope `vdecmpeg4`)
- L11 _prototype_ `void M4InvQuantType1Intra(int16* output, const int16* input, uint8 quantiserScale, uint16 DCScaler, const uint8* dequantMtx);` (scope `vdecmpeg4`)
- L12 _prototype_ `void M4InvQuantType1Inter(int16* output, const int16* input, uint8 quantiserScale, const uint8* dequantMtx);` (scope `vdecmpeg4`)

### `Source/Runtime/AVEncoder/Private/Decoders/vdecmpeg4/M4MemOps.h` (Private)


#### class `vdecmpeg4::MemOpOffsets`  
`class MemOpOffsets`  
_L16-32_
- L19 _public function_ `MemOpOffsets() : mCurrentPitch(0)`
- L21 _public prototype_ `~MemOpOffsets() = default;`
- L23 _public prototype_ `void init(int32 pitch);`
- L25 _public member_ `uint16 blockIdxY[64];`
- L26 _public member_ `uint16 blockIdxUV[64];`
- L28 _public member_ `uint32 blockIdxY4[8];`
- L29 _public member_ `uint32 blockIdxUV4[8];`
- L31 _public member_ `int32 mCurrentPitch;`

#### Free symbols / members of external scopes

- L6 _namespace_ `namespace vdecmpeg4`
- L9 _prototype_ `void M4MemOpIntraMBAll(void* mCurrent, int32 mbx, int32 mby, void* dct);` (scope `vdecmpeg4`)
- L10 _prototype_ `void M4MemOpInterMBCopyAll(void* mCurrent, int32 x, int32 y, void* mReference);` (scope `vdecmpeg4`)
- L11 _prototype_ `void M4MemOpInterMBAdd(void* mCurrent, int32 x, int32 y, void* dctData, uint32 cpb);` (scope `vdecmpeg4`)
- L12 _prototype_ `void M4MemHalfPelInterpolate(void* dst, void* src, int32 stride, int32 xpos, int32 ypos, void* mv, uint32 rounding, bool b4x4=false);` (scope `vdecmpeg4`)
- L13 _prototype_ `void M4MemOpInterpolateAll(void* mCurrent, int32 mbx, int32 mby, void* mReference);` (scope `vdecmpeg4`)

### `Source/Runtime/AVEncoder/Private/Decoders/vdecmpeg4/M4Memory.h` (Private)


#### class `vdecmpeg4::M4MemHandler`  
`class M4MemHandler`  
_L33-64_
- L37 _public function_ `void init(VIDAllocator cbMem, VIDDeallocator cbFree)` — Init global decoder instance memory system
- L44 _public function_ `void* malloc(size_t size, size_t alignment = 32)` — Memory allocation with possible alignment
- L52 _public function_ `void free(void* ptr)` — Memory release
- L62 _private member_ `VIDAllocator mAllocCB;`
- L63 _private member_ `VIDDeallocator mFreeCB;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace vdecmpeg4`
- L14 _macro_ `#define M4_MEMORY_HANDLER \` — We use the following two macros for 'automatic' overloading of the new and delete operations. The effect is a mapping of all memory allocations to the user-established handler

### `Source/Runtime/AVEncoder/Private/Decoders/vdecmpeg4/M4MotionVectorMgr.h` (Private)


#### class `vdecmpeg4::M4MotionVectorMgr`  
`class M4MotionVectorMgr`  
_L13-132_
- L17 _public prototype_ `static M4MotionVectorMgr* create(M4Decoder* pDecoder, M4MemHandler& memSys);` — Creation
- L20 _public prototype_ `static void destroy(M4MotionVectorMgr*& pMgr, M4MemHandler& memSys);` — Destruction
- L25 _public prototype_ `void init();` — Init members for current frame
- L28 _public prototype_ `void readMvForward(M4_MB* mb);` — Read the motion vector residual from the bitstream
- L31 _public prototype_ `void predictAddForward(M4_MB* mb, int32 mbx, int32 mby);` — Add the residual to the prediction
- L34 _public function_ `void addMv(M4_VECTOR& res, uint16 code, const M4_VECTOR& inputMv, const M4_VECTOR& predictor)` — Add predictor and input motion vector based on forward/backward code
- L64 _public function_ `void addMvForward(M4_VECTOR& res, const M4_VECTOR& inputMv, const M4_VECTOR& predictor)` — Add predicted motion vector to FORWARD prediction
- L91 _public function_ `void readMv(M4_VECTOR& res, uint16 code)` — Read motion vector residual from file
- L99 _public member_ `static const M4_VECTOR MV_ZERO;` — Zero motion vector
- L101 _public prototype_ `void* operator new(size_t sz, M4MemHandler& memSys);`
- L102 _public prototype_ `void operator delete(void* ptr);`
- L107 _private prototype_ `M4MotionVectorMgr(M4Decoder* decoder);` — Default constructor
- L110 _private prototype_ `~M4MotionVectorMgr() = default;` — Destructor
- L113 _private prototype_ `void _predictMv(M4_VECTOR& res, int32 mbx, int32 mby, uint32 block);` — motion vector prediction
- L116 _private prototype_ `M4MotionVectorMgr();` — Default constructor
- L119 _private prototype_ `M4MotionVectorMgr(const M4MotionVectorMgr &pObj);` — Copy-constructor not implemented
- L122 _private prototype_ `const M4MotionVectorMgr &operator=(const M4MotionVectorMgr &pObj);` — Assignment operator not implemented
- L124 _private member_ `int32 mMvClipHigh;` — motion vector upper border
- L125 _private member_ `int32 mMvClipLow;` — motion vector lower border
- L126 _private member_ `int32 mMvClipRange;` — motion vector range
- L129 _private member_ `M4Decoder* mDecoder;` — Reference to our decoder class

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace vdecmpeg4`
- L136 _function_ `inline void M4MotionVectorClear(M4_MB* mb)` (scope `vdecmpeg4`) — GENERIC: Set all motion vectors to 0

### `Source/Runtime/AVEncoder/Private/Decoders/vdecmpeg4/M4Prediction.h` (Private)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace vdecmpeg4`
- L10 _macro_ `#define M4ABS(X) (((X)>0)?(X):-(X))`
- L11 _macro_ `#define M4DIVDIV(A,B) ( (A) > 0 ? ((A)+((B)>>1))/(B) : ((A)-((B)>>1))/(B) )`
- L15 _prototype_ `void M4PredictionInit(M4_MB* macroblocks, int32 mbx, int32 mby, int32 pMBWidth, uint32 block, uint8 currentQuant, uint16 iDcScaler, int16* output);` (scope `vdecmpeg4`)
- L16 _prototype_ `void M4PredictionAdd(M4_MB* mb, int16* dctBlock, uint32 block, uint16 iDcScaler, const int16* pPrediction);` (scope `vdecmpeg4`)
- L18 _function_ `inline int32 rescale(int32 predictQuant, int32 currentQuant, int32 coeff)` (scope `vdecmpeg4`)

### `Source/Runtime/AVEncoder/Private/Decoders/vdecmpeg4/M4VlcData.inl` (Private)


#### Free symbols / members of external scopes

- L6 _namespace_ `namespace vdecmpeg4`
- L9 _member_ `uint8 M4VlcDecoder::mMaxLevel[4][64] = { {` (scope `vdecmpeg4::M4VlcDecoder`)
- L56 _member_ `uint8 M4VlcDecoder::mMaxRun[4][256] = { {` (scope `vdecmpeg4::M4VlcDecoder`)
- L199 _member_ `const M4_VLC M4VlcDecoder::mTabCbpCIntra[64] = { VLC_ERROR, MK_VLC(20,6), MK_VLC(36,6), MK_VLC(52,6), MK_VLC(4,4), MK_VLC(4,4), MK_VLC(4,4), MK_VLC(4,4), MK_VLC(19,3), MK_VLC(19,3), MK_VLC(19,3), MK_VLC(19,3), MK_VLC(19,3), MK_VLC(19,3), MK_VLC(19,3), MK_VLC(19,3), MK_VLC(35,3), MK_VLC(35,3), MK_VLC(35,3), MK_VLC(35,3), MK_VLC(35,3), MK_VLC(35,3), MK_VLC(35,3), MK_VLC(35,3), MK_VLC(51,3), MK_VLC(51,3), MK_VLC(51,3), MK_VLC(51,3), MK_VLC(51,3), MK_VLC(51,3), MK_VLC(51,3), MK_VLC(51,3), MK_VLC(3, 1), MK_VLC(3, 1), MK_VLC(3, 1), MK_VLC(3, 1), MK_VLC(3, 1), MK_VLC(3, 1), MK_VLC(3, 1), MK_VLC(3, 1), MK_VLC(3, 1), MK_VLC(3, 1), MK_VLC(3, 1), MK_VLC(3, 1), MK_VLC(3, 1), MK_VLC(3, 1), MK_VLC(3, 1), MK_VLC(3, 1), MK_VLC(3, 1), MK_VLC(3, 1), MK_VLC(3, 1), MK_VLC(3, 1), MK_VLC(3, 1), MK_VLC(3, 1), MK_VLC(3, 1), MK_VLC(3, 1), MK_VLC(3, 1), MK_VLC(3, 1), MK_VLC(3, 1), MK_VLC(3, 1), MK_VLC(3, 1), MK_VLC(3, 1), MK_VLC(3, 1), MK_VLC(3, 1) };` (scope `vdecmpeg4::M4VlcDecoder`)
- L217 _member_ `const M4_VLC M4VlcDecoder::mTabCbpCInter[257] = { VLC_ERROR, MK_VLC(255,9), MK_VLC(52,9), MK_VLC(36,9), MK_VLC(20,9), MK_VLC(49,9), MK_VLC(35,8), MK_VLC(35,8), MK_VLC(19,8), MK_VLC(19,8), MK_VLC(50,8), MK_VLC(50,8), MK_VLC(51,7), MK_VLC(51,7), MK_VLC(51,7), MK_VLC(51,7), MK_VLC(34,7), MK_VLC(34,7), MK_VLC(34,7), MK_VLC(34,7), MK_VLC(18,7), MK_VLC(18,7), MK_VLC(18,7), MK_VLC(18,7), MK_VLC(33,7), MK_VLC(33,7), MK_VLC(33,7), MK_VLC(33,7), MK_VLC(17,7), MK_VLC(17,7), MK_VLC(17,7), MK_VLC(17,7), MK_VLC(4,6), MK_VLC(4,6), MK_VLC(4,6), MK_VLC(4,6), MK_VLC(4,6), MK_VLC(4,6), MK_VLC(4,6), MK_VLC(4,6), MK_VLC(48,6), MK_VLC(48,6), MK_VLC(48,6), MK_VLC(48,6), MK_VLC(48,6), MK_VLC(48,6), MK_VLC(48,6), MK_VLC(48,6), MK_VLC(3,5), MK_VLC(3,5), MK_VLC(3,5), MK_VLC(3,5), MK_VLC(3,5), MK_VLC(3,5), MK_VLC(3,5), MK_VLC(3,5), MK_VLC(3,5), MK_VLC(3,5), MK_VLC(3,5), MK_VLC(3,5), MK_VLC(3,5), MK_VLC(3,5), MK_VLC(3,5), MK_VLC(3,5), MK_VLC(32,4), MK_VLC(32,4), MK_VLC(32,4), MK_VLC(32,4), MK_VLC(32,4), MK_VLC(32,4), MK_VLC(32,4), MK_VLC(32,4), MK_VLC(32,4), MK_VLC(32,4), MK_VLC(32,4), MK_VLC(32,4), MK_VLC(32,4), MK_VLC(32,4), MK_VLC(32,4), MK_VLC(32,4), MK_VLC(32,4), MK_VLC(32,4), MK_VLC(32,4), MK_VLC(32,4), MK_VLC(32,4), MK_VLC(32,4), MK_VLC(32,4), MK_VLC(32,4), MK_VLC(32,4), MK_VLC(32,4), MK_VLC(32,4), MK_VLC(32,4), MK_VLC(32,4), MK_VLC(32,4), MK_VLC(32,4), MK_VLC(32,4), MK_VLC(16,4), MK_VLC(16,4), MK_VLC(16,4), MK_VLC(16,4), MK_VLC(16,4), MK_VLC(16,4), MK_VLC(16,4), MK_VLC(16,4), MK_VLC(16,4), MK_VLC ...` (scope `vdecmpeg4::M4VlcDecoder`)
- L251 _member_ `const M4_VLC M4VlcDecoder::mTabCbpY[64] = { VLC_ERROR, VLC_ERROR, MK_VLC(6,6), MK_VLC(9,6), MK_VLC(8,5), MK_VLC(8,5), MK_VLC(4,5), MK_VLC(4,5), MK_VLC(2,5), MK_VLC(2,5), MK_VLC(1,5), MK_VLC(1,5), MK_VLC(0,4), MK_VLC(0,4), MK_VLC(0,4), MK_VLC(0,4), MK_VLC(12,4), MK_VLC(12,4), MK_VLC(12,4), MK_VLC(12,4), MK_VLC(10,4), MK_VLC(10,4), MK_VLC(10,4), MK_VLC(10,4), MK_VLC(14,4), MK_VLC(14,4), MK_VLC(14,4), MK_VLC(14,4), MK_VLC(5,4), MK_VLC(5,4), MK_VLC(5,4), MK_VLC(5,4), MK_VLC(13,4), MK_VLC(13,4), MK_VLC(13,4), MK_VLC(13,4), MK_VLC(3,4), MK_VLC(3,4), MK_VLC(3,4), MK_VLC(3,4), MK_VLC(11,4), MK_VLC(11,4), MK_VLC(11,4), MK_VLC(11,4), MK_VLC(7,4), MK_VLC(7,4), MK_VLC(7,4), MK_VLC(7,4), MK_VLC(15, 2), MK_VLC(15, 2), MK_VLC(15, 2), MK_VLC(15, 2), MK_VLC(15, 2), MK_VLC(15, 2), MK_VLC(15, 2), MK_VLC(15, 2), MK_VLC(15, 2), MK_VLC(15, 2), MK_VLC(15, 2), MK_VLC(15, 2), MK_VLC(15, 2), MK_VLC(15, 2), MK_VLC(15, 2), MK_VLC(15, 2) };` (scope `vdecmpeg4::M4VlcDecoder`)
- L264 _member_ `M4_VLC M4VlcDecoder::mTabTMNMV0[] = { MK_VLC(3,4), MK_VLC(-3,4), MK_VLC(2,3), MK_VLC(2,3), MK_VLC(-2,3), MK_VLC(-2,3), MK_VLC(1,2), MK_VLC(1,2), MK_VLC(1,2), MK_VLC(1,2), MK_VLC(-1,2), MK_VLC(-1,2), MK_VLC(-1,2), MK_VLC(-1,2) };` (scope `vdecmpeg4::M4VlcDecoder`)
- L270 _member_ `M4_VLC M4VlcDecoder::mTabTMNMV1[] = { MK_VLC(12,10), MK_VLC(-12,10), MK_VLC(11,10), MK_VLC(-11,10), MK_VLC(10,9), MK_VLC(10,9), MK_VLC(-10,9), MK_VLC(-10,9), MK_VLC(9,9), MK_VLC(9,9), MK_VLC(-9,9), MK_VLC(-9,9), MK_VLC(8,9), MK_VLC(8,9), MK_VLC(-8,9), MK_VLC(-8,9), MK_VLC(7,7), MK_VLC(7,7), MK_VLC(7,7), MK_VLC(7,7), MK_VLC(7,7), MK_VLC(7,7), MK_VLC(7,7), MK_VLC(7,7), MK_VLC(-7,7), MK_VLC(-7,7), MK_VLC(-7,7), MK_VLC(-7,7), MK_VLC(-7,7), MK_VLC(-7,7), MK_VLC(-7,7), MK_VLC(-7,7), MK_VLC(6,7), MK_VLC(6,7), MK_VLC(6,7), MK_VLC(6,7), MK_VLC(6,7), MK_VLC(6,7), MK_VLC(6,7), MK_VLC(6,7), MK_VLC(-6,7), MK_VLC(-6,7), MK_VLC(-6,7), MK_VLC(-6,7), MK_VLC(-6,7), MK_VLC(-6,7), MK_VLC(-6,7), MK_VLC(-6,7), MK_VLC(5,7), MK_VLC(5,7), MK_VLC(5,7), MK_VLC(5,7), MK_VLC(5,7), MK_VLC(5,7), MK_VLC(5,7), MK_VLC(5,7), MK_VLC(-5,7), MK_VLC(-5,7), MK_VLC(-5,7), MK_VLC(-5,7), MK_VLC(-5,7), MK_VLC(-5,7), MK_VLC(-5,7), MK_VLC(-5,7), MK_VLC(4,6), MK_VLC(4,6), MK_VLC(4,6), MK_VLC(4,6), MK_VLC(4,6), MK_VLC(4,6), MK_VLC(4,6), MK_VLC(4,6), MK_VLC(4,6), MK_VLC(4,6), MK_VLC(4,6), MK_VLC(4,6), MK_VLC(4,6), MK_VLC(4,6), MK_VLC(4,6), MK_VLC(4,6), MK_VLC(-4,6), MK_VLC(-4,6), MK_VLC(-4,6), MK_VLC(-4,6), MK_VLC(-4,6), MK_VLC(-4,6), MK_VLC(-4,6), MK_VLC(-4,6), MK_VLC(-4,6), MK_VLC(-4,6), MK_VLC(-4,6), MK_VLC(-4,6), MK_VLC(-4,6), MK_VLC(-4,6), MK_VLC(-4,6), MK_VLC(-4,6) };` (scope `vdecmpeg4::M4VlcDecoder`)
- L284 _member_ `M4_VLC M4VlcDecoder::mTabTMNMV2[] = { MK_VLC(32,12), MK_VLC(-32,12), MK_VLC(31,12), MK_VLC(-31,12), MK_VLC(30,11), MK_VLC(30,11), MK_VLC(-30,11), MK_VLC(-30,11), MK_VLC(29,11), MK_VLC(29,11), MK_VLC(-29,11), MK_VLC(-29,11), MK_VLC(28,11), MK_VLC(28,11), MK_VLC(-28,11), MK_VLC(-28,11), MK_VLC(27,11), MK_VLC(27,11), MK_VLC(-27,11), MK_VLC(-27,11), MK_VLC(26,11), MK_VLC(26,11), MK_VLC(-26,11), MK_VLC(-26,11), MK_VLC(25,11), MK_VLC(25,11), MK_VLC(-25,11), MK_VLC(-25,11), MK_VLC(24,10), MK_VLC(24,10), MK_VLC(24,10), MK_VLC(24,10), MK_VLC(-24,10), MK_VLC(-24,10), MK_VLC(-24,10), MK_VLC(-24,10), MK_VLC(23,10), MK_VLC(23,10), MK_VLC(23,10), MK_VLC(23,10), MK_VLC(-23,10), MK_VLC(-23,10), MK_VLC(-23,10), MK_VLC(-23,10), MK_VLC(22,10), MK_VLC(22,10), MK_VLC(22,10), MK_VLC(22,10), MK_VLC(-22,10), MK_VLC(-22,10), MK_VLC(-22,10), MK_VLC(-22,10), MK_VLC(21,10), MK_VLC(21,10), MK_VLC(21,10), MK_VLC(21,10), MK_VLC(-21,10), MK_VLC(-21,10), MK_VLC(-21,10), MK_VLC(-21,10), MK_VLC(20,10), MK_VLC(20,10), MK_VLC(20,10), MK_VLC(20,10), MK_VLC(-20,10), MK_VLC(-20,10), MK_VLC(-20,10), MK_VLC(-20,10), MK_VLC(19,10), MK_VLC(19,10), MK_VLC(19,10), MK_VLC(19,10), MK_VLC(-19,10), MK_VLC(-19,10), MK_VLC(-19,10), MK_VLC(-19,10), MK_VLC(18,10), MK_VLC(18,10), MK_VLC(18,10), MK_VLC(18,10), MK_VLC(-18,10), MK_VLC(-18,10), MK_VLC(-18,10), MK_VLC(-18,10), MK_VLC(17,10), MK_VLC(17,10), MK_VLC(17,10), MK_VLC(17,10), MK_VLC(-17,10), MK_VLC(-17,10), MK_VLC(-17,10), MK_VLC(-17,10), MK_VLC(16,10), MK_VLC(16,10), MK_VLC ...` (scope `vdecmpeg4::M4VlcDecoder`)
- L304 _member_ `M4_VLC M4VlcDecoder::mTabDCT3D0[] = { MK_VLC(4225,7), MK_VLC(4209,7), MK_VLC(4193,7), MK_VLC(4177,7), MK_VLC(193,7), MK_VLC(177,7), MK_VLC(161,7), MK_VLC(4,7), MK_VLC(4161,6), MK_VLC(4161,6), MK_VLC(4145,6), MK_VLC(4145,6), MK_VLC(4129,6), MK_VLC(4129,6), MK_VLC(4113,6), MK_VLC(4113,6), MK_VLC(145,6), MK_VLC(145,6), MK_VLC(129,6), MK_VLC(129,6), MK_VLC(113,6), MK_VLC(113,6), MK_VLC(97,6), MK_VLC(97,6), MK_VLC(18,6), MK_VLC(18,6), MK_VLC(3,6), MK_VLC(3,6), MK_VLC(81,5), MK_VLC(81,5), MK_VLC(81,5), MK_VLC(81,5), MK_VLC(65,5), MK_VLC(65,5), MK_VLC(65,5), MK_VLC(65,5), MK_VLC(49,5), MK_VLC(49,5), MK_VLC(49,5), MK_VLC(49,5), MK_VLC(4097,4), MK_VLC(4097,4), MK_VLC(4097,4), MK_VLC(4097,4), MK_VLC(4097,4), MK_VLC(4097,4), MK_VLC(4097,4), MK_VLC(4097,4), MK_VLC(1,2), MK_VLC(1,2), MK_VLC(1,2), MK_VLC(1,2), MK_VLC(1,2), MK_VLC(1,2), MK_VLC(1,2), MK_VLC(1,2), MK_VLC(1,2), MK_VLC(1,2), MK_VLC(1,2), MK_VLC(1,2), MK_VLC(1,2), MK_VLC(1,2), MK_VLC(1,2), MK_VLC(1,2), MK_VLC(1,2), MK_VLC(1,2), MK_VLC(1,2), MK_VLC(1,2), MK_VLC(1,2), MK_VLC(1,2), MK_VLC(1,2), MK_VLC(1,2), MK_VLC(1,2), MK_VLC(1,2), MK_VLC(1,2), MK_VLC(1,2), MK_VLC(1,2), MK_VLC(1,2), MK_VLC(1,2), MK_VLC(1,2), MK_VLC(17,3), MK_VLC(17,3), MK_VLC(17,3), MK_VLC(17,3), MK_VLC(17,3), MK_VLC(17,3), MK_VLC(17,3), MK_VLC(17,3), MK_VLC(17,3), MK_VLC(17,3), MK_VLC(17,3), MK_VLC(17,3), MK_VLC(17,3), MK_VLC(17,3), MK_VLC(17,3), MK_VLC(17,3), MK_VLC(33,4), MK_VLC(33,4), MK_VLC(33,4), MK_VLC(33,4), MK_VLC(33,4), MK_VLC(33,4), MK_VLC(33,4), MK_VLC ...` (scope `vdecmpeg4::M4VlcDecoder`)
- L327 _member_ `M4_VLC M4VlcDecoder::mTabDCT3D1[] = { MK_VLC(9,10), MK_VLC(8,10), MK_VLC(4481,9), MK_VLC(4481,9), MK_VLC(4465,9), MK_VLC(4465,9), MK_VLC(4449,9), MK_VLC(4449,9), MK_VLC(4433,9), MK_VLC(4433,9), MK_VLC(4417,9), MK_VLC(4417,9), MK_VLC(4401,9), MK_VLC(4401,9), MK_VLC(4385,9), MK_VLC(4385,9), MK_VLC(4369,9), MK_VLC(4369,9), MK_VLC(4098,9), MK_VLC(4098,9), MK_VLC(353,9), MK_VLC(353,9), MK_VLC(337,9), MK_VLC(337,9), MK_VLC(321,9), MK_VLC(321,9), MK_VLC(305,9), MK_VLC(305,9), MK_VLC(289,9), MK_VLC(289,9), MK_VLC(273,9), MK_VLC(273,9), MK_VLC(257,9), MK_VLC(257,9), MK_VLC(241,9), MK_VLC(241,9), MK_VLC(66,9), MK_VLC(66,9), MK_VLC(50,9), MK_VLC(50,9), MK_VLC(7,9), MK_VLC(7,9), MK_VLC(6,9), MK_VLC(6,9), MK_VLC(4353,8), MK_VLC(4353,8), MK_VLC(4353,8), MK_VLC(4353,8), MK_VLC(4337,8), MK_VLC(4337,8), MK_VLC(4337,8), MK_VLC(4337,8), MK_VLC(4321,8), MK_VLC(4321,8), MK_VLC(4321,8), MK_VLC(4321,8), MK_VLC(4305,8), MK_VLC(4305,8), MK_VLC(4305,8), MK_VLC(4305,8), MK_VLC(4289,8), MK_VLC(4289,8), MK_VLC(4289,8), MK_VLC(4289,8), MK_VLC(4273,8), MK_VLC(4273,8), MK_VLC(4273,8), MK_VLC(4273,8), MK_VLC(4257,8), MK_VLC(4257,8), MK_VLC(4257,8), MK_VLC(4257,8), MK_VLC(4241,8), MK_VLC(4241,8), MK_VLC(4241,8), MK_VLC(4241,8), MK_VLC(225,8), MK_VLC(225,8), MK_VLC(225,8), MK_VLC(225,8), MK_VLC(209,8), MK_VLC(209,8), MK_VLC(209,8), MK_VLC(209,8), MK_VLC(34,8), MK_VLC(34,8), MK_VLC(34,8), MK_VLC(34,8), MK_VLC(19,8), MK_VLC(19,8), MK_VLC(19,8), MK_VLC(19,8), MK_VLC(5,8), MK_VLC(5,8), MK_VLC(5,8), MK_VLC(5,8) };` (scope `vdecmpeg4::M4VlcDecoder`)
- L347 _member_ `M4_VLC M4VlcDecoder::mTabDCT3D2[] = { MK_VLC(4114,11), MK_VLC(4114,11), MK_VLC(4099,11), MK_VLC(4099,11), MK_VLC(11,11), MK_VLC(11,11), MK_VLC(10,11), MK_VLC(10,11), MK_VLC(4545,10), MK_VLC(4545,10), MK_VLC(4545,10), MK_VLC(4545,10), MK_VLC(4529,10), MK_VLC(4529,10), MK_VLC(4529,10), MK_VLC(4529,10), MK_VLC(4513,10), MK_VLC(4513,10), MK_VLC(4513,10), MK_VLC(4513,10), MK_VLC(4497,10), MK_VLC(4497,10), MK_VLC(4497,10), MK_VLC(4497,10), MK_VLC(146,10), MK_VLC(146,10), MK_VLC(146,10), MK_VLC(146,10), MK_VLC(130,10), MK_VLC(130,10), MK_VLC(130,10), MK_VLC(130,10), MK_VLC(114,10), MK_VLC(114,10), MK_VLC(114,10), MK_VLC(114,10), MK_VLC(98,10), MK_VLC(98,10), MK_VLC(98,10), MK_VLC(98,10), MK_VLC(82,10), MK_VLC(82,10), MK_VLC(82,10), MK_VLC(82,10), MK_VLC(51,10), MK_VLC(51,10), MK_VLC(51,10), MK_VLC(51,10), MK_VLC(35,10), MK_VLC(35,10), MK_VLC(35,10), MK_VLC(35,10), MK_VLC(20,10), MK_VLC(20,10), MK_VLC(20,10), MK_VLC(20,10), MK_VLC(12,11), MK_VLC(12,11), MK_VLC(21,11), MK_VLC(21,11), MK_VLC(369,11), MK_VLC(369,11), MK_VLC(385,11), MK_VLC(385,11), MK_VLC(4561,11), MK_VLC(4561,11), MK_VLC(4577,11), MK_VLC(4577,11), MK_VLC(4593,11), MK_VLC(4593,11), MK_VLC(4609,11), MK_VLC(4609,11), MK_VLC(22,12), MK_VLC(36,12), MK_VLC(67,12), MK_VLC(83,12), MK_VLC(99,12), MK_VLC(162,12), MK_VLC(401,12), MK_VLC(417,12), MK_VLC(4625,12), MK_VLC(4641,12), MK_VLC(4657,12), MK_VLC(4673,12), MK_VLC(4689,12), MK_VLC(4705,12), MK_VLC(4721,12), MK_VLC(4737,12), MK_VLC(7167,7), MK_VLC(7167,7), MK_VLC(7167,7), MK_ ...` (scope `vdecmpeg4::M4VlcDecoder`)
- L377 _member_ `M4_VLC M4VlcDecoder::mTabDCT3D3[] = { MK_VLC(0x10401, 7), MK_VLC(0x10301, 7), MK_VLC(0x00601, 7), MK_VLC(0x10501, 7), MK_VLC(0x00701, 7), MK_VLC(0x00202, 7), MK_VLC(0x00103, 7), MK_VLC(0x00009, 7), MK_VLC(0x10002, 6), MK_VLC(0x10002, 6), MK_VLC(0x00501, 6), MK_VLC(0x00501, 6), MK_VLC(0x10201, 6), MK_VLC(0x10201, 6), MK_VLC(0x10101, 6), MK_VLC(0x10101, 6), MK_VLC(0x00401, 6), MK_VLC(0x00401, 6), MK_VLC(0x00301, 6), MK_VLC(0x00301, 6), MK_VLC(0x00008, 6), MK_VLC(0x00008, 6), MK_VLC(0x00007, 6), MK_VLC(0x00007, 6), MK_VLC(0x00102, 6), MK_VLC(0x00102, 6), MK_VLC(0x00006, 6), MK_VLC(0x00006, 6), MK_VLC(0x00201, 5), MK_VLC(0x00201, 5), MK_VLC(0x00201, 5), MK_VLC(0x00201, 5), MK_VLC(0x00005, 5), MK_VLC(0x00005, 5), MK_VLC(0x00005, 5), MK_VLC(0x00005, 5), MK_VLC(0x00004, 5), MK_VLC(0x00004, 5), MK_VLC(0x00004, 5), MK_VLC(0x00004, 5), MK_VLC(0x10001, 4), MK_VLC(0x10001, 4), MK_VLC(0x10001, 4), MK_VLC(0x10001, 4), MK_VLC(0x10001, 4), MK_VLC(0x10001, 4), MK_VLC(0x10001, 4), MK_VLC(0x10001, 4), MK_VLC(0x00001, 2), MK_VLC(0x00001, 2), MK_VLC(0x00001, 2), MK_VLC(0x00001, 2), MK_VLC(0x00001, 2), MK_VLC(0x00001, 2), MK_VLC(0x00001, 2), MK_VLC(0x00001, 2), MK_VLC(0x00001, 2), MK_VLC(0x00001, 2), MK_VLC(0x00001, 2), MK_VLC(0x00001, 2), MK_VLC(0x00001, 2), MK_VLC(0x00001, 2), MK_VLC(0x00001, 2), MK_VLC(0x00001, 2), MK_VLC(0x00001, 2), MK_VLC(0x00001, 2), MK_VLC(0x00001, 2), MK_VLC(0x00001, 2), MK_VLC(0x00001, 2), MK_VLC(0x00001, 2), MK_VLC(0x00001, 2), MK_VLC(0x00001, 2), MK_VLC(0x00001, 2), MK ...` (scope `vdecmpeg4::M4VlcDecoder`) — Intra Table, i >= 512
- L410 _member_ `M4_VLC M4VlcDecoder::mTabDCT3D4[] = { MK_VLC(0x00012,10), MK_VLC(0x00011,10), MK_VLC(0x10e01, 9), MK_VLC(0x10e01, 9), MK_VLC(0x10d01, 9), MK_VLC(0x10d01, 9), MK_VLC(0x10c01, 9), MK_VLC(0x10c01, 9), MK_VLC(0x10b01, 9), MK_VLC(0x10b01, 9), MK_VLC(0x10a01, 9), MK_VLC(0x10a01, 9), MK_VLC(0x10102, 9), MK_VLC(0x10102, 9), MK_VLC(0x10004, 9), MK_VLC(0x10004, 9), MK_VLC(0x00c01, 9), MK_VLC(0x00c01, 9), MK_VLC(0x00b01, 9), MK_VLC(0x00b01, 9), MK_VLC(0x00702, 9), MK_VLC(0x00702, 9), MK_VLC(0x00602, 9), MK_VLC(0x00602, 9), MK_VLC(0x00502, 9), MK_VLC(0x00502, 9), MK_VLC(0x00303, 9), MK_VLC(0x00303, 9), MK_VLC(0x00203, 9), MK_VLC(0x00203, 9), MK_VLC(0x00106, 9), MK_VLC(0x00106, 9), MK_VLC(0x00105, 9), MK_VLC(0x00105, 9), MK_VLC(0x00010, 9), MK_VLC(0x00010, 9), MK_VLC(0x00402, 9), MK_VLC(0x00402, 9), MK_VLC(0x0000f, 9), MK_VLC(0x0000f, 9), MK_VLC(0x0000e, 9), MK_VLC(0x0000e, 9), MK_VLC(0x0000d, 9), MK_VLC(0x0000d, 9), MK_VLC(0x10801, 8), MK_VLC(0x10801, 8), MK_VLC(0x10801, 8), MK_VLC(0x10801, 8), MK_VLC(0x10701, 8), MK_VLC(0x10701, 8), MK_VLC(0x10701, 8), MK_VLC(0x10701, 8), MK_VLC(0x10601, 8), MK_VLC(0x10601, 8), MK_VLC(0x10601, 8), MK_VLC(0x10601, 8), MK_VLC(0x10003, 8), MK_VLC(0x10003, 8), MK_VLC(0x10003, 8), MK_VLC(0x10003, 8), MK_VLC(0x00a01, 8), MK_VLC(0x00a01, 8), MK_VLC(0x00a01, 8), MK_VLC(0x00a01, 8), MK_VLC(0x00901, 8), MK_VLC(0x00901, 8), MK_VLC(0x00901, 8), MK_VLC(0x00901, 8), MK_VLC(0x00801, 8), MK_VLC(0x00801, 8), MK_VLC(0x00801, 8), MK_VLC(0x00801, 8), MK_VLC(0x10901, 8), MK ...` (scope `vdecmpeg4::M4VlcDecoder`) — Intra Table, i >= 128
- L439 _member_ `M4_VLC M4VlcDecoder::mTabDCT3D5[] = { MK_VLC(0x10007,11), MK_VLC(0x10007,11), MK_VLC(0x10006,11), MK_VLC(0x10006,11), MK_VLC(0x00016,11), MK_VLC(0x00016,11), MK_VLC(0x00015,11), MK_VLC(0x00015,11), MK_VLC(0x10202,10), MK_VLC(0x10202,10), MK_VLC(0x10202,10), MK_VLC(0x10202,10), MK_VLC(0x10103,10), MK_VLC(0x10103,10), MK_VLC(0x10103,10), MK_VLC(0x10103,10), MK_VLC(0x10005,10), MK_VLC(0x10005,10), MK_VLC(0x10005,10), MK_VLC(0x10005,10), MK_VLC(0x00d01,10), MK_VLC(0x00d01,10), MK_VLC(0x00d01,10), MK_VLC(0x00d01,10), MK_VLC(0x00503,10), MK_VLC(0x00503,10), MK_VLC(0x00503,10), MK_VLC(0x00503,10), MK_VLC(0x00802,10), MK_VLC(0x00802,10), MK_VLC(0x00802,10), MK_VLC(0x00802,10), MK_VLC(0x00403,10), MK_VLC(0x00403,10), MK_VLC(0x00403,10), MK_VLC(0x00403,10), MK_VLC(0x00304,10), MK_VLC(0x00304,10), MK_VLC(0x00304,10), MK_VLC(0x00304,10), MK_VLC(0x00204,10), MK_VLC(0x00204,10), MK_VLC(0x00204,10), MK_VLC(0x00204,10), MK_VLC(0x00107,10), MK_VLC(0x00107,10), MK_VLC(0x00107,10), MK_VLC(0x00107,10), MK_VLC(0x00014,10), MK_VLC(0x00014,10), MK_VLC(0x00014,10), MK_VLC(0x00014,10), MK_VLC(0x00013,10), MK_VLC(0x00013,10), MK_VLC(0x00013,10), MK_VLC(0x00013,10), MK_VLC(0x00017,11), MK_VLC(0x00017,11), MK_VLC(0x00018,11), MK_VLC(0x00018,11), MK_VLC(0x00108,11), MK_VLC(0x00108,11), MK_VLC(0x00902,11), MK_VLC(0x00902,11), MK_VLC(0x10302,11), MK_VLC(0x10302,11), MK_VLC(0x10402,11), MK_VLC(0x10402,11), MK_VLC(0x10f01,11), MK_VLC(0x10f01,11), MK_VLC(0x11001,11), MK_VLC(0x11001,11), MK_VLC(0x00019,12), MK ...` (scope `vdecmpeg4::M4VlcDecoder`) — Intra Table, i >= 8
- L473 _member_ `const M4_VLC M4VlcDecoder::mDCLumTab[] = { MK_VLC(0, 0), MK_VLC(4, 3), MK_VLC(3, 3), MK_VLC(0, 3), MK_VLC(2, 2), MK_VLC(2, 2), MK_VLC(1, 2), MK_VLC(1, 2), };` (scope `vdecmpeg4::M4VlcDecoder`)

### `Source/Runtime/AVEncoder/Private/Decoders/vdecmpeg4/M4VlcDecoder.h` (Private)


#### struct `vdecmpeg4::M4BlockVlcCodeTab`  
`struct M4BlockVlcCodeTab`  
_L26-31_
- desc: helper struct for passing some C++ tables to the ASM routines. Must be initialized only once.
- L28 _public member_ `M4_VLC* mVlcCodeTab[3];`
- L29 _public member_ `void* mMaxLevel;`
- L30 _public member_ `void* mMaxRun;`

#### class `vdecmpeg4::M4VlcDecoder`  
`class M4VlcDecoder`  
_L35-254_
- L39 _public function_ `M4VlcDecoder()` — Default constructor
- L43 _public prototype_ `~M4VlcDecoder() = default;` — Destructor
- L46 _public prototype_ `void init();` — Init vlc tables
- L49 _public function_ `int32 getCoeffIntraNoAsm(int32& run, int32& last, M4Bitstream& bs)`
- L118 _public function_ `int32 getCoeffInterNoAsm(int32& run, int32& last, M4Bitstream& bs)`
- L190 _private function_ `M4_VLC getIntraVlcTab(uint32 bits)` — Get vlc code for intra block
- L207 _private function_ `M4_VLC getInterVlcTab(uint32 bits)` — Get vlc code for inter block
- L224 _private prototype_ `M4VlcDecoder(const M4VlcDecoder &pObj);` — Copy-constructor not implemented
- L227 _private prototype_ `const M4VlcDecoder &operator=(const M4VlcDecoder &pObj);` — Assignment operator not implemented
- L229 _private member_ `M4BlockVlcCodeTab mIntraCodeTab;`
- L230 _private member_ `M4BlockVlcCodeTab mInterCodeTab;`
- L232 _private member_ `static uint8 mMaxLevel[4][64];`
- L233 _private member_ `static uint8 mMaxRun[4][256];`
- L235 _private member_ `static const M4_VLC mTabCbpCIntra[64];`
- L236 _private member_ `static const M4_VLC mTabCbpCInter[257];`
- L237 _private member_ `static const M4_VLC mTabCbpY[64];`
- L239 _private member_ `static M4_VLC mTabTMNMV0[];`
- L240 _private member_ `static M4_VLC mTabTMNMV1[];`
- L241 _private member_ `static M4_VLC mTabTMNMV2[];`
- L243 _private member_ `static M4_VLC mTabDCT3D0[];`
- L244 _private member_ `static M4_VLC mTabDCT3D1[];`
- L245 _private member_ `static M4_VLC mTabDCT3D2[];`
- L247 _private member_ `static M4_VLC mTabDCT3D3[];`
- L248 _private member_ `static M4_VLC mTabDCT3D4[];`
- L249 _private member_ `static M4_VLC mTabDCT3D5[];`
- L251 _private member_ `static const M4_VLC mDCLumTab[];`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace vdecmpeg4`
- L10 _macro_ `#define MK_VLC(a,b) \`
- L13 _macro_ `#define VLC_CODE(a) \`
- L16 _macro_ `#define VLC_LEN(a) \`
- L19 _macro_ `#define VLC_ERROR MK_VLC(0x1ffff, 0)`
- L20 _macro_ `#define VLC_ESCAPE 0x1BFF`
- L22 _typedef_ `typedef uint32 M4_VLC;` (scope `vdecmpeg4`) — Definition of VLC data types

### `Source/Runtime/AVEncoder/Private/Decoders/vdecmpeg4/M4XCmdSingleThread.h` (Private)


#### class `vdecmpeg4::M4XCmdSingleThread`  
`class M4XCmdSingleThread`  
_L23-81_
- L28 _public prototype_ `M4XCmdSingleThread();` — Ctor
- L30 _public prototype_ `~M4XCmdSingleThread();` — Dtor
- L33 _public prototype_ `VIDError Init(M4Decoder* pDecoder);` — Allocate resources
- L35 _public prototype_ `void Exit();` — Release resources
- L39 _public prototype_ `void FrameBegin(M4Image* pOutput, M4BitstreamHeaderInfo* pHeaderInfo, M4Image* pRefImage[2]);`
- L40 _public function_ `void FrameEnd()`
- L46 _public function_ `void XCreatePadding(VIDImage* pImage)`
- L50 _public function_ `void XCopyMB( int32 mbx, int32 mby)`
- L54 _public prototype_ `void XUpdateIntraMB(M4_MB* pMB, int32 mbx, int32 mby, M4BitstreamCacheEntry* pCacheEntry);`
- L55 _public prototype_ `void XUpdateInterMB(M4_MB* pMB, int32 mbx, int32 mby, M4BitstreamCacheEntry* pCacheEntry, MV_PREDICTION mvDir, uint32 refImageNo);`
- L56 _public prototype_ `void XInterpolateMB(M4_MB* pMb, int32 mbx, int32 mby, M4BitstreamCacheEntry* pCacheEntry, uint32 refImageForward, uint32 refImageBackward, uint16 mbLastIdx);`
- L60 _public function_ `int16* GetDctWorkArea() const`
- L65 _public function_ `const VIDImageMacroblockInfo& GetMacroblockInfo() const`
- L72 _protected member_ `int16* mpDctWorkData;`
- L73 _protected member_ `M4Image* mpOutput;`
- L74 _protected member_ `M4BitstreamHeaderInfo* mpHeaderInfo;`
- L76 _protected member_ `M4Image* mpRefImage[2];`
- L78 _protected member_ `M4Decoder* mpDecoder;`
- L80 _protected member_ `VIDImageMacroblockInfo mMacroblockInfo;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace vdecmpeg4`
- L20 _prototype_ `void M4ImageCreatePadding(void* image);` (scope `vdecmpeg4`)

### `Source/Runtime/AVEncoder/Private/Decoders/vdecmpeg4/M4idct.h` (Private)


#### Free symbols / members of external scopes

- L6 _namespace_ `namespace vdecmpeg4`
- L10 _prototype_ `void M4idct(int16* block);` (scope `vdecmpeg4`) — Inverse DCT on 8x8 block

### `Source/Runtime/AVEncoder/Private/Decoders/vdecmpeg4/vdecmpeg4.h` (Private)


#### enum `vdecmpeg4::VID_DECODER_INIT`  
`enum VID_DECODER_INIT`  
_L13-17_
- desc: Possible decoder initialization flags used in VIDDecoderSetup::flags
- L15 _public enumerator_ `VID_DECODER_VID_BUFFERS = (1<<0)` — Allocate indicated number of vid buffers - min 3
- L16 _public enumerator_ `VID_DECODER_DEFAULT = 0`

#### enum `vdecmpeg4::VIDFrameType`  
`enum VIDFrameType`  
_L20-27_
- desc: Possible return values for VIDGetFrameType() function
- L22 _public enumerator_ `VID_FT_ERROR = -1` — Cannot determine frame type from data
- L23 _public enumerator_ `VID_FT_I_FRAME = 0` — Input data stream is I frame
- L24 _public enumerator_ `VID_FT_P_FRAME` — Input data stream is P frame
- L25 _public enumerator_ `VID_FT_B_FRAME` — Input data stream is B frame
- L26 _public enumerator_ `VID_FT_S_FRAME` — Input data stream is S frame

#### enum `vdecmpeg4::VID_IMAGEINFO_FRAMETYPE`  
`enum VID_IMAGEINFO_FRAMETYPE`  
_L34-41_
- desc: Possible frame types returned via VIDImageInfo
- L36 _public enumerator_ `VID_IMAGEINFO_FRAMETYPE_UNKNOWN` — Unknown frame
- L37 _public enumerator_ `VID_IMAGEINFO_FRAMETYPE_I` — I frame
- L38 _public enumerator_ `VID_IMAGEINFO_FRAMETYPE_P` — P frame
- L39 _public enumerator_ `VID_IMAGEINFO_FRAMETYPE_B` — B frame
- L40 _public enumerator_ `VID_IMAGEINFO_FRAMETYPE_S` — S frame (gmc)

#### struct `vdecmpeg4::VIDImageMacroblockInfo`  
`struct VIDImageMacroblockInfo`  
_L44-50_
- desc: Statistical information about the possible mpeg block from which this frame is made.
- L46 _public member_ `uint16 mNumMBinter;` — Number of INTER coded macro blocks
- L47 _public member_ `uint16 mNumMBintra;` — Number of INTRA coded macro blocks
- L48 _public member_ `uint16 mNumMBinterpolated;` — Number of interpolated macro blocks
- L49 _public member_ `uint16 mNumMBnotCoded;` — Number of non-coded (direct copy) macro blocks

#### struct `vdecmpeg4::VIDImageInfo`  
`struct VIDImageInfo`  
_L53-60_
- desc: Statistical information about decoded frame. This struct is returned via a call to VIDGetFrameInfo
- L55 _public member_ `VID_IMAGEINFO_FRAMETYPE mFrameType;` — Current frame type
- L56 _public member_ `uint32 mFrameNumber;` — Current frame number
- L57 _public member_ `float mDecodeTimeMs;` — Decode time of frame in ms
- L58 _public member_ `uint32 mFrameBytes;` — Size of frame input data in bytes
- L59 _public member_ `VIDImageMacroblockInfo mMacroblockInfo;` — See VIDImageMacroblockInfo

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace vdecmpeg4`
- L78 _prototype_ `VIDError VIDCreateDecoder(const VIDDecoderSetup* setup, VIDDecoder* pNewDecoder);` (scope `vdecmpeg4`) — Create decoder Used to create and initialize the decoder instance. All memory allocations happen inside this method and the amount of required memory is determined by inspecting the values inside the ::VIDDecoderSetup. @param[in]	setup			pointer to ::VIDDecoderSetup. Can be deleted after this method returns. @param[out]	pNewDecoder		pointer to ::VIDDecoder variable which get. @return		::VIDError result
- L91 _prototype_ `void VIDDestroyDecoder(VIDDecoder decoder);` (scope `vdecmpeg4`) — Destroy decoder Used to destroy the decoder instance and free all the memory @param[in]	decoder		handle to decoder. @return		none
- L109 _prototype_ `const VIDImageInfo* VIDGetFrameInfo(const VIDImage* pImage);` (scope `vdecmpeg4`) — Extract image information from frame. Some additional paramters about the decoded frame are stored in the ::VIDImageInfo struct which can be extracted from a decoder returned ::VIDImage result by calling this function. @param[in]	pImage		pointer to decoder created image. @return		pointer to ::VIDImageInfo containing extended results.
- L125 _prototype_ `void VIDDebugVideoOutToBMP(VIDDecoder decoder, const char *pBaseName);` (scope `vdecmpeg4`) — Automatic output of decoded images to disk. If available (see note below), this function activates the automatic output of the decoded images as BMP files to disk. The supplied base name is prepended to the generated file name. @param[in]	decoder			handle to decoder. @param[in]	pBaseName		ptr to filename base to prepend to images. @return		none (even no error if write fails!)
- L140 _prototype_ `VIDError VIDStreamSet(VIDDecoder decoder, VIDStreamIO* pStream, VIDStreamEvents* pEvents);` (scope `vdecmpeg4`) — Set current stream for playback The stream is 'attached' to the decoder and processing happens in the VIDStreamDecode function. @param[in]	decoder			handle to decoder. @param[in]	pStream			ptr to stream to play. @return		::VIDError result
- L155 _prototype_ `VIDError VIDStreamDecode(VIDDecoder decoder, float time, const VIDImage** result);` (scope `vdecmpeg4`) — Perform decoding of stream This initiates the processing of all stream. TODO: Check: Callbacks? @param[in]	decoder			handle to decoder. @param[in]	time			TODO: deltaTime or @return		::VIDError result
- L168 _prototype_ `VIDError VIDStreamEventsSet(VIDDecoder decoder, VIDStreamEvents* pEvents);` (scope `vdecmpeg4`) — Set stream event interface explicitly @param[in]	decoder			handle to decoder. @param[in]	pEvents			which event sink to use @return		::VIDError result
- L181 _prototype_ `VIDError VIDStreamSeekNotify(VIDDecoder decoder);` (scope `vdecmpeg4`) — Inform decoder about seeking @param[in]	decoder			handle to decoder. @return		::VIDError result

### `Source/Runtime/AVEncoder/Private/Decoders/vdecmpeg4/vdecmpeg4_Build.h` (Private)
_(no declarations extracted)_

### `Source/Runtime/AVEncoder/Private/Decoders/vdecmpeg4/vdecmpeg4_ErrorCodes.h` (Private)


#### Free symbols / members of external scopes

- L6 _namespace_ `namespace vdecmpeg4`
- L10 _typedef_ `typedef int32 VIDError;` (scope `vdecmpeg4`) — Generic error type
- L13 _macro_ `#define _VID_MAKE_ERROR(_rc) ((VIDError)(0x80000000 | (_rc)))`
- L15 _variable_ `static constexpr VIDError VID_OK = 0;` (scope `vdecmpeg4`) — All okay
- L16 _variable_ `static constexpr VIDError VID_ERROR_GENERIC = _VID_MAKE_ERROR(0x1);` (scope `vdecmpeg4`) — Unspecified error
- L17 _variable_ `static constexpr VIDError VID_ERROR_OUT_OF_MEMORY = _VID_MAKE_ERROR(0x2);` (scope `vdecmpeg4`) — Out of memory
- L19 _variable_ `static constexpr VIDError VID_ERROR_NOT_VIDEO_STREAM = _VID_MAKE_ERROR(0x10);` (scope `vdecmpeg4`) — Not a video stream
- L20 _variable_ `static constexpr VIDError VID_ERROR_BAD_VIDEO_OBJECT = _VID_MAKE_ERROR(0x11);` (scope `vdecmpeg4`) — Unsupported video_object_type
- L22 _variable_ `static constexpr VIDError VID_ERROR_WIDTH_OR_HEIGHT_LESS_THAN_32 = _VID_MAKE_ERROR(0x100);` (scope `vdecmpeg4`) — Resolution of input movie with or height is smaller than 32
- L23 _variable_ `static constexpr VIDError VID_ERROR_INVALID_WIDTH_OR_HEIGHT = _VID_MAKE_ERROR(0x101);` (scope `vdecmpeg4`) — Resolution of input movie is invalid
- L24 _variable_ `static constexpr VIDError VID_ERROR_WIDTH_OR_HEIGHT_NOT_MULTIPLE_OF_16 = _VID_MAKE_ERROR(0x102);` (scope `vdecmpeg4`) — Resolution of input movie is not multiple of 16
- L25 _variable_ `static constexpr VIDError VID_ERROR_INTERLACED_NOT_SUPPORTED = _VID_MAKE_ERROR(0x103);` (scope `vdecmpeg4`) — Interlace is not supported
- L27 _variable_ `static constexpr VIDError VID_ERROR_SETUP_PLATFORM_DATA_INVALID = _VID_MAKE_ERROR(0x200);` (scope `vdecmpeg4`) — Some generic trouble with platform setup
- L28 _variable_ `static constexpr VIDError VID_ERROR_SETUP_NUMBER_OF_VID_BUFFERS_INVALID = _VID_MAKE_ERROR(0x201);` (scope `vdecmpeg4`) — Number of allocated buffers must be at least 2
- L30 _variable_ `static constexpr VIDError VID_ERROR_DECODE_INVALID_VOP = _VID_MAKE_ERROR(0x1000);` (scope `vdecmpeg4`) — Could not get valid frame type from bitstream during decode.
- L31 _variable_ `static constexpr VIDError VID_ERROR_DECODE_STUFFING_NOT_SUPPORTED = _VID_MAKE_ERROR(0x1001);` (scope `vdecmpeg4`) — Stuffing is not supported.
- L32 _variable_ `static constexpr VIDError VID_ERROR_DECODE_GMC_NOT_ENABLED = _VID_MAKE_ERROR(0x1010);` (scope `vdecmpeg4`) — Found GMC frame in input stream, but GMC frames are not enabled
- L33 _variable_ `static constexpr VIDError VID_ERROR_DECODE_NO_VID_BUFFER_AVAILABLE = _VID_MAKE_ERROR(0x1020);` (scope `vdecmpeg4`) — All vid buffers are busy/blocked
- L35 _variable_ `static constexpr VIDError VID_ERROR_MULTITHREADING_INIT = _VID_MAKE_ERROR(0x9000);` (scope `vdecmpeg4`) — Generic error during mulithreaded init
- L37 _variable_ `static constexpr VIDError VID_ERROR_STREAM_NOT_SET = _VID_MAKE_ERROR(0xF001);` (scope `vdecmpeg4`) — No stream set for processing
- L38 _variable_ `static constexpr VIDError VID_ERROR_STREAM_EOF = _VID_MAKE_ERROR(0xF002);` (scope `vdecmpeg4`) — Stream reported eof
- L39 _variable_ `static constexpr VIDError VID_ERROR_STREAM_ERROR = _VID_MAKE_ERROR(0xF003);` (scope `vdecmpeg4`) — Any form of stream error during read operation
- L40 _variable_ `static constexpr VIDError VID_ERROR_STREAM_UNDERFLOW = _VID_MAKE_ERROR(0xF004);` (scope `vdecmpeg4`) — Not enough data for returning a finished frame. Call decode again.
- L41 _variable_ `static constexpr VIDError VID_ERROR_STREAM_VOL_INVALID_SHAPE = _VID_MAKE_ERROR(0xF010);` (scope `vdecmpeg4`) — video_object_layer_shape is not valid
- L42 _variable_ `static constexpr VIDError VID_ERROR_STREAM_VOP_WITHOUT_VOL = _VID_MAKE_ERROR(0xF020);` (scope `vdecmpeg4`) — Found a VOP without a preceeding VOL
- L43 _variable_ `static constexpr VIDError VID_ERROR_STREAM_VOP_NOT_CODED = _VID_MAKE_ERROR(0xF021);` (scope `vdecmpeg4`) — Found a non-coded vop. This needs to be skipped
- L44 _variable_ `static constexpr VIDError VID_ERROR_STREAM_VOP_INVALID_SCALABILITY = _VID_MAKE_ERROR(0xF022);` (scope `vdecmpeg4`) — scalability == 1 is not supported
- L45 _variable_ `static constexpr VIDError VID_ERROR_STREAM_VOP_FRAME_SKIPPED = _VID_MAKE_ERROR(0xF023);` (scope `vdecmpeg4`) — Found invalid b-fame time code (perhaps seeking?);

### `Source/Runtime/AVEncoder/Private/Decoders/vdecmpeg4/vdecmpeg4_Image.h` (Private)


#### struct `vdecmpeg4::VIDYUVTexture`  
`struct VIDYUVTexture`  
_L15-21_
- desc: Texture structure which characterizes an YUV texture.
- L17 _public member_ `uint8* y;` — Pointer to beginning of texture for y samples
- L18 _public member_ `uint8* u;` — Pointer to beginning of texture for u samples
- L19 _public member_ `uint8* v;` — Pointer to beginning of texture for v samples
- L20 _public member_ `void* userData;` — Arbitrary data

#### struct `vdecmpeg4::VIDImage`  
`struct VIDImage`  
_L31-50_
- desc: Video image structure. The decoder returns a pointer to a VIDImage for each frame. Please note that the VIDImage is a subrectangle inside the VIDYUVTexture.
- L33 _public member_ `int16 width;` — Width of video image (excluding border region)
- L34 _public member_ `int16 height;` — height of video image (excluding border region)
- L36 _public member_ `int16 texWidth;` — Total width of video texture containing image (including border region)
- L37 _public member_ `int16 texHeight;` — Total height of video texture containing image (including border region)
- L39 _public member_ `uint8* y;` — Pointer to beginning of video y samples
- L40 _public member_ `uint8* u;` — Pointer to beginning of video u samples
- L41 _public member_ `uint8* v;` — Pointer to beginning of video v samples
- L43 _public member_ `void* _private;`
- L45 _public member_ `VIDYUVTexture texture;` — Our parent texture. We are a subrectangle inside this parent.
- L47 _public member_ `double time;` — absolute vop time of this frame in seconds
- L49 _public prototype_ `virtual void Release() const;` — Release image when no longer needed and referenced.

#### Free symbols / members of external scopes

- L6 _namespace_ `namespace vdecmpeg4`

### `Source/Runtime/AVEncoder/Private/Decoders/vdecmpeg4/vdecmpeg4_Platform.h` (Private)


#### struct `vdecmpeg4::VIDDecoderSetup`  
`struct VIDDecoderSetup`  
_L52-64_
- desc: Decoder setup information. This struct needs to be setup for proper decoder initialiazion. This happens often after opening the video input, because we need information about the image width and height here.
- L54 _public member_ `uint32 size;` — Total size of this structure (sizeof)
- L55 _public member_ `uint32 flags;` — Init flags. See \ref VID_DECODER_INIT
- L56 _public member_ `int16 width;` — Width of expected video image
- L57 _public member_ `int16 height;` — Height of expected video image
- L58 _public member_ `uint16 numOfVidBuffers;` — Explicetly select number of image buffers via \ref VID_DECODER_VID_BUFFERS
- L59 _public member_ `uint16 _reserved;`
- L60 _public member_ `VIDAllocator cbMemAlloc;` — Regular memory allocation callback
- L61 _public member_ `VIDDeallocator cbMemFree;` — Regular memory dealloction callback
- L62 _public member_ `VIDAllocator cbMemAllocLockedCache;` — Memory allocation callback for Locked Cache memory (can be nullptr)
- L63 _public member_ `VIDReporting cbReport;` — Reporting function callback

#### Free symbols / members of external scopes

- L6 _namespace_ `namespace vdecmpeg4`
- L20 _typedef_ `typedef void*(*VIDAllocator) (uint32 size, uint32 alignment);` (scope `vdecmpeg4`) — Memory allocation callback. This is used for all internal decoder memory allocations. Allocations are freed via VIDDeallocator. @param	size			Number of bytes to allocate @param	alignment		Alignment to use for this allocation @return					Pointer to memory
- L28 _typedef_ `typedef void (*VIDReporting) (const char* pMessage);` (scope `vdecmpeg4`) — Message reporting callback @param	pMessage		preformatted message
- L38 _typedef_ `typedef void (*VIDDeallocator) (void* block);` (scope `vdecmpeg4`) — Memory release/free callback. All allocations via VIDAllocator are freed here. @param	block			Pointer to memory block to free
- L40 _typedef_ `typedef void* VIDDecoder;` (scope `vdecmpeg4`) — Opaque type of decoder to outside world. See ::VIDCreateDecoder to create a decoder.

### `Source/Runtime/AVEncoder/Private/Decoders/vdecmpeg4/vdecmpeg4_Stream.h` (Private)


#### enum `vdecmpeg4::VIDStreamResult`  
`enum VIDStreamResult`  
_L10-15_
- desc: Possible resuls for VIDStream methods
- L12 _public enumerator_ `VID_STREAM_OK = 0`
- L13 _public enumerator_ `VID_STREAM_EOF`
- L14 _public enumerator_ `VID_STREAM_ERROR`

#### class `vdecmpeg4::VIDStreamIO`  
`class VIDStreamIO`  
_L21-50_
- desc: Interface for stream communcation between decoder and actual data provider.
- L40 _public prototype_ `virtual VIDStreamResult Read(uint8* pRequestedDataBuffer, uint32 requestedDataBytes, uint32& actualDataBytes) = 0;` — Read data from stream The decoder calls this method for reading 'requestedDataBytes' from the stream to the memory pointed via 'pRequestedDataBuffer'. The real amount of data which can be returned needs to be assigned to 'actualDataBytes' and a proper VIDStreamResult must be returned. @param		pRequestedDataBuffer 		where to put the read data @param		requestedDataBytes 			actual size request of the decoder @param		actualDataBytes 			available number of bytes in buffer after read @return		VIDStreamResult
- L48 _public prototype_ `virtual bool IsEof() = 0;` — Check if stream is at eof @return		True if stream is at eof

#### class `vdecmpeg4::VIDStreamEvents`  
`class VIDStreamEvents`  
_L57-100_
- desc: General callback for stream information
- L99 _public prototype_ `virtual void FoundVideoObjectLayer(const VOLInfo& volInfo) = 0;` — Provide information about a new VOL found in the stream @param		volInfo 				information about VOL

#### struct `vdecmpeg4::VIDStreamEvents::VOLInfo`  
`struct VOLInfo`  
_L62-91_
- desc: VideoObjectLayer
- L64 _public member_ `int16 mWidth;`
- L65 _public member_ `int16 mHeight;`
- L67 _public member_ `int16 mCodedWidth;`
- L68 _public member_ `int16 mCodedHeight;`
- L78 _public member_ `uint8 mAspectRatio;` — Four-bit integer which defines the value of pixel aspect ratio 0x0:  Forbidden 0x1:  1:1 (Square) 0x2:  12:11 (625-type for 4:3 picture) 0x3:  10:11 (525-type for 4:3 picture) 0x4:  16:11 (625-type stretched for 16:9 picture) 0x5:  40:33 (525-type stretched for 16:9 picture) 0xf:  extended PAR - see below
- L82 _public member_ `uint8 mAspectRatioPARwidth;` — Only valid if aspect_ratio_info == 0xf: This is an 8-bit unsigned integer which indicates the horizontal size of pixel aspect ratio
- L85 _public member_ `uint8 mAspectRatioPARheight;` — Only valid if aspect_ratio_info == 0xf: This is an 8-bit unsigned integer which indicates the vertical size of pixel aspect ratio
- L87 _public member_ `uint8 mProfileLevel;`
- L89 _public member_ `uint16 mFPSNumerator;`
- L90 _public member_ `uint16 mFPSDenominator;`

#### Free symbols / members of external scopes

- L6 _namespace_ `namespace vdecmpeg4`

### `Source/Runtime/AVEncoder/Private/Decoders/vdecmpeg4/vdecmpeg4_Types.h` (Private)


#### Free symbols / members of external scopes

- L8 _macro_ `#define M4CHECK check` — Map M4CHECK() to check(). This is done to easily disable all checking in a debug build at this location here if necessary.
- L9 _macro_ `#define M4CHECKF checkf`

### `Source/Runtime/AVEncoder/Private/Encoders/VideoEncoderH264_Dummy.h` (Private)


#### class `AVEncoder::FVideoEncoderH264_Dummy`  
`class FVideoEncoderH264_Dummy : public FVideoEncoder`  
_L15-26_
- inherits: `FVideoEncoder`
- L18 _public prototype_ `static void Register(FVideoEncoderFactory& InFactory);`
- L20 _public prototype_ `virtual bool Setup(TSharedRef<FVideoEncoderInput> InInput, const FInit& InInit) override;`
- L21 _public prototype_ `virtual void Shutdown() override;`
- L22 _public prototype_ `virtual void Encode(const FVideoEncoderInputFrame* InFrame, const FEncodeOptions& InOptions) override;`
- L24 _private prototype_ `FVideoEncoderH264_Dummy();`
- L25 _private prototype_ `virtual ~FVideoEncoderH264_Dummy();`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace AVEncoder`

### `Source/Runtime/AVEncoder/Private/Encoders/WmfAudioEncoder.h` (Private)


#### class `AVEncoder::FWmfAudioEncoderFactory`  
`class FWmfAudioEncoderFactory : public FAudioEncoderFactory PRAGMA_ENABLE_DEPRECATION_WARNINGS`  
_L14-26_
- inherits: `FAudioEncoderFactoryPRAGMA_ENABLE_DEPRECATION_WARNINGS`
- L18 _public prototype_ `FWmfAudioEncoderFactory();`
- L20 _public prototype_ `const TCHAR* GetName() const override;`
- L21 _public prototype_ `TArray<FString> GetSupportedCodecs() const override;`
- L23 _public prototype_ `TUniquePtr<FAudioEncoder> CreateEncoder(const FString& Codec) override;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace AVEncoder`

### `Source/Runtime/AVEncoder/Private/MicrosoftCommon.h` (Private)


#### Free symbols / members of external scopes

- L10 _namespace_ `namespace AVEncoder`
- L13 _function_ `inline const FString GetComErrorDescription(HRESULT Res)` (scope `AVEncoder`)
- L34 _macro_ `#define CHECK_HR(COM_call)\` — macro to deal with COM calls inside a function that returns `false` on error
- L45 _macro_ `#define CHECK_HR_DEFAULT(COM_call)\` — macro to deal with COM calls inside a function that returns `{}` on error
- L56 _macro_ `#define CHECK_HR_COM(COM_call)\` — macro to deal with COM calls inside COM method (that returns HRESULT)
- L67 _macro_ `#define CHECK_HR_VOID(COM_call)\` — macro to deal with COM calls inside COM method (that simply returns)
- L81 _variable_ `const GUID CLSID_AACMFTEncoder = { 0x93AF0C51, 0x2275, 0x45d2, { 0xA3, 0x5B, 0xF2, 0xBA, 0x21, 0xCA, 0xED, 0x00 } };` (scope `AVEncoder`)
- L82 _variable_ `const GUID CLSID_MP3ACMCodecWrapper ={ 0x11103421, 0x354c, 0x4cca, { 0xa7, 0xa3, 0x1a, 0xff, 0x9a, 0x5b, 0x67, 0x01 } };` (scope `AVEncoder`)
- L83 _variable_ `const GUID CLSID_CMSH264EncoderMFT = { 0x6ca50344, 0x051a, 0x4ded, { 0x97, 0x79, 0xa4, 0x33, 0x05, 0x16, 0x5e, 0x35 } };` (scope `AVEncoder`)
- L84 _variable_ `const GUID CLSID_VideoProcessorMFT = { 0x88753b26, 0x5b24, 0x49bd, { 0xb2, 0xe7, 0xc, 0x44, 0x5c, 0x78, 0xc9, 0x82 } };` (scope `AVEncoder`)
- L91 _variable_ `const GUID MF_LOW_LATENCY = { 0x9c27891a, 0xed7a, 0x40e1,{ 0x88, 0xe8, 0xb2, 0x27, 0x27, 0xa0, 0x24, 0xee } };` (scope `AVEncoder`)

### `Source/Runtime/AVEncoder/Private/VideoDecoderCommon.h` (Private)


#### Free symbols / members of external scopes

- L8 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogVideoDecoder, Log, All);`
- L8 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogVideoDecoder, Log, All);`
- L10 _namespace_ `namespace AVEncoder`

### `Source/Runtime/AVEncoder/Private/VideoDecoderUtilities.h` (Private)


#### class `AVEncoder::DecoderUtilities::FEventSignal`  
`class FEventSignal`  
_L16-101_
- L19 _public function_ `FEventSignal(): Event(FPlatformProcess::GetSynchEventFromPool(true))`
- L23 _public prototype_ `FEventSignal(const FEventSignal&) = delete;` — Not copyable!
- L24 _public prototype_ `FEventSignal& operator=(const FEventSignal&) = delete;`
- L26 _public function_ `~FEventSignal()`
- L35 _public function_ `void Wait()` — Waits for the event signal to get set. If already set, this function returns immediately.
- L43 _public function_ `void WaitAndReset()` — Waits for the event signal to get set and clears it immediately. If already set, this function returns immediately.
- L52 _public function_ `void Signal()` — Signals the event to be set. If already set, this does nothing.
- L60 _public function_ `void Reset()` — Clears the signal. Threads will now wait again until the signal is set once more.
- L68 _public function_ `bool IsSignaled() const` — Returns state of the signal.
- L78 _public function_ `bool WaitTimeout(int64 InMicroSeconds)` — Waits for the event signal to get set within the given time limit. If already set, this function returns immediately. Returns true when event was set, false when wait timed out.
- L88 _public function_ `bool WaitTimeoutAndReset(int64 InMicroSeconds)` — Waits for the event signal to get set within the given time limit and clears it immediately. If already set, this function returns immediately. Returns true when event was set, false when wait timed out.
- L100 _private member_ `mutable FEvent* Event;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace AVEncoder`
- L13 _namespace_ `namespace DecoderUtilities` (scope `AVEncoder`)

### `Source/Runtime/AVEncoder/Private/VideoEncoderInputImpl.h` (Private)


#### class `AVEncoder::FVideoEncoderInputImpl`  
`class FVideoEncoderInputImpl : public FVideoEncoderInput`  
_L21-144_
- inherits: `FVideoEncoderInput`
- L24 _public prototype_ `FVideoEncoderInputImpl() = default;`
- L25 _public prototype_ `virtual ~FVideoEncoderInputImpl();`
- L29 _public function_ `uint32 GetNumActiveFrames() const`
- L30 _public function_ `bool GetHasFreeFrames() const`
- L34 _public prototype_ `bool SetupForDummy();`
- L35 _public prototype_ `bool SetupForYUV420P(uint32 InWidth, uint32 InHeight);`
- L38 _public prototype_ `bool SetupForD3D11(void* InApplicationD3DDevice);` — set up for an encoder that encodes a D3D11 texture (nvenc)
- L41 _public prototype_ `bool SetupForD3D11Shared(void* InApplicationD3DDevice);` — set up for an encoder that encodes a D3D11 texture within a feature level 11.1 D3D11 device (amf)
- L44 _public prototype_ `bool SetupForD3D12(void* InApplicationD3DDevice);` — set up for an encoder that encodes a D3D12 texture (amf)
- L47 _public prototype_ `bool SetupForD3D12Shared(void* InApplicationD3DDevice);` — set up for an encoder that encodes a D3D12 texture in the context of a D3D11 device (i.e. nvenc)
- L50 _public prototype_ `bool SetupForCUDA(void* InApplicationContext);` — set up an encoder that encodes a CUArray in a CUDA context
- L54 _public prototype_ `bool SetupForVulkan(VkInstance InApplicationVulkanInstance, VkPhysicalDevice InApplicationVulkanPhysicalDevice, VkDevice InApplicationVulkanDevice);` — set up an encoder that encodes a VkImage in the context of a VkDevice
- L60 _public prototype_ `const TArray<FVideoEncoderInfo>& GetAvailableEncoders() override;` — get a list of supported video encoders
- L65 _public prototype_ `FVideoEncoderInputFrame* CreateBuffer(OnFrameReleasedCallback InOnFrameReleased) override;` — create a user managed buffer
- L67 _public prototype_ `void DestroyBuffer(FVideoEncoderInputFrame* Buffer) override;` — destroy user managed buffer
- L72 _public prototype_ `TSharedPtr<FVideoEncoderInputFrame> ObtainInputFrame() override;` — obtain a video frame that can be used as a buffer for input to a video encoder
- L75 _public prototype_ `void ReleaseInputFrame(FVideoEncoderInputFrame* InFrame) override;` — release (free) an input frame and make it available for future use
- L78 _public prototype_ `void Flush() override;` — destroy/release any frames that are not currently in use
- L81 _public prototype_ `bool IsUserManagedFrame(const FVideoEncoderInputFrame* InBuffer) const;` — indicates whether a given frame is a user managed frame or not
- L86 _public prototype_ `TRefCountPtr<ID3D11Device> GetD3D11EncoderDevice() const override;`
- L87 _public prototype_ `TRefCountPtr<ID3D12Device> GetD3D12EncoderDevice() const override;`
- L90 _public prototype_ `CUcontext GetCUDAEncoderContext() const override;`
- L93 _public prototype_ `void* GetVulkanEncoderDevice() const override;`
- L99 _private prototype_ `void CollectAvailableEncoders();` — collect any encoder that can handle frame format
- L101 _private member_ `TArray<FVideoEncoderInfo> AvailableEncoders;`
- L103 _private prototype_ `FVideoEncoderInputFrameImpl* CreateFrame();`
- L104 _private prototype_ `void SetupFrameYUV420P(FVideoEncoderInputFrameImpl* Frame);`
- L105 _private prototype_ `void SetupFrameD3D11(FVideoEncoderInputFrameImpl* Frame);`
- L106 _private prototype_ `void SetupFrameD3D12(FVideoEncoderInputFrameImpl* Frame);`
- L107 _private prototype_ `void SetupFrameVulkan(FVideoEncoderInputFrameImpl* Frame);`
- L108 _private prototype_ `void SetupFrameCUDA(FVideoEncoderInputFrameImpl* Frame);`
- L112 _private member_ `} FrameInfoDummy;`
- L119 _private member_ `} FrameInfoYUV420P;`
- L127 _private member_ `} FrameInfoD3D;`
- L133 _private member_ `} FrameInfoCUDA;`
- L136 _private member_ `FVulkanDataStruct FrameInfoVulkan;`
- L139 _private member_ `mutable FCriticalSection ProtectFrames;`
- L140 _private member_ `TQueue<TSharedPtr<FVideoEncoderInputFrameImpl>> AvailableFrames;`
- L141 _private member_ `TArray<TSharedPtr<FVideoEncoderInputFrameImpl>> ActiveFrames;`
- L142 _private typedef_ `using UserManagedFrame = TPair<FVideoEncoderInputFrameImpl*, OnFrameReleasedCallback>;`
- L143 _private member_ `TArray<UserManagedFrame> UserManagedFrames;`

#### struct `AVEncoder::FVideoEncoderInputImpl::FFrameInfoDummy`  
`struct FFrameInfoDummy`  
_L110-112_

#### struct `AVEncoder::FVideoEncoderInputImpl::FFrameInfoYUV420P`  
`struct FFrameInfoYUV420P`  
_L114-119_
- L116 _public member_ `uint32 StrideY = 0;`
- L117 _public member_ `uint32 StrideU = 0;`
- L118 _public member_ `uint32 StrideV = 0;`

#### struct `AVEncoder::FVideoEncoderInputImpl::FFrameInfoD3D`  
`struct FFrameInfoD3D`  
_L122-127_
- L124 _public member_ `TRefCountPtr<ID3D11Device> EncoderDeviceD3D11;`
- L125 _public member_ `TRefCountPtr<ID3D11DeviceContext> EncoderDeviceContextD3D11;`
- L126 _public member_ `TRefCountPtr<ID3D12Device> EncoderDeviceD3D12;`

#### struct `AVEncoder::FVideoEncoderInputImpl::FFrameInfoCUDA`  
`struct FFrameInfoCUDA`  
_L130-133_
- L132 _public member_ `CUcontext EncoderContextCUDA;`

#### class `AVEncoder::FVideoEncoderInputFrameImpl`  
`class FVideoEncoderInputFrameImpl : public FVideoEncoderInputFrame`  
_L146-168_
- inherits: `FVideoEncoderInputFrame`
- L149 _public prototype_ `explicit FVideoEncoderInputFrameImpl(FVideoEncoderInputImpl* InInput);`
- L150 _public prototype_ `FVideoEncoderInputFrameImpl(const FVideoEncoderInputFrameImpl& InCloneFrom) = delete;`
- L151 _public prototype_ `explicit FVideoEncoderInputFrameImpl(const FVideoEncoderInputFrameImpl& InCloneFrom, FCloneDestroyedCallback InCloneDestroyedCallback);`
- L152 _public prototype_ `~FVideoEncoderInputFrameImpl();`
- L155 _public prototype_ `const FVideoEncoderInputFrame* Clone(FCloneDestroyedCallback InCloneDestroyedCallback) const override;` — Clone frame - this will create a copy that references the original until destroyed
- L158 _public prototype_ `void Release() const override;` — Release (decrease reference count) of this input frame
- L160 _public function_ `void SetFormat(EVideoFrameFormat InFormat)`
- L161 _public function_ `void SetWidth(uint32 InWidth)`
- L162 _public function_ `void SetHeight(uint32 InHeight)`
- L165 _private member_ `FVideoEncoderInputImpl* Input;`
- L166 _private member_ `const FVideoEncoderInputFrame* ClonedReference = nullptr;`
- L167 _private member_ `const FCloneDestroyedCallback OnCloneDestroyed;`

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace AVEncoder`

### `Source/Runtime/AVEncoder/Public/AVEncoderDebug.h` (Public)


#### Free symbols / members of external scopes

- L5 _macro_ `#define DEBUG_SET_D3D11_OBJECT_NAME(D3D11Object, Name) \`
- L12 _macro_ `#define DEBUG_D3D11_REPORT_LIVE_DEVICE_OBJECT(D3D11Device) \`

### `Source/Runtime/AVEncoder/Public/AudioEncoder.h` (Public)


#### struct `AVEncoder::FAudioFrame`  
`struct UE_DEPRECATED(5.4, "AVEncoder has been deprecated. Please use the AVCodecs plugin family instead.") FAudioFrame`  
_L15-20_
- L17 _public member_ `FTimespan Timestamp;`
- L18 _public member_ `FTimespan Duration;`
- L19 _public member_ `Audio::TSampleBuffer<float> Data;`

#### class `AVEncoder::IAudioEncoderListener`  
`class UE_DEPRECATED(5.4, "AVEncoder has been deprecated. Please use the AVCodecs plugin family instead.") IAudioEncoderListener`  
_L22-28_
- L26 _public prototype_ `virtual void OnEncodedAudioFrame(const FMediaPacket& Packet) = 0;`

#### class `AVEncoder::FAudioEncoder`  
`class UE_DEPRECATED(5.4, "AVEncoder has been deprecated. Please use the AVCodecs plugin family instead.") FAudioEncoder`  
_L30-65_
- L33 _public function_ `virtual ~FAudioEncoder()`
- L34 _public prototype_ `virtual const TCHAR* GetName() const = 0;`
- L35 _public prototype_ `virtual const TCHAR* GetType() const = 0;`
- L37 _public prototype_ `virtual bool Initialize(const FAudioConfig& Config) = 0;`
- L43 _public prototype_ `virtual void Shutdown() = 0;` — Shutdown MUST be called before destruction
- L46 _public prototype_ `virtual void Encode(const FAudioFrame& Frame) = 0;`
- L47 _public prototype_ `virtual FAudioConfig GetConfig() const = 0;`
- L49 _public prototype_ `virtual void RegisterListener(IAudioEncoderListener& Listener);`
- L50 _public prototype_ `virtual void UnregisterListener(IAudioEncoderListener& Listener);`
- L55 _protected prototype_ `void OnEncodedAudioFrame(const FMediaPacket& Packet);`
- L59 _private member_ `FCriticalSection ListenersMutex;`
- L62 _private member_ `TArray<IAudioEncoderListener*> Listeners;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace AVEncoder`

### `Source/Runtime/AVEncoder/Public/AudioEncoderFactory.h` (Public)


#### class `AVEncoder::FAudioEncoderFactory`  
`class UE_DEPRECATED(5.4, "AVEncoder has been deprecated. Please use the AVCodecs plugin family instead.") FAudioEncoderFactory`  
_L14-31_
- L17 _public function_ `virtual ~FAudioEncoderFactory()`
- L18 _public prototype_ `virtual const TCHAR* GetName() const = 0;`
- L19 _public prototype_ `virtual TArray<FString> GetSupportedCodecs() const = 0;`
- L21 _public prototype_ `virtual TUniquePtr<FAudioEncoder> CreateEncoder(const FString& Codec) = 0;`
- L24 _public prototype_ `static void RegisterFactory(FAudioEncoderFactory& Factory);`
- L25 _public prototype_ `static void UnregisterFactory(FAudioEncoderFactory& Factory);`
- L26 _public prototype_ `static FAudioEncoderFactory* FindFactory(const FString& Codec);`
- L27 _public prototype_ `static const TArray<FAudioEncoderFactory*> GetAllFactories();`
- L30 _private member_ `static TArray<FAudioEncoderFactory*> Factories;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace AVEncoder`

### `Source/Runtime/AVEncoder/Public/AudioTypes.h` (Public)


#### struct `LibRtc::FAudioStreamFormat`  
`struct UE_DEPRECATED(5.4, "AVEncoder has been deprecated. Please use the AVCodecs plugin family instead.") FAudioStreamFormat`  
_L20-26_
- desc: Describes the data format of the audio stream
- L23 _public member_ `uint32_t SampleRate;` — The number of samples per seconds
- L25 _public member_ `uint32_t NumberChannels;` — The number of channels in the stream

#### struct `LibRtc::FAudioSampleBuffer`  
`struct UE_DEPRECATED(5.4, "AVEncoder has been deprecated. Please use the AVCodecs plugin family instead.") FAudioSampleBuffer`  
_L45-53_
- desc: Describes the sample buffer of the audio stream One frame - one sample * NumberChannels One second - one frame * SampleRate The number of samples per seconds - one sample byte * NumberBytesPerSample * NumberChannels * SampleRate
- L48 _public member_ `TArrayView<const FAudioChannelSample> AudioSamples;` — The sequence of audio samples
- L51 _public member_ `FAudioStreamFormat AudioStreamFormat;` — The format of audio samples

#### struct `LibRtc::FAudioCodecConfig`  
`struct UE_DEPRECATED(5.4, "AVEncoder has been deprecated. Please use the AVCodecs plugin family instead.") FAudioCodecConfig`  
_L55-59_
- L57 _public member_ `int32_t SampleRate;`
- L58 _public member_ `int32_t NumChannels;`

#### struct `LibRtc::FAudioCodec`  
`struct UE_DEPRECATED(5.4, "AVEncoder has been deprecated. Please use the AVCodecs plugin family instead.") FAudioCodec`  
_L87-94_
- L90 _public member_ `FAudioCodecConfig AudioCodecConfig;`
- L92 _public member_ `OnAudioEncodeCallback OnAudioEncodeCallback;`
- L93 _public member_ `OnAudioDecodeCallback OnAudioDecodeCallback;`

#### struct `LibRtc::FIncomingAudioChannelInfo`  
`struct UE_DEPRECATED(5.4, "AVEncoder has been deprecated. Please use the AVCodecs plugin family instead.") FIncomingAudioChannelInfo`  
_L97-100_
- desc: Information which is used to initialize the incoming audio channel

#### struct `LibRtc::FOutgoingAudioChannelInfo`  
`struct UE_DEPRECATED(5.4, "AVEncoder has been deprecated. Please use the AVCodecs plugin family instead.") FOutgoingAudioChannelInfo`  
_L103-107_
- desc: Information which is used to initialize the outgoing audio channel
- L106 _public member_ `bool bIsMuted;` — Initial muted state of the audio channel

#### enum `LibRtc::EAudioMuteReason`  
`enum class UE_DEPRECATED(5.4, "AVEncoder has been deprecated. Please use the AVCodecs plugin family instead.") EAudioMuteReason`  
_L109-115_
- L111 _public enumerator_ `Unsupported`
- L112 _public enumerator_ `Manual`
- L113 _public enumerator_ `NotListening`
- L114 _public enumerator_ `AdminDisabled`

#### struct `LibRtc::FAudioMuteInfo`  
`struct UE_DEPRECATED(5.4, "AVEncoder has been deprecated. Please use the AVCodecs plugin family instead.") FAudioMuteInfo`  
_L117-122_
- L120 _public member_ `TOptional<EAudioMuteReason> Reason;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace LibRtc`
- L17 _typedef_ `using FAudioChannelSample = int16_t;` (scope `LibRtc`) — There is the declaration of the single audio sample
- L36 _typedef_ `using FAudioByteBuffer = TArrayView<const uint8_t>;` (scope `LibRtc`) — Describes the byte buffer of the audio stream One sample - one sample byte * NumberBytesPerSample One frame - one sample * NumberChannels One second - one frame * SampleRate The number of samples per seconds - one sample byte * NumberBytesPerSample * NumberChannels * SampleRate
- L71 _typedef_ `using OnAudioEncodeCallback = TFunction<void(const FAudioSampleBuffer&, const FAudioByteBuffer& AudioBytes)>;` (scope `LibRtc`) — The callback is called to encode the sample buffer to the byte-by-byte format. The unencoded audio sample buffer is not guaranteed to be available after callback finishes. The pointer of the encoded audio byte buffer should be valid until the next encode call will happen. @param AudioUnencodedSampleBuffer - The sample buffer which is being encoded. @param [out] OutEncodedAudioByteBuffer - The client side pointer of the byte buffer with encoded information.
- L84 _typedef_ `using OnAudioDecodeCallback = TFunction<void(const FAudioByteBuffer& AudioBytes, const FAudioSampleBuffer&)>;` (scope `LibRtc`) — The callback is called to decode the byte-by-byte buffer to the sample buffer format. The undecoded audio byte buffer is not guaranteed to be available after callback finishes. The pointer of the decoded audio sample buffer should be valid until the next decode call will happen. @param AudioUndecodedByteBuffer - The byte buffer which is being decoded. @param [out] OutDecodedAudioSampleBuffer - The client side pointer of the sample buffer with decoded information.

### `Source/Runtime/AVEncoder/Public/CodecPacket.h` (Public)


#### class `AVEncoder::FCodecPacket`  
`class UE_DEPRECATED(5.4, "AVEncoder has been deprecated. Please use the AVCodecs plugin family instead.") FCodecPacket`  
_L12-37_
- L15 _public prototype_ `virtual ~FCodecPacket() = default;`
- L17 _public prototype_ `static FCodecPacket Create(const uint8* InData, uint32 InDataSize);`
- L28 _public member_ `TSharedPtr<uint8> Data;` — pointer to encoded data
- L29 _public member_ `uint32 DataSize = 0;` — number of bytes of encoded data
- L30 _public member_ `bool IsKeyFrame = false;` — whether or not packet represents a key frame
- L31 _public member_ `uint32 VideoQP = 0;`
- L32 _public member_ `uint32 Framerate;`
- L33 _public member_ `FTimings Timings;`
- L36 _private prototype_ `FCodecPacket() = default;`

#### struct `AVEncoder::FCodecPacket::FTimings`  
`struct UE_DEPRECATED(5.4, "AVEncoder has been deprecated. Please use the AVCodecs plugin family instead.") FTimings`  
_L22-26_
- desc: Encoding/Decoding latency
- L24 _public member_ `FTimespan StartTs;`
- L25 _public member_ `FTimespan FinishTs;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace AVEncoder`

### `Source/Runtime/AVEncoder/Public/Configuration.h` (Public)


#### struct `LibRtc::FConfiguration`  
`struct UE_DEPRECATED(5.4, "AVEncoder has been deprecated. Please use the AVCodecs plugin family instead.") FConfiguration`  
_L15-34_
- L27 _public function_ `static FData& Get()`

#### struct `LibRtc::FConfiguration::FData`  
`struct UE_DEPRECATED(5.4, "AVEncoder has been deprecated. Please use the AVCodecs plugin family instead.") FData`  
_L17-25_
- L19 _public member_ `static constexpr const TCHAR* kDefaultStunServerUrl = TEXT("stu`
- L21 _public member_ `FString StunServerUrl = kDefaultStunServerUrl;`
- L23 _public member_ `TOptional<FAudioCodec> CustomAudioCodec;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace LibRtc`

### `Source/Runtime/AVEncoder/Public/IMFSampleWrapper.h` (Public)


#### class `AVEncoder::FIMFSampleWrapper`  
`class UE_DEPRECATED(5.4, "AVEncoder has been deprecated. Please use the AVCodecs plugin family instead.") FIMFSampleWrapper`  
_L18-105_
- desc: Wrapper for IMFSample, to make it easier to report errors
- L22 _public function_ `FIMFSampleWrapper(EPacketType InMediaType = EPacketType::Invalid, IMFSample* InSample = nullptr) : MediaType(InMediaType) , Sample(InSample)`
- L29 _public function_ `const IMFSample* GetSample() const`
- L34 _public function_ `IMFSample* GetSample()`
- L39 _public prototype_ `bool CreateSample();`
- L41 _public prototype_ `FTimespan GetTime() const;`
- L43 _public prototype_ `void SetTime(FTimespan Time);`
- L45 _public prototype_ `FTimespan GetDuration() const;`
- L47 _public prototype_ `void SetDuration(FTimespan Duration);`
- L49 _public prototype_ `void SetIsKeyFrame();`
- L51 _public prototype_ `bool IsVideoKeyFrame() const;`
- L53 _public prototype_ `int GetBufferCount() const;`
- L66 _public function_ `template<typename T> bool IterateBuffers(T&& Func)` — Calls the specified function for each buffer the sample contains Signature is "int (int BufferIndex, TArrayView<uint8> Data) The specified function should return true if iteration should continue, or false to finish The return value is what the specified function returned: true : Iterated through all the buffers false : Early termination
- L88 _public function_ `bool IsValid() const`
- L93 _public function_ `void Reset()`
- L98 _public prototype_ `FIMFSampleWrapper Clone() const;`
- L102 _private member_ `EPacketType MediaType;`
- L104 _private member_ `TRefCountPtr<IMFSample> Sample;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace AVEncoder`

### `Source/Runtime/AVEncoder/Public/MediaPacket.h` (Public)


#### struct `AVEncoder::FVideoConfig`  
`struct UE_DEPRECATED(5.4, "AVEncoder has been deprecated. Please use the AVCodecs plugin family instead.") FVideoConfig`  
_L8-15_
- L10 _public member_ `FString Codec;`
- L11 _public member_ `uint32 Width;`
- L12 _public member_ `uint32 Height;`
- L13 _public member_ `uint32 Framerate;`
- L14 _public member_ `uint32 Bitrate;`

#### struct `AVEncoder::FAudioConfig`  
`struct UE_DEPRECATED(5.4, "AVEncoder has been deprecated. Please use the AVCodecs plugin family instead.") FAudioConfig`  
_L17-23_
- L19 _public member_ `FString Codec;`
- L20 _public member_ `uint32 Samplerate;`
- L21 _public member_ `uint32 NumChannels;`
- L22 _public member_ `uint32 Bitrate;`

#### enum `AVEncoder::EPacketType`  
`enum class UE_DEPRECATED(5.4, "AVEncoder has been deprecated. Please use the AVCodecs plugin family instead.") EPacketType`  
_L25-30_
- L27 _public enumerator_ `Audio`
- L28 _public enumerator_ `Video`
- L29 _public enumerator_ `Invalid`

#### struct `AVEncoder::FMediaPacket`  
`struct UE_DEPRECATED(5.4, "AVEncoder has been deprecated. Please use the AVCodecs plugin family instead.") FMediaPacket`  
_L32-81_
- L35 _public member_ `EPacketType Type;`
- L37 _public member_ `FTimespan Timestamp;`
- L38 _public member_ `FTimespan Duration;`
- L39 _public member_ `TArray<uint8> Data;`
- L58 _public function_ `explicit FMediaPacket(EPacketType TypeIn) PRAGMA_ENABLE_DEPRECATION_WARNINGS`
- L75 _public function_ `bool IsVideoKeyFrame() const`

#### union `AVEncoder::FMediaPacket::(anonymous)`  
``  
_L42-55_

#### struct `AVEncoder::FMediaPacket::__anonc0f5f7ab010a::(anonymous)`  
``  
_L44-50_

#### struct `AVEncoder::FMediaPacket::__anonc0f5f7ab010a::(anonymous)`  
``  
_L53-54_

#### Free symbols / members of external scopes

- L6 _namespace_ `namespace AVEncoder`
- L45 _member_ `bool bKeyFrame;` (scope `AVEncoder::FMediaPacket::__anonc0f5f7ab010a::__anonc0f5f7ab0208`)
- L46 _member_ `int32 Width;` (scope `AVEncoder::FMediaPacket::__anonc0f5f7ab010a::__anonc0f5f7ab0208`)
- L47 _member_ `int32 Height;` (scope `AVEncoder::FMediaPacket::__anonc0f5f7ab010a::__anonc0f5f7ab0208`)
- L48 _member_ `uint32 FrameAvgQP;` (scope `AVEncoder::FMediaPacket::__anonc0f5f7ab010a::__anonc0f5f7ab0208`)
- L49 _member_ `uint32 Framerate;` (scope `AVEncoder::FMediaPacket::__anonc0f5f7ab010a::__anonc0f5f7ab0208`)
- L50 _member_ `} Video;` (scope `AVEncoder::FMediaPacket::__anonc0f5f7ab010a`)
- L54 _member_ `} Audio;` (scope `AVEncoder::FMediaPacket::__anonc0f5f7ab010a`)

### `Source/Runtime/AVEncoder/Public/VideoCommon.h` (Public)


#### enum `AVEncoder::EVideoFrameFormat`  
`enum class UE_DEPRECATED(5.4, "AVEncoder has been deprecated. Please use the AVCodecs plugin family instead.") EVideoFrameFormat`  
_L50-58_
- L52 _public enumerator_ `Undefined` — (not-yet) defined format
- L53 _public enumerator_ `YUV420P` — Planar YUV420 format in CPU memory
- L54 _public enumerator_ `D3D11_R8G8B8A8_UNORM`
- L55 _public enumerator_ `D3D12_R8G8B8A8_UNORM`
- L56 _public enumerator_ `CUDA_R8G8B8A8_UNORM`
- L57 _public enumerator_ `VULKAN_R8G8B8A8_UNORM`

#### enum `AVEncoder::EH264Profile`  
`enum class UE_DEPRECATED(5.4, "AVEncoder has been deprecated. Please use the AVCodecs plugin family instead.") EH264Profile`  
_L60-68_
- L62 _public enumerator_ `UNKNOWN`
- L63 _public enumerator_ `CONSTRAINED_BASELINE`
- L64 _public enumerator_ `BASELINE`
- L65 _public enumerator_ `MAIN`
- L66 _public enumerator_ `CONSTRAINED_HIGH`
- L67 _public enumerator_ `HIGH`

#### enum `AVEncoder::ECodecType`  
`enum class UE_DEPRECATED(5.4, "AVEncoder has been deprecated. Please use the AVCodecs plugin family instead.") ECodecType`  
_L92-98_
- L94 _public enumerator_ `Undefined`
- L95 _public enumerator_ `H264`
- L96 _public enumerator_ `MPEG4`
- L97 _public enumerator_ `VP8`

#### struct `AVEncoder::FVideoEncoderInfo`  
`struct UE_DEPRECATED(5.4, "AVEncoder has been deprecated. Please use the AVCodecs plugin family instead.") FVideoEncoderInfo`  
_L107-123_
- L109 _public member_ `uint32 ID = 0;`
- L110 _public member_ `uint32 MaxWidth = 0;`
- L111 _public member_ `uint32 MaxHeight = 0;`
- L113 _public member_ `ECodecType CodecType = ECodecType::Undefined;`
- L114 _public member_ `TArray<EVideoFrameFormat> SupportedInputFormats;`
- L122 _public member_ `} H264;`

#### struct `AVEncoder::FVideoEncoderInfo::(anonymous)`  
``  
_L118-122_

#### struct `AVEncoder::FVideoDecoderInfo`  
`struct UE_DEPRECATED(5.4, "AVEncoder has been deprecated. Please use the AVCodecs plugin family instead.") FVideoDecoderInfo`  
_L126-135_
- L128 _public member_ `uint32 ID = 0;`
- L129 _public member_ `uint32 MaxWidth = 0;`
- L130 _public member_ `uint32 MaxHeight = 0;`
- L133 _public member_ `ECodecType CodecType = ECodecType::Undefined;`

#### Free symbols / members of external scopes

- L39 _macro_ `#define WMFMEDIA_SUPPORTED_PLATFORM (PLATFORM_WINDOWS && (WINVER >= 0x0600 /*Vista*/) && !UE_SERVER)`
- L46 _namespace_ `namespace AVEncoder`
- L48 _variable_ `const int64 TimeStampNone = 0x7fffffffll;` (scope `AVEncoder`)
- L71 _function_ `inline FString ToString(EVideoFrameFormat Format)` (scope `AVEncoder`)
- L101 _variable_ `const uint32 H264Profile_ConstrainedBaseline = 1 << 0;` (scope `AVEncoder`) — TODO: make enums
- L102 _variable_ `const uint32 H264Profile_Baseline = 1 << 1;` (scope `AVEncoder`)
- L103 _variable_ `const uint32 H264Profile_Main = 1 << 2;` (scope `AVEncoder`)
- L104 _variable_ `const uint32 H264Profile_ConstrainedHigh = 1 << 3;` (scope `AVEncoder`)
- L105 _variable_ `const uint32 H264Profile_High = 1 << 4;` (scope `AVEncoder`)
- L119 _member_ `uint32 SupportedProfiles = 0;` (scope `AVEncoder::FVideoEncoderInfo::__anoneb9358f30108`)
- L120 _member_ `uint32 MinLevel = 0;` (scope `AVEncoder::FVideoEncoderInfo::__anoneb9358f30108`)
- L121 _member_ `uint32 MaxLevel = 0;` (scope `AVEncoder::FVideoEncoderInfo::__anoneb9358f30108`)
- L138 _prototype_ `void DebugSetD3D11ObjectName(ID3D11DeviceChild* InD3DObject, const char* InName);` (scope `AVEncoder`)

### `Source/Runtime/AVEncoder/Public/VideoDecoder.h` (Public)


#### class `AVEncoder::FVideoDecoder`  
`class UE_DEPRECATED(5.4, "AVEncoder has been deprecated. Please use the AVCodecs plugin family instead.") FVideoDecoder`  
_L18-72_
- L21 _public typedef_ `using CreateDecoderAllocationInterfaceCallback = TFunction<void(void* , void** )>;`
- L22 _public typedef_ `using ReleaseDecoderAllocationInterfaceCallback = TFunction<void(void* , void** )>;`
- L34 _public prototype_ `virtual bool Setup(const FInit& InInit) = 0;` — --- setup
- L36 _public prototype_ `virtual void Shutdown() = 0;` — Shuts the decoder down AND destroys it. Do not store a pointer to this decoder in a smart pointer!
- L46 _public prototype_ `virtual EDecodeResult Decode(const FVideoDecoderInput* InInput) = 0;`
- L48 _public typedef_ `using OnDecodedFrameCallback = TFunction<void(const FVideoDecoderOutput* )>;`
- L51 _public function_ `virtual void SetOnDecodedFrame(OnDecodedFrameCallback InCallback)`
- L52 _public function_ `virtual void ClearOnDecodedFrame()`
- L55 _protected prototype_ `FVideoDecoder() = default;`
- L56 _protected prototype_ `virtual ~FVideoDecoder();`
- L59 _protected prototype_ `bool CreateDecoderAllocationInterface();`
- L60 _protected prototype_ `void ReleaseDecoderAllocationInterface();`
- L61 _protected prototype_ `void* GetAllocationInterfaceMethods();`
- L63 _protected prototype_ `EFrameBufferAllocReturn AllocateOutputFrameBuffer(FVideoDecoderAllocFrameBufferResult* OutBuffer, const FVideoDecoderAllocFrameBufferParams* InAllocParams);`
- L68 _protected member_ `OnDecodedFrameCallback OnDecodedFrame;`
- L69 _protected member_ `CreateDecoderAllocationInterfaceCallback CreateDecoderAllocationInterfaceFN;`
- L70 _protected member_ `ReleaseDecoderAllocationInterfaceCallback ReleaseDecoderAllocationInterfaceFN;`
- L71 _protected member_ `FPlatformDecoderAllocInterface* PlatformDecoderAllocInterface = nullptr;`

#### struct `AVEncoder::FVideoDecoder::FInit`  
`struct UE_DEPRECATED(5.4, "AVEncoder has been deprecated. Please use the AVCodecs plugin family instead.") FInit`  
_L24-31_
- L26 _public member_ `CreateDecoderAllocationInterfaceCallback CreateDecoderAllocationInterface;`
- L27 _public member_ `ReleaseDecoderAllocationInterfaceCallback ReleaseDecoderAllocationInterface;`
- L29 _public member_ `int32 Width;`
- L30 _public member_ `int32 Height;`

#### enum `AVEncoder::FVideoDecoder::EDecodeResult`  
`enum class UE_DEPRECATED(5.4, "AVEncoder has been deprecated. Please use the AVCodecs plugin family instead.") EDecodeResult`  
_L38-43_
- L40 _public enumerator_ `Success`
- L41 _public enumerator_ `Failure`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace AVEncoder`

### `Source/Runtime/AVEncoder/Public/VideoDecoderAllocationTypes.h` (Public)


#### enum `EFrameBufferType`  
`enum class UE_DEPRECATED(5.4, "AVEncoder has been deprecated. Please use the AVCodecs plugin family instead.") EFrameBufferType`  
_L12-17_
- desc: Type of video frame buffer to allocate.
- L14 _public enumerator_ `CODEC_RawBuffer = 0`
- L15 _public enumerator_ `CODEC_TextureHandle = 1`
- L16 _public enumerator_ `CODEC_TextureObject = 2`

#### struct `FVideoDecoderAllocFrameBufferParams`  
`struct UE_DEPRECATED(5.4, "AVEncoder has been deprecated. Please use the AVCodecs plugin family instead.") FVideoDecoderAllocFrameBufferParams`  
_L22-44_
- desc: Video frame buffer allocation parameters.
- L26 _public member_ `EFrameBufferType FrameBufferType;` — Type of output frame buffer to allocate
- L35 _public member_ `int32_t AllocSize;` — Number of bytes to allocate with the specified alignment. For a raw buffer the allocation size is required as it may include oversize for padding. For a texture handle or a handle transfer buffer the allocation size is only what is required to carry the texture handle, which may be as little as 8 bytes for a single pointer only.
- L36 _public member_ `int32_t AllocAlignment;`
- L37 _public member_ `int32_t AllocFlags;`
- L39 _public member_ `int32_t Width;` — Dimensions to allocate raw buffer for.
- L40 _public member_ `int32_t Height;`
- L41 _public member_ `int32_t BytesPerPixel;`
- L43 _public member_ `void** ExtraCustomParameters;` — Extra custom parameters (platform specific)

#### enum `EFrameBufferAllocReturn`  
`enum class UE_DEPRECATED(5.4, "AVEncoder has been deprecated. Please use the AVCodecs plugin family instead.") EFrameBufferAllocReturn`  
_L49-57_
- desc: Return value for the video decoder frame buffer allocation callback.
- L52 _public enumerator_ `CODEC_Success = 0` — Buffer successfully allocated.
- L54 _public enumerator_ `CODEC_TryAgainLater = 1` — No resources available right now, try again later.
- L56 _public enumerator_ `CODEC_Failure = 2` — No resources available or some other failure.

#### struct `FFrameBufferOutPlaneDesc`  
`struct UE_DEPRECATED(5.4, "AVEncoder has been deprecated. Please use the AVCodecs plugin family instead.") FFrameBufferOutPlaneDesc`  
_L72-86_
- desc: Output buffer plane description.
- L75 _public member_ `int32_t Width;` — Width of the allocated buffer plane in pixels, including necessary padding.
- L77 _public member_ `int32_t Height;` — Height of the allocated buffer plane in pixels, including necessary padding.
- L79 _public member_ `int32_t BytesPerPixel;` — Bytes per pixel.
- L81 _public member_ `int32_t ByteOffsetToFirstPixel;` — Offset in bytes from the allocated buffer start address to the first pixel of this plane.
- L83 _public member_ `int32_t ByteOffsetBetweenPixels;` — Offset in bytes between two pixels. Multiple of BytesPerPixel. Set larger for interleaved planes (eg. a UV plane).
- L85 _public member_ `int32_t ByteOffsetBetweenRows;` — Offset in bytes between the same column in the next row.

#### struct `FVideoDecoderAllocFrameBufferResult`  
`struct UE_DEPRECATED(5.4, "AVEncoder has been deprecated. Please use the AVCodecs plugin family instead.") FVideoDecoderAllocFrameBufferResult`  
_L91-112_
- desc: Result structure to be filled in by the application.
- L94 _public member_ `void* AllocatedBuffer;` — The buffer the application has allocated.
- L96 _public member_ `int32_t AllocatedSize;` — The actual buffer size the application has allocated.
- L100 _public member_ `int32_t AllocatedPlanesNum;` — Information of the allocated buffer planes, if applicable (depending on frame buffer type to allocate). Supports at most 4 planes (R,G,B,A). Usually 2 (Y, UV) or 3 (Y,U,V or R,G,B).
- L101 _public member_ `int32_t AllocatedPlaneLayout;`
- L103 _public member_ `FFrameBufferOutPlaneDesc AllocatedPlaneDesc[4];` — int32_t AllocatedPlaneLayout;	  reserved
- L107 _public member_ `FRetainFrameBuffer RetainCallback;` — Callback within the application to retain the allocated buffer.
- L109 _public member_ `FReleaseFrameBuffer ReleaseCallback;` — Callback within the application to release the allocated buffer.
- L111 _public member_ `void* CallbackValue;` — Buffer callback user value (a 'this' pointer to something within the application) for the retain and release callbacks.

#### struct `FVideoDecoderMethodsWindows`  
`struct UE_DEPRECATED(5.4, "AVEncoder has been deprecated. Please use the AVCodecs plugin family instead.") FVideoDecoderMethodsWindows`  
_L130-141_
- L133 _public member_ `uint32_t MagicCookie;` — Magic cookie to check for if this is indeed the expected structure.
- L135 _public member_ `void* This;` — Client 'this' pointer passed in the callbacks.
- L137 _public member_ `FAllocFrameBuffer AllocateFrameBuffer;` — Client method to allocate a frame buffer to receive a decoded image.
- L140 _public member_ `FGetD3DDevice GetD3DDevice;` — Client method to query the D3D device and D3D version used.

#### struct `FVideoDecoderMethods`  
`struct UE_DEPRECATED(5.4, "AVEncoder has been deprecated. Please use the AVCodecs plugin family instead.") FVideoDecoderMethods`  
_L148-163_
- L151 _public member_ `uint32_t MagicCookie;` — Magic cookie to check for if this is indeed the expected structure.
- L153 _public member_ `void* This;` — Client 'this' pointer passed in the callbacks.
- L155 _public member_ `FAllocFrameBuffer AllocateFrameBuffer;` — Client method to allocate a frame buffer to receive a decoded image.
- L158 _public member_ `FMemAlloc MemAlloc;` — Client method to allocate specific memory.
- L160 _public member_ `FMemFree MemFree;` — Client method to free specific memory.
- L162 _public member_ `FConfigQuery ConfigQuery;` — Client method to provide specific decoder configuration settings.

#### Free symbols / members of external scopes

- L62 _delegate_ `DECLARE_DELEGATE_TwoParams(FRetainFrameBuffer, void* , void* );` — Callback to retain an allocated buffer
- L62 _prototype_ `DECLARE_DELEGATE_TwoParams(FRetainFrameBuffer, void* , void* );` — Callback to retain an allocated buffer
- L67 _delegate_ `DECLARE_DELEGATE_TwoParams(FReleaseFrameBuffer, void* , void* );` — Callback to release an allocated buffer
- L67 _prototype_ `DECLARE_DELEGATE_TwoParams(FReleaseFrameBuffer, void* , void* );` — Callback to release an allocated buffer
- L120 _delegate_ `DECLARE_DELEGATE_RetVal_ThreeParams(EFrameBufferAllocReturn, FAllocFrameBuffer, void* , const FVideoDecoderAllocFrameBufferParams* , FVideoDecoderAllocFrameBufferResult* );`
- L120 _prototype_ `DECLARE_DELEGATE_RetVal_ThreeParams(EFrameBufferAllocReturn, FAllocFrameBuffer, void* , const FVideoDecoderAllocFrameBufferParams* , FVideoDecoderAllocFrameBufferResult* );` — Video frame buffer allocation callback within the application. We call this to get a new output frame buffer to decode into.
- L128 _delegate_ `DECLARE_DELEGATE_RetVal_ThreeParams(int32_t, FGetD3DDevice, void* , void** , int32_t* );`
- L128 _prototype_ `DECLARE_DELEGATE_RetVal_ThreeParams(int32_t, FGetD3DDevice, void* , void** , int32_t* );`
- L144 _delegate_ `DECLARE_DELEGATE_RetVal_FiveParams(int32_t, FMemAlloc, void* , void** , int32_t , int32_t , int32_t );`
- L144 _prototype_ `DECLARE_DELEGATE_RetVal_FiveParams(int32_t, FMemAlloc, void* , void** , int32_t , int32_t , int32_t );`
- L145 _delegate_ `DECLARE_DELEGATE_RetVal_ThreeParams(int32_t, FMemFree, void* , void** , int32_t );`
- L145 _prototype_ `DECLARE_DELEGATE_RetVal_ThreeParams(int32_t, FMemFree, void* , void** , int32_t );`
- L146 _delegate_ `DECLARE_DELEGATE_RetVal_ThreeParams(int32_t, FConfigQuery, void* , void** , void** );`
- L146 _prototype_ `DECLARE_DELEGATE_RetVal_ThreeParams(int32_t, FConfigQuery, void* , void** , void** );`

### `Source/Runtime/AVEncoder/Public/VideoDecoderFactory.h` (Public)


#### class `AVEncoder::FVideoDecoderFactory`  
`class UE_DEPRECATED(5.4, "AVEncoder has been deprecated. Please use the AVCodecs plugin family instead.") FVideoDecoderFactory`  
_L18-58_
- L21 _public prototype_ `static FVideoDecoderFactory& Get();`
- L22 _public prototype_ `static void Debug_SetDontRegisterDefaultCodecs();`
- L28 _public typedef_ `using CreateDecoderCallback = TFunction<FVideoDecoder*()>;` — the callback type used to create a registered decoder
- L31 _public prototype_ `void Register(const FVideoDecoderInfo& InInfo, const CreateDecoderCallback& InCreateDecoder);` — register a decoder so that it can be iterated and created
- L34 _public function_ `const TArray<FVideoDecoderInfo>& GetAvailable() const` — get a list of registered decoders
- L35 _public prototype_ `bool GetInfo(uint32 InID, FVideoDecoderInfo& OutInfo) const;`
- L39 _public prototype_ `FVideoDecoder* Create(uint32 InID, const FVideoDecoder::FInit& InInit);` — --- decoder creation create a decoder instance. If not nullptr it must be destroyed through invoking its Shutdown() method!
- L43 _private prototype_ `FVideoDecoderFactory();`
- L44 _private prototype_ `~FVideoDecoderFactory();`
- L45 _private prototype_ `FVideoDecoderFactory(const FVideoDecoderFactory&) = delete;`
- L46 _private prototype_ `FVideoDecoderFactory& operator=(const FVideoDecoderFactory&) = delete;`
- L48 _private prototype_ `void RegisterDefaultCodecs();`
- L50 _private member_ `static FThreadSafeCounter NextID;`
- L51 _private member_ `static bool bDebugDontRegisterDefaultCodecs;`
- L53 _private member_ `TArray<CreateDecoderCallback> CreateDecoders;`
- L56 _private member_ `TArray<FVideoDecoderInfo> AvailableDecoders;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace AVEncoder`

### `Source/Runtime/AVEncoder/Public/VideoDecoderInput.h` (Public)


#### class `AVEncoder::FVideoDecoderInput`  
`class UE_DEPRECATED(5.4, "AVEncoder has been deprecated. Please use the AVCodecs plugin family instead.") FVideoDecoderInput`  
_L17-53_
- L35 _public prototype_ `static TSharedPtr<FVideoDecoderInput> Create(const FInputData& InInputData);`
- L37 _public prototype_ `virtual int32 GetWidth() const = 0;`
- L38 _public prototype_ `virtual int32 GetHeight() const = 0;`
- L39 _public prototype_ `virtual int64 GetPTS() const = 0;`
- L40 _public prototype_ `virtual const void* GetData() const = 0;`
- L41 _public prototype_ `virtual int32 GetDataSize() const = 0;`
- L42 _public prototype_ `virtual bool IsKeyframe() const = 0;`
- L43 _public prototype_ `virtual bool IsCompleteFrame() const = 0;`
- L44 _public prototype_ `virtual bool HasMissingFrames() const = 0;`
- L45 _public prototype_ `virtual int32 GetRotation() const = 0;`
- L46 _public prototype_ `virtual int32 GetContentType() const = 0;`
- L49 _protected prototype_ `FVideoDecoderInput() = default;`
- L50 _protected prototype_ `virtual ~FVideoDecoderInput() = default;`
- L51 _protected prototype_ `FVideoDecoderInput(const FVideoDecoderInput&) = delete;`
- L52 _protected prototype_ `FVideoDecoderInput& operator=(const FVideoDecoderInput&) = delete;`

#### struct `AVEncoder::FVideoDecoderInput::FInputData`  
`struct UE_DEPRECATED(5.4, "AVEncoder has been deprecated. Please use the AVCodecs plugin family instead.") FInputData`  
_L21-33_
- L23 _public member_ `const void* EncodedData = nullptr;`
- L24 _public member_ `int64 PTS = 0;`
- L25 _public member_ `int32 EncodedDataSize = 0;`
- L26 _public member_ `int32 Width = 0;`
- L27 _public member_ `int32 Height = 0;`
- L28 _public member_ `int32 Rotation = 0;`
- L29 _public member_ `int32 ContentType = 0;`
- L30 _public member_ `bool bIsKeyframe = false;`
- L31 _public member_ `bool bIsComplete = false;`
- L32 _public member_ `bool bMissingFrames = false;`

#### class `AVEncoder::FVideoDecoderOutput`  
`class UE_DEPRECATED(5.4, "AVEncoder has been deprecated. Please use the AVCodecs plugin family instead.") FVideoDecoderOutput`  
_L57-85_
- L60 _public prototype_ `virtual int32 AddRef() = 0;`
- L61 _public prototype_ `virtual int32 Release() = 0;`
- L62 _public prototype_ `virtual int32 GetWidth() const = 0;`
- L63 _public prototype_ `virtual int32 GetHeight() const = 0;`
- L64 _public prototype_ `virtual int64 GetPTS() const = 0;`
- L67 _public prototype_ `virtual const FVideoDecoderAllocFrameBufferResult* GetAllocatedBuffer() const = 0;`
- L70 _public prototype_ `virtual int32 GetCropLeft() const = 0;`
- L71 _public prototype_ `virtual int32 GetCropRight() const = 0;`
- L72 _public prototype_ `virtual int32 GetCropTop() const = 0;`
- L73 _public prototype_ `virtual int32 GetCropBottom() const = 0;`
- L74 _public prototype_ `virtual int32 GetAspectX() const = 0;`
- L75 _public prototype_ `virtual int32 GetAspectY() const = 0;`
- L76 _public prototype_ `virtual int32 GetPitchX() const = 0;`
- L77 _public prototype_ `virtual int32 GetPitchY() const = 0;`
- L78 _public prototype_ `virtual uint32 GetColorFormat() const = 0;`
- L81 _protected prototype_ `virtual ~FVideoDecoderOutput() = default;`
- L82 _protected prototype_ `FVideoDecoderOutput() = default;`
- L83 _protected prototype_ `FVideoDecoderOutput(const FVideoDecoderOutput&) = delete;`
- L84 _protected prototype_ `FVideoDecoderOutput& operator=(const FVideoDecoderOutput&) = delete;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace AVEncoder`

### `Source/Runtime/AVEncoder/Public/VideoEncoder.h` (Public)


#### class `AVEncoder::FVideoEncoder`  
`class UE_DEPRECATED(5.4, "AVEncoder has been deprecated. Please use the AVCodecs plugin family instead.") FVideoEncoder`  
_L22-127_
- L64 _public prototype_ `virtual ~FVideoEncoder();`
- L67 _public function_ `virtual bool Setup(TSharedRef<FVideoEncoderInput> input, FLayerConfig const& config)`
- L69 _public function_ `virtual void Shutdown()`
- L71 _public prototype_ `virtual bool AddLayer(FLayerConfig const& config);`
- L72 _public function_ `uint32 GetNumLayers() const`
- L73 _public function_ `virtual uint32 GetMaxLayers() const`
- L75 _public prototype_ `FLayerConfig GetLayerConfig(uint32 layerIdx) const;`
- L76 _public prototype_ `void UpdateLayerConfig(uint32 layerIdx, FLayerConfig const& config);`
- L79 _public typedef_ `using OnFrameEncodedCallback = TFunction<void(const TSharedPtr<FVideoEncoderInputFrame> )>;`
- L80 _public typedef_ `using OnEncodedPacketCallback = TFunction<void(uint32 , const TSharedPtr<FVideoEncoderInputFrame> , const FCodecPacket& )>;`
- L89 _public function_ `void SetOnEncodedPacket(OnEncodedPacketCallback callback)`
- L90 _public function_ `void ClearOnEncodedPacket()`
- L93 _public function_ `virtual void Encode(const TSharedPtr<FVideoEncoderInputFrame> frame, FEncodeOptions const& options)`
- L97 _protected prototype_ `FVideoEncoder() = default;`
- L122 _protected function_ `virtual FLayer* CreateLayer(uint32 layerIdx, FLayerConfig const& config)`
- L123 _protected function_ `virtual void DestroyLayer(FLayer* layer)`
- L125 _protected member_ `TArray<FLayer*> Layers;`
- L126 _protected member_ `OnEncodedPacketCallback OnEncodedPacket;`

#### enum `AVEncoder::FVideoEncoder::RateControlMode`  
`enum class RateControlMode`  
_L25-25_
- L25 _public enumerator_ `enum class RateControlMode { UNKNOWN, CONSTQP, VBR, CBR }; enum class MultipassMode { UNKNOWN, DISABLED, QUARTER, FULL }; enum class H264Profile { AUTO, CONSTRAINED_BASELINE, BASELINE, MAIN, CONSTRAINED_HIGH, HIGH, HIGH444, STEREO, SVC_TEMPORAL_SCALABILITY, PROGRESSIVE_HIGH }; struct UE_DEPRECATED(5.4, "AVEncoder has been deprecated. Please use the AVCodecs plugin family instead.") FLayerConfig { uint32 Width = 0; uint32 Height = 0;`
- L25 _public enumerator_ `enum class RateControlMode { UNKNOWN, CONSTQP, VBR, CBR }; enum class MultipassMode { UNKNOWN, DISABLED, QUARTER, FULL }; enum class H264Profile { AUTO, CONSTRAINED_BASELINE, BASELINE, MAIN, CONSTRAINED_HIGH, HIGH, HIGH444, STEREO, SVC_TEMPORAL_SCALABILITY, PROGRESSIVE_HIGH }; struct UE_DEPRECATED(5.4, "AVEncoder has been deprecated. Please use the AVCodecs plugin family instead.") FLayerConfig { uint32 Width = 0; uint32 Height = 0;`
- L25 _public enumerator_ `enum class RateControlMode { UNKNOWN, CONSTQP, VBR, CBR }; enum class MultipassMode { UNKNOWN, DISABLED, QUARTER, FULL }; enum class H264Profile { AUTO, CONSTRAINED_BASELINE, BASELINE, MAIN, CONSTRAINED_HIGH, HIGH, HIGH444, STEREO, SVC_TEMPORAL_SCALABILITY, PROGRESSIVE_HIGH }; struct UE_DEPRECATED(5.4, "AVEncoder has been deprecated. Please use the AVCodecs plugin family instead.") FLayerConfig { uint32 Width = 0; uint32 Height = 0;`
- L25 _public enumerator_ `enum class RateControlMode { UNKNOWN, CONSTQP, VBR, CBR }; enum class MultipassMode { UNKNOWN, DISABLED, QUARTER, FULL }; enum class H264Profile { AUTO, CONSTRAINED_BASELINE, BASELINE, MAIN, CONSTRAINED_HIGH, HIGH, HIGH444, STEREO, SVC_TEMPORAL_SCALABILITY, PROGRESSIVE_HIGH }; struct UE_DEPRECATED(5.4, "AVEncoder has been deprecated. Please use the AVCodecs plugin family instead.") FLayerConfig { uint32 Width = 0; uint32 Height = 0;`

#### enum `AVEncoder::FVideoEncoder::MultipassMode`  
`enum class MultipassMode`  
_L26-26_
- L26 _public enumerator_ `enum class MultipassMode { UNKNOWN, DISABLED, QUARTER, FULL }; enum class H264Profile { AUTO, CONSTRAINED_BASELINE, BASELINE, MAIN, CONSTRAINED_HIGH, HIGH, HIGH444, STEREO, SVC_TEMPORAL_SCALABILITY, PROGRESSIVE_HIGH }; struct UE_DEPRECATED(5.4, "AVEncoder has been deprecated. Please use the AVCodecs plugin family instead.") FLayerConfig { uint32 Width = 0; uint32 Height = 0; uint32 MaxFramerate = 0;`
- L26 _public enumerator_ `enum class MultipassMode { UNKNOWN, DISABLED, QUARTER, FULL }; enum class H264Profile { AUTO, CONSTRAINED_BASELINE, BASELINE, MAIN, CONSTRAINED_HIGH, HIGH, HIGH444, STEREO, SVC_TEMPORAL_SCALABILITY, PROGRESSIVE_HIGH }; struct UE_DEPRECATED(5.4, "AVEncoder has been deprecated. Please use the AVCodecs plugin family instead.") FLayerConfig { uint32 Width = 0; uint32 Height = 0; uint32 MaxFramerate = 0;`
- L26 _public enumerator_ `enum class MultipassMode { UNKNOWN, DISABLED, QUARTER, FULL }; enum class H264Profile { AUTO, CONSTRAINED_BASELINE, BASELINE, MAIN, CONSTRAINED_HIGH, HIGH, HIGH444, STEREO, SVC_TEMPORAL_SCALABILITY, PROGRESSIVE_HIGH }; struct UE_DEPRECATED(5.4, "AVEncoder has been deprecated. Please use the AVCodecs plugin family instead.") FLayerConfig { uint32 Width = 0; uint32 Height = 0; uint32 MaxFramerate = 0;`
- L26 _public enumerator_ `enum class MultipassMode { UNKNOWN, DISABLED, QUARTER, FULL }; enum class H264Profile { AUTO, CONSTRAINED_BASELINE, BASELINE, MAIN, CONSTRAINED_HIGH, HIGH, HIGH444, STEREO, SVC_TEMPORAL_SCALABILITY, PROGRESSIVE_HIGH }; struct UE_DEPRECATED(5.4, "AVEncoder has been deprecated. Please use the AVCodecs plugin family instead.") FLayerConfig { uint32 Width = 0; uint32 Height = 0; uint32 MaxFramerate = 0;`

#### enum `AVEncoder::FVideoEncoder::H264Profile`  
`enum class H264Profile`  
_L27-27_
- L27 _public enumerator_ `enum class H264Profile { AUTO, CONSTRAINED_BASELINE, BASELINE, MAIN, CONSTRAINED_HIGH, HIGH, HIGH444, STEREO, SVC_TEMPORAL_SCALABILITY, PROGRESSIVE_HIGH }; struct UE_DEPRECATED(5.4, "AVEncoder has been deprecated. Please use the AVCodecs plugin family instead.") FLayerConfig { uint32 Width = 0; uint32 Height = 0; uint32 MaxFramerate = 0; int32 MaxBitrate = 0;`
- L27 _public enumerator_ `enum class H264Profile { AUTO, CONSTRAINED_BASELINE, BASELINE, MAIN, CONSTRAINED_HIGH, HIGH, HIGH444, STEREO, SVC_TEMPORAL_SCALABILITY, PROGRESSIVE_HIGH }; struct UE_DEPRECATED(5.4, "AVEncoder has been deprecated. Please use the AVCodecs plugin family instead.") FLayerConfig { uint32 Width = 0; uint32 Height = 0; uint32 MaxFramerate = 0; int32 MaxBitrate = 0;`
- L27 _public enumerator_ `enum class H264Profile { AUTO, CONSTRAINED_BASELINE, BASELINE, MAIN, CONSTRAINED_HIGH, HIGH, HIGH444, STEREO, SVC_TEMPORAL_SCALABILITY, PROGRESSIVE_HIGH }; struct UE_DEPRECATED(5.4, "AVEncoder has been deprecated. Please use the AVCodecs plugin family instead.") FLayerConfig { uint32 Width = 0; uint32 Height = 0; uint32 MaxFramerate = 0; int32 MaxBitrate = 0;`
- L27 _public enumerator_ `enum class H264Profile { AUTO, CONSTRAINED_BASELINE, BASELINE, MAIN, CONSTRAINED_HIGH, HIGH, HIGH444, STEREO, SVC_TEMPORAL_SCALABILITY, PROGRESSIVE_HIGH }; struct UE_DEPRECATED(5.4, "AVEncoder has been deprecated. Please use the AVCodecs plugin family instead.") FLayerConfig { uint32 Width = 0; uint32 Height = 0; uint32 MaxFramerate = 0; int32 MaxBitrate = 0;`
- L27 _public enumerator_ `enum class H264Profile { AUTO, CONSTRAINED_BASELINE, BASELINE, MAIN, CONSTRAINED_HIGH, HIGH, HIGH444, STEREO, SVC_TEMPORAL_SCALABILITY, PROGRESSIVE_HIGH }; struct UE_DEPRECATED(5.4, "AVEncoder has been deprecated. Please use the AVCodecs plugin family instead.") FLayerConfig { uint32 Width = 0; uint32 Height = 0; uint32 MaxFramerate = 0; int32 MaxBitrate = 0;`
- L27 _public enumerator_ `enum class H264Profile { AUTO, CONSTRAINED_BASELINE, BASELINE, MAIN, CONSTRAINED_HIGH, HIGH, HIGH444, STEREO, SVC_TEMPORAL_SCALABILITY, PROGRESSIVE_HIGH }; struct UE_DEPRECATED(5.4, "AVEncoder has been deprecated. Please use the AVCodecs plugin family instead.") FLayerConfig { uint32 Width = 0; uint32 Height = 0; uint32 MaxFramerate = 0; int32 MaxBitrate = 0;`
- L27 _public enumerator_ `enum class H264Profile { AUTO, CONSTRAINED_BASELINE, BASELINE, MAIN, CONSTRAINED_HIGH, HIGH, HIGH444, STEREO, SVC_TEMPORAL_SCALABILITY, PROGRESSIVE_HIGH }; struct UE_DEPRECATED(5.4, "AVEncoder has been deprecated. Please use the AVCodecs plugin family instead.") FLayerConfig { uint32 Width = 0; uint32 Height = 0; uint32 MaxFramerate = 0; int32 MaxBitrate = 0;`
- L27 _public enumerator_ `enum class H264Profile { AUTO, CONSTRAINED_BASELINE, BASELINE, MAIN, CONSTRAINED_HIGH, HIGH, HIGH444, STEREO, SVC_TEMPORAL_SCALABILITY, PROGRESSIVE_HIGH }; struct UE_DEPRECATED(5.4, "AVEncoder has been deprecated. Please use the AVCodecs plugin family instead.") FLayerConfig { uint32 Width = 0; uint32 Height = 0; uint32 MaxFramerate = 0; int32 MaxBitrate = 0;`
- L27 _public enumerator_ `enum class H264Profile { AUTO, CONSTRAINED_BASELINE, BASELINE, MAIN, CONSTRAINED_HIGH, HIGH, HIGH444, STEREO, SVC_TEMPORAL_SCALABILITY, PROGRESSIVE_HIGH }; struct UE_DEPRECATED(5.4, "AVEncoder has been deprecated. Please use the AVCodecs plugin family instead.") FLayerConfig { uint32 Width = 0; uint32 Height = 0; uint32 MaxFramerate = 0; int32 MaxBitrate = 0;`
- L27 _public enumerator_ `enum class H264Profile { AUTO, CONSTRAINED_BASELINE, BASELINE, MAIN, CONSTRAINED_HIGH, HIGH, HIGH444, STEREO, SVC_TEMPORAL_SCALABILITY, PROGRESSIVE_HIGH }; struct UE_DEPRECATED(5.4, "AVEncoder has been deprecated. Please use the AVCodecs plugin family instead.") FLayerConfig { uint32 Width = 0; uint32 Height = 0; uint32 MaxFramerate = 0; int32 MaxBitrate = 0;`

#### struct `AVEncoder::FVideoEncoder::FLayerConfig`  
`struct UE_DEPRECATED(5.4, "AVEncoder has been deprecated. Please use the AVCodecs plugin family instead.") FLayerConfig`  
_L29-62_
- L31 _public member_ `uint32 Width = 0;`
- L32 _public member_ `uint32 Height = 0;`
- L33 _public member_ `uint32 MaxFramerate = 0;`
- L34 _public member_ `int32 MaxBitrate = 0;`
- L35 _public member_ `int32 TargetBitrate = 0;`
- L36 _public member_ `int32 QPMax = -1;`
- L37 _public member_ `int32 QPMin = -1;`
- L38 _public member_ `RateControlMode RateControlMode = RateControlMode::CBR;`
- L39 _public member_ `MultipassMode MultipassMode = MultipassMode::FULL;`
- L40 _public member_ `bool FillData = false;`
- L41 _public member_ `H264Profile H264Profile = H264Profile::BASELINE;`
- L43 _public function_ `bool operator==(FLayerConfig const& other) const`
- L58 _public function_ `bool operator!=(FLayerConfig const& other) const`

#### struct `AVEncoder::FVideoEncoder::FEncodeOptions`  
`struct UE_DEPRECATED(5.4, "AVEncoder has been deprecated. Please use the AVCodecs plugin family instead.") FEncodeOptions`  
_L83-87_
- L85 _public member_ `bool bForceKeyFrame = false;`
- L86 _public member_ `OnFrameEncodedCallback OnFrameEncoded;`

#### class `AVEncoder::FVideoEncoder::FLayer`  
`class UE_DEPRECATED(5.4, "AVEncoder has been deprecated. Please use the AVCodecs plugin family instead.") FLayer`  
_L99-120_
- L102 _public function_ `explicit FLayer(FLayerConfig const& layerConfig) : CurrentConfig(layerConfig) , NeedsReconfigure(false)`
- L106 _public prototype_ `virtual ~FLayer() = default;`
- L108 _public function_ `FLayerConfig const& GetConfig() const`
- L109 _public function_ `void UpdateConfig(FLayerConfig const& config)`
- L117 _protected member_ `FCriticalSection ConfigMutex;`
- L118 _protected member_ `FLayerConfig CurrentConfig;`
- L119 _protected member_ `bool NeedsReconfigure;`

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace AVEncoder`

### `Source/Runtime/AVEncoder/Public/VideoEncoderCommon.h` (Public)


#### Free symbols / members of external scopes

- L11 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogVideoEncoder, Log, All);`
- L11 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogVideoEncoder, Log, All);`
- L13 _namespace_ `namespace AVEncoder`

### `Source/Runtime/AVEncoder/Public/VideoEncoderFactory.h` (Public)


#### class `AVEncoder::FVideoEncoderFactory`  
`class UE_DEPRECATED(5.4, "AVEncoder has been deprecated. Please use the AVCodecs plugin family instead.") FVideoEncoderFactory`  
_L21-67_
- L24 _public prototype_ `static FVideoEncoderFactory& Get();`
- L25 _public prototype_ `static void Shutdown();`
- L26 _public prototype_ `static void Debug_SetDontRegisterDefaultCodecs();`
- L28 _public function_ `bool IsSetup() const`
- L34 _public typedef_ `using CreateEncoderCallback = TFunction<TUniquePtr<FVideoEncoder>()>;` — the callback type used to create a registered encoder
- L37 _public prototype_ `void Register(const FVideoEncoderInfo& InInfo, const CreateEncoderCallback& InCreateEncoder);` — register an encoder so that it can be iterated and created
- L40 _public function_ `const TArray<FVideoEncoderInfo>& GetAvailable() const` — get a list of registered encoders
- L41 _public prototype_ `bool GetInfo(uint32 InID, FVideoEncoderInfo& OutInfo) const;`
- L42 _public prototype_ `bool HasEncoderForCodec(ECodecType CodecType) const;`
- L46 _public prototype_ `TUniquePtr<FVideoEncoder> Create(uint32 InID, const FVideoEncoder::FLayerConfig& config);`
- L47 _public prototype_ `TUniquePtr<FVideoEncoder> Create(uint32 InID, TSharedPtr<FVideoEncoderInput> InInput, const FVideoEncoder::FLayerConfig& config);`
- L50 _private prototype_ `FVideoEncoderFactory() = default;`
- L51 _private prototype_ `~FVideoEncoderFactory() = default;`
- L52 _private prototype_ `FVideoEncoderFactory(const FVideoEncoderFactory&) = delete;`
- L53 _private prototype_ `FVideoEncoderFactory& operator=(const FVideoEncoderFactory&) = delete;`
- L55 _private prototype_ `void RegisterDefaultCodecs();`
- L57 _private member_ `static FCriticalSection ProtectSingleton;`
- L58 _private member_ `static FVideoEncoderFactory Singleton;`
- L59 _private member_ `static FThreadSafeCounter NextID;`
- L60 _private member_ `bool bDebugDontRegisterDefaultCodecs = false;`
- L61 _private member_ `FThreadSafeBool bWasSetup;`
- L62 _private member_ `TArray<CreateEncoderCallback> CreateEncoders;`
- L65 _private member_ `TArray<FVideoEncoderInfo> AvailableEncoders;`

#### Free symbols / members of external scopes

- L17 _namespace_ `namespace AVEncoder`

### `Source/Runtime/AVEncoder/Public/VideoEncoderInput.h` (Public)


#### struct `AVEncoder::FVulkanDataStruct`  
`struct UE_DEPRECATED(5.4, "AVEncoder has been deprecated. Please use the AVCodecs plugin family instead.") FVulkanDataStruct`  
_L37-42_
- L39 _public member_ `VkInstance VulkanInstance;`
- L40 _public member_ `VkPhysicalDevice VulkanPhysicalDevice;`
- L41 _public member_ `VkDevice VulkanDevice;`

#### class `AVEncoder::FVideoEncoderInput`  
`class UE_DEPRECATED(5.4, "AVEncoder has been deprecated. Please use the AVCodecs plugin family instead.") FVideoEncoderInput`  
_L45-129_
- L49 _public prototype_ `static TSharedPtr<FVideoEncoderInput> CreateDummy(bool isResizable = false);` — --- construct video encoder input based on expected input frame format
- L50 _public prototype_ `static TSharedPtr<FVideoEncoderInput> CreateForYUV420P(uint32 InWidth, uint32 InHeight, bool isResizable = false);`
- L53 _public prototype_ `static TSharedPtr<FVideoEncoderInput> CreateForD3D11(void* InApplicationD3D11Device, bool IsResizable = false, bool IsShared = false);` — create input for an encoder that encodes a D3D11 texture
- L56 _public prototype_ `static TSharedPtr<FVideoEncoderInput> CreateForD3D12(void* InApplicationD3D12Device, bool IsResizable = false, bool IsShared = false);` — create input for an encoder that encodes a D3D12 texture
- L59 _public prototype_ `static TSharedPtr<FVideoEncoderInput> CreateForCUDA(void* InApplicationCudaContext, bool IsResizable = false);` — create input for an encoder that encodes a CUarray
- L62 _public prototype_ `static TSharedPtr<FVideoEncoderInput> CreateForVulkan(void* InApplicationVulkanData, bool IsResizable = false);` — create input for an encoder that encodes a VkImage
- L65 _public prototype_ `virtual void SetMaxNumBuffers(uint32 InMaxNumBuffers);` — --- properties
- L68 _public function_ `EVideoFrameFormat GetFrameFormat() const`
- L75 _public prototype_ `virtual const TArray<FVideoEncoderInfo>& GetAvailableEncoders() = 0;` — get a list of supported video encoders
- L83 _public typedef_ `using OnFrameReleasedCallback = TFunction<void(const FVideoEncoderInputFrame* )>;` — new packet callback prototype void(uint32 LayerIndex, const FCodecPacket& Packet)
- L86 _public prototype_ `virtual FVideoEncoderInputFrame* CreateBuffer(OnFrameReleasedCallback InOnFrameReleased) = 0;` — create a user managed buffer
- L89 _public prototype_ `virtual void DestroyBuffer(FVideoEncoderInputFrame* Buffer) = 0;` — destroy user managed buffer
- L94 _public prototype_ `virtual TSharedPtr<FVideoEncoderInputFrame> ObtainInputFrame() = 0;` — obtain a video frame that can be used as a buffer for input to a video encoder
- L97 _public prototype_ `virtual void ReleaseInputFrame(FVideoEncoderInputFrame* InFrame) = 0;` — release (free) an input frame and make it available for future use
- L100 _public prototype_ `virtual void Flush() = 0;` — destroy/release any frames that are not currently in use
- L103 _public prototype_ `virtual TRefCountPtr<ID3D11Device> GetD3D11EncoderDevice() const = 0;`
- L104 _public prototype_ `virtual TRefCountPtr<ID3D12Device> GetD3D12EncoderDevice() const = 0;`
- L107 _public prototype_ `virtual CUcontext GetCUDAEncoderContext() const = 0;`
- L110 _public prototype_ `virtual void* GetVulkanEncoderDevice() const = 0;`
- L114 _protected prototype_ `FVideoEncoderInput() = default;`
- L115 _protected prototype_ `virtual ~FVideoEncoderInput() = default;`
- L116 _protected prototype_ `FVideoEncoderInput(const FVideoEncoderInput&) = delete;`
- L117 _protected prototype_ `FVideoEncoderInput& operator=(const FVideoEncoderInput&) = delete;`
- L120 _protected member_ `EVideoFrameFormat FrameFormat = EVideoFrameFormat::Undefined;`
- L123 _protected member_ `uint32 MaxNumBuffers = 3;`
- L124 _protected member_ `uint32 NumBuffers = 0;`
- L126 _protected member_ `bool bIsResizable = false;`
- L128 _protected member_ `uint32 NextFrameID = 0;`

#### class `AVEncoder::FVideoEncoderInputFrame`  
`class UE_DEPRECATED(5.4, "AVEncoder has been deprecated. Please use the AVCodecs plugin family instead.") FVideoEncoderInputFrame`  
_L133-311_
- desc: TODO this should go elsewhere and be made cross platform
- L137 _public function_ `const FVideoEncoderInputFrame* Obtain() const` — Obtain (increase reference count) of this input frame
- L139 _public prototype_ `virtual void Release() const = 0;` — Release (decrease reference count) of this input frame
- L142 _public typedef_ `using FCloneDestroyedCallback = TFunction<void(const FVideoEncoderInputFrame* )>;` — the callback type used to create a registered encoder
- L145 _public prototype_ `virtual const FVideoEncoderInputFrame* Clone(FCloneDestroyedCallback InCloneDestroyedCallback) const = 0;` — Clone frame - this will create a copy that references the original until destroyed
- L147 _public function_ `void SetFrameID(uint32 id)`
- L148 _public function_ `uint32 GetFrameID() const`
- L150 _public function_ `void SetTimestampUs(int64 timestampUs)`
- L151 _public function_ `int64 GetTimestampUs() const`
- L153 _public function_ `void SetTimestampRTP(int64 timestampRTP)`
- L154 _public function_ `int64 GetTimestampRTP() const`
- L158 _public function_ `EVideoFrameFormat GetFormat() const` — current format of frame
- L161 _public function_ `void SetWidth(uint32 InWidth)` — width of frame buffer
- L162 _public function_ `uint32 GetWidth() const`
- L164 _public function_ `void SetHeight(uint32 InHeight)` — height of frame buffer
- L165 _public function_ `uint32 GetHeight() const`
- L167 _public member_ `TFunction<void()> OnTextureEncode;`
- L179 _public prototype_ `void AllocateYUV420P();`
- L180 _public function_ `const FYUV420P& GetYUV420P() const`
- L185 _public function_ `FYUV420P& GetYUV420P()`
- L187 _public prototype_ `void SetYUV420P(const uint8* InDataY, const uint8* InDataU, const uint8* InDataV, uint32 InStrideY, uint32 InStrideU, uint32 InStrideV);`
- L200 _public function_ `const FD3D11& GetD3D11() const`
- L201 _public function_ `FD3D11& GetD3D11()`
- L204 _public typedef_ `using FReleaseD3D11TextureCallback = TFunction<void(ID3D11Texture2D*)>;` — the callback type used to create a registered encoder
- L206 _public prototype_ `void SetTexture(ID3D11Texture2D* InTexture, FReleaseD3D11TextureCallback InOnReleaseD3D11Texture);`
- L217 _public function_ `const FD3D12& GetD3D12() const`
- L218 _public function_ `FD3D12& GetD3D12()`
- L221 _public typedef_ `using FReleaseD3D12TextureCallback = TFunction<void(ID3D12Resource*)>;` — the callback type used to create a registered encoder
- L223 _public prototype_ `void SetTexture(ID3D12Resource* InTexture, FReleaseD3D12TextureCallback InOnReleaseD3D11Texture);`
- L247 _public function_ `const FCUDA& GetCUDA() const`
- L248 _public function_ `FCUDA& GetCUDA()`
- L251 _public typedef_ `using FReleaseCUDATextureCallback = TFunction<void(CUarray)>;` — the callback type used to create a registered encoder
- L253 _public prototype_ `void SetTexture(CUarray InTexture, EUnderlyingRHI UnderlyingRHI, void* SharedHandle, FReleaseCUDATextureCallback InOnReleaseTexture);`
- L266 _public function_ `const FVulkan& GetVulkan() const`
- L267 _public function_ `FVulkan& GetVulkan()`
- L270 _public typedef_ `using FReleaseVulkanTextureCallback = TFunction<void(VkImage)>;` — the callback type used to create a registered encoder
- L271 _public typedef_ `using FReleaseVulkanSurfaceCallback = TFunction<void(void*)>;`
- L272 _public member_ `mutable FReleaseVulkanSurfaceCallback OnReleaseVulkanSurface;`
- L274 _public prototype_ `void SetTexture(VkImage InTexture, FReleaseVulkanTextureCallback InOnReleaseTexture);`
- L275 _public prototype_ `void SetTexture(VkImage InTexture, VkDeviceMemory InTextureDeviceMemory, uint64 InTextureSize, FReleaseVulkanTextureCallback InOnReleaseTexture);`
- L278 _public prototype_ `virtual ~FVideoEncoderInputFrame();`
- L280 _protected prototype_ `FVideoEncoderInputFrame();`
- L281 _protected prototype_ `explicit FVideoEncoderInputFrame(const FVideoEncoderInputFrame& CloneFrom);`
- L284 _protected member_ `uint32 FrameID;`
- L285 _protected member_ `int64 TimestampUs;`
- L286 _protected member_ `int64 TimestampRTP;`
- L287 _protected member_ `mutable FThreadSafeCounter NumReferences;`
- L288 _protected member_ `uint32 Width;`
- L289 _protected member_ `uint32 Height;`
- L290 _protected member_ `FYUV420P YUV420P;`
- L291 _protected member_ `bool bFreeYUV420PData;`
- L294 _protected member_ `EVideoFrameFormat Format;`
- L298 _protected member_ `FD3D11 D3D11;`
- L299 _protected member_ `FReleaseD3D11TextureCallback OnReleaseD3D11Texture;`
- L300 _protected member_ `FD3D12 D3D12;`
- L301 _protected member_ `FReleaseD3D12TextureCallback OnReleaseD3D12Texture;`
- L304 _protected member_ `FCUDA CUDA;`
- L305 _protected member_ `FReleaseCUDATextureCallback OnReleaseCUDATexture;`
- L308 _protected member_ `FVulkan Vulkan;`
- L309 _protected member_ `FReleaseVulkanTextureCallback OnReleaseVulkanTexture;`

#### struct `AVEncoder::FVideoEncoderInputFrame::FYUV420P`  
`struct UE_DEPRECATED(5.4, "AVEncoder has been deprecated. Please use the AVCodecs plugin family instead.") FYUV420P`  
_L171-177_
- L173 _public member_ `const uint8* Data[3] = { nullptr, nullptr, nullptr };`
- L174 _public member_ `uint32 StrideY = 0;`
- L175 _public member_ `uint32 StrideU = 0;`
- L176 _public member_ `uint32 StrideV = 0;`

#### struct `AVEncoder::FVideoEncoderInputFrame::FD3D11`  
`struct UE_DEPRECATED(5.4, "AVEncoder has been deprecated. Please use the AVCodecs plugin family instead.") FD3D11`  
_L192-198_
- L194 _public member_ `ID3D11Texture2D* Texture = nullptr;`
- L195 _public member_ `ID3D11Device* EncoderDevice = nullptr;`
- L196 _public member_ `ID3D11Texture2D* EncoderTexture = nullptr;`
- L197 _public member_ `void* SharedHandle = nullptr;`

#### struct `AVEncoder::FVideoEncoderInputFrame::FD3D12`  
`struct UE_DEPRECATED(5.4, "AVEncoder has been deprecated. Please use the AVCodecs plugin family instead.") FD3D12`  
_L210-215_
- L212 _public member_ `ID3D12Resource* Texture = nullptr;`
- L213 _public member_ `ID3D12Device* EncoderDevice = nullptr;`
- L214 _public member_ `ID3D12Resource* EncoderTexture = nullptr;`

#### enum `AVEncoder::FVideoEncoderInputFrame::EUnderlyingRHI`  
`enum class UE_DEPRECATED(5.4, "AVEncoder has been deprecated. Please use the AVCodecs plugin family instead.") EUnderlyingRHI`  
_L227-233_
- L229 _public enumerator_ `Undefined`
- L230 _public enumerator_ `D3D11`
- L231 _public enumerator_ `D3D12`
- L232 _public enumerator_ `Vulkan`

#### struct `AVEncoder::FVideoEncoderInputFrame::FCUDA`  
`struct UE_DEPRECATED(5.4, "AVEncoder has been deprecated. Please use the AVCodecs plugin family instead.") FCUDA`  
_L236-245_
- desc: --- CUDA
- L238 _public member_ `CUarray EncoderTexture = nullptr;`
- L239 _public member_ `CUcontext EncoderDevice = nullptr;`
- L240 _public member_ `void* SharedHandle = nullptr;`
- L243 _public member_ `EUnderlyingRHI UnderlyingRHI = EUnderlyingRHI::Undefined;`

#### struct `AVEncoder::FVideoEncoderInputFrame::FVulkan`  
`struct UE_DEPRECATED(5.4, "AVEncoder has been deprecated. Please use the AVCodecs plugin family instead.") FVulkan`  
_L257-264_
- desc: --- Vulkan
- L259 _public member_ `VkImage EncoderTexture = VK_NULL_HANDLE;`
- L260 _public member_ `VkDeviceMemory EncoderDeviceMemory;`
- L261 _public member_ `uint64 EncoderMemorySize = 0;`
- L262 _public member_ `VkDevice EncoderDevice;`
- L263 _public member_ `mutable void* EncoderSurface = nullptr;`

#### Free symbols / members of external scopes

- L28 _namespace_ `namespace amf`
- L32 _namespace_ `namespace AVEncoder`
