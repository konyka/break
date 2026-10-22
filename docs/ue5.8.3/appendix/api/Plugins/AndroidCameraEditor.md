# Plugins / AndroidCameraEditor

- module root: `Plugins/Media/AndroidCamera/Source/AndroidCameraEditor`
- headers: 2; symbols: 8
- symbol kinds: class=2, member=4, prototype=2
- PrivateDependencyModuleNames: Core, CoreUObject, EditorFramework, MediaAssets, UnrealEd

### `Plugins/Media/AndroidCamera/Source/AndroidCameraEditor/Public/AndroidCameraEditor.h` (Public)


#### class `FAndroidCameraEditorModule`  
`class FAndroidCameraEditorModule : public IModuleInterface`  
_L10-19_
- inherits: `IModuleInterface`
- L17 _public prototype_ `virtual void StartupModule() override;`
- L18 _public prototype_ `virtual void ShutdownModule() override;`

### `Plugins/Media/AndroidCamera/Source/AndroidCameraEditor/Public/AndroidCameraRuntimeSettings.h` (Public)


#### class `UAndroidCameraRuntimeSettings`  
`class UAndroidCameraRuntimeSettings : public UObject`  
_L15-34_
- reflection: `UCLASS(Config = Engine, DefaultConfig)`
- inherits: `UObject`
- desc: Implements the settings for the AndroidCamera plugin.
- L21 _private member_ `bool bEnablePermission;` — `UPROPERTY(EditAnywhere, config, Category = ManifestSettings)` — Enable camera permission in AndroidManifest
- L25 _private member_ `bool bRequiresAnyCamera;` — `UPROPERTY(EditAnywhere, config, Category = ManifestSettings)` — Requires a camera to operate (if true and back-facing and front-facing are false, sets android.hardware.camera.any as required)
- L29 _private member_ `bool bRequiresBackFacingCamera;` — `UPROPERTY(EditAnywhere, config, Category = ManifestSettings)` — Requires back-facing camera in AndroidManifest (android.hardware.camera)
- L33 _private member_ `bool bRequiresFrontFacingCamera;` — `UPROPERTY(EditAnywhere, config, Category = ManifestSettings)` — Requires front-facing camera in AndroidManifest (android.hardware.camera.front)
