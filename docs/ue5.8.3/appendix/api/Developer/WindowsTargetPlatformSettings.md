# Developer / WindowsTargetPlatformSettings

- module root: `Source/Developer/Windows/WindowsTargetPlatformSettings`
- headers: 3; symbols: 77
- symbol kinds: class=3, enum=2, enumerator=12, function=19, macro=3, member=33, prototype=4, typedef=1
- PrivateDependencyModuleNames: AudioPlatformConfiguration, CookedEditor, Core, CoreUObject, DesktopPlatform, Engine, RHI, TargetPlatform
- PrivateIncludePathModuleNames: Settings, TextureCompressor
- PublicIncludePathModuleNames: AudioPlatformConfiguration, Engine

### `Source/Developer/Windows/WindowsTargetPlatformSettings/Classes/WindowsTargetSettings.h` (Public)


#### enum `ECompilerVersion`  
`enum class ECompilerVersion : uint8`  
_L18-28_
- reflection: `UENUM()`
- L20 _public enumerator_ `Default = 0`
- L21 _public enumerator_ `VisualStudio2015 = 1 UMETA(DisplayName = "Visual Studio 2015 (deprecated)")`
- L22 _public enumerator_ `VisualStudio2017 = 2 UMETA(DisplayName = "Visual Studio 2017 (deprecated)")`
- L23 _public enumerator_ `VisualStudio2019 = 3 UMETA(DisplayName = "Visual Studio 2019 (deprecated)")`
- L24 _public enumerator_ `VisualStudio2022 = 4 UMETA(DisplayName = "Visual Studio 2022")`
- L25 _public enumerator_ `VisualStudio2026 = 5 UMETA(DisplayName = "Visual Studio 2026")`
- L26 _public enumerator_ `Clang = 6 UMETA(DisplayName = "Clang")`
- L27 _public enumerator_ `Intel = 7 UMETA(DisplayName = "Intel oneAPI")`

#### enum `EDefaultGraphicsRHI`  
`enum class EDefaultGraphicsRHI : uint8`  
_L31-37_
- reflection: `UENUM()`
- L33 _public enumerator_ `DefaultGraphicsRHI_Default = 0 UMETA(DisplayName = "Default")`
- L34 _public enumerator_ `DefaultGraphicsRHI_DX11 = 1 UMETA(DisplayName = "DirectX 11")`
- L35 _public enumerator_ `DefaultGraphicsRHI_DX12 = 2 UMETA(DisplayName = "DirectX 12")`
- L36 _public enumerator_ `DefaultGraphicsRHI_Vulkan = 3 UMETA(DisplayName = "Vulkan")`

#### class `UWindowsTargetSettings`  
`class UWindowsTargetSettings : public UObject`  
_L45-172_
- reflection: `UCLASS(MinimalAPI, config=Engine, defaultconfig)`
- inherits: `UObject`
- desc: Implements the settings for the Windows target platform. The first instance of this class is initialized in WindowsTargetPlatform, really early during the startup sequence before the CDO has been constructed, so its config settings are read manually from there.
- L51 _public prototype_ `virtual void PostInitProperties() override;`
- L55 _public member_ `EDefaultGraphicsRHI DefaultGraphicsRHI;` — `UPROPERTY(EditAnywhere, config, Category="Targeted RHIs", Meta = (DisplayName = "Default RHI", ConfigRestartRequired = true))` — Select which RHI to use. Make sure its also selected as a Targeted RHI. Requires Editor restart.
- L58 _public member_ `TArray<FString> TargetedRHIs_DEPRECATED;` — `UPROPERTY(config, meta = (DeprecatedProperty, DeprecationMessage = "Use one of the RHI specific lists."))`
- L61 _public member_ `TArray<FString> D3D12TargetedShaderFormats;` — `UPROPERTY(EditAnywhere, config, Category = "Rendering", Meta = (ConfigRestartRequired = true))`
- L64 _public member_ `TArray<FString> D3D11TargetedShaderFormats;` — `UPROPERTY(EditAnywhere, config, Category = "Rendering", Meta = (ConfigRestartRequired = true))`
- L67 _public member_ `TArray<FString> VulkanTargetedShaderFormats;` — `UPROPERTY(EditAnywhere, config, Category = "Rendering", Meta = (ConfigRestartRequired = true))`
- L71 _public member_ `bool bGenerateNaniteFallbackMeshes = true;` — `UPROPERTY(config, EditAnywhere, Category = "Renderer", meta = (DisplayName = "Generate Nanite Fallback Meshes", ConfigRestartRequired = true))` — Whether to include Nanite Fallback Meshes in cooked builds for Windows. Can be overriden for specific assets in Static Mesh Editor.
- L75 _public member_ `bool bEnableRayTracing_DEPRECATED;` — `UPROPERTY(config, meta = (DeprecatedProperty))` — Deprecated use RayTracingMode instead.
- L79 _public member_ `ETargetSettingsRayTracingRuntimeMode RayTracingMode;` — `UPROPERTY(config, EditAnywhere, Category = "Renderer", meta = (DisplayName = "Hardware Ray Tracing Mode"))` — Controls the level of ray tracing support for Windows. r.RayTracing cvar also needs to be enabled.
- L83 _public member_ `ECompilerVersion Compiler;` — `UPROPERTY(EditAnywhere, config, Category = "Toolchain", Meta = (DisplayName = "Compiler Version"))` — The compiler version to use for this project. May be different to the chosen IDE.
- L87 _public member_ `int32 AudioSampleRate;` — `UPROPERTY(config, EditAnywhere, Category = "Audio", Meta = (DisplayName = "Audio Mixer Sample Rate"))` — Sample rate to run the audio mixer with.
- L91 _public member_ `int32 AudioCallbackBufferFrameSize;` — `UPROPERTY(config, EditAnywhere, Category = "Audio", meta = (ClampMin = "64", ClampMax = "4096", DisplayName = "Callback Buffer Size", ConfigRestartRequired = true))` — The amount of audio to compute each callback block. Lower values decrease latency but may increase CPU cost.
- L95 _public member_ `int32 AudioNumBuffersToEnqueue;` — `UPROPERTY(config, EditAnywhere, Category = "Audio", meta = (ClampMin = "1", UIMin = "1", DisplayName = "Number of Buffers To Enqueue", ConfigRestartRequired = true))` — The number of buffers to keep enqueued. More buffers increases latency, but can compensate for variable compute availability in audio callbacks on some platforms.
- L99 _public member_ `int32 AudioMaxChannels;` — `UPROPERTY(config, EditAnywhere, Category = "Audio", meta = (ClampMin = "0", UIMin = "0", DisplayName = "Max Channels"))` — The max number of channels (voices) to limit for this platform. The max channels used will be the minimum of this value and the global audio quality settings. A value of 0 will not apply a platform channel count max.
- L103 _public member_ `int32 AudioNumSourceWorkers;` — `UPROPERTY(config, EditAnywhere, Category = "Audio", meta = (ClampMin = "0", UIMin = "0", DisplayName = "Number of Source Workers"))` — The number of workers to use to compute source audio. Will only use up to the max number of sources. Will evenly divide sources to each source worker.
- L107 _public member_ `FString SpatializationPlugin;` — `UPROPERTY(config, EditAnywhere, Category = "Audio")` — Which of the currently enabled spatialization plugins to use.
- L111 _public member_ `FString SourceDataOverridePlugin;` — `UPROPERTY(config, EditAnywhere, Category = "Audio")` — Which of the currently enabled source data override plugins to use.
- L115 _public member_ `FString ReverbPlugin;` — `UPROPERTY(config, EditAnywhere, Category = "Audio")` — Which of the currently enabled reverb plugins to use.
- L119 _public member_ `FString OcclusionPlugin;` — `UPROPERTY(config, EditAnywhere, Category = "Audio")` — Which of the currently enabled occlusion plugins to use.
- L125 _public member_ `FPlatformRuntimeAudioCompressionOverrides CompressionOverrides;` — `UPROPERTY(GlobalConfig, EditAnywhere, Category = "Audio")` — Various overrides for how this platform should handle compression and decompression
- L129 _public member_ `int32 CacheSizeKB;` — `UPROPERTY(GlobalConfig, EditAnywhere, Category = "Audio|CookOverrides|Stream Caching", meta = (DisplayName = "Max Cache Size (KB)"))` — This determines the max amount of memory that should be used for the cache at any given time. If set low (<= 8 MB), it lowers the size of individual chunks of audio during cook.
- L133 _public member_ `int32 MaxChunkSizeOverrideKB;` — `UPROPERTY(GlobalConfig, EditAnywhere, Category = "Audio|CookOverrides|Stream Caching", meta = (DisplayName = "Max Chunk Size Override (KB)"))` — This overrides the default max chunk size used when chunking audio for stream caching (ignored if < 0)
- L136 _public member_ `bool bResampleForDevice;` — `UPROPERTY(GlobalConfig, EditAnywhere, Category = "Audio|CookOverrides")`
- L141 _public member_ `float MaxSampleRate;` — `UPROPERTY(GlobalConfig, EditAnywhere, Category = "Audio|CookOverrides|ResamplingQuality", meta = (DisplayName = "Max"))`
- L144 _public member_ `float HighSampleRate;` — `UPROPERTY(GlobalConfig, EditAnywhere, Category = "Audio|CookOverrides|ResamplingQuality", meta = (DisplayName = "High"))`
- L147 _public member_ `float MedSampleRate;` — `UPROPERTY(GlobalConfig, EditAnywhere, Category = "Audio|CookOverrides|ResamplingQuality", meta = (DisplayName = "Medium"))`
- L150 _public member_ `float LowSampleRate;` — `UPROPERTY(GlobalConfig, EditAnywhere, Category = "Audio|CookOverrides|ResamplingQuality", meta = (DisplayName = "Low"))`
- L153 _public member_ `float MinSampleRate;` — `UPROPERTY(GlobalConfig, EditAnywhere, Category = "Audio|CookOverrides|ResamplingQuality", meta = (DisplayName = "Min"))`
- L157 _public member_ `float CompressionQualityModifier;` — `UPROPERTY(GlobalConfig, EditAnywhere, Category = "Audio|CookOverrides")` — Scales all compression qualities when cooking to this platform. For example, 0.5 will halve all compression qualities, and 1.0 will leave them unchanged.
- L161 _public member_ `float AutoStreamingThreshold;` — `UPROPERTY(GlobalConfig)` — When set to anything beyond 0, this will ensure any SoundWaves longer than this value, in seconds, to stream directly off of the disk.
- L165 _public member_ `int32 SoundCueCookQualityIndex = INDEX_NONE;` — `UPROPERTY(GlobalConfig, EditAnywhere, Category = "Audio|CookOverrides", meta = (DisplayName = "Sound Cue Cook Quality"))` — Quality Level to COOK SoundCues at (if set, all other levels will be stripped by the cooker).
- L167 _public function_ `void virtual OverrideConfigSection(FString& InOutSectionName) override`

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API WINDOWSTARGETPLATFORMSETTINGS_API`

### `Source/Developer/Windows/WindowsTargetPlatformSettings/Public/GenericWindowsTargetPlatformSettings.h` (Public)


#### class `TGenericWindowsTargetPlatformSettings`  
`template<typename TProperties> class TGenericWindowsTargetPlatformSettings : public TTargetPlatformSettingsBase<TProperties>`  
_L24-311_
- inherits: `TTargetPlatformSettingsBase<TProperties>`
- L27 _public typedef_ `typedef TTargetPlatformSettingsBase<TProperties> TSuper;`
- L32 _public function_ `TGenericWindowsTargetPlatformSettings( )` — Default constructor.
- L64 _public function_ `virtual bool SupportsFeature( ETargetPlatformFeatures Feature ) const override`
- L110 _public function_ `virtual bool IsRunningPlatform() const override`
- L116 _public function_ `virtual void GetAllPossibleShaderFormats( TArray<FName>& OutFormats ) const override`
- L139 _public function_ `TArray<FName> GetAllTargetedShaderFormatsInternal(TConstArrayView<const TCHAR*> RelevantSettings) const`
- L180 _public function_ `virtual void GetAllTargetedShaderFormats( TArray<FName>& OutFormats ) const override`
- L196 _public function_ `virtual void GetRayTracingShaderFormats( TArray<FName>& OutFormats ) const override`
- L214 _public function_ `virtual void GetPossibleArchitectures(TArray<FString>& OutArchitectures) const override`
- L222 _public function_ `virtual FString GetHostArchitecture() const override`
- L229 _public function_ `virtual void GetReflectionCaptureFormats(TArray<FName>& OutFormats) const override`
- L239 _public function_ `virtual void GetShaderFormatModuleHints(TArray<FName>& OutModuleNames) const override`
- L246 _public function_ `virtual const class FStaticMeshLODSettings& GetStaticMeshLODSettings( ) const override`
- L252 _public function_ `virtual const UTextureLODSettings& GetTextureLODSettings() const override`
- L257 _public function_ `virtual void RegisterTextureLODSettings(const UTextureLODSettings* InTextureLODSettings) override`
- L264 _public function_ `virtual bool ShouldStripNaniteFallbackMeshes() const override`
- L272 _public function_ `virtual bool UsesDistanceFields() const override`
- L280 _public function_ `virtual bool UsesRayTracing() const override`
- L285 _public function_ `virtual ERayTracingRuntimeMode GetRayTracingMode() const override`
- L301 _private member_ `const UTextureLODSettings* TextureLODSettings;` — Holds the texture LOD settings.
- L304 _private member_ `FStaticMeshLODSettings StaticMeshLODSettings;` — Holds static mesh LOD settings.
- L307 _private member_ `bool bRequiresEncodedHDRReflectionCaptures;` — True if the project requires encoded HDR reflection captures

#### Free symbols / members of external scopes

- L16 _macro_ `#define LOCTEXT_NAMESPACE "TGenericWindowsTargetPlatformSettings"`
- L17 _macro_ `#define WIN_SECTION_TEXT TEXT("/Script/WindowsTargetPlatform.WindowsTargetSettings")`

### `Source/Developer/Windows/WindowsTargetPlatformSettings/Public/IWindowsTargetPlatformSettingsModule.h` (Public)


#### class `IWindowsTargetPlatformSettingsModule`  
`class IWindowsTargetPlatformSettingsModule : public ITargetPlatformSettingsModule`  
_L13-19_
- inherits: `ITargetPlatformSettingsModule`
- L16 _public prototype_ `virtual void GetPlatformSettingsMaps(TMap<FString, ITargetPlatformSettings*>& OutMap) = 0;`
- L17 _public prototype_ `virtual ITargetPlatformSettings* GetCookedEditorPlatformSettings() = 0;`
- L18 _public prototype_ `virtual ITargetPlatformSettings* GetCookedCookerPlatformSettings() = 0;`
