# Developer / AndroidDeviceDetection

- module root: `Source/Developer/Android/AndroidDeviceDetection`
- headers: 3; symbols: 38
- symbol kinds: class=2, member=26, prototype=9, struct=1
- DynamicallyLoadedModuleNames: TcpMessaging
- PrivateDependencyModuleNames: Core, DesktopPlatform, Engine, Json, JsonUtilities, PIEPreviewDeviceSpecification, Slate, SlateCore, Zen
- PrivateIncludePathModuleNames: TcpMessaging

### `Source/Developer/Android/AndroidDeviceDetection/Public/AndroidDeviceDetection.h` (Public)
_(no declarations extracted)_

### `Source/Developer/Android/AndroidDeviceDetection/Public/Interfaces/IAndroidDeviceDetection.h` (Public)


#### struct `FAndroidDeviceInfo`  
`struct FAndroidDeviceInfo`  
_L14-82_
- L16 _public member_ `FString DeviceId;`
- L18 _public member_ `FString AvdName;`
- L21 _public member_ `FString SerialNumber;` — Device serial number, used to route ADB commands to a specific device
- L24 _public member_ `FString Model;` — Device model name
- L27 _public member_ `FString DeviceName;` — Device name
- L30 _public member_ `FString HumanAndroidVersion;` — User-visible version of android installed (ro.build.version.release)
- L33 _public member_ `int32 SDKVersion = INDEX_NONE;` — Android SDK version supported by the device (ro.build.version.sdk - note: deprecated in 4 according to docs, but version 4 devices return an empty string when querying the 'replacement' SDK_INT)
- L35 _public member_ `FString Architecture;`
- L38 _public member_ `FString GLESExtensions;` — List of supported OpenGL extensions (retrieved via SurfaceFlinger)
- L41 _public member_ `int32 GLESVersion = INDEX_NONE;` — Supported GLES version (ro.opengles.version)
- L44 _public member_ `bool bAuthorizedDevice = true;` — Is the device authorized for USB communication?  If not, then none of the other properties besides the serial number will be valid
- L47 _public member_ `uint16 HostMessageBusPort = 0;` — TCP port number on our local host forwarded over adb to the device
- L50 _public member_ `int32 DeviceDPI = 0;` — Holds pixel per inch value.
- L53 _public member_ `float InsetsLeft;` — Holds the safe zones for the device
- L54 _public member_ `float InsetsTop;`
- L55 _public member_ `float InsetsRight;`
- L56 _public member_ `float InsetsBottom;`
- L59 _public member_ `int32 ResolutionX = 0;` — Holds the display resolution for the device
- L60 _public member_ `int32 ResolutionY = 0;`
- L63 _public member_ `FString OpenGLVersionString;` — Holds the reported OpenGLES version.
- L66 _public member_ `FString VulkanVersion;` — device's vulkan version, in major.minor.patch format.
- L69 _public member_ `FString GPUFamilyString;` — Holds the GPU family name.
- L72 _public member_ `FString DeviceBrand;` — Holds the name of the manufacturer
- L75 _public member_ `FString Hardware;` — device Hardware field. (or hardware.chipset for qcom)
- L78 _public member_ `uint32 TotalPhysicalKB = 0;` — device's total mem (as reported from /proc/meminfo)
- L81 _public member_ `FString BuildNumber;` — device BuildNumber field

#### class `IAndroidDeviceDetection`  
`class IAndroidDeviceDetection`  
_L88-104_
- desc: Interface for AndroidDeviceDetection module.
- L91 _public prototype_ `virtual void Initialize(const TCHAR* SDKDirectoryEnvVar, const TCHAR* SDKRelativeExePath, const TCHAR* GetPropCommand, bool bGetExtensionsViaSurfaceFlinger) = 0;`
- L92 _public prototype_ `virtual const TMap<FString,FAndroidDeviceInfo>& GetDeviceMap() = 0;`
- L93 _public prototype_ `virtual FCriticalSection* GetDeviceMapLock() = 0;`
- L94 _public prototype_ `virtual void UpdateADBPath() = 0;`
- L95 _public prototype_ `virtual FString GetADBPath() = 0;`
- L97 _public prototype_ `virtual void ExportDeviceProfile(const FString& OutPath, const FString& DeviceName) = 0;`
- L103 _protected prototype_ `virtual ~IAndroidDeviceDetection() = default;` — Virtual destructor

### `Source/Developer/Android/AndroidDeviceDetection/Public/Interfaces/IAndroidDeviceDetectionModule.h` (Public)


#### class `IAndroidDeviceDetectionModule`  
`class IAndroidDeviceDetectionModule : public IModuleInterface`  
_L16-32_
- inherits: `IModuleInterface`
- desc: Interface for AndroidDeviceDetection module.
- L24 _public prototype_ `virtual IAndroidDeviceDetection* GetAndroidDeviceDetection(const TCHAR* AlternamePlatformName=TEXT("")) = 0;` — Returns the android device detection singleton. @param AlternamePlatformName If a platform needs a separate detection instance, pass in an identifier here to create a new one
- L31 _protected prototype_ `virtual ~IAndroidDeviceDetectionModule( ) = default;` — Virtual destructor
