# Plugins / LiveLinkGenericRecordingDevice

- module root: `Plugins/Animation/LiveLinkGenericRecordingDevice/Source/LiveLinkGenericRecordingDevice`
- headers: 2; symbols: 23
- symbol kinds: class=3, function=1, member=4, prototype=15
- DynamicallyLoadedModuleNames: 
- PrivateDependencyModuleNames: CoreUObject, Engine, LiveLinkDevice, Projects, Slate, SlateCore
- PublicDependencyModuleNames: Core

### `Plugins/Animation/LiveLinkGenericRecordingDevice/Source/LiveLinkGenericRecordingDevice/Private/LiveLinkGenericRecordingDevice.h` (Private)


#### class `ULiveLinkGenericRecordingDeviceSettings`  
`class ULiveLinkGenericRecordingDeviceSettings : public ULiveLinkDeviceSettings`  
_L11-21_
- reflection: `UCLASS(Blueprintable)`
- inherits: `ULiveLinkDeviceSettings`
- L17 _public function_ `ULiveLinkGenericRecordingDeviceSettings()`

#### class `ULiveLinkGenericRecordingDevice`  
`class ULiveLinkGenericRecordingDevice : public ULiveLinkDevice , public ILiveLinkDeviceCapability_Recording`  
_L24-71_
- reflection: `UCLASS(Abstract, Blueprintable)`
- inherits: `ULiveLinkDevice,ILiveLinkDeviceCapability_Recording`
- L32 _public prototype_ `virtual TSubclassOf<ULiveLinkDeviceSettings> GetSettingsClass() const override;` — These delegate to BlueprintNativeEvent versions that Python can override
- L33 _public prototype_ `virtual FText GetDisplayName() const override;`
- L34 _public prototype_ `virtual EDeviceHealth GetDeviceHealth() const override;`
- L35 _public prototype_ `virtual FText GetHealthText() const override;`
- L40 _public prototype_ `FText GetDisplayNameHelper() const;` — `UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Live Link Device")` — BlueprintNativeEvent versions that Python scripts can override
- L41 _public prototype_ `virtual FText GetDisplayNameHelper_Implementation() const;`
- L44 _public prototype_ `EDeviceHealth GetDeviceHealthHelper() const;` — `UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Live Link Device")`
- L45 _public prototype_ `virtual EDeviceHealth GetDeviceHealthHelper_Implementation() const;`
- L48 _public prototype_ `FText GetHealthTextHelper() const;` — `UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Live Link Device")`
- L49 _public prototype_ `virtual FText GetHealthTextHelper_Implementation() const;`
- L53 _public prototype_ `virtual bool StartRecording_Implementation() override;` — These are already BlueprintNativeEvent so they can be overridden in Python
- L54 _public prototype_ `virtual bool StopRecording_Implementation() override;`
- L55 _public prototype_ `virtual bool IsRecording_Implementation() const override;`
- L61 _protected member_ `TSubclassOf<ULiveLinkDeviceSettings> SettingsClass;` — `UPROPERTY(EditDefaultsOnly, Category="Live Link Device")` — Settings class to use (can be set by derived Python class)
- L64 _protected member_ `bool bIsRecording = false;` — `UPROPERTY(BlueprintReadWrite, Category="Live Link Device")`
- L67 _protected member_ `FString Slate;` — `UPROPERTY(BlueprintReadWrite, Category="Live Link Device")`
- L70 _protected member_ `FString Take;` — `UPROPERTY(BlueprintReadWrite, Category="Live Link Device")`

### `Plugins/Animation/LiveLinkGenericRecordingDevice/Source/LiveLinkGenericRecordingDevice/Private/LiveLinkGenericRecordingDeviceModule.h` (Private)


#### class `FLiveLinkGenericRecordingDeviceModule`  
`class FLiveLinkGenericRecordingDeviceModule : public IModuleInterface`  
_L7-13_
- inherits: `IModuleInterface`
- L11 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L12 _public prototype_ `virtual void ShutdownModule() override;`
