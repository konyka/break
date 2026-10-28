# Plugins / InputDebuggingEditor

- module root: `Plugins/Runtime/InputDebugging/Source/InputDebuggingEditor`
- headers: 1; symbols: 6
- symbol kinds: class=1, member=1, prototype=4
- PrivateDependencyModuleNames: ApplicationCore, Core, Engine, MainFrame, Slate, SlateCore

### `Plugins/Runtime/InputDebugging/Source/InputDebuggingEditor/Public/InputDebuggingEditorModule.h` (Public)


#### class `FInputDebuggingEditorModule`  
`class FInputDebuggingEditorModule : public IModuleInterface`  
_L10-29_
- inherits: `IModuleInterface`
- L14 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L15 _public prototype_ `virtual void ShutdownModule() override;`
- L22 _private prototype_ `static const FText& ConnectionStateToText(const EInputDeviceConnectionState NewConnectionState);` — Returns an FText label for the given input device connection state
- L25 _private prototype_ `void OnInputDeviceConnectionChange(EInputDeviceConnectionState NewConnectionState, FPlatformUserId PlatformUserId, FInputDeviceId InputDeviceId);` — Callback for when an input device has a connection state change (New gamepad plugged in, unplugged, etc)
- L28 _private member_ `TSharedPtr<FSlateStyleSet> StyleSet;` — A custom slate style for input debugging related things
