# Runtime / SlateBaseRenderer

- module root: `Source/Runtime/SlateBaseRenderer`
- headers: 4; symbols: 27
- symbol kinds: class=5, function=6, macro=3, member=3, prototype=10
- PrivateDependencyModuleNames: Engine
- PublicDependencyModuleNames: Core, CoreUObject, Slate, SlateCore

### `Source/Runtime/SlateBaseRenderer/Public/FX/SlateFXBaseSubsystem.h` (Public)


#### class `USlateFXBaseSubsystem`  
`class USlateFXBaseSubsystem : public UEngineSubsystem`  
_L16-54_
- reflection: `UCLASS(MinimalAPI, DisplayName = "Slate FX Subsystem")`
- inherits: `UEngineSubsystem`
- L23 _public prototype_ `static USlatePostBufferProcessor* GetPostProcessor(ESlatePostRT InSlatePostBufferBit);` — Get post processor for a particular post buffer index, if it exists
- L26 _public prototype_ `virtual bool ShouldCreateSubsystem(UObject* Outer) const override;`
- L27 _public prototype_ `virtual void Initialize(FSubsystemCollectionBase& Collection) override;`
- L28 _public prototype_ `virtual void Deinitialize() override;`
- L33 _public prototype_ `USlatePostBufferProcessor* GetSlatePostProcessor(ESlatePostRT InPostBufferBit);` — `UFUNCTION(BlueprintCallable, Category = "SlateFX")` — Get post processor for a particular post buffer index, if it exists
- L38 _protected function_ `virtual void OnInitProcessors()` — Called during world initialization to allow subclasses to populate SlatePostBufferProcessors
- L41 _protected function_ `virtual void OnCleanupProcessors()` — Called during world cleanup to allow subclasses to release renderer-specific resources
- L45 _protected member_ `TMap<ESlatePostRT, TObjectPtr<USlatePostBufferProcessor>> SlatePostBufferProcessors;` — `UPROPERTY(Transient)` — Map of post RT buffer index to buffer processors, if they exist
- L50 _private prototype_ `void OnPreWorldInitialization(UWorld* World, const UWorld::InitializationValues IVS);` — Callback to create processors on world init
- L53 _private prototype_ `void OnPostWorldCleanup(UWorld* World, bool SessionEnded, bool bCleanupResources);` — Callback to remove processors on world cleanup

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API SLATEBASERENDERER_API`

### `Source/Runtime/SlateBaseRenderer/Public/FX/SlatePostBufferBlur.h` (Public)


#### class `USlatePostBufferBlur`  
`class USlatePostBufferBlur : public USlatePostBufferProcessor`  
_L16-29_
- reflection: `UCLASS(MinimalAPI, Abstract, Blueprintable, CollapseCategories)`
- inherits: `USlatePostBufferProcessor`
- desc: Slate Post Buffer Processor that performs a simple gaussian blur to the backbuffer Create a new asset deriving from this class to use / modify settings.
- L23 _public member_ `float GaussianBlurStrength = 10;` — `UPROPERTY(interp, BlueprintReadWrite, Category = "GaussianBlur")`
- L27 _public function_ `USlatePostBufferBlur()`
- L28 _public function_ `virtual ~USlatePostBufferBlur() override`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API SLATEBASERENDERER_API`

### `Source/Runtime/SlateBaseRenderer/Public/FX/SlatePostBufferProcessor.h` (Public)


#### class `FSlatePostBufferProcessorProxy`  
`class FSlatePostBufferProcessorProxy : public TSharedFromThis<FSlatePostBufferProcessorProxy>`  
_L13-17_
- inherits: `TSharedFromThis<FSlatePostBufferProcessorProxy>`
- desc: Base class for proxy for post buffer processor that the renderthread uses to perform processing.
- L16 _public function_ `virtual ~FSlatePostBufferProcessorProxy()`

#### class `USlatePostBufferProcessor`  
`class USlatePostBufferProcessor : public UObject`  
_L26-41_
- reflection: `UCLASS(MinimalAPI, Abstract, Blueprintable, CollapseCategories)`
- inherits: `UObject`
- desc: Base class for types that can process the backbuffer scene into the slate post buffer. You need to register a proxy that derives from 'FSlateRHIPostBufferProcessorProxy' in USlateFXSubsystem::CreatePostBufferProcessorProxy For an example see: USlatePostBufferBlur.
- L32 _public prototype_ `virtual ~USlatePostBufferProcessor() = default;`
- L34 _public function_ `void SetRenderThreadProxy(TSharedPtr<FSlatePostBufferProcessorProxy> Proxy)`
- L40 _private member_ `TSharedPtr<FSlatePostBufferProcessorProxy> RenderThreadProxy;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API SLATEBASERENDERER_API`

### `Source/Runtime/SlateBaseRenderer/Public/SlateFontInfoBlueprintLibrary.h` (Public)


#### class `USlateFontInfoBlueprintLibrary`  
`class USlateFontInfoBlueprintLibrary : public UObject`  
_L12-18_
- reflection: `UCLASS()`
- inherits: `UObject`
- L17 _private prototype_ `static FSlateFontInfo MakeSlateFontInfo(const UObject* FontObject, UObject* FontMaterial, FFontOutlineSettings OutlineSettings, FName TypefaceFontName, float Size = 24.0f, int32 LetterSpacing = 0, float SkewAmount = 0.0f, bool bForceMonospaced = false, bool bMaterialIsStencil = false, float MonospacedWidth = 1.0f);` — `UFUNCTION(BlueprintPure, Category = "Slate Font", meta = (NativeMakeFunc))`

#### Free symbols / members of external scopes

- L9 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogSlateFontInfoBlueprint, Log, All);`
