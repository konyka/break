# Plugins / ControlRigEditor

- module root: `Plugins/Animation/ControlRig/Source/ControlRigEditor`
- headers: 234; symbols: 6354
- symbol kinds: class=249, delegate=69, enum=24, enumerator=96, externvar=1, function=819, macro=22, member=1562, namespace=208, prototype=3105, struct=134, typedef=61, variable=4
- PrivateDependencyModuleNames: ActorPickerMode, AdvancedPreviewScene, AnimGraph, AnimGraphRuntime, AnimationCore, AnimationEditMode, AnimationEditor, AnimationEditorWidgets, AnimationWidgets, ApplicationCore, AssetDefinition, AssetTools, BlueprintGraph, Blutility, ClassViewer, Constraints, ContentBrowser, ContentBrowserData, ControlRig, ControlRigDeveloper, Core, CoreUObject, DesktopPlatform, DetailCustomizations, DeveloperSettings, EditorFramework, EditorInteractiveToolsFramework, EditorStyle, EditorWidgets, Engine, GraphEditor, InputCore, Json, KismetCompiler, KismetWidgets, LevelEditor, LevelSequence, LevelSequenceEditor, MessageLog, MovieScene, MovieSceneTools, MovieSceneTracks, Persona, PropertyAccessEditor, PropertyEditor, PropertyPath, PythonScriptPlugin, RigVM, RigVMDeveloper, RigVMEditor, SceneOutliner, Sequencer, SequencerCore, SequencerScripting, SequencerScriptingEditor, SequencerWidgets, Slate, SlateCore, TimeManagement, ToolMenus, ToolWidgets, TweeningUtils, TypedElementFramework, UMG, UMGEditor, UnrealEd, WorkspaceMenuStructure
- PublicDependencyModuleNames: AppFramework, CurveEditor, InteractiveToolsFramework, Kismet, MainFrame, RigVMEditor, TweeningUtilsEditor

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/AnimDetails/AnimDetailsFilter.h` (Private)


#### struct `UE::ControlRigEditor::FAnimDetailsFilter`  
`struct FAnimDetailsFilter`  
_L15-67_
- desc: Filters the details view used in anim details.
- L19 _public prototype_ `void Update(const FText& FilterText, const TArray<TObjectPtr<UAnimDetailsProxyBase>>& Proxies);` — Filters proxies given the filter text.
- L22 _public prototype_ `TArray<UAnimDetailsProxyBase*> GetFilteredProxies() const;` — Returns proxies that match the current filter
- L25 _public prototype_ `bool ContainsProperty(const UAnimDetailsProxyBase& Proxy, const FName& PropertyName) const;` — Returns true if the property is contained in the filter
- L28 _public prototype_ `bool ContainsProperty(const TSharedRef<IPropertyHandle>& PropertyHandle) const;` — Returns true if the property is contained in the filter
- L31 _public prototype_ `bool ContainsStructProperty(const TSharedRef<IPropertyHandle>& StructPropertyHandle) const;` — Returns true if the struct is contained in the filter
- L34 _public function_ `FSimpleMulticastDelegate& GetOnFilterChanged()` — Returns a delegate broadcast when the filtered proxies changed.
- L38 _private member_ `TArray<FString> SearchFragments;` — Fragments of the search string, trimmed, fragmented by whitespace
- L63 _private member_ `TArray<FAnimDetailsFilteredProperty> FilteredProperties;` — Properties matching the filter
- L66 _private member_ `FSimpleMulticastDelegate OnFilterChangedDelegate;` — Called when the filtered proxies changed

#### struct `UE::ControlRigEditor::FAnimDetailsFilter::FAnimDetailsFilteredProperty`  
`struct FAnimDetailsFilteredProperty`  
_L41-60_
- desc: Describes a property that is matching the current filter
- L44 _public prototype_ `static TOptional<FAnimDetailsFilteredProperty> TryCreate( const TArray<FString>& SearchFragments, UAnimDetailsProxyBase* InProxy, const FName& InPropertyName);` — Tries to create an instance. The returned optional is set if creation succeeded
- L49 _public prototype_ `bool operator==(const FAnimDetailsFilteredProperty& Other) const;`
- L52 _public member_ `const TWeakObjectPtr<UAnimDetailsProxyBase> WeakProxy;` — The proxy
- L55 _public member_ `const FName PropertyName;` — The property name
- L58 _private prototype_ `FAnimDetailsFilteredProperty() = default;`
- L59 _private prototype_ `FAnimDetailsFilteredProperty(UAnimDetailsProxyBase* InProxy, const FName& InPropertyName);`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace ControlRigEditor` (scope `UE`)

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/AnimDetails/AnimDetailsMultiEditUtil.h` (Private)


#### class `UE::ControlRigEditor::FAnimDetailsMultiEditUtil`  
`class FAnimDetailsMultiEditUtil`  
_L16-115_
- desc: Utility to edit many possibly unrelated properties of control proxies
- L20 _public prototype_ `static FAnimDetailsMultiEditUtil& Get();` — Returns the default multi edit util instance
- L28 _public prototype_ `void Join(UAnimDetailsProxyManager* ProxyManager, const TSharedRef<IPropertyHandle>& PropertyHandle);` — Lets a single proxy join the util so it can be multi edited along with other proxies @param ProxyManager			The proxy manager that owns the proxies being edited @param PropertyHandle		Property handle for the properties being edited
- L31 _public prototype_ `void Leave(const TWeakPtr<IPropertyHandle>& WeakPropertyHandle);` — Lets a proxy leave the util, e.g. on destruction
- L41 _public prototype_ `template <typename ValueType> void MultiEditSet(const UAnimDetailsProxyManager& ProxyManager, const ValueType Value, const TSharedRef<IPropertyHandle>& InstigatorProperty);` — Sets a value to all selected properties that joined this multi edit util. Supports math operations. @param ProxyManager			The proxy manager that owns the proxies and their properties @param StringValue			The value to set for the properties @param InstigatorProperty	The property that instigated this change ¨
- L53 _public prototype_ `template <typename ValueType> bool MultiEditMath(const UAnimDetailsProxyManager& ProxyManager, FString Expression, const TSharedRef<IPropertyHandle>& InstigatorProperty);` — Sets a value to all selected properties that joined this multi edit util. Supports math operations. @param ProxyManager			The proxy manager that owns the proxies and their properties @param Expression			The mathematical expression to apply for the properties @param InstigatorProperty	The property that instigated this change @return						True if a math operation was successfully applied. ¨
- L64 _public prototype_ `template <typename ValueType> void MultiEditChange(const UAnimDetailsProxyManager& ProxyManager, const ValueType Delta, const TSharedRef<IPropertyHandle>& InstigatorProperty, const bool bInteractive);` — Applies a delta to all selected properties that joined this multi edit util. @param ProxyManager			The proxy manager that owns the proxies and their properties @param Delta					The value to set for the properties @param InstigatorProperty	The property that instigated this change @param bInteractive			If true, the change is carried with interactive flags
- L67 _public function_ `bool IsInteractive() const` — True if the multi edit util is interactively changing values
- L74 _public prototype_ `template <typename ValueType> [[nodiscard]] bool GetInteractiveDelta(const TSharedRef<IPropertyHandle>& Property, ValueType& OutValue) const;` — Gets the interactive delta. Returns false if there is no interactive change on-going or the property is not being edited. This is only available to MultiEditChange during interactive changes, always fails otherwise.
- L79 _private prototype_ `template <typename ValueType> TArray<TSharedRef<IPropertyHandle>> GetPropertiesBeingEdited(const UAnimDetailsProxyManager& ProxyManager, const TSharedRef<IPropertyHandle>& InstigatorProperty);` — Updates the properties that are currently being edited
- L82 _private member_ `bool bIsInteractiveChangeOngoing = false;` — True while PerObjectChange is called interactively
- L85 _private member_ `TMap<TWeakObjectPtr<UAnimDetailsProxyManager>, TArray<TWeakPtr<IPropertyHandle>>> ProxyManagerToPropertiesMap;` — Map of proxy managers with those proxies that joined this util
- L108 _private member_ `FAnimDetailsVariantValue AccumulatedDelta;` — The accumulated delta from an interactive change
- L111 _private member_ `TArray<TSharedRef<IPropertyHandle>> PropertiesBeingEditedInteractively;` — Stores the properties that are being edited while interactively changing values
- L114 _private member_ `static TUniquePtr<FAnimDetailsMultiEditUtil> Instance;` — The proxy instance

#### struct `UE::ControlRigEditor::FAnimDetailsMultiEditUtil::FAnimDetailsVariantValue`  
`struct FAnimDetailsVariantValue`  
_L88-105_
- desc: Struct that allows to store and retrive values of different types
- L90 _public prototype_ `FAnimDetailsVariantValue() = default;`
- L93 _public prototype_ `template <typename ValueType> FAnimDetailsVariantValue(const ValueType Value);`
- L97 _public prototype_ `template <typename ValueType> void Set(ValueType Value);` — Sets the value
- L101 _public prototype_ `template <typename ValueType> ValueType Get() const;` — Gets the value. Returns 0 if it was not previously set
- L104 _private member_ `TVariant<double, int64, bool> VariantValue;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace ControlRigEditor` (scope `UE`)
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace ControlRigEditor` (scope `UE`)

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/AnimDetails/AnimDetailsNavigableWidgetRegistrar.h` (Private)


#### struct `UE::ControlRigEditor::FAnimDetailsNavigableWidgetRegistrar`  
`struct FAnimDetailsNavigableWidgetRegistrar`  
_L14-44_
- desc: Responsible to handle registration of navigable widgets with the navigable widget registry
- L23 _public prototype_ `void RegisterAsNavigable( UAnimDetailsProxyManager& ProxyManager, const TSharedRef<SWidget>& OwnerWidget, const TSharedRef<SWidget>& NavigableWidget);` — Registers a widget that can be navigated to with the navigable widget registry @param ProxyManager		The proxy manager that owns the registry @param OwnerWidget		The widget that owns the navigable widget @param NavigableWidget	The widget to navigate to
- L33 _public prototype_ `void RegisterAsNavigator( UAnimDetailsProxyManager& ProxyManager, const TSharedRef<SWidget>& NavigatorWidget, const TSharedRef<SWidget>& NavigateToOwner);` — Registers a widget that can navigate to an owner with the navigable widget registry. @param ProxyManager		The proxy manager that owns the registry @param NavigatorWidget	The widget that invokes the navigation @param NavigateToOwner	The owner widget to navigate to.
- L40 _private member_ `TWeakObjectPtr<UAnimDetailsProxyManager> WeakProxyManager;` — The proxy manager the widgets are registered with
- L43 _private member_ `TWeakPtr<SWidget> WeakOwnerWidget;` — The widget that owns this registrar

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace ControlRigEditor` (scope `UE`)

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/AnimDetails/AnimDetailsNavigableWidgetRegistry.h` (Private)


#### class `UE::ControlRigEditor::FAnimDetailsNavigableWidgetRegistry`  
`class FAnimDetailsNavigableWidgetRegistry`  
_L16-58_
- desc: Registry for navigable widgets, assuming an owner widget and an inner widget that actually can receive navigation. Used to navigate from property names or value wrappers (e.g. SAnimDetailsValueNumeric) to the actual value widgets. Given such an owner widget, GetNext will return the correct value widget to navigate to.
- L28 _public prototype_ `const TSharedPtr<SWidget> GetNext(const TSharedRef<SWidget>& OwnerWidget) const;` — Returns the next widget given the owner widget, whereas the owner widget can be either registered as navigator or as navigable owner. Returns nullptr if the widget is not registered with this registry.
- L32 _private prototype_ `bool IsWidgetVisible(const TSharedRef<SWidget>& Widget) const;` — Does a deep test if a widget is truly visible.
- L35 _private prototype_ `void RegisterNavigableWidget( const TSharedRef<SWidget>& InOwnerWidget, const TSharedRef<SWidget>& InNavigableWidget);` — Registers a widget that can be navigated to
- L40 _private prototype_ `void RegisterNavigatorWidget( const TSharedRef<SWidget>& InNavigatorWidget, const TSharedRef<SWidget>& InNavigateToWidget);` — Registers a widget that can be navigated to a navigable widget. Requires the navigable widget to be registered.
- L54 _private member_ `mutable TArray<FNavigableWidget> NavigableWidgets;` — The current navigable widgets
- L57 _private member_ `mutable TMap<TWeakPtr<SWidget>, TWeakPtr<SWidget>> WeakNavigatorToNavigableWidgetMap;` — The current navigator widgets with their navigate to widget

#### struct `UE::ControlRigEditor::FAnimDetailsNavigableWidgetRegistry::FNavigableWidget`  
`struct FNavigableWidget`  
_L45-51_
- desc: A widget that can be navigated to
- L47 _public prototype_ `FNavigableWidget(const TSharedRef<SWidget>& InWeakOwner, const TSharedRef<SWidget>& InWeakNavigableWidget);`
- L49 _public member_ `const TWeakPtr<SWidget> WeakOwner;`
- L50 _public member_ `const TWeakPtr<SWidget> WeakNavigableWidget;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace ControlRigEditor` (scope `UE`)

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/AnimDetails/AnimDetailsOptionsMenuContext.h` (Private)


#### class `UAnimDetailsOptionsMenuContext`  
`class UAnimDetailsOptionsMenuContext : public UObject`  
_L11-19_
- reflection: `UCLASS()`
- inherits: `UObject`
- desc: Menu context for the anim details options menu
- L18 _public member_ `TWeakPtr<UE::ControlRigEditor::SAnimDetailsOptions> WeakAnimDetailsOptions;` — The anim details options widget that uses this menu context

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace ControlRigEditor` (scope `UE`)

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/AnimDetails/AnimDetailsProxyManager.h` (Private)


#### class `UAnimDetailsProxyManager`  
`class UAnimDetailsProxyManager : public UObject , public FSelfRegisteringEditorUndoClient`  
_L32-182_
- reflection: `UCLASS()`
- inherits: `UObject,FSelfRegisteringEditorUndoClient`
- desc: Manages the instances of UAnimDetailsProxyBase for anim details. This is a rewrite of what was previously UControlRigDetailPanelControlProxies in ControlRigEditor/Private/EditMode/ControlRigControlsProxy.h.
- L39 _public prototype_ `UAnimDetailsProxyManager();`
- L42 _public prototype_ `virtual void BeginDestroy() override;`
- L46 _public prototype_ `void SetSuspended(const bool bEnabled);` — Suspends or resumes this manager. While the manager is suspended, its proxies are no longer updated.
- L49 _public prototype_ `TSharedPtr<ISequencer> GetSequencer() const;` — Returns the sequencer this proxy manager handles or nullptr if not currently assigned to a sequencer
- L52 _public prototype_ `void RequestUpdateProxies();` — Updates proxies on the next tick. Ignored if the manager is suspended.
- L58 _public prototype_ `void RequestUpdateProxyValues();` — Updates the proxy values on the next tick. Useful to let proxies know that values changed externally. Ignored if the manager is suspended.
- L61 _public function_ `FSimpleMulticastDelegate& GetOnProxiesChanged()` — Delegate broadcase when a displayed proxies changed
- L64 _public function_ `const TArray<TObjectPtr<UAnimDetailsProxyBase>>& GetExternalSelection() const` — Returns the proxies currently selected in anim outliner, control rig and sequencer.
- L67 _public prototype_ `UAnimDetailsSelection* GetAnimDetailsSelection();` — Returns the anim details selection object
- L70 _public prototype_ `const UAnimDetailsSelection* GetAnimDetailsSelection() const;` — Returns the anim details selection object, const
- L73 _public function_ `UE::ControlRigEditor::FAnimDetailsFilter& GetAnimDetailsFilter()` — Returns the filter for anim details
- L76 _public function_ `const UE::ControlRigEditor::FAnimDetailsFilter& GetAnimDetailsFilter() const` — Returns the filter for anim details, const
- L79 _public function_ `static const FName GetProxiesMemberNameChecked()` — Returns the member name of the proxies member
- L82 _public function_ `UE::ControlRigEditor::FAnimDetailsNavigableWidgetRegistry& GetNavigableWidgetRegistry()` — Returns the navigable widget registry that belongs to this proxy manager. Useful for navigation
- L86 _private prototype_ `virtual void PostUndo(bool bSuccess) override;`
- L87 _private prototype_ `virtual void PostRedo(bool bSuccess) override;`
- L91 _private prototype_ `void ClearSequencer();` — Clears the sequencer. This is useful to suspend this proxy manager.
- L94 _private prototype_ `[[nodiscard]] bool UpdateSequencer();` — Updates the sequencer this manager uses. Returns true if a sequencer was set successfully
- L97 _private prototype_ `void SetupBingings();` — Binds to other objects' events to update on their changes
- L100 _private prototype_ `void ReleaseBindings();` — Releases bindings to other objects' events
- L103 _private prototype_ `void OnControlRigShapeActorsRecreated();` — Called when control rig shape actors were recreated
- L106 _private prototype_ `void OnControlRigSelectionChanged(UControlRig* ControlRig, const FRigElementKey& RigElementKey, const bool bIsSelected);` — Called when a control rig element was selected
- L109 _private prototype_ `void OnSequencerSelectionChanged(TArray<FGuid> ObjectGuids);` — Called when the sequencer selection changed
- L112 _private prototype_ `void OnControlRigControlAdded(UControlRig* ControlRig, bool bIsAdded);` — Called when a control rig was added
- L115 _private prototype_ `void OnObjectsReplaced(const TMap<UObject*, UObject*>& OldToNewInstanceMap);` — Called from the editor when a blueprint object replacement has occurred. Useful to restore the control rig for proxies when it was replaced.
- L118 _private prototype_ `void ForceUpdateProxies();` — Updates all proxies.
- L121 _private prototype_ `void ForceUpdateProxyValues();` — Updates the proxy values.
- L124 _private prototype_ `void RemoveInvalidProxies();` — Removes any invalid proxy
- L127 _private prototype_ `[[nodiscard]] UAnimDetailsProxyBase* GetOrCreateControlRigProxy(UControlRig* ControlRig, FRigControlElement* ControlElement);` — Creates or updates a control rig proxy. Will reuse and update sequencer proxies with their related control rig element.
- L130 _private prototype_ `[[nodiscard]] UAnimDetailsProxyBase* GetOrCreateSequencerProxy(UObject* BoundObject, UMovieScenePropertyTrack* PropertyTrack, const TSharedPtr<FTrackInstancePropertyBindings>& Binding);` — Creates or updates a sequencer proxy.
- L133 _private prototype_ `UAnimDetailsProxyBase* NewProxyFromType(UAnimDetailsProxyManager* Owner, ERigControlType ControlType, const TObjectPtr<UEnum>& InEnumPtr, const FName& ProxyName) const;` — Creates a new anim details proxy
- L136 _private prototype_ `void ReevaluateConstraints();` — Reevaluates constraints
- L139 _private prototype_ `[[nodiscard]] bool TryGetControlTypeFromTrackType(const UMovieScenePropertyTrack& InPropertyTrack, ERigControlType& OutControlRigType) const;` — Tries to get a supported control type that is used for the specified property track.
- L142 _private prototype_ `TMap<FGuid, TArray<UMovieScenePropertyTrack*>> GetPropertyTracks(const TSharedRef<ISequencer>& Sequencer, const TArray<FGuid>& ObjectGuids) const;` — Returns a map of object guids with their sequencer property tracks
- L145 _private prototype_ `TArray<UObject*> GetBoundObjectsFromTrack(const TSharedRef<ISequencer>& Sequencer, const FGuid& ObjectGuid) const;` — Returns a an array of objects bound in sequencer which match provided object id
- L148 _private prototype_ `void AddProxyToExternalSelectionIfValid(UAnimDetailsProxyBase* Proxy);` — Convenience to add a proxy to ExternalSelection, only if the proxy is valid
- L151 _private member_ `bool bSuspended = true;` — While true, the manager is not updated
- L155 _private member_ `TArray<TObjectPtr<UAnimDetailsProxyBase>> Proxies;` — `UPROPERTY()` — The current proxies
- L159 _private member_ `TArray<TObjectPtr<UAnimDetailsProxyBase>> ExternalSelection;` — `UPROPERTY()` — The proxies that are currently selected in anim outliner, control rig and sequencer
- L163 _private member_ `TObjectPtr<UAnimDetailsSelection> AnimDetailsSelection;` — `UPROPERTY()` — The anim details selection
- L166 _private member_ `UE::ControlRigEditor::FAnimDetailsFilter AnimDetailsFilter;` — The filter used for anim details
- L169 _private member_ `UE::ControlRigEditor::FAnimDetailsNavigableWidgetRegistry NavigableWidgetRegistry;` — Registry for value widgets, useful for navigation
- L172 _private member_ `TWeakPtr<ISequencer> WeakSequencer;` — The sequencer object this manager currently handles
- L175 _private member_ `FSimpleMulticastDelegate OnProxiesChangedDelegate;` — Delegate broadcase when the selection changed
- L178 _private member_ `FTSTicker::FDelegateHandle RequestUpdateProxiesTickerHandle;` — Ticker handle for the RequestUpdateProxies member function
- L181 _private member_ `FTimerHandle RequestUpdateProxyValuesTimerHandle;` — Timer handle for the RequestUpdateProxyValues member function

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/AnimDetails/AnimDetailsSelection.h` (Private)


#### enum `UE::ControlRigEditor::EAnimDetailsSelectionType`  
`enum class EAnimDetailsSelectionType : uint8`  
_L20-25_
- desc: Describes the type of selection
- L22 _public enumerator_ `Select`
- L23 _public enumerator_ `Toggle`
- L24 _public enumerator_ `SelectRange`

#### struct `FAnimDetailsSelectionPropertyData`  
`struct FAnimDetailsSelectionPropertyData`  
_L30-76_
- reflection: `USTRUCT()`
- desc: Struct to describe a single property in an anim details proxy
- L34 _public prototype_ `FAnimDetailsSelectionPropertyData() = default;`
- L35 _public prototype_ `FAnimDetailsSelectionPropertyData(const FName& InPropertyName);`
- L38 _public prototype_ `void AddProxy(UAnimDetailsProxyBase* Proxy);` — Adds a proxy to this property data
- L41 _public function_ `bool IsSelected() const` — Returns true if this property is selected
- L44 _public function_ `void SetSelected(bool bSelected)` — Sets if the property is selected
- L47 _public function_ `bool IsVisible() const` — Returns true if this property is visible
- L50 _public function_ `void SetVisible(bool bVisible)` — Sets if the property is visible
- L53 _public function_ `const TArray<TWeakObjectPtr<UAnimDetailsProxyBase>>& GetProxiesBeingEdited() const` — Returns the proxies being edited
- L59 _public function_ `const FName& GetProperyName() const` — Returns the property name that relates to this data. Note, this is not a unique identifier, other property datas may use the same property name from different property paths.
- L64 _private member_ `TArray<TWeakObjectPtr<UAnimDetailsProxyBase>> WeakProxies;` — `UPROPERTY()` — The currently selected proxies that own the property. Maybe be multiple if proxies are multi edited on a details row
- L68 _private member_ `bool bIsSelected = false;` — `UPROPERTY()` — If true, the property is selected
- L71 _private member_ `bool bIsVisible = true;` — If true, the property is visible
- L75 _private member_ `FName PropertyName;` — `UPROPERTY()` — The property name for this data

#### class `UAnimDetailsSelection`  
`class UAnimDetailsSelection : public UObject`  
_L85-165_
- reflection: `UCLASS()`
- inherits: `UObject`
- desc: The selection in Anim Details. Note, the selection does not necessarily correspond to the selection in Anim Outliner or Sequencer/Curve Editor. Use UAnimDetailsProxyManager::GetExternalSelection to get the external selection.
- L90 _private typedef_ `using EAnimDetailsSelectionType = UE::ControlRigEditor::EAnimDetailsSelectionType;`
- L93 _public prototype_ `UAnimDetailsSelection();`
- L96 _public prototype_ `void SelectPropertyInProxies(const TArray<UAnimDetailsProxyBase*>& Proxies, const FName& PropertyName, const EAnimDetailsSelectionType SelectionType);` — Selects the property. Depending on selection type other properties may be selected. Note, all proxies need to share the same detail row ID (ensured).
- L99 _public prototype_ `void ClearSelection();` — Clears the selection
- L102 _public prototype_ `bool IsPropertySelected(const UAnimDetailsProxyBase* Proxy, const FName& PropertyName) const;` — Returns true if the property is selected. Note, hidden properties are never considered being selected.
- L105 _public prototype_ `bool IsPropertySelected(const TSharedRef<IPropertyHandle>& PropertyHandle) const;` — Returns true if the property is selected. Note, hidden properties are never considered being selected.
- L108 _public prototype_ `int32 GetNumSelectedProperties() const;` — Returns the number of selected properties
- L111 _public prototype_ `bool IsControlElementSelected(const UControlRig* ControlRig, const FRigControlElement* ControlElement) const;` — Returns true if the control element is selected. Note, hidden properties are never considered being selected.
- L114 _public prototype_ `TArray<UAnimDetailsProxyBase*> GetSelectedProxies() const;` — Returns the currently selected proxies
- L117 _public function_ `bool IsAnimLayersChangingSelection() const` — Returns true while anim layers is changing selection. Useful to avoid updating anim details to override its selection
- L121 _private prototype_ `void OnProxiesChanged();` — Called when proxies changed in the proxy manager
- L124 _private prototype_ `void OnAnimLayersSelected();` — Called when anim layers were selected
- L127 _private prototype_ `void OnFilterChanged();` — Called when the filter changed
- L130 _private prototype_ `void RequestPropagateSelectionToCurveEditor();` — Propagates the selection to curve editor on the next tick
- L133 _private prototype_ `void PropagateSelectionToCurveEditor();` — Propagates the selection to curve editor
- L139 _private prototype_ `FName MakeCommonPropertyID(const TArray<UAnimDetailsProxyBase*>& Proxies, const FName& PropertyName) const;` — Creates a property ID common to the proxies. Note the proxies are expected to share the same detail row ID (ensured). This property ID does not relate to any other engine implementation, it is specific to this selection class.
- L143 _private member_ `TMap<FName, FAnimDetailsSelectionPropertyData> PropertyIDToPropertyDataMap;` — `UPROPERTY()` — A property ID with its property data.
- L146 _private member_ `TMap<FName, FAnimDetailsSelectionPropertyData> RestorePropertyIDToPropertyDataMap;` — When updating, restores property data from this map and resets it
- L149 _private member_ `FName AnchorPropertyID;` — The anchor for selection when shift-multiselecting or name none if there is no anchor
- L152 _private member_ `bool bIsChangingSelection = false;` — True while changing selection
- L155 _private member_ `bool bIsAnimLayersChangingSelection = false;` — True while anim layers is changing selection. Useful to override its selection
- L158 _private member_ `TWeakObjectPtr<UAnimLayers> WeakAnimLayers;` — The current anim layers
- L161 _private member_ `FTimerHandle PropagateSelectionToCurveEditorTimerHandle;` — Timer handle to propagate the selection to the curve editor
- L164 _private member_ `FTimerHandle OnAnimLayersSelectedTimerHandle;` — Timer handle to used when anim layers were selected

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace Sequencer` (scope `UE`)
- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace ControlRigEditor` (scope `UE`)

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/AnimDetails/AnimDetailsSettings.h` (Private)


#### class `UAnimDetailsSettings`  
`class UAnimDetailsSettings : public UObject`  
_L9-26_
- reflection: `UCLASS(config = EditorPerProjectUserSettings)`
- inherits: `UObject`
- desc: Settings for Anim Details
- L17 _public member_ `bool bExpandTransformProperties = true;` — `UPROPERTY(config, EditAnywhere, Category = "Animation Settings")` — Expand transform properties in anim details
- L21 _public member_ `uint8 NumFractionalDigits = 2;` — `UPROPERTY(config, EditAnywhere, Category = "Animation Settings")` — The number of fractional digits displayed in anim details
- L25 _public member_ `bool bLMBSelectsRange = true;` — `UPROPERTY(config, EditAnywhere, Category = "Animation Settings")` — If true, selects a range when the left mouse button is down

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/AnimDetails/Customizations/AnimDetailsOverrideDetails.h` (Private)


#### class `UE::ControlRigEditor::FAnimDetailsOverrideDetails`  
`class FAnimDetailsOverrideDetails : public IPropertyTypeCustomization`  
_L17-31_
- inherits: `IPropertyTypeCustomization`
- desc: Details customization for Control Shape settings
- L20 _public function_ `static TSharedRef<class IPropertyTypeCustomization> MakeInstance()`
- L25 _public prototype_ `FAnimDetailsOverrideDetails();`
- L27 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L28 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> StructPropertyHandle, IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L30 _private member_ `TSharedPtr<FControlRigShapeNameList> ControlRigShapeNameList;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace ControlRigEditor` (scope `UE`)

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/AnimDetails/Customizations/AnimDetailsPropertyRowExtensions.h` (Private)


#### class `UE::ControlRigEditor::FAnimDetailsPropertyRowExtensions`  
`class FAnimDetailsPropertyRowExtensions`  
_L18-46_
- desc: Extends the property rows of anim details, inspired by Dynamic Material Editor
- L21 _public prototype_ `static FAnimDetailsPropertyRowExtensions& Get();`
- L23 _public prototype_ `~FAnimDetailsPropertyRowExtensions();`
- L26 _public prototype_ `void RegisterRowExtensions();` — Registers the extensions with the property editor module
- L29 _public prototype_ `void UnregisterRowExtensions();` — Unregisters the extensions from the property editor module
- L33 _private prototype_ `static void CreatePropertyRowExtension(const FOnGenerateGlobalRowExtensionArgs& InArgs, TArray<FPropertyRowExtensionButton>& OutExtensions);` — Creates the anim details row extension
- L36 _private prototype_ `static void ExtendContextMenu(UToolMenu* InToolMenu);` — Extends the context menu
- L39 _private prototype_ `static void ExtendContextMenu(FToolMenuSection& InSection, const TSharedRef<IPropertyHandle>& InPropertyHandle, const TArray<UAnimDetailsProxyBase*>& InProxies);` — Extends the context menu for the specific section and property handle for proxies
- L42 _private member_ `FDelegateHandle RowExtensionHandle;` — Delegate handle to track registration of the customization
- L45 _private member_ `int32 RegistrationCount = 0;` — Number of active registrations — the extension is bound while this is > 0

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace ControlRigEditor` (scope `UE`)

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/AnimDetails/Customizations/AnimDetailsProxyDetails.h` (Private)


#### class `UE::ControlRigEditor::FAnimDetailsProxyDetails`  
`class FAnimDetailsProxyDetails : public IDetailCustomization`  
_L12-29_
- inherits: `IDetailCustomization`
- desc: Details customization for classes that inherit UAnimDetailsProxyBase
- L16 _public prototype_ `FAnimDetailsProxyDetails();`
- L19 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Creates an instance of this details customization
- L23 _protected prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailLayout) override;`
- L28 _private prototype_ `FReply OnHeaderCategoryRowClicked(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent);` — Called when the header category row (the category row we use to mock up a header row) was clicked

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace ControlRigEditor` (scope `UE`)

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/AnimDetails/Customizations/AnimDetailsProxyManagerDetails.h` (Private)


#### class `UE::ControlRigEditor::FAnimDetailProxyManagerDetails`  
`class FAnimDetailProxyManagerDetails : public IDetailCustomization`  
_L10-21_
- inherits: `IDetailCustomization`
- L15 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Creates an instance of this details customization
- L19 _protected prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailLayout) override;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace ControlRigEditor` (scope `UE`)

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/AnimDetails/Customizations/AnimDetailsSetInstancedPropertyMetadata.h` (Private)


#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace ControlRigEditor` (scope `UE`)
- L10 _namespace_ `namespace AnimDetailsMetaDataUtil` (scope `UE::ControlRigEditor`)
- L13 _prototype_ `void SetInstancedPropertyMetaData(const UAnimDetailsProxyBase& TemplateProxy, const TSharedRef<IPropertyHandle>& ValuePropertyHandle);` (scope `UE::ControlRigEditor::AnimDetailsMetaDataUtil`) — Sets property meta data for the property instance from the data in the template proxy, for example min and max values.

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/AnimDetails/Customizations/AnimDetailsValueCustomization.h` (Private)


#### struct `UE::ControlRigEditor::Private::FAnimDetailsChildWidgetVisiblityHandler`  
`struct FAnimDetailsChildWidgetVisiblityHandler`  
_L22-34_
- desc: When structs are collapsed, the visibility of the widgets is not updated, and their visibility attribute is not executed. This struct serves to update the widget's visibility regardless of this state. Required to deduce if the widget is navigable.
- L24 _public prototype_ `FAnimDetailsChildWidgetVisiblityHandler() = default;`
- L25 _public prototype_ `FAnimDetailsChildWidgetVisiblityHandler(const TSharedRef<IPropertyHandle>& InStructPropertyHandle, const TArray<TWeakPtr<SWidget>>& InWeakWidgets);`
- L27 _public prototype_ `~FAnimDetailsChildWidgetVisiblityHandler();`
- L30 _private member_ `TWeakPtr<IPropertyHandle> WeakStructPropertyHandle;`
- L31 _private member_ `TArray<TWeakPtr<SWidget>> WeakWidgets;`
- L33 _private member_ `FTSTicker::FDelegateHandle TickerHandle;`

#### class `UE::ControlRigEditor::FAnimDetailsValueCustomization`  
`class FAnimDetailsValueCustomization : public FMathStructCustomization`  
_L38-88_
- inherits: `FMathStructCustomization`
- desc: Property type customization for struct properties such as FAnimDetailsBool or FAnimDetailsTransform
- L43 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();` — Creates an instance of this struct customization
- L47 _protected prototype_ `virtual void MakeHeaderRow(TSharedRef<IPropertyHandle>& StructPropertyHandle, FDetailWidgetRow& Row) override;`
- L48 _protected prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> InStructPropertyHandle, IDetailChildrenBuilder& InStructBuilder, IPropertyTypeCustomizationUtils& InStructCustomizationUtils) override;`
- L49 _protected prototype_ `virtual TSharedRef<SWidget> MakeChildWidget(TSharedRef<IPropertyHandle>& StructurePropertyHandle, TSharedRef<IPropertyHandle>& PropertyHandle) override;`
- L54 _private prototype_ `TSharedRef<SWidget> MakePropertyNameWidget(const TSharedRef<IPropertyHandle>& InStructPropertyHandle) const;` — Makes a widget to display the property name
- L57 _private prototype_ `bool IsStructPropertyHiddenByFilter(const TSharedRef<IPropertyHandle>& InStructPropertyHandle) const;` — Returns true if this struct is hidden by the filter
- L60 _private prototype_ `bool IsChildPropertyHiddenByFilter(const TSharedRef<IPropertyHandle>& InPropertyHandle) const;` — Returns true if this struct is hidden by the filter
- L63 _private prototype_ `EVisibility GetVisibilityFromExpansionState() const;` — Returns visible if the value struct is expanded, collapsed otherwise
- L66 _private prototype_ `FLinearColor GetColorFromProperty(const FName& PropertyName) const;` — Gets a color from the property
- L69 _private prototype_ `static bool ShouldUseTransformPropertyExpansion(const TSharedRef<IPropertyHandle>& InStructPropertyHandle);` — Determines whether the transform property should use an expanded layout for its UI in property customizations
- L72 _private prototype_ `bool IsResetToDefaultVisible(const TWeakPtr<IPropertyHandle> WeakPropertyHandle) const;` — Returns true if the property handle's reset to default button is visible
- L75 _private prototype_ `void OnResetToDefaultClicked(const TWeakPtr<IPropertyHandle> WeakPropertyHandle);` — Called when the property handle's reset to default button was clicked
- L78 _private member_ `TUniquePtr<Private::FAnimDetailsChildWidgetVisiblityHandler> ChildContentVisibilityHandler;` — Handles visibility for child widgets in this customization
- L81 _private member_ `IDetailLayoutBuilder* DetailBuilder = nullptr;` — Pointer to the detail builder, or nullptr if not initialized
- L84 _private member_ `TSharedPtr<IPropertyHandle> StructPropertyHandle;` — The customized struct
- L87 _private member_ `TSharedPtr<SWidget> NumericEntryBox;` — The numeric entry box widget

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace ControlRigEditor` (scope `UE`)
- L15 _namespace_ `namespace Private` (scope `UE::ControlRigEditor`)

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/AnimDetails/Customizations/AnimDetailsValueEnumCustomization.h` (Private)


#### class `UE::ControlRigEditor::FAnimDetailsValueEnumCustomization`  
`class FAnimDetailsValueEnumCustomization : public IPropertyTypeCustomization`  
_L16-47_
- inherits: `IPropertyTypeCustomization`
- desc: Property type customization for FAnimDetailsEnum
- L21 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();` — Creates an instance of this property type customization
- L25 _protected prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> InStructPropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L26 _protected prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> InStructPropertyHandle, IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L31 _private prototype_ `TSharedRef<SWidget> MakePropertyNameWidget(const TSharedRef<IPropertyHandle>& InStructPropertyHandle) const;` — Makes a widget to display the property name
- L34 _private prototype_ `bool IsStructPropertyHiddenByFilter(const TSharedRef<IPropertyHandle>& InStructPropertyHandle) const;` — Returns true if this struct is hidden by the filter
- L37 _private prototype_ `void OnEnumValueChanged(int32 InValue, ESelectInfo::Type InSelectInfo);` — Called when the enum value changed
- L40 _private prototype_ `const UEnum* GetEnumType() const;` — Returns the enum type
- L43 _private prototype_ `int32 GetEnumIndex() const;` — Returns the current enum index
- L46 _private member_ `TSharedPtr<IPropertyHandle> EnumIndexPropertyHandle;` — Property handle for the EnumIndex property

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace ControlRigEditor` (scope `UE`)

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/AnimDetails/Proxies/AnimDetailsProxyBase.h` (Private)


#### class `UAnimDetailsProxyBase`  
`class UAnimDetailsProxyBase : public UObject`  
_L27-164_
- reflection: `UCLASS(Abstract)`
- inherits: `UObject`
- desc: Base class for anim details proxies. Anim details proxies can handle a property bound in sequencer, and the related controls if the bound object uses a control rig. This is a rewrite of what was previously UControlRigControlsProxy in ControlRigEditor/Private/EditMode/ControlRigControlsProxy.h.
- L32 _private typedef_ `using FAnimDetailsSequencerProxyItem = UE::ControlRigEditor::FAnimDetailsSequencerProxyItem;`
- L36 _public prototype_ `void SetControlFromControlRig(UControlRig* InControlRig, const FName& InName);` — Sets the control for a control rig
- L39 _public prototype_ `void SetControlFromSequencerBinding(UObject* InObject, const TWeakObjectPtr<UMovieSceneTrack>& InTrack, const TSharedPtr<FTrackInstancePropertyBindings>& InBinding);` — Sets the control for a sequencer binding
- L42 _public prototype_ `UControlRig* GetControlRig() const;` — Returns the control rig this proxy handles, or nullptr if the control rig is invalid
- L45 _public prototype_ `FRigControlElement* GetControlElement() const;` — Returns the control element this proxy handles, or nullptr if the element is invalid.
- L48 _public prototype_ `const FRigElementKey& GetControlElementKey() const;` — Returns a key to the control element this proxy handles.
- L51 _public prototype_ `const FName& GetControlName() const;` — Returns the name of the control element his proxy handles
- L54 _public function_ `const FAnimDetailsSequencerProxyItem& GetSequencerItem()` — Returns the sequencer binding, or nullptr if this proxy is not assigned to a seqeuncer object
- L57 _public function_ `const FAnimDetailsSequencerProxyItem& GetSequencerItem() const` — Returns the sequencer binding, or nullptr if this proxy is not assigned to a seqeuncer object, const version
- L60 _public prototype_ `void PropagateValues();` — Propagates the current proxy values to control rig or the bound sequencer object
- L63 _public prototype_ `FText GetDisplayNameText(const EElementNameDisplayMode ElementNameDisplayMode = EElementNameDisplayMode::Auto) const;` — Returns the display name for this proxy as text
- L66 _public prototype_ `void SetKey(const IPropertyHandle& KeyedPropertyHandle);` — Sets a key for this property in sequencer
- L69 _public prototype_ `void RemoveAllKeys(const IPropertyHandle& KeyedPropertyHandle);` — Removes all keys for this property in sequencer
- L72 _public prototype_ `EPropertyKeyedStatus GetPropertyKeyedStatus(const IPropertyHandle& PropertyHandle) const;` — Gets the keyed status of a property
- L75 _public prototype_ `virtual FName GetCategoryName() const PURE_VIRTUAL(UAnimDetailsProxyBase::GetCategoryName, return NAME_None;) virtual FName GetDetailRowID() const;` — Returns the category of the struct that holds the control type, for example float or transform
- L91 _public prototype_ `virtual FName GetPropertyID(const FName& PropertyName) const;` — Returns an ID for property consisting of the detail row ID and the property name. Properties that share the same property ID will be multiedited on the same property row. The property ID does not relate to any other engine logic, it is specific to anim details proxies.
- L94 _public prototype_ `virtual TArray<FName> GetPropertyNames() const PURE_VIRTUAL(UAnimDetailsProxyBase::GetPropertyNames, return {};) virtual void GetLocalizedPropertyName(const FName& InPropertyName, FText& OutPropertyDisplayName, TOptional<FText>& OutOptionalStructDisplayName) const;` — Returns the property names in this proxy controls. Should be in order they're declared
- L100 _public prototype_ `virtual TSet<ERigControlType> GetSupportedControlTypes() const PURE_VIRTUAL(UAnimDetailsProxyBase::GetSupportedControlTypes, return {};);` — Returns the control types the proxy supports
- L103 _public prototype_ `virtual bool PropertyIsOnProxy(const FProperty* Property, const FProperty* MemberProperty) PURE_VIRTUAL(UAnimDetailsProxyBase::PropertyIsOnProxy, return false;) virtual void AdoptValues(const ERigControlValueType RigControlValueType = ERigControlValueType::Current) PURE_VIRTUAL(UAnimDetailsProxyBase::AdoptValues, return;) virtual void ResetPropertyToDefault(const FName& PropertyName) PURE_VIRTUAL(UAnimDetailsProxyBase::ResetPropertyToDefault, return;) virtual bool HasDefaultValue(const FName& PropertyName) const PURE_VIRTUAL(UAnimDetailsProxyBase::HasDefaultValue, return true;) virtual void UpdateOverrideableProperties();` — Returns true if the property is handled by this proxy
- L118 _public prototype_ `virtual EControlRigContextChannelToKey GetChannelToKeyFromPropertyName(const FName& PropertyName) const PURE_VIRTUAL(UAnimDetailsProxyBase::GetChannelToKeyFromPropertyName, return EControlRigContextChannelToKey::AllTransform;) virtual EControlRigContextChannelToKey GetChannelToKeyFromChannelName(const FString& InChannelName) const PURE_VIRTUAL(UAnimDetailsProxyBase::GetChannelToKeyFromChannelName, return EControlRigContextChannelToKey::AllTransform;)` — Returns the channel to key flags from the property name
- L125 _public prototype_ `virtual bool Modify(bool bAlwaysMarkDirty = true) override;`
- L129 _public member_ `bool bIsIndividual = false;` — If true shows on its own detail row, but is still multi edited with identical controls. If false, is multi-edited with proxies of same type
- L132 _public member_ `ERigControlType Type = ERigControlType::Transform;` — The control rig type to use for this proxy. Note this is used even if there is only a sequencer binding but no control rig
- L136 _public member_ `FString DisplayName;` — `UPROPERTY(EditAnywhere, Category = "Overrides")` — An overrideable display name for the control
- L140 _public member_ `FRigUnit_HierarchyAddControl_ShapeSettings Shape;` — `UPROPERTY(EditAnywhere, Category = "Overrides", meta=(ExpandByDefault))` — Overrideable shape settings for the control
- L144 _protected function_ `virtual void SetControlRigElementValueFromCurrent(const FRigControlModifiedContext& Context) PURE_VIRTUAL(UAnimDetailsProxyBase::SetControlRigElementValueFromCurrent, return;) virtual void SetSequencerBindingValueFromCurrent(const FRigControlModifiedContext & Context)` — Sets the control rig element value from the current proxy value
- L150 _protected member_ `TWeakObjectPtr<UControlRig> WeakControlRig;` — The control rig that holds the control or nullptr if there is no control rig.
- L153 _protected member_ `mutable FCachedRigElement CachedRigElement;` — The cached rig element that holds the control, or nullptr if there is no rig element.
- L156 _protected member_ `FAnimDetailsSequencerProxyItem SequencerItem;` — Item holding data about a sequencer binding
- L160 _private prototype_ `void AddControlRigInteractionScope(EControlRigContextChannelToKey ChannelsToKey, EPropertyChangeType::Type ChangeType);` — Adds a control rig interaction scope to the interaction scopes array
- L163 _private member_ `TMap<FRigControlElement*, TSharedRef<FControlRigInteractionScope>> InteractionScopes;` — Current interaction scopes

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/AnimDetails/Proxies/AnimDetailsProxyBool.h` (Private)


#### struct `FAnimDetailsBool`  
`struct FAnimDetailsBool`  
_L11-17_
- reflection: `USTRUCT(BlueprintType)`
- desc: A boolean value in anim details
- L16 _public member_ `bool Bool = false;` — `UPROPERTY(EditAnywhere, Interp, Category = "Bool")`

#### class `UAnimDetailsProxyBool`  
`class UAnimDetailsProxyBool : public UAnimDetailsProxyBase`  
_L21-43_
- reflection: `UCLASS(EditInlineNew, CollapseCategories)`
- inherits: `UAnimDetailsProxyBase`
- desc: Handles a boolean value property in sequencer, and the related control if the bound object uses a control rig
- L28 _public prototype_ `virtual FName GetCategoryName() const override;`
- L29 _public prototype_ `virtual TArray<FName> GetPropertyNames() const override;`
- L30 _public prototype_ `virtual TSet<ERigControlType> GetSupportedControlTypes() const override;`
- L31 _public prototype_ `virtual bool PropertyIsOnProxy(const FProperty* Property, const FProperty* MemberProperty) override;`
- L32 _public prototype_ `virtual void AdoptValues(const ERigControlValueType RigControlValueType = ERigControlValueType::Current) override;`
- L33 _public prototype_ `virtual void ResetPropertyToDefault(const FName& PropertyName) override;`
- L34 _public prototype_ `virtual bool HasDefaultValue(const FName& PropertyName) const override;`
- L35 _public prototype_ `virtual EControlRigContextChannelToKey GetChannelToKeyFromPropertyName(const FName& InPropertyName) const override;`
- L36 _public prototype_ `virtual EControlRigContextChannelToKey GetChannelToKeyFromChannelName(const FString& InChannelName) const override;`
- L37 _public prototype_ `virtual void SetControlRigElementValueFromCurrent(const FRigControlModifiedContext& Context) override;`
- L38 _public prototype_ `virtual void SetSequencerBindingValueFromCurrent(const FRigControlModifiedContext& Context) override;`
- L42 _public member_ `FAnimDetailsBool Bool;` — `UPROPERTY(EditAnywhere, Interp, Meta = (ShowOnlyInnerProperties), Category = "Bool")`

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/AnimDetails/Proxies/AnimDetailsProxyEnum.h` (Private)


#### struct `FAnimDetailsEnum`  
`struct FAnimDetailsEnum`  
_L11-26_
- reflection: `USTRUCT(BlueprintType)`
- desc: An enum value in anim details
- L15 _public function_ `FAnimDetailsEnum()`
- L22 _public member_ `TObjectPtr<UEnum> EnumType;` — `UPROPERTY()`
- L25 _public member_ `int32 EnumIndex;` — `UPROPERTY(EditAnywhere, Category = Enum)`

#### class `UAnimDetailsProxyEnum`  
`class UAnimDetailsProxyEnum : public UAnimDetailsProxyBase`  
_L30-52_
- reflection: `UCLASS(EditInlineNew, CollapseCategories)`
- inherits: `UAnimDetailsProxyBase`
- desc: Handles an enum property bound in sequencer, and the related control if the bound object uses a control rig
- L37 _public prototype_ `virtual FName GetCategoryName() const override;`
- L38 _public prototype_ `virtual FName GetDetailRowID() const override;`
- L39 _public prototype_ `virtual TArray<FName> GetPropertyNames() const override;`
- L40 _public prototype_ `virtual TSet<ERigControlType> GetSupportedControlTypes() const override;`
- L41 _public prototype_ `virtual bool PropertyIsOnProxy(const FProperty* Property, const FProperty* MemberProperty) override;`
- L42 _public prototype_ `virtual void AdoptValues(const ERigControlValueType RigControlValueType = ERigControlValueType::Current) override;`
- L43 _public prototype_ `virtual void ResetPropertyToDefault(const FName& PropertyName) override;`
- L44 _public prototype_ `virtual bool HasDefaultValue(const FName& PropertyName) const override;`
- L45 _public prototype_ `virtual EControlRigContextChannelToKey GetChannelToKeyFromPropertyName(const FName& InPropertyName) const override;`
- L46 _public prototype_ `virtual EControlRigContextChannelToKey GetChannelToKeyFromChannelName(const FString& InChannelName) const override;`
- L47 _public prototype_ `virtual void SetControlRigElementValueFromCurrent(const FRigControlModifiedContext& Context) override;`
- L51 _public member_ `FAnimDetailsEnum Enum;` — `UPROPERTY(EditAnywhere, Interp, Meta = (ShowOnlyInnerProperties), Category = "Enum")`

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/AnimDetails/Proxies/AnimDetailsProxyFloat.h` (Private)


#### struct `FAnimDetailsFloat`  
`struct FAnimDetailsFloat`  
_L16-22_
- reflection: `USTRUCT(BlueprintType)`
- desc: A floating point value in anim details Note, control rig uses 'float' controls so we call this float though it's a double internally, so we can use same for non-control rig parameters
- L21 _public member_ `double Float = 0.0;` — `UPROPERTY(EditAnywhere, Interp, Category = "Float")`

#### class `UAnimDetailsProxyFloat`  
`class UAnimDetailsProxyFloat : public UAnimDetailsProxyBase`  
_L26-48_
- reflection: `UCLASS(EditInlineNew, CollapseCategories)`
- inherits: `UAnimDetailsProxyBase`
- desc: Handles an floating point property bound in sequencer, and the related control if the bound object uses a control rig
- L33 _public prototype_ `virtual FName GetCategoryName() const override;`
- L34 _public prototype_ `virtual TArray<FName> GetPropertyNames() const override;`
- L35 _public prototype_ `virtual TSet<ERigControlType> GetSupportedControlTypes() const override;`
- L36 _public prototype_ `virtual bool PropertyIsOnProxy(const FProperty* Property, const FProperty* MemberProperty) override;`
- L37 _public prototype_ `virtual void AdoptValues(const ERigControlValueType RigControlValueType = ERigControlValueType::Current) override;`
- L38 _public prototype_ `virtual void ResetPropertyToDefault(const FName& PropertyName) override;`
- L39 _public prototype_ `virtual bool HasDefaultValue(const FName& PropertyName) const override;`
- L40 _public prototype_ `virtual EControlRigContextChannelToKey GetChannelToKeyFromPropertyName(const FName& InPropertyName) const override;`
- L41 _public prototype_ `virtual EControlRigContextChannelToKey GetChannelToKeyFromChannelName(const FString& InChannelName) const override;`
- L42 _public prototype_ `virtual void SetControlRigElementValueFromCurrent(const FRigControlModifiedContext& Context) override;`
- L43 _public prototype_ `virtual void SetSequencerBindingValueFromCurrent(const FRigControlModifiedContext& Context) override;`
- L47 _public member_ `FAnimDetailsFloat Float;` — `UPROPERTY(EditAnywhere, Interp, Category = "Float", meta = (ShowOnlyInnerProperties, Delta = "0.05", SliderExponent = "1", LinearDeltaSensitivity = "1"))`

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/AnimDetails/Proxies/AnimDetailsProxyInteger.h` (Private)


#### struct `FAnimDetailsInteger`  
`struct FAnimDetailsInteger`  
_L11-17_
- reflection: `USTRUCT(BlueprintType)`
- desc: An integer value in anim details
- L16 _public member_ `int64 Integer = 0;` — `UPROPERTY(EditAnywhere, Interp, meta = (Delta = 1.0), Category = "Integer")`

#### class `UAnimDetailsProxyInteger`  
`class UAnimDetailsProxyInteger : public UAnimDetailsProxyBase`  
_L21-43_
- reflection: `UCLASS(EditInlineNew, CollapseCategories)`
- inherits: `UAnimDetailsProxyBase`
- desc: Handles an integer property bound in sequencer, and the related control if the bound object uses a control rig
- L28 _public prototype_ `virtual FName GetCategoryName() const override;`
- L29 _public prototype_ `virtual TArray<FName> GetPropertyNames() const override;`
- L30 _public prototype_ `virtual TSet<ERigControlType> GetSupportedControlTypes() const override;`
- L31 _public prototype_ `virtual bool PropertyIsOnProxy(const FProperty* Property, const FProperty* MemberProperty) override;`
- L32 _public prototype_ `virtual void AdoptValues(const ERigControlValueType RigControlValueType = ERigControlValueType::Current) override;`
- L33 _public prototype_ `virtual void ResetPropertyToDefault(const FName& PropertyName) override;`
- L34 _public prototype_ `virtual bool HasDefaultValue(const FName& PropertyName) const override;`
- L35 _public prototype_ `virtual EControlRigContextChannelToKey GetChannelToKeyFromPropertyName(const FName& InPropertyName) const override;`
- L36 _public prototype_ `virtual EControlRigContextChannelToKey GetChannelToKeyFromChannelName(const FString& InChannelName) const override;`
- L37 _public prototype_ `virtual void SetControlRigElementValueFromCurrent(const FRigControlModifiedContext& Context) override;`
- L38 _public prototype_ `virtual void SetSequencerBindingValueFromCurrent(const FRigControlModifiedContext& Context) override;`
- L42 _public member_ `FAnimDetailsInteger Integer;` — `UPROPERTY(EditAnywhere, Interp, Meta = (ShowOnlyInnerProperties), Category = "Integer")`

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/AnimDetails/Proxies/AnimDetailsProxyLocation.h` (Private)


#### struct `FAnimDetailsLocation`  
`struct FAnimDetailsLocation`  
_L11-30_
- reflection: `USTRUCT(BlueprintType)`
- desc: A location value in anim details
- L16 _public member_ `double LX = 0.0;` — `UPROPERTY(EditAnywhere, Interp, Category = "Location")`
- L19 _public member_ `double LY = 0.0;` — `UPROPERTY(EditAnywhere, Interp, Category = "Location")`
- L22 _public member_ `double LZ = 0.0;` — `UPROPERTY(EditAnywhere, Interp, Category = "Location")`
- L24 _public prototype_ `FAnimDetailsLocation() = default;`
- L25 _public prototype_ `FAnimDetailsLocation(const FVector& InVector);`
- L26 _public prototype_ `FAnimDetailsLocation(const FVector3f& InVector);`
- L28 _public function_ `FVector ToVector() const`
- L29 _public function_ `FVector3f ToVector3f() const`

#### class `UAnimDetailsProxyLocation`  
`class UAnimDetailsProxyLocation : public UAnimDetailsProxyBase`  
_L34-56_
- reflection: `UCLASS(EditInlineNew, CollapseCategories)`
- inherits: `UAnimDetailsProxyBase`
- desc: Handles a location property bound in sequencer, and the related control if the bound object uses a control rig
- L41 _public prototype_ `virtual FName GetCategoryName() const override;`
- L42 _public prototype_ `virtual TArray<FName> GetPropertyNames() const override;`
- L43 _public prototype_ `virtual void GetLocalizedPropertyName(const FName& InPropertyName, FText& OutPropertyDisplayName, TOptional<FText>& OutOptionalStructDisplayName) const override;`
- L44 _public prototype_ `virtual TSet<ERigControlType> GetSupportedControlTypes() const override;`
- L45 _public prototype_ `virtual bool PropertyIsOnProxy(const FProperty* Property, const FProperty* MemberProperty) override;`
- L46 _public prototype_ `virtual void AdoptValues(const ERigControlValueType RigControlValueType = ERigControlValueType::Current) override;`
- L47 _public prototype_ `virtual void ResetPropertyToDefault(const FName& PropertyName) override;`
- L48 _public prototype_ `virtual bool HasDefaultValue(const FName& PropertyName) const override;`
- L49 _public prototype_ `virtual EControlRigContextChannelToKey GetChannelToKeyFromPropertyName(const FName& InPropertyName) const override;`
- L50 _public prototype_ `virtual EControlRigContextChannelToKey GetChannelToKeyFromChannelName(const FString& InChannelName) const override;`
- L51 _public prototype_ `virtual void SetControlRigElementValueFromCurrent(const FRigControlModifiedContext& Context) override;`
- L55 _public member_ `FAnimDetailsLocation Location;` — `UPROPERTY(EditAnywhere, Interp, Category = Location)`

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/AnimDetails/Proxies/AnimDetailsProxyRotation.h` (Private)


#### struct `FAnimDetailsRotation`  
`struct FAnimDetailsRotation`  
_L11-32_
- reflection: `USTRUCT(BlueprintType)`
- desc: A rotation value in anim details
- L16 _public member_ `double RX = 0.0;` — `UPROPERTY(EditAnywhere, Interp, Category = "Rotation")`
- L19 _public member_ `double RY = 0.0;` — `UPROPERTY(EditAnywhere, Interp, Category = "Rotation")`
- L22 _public member_ `double RZ = 0.0;` — `UPROPERTY(EditAnywhere, Interp, Category = "Rotation")`
- L24 _public prototype_ `FAnimDetailsRotation() = default;`
- L25 _public prototype_ `FAnimDetailsRotation(const FRotator& InRotator);`
- L26 _public prototype_ `FAnimDetailsRotation(const FVector3f& InVector);`
- L28 _public prototype_ `FVector ToVector() const;`
- L29 _public prototype_ `FVector3f ToVector3f() const;`
- L30 _public prototype_ `FRotator ToRotator() const;`
- L31 _public prototype_ `void FromRotator(const FRotator& InRotator);`

#### class `UAnimDetailsProxyRotation`  
`class UAnimDetailsProxyRotation : public UAnimDetailsProxyBase`  
_L36-58_
- reflection: `UCLASS(EditInlineNew, CollapseCategories)`
- inherits: `UAnimDetailsProxyBase`
- desc: Handles a rotation property bound in sequencer, and the related control if the bound object uses a control rig
- L43 _public prototype_ `virtual FName GetCategoryName() const override;`
- L44 _public prototype_ `virtual TArray<FName> GetPropertyNames() const override;`
- L45 _public prototype_ `virtual void GetLocalizedPropertyName(const FName& InPropertyName, FText& OutPropertyDisplayName, TOptional<FText>& OutOptionalStructDisplayName) const override;`
- L46 _public prototype_ `virtual TSet<ERigControlType> GetSupportedControlTypes() const override;`
- L47 _public prototype_ `virtual bool PropertyIsOnProxy(const FProperty* Property, const FProperty* MemberProperty) override;`
- L48 _public prototype_ `virtual void AdoptValues(const ERigControlValueType RigControlValueType = ERigControlValueType::Current) override;`
- L49 _public prototype_ `virtual void ResetPropertyToDefault(const FName& PropertyName) override;`
- L50 _public prototype_ `virtual bool HasDefaultValue(const FName& PropertyName) const override;`
- L51 _public prototype_ `virtual EControlRigContextChannelToKey GetChannelToKeyFromPropertyName(const FName& InPropertyName) const override;`
- L52 _public prototype_ `virtual EControlRigContextChannelToKey GetChannelToKeyFromChannelName(const FString& InChannelName) const override;`
- L53 _public prototype_ `virtual void SetControlRigElementValueFromCurrent(const FRigControlModifiedContext& Context) override;`
- L57 _public member_ `FAnimDetailsRotation Rotation;` — `UPROPERTY(EditAnywhere, Interp, Category = Rotation)`

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/AnimDetails/Proxies/AnimDetailsProxyScale.h` (Private)


#### struct `FAnimDetailsScale`  
`struct FAnimDetailsScale`  
_L11-30_
- reflection: `USTRUCT(BlueprintType)`
- desc: A scale value in anim details
- L16 _public member_ `double SX = 1.0;` — `UPROPERTY(EditAnywhere, Interp, Category = "Scale")`
- L19 _public member_ `double SY = 1.0;` — `UPROPERTY(EditAnywhere, Interp, Category = "Scale")`
- L22 _public member_ `double SZ = 1.0;` — `UPROPERTY(EditAnywhere, Interp, Category = "Scale")`
- L24 _public prototype_ `FAnimDetailsScale() = default;`
- L25 _public prototype_ `FAnimDetailsScale(const FVector& InVector);`
- L26 _public prototype_ `FAnimDetailsScale(const FVector3f& InVector);`
- L28 _public prototype_ `FVector ToVector() const;`
- L29 _public prototype_ `FVector3f ToVector3f() const;`

#### class `UAnimDetailsProxyScale`  
`class UAnimDetailsProxyScale : public UAnimDetailsProxyBase`  
_L34-56_
- reflection: `UCLASS(EditInlineNew, CollapseCategories)`
- inherits: `UAnimDetailsProxyBase`
- desc: Handles a scale property bound in sequencer, and the related control if the bound object uses a control rig
- L41 _public prototype_ `virtual FName GetCategoryName() const override;`
- L42 _public prototype_ `virtual TArray<FName> GetPropertyNames() const override;`
- L43 _public prototype_ `virtual void GetLocalizedPropertyName(const FName& InPropertyName, FText& OutPropertyDisplayName, TOptional<FText>& OutOptionalStructDisplayName) const override;`
- L44 _public prototype_ `virtual TSet<ERigControlType> GetSupportedControlTypes() const override;`
- L45 _public prototype_ `virtual bool PropertyIsOnProxy(const FProperty* Property, const FProperty* MemberProperty) override;`
- L46 _public prototype_ `virtual void AdoptValues(const ERigControlValueType RigControlValueType = ERigControlValueType::Current) override;`
- L47 _public prototype_ `virtual void ResetPropertyToDefault(const FName& PropertyName) override;`
- L48 _public prototype_ `virtual bool HasDefaultValue(const FName& PropertyName) const override;`
- L49 _public prototype_ `virtual EControlRigContextChannelToKey GetChannelToKeyFromPropertyName(const FName& InPropertyName) const override;`
- L50 _public prototype_ `virtual EControlRigContextChannelToKey GetChannelToKeyFromChannelName(const FString& InChannelName) const override;`
- L51 _public prototype_ `virtual void SetControlRigElementValueFromCurrent(const FRigControlModifiedContext& Context) override;`
- L55 _public member_ `FAnimDetailsScale Scale;` — `UPROPERTY(EditAnywhere, Interp, Category = Scale)`

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/AnimDetails/Proxies/AnimDetailsProxyTransform.h` (Private)


#### class `UAnimDetailsProxyTransform`  
`class UAnimDetailsProxyTransform : public UAnimDetailsProxyBase`  
_L14-43_
- reflection: `UCLASS(EditInlineNew, CollapseCategories)`
- inherits: `UAnimDetailsProxyBase`
- desc: Handles a transform property bound in sequencer, and the related controls if the bound object uses a control rig
- L21 _public prototype_ `virtual FName GetCategoryName() const override;`
- L22 _public prototype_ `virtual TArray<FName> GetPropertyNames() const override;`
- L23 _public prototype_ `virtual void GetLocalizedPropertyName(const FName& InPropertyName, FText& OutPropertyDisplayName, TOptional<FText>& OutOptionalStructDisplayName) const override;`
- L24 _public prototype_ `virtual TSet<ERigControlType> GetSupportedControlTypes() const override;`
- L25 _public prototype_ `virtual bool PropertyIsOnProxy(const FProperty* Property, const FProperty* MemberProperty) override;`
- L26 _public prototype_ `virtual void AdoptValues(const ERigControlValueType RigControlValueType = ERigControlValueType::Current) override;`
- L27 _public prototype_ `virtual void ResetPropertyToDefault(const FName& PropertyName) override;`
- L28 _public prototype_ `virtual bool HasDefaultValue(const FName& PropertyName) const override;`
- L29 _public prototype_ `virtual EControlRigContextChannelToKey GetChannelToKeyFromPropertyName(const FName& InPropertyName) const override;`
- L30 _public prototype_ `virtual EControlRigContextChannelToKey GetChannelToKeyFromChannelName(const FString& InChannelName) const override;`
- L31 _public prototype_ `virtual void SetControlRigElementValueFromCurrent(const FRigControlModifiedContext& Context) override;`
- L32 _public prototype_ `virtual void SetSequencerBindingValueFromCurrent(const FRigControlModifiedContext& Context) override;`
- L36 _public member_ `FAnimDetailsLocation Location;` — `UPROPERTY(EditAnywhere, Interp, Category = Transform)`
- L39 _public member_ `FAnimDetailsRotation Rotation;` — `UPROPERTY(EditAnywhere, Interp, Category = Transform)`
- L42 _public member_ `FAnimDetailsScale Scale;` — `UPROPERTY(EditAnywhere, Interp, Category = Transform)`

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/AnimDetails/Proxies/AnimDetailsProxyVector2D.h` (Private)


#### struct `FAnimDetailsVector2D`  
`struct FAnimDetailsVector2D`  
_L11-25_
- reflection: `USTRUCT(BlueprintType)`
- desc: A vector 2D value in anim details
- L16 _public member_ `double X = 0.0;` — `UPROPERTY(EditAnywhere, Interp, Category = "Vector2D", meta = (Delta = "0.05", SliderExponent = "1", LinearDeltaSensitivity = "1"))`
- L19 _public member_ `double Y = 0.0;` — `UPROPERTY(EditAnywhere, Interp, Category = "Vector2D", meta = (Delta = "0.05", SliderExponent = "1", LinearDeltaSensitivity = "1"))`
- L21 _public prototype_ `FAnimDetailsVector2D() = default;`
- L22 _public prototype_ `FAnimDetailsVector2D(const FVector2D& InVector);`
- L24 _public prototype_ `FVector2D ToVector2D() const;`

#### class `UAnimDetailsProxyVector2D`  
`class UAnimDetailsProxyVector2D : public UAnimDetailsProxyBase`  
_L29-51_
- reflection: `UCLASS(EditInlineNew, CollapseCategories)`
- inherits: `UAnimDetailsProxyBase`
- desc: Handles a vector 2D property bound in sequencer, and the related control if the bound object uses a control rig
- L36 _public prototype_ `virtual FName GetCategoryName() const override;`
- L37 _public prototype_ `virtual TArray<FName> GetPropertyNames() const override;`
- L38 _public prototype_ `virtual void GetLocalizedPropertyName(const FName& InPropertyName, FText& OutPropertyDisplayName, TOptional<FText>& OutOptionalStructDisplayName) const override;`
- L39 _public prototype_ `virtual TSet<ERigControlType> GetSupportedControlTypes() const override;`
- L40 _public prototype_ `virtual bool PropertyIsOnProxy(const FProperty* Property, const FProperty* MemberProperty) override;`
- L41 _public prototype_ `virtual void AdoptValues(const ERigControlValueType RigControlValueType = ERigControlValueType::Current) override;`
- L42 _public prototype_ `virtual void ResetPropertyToDefault(const FName& PropertyName) override;`
- L43 _public prototype_ `virtual bool HasDefaultValue(const FName& PropertyName) const override;`
- L44 _public prototype_ `virtual EControlRigContextChannelToKey GetChannelToKeyFromPropertyName(const FName& InPropertyName) const override;`
- L45 _public prototype_ `virtual EControlRigContextChannelToKey GetChannelToKeyFromChannelName(const FString& InChannelName) const override;`
- L46 _public prototype_ `virtual void SetControlRigElementValueFromCurrent(const FRigControlModifiedContext& Context) override;`
- L50 _public member_ `FAnimDetailsVector2D Vector2D;` — `UPROPERTY(EditAnywhere, Interp, Category = Vector2D)`

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/AnimDetails/Proxies/AnimDetailsScopedPropertyChangedEvent.h` (Private)


#### struct `UE::ControlRigEditor::FAnimDetailsScopedPropertyChangedEvent`  
`struct FAnimDetailsScopedPropertyChangedEvent : FNoncopyable`  
_L16-39_
- inherits: `FNoncopyable`
- desc: Utility to raise out pre - / post property changed events for arbitrary properties
- L20 _public prototype_ `FAnimDetailsScopedPropertyChangedEvent(UObject& Object, FProperty& InProperty);` — Instantiates a scoped property change for object properties
- L23 _public prototype_ `FAnimDetailsScopedPropertyChangedEvent(UObject& Object, FStructProperty& InStructProperty, FProperty& InProperty);` — Instantiates a scoped property change for struct properties
- L25 _public prototype_ `~FAnimDetailsScopedPropertyChangedEvent();`
- L29 _private prototype_ `void InitObjectToNotify(UObject& Object);` — Initializes the ObjectsToNotify member
- L32 _private member_ `FProperty& Property;` — The property that is being changed
- L35 _private member_ `FEditPropertyChain PropertyChain;` — The property chain for which the event is raised
- L38 _private member_ `TArray<UObject*> ObjectsToNotify;` — Objects that should be notified of the property change

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace ControlRigEditor` (scope `UE`)

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/AnimDetails/Proxies/AnimDetailsSequencerProxyItem.h` (Private)


#### struct `UE::ControlRigEditor::FAnimDetailsSequencerProxyItem`  
`struct FAnimDetailsSequencerProxyItem`  
_L13-53_
- desc: A sequencer binding in a anim details proxy
- L15 _public prototype_ `FAnimDetailsSequencerProxyItem() = default;`
- L24 _public prototype_ `FAnimDetailsSequencerProxyItem(UObject& InBoundObject, UMovieSceneTrack& InMovieSceneTrack, const TSharedRef<FTrackInstancePropertyBindings>& InBinding);` — Constructs a valid item @param InBoundObject			The object the sequencer track is bound to. Should be an actor or a scene component. @param InMovieSceneTrack		The movie scene track. @param InBinding				The property binding for this item.
- L27 _public prototype_ `UObject* GetBoundObject() const;` — Returns the object the sequencer track is bound to or nullptr if the bound object is not valid.
- L30 _public prototype_ `UMovieSceneTrack* GetMovieSceneTrack() const;` — Returns the movie scene track  or nullptr if the movie scene track is not valid.
- L33 _public function_ `const TSharedPtr<FTrackInstancePropertyBindings>& GetBinding() const` — Returns the property binding for this item or nullptr if the binding is not valid
- L36 _public prototype_ `FProperty* GetProperty() const;` — Returns the bound property or nullptr if no property is bound
- L39 _public prototype_ `bool IsValid() const;` — Returns true if this points to a live bound object of a track
- L42 _public prototype_ `void Reset();` — Resets this item irrevocably
- L46 _private member_ `TWeakObjectPtr<UObject> WeakBoundObject;` — The object the sequencer track is bound to. Should be an actor or a scene component.
- L49 _private member_ `TWeakObjectPtr<UMovieSceneTrack> WeakMovieSceneTrack;` — The movie scene track.
- L52 _private member_ `TSharedPtr<FTrackInstancePropertyBindings> Binding;` — The property binding for this item.

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace ControlRigEditor` (scope `UE`)

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/AnimDetails/Views/SAnimDetailsView.h` (Private)


#### class `UE::ControlRigEditor::SAnimDetailsView`  
`class SAnimDetailsView : public SCompoundWidget`  
_L14-48_
- inherits: `SCompoundWidget`
- L17 _private function_ `SLATE_BEGIN_ARGS(SAnimDetailsView)`
- L20 _private prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L27 _private function_ `virtual bool SupportsKeyboardFocus() const override`
- L28 _private prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;`
- L32 _private prototype_ `void RefreshDetailsView();` — Refreshes the details view
- L35 _private prototype_ `void OnOptionsChanged();` — Called when options changed
- L38 _private prototype_ `bool ShouldDisplayProperty(const FPropertyAndParent& InPropertyAndParent) const;` — Returns ture if the propery should be displayed
- L41 _private prototype_ `bool IsReadOnlyProperty(const FPropertyAndParent& InPropertyAndParent) const;` — Returns ture if the propery is ready-only
- L44 _private member_ `TSharedPtr<SAnimDetailsSearchBox> SearchBox;` — The search box displayed in this details view
- L47 _private member_ `TWeakPtr<IDetailsView> WeakDetailsView;` — Weak ptr to the details view this widget is displaying

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace ControlRigEditor` (scope `UE`)

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/AnimDetails/Views/SAnimOverrideDetailsView.h` (Private)


#### class `UE::ControlRigEditor::SAnimOverrideDetailsView`  
`class SAnimOverrideDetailsView : public SCompoundWidget`  
_L18-77_
- inherits: `SCompoundWidget`
- L21 _private function_ `SLATE_DECLARE_WIDGET(SAnimOverrideDetailsView, SCompoundWidget) SLATE_BEGIN_ARGS(SAnimOverrideDetailsView)`
- L25 _private prototype_ `SLATE_EVENT(FSimpleDelegate, OnRequestRefreshDetails) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L34 _private prototype_ `void RefreshDetailsView();` — Refreshes the details view
- L37 _private prototype_ `bool ShouldDisplayProperty(const FPropertyAndParent& InPropertyAndParent) const;` — Returns ture if the property should be displayed
- L40 _private prototype_ `bool IsReadOnlyProperty(const FPropertyAndParent& InPropertyAndParent) const;` — Returns ture if the property is ready-only
- L43 _private prototype_ `void OnFinishedChangingOverride(const FPropertyChangedEvent& PropertyChangedEvent);` — Called when editing a property in the override details panel has finished
- L46 _private prototype_ `bool CanMergeObjects(const UObject* InObjectA, const UObject* InObjectB) const;` — Returns true if two objects can be merged for display on the details panel
- L49 _private prototype_ `bool CanCreateWidget(const FOverrideStatusSubject& InSubject) const;` — Returns true if we can create the override widget for a given subject
- L52 _private prototype_ `EOverrideWidgetStatus::Type GetOverrideStatus(const FOverrideStatusSubject& InSubject) const;` — Returns the override status for a given subject
- L55 _private prototype_ `FReply OnAddOverride(const FOverrideStatusSubject& InSubject);` — React to the user interface request to add an override on a given subject
- L58 _private prototype_ `FReply OnClearOverride(const FOverrideStatusSubject& InSubject);` — React to the user interface request to clear all overrides on a given subject
- L61 _private prototype_ `void MapPropertyFromProxyToControl(FString& InOutPropertyPath) const;` — Updates a property path from what it is on the proxy to what it is on the control settings
- L64 _private prototype_ `static UControlRigOverrideAsset* GetOrCreateOverrideAsset(UControlRig* InControlRig);` — Returns the override asset for a given control rig to record changes to
- L67 _private member_ `TWeakPtr<IDetailsView> WeakDetailsView;` — Weak ptr to the details view this widget is displaying
- L70 _private member_ `TSharedPtr<FOverrideStatusDetailsViewObjectFilter> ObjectFilter;` — The object filter used to show the objects in the override details
- L73 _private member_ `TMap<FString,FString> ProxyPropertyToControl;` — A map from proxy property path to control settings property path
- L76 _private member_ `FSimpleDelegate RequestRefreshDetailsDelegate;` — A delegate fired when we request to refresh the details

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace ControlRigEditor` (scope `UE`)

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/AnimDetails/Widgets/SAnimDetailsOptions.h` (Private)


#### class `UE::ControlRigEditor::SAnimDetailsOptions`  
`class SAnimDetailsOptions : public SCompoundWidget`  
_L12-54_
- inherits: `SCompoundWidget`
- desc: The options menu for anim details
- L16 _public function_ `SLATE_BEGIN_ARGS(SAnimDetailsOptions)`
- L20 _public prototype_ `SLATE_EVENT(FSimpleDelegate, OnOptionsChanged) SLATE_END_ARGS() void Construct(const FArguments& InArgs);` — Event raised when options changed
- L29 _private prototype_ `TSharedRef<SWidget> MakeOptionsMenu();` — Creates the options menu
- L32 _private prototype_ `static void PopulateMenu(UToolMenu* InMenu);` — Populates the menu
- L35 _private prototype_ `ECheckBoxState GetExpandTransformPropertiesCheckState() const;` — Returns the check box state for the expand transform properties option
- L38 _private prototype_ `void OnExpandTransformPropertiesCheckStateChanged(const ECheckBoxState InCheckBoxState);` — Called when the check state for the expand transform properties option changed
- L41 _private prototype_ `FText GetNumFractionalDigitsText() const;` — Returns text for the num fractional digits option
- L44 _private prototype_ `void OnNumFractionalDigitsCommitted(const FText& NewText, ETextCommit::Type InTextCommit);` — Called when num fractional digits were committed
- L47 _private prototype_ `ECheckBoxState GetLMBSelectsRangeCheckState() const;` — Returns the check box state for the LMB selects range option
- L50 _private prototype_ `void OnLMBSelectsRangeCheckStateChanged(ECheckBoxState CheckBoxState);` — Called when the check state for the LMB selects range option changed
- L53 _private member_ `FSimpleDelegate OnOptionsChangedDelegate;` — Delegate executed when options changed

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace ControlRigEditor` (scope `UE`)

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/AnimDetails/Widgets/SAnimDetailsPropertySelectionBorder.h` (Private)


#### class `UE::ControlRigEditor::SAnimDetailsPropertySelectionBorder`  
`class SAnimDetailsPropertySelectionBorder : public SCompoundWidget`  
_L17-79_
- inherits: `SCompoundWidget`
- desc: Widget that can wrap a property with a border so it can be selected in anim details
- L21 _public function_ `SLATE_BEGIN_ARGS(SAnimDetailsPropertySelectionBorder) : _RequiresModifierKeys(false)`
- L26 _public prototype_ `SLATE_DEFAULT_SLOT(FArguments, Content) SLATE_ARGUMENT(bool, RequiresModifierKeys) SLATE_ARGUMENT(TSharedPtr<SWidget>, NavigateToWidget) SLATE_END_ARGS() void Construct( const FArguments& InArgs, UAnimDetailsProxyManager& InProxyManager, const TSharedRef<IPropertyHandle>& PropertyHandle);` — The content that can be selected
- L50 _protected prototype_ `virtual void OnMouseEnter(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L51 _protected function_ `virtual bool SupportsKeyboardFocus() const override`
- L52 _protected prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;`
- L57 _private prototype_ `FReply OnBorderMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent);` — Called when the border receives a mouse button down event
- L60 _private prototype_ `bool IsSelected(const UAnimDetailsProxyBase* Proxy) const;` — Tests if the specified proxy is selected
- L63 _private prototype_ `const TArray<UAnimDetailsProxyBase*> MakeProxyArray() const;` — Convenience function to create an array of proxy object ptrs
- L66 _private member_ `TWeakObjectPtr<UAnimDetailsProxyManager> WeakProxyManager;` — The proxy manager that owns the proxies
- L69 _private member_ `TArray<TWeakObjectPtr<UAnimDetailsProxyBase>> WeakProxies;` — Weak proxy objects the property edits
- L72 _private member_ `FName PropertyName;` — The name of the property that can be selected
- L75 _private member_ `FAnimDetailsNavigableWidgetRegistrar NavigableWidgetRegistrar;` — Registrar for the navigable widget registry
- L78 _private member_ `bool bRequiresModifierKeys = false;` — If ture, selection should only occur when a modifier key is pressed

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace ControlRigEditor` (scope `UE`)

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/AnimDetails/Widgets/SAnimDetailsSearchBox.h` (Private)


#### class `UE::ControlRigEditor::SAnimDetailsSearchBox`  
`class SAnimDetailsSearchBox : public SCompoundWidget`  
_L10-40_
- inherits: `SCompoundWidget`
- desc: The search widget to filter anim details
- L14 _public function_ `SLATE_BEGIN_ARGS(SAnimDetailsSearchBox)`
- L18 _public prototype_ `SLATE_EVENT(FSimpleDelegate, OnSearchTextChanged) SLATE_END_ARGS() void Construct(const FArguments& InArgs);` — Event raised when the search text changed
- L26 _public function_ `const FText& GetSearchText() const` — Returns the current search text
- L30 _private prototype_ `void OnSearchTextChanged(const FText& NewText);` — Called when the search text changed
- L33 _private prototype_ `void OnSearchTextCommitted(const FText& NewText, ETextCommit::Type CommitInfo);` — Called when the search text was committed
- L36 _private member_ `FText SearchText;` — The current search text
- L39 _private member_ `FSimpleDelegate OnSearchTextChangedDelegate;` — Delegate executed when the search text changed

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace ControlRigEditor` (scope `UE`)

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/AnimDetails/Widgets/SAnimDetailsValueBoolean.h` (Private)


#### class `UE::ControlRigEditor::SAnimDetailsValueBoolean`  
`class SAnimDetailsValueBoolean : public SCompoundWidget`  
_L16-64_
- inherits: `SCompoundWidget`
- L20 _public function_ `SLATE_BEGIN_ARGS(SAnimDetailsValueBoolean)`
- L24 _public prototype_ `SLATE_ARGUMENT(FLinearColor, LabelColor) SLATE_END_ARGS() virtual ~SAnimDetailsValueBoolean();` — The label color of the widget, only when displaying values
- L37 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<IPropertyHandle>& PropertyHandle);` — Constructs this widget @param ProxyManager					The proxy manager that holds the displayed property @param StructurePropertyHandle		PropertyHandle or the outer struct prooperty @param PropertyHandle				The property that will be displayed
- L41 _private prototype_ `virtual FNavigationReply OnNavigation(const FGeometry& MyGeometry, const FNavigationEvent& InNavigationEvent) override;`
- L45 _private prototype_ `ECheckBoxState GetCheckState() const;` — Returns the current check box state
- L48 _private prototype_ `void OnCheckStateChanged(ECheckBoxState CheckBoxState);` — Called when the check box state changed
- L51 _private member_ `TSharedPtr<SCheckBox> CheckBox;` — The check box used to display the boolean state
- L54 _private member_ `TSharedPtr<SAnimDetailsPropertySelectionBorder> SelectionBorder;` — Border that handles the selction of the displayed property
- L57 _private member_ `FAnimDetailsNavigableWidgetRegistrar NavigableWidgetRegistrar;` — Handles registration of the inner widget that can be navigated to
- L60 _private member_ `TWeakObjectPtr<UAnimDetailsProxyManager> WeakProxyManager;` — The proxy manager that holds the displayed property
- L63 _private member_ `TWeakPtr<IPropertyHandle> WeakPropertyHandle;` — The property handle that is being edited

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace ControlRigEditor` (scope `UE`)

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/AnimDetails/Widgets/SAnimDetailsValueNumeric.h` (Private)


#### class `UE::ControlRigEditor::SAnimDetailsValueNumeric`  
`template <typename NumericType> class SAnimDetailsValueNumeric : public SCompoundWidget`  
_L25-165_
- inherits: `SCompoundWidget`
- desc: A widget to edit the numeric value of a control proxy, with features specific to the anim details view's needs. The numeric entry box always only uses the first object value and propagates changes to other objects and other selected properties.
- L39 _public function_ `SLATE_BEGIN_ARGS(SAnimDetailsValueNumeric<NumericType>) : _Label() , _LabelVAlign(VAlign_Fill) , _LabelLocation(ELabelLocation::Outside) , _LabelPadding(FMargin(3.f, 0.f))`
- L47 _public prototype_ `SLATE_NAMED_SLOT(FArguments, Label) SLATE_ARGUMENT(EVerticalAlignment, LabelVAlign) SLATE_ARGUMENT(ELabelLocation, LabelLocation) SLATE_ARGUMENT(FMargin, LabelPadding) SLATE_END_ARGS() virtual ~SAnimDetailsValueNumeric();` — Slot for this button's content (optional)
- L63 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<IPropertyHandle>& InPropertyHandle);` — Constructs this widget. Edits the provided property handle
- L66 _public prototype_ `void SetDisplayText(const FText& Text);` — Sets the currently displayed text
- L69 _public function_ `static TSharedRef<SWidget> BuildLabel(TAttribute<FText> LabelText, const FSlateColor& ForegroundColor, const FSlateColor& BackgroundColor)` — Builds a text label
- L87 _public function_ `static TSharedRef<SWidget> BuildNarrowColorLabel(FLinearColor LabelColor)` — Builds a narrow color label
- L100 _private prototype_ `virtual FNavigationReply OnNavigation(const FGeometry& MyGeometry, const FNavigationEvent& InNavigationEvent) override;`
- L104 _private prototype_ `void RequestRefresh();` — Refreshes the widget on the next tick
- L107 _private prototype_ `void ForceRefresh();` — Refreshes the widget
- L110 _private prototype_ `NumericType GetValue() const;` — Returns the current widget value
- L113 _private prototype_ `TOptional<FText> OnGetDisplayValue(NumericType SpinBoxValue);` — Returns the display value
- L116 _private prototype_ `void OnValueChanged(NumericType Value);` — Called when the value changed
- L119 _private prototype_ `void OnValueCommitted(NumericType Value, ETextCommit::Type CommitType);` — Called when a value was committed
- L122 _private prototype_ `void OnBeginSliderMovement();` — Called when slider movement begins
- L125 _private prototype_ `void OnEndSliderMovement(NumericType Value);` — Called when slider movement ends
- L128 _private prototype_ `void MultiEditChangePropertyValue(const NumericType Value, const bool bInteractive);` — Sets the property value
- L131 _private member_ `bool bIsUsingSlider = false;` — True while the the value is edited using the slider
- L134 _private member_ `TWeakObjectPtr<UAnimDetailsProxyManager> WeakProxyManager;` — Weak object ptr to the proxy manager that holds displayed values
- L137 _private member_ `TWeakPtr<IPropertyHandle> WeakPropertyHandle;` — The displayed property
- L140 _private member_ `FText DisplayText;` — The current display text
- L143 _private member_ `FTimerHandle RefreshTimerHandle;` — Timer handle for the refresh methods
- L146 _private member_ `TAlwaysValidWidget Label;` — The label widget. SNullWidget if there is no label.
- L149 _private member_ `EVerticalAlignment LabelVAlign;` — Vertical alignment of the label content
- L152 _private member_ `ELabelLocation LabelLocation;` — If the label should be painted inside or outside of the spinbox
- L155 _private member_ `FMargin LabelPadding;` — Padding around the label content
- L158 _private member_ `TSharedPtr<SWidget> SpinBox;` — The spinbox that is used to display the numeric value
- L161 _private member_ `FAnimDetailsNavigableWidgetRegistrar NavigableWidgetRegistrar;` — Handles registration of the inner widget that can be navigated to
- L164 _private member_ `TSharedPtr<TAnimDetailsNumericTypeInterface<NumericType>> TypeInterface;` — Type inteface for the spinbox

#### enum `UE::ControlRigEditor::SAnimDetailsValueNumeric::ELabelLocation`  
`enum class ELabelLocation : uint8`  
_L30-37_
- desc: Defines if where the label of this widget is painted
- L33 _public enumerator_ `Outside` — Outside the bounds of the editable area of this box. Usually preferred for text based labels
- L36 _public enumerator_ `Inside` — Inside the bounds of the editable area of this box. Usually preferred for non-text based labels when a spin box is used the label will appear on top of the spin box in this case

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace ControlRigEditor` (scope `UE`)
- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace ControlRigEditor` (scope `UE`)

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/AnimSequenceConverterFactory.h` (Private)


#### class `UAnimSequenceConverterFactory`  
`class UAnimSequenceConverterFactory : public UAnimSequenceFactory`  
_L11-17_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAnimSequenceFactory`
- L16 _private function_ `virtual bool ConfigureProperties() override` — Act just like the regular UAnimSequenceFactory, but with a pre-configured skeleton

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/AssetDefinition_ControlRig.h` (Private)


#### class `UAssetDefinition_ControlRig`  
`class UAssetDefinition_ControlRig : public UAssetDefinitionDefault`  
_L16-36_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- desc: Asset Definition that provides a unified Content Browser filter for all Control Rig asset types. This creates a single "Control Rig" filter in the Animation category that matches both UControlRigBlueprint and UControlRigRuntimeAsset.
- L21 _public prototype_ `UAssetDefinition_ControlRig();`
- L24 _public prototype_ `virtual FText GetAssetDisplayName() const override;` — UAssetDefinition interface
- L25 _public prototype_ `virtual FLinearColor GetAssetColor() const override;`
- L26 _public prototype_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override;`
- L27 _public prototype_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override;`
- L28 _public function_ `virtual bool CanRegisterStatically() const override`
- L32 _protected prototype_ `virtual void BuildFilters(TArray<FAssetFilterData>& OutFilters) const override;` — Build a single filter that matches both Control Rig Blueprint and Control Rig Runtime Asset
- L35 _private member_ `TArray<FAssetCategoryPath> Categories;`

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/BakeToControlRigSettings.h` (Private)


#### class `UBakeToControlRigSettings`  
`class UBakeToControlRigSettings : public UObject`  
_L11-36_
- reflection: `UCLASS(BlueprintType, config = EditorSettings)`
- inherits: `UObject`
- L14 _public prototype_ `UBakeToControlRigSettings(const FObjectInitializer& Initializer);`
- L19 _public member_ `bool bReduceKeys = false;` — `UPROPERTY(EditAnywhere, Category = "Reduce Keys")` — Reduce Keys
- L24 _public member_ `float Tolerance = 0.001f;` — `UE_DEPRECATED(5.5, "Use the SmartReduce parameter instead.")` — `UPROPERTY()` — Reduce Keys Tolerance
- L27 _public member_ `FSmartReduceParams SmartReduce;` — `UPROPERTY(EditAnywhere, Category = "Reduce Keys", meta = (EditCondition = "bReduceKeys"))`
- L32 _public member_ `bool bResetControls = true;` — `UE_DEPRECATED(5.8, "When baking onto a new control rig always reset controls")` — `UPROPERTY()` — Reset controls to initial value on every frame
- L35 _public prototype_ `void Reset();` — Resets the default properties.

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/ControlRigAnimGraphDetails.h` (Private)


#### class `FControlRigAnimNodeEventNameDetails`  
`class FControlRigAnimNodeEventNameDetails : public IPropertyTypeCustomization`  
_L16-42_
- inherits: `IPropertyTypeCustomization`
- L20 _public function_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance()`
- L26 _public prototype_ `virtual void CustomizeHeader(TSharedRef<class IPropertyHandle> InStructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;` — IPropertyTypeCustomization interface
- L27 _public prototype_ `virtual void CustomizeChildren(TSharedRef<class IPropertyHandle> InStructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L31 _protected prototype_ `FString GetEntryName() const;`
- L32 _protected prototype_ `void SetEntryName(FString InName);`
- L33 _protected prototype_ `void UpdateEntryNameList();`
- L34 _protected prototype_ `void OnEntryNameChanged(TSharedPtr<FString> InItem, ESelectInfo::Type InSelectionInfo);`
- L35 _protected prototype_ `TSharedRef<SWidget> OnGetEntryNameWidget(TSharedPtr<FString> InItem);`
- L36 _protected prototype_ `FText GetEntryNameAsText() const;`
- L38 _protected member_ `TSharedPtr<IPropertyHandle> NameHandle;`
- L39 _protected member_ `TArray<TSharedPtr<FString>> EntryNameList;`
- L40 _protected member_ `TSharedPtr<SSearchableComboBox> SearchableComboBox;`
- L41 _protected member_ `FAnimNode_ControlRigBase* AnimNodeBeingCustomized;`

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/ControlRigAssetActions.h` (Private)


#### class `FControlRigAssetActions`  
`class FControlRigAssetActions : public FAssetTypeActions_ClassTypeBase`  
_L16-44_
- inherits: `FAssetTypeActions_ClassTypeBase`
- L20 _public function_ `virtual FText GetName() const override` — IAssetTypeActions Implementation
- L21 _public function_ `virtual FColor GetTypeColor() const override`
- L22 _public function_ `virtual UClass* GetSupportedClass() const override`
- L23 _public prototype_ `virtual void OpenAssetEditor( const TArray<UObject*>& InObjects, TSharedPtr<class IToolkitHost> EditWithinLevelEditor = TSharedPtr<IToolkitHost>() ) override;`
- L24 _public function_ `virtual uint32 GetCategories() override`
- L25 _public function_ `virtual bool CanFilter() override`
- L26 _public prototype_ `virtual const TArray<FText>& GetSubMenus() const override;`
- L27 _public prototype_ `virtual TSharedPtr<SWidget> GetThumbnailOverlay(const FAssetData& AssetData) const override;`
- L28 _public prototype_ `virtual void PerformAssetDiff(UObject* Asset1, UObject* Asset2, const struct FRevisionInfo& OldRevision, const struct FRevisionInfo& NewRevision) const override;`
- L29 _public prototype_ `virtual TWeakPtr<IClassTypeActions> GetClassTypeActions(const FAssetData& AssetData) const override;`
- L31 _public prototype_ `static void ExtendSketalMeshToolMenu();`
- L33 _public prototype_ `static UControlRigRuntimeAsset* CreateNewControlRigAsset(const FString& InDesiredPackagePath, const bool bModularRig);`
- L34 _public prototype_ `static UControlRigRuntimeAsset* CreateNewControlRigAsset(UControlRigBlueprint* InBlueprint);`
- L35 _public prototype_ `static UControlRigRuntimeAsset* CreateControlRigFromSkeletalMeshOrSkeleton(UObject* InSelectedObject, const bool bModularRig);`
- L39 _public prototype_ `static USkeletalMesh* GetSkeletalMeshFromControlRigAsset(const FAssetData& InAsset);`
- L40 _public prototype_ `static void PostSpawningSkeletalMeshActor(AActor* InSpawnedActor, UObject* InAsset);`
- L41 _public prototype_ `static void OnSpawnedSkeletalMeshActorChanged(UObject* InObject, FPropertyChangedEvent& InEvent, UObject* InAsset);`
- L43 _public member_ `static FDelegateHandle OnSpawnedSkeletalMeshActorChangedHandle;`

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/ControlRigAssetReferenceDetails.h` (Private)


#### class `FControlRigAssetReferenceDetails`  
`class FControlRigAssetReferenceDetails : public IPropertyTypeCustomization`  
_L16-40_
- inherits: `IPropertyTypeCustomization`
- L18 _private member_ `TWeakPtr<IPropertyHandle> WeakStructPropertyHandle;`
- L19 _private member_ `bool bPropertyIsStrongReference;`
- L20 _private member_ `TArray<TSharedRef<FControlRigAssetSoftReference>> Entries;`
- L21 _private member_ `TSharedPtr<SSearchBox> SearchBox;`
- L22 _private member_ `TSharedPtr<SListView<TSharedRef<FControlRigAssetSoftReference>>> AssetList;`
- L23 _private member_ `FString FilterText;`
- L24 _private member_ `FControlRigAssetSoftReference SelectedSource;`
- L25 _private member_ `TSharedPtr<SComboButton> ComboButton;`
- L26 _private member_ `TSharedPtr<FControlRigClassFilter> AssetFilter;`
- L29 _public function_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance()`
- L35 _public prototype_ `virtual void CustomizeHeader(TSharedRef<class IPropertyHandle> InStructPropertyHandle, class FDetailWidgetRow& InHeaderRow, IPropertyTypeCustomizationUtils& InStructCustomizationUtils) override;` — IPropertyTypeCustomization interface
- L36 _public prototype_ `virtual void CustomizeChildren(TSharedRef<class IPropertyHandle> InStructPropertyHandle, class IDetailChildrenBuilder& InStructBuilder, IPropertyTypeCustomizationUtils& InStructCustomizationUtils) override;`
- L38 _public prototype_ `TSharedRef<SWidget> MakeComboMenuContent();`
- L39 _public prototype_ `void OnBrowseToAssetClicked() const;`

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/ControlRigBlueprintActions.h` (Private)


#### class `FControlRigBlueprintActions`  
`class FControlRigBlueprintActions : public FAssetTypeActions_Blueprint`  
_L15-43_
- inherits: `FAssetTypeActions_Blueprint`
- L19 _public function_ `virtual FText GetName() const override` — IAssetTypeActions Implementation
- L20 _public function_ `virtual FColor GetTypeColor() const override`
- L21 _public function_ `virtual UClass* GetSupportedClass() const override`
- L22 _public prototype_ `virtual void OpenAssetEditor( const TArray<UObject*>& InObjects, TSharedPtr<class IToolkitHost> EditWithinLevelEditor = TSharedPtr<IToolkitHost>() ) override;`
- L23 _public function_ `virtual uint32 GetCategories() override`
- L24 _public function_ `virtual bool CanFilter() override`
- L25 _public prototype_ `virtual const TArray<FText>& GetSubMenus() const override;`
- L26 _public prototype_ `virtual TSharedPtr<SWidget> GetThumbnailOverlay(const FAssetData& AssetData) const override;`
- L27 _public prototype_ `virtual void PerformAssetDiff(UObject* Asset1, UObject* Asset2, const struct FRevisionInfo& OldRevision, const struct FRevisionInfo& NewRevision) const override;`
- L30 _public prototype_ `virtual UFactory* GetFactoryForBlueprintType(UBlueprint* InBlueprint) const override;` — FAssetTypeActions_Blueprint interface
- L31 _public function_ `virtual bool CanCreateNewDerivedBlueprint() const override`
- L33 _public prototype_ `static void ExtendSketalMeshToolMenu();`
- L35 _public prototype_ `static UControlRigBlueprint* CreateNewControlRigAsset(const FString& InDesiredPackagePath, const bool bModularRig);`
- L36 _public prototype_ `static UControlRigBlueprint* CreateControlRigFromSkeletalMeshOrSkeleton(UObject* InSelectedObject, const bool bModularRig);`
- L38 _public prototype_ `static USkeletalMesh* GetSkeletalMeshFromControlRigBlueprint(const FAssetData& InAsset);`
- L39 _public prototype_ `static void PostSpawningSkeletalMeshActor(AActor* InSpawnedActor, UObject* InAsset);`
- L40 _public prototype_ `static void OnSpawnedSkeletalMeshActorChanged(UObject* InObject, FPropertyChangedEvent& InEvent, UObject* InAsset);`
- L42 _public member_ `static FDelegateHandle OnSpawnedSkeletalMeshActorChangedHandle;`

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/ControlRigBlueprintDetails.h` (Private)


#### class `FControlRigBlueprintDetails`  
`class FControlRigBlueprintDetails : public IDetailCustomization`  
_L11-19_
- inherits: `IDetailCustomization`
- L15 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L18 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailLayout) override;` — IDetailCustomization interface

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/ControlRigCompilerDetails.h` (Private)


#### class `FRigVMCompileSettingsDetails`  
`class FRigVMCompileSettingsDetails : public IPropertyTypeCustomization`  
_L12-37_
- inherits: `IPropertyTypeCustomization`
- L16 _public function_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance()`
- L22 _public prototype_ `virtual void CustomizeHeader(TSharedRef<class IPropertyHandle> InStructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;` — IPropertyTypeCustomization interface
- L23 _public prototype_ `virtual void CustomizeChildren(TSharedRef<class IPropertyHandle> InStructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L27 _protected prototype_ `FReply OnInspectMemory(ERigVMMemoryType InMemoryType);`
- L28 _protected prototype_ `FReply OnCopyASTClicked();`
- L29 _protected prototype_ `FReply OnCopyByteCodeClicked();`
- L30 _protected prototype_ `FReply OnCopyAnalyticsClicked();`
- L31 _protected prototype_ `FReply OnCopyHierarchyGraphClicked();`
- L33 _protected prototype_ `FReply OnCopyVMExecutionClicked();`
- L36 _protected member_ `FRigVMEditorAssetInterfacePtr BlueprintBeingCustomized = nullptr;`

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/ControlRigComponentDetails.h` (Private)


#### class `FControlRigComponentDetails`  
`class FControlRigComponentDetails : public IDetailCustomization`  
_L10-19_
- inherits: `IDetailCustomization`
- L14 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L17 _public prototype_ `virtual void CustomizeDetails( IDetailLayoutBuilder& DetailBuilder ) override;` — IDetailCustomization interface

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/ControlRigDrawingDetails.h` (Private)


#### struct `FControlRigDrawContainerImportFbxSettings`  
`struct FControlRigDrawContainerImportFbxSettings`  
_L13-31_
- reflection: `USTRUCT()`
- L17 _public function_ `FControlRigDrawContainerImportFbxSettings() : Scale(1.f) , Detail(1) , bMergeCurves(false)`
- L24 _public member_ `float Scale;` — `UPROPERTY(EditAnywhere, Category = "Fbx Import")`
- L27 _public member_ `int32 Detail;` — `UPROPERTY(EditAnywhere, Category = "Fbx Import", meta = (UIMin = "1", UIMax = "8"))`
- L30 _public member_ `bool bMergeCurves;` — `UPROPERTY(EditAnywhere, Category = "Fbx Import")`

#### class `FControlRigDrawContainerDetails`  
`class FControlRigDrawContainerDetails : public IPropertyTypeCustomization`  
_L33-52_
- inherits: `IPropertyTypeCustomization`
- L37 _public function_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance()`
- L43 _public prototype_ `virtual void CustomizeHeader(TSharedRef<class IPropertyHandle> InStructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;` — IPropertyTypeCustomization interface
- L44 _public prototype_ `virtual void CustomizeChildren(TSharedRef<class IPropertyHandle> InStructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L48 _protected prototype_ `FReply OnImportCurvesFromFBXClicked();`
- L49 _protected prototype_ `static void ImportCurvesFromFBX(const FString& InFilePath, FControlRigAssetInterfacePtr InBlueprint, const FControlRigDrawContainerImportFbxSettings& InSettings);`
- L51 _protected member_ `FControlRigAssetInterfacePtr BlueprintBeingCustomized;`

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/ControlRigEditorAssetActions.h` (Private)


#### class `FControlRigEditorAssetActions`  
`class FControlRigEditorAssetActions : public FAssetTypeActions_Base`  
_L13-23_
- inherits: `FAssetTypeActions_Base`
- desc: Asset type actions for UControlRigEditorAsset that redirects to the runtime asset. When users try to open an EditorAsset directly, we redirect them to open the RuntimeAsset instead, which is the outer object that contains the editor data.
- L17 _public function_ `virtual FText GetName() const override` — IAssetTypeActions Implementation
- L18 _public function_ `virtual FColor GetTypeColor() const override`
- L19 _public prototype_ `virtual UClass* GetSupportedClass() const override;`
- L20 _public prototype_ `virtual void OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<class IToolkitHost> EditWithinLevelEditor = TSharedPtr<IToolkitHost>()) override;`
- L21 _public function_ `virtual uint32 GetCategories() override`
- L22 _public function_ `virtual bool CanFilter() override`

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/ControlRigEditorModule.h` (Private)


#### class `FControlRigEditorModule`  
`class FControlRigEditorModule : public IControlRigEditorModule`  
_L29-92_
- inherits: `IControlRigEditorModule`
- L33 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L34 _public prototype_ `virtual void ShutdownModule() override;`
- L37 _public prototype_ `virtual UClass* GetRigVMAssetClass() const override;` — FRigVMEditorModule interface
- L38 _public prototype_ `virtual UClass* GetRigVMLegacyBlueprintClass() const override;`
- L39 _public prototype_ `virtual UClass* GetRigVMEdGraphSchemaClass() const override;`
- L40 _public prototype_ `virtual UScriptStruct* GetRigVMExecuteContextStruct() const override;`
- L41 _public prototype_ `virtual void GetNodeContextMenuActions(TScriptInterface<IRigVMClientHost> RigVMClientHost, const URigVMEdGraphNode* EdGraphNode, URigVMNode* ModelNode, UToolMenu* Menu) const override;`
- L42 _public prototype_ `virtual void GetPinContextMenuActions(TScriptInterface<IRigVMClientHost> RigVMClientHost, const UEdGraphPin* EdGraphPin, URigVMPin* ModelPin, UToolMenu* Menu) const override;`
- L43 _public prototype_ `virtual bool AssetsPublicFunctionsAllowed(const FAssetData& InAssetData) const override;`
- L47 _public prototype_ `virtual TSharedRef<IControlRigEditor> CreateControlRigEditor(const EToolkitMode::Type Mode, const TSharedPtr<IToolkitHost>& InitToolkitHost, UControlRigBlueprint* Blueprint) override;` — IControlRigEditorModule interface
- L48 _public prototype_ `virtual TSharedRef<IControlRigEditor> CreateControlRigEditor(const EToolkitMode::Type Mode, const TSharedPtr<IToolkitHost>& InitToolkitHost, UControlRigRuntimeAsset* Asset) override;`
- L51 _public prototype_ `void AddControlRigExtenderToToolMenu(FName InToolMenuName);` — Animation Toolbar Extender
- L52 _public prototype_ `TSharedRef< SWidget > GenerateAnimationMenu(TWeakPtr<IAnimationEditor> InAnimationEditor);`
- L53 _public prototype_ `void ToggleIsDrivenByLevelSequence(UAnimSequence* AnimSequence)const;`
- L54 _public prototype_ `bool IsDrivenByLevelSequence(UAnimSequence* AnimSequence)const;`
- L55 _public prototype_ `void EditWithFKControlRig(UAnimSequence* AnimSequence, USkeletalMesh* SkelMesh, USkeleton* InSkeleton);`
- L56 _public prototype_ `void BakeToControlRig(UClass* InClass,UAnimSequence* AnimSequence, USkeletalMesh* SkelMesh,USkeleton* InSkeleton);`
- L57 _public prototype_ `static void OpenLevelSequence(UAnimSequence* AnimSequence);`
- L58 _public prototype_ `static void UnLinkLevelSequence(UAnimSequence* AnimSequence);`
- L59 _public prototype_ `static void ModifyLevelSequenceLinkSettings(UAnimSequence* AnimSequence);`
- L60 _public prototype_ `void ExtendAnimSequenceMenu();`
- L62 _public prototype_ `void GetDirectManipulationMenuActions(IRigVMClientHost* RigVMClientHost, URigVMNode* InNode, URigVMPin* ModelPin, UToolMenu* Menu) const;`
- L66 _private prototype_ `TSharedRef<FPropertySection> RegisterPropertySection(FPropertyEditorModule& PropertyModule, FName ClassName, FName SectionName, FText DisplayName);` — property sections
- L67 _private prototype_ `void UnregisterPropertySectionMappings();`
- L69 _private member_ `TMultiMap<FName, FName> RegisteredPropertySections;`
- L72 _private member_ `FDelegateHandle ControlRigParameterTrackCreateEditorHandle;` — Handle for our sequencer control rig parameter track editor
- L74 _private member_ `TArray<TSharedRef<IAssetTypeActions>> RegisteredAssetTypeActions;`
- L77 _private member_ `TArray<FName> ClassesToUnregisterOnShutdown;` — StaticClass is not safe on shutdown, so we cache the name, and use this to unregister on shut down
- L78 _private member_ `TArray<FName> PropertiesToUnregisterOnShutdown;`
- L81 _private member_ `bool bFilterAssetBySkeleton;` — Param to hold Filter Result to pass to Filter
- L84 _private member_ `TArray<int32> WorkflowHandles;` — Handles for all registered workflows
- L86 _private member_ `TSharedPtr<FRigDependencyGraphPanelNodeFactory> RigDependencyGraphPanelNodeFactory;`
- L89 _private member_ `FGuid SpaceCustomChannelGuid;` — Guids for registered functions for creating custom UObjects for space and constraint channels for scripting
- L90 _private member_ `FGuid ConstraintCustomChannelGuid;`

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/ControlRigEditorStyle.h` (Private)


#### class `FControlRigEditorStyle`  
`class FControlRigEditorStyle final : public FSlateStyleSet`  
_L14-299_
- inherits: `FSlateStyleSet`
- L37 _public function_ `FControlRigEditorStyle() : FSlateStyleSet("ControlRigEditorStyle") , BoneUserInterfaceColor(0.6f, 0.6f, 0.6f) , NullUserInterfaceColor(0.75f, 0.75f, 0.75f) , ConnectorUserInterfaceColor(0.0, 112.f/255.f, 224.f/255.f) , SocketUserInterfaceColor(0.0, 112.f/255.f, 224.f/255.f)`
- L284 _public function_ `static FControlRigEditorStyle& Get()`
- L290 _public function_ `~FControlRigEditorStyle()`
- L295 _public member_ `FLinearColor BoneUserInterfaceColor;`
- L296 _public member_ `FLinearColor NullUserInterfaceColor;`
- L297 _public member_ `FLinearColor ConnectorUserInterfaceColor;`
- L298 _public member_ `FLinearColor SocketUserInterfaceColor;`

#### class `FControlRigEditorStyle::FContentRootBracket`  
`class FContentRootBracket`  
_L17-34_
- L20 _public function_ `FContentRootBracket(FControlRigEditorStyle* InStyle, const FString& NewContentRoot) : Style(InStyle) , PreviousContentRoot(InStyle->GetContentRootDir())`
- L27 _public function_ `~FContentRootBracket()`
- L32 _private member_ `FControlRigEditorStyle* Style;`
- L33 _private member_ `FString PreviousContentRoot;`

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/ControlRigElementDetails.h` (Private)


#### class `SRigElementKeyWidget`  
`class SRigElementKeyWidget : public SCompoundWidget`  
_L49-97_
- inherits: `SCompoundWidget`
- L53 _public prototype_ `DECLARE_DELEGATE_RetVal(FText, FGetElementNameAsText);`
- L54 _public prototype_ `DECLARE_DELEGATE_RetVal(ERigElementType, FGetElementType);`
- L55 _public prototype_ `DECLARE_DELEGATE_RetVal(bool, FIsEnabled);`
- L56 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnElementTypeChanged, ERigElementType);`
- L58 _public function_ `SLATE_BEGIN_ARGS(SRigElementKeyWidget)`
- L62 _public prototype_ `SLATE_ARGUMENT(FControlRigAssetInterfacePtr, Asset) SLATE_ARGUMENT(FSlateColor, ActiveBackgroundColor) SLATE_ARGUMENT(FSlateColor, InactiveBackgroundColor) SLATE_ARGUMENT(FSlateColor, ActiveForegroundColor) SLATE_ARGUMENT(FSlateColor, InactiveForegroundColor) SLATE_EVENT(SSearchableComboBox::FOnSelectionChanged, OnElementNameChanged) SLATE_EVENT(FOnClicked, OnGetSelectedClicked) SLATE_EVENT(FOnClicked, OnSelectInHierarchyClicked) SLATE_EVENT(FGetElementNameAsText, OnGetElementNameAsText) SLATE_EVENT(FGetElementType, OnGetElementType) SLATE_EVENT(FOnElementTypeChanged, OnElementTypeChanged) SLATE_EVENT(FIsEnabled, IsEnabled);`
- L75 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedPtr<IPropertyHandle> InNameHandle, TSharedPtr<IPropertyHandle> InTypeHandle);`
- L78 _public prototype_ `void Construct(const FArguments& InArgs);`
- L80 _public prototype_ `void UpdateElementNameList();`
- L83 _private member_ `TSharedPtr<IPropertyHandle> NameHandle;`
- L84 _private member_ `TSharedPtr<IPropertyHandle> TypeHandle;`
- L87 _private member_ `TSharedPtr<SButton> UseSelectedButton;` — Helper buttons.
- L88 _private member_ `TSharedPtr<SButton> SelectElementButton;`
- L90 _private member_ `FGetElementType OnGetElementType;`
- L91 _private member_ `FOnElementTypeChanged OnElementTypeChanged;`
- L92 _private member_ `SSearchableComboBox::FOnSelectionChanged OnElementNameChanged;`
- L94 _private member_ `FControlRigAssetInterfacePtr BlueprintBeingCustomized;`
- L95 _private member_ `TArray<TSharedPtr<FString>> ElementNameList;`
- L96 _private member_ `TSharedPtr<SSearchableComboBox> SearchableComboBox;`

#### class `FRigElementKeyDetails`  
`class FRigElementKeyDetails : public IPropertyTypeCustomization`  
_L99-138_
- inherits: `IPropertyTypeCustomization`
- L103 _public function_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance()`
- L109 _public prototype_ `virtual void CustomizeHeader(TSharedRef<class IPropertyHandle> InStructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;` — IPropertyTypeCustomization interface
- L110 _public prototype_ `virtual void CustomizeChildren(TSharedRef<class IPropertyHandle> InStructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L114 _protected prototype_ `ERigElementType GetElementType() const;`
- L115 _protected prototype_ `FString GetElementName() const;`
- L116 _protected prototype_ `void SetElementName(FString InName);`
- L117 _protected prototype_ `void OnElementNameChanged(TSharedPtr<FString> InItem, ESelectInfo::Type InSelectionInfo);`
- L118 _protected prototype_ `FText GetElementNameAsText() const;`
- L121 _protected member_ `TSharedPtr<SButton> UseSelectedButton;` — Helper buttons.
- L122 _protected member_ `TSharedPtr<SButton> SelectElementButton;`
- L126 _public prototype_ `static FSlateColor OnGetWidgetForeground(const TSharedPtr<SButton> Button);`
- L127 _public prototype_ `static FSlateColor OnGetWidgetBackground(const TSharedPtr<SButton> Button);`
- L131 _protected prototype_ `FReply OnGetSelectedClicked();`
- L132 _protected prototype_ `FReply OnSelectInHierarchyClicked();`
- L134 _protected member_ `TSharedPtr<IPropertyHandle> TypeHandle;`
- L135 _protected member_ `TSharedPtr<IPropertyHandle> NameHandle;`
- L136 _protected member_ `FControlRigAssetInterfacePtr BlueprintBeingCustomized;`
- L137 _protected member_ `TSharedPtr<SRigElementKeyWidget> RigElementKeyWidget;`

#### class `FRigComponentKeyDetails`  
`class FRigComponentKeyDetails : public IPropertyTypeCustomization`  
_L140-169_
- inherits: `IPropertyTypeCustomization`
- L144 _public function_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance()`
- L150 _public prototype_ `virtual void CustomizeHeader(TSharedRef<class IPropertyHandle> InStructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;` — IPropertyTypeCustomization interface
- L151 _public prototype_ `virtual void CustomizeChildren(TSharedRef<class IPropertyHandle> InStructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L155 _protected prototype_ `FRigElementKey GetElementKey() const;`
- L156 _protected prototype_ `FString GetComponentName() const;`
- L157 _protected prototype_ `void SetComponentName(FString InName);`
- L158 _protected prototype_ `void OnComponentNameChanged(TSharedPtr<FString> InItem, ESelectInfo::Type InSelectionInfo);`
- L159 _protected prototype_ `FText GetComponentNameAsText() const;`
- L160 _protected prototype_ `void UpdateComponentNameList();`
- L162 _protected member_ `TSharedPtr<IPropertyHandle> ElementKeyHandle;`
- L163 _protected member_ `TSharedPtr<IPropertyHandle> NameHandle;`
- L164 _protected member_ `FControlRigAssetInterfacePtr BlueprintBeingCustomized;`
- L166 _protected member_ `TArray<TSharedPtr<FString>> ComponentNameList;`
- L167 _protected member_ `TSharedPtr<SSearchableComboBox> SearchableComboBox;`

#### enum `ERigElementDetailsTransformComponent`  
`enum class ERigElementDetailsTransformComponent : uint8`  
_L172-183_
- reflection: `UENUM()`
- L174 _public enumerator_ `TranslationX`
- L175 _public enumerator_ `TranslationY`
- L176 _public enumerator_ `TranslationZ`
- L177 _public enumerator_ `RotationRoll`
- L178 _public enumerator_ `RotationPitch`
- L179 _public enumerator_ `RotationYaw`
- L180 _public enumerator_ `ScaleX`
- L181 _public enumerator_ `ScaleY`
- L182 _public enumerator_ `ScaleZ`

#### class `FRigComputedTransformDetails`  
`class FRigComputedTransformDetails : public IPropertyTypeCustomization`  
_L185-205_
- inherits: `IPropertyTypeCustomization`
- L189 _public function_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance()`
- L195 _public prototype_ `virtual void CustomizeHeader(TSharedRef<class IPropertyHandle> InStructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;` — IPropertyTypeCustomization interface
- L196 _public prototype_ `virtual void CustomizeChildren(TSharedRef<class IPropertyHandle> InStructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L200 _protected member_ `TSharedPtr<IPropertyHandle> TransformHandle;`
- L201 _protected member_ `FEditPropertyChain PropertyChain;`
- L202 _protected member_ `FControlRigAssetInterfacePtr BlueprintBeingCustomized;`
- L204 _protected prototype_ `void OnTransformChanged(FEditPropertyChain* InPropertyChain);`

#### class `FRigControlTransformChannelDetails`  
`class FRigControlTransformChannelDetails : public IPropertyTypeCustomization`  
_L207-230_
- inherits: `IPropertyTypeCustomization`
- L211 _public function_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance()`
- L217 _public prototype_ `virtual void CustomizeHeader(TSharedRef<class IPropertyHandle> InStructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;` — IPropertyTypeCustomization interface
- L218 _public prototype_ `virtual void CustomizeChildren(TSharedRef<class IPropertyHandle> InStructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L221 _protected prototype_ `ERigControlTransformChannel GetChannel() const;`
- L222 _protected function_ `int32 GetChannelAsInt32() const`
- L223 _protected prototype_ `void OnChannelChanged(int32 NewSelection, ESelectInfo::Type);`
- L226 _public prototype_ `static const TArray<ERigControlTransformChannel>* GetVisibleChannelsForControlType(ERigControlType InControlType);`
- L229 _private member_ `TSharedPtr<IPropertyHandle> Handle;`

#### class `FRigBaseElementDetails`  
`class FRigBaseElementDetails : public IDetailCustomization`  
_L232-394_
- inherits: `IDetailCustomization`
- L237 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;` — IDetailCustomization interface
- L238 _public function_ `virtual void BeginDestroy()`
- L239 _public prototype_ `virtual void PendingDelete() override;`
- L241 _public prototype_ `FRigElementKey GetElementKey() const;`
- L242 _public prototype_ `FText GetName() const;`
- L243 _public prototype_ `void SetName(const FText& InNewText, ETextCommit::Type InCommitType);`
- L244 _public prototype_ `bool OnVerifyNameChanged(const FText& InText, FText& OutErrorMessage);`
- L245 _public prototype_ `FText GetSpawnIndex() const;`
- L247 _public prototype_ `void OnStructContentsChanged(FProperty* InProperty, const TSharedRef<IPropertyUtilities> PropertyUtilities);`
- L248 _public prototype_ `bool IsConstructionModeEnabled() const;`
- L250 _public prototype_ `FText GetParentElementName() const;`
- L252 _public prototype_ `TArray<FRigElementKey> GetElementKeys() const;`
- L255 _public function_ `template<typename T> TArray<T> GetElementsInDetailsView(const TArray<FRigElementKey>& InFilter = TArray<FRigElementKey>()) const`
- L354 _public prototype_ `const FPerElementInfo& FindElement(const FRigElementKey& InKey) const;`
- L355 _public prototype_ `bool IsAnyElementOfType(ERigElementType InType) const;`
- L356 _public prototype_ `bool IsAnyElementNotOfType(ERigElementType InType) const;`
- L357 _public prototype_ `bool IsAnyControlOfAnimationType(ERigControlAnimationType InType) const;`
- L358 _public prototype_ `bool IsAnyControlNotOfAnimationType(ERigControlAnimationType InType) const;`
- L359 _public prototype_ `bool IsAnyControlOfValueType(ERigControlType InType) const;`
- L360 _public prototype_ `bool IsAnyControlNotOfValueType(ERigControlType InType) const;`
- L361 _public prototype_ `bool IsAnyElementProcedural() const;`
- L362 _public prototype_ `bool IsAnyConnectorImported() const;`
- L363 _public prototype_ `bool IsAnyConnectorPrimary() const;`
- L364 _public prototype_ `bool GetCommonElementType(ERigElementType& OutElementType) const;`
- L365 _public prototype_ `bool GetCommonControlType(ERigControlType& OutControlType) const;`
- L366 _public prototype_ `bool GetCommonAnimationType(ERigControlAnimationType& OutAnimationType) const;`
- L367 _public prototype_ `const FPerElementInfo* FindElementByPredicate(const TFunction<bool(const FPerElementInfo&)>& InPredicate) const;`
- L368 _public prototype_ `bool ContainsElementByPredicate(const TFunction<bool(const FPerElementInfo&)>& InPredicate) const;`
- L370 _public prototype_ `static void RegisterSectionMappings(FPropertyEditorModule& PropertyEditorModule);`
- L371 _public prototype_ `virtual void RegisterSectionMappings(FPropertyEditorModule& PropertyEditorModule, UClass* InClass);`
- L373 _public prototype_ `FReply OnSelectParentElementInHierarchyClicked();`
- L374 _public prototype_ `FReply OnSelectElementClicked(const FRigElementKey& InKey);`
- L378 _protected prototype_ `void CustomizeComponents(IDetailLayoutBuilder& DetailBuilder);`
- L379 _protected prototype_ `void CustomizeMetadata(IDetailLayoutBuilder& DetailBuilder);`
- L381 _protected member_ `TArray<FPerElementInfo> PerElementInfos;`
- L382 _protected member_ `FDelegateHandle MetadataHandle;`
- L383 _protected member_ `TArray<TUniquePtr<FControlRigInteractionScope>> InteractionScopes;`
- L391 _protected member_ `TArray<FSharedComponent> SharedComponents;`
- L393 _protected member_ `TSharedPtr<SButton> SelectParentElementButton;`

#### struct `FRigBaseElementDetails::FPerElementInfo`  
`struct FPerElementInfo`  
_L270-352_
- L272 _public function_ `FPerElementInfo() : WrapperObject() , Element() , DefaultElement()`
- L278 _public function_ `bool IsValid() const`
- L279 _public function_ `bool IsProcedural() const`
- L280 _public function_ `operator bool() const`
- L282 _public function_ `URigHierarchy* GetHierarchy() const`
- L283 _public function_ `URigHierarchy* GetDefaultHierarchy() const`
- L293 _public function_ `UControlRigBlueprint* GetBlueprint() const` — `UE_DEPRECATED(5.7, "Use GetAsset instead")`
- L298 _public function_ `FControlRigAssetInterfacePtr GetAsset() const`
- L334 _public function_ `template<typename T = FRigBaseElement> T* GetElement() const`
- L340 _public function_ `template<typename T = FRigBaseElement> T* GetDefaultElement() const`
- L349 _public member_ `TWeakObjectPtr<URigVMDetailsViewWrapperObject> WrapperObject;`
- L350 _public member_ `FRigElementHandle Element;`
- L351 _public member_ `FRigElementHandle DefaultElement;`

#### struct `FRigBaseElementDetails::FSharedComponent`  
`struct FSharedComponent`  
_L385-390_
- L387 _public member_ `FRigComponentHandle Handle;`
- L388 _public member_ `const UScriptStruct* ScriptStruct = nullptr;`
- L389 _public member_ `bool bIsProcedural = false;`

#### enum `ERigTransformElementDetailsTransform::Type`  
`enum Type`  
_L398-406_
- L400 _public enumerator_ `Initial`
- L401 _public enumerator_ `Current`
- L402 _public enumerator_ `Offset`
- L403 _public enumerator_ `Minimum`
- L404 _public enumerator_ `Maximum`
- L405 _public enumerator_ `Max`

#### class `FRigTransformElementDetails`  
`class FRigTransformElementDetails : public FRigBaseElementDetails`  
_L409-459_
- inherits: `FRigBaseElementDetails`
- L414 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;` — IDetailCustomization interface
- L417 _public prototype_ `virtual void RegisterSectionMappings(FPropertyEditorModule& PropertyEditorModule, UClass* InClass) override;` — FRigBaseElementDetails interface
- L419 _public prototype_ `virtual void CustomizeTransform(IDetailLayoutBuilder& DetailBuilder);`
- L423 _protected prototype_ `bool IsCurrentLocalEnabled() const;`
- L425 _protected prototype_ `void AddChoiceWidgetRow(IDetailCategoryBuilder& InCategory, const FText& InSearchText, TSharedRef<SWidget> InWidget);`
- L429 _protected prototype_ `FDetailWidgetRow& CreateTransformComponentValueWidgetRow( ERigControlType InControlType, const TArray<FRigElementKey>& Keys, SAdvancedTransformInputBox<FEulerTransform>::FArguments TransformWidgetArgs, IDetailCategoryBuilder& CategoryBuilder, const FText& Label, const FText& Tooltip, ERigTransformElementDetailsTransform::Type CurrentTransformType, ERigControlValueType ValueType, TSharedPtr<SWidget> NameContent = TSharedPtr<SWidget>());`
- L440 _protected prototype_ `FDetailWidgetRow& CreateEulerTransformValueWidgetRow( const TArray<FRigElementKey>& Keys, SAdvancedTransformInputBox<FEulerTransform>::FArguments TransformWidgetArgs, IDetailCategoryBuilder& CategoryBuilder, const FText& Label, const FText& Tooltip, ERigTransformElementDetailsTransform::Type CurrentTransformType, ERigControlValueType ValueType, TSharedPtr<SWidget> NameContent = TSharedPtr<SWidget>());`
- L450 _protected prototype_ `static ERigTransformElementDetailsTransform::Type GetTransformTypeFromValueType(ERigControlValueType InValueType);`
- L454 _private member_ `static TSharedPtr<TArray<ERigTransformElementDetailsTransform::Type>> PickedTransforms;`
- L458 _protected member_ `TSharedPtr<FScopedTransaction> SliderTransaction;`

#### class `FRigBoneElementDetails`  
`class FRigBoneElementDetails : public FRigTransformElementDetails`  
_L461-473_
- inherits: `FRigTransformElementDetails`
- L466 _public function_ `static TSharedRef<IDetailCustomization> MakeInstance()` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L472 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;` — IDetailCustomization interface

#### class `FRigControlElementDetails`  
`class FRigControlElementDetails : public FRigTransformElementDetails`  
_L475-864_
- inherits: `FRigTransformElementDetails`
- L480 _public function_ `static TSharedRef<IDetailCustomization> MakeInstance()` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L486 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;` — IDetailCustomization interface
- L487 _public prototype_ `void CustomizeValue(IDetailLayoutBuilder& DetailBuilder);`
- L488 _public prototype_ `void CustomizeControl(IDetailLayoutBuilder& DetailBuilder);`
- L489 _public prototype_ `void CustomizeAnimationChannels(IDetailLayoutBuilder& DetailBuilder);`
- L490 _public prototype_ `void CustomizeAvailableSpaces(IDetailLayoutBuilder& DetailBuilder);`
- L491 _public prototype_ `void CustomizeShape(IDetailLayoutBuilder& DetailBuilder);`
- L492 _public prototype_ `virtual void BeginDestroy() override;`
- L495 _public prototype_ `virtual void RegisterSectionMappings(FPropertyEditorModule& PropertyEditorModule, UClass* InClass) override;` — FRigBaseElementDetails interface
- L497 _public prototype_ `bool IsShapeEnabled() const;`
- L499 _public prototype_ `const TArray<TSharedPtr<FRigVMStringWithTag>>& GetShapeNameList() const;`
- L501 _public prototype_ `FText GetDisplayName() const;`
- L502 _public prototype_ `void SetDisplayName(const FText& InNewText, ETextCommit::Type InCommitType);`
- L503 _public prototype_ `FText GetDisplayNameForElement(const FRigElementKey& InKey) const;`
- L504 _public prototype_ `void SetDisplayNameForElement(const FText& InNewText, ETextCommit::Type InCommitType, const FRigElementKey& InKeyToRename);`
- L505 _public prototype_ `bool OnVerifyDisplayNameChanged(const FText& InText, FText& OutErrorMessage, const FRigElementKey& InKeyToRename);`
- L507 _public prototype_ `void OnCopyShapeProperties();`
- L508 _public prototype_ `void OnPasteShapeProperties();`
- L510 _public prototype_ `FDetailWidgetRow& CreateBoolValueWidgetRow( const TArray<FRigElementKey>& Keys, IDetailCategoryBuilder& CategoryBuilder, const FText& Label, const FText& Tooltip, ERigControlValueType ValueType, TAttribute<EVisibility> Visibility = EVisibility::Visible, TSharedPtr<SWidget> NameContent = TSharedPtr<SWidget>());`
- L519 _public prototype_ `FDetailWidgetRow& CreateFloatValueWidgetRow( const TArray<FRigElementKey>& Keys, IDetailCategoryBuilder& CategoryBuilder, const FText& Label, const FText& Tooltip, ERigControlValueType ValueType, TAttribute<EVisibility> Visibility = EVisibility::Visible, TSharedPtr<SWidget> NameContent = TSharedPtr<SWidget>());`
- L528 _public prototype_ `FDetailWidgetRow& CreateIntegerValueWidgetRow( const TArray<FRigElementKey>& Keys, IDetailCategoryBuilder& CategoryBuilder, const FText& Label, const FText& Tooltip, ERigControlValueType ValueType, TAttribute<EVisibility> Visibility = EVisibility::Visible, TSharedPtr<SWidget> NameContent = TSharedPtr<SWidget>());`
- L537 _public prototype_ `FDetailWidgetRow& CreateEnumValueWidgetRow( const TArray<FRigElementKey>& Keys, IDetailCategoryBuilder& CategoryBuilder, const FText& Label, const FText& Tooltip, ERigControlValueType ValueType, TAttribute<EVisibility> Visibility = EVisibility::Visible, TSharedPtr<SWidget> NameContent = TSharedPtr<SWidget>());`
- L546 _public prototype_ `FDetailWidgetRow& CreateVector2DValueWidgetRow( const TArray<FRigElementKey>& Keys, IDetailCategoryBuilder& CategoryBuilder, const FText& Label, const FText& Tooltip, ERigControlValueType ValueType, TAttribute<EVisibility> Visibility = EVisibility::Visible, TSharedPtr<SWidget> NameContent = TSharedPtr<SWidget>());`
- L559 _public function_ `template<typename T> static bool Equals(const T& A, const T& B)` — this is a template since we specialize it further down for a 'nearly equals' implementation for floats and math types.
- L567 _private function_ `template<typename T> FDetailWidgetRow& CreateNumericValueWidgetRow( const TArray<FRigElementKey>& Keys, IDetailCategoryBuilder& CategoryBuilder, const FText& Label, const FText& Tooltip, ERigControlValueType ValueType, TAttribute<EVisibility> Visibility = EVisibility::Visible, TSharedPtr<SWidget> NameContent = TSharedPtr<SWidget>())`
- L839 _private prototype_ `FReply OnAddAnimationChannelClicked();` — animation channel related callbacks
- L840 _private prototype_ `TSharedRef<ITableRow> HandleGenerateAnimationChannelTypeRow(TSharedPtr<ERigControlType> ControlType, const TSharedRef<STableViewBase>& OwnerTable, FRigElementKey ControlKey);`
- L843 _private function_ `const FRigHierarchyTreeDisplaySettings& GetDisplaySettings() const` — multi parent related callbacks
- L844 _private prototype_ `TSharedRef<SWidget> GetAddSpaceContent(const TSharedRef<IPropertyUtilities> PropertyUtilities);`
- L845 _private prototype_ `FReply OnAddSpaceMouseDown(const FGeometry& InGeometry, const FPointerEvent& InPointerEvent, const TSharedRef<IPropertyUtilities> PropertyUtilities);`
- L846 _private prototype_ `void OnAddSpaceSelection(TSharedPtr<FRigHierarchyTreeElement> Selection, ESelectInfo::Type SelectInfo, const TSharedRef<IPropertyUtilities> PropertyUtilities);`
- L848 _private prototype_ `void HandleControlTypeChanged(TSharedPtr<ERigControlType> ControlType, ESelectInfo::Type SelectInfo, FRigElementKey ControlKey, const TSharedRef<IPropertyUtilities> PropertyUtilities);`
- L849 _private prototype_ `void HandleControlTypeChanged(ERigControlType ControlType, TArray<FRigElementKey> ControlKeys, const TSharedRef<IPropertyUtilities> PropertyUtilities);`
- L850 _private prototype_ `void HandleControlEnumChanged(TSharedPtr<FString> InItem, ESelectInfo::Type InSelectionInfo, const TSharedRef<IPropertyUtilities> PropertyUtilities);`
- L852 _private member_ `TArray<TSharedPtr<FRigVMStringWithTag>> ShapeNameList;`
- L853 _private member_ `TSharedPtr<FRigInfluenceEntryModifier> InfluenceModifier;`
- L854 _private member_ `TSharedPtr<FStructOnScope> InfluenceModifierStruct;`
- L856 _private member_ `TSharedPtr<IPropertyHandle> ShapeNameHandle;`
- L857 _private member_ `TSharedPtr<IPropertyHandle> ShapeColorHandle;`
- L859 _private member_ `TSharedPtr<SControlRigShapeNameList> ShapeNameListWidget;`
- L860 _private member_ `static TSharedPtr<TArray<ERigControlValueType>> PickedValueTypes;`
- L862 _private member_ `FRigHierarchyTreeDisplaySettings DisplaySettings;`
- L863 _private member_ `TSharedPtr<SMenuAnchor> AddSpaceMenuAnchor;`
- L867 _function_ `template<> inline bool FRigControlElementDetails::Equals<float>(const float& A, const float& B)`
- L873 _function_ `template<> inline bool FRigControlElementDetails::Equals<double>(const double& A, const double& B)`
- L879 _function_ `template<> inline bool FRigControlElementDetails::Equals<FVector>(const FVector& A, const FVector& B)`
- L885 _function_ `template<> inline bool FRigControlElementDetails::Equals<FRotator>(const FRotator& A, const FRotator& B)`
- L891 _function_ `template<> inline bool FRigControlElementDetails::Equals<FEulerTransform>(const FEulerTransform& A, const FEulerTransform& B)`

#### class `FRigNullElementDetails`  
`class FRigNullElementDetails : public FRigTransformElementDetails`  
_L896-908_
- inherits: `FRigTransformElementDetails`
- L901 _public function_ `static TSharedRef<IDetailCustomization> MakeInstance()` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L907 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;` — IDetailCustomization interface

#### class `FRigConnectorElementDetails`  
`class FRigConnectorElementDetails : public FRigTransformElementDetails`  
_L910-941_
- inherits: `FRigTransformElementDetails`
- L915 _public function_ `static TSharedRef<IDetailCustomization> MakeInstance()` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L921 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;` — IDetailCustomization interface
- L923 _public prototype_ `void CustomizeSettings(IDetailLayoutBuilder& DetailBuilder);`
- L924 _public prototype_ `void CustomizeConnectorTargets(IDetailLayoutBuilder& DetailBuilder);`
- L927 _private prototype_ `TOptional<EConnectorType> GetConnectorType() const;`
- L928 _private prototype_ `TOptional<bool> GetIsConnectorArray() const;`
- L929 _private prototype_ `bool CanBeArray() const;`
- L930 _private prototype_ `bool OnTargetsChanged(TArray<FRigElementKey> InTargets);`
- L933 _private prototype_ `void RequestRefresh();` — Requests to refresh these details
- L935 _private member_ `TSharedPtr<IPropertyHandle> ConnectorTypeHandle;`
- L936 _private member_ `TSharedPtr<IPropertyHandle> IsArrayHandle;`
- L937 _private member_ `TSharedPtr<IPropertyHandle> IsPostConstructionHandle;`
- L940 _private member_ `TSharedPtr<IPropertyUtilities> PropertyUtils;` — Property utils for this customization

#### class `FRigSocketElementDetails`  
`class FRigSocketElementDetails : public FRigNullElementDetails`  
_L943-965_
- inherits: `FRigNullElementDetails`
- L948 _public function_ `static TSharedRef<IDetailCustomization> MakeInstance()` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L954 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;` — IDetailCustomization interface
- L956 _public prototype_ `void CustomizeSettings(IDetailLayoutBuilder& DetailBuilder);`
- L960 _private prototype_ `FReply SetSocketColor(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent);`
- L961 _private prototype_ `FLinearColor GetSocketColor() const;`
- L962 _private prototype_ `void OnSocketColorPicked(FLinearColor NewColor);`
- L963 _private prototype_ `void SetSocketDescription(const FText& InDescription, ETextCommit::Type InCommitType);`
- L964 _private prototype_ `FText GetSocketDescription() const;`

#### class `FRigConnectionRuleDetails`  
`class FRigConnectionRuleDetails : public IPropertyTypeCustomization`  
_L967-993_
- inherits: `IPropertyTypeCustomization`
- L971 _public function_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance()`
- L977 _public prototype_ `virtual void CustomizeHeader(TSharedRef<class IPropertyHandle> InStructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;` — IPropertyTypeCustomization interface
- L978 _public prototype_ `virtual void CustomizeChildren(TSharedRef<class IPropertyHandle> InStructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L982 _protected prototype_ `TSharedRef<SWidget> GenerateStructPicker();`
- L983 _protected prototype_ `void OnPickedStruct(const UScriptStruct* ChosenStruct);`
- L984 _protected prototype_ `FText OnGetStructTextValue() const;`
- L985 _protected prototype_ `void OnRuleContentChanged();`
- L987 _protected member_ `FRigConnectionRuleStash RuleStash;`
- L988 _protected member_ `TSharedPtr<FStructOnScope> Storage;`
- L989 _protected member_ `FControlRigAssetInterfacePtr BlueprintBeingCustomized;`
- L990 _protected member_ `TSharedPtr<IPropertyHandle> StructPropertyHandle;`
- L991 _protected member_ `TSharedPtr<IPropertyUtilities> PropertyUtilities;`
- L992 _protected member_ `TAttribute<bool> EnabledAttribute;`

#### class `FRigBaseComponentDetails`  
`class FRigBaseComponentDetails : public IDetailCustomization`  
_L995-1007_
- inherits: `IDetailCustomization`
- L1000 _public function_ `static TSharedRef<IDetailCustomization> MakeInstance()` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L1006 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;` — IDetailCustomization interface

#### Free symbols / members of external scopes

- L37 _namespace_ `namespace FRigElementKeyDetailsDefs`
- L40 _variable_ `static const float ActivePinForegroundAlpha = 1.f;` (scope `FRigElementKeyDetailsDefs`) — Active foreground pin alpha
- L42 _variable_ `static const float InactivePinForegroundAlpha = 0.15f;` (scope `FRigElementKeyDetailsDefs`) — InActive foreground pin alpha
- L44 _variable_ `static const float ActivePinBackgroundAlpha = 0.8f;` (scope `FRigElementKeyDetailsDefs`) — Active background pin alpha
- L46 _variable_ `static const float InactivePinBackgroundAlpha = 0.4f;` (scope `FRigElementKeyDetailsDefs`) — InActive background pin alpha
- L53 _delegate_ `DECLARE_DELEGATE_RetVal(FText, FGetElementNameAsText);`
- L54 _delegate_ `DECLARE_DELEGATE_RetVal(ERigElementType, FGetElementType);`
- L55 _delegate_ `DECLARE_DELEGATE_RetVal(bool, FIsEnabled);`
- L56 _delegate_ `DECLARE_DELEGATE_OneParam(FOnElementTypeChanged, ERigElementType);`
- L396 _namespace_ `namespace ERigTransformElementDetailsTransform`
- L610 _function_ `` (scope `FRigControlElementDetails::CreateNumericValueWidgetRow`)
- L807 _function_ `}), FCanExecuteAction::CreateLambda([bIsEnabled]()` (scope `FRigControlElementDetails::CreateNumericValueWidgetRow`)

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/ControlRigGizmoLibraryActions.h` (Private)


#### class `FControlRigShapeLibraryActions`  
`class FControlRigShapeLibraryActions : public FAssetTypeActions_Base`  
_L11-22_
- inherits: `FAssetTypeActions_Base`
- L15 _public prototype_ `virtual void GetActions(const TArray<UObject*>& InObjects, FMenuBuilder& MenuBuilder) override;` — IAssetTypeActions Implementation
- L16 _public function_ `virtual FText GetName() const override`
- L17 _public function_ `virtual FColor GetTypeColor() const override`
- L18 _public function_ `virtual UClass* GetSupportedClass() const override`
- L19 _public function_ `virtual bool CanFilter() override`
- L20 _public function_ `virtual uint32 GetCategories() override`
- L21 _public prototype_ `virtual const TArray<FText>& GetSubMenus() const override;`

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/ControlRigGizmoLibraryFactory.h` (Private)


#### class `UControlRigShapeLibraryFactory`  
`class UControlRigShapeLibraryFactory : public UFactory`  
_L12-23_
- reflection: `UCLASS(MinimalAPI, HideCategories=Object)`
- inherits: `UFactory`
- L17 _public prototype_ `UControlRigShapeLibraryFactory();`
- L20 _public prototype_ `virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;` — UFactory Interface
- L21 _public prototype_ `virtual FText GetDisplayName() const override;`
- L22 _public prototype_ `virtual uint32 GetMenuCategories() const override;`

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/ControlRigHierarchyCommands.h` (Private)


#### class `FControlRigHierarchyCommands`  
`class FControlRigHierarchyCommands : public TCommands<FControlRigHierarchyCommands>`  
_L9-153_
- inherits: `TCommands<FControlRigHierarchyCommands>`
- L12 _public function_ `FControlRigHierarchyCommands() : TCommands<FControlRigHierarchyCommands> ( "ControlRigHierarchy", NSLOCTEXT("Contexts", "RigHierarchy", "Rig Hierarchy"), NAME_None,`
- L22 _public member_ `TSharedPtr< FUICommandInfo > AddBoneItem;` — Add Item at origin
- L25 _public member_ `TSharedPtr< FUICommandInfo > AddControlItem;` — Add Item at origin
- L28 _public member_ `TSharedPtr< FUICommandInfo > AddAnimationChannelItem;` — Add an animation channel
- L31 _public member_ `TSharedPtr< FUICommandInfo > AddNullItem;` — Add Item at origin
- L34 _public member_ `TSharedPtr< FUICommandInfo > AddConnectorItem;` — Add Item at origin
- L37 _public member_ `TSharedPtr< FUICommandInfo > AddSocketItem;` — Add Item at origin
- L40 _public member_ `TSharedPtr< FUICommandInfo > FindReferencesOfItem;` — Find all references of an item in the graphs
- L43 _public member_ `TSharedPtr< FUICommandInfo > DuplicateItem;` — Duplicate currently selected items
- L46 _public member_ `TSharedPtr< FUICommandInfo > MirrorItem;` — Mirror currently selected items
- L49 _public member_ `TSharedPtr< FUICommandInfo > DeleteItem;` — Delete currently selected items
- L52 _public member_ `TSharedPtr< FUICommandInfo > RenameItem;` — Rename selected item
- L55 _public member_ `TSharedPtr< FUICommandInfo > CopyItems;` — Copy the selected items.
- L58 _public member_ `TSharedPtr< FUICommandInfo > PasteItems;` — Paste the selected items.
- L61 _public member_ `TSharedPtr< FUICommandInfo > PasteLocalTransforms;` — Paste Local Transform", "Paste the local transforms.
- L64 _public member_ `TSharedPtr< FUICommandInfo > PasteGlobalTransforms;` — Paste Global Transform", "Paste the global transforms.
- L67 _public member_ `TSharedPtr<FUICommandInfo> ResetTransform;` — Reset transform
- L70 _public member_ `TSharedPtr<FUICommandInfo> ResetAllTransforms;` — Reset all transforms
- L73 _public member_ `TSharedPtr<FUICommandInfo> ResetNull;` — Reset space
- L76 _public member_ `TSharedPtr<FUICommandInfo> ZeroControls;` — Sets the transform of the control as offset, zeroes the initial and current transform
- L79 _public member_ `TSharedPtr<FUICommandInfo> ZeroControlsFromClosestBone;` — Sets the offset to the transform of the closest bone, zeroes the initial and current transform
- L82 _public member_ `TSharedPtr<FUICommandInfo> ZeroControlShape;` — Sets the current shape relative to the control's offset, zeroes the control's initial and current transform
- L85 _public member_ `TSharedPtr<FUICommandInfo> SetInitialTransformFromCurrent;` — Set the current transform of selected bone, null or connector as its initial and current transform
- L88 _public member_ `TSharedPtr<FUICommandInfo> FrameSelection;` — frames the selection in the tree
- L91 _public member_ `TSharedPtr<FUICommandInfo> ControlBoneTransform;` — sets the bone transform using a shape
- L94 _public member_ `TSharedPtr<FUICommandInfo> ControlSpaceTransform;` — sets the space transform using a shape
- L97 _public member_ `TSharedPtr<FUICommandInfo> Unparent;` — Unparents the selected elements from the hierarchy
- L100 _public member_ `TSharedPtr< FUICommandInfo > FilteringFlattensHierarchy;` — Flatten hierarchy on filter
- L103 _public member_ `TSharedPtr< FUICommandInfo > HideParentsWhenFiltering;` — Hide parents on filter
- L106 _public member_ `TSharedPtr< FUICommandInfo > ArrangeByModules;` — Arrange the controls by modules in a modular rig
- L109 _public member_ `TSharedPtr< FUICommandInfo > FlattenModules;` — Flatten the modules in a modular rig
- L112 _public member_ `TSharedPtr< FUICommandInfo > SetMultiRigMode_All;` — Options of outliner reflection mode for multi rigs
- L113 _public member_ `TSharedPtr< FUICommandInfo > SetMultiRigMode_SelectedRigs;` — show only rigs with selected controls
- L114 _public member_ `TSharedPtr< FUICommandInfo > SetMultiRigMode_SelectedModules;` — show only modules with selected controls (for modular rigs)
- L117 _public member_ `TSharedPtr< FUICommandInfo > ShowImportedBones;` — Show imported bones
- L120 _public member_ `TSharedPtr< FUICommandInfo > ShowBones;` — Show bones
- L123 _public member_ `TSharedPtr< FUICommandInfo > ShowControls;` — Show controls
- L126 _public member_ `TSharedPtr< FUICommandInfo > ShowNulls;` — Show spaces
- L129 _public member_ `TSharedPtr< FUICommandInfo > ShowReferences;` — Show references
- L132 _public member_ `TSharedPtr< FUICommandInfo > ShowSockets;` — Show sockets
- L135 _public member_ `TSharedPtr< FUICommandInfo > ShowComponents;` — Show components
- L138 _public member_ `TSharedPtr< FUICommandInfo > ToggleControlShapeTransformEdit;` — Toggle Shape Transform Edit
- L141 _public member_ `TSharedPtr< FUICommandInfo > SpaceSwitching;` — Space switch as it would look like for animator
- L144 _public member_ `TSharedPtr< FUICommandInfo > ShowIconColors;` — Whether to tint the icons with the element color
- L147 _public member_ `TSharedPtr< FUICommandInfo > FocusOnSelection;` — Scroll to selection when it changes
- L152 _public prototype_ `virtual void RegisterCommands() override;` — Initialize commands

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/ControlRigInfluenceMapDetails.h` (Private)


#### class `FRigInfluenceMapPerEventDetails`  
`class FRigInfluenceMapPerEventDetails : public IDetailCustomization`  
_L14-31_
- inherits: `IDetailCustomization`
- L18 _public function_ `static TSharedRef<IDetailCustomization> MakeInstance()`
- L24 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;` — IDetailCustomization interface
- L26 _public prototype_ `static UControlRigBlueprint* GetBlueprintFromDetailBuilder(IDetailLayoutBuilder& DetailBuilder);`
- L30 _protected member_ `UControlRigBlueprint* BlueprintBeingCustomized;`

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/ControlRigModularRigCommands.h` (Private)


#### class `FControlRigModularRigCommands`  
`class FControlRigModularRigCommands : public TCommands<FControlRigModularRigCommands>`  
_L9-61_
- inherits: `TCommands<FControlRigModularRigCommands>`
- L12 _public function_ `FControlRigModularRigCommands() : TCommands<FControlRigModularRigCommands> ( "ControlRigModularRigModel", NSLOCTEXT("Contexts", "ModularRigModel", "Modular Rig Modules"), NAME_None,`
- L22 _public member_ `TSharedPtr< FUICommandInfo > AddModuleItem;` — Add Module at root
- L25 _public member_ `TSharedPtr< FUICommandInfo > RenameModuleItem;` — Rename Module
- L28 _public member_ `TSharedPtr< FUICommandInfo > DeleteModuleItem;` — Delete Module
- L31 _public member_ `TSharedPtr< FUICommandInfo > DuplicateModuleItem;` — Duplicate Module
- L34 _public member_ `TSharedPtr< FUICommandInfo > MirrorModuleItem;` — Mirror Module
- L37 _public member_ `TSharedPtr< FUICommandInfo > ReresolveModuleItem;` — Reresolve Module
- L40 _public member_ `TSharedPtr< FUICommandInfo > SwapModuleClassItem;` — Swap Module Class
- L43 _public member_ `TSharedPtr< FUICommandInfo > CopyModuleSettings;` — Copy module settings
- L46 _public member_ `TSharedPtr< FUICommandInfo > PasteModuleSettings;` — Paste module settings
- L49 _public member_ `TSharedPtr< FUICommandInfo > ToggleShowSecondaryContectors;` — Toggle visibility of secondary connectors
- L52 _public member_ `TSharedPtr< FUICommandInfo > ToggleShowOptionalContectors;` — Toggle visibility of optional connectors
- L55 _public member_ `TSharedPtr< FUICommandInfo > ToggleShowUnresolvedContectors;` — Toggle visibility of unresolved connectors
- L60 _public prototype_ `virtual void RegisterCommands() override;` — Initialize commands

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/ControlRigModuleDetails.h` (Private)


#### class `FRigModuleInstanceDetails`  
`class FRigModuleInstanceDetails : public IDetailCustomization`  
_L30-179_
- inherits: `IDetailCustomization`
- L32 _private typedef_ `using FControlRigShowSchematicViewportOverride = UE::ControlRigEditor::FControlRigShowSchematicViewportOverride;`
- L37 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;` — IDetailCustomization interface
- L40 _public function_ `static TSharedRef<IDetailCustomization> MakeInstance()` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L45 _public prototype_ `FText GetName() const;`
- L46 _public prototype_ `void SetName(const FText& InValue, ETextCommit::Type InCommitType, const TSharedRef<IPropertyUtilities> PropertyUtilities);`
- L47 _public prototype_ `bool OnVerifyNameChanged(const FText& InText, FText& OutErrorMessage);`
- L49 _public prototype_ `TArray<FRigModuleConnector> GetConnectors() const;`
- L50 _public prototype_ `FRigElementKeyRedirector GetConnections() const;`
- L52 _public prototype_ `void OnConfigValueChanged(const FPropertyChangedEvent& InPropertyChangedEvent);`
- L60 _public prototype_ `void OnWrapperConfigValueChanged(URigVMDetailsViewWrapperObject* InWrapper, const FString& InPropertyPath, FPropertyChangedChainEvent& InEvent);` — Routed from each module's UControlRigWrapperObject. Mirrors the wrapper's UPROPERTY state back into the rig's variables memory, then defers to OnConfigValueChanged for override-path reconstruction + SetConfigValueInModule. The wrapper-driven path is used for BP-independent rigs where variables live in a UPropertyBag, so that downstream customizations (e.g. shape-name combo) discover the UControlRig via GetOuterObjects() instead of seeing a bare FStructOnScope.
- L62 _public prototype_ `bool OnConnectorTargetChanged(TArray<FRigElementKey> InTargets, FRigModuleConnector InConnector);`
- L64 _public prototype_ `FText GetConstructionStartSpawnIndex() const;`
- L65 _public prototype_ `FText GetPostConstructionStartSpawnIndex() const;`
- L118 _public prototype_ `const FPerModuleInfo& FindModule(const FName& InModuleName) const;`
- L119 _public prototype_ `const FPerModuleInfo* FindModuleByPredicate(const TFunction<bool(const FPerModuleInfo&)>& InPredicate) const;`
- L120 _public prototype_ `bool ContainsModuleByPredicate(const TFunction<bool(const FPerModuleInfo&)>& InPredicate) const;`
- L122 _public prototype_ `virtual void RegisterSectionMappings(FPropertyEditorModule& PropertyEditorModule, UClass* InClass);`
- L126 _protected prototype_ `FText GetBindingText(const FProperty* InProperty) const;`
- L127 _protected prototype_ `const FSlateBrush* GetBindingImage(const FProperty* InProperty) const;`
- L128 _protected prototype_ `FLinearColor GetBindingColor(const FProperty* InProperty) const;`
- L129 _protected prototype_ `void FillBindingMenu(FMenuBuilder& MenuBuilder, const FProperty* InProperty) const;`
- L130 _protected prototype_ `bool CanRemoveBinding(FName InPropertyName) const;`
- L131 _protected prototype_ `void HandleRemoveBinding(FName InPropertyName) const;`
- L132 _protected prototype_ `void HandleChangeBinding(const FProperty* InProperty, const FString& InNewVariablePath) const;`
- L133 _protected prototype_ `FReply OnAddTargetToArrayConnector(const FString InConnectorName, const TSharedRef<IPropertyUtilities> PropertyUtilities);`
- L134 _protected prototype_ `FReply OnClearTargetsForArrayConnector(const FString InConnectorName, const TSharedRef<IPropertyUtilities> PropertyUtilities);`
- L136 _protected member_ `TArray<FPerModuleInfo> PerModuleInfos;`
- L141 _protected member_ `TArray<TStrongObjectPtr<UControlRigWrapperObject>> PerModuleWrappers;` — Strong refs that keep the per-module variable wrappers alive while the details panel is open. Each wrapper carries the owning UControlRig via SetSubject(), so property handles backed by it expose the rig via GetOuterObjects() (needed by FControlRigShapeSettingsDetails and similar).
- L148 _protected member_ `bool bDispatchingWrapperEvent = false;` — Re-entrancy guard for OnWrapperConfigValueChanged. In multi-module selection AddObjectPropertyData merges N wrappers behind one IPropertyHandle; an edit on the merged handle dispatches PostEditChangeChainProperty to each wrapper, so the chain event fires N times. The first dispatch already iterates all modules in OnConfigValueChanged, so subsequent dispatches for the same edit are redundant.
- L151 _protected member_ `TMap<FString, TSharedPtr<SButton>> UseSelectedButton;` — Helper buttons.
- L152 _protected member_ `TMap<FString, TSharedPtr<SButton>> SelectElementButton;`
- L153 _protected member_ `TMap<FString, TSharedPtr<SButton>> ResetConnectorButton;`
- L157 _private prototype_ `FReply OnConnectorDragDetected( const FGeometry& MyGeometry, const FPointerEvent& MouseEvent, const FRigElementKey ElementKey);` — Called when a connector was dragged, starts a drag drop op only if ElementKeys is set
- L163 _private prototype_ `FText GetTooltipForConnector(const FRigElementKey& Key);` — Returns the tooltip for a connector element, or empty text if the element is not a connector
- L166 _private prototype_ `FText GetAssetPath() const;` — Returns path name of the rig asset in use, assumes multiple assets if there is no single outer asset
- L169 _private prototype_ `FText GetAssetName() const;` — Returns name of the rig asset in use, assumes multiple assets if there is no single outer asset
- L172 _private prototype_ `void OnBrowseToRigModuleAssetClicked() const;` — Called when the Browse to Rig Module Asset button was clicked
- L175 _private prototype_ `[[nodiscard]] bool GetSingleAsset(const UObject*& OutAssetObject) const;` — Gets a single asset object the asset was generated by, returns false if there is none or multiple
- L178 _private member_ `FControlRigShowSchematicViewportOverride ShowSchematicViewportOverride;` — Overrides the per project per user schematic viewport visibility

#### struct `FRigModuleInstanceDetails::FPerModuleInfo`  
`struct FPerModuleInfo`  
_L67-116_
- L69 _public function_ `FPerModuleInfo() : ModuleName(NAME_None) , Module()`
- L74 _public function_ `bool IsValid() const`
- L75 _public function_ `operator bool() const`
- L77 _public function_ `const FName& GetModuleName() const`
- L82 _public function_ `UModularRig* GetModularRig() const`
- L87 _public function_ `FControlRigAssetInterfacePtr GetAsset() const`
- L100 _public function_ `FRigModuleInstance* GetModule() const`
- L105 _public function_ `const FRigModuleReference* GetReference() const`
- L114 _public member_ `FName ModuleName;`
- L115 _public member_ `FModuleInstanceHandle Module;`

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/ControlRigOverrideDetails.h` (Private)


#### class `FControlRigOverrideDetails`  
`class FControlRigOverrideDetails : public IPropertyTypeCustomization`  
_L14-26_
- inherits: `IPropertyTypeCustomization`
- L18 _public function_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance()`
- L24 _public prototype_ `virtual void CustomizeHeader(TSharedRef<class IPropertyHandle> InStructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;` — IPropertyTypeCustomization interface
- L25 _public prototype_ `virtual void CustomizeChildren(TSharedRef<class IPropertyHandle> InStructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`

#### class `FControlRigOverrideDetailsBuilder`  
`class FControlRigOverrideDetailsBuilder : public IDetailCustomNodeBuilder , public TSharedFromThis<FControlRigOverrideDetailsBuilder>`  
_L28-49_
- inherits: `IDetailCustomNodeBuilder,TSharedFromThis<FControlRigOverrideDetailsBuilder>`
- L33 _public prototype_ `FControlRigOverrideDetailsBuilder(UControlRigOverrideAsset* InOverrideAsset, const FName& InSubjectKey);`
- L36 _public function_ `virtual void SetOnRebuildChildren( FSimpleDelegate InOnRebuildChildren ) override` — IDetailCustomNodeBuilder interface
- L37 _public function_ `virtual bool RequiresTick() const override`
- L38 _public prototype_ `virtual void Tick( float DeltaTime ) override;`
- L39 _public prototype_ `virtual void GenerateHeaderRowContent( FDetailWidgetRow& NodeRow ) override;`
- L40 _public prototype_ `virtual void GenerateChildContent( IDetailChildrenBuilder& ChildrenBuilder ) override;`
- L41 _public function_ `virtual FName GetName() const override`
- L42 _public function_ `virtual bool InitiallyCollapsed() const override`
- L45 _private member_ `TWeakObjectPtr<UControlRigOverrideAsset> WeakOverrideAsset;`
- L46 _private member_ `FName SubjectKey;`
- L47 _private member_ `FSimpleDelegate OnRebuildChildren;`
- L48 _private member_ `TOptional<uint32> LastHash;`

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/ControlRigShapeNameList.h` (Private)


#### struct `UE::ControlRigEditor::FControlRigShapeNameList`  
`struct FControlRigShapeNameList : public TSharedFromThis<FControlRigShapeNameList>`  
_L20-33_
- inherits: `TSharedFromThis<FControlRigShapeNameList>`
- desc: Helper to create a ShapeLibraryListWidget for a ControlRig details
- L22 _public prototype_ `void GenerateShapeLibraryList(const UControlRig* ControlRig);`
- L23 _public prototype_ `TSharedRef<SWidget> MakeShapeNameListItemWidget(TSharedPtr<FRigVMStringWithTag> InItem);`
- L25 _public prototype_ `void CreateShapeLibraryListWidget(IDetailChildrenBuilder& InStructBuilder, TSharedPtr<IPropertyHandle>& ShapeSettingsNameProperty);`
- L26 _public prototype_ `void OnShapeNameListChanged(TSharedPtr<FRigVMStringWithTag> NewSelection, ESelectInfo::Type SelectInfo);`
- L27 _public prototype_ `void OnShapeNameListComboBox();`
- L28 _public prototype_ `FText GetShapeNameListText() const;`
- L30 _public member_ `TSharedPtr<IPropertyHandle> ShapeSettingsNameProperty;`
- L31 _public member_ `TArray<TSharedPtr<FRigVMStringWithTag>> ShapeNameList;`
- L32 _public member_ `TSharedPtr<SRigVMGraphPinNameListValueWidget> ShapeNameListWidget;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace ControlRigEditor` (scope `UE`)

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/ControlRigShapeSettingsDetails.h` (Private)


#### class `UE::ControlRigEditor::FControlRigShapeSettingsDetails`  
`class FControlRigShapeSettingsDetails : public IPropertyTypeCustomization`  
_L20-38_
- inherits: `IPropertyTypeCustomization`
- L23 _public function_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance()`
- L28 _public prototype_ `FControlRigShapeSettingsDetails();`
- L31 _public prototype_ `virtual void CustomizeHeader(TSharedRef<class IPropertyHandle> InStructPropertyHandle, class FDetailWidgetRow& InHeaderRow, IPropertyTypeCustomizationUtils& InStructCustomizationUtils) override;` — IPropertyTypeCustomization interface
- L32 _public prototype_ `virtual void CustomizeChildren(TSharedRef<class IPropertyHandle> InStructPropertyHandle, class IDetailChildrenBuilder& InStructBuilder, IPropertyTypeCustomizationUtils& InStructCustomizationUtils) override;`
- L35 _protected member_ `TSharedPtr<FControlRigShapeNameList> ControlRigShapeNameList;`
- L37 _protected prototype_ `static UControlRig* GetControlRig(UControlRigWrapperObject* ControlRigWrapperObject);`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace ControlRigEditor` (scope `UE`)

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/EditMode/Constrain/ConstrainToolsManager.h` (Private)


#### class `UE::ControlRigEditor::FConstrainToolsManager`  
`class FConstrainToolsManager : public FNoncopyable`  
_L30-74_
- inherits: `FNoncopyable`
- desc: Manages UI that is used for constraining, namely: - SControlRigSnapper - SRigSpacePickerWidget - SConstraintsEditionWidget This class responsibility is spawning & managing a window with tab-like buttons to switch between these widgets.
- L34 _public prototype_ `explicit FConstrainToolsManager( const TSharedRef<FTabManager>& InToolkitTabManager, const TSharedRef<FWorkspaceItem>& InWorkspaceMenuGroup, const TSharedRef<FUICommandList>& InToolkitCommandList, FControlRigEditMode& InOwningEditMode UE_LIFETIMEBOUND, const TSharedRef<FRigSelectionViewModel>& InSelectionViewModel );`
- L41 _public prototype_ `~FConstrainToolsManager();`
- L43 _public prototype_ `void ToggleVisibility() const;`
- L44 _public prototype_ `void ShowWidget() const;`
- L45 _public prototype_ `void HideWidget() const;`
- L46 _public prototype_ `bool IsShowingWidget() const;`
- L51 _private member_ `const TSharedRef<FTabManager> TabManager;` — Used to show / hide the tab containing our widgets.
- L53 _private member_ `const TWeakPtr<FUICommandList> WeakCommandList;` — The command list that we are bound to for switching between inline tabs.
- L56 _private member_ `FControlRigEditMode& OwningEditMode;` — Needed to construct widget hierarchy.
- L58 _private member_ `const TSharedRef<FRigSelectionViewModel> SelectionViewModel;` — Handles selection changing. Needed to construct widget hierarchy.
- L61 _private member_ `TWeakPtr<SDockTab> SpawnedTab;` — The tab we spawned. Used to detect whether the tab is currently being shown.
- L63 _private member_ `TWeakPtr<SConstrainToolsRoot> ConstrainWindowContent;` — The widget that contains the tabs. Only valid when SpawnedTab is valid. Weak as we don't keep a strong reference to the SDockTab either.
- L66 _private prototype_ `void RegisterTabSpawner(const TSharedRef<FTabManager>& InTabManager, const TSharedRef<FWorkspaceItem>& InWorkspaceMenuGroup);` — Tab spawning
- L67 _private prototype_ `void UnregisterTabSpawner(const TSharedRef<FTabManager>& InTabManager);`
- L68 _private prototype_ `TSharedRef<SDockTab> SpawnSnapperTab(const FSpawnTabArgs& Args);`
- L71 _private prototype_ `void BindCommands();` — Commands
- L72 _private prototype_ `void UnbindCommands();`
- L73 _private prototype_ `void HandleOpenTabCommand(EControlRigConstrainTab InTab);`

#### Free symbols / members of external scopes

- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace ControlRigEditor` (scope `UE`)

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/EditMode/Constrain/SConstrainToolsRoot.h` (Private)


#### class `UE::ControlRigEditor::SConstrainToolsRoot`  
`class SConstrainToolsRoot : public SCompoundWidget`  
_L27-60_
- inherits: `SCompoundWidget`
- desc: Coordinator widget that contains - SControlRigSnapper - SRigSpacePickerWidget - SConstraintsEditionWidget and ranges them under a tab-like structure.
- L31 _public function_ `SLATE_BEGIN_ARGS(SConstrainToolsRoot)`
- L33 _public prototype_ `SLATE_EVENT(FOnTabSelected, OnTabSelected) SLATE_END_ARGS() void Construct(const FArguments& InArgs, FControlRigEditMode& InOwningEditMode, const TSharedRef<FRigSelectionViewModel>& InSelectionViewModel);` — Invoked when one of the named tabs is selected.
- L39 _public prototype_ `void OpenTab(EControlRigConstrainTab InTab) const;` — Opens the specified tab.
- L44 _private member_ `TSharedPtr<SInlineTabPanel> InlineTabs;` — Manages the tabs.
- L47 _private member_ `TSharedPtr<SConstraintsEditionWidget_ConstrainPanel> ConstrainsEditionWidget;` — The widget for editing constraints.
- L50 _private member_ `FOnTabSelected OnTabSelectedDelegate;` — Invoked when one of the named tabs is selected.
- L52 _private prototype_ `TSharedRef<SWidget> CreateSpacesContent(FControlRigEditMode& InOwningEditMode, const TSharedRef<FRigSelectionViewModel>& InSelectionViewModel);`
- L53 _private prototype_ `TSharedRef<SWidget> CreateConstraintsContent(FControlRigEditMode& InOwningMode, const TSharedRef<FRigSelectionViewModel>& InSelectionViewModel);`
- L54 _private prototype_ `TSharedRef<SWidget> CreateSnapperContent();`
- L57 _private prototype_ `void OnTabSelected_ConstraintsEditionWidget() const;` — Refreshes the list when we switch to the tab.
- L59 _private function_ `void BroadcastOnTabSelected(EControlRigConstrainTab ControlRigConstrainTab) const` — Invoked when one of the named tabs is selected.

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace ControlRigEditor` (scope `UE`)
- L18 _delegate_ `DECLARE_DELEGATE_OneParam(FOnTabSelected, EControlRigConstrainTab);`
- L18 _prototype_ `DECLARE_DELEGATE_OneParam(FOnTabSelected, EControlRigConstrainTab);` (scope `UE::ControlRigEditor`)

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/EditMode/Constrain/SConstraintsEditionWidget_ConstrainPanel.h` (Private)


#### class `UE::ControlRigEditor::SConstraintsEditionWidget_ConstrainPanel`  
`class SConstraintsEditionWidget_ConstrainPanel : public SCompoundWidget`  
_L22-64_
- inherits: `SCompoundWidget`
- desc: Constraints edition widget that is shown in the constraints window. Places a SConstraintsEditionWidget in an SExpandableArea. The SExpandableArea's header contains a combo button and + button in the header.
- L26 _public function_ `SLATE_BEGIN_ARGS(SConstraintsEditionWidget_ConstrainPanel) : _InitiallyCollapsed(true)`
- L30 _public prototype_ `SLATE_ARGUMENT(bool, InitiallyCollapsed) SLATE_END_ARGS() void Construct(const FArguments& InArgs, FControlRigEditMode& InEditMode, const TSharedRef<FRigSelectionViewModel>& InSelectionViewModel);` — Whether or not the area is initially collapsed
- L36 _public function_ `void RefreshConstraintList() const`
- L41 _private member_ `FControlRigEditMode* OwningEditMode = nullptr;` — Control rig edit mode we were constructed with
- L44 _private member_ `TSharedPtr<FRigSelectionViewModel> SelectionViewModel;` — View model for when control rig selection changes.
- L47 _private member_ `TSharedPtr<SConstraintsEditionWidget> ConstraintsEditionWidget;` — The constraints edition widget we wrap.
- L50 _private prototype_ `TSharedRef<SWidget> CreateSelectionComboButton();` — Header area (similar to expandable area border we used to have)
- L51 _private prototype_ `TSharedRef<SWidget> CreateAddConstraintButton();`
- L54 _private prototype_ `void OnSelectShowConstraints(int32 Index);`
- L56 _private prototype_ `FReply HandleAddConstraintClicked();` — Spawns the constraints menu when the plus button is pressed.
- L58 _private prototype_ `FText GetShowConstraintsName() const;`
- L59 _private prototype_ `FText GetShowConstraintsTooltip() const;`
- L62 _private prototype_ `void OnControlSelected(UControlRig* Subject, FRigControlElement* RigControlElement, bool bIsSelected) const;` — Refresh the constrain widget when the selected control rig changes.

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace ControlRigEditor` (scope `UE`)

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/EditMode/ControlRigBaseDockableView.h` (Private)


#### class `FControlRigBaseDockableView`  
`class FControlRigBaseDockableView`  
_L17-39_
- L20 _public prototype_ `FControlRigBaseDockableView();`
- L21 _public prototype_ `virtual ~FControlRigBaseDockableView();`
- L22 _public prototype_ `TArray<UControlRig*> GetControlRigs() const;`
- L24 _public prototype_ `virtual TSharedRef<FControlRigBaseDockableView> AsSharedWidget() = 0;`
- L25 _public prototype_ `virtual void SetEditMode(FControlRigEditMode& InEditMode);`
- L26 _public prototype_ `FControlRigEditMode* GetEditMode() const;`
- L29 _protected prototype_ `virtual void HandleControlSelected(UControlRig* Subject, FRigControlElement* InControl, bool bSelected);`
- L30 _protected prototype_ `virtual void HandleControlAdded(UControlRig* ControlRig, bool bIsAdded);`
- L31 _protected prototype_ `virtual void HandleRigVisibilityChanged(TArray<UControlRig*> InControlRigs);`
- L33 _protected prototype_ `void HandlElementSelected(UControlRig* Subject, const FRigElementKey& Key, bool bSelected);`
- L35 _protected prototype_ `ISequencer* GetSequencer() const;`
- L37 _protected member_ `FEditorModeTools* ModeTools = nullptr;`

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/EditMode/ControlRigEditModeCommands.h` (Private)


#### class `FControlRigEditModeCommands`  
`class FControlRigEditModeCommands : public TCommands<FControlRigEditModeCommands>`  
_L9-156_
- inherits: `TCommands<FControlRigEditModeCommands>`
- L13 _public function_ `FControlRigEditModeCommands() : TCommands<FControlRigEditModeCommands> ( "ControlRigEditMode", NSLOCTEXT("Contexts", "RigAnimation", "Rig Animation"), NAME_None,`
- L24 _public member_ `TSharedPtr< FUICommandInfo > ToggleManipulators;` — Toggles hiding all manipulators on active control rig in the viewport
- L27 _public member_ `TSharedPtr< FUICommandInfo > ToggleModuleManipulators;` — Toggles hiding all manipulators belonging to the selected module on active control rig in the viewport
- L30 _public member_ `TSharedPtr< FUICommandInfo > ToggleAllManipulators;` — Toggles hiding all manipulators on all control rigs in the viewport
- L33 _public member_ `TSharedPtr< FUICommandInfo > ToggleControlsAsOverlay;` — Toggles show controls as an overlay in the viewport
- L36 _public member_ `TSharedPtr< FUICommandInfo > InvertTransformsAndChannels;` — Invert Transforms and channels to Rest Pose
- L39 _public member_ `TSharedPtr< FUICommandInfo > InvertAllTransformsAndChannels;` — Invert All Transforms and channels  to Rest Pose
- L42 _public member_ `TSharedPtr< FUICommandInfo > InvertTransforms;` — Invert Transforms to Rest Pose
- L45 _public member_ `TSharedPtr< FUICommandInfo > InvertAllTransforms;` — Invert All Transforms to Rest Pose
- L48 _public member_ `TSharedPtr< FUICommandInfo > ZeroTransforms;` — Set Transforms to Zero
- L51 _public member_ `TSharedPtr< FUICommandInfo > ZeroAllTransforms;` — Set All Transforms to Zero
- L54 _public member_ `TSharedPtr< FUICommandInfo > ClearSelection;` — Clear Selection
- L57 _public member_ `TSharedPtr<FUICommandInfo> FrameSelection;` — Frame selected elements
- L60 _public member_ `TSharedPtr< FUICommandInfo > ToggleControlShapeTransformEdit;` — Toggle Shape Transform Edit
- L63 _public member_ `TSharedPtr< FUICommandInfo > SetAnimLayerPassthroughKey;` — Sets Passthrough Key on selected anim layers
- L66 _public member_ `TSharedPtr< FUICommandInfo > SelectAnimLayerWeightChannel;` — Select weight channel on selected anim layers
- L69 _public member_ `TSharedPtr< FUICommandInfo > SelectMirroredControls;` — Select mirrored Controls on current selection
- L72 _public member_ `TSharedPtr< FUICommandInfo > AddMirroredControlsToSelection;` — Select mirrored Controls on current selection, keeping current selection
- L75 _public member_ `TSharedPtr< FUICommandInfo > MirrorSelectedControls;` — Put selected Controls to mirrored Pose
- L78 _public member_ `TSharedPtr< FUICommandInfo > MirrorUnselectedControls;` — Put unselected Controls to mirrored selected Controls
- L81 _public member_ `TSharedPtr< FUICommandInfo > SelectAllControls;` — Select all Controls
- L84 _public member_ `TSharedPtr< FUICommandInfo > SavePose;` — Save a pose of selected Controls
- L87 _public member_ `TSharedPtr< FUICommandInfo > SelectPose;` — Select Controls in saved Pose
- L90 _public member_ `TSharedPtr< FUICommandInfo > PastePose;` — Paste saved Pose
- L93 _public member_ `TSharedPtr< FUICommandInfo > SelectMirrorPose;` — Select Controls in saved Pose
- L96 _public member_ `TSharedPtr< FUICommandInfo > PasteMirrorPose;` — Paste saved mirror Pose
- L99 _public member_ `TSharedPtr< FUICommandInfo> TogglePivotMode;` — Toggle Pivot Mode
- L102 _public member_ `TSharedPtr< FUICommandInfo> ToggleMotionTrails;` — Toggle Motion Trail Mode
- L105 _public member_ `TSharedPtr< FUICommandInfo > OpenSpacePickerWidget;` — Opens up the space picker widget
- L108 _public member_ `TSharedPtr< FUICommandInfo > SummonTweenWidget;` — Opens the tween slider widget and positions it at the mouse.
- L111 _public member_ `TSharedPtr< FUICommandInfo > ToggleTweenWidget;` — Toggles the visibility of the tween widget.
- L114 _public member_ `TSharedPtr< FUICommandInfo > SummonSelectionSetsWidget;` — Opens the selection sets slider widget and positions it at the mouse.
- L117 _public member_ `TSharedPtr< FUICommandInfo > ToggleSelectionSetsWidget;` — Toggles the visibility of the selection sets widget.
- L120 _public member_ `TSharedPtr< FUICommandInfo > ToggleAnimLayersTab;` — Toggles the visibility of the anim layers window.
- L123 _public member_ `TSharedPtr< FUICommandInfo > TogglePoseLibraryTab;` — Toggles the visibility of the anim pose library window.
- L126 _public member_ `TSharedPtr< FUICommandInfo > ToggleConstrainTab;` — Toggles the visibility of the constrain window.
- L129 _public member_ `TSharedPtr< FUICommandInfo > OpenSpacesTab;` — Opens the spaces tab in the constrain window.
- L132 _public member_ `TSharedPtr< FUICommandInfo > OpenConstraintsTab;` — Opens the constraints tab in the constrain window.
- L135 _public member_ `TSharedPtr< FUICommandInfo > OpenSnapperTab;` — Opens the snapper tab in the constrain window.
- L138 _public member_ `TSharedPtr< FUICommandInfo > CycleDirectManipulationTargetNext;` — Cycle to the next direct manipulation target on the selected node
- L141 _public member_ `TSharedPtr< FUICommandInfo > CycleDirectManipulationTargetPrev;` — Cycle to the previous direct manipulation target on the selected node
- L144 _public member_ `TSharedPtr< FUICommandInfo > IsolateLinkedAnimTracks;` — Isolate linked anim tracks for every binding in the current Sequencer
- L147 _public member_ `TSharedPtr< FUICommandInfo > UnIsolateLinkedAnimTracks;` — Un-isolate linked anim tracks for every binding in the current Sequencer
- L150 _public member_ `TSharedPtr< FUICommandInfo > ClickAndDrag;` — Binding used to validate the click-and-drag pre-click functionality.
- L155 _public prototype_ `virtual void RegisterCommands() override;` — Initialize commands

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/EditMode/ControlRigEditModeSettings.h` (Private)


#### enum `EClickAndDragBehavior`  
`enum class EClickAndDragBehavior : uint8`  
_L15-23_
- reflection: `UENUM(MinimalAPI, meta=(Experimental))`
- desc: Specifies the selection policy applied when using click-and-drag interactions.
- L18 _public enumerator_ `Disabled = 0` — click-and-drag interaction is disabled.
- L20 _public enumerator_ `TransientSelection` — temporarily selects the hovered element during the interaction (if nothing is already selected).
- L22 _public enumerator_ `PersistentSelection` — selects the hovered element and preserves the selection after the interaction ends.

#### class `UControlRigEditModeSettings`  
`class UControlRigEditModeSettings : public UDeveloperSettings`  
_L27-138_
- reflection: `UCLASS(config=EditorPerProjectUserSettings, MinimalAPI, meta=(DisplayName="Control Rig Edit Mode"))`
- inherits: `UDeveloperSettings`
- desc: Settings object used to show useful information in the details panel
- L31 _private function_ `UControlRigEditModeSettings() : bDisplayHierarchy(false) , bDisplayNulls(false) , bDisplaySockets(false) , bHideControlShapes(false) , bShowAllProxyControls(false) , bShowControlsAsOverlay(false) , bDisplayAxesOnSelection(false) , AxisScale(10.f) , bCoordSystemPerWidgetMode(true) , bOnlySelectRigControls(false) , bLocalTransformsInEachLocalSpace(true)`
- L48 _private prototype_ `virtual void PreEditChange(FProperty* PropertyAboutToChange) override;` — UObject interface
- L49 _private prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;`
- L51 _private prototype_ `virtual void PostEditUndo() override;`
- L55 _public function_ `static UControlRigEditModeSettings* Get()`
- L59 _public member_ `bool bDisplayHierarchy;` — `UPROPERTY(config, EditAnywhere, Category = "Animation Settings")` — Whether to show all bones in the hierarchy
- L63 _public member_ `bool bDisplayNulls;` — `UPROPERTY(config, EditAnywhere, Category = "Animation Settings")` — Whether to show all nulls in the hierarchy
- L67 _public member_ `bool bDisplaySockets;` — `UPROPERTY(config, EditAnywhere, Category = "Animation Settings")` — Should we show sockets in the viewport
- L71 _public member_ `bool bHideControlShapes;` — `UPROPERTY(config, EditAnywhere, Category = "Animation Settings")` — Should we always hide control shapes in viewport
- L75 _public member_ `bool bShowAllProxyControls;` — `UPROPERTY(config, EditAnywhere, Category = "Animation Settings", meta = (EditCondition = "!bHideControlShapes"))` — Should we always hide control shapes in viewport
- L79 _public member_ `bool bShowControlsAsOverlay;` — `UPROPERTY(config, EditAnywhere, Category = "Animation Settings", meta = (EditCondition = "!bHideControlShapes"))` — Determins if controls should be rendered on top of other controls
- L83 _public member_ `FLinearColor DrivenControlColor;` — `UPROPERTY(config, EditAnywhere, Category = "Animation Settings", meta = (EditCondition = "!bHideControlShapes"))` — Indicates a control being driven by a proxy control
- L87 _public member_ `bool bDisplayAxesOnSelection;` — `UPROPERTY(config, EditAnywhere, Category = "Animation Settings")` — Should we show axes for the selected elements
- L91 _public member_ `float AxisScale;` — `UPROPERTY(config, EditAnywhere, Category = "Animation Settings")` — The scale for axes to draw on the selection
- L95 _public member_ `bool bCoordSystemPerWidgetMode;` — `UPROPERTY(config, EditAnywhere, Category = "Animation Settings")` — If true we restore the coordinate space when changing Widget Modes in the Viewport
- L99 _public member_ `bool bOnlySelectRigControls;` — `UPROPERTY(config, EditAnywhere, Category = "Animation Settings")` — If true we can only select Rig Controls in the scene not other Actors.
- L103 _public member_ `bool bLocalTransformsInEachLocalSpace;` — `UPROPERTY(config, EditAnywhere, Category = "Animation Settings")` — If true when we transform multiple selected objects in the viewport they each transforms along their own local transform space
- L107 _public member_ `FControlRigUIRestoreStates LastUIStates;` — `UPROPERTY(config)` — Data to restore the UI state control rig had last time it was open.
- L111 _public member_ `FLinearColor TweenOutOfFocusTint = FLinearColor(1.f, 1.f, 1.f, .35f);` — `UPROPERTY(config, EditAnywhere, Category = "Animation Settings|Tween")` — The tint to apply when the tween overlay is out of focus.
- L118 _public member_ `bool bIndirectSliderMovementShouldSnapSliderToMouse = false;` — `UPROPERTY(config, EditAnywhere, Category = "Animation Settings|Tween")` — If enabled, the DragAnimSliderTool hotkey should position the widget at the mouse cursor if the widget was visible when you pressed it. If disabled, the DragAnimSliderTool hotkey will leave the widget where you placed it if the widget was visible when you pressed it.
- L124 _public member_ `bool bSupportUtilityActions = true;` — `UPROPERTY(config, EditAnywhere, Category = "Animation Settings|Workflow")` — Enables the tab menu customization so that users can register contextual utility actions.
- L130 _public member_ `EClickAndDragBehavior ClickAndDragBehavior = EClickAndDragBehavior::Disabled;` — `UPROPERTY(config, EditAnywhere, Category = "Animation Settings|Interaction", meta=(Experimental))` — Enables or disables click-and-drag selection and defines how it behaves.
- L134 _public member_ `FLinearColor HoveredColor = FLinearColor(0.5f, 0.5f, 0.5f, 0.25f);` — `UPROPERTY(config, EditAnywhere, Category = "Animation Settings", meta = (EditCondition = "!bHideControlShapes"))` — Hovered color used when hovering a control shape.
- L136 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnUpdateSettings, const UControlRigEditModeSettings*);`
- L137 _public member_ `static FOnUpdateSettings OnSettingsChange;`

#### Free symbols / members of external scopes

- L11 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FGizmoScaleSet, float );`
- L11 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FGizmoScaleSet, float );`
- L136 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnUpdateSettings, const UControlRigEditModeSettings*);`

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/EditMode/ControlRigEditModeToolkit.h` (Private)


#### class `FControlRigEditModeToolkit`  
`class FControlRigEditModeToolkit : public FModeToolkit`  
_L33-131_
- inherits: `FModeToolkit`
- L35 _private typedef_ `using Super = FModeToolkit;`
- L39 _public prototype_ `explicit FControlRigEditModeToolkit(FControlRigEditMode& InEditMode);`
- L43 _public function_ `virtual FName GetToolkitFName() const override` — IToolkit interface
- L44 _public function_ `virtual FText GetBaseToolkitName() const override`
- L45 _public function_ `virtual class FEdMode* GetEditorMode() const override`
- L46 _public function_ `virtual TSharedPtr<class SWidget> GetInlineContent() const override`
- L47 _public function_ `virtual bool ProcessCommandBindings(const FKeyEvent& InKeyEvent) const override`
- L51 _public prototype_ `virtual void Init(const TSharedPtr<IToolkitHost>& InitToolkitHost) override;`
- L54 _public prototype_ `virtual void GetToolPaletteNames(TArray<FName>& InPaletteName) const override;` — Mode Toolbar Palettes
- L55 _public prototype_ `virtual FText GetToolPaletteDisplayName(FName PaletteName) const override;`
- L56 _public prototype_ `virtual void BuildToolPalette(FName PaletteName, class FToolBarBuilder& ToolbarBuilder) override;`
- L59 _public prototype_ `virtual FText GetActiveToolDisplayName() const override;` — Modes Panel Header Information
- L60 _public prototype_ `virtual FText GetActiveToolMessage() const override;`
- L63 _public prototype_ `void TryToggleToolkitUI(const FName InName);` — If the named UI is shown, hide it. If it's hidden, show it.
- L65 _public prototype_ `void TryInvokeToolkitUI(const FName InName);` — Tries to spawn the named UI. If already spawned, and it's a tab, highlight it (little flash).
- L67 _public prototype_ `void TryCloseToolkitUI(const FName InName) const;` — Tries to hide the named UI.
- L69 _public prototype_ `bool IsToolkitUIActive(const FName InName) const;` — @return Whether the named UI is open
- L72 _public prototype_ `void OnControlsChanged(TConstArrayView<TWeakObjectPtr<UControlRig>> InControlRigs) const;` — Called when the global array of control rigs changed the user is working on has changed.
- L75 _public function_ `UE::ControlRigEditor::FConstrainToolsManager* GetConstrainToolsManager() const` — @return The constraining UI tools, which is a window containing tabs for spaces, constraining, and snapping.
- L79 _public member_ `static const FName PoseTabName;`
- L80 _public member_ `static const FName MotionTrailTabName;`
- L81 _public member_ `static const FName AnimLayerTabName;`
- L82 _public member_ `static const FName TweenOverlayName;`
- L83 _public member_ `static const FName ConstrainingTabName;`
- L85 _public member_ `static const FName SelectionSetsTabName;`
- L87 _public member_ `static const FName SelectionSetsOverlayName;`
- L89 _public member_ `static const FName SnapperTabName;`
- L90 _public member_ `static const FName DetailsTabName;`
- L91 _public member_ `static const FName OutlinerTabName;`
- L93 _public member_ `static TSharedPtr<UE::ControlRigEditor::SAnimDetailsView> Details;`
- L94 _public member_ `static TSharedPtr<SControlRigOutliner> Outliner;`
- L99 _protected prototype_ `virtual void RequestModeUITabs() override;` — FModeToolkit Interface
- L100 _protected prototype_ `virtual void InvokeUI() override;`
- L101 _protected prototype_ `virtual void ShutdownUI() override;`
- L104 _protected prototype_ `void UnregisterAndRemoveFloatingTabs();` — Removes all UI, unregisters tab spawners, and saves the state so it can be restored next time.
- L106 _protected prototype_ `void SaveLayoutState() const;` — Saves the layout state into config so it can be restored next time the user restarts the editor.
- L111 _private member_ `FControlRigEditMode& EditMode;` — The edit mode we are bound to
- L114 _private member_ `const TSharedRef<UE::ControlRigEditor::FRigSelectionViewModel> SelectionViewModel;` — View model for the controls rigs that the user is working on. Used by UI.
- L117 _private member_ `TUniquePtr<UE::ControlRigEditor::FTweenOverlayManager> TweenOverlayManager;` — Manages the tween viewport UI overlay.
- L119 _private member_ `TUniquePtr<UE::ControlRigEditor::FConstrainToolsManager> ConstrainToolsManager;` — Manages the constraining UI tools, which is a window containing tabs for spaces, constraining, and snapping.
- L121 _private member_ `TUniquePtr<UE::AIE::FSelectionSetsOverlayManager> SelectionSetsOverlayManager;`
- L125 _private member_ `TSharedPtr<SControlRigEditModeTools> ModeTools;` — The tools widget
- L128 _private prototype_ `void BuildToolBar(FToolBarBuilder& ToolBarBuilder);` — Adds the toolbar items to the toolbar builder.
- L130 _private prototype_ `void BindCommands();`

#### Free symbols / members of external scopes

- L22 _macro_ `#define SELECTION_SETS_AS_TAB 1`
- L27 _namespace_ `namespace UE`
- L27 _namespace_ `namespace ControlRigEditor` (scope `UE`)

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/EditMode/ControlRigUtilityActions.h` (Private)


#### struct `UE::ControlRigBlutility::FControlRigUtilityActions`  
`struct FControlRigUtilityActions`  
_L22-31_
- desc: FControlRigEditorUtilityActions enables the storage and application of utility functions for control rigs.
- L25 _public prototype_ `static FControlRigUtilityActions GetControlRigUtilityActions(const UWorld* InWorld, const TArrayView<TWeakObjectPtr<UControlRig>>& InRigs);` — Returns the actions/functions and rigs to which they can be applied.
- L28 _public member_ `TArray<UObject*> SupportedRigs;` — Supported control rig objects
- L30 _public member_ `TMap<TSharedRef<FAssetActionUtilityPrototype>, TSet<int32>> UtilityAndRigIndices;` — actions and rig indices (in SupportedRigs) that can be applied

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace ControlRigBlutility` (scope `UE`)
- L19 _prototype_ `bool SupportUtilityActions();` (scope `UE::ControlRigBlutility`) — Returns true if control rig utility actions are supported.

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/EditMode/ControlShapeActorHelper.h` (Private)


#### struct `ControlRigEditMode::Shapes::FShapeUpdateParams`  
`struct FShapeUpdateParams`  
_L31-50_
- desc: Parameters used to update shape actors (transform, visibility, etc.)
- L33 _public prototype_ `FShapeUpdateParams( const UControlRig* InControlRig, const FTransform& InComponentTransform, const bool InSkeletalMeshVisible, const bool IsInLevelEditor, const bool bInHideControlShapes);`
- L40 _public member_ `const UControlRig* ControlRig = nullptr;`
- L41 _public member_ `const URigHierarchy* Hierarchy = nullptr;`
- L42 _public member_ `const UControlRigEditModeSettings* Settings = nullptr;`
- L43 _public member_ `const FTransform& ComponentTransform = FTransform::Identity;`
- L44 _public member_ `const bool bIsSkeletalMeshVisible = false;`
- L45 _public member_ `const bool bIsInLevelEditor = false;`
- L46 _public member_ `bool bControlsHiddenInViewport = false;`
- L47 _public member_ `bool bHideControlShapes = false;`
- L48 _public member_ `bool bIsGameView = false;`
- L49 _public prototype_ `bool IsValid() const;`

#### Free symbols / members of external scopes

- L17 _namespace_ `namespace ControlRigEditMode`
- L17 _namespace_ `namespace Shapes` (scope `ControlRigEditMode`)
- L19 _prototype_ `bool IsSupportedControlType(const ERigControlType& ControlType);` (scope `ControlRigEditMode::Shapes`)
- L22 _prototype_ `bool IsModeSupported(const ERigControlType& InControlType, const UE::Widget::EWidgetMode& InMode);` (scope `ControlRigEditMode::Shapes`) — Returns true if the control type supports being modified using this widget mode
- L25 _prototype_ `void GetControlsEligibleForShapes(const UControlRig* InControlRig, TArray<FRigControlElement*>& OutControls);` (scope `ControlRigEditMode::Shapes`) — Returns the list of controls for which a shape is expected
- L28 _prototype_ `void DestroyShapesActorsFromWorld(const TArray<TObjectPtr<AControlRigShapeActor>>& InShapeActorsToDestroy);` (scope `ControlRigEditMode::Shapes`) — Destroys shape actors and removes them from their UWorld
- L53 _prototype_ `void UpdateControlShape(AControlRigShapeActor* InShapeActor, FRigControlElement* InControlElement, const FShapeUpdateParams& InUpdateParams);` (scope `ControlRigEditMode::Shapes`) — Updates shape actors transform, visibility, etc.
- L57 _prototype_ `void ClearOutHidden(UControlRig* InControlRig);` (scope `ControlRigEditMode::Shapes`) — handle per control visibility by keeping list of hidden controls. We won't create these when requested clear out the hidden ones on this control rig or all if InControlRig is null
- L59 _prototype_ `void ShowControlRigControls(UControlRig* InControlRig, const TSet<FString>& Names, bool bVal);` (scope `ControlRigEditMode::Shapes`) — user is responsible to make sure we recreate them at some other point after the map is set up

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/EditMode/Models/RigSelectionViewModel.h` (Private)


#### class `UE::ControlRigEditor::FRigSelectionViewModel`  
`class FRigSelectionViewModel : public FNoncopyable`  
_L17-49_
- inherits: `FNoncopyable`
- desc: Responsible for invoking an event when control rig selection changes. The intention is for this to be a view model for UI.
- L21 _public prototype_ `~FRigSelectionViewModel();`
- L24 _public prototype_ `void SetControls(TConstArrayView<TWeakObjectPtr<UControlRig>> InControlRigs);` — Called when the global array of control rigs that the user is working on changes.
- L27 _public function_ `TConstArrayView<TWeakObjectPtr<UControlRig>> GetControlRigs() const` — The control rigs that the user is working on.
- L30 _public function_ `FOnControlSelected& OnControlSelected()` — Invoked when a control rig is selected.
- L32 _public function_ `FOnControlsChanged& OnControlsChanged()` — Invoked when the controls rigs change.
- L37 _private member_ `TArray<TWeakObjectPtr<UControlRig>> RuntimeRigs;` — The control rigs that the user is working on.
- L40 _private member_ `FOnControlSelected OnControlSelectedDelegate;` — Invoked when a control rig is selected.
- L43 _private member_ `FOnControlsChanged OnControlsChangedDelegate;` — Invoked when the controls rigs change.
- L46 _private prototype_ `void CleanupSubscriptions();` — Unbinds all subscriptions.
- L48 _private prototype_ `void BroadcastOnRigElementSelected(UControlRig* InSubject, FRigControlElement* InElement, bool bIsSelected);`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace ControlRigEditor` (scope `UE`)
- L10 _delegate_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnControlSelected, UControlRig* , FRigControlElement* , bool );`
- L10 _prototype_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnControlSelected, UControlRig* , FRigControlElement* , bool );` (scope `UE::ControlRigEditor`)
- L11 _typedef_ `using FOnControlsChanged = FSimpleMulticastDelegate;` (scope `UE::ControlRigEditor`)

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/EditMode/SComponentPickerPopup.h` (Private)


#### class `SComponentPickerPopup`  
`class SComponentPickerPopup : public SCompoundWidget`  
_L18-115_
- inherits: `SCompoundWidget`
- L21 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnComponentChosen, FName);`
- L23 _public function_ `SLATE_BEGIN_ARGS(SComponentPickerPopup) : _Actor(NULL), _bCheckForSockets(true)`
- L28 _public prototype_ `SLATE_ARGUMENT(AActor*, Actor) SLATE_ARGUMENT(bool, bCheckForSockets) SLATE_EVENT(FOnComponentChosen, OnComponentChosen) SLATE_END_ARGS() FOnComponentChosen OnComponentChosen;` — An actor with components
- L42 _public member_ `TArray< TSharedPtr<FName> > ComponentNames;` — List of tag names selected in the tag containers
- L45 _private function_ `TSharedRef<ITableRow> MakeListViewWidget(TSharedPtr<FName> InItem, const TSharedRef<STableViewBase>& OwnerTable)`
- L53 _private function_ `void OnComponentSelected(TSharedPtr<FName> InItem, ESelectInfo::Type InSelectInfo)`
- L64 _public function_ `void Construct(const FArguments& InArgs)`

#### Free symbols / members of external scopes

- L21 _delegate_ `DECLARE_DELEGATE_OneParam(FOnComponentChosen, FName);`

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/EditMode/SControlPicker.h` (Private)


#### class `SControlPicker`  
`class SControlPicker : public SCompoundWidget`  
_L20-63_
- inherits: `SCompoundWidget`
- desc: 2D visual picker for picking control manipulators within a rig
- L23 _public function_ `SLATE_BEGIN_ARGS(SControlPicker)`
- L25 _public prototype_ `SLATE_END_ARGS();`
- L27 _public prototype_ `void Construct(const FArguments& InArgs, UWorld* InWorld);`
- L30 _public prototype_ `void SetControlRig(UControlRig* InRig);` — Set the rig to display manipulators for
- L33 _public prototype_ `void SetSelectedManipulators(const TArray<FName>& Manipulators);` — Set the manipulators that are currently selected
- L36 _public prototype_ `void SelectManipulator(FName ManipulatorName, bool bAddToSelection);` — Call when a button is clicked, will fire OnManipulatorsPicked
- L38 _public prototype_ `void ClearSelection();` — Call when background clicked, will fired OnManipulatorsPicked
- L40 _public prototype_ `void SelectAll();` — Select all manipulators
- L43 _public prototype_ `bool IsManipulatorSelected(FName ManipulatorName);` — Returns whether a particular manipulator is selected
- L46 _public prototype_ `UControlRig* GetRig() const;` — Returns the rig we are displaying controls for
- L49 _public prototype_ `bool IsControlIK(FName ControlName) const;` — See if the limb/spine is in IK mode, or FK
- L52 _public prototype_ `void ToggleControlKinematicMode(FName ControlName);` — Toggle kinematic mode for a limb/spine, by name
- L56 _protected prototype_ `EVisibility ShowWidgetHost() const;`
- L59 _protected member_ `TSharedPtr<SEditorUserWidgetHost> EditorUserWidgetHost;` — Widget host for UMG picker
- L62 _protected member_ `TWeakObjectPtr<UControlRig> RigPtr;` — Rig we are showing controls for

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/EditMode/SControlRigBaseListWidget.h` (Private)


#### enum `ESelectedControlAsset::Type`  
`enum Type`  
_L30-38_
- L32 _public enumerator_ `None`
- L33 _public enumerator_ `Pose`
- L34 _public enumerator_ `Animation`
- L35 _public enumerator_ `SelectionSet`
- L37 _public enumerator_ `MAX`

#### class `SControlRigBaseListWidget`  
`class SControlRigBaseListWidget : public SCompoundWidget`  
_L41-138_
- inherits: `SCompoundWidget`
- L44 _public function_ `SLATE_BEGIN_ARGS(SControlRigBaseListWidget)`
- L50 _public prototype_ `void Construct(const FArguments& InArgs);`
- L53 _public function_ `SControlRigBaseListWidget() : bLastInputValidityCheckSuccessful(false)`
- L54 _public prototype_ `~SControlRigBaseListWidget();`
- L56 _public prototype_ `FControlRigEditMode* GetEditMode();`
- L59 _public prototype_ `void FilterChanged();` — Notification that filter has changed, this includes new folder selected
- L62 _public prototype_ `FString GetCurrentlySelectedPath()const;` — Current Path we use to save the asset.
- L65 _public prototype_ `void SelectThisAsset(UObject* Asset);` — Select this Asset, make sure Views all sync up
- L68 _private prototype_ `void BindCommands();`
- L71 _private prototype_ `FText GetAssetNameText()const;` — Asset Related Functions
- L72 _private prototype_ `FText GetPathNameText()const;`
- L73 _private prototype_ `void SetCurrentlySelectedPath(const FString& NewPath);`
- L74 _private prototype_ `void SetCurrentlyEnteredAssetName(const FString& NewName);`
- L75 _private prototype_ `void UpdateInputValidity();`
- L76 _private prototype_ `FString GetObjectPathForSave() const;`
- L79 _private prototype_ `void OnAssetSelected(const FAssetData& AssetData);` — Asset Browser Functions
- L80 _private prototype_ `void OnAssetsActivated(const TArray<FAssetData>& SelectedAssets, EAssetTypeActivationMethod::Type ActivationType);`
- L81 _private prototype_ `void HandleAssetViewFolderEntered(const FString& NewPath);`
- L82 _private prototype_ `TSharedPtr<SWidget> OnGetAssetContextMenu(const TArray<FAssetData>& SelectedAssets);`
- L83 _private prototype_ `void HandlePathSelected(const FString& NewPath);`
- L84 _private prototype_ `TSharedPtr<SWidget> OnGetFolderContextMenu(const TArray<FString>& SelectedPaths, FContentBrowserMenuExtender_SelectedPaths InMenuExtender, FOnCreateNewFolder InOnCreateNewFolder);`
- L85 _private member_ `FSetARFilterDelegate SetFilterDelegate;`
- L86 _private member_ `FGetCurrentSelectionDelegate GetCurrentSelectionDelegate;`
- L87 _private member_ `FSetPathPickerPathsDelegate SetPathsDelegate;`
- L90 _private prototype_ `void ExecuteDeleteFolder(const TArray<FString> SelectedPaths);` — Context Menu Functions
- L91 _private prototype_ `void ExecuteRenameFolder(const FString SelectedPath);`
- L92 _private prototype_ `void ExecuteAddFolder(const FString SelectedPath);`
- L93 _private prototype_ `FReply ExecuteDeleteFolderConfirmed();`
- L94 _private prototype_ `void ExecuteRenameAssets(const TArray<FAssetData> RenameAssets);`
- L95 _private prototype_ `bool CanExecuteRenameAssets(const TArray<FAssetData> RenameAssets) const;`
- L96 _private prototype_ `void ExecuteSaveAssets(const TArray<FAssetData> SelectedAssets);`
- L97 _private prototype_ `void ExecuteDeleteAssets(const TArray<FAssetData> SelectedAssets);`
- L98 _private prototype_ `void ExecutePastePose(UControlRigPoseAsset* PoseAsset);`
- L99 _private prototype_ `bool CanExecutePastePose(UControlRigPoseAsset* PoseAsset) const;`
- L100 _private prototype_ `void ExecuteSelectControls(UControlRigPoseAsset* PoseAsset);`
- L101 _private prototype_ `void ExecutePasteMirrorPose(UControlRigPoseAsset* PoseAsset);`
- L102 _private prototype_ `bool CanExecutePasteMirrorPose(UControlRigPoseAsset* PoseAsset) const;`
- L103 _private prototype_ `void ExecuteUpdatePose(UControlRigPoseAsset* PoseAsset);`
- L104 _private prototype_ `void ExecuteRenamePoseControls(const TArray<FAssetData> SelectedAssets);`
- L105 _private prototype_ `void ExecuteAddFolderToView();`
- L108 _private prototype_ `void CreateCurrentView(UObject* Asset);` — Create the Views for the Selected Asset
- L109 _private prototype_ `TSharedRef<SControlRigPoseView> CreatePoseView(UObject* Asset);`
- L110 _private prototype_ `TSharedRef<SControlRigPoseView> CreateAnimationView(UObject* Asset);`
- L111 _private prototype_ `TSharedRef<SControlRigPoseView> CreateSelectionSetView(UObject* Asset);`
- L114 _private member_ `ESelectedControlAsset::Type CurrentViewType;` — View Type Data
- L115 _private member_ `TSharedPtr<SControlRigPoseView> PoseView;`
- L116 _private member_ `TSharedPtr<SControlRigPoseView> AnimationView;` — todo
- L117 _private member_ `TSharedPtr<SControlRigPoseView> SelectionSetView;` — todo
- L118 _private member_ `TSharedPtr<SBox> EmptyBox;`
- L119 _private member_ `TSharedPtr<SBox> ViewContainer;`
- L121 _private member_ `TSharedPtr<SWidget> PathPicker;`
- L122 _private member_ `TSharedPtr<SWidget> AssetPicker;`
- L124 _private member_ `static FString CurrentlySelectedInternalPath;`
- L125 _private member_ `FString CurrentlyEnteredAssetName;`
- L126 _private member_ `bool bLastInputValidityCheckSuccessful;`
- L129 _private member_ `TSharedPtr< FUICommandList > Commands;` — Commands handled by this widget
- L132 _private member_ `TSharedPtr<FPathPermissionList> CustomFolderPermissionList;` — Deny list held by the Path Picker
- L135 _private prototype_ `void NotifyUser(FNotificationInfo& NotificationInfo);` — Utility function to display notifications to the user
- L137 _private member_ `TWeakPtr<FControlRigEditModeToolkit> WeakToolkit;`

#### Free symbols / members of external scopes

- L28 _namespace_ `namespace ESelectedControlAsset`

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/EditMode/SControlRigControlViews.h` (Private)


#### class `FControlRigView`  
`class FControlRigView`  
_L26-30_
- desc: Class to Hold Statics that are shared and externally callable
- L29 _public prototype_ `static void CaptureThumbnail(UObject* Asset);`

#### class `SControlRigPoseView`  
`class SControlRigPoseView : public SCompoundWidget, public FNotifyHook`  
_L32-117_
- inherits: `SCompoundWidget,FNotifyHook`
- L34 _private function_ `SLATE_BEGIN_ARGS(SControlRigPoseView)`
- L35 _private prototype_ `SLATE_ARGUMENT(UControlRigPoseAsset*, PoseAsset) SLATE_ARGUMENT(TSharedPtr<SControlRigBaseListWidget>, OwningWidget) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L41 _private prototype_ `~SControlRigPoseView();`
- L44 _private prototype_ `virtual void NotifyPostChange(const FPropertyChangedEvent& PropertyChangedEvent, FProperty* PropertyThatChanged) override;` — FNotifyHook
- L45 _private prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L47 _private member_ `bool bUpdateStatusBlocks = false;`
- L48 _private prototype_ `void UpdateStatusBlocks();`
- L53 _private prototype_ `ECheckBoxState IsKeyPoseChecked() const;` — Delegates and Helpers
- L54 _private prototype_ `void OnKeyPoseChecked(ECheckBoxState NewState);`
- L55 _private prototype_ `ECheckBoxState IsMirrorPoseChecked() const;`
- L56 _private prototype_ `void OnMirrorPoseChecked(ECheckBoxState NewState);`
- L57 _private prototype_ `ECheckBoxState IsAdditivePoseChecked() const;`
- L58 _private prototype_ `void OnAdditivePoseChecked(ECheckBoxState NewState);`
- L59 _private prototype_ `bool IsMirrorEnabled() const;`
- L60 _private prototype_ `void OnPoseBlendChanged(float ChangedVal);`
- L61 _private prototype_ `void OnPoseBlendCommited(float ChangedVal, ETextCommit::Type Type);`
- L62 _private prototype_ `void OnBeginSliderMovement();`
- L63 _private prototype_ `void OnEndSliderMovement(float NewValue);`
- L64 _private function_ `float OnGetPoseBlendValue()const`
- L65 _private prototype_ `FReply OnPastePose();`
- L66 _private prototype_ `FReply OnSelectControls();`
- L67 _private prototype_ `FReply OnCaptureThumbnail();`
- L68 _private prototype_ `void HandleControlSelected(UControlRig* Subject, FRigControlElement* InControl, bool bSelected);`
- L69 _private prototype_ `void HandleControlAdded(UControlRig* ControlRig, bool bIsAdded);`
- L70 _private prototype_ `TArray<UControlRig*> GetControlRigs(bool bIsSelected = false);`
- L72 _private member_ `static bool bIsKey;`
- L73 _private member_ `static bool bIsMirror;`
- L74 _private member_ `static bool bIsAdditive;`
- L75 _private member_ `static float bDynamicMin;`
- L76 _private member_ `static float bDynamicMax;`
- L77 _private member_ `static float SplitterSlotValues[3];`
- L79 _private prototype_ `void OnSplitterFinishedResizing();`
- L80 _private member_ `TSharedPtr<SSplitter> PoseSplitter;`
- L82 _private member_ `float PoseBlendValue;`
- L83 _private member_ `bool bIsBlending;`
- L84 _private member_ `bool bSliderStartedTransaction;`
- L85 _private member_ `FControlRigControlPose TempPose;`
- L86 _private member_ `TSharedPtr< FAssetThumbnail > Thumbnail;`
- L87 _private prototype_ `TSharedRef<SWidget> GetThumbnailWidget();`
- L89 _private member_ `TWeakObjectPtr<UControlRigPoseAsset> PoseAsset;`
- L90 _private member_ `TArray<TWeakObjectPtr<UControlRig>> CurrentControlRigs;`
- L92 _private member_ `TSharedPtr<STextBlock> TextStatusBlock1;`
- L93 _private member_ `TSharedPtr<STextBlock> TextStatusBlock2;`
- L95 _private member_ `TWeakPtr<SControlRigBaseListWidget> OwningWidget;`
- L98 _private member_ `TSharedPtr<IDetailsView> MirrorDetailsView;` — Mirroring
- L100 _private function_ `TSharedRef<ITableRow> OnGenerateWidgetForList(TSharedPtr<FString> InItem, const TSharedRef<STableViewBase>& OwnerTable)`
- L116 _public function_ `static bool IsMirror()`

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/EditMode/SControlRigEditModeTools.h` (Private)


#### class `SControlRigEditModeTools`  
`class SControlRigEditModeTools : public SCompoundWidget, public IDetailKeyframeHandler`  
_L20-62_
- inherits: `SCompoundWidget,IDetailKeyframeHandler`
- desc: Shows UI for adding override assets to control rig when the ControlRig.Overrides cvar is enabled.
- L23 _public function_ `SLATE_BEGIN_ARGS(SControlRigEditModeTools)`
- L24 _public prototype_ `SLATE_END_ARGS();`
- L26 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<UE::ControlRigEditor::FRigSelectionViewModel>& InRigViewModel);`
- L29 _public prototype_ `void Cleanup();`
- L32 _public prototype_ `void SetSettingsDetailsObject(const TWeakObjectPtr<>& InObject);` — Set the objects to be displayed in the details panel
- L35 _public prototype_ `void SetSequencer(TWeakPtr<ISequencer> InSequencer);` — Set the sequencer we are bound to
- L38 _public prototype_ `virtual bool IsPropertyKeyable(const UClass* InObjectClass, const class IPropertyHandle& PropertyHandle) const override;` — IDetailKeyframeHandler interface
- L39 _public prototype_ `virtual bool IsPropertyKeyingEnabled() const override;`
- L40 _public prototype_ `virtual void OnKeyPropertyClicked(const IPropertyHandle& KeyedPropertyHandle) override;`
- L41 _public prototype_ `virtual bool IsPropertyAnimated(const class IPropertyHandle& PropertyHandle, UObject *ParentObject) const override;`
- L46 _private member_ `TSharedPtr<UE::ControlRigEditor::FRigSelectionViewModel> RigViewModel;` — Knows about the control rigs that are selected.
- L49 _private member_ `TWeakPtr<ISequencer> WeakSequencer;` — Sequencer we are currently bound to
- L50 _private member_ `TSharedPtr<IDetailsView> SettingsDetailsView;`
- L52 _private member_ `TSharedPtr<IDetailsView> OverridesDetailsView;`
- L55 _private prototype_ `static bool ShouldShowPropertyOnDetailCustomization(const struct FPropertyAndParent& InPropertyAndParent);` — Display or edit set up for property
- L56 _private prototype_ `static bool IsReadOnlyPropertyOnDetailCustomization(const struct FPropertyAndParent& InPropertyAndParent);`
- L58 _private prototype_ `EVisibility GetOverridesExpanderVisibility() const;`
- L59 _private prototype_ `void OnOverrideOptionFinishedChange(const FPropertyChangedEvent& PropertyChangedEvent);`
- L60 _private prototype_ `bool ShouldShowOverrideProperty(const FPropertyAndParent& InPropertyAndParent) const;`
- L61 _private prototype_ `void UpdateOverridesDetailsView();`

#### Free symbols / members of external scopes

- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace ControlRigEditor` (scope `UE`)

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/EditMode/SControlRigOutliner.h` (Private)


#### struct `FMultiRigTreeDelegates`  
`struct FMultiRigTreeDelegates`  
_L39-86_
- L41 _public member_ `FOnGetRigTreeDisplaySettings OnGetDisplaySettings;`
- L42 _public member_ `FOnMultiRigTreeSelectionChanged OnSelectionChanged;`
- L43 _public member_ `FOnContextMenuOpening OnContextMenuOpening;`
- L44 _public member_ `FOnMultiRigTreeMouseButtonClick OnMouseButtonClick;`
- L45 _public member_ `FOnMultiRigTreeMouseButtonDoubleClick OnMouseButtonDoubleClick;`
- L46 _public member_ `FOnRigTreeCompareKeys OnCompareKeys;`
- L47 _public member_ `FOnMultiRigTreeGetEditMode OnGetEditMode;`
- L50 _public function_ `FMultiRigTreeDelegates()`
- L56 _public function_ `const FRigHierarchyTreeDisplaySettings& GetDisplaySettings() const`
- L65 _public function_ `FControlRigEditMode* GetEditMode() const`
- L74 _public function_ `void HandleSelectionChanged(TSharedPtr<FMultiRigTreeElement> Selection, ESelectInfo::Type SelectInfo)`
- L84 _public member_ `static FRigHierarchyTreeDisplaySettings DefaultDisplaySettings;`
- L85 _public member_ `bool bIsChangingRigHierarchy;`

#### class `FMultiRigData`  
`class FMultiRigData`  
_L89-142_
- desc: Data for the tree
- L105 _public function_ `FMultiRigData()`
- L106 _public function_ `FMultiRigData(UControlRig* InControlRig, FRigElementKey InKey) : WeakControlRig(InControlRig), Type(EMultiRigDataType_Element), Key(InKey)`
- L107 _public function_ `FMultiRigData(UControlRig* InControlRig, EMultiRigDataType InType, FName InName) : WeakControlRig(InControlRig), Type(InType), Name(InName)`
- L108 _public prototype_ `FText GetName() const;`
- L109 _public prototype_ `FText GetDisplayName(const FRigHierarchyTreeDisplaySettings& DisplaySettings) const;`
- L110 _public prototype_ `void InvalidateDisplayName() const;`
- L111 _public prototype_ `FText GetToolTipText(const FRigHierarchyTreeDisplaySettings& Settings) const;`
- L112 _public prototype_ `bool operator == (const FMultiRigData & Other) const;`
- L113 _public prototype_ `bool IsValid() const;`
- L114 _public function_ `void Reset()`
- L115 _public prototype_ `URigHierarchy* GetHierarchy() const;`
- L116 _public prototype_ `bool IsModularRig() const;`
- L117 _public prototype_ `FRigModuleInstance* GetModuleInstance() const;`
- L119 _public function_ `bool IsControlElement() const`
- L120 _public function_ `bool IsModule() const`
- L121 _public function_ `bool IsControlRig() const`
- L122 _public function_ `bool IsActor() const`
- L123 _public function_ `bool IsComponent() const`
- L125 _public function_ `FRigElementKey GetElementKey() const`
- L126 _public function_ `FName GetItemName() const`
- L128 _public function_ `void SetElementKey(const FRigElementKey& InKey)`
- L129 _public function_ `void SetItemName(EMultiRigDataType InType, const FName& InName)`
- L130 _public function_ `void SetUniqueID(const uint32 InID)`
- L132 _public member_ `TWeakObjectPtr<UControlRig> WeakControlRig;`
- L133 _public member_ `EMultiRigDataType Type;`
- L137 _private member_ `TOptional<FName> Name;`
- L138 _private member_ `TOptional<FRigElementKey> Key;`
- L139 _private member_ `TOptional<uint32> UniqueID;`
- L141 _private member_ `mutable TOptional<FText> CachedDisplayName;`

#### enum `FMultiRigData::EMultiRigDataType`  
`enum EMultiRigDataType : uint8`  
_L93-103_
- L95 _public enumerator_ `EMultiRigDataType_ControlRig`
- L96 _public enumerator_ `EMultiRigDataType_Element`
- L97 _public enumerator_ `EMultiRigDataType_Module`
- L98 _public enumerator_ `EMultiRigDataType_Component`
- L99 _public enumerator_ `EMultiRigDataType_Actor`
- L101 _public enumerator_ `EMultiRigDataType_MAX`
- L102 _public enumerator_ `EMultiRigDataType_Invalid = EMultiRigDataType_MAX`

#### class `FMultiRigTreeElement`  
`class FMultiRigTreeElement : public TSharedFromThis<FMultiRigTreeElement>`  
_L145-177_
- inherits: `TSharedFromThis<FMultiRigTreeElement>`
- desc: An item in the tree
- L148 _public prototype_ `FMultiRigTreeElement(const FMultiRigData& InData, TWeakPtr<SMultiRigHierarchyTreeView> InTreeView,ERigTreeFilterResult InFilterResult);`
- L151 _public member_ `FMultiRigData Data;` — Element Data to display
- L152 _public member_ `TArray<TSharedPtr<FMultiRigTreeElement>> Children;`
- L154 _public prototype_ `TSharedRef<ITableRow> MakeTreeRowWidget(const TSharedRef<STableViewBase>& InOwnerTable, TSharedRef<FMultiRigTreeElement> InRigTreeElement, TSharedPtr<SMultiRigHierarchyTreeView> InTreeView, const FRigHierarchyTreeDisplaySettings& InSettings, bool bPinned);`
- L156 _public prototype_ `void RefreshDisplaySettings(const URigHierarchy* InHierarchy, const FRigHierarchyTreeDisplaySettings& InSettings);`
- L157 _public prototype_ `bool AreControlsVisible() const;`
- L160 _public member_ `ERigTreeFilterResult FilterResult;` — The current filter result
- L163 _public member_ `const FSlateBrush* IconBrush;` — The brush to use when rendering an icon
- L166 _public member_ `FSlateColor IconColor;` — The color to use when rendering an icon
- L169 _public member_ `FSlateColor TextColor;` — The color to use when rendering the label text
- L172 _public member_ `bool bIsRowHovered = false;` — Whether or not this row is being hovered
- L175 _public member_ `bool bIsEyeballIconHovered = false;` — Whether or not the eyeball icon is being hovered

#### class `SMultiRigHierarchyItem`  
`class SMultiRigHierarchyItem : public SMultiColumnTableRow<TSharedPtr<FMultiRigTreeElement>>`  
_L179-201_
- inherits: `SMultiColumnTableRow<TSharedPtr<FMultiRigTreeElement>>`
- L183 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& OwnerTable, TSharedRef<FMultiRigTreeElement> InRigTreeElement, TSharedPtr<SMultiRigHierarchyTreeView> InTreeView, const FRigHierarchyTreeDisplaySettings& InSettings, bool bPinned);`
- L184 _public prototype_ `static TPair<const FSlateBrush*, FSlateColor> GetBrushForElementType(const URigHierarchy* InHierarchy, const FMultiRigData& InData);`
- L185 _public prototype_ `virtual const FSlateBrush* GetBorder() const override;`
- L186 _public prototype_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn( const FName& InColumnName ) override;`
- L187 _public prototype_ `virtual void OnMouseEnter(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L188 _public prototype_ `virtual void OnMouseLeave(const FPointerEvent& MouseEvent) override;`
- L191 _private member_ `TWeakPtr<FMultiRigTreeElement> WeakRigTreeElement;`
- L192 _private member_ `TSharedPtr<SMultiRigHierarchyTreeView> TreeView;`
- L193 _private member_ `FMultiRigTreeDelegates Delegates;`
- L195 _private prototype_ `FText GetDisplayName() const;`
- L196 _private prototype_ `FText GetToolTipText() const;`
- L197 _private prototype_ `FReply OnToggleVisibilityClicked();`
- L199 _private member_ `static TMap<FSoftObjectPath, TSharedPtr<FSlateBrush>> IconPathToBrush;`

#### class `SMultiRigHierarchyTreeView`  
`class SMultiRigHierarchyTreeView : public STreeView<TSharedPtr<FMultiRigTreeElement>>`  
_L203-298_
- inherits: `STreeView<TSharedPtr<FMultiRigTreeElement>>`
- L207 _public function_ `SLATE_BEGIN_ARGS(SMultiRigHierarchyTreeView)`
- L208 _public prototype_ `SLATE_ARGUMENT(FMultiRigTreeDelegates, RigTreeDelegates) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L212 _public prototype_ `virtual ~SMultiRigHierarchyTreeView();`
- L214 _public function_ `virtual FReply OnFocusReceived(const FGeometry& MyGeometry, const FFocusEvent& InFocusEvent) override`
- L221 _public function_ `void SaveAndClearSparseItemInfos()` — Save a snapshot of the internal map that tracks item expansion before tree reconstruction
- L232 _public function_ `void RestoreSparseItemInfos(TSharedPtr<FMultiRigTreeElement> ItemPtr)` — Restore the expansion infos map from the saved snapshot after tree reconstruction
- L245 _public prototype_ `static TSharedPtr<FMultiRigTreeElement> FindElement(const FMultiRigData& InData, TSharedPtr<FMultiRigTreeElement> CurrentItem);`
- L247 _public prototype_ `bool AddElement(const FMultiRigData& InData, const FMultiRigData& InParentData);`
- L248 _public prototype_ `bool AddElement(UControlRig* InControlRig, const FRigBaseElement* InElement);`
- L249 _public prototype_ `bool ReparentElement(const FMultiRigData& InData, const FMultiRigData& InParentData);`
- L250 _public prototype_ `bool RemoveElement(const FMultiRigData& InData);`
- L251 _public prototype_ `void SetExpansionRecursive(TSharedPtr<FMultiRigTreeElement> InElement, bool bShouldBeExpanded);`
- L252 _public prototype_ `void SetExpansionRecursive(TSharedPtr<FMultiRigTreeElement> InElement, bool bTowardsParent, bool bShouldBeExpanded);`
- L253 _public prototype_ `TSharedRef<ITableRow> MakeTableRowWidget(TSharedPtr<FMultiRigTreeElement> InItem, const TSharedRef<STableViewBase>& OwnerTable, bool bPinned);`
- L254 _public prototype_ `void HandleGetChildrenForTree(TSharedPtr<FMultiRigTreeElement> InItem, TArray<TSharedPtr<FMultiRigTreeElement>>& OutChildren);`
- L255 _public prototype_ `TSharedPtr<FMultiRigTreeElement> FindElement(const FMultiRigData& InData);`
- L256 _public prototype_ `void HandleMouseClicked(TSharedPtr<FMultiRigTreeElement> InElement);`
- L258 _public prototype_ `TArray<FMultiRigData> GetSelectedData() const;`
- L259 _public function_ `const TArray<TSharedPtr<FMultiRigTreeElement>>& GetRootElements() const`
- L260 _public function_ `FMultiRigTreeDelegates& GetTreeDelegates()`
- L262 _public prototype_ `TArray<URigHierarchy*> GetHierarchy() const;`
- L263 _public prototype_ `void SetControlRigs(const TArrayView<TWeakObjectPtr<UControlRig>>& InControlRigs);`
- L266 _public prototype_ `void RequestTreeViewRefresh();` — Requests a tree view refresh. The actual refresh will be done lazily.
- L268 _public prototype_ `TSharedPtr<FMultiRigTreeElement> GetParentElement(TSharedPtr<FMultiRigTreeElement> InElement) const;`
- L270 _public prototype_ `void ScrollToElement(const FMultiRigData& InElement);`
- L275 _private member_ `TSparseItemMap OldSparseItemInfos;` — A temporary snapshot of the SparseItemInfos in STreeView, used during RefreshTreeView()
- L278 _private member_ `TArray<TSharedPtr<FMultiRigTreeElement>> RootElements;` — Backing array for tree view
- L281 _private member_ `TMap<FMultiRigData, TSharedPtr<FMultiRigTreeElement>> ElementMap;` — A map for looking up items based on their key
- L284 _private member_ `TMap<FMultiRigData, FMultiRigData> ParentMap;` — A map for looking up a parent based on their key
- L286 _private member_ `FMultiRigTreeDelegates Delegates;`
- L290 _private member_ `TArray <TWeakObjectPtr<UControlRig>> ControlRigs;`
- L293 _private member_ `TWeakPtr<FActiveTimerHandle> PendingTreeViewRefreshHandle;` — Pending function to refresh the tree view.
- L294 _private member_ `bool bRefreshPending = false;`
- L295 _private member_ `FMultiRigData ScrollToElementAfterRefresh;`
- L296 _private prototype_ `void UnregisterPendingRefresh();`
- L297 _private prototype_ `void RefreshTreeView();`

#### class `SSearchableMultiRigHierarchyTreeView`  
`class SSearchableMultiRigHierarchyTreeView : public SCompoundWidget`  
_L300-344_
- inherits: `SCompoundWidget`
- L304 _public function_ `SLATE_BEGIN_ARGS(SSearchableMultiRigHierarchyTreeView)`
- L306 _public prototype_ `SLATE_ARGUMENT(FMultiRigTreeDelegates, RigTreeDelegates) SLATE_ARGUMENT(FText, InitialFilterText) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L311 _public prototype_ `virtual ~SSearchableMultiRigHierarchyTreeView() = default;`
- L312 _public function_ `TSharedRef<SMultiRigHierarchyTreeView> GetTreeView() const`
- L313 _public prototype_ `const FRigHierarchyTreeDisplaySettings& GetDisplaySettings();`
- L314 _public prototype_ `TSharedRef<SWidget> OnGetOptionsMenu();`
- L315 _public prototype_ `void BindCommands();`
- L316 _public prototype_ `void OnSettingChanged(UObject* Object, FPropertyChangedEvent& PropertyChangedEvent);`
- L318 _public prototype_ `bool IsArrangedByModules() const;`
- L319 _public prototype_ `void ToggleArrangeByModules();`
- L320 _public prototype_ `bool IsShowingFlatModules() const;`
- L321 _public prototype_ `void ToggleFlattenModules();`
- L322 _public prototype_ `EElementNameDisplayMode GetElementNameDisplayMode() const;`
- L323 _public prototype_ `void SetElementNameDisplayMode(EElementNameDisplayMode InElementNameDisplayMode);`
- L324 _public prototype_ `void ToggleModuleManipulators();`
- L325 _public prototype_ `bool CanToggleModuleManipulators() const;`
- L326 _public prototype_ `bool IsFocusingOnSelection() const;`
- L327 _public prototype_ `void ToggleFocusOnSelection();`
- L328 _public prototype_ `void SetMultiRigMode(const EMultiRigTreeDisplayMode InMode);`
- L329 _public prototype_ `bool IsMultiRigMode(const EMultiRigTreeDisplayMode InMode);`
- L330 _public prototype_ `EMultiRigTreeDisplayMode GetMultiRigMode();`
- L334 _private prototype_ `void OnFilterTextChanged(const FText& SearchText);`
- L337 _private member_ `TSharedPtr<FUICommandList> CommandList;` — Command list we bind to
- L339 _private member_ `FOnGetRigTreeDisplaySettings SuperGetRigTreeDisplaySettings;`
- L340 _private member_ `FOnMultiRigTreeGetEditMode GetEditMode;`
- L341 _private member_ `FText FilterText;`
- L342 _private member_ `FRigHierarchyTreeDisplaySettings Settings;`
- L343 _private member_ `TSharedPtr<SMultiRigHierarchyTreeView> TreeView;`

#### class `SControlRigOutliner`  
`class SControlRigOutliner : public FControlRigBaseDockableView, public SCompoundWidget`  
_L346-382_
- inherits: `FControlRigBaseDockableView,SCompoundWidget`
- L348 _private function_ `SLATE_BEGIN_ARGS(SControlRigOutliner)`
- L350 _private prototype_ `SControlRigOutliner();`
- L351 _private prototype_ `~SControlRigOutliner();`
- L353 _private prototype_ `void Construct(const FArguments& InArgs, FControlRigEditMode& InEditMode);`
- L356 _private function_ `virtual TSharedRef<FControlRigBaseDockableView> AsSharedWidget() override` — FControlRigBaseDockableView overrides
- L357 _private prototype_ `virtual void SetEditMode(FControlRigEditMode& InEditMode) override;`
- L359 _private prototype_ `virtual void HandleControlAdded(UControlRig* ControlRig, bool bIsAdded) override;`
- L360 _private prototype_ `virtual void HandleControlSelected(UControlRig* Subject, FRigControlElement* InControl, bool bSelected) override;`
- L361 _private prototype_ `virtual void HandleRigVisibilityChanged(TArray<UControlRig*> InControlRigs) override;`
- L362 _private prototype_ `virtual void HandleHierarchyModified(ERigHierarchyNotification InNotification, URigHierarchy* InHierarchy, const FRigNotificationSubject& InSubject);`
- L365 _private prototype_ `void HandleOnControlRigBound(UControlRig* InControlRig);` — control rig delegates
- L366 _private prototype_ `void HandleOnObjectBoundToControlRig(UObject* InObject);`
- L367 _private prototype_ `void HandlePostConstruction(UControlRig* InControlRig, const FName& InEventName);`
- L369 _private prototype_ `void OnObjectsReplaced(const TMap<UObject*, UObject*>& OldToNewInstanceMap);`
- L370 _private prototype_ `void OnSequencerTreeViewChanged(EMovieSceneDataChangeType MovieSceneDataChange);`
- L372 _private prototype_ `void HandleSelectionChanged(TSharedPtr<FMultiRigTreeElement> Selection, ESelectInfo::Type SelectInfo);`
- L375 _private member_ `TSharedPtr<SSearchableMultiRigHierarchyTreeView> HierarchyTreeView;` — Hierarchy picker for controls
- L376 _private member_ `FRigHierarchyTreeDisplaySettings DisplaySettings;`
- L377 _private function_ `const FRigHierarchyTreeDisplaySettings& GetDisplaySettings() const`
- L378 _private member_ `bool bIsChangingRigHierarchy = false;`
- L381 _private member_ `TArray<TWeakObjectPtr<UControlRig>> BoundControlRigs;` — set of control rigs we are bound too and need to clear delegates from

#### Free symbols / members of external scopes

- L17 _macro_ `#define UE_API CONTROLRIGEDITOR_API`
- L29 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FOnMultiRigTreeCompareKeys, const FMultiRigData& , const FMultiRigData& );`
- L29 _prototype_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FOnMultiRigTreeCompareKeys, const FMultiRigData& , const FMultiRigData& );`
- L30 _delegate_ `DECLARE_DELEGATE_RetVal(FControlRigEditMode*, FOnMultiRigTreeGetEditMode);`
- L30 _prototype_ `DECLARE_DELEGATE_RetVal(FControlRigEditMode*, FOnMultiRigTreeGetEditMode);`
- L32 _typedef_ `typedef STreeView<TSharedPtr<FMultiRigTreeElement>>::FOnSelectionChanged FOnMultiRigTreeSelectionChanged;`
- L33 _typedef_ `typedef STreeView<TSharedPtr<FMultiRigTreeElement>>::FOnMouseButtonClick FOnMultiRigTreeMouseButtonClick;`
- L34 _typedef_ `typedef STreeView<TSharedPtr<FMultiRigTreeElement>>::FOnMouseButtonDoubleClick FOnMultiRigTreeMouseButtonDoubleClick;`
- L35 _typedef_ `typedef STreeView<TSharedPtr<FMultiRigTreeElement>>::FOnSetExpansionRecursive FOnMultiRigTreeSetExpansionRecursive;`
- L37 _prototype_ `uint32 GetTypeHash(const FMultiRigData& Data);`

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/EditMode/SControlRigRenamePoseControls.h` (Private)


#### struct `FControlRigRenameControlsDialog`  
`struct FControlRigRenameControlsDialog`  
_L8-11_
- L10 _public prototype_ `static void RenameControls(const TArray<UControlRigPoseAsset*>& PoseAssets);`

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/EditMode/SControlRigSnapper.h` (Private)


#### class `SControlRigSnapper`  
`class SControlRigSnapper : public SCompoundWidget`  
_L22-71_
- inherits: `SCompoundWidget`
- L24 _private function_ `SLATE_BEGIN_ARGS(SControlRigSnapper)`
- L27 _private prototype_ `~SControlRigSnapper();`
- L29 _private prototype_ `void Construct(const FArguments& InArgs);`
- L34 _private prototype_ `void GetControlRigs(TArray<UControlRig*>& OutControlRigs) const;`
- L39 _private prototype_ `void ActorParentPicked(FActorForWorldTransforms Selection);` — Delegates and Helpers
- L40 _private prototype_ `void ActorParentSocketPicked(const FName SocketName, FActorForWorldTransforms Selection);`
- L41 _private prototype_ `void ActorParentComponentPicked(FName ComponentName, FActorForWorldTransforms Selection);`
- L42 _private prototype_ `void OnActivateSequenceChanged(FMovieSceneSequenceIDRef ID);`
- L44 _private prototype_ `FReply OnActorToSnapClicked();`
- L45 _private prototype_ `FReply OnParentToSnapToClicked();`
- L46 _private prototype_ `FText GetActorToSnapText();`
- L47 _private prototype_ `FText GetParentToSnapText();`
- L49 _private prototype_ `FReply OnStartFrameClicked();`
- L50 _private prototype_ `FReply OnEndFrameClicked();`
- L51 _private prototype_ `FText GetStartFrameToSnapText();`
- L52 _private prototype_ `FText GetEndFrameToSnapText();`
- L54 _private prototype_ `void ClearActors();`
- L55 _private prototype_ `void SetStartEndFrames();`
- L56 _private prototype_ `FReply OnSnapAnimationClicked();`
- L58 _private prototype_ `FControlRigSnapperSelection GetSelection(bool bGetAll);`
- L61 _private member_ `TSharedPtr<IDetailsView> SnapperDetailsView;` — FControlRigSnapper  ControlRigSnapper;
- L63 _private member_ `FControlRigSnapperSelection ActorToSnap;`
- L64 _private member_ `FControlRigSnapperSelection ParentToSnap;`
- L66 _private member_ `FFrameNumber StartFrame;`
- L67 _private member_ `FFrameNumber EndFrame;`
- L69 _private member_ `FControlRigSnapper Snapper;`

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/EditMode/SControlRigUpdatePose.h` (Private)


#### struct `FControlRigUpdatePoseDialog`  
`struct FControlRigUpdatePoseDialog`  
_L8-11_
- L10 _public prototype_ `static void UpdatePose(UControlRigPoseAsset* PoseAsset);`

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/EditMode/SCurveControlContainer.h` (Private)


#### class `FDisplayedCurveControlInfo`  
`class FDisplayedCurveControlInfo`  
_L19-40_
- L22 _public member_ `FName CurveName;`
- L23 _public member_ `float Value;`
- L26 _public function_ `static TSharedRef<FDisplayedCurveControlInfo> Make(const FName& InCurveName)` — Static function for creating a new item, but ensures that you can only have a TSharedRef to one
- L32 _public member_ `TSharedPtr<SInlineEditableTextBlock> EditableText;` — editable text
- L36 _protected function_ `FDisplayedCurveControlInfo(const FName& InCurveName) : CurveName(InCurveName) , Value( 0 )` — Hidden constructor, always use Make above

#### class `SCurveControlListRow`  
`class SCurveControlListRow : public SMultiColumnTableRow< FDisplayedCurveControlInfoPtr >`  
_L52-113_
- inherits: `SMultiColumnTableRow<FDisplayedCurveControlInfoPtr>`
- L56 _public function_ `SLATE_BEGIN_ARGS(SCurveControlListRow)`
- L59 _public prototype_ `SLATE_ARGUMENT(FDisplayedCurveControlInfoPtr, Item) SLATE_EVENT(FSetCurveControlValue, OnSetCurveControlValue) SLATE_EVENT(FGetCurveControlValue, OnGetCurveControlValue) SLATE_EVENT(FGetFilterText, OnGetFilterText) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& OwnerTableView);` — The item for this row
- L76 _public prototype_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& ColumnName) override;` — Overridden from SMultiColumnTableRow.  Generates a widget for this column of the tree row.
- L88 _private prototype_ `void OnCurveControlValueChanged(float NewValue);` — Called when the user changes the value of the SSpinBox @param NewValue - The new number the SSpinBox is set to this may not work right if the rig is being evaluated this just overwrite the data when it's written
- L96 _private prototype_ `void OnCurveControlValueValueCommitted(float NewValue, ETextCommit::Type CommitType);` — Called when the user types the value and enters @param NewValue - The new number the SSpinBox is set to
- L99 _private prototype_ `float GetValue() const;` — Returns the Value of this curve
- L101 _private prototype_ `FText GetItemName() const;` — Returns name of this curve
- L103 _private prototype_ `FText GetFilterText() const;` — Get text we are filtering for
- L105 _private prototype_ `FSlateColor GetItemTextColor() const;` — Return color for text of item
- L108 _private member_ `FDisplayedCurveControlInfoPtr Item;` — The name and Value of the morph target
- L110 _private member_ `FSetCurveControlValue OnSetCurveControlValue;`
- L111 _private member_ `FGetCurveControlValue OnGetCurveControlValue;`
- L112 _private member_ `FGetFilterText OnGetFilterText;`

#### class `SCurveControlContainer`  
`class SCurveControlContainer : public SCompoundWidget`  
_L118-217_
- inherits: `SCompoundWidget`
- L121 _public function_ `SLATE_BEGIN_ARGS( SCurveControlContainer )`
- L124 _public prototype_ `SLATE_END_ARGS() void Construct( const FArguments& InArgs, UControlRig* InControlRig);`
- L138 _public prototype_ `virtual ~SCurveControlContainer();` — Destructor - resets the animation curve
- L146 _public prototype_ `void OnFilterTextChanged( const FText& SearchText );` — Filters the SListView when the user changes the search text box (NameFilterBox) @param SearchText - The text the user has typed
- L157 _public prototype_ `void OnFilterTextCommitted( const FText& SearchText, ETextCommit::Type CommitInfo );` — Filters the SListView when the user hits enter or clears the search box Simply calls OnFilterTextChanged @param SearchText - The text the user has typed @param CommitInfo - Not used
- L167 _public prototype_ `TSharedRef<ITableRow> GenerateCurveControlRow(FDisplayedCurveControlInfoPtr InInfo, const TSharedRef<STableViewBase>& OwnerTable);` — Create a widget for an entry in the tree from an info @param InInfo - Shared pointer to the morph target we're generating a row for @param OwnerTable - The table that owns this row @return A new Slate widget, containing the UI for this row
- L173 _public function_ `FText& GetFilterText()` — Accessor so our rows can grab the filtertext for highlighting
- L175 _public prototype_ `void RefreshCurveList();`
- L176 _public prototype_ `void SetControlRig(UControlRig* InControlRig);`
- L185 _private prototype_ `void CreateCurveControlList( const FString& SearchText = FString() );` — Clears and rebuilds the table, according to an optional search string @param SearchText - Optional search string
- L188 _private prototype_ `void SetCurveValue(const FName& CurveName, float CurveValue);` — delegate for changing info
- L189 _private prototype_ `float GetCurveValue(const FName& CurveName);`
- L191 _private prototype_ `void OnSelectionChanged(FDisplayedCurveControlInfoPtr Selection, ESelectInfo::Type SelectInfo);`
- L193 _private prototype_ `void OnRigElementSelected(UControlRig* Subject, FRigControlElement* ControlElement, bool bSelected);`
- L196 _private member_ `TSharedPtr<SSearchBox> NameFilterBox;` — Box to filter to a specific morph target name
- L199 _private member_ `TArray< FDisplayedCurveControlInfoPtr > CurveControlList;` — A list of animation curve. Used by the CurveControlListView.
- L202 _private member_ `TSharedPtr<SCurveControlListType> CurveControlListView;` — Widget used to display the list of animation curve
- L205 _private member_ `TWeakObjectPtr<UControlRig> ControlRig;` — ControlRig
- L208 _private member_ `FText FilterText;` — Current text typed into NameFilterBox
- L211 _private member_ `TSharedPtr<FUICommandList> UICommandList;` — Commands that are bound to delegates
- L213 _private prototype_ `URigHierarchy* GetHierarchy() const;`

#### Free symbols / members of external scopes

- L42 _typedef_ `typedef TSharedPtr< FDisplayedCurveControlInfo > FDisplayedCurveControlInfoPtr;`
- L43 _typedef_ `typedef SListView< FDisplayedCurveControlInfoPtr > SCurveControlListType;`
- L48 _delegate_ `DECLARE_DELEGATE_TwoParams(FSetCurveControlValue, const FName&, float);`
- L48 _prototype_ `DECLARE_DELEGATE_TwoParams(FSetCurveControlValue, const FName&, float);`
- L49 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(float, FGetCurveControlValue, const FName&);`
- L49 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(float, FGetCurveControlValue, const FName&);`
- L50 _delegate_ `DECLARE_DELEGATE_RetVal(FText&, FGetFilterText);`
- L50 _prototype_ `DECLARE_DELEGATE_RetVal(FText&, FGetFilterText);`

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/EditMode/SEditorUserWidgetHost.h` (Private)


#### class `SEditorUserWidgetHost`  
`class SEditorUserWidgetHost : public SCompoundWidget, public FGCObject`  
_L9-28_
- inherits: `SCompoundWidget,FGCObject`
- L12 _public function_ `SLATE_BEGIN_ARGS(SEditorUserWidgetHost)`
- L14 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, UWorld* InWorld);`
- L19 _public prototype_ `virtual void AddReferencedObjects( FReferenceCollector& Collector ) override;` — FGCObject interface
- L20 _public function_ `virtual FString GetReferencerName() const override`
- L27 _private member_ `TWeakObjectPtr<UWorld> World;` — The world we create widgets with

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/EditMode/Settings/ConstraintsTabRestoreState.h` (Private)


#### enum `EControlRigConstrainTab`  
`enum class EControlRigConstrainTab : uint8`  
_L9-14_
- reflection: `UENUM()`
- L11 _public enumerator_ `Spaces`
- L12 _public enumerator_ `Constraints`
- L13 _public enumerator_ `Snapper`

#### struct `FControlRigConstraintsTabRestoreState`  
`struct FControlRigConstraintsTabRestoreState`  
_L17-26_
- reflection: `USTRUCT()`
- L22 _public member_ `bool bWasOpen = false;` — `UPROPERTY()`
- L25 _public member_ `EControlRigConstrainTab LastOpenInlineTab = EControlRigConstrainTab::Spaces;` — `UPROPERTY()`

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/EditMode/Settings/ControlRigUIRestoreStates.h` (Private)


#### struct `FControlRigUIRestoreStates`  
`struct FControlRigUIRestoreStates`  
_L12-46_
- reflection: `USTRUCT()`
- desc: Data to restore the UI state control rig had last time it was open.
- L17 _public member_ `bool bMotionTrailsOn = false;` — `UPROPERTY()`
- L20 _public member_ `bool bAnimLayerTabOpen = false;` — `UPROPERTY()`
- L23 _public member_ `bool bPoseTabOpen = false;` — `UPROPERTY()`
- L26 _public member_ `bool bSnapperTabOpen = false;` — `UPROPERTY()`
- L29 _public member_ `FControlRigConstraintsTabRestoreState ConstraintsTabState;` — `UPROPERTY()`
- L33 _public member_ `bool bSelectionSetsOpen = false;` — `UPROPERTY()` — Whether the selection set was open when SELECTION_SETS_AS_TAB == 1
- L37 _public member_ `FToolWidget_FlyoutSavedState SelectionSetOverlayState;` — `UPROPERTY()` — Selection set view state if SELECTION_SETS_AS_TAB == 0
- L40 _public member_ `FToolWidget_FlyoutSavedState TweenOverlayState;` — `UPROPERTY()`
- L42 _public function_ `explicit FControlRigUIRestoreStates() : SelectionSetOverlayState(FToolWidget_DragBoxPosition(FVector2f(20.f, 30.f), HAlign_Right, VAlign_Top), false) , TweenOverlayState(FToolWidget_DragBoxPosition(FVector2f(20.f, 30.f), HAlign_Right, VAlign_Bottom), false)`

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/EditMode/Tween/ControlRigObjectSelection.h` (Private)


#### struct `UE::ControlRigEditor::FChannelKeyBounds`  
`struct FChannelKeyBounds`  
_L21-40_
- desc: Key bounds and their values used to blend with Controls and Actor float channels
- L23 _public function_ `FChannelKeyBounds() : bValid(false), FloatChannel(nullptr), DoubleChannel(nullptr) , PreviousIndex(INDEX_NONE), NextIndex(INDEX_NONE) , PreviousFrame(0), NextFrame(0), CurrentFrame(0), PreviousValue(0.0), NextValue(0.0), CurrentValue(0.0)`
- L29 _public member_ `bool bValid;`
- L30 _public member_ `FMovieSceneFloatChannel* FloatChannel;`
- L31 _public member_ `FMovieSceneDoubleChannel* DoubleChannel;`
- L32 _public member_ `int32 PreviousIndex;`
- L33 _public member_ `int32 NextIndex;`
- L34 _public member_ `FFrameNumber PreviousFrame;`
- L35 _public member_ `FFrameNumber NextFrame;`
- L36 _public member_ `FFrameNumber CurrentFrame;`
- L37 _public member_ `double PreviousValue;`
- L38 _public member_ `double NextValue;`
- L39 _public member_ `double CurrentValue;`

#### struct `UE::ControlRigEditor::FControlRigObjectSelection`  
`struct FControlRigObjectSelection`  
_L43-67_
- desc: Contains the selection state for a set of Control Rig Controls to blend with the anim slider
- L53 _public prototype_ `bool Setup(const TWeakPtr<ISequencer>& InSequencer, const TWeakPtr<FControlRigEditMode>& InEditMode);`
- L54 _public prototype_ `bool Setup(const TArray<UControlRig*>& SelectedControlRigs, const TWeakPtr<ISequencer>& InSequencer);`
- L56 _public member_ `TArray<FObjectChannels> ChannelsArray;`
- L61 _private prototype_ `void SetupChannel( FFrameNumber CurrentFrame, TArray<FFrameNumber>& KeyTimes, TArray<FKeyHandle>& Handles, FMovieSceneFloatChannel* FloatChannel, FMovieSceneDoubleChannel* DoubleChannel, FChannelKeyBounds& KeyBounds );` — Either float or double will be non-null
- L66 _private prototype_ `TArray<UControlRig*> GetControlRigs(const TWeakPtr<FControlRigEditMode>& InEditMode);`

#### struct `UE::ControlRigEditor::FControlRigObjectSelection::FObjectChannels`  
`struct FObjectChannels`  
_L46-51_
- desc: set of possible float channels
- L48 _public function_ `FObjectChannels() : Section(nullptr)`
- L49 _public member_ `TArray<FChannelKeyBounds> KeyBounds;`
- L50 _public member_ `UMovieSceneSection* Section;`

#### Free symbols / members of external scopes

- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace ControlRigEditor` (scope `UE`)

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/EditMode/Tween/ControlRigTweenModel.h` (Private)


#### class `UE::ControlRigEditor::TControlRigTweenModel`  
`template<TweeningUtilsEditor::EBlendFunction> class TControlRigTweenModel : public TweeningUtilsEditor::FTweenModel`  
_L29-72_
- inherits: `TweeningUtilsEditor::FTweenModel`
- desc: Implements tweening in ControlRig Priority of tweening: 1. If keys are selected in the curve editor, tween those keys. 2. Otherwise, if a control rig element is selected, insert a key at the current scrub position into the curves corresponding to the control rig and then interpolate those keys.
- L33 _public function_ `explicit TControlRigTweenModel(TAttribute<TWeakPtr<ISequencer>> InSequencerAttr, TWeakPtr<FControlRigEditMode> InControlRigMode) : SequencerAttr(MoveTemp(InSequencerAttr)) , ControlRigMode(MoveTemp(InControlRigMode))`
- L37 _public function_ `explicit TControlRigTweenModel(TAttribute<TWeakPtr<ISequencer>> InSequencerAttr) : TControlRigTweenModel(MoveTemp(InSequencerAttr), nullptr)`
- L42 _public prototype_ `bool BlendSingle(float InNormalizedValue);` — Does a blend and returns whether any values were actually blended.
- L44 _public prototype_ `bool BlendSingleWithControlRigs(float InNormalizedValue, const TArray<UControlRig*>& InControlRigs);` — Does a blend on specified control rigs and returns whether any values were actually blended.
- L47 _public prototype_ `void StartBlendOperationWithControlRigs(const TArray<UControlRig*>& InControlRigs);` — Inits this model with control rigs.
- L50 _public prototype_ `virtual void StartBlendOperation() override;`
- L51 _public function_ `virtual void BlendValues(float InNormalizedValue) override`
- L57 _private member_ `const TAttribute<TWeakPtr<ISequencer>> SequencerAttr;` — Gets the sequencer used by Control Rig. Can return nullptr (e.g. when user has closed the sequencer), in which case blending does nothing.
- L59 _private member_ `const TWeakPtr<FControlRigEditMode> ControlRigMode;` — The control rig mode that owns this tweener. Can be nullptr, in which case only the curve editor key selection is blended.
- L62 _private member_ `TweeningUtilsEditor::FContiguousKeyMapping KeySelection;` — The key selection to blend. Created in StartBlendOperation and used for the entirety of the blend operation.
- L67 _private member_ `FControlRigObjectSelection ObjectSelection;` — The control rig selection to blend if ContiguousKeySelection is empty. Created in StartBlendOperation and used for the entirety of the blend operation.
- L70 _private prototype_ `bool DoBlend(float InNormalizedValue);` — @return Whether any blended occured.
- L71 _private prototype_ `bool BlendObjectSelection(const TSharedPtr<ISequencer>& SequencerPin, float InScaledBlendValue);`
- L78 _function_ `template <TweeningUtilsEditor::EBlendFunction BlendFunction> bool TControlRigTweenModel<BlendFunction>::BlendSingle(float InNormalizedValue)`
- L87 _function_ `template <TweeningUtilsEditor::EBlendFunction BlendFunction> bool TControlRigTweenModel<BlendFunction>::BlendSingleWithControlRigs(float InNormalizedValue, const TArray<UControlRig*>& InControlRigs)`
- L96 _function_ `template <TweeningUtilsEditor::EBlendFunction BlendFunction> void TControlRigTweenModel<BlendFunction>::StartBlendOperationWithControlRigs(const TArray<UControlRig*>& InControlRigs)`
- L106 _function_ `template <TweeningUtilsEditor::EBlendFunction BlendFunction> void TControlRigTweenModel<BlendFunction>::StartBlendOperation()`
- L127 _function_ `template <TweeningUtilsEditor::EBlendFunction BlendFunction> bool TControlRigTweenModel<BlendFunction>::DoBlend(float InNormalizedValue)`
- L162 _function_ `template <TweeningUtilsEditor::EBlendFunction BlendFunction> bool TControlRigTweenModel<BlendFunction>::BlendObjectSelection(const TSharedPtr<ISequencer>& SequencerPin, float InScaledBlendValue)`

#### Free symbols / members of external scopes

- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace ControlRigEditor` (scope `UE`)
- L75 _namespace_ `namespace UE`
- L75 _namespace_ `namespace ControlRigEditor` (scope `UE`)
- L148 _function_ `` (scope `UE::ControlRigEditor::TControlRigTweenModel::DoBlend`)

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/EditMode/Tween/ControlRigTweenModels.h` (Private)


#### class `UE::ControlRigEditor::FControlRigTweenModels`  
`class FControlRigTweenModels : public TweeningUtilsEditor::FTweenModelArray`  
_L16-21_
- inherits: `TweeningUtilsEditor::FTweenModelArray`
- desc: Knows of the tween models used in control rig.
- L20 _public prototype_ `explicit FControlRigTweenModels(const TAttribute<TWeakPtr<ISequencer>>& InSequencerAttr, const TSharedRef<FControlRigEditMode>& InOwningEditMode);`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace ControlRigEditor` (scope `UE`)

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/EditMode/Tween/TweenLogic.h` (Private)


#### struct `UE::ControlRigEditor::FTweenLogicWidgets`  
`struct FTweenLogicWidgets`  
_L17-25_
- L19 _public member_ `TSharedPtr<SWidget> RootWidget;`
- L20 _public member_ `TSharedPtr<TweeningUtilsEditor::STweenSlider> TweenSlider;`
- L22 _public function_ `explicit FTweenLogicWidgets(TSharedPtr<SWidget> InRootWidget, TSharedPtr<TweeningUtilsEditor::STweenSlider> InTweenSlider) : RootWidget(MoveTemp(InRootWidget)), TweenSlider(MoveTemp(InTweenSlider))`

#### class `UE::ControlRigEditor::FTweenLogic`  
`class FTweenLogic`  
_L28-49_
- desc: Creates the tweening model specific to ControlRig and provides an interface for interacting with it.
- L32 _public prototype_ `explicit FTweenLogic(const TAttribute<TWeakPtr<ISequencer>>& InSequencerAttr, const TSharedRef<FControlRigEditMode>& InOwningEditMode);`
- L35 _public prototype_ `FTweenLogicWidgets MakeWidget() const;` — Constructs the content for the viewport tweening widget.
- L37 _public function_ `TweeningUtilsEditor::FTweenControllers& GetControllers()`
- L42 _private member_ `const TSharedRef<FUICommandList> CommandList;` — Owning control rig's command list.
- L45 _private member_ `const TSharedRef<FControlRigTweenModels> TweenModels;` — Holds the used tweening functions and info about how to display them in UI.
- L48 _private member_ `TweeningUtilsEditor::FTweenControllers Controllers;` — Common functionality that should be shared consistent with other editor modules, such as Curve Editor.

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace ControlRigEditor` (scope `UE`)

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/EditMode/Tween/TweenOverlayManager.h` (Private)


#### class `UE::ControlRigEditor::FTweenOverlayManager`  
`class FTweenOverlayManager : public FNoncopyable`  
_L34-79_
- inherits: `FNoncopyable`
- desc: Manages all logic around the tween overlay widget. This class is responsible for holding any Control Rig specific state and injects it into a FFlyoutOverlayManager, which handles all the UI logic for docking the tween slider to the viewport, etc. ========== Command precedence ========== Both FControlRigEditModeCommands::SummonTweenWidget and FTweeningUtilsCommands::DragAnimSliderTool are bound to U by default. While the flyout widget is visible, DragAnimSliderTool takes precedence. This is achieved by binding: - DragAnimSliderTool to FControlRigEditModeToolkit::GetCommandBindings(). - SummonTweenWidget to FControlRigEditMode::GetCommandBindings(). Sequence of input events in the engine is: 1. FEditorModeTools::InputKey, which invokes FControlRigEditModeToolkit::GetCommandBindings()->ProcessCommandBindings 2. SEditorViewport::OnKeyDown 3. SLevelViewport::OnKeyDown 4. SLevelEditor::OnKeyDown, which invokes FControlRigEditModeToolkit::ProcessCommandBindings There are other commands bound to e.g. shift+U in SEditorViewport, so it's important the toolkit's tween commands are processed first. So they must go into FControlRigEditModeToolkit::GetCommandBindings(). This would be fixed if FEditorModeTools::InputKey called FControlRigEditModeToolkit::ProcessCommandBindings instead.
- L38 _public prototype_ `explicit FTweenOverlayManager( const TSharedRef<IToolkitHost>& InToolkitHost, const TSharedRef<FUICommandList>& InToolkitCommandList, const TSharedRef<FControlRigEditMode>& InOwningEditMode );`
- L44 _public function_ `void ToggleVisibility()`
- L45 _public function_ `void ShowWidget()`
- L46 _public function_ `void HideWidget()`
- L47 _public function_ `bool IsShowingWidget() const`
- L52 _private member_ `FTweenLogic TweenControllers;` — Manages logic for the tweening widget.
- L55 _private member_ `const FTweenLogicWidgets WidgetHierarchy;` — The widget hierarchy in the flyout widget manager.
- L57 _private member_ `FFlyoutOverlayManager FlyoutWidgetManager;` — Contains the tween slider widget. Allows it to be dragged around, commands, etc.
- L59 _private member_ `FFlyoutCommandBinder FlyoutCommands;` — Process the command bindings that affect FlyoutWidgetManager.
- L62 _private member_ `TSharedPtr<FFlyoutTemporaryPositionOverride> IndirectSlidePositionOverride;` — Set while the user is sliding using U+LMB.
- L65 _private prototype_ `FVector2f ComputeOffsetFromWidgetCenterToSliderPosition() const;` — @return Computes the offset the widget should have from the mouse cursor so the center of the slider is under it.
- L68 _private prototype_ `void OnStartIndirectSliding();` — When using U+LMB, show move the tween overlay to the mouse.
- L69 _private prototype_ `void OnStopIndirectSliding();`
- L75 _private prototype_ `void OnVisibilityChanged(bool bIsVisible);` — While invisible, gives precedence to SummonTweenWidget by deactivating indirect sliding (DragAnimSliderTool, U+LMB) because by default both commands are bound to the same hotkey.
- L78 _private prototype_ `void OnTweenCommandInvoked();` — If the widget is hidden, temporarily shows the widget and snaps it to the cursor until the user moves the mouse away.

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace ControlRigEditor` (scope `UE`)

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/Editor/Constraints/ConstraintCreationOptions.h` (Private)


#### class `UConstraintCreationOptions`  
`class UConstraintCreationOptions : public UObject`  
_L15-24_
- reflection: `UCLASS(Blueprintable)`
- inherits: `UObject`
- L23 _public member_ `FSequencerCreationOptions SequencerOptions;` — `UPROPERTY(EditAnywhere, Category=Options)` — Creation options related to sequencer.

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/Editor/Constraints/SConstraintsWidget.h` (Private)


#### struct `FConstrainable`  
`struct FConstrainable`  
_L28-33_
- desc: FConstrainable is a UObject/Socket wrapper used to represent the future transformable handle
- L30 _public member_ `TWeakObjectPtr<AActor> Actor = nullptr;`
- L31 _public member_ `TWeakObjectPtr<UObject> Object = nullptr;`
- L32 _public member_ `FName Socket = NAME_None;`

#### class `FConstraintInfo`  
`class FConstraintInfo`  
_L40-51_
- L43 _public prototype_ `static const FSlateBrush* GetBrush(uint8 InType);`
- L44 _public prototype_ `static int8 GetType(UClass* InClass);`
- L45 _public prototype_ `static UTickableTransformConstraint* GetConfigurable(ETransformConstraintType InType);`
- L48 _private prototype_ `static const TArray< const FSlateBrush* >& GetBrushes();`
- L49 _private prototype_ `static const TMap< UClass*, ETransformConstraintType >& GetConstraintToType();`
- L50 _private prototype_ `static const TArray< UTickableTransformConstraint* >& GetConfigurableConstraints();`

#### struct `FDroppableConstraintItem`  
`struct FDroppableConstraintItem`  
_L66-80_
- L68 _public function_ `static TSharedRef<FDroppableConstraintItem> Make(ETransformConstraintType InType)`
- L73 _public member_ `ETransformConstraintType Type = ETransformConstraintType::Parent;`
- L76 _private function_ `FDroppableConstraintItem(ETransformConstraintType InType) : Type(InType)`
- L79 _private prototype_ `FDroppableConstraintItem() = default;`

#### class `SConstraintMenuEntry`  
`class SConstraintMenuEntry : public SCompoundWidget`  
_L86-142_
- inherits: `SCompoundWidget`
- L89 _public function_ `SLATE_BEGIN_ARGS(SConstraintMenuEntry)`
- L91 _public prototype_ `SLATE_EVENT(FOnConstraintCreated, OnConstraintCreated) SLATE_EVENT(FOnGetConstrainable, OnGetParent) SLATE_ARGUMENT(TWeakPtr<ISequencer>, WeakSequencer) SLATE_END_ARGS() void Construct( const FArguments& InArgs, const ETransformConstraintType& InType);`
- L103 _public prototype_ `virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;` — SWidget interface
- L104 _public prototype_ `virtual FReply OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L105 _public prototype_ `virtual FReply OnDragDetected(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L111 _private prototype_ `FReply CreateFromSelectionOrPicker(const bool bUseDefault) const;` — Uses the current selected parent or pick a new one if none has been set.
- L114 _private prototype_ `FReply CreateSelectionPicker(const bool bUseDefault) const;` — Activates the ActorPickerMode to pick a parent in the viewport.
- L117 _private member_ `FOnConstraintCreated OnConstraintCreated;` — Delegate triggered when a new constraint has been created.
- L120 _private member_ `FOnGetConstrainable OnGetParent;` — Delegate to get constrainable parent data.
- L123 _private prototype_ `TSharedRef<SWidget> GenerateConstraintDefaultWidget();` — Creates a widget to edit the constraint default properties.
- L126 _private prototype_ `static void OnParentPicked( AActor* InParent, const FOnConstraintCreated& InDelegate, const ETransformConstraintType InConstraintType, const bool bUseDefault);` — Creates the constraint between the current selection and the picked actor.
- L133 _private member_ `TSharedPtr<const FDroppableConstraintItem> ConstraintItem;` — TSharedPtr to the tree item.
- L135 _private member_ `ETransformConstraintType ConstraintType = ETransformConstraintType::Parent;`
- L138 _private member_ `bool bIsPressed = false;` — State on the item.
- L141 _private member_ `TObjectPtr<UTickableConstraint> ConfigurableConstraint = nullptr;` — object ptr to the configurable constraint.

#### class `FEditableConstraintItem`  
`class FEditableConstraintItem`  
_L152-188_
- L155 _public function_ `static TSharedRef<FEditableConstraintItem> Make( UTickableConstraint* InConstraint, ETransformConstraintType InType)`
- L162 _public member_ `TWeakObjectPtr<UTickableConstraint> Constraint = nullptr;`
- L163 _public member_ `ETransformConstraintType Type = ETransformConstraintType::Parent;`
- L165 _public function_ `FName GetName() const`
- L173 _public function_ `FString GetLabel() const`
- L183 _private function_ `FEditableConstraintItem(UTickableConstraint* InConstraint, ETransformConstraintType InType) : Constraint(InConstraint) , Type(InType)`
- L187 _private function_ `FEditableConstraintItem()`

#### class `SEditableConstraintItem`  
`class SEditableConstraintItem : public SCompoundWidget`  
_L194-210_
- inherits: `SCompoundWidget`
- L197 _public function_ `SLATE_BEGIN_ARGS(SEditableConstraintItem)`
- L198 _public prototype_ `SLATE_END_ARGS() void Construct( const FArguments& InArgs, const TSharedPtr<FEditableConstraintItem>& InItem, TSharedPtr<SConstraintsEditionWidget> InConstraintsWidget);`
- L208 _private member_ `TSharedPtr<FEditableConstraintItem> ConstraintItem;` — TSharedPtr to the tree item.
- L209 _private member_ `TWeakPtr<SConstraintsEditionWidget> ConstraintsWidget;`

#### class `FBaseConstraintListWidget`  
`class FBaseConstraintListWidget : public FEditorUndoClient`  
_L216-284_
- inherits: `FEditorUndoClient`
- L234 _public prototype_ `virtual void PostUndo(bool bSuccess);` — FEditorUndoClient interface
- L235 _public prototype_ `virtual void PostRedo(bool bSuccess);`
- L239 _public prototype_ `virtual void InvalidateConstraintList();` — Invalidates the constraint list for further rebuild.
- L242 _public prototype_ `virtual int32 RefreshConstraintList();` — Rebuild the constraint list based on the current selection.
- L245 _public prototype_ `void OnActorSelectionChanged(const TArray<UObject*>& NewSelection, bool bForceRefresh);` — Triggers a constraint list invalidation when selection in the level viewport.
- L248 _public function_ `EShowConstraints GetShowConstraints() const` — Which constraints to show
- L249 _public function_ `void SetShowConstraints(EShowConstraints InShowConstraints)`
- L257 _public prototype_ `FText GetShowConstraintsText(EShowConstraints Index) const;`
- L258 _public prototype_ `FText GetShowConstraintsTooltip(EShowConstraints Index) const;`
- L262 _protected typedef_ `using ItemSharedPtr = TSharedPtr<FEditableConstraintItem>;` — Types
- L263 _protected typedef_ `using ConstraintItemListView = SListView< ItemSharedPtr >;`
- L265 _protected prototype_ `void RegisterNotifications();`
- L266 _protected prototype_ `void UnregisterNotifications();`
- L269 _protected member_ `TSharedPtr< ConstraintItemListView > ListView;` — List view that shows constraint types
- L272 _protected member_ `TArray< ItemSharedPtr > ListItems;` — List of constraint types
- L275 _protected member_ `bool bNeedsRefresh = false;` — Boolean used to handle the items list refresh.
- L277 _protected member_ `FDelegateHandle OnSelectionChangedHandle;`
- L278 _protected member_ `FDelegateHandle ConstraintsNotificationHandle;`
- L282 _public member_ `static EShowConstraints ShowConstraints;`

#### enum `FBaseConstraintListWidget::EShowConstraints`  
`enum class EShowConstraints`  
_L223-229_
- desc: Constraints to show in Widget
- L225 _public enumerator_ `ShowSelected = 0x0`
- L226 _public enumerator_ `ShowLevelSequence = 0x1`
- L227 _public enumerator_ `ShowValid = 0x2`
- L228 _public enumerator_ `ShowAll = 0x3`

#### class `SConstraintsEditionWidget`  
`class SConstraintsEditionWidget : public SCompoundWidget, public FBaseConstraintListWidget`  
_L290-369_
- inherits: `SCompoundWidget,FBaseConstraintListWidget`
- L293 _public function_ `SLATE_BEGIN_ARGS(SConstraintsEditionWidget)`
- L296 _public prototype_ `SLATE_NAMED_SLOT(FArguments, LeftSplitterContent) SLATE_NAMED_SLOT(FArguments, MiddleSplitterContent) SLATE_NAMED_SLOT(FArguments, RightSplitterContent) SLATE_NAMED_SLOT(FArguments, LeftButtonArea) SLATE_END_ARGS() void Construct(const FArguments& InArgs);` — This is a temporary way to allow you to add "rows" above the details for this panel. This will be revisited in 5.8.
- L308 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;` — Override for SWidget::Tick
- L311 _public prototype_ `bool CanMoveUp(const TSharedPtr<FEditableConstraintItem>& Item) const;`
- L312 _public prototype_ `bool CanMoveDown(const TSharedPtr<FEditableConstraintItem>& Item) const;`
- L315 _public prototype_ `void MoveItemUp(const TSharedPtr<FEditableConstraintItem>& Item);`
- L316 _public prototype_ `void MoveItemDown(const TSharedPtr<FEditableConstraintItem>& Item);`
- L319 _public prototype_ `void RemoveItem(const TSharedPtr<FEditableConstraintItem>& Item);`
- L322 _public prototype_ `virtual void InvalidateConstraintList() override;` — FBaseConstraintListWidget overrides
- L325 _public prototype_ `void SequencerChanged(const TWeakPtr<ISequencer>& InNewSequencer);` — Notify from sequencer changed.
- L328 _public prototype_ `void ResetParent();` — Resets the selected parent data.
- L331 _public prototype_ `const FConstrainable& GetParent() const;` — Returns the parent that has been set using the chooser widget.
- L332 _public prototype_ `bool IsParentValid() const;`
- L337 _private prototype_ `void UpdateParent(AActor* InActor);` — Updates the current constrainable parent data.
- L340 _private member_ `FConstrainable ConstrainableParent;` — Constrainable parent data to be sued to create a new constraint.
- L343 _private prototype_ `TSharedRef<SWidget> OnGetParentMenuContent();` — Widgets to set the constrainable parent without using the picker.
- L344 _private prototype_ `TSharedPtr<SComboButton> GetActorChooserWidget();`
- L345 _private prototype_ `TSharedRef<SWidget> GetUseSelectedActorWidget();`
- L346 _private prototype_ `void OnParentMenuOpenChanged(bool bOpened);`
- L349 _private prototype_ `TSharedRef<ITableRow> OnGenerateWidgetForItem(ItemSharedPtr InItem, const TSharedRef<STableViewBase>& OwnerTable);` — Generates a widget for the specified item
- L352 _private typedef_ `using ItemSharedPtr = TSharedPtr<FEditableConstraintItem>;` — Types
- L353 _private typedef_ `using ConstraintItemListView = SListView< ItemSharedPtr >;`
- L356 _private prototype_ `TSharedPtr< SWidget > CreateContextMenu();` — @todo documentation.
- L357 _private prototype_ `void OnItemDoubleClicked(ItemSharedPtr InItem);`
- L359 _private prototype_ `FReply OnBakeClicked();`
- L361 _private prototype_ `void UpdateSequencer();`
- L364 _private member_ `TWeakPtr<ISequencer> WeakSequencer;` — sequencer and it's time
- L365 _private prototype_ `bool SequencerTimeChanged();`
- L366 _private member_ `FQualifiedFrameTime SequencerLastTime;`
- L368 _private member_ `TSharedPtr<SComboButton> ActorSelectionButtons;`

#### class `SConstraintBakeWidget`  
`class SConstraintBakeWidget : public SCompoundWidget, public FBaseConstraintListWidget`  
_L372-409_
- inherits: `SCompoundWidget,FBaseConstraintListWidget`
- desc: Widget allowing baking of constraints
- L376 _public function_ `SLATE_BEGIN_ARGS(SConstraintBakeWidget) : _Sequencer(nullptr)`
- L380 _public prototype_ `SLATE_ARGUMENT(TSharedPtr<ISequencer>, Sequencer) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L384 _public prototype_ `virtual ~SConstraintBakeWidget() override = default;`
- L386 _public prototype_ `FReply OpenDialog(bool bModal = true);`
- L387 _public prototype_ `void CloseDialog();`
- L390 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;` — SWidget overrides
- L393 _public prototype_ `virtual int32 RefreshConstraintList() override;` — FBaseConstraintListWidget overrides
- L396 _private prototype_ `void BakeSelected();`
- L399 _private prototype_ `TSharedRef<ITableRow> OnGenerateWidgetForItem(ItemSharedPtr InItem, const TSharedRef<STableViewBase>& OwnerTable);` — Generates a widget for the specified item
- L401 _private member_ `TSharedPtr<ISequencer> Sequencer;`
- L403 _private member_ `static TOptional<FBakingAnimationKeySettings> BakeConstraintSettings;` — static to be reused
- L405 _private member_ `TSharedPtr < TStructOnScope<FBakingAnimationKeySettings>> Settings;` — structonscope for details panel
- L406 _private member_ `TWeakPtr<SWindow> DialogWindow;`
- L407 _private member_ `TSharedPtr<IStructureDetailsView> DetailsView;`

#### class `SBakeConstraintItem`  
`class SBakeConstraintItem : public SCompoundWidget`  
_L415-431_
- inherits: `SCompoundWidget`
- L418 _public function_ `SLATE_BEGIN_ARGS(SBakeConstraintItem)`
- L419 _public prototype_ `SLATE_END_ARGS() void Construct( const FArguments& InArgs, const TSharedPtr<FEditableConstraintItem>& InItem, TSharedPtr<SConstraintBakeWidget> InConstraintsWidget);`
- L429 _private member_ `TSharedPtr<FEditableConstraintItem> ConstraintItem;` — TSharedPtr to the tree item.
- L430 _private member_ `TWeakPtr<SConstraintBakeWidget> ConstraintsWidget;`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API CONTROLRIGEDITOR_API`
- L23 _delegate_ `DECLARE_DELEGATE(FOnConstraintCreated);`
- L23 _prototype_ `DECLARE_DELEGATE(FOnConstraintCreated);`
- L34 _delegate_ `DECLARE_DELEGATE_RetVal(FConstrainable, FOnGetConstrainable);`
- L34 _prototype_ `DECLARE_DELEGATE_RetVal(FConstrainable, FOnGetConstrainable);`

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/Editor/ControlRigContextMenuContext.h` (Private)


#### struct `FControlRigRigHierarchyDragAndDropContext`  
`struct FControlRigRigHierarchyDragAndDropContext`  
_L23-40_
- reflection: `USTRUCT(BlueprintType)`
- L27 _public prototype_ `FControlRigRigHierarchyDragAndDropContext() = default;`
- L29 _public function_ `FControlRigRigHierarchyDragAndDropContext(const TArray<FRigHierarchyKey> InDraggedHierarchyKeys, FRigHierarchyKey InTargetHierarchyKey) : DraggedHierarchyKeys(InDraggedHierarchyKeys) , TargetHierarchyKey(InTargetHierarchyKey)`
- L36 _public member_ `TArray<FRigHierarchyKey> DraggedHierarchyKeys;` — `UPROPERTY(BlueprintReadOnly, Category = ControlRigEditorExtensions)`
- L39 _public member_ `FRigHierarchyKey TargetHierarchyKey;` — `UPROPERTY(BlueprintReadOnly, Category = ControlRigEditorExtensions)`

#### struct `FControlRigGraphNodeContextMenuContext`  
`struct FControlRigGraphNodeContextMenuContext`  
_L43-72_
- reflection: `USTRUCT(BlueprintType)`
- L47 _public function_ `FControlRigGraphNodeContextMenuContext() : Graph(nullptr) , Node(nullptr) , Pin(nullptr)`
- L54 _public function_ `FControlRigGraphNodeContextMenuContext(TObjectPtr<const URigVMGraph> InGraph, TObjectPtr<const URigVMNode> InNode, TObjectPtr<const URigVMPin> InPin) : Graph(InGraph) , Node(InNode) , Pin(InPin)`
- L63 _public member_ `TObjectPtr<const URigVMGraph> Graph;` — `UPROPERTY(BlueprintReadOnly, Category = ControlRigEditorExtensions)` — The graph associated with this context.
- L67 _public member_ `TObjectPtr<const URigVMNode> Node;` — `UPROPERTY(BlueprintReadOnly, Category = ControlRigEditorExtensions)` — The node associated with this context.
- L71 _public member_ `TObjectPtr<const URigVMPin> Pin;` — `UPROPERTY(BlueprintReadOnly, Category = ControlRigEditorExtensions)` — The pin associated with this context; may be NULL when over a node.

#### struct `FControlRigRigHierarchyToGraphDragAndDropContext`  
`struct FControlRigRigHierarchyToGraphDragAndDropContext`  
_L75-95_
- reflection: `USTRUCT(BlueprintType)`
- L79 _public prototype_ `FControlRigRigHierarchyToGraphDragAndDropContext() = default;`
- L81 _public function_ `FControlRigRigHierarchyToGraphDragAndDropContext(const TArray<FRigHierarchyKey>& InDraggedHierarchyKeys, UEdGraph* InGraph, const FVector2D& InNodePosition) :DraggedHierarchyKeys(InDraggedHierarchyKeys) ,Graph(InGraph) ,NodePosition(InNodePosition)`
- L88 _public member_ `TArray<FRigHierarchyKey> DraggedHierarchyKeys;` — `UPROPERTY(BlueprintReadOnly, Category = ControlRigEditorExtensions)`
- L90 _public member_ `TWeakObjectPtr<UEdGraph> Graph;`
- L92 _public member_ `FVector2D NodePosition;`
- L94 _public prototype_ `FString GetSectionTitle() const;`

#### struct `FControlRigMenuSpecificContext`  
`struct FControlRigMenuSpecificContext`  
_L97-108_
- L99 _public member_ `TWeakPtr<SRigHierarchy> RigHierarchyPanel;`
- L101 _public member_ `FControlRigRigHierarchyDragAndDropContext RigHierarchyDragAndDropContext;`
- L103 _public member_ `TWeakPtr<SModularRigHierarchy> ModularRigModelPanel;`
- L105 _public member_ `FControlRigGraphNodeContextMenuContext GraphNodeContextMenuContext;`
- L107 _public member_ `FControlRigRigHierarchyToGraphDragAndDropContext RigHierarchyToGraphDragAndDropContext;`

#### class `UControlRigContextMenuContext`  
`class UControlRigContextMenuContext : public UObject`  
_L111-160_
- reflection: `UCLASS(BlueprintType)`
- inherits: `UObject`
- L121 _public prototype_ `void Init(TWeakPtr<IControlRigBaseEditor> InControlRigEditor, const FControlRigMenuSpecificContext& InMenuSpecificContext = FControlRigMenuSpecificContext());` — Initialize the Context @param InControlRigEditor 	    The Control Rig Editor hosting the menus @param InMenuSpecificContext 	Additional context for specific menus
- L125 _public function_ `UControlRigBlueprint* GetControlRigBlueprint() const` — `UFUNCTION(BlueprintCallable, Category = ControlRigEditorExtensions, meta=(DeprecatedFunction, DeprecationMessage="Function has been deprecated, please rely on GetControlRigAssetInterface instead."))` — Get the control rig blueprint that we are editing
- L128 _public prototype_ `TScriptInterface<IControlRigEditorAssetInterface> GetControlRigAssetInterface() const;` — `UFUNCTION(BlueprintCallable, Category = ControlRigEditorExtensions)`
- L132 _public prototype_ `UControlRig* GetControlRig() const;` — `UFUNCTION(BlueprintCallable, Category = ControlRigEditorExtensions)` — Get the active control rig instance in the viewport
- L136 _public prototype_ `bool IsAltDown() const;` — `UFUNCTION(BlueprintCallable, Category = ControlRigEditorExtensions)` — Returns true if either alt key is down
- L140 _public prototype_ `FControlRigRigHierarchyDragAndDropContext GetRigHierarchyDragAndDropContext();` — `UFUNCTION(BlueprintCallable, Category = ControlRigEditorExtensions)` — Returns context for a drag & drop action that contains source and target element keys
- L144 _public prototype_ `FControlRigGraphNodeContextMenuContext GetGraphNodeContextMenuContext();` — `UFUNCTION(BlueprintCallable, Category = ControlRigEditorExtensions)` — Returns context for graph node context menu
- L148 _public prototype_ `FControlRigRigHierarchyToGraphDragAndDropContext GetRigHierarchyToGraphDragAndDropContext();` — `UFUNCTION(BlueprintCallable, Category = ControlRigEditorExtensions)` — Returns context for the menu that shows up when drag and drop from Rig Hierarchy to the Rig Graph
- L150 _public prototype_ `SRigHierarchy* GetRigHierarchyPanel() const;`
- L152 _public prototype_ `SModularRigHierarchy* GetModularRigModelPanel() const;`
- L154 _public prototype_ `IControlRigBaseEditor* GetControlRigEditor() const;`
- L157 _private member_ `TWeakPtr<IControlRigBaseEditor> WeakControlRigEditor;`
- L159 _private member_ `FControlRigMenuSpecificContext MenuSpecificContext;`

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/Editor/ControlRigEditor.h` (Private)


#### struct `FControlRigEditorModes`  
`struct FControlRigEditorModes`  
_L41-61_
- L44 _public member_ `static const FName ControlRigEditorMode;` — Mode constants
- L45 _public function_ `static FText GetLocalizedMode(const FName InMode)`
- L60 _private function_ `FControlRigEditorModes()`

#### class `IControlRigBaseEditor`  
`class IControlRigBaseEditor`  
_L63-185_
- L66 _public prototype_ `virtual TSharedRef<IRigVMEditor> SharedRigVMEditorRef() = 0;`
- L67 _public prototype_ `virtual TSharedRef<IControlRigBaseEditor> SharedControlRigEditorRef() = 0;`
- L68 _public prototype_ `virtual TSharedRef<FControlRigBaseEditor> SharedRef() = 0;`
- L69 _public prototype_ `virtual TSharedRef<const IRigVMEditor> SharedRigVMEditorRef() const = 0;`
- L72 _public prototype_ `virtual UControlRigBlueprint* GetControlRigBlueprint() const = 0;` — `UE_DEPRECATED(5.7, "Use GetControlRigAssetInterface instead.")`
- L73 _public prototype_ `virtual FControlRigAssetInterfacePtr GetControlRigAssetInterface() const = 0;`
- L74 _public prototype_ `virtual TSharedPtr<FAssetEditorToolkit> GetHostingApp() = 0;`
- L75 _public prototype_ `virtual UControlRig* GetControlRig() const = 0;`
- L77 _public prototype_ `virtual TSharedRef<IPersonaToolkit> GetPersonaToolkit() const = 0;`
- L79 _public prototype_ `virtual void Compile() = 0;`
- L81 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FControlRigEditorClosed, IControlRigBaseEditor*, FControlRigAssetInterfacePtr);`
- L82 _public prototype_ `virtual FControlRigEditorClosed& OnEditorClosed() = 0;`
- L83 _public prototype_ `virtual FPersonaViewportKeyDownDelegate& GetKeyDownDelegate() = 0;`
- L84 _public prototype_ `virtual FOnGetContextMenu& OnGetViewportContextMenu() = 0;`
- L85 _public prototype_ `virtual FNewMenuCommandsDelegate& OnViewportContextMenuCommands() = 0;`
- L86 _public prototype_ `virtual FSimpleMulticastDelegate& OnRequestNavigateToConnectorWarning() = 0;`
- L87 _public prototype_ `virtual FControlRigEditorEditMode* GetEditMode() const = 0;`
- L88 _public prototype_ `virtual int32 GetEventQueueComboValue() const = 0;`
- L89 _public prototype_ `virtual void OnHierarchyChanged() = 0;`
- L91 _public prototype_ `virtual void SetDetailViewForRigElements() = 0;`
- L92 _public prototype_ `virtual void SetDetailViewForRigElements(const TArray<FRigHierarchyKey>& InKeys) = 0;`
- L93 _public prototype_ `virtual void ClearDetailObject(bool bChangeUISelectionState = true) = 0;`
- L94 _public prototype_ `virtual void FindReferencesOfItem(const FRigHierarchyKey& InKey) = 0;`
- L96 _public prototype_ `virtual int32 GetRigHierarchyTabCount() const = 0;`
- L97 _public prototype_ `virtual void IncreaseRigHierarchyTabCount() = 0;`
- L98 _public prototype_ `virtual void DecreaseRigHierarchyTabCount() = 0;`
- L100 _public prototype_ `virtual int32 GetModularRigHierarchyTabCount() const = 0;`
- L101 _public prototype_ `virtual void IncreaseModularRigHierarchyTabCount() = 0;`
- L102 _public prototype_ `virtual void DecreaseModularRigHierarchyTabCount() = 0;`
- L104 _public prototype_ `virtual bool& GetSuspendDetailsPanelRefreshFlag() = 0;`
- L105 _public prototype_ `virtual EControlRigReplayPlaybackMode GetReplayPlaybackMode() const = 0;`
- L106 _public prototype_ `virtual TArray<FName> GetSelectedModules() const = 0;`
- L108 _public prototype_ `virtual void RefreshDetailView() = 0;`
- L109 _public prototype_ `virtual FVector2D ComputePersonaProjectedScreenPos(const FVector& InWorldPos, bool bClampToScreenRectangle = false) = 0;`
- L110 _public prototype_ `virtual void SetDetailViewForRigModules(const TArray<FName> InModuleNames) = 0;`
- L112 _public prototype_ `virtual UAnimPreviewInstance* GetPreviewInstance() const = 0;`
- L113 _public prototype_ `virtual void SetPreviewInstance(UAnimPreviewInstance* InPreviewInstance) = 0;`
- L115 _public prototype_ `virtual void RemoveBoneModification(FName BoneName) = 0;`
- L116 _public prototype_ `virtual URigHierarchy* GetHierarchyBeingDebugged() const = 0;`
- L118 _public prototype_ `virtual void FilterDraggedKeys(TArray<FRigElementKey>& Keys, bool bRemoveNameSpace) = 0;`
- L119 _public prototype_ `virtual URigVMController* GetFocusedController() const = 0;`
- L123 _protected prototype_ `virtual void InitRigVMEditorSuper(const EToolkitMode::Type Mode, const TSharedPtr< class IToolkitHost >& InitToolkitHost, FRigVMEditorAssetInterfacePtr InRigVMBlueprint) = 0;`
- L125 _protected prototype_ `virtual bool IsControlRigLegacyEditor() const = 0;`
- L126 _protected prototype_ `virtual FRigVMEditorAssetInterfacePtr GetRigVMAssetInterface() const = 0;`
- L127 _protected prototype_ `virtual URigVMHost* GetRigVMHost() const = 0;`
- L128 _protected prototype_ `virtual bool IsEditorInitialized() const = 0;`
- L130 _protected prototype_ `virtual TSharedRef<FUICommandList> GetToolkitCommands() = 0;`
- L131 _protected prototype_ `virtual FPreviewScene* GetPreviewScene() = 0;`
- L132 _protected prototype_ `virtual bool IsDetailsPanelRefreshSuspended() const = 0;`
- L133 _protected prototype_ `virtual TArray<TWeakObjectPtr<UObject>> GetSelectedObjects() const = 0;`
- L134 _protected prototype_ `virtual UClass* GetDetailWrapperClass() const = 0;`
- L135 _protected prototype_ `virtual void OnWrappedPropertyChangedChainEvent(URigVMDetailsViewWrapperObject* InWrapperObject, const FString& InPropertyPath, FPropertyChangedChainEvent& InPropertyChangedChainEvent) = 0;`
- L136 _protected prototype_ `virtual void SetDetailObjects(const TArray<UObject*>& InObjects) = 0;`
- L137 _protected prototype_ `virtual void SetDetailObjectsSuper(const TArray<UObject*>& InObjects) = 0;`
- L138 _protected prototype_ `virtual void SetDetailObjectFilter(TSharedPtr<FDetailsViewObjectFilter> InObjectFilter) = 0;`
- L139 _protected prototype_ `virtual bool DetailViewShowsStruct(UScriptStruct* InStruct) const = 0;`
- L140 _protected prototype_ `virtual TSharedPtr<class SWidget> GetInspector() const = 0;`
- L141 _protected prototype_ `virtual TArray<FName> GetEventQueue() const = 0;`
- L142 _protected prototype_ `virtual void SummonSearchUI(bool bSetFindWithinBlueprint, FString NewSearchTerms = FString(), bool bSelectFirstResult = false) = 0;`
- L143 _protected prototype_ `virtual const TArray< UObject* >* GetObjectsCurrentlyBeingEdited() const = 0;`
- L144 _protected prototype_ `virtual void UpdateRigVMHost() = 0;`
- L145 _protected prototype_ `virtual void RefreshDetailViewSuper() = 0;`
- L146 _protected prototype_ `virtual void CacheNameLists() = 0;`
- L147 _protected prototype_ `virtual FEditorModeTools& GetEditorModeManagerImpl() const = 0;`
- L148 _protected prototype_ `virtual const FName GetEditorModeNameImpl() const = 0;`
- L149 _protected prototype_ `virtual URigVMGraph* GetFocusedModel() const = 0;`
- L150 _protected prototype_ `virtual UObject* GetOuterForHostSuper() const = 0;`
- L151 _protected prototype_ `virtual void CompileSuper() = 0;`
- L152 _protected prototype_ `virtual void HandleModifiedEventSuper(ERigVMGraphNotifType InNotifType, URigVMGraph* InGraph, UObject* InSubject) = 0;`
- L153 _protected prototype_ `virtual void OnCreateGraphEditorCommandsSuper(TSharedPtr<FUICommandList> GraphEditorCommandsList) = 0;`
- L154 _protected prototype_ `virtual void HandleVMCompiledEventSuper(UObject* InCompiledObject, URigVM* InVM, FRigVMExtendedExecuteContext& InContext) = 0;`
- L155 _protected prototype_ `virtual FReply OnViewportDropSuper(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) = 0;`
- L156 _protected prototype_ `virtual void FillToolbarSuper(FToolBarBuilder& ToolbarBuilder, bool bEndSection = true) = 0;`
- L157 _protected prototype_ `virtual TArray<FName> GetLastEventQueue() const = 0;`
- L158 _protected prototype_ `virtual int32 GetEventQueueComboValueSuper() const = 0;`
- L159 _protected prototype_ `virtual void HandleSetObjectBeingDebuggedSuper(UObject* InObject) = 0;`
- L160 _protected prototype_ `virtual void SetEventQueue(TArray<FName> InEventQueue, bool bCompile) = 0;`
- L161 _protected prototype_ `virtual void SetEventQueueSuper(TArray<FName> InEventQueue, bool bCompile) = 0;`
- L162 _protected prototype_ `virtual void SetEventQueueSuper(TArray<FName> InEventQueue) = 0;`
- L163 _protected prototype_ `virtual void SaveAsset_ExecuteSuper() = 0;`
- L164 _protected prototype_ `virtual void SaveAssetAs_ExecuteSuper() = 0;`
- L165 _protected prototype_ `virtual FReply OnSpawnGraphNodeByShortcutSuper(FInputChord InChord, const FVector2f& InPosition, UEdGraph* InGraph) = 0;`
- L166 _protected prototype_ `virtual void HandleVMExecutedEventSuper(URigVMHost* InHost, const FName& InEventName) = 0;`
- L167 _protected prototype_ `virtual void SetEditorModeManager(TSharedPtr<FEditorModeTools> InManager) = 0;`
- L168 _protected prototype_ `virtual void TickSuper(float DeltaTime) = 0;`
- L169 _protected prototype_ `virtual void UpdateRigVMHostSuper() = 0;`
- L170 _protected prototype_ `virtual void CacheNameListsSuper() = 0;`
- L171 _protected prototype_ `virtual void OnFinishedChangingPropertiesSuper(const FPropertyChangedEvent& PropertyChangedEvent) = 0;`
- L172 _protected prototype_ `virtual void OnWrappedPropertyChangedChainEventSuper(URigVMDetailsViewWrapperObject* InWrapperObject, const FString& InPropertyPath, FPropertyChangedChainEvent& InPropertyChangedChainEvent) = 0;`
- L173 _protected prototype_ `virtual const TArray<TStrongObjectPtr<URigVMDetailsViewWrapperObject>>& GetWrapperObjects() const = 0;`
- L174 _protected prototype_ `virtual void BindCommandsSuper() = 0;`
- L175 _protected prototype_ `virtual void UnbindCommandsSuper() = 0;`
- L176 _protected prototype_ `virtual FMenuBuilder GenerateBulkEditMenuSuper() = 0;`
- L177 _protected prototype_ `virtual TWeakPtr<class SGraphEditor> GetFocusedGraphEd() const = 0;`
- L178 _protected prototype_ `virtual void OnGraphNodeDropToPerformSuper(TSharedPtr<FDragDropOperation> InDragDropOp, UEdGraph* InGraph, const FVector2f& InNodePosition, const FVector2f& InScreenPosition) = 0;`
- L179 _protected prototype_ `virtual void HandleRefreshEditorFromBlueprintSuper(FRigVMEditorAssetInterfacePtr InBlueprint) = 0;`
- L180 _protected prototype_ `virtual void OnGraphNodeDropToPerform(TSharedPtr<FDragDropOperation> InDragDropOp, UEdGraph* InGraph, const FVector2f& InNodePosition, const FVector2f& InScreenPosition) = 0;`
- L182 _protected prototype_ `virtual void OnCloseSuper() = 0;`

#### class `FControlRigBaseEditor`  
`class FControlRigBaseEditor : public IControlRigBaseEditor`  
_L187-585_
- inherits: `IControlRigBaseEditor`
- L190 _public prototype_ `static FControlRigBaseEditor* GetFromAssetEditorInstance(IAssetEditorInstance* Instance);`
- L191 _public function_ `virtual TSharedRef<FControlRigBaseEditor> SharedRef() override`
- L195 _public prototype_ `virtual UControlRigBlueprint* GetControlRigBlueprint() const override;` — `UE_DEPRECATED(5.7, "Use GetControlRigAssetInterface instead")` — Gets the Control Rig Blueprint being edited/viewed
- L196 _public prototype_ `virtual FControlRigAssetInterfacePtr GetControlRigAssetInterface() const override;`
- L199 _protected prototype_ `void InitRigVMEditorImpl(const EToolkitMode::Type Mode, const TSharedPtr< class IToolkitHost >& InitToolkitHost, FRigVMEditorAssetInterfacePtr InRigVMBlueprint);`
- L201 _protected prototype_ `virtual const FName GetEditorAppNameImpl() const;`
- L202 _protected prototype_ `virtual const FName GetEditorModeNameImpl() const;`
- L203 _protected prototype_ `virtual const FSlateBrush* GetDefaultTabIconImpl() const;`
- L206 _protected prototype_ `FControlRigBaseEditor();`
- L207 _protected prototype_ `virtual ~FControlRigBaseEditor() = default;`
- L209 _protected prototype_ `virtual UObject* GetOuterForHostImpl() const;`
- L211 _protected prototype_ `virtual UClass* GetDetailWrapperClassImpl() const;`
- L212 _protected prototype_ `virtual void CompileBaseImpl();`
- L213 _protected prototype_ `virtual void HandleModifiedEventImpl(ERigVMGraphNotifType InNotifType, URigVMGraph* InGraph, UObject* InSubject);`
- L214 _protected prototype_ `virtual void OnCreateGraphEditorCommandsImpl(TSharedPtr<FUICommandList> GraphEditorCommandsList);`
- L215 _protected prototype_ `virtual void HandleVMCompiledEventImpl(UObject* InCompiledObject, URigVM* InVM, FRigVMExtendedExecuteContext& InContext);`
- L216 _protected function_ `virtual bool ShouldOpenGraphByDefaultImpl() const`
- L217 _protected prototype_ `virtual FReply OnViewportDropImpl(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent);`
- L220 _protected prototype_ `virtual void CreateEmptyGraphContentImpl(URigVMController* InController);` — allows the editor to fill an empty graph
- L222 _protected function_ `virtual int32 GetRigHierarchyTabCount() const override`
- L223 _protected function_ `virtual void IncreaseRigHierarchyTabCount() override`
- L224 _protected function_ `virtual void DecreaseRigHierarchyTabCount() override`
- L225 _protected function_ `virtual int32 GetModularRigHierarchyTabCount() const override`
- L226 _protected function_ `virtual void IncreaseModularRigHierarchyTabCount() override`
- L227 _protected function_ `virtual void DecreaseModularRigHierarchyTabCount() override`
- L229 _protected prototype_ `bool IsModularRig() const;`
- L230 _protected prototype_ `bool IsRigModule() const;`
- L235 _protected prototype_ `virtual FName GetToolkitFNameImpl() const;` — IToolkit Interface
- L236 _protected prototype_ `virtual FText GetBaseToolkitNameImpl() const;`
- L237 _protected prototype_ `virtual FString GetWorldCentricTabPrefixImpl() const;`
- L238 _protected function_ `virtual FString GetDocumentationLinkImpl() const`
- L244 _protected prototype_ `virtual FReply OnSpawnGraphNodeByShortcutImpl(FInputChord InChord, const FVector2f& InPosition, UEdGraph* InGraph);` — BlueprintEditor interface
- L246 _protected prototype_ `virtual void PostTransactionImpl(bool bSuccess, const FTransaction* Transaction, bool bIsRedo);`
- L248 _protected prototype_ `void EnsureValidRigElementsInDetailPanel();`
- L251 _protected prototype_ `virtual void TickImpl(float DeltaTime);` — FTickableEditorObject Interface
- L254 _protected prototype_ `virtual UControlRig* GetControlRig() const override;` — returns the hierarchy being debugged
- L257 _protected prototype_ `virtual URigHierarchy* GetHierarchyBeingDebugged() const override;` — returns the hierarchy being debugged
- L259 _protected prototype_ `virtual void SetDetailViewForRigElements() override;`
- L260 _protected prototype_ `virtual void SetDetailViewForRigElements(const TArray<FRigHierarchyKey>& InKeys) override;`
- L261 _protected prototype_ `bool DetailViewShowsAnyRigElement() const;`
- L262 _protected prototype_ `bool DetailViewShowsRigElement(FRigHierarchyKey InKey) const;`
- L263 _protected prototype_ `TArray<FRigHierarchyKey> GetSelectedRigElementsFromDetailView() const;`
- L264 _protected prototype_ `TArray< TWeakObjectPtr<UObject> > GetSelectedObjectsFromDetailView() const;`
- L266 _protected prototype_ `void SetDetailViewForRigModules();`
- L267 _protected prototype_ `virtual void SetDetailViewForRigModules(const TArray<FName> InModuleNames) override;`
- L268 _protected prototype_ `bool DetailViewShowsAnyRigModule() const;`
- L269 _protected prototype_ `bool DetailViewShowsRigModule(FName InModuleName) const;`
- L271 _protected member_ `TArray<FName> ModulesSelected;`
- L272 _protected function_ `virtual TArray<FName> GetSelectedModules() const override`
- L274 _protected prototype_ `virtual void SetDetailObjectsImpl(const TArray<UObject*>& InObjects);`
- L275 _protected prototype_ `virtual void RefreshDetailViewImpl();`
- L277 _protected prototype_ `void CreatePersonaToolKitIfRequired();`
- L281 _public function_ `virtual TSharedRef<IPersonaToolkit> GetPersonaToolkit() const override` — Get the persona toolkit
- L285 _protected prototype_ `virtual FControlRigEditorEditMode* GetEditMode() const override;` — Get the edit mode
- L287 _protected prototype_ `void OnCurveContainerChanged();`
- L289 _protected prototype_ `void OnHierarchyModified(ERigHierarchyNotification InNotif, URigHierarchy* InHierarchy, const FRigNotificationSubject& InSubject);`
- L290 _protected prototype_ `void OnHierarchyModified_AnyThread(ERigHierarchyNotification InNotif, URigHierarchy* InHierarchy, const FRigNotificationSubject& InSubject);`
- L292 _protected prototype_ `void HandleRigTypeChanged(FControlRigAssetInterfacePtr InBlueprint);`
- L294 _protected prototype_ `void HandleModularRigModified(EModularRigNotification InNotification, const FRigModuleReference* InModule);`
- L295 _protected prototype_ `void HandlePostCompileModularRigs(FRigVMEditorAssetInterfacePtr InBlueprint);`
- L296 _protected prototype_ `void SwapModuleWithinAsset();`
- L297 _protected prototype_ `void SwapModuleAcrossProject();`
- L299 _protected member_ `const FName RigHierarchyToGraphDragAndDropMenuName = TEXT("Con`
- L300 _protected prototype_ `void CreateRigHierarchyToGraphDragAndDropMenu() const;`
- L301 _protected prototype_ `virtual void OnGraphNodeDropToPerformImpl(TSharedPtr<FDragDropOperation> InDragDropOp, UEdGraph* InGraph, const FVector2f& InNodePosition, const FVector2f& InScreenPosition);`
- L303 _protected function_ `virtual FPersonaViewportKeyDownDelegate& GetKeyDownDelegate() override`
- L305 _protected function_ `virtual FOnGetContextMenu& OnGetViewportContextMenu() override`
- L306 _protected function_ `virtual FNewMenuCommandsDelegate& OnViewportContextMenuCommands() override`
- L309 _protected function_ `void HandleRequestDirectManipulationPosition() const` — DirectManipulation functionality
- L310 _protected function_ `void HandleRequestDirectManipulationRotation() const`
- L311 _protected function_ `void HandleRequestDirectManipulationScale() const`
- L312 _protected prototype_ `bool HandleRequestDirectManipulation(ERigControlType InControlType) const;`
- L313 _protected prototype_ `bool SetDirectionManipulationSubject(const URigVMUnitNode* InNode);`
- L314 _protected prototype_ `bool IsDirectManipulationEnabled() const;`
- L315 _protected prototype_ `EVisibility GetDirectManipulationVisibility() const;`
- L316 _protected prototype_ `FText GetDirectionManipulationText() const;`
- L317 _protected prototype_ `void OnDirectManipulationChanged(TSharedPtr<FString> NewValue, ESelectInfo::Type SelectInfo);`
- L318 _protected prototype_ `const TArray<FRigDirectManipulationTarget> GetDirectManipulationTargets() const;`
- L319 _protected prototype_ `const TArray<TSharedPtr<FString>>& GetDirectManipulationTargetTextList() const;`
- L320 _protected function_ `bool ClearDirectManipulationSubject()`
- L321 _protected prototype_ `void RefreshDirectManipulationTextList();`
- L322 _protected prototype_ `EVisibility GetPreviewingNodeVisibility() const;`
- L323 _protected prototype_ `void OnPreviewingNodeJumpTo();`
- L324 _protected prototype_ `void OnPreviewingNodeCancel();`
- L327 _protected prototype_ `EVisibility GetConnectorWarningVisibility() const;` — Rig connector functionality
- L328 _protected prototype_ `FText GetConnectorWarningText() const;`
- L329 _protected prototype_ `FReply OnNavigateToConnectorWarning() const;`
- L330 _protected function_ `virtual FSimpleMulticastDelegate& OnRequestNavigateToConnectorWarning() override`
- L332 _protected prototype_ `virtual FVector2D ComputePersonaProjectedScreenPos(const FVector& InWorldPos, bool bClampToScreenRectangle = false) override;`
- L334 _protected prototype_ `virtual void FindReferencesOfItem(const FRigHierarchyKey& InKey) override;`
- L338 _protected prototype_ `virtual void BindCommandsImpl();`
- L339 _protected prototype_ `virtual void UnbindCommandsImpl();`
- L340 _protected prototype_ `virtual FMenuBuilder GenerateBulkEditMenuImpl();`
- L342 _protected prototype_ `virtual void OnHierarchyChanged() override;`
- L344 _protected prototype_ `void SynchronizeViewportBoneSelection();`
- L346 _protected prototype_ `virtual void SaveAsset_ExecuteImpl();`
- L347 _protected prototype_ `virtual void SaveAssetAs_ExecuteImpl();`
- L350 _protected prototype_ `void UpdateBoneModification(FName BoneName, const FTransform& Transform);` — update the cached modification value
- L353 _protected prototype_ `virtual void RemoveBoneModification(FName BoneName) override;` — remove a single bone modification across all instance
- L356 _protected prototype_ `void ResetAllBoneModification();` — reset all bone modification across all instance
- L358 _protected prototype_ `virtual void HandleVMExecutedEventImpl(URigVMHost* InHost, const FName& InEventName);`
- L361 _protected prototype_ `virtual void CreateEditorModeManagerImpl();` — FBaseToolKit overrides
- L364 _protected prototype_ `virtual void FillToolbarImpl(FToolBarBuilder& ToolbarBuilder, bool bEndSection = true);` — Fill the toolbar with content
- L366 _protected prototype_ `virtual TArray<FName> GetDefaultEventQueueImpl() const;`
- L367 _protected prototype_ `virtual void SetEventQueueImpl(TArray<FName> InEventQueue, bool bCompile);`
- L368 _protected prototype_ `virtual int32 GetEventQueueComboValueImpl() const;`
- L369 _protected prototype_ `virtual FText GetEventQueueLabelImpl() const;`
- L370 _protected prototype_ `virtual FSlateIcon GetEventQueueIconImpl(const TArray<FName>& InEventQueue) const;`
- L371 _protected prototype_ `virtual void HandleSetObjectBeingDebuggedImpl(UObject* InObject);`
- L375 _protected prototype_ `void HandlePreviewSceneCreated(const TSharedRef<IPersonaPreviewScene>& InPersonaPreviewScene);` — Handle preview scene setup
- L377 _public prototype_ `void HandleViewportCreated(const TSharedRef<class IPersonaViewport>& InViewport);`
- L381 _protected prototype_ `void SetNextSolveMode();` — `UE_DEPRECATED(5.8, "Instead use SetNextEventQueue")` — Sets the next solve mode, for example Backwards Solve if the last entry in the Queue is ForwardsSolve
- L384 _protected prototype_ `void SetNextEventQueue();` — Sets the next Event Queue, for example Backwards Solve if the last entry in the Queue is ForwardsSolve
- L387 _protected prototype_ `void SetPriorEventQueue();` — Sets the Event Queue that was set prior to the current one
- L390 _protected prototype_ `void ToggleForwardsSolveAndConstruction();` — Toggles between forwards solve and construction
- L392 _protected prototype_ `void HandleToggleControlVisibility();`
- L393 _protected prototype_ `bool AreControlsVisible() const;`
- L394 _protected prototype_ `void HandleToggleControlsAsOverlay();`
- L395 _protected prototype_ `bool AreControlsAsOverlay() const;`
- L396 _protected prototype_ `bool IsToolbarDrawNullsEnabled() const;`
- L397 _protected prototype_ `bool GetToolbarDrawNulls() const;`
- L398 _protected prototype_ `void HandleToggleToolbarDrawNulls();`
- L399 _protected prototype_ `bool IsToolbarDrawSocketsEnabled() const;`
- L400 _protected prototype_ `bool GetToolbarDrawSockets() const;`
- L401 _protected prototype_ `void HandleToggleToolbarDrawSockets();`
- L402 _protected prototype_ `bool GetToolbarDrawAxesOnSelection() const;`
- L403 _protected prototype_ `void HandleToggleToolbarDrawAxesOnSelection();`
- L404 _protected prototype_ `void HandleToggleSchematicViewport();`
- L405 _protected prototype_ `bool IsSchematicViewportActive() const;`
- L406 _protected prototype_ `void HandleToggleSchematicViewportShowEmptySocketsOnly();`
- L407 _protected prototype_ `bool IsSchematicViewportShowEmptySocketsOnlyActive() const;`
- L408 _protected prototype_ `void HandleToggleCompileResetsEventQueue();`
- L409 _protected prototype_ `bool IsToggleCompileResetsEventQueueActive() const;`
- L410 _protected prototype_ `EVisibility GetSchematicOverlayVisibility() const;`
- L412 _protected prototype_ `bool IsRunningForwardSolve() const;`
- L413 _protected prototype_ `void OnRunGraphOnceToggledImpl(bool bRunGraphOnceEnabled);`
- L416 _protected prototype_ `void HandlePreviewMeshChanged(USkeletalMesh* InOldSkeletalMesh, USkeletalMesh* InNewSkeletalMesh);` — Handle switching skeletal meshes
- L419 _protected prototype_ `virtual void UpdateRigVMHostImpl();` — Push a newly compiled/opened control rig to the edit mode
- L420 _protected prototype_ `virtual void UpdateRigVMHost_PreClearOldHostImpl(URigVMHost* InPreviousHost);`
- L423 _protected prototype_ `virtual void CacheNameListsImpl();` — Update the name lists for use in name combo boxes
- L426 _protected prototype_ `void RebindToSkeletalMeshComponent();` — Rebind our anim instance to the preview's skeletal mesh component
- L428 _protected prototype_ `virtual void GenerateEventQueueMenuContentImpl(FMenuBuilder& MenuBuilder);`
- L441 _protected prototype_ `virtual void FilterDraggedKeys(TArray<FRigElementKey>& Keys, bool bRemoveNameSpace) override;`
- L442 _protected prototype_ `void HandleMakeElementGetterSetter(ERigElementGetterSetterType Type, bool bIsGetter, TArray<FRigElementKey> Keys, UEdGraph* Graph, FVector2D NodePosition);`
- L443 _protected prototype_ `void HandleMakeMetadataGetterSetter(const bool bIsGetter, const TArray<FRigElementKey> Keys, UEdGraph* Graph, FVector2D NodePosition);`
- L444 _protected prototype_ `void HandleMakeComponentGetterSetter(bool bIsGetter, TArray<FRigComponentKey> Keys, UEdGraph* Graph, FVector2D NodePosition);`
- L446 _protected prototype_ `void HandleOnControlModified(UControlRig* Subject, FRigControlElement* ControlElement, const FRigControlModifiedContext& Context);`
- L448 _protected prototype_ `virtual void HandleRefreshEditorFromBlueprintImpl(FRigVMEditorAssetInterfacePtr InBlueprint);`
- L450 _protected prototype_ `FText GetReplayAssetName() const;`
- L451 _protected prototype_ `FText GetReplayAssetTooltip() const;`
- L452 _protected prototype_ `bool SetReplayAssetPath(const FString& InAssetPath);`
- L453 _protected prototype_ `TSharedRef<SWidget> GenerateReplayAssetModeMenuContent();`
- L454 _protected prototype_ `TSharedRef<SWidget> GenerateReplayAssetRecordMenuContent();`
- L455 _protected prototype_ `TSharedRef<SWidget> GenerateReplayAssetPlaybackMenuContent();`
- L456 _protected prototype_ `bool RecordReplay(double InRecordingDuration);`
- L457 _protected prototype_ `void ToggleReplay();`
- L460 _protected prototype_ `virtual EControlRigReplayPlaybackMode GetReplayPlaybackMode() const override;`
- L464 _protected member_ `TSharedPtr<IPersonaToolkit> PersonaToolkit;` — Persona toolkit used to support skeletal mesh preview
- L467 _protected member_ `TSharedPtr<IPersonaViewport> PreviewViewport;` — Preview instance inspector widget
- L470 _protected member_ `TSharedPtr<IPersonaPreviewScene> PreviewScene;` — preview scene
- L473 _protected member_ `UAnimPreviewInstance* PreviewInstance;` — preview animation instance
- L474 _protected function_ `virtual UAnimPreviewInstance* GetPreviewInstance() const override`
- L475 _protected function_ `virtual void SetPreviewInstance(UAnimPreviewInstance* InPreviewInstance) override`
- L478 _protected member_ `TSharedPtr<FControlRigSchematicModel> SchematicModel;` — Model for the schematic views
- L481 _protected member_ `FPersonaViewportKeyDownDelegate OnKeyDownDelegate;` — Delegate to deal with key down evens in the viewport / editor
- L484 _protected member_ `FOnGetContextMenu OnGetViewportContextMenuDelegate;` — Delgate to build the context menu for the viewport
- L485 _protected prototype_ `UToolMenu* HandleOnGetViewportContextMenuDelegate();`
- L486 _protected member_ `FNewMenuCommandsDelegate OnViewportContextMenuCommandsDelegate;`
- L487 _protected prototype_ `TSharedPtr<FUICommandList> HandleOnViewportContextMenuCommandsDelegate();`
- L490 _protected prototype_ `FTransform GetRigElementTransform(const FRigElementKey& InElement, bool bLocal, bool bOnDebugInstance) const;` — Bone Selection related
- L491 _protected prototype_ `void SetRigElementTransform(const FRigElementKey& InElement, const FTransform& InTransform, bool bLocal);`
- L494 _protected prototype_ `virtual void OnFinishedChangingPropertiesImpl(const FPropertyChangedEvent& PropertyChangedEvent);` — delegate for changing property
- L495 _protected prototype_ `virtual void OnWrappedPropertyChangedChainEventImpl(URigVMDetailsViewWrapperObject* InWrapperObject, const FString& InPropertyPath, FPropertyChangedChainEvent& InPropertyChangedChainEvent);`
- L497 _protected member_ `URigVMController* ActiveController;`
- L500 _protected member_ `bool bExecutionControlRig;` — Currently executing ControlRig or not - later maybe this will change to enum for whatever different mode
- L509 _protected member_ `bool bPendingInitialViewportFocus = false;` — When true, the editor will try to frame the rig's visible controls in the preview viewport on the next tick. Set during init when no preview mesh is assigned (e.g. Face_ControlBoard_CtrlRig) so the camera doesn't sit somewhere with no rig content visible. Cleared once the framing has been requested or after a small number of attempts (in case the rig hierarchy never populates). See: MH issue "Control Rigs displaced out of their Blueprint Viewports".
- L510 _protected member_ `int32 PendingInitialViewportFocusTickCount = 0;`
- L512 _protected prototype_ `void OnAnimInitialized();`
- L514 _protected prototype_ `bool IsConstructionModeEnabled() const;`
- L515 _protected prototype_ `bool IsDebuggingExternalControlRig(const UControlRig* InControlRig = nullptr) const;`
- L516 _protected prototype_ `bool ShouldExecuteControlRig(const UControlRig* InControlRig = nullptr) const;`
- L518 _protected member_ `int32 RigHierarchyTabCount;`
- L519 _protected member_ `int32 ModularRigHierarchyTabCount;`
- L520 _protected member_ `TWeakObjectPtr<AStaticMeshActor> WeakGroundActorPtr;`
- L522 _protected prototype_ `void OnPreForwardsSolve_AnyThread(UControlRig* InRig, const FName& InEventName);`
- L523 _protected prototype_ `void OnPostForwardsSolve_AnyThread(UControlRig* InRig, const FName& InEventName);`
- L524 _protected prototype_ `void OnPreConstructionForUI_AnyThread(UControlRig* InRig, const FName& InEventName);`
- L525 _protected prototype_ `void OnPreConstruction_AnyThread(UControlRig* InRig, const FName& InEventName);`
- L526 _protected prototype_ `void OnPostConstruction_AnyThread(UControlRig* InRig, const FName& InEventName);`
- L527 _protected prototype_ `void OnEarlyExit_AnyThread(URigVMHost* InHost, URigVMHost::EEarlyExitReason InReason);`
- L528 _protected member_ `FRigPose PreConstructionPose;`
- L529 _protected member_ `TArray<FRigSocketState> SocketStates;`
- L530 _protected member_ `TArray<FRigConnectorState> ConnectorStates;`
- L532 _protected member_ `bool bIsConstructionEventRunning;`
- L533 _protected member_ `uint32 LastHierarchyHash;`
- L535 _protected member_ `TStrongObjectPtr<UControlRigReplay> ReplayStrongPtr;`
- L537 _protected member_ `TWeakObjectPtr<const URigVMUnitNode> DirectManipulationSubject;`
- L538 _protected member_ `TArray<TSharedPtr<FString>> DirectManipulationTextList;`
- L539 _protected member_ `TSharedPtr<SComboBox<TSharedPtr<FString>>> DirectManipulationCombo;`
- L540 _protected member_ `bool bRefreshDirectionManipulationTargetsRequired;`
- L541 _protected member_ `FSimpleMulticastDelegate RequestNavigateToConnectorWarningDelegate;`
- L542 _protected member_ `TSharedPtr<SSchematicGraphPanel> SchematicViewport;`
- L543 _protected member_ `FTimerHandle RecordReplayTimerHandle;`
- L544 _protected member_ `FRigPose BonePoseFromLastEvaluation;`
- L547 _public prototype_ `void SetupTimelineDelegates(FAnimationScrubPanelDelegates& InOutDelegates);`
- L549 _protected prototype_ `bool ShowReplayOnTimeline() const;`
- L550 _protected prototype_ `TOptional<bool> HandleReplayIsRecordingActive() const;`
- L551 _protected prototype_ `TOptional<EVisibility> HandleGetReplayRecordButtonVisibility() const;`
- L552 _protected prototype_ `bool HandleReplayStartRecording();`
- L553 _protected prototype_ `bool HandleReplayStopRecording();`
- L554 _protected prototype_ `TOptional<int32> HandleReplayGetPlaybackMode() const;`
- L555 _protected prototype_ `bool HandleReplaySetPlaybackMode(int32 InPlaybackMode);`
- L556 _protected prototype_ `TOptional<float> HandleReplayGetPlaybackTime() const;`
- L557 _protected prototype_ `bool HandleReplaySetPlaybackTime(float InTime, bool bStopPlayback);`
- L558 _protected prototype_ `bool HandleReplayStepForward();`
- L559 _protected prototype_ `bool HandleReplayStepBackward();`
- L560 _protected prototype_ `TOptional<bool> HandleReplayGetIsLooping() const;`
- L561 _protected prototype_ `bool HandleReplaySetIsLooping(bool bIsLooping);`
- L562 _protected prototype_ `TOptional<FVector2f> HandleReplayGetPlaybackTimeRange() const;`
- L563 _protected prototype_ `TOptional<uint32> HandleReplayGetNumberOfKeys() const;`
- L565 _protected prototype_ `EVisibility GetReplayValidationErrorVisibility() const;`
- L566 _protected prototype_ `FText GetReplayValidationErrorTooltip() const;`
- L568 _protected function_ `virtual FControlRigEditorClosed& OnEditorClosed() override`
- L569 _protected member_ `FControlRigEditorClosed ControlRigEditorClosedDelegate;`
- L571 _protected prototype_ `void OnClose();`
- L573 _protected member_ `static const TArray<FName> ForwardsSolveEventQueue;`
- L574 _protected member_ `static const TArray<FName> BackwardsSolveEventQueue;`
- L575 _protected member_ `static const TArray<FName> ConstructionEventQueue;`
- L576 _protected member_ `static const TArray<FName> BackwardsAndForwardsSolveEventQueue;`

#### enum `FControlRigBaseEditor::ERigElementGetterSetterType`  
`enum ERigElementGetterSetterType`  
_L430-439_
- L432 _public enumerator_ `ERigElementGetterSetterType_Transform`
- L433 _public enumerator_ `ERigElementGetterSetterType_Rotation`
- L434 _public enumerator_ `ERigElementGetterSetterType_Translation`
- L435 _public enumerator_ `ERigElementGetterSetterType_Initial`
- L436 _public enumerator_ `ERigElementGetterSetterType_Relative`
- L437 _public enumerator_ `ERigElementGetterSetterType_Offset`
- L438 _public enumerator_ `ERigElementGetterSetterType_Name`

#### Free symbols / members of external scopes

- L81 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FControlRigEditorClosed, IControlRigBaseEditor*, FControlRigAssetInterfacePtr);`

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/Editor/ControlRigEditorCommands.h` (Private)


#### class `FControlRigEditorCommands`  
`class FControlRigEditorCommands : public TCommands<FControlRigEditorCommands>`  
_L9-88_
- inherits: `TCommands<FControlRigEditorCommands>`
- L12 _public function_ `FControlRigEditorCommands() : TCommands<FControlRigEditorCommands> ( "ControlRigBlueprint", NSLOCTEXT("Contexts", "Animation", "Rig Blueprint"), NAME_None,`
- L22 _public member_ `TSharedPtr< FUICommandInfo > ConstructionEvent;` — Enable the construction mode for the rig
- L25 _public member_ `TSharedPtr< FUICommandInfo > ForwardsSolveEvent;` — Run the forwards solve graph
- L28 _public member_ `TSharedPtr< FUICommandInfo > BackwardsSolveEvent;` — Run the backwards solve graph
- L31 _public member_ `TSharedPtr< FUICommandInfo > BackwardsAndForwardsSolveEvent;` — Run the backwards solve graph followed by the forwards solve graph
- L34 _public member_ `TSharedPtr< FUICommandInfo > SetNextSolveMode;` — `UE_DEPRECATED(5.8, "Instead use SetNextEventQueue")`
- L37 _public member_ `TSharedPtr< FUICommandInfo > SetNextEventQueue;` — Sets the next Event Queue, for example Backwards Solve if the last entry in the Queue is ForwardsSolve
- L40 _public member_ `TSharedPtr< FUICommandInfo > SetPriorEventQueue;` — Sets the prior Event Queue
- L43 _public member_ `TSharedPtr< FUICommandInfo > ToggleForwardsSolveAndConstruction;` — Toggles between Forwards Solve and Construction
- L46 _public member_ `TSharedPtr< FUICommandInfo > RequestDirectManipulationPosition;` — Request per node direct manipulation on a position
- L49 _public member_ `TSharedPtr< FUICommandInfo > RequestDirectManipulationRotation;` — Request per node direct manipulation on a rotation
- L52 _public member_ `TSharedPtr< FUICommandInfo > RequestDirectManipulationScale;` — Request per node direct manipulation on a scale
- L55 _public member_ `TSharedPtr< FUICommandInfo > ToggleControlVisibility;` — Toggle visibility of the controls
- L58 _public member_ `TSharedPtr< FUICommandInfo > ToggleControlsAsOverlay;` — Toggle if controls should be rendered on top of other controls
- L61 _public member_ `TSharedPtr< FUICommandInfo > ToggleDrawNulls;` — Toggle visibility of nulls
- L64 _public member_ `TSharedPtr< FUICommandInfo > ToggleDrawSockets;` — Toggle visibility of sockets
- L67 _public member_ `TSharedPtr< FUICommandInfo > ToggleDrawAxesOnSelection;` — Toggle visibility of axes on selection
- L70 _public member_ `TSharedPtr< FUICommandInfo > ToggleSchematicViewportVisibility;` — Toggle visibility of the schematic
- L73 _public member_ `TSharedPtr< FUICommandInfo > ToggleSchematicViewportShowEmptySocketsOnly;` — Toggles if the schematic viewport shows all sockets or empty sockets only
- L76 _public member_ `TSharedPtr< FUICommandInfo > SwapModuleWithinAsset;` — Swap Module (Asset)
- L79 _public member_ `TSharedPtr< FUICommandInfo > SwapModuleAcrossProject;` — Swap Module (Project)
- L82 _public member_ `TSharedPtr< FUICommandInfo > ToggleCompileResetsEventQueue;` — Toggles if the Event Queue is reset to Forward Solve after compiling
- L87 _public prototype_ `virtual void RegisterCommands() override;` — Initialize commands

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/Editor/ControlRigEditorEditMode.h` (Private)


#### class `FControlRigEditorEditMode`  
`class FControlRigEditorEditMode : public FControlRigEditMode`  
_L9-54_
- inherits: `FControlRigEditMode`
- L12 _public prototype_ `FControlRigEditorEditMode();`
- L13 _public member_ `static inline const FLazyName ModeName = FLazyName(TEXT("Edit`
- L15 _public function_ `virtual bool IsInLevelEditor() const override`
- L16 _public function_ `virtual bool AreEditingControlRigDirectly() const override`
- L19 _public prototype_ `virtual void Render(const FSceneView* View, FViewport* Viewport, FPrimitiveDrawInterface* PDI) override;` — FEdMode interface
- L22 _public prototype_ `virtual bool GetCameraTarget(FSphere& OutTarget) const override;` — IPersonaEditMode interface
- L23 _public prototype_ `virtual class IPersonaPreviewScene& GetAnimPreviewScene() const override;`
- L24 _public prototype_ `virtual void GetOnScreenDebugInfo(TArray<FText>& OutDebugInfo) const override;`
- L27 _public prototype_ `virtual bool HandleBeginTransform(const FEditorViewportClient* InViewportClient) override;` — FControlRigEditMode interface
- L29 _public prototype_ `virtual bool IsDisplayControlsEnabled() const override;`
- L30 _public prototype_ `virtual void ToggleDisplayControlsEnabled() override;`
- L32 _public prototype_ `virtual bool IsControlsAsOverlayEnabled() const override;`
- L33 _public prototype_ `virtual void ToggleControlsAsOverlay() override;`
- L35 _public prototype_ `virtual bool IsDisplayNullsEnabled() const override;`
- L36 _public prototype_ `virtual void ToggleDisplayNulls() override;`
- L38 _public prototype_ `virtual bool IsDisplaySocketsEnabled() const override;`
- L39 _public prototype_ `virtual void ToggleDisplaySockets() override;`
- L41 _public prototype_ `virtual bool IsDisplayAxesOnSelectionEnabled() const override;`
- L42 _public prototype_ `virtual void ToggleDisplayAxesOnSelection() override;`
- L44 _public prototype_ `virtual float GetAxesOnSelectionScale() const override;`
- L47 _public member_ `bool bDrawHierarchyBones = false;` — If set to true the edit mode will additionally render all bones
- L50 _public member_ `UPersonaOptions* ConfigOption = nullptr;` — Drawing options
- L53 _public member_ `TArray<FRigElementKey> ModifiedRigElements;` — Elements which have been modified (e.g. controls moved)

#### class `FModularRigEditorEditMode`  
`class FModularRigEditorEditMode : public FControlRigEditorEditMode`  
_L56-61_
- inherits: `FControlRigEditorEditMode`
- L60 _public member_ `static inline const FLazyName ModeName = FLazyName(TEXT("Edit`

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/Editor/ControlRigEditorMode.h` (Private)


#### class `FControlRigLegacyEditorMode`  
`class FControlRigLegacyEditorMode : public FBlueprintEditorApplicationMode`  
_L19-33_
- inherits: `FBlueprintEditorApplicationMode`
- L22 _public prototype_ `FControlRigLegacyEditorMode(const TSharedRef<FControlRigLegacyEditor>& InControlRigEditor, bool bCreateDefaultLayout = true);`
- L25 _public prototype_ `virtual void RegisterTabFactories(TSharedPtr<FTabManager> InTabManager) override;` — FApplicationMode interface
- L29 _protected member_ `FWorkflowAllowedTabSet TabFactories;` — Set of spawnable tabs
- L32 _private member_ `TWeakObjectPtr<UControlRigBlueprint> ControlRigBlueprintPtr;`

#### class `FModularRigLegacyEditorMode`  
`class FModularRigLegacyEditorMode : public FControlRigLegacyEditorMode`  
_L35-45_
- inherits: `FControlRigLegacyEditorMode`
- L38 _public prototype_ `FModularRigLegacyEditorMode(const TSharedRef<FControlRigLegacyEditor>& InControlRigEditor);`
- L41 _public prototype_ `virtual void RegisterTabFactories(TSharedPtr<FTabManager> InTabManager) override;` — FApplicationMode interface
- L44 _public function_ `virtual void PostActivateMode() override` — for now just don't open up the previous edited documents

#### class `FControlRigEditorMode`  
`class FControlRigEditorMode : public FRigVMNewEditorMode`  
_L48-58_
- inherits: `FRigVMNewEditorMode`
- L51 _public prototype_ `FControlRigEditorMode(const TSharedRef<FControlRigEditor>& InControlRigEditor, bool bCreateDefaultLayout = true);`
- L54 _public prototype_ `virtual void RegisterTabFactories(TSharedPtr<FTabManager> InTabManager) override;` — FApplicationMode interface
- L57 _private member_ `TWeakInterfacePtr<IControlRigEditorAssetInterface> ControlRigBlueprintPtr;`

#### class `FModularRigEditorMode`  
`class FModularRigEditorMode : public FControlRigEditorMode`  
_L60-70_
- inherits: `FControlRigEditorMode`
- L63 _public prototype_ `FModularRigEditorMode(const TSharedRef<FControlRigEditor>& InControlRigEditor);`
- L66 _public prototype_ `virtual void RegisterTabFactories(TSharedPtr<FTabManager> InTabManager) override;` — FApplicationMode interface
- L69 _public function_ `virtual void PostActivateMode() override` — for now just don't open up the previous edited documents

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/Editor/ControlRigLegacyEditor.h` (Private)


#### class `FControlRigLegacyEditor`  
`class FControlRigLegacyEditor : public IControlRigLegacyEditor, public FControlRigBaseEditor`  
_L12-194_
- inherits: `IControlRigLegacyEditor,FControlRigBaseEditor`
- L17 _public function_ `virtual void InitRigVMEditor(const EToolkitMode::Type Mode, const TSharedPtr< class IToolkitHost >& InitToolkitHost, FRigVMEditorAssetInterfacePtr InRigVMBlueprint) override`
- L18 _public function_ `virtual void InitRigVMEditorSuper(const EToolkitMode::Type Mode, const TSharedPtr< class IToolkitHost >& InitToolkitHost, FRigVMEditorAssetInterfacePtr InRigVMBlueprint) override`
- L20 _public function_ `virtual const FName GetEditorAppName() const override`
- L21 _public function_ `virtual const FName GetEditorModeName() const override`
- L22 _public prototype_ `virtual TSharedPtr<FApplicationMode> CreateEditorMode() override;`
- L23 _public function_ `virtual const FSlateBrush* GetDefaultTabIcon() const override`
- L26 _public prototype_ `FControlRigLegacyEditor();`
- L27 _public prototype_ `virtual ~FControlRigLegacyEditor();`
- L30 _public function_ `virtual TSharedPtr<FAssetEditorToolkit> GetHostingApp() override` — FControlRigBaseEditor
- L31 _public function_ `virtual TSharedRef<IControlRigBaseEditor> SharedControlRigEditorRef() override`
- L32 _public function_ `virtual TSharedRef<IRigVMEditor> SharedRigVMEditorRef() override`
- L33 _public function_ `virtual TSharedRef<const IRigVMEditor> SharedRigVMEditorRef() const override`
- L35 _public function_ `virtual bool IsControlRigLegacyEditor() const override`
- L36 _public function_ `virtual FRigVMEditorAssetInterfacePtr GetRigVMAssetInterface() const override`
- L37 _public function_ `UControlRigBlueprint* GetControlRigBlueprint()`
- L38 _public function_ `UControlRigBlueprint* GetControlRigBlueprint() const`
- L39 _public function_ `virtual URigVMHost* GetRigVMHost() const`
- L40 _public function_ `virtual bool IsEditorInitialized() const override`
- L41 _public function_ `virtual TSharedRef<FUICommandList> GetToolkitCommands()`
- L42 _public function_ `virtual FPreviewScene* GetPreviewScene()`
- L43 _public function_ `virtual bool IsDetailsPanelRefreshSuspended() const`
- L44 _public function_ `virtual TArray<TWeakObjectPtr<UObject>> GetSelectedObjects() const`
- L45 _public function_ `virtual void ClearDetailObject(bool bChangeUISelectionState = true)`
- L46 _public function_ `virtual bool DetailViewShowsStruct(UScriptStruct* InStruct) const`
- L47 _public function_ `virtual TSharedPtr<class SWidget> GetInspector() const`
- L48 _public function_ `virtual TArray<FName> GetEventQueue() const`
- L49 _public function_ `virtual void SummonSearchUI(bool bSetFindWithinBlueprint, FString NewSearchTerms = FString(), bool bSelectFirstResult = false)`
- L50 _public function_ `virtual const TArray< UObject* >* GetObjectsCurrentlyBeingEdited() const`
- L51 _public function_ `virtual FEditorModeTools& GetEditorModeManagerImpl() const`
- L52 _public function_ `virtual const FName GetEditorModeNameImpl() const`
- L53 _public function_ `virtual URigVMController* GetFocusedController() const`
- L54 _public function_ `virtual URigVMGraph* GetFocusedModel() const`
- L55 _public function_ `virtual TArray<FName> GetLastEventQueue() const override`
- L58 _public function_ `virtual UObject* GetOuterForHost() const override` — FRigVMEditorBase interface
- L59 _public function_ `virtual UObject* GetOuterForHostSuper() const override`
- L61 _public function_ `virtual UClass* GetDetailWrapperClass() const`
- L62 _public function_ `virtual void Compile() override`
- L63 _public function_ `virtual void CompileSuper() override`
- L65 _public function_ `virtual void HandleModifiedEvent(ERigVMGraphNotifType InNotifType, URigVMGraph* InGraph, UObject* InSubject) override`
- L66 _public function_ `virtual void HandleModifiedEventSuper(ERigVMGraphNotifType InNotifType, URigVMGraph* InGraph, UObject* InSubject) override`
- L68 _public function_ `virtual void OnCreateGraphEditorCommands(TSharedPtr<FUICommandList> GraphEditorCommandsList) override`
- L69 _public function_ `virtual void OnCreateGraphEditorCommandsSuper(TSharedPtr<FUICommandList> GraphEditorCommandsList) override`
- L71 _public function_ `virtual void HandleVMCompiledEvent(UObject* InCompiledObject, URigVM* InVM, FRigVMExtendedExecuteContext& InContext) override`
- L72 _public function_ `virtual void HandleVMCompiledEventSuper(UObject* InCompiledObject, URigVM* InVM, FRigVMExtendedExecuteContext& InContext) override`
- L74 _public function_ `virtual bool ShouldOpenGraphByDefault() const override`
- L75 _public function_ `virtual FReply OnViewportDrop(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override`
- L76 _public function_ `virtual FReply OnViewportDropSuper(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override`
- L79 _public function_ `virtual void CreateEmptyGraphContent(URigVMController* InController) override` — allows the editor to fill an empty graph
- L84 _public function_ `virtual FName GetToolkitFName() const override` — IToolkit Interface
- L85 _public function_ `virtual FText GetBaseToolkitName() const override`
- L86 _public function_ `virtual FString GetWorldCentricTabPrefix() const override`
- L87 _public function_ `virtual FString GetDocumentationLink() const override`
- L90 _public function_ `virtual FReply OnSpawnGraphNodeByShortcut(FInputChord InChord, const FVector2f& InPosition, UEdGraph* InGraph) override` — BlueprintEditor interface
- L91 _public function_ `virtual FReply OnSpawnGraphNodeByShortcutSuper(FInputChord InChord, const FVector2f& InPosition, UEdGraph* InGraph) override`
- L94 _public function_ `virtual void AddViewportOverlayWidget(TSharedRef<SWidget> InViewportOverlayWidget, int32 ZOrder = INDEX_NONE) override` — FAssetEditorToolkit interface
- L95 _public function_ `virtual void RemoveViewportOverlayWidget(TSharedRef<SWidget> InViewportOverlayWidget) override`
- L97 _public prototype_ `virtual bool IsSectionVisible(NodeSectionID::Type InSectionID) const override;`
- L98 _public prototype_ `virtual bool NewDocument_IsVisibleForType(FBlueprintEditor::ECreatedDocumentType GraphType) const override;`
- L100 _public prototype_ `virtual bool IsSectionVisible(RigVMNodeSectionID::Type InSectionID) const override;`
- L101 _public prototype_ `virtual bool NewDocument_IsVisibleForType(FRigVMEditorBase::ECreatedDocumentType GraphType) const override;`
- L104 _public function_ `virtual void PostTransaction(bool bSuccess, const FTransaction* Transaction, bool bIsRedo) override`
- L107 _public function_ `virtual void Tick(float DeltaTime) override` — FTickableEditorObject Interface
- L108 _public function_ `virtual void TickSuper(float DeltaTime) override`
- L110 _public function_ `virtual void SetDetailObjects(const TArray<UObject*>& InObjects) override`
- L111 _public function_ `virtual void SetDetailObjectsSuper(const TArray<UObject*>& InObjects) override`
- L112 _public function_ `virtual void SetDetailObjectFilter(TSharedPtr<FDetailsViewObjectFilter> InObjectFilter) override`
- L113 _public function_ `virtual void RefreshDetailView() override`
- L114 _public function_ `virtual void RefreshDetailViewSuper() override`
- L119 _public function_ `virtual void OnGraphNodeDropToPerform(TSharedPtr<FDragDropOperation> InDragDropOp, UEdGraph* InGraph, const FVector2f& InNodePosition, const FVector2f& InScreenPosition) override`
- L120 _public function_ `virtual void OnGraphNodeDropToPerformSuper(TSharedPtr<FDragDropOperation> InDragDropOp, UEdGraph* InGraph, const FVector2f& InNodePosition, const FVector2f& InScreenPosition) override`
- L125 _protected prototype_ `virtual void InitToolMenuContext(FToolMenuContext& MenuContext) override;`
- L128 _protected function_ `virtual void BindCommands() override`
- L129 _protected function_ `virtual void BindCommandsSuper() override`
- L130 _protected function_ `virtual void UnbindCommands() override`
- L131 _protected function_ `virtual void UnbindCommandsSuper() override`
- L132 _protected function_ `virtual FMenuBuilder GenerateBulkEditMenu() override`
- L133 _protected function_ `virtual FMenuBuilder GenerateBulkEditMenuSuper() override`
- L135 _protected function_ `virtual void SaveAsset_Execute() override`
- L136 _protected function_ `virtual void SaveAsset_ExecuteSuper() override`
- L137 _protected function_ `virtual void SaveAssetAs_Execute() override`
- L138 _protected function_ `virtual void SaveAssetAs_ExecuteSuper() override`
- L140 _protected function_ `virtual void HandleVMExecutedEvent(URigVMHost* InHost, const FName& InEventName) override`
- L141 _protected function_ `virtual void HandleVMExecutedEventSuper(URigVMHost* InHost, const FName& InEventName) override`
- L143 _protected function_ `virtual bool CanRunGraphOnce() const override`
- L144 _protected function_ `virtual void OnRunGraphOnceToggled(bool bRunGraphOnceEnabled) override`
- L147 _protected function_ `virtual void CreateEditorModeManager() override` — FBaseToolKit overrides
- L150 _private function_ `virtual void FillToolbar(FToolBarBuilder& ToolbarBuilder, bool bEndSection = true) override` — Fill the toolbar with content
- L151 _private function_ `virtual void FillToolbarSuper(FToolBarBuilder& ToolbarBuilder, bool bEndSection = true) override`
- L153 _private function_ `virtual TArray<FName> GetDefaultEventQueue() const override`
- L154 _private function_ `virtual void SetEventQueue(TArray<FName> InEventQueue, bool bCompile) override`
- L155 _private function_ `virtual void SetEventQueueSuper(TArray<FName> InEventQueue, bool bCompile) override`
- L156 _private function_ `virtual void SetEventQueueSuper(TArray<FName> InEventQueue) override`
- L157 _private function_ `virtual int32 GetEventQueueComboValue() const override`
- L158 _private function_ `virtual int32 GetEventQueueComboValueSuper() const override`
- L159 _private function_ `virtual FText GetEventQueueLabel() const override`
- L160 _private function_ `virtual FSlateIcon GetEventQueueIcon(const TArray<FName>& InEventQueue) const override`
- L161 _private function_ `virtual void HandleSetObjectBeingDebugged(UObject* InObject) override`
- L162 _private function_ `virtual void HandleSetObjectBeingDebuggedSuper(UObject* InObject) override`
- L165 _private function_ `virtual void UpdateRigVMHost() override` — Push a newly compiled/opened control rig to the edit mode
- L166 _private function_ `virtual void UpdateRigVMHostSuper() override`
- L167 _private function_ `virtual void UpdateRigVMHost_PreClearOldHost(URigVMHost* InPreviousHost) override`
- L170 _private function_ `virtual void CacheNameLists() override` — Update the name lists for use in name combo boxes
- L171 _private function_ `virtual void CacheNameListsSuper() override`
- L173 _private function_ `virtual void GenerateEventQueueMenuContent(FMenuBuilder& MenuBuilder) override`
- L175 _private function_ `virtual void HandleRefreshEditorFromBlueprint(FRigVMEditorAssetInterfacePtr InBlueprint) override`
- L176 _private function_ `virtual void HandleRefreshEditorFromBlueprintSuper(FRigVMEditorAssetInterfacePtr InBlueprint) override`
- L180 _private function_ `virtual void OnFinishedChangingProperties(const FPropertyChangedEvent& PropertyChangedEvent) override` — delegate for changing property
- L181 _private function_ `virtual void OnFinishedChangingPropertiesSuper(const FPropertyChangedEvent& PropertyChangedEvent) override`
- L182 _private function_ `virtual void OnWrappedPropertyChangedChainEvent(URigVMDetailsViewWrapperObject* InWrapperObject, const FString& InPropertyPath, FPropertyChangedChainEvent& InPropertyChangedChainEvent) override`
- L183 _private function_ `virtual void OnWrappedPropertyChangedChainEventSuper(URigVMDetailsViewWrapperObject* InWrapperObject, const FString& InPropertyPath, FPropertyChangedChainEvent& InPropertyChangedChainEvent) override`
- L185 _private function_ `virtual void SetEditorModeManager(TSharedPtr<FEditorModeTools> InManager) override`
- L187 _private function_ `virtual const TArray<TStrongObjectPtr<URigVMDetailsViewWrapperObject>>& GetWrapperObjects() const override`
- L188 _private function_ `virtual bool& GetSuspendDetailsPanelRefreshFlag() override`
- L190 _private function_ `virtual TWeakPtr<class SGraphEditor> GetFocusedGraphEd() const override`
- L192 _private function_ `virtual void OnClose() override`
- L193 _private function_ `virtual void OnCloseSuper() override`

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/Editor/ControlRigNewEditor.h` (Private)


#### class `FControlRigEditor`  
`class FControlRigEditor : public IControlRigNewEditor, public FControlRigBaseEditor`  
_L12-197_
- inherits: `IControlRigNewEditor,FControlRigBaseEditor`
- L16 _public function_ `virtual void InitRigVMEditor(const EToolkitMode::Type Mode, const TSharedPtr< class IToolkitHost >& InitToolkitHost, FRigVMEditorAssetInterfacePtr InRigVMBlueprint) override`
- L17 _public function_ `virtual void InitRigVMEditorSuper(const EToolkitMode::Type Mode, const TSharedPtr<class IToolkitHost>& InitToolkitHost, FRigVMEditorAssetInterfacePtr InRigVMBlueprint) override`
- L19 _public function_ `virtual const FName GetEditorAppName() const override`
- L20 _public function_ `virtual const FName GetEditorModeName() const override`
- L21 _public prototype_ `virtual TSharedPtr<FApplicationMode> CreateEditorMode() override;`
- L22 _public function_ `virtual const FSlateBrush* GetDefaultTabIcon() const override`
- L25 _public prototype_ `FControlRigEditor();`
- L26 _public prototype_ `virtual ~FControlRigEditor();`
- L29 _public function_ `virtual bool IsControlRigLegacyEditor() const override` — FControlRigBaseEditor
- L30 _public function_ `virtual TSharedPtr<FAssetEditorToolkit> GetHostingApp() override`
- L31 _public function_ `virtual TSharedRef<IControlRigBaseEditor> SharedControlRigEditorRef() override`
- L32 _public function_ `virtual TSharedRef<IRigVMEditor> SharedRigVMEditorRef() override`
- L33 _public function_ `virtual TSharedRef<const IRigVMEditor> SharedRigVMEditorRef() const override`
- L35 _public function_ `virtual bool IsControlRigNewEditor() const`
- L36 _public function_ `virtual FRigVMEditorAssetInterfacePtr GetRigVMAssetInterface() const override`
- L37 _public function_ `FControlRigAssetInterfacePtr GetControlRigAssetInterface()`
- L38 _public function_ `FControlRigAssetInterfacePtr GetControlRigAssetInterface() const`
- L39 _public function_ `virtual URigVMHost* GetRigVMHost() const`
- L40 _public function_ `virtual bool IsEditorInitialized() const override`
- L41 _public function_ `virtual TSharedRef<FUICommandList> GetToolkitCommands()`
- L42 _public function_ `virtual FPreviewScene* GetPreviewScene()`
- L43 _public function_ `virtual bool IsDetailsPanelRefreshSuspended() const`
- L44 _public function_ `virtual TArray<TWeakObjectPtr<UObject>> GetSelectedObjects() const`
- L45 _public function_ `virtual void ClearDetailObject(bool bChangeUISelectionState = true)`
- L46 _public function_ `virtual bool DetailViewShowsStruct(UScriptStruct* InStruct) const`
- L47 _public function_ `virtual TSharedPtr<class SWidget> GetInspector() const`
- L48 _public function_ `virtual TArray<FName> GetEventQueue() const`
- L49 _public function_ `virtual void SummonSearchUI(bool bSetFindWithinBlueprint, FString NewSearchTerms = FString(), bool bSelectFirstResult = false)`
- L50 _public function_ `virtual const TArray< UObject* >* GetObjectsCurrentlyBeingEdited() const`
- L51 _public function_ `virtual FEditorModeTools& GetEditorModeManagerImpl() const`
- L52 _public function_ `virtual const FName GetEditorModeNameImpl() const`
- L53 _public function_ `virtual URigVMController* GetFocusedController() const`
- L54 _public function_ `virtual URigVMGraph* GetFocusedModel() const`
- L55 _public function_ `virtual TArray<FName> GetLastEventQueue() const override`
- L58 _public function_ `virtual UObject* GetOuterForHost() const override` — FRigVMEditorBase interface
- L59 _public function_ `virtual UObject* GetOuterForHostSuper() const override`
- L61 _public function_ `virtual UClass* GetDetailWrapperClass() const`
- L62 _public function_ `virtual void Compile() override`
- L63 _public function_ `virtual void CompileSuper() override`
- L65 _public function_ `virtual void HandleModifiedEvent(ERigVMGraphNotifType InNotifType, URigVMGraph* InGraph, UObject* InSubject) override`
- L66 _public function_ `virtual void HandleModifiedEventSuper(ERigVMGraphNotifType InNotifType, URigVMGraph* InGraph, UObject* InSubject) override`
- L68 _public function_ `virtual void OnCreateGraphEditorCommands(TSharedPtr<FUICommandList> GraphEditorCommandsList) override`
- L69 _public function_ `virtual void OnCreateGraphEditorCommandsSuper(TSharedPtr<FUICommandList> GraphEditorCommandsList) override`
- L71 _public function_ `virtual void HandleVMCompiledEvent(UObject* InCompiledObject, URigVM* InVM, FRigVMExtendedExecuteContext& InContext) override`
- L72 _public function_ `virtual void HandleVMCompiledEventSuper(UObject* InCompiledObject, URigVM* InVM, FRigVMExtendedExecuteContext& InContext) override`
- L74 _public function_ `virtual bool ShouldOpenGraphByDefault() const override`
- L75 _public function_ `virtual FReply OnViewportDrop(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override`
- L76 _public function_ `virtual FReply OnViewportDropSuper(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override`
- L79 _public function_ `virtual void CreateEmptyGraphContent(URigVMController* InController) override` — allows the editor to fill an empty graph
- L84 _public function_ `virtual FName GetToolkitFName() const override` — IToolkit Interface
- L85 _public function_ `virtual FText GetBaseToolkitName() const override`
- L86 _public function_ `virtual FString GetWorldCentricTabPrefix() const override`
- L87 _public function_ `virtual FString GetDocumentationLink() const override`
- L90 _public function_ `virtual FReply OnSpawnGraphNodeByShortcut(FInputChord InChord, const FVector2f& InPosition, UEdGraph* InGraph) override` — BlueprintEditor interface
- L91 _public function_ `virtual FReply OnSpawnGraphNodeByShortcutSuper(FInputChord InChord, const FVector2f& InPosition, UEdGraph* InGraph) override`
- L94 _public function_ `virtual void AddViewportOverlayWidget(TSharedRef<SWidget> InViewportOverlayWidget, int32 ZOrder = INDEX_NONE) override` — FAssetEditorToolkit interface
- L95 _public function_ `virtual void RemoveViewportOverlayWidget(TSharedRef<SWidget> InViewportOverlayWidget) override`
- L97 _public prototype_ `virtual bool IsSectionVisible(RigVMNodeSectionID::Type InSectionID) const override;`
- L98 _public prototype_ `virtual bool NewDocument_IsVisibleForType(FRigVMEditorBase::ECreatedDocumentType GraphType) const override;`
- L101 _public prototype_ `virtual void PostUndo(bool bSuccess) override;`
- L102 _public prototype_ `virtual void PostTransaction(bool bSuccess, const FTransaction* Transaction, bool bIsRedo) override;`
- L105 _public prototype_ `virtual void Tick(float DeltaTime) override;` — FTickableEditorObject Interface
- L106 _public function_ `virtual void TickSuper(float DeltaTime) override`
- L108 _public function_ `virtual void SetDetailObjects(const TArray<UObject*>& InObjects) override`
- L109 _public function_ `virtual void SetDetailObjectsSuper(const TArray<UObject*>& InObjects) override`
- L110 _public function_ `virtual void SetDetailObjectFilter(TSharedPtr<FDetailsViewObjectFilter> InObjectFilter) override`
- L111 _public function_ `virtual void RefreshDetailView() override`
- L112 _public function_ `virtual void RefreshDetailViewSuper() override`
- L117 _public function_ `virtual void OnGraphNodeDropToPerform(TSharedPtr<FDragDropOperation> InDragDropOp, UEdGraph* InGraph, const FVector2f& InNodePosition, const FVector2f& InScreenPosition) override`
- L118 _public function_ `virtual void OnGraphNodeDropToPerformSuper(TSharedPtr<FDragDropOperation> InDragDropOp, UEdGraph* InGraph, const FVector2f& InNodePosition, const FVector2f& InScreenPosition) override`
- L123 _protected function_ `virtual void BindCommands() override`
- L124 _protected function_ `virtual void BindCommandsSuper() override`
- L125 _protected function_ `virtual void UnbindCommands() override`
- L126 _protected function_ `virtual void UnbindCommandsSuper() override`
- L127 _protected function_ `virtual FMenuBuilder GenerateBulkEditMenu() override`
- L128 _protected function_ `virtual FMenuBuilder GenerateBulkEditMenuSuper() override`
- L130 _protected function_ `virtual void SaveAsset_Execute() override`
- L131 _protected function_ `virtual void SaveAsset_ExecuteSuper() override`
- L132 _protected function_ `virtual void SaveAssetAs_Execute() override`
- L133 _protected function_ `virtual void SaveAssetAs_ExecuteSuper() override`
- L135 _protected function_ `virtual void HandleVMExecutedEvent(URigVMHost* InHost, const FName& InEventName) override`
- L136 _protected function_ `virtual void HandleVMExecutedEventSuper(URigVMHost* InHost, const FName& InEventName) override`
- L139 _protected function_ `virtual void CreateEditorModeManager() override` — FBaseToolKit overrides
- L142 _protected prototype_ `virtual void InitToolMenuContext(FToolMenuContext& MenuContext) override;`
- L143 _protected function_ `virtual bool CanRunGraphOnce() const override`
- L144 _protected function_ `virtual void OnRunGraphOnceToggled(bool bRunGraphOnceEnabled) override`
- L149 _private function_ `virtual void FillToolbar(FToolBarBuilder& ToolbarBuilder, bool bEndSection = true) override` — Fill the toolbar with content
- L150 _private function_ `virtual void FillToolbarSuper(FToolBarBuilder& ToolbarBuilder, bool bEndSection = true) override`
- L152 _private function_ `virtual TArray<FName> GetDefaultEventQueue() const override`
- L153 _private function_ `virtual void SetEventQueue(TArray<FName> InEventQueue, bool bCompile) override`
- L154 _private function_ `virtual void SetEventQueueSuper(TArray<FName> InEventQueue, bool bCompile) override`
- L155 _private function_ `virtual void SetEventQueueSuper(TArray<FName> InEventQueue) override`
- L156 _private function_ `virtual int32 GetEventQueueComboValue() const override`
- L157 _private function_ `virtual int32 GetEventQueueComboValueSuper() const override`
- L158 _private function_ `virtual FText GetEventQueueLabel() const override`
- L159 _private function_ `virtual FSlateIcon GetEventQueueIcon(const TArray<FName>& InEventQueue) const override`
- L160 _private function_ `virtual void HandleSetObjectBeingDebugged(UObject* InObject) override`
- L161 _private function_ `virtual void HandleSetObjectBeingDebuggedSuper(UObject* InObject) override`
- L164 _private function_ `virtual void UpdateRigVMHost() override` — Push a newly compiled/opened control rig to the edit mode
- L165 _private function_ `virtual void UpdateRigVMHostSuper() override`
- L166 _private function_ `virtual void UpdateRigVMHost_PreClearOldHost(URigVMHost* InPreviousHost) override`
- L169 _private function_ `virtual void CacheNameLists() override` — Update the name lists for use in name combo boxes
- L170 _private function_ `virtual void CacheNameListsSuper() override`
- L172 _private function_ `virtual void GenerateEventQueueMenuContent(FMenuBuilder& MenuBuilder) override`
- L174 _private function_ `virtual void HandleRefreshEditorFromBlueprint(FRigVMEditorAssetInterfacePtr InBlueprint) override`
- L175 _private function_ `virtual void HandleRefreshEditorFromBlueprintSuper(FRigVMEditorAssetInterfacePtr InBlueprint) override`
- L179 _private function_ `virtual void OnFinishedChangingProperties(const FPropertyChangedEvent& PropertyChangedEvent) override` — delegate for changing property
- L180 _private function_ `virtual void OnFinishedChangingPropertiesSuper(const FPropertyChangedEvent& PropertyChangedEvent) override`
- L181 _private function_ `virtual void OnWrappedPropertyChangedChainEvent(URigVMDetailsViewWrapperObject* InWrapperObject, const FString& InPropertyPath, FPropertyChangedChainEvent& InPropertyChangedChainEvent) override`
- L182 _private function_ `virtual void OnWrappedPropertyChangedChainEventSuper(URigVMDetailsViewWrapperObject* InWrapperObject, const FString& InPropertyPath, FPropertyChangedChainEvent& InPropertyChangedChainEvent) override`
- L184 _private function_ `virtual void SetEditorModeManager(TSharedPtr<FEditorModeTools> InManager) override`
- L186 _private function_ `virtual const TArray<TStrongObjectPtr<URigVMDetailsViewWrapperObject>>& GetWrapperObjects() const override`
- L187 _private function_ `virtual bool& GetSuspendDetailsPanelRefreshFlag() override`
- L189 _private function_ `virtual TWeakPtr<class SGraphEditor> GetFocusedGraphEd() const override`
- L191 _private function_ `virtual void OnClose() override`
- L192 _private function_ `virtual void OnCloseSuper() override`
- L196 _private member_ `FPreviewScene PreviewScene;` — Blueprint preview scene

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/Editor/ControlRigSchematicModel.h` (Private)


#### class `FControlRigSchematicRigElementKeyNode`  
`class FControlRigSchematicRigElementKeyNode : public FSchematicGraphGroupNode`  
_L17-36_
- inherits: `FSchematicGraphGroupNode`
- desc: Node for the schematic view
- L21 _public prototype_ `SCHEMATICGRAPHNODE_BODY(FControlRigSchematicRigElementKeyNode, FSchematicGraphGroupNode) virtual ~FControlRigSchematicRigElementKeyNode() override = default;`
- L25 _public function_ `const FRigElementKey& GetKey() const`
- L26 _public prototype_ `virtual FString GetDragDropDecoratorLabel() const override;`
- L27 _public function_ `virtual bool IsAutoScaleEnabled() const override`
- L28 _public prototype_ `virtual bool IsDragSupported() const override;`
- L29 _public prototype_ `virtual const FText& GetLabel() const override;`
- L33 _protected member_ `FRigElementKey Key;`

#### class `FControlRigSchematicRigElementKeyLink`  
`class FControlRigSchematicRigElementKeyLink : public FSchematicGraphLink`  
_L39-56_
- inherits: `FSchematicGraphLink`
- desc: Link between two rig element schematic nodes
- L43 _public prototype_ `SCHEMATICGRAPHLINK_BODY(FControlRigSchematicRigElementKeyLink, FSchematicGraphLink) virtual ~FControlRigSchematicRigElementKeyLink() override = default;`
- L47 _public function_ `const FRigElementKey& GetSourceKey() const`
- L48 _public function_ `const FRigElementKey& GetTargetKey() const`
- L52 _protected member_ `FRigElementKey SourceKey;`
- L53 _protected member_ `FRigElementKey TargetKey;`

#### class `FControlRigSchematicWarningTag`  
`class FControlRigSchematicWarningTag : public FSchematicGraphTag`  
_L58-66_
- inherits: `FSchematicGraphTag`
- L62 _public prototype_ `SCHEMATICGRAPHTAG_BODY(FControlRigSchematicWarningTag, FSchematicGraphTag) FControlRigSchematicWarningTag();`
- L65 _public prototype_ `virtual ~FControlRigSchematicWarningTag() override = default;`

#### class `FControlRigSchematicModel`  
`class FControlRigSchematicModel : public FSchematicGraphModel`  
_L70-147_
- inherits: `FSchematicGraphModel`
- desc: Model for the schematic views
- L74 _public prototype_ `SCHEMATICGRAPHNODE_BODY(FControlRigSchematicModel, FSchematicGraphModel) virtual ~FControlRigSchematicModel() override;`
- L78 _public prototype_ `void SetEditor(const TSharedRef<IControlRigBaseEditor>& InEditor);`
- L79 _public prototype_ `virtual void ApplyToPanel(SSchematicGraphPanel* InPanel) override;`
- L81 _public prototype_ `virtual void Reset() override;`
- L82 _public prototype_ `virtual void Tick(float InDeltaTime) override;`
- L83 _public prototype_ `FControlRigSchematicRigElementKeyNode* AddElementKeyNode(const FRigElementKey& InKey, bool bNotify = true);`
- L84 _public prototype_ `const FControlRigSchematicRigElementKeyNode* FindElementKeyNode(const FRigElementKey& InKey) const;`
- L85 _public prototype_ `FControlRigSchematicRigElementKeyNode* FindElementKeyNode(const FRigElementKey& InKey);`
- L86 _public prototype_ `bool ContainsElementKeyNode(const FRigElementKey& InKey) const;`
- L87 _public prototype_ `virtual bool RemoveNode(const FGuid& InGuid) override;`
- L88 _public prototype_ `bool RemoveElementKeyNode(const FRigElementKey& InKey);`
- L89 _public prototype_ `FControlRigSchematicRigElementKeyLink* AddElementKeyLink(const FRigElementKey& InSourceKey, const FRigElementKey& InTargetKey, bool bNotify = true);`
- L90 _public prototype_ `void UpdateElementKeyNodes();`
- L91 _public prototype_ `void UpdateElementKeyLinks();`
- L92 _public prototype_ `void UpdateControlRigContent();`
- L93 _public prototype_ `void UpdateConnector(const FRigElementKey& InElementKey);`
- L95 _public prototype_ `void OnSetObjectBeingDebugged(UObject* InObject);`
- L96 _public prototype_ `void HandleModularRigModified(EModularRigNotification InNotification, const FRigModuleReference* InModule);`
- L98 _public function_ `virtual bool IsAutoGroupingEnabled() const`
- L99 _public prototype_ `virtual FSchematicGraphGroupNode* AddAutoGroupNode() override;`
- L100 _public prototype_ `virtual FVector2d GetPositionForNode(const FSchematicGraphNode* InNode) const override;`
- L101 _public prototype_ `virtual bool GetPositionAnimationEnabledForNode(const FSchematicGraphNode* InNode) const override;`
- L102 _public prototype_ `virtual int32 GetNumLayersForNode(const FSchematicGraphNode* InNode) const override;`
- L103 _public prototype_ `const FSlateBrush* GetBrushForKey(const FRigElementKey& InKey, const FSchematicGraphNode* InNode) const;`
- L104 _public prototype_ `virtual const FSlateBrush* GetBrushForNode(const FSchematicGraphNode* InNode, int32 InLayerIndex) const override;`
- L105 _public prototype_ `virtual FLinearColor GetColorForNode(const FSchematicGraphNode* InNode, int32 InLayerIndex) const override;`
- L106 _public prototype_ `virtual ESchematicGraphVisibility::Type GetVisibilityForNode(const FSchematicGraphNode* InNode) const override;`
- L107 _public prototype_ `virtual const FSlateBrush* GetBrushForLink(const FSchematicGraphLink* InLink) const override;`
- L108 _public prototype_ `virtual FLinearColor GetColorForLink(const FSchematicGraphLink* InLink) const override;`
- L109 _public prototype_ `virtual ESchematicGraphVisibility::Type GetVisibilityForTag(const FSchematicGraphTag* InTag) const override;`
- L110 _public prototype_ `virtual const FText GetToolTipForTag(const FSchematicGraphTag* InTag) const override;`
- L111 _public prototype_ `virtual bool GetForwardedNodeForDrag(FGuid& InOutGuid) const override;`
- L112 _public prototype_ `virtual bool GetContextMenuForNode(const FSchematicGraphNode* InNode, FMenuBuilder& OutMenu) const override;`
- L114 _public prototype_ `static TArray<FRigElementKey> GetElementKeysFromDragDropEvent(const FDragDropOperation& InDragDropOperation, const UControlRig* InControlRig);`
- L118 _private prototype_ `void ConfigureElementKeyNode(FControlRigSchematicRigElementKeyNode* InNode, const FRigElementKey& InKey);`
- L120 _private prototype_ `void HandleSchematicNodeClicked(SSchematicGraphPanel* InPanel, SSchematicGraphNode* InNode, const FPointerEvent& InMouseEvent);`
- L121 _private prototype_ `void HandleSchematicBeginDrag(SSchematicGraphPanel* InPanel, SSchematicGraphNode* InNode, const TSharedPtr<FDragDropOperation>& InDragDropOperation);`
- L122 _private prototype_ `void HandleSchematicEndDrag(SSchematicGraphPanel* InPanel, SSchematicGraphNode* InNode, const TSharedPtr<FDragDropOperation>& InDragDropOperation);`
- L123 _private prototype_ `void HandleSchematicEnterDrag(SSchematicGraphPanel* InPanel, const TSharedPtr<FDragDropOperation>& InDragDropOperation);`
- L124 _private prototype_ `void HandleSchematicLeaveDrag(SSchematicGraphPanel* InPanel, const TSharedPtr<FDragDropOperation>& InDragDropOperation);`
- L125 _private prototype_ `void HandleSchematicCancelDrag(SSchematicGraphPanel* InPanel, SSchematicGraphNode* InNode, const TSharedPtr<FDragDropOperation>& InDragDropOperation);`
- L126 _private prototype_ `void HandleSchematicDrop(SSchematicGraphPanel* InPanel, SSchematicGraphNode* InNode, const FDragDropEvent& InDragDropEvent);`
- L127 _private prototype_ `void HandlePostConstruction(UControlRig* Subject, const FName& InEventName);`
- L128 _private prototype_ `bool IsConnectorResolved(const FRigElementKey& InConnectorKey, FRigElementKey* OutKey = nullptr) const;`
- L129 _private prototype_ `void OnShowCandidatesForConnector(const FRigElementKey& InConnectorKey);`
- L130 _private prototype_ `void OnShowCandidatesForConnector(const FRigModuleConnector* InModuleConnector);`
- L131 _private prototype_ `void OnShowCandidatesForMatches(const FModularRigResolveResult& InMatches);`
- L132 _private prototype_ `void OnHideCandidatesForConnector();`
- L133 _private prototype_ `void OnHierarchyModified(ERigHierarchyNotification InNotif, URigHierarchy* InHierarchy, const FRigNotificationSubject& InSubject);`
- L135 _private member_ `TWeakPtr<IControlRigBaseEditor> ControlRigEditor;`
- L136 _private member_ `TWeakInterfacePtr<IControlRigEditorAssetInterface> ControlRigBlueprint;`
- L137 _private member_ `TWeakObjectPtr<UControlRig> ControlRigBeingDebuggedPtr;`
- L139 _private member_ `TArray<FGuid> TemporaryNodeGuids;`
- L140 _private member_ `TMap<FGuid, ESchematicGraphVisibility::Type> PreDragVisibilityPerNode;`
- L141 _private member_ `TMap<FRigElementKey, FGuid> RigElementKeyToGuid;`
- L142 _private member_ `mutable TMap<FSoftObjectPath, FSlateBrush> ModuleIcons;`
- L143 _private member_ `bool bUpdateElementKeyLinks = true;`

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/Editor/ControlRigShowSchematicViewportOverride.h` (Private)


#### struct `UE::ControlRigEditor::FControlRigShowSchematicViewportOverride`  
`struct FControlRigShowSchematicViewportOverride`  
_L11-26_
- desc: Utility to override per project per user settings schematic viewport visibility
- L21 _public prototype_ `void OverrideDuringDragDrop(const bool bOverrideShowSchematicViewport);` — Overrides the schematic viewport visibililty during a drag drop op. Note, this function has to be called when a drag drop op is already ongoing, it has no effect when called while FSlateApplication::IsDragDropping is false. Note, this function can be called once or repetitively during a drag drop op.
- L25 _private member_ `FTSTicker::FDelegateHandle TickerHandle;` — Handle for the ticker while overriden

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace ControlRigEditor` (scope `UE`)

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/Editor/ControlRigSkeletalMeshComponent.h` (Private)


#### class `UControlRigSkeletalMeshComponent`  
`class UControlRigSkeletalMeshComponent : public UDebugSkelMeshComponent`  
_L10-68_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UDebugSkelMeshComponent`
- L15 _private prototype_ `virtual void InitAnim(bool bForceReinit) override;` — USkeletalMeshComponent interface
- L18 _private prototype_ `virtual void SetCustomDefaultPose() override;` — BEGIN UDebugSkeletalMeshComponent interface
- L19 _private function_ `virtual const FReferenceSkeleton& GetReferenceSkeleton() const override`
- L24 _private function_ `virtual const TArray<FBoneIndexType>& GetDrawBoneIndices() const override`
- L29 _private prototype_ `virtual FTransform GetDrawTransform(int32 BoneIndex) const override;`
- L31 _private function_ `virtual int32 GetNumDrawTransform() const`
- L36 _private prototype_ `virtual void EnablePreview(bool bEnable, class UAnimationAsset * PreviewAsset) override;`
- L39 _private prototype_ `virtual bool IsPreviewOn() const override;` — return true if preview animation is active
- L47 _public prototype_ `void SetControlRigBeingDebugged(UControlRig* InControlRig);` — React to a control rig being debugged
- L52 _public prototype_ `void RebuildDebugDrawSkeleton();` — Rebuild debug draw skeleton
- L54 _public prototype_ `void OnHierarchyModified(ERigHierarchyNotification InNotif, URigHierarchy* InHierarchy, const FRigNotificationSubject& InSubject);`
- L55 _public prototype_ `void OnHierarchyModified_AnyThread(ERigHierarchyNotification InNotif, URigHierarchy* InHierarchy, const FRigNotificationSubject& InSubject);`
- L57 _public prototype_ `void OnPreConstruction_AnyThread(UControlRig* InControlRig, const FName& InEventName);`
- L58 _public prototype_ `void OnPostConstruction_AnyThread(UControlRig* InControlRig, const FName& InEventName);`
- L61 _private member_ `FReferenceSkeleton DebugDrawSkeleton;`
- L62 _private member_ `TArray<FBoneIndexType> DebugDrawBones;`
- L63 _private member_ `TArray<int32> DebugDrawBoneIndexInHierarchy;`
- L64 _private member_ `TWeakObjectPtr<UControlRig> ControlRigBeingDebuggedPtr;`
- L65 _private member_ `int32 HierarchyInteractionBracket;`
- L66 _private member_ `bool bRebuildDebugDrawSkeletonRequired;`
- L67 _private member_ `bool bIsConstructionEventRunning;`

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/Editor/ControlRigViewportToolbarExtensionControlRig.h` (Private)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace ControlRigEditor` (scope `UE`)
- L10 _prototype_ `void PopulateControlRigViewportToolbarControlRigSubmenu();` (scope `UE::ControlRigEditor`) — Populates the viewport toolbar submenu, unregisters when all instances are destroyed

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/Editor/ControlRigViewportToolbarExtensions.h` (Private)


#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace ControlRig` (scope `UE`)
- L13 _prototype_ `void PopulateControlRigViewportToolbarTransformSubmenu(const FName InMenuName);` (scope `UE::ControlRig`)
- L14 _prototype_ `void PopulateControlRigViewportToolbarShowSubmenu(const FName InMenuName);` (scope `UE::ControlRig`)
- L16 _prototype_ `void RemoveControlRigViewportToolbarExtensions();` (scope `UE::ControlRig`)

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/Editor/ControlRigWrapperObject.h` (Private)


#### class `UControlRigWrapperObject`  
`class UControlRigWrapperObject : public URigVMDetailsViewWrapperObject`  
_L12-23_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `URigVMDetailsViewWrapperObject`
- L17 _public prototype_ `virtual UClass* GetClassForStruct(UScriptStruct* InStruct, bool bCreateIfNeeded) const override;`
- L19 _public prototype_ `virtual void SetContent(const uint8* InStructMemory, const UStruct* InStruct) override;`
- L20 _public prototype_ `virtual void GetContent(uint8* OutStructMemory, const UStruct* InStruct) const override;`
- L22 _public member_ `FRigHierarchyKey HierarchyKey;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API CONTROLRIGEDITOR_API`

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/Editor/Hierarchy/DragDrop/ModularRigHierarchyElementDragDropOp.h` (Private)


#### class `FModularRigHierarchyElementDragDropOp`  
`class FModularRigHierarchyElementDragDropOp : public FDragDropOperation`  
_L7-34_
- inherits: `FDragDropOperation`
- L10 _public prototype_ `DRAG_DROP_OPERATOR_TYPE(FModularRigHierarchyElementDragDropOp, FDragDropOperation) static TSharedRef<FModularRigHierarchyElementDragDropOp> New(const TArray<FName>& InModuleNames);`
- L14 _public prototype_ `virtual TSharedPtr<SWidget> GetDefaultDecorator() const override;`
- L17 _public function_ `bool HasModules() const` — @return true if this drag operation contains dragged modules
- L23 _public function_ `const TArray<FName>& GetModules() const` — @return The module names from this drag operation
- L28 _public prototype_ `FString GetJoinedModuleNames() const;`
- L33 _private member_ `TArray<FName> ModuleNames;` — Data for the module names this item represents

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/Editor/Hierarchy/DragDrop/RigHierarchyElementDragDropOp.h` (Private)


#### class `FRigHierarchyElementDragDropOp`  
`class FRigHierarchyElementDragDropOp : public FGraphNodeDragDropOp`  
_L10-40_
- inherits: `FGraphNodeDragDropOp`
- L13 _public prototype_ `DRAG_DROP_OPERATOR_TYPE(FRigHierarchyElementDragDropOp, FGraphNodeDragDropOp) static TSharedRef<FRigHierarchyElementDragDropOp> New(const TArray<FRigHierarchyKey>& InElements);`
- L17 _public prototype_ `virtual TSharedPtr<SWidget> GetDefaultDecorator() const override;`
- L20 _public function_ `bool HasElements() const` — @return true if this drag operation contains property paths
- L26 _public function_ `const TArray<FRigHierarchyKey>& GetElements() const` — @return The property paths from this drag operation
- L31 _public prototype_ `FString GetJoinedElementNames() const;`
- L33 _public prototype_ `bool IsDraggingSingleConnector() const;`
- L34 _public prototype_ `bool IsDraggingSingleSocket() const;`
- L39 _private member_ `TArray<FRigHierarchyKey> Elements;` — Data for the property paths this item represents

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/Editor/Hierarchy/DragDrop/RigHierarchyTagDragDropOp.h` (Private)


#### class `FRigHierarchyTagDragDropOp`  
`class FRigHierarchyTagDragDropOp : public FDecoratedDragDropOp`  
_L9-28_
- inherits: `FDecoratedDragDropOp`
- L12 _public prototype_ `DRAG_DROP_OPERATOR_TYPE(FRigHierarchyTagDragDropOp, FDecoratedDragDropOp) static TSharedRef<FRigHierarchyTagDragDropOp> New(TSharedPtr<SRigHierarchyTagWidget> InTagWidget);`
- L16 _public prototype_ `virtual TSharedPtr<SWidget> GetDefaultDecorator() const override;`
- L19 _public function_ `const FString& GetIdentifier() const` — @return The identifier being dragged
- L26 _private member_ `FText Text;`
- L27 _private member_ `FString Identifier;`

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/Editor/Hierarchy/Models/ModularRigHierarchyTreeElement.h` (Private)


#### class `FModularRigHierarchyTreeElement`  
`class FModularRigHierarchyTreeElement : public TSharedFromThis<FModularRigHierarchyTreeElement>`  
_L19-117_
- inherits: `TSharedFromThis<FModularRigHierarchyTreeElement>`
- desc: An item in the tree
- L21 _private typedef_ `using FModularRigHierarchyConnectorWarning = UE::ControlRigEditor::FModularRigHierarchyConnectorWarning;`
- L22 _private typedef_ `using FModularRigHierarchyViewModel = UE::ControlRigEditor::FModularRigHierarchyViewModel;`
- L28 _public prototype_ `FModularRigHierarchyTreeElement( const TSharedRef<FModularRigHierarchyViewModel>& InModularRigHierarchyViewModel, const FString& InKey, const bool bInIsPrimary);`
- L34 _public function_ `bool IsPrimary() const` — Returns true if this element is a primary
- L37 _public function_ `const FString& GetKey() const` — Returns the a key that identifies this model
- L40 _public function_ `const FString& GetConnectorName() const` — Returns the name of the connector this element handles
- L43 _public function_ `const FName& GetModuleName() const` — Returns the name of the module this element handles
- L46 _public function_ `const FName& GetShortModuleName() const` — Returns the short name of the module this element handles
- L49 _public function_ `const FSlateColor& GetTextColor() const` — Returns the text color to use for this element
- L52 _public function_ `const FSlateBrush* GetIconBrush() const` — Returns the icon brush for this element
- L55 _public function_ `const FSlateColor& GetIconColor() const` — Returns the icon color to use for this element
- L58 _public function_ `const TArray<TSharedPtr<FModularRigHierarchyTreeElement>>& GetChildren() const` — Returns the child elements of this element
- L61 _public prototype_ `void AddChild(const TSharedPtr<FModularRigHierarchyTreeElement>& Child);` — Adds a child to this element
- L64 _public prototype_ `void RemoveChild(const TSharedPtr<FModularRigHierarchyTreeElement>& Child);` — Removes a child to this element
- L67 _public prototype_ `void RequestRename();` — Requests to rename the modular rig hierarchy element
- L70 _public prototype_ `bool VerifyModuleName(const FText& InNameText, FText& OutErrorMessage) const;` — Verifies if the module name is valid for this element
- L73 _public prototype_ `void SetModuleName(const FText& InNameText);` — Sets the module name
- L76 _public function_ `const TSharedPtr<FModularRigHierarchyConnectorWarning>& GetWarning() const` — Returns the current warning, or nullptr if no warning exists
- L79 _public prototype_ `TSharedRef<ITableRow> MakeTreeRowWidget(const TSharedRef<STableViewBase>& InOwnerTable, TSharedRef<FModularRigHierarchyTreeElement> InRigTreeElement, TSharedPtr<SModularRigHierarchyTreeView> InTreeView, bool bPinned);` — Creates a widget for this element
- L82 _private prototype_ `void RefreshDisplaySettings(const UModularRig* InModularRig);`
- L84 _private prototype_ `TPair<const FSlateBrush*, FSlateColor> GetBrushAndColor(const UModularRig* InModularRig);`
- L87 _private prototype_ `DECLARE_DELEGATE(FOnRenameRequested);` — A delegate to notify when RequestRename was called
- L90 _private member_ `FOnRenameRequested OnRenameRequested;` — Delegate raised when RequestRename was called, useful for the related editing widget
- L93 _private member_ `TWeakPtr<FModularRigHierarchyViewModel> WeakModularRigHierarchyViewModel;` — View outer model for the modular rig hierarchy
- L96 _private member_ `FString Key;` — Element Data to display
- L97 _private member_ `bool bIsPrimary;`
- L98 _private member_ `FName ModuleName;`
- L99 _private member_ `FString ConnectorName;`
- L100 _private member_ `FName ShortName;`
- L101 _private member_ `TArray<TSharedPtr<FModularRigHierarchyTreeElement>> Children;`
- L103 _private member_ `static TMap<FSoftObjectPath, TSharedPtr<FSlateBrush>> IconPathToBrush;`
- L104 _private member_ `static TArray<TStrongObjectPtr<UTexture2D>> Icons;`
- L107 _private member_ `const FSlateBrush* IconBrush = nullptr;` — The brush to use when rendering an icon
- L110 _private member_ `FSlateColor IconColor;` — The color to use when rendering an icon
- L113 _private member_ `FSlateColor TextColor;` — The color to use when rendering the label text
- L116 _private member_ `TSharedPtr<FModularRigHierarchyConnectorWarning> Warning;` — A warning for this element, or nullptr if there is no warning

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace ControlRigEditor` (scope `UE`)
- L87 _delegate_ `DECLARE_DELEGATE(FOnRenameRequested);` — A delegate to notify when RequestRename was called

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/Editor/Hierarchy/Models/ModularRigHierarchyViewModel.h` (Private)


#### struct `UE::ControlRigEditor::FModularRigHierarchyScopedSuspendDetailsPanelRefresh`  
`struct FModularRigHierarchyScopedSuspendDetailsPanelRefresh`  
_L34-44_
- desc: Struct to suspend details panel refresh over the scope of this function
- L36 _public prototype_ `FModularRigHierarchyScopedSuspendDetailsPanelRefresh(const TSharedRef<FModularRigHierarchyViewModel>& ViewModel);`
- L38 _public prototype_ `~FModularRigHierarchyScopedSuspendDetailsPanelRefresh();`
- L41 _private member_ `bool bStateToRestore = false;`
- L43 _private member_ `TWeakPtr<FModularRigHierarchyViewModel> WeakViewModel;`

#### class `UE::ControlRigEditor::FModularRigHierarchyViewModel`  
`class FModularRigHierarchyViewModel : FNoncopyable`  
_L47-135_
- inherits: `FNoncopyable`
- desc: A view model for the modular rig hierarchy
- L51 _public prototype_ `FModularRigHierarchyViewModel(const TSharedRef<IControlRigBaseEditor>& ControlRigEditor);`
- L54 _public prototype_ `void RefreshDetails();` — Refreshes the details view
- L57 _public prototype_ `TArray<FName> GetSelection() const;` — Returns the elements selected in data
- L60 _public prototype_ `void SelectModules(const TArray<FName>& ModuleNames);` — Selects the module in data
- L63 _public prototype_ `void SelectModuleAndChildren(const FName& ModuleName);` — Selects the module and its children in data
- L66 _public prototype_ `FName AddModule(UClass* InClass, const FName& InParentModuleName);` — Adds a new module to the rig. Returns the name of the new module or NAME_None if the module could not be added
- L67 _public prototype_ `FName AddModule(const FControlRigAssetStrongReference& InSource, const FName& InParentModuleName);`
- L70 _public prototype_ `void DeleteModules(const TArray<FName>& ModuleNames);` — Deletes modules given an array of module names
- L73 _public prototype_ `void ReparentModules(const TArray<FName>& ModuleNames, const FName& ParentModuleName, const int32 NewModuleIndex);` — Reparents the modules under their new parent at given index
- L76 _public prototype_ `void ReresolveModules(const TArray<FName>& ModuleNames);` — Reresolves the modules by auto-conneting secondary connectors
- L79 _public prototype_ `void DuplicateModules(const TArray<FName>& ModuleNames);` — Duplicates the modules
- L82 _public prototype_ `void MirrorModules(const TArray<FName>& ModuleNames, const FRigVMMirrorSettings& MirrorSettings);` — Mirrors the modules according to mirror settings
- L85 _public prototype_ `void ClipboardCopyModuleSettings(const TArray<FName>& ModuleNames) const;` — Copies the module settings of specified modules to clipboard
- L88 _public prototype_ `bool CanClipboardPasteModuleSettings(const int32 ExpectedNumElements) const;` — Returns true if clipboard paste module settings is possible and results in expected num elements
- L91 _public prototype_ `void ClipboardPasteModuleSettings(const TArray<FName>& ModuleNames) const;` — Pastes the module settings from clipboard to the specified modules
- L94 _public prototype_ `TSharedPtr<IControlRigBaseEditor> GetControlRigEditor() const;` — Returns the control rig editor
- L97 _public prototype_ `FControlRigAssetInterfacePtr GetControlRigAssetInterface() const;` — Returns the control rig asset interface
- L100 _public prototype_ `FRigVMEditorAssetInterfacePtr GetRigVMAssetInterface() const;` — Returns the rig vm asset interface
- L103 _public prototype_ `UModularRig* GetModularRig() const;` — Returns the modular rig being edited
- L106 _public prototype_ `URigHierarchy* GetHierarchy() const;` — Returns the hierarchy
- L109 _public prototype_ `UModularRigController* GetModularRigController() const;` — Returns the Modular Rig Controller
- L112 _public prototype_ `FModularRigModel* GetModularRigModel() const;` — Returns the modular rig model of this hierarchy
- L115 _public prototype_ `TArray<FRigModuleReference*> GetRootModules() const;` — Returns the root modules of the hierarchy
- L118 _public prototype_ `const FRigModuleReference* FindModule(const FName& ModuleName) const;` — Finds the module with given name
- L121 _public prototype_ `FControlRigAssetSoftReference GetModuleAssetReference(const FName& ModuleName) const;` — Returns the module class of the module
- L125 _private prototype_ `TArray<FName> GetModuleAndDecendants(const FRigModuleReference* ModuleRef) const;` — Gets the name of the module and its children recursively
- L128 _private prototype_ `TArray<FName> GetModuleAndDecendantsOrdered(const FRigModuleReference* ModuleRef) const;` — Gets the name of the module and its children recursively, ordered from root to children
- L131 _private prototype_ `TArray<FName> GetModuleAndDecendantsOrdered(const TArray<FName>& ModuleNames) const;` — Gets the name of the modules and their children recursively, ordered from root to children
- L134 _private member_ `TWeakPtr<IControlRigBaseEditor> WeakControlRigEditor;` — The editor that relates to this model

#### Free symbols / members of external scopes

- L26 _typedef_ `using FControlRigAssetInterfacePtr = TScriptInterface<IControlRigEditorAssetInterface>;`
- L27 _typedef_ `using FRigVMEditorAssetInterfacePtr = TScriptInterface<IRigVMEditorAssetInterface>;`
- L29 _namespace_ `namespace UE`
- L29 _namespace_ `namespace ControlRigEditor` (scope `UE`)

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/Editor/Hierarchy/Models/RigHierarchyTagModel.h` (Private)


#### struct `UE::ControlRigEditor::FRigHierarchyTagModelBase`  
`struct FRigHierarchyTagModelBase`  
_L15-56_
- desc: A tag in a rig hierarchy
- L18 _public prototype_ `bool MakeTagWidgetArgs(SRigHierarchyTagWidget::FArguments& OutArgs) const;` — Creates arguments to display this tag in an SRigHierarchyTagWidget
- L22 _protected member_ `bool bAllowDragDrop = true;` — If true, this tag can be drag dropped
- L25 _protected member_ `TAttribute<EVisibility> Visibility;` — Visiblity attribute
- L28 _protected member_ `const FSlateBrush* IconBrush = nullptr;` — The icon to display
- L31 _protected member_ `TOptional<FLinearColor> IconColor;` — Optional icon color
- L34 _protected member_ `TOptional<FLinearColor> BackgroundColor;` — Optional backgrouond color
- L37 _protected member_ `TAttribute<FText> Label;` — Label to display
- L40 _protected member_ `TAttribute<FText> Tooltip;` — The tooltip for the tag
- L43 _protected member_ `TAttribute<FString> Identifier;` — ID, should be set when bAllowDragDrop is true
- L46 _protected member_ `FSimpleDelegate OnClicked;` — Delegate executed when the tag is clicked
- L49 _protected member_ `FOnTextCommitted OnRenamed;` — Delegate executed when the tag was renamed
- L52 _protected member_ `FOnVerifyTextChanged OnVerifyRename;` — Delegate executed when the while the tag is being renamed, allowing to verify the currrent name
- L55 _protected member_ `bool bIsValid = false;` — Set to true when all data in this tag is valid

#### enum `UE::ControlRigEditor::ERigHierarchyConnectorTagDisplayMode`  
`enum class ERigHierarchyConnectorTagDisplayMode : uint8`  
_L59-63_
- desc: Defines how Tags are displayed in the Hierarchy
- L61 _public enumerator_ `Single`
- L62 _public enumerator_ `Individual`

#### struct `UE::ControlRigEditor::FRigHierarchyValidConnectorTag`  
`struct FRigHierarchyValidConnectorTag final : public FRigHierarchyTagModelBase`  
_L66-104_
- inherits: `FRigHierarchyTagModelBase`
- desc: A tag for a valid connector in a rig hierarchy
- L71 _private prototype_ `FRigHierarchyValidConnectorTag(const ERigHierarchyConnectorTagDisplayMode InTagDisplayMode);` — Constructs this tag, private on purpose, use BuildTag instead
- L75 _public prototype_ `static FRigHierarchyValidConnectorTag BuildTag(const ERigHierarchyConnectorTagDisplayMode InTagDisplayMode);` — Builds a new tag
- L81 _public prototype_ `FRigHierarchyValidConnectorTag& AddConnector( const UControlRig& ControlRig, const FRigHierarchyTreeDisplaySettings& DisplaySettings, const FRigConnectorElement& ConnectorElement);` — Sets the tag given a connector element, combines it if a connector element is already set. Combining should only occur when the tag display mode is ERigHierarchyConnectorTagDisplayMode::Single (ensured).
- L87 _public prototype_ `FRigHierarchyValidConnectorTag& SetOnClicked(const FSimpleDelegate& InOnClicked);` — Sets a delegate executed when the tag is clicked
- L90 _public prototype_ `FRigHierarchyValidConnectorTag& SetOnRenamed(const FOnTextCommitted& InOnRenamed);` — Sets a delegate executed when the tag was renamed
- L93 _public prototype_ `FRigHierarchyValidConnectorTag& SetOnVerifyRename(const FOnVerifyTextChanged& InOnVerifyRename);` — Sets a delegate executed when the while the tag is being renamed, allowing to verify the currrent name
- L96 _public function_ `const ERigHierarchyConnectorTagDisplayMode GetTagDisplayMode() const` — Returns how the tag is displayed in the rig hierarchy tree
- L100 _private member_ `TSet<FRigElementKey> ConnectorElementKeys;` — The connector element keys added to this tag
- L103 _private member_ `const ERigHierarchyConnectorTagDisplayMode TagDisplayMode;` — Defines how tags are displayed in the specific rig hierarchy tree

#### struct `UE::ControlRigEditor::FRigHierarchyConnectorUnresolvedWarningTag`  
`struct FRigHierarchyConnectorUnresolvedWarningTag final : public FRigHierarchyTagModelBase`  
_L108-115_
- inherits: `FRigHierarchyTagModelBase`
- desc: A warning tag for a connector that cannot be resolved in a rig hierarchy
- L111 _public prototype_ `FRigHierarchyConnectorUnresolvedWarningTag( const UControlRig& ControlRig, const FRigHierarchyTreeDisplaySettings& DisplaySettings, const FRigConnectorElement& ConnectorElement);`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace ControlRigEditor` (scope `UE`)

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/Editor/Hierarchy/Models/RigHierarchyTreeElement.h` (Private)


#### enum `ERigTreeFilterResult`  
`enum class ERigTreeFilterResult : int32`  
_L21-31_
- desc: Order is important here! This enum is used internally to the filtering logic and represents an ordering of most filtered (hidden) to least filtered (highlighted).
- L24 _public enumerator_ `Hidden` — Hide the item
- L27 _public enumerator_ `ShownDescendant` — Show the item because child items were shown
- L30 _public enumerator_ `Shown` — Show the item

#### class `FRigHierarchyTreeElement`  
`class FRigHierarchyTreeElement : public TSharedFromThis<FRigHierarchyTreeElement>`  
_L34-91_
- inherits: `TSharedFromThis<FRigHierarchyTreeElement>`
- desc: An item in the tree
- L36 _private typedef_ `using FRigHierarchyValidConnectorTag = UE::ControlRigEditor::FRigHierarchyValidConnectorTag;`
- L37 _private typedef_ `using FRigHierarchyConnectorUnresolvedWarningTag = UE::ControlRigEditor::FRigHierarchyConnectorUnresolvedWarningTag;`
- L40 _public prototype_ `FRigHierarchyTreeElement(const FRigHierarchyKey& InKey, TWeakPtr<SRigHierarchyTreeView> InTreeView, bool InSupportsRename, ERigTreeFilterResult InFilterResult);`
- L43 _public function_ `const TArray<TSharedPtr<FRigHierarchyTreeElement>>& GetChildren() const` — Returns the child elements of this element
- L48 _public member_ `FRigHierarchyKey Key;` — Element Data to display
- L49 _public member_ `FText LongName;`
- L50 _public member_ `FText ShortName;`
- L51 _public member_ `FName ChannelName;`
- L52 _public member_ `bool bIsTransient;`
- L53 _public member_ `bool bIsAnimationChannel;`
- L54 _public member_ `bool bIsProcedural;`
- L55 _public member_ `bool bSupportsRename;`
- L56 _public member_ `TArray<TSharedPtr<FRigHierarchyTreeElement>> Children;`
- L58 _public prototype_ `TSharedRef<ITableRow> MakeTreeRowWidget(const TSharedRef<STableViewBase>& InOwnerTable, TSharedRef<FRigHierarchyTreeElement> InRigTreeElement, TSharedPtr<SRigHierarchyTreeView> InTreeView, const FRigHierarchyTreeDisplaySettings& InSettings, bool bPinned);`
- L60 _public prototype_ `void RequestRename();`
- L62 _public prototype_ `void RefreshDisplaySettings(const URigHierarchy* InHierarchy, const FRigHierarchyTreeDisplaySettings& InSettings);`
- L64 _public prototype_ `FSlateColor GetIconColor() const;`
- L65 _public prototype_ `FSlateColor GetTextColor() const;`
- L68 _public prototype_ `DECLARE_DELEGATE(FOnRenameRequested);` — Delegate for when the context menu requests a rename
- L69 _public member_ `FOnRenameRequested OnRenameRequested;`
- L72 _public member_ `ERigTreeFilterResult FilterResult;` — The current filter result
- L75 _public member_ `const FSlateBrush* IconBrush;` — The brush to use when rendering an icon
- L78 _public member_ `FSlateColor IconColor;` — The color to use when rendering an icon
- L81 _public member_ `FSlateColor TextColor;` — The color to use when rendering the label text
- L84 _public member_ `bool bFadedOutDuringDragDrop;` — If true the item is filtered out during a drag
- L87 _public member_ `TArray<FRigHierarchyValidConnectorTag> ConnectorTags;` — Tags for valid connectors for this element
- L90 _public member_ `TArray<FRigHierarchyConnectorUnresolvedWarningTag> ConnectorResolveWarningTags;` — Tags for invalid connectors for this element

#### Free symbols / members of external scopes

- L68 _delegate_ `DECLARE_DELEGATE(FOnRenameRequested);` — Delegate for when the context menu requests a rename

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/Editor/Hierarchy/ModularRigHierarchyTreeDelegates.h` (Private)


#### struct `FModularRigHierarchyTreeDelegates`  
`struct FModularRigHierarchyTreeDelegates`  
_L22-49_
- L26 _public member_ `FOnGetModularRigTreeRig OnGetModularRig;`
- L27 _public member_ `FOnModularRigTreeMouseButtonClick OnMouseButtonClick;`
- L28 _public member_ `FOnModularRigTreeMouseButtonDoubleClick OnMouseButtonDoubleClick;`
- L29 _public member_ `FOnDragDetected OnDragDetected;`
- L30 _public member_ `FOnModularRigTreeCanAcceptDrop OnCanAcceptDrop;`
- L31 _public member_ `FOnModularRigTreeAcceptDrop OnAcceptDrop;`
- L32 _public member_ `FOnContextMenuOpening OnContextMenuOpening;`
- L33 _public member_ `FOnModularRigTreeResolveConnector OnResolveConnector;`
- L34 _public member_ `FOnModularRigTreeDisconnectConnector OnDisconnectConnector;`
- L35 _public member_ `FOnModularRigTreeSelectionChanged OnSelectionChanged;`
- L36 _public member_ `FOnModularRigTreeAlwaysShowConnector OnAlwaysShowConnector;`
- L38 _public prototype_ `const UModularRig* GetModularRig() const;`
- L39 _public prototype_ `bool HandleResolveConnector(const FRigElementKey& InConnector, const TArray<FRigElementKey>& InTargets);`
- L40 _public prototype_ `bool HandleDisconnectConnector(const FRigElementKey& InConnector);`
- L41 _public prototype_ `void HandleSelectionChanged(TSharedPtr<FModularRigHierarchyTreeElement> Selection, ESelectInfo::Type SelectInfo);`
- L42 _public prototype_ `bool ShouldAlwaysShowConnector(const FName& InConnectorName) const;`
- L46 _private member_ `bool bSuspendSelectionDelegate = false;`

#### Free symbols / members of external scopes

- L11 _delegate_ `DECLARE_DELEGATE_RetVal(const UModularRig*, FOnGetModularRigTreeRig);`
- L11 _prototype_ `DECLARE_DELEGATE_RetVal(const UModularRig*, FOnGetModularRigTreeRig);`
- L12 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnModularRigTreeResolveConnector, const FRigElementKey& , const TArray<FRigElementKey>& );`
- L12 _prototype_ `DECLARE_DELEGATE_TwoParams(FOnModularRigTreeResolveConnector, const FRigElementKey& , const TArray<FRigElementKey>& );`
- L13 _delegate_ `DECLARE_DELEGATE_OneParam(FOnModularRigTreeDisconnectConnector, const FRigElementKey& );`
- L13 _prototype_ `DECLARE_DELEGATE_OneParam(FOnModularRigTreeDisconnectConnector, const FRigElementKey& );`
- L14 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FOnModularRigTreeAlwaysShowConnector, const FName& );`
- L14 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FOnModularRigTreeAlwaysShowConnector, const FName& );`
- L16 _typedef_ `typedef STreeView<TSharedPtr<FModularRigHierarchyTreeElement>>::FOnMouseButtonClick FOnModularRigTreeMouseButtonClick;`
- L17 _typedef_ `typedef STreeView<TSharedPtr<FModularRigHierarchyTreeElement>>::FOnMouseButtonDoubleClick FOnModularRigTreeMouseButtonDoubleClick;`
- L18 _typedef_ `typedef STableRow<TSharedPtr<FModularRigHierarchyTreeElement>>::FOnCanAcceptDrop FOnModularRigTreeCanAcceptDrop;`
- L19 _typedef_ `typedef STableRow<TSharedPtr<FModularRigHierarchyTreeElement>>::FOnAcceptDrop FOnModularRigTreeAcceptDrop;`
- L20 _typedef_ `typedef STreeView<TSharedPtr<FModularRigHierarchyTreeElement>>::FOnSelectionChanged FOnModularRigTreeSelectionChanged;`

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/Editor/Hierarchy/RigHierarchyImportSettings.h` (Private)


#### struct `FRigHierarchyImportSettings`  
`struct FRigHierarchyImportSettings`  
_L11-22_
- reflection: `USTRUCT()`
- L15 _public function_ `FRigHierarchyImportSettings() : Mesh(nullptr)`
- L21 _public member_ `TObjectPtr<USkeletalMesh> Mesh;` — `UPROPERTY(EditAnywhere, Category = "Hierarchy Import")`

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/Editor/Hierarchy/RigHierarchyTreeDelegates.h` (Private)


#### struct `FRigHierarchyTreeDelegates`  
`struct FRigHierarchyTreeDelegates`  
_L38-76_
- L40 _public member_ `FOnGetRigTreeHierarchy OnGetHierarchy;`
- L41 _public member_ `FOnGetRigTreeDisplaySettings OnGetDisplaySettings;`
- L42 _public member_ `FOnRigTreeRenameElement OnRenameElement;`
- L43 _public member_ `FOnRigTreeVerifyElementNameChanged OnVerifyElementNameChanged;`
- L44 _public member_ `FOnDragDetected OnDragDetected;`
- L45 _public member_ `FOnRigTreeCanAcceptDrop OnCanAcceptDrop;`
- L46 _public member_ `FOnRigTreeAcceptDrop OnAcceptDrop;`
- L47 _public member_ `FOnRigTreeGetSelection OnGetSelection;`
- L48 _public member_ `FOnRigTreeSelectionChanged OnSelectionChanged;`
- L49 _public member_ `FOnContextMenuOpening OnContextMenuOpening;`
- L50 _public member_ `FOnRigTreeMouseButtonClick OnMouseButtonClick;`
- L51 _public member_ `FOnRigTreeMouseButtonDoubleClick OnMouseButtonDoubleClick;`
- L52 _public member_ `FOnRigTreeSetExpansionRecursive OnSetExpansionRecursive;`
- L53 _public member_ `FOnRigTreeCompareKeys OnCompareKeys;`
- L54 _public member_ `FOnRigTreeGetResolvedKey OnGetResolvedKey;`
- L55 _public member_ `FOnRigTreeRequestDetailsInspection OnRequestDetailsInspection;`
- L56 _public member_ `FOnRigTreeElementKeyTagDragDetected OnRigTreeElementKeyTagDragDetected;`
- L57 _public member_ `FOnRigTreeItemGetToolTip OnRigTreeGetItemToolTip;`
- L58 _public member_ `FOnRigTreeIsItemVisible OnRigTreeIsItemVisible;`
- L59 _public member_ `FOnRigTreeGetTagDisplayMode OnGetTagDisplayMode;`
- L61 _public prototype_ `URigHierarchy* GetHierarchy();`
- L62 _public prototype_ `const URigHierarchy* GetHierarchy() const;`
- L63 _public prototype_ `const FRigHierarchyTreeDisplaySettings& GetDisplaySettings() const;`
- L64 _public prototype_ `TArray<FRigHierarchyKey> GetSelection() const;`
- L65 _public prototype_ `FName HandleRenameElement(const FRigHierarchyKey& OldKey, const FString& NewName) const;`
- L66 _public prototype_ `bool HandleVerifyElementNameChanged(const FRigHierarchyKey& OldKey, const FString& NewName, FText& OutErrorMessage) const;`
- L67 _public prototype_ `void HandleSelectionChanged(TSharedPtr<FRigHierarchyTreeElement> Selection, ESelectInfo::Type SelectInfo);`
- L68 _public prototype_ `FRigHierarchyKey GetResolvedKey(const FRigHierarchyKey& InKey);`
- L69 _public prototype_ `void RequestDetailsInspection(const FRigHierarchyKey& InKey);`
- L70 _public prototype_ `UE::ControlRigEditor::ERigHierarchyConnectorTagDisplayMode GetTagDisplayMode() const;`
- L72 _public member_ `static FRigHierarchyTreeDisplaySettings DefaultDisplaySettings;`
- L75 _private member_ `bool bIsChangingRigHierarchy = false;`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace ControlRigEditor` (scope `UE`)
- L17 _typedef_ `typedef STableRow<TSharedPtr<FRigHierarchyTreeElement>>::FOnCanAcceptDrop FOnRigTreeCanAcceptDrop;`
- L18 _typedef_ `typedef STableRow<TSharedPtr<FRigHierarchyTreeElement>>::FOnAcceptDrop FOnRigTreeAcceptDrop;`
- L19 _typedef_ `typedef STreeView<TSharedPtr<FRigHierarchyTreeElement>>::FOnSelectionChanged FOnRigTreeSelectionChanged;`
- L20 _typedef_ `typedef STreeView<TSharedPtr<FRigHierarchyTreeElement>>::FOnMouseButtonClick FOnRigTreeMouseButtonClick;`
- L21 _typedef_ `typedef STreeView<TSharedPtr<FRigHierarchyTreeElement>>::FOnMouseButtonDoubleClick FOnRigTreeMouseButtonDoubleClick;`
- L22 _typedef_ `typedef STreeView<TSharedPtr<FRigHierarchyTreeElement>>::FOnSetExpansionRecursive FOnRigTreeSetExpansionRecursive;`
- L24 _delegate_ `DECLARE_DELEGATE_RetVal(const URigHierarchy*, FOnGetRigTreeHierarchy);`
- L24 _prototype_ `DECLARE_DELEGATE_RetVal(const URigHierarchy*, FOnGetRigTreeHierarchy);`
- L25 _delegate_ `DECLARE_DELEGATE_RetVal(const FRigHierarchyTreeDisplaySettings&, FOnGetRigTreeDisplaySettings);`
- L25 _prototype_ `DECLARE_DELEGATE_RetVal(const FRigHierarchyTreeDisplaySettings&, FOnGetRigTreeDisplaySettings);`
- L26 _delegate_ `DECLARE_DELEGATE_RetVal(const TArray<FRigHierarchyKey>, FOnRigTreeGetSelection);`
- L26 _prototype_ `DECLARE_DELEGATE_RetVal(const TArray<FRigHierarchyKey>, FOnRigTreeGetSelection);`
- L27 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(FName, FOnRigTreeRenameElement, const FRigHierarchyKey& , const FString& );`
- L27 _prototype_ `DECLARE_DELEGATE_RetVal_TwoParams(FName, FOnRigTreeRenameElement, const FRigHierarchyKey& , const FString& );`
- L28 _delegate_ `DECLARE_DELEGATE_RetVal_ThreeParams(bool, FOnRigTreeVerifyElementNameChanged, const FRigHierarchyKey& , const FString& , FText& );`
- L28 _prototype_ `DECLARE_DELEGATE_RetVal_ThreeParams(bool, FOnRigTreeVerifyElementNameChanged, const FRigHierarchyKey& , const FString& , FText& );`
- L29 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FOnRigTreeCompareKeys, const FRigHierarchyKey& , const FRigHierarchyKey& );`
- L29 _prototype_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FOnRigTreeCompareKeys, const FRigHierarchyKey& , const FRigHierarchyKey& );`
- L30 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(FRigHierarchyKey, FOnRigTreeGetResolvedKey, const FRigHierarchyKey&);`
- L30 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(FRigHierarchyKey, FOnRigTreeGetResolvedKey, const FRigHierarchyKey&);`
- L31 _delegate_ `DECLARE_DELEGATE_OneParam(FOnRigTreeRequestDetailsInspection, const FRigHierarchyKey&);`
- L31 _prototype_ `DECLARE_DELEGATE_OneParam(FOnRigTreeRequestDetailsInspection, const FRigHierarchyKey&);`
- L32 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(TOptional<FText>, FOnRigTreeItemGetToolTip, const FRigHierarchyKey&);`
- L32 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(TOptional<FText>, FOnRigTreeItemGetToolTip, const FRigHierarchyKey&);`
- L33 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FOnRigTreeIsItemVisible, const FRigHierarchyKey&);`
- L33 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FOnRigTreeIsItemVisible, const FRigHierarchyKey&);`
- L34 _delegate_ `DECLARE_DELEGATE_RetVal(UE::ControlRigEditor::ERigHierarchyConnectorTagDisplayMode, FOnRigTreeGetTagDisplayMode);`
- L34 _prototype_ `DECLARE_DELEGATE_RetVal(UE::ControlRigEditor::ERigHierarchyConnectorTagDisplayMode, FOnRigTreeGetTagDisplayMode);`
- L36 _macro_ `#define UE_API CONTROLRIGEDITOR_API`

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/Editor/Hierarchy/RigHierarchyTreeDisplaySettings.h` (Private)


#### struct `FRigHierarchyTreeDisplaySettings`  
`struct FRigHierarchyTreeDisplaySettings`  
_L8-80_
- L10 _public function_ `FRigHierarchyTreeDisplaySettings()`
- L31 _public member_ `FText FilterText;`
- L34 _public member_ `bool bFlattenHierarchyOnFilter;` — Flatten when text filtering is active
- L37 _public member_ `bool bHideParentsOnFilter;` — Hide parents when text filtering is active
- L40 _public member_ `EElementNameDisplayMode NameDisplayMode;` — The mode used to determine how names are displayed
- L43 _public member_ `bool bShowImportedBones;` — Whether or not to show imported bones in the hierarchy
- L46 _public member_ `bool bShowBones;` — Whether or not to show bones in the hierarchy
- L49 _public member_ `bool bShowControls;` — Whether or not to show controls in the hierarchy
- L52 _public member_ `bool bShowNulls;` — Whether or not to show spaces in the hierarchy
- L55 _public member_ `bool bShowReferences;` — Whether or not to show references in the hierarchy
- L58 _public member_ `bool bShowSockets;` — Whether or not to show sockets in the hierarchy
- L61 _public member_ `bool bShowConnectors;` — Whether or not to show connectors in the hierarchy
- L64 _public member_ `bool bShowComponents;` — Whether or not to show components in the hierarchy
- L67 _public member_ `bool bShowIconColors;` — Whether to tint the icons with the element color
- L70 _public member_ `bool bArrangeByModules;` — Whether or not to arrange the controls into modules (only for modular rigs)
- L73 _public member_ `bool bFlattenModules;` — Whether or not to arrange the modules in a flat list (only for modular rigs)
- L76 _public member_ `bool bFocusOnSelection;` — Whether or not to expand and focus the selection when this changes
- L79 _public member_ `EMultiRigTreeDisplayMode OutlinerDisplayMode;` — Identify which rigs to display based on selection

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/Editor/Hierarchy/RigHierarchyTreePersistentState.h` (Private)


#### struct `UE::ControlRigEditor::RigHierarchyTreePersistentStatePrivate::FRigHierarchElementPersistentStateKey`  
`struct FRigHierarchElementPersistentStateKey`  
_L61-74_
- desc: Key for the persistent state of a single element in the hierarchy tree
- L63 _public prototype_ `FRigHierarchElementPersistentStateKey(const TSharedRef<FRigHierarchyTreeElement>& Element);`
- L64 _public prototype_ `FRigHierarchElementPersistentStateKey(const TSharedRef<FModularRigHierarchyTreeElement>& Element);`
- L66 _public prototype_ `bool operator==(const FRigHierarchElementPersistentStateKey& Other) const;`
- L67 _public prototype_ `bool operator!=(const FRigHierarchElementPersistentStateKey& Other) const;`
- L73 _private member_ `TVariant<FRigHierarchyKey, FString> VariantKey;` — Variant key for which to store the persistent state

#### struct `UE::ControlRigEditor::RigHierarchyTreePersistentStatePrivate::FRigHierarchyTreePersistentState`  
`struct FRigHierarchyTreePersistentState : public TSharedFromThis<FRigHierarchyTreePersistentState>`  
_L77-270_
- inherits: `TSharedFromThis<FRigHierarchyTreePersistentState>`
- desc: A persistent state of a specific hierarchy tree
- L82 _public function_ `bool IsPersistent() const` — Returns true while this state was stored for a new instance of the tree
- L85 _public function_ `bool IsPendingRestore() const` — Returns true while this state was stored but not restored yet
- L89 _public function_ `template <typename TElementType> requires ConceptIsHierarchyElementType<TElementType> void Store( const UControlRig& ControlRig, const STreeView<TElementType>& TreeView, const FName& ViewName)` — Initializes the state while a tree is being destroyed, so it can be restored in a new instance
- L101 _public function_ `template <typename TElementType> requires ConceptIsHierarchyElementType<TElementType> void RestoreState( STreeView<TElementType>& TreeView, const FRigHierarchyTreePersistentStateRebuildItemsRequested& OnRebuildItems, const FOnRigHierarchyTreePersistentStateRestored& OnStateRestored) const` — Restores the state for the specified tree view. This can be a new instance of the tree view.
- L139 _public function_ `template <typename TElementType> requires ConceptIsHierarchyElementType<TElementType> void RetainDuringRefresh( const UControlRig& ControlRig, const TSharedRef<STreeView<TElementType>>& TreeView, const FName& ViewName, const FRigHierarchyTreePersistentStateRebuildItemsRequested& OnRebuildItems, const FOnRigHierarchyTreePersistentStateRestored& OnStateRestored)` — Retains the state of the tree while it is being refreshed. Restoration can be deferred by calling DeferRestoreState
- L181 _public function_ `void DeferRestoreState()` — Defers restoring the state to the first frame number where it wasn't deffered
- L190 _private function_ `template <typename TElementType> requires ConceptIsHierarchyElementType<TElementType> void StoreStateInternal( const UControlRig& ControlRig, const STreeView<TElementType>& TreeView, const FName& ViewName)` — Effectively stores the state
- L207 _private function_ `template <typename TElementType> requires ConceptIsHierarchyElementType<TElementType> void StoreElementExpansionState(const TElementType& Element, bool bExpanded)` — Stores the expansion state of the element in this persistent state
- L218 _private function_ `template <typename TElementType> requires ConceptIsHierarchyElementType<TElementType> void StoreElementSelectionState(const TElementType& Element, bool bExpanded)` — Stores the selection state of the element in this persistent state
- L229 _private function_ `template <typename TElementType> requires ConceptIsHierarchyElementType<TElementType> const bool* GetElementExpansionState(const TElementType& Element) const` — Gets the expansion state for the element. Note, the element is compared by key, not by ptr to ensure persistency.
- L242 _private function_ `template <typename TElementType> requires ConceptIsHierarchyElementType<TElementType> const bool* GetElementSelectionState(const TElementType& Element) const` — Gets the selection state for the element. Note, the element is compared by key, not by ptr to ensure persistency.
- L254 _private member_ `float ScrollOffset = 0.f;` — The scroll offset
- L257 _private member_ `uint32 RestoreOnFrame = 0;` — The frame on which this state can be restored
- L260 _private member_ `bool bIsPersistent = false;` — True while this state was persists for a new instance of the tree
- L263 _private member_ `bool bIsPendingRestore = false;` — True while this state was stored but not restored yet
- L266 _private member_ `TMap<FRigHierarchElementPersistentStateKey, bool> KeyToExpansionStateMap;` — A map of hierarchy keys and their expansion state in the tree
- L269 _private member_ `TMap<FRigHierarchElementPersistentStateKey, bool> KeyToSelectionStateMap;` — A map of hierarchy keys and their selection state in the tree

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace ControlRigEditor` (scope `UE`)
- L18 _delegate_ `DECLARE_DELEGATE(FRigHierarchyTreePersistentStateRebuildItemsRequested);` — Delegate raised when items can be rebuilt during a tree refresh
- L18 _prototype_ `DECLARE_DELEGATE(FRigHierarchyTreePersistentStateRebuildItemsRequested);` (scope `UE::ControlRigEditor`) — Delegate raised when items can be rebuilt during a tree refresh
- L28 _namespace_ `namespace RigHierarchyTreePersistentStatePrivate` (scope `UE::ControlRigEditor`)
- L32 _function_ `template <typename TElementType> requires ConceptIsHierarchyElementType<TElementType> TArray<const TElementType> GetAllElementsInTree(const STreeView<TElementType>& TreeView)` (scope `UE::ControlRigEditor::RigHierarchyTreePersistentStatePrivate`) — Returns all elements in the tree
- L37 _function_ `` (scope `UE::ControlRigEditor::RigHierarchyTreePersistentStatePrivate::GetAllElementsInTree`)
- L153 _function_ `` (scope `UE::ControlRigEditor::RigHierarchyTreePersistentStatePrivate::FRigHierarchyTreePersistentState::RetainDuringRefresh`)

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/Editor/Hierarchy/RigHierarchyTreePersistentStateDelegates.h` (Private)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace ControlRigEditor` (scope `UE`)
- L10 _delegate_ `DECLARE_DELEGATE(FOnRigHierarchyTreePersistentStateRestored);` — Delegate raised when the persistent state of a tree view was restored
- L10 _prototype_ `DECLARE_DELEGATE(FOnRigHierarchyTreePersistentStateRestored);` (scope `UE::ControlRigEditor`) — Delegate raised when the persistent state of a tree view was restored

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/Editor/Hierarchy/RigHierarchyTreePersistentStateStore.h` (Private)


#### class `UE::ControlRigEditor::FRigHierarchyTreePersistentStateStore`  
`class FRigHierarchyTreePersistentStateStore : public TSharedFromThis<FRigHierarchyTreePersistentStateStore>`  
_L27-149_
- inherits: `TSharedFromThis<FRigHierarchyTreePersistentStateStore>`
- desc: Stores the state of a rig hierarchy tree view persistently, so it can be restored from a possibly destructed instance. During their lifetime hierarchy tree views can call FRigHierarchyTreePersistentStateStore::RequestTreeRefresh to retain their state. Refresh will occur one tick after no RequestTreeRefresh call occured. Hierarchy tree views can call FRigHierarchyTreePersistentStateStore::StorePersistentState anytime to store their state persistently without refreshing.
- L34 _private typedef_ `using FRigHierarchyTreePersistentState = UE::ControlRigEditor::RigHierarchyTreePersistentStatePrivate::FRigHierarchyTreePersistentState;`
- L38 _public prototype_ `static FRigHierarchyTreePersistentStateStore& Get();` — Gets the store instance
- L45 _public function_ `template <typename TElementType> requires ConceptIsHierarchyElementType<TElementType> void StorePersistentState( const UControlRig& ControlRig, STreeView<TElementType>& TreeView, const FName& ViewName)` — Retains the of a rig hierarchy tree while it is being destroyed, so it can be restored when it was reinstantiated and refreshed.
- L76 _public function_ `template <typename TElementType> requires ConceptIsHierarchyElementType<TElementType> void RequestTreeRefresh( const UControlRig& ControlRig, const TSharedRef<STreeView<TElementType>>& TreeView, const FName& ViewName, const TSharedPtr<IControlRigBaseEditor>& ControlRigEditor = nullptr, const FRigHierarchyTreePersistentStateRebuildItemsRequested& OnRebuildItems = FRigHierarchyTreePersistentStateRebuildItemsRequested(), const FOnRigHierarchyTreePersistentStateRestored& OnStateRestored = FOnRigHierarchyTreePersistentStateRestored())` — Refreshes the tree on the first tick after this function was last called, possibly skipping over many ticks, e.g. during compiling where the data is reconstructed. If this is a new tree and a previous state was stored persistently, the persistent state is recalled.
- L126 _public prototype_ `static bool IsFeatureEnabled();` — Returns true if the CVar to enable this store is set
- L130 _private prototype_ `FRigHierarchyTreePersistentStateStore() = default;` — Private on purpose, instead use FRigHierarchyTreePersistentStateStore::Get
- L133 _private function_ `TOptional<FName> MakeID(const UControlRig& ControlRig, const FName& ViewName) const` — Creates a persistent ID for a specific view, consisting in the form of AssetPath.ViewName
- L145 _private member_ `TMap<FName, TSharedRef<FRigHierarchyTreePersistentState>> IdToPersistentStateMap;` — Map of IDs in the form of AssetPath.ViewName to the persistent state
- L148 _private member_ `static TSharedPtr<FRigHierarchyTreePersistentStateStore> Instance;` — Static instance

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace ControlRigEditor` (scope `UE`)

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/Editor/Hierarchy/Views/SModularRigHierarchy.h` (Private)


#### class `SModularRigHierarchy`  
`class SModularRigHierarchy : public SCompoundWidget, public FSelfRegisteringEditorUndoClient`  
_L24-175_
- inherits: `SCompoundWidget,FSelfRegisteringEditorUndoClient`
- desc: Widget allowing editing of a control rig's structure
- L26 _private typedef_ `using FModularRigHierarchyViewModel = UE::ControlRigEditor::FModularRigHierarchyViewModel;`
- L29 _public function_ `SLATE_BEGIN_ARGS(SModularRigHierarchy)`
- L32 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedRef<IControlRigBaseEditor> InControlRigEditor, const FName& InViewName);`
- L44 _private prototype_ `void OnEditorClose(IControlRigBaseEditor* InEditor, FControlRigAssetInterfacePtr InBlueprint);`
- L47 _private prototype_ `void BindCommands();` — Bind commands that this widget handles
- L50 _private prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent);` — SWidget interface
- L51 _private prototype_ `virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L54 _private prototype_ `void RefreshTreeView(bool bRebuildContent = true);` — Rebuild the tree view
- L57 _private prototype_ `void OnHiddenColumnsListChanged();` — Called when the hidden columns list changed
- L60 _private prototype_ `TArray<TSharedPtr<FModularRigHierarchyTreeElement>> GetSelectedItems() const;` — Returns all selected items
- L63 _private prototype_ `TArray<FString> GetSelectedKeys() const;` — Return all selected keys
- L66 _private prototype_ `void HandleNewItem();` — Create a new item
- L69 _private prototype_ `void HandleRenameModule();` — Rename item
- L70 _private prototype_ `FName HandleRenameModule(const FName& InOldModuleName, const FName& InNewName);`
- L71 _private prototype_ `bool HandleVerifyNameChanged(const FName& InOldModuleName, const FName& InNewName, FText& OutErrorMessage);`
- L74 _private prototype_ `void HandleDeleteModules();` — Delete items
- L77 _private prototype_ `void HandleDuplicateModules();` — Duplicate items
- L80 _private prototype_ `void HandleMirrorModules();` — Mirror items
- L83 _private prototype_ `void HandleReresolveModules();` — Reresolve items
- L86 _private prototype_ `bool CanSwapModules() const;` — Swap module class for items
- L87 _private prototype_ `void HandleSwapClassForModules();`
- L88 _private prototype_ `void HandleSwapClassForModules(const TArray<FName>& InModuleNames);`
- L91 _private prototype_ `bool CanCopyModuleSettings() const;` — Copy & paste module settings
- L92 _private prototype_ `void HandleCopyModuleSettings();`
- L93 _private prototype_ `bool CanPasteModuleSettings() const;`
- L94 _private prototype_ `void HandlePasteModuleSettings();`
- L97 _private prototype_ `void ToggleConnectorVisibilityFlags(const EModularRigHierarchyEditorConnectorVisibilityFlags ConnectorVisibilityFlags);` — Toggles visibility of specified connector visiblity flags
- L100 _private prototype_ `bool AreAnyConnectorVisibilityFlagsSet(const EModularRigHierarchyEditorConnectorVisibilityFlags ConnectorVisibilityFlags) const;` — Returns true if any of the provided connector visiblity flags are set
- L103 _private prototype_ `void HandleConnectorResolved(const FRigElementKey& InConnector, const TArray<FRigElementKey>& InTargets);` — Resolve connector
- L106 _private prototype_ `void HandleConnectorDisconnect(const FRigElementKey& InConnector);` — UnResolve connector
- L109 _private prototype_ `void HandleSelectionChanged(TSharedPtr<FModularRigHierarchyTreeElement> Selection, ESelectInfo::Type SelectInfo);` — Set Selection Changed
- L112 _private prototype_ `bool ShouldAlwaysShowConnector(const FName& InConnectorName) const;` — Returns true if a given connector should always be shown
- L114 _private prototype_ `TSharedPtr< SWidget > CreateContextMenuWidget();`
- L117 _private prototype_ `virtual void PostUndo(bool bSuccess) override;`
- L118 _private prototype_ `virtual void PostRedo(bool bSuccess) override;`
- L122 _private prototype_ `FReply OnDragDetected(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent);` — reply to a drag operation
- L125 _private prototype_ `TOptional<EItemDropZone> OnCanAcceptDrop(const FDragDropEvent& DragDropEvent, EItemDropZone DropZone, TSharedPtr<FModularRigHierarchyTreeElement> TargetItem);` — reply to a drop operation on item
- L126 _private prototype_ `FReply OnAcceptDrop(const FDragDropEvent& DragDropEvent, EItemDropZone DropZone, TSharedPtr<FModularRigHierarchyTreeElement> TargetItem);`
- L129 _private prototype_ `virtual FReply OnDrop(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;` — SWidget Overrides
- L131 _private member_ `static const FName ContextMenuName;`
- L132 _private prototype_ `static void CreateContextMenu();`
- L133 _private prototype_ `UToolMenu* GetContextMenu();`
- L134 _private prototype_ `TSharedPtr<FUICommandList> GetContextMenuCommands() const;`
- L137 _private member_ `TSharedPtr<SModularRigHierarchyTreeView> TreeView;` — Tree view widget
- L138 _private member_ `TSharedPtr<SHeaderRow> HeaderRowWidget;`
- L140 _private member_ `TWeakInterfacePtr<IControlRigEditorAssetInterface> ControlRigBlueprint;`
- L141 _private member_ `TWeakObjectPtr<UModularRig> ControlRigBeingDebuggedPtr;`
- L144 _private member_ `TSharedPtr<FUICommandList> CommandList;` — Command list we bind to
- L146 _private prototype_ `void HandlePostCompileModularRigs(FRigVMEditorAssetInterfacePtr InBlueprint);`
- L147 _private prototype_ `void OnHierarchyModified(ERigHierarchyNotification InNotif, URigHierarchy* InHierarchy, const FRigNotificationSubject& InSubject);`
- L149 _private prototype_ `void HandleRefreshEditorFromBlueprint(FRigVMEditorAssetInterfacePtr InBlueprint);`
- L150 _private prototype_ `void HandleSetObjectBeingDebugged(UObject* InObject);`
- L152 _private prototype_ `TSharedRef<SWidget> OnGetOptionsMenu();`
- L153 _private prototype_ `void OnFilterTextChanged(const FText& SearchText);`
- L156 _private prototype_ `TArray<FName> GetSelectedModuleNames() const;` — Gets the currently selected module names
- L158 _private member_ `FText FilterText;`
- L160 _private member_ `TSharedPtr<SSearchBox> FilterBox;`
- L161 _private member_ `bool bKeepCurrentEditedConnectors = false;`
- L162 _private member_ `TSet<FName> CurrentlyEditedConnectors;`
- L165 _private member_ `FName ViewName;` — The name of this view to clearly identify it amongst other rig hierarchies in the control rig editor
- L168 _private member_ `TSharedPtr<FModularRigHierarchyViewModel> ViewModel;` — A model for this view

#### Free symbols / members of external scopes

- L21 _namespace_ `namespace UE`
- L21 _namespace_ `namespace ControlRigEditor` (scope `UE`)

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/Editor/Hierarchy/Views/SRigHierarchy.h` (Private)


#### class `SRigHierarchy`  
`class SRigHierarchy : public SCompoundWidget, public FEditorUndoClient`  
_L23-259_
- inherits: `SCompoundWidget,FEditorUndoClient`
- desc: Widget allowing editing of a control rig's structure
- L26 _public function_ `SLATE_BEGIN_ARGS(SRigHierarchy) : _ForModalWindow(false)`
- L31 _public prototype_ `SLATE_ARGUMENT(bool, ForModalWindow) SLATE_END_ARGS() ~SRigHierarchy();` — Disables features that don't work in modal windows due to the absence of the game ticker and frame numbers
- L44 _public prototype_ `void Construct(const FArguments& InArgs, TSharedRef<IControlRigBaseEditor> InControlRigEditor, const FName& InViewName);` — Constructs this widget @param InArgs				Slate Arguments @param InControlRigEditor	The control rig editor that displays this view @param InViewName			The name of this view to clearly identify it amongst other rig hierarchies in the control rig editor
- L46 _public function_ `IControlRigBaseEditor* GetControlRigEditor() const`
- L57 _private prototype_ `void OnEditorClose(IControlRigBaseEditor* InEditor, FControlRigAssetInterfacePtr InBlueprint);`
- L60 _private prototype_ `void BindCommands();` — Bind commands that this widget handles
- L63 _private prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent);` — SWidget interface
- L64 _private prototype_ `virtual FReply OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L67 _private prototype_ `void RefreshTreeView(bool bRebuildContent = true);` — Rebuild the tree view
- L70 _private prototype_ `TArray<FRigHierarchyKey> GetSelectedKeys() const;` — Return all selected keys
- L73 _private prototype_ `TArray<FRigElementKey> GetSelectedElementKeys() const;` — Return all selected element keys
- L76 _private prototype_ `bool CanDeleteItem() const;` — Check whether we can deleting the selected item(s)
- L79 _private prototype_ `void HandleDeleteItem();` — Delete Item
- L82 _private prototype_ `void HandleNewItem(ERigElementType InElementType, bool bIsAnimationChannel);` — Create a new item
- L85 _private prototype_ `bool CanFindReferencesOfItem() const;` — Check we can find the references of an item
- L88 _private prototype_ `void HandleFindReferencesOfItem();` — Find all references of an item
- L91 _private prototype_ `bool CanDuplicateItem() const;` — Check whether we can deleting the selected item(s)
- L94 _private prototype_ `void HandleDuplicateItem();` — Duplicate Item
- L97 _private prototype_ `void HandleMirrorItem();` — Mirror Item
- L100 _private prototype_ `bool CanRenameItem() const;` — Check whether we can deleting the selected item(s)
- L103 _private prototype_ `void HandleRenameItem();` — Rename Item
- L105 _private prototype_ `bool CanPasteItems() const;`
- L106 _private prototype_ `bool CanCopyOrPasteItems() const;`
- L107 _private prototype_ `void HandleCopyItems();`
- L108 _private prototype_ `void HandlePasteItems();`
- L109 _private prototype_ `void HandlePasteLocalTransforms();`
- L110 _private prototype_ `void HandlePasteGlobalTransforms();`
- L111 _private prototype_ `void HandlePasteTransforms(ERigTransformType::Type InTransformType, bool bAffectChildren);`
- L114 _private prototype_ `void OnSelectionChanged(TSharedPtr<FRigHierarchyTreeElement> Selection, ESelectInfo::Type SelectInfo);` — Set Selection Changed
- L116 _private prototype_ `TSharedRef< SWidget > CreateFilterMenu();`
- L117 _private prototype_ `TSharedPtr< SWidget > CreateContextMenuWidget();`
- L118 _private prototype_ `void OnItemClicked(TSharedPtr<FRigHierarchyTreeElement> InItem);`
- L119 _private prototype_ `void OnItemDoubleClicked(TSharedPtr<FRigHierarchyTreeElement> InItem);`
- L120 _private prototype_ `void OnSetExpansionRecursive(TSharedPtr<FRigHierarchyTreeElement> InItem, bool bShouldBeExpanded);`
- L121 _private prototype_ `TOptional<FText> OnGetItemTooltip(const FRigHierarchyKey& InKey) const;`
- L124 _private prototype_ `virtual void PostUndo(bool bSuccess) override;` — FEditorUndoClient
- L125 _private prototype_ `virtual void PostRedo(bool bSuccess) override;`
- L128 _private prototype_ `FReply OnDragDetected(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent);` — reply to a drag operation
- L129 _private prototype_ `TOptional<EItemDropZone> OnCanAcceptDrop(const FDragDropEvent& DragDropEvent, EItemDropZone DropZone, TSharedPtr<FRigHierarchyTreeElement> TargetItem);`
- L130 _private prototype_ `FReply OnAcceptDrop(const FDragDropEvent& DragDropEvent, EItemDropZone DropZone, TSharedPtr<FRigHierarchyTreeElement> TargetItem);`
- L131 _private prototype_ `void OnElementKeyTagDragDetected(const FRigElementKey& InDraggedTag);`
- L132 _private prototype_ `void UpdateConnectorMatchesOnDrag(const TArray<FRigHierarchyKey>& InDraggedKeys);`
- L134 _private member_ `static const FName ContextMenuName;`
- L135 _private prototype_ `static void CreateContextMenu();`
- L136 _private prototype_ `UToolMenu* GetContextMenu();`
- L137 _private prototype_ `TSharedPtr<FUICommandList> GetContextMenuCommands() const;`
- L139 _private member_ `static const FName DragDropMenuName;`
- L140 _private prototype_ `static void CreateDragDropMenu();`
- L141 _private prototype_ `UToolMenu* GetDragDropMenu(const TArray<FRigHierarchyKey>& DraggedKeys, FRigElementKey TargetKey);`
- L144 _private member_ `TWeakPtr<IControlRigBaseEditor> ControlRigEditor;` — Our owning control rig editor
- L146 _private member_ `FRigHierarchyTreeDisplaySettings DisplaySettings;`
- L147 _private function_ `const FRigHierarchyTreeDisplaySettings& GetDisplaySettings() const`
- L150 _private member_ `FRigHierarchyImportSettings ImportSettings;` — struct for import hierarchy dialog (not on stack to allow non-modal dialog)
- L153 _private member_ `TSharedPtr<SSearchBox> FilterBox;` — Search box widget
- L155 _private prototype_ `EVisibility IsToolbarVisible() const;`
- L156 _private prototype_ `EVisibility IsSearchbarVisible() const;`
- L157 _private prototype_ `FReply OnImportSkeletonClicked();`
- L158 _private prototype_ `FText GetImportHierarchyText() const;`
- L159 _private prototype_ `bool IsImportHierarchyEnabled() const;`
- L160 _private prototype_ `void OnFilterTextChanged(const FText& SearchText);`
- L163 _private member_ `TSharedPtr<SRigHierarchyTreeView> TreeView;` — Tree view widget
- L165 _private member_ `TWeakInterfacePtr<IControlRigEditorAssetInterface> ControlRigBlueprint;`
- L166 _private member_ `TWeakObjectPtr<UControlRig> ControlRigBeingDebuggedPtr;`
- L169 _private member_ `TSharedPtr<FUICommandList> CommandList;` — Command list we bind to
- L171 _private prototype_ `bool IsMultiSelected(bool bIncludeProcedural) const;`
- L172 _private prototype_ `bool IsSingleSelected(bool bIncludeProcedural) const;`
- L173 _private prototype_ `bool IsSingleBoneSelected(bool bIncludeProcedural) const;`
- L174 _private prototype_ `bool IsSingleNullSelected(bool bIncludeProcedural) const;`
- L175 _private prototype_ `bool IsControlSelected(bool bIncludeProcedural) const;`
- L176 _private prototype_ `bool IsControlOrNullSelected(bool bIncludeProcedural) const;`
- L177 _private prototype_ `bool IsProceduralSelected() const;`
- L178 _private prototype_ `bool IsNonProceduralSelected() const;`
- L179 _private prototype_ `bool CanAddElement(const ERigElementType ElementType) const;`
- L180 _private prototype_ `bool CanAddAnimationChannel() const;`
- L182 _private prototype_ `URigHierarchy* GetHierarchy() const;`
- L183 _private prototype_ `URigHierarchy* GetDefaultHierarchy() const;`
- L184 _private function_ `const URigHierarchy* GetHierarchyForTreeView() const`
- L185 _private prototype_ `FRigHierarchyKey OnGetResolvedKey(const FRigHierarchyKey& InKey);`
- L186 _private prototype_ `void OnRequestDetailsInspection(const FRigHierarchyKey& InKey);`
- L188 _private prototype_ `void ImportHierarchy(const FAssetData& InAssetData);`
- L189 _private prototype_ `void CreateImportMenu(FMenuBuilder& MenuBuilder);`
- L190 _private prototype_ `void CreateRefreshMenu(FMenuBuilder& MenuBuilder);`
- L191 _private prototype_ `void CreateResetCurvesMenu(FMenuBuilder& MenuBuilder);`
- L192 _private prototype_ `bool ShouldFilterOnImport(const FAssetData& AssetData) const;`
- L193 _private prototype_ `void RefreshHierarchy(const FAssetData& InAssetData, bool bOnlyResetCurves, bool bRestrictToMeshBones);`
- L194 _private prototype_ `void UpdateMesh(USkeletalMesh* InMesh, const bool bImport) const;`
- L196 _private prototype_ `void HandleResetTransform(bool bSelectionOnly);`
- L199 _private prototype_ `void HandleZeroControls();` — Sets the transform of the control as offset, zeroes the initial and current transform
- L200 _private prototype_ `bool CanHandleZeroControls() const;`
- L203 _private prototype_ `void HandleZeroControlsFromClosestBone();` — Sets the offset to the transform of the closest bone, zeroes the initial and current transform
- L204 _private prototype_ `bool CanHandleZeroControlsFromClosestBone() const;`
- L207 _private prototype_ `void HandleZeroControlShape();` — Sets the current shape relative to the control's offset, zeroes the control's initial and current transform
- L208 _private prototype_ `bool CanHandleZeroControlShape() const;`
- L211 _private prototype_ `void HandleSetInitialTransformsAsCurrent();` — Set the current transform of selected bone, null or connector as its initial and current transform
- L212 _private prototype_ `bool CanHandleSetInitialTransformsAsCurrent() const;`
- L214 _private prototype_ `void HandleFrameSelection(const bool bFrameInViewport);`
- L215 _private prototype_ `void HandleControlBoneOrSpaceTransform();`
- L216 _private prototype_ `void HandleUnparent();`
- L217 _private prototype_ `bool FindClosestBone(const FVector& Point, FName& OutRigElementName, FTransform& OutGlobalTransform) const;`
- L218 _private prototype_ `void HandleTestSpaceSwitching();`
- L220 _private prototype_ `void HandleParent(const FToolMenuContext& Context);`
- L221 _private prototype_ `void HandleAlign(const FToolMenuContext& Context);`
- L222 _private prototype_ `FReply ReparentOrMatchTransform(const TArray<FRigHierarchyKey>& DraggedKeys, FRigHierarchyKey TargetKey, bool bReparentItems, int32 LocalIndex = INDEX_NONE);`
- L223 _private prototype_ `FReply ResolveConnector(const FRigElementKey& DraggedKey, const FRigElementKey& TargetKey);`
- L224 _private prototype_ `FReply ResolveConnectorToArray(const FRigElementKey& DraggedKey, const TArray<FRigElementKey>& TargetKeys);`
- L226 _private prototype_ `FName CreateUniqueName(const FName& InBaseName, ERigElementType InElementType) const;`
- L228 _private prototype_ `void ClearDetailPanel() const;`
- L230 _private member_ `bool bIsChangingRigHierarchy;`
- L231 _private prototype_ `void OnHierarchyModified(ERigHierarchyNotification InNotif, URigHierarchy* InHierarchy, const FRigNotificationSubject& InSubject);`
- L232 _private prototype_ `void OnHierarchyModified_AnyThread(ERigHierarchyNotification InNotif, URigHierarchy* InHierarchy, const FRigNotificationSubject& InSubject);`
- L233 _private prototype_ `void OnModularRigModified(EModularRigNotification InNotif, const FRigModuleReference* InModule);`
- L234 _private prototype_ `void HandleRefreshEditorFromBlueprint(FRigVMEditorAssetInterfacePtr InBlueprint);`
- L235 _private prototype_ `void HandleSetObjectBeingDebugged(UObject* InObject);`
- L236 _private prototype_ `void OnPreConstruction_AnyThread(UControlRig* InRig, const FName& InEventName);`
- L237 _private prototype_ `void OnPostConstruction_AnyThread(UControlRig* InRig, const FName& InEventName);`
- L238 _private prototype_ `void OnNavigateToFirstConnectorWarning();`
- L240 _private member_ `bool bIsConstructionEventRunning;`
- L241 _private member_ `bool bRestrictRefreshToMeshBones = false;`
- L242 _private member_ `uint32 LastHierarchyHash;`
- L243 _private member_ `TArray<FRigHierarchyKey> SelectionBeforeConstruction;`
- L244 _private member_ `TMap<FRigElementKey, FModularRigResolveResult> DragRigResolveResults;`
- L247 _public prototype_ `FName HandleRenameElement(const FRigHierarchyKey& OldKey, const FString& NewName);`
- L248 _public prototype_ `bool HandleVerifyNameChanged(const FRigHierarchyKey& OldKey, const FString& NewName, FText& OutErrorMessage);`
- L251 _public prototype_ `virtual FReply OnDrop(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;` — SWidget Overrides
- L254 _public member_ `FName ViewName;` — The name of this view to clearly identify it amongst other rig hierarchies in the control rig editor

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/Editor/Hierarchy/Widgets/SModularRigHierarchySearchableTreeView.h` (Private)


#### class `SModularRigHierarchySearchableTreeView`  
`class SModularRigHierarchySearchableTreeView : public SCompoundWidget`  
_L11-37_
- inherits: `SCompoundWidget`
- L13 _private typedef_ `using FModularRigHierarchyViewModel = UE::ControlRigEditor::FModularRigHierarchyViewModel;`
- L17 _public function_ `SLATE_BEGIN_ARGS(SModularRigHierarchySearchableTreeView)`
- L18 _public prototype_ `SLATE_ARGUMENT(FModularRigHierarchyTreeDelegates, RigTreeDelegates) SLATE_ARGUMENT(FText, InitialFilterText) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<FModularRigHierarchyViewModel>& InViewModel, const FName& InViewName);`
- L31 _public prototype_ `virtual ~SModularRigHierarchySearchableTreeView() = default;`
- L32 _public function_ `TSharedRef<SModularRigHierarchyTreeView> GetTreeView() const`
- L36 _private member_ `TSharedPtr<SModularRigHierarchyTreeView> TreeView;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace ControlRigEditor` (scope `UE`)

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/Editor/Hierarchy/Widgets/SModularRigHierarchyTreeItem.h` (Private)


#### class `SModularRigHierarchyTreeItem`  
`class SModularRigHierarchyTreeItem : public SMultiColumnTableRow<TSharedPtr<FModularRigHierarchyTreeElement>>`  
_L16-87_
- inherits: `SMultiColumnTableRow<TSharedPtr<FModularRigHierarchyTreeElement>>`
- L19 _private typedef_ `using Super = SMultiColumnTableRow<TSharedPtr<FModularRigHierarchyTreeElement>>;`
- L25 _public prototype_ `void Construct( const FArguments& InArgs, const TSharedRef<STableViewBase>& OwnerTable, const TSharedRef<FModularRigHierarchyTreeElement>& InRigTreeElement, const TSharedPtr<SModularRigHierarchyTreeView>& InTreeView, bool bPinned);`
- L32 _public prototype_ `bool OnConnectorTargetChanged(TArray<FRigElementKey> InTargets, const FRigElementKey InConnectorKey);`
- L34 _public prototype_ `void OnNameCommitted(const FText& InText, ETextCommit::Type InCommitType) const;`
- L35 _public prototype_ `bool OnVerifyNameChanged(const FText& InText, FText& OutErrorMessage);`
- L37 _public prototype_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& ColumnName) override;`
- L41 _protected prototype_ `virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L46 _private prototype_ `TSharedRef<SWidget> CreateModuleNameWidget();` — Creates the widget for the module column
- L49 _private prototype_ `TSharedRef<SWidget> CreateWarningsWidget();` — Creates the widget for the warnings column
- L52 _private prototype_ `TSharedRef<SWidget> CreateConnectorWidget();` — Creates the widget for the connector column
- L55 _private prototype_ `TSharedRef<SWidget> CreateModuleClassWidget();` — Creates the widget for the module class column
- L58 _private prototype_ `TSharedRef<SWidget> CreateModuleTagsWidget();` — Creates the widget for the module tags column
- L60 _private prototype_ `TArray<FRigElementKey> GetTargetKeys() const;`
- L63 _private prototype_ `FText GetModuleName(bool bUseShortName) const;` — Returns the name of the module displayed in this row
- L66 _private prototype_ `FText GetModuleNameTooltip() const;` — Returns the tooltip displayed when the module name is hovered
- L69 _private prototype_ `FText GetModuleAssetName() const;` — Returns the name of the module asset displayed in this row
- L72 _private prototype_ `const TScriptInterface<const IRigVMEditorAssetInterface> GetModuleRigVMAsset() const;` — Returns the rig vm asset of the module displayed in this row, or nullptr if no module blueprint can be found
- L75 _private member_ `TWeakPtr<FModularRigHierarchyTreeElement> WeakRigTreeElement;` — The tree element being displayed in this widget
- L78 _private member_ `TWeakPtr<SModularRigHierarchyTreeView> WeakTreeView;` — The tree view that displays this widget
- L80 _private member_ `FModularRigHierarchyTreeDelegates Delegates;`
- L81 _private member_ `TSharedPtr<SRigHierarchySearchableTreeView> ConnectorComboBox;`
- L82 _private member_ `TSharedPtr<SButton> ResetConnectorButton;`
- L83 _private member_ `TSharedPtr<SButton> UseSelectedButton;`
- L84 _private member_ `TSharedPtr<SButton> SelectElementButton;`
- L85 _private member_ `FRigElementKey ConnectorKey;`
- L86 _private member_ `TOptional<FModularRigResolveResult> ConnectorMatches;`

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/Editor/Hierarchy/Widgets/SModularRigHierarchyTreeView.h` (Private)


#### class `SModularRigHierarchyTreeView`  
`class SModularRigHierarchyTreeView : public STreeView<TSharedPtr<FModularRigHierarchyTreeElement>>`  
_L24-163_
- inherits: `STreeView<TSharedPtr<FModularRigHierarchyTreeElement>>`
- L26 _private typedef_ `using FControlRigShowSchematicViewportOverride = UE::ControlRigEditor::FControlRigShowSchematicViewportOverride;`
- L27 _private typedef_ `using FModularRigHierarchyViewModel = UE::ControlRigEditor::FModularRigHierarchyViewModel;`
- L28 _private typedef_ `using FOnRigHierarchyTreePersistentStateRestored = UE::ControlRigEditor::FOnRigHierarchyTreePersistentStateRestored;`
- L32 _public member_ `static const FName Column_ModuleName;`
- L33 _public member_ `static const FName Column_Warnings;`
- L34 _public member_ `static const FName Column_Connector;`
- L35 _public member_ `static const FName Column_ModuleClass;`
- L36 _public member_ `static const FName Column_ModuleTags;`
- L38 _public function_ `SLATE_BEGIN_ARGS(SModularRigHierarchyTreeView) : _AutoScrollEnabled(false) , _FilterText()`
- L42 _public prototype_ `SLATE_ARGUMENT( TSharedPtr<SHeaderRow>, HeaderRow ) SLATE_ARGUMENT(FModularRigHierarchyTreeDelegates, RigTreeDelegates) SLATE_ARGUMENT(bool, AutoScrollEnabled) SLATE_ATTRIBUTE(FText, FilterText) SLATE_END_ARGS() virtual ~SModularRigHierarchyTreeView();`
- L57 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<FModularRigHierarchyViewModel>& ViewModel, const FName& InViewName);` — Constructs this widget @param InArgs			Slate Arguments @param ViewModel			The model for the Modular Rig Hierarchy View this tree resides in @param InViewName		The name of this view to clearly identify it amongst other rig hierarchies in the control rig editor
- L60 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;` — Performs auto scroll
- L62 _public member_ `bool bRequestRenameSelected = false;`
- L66 _public function_ `void SaveAndClearSparseItemInfos()` — `UE_DEPRECATED(5.8, "Should not be used anymore. The tree uses the RigHierarchyTreePersistentStateStore to retain its state")` — Save a snapshot of the internal map that tracks item expansion before tree reconstruction
- L80 _public function_ `void RestoreSparseItemInfos(TSharedPtr<FModularRigHierarchyTreeElement> ItemPtr)` — `UE_DEPRECATED(5.8, "Should not be used anymore. The tree uses the RigHierarchyTreePersistentStateStore to retain its state")` — Restore the expansion infos map from the saved snapshot after tree reconstruction
- L95 _public prototype_ `TSharedPtr<FModularRigHierarchyTreeElement> FindElement(const FString& InElementKey);`
- L96 _public prototype_ `static TSharedPtr<FModularRigHierarchyTreeElement> FindElement(const FString& InElementKey, TSharedPtr<FModularRigHierarchyTreeElement> CurrentItem);`
- L97 _public prototype_ `bool AddElement(FString InKey, FString InParentKey = FString(), bool bApplyFilterText = true);`
- L98 _public prototype_ `bool AddElement(const FRigModuleInstance* InElement, bool bApplyFilterText);`
- L99 _public prototype_ `void AddSpacerElement();`
- L100 _public prototype_ `bool ReparentElement(const FString InKey, const FString InParentKey);`
- L101 _public prototype_ `void RefreshTreeView(const bool bRebuildContent = true, const FOnRigHierarchyTreePersistentStateRestored& OnStateRestored = FOnRigHierarchyTreePersistentStateRestored());`
- L102 _public prototype_ `TSharedRef<ITableRow> MakeTableRowWidget(TSharedPtr<FModularRigHierarchyTreeElement> InItem, const TSharedRef<STableViewBase>& OwnerTable, bool bPinned);`
- L103 _public prototype_ `void HandleGetChildrenForTree(TSharedPtr<FModularRigHierarchyTreeElement> InItem, TArray<TSharedPtr<FModularRigHierarchyTreeElement>>& OutChildren);`
- L105 _public prototype_ `TArray<FName> GetSelectedModuleNames() const;`
- L106 _public prototype_ `void SetSelection(const TArray<TSharedPtr<FModularRigHierarchyTreeElement>>& InSelection, const ESelectInfo::Type SelectInfo);`
- L107 _public function_ `const TArray<TSharedPtr<FModularRigHierarchyTreeElement>>& GetRootElements() const`
- L108 _public function_ `FModularRigHierarchyTreeDelegates& GetRigTreeDelegates()`
- L111 _public prototype_ `const TSharedPtr<FModularRigHierarchyTreeElement>* FindItemAtPosition(FVector2D InScreenSpacePosition) const;` — Given a position, return the item under that position. If nothing is there, return null.
- L115 _private prototype_ `void OnSelectionChanged(TSharedPtr<FModularRigHierarchyTreeElement> Selection, ESelectInfo::Type SelectInfo);` — Called when the tree selection changed
- L118 _private prototype_ `void OnModularRigControllerModified(EModularRigNotification Notif, const FRigModuleReference* Module);` — Called when the modular rig controller was modified
- L121 _private prototype_ `void OnPostCompileModularRigs(FRigVMEditorAssetInterfacePtr InBlueprint);` — Called after modular rigs were compiled
- L124 _private prototype_ `void SetExpansionRecursive(TSharedPtr<FModularRigHierarchyTreeElement> InItem, bool bShouldBeExpanded);` — Called when the user shift clicks the expand button, so children are expanded/collapsed along with their parent
- L128 _private member_ `TSparseItemMap OldSparseItemInfos;` — `UE_DEPRECATED(5.8, "Use RigHierarchyTreePersistentStateStore to retain the tree state")` — A temporary snapshot of the SparseItemInfos in STreeView, used during RefreshTreeView()
- L131 _private member_ `TWeakPtr<FModularRigHierarchyViewModel> WeakViewModel;` — View model for the Modular Rig Hierchy view that draws this tree
- L134 _private member_ `TArray<TSharedPtr<FModularRigHierarchyTreeElement>> RootElements;` — Backing array for tree view
- L137 _private member_ `TMap<FString, TSharedPtr<FModularRigHierarchyTreeElement>> ElementMap;` — A map for looking up items based on their key
- L140 _private member_ `TMap<FString, FString> ParentMap;` — A map for looking up a parent based on their key
- L142 _private member_ `FModularRigHierarchyTreeDelegates Delegates;`
- L144 _private member_ `bool bAutoScrollEnabled = false;`
- L145 _private member_ `FVector2D LastMousePosition = FVector2D::ZeroVector;`
- L146 _private member_ `double TimeAtMousePosition = 0.0;`
- L148 _private member_ `TAttribute<FText> FilterText;`
- L151 _private member_ `FControlRigShowSchematicViewportOverride ShowSchematicViewportOverride;` — Overrides the per project per user schematic viewport visibility
- L154 _private member_ `bool bIsPerformingSelection = false;` — True while this treeview is selecting
- L157 _private member_ `bool bRebuildContentRequested = false;` — True when rebuild content is requested but not yet carried out
- L160 _private member_ `FName ViewName;` — The name of this view to clearly identify it amongst other rig hierarchies in the control rig editor

#### Free symbols / members of external scopes

- L19 _typedef_ `using FRigVMEditorAssetInterfacePtr = TScriptInterface<IRigVMEditorAssetInterface>;`
- L22 _namespace_ `namespace UE`
- L22 _namespace_ `namespace ControlRigEditor` (scope `UE`)

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/Editor/Hierarchy/Widgets/SRigHierarchyItem.h` (Private)


#### class `SRigHierarchyItem`  
`class SRigHierarchyItem : public STableRow<TSharedPtr<FRigHierarchyTreeElement>>`  
_L14-33_
- inherits: `STableRow<TSharedPtr<FRigHierarchyTreeElement>>`
- L18 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& OwnerTable, TSharedRef<FRigHierarchyTreeElement> InRigTreeElement, TSharedPtr<SRigHierarchyTreeView> InTreeView, const FRigHierarchyTreeDisplaySettings& InSettings, bool bPinned);`
- L19 _public prototype_ `void OnNameCommitted(const FText& InText, ETextCommit::Type InCommitType) const;`
- L20 _public prototype_ `bool OnVerifyNameChanged(const FText& InText, FText& OutErrorMessage);`
- L21 _public prototype_ `static TPair<const FSlateBrush*, FSlateColor> GetBrushForElementType(const URigHierarchy* InHierarchy, const FRigHierarchyKey& InKey);`
- L22 _public prototype_ `static FLinearColor GetColorForControlType(ERigControlType InControlType, UEnum* InControlEnum);`
- L25 _private member_ `TWeakPtr<FRigHierarchyTreeElement> WeakRigTreeElement;`
- L26 _private member_ `FRigHierarchyTreeDelegates Delegates;`
- L28 _private prototype_ `FText GetNameForUI() const;`
- L29 _private prototype_ `FText GetName(EElementNameDisplayMode InNameDisplayMode) const;`
- L30 _private prototype_ `FText GetItemTooltip() const;`

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/Editor/Hierarchy/Widgets/SRigHierarchySearchableTreeView.h` (Private)


#### class `SRigHierarchySearchableTreeView`  
`class SRigHierarchySearchableTreeView : public SCompoundWidget`  
_L14-54_
- inherits: `SCompoundWidget`
- L18 _public function_ `SLATE_BEGIN_ARGS(SRigHierarchySearchableTreeView)`
- L21 _public prototype_ `SLATE_ARGUMENT(FRigHierarchyTreeDelegates, RigTreeDelegates) SLATE_ARGUMENT(FText, InitialFilterText) SLATE_ARGUMENT(bool, ForModalWindow) SLATE_END_ARGS() void Construct( const FArguments& InArgs, const FName& InViewName, const TSharedPtr<IControlRigBaseEditor>& InControlRigEditor = nullptr);`
- L41 _public function_ `TSharedRef<SSearchBox> GetSearchBox() const`
- L42 _public function_ `TSharedRef<SRigHierarchyTreeView> GetTreeView() const`
- L43 _public prototype_ `const FRigHierarchyTreeDisplaySettings& GetDisplaySettings();`
- L47 _private prototype_ `void OnFilterTextChanged(const FText& SearchText);`
- L49 _private member_ `FOnGetRigTreeDisplaySettings SuperGetRigTreeDisplaySettings;`
- L50 _private member_ `FText FilterText;`
- L51 _private member_ `FRigHierarchyTreeDisplaySettings Settings;`
- L52 _private member_ `TSharedPtr<SSearchBox> SearchBox;`
- L53 _private member_ `TSharedPtr<SRigHierarchyTreeView> TreeView;`

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/Editor/Hierarchy/Widgets/SRigHierarchyTagWidget.h` (Private)


#### class `SRigHierarchyTagWidget`  
`class SRigHierarchyTagWidget : public SCompoundWidget`  
_L13-70_
- inherits: `SCompoundWidget`
- L16 _public function_ `SLATE_BEGIN_ARGS(SRigHierarchyTagWidget) : _Text() , _TooltipText() , _Icon(nullptr) , _Color(FLinearColor(.2f, .2f, .2f)) , _IconColor(FLinearColor::White) , _TextColor(FLinearColor(.8f, .8f, .8f)) , _Radius(5) , _Identifier() , _AllowDragDrop(false) , _OnClicked() , _OnRenamed() , _OnVerifyRename()`
- L30 _public prototype_ `SLATE_ATTRIBUTE(FText, Text) SLATE_ATTRIBUTE(FText, TooltipText) SLATE_ATTRIBUTE(const FSlateBrush*, Icon) SLATE_ATTRIBUTE(TOptional<FVector2d>, IconSize) SLATE_ATTRIBUTE(FLinearColor, Color) SLATE_ATTRIBUTE(FSlateColor, IconColor) SLATE_ATTRIBUTE(FSlateColor, TextColor) SLATE_ARGUMENT(float, Radius) SLATE_ATTRIBUTE(FString, Identifier) SLATE_ARGUMENT(bool, AllowDragDrop) SLATE_EVENT(FSimpleDelegate, OnClicked) SLATE_EVENT(FOnTextCommitted, OnRenamed) SLATE_EVENT(FOnVerifyTextChanged, OnVerifyRename) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L46 _public prototype_ `virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;`
- L47 _public prototype_ `virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L48 _public prototype_ `virtual FReply OnDragDetected(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L50 _public function_ `FOnRigTreeElementKeyTagDragDetected& OnElementKeyDragDetected()`
- L53 _private prototype_ `void HandleElementRenamed(const FText& InNewName, ETextCommit::Type InCommitType);`
- L54 _private prototype_ `bool HandleVerifyRename(const FText& InText, FText& OutError);`
- L56 _private member_ `TAttribute<FText> Text;`
- L57 _private member_ `TAttribute<const FSlateBrush*> Icon;`
- L58 _private member_ `TAttribute<FLinearColor> Color;`
- L59 _private member_ `TAttribute<FSlateColor> IconColor;`
- L60 _private member_ `float Radius = 5.f;`
- L61 _private member_ `FMargin CombinedPadding;`
- L62 _private member_ `TAttribute<FString> Identifier;`
- L63 _private member_ `bool bAllowDragDrop = false;`
- L64 _private member_ `FSimpleDelegate OnClicked;`
- L65 _private member_ `FOnRigTreeElementKeyTagDragDetected OnElementKeyDragDetectedDelegate;`
- L66 _private member_ `FOnTextCommitted OnRenamed;`
- L67 _private member_ `FOnVerifyTextChanged OnVerifyRename;`

#### Free symbols / members of external scopes

- L11 _delegate_ `DECLARE_DELEGATE_OneParam(FOnRigTreeElementKeyTagDragDetected, const FRigElementKey&);`
- L11 _prototype_ `DECLARE_DELEGATE_OneParam(FOnRigTreeElementKeyTagDragDetected, const FRigElementKey&);`

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/Editor/Hierarchy/Widgets/SRigHierarchyTreeView.h` (Private)


#### class `SRigHierarchyTreeView`  
`class SRigHierarchyTreeView : public STreeView<TSharedPtr<FRigHierarchyTreeElement>>`  
_L18-163_
- inherits: `STreeView<TSharedPtr<FRigHierarchyTreeElement>>`
- L20 _private typedef_ `using FOnRigHierarchyTreePersistentStateRestored = UE::ControlRigEditor::FOnRigHierarchyTreePersistentStateRestored;`
- L24 _public function_ `SLATE_BEGIN_ARGS(SRigHierarchyTreeView) : _AutoScrollEnabled(false) , _PopulateOnConstruct(false) , _ForModalWindow(false)`
- L29 _public prototype_ `SLATE_ARGUMENT(FRigHierarchyTreeDelegates, RigTreeDelegates) SLATE_ARGUMENT(bool, AutoScrollEnabled) SLATE_ARGUMENT(bool, PopulateOnConstruct) SLATE_ARGUMENT(bool, ForModalWindow) SLATE_END_ARGS() virtual ~SRigHierarchyTreeView();`
- L47 _public prototype_ `void Construct( const FArguments& InArgs, const FName& InViewName, const TSharedPtr<IControlRigBaseEditor>& InControlRigEditor = nullptr);` — Constructs this widget @param InArgs				Slate Arguments @param InViewName			The name of this view to clearly identify it amongst other rig hierarchies in the control rig editor @param InControlRigEditor	(optional) The editor that displays this widget. When set, supends details updates during tree refresh.
- L53 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;` — Performs auto scroll
- L55 _public function_ `virtual FReply OnFocusReceived(const FGeometry& MyGeometry, const FFocusEvent& InFocusEvent) override`
- L64 _public member_ `uint32 LastClickCycles = 0;`
- L68 _public function_ `void SaveAndClearSparseItemInfos()` — `UE_DEPRECATED(5.8, "Should not be used anymore. The tree uses the RigHierarchyTreePersistentStateStore to retain its state")` — Save a snapshot of the internal map that tracks item expansion before tree reconstruction
- L82 _public function_ `void RestoreSparseItemInfos(TSharedPtr<FRigHierarchyTreeElement> ItemPtr)` — `UE_DEPRECATED(5.8, "Should not be used anymore. The tree uses the RigHierarchyTreePersistentStateStore to retain its state")` — Restore the expansion infos map from the saved snapshot after tree reconstruction
- L97 _public prototype_ `TSharedPtr<FRigHierarchyTreeElement> FindElement(const FRigHierarchyKey& InElementKey) const;`
- L98 _public prototype_ `static TSharedPtr<FRigHierarchyTreeElement> FindElement(const FRigHierarchyKey& InElementKey, TSharedPtr<FRigHierarchyTreeElement> CurrentItem);`
- L99 _public prototype_ `bool AddElement(FRigHierarchyKey InKey, FRigHierarchyKey InParentKey = FRigHierarchyKey());`
- L100 _public prototype_ `bool AddElement(const FRigBaseElement* InElement);`
- L101 _public prototype_ `bool AddComponent(const FRigBaseComponent* InComponent);`
- L102 _public prototype_ `void AddSpacerElement();`
- L103 _public prototype_ `bool ReparentElement(FRigHierarchyKey InKey, FRigHierarchyKey InParentKey);`
- L104 _public prototype_ `bool RemoveElement(FRigHierarchyKey InKey);`
- L105 _public prototype_ `void RefreshTreeView(const bool bRebuildContent = true, const FOnRigHierarchyTreePersistentStateRestored& OnStateRestored = FOnRigHierarchyTreePersistentStateRestored());`
- L106 _public prototype_ `void SetExpansionRecursive(TSharedPtr<FRigHierarchyTreeElement> InElement, bool bTowardsParent, bool bShouldBeExpanded);`
- L107 _public prototype_ `TSharedRef<ITableRow> MakeTableRowWidget(TSharedPtr<FRigHierarchyTreeElement> InItem, const TSharedRef<STableViewBase>& OwnerTable, bool bPinned);`
- L108 _public prototype_ `void HandleGetChildrenForTree(TSharedPtr<FRigHierarchyTreeElement> InItem, TArray<TSharedPtr<FRigHierarchyTreeElement>>& OutChildren);`
- L109 _public prototype_ `void OnElementKeyTagDragDetected(const FRigElementKey& InDraggedTag);`
- L111 _public prototype_ `TArray<FRigHierarchyKey> GetSelectedKeys() const;`
- L112 _public function_ `const TArray<TSharedPtr<FRigHierarchyTreeElement>>& GetRootElements() const`
- L113 _public function_ `FRigHierarchyTreeDelegates& GetRigTreeDelegates()`
- L116 _public prototype_ `const TSharedPtr<FRigHierarchyTreeElement>* FindItemAtPosition(FVector2D InScreenSpacePosition) const;` — Given a position, return the item under that position. If nothing is there, return null.
- L120 _private prototype_ `void AddConnectorTagToElements( const TArray<TSharedRef<FRigHierarchyTreeElement>> TargetElements, const FRigConnectorElement& ConnectorElement, const UControlRig& ControlRig);` — Addds a connector tag to the tree elements
- L126 _private prototype_ `void AddConnectorResolveWarningTagToElement( const TSharedRef<FRigHierarchyTreeElement> TreeElement, const FRigConnectorElement& ConnectorElement, const UControlRig& ControlRig);` — Adds a warning tag to the tree element indicating the connector could not be resolved
- L133 _private member_ `TSparseItemMap OldSparseItemInfos;` — `UE_DEPRECATED(5.8, "Use RigHierarchyTreePersistentStateStore to retain the tree state")` — A temporary snapshot of the SparseItemInfos in STreeView, used during RefreshTreeView()
- L136 _private member_ `TArray<TSharedPtr<FRigHierarchyTreeElement>> RootElements;` — Backing array for tree view
- L139 _private member_ `TMap<FRigHierarchyKey, TSharedPtr<FRigHierarchyTreeElement>> ElementMap;` — A map for looking up items based on their key
- L142 _private member_ `TMap<FRigHierarchyKey, FRigHierarchyKey> ParentMap;` — A map for looking up a parent based on their key
- L144 _private member_ `FRigHierarchyTreeDelegates Delegates;`
- L146 _private member_ `bool bAutoScrollEnabled;`
- L147 _private member_ `FVector2D LastMousePosition;`
- L148 _private member_ `double TimeAtMousePosition;`
- L151 _private member_ `bool bRebuildContentRequested = false;` — True when rebuild content is requested but not yet carried out
- L154 _private member_ `TWeakPtr<IControlRigBaseEditor> WeakControlRigEditor;` — The editor that displays this widget
- L157 _private member_ `FName ViewName;` — The name of this view to clearly identify it amongst other rig hierarchies in the control rig editor
- L160 _private member_ `bool bForModalWindow = false;` — When true the tree is displayed in a modal window and cannot use FTSTicker anywhere

#### Free symbols / members of external scopes

- L16 _macro_ `#define UE_API CONTROLRIGEDITOR_API`

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/Editor/ModularRigEventQueueCommands.h` (Private)


#### class `FModularRigEventQueueCommands`  
`class FModularRigEventQueueCommands : public TCommands<FModularRigEventQueueCommands>`  
_L8-27_
- inherits: `TCommands<FModularRigEventQueueCommands>`
- L11 _public function_ `FModularRigEventQueueCommands() : TCommands<FModularRigEventQueueCommands> ( "FModularRigEventQueue", NSLOCTEXT("Contexts", "ModularRig", "Event Queue"), NAME_None,`
- L21 _public member_ `TSharedPtr< FUICommandInfo > FocusOnSelection;` — Focuses on a selected event's module
- L26 _public prototype_ `virtual void RegisterCommands() override;` — Initialize commands

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/Editor/ModularRigEventQueueTabSummoner.h` (Private)


#### struct `FModularRigEventQueueTabSummoner`  
`struct FModularRigEventQueueTabSummoner : public FWorkflowTabFactory`  
_L12-25_
- inherits: `FWorkflowTabFactory`
- L16 _public member_ `static inline const FLazyName TabID = FLazyName(TEXT("Even`
- L19 _public prototype_ `FModularRigEventQueueTabSummoner(const TSharedRef<IControlRigBaseEditor>& InControlRigEditor);`
- L21 _public prototype_ `virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& Info) const override;`
- L24 _protected member_ `TWeakPtr<IControlRigBaseEditor> ControlRigEditor;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API CONTROLRIGEDITOR_API`

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/Editor/ModularRigHierarchyConnectorWarning.h` (Private)


#### enum `UE::ControlRigEditor::EModularRigHierarchyConnectorWarningFlags`  
`enum class EModularRigHierarchyConnectorWarningFlags : uint8`  
_L24-49_
- desc: Flags for different warnings
- L27 _public enumerator_ `NoWarning = 0x00` — There is no warning for this element
- L30 _public enumerator_ `MarkedAsInvalid = 0x01` — The module is flagged as invalid in asset variant tags
- L33 _public enumerator_ `NotInModularRigModel = 0x01 << 1` — The module cannot be found in the modular rig model
- L36 _public enumerator_ `NotInModularRig = 0x01 << 2` — The module cannot be found in the modular rig
- L39 _public enumerator_ `NotConnected = 0x01 << 3` — The module is not connected
- L42 _public enumerator_ `ExeedsMinArraySizeRule = 0x01 << 4` — Not enough connections given the array size rule
- L45 _public enumerator_ `ExeedsMaxArraySizeRule = 0x01 << 5` — Too many connections given the array size rule
- L48 _public enumerator_ `MultipleArraySizeRules = 0x01 << 6` — Ambigous array size rules

#### class `UE::ControlRigEditor::FModularRigHierarchyConnectorWarning`  
`class FModularRigHierarchyConnectorWarning : FNoncopyable`  
_L53-122_
- inherits: `FNoncopyable`
- desc: Component to create consistent warnings for a Modular Rig Hierarchy Tree Element
- L61 _public prototype_ `static TSharedPtr<FModularRigHierarchyConnectorWarning> TryCreate( const TSharedRef<IControlRigBaseEditor> InControlRigEditor, const FRigElementKey& InConnectorKey, const FName& InTargetModuleName);` — Tries to create a warning, returns nullptr if there is no warning for this data
- L66 _public function_ `const FText& GetTooltip() const`
- L68 _public function_ `const FSlateBrush* GetBrush() const`
- L70 _public prototype_ `FModularRigHierarchyConnectorWarning( FModularRigHierarchyConnectorWarning::FPrivateToken, const UModularRig& ModularRig, const URigHierarchy& Hierarchy, const FRigConnectorElement& Connector, const FRigModuleInstance& Module);`
- L79 _private prototype_ `void Initialize( const UModularRig& ModularRig, const URigHierarchy& Hierarchy, const FRigConnectorElement& Connector, const FRigModuleInstance& Module);` — Initializes all members
- L86 _private prototype_ `void AddFlagsFromArraySizeRule( const UModularRig& ModularRig, const URigHierarchy& Hierarchy, const FRigConnectorElement& Connector, const FRigModuleInstance& Module);` — Adds flags resulting from the array size rule if any is present
- L93 _private prototype_ `void UpdateTooltipText( const UModularRig& ModularRig, const URigHierarchy& Hierarchy, const FRigConnectorElement& Connector, const FRigModuleInstance& Module);` — Updates the tooltip text member
- L100 _private prototype_ `void UpdateBrush();` — Inits the brush member
- L103 _private prototype_ `const TScriptInterface<const IRigVMEditorAssetInterface> GetModuleRigVMAsset(const FRigModuleInstance& Module);` — Returns the Rig VM Asset of the Module the warning relates to
- L106 _private member_ `EModularRigHierarchyConnectorWarningFlags Flags = EModularRigHierarchyConnectorWarningFlags::NoWarning;` — Warnings flags
- L109 _private member_ `TOptional<int32> MinArraySize;` — If set, the min allowed array size
- L112 _private member_ `TOptional<int32> MaxArraySize;` — If set, the max allowed array size
- L115 _private member_ `FText Tooltip;` — The tooltip text for this warning
- L118 _private member_ `const FSlateBrush* Brush = nullptr;` — The actual icon brush, can be the CustomIconBrush or a common slate brush
- L121 _private member_ `TArray<FRigElementKey> CurrentTargets;` — The current targets of the connector of this element

#### struct `UE::ControlRigEditor::FModularRigHierarchyConnectorWarning::FPrivateToken`  
`struct FPrivateToken`  
_L57-57_
- desc: Prevents from public construction, use TryCreate instead
- L57 _public prototype_ `struct FPrivateToken` — Prevents from public construction, use TryCreate instead

#### Free symbols / members of external scopes

- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace ControlRigEditor` (scope `UE`)
- L50 _prototype_ `ENUM_CLASS_FLAGS(EModularRigHierarchyConnectorWarningFlags);` (scope `UE::ControlRigEditor`)

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/Editor/ModularRigModelTabSummoner.h` (Private)


#### struct `FModularRigModelTabSummoner`  
`struct FModularRigModelTabSummoner : public FWorkflowTabFactory`  
_L10-24_
- inherits: `FWorkflowTabFactory`
- L13 _public member_ `static const FName TabID;`
- L16 _public prototype_ `FModularRigModelTabSummoner(const TSharedRef<IControlRigBaseEditor>& InControlRigEditor);`
- L18 _public prototype_ `virtual FTabSpawnerEntry& RegisterTabSpawner(TSharedRef<FTabManager> TabManager, const FApplicationMode* CurrentApplicationMode) const;`
- L19 _public prototype_ `virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& Info) const override;`
- L20 _public prototype_ `virtual TSharedRef<SDockTab> SpawnTab(const FWorkflowTabSpawnInfo& Info) const override;`
- L23 _protected member_ `TWeakPtr<IControlRigBaseEditor> WeakControlRigEditor;`

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/Editor/RigAnimAttributeTabSummoner.h` (Private)


#### struct `FRigAnimAttributeTabSummoner`  
`struct FRigAnimAttributeTabSummoner : public FWorkflowTabFactory`  
_L10-22_
- inherits: `FWorkflowTabFactory`
- L13 _public member_ `static const FName TabID;`
- L16 _public prototype_ `FRigAnimAttributeTabSummoner(const TSharedRef<IControlRigBaseEditor>& InControlRigEditor);`
- L18 _public prototype_ `virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& Info) const override;`
- L21 _protected member_ `TWeakPtr<IControlRigBaseEditor> ControlRigEditor;`

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/Editor/RigCurveContainerCommands.h` (Private)


#### class `FCurveContainerCommands`  
`class FCurveContainerCommands : public TCommands<FCurveContainerCommands>`  
_L12-30_
- inherits: `TCommands<FCurveContainerCommands>`
- desc: Class containing commands for curve viewer actions
- L15 _public function_ `FCurveContainerCommands() : TCommands<FCurveContainerCommands> ( TEXT("CurveContainer"),`
- L26 _public prototype_ `virtual void RegisterCommands() override;` — Initialize commands
- L29 _public member_ `TSharedPtr< FUICommandInfo > AddCurve;` — Add curve

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/Editor/RigCurveContainerTabSummoner.h` (Private)


#### struct `FRigCurveContainerTabSummoner`  
`struct FRigCurveContainerTabSummoner : public FWorkflowTabFactory`  
_L10-22_
- inherits: `FWorkflowTabFactory`
- L13 _public member_ `static const FName TabID;`
- L16 _public prototype_ `FRigCurveContainerTabSummoner(const TSharedRef<IControlRigBaseEditor>& InControlRigEditor);`
- L18 _public prototype_ `virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& Info) const override;`
- L21 _protected member_ `TWeakPtr<IControlRigBaseEditor> ControlRigEditor;`

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/Editor/RigHierarchyTabSummoner.h` (Private)


#### struct `FRigHierarchyTabSummoner`  
`struct FRigHierarchyTabSummoner : public FWorkflowTabFactory`  
_L10-24_
- inherits: `FWorkflowTabFactory`
- L13 _public member_ `static const FName TabID;`
- L16 _public prototype_ `FRigHierarchyTabSummoner(const TSharedRef<IControlRigBaseEditor>& InControlRigEditor);`
- L18 _public prototype_ `virtual FTabSpawnerEntry& RegisterTabSpawner(TSharedRef<FTabManager> TabManager, const FApplicationMode* CurrentApplicationMode) const;`
- L19 _public prototype_ `virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& Info) const override;`
- L20 _public prototype_ `virtual TSharedRef<SDockTab> SpawnTab(const FWorkflowTabSpawnInfo& Info) const override;`
- L23 _protected member_ `TWeakPtr<IControlRigBaseEditor> ControlRigEditor;`

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/Editor/RigInfluenceMapTabSummoner.h` (Private)


#### struct `FRigInfluenceMapTabSummoner`  
`struct FRigInfluenceMapTabSummoner : public FWorkflowTabFactory`  
_L10-22_
- inherits: `FWorkflowTabFactory`
- L13 _public member_ `static const FName TabID;`
- L16 _public prototype_ `FRigInfluenceMapTabSummoner(const TSharedRef<IControlRigBaseEditor>& InControlRigEditor);`
- L18 _public prototype_ `virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& Info) const override;`
- L21 _protected member_ `TWeakPtr<IControlRigBaseEditor> ControlRigEditor;`

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/Editor/RigModuleAssetBrowserTabSummoner.h` (Private)


#### struct `FRigModuleAssetBrowserTabSummoner`  
`struct FRigModuleAssetBrowserTabSummoner : public FWorkflowTabFactory`  
_L10-20_
- inherits: `FWorkflowTabFactory`
- L13 _public member_ `static const FName TabID;`
- L15 _public prototype_ `FRigModuleAssetBrowserTabSummoner(const TSharedPtr<FAssetEditorToolkit>& InEditorToolkit);`
- L16 _public prototype_ `virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& Info) const override;`
- L17 _public prototype_ `virtual TSharedPtr<SToolTip> CreateTabToolTipWidget(const FWorkflowTabSpawnInfo& Info) const override;`
- L18 _public prototype_ `virtual TSharedRef<SDockTab> SpawnTab(const FWorkflowTabSpawnInfo& Info) const override;`

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/Editor/RigOverrideListTabSummoner.h` (Private)


#### struct `FRigOverrideListTabSummoner`  
`struct FRigOverrideListTabSummoner : public FWorkflowTabFactory`  
_L10-22_
- inherits: `FWorkflowTabFactory`
- L13 _public member_ `static const FName TabID;`
- L16 _public prototype_ `FRigOverrideListTabSummoner(const TSharedRef<IControlRigBaseEditor>& InControlRigEditor);`
- L18 _public prototype_ `virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& Info) const override;`
- L21 _protected member_ `TWeakPtr<IControlRigBaseEditor> ControlRigEditor;`

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/Editor/RigValidationTabSummoner.h` (Private)


#### struct `FRigValidationTabSummoner`  
`struct FRigValidationTabSummoner : public FWorkflowTabFactory`  
_L10-22_
- inherits: `FWorkflowTabFactory`
- L13 _public member_ `static const FName TabID;`
- L16 _public prototype_ `FRigValidationTabSummoner(const TSharedRef<IControlRigBaseEditor>& InControlRigEditor);`
- L18 _public prototype_ `virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& Info) const override;`
- L21 _protected member_ `TWeakPtr<IControlRigBaseEditor> WeakControlRigEditor;`

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/Editor/SControlRigAnimAttributeView.h` (Private)


#### class `SControlRigAnimAttributeView`  
`class SControlRigAnimAttributeView : public SCompoundWidget`  
_L16-38_
- inherits: `SCompoundWidget`
- L18 _private function_ `SLATE_BEGIN_ARGS( SControlRigAnimAttributeView )`
- L23 _private prototype_ `~SControlRigAnimAttributeView();`
- L25 _private prototype_ `void Construct( const FArguments& InArgs, TSharedRef<IControlRigBaseEditor> InControlRigEditor);`
- L27 _private prototype_ `void HandleSetObjectBeingDebugged(UObject* InObject);`
- L29 _private prototype_ `void StartObservingNewControlRig(UControlRig* InControlRig);`
- L30 _private prototype_ `void StopObservingCurrentControlRig();`
- L32 _private prototype_ `void HandleControlRigPostForwardSolve(UControlRig* InControlRig, const FName& InEventName) const;`
- L34 _private member_ `TWeakPtr<IControlRigBaseEditor> ControlRigEditor;`
- L35 _private member_ `TWeakInterfacePtr<IControlRigEditorAssetInterface> ControlRigBlueprint;`
- L36 _private member_ `TWeakObjectPtr<UControlRig> ControlRigBeingDebuggedPtr;`
- L37 _private member_ `TSharedPtr<SAnimAttributeView> AttributeView;`

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/Editor/SControlRigGizmoNameList.h` (Private)


#### class `SControlRigShapeNameList`  
`class SControlRigShapeNameList : public SBox`  
_L13-60_
- inherits: `SBox`
- L17 _public prototype_ `DECLARE_DELEGATE_RetVal( const TArray<TSharedPtr<FRigVMStringWithTag>>&, FOnGetNameListContent );`
- L19 _public function_ `SLATE_BEGIN_ARGS(SControlRigShapeNameList)`
- L21 _public function_ `SLATE_EVENT(FOnGetNameListContent, OnGetNameListContent) SLATE_END_ARGS() UE_DEPRECATED(5.7, "Use void Construct(const FArguments& InArgs, FRigControlElement* ControlElement, FControlRigAssetInterfacePtr InBlueprint); instead") void Construct(const FArguments& InArgs, FRigControlElement* ControlElement, UControlRigBlueprint* InBlueprint)`
- L28 _public function_ `void Construct(const FArguments& InArgs, TArray<FRigControlElement*> ControlElements, UControlRigBlueprint* InBlueprint)` — `UE_DEPRECATED(5.7, "Use void Construct(const FArguments& InArgs, TArray<FRigControlElement*> ControlElements, FControlRigAssetInterfacePtr InBlueprint); instead")`
- L30 _public function_ `void Construct(const FArguments& InArgs, TArray<FRigControlElement> ControlElements, UControlRigBlueprint* InBlueprint)` — `UE_DEPRECATED(5.7, "Use void Construct(const FArguments& InArgs, TArray<FRigControlElement> ControlElements, FControlRigAssetInterfacePtr InBlueprint); instead")`
- L32 _public prototype_ `void Construct(const FArguments& InArgs, FRigControlElement* ControlElement, FControlRigAssetInterfacePtr InBlueprint);`
- L33 _public prototype_ `void Construct(const FArguments& InArgs, TArray<FRigControlElement*> ControlElements, FControlRigAssetInterfacePtr InBlueprint);`
- L34 _public prototype_ `void Construct(const FArguments& InArgs, TArray<FRigControlElement> ControlElements, FControlRigAssetInterfacePtr InBlueprint);`
- L35 _public prototype_ `void BeginDestroy();`
- L39 _protected prototype_ `void ConstructCommon();`
- L41 _protected prototype_ `const TArray<TSharedPtr<FRigVMStringWithTag>>& GetNameList() const;`
- L42 _protected prototype_ `FText GetNameListText() const;`
- L43 _protected prototype_ `virtual void SetNameListText(const FText& NewTypeInValue, ETextCommit::Type CommitInfo);`
- L45 _protected prototype_ `TSharedRef<SWidget> MakeNameListItemWidget(TSharedPtr<FRigVMStringWithTag> InItem);`
- L46 _protected prototype_ `void OnNameListChanged(TSharedPtr<FRigVMStringWithTag> NewSelection, ESelectInfo::Type SelectInfo);`
- L47 _protected prototype_ `void OnNameListComboBox();`
- L49 _protected function_ `static const TArray< TSharedPtr<FRigVMStringWithTag> >& GetEmptyList()`
- L55 _protected member_ `FOnGetNameListContent OnGetNameListContent;`
- L56 _protected member_ `TSharedPtr<SRigVMGraphPinNameListValueWidget> NameListComboBox;`
- L58 _protected member_ `TArray<FRigElementKey> ControlKeys;`
- L59 _protected member_ `FControlRigAssetInterfacePtr Blueprint;`

#### Free symbols / members of external scopes

- L17 _delegate_ `DECLARE_DELEGATE_RetVal( const TArray<TSharedPtr<FRigVMStringWithTag>>&, FOnGetNameListContent );`

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/Editor/SControlRigValidationWidget.h` (Private)


#### class `FControlRigValidationPassItem`  
`class FControlRigValidationPassItem : public TSharedFromThis<FControlRigValidationPassItem>`  
_L22-37_
- inherits: `TSharedFromThis<FControlRigValidationPassItem>`
- L25 _public function_ `FControlRigValidationPassItem(UClass* InClass) : Class(InClass)`
- L33 _public member_ `FText DisplayText;` — The name to display in the UI
- L36 _public member_ `UClass* Class;` — The struct of the rig unit

#### class `SControlRigValidationPassTableRow`  
`class SControlRigValidationPassTableRow : public STableRow<TSharedPtr<FControlRigValidationPassItem>>`  
_L39-53_
- inherits: `STableRow<TSharedPtr<FControlRigValidationPassItem>>`
- L41 _private function_ `SLATE_BEGIN_ARGS(SControlRigValidationPassTableRow)`
- L42 _private prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& OwnerTable, SControlRigValidationWidget* InValidationWidget, TSharedRef<FControlRigValidationPassItem> InPassItem);`
- L45 _private prototype_ `void RefreshDetails(UControlRigValidator* InValidator, UClass* InClass);`
- L49 _private member_ `TSharedPtr<SKismetInspector> KismetInspector;`

#### class `SControlRigValidationWidget`  
`class SControlRigValidationWidget : public SCompoundWidget`  
_L55-85_
- inherits: `SCompoundWidget`
- L58 _public function_ `SLATE_BEGIN_ARGS(SControlRigValidationWidget)`
- L61 _public prototype_ `SControlRigValidationWidget();`
- L62 _public prototype_ `~SControlRigValidationWidget();`
- L64 _public prototype_ `void Construct(const FArguments& InArgs, UControlRigValidator* InValidator);`
- L66 _public prototype_ `TSharedRef<ITableRow> GenerateClassListRow(TSharedPtr<FControlRigValidationPassItem> InItem, const TSharedRef<STableViewBase>& InOwningTable);`
- L67 _public prototype_ `ECheckBoxState IsClassEnabled(UClass* InClass) const;`
- L68 _public prototype_ `EVisibility IsClassVisible(UClass* InClass) const;`
- L69 _public prototype_ `void SetClassEnabled(ECheckBoxState NewState, UClass* InClass);`
- L73 _private prototype_ `void HandleClearMessages();`
- L74 _private prototype_ `void HandleMessageReported(EMessageSeverity::Type InSeverity, const FRigElementKey& InKey, float InQuality, const FString& InMessage);`
- L75 _private prototype_ `void HandleMessageTokenClicked(const TSharedRef<class IMessageToken>& InToken);`
- L77 _private member_ `UControlRigValidator* Validator;`
- L78 _private member_ `TArray<TSharedPtr<FControlRigValidationPassItem>> ClassItems;`
- L79 _private member_ `TMap<UClass*, TSharedRef<SControlRigValidationPassTableRow>> TableRows;`
- L80 _private member_ `TSharedRef<FMessageLogListingModel> ListingModel;`
- L81 _private member_ `TSharedRef<FMessageLogListingViewModel> ListingView;`

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/Editor/SModularRigEventQueueView.h` (Private)


#### class `FModularRigEventEntry`  
`class FModularRigEventEntry : public TSharedFromThis<FModularRigEventEntry>`  
_L18-33_
- inherits: `TSharedFromThis<FModularRigEventEntry>`
- desc: An event in the queue
- L21 _public prototype_ `FModularRigEventEntry(int32 InEventIndex, const FName& InEventName, const FModuleInstanceHandle& InModule, bool InExecuted, double InDurationMicroSeconds);`
- L23 _public prototype_ `TSharedRef<ITableRow> MakeTreeRowWidget(const TSharedRef<STableViewBase>& InOwnerTable, TSharedRef<FModularRigEventEntry> InEntry, TSharedRef<FUICommandList> InCommandList, TSharedPtr<SModularRigEventQueueView> InEventQueueView);`
- L25 _public prototype_ `void UpdateDurationMicroSeconds(double InDurationMicroSeconds);`
- L27 _public member_ `int32 EventIndex;`
- L28 _public member_ `FName EventName;`
- L29 _public member_ `FModuleInstanceHandle Module;`
- L30 _public member_ `bool bExecuted = false;`
- L31 _public member_ `double MicroSeconds = 0.0;`
- L32 _public member_ `TArray<double> MicroSecondsFrames;`

#### class `SModularRigEventItem`  
`class SModularRigEventItem : public STableRow<TSharedPtr<FModularRigEventEntry>>`  
_L35-53_
- inherits: `STableRow<TSharedPtr<FModularRigEventEntry>>`
- L37 _private function_ `SLATE_BEGIN_ARGS(SModularRigEventItem)`
- L38 _private prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& OwnerTable, TSharedRef<FModularRigEventEntry> InEventEntry, TSharedRef<FUICommandList> InCommandList);`
- L43 _private member_ `TWeakPtr<FModularRigEventEntry> WeakEventEntry;`
- L44 _private member_ `TWeakPtr<FUICommandList> WeakCommandList;`
- L46 _private prototype_ `FText GetIndexText() const;`
- L47 _private prototype_ `FText GetModuleLabelText() const;`
- L48 _private prototype_ `FSlateFontInfo GetModuleLabelFont() const;`
- L49 _private prototype_ `FText GetEventLabelText() const;`
- L50 _private prototype_ `FSlateFontInfo GetEventLabelFont() const;`
- L51 _private prototype_ `FText GetTooltip() const;`
- L52 _private prototype_ `FText GetDurationText() const;`

#### class `SModularRigEventQueueView`  
`class SModularRigEventQueueView : public SCompoundWidget`  
_L55-118_
- inherits: `SCompoundWidget`
- L58 _public function_ `SLATE_BEGIN_ARGS(SModularRigEventQueueView)`
- L61 _public prototype_ `~SModularRigEventQueueView();`
- L63 _public prototype_ `void Construct(const FArguments& InArgs, TSharedRef<IControlRigBaseEditor> InControlRigEditor);`
- L66 _public prototype_ `void OnSelectionChanged(TSharedPtr<FModularRigEventEntry> Selection, ESelectInfo::Type SelectInfo);` — Set Selection Changed
- L71 _protected prototype_ `void RefreshTreeView(const UModularRig* InModularRig);` — Rebuild the tree view
- L76 _private prototype_ `void BindCommands();` — Bind commands that this widget handles
- L79 _private prototype_ `TSharedRef<ITableRow> MakeTableRowWidget(TSharedPtr<FModularRigEventEntry> InItem, const TSharedRef<STableViewBase>& OwnerTable);` — Make a row widget for the table
- L82 _private prototype_ `void HandleGetChildrenForTree(TSharedPtr<FModularRigEventEntry> InItem, TArray<TSharedPtr<FModularRigEventEntry>>& OutChildren);` — Get children for the tree
- L85 _private prototype_ `void HandleFocusOnSelectedModule();` — Focus on the selected module in the rig
- L88 _private member_ `TSharedPtr<SSearchBox> FilterBox;` — Search box widget
- L89 _private member_ `FText FilterText;`
- L90 _private prototype_ `void OnFilterTextChanged(const FText& SearchText);`
- L92 _private prototype_ `void HandlePreviewHostUpdated(IRigVMEditor* InEditor);`
- L93 _private prototype_ `void HandleModularRigExecuted(class URigVMHost* InModularRig, const FName& InEventName);`
- L94 _private prototype_ `void HandleModularRigModelModified(EModularRigNotification InNotification, const FRigModuleReference* InModuleReference);`
- L100 _private prototype_ `bool PopulateEventQueueView(const UModularRig* InModularRig);` — Populate the event queue with descriptive names for each event Returns true if the treeview has to refresh.
- L102 _private member_ `TSharedPtr<STreeView<TSharedPtr<FModularRigEventEntry>>> TreeView;`
- L105 _private member_ `TSharedPtr<FUICommandList> CommandList;` — Command list we bind to
- L107 _private member_ `TWeakPtr<IControlRigBaseEditor> WeakEditor;`
- L108 _private member_ `TWeakObjectPtr<UModularRig> WeakModularRig;`
- L109 _private member_ `TWeakObjectPtr<UModularRigController> WeakModularRigController;`
- L111 _private member_ `TArray<TSharedPtr<FModularRigEventEntry>> Events;`
- L112 _private member_ `uint32 LastHash = 0;`
- L113 _private member_ `bool bIsSelecting = false;`
- L115 _private member_ `FDelegateHandle OnPreviewHostUpdatedHandle;`
- L116 _private member_ `FDelegateHandle OnControlRigExecutedHandle;`
- L117 _private member_ `FDelegateHandle OnModularRigModelModifiedHandle;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API CONTROLRIGEDITOR_API`

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/Editor/SRigConnectorTargetWidget.h` (Private)


#### class `URigConnectorTargetsDetailWrapper`  
`class URigConnectorTargetsDetailWrapper : public UObject`  
_L24-52_
- reflection: `UCLASS()`
- inherits: `UObject`
- L30 _public function_ `URigConnectorTargetsDetailWrapper() : Connector(NAME_None, ERigElementType::Connector)`
- L36 _public member_ `FRigElementKey Connector;` — `UPROPERTY()`
- L39 _public member_ `TArray<FRigElementKey> TargetArray;` — `UPROPERTY(EditAnywhere, Category=NoCategory, meta=(FullyExpand=false))`
- L41 _public function_ `FRigHierarchyTreeDelegates* GetRigTreeDelegates() const`
- L48 _private member_ `FRigHierarchyTreeDelegates* RigTreeDelegates = nullptr;`

#### class `SRigConnectorTargetComboButton`  
`class SRigConnectorTargetComboButton : public SComboButton`  
_L55-94_
- inherits: `SComboButton`
- desc: Widget allowing editing the targets of a connector
- L58 _public function_ `SLATE_BEGIN_ARGS(SRigConnectorTargetComboButton) : _Padding(0) , _ContentPadding(3) , _MenuPlacement(EMenuPlacement::MenuPlacement_BelowAnchor) , _ConnectorKey(NAME_None, ERigElementType::Connector) , _ArrayIndex(INDEX_NONE) , _ButtonMinDesiredWith(150.f)`
- L66 _public prototype_ `SLATE_ATTRIBUTE(FMargin, Padding) SLATE_ATTRIBUTE( FMargin, ContentPadding ) SLATE_ATTRIBUTE( EMenuPlacement, MenuPlacement ) SLATE_ARGUMENT(FRigElementKey, ConnectorKey) SLATE_ATTRIBUTE(FRigElementKey, TargetKey) SLATE_ATTRIBUTE(int32, ArrayIndex) SLATE_ARGUMENT(FRigHierarchyTreeDelegates, RigTreeDelegates) SLATE_ARGUMENT(float, ButtonMinDesiredWith) SLATE_EVENT(FRigConnectorTargetWidget_SetTarget, OnSetTarget) SLATE_END_ARGS() virtual ~SRigConnectorTargetComboButton() override;`
- L79 _public prototype_ `void Construct(const FArguments& InArgs);`
- L83 _private prototype_ `void OnComboBoxOpened();`
- L84 _private prototype_ `void PopulateButtonBox();`
- L85 _private prototype_ `void OnConnectorTargetPicked(TSharedPtr<FRigHierarchyTreeElement> Selection, ESelectInfo::Type SelectInfo);`
- L87 _private member_ `FRigElementKey ConnectorKey;`
- L88 _private member_ `TAttribute<FRigElementKey> TargetKey;`
- L89 _private member_ `TAttribute<int32> ArrayIndex;`
- L90 _private member_ `FRigConnectorTargetWidget_SetTarget OnSetTarget;`
- L91 _private member_ `TSharedPtr<SVerticalBox> VerticalButtonBox;`
- L92 _private member_ `FRigHierarchyTreeDelegates RigTreeDelegates;`
- L93 _private member_ `TSharedPtr<SRigHierarchySearchableTreeView> SearchableTreeView;`

#### class `SRigConnectorTargetWidget`  
`class SRigConnectorTargetWidget : public SBox`  
_L97-140_
- inherits: `SBox`
- desc: Widget allowing editing the targets of a connector
- L100 _public function_ `SLATE_BEGIN_ARGS(SRigConnectorTargetWidget) : _Outer(nullptr) , _ConnectorKey(NAME_None, ERigElementType::Connector) , _IsArray(false) , _ExpandArrayByDefault(false) , _RespectConnectorRules(true) , _HandleTargetsChangedInClient(nullptr) , _Padding(FMargin(0))`
- L109 _public prototype_ `SLATE_ARGUMENT(UObject*, Outer) SLATE_ARGUMENT(FRigElementKey, ConnectorKey) SLATE_ARGUMENT(TArray<FRigElementKey>, Targets) SLATE_ARGUMENT(bool, IsArray) SLATE_ARGUMENT(bool, ExpandArrayByDefault) SLATE_ARGUMENT(bool, RespectConnectorRules) SLATE_EVENT(FRigConnectorTargetWidget_SetTargetArray, OnSetTargetArray) SLATE_ARGUMENT(FRigConnectorTargetWidget_HandleTargetsChangedInClient*, HandleTargetsChangedInClient) SLATE_ATTRIBUTE(FMargin, Padding) SLATE_ARGUMENT(FRigHierarchyTreeDelegates, RigTreeDelegates) SLATE_END_ARGS() virtual ~SRigConnectorTargetWidget() override;`
- L123 _public prototype_ `void Construct(const FArguments& InArgs);`
- L127 _private prototype_ `void HandleTargetsChangedInClient(TArray<FRigElementKey> InTargets);`
- L128 _private prototype_ `void OnFinishedChangingProperties(const FPropertyChangedEvent& PropertyChangedEvent);`
- L129 _private prototype_ `void OnPropertyChanged();`
- L130 _private prototype_ `TSharedRef<IPropertyTypeCustomization> GetRigElementKeyCustomization() const;`
- L132 _private prototype_ `FRigElementKey GetSingleTargetKey() const;`
- L134 _private member_ `FRigElementKey Connector;`
- L135 _private member_ `FRigElementKey SingleTarget;`
- L136 _private member_ `TStrongObjectPtr<URigConnectorTargetsDetailWrapper> TargetsDetailWrapper;`
- L137 _private member_ `FRigConnectorTargetWidget_SetTargetArray OnSetTargetArray;`
- L138 _private member_ `bool bIsArray = false;`
- L139 _private member_ `FRigHierarchyTreeDelegates RigTreeDelegates;`

#### class `FRigConnectorTargetWidgetCustomization`  
`class FRigConnectorTargetWidgetCustomization : public IPropertyTypeCustomization`  
_L142-158_
- inherits: `IPropertyTypeCustomization`
- L147 _public prototype_ `virtual void CustomizeHeader(TSharedRef<class IPropertyHandle> InStructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;` — IPropertyTypeCustomization interface
- L148 _public prototype_ `virtual void CustomizeChildren(TSharedRef<class IPropertyHandle> InStructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L152 _protected prototype_ `FRigElementKey GetElementKey() const;`
- L154 _protected member_ `mutable TSharedPtr<IPropertyHandle> StructPropertyHandle;`
- L155 _protected member_ `TWeakObjectPtr<URigConnectorTargetsDetailWrapper> TargetsDetailWrapper;`

#### Free symbols / members of external scopes

- L19 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FRigConnectorTargetWidget_SetTarget, FRigElementKey);`
- L19 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FRigConnectorTargetWidget_SetTarget, FRigElementKey);`
- L20 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FRigConnectorTargetWidget_SetTargetArray, TArray<FRigElementKey>);`
- L20 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FRigConnectorTargetWidget_SetTargetArray, TArray<FRigElementKey>);`
- L21 _delegate_ `DECLARE_DELEGATE_OneParam(FRigConnectorTargetWidget_HandleTargetsChangedInClient, TArray<FRigElementKey>);`
- L21 _prototype_ `DECLARE_DELEGATE_OneParam(FRigConnectorTargetWidget_HandleTargetsChangedInClient, TArray<FRigElementKey>);`

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/Editor/SRigCurveContainer.h` (Private)


#### class `FDisplayedRigCurveInfo`  
`class FDisplayedRigCurveInfo`  
_L25-48_
- L28 _public member_ `const FName CurveName;`
- L29 _public member_ `const FSlateColor TextColor;`
- L30 _public member_ `float Value;`
- L33 _public function_ `static TSharedRef<FDisplayedRigCurveInfo> Make(const FName& InCurveName, const FSlateColor& InTextColor)` — Static function for creating a new item, but ensures that you can only have a TSharedRef to one
- L39 _public member_ `TSharedPtr<SInlineEditableTextBlock> EditableText;` — editable text
- L43 _protected function_ `FDisplayedRigCurveInfo(const FName& InCurveName, const FSlateColor& InTextColor) : CurveName(InCurveName) , TextColor(InTextColor) , Value(0.f)` — Hidden constructor, always use Make above

#### class `SRigCurveListRow`  
`class SRigCurveListRow : public SMultiColumnTableRow< FDisplayedRigCurveInfoPtr >`  
_L60-122_
- inherits: `SMultiColumnTableRow<FDisplayedRigCurveInfoPtr>`
- L64 _public function_ `SLATE_BEGIN_ARGS(SRigCurveListRow)`
- L67 _public prototype_ `SLATE_ARGUMENT(FDisplayedRigCurveInfoPtr, Item) SLATE_EVENT(FOnTextCommitted, OnTextCommitted) SLATE_EVENT(FSetRigCurveValue, OnSetRigCurveValue) SLATE_EVENT(FGetRigCurveValue, OnGetRigCurveValue) SLATE_EVENT(FGetFilterText, OnGetFilterText) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& OwnerTableView);` — The item for this row
- L86 _public prototype_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& ColumnName) override;` — Overridden from SMultiColumnTableRow.  Generates a widget for this column of the tree row.
- L98 _private prototype_ `void OnRigCurveValueChanged(float NewValue);` — Called when the user changes the value of the SSpinBox @param NewValue - The new number the SSpinBox is set to this may not work right if the rig is being evaluated this just overwrite the data when it's written
- L106 _private prototype_ `void OnRigCurveValueValueCommitted(float NewValue, ETextCommit::Type CommitType);` — Called when the user types the value and enters @param NewValue - The new number the SSpinBox is set to
- L109 _private prototype_ `float GetValue() const;` — Returns the Value of this curve
- L111 _private prototype_ `FText GetItemName() const;` — Returns name of this curve
- L113 _private prototype_ `FText GetFilterText() const;` — Get text we are filtering for
- L116 _private member_ `FDisplayedRigCurveInfoPtr Item;` — The name and Value of the morph target
- L118 _private member_ `FOnTextCommitted OnTextCommitted;`
- L119 _private member_ `FSetRigCurveValue OnSetRigCurveValue;`
- L120 _private member_ `FGetRigCurveValue OnGetRigCurveValue;`
- L121 _private member_ `FGetFilterText OnGetFilterText;`

#### class `SRigCurveContainer`  
`class SRigCurveContainer : public SCompoundWidget, public FEditorUndoClient`  
_L127-292_
- inherits: `SCompoundWidget,FEditorUndoClient`
- L129 _private typedef_ `using FRigVMEdGraphNodeRegistry = UE::RigVMEditor::FRigVMEdGraphNodeRegistry;`
- L132 _public function_ `SLATE_BEGIN_ARGS( SRigCurveContainer )`
- L135 _public prototype_ `SLATE_END_ARGS() void Construct( const FArguments& InArgs, TSharedRef<IControlRigBaseEditor> InControlRigEditor);`
- L149 _public prototype_ `virtual ~SRigCurveContainer();` — Destructor - resets the animation curve
- L152 _public prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent);` — SWidget interface
- L160 _public prototype_ `void OnPreviewMeshChanged(class USkeletalMesh* OldPreviewMesh, class USkeletalMesh* NewPreviewMesh);` — Is registered with ControlRig Editor to handle when its preview mesh is changed. @param NewPreviewMesh - The new preview mesh being used by ControlRig Editor
- L167 _public prototype_ `void OnPreviewAssetChanged(class UAnimationAsset* NewPreviewAsset);` — Is registered with ControlRig Editor to handle when its preview asset is changed. Pose Asset will have to add curve manually
- L175 _public prototype_ `void OnFilterTextChanged( const FText& SearchText );` — Filters the SListView when the user changes the search text box (NameFilterBox) @param SearchText - The text the user has typed
- L186 _public prototype_ `void OnFilterTextCommitted( const FText& SearchText, ETextCommit::Type CommitInfo );` — Filters the SListView when the user hits enter or clears the search box Simply calls OnFilterTextChanged @param SearchText - The text the user has typed @param CommitInfo - Not used
- L196 _public prototype_ `TSharedRef<ITableRow> GenerateRigCurveRow(FDisplayedRigCurveInfoPtr InInfo, const TSharedRef<STableViewBase>& OwnerTable);` — Create a widget for an entry in the tree from an info @param InInfo - Shared pointer to the morph target we're generating a row for @param OwnerTable - The table that owns this row @return A new Slate widget, containing the UI for this row
- L202 _public function_ `FText& GetFilterText()` — Accessor so our rows can grab the filtertext for highlighting
- L204 _public prototype_ `void RefreshCurveList_AnyThread();`
- L205 _public prototype_ `void RefreshCurveList();`
- L208 _public prototype_ `virtual void OnNameCommitted(const FText& NewName, ETextCommit::Type CommitType, FDisplayedRigCurveInfoPtr Item);` — When a name is committed after being edited in the list
- L211 _public prototype_ `virtual void PostUndo(bool bSuccess) override;` — FEditorUndoClient
- L212 _public prototype_ `virtual void PostRedo(bool bSuccess) override;`
- L216 _private prototype_ `void BindCommands();`
- L219 _private prototype_ `TSharedPtr<SWidget> OnGetContextMenuContent() const;` — Handler for context menus
- L221 _private prototype_ `void OnEditorClose(IControlRigBaseEditor* InEditor, FControlRigAssetInterfacePtr InBlueprint);`
- L229 _private prototype_ `void CreateRigCurveList( const FString& SearchText = FString() );` — Clears and rebuilds the table, according to an optional search string @param SearchText - Optional search string
- L232 _private prototype_ `bool IsCurveElementUsedInGraph(const FRigCurveElement& CurveElement) const;` — Returns true if the curve is used in the graph
- L234 _private prototype_ `void OnDeleteNameClicked();`
- L235 _private prototype_ `bool CanDelete();`
- L237 _private prototype_ `void OnRenameClicked();`
- L238 _private prototype_ `bool CanRename();`
- L240 _private prototype_ `void OnAddClicked();`
- L243 _private prototype_ `void CreateNewNameEntry(const FText& CommittedText, ETextCommit::Type CommitType);` — Adds a new smartname entry to the skeleton in the container we are managing
- L246 _private prototype_ `void SetCurveValue(const FName& CurveName, float CurveValue);` — delegate for changing info
- L247 _private prototype_ `float GetCurveValue(const FName& CurveName);`
- L248 _private prototype_ `void ChangeCurveName(const FName& OldName, const FName& NewName);`
- L250 _private prototype_ `void OnSelectionChanged(FDisplayedRigCurveInfoPtr Selection, ESelectInfo::Type SelectInfo);`
- L252 _private member_ `bool bIsChangingRigHierarchy;`
- L253 _private prototype_ `void OnHierarchyModified_AnyThread(ERigHierarchyNotification InNotif, URigHierarchy* InHierarchy, const FRigNotificationSubject& InSubject);`
- L254 _private prototype_ `void OnHierarchyModified(ERigHierarchyNotification InNotif, URigHierarchy* InHierarchy, const FRigNotificationSubject& InSubject);`
- L255 _private prototype_ `void OnPostConstruction(UControlRig* InControlRig, const FName& InName);`
- L256 _private prototype_ `void HandleSetObjectBeingDebugged(UObject* InObject);`
- L257 _private prototype_ `void HandleRefreshEditorFromBlueprint(FRigVMEditorAssetInterfacePtr InBlueprint);`
- L260 _private prototype_ `void ImportCurve(const FAssetData& InAssetData);` — import curve part
- L261 _private prototype_ `void CreateImportMenu(FMenuBuilder& MenuBuilder);`
- L262 _private prototype_ `bool ShouldFilterOnImport(const FAssetData& AssetData) const;`
- L265 _private member_ `TSharedPtr<SSearchBox> NameFilterBox;` — Box to filter to a specific morph target name
- L268 _private member_ `TArray< FDisplayedRigCurveInfoPtr > RigCurveList;` — A list of animation curve. Used by the RigCurveListView.
- L271 _private member_ `TSharedPtr<SRigCurveListType> RigCurveListView;` — Widget used to display the list of animation curve
- L274 _private member_ `TWeakInterfacePtr<IControlRigEditorAssetInterface> ControlRigBlueprint;` — Control Rig Blueprint
- L275 _private member_ `TWeakPtr<IControlRigBaseEditor> ControlRigEditor;`
- L276 _private member_ `TWeakObjectPtr<UControlRig> ControlRigBeingDebuggedPtr;`
- L279 _private member_ `FText FilterText;` — Current text typed into NameFilterBox
- L282 _private member_ `TSharedPtr<FRigVMEdGraphNodeRegistry> EdGraphNodeFunctionRegistry;` — Function graph node registry to find coneected curves
- L285 _private member_ `TSharedPtr<FUICommandList> UICommandList;` — Commands that are bound to delegates
- L287 _private prototype_ `URigHierarchy* GetHierarchy() const;`
- L288 _private prototype_ `URigHierarchy* GetDefaultHierarchy() const;`

#### Free symbols / members of external scopes

- L23 _namespace_ `namespace UE`
- L23 _namespace_ `namespace RigVMEditor` (scope `UE`)
- L50 _typedef_ `typedef TSharedPtr< FDisplayedRigCurveInfo > FDisplayedRigCurveInfoPtr;`
- L51 _typedef_ `typedef SListView< FDisplayedRigCurveInfoPtr > SRigCurveListType;`
- L56 _delegate_ `DECLARE_DELEGATE_TwoParams(FSetRigCurveValue, const FName&, float);`
- L56 _prototype_ `DECLARE_DELEGATE_TwoParams(FSetRigCurveValue, const FName&, float);`
- L57 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(float, FGetRigCurveValue, const FName&);`
- L57 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(float, FGetRigCurveValue, const FName&);`
- L58 _delegate_ `DECLARE_DELEGATE_RetVal(FText&, FGetFilterText);`
- L58 _prototype_ `DECLARE_DELEGATE_RetVal(FText&, FGetFilterText);`

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/Editor/SRigModuleAssetBrowser.h` (Private)


#### class `SRigModuleAssetBrowser`  
`class SRigModuleAssetBrowser : public SBox`  
_L21-95_
- inherits: `SBox`
- L23 _private typedef_ `using FControlRigShowSchematicViewportOverride = UE::ControlRigEditor::FControlRigShowSchematicViewportOverride;`
- L24 _private typedef_ `using FRigVMFilterTag = UE::RigVM::Editor::Tools::FFilterByAssetTag;`
- L27 _public function_ `SLATE_BEGIN_ARGS(SRigModuleAssetBrowser) : _bAllowDragging(true), _AssetViewType(EAssetViewType::Tile)`
- L30 _public prototype_ `SLATE_ARGUMENT(bool, bAllowDragging) SLATE_ARGUMENT(EAssetViewType::Type, AssetViewType) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L35 _public prototype_ `virtual ~SRigModuleAssetBrowser();`
- L37 _public prototype_ `TArray<FAssetData> GetSelectedAssets() const;`
- L40 _private prototype_ `void RefreshView();`
- L43 _private prototype_ `virtual FReply OnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;`
- L46 _private prototype_ `void ExecuteFindInContentBrowserAction();`
- L47 _private prototype_ `bool CanExecuteFindInContentBrowserAction();`
- L49 _private prototype_ `bool OnShouldFilterOutAsset(const struct FAssetData& AssetData);`
- L50 _private prototype_ `TSharedPtr<SWidget> OnGetAssetContextMenu(const TArray<FAssetData>& SelectedAssets) const;`
- L51 _private prototype_ `void OnAssetDoubleClicked(const FAssetData& AssetData);`
- L54 _private prototype_ `void OnAssetsDragged(const TArray<FAssetData>& Assets);` — Called when assets where dragged
- L56 _private prototype_ `TSharedRef<SToolTip> CreateCustomAssetToolTip(FAssetData& AssetData);`
- L57 _private prototype_ `TSharedRef<SToolTip> CreateCustomAssetToolTipNewStyle(FAssetData& AssetData);`
- L60 _private member_ `FTimerHandle DeferredRefreshHandle;` — Asset Registry event handlers
- L61 _private prototype_ `void RequestDeferredRefresh();`
- L62 _private prototype_ `void OnAssetAdded(const FAssetData& AssetData);`
- L63 _private prototype_ `void OnAssetRemoved(const FAssetData& AssetData);`
- L64 _private prototype_ `void OnAssetRenamed(const FAssetData& AssetData, const FString& OldObjectPath);`
- L68 _private prototype_ `bool IsRigModuleAsset(const FAssetData& AssetData) const;` — Check if asset is a rig module
- L71 _private member_ `FGetCurrentSelectionDelegate GetCurrentSelectionDelegate;` — Used to get the currently selected assets
- L75 _private member_ `TSharedPtr<SBox> AssetBrowserBox;` — the animation asset browser
- L78 _private member_ `FControlRigShowSchematicViewportOverride ShowSchematicViewportOverride;` — Overrides the per project per user schematic viewport visibility
- L80 _private member_ `bool bAllowDragging;`
- L81 _private member_ `EAssetViewType::Type AssetViewType;`
- L84 _private member_ `TSharedPtr<FUICommandList> CommandList;` — Commands to execute
- L87 _private member_ `FDelegateHandle OnAssetAddedHandle;` — Delegate handles for Asset Registry
- L88 _private member_ `FDelegateHandle OnAssetRemovedHandle;`
- L89 _private member_ `FDelegateHandle OnAssetRenamedHandle;`
- L92 _private member_ `TArray<TSharedRef<FRigVMFilterTag>> CurrentFilters;` — Current filters (stored to preserve state across refreshes)

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace RigVM` (scope `UE`)
- L14 _namespace_ `namespace Editor` (scope `UE::RigVM`)
- L14 _namespace_ `namespace Tools` (scope `UE::RigVM::Editor`)

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/Graph/ControlRigGraphPanelPinFactory.h` (Private)


#### class `FControlRigGraphPanelPinFactory`  
`class FControlRigGraphPanelPinFactory : public FRigVMEdGraphPanelPinFactory`  
_L7-16_
- inherits: `FRigVMEdGraphPanelPinFactory`
- L11 _public prototype_ `virtual TSharedPtr<class SGraphPin> CreatePin(class UEdGraphPin* InPin) const override;` — FGraphPanelPinFactory interface
- L14 _public prototype_ `virtual FName GetFactoryName() const override;` — FRigVMEdGraphPanelPinFactory interface
- L15 _public prototype_ `virtual TSharedPtr<class SGraphPin> CreatePin_Internal(class UEdGraphPin* InPin) const override;`

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/Misc/Flyout/Command/FlyoutCommandArgs.h` (Private)


#### struct `UE::ControlRigEditor::FFlyoutCommandArgs`  
`struct FFlyoutCommandArgs`  
_L16-32_
- L18 _public function_ `explicit FFlyoutCommandArgs(const TSharedRef<FUICommandList>& InCommandList) : CommandList(InCommandList)`
- L22 _public function_ `FFlyoutCommandArgs& SetToggleVisibility(TSharedPtr<FUICommandInfo> InCommand)`
- L23 _public function_ `FFlyoutCommandArgs& SetSummonToCursor(TSharedPtr<FUICommandInfo> InCommand)`
- L26 _public member_ `const TSharedRef<FUICommandList> CommandList;` — Command list that the commands should be bound to. Required.
- L29 _public member_ `TSharedPtr<FUICommandInfo> ToggleVisibilityCommand;` — Shows or hides the widget. Optional.
- L31 _public member_ `TSharedPtr<FUICommandInfo> SummonToCursorCommand;` — Summons the widget to the cursor. Once the cursor moves out of the widget bounds, it is placed back ast its original position. Optional.

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace ControlRigEditor` (scope `UE`)

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/Misc/Flyout/Command/FlyoutCommandBinder.h` (Private)


#### class `UE::ControlRigEditor::FFlyoutCommandBinder`  
`class FFlyoutCommandBinder : public FNoncopyable`  
_L19-47_
- inherits: `FNoncopyable`
- desc: Processes UI commands and forwards them to FFlyoutOverlayManager. - Command: Toggle widget visible / hidden - Command: Summon widget to cursor. Once your mouse leaves the widget bounds, the widget is positioned back to its original position.
- L23 _public prototype_ `explicit FFlyoutCommandBinder(FFlyoutOverlayManager& InManager UE_LIFETIMEBOUND, FFlyoutCommandArgs InArgs);`
- L24 _public prototype_ `~FFlyoutCommandBinder();`
- L26 _public prototype_ `void BindSummonCommand();`
- L27 _public prototype_ `void UnbindSummonCommand();`
- L32 _private member_ `FFlyoutOverlayManager& Manager;` — The manager that is being extended.
- L35 _private member_ `FFlyoutCommandArgs Args;` — The arguments this was constructed with.
- L38 _private member_ `TOptional<FFlyoutSummonCommand> SummonCommand;` — Implements the summon to cursor command.
- L40 _private function_ `TSharedRef<FUICommandList> GetCommandList() const`
- L42 _private prototype_ `void BindCommands();`
- L43 _private prototype_ `void UnbindCommands();`
- L45 _private prototype_ `void HandleToggleVisibilityCommand();`
- L46 _private prototype_ `void HandleSummonToCursorCommand();`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace ControlRigEditor` (scope `UE`)

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/Misc/Flyout/Command/FlyoutSummonCommand.h` (Private)


#### class `UE::ControlRigEditor::FFlyoutSummonCommand`  
`class FFlyoutSummonCommand : public FNoncopyable`  
_L17-43_
- inherits: `FNoncopyable`
- desc: Temporarily summons the flyout widget to the cursor.
- L21 _public prototype_ `explicit FFlyoutSummonCommand( FFlyoutOverlayManager& InManager UE_LIFETIMEBOUND, const TSharedRef<FUICommandInfo>& InSummonToCursorCommand );`
- L25 _public prototype_ `~FFlyoutSummonCommand();`
- L28 _public prototype_ `void Execute();` — Temporarily summons the flyout widget to the cursor.
- L33 _public member_ `FFlyoutOverlayManager& Manager;` — The manager that is being extended.
- L36 _public member_ `const TSharedRef<FUICommandInfo> SummonToCursorCommand;` — The command that FFlyoutSummonCommand is bound to. Used to look up key mapping.
- L39 _public member_ `TSharedPtr<FFlyoutTemporaryPositionOverride> CommandTriggeredPositionOverride;` — Overrides the position when FFlyoutWidgetArgs::SummonToCursorCommand is invoked. Resets once the mouse leaves the widget bounds.
- L41 _public prototype_ `void OnMouseLeftContent();`
- L42 _public prototype_ `void OnMenuClosed();`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace ControlRigEditor` (scope `UE`)

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/Misc/Flyout/FlyoutOverlayManager.h` (Private)


#### enum `UE::ControlRigEditor::ETemporaryFlyoutPositionFlags`  
`enum class ETemporaryFlyoutPositionFlags : uint8`  
_L22-34_
- L24 _public enumerator_ `None = 0`
- L30 _public enumerator_ `AllowCursorOutsideOfParent = 1 << 0` — If set, the mouse cursor position is snapped to the parent widget draw space. If unset, and the mouse cursor is outside the parent widget, the operation is skipped (but a set optional is still returned).
- L33 _public enumerator_ `HideAtEnd = 1 << 1` — If set, then the widget will be hidden once the flyout position is moved back to its original position.

#### class `UE::ControlRigEditor::FFlyoutOverlayManager`  
`class FFlyoutOverlayManager : public FNoncopyable`  
_L51-157_
- inherits: `FNoncopyable`
- desc: Manages all logic around a flyout widget. A flyout widget is designed to be overlaid with another widget, usually the viewport. The user can reposition it freely in the parent widget. The following functionality is provided: - Drag-drop the widget to reposition it. The widget is "docked" to the corner closest to which the widget is dragged. Example: If the user drops the widget at the right-bottom corner, and moves the right side of the viewport to the left, this content widget maintains the same offset to the right side. - Subdue widget while not in use: - While hovered, the content widget renders at full opacity. - While not hovered, the content widget is subdued. - This also handles the edge case of the content widget opening a menu and the user unhovering the content widget. No subduing takes place while a menu is being shown.
- L56 _public prototype_ `explicit FFlyoutOverlayManager(FFlyoutWidgetArgs InArgs);`
- L57 _public prototype_ `~FFlyoutOverlayManager();`
- L59 _public function_ `bool IsShowingWidget() const`
- L60 _public function_ `void ToggleVisibility()`
- L61 _public prototype_ `void ShowWidget();`
- L62 _public prototype_ `void HideWidget();`
- L63 _public prototype_ `void DestroyWidget();`
- L65 _public function_ `bool IsTemporarilyRepositioned() const` — @return Whether the widget is temporarily repositioned.
- L72 _public prototype_ `TSharedPtr<FFlyoutTemporaryPositionOverride> TryTemporarilyPositionWidgetAtCursor( ETemporaryFlyoutPositionFlags InFlags = ETemporaryFlyoutPositionFlags::None );` — Positions the widget at the mouse cursor until the returned FFlyoutTemporaryPositionOverride is destroyed. If the widget has never been painted, the repositioning happens next tick. In that case this returns a valid FFlyoutTemporaryPositionOverride but that may end up being cancelled next tick (e.g. if the cursor is outside of the viewport).
- L77 _public prototype_ `void TrySubdueContent(bool bForce = false) const;` — Subdues the content if allowed.
- L79 _public prototype_ `void UnsubdueContent() const;` — Shows the content normally again.
- L82 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnVisibilityChanged, bool );` — Broadcasts when the visibility of the widget changes.
- L83 _public function_ `FOnVisibilityChanged& OnVisibilityChanged()`
- L85 _public function_ `FSimpleMulticastDelegate& OnMouseLeftContent()` — This delegate is invoked when the mouse cursor leaves the content of the widget.
- L87 _public function_ `FSimpleMulticastDelegate& OnMenuClosedWhileActive()` — This delegate is invoked when a menu is closed while this widget is active (i.e. not subdued).
- L92 _private member_ `const FFlyoutWidgetArgs Args;` — The behaviour this widget was initialized with.
- L95 _private member_ `TSharedPtr<ToolWidgets::SDraggableBoxOverlay> DragWidget;` — Contains the actual content widget. Nullptr until shown for the first time.
- L97 _private member_ `TSharedPtr<Private::SFlyoutWidgetWrapper> ContentWidget;` — The widget displayed in DragWidget. This widget wraps the API caller's supplied widget.
- L100 _private member_ `bool bShouldShowWidget = false;` — Whether the widget should be shown.
- L115 _private member_ `TOptional<FTemporaryMoveData> TemporaryMoveOperation;` — Set while the content widget is temporarily moved.
- L118 _private member_ `FOnVisibilityChanged OnVisibilityChangedDelegate;` — Broadcasts when the visibility of the widget changes.
- L121 _private member_ `FSimpleMulticastDelegate OnMouseLeftContentDelegate;` — This delegate is invoked when the mouse cursor leaves the content of the widget.
- L123 _private member_ `FSimpleMulticastDelegate OnMenuClosedWhileActiveDelegate;` — This delegate is invoked when a menu is closed while this widget is active (i.e. not subdued).
- L126 _private prototype_ `bool TemporarilyMoveWidgetToCursor(ETemporaryFlyoutPositionFlags InFlags);` — Moves the widget to the cursor until the cursor leaves the widget bounds. After leaving the widget bounds, move the widget back to where it was.
- L128 _private prototype_ `void StopTemporaryWidgetPosition(bool bSkipHideEvenIfRequested = false);` — Moves the widget back to its original position.
- L137 _private prototype_ `bool InternalPositionWidgetAt(const FVector2f& InAbsoluteScreenPosition, bool bAllowCursorOutsideOfParent = false) const;` — Places the widget at the given position. If the position is outside the viewport bounds, nothing happens. @param bAllowCursorOutsideOfParent If true, InAbsoluteScreenPosition is snapped to the parent widget draw space. If false, nothing happens if the user clicks outside. @return Whether the widget was moved.
- L140 _private prototype_ `void SaveWidgetState() const;` — Saves the current widget state, if supported.
- L141 _private prototype_ `void SaveWidgetState(const FToolWidget_DragBoxPosition& InPosition) const;`
- L143 _private prototype_ `bool CanDragWidget() const;` — @return Whether to allow the content widget to be dragged. False while the widget is temporarily moved.
- L146 _private prototype_ `void HandleMouseEnterContent();` — Invokes when the mouse hovers the content area.
- L148 _private prototype_ `void HandleMouseLeftContent();` — Invoked when the mouse has left the content area.
- L156 _private prototype_ `void OnWindowDestroyed(const SWindow&);` — Used to detect when menu window is destroyed, so we can subdue the content widget. This is called shortly after FSlateApplication::OnMenuBeingDestroyed; during OnMenuBeingDestroyed, FSlateApplication::AnyMenusVisible still returns true broadcast timing. OnWindowDestroyed is called right after, when AnyMenusVisible returns the updated value.

#### struct `UE::ControlRigEditor::FFlyoutOverlayManager::FTemporaryMoveData`  
`struct FTemporaryMoveData`  
_L102-113_
- L105 _public member_ `const FToolWidget_DragBoxPosition RestorePosition;` — The position the box had before it was temporarily moved.
- L108 _public member_ `const bool bHideWidgetAtEnd;` — Whether to hide the widget after the operation concludes.
- L110 _public function_ `explicit FTemporaryMoveData(const FToolWidget_DragBoxPosition& InRestorePosition, bool bHideWidgetAtEnd) : RestorePosition(InRestorePosition), bHideWidgetAtEnd(bHideWidgetAtEnd)`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace ToolWidgets` (scope `UE`)
- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace ControlRigEditor` (scope `UE`)
- L20 _namespace_ `namespace Private` (scope `UE::ControlRigEditor`)
- L35 _prototype_ `ENUM_CLASS_FLAGS(ETemporaryFlyoutPositionFlags);` (scope `UE::ControlRigEditor`)
- L82 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnVisibilityChanged, bool );` — Broadcasts when the visibility of the widget changes.

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/Misc/Flyout/FlyoutSavedState.h` (Private)


#### struct `FToolWidget_FlyoutSavedState`  
`struct FToolWidget_FlyoutSavedState`  
_L11-22_
- reflection: `USTRUCT()`
- desc: Holds information to save the state of the flyout manager. This is useful for saving in a config file.
- L17 _public member_ `FToolWidget_DragBoxPosition Position;` — `UPROPERTY()` — Where the widget was docked.
- L21 _public member_ `bool bWasVisible = false;` — `UPROPERTY()` — Whether to show the widget automatically.

#### Free symbols / members of external scopes

- L24 _namespace_ `namespace UE`
- L24 _namespace_ `namespace ControlRigEditor` (scope `UE`)
- L26 _typedef_ `using FFlyoutSavedState = FToolWidget_FlyoutSavedState;` (scope `UE::ControlRigEditor`)
- L27 _delegate_ `DECLARE_DELEGATE_OneParam(FSaveFlyoutState, FFlyoutSavedState);`
- L27 _prototype_ `DECLARE_DELEGATE_OneParam(FSaveFlyoutState, FFlyoutSavedState);` (scope `UE::ControlRigEditor`)

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/Misc/Flyout/FlyoutWidgetArgs.h` (Private)


#### struct `UE::ControlRigEditor::FFlyoutWidgetArgs`  
`struct FFlyoutWidgetArgs`  
_L21-77_
- L23 _public function_ `explicit FFlyoutWidgetArgs( FGetFlyoutWidgetContent InGetWidgetDelegate, const TSharedRef<IWidgetHost>& InWidgetHost ) : GetWidgetDelegate(MoveTemp(InGetWidgetDelegate)) , WidgetHost(InWidgetHost)`
- L33 _public function_ `explicit FFlyoutWidgetArgs( const TSharedRef<SWidget>& InContentWidget, const TSharedRef<IWidgetHost>& InWidgetHost ) : FFlyoutWidgetArgs( FGetFlyoutWidgetContent::CreateLambda([InContentWidget]{ return InContentWidget; }), InWidgetHost )`
- L38 _public function_ `FGetFlyoutWidgetContent::CreateLambda([InContentWidget]{ return InContentWidget; }), InWidgetHost )`
- L43 _public function_ `FFlyoutWidgetArgs& SetStateToRestoreFrom(FFlyoutSavedState InState)`
- L44 _public function_ `FFlyoutWidgetArgs& SetSaveStateDelegate(FSaveFlyoutState InDelegate)`
- L45 _public function_ `FFlyoutWidgetArgs& SetCanSubdue(TAttribute<bool> InCanSubdueAttr)`
- L46 _public function_ `FFlyoutWidgetArgs& SetSubduedOpacity(TAttribute<FLinearColor> InTintAttr)`
- L47 _public function_ `FFlyoutWidgetArgs& SetAbsOffsetFromCursor(TAttribute<FVector2f> InOffsetAttr)`
- L50 _public member_ `const FGetFlyoutWidgetContent GetWidgetDelegate;` — Creates the widget that is supposed to be displayed. Required.
- L52 _public member_ `const TSharedPtr<IWidgetHost> WidgetHost;` — Handles adding the widget to some UI hierarchy. Required.
- L55 _public member_ `TOptional<FFlyoutSavedState> StateToRestoreFrom;` — The initial state that should be applied. You usually pass what you have saved in a user config to this. Optional.
- L60 _public member_ `FSaveFlyoutState SaveStateDelegate;` — Saves the state of the flyout widget so it can be restored at a later time, e.g. after an editor restart, etc. You usually pass the saved state to RestoredFromState. Optional.
- L68 _public member_ `TAttribute<bool> CanSubdueAttr = true;` — Decides whether the widget can be subdued, i.e. render it so it is less noticeable to the user. Optional. This is only invoked when the widget determines now is a good time be hidden, e.g. when the cursor isn't near it. In other words: simply returning true does not mean it will be subdued - it just indicates whether right now it is appropriate or not.
- L70 _public member_ `TAttribute<FLinearColor> SubduedTintAttr = FLinearColor(1.f, 1.f, 1.f, .35f);` — The render opacity to set when the widget is out of focus.
- L76 _public member_ `TAttribute<FVector2f> AbsOffsetFromCursorAttr = FVector2f::ZeroVector;` — By default, the center of the widget is placed at the mouse cursor. This is an extra offset that is added to the absolute cursor position. The widget's center is positioned at this final transformed point.

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace ControlRigEditor` (scope `UE`)
- L19 _typedef_ `using FGetFlyoutWidgetContent = FOnGetContent;` (scope `UE::ControlRigEditor`)

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/Misc/Flyout/Host/IWidgetHost.h` (Private)


#### class `UE::ControlRigEditor::IWidgetHost`  
`class IWidgetHost`  
_L12-23_
- desc: Hosts a widget in some UI.
- L17 _public prototype_ `virtual void AddWidgetToHost(const TSharedRef<SWidget>& Widget) = 0;` — Adds the widget to the target UI. The implementation is allowed to keep a strong reference to the widget until RemoveWidgetFromHost is called.
- L20 _public prototype_ `virtual void RemoveWidgetFromHost() = 0;` — Removes the widget from the target UI and clears and strong reference to it.
- L22 _public prototype_ `virtual ~IWidgetHost() = default;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace ControlRigEditor` (scope `UE`)

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/Misc/Flyout/Host/ToolkitBasedWidgetHost.h` (Private)


#### class `UE::ControlRigEditor::FToolkitBasedWidgetHost`  
`class FToolkitBasedWidgetHost : public IWidgetHost`  
_L15-37_
- inherits: `IWidgetHost`
- desc: Adapter which hosts a widget in the IToolkitHost's active viewport. When the viewport changes, the widget is moved to the active viewport.
- L19 _public prototype_ `explicit FToolkitBasedWidgetHost(const TSharedRef<IToolkitHost>& InToolkitHost);`
- L23 _public prototype_ `virtual void AddWidgetToHost(const TSharedRef<SWidget>& Widget) override;`
- L24 _public prototype_ `virtual void RemoveWidgetFromHost() override;`
- L30 _private member_ `TSharedRef<IToolkitHost> ToolkitHost;` — The toolkit host in whicht the widget is hosted.
- L33 _private member_ `TSharedPtr<SWidget> HostedWidget;` — The widget that is hosted. Set by AddWidgetToHost.
- L36 _private prototype_ `void OnActiveViewportChanged(TSharedPtr<IAssetViewport> OldViewport, TSharedPtr<IAssetViewport> NewViewport) const;` — Moves HostedWidget to the new viewport.

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace ControlRigEditor` (scope `UE`)

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/Misc/Flyout/TemporaryPositionOverride.h` (Private)


#### class `UE::ControlRigEditor::FFlyoutTemporaryPositionOverride`  
`class FFlyoutTemporaryPositionOverride : public FNoncopyable`  
_L12-30_
- inherits: `FNoncopyable`
- desc: Keeps the flyout widget at the temporary override position until this object is destroyed, at which point it calls StopTemporaryWidgetPosition.
- L17 _private member_ `FFlyoutOverlayManager* ManagerToRestore;`
- L20 _private function_ `void Cancel()`
- L21 _private function_ `bool IsCancelled() const`
- L25 _public prototype_ `FFlyoutTemporaryPositionOverride(FPrivateToken, FFlyoutOverlayManager& InManager);`
- L26 _public prototype_ `FFlyoutTemporaryPositionOverride(FFlyoutTemporaryPositionOverride&& Other);`
- L27 _public prototype_ `FFlyoutTemporaryPositionOverride& operator=(FFlyoutTemporaryPositionOverride&& Other) = delete;`
- L29 _public prototype_ `~FFlyoutTemporaryPositionOverride();`

#### struct `UE::ControlRigEditor::FFlyoutTemporaryPositionOverride::FPrivateToken`  
`struct FPrivateToken`  
_L15-15_
- L15 _public prototype_ `struct FPrivateToken`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace ControlRigEditor` (scope `UE`)

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/Misc/RigEditModeUtils.h` (Private)


#### struct `UE::ControlRigEditor::FInitialSpacePickerSelection`  
`struct FInitialSpacePickerSelection`  
_L16-25_
- L22 _public member_ `TMap<TWeakObjectPtr<URigHierarchy>, TArray<FRigElementKey>> WeakHierarchyToControlsMap;` — All selected controls per rig, covering every selected rig. Used by the floating space picker so multi-rig selections are represented correctly.
- L24 _public function_ `bool IsValid() const`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace ControlRigEditor` (scope `UE`)
- L28 _prototype_ `FInitialSpacePickerSelection DetermineInitialSpacePickerSelection(FControlRigEditMode& InEditMode);` (scope `UE::ControlRigEditor`) — @return The initial hierarchy and controls to select when constructing SRigSpaceEditor.

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/Misc/SequencerUtils.h` (Private)


#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace ControlRigEditor` (scope `UE`)
- L13 _prototype_ `TSharedPtr<FCurveEditor> GetCurveEditorFromSequencer(const TSharedPtr<ISequencer>& InSequencer);` (scope `UE::ControlRigEditor`) — @return The curve editor used by sequencer

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/Misc/Tab/SInlineTabPanel.h` (Private)


#### struct `UE::ControlRigEditor::FInlineTabArgs`  
`struct FInlineTabArgs`  
_L15-38_
- L18 _public member_ `TAttribute<FText> Label;` — The name of the tab
- L21 _public member_ `TAttribute<FText> ToolTipText;` — The tooltip of the tab
- L24 _public member_ `FSlateIcon Icon;` — Optional icon displayed in front of the label.
- L27 _public member_ `TAlwaysValidWidget Content;` — Content to display as tab content
- L30 _public member_ `FSimpleDelegate OnTabSelected;` — Invoked when this tab's content is shown (except for when SInlineTabPanel is constructed).
- L32 _public function_ `FInlineTabArgs& SetLabel(TAttribute<FText> InLabel)`
- L33 _public function_ `FInlineTabArgs& SetToolTipText(TAttribute<FText> InToolTipText)`
- L34 _public function_ `FInlineTabArgs& SetIcon(const FSlateIcon& InIcon)`
- L35 _public function_ `FInlineTabArgs& SetContent(TAlwaysValidWidget InWidget)`
- L36 _public function_ `FInlineTabArgs& SetContent(const TSharedRef<SWidget>& InWidget)`
- L37 _public function_ `FInlineTabArgs& SetOnTabSelected(FSimpleDelegate InOnTabSelected)`

#### class `UE::ControlRigEditor::SInlineTabPanel`  
`class SInlineTabPanel : public SCompoundWidget`  
_L47-76_
- inherits: `SCompoundWidget`
- desc: Coordinator widget. A vertical box with tab buttons on the top and the selected tab content at the bottom. This is supposed to implement easy to use fence pattern. If you need more flexibility for styling, considering building your widget hierarchy directly by using STabArea, SWidgetSwitcher, and STabButton instead of complicating this widget's interface.
- L51 _public function_ `SLATE_BEGIN_ARGS(SInlineTabPanel) : _ActiveTabIndex(0) , _Padding(3.f)`
- L57 _public prototype_ `SLATE_ARGUMENT(TArray<FInlineTabArgs>, Tabs) SLATE_ARGUMENT(int32, ActiveTabIndex) SLATE_ARGUMENT(FMargin, Padding) SLATE_END_ARGS() void Construct(const FArguments& InArgs);` — The tabs to create
- L68 _public prototype_ `void SwitchToTab(int32 InIndex) const;` — Shows the content of the specified tab index.
- L73 _private member_ `TSharedPtr<STabArea> TabArea;` — Displays the tab buttons.
- L75 _private member_ `TSharedPtr<SWidgetSwitcher> TabContentSwitcher;` — Switches the content for the tabs

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace ControlRigEditor` (scope `UE`)

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/Misc/Tab/STabArea.h` (Private)


#### struct `UE::ControlRigEditor::FTabEntry`  
`struct FTabEntry`  
_L12-22_
- L15 _public member_ `TAlwaysValidWidget ButtonContent;` — Content to display in the button
- L18 _public member_ `TAttribute<float> MinButtonSlotWidth = 60.f;` — Min widhth you want the button slot to have when the panel is resized
- L21 _public member_ `FSimpleDelegate OnTabSelected;` — Invoked when the tab is opened

#### class `UE::ControlRigEditor::STabArea`  
`class STabArea : public SCompoundWidget`  
_L25-54_
- inherits: `SCompoundWidget`
- desc: Manages multiple STabButtons, making sure exactly 1 is active at a time.
- L29 _public function_ `SLATE_BEGIN_ARGS(STabArea) : _ActiveTabIndex(0) , _Padding(3.f)`
- L34 _public prototype_ `SLATE_ARGUMENT(TArray<FTabEntry>, Tabs) SLATE_ARGUMENT(int32, ActiveTabIndex) SLATE_ARGUMENT(FMargin, Padding) SLATE_END_ARGS() void Construct(const FArguments& InArgs);` — The tabs to create
- L45 _public prototype_ `void SetButtonActivated(int32 ButtonIndex);` — Informs the owning view has manually changed to the content displayed by ButtonIndex. Make the button appear selected.
- L50 _private member_ `TArray<TSharedRef<STabButton>> TabButtons;` — The buttons in this area.
- L53 _private prototype_ `void OnButtonActivated(int32 ButtonIndex);` — Called when the button at TabButtons[ButtonIndex] is activated.

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace ControlRigEditor` (scope `UE`)

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/Misc/Tab/STabButton.h` (Private)


#### class `UE::ControlRigEditor::STabButton`  
`class STabButton : public SCompoundWidget`  
_L14-42_
- inherits: `SCompoundWidget`
- desc: Used to switch "tabs". It is a blue button when active and gray when inactive.
- L18 _public function_ `SLATE_BEGIN_ARGS(STabButton)`
- L20 _public prototype_ `SLATE_EVENT(FSimpleDelegate, OnActivated) SLATE_DEFAULT_SLOT(FArguments, ButtonContent) SLATE_END_ARGS() void Construct(const FArguments& InArgs);` — Called when this button is clicked and becomes active. Not trigger if it was already active.
- L28 _public function_ `void Activate()` — Makes the button appear active.
- L30 _public function_ `void Deactivate()` — Makes the button appear inactive.
- L35 _private member_ `bool bIsActive = false;` — Whether the button is active (the tab content is supposed to be shown).
- L38 _private member_ `FSimpleDelegate OnActivatedDelegate;` — Called when this button is clicked and becomes active. Not trigger if it was already active.
- L40 _private prototype_ `ECheckBoxState IsChecked() const;`
- L41 _private prototype_ `void OnButtonClicked(ECheckBoxState NewState);`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace ControlRigEditor` (scope `UE`)

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/ModifyLevelSequenceLinkSettings.h` (Private)


#### class `UModifyLevelSequenceLinkSettings`  
`class UModifyLevelSequenceLinkSettings : public UObject`  
_L11-17_
- reflection: `UCLASS(Transient)`
- inherits: `UObject`
- desc: Object to hold the LinkItem so we can modify it in asset details
- L16 _public member_ `FLevelSequenceAnimSequenceLinkItem LinkItem;` — `UPROPERTY(EditAnywhere, Category = Property, meta = (ShowOnlyInnerProperties))`

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/RigDependencyGraph/RigDependencyConnectionDrawingPolicy.h` (Private)


#### class `FRigDependencyConnectionDrawingPolicy`  
`class FRigDependencyConnectionDrawingPolicy : public FConnectionDrawingPolicy`  
_L7-22_
- inherits: `FConnectionDrawingPolicy`
- L10 _public function_ `FRigDependencyConnectionDrawingPolicy(int32 InBackLayerID, int32 InFrontLayerID, float InZoomFactor, const FSlateRect& InClippingRect, FSlateWindowElementList& InDrawElements) : FConnectionDrawingPolicy(InBackLayerID, InFrontLayerID, InZoomFactor, InClippingRect, InDrawElements)`
- L15 _public function_ `virtual FVector2f ComputeSplineTangent(const FVector2f& Start, const FVector2f& End) const override`
- L21 _public prototype_ `virtual void DetermineWiringStyle(UEdGraphPin* OutputPin, UEdGraphPin* InputPin, FConnectionParams& Params) override;`

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/RigDependencyGraph/RigDependencyGraph.h` (Private)


#### class `URigDependencyGraph`  
`class URigDependencyGraph : public UEdGraph`  
_L18-272_
- reflection: `UCLASS()`
- inherits: `UEdGraph`
- L23 _public typedef_ `using FNodeId = URigDependencyGraphNode::FNodeId;`
- L25 _public prototype_ `void Initialize(const TSharedRef<IControlRigBaseEditor>& InControlRigEditor, const TWeakObjectPtr<UControlRig>& InControlRig);`
- L28 _public prototype_ `void RebuildGraph(bool bExpand = false);` — Rebuilds graph from selection
- L31 _public prototype_ `void RebuildLinks();` — Rebuilds the links
- L34 _public prototype_ `void RebuildIslands();` — Recomputes the islands based on the connectivity
- L37 _public prototype_ `void UpdatePinVisibility();` — Update the input and output pins
- L40 _public prototype_ `void UpdateFadeOutStates();` — Update the nodes' fade out states
- L43 _public prototype_ `void SelectNodes(const TArray<FNodeId>& InNodeIds);` — Select the nodes
- L46 _public prototype_ `void ClearNodeSelection();` — Removes all nodes from the selection
- L49 _public function_ `const TArray<URigDependencyGraphNode*>& GetNodes() const` — Get the dependency graph nodes we are displaying
- L52 _public prototype_ `const URigDependencyGraphNode* FindNode(const FNodeId& InNodeId) const;` — Returns the node given a Node Id
- L53 _public prototype_ `URigDependencyGraphNode* FindNode(const FNodeId& InNodeId);`
- L56 _public prototype_ `bool Contains(const FNodeId& InNodeId) const;` — Returns true if the node given a Node Id exists
- L59 _public function_ `TSharedRef<IControlRigBaseEditor> GetControlRigEditor() const` — Get the control rig asset editor we are embedded in
- L62 _public prototype_ `UControlRig* GetControlRig() const;` — Get the control rig we are displaying
- L65 _public prototype_ `URigHierarchy* GetRigHierarchy() const;` — Get the hierarchy we are displaying
- L68 _public prototype_ `const FRigVMClient* GetRigVMClient() const;` — Get the client to resolve a node for
- L71 _public prototype_ `void RequestRefreshLayout();` — Requests a layout refresh
- L72 _public prototype_ `void RequestRefreshLayout(const TArray<FNodeId>& InNodes);`
- L75 _public prototype_ `bool NeedsRefreshLayout() const;` — Get whether a layout refresh was requested
- L78 _public prototype_ `TSharedRef<IRigDependenciesProvider> GetRigDependencyProvider() const;` — Get the dependency provider we are editing
- L81 _public prototype_ `const URigDependencyGraphSchema* GetRigDependencyGraphSchema() const;` — Get the dependency graph schema
- L83 _public function_ `bool DoesFollowParentRelationShips() const`
- L84 _public function_ `bool DoesFollowVMRelationShips() const`
- L85 _public function_ `bool IsContentLocked() const`
- L87 _public prototype_ `void SetFollowParentRelationShips(bool InFollowParentRelationShips);`
- L88 _public prototype_ `void SetFollowControlSpaceRelationships(bool InFollowControlSpaceRelationships);`
- L89 _public prototype_ `void SetFollowVMRelationShips(bool InFollowVMRelationShips);`
- L90 _public prototype_ `void SetContentLocked(bool InLockContent);`
- L92 _public prototype_ `TArray<FNodeId> GetNodesToExpand(const TArray<FNodeId>& InNodeIds, bool bExpandInputs = true, bool bExpandOutputs = true) const;`
- L94 _public prototype_ `const URigVMNode* GetRigVMNodeForInstruction(const FNodeId& InNodeId) const;`
- L95 _public prototype_ `FRigHierarchyRecord GetRecordForRigVMNode(const URigVMNode* InNode) const;`
- L97 _public prototype_ `const FRigVMExternalVariableDef* GetExternalVariable(const FNodeId& InNodeId) const;`
- L99 _public prototype_ `void Tick(float DeltaTime);`
- L101 _public prototype_ `void SelectAllNodes();`
- L102 _public prototype_ `void RemoveAllNodes();`
- L103 _public prototype_ `TArray<FNodeId> GetAllNodeIds() const;`
- L104 _public function_ `const TArray<FNodeId>& GetSelectedNodeIds() const`
- L105 _public prototype_ `void RemoveSelectedNodes();`
- L106 _public prototype_ `void RemoveUnselectedNodes();`
- L107 _public prototype_ `void RemoveUnrelatedNodes();`
- L108 _public prototype_ `void SelectLinkedNodes(const TArray<FNodeId>& InNodeIds, bool bInputNodes, bool bClearSelection, bool bRecursive);`
- L109 _public prototype_ `void SelectNodeIsland(const TArray<FNodeId>& InNodeIds, bool bClearSelection);`
- L112 _private prototype_ `void ConstructNodes(const TArray<FNodeId>& InNodesToConstruct, bool bExpand);`
- L113 _private prototype_ `void UpdateNodeIndices();`
- L114 _private prototype_ `void RemoveDependencyGraphNode(URigDependencyGraphNode* InNode);`
- L116 _private prototype_ `FBox2D GetAllNodesBounds() const;`
- L117 _private prototype_ `FBox2D GetSelectedNodesBounds() const;`
- L120 _private function_ `template<typename RangeType> FBox2D GetNodesBounds(const RangeType& InNodeIds) const`
- L134 _private prototype_ `void CancelLayout();`
- L136 _private prototype_ `void OnHierarchyModified(ERigHierarchyNotification InNotification, URigHierarchy* InHierarchy, const FRigNotificationSubject& InSubject);`
- L137 _private member_ `FDelegateHandle OnHierarchyModifiedHandle;`
- L139 _private prototype_ `void OnMetadataChanged(const FRigElementKey& InKey, const FName& InMetadataName);`
- L140 _private member_ `FDelegateHandle OnMetadataChangedHandle;`
- L142 _private prototype_ `void OnSetObjectBeingDebugged(UObject* InObject);`
- L143 _private member_ `FDelegateHandle OnSetObjectBeingDebuggedHandle;`
- L145 _private prototype_ `void OnVMCompiled(UObject* InAsset, URigVM* InVM, FRigVMExtendedExecuteContext& InExtendedContext);`
- L146 _private member_ `FDelegateHandle OnVMCompiledHandle;`
- L148 _private prototype_ `void OnRigVMGraphModified(ERigVMGraphNotifType InNotification, URigVMGraph* InRigVMGraph, UObject* InSubject);`
- L149 _private member_ `FDelegateHandle OnRigVMGraphModifiedHandle;`
- L153 _private prototype_ `static void ComputeControlToSpaceMap(const URigHierarchy* InHierarchy, TSet<uint32>* OutHashes, TMap<int32, TArray<int32>>* OutControlToSpace, TMap<int32, TArray<int32>>* OutSpaceToControl);`
- L155 _private member_ `TArray<FNodeId> SelectedNodes;`
- L158 _private member_ `TArray<TObjectPtr<URigDependencyGraphNode>> DependencyGraphNodes;` — `UPROPERTY()`
- L160 _private member_ `TMap<FNodeId, URigDependencyGraphNode*> NodeIdLookup;`
- L162 _private member_ `TWeakPtr<IControlRigBaseEditor> WeakControlRigEditor;`
- L163 _private member_ `TWeakObjectPtr<UControlRig> WeakControlRig;`
- L164 _private member_ `TSharedPtr<IRigDependenciesProvider> RigDependencyProvider;`
- L166 _private member_ `mutable FTransactionallySafeCriticalSection NodesToSelectCriticalSection;`
- L167 _private member_ `mutable TOptional<TArray<FNodeId>> NodesToSelectDuringTick;`
- L168 _private member_ `mutable TOptional<bool> RemoveAllNodesDuringTick;`
- L169 _private member_ `mutable TOptional<bool> ZoomAndFitDuringLayout;`
- L170 _private member_ `TOptional<uint32> LastRecordsHash;`
- L172 _private member_ `int32 DefaultLayoutIterationsPerNode;`
- L173 _private member_ `int32 LayoutIterationsLeft;`
- L174 _private member_ `int32 LayoutIterationsTotal;`
- L175 _private member_ `int32 LayoutIterationsMax;`
- L176 _private member_ `bool bFollowParentRelationShips;`
- L177 _private member_ `bool bFollowControlSpaceRelationships;`
- L178 _private member_ `bool bFollowVMRelationShips;`
- L179 _private member_ `bool bLockContent;`
- L180 _private member_ `bool bIsPerformingGridLayout;`
- L182 _private member_ `TSet<uint32> HierarchySpaceToControlHashes;`
- L183 _private member_ `TMap<int32, TArray<int32>> HierarchyControlToSpace;`
- L184 _private member_ `TMap<int32, TArray<int32>> HierarchySpaceToControl;`
- L187 _private member_ `int32 BlockSelectionCounter;` — As selection broadcasting is deferred in the graph, we need to block re-broadcasting a for a few frames on refresh
- L214 _private function_ `friend uint32 GetTypeHash(const FLayoutEdge& InEdge)`
- L264 _private member_ `TSet<FLayoutEdge> LayoutEdges;`
- L265 _private member_ `TArray<FNodeIsland> NodeIslands;`
- L267 _private member_ `FSimpleDelegate OnClearSelection;`

#### struct `URigDependencyGraph::FLayoutEdge`  
`struct FLayoutEdge`  
_L189-255_
- L191 _public function_ `FLayoutEdge() : NodeA(INDEX_NONE) , NodeB(INDEX_NONE) , AnchorA(FVector2D::ZeroVector) , AnchorB(FVector2D::ZeroVector) , Strength(0.f)`
- L200 _public function_ `FLayoutEdge(int32 InNodeA, int32 InNodeB, const FVector2D& InAnchorA, const FVector2D& InAnchorB, float InStrength) : NodeA(InNodeA) , NodeB(InNodeB) , AnchorA(InAnchorA) , AnchorB(InAnchorB) , Strength(InStrength)`
- L219 _public function_ `bool operator==(const FLayoutEdge& InOther) const`
- L224 _public function_ `bool operator>(const FLayoutEdge& InOther) const`
- L237 _public function_ `bool operator<(const FLayoutEdge& InOther) const`
- L250 _public member_ `int32 NodeA;`
- L251 _public member_ `int32 NodeB;`
- L252 _public member_ `FVector2D AnchorA;`
- L253 _public member_ `FVector2D AnchorB;`
- L254 _public member_ `float Strength;`

#### struct `URigDependencyGraph::FNodeIsland`  
`struct FNodeIsland`  
_L257-262_
- L259 _public member_ `FGuid Guid;`
- L260 _public member_ `TSet<FNodeId> NodeIds;`
- L261 _public member_ `FBox2D Bounds;`

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/RigDependencyGraph/RigDependencyGraphCommands.h` (Private)


#### class `FRigDependencyGraphCommands`  
`class FRigDependencyGraphCommands : public TCommands<FRigDependencyGraphCommands>`  
_L9-79_
- inherits: `TCommands<FRigDependencyGraphCommands>`
- L12 _public function_ `FRigDependencyGraphCommands() : TCommands<FRigDependencyGraphCommands> ( "ControlRigDependencyGraph", NSLOCTEXT("Contexts", "RigDependencyGraph", "Dependencies"), NAME_None,`
- L22 _public member_ `TSharedPtr<FUICommandInfo> FrameSelection;` — frames the selection in the graph
- L25 _public member_ `TSharedPtr<FUICommandInfo> JumpToSource;` — Jumps to the instruction node backing up the dependency node
- L28 _public member_ `TSharedPtr< FUICommandInfo > ShowParentChildRelationships;` — Show parent-child relationships
- L31 _public member_ `TSharedPtr< FUICommandInfo > ShowControlSpaceRelationships;` — Show control-space relationships
- L34 _public member_ `TSharedPtr< FUICommandInfo > ShowInstructionRelationships;` — Show instruction based relationships
- L37 _public member_ `TSharedPtr< FUICommandInfo > LockContent;` — Locks the content of the view and stops syncing based on selection changes
- L40 _public member_ `TSharedPtr< FUICommandInfo > EnableFlashlight;` — Enable a flashlight around the mouse cursor to brighten up faded out nodes
- L43 _public member_ `TSharedPtr<FUICommandInfo> SelectAllNodes;` — select all nodes
- L46 _public member_ `TSharedPtr<FUICommandInfo> SelectInputNodes;` — select the input nodes of the current selection
- L49 _public member_ `TSharedPtr<FUICommandInfo> SelectOutputNodes;` — select the output nodes of the current selection
- L52 _public member_ `TSharedPtr<FUICommandInfo> SelectNodeIsland;` — select the complete node island
- L55 _public member_ `TSharedPtr<FUICommandInfo> RemoveAllNodes;` — remove all nodes
- L58 _public member_ `TSharedPtr<FUICommandInfo> RemoveSelected;` — remove selected nodes
- L61 _public member_ `TSharedPtr<FUICommandInfo> IsolateSelected;` — isolate selected nodes
- L64 _public member_ `TSharedPtr<FUICommandInfo> RemoveUnrelated;` — remove unrealted nodes
- L67 _public member_ `TSharedPtr<FUICommandInfo> RunLayoutSimulation;` — starts a layout simulation to relax the nodes
- L70 _public member_ `TSharedPtr<FUICommandInfo> CancelLayoutSimulation;` — cancel an ongoing layout simulation
- L73 _public member_ `TSharedPtr<FUICommandInfo> FindNodesByName;` — search nodes by name
- L78 _public prototype_ `virtual void RegisterCommands() override;` — Initialize commands

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/RigDependencyGraph/RigDependencyGraphNode.h` (Private)


#### class `URigDependencyGraphNode`  
`class URigDependencyGraphNode : public UEdGraphNode`  
_L22-112_
- reflection: `UCLASS()`
- inherits: `UEdGraphNode`
- L26 _private typedef_ `using FNodeId = FRigHierarchyRecord;`
- L28 _private prototype_ `virtual void SetupRigDependencyNode(const FNodeId& InNodeId);`
- L29 _private prototype_ `virtual UObject* GetDetailsObject();`
- L31 _private prototype_ `class URigDependencyGraph* GetRigDependencyGraph() const;`
- L34 _private prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;` — UEdGraphNode implementation
- L35 _private prototype_ `virtual FLinearColor GetNodeBodyTintColor() const override;`
- L36 _private function_ `virtual FText GetTooltipText() const override`
- L37 _private prototype_ `virtual void AllocateDefaultPins() override;`
- L38 _private function_ `virtual bool ShowPaletteIconOnNode() const override`
- L39 _private prototype_ `virtual FSlateIcon GetIconAndTint(FLinearColor& OutColor) const;`
- L41 _private function_ `int32 GetIndex() const`
- L42 _private function_ `const FNodeId& GetNodeId() const`
- L44 _private prototype_ `UEdGraphPin& GetInputPin() const;`
- L46 _private prototype_ `UEdGraphPin& GetOutputPin() const;`
- L48 _private prototype_ `void SetDimensions(const FVector2D& InDimensions);`
- L49 _private function_ `const FVector2D& GetDimensions() const`
- L51 _private prototype_ `int32 GetDependencyDepth() const;`
- L54 _private prototype_ `UControlRig* GetControlRig() const;` — Get the control rig we are displaying
- L57 _private prototype_ `URigHierarchy* GetRigHierarchy() const;` — Get the hierarchy we are displaying
- L60 _private prototype_ `const FRigVMClient* GetRigVMClient() const;` — Get the client to resolve a node for
- L62 _private prototype_ `FRigElementKey GetRigElementKey() const;`
- L63 _private prototype_ `const FRigBaseElement* GetRigElement() const;`
- L64 _private prototype_ `const URigVMNode* GetRigVMNodeForInstruction() const;`
- L65 _private prototype_ `const FRigVMExternalVariableDef* GetExternalVariable() const;`
- L67 _private prototype_ `bool IsFadedOut() const;`
- L68 _private prototype_ `float GetFadedOutState() const;`
- L69 _private prototype_ `void OverrideFadeOutState(TOptional<float> InFadedOutState);`
- L70 _private function_ `void ResetFadedOutState()`
- L72 _private prototype_ `const FGuid& GetIslandGuid() const;`
- L74 _private prototype_ `void InvalidateCache();`
- L78 _protected prototype_ `int32 GetDependencyDepth_Impl(TArray<bool>& InOutVisited) const;`
- L80 _protected member_ `int32 Index;`
- L82 _protected member_ `FNodeId NodeId;`
- L85 _protected member_ `FText NodeTitle;` — Cached title for the node
- L86 _protected member_ `FText NodeTooltip;`
- L87 _protected member_ `FLinearColor NodeBodyColor;`
- L90 _protected member_ `UEdGraphPin* InputPin;` — Our one input pin
- L93 _protected member_ `UEdGraphPin* OutputPin;` — Our one output pin
- L96 _protected member_ `TOptional<bool> FollowLayout;` — Cached dimensions of this node (used for layout)
- L97 _protected member_ `FVector2D LayoutPosition;`
- L98 _protected member_ `FVector2D LayoutVelocity;`
- L99 _protected member_ `FVector2D LayoutForce;`
- L100 _protected member_ `FVector2D Dimensions;`
- L102 _protected member_ `mutable TOptional<int32> DependencyDepth;`
- L103 _protected member_ `mutable TOptional<FGuid> IslandGuid;`
- L104 _protected member_ `mutable TOptional<bool> bIsFadedOut;`
- L105 _protected member_ `mutable TOptional<float> FadedOutOverride;`
- L107 _protected member_ `mutable TWeakObjectPtr<const URigVMNode> CachedRigVMNode;`
- L108 _protected member_ `mutable FRigVMExternalVariableDef CachedRigVMExternalVariableDef;`

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/RigDependencyGraph/RigDependencyGraphPanelNodeFactory.h` (Private)


#### class `FRigDependencyGraphPanelNodeFactory`  
`class FRigDependencyGraphPanelNodeFactory : public FGraphPanelNodeFactory`  
_L10-13_
- inherits: `FGraphPanelNodeFactory`
- L12 _private prototype_ `virtual TSharedPtr<class SGraphNode> CreateNode(UEdGraphNode* Node) const override;`

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/RigDependencyGraph/RigDependencyGraphSchema.h` (Private)


#### class `URigDependencyGraphSchema`  
`class URigDependencyGraphSchema : public UEdGraphSchema`  
_L15-42_
- reflection: `UCLASS()`
- inherits: `UEdGraphSchema`
- L21 _public function_ `virtual FName GetParentContextMenuName() const override` — UEdGraphSchema interface
- L22 _public prototype_ `virtual FLinearColor GetPinTypeColor(const FEdGraphPinType& PinType) const override;`
- L23 _public prototype_ `virtual void BreakPinLinks(UEdGraphPin& TargetPin, bool bSendsNodeNotifcation) const override;`
- L24 _public prototype_ `virtual void BreakSinglePinLink(UEdGraphPin* SourcePin, UEdGraphPin* TargetPin) const override;`
- L25 _public prototype_ `virtual FPinConnectionResponse MovePinLinks(UEdGraphPin& MoveFromPin, UEdGraphPin& MoveToPin, bool bIsIntermediateMove = false, bool bNotifyLinkedNodes = false) const override;`
- L26 _public prototype_ `virtual FPinConnectionResponse CopyPinLinks(UEdGraphPin& CopyFromPin, UEdGraphPin& CopyToPin, bool bIsIntermediateCopy = false) const override;`
- L27 _public prototype_ `virtual class FConnectionDrawingPolicy* CreateConnectionDrawingPolicy(int32 InBackLayerID, int32 InFrontLayerID, float InZoomFactor, const FSlateRect& InClippingRect, class FSlateWindowElementList& InDrawElements, class UEdGraph* InGraphObj) const override;`
- L28 _public function_ `virtual bool ShouldAlwaysPurgeOnModification() const override`
- L29 _public prototype_ `virtual FPinConnectionResponse CanCreateNewNodes(UEdGraphPin* InSourcePin) const override;`
- L30 _public prototype_ `virtual const FPinConnectionResponse CanCreateConnection(const UEdGraphPin* A, const UEdGraphPin* B) const override;`
- L31 _public prototype_ `virtual bool SupportsDropPinOnNode(UEdGraphNode* InTargetNode, const FEdGraphPinType& InSourcePinType, EEdGraphPinDirection InSourcePinDirection, FText& OutErrorMessage) const override;`
- L32 _public prototype_ `virtual void SetNodePosition(UEdGraphNode* Node, const FVector2f& Position) const override;`
- L35 _public prototype_ `virtual URigDependencyGraphNode* CreateGraphNode(URigDependencyGraph* InGraph, const URigDependencyGraphNode::FNodeId& InNodeId) const;`
- L37 _public prototype_ `virtual void LayoutNodes(URigDependencyGraph* InGraph, int32 InIterations) const;`
- L39 _public typedef_ `using FNodeId = URigDependencyGraphNode::FNodeId;`
- L40 _public typedef_ `using FLayoutEdge = URigDependencyGraph::FLayoutEdge;`
- L41 _public typedef_ `using FNodeIsland = URigDependencyGraph::FNodeIsland;`

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/RigDependencyGraph/RigDependencyGraphSummoner.h` (Private)


#### struct `FRigDependencyGraphSummoner`  
`struct FRigDependencyGraphSummoner : public FWorkflowTabFactory`  
_L8-20_
- inherits: `FWorkflowTabFactory`
- L11 _public prototype_ `FRigDependencyGraphSummoner(const TSharedRef<IControlRigBaseEditor>& InControlRigEditor);`
- L14 _public prototype_ `virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& Info) const override;` — FWorkflowTabFactory interface
- L15 _public prototype_ `virtual TSharedPtr<SToolTip> CreateTabToolTipWidget(const FWorkflowTabSpawnInfo& Info) const override;`
- L16 _public prototype_ `virtual TSharedRef<SDockTab> SpawnTab(const FWorkflowTabSpawnInfo& Info) const override;`
- L19 _protected member_ `TWeakPtr<IControlRigBaseEditor> ControlRigEditor;`

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/RigDependencyGraph/SRigDependencyGraph.h` (Private)


#### class `SRigDependencyGraph`  
`class SRigDependencyGraph : public SCompoundWidget, public FEditorUndoClient`  
_L22-90_
- inherits: `SCompoundWidget,FEditorUndoClient`
- L26 _public typedef_ `using FNodeId = URigDependencyGraph::FNodeId;`
- L28 _public function_ `SLATE_BEGIN_ARGS(SRigDependencyGraph) : _FlashLightRadius(5.f)`
- L32 _public prototype_ `SLATE_ATTRIBUTE(float, FlashLightRadius) SLATE_END_ARGS() ~SRigDependencyGraph();`
- L39 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;` — SWidget interface
- L42 _public prototype_ `virtual void PostUndo(bool bSuccess) override;` — FEditorUndoClient interface
- L43 _public prototype_ `virtual void PostRedo(bool bSuccess) override;`
- L46 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<IControlRigBaseEditor>& InControlRigEditor);` — Constructs this widget with InArgs
- L49 _public prototype_ `void SelectNodes(const TArray<FNodeId>& InNodeIds);` — Set the selected nodes
- L51 _public prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent);`
- L55 _private prototype_ `void OnGraphEditorTick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime);`
- L58 _private prototype_ `FActionMenuContent OnCreateGraphActionMenu(UEdGraph* InGraph, const FVector2f& InNodePosition, const TArray<UEdGraphPin*>& InDraggedPins, bool bAutoExpand, SGraphEditor::FActionMenuClosed InOnMenuClosed);` — Called to create context menu when right-clicking on graph
- L61 _private prototype_ `void OnSearchBarTextChanged(const FText& NewText);` — Called when the path is being edited
- L62 _private prototype_ `void OnSearchMatchPicked(int32 InIndex);`
- L64 _private prototype_ `void HandleSelectionChanged(const FGraphPanelSelectionSet& SelectionSet);`
- L66 _private prototype_ `void HandleNodeDoubleClicked(UEdGraphNode* InNode);`
- L68 _private prototype_ `void OnClearNodeSelection();`
- L70 _private prototype_ `TSharedRef< SWidget > CreateTopLeftMenu();`
- L72 _private prototype_ `void BindCommands();`
- L76 _private member_ `TSharedPtr<SGraphEditor> GraphEditor;`
- L77 _private member_ `TSharedPtr<SProgressBar> LayoutProgressBar;`
- L78 _private member_ `TWeakPtr<IControlRigBaseEditor> WeakControlRigEditor;`
- L80 _private member_ `URigDependencyGraph* GraphObj;`
- L81 _private member_ `TSharedPtr<FUICommandList> CommandList;`
- L84 _private member_ `TSharedPtr<SSearchBox> FilterBox;` — Search box widget
- L86 _private member_ `TArray<FNodeId> NodesMatchingSearch;`
- L87 _private member_ `TOptional<int32> MatchIndex;`
- L89 _private member_ `TAttribute<float> FlashLightRadiusAttribute;`

#### Free symbols / members of external scopes

- L20 _delegate_ `DECLARE_DELEGATE_OneParam(FOnRigDependencyGraphObjectsSelected, const TArrayView<UObject*>& );` — Delegate used to communicate graph selection
- L20 _prototype_ `DECLARE_DELEGATE_OneParam(FOnRigDependencyGraphObjectsSelected, const TArrayView<UObject*>& );` — Delegate used to communicate graph selection

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/RigDependencyGraph/SRigDependencyGraphNode.h` (Private)


#### class `SRigDependencyGraphNode`  
`class SRigDependencyGraphNode : public SGraphNode`  
_L16-43_
- inherits: `SGraphNode`
- L19 _public function_ `SLATE_BEGIN_ARGS(SRigDependencyGraphNode)`
- L21 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, class URigDependencyGraphNode* InNode);`
- L28 _protected prototype_ `virtual void CreatePinWidgets() override;` — SGraphNode interface
- L29 _protected prototype_ `virtual void AddPin(const TSharedRef<SGraphPin>& PinToAdd) override;`
- L31 _protected prototype_ `FText GetNodeTitle() const;`
- L32 _protected prototype_ `virtual FText GetNodeTooltip() const override;`
- L33 _protected prototype_ `const FSlateBrush* GetNodeTitleIcon() const;`
- L34 _protected prototype_ `virtual FSlateColor GetNodeBodyColor() const override;`
- L35 _protected prototype_ `virtual const FSlateBrush* GetNodeBodyBrush() const override;`
- L36 _protected prototype_ `virtual void UpdateGraphNode() override;`
- L37 _protected prototype_ `virtual FReply OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L38 _protected prototype_ `virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;`
- L42 _protected member_ `TSharedPtr<SWidget> ContentWidget;` — The content widget for this node - derived classes can insert what they want

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/SBakeToControlRigDialog.h` (Private)


#### struct `BakeToControlRigDialog`  
`struct BakeToControlRigDialog`  
_L11-14_
- L13 _public prototype_ `static void GetBakeParams(FBakeToControlDelegate& Delegate, const FOnWindowClosed& OnClosedDelegate);`

#### Free symbols / members of external scopes

- L9 _delegate_ `DECLARE_DELEGATE_FourParams(FBakeToControlDelegate, bool, float, FFrameRate, bool);`
- L9 _prototype_ `DECLARE_DELEGATE_FourParams(FBakeToControlDelegate, bool, float, FFrameRate, bool);`

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/SControlRigAssetReferencePicker.h` (Private)


#### class `SControlRigAssetReferencePicker`  
`class SControlRigAssetReferencePicker : public SCompoundWidget`  
_L15-44_
- inherits: `SCompoundWidget`
- L17 _private prototype_ `DECLARE_DELEGATE_OneParam(FOnSelectionChanged, FControlRigAssetSoftReference);`
- L18 _private function_ `SLATE_BEGIN_ARGS(SControlRigAssetReferencePicker)`
- L21 _private prototype_ `SLATE_ARGUMENT(TSharedPtr<FControlRigClassFilter>, Filter) SLATE_ARGUMENT(TArray<FControlRigAssetSoftReference>, ExtraAssets) SLATE_ARGUMENT(TFunction<bool(const TSharedRef<FControlRigAssetSoftReference> A, const TSharedRef<FControlRigAssetSoftReference> B)>, SortPredicate) SLATE_EVENT(FOnSelectionChanged, OnSelectionChanged) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L29 _private prototype_ `TSharedRef<ITableRow> GenerateRow(TSharedRef<FControlRigAssetSoftReference> Entry, const TSharedRef<STableViewBase>& OwnerTable);`
- L30 _private prototype_ `static FText GetDisplayName(const FControlRigAssetSoftReference& Source);`
- L31 _private prototype_ `void OnFilterTextChanged(const FText& InFilterText);`
- L32 _private prototype_ `void RefreshFilteredEntries();`
- L34 _private member_ `TSharedPtr<SSearchBox> SearchBox;`
- L35 _private member_ `TSharedPtr<SListView<TSharedRef<FControlRigAssetSoftReference>>> AssetList;`
- L36 _private member_ `TArray<TSharedRef<FControlRigAssetSoftReference>> Entries;`
- L37 _private member_ `FControlRigAssetSoftReference SelectedSource;`
- L38 _private member_ `FString FilterText;`
- L40 _private member_ `FOnSelectionChanged OnSelectionChanged;`
- L41 _private member_ `TSharedPtr<FControlRigClassFilter> ControlRigFilter;`
- L42 _private member_ `TArray<FControlRigAssetSoftReference> ExtraAssets;`
- L43 _private member_ `TFunction<bool(const TSharedRef<FControlRigAssetSoftReference> A, const TSharedRef<FControlRigAssetSoftReference> B)> SortPredicate;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API CONTROLRIGEDITOR_API`
- L17 _delegate_ `DECLARE_DELEGATE_OneParam(FOnSelectionChanged, FControlRigAssetSoftReference);`

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/SControlRigDismissDependencyDialog.h` (Private)


#### struct `ControlRigDismissDependencyDialog`  
`struct ControlRigDismissDependencyDialog`  
_L7-10_
- L9 _public prototype_ `static bool LaunchDismissDependencyDialog(const URigHierarchy* InHierarchy, const FRigElementKey& InChild, const FRigElementKey& InParent, const FRigHierarchyDependencyChain& InDependencyChain);`

#### class `FControlRigDismissDependencyDialogGuard`  
`class FControlRigDismissDependencyDialogGuard`  
_L12-35_
- L15 _public function_ `FControlRigDismissDependencyDialogGuard(URigHierarchy* InHierarchy) : Hierarchy(InHierarchy)`
- L24 _public function_ `~FControlRigDismissDependencyDialogGuard()`
- L34 _private member_ `TWeakObjectPtr<URigHierarchy> Hierarchy;`

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/SControlRigDragDropBox.h` (Private)


#### class `UE::ControlRigEditor::SControlRigDragDropBox`  
`class SControlRigDragDropBox : public SCompoundWidget`  
_L12-37_
- inherits: `SCompoundWidget`
- desc: A box useful to detect drags on arbitrary widgets
- L17 _public function_ `SLATE_BEGIN_ARGS(SControlRigDragDropBox)`
- L20 _public prototype_ `SLATE_DEFAULT_SLOT(FArguments, Content) SLATE_EVENT(FOnDragDetected, OnDragDetected) SLATE_END_ARGS() void Construct(const FArguments& InArgs);` — The box content
- L31 _private prototype_ `virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L32 _private prototype_ `virtual FReply OnDragDetected(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L36 _private member_ `FOnDragDetected OnDragDetectedDelegate;` — Delegate to execute when drag was detected

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace ControlRigEditor` (scope `UE`)

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/SModifyLevelSequenceLinkDialog.h` (Private)


#### struct `ModifyLevelSequenceLinkDialog`  
`struct ModifyLevelSequenceLinkDialog`  
_L10-13_
- L12 _public prototype_ `static void ShowDialog(const FLevelSequenceAnimSequenceLinkItem& InLinkItem, FModifyLevelSequenceLinkDelegate InDelegate);`

#### Free symbols / members of external scopes

- L8 _delegate_ `DECLARE_DELEGATE_OneParam(FModifyLevelSequenceLinkDelegate, const FLevelSequenceAnimSequenceLinkItem&);`
- L8 _prototype_ `DECLARE_DELEGATE_OneParam(FModifyLevelSequenceLinkDelegate, const FLevelSequenceAnimSequenceLinkItem&);`

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/Sequencer/AnimLayerSequencerFilter.h` (Private)


#### class `UAnimLayerSequencerFilter`  
`class UAnimLayerSequencerFilter : public USequencerTrackFilterExtension`  
_L9-19_
- reflection: `UCLASS()`
- inherits: `USequencerTrackFilterExtension`
- L15 _public prototype_ `virtual void AddTrackFilterExtensions(ISequencerTrackFilters& InOutFilterInterface , const TSharedRef<FFilterCategory>& InPreferredCategory , TArray<TSharedRef<FSequencerTrackFilter>>& InOutFilterList) const override;`

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/Sequencer/AnimLayers/AnimLayers.h` (Private)


#### struct `FMergeAnimLayerSettings`  
`struct FMergeAnimLayerSettings`  
_L29-51_
- reflection: `USTRUCT(BlueprintType)`
- L33 _public function_ `FMergeAnimLayerSettings()`
- L41 _public member_ `EBakingKeySettings BakingKeySettings;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Bake")`
- L44 _public member_ `int32 FrameIncrement;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Bake", meta = (ClampMin = "1", UIMin = "1", EditCondition = "BakingKeySettings == EBakingKeySettings::AllFrames"))`
- L47 _public member_ `bool bReduceKeys;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Bake", meta = (EditCondition = "BakingKeySettings == EBakingKeySettings::AllFrames"))`
- L50 _public member_ `float TolerancePercentage;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Bake", meta = (EditCondition = "BakingKeySettings == EBakingKeySettings::AllFrames && bReduceKeys"))`

#### struct `FAnimLayerPropertyAndChannels`  
`struct FAnimLayerPropertyAndChannels`  
_L57-69_
- desc: Name of a property and control and the specific channels that make up the layer
- L61 _public function_ `FAnimLayerPropertyAndChannels() : Name(NAME_None) , Channels((uint32)EControlRigContextChannelToKey::AllTransform)`
- L65 _public member_ `FName Name;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Data")` — Name of the property or control
- L68 _public member_ `uint32 Channels;` — Mask of channels for that property/control, currently not used

#### struct `FAnimLayerSelectionSet`  
`struct FAnimLayerSelectionSet`  
_L74-96_
- reflection: `USTRUCT(BlueprintType)`
- desc: Bound object/control rig and the properties/channels it is made of A layer will consist of a bunch of these
- L77 _public function_ `FAnimLayerSelectionSet() :BoundObject(nullptr)`
- L79 _public function_ `FAnimLayerSelectionSet& operator = (const FAnimLayerSelectionSet& Other)`
- L90 _public member_ `TWeakObjectPtr<UObject> BoundObject;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Data")` — bound object is either a CR or a bound sequencer object
- L93 _public member_ `TMap<FName, FAnimLayerPropertyAndChannels> Names;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Data")` — property/control name and channels
- L95 _public prototype_ `bool MergeWithAnotherSelection(const FAnimLayerSelectionSet& Selection);`

#### struct `FAnimLayerSectionItem`  
`struct FAnimLayerSectionItem`  
_L100-110_
- reflection: `USTRUCT(BlueprintType)`
- desc: The set with it's section
- L103 _public function_ `FAnimLayerSectionItem() : Section(nullptr)`
- L106 _public member_ `FAnimLayerSelectionSet AnimLayerSet;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Data")`
- L109 _public member_ `TWeakObjectPtr<UMovieSceneSection> Section;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Data")`

#### struct `FAnimLayerItem`  
`struct FAnimLayerItem`  
_L114-132_
- reflection: `USTRUCT(BlueprintType)`
- desc: individual layer items that make up the layer
- L117 _public function_ `FAnimLayerItem()`
- L120 _public member_ `TArray< FAnimLayerSectionItem> SectionItems;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Data")`
- L123 _public member_ `FGuid SequencerGuid;` — `UPROPERTY()`
- L126 _public prototype_ `void MakeCopy(const FGuid& NewGuid, const TWeakObjectPtr<UObject>& NewObject, FAnimLayerItem& OutCopy) const;` — make copy with new guid
- L129 _public prototype_ `FAnimLayerSectionItem* FindMatchingSectionItem(UMovieSceneSection* InMovieSceneSection);` — find section that matches based upon incoming section (same type and property)
- L131 _public prototype_ `void SetSectionsActive(bool bIsActive);`

#### enum `EAnimLayerType`  
`enum EAnimLayerType : uint32`  
_L135-140_
- reflection: `UENUM()`
- L137 _public enumerator_ `Base = 0x0`
- L138 _public enumerator_ `Additive = 0x1`
- L139 _public enumerator_ `Override = 0x2`

#### struct `FAnimLayerState`  
`struct FAnimLayerState`  
_L145-174_
- reflection: `USTRUCT(BlueprintType)`
- desc: state and properties of a layer
- L150 _public prototype_ `FAnimLayerState();`
- L151 _public prototype_ `FText AnimLayerTypeToText()const;`
- L154 _public member_ `mutable ECheckBoxState bKeyed = ECheckBoxState::Unchecked;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Data")`
- L157 _public member_ `mutable ECheckBoxState bSelected = ECheckBoxState::Unchecked;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Data")`
- L160 _public member_ `mutable bool bActive;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Data")`
- L163 _public member_ `mutable bool bLock;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Data")`
- L166 _public member_ `FText Name;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Data")`
- L169 _public member_ `mutable double Weight;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Data")`
- L172 _public member_ `mutable int32 Type;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Data", meta = (Bitmask, BitmaskEnum = "/Script/ControlRigEditor.EAnimLayerType"))`

#### struct `FAnimLayerControlRigObject`  
`struct FAnimLayerControlRigObject`  
_L177-184_
- reflection: `USTRUCT(BlueprintType)`
- L181 _public member_ `TWeakObjectPtr<UControlRig> ControlRig;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Data")`
- L183 _public member_ `TArray<FName> ControlNames;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Data")`

#### struct `FAnimLayerSceneObject`  
`struct FAnimLayerSceneObject`  
_L187-196_
- reflection: `USTRUCT(BlueprintType)`
- L191 _public member_ `TWeakObjectPtr<UObject> SceneObjectOrComponent;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Data")`

#### struct `FAnimLayerObjects`  
`struct FAnimLayerObjects`  
_L201-210_
- reflection: `USTRUCT(BlueprintType)`
- L206 _public member_ `TArray<FAnimLayerControlRigObject> ControlRigObjects;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Data")`
- L209 _public member_ `TArray<FAnimLayerSceneObject> SceneObjects;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Data")`

#### class `UAnimLayerWeightProxy`  
`class UAnimLayerWeightProxy : public UObject`  
_L213-226_
- reflection: `UCLASS(EditInlineNew, CollapseCategories, HideDropdown)`
- inherits: `UObject`
- L219 _public member_ `double Weight = 1.0;` — `UPROPERTY(EditAnywhere, Interp, DisplayName = "", Category = "NoCategory", meta = (SliderExponent = "1.0"))`
- L222 _public prototype_ `virtual void PostEditChangeChainProperty(struct FPropertyChangedChainEvent& PropertyChangedEvent) override;` — UObect overrides for setting values when weight changes
- L224 _public prototype_ `virtual void PostEditUndo() override;`

#### class `UAnimLayer`  
`class UAnimLayer : public UObject`  
_L234-330_
- reflection: `UCLASS(BlueprintType, MinimalAPI)`
- inherits: `UObject`
- L238 _public function_ `UAnimLayer()`
- L239 _public prototype_ `virtual void PostLoad() override;`
- L241 _public prototype_ `void GetAnimLayerObjects(FAnimLayerObjects& InLayerObjects) const;`
- L242 _public prototype_ `void GetSections(TArray<UMovieSceneSection*>& OutSections) const;`
- L245 _public prototype_ `ECheckBoxState GetKeyed() const;` — `UFUNCTION(BlueprintCallable, Category = "State")`
- L247 _public prototype_ `void SetKeyed();` — `UFUNCTION(BlueprintCallable, Category = "State")`
- L250 _public prototype_ `ECheckBoxState GetSelected() const;` — `UFUNCTION(BlueprintCallable, Category = "State")`
- L252 _public prototype_ `void SetSelected(bool bInSelected, bool bClearSelection);` — `UFUNCTION(BlueprintCallable, Category = "State")`
- L255 _public prototype_ `bool GetActive() const;` — `UFUNCTION(BlueprintCallable, Category = "State")`
- L257 _public prototype_ `void SetActive(bool bInActive);` — `UFUNCTION(BlueprintCallable, Category = "State")`
- L260 _public prototype_ `bool GetLock() const;` — `UFUNCTION(BlueprintCallable, Category = "State")`
- L262 _public prototype_ `void SetLock(bool bInLock);` — `UFUNCTION(BlueprintCallable, Category = "State")`
- L265 _public prototype_ `FText GetName() const;` — `UFUNCTION(BlueprintCallable, Category = "State")`
- L267 _public prototype_ `void SetName(const FText& InName);` — `UFUNCTION(BlueprintCallable, Category = "State")`
- L270 _public prototype_ `double GetWeight() const;` — `UFUNCTION(BlueprintCallable, Category = "State")`
- L272 _public prototype_ `void SetWeight(double InWeight);` — `UFUNCTION(BlueprintCallable, Category = "State")`
- L275 _public prototype_ `EAnimLayerType GetType() const;` — `UFUNCTION(BlueprintCallable, Category = "State")`
- L277 _public prototype_ `void SetType(EAnimLayerType LayerType);` — `UFUNCTION(BlueprintCallable, Category = "State")`
- L280 _public prototype_ `bool AddSelectedInSequencer();` — `UFUNCTION(BlueprintCallable, Category = "State")`
- L282 _public prototype_ `bool RemoveSelectedInSequencer();` — `UFUNCTION(BlueprintCallable, Category = "State")`
- L285 _public prototype_ `void SelectWeightChannel(bool bClearSelection);` — `UFUNCTION(BlueprintCallable, Category = "State")`
- L287 _public function_ `int32 GetAnimLayerIndex() const`
- L288 _public prototype_ `bool RemoveAnimLayerItem(UObject* InObject);`
- L289 _public prototype_ `void SetSelectedInList(const FAnimLayersScopedSelection& ScopedSelection, bool bInValue);`
- L290 _public function_ `bool GetSelectedInList() const`
- L291 _public prototype_ `ECheckBoxState GetSelected(TSet<UObject*>& OutSelectedObjects, TMap<UControlRig*, TArray<FName>>& OutSelectedControls) const;`
- L294 _public prototype_ `void SetKey(TSharedPtr<ISequencer>& Sequencer, const IPropertyHandle& KeyedPropertyHandle);` — for key property status for weights
- L295 _public prototype_ `EPropertyKeyedStatus GetPropertyKeyedStatus(TSharedPtr<ISequencer>& Sequencer, const IPropertyHandle& PropertyHandle);`
- L298 _public prototype_ `void UpdateSceneObjectorGuidsForItems(ISequencer* InSequencer);` — function to make sure we have Guids stored on the anim layers now so we can correctly keep track of spawned actors.
- L301 _public prototype_ `void ApplyControlSelectionToSequencer(bool bSelect = true) const;` — Sets sequencer selection for this layer's currently selected controls
- L304 _public prototype_ `bool HasSectionsInCurrentEditorSelection() const;` — Returns true if the layer has sections that match the current editor selection
- L309 _private member_ `TMap<TWeakObjectPtr<UObject>, FAnimLayerItem> AnimLayerItems;` — `UPROPERTY(VisibleAnywhere, Category = "Data")`
- L312 _private member_ `FAnimLayerState State;` — `UPROPERTY(VisibleAnywhere, Category = "Data")`
- L315 _private member_ `TObjectPtr<UAnimLayerWeightProxy> WeightProxy;` — `UPROPERTY(Transient)`
- L319 _private member_ `int32 LayerIndex = INDEX_NONE;` — `UPROPERTY()` — cache of index in layer array
- L321 _private prototype_ `void SetSectionToKey() const;`
- L324 _private prototype_ `static bool IsAccepableNonControlRigObject(UObject* InObject);` — static helper functions
- L326 _private member_ `bool bIsSelectedInList = false;`

#### class `UAnimLayers`  
`class UAnimLayers : public UAssetUserData`  
_L334-402_
- reflection: `UCLASS(BlueprintType, MinimalAPI)`
- inherits: `UAssetUserData`
- desc: Link To Set of Anim Sequences that we may belinked to.
- L340 _public prototype_ `virtual void PostEditUndo() override;`
- L342 _public function_ `virtual bool IsEditorOnly() const override`
- L343 _public prototype_ `virtual void PostLoad() override;`
- L346 _public member_ `TArray<TObjectPtr<UAnimLayer>> AnimLayers;` — `UPROPERTY(BlueprintReadWrite, Category = Layers)`
- L349 _public member_ `bool bOpenUIOnOpen = true;` — `UPROPERTY()`
- L351 _public prototype_ `int32 GetAnimLayerIndex(UAnimLayer* InAnimLayer) const;`
- L352 _public prototype_ `bool DeleteAnimLayer(ISequencer* InSequencer, int32 Index);`
- L353 _public prototype_ `int32 DuplicateAnimLayer(ISequencer* InSequencer, int32 Index);`
- L354 _public prototype_ `int32 AddAnimLayerFromSelection(ISequencer* InSequencer);`
- L355 _public prototype_ `void GetAnimLayerStates(TArray<FAnimLayerState>& OutStates);`
- L356 _public prototype_ `bool MergeAnimLayers(TSharedPtr<ISequencer>& InSequencerPtr, const TArray<int32>& Indices, const FMergeAnimLayerSettings* InSettings);`
- L357 _public prototype_ `bool SetPassthroughKey(ISequencer* InSequencer, int32 Index);`
- L358 _public prototype_ `bool SetKey(ISequencer* InSequencer, int32 Index);`
- L359 _public prototype_ `bool ReorderAnimLayers(ISequencer* InSequencer, int32 OldIndex, int32 NewIndex);`
- L361 _public prototype_ `bool AdjustmentBlendLayers(ISequencer* InSequencer, int32 LayerIndex);` — will always blend to base for now
- L363 _public prototype_ `bool IsTrackOnSelectedLayer(const UMovieSceneTrack* InTrack)const;`
- L365 _public prototype_ `TArray<UMovieSceneSection*> GetSelectedLayerSections() const;`
- L368 _public prototype_ `static UAnimLayers* GetAnimLayers(ISequencer* InSequencer, bool bAddIfDoesNotExist = false);` — Get
- L369 _public prototype_ `static UAnimLayers* GetAnimLayers(ULevelSequence* InLevelSequence, bool bAddIfDoesNotExist = false);`
- L370 _public prototype_ `static bool HasAnimLayers(ISequencer* InSequencer);`
- L372 _public prototype_ `static TSharedPtr<ISequencer> GetSequencerFromAsset();`
- L375 _public prototype_ `DECLARE_EVENT_OneParam(UAnimLayers, FAnimLayerListChanged, UAnimLayers*);`
- L377 _public function_ `FAnimLayerListChanged& AnimLayerListChanged()`
- L380 _public function_ `FSimpleMulticastDelegate& GetOnSelectionChanged()` — Returns a delegate broadcast when anim outliner changed selection, both for anim layers self as well as for sequencer.
- L383 _private prototype_ `void AnimLayerListChangedBroadcast();`
- L384 _private member_ `FAnimLayerListChanged OnAnimLayerListChanged;`
- L385 _private prototype_ `void AddBaseLayer();`
- L386 _private prototype_ `bool SetKeyValueOrPassthrough(ISequencer* InSequencer, int32 Index, bool bJustValue);`
- L389 _private prototype_ `void SetAnimLayerIndices(bool bResetSectionOrders);` — Set the anim layer index values, if bResetSectionOrders is true we will also go through and make sure the sections are also in order
- L391 _private prototype_ `void GetTracksAndSections(TMap<UMovieSceneTrack*, TArray<TPair<UAnimLayer*, UMovieSceneSection*>>>& OutTracksAndOrderedSections);` — get set of tracks and their sections for each anim layer
- L393 _private prototype_ `void SetTrackRowForSections(const TMap<UMovieSceneTrack*, TArray<TPair<UAnimLayer*, UMovieSceneSection*>>>& TracksAndOrderedSections);` — setup track information (name, mute state etc), for sections on the track per anim layer
- L395 _private member_ `FSimpleMulticastDelegate OnSelectionChanged;` — A delegate broadcast when the selected layer sections changed
- L398 _public prototype_ `void SetUpBaseLayerSections();`
- L400 _public prototype_ `static void SetUpSectionDefaults(ISequencer* SequencerPtr, UAnimLayer* Layer, UMovieSceneTrack* InTrack, UMovieSceneSection* InSection, FMovieSceneFloatChannel* FloatChannel);`
- L401 _public prototype_ `static void SetUpControlRigSection(UMovieSceneControlRigParameterSection* InSection, TArray<FName>& ControlNames);`

#### struct `FAnimLayersScopedSelection`  
`struct FAnimLayersScopedSelection`  
_L405-422_
- desc: A scope in which selection can occur in anim layers. Raises OnSelectionChanged when destructed.
- L407 _public function_ `FAnimLayersScopedSelection(UAnimLayers & AnimLayers) : WeakAnimLayers(&AnimLayers)`
- L412 _public function_ `~FAnimLayersScopedSelection()`
- L421 _private member_ `TWeakObjectPtr<UAnimLayers> WeakAnimLayers;`

#### Free symbols / members of external scopes

- L26 _namespace_ `namespace UE`
- L26 _namespace_ `namespace Sequencer` (scope `UE`)
- L375 _delegate_ `DECLARE_EVENT_OneParam(UAnimLayers, FAnimLayerListChanged, UAnimLayers*);`

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/Sequencer/AnimLayers/SAnimLayerComboBox.h` (Private)


#### class `SAnimLayerComboBox`  
`class SAnimLayerComboBox : public SCompoundWidget`  
_L19-114_
- inherits: `SCompoundWidget`
- L30 _public typedef_ `using FAnimLayerItemPtr = TSharedPtr<FItem>;`
- L32 _public function_ `DECLARE_DELEGATE_OneParam(FOnAnimLayerChanged, UAnimLayer*) SLATE_BEGIN_ARGS(SAnimLayerComboBox) : _MinDesiredWidth(120.f)`
- L37 _public prototype_ `SLATE_ATTRIBUTE(FOptionalSize, MinDesiredWidth) SLATE_EVENT(FOnAnimLayerChanged, OnAnimLayerChanged) SLATE_END_ARGS() virtual ~SAnimLayerComboBox() override;`
- L46 _public prototype_ `void Construct(const FArguments& InArgs, const TWeakPtr<ISequencer>& InWeakSequencer);`
- L49 _public prototype_ `virtual void Tick(const FGeometry& InGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L52 _public prototype_ `void SetSelectedAnimLayer(UAnimLayer* const InAnimLayer);`
- L53 _public prototype_ `void SetSelectedAnimLayers(const TSet<UAnimLayer*>& InSelectedLayers);`
- L54 _public prototype_ `TSet<UAnimLayer*> GetSelectedAnimLayers() const;`
- L57 _protected prototype_ `TSharedRef<ITableRow> GenerateListRow(const FAnimLayerItemPtr InItem, const TSharedRef<STableViewBase>& InOwnerTable);`
- L59 _protected prototype_ `void ReloadAnimLayerData();`
- L61 _protected prototype_ `void RemoveAnimLayerBindings();`
- L63 _protected prototype_ `void ResetCache();`
- L65 _protected prototype_ `void SyncListSelectionToAnimLayerSelection();`
- L67 _protected prototype_ `void HandleComboMenuOpenChanged(const bool bInOpen);`
- L69 _protected prototype_ `EActiveTimerReturnType HandleDeferredSyncSelection(const double InCurrentTime, const float InDeltaTime);`
- L71 _protected prototype_ `void HandleAnimLayerSelectionChanged();`
- L72 _protected prototype_ `void HandleAnimLayersChanged(UAnimLayers* const InAnimLayers);`
- L74 _protected prototype_ `void HandleSelectionChanged(const FAnimLayerItemPtr InItem, const ESelectInfo::Type InSelectInfo);`
- L76 _protected prototype_ `void UpdateSelectedContent();`
- L78 _protected prototype_ `FAnimLayerItemPtr FindItemByAnimLayer(UAnimLayer* const InAnimLayer) const;`
- L80 _protected prototype_ `UMovieScene* GetFocusedMovieScene() const;`
- L82 _protected prototype_ `UAnimLayer* FindLayerForSection(UMovieSceneSection* const InSection) const;`
- L84 _protected prototype_ `void RebuildSectionToLayerMap();`
- L86 _protected prototype_ `bool GetSingleAnimLayerFromSections(const TArray<UMovieSceneSection*>& InSections , UAnimLayer*& OutLayer, bool& bOutMultiple) const;`
- L89 _protected prototype_ `FAnimLayerItemPtr GetBaseLayerItem() const;`
- L91 _protected prototype_ `void ShowMultipleSelectedContent();`
- L93 _protected prototype_ `TSet<FAnimLayerItemPtr> GetSelectedItems() const;`
- L95 _protected member_ `TWeakPtr<ISequencer> WeakSequencer;`
- L97 _protected member_ `FOnAnimLayerChanged AnimLayerChangedDelegate;`
- L99 _protected member_ `TSharedPtr<SComboButton> ComboButton;`
- L100 _protected member_ `TSharedPtr<SListView<FAnimLayerItemPtr>> ListView;`
- L101 _protected member_ `TSharedPtr<SBox> SelectedContent;`
- L103 _protected member_ `FGuid LastMovieSceneSig;`
- L105 _protected member_ `TArray<FAnimLayerItemPtr> AnimLayerItems;`
- L107 _protected member_ `FDelegateHandle AnimLayersChangedDelegate;`
- L108 _protected member_ `FDelegateHandle AnimLayerSelectionChangedDelegate;`
- L110 _protected member_ `TMap<TWeakObjectPtr<UMovieSceneSection>, TWeakObjectPtr<UAnimLayer>> SectionToLayerMap;`
- L112 _protected member_ `FAnimLayerItemPtr CachedSelectedItem;`
- L113 _protected member_ `int32 CachedSelectedCount = INDEX_NONE;`

#### struct `SAnimLayerComboBox::FItem`  
`struct FItem`  
_L22-29_
- L24 _public function_ `FItem(const TWeakObjectPtr<UAnimLayer>& InAnimLayer) : WeakAnimLayer(InAnimLayer)`
- L28 _public member_ `TWeakObjectPtr<UAnimLayer> WeakAnimLayer;`

#### Free symbols / members of external scopes

- L32 _delegate_ `DECLARE_DELEGATE_OneParam(FOnAnimLayerChanged, UAnimLayer*) SLATE_BEGIN_ARGS(SAnimLayerComboBox) : _MinDesiredWidth(120.f) {} SLATE_ATTRIBUTE(FOptionalSize, MinDesiredWidth) SLATE_EVENT(FOnAnimLayerChanged, OnAnimLayerChanged) SLATE_END_ARGS() virtual ~SAnimLayerComboBox() override;`

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/Sequencer/AnimLayers/SAnimLayerComboBoxItem.h` (Private)


#### class `SAnimLayerComboBoxItem`  
`class SAnimLayerComboBoxItem : public SCompoundWidget`  
_L12-33_
- inherits: `SCompoundWidget`
- L15 _public function_ `SLATE_BEGIN_ARGS(SAnimLayerComboBoxItem)`
- L16 _public prototype_ `SLATE_ATTRIBUTE(TSharedPtr<SAnimLayerComboBox::FItem>, Item) SLATE_ATTRIBUTE(FSlateColor, TextColor) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L23 _protected prototype_ `FSlateColor GetIconColor() const;`
- L24 _protected prototype_ `EVisibility GetIconVisibility() const;`
- L26 _protected prototype_ `FText GetDisplayText() const;`
- L27 _protected prototype_ `FSlateColor GetDisplayTextColor() const;`
- L29 _protected prototype_ `UAnimLayer* GetAnimLayer() const;`
- L31 _protected member_ `TAttribute<TSharedPtr<SAnimLayerComboBox::FItem>> Item;`
- L32 _protected member_ `TAttribute<FSlateColor> TextColor;`

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/Sequencer/AnimLayers/SAnimLayers.h` (Private)


#### class `SAnimLayers`  
`class SAnimLayers : public FControlRigBaseDockableView, public SCompoundWidget, public FSelfRegisteringEditorUndoClient`  
_L22-74_
- inherits: `FControlRigBaseDockableView,SCompoundWidget,FSelfRegisteringEditorUndoClient`
- L24 _private function_ `SLATE_BEGIN_ARGS(SAnimLayers)`
- L26 _private prototype_ `SAnimLayers();`
- L27 _private prototype_ `~SAnimLayers();`
- L29 _private prototype_ `void Construct(const FArguments& InArgs, FControlRigEditMode& InEditMode);`
- L31 _private prototype_ `void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;` — SCompuntWidget
- L34 _private function_ `virtual TSharedRef<FControlRigBaseDockableView> AsSharedWidget() override` — FControlRigBaseDockableView overrides
- L35 _private prototype_ `virtual void SetEditMode(FControlRigEditMode& InEditMode) override;`
- L36 _private prototype_ `virtual void HandleControlAdded(UControlRig* ControlRig, bool bIsAdded) override;`
- L40 _private prototype_ `virtual void PostUndo(bool bSuccess) override;`
- L41 _private prototype_ `virtual void PostRedo(bool bSuccess) override;`
- L44 _private prototype_ `void HandleOnControlRigBound(UControlRig* InControlRig);`
- L45 _private prototype_ `void HandleOnObjectBoundToControlRig(UObject* InObject);`
- L46 _private prototype_ `virtual void HandleControlSelected(UControlRig* Subject, FRigControlElement* InControl, bool bSelected) override;`
- L47 _private prototype_ `void OnObjectsReplaced(const TMap<UObject*, UObject*>& OldToNewInstanceMap);`
- L50 _private member_ `TArray<TWeakObjectPtr<UControlRig>> BoundControlRigs;` — set of control rigs we are bound too and need to clear delegates from
- L53 _private prototype_ `void RegisterSelectionChanged();` — actor selection changing
- L54 _private prototype_ `void OnActorSelectionChanged(const TArray<UObject*>& NewSelection, bool bForceRefresh);`
- L55 _private member_ `FDelegateHandle OnSelectionChangedHandle;`
- L56 _private member_ `FDelegateHandle OnAnimLayerListChangedHandle;`
- L59 _private prototype_ `void OnActivateSequence(FMovieSceneSequenceIDRef ID);` — sequencer changing so need to refresh list or update weight
- L60 _private prototype_ `void OnGlobalTimeChanged();`
- L61 _private prototype_ `void OnMovieSceneDataChanged(EMovieSceneDataChangeType);`
- L62 _private member_ `FGuid LastMovieSceneSig = FGuid();`
- L65 _private prototype_ `FReply OnAddClicked();`
- L66 _private prototype_ `FReply OnSelectionFilterClicked();`
- L67 _private prototype_ `bool IsSelectionFilterActive() const;`
- L68 _private member_ `TSharedPtr<FAnimLayerController> AnimLayerController;`
- L69 _private member_ `TWeakObjectPtr<UAnimLayers> AnimLayers;`
- L72 _private function_ `virtual bool SupportsKeyboardFocus() const override` — Keyboard interaction for Sequencer hotkeys
- L73 _private prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;`

#### class `SAnimWeightDetails`  
`class SAnimWeightDetails : public SCompoundWidget`  
_L76-90_
- inherits: `SCompoundWidget`
- L79 _private function_ `SLATE_BEGIN_ARGS(SAnimWeightDetails)`
- L82 _private prototype_ `~SAnimWeightDetails();`
- L84 _private prototype_ `void Construct(const FArguments& InArgs, FControlRigEditMode* InEditMode, UObject* InWeightObject);`
- L88 _private member_ `TSharedPtr<IDetailsView> WeightView;`

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/Sequencer/ControlRigParameterTrackEditor.h` (Private)


#### class `SCollapseControlsWidget`  
`class SCollapseControlsWidget : public SCompoundWidget`  
_L61-89_
- inherits: `SCompoundWidget`
- desc: Widget allowing collapsing of controls
- L65 _public function_ `SLATE_BEGIN_ARGS(SCollapseControlsWidget) : _Sequencer(nullptr)`
- L68 _public prototype_ `SLATE_ARGUMENT(TWeakPtr<ISequencer>, Sequencer) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L72 _public prototype_ `virtual ~SCollapseControlsWidget() override = default;`
- L74 _public prototype_ `FReply OpenDialog(bool bModal = true);`
- L75 _public prototype_ `void CloseDialog();`
- L77 _public function_ `void SetCollapseCB(FCollapseControlsCB& InCB)`
- L79 _private prototype_ `void Collapse();`
- L81 _private member_ `TWeakPtr<ISequencer> Sequencer;`
- L83 _private member_ `static TOptional<FBakingAnimationKeySettings> CollapseControlsSettings;` — static to be reused
- L85 _private member_ `TSharedPtr < TStructOnScope<FBakingAnimationKeySettings>> Settings;` — structonscope for details panel
- L86 _private member_ `TWeakPtr<SWindow> DialogWindow;`
- L87 _private member_ `TSharedPtr<IStructureDetailsView> DetailsView;`
- L88 _private member_ `FCollapseControlsCB CollapseCB;`

#### struct `FControlRigKeyAddParams`  
`struct FControlRigKeyAddParams`  
_L92-96_
- desc: Per-control data for batched key operations. Caller fills both fields.
- L94 _public member_ `FName RigControlName;`
- L95 _public member_ `FRigControlElement* ControlElement = nullptr;`

#### struct `FControlRigSectionKeyData`  
`struct FControlRigSectionKeyData`  
_L100-104_
- desc: All data needed to key a single section: the controls to key and one shared key array whose indices are set by GetControlRigKeys and consumed by AddKeysToSection.
- L102 _public member_ `TArray<FControlRigKeyAddParams> Params;`
- L103 _public member_ `TSharedPtr<FGeneratedTrackKeys> GeneratedKeys;` — one instance for all Params in this section

#### class `FControlRigParameterTrackEditor`  
`class FControlRigParameterTrackEditor : public FKeyframeTrackEditor<UMovieSceneControlRigParameterTrack>, public IMovieSceneToolsAnimationBakeHelper, public FEditorUndoClient, public IMovieSceneAnimMixerItemMenuProvider`  
_L112-509_
- inherits: `FKeyframeTrackEditor<UMovieSceneControlRigParameterTrack>,IMovieSceneToolsAnimationBakeHelper,FEditorUndoClient,IMovieSceneAnimMixerItemMenuProvider`
- desc: Tools for animation tracks
- L121 _public prototype_ `FControlRigParameterTrackEditor(TSharedRef<ISequencer> InSequencer);` — Constructor @param InSequencer The sequencer instance to be used by this tool
- L124 _public prototype_ `virtual ~FControlRigParameterTrackEditor();` — Virtual destructor.
- L132 _public prototype_ `static TSharedRef<ISequencerTrackEditor> CreateTrackEditor(TSharedRef<ISequencer> OwningSequencer);` — Creates an instance of this class.  Called by a sequencer @param OwningSequencer The sequencer instance to be used by this tool @return The new instance of this class
- L141 _public member_ `static FControlRigParameterTrackEditor* CurrentEditor;` — Cached version of the current track editor, that lets other animaiton tools call specific functions. in particularly setting keys on current values
- L145 _public prototype_ `virtual FText GetDisplayName() const override;` — ISequencerTrackEditor interface
- L146 _public prototype_ `virtual void OnInitialize() override;`
- L147 _public prototype_ `virtual void OnRelease() override;`
- L148 _public prototype_ `virtual TSharedPtr<SWidget> BuildOutlinerEditWidget(const FGuid& ObjectBinding, UMovieSceneTrack* Track, const FBuildEditWidgetParams& Params) override;`
- L149 _public prototype_ `virtual void BuildObjectBindingContextMenu(FMenuBuilder& MenuBuilder, const TArray<FGuid>& ObjectBindings, const UClass* ObjectClass) override;`
- L150 _public prototype_ `virtual void BuildObjectBindingTrackMenu(FMenuBuilder& MenuBuilder, const TArray<FGuid>& ObjectBindings, const UClass* ObjectClass) override;`
- L151 _public prototype_ `virtual TSharedRef<ISequencerSection> MakeSectionInterface(UMovieSceneSection& SectionObject, UMovieSceneTrack& Track, FGuid ObjectBinding) override;`
- L152 _public prototype_ `virtual const FSlateBrush* GetIconBrush() const override;`
- L153 _public prototype_ `virtual bool SupportsType(TSubclassOf<UMovieSceneTrack> Type) const override;`
- L154 _public prototype_ `virtual bool SupportsSequence(UMovieSceneSequence* InSequence) const override;`
- L155 _public function_ `virtual bool HasTransformKeyBindings() const override`
- L156 _public prototype_ `virtual bool CanAddTransformKeysForSelectedObjects() const override;`
- L157 _public prototype_ `virtual void OnAddTransformKeysForSelectedObjects(EMovieSceneTransformChannel Channel);`
- L158 _public prototype_ `virtual void OnDeleteTransformKeysForSelectedObjects(EMovieSceneTransformChannel Channel) override;`
- L159 _public prototype_ `virtual bool HasTransformKeyOverridePriority() const override;`
- L160 _public prototype_ `virtual void ObjectImplicitlyAdded(UObject* InObject) override;`
- L161 _public prototype_ `virtual void ObjectImplicitlyRemoved(UObject* InObject) override;`
- L162 _public prototype_ `virtual void BuildTrackContextMenu(FMenuBuilder& MenuBuilder, UMovieSceneTrack* InTrack) override;`
- L163 _public prototype_ `virtual bool HandleAssetAdded(UObject* Asset, const FGuid& TargetObjectGuid) override;`
- L164 _public prototype_ `virtual void ProcessKeyOperation(FFrameNumber InKeyTime, const UE::Sequencer::FKeyOperation& Operation, ISequencer& InSequencer, TArray<UE::Sequencer::FAddKeyResult>* OutResults) override;`
- L167 _public prototype_ `virtual void PostEvaluation(UMovieScene* MovieScene, FFrameNumber Frame);` — IMovieSceneToolsAnimationBakeHelper
- L170 _public prototype_ `virtual bool MatchesContext(const FTransactionContext& InContext, const TArray<TPair<UObject*, FTransactionObjectEvent>>& TransactionObjects) const override;` — FEditorUndoClient Interface
- L171 _public prototype_ `virtual void PostUndo(bool bSuccess) override;`
- L172 _public function_ `virtual void PostRedo(bool bSuccess) override`
- L175 _public prototype_ `virtual const UClass* GetHandledMixerItemClass() const override;` — IMovieSceneAnimMixerItemMenuProvider Interface
- L176 _public prototype_ `virtual void PopulateAddMixerItemMenu(FMenuBuilder& MenuBuilder, TArray<FGuid> ObjectBindings, UMovieSceneTrack* Track, TSharedPtr<ISequencer> Sequencer, int32 RowIndex) override;`
- L177 _public function_ `virtual int32 GetMixerItemMenuPriority() const override`
- L178 _public prototype_ `virtual void PopulateObjectBindingAnimationMenu(FMenuBuilder& MenuBuilder, const TArray<FGuid>& ObjectBindings, const UClass* ObjectClass, bool bIsInsideSubmenu) override;`
- L181 _public prototype_ `void SetKeysOnControls(const TMap<UControlRig*, TArray<FRigElementKey>>& Controls, EMovieSceneTransformChannel Channel);` — function to set keys on controls
- L184 _public function_ `bool IsDoingSelection() const` — Whether the selection is currently being changed by the track editor.
- L188 _private prototype_ `void ProcessKeyOperation(UObject* ObjectToKey, UMovieSceneControlRigParameterTrack* Track, TArrayView<const UE::Sequencer::FKeySectionOperation> SectionsToKey, ISequencer& InSequencer, FFrameNumber KeyTime, TArray<UE::Sequencer::FAddKeyResult>* OutResults);`
- L189 _private prototype_ `UE::MovieScene::FControlRigParameterValues GetRecomposedControlValues(UMovieSceneControlRigParameterTrack* Track, UMovieSceneControlRigParameterSection* Section, FFrameNumber KeyTime);`
- L191 _private prototype_ `void HandleAddTrackSubMenu(FMenuBuilder& MenuBuilder, TArray<FGuid> ObjectBindings, UMovieSceneTrack* Track, TFunction<UMovieSceneControlRigParameterTrack*(FGuid)> InTrackCreationCallback = nullptr);`
- L193 _private prototype_ `void ToggleIsAdditiveControlRig();`
- L194 _private prototype_ `bool IsToggleIsAdditiveControlRig();`
- L196 _private prototype_ `void ToggleFilterAssetBySkeleton();`
- L197 _private prototype_ `bool IsToggleFilterAssetBySkeleton();`
- L199 _private prototype_ `void ToggleFilterAssetByAnimatableControls();`
- L200 _private prototype_ `bool IsToggleFilterAssetByAnimatableControls();`
- L201 _private prototype_ `void SelectSequencerNodeInSection(UMovieSceneControlRigParameterSection* ParamSection, const FName& ControlName, bool bSelected);`
- L204 _private prototype_ `void AddControlRig(FControlRigAssetStrongReference InSource, UObject* BoundActor, FGuid ObjectBinding);` — Control Rig Picked
- L205 _private prototype_ `void AddControlRig(const FControlRigAssetStrongReference InSource, UObject* BoundActor, FGuid ObjectBinding, UControlRig* InExistingControlRig, TFunction<UMovieSceneControlRigParameterTrack*(FGuid)> InTrackCreationCallback = nullptr);`
- L206 _private prototype_ `void AddControlRig(const FAssetData& InAsset, UObject* BoundActor, FGuid ObjectBinding, TFunction<UMovieSceneControlRigParameterTrack*(FGuid)> InTrackCreationCallback = nullptr);`
- L207 _private prototype_ `void AddControlRig(const TArray<FAssetData>& InAssets, UObject* BoundActor, FGuid ObjectBinding, TFunction<UMovieSceneControlRigParameterTrack*(FGuid)> InTrackCreationCallback = nullptr);`
- L208 _private prototype_ `void AddFKControlRig(UObject* BoundActor, FGuid ObjectBinding, TFunction<UMovieSceneControlRigParameterTrack*(FGuid)> InTrackCreationCallback = nullptr);`
- L209 _private prototype_ `void AddControlRigFromComponent(FGuid InGuid);`
- L211 _private prototype_ `bool IsControlRigAllowed(const FAssetData& AssetData, TArray<FControlRigAssetStrongReference> ExistingRigs, USkeleton* Skeleton);`
- L214 _private prototype_ `void OnSelectionChanged(TArray<UMovieSceneTrack*> InTracks);` — Delegate for Selection Changed Event
- L217 _private prototype_ `FEditorModeTools* GetEditorModeTools() const;` — Returns the Edit Mode tools manager hosting the edit mode
- L218 _private prototype_ `FControlRigEditMode* GetEditMode(bool bForceActivate = false) const;`
- L221 _private prototype_ `void OnSequencerDataChanged(EMovieSceneDataChangeType DataChangeType);` — Delegate for MovieScene Changing so we can see if our track got deleted
- L224 _private prototype_ `void OnChannelChanged(const TArray<FFrameNumber>& Frames, const FMovieSceneChannelMetaData* MetaData, UMovieSceneSection* InSection);` — Delegate for when track immediately changes, so we need to do an interaction edit for things like fk/ik
- L227 _private prototype_ `void OnMovieSceneBindingsChanged();` — Delegate for when bindings changed, anim layers need to get updated
- L230 _private prototype_ `void OnActivateSequenceChanged(FMovieSceneSequenceIDRef ID);` — Delegate for difference focused movie scene sequence
- L231 _private member_ `FTimerHandle DeactivateModeHandle;`
- L232 _private member_ `FTimerHandle ActivateModeHandle;`
- L235 _private prototype_ `void HandleActorAdded(AActor* Actor, FGuid TargetObjectGuid);` — Actor Added Delegate
- L237 _private prototype_ `void AddTrackForComponent(USceneComponent* Component, FGuid Binding);` — Add Control Rig Tracks For Skelmesh Components
- L240 _private prototype_ `void HandleControlModified(UControlRig* Subject, FRigControlElement* ControlElement, const FRigControlModifiedContext& Context);` — Control Rig Delegates
- L241 _private prototype_ `void HandleControlSelected(UControlRig* Subject, FRigControlElement* ControlElement, bool bSelected);`
- L242 _private prototype_ `void HandleControlUndoBracket(UControlRig* Subject, bool bOpenUndoBracket);`
- L243 _private prototype_ `void HandleOnPostConstructed(UControlRig* Subject, const FName& InEventName);`
- L244 _private prototype_ `void HandleOnControlRigBound(UControlRig* InControlRig);`
- L245 _private prototype_ `void HandleOnObjectBoundToControlRig(UObject* InObject);`
- L248 _private prototype_ `void ClearOutAllSpaceAndConstraintDelegates(const UControlRig* InOptionalControlRig = nullptr) const;` — if rig not set then we clear delegates for everyone
- L251 _private prototype_ `void HandleOnSpaceAdded( UMovieSceneControlRigParameterSection* Section, const FName& ControlName, FMovieSceneControlRigSpaceChannel* Channel);` — SpaceChannel Delegates
- L255 _private prototype_ `void HandleSpaceKeyDeleted( UMovieSceneControlRigParameterSection* Section, FMovieSceneControlRigSpaceChannel* Channel, const TArray<FKeyAddOrDeleteEventItem>& DeletedItems) const;`
- L259 _private prototype_ `static void HandleSpaceKeyMoved( UMovieSceneControlRigParameterSection* Section, FMovieSceneControlRigSpaceChannel* Channel, const TArray<FKeyMoveEventItem>& MovedItems);`
- L265 _private prototype_ `void HandleOnConstraintAdded( IMovieSceneConstrainedSection* InSection, FMovieSceneConstraintChannel* InConstraintChannel);` — ConstraintChannel Delegates
- L268 _private prototype_ `void HandleConstraintKeyDeleted( IMovieSceneConstrainedSection* InSection, const FMovieSceneConstraintChannel* InConstraintChannel, const TArray<FKeyAddOrDeleteEventItem>& InDeletedItems) const;`
- L272 _private prototype_ `static void HandleConstraintKeyMoved( IMovieSceneConstrainedSection* InSection, const FMovieSceneConstraintChannel* InConstraintChannel, const TArray<FKeyMoveEventItem>& InMovedItems);`
- L276 _private prototype_ `void HandleConstraintRemoved(IMovieSceneConstrainedSection* InSection);`
- L277 _private prototype_ `void HandleConstraintPropertyChanged(UTickableTransformConstraint* InConstraint, const FPropertyChangedEvent& InPropertyChangedEvent) const;`
- L280 _private prototype_ `void SelectRigsAndControls(UControlRig* Subject, const TArray<const IKeyArea*>& KeyAreas);` — Select control rig if not selected, select controls from key areas
- L283 _private prototype_ `FMovieSceneTrackEditor::FFindOrCreateHandleResult FindOrCreateHandleToObject(UObject* InObj, UControlRig* InControlRig = nullptr);` — Handle Creation for Skeleton, SkelMeshComp or Actor Owner, they may or may not have a binding, use optional control rig to pick one
- L286 _private prototype_ `FMovieSceneTrackEditor::FFindOrCreateTrackResult FindOrCreateControlRigTrackForObject(FGuid ObjectBinding, UControlRig* ControlRig, FName PropertyName = NAME_None, bool bCreateTrackIfMissing = true);` — Handle Creation for control rig track given the object binding and the control rig
- L289 _private prototype_ `void ImportFBX(UMovieSceneControlRigParameterTrack* InTrack, UMovieSceneControlRigParameterSection* InSection, TArray<FRigControlFBXNodeAndChannels>* NodeAndChannels);` — Import FBX
- L293 _private prototype_ `void ExportFBX(UMovieSceneControlRigParameterTrack* InTrack, UMovieSceneControlRigParameterSection* InSection);` — Export FBX
- L296 _private prototype_ `UMovieSceneControlRigParameterTrack* FindTrack(const UControlRig* InControlRig) const;` — Find Track for given ControlRig
- L299 _private prototype_ `void SelectFKBonesToAnimate(UFKControlRig* FKControlRig, UMovieSceneControlRigParameterTrack* Track);` — Select Bones to Animate on FK Rig
- L302 _private prototype_ `void BakeToControlRigSubMenu(FMenuBuilder& MenuBuilder, FGuid ObjectBinding, UObject* BoundObject, USkeletalMeshComponent* SkelMeshComp,USkeleton* Skeleton);` — Bake To Control Rig Sub Menu
- L305 _private prototype_ `void BakeToControlRig(const FControlRigAssetStrongReference& InAssetReference, FGuid ObjectBinding,UObject* BoundObject, USkeletalMeshComponent* SkelMeshComp, USkeleton* Skeleton);` — Bake To Control Rig Sub Menu
- L308 _private prototype_ `void BakeInvertedPose(UControlRig* InControlRig, UMovieSceneControlRigParameterTrack* Track);` — Bake Inersion of Additive Control Rig to Rest Pose
- L311 _private prototype_ `bool IsLayered(UMovieSceneControlRigParameterTrack* Track) const;` — Return true if the control rig is in layered mode
- L314 _private prototype_ `void ConvertIsLayered(UMovieSceneControlRigParameterTrack* Track);` — Convert an absolute control rit to a layered control rig
- L317 _private prototype_ `void RecreateControlRigWithNewSettings(UMovieSceneControlRigParameterTrack* Track);` — Change rig settings and recreates the rig using the new settings
- L319 _private prototype_ `bool CanRecreateControlRigWithNewSettings(UMovieSceneControlRigParameterTrack* Track);`
- L321 _private prototype_ `void CreateAndShowRigSettingsWindow(UMovieSceneControlRigParameterTrack* Track);`
- L352 _private member_ `TSharedPtr<FRecreateRigOperator> RecreateRigOperator;`
- L354 _private prototype_ `void ResetRecreateRigOperatorIfNeeded(TSharedRef<FControlRigParameterTrackEditor::FRecreateRigOperator> InRequestingOperator);`
- L357 _public prototype_ `void SetUpEditModeIfNeeded(UControlRig* ControlRig);` — Set Up EditMode for Specified Control Rig
- L360 _public prototype_ `void IterateTracks(TFunctionRef<bool(UMovieSceneControlRigParameterTrack*, FGuid)> Callback) const;` — Helper functions to iterate over UMovieSceneControlRigParameterTracks in the currently focussed MovieScene
- L363 _private member_ `TSharedPtr<FUICommandList> CommandBindings;` — Command Bindings added by the Transform Track Editor to Sequencer and curve editor.
- L364 _private member_ `FAcquiredResources AcquiredResources;`
- L368 _public prototype_ `void AddControlKeys(UObject* InObject, UControlRig* InControlRig, FName PropertyName, FName ParameterName, EControlRigContextChannelToKey ChannelsToKey, ESequencerKeyMode KeyMode, float InLocalTime, const bool bInConstraintSpace = false);`
- L371 _public prototype_ `void GetControlRigKeys(UControlRig* InControlRig, FName ParameterName, EControlRigContextChannelToKey ChannelsToKey, ESequencerKeyMode KeyMode, UMovieSceneControlRigParameterSection* SectionToKey, FGeneratedTrackKeys& OutGeneratedKeys, const bool bInConstraintSpace = false);`
- L374 _public prototype_ `FKeyPropertyResult AddKeysToControlRig( UObject* InObject, UControlRig* InControlRig, FFrameNumber KeyTime, FFrameNumber EvaluateTime, FGeneratedTrackKeys& GeneratedKeys, ESequencerKeyMode KeyMode, TSubclassOf<UMovieSceneTrack> TrackClass, FName ControlRigName, FName RigControlName);`
- L377 _public prototype_ `FKeyPropertyResult AddKeysToControlRigHandle(UObject* InObject, UControlRig* InControlRig, FGuid ObjectHandle, FFrameNumber KeyTime, FFrameNumber EvaluateTime, FGeneratedTrackKeys& GeneratedKeys, ESequencerKeyMode KeyMode, TSubclassOf<UMovieSceneTrack> TrackClass, FName ControlRigName, FName RigControlName);`
- L382 _public prototype_ `void AddControlKeys(UObject* InObject, UControlRig* InControlRig, FName ControlRigName, TArray<FControlRigKeyAddParams>& InOutParams, EControlRigContextChannelToKey ChannelsToKey, ESequencerKeyMode KeyMode, float InLocalTime, const bool bInConstraintSpace = false);` — Batched overload: groups controls by section, resolves handle/track once, keys all in one transaction.
- L388 _public prototype_ `void GetControlRigKeys(UControlRig* InControlRig, FControlRigSectionParamMap& InOutSectionParamMap, EControlRigContextChannelToKey ChannelsToKey, ESequencerKeyMode KeyMode, const bool bInConstraintSpace = false);` — Batched overload: populates GeneratedKeys for every param in a single pass over the control hierarchy.
- L403 _public prototype_ `bool ModifyOurGeneratedKeysByCurrentAndWeight(UObject* Object, UControlRig* InControlRig, FName RigControlName, UMovieSceneTrack *Track, UMovieSceneSection* SectionToKey, FFrameNumber EvaluateTime, FGeneratedTrackKeys& InOutGeneratedTotalKeys, float Weight) const;` — Modify the passed in Generated Keys by the current tracks values and weight at the passed in time. @param Object The handle to the object modify @param Track The track we are modifying @param SectionToKey The Sections Channels we will be modifiying @param Time The Time at which to evaluate @param InOutGeneratedTrackKeys The Keys we need to modify. We change these values. @param Weight The weight we need to modify the values by.
- L406 _public prototype_ `static bool CollapseAllLayers(TSharedPtr<ISequencer>& SequencerPtr, UMovieSceneTrack* OwnerTrack, const FBakingAnimationKeySettings& InSettings);` — / Function to collapse all layers from this section onto the first absoluate layer.
- L409 _public prototype_ `static bool LoadAnimationIntoSection(const TSharedPtr<ISequencer>& InSequencer, UAnimSequence* AnimSequence, USkeletalMeshComponent* SkelMeshComp, FFrameNumber StartFrame, bool bReduceKeys, const FSmartReduceParams& ReduceParams, bool bResetControls,const TOptional<TRange<FFrameNumber>> &InFrameRamge, bool bOntoSelectedControls, UMovieSceneControlRigParameterSection* ParamSection);` — /  Function to load animation into a section, returns true if successful
- L414 _public prototype_ `static void SmartReduce(const TSharedPtr<ISequencer>& InSequencer, const FSmartReduceParams& InParams, UMovieSceneSection* InSection);` — /  Function to smart reduce all keys on all constraints based on the parameters
- L417 _public prototype_ `static void AddConstraintToSequencer(const TSharedPtr<ISequencer>& InSequencer, UTickableTransformConstraint* InConstraint, const UConstraintCreationOptions* InSequencerOptions = nullptr);` — Adds the constraint to sequencer and create the bindings if needed. Note that ControlRig Track auto-generation is disabled in this function.
- L421 _public prototype_ `static bool ShouldBeSelected(URigHierarchy* Hierarchy, FRigControlElement* ParentElement, FRigControlElement* ChildElement);` — Whether or not the Control Element should also be selected if the parent is selected, e.g. channel, hosted channel etc
- L424 _public prototype_ `static bool BakeTimeWarp(TSharedPtr<ISequencer>& InSequencer, UMovieSceneControlRigParameterSection* InSection);` — Bake the timewarp, per frame on the specified section
- L428 _private prototype_ `FKeyPropertyResult AddKeysToControlRigBatch(UObject* InObject, UControlRig* InControlRig, FGuid ObjectHandle, UMovieSceneControlRigParameterTrack* Track, FFrameNumber KeyTime, FFrameNumber EvaluateTime, FControlRigSectionParamMap& InOutSectionParamMap, ESequencerKeyMode KeyMode, FName ControlRigName);` — Iterates sections once each: extends bounds, one interrogation, one AddKeysToSection per section.
- L435 _private prototype_ `bool ModifyOurGeneratedKeysByCurrentAndWeight(UObject* Object, UControlRig* InControlRig, UMovieSceneTrack* Track, UMovieSceneSection* SectionToKey, FFrameNumber EvaluateTime, FControlRigSectionKeyData& InOutSectionKeyData, float Weight) const;` — Batched weight-blend: one track interrogation per section; writes into SectionKeyData.GeneratedKeys.
- L439 _private member_ `FDelegateHandle SelectionChangedHandle;`
- L440 _private member_ `FDelegateHandle SequencerChangedHandle;`
- L441 _private member_ `FDelegateHandle OnActivateSequenceChangedHandle;`
- L442 _private member_ `FDelegateHandle CurveChangedHandle;`
- L443 _private member_ `FDelegateHandle OnChannelChangedHandle;`
- L444 _private member_ `FDelegateHandle OnMovieSceneBindingsChangeHandle;`
- L445 _private member_ `FDelegateHandle OnMovieSceneChannelChangedHandle;`
- L446 _private member_ `FDelegateHandle OnActorAddedToSequencerHandle;`
- L451 _private member_ `TSet<FName> DisplayedControls;` — used to sync curve editor selections/displays on next tick for performance reasons
- L452 _private member_ `TSet<FName> UnDisplayedControls;`
- L453 _private member_ `bool bCurveDisplayTickIsPending;`
- L454 _private prototype_ `void BindControlRig(UControlRig* ControlRig, FGuid);`
- L455 _private prototype_ `void UnbindControlRig(UControlRig* ControlRig);`
- L456 _private prototype_ `void UnbindAllControlRigs();`
- L457 _private member_ `TMap<TWeakObjectPtr<UControlRig>, FGuid> BoundControlRigs;`
- L462 _private member_ `bool bIsDoingSelection;` — Guard to stop infinite loops when handling control selections
- L465 _private member_ `bool bSkipNextSelectionFromTimer;` — A flag to determine if the next update coming from the timer should be skipped
- L468 _private member_ `bool bIsLayeredControlRig;` — Whether or not this rig will be used as an layered control rig
- L471 _private member_ `bool bFilterAssetBySkeleton;` — Whether or not we should check Skeleton when filtering
- L474 _private member_ `bool bFilterAssetByAnimatableControls;` — Whether or not we should check for Animatable Controls when filtering
- L476 _private member_ `FRefreshAssetViewDelegate RefreshControlRigPickerDelegate;`
- L479 _private member_ `FTimerHandle UpdateSelectionTimerHandle;` — Handle to help updating selection on tick tick to avoid too many flooded selections
- L482 _private member_ `mutable TArray<UMovieSceneControlRigParameterSection*> SectionsGettingUndone;` — Array of sections that are getting undone, we need to recreate any space channel add,move key delegates to them
- L485 _private member_ `int32 ControlUndoBracket;` — An index counter for the opened undo brackets
- L488 _private member_ `int32 ControlChangedDuringUndoBracket;` — A counter for occurred control changes during a control undo bracket
- L491 _private member_ `static FCriticalSection ControlUndoTransactionMutex;` — Lock to avoid registering multiple transactions from different tracks at the same time
- L494 _private member_ `TSharedPtr<FScopedTransaction> ControlUndoTransaction;` — A transaction used to group multiple key events
- L497 _private member_ `static bool bAutoGenerateControlRigTrack;` — Controls if the control rig track for the default animating rig should be created
- L500 _private member_ `TSet<FDelegateHandle> ConstraintHandlesToClear;` — Set of delegate handles we have added delegate's too, need to clear them
- L506 _private member_ `static bool bControlRigEditModeWasOpen;` — Whether or not animation/control rig edit mode was open when we closed
- L508 _private member_ `static TArray <TPair<FControlRigAssetStrongReference, TArray<FName>>> PreviousSelectedControlRigs;` — Previous selection if open

#### struct `FControlRigParameterTrackEditor::FRecreateRigOperator`  
`struct FRecreateRigOperator : TSharedFromThis<FRecreateRigOperator>`  
_L325-350_
- inherits: `TSharedFromThis<FRecreateRigOperator>`
- L327 _public member_ `FInstancedPropertyBag SettingsForNewControlRig;`
- L329 _public member_ `TWeakPtr<FControlRigParameterTrackEditor> WeakTrackEditor;`
- L330 _public member_ `TWeakObjectPtr<UMovieSceneControlRigParameterTrack> WeakTrack;`
- L331 _public member_ `TWeakObjectPtr<UControlRig> WeakControlRig;`
- L333 _public member_ `TWeakPtr<SWindow> WeakWindow;`
- L334 _public member_ `TWeakPtr<IStructureDetailsView> WeakDetailsView;`
- L336 _public prototype_ `void Start( const TSharedRef<FControlRigParameterTrackEditor>& InTrackEditor, UMovieSceneControlRigParameterTrack* InTrack );`
- L341 _public prototype_ `~FRecreateRigOperator();`
- L343 _public prototype_ `bool IsValid();`
- L344 _public prototype_ `void Abort();`
- L345 _public prototype_ `void OnRigSettingsWindowClosed(const TSharedRef<SWindow>& Window);`
- L346 _public prototype_ `void RefreshSettingsFromControlRig();`
- L347 _public prototype_ `void OnPostControlRigForwardSolve_AnyThread(UControlRig*, const FName&);`
- L348 _public prototype_ `void OnRigSettingsChanged( const FPropertyChangedEvent& InEvent);`
- L349 _public prototype_ `bool IsEditingObject(UObject* InRigToCheck);`

#### class `FControlRigParameterSection`  
`class FControlRigParameterSection : public FSequencerSection`  
_L514-561_
- inherits: `FSequencerSection`
- desc: Class for control rig sections
- L524 _public function_ `FControlRigParameterSection(UMovieSceneSection& InSection, TWeakPtr<ISequencer> InSequencer) : FSequencerSection(InSection), WeakSequencer(InSequencer)` — Creates a new control rig property section. @param InSection The section object which is being displayed and edited. @param InSequencer The sequencer which is controlling this parameter section.
- L531 _public prototype_ `virtual void BuildSectionContextMenu(FMenuBuilder& MenuBuilder, const FGuid& InObjectBinding) override;`
- L534 _public prototype_ `virtual bool RequestDeleteCategory(const TArray<FName>& CategoryNamePath) override;`
- L535 _public prototype_ `virtual bool RequestDeleteKeyArea(const TArray<FName>& KeyAreaNamePath) override;`
- L538 _protected prototype_ `void LoadAnimationIntoSection(FMenuBuilder& MenuBuilder, FGuid ObjectBinding, USkeleton* Skeleton, UMovieSceneControlRigParameterSection* Section);` — Add Sub Menu
- L541 _protected prototype_ `bool ShouldFilterAsset(const FAssetData& AssetData);` — Animation sub menu filter function
- L544 _protected prototype_ `void OnAnimationAssetSelected(const FAssetData& AssetData,FGuid ObjectBinding, UMovieSceneControlRigParameterSection* Section);` — Animation asset selected
- L547 _protected prototype_ `void OnAnimationAssetEnterPressed(const TArray<FAssetData>& AssetData, FGuid ObjectBinding, UMovieSceneControlRigParameterSection* Section);` — Animation asset enter pressed
- L550 _protected prototype_ `void ShowSelectedControlsChannels();` — Select controls channels from selected pressed
- L552 _protected prototype_ `void ShowAllControlsChannels();` — Show all control channels
- L554 _protected prototype_ `void KeyZeroValue();`
- L555 _protected prototype_ `void KeyWeightValue(float Val);`
- L556 _protected prototype_ `void CollapseAllLayers();`
- L559 _protected member_ `TWeakPtr<ISequencer> WeakSequencer;` — The sequencer which is controlling this section.

#### Free symbols / members of external scopes

- L47 _namespace_ `namespace UE`
- L47 _namespace_ `namespace MovieScene` (scope `UE`)
- L52 _macro_ `#define UE_API CONTROLRIGEDITOR_API`
- L53 _externvar_ `extern TAutoConsoleVariable<bool> CVarSelectChildChannels;`
- L58 _delegate_ `DECLARE_DELEGATE_TwoParams(FCollapseControlsCB, TSharedPtr<ISequencer>& InSequencer, const FBakingAnimationKeySettings& InSettings);`
- L58 _prototype_ `DECLARE_DELEGATE_TwoParams(FCollapseControlsCB, TSharedPtr<ISequencer>& InSequencer, const FBakingAnimationKeySettings& InSettings);`
- L107 _typedef_ `using FControlRigSectionParamMap = TMap<UMovieSceneControlRigParameterSection*, FControlRigSectionKeyData>;` — Maps each section to its key data (params + one shared GeneratedKeys).

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/Sequencer/ControlRigSelectionUtils.h` (Private)


#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Sequencer` (scope `UE`)
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace ControlRig` (scope `UE`)
- L15 _prototype_ `bool IsAnimDetailsChangingSelection(FControlRigEditMode& InControlMode);` (scope `UE::ControlRig`) — @return Whether anim details is changing selection.
- L21 _prototype_ `void EnumerateParentControlChildren(const ISequencer& InSequencer, TFunctionRef<bool(const Sequencer::FViewModelPtr&)> InCallback);` (scope `UE::ControlRig`) — Goes through Sequencer selecting and finds all channels that are related to selected control rig controls. For example, if you have selected root_ctrl.Location.X then this lists out Location.Y, Rotation.Yaw, etc.
- L32 _prototype_ `void EnumerateOutlinerExtensionsForCurrentControlSelection( const ISequencer& InSequencer, TFunctionRef<bool(const Sequencer::TViewModelPtr<Sequencer::IOutlinerExtension>&)> InCallback );` (scope `UE::ControlRig`) — Enumerates IOutlinerExtension that represent a channel of controls selected in the viewport & rig hierarchy. The bridge from channel back to control name uses UMovieSceneControlRigParameterSection::GetChannelMetaData, which is the channel<->control mapping produced by UMovieSceneControlRigParameterSection>>CacheChannelProxy. @param InSequencer The Sequencer to search for selected view models on @param InCallback The callback to invoke. Return true to continue iteration, false to stop.

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/Sequencer/ControlRigSequencerFilter.h` (Private)


#### class `UControlRigTrackFilter`  
`class UControlRigTrackFilter : public USequencerTrackFilterExtension`  
_L9-19_
- reflection: `UCLASS()`
- inherits: `USequencerTrackFilterExtension`
- L15 _public prototype_ `virtual void AddTrackFilterExtensions(ISequencerTrackFilters& InOutFilterInterface , const TSharedRef<FFilterCategory>& InPreferredCategory , TArray<TSharedRef<FSequencerTrackFilter>>& InOutFilterList) const override;`

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/Sequencer/Extensions/ControlRigSelectionFilterExtension.h` (Private)


#### class `UControlRigSelectionFilterExtension`  
`class UControlRigSelectionFilterExtension : public USequencerTrackFilterSelectedExtension`  
_L12-21_
- reflection: `UCLASS()`
- inherits: `USequencerTrackFilterSelectedExtension`
- desc: Extends FSequencerTrackFilter_Selected such that selecting e.g. Dragon.ChestCtrl.Location.X shows Location.Y, Rotation, Scale, etc., as well.
- L17 _public prototype_ `virtual void EnumerateViewModelsConsideredAsSelected( const ISequencer& InSequencer, TFunctionRef<EBreakBehavior(const UE::Sequencer::FViewModelPtr&)> InCallback ) override;`

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/Sequencer/Extensions/ControlRigStickySelectionFilterExtension.h` (Private)


#### class `UControlRigStickySelectionFilterExtension`  
`class UControlRigStickySelectionFilterExtension : public USequencerTrackFilterStickySelectionExtension`  
_L10-16_
- reflection: `UCLASS()`
- inherits: `USequencerTrackFilterStickySelectionExtension`
- desc: Extends FSequencerTrackFilter_StickySelection such that clicking control rig controls in the viewport clears sticky selection.
- L15 _public prototype_ `virtual bool IsPerformingSelectionThatShouldClearStickySelection(const ISequencer& InSequencer) override;`

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/Sequencer/LoadAnimToControlRigSettings.h` (Private)


#### class `ULoadAnimToControlRigSettings`  
`class ULoadAnimToControlRigSettings : public UObject`  
_L12-44_
- reflection: `UCLASS(BlueprintType, config = EditorSettings)`
- inherits: `UObject`
- desc: settings used when loading animation sequences into a control rig section
- L15 _public prototype_ `ULoadAnimToControlRigSettings(const FObjectInitializer& Initializer);`
- L20 _public member_ `bool bOntoSelectedControls = false;` — `UPROPERTY(EditAnywhere, Category = "Controls")` — Load animation onto only selected controls
- L24 _public member_ `bool bReduceKeys = false;` — `UPROPERTY(EditAnywhere, Category = "Reduce Keys")` — Reduce Keys
- L27 _public member_ `FSmartReduceParams SmartReduce;` — `UPROPERTY(EditAnywhere, Category = "Reduce Keys", meta = (EditCondition = "bReduceKeys"))`
- L30 _public member_ `bool bUseCustomTimeRange = false;` — `UPROPERTY(EditAnywhere, Category = "Animation Time Range")`
- L33 _public member_ `FFrameNumber StartFrame;` — `UPROPERTY(EditAnywhere, Category = "Animation Time Range", meta = (EditCondition = "bUseCustomTimeRange"))`
- L36 _public member_ `FFrameNumber EndFrame;` — `UPROPERTY(EditAnywhere, Category = "Animation Time Range", meta = (EditCondition = "bUseCustomTimeRange"))`
- L40 _public member_ `bool bResetControls = false;` — `UPROPERTY(EditAnywhere, Category = "Reset Controls")` — Reset controls to initial value on every frame
- L43 _public prototype_ `void Reset();` — Resets the default properties.

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/Sequencer/MovieSceneControlRigSectionDetailsCustomization.h` (Private)


#### class `FMovieSceneControlRigSectionDetailsCustomization`  
`class FMovieSceneControlRigSectionDetailsCustomization : public IDetailCustomization`  
_L11-19_
- inherits: `IDetailCustomization`
- L15 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L18 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailLayout) override;` — IDetailCustomization interface

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/Sequencer/SLoadAnimToControlRig.h` (Private)


#### struct `FLoadAnimToControlRigDialog`  
`struct FLoadAnimToControlRigDialog`  
_L13-16_
- desc: dialog to show ULoadAnimToControlRigSettings properties for loading animation into a control rig section
- L15 _public prototype_ `static void GetLoadAnimParams(FLoadAnimToControlRigDelegate& Delegate, const FOnWindowClosed& OnClosedDelegate);`

#### Free symbols / members of external scopes

- L10 _delegate_ `DECLARE_DELEGATE_OneParam(FLoadAnimToControlRigDelegate, ULoadAnimToControlRigSettings*);`
- L10 _prototype_ `DECLARE_DELEGATE_OneParam(FLoadAnimToControlRigDelegate, ULoadAnimToControlRigSettings*);`

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/Sequencer/SaveScopedControlRigSelection.h` (Private)


#### struct `UE::ControlRig::FSaveScopedControlRigSelection`  
`struct FSaveScopedControlRigSelection : FNoncopyable`  
_L23-34_
- inherits: `FNoncopyable`
- desc: RAII helper that saves the current editor object selection and Control Rig control selection, then restores both when it goes out of scope. This is used around Sequencer operations such as anim layer add/merge that may rebuild sections or tracks and temporarily clear selection.
- L25 _public prototype_ `explicit FSaveScopedControlRigSelection(const TWeakPtr<ISequencer>& InWeakSequencer);`
- L26 _public prototype_ `~FSaveScopedControlRigSelection();`
- L29 _private member_ `TWeakPtr<ISequencer> WeakSequencer;`
- L31 _private member_ `TArray<TWeakObjectPtr<AActor>> SavedActorSelections;`
- L32 _private member_ `TArray<TWeakObjectPtr<USceneComponent>> SavedComponentSelections;`
- L33 _private member_ `TArray<TPair<TWeakObjectPtr<UControlRig>, TArray<FName>>> SavedControlSelections;`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace ControlRig` (scope `UE`)

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/Sequencer/Scripting/MovieSceneScriptingConstraint.h` (Private)


#### class `UMovieSceneScriptingConstraintChannelKey`  
`class UMovieSceneScriptingConstraintChannelKey : public UMovieSceneScriptingKey, public TMovieSceneScriptingKey<FMovieSceneConstraintChannel, bool>`  
_L22-63_
- reflection: `UCLASS(BlueprintType)`
- inherits: `UMovieSceneScriptingKey,TMovieSceneScriptingKey<FMovieSceneConstraintChannel,bool>`
- desc: Exposes a Constraint Channel key to Python/Blueprints. Stores a reference to the data so changes to this class are forwarded onto the underlying data structures.
- L32 _public function_ `virtual FFrameTime GetTime(EMovieSceneTimeUnit TimeUnit = EMovieSceneTimeUnit::DisplayRate) const override` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Get Time (Constraint Key)"))` — Gets the time for this key from the owning channel. @param TimeUnit	Should the time be returned in Display Rate frames (possibly with a sub-frame value) or in Tick Resolution with no sub-frame values? @return			The time of this key which combines both the frame number and the sub-frame it is on. Sub-frame will be zero if you request Tick Resolution.
- L41 _public function_ `void SetTime(const FFrameNumber& NewFrameNumber, float SubFrame = 0.f, EMovieSceneTimeUnit TimeUnit = EMovieSceneTimeUnit::DisplayRate)` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Set Time (Constraint Key)"))` — Sets the time for this key in the owning channel. Will replace any key that already exists at that frame number in this channel. @param NewFrameNumber	What frame should this key be moved to? This should be in the time unit specified by TimeUnit. @param SubFrame		If using Display Rate time, what is the sub-frame this should go to? Clamped [0-1), and ignored with when TimeUnit is set to Tick Resolution. @param TimeUnit		Should the NewFrameNumber be interpreted as Display Rate frames or in Tick Resolution?
- L48 _public function_ `bool GetValue() const` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Get Value (Constraint Key)"))` — Gets the value for this key from the owning channel. @return	The  constraint key.
- L59 _public function_ `void SetValue(const bool& InNewValue)` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Set Value (Constraint Key)"))` — Sets the value for this key, reflecting it in the owning channel. @param InNewValue	The constraint key

#### class `UMovieSceneScriptingConstraintChannel`  
`class UMovieSceneScriptingConstraintChannel : public UMovieSceneScriptingChannel`  
_L66-226_
- reflection: `UCLASS(BlueprintType)`
- inherits: `UMovieSceneScriptingChannel`
- L70 _private typedef_ `using Impl = TMovieSceneScriptingChannel<FMovieSceneConstraintChannel, UMovieSceneScriptingConstraintChannelKey, bool>;`
- L82 _public function_ `UMovieSceneScriptingConstraintChannelKey* AddKey(const FFrameNumber InTime, bool NewValue, float SubFrame = 0.f, EMovieSceneTimeUnit TimeUnit = EMovieSceneTimeUnit::DisplayRate)` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Add Key (Constraint Key)"))` — Add a key to this channel. This initializes a new key and returns a reference to it. @param	InTime			The frame this key should go on. Respects TimeUnit to determine if it is a display rate frame or a tick resolution frame. @param	NewValue		The value that this key should be created with. @param	SubFrame		Optional [0-1) clamped sub-frame to put this key on. Ignored if TimeUnit is set to Tick Resolution. @param	TimeUnit 		Is the specified InTime in Display Rate frames or Tick Resolution. @return	The key that was created with the specified values at the specified time.
- L91 _public function_ `virtual void RemoveKey(UMovieSceneScriptingKey* Key)` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Remove Key (Constraint Key)"))` — Removes the specified key. Does nothing if the key is not specified or the key belongs to another channel.
- L102 _public function_ `virtual TArray<UMovieSceneScriptingKey*> GetKeys() const override` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Get Keys (Constraint Key)"))` — Gets all of the keys in this channel. @return	An array of UMovieSceneScriptingConstraintChannelKeys contained by this channel. Returns all keys even if clipped by the owning section's boundaries or outside of the current sequence play range.
- L114 _public function_ `virtual TArray<UMovieSceneScriptingKey*> GetKeysByIndex(const TArray<int32>& Indices) const override` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Get Keys By Index (Constraint Key)"))` — Gets the keys in this channel specified by the specific index @Indices  The indices from which to get the keys from @return	An array of UMovieSceneScriptingKey's contained by this channel. Returns all keys specified by the indices, even if out of range.
- L125 _public function_ `TArray<bool> EvaluateKeys(FSequencerScriptingRange Range, FFrameRate FrameRate) const` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Evaluate Keys (Constraint Key)"))` — Gets baked keys in this channel. @return	An array of values contained by this channel. Returns baked keys in the specified range.
- L134 _public function_ `void SetDefault(bool InDefaultValue)` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Set Default (Constraint Key)"))` — Set this channel's default value that should be used when no keys are present. Sets bHasDefaultValue to true automatically.
- L146 _public function_ `bool GetDefault() const` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Get Default (Constraint Key)"))` — Get this channel's default value that will be used when no keys are present. Only a valid value when HasDefault() returns true.
- L156 _public function_ `void RemoveDefault()` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Remove Default (Constraint Key)"))` — Remove this channel's default value causing the channel to have no effect where no keys are present
- L185 _public function_ `bool HasDefault() const` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Has Default (Constraint Key)"))` — @return Does this channel have a default value set?
- L201 _public function_ `void Transform(FFrameNumber OffsetFrame, double Scale, FFrameNumber PivotFrame, FSequencerScriptingRange ScriptingRange, EMovieSceneTimeUnit TimeUnit = EMovieSceneTimeUnit::DisplayRate)` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Transform (Constraint Key)"))` — Transform the keys in time in the channel by an offset, scale and pivot @param	OffsetFrame	    The amount to offset the keys by @param	Scale	        The amount to scale the keys by @param	PivotFrame	    The frame to pivot around when scaling the keys @param   ScriptingRange  The time range of the keys to transform @param	TimeUnit 		Is the specified OffsetFrame, PivotFrame, and ScriptingRange in Display Rate frames or Tick Resolution.
- L210 _public function_ `UTickableConstraint* GetConstraint()` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Get Constraint (Constraint Channel)"))` — @return Get the tickable constraint associated with this channel
- L223 _public member_ `TWeakObjectPtr<UMovieSceneSequence> OwningSequence;`
- L224 _public member_ `TWeakObjectPtr<UMovieSceneSection> OwningSection;`
- L225 _public member_ `TMovieSceneChannelHandle<FMovieSceneConstraintChannel> ChannelHandle;`

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/Sequencer/Scripting/MovieSceneScriptingSpace.h` (Private)


#### class `UMovieSceneScriptingSpaceChannelKey`  
`class UMovieSceneScriptingSpaceChannelKey : public UMovieSceneScriptingKey, public TMovieSceneScriptingKey<FMovieSceneControlRigSpaceChannel, FMovieSceneControlRigSpaceBaseKey>`  
_L21-63_
- reflection: `UCLASS(BlueprintType)`
- inherits: `UMovieSceneScriptingKey,TMovieSceneScriptingKey<FMovieSceneControlRigSpaceChannel,FMovieSceneControlRigSpaceBaseKey>`
- desc: Exposes a Space Channel key to Python/Blueprints. Stores a reference to the data so changes to this class are forwarded onto the underlying data structures.
- L31 _public function_ `virtual FFrameTime GetTime(EMovieSceneTimeUnit TimeUnit = EMovieSceneTimeUnit::DisplayRate) const override` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Get Time (Space Keye)"))` — Gets the time for this key from the owning channel. @param TimeUnit	Should the time be returned in Display Rate frames (possibly with a sub-frame value) or in Tick Resolution with no sub-frame values? @return			The time of this key which combines both the frame number and the sub-frame it is on. Sub-frame will be zero if you request Tick Resolution.
- L40 _public function_ `void SetTime(const FFrameNumber& NewFrameNumber, float SubFrame = 0.f, EMovieSceneTimeUnit TimeUnit = EMovieSceneTimeUnit::DisplayRate)` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Set Time (Space Keye)"))` — Sets the time for this key in the owning channel. Will replace any key that already exists at that frame number in this channel. @param NewFrameNumber	What frame should this key be moved to? This should be in the time unit specified by TimeUnit. @param SubFrame		If using Display Rate time, what is the sub-frame this should go to? Clamped [0-1), and ignored with when TimeUnit is set to Tick Resolution. @param TimeUnit		Should the NewFrameNumber be interpreted as Display Rate frames or in Tick Resolution?
- L47 _public function_ `FMovieSceneControlRigSpaceBaseKey GetValue() const` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Get Value (Space Key)"))` — Gets the value for this key from the owning channel. @return The space key
- L58 _public function_ `void SetValue(const FMovieSceneControlRigSpaceBaseKey& InNewValue)` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Set Value (Space Key)"))` — Sets the value for this key, reflecting it in the owning channel. @param InNewValue	The new space key

#### class `UMovieSceneScriptingSpaceChannel`  
`class UMovieSceneScriptingSpaceChannel: public UMovieSceneScriptingChannel`  
_L66-211_
- reflection: `UCLASS(BlueprintType)`
- inherits: `UMovieSceneScriptingChannel`
- L70 _private typedef_ `using Impl = TMovieSceneScriptingChannel<FMovieSceneControlRigSpaceChannel, UMovieSceneScriptingSpaceChannelKey, FMovieSceneControlRigSpaceBaseKey>;`
- L82 _public function_ `UMovieSceneScriptingSpaceChannelKey* AddKey(const FFrameNumber InTime, FMovieSceneControlRigSpaceBaseKey NewValue, float SubFrame = 0.f, EMovieSceneTimeUnit TimeUnit = EMovieSceneTimeUnit::DisplayRate)` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Add Key (Space Key)"))` — Add a key to this channel. This initializes a new key and returns a reference to it. @param	InTime			The frame this key should go on. Respects TimeUnit to determine if it is a display rate frame or a tick resolution frame. @param	NewValue		The value that this key should be created with. @param	SubFrame		Optional [0-1) clamped sub-frame to put this key on. Ignored if TimeUnit is set to Tick Resolution. @param	TimeUnit 		Is the specified InTime in Display Rate frames or Tick Resolution. @return	The key that was created with the specified values at the specified time.
- L91 _public function_ `virtual void RemoveKey(UMovieSceneScriptingKey* Key)` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Remove Key (Space Key)"))` — Removes the specified key. Does nothing if the key is not specified or the key belongs to another channel.
- L102 _public function_ `virtual TArray<UMovieSceneScriptingKey*> GetKeys() const override` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Get Keys (Space Key)"))` — Gets all of the keys in this channel. @return	An array of UMovieSceneScriptingSpaceChannelKeys contained by this channel. Returns all keys even if clipped by the owning section's boundaries or outside of the current sequence play range.
- L114 _public function_ `virtual TArray<UMovieSceneScriptingKey*> GetKeysByIndex(const TArray<int32>& Indices) const override` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Get Keys By Index (Space Key)"))` — Gets the keys in this channel specified by the specific index @Indices  The indices from which to get the keys from @return	An array of UMovieSceneScriptingKey's contained by this channel. Returns all keys specified by the indices, even if out of range.
- L125 _public function_ `TArray<FMovieSceneControlRigSpaceBaseKey> EvaluateKeys(FSequencerScriptingRange ScriptingRange, FFrameRate FrameRate) const` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Evaluate Keys (Space Key)"))` — Gets baked keys in this channel. @return	An array of values contained by this channel. Returns baked keys in the specified range.
- L135 _public function_ `void SetDefault(FMovieSceneControlRigSpaceBaseKey InDefaultValue)` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Set Default (Space Key)"))` — Set this channel's default value that should be used when no keys are present. Sets bHasDefaultValue to true automatically.
- L147 _public function_ `FMovieSceneControlRigSpaceBaseKey GetDefault() const` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Get Default (Space Key)"))` — Get this channel's default value that will be used when no keys are present. Only a valid value when HasDefault() returns true.
- L157 _public function_ `void RemoveDefault()` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Remove Default (Space Key)"))` — Remove this channel's default value causing the channel to have no effect where no keys are present
- L186 _public function_ `bool HasDefault() const` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Has Default (Space Key)"))` — @return Does this channel have a default value set?
- L202 _public function_ `void Transform(FFrameNumber OffsetFrame, double Scale, FFrameNumber PivotFrame, FSequencerScriptingRange ScriptingRange, EMovieSceneTimeUnit TimeUnit = EMovieSceneTimeUnit::DisplayRate)` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Keys", meta = (DisplayName = "Transform (Space Key)"))` — Transform the keys in time in the channel by an offset, scale and pivot @param	OffsetFrame	    The amount to offset the keys by @param	Scale	        The amount to scale the keys by @param	PivotFrame	    The frame to pivot around when scaling the keys @param   ScriptingRange  The time range of the keys to transform @param	TimeUnit 		Is the specified OffsetFrame, PivotFrame, and ScriptingRange in Display Rate frames or Tick Resolution.
- L208 _public member_ `TWeakObjectPtr<UMovieSceneSequence> OwningSequence;`
- L209 _public member_ `TWeakObjectPtr<UMovieSceneSection> OwningSection;`
- L210 _public member_ `TMovieSceneChannelHandle<FMovieSceneControlRigSpaceChannel> ChannelHandle;`

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/Sequencer/SelectionSets/SSelectionSets.h` (Private)


#### class `SSelectionSetButton`  
`class SSelectionSetButton: public SButton`  
_L23-62_
- inherits: `SButton`
- L26 _public function_ `SLATE_BEGIN_ARGS(SSelectionSetButton)`
- L28 _public prototype_ `SLATE_DEFAULT_SLOT(FArguments, Content) SLATE_EVENT(FOnClicked, OnClicked) SLATE_ARGUMENT(FGuid, Guid) SLATE_ARGUMENT(SSelectionSets*, SetsWidget ) SLATE_END_ARGS() void Construct(const FArguments& Args);`
- L36 _public function_ `bool IsDragHovered() const`
- L39 _protected prototype_ `virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L40 _protected prototype_ `virtual FReply OnMouseButtonDoubleClick(const FGeometry& InMyGeometry, const FPointerEvent& InMouseEvent) override;`
- L41 _protected prototype_ `virtual FReply OnDragDetected(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L42 _protected prototype_ `virtual void OnDragEnter(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;`
- L43 _protected prototype_ `virtual void OnDragLeave(const FDragDropEvent& DragDropEvent) override;`
- L44 _protected prototype_ `virtual FReply OnDrop(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;`
- L47 _private member_ `bool bIsDragHovered = false;`
- L48 _private member_ `FGuid SelectionSetGuid;`
- L49 _private member_ `SSelectionSets* SelectionSetsWidget = nullptr;`
- L50 _private prototype_ `void AddSelectionToSet() const;`
- L51 _private prototype_ `void RemoveSelectionFromSet() const;`
- L52 _private prototype_ `void DeleteSet() const;`
- L53 _private prototype_ `void RenameSet() const;`
- L54 _private prototype_ `TSharedRef<SWidget> CreateSelectionSetColorWidget(const FGuid& InGuid, TSharedPtr<ISequencer>& SequencerPtr) const;`
- L55 _private prototype_ `void CreateMirror() const;`
- L56 _private prototype_ `void SelectMirror() const;`
- L57 _private prototype_ `void HideSelectionSet() const;`
- L58 _private prototype_ `void ShowSelectionSet() const;`
- L59 _private prototype_ `void IsolateSelectionSet() const;`
- L60 _private prototype_ `void ShowAllSelectionSet() const;`
- L61 _private prototype_ `void KeyAll() const;`

#### class `SSelectionSets`  
`class SSelectionSets : public FControlRigBaseDockableView, public SCompoundWidget, FSelfRegisteringEditorUndoClient`  
_L64-157_
- inherits: `FControlRigBaseDockableView,SCompoundWidget,FSelfRegisteringEditorUndoClient`
- L66 _private function_ `SLATE_BEGIN_ARGS(SSelectionSets)`
- L68 _private prototype_ `SSelectionSets();`
- L69 _private prototype_ `~SSelectionSets();`
- L72 _private prototype_ `virtual void PostUndo( bool bSuccess );` — FSelfRegisteringEditorUndoClient interface
- L73 _private prototype_ `virtual void PostRedo( bool bSuccess );`
- L74 _private prototype_ `virtual bool MatchesContext( const FTransactionContext& InContext, const TArray<TPair<UObject*, FTransactionObjectEvent>>& TransactionObjectContexts ) const;`
- L77 _private prototype_ `void Construct(const FArguments& InArgs, FControlRigEditMode& InEditMode);`
- L79 _private prototype_ `void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;` — SCompuntWidget
- L82 _private function_ `virtual TSharedRef<FControlRigBaseDockableView> AsSharedWidget() override` — FControlRigBaseDockableView overrides
- L83 _private prototype_ `virtual void SetEditMode(FControlRigEditMode& InEditMode) override;`
- L84 _private prototype_ `virtual void HandleControlAdded(UControlRig* ControlRig, bool bIsAdded) override;`
- L86 _private function_ `void SetFocusOnTextBlock(const FGuid& InGuid)`
- L88 _private prototype_ `void HandleOnControlRigBound(UControlRig* InControlRig);`
- L89 _private prototype_ `void HandleOnObjectBoundToControlRig(UObject* InObject);`
- L90 _private prototype_ `virtual void HandleControlSelected(UControlRig* Subject, FRigControlElement* InControl, bool bSelected) override;`
- L93 _private member_ `TArray<TWeakObjectPtr<UControlRig>> BoundControlRigs;` — set of control rigs we are bound too and need to clear delegates from
- L96 _private prototype_ `void RegisterSelectionChanged();` — actor selection changing
- L97 _private prototype_ `void OnActorSelectionChanged(const TArray<UObject*>& NewSelection, bool bForceRefresh);`
- L98 _private member_ `FDelegateHandle OnSelectionChangedHandle;`
- L101 _private prototype_ `void OnActivateSequence(FMovieSceneSequenceIDRef ID);` — sequencer changing so need to refresh list
- L102 _private prototype_ `void OnMovieSceneDataChanged(EMovieSceneDataChangeType);`
- L103 _private prototype_ `void OnCloseEvent(TSharedRef<ISequencer> InSequencer);`
- L104 _private prototype_ `void OnMovieSceneBindingsChanged();`
- L105 _private prototype_ `void UpdateBindings();`
- L107 _private member_ `FGuid LastMovieSceneSig = FGuid();`
- L110 _private function_ `void HandleSelectionListChanged(UAIESelectionSets*)`
- L112 _private prototype_ `FReply OnSelectionFilterClicked();`
- L113 _private prototype_ `bool IsSelectionFilterActive() const;`
- L114 _private prototype_ `FReply OnAddClicked();`
- L115 _private prototype_ `bool ImportOrExportPath(FString& OutPath, bool bImport);`
- L116 _private prototype_ `bool ImportLastSelectionSet();`
- L117 _private prototype_ `bool ImportFromJson();`
- L118 _private prototype_ `bool ExportToJson();`
- L119 _private prototype_ `void SaveLastJson();`
- L120 _private prototype_ `void NewSelectionSet(UAIESelectionSets* NewSelectionSet);`
- L124 _private prototype_ `TSharedRef<SWidget> CreateActorMenu(const FActorWithSelectionSet& ActorWithSelectionSet);`
- L125 _private prototype_ `TSharedRef<SWidget> MakeImportExportMenu();`
- L130 _private member_ `TSharedPtr<SBorder> MainAddFilterSetSlot;` — main UI elements
- L131 _private member_ `TSharedPtr<SBox> ActiveActorsSlot;`
- L132 _private member_ `TSharedPtr<SBorder> SearchSetsSlot;`
- L133 _private member_ `TSharedPtr<SBox> ActiveSetsSlot;`
- L135 _private member_ `TSharedPtr<SWrapBox> ActiveActorsWidget;`
- L136 _private member_ `TSharedPtr<SWrapBox> SelectionSetsWidget;`
- L138 _private member_ `TMap<FGuid, TSharedPtr<SSelectionSetButton>> SelectionSetsButton;`
- L139 _private member_ `TMap<FGuid, TSharedPtr<SInlineEditableTextBlock>> SelectionSetsTextBlock;`
- L140 _private member_ `TSharedPtr<SSearchBox> SetSearchBox;`
- L141 _private member_ `TSharedPtr<FTextFilterExpressionEvaluator> SetTextFilter;`
- L143 _private member_ `FGuid FocusOnTextBlock;`
- L146 _private prototype_ `void PopulateUI();`
- L147 _private prototype_ `void PopulateActiveActors();`
- L148 _private prototype_ `void PopulateSelectionSets();`
- L151 _private member_ `bool bSetUpTimerIsSet = false;` — things we handle on next tick
- L152 _private member_ `bool bUpdateBindings = false;`
- L153 _private member_ `bool bPopulateUI = false;`
- L156 _private member_ `static FString LastSelectionSetJSON;` — cache of last select set closed, for quick loading of sets onto new level sequences

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/Sequencer/SelectionSets/SelectionSetDragDropOp.h` (Private)


#### class `FAIESelectionSetDragDropOp`  
`class FAIESelectionSetDragDropOp : public FDecoratedDragDropOp`  
_L6-22_
- inherits: `FDecoratedDragDropOp`
- L9 _public prototype_ `DRAG_DROP_OPERATOR_TYPE(FAIESelectionSetDragDropOp, FDecoratedDragDropOp) FGuid DraggedGuid;`
- L13 _public function_ `static TSharedRef<FAIESelectionSetDragDropOp> New(const FGuid& InGuid)`

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/Sequencer/SelectionSets/SelectionSets.h` (Private)


#### enum `EAIESelectionSetItemType`  
`enum EAIESelectionSetItemType : int32`  
_L19-26_
- reflection: `UENUM()`
- desc: Type  of the selection set item
- L22 _public enumerator_ `ControlRig = 0x0` — Control Rig Type
- L24 _public enumerator_ `Actor = 0x1` — Actor Type

#### struct `FAIESelectionSetItemName`  
`struct FAIESelectionSetItemName`  
_L31-54_
- reflection: `USTRUCT(BlueprintType)`
- desc: Individual 'Name" within a Seletion Set, maybe Actor Labe or Control Rig Control Name
- L37 _public member_ `FString Name;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Data")` — The Name of the selection set item*, maybe an Actor Label or a ControlRig Control Name
- L41 _public member_ `FString MirrorName;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Data")` — The Name of the selection set mirrored item for Control Rig Controls that have them
- L45 _public member_ `int32 Type = 1;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Data")` — The EAIESelectionSetItemType, 0 is a Control Rig Control, 1 is an Actor
- L49 _public member_ `int32 Duplicates = 0;` — `UPROPERTY()` — currently not used but maybe in future
- L53 _public member_ `FString OwnerActorName;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Data")` — The Name of the Owner Actor for Multi-Sets containing multiple rigs, may not be set

#### struct `FAIESelectionSetItemViewData`  
`struct FAIESelectionSetItemViewData`  
_L58-73_
- reflection: `USTRUCT(BlueprintType)`
- desc: View Data for the set, contains location and color in the UI
- L64 _public member_ `FLinearColor Color = FLinearColor::White;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Data")` — The Color of the Set
- L68 _public member_ `int32 Row = 0;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Data")` — The logical row the set should be in, basically it's order. This is an internal order for just one set
- L72 _public member_ `int32 Column = 0;` — `UPROPERTY()` — currently not used but maybe in future

#### struct `FAIESelectionSetItem`  
`struct FAIESelectionSetItem`  
_L77-111_
- reflection: `USTRUCT(BlueprintType)`
- desc: Main selection set item, has it's name, it's view data, and array of names making up the set
- L83 _public member_ `FGuid Guid;` — `UPROPERTY()` — Unique ID
- L87 _public member_ `FText ItemName;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Data")` — The Name of the Set
- L91 _public member_ `TArray<FAIESelectionSetItemName> Names;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Data")` — The collection of set items that make up the set, basically an array of names with some metadata
- L95 _public member_ `FAIESelectionSetItemViewData ViewData;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Data")` — Viewing Data for the set, like location and color
- L99 _public member_ `FGuid Parent;` — `UPROPERTY()` — currently not used but maybe in future
- L101 _public member_ `TArray<FGuid> Children;` — currently not used but maybe in future
- L103 _public prototype_ `bool ContainsItem(const FString& Name) const;`
- L104 _public prototype_ `FAIESelectionSetItemName* GetItem(const FString& Name);`
- L105 _public prototype_ `bool RemoveItem(const FString& Name, const FString& ActorLabel);`
- L107 _public prototype_ `bool IsMultiAsset() const;`
- L108 _public prototype_ `bool ContainsOwnerActor(const FString& ActorLabel) const;`
- L109 _public prototype_ `void GetAllChildren(const UAIESelectionSets* SelectionSets, TArray<FGuid>& AllChildren) const;`
- L110 _public prototype_ `static FString GetMirror(const FString& InString);`

#### struct `FActorWithSelectionSet`  
`struct FActorWithSelectionSet`  
_L114-158_
- desc: Internal Struct to specify a set of actors/control rigs and the sets they operate upon
- L117 _public member_ `FText Name;` — Name, usually the Actor Label
- L120 _public member_ `FLinearColor Color;` — The Color in the UI
- L123 _public member_ `TSet<TWeakObjectPtr<UObject>> Actors;` — Actors in the level sequence that may be operated on by a Set
- L126 _public member_ `TSet<FGuid> SetsThatMatch;` — Set of selection sets that match up with these Actors
- L129 _public prototype_ `bool IsSelectedInViewport(bool bOnlyInViewport = false) const;` — If this Actor group is selected in the viewport
- L132 _public prototype_ `bool IsControlRig() const;` — If this Actor group is a Control Rig Actor
- L135 _public prototype_ `void ShowAllControlsOnThisActor() const;` — Make all Controls visisable on this Control Rig Actor
- L138 _public function_ `void SetSelected(bool bInSelected)` — Make this Set Actor Selected, may not be Active though based upon UAIESelectionSets::bShowSelectedOnly filter etc..
- L141 _public function_ `bool GetSelected() const` — Get if this Set Actor is Selected. Note may be Selected by not Active for a set based upon UAIESelectionSets::bShowSelectedOnly filter
- L144 _public prototype_ `bool IsActive(bool bShowSelectedOnly) const;` — Get if this Set Actor is Active and may be operated upon by a Set Selection, takes into account filters/settings etc
- L147 _public prototype_ `void SetUpOwnedActors(const TWeakObjectPtr<AActor>& ActorOwner, TSharedPtr<ISequencer>& InSequencer, UAIESelectionSets* SelectionSets);` — if the set contains owned actors but they came from a different control rig we mark that. This is done in SetUpFromSequencer
- L148 _public member_ `TMap <FGuid,FString> OwnedActors;`
- L151 _public member_ `mutable bool bWasSelectedInViewport = false;` — it was previously selected but no more
- L154 _private member_ `bool bIsSelected = false;`
- L156 _public prototype_ `static AActor* GetControlRigActor(const UControlRig* InControlRig);`

#### struct `FActorsWithSelectionSets`  
`struct FActorsWithSelectionSets`  
_L161-166_
- desc: Internal struct containing all ofthe actor sets
- L163 _public member_ `TMap<TWeakObjectPtr<AActor>, FActorWithSelectionSet> ActorsWithSet;`
- L164 _public prototype_ `bool ContainsActor(const FString& ActorLabel, bool bShowSelectedOnly) const;`
- L165 _public prototype_ `void SetUpFromSequencer(TSharedPtr<ISequencer>& InSequencer, UAIESelectionSets* SelectionSets, const TSet<TWeakObjectPtr<UObject>>& MakeSelectedIfPresent);`

#### class `UAIESelectionSets`  
`class UAIESelectionSets : public UAssetUserData`  
_L171-357_
- reflection: `UCLASS(BlueprintType, MinimalAPI)`
- inherits: `UAssetUserData`
- desc: Link To Set of Anim Sequences that we may be linked to.
- L177 _public function_ `virtual bool IsEditorOnly() const override`
- L180 _public member_ `TMap<FGuid, FAIESelectionSetItem> SelectionSets;` — `UPROPERTY(BlueprintReadOnly, Category = SelectionSet)`
- L184 _public function_ `bool GetShowAndSetSelectedOnly() const` — `UFUNCTION(BlueprintPure, Category = "State")` — Whether we are only showing and setting selections on current selections
- L191 _public prototype_ `void SetShowAndSetSelectedOnly(bool bInShowSelectedOnly);` — `UFUNCTION(BlueprintCallable, Category = "State")` — Set whether we are only showing and setting selections on current selections
- L195 _public prototype_ `TArray<FGuid> GetActiveSelectionSets();` — `UFUNCTION(BlueprintCallable, Category = "State")` — Get the current set of active selection sets based upon active actors. This function will set it up also if needed
- L200 _public prototype_ `bool SetActorAsActive(AActor* InActor, bool bSetActive);` — `UFUNCTION(BlueprintCallable, Category = "Actor")` — Set the AActor as Active or not, so it will or won't be selected from a selection set. Will return false if it doesn't match any sets*. Note if GetShowAndSetSelectedOnly() is true the selected state of the Actor will take precedence over this
- L204 _public prototype_ `TArray<AActor*> GetAllActors() const;` — `UFUNCTION(BlueprintPure, Category = "Actor")` — Get all the actors which are present to be selected by a selection set
- L208 _public prototype_ `TArray<AActor*> GetActiveActors() const;` — `UFUNCTION(BlueprintPure, Category = "Actor")` — Get the actors which are selectable
- L212 _public prototype_ `FGuid CreateSetItemFromSelection();` — `UFUNCTION(BlueprintCallable, Category = "Sets")` — Create a selection set from current selection. Will return empty FGuid if no set created
- L213 _public prototype_ `FGuid CreateSetItemFromSelection(TSharedPtr<ISequencer>& InSequencer);`
- L217 _public prototype_ `FGuid CreateMirror(const FGuid& InGuid);` — `UFUNCTION(BlueprintCallable, Category = "Sets")` — Create a mirrored selection set from an existing set. Will return empty FGuid if no set created
- L218 _public prototype_ `FGuid CreateMirror(TSharedPtr<ISequencer>& InSequencer, const FGuid& InGuid);`
- L222 _public prototype_ `bool AddSelectionToSetItem(const FGuid& InGuid);` — `UFUNCTION(BlueprintCallable, Category = "Set")` — Add selection to specified selection set
- L223 _public prototype_ `bool AddSelectionToSetItem(const FGuid& InGuid, TSharedPtr<ISequencer>& InSequencer);`
- L227 _public prototype_ `bool RemoveSelectionFromSetItem(const FGuid& InGuid);` — `UFUNCTION(BlueprintCallable, Category = "Set")` — Remove selection from specified selection set
- L228 _public prototype_ `bool RemoveSelectionFromSetItem(const FGuid& InGuid, TSharedPtr<ISequencer>& InSequencer);`
- L232 _public prototype_ `bool RenameSetItem(const FGuid& InGuid,const FText& NewName);` — `UFUNCTION(BlueprintCallable, Category = "Set")` — Rename selection set
- L236 _public prototype_ `bool GetItemName(const FGuid& InGuid, FText& OutName) const;` — `UFUNCTION(BlueprintPure, Category = "Set")` — Get selection set name
- L240 _public prototype_ `bool IsMultiAsset(const FGuid& InGuid) const;` — `UFUNCTION(BlueprintPure, Category = "Set")` — Rename selection set
- L244 _public prototype_ `void GetItemGuids(const FText& ItemName, TArray<FGuid>& OutGuids) const;` — `UFUNCTION(BlueprintPure, Category = "State")` — Get the guids of set items associated with this name
- L248 _public prototype_ `bool DeleteSetItem(const FGuid& InGuid);` — `UFUNCTION(BlueprintCallable, Category = "Set")` — Delete selection set
- L249 _public prototype_ `bool DeleteSetItem(const FGuid& InGuid, TSharedPtr<ISequencer>& InSequencer);`
- L253 _public prototype_ `bool DeleteAllSetItems();` — `UFUNCTION(BlueprintCallable, Category = "Set")` — Delete all selection sets
- L254 _public prototype_ `bool DeleteAllSetItems(TSharedPtr<ISequencer>& InSequencer);`
- L258 _public prototype_ `bool GetItemColor(const FGuid& InGuid, FLinearColor& OutColor) const;` — `UFUNCTION(BlueprintPure, Category = "Set")` — Get selection set color
- L262 _public prototype_ `bool SetItemColor(const FGuid& InGuid, const FLinearColor& InColor);` — `UFUNCTION(BlueprintCallable, Category = "Set")` — Set selection set color
- L266 _public prototype_ `bool GetItemRow(const FGuid& InGuid, int32& OutRow) const;` — `UFUNCTION(BlueprintPure, Category = "Set")` — Get selection set row
- L270 _public prototype_ `bool SetItemRow(const FGuid& InGuid, int32 InRow);` — `UFUNCTION(BlueprintCallable, Category = "Set")` — Set selection set row
- L274 _public prototype_ `bool SelectItem(const FGuid& InGuid, bool bDoMirror, bool bAdd, bool bToggle,bool bSelect = true) const;` — `UFUNCTION(BlueprintCallable, Category = "Set")` — Select from selection set, will select on the active actors
- L278 _public prototype_ `bool ShowOrHideControls(const FGuid& InGuid, bool bShow, bool bDoMirror) const;` — `UFUNCTION(BlueprintCallable, Category = "Visibility")` — Show or hide controls on the active actors from the specified set
- L282 _public prototype_ `bool IsolateControls(const FGuid& InGuid) const;` — `UFUNCTION(BlueprintCallable, Category = "Visibility")` — Isolate controls from just this selection set on active actors
- L286 _public prototype_ `bool ShowAllControls(const FGuid& InGuid) const;` — `UFUNCTION(BlueprintCallable, Category = "Visibility")` — Show all controls from this selection set's active actors
- L290 _public prototype_ `bool KeyAll(const FGuid& InGuid) const;` — `UFUNCTION(BlueprintCallable, Category = "Set")` — Key the selection sets on active actors
- L291 _public prototype_ `bool KeyAll(TSharedPtr<ISequencer>& InSequencer, const FGuid& InGuid) const;`
- L295 _public prototype_ `bool LoadFromJsonFile(const FFilePath& JsonFilePath);` — `UFUNCTION(BlueprintCallable, Category = "ImportExport")` — Load sets from a JSON file
- L296 _public prototype_ `bool LoadFromJsonFile(TSharedPtr<ISequencer>& InSequencer, const FFilePath& JsonFilePath);`
- L300 _public prototype_ `bool ExportAsJsonFile(const FFilePath& JsonFilePath) const;` — `UFUNCTION(BlueprintCallable, Category = "ImportExport")` — Export sets to a JSON file
- L304 _public prototype_ `bool LoadFromJsonString(const FString& JsonString);` — `UFUNCTION(BlueprintCallable, Category = "ImportExport")` — Load sets from a string
- L305 _public prototype_ `bool LoadFromJsonString(TSharedPtr<ISequencer>& InSequencer, const FString& JsonString);`
- L309 _public prototype_ `bool ExportAsJsonString(FString& OutJsonString) const;` — `UFUNCTION(BlueprintCallable, Category = "ImportExport")` — Export sets from a string
- L312 _public prototype_ `bool IsVisible(const FActorWithSelectionSet& ActorWithSelectionSet) const;` — Get updated visibility for the actor selections, using settings and properties
- L315 _public prototype_ `void SequencerBindingsAdded(TSharedPtr<ISequencer>& InSequencer);` — utility functions
- L317 _public prototype_ `bool AddChildToItem(const FGuid& InParentGuid, const FGuid& InChildGuid);` — tbd
- L318 _public prototype_ `bool RemoveChildFromItem(const FGuid& InParentGuid, const FGuid& InChildGuid);`
- L320 _public prototype_ `static UAIESelectionSets* GetSelectionSets(const TSharedPtr<ISequencer>& InSequencer, bool bAddIfDoesNotExist = false);`
- L321 _public prototype_ `static UAIESelectionSets* GetSelectionSets(ULevelSequence* InLevelSequence, bool bAddIfDoesNotExist = false);`
- L322 _public prototype_ `static TSharedPtr<ISequencer> GetSequencerFromAsset();`
- L326 _public member_ `FActorsWithSelectionSets ActorsWithSelectionSets;` — current set of actors we can work on
- L330 _public prototype_ `DECLARE_EVENT_OneParam(UAIESelectionSets, FSelectionSetsChanged, UAIESelectionSets*);`
- L332 _public function_ `FSelectionSetsChanged& SelectionListChanged()`
- L335 _public prototype_ `void SelectionSetsChangedBroadcast();`
- L336 _public member_ `FSelectionSetsChanged OnSelectionSetsChanged;`
- L338 _public prototype_ `FLinearColor GetNextSelectionSetColor();`
- L339 _public prototype_ `FLinearColor GetNextActorColor();`
- L345 _private prototype_ `TArray<FGuid> SortSelectionSetsByRow(TArray<FGuid>& InSelectionSets);`
- L348 _private prototype_ `void UpdateRowValues(int32 StartRow, int32 EndRow, bool bIncrease);` — starting from StartRow going to EndRow(inclusive) increase or decrease row values, used for when changing row value or deleting the item
- L351 _private member_ `mutable TSet<FGuid> LastActiveSelectionSetsSet;` — to handle selecting last selected object when none are selected
- L356 _private member_ `bool bShowSelectedOnly = true;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L330 _delegate_ `DECLARE_EVENT_OneParam(UAIESelectionSets, FSelectionSetsChanged, UAIESelectionSets*);`

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/Sequencer/SelectionSets/SelectionSetsOverlayManager.h` (Private)


#### class `UE::AIE::FSelectionSetsOverlayManager`  
`class FSelectionSetsOverlayManager : public FNoncopyable`  
_L15-41_
- inherits: `FNoncopyable`
- desc: Manages all logic around the selectio set overlay widget.
- L19 _public prototype_ `explicit FSelectionSetsOverlayManager( const TSharedRef<IToolkitHost>& InToolkitHost, const TSharedRef<FUICommandList>& InToolkitCommandList, const TSharedRef<FControlRigEditMode>& InOwningEditMode );`
- L25 _public function_ `void ToggleVisibility()`
- L26 _public function_ `void ShowWidget()`
- L27 _public function_ `void HideWidget()`
- L28 _public function_ `void DestroyWidget()`
- L29 _public function_ `bool IsShowingWidget() const`
- L34 _private member_ `TSharedPtr<SWidget> SelectionSetWidget;`
- L36 _private member_ `ControlRigEditor::FFlyoutOverlayManager FlyoutWidgetManager;`
- L39 _private member_ `ControlRigEditor::FFlyoutCommandBinder CommandBinder;` — Process the command bindings that affect FlyoutWidgetManager.

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace AIE` (scope `UE`)

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/Sequencer/SelectionSets/SelectionSetsSettings.h` (Private)


#### class `USelectionSetsSettings`  
`class USelectionSetsSettings : public UDeveloperSettings`  
_L21-39_
- reflection: `UCLASS(MinimalAPI, config=EditorPerProjectUserSettings)`
- inherits: `UDeveloperSettings`
- desc: Serializable options for animation mode selection sets.
- L26 _public prototype_ `USelectionSetsSettings();`
- L28 _public function_ `const TArray<FLinearColor>& GetCustomColors() const`
- L34 _protected member_ `TArray<FLinearColor> CustomColors;` — `UPROPERTY(config, EditAnywhere, Category="Colors")` — Set of colors to use for selection sets

#### Free symbols / members of external scopes

- L16 _macro_ `#define UE_API CONTROLRIGEDITOR_API`

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/Sequencer/SequencerSimpleViewExtension.h` (Private)


#### class `UE::ControlRig::SimpleView::FSequencerSimpleViewExtension`  
`class FSequencerSimpleViewExtension`  
_L15-35_
- L18 _public prototype_ `static void Register();`
- L19 _public prototype_ `static void Unregister();`
- L22 _private prototype_ `static void AddSequencerToolbarMenuExtension();`
- L23 _private prototype_ `static void RemoveSequencerToolbarMenuExtension();`
- L25 _private prototype_ `static void AddAnimLayersComboBox(FToolMenuSection& InSection);`
- L27 _private prototype_ `static bool SupportsAnimLayerComboBox(const TWeakPtr<ISequencer> InWeakSequencer);`
- L28 _private prototype_ `static EVisibility GetAnimLayerComboBoxVisibility(const TWeakPtr<ISequencer> InWeakSequencer);`
- L30 _private prototype_ `static void AddSequencerSimpleViewChannelFilters();`
- L31 _private prototype_ `static void RemoveSequencerSimpleViewChannelFilters();`
- L33 _private prototype_ `static void AddAdditionalSelectedViewModels();`
- L34 _private prototype_ `static void RemoveAdditionalSelectedViewModels();`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace ControlRig` (scope `UE`)
- L11 _namespace_ `namespace SimpleView` (scope `UE::ControlRig`)

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/SpacePicker/Models/RigAssetEditorFloatingSpacePickerModel.h` (Private)


#### class `UE::ControlRigEditor::FRigAssetEditorFloatingSpacePickerModel`  
`class FRigAssetEditorFloatingSpacePickerModel : public FRigSpacePickerModelBase , public IRigSpacePickerSetActiveSpacesInterface , public IRigSpacePickerAddSpacesInterface , public IRigSpacePickerDeleteSpacesInterface , public IRigSpacePickerMoveSpacesInterface`  
_L10-53_
- inherits: `FRigSpacePickerModelBase,IRigSpacePickerSetActiveSpacesInterface,IRigSpacePickerAddSpacesInterface,IRigSpacePickerDeleteSpacesInterface,IRigSpacePickerMoveSpacesInterface`
- desc: Minimal model for the floating space picker working in the asset editor
- L19 _protected function_ `virtual IRigSpacePickerAddSpacesInterface* GetAddSpacesInterface() override`
- L20 _protected function_ `virtual IRigSpacePickerSetActiveSpacesInterface* GetSetActiveSpacesInterface() override`
- L21 _protected function_ `virtual IRigSpacePickerDeleteSpacesInterface* GetDeleteSpacesInterface() override`
- L22 _protected function_ `virtual IRigSpacePickerMoveSpacesInterface* GetMoveSpacesInterface() override`
- L26 _protected prototype_ `virtual void SetActiveSpaces(const TSharedRef<FRigSpacePickerItem>& Item) override;`
- L30 _protected prototype_ `virtual bool CanAddSpace() const override;`
- L31 _protected prototype_ `virtual void AddSpace(const FRigElementKeyWithLabel& SpaceKeyWithLabel) override;`
- L35 _protected prototype_ `virtual bool CanDeleteSpaces(const TSharedRef<FRigSpacePickerItem>& Item) const override;`
- L36 _protected prototype_ `virtual void DeleteSpaces(const TSharedRef<FRigSpacePickerItem>& Item) override;`
- L40 _protected prototype_ `virtual bool CanMoveSpaces(const TSharedRef<FRigSpacePickerItem>& Item, const ERigSpacePickerMoveSpaceDirection Direction) const override;`
- L41 _protected prototype_ `virtual void MoveSpaces(const TSharedRef<FRigSpacePickerItem>& Item, const ERigSpacePickerMoveSpaceDirection Direction) override;`
- L46 _private prototype_ `void ModifyAsset(URigHierarchy* Hierarchy);` — Modifies the asset
- L49 _private prototype_ `void EditAvailableSpaces(URigHierarchy* Hierarchy, const FRigElementKey& ControlKey, TFunctionRef<void(TArray<FRigElementKeyWithLabel>&)> Function);` — Edits the available spaces of a control by function
- L52 _private prototype_ `UControlRig* GetControlRig() const;` — Returns the control rig

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace ControlRigEditor` (scope `UE`)

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/SpacePicker/Models/RigLevelEditorBakeDialogSpacePickerModel.h` (Private)


#### class `UE::ControlRigEditor::FRigLevelEditorBakeDialogSpacePickerModel`  
`class FRigLevelEditorBakeDialogSpacePickerModel : public FRigLevelEditorSpacePickerModel`  
_L16-51_
- inherits: `FRigLevelEditorSpacePickerModel`
- desc: The bake dialog shows a space picker similar to other level editor focused space pickers. Hence a model for the space picker in the bake spaces dialog.
- L20 _public prototype_ `FRigLevelEditorBakeDialogSpacePickerModel(const FRigSpacePickerBakeSettings& InSettings);`
- L23 _public prototype_ `const FRigSpacePickerBakeSettings* GetSettings() const;` — Returns the settings struct so it can be displayed in a details view
- L26 _public function_ `const TSharedPtr<TStructOnScope<FRigSpacePickerBakeSettings>>& GetSettingsStructOnScope() const` — Returns the settings struct so it can be displayed in a details view
- L29 _public prototype_ `bool CanPerformBake() const;` — Returns true if baking can be performed
- L32 _public prototype_ `void PerformBake();` — Performs baking of the currently active item
- L36 _protected function_ `virtual TArray<FRigElementKeyWithLabel> GatherAdditionalSpaces(URigHierarchy* Hierarchy, const FRigElementKey& ControlKey) const`
- L38 _protected function_ `virtual IRigSpacePickerDeleteSpacesInterface* GetDeleteSpacesInterface() override` — Disabled
- L39 _protected function_ `virtual IRigSpacePickerMoveSpacesInterface* GetMoveSpacesInterface() override` — Disabled
- L40 _protected function_ `virtual IRigSpacePickerCompensateKeysInterface* GetCompensateKeysInterface() override` — Disabled
- L41 _protected function_ `virtual IRigSpacePickerSupportsBakeDialogInterface* GetSupportsBakeDialogInterface() override` — Disabled, we're the dialog
- L45 _protected prototype_ `virtual void SetActiveSpaces(const TSharedRef<FRigSpacePickerItem>& Item) override;`
- L50 _private member_ `TSharedPtr<TStructOnScope<FRigSpacePickerBakeSettings>> SettingsStructOnScope;` — The settings when baking

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace ControlRigEditor` (scope `UE`)

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/SpacePicker/Models/RigLevelEditorFloatingSpacePickerModel.h` (Private)


#### class `UE::ControlRigEditor::FRigLevelEditorFloatingSpacePickerModel`  
`class FRigLevelEditorFloatingSpacePickerModel : public FRigLevelEditorSpacePickerModel`  
_L14-25_
- inherits: `FRigLevelEditorSpacePickerModel`
- desc: Model for the floating space picker in the level editor.
- L19 _protected function_ `virtual IRigSpacePickerAddSpacesInterface* GetAddSpacesInterface() override` — Disabled
- L20 _protected function_ `virtual IRigSpacePickerDeleteSpacesInterface* GetDeleteSpacesInterface() override` — Disabled
- L21 _protected function_ `virtual IRigSpacePickerMoveSpacesInterface* GetMoveSpacesInterface() override` — Disabled
- L22 _protected function_ `virtual IRigSpacePickerCompensateKeysInterface* GetCompensateKeysInterface() override` — Disabled
- L23 _protected function_ `virtual IRigSpacePickerSupportsBakeDialogInterface* GetSupportsBakeDialogInterface() override` — Disabled

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace ControlRigEditor` (scope `UE`)

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/SpacePicker/Models/RigLevelEditorSpacePickerModel.h` (Private)


#### class `UE::ControlRigEditor::FRigLevelEditorSpacePickerModel`  
`class FRigLevelEditorSpacePickerModel : public FRigSpacePickerModelBase , public IRigSpacePickerSetActiveSpacesInterface , public IRigSpacePickerAddSpacesInterface , public IRigSpacePickerDeleteSpacesInterface , public IRigSpacePickerMoveSpacesInterface , public IRigSpacePickerCompensateKeysInterface , public IRigSpacePickerSupportsBakeDialogInterface`  
_L16-82_
- inherits: `FRigSpacePickerModelBase,IRigSpacePickerSetActiveSpacesInterface,IRigSpacePickerAddSpacesInterface,IRigSpacePickerDeleteSpacesInterface,IRigSpacePickerMoveSpacesInterface,IRigSpacePickerCompensateKeysInterface,IRigSpacePickerSupportsBakeDialogInterface`
- desc: Full model for a space pickers working within the level editor
- L27 _public prototype_ `TSharedPtr<ISequencer> GetSequencer() const;` — Returns the current sequencer or nullptr if sequencer is not active
- L31 _protected function_ `virtual IRigSpacePickerSetActiveSpacesInterface* GetSetActiveSpacesInterface() override`
- L32 _protected function_ `virtual IRigSpacePickerAddSpacesInterface* GetAddSpacesInterface() override`
- L33 _protected function_ `virtual IRigSpacePickerDeleteSpacesInterface* GetDeleteSpacesInterface() override`
- L34 _protected function_ `virtual IRigSpacePickerMoveSpacesInterface* GetMoveSpacesInterface() override`
- L35 _protected function_ `virtual IRigSpacePickerCompensateKeysInterface* GetCompensateKeysInterface() override`
- L36 _protected function_ `virtual IRigSpacePickerSupportsBakeDialogInterface* GetSupportsBakeDialogInterface() override`
- L40 _protected prototype_ `virtual void SetActiveSpaces(const TSharedRef<FRigSpacePickerItem>& Item) override;`
- L44 _protected prototype_ `virtual bool CanAddSpace() const override;`
- L45 _protected prototype_ `virtual void AddSpace(const FRigElementKeyWithLabel& SpaceKeyWithLabel) override;`
- L49 _protected prototype_ `virtual bool CanDeleteSpaces(const TSharedRef<FRigSpacePickerItem>& Item) const override;`
- L50 _protected prototype_ `virtual void DeleteSpaces(const TSharedRef<FRigSpacePickerItem>& Item) override;`
- L54 _protected prototype_ `virtual bool CanMoveSpaces(const TSharedRef<FRigSpacePickerItem>& Item, const ERigSpacePickerMoveSpaceDirection Direction) const override;`
- L55 _protected prototype_ `virtual void MoveSpaces(const TSharedRef<FRigSpacePickerItem>& Item, const ERigSpacePickerMoveSpaceDirection Direction) override;`
- L59 _protected prototype_ `virtual bool CanCompensateKeys() const override;`
- L60 _protected prototype_ `virtual void CompensateKeys() override;`
- L61 _protected prototype_ `virtual bool CanCompensateAllKeys() const override;`
- L62 _protected prototype_ `virtual void CompensateAllKeys() override;`
- L66 _protected prototype_ `virtual bool CanShowBakeDialog() const override;`
- L67 _protected prototype_ `virtual void ShowBakeDialog() override;`
- L71 _protected prototype_ `void NotifyControlSettingChanged(URigHierarchy* Hierarchy, const FRigControlElement* ControlElement) const;` — Notifies space settings of a control changed
- L75 _private prototype_ `bool CanBakeOrCompensate() const;` — Returns true if baking or compensating is possible
- L78 _private prototype_ `void CompensateImpl(const TOptional<FFrameNumber>& OptionalKeyTime, const bool bCompensatePreviousTick) const;` — Implements the compensate functionality
- L81 _private prototype_ `FControlRigEditMode* GetEditMode() const;` — Returns the control rig edit mode of the level editor, or nullptr if the mode is not active

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace ControlRigEditor` (scope `UE`)

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/SpacePicker/Models/RigSpacePickerItem.h` (Private)


#### struct `UE::ControlRigEditor::FRigSpacePickerControlToSpaceBinding`  
`struct FRigSpacePickerControlToSpaceBinding`  
_L17-58_
- desc: A control bound to a space. Useful to group bindings by their common space name
- L19 _public prototype_ `FRigSpacePickerControlToSpaceBinding( URigHierarchy& Hierarchy, const FRigElementKey& InControlKey, const FRigElementKeyWithLabel& InSpaceKey);`
- L24 _public member_ `const FRigElementKey ControlKey;`
- L25 _public member_ `const FRigElementKey SpaceKey;`
- L28 _public function_ `const FName& GetCommonSpaceName() const` — Returns the name common to spaces that can be multi edited
- L31 _public function_ `const FName& GetDisplayName() const` — Returns the display name of the space, useful when not multi-editing
- L34 _public function_ `URigHierarchy* GetHierarchy() const` — Returns the hierarchy or nullptr if the hierarchy of this binding is no longer valid
- L36 _public function_ `inline bool operator==(const FRigSpacePickerControlToSpaceBinding& Other) const`
- L44 _public function_ `inline bool operator!=(const FRigSpacePickerControlToSpaceBinding& Other) const`
- L51 _private member_ `FName CommonSpaceName;` — The name common to spaces that can be multi edited
- L54 _private member_ `FName DisplayName;` — The display name of the space, useful when not multi-editing
- L57 _private member_ `TWeakObjectPtr<URigHierarchy> WeakHierarchy;` — The hierarchy that contains the control and space

#### enum `UE::ControlRigEditor::ERigSpacePickerItemActiveState`  
`enum class ERigSpacePickerItemActiveState : uint8`  
_L61-71_
- desc: Enumerates active states an item can have
- L64 _public enumerator_ `Inactive` — The item is not active
- L67 _public enumerator_ `PartiallyActive` — Some bindings in this item are active
- L70 _public enumerator_ `FullyActive` — All bindings in this item are active. Implies no other item is active.

#### class `UE::ControlRigEditor::FRigSpacePickerItem`  
`class FRigSpacePickerItem : public TSharedFromThis<FRigSpacePickerItem>`  
_L81-146_
- inherits: `TSharedFromThis<FRigSpacePickerItem>`
- desc: An item that is displayed as a single row in the space editor widget. The item contains an array of control to space bindings, one space for each control This is to enable multi-editing when multiple controls with common space names are selected. Items are guaranteed to have common space names accross all their bindings (ensured).
- L90 _public prototype_ `explicit FRigSpacePickerItem(const TArray<FRigSpacePickerControlToSpaceBinding>& InBindings);` — Constructs this item @param InBindings		The bindings for this item
- L93 _public prototype_ `static FName MakeCommonSpaceName(const FRigElementKeyWithLabel& SpaceKey);` — Makes a common space name from the space key. Only bindings with common space names should be stored in an item
- L96 _public prototype_ `bool IsDefaultSpace() const;` — Returns true if this item is a default space
- L99 _public function_ `const TArray<FRigSpacePickerControlToSpaceBinding>& GetBindings() const` — Returns the bindings for this item
- L102 _public function_ `const FSlateColor& GetColor() const` — Returns the color for this item
- L105 _public function_ `const FSlateBrush* GetIconBrush() const` — The icon brush to display for this item
- L108 _public function_ `const FText& GetDisplayName() const` — Returns the display name for this item
- L111 _public function_ `FText GetTooltip() const` — Returns the tooltip for this item
- L114 _public function_ `ERigSpacePickerItemActiveState GetActiveState() const` — Returns the active state of this item
- L117 _public prototype_ `void OverrideActiveState(const ERigSpacePickerItemActiveState NewActiveState);` — Overrides the active state. Useful if the active state shouldn't follow the hierarchy
- L120 _public prototype_ `void Flash(const float Duration);` — Flashes this item's color during duration, useful to provide hints to the user
- L123 _public prototype_ `bool IsFlashing() const;` — True while the item is flashing
- L127 _private member_ `TArray<FRigSpacePickerControlToSpaceBinding> Bindings;` — Bindings for this item
- L130 _private member_ `FText DisplayName;` — The name displayed for this item
- L133 _private member_ `const FSlateBrush* IconBrush = nullptr;` — The icon brush to display for this item
- L136 _private member_ `FSlateColor Color = FSlateColor::UseForeground();` — The final display color, incorporating active state
- L139 _private member_ `ERigSpacePickerItemActiveState ActiveState = ERigSpacePickerItemActiveState::Inactive;` — The active state of this item
- L142 _private member_ `FText CachedTooltip;` — Cached tooltip text
- L145 _private member_ `float FlashTimer = 0.f;` — Timer for the icon to flash

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace ControlRigEditor` (scope `UE`)

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/SpacePicker/Models/RigSpacePickerModelBase.h` (Private)


#### class `UE::ControlRigEditor::IRigSpacePickerSetActiveSpacesInterface`  
`class IRigSpacePickerSetActiveSpacesInterface`  
_L24-31_
- desc: Interface for models that can set active spaces
- L27 _public prototype_ `virtual ~IRigSpacePickerSetActiveSpacesInterface() = default;`
- L30 _public prototype_ `virtual void SetActiveSpaces(const TSharedRef<FRigSpacePickerItem>& Item) = 0;` — Sets the active spaces

#### class `UE::ControlRigEditor::IRigSpacePickerAddSpacesInterface`  
`class IRigSpacePickerAddSpacesInterface`  
_L34-44_
- desc: Interface for models that can add spaces
- L37 _public prototype_ `virtual ~IRigSpacePickerAddSpacesInterface() = default;`
- L40 _public prototype_ `virtual bool CanAddSpace() const = 0;` — Returns true if spaces can currently be added
- L43 _public prototype_ `virtual void AddSpace(const FRigElementKeyWithLabel& SpaceKeyWithLabel) = 0;` — Adds spaces

#### class `UE::ControlRigEditor::IRigSpacePickerDeleteSpacesInterface`  
`class IRigSpacePickerDeleteSpacesInterface`  
_L47-57_
- desc: Interface for models that can delete spaces
- L50 _public prototype_ `virtual ~IRigSpacePickerDeleteSpacesInterface() = default;`
- L53 _public prototype_ `virtual bool CanDeleteSpaces(const TSharedRef<FRigSpacePickerItem>& Item) const = 0;` — Returns true if spaces can currently be deleted
- L56 _public prototype_ `virtual void DeleteSpaces(const TSharedRef<FRigSpacePickerItem>& Item) = 0;` — Deletes spaces of the item

#### enum `UE::ControlRigEditor::ERigSpacePickerMoveSpaceDirection`  
`enum class ERigSpacePickerMoveSpaceDirection : uint8`  
_L60-64_
- desc: Direction in which items are moved
- L62 _public enumerator_ `Up`
- L63 _public enumerator_ `Down`

#### class `UE::ControlRigEditor::IRigSpacePickerMoveSpacesInterface`  
`class IRigSpacePickerMoveSpacesInterface`  
_L67-77_
- desc: Interface for models that can move spaces
- L70 _public prototype_ `virtual ~IRigSpacePickerMoveSpacesInterface() = default;`
- L73 _public prototype_ `virtual bool CanMoveSpaces(const TSharedRef<FRigSpacePickerItem>& Item, const ERigSpacePickerMoveSpaceDirection Direction) const = 0;` — Returns true if spaces can currently be moved
- L76 _public prototype_ `virtual void MoveSpaces(const TSharedRef<FRigSpacePickerItem>& Item, const ERigSpacePickerMoveSpaceDirection Direction) = 0;` — Moves spaces of the item

#### class `UE::ControlRigEditor::IRigSpacePickerCompensateKeysInterface`  
`class IRigSpacePickerCompensateKeysInterface`  
_L80-96_
- desc: Interface for models that can compensate keys
- L83 _public prototype_ `virtual ~IRigSpacePickerCompensateKeysInterface() = default;`
- L86 _public prototype_ `virtual bool CanCompensateKeys() const = 0;` — Returns true if keys can be compensated in sequencer
- L89 _public prototype_ `virtual void CompensateKeys() = 0;` — Compensates keys in sequencer
- L92 _public prototype_ `virtual bool CanCompensateAllKeys() const = 0;` — Returns true if all keys can be compensated in sequencer
- L95 _public prototype_ `virtual void CompensateAllKeys() = 0;` — Compensates all keys in sequencer

#### class `UE::ControlRigEditor::IRigSpacePickerSupportsBakeDialogInterface`  
`class IRigSpacePickerSupportsBakeDialogInterface`  
_L99-109_
- desc: Interface for models that support showing the baking dialog
- L102 _public prototype_ `virtual ~IRigSpacePickerSupportsBakeDialogInterface() = default;`
- L105 _public prototype_ `virtual bool CanShowBakeDialog() const = 0;` — Returns true if a bake dialog can be displayed
- L108 _public prototype_ `virtual void ShowBakeDialog() = 0;` — Shows the bake dialog

#### class `UE::ControlRigEditor::FRigSpacePickerModelBase`  
`class FRigSpacePickerModelBase : public FSelfRegisteringEditorUndoClient , public TSharedFromThis<FRigSpacePickerModelBase>`  
_L112-224_
- inherits: `FSelfRegisteringEditorUndoClient,TSharedFromThis<FRigSpacePickerModelBase>`
- desc: Base view model for the space picker
- L117 _public prototype_ `virtual ~FRigSpacePickerModelBase();`
- L120 _public prototype_ `void Update();` — Updates the model by reevaluating the current hierarchies and controls
- L123 _public prototype_ `void Update(const TWeakObjectPtr<URigHierarchy>& InWeakHierarchy, const TArray<FRigElementKey>& InSelectedControls);` — Updates the model from a single hierarchy and its currently selected controls
- L126 _public prototype_ `void Update(const TMap<TWeakObjectPtr<URigHierarchy>, TArray<FRigElementKey>>& InWeakHierarchyToControlKeysMap);` — Updates the model from hierarchies and their currently selected controls
- L129 _public prototype_ `void GenerateItems();` — Generates item from this model, does not update the model
- L132 _public function_ `const TArray<TSharedPtr<FRigSpacePickerItem>>& GetItems() const` — Returns the current items
- L135 _public function_ `bool IsSpaceSwitchingRestricted() const` — Returns true if any of the selected controls restricts space switching
- L138 _public function_ `virtual IRigSpacePickerSetActiveSpacesInterface* GetSetActiveSpacesInterface()` — Returns the interface to set active spaces, or nullptr if setting active spaces is not supported
- L141 _public function_ `virtual IRigSpacePickerAddSpacesInterface* GetAddSpacesInterface()` — Returns the interface to add spaces, or nullptr if adding spaces is not supported
- L144 _public function_ `virtual IRigSpacePickerDeleteSpacesInterface* GetDeleteSpacesInterface()` — Returns the interface to delete spaces, or nullptr if deleting spaces is not supported
- L147 _public function_ `virtual IRigSpacePickerMoveSpacesInterface* GetMoveSpacesInterface()` — Returns the interface to move spaces, or nullptr if moving spaces is not supported
- L150 _public function_ `virtual IRigSpacePickerCompensateKeysInterface* GetCompensateKeysInterface()` — Returns the interface to compensate keys for spaces, or nullptr compensating keys is not supported
- L153 _public function_ `virtual IRigSpacePickerSupportsBakeDialogInterface* GetSupportsBakeDialogInterface()` — Returns the interface to show a bake dialog, or nullptr if showing a bake dialog is not supported
- L156 _public prototype_ `TArray<FRigElementKey> GetControlKeys() const;` — Returns the current control keys
- L159 _public prototype_ `bool DoesControlHaveSpace(const URigHierarchy* Hierarchy, const FRigElementKey& ControlKey, const FRigElementKey& SpaceKey) const;` — Returns true if given control already has given space assigned
- L162 _public prototype_ `TArray<URigHierarchy*> GetHierarchies() const;` — Returns the current hierarchies
- L165 _public prototype_ `URigHierarchy* TryGetSingleHierarchy() const;` — Tries to get the single hierarchy currently present in this model. Returns nullptr if there are none or many.
- L168 _public function_ `virtual bool SupportsEditingMultipleRigs() const` — Returns true if the model supports editing spaces of multiple rigs
- L171 _public function_ `virtual bool ShouldGenerateDefaultItems() const` — Returns true if default items 'World' and 'Parent' should be generated
- L174 _public function_ `virtual bool ShouldGenerateFavoriteItems() const` — Returns true if items from control customizations should be generated
- L177 _public function_ `virtual bool ShouldGenerateAdditionalItems() const` — Returns true if additional items should be generated
- L180 _public function_ `virtual TArray<FRigElementKeyWithLabel> GatherAdditionalSpaces(URigHierarchy* Hierarchy, const FRigElementKey& ControlKey) const` — Can be implemented to provide additional spaces from external sources (e.g. sequencer channel)
- L183 _public function_ `const TMap<TWeakObjectPtr<URigHierarchy>, TArray<FRigElementKey>>& GetWeakHierarchyToControlKeysMap() const` — Returns current hierarchies with their control keys for which items are generated
- L185 _public prototype_ `DECLARE_EVENT(FRigSpacePickerModelBase, FRigSpacePickerModelRequestRefreshMVVM) FRigSpacePickerModelRequestRefreshMVVM OnRequestRefreshMVVM;`
- L191 _protected prototype_ `virtual void PostUndo(bool bSuccess) override;`
- L192 _protected prototype_ `virtual void PostRedo(bool bSuccess) override;`
- L196 _protected prototype_ `bool CanMoveSpacesImpl(const TSharedRef<FRigSpacePickerItem>& Item, const ERigSpacePickerMoveSpaceDirection Direction) const;` — Default implementation to determine if spaces can be moved
- L200 _private prototype_ `void CacheIsSpaceSwitchingRestricted();` — Caches if space switching restricted into the bIsSpaceSwitchingRestricted member
- L203 _private prototype_ `void OnHierarchyModified( ERigHierarchyNotification InNotif, URigHierarchy* InHierarchy, const FRigNotificationSubject& InSubject);` — Called when the current hierarchy was modified
- L208 _private typedef_ `using FHierarchyToControlFunctionSignature = void(URigHierarchy*, const FRigElementKey&);`
- L210 _private prototype_ `void ForEachControlKey(TFunctionRef<FHierarchyToControlFunctionSignature> Function) const;` — Executes function for each control key
- L212 _private typedef_ `using FHierarchyToControlFunctionWithBreakSignature = bool(URigHierarchy*, const FRigElementKey&);`
- L214 _private prototype_ `void ForEachControlKeyWithBreak(TFunctionRef<FHierarchyToControlFunctionWithBreakSignature> Function) const;` — Executes function for each control key, breaks when function returns false
- L217 _private member_ `bool bCachedIsSpaceSwitchingRestricted = false;` — True if one or more controls restrict space switching
- L220 _private member_ `TArray<TSharedPtr<FRigSpacePickerItem>> Items;` — The current items
- L223 _private member_ `TMap<TWeakObjectPtr<URigHierarchy>, TArray<FRigElementKey>> WeakHierarchyToControlKeysMap;` — The current hierarchies with their control keys for which items are generated

#### Free symbols / members of external scopes

- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace ControlRigEditor` (scope `UE`)
- L185 _delegate_ `DECLARE_EVENT(FRigSpacePickerModelBase, FRigSpacePickerModelRequestRefreshMVVM) FRigSpacePickerModelRequestRefreshMVVM OnRequestRefreshMVVM;`

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/SpacePicker/RigFloatingSpacePickerManager.h` (Private)


#### class `UE::ControlRigEditor::FRigFloatingSpacePickerManager`  
`class FRigFloatingSpacePickerManager : public FNoncopyable`  
_L15-44_
- inherits: `FNoncopyable`
- desc: Manages the floating space picker, which by default is spawned by pressing tab.
- L19 _public prototype_ `explicit FRigFloatingSpacePickerManager(FControlRigEditMode& InOwningMode UE_LIFETIMEBOUND);`
- L21 _public prototype_ `~FRigFloatingSpacePickerManager();`
- L24 _public prototype_ `void SummonSpacePickerAtCursor();` — Spawns a new space picker at the cursor. Replaces the old one if one exists.
- L27 _public prototype_ `TSharedPtr<SRigSpacePickerMenuEntry> CreateSpacePickerMenuEntry();` — Creates a space picker menu entry
- L31 _private prototype_ `TSharedPtr<SRigSpacePickerDialog> CreateSpacePickerDialog();` — Creates a space picker dialog
- L34 _private prototype_ `void TryCloseDialog();` — Tries to close a currently open dialog
- L37 _private member_ `FControlRigEditMode& OwningMode;` — The edit mode that owns us. Needed to display some information about the space picker.
- L40 _private member_ `TWeakPtr<SWindow> WeakWindow;` — The window that contained the last created space picker. If still valid, we replace the window.
- L43 _private member_ `TSharedPtr<FRigSpacePickerModelBase> ViewModel;` — Model for the currently active floating manager

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace ControlRigEditor` (scope `UE`)

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/SpacePicker/Views/SRigLevelEditorSpacePicker.h` (Private)


#### class `UE::ControlRigEditor::SRigLevelEditorSpacePicker`  
`class SRigLevelEditorSpacePicker : public SCompoundWidget , public FControlRigBaseDockableView`  
_L17-57_
- inherits: `SCompoundWidget,FControlRigBaseDockableView`
- L22 _public typedef_ `using FWeakHierarchytoControlsMap = TMap<TWeakObjectPtr<URigHierarchy>, TArray<FRigElementKey>>;`
- L24 _public function_ `SLATE_BEGIN_ARGS(SRigLevelEditorSpacePicker)`
- L28 _public prototype_ `SLATE_ARGUMENT(FWeakHierarchytoControlsMap, InitialSelection) SLATE_END_ARGS() virtual ~SRigLevelEditorSpacePicker() override;` — The initially selected hierarchy.
- L34 _public prototype_ `void Construct( const FArguments& InArgs, FControlRigEditMode& InEditMode, const TSharedRef<FRigSelectionViewModel>& InSelectionViewModel);`
- L41 _protected prototype_ `virtual void HandleControlSelected(UControlRig* Subject, FRigControlElement* InControl, bool bSelected) override;`
- L42 _protected function_ `virtual TSharedRef<FControlRigBaseDockableView> AsSharedWidget() override`
- L47 _private prototype_ `void RequestRefresh();` — Updates this widget on the next tick
- L50 _private member_ `TSharedPtr<FRigSelectionViewModel> SelectionViewModel;` — View model for when control rig selection changes.
- L53 _private member_ `TSharedPtr<FRigLevelEditorSpacePickerModel> SpacePickerViewModel;` — Model driving the space picker widget
- L56 _private member_ `FTimerHandle PendingRefreshHandle;` — Timer handle to refresh this widget

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace ControlRigEditor` (scope `UE`)

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/SpacePicker/Views/SRigSpacePicker.h` (Private)


#### class `UE::ControlRigEditor::SRigSpacePicker`  
`class SRigSpacePicker : public SCompoundWidget`  
_L21-67_
- inherits: `SCompoundWidget`
- desc: A generic widget to edit spaces of controls in control rigs, feature set depends on the model
- L25 _public function_ `SLATE_BEGIN_ARGS(SRigSpacePicker)`
- L29 _public prototype_ `SLATE_ARGUMENT(FText, Title) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<FRigSpacePickerModelBase>& InModel);` — The title for this widget
- L38 _protected prototype_ `virtual void OnItemSelected(TSharedPtr<FRigSpacePickerItem> Item, ESelectInfo::Type SelectInfo);` — Called when an item was selected
- L41 _protected function_ `virtual void OnIsAddMenuOpenChanged(bool bIsOpen)` — Called when the add menu is opened or closed
- L45 _private prototype_ `void TryAddTitle(const FText& Title);` — Tries to add a title widget, fails quietly if no title is set
- L48 _private prototype_ `void TryCreateBottomButtons(const FArguments& InArgs);` — Tries to create buttons to operate on spaces at the bottom of the widget
- L51 _private prototype_ `TSharedRef<ITableRow> OnGenerateItemRow(TSharedPtr<FRigSpacePickerItem> Item, const TSharedRef<STableViewBase>& OwnerTable);` — Called when an item row is generated
- L54 _private prototype_ `void OnRequestRefreshMVVM();` — Called when spaces changed
- L57 _private member_ `TSharedPtr<SVerticalBox> TopLevelListBox;` — Top level box containing all content
- L60 _private member_ `TSharedPtr<SListView<TSharedPtr<FRigSpacePickerItem>>> SpacesList;` — Vertical box containing spaces
- L63 _private member_ `TSharedPtr<FRigSpacePickerModelBase> Model;` — A model for this view
- L66 _private member_ `TArray<TSharedPtr<FRigSpacePickerItem>> Items;` — Items displayed in this view

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace ControlRigEditor` (scope `UE`)

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/SpacePicker/Views/SRigSpacePickerBakeDialog.h` (Private)


#### class `UE::ControlRigEditor::SRigSpacePickerBakeDialog`  
`class SRigSpacePickerBakeDialog : public SCompoundWidget`  
_L19-49_
- inherits: `SCompoundWidget`
- desc: Dialog for baking controls to a space
- L23 _public function_ `SLATE_BEGIN_ARGS(SRigSpacePickerBakeDialog)`
- L26 _public prototype_ `SLATE_ARGUMENT(TWeakObjectPtr<URigHierarchy>, WeakHierarchy) SLATE_ARGUMENT(TArray<FRigElementKey>, Controls) SLATE_ARGUMENT(FRigSpacePickerBakeSettings, Settings) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L35 _public prototype_ `FReply OpenDialog(bool bModal = true);` — Opens the bake dialog
- L38 _public prototype_ `void CloseDialog();` — Closes the bake dialog
- L42 _private member_ `TWeakPtr<SWindow> DialogWindow;` — The dialog window, valid while the dialog is open
- L45 _private member_ `TSharedPtr<IStructureDetailsView> DetailsView;` — Details view used to display bake settings
- L48 _private member_ `TSharedPtr<FRigLevelEditorBakeDialogSpacePickerModel> ViewModel;` — A model for the space picker view displayed in this bake dialog

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace ControlRigEditor` (scope `UE`)

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/SpacePicker/Views/SRigSpacePickerDialog.h` (Private)


#### class `UE::ControlRigEditor::SRigSpacePickerDialog`  
`class SRigSpacePickerDialog : public SRigSpacePicker`  
_L10-46_
- inherits: `SRigSpacePicker`
- desc: Wraps SRigSpacePicker to be suitable as a dialog
- L15 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<FRigSpacePickerModelBase>& InModel);` — Constructs this widget
- L18 _public prototype_ `TSharedPtr<SWindow> OpenDialog(bool bModal = true);` — Shows this widget as a dialog
- L21 _public prototype_ `void CloseDialog();` — Closes the dialog
- L25 _protected prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;`
- L26 _protected prototype_ `virtual bool SupportsKeyboardFocus() const override;`
- L30 _protected prototype_ `virtual void OnItemSelected(TSharedPtr<FRigSpacePickerItem> Item, ESelectInfo::Type SelectInfo) override;`
- L31 _protected prototype_ `virtual void OnIsAddMenuOpenChanged(const bool bIsOpen) override;`
- L36 _private prototype_ `void OnWindowDeactivated();` — Called when the window was deactivated
- L39 _private member_ `TWeakPtr<SWindow> WeakDialogWindow;` — The dialog window if currently displayed as dialog
- L42 _private member_ `TWeakPtr<SWidget> WeakWidgetToFocusOnDialogClosed;` — The widget we want to pass keyboard focus to when this widget is displayed as a dialog
- L45 _private member_ `bool bIsAddMenuOpen = false;` — True when the add menu is open

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace ControlRigEditor` (scope `UE`)

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/SpacePicker/Views/SRigSpacePickerMenuEntry.h` (Private)


#### class `UE::ControlRigEditor::SRigSpacePickerMenuEntry`  
`class SRigSpacePickerMenuEntry : public SRigSpacePicker`  
_L10-26_
- inherits: `SRigSpacePicker`
- desc: Wraps SRigSpacePicker to be suitable as a menu entry
- L15 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<FRigSpacePickerModelBase>& InModel);` — Constructs this widget
- L19 _protected prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;`
- L20 _protected prototype_ `virtual bool SupportsKeyboardFocus() const override;`
- L24 _protected prototype_ `virtual void OnItemSelected(TSharedPtr<FRigSpacePickerItem> Item, ESelectInfo::Type SelectInfo) override;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace ControlRigEditor` (scope `UE`)

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/SpacePicker/Widgets/SRigSpacePickerAddSpaceButton.h` (Private)


#### class `UE::ControlRigEditor::SRigSpacePickerAddSpaceButton`  
`class SRigSpacePickerAddSpaceButton : public SCompoundWidget`  
_L19-62_
- inherits: `SCompoundWidget`
- desc: Add Space button for the space picker
- L22 _public function_ `SLATE_BEGIN_ARGS(SRigSpacePickerAddSpaceButton)`
- L26 _public prototype_ `SLATE_EVENT(FOnIsOpenChanged, OnIsMenuOpenChanged) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<FRigSpacePickerModelBase>& InViewModel);` — Executed when the add menu is opened or closed
- L34 _private prototype_ `TSharedRef<SWidget> OnGetMenuContent();` — @return Menu content for the combo button
- L37 _private prototype_ `void HandleClickTreeItem(TSharedPtr<FRigHierarchyTreeElement> TreeElement);` — Assigns the clicked space to the current control selection
- L40 _private prototype_ `bool IsRigTreeItemVisible(const FRigHierarchyKey& HierarchyKey, TSharedRef<FRigDependenciesProviderForControlRig> DependencyProvider) const;` — Returns true if the rig tree item should be visible
- L43 _private prototype_ `bool IsButtonEnabled() const;` — Returns true when the button should be interactive
- L46 _private prototype_ `FText GetTooltipText() const;` — Returns the tooltip text
- L49 _private prototype_ `const URigHierarchy* GetHierarchy() const;` — Returns the current hierarchy
- L52 _private function_ `const FRigHierarchyTreeDisplaySettings& GetDisplaySettingsRef() const` — Returns the hierarchy display settings
- L55 _private member_ `TSharedPtr<SPositiveActionButton> ComboButton;` — Combo button that opens the add space menu
- L58 _private member_ `FRigHierarchyTreeDisplaySettings HierarchyDisplaySettings;` — Display settings for the rig hierarchy
- L61 _private member_ `TSharedPtr<FRigSpacePickerModelBase> ViewModel;` — The model of the view that displays this button

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace ControlRigEditor` (scope `UE`)

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/Tools/AssetDefinition_ControlRigPose.h` (Private)


#### class `UAssetDefinition_ControlRigPose`  
`class UAssetDefinition_ControlRigPose : public UAssetDefinitionDefault`  
_L11-26_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L17 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L18 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L19 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L20 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/Tools/ControlRigFrustumSelectInteraction.h` (Private)


#### class `UControlRigFrustumSelectInteraction`  
`class UControlRigFrustumSelectInteraction : public UFrustumSelectInteraction`  
_L13-28_
- reflection: `UCLASS(MinimalAPI, Transient)`
- inherits: `UFrustumSelectInteraction`
- desc: Similar to its base class, this marquee select tool switches between LMB only and Ctrl + Alt + LMB to activate marquee selection. Could potentially be used to add other custom logic.
- L18 _public prototype_ `UControlRigFrustumSelectInteraction();`
- L20 _public prototype_ `virtual void Initialize(UViewportInteractionsBehaviorSource* const InViewportInteractionsBehaviorSource) override;`
- L21 _public prototype_ `virtual void BeginDestroy() override;`
- L23 _public function_ `virtual TArray<FEditorModeID> GetUnsupportedModes() const override`
- L26 _private prototype_ `void OnControlRigEditorSettingChanged(UObject* InSettingsChanged, FPropertyChangedEvent& InPropertyChangedEvent);`
- L27 _private prototype_ `void UpdateBindings();`

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Public/BakeToControlRigHelper.h` (Public)


#### struct `UE::ControlRig::FBakeToControlRigResult`  
`struct FBakeToControlRigResult`  
_L27-33_
- desc: Result returned by InitControlRigFromAnimSequence / HandleBakeToControlRig. Track, Section, and ControlRig are only guaranteed valid when bSuccess is true.
- L29 _public member_ `UMovieSceneControlRigParameterTrack* Track = nullptr;`
- L30 _public member_ `UMovieSceneControlRigParameterSection* Section = nullptr;`
- L31 _public member_ `UControlRig* ControlRig = nullptr;`
- L32 _public member_ `bool bSuccess = false;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API CONTROLRIGEDITOR_API`
- L22 _namespace_ `namespace UE`
- L22 _namespace_ `namespace ControlRig` (scope `UE`)
- L43 _delegate_ `DECLARE_DELEGATE_RetVal_ThreeParams(bool, FPopulateAnimSequenceDelegate, UAnimSequence* , UAnimSeqExportOption* , USkeletalMeshComponent* );` — Delegate that callers provide to populate a temp UAnimSequence with animation data. Called after the user confirms the bake options dialog. Return true on success, false to abort the bake. CR track editor: fills via MovieSceneToolHelpers::ExportToAnimSequence (from skel mesh). Mixer track editor: fills via ExportMixerToAnimSequence (from EvaluateRange).
- L43 _prototype_ `DECLARE_DELEGATE_RetVal_ThreeParams(bool, FPopulateAnimSequenceDelegate, UAnimSequence* , UAnimSeqExportOption* , USkeletalMeshComponent* );` (scope `UE::ControlRig`) — Delegate that callers provide to populate a temp UAnimSequence with animation data. Called after the user confirms the bake options dialog. Return true on success, false to abort the bake. CR track editor: fills via MovieSceneToolHelpers::ExportToAnimSequence (from skel mesh). Mixer track editor: fills via ExportMixerToAnimSequence (from EvaluateRange).
- L56 _prototype_ `FBakeToControlRigResult InitControlRigFromAnimSequence( const TSharedPtr<ISequencer>& Sequencer, UMovieScene* MovieScene, UMovieSceneControlRigParameterTrack* Track, const FControlRigAssetStrongReference& AssetReference, UObject* BoundActor, USkeletalMeshComponent* SkelMeshComp, UAnimSequence* AnimSequence, bool bReduceKeys, const FSmartReduceParams& SmartReduceParams);` (scope `UE::ControlRig`) — Low-level helper: given an already-created track and a pre-populated anim sequence, creates the control rig instance, validates it, initializes it, creates the section, loads the animation, and optionally reduces keys. Callers are responsible for creating/placing the track, managing edit mode, binding delegates, disabling source tracks, and notifying sequencer.
- L79 _prototype_ `void BuildBakeToControlRigMenu( FMenuBuilder& MenuBuilder, USkeleton* Skeleton, bool& bFilterAssetBySkeleton, const FPopulateAnimSequenceDelegate& PopulateDelegate, const TSharedPtr<ISequencer>& Sequencer, FGuid ObjectBinding, UObject* BoundActor, USkeletalMeshComponent* SkelMeshComp, TFunction<UMovieSceneControlRigParameterTrack*(UMovieScene*)> TrackFactory, TFunction<void(const FBakeToControlRigResult&)> OnComplete = nullptr, const FText& SubmenuLabelOverride = FText::GetEmpty());` (scope `UE::ControlRig`) — Builds the "Filter Asset By Skeleton" toggle and "Bake To Control Rig" submenu into the provided MenuBuilder. When the user picks a rig, the full bake flow runs automatically: options dialog, PopulateDelegate to fill the anim sequence, TrackFactory to create/place the track, InitControlRigFromAnimSequence, then OnComplete. @param bFilterAssetBySkeleton  Mutable reference — caller owns the bool (persists across menu opens). @param PopulateDelegate        Fills the temp anim sequence (caller-specific). @param TrackFactory            Creates and returns the CR track (standalone AddTrack or mixer AddChildTrack). @param OnComplete              Called after successful bake for caller-specific post-processing (edit mode, BindControlRig, muting source tracks, etc.).
- L97 _prototype_ `FBakeToControlRigResult HandleBakeToControlRig( const FControlRigAssetStrongReference& AssetReference, const TSharedPtr<ISequencer>& Sequencer, FGuid ObjectBinding, UObject* BoundActor, USkeletalMeshComponent* SkelMeshComp, USkeleton* Skeleton, const FPopulateAnimSequenceDelegate& PopulateDelegate, TFunction<UMovieSceneControlRigParameterTrack*(UMovieScene*)> TrackFactory);` (scope `UE::ControlRig`) — Full bake flow: shows options dialog, calls PopulateDelegate, creates track via TrackFactory, initializes rig via InitControlRigFromAnimSequence. Called internally by BuildBakeToControlRigMenu, but also usable directly.

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Public/ControlConstraintChannelInterface.h` (Public)


#### struct `FControlConstraintChannelInterface`  
`struct FControlConstraintChannelInterface : ITransformConstraintChannelInterface`  
_L24-54_
- inherits: `ITransformConstraintChannelInterface`
- L26 _public prototype_ `virtual ~FControlConstraintChannelInterface() override = default;`
- L30 _public prototype_ `virtual UMovieSceneSection* GetHandleSection(const UTransformableHandle* InHandle, const TSharedPtr<ISequencer>& InSequencer) override;`
- L31 _public prototype_ `virtual UMovieSceneSection* GetHandleConstraintSection(const UTransformableHandle* InHandle, const TSharedPtr<ISequencer>& InSequencer) override;`
- L34 _public prototype_ `virtual UWorld* GetHandleWorld(UTransformableHandle* InHandle) override;` — Get the world from the ControlRig.
- L37 _public prototype_ `virtual bool SmartConstraintKey( UTickableTransformConstraint* InConstraint, const TOptional<bool>& InOptActive, const TRange<FFrameNumber>& InTimeRange, const TSharedPtr<ISequencer>& InSequencer) override;` — Add an active/inactive key to the constraint channel if needed and does the transform compensation on the control's transform channels.
- L42 _public prototype_ `virtual void AddHandleTransformKeys( const TSharedPtr<ISequencer>& InSequencer, const UTransformableHandle* InHandle, const TArray<FFrameNumber>& InFrames, const TArray<FTransform>& InLocalTransforms, const EMovieSceneTransformChannel& InChannels) override;` — Add keys on the controls's transform channels.
- L50 _protected prototype_ `virtual void UnregisterTrack(UMovieSceneTrack* InTrack, UWorld* InWorld) override;`
- L53 _private prototype_ `static UMovieSceneControlRigParameterSection* GetControlSection(const UTransformableControlHandle* InHandle, const TSharedPtr<ISequencer>& InSequencer, const bool bIsConstraint);`

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Public/ControlRigAssetFactory.h` (Public)


#### class `UControlRigAssetFactory`  
`class UControlRigAssetFactory : public UFactory`  
_L16-55_
- reflection: `UCLASS(MinimalAPI, HideCategories=Object)`
- inherits: `UFactory`
- L20 _private member_ `UClass* EditorOnlyClass;`
- L23 _public prototype_ `UControlRigAssetFactory();`
- L27 _public member_ `TSubclassOf<UControlRig> ParentClass;` — `UPROPERTY(EditAnywhere, Category="Control Rig Factory", meta=(AllowAbstract = ""))` — The class of the created instances
- L31 _public member_ `bool bCreateAsControlRigModule = false;` — `UPROPERTY(EditAnywhere, Category = "Control Rig Factory", meta = (AllowAbstract = ""))` — If true, the control rig is created as Control Rig Module
- L34 _public prototype_ `virtual bool ConfigureProperties() override;` — UFactory Interface
- L35 _public prototype_ `virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn, FName CallingContext) override;`
- L36 _public prototype_ `virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;`
- L37 _public prototype_ `virtual bool CanCreateNew() const override;`
- L45 _public prototype_ `static UControlRigRuntimeAsset* CreateNewControlRigAsset(const FString& InDesiredPackagePath, const bool bModularRig = false);` — `UFUNCTION(BlueprintCallable, Category = "Control Rig")` — Create a new control rig asset within the contents space of the project. @param InDesiredPackagePath The package path to use for the control rig asset @param bModularRig If true the rig will be created as a modular rig
- L54 _public prototype_ `static UControlRigRuntimeAsset* CreateControlRigFromSkeletalMeshOrSkeleton(UObject* InSelectedObject, const bool bModularRig = false);` — `UFUNCTION(BlueprintCallable, Category = "Control Rig")` — Create a new control rig asset within the contents space of the project based on a skeletal mesh or skeleton object. @param InSelectedObject The SkeletalMesh / Skeleton object to base the control rig asset on @param bModularRig If true the rig will be created as a modular rig

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API CONTROLRIGEDITOR_API`

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Public/ControlRigBlueprintEditorLibrary.h` (Public)


#### enum `ECastToControlRigBlueprintCases`  
`enum class ECastToControlRigBlueprintCases : uint8`  
_L19-23_
- reflection: `UENUM(BlueprintType)`
- L21 _public enumerator_ `CastSucceeded`
- L22 _public enumerator_ `CastFailed`

#### class `UControlRigBlueprintEditorLibrary`  
`class UControlRigBlueprintEditorLibrary : public URigVMEditorBlueprintLibrary`  
_L26-67_
- reflection: `UCLASS(MinimalAPI, BlueprintType, meta=(ScriptName="ControlRigBlueprintLibrary"))`
- inherits: `URigVMEditorBlueprintLibrary`
- L33 _public prototype_ `static void CastToControlRigBlueprint( UObject* Object, ECastToControlRigBlueprintCases& Branches, UControlRigBlueprint*& AsControlRigBlueprint);` — `UFUNCTION(BlueprintCallable, Category = "Control Rig Blueprint", Meta = (ExpandEnumAsExecs = "Branches"))`
- L39 _public prototype_ `static void SetPreviewMesh(UControlRigBlueprint* InRigBlueprint, USkeletalMesh* PreviewMesh, bool bMarkAsDirty = true);` — `UFUNCTION(BlueprintCallable, Category = "Control Rig Blueprint")`
- L42 _public prototype_ `static USkeletalMesh* GetPreviewMesh(UControlRigBlueprint* InRigBlueprint);` — `UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Control Rig Blueprint")`
- L45 _public prototype_ `static void RequestControlRigInit(UControlRigBlueprint* InRigBlueprint);` — `UFUNCTION(BlueprintCallable, Category = "Control Rig Blueprint")`
- L48 _public prototype_ `static TArray<UControlRigBlueprint*> GetCurrentlyOpenRigBlueprints();` — `UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Control Rig Blueprint")`
- L51 _public prototype_ `static TArray<UStruct*> GetAvailableRigUnits();` — `UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Control Rig Blueprint")`
- L54 _public prototype_ `static URigHierarchy* GetHierarchy(UControlRigBlueprint* InRigBlueprint);` — `UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Control Rig Blueprint")`
- L57 _public prototype_ `static URigHierarchyController* GetHierarchyController(UControlRigBlueprint* InRigBlueprint);` — `UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Control Rig Blueprint")`
- L60 _public prototype_ `static void SetupAllEditorMenus();` — `UFUNCTION(BlueprintCallable, BlueprintCallable, Category = "Control Rig Blueprint")`
- L63 _public prototype_ `static TArray<FRigModuleDescription> GetAvailableRigModules();` — `UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Control Rig Blueprint")`
- L66 _public prototype_ `static UControlRigRuntimeAsset* CreateControlRigAssetFromBlueprint(UControlRigBlueprint* InRigBlueprint);` — `UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Control Rig Blueprint")`

#### Free symbols / members of external scopes

- L16 _macro_ `#define UE_API CONTROLRIGEDITOR_API`

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Public/ControlRigBlueprintFactory.h` (Public)


#### class `UControlRigBlueprintFactory`  
`class UControlRigBlueprintFactory : public UFactory`  
_L17-54_
- reflection: `UCLASS(MinimalAPI, HideCategories=Object)`
- inherits: `UFactory`
- L22 _public prototype_ `UControlRigBlueprintFactory();`
- L26 _public member_ `TSubclassOf<UControlRig> ParentClass;` — `UPROPERTY(EditAnywhere, Category="Control Rig Factory", meta=(AllowAbstract = ""))` — The parent class of the created blueprint
- L30 _public member_ `bool bCreateAsControlRigModule = false;` — `UPROPERTY(EditAnywhere, Category = "Control Rig Factory", meta = (AllowAbstract = ""))` — If true, the control rig is created as Control Rig Module
- L33 _public prototype_ `virtual bool ConfigureProperties() override;` — UFactory Interface
- L34 _public prototype_ `virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn, FName CallingContext) override;`
- L35 _public prototype_ `virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;`
- L36 _public prototype_ `virtual bool CanCreateNew() const override;`
- L44 _public prototype_ `static UControlRigBlueprint* CreateNewControlRigAsset(const FString& InDesiredPackagePath, const bool bModularRig = false);` — `UFUNCTION(BlueprintCallable, Category = "Control Rig")` — Create a new control rig asset within the contents space of the project. @param InDesiredPackagePath The package path to use for the control rig asset @param bModularRig If true the rig will be created as a modular rig
- L53 _public prototype_ `static UControlRigBlueprint* CreateControlRigFromSkeletalMeshOrSkeleton(UObject* InSelectedObject, const bool bModularRig = false);` — `UFUNCTION(BlueprintCallable, Category = "Control Rig")` — Create a new control rig asset within the contents space of the project based on a skeletal mesh or skeleton object. @param InSelectedObject The SkeletalMesh / Skeleton object to base the control rig asset on @param bModularRig If true the rig will be created as a modular rig

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API CONTROLRIGEDITOR_API`

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Public/ControlRigSequencerEditorLibrary.h` (Public)


#### struct `FControlRigSequencerBindingProxy`  
`struct FControlRigSequencerBindingProxy`  
_L40-63_
- reflection: `USTRUCT(BlueprintType)`
- L44 _public function_ `FControlRigSequencerBindingProxy() : ControlRig(nullptr) , Track(nullptr)`
- L49 _public function_ `FControlRigSequencerBindingProxy(const FMovieSceneBindingProxy& InProxy, UControlRig* InControlRig, UMovieSceneControlRigParameterTrack* InTrack) : Proxy(InProxy) , ControlRig(InControlRig) , Track(InTrack)`
- L56 _public member_ `FMovieSceneBindingProxy Proxy;` — `UPROPERTY(BlueprintReadOnly, Category = ControlRig)`
- L59 _public member_ `TObjectPtr<UControlRig> ControlRig;` — `UPROPERTY(BlueprintReadOnly, Category = ControlRig)`
- L62 _public member_ `TObjectPtr<UMovieSceneControlRigParameterTrack> Track;` — `UPROPERTY(BlueprintReadOnly, Category = ControlRig)`

#### enum `EAnimToolBlendOperation`  
`enum class EAnimToolBlendOperation : uint8`  
_L66-74_
- reflection: `UENUM(BlueprintType)`
- L68 _public enumerator_ `Tween`
- L69 _public enumerator_ `BlendToNeighbor`
- L70 _public enumerator_ `PushPull`
- L71 _public enumerator_ `BlendRelative`
- L72 _public enumerator_ `BlendToEase`
- L73 _public enumerator_ `SmoothRough`

#### struct `FArrayOfRigControlValues`  
`struct FArrayOfRigControlValues`  
_L78-92_
- reflection: `USTRUCT(BlueprintType)`
- L84 _public member_ `FName ControlName;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = ControlRig)` — Name of the Control
- L88 _public member_ `TArray<FRigControlValue> Values;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = ControlRig)` — Array of control rig values, will correspond usually to a frame value
- L91 _public member_ `FRigControlElement* CachedElement = nullptr;` — cached value, may be empty but will be set after UControlRigSequencerEditorLibrary::GetControlValues

#### enum `EControlRigTransformSpace`  
`enum class EControlRigTransformSpace : uint8`  
_L95-99_
- reflection: `UENUM(BlueprintType)`
- L97 _public enumerator_ `Local = 0`
- L98 _public enumerator_ `Global`

#### struct `FArrayOfRigControlTransforms`  
`struct FArrayOfRigControlTransforms`  
_L102-116_
- reflection: `USTRUCT(BlueprintType)`
- L108 _public member_ `FName ControlName;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = ControlRig)` — Name of the Control
- L112 _public member_ `TArray<FTransform> Transforms;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = ControlRig)` — Array of control rig transforms, will correspond usually to a frame value
- L115 _public member_ `FRigControlElement* CachedElement = nullptr;` — cached value, may be empty but will be set after UControlRigSequencerEditorLibrary::BatchGetControlTransforms or BatchSetControlTransforms

#### class `UControlRigSequencerEditorLibrary`  
`class UControlRigSequencerEditorLibrary : public UBlueprintFunctionLibrary`  
_L122-1505_
- reflection: `UCLASS(MinimalAPI, meta=(Transient, ScriptName="ControlRigSequencerLibrary"))`
- inherits: `UBlueprintFunctionLibrary`
- desc: This is a set of helper functions to access various parts of the Sequencer and Control Rig API via Python and Blueprints.
- L135 _public prototype_ `static TArray<UControlRig*> GetVisibleControlRigs();` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Sequencer Tools | Control Rig")` — Get all of the visible control rigs in the level @return returns list of visible Control Rigs
- L143 _public prototype_ `static TArray<FControlRigSequencerBindingProxy> GetControlRigs(ULevelSequence* LevelSequence);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Sequencer Tools | Control Rig")` — Get all of the control rigs and their bindings in the level sequence @param LevelSequence The movie scene sequence to look for Control Rigs @return returns list of Control Rigs in the level sequence.
- L154 _public prototype_ `static UMovieSceneTrack* FindOrCreateControlRigTrack(UWorld* World, ULevelSequence* LevelSequence, const UClass* ControlRigClass, const FMovieSceneBindingProxy& InBinding, bool bIsLayeredControlRig = false);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Sequencer Tools | Control Rig")` — Find or create a Control Rig track of a specific class based upon the binding @param World The world used to spawn into temporarily if binding is a spawnable @param LevelSequence The LevelSequence to find or create @param ControlRigClass The class of the Control Rig @param InBinding The binding (actor or component binding) to find or create the Control Rig track @return returns Return the found or created track
- L164 _public prototype_ `static TArray<UMovieSceneTrack*> FindOrCreateControlRigComponentTrack(UWorld* World, ULevelSequence* LevelSequence, const FMovieSceneBindingProxy& InBinding);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Sequencer Tools | Control Rig")` — Find or create a Control Rig Component @param World The world used to spawn into temporarily if binding is a spawnable @param LevelSequence The LevelSequence to find or create @param InBinding The binding (actor or component binding) to find or create the Control Rig tracks @return returns Find array of component Control Rigs that were found or created
- L178 _public prototype_ `static bool ExportAnimSequenceFromSequencer(UAnimSequence* AnimSequence, UAnimSeqExportOption* ExportOption, const FMovieSceneBindingProxy& Binding, bool bCreateLink);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Sequencer Tools | Animation")` — Export Passed in Binding as an Anim Sequence, using open Level Sequence in Sequencer. Use this instead of USequencerToolsFunctionLibrary::ExportAnimSequence when you may be exporting an anim sequence from a Spawnable that can't be created dynamically in a closed system. @AnimSequence The AnimSequence to save into. @ExportOption The export options for the sequence. @InBinding Binding to export that has a skelmesh component on it @InAnimSequenceFilename File to create @bCreateLink If true will create a link between the animation sequence and the level sequence
- L186 _public prototype_ `static bool DeleteLinkedAnimSequence(const FMovieSceneBindingProxy& Binding);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Sequencer Tools | Animation")` — Remove the bidirectional link between the AnimSequence owned by the given binding and its LevelSequence. @param Binding The binding whose linked AnimSequence should be unlinked @return True if a linked AnimSequence was found and unlinked
- L194 _public prototype_ `static bool DeleteLinkedAnimTrack(const FMovieSceneBindingProxy& Binding);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Sequencer Tools | Animation")` — Remove the linked animation track and its linked animation sequence for the given binding. @param Binding The binding whose linked track and anim sequence should be removed @return True if a linked track was found and removed
- L202 _public prototype_ `static UMovieSceneTrack* GetLinkedAnimTrack(const FMovieSceneBindingProxy& InBinding);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Sequencer Tools | Animation")` — Get the linked animation track for the given binding (read-only lookup). @param InBinding The binding to look up @return The linked UMovieSceneTrack, or nullptr if none exists
- L211 _public prototype_ `static UMovieSceneTrack* GetOrCreateLinkedAnimTrack(const FMovieSceneBindingProxy& InBinding);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Sequencer Tools | Animation")` — Find or create the linked animation track for the given binding. Same as Configure AutoBake in the UI. Creates the necessary track structure, linked anim sequence, and section if none exist. @param InBinding The binding to find or create the linked track for @return The linked UMovieSceneTrack, or nullptr on failure
- L219 _public prototype_ `static void AddAutoBake(const TArray<FMovieSceneBindingProxy>& InBindings);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Sequencer Tools | Animation")` — Set up auto-bake recorders for the linked anim sequences on the given bindings. Equivalent to the "Add AutoBake" context-menu entry in the Sequencer UI. @param InBindings The bindings to configure for auto-baking
- L230 _public prototype_ `static bool IsolateLinkedAnimTrack(const FMovieSceneBindingProxy& InBinding, bool bIsolate);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Sequencer Tools | Animation")` — Isolate or un-isolate the linked animation track for the given binding. When isolating: enables the linked anim track and disables other anim/control rig tracks. When un-isolating: restores the previous evaluation state. @param InBinding The binding whose linked track to isolate @param bIsolate True to isolate, false to un-isolate @return True if any track evaluation state was changed
- L238 _public prototype_ `static bool IsolateLinkedAnimTracksForAllBindings(bool bIsolate);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Sequencer Tools | Animation")` — Isolate or un-isolate the linked animation tracks for every binding in the focused Sequencer movie scene. @param bIsolate True to isolate, false to un-isolate @return True if any track evaluation state was changed
- L259 _public prototype_ `static bool LoadAnimSequenceIntoControlRigSectionWithRange(UMovieSceneSection* MovieSceneSection, UAnimSequence* AnimSequence, USkeletalMeshComponent* SkelMeshComp, FFrameNumber InStartFrame, bool bUseCustomAnimRange, FFrameNumber AnimStartRange, FFrameNumber AnimEndRange, EMovieSceneTimeUnit TimeUnit = EMovieSceneTimeUnit::DisplayRate, bool bKeyReduce = false, float Tolerance = 0.001f, EMovieSceneKeyInterpolation Interpolation = EMovieSceneKeyInterpolation::SmartAuto, bool bResetControls = true, bool bOntoSelectedControls = false);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Sequencer Tools | Control Rig")` — Load anim sequence into this control rig section @param MovieSceneSection The MovieSceneSectionto load into @param AnimSequence The Sequence to load @param MovieScene The MovieScene getting loaded into @param SkelMeshComponent The Skeletal Mesh component getting loaded into. @param InStartFrame Frame to insert the animation @param bUseCustomAnimRange If true we will load in a specific animation range from the anim sequence @param AnimStartRange  The start of the animation in the anim sequence frame rate that we load the animation from, used if bUseCustomAnimRange is true @param AnimEndRange The end of the animation in the anim sequence frame rate we load the animation from, used if bUseCustomAnimRange is true @param TimeUnit Unit for all frame and time values, either in display rate or tick resolution @param bKeyReduce If true do key reduction based upon Tolerance, if false don't @param Tolerance If reducing keys, tolerance about which keys will be removed, smaller tolerance, more keys usually. @param Interpolation The key interpolation type to set the keys, defaults to EMovieSceneKeyInterpolation::SmartAuto @param bResetControls If true will reset all controls to initial value on every frame @param bOntoSelectedControls if true will only load onto selected controls on the Control Rig, otherwise will load onto all controls that aren't masked out @return returns True if successful, False otherwise
- L267 _public prototype_ `static bool LoadAnimSequenceIntoControlRigSection(UMovieSceneSection* MovieSceneSection, UAnimSequence* AnimSequence, USkeletalMeshComponent* SkelMeshComp, FFrameNumber InStartFrame, EMovieSceneTimeUnit TimeUnit = EMovieSceneTimeUnit::DisplayRate, bool bKeyReduce = false, float Tolerance = 0.001f, EMovieSceneKeyInterpolation Interpolation = EMovieSceneKeyInterpolation::SmartAuto, bool bResetControls = true);` — `UE_DEPRECATED(5.6, "Use LoadAnimSequenceIntoControlRigSectionWithRange that takes UseCustomTimeRange")` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Sequencer Tools | Control Rig", meta = (DeprecatedFunction, DeprecationMessage = "Use LoadAnimSequenceIntoControlRigSectionWithRange that takes UseCustomTimeRange"))`
- L279 _public prototype_ `static bool ControlRigCopyVectorParameterCurvesToTransform(UMovieSceneControlRigParameterTrack* InTrack, const FName& InControlName, ERigControlType InType);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Sequencer Tools | Control Rig")` — Copy the internal parameter curves from vector control rig curves to transform curves, this is needed if a vector type is changed to transform type You would run this script first, resave, and then on next reload the curves should now show up on correct curves in the transform control @param InTrack Control Rig track to convert @param InControlName The name of the existing Vector type control @param InType The type of the control to convert, ERigControlType::Position,Rotator, or Scale @param returns true if at least one section was converted, false if nothing was converted
- L295 _public prototype_ `static bool BakeToControlRig(UWorld* World, ULevelSequence* LevelSequence, UClass* ControlRigClass, UAnimSeqExportOption* ExportOptions, bool bReduceKeys, float Tolerance, const FMovieSceneBindingProxy& Binding, bool bResetControls = true);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Sequencer Tools | Control Rig")` — Bake the current animation in the binding to a Control Rig track @param World The active world @param LevelSequence The LevelSequence we are baking @param ControlRigClass The class of the Control Rig @param ExportOptions Export options for creating an animation sequence @param bKeyReduce If true do key reduction based upon Tolerance, if false don't @param Tolerance If reducing keys, tolerance about which keys will be removed, smaller tolerance, more keys usually. @param Binding The binding upon which to bake @param bResetControls If true will reset all controls to initial value on every frame @return returns True if successful, False otherwise
- L308 _public prototype_ `static bool SmartReduce(FSmartReduceParams& ReduceParams, UMovieSceneSection* MovieSceneSection);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Sequencer Tools | Control Rig")` — Peform new Smart Reduce filter over the specified control rig section in the current open level sequence. Note existing functions like LoadAnimSequenceIntoControlRigSection and BakeToControlRig, will still use the old key reduction algorithm, so if you want to bake and then key reduce with the new function, set the bKeyReduce param as false with those functions, but then call this function after. @param ReduceParams Key reduction parameters @param MovieSceneSection The Control rig section we want to reduce @return returns True if successful, False otherwise
- L320 _public prototype_ `static bool BakeConstraint(UWorld* World, UTickableConstraint* Constraint, const TArray<FFrameNumber>& Frames, EMovieSceneTimeUnit TimeUnit = EMovieSceneTimeUnit::DisplayRate);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Sequencer Tools | Control Rig")` — Bake the constraint to keys based on the passed in frames. This will use the open sequencer to bake. See ConstraintsScriptingLibrary to get the list of available constraints @param World The active world @param Constraint The Constraint to bake. After baking it will be keyed to be inactive of the range of frames that are baked @param Frames The frames to bake, if the array is empty it will use the active time ranges of the constraint to determine where it should bake @param TimeUnit Unit for all frame and time values, either in display rate or tick resolution @return Returns True if successful, False otherwise
- L330 _public prototype_ `static bool BakeConstraints(UWorld* World, TArray<UTickableConstraint*>& InConstraints,const FBakingAnimationKeySettings& InSettings);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Sequencer Tools | Control Rig")` — Bake the constraint to keys based on the passed in settings. This will use the open sequencer to bake. See ConstraintsScriptingLibrary to get the list of available constraints @param World The active world @param InConstraints The Constraints tobake.  After baking they will be keyed to be inactive of the range of frames that are baked @param InSettings Settings to use for baking @return Returns True if successful, False otherwise
- L341 _public prototype_ `static UTickableConstraint* AddConstraint(UWorld* World, ETransformConstraintType InType, UTransformableHandle* InChild, UTransformableHandle* InParent, const bool bMaintainOffset);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Sequencer Tools | Control Rig")` — Add a constraint possibly adding to sequencer also if one is open. @param World The active world @param InType Type of constraint to create @param InChild The handle to the transormable to be constrainted @param InParent The handle to the parent of the constraint @param bMaintainOffset Whether to maintain offset between child and parent when setting the constraint @return Returns the constraint if created all nullptr if not
- L353 _public prototype_ `static bool GetConstraintKeys(UTickableConstraint* InConstraint, UMovieSceneSection* ConstraintSection,TArray<bool>& OutBools, TArray<FFrameNumber>& OutFrames, EMovieSceneTimeUnit TimeUnit = EMovieSceneTimeUnit::DisplayRate);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Sequencer Tools | Control Rig")` — Get the constraint keys for the specified constraint @param InConstraint The constraint to get @param ConstraintSection Section containing Cosntraint Key @param OutBools Array of whether or not it's active at the specified times @param OutFrames The Times for the keys @param TimeUnit Unit for the time params, either in display rate or tick resolution @return Returns true if we got the keys from this constraint
- L364 _public prototype_ `static bool SetConstraintActiveKey(UTickableConstraint* InConstraint, bool bActive, FFrameNumber InFrame, EMovieSceneTimeUnit TimeUnit = EMovieSceneTimeUnit::DisplayRate);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Sequencer Tools | Control Rig")` — Set the constraint active key in the current open Sequencer @param InConstraint The constraint to set the key @param bActive Whether or not it's active @param FrameTime Time to set the value @param TimeUnit Unit for the time params, either in display rate or tick resolution @return Returns true if we set the constraint to be the passed in value, false if not. We may not do so if the value is the same.
- L372 _public prototype_ `static TArray <UTickableConstraint*> GetConstraintsForHandle(UWorld* InWorld, const UTransformableHandle* InChild);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Sequencer Tools | Control Rig")` — Get all constraints for this object, which is described by a transformable handle @param InChild The handle to look for constraints controlling it @return Returns array of Constraints this handle is constrained to.
- L383 _public prototype_ `static bool MoveConstraintKey(UTickableConstraint* Constraint, UMovieSceneSection* ConstraintSection, FFrameNumber InTime, FFrameNumber InNewTime, EMovieSceneTimeUnit TimeUnit = EMovieSceneTimeUnit::DisplayRate);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Sequencer Tools | Control Rig")` — Move the constraint active key in the current open Sequencer @param InConstraint The constraint whose key to move @param ConstraintSection Section containing Cosntraint Key @param InTime Original time of the constraint key @param InNewTime New time for the constraint key @param TimeUnit Unit for the time params, either in display rate or tick resolution @return Will return false if function fails, for example if there is no key at this time it will fail, or if the new time is invalid it could fail also
- L393 _public prototype_ `static bool DeleteConstraintKey(UTickableConstraint* Constraint, UMovieSceneSection* ConstraintSection, FFrameNumber InTime, EMovieSceneTimeUnit TimeUnit = EMovieSceneTimeUnit::DisplayRate);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Sequencer Tools | Control Rig")` — Delete the Key for the Constraint at the specified time. @param InConstraint The constraint whose key to move @param ConstraintSection Section containing Cosntraint Key @param InTime Time to delete the constraint. @param TimeUnit Unit for the InTime, either in display rate or tick resolution @return Will return false if function fails,  for example if there is no key at this time it will fail.
- L402 _public prototype_ `static bool Compensate(UTickableConstraint* InConstraint, FFrameNumber InTime, EMovieSceneTimeUnit TimeUnit = EMovieSceneTimeUnit::DisplayRate);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Sequencer Tools | Control Rig")` — Compensate constraint at the specfied time @param InConstraint The constraint to compensate @param InTime Time to compensate @param TimeUnit Unit for the InTime, either in display rate or tick resolution @return Returns true if it can compensate
- L410 _public prototype_ `static bool CompensateAll(UTickableConstraint* InConstraint);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Sequencer Tools | Control Rig")` — Compensate constraint at all keys @param InConstraint The constraint to compensate @return Returns true if it can compensate
- L419 _public prototype_ `static bool TweenControlRig(ULevelSequence* LevelSequence, UControlRig* ControlRig, float TweenValue);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Sequencer Tools | Control Rig")` — Peform a Tween operation on the current active sequencer time(must be visible). @param LevelSequence The LevelSequence that's loaded in the editor @param ControlRig The Control Rig to tween. @param TweenValue The tween value to use, range from -1(blend to previous) to 1(blend to next)
- L428 _public prototype_ `static bool BlendValuesOnSelected(ULevelSequence* LevelSequence, EAnimToolBlendOperation BlendOperation, float BlendValue);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Sequencer Tools | Control Rig")` — Peform specified blend operation based upon selected keys in the curve editor or selected control rig controls @param LevelSequence The LevelSequence that's loaded in the editor @param EAnimToolBlendOperation The operation to perform @param BlendValue The blend value to use, range from -1(blend to previous) to 1(blend to next)
- L443 _public prototype_ `static bool SnapControlRig(ULevelSequence* LevelSequence, FFrameNumber StartFrame, FFrameNumber EndFrame, const FControlRigSnapperSelection& ChildrenToSnap, const FControlRigSnapperSelection& ParentToSnap, const UControlRigSnapSettings* SnapSettings, EMovieSceneTimeUnit TimeUnit = EMovieSceneTimeUnit::DisplayRate);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Sequencer Tools | Control Rig")` — Peform a Snap operation to snap the children to the parent. @param LevelSequence Active Sequence to snap @param StartFrame Beginning of the snap @param EndFrame End of the snap @param ChildrenToSnap The children objects that snap and get keys set onto. They need to live in an active Sequencer in the level editor @param ParentToSnap The parent object to snap relative to. If animated, it needs to live in an active Sequencer in the level editor @param SnapSettings Settings to use @param TimeUnit Unit for frame values, either in display rate or tick resolution @param Returns True if successful
- L455 _public prototype_ `static FTransform GetActorWorldTransform(ULevelSequence* LevelSequence,AActor* Actor, FFrameNumber Frame, EMovieSceneTimeUnit TimeUnit = EMovieSceneTimeUnit::DisplayRate);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Sequencer Tools | Control Rig")` — Get Actors World Transform at a specific time @param LevelSequence Active Sequence to get transform for @param Actor The actor @param Frame Time to get the transform @param TimeUnit Unit for frame values, either in display rate or tick resolution @return Returns World Transform
- L466 _public prototype_ `static TArray<FTransform> GetActorWorldTransforms(ULevelSequence* LevelSequence, AActor* Actor, const TArray<FFrameNumber>& Frames, EMovieSceneTimeUnit TimeUnit = EMovieSceneTimeUnit::DisplayRate);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Sequencer Tools | Control Rig")` — Get Actors World Transforms at specific times @param LevelSequence Active Sequence to get transform for @param Actor The actor @param Frames Times to get the transform @param TimeUnit Unit for frame values, either in display rate or tick resolution @return Returns World Transforms
- L478 _public prototype_ `static FTransform GetSkeletalMeshComponentWorldTransform(ULevelSequence* LevelSequence, USkeletalMeshComponent* SkeletalMeshComponent, FFrameNumber Frame, EMovieSceneTimeUnit TimeUnit = EMovieSceneTimeUnit::DisplayRate,FName ReferenceName = NAME_None);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Sequencer Tools | Control Rig")` — Get SkeletalMeshComponent World Transform at a specific time @param LevelSequence Active Sequence to get transform for @param SkeletalMeshComponent The SkeletalMeshComponent @param Frame Time to get the transform @param TimeUnit Unit for frame values, either in display rate or tick resolution @param ReferenceName Optional name of the referencer @return Returns World Transform
- L491 _public prototype_ `static TArray<FTransform> GetSkeletalMeshComponentWorldTransforms(ULevelSequence* LevelSequence, USkeletalMeshComponent* SkeletalMeshComponent, const TArray<FFrameNumber>& Frames, EMovieSceneTimeUnit TimeUnit = EMovieSceneTimeUnit::DisplayRate,FName ReferenceName = NAME_None);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Sequencer Tools | Control Rig")` — Get SkeletalMeshComponents World Transforms at specific times @param LevelSequence Active Sequence to get transform for @param SkeletalMeshComponent The SkeletalMeshComponent @param Frames Times to get the transform @param TimeUnit Unit for frame values, either in display rate or tick resolution @param ReferenceName Optional name of the referencer @return Returns World Transforms
- L499 _public prototype_ `static void SetInteraction(bool bIsInteracting);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Sequencer Tools | Control Rig")` — Sets the interaction state of the following SetLocalControlRig* functions (default is False). @param bIsInteracting If True the SetLocalControlRig* functions will be treated as if the ControlRig was interacting to react to interaction events.
- L513 _public prototype_ `static TArray<FArrayOfRigControlValues> GetControlValues(ULevelSequence* LevelSequence, UControlRig* ControlRig, const TArray<FName>& ControlNames, const TArray<FFrameNumber>& Frames, EMovieSceneTimeUnit TimeUnit = EMovieSceneTimeUnit::DisplayRate);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Sequencer Tools | Control Rig")` — Get an array per frame of specified control rig values for the specified control names. Use URigHierarchy::Get*FromControlValue functions to convert these FRigControlValue to Bool,Rotator,EulerTransform, etc.. @param LevelSequence Active Sequence to get values for, if not set will use the level sequence open in Sequencer @param ControlRig The ControlRig @param ControlNames Names of the Controls @param Frames Times to get the values @param TimeUnit Unit for frame values, either in display rate or tick resolution @return Returns an array per control containing control values for each frame. Note that that lhe length of this array may not be equal to the length of the Control Names array if there are invalid ControlNames
- L529 _public prototype_ `static TArray<FArrayOfRigControlTransforms> BatchGetControlTransforms(ULevelSequence* LevelSequence, UControlRig* ControlRig, const TArray<FName>& ControlNames, const TArray<FFrameNumber>& Frames, EControlRigTransformSpace Space, EMovieSceneTimeUnit TimeUnit = EMovieSceneTimeUnit::DisplayRate);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Sequencer Tools | Control Rig")` — Get an array per frame of specified control rig transforms for the specified control names. @param LevelSequence Active Sequence to get values for, if not set will use the level sequence open in Sequencer @param ControlRig The ControlRig @param ControlNames Names of the Controls @param Frames Times to get the values @param Space The space (Local or Global) the transforms will be in @param TimeUnit Unit for frame values, either in display rate or tick resolution @return Returns an array per control containing transforms for each frame. Note that that lhe length of this array may not be equal to the length of the ControlNames array if there are invalid Control names
- L544 _public prototype_ `static bool BatchSetControlTransforms(ULevelSequence* LevelSequence, UControlRig* ControlRig, const TArray<FArrayOfRigControlTransforms>& Controls, const TArray<FFrameNumber>& Frames, EControlRigTransformSpace Space, UMovieSceneControlRigParameterSection* OptionalSectionToSet = nullptr, EMovieSceneTimeUnit TimeUnit = EMovieSceneTimeUnit::DisplayRate);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Sequencer Tools | Control Rig")` — Set from Control transforms for different controls in the specified space at different frames @param LevelSequence Active Sequence to get values for, if not set will use the level sequence open in Sequencer @param ControlRig The ControlRig @param Controls The set of Controls with their transforms, the CachedElements may get set on this if not set @param Frames Times to get the values @param Space The space (Local or Global) the transforms will be in @param OptionalSectionToSet The section that should get the keys, if not set, it will use the current section to key setup on the track. @param TimeUnit Unit for frame values, either in display rate or tick resolution @return Returns true if successful, false otherwise
- L557 _public prototype_ `static FTransform GetControlRigWorldTransform(ULevelSequence* LevelSequence, UControlRig* ControlRig, FName ControlName, FFrameNumber Frame, EMovieSceneTimeUnit TimeUnit = EMovieSceneTimeUnit::DisplayRate);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Sequencer Tools | Control Rig")` — Get ControlRig Control's World Transform at a specific time @param LevelSequence Active Sequence to get transform for @param ControlRig The ControlRig @param ControlName Name of the Control @param Frame Time to get the transform @param TimeUnit Unit for frame values, either in display rate or tick resolution @return Returns World Transform
- L570 _public prototype_ `static TArray<FTransform> GetControlRigWorldTransforms(ULevelSequence* LevelSequence, UControlRig* ControlRig, FName ControlName, const TArray<FFrameNumber>& Frames, EMovieSceneTimeUnit TimeUnit = EMovieSceneTimeUnit::DisplayRate);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Sequencer Tools | Control Rig")` — Get ControlRig Control's World Transforms at specific times @param LevelSequence Active Sequence to get transform for @param ControlRig The ControlRig @param ControlName Name of the Control @param Frames Times to get the transform @param TimeUnit Unit for frame values, either in display rate or tick resolution @return Returns World Transforms
- L584 _public prototype_ `static void SetControlRigWorldTransform(ULevelSequence* LevelSequence, UControlRig* ControlRig, FName ControlName, FFrameNumber Frame, const FTransform& WorldTransform, EMovieSceneTimeUnit TimeUnit = EMovieSceneTimeUnit::DisplayRate, bool bSetKey = true);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Sequencer Tools | Control Rig")` — Set ControlRig Control's World Transform at a specific time @param LevelSequence Active Sequence to set transforms for. Must be loaded in Level Editor. @param ControlRig The ControlRig @param ControlName Name of the Control @param Frame Time to set the transform @param WorldTransform World Transform to set @param TimeUnit Unit for frame values, either in display rate or tick resolution @param bSetKey Whether or not to set a key.
- L597 _public prototype_ `static void SetControlRigWorldTransforms(ULevelSequence* LevelSequence, UControlRig* ControlRig, FName ControlName, const TArray<FFrameNumber>& Frames, const TArray<FTransform>& WorldTransforms, EMovieSceneTimeUnit TimeUnit = EMovieSceneTimeUnit::DisplayRate);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Sequencer Tools | Control Rig")` — Set ControlRig Control's World Transforms at a specific times. @param LevelSequence Active Sequence to set transforms for. Must be loaded in Level Editor. @param ControlRig The ControlRig @param ControlName Name of the Control @param Frames Times to set the transform @param WorldTransform World Transform to set @param TimeUnit Unit for frame values, either in display rate or tick resolution
- L610 _public prototype_ `static float GetLocalControlRigFloat(ULevelSequence* LevelSequence, UControlRig* ControlRig, FName ControlName, FFrameNumber Frame, EMovieSceneTimeUnit TimeUnit = EMovieSceneTimeUnit::DisplayRate);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Sequencer Tools | Control Rig")` — Get ControlRig Control's float value at a specific time @param LevelSequence Active Sequence to get value for @param ControlRig The ControlRig @param ControlName Name of the Control, should be a float control @param Frame Time to get the value @param TimeUnit Unit for frame values, either in display rate or tick resolution @return Returns Value at that time
- L623 _public prototype_ `static TArray<float> GetLocalControlRigFloats(ULevelSequence* LevelSequence, UControlRig* ControlRig, FName ControlName, const TArray<FFrameNumber>& Frames, EMovieSceneTimeUnit TimeUnit = EMovieSceneTimeUnit::DisplayRate);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Sequencer Tools | Control Rig")` — Get ControlRig Control's float values at specific times @param LevelSequence Active Sequence to get value for @param ControlRig The ControlRig @param ControlName Name of the Control, should be a float control @param Frames Times to get the values @param TimeUnit Unit for frame values, either in display rate or tick resolution @return Returns Values at those times
- L637 _public prototype_ `static void SetLocalControlRigFloat(ULevelSequence* LevelSequence, UControlRig* ControlRig, FName ControlName, FFrameNumber Frame, float Value, EMovieSceneTimeUnit TimeUnit = EMovieSceneTimeUnit::DisplayRate,bool bSetKey = true);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Sequencer Tools | Control Rig")` — Set ControlRig Control's float value at specific time @param LevelSequence Active Sequence to set value on @param ControlRig The ControlRig @param ControlName Name of the Control, should be a float control @param Frame Time to set the value @param Value The value to set @param TimeUnit Unit for frame values, either in display rate or tick resolution @param bSetKey If True set a key, if not just set the value
- L650 _public prototype_ `static void SetLocalControlRigFloats(ULevelSequence* LevelSequence, UControlRig* ControlRig, FName ControlName, const TArray<FFrameNumber>& Frames, const TArray<float> Values, EMovieSceneTimeUnit TimeUnit = EMovieSceneTimeUnit::DisplayRate);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Sequencer Tools | Control Rig")` — Set ControlRig Control's float values at specific times @param LevelSequence Active Sequence to set value on @param ControlRig The ControlRig @param ControlName Name of the Control, should be a float control @param Frames Times to set the values @param Values The values to set at those times @param TimeUnit Unit for frame values, either in display rate or tick resolution
- L663 _public prototype_ `static bool GetLocalControlRigBool(ULevelSequence* LevelSequence, UControlRig* ControlRig, FName ControlName, FFrameNumber Frame, EMovieSceneTimeUnit TimeUnit = EMovieSceneTimeUnit::DisplayRate);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Sequencer Tools | Control Rig")` — Get ControlRig Control's bool value at a specific time @param LevelSequence Active Sequence to get value for @param ControlRig The ControlRig @param ControlName Name of the Control, should be a bool control @param Frame Time to get the value @param TimeUnit Unit for frame values, either in display rate or tick resolution @return Returns Value at that time
- L676 _public prototype_ `static TArray<bool> GetLocalControlRigBools(ULevelSequence* LevelSequence, UControlRig* ControlRig, FName ControlName, const TArray<FFrameNumber>& Frames, EMovieSceneTimeUnit TimeUnit = EMovieSceneTimeUnit::DisplayRate);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Sequencer Tools | Control Rig")` — Get ControlRig Control's bool values at specific times @param LevelSequence Active Sequence to get value for @param ControlRig The ControlRig @param ControlName Name of the Control, should be a bool control @param Frames Times to get the values @param TimeUnit Unit for frame values, either in display rate or tick resolution @return Returns Values at those times
- L690 _public prototype_ `static void SetLocalControlRigBool(ULevelSequence* LevelSequence, UControlRig* ControlRig, FName ControlName, FFrameNumber Frame, bool Value, EMovieSceneTimeUnit TimeUnit = EMovieSceneTimeUnit::DisplayRate, bool bSetKey = true);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Sequencer Tools | Control Rig")` — Set ControlRig Control's bool value at specific time @param LevelSequence Active Sequence to set value on @param ControlRig The ControlRig @param ControlName Name of the Control, should be a bool control @param Frame Time to set the value @param Value The value to set @param TimeUnit Unit for frame values, either in display rate or tick resolution @param bSetKey If True set a key, if not just set the value
- L703 _public prototype_ `static void SetLocalControlRigBools(ULevelSequence* LevelSequence, UControlRig* ControlRig, FName ControlName, const TArray<FFrameNumber>& Frames, const TArray<bool> Values, EMovieSceneTimeUnit TimeUnit = EMovieSceneTimeUnit::DisplayRate);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Sequencer Tools | Control Rig")` — Set ControlRig Control's bool values at specific times @param LevelSequence Active Sequence to set value on @param ControlRig The ControlRig @param ControlName Name of the Control, should be a bool control @param Frames Times to set the values @param Values The values to set at those times @param TimeUnit Unit for frame values, either in display rate or tick resolution
- L716 _public prototype_ `static int32 GetLocalControlRigInt(ULevelSequence* LevelSequence, UControlRig* ControlRig, FName ControlName, FFrameNumber Frame, EMovieSceneTimeUnit TimeUnit = EMovieSceneTimeUnit::DisplayRate);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Sequencer Tools | Control Rig")` — Get ControlRig Control's integer value at a specific time @param LevelSequence Active Sequence to get value for @param ControlRig The ControlRig @param ControlName Name of the Control, should be a integer control @param Frame Time to get the value @param TimeUnit Unit for frame values, either in display rate or tick resolution @return Returns Value at that time
- L729 _public prototype_ `static TArray<int32> GetLocalControlRigInts(ULevelSequence* LevelSequence, UControlRig* ControlRig, FName ControlName, const TArray<FFrameNumber>& Frames, EMovieSceneTimeUnit TimeUnit = EMovieSceneTimeUnit::DisplayRate);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Sequencer Tools | Control Rig")` — Get ControlRig Control's integer values at specific times @param LevelSequence Active Sequence to get value for @param ControlRig The ControlRig @param ControlName Name of the Control, should be a intteger control @param Frames Times to get the values @param TimeUnit Unit for frame values, either in display rate or tick resolution @return Returns Values at those times
- L743 _public prototype_ `static void SetLocalControlRigInt(ULevelSequence* LevelSequence, UControlRig* ControlRig, FName ControlName, FFrameNumber Frame, int32 Value, EMovieSceneTimeUnit TimeUnit = EMovieSceneTimeUnit::DisplayRate,bool bSetKey = true);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Sequencer Tools | Control Rig")` — Set ControlRig Control's int value at specific time @param LevelSequence Active Sequence to set value on @param ControlRig The ControlRig @param ControlName Name of the Control, should be a int control @param Frame Time to set the value @param Value The value to set @param TimeUnit Unit for frame values, either in display rate or tick resolution @param bSetKey If True set a key, if not just set the value
- L757 _public prototype_ `static void SetLocalControlRigInts(ULevelSequence* LevelSequence, UControlRig* ControlRig, FName ControlName, const TArray<FFrameNumber>& Frames, const TArray<int32> Values, EMovieSceneTimeUnit TimeUnit = EMovieSceneTimeUnit::DisplayRate);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Sequencer Tools | Control Rig")` — Set ControlRig Control's int values at specific times @param LevelSequence Active Sequence to set value on @param ControlRig The ControlRig @param ControlName Name of the Control, should be a int control @param Frames Times to set the values @param Values The values to set at those times @param TimeUnit Unit for frame values, either in display rate or tick resolution
- L770 _public prototype_ `static FVector2D GetLocalControlRigVector2D(ULevelSequence* LevelSequence, UControlRig* ControlRig, FName ControlName, FFrameNumber Frame, EMovieSceneTimeUnit TimeUnit = EMovieSceneTimeUnit::DisplayRate);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Sequencer Tools | Control Rig")` — Get ControlRig Control's Vector2D value at a specific time @param LevelSequence Active Sequence to get value for @param ControlRig The ControlRig @param ControlName Name of the Control, should be a Vector2D control @param Frame Time to get the value @param TimeUnit Unit for frame values, either in display rate or tick resolution @return Returns Value at that time
- L783 _public prototype_ `static TArray<FVector2D> GetLocalControlRigVector2Ds(ULevelSequence* LevelSequence, UControlRig* ControlRig, FName ControlName, const TArray<FFrameNumber>& Frames, EMovieSceneTimeUnit TimeUnit = EMovieSceneTimeUnit::DisplayRate);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Sequencer Tools | Control Rig")` — Get ControlRig Control's Vector2D values at specific times @param LevelSequence Active Sequence to get value for @param ControlRig The ControlRig @param ControlName Name of the Control, should be a Vector2D control @param Frames Times to get the values @param TimeUnit Unit for frame values, either in display rate or tick resolution @return Returns Values at those times
- L797 _public prototype_ `static void SetLocalControlRigVector2D(ULevelSequence* LevelSequence, UControlRig* ControlRig, FName ControlName, FFrameNumber Frame, FVector2D Value, EMovieSceneTimeUnit TimeUnit = EMovieSceneTimeUnit::DisplayRate,bool bSetKey = true);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Sequencer Tools | Control Rig")` — Set ControlRig Control's Vector2D value at specific time @param LevelSequence Active Sequence to set value on @param ControlRig The ControlRig @param ControlName Name of the Control, should be a Vector2D control @param Frame Time to set the value @param Value The value to set @param TimeUnit Unit for frame values, either in display rate or tick resolution @param bSetKey If True set a key, if not just set the value
- L811 _public prototype_ `static void SetLocalControlRigVector2Ds(ULevelSequence* LevelSequence, UControlRig* ControlRig, FName ControlName, const TArray<FFrameNumber>& Frames, const TArray<FVector2D> Values, EMovieSceneTimeUnit TimeUnit = EMovieSceneTimeUnit::DisplayRate);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Sequencer Tools | Control Rig")` — Set ControlRig Control's Vector2D values at specific times @param LevelSequence Active Sequence to set value on @param ControlRig The ControlRig @param ControlName Name of the Control, should be a Vector2D control @param Frames Times to set the values @param Values The values to set at those times @param TimeUnit Unit for frame values, either in display rate or tick resolution
- L824 _public prototype_ `static FVector GetLocalControlRigPosition(ULevelSequence* LevelSequence, UControlRig* ControlRig, FName ControlName, FFrameNumber Frame, EMovieSceneTimeUnit TimeUnit = EMovieSceneTimeUnit::DisplayRate);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Sequencer Tools | Control Rig")` — Get ControlRig Control's Position value at a specific time @param LevelSequence Active Sequence to get value for @param ControlRig The ControlRig @param ControlName Name of the Control, should be a Position control @param Frame Time to get the value @param TimeUnit Unit for frame values, either in display rate or tick resolution @return Returns Value at that time
- L837 _public prototype_ `static TArray<FVector> GetLocalControlRigPositions(ULevelSequence* LevelSequence, UControlRig* ControlRig, FName ControlName, const TArray<FFrameNumber>& Frames, EMovieSceneTimeUnit TimeUnit = EMovieSceneTimeUnit::DisplayRate);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Sequencer Tools | Control Rig")` — Get ControlRig Control's Position values at specific times @param LevelSequence Active Sequence to get value for @param ControlRig The ControlRig @param ControlName Name of the Control, should be a Position control @param Frames Times to get the values @param TimeUnit Unit for frame values, either in display rate or tick resolution @return Returns Values at those times
- L851 _public prototype_ `static void SetLocalControlRigPosition(ULevelSequence* LevelSequence, UControlRig* ControlRig, FName ControlName, FFrameNumber Frame, FVector Value, EMovieSceneTimeUnit TimeUnit = EMovieSceneTimeUnit::DisplayRate, bool bSetKey = true);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Sequencer Tools | Control Rig")` — Set ControlRig Control's Position value at specific time @param LevelSequence Active Sequence to set value on @param ControlRig The ControlRig @param ControlName Name of the Control, should be a Position control @param Frame Time to set the value @param Value The value to set @param TimeUnit Unit for frame values, either in display rate or tick resolution @param bSetKey If True set a key, if not just set the value
- L864 _public prototype_ `static void SetLocalControlRigPositions(ULevelSequence* LevelSequence, UControlRig* ControlRig, FName ControlName, const TArray<FFrameNumber>& Frames, const TArray<FVector> Values, EMovieSceneTimeUnit TimeUnit = EMovieSceneTimeUnit::DisplayRate);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Sequencer Tools | Control Rig")` — Set ControlRig Control's Position values at specific times @param LevelSequence Active Sequence to set value on @param ControlRig The ControlRig @param ControlName Name of the Control, should be a Position control @param Frames Times to set the values @param Values The values to set at those times @param TimeUnit Unit for frame values, either in display rate or tick resolution
- L877 _public prototype_ `static FRotator GetLocalControlRigRotator(ULevelSequence* LevelSequence, UControlRig* ControlRig, FName ControlName, FFrameNumber Frame, EMovieSceneTimeUnit TimeUnit = EMovieSceneTimeUnit::DisplayRate);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Sequencer Tools | Control Rig")` — Get ControlRig Control's Rotator value at a specific time @param LevelSequence Active Sequence to get value for @param ControlRig The ControlRig @param ControlName Name of the Control, should be a Rotator control @param Frame Time to get the value @param TimeUnit Unit for frame values, either in display rate or tick resolution @return Returns Value at that time
- L890 _public prototype_ `static TArray<FRotator> GetLocalControlRigRotators(ULevelSequence* LevelSequence, UControlRig* ControlRig, FName ControlName, const TArray<FFrameNumber>& Frames, EMovieSceneTimeUnit TimeUnit = EMovieSceneTimeUnit::DisplayRate);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Sequencer Tools | Control Rig")` — Get ControlRig Control's Rotator values at specific times @param LevelSequence Active Sequence to get value for @param ControlRig The ControlRig @param ControlName Name of the Control, should be a Rotator control @param Frames Times to get the values @param TimeUnit Unit for frame values, either in display rate or tick resolution @return Returns Values at those times
- L904 _public prototype_ `static void SetLocalControlRigRotator(ULevelSequence* LevelSequence, UControlRig* ControlRig, FName ControlName, FFrameNumber Frame, FRotator Value, EMovieSceneTimeUnit TimeUnit = EMovieSceneTimeUnit::DisplayRate, bool bSetKey = true);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Sequencer Tools | Control Rig")` — Set ControlRig Control's Rotator value at specific time @param LevelSequence Active Sequence to set value on @param ControlRig The ControlRig @param ControlName Name of the Control, should be a Rotator control @param Frame Time to set the value @param Value The value to set @param TimeUnit Unit for frame values, either in display rate or tick resolution @param bSetKey If True set a key, if not just set the value
- L917 _public prototype_ `static void SetLocalControlRigRotators(ULevelSequence* LevelSequence, UControlRig* ControlRig, FName ControlName, const TArray<FFrameNumber>& Frames, const TArray<FRotator> Values, EMovieSceneTimeUnit TimeUnit = EMovieSceneTimeUnit::DisplayRate);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Sequencer Tools | Control Rig")` — Set ControlRig Control's Rotator values at specific times @param LevelSequence Active Sequence to set value on @param ControlRig The ControlRig @param ControlName Name of the Control, should be a Rotator control @param Frames Times to set the values @param Values The values to set at those times @param TimeUnit Unit for frame values, either in display rate or tick resolution
- L930 _public prototype_ `static FVector GetLocalControlRigScale(ULevelSequence* LevelSequence, UControlRig* ControlRig, FName ControlName, FFrameNumber Frame, EMovieSceneTimeUnit TimeUnit = EMovieSceneTimeUnit::DisplayRate);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Sequencer Tools | Control Rig")` — Get ControlRig Control's Scale value at a specific time @param LevelSequence Active Sequence to get value for @param ControlRig The ControlRig @param ControlName Name of the Control, should be a Scale control @param Frame Time to get the value @param TimeUnit Unit for frame values, either in display rate or tick resolution @return Returns Value at that time
- L943 _public prototype_ `static TArray<FVector> GetLocalControlRigScales(ULevelSequence* LevelSequence, UControlRig* ControlRig, FName ControlName, const TArray<FFrameNumber>& Frames, EMovieSceneTimeUnit TimeUnit = EMovieSceneTimeUnit::DisplayRate);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Sequencer Tools | Control Rig")` — Get ControlRig Control's Scale values at specific times @param LevelSequence Active Sequence to get value for @param ControlRig The ControlRig @param ControlName Name of the Control, should be a Scale control @param Frames Times to get the values @param TimeUnit Unit for frame values, either in display rate or tick resolution @return Returns Values at those times
- L957 _public prototype_ `static void SetLocalControlRigScale(ULevelSequence* LevelSequence, UControlRig* ControlRig, FName ControlName, FFrameNumber Frame, FVector Value, EMovieSceneTimeUnit TimeUnit = EMovieSceneTimeUnit::DisplayRate, bool bSetKey = true);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Sequencer Tools | Control Rig")` — Set ControlRig Control's Scale value at specific time @param LevelSequence Active Sequence to set value on @param ControlRig The ControlRig @param ControlName Name of the Control, should be a Scale control @param Frame Time to set the value @param Value The value to set @param TimeUnit Unit for frame values, either in display rate or tick resolution @param bSetKey If True set a key, if not just set the value
- L970 _public prototype_ `static void SetLocalControlRigScales(ULevelSequence* LevelSequence, UControlRig* ControlRig, FName ControlName, const TArray<FFrameNumber>& Frames, const TArray<FVector> Values, EMovieSceneTimeUnit TimeUnit = EMovieSceneTimeUnit::DisplayRate);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Sequencer Tools | Control Rig")` — Set ControlRig Control's Scale values at specific times @param LevelSequence Active Sequence to set value on @param ControlRig The ControlRig @param ControlName Name of the Control, should be a Scale control @param Frames Times to set the values @param Values The values to set at those times @param TimeUnit Unit for frame values, either in display rate or tick resolution
- L984 _public prototype_ `static FEulerTransform GetLocalControlRigEulerTransform(ULevelSequence* LevelSequence, UControlRig* ControlRig, FName ControlName, FFrameNumber Frame, EMovieSceneTimeUnit TimeUnit = EMovieSceneTimeUnit::DisplayRate);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Sequencer Tools | Control Rig")` — Get ControlRig Control's EulerTransform value at a specific time @param LevelSequence Active Sequence to get value for @param ControlRig The ControlRig @param ControlName Name of the Control, should be a EulerTransfom control @param Frame Time to get the value @param TimeUnit Unit for frame values, either in display rate or tick resolution @return Returns Value at that time
- L997 _public prototype_ `static TArray<FEulerTransform> GetLocalControlRigEulerTransforms(ULevelSequence* LevelSequence, UControlRig* ControlRig, FName ControlName, const TArray<FFrameNumber>& Frames, EMovieSceneTimeUnit TimeUnit = EMovieSceneTimeUnit::DisplayRate);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Sequencer Tools | Control Rig")` — Get ControlRig Control's EulerTransform values at specific times @param LevelSequence Active Sequence to get value for @param ControlRig The ControlRig @param ControlName Name of the Control, should be a EulerTransform control @param Frames Times to get the values @param TimeUnit Unit for frame values, either in display rate or tick resolution @return Returns Values at those times
- L1011 _public prototype_ `static void SetLocalControlRigEulerTransform(ULevelSequence* LevelSequence, UControlRig* ControlRig, FName ControlName, FFrameNumber Frame, FEulerTransform Value, EMovieSceneTimeUnit TimeUnit = EMovieSceneTimeUnit::DisplayRate, bool bSetKey = true);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Sequencer Tools | Control Rig")` — Set ControlRig Control's EulerTransform value at specific time @param LevelSequence Active Sequence to set value on @param ControlRig The ControlRig @param ControlName Name of the Control, should be a EulerTransform control @param Frame Time to set the value @param Value The value to set @param TimeUnit Unit for frame values, either in display rate or tick resolution @param bSetKey If True set a key, if not just set the value
- L1024 _public prototype_ `static void SetLocalControlRigEulerTransforms(ULevelSequence* LevelSequence, UControlRig* ControlRig, FName ControlName, const TArray<FFrameNumber>& Frames, const TArray<FEulerTransform> Values, EMovieSceneTimeUnit TimeUnit = EMovieSceneTimeUnit::DisplayRate);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Sequencer Tools | Control Rig")` — Set ControlRig Control's EulerTransform values at specific times @param LevelSequence Active Sequence to set value on @param ControlRig The ControlRig @param ControlName Name of the Control, should be a EulerTransform control @param Frames Times to set the values @param Values The values to set at those times @param TimeUnit Unit for frame values, either in display rate or tick resolution
- L1037 _public prototype_ `static FTransformNoScale GetLocalControlRigTransformNoScale(ULevelSequence* LevelSequence, UControlRig* ControlRig, FName ControlName, FFrameNumber Frame, EMovieSceneTimeUnit TimeUnit = EMovieSceneTimeUnit::DisplayRate);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Sequencer Tools | Control Rig")` — Get ControlRig Control's TransformNoScale value at a specific time @param LevelSequence Active Sequence to get value for @param ControlRig The ControlRig @param ControlName Name of the Control, should be a TransformNoScale control @param Frame Time to get the value @param TimeUnit Unit for frame values, either in display rate or tick resolution @return Returns Value at that time
- L1050 _public prototype_ `static TArray<FTransformNoScale> GetLocalControlRigTransformNoScales(ULevelSequence* LevelSequence, UControlRig* ControlRig, FName ControlName, const TArray<FFrameNumber>& Frames, EMovieSceneTimeUnit TimeUnit = EMovieSceneTimeUnit::DisplayRate);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Sequencer Tools | Control Rig")` — Get ControlRig Control's TransformNoScale values at specific times @param LevelSequence Active Sequence to get value for @param ControlRig The ControlRig @param ControlName Name of the Control, should be a TransformNoScale control @param Frames Times to get the values @param TimeUnit Unit for frame values, either in display rate or tick resolution @return Returns Values at those times
- L1064 _public prototype_ `static void SetLocalControlRigTransformNoScale(ULevelSequence* LevelSequence, UControlRig* ControlRig, FName ControlName, FFrameNumber Frame, FTransformNoScale Value, EMovieSceneTimeUnit TimeUnit = EMovieSceneTimeUnit::DisplayRate, bool bSetKey = true);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Sequencer Tools | Control Rig")` — Set ControlRig Control's TransformNoScale value at specific time @param LevelSequence Active Sequence to set value on @param ControlRig The ControlRig @param ControlName Name of the Control, should be a TransformNoScale control @param Frame Time to set the value @param Value The value to set @param TimeUnit Unit for frame values, either in display rate or tick resolution @param bSetKey If True set a key, if not just set the value
- L1077 _public prototype_ `static void SetLocalControlRigTransformNoScales(ULevelSequence* LevelSequence, UControlRig* ControlRig, FName ControlName, const TArray<FFrameNumber>& Frames, const TArray<FTransformNoScale> Values, EMovieSceneTimeUnit TimeUnit = EMovieSceneTimeUnit::DisplayRate);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Sequencer Tools | Control Rig")` — Set ControlRig Control's TransformNoScale values at specific times @param LevelSequence Active Sequence to set value on @param ControlRig The ControlRig @param ControlName Name of the Control, should be a TransformNoScale control @param Frames Times to set the values @param Values The values to set at those times @param TimeUnit Unit for frame values, either in display rate or tick resolution
- L1090 _public prototype_ `static FTransform GetLocalControlRigTransform(ULevelSequence* LevelSequence, UControlRig* ControlRig, FName ControlName, FFrameNumber Frame, EMovieSceneTimeUnit TimeUnit = EMovieSceneTimeUnit::DisplayRate);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Sequencer Tools | Control Rig")` — Get ControlRig Control's Transform value at a specific time @param LevelSequence Active Sequence to get value for @param ControlRig The ControlRig @param ControlName Name of the Control, should be a Transform control @param Frame Time to get the value @param TimeUnit Unit for frame values, either in display rate or tick resolution @return Returns Value at that time
- L1103 _public prototype_ `static TArray<FTransform> GetLocalControlRigTransforms(ULevelSequence* LevelSequence, UControlRig* ControlRig, FName ControlName, const TArray<FFrameNumber>& Frames, EMovieSceneTimeUnit TimeUnit = EMovieSceneTimeUnit::DisplayRate);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Sequencer Tools | Control Rig")` — Get ControlRig Control's Transform values at specific times @param LevelSequence Active Sequence to get value for @param ControlRig The ControlRig @param ControlName Name of the Control, should be a Transform control @param Frames Times to get the values @param TimeUnit Unit for frame values, either in display rate or tick resolution @return Returns Values at those times
- L1117 _public prototype_ `static void SetLocalControlRigTransform(ULevelSequence* LevelSequence, UControlRig* ControlRig, FName ControlName, FFrameNumber Frame, FTransform Value, EMovieSceneTimeUnit TimeUnit = EMovieSceneTimeUnit::DisplayRate, bool bSetKey = true);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Sequencer Tools | Control Rig")` — Set ControlRig Control's Transform value at specific time @param LevelSequence Active Sequence to set value on @param ControlRig The ControlRig @param ControlName Name of the Control, should be a Transform control @param Frame Time to set the value @param Value The value to set @param TimeUnit Unit for frame values, either in display rate or tick resolution @param bSetKey If True set a key, if not just set the value
- L1130 _public prototype_ `static void SetLocalControlRigTransforms(ULevelSequence* LevelSequence, UControlRig* ControlRig, FName ControlName, const TArray<FFrameNumber>& Frames, const TArray<FTransform> Values, EMovieSceneTimeUnit TimeUnit = EMovieSceneTimeUnit::DisplayRate);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Sequencer Tools | Control Rig")` — Set ControlRig Control's Transform values at specific times @param LevelSequence Active Sequence to set value on @param ControlRig The ControlRig @param ControlName Name of the Control, should be a Transform control @param Frames Times to set the values @param Values The values to set at those times @param TimeUnit Unit for frame values, either in display rate or tick resolution
- L1145 _public prototype_ `static bool ImportFBXToControlRigTrack(UWorld* World, ULevelSequence* InSequence, UMovieSceneControlRigParameterTrack* InTrack, UMovieSceneControlRigParameterSection* InSection, const TArray<FString>& SelectedControlRigNames, UMovieSceneUserImportFBXControlRigSettings* ImportFBXControlRigSettings, const FString& ImportFilename);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Sequencer Tools | FBX")` — Import FBX onto a control rig with the specified track and section @param InWorld World to import to @param InSequence Sequence to import @param InTrack Track to import onto @param InSection Section to import onto, may be null in which case we use the track's section to key @param SelectedControlRigNames  List of selected control rig names. Will use them if  ImportFBXControlRigSettings->bImportOntoSelectedControls is true @param ImportFBXControlRigSettings Settings to control import. @param InImportFileName Path to fbx file to create
- L1152 _public prototype_ `static bool ExportFBXFromControlRigSection(ULevelSequence* Sequence, const UMovieSceneControlRigParameterSection* Section, const UMovieSceneUserExportFBXControlRigSettings* ExportFBXControlRigSettings);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Sequencer Tools | FBX")` — Exports an FBX from the given control rig section.
- L1164 _public prototype_ `static bool CollapseControlRigAnimLayers(ULevelSequence* InSequence,UMovieSceneControlRigParameterTrack* InTrack, bool bKeyReduce = false, float Tolerance = 0.001f);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Sequencer Tools | Control Rig")` — Collapse and bake all sections and layers on a control rig track to just one section. @param InSequence Sequence that has track to collapse @param InTrack Track for layers to collapse @param bKeyReduce If true do key reduction based upon Tolerance, if false don't @param Tolerance If reducing keys, tolerance about which keys will be removed, smaller tolerance, more keys usually.
- L1174 _public prototype_ `static bool CollapseControlRigAnimLayersWithSettings(ULevelSequence* InSequence, UMovieSceneControlRigParameterTrack* InTrack, const FBakingAnimationKeySettings& InSettings);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Sequencer Tools | Control Rig")` — Collapse and bake all sections and layers on a control rig track to just one section using passed in settings. @param InSequence Sequence that has track to collapse @param InTrack Track for layers to collapse @param InSettings Settings that determine how to collapse
- L1183 _public prototype_ `static bool DeleteTimeWarp(UMovieSceneControlRigParameterSection* InSection);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Sequencer Tools | Control Rig")` — Remove any timewarp from section @param InSection Section to remove time warp from @return true if successful false otherwise
- L1192 _public prototype_ `static bool BakeTimeWarp(UMovieSceneControlRigParameterSection* InSection);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Sequencer Tools | Control Rig")` — Bake any timewarp from section @param InSection Section to bake time warp from @return true if successful false otherwise
- L1204 _public prototype_ `static UMovieSceneScriptingChannel* GetSpaceChannel(UMovieSceneSequence* InSequence, UControlRig* InControlRig, FName InControlName, bool bCreateIfNeeded = true);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Sequencer Tools | Control Rig")` — Get the space channel for the specified control rig and control name. Will create it if needed. Note spaces will always live on the first section. @param InSequence Sequence that to get space channel @param InControlRig ControlRig with the Control @param InControlName Name of control to have space channel @param bCreateIfNeeded Create the channel if it doesn't exist @return return the space channel if one exists or was created based upon bCreateIfNeeded
- L1211 _public prototype_ `static FRigElementKey GetDefaultParentKey();` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Sequencer Tools | Control Rig")` — Get the default parent key, can be used a parent space.
- L1218 _public prototype_ `static FRigElementKey GetWorldSpaceReferenceKey();` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Sequencer Tools | Control Rig")` — Get the default world space key, can be used a world space.
- L1231 _public prototype_ `static bool SetControlRigSpace(ULevelSequence* InSequence, UControlRig* InControlRig, FName InControlName, const FRigElementKey& InSpaceKey, FFrameNumber InTime, EMovieSceneTimeUnit TimeUnit = EMovieSceneTimeUnit::DisplayRate);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Sequencer Tools | Control Rig")` — Set the a key for the Control Rig Space for the Control at the specified time. If space is the same as the current no key will be set. @param InSequence Sequence to set the space @param InControlRig ControlRig with the Control @param InControlName The name of the Control @param InSpaceKey  The new space for the Control @param InTime Time to change the space. @param TimeUnit Unit for the InTime, either in display rate or tick resolution
- L1241 _public prototype_ `static bool BakeControlRigSpace(ULevelSequence* InSequence, UControlRig* InControlRig, const TArray<FName>& InControlNames, FRigSpacePickerBakeSettings InSettings, EMovieSceneTimeUnit TimeUnit = EMovieSceneTimeUnit::DisplayRate);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Sequencer Tools | Control Rig")` — Bake specified Control Rig Controls to a specified Space based upon the current settings @param InSequence Sequence to bake @param InControlRig ControlRig to bake @param InControlNames The name of the Controls to bake @param InSettings  The settings for the bake, e.g, how long to bake, to key reduce etc. @param TimeUnit Unit for the start and end times in the InSettings parameter.
- L1250 _public prototype_ `static bool SpaceCompensate(UControlRig* InControlRig, FFrameNumber InTime, EMovieSceneTimeUnit TimeUnit = EMovieSceneTimeUnit::DisplayRate);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Sequencer Tools | Control Rig")` — Perform compensation for any spaces at the specified time for the specified control rig @param InControlRig Control Rig to compensate @param InTime  The time to look for a space key to compensate @param TimeUnit Unit for the InTime @return Will return false if function fails
- L1256 _public prototype_ `static bool SpaceCompensateAll(UControlRig* InControlRig);` — Perform compensation for all spaces for the specified control rig @param InControlRig Control Rig to compensate @return Will return false if function fails
- L1268 _public prototype_ `static bool DeleteControlRigSpace(ULevelSequence* InSequence, UControlRig* InControlRig, FName InControlName, FFrameNumber InTime, EMovieSceneTimeUnit TimeUnit = EMovieSceneTimeUnit::DisplayRate);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Sequencer Tools | Control Rig")` — Delete the Control Rig Space Key for the Control at the specified time. This will delete any attached Control Rig keys at this time and will perform any needed compensation to the new space. @param InSequence Sequence to set the space @param InControlRig ControlRig with the Control @param InControlName The name of the Control @param InTime Time to delete the space. @param TimeUnit Unit for the InTime, either in display rate or tick resolution @return Will return false if function fails,  for example if there is no key at this time it will fail.
- L1281 _public prototype_ `static bool MoveControlRigSpace(ULevelSequence* InSequence, UControlRig* InControlRig, FName InControlName, FFrameNumber InTime, FFrameNumber InNewTime, EMovieSceneTimeUnit TimeUnit = EMovieSceneTimeUnit::DisplayRate);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Sequencer Tools | Control Rig")` — Move the Control Rig Space Key for the Control at the specified time to the new time. This will also move any Control Rig keys at this space switch boundary. @param InSequence Sequence to set the space @param InControlRig ControlRig with the Control @param InControlName The name of the Control @param InTime Original time of the space key @param InNewTime New time for the space key @param TimeUnit Unit for the time params, either in display rate or tick resolution @return Will return false if function fails, for example if there is no key at this time it will fail, or if the new time is invalid it could fail also
- L1289 _public prototype_ `static bool ReplaceControlRig(UMovieSceneTrack* InControlRigTrack, UControlRig* NewControlRig);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Sequencer Tools | Control Rig")` — Replace the Control Rig on the track with a new Control Rig. Note it will now be owned by the track @param InControlRigTrack ControlRigTrack to replace @param NewControlRig ControlRig to put on track @return Return true if the function succeeds, false if it doesn't
- L1299 _public prototype_ `static bool RenameControlRigControlChannels(ULevelSequence* InSequence, UControlRig* InControlRig, const TArray<FName>& InOldControlNames, const TArray<FName>& InNewControlNames);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Sequencer Tools | Control Rig")` — Rename the Control Rig Channels in Sequencer to the specified new control names, which should be present on the Control Rig @param InSequence Sequence to rename controls @param InControlRig ControlRig to rename controls @param InOldControlNames The name of the old Control Rig Control Channels to change. Will be replaced by the corresponding name in the InNewControlNames array @param InNewControlNames  The name of the new Control Rig Channels @return Return true if the function succeeds, false if it doesn't which can happen if the name arrays don't match in size or any of the new Control Names aren't valid
- L1303 _public prototype_ `static bool GetControlsMask(UMovieSceneSection* InSection, FName ControlName);` — `UFUNCTION(BlueprintPure, Category = "Editor Scripting | Sequencer Tools | Control Rig")` — Get the controls mask for the given ControlName
- L1307 _public prototype_ `static void SetControlsMask(UMovieSceneSection* InSection, const TArray<FName>& ControlNames, bool bVisible);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Sequencer Tools | Control Rig")` — Set the controls mask for the given ControlNames
- L1311 _public prototype_ `static void ClearSelection();` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Sequencer Tools | Control Rig")` — Clear Selection
- L1315 _public prototype_ `static void FrameSelection();` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Sequencer Tools | Control Rig")` — Frame to current Control Selection
- L1319 _public prototype_ `static void SelectMirroredControls();` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Sequencer Tools | Control Rig")` — Select Mirrored Controls on Current Selection
- L1323 _public prototype_ `static void AddMirroredControlsToSelection();` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Sequencer Tools | Control Rig")` — Select Mirrored Controls on Current Selection, keeping current selection
- L1327 _public prototype_ `static void MirrorSelectedControls();` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Sequencer Tools | Control Rig")` — Put Selected Controls To Mirrored Pose
- L1331 _public prototype_ `static void MirrorUnselectedControls();` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Sequencer Tools | Control Rig")` — Put Unselected Controls To Mirrored Pose
- L1338 _public prototype_ `static void ZeroTransforms(bool bSelectionOnly, bool bIncludeChannels);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Sequencer Tools | Control Rig")` — Reset Transforms to default values, usually zero values but which may not be zero if initial values are present @param bSelectionOnly Only onto rigs with selected controls @param bIncludeChannels Include channels in addition to parent controls
- L1345 _public prototype_ `static void InvertInputPose(bool bSelectionOnly, bool bIncludeChannels);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Sequencer Tools | Control Rig")` — Invert Input Pose, this will set layered controls rigs to default pose, for non-layered same as ZeroTransforms @param bSelectionOnly Only onto rigs with selected controls @param bIncludeChannels Include channels in addition to parent controls
- L1349 _public prototype_ `static void OpenPoseLibraryTab();` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Sequencer Tools | Control Rig")` — Opens the Control Rig Pose Library panel.
- L1353 _public prototype_ `static void ClosePoseLibraryTab();` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Sequencer Tools | Control Rig")` — Closes the Control Rig Pose Library panel.
- L1359 _public prototype_ `static void KeyControls(UMovieSceneSection* InSection, const TArray<FName>& ControlNames);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Sequencer Tools | Control Rig")` — Key Controls On Section at the current frame
- L1365 _public prototype_ `static void KeyControlsAtFrames(UMovieSceneSection* InSection, const TArray<FName>& ControlNames , const TArray<FFrameNumber>& AtTimes, EMovieSceneTimeUnit TimeUnit = EMovieSceneTimeUnit::DisplayRate);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Sequencer Tools | Control Rig")` — Key Controls On Section at the specified frame
- L1369 _public prototype_ `static void ShowAllControls(UMovieSceneSection* InSection);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Sequencer Tools | Control Rig")` — Shows all of the controls for the given section
- L1373 _public prototype_ `static void HideAllControls(UMovieSceneSection* InSection);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Sequencer Tools | Control Rig")` — Hides all of the controls for the given section
- L1377 _public prototype_ `static void SetControlRigPriorityOrder(UMovieSceneTrack* InTrack,int32 PriorityOrder);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Sequencer Tools | Control Rig")` — Set Control Rig priority order
- L1381 _public prototype_ `static int32 GetControlRigPriorityOrder(UMovieSceneTrack* InTrack);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Sequencer Tools | Control Rig")` — Get Control Rig prirority order
- L1387 _public prototype_ `static bool IsFKControlRig(UControlRig* InControlRig);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Sequencer Tools | Control Rig")` — Whether or not the control rig is an FK Control Rig. @param InControlRig Rig to test to see if FK Control Rig
- L1393 _public prototype_ `static bool IsLayeredControlRig(UControlRig* InControlRig);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Sequencer Tools | Control Rig")` — Whether or not the control rig is an Layered Control Rig. @param InControlRig Rig to test to see if Layered Control Rig
- L1399 _public prototype_ `static bool MarkLayeredModeOnTrackDisplay(UMovieSceneControlRigParameterTrack* InTrack);` — Mark the layered mode of a control rig on the color and display name of a track @param InTrack The track to modify the color and display name if necessary
- L1408 _public prototype_ `static bool SetControlRigLayeredMode(UMovieSceneControlRigParameterTrack* InTrack, bool bSetIsLayered);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Sequencer Tools | Control Rig")` — Convert the control rig track into absolute or layered rig @param InTrack Control rig track to convert @param bSetIsLayered Convert to layered rig if true, or absolute if false
- L1415 _public prototype_ `static EControlRigFKRigExecuteMode GetFKControlRigApplyMode(UControlRig* InControlRig);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Sequencer Tools | Control Rig")` — Get FKControlRig Apply Mode. @param InControlRig Rig to test @return The EControlRigFKRigExecuteMode mode it is in, either Replace,Additive or Direct
- L1423 _public prototype_ `static bool SetControlRigApplyMode(UControlRig* InControlRig, EControlRigFKRigExecuteMode InApplyMode);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Sequencer Tools | Control Rig")` — Set the FK Control Rig to apply mode @param InControlRig Rig to set @param InApplyMode Set the EControlRigFKRigExecuteMode mode (Replace,Addtiive or Direct) @return returns True if the mode was set, may not be set if the Control Rig doesn't support these modes currently only FKControlRig's do.
- L1432 _public prototype_ `static bool RecreateControlRigWithNewSettings(UMovieSceneControlRigParameterTrack* InTrack, const TMap<FName, FString>& InSettingsToOverride);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Sequencer Tools | Control Rig")` — Recreate a control rig track with new settings @param InTrack Track to recreate Control Rig @param InSettingsToOverride Map of public variable name and value strings that should be applied to the rig.
- L1440 _public prototype_ `static bool DeleteAnimLayer(int32 Index);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Sequencer Tools | Control Rig | Animation Layers")` — Delete anim layer at specified index @param Index The index where the anim layer exists @return Returns true if successful, false otherwise
- L1448 _public prototype_ `static int32 DuplicateAnimLayer(int32 Index);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Sequencer Tools | Control Rig | Animation Layers")` — Duplicate anim layer at specified index @param Index The index where the anim layer exists @return Returns index of new layer, -1 if none created
- L1455 _public prototype_ `static int32 AddAnimLayerFromSelection();` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Sequencer Tools | Control Rig | Animation Layers")` — Add anim layer from objects selected in Sequencer @return Returns Index of created anim layer
- L1464 _public prototype_ `static bool ReorderAnimLayers(int32 OldIndex, int32 NewIndex);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Sequencer Tools | Control Rig | Animation Layers")` — Move Anim Layer to new index, this will also change evaluation order @param OldIndex The old index where the anim layer exists, can not be zero, can not move the base layer @param NewIndex The new where the anim layer exists, can not be zero, can not move into the base layer. @return Returns true if successful, false if not, for example if the indices are invalid, or if you are trying to move the base layer
- L1469 _public prototype_ `static bool MergeAnimLayers(const TArray<int32>& Indices);` — `UE_DEPRECATED(5.6, "Use MergeAnimLayersWithSettings that takes FMergeAnimLayerSettings")` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Sequencer Tools | Control Rig | AnimationLayers", meta = (DeprecatedFunction, DeprecationMessage = "Use MergeAnimLayersWithSettings that takes FMergeAnimLayerSettings"))`
- L1479 _public prototype_ `static bool MergeAnimLayersWithSettings(const TArray<int32>& Indices, const FMergeAnimLayerSettings& MergeAnimLayerSettings);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Sequencer Tools | Control Rig | Animation Layers")`
- L1487 _public prototype_ `static TArray<UAnimLayer*> GetAnimLayers(bool bAddIfDoesNotExist = true);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Sequencer Tools | Control Rig | Animation Layers")` — Get the animation layer objects, will create it bAddIfDoesNotExist is set to true @param bAddIfDoesNotExist If it doesn't exist create it @return Returns array of anim layer objects if they exist on active Sequencer
- L1495 _public prototype_ `static int32 GetAnimLayerIndex(UAnimLayer* AnimLayer);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Sequencer Tools | Control Rig | Animation Layers")` — Helper function to get the index in the anim layer array from the anim layer @param Anim Layer to get the index for @return Returns index for the anim layer or INDEX_NONE(-1) if it doesn't exist
- L1503 _public prototype_ `static UAIESelectionSets* GetSelectionSets(bool bAddIfDoesNotExist = true);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Sequencer Tools | Control Rig | Selection Sets")` — Get the selection set objects, will create it bAddIfDoesNotExist is set to true @param bAddIfDoesNotExist If it doesn't exist create it @return Returns main selection set object that contains operations you can perform to create and use selection sets

#### Free symbols / members of external scopes

- L25 _macro_ `#define UE_API CONTROLRIGEDITOR_API`

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Public/ControlRigSpaceChannelCurveModel.h` (Public)


#### class `FControlRigSpaceChannelCurveModel`  
`class FControlRigSpaceChannelCurveModel : public FKeyBarCurveModel`  
_L16-66_
- inherits: `FKeyBarCurveModel`
- L19 _public member_ `static ECurveEditorViewID ViewID;`
- L21 _public prototype_ `FControlRigSpaceChannelCurveModel(TMovieSceneChannelHandle<FMovieSceneControlRigSpaceChannel> InChannel, UMovieSceneSection* InOwningSection, TWeakPtr<ISequencer> InWeakSequencer);`
- L22 _public prototype_ `~FControlRigSpaceChannelCurveModel();`
- L24 _public prototype_ `virtual const void* GetCurve() const override;` — FCurveModel
- L26 _public prototype_ `virtual void Modify() override;`
- L28 _public prototype_ `virtual void DrawCurve(const FCurveEditor& CurveEditor, const FCurveEditorScreenSpace& ScreenSpace, TArray<TTuple<double, double>>& InterpolatingPoints) const override;`
- L29 _public prototype_ `virtual void GetKeys(double MinTime, double MaxTime, double MinValue, double MaxValue, TArray<FKeyHandle>& OutKeyHandles) const override;`
- L30 _public prototype_ `virtual void GetKeyDrawInfo(ECurvePointType PointType, const FKeyHandle InKeyHandle, FKeyDrawInfo& OutDrawInfo) const override;`
- L32 _public prototype_ `virtual void GetKeyPositions(TArrayView<const FKeyHandle> InKeys, TArrayView<FKeyPosition> OutKeyPositions) const override;`
- L33 _public prototype_ `virtual void SetKeyPositions(TArrayView<const FKeyHandle> InKeys, TArrayView<const FKeyPosition> InKeyPositions, EPropertyChangeType::Type ChangeType) override;`
- L35 _public prototype_ `virtual void GetKeyAttributes(TArrayView<const FKeyHandle> InKeys, TArrayView<FKeyAttributes> OutAttributes) const override;`
- L36 _public prototype_ `virtual void SetKeyAttributes(TArrayView<const FKeyHandle> InKeys, TArrayView<const FKeyAttributes> InAttributes, EPropertyChangeType::Type ChangeType = EPropertyChangeType::Unspecified) override;`
- L38 _public prototype_ `virtual void GetCurveAttributes(FCurveAttributes& OutCurveAttributes) const override;`
- L39 _public prototype_ `virtual void SetCurveAttributes(const FCurveAttributes& InCurveAttributes) override;`
- L40 _public prototype_ `virtual void GetTimeRange(double& MinTime, double& MaxTime) const override;`
- L41 _public prototype_ `virtual void GetValueRange(double& MinValue, double& MaxValue) const override;`
- L42 _public prototype_ `virtual int32 GetNumKeys() const override;`
- L43 _public function_ `virtual void GetNeighboringKeys(const FKeyHandle InKeyHandle, TOptional<FKeyHandle>& OutPreviousKeyHandle, TOptional<FKeyHandle>& OutNextKeyHandle) const override`
- L44 _public prototype_ `virtual bool Evaluate(double ProspectiveTime, double& OutValue) const override;`
- L45 _public prototype_ `virtual void AddKeys(TArrayView<const FKeyPosition> InKeyPositions, TArrayView<const FKeyAttributes> InAttributes, TArrayView<TOptional<FKeyHandle>>* OutKeyHandles) override;`
- L46 _public prototype_ `virtual void RemoveKeys(TArrayView<const FKeyHandle> InKeys, double InCurrentTime) override;`
- L48 _public prototype_ `virtual void CreateKeyProxies(TWeakPtr<FCurveEditor> InWeakCurveEditor, FCurveModelID InCurveModelID, TArrayView<const FKeyHandle> InKeyHandles, TArrayView<UObject*> OutObjects) override;`
- L50 _public prototype_ `virtual UObject* GetOwningObject() const override;`
- L51 _public prototype_ `virtual bool HasChangedAndResetTest() override;`
- L54 _public prototype_ `virtual void BuildContextMenu(const FCurveEditor& CurveEditor,FMenuBuilder& MenuBuilder, TOptional<FCurvePointHandle> ClickedPoint);` — FKeyBarCurveModel
- L55 _public prototype_ `virtual TArray<FKeyBarCurveModel::FBarRange> FindRanges();`
- L59 _private prototype_ `void FixupCurve();`
- L61 _private member_ `TMovieSceneChannelHandle<FMovieSceneControlRigSpaceChannel> ChannelHandle;`
- L62 _private member_ `TWeakObjectPtr<UMovieSceneSection> WeakSection;`
- L63 _private member_ `TWeakPtr<ISequencer> WeakSequencer;`
- L64 _private member_ `FGuid LastSignature;`
- L65 _private member_ `FDelegateHandle OnDestroyHandle;`

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Public/ControlRigSpaceChannelEditors.h` (Public)


#### struct `FSpaceChannelAndSection`  
`struct FSpaceChannelAndSection`  
_L34-39_
- L36 _public function_ `FSpaceChannelAndSection() : SectionToKey(nullptr), SpaceChannel(nullptr)`
- L37 _public member_ `UMovieSceneSection* SectionToKey;`
- L38 _public member_ `FMovieSceneControlRigSpaceChannel* SpaceChannel;`

#### struct `FControlRigSpaceChannelHelpers`  
`struct FControlRigSpaceChannelHelpers`  
_L45-67_
- desc: Class that contains helper functions for various space switching activities
- L47 _public prototype_ `static FKeyHandle SequencerKeyControlRigSpaceChannel(UControlRig* ControlRig, ISequencer* Sequencer, FMovieSceneControlRigSpaceChannel* Channel, UMovieSceneSection* SectionToKey, FFrameNumber Time, URigHierarchy* RigHierarchy, const FRigElementKey& ControlKey, const FRigElementKey& SpaceKey);`
- L48 _public prototype_ `static void SequencerSpaceChannelKeyDeleted(UControlRig* ControlRig, ISequencer* Sequencer, FName ControlName, FMovieSceneControlRigSpaceChannel* Channel, UMovieSceneControlRigParameterSection* SectionToKey, FFrameNumber TimeOfDeletion);`
- L49 _public prototype_ `static UMovieSceneControlRigParameterSection* GetControlRigSection(ISequencer* Sequencer, const UControlRig* ControlRig);`
- L50 _public prototype_ `static void CompensateIfNeeded(UControlRig* ControlRig, ISequencer* Sequencer, UMovieSceneControlRigParameterSection* Section, const TOptional<FFrameNumber>& Time, bool bCompPreviousTick);`
- L51 _public prototype_ `static FSpaceChannelAndSection FindSpaceChannelAndSectionForControl(UControlRig* ControlRig, FName ControlName, ISequencer* Sequencer, bool bCreateIfNeeded);`
- L52 _public prototype_ `static void SequencerBakeControlInSpace(UControlRig* ControlRig, ISequencer* Sequencer, FMovieSceneControlRigSpaceChannel* Channel, UMovieSceneSection* SectionToKey, URigHierarchy* RigHierarchy, const FRigElementKey& ControlKey, FRigSpacePickerBakeSettings InSettings);`
- L54 _public prototype_ `static void GetFramesInThisSpaceAfterThisTime(UControlRig* ControlRig, FName ControlName, FMovieSceneControlRigSpaceBaseKey CurrentValue, FMovieSceneControlRigSpaceChannel* Channel, UMovieSceneSection* SectionToKey, FFrameNumber Time, TSortedMap<FFrameNumber,FFrameNumber>& OutMoreFrames);`
- L57 _public prototype_ `static void HandleSpaceKeyTimeChanged(UControlRig* ControlRig, FName ControlName,FMovieSceneControlRigSpaceChannel* Channel, UMovieSceneSection* SectionToKey, FFrameNumber CurrentFrame, FFrameNumber NextFrame);`
- L59 _public prototype_ `static void DeleteTransformKeysAtThisTime(UControlRig* ControlRig, UMovieSceneControlRigParameterSection* Section, FName ControlName, FFrameNumber Time);`
- L60 _public prototype_ `static FLinearColor GetColor(const FMovieSceneControlRigSpaceBaseKey& Key);`
- L61 _public prototype_ `static FReply OpenBakeDialog(ISequencer* Sequencer, FMovieSceneControlRigSpaceChannel* Channel, int32 KeyIndex, UMovieSceneSection* SectionToKey);`
- L62 _public prototype_ `static TArray<FKeyBarCurveModel::FBarRange> FindRanges(FMovieSceneControlRigSpaceChannel* Channel, const UMovieSceneSection* Section);`
- L64 _public prototype_ `static TPair<FRigControlElement*, FChannelMapInfo*> GetControlAndChannelInfo(UControlRig* ControlRig, UMovieSceneControlRigParameterSection* Section, FName ControlName);` — retrieve the control and the channel infos for that ControlRig/Section.
- L66 _public prototype_ `static int32 GetNumFloatChannels(const ERigControlType InControlType);` — retrieve the number of float channels based on the control type.

#### Free symbols / members of external scopes

- L70 _prototype_ `FKeyHandle AddOrUpdateKey(FMovieSceneControlRigSpaceChannel* Channel, UMovieSceneSection* SectionToKey, FFrameNumber Time, ISequencer& Sequencer, const FGuid& ObjectBindingID, FTrackInstancePropertyBindings* PropertyBindings);` — template specialization
- L73 _prototype_ `bool CanCreateKeyEditor(const FMovieSceneControlRigSpaceChannel* Channel);` — Key editor overrides
- L74 _prototype_ `TSharedRef<SWidget> CreateKeyEditor(const TMovieSceneChannelHandle<FMovieSceneControlRigSpaceChannel>& Channel, const UE::Sequencer::FCreateKeyEditorParams& Params);`
- L77 _prototype_ `void DrawKeys(FMovieSceneControlRigSpaceChannel* Channel, TArrayView<const FKeyHandle> InKeyHandles, const UMovieSceneSection* InOwner, TArrayView<FKeyDrawParams> OutKeyDrawParams);` — Key drawing overrides
- L78 _prototype_ `int32 DrawExtra(FMovieSceneControlRigSpaceChannel* Channel, const UMovieSceneSection* Owner, const FSequencerChannelPaintArgs& PaintArgs, int32 LayerId);`
- L89 _function_ `inline bool SupportsCurveEditorModels(const TMovieSceneChannelHandle<FMovieSceneControlRigSpaceChannel>& Channel)` — Curve editor models
- L90 _prototype_ `TUniquePtr<FCurveModel> CreateCurveEditorModel(const TMovieSceneChannelHandle<FMovieSceneControlRigSpaceChannel>& Channel, const UE::Sequencer::FCreateCurveEditorModelParams& Params);`

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Public/ControlRigThumbnailRenderer.h` (Public)


#### class `UControlRigThumbnailRenderer`  
`class UControlRigThumbnailRenderer : public USkeletalMeshThumbnailRenderer`  
_L21-36_
- reflection: `UCLASS(config=Editor, MinimalAPI)`
- inherits: `USkeletalMeshThumbnailRenderer`
- L26 _private prototype_ `virtual bool CanVisualizeAsset(UObject* Object) override;`
- L27 _private prototype_ `virtual void Draw(UObject* Object, int32 X, int32 Y, uint32 Width, uint32 Height, FRenderTarget*, FCanvas* Canvas, bool bAdditionalViewFamily) override;`
- L31 _private prototype_ `virtual void AddAdditionalPreviewSceneContent(UObject* Object, UWorld* PreviewWorld) override;` — USkeletalMeshThumbnailRenderer implementation
- L34 _protected member_ `FControlRigAssetInterfacePtr RigBlueprint;`
- L35 _protected member_ `TMap<FName, AActor*> ShapeActors;`

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Public/EditMode/ControlRigEditMode.h` (Public)


#### enum `ERecreateControlRigShape`  
`enum class ERecreateControlRigShape`  
_L75-80_
- L77 _public enumerator_ `RecreateNone`
- L78 _public enumerator_ `RecreateAll`
- L79 _public enumerator_ `RecreateSpecified`

#### class `UControlRigEditModeDelegateHelper`  
`class UControlRigEditModeDelegateHelper : public UObject`  
_L84-104_
- reflection: `UCLASS()`
- inherits: `UObject`
- L91 _public prototype_ `void OnPoseInitialized();` — `UFUNCTION()`
- L94 _public prototype_ `void PostPoseUpdate();` — `UFUNCTION()`
- L96 _public prototype_ `void AddDelegates(USkeletalMeshComponent* InSkeletalMeshComponent);`
- L97 _public prototype_ `void RemoveDelegates();`
- L99 _public member_ `TWeakObjectPtr<USkeletalMeshComponent> BoundComponent;`
- L100 _public member_ `FControlRigEditMode* EditMode = nullptr;`
- L103 _private member_ `FDelegateHandle OnBoneTransformsFinalizedHandle;`

#### struct `FDetailKeyFrameCacheAndHandler`  
`struct FDetailKeyFrameCacheAndHandler: public IDetailKeyframeHandler`  
_L107-136_
- inherits: `IDetailKeyframeHandler`
- L109 _public function_ `FDetailKeyFrameCacheAndHandler()`
- L112 _public prototype_ `virtual bool IsPropertyKeyable(const UClass* InObjectClass, const class IPropertyHandle& PropertyHandle) const override;` — IDetailKeyframeHandler interface
- L113 _public prototype_ `virtual bool IsPropertyKeyingEnabled() const override;`
- L114 _public prototype_ `virtual void OnKeyPropertyClicked(const IPropertyHandle& KeyedPropertyHandle) override;`
- L115 _public prototype_ `virtual bool IsPropertyAnimated(const class IPropertyHandle& PropertyHandle, UObject* ParentObject) const override;`
- L116 _public prototype_ `virtual EPropertyKeyedStatus GetPropertyKeyedStatus(const IPropertyHandle& PropertyHandle) const override;`
- L119 _public prototype_ `void OnGlobalTimeChanged();` — Delegates Resetting Cached Data
- L120 _public prototype_ `void OnMovieSceneDataChanged(EMovieSceneDataChangeType);`
- L121 _public prototype_ `void OnChannelChangedWithTime(const TArray<FFrameNumber>&, const FMovieSceneChannelMetaData*, UMovieSceneSection*);`
- L123 _public prototype_ `void SetDelegates(TWeakPtr<ISequencer>& InWeakSequencer, FControlRigEditMode* InEditMode);`
- L124 _public prototype_ `void UnsetDelegates();`
- L125 _public prototype_ `void ResetCachedData();`
- L126 _public prototype_ `void UpdateIfDirty();`
- L128 _public member_ `mutable TMap<const IPropertyHandle*, EPropertyKeyedStatus> CachedPropertyKeyedStatusMap;` — Map to the last calculated property keyed status. Resets when Scrubbing, changing Movie Scene Data, etc
- L131 _public member_ `bool bValuesDirty = false;` — flag to specify that we need to update values, will poll this on edit mode tick for performance
- L133 _private member_ `TWeakPtr<ISequencer> WeakSequencer;`
- L134 _private member_ `FControlRigEditMode* EditMode = nullptr;`

#### struct `FMultiControlRigElementSelection`  
`struct FMultiControlRigElementSelection`  
_L139-148_
- reflection: `USTRUCT(BlueprintType)`
- L144 _public member_ `TArray<TWeakObjectPtr<UControlRig>> Rigs;` — `UPROPERTY()`
- L147 _public member_ `TArray<FRigElementKeyCollection> KeysPerRig;` — `UPROPERTY()`

#### class `FControlRigEditMode`  
`class FControlRigEditMode : public IPersonaEditMode`  
_L154-885_
- inherits: `IPersonaEditMode`
- L157 _public member_ `static inline const FLazyName ModeName = FLazyName(TEXT("Edit`
- L159 _public prototype_ `FControlRigEditMode();`
- L160 _public prototype_ `~FControlRigEditMode();`
- L164 _public prototype_ `void SetObjects(UControlRig* InControlRig, UObject* BindingObject, const TWeakPtr<ISequencer>& InSequencer);` — Set the Control Rig Object to be active in the edit mode. You set both the Control Rig and a possible binding together with an optional Sequencer This will remove all other control rigs present and should be called for stand alone editors, like the Control Rig Editor
- L167 _public prototype_ `bool AddControlRigObject(UControlRig* InControlRig, const TWeakPtr<ISequencer>& InSequencer);` — Add a Control Rig object if it doesn't exist, will return true if it was added, false if it wasn't since it's already there. You can also set the Sequencer.
- L170 _public prototype_ `void RemoveControlRig(UControlRig* InControlRig);` — Remove control rig
- L173 _public prototype_ `void ReplaceControlRig(UControlRig* OldControlRig, UControlRig* NewControlRig);` — Replace old Control Rig with the New Control Rig, perhaps from a recompile in the level editor
- L176 _public prototype_ `virtual bool IsInLevelEditor() const;` — This edit mode is re-used between the level editor and the asset editors (control rig editor etc.). Calling this indicates which context we are in
- L178 _public function_ `virtual bool AreEditingControlRigDirectly() const` — This is used to differentiate between the control rig editor and any other (asset/level) editors in which this edit mode is used
- L181 _public prototype_ `virtual bool UsesToolkits() const override;` — FEdMode interface
- L182 _public prototype_ `virtual void Enter() override;`
- L183 _public prototype_ `virtual void Exit() override;`
- L184 _public prototype_ `virtual void Tick(FEditorViewportClient* ViewportClient, float DeltaTime) override;`
- L185 _public prototype_ `virtual void Render(const FSceneView* View, FViewport* Viewport, FPrimitiveDrawInterface* PDI) override;`
- L186 _public prototype_ `virtual void DrawHUD(FEditorViewportClient* ViewportClient, FViewport* Viewport, const FSceneView* View, FCanvas* Canvas) override;`
- L187 _public prototype_ `virtual bool EndTracking(FEditorViewportClient* InViewportClient, FViewport* InViewport) override;`
- L188 _public prototype_ `virtual bool StartTracking(FEditorViewportClient* InViewportClient, FViewport* InViewport) override;`
- L189 _public prototype_ `virtual bool BeginTransform(const FGizmoState& InState) override;`
- L190 _public prototype_ `virtual bool EndTransform(const FGizmoState& InState) override;`
- L191 _public prototype_ `virtual bool HandleClick(FEditorViewportClient* InViewportClient, HHitProxy *HitProxy, const FViewportClick &Click) override;`
- L192 _public prototype_ `virtual bool BoxSelect(FBox& InBox, bool InSelect = true) override;`
- L193 _public prototype_ `virtual bool FrustumSelect(const FConvexVolume& InFrustum, FEditorViewportClient* InViewportClient, bool InSelect = true) override;`
- L194 _public prototype_ `virtual void SelectNone() override;`
- L195 _public prototype_ `virtual bool InputDelta(FEditorViewportClient* InViewportClient, FViewport* InViewport, FVector& InDrag, FRotator& InRot, FVector& InScale) override;`
- L196 _public prototype_ `virtual bool UsesTransformWidget() const override;`
- L197 _public prototype_ `virtual bool GetPivotForOrbit(FVector& OutPivot) const override;`
- L198 _public prototype_ `virtual bool UsesTransformWidget(UE::Widget::EWidgetMode CheckMode) const override;`
- L199 _public prototype_ `virtual FVector GetWidgetLocation() const override;`
- L200 _public prototype_ `virtual bool GetCustomDrawingCoordinateSystem(FMatrix& OutMatrix, void* InData) override;`
- L201 _public prototype_ `virtual bool GetCustomInputCoordinateSystem(FMatrix& OutMatrix, void* InData) override;`
- L202 _public prototype_ `virtual bool ShouldDrawWidget() const override;`
- L203 _public prototype_ `virtual bool IsCompatibleWith(FEditorModeID OtherModeID) const override;`
- L204 _public prototype_ `virtual bool GetCursor(EMouseCursor::Type& OutCursor) const override;`
- L205 _public prototype_ `virtual bool MouseMove(FEditorViewportClient* ViewportClient, FViewport* Viewport, int32 x, int32 y) override;`
- L206 _public prototype_ `virtual bool MouseEnter( FEditorViewportClient* ViewportClient,FViewport* Viewport,int32 x, int32 y ) override;`
- L207 _public prototype_ `virtual bool MouseLeave(FEditorViewportClient* ViewportClient, FViewport* Viewport) override;`
- L208 _public prototype_ `virtual void PostUndo() override;`
- L209 _public prototype_ `virtual EEditAction::Type GetActionDragDuplicate() override;`
- L212 _public function_ `virtual bool GetCameraTarget(FSphere& OutTarget) const override` — IPersonaEditMode interface
- L213 _public function_ `virtual class IPersonaPreviewScene& GetAnimPreviewScene() const override`
- L214 _public function_ `virtual void GetOnScreenDebugInfo(TArray<FText>& OutDebugInfo) const override`
- L217 _public prototype_ `virtual void AddReferencedObjects( FReferenceCollector& Collector ) override;` — FGCObject interface
- L220 _public prototype_ `void RefreshObjects();` — Refresh our internal object list (they may have changed)
- L223 _public prototype_ `static FControlRigEditMode* GetEditModeFromWorldContext(UWorld* InWorldContext);` — Find the edit mode corresponding to the specified world context
- L226 _public function_ `FOnGetRigElementTransform& OnGetRigElementTransform()` — Bone Manipulation Delegates
- L227 _public function_ `FOnSetRigElementTransform& OnSetRigElementTransform()`
- L230 _public function_ `FOnGetContextMenu& OnGetContextMenu()` — Context Menu Delegates
- L231 _public function_ `FNewMenuCommandsDelegate& OnContextMenuCommands()`
- L232 _public function_ `FSimpleMulticastDelegate& OnAnimSystemInitialized()`
- L235 _public function_ `FControlRigAddedOrRemoved& OnControlRigAddedOrRemoved()` — Control Rig Changed Delegate
- L238 _public function_ `FControlRigSelected& OnControlRigSelected()` — Control Rig Selected Delegate
- L241 _public function_ `FOnControlRigVisibilityChanged& OnControlRigVisibilityChanged()` — Control Rig Visibility Delegate
- L244 _public function_ `FControlRigEditModeInteractionStartedEvent& OnGizmoInteractionStarted()` — Broadcasts a notification when a gizmo manipulation has started
- L247 _public function_ `FSimpleMulticastDelegate& OnControlRigShapeActorsRecreated()` — Returns a delegate broadcast when control rig shape actors were recreated
- L250 _public function_ `FControlRigEditModeInteractionEndedEvent& OnGizmoInteractionEnded()` — Broadcasts a notification when a gizmo manipulation has ended
- L253 _public function_ `FControlRigEditModeInteractionUpdatedEvent& OnGizmoInteractionPreUpdated()` — Broadcasts a notification when a gizmo manipulation has been updated (before the update actually takes place)
- L255 _public function_ `FControlRigEditModeInteractionUpdatedEvent& OnGizmoInteractionPostUpdated()` — Broadcasts a notification when a gizmo manipulation has been updated (after the transforms have been updated)
- L258 _public prototype_ `void OnHierarchyModified(ERigHierarchyNotification InNotif, URigHierarchy* InHierarchy, const FRigNotificationSubject& InSubject);` — callback that gets called when rig element is selected in other view
- L259 _public prototype_ `void OnHierarchyModified_AnyThread(ERigHierarchyNotification InNotif, URigHierarchy* InHierarchy, const FRigNotificationSubject& InSubject);`
- L260 _public prototype_ `void OnControlModified(UControlRig* Subject, FRigControlElement* InControlElement, const FRigControlModifiedContext& Context);`
- L261 _public prototype_ `void OnPreConstruction_AnyThread(UControlRig* InRig, const FName& InEventName);`
- L262 _public prototype_ `void OnPostConstruction_AnyThread(UControlRig* InRig, const FName& InEventName);`
- L266 _public prototype_ `bool CanRemoveFromPreviewScene(const USceneComponent* InComponent);` — return true if it can be removed from preview scene - this is to ensure preview scene doesn't remove shape actors
- L268 _public function_ `TSharedPtr<FUICommandList> GetCommandBindings() const`
- L272 _public prototype_ `void RequestToRecreateControlShapeActors(UControlRig* ControlRig = nullptr);` — Requests to recreate the shape actors in the next tick. Will recreate only the ones for the specified Control Rig, otherwise will recreate all of them
- L274 _public function_ `static uint32 ValidControlTypeMask()`
- L280 _public prototype_ `void ShowControlRigControls(UControlRig* InControlRig,const TSet<FString>& Names, bool bVal);` — show or hide the specified Controls on this Control Rig;
- L281 _public prototype_ `void ClearOutHidden(UControlRig* InControlRig);`
- L285 _protected prototype_ `EControlRigInteractionTransformSpace GetTransformSpace() const;`
- L289 _protected prototype_ `AControlRigShapeActor* GetControlShapeFromControlName(UControlRig* InControlRig,const FName& InControlName) const;` — Get the node name from the property path
- L292 _protected prototype_ `void SetObjects_Internal();` — Helper function: set ControlRigs array to the details panel
- L295 _protected prototype_ `void SetUpDetailPanel() const;` — Set up Details Panel based upon Selected Objects
- L298 _protected prototype_ `void UpdatePivotTransforms();` — Updates cached pivot transforms
- L299 _protected prototype_ `bool ComputePivotFromEditedShape(UControlRig* InControlRig, FTransform& OutTransform) const;`
- L300 _protected prototype_ `bool ComputePivotFromShapeActors(UControlRig* InControlRig, const bool bEachLocalSpace, const EControlRigInteractionTransformSpace InSpace, FTransform& OutTransform) const;`
- L301 _protected prototype_ `bool ComputePivotFromElements(UControlRig* InControlRig, FTransform& OutTransform) const;`
- L302 _protected prototype_ `FTransform GetPivotOrientation(const FRigElementKey& InControlKey, const UControlRig* InControlRig, URigHierarchy* InHierarchy, const EControlRigInteractionTransformSpace InSpace, const FTransform& InComponentTransform) const;`
- L305 _protected prototype_ `ECoordSystem GetCoordSystemSpace() const;` — Get the current coordinate system space
- L308 _protected prototype_ `void HandleSelectionChanged();` — Handle selection internally
- L311 _protected prototype_ `void ToggleManipulators();` — Toggles visibility of acive control rig shapes in the viewport
- L314 _protected prototype_ `void ToggleAllManipulators();` — Toggles visibility of all  control rig shapes in the viewport
- L317 _protected prototype_ `bool AreControlsVisible() const;` — Returns true if all control rig shapes are visible in the viewport
- L319 _protected prototype_ `virtual bool HandleBeginTransform(const FEditorViewportClient* InViewportClient);`
- L320 _protected prototype_ `virtual bool HandleEndTransform(FEditorViewportClient* InViewportClient);`
- L323 _public prototype_ `virtual bool IsDisplayControlsEnabled() const;`
- L324 _public prototype_ `virtual void ToggleDisplayControlsEnabled();`
- L326 _public prototype_ `virtual bool IsControlsAsOverlayEnabled() const;`
- L327 _public prototype_ `virtual void ToggleControlsAsOverlay();`
- L329 _public prototype_ `virtual bool IsDisplayNullsEnabled() const;`
- L330 _public prototype_ `virtual void ToggleDisplayNulls();`
- L332 _public prototype_ `virtual bool IsDisplaySocketsEnabled() const;`
- L333 _public prototype_ `virtual void ToggleDisplaySockets();`
- L335 _public prototype_ `virtual bool IsDisplayAxesOnSelectionEnabled() const;`
- L336 _public prototype_ `virtual void ToggleDisplayAxesOnSelection();`
- L338 _public prototype_ `virtual float GetAxesOnSelectionScale() const;`
- L341 _public prototype_ `void ToggleModuleManipulators();` — Toggles visibility of acive control rig shapes inside the selected module in the viewport
- L344 _public prototype_ `void OpenPoseLibraryTab();` — Opens the Control Rig Pose Library panel
- L347 _public prototype_ `void ClosePoseLibraryTab();` — Closes the Control Rig Pose Library panel
- L350 _public prototype_ `void ClearSelection();` — Clear Selection
- L353 _public prototype_ `void FrameSelection();` — Frame to current Control Selection
- L356 _public prototype_ `void FrameItems(const TArray<FRigElementKey>& InItems);` — Frame a list of provided items
- L359 _public prototype_ `void SetAnimLayerPassthroughKey();` — Sets Passthrough Key on selected anim layers
- L362 _public prototype_ `void SelectAnimLayerWeightChannel();` — Select weight channel on selected anim layers
- L365 _public prototype_ `void SelectMirroredControls();` — Select Mirrored Controls on Current Selection
- L368 _public prototype_ `void AddMirroredControlsToSelection();` — Select Mirrored Controls on Current Selection, keeping current selection
- L371 _public prototype_ `void MirrorSelectedControls();` — Put Selected Controls To Mirrored Pose
- L374 _public prototype_ `void MirrorUnselectedControls();` — Put Unselected Controls To Mirrored Pose
- L377 _public prototype_ `void SelectAllControls();` — Select All Controls
- L382 _public prototype_ `void SavePose(int32 PoseNum = 0);` — Save a pose of selected controls
- L385 _public prototype_ `void SelectPose(bool bDoMirror, int32 PoseNum = 0 );` — Select controls in saved pose
- L388 _public prototype_ `void PastePose(bool bDoMirror, int32 PoseNum = 0);` — Paste saved pose
- L391 _public prototype_ `void OpenSpacePickerWidget();` — Opens up the space picker widget
- L394 _public prototype_ `void ZeroTransforms(bool bSelectionOnly, bool bIncludeChannels = true, UControlRig* InControlRig = nullptr);` — Reset Transforms to Default(which may not be zero if initial values are present
- L397 _public prototype_ `void InvertInputPose(bool bSelectionOnly, bool bIncludeChannels = true);` — Invert Input Pose, this will set layered controls rigs to default pose, for non-layered same as ZeroTransforms
- L400 _public prototype_ `static void ZeroTransforms(UControlRig* ControlRig, const FRigControlModifiedContext& Context, bool bSelectionOnly, bool bIncludeChannels);` — Reset Transforms for this Control Rig Controls based upon selection and channel states
- L403 _public prototype_ `static void InvertInputPose(UControlRig* ControlRig, const FRigControlModifiedContext& Context, bool bSelectionOnly, bool bIncludeChannels);` — Invert Input Pose for this Control Rig Controls based upon selection and channel states
- L406 _public prototype_ `void ToggleMotionTrails();` — Toggle Motion Trail Mode
- L409 _public prototype_ `void TogglePivotMode();` — Toggle Pivot Mode
- L412 _public prototype_ `void IsolateLinkedAnimTracksForAllBindings(bool bIsolate);` — Isolate or un-isolate linked anim tracks for every binding in the current Sequencer
- L417 _private prototype_ `void OpenTabMenu();` — Opens the space picker or a contextual menu with the picker and utility actions if any.
- L420 _private prototype_ `bool CanFrameSelection();` — Whether or not we should Frame Selection or not
- L423 _private member_ `FPendingWidgetFocus PendingFocus;` — Pending focus handler
- L426 _private prototype_ `void RegisterPendingFocusMode();` — Pending focus cvar binding functions to enable/disable pending focus mode
- L427 _private prototype_ `void UnregisterPendingFocusMode();`
- L428 _private member_ `FDelegateHandle PendingFocusHandle;`
- L431 _private prototype_ `void SetSequencerDelegates(const TWeakPtr<ISequencer>& InWeakSequencer);` — Listen to sequencer and optimize notifications and performances when playing.
- L432 _private prototype_ `void UnsetSequencerDelegates() const;`
- L433 _private prototype_ `void UpdateSequencerStatus();`
- L434 _private member_ `bool bSequencerPlaying = false;`
- L439 _public prototype_ `void ToggleControlShapeTransformEdit();` — Toggle Shape Transform Edit
- L444 _private prototype_ `FText GetToggleControlShapeTransformEditHotKey() const;` — The hotkey text is passed to a viewport notification to inform users how to toggle shape edit
- L447 _private prototype_ `void BindCommands();` — Bind our keyboard commands
- L450 _private prototype_ `void RecreateControlShapeActors();` — It creates if it doesn't have it
- L453 _private prototype_ `bool ShapeSelectionOverride(const UPrimitiveComponent* InComponent) const;` — Let the preview scene know how we want to select components
- L456 _private member_ `bool bIsChangingControlShapeTransform;` — Enable editing of control's shape transform instead of control's transform
- L460 _protected member_ `TWeakPtr<ISequencer> WeakSequencer;`
- L461 _protected member_ `FGuid LastMovieSceneSig;`
- L464 _protected member_ `TPimplPtr<UE::ControlRigEditor::FRigFloatingSpacePickerManager> FloatingSpacePickerManager;` — Handles spawning the floating space picker. Ensures only one can be created at the time. Removes the widget when destroyed.
- L467 _protected prototype_ `UE::ControlRigEditor::FRigFloatingSpacePickerManager& GetSpacePickerManager();` — Lazy creation of the picker manager.
- L470 _protected member_ `TMap<UControlRig*, TUniquePtr<FControlRigInteractionScope>> InteractionScopes;` — The scope for the interaction, one per manipulated Control rig
- L473 _protected member_ `bool bIsTracking;` — True if there's tracking going on right now
- L476 _protected member_ `bool bManipulatorMadeChange;` — Whether a manipulator actually made a change when transacting
- L479 _protected member_ `bool bSelecting;` — Guard value for selection
- L482 _protected member_ `bool bSelectionChanged;` — If selection was changed, we set up proxies on next tick
- L485 _protected member_ `TMap<UControlRig*,FTransform> PivotTransforms;` — Cached transform of pivot point for selected objects for each Control Rig
- L488 _protected member_ `TMap<UControlRig*, FTransform> LastPivotTransforms;` — Previous cached transforms, need this to check on tick if any transform changed, gizmo may have changed
- L491 _protected member_ `TSharedPtr<FUICommandList> CommandBindings;` — Command bindings for keyboard shortcuts
- L494 _protected prototype_ `void OnObjectsReplaced(const TMap<UObject*, UObject*>& OldToNewInstanceMap);` — Called from the editor when a blueprint object replacement has occurred
- L497 _protected prototype_ `void CopyControlsVisibility(const UControlRig* SourceRig, UControlRig* TargetRig);` — Copy control visibility from the source rig (and its modules if necessary) to the target rig
- L500 _protected prototype_ `bool IsTransformDelegateAvailable() const;` — Return true if transform setter/getter delegates are available
- L502 _protected member_ `FOnGetRigElementTransform OnGetRigElementTransformDelegate;`
- L503 _protected member_ `FOnSetRigElementTransform OnSetRigElementTransformDelegate;`
- L504 _protected member_ `FOnGetContextMenu OnGetContextMenuDelegate;`
- L505 _protected member_ `FNewMenuCommandsDelegate OnContextMenuCommandsDelegate;`
- L506 _protected member_ `FSimpleMulticastDelegate OnAnimSystemInitializedDelegate;`
- L507 _protected member_ `FControlRigAddedOrRemoved OnControlRigAddedOrRemovedDelegate;`
- L508 _protected member_ `FControlRigSelected OnControlRigSelectedDelegate;`
- L509 _protected member_ `FOnControlRigVisibilityChanged OnControlRigVisibilityChangedDelegate;`
- L512 _protected member_ `FControlRigEditModeInteractionStartedEvent OnGizmoInteractionStartedDelegate;` — Broadcasts a notification when a gizmo manipulation has started
- L515 _protected member_ `FControlRigEditModeInteractionEndedEvent OnGizmoInteractionEndedDelegate;` — Broadcasts a notification when a gizmo manipulation has ended
- L518 _protected member_ `FControlRigEditModeInteractionUpdatedEvent OnGizmoInteractionPreUpdatedDelegate;` — Broadcasts a notification when a gizmo manipulation has been updated (before the update actually takes place)
- L521 _protected member_ `FControlRigEditModeInteractionUpdatedEvent OnGizmoInteractionPostUpdatedDelegate;` — Broadcasts a notification when a gizmo manipulation has been updated (after the transforms have been updated)
- L524 _protected member_ `FSimpleMulticastDelegate OnControlRigShapeActorsRecreatedDelegate;` — Broadcasts a notification when a control rig shape actors were recreated
- L527 _protected prototype_ `TArray<FRigElementKey> GetSelectedRigElements() const;` — GetSelectedRigElements, if InControlRig is nullptr get the first one
- L528 _protected prototype_ `static TArray<FRigElementKey> GetSelectedRigElements(UControlRig* InControlRig);`
- L531 _protected prototype_ `static TArray<FRigElementKey> GetRigElementsForSettingTransforms(UControlRig* InControlRig, bool bSelectionOnly, bool bIncludeChannels);` — Get the rig elements, based upon the selection or if it's a channel, also will do internal additive filters(like no bools)
- L534 _protected member_ `ERecreateControlRigShape RecreateControlShapesRequired;` — Flag to recreate shapes during tick
- L536 _protected member_ `TArray<UControlRig*> ControlRigsToRecreate;` — List of Control Rigs we should recreate
- L539 _protected member_ `bool bSuspendHierarchyNotifs;` — Flag to temporarily disable handling notifs from the hierarchy
- L542 _protected member_ `TMap<TWeakObjectPtr<UControlRig>,TArray<TObjectPtr<AControlRigShapeActor>>> ControlRigShapeActors;` — Shape actors
- L546 _protected member_ `TObjectPtr<UAnimDetailsProxyManager> AnimDetailsProxyManager;` — Manager for anim details proxies
- L549 _protected prototype_ `bool IsControlSelected(const bool bUseShapes = false) const;` — Utility functions for UI/Some other viewport manipulation
- L550 _protected prototype_ `bool AreRigElementSelectedAndMovable(UControlRig* InControlRig) const;`
- L553 _protected prototype_ `void OpenContextMenu(FEditorViewportClient* InViewportClient);` — Set initial transform handlers
- L557 _protected member_ `float PreviousGizmoScale = 1.0f;` — `UE_DEPRECATED(5.8, "The ControlRigEditMode-Specific gizmo scale feature has been removed.")` — previous Gizmo(Widget) scale before we enter this mode, used to set it back
- L560 _protected member_ `TMap<UControlRig*, UE::ControlRigEditMode::FInteractionDependencyCache> InteractionDependencies;` — Per ControlRig dependencies between the selected controls during interaction.
- L563 _protected prototype_ `UE::ControlRigEditMode::FInteractionDependencyCache& GetInteractionDependencies(UControlRig* InControlRig);` — Returns the interaction dependencies of that ControlRig.
- L567 _public prototype_ `void ClearRigElementSelection(uint32 InTypes);` — Clear all selected RigElements
- L570 _public prototype_ `void SetRigElementSelection(UControlRig* ControlRig, ERigElementType Type, const FName& InRigElementName, bool bSelected);` — Set a RigElement's selection state
- L573 _public prototype_ `void SetRigElementSelection(UControlRig* ControlRig, ERigElementType Type, const TArray<FName>& InRigElementNames, bool bSelected);` — Set multiple RigElement's selection states
- L576 _public prototype_ `bool AreRigElementsSelected(uint32 InTypes, UControlRig* InControlRig) const;` — Check if any RigElements are selected
- L579 _public prototype_ `void GetAllSelectedControls(TMap<UControlRig*, TArray<FRigElementKey>>& OutSelectedControls) const;` — Get all of the selected Controls
- L582 _public prototype_ `TArrayView<const TWeakObjectPtr<UControlRig>> GetControlRigs() const;` — Get all of the ControlRigs, maybe not valid anymore
- L583 _public prototype_ `TArrayView<TWeakObjectPtr<UControlRig>> GetControlRigs();`
- L585 _public prototype_ `TArray<UControlRig*> GetControlRigsArray(bool bIsVisible);` — Get valid  Control Rigs possibly just visible
- L586 _public prototype_ `TArray<const UControlRig*> GetControlRigsArray(bool bIsVisible) const;`
- L589 _public function_ `UAnimDetailsProxyManager* GetAnimDetailsProxyManager() const` — Get the detail proxies control rig
- L592 _public function_ `TWeakPtr<ISequencer> GetWeakSequencer()` — Get Sequencer Driving This
- L595 _public function_ `void SuspendHierarchyNotifs(bool bVal)` — Suspend Rig Hierarchy Notifies
- L598 _public prototype_ `void RequestTransformWidgetMode(UE::Widget::EWidgetMode InWidgetMode);` — Request a certain transform widget for the next update
- L602 _private prototype_ `bool IsViewportHitProxySelectable(HHitProxy* const InHitProxy) const;` — Adapts hovered viewport hit proxies to the controls-only selectability policy used for cursor feedback.
- L605 _private prototype_ `bool IsViewportObjectSelectable(UObject* const InObject) const;` — Returns whether an object is selectable under the current Control Rig viewport policy, including controls-only mode.
- L608 _private prototype_ `void SetRigElementSelectionInternal(UControlRig* ControlRig, ERigElementType Type, const FName& InRigElementName, bool bSelected);` — Set a RigElement's selection state.
- L611 _private prototype_ `void SetRigElementsSelectionInternal(const TMap<TWeakObjectPtr<UControlRig>, TArray<FRigElementKey>>& InRigElementsToSelect, bool bSelected);` — Set multiple RigElements' selection states.
- L614 _private prototype_ `bool HasPivotTransformsChanged() const;` — Whether or not Pivot Transforms have changed, in which case we need to redraw viewport.
- L617 _private prototype_ `void UpdatePivotTransformsIfNeeded(UControlRig* InControlRig, FTransform& InOutTransform) const;` — Updates the pivot transforms before ticking to ensure that they are up-to-date when needed.
- L619 _private member_ `FEditorViewportClient* CurrentViewportClient;`
- L620 _private member_ `TArray<UE::Widget::EWidgetMode> RequestedWidgetModes;`
- L622 _private member_ `FDelegateHandle ViewportSelectabilityDelegateHandle;`
- L626 _private prototype_ `void OnWidgetModeChanged(UE::Widget::EWidgetMode InWidgetMode);`
- L627 _private prototype_ `void OnCoordSystemChanged(ECoordSystem InCoordSystem);`
- L628 _private member_ `TArray<ECoordSystem> CoordSystemPerWidgetMode;`
- L629 _private member_ `bool bIsChangingCoordSystem;`
- L631 _private prototype_ `bool CanChangeControlShapeTransform();`
- L633 _private prototype_ `void OnSettingsChanged(const UControlRigEditModeSettings* InSettings);`
- L634 _private prototype_ `void OnSettingsPropertyChanged(UObject* InObject, FPropertyChangedEvent& PropertyChangedEvent);`
- L638 _public prototype_ `void SetOnlySelectRigControls(bool val);` — Toolbar functions
- L639 _public prototype_ `bool GetOnlySelectRigControls()const;`
- L640 _public prototype_ `bool SetSequencer(TWeakPtr<ISequencer> InSequencer);`
- L643 _private prototype_ `TSet<FName> GetActiveControlsFromSequencer(UControlRig* ControlRig);`
- L646 _private prototype_ `void CreateShapeActors(UControlRig* InControlRig);` — Create/Delete/Update shape actors for the specified ControlRig
- L647 _private prototype_ `void DestroyShapesActors(UControlRig* InControlRig);`
- L648 _private prototype_ `bool TryUpdatingControlsShapes(UControlRig* InControlRig);`
- L651 _private prototype_ `void AddControlRigInternal(UControlRig* InControlRig);` — Internal function for adding ControlRig
- L657 _private prototype_ `void TickManipulatableObjects(const TArray<TWeakObjectPtr<UControlRig>>& InRigs = TArray<TWeakObjectPtr<UControlRig>>()) const;` — Updates the bound components (skeletal meshes or control rig component) and the control shapes so that all transform data are updated. if InRig is empty, all rigs / control shapes will be updated.
- L660 _private prototype_ `bool CheckMovieSceneSig();` — Check on tick to see if movie scene has changed, returns true if it has
- L661 _private prototype_ `void SetControlShapeTransform( const AControlRigShapeActor* InShapeActor, const FTransform& InGlobalTransform, const FTransform& InToWorldTransform, const FRigControlModifiedContext& InContext, const bool bPrintPython, const FControlRigInteractionTransformContext& InTransformContext, const bool bFixEulerFlips = true) const;`
- L664 _private prototype_ `static FTransform GetControlShapeTransform(const AControlRigShapeActor* ShapeActor);`
- L666 _private prototype_ `static void ChangeControlShapeTransform(AControlRigShapeActor* ShapeActor, const FControlRigInteractionTransformContext& InContext, const FTransform& ToWorldTransform);`
- L668 _private prototype_ `bool ModeSupportedByShapeActor(const AControlRigShapeActor* ShapeActor, UE::Widget::EWidgetMode InMode) const;`
- L672 _public prototype_ `static void NotifyDrivenControls(UControlRig* InControlRig, const FRigElementKey& InKey, const FRigControlModifiedContext& InContext);` — notify driven controls, should this be inside CR instead?
- L676 _protected prototype_ `bool MoveControlShapeLocally( AControlRigShapeActor* ShapeActor, const FControlRigInteractionTransformContext& InTransformContext, const FTransform& ToWorldTransform, const FTransform& InLocal);`
- L680 _protected prototype_ `void MoveControlShape(AControlRigShapeActor* ShapeActor, const FControlRigInteractionTransformContext& InContext, const FTransform& ToWorldTransform, const bool bUseLocal, const bool bCalcLocal, FTransform* InOutLocal, TArray<TFunction<void()>>& OutTasks);`
- L686 _protected prototype_ `USceneComponent* GetHostingSceneComponent(const UControlRig* ControlRig = nullptr) const;` — If the passed in ControlRig is nullptr we use the first Control Rig(this can happen from the BP Editors).
- L687 _protected prototype_ `FTransform GetHostingSceneComponentTransform(const UControlRig* ControlRig = nullptr) const;`
- L690 _protected prototype_ `bool IsControlRigSkelMeshVisible(const UControlRig* InControlRig) const;` — Get if the hosted component is visible
- L693 _public member_ `TSharedPtr<FDetailKeyFrameCacheAndHandler> DetailKeyFrameCache;`
- L698 _private prototype_ `void OnPoseInitialized();` — Post pose update handler
- L704 _private prototype_ `void PostPoseUpdate(const FEditorViewportClient* InViewportClient = nullptr, const TArray<TWeakObjectPtr<UControlRig>>& InRigs = TArray<TWeakObjectPtr<UControlRig>>()) const;` — Updates the control shapes properties (transform, visibility, ...) depending on the current viewport state. If InRig is empty, all control shapes will be updated.
- L706 _private prototype_ `void UpdateSelectabilityOnSkeletalMeshes(UControlRig* InControlRig, bool bEnabled);`
- L708 _private prototype_ `bool IsMovingCamera(const FViewport* InViewport) const;`
- L709 _private prototype_ `bool IsDoingDrag(const FViewport* InViewport) const;`
- L712 _private member_ `FDelegateHandle OnWorldCleanupHandle;` — world clean up handlers
- L713 _private prototype_ `void OnWorldCleanup(UWorld* World, bool bSessionEnded, bool bCleanupResources);`
- L714 _private member_ `UWorld* WorldPtr = nullptr;`
- L716 _private prototype_ `void OnEditorClosed();`
- L746 _private member_ `FMarqueeDragTool DragToolHandler;`
- L749 _protected member_ `TArray<TWeakObjectPtr<UControlRig>> RuntimeControlRigs;`
- L750 _protected member_ `bool bShowControlsAsOverlay;`
- L753 _protected prototype_ `TArray<UControlRig*> GetControlRigsBasedOnSelection(bool bSelectionOnly) const;` — if selection flag is set, get control rigs with selected controls, if not get all control rigs if there are none selected
- L756 _private member_ `TMap<UControlRig*,TStrongObjectPtr<UControlRigEditModeDelegateHelper>> DelegateHelpers;`
- L758 _private member_ `TArray<FRigElementKey> DeferredItemsToFrame;`
- L761 _private prototype_ `static uint8 GetInteractionType(const FEditorViewportClient* InViewportClient);` — Computes the current interaction types based on the widget mode
- L762 _private member_ `uint8 InteractionType;`
- L764 _private member_ `bool bPivotsNeedUpdate = true;`
- L766 _private member_ `bool bIsConstructionEventRunning;`
- L767 _private member_ `TArray<uint32> LastHierarchyHash;`
- L768 _private member_ `TArray<uint32> LastShapeLibraryHash;`
- L771 _private member_ `TArray<UControlRig*> RigsToEvaluateDuringThisTick;` — A list of rigs we need to run during this tick
- L772 _private member_ `uint32 RigEvaluationBracket = 0;`
- L791 _private prototype_ `static void EvaluateRig(UControlRig* InControlRig);`
- L794 _private member_ `static bool bDoPostPoseUpdate;` — to disable post pose update, needed for offfline evlauations
- L801 _private prototype_ `const UControlRigEditModeSettings* GetSettings() const;` — get default/mutable settings todo: have a local setting object that listen to property changes to send updates instead of getting data directly from the CDO
- L802 _private prototype_ `UControlRigEditModeSettings* GetMutableSettings() const;`
- L803 _private member_ `mutable TWeakObjectPtr<UControlRigEditModeSettings> WeakSettings;`
- L806 _private member_ `TObjectPtr<UControlRigPoseAsset> StoredPose;` — pose used by the hotkeys
- L808 _private member_ `TWeakObjectPtr<UEditorTransformGizmoContextObject> WeakGizmoContext;`
- L809 _private prototype_ `FRotationContext& GetRotationContext() const;`
- L810 _private prototype_ `void UpdateRotationContext();`
- L812 _private prototype_ `TOptional<FTransform> GetConstraintParentTransform(const UControlRig* InControlRig, const FName& InControlName) const;`
- L813 _private member_ `mutable UE::TransformConstraintUtil::FConstraintsInteractionCache ConstraintsCache;`
- L816 _private member_ `mutable UE::AnimationEditMode::FControlRigKeyframer Keyframer;` — Used to store and apply keyframes (if deferred)
- L819 _private member_ `bool bOtherSelectedObjects = false;` — whether there are other objects selected in the world that are not shape actors or components bound to the rigs
- L820 _private member_ `TSet<TWeakObjectPtr<UObject>> SelectedObjects;`
- L821 _private prototype_ `void CacheAnyOtherSelectedObjects();`
- L823 _private prototype_ `void HandleActorMoving(AActor* InMovedActor);`
- L824 _private member_ `bool bUpdateNonInteractingRigs = false;`
- L825 _private prototype_ `void CacheNonInteractingRigsToUpdate();`
- L826 _private member_ `TArray<TWeakObjectPtr<UControlRig>> NonInteractingRigs;`
- L828 _private member_ `FDelegateHandle BuildViewportInteractionsDelegate;`
- L831 _private member_ `UE::AnimationEditMode::FDirectControl DirectControl;` — direct control system for viewport click-and-drag interactions
- L834 _private prototype_ `void BindDirectControl();` — binds the direct control system to the gizmo
- L857 _private member_ `FMouseMoveCache MouseMoveCache;`

#### struct `FControlRigEditMode::FMarqueeDragTool`  
`struct FMarqueeDragTool`  
_L718-744_
- L720 _public prototype_ `FMarqueeDragTool();`
- L721 _public prototype_ `~FMarqueeDragTool() = default;`
- L723 _public prototype_ `bool StartTracking(FEditorViewportClient* InViewportClient, FViewport* InViewport);`
- L724 _public prototype_ `bool EndTracking(FEditorViewportClient* InViewportClient, FViewport* InViewport);`
- L725 _public prototype_ `void MakeDragTool(FEditorViewportClient* InViewportClient);`
- L726 _public prototype_ `bool InputDelta(FEditorViewportClient* InViewportClient, FViewport* InViewport, FVector& InDrag, FRotator& InRot, FVector& InScale);`
- L728 _public prototype_ `bool UsingDragTool() const;`
- L729 _public prototype_ `void Render3DDragTool(const FSceneView* View, FPrimitiveDrawInterface* PDI);`
- L730 _public prototype_ `void RenderDragTool(const FSceneView* View, FCanvas* Canvas);`
- L738 _private member_ `TSharedPtr<FDragTool> DragTool;` — If there is a dragging tool being used, this will point to it. Gets newed/deleted in StartTracking/EndTracking.
- L741 _private member_ `bool bIsDeletingDragTool = false;` — Tracks whether the drag tool is in the process of being deleted (to protect against reentrancy)
- L743 _private member_ `FControlRigEditMode* EditMode;`

#### class `FControlRigEditMode::FPendingControlRigEvaluator`  
`class FPendingControlRigEvaluator`  
_L774-789_
- L778 _public function_ `FPendingControlRigEvaluator(FControlRigEditMode* InEditMode) : EditMode(InEditMode)`
- L784 _public prototype_ `~FPendingControlRigEvaluator();`
- L788 _private member_ `FControlRigEditMode* EditMode;`

#### struct `FControlRigEditMode::FMouseMoveCache`  
`struct FMouseMoveCache`  
_L838-856_
- desc: This structure is used to cache the last mouse screen position and last viewport in FControlRigEditMode::MouseMove to prevent synthesized mouse movements from triggering useless hover updates.
- L840 _public function_ `bool Update(const FViewport* InViewport, const int32 InX, const int32 InY)`
- L853 _private member_ `const FViewport* Viewport = nullptr;`
- L854 _private member_ `int32 X = 0;`
- L855 _private member_ `int32 Y = 0;`

#### class `FControlRigEditMode::FTurnOffPosePoseUpdate`  
`class FTurnOffPosePoseUpdate`  
_L870-884_
- L873 _public function_ `FTurnOffPosePoseUpdate()`
- L878 _public function_ `~FTurnOffPosePoseUpdate()`
- L883 _private member_ `bool bLastVal;`

#### Free symbols / members of external scopes

- L28 _macro_ `#define UE_API CONTROLRIGEDITOR_API`
- L63 _namespace_ `namespace UE`
- L63 _namespace_ `namespace ControlRigEditor` (scope `UE`)
- L65 _delegate_ `DECLARE_DELEGATE_RetVal_ThreeParams(FTransform, FOnGetRigElementTransform, const FRigElementKey& , bool , bool );`
- L65 _prototype_ `DECLARE_DELEGATE_RetVal_ThreeParams(FTransform, FOnGetRigElementTransform, const FRigElementKey& , bool , bool );`
- L66 _delegate_ `DECLARE_DELEGATE_ThreeParams(FOnSetRigElementTransform, const FRigElementKey& , const FTransform& , bool );`
- L66 _prototype_ `DECLARE_DELEGATE_ThreeParams(FOnSetRigElementTransform, const FRigElementKey& , const FTransform& , bool );`
- L67 _delegate_ `DECLARE_DELEGATE_RetVal(TSharedPtr<FUICommandList>, FNewMenuCommandsDelegate);`
- L67 _prototype_ `DECLARE_DELEGATE_RetVal(TSharedPtr<FUICommandList>, FNewMenuCommandsDelegate);`
- L68 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FControlRigAddedOrRemoved, UControlRig*, bool );`
- L68 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FControlRigAddedOrRemoved, UControlRig*, bool );`
- L69 _delegate_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FControlRigSelected, UControlRig*, const FRigElementKey& ,const bool );`
- L69 _prototype_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FControlRigSelected, UControlRig*, const FRigElementKey& ,const bool );`
- L70 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnControlRigVisibilityChanged, TArray<UControlRig*>);`
- L70 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnControlRigVisibilityChanged, TArray<UControlRig*>);`
- L71 _delegate_ `DECLARE_DELEGATE_RetVal(UToolMenu*, FOnGetContextMenu);`
- L71 _prototype_ `DECLARE_DELEGATE_RetVal(UToolMenu*, FOnGetContextMenu);`
- L150 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FControlRigEditModeInteractionStartedEvent, FMultiControlRigElementSelection, InteractionKeys, EControlRigInteractionType, InteractionType);`
- L150 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FControlRigEditModeInteractionStartedEvent, FMultiControlRigElementSelection, InteractionKeys, EControlRigInteractionType, InteractionType);`
- L151 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FControlRigEditModeInteractionEndedEvent, FMultiControlRigElementSelection, InteractionKeys);`
- L151 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FControlRigEditModeInteractionEndedEvent, FMultiControlRigElementSelection, InteractionKeys);`
- L152 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FControlRigEditModeInteractionUpdatedEvent, FMultiControlRigElementSelection, InteractionKeys, FControlRigInteractionTransformContext, TransformContext);`
- L152 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FControlRigEditModeInteractionUpdatedEvent, FMultiControlRigElementSelection, InteractionKeys, FControlRigInteractionTransformContext, TransformContext);`

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Public/EditMode/ControlRigEditModeUtil.h` (Public)


#### enum `EControlRigInteractionTransformSpace`  
`enum class EControlRigInteractionTransformSpace`  
_L28-34_
- reflection: `UENUM()`
- L30 _public enumerator_ `World`
- L31 _public enumerator_ `Local`
- L32 _public enumerator_ `Parent`
- L33 _public enumerator_ `Explicit`

#### struct `FControlRigInteractionTransformContext`  
`struct FControlRigInteractionTransformContext`  
_L41-71_
- reflection: `USTRUCT(BlueprintType)`
- desc: FControlRigInteractionTransformContext provides a way of passing the various transform parameters to functions that need to know what the transform context is. Extend it if necessary, particularly to avoid overloading some functions signatures.
- L44 _public prototype_ `FControlRigInteractionTransformContext() = default;`
- L46 _public function_ `FControlRigInteractionTransformContext(const UE::Widget::EWidgetMode& InWidgetMode) : bTranslation(InWidgetMode == UE::Widget::WM_Translate || InWidgetMode == UE::Widget::WM_TranslateRotateZ) , bRotation(InWidgetMode == UE::Widget::WM_Rotate || InWidgetMode == UE::Widget::WM_TranslateRotateZ) , bScale(InWidgetMode == UE::Widget::WM_Scale)`
- L52 _public function_ `bool CanTransform() const`
- L57 _public member_ `bool bTranslation = false;`
- L59 _public member_ `FVector Drag = FVector::ZeroVector;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Interaction")`
- L61 _public member_ `bool bRotation = false;`
- L63 _public member_ `FRotator Rot = FRotator::ZeroRotator;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Interaction")`
- L65 _public member_ `bool bScale = false;`
- L67 _public member_ `FVector Scale = FVector::OneVector;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Interaction")`
- L70 _public member_ `EControlRigInteractionTransformSpace Space = EControlRigInteractionTransformSpace::World;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Interaction")`

#### struct `UE::ControlRigEditMode::FInteractionDependencyCache`  
`struct FInteractionDependencyCache`  
_L83-125_
- L85 _public function_ `bool HasDownwardDependencies(const FRigElementKey& InKey) const`
- L90 _public function_ `bool HasUpwardDependencies(const FRigElementKey& InKey) const`
- L95 _public function_ `bool CheckAndUpdateParentsPoseVersion()`
- L121 _public member_ `TSet<FRigElementKey> Parents;`
- L122 _public member_ `TSet<FRigElementKey> Children;`
- L123 _public member_ `TMap<int32, int32> ParentsPoseVersion;`
- L124 _public member_ `TWeakObjectPtr<URigHierarchy> WeakHierarchy;`

#### struct `UE::ControlRigEditMode::FExplicitRotationInteraction`  
`struct FExplicitRotationInteraction`  
_L131-150_
- L133 _public prototype_ `FExplicitRotationInteraction(const FControlRigInteractionTransformContext& InContext, UControlRig* InControlRig, URigHierarchy* InHierarchy, FRigControlElement* InControlElement, const FTransform& InComponentWorldTransform);`
- L139 _public prototype_ `bool IsValid() const;`
- L141 _public prototype_ `void Apply(const FTransform& InGlobalTransform, const FRigControlModifiedContext& InContext, const bool bPrintPython, const TArray< TWeakObjectPtr<UTickableConstraint> >& InConstraints = TArray< TWeakObjectPtr<UTickableConstraint> >()) const;`
- L145 _private member_ `const FControlRigInteractionTransformContext& TransformContext;`
- L146 _private member_ `UControlRig* ControlRig = nullptr;`
- L147 _private member_ `URigHierarchy* Hierarchy = nullptr;`
- L148 _private member_ `FRigControlElement* ControlElement = nullptr;`
- L149 _private member_ `const FTransform& ComponentWorldTransform;`

#### struct `UE::ControlRigEditMode::FSelectionHelper`  
`struct FSelectionHelper`  
_L156-194_
- L158 _public prototype_ `FSelectionHelper( FEditorViewportClient* InViewportClient, const TMap<TWeakObjectPtr<UControlRig>, TArray<TObjectPtr<AControlRigShapeActor>>>& InControlRigShapeActors, TMap<TWeakObjectPtr<UControlRig>, TArray<FRigElementKey>>& OutElements);`
- L167 _public prototype_ `void GetFromFrustum(const FConvexVolume& InFrustum) const;` — Gets the elements contained in the frustum. Note that the function will actually use a screen space rectangle selection if occluded objects must be skipped.
- L172 _private prototype_ `bool IsValid() const;` — Returns true if the viewport to select into is not null.
- L175 _private prototype_ `TOptional<FIntRect> RectangleFromFrustum(const FConvexVolume& InFrustum) const;` — Returns a screen space rectangle based of the frustum. (it assumes that there's a valid near plane)
- L178 _private prototype_ `void GetNonOccludedElements(const FIntRect& InRect) const;` — Gets the no-occluded elements contained in the screen space rectangle.
- L181 _private member_ `FEditorViewportClient* ViewportClient = nullptr;` — The viewport client being interacted with.
- L184 _private member_ `const TMap<TWeakObjectPtr<UControlRig>, TArray<TObjectPtr<AControlRigShapeActor>>>& ControlRigShapeActors;` — A reference to the edit mode's control shapes.
- L187 _private member_ `TMap<TWeakObjectPtr<UControlRig>, TArray<FRigElementKey>>& Elements;` — The elements to be selected.
- L190 _private member_ `const ULevelEditorViewportSettings* LevelEditorViewportSettings = nullptr;` — Current viewport settings. (used for strict box & transparent selection)
- L193 _private member_ `TArray<FName> HiddenLayers;` — List of layers that are hidden in this view. (only valid for level editor vpc)

#### Free symbols / members of external scopes

- L73 _namespace_ `namespace UE`
- L73 _namespace_ `namespace ControlRigEditMode` (scope `UE`)

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Public/IControlRigEditMode.h` (Public)


#### class `IControlRigEditMode`  
`class IControlRigEditMode : public IPersonaEditMode`  
_L10-14_
- inherits: `IPersonaEditMode`
- L13 _public prototype_ `virtual void SetObjects(const TWeakObjectPtr<>& InSelectedObject, UObject* BindingObject, TWeakPtr<ISequencer> InSequencer) = 0;`

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Public/IControlRigEditor.h` (Public)


#### class `IControlRigEditor`  
`class IControlRigEditor`  
_L15-20_
- L18 _public prototype_ `virtual URigVMHost* GetRigVMHost() const = 0;`
- L19 _public prototype_ `virtual bool IsEditorInitialized() const = 0;`

#### class `IControlRigLegacyEditor`  
`class IControlRigLegacyEditor : public FRigVMLegacyEditor, public IControlRigEditor`  
_L23-25_
- inherits: `FRigVMLegacyEditor,IControlRigEditor`

#### class `IControlRigNewEditor`  
`class IControlRigNewEditor : public FRigVMNewEditor, public IControlRigEditor`  
_L28-30_
- inherits: `FRigVMNewEditor,IControlRigEditor`

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Public/IControlRigEditorModule.h` (Public)


#### class `FControlRigClassFilter`  
`class FControlRigClassFilter : public IClassViewerFilter`  
_L24-40_
- inherits: `IClassViewerFilter`
- L27 _public prototype_ `FControlRigClassFilter(bool bInCheckSkeleton, bool bInCheckAnimatable, bool bInCheckInversion, USkeleton* InSkeleton);`
- L28 _public prototype_ `virtual bool IsClassAllowed(const FClassViewerInitializationOptions& InInitOptions, const UClass* InClass, TSharedRef< FClassViewerFilterFuncs > InFilterFuncs) override;`
- L29 _public prototype_ `virtual bool IsUnloadedClassAllowed(const FClassViewerInitializationOptions& InInitOptions, const TSharedRef< const IUnloadedBlueprintData > InUnloadedClassData, TSharedRef< FClassViewerFilterFuncs > InFilterFuncs) override;`
- L31 _public prototype_ `virtual bool MatchesFilter(const FAssetData& AssetData);`
- L34 _private member_ `bool bFilterAssetBySkeleton;`
- L35 _private member_ `bool bFilterExposesAnimatableControls;`
- L36 _private member_ `bool bFilterInversion;`
- L38 _private member_ `USkeleton* Skeleton;`
- L39 _private member_ `const IAssetRegistry& AssetRegistry;`

#### class `IControlRigEditorModule`  
`class IControlRigEditorModule : public FRigVMEditorModule`  
_L42-73_
- inherits: `FRigVMEditorModule`
- L46 _public function_ `static IControlRigEditorModule& Get()`
- L60 _public prototype_ `virtual TSharedRef<IControlRigEditor> CreateControlRigEditor(const EToolkitMode::Type Mode, const TSharedPtr<IToolkitHost>& InitToolkitHost, UControlRigBlueprint* Blueprint) = 0;` — Creates an instance of a Control Rig editor. @param	Mode					Mode that this editor should operate in @param	InitToolkitHost			When Mode is WorldCentric, this is the level editor instance to spawn this editor within @param	Blueprint				The blueprint object to start editing. @return	Interface to the new Control Rig editor
- L71 _public prototype_ `virtual TSharedRef<IControlRigEditor> CreateControlRigEditor(const EToolkitMode::Type Mode, const TSharedPtr<IToolkitHost>& InitToolkitHost, UControlRigRuntimeAsset* Asset) = 0;` — Creates an instance of a Control Rig editor. @param	Mode					Mode that this editor should operate in @param	InitToolkitHost			When Mode is WorldCentric, this is the level editor instance to spawn this editor within @param	Asset					The control rig asset to start editing. @return	Interface to the new Control Rig editor

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API CONTROLRIGEDITOR_API`
- L15 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogControlRigEditor, Log, All);`
- L15 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogControlRigEditor, Log, All);`

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Public/RigSpacePickerBakeSettings.h` (Public)


#### struct `FRigSpacePickerBakeSettings`  
`struct FRigSpacePickerBakeSettings`  
_L12-47_
- reflection: `USTRUCT(BlueprintType)`
- L16 _public function_ `FRigSpacePickerBakeSettings()`
- L27 _public member_ `FRigElementKey TargetSpace;` — `UPROPERTY(BlueprintReadWrite, Category = "Settings")`
- L30 _public member_ `FBakingAnimationKeySettings Settings;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Bake", meta = (ShowOnlyInnerProperties))`
- L34 _public member_ `FFrameNumber StartFrame_DEPRECATED;` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "Use Settings.StartFrame instead"))` — DEPRECATED 5.3
- L38 _public member_ `FFrameNumber EndFrame_DEPRECATED;` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "Use Settings.EndFrame instead"))` — DEPRECATED 5.3
- L42 _public member_ `bool bReduceKeys_DEPRECATED;` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "Use Settings.bReduceKeys instead"))` — DEPRECATED 5.3
- L46 _public member_ `float Tolerance_DEPRECATED;` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "Use Settings.Tolerance instead"))` — DEPRECATED 5.3

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Public/Sequencer/AnimationAuthoringSettings.h` (Public)


#### class `UAnimationAuthoringSettings`  
`class UAnimationAuthoringSettings : public UDeveloperSettings`  
_L13-27_
- reflection: `UCLASS(MinimalAPI, config=EditorPerProjectUserSettings, meta = (DisplayName = "Animation Authoring Settings"))`
- inherits: `UDeveloperSettings`
- L21 _public member_ `bool bAutoKeyOnRelease = true;` — `UPROPERTY(config, EditAnywhere, Category = Interaction)` — Whether controls' keyframes should be added on release only.
- L23 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnUpdateSettings, const UAnimationAuthoringSettings*);`
- L24 _public member_ `static FOnUpdateSettings OnSettingsChange;`
- L26 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API CONTROLRIGEDITOR_API`
- L23 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnUpdateSettings, const UAnimationAuthoringSettings*);`

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Public/Sequencer/EditModeAnimationUtil.h` (Public)


#### class `UE::AnimationEditMode::FCustomMovieSceneRegistry`  
`class FCustomMovieSceneRegistry`  
_L49-78_
- L52 _public prototype_ `~FCustomMovieSceneRegistry() = default;`
- L54 _public prototype_ `static FCustomMovieSceneRegistry& Get();`
- L58 _public function_ `template<typename SequenceType> void RegisterSequence()` — Registers a particular UMovieSceneSequence subclass to support constraints.
- L71 _public prototype_ `bool IsSequenceSupported(const UClass* InSequenceClass) const;` — Whether a particular UMovieSceneSequence subclass is supported.
- L74 _private prototype_ `FCustomMovieSceneRegistry() = default;`
- L77 _private member_ `TSet<UClass*> SupportedSequenceTypes;` — List of supported UMovieSceneSequence classes.

#### struct `UE::AnimationEditMode::FControlKeyframeData`  
`struct FControlKeyframeData`  
_L85-92_
- L88 _public member_ `FTransform LocalTransform = FTransform::Identity;` — Local transform data of the control to be keyed.
- L91 _public member_ `bool bConstraintSpace = false;` — Whether this local transform represents a constraint space local transform.

#### struct `UE::AnimationEditMode::FControlRigKeyframer`  
`struct FControlRigKeyframer`  
_L101-150_
- L103 _public prototype_ `~FControlRigKeyframer();`
- L106 _public prototype_ `void Initialize();` — Initializes this keyframer and bounds it to the animation authoring settings.
- L109 _public prototype_ `void Enable(const bool InEnabled);` — Resets the data storage and enable/disable the keyframer.
- L112 _public prototype_ `bool IsEnabled() const;` — Returns true if enabled.
- L115 _public prototype_ `void Store(const uint32 InControlHash, FControlKeyframeData&& InData);` — Stores the keyframe data for a specific control.
- L118 _public prototype_ `void Apply(const FControlRigInteractionScope& InInteractionScope, const FControlRigInteractionTransformContext& InTransformContext);` — Does the actual work off adding keyframes to the controls currently interacting.
- L121 _public prototype_ `void Finalize(UWorld* InWorld);` — Updates whatever needs to once the keyframes have been added (updating constraints is one of them).
- L124 _public prototype_ `void Reset();` — Empties the storage.
- L129 _private member_ `TMap<uint32, FControlKeyframeData> KeyframeData;` — Storage representing keyframe data per control.
- L140 _private prototype_ `FRIEND_ENUM_CLASS_FLAGS(EEnableState)`
- L146 _private member_ `FDelegateHandle OnAnimSettingsChanged;` — Handle to UAnimationAuthoringSettings::OnSettingsChange delegate.
- L149 _private prototype_ `void OnSettingsChanged(const UAnimationAuthoringSettings* InSettings);` — Used to track changes to animation authoring settings.

#### enum `UE::AnimationEditMode::FControlRigKeyframer::EEnableState`  
`enum class EEnableState : uint8`  
_L132-139_
- desc: Current state of the keyframer
- L134 _public enumerator_ `Disabled = 0x000` — Keyframing disabled
- L135 _public enumerator_ `EnabledDirectly = 0x001` — Keyframing enabled via code
- L136 _public enumerator_ `EnabledBySettings = 0x002` — Keyframing enabled by settings
- L138 _public enumerator_ `FullyEnabled = EnabledDirectly | EnabledBySettings`

#### struct `UE::AnimationEditMode::FComponentDependency`  
`struct FComponentDependency`  
_L156-172_
- L158 _public prototype_ `FComponentDependency(USceneComponent* InComponent, UWorld* InWorld, TransformConstraintUtil::FConstraintsInteractionCache& InCacheRef);`
- L163 _public prototype_ `bool DependsOn(UObject* InObject);` — Returns true if the stored component depends on InObject or one of its children if it's a scene component.
- L167 _private prototype_ `bool IsValid(const UObject* InObject) const;`
- L169 _private member_ `USceneComponent* Component = nullptr;`
- L170 _private member_ `UWorld* World = nullptr;`
- L171 _private member_ `TransformConstraintUtil::FConstraintsInteractionCache& ConstraintsCache;`

#### struct `UE::AnimationEditMode::FDirectControl`  
`struct FDirectControl`  
_L184-264_
- L186 _public prototype_ `~FDirectControl();`
- L189 _public prototype_ `void Bind(const FEditorModeTools* InModeTools);` — Binds to the given editor mode tools (stores a weak reference to the gizmo context).
- L192 _public prototype_ `void UnBind();` — Removes all delegates and resets all states.
- L195 _public member_ `TFunction<bool (HHitProxy*)> HitProxyFilterFunction;` — Optional extra filter (return false to reject a hit proxy from triggering selection).
- L198 _public member_ `bool bHasTransformChanged = false;` — Set externally to indicate the transform was modified during the current interaction.
- L201 _public member_ `TFunction<TSharedPtr<ISequencer>()> SequencerFunction;` — Optional function returning the active sequencer (if any).
- L204 _public prototype_ `void Reset(const bool bAlsoResetHit = true);` — Clears transient interaction state flags (bAlsoResetHit is true (default), also clears CachedId).
- L209 _private prototype_ `void UnselectAll();` — Deselects all actors.
- L212 _private prototype_ `bool IsAnythingSelected() const;` — Returns true if any actor is currently selected.
- L215 _private prototype_ `HHitProxy* RequestNewHitProxy(const FInputDeviceRay& InRay) const;` — Queries and returns the hit proxy at the given screen-space ray position from the focused viewport.
- L218 _private prototype_ `void ProcessClick(const FKey& InKey, const EInputEvent& InEvent, const FInputDeviceRay& InRay, HHitProxy* InHitProxy) const;` — Forwards a click event to the viewport client at the given ray's screen position.
- L221 _private member_ `bool bHasSelected = false;` — Tracks whether a selection was made by the direct control system.
- L224 _private member_ `bool bProcessing = false;` — Indicates that the direct control system is actively processing a gizmo interaction.
- L227 _private member_ `FTypedHandleCombinedId CachedId = 0;` — Caches the element handle ID of the last selected hit proxy to avoid redundant selection changes across interaction callbacks.
- L230 _private prototype_ `UTransformGizmo* FindGizmo() const;` — Finds and returns the default transform gizmo from the mode tools' interactive tools context, or nullptr if not found.
- L233 _private prototype_ `void BindGizmo(UTransformGizmo* InGizmo);` — Registers pre and post-interaction delegates.
- L236 _private prototype_ `FEditorModeTools* GetModeTools() const;` — Returns the editor mode tools pointer (or nullptr if no longer valid).
- L239 _private prototype_ `FEditorViewportClient* GetViewportClient() const;` — Returns the focused viewport client from the editor mode tools (or nullptr if unavailable).
- L242 _private prototype_ `bool IsHitProxyValidForSelection(HHitProxy* InHitProxy) const;` — Returns true if the hit proxy represents a selectable element.
- L245 _private member_ `TWeakObjectPtr<UEditorTransformGizmoContextObject> WeakContext = nullptr;` — Weak pointer to the gizmo context.
- L248 _private member_ `FDelegateHandle PreInteractionHandle;` — Delegate handle for the transform gizmo's OnPreCanInteract event, used to trigger selection before the gizmo begins interacting.
- L251 _private prototype_ `void OnPreCanGizmoInteract(const FGizmoInteractionDescription& InDesc);` — Function bound to the transform gizmo's OnPreCanInteract event, used to trigger selection before the gizmo begins interacting.
- L254 _private member_ `FDelegateHandle PostInteractionHandle;` — Delegate handle for the transform gizmo's OnPostInteraction event, used to clean up selection state after the gizmo finishes interacting.
- L257 _private prototype_ `void OnGizmoPostInteract(const FGizmoInteractionDescription& InDesc);` — Function bound to the transform gizmo's OnPostInteraction event, used to clean up selection state after the gizmo finishes interacting.
- L260 _private member_ `FDelegateHandle GizmoChangeHandle;` — Delegate handle to listen to TRS gizmo activation / deactivation.
- L263 _private member_ `FDelegateHandle GizmoCreatedHandle;` — Delegate handle to listen to TRS gizmo creation

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API CONTROLRIGEDITOR_API`
- L30 _namespace_ `namespace UE`
- L30 _namespace_ `namespace TransformConstraintUtil` (scope `UE`)
- L35 _namespace_ `namespace UE`
- L35 _namespace_ `namespace AnimationEditMode` (scope `UE`)
- L39 _prototype_ `TWeakPtr<ISequencer> GetSequencer();` (scope `UE::AnimationEditMode`) — Returns the current sequencer.

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Public/Tools/BakingHelper.h` (Public)


#### struct `FBakingHelper`  
`struct FBakingHelper`  
_L13-15_

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Public/Tools/ConstraintBaker.h` (Public)


#### struct `FConstraintBaker`  
`struct FConstraintBaker`  
_L20-60_
- L24 _public prototype_ `static void Bake( UWorld* InWorld, UTickableTransformConstraint* InConstraint, const TSharedPtr<ISequencer>& InSequencer, const TOptional< FBakingAnimationKeySettings>& InSettings, const TOptional<TArray<FFrameNumber>>& InFrames);` — Bake constraint over specified frames, frames must be in order
- L32 _public prototype_ `static bool BakeMultiple( UWorld* InWorld, TArray< UTickableTransformConstraint*>& InConstraints, const TSharedPtr<ISequencer>& InSequencer, const FBakingAnimationKeySettings& Settings);` — Bake Multiple Constraints using settings
- L41 _private prototype_ `static void GetMinimalFramesToBake( UWorld* InWorld, const UTickableTransformConstraint* InConstraint, const TSharedPtr<ISequencer>& InSequencer, UMovieSceneSection* InSection, const TOptional< FBakingAnimationKeySettings>& Settings, TArray<FFrameNumber>& OutFramesToBake);` — Computes the minimal frames to bake for that constraint.
- L50 _private prototype_ `static void DeleteTransformKeysInActiveRanges( const TArrayView<FMovieSceneFloatChannel*>& InFloatTransformChannels, const TArrayView<FMovieSceneDoubleChannel*>& InDoubleTransformChannels, const EMovieSceneTransformChannel& InChannels, const TArray<FFrameNumber>& InFramesToBake, const TArrayView<const FFrameNumber>& InConstraintFrames, const TArray<bool>& InConstraintValues);` — Delete the handle's transform keys within active ranges.
- L59 _private prototype_ `static void CleanupConstraintKeys(FConstraintAndActiveChannel& InOutActiveChannel);` — Removes unnecessary inactive keys to ensure the cleanest possible active channel once baked

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Public/Tools/ControlRigPoseThumbnailRenderer.h` (Public)


#### class `UControlRigPoseThumbnailRenderer`  
`class UControlRigPoseThumbnailRenderer : public UDefaultSizedThumbnailRenderer`  
_L20-37_
- reflection: `UCLASS(config = Editor, MinimalAPI)`
- inherits: `UDefaultSizedThumbnailRenderer`
- L25 _private prototype_ `virtual bool CanVisualizeAsset(UObject* Object) override;`
- L26 _private prototype_ `virtual void Draw(UObject* Object, int32 X, int32 Y, uint32 Width, uint32 Height, FRenderTarget*, FCanvas* Canvas, bool bAdditionalViewFamily) override;`
- L30 _private prototype_ `virtual void BeginDestroy() override;` — UObject Implementation
- L34 _private member_ `FControlRigPoseThumbnailScene* ThumbnailScene;`
- L36 _protected member_ `UControlRigPoseAsset* ControlRigPoseAsset;`

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Public/Tools/ControlRigSnapSettings.h` (Public)


#### class `UControlRigSnapSettings`  
`class UControlRigSnapSettings : public UObject`  
_L16-59_
- reflection: `UCLASS(MinimalAPI, config = EditorPerProjectUserSettings)`
- inherits: `UObject`
- L22 _public prototype_ `UControlRigSnapSettings();`
- L26 _public member_ `bool bKeepOffset = false;` — `UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category = "Snap Settings", meta = (ToolTip = "When snapping keep offset, if false snap completely"))` — When snapping keep offset, If false snap completely
- L30 _public member_ `bool bSnapPosition = true;` — `UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category = "Snap Settings", meta = (ToolTip = "When snapping, also snap position"))` — When snapping, also snap position
- L34 _public member_ `bool bSnapRotation = false;` — `UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category = "Snap Settings", meta = (ToolTip = "When snapping, also snap rotation"))` — When snapping, also snap rotation
- L38 _public member_ `bool bSnapScale = false;` — `UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category = "Snap Settings", meta = (ToolTip = "When snapping, also snap scale"))` — When snapping, also snap scale
- L41 _public member_ `EBakingKeySettings BakingKeySettings = EBakingKeySettings::KeysOnly;` — `UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category = "Bake")`
- L44 _public member_ `int32 FrameIncrement = 1;` — `UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category = "Bake", meta = (ClampMin = "1", UIMin = "1", EditCondition = "BakingKeySettings == EBakingKeySettings::AllFrames"))`
- L47 _public member_ `bool bReduceKeys = false;` — `UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category = "Bake", meta = (EditCondition = "BakingKeySettings == EBakingKeySettings::AllFrames"))`
- L50 _public member_ `float Tolerance = 0.001f;` — `UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category = "Bake", meta = (EditCondition = "BakingKeySettings == EBakingKeySettings::AllFrames || bReduceKeys"))`
- L56 _protected prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API CONTROLRIGEDITOR_API`

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Public/Tools/ControlRigSnapper.h` (Public)


#### struct `FControlRigForWorldTransforms`  
`struct FControlRigForWorldTransforms`  
_L20-29_
- reflection: `USTRUCT(BlueprintType)`
- desc: Specification containing a Control Rig and a list of selected Controls we use to get World Transforms for Snapping.
- L24 _public function_ `FControlRigForWorldTransforms() : ControlRig(nullptr)`
- L26 _public member_ `TWeakObjectPtr<UControlRig> ControlRig;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Control Rig")`
- L28 _public member_ `TArray<FName> ControlNames;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Control Rig")`

#### struct `FControlRigSnapperSelection`  
`struct FControlRigSnapperSelection`  
_L33-46_
- reflection: `USTRUCT(BlueprintType)`
- desc: Selection from the UI to Snap To. Contains a set of Actors and/or Control Rigs to snap onto or from.
- L38 _public member_ `TArray<FActorForWorldTransforms> Actors;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Selection")`
- L40 _public member_ `TArray<FControlRigForWorldTransforms> ControlRigs;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Selection")`
- L42 _public function_ `bool IsValid() const`
- L43 _public prototype_ `FText GetName() const;`
- L44 _public prototype_ `int32 NumSelected() const;`
- L45 _public function_ `void Clear()`

#### struct `FControlRigSnapper`  
`struct FControlRigSnapper`  
_L50-95_
- L55 _public prototype_ `TWeakPtr<ISequencer> GetSequencer();` — Get Current Active Sequencer in the Level.
- L65 _public prototype_ `bool SnapIt(FFrameNumber StartFrame, FFrameNumber EndFrame, const FControlRigSnapperSelection& ChildrenToSnap, const FControlRigSnapperSelection& ParentToSnap, const UControlRigSnapSettings* SnapSettings);` — Snap the passed in children over the start and end frames. @param StartFrame Start of the snap interval. @param EndFrame End of the snap interval. @param ChildrenToSnap The children to snap over the interval. Will set a key per frame on them. @param ParentToSnap  The parent to snap to. @param SnapSettings The settings to use.
- L78 _public prototype_ `bool GetControlRigControlTransforms(ISequencer* Sequencer, UControlRig* ControlRig, const FName& ControlName, const TArray<FFrameNumber>& Frames, const TArray<FTransform>& ParentTransforms, TArray<FTransform>& OutTransforms);` — Get the ControlRig Transforms for current Sequencer @param Sequencer Sequencer Evaluating @param ControlRig The Control Rig to evaluate @param ControlName The name of the Control to get. @param Frames  The times to get the transforms. @param ParentTransforms List of Parent Transforms for each time that the resulting transforms will be concatenated to. @param OutTransforms  Results
- L92 _public prototype_ `bool GetControlRigControlTransforms(UWorld* World, ULevelSequence* LevelSequence, UControlRig* ControlRig, const FName& ControlName,const TArray<FFrameNumber>& Frames, const TArray<FTransform>& ParentTransforms, TArray<FTransform>& OutTransforms);` — Get the ControlRig Transforms from specified MovieSceneSequence. This will create a new player to evalaute so can be used on MovieSceneSequence that isn't in the scene @param World Active World @param LevelSequence LevelSequence Evaluating @param ControlRig The Control Rig to evaluate @param ControlName The name of the Control to get. @param Frames  The times to get the transforms. @param ParentTransforms List of Parent Transforms for each time that the resulting transforms will be concatenated to. @param OutTransforms  Results

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Public/Tools/CreateControlAssetRigSettings.h` (Public)


#### class `UCreateControlPoseAssetRigSettings`  
`class UCreateControlPoseAssetRigSettings : public UObject`  
_L15-26_
- reflection: `UCLASS(BlueprintType, config = EditorSettings)`
- inherits: `UObject`
- L18 _public prototype_ `UCreateControlPoseAssetRigSettings(const FObjectInitializer& Initializer);`
- L24 _public member_ `FString AssetName;` — `UPROPERTY(EditAnywhere, Category = "Control Pose")` — Asset Name

### `Plugins/Animation/ControlRig/Source/ControlRigEditor/Public/Tools/EvaluateSequencerTools.h` (Public)


#### struct `UE::AIE::FFrameTimeByIndex`  
`struct FFrameTimeByIndex`  
_L43-121_
- desc: Specify a range of time using start time and a frame step with accessors to get the index from the time, and the time from the index
- L45 _public member_ `FFrameNumber StartFrame;`
- L46 _public member_ `FFrameNumber EndFrame;`
- L47 _public member_ `FFrameNumber FrameStep;`
- L48 _public member_ `int32 NumFrames;`
- L49 _public function_ `FFrameTimeByIndex() : StartFrame(0), EndFrame(0), FrameStep(0), NumFrames(0)`
- L55 _public prototype_ `FFrameTimeByIndex(const FFrameTimeByIndex& Index) = default;`
- L57 _public function_ `FFrameTimeByIndex(const FFrameNumber& InStartFrame, const FFrameNumber& InFrameStep, const int32 InNumFrames) : StartFrame(InStartFrame), FrameStep(InFrameStep), NumFrames(InNumFrames)`
- L65 _public function_ `FFrameTimeByIndex(const FFrameNumber& InStartFrame, const FFrameNumber& InEndFrame, const FFrameNumber& InFrameStep) : StartFrame(InStartFrame), FrameStep(InFrameStep)`
- L74 _public function_ `FFrameNumber CalculateFrame(int32 Index) const`
- L79 _public function_ `int32 CalculateIndex(const FFrameNumber& InCurrentFrame) const`
- L95 _public function_ `TArray<int32> GetFullIndexArray() const`
- L108 _public function_ `TArray<FFrameNumber> GetFullFrameArray() const`

#### struct `UE::AIE::FArrayOfTransforms`  
`struct FArrayOfTransforms`  
_L124-141_
- desc: Array of transforms, that maybe be sparse with only some transforms set
- L126 _public member_ `TArray<FTransform> Transforms;`
- L127 _public function_ `void SetNum(int32 InNum)`
- L131 _public function_ `int32 Num() const`
- L135 _public function_ `FTransform& operator[](int32 Index)`
- L140 _public prototype_ `FTransform Interp(const FFrameNumber& InTime, const TArray<int32>& ValidIndices, const TArray<FFrameNumber>& ValidTimes);` — interpolate with sparse set of indices

#### struct `UE::AIE::FActorAndWorldTransforms`  
`struct FActorAndWorldTransforms`  
_L144-178_
- desc: An 'Actor'(which may be an AActor/SceneComponent/Socket) and a set of sparse world transforms with corrensonding parent transforms
- L146 _public function_ `FActorAndWorldTransforms()`
- L148 _public function_ `FActorAndWorldTransforms(TSharedPtr<FArrayOfTransforms>& InWorldTransforms, TSharedPtr<FArrayOfTransforms>& InParentTransforms) : WorldTransforms(InWorldTransforms), ParentTransforms(InParentTransforms)`
- L151 _public member_ `FActorForWorldTransforms Actor;`
- L152 _public member_ `TSharedPtr<FArrayOfTransforms> WorldTransforms;`
- L153 _public member_ `TSharedPtr<FArrayOfTransforms> ParentTransforms;`
- L155 _public function_ `void MakeCopy(FActorAndWorldTransforms& OutCopy) const`
- L167 _public function_ `void SetNumOfTransforms(int32 Num)`

#### struct `UE::AIE::FControlRigAndWorldTransforms`  
`struct FControlRigAndWorldTransforms`  
_L181-226_
- desc: A Control rig with a set of Controls
- L183 _public function_ `void AddWorldTransform(bool but, TSharedPtr<FArrayOfTransforms>& InWorldTransforms)`
- L187 _public function_ `void AddWorldTransform(const FName& InName, TSharedPtr<FArrayOfTransforms>& InWorldTransforms)`
- L192 _public function_ `void SetNumOfTransforms(int32 Num)`
- L207 _public function_ `void MakeCopy(FControlRigAndWorldTransforms& OutCopy) const`
- L222 _public member_ `TWeakObjectPtr<UControlRig> ControlRig;`
- L223 _public member_ `TSharedPtr<FArrayOfTransforms > ParentTransforms;`
- L224 _public member_ `TMap<FName, TSharedPtr<FArrayOfTransforms>> ControlAndWorldTransforms;` — one for each control in the FControlRigAndWorldTransform

#### struct `UE::AIE::FSetTransformHelpers`  
`struct FSetTransformHelpers`  
_L228-242_
- L231 _public prototype_ `static bool SetConstrainedTransform(FTransform LocalTransform, UControlRig* ControlRig, FRigControlElement* ControlElement, const FRigControlModifiedContext& Context);` — get a copy of a transform and possibly use it to set a constrainted transform on a control, if this happens it returns true
- L233 _public prototype_ `static void SetControlTransform(const FEulerTransform& LocalTransform, UControlRig* ControlRig, FRigControlElement* ControlElement, const FRigControlModifiedContext& Context);` — set a control transform from a local transform, will set a constrainted transform if one is needed, otherwise will just set a normal one.
- L235 _public prototype_ `static void SetControlGlobalTransform(const FTransform& GlobalTransform, UControlRig* ControlRig, FRigControlElement* ControlElement, const FRigControlModifiedContext& Context);` — set a control transform from a global transform, will call SetControlTransform but handles doing the converstion to local space
- L239 _public prototype_ `static bool SetActorTransform(ISequencer* Sequencer, USceneComponent* SceneComponent, UMovieScene3DTransformSection* TransformSection, const TArray<FFrameNumber>& Frames, const TArray<FTransform>& WorldTransformsToSnapTo, const TArray<FTransform>& ParentWorldTransforms);` — set a set of tranfsorms on an scene component, will handle constraints

#### struct `UE::AIE::FSequencerTransformDependencies`  
`struct FSequencerTransformDependencies`  
_L248-276_
- desc: Calculates for a set of tracks under an actor in sequencer the set of dependencies that it requires to caluclate it's transform, so parent actors, attachments/constraints etc. This is somewhat similar to what you would calculate with a DAG to figure out dependencies but since we don't have a DAG we need to do this manually by walking parents/tracks. It will also calcualate the corresponding UMovieSceneSignedObject FGuid signatures, which will then be used to determine if we need to recalculate an objects tranforms, like with motion trails since some downstream dependency has changed.
- L252 _public prototype_ `static TArray<UMovieSceneTrack*> GetTransformAffectingTracks(UMovieScene* InMovieScene, const FMovieSceneBinding& Binding);` — Get the list of tracks in the moviescene with this binding that may effect the final transform of something in the binding. Currently it will return a set of transform, control rig, attachment, path and  skeletal anim tracks.
- L255 _public prototype_ `void CalculateDependencies(ISequencer* InSequencer, AActor* InActor, TArray<UMovieSceneTrack*>& InTracks);` — Main function to calculate the dependencies for an actor and a set of tracks under that actor
- L257 _public prototype_ `bool Compare(FSequencerTransformDependencies& CopyInIfDifferent) const;` — Compare 2 set of dependencies to see if they have changed.
- L259 _public prototype_ `void CopyFrom(const FSequencerTransformDependencies& Other);` — Copy other set of dependencies to this one
- L261 _public function_ `bool IsEmpty() const` — If setup or not
- L265 _public member_ `TMap<TWeakObjectPtr<UMovieSceneTrack>, FGuid> Tracks;` — These are the values calculated by CalculateDependents function Track dependencies
- L267 _public member_ `TMap<AActor*, FGuid> SequencerActors;` — Sequencer actor dependencies
- L269 _public member_ `TSet<AActor*> NonSequencerActors;` — Non sequencer actors that this object depends upon
- L271 _private prototype_ `FMovieSceneBinding GetBindingFromTrack(UMovieScene* InMovieScene, UMovieSceneTrack* Track);`
- L272 _private prototype_ `void CalculateTrackDependents(ISequencer* InSequencer, UMovieSceneTrack* InTrack);`
- L274 _private prototype_ `void AddTrack(ISequencer* InSequencer, UMovieSceneTrack* InTrack);` — Add a track to the set of calculated onces and recursively get it's dependencies

#### struct `UE::AIE::FEvalHelpers`  
`struct FEvalHelpers`  
_L278-286_
- L281 _public prototype_ `static bool CalculateWorldTransforms(UWorld* World, ISequencer* Sequencer, const FFrameTimeByIndex& FrameTimeByIndex, const TArray<int32>& Indices, TArray<FActorAndWorldTransforms>& Actors, TMap<UControlRig*, FControlRigAndWorldTransforms>& ControlRigs);` — The main evaluation function to use a sparse set of times and caclculate their world transforms for a set of sequencer actors/control rigs.
- L285 _public prototype_ `static bool EvaluateSequencer(UWorld* World, ISequencer* Sequencer, const TSet<const UMovieSceneTrack*>& RelevantTracks);` — Evaluate sequencer for the relevant tracks, making sure depencencies such as constraints and control rigs also tick

#### struct `UE::AIE::FControlRigAndControlsAndTrack`  
`struct FControlRigAndControlsAndTrack`  
_L288-293_
- L290 _public member_ `UMovieSceneControlRigParameterTrack* Track;`
- L291 _public member_ `UControlRig* ControlRig;`
- L292 _public member_ `TArray<FName> Controls;`

#### struct `UE::AIE::FObjectAndTrack`  
`struct FObjectAndTrack`  
_L295-300_
- L297 _public member_ `UMovieScenePropertyTrack* Track;`
- L298 _public member_ `UObject* BoundObject;`
- L299 _public member_ `FGuid SequencerGuid;`

#### struct `UE::AIE::FSequencerSelected`  
`struct FSequencerSelected`  
_L303-307_
- desc: helper to get selected items in sequencer, control rigs and properties
- L305 _public prototype_ `static TArray<FGuid> GetSelectedOutlinerGuids(ISequencer* SequencerPtr);`
- L306 _public prototype_ `static void GetSelectedControlRigsAndBoundObjects(ISequencer* SequencerPtr, TArray<FControlRigAndControlsAndTrack>& OutSelectedCRs, TArray<FObjectAndTrack>& OutBoundObjects);`

#### struct `UE::AIE::FControlRigKeys`  
`struct FControlRigKeys`  
_L310-313_
- desc: get start end times for control sections keys
- L312 _public prototype_ `static bool GetStartEndIndicesForControl(UMovieSceneControlRigParameterSection* BaseSection, const FRigControlElement* ControlElement, int& OutStartIndex, int& OutEndIndex);`

#### struct `UE::AIE::FControlRigWorldTransformProvider`  
`struct FControlRigWorldTransformProvider`  
_L350-362_
- L352 _public prototype_ `FControlRigWorldTransformProvider(AActor* InActor, USceneComponent* InComponent, UControlRig* InControlRig, float InDeltaTime);`
- L354 _public prototype_ `bool IsValid() const;`
- L355 _public prototype_ `FTransform GetTransform(const FName& InControlName, const bool bUpdateAnimation = false) const;`
- L356 _public prototype_ `FTransform GetComponentTransform(const bool bUpdateAnimation = false) const;`
- L358 _public member_ `TWeakObjectPtr<AActor> Actor = nullptr;`
- L359 _public member_ `TWeakObjectPtr<USceneComponent> Component = nullptr;`
- L360 _public member_ `TWeakObjectPtr<UControlRig> ControlRig = nullptr;`
- L361 _public member_ `float DeltaTime = 1.f / 30.f;`

#### Free symbols / members of external scopes

- L16 _macro_ `#define UE_API CONTROLRIGEDITOR_API`
- L32 _namespace_ `namespace UE`
- L34 _namespace_ `namespace AIE` (scope `UE`)
- L316 _function_ `template<typename ChannelType, typename ValueType> void AssigneOrSetValue(ChannelType* Channel, ValueType Value, const FFrameNumber& FrameNumber, EMovieSceneKeyInterpolation DefaultInterpolation)` (scope `UE::AIE`)
- L336 _function_ `template<typename ChannelType, typename ValueType> void SetCurrentKeys(TArrayView<ChannelType*> Channels, int32 StartIndex, int32 EndIndex, EMovieSceneKeyInterpolation DefaultInterpolation, const FFrameNumber& FrameNumber)` (scope `UE::AIE`)
