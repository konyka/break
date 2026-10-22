# Plugins / LedWallCalibrationEditor

- module root: `Plugins/Experimental/VirtualProduction/LedWallCalibration/Source/LedWallCalibrationEditor`
- headers: 2; symbols: 9
- symbol kinds: class=1, delegate=1, member=2, prototype=5
- PrivateDependencyModuleNames: AssetRegistry, AssetTools, CameraCalibrationCore, CameraCalibrationCoreEditor, Core, CoreUObject, Engine, LedWallCalibration, OpenCV, OpenCVHelper, Settings, Slate, SlateCore, ToolWidgets, UnrealEd

### `Plugins/Experimental/VirtualProduction/LedWallCalibration/Source/LedWallCalibrationEditor/Private/CalibrationPointArucosForWallDetailsRow.h` (Private)


#### class `FCalibrationPointArucosForWallDetailsRow`  
`class FCalibrationPointArucosForWallDetailsRow : public ICalibrationPointComponentDetailsRow`  
_L10-34_
- inherits: `ICalibrationPointComponentDetailsRow`
- L15 _public prototype_ `virtual FText GetSearchString() const override;`
- L16 _public prototype_ `virtual bool IsAdvanced() const override;`
- L17 _public prototype_ `virtual void CustomizeRow(FDetailWidgetRow& WidgetRow, const TArray<TWeakObjectPtr<UObject>>& SelectedObjectsList) override;`
- L23 _private prototype_ `void CreateArucos(const TArray<TWeakObjectPtr<UCalibrationPointComponent>>& SelectedCalibrationPointComponents);` — Finds the panel locations and adds calibration subpoints named after aruco markers to represent them
- L28 _private member_ `EArucoDictionary PreviousArucoDictionaryUsed = EArucoDictionary::DICT_6X6_1000;` — Remember last Aruco dictionary used so that it can be pre-chosen next time
- L33 _private member_ `int32 PreviousNextMarkerId = 1;` — Remember next marker id so that it can pre-choose the next starting marker id.

### `Plugins/Experimental/VirtualProduction/LedWallCalibration/Source/LedWallCalibrationEditor/Private/LedWallCalibrationEditorLog.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogLedWallCalibrationEditor, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogLedWallCalibrationEditor, Log, All);`
