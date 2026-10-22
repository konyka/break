# Runtime / ImageWriteQueue

- module root: `Source/Runtime/ImageWriteQueue`
- headers: 6; symbols: 140
- symbol kinds: class=5, delegate=2, enum=5, enumerator=13, function=35, member=32, prototype=30, struct=15, typedef=3
- PrivateDependencyModuleNames: Engine, RHI, RenderCore
- PublicDependencyModuleNames: Core, CoreUObject, ImageCore, ImageWrapper

### `Source/Runtime/ImageWriteQueue/Public/ImagePixelData.h` (Public)


#### enum `EImagePixelType`  
`enum class EImagePixelType`  
_L16-21_
- desc: todo : use ImageCore ERawImageFormat instead
- L18 _public enumerator_ `Color`
- L19 _public enumerator_ `Float16`
- L20 _public enumerator_ `Float32`

#### struct `IImagePixelDataPayload`  
`struct IImagePixelDataPayload`  
_L23-26_
- L25 _public prototype_ `virtual ~IImagePixelDataPayload() = default;`

#### struct `FImagePixelData`  
`struct FImagePixelData`  
_L34-257_
- desc: @todo Oodle : use ImageCore FImage instead get rid of this whole class and TImagePixelData too just use an FImage instead
- L36 _public prototype_ `virtual ~FImagePixelData() = default;`
- L44 _public function_ `EImagePixelType GetType() const` — Retrieve the type of this data
- L52 _public function_ `FIntPoint GetSize() const` — Retrieve the size of this data
- L60 _public function_ `ERGBFormat GetPixelLayout() const` — Retrieve the pixel layout of this data
- L68 _public function_ `uint8 GetBitDepth() const` — Retrieve the number of bits per each channel of color in the data
- L76 _public function_ `uint8 GetNumChannels() const` — Retrieve the number of channels in the data
- L84 _public function_ `FImageView GetImageView() const` — Get the pixel data as an FImage
- L130 _public function_ `void SetAlphaOpaque()` — Change the alpha channel to opaque
- L138 _public function_ `bool IsDataWellFormed() const` — Check that this data is the size it should be
- L149 _public function_ `bool GetRawData(const void*& OutRawData, int64& OutSizeBytes) const` — Get the data and its size only if it is well formed
- L169 _public function_ `int64 GetRawDataSizeInBytes() const` — Get the size in bytes, regardless of if it is well formed.
- L181 _public function_ `TUniquePtr<FImagePixelData> CopyImageData() const` — Copy this whole image buffer. This can be very costly for large images.
- L189 _public function_ `TUniquePtr<FImagePixelData> MoveImageDataToNew()` — Move this whole image buffer to a new allocation.
- L198 _public function_ `template<typename T> T* GetPayload()` — Return a pointer to the Payload stored in this data.
- L204 _public function_ `template<typename T> const T* GetPayload() const` — Return a const pointer to the Payload stored in this data.
- L209 _public function_ `void SetPayload(FImagePixelPayloadPtr NewPayload)` — Sets the payload after construction.
- L211 _public function_ `bool GetSRGB() const`
- L212 _public function_ `void SetSRGB(bool InSRGB)`
- L216 _protected function_ `FImagePixelData(const FIntPoint& InSize, EImagePixelType InPixelType, ERGBFormat InPixelLayout, uint8 InBitDepth, uint8 InNumChannels, FImagePixelPayloadPtr InPayload) : Size(InSize) , Type(InPixelType) , PixelLayout(InPixelLayout) , BitDepth(InBitDepth) , NumChannels(InNumChannels) , Payload(InPayload)`
- L233 _private prototype_ `virtual void RetrieveData(const void*& OutDataPtr, int64& OutSizeBytes) const = 0;` — Retrieve the raw pixel data
- L234 _private prototype_ `virtual TUniquePtr<FImagePixelData> Copy() const = 0;`
- L235 _private prototype_ `virtual TUniquePtr<FImagePixelData> Move() = 0;`
- L238 _private member_ `FIntPoint Size;` — The size of the pixel data
- L241 _private member_ `EImagePixelType Type;` — The type of the derived data
- L244 _private member_ `ERGBFormat PixelLayout;` — The pixel layout of this data
- L247 _private member_ `uint8 BitDepth;` — The number of bits per each channel of color in the data
- L250 _private member_ `uint8 NumChannels;` — Number of channels in the data
- L253 _private member_ `bool bSRGB;` — Is FColor SRGB or Linear?  Floats are always Linear and ignore this
- L256 _private member_ `FImagePixelPayloadPtr Payload;` — Optional user-specified payload

#### struct `TImagePixelData`  
`template<typename PixelType> struct TImagePixelData : FImagePixelData`  
_L263-300_
- inherits: `FImagePixelData`
- desc: Templated pixel data - currently supports FColor, FFloat16Color and FLinearColor
- L265 _public member_ `TArray64<PixelType> Pixels;`
- L267 _public function_ `TImagePixelData(const FIntPoint& InSize) : FImagePixelData(InSize, TImagePixelDataTraits<PixelType>::PixelType, TImagePixelDataTraits<PixelType>::PixelLayout, TImagePixelDataTraits<PixelType>::BitDepth, TImagePixelDataTraits<PixelType>::NumChannels, nullptr)`
- L271 _public function_ `TImagePixelData(const FIntPoint& InSize, TArray64<PixelType>&& InPixels) : FImagePixelData(InSize, TImagePixelDataTraits<PixelType>::PixelType, TImagePixelDataTraits<PixelType>::PixelLayout, TImagePixelDataTraits<PixelType>::BitDepth, TImagePixelDataTraits<PixelType>::NumChannels, nullptr) , Pixels(MoveTemp(InPixels))`
- L276 _public function_ `TImagePixelData(const FIntPoint& InSize, FImagePixelPayloadPtr InPayload) : FImagePixelData(InSize, TImagePixelDataTraits<PixelType>::PixelType, TImagePixelDataTraits<PixelType>::PixelLayout, TImagePixelDataTraits<PixelType>::BitDepth, TImagePixelDataTraits<PixelType>::NumChannels, InPayload)`
- L280 _public function_ `TImagePixelData(const FIntPoint& InSize, TArray64<PixelType>&& InPixels, FImagePixelPayloadPtr InPayload) : FImagePixelData(InSize, TImagePixelDataTraits<PixelType>::PixelType, TImagePixelDataTraits<PixelType>::PixelLayout, TImagePixelDataTraits<PixelType>::BitDepth, TImagePixelDataTraits<PixelType>::NumChannels, InPayload) , Pixels(MoveTemp(InPixels))`
- L285 _public function_ `virtual TUniquePtr<FImagePixelData> Move() override`
- L290 _public function_ `virtual TUniquePtr<FImagePixelData> Copy() const override`
- L295 _public function_ `virtual void RetrieveData(const void*& OutDataPtr, int64& OutSizeBytes) const override`

#### struct `TImagePixelDataTraits`  
`template<> struct TImagePixelDataTraits<FColor>`  
_L302-308_
- L304 _public member_ `static const ERGBFormat PixelLayout = ERGBFormat::BGRA;`
- L305 _public member_ `static const EImagePixelType PixelType = EImagePixelType::Color;`
- L312 _public member_ `static const ERGBFormat PixelLayout = ERGBFormat::RGBAF;`
- L313 _public member_ `static const EImagePixelType PixelType = EImagePixelType::Float16;`
- L321 _public member_ `static const EImagePixelType PixelType = EImagePixelType::Float32;`

#### enum `TImagePixelDataTraits::(anonymous)`  
`enum`  
_L307-307_

#### struct `TImagePixelDataTraits`  
`template<> struct TImagePixelDataTraits<FFloat16Color>`  
_L310-316_
- L304 _public member_ `static const ERGBFormat PixelLayout = ERGBFormat::BGRA;`
- L305 _public member_ `static const EImagePixelType PixelType = EImagePixelType::Color;`
- L312 _public member_ `static const ERGBFormat PixelLayout = ERGBFormat::RGBAF;`
- L313 _public member_ `static const EImagePixelType PixelType = EImagePixelType::Float16;`
- L321 _public member_ `static const EImagePixelType PixelType = EImagePixelType::Float32;`

#### enum `TImagePixelDataTraits::(anonymous)`  
`enum`  
_L315-315_

#### struct `TImagePixelDataTraits`  
`template<> struct TImagePixelDataTraits<FLinearColor>`  
_L318-324_
- L304 _public member_ `static const ERGBFormat PixelLayout = ERGBFormat::BGRA;`
- L305 _public member_ `static const EImagePixelType PixelType = EImagePixelType::Color;`
- L312 _public member_ `static const ERGBFormat PixelLayout = ERGBFormat::RGBAF;`
- L313 _public member_ `static const EImagePixelType PixelType = EImagePixelType::Float16;`
- L321 _public member_ `static const EImagePixelType PixelType = EImagePixelType::Float32;`

#### enum `TImagePixelDataTraits::(anonymous)`  
`enum`  
_L323-323_

#### Free symbols / members of external scopes

- L28 _typedef_ `typedef TSharedPtr<IImagePixelDataPayload, ESPMode::ThreadSafe> FImagePixelPayloadPtr;`
- L307 _enumerator_ `enum { BitDepth = 8, NumChannels = 4 };` (scope `TImagePixelDataTraits::__anon4a10694e0103`)
- L307 _enumerator_ `enum { BitDepth = 8, NumChannels = 4 };` (scope `TImagePixelDataTraits::__anon4a10694e0103`)
- L315 _enumerator_ `enum { BitDepth = 16, NumChannels = 4 };` (scope `TImagePixelDataTraits::__anon4a10694e0203`)
- L315 _enumerator_ `enum { BitDepth = 16, NumChannels = 4 };` (scope `TImagePixelDataTraits::__anon4a10694e0203`)
- L323 _enumerator_ `enum { BitDepth = 32, NumChannels = 4 };` (scope `TImagePixelDataTraits::__anon4a10694e0303`)
- L323 _enumerator_ `enum { BitDepth = 32, NumChannels = 4 };` (scope `TImagePixelDataTraits::__anon4a10694e0303`)

### `Source/Runtime/ImageWriteQueue/Public/ImageWriteBlueprintLibrary.h` (Public)


#### struct `FImageWriteOptions`  
`struct FImageWriteOptions`  
_L20-54_
- reflection: `USTRUCT(BlueprintType)`
- desc: Options specific to writing image files to disk
- L24 _public function_ `FImageWriteOptions() : Format(EDesiredImageFormat::EXR) , bOverwriteFile(true) , bAsync(true)`
- L34 _public member_ `EDesiredImageFormat Format;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Image")` — The desired output image format to write to disk
- L38 _public member_ `FOnImageWriteComplete OnComplete;` — `UPROPERTY(BlueprintReadWrite, Category="Image")` — A callback to invoke when the image has been written, or there was an error
- L42 _public member_ `int32 CompressionQuality;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Image")` — An image format specific compression setting. Either 0 (Default) or 1 (Uncompressed) for EXRs, or a value between 0 and 100.
- L46 _public member_ `bool bOverwriteFile;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Image")` — Whether to overwrite the image if it already exists
- L50 _public member_ `bool bAsync;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Image")` — Whether to perform the writing asynchronously, or to block the game thread until it is complete
- L53 _public member_ `TFunction<void(bool)> NativeOnComplete;` — A native completion callback that will be called in addition to the dynamic one above.

#### class `UImageWriteBlueprintLibrary`  
`class UImageWriteBlueprintLibrary : public UBlueprintFunctionLibrary`  
_L60-77_
- reflection: `UCLASS()`
- inherits: `UBlueprintFunctionLibrary`
- desc: Function library containing utility methods for writing images on a global async queue
- L66 _public prototype_ `static bool ResolvePixelData(UTexture* Texture, const FOnPixelsReady& OnPixelsReady);`
- L76 _public prototype_ `static void ExportToDisk(UTexture* Texture, const FString& Filename, const FImageWriteOptions& Options);` — `UFUNCTION(BlueprintCallable, Category=Texture, meta=(ScriptMethod))` — Export the specified texture to disk @param Texture         The texture or render target to export @param Filename        The filename on disk to save as @param Options         Parameters defining the various export options

#### Free symbols / members of external scopes

- L12 _typedef_ `typedef TFunction<void(TUniquePtr<FImagePixelData>&&)> FOnPixelsReady;`
- L14 _delegate_ `DECLARE_DYNAMIC_DELEGATE_OneParam(FOnImageWriteComplete, bool, bSuccess);`
- L14 _prototype_ `DECLARE_DYNAMIC_DELEGATE_OneParam(FOnImageWriteComplete, bool, bSuccess);`

### `Source/Runtime/ImageWriteQueue/Public/ImageWriteQueue.h` (Public)


#### class `IImageWriteQueue`  
`class IImageWriteQueue`  
_L26-56_
- desc: Public interface for an asynchronous queue of work dedicated to writing images to disk Concurrency metrics are controllable by ImageWriteQueue.MaxConcurrency and ImageWriteQueue.MaxQueueSize Dispatched tasks can contain callbacks that are called on the main thread when completed. It is possible to wait on completion of the current queue state by creating a 'fence' that can be waited upon
- L30 _public prototype_ `virtual ~IImageWriteQueue()= default;`
- L39 _public prototype_ `virtual TFuture<bool> Enqueue(TUniquePtr<IImageWriteTaskBase>&& InTask, bool bInBlockIfAtCapacity = true) = 0;` — (thread-safe) Enqueue a new asynchronous image write task. @param InTask                 A unique pointer to a task to perform on a thread when available. Pass with MoveTemp(). @param bInBlockIfAtCapacity   Wait until the number of pending tasks does not exceed the queue capacity. If false and the number of pending tasks does exceed, the function will return and will not enqueue the task. @return A future to the completion state of the task (success or failure), or an invalid future in the case where the task could not be dispatched
- L49 _public prototype_ `virtual TFuture<void> CreateFence(const TFunction<void()>& InOnFenceReached = TFunction<void()>()) = 0;` — (thread-safe) Create a fence at the current position in the queue. The future and callback will be invoked when all existing tasks in the queue have been completed. @note: Where the queue is empty, the future will be immediately fulfilled, and callback invoked on the next main thread tick. @param InOnFenceReached       A callback to be invoked when the fence has been reached (ie _all_ work ahead of it in the queue has been completed) @return A future that is fulfilled when the current state of the queue has been completely finished
- L55 _public prototype_ `virtual int32 GetNumPendingTasks() const = 0;` — (thread-safe) Query the number of tasks currently pending or in progress

#### class `IImageWriteQueueModule`  
`class IImageWriteQueueModule : public IModuleInterface`  
_L62-70_
- inherits: `IModuleInterface`
- desc: Module implementation that returns a write queue. Access is only via the module interface to ensure that the queue is flushed correctly on shutdown
- L69 _public prototype_ `virtual IImageWriteQueue& GetWriteQueue() = 0;` — Access a global queue of image writing tasks

#### Free symbols / members of external scopes

- L15 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogImageWriteQueue, Warning, Warning);`
- L15 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogImageWriteQueue, Warning, Warning);`

### `Source/Runtime/ImageWriteQueue/Public/ImageWriteStream.h` (Public)


#### struct `FImagePixelPipe`  
`struct FImagePixelPipe`  
_L20-76_
- desc: A pipe that receives image data and forwards it onto 0 or more end points, copying the buffer as few times as possible
- L25 _public function_ `FImagePixelPipe()` — Default constructor (an empty pipe)
- L31 _public function_ `FImagePixelPipe(const TFunction<void(TUniquePtr<FImagePixelData>&&)>& InEndpoint)` — Define a new pipe with a single initial endpoint
- L41 _public prototype_ `void Push(TUniquePtr<FImagePixelData>&& InImagePixelData);` — Push the specified pixel data onto this pipe @param InImagePixelData         The data to push through this pipe
- L48 _public prototype_ `void AddEndpoint(TUniquePtr<FImageStreamEndpoint>&& InEndpoint);` — Add a new end point handler to this pipe. @param InEndpoint               The new endpoint to add. Potentially used on any thread.
- L55 _public prototype_ `void AddEndpoint(const TFunction<void(TUniquePtr<FImagePixelData>&& )>& InHandler);` — Add a new end point handler to this pipe as a functor. @param InHandler                A handler function implemented as an anonymous functor. Potentially called on any thread.
- L61 _public function_ `TArrayView<const TUniquePtr<FImageStreamEndpoint>> GetEndPoints() const` — Access this pipe's current set of end points. Warning: Not thread-safe - should only be called where no other modification to the end points can be happening.
- L67 _public member_ `std::atomic_bool bIsExpecting32BitPixelData = false;` — Boolean flag used to request 32-bit image pixel data, false by default.
- L72 _private member_ `FCriticalSection EndPointLock;` — A lock to protect the end points array
- L75 _private member_ `TArray<TUniquePtr<FImageStreamEndpoint>> EndPoints;` — array of endpoints to be called in order

#### struct `FImageStreamEndpoint`  
`struct FImageStreamEndpoint`  
_L83-100_
- desc: Stream end-point that receives a copy of image data from a thread
- L85 _public prototype_ `virtual ~FImageStreamEndpoint()= default;`
- L92 _public prototype_ `void PipeImage(TUniquePtr<FImagePixelData>&& InOwnedImage);` — Pipe the specified image data onto this end point @param InOwnedImage       Image data to pass through this end point.
- L99 _private function_ `virtual void OnImageReceived(TUniquePtr<FImagePixelData>&& InOwnedImage)` — Implemented in derived classes to handle image data being received

### `Source/Runtime/ImageWriteQueue/Public/ImageWriteTask.h` (Public)


#### class `IImageWriteTaskBase`  
`class IImageWriteTaskBase`  
_L27-45_
- desc: Interface that is implemented in order to be able to asynchronously write images to disk
- L34 _public prototype_ `virtual ~IImageWriteTaskBase() = default;` — Virtual destruction
- L39 _public prototype_ `virtual bool RunTask() = 0;`
- L44 _public prototype_ `virtual void OnAbandoned() = 0;`

#### class `FImageWriteTask`  
`class FImageWriteTask : public IImageWriteTaskBase`  
_L47-116_
- inherits: `IImageWriteTaskBase`
- L53 _public member_ `FString Filename;` — The filename to write to
- L56 _public member_ `EImageFormat Format;` — The desired image format to write out
- L59 _public member_ `int32 CompressionQuality;` — A compression quality setting specific to the desired image format
- L62 _public member_ `bool bOverwriteFile;` — True if this task is allowed to overwrite an existing file, false otherwise.
- L65 _public member_ `TFunction<void(bool)> OnCompleted;` — A function to invoke on the game thread when the task has completed
- L68 _public member_ `TUniquePtr<FImagePixelData> PixelData;` — The actual write operation.
- L71 _public member_ `TArray<FPixelPreProcessor> PixelPreProcessors;` — Array of preprocessors to apply serially to the pixel data when this task is executed.
- L73 _public function_ `FImageWriteTask() : Format(EImageFormat::BMP) , CompressionQuality((int32)EImageCompressionQuality::Default) , bOverwriteFile(true)`
- L81 _public prototype_ `virtual bool RunTask() override final;`
- L82 _public prototype_ `virtual void OnAbandoned() override final;`
- L84 _public prototype_ `void AddPreProcessorToSetAlphaOpaque();`
- L93 _private prototype_ `bool WriteToDisk();` — Run the task, attempting to write out the raw data using the currently specified parameters @return true on success, false on any failure
- L100 _private prototype_ `bool EnsureWritableFile();` — Ensures that the desired output filename is writable, deleting an existing file if bOverwriteFile is true @return True if the file is writable and the task can proceed, false otherwise
- L109 _private prototype_ `bool InitializeWrapper(IImageWrapper* InWrapper, EImageFormat WrapperFormat);` — Initialize the specified image wrapper with our raw data, ready for writing @param InWrapper      The wrapper to initialize with our data @param WrapperFormat  The desired image format to write out @return true on success, false on any failure
- L115 _private prototype_ `void PreProcess();` — Run over all the processors for the pixel data

#### struct `TAsyncAlphaWrite`  
`template<> struct TAsyncAlphaWrite<FColor>`  
_L127-142_
- desc: prefer AddPreProcessorToSetAlphaOpaque
- L129 _public member_ `uint8 Alpha;`
- L130 _public function_ `TAsyncAlphaWrite(uint8 InAlpha) : Alpha(InAlpha)`
- L132 _public function_ `void operator()(FImagePixelData* PixelData)`
- L147 _public member_ `FFloat16 Alpha;`
- L148 _public function_ `TAsyncAlphaWrite(float InAlpha) : Alpha(InAlpha)`
- L165 _public member_ `float Alpha;`

#### struct `TAsyncAlphaWrite`  
`template<> struct TAsyncAlphaWrite<FFloat16Color>`  
_L145-160_
- desc: prefer AddPreProcessorToSetAlphaOpaque
- L129 _public member_ `uint8 Alpha;`
- L130 _public function_ `TAsyncAlphaWrite(uint8 InAlpha) : Alpha(InAlpha)`
- L132 _public function_ `void operator()(FImagePixelData* PixelData)`
- L147 _public member_ `FFloat16 Alpha;`
- L148 _public function_ `TAsyncAlphaWrite(float InAlpha) : Alpha(InAlpha)`
- L165 _public member_ `float Alpha;`

#### struct `TAsyncAlphaWrite`  
`template<> struct TAsyncAlphaWrite<FLinearColor>`  
_L163-178_
- desc: prefer AddPreProcessorToSetAlphaOpaque
- L129 _public member_ `uint8 Alpha;`
- L130 _public function_ `TAsyncAlphaWrite(uint8 InAlpha) : Alpha(InAlpha)`
- L132 _public function_ `void operator()(FImagePixelData* PixelData)`
- L147 _public member_ `FFloat16 Alpha;`
- L148 _public function_ `TAsyncAlphaWrite(float InAlpha) : Alpha(InAlpha)`
- L165 _public member_ `float Alpha;`

#### struct `TAsyncAlphaInvert`  
`template<> struct TAsyncAlphaInvert<FColor>`  
_L189-201_
- L191 _public function_ `void operator()(FImagePixelData* PixelData)`

#### struct `TAsyncAlphaInvert`  
`template<> struct TAsyncAlphaInvert<FFloat16Color>`  
_L204-216_
- L191 _public function_ `void operator()(FImagePixelData* PixelData)`

#### struct `TAsyncAlphaInvert`  
`template<> struct TAsyncAlphaInvert<FLinearColor>`  
_L219-231_
- L191 _public function_ `void operator()(FImagePixelData* PixelData)`

#### Free symbols / members of external scopes

- L22 _typedef_ `typedef TUniqueFunction<void(FImagePixelData*)> FPixelPreProcessor;`

### `Source/Runtime/ImageWriteQueue/Public/ImageWriteTypes.h` (Public)


#### enum `EDesiredImageFormat`  
`enum class EDesiredImageFormat : uint8`  
_L10-16_
- reflection: `UENUM()`
- L12 _public enumerator_ `PNG`
- L13 _public enumerator_ `JPG`
- L14 _public enumerator_ `BMP`
- L15 _public enumerator_ `EXR`

#### Free symbols / members of external scopes

- L18 _prototype_ `EImageFormat ImageFormatFromDesired(EDesiredImageFormat In);`
