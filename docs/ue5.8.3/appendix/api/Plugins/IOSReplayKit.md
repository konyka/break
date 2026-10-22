# Plugins / IOSReplayKit

- module root: `Plugins/Runtime/IOSReplayKit/Source/IOSReplayKit`
- headers: 3; symbols: 21
- symbol kinds: class=2, delegate=1, function=2, prototype=16
- PrivateDependencyModuleNames: Core, CoreUObject, EditorFramework, Engine, UnrealEd

### `Plugins/Runtime/IOSReplayKit/Source/IOSReplayKit/Private/ReplayKitRecorder.h` (Private)
_(no declarations extracted)_

### `Plugins/Runtime/IOSReplayKit/Source/IOSReplayKit/Public/IOSReplayKit.h` (Public)


#### class `IIOSReplayKitModuleInterface`  
`class IIOSReplayKitModuleInterface : public IModuleInterface`  
_L14-56_
- inherits: `IModuleInterface`
- desc: The public interface to this module.  In most cases, this interface is only public to sibling modules within this plugin.
- L19 _public prototype_ `virtual void Initialize( bool bMicrophoneEnabled = false, bool bCameraEnabled = false ) = 0;`
- L21 _public prototype_ `virtual void StartRecording() = 0;`
- L22 _public prototype_ `virtual void StopRecording() = 0;`
- L24 _public prototype_ `virtual void StartCaptureToFile() = 0;`
- L25 _public prototype_ `virtual void StopCapture() = 0;`
- L27 _public prototype_ `virtual void StartBroadcast() = 0;`
- L28 _public prototype_ `virtual void PauseBroadcast() = 0;`
- L29 _public prototype_ `virtual void ResumeBroadcast() = 0;`
- L30 _public prototype_ `virtual void StopBroadcast() = 0;`
- L38 _public function_ `static inline IIOSReplayKitModuleInterface& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L48 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use
- L54 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L55 _public prototype_ `virtual void ShutdownModule() override;`

#### Free symbols / members of external scopes

- L8 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogIOSReplayKit, Log, All);`
- L8 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogIOSReplayKit, Log, All);`

### `Plugins/Runtime/IOSReplayKit/Source/IOSReplayKit/Public/IOSReplayKitControl.h` (Public)


#### class `UIOSReplayKitControl`  
`class UIOSReplayKitControl : public UBlueprintFunctionLibrary`  
_L10-26_
- reflection: `UCLASS()`
- inherits: `UBlueprintFunctionLibrary`
- L16 _public prototype_ `static void StartRecording(bool bMicrophoneEnabled = true);` — `UFUNCTION(BlueprintCallable, Category="IOSReplayKit", meta = (WorldContext = "WorldContextObject", Keywords = "replaykit record"))`
- L19 _public prototype_ `static void StopRecording();` — `UFUNCTION(BlueprintCallable, Category="IOSReplayKit", meta = (WorldContext = "WorldContextObject", Keywords = "replaykit record"))`
- L22 _public prototype_ `static void StartCaptureToFile(bool bMicrophoneEnabled = true);` — `UFUNCTION(BlueprintCallable, Category="IOSReplayKit", meta = (WorldContext = "WorldContextObject", Keywords = "replaykit capture"))`
- L25 _public prototype_ `static void StopCapture();` — `UFUNCTION(BlueprintCallable, Category="IOSReplayKit", meta = (WorldContext = "WorldContextObject", Keywords = "replaykit capture"))`
