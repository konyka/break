# Plugins / VirtualCameraEditor

- module root: `Plugins/VirtualProduction/VirtualCamera/Source/VirtualCameraEditor`
- headers: 1; symbols: 8
- symbol kinds: class=1, namespace=4, prototype=3
- PrivateDependencyModuleNames: CinematicCamera, Core, CoreUObject, EditorWidgets, Engine, PlacementMode, Settings, TakeRecorderSources, UnrealEd, VCamCore, VPUtilitiesEditor, VirtualCamera

### `Plugins/VirtualProduction/VirtualCamera/Source/VirtualCameraEditor/Private/Cinematic/VCamSupportForCinematicTooling.h` (Private)


#### class `UE::VirtualCamera::FVCamSupportForCinematicTooling`  
`class FVCamSupportForCinematicTooling : public FNoncopyable`  
_L12-21_
- inherits: `FNoncopyable`
- desc: Manages setting up global delegates, etc. so VCam operates correctly with Take Recorder & Sequencer.
- L16 _public prototype_ `FVCamSupportForCinematicTooling();`
- L17 _public prototype_ `~FVCamSupportForCinematicTooling();`
- L20 _public prototype_ `static bool CanRecordComponent(const TakeRecorderSources::FCanRecordArgs& InArgs);` — Used by ITakeRecorderSourcesModule::RegisterCanRecordDelegate. If a VCam is set to record as ACineCameraActor, this will skip any additional components, such as VCam and the input component.

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace TakeRecorderSources` (scope `UE`)
- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace VirtualCamera` (scope `UE`)
