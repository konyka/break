# Plugins / AndroidCameraFactory

- module root: `Plugins/Media/AndroidCamera/Source/AndroidCameraFactory`
- headers: 2; symbols: 5
- symbol kinds: class=1, delegate=1, member=1, prototype=2
- DynamicallyLoadedModuleNames: AndroidCamera, Media
- PrivateDependencyModuleNames: MediaAssets
- PrivateIncludePathModuleNames: AndroidCamera, Media
- PublicDependencyModuleNames: Core, CoreUObject

### `Plugins/Media/AndroidCamera/Source/AndroidCameraFactory/Private/AndroidCameraFactoryPrivate.h` (Private)


#### Free symbols / members of external scopes

- L9 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogAndroidCameraFactory, Log, All);` — Log category for the AndroidCameraFactory module.
- L9 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogAndroidCameraFactory, Log, All);` — Log category for the AndroidCameraFactory module.

### `Plugins/Media/AndroidCamera/Source/AndroidCameraFactory/Public/AndroidCameraSettings.h` (Public)


#### class `UAndroidCameraSettings`  
`class UAndroidCameraSettings : public UObject`  
_L16-46_
- reflection: `UCLASS(config=Engine)`
- inherits: `UObject`
- desc: Settings for the ImgMedia module.
- L40 _public member_ `bool CacheableVideoSampleBuffers;` — `UPROPERTY(config, EditAnywhere, Category="Video")` — Whether video samples should be cacheable (default = off). This setting only affects applications that are not compiled against the Engine. In such applications, the video samples transfer their contents via a frame buffer. By default, the same frame buffer is reused for every sample to avoid buffer copies. Every time a new sample is generated, the previously generated samples are invalidated. When enabling this option, video frame buffers are copied into instead of referenced in video samples. This may be useful for applications that require access to individual frames, but it may dramatically decrease performance. When compiling against the Engine, this setting has no effect as the frame data is transferred via separate texture resource objects.
- L45 _public prototype_ `UAndroidCameraSettings();` — Default constructor.
