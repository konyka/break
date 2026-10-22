# Plugins / CineCameraRigsEditor

- module root: `Plugins/Experimental/CineCameraRigs/Source/CineCameraRigsEditor`
- headers: 3; symbols: 90
- symbol kinds: class=4, function=8, member=18, namespace=1, prototype=59
- PrivateDependencyModuleNames: CineCameraRigs, CinematicCamera, ComponentVisualizers, Core, CoreUObject, DetailCustomizations, Engine, InputCore, PlacementMode, PropertyEditor, Slate, SlateCore, UnrealEd
- PrivateIncludePathModuleNames: 
- PublicDependencyModuleNames: 

### `Plugins/Experimental/CineCameraRigs/Source/CineCameraRigsEditor/Private/CineCameraRigRailDetails.h` (Private)


#### class `FCineCameraRigRailDetails`  
`class FCineCameraRigRailDetails : public IDetailCustomization`  
_L18-60_
- inherits: `IDetailCustomization`
- desc: Implements a details view customization for the ACineCameraRigRail
- L21 _public function_ `static TSharedRef<IDetailCustomization> MakeInstance()`
- L26 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`
- L28 _public member_ `TOptional<float> CurrentPositionValue = 1.0f;`
- L31 _private member_ `TWeakObjectPtr<ACineCameraRigRail> RigRailActorPtr;`
- L33 _private prototype_ `TOptional<float> GetAbsolutePosition() const;`
- L35 _private prototype_ `TOptional<float> GetAbsolutePositionSliderMinValue() const;`
- L36 _private prototype_ `TOptional<float> GetAbsolutePositionSliderMaxValue() const;`
- L37 _private prototype_ `void OnBeginAbsolutePositionSliderMovement();`
- L38 _private prototype_ `void OnEndAbsolutePositionSliderMovement(float NewValue);`
- L39 _private prototype_ `void OnAbsolutePositionCommitted(float NewValue, ETextCommit::Type CommitType);`
- L40 _private prototype_ `void OnAbsolutePositionChanged(float NewValue);`
- L42 _private member_ `bool bAbsolutePositionSliderStartedTransaction = false;`
- L44 _private prototype_ `ECheckBoxState IsAttachOptionChecked(TArray<TSharedRef<IPropertyHandle>> PropertyHandles) const;`
- L45 _private prototype_ `void OnAttachOptionChanged(ECheckBoxState NewState, TArray<TSharedRef<IPropertyHandle>> PropertyHandles);`
- L47 _private member_ `TSharedPtr<IPropertyHandle> DriveModeHandle;`
- L48 _private prototype_ `ECineCameraRigRailDriveMode GetDriveMode() const;`
- L50 _private prototype_ `void OnUseAbsolutePositionChanged(ECheckBoxState NewState, TSharedRef<IPropertyHandle> PropertyHandle);`
- L52 _private prototype_ `void CustomizeRailControlCategory(IDetailLayoutBuilder& DetailBuilder);`
- L53 _private prototype_ `void CustomizeSplineVisualizationCategory(IDetailLayoutBuilder& DetailBuilder);`
- L54 _private prototype_ `void CustomizeAttachmentCategory(IDetailLayoutBuilder& DetailBuilder);`
- L55 _private prototype_ `void CustomizeDriveModeCategory(IDetailLayoutBuilder& DetailBuilder);`
- L56 _private prototype_ `void HideExtraCategories(IDetailLayoutBuilder& DetailBuilder);`
- L58 _private prototype_ `ECheckBoxState IsAttachRotationOptionChecked(TArray<TSharedRef<IPropertyHandle>> PropertyHandles) const;`
- L59 _private prototype_ `void OnRotationAxisAttachmentChanged(ECheckBoxState NewState, TSharedRef<IPropertyHandle> PropertyHandle);`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace ETextCommit`

### `Plugins/Experimental/CineCameraRigs/Source/CineCameraRigsEditor/Private/CineSplineComponentVisualizer.h` (Private)


#### class `FCineSplineComponentVisualizer`  
`class FCineSplineComponentVisualizer : public FSplineComponentVisualizer`  
_L19-53_
- inherits: `FSplineComponentVisualizer`
- L22 _public prototype_ `FCineSplineComponentVisualizer();`
- L23 _public prototype_ `virtual ~FCineSplineComponentVisualizer();`
- L26 _public prototype_ `virtual void OnRegister() override;`
- L27 _public prototype_ `virtual void DrawVisualizationHUD(const UActorComponent* Component, const FViewport* Viewport, const FSceneView* View, FCanvas* Canvas) override;`
- L28 _public prototype_ `virtual void DrawVisualization(const UActorComponent* Component, const FSceneView* View, FPrimitiveDrawInterface* PDI) override;`
- L29 _public prototype_ `virtual void GenerateContextMenuSections(FMenuBuilder& InMenuBuilder) const;`
- L30 _public prototype_ `virtual bool HandleInputDelta(FEditorViewportClient* ViewportClient, FViewport* Viewport, FVector& DeltaTranslate, FRotator& DeltaRotate, FVector& DeltaScale) override;`
- L31 _public prototype_ `virtual bool GetCustomInputCoordinateSystem(const FEditorViewportClient* ViewportClient, FMatrix& OutMatrix) const override;`
- L34 _protected member_ `bool bManipulatePointRotation;`
- L36 _protected prototype_ `bool TransformPointRotation(const FRotator& DeltaRotate);`
- L38 _protected prototype_ `void OnSetVisualizeNormalizedPosition();`
- L39 _protected prototype_ `bool IsVisualizeNormalizedPosition() const;`
- L40 _protected prototype_ `void OnSetVisualizeSplineLength();`
- L41 _protected prototype_ `bool IsVisualizeSplineLength() const;`
- L42 _protected prototype_ `void OnSetVisualizePointRotation();`
- L43 _protected prototype_ `bool IsVisualizePointRotation() const;`
- L44 _protected prototype_ `void OnSetManipulatePointRotation();`
- L45 _protected prototype_ `bool IsManipulatePointRotation() const;`
- L47 _protected prototype_ `void OnSetMetadataTangent(ECineSplineMetadataTangentType TangentType);`
- L48 _protected prototype_ `bool IsMetadataTangent(ECineSplineMetadataTangentType TangentType);`
- L49 _protected prototype_ `void GenerateMetadataTangentTypeSubMenu(FMenuBuilder& MenuBuilder) const;`
- L51 _protected member_ `TSharedPtr<FUICommandList> CineSplineComponentVisualizerActions;`

### `Plugins/Experimental/CineCameraRigs/Source/CineCameraRigsEditor/Private/CineSplineMetadataDetails.h` (Private)


#### class `UCineSplineMetadataDetailsFactory`  
`class UCineSplineMetadataDetailsFactory : public USplineMetadataDetailsFactoryBase`  
_L20-27_
- reflection: `UCLASS()`
- inherits: `USplineMetadataDetailsFactoryBase`
- L25 _public prototype_ `virtual TSharedPtr<ISplineMetadataDetails> Create() override;`
- L26 _public prototype_ `virtual UClass* GetMetadataClass() const override;`

#### class `FCineSplineMetadataDetails`  
`class FCineSplineMetadataDetails : public ISplineMetadataDetails, public TSharedFromThis<FCineSplineMetadataDetails>`  
_L29-85_
- inherits: `ISplineMetadataDetails,TSharedFromThis<FCineSplineMetadataDetails>`
- L32 _public prototype_ `virtual ~FCineSplineMetadataDetails() = default;`
- L33 _public function_ `virtual FName GetName() const override`
- L34 _public prototype_ `virtual FText GetDisplayName() const override;`
- L35 _public prototype_ `virtual void Update(USplineComponent* InSplineComponent, const TSet<int32>& InSelectedKeys) override;`
- L36 _public prototype_ `virtual void GenerateChildContent(IDetailGroup& InGroup) override;`
- L38 _public member_ `TOptional<float> AbsolutePositionValue;`
- L39 _public member_ `TOptional<float> FocalLengthValue;`
- L40 _public member_ `TOptional<float> ApertureValue;`
- L41 _public member_ `TOptional<float> FocusDistanceValue;`
- L42 _public member_ `TOptional<FQuat> PointRotationValue;`
- L43 _public member_ `TOptional<ECineSplineMetadataTangentType> InterpTypeValue;`
- L45 _public member_ `USplineComponent* SplineComp = nullptr;`
- L46 _public member_ `TSet<int32> SelectedKeys;`
- L47 _public member_ `int32 SliderEnterCount = 0;`
- L50 _private prototype_ `void OnBeginSliderMovement();`
- L51 _private prototype_ `void OnEndSliderMovement(float NewValue);`
- L53 _private function_ `EVisibility IsEnabled() const`
- L54 _private function_ `bool IsOnePointSelected() const`
- L56 _private function_ `TOptional<float> GetAbsolutePosition() const`
- L57 _private prototype_ `void OnSetAbsolutePosition(float NewValue, ETextCommit::Type CommitInfo);`
- L59 _private function_ `TOptional<float> GetFocalLength() const`
- L60 _private prototype_ `void OnSetFocalLength(float NewValue, ETextCommit::Type CommitInfo);`
- L62 _private function_ `TOptional<float> GetAperture() const`
- L63 _private prototype_ `void OnSetAperture(float NewValue, ETextCommit::Type CommitInfo);`
- L65 _private function_ `TOptional<float> GetFocusDistance() const`
- L66 _private prototype_ `void OnSetFocusDistance(float NewValue, ETextCommit::Type CommitInfo);`
- L68 _private prototype_ `TOptional<float> GetRotation(EAxis::Type Axis) const;`
- L69 _private prototype_ `void OnSetRotation(float NewValue, ETextCommit::Type CommitInfo, EAxis::Type Axis);`
- L71 _private prototype_ `FText GetInterpType() const;`
- L72 _private prototype_ `void OnInterpTypeChanged(TSharedPtr<FString> NewValue, ESelectInfo::Type SelectInfo);`
- L74 _private prototype_ `TSharedRef<SWidget> OnGenerateInterpTypeComboWidget(TSharedPtr<FString> InComboString);`
- L75 _private prototype_ `void OnInterpTypeComboWidgetOpened();`
- L76 _private prototype_ `void UpdateInterpTypes();`
- L78 _private prototype_ `UCineSplineMetadata* GetMetadata() const;`
- L81 _private member_ `TUniquePtr<FScopedTransaction> EditSliderValueTransaction;`
- L83 _private member_ `TArray<TSharedPtr<FString>> InterpTypes;`
- L84 _private member_ `TSharedPtr<SComboBox<TSharedPtr<FString>>> InterpTypeComboBox;`
