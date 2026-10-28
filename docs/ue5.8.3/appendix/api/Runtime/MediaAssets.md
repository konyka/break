# Runtime / MediaAssets

- module root: `Source/Runtime/MediaAssets`
- headers: 24; symbols: 759
- symbol kinds: class=24, delegate=10, enum=13, enumerator=56, function=50, member=216, namespace=6, prototype=364, struct=13, typedef=3, variable=4
- PrivateDependencyModuleNames: RHI, RenderCore, Renderer
- PrivateIncludePathModuleNames: TargetPlatform
- PublicDependencyModuleNames: AudioExtensions, AudioMixer, Core, CoreUObject, Engine, Media, MediaUtils, SignalProcessing

### `Source/Runtime/MediaAssets/Internal/Assets/MediaSequenceInfo.h` (Internal)


#### struct `FMediaSequenceInfo`  
`struct FMediaSequenceInfo`  
_L15-46_
- desc: Holds size, tiling, and mip-count information for a single tiled media sequence. Note: This type is engine-internal. It lives in MediaAssets/Internal so that media plugins (ImgMedia, MediaPlate, future preview viewports) can share it without forcing it into the public API surface.
- L18 _public member_ `FName Name;` — Name of this sequence.
- L21 _public member_ `FIntPoint Dim = FIntPoint::ZeroValue;` — Pixel dimensions of this sequence.
- L24 _public member_ `int32 NumMipLevels = 0;` — Number of mip levels.
- L27 _public member_ `FMediaTextureTilingDescription TilingDescription;` — Tiling description.
- L30 _public function_ `FORCEINLINE bool IsTiled() const` — True if the sequence has more than one tile in either dimension.
- L36 _public function_ `FORCEINLINE FVector2f GetPartialTileNum(const int32 InMipLevel = 0) const` — Get the fractional number of tiles, optionally at a specified mip level.

### `Source/Runtime/MediaAssets/Internal/Assets/MediaTileSelection.h` (Internal)


#### struct `FMediaTileSelection`  
`struct FMediaTileSelection`  
_L15-96_
- desc: Describes which tiles of a single mip level are visible. Note: Engine-internal. See MediaSequenceInfo.h for the visibility rationale.
- L24 _public prototype_ `FMediaTileSelection(int32 InNumTilesX, int32 InNumTilesY, bool bInDefaultVisibility = false);` — Create and initialize a new tile selection. @param InNumTilesX Horizontal tile count. @param InNumTilesY Vertical tile count. @param bInDefaultVisibility Optional visibility for the entire region.
- L34 _public prototype_ `static FMediaTileSelection CreateForTargetMipLevel(const FIntPoint& InMipZeroResolution, const FIntPoint& InTileSize, int32 InTargetMipLevel, bool bInDefaultVisibility = false);` — Create and initialize a new tile selection, adjusting tile counts for the specified higher mip level. @param InMipZeroResolution Pixel resolution of Mip 0. @param InTileSize Dimensions of tiles in pixels. @param InTargetMipLevel Higher target mip level for the selection (usually 1 and above). @param bInDefaultVisibility Optional visibility for the entire region.
- L36 _public prototype_ `FMediaTileSelection() = default;`
- L37 _public prototype_ `~FMediaTileSelection() noexcept = default;`
- L39 _public prototype_ `FMediaTileSelection(const FMediaTileSelection&) = default;`
- L40 _public prototype_ `FMediaTileSelection& operator=(const FMediaTileSelection&) = default;`
- L42 _public prototype_ `FMediaTileSelection(FMediaTileSelection&&) = default;`
- L43 _public prototype_ `FMediaTileSelection& operator=(FMediaTileSelection&&) = default;`
- L46 _public prototype_ `bool IsAnyVisible() const;` — True if any tile is visible.
- L49 _public prototype_ `bool IsVisible(int32 InTileCoordX, int32 InTileCoordY) const;` — True if a specific tile is visible.
- L52 _public prototype_ `bool Contains(const FMediaTileSelection& InOther) const;` — True if the currently visible tiles are also visible in another selection.
- L55 _public prototype_ `void Include(const FMediaTileSelection& InOther);` — Combine the current selection with another (assumes they are the same size).
- L58 _public prototype_ `void SetVisible(int32 InTileCoordX, int32 InTileCoordY);` — Mark a tile as visible.
- L61 _public prototype_ `TArray<FIntPoint> GetVisibleCoordinates() const;` — Returns the list of visible tile coordinates, in row and column order.
- L67 _public prototype_ `TArray<FIntRect> GetVisibleRegions(const FMediaTileSelection* InCurrentTileSelection = nullptr) const;` — Returns a calculated list of contiguous visible tile regions. Only provides regions for the missing tiles if CurrentTileSelection is specified.
- L70 _public prototype_ `FIntRect GetVisibleRegion() const;` — Return the rectangular region bounding the visible tiles.
- L73 _public prototype_ `int32 NumVisibleTiles() const;` — Returns the number of visible tiles.
- L76 _public function_ `FIntPoint GetDimensions() const` — Returns the overall dimensions in number of tiles.
- L80 _private function_ `FORCEINLINE static int32 ToIndex(const int32 InCoordX, const int32 InCoordY, const FIntPoint& InDim)` — Flat index for (CoordX, CoordY) given InDim.X stride.
- L86 _private member_ `TBitArray<> Tiles;` — Visibility bit per tile, row-major.
- L89 _private member_ `FIntPoint Dimensions;` — Tile counts (X, Y).
- L92 _private member_ `mutable FIntRect CachedVisibleRegion;` — Cached result of GetVisibleRegion; rebuilt when bCachedVisibleRegionDirty is true.
- L95 _private member_ `mutable bool bCachedVisibleRegionDirty = false;` — True when CachedVisibleRegion is stale and must be recomputed.

### `Source/Runtime/MediaAssets/Internal/Assets/MediaTileVisibility.h` (Internal)


#### struct `FMediaTileVisibilityRequest`  
`struct FMediaTileVisibilityRequest`  
_L20-33_
- desc: Per-frame tile-visibility output produced by a single visibility provider. Multiple requests are merged (bitwise-OR'd) by a per-loader resolver before being handed to the underlying media reader. Note: Engine-internal. See MediaSequenceInfo.h for the visibility rationale.
- L23 _public member_ `TMap<int32, FMediaTileSelection> VisibleTiles;` — Visible tiles per mip level.
- L26 _public member_ `int32 MipLevelToUpscale = -1;` — Minimum mip level to upscale into lower-quality mips, or -1 if disabled.
- L29 _public prototype_ `void Reset();` — Reset to an empty state, preserving allocated capacity.
- L32 _public prototype_ `void Merge(const FMediaTileVisibilityRequest& InOther);` — Merge another request into this one (OR tiles, min non-negative upscale level).

#### class `IMediaTileVisibilityProvider`  
`class IMediaTileVisibilityProvider`  
_L46-79_
- desc: Pure interface implemented by anything that wants to influence which tiles a tiled / mipped media sequence loads (mesh-on-plane, sphere, 2D preview viewport, UMG widget, etc.). Providers are owned by their consumer. The visibility resolver holds them by TWeakPtr and prunes when IsAlive() returns false. Most implementations inherit from FMediaTileVisibilityProvider (below) to pick up the thread-safe default implementation of the OnInputsChanged trio.
- L49 _public prototype_ `virtual ~IMediaTileVisibilityProvider() = default;`
- L63 _public prototype_ `virtual void GatherVisibleTiles(const FMediaSequenceInfo& InSequenceInfo, FMediaTileVisibilityRequest& OutRequest) const = 0;` — Append this provider's visible tiles for the given sequence. Threading contract: invoked by the resolver without any resolver lock held, potentially from worker threads, potentially concurrently with other providers. Implementations MUST NOT call back into the owning resolver synchronously (RegisterProvider / UnregisterProvider / InvalidateSnapshot / GetSnapshot) and MUST be safe to call concurrently with other invocations on the same instance. @param InSequenceInfo  Description of the sequence (size, mips, tiling). @param OutRequest      Output - tiles are merged into this; do not clear.
- L67 _public prototype_ `virtual bool IsAlive() const = 0;` — Returns true if the underlying consumer is still alive (mesh not garbage-collected, etc).
- L76 _public prototype_ `virtual FDelegateHandle AddOnInputsChangedHandler(const FSimpleDelegate& InHandler) = 0;` — OnInputsChanged signals that consumer-pushed inputs to GatherVisibleTiles have changed (widget resize, mip pin, etc.) so the next snapshot rebuild may yield a different tile set. Implementations must be thread-safe against concurrent Add / Remove / Broadcast on the same provider. Handlers MUST NOT call back into Add/Remove/Broadcast on the same provider.
- L77 _public prototype_ `virtual void RemoveOnInputsChangedHandler(FDelegateHandle InHandle) = 0;`
- L78 _public prototype_ `virtual void BroadcastOnInputsChanged() = 0;`

#### class `FMediaTileVisibilityProvider`  
`class FMediaTileVisibilityProvider : public IMediaTileVisibilityProvider`  
_L87-122_
- inherits: `IMediaTileVisibilityProvider`
- desc: Abstract base providing the standard thread-safe OnInputsChanged trio for IMediaTileVisibilityProvider implementations. Inherit from this rather than IMediaTileVisibilityProvider directly unless you need custom threading.
- L91 _public function_ `virtual FDelegateHandle AddOnInputsChangedHandler(const FSimpleDelegate& InHandler) override final`
- L97 _public function_ `virtual void RemoveOnInputsChangedHandler(FDelegateHandle InHandle) override final`
- L103 _public function_ `virtual void BroadcastOnInputsChanged() override final`
- L120 _private member_ `FCriticalSection OnInputsChangedMutex;`
- L121 _private member_ `FSimpleMulticastDelegate OnInputsChanged;`

### `Source/Runtime/MediaAssets/Internal/MediaSourcePathValidation.h` (Internal)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace MediaAssets` (scope `UE`)
- L25 _prototype_ `bool IsUNCPath(FStringView InPath);` (scope `UE::MediaAssets`) — Returns true if InPath denotes a Windows UNC / network path, by literal- prefix scan after stripping a leading file:// scheme (case-insensitive). Detected forms: - \\server\share        (standard UNC) - //server/share        (forward-slash UNC) - \\?\UNC\server\...    (Win32 file namespace UNC) - \\.\UNC\server\...    (Win32 device namespace UNC) - file://<any of the above> Limitations: mapped network drives (e.g. Z:\ from 'net use') cannot be detected from the path string alone. On non-Windows platforms, network mounts appear as ordinary local paths (/Volumes/<share> on macOS, arbitrary mount points on Linux) and are also not detected. Callers that need cross-platform mount-aware detection must supplement this check.
- L37 _prototype_ `bool AreNetworkPathsAllowed();` (scope `UE::MediaAssets`) — Returns true if media sources may resolve UNC / network paths. Controlled by the MediaAssets.AllowNetworkPaths console variable; online game servers can disable it to harden against UNC path injection through media-source assets. The cvar is read-only at runtime: it must be set in DefaultEngine.ini or on the command line before the MediaAssets module loads. Console writes after startup are silently ignored.
- L44 _prototype_ `bool IsSourcePathAllowed(FStringView InPath);` (scope `UE::MediaAssets`) — Returns true if InPath is acceptable as a media source path: either it is not a UNC / network path, or network paths are currently allowed by the MediaAssets.AllowNetworkPaths console variable.

### `Source/Runtime/MediaAssets/Private/MediaAssetsPrivate.h` (Private)


#### Free symbols / members of external scopes

- L10 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogMediaAssets, Log, All);` — Declares a log category for this module.
- L10 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogMediaAssets, Log, All);` — Declares a log category for this module.

### `Source/Runtime/MediaAssets/Private/Misc/MediaTextureResource.h` (Private)


#### class `FMediaTextureResource`  
`class FMediaTextureResource : public FRenderTarget , public FTextureResource`  
_L60-304_
- inherits: `FRenderTarget,FTextureResource`
- desc: Texture resource type for media textures.
- L77 _public prototype_ `FMediaTextureResource(UMediaTexture& InOwner, FIntPoint& InOwnerDim, SIZE_T& InOwnerSize, FLinearColor InClearColor, FGuid InTextureGuid, bool bEnableGenMips, uint8 InNumMips, UE::Color::EColorSpace OverrideColorSpaceType);` — Creates and initializes a new instance. @param InOwner The Movie texture object to create a resource for (must not be nullptr). @param InOwnerDim Reference to the width and height of the texture that owns this resource (will be updated by resource). @param InOwnerSize Reference to the size in bytes of the texture that owns this resource (will be updated by resource). @param InClearColor The initial clear color. @param InTextureGuid The initial external texture GUID. @param bEnableGenMips If true mips generation will be enabled (possibly optimizing for NumMips == 1 case) @param InNumMips The initial number of mips to be generated for the output texture
- L80 _public prototype_ `virtual ~FMediaTextureResource() = default;` — Virtual destructor.
- L132 _public prototype_ `void Render(const FRenderParams& Params);` — Render the texture resource. This method is called on the render thread by the MediaTexture that owns this texture resource to clear or redraw the resource using the given parameters. @param Params Render parameters.
- L138 _public prototype_ `void FlushPendingData();` — Flush out any pending data like texture samples waiting for retirement etc. @note this call can stall for noticable amounts of time under certain circumstances
- L141 _public prototype_ `void SetJustInTimeRenderParams(const FRenderParams& InJustInTimeRenderParams);` — Sets the just in time render parameters for later use when JustInTimeRender() gets called
- L144 _public prototype_ `void ResetJustInTimeRenderParams();` — Clears the just in time render params, in which case calling JustInTimeRender() would have no effect
- L147 _public prototype_ `void JustInTimeRender();` — Render the texture using the cached FRenderParams. Call from render thread only.
- L153 _public prototype_ `virtual FIntPoint GetSizeXY() const override;`
- L159 _public prototype_ `virtual FString GetFriendlyName() const override;`
- L160 _public prototype_ `virtual uint32 GetSizeX() const override;`
- L161 _public prototype_ `virtual uint32 GetSizeY() const override;`
- L162 _public prototype_ `virtual void InitRHI(FRHICommandListBase& RHICmdList) override;`
- L163 _public prototype_ `virtual void ReleaseRHI() override;`
- L173 _protected prototype_ `void ClearTexture(FRHICommandListImmediate& RHICmdList, const FLinearColor& ClearColor, bool SrgbOutput);` — Clear the texture using the given clear color. @param ClearColor The clear color to use. @param SrgbOutput Whether the output texture is in sRGB color space.
- L183 _protected prototype_ `void ConvertSample(FRHICommandListImmediate& RHICmdList, const TSharedPtr<IMediaTextureSample, ESPMode::ThreadSafe>& Sample, const FLinearColor& ClearColor, uint8 InTargetNumMips);` — Render the given texture sample by converting it on the GPU. @param Sample The texture sample to convert. @param ClearColor The clear color to use for the output texture. @param Number of mips @see CopySample
- L185 _protected prototype_ `void ConvertTextureToOutput(FRHICommandListImmediate& RHICmdList, FRHITexture* InputTexture, const TSharedPtr<IMediaTextureSample, ESPMode::ThreadSafe>& Sample);`
- L196 _protected prototype_ `void CopySample(FRHICommandListImmediate& RHICmdList, const TSharedPtr<IMediaTextureSample, ESPMode::ThreadSafe>& Sample, const FLinearColor& ClearColor, uint8 InTargetNumMips, const FGuid & TextureGUID);` — Render the given texture sample by using it as or copying it to the render target. @param Sample The texture sample to copy. @param ClearColor The clear color to use for the output texture. @param SrgbOutput Whether the output texture is in sRGB color space. @param Number of mips @see ConvertSample
- L199 _protected prototype_ `void UpdateResourceSize();` — Calculates the current resource size and notifies the owner texture.
- L206 _protected prototype_ `void UpdateTextureReference(FRHICommandListImmediate& RHICmdList, FRHITexture* NewTexture);` — Set the owner's texture reference to the given texture. @param NewTexture The texture to set.
- L217 _protected prototype_ `void CreateIntermediateRenderTarget(FRHICommandListImmediate& RHICmdList, const FIntPoint & InDim, EPixelFormat InPixelFormat, bool bInSRGB, const FLinearColor & InClearColor, uint8 InNumMips, bool bNeedsUAVSupport, ETextureCreateFlags InExtraCreateFlags = ETextureCreateFlags::None);` — Create/update intermediate render target as needed. If no color conversion is needed, the RT will be used as the output. InExtraCreateFlags - additional ETextureCreateFlags OR'd into the create flags before the FRHITextureCreateDesc is constructed. Lets a caller request extra capabilities on the intermediate target (e.g. TexCreate_ReservedResource for sparse residency) without affecting samples that don't opt in. Default of None preserves existing behavior for all current callers.
- L224 _protected prototype_ `void CacheNextAvailableSampleTime(const TSharedPtr<FMediaTextureSampleSource, ESPMode::ThreadSafe>& InSampleQueue) const;` — Caches next available sample from queue in MediaTexture owner to keep single consumer access @param InSampleQueue SampleQueue to query sample information from
- L227 _protected prototype_ `void SetupSampler();` — Setup sampler state from owner's settings as needed
- L230 _protected prototype_ `void CopyFromExternalTexture(FRHICommandListImmediate& RHICmdList, const TSharedPtr <IMediaTextureSample, ESPMode::ThreadSafe>& Sample, const FGuid & TextureGUID);` — Copy to local buffer from external texture
- L232 _protected prototype_ `bool RequiresConversion(const TSharedPtr<IMediaTextureSample, ESPMode::ThreadSafe>& Sample, uint8 InTargetNumMips) const;`
- L233 _protected prototype_ `bool RequiresConversion(const FTextureRHIRef& SampleTexture, const FIntPoint & OutputDim, uint8 InTargetNumMips) const;`
- L236 _protected prototype_ `void GetColorSpaceConversionMatrixForSample(const TSharedPtr<IMediaTextureSample, ESPMode::ThreadSafe> Sample, FMatrix44f& ColorSpaceMtx);` — Compute CS conversion martix based on sample's data
- L241 _private member_ `bool bUsesImageExternal;` — Platform uses GL/ES ImageExternal
- L244 _private member_ `bool Cleared;` — Whether the texture has been cleared.
- L247 _private member_ `FLinearColor CurrentClearColor;` — Tracks the current clear color.
- L250 _private member_ `FGuid InitialTextureGuid;` — The external texture GUID to use when initializing this resource.
- L253 _private member_ `TRefCountPtr<FRHITexture> InputTarget;` — Input render target if the texture samples don't provide one (for conversions).
- L256 _private member_ `TRefCountPtr<FRHITexture> IntermediateTarget;` — Holds the intermediate render target if the texture samples don't provide one, or final render target when not using a texture sample color converter.
- L259 _private member_ `TRefCountPtr<FRHITexture> OutputTarget;` — Output render target where the texture sample color converter writes.
- L262 _private member_ `UMediaTexture& Owner;` — The media texture that owns this resource.
- L265 _private member_ `FIntPoint& OwnerDim;` — Reference to the owner's texture dimensions field.
- L268 _private member_ `SIZE_T& OwnerSize;` — Reference to the owner's texture size field.
- L271 _private member_ `bool bEnableGenMips;` — Enable mips generation
- L274 _private member_ `uint8 CurrentNumMips;` — Current number of mips to be generated as output
- L277 _private member_ `ESamplerFilter CurrentSamplerFilter;` — Current texture sampler filter value
- L280 _private member_ `float CurrentMipMapBias;` — Current texture sampler mip bias.
- L283 _private member_ `TWeakPtr<FMediaPlayerFacade, ESPMode::ThreadSafe> PlayerFacadePtr;` — The current media player facade to get video samples from.
- L286 _private member_ `TSharedPtr<IMediaTextureSample, ESPMode::ThreadSafe> CurrentSample;` — cached media sample to postpone releasing it until the next sample rendering as it can get overwritten due to asynchronous rendering
- L289 _private member_ `TSharedRef<FPriorSamples, ESPMode::ThreadSafe> PriorSamples;` — prior samples not yet ready for retirement as GPU may still actively use them
- L291 _private member_ `FCriticalSection PriorSamplesCS;` — prior samples CS
- L294 _private member_ `TRefCountPtr<IPooledRenderTarget> MipGenerationCache;` — cached params etc. for use with mip generator
- L297 _private member_ `TUniquePtr<FRenderParams> JustInTimeRenderParams;` — Cached FRenderParams, used when JustInTimeRender() gets called.
- L300 _private member_ `TUniquePtr<UE::Color::FColorSpace> OverrideColorSpace;` — Destination colorspace to override standard project "working color space'. Used primarily by Slate which remains sRGB-only.
- L303 _private member_ `bool bRecreateOutputTarget = false;` — Used to keep track of whether we should re-create the output target because the intermediate target has changed.

#### struct `FMediaTextureResource::FRenderParams`  
`struct FRenderParams`  
_L85-122_
- desc: Parameters for the Render method.
- L88 _public prototype_ `FRenderParams() = default;`
- L89 _public prototype_ `FRenderParams(const FRenderParams& InOther) = default;`
- L90 _public prototype_ `FRenderParams(FRenderParams&& InOther) = default;`
- L91 _public prototype_ `FRenderParams& operator=(const FRenderParams&) = default;`
- L92 _public prototype_ `FRenderParams& operator=(FRenderParams&&) = default;`
- L96 _public member_ `bool CanClear;` — Whether the texture can be cleared.
- L99 _public member_ `FLinearColor ClearColor;` — The clear color to use when clearing the texture.
- L102 _public member_ `FGuid CurrentGuid;` — The texture's current external texture GUID.
- L105 _public member_ `FGuid PreviousGuid;` — The texture's previously used external texture GUID.
- L108 _public member_ `float Rate;` — The player's play rate.
- L111 _public member_ `TWeakPtr<FMediaTextureSampleSource, ESPMode::ThreadSafe> SampleSource;` — The player facade that provides the video samples to render.
- L115 _public member_ `uint8 NumMips;` — `UE_DEPRECATED(5.6, "Unused since UMediaTexture NumMips is now deprecated.")` — Number of mips wanted
- L118 _public member_ `FMediaTimeStamp Time;` — The time of the video frame to render (in player's clock).
- L121 _public member_ `TSharedPtr<IMediaTextureSample, ESPMode::ThreadSafe> TextureSample;` — Explicit texture sample to render - if set time will be ignored

#### Free symbols / members of external scopes

- L32 _namespace_ `namespace UE`
- L32 _namespace_ `namespace MediaTexture` (scope `UE`)
- L32 _namespace_ `namespace Private` (scope `UE::MediaTexture`)
- L35 _prototype_ `uint8 ClampNumMips(uint8 InNumMips, const FIntPoint& InDim);` (scope `UE::MediaTexture::Private`) — Clamps the number of mips to the maximum needed mips given the texture dimensions.
- L44 _prototype_ `uint8 CalcGeneratedNumMips(const IMediaTextureSample& InSample, bool bInEnableGenMips);` (scope `UE::MediaTexture::Private`) — @brief Calculates the target number of generated mips for a given sample. @param InSample Decoded sample. @param bInEnableGenMips Indicate if mip generation is enabled. @return Expected number of generated mips.
- L54 _prototype_ `uint8 CalcTextureNumMips(const IMediaTextureSample& InSample, bool bInEnableGenMips);` (scope `UE::MediaTexture::Private`) — @brief Calculates the expected texture resource number of mips for the given sample. Sample source mips take priority over generated ones. @param InSample Decoded sample. @param bInEnableGenMips Indicate if mip generation is enabled. @return Expected number of mips.

### `Source/Runtime/MediaAssets/Public/BaseMediaSource.h` (Public)


#### class `UBaseMediaSource`  
`class UBaseMediaSource : public UMediaSource`  
_L28-67_
- reflection: `UCLASS(Abstract, BlueprintType, hidecategories=(Object), MinimalAPI)`
- inherits: `UMediaSource`
- desc: Base class for concrete media sources.
- L39 _public member_ `TMap<FString, FName> PlatformPlayerNames;` — `UPROPERTY(transient, BlueprintReadWrite, EditAnywhere, Category=Platforms, Meta=(DisplayName="Player Overrides"))` — Override native media player plug-ins per platform (Empty = find one automatically).
- L43 _private member_ `TMap<FGuid, FGuid> BlindPlatformGuidPlayerNames;` — Platform to player plugin GUID mappings that could not be resolved on load (e.g. missing platform support)
- L50 _public prototype_ `virtual void PreSave(FObjectPreSaveContext ObjectSaveContext);`
- L51 _public prototype_ `virtual void GetAssetRegistryTags(FAssetRegistryTagsContext Context) const override;`
- L53 _public prototype_ `virtual void GetAssetRegistryTags(TArray<FAssetRegistryTag>& OutTags) const override;` — `UE_DEPRECATED(5.4, "Implement the version that takes FAssetRegistryTagsContext instead.")`
- L54 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L60 _public prototype_ `virtual FName GetDesiredPlayerName() const override;`
- L66 _private member_ `FName PlayerName;` — `UPROPERTY(transient)` — Name of the desired native media player (Empty = find one automatically).

### `Source/Runtime/MediaAssets/Public/BaseMediaSourceColorSettings.h` (Public)


#### enum `EMediaSourceEncoding`  
`enum class EMediaSourceEncoding : uint8`  
_L15-25_
- reflection: `UENUM()`
- desc: List of source encodings that can be converted to linear. (Integer values match the ETextureSourceEncoding values in TextureDefines.h
- L17 _public enumerator_ `MSE_None = 0 UMETA(DisplayName = "None", ToolTip = "The source encoding is not overridden.")`
- L18 _public enumerator_ `MSE_Linear = 1 UMETA(DisplayName = "Linear", ToolTip = "The source encoding is considered linear.")`
- L19 _public enumerator_ `MSE_sRGB = 2 UMETA(DisplayName = "sRGB", ToolTip = "sRGB source encoding to be linearized")`
- L20 _public enumerator_ `MSE_ST2084 = 3 UMETA(DisplayName = "ST 2084/PQ", ToolTip = "SMPTE ST 2084/PQ source encoding to be linearized")`
- L21 _public enumerator_ `MSE_SLog3 = 12 UMETA(DisplayName = "SLog3", ToolTip = "Sony SLog3 source encoding to be linearized")`
- L22 _public enumerator_ `MSE_HLG = 17 UMETA(DisplayName = "HLG", ToolTip = "HLG (BT.2100): linearized to the [0, 1] range.")`
- L24 _public enumerator_ `MSE_MAX = 18`

#### enum `EMediaReferenceWhite`  
`enum class EMediaReferenceWhite : uint8`  
_L32-40_
- reflection: `UENUM()`
- desc: Reference-white standards to scale HDR media sources so diffuse white lands at UE scene-linear 1.0, and vice-versa.
- L34 _public enumerator_ `MRW_None = 0 UMETA(DisplayName = "None", ToolTip = "The source reference white is not overridden, defer to system/default behavior.")`
- L35 _public enumerator_ `MRW_DisableNormalization = 1 UMETA(DisplayName = "Disable Normalization", ToolTip = "Explicitly preserve input/native scaling.")`
- L36 _public enumerator_ `MRW_BT2408 = 2 UMETA(DisplayName = "BT.2408 (203 nits)", ToolTip = "ITU-R BT.2408 Reference White. 203 cd/m2 for PQ (ST2084), 75% signal for HLG scale to scene linear white (1.0).")`
- L37 _public enumerator_ `MRW_BT1886 = 3 UMETA(DisplayName = "BT.1886 (100 nits)", ToolTip = "ITU-R BT.1886 SDR reference white (100 cd/m2). Scales PQ (100-nit paper white) and HLG (in-house 100-nit convention on a 1000 cd/m2 BT.2100 reference display) to scene linear white (1.0).")`
- L39 _public enumerator_ `MRW_MAX = 4 UMETA(Hidden)`

#### struct `FMediaSourceColorSettings`  
`struct FMediaSourceColorSettings`  
_L44-96_
- reflection: `USTRUCT(BlueprintType)`
- desc: Manual definition of media source color space & encoding.
- L48 _public function_ `FMediaSourceColorSettings() : EncodingOverride(EMediaSourceEncoding::MSE_None) , ColorSpaceOverride(ETextureColorSpace::TCS_None) , RedChromaticityCoordinate(FVector2D::ZeroVector) , GreenChromaticityCoordinate(FVector2D::ZeroVector) , BlueChromaticityCoordinate(FVector2D::ZeroVector) , WhiteChromaticityCoordinate(FVector2D::ZeroVector) , ChromaticAdaptationMethod(static_cast<ETextureChromaticAdaptationMethod>(UE::Color::DEFAULT_CHROMATIC_ADAPTATION_METHOD)) , ReferenceWhiteOverride(EMediaReferenceWhite::MRW_None)`
- L61 _public member_ `EMediaSourceEncoding EncodingOverride;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ColorManagement)` — Source encoding of the media.
- L65 _public member_ `ETextureColorSpace ColorSpaceOverride;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ColorManagement)` — Source color space of the media.
- L69 _public member_ `FVector2D RedChromaticityCoordinate;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ColorManagement, meta = (EditCondition = "ColorSpaceOverride == ETextureColorSpace::TCS_Custom", EditConditionHides))` — Red chromaticity coordinate of the source color space.
- L73 _public member_ `FVector2D GreenChromaticityCoordinate;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ColorManagement, meta = (EditCondition = "ColorSpaceOverride == ETextureColorSpace::TCS_Custom", EditConditionHides))` — Green chromaticity coordinate of the source color space.
- L77 _public member_ `FVector2D BlueChromaticityCoordinate;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ColorManagement, meta = (EditCondition = "ColorSpaceOverride == ETextureColorSpace::TCS_Custom", EditConditionHides))` — Blue chromaticity coordinate of the source color space.
- L81 _public member_ `FVector2D WhiteChromaticityCoordinate;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ColorManagement, meta = (EditCondition = "ColorSpaceOverride == ETextureColorSpace::TCS_Custom", EditConditionHides))` — White chromaticity coordinate of the source color space.
- L85 _public member_ `ETextureChromaticAdaptationMethod ChromaticAdaptationMethod;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ColorManagement, meta = (EditCondition = "ColorSpaceOverride != ETextureColorSpace::TCS_None"))` — Chromatic adaption method applied if the source white point differs from the working color space white point.
- L90 _public member_ `EMediaReferenceWhite ReferenceWhiteOverride;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ColorManagement, meta = (EditCondition = "EncodingOverride == EMediaSourceEncoding::MSE_ST2084 || EncodingOverride == EMediaSourceEncoding::MSE_HLG", EditConditionHides))` — Reference HDR white standard used to scale input signals to scene linear white (1.0).
- L94 _public prototype_ `void UpdateColorSpaceChromaticities();` — Update the chromaticity coordinates member variables based on the color space choice (unless custom).

#### struct `FNativeMediaSourceColorSettings`  
`struct FNativeMediaSourceColorSettings : public IMediaOptions::FDataContainer`  
_L99-158_
- inherits: `IMediaOptions::FDataContainer`
- desc: Engine-native color source settings container for media option.
- L102 _public prototype_ `FNativeMediaSourceColorSettings();` — Constructor
- L105 _public prototype_ `~FNativeMediaSourceColorSettings();` — Destructor
- L108 _public prototype_ `FNativeMediaSourceColorSettings(const FNativeMediaSourceColorSettings& Other);` — Copy constructor
- L111 _public prototype_ `FNativeMediaSourceColorSettings& operator=(const FNativeMediaSourceColorSettings& Other);` — Assignment operator
- L114 _public prototype_ `void Update(const FMediaSourceColorSettings& InSettings);` — Updates the native settings from user-controlled settings.
- L117 _public function_ `inline bool HasEncodingOverride() const` — Has encoding override.
- L120 _public function_ `inline UE::Color::EEncoding GetEncodingOverride() const` — Color encoding override getter.
- L123 _public function_ `inline void SetEncodingOverride(UE::Color::EEncoding InEncodingOverride)` — Color encoding override setter.
- L126 _public function_ `inline UE::Color::EReferenceWhite GetReferenceWhiteOverride() const` — Reference-white override getter. See FMediaSourceColorSettings::ReferenceWhiteOverride for semantics.
- L129 _public function_ `inline void SetReferenceWhiteOverride(UE::Color::EReferenceWhite InReferenceWhiteOverride)` — Reference-white override setter.
- L132 _public prototype_ `bool HasColorSpaceOverride() const;` — Has color space override.
- L135 _public prototype_ `const UE::Color::FColorSpace& GetColorSpaceOverride(const UE::Color::FColorSpace& InDefaultColorSpace) const;` — Color space override getter.
- L138 _public prototype_ `void SetColorSpaceOverride(const UE::Color::FColorSpace& InColorSpaceOverride);` — Color space override setter.
- L141 _public function_ `inline UE::Color::EChromaticAdaptationMethod GetChromaticAdaptationMethod() const` — Chromatic adaptation getter.
- L145 _private member_ `std::atomic<UE::Color::EEncoding> EncodingOverride;` — Manual source encoding override.
- L148 _private member_ `std::atomic<UE::Color::EReferenceWhite> ReferenceWhiteOverride;` — Companion reference-white override. EReferenceWhite::None means no normalization.
- L151 _private member_ `TOptional<UE::Color::FColorSpace> ColorSpaceOverride;` — Manual source color space override.
- L154 _private member_ `std::atomic<UE::Color::EChromaticAdaptationMethod> ChromaticAdaptationMethod;` — Chromatic adapation to be used on manual source color space override.
- L157 _private member_ `mutable FCriticalSection ColorSpaceCriticalSection;` — Protects color space override variable.

### `Source/Runtime/MediaAssets/Public/FileMediaSource.h` (Public)


#### class `UFileMediaSource`  
`class UFileMediaSource : public UBaseMediaSource`  
_L21-104_
- reflection: `UCLASS(BlueprintType, MinimalAPI)`
- inherits: `UBaseMediaSource`
- L34 _public member_ `FString FilePath;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=File, AssetRegistrySearchable)` — The path to the media file to be played. @see SetFilePath
- L39 _public member_ `bool PrecacheFile;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=File, AdvancedDisplay)` — Load entire media file into memory and play from there (if possible).
- L49 _public function_ `const FString& GetFilePath() const` — Get the path to the media file to be played. @return The file path. @see GetFullPath, SetFilePath
- L60 _public prototype_ `FString GetFullPath() const;` — Get the full path to the file. @return The full file path. @return GetFilePath
- L72 _public prototype_ `void SetFilePath(const FString& Path);` — `UFUNCTION(BlueprintCallable, Category="Media|FileMediaSource")` — Set the path to the media file that this source represents. Automatically converts full paths to media sources that reside in the Engine's or project's /Content/Movies directory into relative paths. @param Path The path to set. @see FilePath, GetFilePath
- L75 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L82 _public prototype_ `virtual bool GetMediaOption(const FName& Key, bool DefaultValue) const override;`
- L83 _public prototype_ `virtual bool HasMediaOption(const FName& Key) const override;`
- L89 _public prototype_ `virtual FString GetUrl() const override;`
- L90 _public prototype_ `virtual bool Validate() const override;`
- L93 _public prototype_ `virtual void GetDetailsPanelInfoElements(TArray<FInfoElement>& OutInfoElements) const override;`
- L98 _public member_ `static FName PrecacheFileOption;` — Name of the PrecacheFile media option.
- L101 _private prototype_ `void ResolveFullPath() const;`
- L102 _private prototype_ `void ClearResolvedFullPath() const;`
- L103 _private member_ `mutable FString ResolvedFullPath;` — this is a cached variable updated in ResolveFullPath hence mutable

### `Source/Runtime/MediaAssets/Public/IMediaAssetsModule.h` (Public)


#### class `IMediaAssetsModule`  
`class IMediaAssetsModule : public IModuleInterface`  
_L15-79_
- inherits: `IModuleInterface`
- desc: Interface for the MediaAssets module.
- L20 _public prototype_ `DECLARE_DELEGATE_RetVal_TwoParams(UMediaPlayer*, FOnGetPlayerFromObject, UObject*, UObject*& );` — Delegate to get a player from a UObject.
- L22 _public prototype_ `DECLARE_DELEGATE_RetVal(UObject*, FOnCreateMediaSourceRenderer);` — Delegate to create an object that implements IMediaSourceRendererInterface.
- L24 _public prototype_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FMediaStateChangedDelegate, const TArray<FString>& , uint8 , bool );` — Delegate that reacts to change in Media state (Play, Stop, Pause etc.)
- L32 _public prototype_ `virtual int32 RegisterGetPlayerFromObject(const FOnGetPlayerFromObject& Delegate) = 0;` — Plugins should call this so they can provide a function to get a media player from an object. @param Delegate		Delegate to get a media player. @return ID to pass in to UnregisterGetPlayerFromObject.
- L39 _public prototype_ `virtual void UnregisterGetPlayerFromObject(int32 DelegateID) = 0;` — Call this to unregister a delegate. @param DelegateID	ID returned from RegisterGetPlayerFromObject.
- L51 _public prototype_ `virtual UMediaPlayer* GetPlayerFromObject(UObject* Object, UObject*& PlayerProxy) = 0;` — Call this to get a media player (and proxy object) from an object. This will query any plugins that have called RegisterGetPlayerFromObject. The proxy object will implement IMediaPlayerProxyInterface. @param Object		Object to get the player from. @param PlayerProxy	Will be set to the proxy object (or nullptr if none). @return Media player, or nullptr if none found.
- L56 _public prototype_ `virtual void RegisterCreateMediaSourceRenderer(const FOnCreateMediaSourceRenderer& Delegate) = 0;` — Register a delegate to create an object that implements IMediaSourceRendererInterface.
- L61 _public prototype_ `virtual void UnregisterCreateMediaSourceRenderer() = 0;` — Unregisters the delegate passed in with RegisterCreateMediaSourceRenderer.
- L64 _public prototype_ `virtual FDelegateHandle RegisterOnMediaStateChangedEvent(FMediaStateChangedDelegate::FDelegate InStateChangedDelegate) = 0;` — Subscribes to the event that is called whenever any of Media state changes (such as play button was pressed).
- L67 _public prototype_ `virtual void UnregisterOnMediaStateChangedEvent(FDelegateHandle InHandle) = 0;` — Removes event handling.
- L70 _public prototype_ `virtual void BroadcastOnMediaStateChangedEvent(const TArray<FString>& InActorsPathNames, uint8 EnumState, bool bRemoteBroadcast = false) = 0;` — Broadcasts the event to all subscribers. InActorsPathNames are the paths of selected Medias in the scene.
- L75 _public prototype_ `virtual UObject* CreateMediaSourceRenderer() = 0;` — Creates an object that implements IMediaSourceRendererInterface.
- L78 _public prototype_ `virtual ~IMediaAssetsModule() = default;` — Virtual destructor.

#### Free symbols / members of external scopes

- L20 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(UMediaPlayer*, FOnGetPlayerFromObject, UObject*, UObject*& );` — Delegate to get a player from a UObject.
- L22 _delegate_ `DECLARE_DELEGATE_RetVal(UObject*, FOnCreateMediaSourceRenderer);` — Delegate to create an object that implements IMediaSourceRendererInterface.
- L24 _delegate_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FMediaStateChangedDelegate, const TArray<FString>& , uint8 , bool );` — Delegate that reacts to change in Media state (Play, Stop, Pause etc.)

### `Source/Runtime/MediaAssets/Public/MediaComponent.h` (Public)


#### class `UMediaComponent`  
`class UMediaComponent : public UActorComponent`  
_L13-41_
- reflection: `UCLASS(Category="Media", hideCategories=(Media, Activation), MinimalAPI)`
- inherits: `UActorComponent`
- L18 _public prototype_ `UMediaComponent(const FObjectInitializer& ObjectInitializer);`
- L22 _public prototype_ `UMediaPlayer* GetMediaPlayer() const;` — `UFUNCTION(BlueprintPure, Category="Media")` — Get the media player that this component owns
- L26 _public prototype_ `UMediaTexture* GetMediaTexture() const;` — `UFUNCTION(BlueprintPure, Category="Media")` — Get the media texture that this component owns, bound to its media player.
- L30 _private prototype_ `virtual void OnRegister() override;`
- L36 _private member_ `TObjectPtr<UMediaTexture> MediaTexture;` — `UPROPERTY(Category="Media", Instanced, Transient, BlueprintGetter=GetMediaTexture)` — This component's media texture
- L40 _private member_ `TObjectPtr<UMediaPlayer> MediaPlayer;` — `UPROPERTY(Category="Media", Instanced, Transient, BlueprintGetter=GetMediaPlayer, Interp)` — This component's media player

### `Source/Runtime/MediaAssets/Public/MediaPlayer.h` (Public)


#### enum `EMediaPlayerTrack`  
`enum class EMediaPlayerTrack : uint8`  
_L54-76_
- reflection: `UENUM(BlueprintType)`
- desc: Media track types. Note: Keep this in sync with EMediaTrackType
- L57 _public enumerator_ `Audio` — Audio track.
- L60 _public enumerator_ `Caption` — Caption track.
- L63 _public enumerator_ `Metadata` — Metadata track.
- L66 _public enumerator_ `Script` — Script track.
- L69 _public enumerator_ `Subtitle` — Subtitle track.
- L72 _public enumerator_ `Text` — Text track.
- L75 _public enumerator_ `Video` — Video track.

#### enum `EMediaTimeRangeBPType`  
`enum class EMediaTimeRangeBPType : uint8`  
_L83-91_
- reflection: `UENUM(BlueprintType)`
- desc: Blueprint usable enum of EMediaTimeRangeType
- L86 _public enumerator_ `Absolute = (uint8)EMediaTimeRangeType::Absolute` — Total absolute time range as defined by the media.
- L89 _public enumerator_ `Current = (uint8)EMediaTimeRangeType::Current` — Current time range of the media, set by media internal means or through API calls.

#### class `UMediaTimeStampInfo`  
`class UMediaTimeStampInfo : public UObject`  
_L95-108_
- reflection: `UCLASS(BlueprintType, hidecategories = (Object), MinimalAPI)`
- inherits: `UObject`
- L101 _public function_ `UMediaTimeStampInfo() : Time(FTimespan::Zero()), SequenceIndex(0)`
- L104 _public member_ `FTimespan Time;` — `UPROPERTY(BlueprintReadOnly, Category = "Media|Time")`
- L107 _public member_ `int64 SequenceIndex;` — `UPROPERTY(BlueprintReadOnly, Category = "Media|Time")`

#### struct `FMediaMetadataItemBPT`  
`struct FMediaMetadataItemBPT`  
_L111-127_
- reflection: `USTRUCT(BlueprintType)`
- L117 _public member_ `FString LanguageCode;` — `UPROPERTY(BlueprintReadOnly, Category = "Media|Metadata")`
- L120 _public member_ `FString MimeType;` — `UPROPERTY(BlueprintReadOnly, Category = "Media|Metadata")`
- L123 _public member_ `FString StringData;` — `UPROPERTY(BlueprintReadOnly, Category = "Media|Metadata")`
- L126 _public member_ `TArray<uint8> BinaryData;` — `UPROPERTY(BlueprintReadOnly, Category = "Media|Metadata")`

#### struct `FMediaMetadataItemsBPT`  
`struct FMediaMetadataItemsBPT`  
_L130-136_
- reflection: `USTRUCT(BlueprintType)`
- L135 _public member_ `TArray<FMediaMetadataItemBPT> Items;` — `UPROPERTY(BlueprintReadOnly, Category = "Media|Metadata")`

#### class `FMediaPlayerProxy`  
`class FMediaPlayerProxy : public Audio::TProxyData<FMediaPlayerProxy>`  
_L141-165_
- inherits: `Audio::TProxyData<FMediaPlayerProxy>`
- desc: Proxy implementation for Metasound integration
- L144 _public prototype_ `IMPL_AUDIOPROXY_CLASS(FMediaPlayerProxy);`
- L146 _public prototype_ `explicit FMediaPlayerProxy(UMediaPlayer* Player);`
- L148 _public prototype_ `FMediaPlayerProxy(const FMediaPlayerProxy& Other);`
- L150 _public prototype_ `~FMediaPlayerProxy();`
- L152 _public function_ `TSharedPtr<FMediaPlayerFacade, ESPMode::ThreadSafe> GetPlayerFacade() const`
- L163 _private member_ `TWeakPtr<FMediaPlayerFacade, ESPMode::ThreadSafe> PlayerFacade;`
- L164 _private member_ `uint32 TypeHash = INDEX_NONE;`

#### class `UMediaPlayer`  
`class UMediaPlayer : public UObject , public IAudioProxyDataFactory`  
_L173-1543_
- reflection: `UCLASS(BlueprintType, hidecategories=(Object), MinimalAPI)`
- inherits: `UObject,IAudioProxyDataFactory`
- desc: Implements a media player asset that can play movies and other media sources.
- L190 _public prototype_ `bool CanPause() const;` — `UFUNCTION(BlueprintCallable, Category="Media|MediaPlayer")` — Check whether media playback can be paused right now. Playback can be paused if the media supports pausing and if it is currently playing. @return true if pausing playback can be paused, false otherwise. @see CanPlay, Pause
- L203 _public prototype_ `bool CanPlaySource(UMediaSource* MediaSource);` — `UFUNCTION(BlueprintCallable, Category = "Media|MediaPlayer")` — Check whether the specified media source can be played by this player. If a desired player name is set for this player, it will only check whether that particular player type can play the specified source. @param MediaSource The media source to check. @return true if the media source can be opened, false otherwise. @see CanPlayUrl, SetDesiredPlayerName
- L215 _public prototype_ `bool CanPlayUrl(const FString& Url);` — `UFUNCTION(BlueprintCallable, Category="Media|MediaPlayer")` — Check whether the specified URL can be played by this player. If a desired player name is set for this player, it will only check whether that particular player type can play the specified URL. @param Url The URL to check. @see CanPlaySource, SetDesiredPlayerName
- L223 _public prototype_ `void Close();` — `UFUNCTION(BlueprintCallable, Category="Media|MediaPlayer")` — Close the currently open media, if any. @see OnMediaClosed, OpenPlaylist, OpenPlaylistIndex, OpenSource, OpenUrl, Pause, Play
- L234 _public prototype_ `int32 GetAudioTrackChannels(int32 TrackIndex, int32 FormatIndex) const;` — `UFUNCTION(BlueprintCallable, Category = "Media|MediaPlayer")` — Get the number of channels in the specified audio track. @param TrackIndex Index of the audio track, or INDEX_NONE for the selected one. @param FormatIndex Index of the track format, or INDEX_NONE for the selected one. @return Number of channels. @see GetAudioTrackSampleRate, GetAudioTrackType
- L245 _public prototype_ `int32 GetAudioTrackSampleRate(int32 TrackIndex, int32 FormatIndex) const;` — `UFUNCTION(BlueprintCallable, Category = "Media|MediaPlayer")` — Get the sample rate of the specified audio track. @param TrackIndex Index of the audio track, or INDEX_NONE for the selected one. @param FormatIndex Index of the track format, or INDEX_NONE for the selected one. @return Samples per second. @see GetAudioTrackChannels, GetAudioTrackType
- L256 _public prototype_ `FString GetAudioTrackType(int32 TrackIndex, int32 FormatIndex) const;` — `UFUNCTION(BlueprintCallable, Category="Media|MediaPlayer")` — Get the type of the specified audio track format. @param TrackIndex The index of the track, or INDEX_NONE for the selected one. @param FormatIndex Index of the track format, or INDEX_NONE for the selected one. @return Audio format type string. @see GetAudioTrackSampleRate, GetAudioTrackSampleRate
- L265 _public prototype_ `FName GetDesiredPlayerName() const;` — `UFUNCTION(BlueprintCallable, Category = "Media|MediaPlayer")` — Get the name of the current desired native player. @return The name of the desired player, or NAME_None if not set. @see SetDesiredPlayerName
- L274 _public prototype_ `FTimespan GetDuration() const;` — `UFUNCTION(BlueprintCallable, Category="Media|MediaPlayer")` — Get the media's duration. @return A time span representing the duration. @see GetTime, Seek
- L283 _public prototype_ `float GetHorizontalFieldOfView() const;` — `UFUNCTION(BlueprintCallable, Category="Media|MediaPlayer")` — Get the current horizontal field of view (only for 360 videos). @return Horizontal field of view (in Euler degrees). @see GetVerticalFieldOfView, GetViewRotation, SetHorizontalFieldOfView
- L292 _public prototype_ `virtual FText GetMediaName() const;` — `UFUNCTION(BlueprintCallable, Category="Media|MediaPlayer")` — Get the human readable name of the currently loaded media source. @return Media source name, or empty text if no media is opened @see GetPlayerName, GetUrl
- L302 _public prototype_ `int32 GetNumTracks(EMediaPlayerTrack TrackType) const;` — `UFUNCTION(BlueprintCallable, Category="Media|MediaPlayer")` — Get the number of tracks of the given type. @param TrackType The type of media tracks. @return Number of tracks. @see GetNumTrackFormats, GetSelectedTrack, SelectTrack
- L313 _public prototype_ `int32 GetNumTrackFormats(EMediaPlayerTrack TrackType, int32 TrackIndex) const;` — `UFUNCTION(BlueprintCallable, Category="Media|MediaPlayer")` — Get the number of formats of the specified track. @param TrackType The type of media tracks. @param TrackIndex The index of the track. @return Number of formats. @see GetNumTracks, GetSelectedTrack, SelectTrack
- L322 _public prototype_ `FName GetPlayerName() const;` — `UFUNCTION(BlueprintCallable, Category="Media|MediaPlayer")` — Get the name of the current native media player. @return Player name, or NAME_None if not available. @see GetMediaName
- L334 _public function_ `UMediaPlaylist* GetPlaylist() const` — `UFUNCTION(BlueprintCallable, Category="Media|MediaPlayer")` — Get the current play list. Media players always have a valid play list. In C++ code you can use the GetPlaylistRef to get a reference instead of a pointer to it. @return The play list. @see GetPlaylistIndex, GetPlaylistRef
- L347 _public function_ `int32 GetPlaylistIndex() const` — `UFUNCTION(BlueprintCallable, Category = "Media|MediaPlayer")` — Get the current play list index. @return Play list index. @see GetPlaylist
- L359 _public prototype_ `float GetRate() const;` — `UFUNCTION(BlueprintCallable, Category="Media|MediaPlayer")` — Get the media's current playback rate. @return The playback rate. @see SetRate, SupportsRate
- L369 _public prototype_ `int32 GetSelectedTrack(EMediaPlayerTrack TrackType) const;` — `UFUNCTION(BlueprintCallable, Category="Media|MediaPlayer")` — Get the index of the currently selected track of the given type. @param TrackType The type of track to get. @return The index of the selected track, or INDEX_NONE if no track is active. @see GetNumTracks, GetTrackFormat, SelectTrack
- L379 _public prototype_ `void GetSupportedRates(TArray<FFloatRange>& OutRates, bool Unthinned) const;` — `UFUNCTION(BlueprintCallable, Category="Media|MediaPlayer")` — Get the supported playback rates. @param Unthinned Whether the rates are for unthinned playback. @param OutRates Will contain the the ranges of supported rates. @see SetRate, SupportsRate
- L388 _public prototype_ `FTimespan GetTime() const;` — `UFUNCTION(BlueprintCallable, Category="Media|MediaPlayer")` — Get the media's current playback time. @return Playback time. @see GetDuration, Seek
- L397 _public prototype_ `FTimespan GetDisplayTime() const;` — `UFUNCTION(BlueprintCallable, Category = "Media|MediaPlayer")` — Get the media's current playback time as appropriate for display. @return Playback time. @see GetDuration, Seek
- L406 _public prototype_ `UMediaTimeStampInfo* GetTimeStamp() const;` — `UFUNCTION(BlueprintCallable, Category = "Media|MediaPlayer")` — Get the media's current playback timestamp. @return Playback timestamp. @see GetDuration, Seek
- L415 _public prototype_ `UMediaTimeStampInfo* GetDisplayTimeStamp() const;` — `UFUNCTION(BlueprintCallable, Category = "Media|MediaPlayer")` — Get the media's current playback timestamp as appropriate for display. @return Playback timestamp. @see GetDuration, Seek
- L428 _public prototype_ `TOptional<FTimecode> GetVideoTimecode() const;` — Get the timecode from the video track, if one is available. If available, the returned value will be the timecode of the sample most recently sent into the video sink. @return Most recently delivered video timecode from the video track. @note Even if timecode is available, the value returned reflects the timecode that most recently delivered to the video sink. During a seek operation the timecode will be unset.
- L438 _public prototype_ `TOptional<FTimespan> GetTrackDuration(EMediaPlayerTrack TrackType, int32 TrackIndex) const;` — Gets the duration of a specific track, if available. Availability depends on the media format and player implementation. If unset only the overall media duration can be used. @return An optional time span representing the duration. @see GetDuration
- L449 _public prototype_ `FText GetTrackDisplayName(EMediaPlayerTrack TrackType, int32 TrackIndex) const;` — `UFUNCTION(BlueprintCallable, Category = "Media|MediaPlayer")` — Get the human readable name of the specified track. @param TrackType The type of track. @param TrackIndex The index of the track, or INDEX_NONE for the selected one. @return Display name. @see GetNumTracks, GetTrackLanguage
- L460 _public prototype_ `int32 GetTrackFormat(EMediaPlayerTrack TrackType, int32 TrackIndex) const;` — `UFUNCTION(BlueprintCallable, Category="Media|MediaPlayer")` — Get the index of the active format of the specified track type. @param TrackType The type of track. @param TrackIndex The index of the track, or INDEX_NONE for the selected one. @return The index of the selected format. @see GetNumTrackFormats, GetSelectedTrack, SetTrackFormat
- L471 _public prototype_ `FString GetTrackLanguage(EMediaPlayerTrack TrackType, int32 TrackIndex) const;` — `UFUNCTION(BlueprintCallable, Category="Media|MediaPlayer")` — Get the language tag of the specified track. @param TrackType The type of track. @param TrackIndex The index of the track, or INDEX_NONE for the selected one. @return Language tag, i.e. "en-US" for English, or "und" for undefined. @see GetNumTracks, GetTrackDisplayName
- L480 _public prototype_ `const FString& GetUrl() const;` — `UFUNCTION(BlueprintCallable, Category="Media|MediaPlayer")` — Get the URL of the currently loaded media, if any. @return Media URL, or empty string if no media was loaded. @see OpenUrl
- L489 _public prototype_ `float GetVerticalFieldOfView() const;` — `UFUNCTION(BlueprintCallable, Category="Media|MediaPlayer")` — Get the current vertical field of view (only for 360 videos). @return Vertical field of view (in Euler degrees), or 0.0 if not available. @see GetHorizontalFieldOfView, GetViewRotation, SetVerticalFieldOfView
- L500 _public prototype_ `float GetVideoTrackAspectRatio(int32 TrackIndex, int32 FormatIndex) const;` — `UFUNCTION(BlueprintCallable, Category = "Media|MediaPlayer")` — Get the aspect ratio of the specified video track. @param TrackIndex Index of the video track, or INDEX_NONE for the selected one. @param FormatIndex Index of the track format, or INDEX_NONE for the selected one. @return Aspect ratio. @see GetVideoTrackDimensions, GetVideoTrackFrameRate, GetVideoTrackFrameRates, GetVideoTrackType
- L511 _public prototype_ `FIntPoint GetVideoTrackDimensions(int32 TrackIndex, int32 FormatIndex) const;` — `UFUNCTION(BlueprintCallable, Category="Media|MediaPlayer")` — Get the current dimensions of the specified video track. @param TrackIndex The index of the track, or INDEX_NONE for the selected one. @param FormatIndex Index of the track format, or INDEX_NONE for the selected one. @return Video dimensions (in pixels). @see GetVideoTrackAspectRatio, GetVideoTrackFrameRate, GetVideoTrackFrameRates, GetVideoTrackType
- L522 _public prototype_ `float GetVideoTrackFrameRate(int32 TrackIndex, int32 FormatIndex) const;` — `UFUNCTION(BlueprintCallable, Category="Media|MediaPlayer")` — Get the frame rate of the specified video track. @param TrackIndex The index of the track, or INDEX_NONE for the selected one. @param FormatIndex Index of the track format, or INDEX_NONE for the selected one. @return Frame rate (in frames per second). @see GetVideoTrackAspectRatio, GetVideoTrackDimensions, GetVideoTrackFrameRates, GetVideoTrackType, SetVideoTrackFrameRate
- L533 _public prototype_ `FFloatRange GetVideoTrackFrameRates(int32 TrackIndex, int32 FormatIndex) const;` — `UFUNCTION(BlueprintCallable, Category="Media|MediaPlayer")` — Get the supported range of frame rates of the specified video track. @param TrackIndex The index of the track, or INDEX_NONE for the selected one. @param FormatIndex Index of the track format, or INDEX_NONE for the selected one. @return Frame rate range (in frames per second). @see GetVideoTrackAspectRatio, GetVideoTrackDimensions, GetVideoTrackFrameRate, GetVideoTrackType
- L544 _public prototype_ `FString GetVideoTrackType(int32 TrackIndex, int32 FormatIndex) const;` — `UFUNCTION(BlueprintCallable, Category="Media|MediaPlayer")` — Get the type of the specified video track format. @param TrackIndex The index of the track, or INDEX_NONE for the selected one. @param FormatIndex Index of the track format, or INDEX_NONE for the selected one. @return Video format type string. @see GetVideoTrackAspectRatio, GetVideoTrackDimensions, GetVideoTrackFrameRate, GetVideoTrackFrameRates
- L553 _public prototype_ `FRotator GetViewRotation() const;` — `UFUNCTION(BlueprintCallable, Category="Media|MediaPlayer")` — Get the current view rotation (only for 360 videos). @return View rotation, or zero rotator if not available. @see GetHorizontalFieldOfView, GetVerticalFieldOfView, SetViewRotation
- L562 _public prototype_ `FTimespan GetTimeDelay() const;` — `UFUNCTION(BlueprintCallable, Category="Media|MediaPlayer")` — Delay of the player's time. @return Delay added to the player's time used to manually sync multiple sources. @see SetTimeDelay
- L575 _public prototype_ `bool HasError() const;` — `UFUNCTION(BlueprintCallable, Category="Media|MediaPlayer")` — Check whether the player is in an error state. When the player is in an error state, no further operations are possible. The current media must be closed, and a new media source must be opened before the player can be used again. Errors are usually caused by faulty media files or interrupted network connections. @see IsReady
- L584 _public prototype_ `bool IsBuffering() const;` — `UFUNCTION(BlueprintCallable, Category="Media|MediaPlayer")` — Check whether playback is buffering data. @return true if looping, false otherwise. @see IsConnecting, IsLooping, IsPaused, IsPlaying, IsPreparing, IsReady
- L593 _public prototype_ `bool IsConnecting() const;` — `UFUNCTION(BlueprintCallable, Category="Media|MediaPlayer")` — Check whether the player is currently connecting to a media source. @return true if connecting, false otherwise. @see IsBuffering, IsLooping, IsPaused, IsPlaying, IsPreparing, IsReady
- L602 _public prototype_ `bool IsLooping() const;` — `UFUNCTION(BlueprintCallable, Category="Media|MediaPlayer")` — Check whether playback is looping. @return true if looping, false otherwise. @see IsBuffering, IsConnecting, IsPaused, IsPlaying, IsPreparing, IsReady, SetLooping
- L611 _public prototype_ `bool IsPaused() const;` — `UFUNCTION(BlueprintCallable, Category="Media|MediaPlayer")` — Check whether playback is currently paused. @return true if playback is paused, false otherwise. @see CanPause, IsBuffering, IsConnecting, IsLooping, IsPaused, IsPlaying, IsPreparing, IsReady, Pause
- L620 _public prototype_ `bool IsPlaying() const;` — `UFUNCTION(BlueprintCallable, Category="Media|MediaPlayer")` — Check whether playback has started. @return true if playback has started, false otherwise. @see CanPlay, IsBuffering, IsConnecting, IsLooping, IsPaused, IsPlaying, IsPreparing, IsReady, Play
- L629 _public prototype_ `bool IsPreparing() const;` — `UFUNCTION(BlueprintCallable, Category="Media|MediaPlayer")` — Check whether the media is currently opening or buffering. @return true if playback is being prepared, false otherwise. @see CanPlay, IsBuffering, IsConnecting, IsLooping, IsPaused, IsPlaying, IsReady, Play
- L637 _public prototype_ `bool IsClosed() const;` — `UFUNCTION(BlueprintCallable, Category="Media|MediaPlayer")` — Whether media is currently closed. @return true if media is closed, false otherwise.
- L649 _public prototype_ `bool IsReady() const;` — `UFUNCTION(BlueprintCallable, Category="Media|MediaPlayer")` — Check whether media is ready for playback. A player is ready for playback if it has a media source opened that finished preparing and is not in an error state. @return true if media is ready, false otherwise. @see HasError, IsBuffering, IsConnecting, IsLooping, IsPaused, IsPlaying, IsPreparing
- L661 _public prototype_ `bool Next();` — `UFUNCTION(BlueprintCallable, Category="Media|MediaPlayer")` — Open the next item in the current play list. The player will start playing the new media source if it was playing something previously, otherwise it will only open the media source. @return true on success, false otherwise. @see Close, OpenUrl, OpenSource, Play, Previous, SetPlaylist
- L676 _public prototype_ `bool OpenFile(const FString& FilePath);` — `UFUNCTION(BlueprintCallable, Category="Media|MediaPlayer")` — Opens the specified media file path. A return value of true indicates that the player will attempt to open the media, but it may fail to do so later for other reasons, i.e. if a connection to the media server timed out. Use the OnMediaOpened and OnMediaOpenFailed delegates to detect if and when the media is ready! @param FilePath The file path to open. @return true if the file path will be opened, false otherwise. @see GetUrl, Close, OpenPlaylist, OpenPlaylistIndex, OpenSource, OpenUrl, Reopen
- L686 _public function_ `bool OpenPlaylist(UMediaPlaylist* InPlaylist)` — `UFUNCTION(BlueprintCallable, Category="Media|MediaPlayer")` — Open the first media source in the specified play list. @param InPlaylist The play list to open. @return true if the source will be opened, false otherwise. @see Close, OpenFile, OpenPlaylistIndex, OpenSource, OpenUrl, Reopen
- L700 _public prototype_ `bool OpenPlaylistIndex(UMediaPlaylist* InPlaylist, int32 Index);` — `UFUNCTION(BlueprintCallable, Category="Media|MediaPlayer")` — Open a particular media source in the specified play list. @param InPlaylist The play list to open. @param Index The index of the source to open. @return true if the source will be opened, false otherwise. @see Close, OpenFile, OpenPlaylist, OpenSource, OpenUrl, Reopen
- L715 _public prototype_ `bool OpenSource(UMediaSource* MediaSource);` — `UFUNCTION(BlueprintCallable, Category="Media|MediaPlayer")` — Open the specified media source. A return value of true indicates that the player will attempt to open the media, but it may fail to do so later for other reasons, i.e. if a connection to the media server timed out. Use the OnMediaOpened and OnMediaOpenFailed delegates to detect if and when the media is ready! @param MediaSource The media source to open. @return true if the source will be opened, false otherwise. @see Close, OpenFile, OpenPlaylist, OpenPlaylistIndex, OpenUrl, Reopen
- L731 _public prototype_ `bool OpenSourceWithOptions(UMediaSource* MediaSource, const FMediaPlayerOptions& Options);` — `UFUNCTION(BlueprintCallable, Category="Media|MediaPlayer")` — Open the specified media source with supplied options applied. A return value of true indicates that the player will attempt to open the media, but it may fail to do so later for other reasons, i.e. if a connection to the media server timed out. Use the OnMediaOpened and OnMediaOpenFailed delegates to detect if and when the media is ready! @param MediaSource The media source to open. @param Options The media player options to apply. @return true if the source will be opened, false otherwise. @see Close, OpenFile, OpenPlaylist, OpenPlaylistIndex, OpenUrl, Reopen
- L744 _public prototype_ `void OpenSourceLatent(const UObject* WorldContextObject, struct FLatentActionInfo LatentInfo, UMediaSource* MediaSource, const FMediaPlayerOptions& Options, bool& bSuccess);` — `UFUNCTION(BlueprintCallable, Category = "Media|MediaPlayer", meta = (Latent, LatentInfo = "LatentInfo", WorldContext = "WorldContextObject"))` — Open the specified media source with options using a latent action. A result of true indicates that the player successfully completed all requested operations. @param MediaSource The media source to open. @param Options The media player options to apply. @param bSuccess  All requested operations have completed successfully. @see Close, OpenFile, OpenPlaylist, OpenPlaylistIndex, OpenUrl, Reopen
- L759 _public prototype_ `bool OpenUrl(const FString& Url);` — `UFUNCTION(BlueprintCallable, Category="Media|MediaPlayer")` — Opens the specified media URL. A return value of true indicates that the player will attempt to open the media, but it may fail to do so later for other reasons, i.e. if a connection to the media server timed out. Use the OnMediaOpened and OnMediaOpenFailed delegates to detect if and when the media is ready! @param Url The URL to open. @return true if the URL will be opened, false otherwise. @see GetUrl, Close, OpenFile, OpenPlaylist, OpenPlaylistIndex, OpenSource, Reopen
- L770 _public prototype_ `bool Pause();` — `UFUNCTION(BlueprintCallable, Category="Media|MediaPlayer")` — Pauses media playback. This is the same as setting the playback rate to 0.0. @return true if playback is being paused, false otherwise. @see CanPause, Close, Next, Play, Previous, Rewind, Seek
- L781 _public prototype_ `bool Play();` — `UFUNCTION(BlueprintCallable, Category="Media|MediaPlayer")` — Starts media playback. This is the same as setting the playback rate to 1.0. @return true if playback is starting, false otherwise. @see CanPlay, GetRate, Next, Pause, Previous, SetRate
- L787 _public prototype_ `void PlayAndSeek();` — `UFUNCTION(BlueprintCallable, Category="Media|MediaPlayer")` — Starts playback from the media opened event, but can be used elsewhere.
- L799 _public prototype_ `bool Previous();` — `UFUNCTION(BlueprintCallable, Category="Media|MediaPlayer")` — Open the previous item in the current play list. The player will start playing the new media source if it was playing something previously, otherwise it will only open the media source. @return true on success, false otherwise. @see Close, Next, OpenUrl, OpenSource, Play, SetPlaylist
- L808 _public prototype_ `bool Reopen();` — `UFUNCTION(BlueprintCallable, Category="Media|MediaPlayer")` — Reopens the currently opened media or play list. @return true if the media will be opened, false otherwise. @see Close, Open, OpenFile, OpenPlaylist, OpenPlaylistIndex, OpenSource, OpenUrl
- L819 _public prototype_ `bool Rewind();` — `UFUNCTION(BlueprintCallable, Category="Media|MediaPlayer")` — Rewinds the media to the beginning. This is the same as seeking to zero time. @return true if rewinding, false otherwise. @see GetTime, Seek
- L829 _public prototype_ `bool Seek(const FTimespan& Time);` — `UFUNCTION(BlueprintCallable, Category="Media|MediaPlayer")` — Seeks to the specified playback time. @param Time The playback time to set. @return true on success, false otherwise. @see GetTime, Rewind
- L848 _public prototype_ `bool Scrub(const FTimespan& Time);` — `UFUNCTION(BlueprintCallable, Category="Media|MediaPlayer")` — Seeks to the specified playback time as soon as possible. If the player is currently seeking, the new seek request will be queued and executed as soon as the current one is completed. It will guarantee that at least one sample of the previous seek makes it to the sample queue. if new seek requests are performed in rapid succession (as in scrubbing), the requests are aggregated and only the most recent request will be performed. As a result, OnSeekCompleted event is only sent for the request that got performed. If the player is not currently seeking, Seek will be called immediately. @param Time The playback time to set. @return true on success, false otherwise. @see Seek
- L863 _public prototype_ `bool SelectTrack(EMediaPlayerTrack TrackType, int32 TrackIndex);` — `UFUNCTION(BlueprintCallable, Category="Media|MediaPlayer")` — Select the active track of the given type. The selected track will use its currently active format. Active formats will be remembered on a per track basis. The first available format is active by default. To switch the track format, use SetTrackFormat instead. @param TrackType The type of track to select. @param TrackIndex The index of the track to select, or INDEX_NONE to deselect. @return true if the track was selected, false otherwise. @see GetNumTracks, GetSelectedTrack, SetTrackFormat
- L874 _public prototype_ `void SetBlockOnTime(const FTimespan& Time);` — `UFUNCTION(BlueprintCallable, Category = "Media|MediaPlayer")` — Set the time on which to block. If set, this player will block in TickInput or TickFetch until the video sample for the specified time are actually available. @param Time The time to block on, or FTimespan::MinValue to disable.
- L884 _public prototype_ `void SetBlockOnTimeRange(const TRange<FTimespan>& TimeRange);` — Set the time range on which to block. If set, this player will block in TickInput or TickFetch until the video sample for the specified time are actually available. @param TimeRange The time range to block on, or empty range to disable.
- L893 _public prototype_ `void SetDesiredPlayerName(FName PlayerName);` — `UFUNCTION(BlueprintCallable, Category = "Media|MediaPlayer")` — Set the name of the desired native player. @param PlayerName The name of the player to set. @see GetDesiredPlayerName
- L903 _public prototype_ `bool SetLooping(bool Looping);` — `UFUNCTION(BlueprintCallable, Category="Media|MediaPlayer")` — Enables or disables playback looping. @param Looping Whether playback should be looped. @return true on success, false otherwise. @see IsLooping
- L911 _public prototype_ `void SetMediaOptions(const UMediaSource* Options);` — `UFUNCTION(BlueprintCallable, Category = "Media|MediaPlayer")` — Sets the media options used by the player. @param Options Options to pass to the player.
- L921 _public prototype_ `bool SetRate(float Rate);` — `UFUNCTION(BlueprintCallable, Category="Media|MediaPlayer")` — Changes the media's playback rate. @param Rate The playback rate to set. @return true on success, false otherwise. @see GetRate, SupportsRate
- L935 _public prototype_ `bool SetNativeVolume(float Volume);` — `UFUNCTION(BlueprintCallable, Category = "Media|MediaPlayer")` — Set the volume on the native player if not mixing with Sound Wave asset. The SetNativeVolume can be used to change the audio output volume at runtime. Note that not all media player plug-ins may support native audio output on all platforms. @param Volume The volume to set. @return true on success, false otherwise. @see NativeAudioOut
- L951 _public prototype_ `bool SetTrackFormat(EMediaPlayerTrack TrackType, int32 TrackIndex, int32 FormatIndex);` — `UFUNCTION(BlueprintCallable, Category="Media|MediaPlayer")` — Set the format on the specified track. Selecting the format will not switch to the specified track. To switch tracks, use SelectTrack instead. If the track is already selected, the format change will be applied immediately. @param TrackType The type of track to update. @param TrackIndex The index of the track to update. @param FormatIndex The index of the format to select (must be valid). @return true if the track was selected, false otherwise. @see GetNumTrackFormats, GetNumTracks, GetTrackFormat, SelectTrack
- L963 _public prototype_ `bool SetVideoTrackFrameRate(int32 TrackIndex, int32 FormatIndex, float FrameRate);` — `UFUNCTION(BlueprintCallable, Category="Media|MediaPlayer")` — Set the frame rate of the specified video track. @param TrackIndex The index of the track, or INDEX_NONE for the selected one. @param FormatIndex Index of the track format, or INDEX_NONE for the selected one. @param FrameRate The frame rate to set (must be in range of format's supported frame rates). @return true on success, false otherwise. @see GetVideoTrackAspectRatio, GetVideoTrackDimensions, GetVideoTrackFrameRate, GetVideoTrackFrameRates, GetVideoTrackType
- L975 _public prototype_ `bool SetViewField(float Horizontal, float Vertical, bool Absolute);` — `UFUNCTION(BlueprintCallable, Category = "Media|MediaPlayer")` — Set the field of view (only for 360 videos). @param Horizontal Horizontal field of view (in Euler degrees). @param Vertical Vertical field of view (in Euler degrees). @param Whether the field of view change should be absolute (true) or relative (false). @return true on success, false otherwise. @see GetHorizontalFieldOfView, GetVerticalFieldOfView, SetViewRotation
- L986 _public prototype_ `bool SetViewRotation(const FRotator& Rotation, bool Absolute);` — `UFUNCTION(BlueprintCallable, Category = "Media|MediaPlayer")` — Set the view's rotation (only for 360 videos). @param Rotation The desired view rotation. @param Whether the rotation change should be absolute (true) or relative (false). @return true on success, false otherwise. @see GetViewRotation, SetViewField
- L998 _public prototype_ `void SetTimeDelay(FTimespan TimeDelay);` — `UFUNCTION(BlueprintCallable, Category = "Media|MediaPlayer")` — Delay of the player's time. This setting can be used to manually sync multiple sources. Set to 1 seconds, if you would like that Player to play 1 second behind its current time. If the value is too big, it is possible that the player would not hold that frame for that long. @return true on success, false otherwise. @see GetTimeDelay
- L1008 _public prototype_ `bool SupportsRate(float Rate, bool Unthinned) const;` — `UFUNCTION(BlueprintCallable, Category="Media|MediaPlayer")` — Check whether the specified playback rate is supported. @param Rate The playback rate to check. @param Unthinned Whether no frames should be dropped at the given rate. @see SupportsScrubbing, SupportsSeeking
- L1017 _public prototype_ `bool SupportsScrubbing() const;` — `UFUNCTION(BlueprintCallable, Category="Media|MediaPlayer")` — Check whether the currently loaded media supports scrubbing. @return true if scrubbing is supported, false otherwise. @see SupportsRate, SupportsSeeking
- L1026 _public prototype_ `bool SupportsSeeking() const;` — `UFUNCTION(BlueprintCallable, Category="Media|MediaPlayer")` — Check whether the currently loaded media can jump to a certain position. @return true if seeking is supported, false otherwise. @see SupportsRate, SupportsScrubbing
- L1032 _public member_ `FOnMediaPlayerMediaEvent OnEndReached;` — `UPROPERTY(BlueprintAssignable, Category="Media|MediaPlayer", meta = (HideInDetailPanel))` — A delegate that is invoked when playback has reached the end of the media.
- L1036 _public member_ `FOnMediaPlayerMediaEvent OnMediaClosed;` — `UPROPERTY(BlueprintAssignable, Category="Media|MediaPlayer", meta = (HideInDetailPanel))` — A delegate that is invoked when a media source has been closed.
- L1048 _public member_ `FOnMediaPlayerMediaOpened OnMediaOpened;` — `UPROPERTY(BlueprintAssignable, Category="Media|MediaPlayer", meta = (HideInDetailPanel))` — A delegate that is invoked when a media source has been opened. Depending on whether the underlying player implementation opens the media synchronously or asynchronously, this event may be executed before or after the call to OpenSource / OpenUrl returns. @see OnMediaOpenFailed, OnTracksChanged
- L1060 _public member_ `FOnMediaPlayerMediaOpenFailed OnMediaOpenFailed;` — `UPROPERTY(BlueprintAssignable, Category="Media|MediaPlayer", meta = (HideInDetailPanel))` — A delegate that is invoked when a media source has failed to open. This delegate is only executed if OpenSource / OpenUrl returned true and the media failed to open asynchronously later. It is not executed if OpenSource / OpenUrl returned false, indicating an immediate failure. @see OnMediaOpened
- L1068 _public member_ `FOnMediaPlayerMediaEvent OnPlaybackResumed;` — `UPROPERTY(BlueprintAssignable, Category="Media|MediaPlayer", meta = (HideInDetailPanel))` — A delegate that is invoked when media playback has been resumed. @see OnPlaybackSuspended
- L1076 _public member_ `FOnMediaPlayerMediaEvent OnPlaybackSuspended;` — `UPROPERTY(BlueprintAssignable, Category="Media|MediaPlayer", meta = (HideInDetailPanel))` — A delegate that is invoked when media playback has been suspended. @see OnPlaybackResumed
- L1086 _public member_ `FOnMediaPlayerMediaEvent OnSeekCompleted;` — `UPROPERTY(BlueprintAssignable, Category="Media|MediaPlayer", meta = (HideInDetailPanel))` — A delegate that is invoked when a seek operation completed successfully. Depending on whether the underlying player implementation performs seeks synchronously or asynchronously, this event may be executed before or after the call to Seek returns.
- L1094 _public member_ `FOnMediaPlayerMediaEvent OnTracksChanged;` — `UPROPERTY(BlueprintAssignable, Category="Media|MediaPlayer", meta = (HideInDetailPanel))` — A delegate that is invoked when the media track collection changed. @see OnMediaOpened
- L1102 _public member_ `FOnMediaPlayerMediaEvent OnMetadataChanged;` — `UPROPERTY(BlueprintAssignable, Category="Media|MediaPlayer", meta = (HideInDetailPanel))` — A delegate that is invoked when the media metadata changed. @see OnMediaOpened
- L1111 _public member_ `FOnMediaPlayerMediaEvent OnBufferingStart;` — `UPROPERTY(BlueprintAssignable, Category="Media|MediaPlayer", meta = (HideInDetailPanel))` — A delegate that is invoked when the player starts buffering data. This event is not sent by all media players. @see OnBufferingCompleted
- L1120 _public member_ `FOnMediaPlayerMediaEvent OnBufferingCompleted;` — `UPROPERTY(BlueprintAssignable, Category="Media|MediaPlayer", meta = (HideInDetailPanel))` — A delegate that may be invoked when the player completes buffering data. This event should not be relied upon since not all media players support this. @see OnBufferingStart
- L1130 _public prototype_ `bool SupportsPlaybackTimeRange() const;` — `UFUNCTION(BlueprintCallable, Category="Media|MediaPlayer")` — Check whether the player supports playing back of range within the media. @return true if playing back a range is supported, false otherwise. @see GetPlaybackTimeRange, SetPlaybackTimeRange
- L1156 _public prototype_ `TRange<FTimespan> GetPlaybackTimeRange(EMediaTimeRangeType InRangeToGet);` — Returns the current playback range of the media. If playing back a range is not supported, the range returned will be equal to [ 0, GetDuration() ). The media may have an implicit default range provided by the container format or other means without having called SetPlaybackTimeRange(). The media may have internal time values not starting at 0, which are conveyed by the range. Since the range may be only a portion of the media, the duration of the returned range may be less than the media overall duration returned by GetDuration(). For live video streams the range may change dynamically as new content becomes available and old content falls off the timeline. @param InRangeToGet The type of range to get. `Absolute` returns the media's smallest and largest timeline values. Unless continuously changing in a Live stream this is usually the same as [ 0, GetDuration() ]. The base time does not have to be zero though. `Current` returns the currently set range, which is a subset of the absolute range. @return The playback range as queried for. @see SupportsPlaybackTimeRange, SetPlaybackTimeRange, GetDuration
- L1164 _public prototype_ `FFloatInterval GetPlaybackTimeRange(EMediaTimeRangeBPType InRangeToGet);` — `UFUNCTION(BlueprintCallable, Category="Media|MediaPlayer")` — Blueprint accessible version of GetPlaybackTimeRange. This returns the range truncated into a blueprint usable float interval and should not be used for live streams as 32 bit floats can not store wallclock times with enough precision.
- L1179 _public prototype_ `bool SetPlaybackTimeRange(const TRange<FTimespan>& InTimeRange);` — Sets a new media playback range. Has an effect only if SupportsPlaybackTimeRange() returns true and the media supports it. A live stream cannot be constrained to a range. The range will be clamped if necessary to be within the media's absolute time range. Changing the time range may trigger an implicit Seek() depending on where the current playback position is located with regard to the new range. Unless prevented by the media a playback range can be cleared by passing an empty range. @param InTimeRange The new playback range to set. @return true if successful, false otherwise. @see SupportsPlaybackTimeRange, GetPlaybackTimeRange
- L1187 _public prototype_ `bool SetPlaybackTimeRange(FFloatInterval InTimeRange);` — `UFUNCTION(BlueprintCallable, Category="Media|MediaPlayer")` — Blueprint accessible version of SetPlaybackTimeRange(). The range is set through a blueprint usable float interval which may not have enough precision to represent the range accurately.
- L1194 _public prototype_ `void CleanUpBeforeDestroy();` — Clean up before this object is destroyed. Normally you would not need to call this, but if you want to clean up resources before garbage collection (e.g. you are in the editor) then this could be helpful.
- L1201 _public function_ `const FGuid& GetGuid()` — Get the Guid associated with this media player @return The Guid.
- L1215 _public prototype_ `FVariant GetMediaInfo(FName InfoName) const;` — Get information about the media that is playing. Not all formats support all information. Some possible common information is in this file, look for MediaInfoNameSourceNumMips for example. @param	InfoName		Name of the information we want. @returns					Requested information, or empty if not available.
- L1228 _public function_ `template<typename T> bool GetMediaInfo(T& Result, FName InfoName) const` — Templated version of GetMediaInfo. No need to deal with variants. @param	T			Type of the information. @param	Result		If the information is found and is the correct type, then this will be set to its value. It will not be set otherwise. @param	InfoName	Name of the information. @returns				True if the information is found, false if not.
- L1246 _public prototype_ `TSharedPtr<TMap<FString, TArray<TUniquePtr<IMediaMetadataItem>>>, ESPMode::ThreadSafe> GetMediaMetadata() const;` — Get meta data contained in the current stream @return Map with arrays of IMediaMetaDataItem entries describing any metadata found in the current stream @note Listen to EMediaEvent::MetadataChanged to catch updates to this data
- L1254 _public prototype_ `TMap<FString, FMediaMetadataItemsBPT> GetMediaMetadataItems() const;` — `UFUNCTION(BlueprintCallable, Category = "Media|Metadata")` — This is the blueprint accessible version of the GetMediaMetadata. @return Map with arrays of FMediaMetaDataItem entries describing any metadata found in the current stream @note Listen to EMediaEvent::MetadataChanged to catch updates to this data
- L1261 _public prototype_ `TSharedRef<FMediaPlayerFacade, ESPMode::ThreadSafe> GetPlayerFacade() const;` — Get the media player facade that manages low-level media players @return The media player facade.
- L1267 _public prototype_ `void RegisterWithMediaModule();` — Register player with media module to be ticked
- L1272 _public prototype_ `void UnregisterWithMediaModule();` — When the player goes out of scope, make sure to clean up the clock sink
- L1280 _public function_ `UMediaPlaylist& GetPlaylistRef() const` — Get the current play list. @return The play list. @see GetPlaylistIndex, GetPlaylist
- L1291 _public function_ `DECLARE_EVENT_OneParam(UMediaPlayer, FOnMediaEvent, EMediaEvent ) FOnMediaEvent& OnMediaEvent()` — Get an event delegate that is invoked when a media event occurred. @return The delegate.
- L1303 _public prototype_ `void PausePIE();` — Called when PIE has been paused. @see ResumePIE
- L1310 _public prototype_ `void ResumePIE();` — Called when PIE has been resumed. @see PausePIE
- L1317 _public prototype_ `virtual void BeginDestroy() override;`
- L1319 _public prototype_ `virtual FString GetDesc() override;`
- L1320 _public prototype_ `virtual void PostDuplicate(bool bDuplicateForPIE) override;`
- L1321 _public prototype_ `virtual void PostInitProperties() override;`
- L1322 _public prototype_ `virtual void PostLoad() override;`
- L1325 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L1334 _public member_ `static FLazyName MediaInfoNameSourceNumMips;` — Number of mip map levels in the source. Int32.
- L1336 _public member_ `static FLazyName MediaInfoNameSourceNumTiles;` — Number of tiles (X and Y) in the source. IntPoint.
- L1338 _public member_ `static FLazyName MediaInfoNameStartTimecodeValue;` — Start Timecode. SMPTE format (ex: HH:MM:SS:FF) string.
- L1340 _public member_ `static FLazyName MediaInfoNameStartTimecodeFrameRate;` — Start Timecode frame rate. String.
- L1342 _public member_ `static FLazyName MediaInfoNameKeyframeInterval;` — Keyframe interval. Int32.
- L1344 _public member_ `static FLazyName MediaInfoNameVideoDecoderProvider;` — Video decoder provider. String.
- L1346 _public member_ `static FLazyName MediaInfoNameAudioDecoderProvider;` — Audio decoder provider. String.
- L1354 _public member_ `FTimespan CacheAhead;` — `UPROPERTY(BlueprintReadWrite, Category=Caching)` — Duration of samples to cache ahead of the play head. @see CacheBehind, CacheBehindGame
- L1362 _public member_ `FTimespan CacheBehind;` — `UPROPERTY(BlueprintReadWrite, Category=Caching)` — Duration of samples to cache behind the play head (when not running as game). @see CacheAhead, CacheBehindGame
- L1370 _public member_ `FTimespan CacheBehindGame;` — `UPROPERTY(BlueprintReadWrite, Category=Caching)` — Duration of samples to cache behind the play head (when running as game). @see CacheAhead, CacheBehind
- L1384 _public member_ `bool NativeAudioOut;` — `UPROPERTY(BlueprintReadWrite, Category=Output, AdvancedDisplay)` — Output any audio via the operating system's sound mixer instead of a Sound Wave asset. If enabled, the assigned Sound Wave asset will be ignored. The SetNativeVolume function can then be used to change the audio output volume at runtime. Note that not all media player plug-ins may support native audio output on all platforms. @see SetNativeVolume
- L1397 _public member_ `bool PlayOnOpen;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=Playback)` — Automatically start playback after media opened successfully. If disabled, listen to the OnMediaOpened Blueprint event to detect when the media finished opening, and then start playback using the Play function. @see OpenFile, OpenPlaylist, OpenPlaylistIndex, OpenSource, OpenUrl, Play
- L1405 _public member_ `uint32 Shuffle : 1;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=Playback)` — Whether playback should shuffle media sources in the play list. @see OpenPlaylist, OpenPlaylistIndex
- L1412 _public prototype_ `virtual TSharedPtr<Audio::IProxyData> CreateProxyData(const Audio::FProxyDataInitParams& InitParams) override;`
- L1424 _protected member_ `uint32 Loop:1;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category=Playback)` — Whether the player should loop when media playback reaches the end. Use the SetLooping function to change this value at runtime. @see IsLooping, SetLooping
- L1434 _protected member_ `mutable TObjectPtr<UMediaPlaylist> Playlist;` — `UPROPERTY(BlueprintReadOnly, transient, Category=Playback, BlueprintGetter = GetPlayList)` — The play list to use, if any. Use the OpenPlaylist or OpenPlaylistIndex function to change this value at runtime. @see OpenPlaylist, OpenPlaylistIndex
- L1444 _protected member_ `int32 PlaylistIndex;` — `UPROPERTY(BlueprintReadOnly, Category=Playback)` — The current index of the source in the play list being played. Use the Previous and Next methods to change this value at runtime. @see Next, Previous
- L1452 _protected member_ `FTimespan TimeDelay;` — `UPROPERTY(BlueprintReadOnly, Category=Playback)` — Delay of the player's time. @see SetTimeDelay, GetTimeDelay
- L1466 _protected member_ `float HorizontalFieldOfView;` — `UPROPERTY(EditAnywhere, Category=ViewSettings)` — The initial horizontal field of view (in Euler degrees; default = 90). This setting is used only for 360 videos. It determines the portion of the video that is visible at a time. To modify the field of view at runtime in Blueprints, use the SetHorizontalFieldOfView function. @see GetHorizontalFieldOfView, SetHorizontalFieldOfView, VerticalFieldOfView, ViewRotation
- L1481 _protected member_ `float VerticalFieldOfView;` — `UPROPERTY(EditAnywhere, Category=ViewSettings)` — The initial vertical field of view (in Euler degrees; default = 60). This setting is used only for 360 videos. It determines the portion of the video that is visible at a time. To modify the field of view at runtime in Blueprints, use the SetHorizontalFieldOfView function. Please note that some 360 video players may be able to change only the horizontal field of view, and this setting may be ignored. @see GetVerticalFieldOfView, SetVerticalFieldOfView, HorizontalFieldOfView, ViewRotation
- L1495 _protected member_ `FRotator ViewRotation;` — `UPROPERTY(EditAnywhere, Category=ViewSettings)` — The initial view rotation. This setting is used only for 360 videos. It determines the rotation of the video's view. To modify the view orientation at runtime in Blueprints, use the GetViewRotation and SetViewRotation functions. Please note that not all players may support video view rotations. @see GetViewRotation, SetViewRotation, HorizontalFieldOfView, VerticalFieldOfView
- L1498 _private function_ `virtual bool CanBeInCluster() const override`
- L1501 _private prototype_ `void HandlePlayerMediaEvent(EMediaEvent Event);` — Callback for when a media event occurred in the player.
- L1504 _private prototype_ `void SetPlaylistInternal(UMediaPlaylist* InPlaylist) const;` — Sets the playlist and properly handles cases when this MediaPlayer object is in disregard for GC set
- L1507 _private prototype_ `bool OpenSourceInternal(UMediaSource* MediaSource, const FMediaPlayerOptions* Options);` — Open media source with the given options.
- L1510 _private prototype_ `void EnsurePlaylist() const;` — Ensure internal playlist is created
- L1515 _private member_ `FOnMediaEvent MediaEvent;` — An event delegate that is invoked when a media event occurred.
- L1518 _private member_ `TSharedPtr<FMediaPlayerFacade, ESPMode::ThreadSafe> PlayerFacade;` — The player facade.
- L1522 _private member_ `FGuid PlayerGuid;` — `UPROPERTY()` — The player's globally unique identifier.
- L1525 _private member_ `bool PlayOnNext;` — Automatically start playback of next item in play list.
- L1528 _private member_ `bool RegisteredWithMediaModule;` — Has registered with the media module
- L1531 _private member_ `FMediaPlayerProxyPtr Proxy;` — Proxy instance for integration with Metasound
- L1537 _public member_ `bool AffectedByPIEHandling;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, AdvancedDisplay, Category=Editor)` — Whether this player should stop when entering or exiting PIE.
- L1541 _private member_ `bool WasPlayingInPIE;` — Whether the player was playing in PIE/SIE.

#### Free symbols / members of external scopes

- L39 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnMediaPlayerMediaEvent);` — Multicast delegate that is invoked when a media event occurred in the player.
- L39 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnMediaPlayerMediaEvent);` — Multicast delegate that is invoked when a media event occurred in the player.
- L42 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMediaPlayerMediaOpened, FString, OpenedUrl);` — Multicast delegate that is invoked when a media player's media has been opened.
- L42 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMediaPlayerMediaOpened, FString, OpenedUrl);` — Multicast delegate that is invoked when a media player's media has been opened.
- L45 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMediaPlayerMediaOpenFailed, FString, FailedUrl);` — Multicast delegate that is invoked when a media player's media has failed to open.
- L45 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMediaPlayerMediaOpenFailed, FString, FailedUrl);` — Multicast delegate that is invoked when a media player's media has failed to open.
- L157 _function_ `friend inline uint32 GetTypeHash(const FMediaPlayerProxy& InProxy)`
- L166 _typedef_ `using FMediaPlayerProxyPtr = TSharedPtr<FMediaPlayerProxy, ESPMode::ThreadSafe>;`
- L1291 _delegate_ `DECLARE_EVENT_OneParam(UMediaPlayer, FOnMediaEvent, EMediaEvent ) FOnMediaEvent& OnMediaEvent() { return MediaEvent; } #if WITH_EDITOR void PausePIE();` — Get an event delegate that is invoked when a media event occurred. @return The delegate.

### `Source/Runtime/MediaAssets/Public/MediaPlayerProxyInterface.h` (Public)


#### class `UMediaPlayerProxyInterface`  
`class UMediaPlayerProxyInterface : public UInterface`  
_L20-23_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UInterface`
- desc: The proxy object provides a higher level of insight/control than just the media player. For example, the object owning the player may control the player in some cases, and the proxy allows you and the object to avoid conflicts in control.

#### class `IMediaPlayerProxyInterface`  
`class IMediaPlayerProxyInterface`  
_L25-88_
- L35 _public prototype_ `virtual float GetProxyRate() const = 0;` — Get the desired playback rate. Note that this is not necessarily the actual rate of the player, merely the desired rate the user wants.
- L43 _public prototype_ `virtual bool SetProxyRate(float Rate) = 0;` — Changes the desired playback rate. @param Rate		The playback rate to set. @return			True on success, false otherwise.
- L50 _public prototype_ `virtual bool IsExternalControlAllowed() = 0;` — Call this to see if you can control the media player, or if the owning object is using it. @return				True if you can control the player.
- L55 _public prototype_ `virtual const FMediaSourceCacheSettings& GetCacheSettings() const = 0;` — Gets the cache settings for the player.
- L60 _public prototype_ `virtual UMediaSource* ProxyGetMediaSourceFromIndex(int32 Index) const = 0;` — Get the media source for a given index.
- L65 _public prototype_ `virtual UMediaTexture* ProxyGetMediaTexture(int32 LayerIndex, int32 TextureIndex) = 0;` — Get a media texture that we can assign a media player to.
- L70 _public prototype_ `virtual void ProxyReleaseMediaTexture(int32 LayerIndex, int32 TextureIndex) = 0;` — Release a media texture that was retrieved from ProxyGetMediaTexture.
- L82 _public prototype_ `virtual bool ProxySetAspectRatio(UMediaPlayer* InMediaPlayer) = 0;` — Sets the aspect ratio of the proxy based on what the media player is playing. This should be called every frame until it returns true. It might take a few frames to discover what the aspect ratio is. Also some proxies might not support aspect ratios, so they will also return true so you do not call this endlessly. @return True if you no longer need to call this.
- L87 _public prototype_ `virtual void ProxySetTextureBlend(int32 LayerIndex, int32 TextureIndex, float Blend) = 0;` — Set the blend value for a texture that was retrieved from ProxyGetMediaTexture.

### `Source/Runtime/MediaAssets/Public/MediaPlaylist.h` (Public)


#### class `UMediaPlaylist`  
`class UMediaPlaylist : public UObject`  
_L24-160_
- reflection: `UCLASS(BlueprintType, hidecategories=(Object), MinimalAPI)`
- inherits: `UObject`
- desc: Implements a media play list.
- L39 _public prototype_ `bool Add(UMediaSource* MediaSource);` — `UFUNCTION(BlueprintCallable, Category="Media|MediaPlaylist")` — Add a media source to the play list. @param MediaSource The media source to append. @return true if the media source was added, false otherwise. @see AddFile, AddUrl, Insert, RemoveAll, Remove, Replace
- L49 _public prototype_ `bool AddFile(const FString& FilePath);` — `UFUNCTION(BlueprintCallable, Category="Media|MediaPlaylist")` — Add a media file path to the play list. @param FilePath The file path to add. @return true if the file was added, false otherwise. @see Add, AddUrl, Insert, RemoveAll, Remove, Replace
- L59 _public prototype_ `bool AddUrl(const FString& Url);` — `UFUNCTION(BlueprintCallable, Category="Media|MediaPlaylist")` — Add a media URL to the play list. @param Url The URL to add. @return true if the URL was added, false otherwise. @see Add, AddFile, Insert, RemoveAll, Remove, Replace
- L69 _public prototype_ `UMediaSource* Get(int32 Index);` — `UFUNCTION(BlueprintCallable, Category="Media|MediaPlaylist")` — Get the media source at the specified index. @param Index The index of the media source to get. @return The media source, or nullptr if the index doesn't exist. @see GetNext, GetRandom
- L79 _public prototype_ `UMediaSource* GetNext(int32& InOutIndex);` — `UFUNCTION(BlueprintCallable, Category="Media|MediaPlaylist")` — Get the next media source in the play list. @param InOutIndex Index of the current media source (will contain the new index). @return The media source after the current one, or nullptr if the list is empty. @see , GetPrevious, GetRandom
- L89 _public prototype_ `UMediaSource* GetPrevious(int32& InOutIndex);` — `UFUNCTION(BlueprintCallable, Category="Media|MediaPlaylist")` — Get the previous media source in the play list. @param InOutIndex Index of the current media source (will contain the new index). @return The media source before the current one, or nullptr if the list is empty. @see , GetNext, GetRandom
- L99 _public prototype_ `UMediaSource* GetRandom(int32& OutIndex);` — `UFUNCTION(BlueprintCallable, Category="Media|MediaPlaylist")` — Get a random media source in the play list. @param OutIndex Will contain the index of the returned media source. @return The random media source, or nullptr if the list is empty. @see Get, GetNext, GetPrevious
- L109 _public prototype_ `void Insert(UMediaSource* MediaSource, int32 Index);` — `UFUNCTION(BlueprintCallable, Category="Media|MediaPlaylist")` — Insert a media source into the play list at the given position. @param MediaSource The media source to insert. @param Index The index to insert into. @see Add, Remove, RemoveAll, Replace
- L117 _public function_ `int32 Num()` — `UFUNCTION(BlueprintCallable, Category="Media|MediaPlaylist")` — Get the number of media sources in the play list. @return Number of media sources.
- L130 _public prototype_ `bool Remove(UMediaSource* MediaSource);` — `UFUNCTION(BlueprintCallable, Category="Media|MediaPlaylist")` — Remove all occurrences of the given media source in the play list. @param MediaSource The media source to remove. @return true if the media source was removed, false otherwise. @see Add, Insert, Remove, Replace
- L140 _public prototype_ `bool RemoveAt(int32 Index);` — `UFUNCTION(BlueprintCallable, Category="Media|MediaPlaylist")` — Remove the media source at the specified position. @param Index The index of the media source to remove. @return true if the media source was removed, false otherwise. @see Add, Insert, RemoveAll, Replace
- L151 _public prototype_ `bool Replace(int32 Index, UMediaSource* Replacement);` — `UFUNCTION(BlueprintCallable, Category="Media|MediaPlaylist")` — Replace the media source at the specified position. @param Index The index of the media source to replace. @param Replacement The replacement media source. @return true if the media source was replaced, false otherwise. @see Add, Insert, RemoveAll, RemoveAt
- L157 _protected member_ `TArray<TObjectPtr<UMediaSource>> Items;` — `UPROPERTY(EditAnywhere, Category=Playlist)` — List of media sources to play.
- L159 _protected function_ `virtual bool CanBeInCluster() const override`

### `Source/Runtime/MediaAssets/Public/MediaSoundComponent.h` (Public)


#### enum `EMediaSoundChannels`  
`enum class EMediaSoundChannels`  
_L36-46_
- reflection: `UENUM()`
- desc: Available media sound channel types.
- L39 _public enumerator_ `Mono` — Mono (1 channel).
- L42 _public enumerator_ `Stereo` — Stereo (2 channels).
- L45 _public enumerator_ `Surround` — Surround sound (7.1 channels; for UI).

#### enum `EMediaSoundComponentFFTSize`  
`enum class EMediaSoundComponentFFTSize : uint8`  
_L49-55_
- reflection: `UENUM(BlueprintType)`
- L51 _public enumerator_ `Min_64`
- L52 _public enumerator_ `Small_256`
- L53 _public enumerator_ `Medium_512`
- L54 _public enumerator_ `Large_1024`

#### struct `FMediaSoundComponentSpectralData`  
`struct FMediaSoundComponentSpectralData`  
_L58-69_
- reflection: `USTRUCT(BlueprintType)`
- L64 _public member_ `float FrequencyHz = 0.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpectralData")` — The frequency hz of the spectrum value
- L68 _public member_ `float Magnitude = 0.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpectralData")` — The magnitude of the spectrum at this frequency

#### class `FMediaSoundGenerator`  
`class FMediaSoundGenerator : public ISoundGenerator`  
_L72-146_
- inherits: `ISoundGenerator`
- desc: Class implements an ISoundGenerator to feed decoded audio to audio renderering async tasks
- L97 _public prototype_ `FMediaSoundGenerator(FSoundGeneratorParams& InParams);`
- L99 _public prototype_ `virtual ~FMediaSoundGenerator();`
- L101 _public prototype_ `virtual void OnEndGenerate() override;`
- L103 _public prototype_ `virtual int32 OnGenerateAudio(float* OutAudio, int32 NumSamples) override;`
- L105 _public prototype_ `void SetCachedData(float InCachedRate, const FTimespan& InCachedTime);`
- L106 _public prototype_ `void SetLastPlaySampleTime(const FTimespan& InLastPlaySampleTime);`
- L108 _public prototype_ `void SetEnableSpectralAnalysis(bool bInSpectralAnlaysisEnabled);`
- L109 _public prototype_ `void SetEnableEnvelopeFollowing(bool bInEnvelopeFollowingEnabled);`
- L111 _public prototype_ `void SetSpectrumAnalyzerSettings(Audio::FSpectrumAnalyzerSettings::EFFTSize InFFTSize, const TArray<float>& InFrequenciesToAnalyze);`
- L112 _public prototype_ `void SetEnvelopeFollowingSettings(int32 InAttackTimeMsec, int32 InReleaseTimeMsec);`
- L114 _public prototype_ `void SetSampleQueue(TSharedPtr<FMediaAudioSampleQueue, ESPMode::ThreadSafe>& InSampleQueue);`
- L116 _public prototype_ `TArray<FMediaSoundComponentSpectralData> GetSpectralData() const;`
- L117 _public prototype_ `TArray<FMediaSoundComponentSpectralData> GetNormalizedSpectralData() const;`
- L118 _public function_ `float GetCurrentEnvelopeValue() const`
- L120 _public function_ `FTimespan GetLastPlayTime() const`
- L124 _private member_ `FSoundGeneratorParams Params;`
- L127 _private member_ `FMediaAudioResampler Resampler;` — The audio resampler.
- L130 _private member_ `Audio::AlignedFloatBuffer AudioScratchBuffer;` — Scratch buffer to mix in source audio to from decoder
- L133 _private member_ `mutable Audio::FAsyncSpectrumAnalyzer SpectrumAnalyzer;` — Spectrum analyzer used for analyzing audio in media.
- L135 _private member_ `Audio::FEnvelopeFollower EnvelopeFollower;`
- L137 _private member_ `TAtomic<float> CachedRate;`
- L138 _private member_ `TAtomic<FTimespan> CachedTime;`
- L139 _private member_ `TAtomic<FTimespan> LastPlaySampleTime;`
- L141 _private member_ `float CurrentEnvelopeValue = 0.0f;`
- L142 _private member_ `bool bEnvelopeFollowerSettingsChanged = false;`
- L144 _private member_ `mutable FCriticalSection AnalysisCritSect;`
- L145 _private member_ `mutable FCriticalSection SampleQueueCritSect;`

#### struct `FMediaSoundGenerator::FSoundGeneratorParams`  
`struct FSoundGeneratorParams`  
_L75-95_
- L77 _public member_ `int32 SampleRate = 0;`
- L78 _public member_ `int32 NumChannels = 0;`
- L80 _public member_ `TSharedPtr<FMediaAudioSampleQueue, ESPMode::ThreadSafe> SampleQueue;`
- L81 _public member_ `uint32 PreviousSampleQueueFlushCount = 0;`
- L83 _public member_ `bool bSpectralAnalysisEnabled = false;`
- L84 _public member_ `bool bEnvelopeFollowingEnabled = false;`
- L86 _public member_ `int32 EnvelopeFollowerAttackTime = 0;`
- L87 _public member_ `int32 EnvelopeFollowerReleaseTime = 0;`
- L89 _public member_ `Audio::FSpectrumAnalyzerSettings SpectrumAnalyzerSettings;`
- L90 _public member_ `TArray<float> FrequenciesToAnalyze;`
- L92 _public member_ `float CachedRate = 0.0f;`
- L93 _public member_ `FTimespan CachedTime;`
- L94 _public member_ `FTimespan LastPlaySampleTime;`

#### class `UMediaSoundComponent`  
`class UMediaSoundComponent : public USynthComponent`  
_L152-402_
- reflection: `UCLASS(ClassGroup=Media, editinlinenew, meta=(BlueprintSpawnableComponent), MinimalAPI)`
- inherits: `USynthComponent`
- desc: Implements a sound component for playing a media player's audio output.
- L161 _public member_ `EMediaSoundChannels Channels;` — `UPROPERTY(EditAnywhere, Category="Media")` — Media sound channel type.
- L165 _public member_ `bool DynamicRateAdjustment;` — `UPROPERTY(EditAnywhere, Category="Media", AdvancedDisplay)` — Dynamically adjust the sample rate if audio and media clock desynchronize.
- L175 _public member_ `float RateAdjustmentFactor;` — `UPROPERTY(EditAnywhere, Category="Media", AdvancedDisplay)` — Factor for calculating the sample rate adjustment. If dynamic rate adjustment is enabled, this number is multiplied with the drift between the audio and media clock (in 100ns ticks) to determine the adjustment. that is to be multiplied into the current playrate.
- L184 _public member_ `FFloatRange RateAdjustmentRange;` — `UPROPERTY(EditAnywhere, Category="Media", AdvancedDisplay)` — The allowed range of dynamic rate adjustment. If dynamic rate adjustment is enabled, and the necessary adjustment falls outside of this range, audio samples will be dropped.
- L193 _public prototype_ `UMediaSoundComponent(const FObjectInitializer& ObjectInitializer);` — Create and initialize a new instance. @param ObjectInitializer Initialization parameters.
- L196 _public prototype_ `~UMediaSoundComponent();` — Virtual destructor.
- L207 _public prototype_ `bool BP_GetAttenuationSettingsToApply(FSoundAttenuationSettings& OutAttenuationSettings);` — `UFUNCTION(BlueprintCallable, Category="Media|MediaSoundComponent", meta=(DisplayName="Get Attenuation Settings To Apply", ScriptName="GetAttenuationSettingsToApply"))` — Get the attenuation settings based on the current component settings. @param OutAttenuationSettings Will contain the attenuation settings, if available. @return true if attenuation settings were returned, false if attenuation is disabled.
- L216 _public prototype_ `UMediaPlayer* GetMediaPlayer() const;` — `UFUNCTION(BlueprintCallable, Category="Media|MediaSoundComponent")` — Get the media player that provides the audio samples. @return The component's media player, or nullptr if not set. @see SetMediaPlayer
- L218 _public function_ `virtual USoundClass* GetSoundClass() override`
- L248 _public prototype_ `void SetMediaPlayer(UMediaPlayer* NewMediaPlayer);` — `UFUNCTION(BlueprintCallable, Category="Media|MediaSoundComponent")` — Set the media player that provides the audio samples. @param NewMediaPlayer The player to set. @see GetMediaPlayer
- L252 _public prototype_ `void SetEnableSpectralAnalysis(bool bInSpectralAnalysisEnabled);` — `UFUNCTION(BlueprintCallable, Category = "Media|MediaSoundComponent")` — Turns on spectral analysis of the audio generated in the media sound component.
- L256 _public prototype_ `void SetSpectralAnalysisSettings(TArray<float> InFrequenciesToAnalyze, EMediaSoundComponentFFTSize InFFTSize = EMediaSoundComponentFFTSize::Medium_512);` — `UFUNCTION(BlueprintCallable, Category = "Media|MediaSoundComponent")` — Sets the settings to use for spectral analysis.
- L260 _public prototype_ `TArray<FMediaSoundComponentSpectralData> GetSpectralData();` — `UFUNCTION(BlueprintCallable, Category = "TimeSynth")` — Retrieves the spectral data if spectral analysis is enabled.
- L264 _public prototype_ `TArray<FMediaSoundComponentSpectralData> GetNormalizedSpectralData();` — `UFUNCTION(BlueprintCallable, Category = "TimeSynth")` — Retrieves and normalizes the spectral data if spectral analysis is enabled.
- L268 _public prototype_ `void SetEnableEnvelopeFollowing(bool bInEnvelopeFollowing);` — `UFUNCTION(BlueprintCallable, Category = "Media|MediaSoundComponent")` — Turns on amplitude envelope following the audio in the media sound component.
- L272 _public prototype_ `void SetEnvelopeFollowingsettings(int32 AttackTimeMsec, int32 ReleaseTimeMsec);` — `UFUNCTION(BlueprintCallable, Category = "Media|MediaSoundComponent")` — Sets the envelope attack and release times (in ms).
- L276 _public prototype_ `float GetEnvelopeValue() const;` — `UFUNCTION(BlueprintCallable, Category = "TimeSynth")` — Retrieves the current amplitude envelope.
- L281 _public prototype_ `void AddClockSink();` — Adds a clock sink so this can be ticked without the world.
- L284 _public prototype_ `void RemoveClockSink();` — Removes the clock sink.
- L286 _public prototype_ `void UpdatePlayer();`
- L295 _public prototype_ `void SetDefaultMediaPlayer(UMediaPlayer* NewMediaPlayer);` — Set the component's default media player property. @param NewMediaPlayer The player to set. @see SetMediaPlayer
- L302 _public prototype_ `void CollectAttenuationShapesForVisualization(TMultiMap<EAttenuationShape::Type, FBaseAttenuationSettings::AttenuationShapeDetails>& ShapeDetailsMap) const;`
- L308 _public prototype_ `virtual void OnRegister() override;`
- L309 _public prototype_ `virtual void OnUnregister() override;`
- L310 _public prototype_ `virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;`
- L316 _public prototype_ `virtual void Activate(bool bReset = false) override;`
- L317 _public prototype_ `virtual void Deactivate() override;`
- L322 _public prototype_ `virtual void PostLoad() override;`
- L325 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L335 _protected prototype_ `const FSoundAttenuationSettings* GetSelectedAttenuationSettings() const;` — Get the attenuation settings based on the current component settings. @return Attenuation settings, or nullptr if attenuation is disabled.
- L341 _protected prototype_ `virtual bool Init(int32& SampleRate) override;`
- L343 _protected prototype_ `virtual ISoundGeneratorPtr CreateSoundGenerator(const FSoundGeneratorInitParams& InParams) override;`
- L356 _protected member_ `TObjectPtr<UMediaPlayer> MediaPlayer;` — `UPROPERTY(EditAnywhere, Category="Media")` — The media player asset associated with this component. This property is meant for design-time convenience. To change the associated media player at run-time, use the SetMediaPlayer method. @see SetMediaPlayer
- L361 _private member_ `float CachedRate;` — The player's current play rate (cached for use on audio thread).
- L364 _private member_ `FTimespan CachedTime;` — The player's current time (cached for use on audio thread).
- L367 _private member_ `FTransactionallySafeCriticalSection CriticalSection;` — Critical section for synchronizing access to PlayerFacadePtr.
- L370 _private member_ `TWeakObjectPtr<UMediaPlayer> CurrentPlayer;` — The player that is currently associated with this component.
- L373 _private member_ `TWeakPtr<FMediaPlayerFacade, ESPMode::ThreadSafe> CurrentPlayerFacade;` — The player facade that's currently providing texture samples.
- L376 _private member_ `float RateAdjustment;` — Adjusts the output sample rate to synchronize audio and media clock.
- L379 _private member_ `TSharedPtr<FMediaAudioSampleQueue, ESPMode::ThreadSafe> SampleQueue;` — Audio sample queue.
- L382 _private member_ `FTimespan LastPlaySampleTime;` — Time of last sample played.
- L385 _private member_ `TArray<float> FrequenciesToAnalyze;` — Which frequencies to analyze.
- L387 _private member_ `Audio::FSpectrumAnalyzerSettings SpectrumAnalyzerSettings;` — Spectrum analyzer used for analyzing audio in media.
- L388 _private member_ `int32 EnvelopeFollowerAttackTime;`
- L389 _private member_ `int32 EnvelopeFollowerReleaseTime;`
- L392 _private member_ `bool bSpectralAnalysisEnabled;` — Whether or not spectral analysis is enabled.
- L395 _private member_ `bool bEnvelopeFollowingEnabled;` — Whether or not envelope following is enabled.
- L398 _private member_ `TSharedPtr<FMediaSoundComponentClockSink, ESPMode::ThreadSafe> ClockSink;` — Holds our clock sink if available.
- L401 _private member_ `ISoundGeneratorPtr MediaSoundGenerator;` — Instance of our media sound generator. This is a non-uobject that is used to feed sink audio to a sound source on the audio render thread (or async task).

### `Source/Runtime/MediaAssets/Public/MediaSource.h` (Public)


#### class `UMediaSource`  
`class UMediaSource : public UObject , public IMediaOptions`  
_L42-184_
- reflection: `UCLASS(Abstract, editinlinenew, BlueprintType, hidecategories=(Object), MinimalAPI)`
- inherits: `UObject,IMediaOptions`
- desc: Abstract base class for media sources. Media sources describe the location and/or settings of media objects that can be played in a media player, such as a video file on disk, a video stream on the internet, or a web cam attached to or built into the target device. The location is encoded as a media URL string, whose URI scheme and optional file extension will be used to locate a suitable media player.
- L57 _public prototype_ `virtual FString GetUrl() const PURE_VIRTUAL(UMediaSource::GetUrl, return FString(););` — `UFUNCTION(BlueprintCallable, Category="Media|MediaSource")` — Get the media source's URL string (must be implemented in child classes). @return The media URL. @see GetProxies
- L65 _public prototype_ `virtual bool Validate() const PURE_VIRTUAL(UMediaSource::Validate, return false;);` — `UFUNCTION(BlueprintCallable, Category="Media|MediaSource")` — Validate the media source settings (must be implemented in child classes). @return true if validation passed, false otherwise.
- L72 _public prototype_ `void GenerateThumbnail();` — Starts the process to generate a thumbnail.
- L77 _public function_ `UTexture* GetThumbnail() const` — Gets our thumbnail texture, if any.
- L82 _public function_ `void SetThumbnail(UTexture* InTexture)` — Sets what the thumbnail texture should be.
- L85 _public function_ `virtual FString GetDescriptionString() const` — Gets a string that sums up the media source's description for UI purposes
- L87 _public typedef_ `typedef TTuple<FText, FText, FText> FInfoElement;`
- L93 _public prototype_ `virtual void GetDetailsPanelInfoElements(TArray<FInfoElement>& OutInfoElements) const;` — Gets a list of text containing the media source's configuration and description for UI purposes @param OutInfoElements A list of elements, where an element is constructed from a group, a label, and a value
- L104 _public prototype_ `static void RegisterSpawnFromFileExtension(const FString& Extension, FMediaSourceSpawnDelegate InDelegate);` — Call this to register a callback when someone calls SpawnMediaSourceForString. This lets you spawn a media source if the file extension matches what you want. @param Extension		File extension to match. This is case insensitive. @param InDelegate	This will get called if the Url passed into GetMediaSourceForUrl matches Extension.
- L111 _public prototype_ `static void UnregisterSpawnFromFileExtension(const FString& Extension);` — Call this to unregister a callback set with RegisterSpawnFromFileExtension. @param Extension		File extension that the callack was registered with.
- L120 _public prototype_ `static UMediaSource* SpawnMediaSourceForString(const FString& MediaPath, UObject* Outer);` — Call this to try and create a media source appropriate for the media. @param MediaPath		Can be a file location or a Url. @param Outer			Outer to use for this object. @return				Media source or nullptr if none are appropriate.
- L124 _public prototype_ `virtual void BeginDestroy() override;`
- L128 _public prototype_ `virtual FName GetDesiredPlayerName() const override;`
- L129 _public prototype_ `virtual bool GetMediaOption(const FName& Key, bool DefaultValue) const override;`
- L130 _public prototype_ `virtual double GetMediaOption(const FName& Key, double DefaultValue) const override;`
- L131 _public prototype_ `virtual int64 GetMediaOption(const FName& Key, int64 DefaultValue) const override;`
- L132 _public prototype_ `virtual FString GetMediaOption(const FName& Key, const FString& DefaultValue) const override;`
- L133 _public prototype_ `virtual FText GetMediaOption(const FName& Key, const FText& DefaultValue) const override;`
- L134 _public prototype_ `virtual TSharedPtr<FDataContainer, ESPMode::ThreadSafe> GetMediaOption(const FName& Key, const TSharedPtr<FDataContainer, ESPMode::ThreadSafe>& DefaultValue) const override;`
- L135 _public prototype_ `virtual bool HasMediaOption(const FName& Key) const override;`
- L136 _public prototype_ `virtual const UObject* ToUObject() const override;`
- L140 _public prototype_ `void SetMediaOptionBool(const FName& Key, bool Value);` — `UFUNCTION(BlueprintCallable, meta=(DisplayName = "SetMediaOption (boolean)"), Category = "Media|MediaSource")` — Set a boolean parameter to pass to the player.
- L143 _public prototype_ `void SetMediaOptionFloat(const FName& Key, float Value);` — `UFUNCTION(BlueprintCallable, meta = (DisplayName = "SetMediaOption (float)"), Category = "Media|MediaSource")` — Set a float parameter to pass to the player.
- L145 _public prototype_ `void SetMediaOptionDouble(const FName& Key, double Value);` — Set a double parameter to pass to the player.
- L148 _public prototype_ `void SetMediaOptionInt64(const FName& Key, int64 Value);` — `UFUNCTION(BlueprintCallable, meta = (DisplayName = "SetMediaOption (integer64)"), Category = "Media|MediaSource")` — Set an integer64 parameter to pass to the player.
- L151 _public prototype_ `void SetMediaOptionString(const FName& Key, const FString& Value);` — `UFUNCTION(BlueprintCallable, meta = (DisplayName = "SetMediaOption (string)"), Category = "Media|MediaSource")` — Set a string parameter to pass to the player.
- L155 _private member_ `TMap<FName, FVariant> MediaOptionsMap;` — Holds our media options.
- L161 _private prototype_ `const FVariant* GetMediaOptionDefault(const FName& Key) const;` — Get the media option specified by the Key as a Variant. Returns nullptr if the Key does not exist.
- L166 _private prototype_ `void SetMediaOption(const FName& Key, FVariant& Value);` — Sets the media option specified by Key to the supplied Variant.
- L171 _private prototype_ `static TMap<FString, FMediaSourceSpawnDelegate>& GetSpawnFromFileExtensionDelegates();` — Get a mapping of file extensions to spawn delegates.
- L177 _private member_ `TObjectPtr<UTexture> ThumbnailImage = nullptr;` — `UPROPERTY(Transient)` — The thumbnail image.
- L181 _private member_ `TObjectPtr<UObject> MediaSourceRenderer = nullptr;` — `UPROPERTY(Transient)` — Renders thumnbnails for us.

#### Free symbols / members of external scopes

- L30 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(UMediaSource*, FMediaSourceSpawnDelegate, const FString&, UObject*);` — Delegate for creating a media source from a string.
- L30 _prototype_ `DECLARE_DELEGATE_RetVal_TwoParams(UMediaSource*, FMediaSourceSpawnDelegate, const FString&, UObject*);` — Delegate for creating a media source from a string.

### `Source/Runtime/MediaAssets/Public/MediaSourceOptions.h` (Public)


#### struct `FMediaSourceCacheSettings`  
`struct FMediaSourceCacheSettings`  
_L21-50_
- reflection: `USTRUCT(BlueprintType)`
- desc: Cache settings to pass to the player.
- L30 _public member_ `bool bOverride = false;` — `UPROPERTY(EditAnywhere, Category = "Media Cache")` — Override the default cache settings. Currently only the ImgMedia player supports these settings.
- L38 _public member_ `float TimeToLookAhead = 0.2f;` — `UPROPERTY(EditAnywhere, Category = "Media Cache")` — The cache will fill up with frames that are up to this time from the current time. E.g. if this is 0.2, and we are at time index 5 seconds, then we will fill the cache with frames between 5 seconds and 5.2 seconds.
- L41 _public function_ `inline bool operator==(const FMediaSourceCacheSettings& Other) const`
- L46 _public function_ `inline bool operator!=(const FMediaSourceCacheSettings& Other) const`

### `Source/Runtime/MediaAssets/Public/MediaSourceRendererInterface.h` (Public)


#### class `UMediaSourceRendererInterface`  
`class UMediaSourceRendererInterface : public UInterface`  
_L16-19_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UInterface`
- desc: Interface for an object that can render a media source to a texture.

#### class `IMediaSourceRendererInterface`  
`class IMediaSourceRendererInterface`  
_L21-34_
- L33 _public prototype_ `virtual UMediaTexture* Open(UMediaSource* InMediaSource) = 0;` — Open the media source to render a texture for. @param	InMediaSource		Media source to play. @return	Media texture that will hold the image.

### `Source/Runtime/MediaAssets/Public/MediaTexture.h` (Public)


#### enum `MediaTextureOrientation`  
`enum MediaTextureOrientation : int`  
_L25-31_
- reflection: `UENUM()`
- L27 _public enumerator_ `MTORI_Original UMETA(DisplayName = "Original (as decoded)")`
- L28 _public enumerator_ `MTORI_CW90 UMETA(DisplayName = "Clockwise 90deg")`
- L29 _public enumerator_ `MTORI_CW180 UMETA(DisplayName = "Clockwise 180deg")`
- L30 _public enumerator_ `MTORI_CW270 UMETA(DisplayName = "Clockwise 270deg")`

#### class `UMediaTexture`  
`class UMediaTexture : public UTexture`  
_L40-370_
- reflection: `UCLASS(hidecategories=(Adjustments, Compositing, LevelOfDetail, ImportSettings, Object), MinimalAPI)`
- inherits: `UTexture`
- desc: Implements a texture asset for rendering video tracks from UMediaPlayer assets. note: derives directly from UTexture, not from UTexture2D or UTexture2DDynamic maybe should have been UTexture2DDynamic?
- L58 _public member_ `TEnumAsByte<TextureAddress> AddressX;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MediaTexture", meta=(DisplayName="X-axis Tiling Method"), AssetRegistrySearchable, AdvancedDisplay)` — The addressing mode to use for the X axis.
- L62 _public member_ `TEnumAsByte<TextureAddress> AddressY;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MediaTexture", meta=(DisplayName="Y-axis Tiling Method"), AssetRegistrySearchable, AdvancedDisplay)` — The addressing mode to use for the Y axis.
- L66 _public member_ `bool AutoClear;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MediaTexture")` — Whether to clear the texture when no media is being played (default = enabled).
- L70 _public member_ `FLinearColor ClearColor;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MediaTexture")` — The color used to clear the texture if AutoClear is enabled (default = black).
- L74 _public member_ `bool EnableGenMips;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MediaTexture", meta = (DisplayName = "Enable Mipmap generation"))` — Basic enablement for mip generation (default = false).
- L79 _public member_ `uint8 NumMips_DEPRECATED;` — `UE_DEPRECATED(5.6, "Only 'Enable Mipmap Generation' is needed now. When true, the full mip chain will be generated.")` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "Only 'Enable Mipmap Generation' is needed now. When true, the full mip chain will be generated."))`
- L87 _public member_ `bool NewStyleOutput;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MediaTexture", meta = (DisplayName = "Enable New Style Output"))` — Allows the media texture to be used as a regular 2D texture in materials, with Color or Linear Color sampler types as opposed to External. Note however that external textures can remain more efficient on lower-end platforms (OpenGL ES).
- L91 _public member_ `float CurrentAspectRatio;` — `UPROPERTY(Transient, TextExportTransient, SkipSerialization, BlueprintReadOnly, Category = "MediaTexture", meta = (DisplayName = "Current frame's aspect ratio"))` — Current aspect ratio
- L106 _public prototype_ `float GetAspectRatio() const;` — `UFUNCTION(BlueprintCallable, Category="Media|MediaTexture")` — Gets the current aspect ratio of the texture. @return Texture aspect ratio. @see GetHeight, GetWidth
- L115 _public prototype_ `int32 GetHeight() const;` — `UFUNCTION(BlueprintCallable, Category="Media|MediaTexture")` — Gets the current height of the texture. @return Texture height (in pixels). @see GetAspectRatio, GetWidth
- L124 _public prototype_ `int32 GetWidth() const;` — `UFUNCTION(BlueprintCallable, Category="Media|MediaTexture")` — Gets the current width of the texture. @return Texture width (in pixels). @see GetAspectRatio, GetHeight
- L132 _public prototype_ `int32 GetTextureNumMips() const;` — `UFUNCTION(BlueprintCallable, Category = "Media|MediaTexture")` — Gets the current numbe of mips of the texture. @return Number of mips.
- L141 _public prototype_ `UMediaPlayer* GetMediaPlayer() const;` — `UFUNCTION(BlueprintCallable, Category = "Media|MediaTexture")` — Get the media player that provides the video samples. @return The texture's media player, or nullptr if not set. @see SetMediaPlayer
- L150 _public prototype_ `void SetMediaPlayer(UMediaPlayer* NewMediaPlayer);` — `UFUNCTION(BlueprintCallable, Category="Media|MediaTexture")` — Set the media player that provides the video samples. @param NewMediaPlayer The player to set. @see GetMediaPlayer
- L160 _public prototype_ `void SetMediaPlayer(UMediaPlayer* NewMediaPlayer, TSharedPtr<FMediaTextureSampleQueue> InSampleQueue);` — Set the media player that provides the video samples and optionally the sample queue that receives them. If no sample queue is provided, the media texture creates a new one internally. @param NewMediaPlayer The player to set. @param InSampleQueue Provide an optional sample queue to use instead of creating a new one. @see GetMediaPlayer
- L168 _public function_ `void UpdateResource()` — `UFUNCTION(BlueprintCallable, Category = "Media|MediaTexture")` — Creates a new resource for the texture, and updates any cached references to the resource. This obviously is just an override to expose to blueprints. Since the base is deprecated in favor of the new params version, we remove the virtual override and pass the flags we care about here.
- L174 _public prototype_ `void CacheNextAvailableSampleTime(FTimespan InNextSampleTime);` — Caches the next available sample time from the queue when last rendering was made @see GetNextSampleTime
- L182 _public prototype_ `FTimespan GetNextSampleTime() const;` — Gets the next sample Time. Only valid if GetAvailableSampleCount is greater than 0 @note This value is cached when last render command was executed to keep single consumer requirements. @return FTimespan of the next sample or FTimespan::MinValue if no sample was available in the queue. @see GetAvailableSampleCount, CacheNextAvailableSampleTime
- L188 _public prototype_ `int32 GetAvailableSampleCount() const;` — Gets the number of samples that are available @return The number of samples in the queue
- L198 _public prototype_ `void SetDefaultMediaPlayer(UMediaPlayer* NewMediaPlayer);` — Set the texture's default media player property. @param NewMediaPlayer The player to set. @see SetMediaPlayer
- L206 _public prototype_ `float GetCurrentAspectRatio() const;` — Get current aspect ratio of presented frame. @return Aspect ratio of current frame
- L212 _public prototype_ `MediaTextureOrientation GetCurrentOrientation() const;` — Get current orientation of presented frame. @return Orientation of current frame
- L218 _public prototype_ `float GetMipMapBias() const;` — Get the texture's mip-map bias, clamped to a legal range. @return Mip-map bias value
- L226 _public prototype_ `void SetMipMapBias(float InMipMapBias);` — Set texture's mip-map bias, for use by the texture resource sampler. Note: UpdateResource() should be called afterwards and the material should be notified. @param InMipMapBias Bias value.
- L231 _public function_ `void SetColorSpaceOverride(UE::Color::EColorSpace InColorspaceOverride)` — Set an override for color space conversions
- L237 _public prototype_ `virtual void JustInTimeRender();` — Renders this media texture. Only has an effect if its RenderMode is ERenderMode::JustInTime
- L240 _public function_ `void SetRenderMode(ERenderMode InRenderMode)` — Sets the ERenderMode of this media texture
- L246 _public function_ `ERenderMode GetRenderMode()` — Returns the ERenderMode of this media texture
- L255 _public prototype_ `virtual void BeginDestroy() override;`
- L256 _public prototype_ `virtual FTextureResource* CreateResource() override;`
- L257 _public prototype_ `virtual EMaterialValueType GetMaterialType() const override;`
- L258 _public prototype_ `virtual float GetSurfaceWidth() const override;`
- L259 _public prototype_ `virtual float GetSurfaceHeight() const override;`
- L260 _public function_ `virtual float GetSurfaceDepth() const override`
- L261 _public function_ `virtual uint32 GetSurfaceArraySize() const override`
- L262 _public prototype_ `virtual FGuid GetExternalTextureGuid() const override;`
- L263 _public prototype_ `void SetRenderedExternalTextureGuid(const FGuid& InNewGuid);`
- L264 _public function_ `virtual ETextureClass GetTextureClass() const override`
- L265 _public prototype_ `virtual uint32 CalcTextureMemorySizeEnum(ETextureMipCount Enum) const override;`
- L266 _public function_ `virtual bool HasRuntimeVariableSRGB() const override`
- L272 _public prototype_ `virtual FString GetDesc() override;`
- L273 _public prototype_ `virtual void GetResourceSizeEx(FResourceSizeEx& CumulativeResourceSize) override;`
- L274 _public prototype_ `virtual void PostInitProperties() override;`
- L275 _public prototype_ `virtual void PostLoad() override;`
- L276 _public prototype_ `virtual bool IsPostLoadThreadSafe() const override;`
- L279 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L289 _protected prototype_ `void TickResource(FTimespan Timecode);` — Tick the texture resource. @param Timecode The current timecode.
- L295 _protected prototype_ `void UpdatePlayerAndQueue(TSharedPtr<FMediaTextureSampleQueue> InSampleQueue = nullptr);` — Update the video sample queue, if necessary. @param InSampleQueue Optional sample queue to use.
- L298 _protected prototype_ `void UpdateSampleInfo(const TSharedPtr<IMediaTextureSample, ESPMode::ThreadSafe>& Sample);` — Update sample info
- L311 _protected member_ `TObjectPtr<UMediaPlayer> MediaPlayer;` — `UPROPERTY(EditAnywhere, Category="Media")` — The media player asset associated with this texture. This property is meant for design-time convenience. To change the associated media player at run-time, use the SetMediaPlayer method. @see SetMediaPlayer
- L318 _private member_ `TSharedPtr<FMediaTextureClockSink, ESPMode::ThreadSafe> ClockSink;` — The texture's media clock sink.
- L321 _private member_ `FGuid CurrentGuid;` — The default external texture GUID if no media player is assigned.
- L324 _private member_ `FGuid CurrentRenderedGuid;` — The last Guid that was rendered and registered in the render command
- L327 _private member_ `TWeakObjectPtr<UMediaPlayer> CurrentPlayer;` — The player that is currently associated with this texture.
- L330 _private member_ `const FGuid DefaultGuid;` — The default external texture GUID if no media player is assigned.
- L333 _private member_ `FIntPoint Dimensions;` — Current width and height of the resource (in pixels).
- L336 _private member_ `FIntPoint LastDimensions;` — Last Tick's width and height of the resource (in pixels).
- L339 _private member_ `FLinearColor LastClearColor;` — The previously clear color.
- L342 _private member_ `bool LastSrgb;` — The previously used sRGB flag.
- L345 _private member_ `bool bIsCleared;` — True if the texture has been cleared.
- L348 _private member_ `TSharedPtr<FMediaTextureSampleQueue, ESPMode::ThreadSafe> SampleQueue;` — Texture sample queue.
- L351 _private member_ `SIZE_T Size;` — Current size of the resource (in bytes).
- L354 _private member_ `mutable FCriticalSection CriticalSection;` — Critical section to protect last rendered guid since it can be read from anywhere.
- L357 _private member_ `TAtomic<FTimespan> CachedNextSampleTime;` — Next available sample time when last render call was made
- L360 _private member_ `int32 TextureNumMips;` — Number of mips in the actual output texture
- L363 _private member_ `float MipMapBias;` — Mip-map bias used by the media texture resource sampler.
- L366 _private member_ `ERenderMode RenderMode = ERenderMode::Default;` — Current render mode of this media texture. Can be changed using SetRenderMode()
- L369 _private member_ `UE::Color::EColorSpace ColorspaceOverride;` — Colorspace override

#### enum `UMediaTexture::ERenderMode`  
`enum class ERenderMode`  
_L48-52_
- desc: Possible render modes of this media texture.
- L50 _public enumerator_ `Default = 0`
- L51 _public enumerator_ `JustInTime` — Will defer rendering this media texture until its consumer calls its JustInTimeRender function.

### `Source/Runtime/MediaAssets/Public/MediaTextureTracker.h` (Public)


#### enum `EMediaTextureVisibleMipsTiles`  
`enum class EMediaTextureVisibleMipsTiles : uint8`  
_L26-31_
- reflection: `UENUM()`
- L28 _public enumerator_ `None = 0`
- L29 _public enumerator_ `Plane = 1`
- L30 _public enumerator_ `Sphere`

#### enum `EMediaTextureTargetViewResolution`  
`enum class EMediaTextureTargetViewResolution : uint8`  
_L33-39_
- L35 _public enumerator_ `None = 0`
- L36 _public enumerator_ `RenderResolution = 1 << 0`
- L37 _public enumerator_ `DisplayResolution = 1 << 1`
- L38 _public enumerator_ `All = RenderResolution | DisplayResolution`

#### struct `FMediaTextureTrackerObject`  
`struct FMediaTextureTrackerObject`  
_L43-62_
- desc: Holds info on a single object.
- L46 _public member_ `TWeakObjectPtr<class AActor> Object;` — Actor that is using our img sequence.
- L48 _public member_ `float MipMapLODBias;` — LOD bias for the mipmap level.
- L50 _public member_ `EMediaTextureVisibleMipsTiles VisibleMipsTilesCalculations;` — Specify type of mesh used for visible mips and tiles calculations.
- L52 _public member_ `FVector2D MeshRange;` — Arc size in degrees used for visible tiles calculations, specific to the sphere.
- L54 _public member_ `int32 MipLevelToUpscale = -1;` — Mip level to upscale into lower quality mips. All levels including and above the specified value will be fully read.
- L56 _public member_ `bool bAdaptivePoleMipUpscaling = false;` — When this is enabled Media Plate will automatically try to figure out the best mip to upscale to reduce the load.
- L58 _public member_ `EMediaTextureTargetViewResolution TargetViewResolutionMask = EMediaTextureTargetViewResolution::RenderResolution;` — Bitwise mask for the target displayed resolution of the media texture (used for mip level estimation).
- L61 _public member_ `TSharedPtr<IMediaTileVisibilityProvider, ESPMode::ThreadSafe> TileVisibilityProvider;` — Optional consumer-supplied tile-visibility provider; takes precedence over VisibleMipsTilesCalculations when set.

#### class `FMediaTextureTracker`  
`class FMediaTextureTracker`  
_L67-138_
- desc: Tracks which media textures are used by which objects.
- L75 _public prototype_ `static FMediaTextureTracker& Get();` — Access engine from here. @return Engine.
- L77 _public prototype_ `virtual ~FMediaTextureTracker() = default;`
- L85 _public prototype_ `void RegisterTexture(TSharedPtr<FMediaTextureTrackerObject, ESPMode::ThreadSafe>& InInfo, TObjectPtr<UMediaTexture> InTexture);` — Each object should call this for each media texture that the object has. @param InInfo Object that has the texture. @param InTexture Texture to register.
- L95 _public prototype_ `void UnregisterTexture(TSharedPtr<FMediaTextureTrackerObject, ESPMode::ThreadSafe>& InInfo, TObjectPtr<UMediaTexture> InTexture);` — Each object should call this for each media texture that the object has. @param InInfo Object that has the texture. @param InTexture Texture to unregister. May be null if the caller has lost the pointer (e.g. the texture was garbage-collected before the owner was destroyed); in that case the tracker scans for InInfo across all registered textures.
- L103 _public prototype_ `const TArray<TWeakPtr<FMediaTextureTrackerObject, ESPMode::ThreadSafe>>* GetObjects(TObjectPtr<UMediaTexture> InTexture) const;` — Get which objects are usnig a specific media texture. @param InTexture Media texture to check. @return Nullptr if nothing found, or a pointer to an array of objects.
- L110 _public function_ `const TArray<TWeakObjectPtr<UMediaTexture>>& GetTextures()` — Get a list of media textures we know about. @ return List of textures.
- L117 _public function_ `FOnMediaTextureTrackerObjectsChanged& OnObjectRegistered()` — Delegate fired after a tracker object has been added for a texture. Subscribe to pick up late registrations.
- L124 _public function_ `FOnMediaTextureTrackerObjectsChanged& OnObjectUnregistered()` — Delegate fired after a tracker object has been removed for a texture.
- L132 _protected member_ `TMap<TWeakObjectPtr<UMediaTexture>, TArray<TWeakPtr<FMediaTextureTrackerObject, ESPMode::ThreadSafe>>> MapTextureToObject;` — Maps a media texture to an array of playback components.
- L134 _protected member_ `TArray<TWeakObjectPtr<UMediaTexture>> MediaTextures;` — Array of media textures that we know about.
- L136 _protected member_ `FOnMediaTextureTrackerObjectsChanged ObjectRegisteredDelegate;`
- L137 _protected member_ `FOnMediaTextureTrackerObjectsChanged ObjectUnregisteredDelegate;`

#### Free symbols / members of external scopes

- L20 _typedef_ `using FMediaTextureTrackerObjectPtr = TSharedPtr<FMediaTextureTrackerObject, ESPMode::ThreadSafe>;` — Workaround to avoid having a comma in the type for the multicast macro.
- L23 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnMediaTextureTrackerObjectsChanged, TObjectPtr<UMediaTexture> , const FMediaTextureTrackerObjectPtr& );` — Fires on register/unregister of a tracker object. Game thread only. Texture may be null on unregister if GC'd.
- L23 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnMediaTextureTrackerObjectsChanged, TObjectPtr<UMediaTexture> , const FMediaTextureTrackerObjectPtr& );` — Fires on register/unregister of a tracker object. Game thread only. Texture may be null on unregister if GC'd.
- L40 _prototype_ `ENUM_CLASS_FLAGS(EMediaTextureTargetViewResolution);`

### `Source/Runtime/MediaAssets/Public/Misc/MediaBlueprintFunctionLibrary.h` (Public)


#### enum `EMediaAudioCaptureDeviceFilter`  
`enum class EMediaAudioCaptureDeviceFilter : uint8`  
_L24-39_
- reflection: `UENUM(BlueprintType, meta=(BitFlags, UseEnumValuesAsMaskValuesInEditor = "true"))`
- desc: Filter flags for the EnumerateAudioCaptureDevices BP function.
- L26 _public enumerator_ `None = 0 UMETA(Hidden)`
- L29 _public enumerator_ `Card = 0x1` — Audio capture cards.
- L32 _public enumerator_ `Microphone = 0x2` — Microphone.
- L35 _public enumerator_ `Software = 0x4` — Software device.
- L38 _public enumerator_ `Unknown = 0x8` — Unknown audio capture device types.

#### enum `EMediaVideoCaptureDeviceFilter`  
`enum class EMediaVideoCaptureDeviceFilter : uint8`  
_L48-63_
- reflection: `UENUM(BlueprintType, meta=(BitFlags, UseEnumValuesAsMaskValuesInEditor = "true"))`
- desc: Filter flags for the EnumerateVideoCaptureDevices BP function.
- L50 _public enumerator_ `None = 0 UMETA(Hidden)`
- L53 _public enumerator_ `Card = 0x1` — Video capture card.
- L56 _public enumerator_ `Software = 0x2` — Software video capture device.
- L59 _public enumerator_ `Unknown = 0x4` — Unknown video capture device types.
- L62 _public enumerator_ `Webcam = 0x8` — Web cam.

#### enum `EMediaWebcamCaptureDeviceFilter`  
`enum class EMediaWebcamCaptureDeviceFilter : uint8`  
_L72-87_
- reflection: `UENUM(BlueprintType, meta=(BitFlags, UseEnumValuesAsMaskValuesInEditor = "true"))`
- desc: Filter flags for the EnumerateWebcamCaptureDevices BP function.
- L74 _public enumerator_ `None = 0 UMETA(Hidden)`
- L77 _public enumerator_ `DepthSensor = 0x1` — Depth sensor.
- L80 _public enumerator_ `Front = 0x2` — Front facing web cam.
- L83 _public enumerator_ `Rear = 0x4` — Rear facing web cam.
- L86 _public enumerator_ `Unknown = 0x8` — Unknown web cam types.

#### struct `FMediaCaptureDevice`  
`struct FMediaCaptureDevice`  
_L96-116_
- reflection: `USTRUCT(BlueprintType)`
- desc: Information about a capture device.
- L102 _public member_ `FText DisplayName;` — `UPROPERTY(Transient, BlueprintReadOnly, Category = "Media Capture Device")` — Human readable display name.
- L106 _public member_ `FString Url;` — `UPROPERTY(Transient, BlueprintReadOnly, Category = "Media Capture Device")` — Media URL string for use with media players.
- L109 _public function_ `FMediaCaptureDevice()` — Default constructor.
- L112 _public function_ `FMediaCaptureDevice(const FText& InDisplayName, const FString& InUrl) : DisplayName(InDisplayName) , Url(InUrl)` — Create and initialize a new instance.

#### class `UMediaBlueprintFunctionLibrary`  
`class UMediaBlueprintFunctionLibrary : public UBlueprintFunctionLibrary`  
_L123-165_
- reflection: `UCLASS(meta=(ScriptName="MediaLibrary"), MinimalAPI)`
- inherits: `UBlueprintFunctionLibrary`
- desc: Blueprint library for Media related functions.
- L140 _public prototype_ `static void EnumerateAudioCaptureDevices(TArray<FMediaCaptureDevice>& OutDevices, int32 Filter = -1);` — `UFUNCTION(BlueprintCallable, Category = "Media|Capture")` — Enumerate available audio capture devices. To filter for a specific subset of devices, use the MakeBitmask node with EMediaAudioCaptureDeviceFilter as the Bitmask Enum. @param OutDevices Will contain the available capture devices. @param Filter The types of capture devices to return (-1 = all).
- L152 _public prototype_ `static void EnumerateVideoCaptureDevices(TArray<FMediaCaptureDevice>& OutDevices, int32 Filter = -1);` — `UFUNCTION(BlueprintCallable, Category = "Media|Capture")` — Enumerate available audio capture devices. To filter for a specific subset of devices, use the MakeBitmask node with EMediaVideoCaptureDeviceFilter as the Bitmask Enum. @param OutDevices Will contain the available capture devices. @param Filter The types of capture devices to return (-1 = all).
- L164 _public prototype_ `static void EnumerateWebcamCaptureDevices(TArray<FMediaCaptureDevice>& OutDevices, int32 Filter = -1);` — `UFUNCTION(BlueprintCallable, Category = "Media|Capture")` — Enumerate available audio capture devices. To filter for a specific subset of devices, use the MakeBitmask node with EMediaWebcamCaptureDeviceFilter as the Bitmask Enum. @param OutDevices Will contain the available capture devices. @param Filter The types of capture devices to return (-1 = all).

### `Source/Runtime/MediaAssets/Public/PlatformMediaSource.h` (Public)


#### class `UPlatformMediaSource`  
`class UPlatformMediaSource : public UMediaSource`  
_L29-93_
- reflection: `UCLASS(BlueprintType, MinimalAPI)`
- inherits: `UMediaSource`
- desc: A media source that selects other media sources based on target platform. Use this asset to override media sources on a per-platform basis.
- L40 _public member_ `TMap<FString, TObjectPtr<UMediaSource>> PlatformMediaSources;` — `UPROPERTY(transient, EditAnywhere, Category=Sources, Meta=(DisplayName="Media Sources"))` — Media sources per platform.
- L44 _private member_ `TMap<FGuid, UMediaSource*> BlindPlatformMediaSources;` — Blind data encountered at load that could not be mapped to a known platform
- L50 _public prototype_ `virtual void PreSave(FObjectPreSaveContext ObjectSaveContext);`
- L51 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L55 _public prototype_ `virtual FString GetUrl() const override;`
- L56 _public prototype_ `virtual bool Validate() const override;`
- L59 _public prototype_ `virtual FString GetDescriptionString() const override;`
- L60 _public prototype_ `virtual void GetDetailsPanelInfoElements(TArray<FInfoElement>& OutInfoElements) const override;`
- L67 _public prototype_ `virtual FName GetDesiredPlayerName() const override;`
- L68 _public prototype_ `virtual bool GetMediaOption(const FName& Key, bool DefaultValue) const override;`
- L69 _public prototype_ `virtual double GetMediaOption(const FName& Key, double DefaultValue) const override;`
- L70 _public prototype_ `virtual int64 GetMediaOption(const FName& Key, int64 DefaultValue) const override;`
- L71 _public prototype_ `virtual FString GetMediaOption(const FName& Key, const FString& DefaultValue) const override;`
- L72 _public prototype_ `virtual FText GetMediaOption(const FName& Key, const FText& DefaultValue) const override;`
- L73 _public prototype_ `virtual bool HasMediaOption(const FName& Key) const override;`
- L82 _private prototype_ `UMediaSource* GetMediaSource() const;` — Get the media source for the running target platform. @return The media source, or nullptr if not set.
- L92 _private member_ `TObjectPtr<UMediaSource> MediaSource;` — `UPROPERTY()` — Default media source. This media source will be used if no source was specified for a target platform.

### `Source/Runtime/MediaAssets/Public/StreamMediaSource.h` (Public)


#### class `UStreamMediaSource`  
`class UStreamMediaSource : public UBaseMediaSource`  
_L16-38_
- reflection: `UCLASS(BlueprintType, MinimalAPI)`
- inherits: `UBaseMediaSource`
- L25 _public member_ `FString StreamUrl;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=Stream, AssetRegistrySearchable)` — The URL to the media stream to be played.
- L31 _public prototype_ `virtual FString GetUrl() const override;`
- L32 _public prototype_ `virtual bool Validate() const override;`
- L35 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`

### `Source/Runtime/MediaAssets/Public/TimeSynchronizableMediaSource.h` (Public)


#### class `UTimeSynchronizableMediaSource`  
`class UTimeSynchronizableMediaSource : public UBaseMediaSource`  
_L30-73_
- reflection: `UCLASS(Abstract, MinimalAPI)`
- inherits: `UBaseMediaSource`
- desc: Base class for media sources that can be synchronized with the engine's timecode.
- L36 _public prototype_ `UTimeSynchronizableMediaSource();` — Default constructor.
- L46 _public member_ `bool bUseTimeSynchronization;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=Synchronization, meta=(DisplayName="Time Synchronization"))` — Synchronize the media with the engine's timecode. The media player has be able to read timecode. The media player will try to play the corresponding frame, base on the frame's timecode value.
- L53 _public member_ `int32 FrameDelay;` — `UPROPERTY(EditAnywhere, Category=Synchronization, meta=(EditCondition="bUseTimeSynchronization", ClampMin = "0", ClampMax = "4"))` — When using Time Synchronization, how many frame back should it read. Capped at 4 frames due to the potential issues with buffer sizes. Framelocked modes don't support this feature.
- L57 _public member_ `double TimeDelay;` — `UPROPERTY(EditAnywhere, Category=Synchronization, meta=(EditCondition="!bUseTimeSynchronization", ForceUnits=s))` — When not using Time Synchronization, how far back it time should it read.
- L61 _public member_ `bool bAutoDetectInput = true;` — `UPROPERTY()` — Whether to autodetect the input or not.
- L66 _public prototype_ `virtual bool GetMediaOption(const FName& Key, bool DefaultValue) const override;`
- L67 _public prototype_ `virtual int64 GetMediaOption(const FName& Key, int64 DefaultValue) const override;`
- L68 _public prototype_ `virtual double GetMediaOption(const FName& Key, double DefaultValue) const override;`
- L69 _public prototype_ `virtual FString GetMediaOption(const FName& Key, const FString& DefaultValue) const override;`
- L70 _public prototype_ `virtual bool HasMediaOption(const FName& Key) const override;`
- L72 _public function_ `virtual bool SupportsFormatAutoDetection() const`

#### Free symbols / members of external scopes

- L17 _namespace_ `namespace TimeSynchronizableMedia`
- L20 _variable_ `static FName UseTimeSynchronizatioOption("Use` (scope `TimeSynchronizableMedia`) — Name of bUseTimeSynchronization media option.
- L21 _variable_ `static FName FrameDelay("Fra` (scope `TimeSynchronizableMedia`)
- L22 _variable_ `static FName TimeDelay("Tim` (scope `TimeSynchronizableMedia`)
- L23 _variable_ `static FName AutoDetect("Aut` (scope `TimeSynchronizableMedia`)
