# Plugins / WmfMediaFactory

- module root: `Plugins/Media/WmfMedia/Source/WmfMediaFactory`
- headers: 2; symbols: 11
- symbol kinds: class=1, delegate=1, macro=1, member=5, prototype=3
- DynamicallyLoadedModuleNames: Media, Settings, WmfMedia
- PrivateDependencyModuleNames: MediaAssets
- PrivateIncludePathModuleNames: Media, Settings, WmfMedia
- PublicDependencyModuleNames: Core, CoreUObject

### `Plugins/Media/WmfMedia/Source/WmfMediaFactory/Private/WmfMediaFactoryPrivate.h` (Private)


#### Free symbols / members of external scopes

- L8 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogWmfMediaFactory, Log, All);` — Log category for the WmfMediaFactory module.
- L8 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogWmfMediaFactory, Log, All);` — Log category for the WmfMediaFactory module.

### `Plugins/Media/WmfMedia/Source/WmfMediaFactory/Public/WmfMediaSettings.h` (Public)


#### class `UWmfMediaSettings`  
`class UWmfMediaSettings : public UObject`  
_L15-65_
- reflection: `UCLASS(MinimalAPI, config=Engine, defaultconfig)`
- inherits: `UObject`
- desc: Settings for the WmfMedia plug-in.
- L23 _public prototype_ `UWmfMediaSettings();` — Default constructor.
- L36 _public member_ `bool AllowNonStandardCodecs;` — `UPROPERTY(config, EditAnywhere, Category=Media)` — Whether to allow the loading of media that uses non-standard codecs (default = off). By default, the player will attempt to detect audio and video codecs that are not supported by the operating system out of the box, but may require the user to install additional codec packs. Enable this option to skip this check and allow the usage of non-standard codecs.
- L48 _public member_ `bool LowLatency;` — `UPROPERTY(config, EditAnywhere, Category=Media)` — Enable low latency processing in the Windows media pipeline (default = off). When this setting is enabled, the media data is generated with the lowest possible delay. This might be desirable for certain real-time applications, but it can negatively affect audio and video quality. @note This setting is only supported on Windows 8 or newer
- L52 _public member_ `bool NativeAudioOut;` — `UPROPERTY(config, EditAnywhere, Category=Debug)` — Play audio tracks via the operating system's native sound mixer (default = off).
- L56 _public member_ `bool HardwareAcceleratedVideoDecoding;` — `UPROPERTY(config, EditAnywhere, Category=Media, meta = (DisplayName = "Hardware Accelerated Video Decoding (Experimental)"))` — Use hardware accelerated video acceleration (GPU) when possible otherwise fallback to software implementation (CPU), Windows and DX11 only.
- L59 _public member_ `bool bAreHardwareAcceleratedCodecRegistered;` — Set when at least one registered codec is hardware accelerated.
- L63 _public prototype_ `void EnableHardwareAcceleratedCodecRegistered();`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API WMFMEDIAFACTORY_API`
