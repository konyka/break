# Plugins / AvalancheLevelViewport

- module root: `Plugins/VirtualProduction/Avalanche/Source/AvalancheLevelViewport`
- headers: 31; symbols: 968
- symbol kinds: class=30, delegate=3, enum=1, enumerator=4, function=98, member=230, namespace=13, prototype=570, struct=10, variable=9
- PrivateDependencyModuleNames: ApplicationCore, Avalanche, AvalancheComponentVisualizers, AvalancheEditorCore, AvalancheFunctionalTest, AvalancheInteractiveTools, AvalancheViewport, CinematicCamera, CustomDetailsView, EditorFramework, FunctionalTesting, InputCore, LevelEditor, Projects, PropertyAnimatorCore, PropertyEditor, ToolMenus, TypedElementRuntime
- PublicDependencyModuleNames: AvalancheViewport, Core, CoreUObject, Engine, Slate, SlateCore, UnrealEd
- PublicIncludePathModuleNames: AvalancheInteractiveTools, SceneOutliner

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheLevelViewport/Private/AvaLevelViewportModule.h` (Private)


#### class `FAvaLevelViewportModule`  
`class FAvaLevelViewportModule : public IModuleInterface`  
_L18-31_
- inherits: `IModuleInterface`
- L21 _private prototype_ `virtual void StartupModule() override;`
- L22 _private prototype_ `virtual void ShutdownModule() override;`
- L25 _private prototype_ `void RegisterMenus();`
- L27 _private member_ `FDelegateHandle AvaLevelViewportClientCasterDelegateHandle;`
- L30 _private member_ `TSharedPtr<FAvaViewportCameraHistory> ViewportCameraHistory;` — Handles viewport camera undo/redo

#### Free symbols / members of external scopes

- L11 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(AvaLevelViewportLog, Log, All);`
- L11 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(AvaLevelViewportLog, Log, All);`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace AvaLevelViewport` (scope `UE`)
- L13 _namespace_ `namespace Internal` (scope `UE::AvaLevelViewport`)
- L15 _variable_ `static FName StatusBarMenuName = TEXT("Ava` (scope `UE::AvaLevelViewport::Internal`)

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheLevelViewport/Private/AvaLevelViewportStyle.h` (Private)


#### class `FAvaLevelViewportStyle`  
`class FAvaLevelViewportStyle final : public FSlateStyleSet`  
_L7-18_
- inherits: `FSlateStyleSet`
- L10 _public function_ `static FAvaLevelViewportStyle& Get()`
- L16 _public prototype_ `FAvaLevelViewportStyle();`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheLevelViewport/Private/AvaLevelViewportToolbarContext.h` (Private)


#### class `UAvaLevelViewportToolbarContext`  
`class UAvaLevelViewportToolbarContext : public UObject`  
_L12-25_
- reflection: `UCLASS()`
- inherits: `UObject`
- L17 _public prototype_ `UAvaLevelViewportToolbarContext() = default;`
- L19 _public function_ `void SetViewport(const TSharedPtr<SAvaLevelViewport>& InViewport)`
- L21 _public function_ `TSharedPtr<SAvaLevelViewport> GetViewport() const`
- L24 _private member_ `TWeakPtr<SAvaLevelViewport> ViewportWeak;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheLevelViewport/Private/AvaViewportCameraHistory.h` (Private)


#### class `FAvaViewportCameraHistory`  
`class FAvaViewportCameraHistory : public TSharedFromThis<FAvaViewportCameraHistory>`  
_L22-66_
- inherits: `TSharedFromThis<FAvaViewportCameraHistory>`
- desc: Handles undo/redo for camera viewport movement.
- L26 _public prototype_ `FAvaViewportCameraHistory();`
- L27 _public prototype_ `~FAvaViewportCameraHistory();`
- L29 _public prototype_ `void BindCommands();`
- L30 _public prototype_ `void UnbindCommands();`
- L33 _private prototype_ `void MapOpened(const FString& InMapName, bool bIsTemplate);`
- L34 _private prototype_ `void PostEngineInit();`
- L36 _private prototype_ `void Reset();`
- L38 _private prototype_ `void BindCameraTransformDelegates();`
- L39 _private prototype_ `void UnbindCameraTransformDelegates();`
- L41 _private prototype_ `void OnBeginCameraTransform(UObject& InCameraObject);`
- L42 _private prototype_ `void OnEndCameraTransform(UObject& InCameraObject);`
- L44 _private prototype_ `void ExecuteCameraTransformUndo();`
- L45 _private prototype_ `void ExecuteCameraTransformRedo();`
- L47 _private prototype_ `void NotifyUndo();`
- L48 _private prototype_ `void NotifyRedo();`
- L49 _private prototype_ `void Notify(const FText& InText);`
- L52 _private member_ `FDelegateHandle OnBeginCameraTransformHandle;`
- L53 _private member_ `FDelegateHandle OnEndCameraTransformHandle;`
- L56 _private member_ `TSharedPtr<SNotificationItem> UndoRedoNotificationItem;` — The notification item to use for undo/redo
- L59 _private member_ `TArray<TPair<TWeakObjectPtr<AActor>, FTransform>, TFixedAllocator<UE::AvaEditor::Internal::CameraUndoHistoryCapacity>> CameraTransformHistory;` — Stores previous camera transforms (as camera, transform pair) for undo/redo, if any
- L62 _private member_ `int32 CameraTransformHistoryIndex = INDEX_NONE;` — Stores current position in the camera transform history, to allow redo of actions ahead of this position
- L65 _private member_ `int32 CameraTransformHistoryHeadIndex = 1;` — Stores current position of the array "end", needed due to circular storage

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace AvaEditor` (scope `UE`)
- L12 _namespace_ `namespace Internal` (scope `UE::AvaEditor`)
- L14 _variable_ `static constexpr int32 CameraUndoHistoryCapacity = 64;` (scope `UE::AvaEditor::Internal`)

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheLevelViewport/Private/ColorPicker/AvaLevelColorPicker.h` (Private)


#### class `FAvaLevelColorPicker`  
`class FAvaLevelColorPicker`  
_L11-36_
- L14 _public prototype_ `FAvaLevelColorPicker();`
- L15 _public prototype_ `~FAvaLevelColorPicker();`
- L17 _public prototype_ `void SetToolkitHost(const TSharedRef<IToolkitHost>& InToolkitHost);`
- L19 _public prototype_ `void OnColorSelected(const FAvaColorChangeData& InNewColorData);`
- L21 _public function_ `const FAvaColorChangeData& GetLastColorData() const`
- L27 _private prototype_ `void ApplyColorToSelections(const FAvaColorChangeData& InNewColorData);`
- L29 _private prototype_ `void UpdateFromSelection(UObject* InSelection);`
- L31 _private member_ `TWeakPtr<IToolkitHost> ToolkitHostWeak;`
- L33 _private member_ `FAvaColorChangeData LastColorData;`
- L35 _private member_ `FDelegateHandle OnSelectionChangedHandle;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheLevelViewport/Private/Customizations/AvaLevelViewportCameraCustomization.h` (Private)


#### class `FAvaLevelViewportCameraCustomization`  
`class FAvaLevelViewportCameraCustomization : public TSharedFromThis<FAvaLevelViewportCameraCustomization>`  
_L9-20_
- inherits: `TSharedFromThis<FAvaLevelViewportCameraCustomization>`
- L12 _public prototype_ `static const TSharedRef<FAvaLevelViewportCameraCustomization>& Get();`
- L14 _public prototype_ `void Register();`
- L16 _public prototype_ `void Unregister();`
- L19 _protected prototype_ `void ExtendLevelViewportToolbar(UToolMenu* InToolMenu);`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheLevelViewport/Private/Customizations/AvaLevelViewportComponentTransformDetails.h` (Private)


#### enum `EAvaLevelViewportTransformFieldType`  
`enum class EAvaLevelViewportTransformFieldType : uint8`  
_L26-32_
- L28 _public enumerator_ `Location`
- L29 _public enumerator_ `Rotation`
- L30 _public enumerator_ `Scale`
- L31 _public enumerator_ `All`

#### class `FAvaLevelViewportComponentTransformDetails`  
`class FAvaLevelViewportComponentTransformDetails : public TSharedFromThis<FAvaLevelViewportComponentTransformDetails>, public IDetailCustomNodeBuilder, public TNumericUnitTypeInterface<FVector::FReal>`  
_L39-415_
- inherits: `TSharedFromThis<FAvaLevelViewportComponentTransformDetails>,IDetailCustomNodeBuilder,TNumericUnitTypeInterface<FVector::FReal>`
- desc: Manages the Transform section of a details view
- L43 _public prototype_ `FAvaLevelViewportComponentTransformDetails(TSharedPtr<FAvaLevelViewportClient> InAvaViewportClient);`
- L46 _public function_ `static bool IsUseSelectionAsParent()`
- L51 _public prototype_ `void CacheTransform();` — Caches the representation of the actor transform for the user input boxes
- L53 _public function_ `virtual void GenerateHeaderRowContent(FDetailWidgetRow& NodeRow) override`
- L54 _public function_ `virtual void GenerateChildContent(IDetailChildrenBuilder& ChildrenBuilder) override`
- L55 _public function_ `virtual bool RequiresTick() const override`
- L56 _public function_ `virtual FName GetName() const override`
- L57 _public function_ `virtual bool InitiallyCollapsed() const override`
- L58 _public prototype_ `virtual void Tick(float DeltaTime) override;`
- L59 _public function_ `virtual void SetOnRebuildChildren(FSimpleDelegate OnRebuildChildren) override`
- L61 _public prototype_ `void OnSelectionChanged(const TArray<UObject*>& InSelectedObjects);`
- L62 _public prototype_ `void OnSelectionSetChanged(const UTypedElementSelectionSet* InSelectionSet);`
- L64 _public prototype_ `TSharedPtr<SWidget> GetTransformBody();`
- L65 _public prototype_ `TSharedPtr<SWidget> GetRotationBody();`
- L66 _public prototype_ `TSharedPtr<SWidget> GetScaleBody();`
- L67 _public prototype_ `TSharedPtr<SWidget> GetOptionsHeader();`
- L68 _public prototype_ `TSharedPtr<SWidget> GetOptionsBody();`
- L69 _public prototype_ `TSharedRef<SWidget> GetPreserveScaleRatioWidget();`
- L71 _public function_ `int32 GetSelectedActorCount() const`
- L74 _public function_ `TConstArrayView<TWeakObjectPtr<UObject>> GetSelectedObjects() const` — Returns the cached list of selected objects.
- L76 _public prototype_ `void SetTransform(EAvaLevelViewportTransformFieldType TransformField, const FVector& NewValue);`
- L78 _public member_ `static FOnUseSelectionAsParentChanged OnUseSelectionAsParentChangedEvent;`
- L81 _public prototype_ `void OnLocationResetClicked();` — Called when the "Reset to Default" button for the location has been clicked
- L84 _public prototype_ `void OnRotationResetClicked();` — Called when the "Reset to Default" button for the rotation has been clicked
- L87 _public prototype_ `void OnScaleResetClicked();` — Called when the "Reset to Default" button for the scale has been clicked
- L89 _public function_ `TConstArrayView<TSharedPtr<IPropertyHandle>> GetPropertyHandles() const`
- L94 _private prototype_ `bool GetIsEnabled() const;` — @return Whether the transform details panel should be enabled (editable) or not (read-only / greyed out)
- L97 _private prototype_ `FVector GetAxisFilteredVector(EAxisList::Type Axis, const FVector& NewValue, const FVector& OldValue);` — Sets a vector based on two source vectors and an axis list
- L100 _private prototype_ `void OnBeginChange(EAvaLevelViewportTransformFieldType TransformField);` — Called when a change starts (direct ui commit or slider begin)
- L103 _private prototype_ `void OnEndChange(EAvaLevelViewportTransformFieldType TransformField, EAxisList::Type Axis);` — Called when a change ends (direct ui commit or slider end)
- L114 _private prototype_ `void OnSetTransform(EAvaLevelViewportTransformFieldType TransformField, EAxisList::Type Axis, FVector NewValue, bool bMirror, bool bCommitted);` — Sets the selected object(s) axis to passed in value @param TransformField	The field (location/rotation/scale) to modify @param Axis				Bitfield of which axis to set, can be multiple @param NewValue			The new vector values, it only uses the ones with specified axis @param bMirror			If true, set the value to it's inverse instead of using NewValue @param bCommitted		True if the value was committed, false is the value comes from the slider
- L117 _private prototype_ `void OnSetTransformSelectionParent(EAvaLevelViewportTransformFieldType TransformField, EAxisList::Type Axis, FVector NewValue, bool bMirror, bool bCommitted);` — Transform components based the selection transform, not the component transform.
- L128 _private prototype_ `void OnSetTransformAxis(FVector::FReal NewValue, ETextCommit::Type CommitInfo, EAvaLevelViewportTransformFieldType TransformField, EAxisList::Type Axis, bool bCommitted);` — Sets a single axis value, called from UI @param TransformField	The field (location/rotation/scale) to modify @param NewValue			The new translation value @param CommitInfo		Whether or not this was committed from pressing enter or losing focus @param Axis				Bitfield of which axis to set, can be multiple @param bCommitted		true if the value was committed, false is the value comes from the slider
- L139 _private prototype_ `void OnSetTransformAxisFloat(float NewValue, ETextCommit::Type CommitInfo, EAvaLevelViewportTransformFieldType TransformField, EAxisList::Type Axis, bool bCommitted);` — Sets a single axis float value, called from UI @param TransformField	The field (location/rotation/scale) to modify @param NewValue			The new translation value @param CommitInfo		Whether or not this was committed from pressing enter or losing focus @param Axis				Bitfield of which axis to set, can be multiple @param bCommitted		true if the value was committed, false is the value comes from the slider
- L146 _private prototype_ `void BeginSliderTransaction(FText ActorTransaction, FText ComponentTransaction) const;` — Helper to begin a new transaction for a slider interaction. @param ActorTransaction		The name to give the transaction when changing an actor transform. @param ComponentTransaction	The name to give the transaction when directly editing a component transform.
- L149 _private prototype_ `void OnBeginRotationSlider();` — Called when the one of the axis sliders for object rotation begins to change for the first time
- L152 _private prototype_ `void OnEndRotationSlider(float NewValue);` — Called when the one of the axis sliders for object rotation is released
- L155 _private prototype_ `void OnBeginLocationSlider();` — Called when one of the axis sliders for object location begins to change
- L158 _private prototype_ `void OnEndLocationSlider(FVector::FReal NewValue);` — Called when one of the axis sliders for object location is released
- L161 _private prototype_ `void OnBeginScaleSlider();` — Called when one of the axis sliders for object scale begins to change
- L164 _private prototype_ `void OnEndScaleSlider(FVector::FReal NewValue);` — Called when one of the axis sliders for object scale is released
- L167 _private prototype_ `const FSlateBrush* GetPreserveScaleRatioImage() const;` — @return Icon to use in the preserve scale ratio check box
- L170 _private prototype_ `ECheckBoxState IsPreserveScaleRatioChecked() const;` — @return The state of the preserve scale ratio checkbox
- L175 _private prototype_ `void OnPreserveScaleRatioToggled(ECheckBoxState NewState);` — Called when the preserve scale ratio checkbox is toggled
- L183 _private prototype_ `TSharedRef<SWidget> BuildTransformFieldLabel(EAvaLevelViewportTransformFieldType TransformField);` — Builds a transform field label @param TransformField The field to build the label for @return The label widget
- L191 _private prototype_ `FText GetTransformFieldText(EAvaLevelViewportTransformFieldType TransformField) const;` — Gets display text for a transform field @param TransformField	The field to get the text for @return The text label for TransformField
- L196 _private prototype_ `FText GetLocationText() const;` — @return the text to display for translation
- L201 _private prototype_ `FText GetRotationText() const;` — @return the text to display for rotation
- L206 _private prototype_ `FText GetScaleText() const;` — @return the text to display for scale
- L214 _private prototype_ `void OnSetAbsoluteTransform(EAvaLevelViewportTransformFieldType TransformField, bool bAbsoluteEnabled);` — Sets relative transform on the specified field @param TransformField the field that should be set to relative @param bAbsoluteEnabled true to absolute, false for relative
- L217 _private prototype_ `bool IsAbsoluteTransformChecked(EAvaLevelViewportTransformFieldType TransformField, bool bAbsoluteEnabled=true) const;` — @return true if Absolute flag of transform type matches passed in bCheckAbsolute
- L220 _private prototype_ `bool OnCanCopy(EAvaLevelViewportTransformFieldType TransformField) const;` — @return true of copy is enabled for the specified field
- L225 _private prototype_ `void OnCopy(EAvaLevelViewportTransformFieldType TransformField);` — Copies the specified transform field to the clipboard
- L230 _private prototype_ `void OnPaste(EAvaLevelViewportTransformFieldType TransformField);` — Pastes the specified transform field from the clipboard
- L235 _private prototype_ `FUIAction CreateCopyAction(EAvaLevelViewportTransformFieldType TransformField) const;` — Creates a UI action for copying a specified transform field
- L240 _private prototype_ `FUIAction CreatePasteAction(EAvaLevelViewportTransformFieldType TransformField) const;` — Creates a UI action for pasting a specified transform field
- L243 _private prototype_ `void ExtendXScaleContextMenu(FMenuBuilder& MenuBuilder);` — Extend the context menu for the X component
- L245 _private prototype_ `void ExtendYScaleContextMenu(FMenuBuilder& MenuBuilder);` — Extend the context menu for the Y component
- L247 _private prototype_ `void ExtendZScaleContextMenu(FMenuBuilder& MenuBuilder);` — Extend the context menu for the Z component
- L250 _private prototype_ `void OnXScaleMirrored();` — Called when the X axis scale is mirrored
- L252 _private prototype_ `void OnYScaleMirrored();` — Called when the Y axis scale is mirrored
- L254 _private prototype_ `void OnZScaleMirrored();` — Called when the Z axis scale is mirrored
- L257 _private function_ `TOptional<FVector::FReal> GetLocationX() const` — @return The X component of location
- L259 _private function_ `TOptional<FVector::FReal> GetLocationY() const` — @return The Y component of location
- L261 _private function_ `TOptional<FVector::FReal> GetLocationZ() const` — @return The Z component of location
- L263 _private prototype_ `bool GetLocationResetVisibility() const;` — @return The visibility of the "Reset to Default" button for the location component
- L266 _private function_ `TOptional<float> GetRotationX() const` — @return The X component of rotation
- L268 _private function_ `TOptional<float> GetRotationY() const` — @return The Y component of rotation
- L270 _private function_ `TOptional<float> GetRotationZ() const` — @return The Z component of rotation
- L272 _private prototype_ `bool GetRotationResetVisibility() const;` — @return The visibility of the "Reset to Default" button for the rotation component
- L275 _private function_ `TOptional<FVector::FReal> GetScaleX() const` — @return The X component of scale
- L277 _private function_ `TOptional<FVector::FReal> GetScaleY() const` — @return The Y component of scale
- L279 _private function_ `TOptional<FVector::FReal> GetScaleZ() const` — @return The Z component of scale
- L281 _private prototype_ `bool GetScaleResetVisibility() const;` — @return The visibility of the "Reset to Default" button for the scale component
- L284 _private prototype_ `void CacheCommonLocationUnits();` — Cache a single unit to display all location components in
- L287 _private prototype_ `void GeneratePropertyHandles();` — Generate a property handles from a the scene component properties.
- L290 _private prototype_ `void UpdatePropertyHandlesObjects(TArray<UObject*> NewSceneComponents);` — Update the outer objects of the property handles generated from this transform.
- L293 _private prototype_ `void OnObjectsReplaced(const TMap<UObject*, UObject*>& ReplacementMap);` — Delegate called when the OnObjectsReplaced is broadcast by the engine.
- L295 _private function_ `ECheckBoxState IsUseSelectionAsParentChecked() const`
- L296 _private prototype_ `void OnUseSelectionAsParentChanged(ECheckBoxState NewState);`
- L298 _private prototype_ `void OnUseSelectionAsParentChanged(bool bNewValue);`
- L300 _private prototype_ `void OnEnginePreExit();`
- L339 _private member_ `FSelectedActorInfo SelectedActorInfo;`
- L342 _private member_ `TArray< TWeakObjectPtr<UObject> > SelectedObjects;` — Copy of selected actor references in the details view
- L345 _private member_ `FOptionalVector<FVector::FReal> CachedLocation;` — Cache translation value of the selected set
- L348 _private member_ `FOptionalVector<float> CachedRotation;` — Cache rotation value of the selected set
- L351 _private member_ `FOptionalVector<FVector::FReal> CachedScale;` — Cache scale value of the selected set
- L354 _private member_ `FNotifyHook* NotifyHook;` — Notify hook to use
- L357 _private member_ `TMap< UObject*, FRotator > ObjectToRelativeRotationMap;` — Mapping from object to relative rotation values which are not affected by Quat->Rotator conversions during transform calculations
- L360 _private member_ `bool bAbsoluteLocation;` — Whether or not we are in absolute translation mode
- L363 _private member_ `bool bAbsoluteRotation;` — Whether or not we are in absolute rotation mode
- L366 _private member_ `bool bAbsoluteScale;` — Whether or not we are in absolute scale mode
- L369 _private member_ `bool bPreserveScaleRatio;` — Whether or not to preserve scale ratios
- L372 _private member_ `FVector SliderScaleRatio;` — Scale ratio to use when we are using the sliders with bPreserveScaleRatio set.
- L375 _private member_ `bool bEditingRotationInUI;` — Flag to indicate we are currently editing the rotation in the UI, so we should rely on the cached value in objectToRelativeRotationMap, not the value from the object
- L378 _private member_ `bool bIsSliderTransaction;` — Flag to indicate we are currently performing a slider transaction
- L381 _private member_ `uint8 DisplayedFieldType;` — Bitmask to indicate which fields should be hidden (if any)
- L384 _private member_ `TSharedPtr<IPropertyRowGenerator> PropertyRowGenerator;` — Used to generated property handles.
- L387 _private member_ `TArray<TSharedPtr<IDetailTreeNode>> TreeNodes;` — Tree nodes for the property handles.
- L390 _private member_ `TArray<TSharedPtr<IPropertyHandle>> PropertyHandles;` — Holds this transform's property handles.
- L393 _private member_ `TArray<TWeakObjectPtr<UObject>> CachedHandlesObjects;` — Holds the property handles' outer objects. Used to update the handles' objects when the actor construction script runs.
- L396 _private member_ `TWeakPtr<FAvaLevelViewportClient> AvaViewportClientWeak;` — Link to the viewport client for which this is displaying details
- L399 _private member_ `static bool bUseSelectionAsParent;` — If true, use the multi-select as an ad-hoc parent
- L400 _private member_ `bool bLastUseSelectionAsParent;`
- L403 _private member_ `bool bCanUseSelectionAsParent;` — If true, we can use the multi-select as a parent
- L405 _private member_ `TSharedPtr<SBox> TransformBox;`
- L406 _private member_ `TSharedPtr<SBox> RotationBox;`
- L407 _private member_ `TSharedPtr<SBox> ScaleBox;`
- L408 _private member_ `TArray<TWeakObjectPtr<UObject>> ModifiedObjects;`
- L409 _private member_ `TMap<USceneComponent*, FVector> OriginalLocations;`
- L410 _private member_ `TMap<USceneComponent*, FRotator> OriginalRotations;`
- L411 _private member_ `TMap<USceneComponent*, FVector> OriginalScales;`
- L414 _private member_ `TWeakObjectPtr<UTypedElementSelectionSet> EditorSelectionSetWeak;` — Editor Selection Set used to listen to Selection Changes

#### struct `FAvaLevelViewportComponentTransformDetails::FOptionalVector`  
`template <typename NumericType> struct FOptionalVector`  
_L305-337_
- desc: A vector where it may optionally be unset
- L310 _public function_ `void Set(const FVector& InVec)` — Sets the value from an FVector
- L320 _public function_ `void Set(const FRotator& InRot)` — Sets the value from an FRotator
- L328 _public function_ `bool IsSet() const` — @return Whether or not the value is set
- L334 _public member_ `TOptional<NumericType> X;`
- L335 _public member_ `TOptional<NumericType> Y;`
- L336 _public member_ `TOptional<NumericType> Z;`

#### Free symbols / members of external scopes

- L34 _delegate_ `DECLARE_EVENT_OneParam(FAvaLevelViewportComponentTransformDetails, FOnUseSelectionAsParentChanged, bool);`
- L34 _prototype_ `DECLARE_EVENT_OneParam(FAvaLevelViewportComponentTransformDetails, FOnUseSelectionAsParentChanged, bool);`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheLevelViewport/Private/SAvaLevelViewport.h` (Private)


#### class `SAvaLevelViewport`  
`class SAvaLevelViewport : public SLevelViewport, public FSelfRegisteringEditorUndoClient`  
_L39-266_
- inherits: `SLevelViewport,FSelfRegisteringEditorUndoClient`
- L44 _public function_ `SLATE_DECLARE_WIDGET(SAvaLevelViewport, SLevelViewport) SLATE_BEGIN_ARGS(SAvaLevelViewport)`
- L47 _public prototype_ `SLATE_ARGUMENT(TWeakPtr<ILevelEditor>, ParentLevelEditor) SLATE_ARGUMENT(TSharedPtr<SAvaLevelViewportFrame>, ViewportFrame) SLATE_END_ARGS() virtual ~SAvaLevelViewport() override;`
- L53 _public prototype_ `void Construct(const FArguments& InArgs, const FAssetEditorViewportConstructionArgs& InViewportArgs);`
- L57 _public prototype_ `virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;` — Tick is private in SLevelViewport ?!
- L62 _public prototype_ `virtual void BindCommands() override;`
- L63 _public prototype_ `virtual FName RegisterViewportToolbar() const override;`
- L64 _public prototype_ `virtual void PopulateViewportOverlays(TSharedRef<SOverlay> Overlay) override;`
- L67 _public prototype_ `TSharedPtr<SAvaLevelViewportFrame> GetAvaLevelViewportFrame() const;`
- L68 _public prototype_ `TSharedPtr<FAvaLevelViewportClient> GetAvaLevelViewportClient() const;`
- L70 _public function_ `TSharedPtr<SAvaLevelViewportPixelGrid> GetPixelGrid() const`
- L71 _public function_ `TSharedPtr<SAvaLevelViewportScreenGrid> GetScreenGrid() const`
- L72 _public function_ `TSharedPtr<SAvaLevelViewportSnapIndicators> GetSnapIndicators() const`
- L74 _public function_ `TConstArrayView<TSharedPtr<SAvaLevelViewportGuide>> GetGuides() const`
- L75 _public prototype_ `TSharedPtr<SAvaLevelViewportGuide> AddGuide(EOrientation InOrientation, float InOffsetFraction, bool bInSaveGuides = true);`
- L76 _public prototype_ `bool RemoveGuide(TSharedPtr<SAvaLevelViewportGuide> InGuidetoRemove);` — TSharedPtr<SAvaLevelViewportGuide> AddGuide(EOrientation InOrientation, float InOffsetFraction, bool bInSaveGuides = true);   0 = left/top. 1 = right/bottom/
- L77 _public prototype_ `void SaveGuides();`
- L79 _public prototype_ `bool CanToggleOverlay() const;`
- L80 _public prototype_ `void ExecuteToggleOverlay();`
- L82 _public prototype_ `bool CanToggleSafeFrames() const;`
- L83 _public prototype_ `void ExecuteToggleSafeFrames();`
- L85 _public prototype_ `bool CanToggleBoundingBox() const;`
- L86 _public prototype_ `void ExecuteToggleBoundingBox();`
- L88 _public prototype_ `bool CanToggleGrid() const;`
- L89 _public prototype_ `void ExecuteToggleGrid();`
- L91 _public prototype_ `bool CanToggleGridAlwaysVisible() const;`
- L92 _public prototype_ `bool IsGridAlwaysVisible() const;`
- L93 _public prototype_ `void ExecuteToggleGridAlwaysVisible();`
- L95 _public prototype_ `bool CanIncreaseGridSize() const;`
- L96 _public prototype_ `void ExecuteIncreaseGridSize();`
- L98 _public prototype_ `bool CanDecreaseGridSize() const;`
- L99 _public prototype_ `void ExecuteDecreaseGridSize();`
- L101 _public prototype_ `bool CanChangeGridSize() const;`
- L102 _public prototype_ `void ExecuteSetGridSize(int32 InNewSize, bool bInCommit);`
- L104 _public prototype_ `bool CanToggleSnapping() const;`
- L105 _public prototype_ `void ExecuteToggleSnapping();`
- L107 _public prototype_ `bool CanToggleGridSnapping() const;`
- L108 _public prototype_ `bool IsGridSnappingEnabled() const;`
- L109 _public prototype_ `void ExecuteToggleGridSnapping();`
- L111 _public prototype_ `bool CanToggleScreenSnapping() const;`
- L112 _public prototype_ `bool IsScreenSnappingEnabled() const;`
- L113 _public prototype_ `void ExecuteToggleScreenSnapping();`
- L115 _public prototype_ `bool CanToggleActorSnapping() const;`
- L116 _public prototype_ `bool IsActorSnappingEnabled() const;`
- L117 _public prototype_ `void ExecuteToggleActorSnapping();`
- L119 _public prototype_ `bool CanToggleGuides() const;`
- L120 _public prototype_ `void ExecuteToggleGuides();`
- L122 _public prototype_ `bool CanAddHorizontalGuide() const;`
- L123 _public prototype_ `void ExecuteAddHorizontalGuide();`
- L125 _public prototype_ `bool CanAddVerticalGuide() const;`
- L126 _public prototype_ `void ExecuteAddVerticalGuide();`
- L128 _public prototype_ `void ExecuteToggleChildActorLock();`
- L130 _public prototype_ `bool IsPostProcessTypeEnabled(EAvaViewportPostProcessType InPostProcessType) const;`
- L131 _public prototype_ `bool CanTogglePostProcessType(EAvaViewportPostProcessType InPostProcessType) const;`
- L132 _public prototype_ `void ExecuteTogglePostProcessType(EAvaViewportPostProcessType InPostProcessType);`
- L134 _public prototype_ `bool CanToggleTextureOverlay() const;`
- L135 _public prototype_ `void ExecuteToggleTextureOverlay();`
- L137 _public prototype_ `FIntPoint GetVirtualSize() const;`
- L138 _public prototype_ `bool IsVirtualSizeActive(FIntPoint InVirtualSize) const;`
- L139 _public prototype_ `void SetVirtualSize(FIntPoint InVirtualSize);`
- L140 _public prototype_ `float GetVirtualSizeAspectRatio() const;`
- L142 _public prototype_ `bool IsUsingVirtualSizeAspectRatioState(EAvaViewportVirtualSizeAspectRatioState InAspectRatioState) const;`
- L143 _public prototype_ `void SetVirtualSizeAspectRatioState(EAvaViewportVirtualSizeAspectRatioState InAspectRatioState);`
- L145 _public prototype_ `void LoadGuides();`
- L146 _public prototype_ `void ReloadGuides();`
- L148 _public prototype_ `void LoadPostProcessInfo();`
- L150 _public prototype_ `void ActivateCamera(TWeakObjectPtr<ACameraActor> InCamera);`
- L151 _public prototype_ `bool IsCameraActive(TWeakObjectPtr<ACameraActor> InCamera) const;`
- L153 _public prototype_ `bool CanResetPilotedCameraTransform() const;`
- L154 _public prototype_ `void ResetPilotedCameraTransform();`
- L156 _public prototype_ `void FillCameraMenu(UToolMenu* InMenu, bool bInIncludeCamerasAndViewports);`
- L159 _public prototype_ `virtual void PostUndo(bool bInSuccess);`
- L160 _public prototype_ `virtual void PostRedo(bool bInSuccess);`
- L164 _private member_ `TWeakPtr<SAvaLevelViewportFrame> ViewportFrameWeak;`
- L165 _private member_ `TSharedPtr<SAvaLevelViewportCameraBounds> CameraBounds;`
- L166 _private member_ `TSharedPtr<SAvaLevelViewportTextureOverlay> TextureOverlay;`
- L167 _private member_ `TSharedPtr<SAvaLevelViewportPixelGrid> PixelGrid;`
- L168 _private member_ `TSharedPtr<SAvaLevelViewportScreenGrid> ScreenGrid;`
- L169 _private member_ `TSharedPtr<SAvaLevelViewportSafeFrames> SafeFrames;`
- L170 _private member_ `TSharedPtr<SCanvas> GuideCanvas;`
- L171 _private member_ `TArray<TSharedPtr<SAvaLevelViewportGuide>> Guides;`
- L172 _private member_ `TSharedPtr<SAvaLevelViewportSnapIndicators> SnapIndicators;`
- L173 _private member_ `TSharedPtr<SWidget> BackgroundTextureSelector;`
- L174 _private member_ `TSharedPtr<SWidget> PostProcessOpacitySlider;`
- L175 _private member_ `TSharedPtr<FScopedTransaction> PostProcessInfoTransaction;`
- L177 _private member_ `float VirtualSizeAspectRatio;`
- L178 _private member_ `EAvaViewportVirtualSizeAspectRatioState VirtualSizeAspectRatioState;`
- L179 _private member_ `TSharedPtr<FScopedTransaction> VirtualSizeComponentSliderTransaction;`
- L181 _private prototype_ `FSlateIcon GetCameraIcon() const;`
- L183 _private prototype_ `TSharedRef<SWidget> GenerateCameraMenu();`
- L184 _private prototype_ `bool CanChangeCameraInCameraMenu() const;`
- L186 _private prototype_ `void AddCameraEntries(UToolMenu* InMenu, TArray<TWeakObjectPtr<ACameraActor>> InCameraActors);`
- L187 _private prototype_ `void AddCameraEntries(FToolMenuSection& InSection, TArray<TWeakObjectPtr<ACameraActor>> InCameraActors);`
- L189 _private prototype_ `void AddViewportEntries(UToolMenu* InMenu);`
- L190 _private prototype_ `void AddViewportEntries(FToolMenuSection& InSection);`
- L192 _private prototype_ `void AddVirtualSizeMenuEntries(UToolMenu* InMenu);`
- L193 _private prototype_ `void AddVirtualSizeDefaultEntries(FToolMenuSection& InSection);`
- L194 _private prototype_ `void AddVirtualSizeSizeSettings(FToolMenuSection& InSection);`
- L196 _private prototype_ `void AddGuidePresetMenuEntries(UToolMenu* InMenu);`
- L197 _private prototype_ `void AddGuidePresetCurrentMenu(UToolMenu* InMenu);`
- L198 _private prototype_ `void AddGuidePresetSavedMenu(UToolMenu* InMenu);`
- L200 _private prototype_ `void AddCameraZoomMenuEntries(UToolMenu* InMenu);`
- L202 _private prototype_ `static void AddVisualizerEntries(UToolMenu* InMenu);`
- L204 _private prototype_ `void OnSettingsChanged(const UAvaViewportSettings* InSettings, FName InPropertyChanged);`
- L205 _private prototype_ `void ApplySettings(const UAvaViewportSettings* InSettings);`
- L207 _private prototype_ `void LoadVirtualSizeSettings();`
- L209 _private prototype_ `bool IsChildActorLockEnabled() const;`
- L211 _private prototype_ `void BeginPostProcessInfoTransaction();`
- L212 _private prototype_ `void EndPostProcessInfoTransaction();`
- L214 _private prototype_ `FString GetBackgroundTextureObjectPath() const;`
- L215 _private prototype_ `void OnBackgroundTextureChanged(const FAssetData& InAssetData);`
- L217 _private prototype_ `float GetBackgroundOpacity() const;`
- L218 _private prototype_ `void OnBackgroundOpacitySliderBegin();`
- L219 _private prototype_ `void OnBackgroundOpacitySliderEnd(float InValue);`
- L220 _private prototype_ `void OnBackgroundOpacityChanged(float InValue);`
- L221 _private prototype_ `void OnBackgroundOpacityCommitted(float InValue, ETextCommit::Type InCommitType);`
- L223 _private prototype_ `FString GetTextureOverlayTextureObjectPath() const;`
- L224 _private prototype_ `void OnTextureOverlayTextureChanged(const FAssetData& InAssetData);`
- L226 _private prototype_ `float GetTextureOverlayOpacity() const;`
- L227 _private prototype_ `void OnTextureOverlayOpacitySliderEnd(float InValue);`
- L228 _private prototype_ `void OnTextureOverlayOpacityChanged(float InValue);`
- L229 _private prototype_ `void OnTextureOverlayOpacityCommitted(float InValue, ETextCommit::Type InCommitType);`
- L231 _private prototype_ `ECheckBoxState GetTextureOverlayStretchEnabledCheckBoxState() const;`
- L232 _private prototype_ `void OnTextureOverlayStretchEnabledCheckBoxChanged(ECheckBoxState InState);`
- L234 _private prototype_ `int32 GetVirtualSizeX() const;`
- L235 _private prototype_ `int32 GetVirtualSizeY() const;`
- L236 _private prototype_ `void OnVirtualSizeComponentSliderCommitted(int32 InNewDimension, ETextCommit::Type InCommitType, EAxis::Type InAxis);`
- L237 _private prototype_ `void OnVirtualSizeAspectRatioCommitted(float InNewAspectRatio, ETextCommit::Type InCommitType);`
- L238 _private prototype_ `void OnVirtualSizeSliderBegin();`
- L239 _private prototype_ `void OnVirtualSizeComponentSliderEnd(int32 InNewSize);`
- L240 _private prototype_ `void OnVirtualSizeAspectRatioSliderEnd(float InNewAspectRatio);`
- L241 _private prototype_ `bool IsVirtualSizeAspectRatioEnabled() const;`
- L243 _private prototype_ `bool ApplyVirtualSizeSettings(FIntPoint& InOutVirtualSize);`
- L244 _private prototype_ `void UpdateVirtualSizeSettings();`
- L246 _private prototype_ `void CheckVirtualSizeCameraUpdateSettings();`
- L248 _private prototype_ `bool HasGuides() const;`
- L250 _private prototype_ `bool CanSaveAsGuidePreset() const;`
- L252 _private prototype_ `bool CanSaveAsGuidePreset(const FToolMenuContext& InContext) const;`
- L253 _private prototype_ `void ExecuteSaveAsGuidePreset(const FToolMenuContext& InContext);`
- L255 _private prototype_ `bool CanSaveGuidePreset(const FToolMenuContext & InContext) const;`
- L256 _private prototype_ `void ExecuteSaveGuidePreset(const FToolMenuContext& InContext);`
- L258 _private prototype_ `bool CanReloadGuidePreset(const FToolMenuContext& InContext) const;`
- L259 _private prototype_ `void ExecuteReloadGuidePreset(const FToolMenuContext& InContext);`
- L261 _private prototype_ `FReply ExecuteLoadGuidePreset(FString InPresetName);`
- L263 _private prototype_ `FReply ExecuteReplaceGuidePreset(FString InPresetName);`
- L265 _private prototype_ `FReply ExecuteRemoveGuidePreset(FString InPresetName);`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheLevelViewport/Private/SAvaLevelViewportFrame.h` (Private)


#### struct `FAvaLevelViewportGuideFrameAndWidget`  
`struct FAvaLevelViewportGuideFrameAndWidget`  
_L16-27_
- L18 _public member_ `TSharedPtr<SAvaLevelViewportFrame> ViewportFrame;`
- L19 _public member_ `TSharedPtr<SAvaLevelViewport> ViewportWidget;`
- L21 _public prototype_ `FAvaLevelViewportGuideFrameAndWidget(TWeakPtr<SAvaLevelViewportFrame> InViewportFrameWeak);`
- L23 _public function_ `bool IsValid() const`
- L26 _protected member_ `bool bIsValid = false;`

#### struct `FAvaLevelViewportGuideFrameAndClient`  
`struct FAvaLevelViewportGuideFrameAndClient`  
_L29-40_
- L31 _public member_ `TSharedPtr<SAvaLevelViewportFrame> ViewportFrame;`
- L32 _public member_ `TSharedPtr<FAvaLevelViewportClient> ViewportClient;`
- L34 _public prototype_ `FAvaLevelViewportGuideFrameAndClient(TWeakPtr<SAvaLevelViewportFrame> InViewportFrameWeak);`
- L36 _public function_ `bool IsValid() const`
- L39 _protected member_ `bool bIsValid = false;`

#### struct `FAvaLevelViewportGuideFrameClientAndWidget`  
`struct FAvaLevelViewportGuideFrameClientAndWidget`  
_L42-54_
- L44 _public member_ `TSharedPtr<SAvaLevelViewportFrame> ViewportFrame;`
- L45 _public member_ `TSharedPtr<FAvaLevelViewportClient> ViewportClient;`
- L46 _public member_ `TSharedPtr<SAvaLevelViewport> ViewportWidget;`
- L48 _public prototype_ `FAvaLevelViewportGuideFrameClientAndWidget(TWeakPtr<SAvaLevelViewportFrame> InViewportFrameWeak);`
- L50 _public function_ `bool IsValid() const`
- L53 _protected member_ `bool bIsValid = false;`

#### class `SAvaLevelViewportFrame`  
`class SAvaLevelViewportFrame : public SCompoundWidget`  
_L56-85_
- inherits: `SCompoundWidget`
- L59 _public function_ `SLATE_BEGIN_ARGS(SAvaLevelViewportFrame)`
- L60 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs , const FAssetEditorViewportConstructionArgs& InViewportArgs , TSharedPtr<ILevelEditor> InLevelEditor);`
- L66 _public function_ `TSharedPtr<SAvaLevelViewport> GetViewportWidget() const`
- L68 _public function_ `TSharedPtr<FAvaLevelViewportClient> GetViewportClient() const`
- L70 _public function_ `float GetDPIScale() const`
- L73 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L77 _private member_ `TSharedPtr<SAvaLevelViewport> ViewportWidget;`
- L78 _private member_ `TSharedPtr<FAvaLevelViewportClient> ViewportClient;`
- L79 _private member_ `TSharedPtr<SAvaLevelViewportRuler> HorizontalRuler;`
- L80 _private member_ `TSharedPtr<SAvaLevelViewportRuler> VerticalRuler;`
- L81 _private member_ `float DPIScale;`
- L83 _private prototype_ `FMargin GetHorizontalRulerOffset() const;`
- L84 _private prototype_ `FMargin GetVerticalRulerOffset() const;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheLevelViewport/Private/ViewportClient/AvaLevelViewportClient.h` (Private)


#### class `FAvaLevelViewportClient`  
`class FAvaLevelViewportClient : public FLevelEditorViewportClient, public FAvaViewportClientUtilityProvider, public TSharedFromThis<FAvaLevelViewportClient>`  
_L29-151_
- inherits: `FLevelEditorViewportClient,FAvaViewportClientUtilityProvider,TSharedFromThis<FAvaLevelViewportClient>`
- L32 _public prototype_ `UE_AVA_INHERITS_WITH_SUPER(FAvaLevelViewportClient, FLevelEditorViewportClient, FAvaViewportClientUtilityProvider) static bool IsAvaLevelViewportClient(const FEditorViewportClient* InViewportClient);`
- L36 _public prototype_ `FAvaLevelViewportClient();`
- L39 _public prototype_ `void Init();`
- L41 _public function_ `const FAvaViewportGeometry& GetViewportGeometry() const`
- L43 _public prototype_ `bool HasCachedViewportSize() const;`
- L44 _public prototype_ `FVector2f GetCachedViewportSize() const;`
- L45 _public prototype_ `FVector2f GetCachedViewportOffset() const;`
- L47 _public prototype_ `bool HasVirtualViewportSize() const;`
- L48 _public prototype_ `void SetVirtualViewportSize(const FIntPoint& InVirtualSize);`
- L51 _public prototype_ `void SetViewportWidget(TSharedPtr<SAvaLevelViewport> InLevelViewport);`
- L53 _public prototype_ `virtual FSceneView* CalcNonZoomedSceneView(FSceneViewFamily* ViewFamily, const int32 StereoViewIndex = INDEX_NONE);`
- L55 _public function_ `bool AreChildActorsLocked() const`
- L56 _public function_ `void SetChildActorsLocked(bool bInLockChildActors)`
- L58 _public function_ `TSharedRef<IAvaViewportBoundingBoxVisualizer> GetBoundingBoxVisualizer() const`
- L60 _public function_ `TSharedRef<FAvaIsolateActorsOperation> GetIsolateActorsOperation() const`
- L62 _public prototype_ `AActor* GetCinematicViewTarget() const;`
- L65 _public prototype_ `virtual ELevelViewportType GetViewportType() const override;`
- L66 _public function_ `virtual void SetViewportType(ELevelViewportType InViewportType) override`
- L67 _public prototype_ `virtual void Draw(const FSceneView* InView, FPrimitiveDrawInterface* InPDI) override;`
- L68 _public prototype_ `virtual void DrawCanvas(FViewport& InViewport, FSceneView& View, FCanvas& Canvas) override;`
- L69 _public prototype_ `virtual FSceneView* CalcSceneView(FSceneViewFamily* ViewFamily, const int32 StereoViewIndex = INDEX_NONE) override;`
- L70 _public prototype_ `virtual void TrackingStarted(const FInputEventState& InInputState, bool bIsDraggingWidget, bool bNudge) override;`
- L71 _public prototype_ `virtual void TrackingStopped() override;`
- L72 _public prototype_ `virtual bool InputKey(const FInputKeyEventArgs& EventArgs) override;`
- L73 _public prototype_ `virtual void UpdateMouseDelta() override;`
- L74 _public prototype_ `virtual EMouseCursor::Type GetCursor(FViewport* InViewport, int32 InX, int32 InY) override;`
- L75 _public prototype_ `virtual FMatrix CalcViewRotationMatrixForControllingActorView(const FRotator& InViewRotation) const override;`
- L76 _public prototype_ `virtual bool ProcessScreenShots(FViewport* InViewport) override;`
- L80 _public prototype_ `virtual FVector2f GetViewportSize() const override;`
- L81 _public prototype_ `virtual FTransform GetViewportViewTransform() const override;`
- L85 _public function_ `virtual bool IsMotionDesignViewport() const override`
- L86 _public function_ `virtual const FEditorViewportClient* AsEditorViewportClient() const override`
- L87 _public function_ `virtual bool SupportsZoom() const override`
- L88 _public prototype_ `virtual float GetZoomedFOV() const override;`
- L89 _public prototype_ `virtual float GetUnZoomedFOV() const override;`
- L90 _public prototype_ `virtual FIntPoint GetVirtualViewportSize() const override;`
- L91 _public prototype_ `virtual FVector2f GetViewportOffset() const override;`
- L92 _public prototype_ `virtual FVector2f GetViewportWidgetSize() const override;`
- L93 _public prototype_ `virtual float GetViewportDPIScale() const override;`
- L94 _public prototype_ `virtual FAvaVisibleArea GetVisibleArea() const override;`
- L95 _public prototype_ `virtual FAvaVisibleArea GetZoomedVisibleArea() const override;`
- L96 _public prototype_ `virtual FAvaVisibleArea GetVirtualVisibleArea() const override;`
- L97 _public prototype_ `virtual FAvaVisibleArea GetVirtualZoomedVisibleArea() const override;`
- L98 _public prototype_ `virtual FVector2f GetUnconstrainedViewportMousePosition() const override;`
- L99 _public prototype_ `virtual FVector2f GetConstrainedViewportMousePosition() const override;`
- L100 _public prototype_ `virtual FVector2f GetUnconstrainedZoomedViewportMousePosition() const override;`
- L101 _public prototype_ `virtual FVector2f GetConstrainedZoomedViewportMousePosition() const override;`
- L102 _public function_ `virtual TSharedPtr<FAvaSnapOperation> GetSnapOperation() const override`
- L103 _public prototype_ `virtual TSharedPtr<FAvaSnapOperation> StartSnapOperation() override;`
- L104 _public prototype_ `virtual bool EndSnapOperation(FAvaSnapOperation* InSnapOperation) override;`
- L105 _public prototype_ `virtual void OnActorSelectionChanged() override;`
- L106 _public function_ `virtual TSharedPtr<FAvaCameraZoomController> GetZoomController() const override`
- L107 _public prototype_ `virtual UCameraComponent* GetCameraComponentViewTarget() const override;`
- L108 _public prototype_ `virtual AActor* GetViewTarget() const override;`
- L109 _public prototype_ `virtual void SetViewTarget(TWeakObjectPtr<AActor> InViewTarget) override;`
- L110 _public prototype_ `virtual void OnCameraCut(AActor* InTarget, bool bInJumpCut) override;`
- L111 _public function_ `virtual UWorld* GetViewportWorld() const`
- L112 _public function_ `virtual TSharedPtr<FAvaViewportPostProcessManager> GetPostProcessManager() const override`
- L116 _protected member_ `TWeakPtr<SAvaLevelViewport> AvaLevelViewportWeak;`
- L118 _protected member_ `FAvaViewportGeometry ViewportGeometry;`
- L120 _protected member_ `TSharedPtr<FAvaCameraZoomController> ZoomController;`
- L122 _protected member_ `TSharedPtr<IAvaViewportBoundingBoxVisualizer> BoundingBoxVisualizer;`
- L124 _protected member_ `TWeakObjectPtr<UCameraComponent> ActiveCameraComponentWeak;`
- L126 _protected member_ `TWeakPtr<FAvaSnapOperation> SnapOperationWeak;`
- L128 _protected member_ `TSharedPtr<FAvaDragOperation> DragOperation;`
- L130 _protected member_ `TSharedPtr<FAvaChildTransformLockOperation> ChildTransformLockOperation;`
- L132 _protected member_ `TSharedPtr<FAvaViewportPostProcessManager> PostProcessManager;`
- L134 _protected member_ `TSharedPtr<FAvaIsolateActorsOperation> IsolateActorsOperation;`
- L136 _protected member_ `bool bIsZoomedSceneView;`
- L138 _protected member_ `bool bLockChildActorsOnDrag;`
- L140 _protected prototype_ `void SetCinematicViewTarget(AActor* InCinematicViewTarget);`
- L142 _protected prototype_ `void LoadActiveCameraComponent();`
- L144 _protected prototype_ `void CheckActiveCameraComponent();`
- L146 _protected prototype_ `UCameraComponent* UpdateActiveCameraComponent(AActor* InViewTarget);`
- L148 _protected prototype_ `void SetActiveCameraComponent(UCameraComponent* InCameraComponent);`
- L150 _protected prototype_ `void OnMapChanged(UWorld* InWorld, EMapChangeType InChangeType);`

#### Free symbols / members of external scopes

- L27 _prototype_ `UE_AVA_TYPE_EXTERNAL(FLevelEditorViewportClient);`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheLevelViewport/Private/Widgets/Engine/SRuler.h` (Private)


#### class `UE::AvaLevelViewport::Private::SRuler`  
`class SRuler : public SCompoundWidget`  
_L25-109_
- inherits: `SCompoundWidget`
- L29 _public function_ `SLATE_BEGIN_ARGS(SRuler) : _Orientation(Orient_Horizontal) , _OnMouseButtonDown()`
- L36 _public prototype_ `SLATE_ARGUMENT(EOrientation, Orientation) SLATE_EVENT(FPointerEventHandler, OnMouseButtonDown) SLATE_END_ARGS() void Construct( const FArguments& InArgs );`
- L59 _public prototype_ `float DetermineOptimalSpacing(float InPixelsPerInput, uint32 MinTick, float MinTickSpacing) const;` — Determines the optimal spacing between tick marks in the slider for a given pixel density Increments until a minimum amount of slate units specified by MinTick is reached @param InPixelsPerInput	The density of pixels between each input @param MinTick			The minimum slate units per tick allowed @param MinTickSpacing	The minimum tick spacing in time units allowed @return the optimal spacing in time units
- L68 _public prototype_ `void SetRuling(FVector2D AbsoluteOrigin, float SlateToUnitScale);` — Sets the rules to use when rendering the ruler. @param AbsoluteOrigin The origin of the ruler in absolute window space. @param SlateToUnitScale The scaler applied to slate units to get the same number of units currently being displayed by the rule marks.
- L75 _public prototype_ `void SetCursor(TOptional<FVector2D> AbsoluteCursor);` — Sets the cursor position in window absolute space. @param AbsoluteCursor The position of the cursor in absolute window space.
- L79 _protected prototype_ `virtual FVector2D ComputeDesiredSize(float) const override;` — SWidget interface
- L80 _protected prototype_ `virtual int32 OnPaint( const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled ) const override;`
- L81 _protected prototype_ `virtual FReply OnMouseButtonDown( const FGeometry& MyGeometry, const FPointerEvent& MouseEvent ) override;`
- L82 _protected prototype_ `virtual FReply OnMouseButtonUp( const FGeometry& MyGeometry, const FPointerEvent& MouseEvent ) override;`
- L83 _protected prototype_ `virtual FReply OnMouseMove( const FGeometry& MyGeometry, const FPointerEvent& MouseEvent ) override;`
- L84 _protected prototype_ `virtual FReply OnMouseWheel( const FGeometry& MyGeometry, const FPointerEvent& MouseEvent ) override;`
- L92 _private prototype_ `int32 DrawTicks(FSlateWindowElementList& OutDrawElements, const FScrubRangeToScreen& RangeToScreen, FDrawTickArgs& InArgs) const;` — Draws the ticks on the track
- L96 _private member_ `EOrientation Orientation;` — The orientation of the ruler
- L99 _private member_ `FVector2D AbsoluteOrigin;` — The absolute origin of the document being measured.  The 0 on the ruler will start here.
- L102 _private member_ `TOptional<FVector2D> AbsoluteCursor;` — The absolute position of the cursor so that little lines can be drawn showing the cursors position on the ruler.
- L105 _private member_ `float SlateToUnitScale;` — The current conversion from Slate Pixel To Unit Size.
- L108 _private member_ `FPointerEventHandler MouseButtonDownHandler;` — The public event we expose when the mouse button is pressed onto the ruler.

#### Free symbols / members of external scopes

- L22 _namespace_ `namespace UE`
- L22 _namespace_ `namespace AvaLevelViewport` (scope `UE`)
- L22 _namespace_ `namespace Private` (scope `UE::AvaLevelViewport`)

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheLevelViewport/Private/Widgets/SAvaEyeDropperButton.h` (Private)


#### class `SAvaEyeDropperButton`  
`class SAvaEyeDropperButton : public SButton`  
_L26-98_
- inherits: `SButton`
- desc: Unashamedly stolen from private engine code
- L29 _public function_ `DECLARE_DELEGATE_OneParam(FOnDropperComplete, bool) SLATE_BEGIN_ARGS( SAvaEyeDropperButton ) : _OnValueChanged() , _OnBegin() , _OnComplete() , _DisplayGamma()`
- L39 _public prototype_ `SLATE_EVENT(FOnLinearColorValueChanged, OnValueChanged) SLATE_EVENT(FSimpleDelegate, OnBegin) SLATE_EVENT(FOnDropperComplete, OnComplete) SLATE_ATTRIBUTE(float, DisplayGamma) SLATE_END_ARGS() void Construct(const FArguments& InArgs);` — Invoked when a new value is selected by the dropper
- L54 _public prototype_ `virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L55 _public prototype_ `virtual FReply OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L56 _public prototype_ `virtual FReply OnMouseMove(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L57 _public prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;`
- L58 _public prototype_ `virtual FCursorReply OnCursorQuery(const FGeometry& MyGeometry, const FPointerEvent& CursorEvent) const override;`
- L59 _public prototype_ `virtual void OnMouseCaptureLost(const FCaptureLostEvent& CaptureLostEvent) override;`
- L63 _private prototype_ `FReply OnClicked();`
- L65 _private prototype_ `EVisibility GetEscapeTextVisibility() const;`
- L67 _private prototype_ `FSlateColor GetDropperImageColor() const;`
- L69 _private prototype_ `bool IsMouseOver(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) const;`
- L71 _private prototype_ `void OnPreTick(float DeltaTime);`
- L72 _private prototype_ `void ResetDropperModeStates();`
- L76 _private member_ `TSharedPtr<SWidgetSwitcher> ButtonContentSwitcher;`
- L79 _private member_ `FOnLinearColorValueChanged OnValueChanged;` — Invoked when a new value is selected by the dropper
- L82 _private member_ `FSimpleDelegate OnBegin;` — Invoked when the dropper goes from inactive to active
- L85 _private member_ `FOnDropperComplete OnComplete;` — Invoked when the dropper goes from active to inactive - can be used to commit colors by the owning picker
- L88 _private member_ `TAttribute<float> DisplayGamma;` — Sets the display Gamma setting - used to correct colors sampled from the screen
- L91 _private member_ `TOptional<FVector2f> LastCursorPosition;` — Previous Tick's cursor position
- L94 _private member_ `bool bWasClicked = false;` — Dropper states
- L95 _private member_ `bool bWasClickActivated = false;`
- L96 _private member_ `bool bWasLeft = false;`
- L97 _private member_ `bool bWasReEntered = false;`

#### Free symbols / members of external scopes

- L29 _delegate_ `DECLARE_DELEGATE_OneParam(FOnDropperComplete, bool) SLATE_BEGIN_ARGS( SAvaEyeDropperButton ) : _OnValueChanged() , _OnBegin() , _OnComplete() , _DisplayGamma() {} SLATE_EVENT(FOnLinearColorValueChanged, OnValueChanged) SLATE_EVENT(FSimpleDelegate, OnBegin) SLATE_EVENT(FOnDropperComplete, OnComplete) SLATE_ATTRIBUTE(float, DisplayGamma) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheLevelViewport/Private/Widgets/SAvaLevelViewportActorAlignmentMenu.h` (Private)


#### class `SAvaLevelViewportActorAlignmentMenu`  
`class SAvaLevelViewportActorAlignmentMenu : public SCompoundWidget`  
_L18-55_
- inherits: `SCompoundWidget`
- L20 _private function_ `SLATE_DECLARE_WIDGET(SAvaLevelViewportActorAlignmentMenu, SCompoundWidget) SLATE_BEGIN_ARGS(SAvaLevelViewportActorAlignmentMenu)`
- L26 _public prototype_ `static TSharedRef<SAvaLevelViewportActorAlignmentMenu> CreateMenu(const TSharedRef<IToolkitHost>& InToolkitHost);`
- L28 _public prototype_ `void Construct(const FArguments& Args, const TSharedRef<IToolkitHost>& InToolkitHost);`
- L31 _protected member_ `TWeakPtr<IToolkitHost> ToolkitHostWeak;`
- L33 _protected member_ `static const inline uint8 NO_VALUE = 255;`
- L35 _protected prototype_ `TSharedRef<SButton> GetLocationAlignmentButton(EAvaHorizontalAlignment InHoriz, EAvaVerticalAlignment InVert, EAvaDepthAlignment InDepth, FName InImage, FText InToolTip);`
- L38 _protected prototype_ `TSharedRef<SButton> GetDistributionAlignmentButton(EAvaScreenAxis InScreenAxis, FName InImage, FText InToolTip);`
- L40 _protected prototype_ `TSharedRef<SButton> GetRotationAlignmentButton(EAvaRotationAxis InAxisList, FName InImage, FText InToolTip);`
- L42 _protected prototype_ `TSharedRef<SButton> GetCameraRotationAlignmentButton(EAvaRotationAxis InAxisList, FName InImage, FText InToolTip);`
- L44 _protected prototype_ `FReply OnSizeToScreenClicked(bool bInStretchToFit);`
- L46 _protected prototype_ `FReply OnFitToScreenClicked();`
- L48 _protected prototype_ `FReply OnRotationAlignmentButtonClicked(EAvaRotationAxis InAxisList);`
- L50 _protected prototype_ `FReply OnCameraRotationAlignmentButtonClicked(EAvaRotationAxis InAxisList);`
- L52 _protected prototype_ `FReply OnDistributeAlignmentButtonClicked(EAvaScreenAxis InScreenAxis);`
- L54 _protected prototype_ `FReply OnLocationAlignmentButtonClicked(EAvaHorizontalAlignment InHoriz, EAvaVerticalAlignment InVert, EAvaDepthAlignment InDepth);`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheLevelViewport/Private/Widgets/SAvaLevelViewportActorColorMenu.h` (Private)


#### struct `FAvaColorInfo`  
`struct FAvaColorInfo`  
_L26-30_
- L28 _public member_ `FLinearColor Color;`
- L29 _public member_ `FText Label;`

#### struct `FAvaColorTheme`  
`struct FAvaColorTheme`  
_L32-69_
- L34 _public function_ `FAvaColorTheme() :FAvaColorTheme("Theme")`
- L39 _public function_ `FAvaColorTheme(const FString& InName)`
- L44 _public function_ `const FString& GetName() const`
- L45 _public function_ `void SetName(const FString& InNewName)`
- L47 _public function_ `TArray<FAvaColorInfo>& GetColors()`
- L52 _public function_ `int32 FindApproxColor(const FLinearColor& InColor, float InTolerance = KINDA_SMALL_NUMBER) const`
- L67 _protected member_ `FString Name;`
- L68 _protected member_ `TArray<FAvaColorInfo> Colors;`

#### class `SAvaLevelViewportActorColorMenu`  
`class SAvaLevelViewportActorColorMenu : public SCompoundWidget, public FGCObject`  
_L71-232_
- inherits: `SCompoundWidget,FGCObject`
- L73 _private function_ `SLATE_DECLARE_WIDGET(SAvaLevelViewportActorColorMenu, SCompoundWidget) SLATE_BEGIN_ARGS(SAvaLevelViewportActorColorMenu)`
- L79 _public prototype_ `static TSharedRef<SAvaLevelViewportActorColorMenu> CreateMenu(const TSharedRef<IToolkitHost>& InToolkitHost);`
- L81 _public prototype_ `static FAvaColorTheme* FindTheme(const FString& InName, bool bInAddIfNotFound = false);`
- L82 _public prototype_ `static FAvaColorTheme* GetTheme(int32 InThemeIndex);`
- L84 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<IToolkitHost>& InToolkitHost);`
- L86 _public prototype_ `virtual FReply OnMouseButtonDown(const FGeometry& InMyGeometry, const FPointerEvent& InMouseEvent) override;`
- L87 _public prototype_ `virtual FReply OnMouseButtonUp(const FGeometry& InMyGeometry, const FPointerEvent& InMouseEvent) override;`
- L88 _public prototype_ `virtual FReply OnMouseMove(const FGeometry& InMyGeometry, const FPointerEvent& InMouseEvent) override;`
- L89 _public prototype_ `virtual FReply OnDragDetected(const FGeometry& InMyGeometry, const FPointerEvent& InMouseEvent) override;`
- L91 _public prototype_ `void UpdateColorWheel(const FVector2f& InLocalMouseLocation);`
- L92 _public prototype_ `void EndColorSelection();`
- L94 _public function_ `FLinearColor GetActiveColor() const`
- L95 _public function_ `FLinearColor GetInactiveColor() const`
- L96 _public function_ `EAvaColorStyle GetColorStyle() const`
- L98 _public prototype_ `void SetActiveColorRGB(FLinearColor InRGB);`
- L99 _public prototype_ `void SetActiveColorHSV(FLinearColor InHSV);`
- L101 _public prototype_ `void SetInactiveColorRGB(FLinearColor InRGB);`
- L102 _public prototype_ `void SetInactiveColorHSV(FLinearColor InHSV);`
- L104 _public prototype_ `void SetColorStyle(EAvaColorStyle InNewStyle);`
- L106 _public prototype_ `void SwitchActiveColor();`
- L108 _public prototype_ `void SetRedValue(float InNewValue, bool bInAddToTheme);`
- L109 _public prototype_ `void SetGreenValue(float InNewValue, bool bInAddToTheme);`
- L110 _public prototype_ `void SetBlueValue(float InNewValue, bool bInAddToTheme);`
- L111 _public prototype_ `void SetHueValue(float InNewValue, bool bInAddToTheme);`
- L112 _public prototype_ `void SetSaturationValue(float InNewValue, bool InbAddToTheme);`
- L113 _public prototype_ `void SetValueValue(float InNewValue, bool InbAddToTheme);`
- L116 _private member_ `static const FVector2f WheelMiddle;`
- L117 _private member_ `static const inline int32 MaxColorsForAutoAdd = 21;`
- L118 _private member_ `static constexpr int32 ColorsPerPaletteRow = 3;`
- L120 _private member_ `static int32 ActiveThemeIndex;`
- L121 _private member_ `static TArray<FAvaColorTheme> ColorThemes;`
- L123 _private prototype_ `static void LoadColorThemesFromIni();`
- L124 _private prototype_ `static void SaveColorThemesToIni();`
- L126 _private member_ `FAvaLevelColorPicker ColorPicker;`
- L128 _private member_ `TObjectPtr<UMaterial> HueMaterial;`
- L129 _private member_ `TObjectPtr<UMaterial> SatValueMaterial;`
- L130 _private member_ `TObjectPtr<UTexture2D> SelectedValueImage;`
- L131 _private member_ `TObjectPtr<UMaterialInstanceDynamic> SatValueMaterialDynamic;`
- L133 _private member_ `TSharedPtr<FSlateMaterialBrush> HueBrush;`
- L134 _private member_ `TSharedPtr<FSlateMaterialBrush> SatValueBrush;`
- L135 _private member_ `TSharedPtr<FSlateImageBrush> SelectedValueBrush;`
- L137 _private member_ `float Red;`
- L138 _private member_ `float Green;`
- L139 _private member_ `float Blue;`
- L141 _private member_ `float Hue;`
- L142 _private member_ `float Saturation;`
- L143 _private member_ `float Value;`
- L145 _private member_ `FLinearColor ActiveColor;`
- L146 _private member_ `FLinearColor InactiveColor;`
- L148 _private member_ `EAvaColorStyle ColorStyle = EAvaColorStyle::Solid;`
- L149 _private member_ `bool bIsUnlit = true;`
- L151 _private member_ `bool bIsRGB = true;`
- L152 _private member_ `TSharedPtr<STextBlock> ColorFormatButtonText;`
- L153 _private member_ `TSharedPtr<SBox> ColorTextInputWidgetBox;`
- L155 _private member_ `SConstraintCanvas::FSlot* HueSlot = nullptr;`
- L156 _private member_ `SConstraintCanvas::FSlot* SatValueSlot = nullptr;`
- L158 _private member_ `TSharedPtr<SGridPanel> ColorPalette;`
- L159 _private member_ `TSharedPtr<SButton> ThemesButton;`
- L160 _private member_ `TSharedPtr<SWidgetSwitcher> ColorStyleSwitcher;`
- L162 _private member_ `bool bEditingHue;`
- L163 _private member_ `bool bEditingSaturationValue;`
- L166 _private prototype_ `virtual FString GetReferencerName() const override;`
- L167 _private prototype_ `virtual void AddReferencedObjects(FReferenceCollector& InCollector) override;`
- L170 _private prototype_ `void ApplyActiveColor();`
- L171 _private prototype_ `void UpdateColorPalette();`
- L172 _private prototype_ `void AddColorToTheme(const FLinearColor& InNewColor);`
- L174 _private prototype_ `TSharedRef<SWidget> GetRGBEntryBox();`
- L175 _private prototype_ `TSharedRef<SWidget> GetHSLEntryBox();`
- L177 _private prototype_ `bool IsOverSaturationValueBlock(const FVector2f& InLocalMouseLocation) const;`
- L178 _private prototype_ `bool IsOverColorWheel(const FVector2f& InLocalMouseLocation) const;`
- L179 _private prototype_ `bool IsOverColorSelector(const FVector2f& InLocalMouseLocation) const;`
- L181 _private prototype_ `FReply OnColorFormatToggleClicked();`
- L182 _private prototype_ `FReply OnActiveColorMouseDown(const FGeometry& InMyGeometry, const FPointerEvent& InMouseEvent);`
- L183 _private prototype_ `FReply OnInactiveColorMouseDown(const FGeometry& InMyGeometry, const FPointerEvent& InMouseEvent);`
- L184 _private prototype_ `FReply OnColorPaletteMouseDown(const FGeometry& InMyGeometry, const FPointerEvent& InMouseEvent, int32 InColorIdx);`
- L185 _private prototype_ `FReply OnChangeThemeButtonClicked();`
- L186 _private prototype_ `FReply OnUnlitButtonClicked();`
- L188 _private prototype_ `void OnRedSliderValueChanged(float InNewValue);`
- L189 _private prototype_ `void OnGreenSliderValueChanged(float InNewValue);`
- L190 _private prototype_ `void OnBlueSliderValueChanged(float InNewValue);`
- L191 _private prototype_ `void OnHueSliderValueChanged(float InNewValue);`
- L192 _private prototype_ `void OnSaturationSliderValueChanged(float InNewValue);`
- L193 _private prototype_ `void OnValueSliderValueChanged(float InNewValue);`
- L195 _private prototype_ `void OnRedValueChanged(float InNewValue, ETextCommit::Type InCommitType);`
- L196 _private prototype_ `void OnGreenValueChanged(float InNewValue, ETextCommit::Type InCommitType);`
- L197 _private prototype_ `void OnBlueValueChanged(float InNewValue, ETextCommit::Type InCommitType);`
- L198 _private prototype_ `void OnHueValueChanged(float InNewValue, ETextCommit::Type InCommitType);`
- L199 _private prototype_ `void OnSaturationValueChanged(float InNewValue, ETextCommit::Type InCommitType);`
- L200 _private prototype_ `void OnValueValueChanged(float InNewValue, ETextCommit::Type InCommitType);`
- L202 _private prototype_ `TSharedRef<SWidget> BuildRenameColorMenu(int32 InColorIdx);`
- L203 _private prototype_ `TSharedRef<SWidget> BuildThemesMenu();`
- L205 _private prototype_ `void OnDropperValueChanged(FLinearColor InNewColor);`
- L206 _private prototype_ `void OnDropperComplete(bool bInSuccess);`
- L208 _private function_ `TOptional<float> GetRed() const`
- L209 _private function_ `TOptional<float> GetGreen() const`
- L210 _private function_ `TOptional<float> GetBlue() const`
- L211 _private function_ `TOptional<float> GetHue() const`
- L212 _private function_ `TOptional<float> GetSaturation() const`
- L213 _private function_ `TOptional<float> GetValue() const`
- L215 _private prototype_ `FSlateColor GetUnlitButtonColor() const;`
- L217 _private prototype_ `void CopyRGBtoHSV();`
- L218 _private prototype_ `void CopyHSVtoRGB();`
- L220 _private prototype_ `FReply OnColorSwitchedMouseDown(const FGeometry& InMyGeometry, const FPointerEvent& InPointerEvent);`
- L222 _private prototype_ `void OnColorStyleChanged();`
- L223 _private prototype_ `void BroadcastColorChange();`
- L225 _private prototype_ `void SetActiveColorRGB_Direct(FLinearColor InRGB);`
- L226 _private prototype_ `void SetActiveColorHSV_Direct(FLinearColor InHSV);`
- L228 _private prototype_ `void SetInactiveColorRGB_Direct(FLinearColor InRGB);`
- L229 _private prototype_ `void SetInactiveColorHSV_Direct(FLinearColor InHSV);`
- L231 _private prototype_ `void SetColorStyle_Direct(EAvaColorStyle InStyle);`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheLevelViewport/Private/Widgets/SAvaLevelViewportCameraBounds.h` (Private)


#### class `SAvaLevelViewportCameraBounds`  
`class SAvaLevelViewportCameraBounds : public SCompoundWidget`  
_L10-29_
- inherits: `SCompoundWidget`
- L13 _public function_ `SLATE_BEGIN_ARGS(SAvaLevelViewportCameraBounds)`
- L15 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedRef<FAvaLevelViewportClient> InAvaLevelViewportClient);`
- L20 _public prototype_ `virtual int32 OnPaint(const FPaintArgs& InPaintArgs, const FGeometry& InAllottedGeometry, const FSlateRect& InMyCullingRect, FSlateWindowElementList& OutDrawElements, int32 InLayerId, const FWidgetStyle& InWidgetStyle, bool bInParentEnabled) const override;`
- L25 _protected member_ `TWeakPtr<FAvaLevelViewportClient> AvaLevelViewportClientWeak;`
- L27 _protected prototype_ `void DrawCameraBounds(const FPaintArgs& InPaintArgs, const FGeometry& InAllottedGeometry, const FSlateRect& InMyCullingRect, FSlateWindowElementList& OutDrawElements, int32& InOutLayerId, const FLinearColor& InQuadColor) const;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheLevelViewport/Private/Widgets/SAvaLevelViewportGuide.h` (Private)


#### class `UAvaLevelViewportGuideContext`  
`class UAvaLevelViewportGuideContext : public UObject`  
_L18-24_
- reflection: `UCLASS()`
- inherits: `UObject`
- L23 _public member_ `TWeakPtr<SAvaLevelViewportGuide> GuideWeak;`

#### class `FAvaLevelViewportGuideDragDropOperation`  
`class FAvaLevelViewportGuideDragDropOperation : public FDragDropOperation`  
_L26-44_
- inherits: `FDragDropOperation`
- L29 _public prototype_ `DRAG_DROP_OPERATOR_TYPE(FAvaLevelViewportGuideDragDropOperation, FDragDropOperation) FAvaLevelViewportGuideDragDropOperation(TSharedPtr<SAvaLevelViewportGuide> InGuide);`
- L35 _public prototype_ `virtual void OnDragged(const FDragDropEvent& DragDropEvent) override;`
- L38 _public function_ `TSharedPtr<FAvaSnapOperation> GetSnapOperation() const`
- L41 _protected member_ `TWeakPtr<SAvaLevelViewportGuide> GuideWeak;`
- L42 _protected member_ `TSharedPtr<FAvaSnapOperation> SnapOperation;`
- L43 _protected member_ `TSharedPtr<TGuardValue<int32>> SnapStateGuard;`

#### class `SAvaLevelViewportGuide`  
`class SAvaLevelViewportGuide : public SBox`  
_L46-120_
- inherits: `SBox`
- L49 _public function_ `SLATE_BEGIN_ARGS(SAvaLevelViewportGuide) : _Orientation(EOrientation::Orient_Horizontal) , _OffsetFraction(0.5f) , _InitialState(EAvaViewportGuideState::Enabled)`
- L54 _public prototype_ `SLATE_ARGUMENT(EOrientation, Orientation) SLATE_ARGUMENT(float, OffsetFraction) SLATE_ARGUMENT(EAvaViewportGuideState, InitialState) SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedPtr<SAvaLevelViewportFrame> InViewportFrame, int32 InIndex);`
- L61 _public function_ `const FAvaViewportGuideInfo& GetGuideInfo() const`
- L62 _public prototype_ `void SetState(EAvaViewportGuideState InNewState, bool bInSaveGuides = true);`
- L63 _public function_ `void SetLocked(bool bInLocked)`
- L64 _public function_ `bool IsBeingDragged() const`
- L65 _public prototype_ `EVisibility GetGuideVisibility() const;`
- L66 _public prototype_ `float GetOffset() const;`
- L67 _public prototype_ `bool SetOffset(float InOffset);`
- L68 _public prototype_ `FVector2D GetSize() const;`
- L69 _public prototype_ `FVector2D GetPosition() const;`
- L70 _public function_ `void SetIndex(int32 InNewIndex)`
- L72 _public prototype_ `void DragStart();`
- L73 _public prototype_ `bool DragUpdate();` — Returns true if successfully updated
- L74 _public prototype_ `void DragEnd();`
- L76 _public prototype_ `TSharedPtr<SAvaLevelViewportFrame> GetViewportFrame() const;`
- L78 _public prototype_ `TSharedPtr<FUICommandList> GetGetCommandList();`
- L81 _public prototype_ `virtual FReply OnMouseButtonDown(const FGeometry& Geometry, const FPointerEvent& PointerEvent) override;`
- L82 _public prototype_ `virtual FReply OnMouseButtonUp(const FGeometry& Geometry, const FPointerEvent& PointerEvent) override;`
- L83 _public prototype_ `virtual FReply OnMouseMove(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L84 _public prototype_ `virtual FReply OnDragDetected(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L85 _public prototype_ `virtual int32 OnPaint(const FPaintArgs& InPaintArgs, const FGeometry& InAllottedGeometry, const FSlateRect& InMyCullingRect, FSlateWindowElementList& OutDrawElements, int32 InLayerId, const FWidgetStyle& InWidgetStyle, bool bInParentEnabled) const override;`
- L90 _protected member_ `TWeakPtr<SAvaLevelViewportFrame> ViewportFrameWeak;`
- L91 _protected member_ `int32 Index;`
- L92 _protected member_ `FAvaViewportGuideInfo Info;`
- L93 _protected member_ `bool bBeingDragged;`
- L94 _protected member_ `bool bDragRemove;`
- L95 _protected member_ `FVector2f LastMouseDownLocation;`
- L96 _protected member_ `FDateTime LastClickTime;`
- L97 _protected member_ `FVector2f LastClickLocation;`
- L98 _protected member_ `TSharedPtr<FUICommandList> CommandList;`
- L100 _protected prototype_ `FLinearColor GetColor() const;`
- L103 _protected prototype_ `virtual TOptional<EMouseCursor::Type> GetCursor() const override;`
- L106 _protected prototype_ `void UpdateGuideData() const;`
- L108 _protected prototype_ `void OpenRightClickMenu();`
- L110 _protected prototype_ `void BindCommands();`
- L112 _protected prototype_ `ECheckBoxState GetEnabledCheckState() const;`
- L113 _protected prototype_ `bool CanToggleEnable() const;`
- L114 _protected prototype_ `void ToggleEnabled();`
- L116 _protected prototype_ `ECheckBoxState GetLockedCheckState() const;`
- L117 _protected prototype_ `void ToggleLocked();`
- L119 _protected prototype_ `void RemoveGuide();`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheLevelViewport/Private/Widgets/SAvaLevelViewportPixelGrid.h` (Private)


#### class `SAvaLevelViewportPixelGrid`  
`class SAvaLevelViewportPixelGrid : public SCompoundWidget`  
_L10-29_
- inherits: `SCompoundWidget`
- L13 _public function_ `SLATE_BEGIN_ARGS(SAvaLevelViewportPixelGrid)`
- L15 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedRef<FAvaLevelViewportClient> InAvaLevelViewportClient);`
- L20 _public prototype_ `virtual int32 OnPaint(const FPaintArgs& InPaintArgs, const FGeometry& InAllottedGeometry, const FSlateRect& InMyCullingRect, FSlateWindowElementList& OutDrawElements, int32 InLayerId, const FWidgetStyle& InWidgetStyle, bool bInParentEnabled) const override;`
- L25 _protected member_ `TWeakPtr<FAvaLevelViewportClient> AvaLevelViewportClientWeak;`
- L27 _protected prototype_ `void DrawGrid(const FPaintArgs& InPaintArgs, const FGeometry& InAllottedGeometry, const FSlateRect& InMyCullingRect, FSlateWindowElementList& OutDrawElements, int32& InOutLayerId, const FLinearColor& InGridColor, const float InGridThickness) const;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheLevelViewport/Private/Widgets/SAvaLevelViewportRuler.h` (Private)


#### class `SAvaLevelViewportRuler`  
`class SAvaLevelViewportRuler : public UE::AvaLevelViewport::Private::SRuler`  
_L9-35_
- inherits: `UE::AvaLevelViewport::Private::SRuler`
- L12 _public function_ `SLATE_BEGIN_ARGS(SAvaLevelViewportRuler) : _Orientation(Orient_Horizontal)`
- L17 _public prototype_ `SLATE_ARGUMENT(EOrientation, Orientation) SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedPtr<SAvaLevelViewportFrame> InViewportFrame);`
- L23 _public prototype_ `virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L24 _public prototype_ `virtual FReply OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L25 _public prototype_ `virtual FReply OnDragDetected(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L26 _public prototype_ `virtual int32 OnPaint(const FPaintArgs& InArgs, const FGeometry& InAllottedGeometry, const FSlateRect& InMyCullingRect, FSlateWindowElementList& OutDrawElements, int32 InLayerId, const FWidgetStyle& InWidgetStyle, bool bInParentEnabled) const override;`
- L31 _protected member_ `TWeakPtr<SAvaLevelViewportFrame> ViewportFrameWeak;`
- L34 _protected member_ `EOrientation AccessibleOrientation;` — This is private in the parent class.

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheLevelViewport/Private/Widgets/SAvaLevelViewportSafeFrames.h` (Private)


#### class `SAvaLevelViewportSafeFrames`  
`class SAvaLevelViewportSafeFrames : public SCompoundWidget`  
_L10-30_
- inherits: `SCompoundWidget`
- L13 _public function_ `SLATE_BEGIN_ARGS(SAvaLevelViewportSafeFrames)`
- L15 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedRef<FAvaLevelViewportClient> InAvaLevelViewportClient);`
- L20 _public prototype_ `virtual int32 OnPaint(const FPaintArgs& InPaintArgs, const FGeometry& InAllottedGeometry, const FSlateRect& InMyCullingRect, FSlateWindowElementList& OutDrawElements, int32 InLayerId, const FWidgetStyle& InWidgetStyle, bool bInParentEnabled) const override;`
- L25 _protected member_ `TWeakPtr<FAvaLevelViewportClient> AvaLevelViewportClientWeak;`
- L27 _protected prototype_ `void DrawSafeFrame(const FPaintArgs& InPaintArgs, const FGeometry& InAllottedGeometry, const FSlateRect& InMyCullingRect, FSlateWindowElementList& OutDrawElements, int32& InOutLayerId, float InScreenPercentage, const FLinearColor& InLineColor, const float InLineThickness) const;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheLevelViewport/Private/Widgets/SAvaLevelViewportScreenGrid.h` (Private)


#### class `SAvaLevelViewportScreenGrid`  
`class SAvaLevelViewportScreenGrid : public SCompoundWidget`  
_L10-30_
- inherits: `SCompoundWidget`
- L13 _public function_ `SLATE_BEGIN_ARGS(SAvaLevelViewportScreenGrid)`
- L15 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedRef<FAvaLevelViewportClient> InAvaLevelViewportClient);`
- L20 _public prototype_ `virtual int32 OnPaint(const FPaintArgs& InPaintArgs, const FGeometry& InAllottedGeometry, const FSlateRect& InMyCullingRect, FSlateWindowElementList& OutDrawElements, int32 InLayerId, const FWidgetStyle& InWidgetStyle, bool bInParentEnabled) const override;`
- L25 _protected member_ `TWeakPtr<FAvaLevelViewportClient> AvaLevelViewportClientWeak;`
- L27 _protected prototype_ `void DrawGrid(const FPaintArgs& InPaintArgs, const FGeometry& InAllottedGeometry, const FSlateRect& InMyCullingRect, FSlateWindowElementList& OutDrawElements, int32& InOutLayerId, float InGridSizeSeparation, const FLinearColor& InGridColor, const float InGridThickness) const;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheLevelViewport/Private/Widgets/SAvaLevelViewportSnapIndicators.h` (Private)


#### class `SAvaLevelViewportSnapIndicators`  
`class SAvaLevelViewportSnapIndicators : public SCompoundWidget`  
_L10-30_
- inherits: `SCompoundWidget`
- L13 _public function_ `SLATE_BEGIN_ARGS(SAvaLevelViewportSnapIndicators)`
- L15 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedRef<FAvaLevelViewportClient> InAvaLevelViewportClient);`
- L20 _public prototype_ `virtual int32 OnPaint(const FPaintArgs& InPaintArgs, const FGeometry& InAllottedGeometry, const FSlateRect& InMyCullingRect, FSlateWindowElementList& OutDrawElements, int32 InLayerId, const FWidgetStyle& InWidgetStyle, bool bInParentEnabled) const override;`
- L25 _protected member_ `TWeakPtr<FAvaLevelViewportClient> AvaLevelViewportClientWeak;`
- L27 _protected prototype_ `void DrawIndicator(const FPaintArgs& InPaintArgs, const FGeometry& InAllottedGeometry, const FSlateRect& InMyCullingRect, FSlateWindowElementList& OutDrawElements, int32& InOutLayerId, float InPosition, EOrientation InLineOrientation, const FLinearColor& InLineColor, const float InLineThickness) const;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheLevelViewport/Private/Widgets/SAvaLevelViewportStatusBar.h` (Private)


#### class `SAvaLevelViewportStatusBar`  
`class SAvaLevelViewportStatusBar : public SCompoundWidget`  
_L118-130_
- inherits: `SCompoundWidget`
- L121 _public function_ `SLATE_BEGIN_ARGS(SAvaLevelViewportStatusBar)`
- L122 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedPtr<SAvaLevelViewportFrame> InViewportFrame);`
- L126 _public function_ `TSharedPtr<SAvaLevelViewportFrame> GetViewportFrameWeak() const`
- L129 _protected member_ `TWeakPtr<SAvaLevelViewportFrame> ViewportFrameWeak;`

#### Free symbols / members of external scopes

- L21 _namespace_ `namespace UE`
- L21 _namespace_ `namespace AvaLevelViewport` (scope `UE`)
- L21 _namespace_ `namespace Private` (scope `UE::AvaLevelViewport`)
- L23 _namespace_ `namespace ViewportStatusBarButton` (scope `UE::AvaLevelViewport::Private`)
- L25 _variable_ `const FSlateColor ActiveColor = FSlateColor(FLinearColor(0.0f, 0.45f, 0.9f, 1.0f));` (scope `UE::AvaLevelViewport::Private::ViewportStatusBarButton`)
- L26 _variable_ `const FSlateColor EnabledColor = FSlateColor(FStyleColors::AccentGray.GetSpecifiedColor());` (scope `UE::AvaLevelViewport::Private::ViewportStatusBarButton`)
- L27 _variable_ `const FSlateColor DisabledColor = FSlateColor(FLinearColor(0.5f, 0.1f, 0.1f, 1.0f));` (scope `UE::AvaLevelViewport::Private::ViewportStatusBarButton`)
- L28 _variable_ `const FMargin Padding = FMargin(0.f, 1.f, 0.f, 2.f);` (scope `UE::AvaLevelViewport::Private::ViewportStatusBarButton`)
- L30 _variable_ `static const FButtonStyle* Style = &FAppStyle::Get().GetWidgetStyle<FButtonStyle>("Sim` (scope `UE::AvaLevelViewport::Private::ViewportStatusBarButton`)
- L31 _variable_ `static const FMargin Margin = FMargin(1.0f, 2.0f, 1.0f, 2.0f);` (scope `UE::AvaLevelViewport::Private::ViewportStatusBarButton`)
- L32 _variable_ `static const FVector2D ImageSize = FVector2D(16.0f, 16.0f);` (scope `UE::AvaLevelViewport::Private::ViewportStatusBarButton`)
- L35 _function_ `template<typename InWidgetType> TSharedRef<SButton> MakeButton( InWidgetType* InWidget, TSharedPtr<FUICommandInfo> InCommandInfo, const FSlateBrush* InBrush, FOnClicked::TMethodPtr<InWidgetType> InCallback, TAttribute<bool>::FGetter::TConstMethodPtr<InWidgetType> InEnabledFunc, TAttribute<FSlateColor>::FGetter::TConstMethodPtr<InWidgetType> InColorFunc)` (scope `UE::AvaLevelViewport::Private::ViewportStatusBarButton`)
- L58 _function_ `template<typename InGetType, typename InBrushType, typename InColorType> TSharedRef<SComboButton> MakeMenuButton( const FText& InTooltip, InGetType InGetMenuContent, InBrushType InBrush, InColorType InColor)` (scope `UE::AvaLevelViewport::Private::ViewportStatusBarButton`)
- L80 _function_ `template<typename InGetType, typename InBrushType, typename InColorType> TSharedRef<SAvaMultiComboButton> MakeMultiMenuButton( const FText& InTooltip, InGetType InGetMenuContent, InBrushType InBrush, InColorType InColor, FOnClicked InClicked)` (scope `UE::AvaLevelViewport::Private::ViewportStatusBarButton`)

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheLevelViewport/Private/Widgets/SAvaLevelViewportStatusBarButtons.h` (Private)


#### class `SAvaLevelViewportStatusBarButtons`  
`class SAvaLevelViewportStatusBarButtons : public SCompoundWidget`  
_L14-125_
- inherits: `SCompoundWidget`
- L17 _public function_ `SLATE_BEGIN_ARGS(SAvaLevelViewportStatusBarButtons)`
- L18 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedPtr<SAvaLevelViewportFrame> InViewportFrame);`
- L22 _public function_ `TSharedPtr<SAvaLevelViewportFrame> GetViewportFrameWeak() const`
- L25 _protected member_ `TWeakPtr<SAvaLevelViewportFrame> ViewportFrameWeak;`
- L27 _protected member_ `TSharedPtr<SWidget> BackgroundTextureSelector;`
- L29 _protected member_ `TSharedPtr<SWidget> PostProcessOpacitySlider;`
- L31 _protected member_ `TSharedPtr<SWidget> GridSizeSlider;`
- L33 _protected member_ `TSharedPtr<SWidget> TextureOverlayTextureSelector;`
- L35 _protected member_ `TSharedPtr<SWidget> TextureOverlayOpacitySlider;`
- L37 _protected member_ `TSharedPtr<SWidget> TextureOverlayStretchCheckBox;`
- L39 _protected prototype_ `void CreateContextMenuWigets();`
- L41 _protected prototype_ `void PopulateActorButtons(TSharedPtr<SHorizontalBox> InContainer);`
- L42 _protected prototype_ `void PopulateViewportButtons(TSharedPtr<SHorizontalBox> InContainer);`
- L45 _protected prototype_ `FSlateColor GetActorAlignmentColor() const;` — Actor
- L46 _protected prototype_ `bool GetActorAlignmentEnabled() const;`
- L47 _protected prototype_ `TSharedRef<SWidget> GetActorAlignmentMenuContent() const;`
- L48 _protected prototype_ `TSharedRef<SWidget> GetActorColorMenuContent() const;`
- L50 _protected prototype_ `FSlateColor GetAnimatorButtonMuteColor() const;`
- L51 _protected prototype_ `FSlateColor GetAnimatorButtonUnmuteColor() const;`
- L52 _protected prototype_ `bool GetAnimatorButtonEnabled() const;`
- L53 _protected prototype_ `FReply EnableAnimators();`
- L54 _protected prototype_ `FReply DisableAnimators();`
- L57 _protected prototype_ `bool GetPostProcessEnabled() const;` — Post Process
- L58 _protected prototype_ `TSharedRef<SWidget> GetPostProcessMenuContent();`
- L60 _protected prototype_ `bool GetPostProcessEnabledMenu(const FToolMenuContext& InContext) const;`
- L61 _protected prototype_ `ECheckBoxState GetPostProcessActiveMenu(const FToolMenuContext& InContext, EAvaViewportPostProcessType InPostProcessType) const;`
- L62 _protected prototype_ `void TogglePostProcessMenu(const FToolMenuContext& InContext, EAvaViewportPostProcessType InPostProcessType);`
- L65 _protected prototype_ `FSlateColor GetToggleViewportToolbarColor() const;` — Viewport
- L66 _protected prototype_ `bool GetToggleViewportToolbarEnabled() const;`
- L67 _protected prototype_ `FReply ToggleViewportToolbar();`
- L69 _protected prototype_ `FSlateColor GetHighResScreenshotColor() const;`
- L70 _protected prototype_ `bool GetHighResScreenshotEnabled() const;`
- L71 _protected prototype_ `FReply HighResScreenshot();`
- L73 _protected prototype_ `FSlateColor GetToggleGuidesColor() const;`
- L74 _protected prototype_ `bool GetToggleGuidesEnabled() const;`
- L75 _protected prototype_ `FReply ToggleGuides();`
- L77 _protected prototype_ `FSlateColor GetToggleOverlayColor() const;`
- L78 _protected prototype_ `bool GetToggleOverlayEnabled() const;`
- L79 _protected prototype_ `FReply ToggleOverlay();`
- L81 _protected prototype_ `FSlateColor GetToggleBoundingBoxesColor() const;`
- L82 _protected prototype_ `bool GetToggleBoundingBoxesEnabled() const;`
- L83 _protected prototype_ `FReply ToggleBoundingBoxes();`
- L85 _protected prototype_ `FSlateColor GetToggleIsolateActorsColor() const;`
- L86 _protected prototype_ `bool GetToggleIsolateActorsEnabled() const;`
- L87 _protected prototype_ `FReply ToggleIsolateActors();`
- L89 _protected prototype_ `FSlateColor GetToggleSafeFramesColor() const;`
- L90 _protected prototype_ `bool GetToggleSafeFramesEnabled() const;`
- L91 _protected prototype_ `FReply ToggleSafeFrames();`
- L93 _protected prototype_ `FSlateColor GetToggleGameViewColor() const;`
- L94 _protected prototype_ `bool GetToggleGameViewEnabled() const;`
- L95 _protected prototype_ `FReply ToggleGameView();`
- L97 _protected prototype_ `FSlateColor GetToggleSnapColor() const;`
- L98 _protected prototype_ `bool GetToggleSnapEnabled() const;`
- L99 _protected prototype_ `FReply ToggleSnap();`
- L101 _protected prototype_ `TSharedRef<SWidget> GetSnappingMenuContent() const;`
- L103 _protected prototype_ `FSlateColor GetToggleShapeEditorOverlayColor() const;`
- L104 _protected prototype_ `bool GetToggleShapeEditorOverlayEnabled() const;`
- L105 _protected prototype_ `FReply ToggleShapeEditorOverlay();`
- L107 _protected prototype_ `FSlateColor GetToggleGridColor() const;`
- L108 _protected prototype_ `bool GetToggleGridEnabled() const;`
- L109 _protected prototype_ `FReply ToggleGrid();`
- L111 _protected prototype_ `TSharedRef<SWidget> GetGridMenuContent() const;`
- L113 _protected prototype_ `bool CanChangeGridSize() const;`
- L114 _protected prototype_ `void OnGridSizeChanged(int32 InNewValue) const;`
- L115 _protected prototype_ `void OnGridSizeCommitted(int32 InNewValue, ETextCommit::Type InCommitType) const;`
- L117 _protected prototype_ `bool GetViewportInfoEnabled() const;`
- L118 _protected prototype_ `FSlateColor GetViewportInfoColor() const;`
- L119 _protected prototype_ `TSharedRef<SWidget> GetViewportInfoWidget() const;`
- L121 _protected prototype_ `FSlateColor GetTextureOverlayColor() const;`
- L122 _protected prototype_ `bool GetTextureOverlayEnabled() const;`
- L123 _protected prototype_ `TSharedRef<SWidget> GetTextureOverlayMenuContent();`
- L124 _protected prototype_ `FReply ToggleTextureOverlay();`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheLevelViewport/Private/Widgets/SAvaLevelViewportStatusBarTransformSettings.h` (Private)


#### class `SAvaLevelViewportStatusBarTransformSettings`  
`class SAvaLevelViewportStatusBarTransformSettings : public SCompoundWidget`  
_L14-56_
- inherits: `SCompoundWidget`
- L17 _public function_ `SLATE_BEGIN_ARGS(SAvaLevelViewportStatusBarTransformSettings)`
- L18 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedPtr<SAvaLevelViewportFrame> InViewportFrame);`
- L21 _public function_ `TSharedPtr<SAvaLevelViewportFrame> GetViewportFrameWeak() const`
- L24 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L28 _protected member_ `TWeakPtr<SAvaLevelViewportFrame> ViewportFrameWeak;`
- L29 _protected member_ `TSharedPtr<FAvaLevelViewportComponentTransformDetails> TransformDetails;`
- L30 _protected member_ `TSharedPtr<SWidgetSwitcher> Switcher;`
- L31 _protected member_ `TArray<FPropertyRowExtensionButton> KeyframeButtons;`
- L33 _protected prototype_ `TSharedRef<SHorizontalBox> CreateLocationWidgets();`
- L34 _protected prototype_ `TSharedRef<SHorizontalBox> CreateRotationWidgets();`
- L35 _protected prototype_ `TSharedRef<SHorizontalBox> CreateScaleWidgets();`
- L37 _protected prototype_ `void CreateKeyframeButtons();`
- L38 _protected prototype_ `void UpdateKeyframeButtons();`
- L40 _protected prototype_ `bool IsResetLocationEnabled() const;`
- L41 _protected prototype_ `FSlateColor GetResetLocationColor() const;`
- L42 _protected prototype_ `FReply OnResetLocationClicked();`
- L44 _protected prototype_ `bool IsResetRotationEnabled() const;`
- L45 _protected prototype_ `FSlateColor GetResetRotationColor() const;`
- L46 _protected prototype_ `FReply OnResetRotationClicked();`
- L48 _protected prototype_ `bool IsResetScaleEnabled() const;`
- L49 _protected prototype_ `FSlateColor GetResetScaleColor() const;`
- L50 _protected prototype_ `FReply OnResetScaleClicked();`
- L52 _protected prototype_ `bool IsKeyframeEnabled(int32 InButtonIndex) const;`
- L53 _protected prototype_ `const FSlateBrush* GetKeyframeIcon(int32 InButtonIndex) const;`
- L54 _protected prototype_ `FText GetKeyframeToolTip(int32 InButtonIndex) const;`
- L55 _protected prototype_ `FReply OnKeyframeClicked(int32 InButtonIndex);`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheLevelViewport/Private/Widgets/SAvaLevelViewportTextureOverlay.h` (Private)


#### class `SAvaLevelViewportTextureOverlay`  
`class SAvaLevelViewportTextureOverlay: public SCompoundWidget`  
_L14-44_
- inherits: `SCompoundWidget`
- L17 _public function_ `SLATE_BEGIN_ARGS(SAvaLevelViewportTextureOverlay)`
- L21 _public prototype_ `SAvaLevelViewportTextureOverlay();`
- L24 _public prototype_ `void Construct(const FArguments& InArgs, TSharedRef<FAvaLevelViewportClient> InAvaLevelViewportClient);`
- L27 _public prototype_ `virtual int32 OnPaint(const FPaintArgs& InPaintArgs, const FGeometry& InAllottedGeometry, const FSlateRect& InMyCullingRect, FSlateWindowElementList& OutDrawElements, int32 InLayerId, const FWidgetStyle& InWidgetStyle, bool bInParentEnabled) const override;`
- L32 _protected member_ `TWeakPtr<FAvaLevelViewportClient> AvaLevelViewportClientWeak;`
- L33 _protected member_ `TStrongObjectPtr<UTexture> TextureStrong;`
- L34 _protected member_ `FSlateImageBrush TextureBrush;`
- L36 _protected prototype_ `void DrawOverlay(const FPaintArgs& InPaintArgs, const FGeometry& InAllottedGeometry, const FSlateRect& InMyCullingRect, FSlateWindowElementList& OutDrawElements, int32& InOutLayerId, UTexture* InTexture, float InOpacity, bool bInStretch) const;`
- L39 _protected prototype_ `void OnAvaViewportSettingsChanged(const UAvaViewportSettings* InSettings, FName InSetting);`
- L41 _protected prototype_ `void SetTexture(UTexture* InTexture);`
- L43 _protected prototype_ `void SetOpacity(float InOpacity);`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheLevelViewport/Private/Widgets/SAvaViewportInfo.h` (Private)


#### class `SAvaViewportInfo`  
`class SAvaViewportInfo : public SCompoundWidget`  
_L13-42_
- inherits: `SCompoundWidget`
- L15 _private function_ `SLATE_DECLARE_WIDGET(SAvaViewportInfo, SCompoundWidget) SLATE_BEGIN_ARGS(SAvaViewportInfo)`
- L21 _public prototype_ `static TSharedRef<SAvaViewportInfo> CreateInstance(const TSharedRef<IToolkitHost>& InToolkitHost);`
- L23 _public prototype_ `void Construct(const FArguments& Args, const TSharedRef<IToolkitHost>& InToolkitHost);`
- L26 _protected member_ `TWeakPtr<IToolkitHost> ToolkitHostWeak;`
- L28 _protected prototype_ `FVector2f GetViewportSizeForActiveViewport() const;`
- L29 _protected prototype_ `FIntPoint GetVirtualSizeForActiveViewport() const;`
- L30 _protected prototype_ `FAvaVisibleArea GetVisibleAreaForActiveViewport() const;`
- L31 _protected prototype_ `FVector2f GetMouseLocationOnViewport() const;`
- L33 _protected prototype_ `FText GetViewportSize() const;`
- L34 _protected prototype_ `FText GetVirtualViewportSize() const;`
- L35 _protected prototype_ `FText GetViewportVisibleAreaSize() const;`
- L36 _protected prototype_ `FText GetCanvasVisibleAreaSize() const;`
- L37 _protected prototype_ `FText GetViewportZoomOffset() const;`
- L38 _protected prototype_ `FText GetCanvasZoomOffset() const;`
- L39 _protected prototype_ `FText GetMouseLocation() const;`
- L40 _protected prototype_ `FText GetVirtualMouseLocation() const;`
- L41 _protected prototype_ `FText GetZoomLevel() const;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheLevelViewport/Public/AvaLevelViewportCommands.h` (Public)


#### class `FAvaLevelViewportCommands`  
`class FAvaLevelViewportCommands : public TCommands<FAvaLevelViewportCommands>`  
_L7-98_
- inherits: `TCommands<FAvaLevelViewportCommands>`
- L10 _public prototype_ `static const FAvaLevelViewportCommands& GetExternal();`
- L12 _public prototype_ `static const FAvaLevelViewportCommands& GetInternal();`
- L14 _public prototype_ `FAvaLevelViewportCommands();`
- L17 _public prototype_ `virtual void RegisterCommands() override;`
- L21 _public member_ `TSharedPtr<FUICommandInfo> ToggleOverlay;` — Viewport
- L22 _public member_ `TSharedPtr<FUICommandInfo> ToggleBoundingBoxes;`
- L23 _public member_ `TSharedPtr<FUICommandInfo> ToggleIsolateActors;`
- L24 _public member_ `TSharedPtr<FUICommandInfo> ToggleSafeFrames;`
- L25 _public member_ `TSharedPtr<FUICommandInfo> ToggleChildActorLock;`
- L26 _public member_ `TSharedPtr<FUICommandInfo> ToggleShapeEditorOverlay;`
- L27 _public member_ `TSharedPtr<FUICommandInfo> TogglePostProcessNone;`
- L28 _public member_ `TSharedPtr<FUICommandInfo> TogglePostProcessBackground;`
- L29 _public member_ `TSharedPtr<FUICommandInfo> TogglePostProcessChannelRed;`
- L30 _public member_ `TSharedPtr<FUICommandInfo> TogglePostProcessChannelGreen;`
- L31 _public member_ `TSharedPtr<FUICommandInfo> TogglePostProcessChannelBlue;`
- L32 _public member_ `TSharedPtr<FUICommandInfo> TogglePostProcessChannelAlpha;`
- L33 _public member_ `TSharedPtr<FUICommandInfo> TogglePostProcessCheckerboard;`
- L34 _public member_ `TSharedPtr<FUICommandInfo> ToggleTextureOverlay;`
- L37 _public member_ `TSharedPtr<FUICommandInfo> CameraZoomInCenter;` — Camera
- L38 _public member_ `TSharedPtr<FUICommandInfo> CameraZoomOutCenter;`
- L39 _public member_ `TSharedPtr<FUICommandInfo> CameraPanLeft;`
- L40 _public member_ `TSharedPtr<FUICommandInfo> CameraPanRight;`
- L41 _public member_ `TSharedPtr<FUICommandInfo> CameraPanUp;`
- L42 _public member_ `TSharedPtr<FUICommandInfo> CameraPanDown;`
- L43 _public member_ `TSharedPtr<FUICommandInfo> CameraFrameActor;`
- L44 _public member_ `TSharedPtr<FUICommandInfo> CameraZoomReset;`
- L45 _public member_ `TSharedPtr<FUICommandInfo> CameraTransformReset;`
- L46 _public member_ `TSharedPtr<FUICommandInfo> CameraTransformUndo;`
- L47 _public member_ `TSharedPtr<FUICommandInfo> CameraTransformRedo;`
- L50 _public member_ `TSharedPtr<FUICommandInfo> ToggleGrid;` — Grid
- L51 _public member_ `TSharedPtr<FUICommandInfo> ToggleGridAlwaysVisible;`
- L52 _public member_ `TSharedPtr<FUICommandInfo> IncreaseGridSize;`
- L53 _public member_ `TSharedPtr<FUICommandInfo> DecreaseGridSize;`
- L56 _public member_ `TSharedPtr<FUICommandInfo> ToggleSnapping;` — Snapping
- L57 _public member_ `TSharedPtr<FUICommandInfo> ToggleGridSnapping;`
- L58 _public member_ `TSharedPtr<FUICommandInfo> ToggleScreenSnapping;`
- L59 _public member_ `TSharedPtr<FUICommandInfo> ToggleActorSnapping;`
- L62 _public member_ `TSharedPtr<FUICommandInfo> VirtualSizeDisable;` — Virtual size
- L63 _public member_ `TSharedPtr<FUICommandInfo> VirtualSize1920x1080;`
- L64 _public member_ `TSharedPtr<FUICommandInfo> VirtualSizeAspectRatioUnlocked;`
- L65 _public member_ `TSharedPtr<FUICommandInfo> VirtualSizeAspectRatioLocked;`
- L66 _public member_ `TSharedPtr<FUICommandInfo> VirtualSizeAspectRatioLockedToCamera;`
- L69 _public member_ `TSharedPtr<FUICommandInfo> ToggleGuides;` — Guides
- L70 _public member_ `TSharedPtr<FUICommandInfo> AddGuideHorizontal;`
- L71 _public member_ `TSharedPtr<FUICommandInfo> AddGuideVertical;`
- L72 _public member_ `TSharedPtr<FUICommandInfo> ToggleGuideEnabled;`
- L73 _public member_ `TSharedPtr<FUICommandInfo> ToggleGuideLocked;`
- L74 _public member_ `TSharedPtr<FUICommandInfo> RemoveGuide;`
- L77 _public member_ `TSharedPtr<FUICommandInfo> ResetLocation;` — Transform
- L78 _public member_ `TSharedPtr<FUICommandInfo> ResetRotation;`
- L79 _public member_ `TSharedPtr<FUICommandInfo> ResetScale;`
- L80 _public member_ `TSharedPtr<FUICommandInfo> ResetTransform;`
- L83 _public member_ `TSharedPtr<FUICommandInfo> DisableAnimators;` — Animator
- L84 _public member_ `TSharedPtr<FUICommandInfo> EnableAnimators;`
- L90 _private prototype_ `void RegisterViewportCommands();`
- L91 _private prototype_ `void RegisterCameraCommands();`
- L92 _private prototype_ `void RegisterGridCommands();`
- L93 _private prototype_ `void RegisterSnappingCommands();`
- L94 _private prototype_ `void RegisterVirtualSizeCommands();`
- L95 _private prototype_ `void RegisterGuideCommands();`
- L96 _private prototype_ `void RegisterTransformCommands();`
- L97 _private prototype_ `void RegisterAnimatorCommands();`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheLevelViewport/Public/AvaLevelViewportLayoutEntity.h` (Public)


#### class `FAvaLevelViewportLayoutEntity`  
`class FAvaLevelViewportLayoutEntity : public ILevelViewportLayoutEntity`  
_L12-36_
- inherits: `ILevelViewportLayoutEntity`
- L15 _public prototype_ `FAvaLevelViewportLayoutEntity(const FAssetEditorViewportConstructionArgs& InArgs, TSharedPtr<ILevelEditor> InLevelEditor);`
- L17 _public prototype_ `static FName GetStaticType();`
- L20 _public prototype_ `virtual TSharedPtr<SLevelViewport> AsLevelViewport() const override;`
- L21 _public prototype_ `virtual TSharedRef<SWidget> AsWidget() const override;`
- L22 _public prototype_ `virtual void SetKeyboardFocus() override;`
- L23 _public prototype_ `virtual void OnLayoutDestroyed() override;`
- L24 _public prototype_ `virtual void SaveConfig(const FString& InConfigSection) override;`
- L25 _public prototype_ `virtual FName GetType() const override;`
- L26 _public prototype_ `virtual void TakeHighResScreenShot() const override;`
- L27 _public prototype_ `virtual FLevelEditorViewportClient& GetLevelViewportClient() const override;`
- L28 _public prototype_ `virtual bool IsPlayInEditorViewportActive() const override;`
- L29 _public prototype_ `virtual void RegisterGameViewportIfPIE() override;`
- L33 _private prototype_ `TSharedPtr<SLevelViewport> GetViewportWidget() const;`
- L35 _private member_ `TSharedPtr<SAvaLevelViewportFrame> Viewport;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheLevelViewport/Public/ColorPicker/AvaViewportColorPickerActorClassRegistry.h` (Public)


#### struct `FAvaViewportColorPickerActorClassRegistry`  
`struct FAvaViewportColorPickerActorClassRegistry`  
_L13-34_
- L17 _public function_ `static void RegisterDefaultClassAdapter()`
- L24 _public function_ `static void RegisterClassAdapter(InArgTypes&&... InArgs)`
- L29 _public prototype_ `static void RegisterClassAdapter(UClass* InClass, const TSharedRef<IAvaViewportColorPickerAdapter>& InAdapter);`
- L31 _public prototype_ `static bool GetColorDataFromActor(const AActor* InActor, FAvaColorChangeData& OutColorData);`
- L33 _public prototype_ `static bool ApplyColorDataToActor(AActor* InActor, const FAvaColorChangeData& InColorData);`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheLevelViewport/Public/ColorPicker/AvaViewportColorPickerAdapter.h` (Public)


#### struct `CAvaViewportColorPickable`  
`struct CAvaViewportColorPickable`  
_L13-20_
- desc: Describes a type that implements: - GetColorData const member function that returns FAvaColorChangeData - SetColorData that accepts a const FAvaColorChangeData as a parameter
- L16 _public prototype_ `template <typename T> auto Requires(const T& InConstActor, FAvaColorChangeData& OutColorData, T& InMutableActor, const FAvaColorChangeData& InColorData)->decltype( OutColorData = InConstActor.GetColorData(), InMutableActor.SetColorData(InColorData) );`

#### struct `TAvaViewportColorPickerActorAdapter`  
`struct TAvaViewportColorPickerActorAdapter : IAvaViewportColorPickerAdapter`  
_L25-48_
- inherits: `IAvaViewportColorPickerAdapter`
- L27 _public prototype_ `virtual ~TAvaViewportColorPickerActorAdapter() override = default;`
- L30 _public function_ `virtual bool GetColorData(const AActor& InActor, FAvaColorChangeData& OutColorData) const override`
- L40 _public function_ `virtual void SetColorData(AActor& InActor, const FAvaColorChangeData& InColorData) const override`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheLevelViewport/Public/ColorPicker/IAvaViewportColorPickerAdapter.h` (Public)


#### struct `IAvaViewportColorPickerAdapter`  
`struct IAvaViewportColorPickerAdapter`  
_L8-15_
- L10 _public prototype_ `virtual ~IAvaViewportColorPickerAdapter() = default;`
- L12 _public prototype_ `virtual bool GetColorData(const AActor& InActor, FAvaColorChangeData& OutColorData) const = 0;`
- L14 _public prototype_ `virtual void SetColorData(AActor& InActor, const FAvaColorChangeData& InColorData) const = 0;`
