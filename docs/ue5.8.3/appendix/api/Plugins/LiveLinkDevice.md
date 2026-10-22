# Plugins / LiveLinkDevice

- module root: `Plugins/Animation/LiveLinkDevice/Source/LiveLinkDevice`
- headers: 10; symbols: 178
- symbol kinds: class=15, delegate=5, enum=2, enumerator=9, function=30, macro=1, member=34, prototype=76, struct=5, typedef=1
- PrivateDependencyModuleNames: Core, CoreUObject, Engine, InputCore, JsonUtilities, Projects, Slate, SlateCore, ToolWidgets
- PublicDependencyModuleNames: LiveLinkInterface

### `Plugins/Animation/LiveLinkDevice/Source/LiveLinkDevice/Private/LiveLinkDeviceModule.h` (Private)


#### class `FLiveLinkDeviceModule`  
`class FLiveLinkDeviceModule : public ILiveLinkDeviceModule`  
_L18-40_
- inherits: `ILiveLinkDeviceModule`
- L22 _public prototype_ `virtual void StartupModule() override;`
- L23 _public prototype_ `virtual void ShutdownModule() override;`
- L26 _public function_ `FOnDeviceSelectionChangedDelegate& OnSelectionChanged() override`
- L29 _public prototype_ `virtual void CreateDeviceMenuEntries(FMenuBuilder& Builder) override;`
- L33 _private prototype_ `void DeviceSelectionChanged(ULiveLinkDevice* InSelectedDevice);`
- L35 _private member_ `TSharedPtr<IDetailsView> DetailsView;`
- L36 _private member_ `TWeakObjectPtr<ULiveLinkDevice> WeakSelectedDevice;`
- L37 _private member_ `FName RegisteredCustomClassLayoutName;`
- L39 _private member_ `FOnDeviceSelectionChangedDelegate OnDeviceSelectionChangedDelegate;`

### `Plugins/Animation/LiveLinkDevice/Source/LiveLinkDevice/Private/LiveLinkDeviceSettingsDetailCustomization.h` (Private)


#### class `FLiveLinkDeviceSettingsDetailCustomization`  
`class FLiveLinkDeviceSettingsDetailCustomization : public IDetailCustomization`  
_L18-35_
- inherits: `IDetailCustomization`
- desc: Detail customization for ULiveLinkDeviceSettings. Validates that DisplayName is unique across all devices.
- L21 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L24 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`
- L29 _private prototype_ `FText GetDisplayName() const;`
- L30 _private prototype_ `bool OnVerifyDisplayNameChanged(const FText& InText, FText& OutErrorMessage) const;`
- L31 _private prototype_ `void SetDisplayName(const FText& InCommittedText, ETextCommit::Type InCommitType);`
- L33 _private member_ `TWeakObjectPtr<ULiveLinkDevice> WeakDevice;`
- L34 _private member_ `TSharedPtr<IPropertyHandle> DisplayNameHandle;`

### `Plugins/Animation/LiveLinkDevice/Source/LiveLinkDevice/Private/LiveLinkDeviceStyle.h` (Private)


#### class `FLiveLinkDeviceStyle`  
`class FLiveLinkDeviceStyle`  
_L11-27_
- L14 _public prototype_ `static void Initialize();`
- L15 _public prototype_ `static void Shutdown();`
- L17 _public prototype_ `static TSharedPtr<ISlateStyle> Get();`
- L19 _public function_ `static FName GetStyleSetName()`
- L26 _private member_ `static TSharedPtr<FSlateStyleSet> StyleSet;`

### `Plugins/Animation/LiveLinkDevice/Source/LiveLinkDevice/Private/LiveLinkHubSessionExtraData_Device.h` (Private)


#### struct `FLiveLinkDevicePreset`  
`struct FLiveLinkDevicePreset`  
_L15-30_
- reflection: `USTRUCT()`
- L20 _public member_ `FGuid DeviceGuid;` — `UPROPERTY()`
- L23 _public member_ `TSubclassOf<ULiveLinkDevice> DeviceClass;` — `UPROPERTY()`
- L26 _public member_ `TObjectPtr<ULiveLinkDeviceSettings> DeviceSettings;` — `UPROPERTY(Instanced)`
- L29 _public member_ `TMap<TSubclassOf<ULiveLinkDeviceCapability>, TObjectPtr<UObject>> DeviceCapabilityData;` — `UPROPERTY(Instanced)`

#### class `ULiveLinkHubSessionExtraData_Device`  
`class ULiveLinkHubSessionExtraData_Device : public ULiveLinkHubSessionExtraData`  
_L34-41_
- reflection: `UCLASS()`
- inherits: `ULiveLinkHubSessionExtraData`
- L40 _public member_ `TArray<FLiveLinkDevicePreset> Devices;` — `UPROPERTY()`

### `Plugins/Animation/LiveLinkDevice/Source/LiveLinkDevice/Public/ILiveLinkDeviceModule.h` (Public)


#### class `ILiveLinkDeviceModule`  
`class ILiveLinkDeviceModule : public IModuleInterface`  
_L19-44_
- inherits: `IModuleInterface`
- desc: The public interface to this module
- L30 _public function_ `static inline ILiveLinkDeviceModule& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L40 _public prototype_ `virtual FOnDeviceSelectionChangedDelegate& OnSelectionChanged() = 0;` — Gets the device selection changed delegate @return Returns the device selection changed delegate
- L43 _public prototype_ `virtual void CreateDeviceMenuEntries(FMenuBuilder& Builder) = 0;` — Populate a menu builder with entries for every device registered with the device subsystem.

#### Free symbols / members of external scopes

- L10 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnDeviceSelectionChangedDelegate, ULiveLinkDevice*);`
- L10 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnDeviceSelectionChangedDelegate, ULiveLinkDevice*);`
- L12 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogLiveLinkDevice, Log, All);`
- L12 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogLiveLinkDevice, Log, All);`

### `Plugins/Animation/LiveLinkDevice/Source/LiveLinkDevice/Public/LiveLinkDevice.h` (Public)


#### enum `EDeviceHealth`  
`enum class EDeviceHealth : uint8`  
_L16-23_
- reflection: `UENUM(BlueprintType)`
- L18 _public enumerator_ `Nominal = 0`
- L19 _public enumerator_ `Good`
- L20 _public enumerator_ `Info`
- L21 _public enumerator_ `Warning`
- L22 _public enumerator_ `Error`

#### class `ULiveLinkDeviceSettings`  
`class ULiveLinkDeviceSettings : public UObject`  
_L27-36_
- reflection: `UCLASS(Abstract)`
- inherits: `UObject`
- L35 _public member_ `FString DisplayName;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LiveLink Device")` — Unique display name for this device

#### class `ULiveLinkDevice`  
`class ULiveLinkDevice : public UObject`  
_L43-109_
- reflection: `UCLASS(Abstract, Blueprintable)`
- inherits: `UObject`
- desc: Abstract base class for all Live Link devices.
- L49 _public prototype_ `virtual TSubclassOf<ULiveLinkDeviceSettings> GetSettingsClass() const PURE_VIRTUAL(ULiveLinkDevice::GetSettingsClass, return ULiveLinkDeviceSettings::StaticClass(););` — Get the device settings class to be displayed in the details view.
- L53 _public prototype_ `virtual FText GetDisplayName() const;` — `UFUNCTION(BlueprintCallable, Category="Live Link Device")` — Human-readable display name for this device.
- L57 _public prototype_ `virtual EDeviceHealth GetDeviceHealth() const PURE_VIRTUAL(ULiveLinkDevice::GetDeviceHealth, return EDeviceHealth::Error;);` — `UFUNCTION(BlueprintCallable, Category="Live Link Device")` — At-a-glance health/"severity" of the device.
- L61 _public prototype_ `virtual FText GetHealthText() const PURE_VIRTUAL(ULiveLinkDevice::GetHealthText, return FText(););` — `UFUNCTION(BlueprintCallable, Category="Live Link Device")` — Human-readable explanation for the current device health.
- L67 _public prototype_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn( const FName InColumnId, const FLiveLinkDeviceWidgetArguments& InArgs );` — Generate the Slate content, for this device's row, for the specified column. The default implementation will delegate to the capability CDO where appropriate.
- L74 _public function_ `virtual void OnDeviceAdded()` — Called when the device has been registered with the device manager, with either initial or restored settings.
- L77 _public function_ `virtual void OnDeviceRemoved()` — Called when the device is removed from the device manager.
- L80 _public function_ `virtual void OnSettingChanged(const FPropertyChangedEvent& InPropertyChangedEvent)` — Called when a setting value has changed via the UI.
- L83 _public function_ `virtual TMap<TSubclassOf<class ULiveLinkDeviceCapability>, TObjectPtr<UObject>> OnSaveDeviceCapabilityData() const` — Called when the device is being saved to the settings
- L86 _public function_ `virtual void OnLoadDeviceCapabilityData(TMap<TSubclassOf<class ULiveLinkDeviceCapability>, TObjectPtr<UObject>> InCapabilityDataMap)` — Called when the device is being loaded from the settings
- L90 _public function_ `template<typename T = ULiveLinkDeviceSettings> const T* GetDeviceSettings() const` — This device's settings UObject.
- L94 _public function_ `template<typename T = ULiveLinkDeviceSettings> T* GetDeviceSettings()` — This device's settings UObject (mutable).
- L97 _public function_ `FGuid GetDeviceId() const` — The identifier with which this device was registered with `ULiveLinkDeviceSubsystem`.
- L101 _private prototype_ `virtual void InternalDeviceAdded(const FGuid InDeviceGuid, ULiveLinkDeviceSettings* InSettings);`
- L103 _private prototype_ `const struct FSlateBrush* GetHealthImage() const;` — Provides an image for the status column in the combined list view.
- L105 _private member_ `FGuid DeviceGuid;`
- L108 _private member_ `TObjectPtr<ULiveLinkDeviceSettings> Settings;` — `UPROPERTY()`

### `Plugins/Animation/LiveLinkDevice/Source/LiveLinkDevice/Public/LiveLinkDeviceCapability.h` (Public)


#### struct `FLiveLinkDeviceWidgetArguments`  
`struct FLiveLinkDeviceWidgetArguments`  
_L16-19_
- desc: Helper passed to GenerateWidgetForColumn.
- L18 _public member_ `TDelegate<bool()> IsRowSelected;`

#### class `ULiveLinkDeviceCapability`  
`class ULiveLinkDeviceCapability : public UInterface`  
_L30-119_
- reflection: `UINTERFACE(Blueprintable)`
- inherits: `UInterface`
- desc: Base class for all device capabilities. Every IInterface has a corresponding UInterface, which exists only as a class default object (CDO), and provides a place to manage centralized state related to the capability.
- L44 _public function_ `ULiveLinkDeviceCapability()`
- L50 _public function_ `virtual void OnDeviceSubsystemInitialized()` — Called at completion of Live Link device subsystem initialization.
- L53 _public function_ `virtual void OnDeviceSubsystemDeinitializing()` — Called at the beginning of Live Link device subsystem de-initialization.
- L56 _public function_ `const TMap<FName, FDeviceTableColumnDesc>& GetTableColumns() const` — Return device table widget columns this capability provides.
- L62 _public function_ `virtual SHeaderRow::FColumn::FArguments& GenerateHeaderForColumn( const FName InColumnId, SHeaderRow::FColumn::FArguments& InArgs )` — Configure the header for the specified column.
- L74 _public function_ `virtual TSharedPtr<SWidget> GenerateWidgetForColumn( const FName InColumnId, const FLiveLinkDeviceWidgetArguments& InArgs, ULiveLinkDevice* InDevice )` — Optional; allows a capability to provide a default widget the device can fall back to.
- L89 _protected function_ `FName RegisterTableColumn(const FName InColumnShortName)` — Call this from your derived class to define a new device table column. @return The full, namespaced column identifier for future reference.
- L100 _protected function_ `void RegisterGlobalTableColumnHandler(const FName InGlobalColumnName)` — Call this from your derived class to register a handler for one of the existing columns in the combined subjects/sources/devices view. For example, this can be used by a capability to allow generating a widget for the status or action column.
- L108 _protected function_ `FName ExpandColumnShortName(FName InShortName) const`
- L118 _private member_ `TMap<FName, FDeviceTableColumnDesc> TableColumns;`

#### struct `ULiveLinkDeviceCapability::FDeviceTableColumnDesc`  
`struct FDeviceTableColumnDesc`  
_L35-41_
- L40 _public member_ `bool bGlobal = false;` — This is a global column, no header should be generated for it since it's present by default.

#### class `ILiveLinkDeviceCapability`  
`class ILiveLinkDeviceCapability`  
_L122-125_

### `Plugins/Animation/LiveLinkDevice/Source/LiveLinkDevice/Public/LiveLinkDeviceCapability_Connection.h` (Public)


#### enum `ELiveLinkDeviceConnectionStatus`  
`enum class ELiveLinkDeviceConnectionStatus : uint8`  
_L11-17_
- reflection: `UENUM()`
- desc: Device connection states.
- L13 _public enumerator_ `Disconnected`
- L14 _public enumerator_ `Connecting`
- L15 _public enumerator_ `Connected`
- L16 _public enumerator_ `Disconnecting`

#### class `ULiveLinkDeviceCapability_Connection`  
`class ULiveLinkDeviceCapability_Connection : public ULiveLinkDeviceCapability`  
_L22-54_
- reflection: `UINTERFACE()`
- inherits: `ULiveLinkDeviceCapability`
- desc: \see ILiveLinkDeviceCapability_Connection.
- L27 _public member_ `const FName Column_HardwareId;`
- L29 _public prototype_ `ULiveLinkDeviceCapability_Connection();`
- L32 _public prototype_ `virtual SHeaderRow::FColumn::FArguments& GenerateHeaderForColumn( const FName InColumnId, SHeaderRow::FColumn::FArguments& InArgs ) override;`
- L37 _public prototype_ `virtual TSharedPtr<SWidget> GenerateWidgetForColumn( const FName InColumnId, const FLiveLinkDeviceWidgetArguments& InArgs, ULiveLinkDevice* InDevice ) override;`
- L47 _protected prototype_ `TSharedRef<SWidget> Header_GetMenuContent();` — Builds the menu for the column header.
- L50 _protected prototype_ `void ConnectAllDevices();` — Invokes the `Connect` method on all registered devices implementing this interface.
- L53 _protected prototype_ `void DisconnectAllDevices();` — Invokes the `Disconnect` method on all registered devices implementing this interface.

#### class `UConnectionDelegate`  
`class UConnectionDelegate : public UObject`  
_L63-74_
- reflection: `UCLASS()`
- inherits: `UObject`
- L71 _public member_ `FDeviceConnectionStatusChangedDynamic ConnectionChangedDynamic;` — `UPROPERTY(EditAnywhere, Category = "Live Link Device|Connection")` — Dynamic delegate to be used in Blueprints. Avoid using it outside of the Game Thread.
- L73 _public member_ `FDeviceConnectionStatusChanged ConnectionChanged;`

#### class `ILiveLinkDeviceCapability_Connection`  
`class ILiveLinkDeviceCapability_Connection : public ILiveLinkDeviceCapability`  
_L81-127_
- inherits: `ILiveLinkDeviceCapability`
- desc: Status and operations relevant to devices with the concept of being (dis)connected. This could be a physical hardware connection, a network connection, or something else.
- L86 _public prototype_ `ILiveLinkDeviceCapability_Connection();`
- L90 _public prototype_ `ELiveLinkDeviceConnectionStatus GetConnectionStatus() const;` — `UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Live Link Device|Connection")` — Get the current connection state.
- L91 _public prototype_ `virtual ELiveLinkDeviceConnectionStatus GetConnectionStatus_Implementation() const = 0;`
- L95 _public prototype_ `FString GetHardwareId() const;` — `UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Live Link Device|Connection")` — Retrieve hardware identifier (serial number, network endpoint, etc).
- L96 _public prototype_ `virtual FString GetHardwareId_Implementation() const = 0;`
- L100 _public prototype_ `bool CanSetHardwareId();` — `UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Live Link Device|Connection")` — Returns whether it's valid to call `SetHardwareId()` on this device at this time.
- L101 _public function_ `virtual bool CanSetHardwareId_Implementation()`
- L105 _public prototype_ `bool SetHardwareId(const FString& HardwareID);` — `UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Live Link Device|Connection")` — Set hardware identifier (serial number, network endpoint, etc).
- L106 _public function_ `virtual bool SetHardwareId_Implementation(const FString& HardwareID)`
- L110 _public prototype_ `bool Connect();` — `UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Live Link Device|Connection")` — Attempt to establish a connection.
- L111 _public prototype_ `virtual bool Connect_Implementation() = 0;`
- L115 _public prototype_ `bool Disconnect();` — `UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Live Link Device|Connection")` — Attempt to terminate an existing connection.
- L116 _public prototype_ `virtual bool Disconnect_Implementation() = 0;`
- L119 _public prototype_ `UConnectionDelegate* GetConnectionDelegate();` — `UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Live Link Device|Connection")`
- L120 _public prototype_ `UConnectionDelegate* GetConnectionDelegate_Implementation();`
- L123 _protected prototype_ `virtual void SetConnectionStatus(ELiveLinkDeviceConnectionStatus InStatus);`
- L126 _private member_ `TStrongObjectPtr<UConnectionDelegate> ConnectionDelegate;`

#### Free symbols / members of external scopes

- L57 _delegate_ `DECLARE_TS_MULTICAST_DELEGATE_OneParam(FDeviceConnectionStatusChanged, ELiveLinkDeviceConnectionStatus);`
- L57 _prototype_ `DECLARE_TS_MULTICAST_DELEGATE_OneParam(FDeviceConnectionStatusChanged, ELiveLinkDeviceConnectionStatus);`
- L59 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDeviceConnectionStatusChangedDynamic, ELiveLinkDeviceConnectionStatus, InNewStatus);`
- L59 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDeviceConnectionStatusChangedDynamic, ELiveLinkDeviceConnectionStatus, InNewStatus);` — `UDELEGATE()`

### `Plugins/Animation/LiveLinkDevice/Source/LiveLinkDevice/Public/LiveLinkDeviceCapability_Recording.h` (Public)


#### class `ULiveLinkDeviceCapability_Recording`  
`class ULiveLinkDeviceCapability_Recording : public ULiveLinkDeviceCapability`  
_L10-35_
- reflection: `UINTERFACE()`
- inherits: `ULiveLinkDeviceCapability`
- L15 _public member_ `const FName Column_RecordingStatus;`
- L17 _public prototype_ `ULiveLinkDeviceCapability_Recording();`
- L19 _public prototype_ `virtual void OnDeviceSubsystemInitialized() override;`
- L20 _public prototype_ `virtual void OnDeviceSubsystemDeinitializing() override;`
- L22 _public prototype_ `virtual SHeaderRow::FColumn::FArguments& GenerateHeaderForColumn( const FName InColumnId, SHeaderRow::FColumn::FArguments& InArgs ) override;`
- L26 _public prototype_ `virtual TSharedPtr<SWidget> GenerateWidgetForColumn( const FName InColumnId, const FLiveLinkDeviceWidgetArguments& InArgs, ULiveLinkDevice* InDevice ) override;`
- L33 _protected prototype_ `void HandleRecordingStarted();`
- L34 _protected prototype_ `void HandleRecordingStopped();`

#### class `ILiveLinkDeviceCapability_Recording`  
`class ILiveLinkDeviceCapability_Recording : public ILiveLinkDeviceCapability`  
_L38-54_
- inherits: `ILiveLinkDeviceCapability`
- L44 _public prototype_ `bool StartRecording();` — `UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Live Link Device|Recording")`
- L45 _public prototype_ `virtual bool StartRecording_Implementation() = 0;`
- L48 _public prototype_ `bool StopRecording();` — `UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Live Link Device|Recording")`
- L49 _public prototype_ `virtual bool StopRecording_Implementation() = 0;`
- L52 _public prototype_ `bool IsRecording() const;` — `UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Live Link Device|Recording")`
- L53 _public prototype_ `virtual bool IsRecording_Implementation() const = 0;`

### `Plugins/Animation/LiveLinkDevice/Source/LiveLinkDevice/Public/LiveLinkDeviceSubsystem.h` (Public)


#### struct `FLiveLinkDeviceCreateResult`  
`struct FLiveLinkDeviceCreateResult`  
_L21-30_
- reflection: `USTRUCT(BlueprintType)`
- L26 _public member_ `FGuid DeviceId;` — `UPROPERTY(BlueprintReadWrite, Category="Live Link|Devices")`
- L29 _public member_ `TObjectPtr<ULiveLinkDevice> Device;` — `UPROPERTY(BlueprintReadWrite, Category="Live Link|Devices")`

#### struct `FLiveLinkDeviceCreateError`  
`struct FLiveLinkDeviceCreateError`  
_L34-37_
- reflection: `USTRUCT(BlueprintType)`

#### class `ULiveLinkDeviceSubsystem`  
`class ULiveLinkDeviceSubsystem : public UEngineSubsystem , public ILiveLinkHubSessionExtraDataHandler`  
_L45-146_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UEngineSubsystem,ILiveLinkHubSessionExtraDataHandler`
- desc: Device repository with lifecycle notifications. Facilitates cached lookups related to device and capability classes.
- L51 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnLiveLinkDeviceChangedDelegate, FGuid, ULiveLinkDevice*);`
- L53 _public typedef_ `using FCreateResult = TValueOrError<FLiveLinkDeviceCreateResult, FLiveLinkDeviceCreateError>;`
- L56 _public prototype_ `virtual void Initialize(FSubsystemCollectionBase& Collection) override;`
- L57 _public prototype_ `virtual void Deinitialize() override;`
- L61 _public prototype_ `virtual TSubclassOf<ULiveLinkHubSessionExtraData> GetExtraDataClass() const override;`
- L62 _public prototype_ `virtual void OnExtraDataSessionSaving(ULiveLinkHubSessionExtraData* InExtraData) override;`
- L63 _public prototype_ `virtual void OnExtraDataSessionLoaded(const ULiveLinkHubSessionExtraData* InExtraData) override;`
- L70 _public prototype_ `FCreateResult CreateDeviceOfClass( TSubclassOf<ULiveLinkDevice> InDeviceClass, ULiveLinkDeviceSettings* InDeviceSettingsTemplate = nullptr );` — Register a newly created \c ULiveLinkDevice. @return A new GUID serving as a handle to this device.
- L76 _public prototype_ `void RemoveDevice(ULiveLinkDevice* InDevice);` — Remove a previously registered device.
- L79 _public prototype_ `void RemoveDevice(FGuid InDeviceId);` — Remove a previously registered device by its GUID.
- L81 _public function_ `FOnLiveLinkDeviceChangedDelegate& OnDeviceAdded()`
- L82 _public function_ `FOnLiveLinkDeviceChangedDelegate& OnDeviceRemoved()`
- L85 _public function_ `const TMap<FGuid, TObjectPtr<ULiveLinkDevice>>& GetDeviceMap() const` — @return All added ULiveLinkDevice instances and their corresponding GUIDs.
- L88 _public function_ `const TSet<TSubclassOf<ULiveLinkDeviceCapability>>& GetKnownCapabilities() const` — @return All registered device capabilities.
- L91 _public function_ `const TSet<TSubclassOf<ULiveLinkDevice>>& GetKnownDeviceClasses() const` — @return All registered device classes.
- L94 _public function_ `const TMultiMap<TSubclassOf<ULiveLinkDevice>, TSubclassOf<ULiveLinkDeviceCapability>>& GetCapabilitiesByDeviceClass()` — @return A map from device classes to all capabilities implemented by that device class.
- L97 _public function_ `const TMultiMap<TSubclassOf<ULiveLinkDeviceCapability>, TSubclassOf<ULiveLinkDevice>>& GetDeviceClassesByCapability()` — @return A map from capability classes to all device classes implementing that capability.
- L100 _public function_ `const TMap<FName, TSubclassOf<ULiveLinkDeviceCapability>>& GetTableColumnIdToCapability()` — @return A map from device table column to capability class.
- L103 _public prototype_ `void GetDevicesByClass(TSubclassOf<ULiveLinkDevice> DeviceClass, TArray<ULiveLinkDevice*>& OutDevices) const;` — `UFUNCTION(BlueprintPure, Category="Live Link|Devices", meta=(DeterminesOutputType="DeviceClass"))`
- L106 _public prototype_ `void GetDevicesByCapability(TSubclassOf<ULiveLinkDeviceCapability> Capability, TArray<ULiveLinkDevice*>& OutDevices) const;` — `UFUNCTION(BlueprintPure, Category="Live Link|Devices")`
- L109 _public prototype_ `bool IsDisplayNameInUse(const FString& InDisplayName) const;` — Check whether a display name is already in use by any device.
- L112 _public prototype_ `FString GenerateUniqueDisplayName(const FString& InBaseName) const;` — Generate a unique display name by appending a numeric suffix if needed.
- L115 _private prototype_ `FCreateResult InternalCreateDeviceOfClass( TSubclassOf<ULiveLinkDevice> InDeviceClass, ULiveLinkDeviceSettings* InDeviceSettingsTemplate = nullptr, TOptional<FGuid> InDeviceGuid = {} );`
- L121 _private prototype_ `void InternalAddDevice(FGuid InDeviceId, ULiveLinkDevice* InDevice, ULiveLinkDeviceSettings* InSettings);`
- L122 _private prototype_ `void InternalRemoveDevice(FGuid InDeviceId, ULiveLinkDevice* InDevice);`
- L124 _private prototype_ `void RegisterCapabilityClass(TSubclassOf<ULiveLinkDeviceCapability> InCapability);`
- L125 _private prototype_ `void RegisterDeviceClass(TSubclassOf<ULiveLinkDevice> InDeviceClass);`
- L130 _private member_ `TMap<FGuid, TObjectPtr<ULiveLinkDevice>> Devices;` — `UPROPERTY()` — Devices by ID (strong references).
- L133 _private member_ `TMultiMap<TSubclassOf<ULiveLinkDevice>, ULiveLinkDevice*> DevicesByClass;` — Devices by class.
- L135 _private member_ `FOnLiveLinkDeviceChangedDelegate OnDeviceAddedDelegate;`
- L136 _private member_ `FOnLiveLinkDeviceChangedDelegate OnDeviceRemovedDelegate;`
- L140 _private member_ `TSet<TSubclassOf<ULiveLinkDeviceCapability>> KnownCapabilities;` — UClass/UInterface metadata
- L141 _private member_ `TSet<TSubclassOf<ULiveLinkDevice>> KnownDeviceClasses;`
- L142 _private member_ `TMultiMap<TSubclassOf<ULiveLinkDevice>, TSubclassOf<ULiveLinkDeviceCapability>> CapabilitiesByDeviceClass;`
- L143 _private member_ `TMultiMap<TSubclassOf<ULiveLinkDeviceCapability>, TSubclassOf<ULiveLinkDevice>> DeviceClassesByCapability;`
- L145 _private member_ `TMap<FName, TSubclassOf<ULiveLinkDeviceCapability>> TableColumnIdToCapability;`

#### Free symbols / members of external scopes

- L18 _macro_ `#define UE_API LIVELINKDEVICE_API`
- L51 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnLiveLinkDeviceChangedDelegate, FGuid, ULiveLinkDevice*);`
