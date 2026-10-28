# Plugins / AndroidMediaFactory

- module root: `Plugins/Media/AndroidMedia/Source/AndroidMediaFactory`
- headers: 2; symbols: 6
- symbol kinds: class=1, delegate=1, macro=1, member=1, prototype=2
- DynamicallyLoadedModuleNames: AndroidMedia, Media
- PrivateDependencyModuleNames: MediaAssets
- PrivateIncludePathModuleNames: AndroidMedia, Media
- PublicDependencyModuleNames: Core, CoreUObject

### `Plugins/Media/AndroidMedia/Source/AndroidMediaFactory/Private/AndroidMediaFactoryPrivate.h` (Private)


#### Free symbols / members of external scopes

- L9 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogAndroidMediaFactory, Log, All);` — Log category for the AndroidMediaFactory module.
- L9 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogAndroidMediaFactory, Log, All);` — Log category for the AndroidMediaFactory module.

### `Plugins/Media/AndroidMedia/Source/AndroidMediaFactory/Public/AndroidMediaSettings.h` (Public)


#### class `UAndroidMediaSettings`  
`class UAndroidMediaSettings : public UObject`  
_L16-46_
- reflection: `UCLASS(MinimalAPI, config=Engine)`
- inherits: `UObject`
- desc: Settings for the ImgMedia module.
- L40 _public member_ `bool CacheableVideoSampleBuffers;` — `UPROPERTY(config, EditAnywhere, Category="Video")` — Whether video samples should be cacheable (default = off). This setting only affects applications that are not compiled against the Engine. In such applications, the video samples transfer their contents via a frame buffer. By default, the same frame buffer is reused for every sample to avoid buffer copies. Every time a new sample is generated, the previously generated samples are invalidated. When enabling this option, video frame buffers are copied into instead of referenced in video samples. This may be useful for applications that require access to individual frames, but it may dramatically decrease performance. When compiling against the Engine, this setting has no effect as the frame data is transferred via separate texture resource objects.
- L45 _public prototype_ `UAndroidMediaSettings();` — Default constructor.

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API ANDROIDMEDIAFACTORY_API`
