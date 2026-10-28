# Runtime / LaunchDaemonMessages

- module root: `Source/Runtime/IOS/LaunchDaemonMessages`
- headers: 2; symbols: 21
- symbol kinds: function=4, member=14, struct=3
- PrivateDependencyModuleNames: Core
- PublicDependencyModuleNames: CoreUObject

### `Source/Runtime/IOS/LaunchDaemonMessages/Classes/IOSMessageProtocol.h` (Public)


#### struct `FIOSLaunchDaemonPing`  
`struct FIOSLaunchDaemonPing`  
_L12-17_
- reflection: `USTRUCT()`

#### struct `FIOSLaunchDaemonPong`  
`struct FIOSLaunchDaemonPong`  
_L21-80_
- reflection: `USTRUCT()`
- L26 _public member_ `FString DeviceID;` — `UPROPERTY()`
- L29 _public member_ `FString DeviceUDID;` — `UPROPERTY()`
- L32 _public member_ `FString DeviceName;` — `UPROPERTY()`
- L35 _public member_ `FString DeviceStatus;` — `UPROPERTY()`
- L38 _public member_ `FString DeviceType;` — `UPROPERTY()`
- L41 _public member_ `FString DeviceOSVersion;` — `UPROPERTY()`
- L44 _public member_ `FString DeviceModelId;` — `UPROPERTY()`
- L47 _public member_ `FString DeviceConnectionType;` — `UPROPERTY()`
- L50 _public member_ `bool bCanPowerOff;` — `UPROPERTY()`
- L53 _public member_ `bool bCanPowerOn;` — `UPROPERTY()`
- L56 _public member_ `bool bIsAuthorized;` — `UPROPERTY()`
- L59 _public member_ `bool bCanReboot;` — `UPROPERTY()`
- L61 _public function_ `FIOSLaunchDaemonPong() : bCanPowerOff(false) , bCanPowerOn(false) , bIsAuthorized(false) , bCanReboot(false)`
- L68 _public function_ `FIOSLaunchDaemonPong(FString InDeviceID, FString InDeviceUDID, FString InDeviceName, FString InDeviceStatus, FString InDeviceType, FString InDeviceConnectionType, bool bInCanPowerOff, bool bInCanPowerOn, bool bInCanReboot, bool bIsAuthorized) : DeviceID(InDeviceID) , DeviceUDID(InDeviceUDID) , DeviceName(InDeviceName) , DeviceStatus(InDeviceStatus) , DeviceType(InDeviceType) , DeviceConnectionType(InDeviceConnectionType) , bCanPowerOff(bInCanPowerOff) , bCanPowerOn(bInCanPowerOn) , bIsAuthorized(bIsAuthorized) , bCanReboot(bInCanReboot)`

#### struct `FIOSLaunchDaemonLaunchApp`  
`struct FIOSLaunchDaemonLaunchApp`  
_L84-100_
- reflection: `USTRUCT()`
- L89 _public member_ `FString AppID;` — `UPROPERTY()`
- L92 _public member_ `FString Parameters;` — `UPROPERTY()`
- L94 _public function_ `FIOSLaunchDaemonLaunchApp()`
- L96 _public function_ `FIOSLaunchDaemonLaunchApp(FString InAppID, FString Params) : AppID(InAppID) , Parameters(Params)`

### `Source/Runtime/IOS/LaunchDaemonMessages/Public/LaunchDaemonMessages.h` (Public)
_(no declarations extracted)_
