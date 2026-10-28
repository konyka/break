# Plugins / ColorCorrectRegionsEditor

- module root: `Plugins/Experimental/ColorCorrectRegions/Source/ColorCorrectRegionsEditor`
- headers: 6; symbols: 35
- symbol kinds: class=5, delegate=1, function=1, member=4, prototype=23, struct=1
- PrivateDependencyModuleNames: ActorPickerMode, ColorCorrectRegions, ColorGradingEditor, Core, CoreUObject, Engine, LevelEditor, ObjectMixerEditor, PlacementMode, Projects, SceneOutliner, Slate, SlateCore, ToolMenus, TypedElementRuntime, UnrealEd

### `Plugins/Experimental/ColorCorrectRegions/Source/ColorCorrectRegionsEditor/Private/ColorCorrectRegionCustomization.h` (Private)


#### class `FColorCorrectWindowDetails`  
`class FColorCorrectWindowDetails : public IDetailCustomization`  
_L12-20_
- inherits: `IDetailCustomization`
- L16 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L19 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;` — IDetailCustomization interface

### `Plugins/Experimental/ColorCorrectRegions/Source/ColorCorrectRegionsEditor/Private/ColorCorrectionActorContextMenu.h` (Private)


#### class `FColorCorrectionActorContextMenu`  
`class FColorCorrectionActorContextMenu`  
_L8-23_
- L12 _public prototype_ `void RegisterContextMenuExtender();` — Create all required callbacks for context menu's widget and button creation.
- L15 _public prototype_ `void UnregisterContextMenuExtender();` — Release context menu related resources such as handles.
- L19 _private member_ `FLevelEditorModule::FLevelViewportMenuExtender_SelectedActors CCRLevelViewportContextMenuExtender;` — Context menu extender.
- L22 _private member_ `FDelegateHandle ContextMenuExtenderDelegateHandle;` — Handle to context menu extender delegate.

### `Plugins/Experimental/ColorCorrectRegions/Source/ColorCorrectRegionsEditor/Private/ColorGradingDataModelGenerator_ColorCorrectRegion.h` (Private)


#### class `FColorGradingDataModelGenerator_ColorCorrectRegion`  
`class FColorGradingDataModelGenerator_ColorCorrectRegion : public IColorGradingEditorDataModelGenerator`  
_L11-25_
- inherits: `IColorGradingEditorDataModelGenerator`
- desc: Color Grading Data Model Generator for the AColorCorrectionRegion actor class
- L14 _public prototype_ `static TSharedRef<IColorGradingEditorDataModelGenerator> MakeInstance();`
- L17 _public prototype_ `virtual void Initialize(const TSharedRef<class FColorGradingEditorDataModel>& ColorGradingDataModel, const TSharedRef<IPropertyRowGenerator>& PropertyRowGenerator) override;`
- L18 _public prototype_ `virtual void Destroy(const TSharedRef<class FColorGradingEditorDataModel>& ColorGradingDataModel, const TSharedRef<IPropertyRowGenerator>& PropertyRowGenerator) override;`
- L19 _public prototype_ `virtual void GenerateDataModel(IPropertyRowGenerator& PropertyRowGenerator, FColorGradingEditorDataModel& OutColorGradingDataModel) override;`
- L24 _private prototype_ `FColorGradingEditorDataModel::FColorGradingElement CreateColorGradingElement(const TSharedRef<IDetailTreeNode>& GroupNode, FText ElementLabel);` — Creates a new color grading element structure for the specified detail tree node, which is expected to have child color properties with the ColorGradingMode metadata set

### `Plugins/Experimental/ColorCorrectRegions/Source/ColorCorrectRegionsEditor/Private/ColorGradingHierarchyConfig_ColorCorrectRegion.h` (Private)


#### struct `FColorGradingHierarchyConfig_ColorCorrectRegion`  
`struct FColorGradingHierarchyConfig_ColorCorrectRegion : IColorGradingMixerObjectHierarchyConfig`  
_L8-21_
- inherits: `IColorGradingMixerObjectHierarchyConfig`
- desc: Color Grading hierarchy config for the AColorCorrectionRegion actor class
- L11 _public prototype_ `static TSharedRef<IColorGradingMixerObjectHierarchyConfig> MakeInstance();`
- L14 _public prototype_ `virtual TArray<AActor*> FindAssociatedActors(UObject* ParentObject) const override;`
- L15 _public prototype_ `virtual bool IsActorAssociated(UObject* ParentObject, AActor* AssociatedActor) const override;`
- L16 _public prototype_ `virtual bool HasCustomDropHandling() const override;`
- L17 _public prototype_ `virtual FSceneOutlinerDragValidationInfo ValidateDrop(UObject* DropTarget, const FSceneOutlinerDragDropPayload& Payload) const override;`
- L18 _public prototype_ `virtual bool OnDrop(UObject* DropTarget, const FSceneOutlinerDragDropPayload& Payload, const FSceneOutlinerDragValidationInfo& ValidationInfo) const override;`
- L19 _public prototype_ `virtual TSet<FName> GetPropertiesThatRequireListRefresh() const override;`

### `Plugins/Experimental/ColorCorrectRegions/Source/ColorCorrectRegionsEditor/Public/ColorCorrectRegionsEditorModule.h` (Public)


#### class `FColorCorrectRegionsEditorModule`  
`class FColorCorrectRegionsEditorModule : public IModuleInterface`  
_L10-24_
- inherits: `IModuleInterface`
- L15 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation start
- L16 _public prototype_ `virtual void ShutdownModule() override;`
- L19 _public prototype_ `void RegisterSectionMappings();`
- L20 _public prototype_ `void OnPlacementModeRefresh(FName CategoryName);`
- L23 _private member_ `TSharedPtr<class FColorCorrectionActorContextMenu> ContextMenu;`

#### Free symbols / members of external scopes

- L8 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(ColorCorrectRegionsEditorLogOutput, Log, All);`
- L8 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(ColorCorrectRegionsEditorLogOutput, Log, All);`

### `Plugins/Experimental/ColorCorrectRegions/Source/ColorCorrectRegionsEditor/Public/ColorCorrectRegionsStyle.h` (Public)


#### class `FColorCorrectRegionsStyle`  
`class FColorCorrectRegionsStyle`  
_L8-17_
- L11 _public prototype_ `static void Initialize();`
- L12 _public prototype_ `static void Shutdown();`
- L13 _public function_ `static TSharedPtr<ISlateStyle> Get()`
- L16 _private member_ `static TSharedPtr<FSlateStyleSet> CCRStyle;`
