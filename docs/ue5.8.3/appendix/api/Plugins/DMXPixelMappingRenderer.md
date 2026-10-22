# Plugins / DMXPixelMappingRenderer

- module root: `Plugins/VirtualProduction/DMX/DMXPixelMapping/Source/DMXPixelMappingRenderer`
- headers: 14; symbols: 265
- symbol kinds: class=17, delegate=1, enum=3, enumerator=11, function=29, member=78, namespace=45, prototype=75, struct=5, typedef=1
- PrivateDependencyModuleNames: Core, CoreUObject, DMXRuntime, Engine, Projects, RHI, RenderCore, Slate, SlateCore, UMG
- PublicDependencyModuleNames: Core, CoreUObject

### `Plugins/VirtualProduction/DMX/DMXPixelMapping/Source/DMXPixelMappingRenderer/Internal/DMXPixelMappingTripleBufferedData.h` (Internal)


#### class `UE::DMX::Internal::TDMXPixelMappingTripleBufferedData`  
`template <class DataType> class TDMXPixelMappingTripleBufferedData`  
_L84-211_
- desc: A lock free paradigm for sharing data between threads. Called a triple buffer because at any point in time, there may be 3 buffers available: 1 owned by the producing thread, 1 owned by the consuming thread, and 1 waiting in an atomic variable. The third storage location enables transfer of ownership such that if you have a copy of the data, you own it without worry of contention. Producer thread: \code struct AnimXf { TArray<FTransform> Xf; TArray<FVector> Velocity; }; struct MyProducer { MyConsumer Consumer; // Owns the triple buffer. AnimXf* Buffer = nullptr; // This function is called repeatedly at some interval by the producing thread. void Produce() { // Get a new buffer if we need one. if(!Buffer) Buffer = Consumer.AnimXfTripleBuffer.ExchangeProducerBuffer(); // This class now has exclusive ownership of the memory pointed to by Buffer. Buffer->Xf = ...; Buffer->Velocity = ...; // Push the new values to the consumer, and get a new buffer for next time. Buffer = Consumer.AnimXfTripleBuffer.ExchangeProducerBuffer(); } }; \endcode Consumer thread: \code struct MyConsumer { // In this example the consumer owns the triple buffer, but that's // not a requirement. TDMXPixelMappingTripleBufferedData<AnimXf> AnimXfTripleBuffer; AnimXf* Buffer = nullptr; // This function is called repeatedly at some interval by the consuming thread. void Consume() { // Get a new view of the data, which can be null or old. Buffer = AnimXfTripleBuffer.ExchangeAnimXfConsumerBuffer(); // This class n
- L87 _public function_ `TDMXPixelMappingTripleBufferedData() : ProducerThreadBuffer(&Buffers[0]) , ConsumerThreadBuffer(&Buffers[1]) , Interchange(&Buffers[2]) , Counter(0) , LastId(0)`
- L126 _public function_ `DataType* ExchangeProducerBuffer()` — Get a new buffer for the producing thread to write to, while at the same time making the previous buffer available to the consumer. This function will manufacture new instances of \c DataType, if it needs to.  Thus, the returned pointer will never be null. The \c DataType value is returned by shared pointer to simplify ownership semantics, particularly with respect to cleanup.  It is important to not mistake that for exclusive ownership of the memory, and retain the return value of this function too long.  For instance: \code TDMXPixelMappingTripleBufferedData<int> IntBuffer; ... int* MyCopy = IntBuffer.ExchangeProducerBuffer(); (*MyCopy) = 1; // Ok IntBuffer.ExchangeProducerBuffer(); // Mem holding "1" now available to consumer thread. (*MyCopy) = 2; // Race condition! \endcode Instead, always reuse the same shared pointer, or dereference the returned shared pointer if you're not worried about copying the data. \code TDMXPixelMappingTripleBufferedData<int> IntBuffer; ... int* MyCopy = IntBuffer.ExchangeProducerBuffer(); (*MyCopy) = 1; // Ok MyCopy = IntBuffer.ExchangeProducerBuffer(); // Mem holding "1" now available to consumer thread. (*MyCopy) = 2; // Ok \endcode
- L164 _public function_ `DataType* ExchangeConsumerBuffer()` — Get an updated buffer for the consuming thread to read from. The returned pointer may be null if the producer thread hasn't done an update since the last time this function was called. The same capacity for a race condition exists with this functions return value as with \c ExchangeProducerBuffer(). \code TDMXPixelMappingTripleBufferedData<int> IntBuffer; ... int* MyCopy = IntBuffer.ExchangeConsumerBuffer(); int X = *MyCopy; // Ok IntBuffer.ExchangeConsumerBuffer(); // Mem holding X returned to producer thread. int Y = *MyCopy; // Race condition! \endcode Always refresh the same variable. \code TDMXPixelMappingTripleBufferedData<int> IntBuffer; ... int* MyCopy = IntBuffer.ExchangeConsumerBuffer(); int X = *MyCopy; // Ok MyCopy = IntBuffer.ExchangeConsumerBuffer(); // Mem holding X returned to producer thread. int Y = *MyCopy; // Ok \endcode
- L178 _private prototype_ `TDMXPixelMappingTripleBufferedData(TDMXPixelMappingTripleBufferedData&& Other) = delete;` — Non-copyable and non-movable, due to TAtomic member.
- L179 _private prototype_ `TDMXPixelMappingTripleBufferedData(const TDMXPixelMappingTripleBufferedData&) = delete;`
- L180 _private prototype_ `TDMXPixelMappingTripleBufferedData& operator=(TDMXPixelMappingTripleBufferedData&&) = delete;`
- L181 _private prototype_ `TDMXPixelMappingTripleBufferedData& operator=(const TDMXPixelMappingTripleBufferedData&) = delete;`
- L205 _private member_ `DataTypeWrapper Buffers[3] = { DataTypeWrapper(), DataTypeWrapper(), DataTypeWrapper() };`
- L206 _private member_ `DataTypeWrapper* ProducerThreadBuffer;`
- L207 _private member_ `DataTypeWrapper* ConsumerThreadBuffer;`
- L208 _private member_ `TAtomic<DataTypeWrapper*> Interchange;`
- L209 _private member_ `uint64 Counter;` — Only accessed by producer thread
- L210 _private member_ `uint64 LastId;` — Only accessed by consumer thread

#### struct `UE::DMX::Internal::TDMXPixelMappingTripleBufferedData::DataTypeWrapper`  
`struct DataTypeWrapper`  
_L183-203_
- L185 _public function_ `DataTypeWrapper() : Value(nullptr) , Id(0)`
- L189 _public prototype_ `DataTypeWrapper(const DataTypeWrapper&) = delete;`
- L190 _public function_ `DataTypeWrapper(DataTypeWrapper&& Other) : Value(MoveTemp(Other.Value)) , Id(MoveTemp(Other.Id))`
- L195 _public prototype_ `void operator=(const DataTypeWrapper& Other) = delete;`
- L201 _public member_ `TUniquePtr<DataType> Value;` — Depending on the use case, it may be useful to store DataType instances via shared pointer so that the thread that doesn't own the TripleBufferedData instance, can retain ownership of this memory after this class goes out of scope.
- L202 _public member_ `uint64 Id;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace DMX` (scope `UE`)
- L11 _namespace_ `namespace Internal` (scope `UE::DMX`)

### `Plugins/VirtualProduction/DMX/DMXPixelMapping/Source/DMXPixelMappingRenderer/Private/DMXPixelMappingApplyFilterMaterialProxy.h` (Private)


#### class `UE::DMXPixelMapping::Rendering::Preprocess::Private::FDMXPixelMappingPreprocessMaterialCanvas`  
`class FDMXPixelMappingPreprocessMaterialCanvas : public FGCObject`  
_L20-42_
- inherits: `FGCObject`
- desc: Canvas implementation for pixelmapping
- L25 _public prototype_ `FDMXPixelMappingPreprocessMaterialCanvas();` — Constructor
- L28 _public prototype_ `void DrawMaterialToRenderTarget(UTextureRenderTarget2D* TextureRenderTarget, UMaterialInterface* Material);` — Draws a material to a render target
- L32 _protected prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;`
- L33 _protected function_ `virtual FString GetReferencerName() const override`
- L41 _private member_ `TObjectPtr<UCanvas> Canvas;` — Canvas used to draw the material

#### class `UE::DMXPixelMapping::Rendering::Preprocess::Private::FDMXPixelMappingApplyFilterMaterialProxy`  
`class FDMXPixelMappingApplyFilterMaterialProxy : public IPreprocessApplyFilterMaterialProxy , public FGCObject`  
_L45-93_
- inherits: `IPreprocessApplyFilterMaterialProxy,FGCObject`
- desc: Proxy to filter the texture used in Pixel Mapping
- L50 _public prototype_ `FDMXPixelMappingApplyFilterMaterialProxy(EPixelFormat InFormat);`
- L53 _public prototype_ `virtual void Render(UTexture* InInputTexture, const UDMXPixelMappingPreprocessRenderer& InPreprocessRenderer) override;`
- L54 _public prototype_ `virtual UTexture* GetRenderedTexture() const override;`
- L59 _protected prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;`
- L60 _protected function_ `virtual FString GetReferencerName() const override`
- L68 _private prototype_ `bool CanRender() const;` — Returns true if rendering is needed
- L71 _private prototype_ `void UpdateRenderTargets(int32 NumDownsamplePasses, const TOptional<FVector2D>& OptionalOutputSize);` — Updates render targets
- L74 _private prototype_ `void RenderTextureToTarget(UTexture* Texture, UTextureRenderTarget2D* RenderTarget) const;` — Renders the Input Texture to the Output render target
- L77 _private member_ `EPixelFormat Format = PF_Unknown;` — The pixel format his proxy should use
- L80 _private member_ `TWeakObjectPtr<UTexture> WeakInputTexture;` — Weak ref to the input texture
- L83 _private member_ `TObjectPtr<UMaterialInstanceDynamic> MaterialInstanceDynamic;` — The dynamic material instance to be applied to the input texture
- L86 _private member_ `TArray<TObjectPtr<UTextureRenderTarget2D>> DownsampleRenderTargets;` — Downsample render targets
- L89 _private member_ `TObjectPtr<UTextureRenderTarget2D> OutputRenderTarget;` — The target to which the output is rendered. Either the last downscale render target or the scale render target
- L92 _private member_ `FDMXPixelMappingPreprocessMaterialCanvas DrawMaterialCanvas;` — Canvas used to draw materials

#### Free symbols / members of external scopes

- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace DMXPixelMapping` (scope `UE`)
- L17 _namespace_ `namespace Rendering` (scope `UE::DMXPixelMapping`)
- L17 _namespace_ `namespace Preprocess` (scope `UE::DMXPixelMapping::Rendering`)
- L17 _namespace_ `namespace Private` (scope `UE::DMXPixelMapping::Rendering::Preprocess`)

### `Plugins/VirtualProduction/DMX/DMXPixelMapping/Source/DMXPixelMappingRenderer/Private/DMXPixelMappingRenderInputMaterialProxy.h` (Private)


#### class `UE::DMXPixelMapping::Rendering::Preprocess::Private::FDMXPixelMappingRenderInputMaterialProxy`  
`class FDMXPixelMappingRenderInputMaterialProxy : public IPreprocessRenderInputProxy , public FGCObject`  
_L18-52_
- inherits: `IPreprocessRenderInputProxy,FGCObject`
- desc: Proxy responsible for the input material
- L23 _public prototype_ `FDMXPixelMappingRenderInputMaterialProxy(UMaterialInterface* InMaterial, const FVector2D& InInputSize, EPixelFormat Format);`
- L26 _public prototype_ `virtual void Render() override;`
- L27 _public prototype_ `virtual UTexture* GetRenderedTexture() const override;`
- L28 _public prototype_ `virtual FVector2D GetSize2D() const override;`
- L33 _protected prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;`
- L34 _protected function_ `virtual FString GetReferencerName() const override`
- L42 _private member_ `TSharedPtr<FWidgetRenderer> MaterialRenderer;` — Material renderer
- L45 _private member_ `TSharedPtr<FSlateMaterialBrush> UIMaterialBrush;` — Brush for Material widget renderer
- L48 _private member_ `TWeakObjectPtr<UMaterialInterface> WeakMaterial;` — The Input object
- L51 _private member_ `TObjectPtr<UTextureRenderTarget2D> IntermediateRenderTarget;` — Intermediate render target for materials and user widgets

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace DMXPixelMapping` (scope `UE`)
- L15 _namespace_ `namespace Rendering` (scope `UE::DMXPixelMapping`)
- L15 _namespace_ `namespace Preprocess` (scope `UE::DMXPixelMapping::Rendering`)
- L15 _namespace_ `namespace Private` (scope `UE::DMXPixelMapping::Rendering::Preprocess`)

### `Plugins/VirtualProduction/DMX/DMXPixelMapping/Source/DMXPixelMappingRenderer/Private/DMXPixelMappingRenderInputTextureProxy.h` (Private)


#### class `UE::DMXPixelMapping::Rendering::Preprocess::Private::FDMXPixelMappingRenderInputTextureProxy`  
`class FDMXPixelMappingRenderInputTextureProxy : public IPreprocessRenderInputProxy`  
_L16-31_
- inherits: `IPreprocessRenderInputProxy`
- desc: Proxy responsible for the input texture
- L20 _public prototype_ `FDMXPixelMappingRenderInputTextureProxy(UTexture* InTexture);`
- L23 _public prototype_ `virtual void Render() override;`
- L24 _public prototype_ `virtual UTexture* GetRenderedTexture() const override;`
- L25 _public prototype_ `virtual FVector2D GetSize2D() const override;`
- L30 _private member_ `TWeakObjectPtr<UTexture> WeakInputTexture;` — The Input object

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace DMXPixelMapping` (scope `UE`)
- L13 _namespace_ `namespace Rendering` (scope `UE::DMXPixelMapping`)
- L13 _namespace_ `namespace Preprocess` (scope `UE::DMXPixelMapping::Rendering`)
- L13 _namespace_ `namespace Private` (scope `UE::DMXPixelMapping::Rendering::Preprocess`)

### `Plugins/VirtualProduction/DMX/DMXPixelMapping/Source/DMXPixelMappingRenderer/Private/DMXPixelMappingRenderInputUserWidgetProxy.h` (Private)


#### class `UE::DMXPixelMapping::Rendering::Preprocess::Private::FDMXPixelMappingRenderInputUserWidgetProxy`  
`class FDMXPixelMappingRenderInputUserWidgetProxy : public IPreprocessRenderInputProxy , public FGCObject`  
_L17-48_
- inherits: `IPreprocessRenderInputProxy,FGCObject`
- desc: Proxy responsible for the input user widget
- L22 _public prototype_ `FDMXPixelMappingRenderInputUserWidgetProxy(UUserWidget* InUserWidget, const FVector2D& InInputSize, EPixelFormat InFormat);`
- L25 _public prototype_ `virtual void Render() override;`
- L26 _public prototype_ `virtual UTexture* GetRenderedTexture() const override;`
- L27 _public prototype_ `virtual FVector2D GetSize2D() const override;`
- L32 _protected prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;`
- L33 _protected function_ `virtual FString GetReferencerName() const override`
- L41 _private member_ `TSharedPtr<FWidgetRenderer> UMGRenderer;` — UMG widget renderer
- L44 _private member_ `TWeakObjectPtr<UUserWidget> WeakUserWidget;` — The Input object
- L47 _private member_ `TObjectPtr<UTextureRenderTarget2D> IntermediateRenderTarget;` — Intermediate render target for materials and user widgets

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace DMXPixelMapping` (scope `UE`)
- L14 _namespace_ `namespace Rendering` (scope `UE::DMXPixelMapping`)
- L14 _namespace_ `namespace Preprocess` (scope `UE::DMXPixelMapping::Rendering`)
- L14 _namespace_ `namespace Private` (scope `UE::DMXPixelMapping::Rendering::Preprocess`)

### `Plugins/VirtualProduction/DMX/DMXPixelMapping/Source/DMXPixelMappingRenderer/Private/DMXPixelMappingRenderPixelMapProxy.h` (Private)


#### class `UE::DMXPixelMapping::Rendering::Private::FDMXPixelMappingRenderPixelMapProxy`  
`class FDMXPixelMappingRenderPixelMapProxy : public IRenderPixelMapProxy , public FGCObject`  
_L16-49_
- inherits: `IRenderPixelMapProxy,FGCObject`
- desc: Interface for the object responsible to render the input texture/material/umg widget.
- L30 _public prototype_ `virtual void Render( UTexture* InInputTexture, UTextureRenderTarget2D* InRenderTarget, const TArray<TSharedRef<FPixelMapRenderElement>>& InElements, float InBrightness ) override;` — Pixelmapping specific, downsample and draw input texture to destination texture. @param InInputTexture				The input texture to pixel map @param InRenderTarget				The render target that is pixel mapped to @param InElements					Elements to be rendered @param InBrightness					Global brightness @param InCallback					Callback for reading  the pixels from GPU to CPU
- L39 _protected prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;`
- L40 _protected function_ `virtual FString GetReferencerName() const override`
- L45 _private member_ `TObjectPtr<UTexture> InputTexture;` — Strong ref to the current input texture
- L48 _private member_ `TObjectPtr<UTextureRenderTarget2D> RenderTarget;` — Strong ref to the current render target

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace DMXPixelMapping` (scope `UE`)
- L10 _namespace_ `namespace Rendering` (scope `UE::DMXPixelMapping`)
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace DMXPixelMapping` (scope `UE`)
- L13 _namespace_ `namespace Rendering` (scope `UE::DMXPixelMapping`)
- L13 _namespace_ `namespace Private` (scope `UE::DMXPixelMapping::Rendering`)

### `Plugins/VirtualProduction/DMX/DMXPixelMapping/Source/DMXPixelMappingRenderer/Private/DMXPixelMappingRenderer.h` (Private)


#### class `FDMXPixelMappingRenderer`  
`class FDMXPixelMappingRenderer : public IDMXPixelMappingRenderer`  
_L17-55_
- inherits: `IDMXPixelMappingRenderer`
- desc: DEPRECATED 5.2
- L22 _public prototype_ `FDMXPixelMappingRenderer();` — Default constructor
- L25 _public prototype_ `virtual void DownsampleRender( const FTextureResource* InputTexture, const FTextureResource* DstTexture, const FTextureRenderTargetResource* DstTextureTargetResource, const TArray<FDMXPixelMappingDownsamplePixelParamsV2>& InDownsamplePixelPass, DownsampleReadCallback InCallback ) const override;`
- L33 _public prototype_ `virtual void RenderMaterial(UTextureRenderTarget2D* InRenderTarget, UMaterialInterface* InMaterialInterface) const override;`
- L34 _public prototype_ `virtual void RenderWidget(UTextureRenderTarget2D* InRenderTarget, UUserWidget* InUserWidget) const override;`
- L36 _public prototype_ `virtual void RenderTextureToRectangle(const FTextureResource* InTextureResource, const FTextureRHIRef InRenderTargetTexture, FVector2D InSize, bool bSRGBSource) const override;`
- L39 _public prototype_ `virtual void RenderPreview(const FTextureResource* TextureResource, const FTextureResource* DownsampleResource, TArray<FDMXPixelMappingDownsamplePixelPreviewParam>&& InPixelPreviewParamSet) const override;`
- L45 _private member_ `TSharedPtr<FSlateMaterialBrush> UIMaterialBrush;` — Brush for Material widget renderer
- L48 _private member_ `TSharedPtr<FWidgetRenderer> MaterialWidgetRenderer;` — Material widget renderer
- L51 _private member_ `TSharedPtr<FWidgetRenderer> UMGRenderer;` — UMG widget renderer
- L54 _private member_ `IRendererModule* RendererModule;` — The public interface of the renderer module.

### `Plugins/VirtualProduction/DMX/DMXPixelMapping/Source/DMXPixelMappingRenderer/Private/DMXPixelMappingRendererCommon.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogDMXPixelMappingRenderer, All, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogDMXPixelMappingRenderer, All, All);`

### `Plugins/VirtualProduction/DMX/DMXPixelMapping/Source/DMXPixelMappingRenderer/Private/DMXPixelMappingRendererModule.h` (Private)


#### class `FDMXPixelMappingRendererModule`  
`class FDMXPixelMappingRendererModule : public IDMXPixelMappingRendererModule`  
_L11-26_
- inherits: `IDMXPixelMappingRendererModule`
- L17 _public prototype_ `virtual void StartupModule() override;`
- L23 _public prototype_ `virtual TSharedPtr<IDMXPixelMappingRenderer> CreateRenderer() const override;` — `UE_DEPRECATED(5.3, "IDMXPixelMappingRenderer was replaced with UDMXPixelMappigPixelMapRenderer")`

### `Plugins/VirtualProduction/DMX/DMXPixelMapping/Source/DMXPixelMappingRenderer/Public/DMXPixelMappingPixelMapRenderer.h` (Public)


#### class `UE::DMXPixelMapping::Rendering::Private::IRenderPixelMapProxy`  
`class IRenderPixelMapProxy : public TSharedFromThis<IRenderPixelMapProxy>`  
_L23-43_
- inherits: `TSharedFromThis<IRenderPixelMapProxy>`
- desc: Interface for the object responsible to render the pixel map
- L27 _public function_ `virtual ~IRenderPixelMapProxy()`
- L37 _public prototype_ `virtual void Render( UTexture* InInputTexture, UTextureRenderTarget2D* InRenderTarget, const TArray<TSharedRef<UE::DMXPixelMapping::Rendering::FPixelMapRenderElement>>& InElements, float InBrightness ) = 0;` — Pixelmapping specific, downsample and draw input texture to destination texture. @param InputTexture					The input texture to render @param RenderTarget					The render target to render to @param InElements						The elements that are pixel mapped @param Brightness						Global brightness of the rendered colors

#### class `UDMXPixelMappingPixelMapRenderer`  
`class UDMXPixelMappingPixelMapRenderer : public UObject`  
_L49-78_
- reflection: `UCLASS()`
- inherits: `UObject`
- desc: Maps pixel map render elements to pixels
- L55 _public prototype_ `UDMXPixelMappingPixelMapRenderer();`
- L58 _public prototype_ `void SetElements(const TArray<TSharedRef<UE::DMXPixelMapping::Rendering::FPixelMapRenderElement>>& InElements, EPixelFormat InFormat);` — Sets the elements to render
- L62 _public prototype_ `void SetElements(const TArray<TSharedRef<UE::DMXPixelMapping::Rendering::FPixelMapRenderElement>>& InElements);` — `UE_DEPRECATED(5.4, "It is now required to specify a pixel format, see related overload.")` — DEPRECATED 5.4 - Sets the elements to render
- L65 _public prototype_ `void Render(UTexture* InputTexture, float Brightness);` — Renders the current elements
- L68 _private member_ `static const FIntPoint MaxPixelMapSize;`
- L71 _private member_ `TObjectPtr<UTextureRenderTarget2D> PixelMapRenderTarget;` — `UPROPERTY(Transient, DuplicateTransient)`
- L74 _private member_ `TArray<TSharedRef<UE::DMXPixelMapping::Rendering::FPixelMapRenderElement>> RenderElements;` — The elements to render
- L77 _private member_ `TSharedPtr<UE::DMXPixelMapping::Rendering::Private::IRenderPixelMapProxy> RendererPixelMapProxy;` — Proxy that carries out the actual rendering

#### Free symbols / members of external scopes

- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace DMXPixelMapping` (scope `UE`)
- L17 _namespace_ `namespace Rendering` (scope `UE::DMXPixelMapping`)
- L20 _namespace_ `namespace UE`
- L20 _namespace_ `namespace DMXPixelMapping` (scope `UE`)
- L20 _namespace_ `namespace Rendering` (scope `UE::DMXPixelMapping`)
- L20 _namespace_ `namespace Private` (scope `UE::DMXPixelMapping::Rendering`)

### `Plugins/VirtualProduction/DMX/DMXPixelMapping/Source/DMXPixelMappingRenderer/Public/DMXPixelMappingPreprocessRenderer.h` (Public)


#### enum `EDMXPixelMappingRenderingPreprocessorSizeMode`  
`enum class EDMXPixelMappingRenderingPreprocessorSizeMode : uint8`  
_L18-23_
- reflection: `UENUM(BlueprintType)`
- L20 _public enumerator_ `SameAsInput`
- L21 _public enumerator_ `Downsampled`
- L22 _public enumerator_ `CustomSize`

#### class `UE::DMXPixelMapping::Rendering::Preprocess::Private::IPreprocessRenderInputProxy`  
`class IPreprocessRenderInputProxy : public TSharedFromThis<IPreprocessRenderInputProxy>`  
_L28-42_
- inherits: `TSharedFromThis<IPreprocessRenderInputProxy>`
- desc: Interface for the object responsible to render the input texture/material/umg widget.
- L32 _public function_ `virtual ~IPreprocessRenderInputProxy()`
- L35 _public prototype_ `virtual void Render() = 0;` — Renders the input texture, optionally using a Filter material
- L38 _public prototype_ `virtual UTexture* GetRenderedTexture() const = 0;` — Returns the currently rendered texture, or nullptr if no texture was rendered yet
- L41 _public prototype_ `virtual FVector2D GetSize2D() const = 0;` — Returns the size of the input object

#### class `UE::DMXPixelMapping::Rendering::Preprocess::Private::IPreprocessApplyFilterMaterialProxy`  
`class IPreprocessApplyFilterMaterialProxy : public TSharedFromThis<IPreprocessApplyFilterMaterialProxy>`  
_L45-56_
- inherits: `TSharedFromThis<IPreprocessApplyFilterMaterialProxy>`
- desc: Interface for the object responsible to apply the material to the input texture.
- L49 _public function_ `virtual ~IPreprocessApplyFilterMaterialProxy()`
- L52 _public prototype_ `virtual void Render(UTexture* InInputTexture, const class UDMXPixelMappingPreprocessRenderer& InPreprocessRenderer) = 0;` — Renders the input texture, optionally using a Filter material
- L55 _public prototype_ `virtual UTexture* GetRenderedTexture() const = 0;` — Returns the preprocessed texture

#### class `UDMXPixelMappingPreprocessRenderer`  
`class UDMXPixelMappingPreprocessRenderer : public UObject`  
_L61-185_
- reflection: `UCLASS(BlueprintType)`
- inherits: `UObject`
- desc: Renders the texture that is used to pixel map
- L68 _public prototype_ `void SetInputTexture(UTexture* InTexture, EPixelFormat InFormat);` — Sets the input texture that is used when rendering
- L71 _public prototype_ `void SetInputMaterial(UMaterialInterface* InMaterial, EPixelFormat InFormat);` — Sets the input texture that is used when rendering
- L74 _public prototype_ `void SetInputUserWidget(UUserWidget* InUserWidget, EPixelFormat InFormat);` — Sets the input texture that is used when rendering
- L78 _public prototype_ `void SetInputTexture(UTexture* InTexture);` — `UE_DEPRECATED(5.4, "It is now required to specify a pixel format, see related overload.")` — DEPRECATED 5.4 - Sets the input texture that is used when rendering
- L82 _public prototype_ `void SetInputMaterial(UMaterialInterface* InMaterial);` — `UE_DEPRECATED(5.4, "It is now required to specify a pixel format, see related overload.")` — DEPRECATED 5.4 - Sets the input texture that is used when rendering
- L86 _public prototype_ `void SetInputUserWidget(UUserWidget* InUserWidget);` — `UE_DEPRECATED(5.4, "It is now required to specify a pixel format, see related overload.")` — DEPRECATED 5.4 - Sets the input texture that is used when rendering
- L89 _public prototype_ `void ClearInput();` — Clears input
- L92 _public prototype_ `void Render();` — Renders the current input
- L95 _public prototype_ `UTexture* GetRenderedTexture() const;` — Returns the rendered input texture, or nullptr if no texture was rendered yet
- L98 _public prototype_ `FVector2D GetResultingSize2D() const;` — Returns the resulting size of preprocessing, even if rendering did not occur yet
- L101 _public function_ `const TObjectPtr<UMaterialInstanceDynamic>& GetFilterMID() const` — Returns the Filter material, or nullptr if no Filter material is set
- L104 _public function_ `bool ShouldApplyFilterMaterialEachDownsamplePass() const` — Returns true, if the Filter material should be applied each downsample pass
- L107 _public function_ `int32 GetNumDownsamplePasses() const` — Returns the number of time the texture should be downsampled by factor 2
- L110 _public prototype_ `TOptional<FVector2D> GetDesiredOutputSize2D() const;` — Returns the desired output size, or an unset optional vector 2D if the resulting size should be used
- L113 _public function_ `float GetBlurDistance() const` — Returns the blur distance parameter
- L116 _public function_ `FName GetTextureParameterName() const` — Returns the texture parameter name
- L119 _public function_ `FName GetBlurDistanceParameterName() const` — Returns the blur distance parameter name
- L122 _public function_ `static FName GetOutputSizeModeMemberNameChecked()` — Property name getters
- L123 _public function_ `static FName GetCustomOutputSizeMemberNameChecked()`
- L124 _public function_ `static FName GetFilterMaterialMemberNameChecked()`
- L125 _public function_ `static FName GetBlurDistanceMemberNameChecked()`
- L129 _protected prototype_ `virtual void PostLoad() override;`
- L131 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L138 _private member_ `FVector2D InputSize{ 1024.f, 1024.f };` — `UPROPERTY(EditAnywhere, Category = "Render Settings", Meta = (EditCondition = "bShowInputSize", EditConditionHides, HideEditConditionToggle, ClampMin = "1", ClampMax = "8192", UIMin = "1", UIMax = "4096", AllowPrivateAccess = true))` — Size of the input texture (Material and User Widget only)
- L142 _private member_ `int32 NumDownSamplePasses = 0;` — `UPROPERTY(EditAnywhere, Category = "Filtering", Meta = (ClampMin = "0", ClampMax = "256", UIMin = "0", UIMax = "16", AllowPrivateAccess = true))` — Number of times the pixelmapping input is downsampled
- L146 _private member_ `EDMXPixelMappingRenderingPreprocessorSizeMode OutputSizeMode = EDMXPixelMappingRenderingPreprocessorSizeMode::SameAsInput;` — `UPROPERTY(EditAnywhere, Category = "Filtering", Meta = (AllowPrivateAccess = true))` — Defines how the texture is resized after filtering
- L150 _private member_ `FIntPoint CustomOutputSize { 256, 256 };` — `UPROPERTY(EditAnywhere, Category = "Filtering", Meta = (DisplayName = "Custom Size", ClampMin = "1", ClampMax = 2048, UIMin = 1, UIMax = 2048, EditCondition = "OutputSizeMode == EDMXPixelMappingRenderingPreprocessorSizeMode::CustomSize", EditConditionHides, AllowPrivateAccess = true))` — Size of the rendered texture
- L154 _private member_ `TObjectPtr<UMaterialInterface> FilterMaterial;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Filtering", Meta = (AllowPrivateAccess = true))` — Filter material applied to the rendered input
- L158 _private member_ `TObjectPtr<UMaterialInstanceDynamic> FilterMID;` — `UPROPERTY(Transient)` — Actual material instance dynamic applied to the rendered input
- L162 _private member_ `bool bApplyFilterMaterialEachDownsamplePass = true;` — `UPROPERTY(EditAnywhere, Category = "Filtering", Meta = (AllowPrivateAccess = true, DisplayName = "Apply Material each pass"))` — If true, the filter material is applied each downsample pass, otherwise only once after the last pass
- L166 _private member_ `float BlurDistance = .02f;` — `UPROPERTY(EditAnywhere, Category = "Filtering", Meta = (UIMin = "0", UIMax = "1", SliderExponent = 2.0, AllowPrivateAccess = true))` — Blur distance applied, only applicable if the filter matierial has a "BlurDistance" parameter
- L170 _private member_ `FName TextureParameterName = "Te` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Category = "Filtering", Meta = (AllowPrivateAccess = true))` — The texture parameter name in the Filter Material
- L174 _private member_ `FName BlurDistanceParamterName = "Bl` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Category = "Filtering", Meta = (AllowPrivateAccess = true))` — The blur distance parameter name in the Filter Material
- L178 _private member_ `bool bShowInputSize = false;` — `UPROPERTY(Transient)` — If true, shows the input size property
- L181 _private member_ `TSharedPtr<UE::DMXPixelMapping::Rendering::Preprocess::Private::IPreprocessRenderInputProxy> RenderInputProxy;` — Proxy to render the input
- L184 _private member_ `TSharedPtr<UE::DMXPixelMapping::Rendering::Preprocess::Private::IPreprocessApplyFilterMaterialProxy> ApplyMaterialProxy;` — Proxy to render the input

#### Free symbols / members of external scopes

- L25 _namespace_ `namespace UE`
- L25 _namespace_ `namespace DMXPixelMapping` (scope `UE`)
- L25 _namespace_ `namespace Rendering` (scope `UE::DMXPixelMapping`)
- L25 _namespace_ `namespace Preprocess` (scope `UE::DMXPixelMapping::Rendering`)
- L25 _namespace_ `namespace Private` (scope `UE::DMXPixelMapping::Rendering::Preprocess`)

### `Plugins/VirtualProduction/DMX/DMXPixelMapping/Source/DMXPixelMappingRenderer/Public/DMXPixelMappingRenderElement.h` (Public)


#### enum `EDMXPixelBlendingQuality`  
`enum class EDMXPixelBlendingQuality : uint8`  
_L15-28_
- reflection: `UENUM()`
- desc: Enum that defines the quality of how pixels are rendered
- L18 _public enumerator_ `Low` — 1 sample
- L21 _public enumerator_ `Medium` — 5 samples ( 2 x 2 with center)
- L24 _public enumerator_ `High` — 9 samples ( 3 x 3 )
- L27 _public enumerator_ `MAX UMETA(Hidden)` — Max, for shaders only

#### struct `UE::DMXPixelMapping::Rendering::FPixelMapRenderElementParameters`  
`struct FPixelMapRenderElementParameters`  
_L32-57_
- L35 _public member_ `FVector2D UV;` — Position in texels of the center of the quad's UV's
- L38 _public member_ `FVector2D UVSize;` — Size in texels of UV. May match UVSize
- L41 _public member_ `FVector2D UVTopLeftRotated;` — Position in texels of the top left corner of the quad's UV's, in rotated space
- L44 _public member_ `FVector2D UVTopRightRotated;` — Position in texels of the top right corner of the quad's UV's, in rotate space
- L47 _public member_ `double Rotation;` — Rotation in degrees. Useful to paint these elements in the preview view.
- L50 _public member_ `FVector2D UVCellSize_DEPRECATED;` — DERPECATED 5.4 - Size in texels of the quad's total UV space
- L53 _public member_ `EDMXPixelBlendingQuality CellBlendingQuality;` — The quality of color samples in the pixel shader(number of samples)
- L56 _public member_ `bool bStaticCalculateUV = true;` — Calculates the UV point to sample purely on the UV position/size. Works best for renderers which represent a single pixel

#### class `UE::DMXPixelMapping::Rendering::FPixelMapRenderElement`  
`class FPixelMapRenderElement : public TSharedFromThis<FPixelMapRenderElement>`  
_L60-97_
- inherits: `TSharedFromThis<FPixelMapRenderElement>`
- desc: An element rendered by the pixel map renderer
- L64 _public function_ `FPixelMapRenderElement(FPixelMapRenderElementParameters InParameters) : Parameters(InParameters)`
- L68 _public function_ `virtual ~FPixelMapRenderElement()`
- L71 _public prototype_ `void SetParameters(FPixelMapRenderElementParameters InParameters);` — Sets the parameters, thread-safe
- L74 _public prototype_ `FPixelMapRenderElementParameters GetParameters() const;` — Gets the parameters, thread-safe
- L77 _public prototype_ `void SetColor(const FLinearColor& Color);` — Sets the pixel color, thread safe. This is called from the renderer to set the rendered color.
- L80 _public prototype_ `FLinearColor GetColor() const;` — Gets the pixel color, thread safe
- L84 _private member_ `mutable FLinearColor ColorGameThread;` — The current color, readable from the game thread
- L87 _private member_ `mutable UE::DMX::Internal::TDMXPixelMappingTripleBufferedData<FLinearColor> ColorTipleBuffer;` — Triple buffered color data, useful to copy data to game thread without locking.
- L90 _private member_ `FLinearColor* ProducerColorPtr = nullptr;` — Pointer to the color data that is currently safe to write for the producer
- L93 _private member_ `FPixelMapRenderElementParameters Parameters;` — The current parameters
- L96 _private member_ `mutable FCriticalSection AccessParametersMutex;` — Mutex acccess to parameters

#### Free symbols / members of external scopes

- L30 _namespace_ `namespace UE`
- L30 _namespace_ `namespace DMXPixelMapping` (scope `UE`)
- L30 _namespace_ `namespace Rendering` (scope `UE::DMXPixelMapping`)

### `Plugins/VirtualProduction/DMX/DMXPixelMapping/Source/DMXPixelMappingRenderer/Public/IDMXPixelMappingRenderer.h` (Public)


#### enum `EDMXPixelShaderBlendingQuality`  
`enum class EDMXPixelShaderBlendingQuality : uint8`  
_L24-31_
- reflection: `UE_DEPRECATED(5.3, "Please use UDMXPixelMappingPixelMapRenderer instead.")`
- desc: Used in shader permutation for determining number of samples to use in texture blending. If adding to this you must also adjust the public facing option: 'EPixelBlendingQuality' under the runtime module's DMXPixelMappingOutputComponent.h
- L26 _public enumerator_ `Low`
- L27 _public enumerator_ `Medium`
- L28 _public enumerator_ `High`
- L30 _public enumerator_ `MAX`

#### struct `FDMXPixelMappingDownsamplePixelPreviewParam`  
`struct FDMXPixelMappingDownsamplePixelPreviewParam`  
_L39-49_
- reflection: `UE_DEPRECATED(5.3, "Deprecated in favor of FPixelMapRenderElement.")`
- desc: Downsample pixel preview rendering params. Using for pixel rendering setting in preview
- L42 _public member_ `FVector2D ScreenPixelPosition;` — Position in screen pixels of the top left corner of the quad
- L45 _public member_ `FVector2D ScreenPixelSize;` — Size in screen pixels of the quad
- L48 _public member_ `FIntPoint DownsamplePosition;` — Downsample pixel position in screen pixels of the quad

#### struct `FDMXPixelMappingDownsamplePixelParam`  
`struct FDMXPixelMappingDownsamplePixelParam`  
_L56-81_
- reflection: `UE_DEPRECATED(5.2, "Deprecated in favor of FDMXPixelMappingDownsamplePixelParamsV2. To apply color spaces, all color values are now computed at all times.")`
- desc: Downsample pixel rendering params Using for pixel rendering in downsample rendering pipeline
- L59 _public member_ `FVector4 PixelFactor;` — RGBA pixel multiplication
- L62 _public member_ `FIntVector4 InvertPixel;` — RGBA pixel flag for inversion
- L65 _public member_ `FIntPoint Position;` — Position in screen pixels of the top left corner of the quad
- L68 _public member_ `FVector2D UV;` — Position in texels of the top left corner of the quad's UV's
- L71 _public member_ `FVector2D UVSize;` — Size in texels of the quad's total UV space
- L74 _public member_ `FVector2D UVCellSize;` — Size in texels of UV.May match UVSize
- L77 _public member_ `EDMXPixelBlendingQuality CellBlendingQuality;` — The quality of color samples in the pixel shader(number of samples)
- L80 _public member_ `bool bStaticCalculateUV;` — Calculates the UV point to sample purely on the UV position/size. Works best for renderers which represent a single pixel

#### struct `FDMXPixelMappingDownsamplePixelParamsV2`  
`struct FDMXPixelMappingDownsamplePixelParamsV2`  
_L84-103_
- reflection: `UE_DEPRECATED(5.3, "Deprecated in favor of FPixelMapRenderElement.")`
- L87 _public member_ `FIntPoint Position;` — Position in screen pixels of the top left corner of the quad
- L90 _public member_ `FVector2D UV;` — Position in texels of the top left corner of the quad's UV's
- L93 _public member_ `FVector2D UVSize;` — Size in texels of the quad's total UV space
- L96 _public member_ `FVector2D UVCellSize;` — Size in texels of UV.May match UVSize
- L99 _public member_ `EDMXPixelBlendingQuality CellBlendingQuality;` — The quality of color samples in the pixel shader(number of samples)
- L102 _public member_ `bool bStaticCalculateUV;` — Calculates the UV point to sample purely on the UV position/size. Works best for renderers which represent a single pixel

#### class `IDMXPixelMappingRenderer`  
`class IDMXPixelMappingRenderer : public TSharedFromThis<IDMXPixelMappingRenderer>`  
_L110-187_
- inherits: `TSharedFromThis<IDMXPixelMappingRenderer>`
- desc: The public interface of the Pixel Mapping renderer instance interface.
- L114 _public typedef_ `using DownsampleReadCallback = TFunction<void(TArray<FLinearColor>&&, FIntRect)>;`
- L118 _public prototype_ `virtual ~IDMXPixelMappingRenderer() = default;` — Virtual destructor
- L129 _public prototype_ `virtual void DownsampleRender( const FTextureResource* InputTexture, const FTextureResource* DstTexture, const FTextureRenderTargetResource* DstTextureTargetResource, const TArray<FDMXPixelMappingDownsamplePixelParamsV2>& InDownsamplePixelPass, DownsampleReadCallback InCallback ) const = 0;` — `UE_DEPRECATED(5.3, "Please use UDMXDMXPixelMappingPixelMapRenderer instead.")` — Pixelmapping specific, downsample and draw input texture to destination texture. @param InputTexture					Rendering resource of input texture @param DstTexture					Rendering resource of RenderTarget texture @param InDownsamplePixelPass			Pixels rendering params @param InCallback					Callback for reading  the pixels from GPU to CPU
- L144 _public prototype_ `virtual void RenderMaterial(UTextureRenderTarget2D* InRenderTarget, UMaterialInterface* InMaterialInterface) const = 0;` — `UE_DEPRECATED(5.3, "Please use FWidgetRenderer::DrawWidget or similar engine methods instead.")` — Render material into the RenderTarget2D @param InRenderTarget				2D render target texture resource @param InMaterialInterface			Material to use
- L153 _public prototype_ `virtual void RenderWidget(UTextureRenderTarget2D* InRenderTarget, UUserWidget* InUserWidget) const = 0;` — `UE_DEPRECATED(5.3, "Please use FWidgetRenderer::DrawWidget or similar engine methods instead.")` — Render material into the RenderTarget2D @param InRenderTarget				2D render target texture resource @param InUserWidget					UMG widget to use
- L164 _public prototype_ `virtual void RenderTextureToRectangle(const FTextureResource* InTextureResource, const FTextureRHIRef InRenderTargetTexture, FVector2D InSize, bool bSRGBSource) const = 0;` — `UE_DEPRECATED(5.3, "Removed without replacement. Please use core engine methods to draw texture to rectangle.")` — Rendering input texture to render target @param InTextureResource				Input texture resource @param InRenderTargetTexture			RenderTarget @param InSize						Rendering size @param bSRGBSource					If the source texture is sRGB
- L175 _public prototype_ `virtual void RenderPreview(const FTextureResource* TextureResource, const FTextureResource* DownsampleResource, TArray<FDMXPixelMappingDownsamplePixelPreviewParam>&& InPixelPreviewParamSet) const = 0;` — `UE_DEPRECATED(5.3, "Pixel mapping no longer has a dedicated preview renderer. Instead draw pixel map elements to a view port (see FDMXPixelMappingPreviewViewportClient.")` — Render preview with one or multiple downsampled textures @param TextureResource				Rendering resource of RenderTarget texture @param DownsampleResource			Rendering resource of RenderTarget texture @param InPixelPreviewParamSet		Pixels rendering params
- L182 _public function_ `void SetBrightness(const float InBrightness)` — `UE_DEPRECATED(5.3, "IDMXPixelMappingRenderer and all its members are deprecated.")` — Sets the brigthness of the renderer
- L186 _protected member_ `float Brightness = 1.0f;` — Brightness multiplier for the renderer

### `Plugins/VirtualProduction/DMX/DMXPixelMapping/Source/DMXPixelMappingRenderer/Public/IDMXPixelMappingRendererModule.h` (Public)


#### class `IDMXPixelMappingRendererModule`  
`class IDMXPixelMappingRendererModule : public IModuleInterface`  
_L16-58_
- inherits: `IModuleInterface`
- desc: Public module interface for the DMX Renderer module
- L20 _public member_ `static constexpr auto ModuleName = TEXT("DMX`
- L25 _public function_ `virtual ~IDMXPixelMappingRendererModule()` — Virtual destructor
- L34 _public function_ `static IDMXPixelMappingRendererModule& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L44 _public function_ `static bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use
- L56 _public prototype_ `virtual TSharedPtr<IDMXPixelMappingRenderer> CreateRenderer() const = 0;` — Get Renderer instance There is no limit to the amount of creation of renderers @return IDMXPixelMappingRenderer instance.
