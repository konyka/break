# Plugins / LiveLinkCameraEditor

- module root: `Plugins/VirtualProduction/LiveLinkCamera/Source/LiveLinkCameraEditor`
- headers: 2; symbols: 13
- symbol kinds: class=2, function=1, member=1, prototype=9
- PrivateDependencyModuleNames: CameraCalibrationCore, Core, CoreUObject, DetailCustomizations, LiveLinkCamera, LiveLinkComponents, LiveLinkInterface, PropertyEditor, Slate, SlateCore

### `Plugins/VirtualProduction/LiveLinkCamera/Source/LiveLinkCameraEditor/Private/LiveLinkCameraControllerCustomization.h` (Private)


#### class `FLiveLinkCameraControllerCustomization`  
`class FLiveLinkCameraControllerCustomization : public IDetailCustomization`  
_L18-56_
- inherits: `IDetailCustomization`
- desc: Implements a details view customization for the ULiveLinkCameraController class.
- L23 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`
- L33 _public function_ `static TSharedRef<IDetailCustomization> MakeInstance()` — Creates an instance of this class. @return The new instance.
- L41 _private prototype_ `FString HandleFilePathPickerFilePath() const;` — Callback for getting the selected path in the URL picker widget.
- L44 _private prototype_ `FString HandleFilePathPickerFileTypeFilter() const;` — Callback for getting the file type filter for the URL picker.
- L47 _private prototype_ `void HandleFilePathPickerPathPicked(const FString& PickedPath);` — Callback for picking a path in the URL picker.
- L50 _private prototype_ `EVisibility HandleEncoderMappingWarningIconVisibility() const;` — Callback for getting the visibility of warning icon for invalid encoder mapping
- L55 _private member_ `TWeakObjectPtr<ULiveLinkComponentController> EditedObject;` — LiveLinkComponent on which we're acting

### `Plugins/VirtualProduction/LiveLinkCamera/Source/LiveLinkCameraEditor/Private/LiveLinkCameraEditorModule.h` (Private)


#### class `FLiveLinkCameraEditorModule`  
`class FLiveLinkCameraEditorModule : public IModuleInterface`  
_L8-20_
- inherits: `IModuleInterface`
- L13 _public prototype_ `virtual void StartupModule() override;`
- L14 _public prototype_ `virtual void ShutdownModule() override;`
- L18 _private prototype_ `void RegisterCustomizations();`
- L19 _private prototype_ `void UnregisterCustomizations();`
