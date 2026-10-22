# Plugins / PixelCapture

- module root: `Plugins/Media/PixelCapture/Source/PixelCapture`
- headers: 30; symbols: 460
- symbol kinds: class=28, delegate=5, function=80, macro=17, member=124, namespace=5, prototype=189, struct=3, typedef=2, variable=7
- PrivateDependencyModuleNames: Core, CoreUObject, Engine, PixelCaptureShaders, RenderCore, Renderer, WebRTC
- PublicDependencyModuleNames: MediaIOCore, RHI

### `Plugins/Media/PixelCapture/Source/PixelCapture/Internal/PixelCaptureCapturerMediaCapture.h` (Internal)


#### class `UPixelCaptureMediaOuput`  
`class UPixelCaptureMediaOuput : public UMediaOutput`  
_L16-28_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UMediaOutput`
- L21 _public function_ `void SetRequestedSize(FIntPoint InRequestedSize)`
- L22 _public function_ `virtual FIntPoint GetRequestedSize() const override`
- L23 _public function_ `virtual EPixelFormat GetRequestedPixelFormat() const override`
- L24 _public function_ `virtual EMediaCaptureConversionOperation GetConversionOperation(EMediaCaptureSourceType InSourceType) const override`
- L27 _private member_ `FIntPoint RequestedSize;`

#### class `UPixelCaptureMediaCapture`  
`class UPixelCaptureMediaCapture : public UMediaCapture`  
_L31-128_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UMediaCapture`
- L36 _public function_ `void AddOutputFrame(uint64 InFrameNumberRenderThread, TSharedPtr<IPixelCaptureOutputFrame> InOutputFrame)`
- L41 _public function_ `void RemoveOutputFrame(uint64 InFrameNumberRenderThread)`
- L46 _public function_ `void SetFormat(int32 InFormat)`
- L51 _public function_ `void SetIsSRGB(bool bInIsSRGB)`
- L56 _public prototype_ `DECLARE_EVENT_OneParam(UPixelCaptureMediaCapture, FOnCaptureComplete, TSharedPtr<IPixelCaptureOutputFrame>);`
- L57 _public member_ `FOnCaptureComplete OnCaptureComplete;`
- L60 _protected function_ `virtual bool InitializeCapture() override`
- L66 _protected prototype_ `virtual void OnRHIResourceCaptured_AnyThread( const FCaptureBaseData& BaseData, TSharedPtr<FMediaCaptureUserData, ESPMode::ThreadSafe> UserData, FTextureRHIRef Texture) override;`
- L71 _protected prototype_ `virtual void OnRHIResourceCaptured_RenderingThread( FRHICommandListImmediate& RHICmdList, const FCaptureBaseData& BaseData, TSharedPtr<FMediaCaptureUserData, ESPMode::ThreadSafe> UserData, FTextureRHIRef Texture) override;`
- L77 _protected prototype_ `virtual void OnFrameCaptured_AnyThread( const FCaptureBaseData& BaseData, TSharedPtr<FMediaCaptureUserData, ESPMode::ThreadSafe> UserData, const FMediaCaptureResourceData& ResourceData) override;`
- L82 _protected prototype_ `virtual void OnCustomCapture_RenderingThread( FRDGBuilder& GraphBuilder, const FCaptureBaseData& InBaseData, TSharedPtr<FMediaCaptureUserData, ESPMode::ThreadSafe> InUserData, FRDGTextureRef InSourceTexture, FRDGTextureRef OutputTexture, const FRHICopyTextureInfo& CopyInfo, FVector2D CropU, FVector2D CropV) override;`
- L92 _protected prototype_ `virtual void OnFrameCaptured_RenderingThread( const FCaptureBaseData& InBaseData, TSharedPtr<FMediaCaptureUserData, ESPMode::ThreadSafe> InUserData, void* InBuffer, int32 Width, int32 Height, int32 BytesPerRow) override;`
- L100 _protected function_ `virtual bool ShouldCaptureRHIResource() const override`
- L105 _protected function_ `virtual bool SupportsAnyThreadCapture() const`
- L117 _protected prototype_ `virtual ETextureCreateFlags GetOutputTextureFlags() const override;`
- L118 _protected prototype_ `virtual void WaitForGPU(FRHITexture* InRHITexture) override;`
- L120 _private member_ `int32 Format = PixelCaptureBufferFormat::FORMAT_UNKNOWN;`
- L122 _private member_ `bool bIsSRGB = false;`
- L124 _private member_ `TStripedMap<32, uintptr_t, FGPUFenceRHIRef> Fences;`
- L127 _private member_ `TStripedMap<32, uint64, TSharedPtr<IPixelCaptureOutputFrame>> OutputFrames;` — SourceFrameNumberRenderThread, OutputFrame

#### class `FPixelCaptureCapturerMediaCapture`  
`class FPixelCaptureCapturerMediaCapture : public FPixelCaptureCapturer, public TSharedFromThis<FPixelCaptureCapturerMediaCapture>`  
_L135-163_
- inherits: `FPixelCaptureCapturer,TSharedFromThis<FPixelCaptureCapturerMediaCapture>`
- desc: A MediaIO based capturer that will copy and convert RHI texture frames. Input: FPixelCaptureInputFrameRHI Output: FPixelCaptureOutputFrameRHI/FPixelCaptureOutputFrameI420
- L142 _public prototype_ `static TSharedPtr<FPixelCaptureCapturerMediaCapture> Create(FPixelCaptureCapturerConfig Config, int32 InFormat);` — Creates a new Capturer capturing the input frame at the given resolution. @param InOutputResolution The resolution of the resulting output capture.
- L146 _protected prototype_ `virtual FString GetCapturerName() const override;`
- L147 _protected prototype_ `virtual IPixelCaptureOutputFrame* CreateOutputBuffer(int32 InputWidth, int32 InputHeight) override;`
- L148 _protected prototype_ `virtual void BeginProcess(const IPixelCaptureInputFrame& InputFrame, TSharedPtr<IPixelCaptureOutputFrame> OutputBuffer) override;`
- L151 _private member_ `uint64 LastFrameCounterRenderThread = 0;`
- L152 _private member_ `int32 Format = PixelCaptureBufferFormat::FORMAT_UNKNOWN;`
- L153 _private member_ `bool bMediaCaptureInitialized = false;`
- L155 _private prototype_ `FPixelCaptureCapturerMediaCapture(FPixelCaptureCapturerConfig& Config, int32 InFormat);`
- L156 _private prototype_ `void InitializeMediaCapture();`
- L158 _private prototype_ `void InvalidateOutputBuffer(TSharedPtr<IPixelCaptureOutputFrame> OutputBuffer);`
- L160 _private member_ `TObjectPtr<UPixelCaptureMediaCapture> MediaCapture = nullptr;`
- L162 _private member_ `TObjectPtr<UPixelCaptureMediaOuput> MediaOutput = nullptr;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API PIXELCAPTURE_API`
- L56 _delegate_ `DECLARE_EVENT_OneParam(UPixelCaptureMediaCapture, FOnCaptureComplete, TSharedPtr<IPixelCaptureOutputFrame>);`

### `Plugins/Media/PixelCapture/Source/PixelCapture/Private/OutputFrameBuffer.h` (Private)


#### class `UE::PixelCapture::FOutputFrameBuffer`  
`class FOutputFrameBuffer`  
_L18-61_
- desc: A Single Producer Multiple Consumer ring buffer. Used by the capture process where there is a single source of captured frames that are then consumed by multiple users. We use the ref counting on TSharedPtr to check if the buffer is being used by anyone and if not we use it as a produce buffer. Once the produce is done we mark that buffer as the next consume buffer so that GetConsumeBuffer will always consume the most recently produced buffer.
- L21 _public typedef_ `using FFrameFactory = TFunction<TSharedPtr<IPixelCaptureOutputFrame>()>;`
- L23 _public prototype_ `FOutputFrameBuffer();`
- L32 _public prototype_ `void Reset(int32 InitialSize, int32 InMaxSize, const FFrameFactory& InFrameFactory);` — Resets the ring buffer to initial state. Must be called at least once before use. @param InitialSize The starting number of available buffers. @param InMaxSize The maximum number of buffers to grow to. @param InFrameFactory A function object that is used to create new buffers when growing.
- L39 _public prototype_ `TSharedPtr<IPixelCaptureOutputFrame> LockProduceBuffer();` — Gets the next available produce buffer. Might cause the buffer to grow by one up to MaxSize. @return A buffer ready to write to or null in the case of a full ring.
- L45 _public prototype_ `bool ReleaseProduceBuffer(TSharedPtr<IPixelCaptureOutputFrame> OutputBuffer);` — Indicates that the previously acquired produce buffer has been filled and ready to consume. Updates the consume position to this buffer.
- L51 _public prototype_ `TSharedPtr<IPixelCaptureOutputFrame> GetConsumeBuffer();` — Gets the newest buffer ready to consume. @return Will always return a buffer ready to be consumed.
- L54 _private member_ `FFrameFactory FrameFactory;`
- L55 _private member_ `TArray<TSharedPtr<IPixelCaptureOutputFrame>> BufferRing;`
- L56 _private member_ `TAtomic<int32> ProduceIndex;`
- L57 _private member_ `TAtomic<int32> ConsumeIndex;`
- L58 _private member_ `int32 MaxSize;`
- L60 _private prototype_ `void Grow(int32 NewSize);`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace PixelCapture` (scope `UE`)

### `Plugins/Media/PixelCapture/Source/PixelCapture/Private/PixelCapturePrivate.h` (Private)


#### Free symbols / members of external scopes

- L9 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogPixelCapture, Log, All);`
- L9 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogPixelCapture, Log, All);`

### `Plugins/Media/PixelCapture/Source/PixelCapture/Private/PixelCaptureUtils.h` (Private)


#### Free symbols / members of external scopes

- L17 _function_ `inline void CopyTexture(FRHICommandList& RHICmdList, FTextureRHIRef SourceTexture, FTextureRHIRef DestTexture, FRHIGPUFence* Fence)` — Copy from one texture to another. Assumes SourceTexture is in ERHIAccess::CopySrc and DestTexture is in ERHIAccess::CopyDest Fence can be nullptr if no fence is to be used.
- L83 _function_ `inline void CopyTextureRDG(FRHICommandListImmediate& RHICmdList, FTextureRHIRef SourceTexture, FTextureRHIRef DestTexture)`

### `Plugins/Media/PixelCapture/Source/PixelCapture/Public/IPixelCaptureBuffer.h` (Public)


#### class `IPixelCaptureBuffer`  
`class IPixelCaptureBuffer`  
_L11-43_
- desc: Buffer Template for defining frame data.
- L17 _public prototype_ `virtual int32 GetWidth() const = 0;` — Get the width of the frame
- L22 _public prototype_ `virtual int32 GetHeight() const = 0;` — Get the height of the frame
- L27 _public prototype_ `virtual int64 GetSize() const = 0;` — Gets the total size of this buffer.
- L32 _public prototype_ `virtual int32 GetFormat() const = 0;` — Gets the Format of the buffer can be used to cast to the Specific type.
- L37 _public prototype_ `const virtual uint8_t* GetData() const = 0;` — Gets a const pointer to the beginning of entire buffer for reading.
- L42 _public prototype_ `virtual uint8_t* GetMutableData() = 0;` — Gets a pointer to the beginning of the entire buffer for editing.

### `Plugins/Media/PixelCapture/Source/PixelCapture/Public/IPixelCaptureCapturerSource.h` (Public)


#### class `IPixelCaptureCapturerSource`  
`class IPixelCaptureCapturerSource`  
_L11-34_
- desc: The interface that is queried when the Layered or Multi capturers wish to create specific Capturers for a given format.
- L22 _public prototype_ `virtual TSharedPtr<FPixelCaptureCapturer> CreateCapturer(int32 FinalFormat, FIntPoint OutputResolution) = 0;` — Implement this to create an capture process that captures to the FinalFormat at the given resolution. The source format should be known by whatever is fed into the capture system. @param FinalFormat The format the capture process should capture. @param Resolution The frame resolution the capture process should output. @return The FPixelCaptureCapturer that will do the work.
- L33 _public function_ `virtual TSharedPtr<FPixelCaptureCapturer> CreateCapturer(int32 FinalFormat, float FinalScale) final` — `UE_DEPRECATED(5.7, "CreateCapturer using a scale has been deprecated. Please implement CreateCapturer using an FIntPoint output resolution.")` — Implement this to create an capture process that captures to the FinalFormat at the given scale. The source format should be known by whatever is fed into the capture system. @param FinalFormat The format the capture process should capture. @param FinalScale The frame scale the capture process should scale to. @return The FPixelCaptureCapturer that will do the work.

### `Plugins/Media/PixelCapture/Source/PixelCapture/Public/IPixelCaptureInputFrame.h` (Public)


#### class `IPixelCaptureInputFrame`  
`class IPixelCaptureInputFrame`  
_L13-52_
- desc: The base interface that is fed into the capture system. This wrapper is fed into the FPixelCaptureCapturer objects for each format/resolution. The capturer should then cast to the known type fed into the system to unwrap the data.
- L16 _public function_ `IPixelCaptureInputFrame()`
- L21 _public function_ `IPixelCaptureInputFrame(TSharedPtr<FPixelCaptureUserData> UserData)`
- L27 _public prototype_ `virtual ~IPixelCaptureInputFrame() = default;`
- L34 _public prototype_ `virtual int32 GetType() const = 0;` — Should return a unique type id from either EPixelCaptureBufferFormat or an extended user implemented enum. Value crashes could result in incorrect/unsafe casting. @return A unique id value for the implementation of this interface.
- L40 _public prototype_ `virtual int32 GetWidth() const = 0;` — Gets the width of the input frame. @return The pixel width of the input frame.
- L46 _public prototype_ `virtual int32 GetHeight() const = 0;` — Gets the height of the input frame. @return The pixel height of the input frame.
- L51 _public member_ `FPixelCaptureFrameMetadata Metadata;` — Internal structure that contains various bits of information about the capture process

### `Plugins/Media/PixelCapture/Source/PixelCapture/Public/IPixelCaptureOutputFrame.h` (Public)


#### class `IPixelCaptureOutputFrame`  
`class IPixelCaptureOutputFrame`  
_L12-24_
- desc: Wraps the output of the capture process for a single layer. Extend this for your own result types. You must implement GetWidth and GetHeight to return the width and height of the frame. Add your own method to extract the captured data.
- L15 _public prototype_ `virtual ~IPixelCaptureOutputFrame() = default;`
- L17 _public prototype_ `virtual int32 GetWidth() const = 0;`
- L18 _public prototype_ `virtual int32 GetHeight() const = 0;`
- L23 _public member_ `FPixelCaptureFrameMetadata Metadata;` — Internal structure that contains various bits of information about the capture and encode process

### `Plugins/Media/PixelCapture/Source/PixelCapture/Public/PixelCaptureBufferFormat.h` (Public)


#### Free symbols / members of external scopes

- L11 _namespace_ `namespace PixelCaptureBufferFormat`
- L13 _variable_ `static const int32 FORMAT_UNKNOWN = 0;` (scope `PixelCaptureBufferFormat`)
- L14 _variable_ `static const int32 FORMAT_RHI = 1;` (scope `PixelCaptureBufferFormat`)
- L15 _variable_ `static const int32 FORMAT_I420 = 2;` (scope `PixelCaptureBufferFormat`)
- L16 _variable_ `static const int32 FORMAT_NV12 = 3;` (scope `PixelCaptureBufferFormat`)
- L17 _variable_ `static const int32 FORMAT_P010 = 4;` (scope `PixelCaptureBufferFormat`)
- L18 _variable_ `static const int32 FORMAT_I010 = 5;` (scope `PixelCaptureBufferFormat`)
- L20 _variable_ `static const int32 FORMAT_USER = 128;` (scope `PixelCaptureBufferFormat`)

### `Plugins/Media/PixelCapture/Source/PixelCapture/Public/PixelCaptureBufferI010.h` (Public)


#### class `FPixelCaptureBufferI010`  
`class FPixelCaptureBufferI010 : public IPixelCaptureBuffer`  
_L12-117_
- inherits: `IPixelCaptureBuffer`
- desc: Buffer class for holding I010 frame data.
- L18 _public prototype_ `FPixelCaptureBufferI010(int InWidth, int InHeight);` — Create an empty buffer of the specified size.
- L20 _public prototype_ `FPixelCaptureBufferI010(const FPixelCaptureBufferI010& Other) = default;`
- L21 _public prototype_ `virtual ~FPixelCaptureBufferI010() = default;`
- L26 _public function_ `virtual int32 GetWidth() const override` — Get the width of the frame
- L31 _public function_ `virtual int32 GetHeight() const override` — Get the height of the frame
- L36 _public function_ `virtual int32 GetFormat() const override` — Get the Buffer format
- L41 _public function_ `int32 GetStrideY() const` — Get the stride of the Y plane
- L46 _public function_ `int32 GetStrideUV() const` — Get the stride of the U and V planes
- L51 _public prototype_ `virtual const uint8_t* GetData() const override;` — Gets a const pointer to the beginning of entire buffer for reading.
- L56 _public prototype_ `const uint16_t* GetDataY() const;` — Gets a const pointer to the beginning of the Y plane for reading.
- L61 _public prototype_ `const uint16_t* GetDataU() const;` — Gets a const pointer to the beginning of the U plane for reading.
- L66 _public prototype_ `const uint16_t* GetDataV() const;` — Gets a const pointer to the beginning of the V plane for reading.
- L71 _public prototype_ `virtual uint8_t* GetMutableData() override;` — Gets a pointer to the beginning of the entire buffer for editing.
- L76 _public prototype_ `uint16_t* GetMutableDataY();` — Gets a pointer to the beginning of the Y plane for editing.
- L81 _public prototype_ `uint16_t* GetMutableDataU();` — Gets a pointer to the beginning of the U plane for editing.
- L86 _public prototype_ `uint16_t* GetMutableDataV();` — Gets a pointer to the beginning of the V plane for editing.
- L91 _public prototype_ `int32 GetDataSizeY() const;` — Gets the size of the Y plane in bytes.
- L96 _public prototype_ `int32 GetDataSizeUV() const;` — Gets the size of both the U and V planes in bytes.
- L101 _public function_ `virtual int64 GetSize() const override` — Gets the total size of this buffer.
- L107 _public function_ `void Copy(const FPixelCaptureBufferI010& Other)` — Copies the given buffer into this buffer. Supplied so copies can be explicit in code where we want to be verbose.
- L110 _private member_ `int Width = 0;`
- L111 _private member_ `int Height = 0;`
- L113 _private member_ `int StrideY = 0;`
- L114 _private member_ `int StrideUV = 0;`
- L116 _private member_ `TArray<uint16_t> Data;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API PIXELCAPTURE_API`

### `Plugins/Media/PixelCapture/Source/PixelCapture/Public/PixelCaptureBufferI420.h` (Public)


#### class `FPixelCaptureBufferI420`  
`class FPixelCaptureBufferI420 : public IPixelCaptureBuffer`  
_L12-117_
- inherits: `IPixelCaptureBuffer`
- desc: Buffer class for holding I420 frame data.
- L18 _public prototype_ `FPixelCaptureBufferI420(int InWidth, int InHeight);` — Create an empty buffer of the specified size.
- L20 _public prototype_ `FPixelCaptureBufferI420(const FPixelCaptureBufferI420& Other) = default;`
- L21 _public prototype_ `virtual ~FPixelCaptureBufferI420() = default;`
- L26 _public function_ `virtual int32 GetWidth() const override` — Get the width of the frame
- L31 _public function_ `virtual int32 GetHeight() const override` — Get the height of the frame
- L36 _public function_ `virtual int32 GetFormat() const override` — Get the Buffer format
- L41 _public function_ `int32 GetStrideY() const` — Get the stride of the Y plane
- L46 _public function_ `int32 GetStrideUV() const` — Get the stride of the U and V planes
- L51 _public prototype_ `virtual const uint8_t* GetData() const override;` — Gets a const pointer to the beginning of entire buffer for reading.
- L56 _public prototype_ `const uint8_t* GetDataY() const;` — Gets a const pointer to the beginning of the Y plane for reading.
- L61 _public prototype_ `const uint8_t* GetDataU() const;` — Gets a const pointer to the beginning of the U plane for reading.
- L66 _public prototype_ `const uint8_t* GetDataV() const;` — Gets a const pointer to the beginning of the V plane for reading.
- L71 _public prototype_ `virtual uint8_t* GetMutableData() override;` — Gets a pointer to the beginning of the entire buffer for editing.
- L76 _public prototype_ `uint8_t* GetMutableDataY();` — Gets a pointer to the beginning of the Y plane for editing.
- L81 _public prototype_ `uint8_t* GetMutableDataU();` — Gets a pointer to the beginning of the U plane for editing.
- L86 _public prototype_ `uint8_t* GetMutableDataV();` — Gets a pointer to the beginning of the V plane for editing.
- L91 _public prototype_ `int32 GetDataSizeY() const;` — Gets the size of the Y plane in bytes.
- L96 _public prototype_ `int32 GetDataSizeUV() const;` — Gets the size of both the U and V planes in bytes.
- L101 _public function_ `virtual int64 GetSize() const override` — Gets the total size of this buffer.
- L107 _public function_ `void Copy(const FPixelCaptureBufferI420& Other)` — Copies the given buffer into this buffer. Supplied so copies can be explicit in code where we want to be verbose.
- L110 _private member_ `int Width = 0;`
- L111 _private member_ `int Height = 0;`
- L113 _private member_ `int StrideY = 0;`
- L114 _private member_ `int StrideUV = 0;`
- L116 _private member_ `TArray<uint8_t> Data;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API PIXELCAPTURE_API`

### `Plugins/Media/PixelCapture/Source/PixelCapture/Public/PixelCaptureBufferNV12.h` (Public)


#### class `FPixelCaptureBufferNV12`  
`class FPixelCaptureBufferNV12 : public IPixelCaptureBuffer`  
_L12-107_
- inherits: `IPixelCaptureBuffer`
- desc: Buffer class for holding I420 frame data.
- L18 _public prototype_ `FPixelCaptureBufferNV12(int InWidth, int InHeight);` — Create an empty buffer of the specified size.
- L20 _public prototype_ `FPixelCaptureBufferNV12(const FPixelCaptureBufferNV12& Other) = default;`
- L21 _public prototype_ `virtual ~FPixelCaptureBufferNV12() = default;`
- L26 _public function_ `virtual int GetWidth() const override` — Get the width of the frame
- L31 _public function_ `virtual int GetHeight() const override` — Get the height of the frame
- L36 _public function_ `virtual int32 GetFormat() const override` — Get the Buffer format
- L41 _public function_ `int GetStrideY() const` — Get the stride of the Y plane
- L46 _public function_ `int GetStrideUV() const` — Get the stride of the U and V planes
- L51 _public prototype_ `virtual const uint8_t* GetData() const override;` — Gets a const pointer to the beginning of entire buffer for reading.
- L56 _public prototype_ `const uint8_t* GetDataY() const;` — Gets a const pointer to the beginning of the Y plane for reading.
- L61 _public prototype_ `const uint8_t* GetDataUV() const;` — Gets a const pointer to the beginning of the U plane for reading.
- L66 _public prototype_ `virtual uint8_t* GetMutableData() override;` — Gets a pointer to the beginning of the entire buffer for editing.
- L71 _public prototype_ `uint8_t* GetMutableDataY();` — Gets a pointer to the beginning of the Y plane for editing.
- L76 _public prototype_ `uint8_t* GetMutableDataUV();` — Gets a pointer to the beginning of the U plane for editing.
- L81 _public prototype_ `int GetDataSizeY() const;` — Gets the size of the Y plane in bytes.
- L86 _public prototype_ `int GetDataSizeUV() const;` — Gets the size of both the UV plane in bytes.
- L91 _public function_ `virtual int64 GetSize() const override` — Gets the total size of this buffer.
- L97 _public function_ `void Copy(const FPixelCaptureBufferNV12& Other)` — Copies the given buffer into this buffer. Supplied so copies can be explicit in code where we want to be verbose.
- L100 _private member_ `int Width = 0;`
- L101 _private member_ `int Height = 0;`
- L103 _private member_ `int StrideY = 0;`
- L104 _private member_ `int StrideUV = 0;`
- L106 _private member_ `TArray<uint8_t> Data;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API PIXELCAPTURE_API`

### `Plugins/Media/PixelCapture/Source/PixelCapture/Public/PixelCaptureCapturer.h` (Public)


#### struct `FPixelCaptureCapturerConfig`  
`struct FPixelCaptureCapturerConfig`  
_L21-25_
- L23 _public member_ `FIntPoint OutputResolution;`
- L24 _public member_ `bool bIsSRGB = false;`

#### class `FPixelCaptureCapturer`  
`class FPixelCaptureCapturer`  
_L40-172_
- desc: The base class for all Capturers in the system. Incoming frames will be user types implementing IPixelCaptureInputFrame. Outgoing frames should be user types implementing IPixelCaptureOutputFrame. Each capturer system should expect one known input user type. Implement CreateOutputBuffer to create your custom IPixelCaptureOutputFrame implementation to hold the result of the capture process. Implement BeginProcess to start the capture work which ideally should be an async task of some sort. The capture work should fill the given IPixelCaptureOutputFrame and then call EndProcess to indicate the work is done. While the capture should be async it should only expect to work on one frame at a time.
- L43 _public prototype_ `FPixelCaptureCapturer(FPixelCaptureCapturerConfig Config = {});`
- L44 _public prototype_ `virtual ~FPixelCaptureCapturer();`
- L50 _public prototype_ `void Capture(const IPixelCaptureInputFrame& InputFrame);` — Called when an input frame needs capturing. @param InputFrame The input frame to be captured.
- L57 _public function_ `bool IsInitialized() const` — Returns true if Initialize() has been called. Output data can depend on the incoming frames so we do lazy initialization when we first consume. @return True if this process has been initialized correctly.
- L63 _public function_ `bool IsBusy() const` — Returns true when this process is actively working on capturing frame data. @return True when this process is busy.
- L69 _public function_ `bool HasOutput() const` — Returns true if this process has a frame in the output buffer ready to be read. @return True when this process has output data.
- L75 _public prototype_ `TSharedPtr<IPixelCaptureOutputFrame> ReadOutput();` — Gets the output frame from the output buffer. @return The output data of this process.
- L80 _public prototype_ `DECLARE_TS_MULTICAST_DELEGATE(FOnComplete);` — Listen on this to be notified when the capture process completes for each input.
- L81 _public member_ `FOnComplete OnComplete;`
- L88 _protected function_ `void SetIsBusy(bool bInBusy)` — Sets whether this process is actively working on capturing frame data. @param bInBusy whether this process is busy.
- L95 _protected prototype_ `virtual FString GetCapturerName() const = 0;` — Gets the human readable name for this capture process. This name will be used in stats readouts so the shorter the better. @return A human readable name for this capture process.
- L102 _protected prototype_ `virtual void Initialize(int32 InputWidth, int32 InputHeight);` — Initializes the process to be ready for work. Called once at startup. @param InputWidth The pixel count of the input frame width @param InputHeight The pixel count of the input frame height
- L110 _protected prototype_ `virtual IPixelCaptureOutputFrame* CreateOutputBuffer(int32 InputWidth, int32 InputHeight) = 0;` — Implement this to create a buffer for the output. @param InputWidth The pixel width of the input frame. @param InputHeight The pixel height of the input frame. @return An empty output structure that the process can store the output of its process on.
- L118 _protected function_ `void BeginProcess(const IPixelCaptureInputFrame& InputFrame, IPixelCaptureOutputFrame* OutputBuffer)` — `UE_DEPRECATED(5.6, "BeginProcess(const IPixelCaptureInputFrame& InputFrame, IPixelCaptureOutputFrame* OutputBuffer) has been deprecated. Please use BeginProcess(const IPixelCaptureInputFrame& InputFrame, TSharedPtr<IPixelCaptureOutputFrame> OutputBuffer) to ensure memory safety.")` — Implement this with your specific process to capture the incoming frame. @param InputFrame The input frame data for the process to begin working on. @param OutputBuffer The destination buffer for the process. Is guaranteed to be of the type created in CreateOutputBuffer()
- L119 _protected prototype_ `virtual void BeginProcess(const IPixelCaptureInputFrame& InputFrame, TSharedPtr<IPixelCaptureOutputFrame> OutputBuffer) = 0;`
- L125 _protected function_ `void MarkCPUWorkStart()` — `UE_DEPRECATED(5.6, "MarkCPUWorkStart(void) has been deprecated. Please use MarkCPUWorkStart(TSharedPtr<IPixelCaptureOutputFrame> OutputBuffer) to ensure the metadata is updated for the correct output buffer.")` — Metadata info (optional). Marks the start of some CPU work. Multiple work sections are valid.
- L131 _protected function_ `void MarkCPUWorkEnd()` — `UE_DEPRECATED(5.6, "MarkCPUWorkEnd(void) has been deprecated. Please use UE::PixelCapture::MarkCPUWorkEnd(TSharedPtr<IPixelCaptureOutputFrame> OutputBuffer) to ensure the metadata is updated for the correct output buffer.")` — Metadata info (optional). Marks the end of some CPU work.
- L137 _protected function_ `void MarkGPUWorkStart()` — `UE_DEPRECATED(5.6, "MarkGPUWorkStart(void) has been deprecated. Please use UE::PixelCapture::MarkGPUWorkStart(TSharedPtr<IPixelCaptureOutputFrame> OutputBuffer) to ensure the metadata is updated for the correct output buffer.")` — Metadata info (optional). Marks the start of some GPU work. Multiple work sections are valid.
- L143 _protected function_ `void MarkGPUWorkEnd()` — `UE_DEPRECATED(5.6, "MarkGPUWorkEnd(void) has been deprecated. Please use UE::PixelCapture::MarkGPUWorkEnd(TSharedPtr<IPixelCaptureOutputFrame> OutputBuffer) to ensure the metadata is updated for the correct output buffer.")` — Metadata info (optional). Marks the end of some GPU work.
- L149 _protected function_ `void EndProcess()` — `UE_DEPRECATED(5.6, "EndProcess(void) has been deprecated. Please use EndProcess(TSharedPtr<IPixelCaptureOutputFrame> OutputBuffer) to ensure the metadata is updated for the correct output buffer.")` — Call this to mark the end of processing. Will commit the current write buffer into the read buffer.
- L150 _protected prototype_ `void EndProcess(TSharedPtr<IPixelCaptureOutputFrame> OutputBuffer);`
- L153 _protected member_ `FPixelCaptureCapturerConfig Config;`
- L156 _private member_ `bool bInitialized = false;`
- L157 _private member_ `bool bBusy = false;`
- L158 _private member_ `bool bHasOutput = false;`
- L160 _private member_ `int32 ExpectedInputWidth = 0;`
- L161 _private member_ `int32 ExpectedInputHeight = 0;`
- L163 _private member_ `FThreadSafeCounter64 FrameId;`
- L165 _private member_ `TUniquePtr<UE::PixelCapture::FOutputFrameBuffer> Buffer;`
- L167 _private member_ `mutable FCriticalSection OutputBuffersMutex;`
- L168 _private member_ `TArray<TSharedPtr<IPixelCaptureOutputFrame>> OutputBuffers;`
- L170 _private prototype_ `void InitMetadata(FPixelCaptureFrameMetadata InputMetadata, TSharedPtr<IPixelCaptureOutputFrame> OutputBuffer);`
- L171 _private prototype_ `void FinalizeMetadata(TSharedPtr<IPixelCaptureOutputFrame> OutputBuffer);`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API PIXELCAPTURE_API`
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace PixelCapture` (scope `UE`)
- L15 _prototype_ `void MarkCPUWorkStart(TSharedPtr<IPixelCaptureOutputFrame> OutputBuffer);` (scope `UE::PixelCapture`)
- L16 _prototype_ `void MarkCPUWorkEnd(TSharedPtr<IPixelCaptureOutputFrame> OutputBuffer);` (scope `UE::PixelCapture`)
- L17 _prototype_ `void MarkGPUWorkStart(TSharedPtr<IPixelCaptureOutputFrame> OutputBuffer);` (scope `UE::PixelCapture`)
- L18 _prototype_ `void MarkGPUWorkEnd(TSharedPtr<IPixelCaptureOutputFrame> OutputBuffer);` (scope `UE::PixelCapture`)
- L80 _delegate_ `DECLARE_TS_MULTICAST_DELEGATE(FOnComplete);` — Listen on this to be notified when the capture process completes for each input.

### `Plugins/Media/PixelCapture/Source/PixelCapture/Public/PixelCaptureCapturerI420.h` (Public)


#### class `FPixelCaptureCapturerI420`  
`class FPixelCaptureCapturerI420 : public FPixelCaptureCapturer`  
_L14-28_
- inherits: `FPixelCaptureCapturer`
- desc: A basic capturer that will copy I420 frames. Input: FPixelCaptureInputFrameI420 Output: FPixelCaptureOutputFrameI420
- L17 _public prototype_ `static TSharedPtr<FPixelCaptureCapturerI420> Create(FPixelCaptureCapturerConfig Config = {});`
- L18 _public prototype_ `virtual ~FPixelCaptureCapturerI420() = default;`
- L21 _protected function_ `virtual FString GetCapturerName() const override`
- L22 _protected prototype_ `virtual void Initialize(int32 InputWidth, int32 InputHeight) override;`
- L23 _protected prototype_ `virtual IPixelCaptureOutputFrame* CreateOutputBuffer(int32 InputWidth, int32 InputHeight) override;`
- L24 _protected prototype_ `virtual void BeginProcess(const IPixelCaptureInputFrame& InputFrame, TSharedPtr<IPixelCaptureOutputFrame> OutputBuffer) override;`
- L27 _private prototype_ `FPixelCaptureCapturerI420(FPixelCaptureCapturerConfig& Config);`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API PIXELCAPTURE_API`

### `Plugins/Media/PixelCapture/Source/PixelCapture/Public/PixelCaptureCapturerI420ToRHI.h` (Public)


#### class `FPixelCaptureCapturerI420ToRHI`  
`class FPixelCaptureCapturerI420ToRHI : public FPixelCaptureCapturer, public TSharedFromThis<FPixelCaptureCapturerI420ToRHI>`  
_L14-30_
- inherits: `FPixelCaptureCapturer,TSharedFromThis<FPixelCaptureCapturerI420ToRHI>`
- desc: A basic capturer that will capture I420 frames to native RHI textures. Input: FPixelCaptureInputFrameI420 Output: FPixelCaptureOutputFrameRHI
- L17 _public prototype_ `static TSharedPtr<FPixelCaptureCapturerI420ToRHI> Create(FPixelCaptureCapturerConfig Config = {});`
- L18 _public prototype_ `virtual ~FPixelCaptureCapturerI420ToRHI();`
- L21 _protected function_ `virtual FString GetCapturerName() const override`
- L22 _protected prototype_ `virtual void Initialize(int32 InputWidth, int32 InputHeight) override;`
- L23 _protected prototype_ `virtual IPixelCaptureOutputFrame* CreateOutputBuffer(int32 InputWidth, int32 InputHeight) override;`
- L24 _protected prototype_ `virtual void BeginProcess(const IPixelCaptureInputFrame& InputFrame, TSharedPtr<IPixelCaptureOutputFrame> OutputBuffer) override;`
- L27 _private member_ `uint8_t* ARGBBuffer = nullptr;`
- L29 _private prototype_ `FPixelCaptureCapturerI420ToRHI(FPixelCaptureCapturerConfig& Config);`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API PIXELCAPTURE_API`

### `Plugins/Media/PixelCapture/Source/PixelCapture/Public/PixelCaptureCapturerLayered.h` (Public)


#### class `FPixelCaptureCapturerLayered`  
`class FPixelCaptureCapturerLayered : public TSharedFromThis<FPixelCaptureCapturerLayered>`  
_L13-73_
- inherits: `TSharedFromThis<FPixelCaptureCapturerLayered>`
- desc: A capturer that contains multiple layers of different resolution capture processes. Feed it a IPixelCaptureCapturerSource that will create the appropriate base capturers. Input: User defined Output: Capturer defined
- L22 _public prototype_ `static TSharedPtr<FPixelCaptureCapturerLayered> Create(IPixelCaptureCapturerSource* InCapturerSource, int32 InDestinationFormat, TArray<FIntPoint> InOutputResolutions = {});` — Create a new Layered Capturer. @param InCapturerSource A source for capturers for each layer. @param InDestinationFormat The format to capture to. @param InOutputResolutions An optional parameter to specify the resolutions to create capture processes for during construction.
- L31 _public prototype_ `static TSharedPtr<FPixelCaptureCapturerLayered> Create(IPixelCaptureCapturerSource* InCapturerSource, int32 InDestinationFormat, TArray<float> LayerScales);` — `UE_DEPRECATED(5.7, "Create taking in an array of layer scales has been deprecated. You no longer need to pass in the scales during construction!")` — Create a new Layered Capturer. @param InCapturerSource A source for capturers for each layer. @param InDestinationFormat The format to capture to. @param LayerScales A list of scales for each layer.
- L33 _public prototype_ `virtual ~FPixelCaptureCapturerLayered() = default;`
- L38 _public prototype_ `void Capture(const IPixelCaptureInputFrame& SourceFrame);` — Begins the capture process of a given frame.
- L46 _public prototype_ `TSharedPtr<IPixelCaptureOutputFrame> ReadOutput(FIntPoint LayerSize);` — Try to read the result of the capture process. May return null if no output has been captured yet. @param LayerSize The resolution of the layer to try and read the output from. @return The captured frame layer if one exists. Null otherwise.
- L55 _public function_ `TSharedPtr<IPixelCaptureOutputFrame> ReadOutput(int32 LayerIndex)` — `UE_DEPRECATED(5.7, "ReadOutput using a layer index has been deprecated. Please use ReadOutput that takes a resolution")` — Try to read the result of the capture process. May return null if no output has been captured yet. @param LayerIndex The layer to try and read the output from. @return The captured frame layer if one exists. Null otherwise.
- L61 _public prototype_ `DECLARE_TS_MULTICAST_DELEGATE(FOnComplete);` — A callback to broadcast on when the frame has completed the capture process. Called once when all layers of a given input frame have completed.
- L62 _public member_ `FOnComplete OnComplete;`
- L65 _protected prototype_ `FPixelCaptureCapturerLayered(IPixelCaptureCapturerSource* InCapturerSource, int32 InDestinationFormat);`
- L67 _protected prototype_ `void OnCaptureComplete();`
- L69 _protected member_ `IPixelCaptureCapturerSource* CapturerSource;`
- L70 _protected member_ `int32 DestinationFormat;`
- L71 _protected member_ `TMap<FIntPoint, TSharedPtr<FPixelCaptureCapturer>> LayerCapturers;`
- L72 _protected member_ `mutable FCriticalSection LayersGuard;`

#### Free symbols / members of external scopes

- L61 _delegate_ `DECLARE_TS_MULTICAST_DELEGATE(FOnComplete);` — A callback to broadcast on when the frame has completed the capture process. Called once when all layers of a given input frame have completed.

### `Plugins/Media/PixelCapture/Source/PixelCapture/Public/PixelCaptureCapturerMultiFormat.h` (Public)


#### class `FPixelCaptureCapturerMultiFormat`  
`class FPixelCaptureCapturerMultiFormat : public TSharedFromThis<FPixelCaptureCapturerMultiFormat>`  
_L16-156_
- inherits: `TSharedFromThis<FPixelCaptureCapturerMultiFormat>`
- desc: A capturer that contains multiple formats of multi layer capture processes. Feed it a IPixelCaptureCapturerSource that will create the appropriate base capturers. Input: User defined Output: Capturer defined
- L24 _public prototype_ `static TSharedPtr<FPixelCaptureCapturerMultiFormat> Create(IPixelCaptureCapturerSource* InCapturerSource, TArray<FIntPoint> InOutputResolutions = {});` — Create a new multi-format multi-Layered Capturer. @param InCapturerSource A source for capturers for each layer. @param InOutputResolutions An optional parameter containing the output resolutions if known.
- L32 _public prototype_ `static TSharedPtr<FPixelCaptureCapturerMultiFormat> Create(IPixelCaptureCapturerSource* InCapturerSource, TArray<float> LayerScales);` — `UE_DEPRECATED(5.7, "Create taking in an array of layer scales has been deprecated. You no longer need to pass in the scales during construction!")` — Create a new multi-format multi-Layered Capturer. @param InCapturerSource A source for capturers for each layer. @param LayerScales A list of scales for each layer.
- L34 _public prototype_ `virtual ~FPixelCaptureCapturerMultiFormat();`
- L40 _public function_ `int32 GetNumLayers() const` — Gets the number of layers in the multi-layered capturers. @return The number of layers in each multi-layered capturer.
- L46 _public function_ `TArray<FIntPoint> GetLayerSizes() const` — Gets the layer sizes @return The array containing the resolution of each layer
- L53 _public function_ `int32 GetWidth(int LayerIndex) const` — `UE_DEPRECATED(5.7, "GetWidth for a layer index has been deprecated. You shouldn't need to use this as PixelCapture now uses resolutions directly")` — Gets the frame width of a given output layer. @return The pixel count of the width of a output layer.
- L60 _public function_ `int32 GetHeight(int LayerIndex) const` — `UE_DEPRECATED(5.7, "GetHeight for a layer index has been deprecated. You shouldn't need to use this as PixelCapture now uses resolutions directly")` — Gets the frame height of a given output layer. @return The pixel count of the height of a output layer.
- L65 _public prototype_ `void Capture(const IPixelCaptureInputFrame& SourceFrame);` — Begins the capture process of a given frame.
- L72 _public prototype_ `void AddOutputFormat(int32 Format);` — Sets up a capture pipeline for the given destination format. No effect if the pipeline already exists. @param Format The destination format for the requested pipeline.
- L83 _public prototype_ `TSharedPtr<IPixelCaptureOutputFrame> RequestFormat(int32 Format, FIntPoint LayerSize);` — Requests the output in a specific format. If this is the first request for the format and AddOutputFormat has not been called for the format then this call will return nullptr. Otherwise will return the buffer for the format provided the capture has completed. @param Format The format we want the output in. @param LayerSize The resolution of the layer we want to get the output of. @return The final buffer of a given format if it exists or null.
- L95 _public function_ `TSharedPtr<IPixelCaptureOutputFrame> RequestFormat(int32 Format, int32 LayerIndex)` — `UE_DEPRECATED(5.7, "RequestFormat taking a layer index has been deprecated. Please use RequestFormat that takes an FIntPoint resolution")` — Requests the output in a specific format. If this is the first request for the format and AddOutputFormat has not been called for the format then this call will return nullptr. Otherwise will return the buffer for the format provided the capture has completed. @param Format The format we want the output in. @param LayerIndex The layer we want to get the output of. @return The final buffer of a given format if it exists or null.
- L107 _public prototype_ `TSharedPtr<IPixelCaptureOutputFrame> WaitForFormat(int32 Format, FIntPoint LayerSize, uint32 MaxWaitTime = 5000);` — Like RequestFormat except if the format does not exist it will add it and then wait for the format to have output. NOTE: This will block the calling thread so it is important that the capture process is not dependent on this calling thread or we will deadlock. @param Format The format we want the output in. @param LayerSize The resolution of the layer we want to get the output of. @param MaxWaitTime The max number of milliseconds to wait for a frame. Default is 5 seconds. @return The final buffer of a given format or null in case of timeout or the capturer has been disconnected.
- L120 _public function_ `TSharedPtr<IPixelCaptureOutputFrame> WaitForFormat(int32 Format, int32 LayerIndex, uint32 MaxWaitTime = 5000)` — `UE_DEPRECATED(5.7, "WaitForFormat taking a layer index has been deprecated. Please use WaitForFormat that takes an FIntPoint resolution")` — Like RequestFormat except if the format does not exist it will add it and then wait for the format to have output. NOTE: This will block the calling thread so it is important that the capture process is not dependent on this calling thread or we will deadlock. @param Format The format we want the output in. @param LayerIndex The layer we want to get the output of. @param MaxWaitTime The max number of milliseconds to wait for a frame. Default is 5 seconds. @return The final buffer of a given format or null in case of timeout or the capturer has been disconnected.
- L126 _public prototype_ `void OnDisconnected();` — Call to notify this capturer that it has been disconnected and no more frames will be captured and any waiting for format calls should stop waiting.
- L131 _public prototype_ `DECLARE_TS_MULTICAST_DELEGATE(FOnComplete);` — Listen on this to be notified when a frame completes all capture formats/layers.
- L132 _public member_ `FOnComplete OnComplete;`
- L135 _protected prototype_ `FPixelCaptureCapturerMultiFormat(IPixelCaptureCapturerSource* InCapturerSource, TArray<FIntPoint> InOutputResolutions);`
- L136 _protected prototype_ `void OnCaptureFormatComplete(int32 Format);`
- L138 _protected prototype_ `FEvent* GetEventForFormat(int32 Format);`
- L139 _protected prototype_ `void CheckFormatEvent(int32 Format);`
- L140 _protected prototype_ `void FreeEvent(int32 Format, FEvent* Event);`
- L141 _protected prototype_ `void FlushWaitingEvents();`
- L143 _protected member_ `IPixelCaptureCapturerSource* CapturerSource;`
- L145 _protected member_ `mutable FCriticalSection LayersGuard;`
- L146 _protected member_ `TSet<FIntPoint> LayerSizes;`
- L148 _protected member_ `TMap<int32, TSharedPtr<FPixelCaptureCapturerLayered>> FormatCapturers;`
- L149 _protected member_ `TAtomic<int> PendingFormats = 0;` — atomic because the complete events can come in on multiple threads
- L150 _protected member_ `mutable FCriticalSection FormatGuard;`
- L152 _protected member_ `FCriticalSection EventMutex;`
- L153 _protected member_ `TMap<int32, FEvent*> FormatEvents;`
- L155 _protected member_ `bool bDisconnected = false;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API PIXELCAPTURE_API`
- L131 _delegate_ `DECLARE_TS_MULTICAST_DELEGATE(FOnComplete);` — Listen on this to be notified when a frame completes all capture formats/layers.

### `Plugins/Media/PixelCapture/Source/PixelCapture/Public/PixelCaptureCapturerNV12ToRHI.h` (Public)


#### class `FPixelCaptureCapturerNV12ToRHI`  
`class FPixelCaptureCapturerNV12ToRHI : public FPixelCaptureCapturer, public TSharedFromThis<FPixelCaptureCapturerNV12ToRHI>`  
_L14-30_
- inherits: `FPixelCaptureCapturer,TSharedFromThis<FPixelCaptureCapturerNV12ToRHI>`
- desc: A basic capturer that will capture NV12 frames to native RHI textures. Input: FPixelCaptureInputFrameNV12 Output: FPixelCaptureOutputFrameRHI
- L17 _public prototype_ `static TSharedPtr<FPixelCaptureCapturerNV12ToRHI> Create(FPixelCaptureCapturerConfig Config = {});`
- L18 _public prototype_ `virtual ~FPixelCaptureCapturerNV12ToRHI();`
- L21 _protected function_ `virtual FString GetCapturerName() const override`
- L22 _protected prototype_ `virtual void Initialize(int32 InputWidth, int32 InputHeight) override;`
- L23 _protected prototype_ `virtual IPixelCaptureOutputFrame* CreateOutputBuffer(int32 InputWidth, int32 InputHeight) override;`
- L24 _protected prototype_ `virtual void BeginProcess(const IPixelCaptureInputFrame& InputFrame, TSharedPtr<IPixelCaptureOutputFrame> OutputBuffer) override;`
- L27 _private member_ `uint8_t* R8Buffer = nullptr;`
- L29 _private prototype_ `FPixelCaptureCapturerNV12ToRHI(FPixelCaptureCapturerConfig& Config);`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API PIXELCAPTURE_API`

### `Plugins/Media/PixelCapture/Source/PixelCapture/Public/PixelCaptureCapturerRHI.h` (Public)


#### class `FPixelCaptureCapturerRHI`  
`class FPixelCaptureCapturerRHI : public FPixelCaptureCapturer, public TSharedFromThis<FPixelCaptureCapturerRHI>`  
_L15-36_
- inherits: `FPixelCaptureCapturer,TSharedFromThis<FPixelCaptureCapturerRHI>`
- desc: A basic capturer that will copy RHI texture frames. Input: FPixelCaptureInputFrameRHI Output: FPixelCaptureOutputFrameRHI
- L18 _public prototype_ `static TSharedPtr<FPixelCaptureCapturerRHI> Create(FPixelCaptureCapturerConfig Config = {});`
- L21 _public function_ `static TSharedPtr<FPixelCaptureCapturerRHI> Create(float InScale)` — `UE_DEPRECATED(5.7, "Create taking a scale has been deprecated. Please use Create that takes an FPixelCaptureCaptureConfig instead")`
- L23 _public prototype_ `virtual ~FPixelCaptureCapturerRHI() = default;`
- L26 _protected function_ `virtual FString GetCapturerName() const override`
- L27 _protected prototype_ `virtual IPixelCaptureOutputFrame* CreateOutputBuffer(int32 InputWidth, int32 InputHeight) override;`
- L28 _protected prototype_ `virtual void BeginProcess(const IPixelCaptureInputFrame& InputFrame, TSharedPtr<IPixelCaptureOutputFrame> OutputBuffer) override;`
- L31 _private member_ `ERHIInterfaceType RHIType;`
- L33 _private prototype_ `FPixelCaptureCapturerRHI(FPixelCaptureCapturerConfig& Config);`
- L34 _private prototype_ `void CheckComplete(TSharedPtr<IPixelCaptureOutputFrame> OutputBuffer, FGPUFenceRHIRef Fence);`
- L35 _private prototype_ `void OnRHIStageComplete(TSharedPtr<IPixelCaptureOutputFrame> OutputBuffer);`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API PIXELCAPTURE_API`

### `Plugins/Media/PixelCapture/Source/PixelCapture/Public/PixelCaptureCapturerRHINoCopy.h` (Public)


#### class `FPixelCaptureCapturerRHINoCopy`  
`class FPixelCaptureCapturerRHINoCopy : public FPixelCaptureCapturer, public TSharedFromThis<FPixelCaptureCapturerRHINoCopy>`  
_L17-37_
- inherits: `FPixelCaptureCapturer,TSharedFromThis<FPixelCaptureCapturerRHINoCopy>`
- desc: A basic capturer for receiving copy-safe RHI Texture frames. This pixel capturer will shortcut the need to copy texture is the input and output frame sizes match Input: FPixelCaptureInputFrameRHI Output: FPixelCaptureOutputFrameRHI
- L23 _public prototype_ `static TSharedPtr<FPixelCaptureCapturerRHINoCopy> Create(FPixelCaptureCapturerConfig Config = {});` — Creates a new capturer that assigns the output frame to the input frame. NOTE: This means this capturer doesn't support resolution or format changes
- L26 _public function_ `static TSharedPtr<FPixelCaptureCapturerRHINoCopy> Create(float InScale)` — `UE_DEPRECATED(5.7, "Create taking a scale has been deprecated. Please use Create that takes an FPixelCaptureCapturerConfig instead")`
- L28 _public prototype_ `virtual ~FPixelCaptureCapturerRHINoCopy() = default;`
- L31 _protected function_ `virtual FString GetCapturerName() const override`
- L32 _protected prototype_ `virtual IPixelCaptureOutputFrame* CreateOutputBuffer(int32 InputWidth, int32 InputHeight) override;`
- L33 _protected prototype_ `virtual void BeginProcess(const IPixelCaptureInputFrame& InputFrame, TSharedPtr<IPixelCaptureOutputFrame> OutputBuffer) override;`
- L36 _private prototype_ `FPixelCaptureCapturerRHINoCopy(FPixelCaptureCapturerConfig& Config);`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API PIXELCAPTURE_API`

### `Plugins/Media/PixelCapture/Source/PixelCapture/Public/PixelCaptureCapturerRHIRDG.h` (Public)


#### class `FPixelCaptureCapturerRHIRDG`  
`class FPixelCaptureCapturerRHIRDG : public FPixelCaptureCapturer, public TSharedFromThis<FPixelCaptureCapturerRHIRDG>`  
_L15-34_
- inherits: `FPixelCaptureCapturer,TSharedFromThis<FPixelCaptureCapturerRHIRDG>`
- desc: A basic capturer that will copy RHI texture frames. Input: FPixelCaptureInputFrameRHI Output: FPixelCaptureOutputFrameRHI
- L18 _public prototype_ `static TSharedPtr<FPixelCaptureCapturerRHIRDG> Create(FPixelCaptureCapturerConfig Config = {});`
- L21 _public function_ `static TSharedPtr<FPixelCaptureCapturerRHIRDG> Create(float InScale)` — `UE_DEPRECATED(5.7, "Create taking a scale has been deprecated. Please use Create that takes an FPixelCaptureCapturerConfig instead")`
- L23 _public prototype_ `virtual ~FPixelCaptureCapturerRHIRDG() = default;`
- L26 _protected function_ `virtual FString GetCapturerName() const override`
- L27 _protected prototype_ `virtual IPixelCaptureOutputFrame* CreateOutputBuffer(int32 InputWidth, int32 InputHeight) override;`
- L28 _protected prototype_ `virtual void BeginProcess(const IPixelCaptureInputFrame& InputFrame, TSharedPtr<IPixelCaptureOutputFrame> OutputBuffer) override;`
- L31 _private prototype_ `FPixelCaptureCapturerRHIRDG(FPixelCaptureCapturerConfig& Config);`
- L32 _private prototype_ `void CheckComplete();`
- L33 _private prototype_ `void OnRHIStageComplete(TSharedPtr<IPixelCaptureOutputFrame> OutputBuffer);`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API PIXELCAPTURE_API`

### `Plugins/Media/PixelCapture/Source/PixelCapture/Public/PixelCaptureCapturerRHIToI420CPU.h` (Public)


#### class `FPixelCaptureCapturerRHIToI420CPU`  
`class FPixelCaptureCapturerRHIToI420CPU : public FPixelCaptureCapturer, public TSharedFromThis<FPixelCaptureCapturerRHIToI420CPU>`  
_L17-45_
- inherits: `FPixelCaptureCapturer,TSharedFromThis<FPixelCaptureCapturerRHIToI420CPU>`
- desc: A basic capturer that will capture RHI texture frames to I420 buffers utilizing cpu functions. Involves CPU readback of GPU textures and processing of that readback data. Input: FPixelCaptureInputFrameRHI Output: FPixelCaptureOutputFrameI420
- L20 _public prototype_ `static TSharedPtr<FPixelCaptureCapturerRHIToI420CPU> Create(FPixelCaptureCapturerConfig Config = {});`
- L23 _public function_ `static TSharedPtr<FPixelCaptureCapturerRHIToI420CPU> Create(float InScale)` — `UE_DEPRECATED(5.7, "Create taking a scale has been deprecated. Please use Create that takes an FPixelCaptureCapturerConfig instead")`
- L25 _public prototype_ `virtual ~FPixelCaptureCapturerRHIToI420CPU();`
- L28 _protected function_ `virtual FString GetCapturerName() const override`
- L29 _protected prototype_ `virtual void Initialize(int32 InputWidth, int32 InputHeight) override;`
- L30 _protected prototype_ `virtual IPixelCaptureOutputFrame* CreateOutputBuffer(int32 InputWidth, int32 InputHeight) override;`
- L31 _protected prototype_ `virtual void BeginProcess(const IPixelCaptureInputFrame& InputFrame, TSharedPtr<IPixelCaptureOutputFrame> OutputBuffer) override;`
- L34 _private member_ `FTextureRHIRef StagingTexture;`
- L36 _private prototype_ `FPixelCaptureCapturerRHIToI420CPU(FPixelCaptureCapturerConfig& Config);`
- L39 _private member_ `TSharedPtr<FRHIGPUTextureReadback> TextureReader;`
- L40 _private prototype_ `void OnRHIStageComplete(TSharedPtr<IPixelCaptureOutputFrame> OutputBuffer);`
- L41 _private prototype_ `void CheckComplete(TSharedPtr<IPixelCaptureOutputFrame> OutputBuffer);`
- L43 _private member_ `FTextureRHIRef ReadbackTexture;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API PIXELCAPTURE_API`

### `Plugins/Media/PixelCapture/Source/PixelCapture/Public/PixelCaptureCapturerRHIToI420Compute.h` (Public)


#### class `FPixelCaptureCapturerRHIToI420Compute`  
`class FPixelCaptureCapturerRHIToI420Compute : public FPixelCaptureCapturer, public TSharedFromThis<FPixelCaptureCapturerRHIToI420Compute>`  
_L16-64_
- inherits: `FPixelCaptureCapturer,TSharedFromThis<FPixelCaptureCapturerRHIToI420Compute>`
- desc: A basic capturer that will capture RHI texture frames to I420 buffers utilizing a compute shader. Involves compute shader reading and processing of GPU textures so should be faster than CPU variant. Input: FPixelCaptureInputFrameRHI Output: FPixelCaptureOutputFrameI420
- L19 _public prototype_ `static TSharedPtr<FPixelCaptureCapturerRHIToI420Compute> Create(FPixelCaptureCapturerConfig Config = {});`
- L22 _public function_ `static TSharedPtr<FPixelCaptureCapturerRHIToI420Compute> Create(float InScale)` — `UE_DEPRECATED(5.7, "Create taking a scale has been deprecated. Please use Create that takes an FPixelCaptureCapturerConfig instead")`
- L24 _public prototype_ `virtual ~FPixelCaptureCapturerRHIToI420Compute();`
- L27 _protected function_ `virtual FString GetCapturerName() const override`
- L28 _protected prototype_ `virtual void Initialize(int32 InputWidth, int32 InputHeight) override;`
- L29 _protected prototype_ `virtual IPixelCaptureOutputFrame* CreateOutputBuffer(int32 InputWidth, int32 InputHeight) override;`
- L30 _protected prototype_ `virtual void BeginProcess(const IPixelCaptureInputFrame& InputFrame, TSharedPtr<IPixelCaptureOutputFrame> OutputBuffer) override;`
- L34 _private member_ `FIntPoint PlaneYDimensions;` — dimensions of the texures
- L35 _private member_ `FIntPoint PlaneUVDimensions;`
- L38 _private member_ `FTextureRHIRef TextureY;` — used as targets for the compute shader
- L39 _private member_ `FTextureRHIRef TextureU;`
- L40 _private member_ `FTextureRHIRef TextureV;`
- L43 _private member_ `FUnorderedAccessViewRHIRef TextureYUAV;` — the UAVs of the targets
- L44 _private member_ `FUnorderedAccessViewRHIRef TextureUUAV;`
- L45 _private member_ `FUnorderedAccessViewRHIRef TextureVUAV;`
- L48 _private member_ `FTextureRHIRef StagingTextureY;` — cpu readable copies of the targets above
- L49 _private member_ `FTextureRHIRef StagingTextureU;`
- L50 _private member_ `FTextureRHIRef StagingTextureV;`
- L53 _private member_ `void* MappedY = nullptr;` — memory mapped pointers of the staging textures
- L54 _private member_ `void* MappedU = nullptr;`
- L55 _private member_ `void* MappedV = nullptr;`
- L57 _private member_ `int32 YStride = 0;`
- L58 _private member_ `int32 UStride = 0;`
- L59 _private member_ `int32 VStride = 0;`
- L61 _private prototype_ `FPixelCaptureCapturerRHIToI420Compute(FPixelCaptureCapturerConfig& Config);`
- L62 _private prototype_ `void OnRHIStageComplete(TSharedPtr<IPixelCaptureOutputFrame> OutputBuffer);`
- L63 _private prototype_ `void CleanUp();`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API PIXELCAPTURE_API`

### `Plugins/Media/PixelCapture/Source/PixelCapture/Public/PixelCaptureFrameMetadata.h` (Public)


#### class `FPixelCaptureUserData`  
`class FPixelCaptureUserData`  
_L7-7_

#### struct `FPixelCaptureFrameMetadata`  
`struct FPixelCaptureFrameMetadata`  
_L9-91_
- L12 _public member_ `FString ProcessName = "Un` — Identifier for the capture pipeline/process this frame took
- L15 _public member_ `uint64 Id = 0;` — Identifier for the frame
- L18 _public member_ `int32 Layer = 0;` — Which layer this specific frame is associated with
- L21 _public member_ `uint64 SourceTime = 0;` — The time this frame was sourced/created
- L24 _public member_ `uint64 CaptureStartCyles = 0;` — Timestamps to track the entire length of the capture process
- L25 _public member_ `uint64 CaptureEndCyles = 0;`
- L28 _public member_ `uint64 CaptureProcessCPUStartCycles = 0;` — Timestamps for when CPU work has started / ended
- L29 _public member_ `uint64 CaptureProcessCPUEndCycles = 0;`
- L32 _public member_ `uint64 CaptureProcessGPUEnqueueStartCycles = 0;` — Timestamps for when the capture process was enqueued to the GPU and when the GPU actually started work
- L33 _public member_ `uint64 CaptureProcessGPUEnqueueEndCycles = 0;`
- L36 _public member_ `uint64 CaptureProcessGPUStartCycles = 0;` — Timestamps for when the GPU started work and when the GPU finished the capture process
- L37 _public member_ `uint64 CaptureProcessGPUEndCycles = 0;`
- L40 _public member_ `uint64 CaptureProcessPostGPUStartCycles = 0;` — Timestamps for tracking time after the GPU completed it's work until the capture process completed.
- L41 _public member_ `uint64 CaptureProcessPostGPUEndCycles = 0;`
- L45 _public member_ `uint64 CaptureTime = 0;` — `UE_DEPRECATED(5.6, "CaptureTime has been deprecated. You can calculate the time taken with FPlatformTime::ToMilliseconds64(CaptureEndCyles - CaptureStartCyles).")` — Capture process timings. Duration not timestamp.
- L47 _public member_ `uint64 CaptureProcessCPUTime = 0;` — `UE_DEPRECATED(5.6, "CaptureProcessCPUTime has been deprecated. You can calculate the time taken with FPlatformTime::ToMilliseconds64(CaptureProcessCPUEndCycles - CaptureProcessCPUStartCycles).")`
- L49 _public member_ `uint64 CaptureProcessGPUDelay = 0;` — `UE_DEPRECATED(5.6, "CaptureProcessGPUDelay has been deprecated. You can calculate the time taken with FPlatformTime::ToMilliseconds64(CaptureProcessGPUEnqueueEndCycles - CaptureProcessGPUEnqueueStartCycles).")`
- L51 _public member_ `uint64 CaptureProcessGPUTime = 0;` — `UE_DEPRECATED(5.6, "CaptureProcessGPUTime has been deprecated. You can calculate the time taken with FPlatformTime::ToMilliseconds64(CaptureProcessGPUEndCycles - CaptureProcessGPUStartCycles).")`
- L54 _public member_ `uint64 DisplayTime = 0;` — Display process timings. Duration not timestamp.
- L57 _public member_ `uint32 UseCount = 0;` — Frame use timings (can happen multiple times. ie. we are consuming frames faster than producing them)
- L60 _public member_ `uint64 FirstEncodeStartTime = 0;` — Encode Timings
- L61 _public member_ `uint64 LastEncodeStartTime = 0;`
- L62 _public member_ `uint64 LastEncodeEndTime = 0;`
- L65 _public member_ `uint64 FirstPacketizationStartTime = 0;` — Packet Timings
- L66 _public member_ `uint64 LastPacketizationStartTime = 0;`
- L67 _public member_ `uint64 LastPacketizationEndTime = 0;`
- L70 _public member_ `uint64 FirstDecodeStartTime = 0;` — Decode Timings
- L71 _public member_ `uint64 LastDecodeStartTime = 0;`
- L72 _public member_ `uint64 LastDecodeEndTime = 0;`
- L75 _public member_ `TSharedPtr<FPixelCaptureUserData> UserData;` — Pointer to a user class that stores additional metadata that they want to keep throughout the process
- L80 _public function_ `FPixelCaptureFrameMetadata Copy() const` — wanted this to be explicit with a name
- L85 _public prototype_ `FPixelCaptureFrameMetadata() = default;`
- L86 _public prototype_ `FPixelCaptureFrameMetadata(FPixelCaptureFrameMetadata&&) = default;`
- L87 _public prototype_ `FPixelCaptureFrameMetadata(const FPixelCaptureFrameMetadata&) = default;`
- L88 _public prototype_ `FPixelCaptureFrameMetadata& operator=(FPixelCaptureFrameMetadata&&) = default;`
- L89 _public prototype_ `FPixelCaptureFrameMetadata& operator=(const FPixelCaptureFrameMetadata&) = default;`

### `Plugins/Media/PixelCapture/Source/PixelCapture/Public/PixelCaptureI420Buffer.h` (Public)


#### Free symbols / members of external scopes

- L8 _typedef_ `typedef FPixelCaptureBufferI420 FPixelCaptureI420Buffer;` — `UE_DEPRECATED(5.2, "Use FPixelCaptureBufferI420 instead.")`

### `Plugins/Media/PixelCapture/Source/PixelCapture/Public/PixelCaptureInputFrameI420.h` (Public)


#### class `FPixelCaptureInputFrameI420`  
`class FPixelCaptureInputFrameI420 : public IPixelCaptureInputFrame`  
_L13-27_
- inherits: `IPixelCaptureInputFrame`
- desc: A basic input frame for the Capture system that wraps a I420 buffer.
- L16 _public prototype_ `FPixelCaptureInputFrameI420(TSharedPtr<FPixelCaptureBufferI420> Buffer, TSharedPtr<FPixelCaptureUserData> UserData = nullptr);`
- L17 _public prototype_ `virtual ~FPixelCaptureInputFrameI420() = default;`
- L19 _public prototype_ `virtual int32 GetType() const override;`
- L20 _public prototype_ `virtual int32 GetWidth() const override;`
- L21 _public prototype_ `virtual int32 GetHeight() const override;`
- L23 _public prototype_ `TSharedPtr<FPixelCaptureBufferI420> GetBuffer() const;`
- L26 _private member_ `TSharedPtr<FPixelCaptureBufferI420> I420Buffer;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API PIXELCAPTURE_API`

### `Plugins/Media/PixelCapture/Source/PixelCapture/Public/PixelCaptureInputFrameNV12.h` (Public)


#### class `FPixelCaptureInputFrameNV12`  
`class FPixelCaptureInputFrameNV12 : public IPixelCaptureInputFrame`  
_L13-27_
- inherits: `IPixelCaptureInputFrame`
- desc: A basic input frame for the Capture system that wraps a I420 buffer.
- L16 _public prototype_ `FPixelCaptureInputFrameNV12(TSharedPtr<FPixelCaptureBufferNV12> Buffer, TSharedPtr<FPixelCaptureUserData> UserData = nullptr);`
- L17 _public prototype_ `virtual ~FPixelCaptureInputFrameNV12() = default;`
- L19 _public prototype_ `virtual int32 GetType() const override;`
- L20 _public prototype_ `virtual int32 GetWidth() const override;`
- L21 _public prototype_ `virtual int32 GetHeight() const override;`
- L23 _public prototype_ `TSharedPtr<FPixelCaptureBufferNV12> GetBuffer() const;`
- L26 _private member_ `TSharedPtr<FPixelCaptureBufferNV12> NV12Buffer;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API PIXELCAPTURE_API`

### `Plugins/Media/PixelCapture/Source/PixelCapture/Public/PixelCaptureInputFrameRHI.h` (Public)


#### class `FPixelCaptureInputFrameRHI`  
`class FPixelCaptureInputFrameRHI : public IPixelCaptureInputFrame`  
_L13-24_
- inherits: `IPixelCaptureInputFrame`
- desc: A basic input frame for the Capture system that wraps a RHI texture buffer.
- L16 _public prototype_ `FPixelCaptureInputFrameRHI(FTextureRHIRef InFrameTexture, TSharedPtr<FPixelCaptureUserData> UserData = nullptr);`
- L17 _public prototype_ `virtual ~FPixelCaptureInputFrameRHI() = default;`
- L19 _public prototype_ `virtual int32 GetType() const override;`
- L20 _public prototype_ `virtual int32 GetWidth() const override;`
- L21 _public prototype_ `virtual int32 GetHeight() const override;`
- L23 _public member_ `FTextureRHIRef FrameTexture;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API PIXELCAPTURE_API`

### `Plugins/Media/PixelCapture/Source/PixelCapture/Public/PixelCaptureOutputFrameI420.h` (Public)


#### class `FPixelCaptureOutputFrameI420`  
`class FPixelCaptureOutputFrameI420 : public IPixelCaptureOutputFrame`  
_L11-28_
- inherits: `IPixelCaptureOutputFrame`
- desc: A basic output frame from the Capture system that wraps a I420 buffer.
- L14 _public function_ `FPixelCaptureOutputFrameI420(TSharedPtr<FPixelCaptureBufferI420> InI420Buffer) : I420Buffer(InI420Buffer)`
- L18 _public prototype_ `virtual ~FPixelCaptureOutputFrameI420() = default;`
- L20 _public function_ `virtual int32 GetWidth() const override`
- L21 _public function_ `virtual int32 GetHeight() const override`
- L23 _public function_ `TSharedPtr<FPixelCaptureBufferI420> GetI420Buffer() const`
- L24 _public function_ `void SetI420Buffer(TSharedPtr<FPixelCaptureBufferI420> InI420Buffer)`
- L27 _private member_ `TSharedPtr<FPixelCaptureBufferI420> I420Buffer;`

### `Plugins/Media/PixelCapture/Source/PixelCapture/Public/PixelCaptureOutputFrameRHI.h` (Public)


#### class `FPixelCaptureOutputFrameRHI`  
`class FPixelCaptureOutputFrameRHI : public IPixelCaptureOutputFrame`  
_L11-66_
- inherits: `IPixelCaptureOutputFrame`
- desc: A basic output frame from the Capture system that wraps a RHI texture buffer.
- L27 _public function_ `FPixelCaptureOutputFrameRHI(FTextureRHIRef InFrameTexture) : FrameTexture(InFrameTexture), bHasWrapperFormatData(false), WrapperData()`
- L32 _public function_ `FPixelCaptureOutputFrameRHI(FTextureRHIRef InFrameTexture, WrapperFormatData InWrapperData) : FrameTexture(InFrameTexture), bHasWrapperFormatData(true), WrapperData(InWrapperData)`
- L37 _public prototype_ `virtual ~FPixelCaptureOutputFrameRHI() = default;`
- L39 _public function_ `virtual int32 GetWidth() const override`
- L43 _public function_ `virtual int32 GetHeight() const override`
- L48 _public function_ `virtual bool GetWrapperFormatData(WrapperFormatData& OutData) const`
- L58 _public function_ `FTextureRHIRef GetFrameTexture() const`
- L60 _public function_ `void SetFrameTexture(FTextureRHIRef InFrameTexture)`
- L63 _private member_ `FTextureRHIRef FrameTexture;`
- L64 _private member_ `bool bHasWrapperFormatData;`
- L65 _private member_ `WrapperFormatData WrapperData;`

#### struct `FPixelCaptureOutputFrameRHI::WrapperFormatData`  
`struct WrapperFormatData`  
_L20-25_
- desc: Sometimes we need to pack data in a pixel format not fully supported by the RHI, so we may instead store it as a different format for transport and read it as the original format sometime later, this struct is meant to hold information about the wrapper format if it exists
- L22 _public member_ `int32 Width;`
- L23 _public member_ `int32 Height;`
- L24 _public member_ `EPixelFormat Format;`
