# Plugins / ChaosClothEditor

- module root: `Plugins/ChaosCloth/Source/ChaosClothEditor`
- headers: 4; symbols: 33
- symbol kinds: class=3, delegate=1, member=2, namespace=1, prototype=26
- PrivateDependencyModuleNames: ChaosCloth, ClothingSystemEditorInterface, Core, CoreUObject, DetailCustomizations, EditorFramework, Engine, InputCore, Persona, Slate, SlateCore, UnrealEd

### `Plugins/ChaosCloth/Source/ChaosClothEditor/Private/ChaosClothEditor/ChaosClothEditorPrivate.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogChaosClothEditor, Verbose, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogChaosClothEditor, Verbose, All);`

### `Plugins/ChaosCloth/Source/ChaosClothEditor/Private/ChaosClothEditor/ChaosClothWeightedValueCustomization.h` (Private)


#### class `FChaosClothWeightedValueCustomization`  
`class FChaosClothWeightedValueCustomization : public FMathStructCustomization`  
_L14-56_
- inherits: `FMathStructCustomization`
- desc: Customization for all property that also uses weight maps. Works like a FMathStructCustomization with the difference that the structure member short names are displayed in the header's row.
- L18 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L20 _public prototype_ `FChaosClothWeightedValueCustomization();`
- L24 _protected prototype_ `virtual TSharedRef<SWidget> MakeChildWidget(TSharedRef<IPropertyHandle>& StructurePropertyHandle, TSharedRef<IPropertyHandle>& PropertyHandle) override;`
- L29 _private prototype_ `template <typename NumericType> static void ExtractNumericMetadata(TSharedRef<IPropertyHandle>& PropertyHandle, TOptional<NumericType>& MinValue, TOptional<NumericType>& MaxValue, TOptional<NumericType>& SliderMinValue, TOptional<NumericType>& SliderMaxValue, NumericType& SliderExponent, NumericType& Delta, float& ShiftMultiplier, float& CtrlMultiplier, bool& SupportDynamicSliderMaxValue, bool& SupportDynamicSliderMinValue);` — Have to duplicate all protected templates from FMathStructCustomization, since they are not correctly exported
- L32 _private prototype_ `template<typename NumericType> TSharedRef<SWidget> MakeNumericWidget(TSharedRef<IPropertyHandle>& StructurePropertyHandle, TSharedRef<IPropertyHandle>& PropertyHandle);`
- L35 _private prototype_ `template<typename NumericType> TOptional<NumericType> OnGetValue(TWeakPtr<IPropertyHandle> WeakHandlePtr) const;`
- L38 _private prototype_ `template<typename NumericType> void OnValueCommitted(NumericType NewValue, ETextCommit::Type CommitType, TWeakPtr<IPropertyHandle> WeakHandlePtr);`
- L41 _private prototype_ `template<typename NumericType> void OnValueChanged(NumericType NewValue, TWeakPtr<IPropertyHandle> WeakHandlePtr);`
- L44 _private prototype_ `template<typename NumericType> void SetValue(NumericType NewValue, EPropertyValueSetFlags::Type Flags, TWeakPtr<IPropertyHandle> WeakHandlePtr);`
- L46 _private prototype_ `void OnBeginSliderMovement();`
- L49 _private prototype_ `template<typename NumericType> void OnEndSliderMovement(NumericType NewValue);`
- L52 _private prototype_ `template <typename NumericType> void OnDynamicSliderMaxValueChanged(NumericType NewMaxSliderValue, TWeakPtr<SWidget> InValueChangedSourceWidget, bool IsOriginator, bool UpdateOnlyIfHigher);`
- L55 _private prototype_ `template <typename NumericType> void OnDynamicSliderMinValueChanged(NumericType NewMinSliderValue, TWeakPtr<SWidget> InValueChangedSourceWidget, bool IsOriginator, bool UpdateOnlyIfLower);`

### `Plugins/ChaosCloth/Source/ChaosClothEditor/Public/ChaosClothEditor/ChaosClothEditorModule.h` (Public)


#### class `FChaosClothEditorModule`  
`class FChaosClothEditorModule : public IModuleInterface`  
_L8-16_
- inherits: `IModuleInterface`
- L11 _public prototype_ `virtual void StartupModule() override;`
- L12 _public prototype_ `virtual void ShutdownModule() override;`
- L15 _private member_ `Chaos::FSimulationEditorExtender ChaosEditorExtender;`

### `Plugins/ChaosCloth/Source/ChaosClothEditor/Public/ChaosClothEditor/ChaosSimulationEditorExtender.h` (Public)


#### class `Chaos::FSimulationEditorExtender`  
`class FSimulationEditorExtender : public ISimulationEditorExtender`  
_L12-43_
- inherits: `ISimulationEditorExtender`
- desc: Chaos extension to the asset editor.
- L15 _public prototype_ `FSimulationEditorExtender();`
- L19 _public prototype_ `virtual UClass* GetSupportedSimulationFactoryClass() override;` — ISimulationEditorExtender Interface
- L20 _public prototype_ `virtual void ExtendViewportShowMenu(FMenuBuilder& MenuBuilder, TSharedRef<IPersonaPreviewScene> PreviewScene) override;`
- L21 _public prototype_ `virtual void DebugDrawSimulation(const IClothingSimulationInterface* Simulation, USkeletalMeshComponent* OwnerComponent, FPrimitiveDrawInterface* PDI) override;`
- L22 _public prototype_ `virtual void DebugDrawSimulationTexts(const IClothingSimulationInterface* Simulation, USkeletalMeshComponent* OwnerComponent, FCanvas* Canvas, const FSceneView* SceneView) override;`
- L27 _private prototype_ `virtual FName GetSectionName() const;` — Return the name of the menu section.
- L30 _private prototype_ `virtual FText GetSectionHeadingText() const;` — Return the heading text of the menu section.
- L33 _private prototype_ `virtual const FClothVisualizationNoGC* GetClothVisualization(const IClothingSimulationInterface* Simulation) const;` — Return the visualization object for the specified simulation.
- L36 _private prototype_ `bool ShouldDisableSimulation() const;` — Return whether or not - given the current enabled options - the simulation should be disabled.
- L38 _private prototype_ `void ShowClothSections(USkeletalMeshComponent* MeshComponent, bool bIsClothSectionsVisible) const;` — Show/hide all cloth sections for the specified mesh compoment.
- L42 _private member_ `TBitArray<> Flags;` — Flags used to store the checked status for the visualization options.

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace Chaos`
