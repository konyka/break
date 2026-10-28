# Plugins / OpenColorIO

- module root: `Plugins/Compositing/OpenColorIO/Source/OpenColorIO`
- headers: 16; symbols: 419
- symbol kinds: class=19, delegate=2, enum=5, enumerator=11, externvar=1, function=60, macro=10, member=93, namespace=1, prototype=199, struct=15, typedef=3
- DynamicallyLoadedModuleNames: 
- PrivateDependencyModuleNames: DerivedDataCache, EditorFramework, ImageCore, Projects, RHI, RenderCore, Renderer, Slate, SlateCore, TargetPlatform, UnrealEd
- PublicDependencyModuleNames: Core, CoreUObject, DeveloperSettings, Engine, OpenColorIOWrapper

### `Plugins/Compositing/OpenColorIO/Source/OpenColorIO/Private/OpenColorIODerivedDataVersion.h` (Private)


#### Free symbols / members of external scopes

- L13 _macro_ `#define OPENCOLORIO_DERIVEDDATA_VER TEXT("EF2734CC-A92C-4025-A75B-96AB950E5198")` — In case of merge conflicts with DDC versions, you MUST generate a new GUID and set this new guid as version

### `Plugins/Compositing/OpenColorIO/Source/OpenColorIO/Private/OpenColorIOModule.h` (Private)


#### class `FOpenColorIOModule`  
`class FOpenColorIOModule : public IOpenColorIOModule`  
_L20-39_
- inherits: `IOpenColorIOModule`
- desc: Implements the OpenColorIO module.
- L24 _public prototype_ `FOpenColorIOModule();`
- L25 _public prototype_ `virtual ~FOpenColorIOModule() = default;`
- L28 _public prototype_ `virtual void StartupModule() override;`
- L29 _public prototype_ `virtual void ShutdownModule() override;`
- L33 _public prototype_ `virtual FOpenColorIODisplayManager& GetDisplayManager() override;`
- L38 _private member_ `TUniquePtr<FOpenColorIODisplayManager> DisplayManager;`

#### Free symbols / members of external scopes

- L12 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogOpenColorIO, Log, All);`
- L12 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogOpenColorIO, Log, All);`

### `Plugins/Compositing/OpenColorIO/Source/OpenColorIO/Public/IOpenColorIOModule.h` (Public)


#### class `IOpenColorIOModule`  
`class IOpenColorIOModule : public IModuleInterface`  
_L17-47_
- inherits: `IModuleInterface`
- desc: Interface for the OpenColorIO module.
- L26 _public function_ `static inline IOpenColorIOModule& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L37 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() during shutdown if IsAvailable() returns true. @return True if the module is loaded and ready to use
- L46 _public prototype_ `virtual FOpenColorIODisplayManager& GetDisplayManager() = 0;` — Returns the collections of ocio display look currently in play

### `Plugins/Compositing/OpenColorIO/Source/OpenColorIO/Public/OpenColorIOBlueprintLibrary.h` (Public)


#### class `UOpenColorIOBlueprintLibrary`  
`class UOpenColorIOBlueprintLibrary : public UBlueprintFunctionLibrary`  
_L14-29_
- reflection: `UCLASS(MinimalAPI, meta=(ScriptName="OpenColorIOLibrary"))`
- inherits: `UBlueprintFunctionLibrary`
- L28 _private prototype_ `static bool ApplyColorSpaceTransform(const UObject* WorldContextObject, const FOpenColorIOColorConversionSettings& ConversionSettings, UTexture* InputTexture, UTextureRenderTarget2D* OutputRenderTarget);` — `UFUNCTION(BlueprintCallable, Category = "OpenColorIO", meta = (WorldContext = "WorldContextObject"))` — Applies a rendering pass of the color transform described in the settings @param WorldContextObject World from which to get the actual shader feature level we need to render @param ConversionSettings Settings describing the color space transform to apply @param InputTexture Texture in the source color space @param OutputRenderTarget RenderTarget where to draw the input texture in the destination color space @return True if a rendering command to apply the transform was queued.

### `Plugins/Compositing/OpenColorIO/Source/OpenColorIO/Public/OpenColorIOColorSpace.h` (Public)


#### struct `FOpenColorIOColorSpace`  
`struct FOpenColorIOColorSpace`  
_L15-83_
- reflection: `USTRUCT(BlueprintType, meta = (DisplayName = "OpenColorIO Color Space"))`
- desc: Structure to identify a ColorSpace as described in an OCIO configuration file. Members are populated by data coming from a config file.
- L23 _public prototype_ `FOpenColorIOColorSpace() = default;` — Default constructor.
- L24 _public prototype_ `~FOpenColorIOColorSpace() = default;`
- L25 _public prototype_ `FOpenColorIOColorSpace(const FOpenColorIOColorSpace&) = default;`
- L26 _public prototype_ `FOpenColorIOColorSpace(FOpenColorIOColorSpace&&) = default;`
- L27 _public prototype_ `FOpenColorIOColorSpace& operator=(const FOpenColorIOColorSpace&) = default;`
- L28 _public prototype_ `FOpenColorIOColorSpace& operator=(FOpenColorIOColorSpace&&) = default;`
- L34 _public prototype_ `FOpenColorIOColorSpace(const FString& InColorSpaceName, int32 InColorSpaceIndex, const FString& InFamilyName, const FString& InDescription = FString());` — Create and initialize a new instance.
- L38 _public member_ `FString ColorSpaceName;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=ColorSpace)` — The ColorSpace name.
- L44 _public member_ `int32 ColorSpaceIndex_DEPRECATED = INDEX_NONE;` — `UE_DEPRECATED(5.6, "ColorSpaceIndex has been deprecated.")` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "ColorSpaceIndex has been deprecated."))`
- L52 _public member_ `FString FamilyName;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=ColorSpace)` — The family of this ColorSpace as specified in the configuration file. When you have lots of colorspaces, you can regroup them by family to facilitate browsing them.
- L56 _public member_ `FString Description;` — `UPROPERTY()` — Colorspace description.
- L59 _public member_ `static const TCHAR* FamilyDelimiter;` — Delimiter used in the OpenColorIO library to make family hierarchies
- L62 _public function_ `bool operator==(const FOpenColorIOColorSpace& Other) const`
- L63 _public function_ `bool operator!=(const FOpenColorIOColorSpace& Other) const`
- L69 _public prototype_ `FString ToString() const;` — Get the string representation of this color space. @return ColorSpace name.
- L72 _public prototype_ `bool IsValid() const;` — Return true if the index and name have been set properly
- L75 _public prototype_ `void Reset();` — Reset members to default/empty values.
- L82 _public prototype_ `FString GetFamilyNameAtDepth(int32 InDepth) const;` — Return the family name at the desired depth level @param InDepth Desired depth in the family string. 0 == First layer. @return FamilyName at the desired depth. Empty string if depth level doesn't exist.

#### enum `EOpenColorIOViewTransformDirection`  
`enum class EOpenColorIOViewTransformDirection : uint8`  
_L90-94_
- reflection: `UENUM(BlueprintType, meta = (DisplayName = "OpenColorIO View Transform Direction"))`
- desc: Transformation direction type for display-view transformations.
- L92 _public enumerator_ `Forward = 0 UMETA(DisplayName = "Forward")`
- L93 _public enumerator_ `Inverse = 1 UMETA(DisplayName = "Inverse")`

#### struct `FOpenColorIODisplayView`  
`struct FOpenColorIODisplayView`  
_L98-134_
- reflection: `USTRUCT(BlueprintType, meta = (DisplayName = "OpenColorIO Display View"))`
- L104 _public prototype_ `FOpenColorIODisplayView() = default;` — Default constructor.
- L109 _public prototype_ `FOpenColorIODisplayView(FStringView InDisplayName, FStringView InViewName, const FString& InDescription = FString());` — Create and initialize a new instance.
- L113 _public member_ `FString Display;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ColorSpace)` — Display name.
- L117 _public member_ `FString View;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ColorSpace)` — View name.
- L121 _public member_ `FString Description;` — `UPROPERTY()` — Display-view (transform) description.
- L123 _public prototype_ `FString ToString() const;`
- L126 _public prototype_ `bool IsValid() const;` — Return true if the index and name have been set properly
- L129 _public prototype_ `void Reset();` — Reset members to default/empty values.
- L132 _public function_ `bool operator==(const FOpenColorIODisplayView& Other) const`
- L133 _public function_ `bool operator!=(const FOpenColorIODisplayView& Other) const`

#### struct `FOpenColorIOColorConversionSettings`  
`struct FOpenColorIOColorConversionSettings`  
_L140-217_
- reflection: `USTRUCT(BlueprintType, meta = (DisplayName = "OpenColorIO Color Conversion Settings"))`
- desc: Identifies a OCIO ColorSpace conversion.
- L145 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnConversionSettingsChange);`
- L148 _public prototype_ `FOpenColorIOColorConversionSettings();` — Default constructor.
- L152 _public member_ `TObjectPtr<UOpenColorIOConfiguration> ConfigurationSource;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ColorSpace)` — The source color space name.
- L156 _public member_ `FOpenColorIOColorSpace SourceColorSpace;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ColorSpace)` — The source color space name.
- L160 _public member_ `FOpenColorIOColorSpace DestinationColorSpace;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ColorSpace)` — The destination color space name.
- L164 _public member_ `FOpenColorIODisplayView DestinationDisplayView;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ColorSpace)` — The destination display view name.
- L168 _public member_ `EOpenColorIOViewTransformDirection DisplayViewDirection = EOpenColorIOViewTransformDirection::Forward;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ColorSpace)` — The display view direction.
- L172 _public prototype_ `void PostSerialize(const FArchive& Ar);`
- L178 _public prototype_ `FString ToString() const;` — Get a string representation of this conversion. @return String representation, i.e. "ConfigurationAssetName - SourceColorSpace to DestinationColorSpace".
- L183 _public prototype_ `bool IsValid() const;` — Returns true if the source and destination color spaces are found in the configuration file
- L186 _public prototype_ `FString GetSourceString() const;` — Returns a string representing the settings' source
- L189 _public prototype_ `FString GetDestinationString() const;` — Returns a string representing the settings' destination
- L195 _public prototype_ `void Reset(bool bResetConfigurationSource = false);` — Reset members to default/empty values. @param InDepth Desired depth in the family string. 0 == First layer.
- L200 _public prototype_ `void ValidateColorSpaces();` — Ensure that the selected source and destination color spaces are valid, resets them otherwise.
- L202 _public function_ `bool operator==(const FOpenColorIOColorConversionSettings& Other) const`
- L203 _public function_ `bool operator!=(const FOpenColorIOColorConversionSettings& Other) const`
- L206 _public function_ `bool Equals(const FOpenColorIOColorConversionSettings& Other) const` — Determines if this ColorConversionSettings is the same as another.
- L216 _public prototype_ `bool IsDisplayView() const;` — Whether or not these settings are of the display-view type.

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FOpenColorIOColorConversionSettings> : public TStructOpsTypeTraitsBase2<FOpenColorIOColorConversionSettings>`  
_L219-225_
- inherits: `TStructOpsTypeTraitsBase2<FOpenColorIOColorConversionSettings>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L222-224_

#### struct `FOpenColorIODisplayConfiguration`  
`struct FOpenColorIODisplayConfiguration`  
_L231-255_
- reflection: `USTRUCT(BlueprintType, meta = (DisplayName = "OpenColorIO Display Configuration"))`
- desc: Identifies an OCIO Display look configuration
- L241 _public member_ `bool bIsEnabled = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ColorSpace, DisplayName = "Enable OCIO")` — Whether or not this display configuration is enabled Since display look are applied on viewports, this will dictate whether it's applied or not to it
- L245 _public member_ `FOpenColorIOColorConversionSettings ColorConfiguration;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ColorSpace)` — Conversion to apply when this display is enabled
- L247 _public prototype_ `bool Serialize(FArchive& Ar);`
- L248 _public prototype_ `void PostSerialize(const FArchive& Ar);`
- L251 _public function_ `bool Equals(const FOpenColorIODisplayConfiguration& Other) const` — Determines if this DisplayConfiguration is the same as another.

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FOpenColorIODisplayConfiguration> : public TStructOpsTypeTraitsBase2<FOpenColorIODisplayConfiguration>`  
_L257-264_
- inherits: `TStructOpsTypeTraitsBase2<FOpenColorIODisplayConfiguration>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L260-263_

#### Free symbols / members of external scopes

- L145 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnConversionSettingsChange);`
- L223 _enumerator_ `WithPostSerialize = true` (scope `TStructOpsTypeTraits::__anon6232e00a0103`)
- L261 _enumerator_ `WithSerializer = true` (scope `TStructOpsTypeTraits::__anon6232e00a0203`)
- L262 _enumerator_ `WithPostSerialize = true` (scope `TStructOpsTypeTraits::__anon6232e00a0203`)

### `Plugins/Compositing/OpenColorIO/Source/OpenColorIO/Public/OpenColorIOColorTransform.h` (Public)


#### class `UOpenColorIOColorTransform`  
`class UOpenColorIOColorTransform : public UObject`  
_L29-251_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- desc: Object used to generate shader and LUTs from OCIO configuration file and contain required resource to make a color space transform.
- L35 _public prototype_ `UOpenColorIOColorTransform(const FObjectInitializer& ObjectInitializer);`
- L38 _public prototype_ `virtual ~UOpenColorIOColorTransform() = default;`
- L44 _public prototype_ `bool Initialize(const FString& InSourceColorSpace, const FString& InDestinationColorSpace);` — Initialize resources for color space transform.
- L47 _public prototype_ `bool Initialize(const FString& InSourceColorSpace, const FString& InDisplay, const FString& InView, EOpenColorIOViewTransformDirection InDirection);` — Initialize resources for display-view transform.
- L52 _public prototype_ `bool GetRenderResources(ERHIFeatureLevel::Type InFeatureLevel, FOpenColorIOTransformResource*& OutShaderResource, TArray<TWeakObjectPtr<UTexture>>& OutTextureResources) const;` — Returns the desired resources required to apply this transform during rendering.
- L57 _public prototype_ `bool AreRenderResourcesReady() const;` — Returns true if shader/texture resources have finished compiling and are ready for use (to be called on the game thread).
- L62 _public prototype_ `bool IsTransform(const FString& InSourceColorSpace, const FString& InDestinationColorSpace) const;` — Returns true if the current transform corresponds to the specified color spaces.
- L67 _public prototype_ `bool IsTransform(const FString& InSourceColorSpace, const FString& InDisplay, const FString& InView, EOpenColorIOViewTransformDirection InDirection) const;` — Returns true if the current transform corresponds to the specified color space and display/view & direction.
- L75 _public prototype_ `bool GetTransformProcessor(FOpenColorIOWrapperProcessor& OutProcessor, const TMap<FString, FString>& InContextOverride = {}) const;` — Get the transform processor. @param OutProcessor Processor wrapper for the current transform. @return True if the processor was created and is valid.
- L78 _public prototype_ `bool TransformColor(FLinearColor& InOutColor) const;` — Apply the color transform in-place to the specified color.
- L81 _public prototype_ `bool TransformImage(const FImageView& InOutImage) const;` — Apply the color transform in-place to the specified image.
- L84 _public prototype_ `bool TransformImage(const FImageView& SrcImage, const FImageView& DestImage) const;` — Apply the color transform from the source image to the destination image. (The destination FImageView is const but what it points at is not.)
- L92 _public prototype_ `bool GetDisplayViewDirection(EOpenColorIOViewTransformDirection& OutDirection) const;` — Get the display view direction type, when applicable. @param OutDirection The returned direction. @return True if the transformation is of display-view type.
- L95 _public prototype_ `static void AllColorTransformsCacheResourceShadersForRendering();` — For all ColorTransforms, UOpenColorIOColorTransform::CacheResourceShadersForRendering
- L98 _public prototype_ `TMap<FString, FString> GetContextKeyValues() const;` — Get the owner config's context key-values.
- L106 _private prototype_ `void CacheResourceShadersForRendering(bool bRegenerateId = false);` — Cache resource shaders for rendering. If a matching shader map is not found in memory or the DDC, a new one will be compiled.
- L108 _private prototype_ `void CacheShadersForResources(EShaderPlatform InShaderPlatform, FOpenColorIOTransformResource* InResourcesToCache, bool bApplyCompletedShaderMapForRendering, bool bIsCooking, const ITargetPlatform* TargetPlatform = nullptr);`
- L113 _private prototype_ `static void SerializeOpenColorIOShaderMaps(const TMap<const ITargetPlatform*, TArray<FOpenColorIOTransformResource*>>* PlatformColorTransformResourcesToSavePtr, FArchive& Ar, TArray<FOpenColorIOTransformResource>& OutLoadedResources);` — Helper function to serialize shader maps for the given color transform resources.
- L118 _private prototype_ `static void ProcessSerializedShaderMaps(UOpenColorIOColorTransform* Owner, TArray<FOpenColorIOTransformResource>& LoadedResources, FOpenColorIOTransformResource* (&OutColorTransformResourcesLoaded)[ERHIFeatureLevel::Num]);` — Helper function to register serialized shader maps for the given color transform resources
- L123 _private prototype_ `static void GetOpenColorIOLUTKeyGuid(const FString& InProcessorIdentifier, const FName& InName, FGuid& OutLutGuid );` — Returns a Guid for the LUT based on its unique identifier, name and the OCIO DDC key.
- L128 _private prototype_ `FString GetTransformFriendlyName() const;` — Helper function returning the color space transform name based on source and destination color spaces.
- L135 _private prototype_ `bool UpdateShaderInfo(FString& OutShaderCodeHash, FString& OutShaderCode, FString& OutRawConfigHash);` — Fetch shader code and hash from the OCIO library @return: true if shader could be generated from the library
- L140 _private prototype_ `TObjectPtr<UTexture> CreateTexture3DLUT(const FString& InProcessorIdentifier, const FName& InName, uint32 InLutLength, TextureFilter InFilter, const float* InSourceData);` — Helper function taking raw 3D LUT data coming from the library and initializing a UVolumeTexture with it.
- L145 _private prototype_ `TObjectPtr<UTexture> CreateTexture1DLUT(const FString& InProcessorIdentifier, const FName& InName, uint32 InTextureWidth, uint32 InTextureHeight, TextureFilter InFilter, bool bRedChannelOnly, const float* InSourceData );` — Helper function taking raw 1D LUT data coming from the library and initializing a UTexture with it.
- L150 _private prototype_ `void ProcessTransformForGPU();` — Create the transform processor(s) and generate its resources. Editor-only, in game mode GPU resources are already present.
- L154 _private prototype_ `void FlushResourceShaderMaps();` — Release all shader maps.
- L157 _private prototype_ `FShaderParametersMetadata* BuildShaderParamMetadata();` — Create the shader parameter metadata, using our built-in struct and any LUT-associated texture and sampler resources.
- L162 _public prototype_ `void Serialize(FArchive& Ar) override;`
- L163 _public prototype_ `virtual void PostLoad() override;`
- L165 _public prototype_ `static void DeclareConstructClasses(TArray<FTopLevelAssetPath>& OutConstructClasses, const UClass* SpecificSubclass);`
- L168 _public prototype_ `virtual void BeginDestroy() override;`
- L169 _public prototype_ `virtual bool IsReadyForFinishDestroy() override;`
- L170 _public prototype_ `virtual void FinishDestroy() override;`
- L179 _public prototype_ `void CacheResourceShadersForCooking(EShaderPlatform InShaderPlatform, const ITargetPlatform* TargetPlatform, const FString& InShaderHash, const FString& InShaderCode, const FString& InRawConfigHash, TArray<FOpenColorIOTransformResource*>& OutCachedResources);` — Cache resource shaders for cooking on the given shader platform. If a matching shader map is not found in memory or the DDC, a new one will be compiled. This does not apply completed results to the renderer scenes. Caller is responsible for deleting OutCachedResource.
- L181 _public prototype_ `virtual void BeginCacheForCookedPlatformData(const ITargetPlatform* TargetPlatform) override;`
- L182 _public prototype_ `virtual bool IsCachedCookedPlatformDataLoaded(const ITargetPlatform* TargetPlatform) override;`
- L183 _public prototype_ `virtual void ClearCachedCookedPlatformData(const ITargetPlatform *TargetPlatform) override;`
- L184 _public prototype_ `virtual void ClearAllCachedCookedPlatformData() override;`
- L194 _public prototype_ `void ReleaseResources();` — Releases rendering resources used by this color transform. This should only be called directly if the ColorTransform will not be deleted through the GC system afterward. FlushRenderingCommands() must have been called before this.
- L199 _public member_ `bool bIsDisplayViewType = false;` — `UPROPERTY(VisibleAnywhere, Category = "ColorSpace")`
- L202 _public member_ `FString SourceColorSpace;` — `UPROPERTY(VisibleAnywhere, Category = "ColorSpace")`
- L205 _public member_ `FString DestinationColorSpace;` — `UPROPERTY(VisibleAnywhere, Category = "ColorSpace")`
- L208 _public member_ `FString Display;` — `UPROPERTY(VisibleAnywhere, Category = "ColorSpace")`
- L211 _public member_ `FString View;` — `UPROPERTY(VisibleAnywhere, Category = "ColorSpace")`
- L214 _public member_ `EOpenColorIOViewTransformDirection DisplayViewDirection = EOpenColorIOViewTransformDirection::Forward;` — `UPROPERTY(VisibleAnywhere, Category = "ColorSpace")`
- L220 _private member_ `TMap<int32, TObjectPtr<UTexture>> Textures_DEPRECATED;` — `UE_DEPRECATED(5.6, "Map of textures has been deprecated in favor of an array.")` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "Map of textures has been deprecated in favor of an array."))`
- L225 _private member_ `TArray<TObjectPtr<UTexture>> LookupTextures;` — `UPROPERTY()` — If the color space transform requires LUTs, this will contains the texture data to do the transform
- L230 _private member_ `FString GeneratedShaderHash;` — `UPROPERTY()` — Generated transform shader hash.
- L234 _private member_ `FString GeneratedShader;` — `UPROPERTY()` — Generated transform shader function.
- L238 _private member_ `TArray<FOpenColorIOTransformResource> LoadedTransformResources;` — Inline ColorTransform resources serialized from disk. To be processed on game thread in PostLoad.
- L240 _private member_ `FOpenColorIOTransformResource* ColorTransformResources[ERHIFeatureLevel::Num];`
- L242 _private member_ `FRenderCommandFence ReleaseFence;`

#### Free symbols / members of external scopes

- L17 _macro_ `#define UE_API OPENCOLORIO_API`

### `Plugins/Compositing/OpenColorIO/Source/OpenColorIO/Public/OpenColorIOConfiguration.h` (Public)


#### class `UOpenColorIOConfiguration`  
`class UOpenColorIOConfiguration : public UObject`  
_L29-195_
- reflection: `UCLASS(MinimalAPI, BlueprintType, meta = (DisplayName = "OpenColorIO Configuration"))`
- inherits: `UObject`
- desc: Asset to manage allowed OpenColorIO color spaces. This will create required transform objects.
- L35 _public prototype_ `UOpenColorIOConfiguration(const FObjectInitializer& ObjectInitializer);`
- L40 _public prototype_ `bool IsTransformReady(const FOpenColorIOColorConversionSettings& InSettings);` — Check if the transform resources (shader & optionally lookup textures) are ready for use.
- L43 _public prototype_ `bool GetRenderResources(ERHIFeatureLevel::Type InFeatureLevel, const FOpenColorIOColorConversionSettings& InSettings, FOpenColorIOTransformResource*& OutShaderResource, TArray<TWeakObjectPtr<UTexture>>& OutTextureResources);` — Get the shader and optionally lookup texture resources to be used by the color transform render pass specified by the settings parameter.
- L46 _public prototype_ `bool HasTransform(const FString& InSourceColorSpace, const FString& InDestinationColorSpace);` — Check if this configuration contains a transform from the specified source & destination color spaces.
- L49 _public prototype_ `bool HasTransform(const FString& InSourceColorSpace, const FString& InDisplay, const FString& InView, EOpenColorIOViewTransformDirection InDirection);` — Check if this configuration contains a transform from the specified source color space & view destination.
- L52 _public prototype_ `bool HasDesiredColorSpace(const FOpenColorIOColorSpace& ColorSpace) const;` — Check if this configuration contains a color space.
- L55 _public prototype_ `bool HasDesiredDisplayView(const FOpenColorIODisplayView& DisplayView) const;` — Check if this configuration contains a display-view.
- L58 _public prototype_ `bool Validate() const;` — Check if this configuration is valid. (TODO: Rename to avoid confusion with config validation calls provided by the library.)
- L61 _public prototype_ `bool TransformColor(const FOpenColorIOColorConversionSettings& InSettings, FLinearColor& InOutColor) const;` — Apply the color transform in-place to the specified image.
- L64 _public prototype_ `bool TransformImage(const FOpenColorIOColorConversionSettings& InSettings, const FImageView& InOutImage) const;` — Apply the color transform in-place to the specified image.
- L67 _public prototype_ `bool TransformImage(const FOpenColorIOColorConversionSettings& InSettings, const FImageView& SrcImage, const FImageView& DestImage) const;` — Apply the color transform from the source image to the destination image. (The destination FImageView is const but what it points at is not.)
- L71 _public prototype_ `void ReloadExistingColorspaces(bool bForce = false);` — `UFUNCTION(BlueprintCallable, Category = "OpenColorIO")` — This forces to reload colorspaces and corresponding shaders if those are not loaded already.
- L77 _public prototype_ `void ConfigPathChangedEvent(const TArray<FFileChangeData>& InFileChanges, const FString InFileMountPath);` — This method is called by directory watcher when any file or folder is changed in the directory where raw ocio config is located.
- L82 _public prototype_ `FOpenColorIOWrapperConfig* GetConfigWrapper() const;` — Get the private wrapper implementation of the OCIO config.
- L88 _public prototype_ `FOpenColorIOWrapperConfig* GetOrCreateConfigWrapper();` — Get or create the private wrapper implementation of the OCIO config. Useful for non-editor modes where the config isn't automatically loaded.
- L91 _public prototype_ `TObjectPtr<const UOpenColorIOColorTransform> FindTransform(const FOpenColorIOColorConversionSettings& InSettings) const;` — Find the color transform object that corresponds to the specified settings, nullptr if not found.
- L95 _protected prototype_ `void CreateColorTransform(const FString& InSourceColorSpace, const FString& InDestinationColorSpace);`
- L96 _protected prototype_ `void CreateColorTransform(const FString& InSourceColorSpace, const FString& InDisplay, const FString& InView, EOpenColorIOViewTransformDirection InDirection);`
- L98 _protected prototype_ `void CleanupTransforms();`
- L101 _protected prototype_ `void StartDirectoryWatch(const FString& FilePath);` — Same as above except user can specify the path manually.
- L104 _protected prototype_ `void StopDirectoryWatch();` — Stop watching the current directory.
- L109 _public prototype_ `virtual void PostInitProperties() override;`
- L110 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L111 _public prototype_ `virtual void PostLoad() override;`
- L112 _public prototype_ `virtual void GetAssetRegistryTags(FAssetRegistryTagsContext RegistryTagsContext) const override;`
- L114 _public prototype_ `static void DeclareConstructClasses(TArray<FTopLevelAssetPath>& OutConstructClasses, const UClass* SpecificSubclass);`
- L117 _public prototype_ `virtual void PreSave(FObjectPreSaveContext SaveContext) override;`
- L118 _public prototype_ `virtual void BeginDestroy() override;`
- L121 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L128 _private prototype_ `void LoadConfiguration();` — Load the config file to initialize the configuration wrapper object. Automatically called internally.
- L131 _private prototype_ `bool GetHash(FString& OutHash) const;` — Obtain the hash of the config and additional dependent state such as library version, working color space and context.
- L135 _private prototype_ `void OnToastCallback(bool bInReloadColorspaces);` — This method resets the status of Notification dialog and reacts depending on user's choice.
- L142 _public function_ `const FFilePath& GetConfigurationFile() const` — `UFUNCTION(BlueprintGetter)` — Get the configuration file path.
- L146 _public prototype_ `void SetConfigurationFile(const FFilePath& InFilePath);` — `UFUNCTION(BlueprintSetter)` — Set the configuration file path.
- L150 _public member_ `TArray<FOpenColorIOColorSpace> DesiredColorSpaces;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Transform")` — Desired color space tranforms.
- L154 _public member_ `TArray<FOpenColorIODisplayView> DesiredDisplayViews;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Transform", DisplayName="Desired Display-Views")` — Desired display view tranforms.
- L160 _public member_ `TMap<FString, FString> Context;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Transform")` — OCIO context of key-value string pairs, typically used to apply shot-specific looks (such as a CDL color correction, or a 1D grade LUT).
- L165 _private member_ `FFilePath ConfigurationFile;` — `UPROPERTY(EditAnywhere, BlueprintGetter = GetConfigurationFile, BlueprintSetter = SetConfigurationFile, Category = "Config", meta = (AllowPrivateAccess = true, FilePathFilter = "Config Files (*.ocio, *.ocioz)|*.ocio;*.ocioz", RelativeToGameDir))` — Configuration file path.
- L168 _private member_ `TArray<TObjectPtr<UOpenColorIOColorTransform>> ColorTransforms;` — `UPROPERTY()`
- L184 _private member_ `FOCIOConfigWatchedDirInfo WatchedDirectoryInfo;` — Information about the currently watched directory. Helps us manage the directory change events.
- L187 _private member_ `TPimplPtr<FOpenColorIOWrapperConfig> Config = nullptr;` — Private implementation of the OpenColorIO config object.
- L191 _private member_ `FString ConfigHash;` — `UPROPERTY()` — Hash of all of the config content, including relevant external file information.

#### struct `UOpenColorIOConfiguration::FOCIOConfigWatchedDirInfo`  
`struct FOCIOConfigWatchedDirInfo`  
_L171-181_
- L174 _public member_ `FDelegateHandle DirectoryWatcherHandle;` — A handle to the directory watcher. Gives us the ability to control directory watching status.
- L177 _public member_ `FString FolderPath;` — Currently watched folder.
- L180 _public member_ `TWeakPtr<SNotificationItem> RawConfigChangedToast;` — A handle to Notification message that pops up to notify user of raw config file going out of date.

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API OPENCOLORIO_API`
- L23 _namespace_ `namespace ERHIFeatureLevel`

### `Plugins/Compositing/OpenColorIO/Source/OpenColorIO/Public/OpenColorIODisplayExtension.h` (Public)


#### class `FOpenColorIODisplayExtension`  
`class FOpenColorIODisplayExtension : public FSceneViewExtensionBase, public FGCObject`  
_L23-69_
- inherits: `FSceneViewExtensionBase,FGCObject`
- desc: View extension applying an OCIO Display Look to the viewport we're attached to
- L27 _public prototype_ `FOpenColorIODisplayExtension(const FAutoRegister& AutoRegister, FViewportClient* AssociatedViewportClient = nullptr);`
- L30 _public function_ `virtual int32 GetPriority() const override`
- L31 _public prototype_ `virtual void SetupView(FSceneViewFamily& InViewFamily, FSceneView& InView) override;`
- L33 _public prototype_ `virtual void SubscribeToPostProcessingPass(EPostProcessingPass PassId, const FSceneView& View, FAfterPassCallbackDelegateArray& InOutPassCallbacks, bool bIsPassEnabled) override;`
- L34 _public prototype_ `virtual bool IsActiveThisFrame_Internal(const FSceneViewExtensionContext& Context) const override;`
- L37 _public prototype_ `FScreenPassTexture PostProcessPassAfterTonemap_RenderThread(FRDGBuilder& GraphBuilder, const FSceneView& View, const FPostProcessMaterialInputs& Inputs);`
- L40 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;`
- L41 _public function_ `virtual FString GetReferencerName() const override`
- L47 _public function_ `void SetDisplayConfiguration(const FOpenColorIODisplayConfiguration& InDisplayConfiguration)`
- L50 _public function_ `FViewportClient* GetAssociatedViewportClient()` — Returns the ViewportClient this extension is currently attached to
- L53 _public function_ `const FOpenColorIODisplayConfiguration& GetDisplayConfiguration() const` — Returns the current display configuration in a const manner
- L56 _public function_ `FOpenColorIODisplayConfiguration& GetDisplayConfiguration()` — Returns the current display configuration to be updated
- L61 _private member_ `FOpenColorIORenderPassResources CachedResourcesRenderThread;` — Cached pass resources required to apply conversion for render thread
- L64 _private member_ `FOpenColorIODisplayConfiguration DisplayConfiguration;` — Configuration to apply during post render callback
- L67 _private member_ `FViewportClient* LinkedViewportClient = nullptr;` — ViewportClient to which we are attached

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API OPENCOLORIO_API`
- L18 _macro_ `#define OPENCOLORIO_SCENE_VIEW_EXTENSION_PRIORITY 100`

### `Plugins/Compositing/OpenColorIO/Source/OpenColorIO/Public/OpenColorIODisplayExtensionWrapper.h` (Public)


#### class `UOpenColorIODisplayExtensionWrapper`  
`class UOpenColorIODisplayExtensionWrapper : public UObject`  
_L17-62_
- reflection: `UCLASS(MinimalAPI, Blueprintable, meta = (DisplayName = "OpenColorIO Display Extension Wrapper"))`
- inherits: `UObject`
- desc: This Blueprintable object can hold an OCIO Scene View Extension. You can change its OCIO config, and specify the context in which you want it to be active on.
- L25 _public prototype_ `FOpenColorIODisplayConfiguration GetOpenColorIOConfiguration() const;` — `UFUNCTION(BlueprintCallable, meta = (DisplayName = "Get OpenColorIO Configuration"), Category = "OpenColorIO")` — Gets the display extension OCIO configuration.
- L29 _public prototype_ `void SetOpenColorIOConfiguration(FOpenColorIODisplayConfiguration InDisplayConfiguration);` — `UFUNCTION(BlueprintCallable, meta = (DisplayName = "Set OpenColorIO Configuration"), Category = "OpenColorIO")` — Sets the display extension OCIO configuration.
- L33 _public prototype_ `void SetSceneExtensionIsActiveFunction(const FSceneViewExtensionIsActiveFunctor& IsActiveFunction);` — `UFUNCTION(BlueprintCallable, Category = "OpenColorIO")` — Sets a single activation function. Will remove any others.
- L37 _public prototype_ `void SetSceneExtensionIsActiveFunctions(const TArray<FSceneViewExtensionIsActiveFunctor>& IsActiveFunctions);` — `UFUNCTION(BlueprintCallable, Category = "OpenColorIO")` — Sets an array of activation functions. Will remove any others.
- L41 _public prototype_ `void RemoveSceneExtension();` — `UFUNCTION(BlueprintCallable, Category = "OpenColorIO")` — Removes the extension.
- L45 _public prototype_ `static UOpenColorIODisplayExtensionWrapper* CreateOpenColorIODisplayExtension( FOpenColorIODisplayConfiguration InDisplayConfiguration, const FSceneViewExtensionIsActiveFunctor& IsActiveFunction);` — `UFUNCTION(BlueprintCallable, meta = (DisplayName = "Create OpenColorIO Display Extension"), Category = "OpenColorIO")` — Creates an instance of this object, configured with the given arguments (OCIO and activation function).
- L51 _public prototype_ `static UOpenColorIODisplayExtensionWrapper* CreateInGameOpenColorIODisplayExtension( FOpenColorIODisplayConfiguration InDisplayConfiguration);` — `UFUNCTION(BlueprintCallable, meta = (DisplayName = "Create In-Game OpenColorIO Display Extension"), Category = "OpenColorIO")` — Creates an instance of this object, configured for use in game with the given OCIO configuration.
- L56 _private prototype_ `void CreateDisplayExtensionIfNotExists();` — Creates OCIO Extension if it doesn't exist.
- L61 _private member_ `TSharedPtr<FOpenColorIODisplayExtension, ESPMode::ThreadSafe> DisplayExtension;` — Holds the OCIO Extension.

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API OPENCOLORIO_API`

### `Plugins/Compositing/OpenColorIO/Source/OpenColorIO/Public/OpenColorIODisplayManager.h` (Public)


#### class `FOpenColorIODisplayManager`  
`class FOpenColorIODisplayManager : public TSharedFromThis<FOpenColorIODisplayManager>`  
_L15-35_
- inherits: `TSharedFromThis<FOpenColorIODisplayManager>`
- L20 _public prototype_ `FOpenColorIODisplayConfiguration& FindOrAddDisplayConfiguration(FViewportClient* InViewportClient);` — Will return the configuration associated to the desired viewport or create one if it's not tracked
- L23 _public prototype_ `const FOpenColorIODisplayConfiguration* GetDisplayConfiguration(const FViewportClient* InViewportClient) const;` — Returns the configuration for a given viewport if it was found, nullptr otherwise
- L26 _public prototype_ `bool RemoveDisplayConfiguration(const FViewportClient* InViewportClient);` — Remove display configuration associated with this viewport
- L29 _public prototype_ `bool IsTrackingViewport(const FViewportClient* InViewportClient) const;` — Whether or not InViewport has a display configuration linked to it
- L34 _protected member_ `TArray<TSharedPtr<FOpenColorIODisplayExtension, ESPMode::ThreadSafe>> DisplayExtensions;` — List of DisplayExtension created when a viewport is asked to be tracked. It contains the configuration.

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API OPENCOLORIO_API`

### `Plugins/Compositing/OpenColorIO/Source/OpenColorIO/Public/OpenColorIORendering.h` (Public)


#### struct `FOpenColorIORenderPassResources`  
`struct FOpenColorIORenderPassResources`  
_L25-38_
- desc: Resources needed by the FOpenColorIORendering pass function.
- L28 _public member_ `FOpenColorIOTransformResource* ShaderResource = nullptr;` — Color transform pass (generated) shader.
- L31 _public member_ `TArray<TWeakObjectPtr<UTexture>> TextureResources = {};` — Collection of LUT textures needed by the shader.
- L34 _public member_ `FString TransformName = FString();` — Color transform string description.
- L37 _public function_ `bool IsValid() const` — Resources are valid when the shader resource is not null.

#### enum `EOpenColorIOTransformAlpha`  
`enum class EOpenColorIOTransformAlpha : uint32`  
_L41-46_
- desc: Option to transform the render target alpha before applying the color transform.
- L43 _public enumerator_ `None = 0`
- L44 _public enumerator_ `Unpremultiply = 1`
- L45 _public enumerator_ `InvertUnpremultiply = 2`

#### class `FOpenColorIORendering`  
`class FOpenColorIORendering`  
_L49-119_
- desc: Entry point to trigger OpenColorIO conversion rendering
- L52 _public prototype_ `FOpenColorIORendering() = delete;`
- L63 _public prototype_ `static bool ApplyColorTransform(UWorld* InWorld, const FOpenColorIOColorConversionSettings& InSettings, UTexture* InTexture, UTextureRenderTarget2D* OutRenderTarget);` — Applies the color transform described in the settings @param InWorld World from which to get the actual shader feature level we need to render @param InSettings Settings describing the color space transform to apply @param InTexture Texture in the source color space @param OutRenderTarget RenderTarget where to draw the input texture in the destination color space @return True if a rendering command to apply the transform was queued.
- L73 _public prototype_ `static FOpenColorIORenderPassResources GetRenderPassResources(const FOpenColorIOColorConversionSettings& InSettings, ERHIFeatureLevel::Type InFeatureLevel);` — Get render pass resources on the game thread, to be enqueue-copied for later use by the `AddPass_RenderThread` function. @param InSettings Settings describing the color space transform to apply @param InFeatureLevel Rendering feature level @return FOpenColorIORenderPassResources Render pass resources to be enqueue-copied onto the render thread.
- L87 _public prototype_ `static void AddPass_RenderThread( FRDGBuilder& GraphBuilder, FScreenPassViewInfo ViewInfo, ERHIFeatureLevel::Type FeatureLevel, const FScreenPassTexture& Input, const FScreenPassRenderTarget& Output, const FOpenColorIORenderPassResources& InPassInfo, float InGamma, EOpenColorIOTransformAlpha TransformAlpha = EOpenColorIOTransformAlpha::None);` — Applies the color transform RDG pass with the provided resources. @param GraphBuilder Render graph builder @param ViewInfo Scene view with additional information @param FeatureLevel - Shader model. @param Input Input color texture @param Output Destination render target @param InPassInfo OpenColorIO shader and texture resources @param InGamma Display gamma @param TransformAlpha Whether to unpremult/invert before applying the color transform
- L107 _public prototype_ `static void AddPass_RenderThread( FRDGBuilder& GraphBuilder, const FSceneView& View, const FScreenPassTexture& Input, const FScreenPassRenderTarget& Output, const FOpenColorIORenderPassResources& InPassInfo, EOpenColorIOTransformAlpha TransformAlpha = EOpenColorIOTransformAlpha::None);` — Similar to the above, except gamma and feature level are handled by the function itself based on provided View. @param GraphBuilder Render graph builder @param View Scene view with additional information @param Input Input color texture @param Output Destination render target @param InPassInfo OpenColorIO shader and texture resources @param TransformAlpha Whether to unpremult/invert before applying the color transform
- L118 _public prototype_ `static void PrepareView(FSceneViewFamily& InViewFamily, FSceneView& InView);` — This function sets up provided view and related family to properly support OCIO.

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API OPENCOLORIO_API`

### `Plugins/Compositing/OpenColorIO/Source/OpenColorIO/Public/OpenColorIOSettings.h` (Public)


#### class `UOpenColorIOSettings`  
`class UOpenColorIOSettings : public UDeveloperSettings`  
_L18-52_
- reflection: `UCLASS(MinimalAPI, config = Engine, defaultconfig)`
- inherits: `UDeveloperSettings`
- desc: Rendering settings.
- L23 _public prototype_ `UOpenColorIOSettings();`
- L26 _public prototype_ `virtual FName GetCategoryName() const;`
- L28 _public prototype_ `virtual FText GetSectionText() const override;`
- L29 _public prototype_ `virtual FName GetSectionName() const override;`
- L39 _public member_ `uint8 bUseLegacyProcessor : 1;` — `UPROPERTY(config, EditAnywhere, Category = Transform, meta = ( DisplayName = "Enable Legacy Gpu Processor", ToolTip = "Whether to enable OCIO V1's legacy gpu processor.", ConfigRestartRequired = true))`
- L45 _public member_ `uint8 bUse32fLUT : 1;` — `UPROPERTY(config, EditAnywhere, Category = Transform, meta = ( DisplayName = "32-bit float LUTs", ToolTip = "Whether to create lookup table texture resources in 32-bit float format (higher performance requirements).", ConfigRestartRequired = true))`
- L51 _public member_ `uint8 bSupportInverseViewTransforms : 1;` — `UPROPERTY(config, EditAnywhere, Category = Transform, meta = ( DisplayName = "Support inverse view transforms", ToolTip = "Whether inverse view transforms are cached and supported. Disabled by default, to minimize the number of transform combinations.", ConfigRestartRequired = true))`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API OPENCOLORIO_API`

### `Plugins/Compositing/OpenColorIO/Source/OpenColorIO/Public/OpenColorIOShader.h` (Public)


#### class `FOpenColorIOPixelShader`  
`class FOpenColorIOPixelShader : public FGlobalShader`  
_L26-39_
- inherits: `FGlobalShader`
- L31 _public prototype_ `FOpenColorIOPixelShader() = default;`
- L32 _public prototype_ `FOpenColorIOPixelShader( const FOpenColorIOShaderType::CompiledShaderInitializerType& Initializer );`

#### struct `FOpenColorIOPixelShader::FParameters`  
`MS_ALIGN(SHADER_PARAMETER_STRUCT_ALIGNMENT) struct FParameters`  
_L36-38_

#### class `FOpenColorIOInvalidPixelShader`  
`class FOpenColorIOInvalidPixelShader : public FGlobalShader`  
_L48-55_
- inherits: `FGlobalShader`
- L52 _public prototype_ `SHADER_USE_PARAMETER_STRUCT(FOpenColorIOInvalidPixelShader, FGlobalShader);`
- L54 _public typedef_ `using FParameters = FOpenColorIOInvalidShaderParameters;`

#### Free symbols / members of external scopes

- L57 _prototype_ `FRHITexture* OpenColorIOGetMiniFontTexture();`

### `Plugins/Compositing/OpenColorIO/Source/OpenColorIO/Public/OpenColorIOShaderCompilationManager.h` (Public)


#### struct `FOpenColorIOShaderCompileWorkerInfo`  
`struct FOpenColorIOShaderCompileWorkerInfo`  
_L14-51_
- desc: Information tracked for each shader compile worker process instance.
- L17 _public member_ `FProcHandle WorkerProcess;` — Process handle of the worker app once launched.  Invalid handle means no process.
- L20 _public member_ `bool bIssuedTasksToWorker;` — Tracks whether tasks have been issued to the worker.
- L23 _public member_ `bool bLaunchedWorker;` — Whether the worker has been launched for this set of tasks.
- L26 _public member_ `bool bComplete;` — Tracks whether all tasks issued to the worker have been received.
- L29 _public member_ `double StartTime;` — Time at which the worker started the most recent batch of tasks.
- L32 _public member_ `TArray<FShaderCommonCompileJobPtr> QueuedJobs;` — Jobs that this worker is responsible for compiling.
- L34 _public function_ `FOpenColorIOShaderCompileWorkerInfo() : bIssuedTasksToWorker(false), bLaunchedWorker(false), bComplete(false), StartTime(0)`
- L43 _public function_ `~FOpenColorIOShaderCompileWorkerInfo()` — warning: not virtual

#### struct `FOpenColorIOShaderMapCompileResults`  
`struct FOpenColorIOShaderMapCompileResults`  
_L55-65_
- desc: Results for a single compiled shader map.
- L57 _public function_ `FOpenColorIOShaderMapCompileResults() : NumJobsQueued(0), bAllJobsSucceeded(true)`
- L62 _public member_ `int32 NumJobsQueued;`
- L63 _public member_ `bool bAllJobsSucceeded;`
- L64 _public member_ `TArray<FShaderCommonCompileJobPtr> FinishedJobs;`

#### struct `FOpenColorIOShaderMapFinalizeResults`  
`struct FOpenColorIOShaderMapFinalizeResults : public FOpenColorIOShaderMapCompileResults`  
_L69-78_
- inherits: `FOpenColorIOShaderMapCompileResults`
- desc: Results for a single compiled and finalized shader map.
- L72 _public member_ `int32 FinalizeJobIndex;` — Tracks finalization progress on this shader map.
- L74 _public function_ `FOpenColorIOShaderMapFinalizeResults(const FOpenColorIOShaderMapCompileResults& InCompileResults) : FOpenColorIOShaderMapCompileResults(InCompileResults), FinalizeJobIndex(0)`

#### class `FOpenColorIOShaderCompilationManager`  
`class FOpenColorIOShaderCompilationManager`  
_L83-109_
- desc: handles finished shader compile jobs, applying of the shaders to their config asset, and some error handling
- L86 _public prototype_ `FOpenColorIOShaderCompilationManager();`
- L87 _public prototype_ `~FOpenColorIOShaderCompilationManager();`
- L89 _public prototype_ `void Tick(float DeltaSeconds = 0.0f);`
- L90 _public prototype_ `void AddJobs(TArray<FShaderCommonCompileJobPtr> InNewJobs);`
- L91 _public prototype_ `void ProcessAsyncResults();`
- L93 _public prototype_ `void FinishCompilation(const TCHAR* InTransformName, const TArray<int32>& ShaderMapIdsToFinishCompiling);`
- L96 _private prototype_ `void ProcessCompiledOpenColorIOShaderMaps(TMap<int32, FOpenColorIOShaderMapFinalizeResults>& CompiledShaderMaps, float TimeBudget);`
- L98 _private prototype_ `void InitWorkerInfo();`
- L100 _private member_ `TArray<FShaderCommonCompileJobPtr> JobQueue;`
- L103 _private member_ `TMap<int32, FOpenColorIOShaderMapCompileResults> OpenColorIOShaderMapJobs;` — Map from shader map Id to the compile results for that map, used to gather compiled results.
- L106 _private member_ `TMap<int32, FOpenColorIOShaderMapFinalizeResults> PendingFinalizeOpenColorIOShaderMaps;` — Map from shader map id to results being finalized.  Used to track shader finalizations over multiple frames.
- L108 _private member_ `TArray<struct FOpenColorIOShaderCompileWorkerInfo*> WorkerInfos;`

#### Free symbols / members of external scopes

- L111 _externvar_ `extern FOpenColorIOShaderCompilationManager GOpenColorIOShaderCompilationManager;`

### `Plugins/Compositing/OpenColorIO/Source/OpenColorIO/Public/OpenColorIOShaderType.h` (Public)


#### struct `FOpenColorIOShaderPermutationParameters`  
`struct FOpenColorIOShaderPermutationParameters : public FGlobalShaderPermutationParameters`  
_L33-41_
- inherits: `FGlobalShaderPermutationParameters`
- L35 _public member_ `const FOpenColorIOTransformResource* Transform;`
- L37 _public function_ `FOpenColorIOShaderPermutationParameters(FName InGlobalShaderName, EShaderPlatform InPlatform, const FOpenColorIOTransformResource* InTransform) : FGlobalShaderPermutationParameters(InGlobalShaderName, InPlatform) , Transform(InTransform)`

#### class `FOpenColorIOShaderType`  
`class FOpenColorIOShaderType : public FShaderType`  
_L46-176_
- inherits: `FShaderType`
- desc: A shader meta type for OpenColorIO-linked shaders.
- L76 _public function_ `FOpenColorIOShaderType( FTypeLayoutDesc& InTypeLayout, const TCHAR* InName, const TCHAR* InSourceFilename, const TCHAR* InFunctionName, uint32 InFrequency,`
- L133 _public prototype_ `void BeginCompileShader( uint32 ShaderMapId, const FOpenColorIOTransformResource* InColorTransform, FSharedShaderCompilerEnvironment* CompilationEnvironment, EShaderPlatform Platform, TArray<TRefCountPtr<class FShaderCommonCompileJob>>& NewJobs, FShaderTarget Target );` — Enqueues a compilation for a new shader of this type. @param InColorTransform - The ColorTransform to link the shader with.
- L149 _public prototype_ `FShader* FinishCompileShader( uint64 InOCIOShaderMapHash, const FShaderCompileJob& CurrentJob, const FString& InDebugDescription ) const;` — Either creates a new instance of this type or returns an equivalent existing shader. @param InOCIOShaderMapHash - The hash value of the shadermap which will reference this shader @param CurrentJob - Compile job that was enqueued by BeginCompileShader. @param InDebugDescription - Description of the shader job (type, permutation ID, etc.) @return The constructed FShader instance for the completed job
- L162 _public function_ `bool ShouldCache(EShaderPlatform InPlatform, const FOpenColorIOTransformResource* InColorTransform) const` — Checks if the shader type should be cached for a particular platform and color transform. @param Platform - The platform to check. @param InColorTransform - The color transform to check. @return True if this shader type should be cached.
- L174 _protected prototype_ `void SetupCompileEnvironment(EShaderPlatform InPlatform, const FOpenColorIOTransformResource* InColorTransform, FShaderCompilerEnvironment& OutEnvironment) const;` — Sets up the environment used to compile an instance of this shader type. @param InPlatform - Platform to compile for. @param OutEnvironment - The shader compile environment that the function modifies.

#### struct `FOpenColorIOShaderType::FParameters`  
`struct FParameters : public FShaderType::FParameters`  
_L49-57_
- inherits: `FShaderType::FParameters`
- L51 _public member_ `TSharedRef<const FShaderParametersMetadata> ShaderParamMetadata;`
- L53 _public function_ `FParameters(const TSharedRef<const FShaderParametersMetadata>& InShaderParamMetadata) : ShaderParamMetadata(InShaderParamMetadata)`

#### struct `FOpenColorIOShaderType::CompiledShaderInitializerType`  
`struct CompiledShaderInitializerType : FShaderCompiledShaderInitializerType`  
_L59-74_
- inherits: `FShaderCompiledShaderInitializerType`
- L61 _public member_ `const FString DebugDescription;`
- L63 _public function_ `CompiledShaderInitializerType( const FShaderType* InType, const FParameters* InParameters, int32 InPermutationId, const FShaderCompilerOutput& CompilerOutput, uint64 InOCIOShaderMapHash, const FString& InDebugDescription ) : FShaderCompiledShaderInitializerType(InType, InParameters, InPermutationId, CompilerOutput, InOCIOShaderMapHash, nullptr, nullptr) , DebugDescription(InDebugDescription)`

#### Free symbols / members of external scopes

- L15 _macro_ `#define IMPLEMENT_OCIO_SHADER_TYPE(TemplatePrefix,ShaderClass,SourceFilename,FunctionName,Frequency) \` — A macro to implement OpenColorIO Color Space Transform shaders.
- L31 _prototype_ `extern void UpdateOpenColorIOShaderCompilingStats(const FOpenColorIOTransformResource* InShader);` — Called for every OpenColorIO shader to update the appropriate stats.

### `Plugins/Compositing/OpenColorIO/Source/OpenColorIO/Public/OpenColorIOShared.h` (Public)


#### enum `EOpenColorIOWorkingColorSpaceTransform`  
`enum class EOpenColorIOWorkingColorSpaceTransform : uint8`  
_L22-27_
- desc: Enum used to indicate whether the working color space should be used as a source or destination.
- L24 _public enumerator_ `None = 0`
- L25 _public enumerator_ `Source = 1`
- L26 _public enumerator_ `Destination = 2`

#### class `FOpenColorIOCompilationOutput`  
`class FOpenColorIOCompilationOutput`  
_L36-42_
- desc: Stores outputs from the color transform compile that need to be saved.
- L40 _public function_ `FOpenColorIOCompilationOutput()`

#### class `FOpenColorIOShaderMapId`  
`class FOpenColorIOShaderMapId`  
_L45-111_
- desc: Contains all the information needed to uniquely identify a FOpenColorIOShaderMapID.
- L66 _public function_ `FOpenColorIOShaderMapId() : FeatureLevel(ERHIFeatureLevel::SM5)`
- L70 _public prototype_ `~FOpenColorIOShaderMapId() = default;`
- L73 _public prototype_ `void SetShaderDependencies(const TArray<FShaderType*>& InShaderTypes, EShaderPlatform InShaderPlatform);`
- L83 _public function_ `SIZE_T GetSizeBytes() const`
- L89 _public prototype_ `uint64 GetOpenColorIOHash() const;` — Hashes the color transform-specific part of this shader map Id.
- L97 _public prototype_ `bool operator==(const FOpenColorIOShaderMapId& InReferenceSet) const;` — Tests this set against another for equality, disregarding override settings. @param InReferenceSet	The set to compare against @return					true if the sets are equal
- L99 _public function_ `bool operator!=(const FOpenColorIOShaderMapId& InReferenceSet) const`
- L106 _public prototype_ `void AppendKeyString(FString& OutKeyString) const;` — Appends string representations of this Id to a key string.
- L110 _public prototype_ `bool ContainsShaderType(const FShaderType* ShaderType) const;` — Returns true if the requested shader type is a dependency of this shader map Id.

#### class `FOpenColorIOShaderMapContent`  
`class FOpenColorIOShaderMapContent : public FShaderMapContent`  
_L113-129_
- inherits: `FShaderMapContent`
- L115 _private typedef_ `using Super = FShaderMapContent;`
- L119 _private function_ `explicit FOpenColorIOShaderMapContent(EShaderPlatform InPlatform) : Super(InPlatform)`

#### class `FOpenColorIOShaderMap`  
`class FOpenColorIOShaderMap : public TShaderMap<FOpenColorIOShaderMapContent, FShaderMapPointerTable>, public FDeferredCleanupInterface`  
_L135-302_
- inherits: `TShaderMap<FOpenColorIOShaderMapContent,FShaderMapPointerTable>,FDeferredCleanupInterface`
- desc: The shaders required to apply an OCIO color transform.
- L138 _public typedef_ `using Super = TShaderMap<FOpenColorIOShaderMapContent, FShaderMapPointerTable>;`
- L146 _public prototype_ `static FOpenColorIOShaderMap* FindId(const FOpenColorIOShaderMapId& InShaderMapId, EShaderPlatform InPlatform);` — Finds the shader map for a color transform. @param InShaderMapId - Id to find @param Platform - The platform to lookup for @return nullptr if no cached shader map was found.
- L149 _public function_ `template<typename ShaderType> TShaderRef<ShaderType> GetShader() const` — ShaderMap interface
- L157 _public prototype_ `static void LoadFromDerivedDataCache(const FOpenColorIOTransformResource* InColorTransform, const FOpenColorIOShaderMapId& InShaderMapId, EShaderPlatform InPlatform, TRefCountPtr<FOpenColorIOShaderMap>& InOutShaderMap);` — Attempts to load the shader map for the given color transform from the Derived Data Cache. If InOutShaderMap is valid, attempts to load the individual missing shaders instead.
- L160 _public prototype_ `FOpenColorIOShaderMap();`
- L163 _public prototype_ `~FOpenColorIOShaderMap();` — Destructor.
- L172 _public prototype_ `void Compile( FOpenColorIOTransformResource* InColorTransform, const FOpenColorIOShaderMapId& InShaderMapId, TRefCountPtr<FSharedShaderCompilerEnvironment> InCompilationEnvironment, const FOpenColorIOCompilationOutput& InOpenColorIOCompilationOutput, EShaderPlatform InPlatform, bool bSynchronousCompile, bool bApplyCompletedShaderMapForRendering );` — Compiles the shaders for a color transform and caches them in this shader map. @param InColorTransform - The color transform to compile shaders for. @param InShaderMapId - the set of static parameters to compile for @param InPlatform - The platform to compile to
- L183 _public prototype_ `bool ProcessCompilationResults(const TArray<TRefCountPtr<class FShaderCommonCompileJob>>& InCompilationResults, int32& InOutResultIndex, float& InOutTimeBudget);` — Sorts the incoming compiled jobs into the appropriate OCIO shader maps, and finalizes this shader map so that it can be used for rendering.
- L191 _public prototype_ `bool IsComplete(const FOpenColorIOTransformResource* InColorTransform, bool bSilent);` — Checks whether the shader map is missing any shader types necessary for the given color transform. @param InColorTransform - The OpenColorIO ColorTransform which is checked. @return True if the shader map has all of the shader types necessary.
- L200 _public prototype_ `bool TryToAddToExistingCompilationTask(FOpenColorIOTransformResource* InColorTransform);` — Checks to see if the shader map is already being compiled for another color transform, and if so adds the specified color transform to the list to be applied to once the compile finishes. @param InColorTransform - The OpenColorIO ColorTransform we also wish to apply the compiled shader map to. @return True if the shader map was being compiled and we added ColorTransform to the list to be applied.
- L204 _public prototype_ `void GetShaderList(TMap<FShaderId, TShaderRef<FShader>>& OutShaders) const;` — Builds a list of the shaders in a shader map.
- L205 _public prototype_ `virtual void GetShaderList(TMap<FHashedName, TShaderRef<FShader>>& OutShaders) const override;`
- L206 _public prototype_ `virtual void GetShaderPipelineList(TArray<FShaderPipelineRef>& OutShaderPipelines) const override;`
- L209 _public prototype_ `void Register(EShaderPlatform InShaderPlatform);` — Registers a OpenColorIO shader map in the global map so it can be used by OpenColorIO ColorTransform.
- L211 _public prototype_ `void AddRef();` — Reference counting.
- L212 _public prototype_ `void Release();`
- L216 _public prototype_ `static void RemovePendingColorTransform(FOpenColorIOTransformResource* InColorTransform);` — Removes a ColorTransform from OpenColorIOShaderMapsBeingCompiled.
- L220 _public prototype_ `bool Serialize(FArchive& Ar);` — Serializes the shader map.
- L224 _public prototype_ `void SaveToDerivedDataCache();` — Saves this shader map to the derived data cache.
- L228 _public function_ `const FOpenColorIOShaderMapId& GetShaderMapId() const` — Accessors.
- L229 _public function_ `EShaderPlatform GetShaderPlatform() const`
- L230 _public function_ `const FMemoryImageString& GetFriendlyName() const`
- L231 _public function_ `uint32 GetCompilingId() const`
- L232 _public function_ `bool IsCompilationFinalized() const`
- L233 _public function_ `bool CompiledSuccessfully() const`
- L235 _public function_ `bool IsValid() const`
- L240 _public function_ `int32 GetNumRefs() const`
- L241 _public function_ `uint32 GetCompilingId()`
- L244 _public function_ `static TMap<TRefCountPtr<FOpenColorIOShaderMap>, TArray<FOpenColorIOTransformResource*> > &GetInFlightShaderMaps()`
- L246 _public function_ `void SetCompiledSuccessfully(bool bSuccess)`
- L255 _private member_ `static TMap<FOpenColorIOShaderMapId, FOpenColorIOShaderMap*> GIdToOpenColorIOShaderMap[SP_NumPlatforms];` — A global map from a ColorTransform's ID and static switch set to any shader map cached for that color transform. Note: this does not necessarily contain all color transform shader maps in memory.  Shader maps with the same key can evict each other. No ref counting needed as these are removed on destruction of the shader map.
- L261 _private member_ `static TArray<FOpenColorIOShaderMap*> AllOpenColorIOShaderMaps;` — All color transform shader maps in memory. No ref counting needed as these are removed on destruction of the shader map.
- L265 _private member_ `static uint32 NextCompilingId;` — Next value for CompilingId.
- L268 _private member_ `static TMap<TRefCountPtr<FOpenColorIOShaderMap>, TArray<FOpenColorIOTransformResource*> > OpenColorIOShaderMapsBeingCompiled;` — Tracks resources and their shader maps that need to be compiled but whose compilation is being deferred.
- L272 _private member_ `uint32 CompilingId;` — Uniquely identifies this shader map during compilation, needed for deferred compilation where shaders from multiple shader maps are compiled together.
- L274 _private member_ `mutable int32 NumRefs;`
- L277 _private member_ `bool bDeletedThroughDeferredCleanup;` — Used to catch errors where the shader map is deleted directly.
- L280 _private member_ `uint32 bRegistered : 1;` — Indicates whether this shader map has been registered in GIdToOpenColorsIOShaderMap
- L286 _private member_ `uint32 bCompilationFinalized : 1;` — Indicates whether this shader map has had ProcessCompilationResults called after Compile. The shader map must not be used on the rendering thread unless bCompilationFinalized is true.
- L288 _private member_ `uint32 bCompiledSuccessfully : 1;`
- L291 _private member_ `uint32 bIsPersistent : 1;` — Indicates whether the shader map should be stored in the shader cache.
- L293 _private member_ `uint32 bHasFrozenContent : 1;`
- L296 _private prototype_ `FShader* ProcessCompilationResultsForSingleJob(const TRefCountPtr<class FShaderCommonCompileJob>& SingleJob, uint64 InShaderMapHash);`
- L299 _private prototype_ `bool IsOpenColorIOShaderComplete(const FOpenColorIOTransformResource* InColorTransform, const FOpenColorIOShaderType* InShaderType, bool bSilent);`

#### class `FOpenColorIOTransformResource`  
`class FOpenColorIOTransformResource`  
_L308-580_
- desc: FOpenColorIOTransformResource represents a OpenColorIO color transform to the shader compilation process
- L315 _public prototype_ `FOpenColorIOTransformResource();` — Minimal initialization constructor.
- L320 _public prototype_ `virtual ~FOpenColorIOTransformResource();` — Destructor
- L326 _public prototype_ `bool CacheShaders(EShaderPlatform InPlatform, const ITargetPlatform* TargetPlatform, bool bApplyCompletedShaderMapForRendering, bool bSynchronous);` — Caches the shaders for this color transform with no static parameters on the given platform. This is used by UOpenColorIOColorTransform
- L327 _public prototype_ `bool CacheShaders(const FOpenColorIOShaderMapId& InShaderMapId, EShaderPlatform InPlatform, bool bApplyCompletedShaderMapForRendering, bool bSynchronous);`
- L330 _public prototype_ `TSharedPtr<const FShaderParametersMetadata, ESPMode::ThreadSafe> GetShaderParamMetadata() const;` — Returns the shader parameter metadata for the generated shader (built-in FOpenColorIOPixelShaderParameters, followed by dynamic textures & samplers).
- L341 _public prototype_ `virtual bool ShouldCache(EShaderPlatform InPlatform, const FShaderType* InShaderType) const;` — Should the shader for this color transform with the given platform, shader type and vertex factory type combination be compiled @param InPlatform		The platform currently being compiled for @param InShaderType		Which shader is being compiled @return true if the shader should be compiled
- L343 _public prototype_ `void SerializeShaderMap(FArchive& Ar);`
- L346 _public prototype_ `void ReleaseShaderMap();` — Releases this color transform's shader map.  Must only be called on ColorTransforms not exposed to the rendering thread!
- L349 _public prototype_ `void DiscardShaderMap();` — Discards loaded shader maps if the application can't render
- L351 _public prototype_ `void GetDependentShaderTypes(EShaderPlatform InPlatform, TArray<FShaderType*>& OutShaderTypes) const;`
- L352 _public prototype_ `virtual void GetShaderMapId(EShaderPlatform InPlatform, const ITargetPlatform* TargetPlatform, FOpenColorIOShaderMapId& OutId) const;`
- L354 _public prototype_ `void Invalidate();`
- L359 _public function_ `virtual bool IsPersistent() const` — Should shaders compiled for this color transform be saved to disk?
- L365 _public prototype_ `void CancelCompilation();` — Cancels all outstanding compilation jobs
- L370 _public prototype_ `void FinishCompilation();` — Blocks until compilation has completed. Returns immediately if a compilation is not outstanding.
- L378 _public prototype_ `bool IsCompilationFinished() const;` — Checks if the compilation for this shader is finished @return returns true if compilation is complete false otherwise
- L381 _public function_ `const TArray<FString>& GetCompileErrors() const` — Accessors.
- L382 _public function_ `void SetCompileErrors(const TArray<FString>& InCompileErrors)`
- L384 _public function_ `ERHIFeatureLevel::Type GetFeatureLevel() const`
- L386 _public function_ `FOpenColorIOShaderMap* GetGameThreadShaderMap() const`
- L393 _public function_ `FName GetOwnerFName() const` — Returns owner name for tracking
- L399 _public function_ `void SetGameThreadShaderMap(FOpenColorIOShaderMap* InShaderMap)` — Note: SetRenderingThreadShaderMap must also be called with the same value, but from the rendering thread.
- L410 _public prototype_ `void SetRenderingThreadShaderMap(FOpenColorIOShaderMap* InShaderMap);` — Note: SetGameThreadShaderMap must also be called with the same value, but from the game thread.
- L413 _public function_ `void AddCompileId(uint32 InIdentifier)`
- L419 _public function_ `void SetInlineShaderMap(FOpenColorIOShaderMap* InShaderMap)`
- L433 _public prototype_ `void RemoveOutstandingCompileId(const int32 InOldOutstandingCompileShaderMapId);`
- L441 _public function_ `bool GetColorTransformHLSLSource(FString& OutSource)` — Get OCIO generated source code for the shader @param OutSource - generated source code @return - true on Success
- L447 _public function_ `const FString& GetFriendlyName() const`
- L450 _public prototype_ `void SetupResource( ERHIFeatureLevel::Type InFeatureLevel, const FString& InShaderCodeHash, const FString& InShadercode, const FString& InRawConfigHash, const FString& InFriendlyName, const FName& InAssetPath, FShaderParametersMetadata* InShaderParameterMetadata );` — Note: Takes ownership of the shader parameter metadata.
- L460 _public function_ `void SetCompileErrors(TArray<FString> &InErrors)`
- L465 _public member_ `FString ShaderCode;`
- L468 _public function_ `template <typename ShaderType> TShaderRef<ShaderType> GetShader() const`
- L480 _public function_ `template <typename ShaderType> TShaderRef<ShaderType> GetShaderGameThread() const`
- L491 _public prototype_ `bool IsSame(const FOpenColorIOShaderMapId& InId) const;`
- L498 _protected prototype_ `void GetShaderMapIDsWithUnfinishedCompilation(TArray<int32>& OutShaderMapIds);` — Fills the passed array with IDs of shader maps unfinished compilation jobs.
- L501 _protected function_ `void SetFeatureLevel(ERHIFeatureLevel::Type InFeatureLevel)`
- L508 _private member_ `TArray<FString> CompileErrors;`
- L516 _private member_ `TRefCountPtr<FOpenColorIOShaderMap> GameThreadShaderMap;` — Game thread tracked shader map, which is ref counted and manages shader map lifetime. The shader map uses deferred deletion so that the rendering thread has a chance to process a release command when the shader map is no longer referenced. Code that sets this is responsible for updating RenderingThreadShaderMap in a thread safe way. During an async compile, this will be NULL and will not contain the actual shader map until compilation is complete.
- L521 _private member_ `TSharedPtr<const FShaderParametersMetadata, ESPMode::ThreadSafe> ShaderParametersMetadata;` — The shader parameter metadata for the generated shader (built-in FOpenColorIOPixelShaderParameters, followed by dynamic textures & samplers).
- L527 _private member_ `FOpenColorIOShaderMap* RenderingThreadShaderMap;` — Shader map for this FOpenColorIOTransformResource which is accessible by the rendering thread. This must be updated along with GameThreadShaderMap, but on the rendering thread.
- L533 _private member_ `FString ShaderCodeAndConfigHash;` — Hash computed from shader code and raw config hashes. If either raw config or shader code is changed new data will be generated and saved in DDC.
- L540 _private member_ `TArray<int32, TInlineAllocator<1> > OutstandingCompileShaderMapIds;` — Contains the compiling id of this shader map when it is being compiled asynchronously. This can be used to access the shader map during async compiling, since GameThreadShaderMap will not have been set yet.
- L544 _private member_ `ERHIFeatureLevel::Type FeatureLevel;` — Feature level that this color transform is representing.
- L551 _private member_ `uint32 bContainsInlineShaders : 1;`
- L552 _private member_ `uint32 bLoadedCookedShaderMapId : 1;`
- L553 _private member_ `FOpenColorIOShaderMapId CookedShaderMapId;`
- L559 _private prototype_ `bool BeginCompileShaderMap( const FOpenColorIOShaderMapId& InShaderMapId, EShaderPlatform InPlatform, TRefCountPtr<class FOpenColorIOShaderMap>& OutShaderMap, bool bApplyCompletedShaderMapForRendering, bool bSynchronous = false);` — Compiles this color transform for InPlatform, storing the result in OutShaderMap if the compile was synchronous
- L567 _private prototype_ `void SetupShaderCompilationEnvironment( EShaderPlatform InPlatform, FShaderCompilerEnvironment& OutEnvironment ) const;` — Populates OutEnvironment with defines needed to compile shaders for this color transform.
- L573 _private member_ `FString FriendlyName;`
- L576 _private member_ `FName AssetPath;` — Asset using this resource

#### Free symbols / members of external scopes

- L78 _function_ `friend uint32 GetTypeHash(const FOpenColorIOShaderMapId& Ref)`
