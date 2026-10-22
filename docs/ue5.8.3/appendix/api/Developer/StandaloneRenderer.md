# Developer / StandaloneRenderer

- module root: `Source/Developer/StandaloneRenderer`
- headers: 23; symbols: 583
- symbol kinds: class=29, delegate=1, externvar=49, function=69, macro=14, member=153, namespace=3, prototype=255, struct=10
- PrivateDependencyModuleNames: ApplicationCore, Core, CoreUObject, ImageWrapper, InputCore, SlateCore, SlateNullRenderer

### `Source/Developer/StandaloneRenderer/Private/Mac/OpenGL/SlateOpenGLMac.h` (Private)


#### Free symbols / members of external scopes

- L13 _prototype_ `void LockGLContext(NSOpenGLContext* Context);`
- L14 _prototype_ `void UnlockGLContext(NSOpenGLContext* Context);`

### `Source/Developer/StandaloneRenderer/Private/OpenGL/SlateOpenGLExtensions.h` (Private)


#### Free symbols / members of external scopes

- L13 _externvar_ `extern PFNGLGENBUFFERSARBPROC glGenBuffers;` — buffers
- L14 _externvar_ `extern PFNGLBINDBUFFERARBPROC glBindBuffer;`
- L15 _externvar_ `extern PFNGLBUFFERDATAARBPROC glBufferData;`
- L16 _externvar_ `extern PFNGLDELETEBUFFERSARBPROC glDeleteBuffers;`
- L17 _externvar_ `extern PFNGLMAPBUFFERARBPROC glMapBuffer;`
- L18 _externvar_ `extern PFNGLUNMAPBUFFERARBPROC glUnmapBuffer;`
- L19 _externvar_ `extern PFNGLDRAWRANGEELEMENTSPROC glDrawRangeElements;`
- L22 _externvar_ `extern PFNGLBLENDEQUATIONPROC glBlendEquation;` — Blending / texturing
- L23 _externvar_ `extern PFNGLACTIVETEXTUREARBPROC glActiveTexture;`
- L26 _externvar_ `extern PFNGLCREATESHADERPROC glCreateShader;` — shaders
- L27 _externvar_ `extern PFNGLSHADERSOURCEPROC glShaderSource;`
- L28 _externvar_ `extern PFNGLCOMPILESHADERPROC glCompileShader;`
- L29 _externvar_ `extern PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog;`
- L30 _externvar_ `extern PFNGLCREATEPROGRAMPROC glCreateProgram;`
- L31 _externvar_ `extern PFNGLATTACHSHADERPROC glAttachShader;`
- L32 _externvar_ `extern PFNGLDETACHSHADERPROC glDetachShader;`
- L33 _externvar_ `extern PFNGLLINKPROGRAMPROC glLinkProgram;`
- L34 _externvar_ `extern PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog;`
- L35 _externvar_ `extern PFNGLUSEPROGRAMPROC glUseProgram;`
- L36 _externvar_ `extern PFNGLDELETESHADERPROC glDeleteShader;`
- L37 _externvar_ `extern PFNGLDELETEPROGRAMPROC glDeleteProgram;`
- L38 _externvar_ `extern PFNGLGETSHADERIVPROC glGetShaderiv;`
- L39 _externvar_ `extern PFNGLGETPROGRAMIVPROC glGetProgramiv;`
- L40 _externvar_ `extern PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation;`
- L41 _externvar_ `extern PFNGLUNIFORM1FPROC glUniform1f;`
- L42 _externvar_ `extern PFNGLUNIFORM2FPROC glUniform2f;`
- L43 _externvar_ `extern PFNGLUNIFORM3FPROC glUniform3f;`
- L44 _externvar_ `extern PFNGLUNIFORM3FVPROC glUniform3fv;`
- L45 _externvar_ `extern PFNGLUNIFORM4FPROC glUniform4f;`
- L46 _externvar_ `extern PFNGLUNIFORM4FVPROC glUniform4fv;`
- L47 _externvar_ `extern PFNGLUNIFORM1IPROC glUniform1i;`
- L48 _externvar_ `extern PFNGLUNIFORMMATRIX4FVPROC glUniformMatrix4fv;`
- L49 _externvar_ `extern PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer;`
- L50 _externvar_ `extern PFNGLBINDATTRIBLOCATIONPROC glBindAttribLocation;`
- L51 _externvar_ `extern PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray;`
- L52 _externvar_ `extern PFNGLDISABLEVERTEXATTRIBARRAYPROC glDisableVertexAttribArray;`
- L53 _externvar_ `extern PFNGLGETACTIVEATTRIBPROC glGetActiveAttrib;`
- L54 _externvar_ `extern PFNGLGETACTIVEUNIFORMPROC glGetActiveUniform;`
- L55 _externvar_ `extern PFNGLGETATTACHEDSHADERSPROC glGetAttachedShaders;`
- L56 _externvar_ `extern PFNGLGETATTRIBLOCATIONPROC glGetAttribLocation;`
- L58 _externvar_ `extern PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB;`
- L60 _externvar_ `extern PFNGLDEBUGMESSAGECALLBACKARBPROC glDebugMessageCallback;`
- L61 _externvar_ `extern PFNGLBINDVERTEXARRAYPROC glBindVertexArray;`
- L62 _externvar_ `extern PFNGLDELETEVERTEXARRAYSPROC glDeleteVertexArrays;`
- L63 _externvar_ `extern PFNGLGENVERTEXARRAYSPROC glGenVertexArrays;`
- L64 _externvar_ `extern PFNGLISVERTEXARRAYPROC glIsVertexArray;`
- L68 _macro_ `#define ENUM_GL_ENTRYPOINTS(EnumMacro) \`
- L124 _macro_ `#define DECLARE_GL_ENTRYPOINTS(Type,Func) extern Type Func;`
- L125 _prototype_ `ENUM_GL_ENTRYPOINTS(DECLARE_GL_ENTRYPOINTS);`
- L129 _prototype_ `void LoadOpenGLExtensions();`

### `Source/Developer/StandaloneRenderer/Private/OpenGL/SlateOpenGLIndexBuffer.h` (Private)


#### class `FSlateOpenGLIndexBuffer`  
`class FSlateOpenGLIndexBuffer`  
_L12-69_
- desc: An OpenGL index buffer
- L15 _public prototype_ `FSlateOpenGLIndexBuffer();`
- L16 _public prototype_ `~FSlateOpenGLIndexBuffer();`
- L21 _public prototype_ `void DestroyBuffer();` — Releases the index buffers resource.
- L26 _public function_ `uint32 GetMaxNumIndices() const` — Returns the maximum number of indices that can be used by this buffer
- L32 _public prototype_ `void ResizeBuffer( uint32 NumIndices );` — Resizes the buffer to the passed in number of indices. Preserves internal data
- L37 _public prototype_ `void* Lock( uint32 FirstIndex );` — Locks the index buffer, returning a pointer to the indices
- L42 _public prototype_ `void Unlock();` — Unlocks the buffer.  Pointers to buffer data will no longer be valid after this call
- L47 _public prototype_ `void Bind();` — Binds the buffer so it can be accessed
- L52 _public function_ `bool IsValid() const` — Returns true if the buffer is valid and can be used
- L57 _private prototype_ `void ConditionalCreateBuffer();` — Initializes the index buffers resource if needed
- L60 _private member_ `GLuint MaxNumIndices;` — The maximum number of indices this buffer can hold
- L62 _private member_ `GLuint BufferID;` — An OpenGL resource id for this buffer
- L64 _private member_ `GLuint BufferSize;` — The size of the buffer in bytes
- L66 _private prototype_ `FSlateOpenGLIndexBuffer( const FSlateOpenGLIndexBuffer& );` — Hidden copy methods.
- L67 _private prototype_ `void operator=(const FSlateOpenGLIndexBuffer& );`

### `Source/Developer/StandaloneRenderer/Private/OpenGL/SlateOpenGLRenderer.h` (Private)


#### struct `FSlateOpenGLContext`  
`struct FSlateOpenGLContext`  
_L42-83_
- desc: Representation of an OpenGL context
- L45 _public member_ `HWND WindowHandle;`
- L46 _public member_ `HDC WindowDC;`
- L47 _public member_ `HGLRC Context;`
- L48 _public member_ `bool bReleaseWindowOnDestroy;`
- L69 _public prototype_ `FSlateOpenGLContext();`
- L70 _public prototype_ `~FSlateOpenGLContext();`
- L78 _public prototype_ `void Initialize( void* InWindow, const FSlateOpenGLContext* SharedContext );` — Initializes the context @param InWindow			Window owning this context or NULL @param SharedContext		The OpneGL context to share resources with or NULL
- L80 _public prototype_ `void Destroy();` — Releases the OpenGL context
- L82 _public prototype_ `void MakeCurrent();` — Sets this context as active

#### struct `FSlateOpenGLViewport`  
`struct FSlateOpenGLViewport`  
_L88-141_
- desc: Representation of an OpenGL viewport
- L90 _public member_ `FMatrix ProjectionMatrix;`
- L91 _public member_ `FSlateRect ViewportRect;`
- L92 _public member_ `FSlateOpenGLContext RenderingContext;`
- L94 _public member_ `bool bFullscreen;` — Whether or not we are fullscreen (@todo not implemented)
- L96 _public prototype_ `FSlateOpenGLViewport();`
- L97 _public function_ `~FSlateOpenGLViewport()`
- L105 _public prototype_ `void Initialize( TSharedRef<SWindow> InWindow, const FSlateOpenGLContext& SharedContext );` — Initializes the viewport @param InWindow			Window owning this viewport @param SharedContext		The OpneGL context to share resources with or NULL
- L107 _public prototype_ `void Destroy();` — Releases the OpenGL context
- L110 _public prototype_ `void MakeCurrent();` — Sets this viewport's OpenGL context as active
- L112 _public prototype_ `void SwapBuffers();` — Brings the contents of the back buffer to screen
- L115 _public prototype_ `void Resize( int32 Width, int32 Height, bool bInFullscreen );` — Updates the OpenGL context and projection matrix on resize
- L125 _private function_ `FMatrix CreateProjectionMatrix( uint32 Width, uint32 Height ) const` — Creates an orthographic matrix for use in OpenGL. @param Width		The width of the viewport @param Height	The height of the viewport

#### class `FSlateOpenGLRenderer`  
`class FSlateOpenGLRenderer : public FSlateRenderer`  
_L146-210_
- inherits: `FSlateRenderer`
- desc: An OpenGL renderer for use in rendering slate elements
- L149 _public prototype_ `FSlateOpenGLRenderer( const ISlateStyle& InStyle );`
- L150 _public prototype_ `~FSlateOpenGLRenderer();`
- L153 _public prototype_ `virtual FSlateDrawBuffer& AcquireDrawBuffer() override;` — FSlateRenderer interface
- L154 _public prototype_ `virtual void ReleaseDrawBuffer( FSlateDrawBuffer& InWindowDrawBuffer ) override;`
- L155 _public prototype_ `virtual bool Initialize() override;`
- L156 _public function_ `virtual void Destroy() override`
- L157 _public prototype_ `virtual void DrawWindows( FSlateDrawBuffer& InWindowDrawBuffer ) override;`
- L158 _public prototype_ `virtual void OnWindowDestroyed( const TSharedRef<SWindow>& InWindow ) override;`
- L159 _public prototype_ `virtual void CreateViewport( const TSharedRef<SWindow> InWindow ) override;`
- L160 _public prototype_ `virtual void RequestResize( const TSharedPtr<SWindow>& InWindow, uint32 NewSizeX, uint32 NewSizeY ) override;`
- L161 _public prototype_ `virtual void UpdateFullscreenState( const TSharedRef<SWindow> InWindow, uint32 OverrideResX, uint32 OverrideResY ) override;`
- L162 _public function_ `virtual void SetSystemResolution(uint32 Width, uint32 Height) override`
- L163 _public function_ `virtual void RestoreSystemResolution(const TSharedRef<SWindow> InWindow) override`
- L164 _public prototype_ `virtual void ReleaseDynamicResource( const FSlateBrush& Brush ) override;`
- L165 _public prototype_ `virtual bool GenerateDynamicImageResource(FName ResourceName, uint32 Width, uint32 Height, const TArray< uint8 >& Bytes) override;`
- L166 _public prototype_ `virtual bool GenerateDynamicImageResource(FName ResourceName, FSlateTextureDataRef TextureData) override;`
- L167 _public prototype_ `virtual FSlateResourceHandle GetResourceHandle(const FSlateBrush& Brush, FVector2f LocalSize, float DrawScale) override;`
- L168 _public prototype_ `virtual void RemoveDynamicBrushResource( TSharedPtr<FSlateDynamicImageBrush> BrushToRemove ) override;`
- L169 _public prototype_ `virtual void LoadStyleResources(const ISlateStyle& Style) override;`
- L170 _public prototype_ `virtual FSlateUpdatableTexture* CreateUpdatableTexture(uint32 Width, uint32 Height) override;`
- L171 _public prototype_ `virtual FSlateUpdatableTexture* CreateSharedHandleTexture(void* SharedHandle) override;`
- L172 _public prototype_ `virtual void ReleaseUpdatableTexture(FSlateUpdatableTexture* Texture) override;`
- L173 _public prototype_ `virtual ISlateAtlasProvider* GetTextureAtlasProvider() override;`
- L174 _public prototype_ `virtual FCriticalSection* GetResourceCriticalSection() override;`
- L175 _public prototype_ `virtual int32 GetCurrentSceneIndex() const override;`
- L176 _public prototype_ `virtual void SetCurrentSceneIndex(int32 InIndex) override;`
- L177 _public prototype_ `virtual void ClearScenes() override;`
- L180 _protected prototype_ `virtual void RegisterCurrentScene_Impl(FSceneInterface* Scene) override;`
- L189 _private prototype_ `void Private_ResizeViewport( FVector2f WindowSize, FSlateOpenGLViewport& InViewport, bool bFullscreen );` — Resizes an OpenGL Viewport @param WindowSize    The Size of the window in pixels @param InViewport    The viewport to resize
- L192 _private member_ `FMatrix ViewMatrix;` — View matrix to use when rendering
- L194 _private member_ `TMap<const SWindow*, FSlateOpenGLViewport> WindowToViewportMap;` — A mapping of slate windows to OpenGL viewports
- L196 _private member_ `FSlateDrawBuffer DrawBuffer;` — The buffer available to slate for creating draw elements
- L198 _private member_ `TUniquePtr<FSlateElementBatcher> ElementBatcher;` — The element batcher used to create and batch geometry for each element.
- L200 _private member_ `TSharedPtr<FSlateOpenGLTextureManager> TextureManager;` — Texture manager for accessing slate textures
- L202 _private member_ `TSharedPtr<FSlateOpenGLRenderingPolicy> RenderingPolicy;` — The rendering policy to use when drawing elements
- L204 _private member_ `const ISlateStyle& Style;` — Slate style used to create textures for rendering
- L206 _private member_ `FSlateOpenGLContext SharedContext;` — Shared OpenGL context
- L208 _private member_ `TArray<TSharedPtr<FSlateDynamicImageBrush>> DynamicBrushesToRemove;` — Dynamic image brushes to remove when safe
- L209 _private member_ `FCriticalSection ResourceCriticalSection;`

#### Free symbols / members of external scopes

- L27 _macro_ `#define LINUX_USE_OPENGL_3_2 0` — Optionally use 3.2 context on Linux. There's no real need to require this in a standalone application since it only renders Slate UI. With this set to 0, StandaloneRenderer will use OpenGL 2.1 on Linux, which is almost universally supported (as of 2015).
- L30 _macro_ `#define CHECK_GL_ERRORS \`
- L36 _macro_ `#define CHECK_GL_ERRORS`

### `Source/Developer/StandaloneRenderer/Private/OpenGL/SlateOpenGLRenderingPolicy.h` (Private)


#### class `FSlateOpenGLRenderingPolicy`  
`class FSlateOpenGLRenderingPolicy : public FSlateRenderingPolicy`  
_L19-70_
- inherits: `FSlateRenderingPolicy`
- L22 _public prototype_ `FSlateOpenGLRenderingPolicy( TSharedRef<FSlateFontServices> InSlateFontServices, TSharedRef<FSlateOpenGLTextureManager> InTextureManager );`
- L23 _public prototype_ `~FSlateOpenGLRenderingPolicy();`
- L30 _public prototype_ `void BuildRenderingBuffers(FSlateBatchData& BatchData);` — Updates vertex and index buffers used in drawing @param BatchData	The batch data that contains rendering data we need to upload to the buffers
- L38 _public prototype_ `void DrawElements( const FMatrix& ViewProjectionMatrix, FVector2D ViewportSize, TArrayView<const FSlateRenderBatch> RenderBatches);` — Draws Slate elements @param ViewProjectionMatrix	The view projection matrix to pass to the vertex shader @param RenderBatches			A list of batches that should be rendered.
- L40 _public prototype_ `virtual TSharedRef<FSlateShaderResourceManager> GetResourceManager() const override;`
- L42 _public function_ `virtual bool IsVertexColorInLinearSpace() const override`
- L47 _public prototype_ `void ConditionalInitializeResources();` — Initializes resources if needed
- L52 _public prototype_ `void ReleaseResources();` — Releases rendering resources
- L55 _private member_ `FSlateOpenGLVS VertexShader;` — Vertex shader used for all elements
- L57 _private member_ `FSlateOpenGLPS PixelShader;` — Pixel shader used for all elements
- L59 _private member_ `FSlateOpenGLElementProgram ElementProgram;` — Shader program for all elements
- L61 _private member_ `FSlateOpenGLVertexBuffer VertexBuffer;` — Vertex buffer containing all the vertices of every element
- L63 _private member_ `FSlateOpenGLIndexBuffer IndexBuffer;` — Index buffer for accessing vertices of elements
- L65 _private member_ `FSlateShaderResource* WhiteTexture;` — A default white texture to use if no other texture can be found
- L67 _private member_ `TSharedPtr<FSlateOpenGLTextureManager> TextureManager;` — Texture manager for accessing OpenGL textures
- L69 _private member_ `bool bIsInitialized;` — True if the rendering policy has been initialized

### `Source/Developer/StandaloneRenderer/Private/OpenGL/SlateOpenGLShaders.h` (Private)


#### class `FSlateOpenGLShader`  
`class FSlateOpenGLShader`  
_L16-27_
- desc: Base class for all OpenGL shaders
- L19 _public prototype_ `FSlateOpenGLShader();`
- L20 _public prototype_ `virtual ~FSlateOpenGLShader();`
- L21 _public prototype_ `virtual void Create( const FString& Filename ) = 0;`
- L22 _public function_ `GLuint GetShaderID() const`
- L24 _protected prototype_ `void CompileShader( const FString& Filename, GLenum ShaderType );`
- L26 _protected member_ `GLuint ShaderID;`

#### class `FSlateOpenGLVS`  
`class FSlateOpenGLVS : public FSlateOpenGLShader`  
_L31-37_
- inherits: `FSlateOpenGLShader`
- desc: Represents an OpenGL vertex shader.  Do not inherit from this for specific shaders.  Inherit from FSlateOpenGLProgram
- L34 _public prototype_ `FSlateOpenGLVS();`
- L35 _public prototype_ `~FSlateOpenGLVS();`
- L36 _public prototype_ `virtual void Create( const FString& Filename );`

#### class `FSlateOpenGLPS`  
`class FSlateOpenGLPS : public FSlateOpenGLShader`  
_L42-48_
- inherits: `FSlateOpenGLShader`
- desc: Represents an OpenGL vertex shader.  Do not inherit from this for specific shaders.  Inherit from FSlateOpenGLProgram
- L45 _public prototype_ `FSlateOpenGLPS();`
- L46 _public prototype_ `~FSlateOpenGLPS();`
- L47 _public prototype_ `virtual void Create( const FString& Filename );`

#### class `FSlateOpenGLShaderProgram`  
`class FSlateOpenGLShaderProgram`  
_L51-62_
- L54 _public prototype_ `FSlateOpenGLShaderProgram();`
- L55 _public prototype_ `virtual ~FSlateOpenGLShaderProgram();`
- L56 _public prototype_ `virtual void CreateProgram( const FSlateOpenGLVS& VertexShader, const FSlateOpenGLPS& PixelShader ) = 0;`
- L57 _public prototype_ `void BindProgram();`
- L59 _protected prototype_ `void LinkShaders( const FSlateOpenGLVS& VertexShader, const FSlateOpenGLPS& PixelShader );`
- L61 _protected member_ `GLuint ProgramID;`

#### class `FSlateOpenGLElementProgram`  
`class FSlateOpenGLElementProgram : public FSlateOpenGLShaderProgram`  
_L64-90_
- inherits: `FSlateOpenGLShaderProgram`
- L67 _public prototype_ `virtual void CreateProgram( const FSlateOpenGLVS& VertexShader, const FSlateOpenGLPS& PixelShader );`
- L68 _public prototype_ `void SetViewProjectionMatrix( const FMatrix& InVP );`
- L69 _public prototype_ `void SetVertexShaderParams( const FVector4f& ShaderParams );`
- L70 _public prototype_ `void SetTexture( FSlateOpenGLTexture *Texture, uint32 AddressU, uint32 AddressV );`
- L71 _public prototype_ `void SetDrawEffects(ESlateDrawEffect InDrawEffects );`
- L72 _public prototype_ `void SetShaderType( uint32 InShaderType );`
- L73 _public prototype_ `void SetShaderParams(const FShaderParams& InShaderParams);`
- L74 _public prototype_ `void SetGammaValues(const FVector2f& InGammaValues);`
- L76 _private member_ `GLint ViewProjectionMatrixParam;`
- L77 _private member_ `GLint VertexShaderParam;`
- L78 _private member_ `GLint TextureParam;`
- L79 _private member_ `GLint EffectsDisabledParam;`
- L80 _private member_ `GLint IgnoreTextureAlphaParam;`
- L82 _private member_ `GLint TextureRectParam;`
- L83 _private member_ `GLint SizeParam;`
- L84 _private member_ `GLint UseTextureRectangle;`
- L86 _private member_ `GLint ShaderTypeParam;`
- L87 _private member_ `GLint ShaderParamsParam;`
- L88 _private member_ `GLint ShaderParams2Param;`
- L89 _private member_ `GLint GammaValuesParam;`

### `Source/Developer/StandaloneRenderer/Private/OpenGL/SlateOpenGLTextureManager.h` (Private)


#### class `FSlateOpenGLTextureManager`  
`class FSlateOpenGLTextureManager : public FSlateShaderResourceManager, public ISlateAtlasProvider`  
_L20-95_
- inherits: `FSlateShaderResourceManager,ISlateAtlasProvider`
- desc: Stores a mapping of texture names to their loaded opengl resource.  Resources are loaded from disk and created on demand when needed
- L23 _public prototype_ `FSlateOpenGLTextureManager();`
- L24 _public prototype_ `virtual ~FSlateOpenGLTextureManager();`
- L26 _public prototype_ `void LoadUsedTextures();`
- L27 _public prototype_ `void LoadStyleResources(const ISlateStyle& Style);`
- L32 _public prototype_ `virtual FSlateShaderResourceProxy* GetShaderResource(const FSlateBrush& Brush, FVector2f LocalSize, float DrawScale) override;` — Returns a texture with the passed in name or NULL if it cannot be found.
- L35 _public prototype_ `virtual ISlateAtlasProvider* GetTextureAtlasProvider() override;`
- L38 _public prototype_ `virtual int32 GetNumAtlasPages() const override;` — ISlateAtlasProvider
- L39 _public prototype_ `virtual FSlateShaderResource* GetAtlasPageResource(const int32 InIndex) const override;`
- L40 _public prototype_ `virtual bool IsAtlasPageResourceAlphaOnly(const int32 InIndex) const override;`
- L42 _public prototype_ `virtual FAtlasSlotInfo GetAtlasSlotInfoAtPosition(FIntPoint InPosition, int32 AtlasIndex) const override;`
- L51 _public prototype_ `FSlateOpenGLTexture* CreateColorTexture(const FName TextureName, FColor InColor);` — Creates a 1x1 texture of the specified color @param TextureName	The name of the texture @param InColor		The color for the texture
- L53 _public prototype_ `FSlateShaderResourceProxy* CreateDynamicTextureResource(FName ResourceName, uint32 Width, uint32 Height, const TArray< uint8 >& RawData);`
- L55 _public prototype_ `void ReleaseDynamicTextureResource(const FSlateBrush& InBrush);`
- L57 _public prototype_ `void UpdateCache();`
- L58 _public prototype_ `void ConditionalFlushCache();`
- L65 _private prototype_ `void CreateTextures(const TArray< const FSlateBrush* >& Resources);` — Creates textures from files on disk and atlases them if possible @param Resources	The brush resources to load images for
- L67 _private prototype_ `bool LoadTexture(const FSlateBrush& InBrush, uint32& OutWidth, uint32& OutHeight, TArray<uint8>& OutDecodedImage);`
- L69 _private prototype_ `FSlateShaderResourceProxy* GenerateTextureResource(const FNewTextureInfo& Info, FName TextureName);`
- L71 _private prototype_ `FSlateShaderResourceProxy* GetDynamicTextureResource(const FSlateBrush& InBrush);`
- L73 _private prototype_ `FSlateShaderResourceProxy* GetVectorResource(const FSlateBrush& Brush, FVector2f LocalSize, float DrawScale);`
- L86 _private member_ `TMap<FName, TSharedPtr<FDynamicTextureResource> > DynamicTextureMap;` — Map of all active dynamic texture objects being used for brush resources
- L89 _private member_ `TArray<TUniquePtr<FSlateTextureAtlasOpenGL>> PrecachedTextureAtlases;` — Static texture atlases
- L92 _private member_ `TArray<TUniquePtr<FSlateOpenGLTexture>> NonAtlasedTextures;` — Static non atlased textures
- L94 _private member_ `TUniquePtr<FSlateVectorGraphicsCache> VectorGraphicsCache;`

#### struct `FSlateOpenGLTextureManager::FDynamicTextureResource`  
`struct FDynamicTextureResource`  
_L76-83_
- desc: Represents a dynamic resource for rendering
- L78 _public member_ `FSlateShaderResourceProxy* Proxy;`
- L79 _public member_ `FSlateOpenGLTexture* OpenGLTexture;`
- L81 _public prototype_ `FDynamicTextureResource(FSlateOpenGLTexture* OpenGLTexture);`
- L82 _public prototype_ `~FDynamicTextureResource();`

### `Source/Developer/StandaloneRenderer/Private/OpenGL/SlateOpenGLTextures.h` (Private)


#### class `FSlateOpenGLTexture`  
`class FSlateOpenGLTexture : public TSlateTexture< GLuint >, public FSlateUpdatableTexture`  
_L16-83_
- inherits: `TSlateTexture<GLuint>,FSlateUpdatableTexture`
- L19 _public function_ `FSlateOpenGLTexture( uint32 InSizeX, uint32 InSizeY ) : TSlateTexture( FSlateOpenGLTexture::NullTexture ) , SizeX(InSizeX) , SizeY(InSizeY) , TextureTargetType(GL_TEXTURE_2D)`
- L28 _public function_ `FSlateOpenGLTexture() : TSlateTexture( FSlateOpenGLTexture::NullTexture ) , SizeX(0) , SizeY(0) #if PLATFORM_LINUX , TextureTargetType(GL_TEXTURE_RECTANGLE) #else , TextureTargetType(GL_TEXTURE_RECTANGLE_ARB) #endif`
- L41 _public prototype_ `void Init( GLenum InTexFormat, const TArray<uint8>& TextureData );`
- L43 _public prototype_ `void Init( GLuint TextureID );`
- L45 _public prototype_ `void Init( void* TextureHandle );`
- L47 _public function_ `~FSlateOpenGLTexture()`
- L52 _public function_ `virtual void Cleanup() override`
- L54 _public function_ `uint32 GetWidth() const`
- L55 _public function_ `uint32 GetHeight() const`
- L58 _public function_ `virtual FSlateShaderResource* GetSlateResource() override` — FSlateUpdatableTexture interface
- L59 _public prototype_ `virtual void ResizeTexture( uint32 Width, uint32 Height ) override;`
- L60 _public prototype_ `virtual void UpdateTexture(const TArray<uint8>& Bytes) override;`
- L61 _public function_ `virtual void UpdateTextureThreadSafe(const TArray<uint8>& Bytes) override`
- L62 _public prototype_ `virtual void UpdateTextureThreadSafeRaw(uint32 Width, uint32 Height, const void* Buffer, const FIntRect& Dirty = FIntRect()) override;`
- L63 _public prototype_ `virtual void UpdateTextureThreadSafeWithTextureData(FSlateTextureData* TextureData) override;`
- L66 _public prototype_ `virtual void UpdateTextureThreadSafeWithKeyedTextureHandle(void* TextureHandle, int KeyLockVal, int KeyUnlockVal, const FIntRect& Dirty = FIntRect()) override;` — only macOS has support for texture handles currently
- L68 _public function_ `virtual void UpdateTextureThreadSafeWithKeyedTextureHandle(void* TextureHandle, int KeyLockVal, int KeyUnlockVal, const FIntRect& Dirty = FIntRect()) override`
- L71 _public function_ `uint32 GetTextureTargetType() const`
- L74 _private prototype_ `void UpdateTextureRaw(const void* Buffer, const FIntRect& Dirty);` — Helper method used by the different UpdateTexture* methods
- L76 _private member_ `static GLuint NullTexture;`
- L78 _private member_ `GLenum TexFormat;`
- L79 _private member_ `uint32 SizeX;`
- L80 _private member_ `uint32 SizeY;`
- L81 _private member_ `bool bHasPendingResize;`
- L82 _private member_ `uint32 TextureTargetType;`

#### class `FSlateFontTextureOpenGL`  
`class FSlateFontTextureOpenGL : public FSlateFontAtlas`  
_L88-108_
- inherits: `FSlateFontAtlas`
- desc: Representation of a texture for fonts in which characters are packed tightly based on their bounding rectangle
- L91 _public prototype_ `FSlateFontTextureOpenGL(uint32 Width, uint32 Height, ESlateFontAtlasContentType InContentType);`
- L92 _public prototype_ `~FSlateFontTextureOpenGL();`
- L94 _public prototype_ `void CreateFontTexture();`
- L97 _public prototype_ `virtual void ConditionalUpdateTexture();` — FSlateFontAtlas interface
- L98 _public function_ `virtual class FSlateShaderResource* GetSlateTexture() const override`
- L99 _public function_ `virtual class FTextureResource* GetEngineTexture() override`
- L100 _public function_ `virtual void ReleaseResources() override`
- L103 _private prototype_ `GLint GetGLTextureInternalFormat() const;`
- L104 _private prototype_ `GLint GetGLTextureFormat() const;`
- L105 _private prototype_ `GLint GetGLTextureType() const;`
- L107 _private member_ `FSlateOpenGLTexture* FontTexture;`

#### class `FSlateTextureAtlasOpenGL`  
`class FSlateTextureAtlasOpenGL : public FSlateTextureAtlas`  
_L114-130_
- inherits: `FSlateTextureAtlas`
- desc: Representation of a texture for images in which characters are packed tightly based on their bounding rectangle
- L117 _public prototype_ `FSlateTextureAtlasOpenGL(uint32 Width, uint32 Height, uint32 StrideBytes, ESlateTextureAtlasPaddingStyle PaddingStyle);`
- L118 _public prototype_ `~FSlateTextureAtlasOpenGL();`
- L121 _public prototype_ `virtual void ConditionalUpdateTexture() override;`
- L122 _public function_ `virtual void ReleaseResources() override`
- L124 _public function_ `FSlateOpenGLTexture* GetAtlasTexture() const`
- L126 _private prototype_ `void InitAtlasTexture();`
- L128 _private member_ `FSlateOpenGLTexture* AtlasTexture;`
- L129 _private member_ `GLuint TextureID;`

### `Source/Developer/StandaloneRenderer/Private/OpenGL/SlateOpenGLVertexBuffer.h` (Private)


#### class `FSlateOpenGLVertexBuffer`  
`class FSlateOpenGLVertexBuffer`  
_L14-70_
- desc: An OpenGL vertex buffer
- L17 _public prototype_ `FSlateOpenGLVertexBuffer( uint32 InStride );`
- L18 _public prototype_ `~FSlateOpenGLVertexBuffer();`
- L23 _public prototype_ `void DestroyBuffer();` — Releases the vertex buffers resource.
- L28 _public function_ `uint32 GetBufferSize() const` — Returns the size of the buffer in bytes.
- L34 _public prototype_ `void ResizeBuffer( uint32 NewSize );` — Resizes the buffer to the passed in number of indices. Preserves internal data
- L39 _public prototype_ `void* Lock( uint32 Offset );` — Locks the vertex buffer, returning a pointer to its vertices
- L44 _public prototype_ `void Unlock();` — Unlocks the buffer.  Pointers to buffer data will no longer be valid after this call
- L49 _public prototype_ `void Bind();` — Binds the buffer so it can be accessed
- L54 _public function_ `bool IsValid() const` — Returns true if the buffer is valid and can be used
- L59 _private prototype_ `void ConditionalCreateBuffer();` — Initializes the vertex buffers resource if needed
- L62 _private member_ `GLuint BufferSize;` — The size of the buffer in bytes.
- L64 _private member_ `GLuint Stride;` — The size of each element in the buffer.
- L66 _private member_ `GLuint BufferID;` — An OpenGL resource ID for the buffer
- L68 _private prototype_ `FSlateOpenGLVertexBuffer( const FSlateOpenGLVertexBuffer& );` — Hidden copy methods.
- L69 _private prototype_ `void operator=(const FSlateOpenGLVertexBuffer& );`

### `Source/Developer/StandaloneRenderer/Private/StandaloneRendererLog.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogStandaloneRenderer, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogStandaloneRenderer, Log, All);`

### `Source/Developer/StandaloneRenderer/Private/StandaloneRendererPlatformHeaders.h` (Private)


#### Free symbols / members of external scopes

- L41 _macro_ `#define glMapBuffer glMapBufferOES` — renamed keywords
- L42 _macro_ `#define glUnmapBuffer glUnmapBufferOES`
- L43 _macro_ `#define GL_WRITE_ONLY GL_WRITE_ONLY_OES`
- L44 _macro_ `#define GL_CLAMP GL_CLAMP_TO_EDGE`
- L45 _macro_ `#define GL_RGBA8 GL_RGBA`
- L46 _macro_ `#define GL_UNSIGNED_INT_8_8_8_8_REV GL_UNSIGNED_BYTE`
- L49 _macro_ `#define glTexEnvf(...)` — unused functions
- L50 _macro_ `#define glTexEnvi(...)`
- L51 _macro_ `#define glAlphaFunc(...)`

### `Source/Developer/StandaloneRenderer/Private/StandaloneRendererPrivate.h` (Private)
_(no declarations extracted)_

### `Source/Developer/StandaloneRenderer/Private/Windows/D3D/SlateD3DConstantBuffer.h` (Private)


#### class `FSlateD3DConstantBuffer`  
`template<typename BufferType> class FSlateD3DConstantBuffer`  
_L11-56_
- L14 _public function_ `void Create()`
- L33 _public function_ `TRefCountPtr<ID3D11Buffer> GetResource()`
- L34 _public function_ `BufferType& GetBufferData()`
- L35 _public function_ `void UpdateBuffer()`
- L42 _private function_ `void* Lock()`
- L49 _private function_ `void Unlock()`
- L54 _private member_ `TRefCountPtr<ID3D11Buffer> Buffer;`
- L55 _private member_ `BufferType BufferData;`

### `Source/Developer/StandaloneRenderer/Private/Windows/D3D/SlateD3DFindBestDevice.h` (Private)


#### struct `UE::StandaloneRenderer::D3D::FFindBestDevice`  
`struct FFindBestDevice`  
_L16-46_
- L18 _public prototype_ `FFindBestDevice();`
- L19 _public prototype_ `~FFindBestDevice();`
- L21 _public prototype_ `bool IsValid() const;`
- L23 _public prototype_ `bool CreateDevice(ID3D11Device** Device, ID3D11DeviceContext** DeviceContext);`
- L25 _public prototype_ `static const TCHAR* GetFeatureLevelString(D3D_FEATURE_LEVEL FeatureLevel);`
- L28 _private prototype_ `void LoadSettings();`
- L29 _private prototype_ `void SelectAdapter();`
- L31 _private prototype_ `HRESULT EnumerateAdapters(UINT AdapterIndex, IDXGIAdapter** Adapter);`
- L32 _private prototype_ `bool CreateTesingDevice(IDXGIAdapter* Adapter, D3D_FEATURE_LEVEL& ResultFeatureLevel);`
- L35 _private member_ `TRefCountPtr<IDXGIAdapter> ChosenAdapter;`
- L36 _private member_ `TRefCountPtr<IDXGIFactory1> DXGIFactory1;`
- L37 _private member_ `TRefCountPtr<IDXGIFactory6> DXGIFactory6;`
- L38 _private member_ `D3D_FEATURE_LEVEL ChosenFeatureLevel;`
- L39 _private member_ `int32 GpuPreference;`
- L40 _private member_ `int32 ExplicitAdapterValue = -1;` — int32 GpuPreference;  DXGI_GPU_PREFERENCE
- L41 _private member_ `int32 PreferedAdapterVendor = -1;`
- L42 _private member_ `bool bAllowSoftwareRendering = false;`
- L43 _private member_ `bool bPreferedMinimalPower = false;`
- L44 _private member_ `bool bPreferedHighPerformance = false;`
- L45 _private member_ `bool bDebug = false;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace StandaloneRenderer` (scope `UE`)
- L13 _namespace_ `namespace D3D` (scope `UE::StandaloneRenderer`)

### `Source/Developer/StandaloneRenderer/Private/Windows/D3D/SlateD3DIndexBuffer.h` (Private)


#### class `FSlateD3DIndexBuffer`  
`class FSlateD3DIndexBuffer`  
_L9-41_
- L12 _public prototype_ `FSlateD3DIndexBuffer();`
- L13 _public prototype_ `virtual ~FSlateD3DIndexBuffer();`
- L16 _public prototype_ `virtual void CreateBuffer();` — Initializes the index buffers resource.
- L19 _public prototype_ `virtual void DestroyBuffer();` — Releases the index buffers resource.
- L22 _public function_ `uint32 GetMaxNumIndices() const` — Returns the maximum number of indices that can be used by this buffer
- L25 _public prototype_ `void ResizeBuffer( uint32 NumIndices );` — Resizes the buffer to the passed in size.  Preserves internal data
- L28 _public prototype_ `void* Lock( uint32 FirstIndex );` — Locks the index buffer, returning a pointer to the indices
- L31 _public prototype_ `void Unlock();` — Unlocks the index buffer
- L33 _public function_ `TRefCountPtr<ID3D11Buffer> GetResource()`
- L35 _private member_ `uint32 MaxNumIndices;`
- L36 _private member_ `TRefCountPtr<ID3D11Buffer> Buffer;`
- L38 _private prototype_ `FSlateD3DIndexBuffer( const FSlateD3DIndexBuffer& );` — Hidden copy methods.
- L39 _private prototype_ `void operator=(const FSlateD3DIndexBuffer& );`

### `Source/Developer/StandaloneRenderer/Private/Windows/D3D/SlateD3DRenderer.h` (Private)


#### struct `FSlateD3DViewport`  
`struct FSlateD3DViewport`  
_L14-38_
- L16 _public member_ `FMatrix ProjectionMatrix;`
- L17 _public member_ `D3D11_VIEWPORT ViewportInfo;`
- L18 _public member_ `TRefCountPtr<IDXGISwapChain> D3DSwapChain;`
- L19 _public member_ `TRefCountPtr<ID3D11Texture2D> BackBufferTexture;`
- L20 _public member_ `TRefCountPtr<ID3D11RenderTargetView> RenderTargetView;`
- L21 _public member_ `TRefCountPtr<ID3D11DepthStencilView> DepthStencilView;`
- L22 _public member_ `bool bFullscreen;`
- L24 _public function_ `FSlateD3DViewport() : bFullscreen( false )`
- L30 _public function_ `~FSlateD3DViewport()`

#### class `FSlateD3DRenderer`  
`class FSlateD3DRenderer : public FSlateRenderer`  
_L46-106_
- inherits: `FSlateRenderer`
- L49 _public prototype_ `FSlateD3DRenderer( const ISlateStyle &InStyle );`
- L50 _public prototype_ `~FSlateD3DRenderer();`
- L53 _public prototype_ `virtual bool Initialize() override;` — FSlateRenderer Interface
- L54 _public prototype_ `virtual void Destroy() override;`
- L55 _public prototype_ `virtual FSlateDrawBuffer& AcquireDrawBuffer() override;`
- L56 _public prototype_ `virtual void ReleaseDrawBuffer( FSlateDrawBuffer& InWindowDrawBuffer ) override;`
- L57 _public prototype_ `virtual void DrawWindows( FSlateDrawBuffer& InWindowDrawBuffer ) override;`
- L58 _public prototype_ `virtual void OnWindowDestroyed( const TSharedRef<SWindow>& InWindow ) override;`
- L59 _public prototype_ `virtual void CreateViewport( const TSharedRef<SWindow> InWindow ) override;`
- L60 _public prototype_ `virtual void RequestResize( const TSharedPtr<SWindow>& InWindow, uint32 NewSizeX, uint32 NewSizeY ) override;`
- L61 _public prototype_ `virtual void UpdateFullscreenState( const TSharedRef<SWindow> InWindow, uint32 OverrideResX, uint32 OverrideResY ) override;`
- L62 _public function_ `virtual void SetSystemResolution(uint32 Width, uint32 Height) override`
- L63 _public function_ `virtual void RestoreSystemResolution(const TSharedRef<SWindow> InWindow) override`
- L64 _public prototype_ `virtual void ReleaseDynamicResource( const FSlateBrush& Brush ) override;`
- L65 _public prototype_ `virtual bool GenerateDynamicImageResource(FName ResourceName, uint32 Width, uint32 Height, const TArray< uint8 >& Bytes) override;`
- L66 _public prototype_ `virtual bool GenerateDynamicImageResource(FName ResourceName, FSlateTextureDataRef TextureData) override;`
- L67 _public prototype_ `virtual FSlateResourceHandle GetResourceHandle(const FSlateBrush& Brush, FVector2f LocalSize, float DrawScale) override;`
- L68 _public prototype_ `virtual void RemoveDynamicBrushResource( TSharedPtr<FSlateDynamicImageBrush> BrushToRemove ) override;`
- L69 _public prototype_ `virtual void LoadStyleResources( const ISlateStyle& Style ) override;`
- L70 _public prototype_ `virtual FSlateUpdatableTexture* CreateUpdatableTexture(uint32 Width, uint32 Height) override;`
- L71 _public prototype_ `virtual FSlateUpdatableTexture* CreateSharedHandleTexture(void* SharedHandle) override;`
- L72 _public prototype_ `virtual void ReleaseUpdatableTexture(FSlateUpdatableTexture* Texture) override;`
- L73 _public prototype_ `virtual ISlateAtlasProvider* GetTextureAtlasProvider() override;`
- L74 _public prototype_ `virtual FCriticalSection* GetResourceCriticalSection() override;`
- L75 _public prototype_ `virtual int32 GetCurrentSceneIndex() const override;`
- L76 _public prototype_ `virtual void SetCurrentSceneIndex(int32 InIndex) override;`
- L77 _public prototype_ `virtual void ClearScenes() override;`
- L80 _protected prototype_ `virtual void RegisterCurrentScene_Impl(FSceneInterface* Scene) override;`
- L84 _public prototype_ `bool CreateDevice();`
- L85 _public prototype_ `void CreateDepthStencilBuffer( FSlateD3DViewport& Viewport );`
- L87 _public prototype_ `virtual bool HasLostDevice() const override;`
- L90 _private prototype_ `void Private_CreateViewport( TSharedRef<SWindow> InWindow, const FVector2D& WindowSize );`
- L91 _private prototype_ `void Private_ResizeViewport( const TSharedRef<SWindow> InWindow, uint32 Width, uint32 Height, bool bFullscreen );`
- L92 _private prototype_ `void CreateBackBufferResources( TRefCountPtr<IDXGISwapChain>& InSwapChain, TRefCountPtr<ID3D11Texture2D>& OutBackBuffer, TRefCountPtr<ID3D11RenderTargetView>& OutRTV );`
- L96 _private member_ `bool bHasAttemptedInitialization;`
- L98 _private member_ `FMatrix ViewMatrix;`
- L99 _private member_ `TMap<const SWindow*, FSlateD3DViewport> WindowToViewportMap;`
- L100 _private member_ `FSlateDrawBuffer DrawBuffer;`
- L101 _private member_ `TUniquePtr<FSlateElementBatcher> ElementBatcher;`
- L102 _private member_ `TSharedPtr<FSlateD3DTextureManager> TextureManager;`
- L103 _private member_ `TSharedPtr<FSlateD3D11RenderingPolicy> RenderingPolicy;`
- L104 _private member_ `TArray<TSharedPtr<FSlateDynamicImageBrush>> DynamicBrushesToRemove;`
- L105 _private member_ `FCriticalSection ResourceCriticalSection;`

#### Free symbols / members of external scopes

- L40 _externvar_ `extern TRefCountPtr<ID3D11Device> GD3DDevice;`
- L41 _externvar_ `extern TRefCountPtr<ID3D11DeviceContext> GD3DDeviceContext;`
- L42 _externvar_ `extern bool GEncounteredCriticalD3DDeviceError;`
- L44 _prototype_ `void LogSlateD3DRendererFailure(const FString& Description, HRESULT Hr);`

### `Source/Developer/StandaloneRenderer/Private/Windows/D3D/SlateD3DRenderingPolicy.h` (Private)


#### class `FSlateD3D11RenderingPolicy`  
`class FSlateD3D11RenderingPolicy : public FSlateRenderingPolicy`  
_L14-46_
- inherits: `FSlateRenderingPolicy`
- L17 _public prototype_ `FSlateD3D11RenderingPolicy( TSharedRef<FSlateFontServices> InSlateFontServices, TSharedRef<FSlateD3DTextureManager> InTextureManager );`
- L18 _public prototype_ `~FSlateD3D11RenderingPolicy();`
- L20 _public prototype_ `void BuildRenderingBuffers( FSlateBatchData& InBatchData );`
- L21 _public prototype_ `void DrawElements(const FMatrix& ViewProjectionMatrix, int32 FirstBatchIndex, const TArray<FSlateRenderBatch>& RenderBatches);`
- L23 _public prototype_ `virtual TSharedRef<FSlateShaderResourceManager> GetResourceManager() const override;`
- L24 _public function_ `virtual bool IsVertexColorInLinearSpace() const override`
- L27 _private prototype_ `void InitResources();`
- L28 _private prototype_ `void ReleaseResources();`
- L30 _private member_ `FSlateD3DVertexBuffer VertexBuffer;`
- L31 _private member_ `FSlateD3DIndexBuffer IndexBuffer;`
- L32 _private member_ `FSlateDefaultVS* VertexShader;`
- L33 _private member_ `FSlateDefaultPS* PixelShader;`
- L34 _private member_ `FSlateShaderResource* WhiteTexture;`
- L35 _private member_ `TRefCountPtr<ID3D11RasterizerState> NormalRasterState;`
- L36 _private member_ `TRefCountPtr<ID3D11RasterizerState> WireframeRasterState;`
- L37 _private member_ `TRefCountPtr<ID3D11RasterizerState> ScissorRasterState;`
- L38 _private member_ `TRefCountPtr<ID3D11BlendState> AlphaBlendState;`
- L39 _private member_ `TRefCountPtr<ID3D11BlendState> NoBlendState;`
- L40 _private member_ `TRefCountPtr<ID3D11DepthStencilState> DSStateOff;`
- L41 _private member_ `TRefCountPtr<ID3D11SamplerState> PointSamplerState_Wrap;`
- L42 _private member_ `TRefCountPtr<ID3D11SamplerState> PointSamplerState_Clamp;`
- L43 _private member_ `TRefCountPtr<ID3D11SamplerState> BilinearSamplerState_Wrap;`
- L44 _private member_ `TRefCountPtr<ID3D11SamplerState> BilinearSamplerState_Clamp;`
- L45 _private member_ `TSharedRef<FSlateD3DTextureManager> TextureManager;`

### `Source/Developer/StandaloneRenderer/Private/Windows/D3D/SlateD3DShaders.h` (Private)


#### class `FSlateD3DShaderParameter`  
`class FSlateD3DShaderParameter`  
_L10-14_
- L13 _public function_ `virtual ~FSlateD3DShaderParameter()`

#### class `TSlateD3DTypedShaderParameter`  
`template <typename ParamType> class TSlateD3DTypedShaderParameter : public FSlateD3DShaderParameter`  
_L17-24_
- inherits: `FSlateD3DShaderParameter`
- L20 _public function_ `void SetParameter( const TRefCountPtr<ParamType>& InParam)`
- L21 _public function_ `const TRefCountPtr<ParamType>& GetParameter() const`
- L23 _private member_ `TRefCountPtr<ParamType> Param;`

#### class `FSlateShaderParameterMap`  
`class FSlateShaderParameterMap`  
_L26-91_
- L29 _public function_ `static FSlateShaderParameterMap& Get()`
- L41 _public function_ `template <typename ParamType> TSlateD3DTypedShaderParameter<ParamType>& RegisterParameter( const FString& ParamName )`
- L58 _public function_ `FSlateD3DShaderParameter* Find( const FString& ParamName )`
- L72 _public function_ `void Shutdown()`
- L82 _public function_ `~FSlateShaderParameterMap()`
- L88 _private function_ `FSlateShaderParameterMap()`
- L90 _private member_ `TMap<FString, FSlateD3DShaderParameter*> NameToParameterMap;`

#### struct `FSlateD3DShaderBindings`  
`struct FSlateD3DShaderBindings`  
_L95-100_
- L97 _public member_ `TArray< TSlateD3DTypedShaderParameter<ID3D11ShaderResourceView>* > ResourceViews;`
- L98 _public member_ `TArray< TSlateD3DTypedShaderParameter<ID3D11SamplerState>* > SamplerStates;`
- L99 _public member_ `TArray< TSlateD3DTypedShaderParameter<ID3D11Buffer>* > ConstantBuffers;`

#### class `FSlateD3DVS`  
`class FSlateD3DVS`  
_L102-115_
- L105 _public function_ `virtual ~FSlateD3DVS()`
- L106 _public prototype_ `void Create( const FString& Filename, const FString& EntryPoint, const FString& ShaderModel, D3D11_INPUT_ELEMENT_DESC* VertexLayout, uint32 VertexLayoutCount );`
- L107 _public prototype_ `void BindShader();`
- L108 _public prototype_ `void BindParameters();`
- L110 _protected function_ `virtual void UpdateParameters()`
- L112 _private member_ `FSlateD3DShaderBindings ShaderBindings;`
- L113 _private member_ `TRefCountPtr<ID3D11VertexShader> VertexShader;`
- L114 _private member_ `TRefCountPtr<ID3D11InputLayout> InputLayout;`

#### class `FSlateD3DPS`  
`class FSlateD3DPS`  
_L118-130_
- L121 _public function_ `virtual ~FSlateD3DPS()`
- L122 _public prototype_ `void Create( const FString& Filename, const FString& EntryPoint, const FString& ShaderModel );`
- L123 _public prototype_ `void BindShader();`
- L124 _public prototype_ `void BindParameters();`
- L126 _protected function_ `virtual void UpdateParameters()`
- L128 _private member_ `FSlateD3DShaderBindings ShaderBindings;`
- L129 _private member_ `TRefCountPtr<ID3D11PixelShader> PixelShader;`

#### class `FSlateDefaultVS`  
`class FSlateDefaultVS : public FSlateD3DVS`  
_L132-151_
- inherits: `FSlateD3DVS`
- L135 _public prototype_ `FSlateDefaultVS();`
- L136 _public prototype_ `void SetViewProjection( const FMatrix& ViewProjectionMatrix );`
- L137 _public prototype_ `void SetShaderParams( const FVector4& InShaderParams );`
- L139 _protected prototype_ `void UpdateParameters();`
- L149 _private member_ `FSlateD3DConstantBuffer<FPerElementConstants> ConstantBuffer;`
- L150 _private member_ `TSlateD3DTypedShaderParameter<ID3D11Buffer>* Constants;`

#### struct `FSlateDefaultVS::FPerElementConstants`  
`struct FPerElementConstants`  
_L142-146_
- L144 _public member_ `FMatrix44f ViewProjection;`
- L145 _public member_ `FVector4f VertexShaderParams;`

#### class `FSlateDefaultPS`  
`class FSlateDefaultPS : public FSlateD3DPS`  
_L153-195_
- inherits: `FSlateD3DPS`
- L156 _public prototype_ `FSlateDefaultPS();`
- L158 _public function_ `void SetTexture( const TRefCountPtr<ID3D11ShaderResourceView>& InTexture, TRefCountPtr<ID3D11SamplerState>& InSamplerState )`
- L164 _public prototype_ `void SetShaderType(uint32 InShaderType);`
- L165 _public prototype_ `void SetDrawEffects(ESlateDrawEffect InDrawEffects);`
- L166 _public prototype_ `void SetShaderParams(const FShaderParams& InShaderParams);`
- L167 _public prototype_ `void SetGammaValues(const FVector2f& InGammaValues);`
- L169 _protected prototype_ `void UpdateParameters();`
- L188 _private member_ `FSlateD3DConstantBuffer<FPerElementConstants> PerElementConstants;`
- L189 _private member_ `FSlateD3DConstantBuffer<FPerFrameConstants> PerFrameConstants;`
- L190 _private member_ `TSlateD3DTypedShaderParameter<ID3D11ShaderResourceView>* Texture;`
- L191 _private member_ `TSlateD3DTypedShaderParameter<ID3D11SamplerState>* TextureSampler;`
- L192 _private member_ `TSlateD3DTypedShaderParameter<ID3D11Buffer>* PerFrameCBufferParam;`
- L193 _private member_ `TSlateD3DTypedShaderParameter<ID3D11Buffer>* PerElementCBufferParam;`
- L194 _private member_ `TRefCountPtr<ID3D11SamplerState> SamplerState;`

#### struct `FSlateDefaultPS::FPerElementConstants`  
`MS_ALIGN(16) struct FPerElementConstants`  
_L171-179_
- L173 _public member_ `FVector4f ShaderParams;` — 16 bytes
- L174 _public member_ `FVector4f ShaderParams2;` — 16 bytes
- L175 _public member_ `uint32 ShaderType;` — 4 bytes
- L176 _public member_ `uint32 IgnoreTextureAlpha;` — 4 bytes
- L177 _public member_ `uint32 DisableEffect;` — 4 bytes
- L178 _public member_ `uint32 UNUSED[1];` — 4 bytes

#### struct `FSlateDefaultPS::FPerFrameConstants`  
`MS_ALIGN(16) struct FPerFrameConstants`  
_L182-185_
- L184 _public member_ `FVector2f GammaValues;`

### `Source/Developer/StandaloneRenderer/Private/Windows/D3D/SlateD3DTextureManager.h` (Private)


#### class `FSlateD3DTextureManager`  
`class FSlateD3DTextureManager : public ISlateAtlasProvider, public FSlateShaderResourceManager`  
_L15-120_
- inherits: `ISlateAtlasProvider,FSlateShaderResourceManager`
- desc: Stores a mapping of texture names to their loaded d3d resource.  Resources are loaded from disk and created on demand when needed
- L18 _public prototype_ `FSlateD3DTextureManager();`
- L19 _public prototype_ `virtual ~FSlateD3DTextureManager();`
- L22 _public prototype_ `virtual int32 GetNumAtlasPages() const override;` — ISlateAtlasProvider
- L23 _public prototype_ `virtual FSlateShaderResource* GetAtlasPageResource(const int32 InIndex) const override;`
- L24 _public prototype_ `virtual bool IsAtlasPageResourceAlphaOnly(const int32 InIndex) const override;`
- L26 _public prototype_ `virtual FAtlasSlotInfo GetAtlasSlotInfoAtPosition(FIntPoint InPosition, int32 AtlasIndex) const override;`
- L33 _public prototype_ `void LoadUsedTextures();` — Loads and creates rendering resources for all used textures. In this implementation all textures must be known at startup time or they will not be found
- L35 _public prototype_ `void LoadStyleResources( const ISlateStyle& Style );`
- L41 _public prototype_ `virtual FSlateShaderResourceProxy* GetShaderResource(const FSlateBrush& Brush, FVector2f LocalSize, float DrawScale) override;` — Returns a texture with the passed in name or NULL if it cannot be found.
- L43 _public prototype_ `virtual ISlateAtlasProvider* GetTextureAtlasProvider() override;`
- L51 _public prototype_ `virtual FSlateShaderResourceProxy* CreateColorTexture( const FName TextureName, FColor InColor );` — Creates a 1x1 texture of the specified color @param TextureName	The name of the texture @param InColor		The color for the texture
- L53 _public prototype_ `FSlateShaderResourceProxy* CreateDynamicTextureResource(FName ResourceName, uint32 Width, uint32 Height, const TArray< uint8 >& RawData);`
- L60 _public prototype_ `void ReleaseDynamicTextureResource( const FSlateBrush& InBrush );` — Releases a dynamic texture resource @param InBrush	The brush to with texture to release
- L62 _public prototype_ `void UpdateCache();`
- L63 _public prototype_ `void ConditionalFlushCache();`
- L70 _private prototype_ `FSlateShaderResourceProxy* GetDynamicTextureResource( const FSlateBrush& InBrush );` — Gets a dynamic texture resource @param InBrush	The brush to with texture to get
- L79 _private prototype_ `FSlateShaderResourceProxy* GetVectorResource(const FSlateBrush& Brush, FVector2f LocalSize, float DrawScale);` — Gets a vector graphics resource (may generate it internally) @param InBrush	The brush to with texture to get @param LocalSize	The unscaled local size of the final image @param DrawScale	Any scaling applied to the final image
- L86 _private prototype_ `void CreateTextures( const TArray< const FSlateBrush* >& Resources );` — Creates textures from files on disk and atlases them if possible @param Resources	The brush resources to load images for
- L88 _private prototype_ `bool LoadTexture( const FSlateBrush& InBrush, uint32& OutWidth, uint32& OutHeight, TArray<uint8>& OutDecodedImage );`
- L95 _private prototype_ `FSlateShaderResourceProxy* GenerateTextureResource( const FNewTextureInfo& Info, FName TextureName );` — Generates rendering resources for a texture @param Info	Information on how to generate the texture resource
- L110 _private member_ `TMap<FName, TSharedPtr<FDynamicTextureResource> > DynamicTextureMap;` — Map of all active dynamic texture objects being used for brush resources
- L113 _private member_ `TArray<TUniquePtr<FSlateTextureAtlasD3D>> PrecachedTextureAtlases;` — Static texture atlases
- L116 _private member_ `TArray<TUniquePtr<FSlateD3DTexture>> NonAtlasedTextures;` — Static non atlased textures
- L119 _private member_ `TUniquePtr<FSlateVectorGraphicsCache> VectorGraphicsCache;` — Cache for vector graphic atlases

#### struct `FSlateD3DTextureManager::FDynamicTextureResource`  
`struct FDynamicTextureResource`  
_L100-107_
- desc: Represents a dynamic resource for rendering
- L102 _public member_ `FSlateShaderResourceProxy* Proxy;`
- L103 _public member_ `FSlateD3DTexture* D3DTexture;`
- L105 _public prototype_ `FDynamicTextureResource( FSlateD3DTexture* ExistingTexture );`
- L106 _public prototype_ `~FDynamicTextureResource();`

### `Source/Developer/StandaloneRenderer/Private/Windows/D3D/SlateD3DTextures.h` (Private)


#### class `FSlateD3DTexture`  
`class FSlateD3DTexture : public TSlateTexture< TRefCountPtr<ID3D11ShaderResourceView> >, public FSlateUpdatableTexture`  
_L15-70_
- inherits: `TSlateTexture<TRefCountPtr<ID3D11ShaderResourceView>>,FSlateUpdatableTexture`
- desc: Encapsulates a D3D11 texture that can be accessed by a shader
- L18 _public function_ `FSlateD3DTexture( uint32 InSizeX, uint32 InSizeY ) : TSlateTexture() , SizeX(InSizeX) , SizeY(InSizeY)`
- L26 _public function_ `FSlateD3DTexture() : TSlateTexture() , SizeX(0) , SizeY(0)`
- L35 _public function_ `~FSlateD3DTexture()`
- L40 _public prototype_ `void Init( DXGI_FORMAT InFormat, D3D11_SUBRESOURCE_DATA* InitalData = NULL, bool bUpdatable = false, bool bUseStagingTexture = false );`
- L41 _public prototype_ `void Init(void* ShareHandle);` — shared handle variant
- L43 _public function_ `virtual void Cleanup() override`
- L45 _public function_ `uint32 GetWidth() const`
- L46 _public function_ `uint32 GetHeight() const`
- L48 _public function_ `TRefCountPtr<ID3D11Texture2D> GetTextureResource() const`
- L51 _public function_ `virtual FSlateShaderResource* GetSlateResource() override` — FSlateUpdatableTexture interface
- L52 _public prototype_ `virtual void ResizeTexture( uint32 Width, uint32 Height ) override;`
- L53 _public prototype_ `virtual void UpdateTexture(const TArray<uint8>& Bytes) override;`
- L54 _public function_ `virtual void UpdateTextureThreadSafe(const TArray<uint8>& Bytes) override`
- L55 _public prototype_ `virtual void UpdateTextureThreadSafeRaw(uint32 Width, uint32 Height, const void* Buffer, const FIntRect& Dirty = FIntRect()) override;`
- L56 _public prototype_ `virtual void UpdateTextureThreadSafeWithTextureData(FSlateTextureData* TextureData) override;`
- L57 _public prototype_ `virtual void UpdateTextureThreadSafeWithKeyedTextureHandle(void* TextureHandle, int KeyLockVal, int KeyUnlockVal, const FIntRect& Dirty = FIntRect()) override;`
- L60 _private prototype_ `void UpdateTextureRaw(const void* Buffer, const FIntRect& Dirty);` — Helper method used by the different UpdateTexture* methods
- L62 _private member_ `TRefCountPtr<ID3D11Texture2D> D3DTexture;` — Actual texture.  In D3D the SRV is used by the shader so our parent class holds that
- L64 _private member_ `TRefCountPtr<ID3D11Texture2D> StagingTexture;` — Texture for doing staged updating of the texture contents.
- L65 _private member_ `uint32 SizeX;`
- L66 _private member_ `uint32 SizeY;`
- L67 _private member_ `uint32 BytesPerPixel;`
- L69 _private member_ `void* ShareHandle;`

#### class `FSlateTextureAtlasD3D`  
`class FSlateTextureAtlasD3D : public FSlateTextureAtlas`  
_L72-87_
- inherits: `FSlateTextureAtlas`
- L75 _public prototype_ `FSlateTextureAtlasD3D( uint32 Width, uint32 Height, uint32 StrideBytes, ESlateTextureAtlasPaddingStyle PaddingStyle );`
- L76 _public prototype_ `~FSlateTextureAtlasD3D();`
- L79 _public prototype_ `virtual void ConditionalUpdateTexture() override;`
- L80 _public function_ `virtual void ReleaseResources() override`
- L82 _public function_ `FSlateD3DTexture* GetAtlasTexture() const`
- L84 _private prototype_ `void InitAtlasTexture();`
- L86 _private member_ `FSlateD3DTexture* AtlasTexture;`

#### class `FSlateFontAtlasD3D`  
`class FSlateFontAtlasD3D : public FSlateFontAtlas`  
_L92-107_
- inherits: `FSlateFontAtlas`
- desc: Representation of a texture for fonts in which characters are packed tightly based on their bounding rectangle
- L95 _public prototype_ `FSlateFontAtlasD3D(uint32 Width, uint32 Height, ESlateFontAtlasContentType InContentType);`
- L96 _public prototype_ `~FSlateFontAtlasD3D();`
- L99 _public prototype_ `virtual void ConditionalUpdateTexture();` — FSlateFontAtlas interface
- L100 _public function_ `virtual class FSlateShaderResource* GetSlateTexture() const override`
- L101 _public function_ `virtual class FTextureResource* GetEngineTexture() override`
- L102 _public function_ `virtual void ReleaseResources() override`
- L106 _private member_ `FSlateD3DTexture* FontTexture;` — Texture used for rendering

### `Source/Developer/StandaloneRenderer/Private/Windows/D3D/SlateD3DVertexBuffer.h` (Private)


#### class `FSlateD3DVertexBuffer`  
`class FSlateD3DVertexBuffer`  
_L12-42_
- desc: Vertex buffer containing all Slate vertices
- L15 _public prototype_ `FSlateD3DVertexBuffer();`
- L16 _public prototype_ `~FSlateD3DVertexBuffer();`
- L19 _public prototype_ `void CreateBuffer( uint32 InStride );` — Initializes the vertex buffers RHI resource.
- L22 _public prototype_ `void DestroyBuffer();` — Releases the vertex buffers RHI resource.
- L25 _public function_ `uint32 GetBufferSize() const` — Returns the size of the buffer in bytes.
- L28 _public prototype_ `void ResizeBuffer( uint32 NewSize );` — Resizes the buffer to the passed in size.  Preserves internal data
- L30 _public prototype_ `void* Lock( uint32 Offset );`
- L31 _public prototype_ `void Unlock();`
- L33 _public function_ `TRefCountPtr<ID3D11Buffer> GetResource()`
- L36 _private member_ `uint32 BufferSize;` — The size of the buffer in bytes.
- L37 _private member_ `uint32 Stride;`
- L38 _private member_ `TRefCountPtr<ID3D11Buffer> Buffer;`
- L40 _private prototype_ `FSlateD3DVertexBuffer( const FSlateD3DVertexBuffer& );` — Hidden copy methods.
- L41 _private prototype_ `void operator=(const FSlateD3DVertexBuffer& );`

### `Source/Developer/StandaloneRenderer/Public/IOS/SlateOpenGLESView.h` (Public)
_(no declarations extracted)_

### `Source/Developer/StandaloneRenderer/Public/StandaloneRenderer.h` (Public)


#### Free symbols / members of external scopes

- L12 _prototype_ `TSharedRef<FSlateRenderer> GetStandardStandaloneRenderer();` — Single function to create the standalone renderer for the running platform
