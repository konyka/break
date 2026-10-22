# Editor / PIEPreviewDeviceSpecification

- module root: `Source/Editor/PIEPreviewDeviceSpecification`
- headers: 1; symbols: 74
- symbol kinds: class=1, enum=1, enumerator=6, macro=2, member=57, struct=7
- PublicDependencyModuleNames: Core, CoreUObject

### `Source/Editor/PIEPreviewDeviceSpecification/Public/PIEPreviewDeviceSpecification.h` (Public)


#### enum `EPIEPreviewDeviceType`  
`enum class EPIEPreviewDeviceType : uint8`  
_L17-25_
- reflection: `UENUM()`
- L19 _public enumerator_ `Unset`
- L20 _public enumerator_ `Android`
- L21 _public enumerator_ `IOS`
- L22 _public enumerator_ `TVOS`
- L23 _public enumerator_ `Switch`
- L24 _public enumerator_ `MAX`

#### class `UPIEPreviewDeviceSpecification`  
`class UE_DEPRECATED(5.8, "PIEPreviewDeviceProfileSelector is deprecated and will be removed. Please use the new Preview Json System to preview Devices") UPIEPreviewDeviceSpecification : public UObject`  
_L28-55_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- L33 _public member_ `EPIEPreviewDeviceType PreviewDeviceType;` — `UPROPERTY()`
- L36 _public member_ `FString GPUFamily;` — `UPROPERTY()`
- L38 _public member_ `FString GLVersion;` — `UPROPERTY()`
- L40 _public member_ `FString VulkanVersion;` — `UPROPERTY()`
- L42 _public member_ `FString AndroidVersion;` — `UPROPERTY()`
- L44 _public member_ `FString DeviceMake;` — `UPROPERTY()`
- L46 _public member_ `FString DeviceModel;` — `UPROPERTY()`
- L48 _public member_ `FString DeviceBuildNumber;` — `UPROPERTY()`
- L50 _public member_ `bool UsingHoudini;` — `UPROPERTY()`
- L52 _public member_ `FString Hardware;` — `UPROPERTY()`
- L54 _public member_ `FString Chipset;` — `UPROPERTY()`

#### struct `FPIERHIOverrideState`  
`struct UE_DEPRECATED(5.8, "PIEPreviewDeviceProfileSelector is deprecated and will be removed. Please use the new Preview Json System to preview Devices") FPIERHIOverrideState`  
_L58-76_
- reflection: `USTRUCT()`
- L63 _public member_ `int32 MaxShadowDepthBufferSizeX = 0;` — `UPROPERTY()`
- L65 _public member_ `int32 MaxShadowDepthBufferSizeY = 0;` — `UPROPERTY()`
- L67 _public member_ `int32 MaxTextureDimensions = 0;` — `UPROPERTY()`
- L69 _public member_ `int32 MaxCubeTextureDimensions = 0;` — `UPROPERTY()`
- L71 _public member_ `bool SupportsRenderTargetFormat_PF_G8 = false;` — `UPROPERTY()`
- L73 _public member_ `bool SupportsRenderTargetFormat_PF_FloatRGBA = false;` — `UPROPERTY()`
- L75 _public member_ `bool SupportsMultipleRenderTargets = false;` — `UPROPERTY()`

#### struct `FPIEAndroidDeviceProperties`  
`struct FPIEAndroidDeviceProperties`  
_L79-114_
- reflection: `USTRUCT()`
- L84 _public member_ `int32 Version = 0;` — `UPROPERTY()`
- L86 _public member_ `FString GPUFamily;` — `UPROPERTY()`
- L88 _public member_ `FString GLVersion;` — `UPROPERTY()`
- L90 _public member_ `FString VulkanVersion;` — `UPROPERTY()`
- L92 _public member_ `FString AndroidVersion;` — `UPROPERTY()`
- L94 _public member_ `FString DeviceMake;` — `UPROPERTY()`
- L96 _public member_ `FString DeviceModel;` — `UPROPERTY()`
- L98 _public member_ `FString DeviceBuildNumber;` — `UPROPERTY()`
- L100 _public member_ `bool VulkanAvailable = false;` — `UPROPERTY()`
- L102 _public member_ `bool UsingHoudini = false;` — `UPROPERTY()`
- L104 _public member_ `FString Hardware;` — `UPROPERTY()`
- L106 _public member_ `FString Chipset;` — `UPROPERTY()`
- L108 _public member_ `FString TotalPhysicalGB;` — `UPROPERTY()`
- L110 _public member_ `FString HMDSystemName;` — `UPROPERTY()`
- L113 _public member_ `bool SM5Available = false;` — `UPROPERTY()`

#### struct `FPIEIOSDeviceProperties`  
`struct FPIEIOSDeviceProperties`  
_L117-130_
- reflection: `USTRUCT()`
- L123 _public member_ `int32 Version = 0;` — `UPROPERTY()`
- L126 _public member_ `FString DeviceModel;` — `UPROPERTY()`
- L129 _public member_ `float NativeScaleFactor = 0.0f;` — `UPROPERTY()`

#### struct `FPIESwitchDeviceProperties`  
`struct FPIESwitchDeviceProperties`  
_L133-140_
- reflection: `USTRUCT()`
- L139 _public member_ `bool Docked = false;` — `UPROPERTY()`

#### struct `FPIEPreviewDeviceBezelViewportRect`  
`struct UE_DEPRECATED(5.8, "PIEPreviewDeviceProfileSelector is deprecated and will be removed. Please use the new Preview Json System to preview Devices") FPIEPreviewDeviceBezelViewportRect`  
_L144-157_
- reflection: `USTRUCT()`
- L150 _public member_ `int32 X = 0;` — `UPROPERTY()`
- L152 _public member_ `int32 Y = 0;` — `UPROPERTY()`
- L154 _public member_ `int32 Width = 0;` — `UPROPERTY()`
- L156 _public member_ `int32 Height = 0;` — `UPROPERTY()`

#### struct `FPIEBezelProperties`  
`struct UE_DEPRECATED(5.8, "PIEPreviewDeviceProfileSelector is deprecated and will be removed. Please use the new Preview Json System to preview Devices") FPIEBezelProperties`  
_L160-171_
- reflection: `USTRUCT()`
- L165 _public member_ `FString DeviceBezelFile;` — `UPROPERTY()`
- L169 _public member_ `FPIEPreviewDeviceBezelViewportRect BezelViewportRect;` — `UPROPERTY(meta = (DeprecatedProperty))`

#### struct `FPIEPreviewDeviceSpecifications`  
`struct FPIEPreviewDeviceSpecifications`  
_L174-218_
- reflection: `USTRUCT()`
- L179 _public member_ `EPIEPreviewDeviceType DevicePlatform = EPIEPreviewDeviceType::Unset;` — `UPROPERTY()`
- L181 _public member_ `int32 ResolutionX = 0;` — `UPROPERTY()`
- L183 _public member_ `int32 ResolutionY = 0;` — `UPROPERTY()`
- L185 _public member_ `int32 ResolutionYImmersiveMode = 0;` — `UPROPERTY()`
- L188 _public member_ `float InsetsLeft = 0.0f;` — `UPROPERTY()`
- L191 _public member_ `float InsetsTop = 0.0f;` — `UPROPERTY()`
- L194 _public member_ `float InsetsRight = 0.0f;` — `UPROPERTY()`
- L197 _public member_ `float InsetsBottom = 0.0f;` — `UPROPERTY()`
- L200 _public member_ `int32 PPI = 0;` — `UPROPERTY()`
- L203 _public member_ `TArray<float> ScaleFactors;` — `UPROPERTY()`
- L207 _public member_ `FPIEBezelProperties BezelProperties;` — `UPROPERTY(meta = (DeprecatedProperty))`
- L211 _public member_ `FPIEAndroidDeviceProperties AndroidProperties;` — `UPROPERTY()`
- L214 _public member_ `FPIEIOSDeviceProperties IOSProperties;` — `UPROPERTY()`
- L217 _public member_ `FPIESwitchDeviceProperties SwitchProperties;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L13 _macro_ `#define IOS_DEVICE_PROPERTIES_VERSION 1` — If you modify the logic or structure of the FPIEPreviewDeviceSpecifications Please bump the version for the platform affected and add backwards compatibility to the MakeOutdatedDeviceSpecCompatible function of the platform's Preview Device Profile Selector.
- L14 _macro_ `#define ANDROID_DEVICE_PROPERTIES_VERSION 1`
