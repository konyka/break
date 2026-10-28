# Editor / DeviceProfileServices

- module root: `Source/Editor/DeviceProfileServices`
- headers: 5; symbols: 27
- symbol kinds: class=4, member=4, prototype=17, typedef=2
- PrivateDependencyModuleNames: CoreUObject, DesktopPlatform, EditorFramework, PIEPreviewDeviceSpecification, TargetPlatform, UnrealEd
- PrivateIncludePathModuleNames: 
- PublicDependencyModuleNames: Core, Engine, Json, JsonUtilities

### `Source/Editor/DeviceProfileServices/Private/DeviceProfileServicesUIManager.h` (Private)


#### class `FDeviceProfileServicesUIManager`  
`class FDeviceProfileServicesUIManager : public IDeviceProfileServicesUIManager`  
_L18-60_
- inherits: `IDeviceProfileServicesUIManager`
- desc: Implements the device profile services manager for UI
- L24 _public prototype_ `FDeviceProfileServicesUIManager( );` — Default constructor.
- L27 _public prototype_ `virtual ~FDeviceProfileServicesUIManager() = default;` — Destructor.
- L33 _public prototype_ `virtual const FName GetDeviceIconName( const FString& DeviceName ) const override;`
- L34 _public prototype_ `virtual const TArray<TSharedPtr<FString> > GetPlatformList( ) override;`
- L35 _public prototype_ `virtual void GetProfilesByType( TArray<UDeviceProfile*>& OutDeviceProfiles, const FString& InType ) override;`
- L36 _public prototype_ `virtual const FName GetPlatformIconName( const FString& DeviceName ) const override;`
- L37 _public prototype_ `virtual void SetProfile( const FString& DeviceProfileName ) override;`
- L42 _protected prototype_ `void CreatePlatformMap();` — Generates the UI icon list.
- L45 _protected prototype_ `void HandleRefreshUIData();` — Refresh the UI list - rebuild lists.
- L50 _private member_ `TMap<const UClass*, FString> PickerTypeMap;` — Map of profiles to platform types.
- L53 _private member_ `TMap<const FString, FString> DeviceToPlatformMap;` — Map of profiles to platform types.
- L56 _private member_ `TMap<const FString, FName> DeviceTypeToIconMap;` — Map of profiles to platform types.
- L59 _private member_ `TArray<TSharedPtr<FString> > PlatformList;` — Holds the list of known platforms.

### `Source/Editor/DeviceProfileServices/Public/CheckAndroidDeviceProfileCommandlet.h` (Public)


#### class `UCheckAndroidDeviceProfileCommandlet`  
`class UCheckAndroidDeviceProfileCommandlet : public UCommandlet`  
_L33-46_
- reflection: `UCLASS()`
- inherits: `UCommandlet`
- desc: CheckAndroidDeviceProfile Commandlet that runs the rules in [/Script/AndroidDeviceProfileSelector.AndroidDeviceProfileMatchingRules] against the supplied parameters and outputs the device profile that will be matched. Usage: ProjectName -run=DeviceProfileServices.CheckAndroidDeviceProfile DeviceModel ProjectName -run=DeviceProfileServices.CheckAndroidDeviceProfile DeviceMake DeviceModel ProjectName -run=DeviceProfileServices.CheckAndroidDeviceProfile [-DeviceMake=...] [-DeviceModel=...] [-GPUFamily=...] [-GLVersion=...] [-VulkanAvailable=True|False] [-VulkanVersion=...] [-AndroidVersion=...] [-DeviceBuildNumber=...] [-UsingHoudini=True|False] [-Hardware=...] [-Chipset=...] Running against ProjectName -run=DeviceProfileServices.CheckAndroidDeviceProfile -DeviceSpecsFolder=<directory containing device.json files> -DeviceSpecsFile=<path to a single device.json file> -OutDir=<output directory> [-OverrideDP=<optional DP name to override device profile selection>]
- L41 _public prototype_ `virtual int32 Main(const FString& Params) override;`

### `Source/Editor/DeviceProfileServices/Public/DeviceProfileServices.h` (Public)
_(no declarations extracted)_

### `Source/Editor/DeviceProfileServices/Public/IDeviceProfileServicesModule.h` (Public)


#### class `IDeviceProfileServicesModule`  
`class IDeviceProfileServicesModule : public IModuleInterface`  
_L12-28_
- inherits: `IModuleInterface`
- desc: Device Profile Editor module
- L22 _public prototype_ `virtual IDeviceProfileServicesUIManagerRef GetProfileServicesManager( ) = 0;` — Gets the profile services manager. @return The profile services manager.
- L27 _public prototype_ `virtual ~IDeviceProfileServicesModule( ) = default;` — Virtual destructor.

### `Source/Editor/DeviceProfileServices/Public/IDeviceProfileServicesUIManager.h` (Public)


#### class `IDeviceProfileServicesUIManager`  
`class IDeviceProfileServicesUIManager`  
_L20-61_
- desc: Device Profile Services Manager for UI.
- L30 _public prototype_ `virtual const FName GetDeviceIconName( const FString& DeviceName ) const = 0;` — Gets an icon name for a given device. @param DeviceName The device name. @return The icon name.
- L37 _public prototype_ `virtual const TArray<TSharedPtr<FString> > GetPlatformList( ) = 0;` — Gets Platform List. @return the platform list.
- L45 _public prototype_ `virtual void GetProfilesByType( TArray<UDeviceProfile*>& OutDeviceProfiles, const FString& InType ) = 0;` — Gets an array of profile that match a type. @param OutDeviceProfiles The populated profile list. @param InType The type to match.
- L53 _public prototype_ `virtual const FName GetPlatformIconName( const FString& DeviceName ) const = 0;` — Gets an icon name for a given platform. @param DeviceName -The platform name. @return The icon name.
- L60 _public prototype_ `virtual void SetProfile( const FString& DeviceProfileName ) = 0;` — Set a profile - add the type to an INI file so it can be used in a history view. @param DeviceProfileName The platform type.

#### Free symbols / members of external scopes

- L11 _typedef_ `typedef TSharedPtr<class IDeviceProfileServicesUIManager> IDeviceProfileServicesUIManagerPtr;` — Type definition for shared pointers to instances of IDeviceProfileServicesUIManager.
- L14 _typedef_ `typedef TSharedRef<class IDeviceProfileServicesUIManager> IDeviceProfileServicesUIManagerRef;` — Type definition for shared references to instances of IDeviceProfileServicesUIManager.
