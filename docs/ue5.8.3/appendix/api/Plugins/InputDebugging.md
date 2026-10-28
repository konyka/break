# Plugins / InputDebugging

- module root: `Plugins/Runtime/InputDebugging/Source/InputDebugging`
- headers: 2; symbols: 28
- symbol kinds: class=2, function=2, macro=2, member=4, prototype=17, struct=1
- PrivateDependencyModuleNames: ApplicationCore, Core, CoreUObject, Engine, InputCore, Slate, SlateCore
- PublicDependencyModuleNames: UnrealEd

### `Plugins/Runtime/InputDebugging/Source/InputDebugging/Private/InputDeviceDebugTools.h` (Private)


#### class `FInputDeviceDebugTools`  
`class FInputDeviceDebugTools : public TSharedFromThis<FInputDeviceDebugTools>`  
_L23-52_
- inherits: `TSharedFromThis<FInputDeviceDebugTools>`
- L27 _public prototype_ `FInputDeviceDebugTools();`
- L28 _public prototype_ `~FInputDeviceDebugTools();`
- L31 _public prototype_ `FInputDeviceDebugTools(const FInputDeviceDebugTools& Other) = delete;` — non-copyable, non-movable
- L32 _public prototype_ `FInputDeviceDebugTools(FInputDeviceDebugTools&& Other) = delete;`
- L36 _private prototype_ `void AddConsoleCommands();`
- L37 _private prototype_ `void RemoveConsoleCommands();`
- L39 _private prototype_ `static void OnShowDebugInfo(AHUD* HUD, UCanvas* Canvas, const FDebugDisplayInfo& DisplayInfo, float& YL, float& YPos);`
- L41 _private prototype_ `static void OnShowDebugDeviceProperties(UCanvas* Canvas);`
- L43 _private prototype_ `static void OnShowDebugHardwareDevices(UCanvas* Canvas);`
- L46 _private prototype_ `void ListAllKnownHardwareDeviceIdentifier(const TArray<FString>& Args, UWorld* World);` — Log all the platform's currently available FHardwareDeviceIdentifier
- L48 _private prototype_ `void LogAllConnectedDevices(const TArray<FString>& Args, UWorld* World);`
- L51 _private member_ `TArray<IConsoleCommand*> ConsoleCommands;` — Console commands registered by this device debugger

#### Free symbols / members of external scopes

- L9 _macro_ `#define SUPPORT_INPUT_DEVICE_DEBUGGING !UE_BUILD_SHIPPING`

### `Plugins/Runtime/InputDebugging/Source/InputDebugging/Private/TouchInputVisualizer.h` (Private)


#### class `FTouchInputVisualizer`  
`class FTouchInputVisualizer : public IInputProcessor, public TSharedFromThis<FTouchInputVisualizer>`  
_L14-43_
- inherits: `IInputProcessor,TSharedFromThis<FTouchInputVisualizer>`
- L17 _public prototype_ `FTouchInputVisualizer();`
- L18 _public prototype_ `virtual ~FTouchInputVisualizer() = default;`
- L20 _public prototype_ `void OnDebugDraw(class UCanvas* Canvas);`
- L24 _protected function_ `virtual void Tick(const float DeltaTime, FSlateApplication& SlateApp, TSharedRef<ICursor> Cursor) override` — IInputProcessor interface
- L25 _protected prototype_ `virtual bool HandleMouseMoveEvent(FSlateApplication& SlateApp, const FPointerEvent& MouseEvent) override;`
- L26 _protected prototype_ `virtual bool HandleMouseButtonDownEvent(FSlateApplication& SlateApp, const FPointerEvent& MouseEvent) override;`
- L27 _protected prototype_ `virtual bool HandleMouseButtonUpEvent(FSlateApplication& SlateApp, const FPointerEvent& MouseEvent) override;`
- L41 _protected member_ `TMap<uint32, FDebugTouchPoint> DebugTouchPoints;`

#### struct `FTouchInputVisualizer::FDebugTouchPoint`  
`struct FDebugTouchPoint`  
_L29-39_
- L31 _public function_ `explicit FDebugTouchPoint( const FVector2D& Center, float Pressure)`
- L37 _public member_ `FVector2D Center;`
- L38 _public member_ `float Pressure;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define SUPPORT_TOUCH_INPUT_DISPLAY !UE_BUILD_SHIPPING`
