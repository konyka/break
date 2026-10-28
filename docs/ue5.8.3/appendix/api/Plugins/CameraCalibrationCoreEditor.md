# Plugins / CameraCalibrationCoreEditor

- module root: `Plugins/VirtualProduction/CameraCalibrationCore/Source/CameraCalibrationCoreEditor`
- headers: 6; symbols: 38
- symbol kinds: class=5, delegate=2, function=3, macro=1, member=5, prototype=22
- PrivateDependencyModuleNames: CameraCalibrationCore, Core, CoreUObject, Engine, PlacementMode, PropertyEditor, Slate, SlateCore, UnrealEd
- PrivateIncludePathModuleNames: LevelEditor

### `Plugins/VirtualProduction/CameraCalibrationCore/Source/CameraCalibrationCoreEditor/Private/CalibrationPointComponentDetails.h` (Private)


#### class `FCalibrationPointComponentDetails`  
`class FCalibrationPointComponentDetails : public IDetailCustomization`  
_L11-20_
- inherits: `IDetailCustomization`
- L15 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L18 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;` — Makes a new instance of this detail layout class for a specific detail view requesting it static TSharedRef<IDetailCustomization> MakeInstance(); ~ Begin IDetailCustomization interface

### `Plugins/VirtualProduction/CameraCalibrationCore/Source/CameraCalibrationCoreEditor/Private/CameraCalibrationCoreEditorLog.h` (Private)


#### Free symbols / members of external scopes

- L8 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogCameraCalibrationCoreEditor, Log, All);`
- L8 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogCameraCalibrationCoreEditor, Log, All);`

### `Plugins/VirtualProduction/CameraCalibrationCore/Source/CameraCalibrationCoreEditor/Private/CameraCalibrationCoreEditorStyle.h` (Private)


#### class `FCameraCalibrationCoreEditorStyle`  
`class FCameraCalibrationCoreEditorStyle final : public FSlateStyleSet`  
_L14-41_
- inherits: `FSlateStyleSet`
- desc: Implements the visual style of the camera calibration core  UI.
- L19 _public function_ `FCameraCalibrationCoreEditorStyle() : FSlateStyleSet("CameraCalibrationCoreEditorStyle")` — Default constructor.
- L31 _public function_ `virtual ~FCameraCalibrationCoreEditorStyle()` — Virtual destructor.
- L36 _public function_ `static FCameraCalibrationCoreEditorStyle& Get()`

### `Plugins/VirtualProduction/CameraCalibrationCore/Source/CameraCalibrationCoreEditor/Public/CameraCalibrationCoreEditorModule.h` (Public)


#### class `FCameraCalibrationCoreEditorModule`  
`class FCameraCalibrationCoreEditorModule : public IModuleInterface`  
_L21-59_
- inherits: `IModuleInterface`
- desc: Implements the CameraCalibrationCoreEditor module.
- L26 _public prototype_ `virtual void StartupModule() override;`
- L27 _public prototype_ `virtual void ShutdownModule() override;`
- L31 _public prototype_ `void RegisterCalibrationPointDetailsRow(const TWeakPtr<ICalibrationPointComponentDetailsRow> Row);` — Register a details row generator for CalibrationPointComponent
- L34 _public prototype_ `void UnregisterCalibrationPointDetailsRow(const TWeakPtr<ICalibrationPointComponentDetailsRow> Row);` — Unregister a details row generator for CalibrationPointComponent
- L37 _public prototype_ `TArray<TWeakPtr<ICalibrationPointComponentDetailsRow>> GetRegisteredCalibrationPointComponentDetailsRows();` — Returns a copy of the set of registered calibration point details rows
- L42 _private prototype_ `void RegisterPlacementModeItems();` — Register items to show up in the Place Actors panel.
- L45 _private prototype_ `void UnregisterPlacementModeItems();` — Unregister items in Place Actors panel
- L48 _private prototype_ `const FPlacementCategoryInfo* GetVirtualProductionCategoryRegisteredInfo() const;` — Gathers the Info on the Virtual Production Place Actors Category
- L52 _private member_ `TArray<TSharedRef<IAssetTypeActions>> RegisteredAssetTypeActions;`
- L53 _private member_ `FDelegateHandle PostEngineInitHandle;`
- L55 _private member_ `TArray<TOptional<FPlacementModeID>> PlaceActors;`
- L58 _private member_ `TArray<TWeakPtr<ICalibrationPointComponentDetailsRow>> RegisteredCalibrationPointComponentDetailsRows;` — Array of registered details rows for CalibrationPointComponents

#### Free symbols / members of external scopes

- L15 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogCameraCalibrationCoreEditor, Log, All);`
- L15 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogCameraCalibrationCoreEditor, Log, All);`

### `Plugins/VirtualProduction/CameraCalibrationCore/Source/CameraCalibrationCoreEditor/Public/ICalibrationPointComponentDetailsRow.h` (Public)


#### class `ICalibrationPointComponentDetailsRow`  
`class ICalibrationPointComponentDetailsRow`  
_L12-35_
- L16 _public prototype_ `virtual ~ICalibrationPointComponentDetailsRow() = default;`
- L21 _public prototype_ `virtual FText GetSearchString() const = 0;` — Returns the search string for this details row
- L24 _public prototype_ `virtual bool IsAdvanced() const = 0;` — True if this details row should appear in advanced section
- L32 _public prototype_ `virtual void CustomizeRow( FDetailWidgetRow& WidgetRow, const TArray<TWeakObjectPtr<UObject>>& SelectedObjectsList) = 0;` — Customizes the given details widget row @param WidgetRow the detail widget row to customize @param SelectedObjectsList the list of objects selected that this row may apply to.

### `Plugins/VirtualProduction/CameraCalibrationCore/Source/CameraCalibrationCoreEditor/Public/LensDistortionStateDetailCustomization.h` (Public)


#### class `FLensDistortionStateDetailCustomization`  
`class FLensDistortionStateDetailCustomization : public IPropertyTypeCustomization`  
_L12-34_
- inherits: `IPropertyTypeCustomization`
- L15 _public prototype_ `FLensDistortionStateDetailCustomization(TSubclassOf<ULensModel> InLensModel);`
- L18 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L19 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> PropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L24 _private prototype_ `void CustomizeDistortionInfo(TSharedRef<IPropertyHandle> PropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils);` — Customize the FDistortionInfo struct property
- L27 _private prototype_ `void CustomizeFocalLengthInfo(TSharedRef<IPropertyHandle> PropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils);` — Customize the FFocalLengthInfo struct property
- L30 _private prototype_ `void CustomizeImageCenterInfo(TSharedRef<IPropertyHandle> PropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils);` — Customize the FImageCenterInfo struct property
- L33 _private member_ `TSubclassOf<ULensModel> LensModel;` — The LensModel used to customize the names of the properties in the distortion parameter array

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API CAMERACALIBRATIONCOREEDITOR_API`
