# Plugins / GameInputWindows

- module root: `Plugins/GameInputWindows/Source/GameInputWindows`
- headers: 2; symbols: 16
- symbol kinds: class=2, member=1, prototype=13
- PrivateDependencyModuleNames: ApplicationCore, Core, CoreUObject, DeveloperSettings, Engine, GameInputBase, InputCore, InputDevice

### `Plugins/GameInputWindows/Source/GameInputWindows/Private/GameInputWindowsDevice.h` (Private)


#### class `FGameInputWindowsInputDevice`  
`class FGameInputWindowsInputDevice : public IGameInputDeviceInterface`  
_L9-34_
- inherits: `IGameInputDeviceInterface`
- L12 _public prototype_ `explicit FGameInputWindowsInputDevice(const TSharedRef<FGenericApplicationMessageHandler>& InMessageHandler, struct IGameInput* InGameInput);`
- L15 _public prototype_ `void SetGameInputAndReinitialize(IGameInput* InGameInput);`
- L20 _protected prototype_ `virtual GameInputKind GetCurrentGameInputKindSupport() const override;`
- L21 _protected prototype_ `virtual void HandleDeviceDisconnected(IGameInputDevice* Device, uint64 Timestamp) override;`
- L22 _protected prototype_ `virtual void HandleDeviceConnected(IGameInputDevice* Device, uint64 Timestamp) override;`
- L23 _protected prototype_ `virtual FGameInputDeviceContainer* CreateDeviceData(IGameInputDevice* InDevice) override;`
- L28 _private prototype_ `void SetupEditorSettingListener();`
- L29 _private prototype_ `void CleanupEditorSettingListener();`
- L30 _private prototype_ `void HandleEditorSettingChanged();`
- L32 _private member_ `FDelegateHandle EditorSettingChangedDelegate;`

### `Plugins/GameInputWindows/Source/GameInputWindows/Private/GameInputWindowsModule.h` (Private)


#### class `FGameInputWindowsModule`  
`class FGameInputWindowsModule : public IInputDeviceModule`  
_L10-22_
- inherits: `IInputDeviceModule`
- desc: Input Device module that will create the Game Input Device to handle input on Windows platforms.
- L13 _public prototype_ `static FGameInputWindowsModule& Get();`
- L16 _public prototype_ `static bool IsAvailable();` — Returns true if this module is loaded (aka available) by the FModuleManager
- L19 _public prototype_ `virtual TSharedPtr<IInputDevice> CreateInputDevice(const TSharedRef<FGenericApplicationMessageHandler>& InMessageHandler) override;`
- L20 _public prototype_ `virtual const TCHAR* GetPreferredDeviceAPIString() const override;`
