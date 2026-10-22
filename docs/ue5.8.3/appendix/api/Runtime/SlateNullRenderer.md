# Runtime / SlateNullRenderer

- module root: `Source/Runtime/SlateNullRenderer`
- headers: 3; symbols: 34
- symbol kinds: class=2, function=1, member=3, prototype=28
- PrivateDependencyModuleNames: Core, CoreUObject, Engine, RHI, RenderCore, SlateBaseRenderer, SlateCore

### `Source/Runtime/SlateNullRenderer/Private/SlateNullRenderer.h` (Private)


#### class `FSlateNullRenderer`  
`class FSlateNullRenderer : public FSlateRenderer`  
_L17-56_
- inherits: `FSlateRenderer`
- desc: A slate null rendering implementation
- L20 _public prototype_ `FSlateNullRenderer(const TSharedRef<FSlateFontServices>& InSlateFontServices, const TSharedRef<FSlateShaderResourceManager>& InResourceManager);`
- L23 _public prototype_ `virtual bool Initialize() override;` — FSlateRenderer interface
- L24 _public prototype_ `virtual void Destroy() override;`
- L25 _public prototype_ `virtual FSlateDrawBuffer& AcquireDrawBuffer() override;`
- L26 _public prototype_ `virtual void ReleaseDrawBuffer(FSlateDrawBuffer& InWindowDrawBuffer) override;`
- L27 _public prototype_ `virtual void OnWindowDestroyed( const TSharedRef<SWindow>& InWindow ) override;`
- L28 _public prototype_ `virtual void RequestResize( const TSharedPtr<SWindow>& Window, uint32 NewWidth, uint32 NewHeight ) override;`
- L29 _public prototype_ `virtual void CreateViewport( const TSharedRef<SWindow> Window ) override;`
- L30 _public prototype_ `virtual void UpdateFullscreenState( const TSharedRef<SWindow> Window, uint32 OverrideResX, uint32 OverrideResY ) override;`
- L31 _public function_ `virtual void SetSystemResolution(uint32 Width, uint32 Height) override`
- L32 _public prototype_ `virtual void RestoreSystemResolution(const TSharedRef<SWindow> InWindow) override;`
- L33 _public prototype_ `virtual void DrawWindows( FSlateDrawBuffer& InWindowDrawBuffer ) override;`
- L34 _public prototype_ `virtual void ReleaseDynamicResource( const FSlateBrush& InBrush ) override;`
- L35 _public prototype_ `virtual void RemoveDynamicBrushResource( TSharedPtr<FSlateDynamicImageBrush> BrushToRemove ) override;`
- L36 _public prototype_ `virtual FIntPoint GenerateDynamicImageResource(const FName InTextureName) override;`
- L37 _public prototype_ `virtual bool GenerateDynamicImageResource( FName ResourceName, uint32 Width, uint32 Height, const TArray< uint8 >& Bytes ) override;`
- L38 _public prototype_ `virtual void PrepareToTakeScreenshot(const FIntRect& Rect, TArray<FColor>* OutColorData, SWindow* InScreenshotWindow) override;`
- L39 _public prototype_ `virtual FSlateResourceHandle GetResourceHandle(const FSlateBrush& Brush, FVector2f LocalSize, float DrawScale) override;`
- L40 _public prototype_ `virtual FSlateUpdatableTexture* CreateUpdatableTexture(uint32 Width, uint32 Height) override;`
- L41 _public prototype_ `virtual FSlateUpdatableTexture* CreateSharedHandleTexture(void* SharedHandle) override;`
- L42 _public prototype_ `virtual void ReleaseUpdatableTexture(FSlateUpdatableTexture* Texture) override;`
- L43 _public prototype_ `virtual FCriticalSection* GetResourceCriticalSection() override;`
- L44 _public prototype_ `virtual int32 GetCurrentSceneIndex() const override;`
- L45 _public prototype_ `virtual void SetCurrentSceneIndex(int32 InIndex) override;`
- L46 _public prototype_ `virtual void ClearScenes() override;`
- L47 _public prototype_ `virtual void Sync() const override;`
- L50 _protected prototype_ `virtual void RegisterCurrentScene_Impl(FSceneInterface* Scene) override;`
- L53 _private member_ `TSharedPtr<FSlateShaderResourceManager> ResourceManager;`
- L54 _private member_ `TUniquePtr<FSlateDrawBuffer> DrawBuffer;`
- L55 _private member_ `FCriticalSection ResourceCriticalSection;`

### `Source/Runtime/SlateNullRenderer/Private/SlateNullRendererPrivate.h` (Private)
_(no declarations extracted)_

### `Source/Runtime/SlateNullRenderer/Public/Interfaces/ISlateNullRendererModule.h` (Public)


#### class `ISlateNullRendererModule`  
`class ISlateNullRendererModule : public IModuleInterface`  
_L13-26_
- inherits: `IModuleInterface`
- desc: Interface for the Slate RHI Renderer module.
- L23 _public prototype_ `virtual TSharedRef<FSlateRenderer> CreateSlateNullRenderer( ) = 0;` — Creates a Slate RHI renderer. @return A new renderer which renders nothing.
- L25 _public prototype_ `virtual TSharedRef<ISlateFontAtlasFactory> CreateSlateFontAtlasFactory() = 0;`
