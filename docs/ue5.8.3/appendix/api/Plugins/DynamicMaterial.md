# Plugins / DynamicMaterial

- module root: `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterial`
- headers: 47; symbols: 1162
- symbol kinds: class=46, delegate=9, enum=10, enumerator=58, function=120, macro=2, member=243, namespace=8, prototype=643, struct=10, variable=13
- PrivateDependencyModuleNames: Engine, Json, JsonUtilities, RenderCore, UnrealEd
- PublicDependencyModuleNames: Core, CoreUObject, DynamicMaterialTextureSet, Slate, SlateCore, UMG

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterial/Public/Components/DMMaterialComponent.h` (Public)


#### enum `EDMComponentLifetimeState`  
`enum class EDMComponentLifetimeState : uint8`  
_L17-22_
- reflection: `UENUM(BlueprintType)`
- L19 _public enumerator_ `Created`
- L20 _public enumerator_ `Added`
- L21 _public enumerator_ `Removed`

#### class `UDMMaterialComponent`  
`class UDMMaterialComponent : public UObject, public FNotifyHook`  
_L28-212_
- reflection: `UCLASS(MinimalAPI, Abstract, BlueprintType, meta = (DisplayName = "Material Designer Component"))`
- inherits: `UObject,FNotifyHook`
- desc: The base class for all material components. Has a few useful things.
- L37 _public prototype_ `static bool CanClean();` — Returns true if we can attempt to un-dirty a component.
- L40 _public prototype_ `static void PreventClean(double InDelayFor = MinTimeBeforeClean);` — Called to prevent cleaning for InDelayFor.
- L43 _public prototype_ `UDMMaterialComponent();`
- L47 _public prototype_ `bool IsComponentValid() const;` — `UFUNCTION(BlueprintPure, Category = "Material Designer")` — Checks object flags and IsValid()
- L51 _public prototype_ `UDMMaterialComponent* GetComponentByPath(const FString& InPath) const;` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")` — Searches the component for a specific component based on a path.
- L54 _public prototype_ `UDMMaterialComponent* GetComponentByPath(FDMComponentPath& InPath) const;` — Searches the component for a specific component based on a path.
- L57 _public function_ `template<typename InComponentClass> UDMMaterialComponent* GetComponentByPath(FDMComponentPath& InPath) const`
- L64 _public prototype_ `virtual void Update(UDMMaterialComponent* InSource, EDMUpdateType InUpdateType);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")` — Event that is triggered when this component, or a sub-component, changes to trigger other updates in the model.
- L69 _public prototype_ `FString GetComponentPath() const;` — `UFUNCTION(BlueprintPure, Category = "Material Designer")` — Returns the complete path from the model to this component.
- L73 _public prototype_ `virtual UDMMaterialComponent* GetParentComponent() const;` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")` — Returns the component that owns this component in the model hierarchy.
- L77 _public prototype_ `UDMMaterialComponent* GetTypedParent(UClass* InParentClass, bool bInAllowSubclasses) const;` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")` — Returns the first in the model hierarchy above this component of the given type.
- L80 _public function_ `template<class InParentClass> InParentClass* GetTypedParent(bool bInAllowSubclasses) const`
- L87 _public prototype_ `virtual FText GetComponentDescription() const;` — `UFUNCTION(BlueprintPure, Category = "Material Designer")` — Returns a description of this class/object.
- L90 _public prototype_ `virtual FSlateIcon GetComponentIcon() const;` — Returns a brush which indicates this component (type)
- L93 _public prototype_ `bool NeedsClean();` — Returns true if this component has been marked dirty.
- L96 _public prototype_ `virtual void DoClean();` — Performs whatever operation is involved in cleaning this component.
- L99 _public function_ `EDMComponentLifetimeState GetComponentState() const` — `UFUNCTION(BlueprintPure, Category = "Material Designer")`
- L103 _public function_ `bool IsComponentCreated() const` — `UFUNCTION(BlueprintPure, Category = "Material Designer")` — Returns true if this component is in the original "Created" state and has not been moved onto Added or Removed.
- L107 _public function_ `bool HasComponentBeenCreated() const` — `UFUNCTION(BlueprintPure, Category = "Material Designer")` — This is a kind of "useless" check, a component has _always_ been created. It's here for completeness.
- L114 _public function_ `bool IsComponentAdded() const` — `UFUNCTION(BlueprintPure, Category = "Material Designer")` — Returns true if this component is in the Added state.
- L118 _public function_ `bool HasComponentBeenAdded() const` — `UFUNCTION(BlueprintPure, Category = "Material Designer")` — Returns true if this component is in the Added or greater state.
- L122 _public function_ `bool IsComponentRemoved() const` — `UFUNCTION(BlueprintPure, Category = "Material Designer")` — Returns true if this component is in the Removed state.
- L126 _public function_ `bool HasComponentBeenRemoved() const` — `UFUNCTION(BlueprintPure, Category = "Material Designer")` — Returns true if this component is in the Removed or greater state.
- L130 _public prototype_ `void SetComponentState(EDMComponentLifetimeState InNewState);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")` — Changes the component state to a new one. Should not be used to set it back to Created.
- L134 _public function_ `const TArray<FName>& GetEditableProperties() const` — `UFUNCTION(BlueprintPure, Category = "Material Designer")` — Returns a list of FNames for this component representing editable UPROPERTYs.
- L138 _public function_ `virtual bool IsPropertyVisible(FName InProperty) const` — `UFUNCTION(BlueprintPure, Category = "Material Designer")` — Returns true the given UPROPERTY name is editable.
- L141 _public prototype_ `virtual FString GetComponentPathComponent() const;` — Returns the part of the component representing just this object
- L144 _public prototype_ `virtual void PostEditorDuplicate(UDynamicMaterialModel* InMaterialModel, UDMMaterialComponent* InParent);` — Called to ensure that the object hierarchy is correct.
- L146 _public function_ `DECLARE_MULTICAST_DELEGATE_ThreeParams( FOnUpdate, UDMMaterialComponent* , UDMMaterialComponent* , EDMUpdateType ) FOnUpdate::RegistrationType& GetOnUpdate()`
- L156 _public function_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnLifetimeStateChanged, UDMMaterialComponent*, EDMComponentLifetimeState) FOnLifetimeStateChanged::RegistrationType& GetOnAdded()`
- L162 _public function_ `FOnLifetimeStateChanged::RegistrationType& GetOnRemoved()` — Event called when this component's state changes to Removed.
- L165 _public prototype_ `virtual bool Modify(bool bInAlwaysMarkDirty = true) override;`
- L166 _public prototype_ `virtual void PostLoad() override;`
- L171 _protected member_ `static const double MinTimeBeforeClean;`
- L172 _protected member_ `static double MinCleanTime;`
- L176 _protected member_ `EDMComponentLifetimeState ComponentState;` — `UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Material Designer")`
- L179 _protected member_ `bool bComponentDirty;` — `UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Transient, Category = "Material Designer")`
- L182 _protected member_ `TArray<FName> EditableProperties;` — `UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Transient, Category = "Material Designer")`
- L184 _protected member_ `FOnUpdate OnUpdate;`
- L185 _protected member_ `FOnLifetimeStateChanged OnAdded;`
- L186 _protected member_ `FOnLifetimeStateChanged OnRemoved;`
- L191 _protected prototype_ `UObject* GetOuterSafe() const;` — `UFUNCTION(BlueprintPure, Category = "Material Designer")` — Does some checks to see whether the out is safe to retrieve and retrieves it.
- L194 _protected prototype_ `virtual UDMMaterialComponent* GetSubComponentByPath(FDMComponentPath& InPath, const FDMComponentPathSegment& InPathSegment) const;` — Searches the component for a specific component based on a path.
- L197 _protected prototype_ `void MarkComponentDirty();` — Marks this component as needed to be cleaned. Preview materials updates, etc.
- L201 _protected prototype_ `virtual void GetComponentPathInternal(TArray<FString>& OutChildComponentPathComponents) const;` — Allows this object to modify the child path when generating a path.
- L204 _protected prototype_ `virtual void OnComponentStateChange(EDMComponentLifetimeState InNewState);` — Called when a component state changes to call the enter state functions.
- L207 _protected prototype_ `virtual void OnComponentAdded();` — Called when a component enters the Added state.
- L210 _protected prototype_ `virtual void OnComponentRemoved();` — Called when a component enters the Removed state.

#### Free symbols / members of external scopes

- L146 _delegate_ `DECLARE_MULTICAST_DELEGATE_ThreeParams( FOnUpdate, UDMMaterialComponent* , UDMMaterialComponent* , EDMUpdateType ) FOnUpdate::RegistrationType& GetOnUpdate() { return OnUpdate; } DECLARE_MULTICAST_DELEGATE_TwoParams(FOnLifetimeStateChanged, UDMMaterialComponent*, EDMComponentLifetimeState) FOnLifetimeStateChanged::RegistrationType& GetOnAdded() { return OnAdded; } FOnLifetimeStateChanged::RegistrationType& GetOnRemoved() { return OnRemoved; }`
- L156 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnLifetimeStateChanged, UDMMaterialComponent*, EDMComponentLifetimeState) FOnLifetimeStateChanged::RegistrationType& GetOnAdded() { return OnAdded; } FOnLifetimeStateChanged::RegistrationType& GetOnRemoved() { return OnRemoved; }`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterial/Public/Components/DMMaterialComponentDynamic.h` (Public)


#### class `UDMMaterialComponentDynamic`  
`class UDMMaterialComponentDynamic : public UDMMaterialComponent`  
_L14-62_
- reflection: `UCLASS(MinimalAPI, BlueprintType, Abstract, ClassGroup = "Material Designer", meta = (DisplayName = "Material Designer Value Instance"))`
- inherits: `UDMMaterialComponent`
- desc: Base version of a dynamic material component. Links to the original in the parent material model.
- L19 _public member_ `static const FString ParentValuePathToken;`
- L25 _public prototype_ `UDMMaterialComponentDynamic();`
- L27 _public prototype_ `virtual ~UDMMaterialComponentDynamic() override = default;`
- L30 _public prototype_ `UDynamicMaterialModelDynamic* GetMaterialModelDynamic() const;` — `UFUNCTION(BlueprintPure, Category = "Material Designer")`
- L33 _public prototype_ `FName GetParentComponentName() const;` — `UFUNCTION(BlueprintPure, Category = "Material Designer")`
- L37 _public prototype_ `UDMMaterialComponent* GeResolvedParentComponent() const;` — `UFUNCTION(BlueprintPure, Category = "Material Designer")` — Resolves and returns the component this dynamic one is based on.
- L41 _public prototype_ `virtual void CopyDynamicPropertiesTo(UDMMaterialComponent* InDestinationComponent) const PURE_VIRTUAL(UDMMaterialComponentDynamic::CopyPropertiesTo) virtual void PostEditorDuplicate(UDynamicMaterialModelDynamic* InMaterialModelDynamic);` — Copies the properties of this dynamic component back to a non-dynamic counterpart.
- L46 _public prototype_ `virtual void BeginDestroy() override;`
- L52 _protected member_ `FName ParentComponentName;` — `UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Material Designer")`
- L55 _protected member_ `TObjectPtr<UDMMaterialComponent> ParentComponent;` — `UPROPERTY(Transient)`
- L57 _protected prototype_ `void ResolveParentComponent();`
- L60 _protected prototype_ `virtual UDMMaterialComponent* GetSubComponentByPath(FDMComponentPath& InPath, const FDMComponentPathSegment& InPathSegment) const override;`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterial/Public/Components/DMMaterialLinkedComponent.h` (Public)


#### class `UDMMaterialLinkedComponent`  
`class UDMMaterialLinkedComponent : public UDMMaterialComponent`  
_L10-32_
- reflection: `UCLASS(MinimalAPI, Abstract, BlueprintType, meta = (DisplayName = "Material Designer Linked Component"))`
- inherits: `UDMMaterialComponent`
- desc: A component which links to a specific parent component in the hierarchy instead of its Outer.
- L17 _public prototype_ `virtual UDMMaterialComponent* GetParentComponent() const override;` — Returns the linked parent component.
- L21 _public prototype_ `void SetParentComponent(UDMMaterialComponent* InParentComponent);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")` — Sets the linked parent component.
- L24 _public prototype_ `virtual void PostEditorDuplicate(UDynamicMaterialModel* InMaterialModel, UDMMaterialComponent* InParent) override;` — Sets the parent component to the InParent parameter.
- L30 _protected member_ `TObjectPtr<UDMMaterialComponent> ParentComponent = nullptr;` — `UPROPERTY()`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterial/Public/Components/DMMaterialParameter.h` (Public)


#### class `UDMMaterialParameter`  
`class UDMMaterialParameter : public UDMMaterialLinkedComponent`  
_L14-55_
- reflection: `UCLASS(MinimalAPI, BlueprintType, meta = (DisplayName = "Material Designer Parameter"))`
- inherits: `UDMMaterialLinkedComponent`
- desc: A parameter on a Material Designer Material.
- L21 _public prototype_ `UDMMaterialParameter();`
- L24 _public prototype_ `UDynamicMaterialModel* GetMaterialModel() const;` — `UFUNCTION(BlueprintPure, Category = "Material Designer")`
- L27 _public function_ `FName GetParameterName() const` — `UFUNCTION(BlueprintPure, Category = "Material Designer")`
- L32 _public prototype_ `void RenameParameter(FName InBaseParameterName);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")` — Changes the parameter name registered with the Model.
- L36 _public prototype_ `virtual void BeginDestroy() override;` — Unregisters the parameter name with the model.
- L40 _public prototype_ `virtual void PostEditorDuplicate(UDynamicMaterialModel* InMaterialModel, UDMMaterialComponent* InParent) override;`
- L46 _protected member_ `FName ParameterName;` — `UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly, Category = "Material Designer")`
- L52 _private prototype_ `virtual void OnComponentRemoved() override;` — Unregisters the parameter name with the model.

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterial/Public/Components/DMMaterialValue.h` (Public)


#### class `UDMMaterialValue`  
`class UDMMaterialValue : public UDMMaterialLinkedComponent, public IDMJsonSerializable, public IDMParameterContainer`  
_L33-219_
- reflection: `UCLASS(MinimalAPI, BlueprintType, Abstract, ClassGroup = "Material Designer", meta = (DisplayName = "Material Designer Value"))`
- inherits: `UDMMaterialLinkedComponent,IDMJsonSerializable,IDMParameterContainer`
- desc: A value used in a material. Manages its own parameter.
- L40 _public member_ `static const FString ParameterPathToken;`
- L44 _public member_ `static const FName ValueName;` — Name that should be used by all child classes for its value property ("Value").
- L48 _public prototype_ `static UDMMaterialValue* CreateMaterialValue(UDynamicMaterialModel* InMaterialModel, const FString& InName, TSubclassOf<UDMMaterialValue> InValueClass, bool bInLocal);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")` — Creates a new material value and initializes it with the given material model.
- L51 _public prototype_ `UDMMaterialValue();`
- L55 _public prototype_ `UDynamicMaterialModel* GetMaterialModel() const;` — `UFUNCTION(BlueprintPure, Category = "Material Designer")` — Returns the owning material model (this object's Outer).
- L59 _public function_ `EDMValueType GetType() const` — `UFUNCTION(BlueprintPure, Category = "Material Designer")` — Returns the type of value as respresented by the possible base type enums.
- L64 _public prototype_ `FText GetTypeName() const;` — `UFUNCTION(BlueprintPure, Category = "Material Designer")` — Uses the Value Definition Library to get the type name of the base enum type.
- L68 _public prototype_ `FText GetDescription() const;` — `UFUNCTION(BlueprintPure, Category = "Material Designer")` — Combination of parameter name and type name. May be an automatically generated parameter name.
- L71 _public function_ `virtual bool IsDefaultValue() const PURE_VIRTUAL(UDMMaterialValue::IsDefaultValue, return false;) bool CanResetToDefault(TSharedPtr<IPropertyHandle> InPropertyHandle) const` — `UFUNCTION(BlueprintPure, Category = "Material Designer")`
- L79 _public prototype_ `virtual void ApplyDefaultValue() PURE_VIRTUAL(UDMMaterialValue::ApplyDefaultValue) virtual void ResetToDefault(TSharedPtr<IPropertyHandle> InPropertyHandle);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")` — Subclasses should implement a SetDefaultValue.
- L87 _public function_ `virtual void ResetDefaultValue() PURE_VIRTUAL(UDMMaterialValue::ResetDefaultValue) #endif UFUNCTION(BlueprintPure, Category = "Material Designer") bool IsLocal() const` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")` — Resets to the default default value. 0, nullptr, etc.
- L96 _public function_ `UDMMaterialParameter* GetParameter() const` — `UFUNCTION(BlueprintPure, Category = "Material Designer")` — Returns the parameter component managed by this value. Will only exist if a parameter name has been set.
- L100 _public prototype_ `FName GetMaterialParameterName() const;` — `UFUNCTION(BlueprintPure, Category = "Material Designer")` — Returns the specifically set parameter name or an automatically generated parameter name.
- L109 _public prototype_ `bool SetParameterName(FName InBaseName);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")` — Sets a specific parameter name, overriding the automatic one if a base name is provided, or resetting back to the original if a base name is not provider (NAME_None). When setting a specific name a parameter component is created and registered with the Model.
- L112 _public prototype_ `EDMMaterialParameterGroup GetParameterGroup() const;` — Determines the group this value's parameter will be in in the Material.
- L115 _public function_ `bool GetShouldExposeParameter() const` — `UFUNCTION(BlueprintPure, Category = "Material Designer")`
- L118 _public prototype_ `void SetShouldExposeParameter(bool bInExpose);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L120 _public prototype_ `virtual void GenerateExpression(const TSharedRef<IDMMaterialBuildStateInterface>& InBuildState) const PURE_VIRTUAL(UDMMaterialStageSource::GenerateExpressions) #endif #if WITH_EDITOR virtual int32 GetInnateMaskOutput(int32 OutputChannels) const;`
- L132 _public function_ `virtual bool IsWholeLayerValue() const` — Return true if, when setting the base stage, the same value should be applied to the mask stage.
- L135 _public function_ `virtual bool AllowEditValue() const` — Returns true if the property row generator should expose the value property.
- L138 _public prototype_ `virtual void SetMIDParameter(UMaterialInstanceDynamic* InMID) const PURE_VIRTUAL(UDMMaterialStageSource::SetMIDParameter) #if WITH_EDITOR virtual UDMMaterialValueDynamic* ToDynamic(UDynamicMaterialModelDynamic* InMaterialModelDynamic) PURE_VIRTUAL(UDMMaterialStageSource::ToDynamic, return nullptr;) #endif`
- L147 _public prototype_ `virtual void PostEditorDuplicate(UDynamicMaterialModel* InMaterialModel, UDMMaterialComponent* InParent) override;`
- L153 _public prototype_ `virtual TSharedPtr<FJsonValue> JsonSerialize() const override;`
- L154 _public prototype_ `virtual bool JsonDeserialize(const TSharedPtr<FJsonValue>& InJsonValue) override;`
- L159 _public prototype_ `virtual bool Modify(bool bInAlwaysMarkDirty = true) override;`
- L160 _public prototype_ `virtual void PostEditUndo() override;`
- L161 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& InPropertyChangedEvent) override;`
- L162 _public prototype_ `virtual void PostCDOContruct() override;`
- L163 _public prototype_ `virtual void PostLoad() override;`
- L164 _public prototype_ `virtual void PostEditImport() override;`
- L169 _protected member_ `static TMap<EDMValueType, TStrongObjectPtr<UClass>> TypeClasses;`
- L172 _protected member_ `EDMValueType Type;` — `UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Material Designer")`
- L179 _protected member_ `bool bLocal;` — `UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Material Designer")` — True: The value is local to the stage it is used in. False: The value is a global value owned directly by the Model.
- L186 _protected member_ `TObjectPtr<UDMMaterialParameter> Parameter;` — `UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Instanced, Category = "Material Designer")` — The parameter name used to expose this value in a material. If it isn't provided, an automatic name will be generated.
- L189 _protected member_ `FName CachedParameterName;` — `UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, DuplicateTransient, TextExportTransient, Category = "Material Designer")`
- L193 _protected member_ `bool bExposeParameter;` — `UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Material Designer")`
- L196 _protected prototype_ `UDMMaterialValue(EDMValueType InType);`
- L199 _protected prototype_ `virtual void OnValueChanged(EDMUpdateType InUpdateType);` — Called when the value changes to call this component's and the parent component's Update if possible.
- L203 _protected prototype_ `FName GenerateAutomaticParameterName() const;` — Generates an automatic path name based on the component hierarchy
- L206 _protected prototype_ `void UpdateCachedParameterName(bool bInResetName);` — Updates the cached parameter name based on the Parameter object or the above method.
- L210 _protected prototype_ `virtual UDMMaterialComponent* GetSubComponentByPath(FDMComponentPath& InPath, const FDMComponentPathSegment& InPathSegment) const override;`
- L215 _protected prototype_ `virtual void OnComponentAdded() override;`
- L216 _protected prototype_ `virtual void OnComponentRemoved() override;`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterial/Public/Components/DMMaterialValueDynamic.h` (Public)


#### class `UDMMaterialValueDynamic`  
`class UDMMaterialValueDynamic : public UDMMaterialComponentDynamic, public IDMJsonSerializable, public IDMParameterContainer`  
_L22-84_
- reflection: `UCLASS(MinimalAPI, BlueprintType, Abstract, ClassGroup = "Material Designer", meta = (DisplayName = "Material Designer Value Instance"))`
- inherits: `UDMMaterialComponentDynamic,IDMJsonSerializable,IDMParameterContainer`
- desc: A value used inside an instanced material instance. Links to the original value in the parent material.
- L29 _public prototype_ `static UDMMaterialValueDynamic* CreateValueDynamic(TSubclassOf<UDMMaterialValueDynamic> InInstanceValueClass, UDynamicMaterialModelDynamic* InMaterialModelDynamic, UDMMaterialValue* InParentValue);` — Creates a value dynamic and initializes it with the given Material Designer Model Dyanmic.
- L33 _public function_ `template<class InValueClass> static InValueClass* CreateValueDynamic(UDynamicMaterialModelDynamic* InMaterialModelDynamic, UDMMaterialValue* InParentValue)`
- L41 _public prototype_ `UDMMaterialValue* GetParentValue() const;` — `UFUNCTION(BlueprintPure, Category = "Material Designer")` — Resolves (if necessary) and returns the value this dynamic value is based on.
- L46 _public function_ `virtual bool IsDefaultValue() const PURE_VIRTUAL(UDMMaterialValue::IsDefaultValue, return false;) bool CanResetToDefault(TSharedPtr<IPropertyHandle> InPropertyHandle) const` — `UFUNCTION(BlueprintPure, Category = "Material Designer")` — Returns true if this value dynamic's value is the same as the parent value's value.
- L51 _public prototype_ `virtual void ApplyDefaultValue() PURE_VIRTUAL(UDMMaterialValue::ApplyDefaultValue) virtual void ResetToDefault(TSharedPtr<IPropertyHandle> InPropertyHandle);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L56 _public prototype_ `virtual void SetMIDParameter(UMaterialInstanceDynamic* InMID) const PURE_VIRTUAL(UDMMaterialValueDynamic::SetMIDParameter)`
- L64 _public prototype_ `virtual TSharedPtr<FJsonValue> JsonSerialize() const override;`
- L65 _public prototype_ `virtual bool JsonDeserialize(const TSharedPtr<FJsonValue>& InJsonValue) override;`
- L70 _public prototype_ `virtual void PostEditUndo() override;`
- L71 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& InPropertyChangedEvent) override;`
- L77 _protected prototype_ `virtual void OnValueChanged();` — Call when this value dynamic changes and calls Update.
- L81 _protected prototype_ `virtual void OnComponentAdded() override;`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterial/Public/Components/DMRenderTargetRenderer.h` (Public)


#### class `UDMRenderTargetRenderer`  
`class UDMRenderTargetRenderer : public UDMMaterialComponent, public IDMJsonSerializable`  
_L16-75_
- reflection: `UCLASS(MinimalAPI, Abstract, BlueprintType, Blueprintable, ClassGroup = "Material Designer", meta = (DisplayName = "Material Designer Render Target Renderer"))`
- inherits: `UDMMaterialComponent,IDMJsonSerializable`
- desc: A component responsible for rendering something to a texture render target (value).
- L21 _public member_ `FDelegateHandle EndOfFrameDelegateHandle;`
- L25 _public prototype_ `static UDMRenderTargetRenderer* CreateRenderTargetRenderer(TSubclassOf<UDMRenderTargetRenderer> InRendererClass, UDMMaterialValueRenderTarget* InRenderTargetValue);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")` — Creates a render of the given class and initializes it.
- L30 _public function_ `static InRendererClass* CreateRenderTargetRenderer(UDMMaterialValueRenderTarget* InRenderTargetValue)`
- L37 _public prototype_ `UDMMaterialValueRenderTarget* GetRenderTargetValue() const;` — `UFUNCTION(BlueprintPure, Category = "Material Designer")` — Returns the render target value (the object's Outer).
- L41 _public prototype_ `void UpdateRenderTarget();` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")` — Updates the contents of the render target, redrawing and possibly resizing it.
- L45 _public prototype_ `void AsyncUpdateRenderTarget();` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")` — Updates the contents of the render target, redrawing and possibly resizing it, at the end of the frame.
- L48 _public prototype_ `void FlushUpdateRenderTarget();` — Will trigger the end of frame update if it is currently queued.
- L52 _public function_ `bool IsUpdating() const` — `UFUNCTION(BlueprintPure, Category = "Material Designer")` — Returns true is this target is currently being re-rendering.
- L55 _public prototype_ `virtual TSharedPtr<FJsonValue> JsonSerialize() const override;`
- L56 _public prototype_ `virtual bool JsonDeserialize(const TSharedPtr<FJsonValue>& InJsonValue) override;`
- L61 _public prototype_ `virtual FText GetComponentDescription() const override;`
- L63 _public prototype_ `virtual void Update(UDMMaterialComponent* InSource, EDMUpdateType InUpdateType) override;`
- L67 _public prototype_ `virtual void PostLoad() override;`
- L71 _protected member_ `bool bUpdating = false;`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterial/Public/Components/DMTextureUV.h` (Public)


#### class `UDMTextureUV`  
`class UDMTextureUV : public UDMMaterialLinkedComponent, public IDMParameterContainer`  
_L54-283_
- reflection: `UCLASS(MinimalAPI, BlueprintType, ClassGroup = "Material Designer", meta = (DisplayName = "Material Designer Texture UV"))`
- inherits: `UDMMaterialLinkedComponent,IDMParameterContainer`
- desc: Represents a Texture UV material function with the following parameters: offset, tiling, pivot and rotation.
- L63 _public member_ `static const FName NAME_UVSource;`
- L64 _public member_ `static const FName NAME_bMirrorOnX;`
- L65 _public member_ `static const FName NAME_bMirrorOnY;`
- L68 _public member_ `static const FName NAME_Offset;`
- L69 _public member_ `static const FName NAME_Pivot;`
- L70 _public member_ `static const FName NAME_Rotation;`
- L71 _public member_ `static const FName NAME_Tiling;`
- L73 _public member_ `static const FString OffsetXPathToken;`
- L74 _public member_ `static const FString OffsetYPathToken;`
- L75 _public member_ `static const FString PivotXPathToken;`
- L76 _public member_ `static const FString PivotYPathToken;`
- L77 _public member_ `static const FString RotationPathToken;`
- L78 _public member_ `static const FString TilingXPathToken;`
- L79 _public member_ `static const FString TilingYPathToken;`
- L81 _public member_ `static const FGuid GUID;`
- L85 _public member_ `static const TMap<FName, bool> TextureProperties;` — The bool is whether or not the property should be exposed to Sequencer as keyable.
- L88 _public prototype_ `static UDMTextureUV* CreateTextureUV(UObject* InOuter);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L91 _public prototype_ `UDMTextureUV();`
- L95 _public member_ `bool bLinkTiling = true;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Material Designer")`
- L99 _public prototype_ `UDynamicMaterialModel* GetMaterialModel() const;` — `UFUNCTION(BlueprintPure, Category = "Material Designer")`
- L103 _public function_ `EDMUVSource GetUVSource() const` — `UFUNCTION(BlueprintPure, Category = "Material Designer")`
- L106 _public prototype_ `void SetUVSource(EDMUVSource InUVSource);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L110 _public function_ `const FVector2D& GetOffset() const` — `UFUNCTION(BlueprintPure, Category = "Material Designer")`
- L113 _public prototype_ `void SetOffset(const FVector2D& InOffset);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L116 _public function_ `const FVector2D& GetPivot() const` — `UFUNCTION(BlueprintPure, Category = "Material Designer")`
- L119 _public prototype_ `void SetPivot(const FVector2D& InPivot);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L122 _public function_ `float GetRotation() const` — `UFUNCTION(BlueprintPure, Category = "Material Designer")`
- L125 _public prototype_ `void SetRotation(float InRotation);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L128 _public function_ `const FVector2D& GetTiling() const` — `UFUNCTION(BlueprintPure, Category = "Material Designer")`
- L131 _public prototype_ `void SetTiling(const FVector2D& InTiling);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L135 _public function_ `bool GetMirrorOnX() const` — `UFUNCTION(BlueprintPure, Category = "Material Designer")`
- L138 _public prototype_ `void SetMirrorOnX(bool bInMirrorOnX);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L141 _public function_ `bool GetMirrorOnY() const` — `UFUNCTION(BlueprintPure, Category = "Material Designer")`
- L144 _public prototype_ `void SetMirrorOnY(bool bInMirrorOnY);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L148 _public prototype_ `TArray<UDMMaterialParameter*> GetParameters() const;` — `UFUNCTION(BlueprintPure, Category = "Material Designer")`
- L151 _public prototype_ `UDMMaterialParameter* GetMaterialParameter(FName InPropertyName, int32 InComponent) const;` — `UFUNCTION(BlueprintPure, Category = "Material Designer")`
- L154 _public prototype_ `FName GetMaterialParameterName(FName InPropertyName, int32 InComponent) const;` — `UFUNCTION(BlueprintPure, Category = "Material Designer")`
- L158 _public prototype_ `bool SetMaterialParameterName(FName InPropertyName, int32 InComponent, FName InNewName);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L160 _public prototype_ `EDMMaterialParameterGroup GetParameterGroup(FName InPropertyName, int32 InComponent) const;`
- L163 _public prototype_ `bool GetShouldExposeParameter(FName InPropertyName, int32 InComponent) const;` — `UFUNCTION(BlueprintPure, Category = "Material Designer")`
- L166 _public prototype_ `void SetShouldExposeParameter(FName InPropertyName, int32 InComponent, bool bInExpose);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L169 _public prototype_ `void SetMIDParameters(UMaterialInstanceDynamic* InMID);`
- L172 _public prototype_ `UDMTextureUVDynamic* ToDynamic(UDynamicMaterialModelDynamic* InMaterialModelDynamic);`
- L177 _public prototype_ `virtual bool Modify(bool bInAlwaysMarkDirty = true) override;`
- L178 _public prototype_ `virtual void PostLoad() override;`
- L179 _public prototype_ `virtual void PostEditImport() override;`
- L180 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& InPropertyChangedEvent) override;`
- L181 _public prototype_ `virtual void PreEditUndo() override;`
- L182 _public prototype_ `virtual void PostEditUndo() override;`
- L184 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L189 _public prototype_ `virtual FString GetComponentPathComponent() const override;`
- L190 _public prototype_ `virtual void PostEditorDuplicate(UDynamicMaterialModel* InMaterialModel, UDMMaterialComponent* InParent) override;`
- L192 _public prototype_ `virtual void Update(UDMMaterialComponent* InSource, EDMUpdateType InUpdateType) override;`
- L196 _protected prototype_ `static int32 PropertyComponentToParamId(FName InPropertyName, int32 InComponent);`
- L201 _protected member_ `EDMUVSource UVSource = EDMUVSource::Texture;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Material Designer|Texture UV", meta = (AllowPrivateAccess = "true", ToolTip = "Forces a material rebuild.", NotKeyframeable))`
- L203 _protected member_ `EDMUVSource UVSource_PreUndo = UVSource;`
- L208 _protected member_ `FVector2D Offset = FVector2D(0.f, 0.f);` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Getter, Setter, BlueprintSetter = SetOffset, Category = "Material Designer|Texture UV", meta = (AllowPrivateAccess = "true", Delta = 0.001))`
- L212 _protected member_ `FVector2D Pivot = FVector2D(0.5, 0.5);` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Getter, Setter, BlueprintSetter = SetPivot, Category = "Material Designer|Texture UV", meta = (AllowPrivateAccess = "true", ToolTip="Pivot for rotation and tiling.", Delta = 0.001))`
- L216 _protected member_ `float Rotation = 0.f;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Getter, Setter, BlueprintSetter = SetRotation, Category = "Material Designer|Texture UV", meta = (AllowPrivateAccess = "true", Delta = 1.0))`
- L220 _protected member_ `FVector2D Tiling = FVector2D(1.f, 1.f);` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Getter, Setter, BlueprintSetter = SetTiling, Category = "Material Designer|Texture UV", meta = (AllowPrivateAccess = "true", AllowPreserveRatio, VectorRatioMode = 3, Delta = 0.001))`
- L224 _protected member_ `FVector2D Scale = FVector2D(1.f, 1.f);` — `UE_DEPRECATED(5.5, "Changed to tiling.")` — `UPROPERTY()`
- L229 _protected member_ `bool bMirrorOnX = false;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Material Designer|Texture UV", meta = (AllowPrivateAccess = "true", ToolTip = "Forces a material rebuild.", NotKeyframeable))`
- L233 _protected member_ `bool bMirrorOnY = false;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Material Designer|Texture UV", meta = (AllowPrivateAccess = "true", ToolTip = "Forces a material rebuild.", NotKeyframeable))`
- L235 _protected member_ `bool bMirrorOnX_PreUndo = bMirrorOnX;`
- L236 _protected member_ `bool bMirrorOnY_PreUndo = bMirrorOnY;`
- L240 _protected member_ `TMap<int32, TObjectPtr<UDMMaterialParameter>> MaterialParameters;` — `UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, DuplicateTransient, TextExportTransient, Category = "Material Designer")`
- L243 _protected member_ `TMap<int32, FName> CachedParameterNames;` — `UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, DuplicateTransient, TextExportTransient, Category = "Material Designer")`
- L246 _protected member_ `TSet<int32> ExposedParameters;` — `UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Material Designer")`
- L249 _protected member_ `bool bNeedsPostLoadValueUpdate = false;`
- L250 _protected member_ `bool bNeedsPostLoadStructureUpdate = false;`
- L252 _protected prototype_ `void RemoveParameterNames();`
- L256 _protected prototype_ `virtual void CopyParametersFrom_Implementation(UObject* InOther) override;`
- L259 _protected prototype_ `void OnTextureUVChanged(EDMUpdateType InUpdateType);`
- L263 _protected prototype_ `FName GenerateAutomaticPathComponent(FName InPropertyName, int32 InComponent) const;` — Generates an automatic path component based on the property name and component.
- L266 _protected prototype_ `FName GenerateAutomaticParameterName(FName InPropertyName, int32 InComponent) const;` — Generates an automatic path name based on the component hierarchy
- L269 _protected prototype_ `void UpdateCachedParameterName(FName InPropertyName, int32 InComponent);` — Update an individual cached parameter name.
- L272 _protected prototype_ `void UpdateCachedParameterNames(bool bInResetNames);` — Updates the cached parameter name based on the Parameter object or the above method.
- L276 _protected prototype_ `virtual UDMMaterialComponent* GetSubComponentByPath(FDMComponentPath& InPath, const FDMComponentPathSegment& InPathSegment) const override;`
- L278 _protected prototype_ `virtual void GetComponentPathInternal(TArray<FString>& OutChildComponentPathComponents) const override;`
- L279 _protected prototype_ `virtual void OnComponentAdded() override;`
- L280 _protected prototype_ `virtual void OnComponentRemoved() override;`

#### Free symbols / members of external scopes

- L31 _namespace_ `namespace UE`
- L31 _namespace_ `namespace DynamicMaterial` (scope `UE`)
- L31 _namespace_ `namespace ParamID` (scope `UE::DynamicMaterial`)
- L34 _variable_ `constexpr int32 Invalid = -1;` (scope `UE::DynamicMaterial::ParamID`) — Individual parameters
- L35 _variable_ `constexpr int32 PivotX = 0;` (scope `UE::DynamicMaterial::ParamID`)
- L36 _variable_ `constexpr int32 PivotY = 1;` (scope `UE::DynamicMaterial::ParamID`)
- L37 _variable_ `constexpr int32 TilingX = 2;` (scope `UE::DynamicMaterial::ParamID`)
- L38 _variable_ `constexpr int32 TilingY = 3;` (scope `UE::DynamicMaterial::ParamID`)
- L39 _variable_ `constexpr int32 Rotation = 4;` (scope `UE::DynamicMaterial::ParamID`)
- L40 _variable_ `constexpr int32 OffsetX = 5;` (scope `UE::DynamicMaterial::ParamID`)
- L41 _variable_ `constexpr int32 OffsetY = 6;` (scope `UE::DynamicMaterial::ParamID`)
- L44 _variable_ `constexpr int32 Pivot = PivotX;` (scope `UE::DynamicMaterial::ParamID`) — Parameter groups
- L45 _variable_ `constexpr int32 Tiling = TilingX;` (scope `UE::DynamicMaterial::ParamID`)
- L47 _variable_ `constexpr int32 Offset = OffsetX;` (scope `UE::DynamicMaterial::ParamID`) — constexpr int32 Rotation = 4; // No additional group value needed

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterial/Public/Components/DMTextureUVDynamic.h` (Public)


#### class `UDMTextureUVDynamic`  
`class UDMTextureUVDynamic : public UDMMaterialComponentDynamic, public IDMParameterContainer`  
_L21-119_
- reflection: `UCLASS(MinimalAPI, BlueprintType, ClassGroup = "Material Designer", meta = (DisplayName = "Material Designer Texture UV Instance"))`
- inherits: `UDMMaterialComponentDynamic,IDMParameterContainer`
- desc: A texture uv used inside a instanced material instance. Links to the original texture uv in the parent material.
- L30 _public prototype_ `static UDMTextureUVDynamic* CreateTextureUVDynamic(UDynamicMaterialModelDynamic* InMaterialModelDynamic, UDMTextureUV* InParentTextureUV);` — Creates a new texture uv dynamic and initializes it with the model dynamic.
- L36 _public prototype_ `UDMTextureUV* GetParentTextureUV() const;` — `UFUNCTION(BlueprintPure, Category = "Material Designer")` — Resolves and returns the parent texture uv from the parent model.
- L40 _public function_ `const FVector2D& GetOffset() const` — `UFUNCTION(BlueprintPure, Category = "Material Designer")` — Returns the dynamic value for this property.
- L44 _public prototype_ `void SetOffset(const FVector2D& InOffset);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")` — Sets the dynamic value for this property.
- L48 _public function_ `const FVector2D& GetPivot() const` — `UFUNCTION(BlueprintPure, Category = "Material Designer")` — Returns the dynamic value for this property.
- L52 _public prototype_ `void SetPivot(const FVector2D& InPivot);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")` — Sets the dynamic value for this property.
- L56 _public function_ `float GetRotation() const` — `UFUNCTION(BlueprintPure, Category = "Material Designer")` — Returns the dynamic value for this property.
- L60 _public prototype_ `void SetRotation(float InRotation);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")` — Sets the dynamic value for this property.
- L64 _public function_ `const FVector2D& GetTiling() const` — `UFUNCTION(BlueprintPure, Category = "Material Designer")` — Returns the dynamic value for this property.
- L68 _public prototype_ `void SetTiling(const FVector2D& InTiling);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")` — Sets the dynamic value for this property.
- L71 _public prototype_ `void SetMIDParameters(UMaterialInstanceDynamic* InMID) const;` — Updates the given MID with the values of this texture uv.
- L75 _public prototype_ `virtual void CopyDynamicPropertiesTo(UDMMaterialComponent* InDestinationComponent) const override;`
- L80 _public prototype_ `virtual void Update(UDMMaterialComponent* InSource, EDMUpdateType InUpdateType = EDMUpdateType::Value) override;`
- L85 _public prototype_ `virtual void PostEditUndo() override;`
- L86 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& InPropertyChangedEvent) override;`
- L93 _protected member_ `FVector2D Offset = FVector2D(0.f, 0.f);` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Getter = GetOffset, Setter = SetOffset, BlueprintSetter = SetOffset, Category = "Material Designer|Texture UV", meta = (AllowPrivateAccess = "true", Delta = 0.001))`
- L97 _protected member_ `FVector2D Pivot = FVector2D(0.5, 0.5);` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Getter = GetPivot, Setter = SetPivot, BlueprintSetter = SetPivot, Category = "Material Designer|Texture UV", meta = (AllowPrivateAccess = "true", ToolTip = "Pivot for rotation and tiling.", Delta = 0.001))`
- L101 _protected member_ `float Rotation = 0.f;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Getter = GetRotation, Setter = SetRotation, BlueprintSetter = SetRotation, Category = "Material Designer|Texture UV", meta = (AllowPrivateAccess = "true", Delta = 1.0))`
- L105 _protected member_ `FVector2D Tiling = FVector2D(1.f, 1.f);` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Getter = GetTiling, Setter = SetTiling, BlueprintSetter = SetTiling, Category = "Material Designer|Texture UV", meta = (AllowPrivateAccess = "true", AllowPreserveRatio, VectorRatioMode = 3, Delta = 0.001))`
- L108 _protected prototype_ `virtual void OnTextureUVChanged();` — Called when any value in this texture uv changes.
- L111 _protected prototype_ `virtual void CopyParametersFrom_Implementation(UObject* InOther) override;`
- L116 _protected prototype_ `virtual void OnComponentAdded() override;`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterial/Public/Components/MaterialValues/DMMaterialValueBool.h` (Public)


#### class `UDMMaterialValueBool`  
`class UDMMaterialValueBool : public UDMMaterialValue`  
_L12-72_
- reflection: `UCLASS(MinimalAPI, BlueprintType, ClassGroup = "Material Designer")`
- inherits: `UDMMaterialValue`
- desc: Component representing a bool value. Manages its own parameter.
- L17 _public prototype_ `UDMMaterialValueBool();`
- L20 _public function_ `bool GetValue() const` — `UFUNCTION(BlueprintPure, Category = "Material Designer")`
- L23 _public prototype_ `void SetValue(bool InValue);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L27 _public function_ `bool GetDefaultValue() const` — `UFUNCTION(BlueprintPure, Category = "Material Designer")`
- L30 _public prototype_ `void SetDefaultValue(bool bInDefaultValue);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L35 _public prototype_ `virtual TSharedPtr<FJsonValue> JsonSerialize() const override;`
- L36 _public prototype_ `virtual bool JsonDeserialize(const TSharedPtr<FJsonValue>& InJsonValue) override;`
- L41 _public prototype_ `virtual void SetMIDParameter(UMaterialInstanceDynamic* InMID) const override;`
- L43 _public prototype_ `virtual void GenerateExpression(const TSharedRef<IDMMaterialBuildStateInterface>& InBuildState) const override;`
- L44 _public prototype_ `virtual bool IsDefaultValue() const override;`
- L45 _public prototype_ `virtual void ApplyDefaultValue() override;`
- L46 _public prototype_ `virtual void ResetDefaultValue() override;`
- L47 _public prototype_ `virtual UDMMaterialValueDynamic* ToDynamic(UDynamicMaterialModelDynamic* InMaterialModelDynamic) override;`
- L53 _public prototype_ `virtual FString GetComponentPathComponent() const override;`
- L54 _public prototype_ `virtual FText GetComponentDescription() const override;`
- L61 _protected member_ `bool Value;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Getter, Setter, BlueprintSetter = SetValue, Category = "Material Designer", meta = (AllowPrivateAccess = "true", DisplayName = "Bool"))`
- L66 _protected member_ `bool bDefaultValue;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, BlueprintSetter = SetDefaultValue, Category = "Material Designer", meta = (AllowPrivateAccess = "true"))`
- L70 _protected prototype_ `virtual void CopyParametersFrom_Implementation(UObject* InOther) override;`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterial/Public/Components/MaterialValues/DMMaterialValueColorAtlas.h` (Public)


#### class `UDMMaterialValueColorAtlas`  
`class UDMMaterialValueColorAtlas : public UDMMaterialValue`  
_L17-99_
- reflection: `UCLASS(MinimalAPI, BlueprintType, ClassGroup = "Material Designer")`
- inherits: `UDMMaterialValue`
- desc: Component representing a color atlas value. Manages its own parameter.
- L22 _public prototype_ `UDMMaterialValueColorAtlas();`
- L25 _public function_ `float GetValue() const` — `UFUNCTION(BlueprintPure, Category = "Material Designer")`
- L28 _public prototype_ `void SetValue(float InValue);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L32 _public function_ `float GetDefaultValue() const` — `UFUNCTION(BlueprintPure, Category = "Material Designer")`
- L35 _public prototype_ `void SetDefaultValue(float InDefaultValue);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L38 _public function_ `UCurveLinearColorAtlas* GetAtlas() const` — `UFUNCTION(BlueprintPure, Category = "Material Designer")`
- L41 _public prototype_ `void SetAtlas(UCurveLinearColorAtlas* InAtlas);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L44 _public function_ `UCurveLinearColor* GetCurve() const` — `UFUNCTION(BlueprintPure, Category = "Material Designer")`
- L47 _public prototype_ `void SetCurve(UCurveLinearColor* InCurve);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L49 _public function_ `virtual bool IsWholeLayerValue() const override`
- L54 _public prototype_ `virtual TSharedPtr<FJsonValue> JsonSerialize() const override;`
- L55 _public prototype_ `virtual bool JsonDeserialize(const TSharedPtr<FJsonValue>& InJsonValue) override;`
- L60 _public prototype_ `virtual void SetMIDParameter(UMaterialInstanceDynamic* InMID) const override;`
- L62 _public prototype_ `virtual void GenerateExpression(const TSharedRef<IDMMaterialBuildStateInterface>& InBuildState) const override;`
- L63 _public prototype_ `virtual bool IsDefaultValue() const override;`
- L64 _public prototype_ `virtual void ApplyDefaultValue() override;`
- L65 _public prototype_ `virtual void ResetDefaultValue() override;`
- L66 _public prototype_ `virtual UDMMaterialValueDynamic* ToDynamic(UDynamicMaterialModelDynamic* InMaterialModelDynamic) override;`
- L72 _public prototype_ `virtual FString GetComponentPathComponent() const override;`
- L73 _public prototype_ `virtual FText GetComponentDescription() const override;`
- L80 _protected member_ `float Value;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Getter, Setter, BlueprintSetter = SetValue, Category = "Material Designer", meta = (DisplayName = "Alpha", AllowPrivateAccess = "true", ClampMin = 0, UIMin = 0, ClampMax = 1, UIMax = 1))`
- L85 _protected member_ `float DefaultValue;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, BlueprintSetter = SetDefaultValue, Category = "Material Designer", meta = (AllowPrivateAccess = "true", ClampMin = 0, UIMin = 0, ClampMax = 1, UIMax = 1))`
- L89 _protected member_ `TObjectPtr<UCurveLinearColorAtlas> Atlas;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, BlueprintSetter = SetAtlas, Category = "Material Designer", meta = (AllowPrivateAccess = "true", NotKeyframeable, NoCreate))`
- L93 _protected member_ `TObjectPtr<UCurveLinearColor> Curve;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, BlueprintSetter = SetCurve, Category = "Material Designer", meta = (AllowPrivateAccess = "true", NotKeyframeable, NoCreate))`
- L97 _protected prototype_ `virtual void CopyParametersFrom_Implementation(UObject* InOther) override;`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterial/Public/Components/MaterialValues/DMMaterialValueFloat.h` (Public)


#### class `UDMMaterialValueFloat`  
`class UDMMaterialValueFloat : public UDMMaterialValue`  
_L12-37_
- reflection: `UCLASS(MinimalAPI, Abstract, BlueprintType, ClassGroup = "Material Designer")`
- inherits: `UDMMaterialValue`
- desc: Base class for float/scalar values in Materials.
- L17 _public prototype_ `UDMMaterialValueFloat();`
- L21 _public function_ `const FFloatInterval& GetValueRange() const` — `UFUNCTION(BlueprintPure, Category = "Material Designer")` — The value range for any float component. If both values are the same, it is not set.
- L25 _public function_ `bool HasValueRange() const` — `UFUNCTION(BlueprintPure, Category = "Material Designer")` — Returns true if a value range has been set. This is true if the min and max aren't the same.
- L29 _public function_ `void SetValueRange(const FFloatInterval& InValueRange)` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")` — Sets the range of possible values. Set min and max to the same to disable.
- L34 _protected member_ `FFloatInterval ValueRange;` — `UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite, Getter, Setter, BlueprintSetter = SetValueRange, Category = "Material Designer", meta = (AllowPrivateAccess = "true", DisplayName = "Value Range"))`
- L36 _protected prototype_ `UDMMaterialValueFloat(EDMValueType InValueType);`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterial/Public/Components/MaterialValues/DMMaterialValueFloat1.h` (Public)


#### class `UDMMaterialValueFloat1`  
`class UDMMaterialValueFloat1 : public UDMMaterialValueFloat`  
_L12-72_
- reflection: `UCLASS(MinimalAPI, BlueprintType, ClassGroup = "Material Designer")`
- inherits: `UDMMaterialValueFloat`
- desc: Component representing a float/scalar value. Manages its own parameter.
- L17 _public prototype_ `UDMMaterialValueFloat1();`
- L20 _public function_ `float GetValue() const` — `UFUNCTION(BlueprintPure, Category = "Material Designer")`
- L23 _public prototype_ `void SetValue(float InValue);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L27 _public function_ `float GetDefaultValue() const` — `UFUNCTION(BlueprintPure, Category = "Material Designer")`
- L30 _public prototype_ `void SetDefaultValue(float InDefaultValue);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L35 _public prototype_ `virtual TSharedPtr<FJsonValue> JsonSerialize() const override;`
- L36 _public prototype_ `virtual bool JsonDeserialize(const TSharedPtr<FJsonValue>& InJsonValue) override;`
- L41 _public prototype_ `virtual void SetMIDParameter(UMaterialInstanceDynamic* InMID) const override;`
- L43 _public prototype_ `virtual void GenerateExpression(const TSharedRef<IDMMaterialBuildStateInterface>& InBuildState) const override;`
- L44 _public prototype_ `virtual bool IsDefaultValue() const override;`
- L45 _public prototype_ `virtual void ApplyDefaultValue() override;`
- L46 _public prototype_ `virtual void ResetDefaultValue() override;`
- L47 _public prototype_ `virtual UDMMaterialValueDynamic* ToDynamic(UDynamicMaterialModelDynamic* InMaterialModelDynamic) override;`
- L53 _public prototype_ `virtual FString GetComponentPathComponent() const override;`
- L54 _public prototype_ `virtual FText GetComponentDescription() const override;`
- L61 _protected member_ `float Value;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Getter, Setter, BlueprintSetter = SetValue, Category = "Material Designer", meta = (AllowPrivateAccess = "true"), DisplayName = "Float")`
- L66 _protected member_ `float DefaultValue;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, BlueprintSetter = SetDefaultValue, Category = "Material Designer", meta = (AllowPrivateAccess = "true"))`
- L70 _protected prototype_ `virtual void CopyParametersFrom_Implementation(UObject* InOther) override;`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterial/Public/Components/MaterialValues/DMMaterialValueFloat2.h` (Public)


#### class `UDMMaterialValueFloat2`  
`class UDMMaterialValueFloat2 : public UDMMaterialValueFloat`  
_L12-74_
- reflection: `UCLASS(MinimalAPI, BlueprintType, ClassGroup = "Material Designer")`
- inherits: `UDMMaterialValueFloat`
- desc: Component representing an FVector2D value. Manages its own parameter.
- L17 _public prototype_ `UDMMaterialValueFloat2();`
- L20 _public function_ `const FVector2D& GetValue() const` — `UFUNCTION(BlueprintPure, Category = "Material Designer")`
- L23 _public prototype_ `void SetValue(const FVector2D& InValue);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L27 _public function_ `const FVector2D& GetDefaultValue() const` — `UFUNCTION(BlueprintPure, Category = "Material Designer")`
- L30 _public prototype_ `void SetDefaultValue(const FVector2D& InDefaultValue);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L35 _public prototype_ `virtual TSharedPtr<FJsonValue> JsonSerialize() const override;`
- L36 _public prototype_ `virtual bool JsonDeserialize(const TSharedPtr<FJsonValue>& InJsonValue) override;`
- L41 _public prototype_ `virtual void SetMIDParameter(UMaterialInstanceDynamic* InMID) const override;`
- L43 _public prototype_ `virtual void GenerateExpression(const TSharedRef<IDMMaterialBuildStateInterface>& InBuildState) const override;`
- L44 _public prototype_ `virtual int32 GetInnateMaskOutput(int32 OutputChannels) const override;`
- L45 _public prototype_ `virtual bool IsDefaultValue() const override;`
- L46 _public prototype_ `virtual void ApplyDefaultValue() override;`
- L47 _public prototype_ `virtual void ResetToDefault(TSharedPtr<IPropertyHandle> InPropertyHandle) override;`
- L48 _public prototype_ `virtual void ResetDefaultValue() override;`
- L49 _public prototype_ `virtual UDMMaterialValueDynamic* ToDynamic(UDynamicMaterialModelDynamic* InMaterialModelDynamic) override;`
- L55 _public prototype_ `virtual FString GetComponentPathComponent() const override;`
- L56 _public prototype_ `virtual FText GetComponentDescription() const override;`
- L63 _protected member_ `FVector2D Value;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Getter, Setter, BlueprintSetter = SetValue, Category = "Material Designer", meta = (AllowPrivateAccess = "true", DisplayName = "Vector2D", Delta = 0.001))`
- L68 _protected member_ `FVector2D DefaultValue;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, BlueprintSetter = SetDefaultValue, Category = "Material Designer", meta = (AllowPrivateAccess = "true"))`
- L72 _protected prototype_ `virtual void CopyParametersFrom_Implementation(UObject* InOther) override;`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterial/Public/Components/MaterialValues/DMMaterialValueFloat3RGB.h` (Public)


#### class `UDMMaterialValueFloat3RGB`  
`class UDMMaterialValueFloat3RGB : public UDMMaterialValueFloat`  
_L12-74_
- reflection: `UCLASS(MinimalAPI, BlueprintType, ClassGroup = "Material Designer")`
- inherits: `UDMMaterialValueFloat`
- desc: Component representing an FLinearColor (no alpha) value. Manages its own parameter.
- L17 _public prototype_ `UDMMaterialValueFloat3RGB();`
- L20 _public function_ `const FLinearColor& GetValue() const` — `UFUNCTION(BlueprintPure, Category = "Material Designer")`
- L23 _public prototype_ `void SetValue(const FLinearColor& InValue);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L27 _public function_ `const FLinearColor& GetDefaultValue() const` — `UFUNCTION(BlueprintPure, Category = "Material Designer")`
- L30 _public prototype_ `void SetDefaultValue(const FLinearColor& InDefaultValue);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L35 _public prototype_ `virtual TSharedPtr<FJsonValue> JsonSerialize() const override;`
- L36 _public prototype_ `virtual bool JsonDeserialize(const TSharedPtr<FJsonValue>& InJsonValue) override;`
- L41 _public prototype_ `virtual void SetMIDParameter(UMaterialInstanceDynamic* InMID) const override;`
- L43 _public prototype_ `virtual void GenerateExpression(const TSharedRef<IDMMaterialBuildStateInterface>& InBuildState) const override;`
- L44 _public prototype_ `virtual int32 GetInnateMaskOutput(int32 OutputChannels) const override;`
- L45 _public prototype_ `virtual bool IsDefaultValue() const override;`
- L46 _public prototype_ `virtual void ApplyDefaultValue() override;`
- L47 _public prototype_ `virtual void ResetToDefault(TSharedPtr<IPropertyHandle> InPropertyHandle) override;`
- L48 _public prototype_ `virtual void ResetDefaultValue() override;`
- L49 _public prototype_ `virtual UDMMaterialValueDynamic* ToDynamic(UDynamicMaterialModelDynamic* InMaterialModelDynamic) override;`
- L55 _public prototype_ `virtual FString GetComponentPathComponent() const override;`
- L56 _public prototype_ `virtual FText GetComponentDescription() const override;`
- L63 _protected member_ `FLinearColor Value;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Getter, Setter, BlueprintSetter = SetValue, Category = "Material Designer", meta = (AllowPrivateAccess = "true", DisplayName = "Color", HideAlphaChannel))`
- L68 _protected member_ `FLinearColor DefaultValue;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, BlueprintSetter = SetDefaultValue, Category = "Material Designer", meta = (AllowPrivateAccess = "true", HideAlphaChannel))`
- L72 _protected prototype_ `virtual void CopyParametersFrom_Implementation(UObject* InOther) override;`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterial/Public/Components/MaterialValues/DMMaterialValueFloat3RPY.h` (Public)


#### class `UDMMaterialValueFloat3RPY`  
`class UDMMaterialValueFloat3RPY : public UDMMaterialValueFloat`  
_L12-74_
- reflection: `UCLASS(MinimalAPI, BlueprintType, ClassGroup = "Material Designer")`
- inherits: `UDMMaterialValueFloat`
- desc: Component representing an FRotator value. Manages its own parameter.
- L17 _public prototype_ `UDMMaterialValueFloat3RPY();`
- L20 _public function_ `const FRotator& GetValue() const` — `UFUNCTION(BlueprintPure, Category = "Material Designer")`
- L23 _public prototype_ `void SetValue(const FRotator& InValue);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L27 _public function_ `const FRotator& GetDefaultValue() const` — `UFUNCTION(BlueprintPure, Category = "Material Designer")`
- L30 _public prototype_ `void SetDefaultValue(const FRotator& InDefaultValue);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L35 _public prototype_ `virtual TSharedPtr<FJsonValue> JsonSerialize() const override;`
- L36 _public prototype_ `virtual bool JsonDeserialize(const TSharedPtr<FJsonValue>& InJsonValue) override;`
- L41 _public prototype_ `virtual void SetMIDParameter(UMaterialInstanceDynamic* InMID) const override;`
- L43 _public prototype_ `virtual void GenerateExpression(const TSharedRef<IDMMaterialBuildStateInterface>& InBuildState) const override;`
- L44 _public prototype_ `virtual int32 GetInnateMaskOutput(int32 OutputChannels) const override;`
- L45 _public prototype_ `virtual bool IsDefaultValue() const override;`
- L46 _public prototype_ `virtual void ApplyDefaultValue() override;`
- L47 _public prototype_ `virtual void ResetToDefault(TSharedPtr<IPropertyHandle> InPropertyHandle) override;`
- L48 _public prototype_ `virtual void ResetDefaultValue() override;`
- L49 _public prototype_ `virtual UDMMaterialValueDynamic* ToDynamic(UDynamicMaterialModelDynamic* InMaterialModelDynamic) override;`
- L55 _public prototype_ `virtual FString GetComponentPathComponent() const override;`
- L56 _public prototype_ `virtual FText GetComponentDescription() const override;`
- L63 _protected member_ `FRotator Value;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Getter, Setter, BlueprintSetter = SetValue, Category = "Material Designer", meta = (AllowPrivateAccess = "true", DisplayName = "Rotation"))`
- L68 _protected member_ `FRotator DefaultValue;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintSetter = SetDefaultValue, Category = "Material Designer", meta = (AllowPrivateAccess = "true"))`
- L72 _protected prototype_ `virtual void CopyParametersFrom_Implementation(UObject* InOther) override;`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterial/Public/Components/MaterialValues/DMMaterialValueFloat3XYZ.h` (Public)


#### class `UDMMaterialValueFloat3XYZ`  
`class UDMMaterialValueFloat3XYZ : public UDMMaterialValueFloat`  
_L12-74_
- reflection: `UCLASS(MinimalAPI, BlueprintType, ClassGroup = "Material Designer")`
- inherits: `UDMMaterialValueFloat`
- desc: Component representing an FVector value. Manages its own parameter.
- L17 _public prototype_ `UDMMaterialValueFloat3XYZ();`
- L20 _public function_ `const FVector& GetValue() const` — `UFUNCTION(BlueprintPure, Category = "Material Designer")`
- L23 _public prototype_ `void SetValue(const FVector& InValue);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L27 _public function_ `const FVector& GetDefaultValue() const` — `UFUNCTION(BlueprintPure, Category = "Material Designer")`
- L30 _public prototype_ `void SetDefaultValue(const FVector& InDefaultValue);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L35 _public prototype_ `virtual TSharedPtr<FJsonValue> JsonSerialize() const override;`
- L36 _public prototype_ `virtual bool JsonDeserialize(const TSharedPtr<FJsonValue>& InJsonValue) override;`
- L41 _public prototype_ `virtual void SetMIDParameter(UMaterialInstanceDynamic* InMID) const override;`
- L43 _public prototype_ `virtual void GenerateExpression(const TSharedRef<IDMMaterialBuildStateInterface>& InBuildState) const override;`
- L44 _public prototype_ `virtual int32 GetInnateMaskOutput(int32 OutputChannels) const override;`
- L45 _public prototype_ `virtual bool IsDefaultValue() const override;`
- L46 _public prototype_ `virtual void ApplyDefaultValue() override;`
- L47 _public prototype_ `virtual void ResetToDefault(TSharedPtr<IPropertyHandle> InPropertyHandle) override;`
- L48 _public prototype_ `virtual void ResetDefaultValue() override;`
- L49 _public prototype_ `virtual UDMMaterialValueDynamic* ToDynamic(UDynamicMaterialModelDynamic* InMaterialModelDynamic) override;`
- L55 _public prototype_ `virtual FString GetComponentPathComponent() const override;`
- L56 _public prototype_ `virtual FText GetComponentDescription() const override;`
- L63 _protected member_ `FVector Value;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Getter, Setter, BlueprintSetter = SetValue, Category = "Material Designer", meta = (AllowPrivateAccess = "true", DisplayName = "Vector3D"))`
- L68 _protected member_ `FVector DefaultValue;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintSetter = SetDefaultValue, meta = (AllowPrivateAccess = "true"), Category = "Material Designer")`
- L72 _protected prototype_ `virtual void CopyParametersFrom_Implementation(UObject* InOther) override;`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterial/Public/Components/MaterialValues/DMMaterialValueFloat4.h` (Public)


#### class `UDMMaterialValueFloat4`  
`class UDMMaterialValueFloat4 : public UDMMaterialValueFloat`  
_L12-75_
- reflection: `UCLASS(MinimalAPI, BlueprintType, ClassGroup = "Material Designer")`
- inherits: `UDMMaterialValueFloat`
- desc: Component representing a float4 value. Manages its own parameter.
- L17 _public prototype_ `UDMMaterialValueFloat4();`
- L20 _public function_ `const FLinearColor& GetValue() const` — `UFUNCTION(BlueprintPure, Category = "Material Designer")`
- L23 _public prototype_ `void SetValue(const FLinearColor& InValue);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L27 _public function_ `const FLinearColor& GetDefaultValue() const` — `UFUNCTION(BlueprintPure, Category = "Material Designer")`
- L30 _public prototype_ `void SetDefaultValue(const FLinearColor& InDefaultValue);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L35 _public prototype_ `virtual TSharedPtr<FJsonValue> JsonSerialize() const override;`
- L36 _public prototype_ `virtual bool JsonDeserialize(const TSharedPtr<FJsonValue>& InJsonValue) override;`
- L41 _public prototype_ `virtual void SetMIDParameter(UMaterialInstanceDynamic* InMID) const override;`
- L43 _public prototype_ `virtual void GenerateExpression(const TSharedRef<IDMMaterialBuildStateInterface>& InBuildState) const override;`
- L44 _public prototype_ `virtual int32 GetInnateMaskOutput(int32 OutputChannels) const override;`
- L45 _public prototype_ `virtual bool IsDefaultValue() const override;`
- L46 _public prototype_ `virtual void ApplyDefaultValue() override;`
- L47 _public prototype_ `virtual void ResetDefaultValue() override;`
- L48 _public prototype_ `virtual void ResetToDefault(TSharedPtr<IPropertyHandle> InPropertyHandle) override;`
- L49 _public function_ `virtual bool IsWholeLayerValue() const override`
- L50 _public prototype_ `virtual UDMMaterialValueDynamic* ToDynamic(UDynamicMaterialModelDynamic* InMaterialModelDynamic) override;`
- L56 _public prototype_ `virtual FString GetComponentPathComponent() const override;`
- L57 _public prototype_ `virtual FText GetComponentDescription() const override;`
- L64 _protected member_ `FLinearColor Value;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Getter, Setter, BlueprintSetter = SetValue, Category = "Material Designer", meta = (AllowPrivateAccess = "true", DisplayName = "Color"))`
- L69 _protected member_ `FLinearColor DefaultValue;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintSetter = SetDefaultValue, Category = "Material Designer", meta = (AllowPrivateAccess = "true"))`
- L73 _protected prototype_ `virtual void CopyParametersFrom_Implementation(UObject* InOther) override;`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterial/Public/Components/MaterialValues/DMMaterialValueRenderTarget.h` (Public)


#### class `UDMMaterialValueRenderTarget`  
`class UDMMaterialValueRenderTarget : public UDMMaterialValueTexture`  
_L18-131_
- reflection: `UCLASS(MinimalAPI, BlueprintType, ClassGroup = "Material Designer")`
- inherits: `UDMMaterialValueTexture`
- desc: Component representing a render target texture value. Manages its own parameter.
- L23 _public member_ `static const FString RendererPathToken;`
- L25 _public prototype_ `UDMMaterialValueRenderTarget();`
- L30 _public prototype_ `UTextureRenderTarget2D* GetRenderTarget() const;` — `UFUNCTION(BlueprintPure, Category = "Material Designer")`
- L33 _public prototype_ `const FIntPoint& GetTextureSize() const;` — `UFUNCTION(BlueprintPure, Category = "Material Designer")`
- L36 _public prototype_ `void SetTextureSize(const FIntPoint& InTextureSize);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L39 _public prototype_ `ETextureRenderTargetFormat GetTextureFormat() const;` — `UFUNCTION(BlueprintPure, Category = "Material Designer")`
- L42 _public prototype_ `void SetTextureFormat(ETextureRenderTargetFormat InTextureFormat);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L45 _public prototype_ `const FLinearColor& GetClearColor() const;` — `UFUNCTION(BlueprintPure, Category = "Material Designer")`
- L48 _public prototype_ `void SetClearColor(const FLinearColor& InClearColor);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L51 _public prototype_ `UDMRenderTargetRenderer* GetRenderer() const;` — `UFUNCTION(BlueprintPure, Category = "Material Designer")`
- L54 _public prototype_ `void SetRenderer(UDMRenderTargetRenderer* InRenderer);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L60 _public prototype_ `void EnsureRenderTarget(bool bInAsync = false);` — Allows outside objects to ensure our render target is valid. @param bInAsync If true, will create the render target on end of frame.
- L63 _public prototype_ `void FlushCreateRenderTarget();` — Will trigger the end of frame update if it is currently queued or is invalid
- L67 _public prototype_ `virtual void CopyParametersFrom_Implementation(UObject* InOther) override;`
- L71 _public prototype_ `virtual TSharedPtr<FJsonValue> JsonSerialize() const override;`
- L72 _public prototype_ `virtual bool JsonDeserialize(const TSharedPtr<FJsonValue>& InJsonValue) override;`
- L77 _public function_ `virtual bool AllowEditValue() const override` — Render target is handled internally.
- L78 _public prototype_ `virtual UDMMaterialValueDynamic* ToDynamic(UDynamicMaterialModelDynamic* InMaterialModelDynamic) override;`
- L83 _public prototype_ `virtual void Update(UDMMaterialComponent* InSource, EDMUpdateType InUpdateType) override;`
- L85 _public prototype_ `virtual FString GetComponentPathComponent() const override;`
- L86 _public prototype_ `virtual FText GetComponentDescription() const override;`
- L87 _public prototype_ `virtual void PostEditorDuplicate(UDynamicMaterialModel* InMaterialModel, UDMMaterialComponent* InParent) override;`
- L93 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& InPropertyChangedEvent) override;`
- L95 _public prototype_ `virtual void PostLoad() override;`
- L101 _protected member_ `FIntPoint TextureSize;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Setter = SetTextureSize, BlueprintSetter = SetTextureSize, Category = "Material Designer|Render Target", meta = (AllowPrivateAccess = "true", NotKeyframeable))`
- L105 _protected member_ `TEnumAsByte<ETextureRenderTargetFormat> TextureFormat;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Setter = SetTextureFormat, BlueprintSetter = SetTextureFormat, Category = "Material Designer|Render Target", meta = (AllowPrivateAccess = "true", NotKeyframeable))`
- L109 _protected member_ `FLinearColor ClearColor;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Setter = SetClearColor, BlueprintSetter = SetClearColor, Category = "Material Designer|Render Target", meta = (AllowPrivateAccess = "true", NotKeyframeable))`
- L113 _protected member_ `TObjectPtr<UDMRenderTargetRenderer> Renderer;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Setter = SetRenderer, BlueprintSetter = SetRenderer, Category = "Material Designer", meta = (AllowPrivateAccess = "true", NotKeyframeable, NoCreate))`
- L116 _protected member_ `FDelegateHandle EndOfFrameDelegateHandle;` — Used to asynchronously update the render target.
- L118 _protected prototype_ `void AsyncCreateRenderTarget();`
- L120 _protected prototype_ `void CreateRenderTarget();`
- L122 _protected prototype_ `void UpdateRenderTarget();`
- L125 _protected prototype_ `virtual UDMMaterialComponent* GetSubComponentByPath(FDMComponentPath& InPath, const FDMComponentPathSegment& InPathSegment) const override;`
- L127 _protected prototype_ `virtual void OnComponentAdded() override;`
- L128 _protected prototype_ `virtual void OnComponentRemoved() override;`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterial/Public/Components/MaterialValues/DMMaterialValueTexture.h` (Public)


#### class `UDMMaterialValueTexture`  
`class UDMMaterialValueTexture : public UDMMaterialValue`  
_L24-107_
- reflection: `UCLASS(MinimalAPI, BlueprintType, ClassGroup = "Material Designer")`
- inherits: `UDMMaterialValue`
- desc: Component representing a texture value. Manages its own parameter.
- L29 _public prototype_ `UDMMaterialValueTexture();`
- L32 _public member_ `static FDMGetDefaultRGBTexture GetDefaultRGBTexture;`
- L35 _public prototype_ `static UDMMaterialValueTexture* CreateMaterialValueTexture(UObject* InOuter, UTexture* InTexture);` — `UFUNCTION(BlueprintPure, Category = "Material Designer")`
- L39 _public function_ `UTexture* GetValue() const` — `UFUNCTION(BlueprintPure, Category = "Material Designer")`
- L42 _public prototype_ `void SetValue(UTexture* InValue);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L47 _public prototype_ `bool HasAlpha() const;` — `UFUNCTION(BlueprintPure, Category = "Material Designer")` — Return true if the texture value has an alpha channel.
- L50 _public function_ `UTexture* GetDefaultValue() const` — `UFUNCTION(BlueprintPure, Category = "Material Designer")`
- L53 _public prototype_ `void SetDefaultValue(UTexture* InDefaultValue);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L58 _public prototype_ `virtual TSharedPtr<FJsonValue> JsonSerialize() const override;`
- L59 _public prototype_ `virtual bool JsonDeserialize(const TSharedPtr<FJsonValue>& InJsonValue) override;`
- L64 _public prototype_ `virtual void SetMIDParameter(UMaterialInstanceDynamic* InMID) const override;`
- L66 _public prototype_ `virtual void GenerateExpression(const TSharedRef<IDMMaterialBuildStateInterface>& InBuildState) const override;`
- L67 _public prototype_ `virtual bool IsDefaultValue() const override;`
- L68 _public prototype_ `virtual void ApplyDefaultValue() override;`
- L69 _public prototype_ `virtual void ResetDefaultValue() override;`
- L70 _public prototype_ `virtual UDMMaterialValueDynamic* ToDynamic(UDynamicMaterialModelDynamic* InMaterialModelDynamic) override;`
- L76 _public prototype_ `virtual FString GetComponentPathComponent() const override;`
- L77 _public prototype_ `virtual FText GetComponentDescription() const override;`
- L83 _public prototype_ `virtual void PreEditChange(FProperty* InPropertyAboutToChange) override;`
- L84 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& InPropertyChangedEvent) override;`
- L86 _public prototype_ `virtual void PostLoad() override;`
- L92 _protected member_ `TObjectPtr<UTexture> Value;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, NoClear, Getter, Setter, BlueprintSetter = SetValue, Category = "Material Designer", meta = (DisplayThumbnail = true, DisplayName = "Texture", AllowPrivateAccess = "true", HighPriority, NoCreate))`
- L97 _protected member_ `TObjectPtr<UTexture> DefaultValue;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintSetter = SetDefaultValue, Category = "Material Designer", meta = (AllowPrivateAccess = "true"))`
- L101 _protected member_ `TObjectPtr<UTexture> OldValue;` — `UPROPERTY()` — Used for PostEditChangeProperty
- L105 _protected prototype_ `virtual void CopyParametersFrom_Implementation(UObject* InOther) override;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace DynamicMaterial` (scope `UE`)
- L11 _namespace_ `namespace Private` (scope `UE::DynamicMaterial`)
- L14 _prototype_ `bool HasAlpha(UTexture* InTexture);` (scope `UE::DynamicMaterial::Private`) — Return true if the texture has an alpha channel.
- L17 _delegate_ `DECLARE_DELEGATE_RetVal(UTexture*, FDMGetDefaultRGBTexture);`
- L17 _prototype_ `DECLARE_DELEGATE_RetVal(UTexture*, FDMGetDefaultRGBTexture);`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterial/Public/Components/MaterialValuesDynamic/DMMaterialValueBoolDynamic.h` (Public)


#### class `UDMMaterialValueBoolDynamic`  
`class UDMMaterialValueBoolDynamic : public UDMMaterialValueDynamic`  
_L12-52_
- reflection: `UCLASS(MinimalAPI, BlueprintType, ClassGroup = "Material Designer")`
- inherits: `UDMMaterialValueDynamic`
- desc: Link to a UDMMaterialValueBool for Material Designer Model Dynamics.
- L17 _public prototype_ `UDMMaterialValueBoolDynamic();`
- L20 _public function_ `bool GetValue() const` — `UFUNCTION(BlueprintPure, Category = "Material Designer")`
- L23 _public prototype_ `void SetValue(bool InValue);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L27 _public prototype_ `bool GetDefaultValue() const;` — `UFUNCTION(BlueprintPure, Category = "Material Designer")`
- L30 _public prototype_ `virtual TSharedPtr<FJsonValue> JsonSerialize() const override;`
- L31 _public prototype_ `virtual bool JsonDeserialize(const TSharedPtr<FJsonValue>& InJsonValue) override;`
- L36 _public prototype_ `virtual void SetMIDParameter(UMaterialInstanceDynamic* InMID) const override;`
- L38 _public prototype_ `virtual bool IsDefaultValue() const override;`
- L39 _public prototype_ `virtual void ApplyDefaultValue() override;`
- L40 _public prototype_ `virtual void CopyDynamicPropertiesTo(UDMMaterialComponent* InDestinationComponent) const override;`
- L47 _protected member_ `bool Value;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Getter, Setter, BlueprintSetter = SetValue, Category = "Material Designer", meta = (AllowPrivateAccess = "true"), DisplayName = "Bool")`
- L50 _protected prototype_ `virtual void CopyParametersFrom_Implementation(UObject* InOther) override;`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterial/Public/Components/MaterialValuesDynamic/DMMaterialValueColorAtlasDynamic.h` (Public)


#### class `UDMMaterialValueColorAtlasDynamic`  
`class UDMMaterialValueColorAtlasDynamic : public UDMMaterialValueDynamic`  
_L12-52_
- reflection: `UCLASS(MinimalAPI, BlueprintType, ClassGroup = "Material Designer")`
- inherits: `UDMMaterialValueDynamic`
- desc: Link to a UDMMaterialValueColorAtlas for Material Designer Model Dynamics.
- L17 _public prototype_ `UDMMaterialValueColorAtlasDynamic();`
- L20 _public function_ `float GetValue() const` — `UFUNCTION(BlueprintPure, Category = "Material Designer")`
- L23 _public prototype_ `void SetValue(float InValue);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L27 _public prototype_ `float GetDefaultValue() const;` — `UFUNCTION(BlueprintPure, Category = "Material Designer")`
- L30 _public prototype_ `virtual TSharedPtr<FJsonValue> JsonSerialize() const override;`
- L31 _public prototype_ `virtual bool JsonDeserialize(const TSharedPtr<FJsonValue>& InJsonValue) override;`
- L36 _public prototype_ `virtual void SetMIDParameter(UMaterialInstanceDynamic* InMID) const override;`
- L38 _public prototype_ `virtual bool IsDefaultValue() const override;`
- L39 _public prototype_ `virtual void ApplyDefaultValue() override;`
- L40 _public prototype_ `virtual void CopyDynamicPropertiesTo(UDMMaterialComponent* InDestinationComponent) const override;`
- L47 _protected member_ `float Value;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Getter, Setter, BlueprintSetter = SetValue, Category = "Material Designer", meta = (DisplayName = "Alpha", AllowPrivateAccess = "true", ClampMin = 0, UIMin = 0, ClampMax = 1, UIMax = 1))`
- L50 _protected prototype_ `virtual void CopyParametersFrom_Implementation(UObject* InOther) override;`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterial/Public/Components/MaterialValuesDynamic/DMMaterialValueFloat1Dynamic.h` (Public)


#### class `UDMMaterialValueFloat1Dynamic`  
`class UDMMaterialValueFloat1Dynamic : public UDMMaterialValueDynamic`  
_L12-52_
- reflection: `UCLASS(MinimalAPI, BlueprintType, ClassGroup = "Material Designer")`
- inherits: `UDMMaterialValueDynamic`
- desc: Link to a UDMMaterialValueFloat1 for Material Designer Model Dynamics.
- L17 _public prototype_ `UDMMaterialValueFloat1Dynamic();`
- L20 _public function_ `float GetValue() const` — `UFUNCTION(BlueprintPure, Category = "Material Designer")`
- L23 _public prototype_ `void SetValue(float InValue);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L27 _public prototype_ `float GetDefaultValue() const;` — `UFUNCTION(BlueprintPure, Category = "Material Designer")`
- L30 _public prototype_ `virtual TSharedPtr<FJsonValue> JsonSerialize() const override;`
- L31 _public prototype_ `virtual bool JsonDeserialize(const TSharedPtr<FJsonValue>& InJsonValue) override;`
- L36 _public prototype_ `virtual void SetMIDParameter(UMaterialInstanceDynamic* InMID) const override;`
- L38 _public prototype_ `virtual bool IsDefaultValue() const override;`
- L39 _public prototype_ `virtual void ApplyDefaultValue() override;`
- L40 _public prototype_ `virtual void CopyDynamicPropertiesTo(UDMMaterialComponent* InDestinationComponent) const override;`
- L47 _protected member_ `float Value;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Getter, Setter, BlueprintSetter = SetValue, Category = "Material Designer", meta = (AllowPrivateAccess = "true"), DisplayName = "Float")`
- L50 _protected prototype_ `virtual void CopyParametersFrom_Implementation(UObject* InOther) override;`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterial/Public/Components/MaterialValuesDynamic/DMMaterialValueFloat2Dynamic.h` (Public)


#### class `UDMMaterialValueFloat2Dynamic`  
`class UDMMaterialValueFloat2Dynamic : public UDMMaterialValueDynamic`  
_L13-54_
- reflection: `UCLASS(MinimalAPI, BlueprintType, ClassGroup = "Material Designer")`
- inherits: `UDMMaterialValueDynamic`
- desc: Link to a UDMMaterialValueFloat2 for Material Designer Model Dynamics.
- L18 _public prototype_ `UDMMaterialValueFloat2Dynamic();`
- L21 _public function_ `const FVector2D& GetValue() const` — `UFUNCTION(BlueprintPure, Category = "Material Designer")`
- L24 _public prototype_ `void SetValue(const FVector2D& InValue);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L28 _public prototype_ `const FVector2D& GetDefaultValue() const;` — `UFUNCTION(BlueprintPure, Category = "Material Designer")`
- L31 _public prototype_ `virtual TSharedPtr<FJsonValue> JsonSerialize() const override;`
- L32 _public prototype_ `virtual bool JsonDeserialize(const TSharedPtr<FJsonValue>& InJsonValue) override;`
- L37 _public prototype_ `virtual void SetMIDParameter(UMaterialInstanceDynamic* InMID) const override;`
- L39 _public prototype_ `virtual bool IsDefaultValue() const override;`
- L40 _public prototype_ `virtual void ApplyDefaultValue() override;`
- L41 _public prototype_ `virtual void ResetToDefault(TSharedPtr<IPropertyHandle> InPropertyHandle);`
- L42 _public prototype_ `virtual void CopyDynamicPropertiesTo(UDMMaterialComponent* InDestinationComponent) const override;`
- L49 _protected member_ `FVector2D Value;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Getter, Setter, BlueprintSetter = SetValue, Category = "Material Designer", meta = (AllowPrivateAccess = "true", DisplayName = "Vector2D", Delta = 0.001))`
- L52 _protected prototype_ `virtual void CopyParametersFrom_Implementation(UObject* InOther) override;`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterial/Public/Components/MaterialValuesDynamic/DMMaterialValueFloat3RGBDynamic.h` (Public)


#### class `UDMMaterialValueFloat3RGBDynamic`  
`class UDMMaterialValueFloat3RGBDynamic : public UDMMaterialValueDynamic`  
_L13-54_
- reflection: `UCLASS(MinimalAPI, BlueprintType, ClassGroup = "Material Designer")`
- inherits: `UDMMaterialValueDynamic`
- desc: Link to a UDMMaterialValue3RGB for Material Designer Model Dynamics.
- L18 _public prototype_ `UDMMaterialValueFloat3RGBDynamic();`
- L21 _public function_ `const FLinearColor& GetValue() const` — `UFUNCTION(BlueprintPure, Category = "Material Designer")`
- L24 _public prototype_ `void SetValue(const FLinearColor& InValue);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L28 _public prototype_ `const FLinearColor& GetDefaultValue() const;` — `UFUNCTION(BlueprintPure, Category = "Material Designer")`
- L31 _public prototype_ `virtual TSharedPtr<FJsonValue> JsonSerialize() const override;`
- L32 _public prototype_ `virtual bool JsonDeserialize(const TSharedPtr<FJsonValue>& InJsonValue) override;`
- L37 _public prototype_ `virtual void SetMIDParameter(UMaterialInstanceDynamic* InMID) const override;`
- L39 _public prototype_ `virtual bool IsDefaultValue() const override;`
- L40 _public prototype_ `virtual void ApplyDefaultValue() override;`
- L41 _public prototype_ `virtual void ResetToDefault(TSharedPtr<IPropertyHandle> InPropertyHandle);`
- L42 _public prototype_ `virtual void CopyDynamicPropertiesTo(UDMMaterialComponent* InDestinationComponent) const override;`
- L49 _protected member_ `FLinearColor Value;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Getter, Setter, BlueprintSetter = SetValue, Category = "Material Designer", meta = (AllowPrivateAccess = "true", DisplayName = "Color", HideAlphaChannel))`
- L52 _protected prototype_ `virtual void CopyParametersFrom_Implementation(UObject* InOther) override;`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterial/Public/Components/MaterialValuesDynamic/DMMaterialValueFloat3RPYDynamic.h` (Public)


#### class `UDMMaterialValueFloat3RPYDynamic`  
`class UDMMaterialValueFloat3RPYDynamic : public UDMMaterialValueDynamic`  
_L13-54_
- reflection: `UCLASS(MinimalAPI, BlueprintType, ClassGroup = "Material Designer")`
- inherits: `UDMMaterialValueDynamic`
- desc: Link to a UDMMaterialValueFloat3RPY for Material Designer Model Dynamics.
- L18 _public prototype_ `UDMMaterialValueFloat3RPYDynamic();`
- L21 _public function_ `const FRotator& GetValue() const` — `UFUNCTION(BlueprintPure, Category = "Material Designer")`
- L24 _public prototype_ `void SetValue(const FRotator& InValue);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L28 _public prototype_ `const FRotator& GetDefaultValue() const;` — `UFUNCTION(BlueprintPure, Category = "Material Designer")`
- L31 _public prototype_ `virtual TSharedPtr<FJsonValue> JsonSerialize() const override;`
- L32 _public prototype_ `virtual bool JsonDeserialize(const TSharedPtr<FJsonValue>& InJsonValue) override;`
- L37 _public prototype_ `virtual void SetMIDParameter(UMaterialInstanceDynamic* InMID) const override;`
- L39 _public prototype_ `virtual bool IsDefaultValue() const override;`
- L40 _public prototype_ `virtual void ApplyDefaultValue() override;`
- L41 _public prototype_ `virtual void ResetToDefault(TSharedPtr<IPropertyHandle> InPropertyHandle);`
- L42 _public prototype_ `virtual void CopyDynamicPropertiesTo(UDMMaterialComponent* InDestinationComponent) const override;`
- L49 _protected member_ `FRotator Value;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Getter, Setter, BlueprintSetter = SetValue, Category = "Material Designer", meta = (AllowPrivateAccess = "true", DisplayName = "Rotation"))`
- L52 _protected prototype_ `virtual void CopyParametersFrom_Implementation(UObject* InOther) override;`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterial/Public/Components/MaterialValuesDynamic/DMMaterialValueFloat3XYZDynamic.h` (Public)


#### class `UDMMaterialValueFloat3XYZDynamic`  
`class UDMMaterialValueFloat3XYZDynamic : public UDMMaterialValueDynamic`  
_L13-54_
- reflection: `UCLASS(MinimalAPI, BlueprintType, ClassGroup = "Material Designer")`
- inherits: `UDMMaterialValueDynamic`
- desc: Link to a UDMMaterialValueFloat3XYZ for Material Designer Model Dynamics.
- L18 _public prototype_ `UDMMaterialValueFloat3XYZDynamic();`
- L21 _public function_ `const FVector& GetValue() const` — `UFUNCTION(BlueprintPure, Category = "Material Designer")`
- L24 _public prototype_ `void SetValue(const FVector& InValue);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L28 _public prototype_ `const FVector& GetDefaultValue() const;` — `UFUNCTION(BlueprintPure, Category = "Material Designer")`
- L31 _public prototype_ `virtual TSharedPtr<FJsonValue> JsonSerialize() const override;`
- L32 _public prototype_ `virtual bool JsonDeserialize(const TSharedPtr<FJsonValue>& InJsonValue) override;`
- L37 _public prototype_ `virtual void SetMIDParameter(UMaterialInstanceDynamic* InMID) const override;`
- L39 _public prototype_ `virtual bool IsDefaultValue() const override;`
- L40 _public prototype_ `virtual void ApplyDefaultValue() override;`
- L41 _public prototype_ `virtual void ResetToDefault(TSharedPtr<IPropertyHandle> InPropertyHandle);`
- L42 _public prototype_ `virtual void CopyDynamicPropertiesTo(UDMMaterialComponent* InDestinationComponent) const override;`
- L49 _protected member_ `FVector Value;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Getter, Setter, BlueprintSetter = SetValue, Category = "Material Designer", meta = (AllowPrivateAccess = "true", DisplayName = "Vector3D", Delta = 0.001))`
- L52 _protected prototype_ `virtual void CopyParametersFrom_Implementation(UObject* InOther) override;`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterial/Public/Components/MaterialValuesDynamic/DMMaterialValueFloat4Dynamic.h` (Public)


#### class `UDMMaterialValueFloat4Dynamic`  
`class UDMMaterialValueFloat4Dynamic : public UDMMaterialValueDynamic`  
_L13-54_
- reflection: `UCLASS(MinimalAPI, BlueprintType, ClassGroup = "Material Designer")`
- inherits: `UDMMaterialValueDynamic`
- desc: Link to a UDMMaterialValueFloat4 for Material Designer Model Dynamics.
- L18 _public prototype_ `UDMMaterialValueFloat4Dynamic();`
- L21 _public function_ `const FLinearColor& GetValue() const` — `UFUNCTION(BlueprintPure, Category = "Material Designer")`
- L24 _public prototype_ `void SetValue(const FLinearColor& InValue);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L28 _public prototype_ `const FLinearColor& GetDefaultValue() const;` — `UFUNCTION(BlueprintPure, Category = "Material Designer")`
- L31 _public prototype_ `virtual TSharedPtr<FJsonValue> JsonSerialize() const override;`
- L32 _public prototype_ `virtual bool JsonDeserialize(const TSharedPtr<FJsonValue>& InJsonValue) override;`
- L37 _public prototype_ `virtual void SetMIDParameter(UMaterialInstanceDynamic* InMID) const override;`
- L39 _public prototype_ `virtual bool IsDefaultValue() const override;`
- L40 _public prototype_ `virtual void ApplyDefaultValue() override;`
- L41 _public prototype_ `virtual void ResetToDefault(TSharedPtr<IPropertyHandle> InPropertyHandle);`
- L42 _public prototype_ `virtual void CopyDynamicPropertiesTo(UDMMaterialComponent* InDestinationComponent) const override;`
- L49 _protected member_ `FLinearColor Value;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Getter, Setter, BlueprintSetter = SetValue, Category = "Material Designer", meta = (AllowPrivateAccess = "true", DisplayName = "Color"))`
- L52 _protected prototype_ `virtual void CopyParametersFrom_Implementation(UObject* InOther) override;`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterial/Public/Components/MaterialValuesDynamic/DMMaterialValueRenderTargetDynamic.h` (Public)


#### class `UDMMaterialValueRenderTargetDynamic`  
`class UDMMaterialValueRenderTargetDynamic : public UDMMaterialValueDynamic`  
_L10-36_
- reflection: `UCLASS(MinimalAPI, BlueprintType, ClassGroup = "Material Designer")`
- inherits: `UDMMaterialValueDynamic`
- desc: Skeleton class because this offers no functionality in a dynamic model. Yet.
- L15 _public prototype_ `UDMMaterialValueRenderTargetDynamic();`
- L18 _public prototype_ `virtual void CopyParametersFrom_Implementation(UObject* InOther) override;`
- L23 _public prototype_ `virtual TSharedPtr<FJsonValue> JsonSerialize() const override;`
- L24 _public prototype_ `virtual bool JsonDeserialize(const TSharedPtr<FJsonValue>& InJsonValue) override;`
- L29 _public prototype_ `virtual void SetMIDParameter(UMaterialInstanceDynamic* InMID) const override;`
- L31 _public prototype_ `virtual bool IsDefaultValue() const override;`
- L32 _public prototype_ `virtual void ApplyDefaultValue() override;`
- L33 _public prototype_ `virtual void CopyDynamicPropertiesTo(UDMMaterialComponent* InDestinationComponent) const override;`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterial/Public/Components/MaterialValuesDynamic/DMMaterialValueTextureDynamic.h` (Public)


#### class `UDMMaterialValueTextureDynamic`  
`class UDMMaterialValueTextureDynamic : public UDMMaterialValueDynamic`  
_L14-54_
- reflection: `UCLASS(MinimalAPI, BlueprintType, ClassGroup = "Material Designer")`
- inherits: `UDMMaterialValueDynamic`
- desc: Link to a UDMMaterialValueTexture for Material Designer Model Dynamics.
- L19 _public prototype_ `UDMMaterialValueTextureDynamic();`
- L22 _public function_ `UTexture* GetValue() const` — `UFUNCTION(BlueprintPure, Category = "Material Designer")`
- L25 _public prototype_ `void SetValue(UTexture* InValue);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L29 _public prototype_ `UTexture* GetDefaultValue() const;` — `UFUNCTION(BlueprintPure, Category = "Material Designer")`
- L32 _public prototype_ `virtual TSharedPtr<FJsonValue> JsonSerialize() const override;`
- L33 _public prototype_ `virtual bool JsonDeserialize(const TSharedPtr<FJsonValue>& InJsonValue) override;`
- L38 _public prototype_ `virtual void SetMIDParameter(UMaterialInstanceDynamic* InMID) const override;`
- L40 _public prototype_ `virtual bool IsDefaultValue() const override;`
- L41 _public prototype_ `virtual void ApplyDefaultValue() override;`
- L42 _public prototype_ `virtual void CopyDynamicPropertiesTo(UDMMaterialComponent* InDestinationComponent) const override;`
- L49 _protected member_ `TObjectPtr<UTexture> Value;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Getter, Setter, BlueprintSetter = SetValue, Category = "Material Designer", meta = (DisplayThumbnail = true, DisplayName = "Texture", AllowPrivateAccess = "true", HighPriority, NoCreate))`
- L52 _protected prototype_ `virtual void CopyParametersFrom_Implementation(UObject* InOther) override;`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterial/Public/Components/RenderTargetRenderers/DMRenderTargetTextRenderer.h` (Public)


#### struct `FDMTextLine`  
`struct FDMTextLine`  
_L24-32_
- reflection: `USTRUCT()`
- L29 _public member_ `FString Line;` — `UPROPERTY()`
- L31 _public member_ `TSharedPtr<STextBlock> Widget;`

#### class `UDMRenderTargetTextRenderer`  
`class UDMRenderTargetTextRenderer : public UDMRenderTargetWidgetRendererBase, public IDMParameterContainer`  
_L38-321_
- reflection: `UCLASS(MinimalAPI, BlueprintType, ClassGroup = "Material Designer", meta = (DisplayName = "Material Designer Render Target Text Renderer"))`
- inherits: `UDMRenderTargetWidgetRendererBase,IDMParameterContainer`
- desc: Renderer that renders an STextBlock widget and exposes all its parameters/properties.
- L45 _public prototype_ `UDMRenderTargetTextRenderer();`
- L48 _public prototype_ `const FSlateFontInfo& GetFontInfo() const;` — `UFUNCTION(BlueprintPure, Category = "Material Designer")`
- L51 _public prototype_ `void SetFontInfo(const FSlateFontInfo& InFontInfo);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L54 _public prototype_ `const FText& GetText() const;` — `UFUNCTION(BlueprintPure, Category = "Material Designer")`
- L57 _public prototype_ `void SetText(const FText& InText);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L60 _public prototype_ `const FLinearColor& GetTextColor() const;` — `UFUNCTION(BlueprintPure, Category = "Material Designer")`
- L63 _public prototype_ `void SetTextColor(const FLinearColor& InColor);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L66 _public prototype_ `const FLinearColor& GetBackgroundColor() const;` — `UFUNCTION(BlueprintPure, Category = "Material Designer")`
- L69 _public prototype_ `void SetBackgroundColor(const FLinearColor& InBackgroundColor);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L72 _public prototype_ `bool GetHasHighlight() const;` — `UFUNCTION(BlueprintPure, Category = "Material Designer")`
- L75 _public prototype_ `void SetHasHighlight(bool bInHasHighlight);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L78 _public prototype_ `const FLinearColor& GetHighlightColor() const;` — `UFUNCTION(BlueprintPure, Category = "Material Designer")`
- L81 _public prototype_ `void SetHighlightColor(const FLinearColor& InHighlightColor);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L84 _public prototype_ `bool GetHasShadow() const;` — `UFUNCTION(BlueprintPure, Category = "Material Designer")`
- L87 _public prototype_ `void SetHasShadow(bool bInHasShadow);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L90 _public prototype_ `const FLinearColor& GetShadowColor() const;` — `UFUNCTION(BlueprintPure, Category = "Material Designer")`
- L93 _public prototype_ `void SetShadowColor(const FLinearColor& InShadowColor);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L96 _public prototype_ `const FVector2D& GetShadowOffset() const;` — `UFUNCTION(BlueprintPure, Category = "Material Designer")`
- L99 _public prototype_ `void SetShadowOffset(const FVector2D& InShadowOffset);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L102 _public prototype_ `bool GetAutoWrapText() const;` — `UFUNCTION(BlueprintPure, Category = "Material Designer")`
- L105 _public prototype_ `void SetAutoWrapText(bool bInAutoWrap);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L108 _public prototype_ `float GetWrapTextAt() const;` — `UFUNCTION(BlueprintPure, Category = "Material Designer")`
- L111 _public prototype_ `void SetWrapTextAt(float InWrapAt);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L114 _public prototype_ `ETextWrappingPolicy GetWrappingPolicy() const;` — `UFUNCTION(BlueprintPure, Category = "Material Designer")`
- L117 _public prototype_ `void SetWrappingPolicy(ETextWrappingPolicy InWrappingPolicy);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L120 _public prototype_ `ETextJustify::Type GetJustify() const;` — `UFUNCTION(BlueprintPure, Category = "Material Designer")`
- L123 _public prototype_ `void SetJustify(ETextJustify::Type InJustify);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L126 _public prototype_ `ETextTransformPolicy GetTransformPolicy() const;` — `UFUNCTION(BlueprintPure, Category = "Material Designer")`
- L129 _public prototype_ `void SetTransformPolicy(ETextTransformPolicy InTransformPolicy);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L132 _public prototype_ `ETextFlowDirection GetFlowDirection() const;` — `UFUNCTION(BlueprintPure, Category = "Material Designer")`
- L135 _public prototype_ `void SetFlowDirection(ETextFlowDirection InFlowDirection);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L138 _public prototype_ `ETextShapingMethod GetShapingMethod() const;` — `UFUNCTION(BlueprintPure, Category = "Material Designer")`
- L141 _public prototype_ `void SetShapingMethod(ETextShapingMethod InShapingMethod);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L144 _public prototype_ `const TInstancedStruct<FSlateBrush>& GetStrikeBrush() const;` — `UFUNCTION(BlueprintPure, Category = "Material Designer")`
- L147 _public prototype_ `void SetStrikeBrush(const TInstancedStruct<FSlateBrush>& InStrikeBrush);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L150 _public prototype_ `float GetLineHeight() const;` — `UFUNCTION(BlueprintPure, Category = "Material Designer")`
- L153 _public prototype_ `void SetLineHeight(float InLineHeight);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L156 _public prototype_ `float GetPaddingLeft() const;` — `UFUNCTION(BlueprintPure, Category = "Material Designer")`
- L159 _public prototype_ `void SetPaddingLeft(float InPadding);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L162 _public prototype_ `float GetPaddingRight() const;` — `UFUNCTION(BlueprintPure, Category = "Material Designer")`
- L165 _public prototype_ `void SetPaddingRight(float InPadding);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L168 _public prototype_ `float GetPaddingTop() const;` — `UFUNCTION(BlueprintPure, Category = "Material Designer")`
- L171 _public prototype_ `void SetPaddingTop(float InPadding);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L174 _public prototype_ `float GetPaddingBottom() const;` — `UFUNCTION(BlueprintPure, Category = "Material Designer")`
- L177 _public prototype_ `void SetPaddingBottom(float InPadding);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L180 _public prototype_ `bool IsOverridingRenderTargetSize() const;` — `UFUNCTION(BlueprintPure, Category = "Material Designer")`
- L183 _public prototype_ `void SetOverrideRenderTargetSize(bool bInOverride);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L187 _public prototype_ `virtual void CopyParametersFrom_Implementation(UObject* InOther) override;`
- L191 _public prototype_ `virtual TSharedPtr<FJsonValue> JsonSerialize() const override;`
- L192 _public prototype_ `virtual bool JsonDeserialize(const TSharedPtr<FJsonValue>& InJsonValue) override;`
- L196 _public prototype_ `virtual FText GetComponentDescription() const override;`
- L200 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& InPropertyChangedEvent) override;`
- L207 _protected member_ `FSlateFontInfo FontInfo;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Getter, Setter, BlueprintSetter = SetFontInfo, Category = "Material Designer|Text", meta = (NotKeyframeable, AllowPrivateAccess = "true"))`
- L211 _protected member_ `FText Text = FText::GetEmpty();` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Getter, Setter, BlueprintSetter = SetText, Category = "Material Designer|Text", meta = (MultiLine, NotKeyframeable, AllowPrivateAccess = "true"))`
- L215 _protected member_ `TArray<FDMTextLine> Lines = {};` — `UPROPERTY()` — Text broken down into individual lines and their corresponding widgets.
- L219 _protected member_ `FLinearColor TextColor = FLinearColor::White;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Getter, Setter, BlueprintSetter = SetTextColor, Category = "Material Designer|Text", meta = (AllowPrivateAccess = "true"))`
- L223 _protected member_ `bool bHasHighlight = false;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Getter = GetHasHighlight, Setter = SetHasHighlight, BlueprintSetter = SetHasHighlight, Category = "Material Designer|Text", meta = (NotKeyframeable, AllowPrivateAccess = "true"))`
- L227 _protected member_ `FLinearColor HighlightColor = FLinearColor::Black;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Getter, Setter, BlueprintSetter = SetHighlightColor, Category = "Material Designer|Text", meta = (AllowPrivateAccess = "true", EditCondition = "bHasHighlight", EditConditionHides = true))`
- L231 _protected member_ `bool bHasShadow = false;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Getter = GetHasShadow, Setter = SetHasShadow, BlueprintSetter = SetHasShadow, Category = "Material Designer|Text", meta = (NotKeyframeable, AllowPrivateAccess = "true"))`
- L235 _protected member_ `FLinearColor ShadowColor = FLinearColor::Black;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Getter, Setter, BlueprintSetter = SetShadowColor, Category = "Material Designer|Text", meta = (AllowPrivateAccess = "true", EditCondition = "bHasShadow", EditConditionHides = true))`
- L239 _protected member_ `FVector2D ShadowOffset = FVector2D(1.0, 1.0);` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Getter, Setter, BlueprintSetter = SetShadowOffset, Category = "Material Designer|Text", meta = (AllowPrivateAccess = "true", EditCondition = "bHasShadow", EditConditionHides = true))`
- L243 _protected member_ `bool bAutoWrapText = false;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Getter = GetAutoWrapText, Setter = SetAutoWrapText, BlueprintSetter = SetAutoWrapText, Category = "Material Designer|Text", meta = (NotKeyframeable, AllowPrivateAccess = "true"))`
- L247 _protected member_ `float WrapTextAt = 0.f;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Getter, Setter, BlueprintSetter = SetWrapTextAt, Category = "Material Designer|Text", meta = (NotKeyframeable, AllowPrivateAccess = "true", EditCondition="bAutoWrapText", EditConditionHides))`
- L251 _protected member_ `ETextWrappingPolicy WrappingPolicy = ETextWrappingPolicy::DefaultWrapping;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Getter, Setter, BlueprintSetter = SetWrappingPolicy, Category = "Material Designer|Text", meta = (NotKeyframeable, AllowPrivateAccess = "true", EditCondition = "bAutoWrapText", EditConditionHides))`
- L255 _protected member_ `TEnumAsByte<ETextJustify::Type> Justify = ETextJustify::Left;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Getter, Setter, BlueprintSetter = SetJustify, Category = "Material Designer|Text", meta = (NotKeyframeable, AllowPrivateAccess = "true"))`
- L259 _protected member_ `ETextTransformPolicy TransformPolicy = ETextTransformPolicy::None;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Getter, Setter, BlueprintSetter = SetTransformPolicy, Category = "Material Designer|Text", meta = (NotKeyframeable, AllowPrivateAccess = "true"))`
- L263 _protected member_ `ETextFlowDirection FlowDirection = ETextFlowDirection::Auto;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Getter, Setter, BlueprintSetter = SetFlowDirection, Category = "Material Designer|Text", meta = (NotKeyframeable, AllowPrivateAccess = "true"))`
- L267 _protected member_ `ETextShapingMethod ShapingMethod = ETextShapingMethod::Auto;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Getter, Setter, BlueprintSetter = SetShapingMethod, Category = "Material Designer|Text", meta = (NotKeyframeable, AllowPrivateAccess = "true"))`
- L271 _protected member_ `TInstancedStruct<FSlateBrush> StrikeBrush;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Getter, Setter, BlueprintSetter = SetStrikeBrush, Category = "Material Designer|Text", meta = (NotKeyframeable, AllowPrivateAccess = "true"))`
- L276 _protected member_ `float LineHeight = 1.f;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Getter, Setter, BlueprintSetter = SetLineHeight, Category = "Material Designer|Text", meta = (AllowPrivateAccess = "true", UIMin = 0.1, UIMax = 2.0))` — Multiplier on the base font height.
- L281 _protected member_ `float PaddingLeft = 0.f;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Getter, Setter, BlueprintSetter = SetPaddingLeft, Category = "Material Designer|Text", meta = (AllowPrivateAccess = "true"))` — Extra space adding beyond the edge of the glyphs. Useful for shadows, glows, etc.
- L286 _protected member_ `float PaddingRight = 0.f;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Getter, Setter, BlueprintSetter = SetPaddingRight, Category = "Material Designer|Text", meta = (AllowPrivateAccess = "true"))` — Extra space adding beyond the edge of the glyphs. Useful for shadows, glows, etc.
- L291 _protected member_ `float PaddingTop = 0.f;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Getter, Setter, BlueprintSetter = SetPaddingTop, Category = "Material Designer|Text", meta = (AllowPrivateAccess = "true"))` — Extra space adding beyond the edge of the glyphs. Useful for shadows, glows, etc.
- L296 _protected member_ `float PaddingBottom = 0.f;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Getter, Setter, BlueprintSetter = SetPaddingBottom, Category = "Material Designer|Text", meta = (AllowPrivateAccess = "true"))` — Extra space adding beyond the edge of the glyphs. Useful for shadows, glows, etc.
- L301 _protected member_ `bool bOverrideRenderTargetSize = true;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Getter = IsOverridingRenderTargetSize, Setter = SetOverrideRenderTargetSize, BlueprintSetter = SetOverrideRenderTargetSize, Category = "Material Designer|Render Target", meta = (NotKeyframeable, AllowPrivateAccess = "true"))` — When true, will change the size of the render target to fit the text.
- L303 _protected member_ `bool bRecalculateTextSize = false;`
- L306 _protected prototype_ `void UpdateTextLines();` — Takes the Text and creates a new TextLines array.
- L309 _protected prototype_ `TSharedRef<STextBlock> CreateTextWidget(const FText& InText) const;` — Creates the widget for an individual line.
- L312 _protected prototype_ `void SetCustomTextureSize();` — Updates the texture size, if needed, for the given text.
- L315 _protected prototype_ `virtual void CreateWidgetInstance() override;`
- L319 _protected prototype_ `virtual void UpdateRenderTarget_Internal() override;`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterial/Public/Components/RenderTargetRenderers/DMRenderTargetUMGWidgetRenderer.h` (Public)


#### class `UDMRenderTargetUMGWidgetRenderer`  
`class UDMRenderTargetUMGWidgetRenderer : public UDMRenderTargetWidgetRendererBase, public IDMParameterContainer`  
_L13-56_
- reflection: `UCLASS(MinimalAPI, BlueprintType, ClassGroup = "Material Designer", meta = (DisplayName = "Material Designer Render Target Widget Renderer"))`
- inherits: `UDMRenderTargetWidgetRendererBase,IDMParameterContainer`
- L18 _public prototype_ `UDMRenderTargetUMGWidgetRenderer();`
- L21 _public function_ `TSubclassOf<UWidget> GetWidgetClass() const` — `UFUNCTION(BlueprintPure, Category = "Material Designer")`
- L24 _public prototype_ `void SetWidgetClass(TSubclassOf<UWidget> InWidgetClass);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")`
- L28 _public prototype_ `virtual void CopyParametersFrom_Implementation(UObject* InOther) override;`
- L32 _public prototype_ `virtual TSharedPtr<FJsonValue> JsonSerialize() const override;`
- L33 _public prototype_ `virtual bool JsonDeserialize(const TSharedPtr<FJsonValue>& InJsonValue) override;`
- L37 _public prototype_ `virtual FText GetComponentDescription() const override;`
- L41 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& InPropertyChangedEvent) override;`
- L48 _protected member_ `TSubclassOf<UWidget> WidgetClass;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Setter = SetWidgetClass, BlueprintSetter = SetWidgetClass, Category = "Material Designer", meta = (NotKeyframeable, AllowPrivateAccess = "true", NoCreate))`
- L51 _protected member_ `TObjectPtr<UWidget> WidgetInstance;` — `UPROPERTY()`
- L54 _protected prototype_ `virtual void CreateWidgetInstance() override;`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterial/Public/Components/RenderTargetRenderers/DMRenderTargetWidgetRendererBase.h` (Public)


#### class `UDMRenderTargetWidgetRendererBase`  
`class UDMRenderTargetWidgetRendererBase : public UDMRenderTargetRenderer`  
_L16-38_
- reflection: `UCLASS(MinimalAPI, Abstract, BlueprintType, ClassGroup = "Material Designer", meta = (DisplayName = "Material Designer Render Target Widget Renderer"))`
- inherits: `UDMRenderTargetRenderer`
- desc: Renderer that renders UWidgets to render targets.
- L21 _public prototype_ `UDMRenderTargetWidgetRendererBase();`
- L25 _public prototype_ `virtual FText GetComponentDescription() const override;`
- L30 _protected member_ `TSharedPtr<SWidget> Widget;`
- L31 _protected member_ `TSharedPtr<FWidgetRenderer> WidgetRenderer;`
- L33 _protected prototype_ `virtual void CreateWidgetInstance() PURE_VIRTUAL(UDMRenderTargetUMGWidgetRenderer::CreateWidgetInstance);`
- L36 _protected prototype_ `virtual void UpdateRenderTarget_Internal() override;`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterial/Public/DMComponentPath.h` (Public)


#### struct `FDMComponentPath`  
`struct FDMComponentPath`  
_L10-29_
- desc: A path such as Name.Component.Component[2].Value
- L12 _public member_ `static constexpr TCHAR Separator = '.';`
- L13 _public member_ `static constexpr TCHAR ParameterOpen = '['; static constexpr TCHAR ParameterClose = ']';`
- L14 _public member_ `static constexpr TCHAR ParameterClose = ']';`
- L16 _public prototype_ `FDMComponentPath() = delete;`
- L17 _public prototype_ `FDMComponentPath(FStringView InPath);`
- L18 _public prototype_ `FDMComponentPath(const FString& InPathString);`
- L20 _public prototype_ `bool IsLeaf() const;`
- L25 _public prototype_ `FDMComponentPathSegment GetFirstSegment();` — Extracts the first component and removes it from the path
- L28 _protected member_ `FStringView Path;`

#### struct `FDMComponentPathSegment`  
`struct FDMComponentPathSegment`  
_L32-49_
- desc: Represents a single part of a component path
- L36 _public prototype_ `FDMComponentPathSegment(FStringView InToken, FStringView InParameter);`
- L38 _public function_ `FStringView GetToken() const`
- L40 _public prototype_ `bool HasParameter() const;`
- L42 _public prototype_ `bool GetParameter(int32& OutParameter) const;`
- L44 _public prototype_ `bool GetParameter(FString& OutParameter) const;`
- L47 _protected member_ `FStringView Token;`
- L48 _protected member_ `FStringView Parameter;`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterial/Public/DMDefs.h` (Public)


#### enum `EDMMaterialPropertyType`  
`enum class EDMMaterialPropertyType : uint8`  
_L16-41_
- reflection: `UENUM(BlueprintType)`
- desc: Some short names provided so they fit nicely on buttons!
- L18 _public enumerator_ `None = 0`
- L19 _public enumerator_ `BaseColor UMETA(ShortName = "Base")`
- L20 _public enumerator_ `EmissiveColor UMETA(ShortName = "Emis")`
- L21 _public enumerator_ `Opacity UMETA(ShortName = "Opac")`
- L22 _public enumerator_ `OpacityMask UMETA(ShortName = "Mask")`
- L23 _public enumerator_ `Roughness UMETA(ShortName = "Rough")`
- L24 _public enumerator_ `Specular UMETA(ShortName = "Spec")`
- L25 _public enumerator_ `Metallic UMETA(ShortName = "Metal")`
- L26 _public enumerator_ `Normal UMETA(ShortName = "Norm")`
- L27 _public enumerator_ `PixelDepthOffset UMETA(ShortName = "PDO")`
- L28 _public enumerator_ `WorldPositionOffset UMETA(ShortName = "WPO")`
- L29 _public enumerator_ `AmbientOcclusion UMETA(ShortName = "AO")`
- L30 _public enumerator_ `Anisotropy UMETA(ShortName = "Aniso")`
- L31 _public enumerator_ `Refraction UMETA(ShortName = "Refra")`
- L32 _public enumerator_ `Tangent UMETA(ShortName = "Tang")`
- L33 _public enumerator_ `Custom1`
- L34 _public enumerator_ `Custom2`
- L35 _public enumerator_ `Custom3`
- L36 _public enumerator_ `Custom4`
- L37 _public enumerator_ `Displacement UMETA(ShortName = "Disp")`
- L38 _public enumerator_ `SubsurfaceColor UMETA(ShortName = "Surf")`
- L39 _public enumerator_ `SurfaceThickness UMETA(ShortName = "Thick")`
- L40 _public enumerator_ `Any`

#### enum `EDMIterationResult`  
`enum class EDMIterationResult : uint8`  
_L43-47_
- L45 _public enumerator_ `Continue`
- L46 _public enumerator_ `Break`

#### enum `EDMValueType`  
`enum class EDMValueType : uint8`  
_L60-75_
- reflection: `UENUM(BlueprintType)`
- L62 _public enumerator_ `VT_None`
- L63 _public enumerator_ `VT_Bool`
- L64 _public enumerator_ `VT_Float1`
- L65 _public enumerator_ `VT_Float2`
- L66 _public enumerator_ `VT_Float3_RPY`
- L67 _public enumerator_ `VT_Float3_RGB`
- L68 _public enumerator_ `VT_Float3_XYZ`
- L69 _public enumerator_ `VT_Float4_RGBA`
- L70 _public enumerator_ `VT_Float_Any`
- L71 _public enumerator_ `VT_Texture`
- L72 _public enumerator_ `VT_ColorAtlas`
- L73 _public enumerator_ `VT_Unused`
- L74 _public enumerator_ `VT_MAX`

#### enum `EDMUpdateType`  
`enum class EDMUpdateType : uint8`  
_L78-84_
- reflection: `UENUM(BlueprintType)`
- L80 _public enumerator_ `Value = 0`
- L81 _public enumerator_ `Structure = 1 << 0`
- L82 _public enumerator_ `AllowParentUpdate = 1 << 1`
- L83 _public enumerator_ `RefreshDetailView = 1 << 2`

#### enum `EDMMaterialShadingModel`  
`enum class EDMMaterialShadingModel : uint8`  
_L88-92_
- reflection: `UENUM(BlueprintType)`
- L90 _public enumerator_ `Unlit = EMaterialShadingModel::MSM_Unlit`
- L91 _public enumerator_ `DefaultLit = EMaterialShadingModel::MSM_DefaultLit`

#### enum `EDMUVSource`  
`enum class EDMUVSource : uint8`  
_L95-100_
- reflection: `UENUM(BlueprintType, meta = (DisplayName = "Material Designer UV Source"))`
- L97 _public enumerator_ `Texture`
- L98 _public enumerator_ `ScreenPosition`
- L99 _public enumerator_ `WorldPosition`

#### enum `EDMLocationType`  
`enum class EDMLocationType : uint8`  
_L103-107_
- reflection: `UENUM(BlueprintType)`
- L105 _public enumerator_ `World`
- L106 _public enumerator_ `Actor`

#### struct `FDMMaterialStageConnectorChannel`  
`struct FDMMaterialStageConnectorChannel`  
_L113-159_
- reflection: `USTRUCT(BlueprintType, Category = "Material Designer", meta = (DisplayName = "Material Designer Stage Connector Channel"))`
- desc: An individual component of a connector (e.g. G from RGB.)
- L117 _public member_ `static constexpr int32 NO_SOURCE = -1;`
- L118 _public member_ `static constexpr int32 PREVIOUS_STAGE = 0;`
- L119 _public member_ `static constexpr int32 FIRST_STAGE_INPUT = 1;`
- L120 _public member_ `static constexpr int32 WHOLE_CHANNEL = 0;`
- L121 _public member_ `static constexpr int32 FIRST_CHANNEL = 1;`
- L122 _public member_ `static constexpr int32 SECOND_CHANNEL = 2;`
- L123 _public member_ `static constexpr int32 THIRD_CHANNEL = 4;`
- L124 _public member_ `static constexpr int32 FOURTH_CHANNEL = 8;`
- L125 _public member_ `static constexpr int32 TWO_CHANNELS = FIRST_CHANNEL | SECOND_CHANNEL;`
- L126 _public member_ `static constexpr int32 THREE_CHANNELS = FIRST_CHANNEL | SECOND_CHANNEL | THIRD_CHANNEL;`
- L128 _public member_ `static constexpr int32 FOUR_CHANNELS = FIRST_CHANNEL | SECOND_CHANNEL | THIRD_CHANNEL | FOURTH_CHANNEL;` — Not really needed? Effectively the whole channel!
- L135 _public member_ `int32 SourceIndex = PREVIOUS_STAGE;` — `UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Material Designer")` — The index of the source of this channel Index 0 is the previous stage, 1+ are the other inputs required by the current stage (e.g. textures, uvs, etc.)
- L139 _public member_ `EDMMaterialPropertyType MaterialProperty = EDMMaterialPropertyType::None;` — `UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Material Designer")` — When using previous stages, this is the material property the previous stage is using
- L143 _public member_ `int32 OutputIndex = 0;` — `UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Material Designer")` — The index of the output connector of the given stage.
- L150 _public member_ `int32 OutputChannel = WHOLE_CHANNEL;` — `UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Material Designer")` — This can be used to break down float2/3/4 into single pieces of data A value of 0 will be the original output. A bitmask (1,2,4,8) will reference (and combine) the specific channels.
- L152 _public function_ `bool operator==(const FDMMaterialStageConnectorChannel& InOther) const`

#### struct `FDMUpdateGuard`  
`struct FDMUpdateGuard`  
_L162-181_
- desc: Used to prevent Update from running during batch operations.
- L164 _public function_ `FDMUpdateGuard()`
- L169 _public function_ `~FDMUpdateGuard()`
- L174 _public function_ `static bool CanUpdate()`
- L180 _private member_ `static int32 GuardCount;`

#### struct `FDMInitializationGuard`  
`struct FDMInitializationGuard`  
_L184-207_
- desc: Used to prevent initialization from running during batch operations.
- L186 _public function_ `static bool IsInitializing()`
- L191 _public function_ `FDMInitializationGuard()`
- L197 _public function_ `~FDMInitializationGuard()`
- L206 _private member_ `static uint32 GuardCount;`

#### Free symbols / members of external scopes

- L49 _namespace_ `namespace UE`
- L49 _namespace_ `namespace DynamicMaterial` (scope `UE`)
- L51 _variable_ `constexpr int32 RenameFlags = REN_DontCreateRedirectors | REN_DoNotDirty | REN_AllowPackageLinkerMismatch | REN_NonTransactional;` (scope `UE::DynamicMaterial`)
- L52 _variable_ `constexpr EClassFlags InvalidClassFlags = CLASS_Abstract | CLASS_Hidden | CLASS_Deprecated | CLASS_NewerVersionExists;` (scope `UE::DynamicMaterial`)
- L54 _prototype_ `void ForEachMaterialPropertyType(TFunctionRef<EDMIterationResult(EDMMaterialPropertyType InType)> InCallable, EDMMaterialPropertyType InStart = static_cast<EDMMaterialPropertyType>(static_cast<uint8>(EDMMaterialPropertyType::None) + 1), EDMMaterialPropertyType InEnd = static_cast<EDMMaterialPropertyType>(static_cast<uint8>(EDMMaterialPropertyType::Any) - 1));` (scope `UE::DynamicMaterial`)

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterial/Public/DMValueDefinition.h` (Public)


#### struct `FDMValueDefinition`  
`struct FDMValueDefinition`  
_L21-84_
- reflection: `USTRUCT(BlueprintType)`
- desc: Stores information about basic value types, such as EDMValueType::Float1.
- L25 _public function_ `FDMValueDefinition() : FDMValueDefinition(EDMValueType::VT_None, 0, FText::GetEmpty(), {}, TSubclassOf<UDMMaterialValue>())`
- L30 _public function_ `FDMValueDefinition(EDMValueType InType, uint8 InFloatCount, const FText& InDisplayName, const TArray<FText>& InChannelNames, TSubclassOf<UDMMaterialValue> InValueClass) : Type(InType) , FloatCount(InFloatCount) , DisplayName(InDisplayName) , ChannelNames(InChannelNames) , ValueClass(InValueClass)`
- L40 _public function_ `FDMValueDefinition(EDMValueType InType, uint8 InFloatCount, FText&& InDisplayName, TArray<FText>&& InChannelNames, TSubclassOf<UDMMaterialValue> InValueClass) : Type(InType) , FloatCount(InFloatCount) , DisplayName(MoveTemp(InDisplayName)) , ChannelNames(MoveTemp(InChannelNames)) , ValueClass(InValueClass)`
- L50 _public function_ `EDMValueType GetType() const`
- L53 _public function_ `uint8 GetFloatCount() const` — Will return 0 for non-float/any-float types.
- L55 _public function_ `const FText& GetDisplayName() const`
- L57 _public function_ `const TArray<FText>& GetChannelNames() const`
- L60 _public function_ `TSubclassOf<UDMMaterialValue> GetValueClass() const` — Returns the base class of this type.
- L62 _public prototype_ `bool IsFloatType() const;`
- L64 _public prototype_ `bool IsFloat3Type() const;`
- L67 _public prototype_ `const FText& GetChannelName(int32 InChannel) const;` — To be consistent without OutputChannel, 1 is the first channel, not 0.
- L71 _protected member_ `EDMValueType Type;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Material Designer")`
- L74 _protected member_ `uint8 FloatCount;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Material Designer")`
- L77 _protected member_ `FText DisplayName;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Material Designer")`
- L80 _protected member_ `TArray<FText> ChannelNames;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Material Designer")`
- L83 _protected member_ `TSubclassOf<UDMMaterialValue> ValueClass;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Material Designer")`

#### class `UDMValueDefinitionLibrary`  
`class UDMValueDefinitionLibrary : public UBlueprintFunctionLibrary`  
_L87-122_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UBlueprintFunctionLibrary`
- L94 _public prototype_ `static const TArray<EDMValueType>& GetValueTypes();` — `UFUNCTION(BlueprintPure, CallInEditor, Category = "Material Designer")` — Returns the array of available Value Types, excluding generics like None or Max.
- L98 _public prototype_ `static const FDMValueDefinition& GetValueDefinition(EDMValueType InValueType);` — `UFUNCTION(BlueprintPure, CallInEditor, Category = "Material Designer")` — Returns a value definition for the given value type.
- L102 _public function_ `static bool BP_AreTypesCompatible(EDMValueType A, EDMValueType B, int32 AChannel, int32 BChannel)` — `UFUNCTION(BlueprintPure, CallInEditor, Category = "Material Designer", meta = (DisplayName = "Are Types Compatible"))` — Returns whether the given types can be connected together as input/output.
- L108 _public prototype_ `static bool AreTypesCompatible(EDMValueType InA, EDMValueType InB, int32 InAChannel = FDMMaterialStageConnectorChannel::WHOLE_CHANNEL, int32 InBChannel = FDMMaterialStageConnectorChannel::WHOLE_CHANNEL);` — Returns whether the given types can be connected together as input/output.
- L113 _public prototype_ `static const FDMValueDefinition& GetTypeForFloatCount(uint8 InFloatCount);` — Converts a number of floats into the value type
- L117 _public prototype_ `static const FDMValueDefinition& GetTypeForFloatCount(int32 InFloatCount);` — `UFUNCTION(BlueprintPure, CallInEditor, Category = "Material Designer")` — Converts a number of floats into the value type
- L120 _public prototype_ `static FSlateIcon GetValueIcon(EDMValueType InType);`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterial/Public/DynamicMaterialModule.h` (Public)


#### class `FDynamicMaterialModule`  
`class FDynamicMaterialModule : public IModuleInterface`  
_L28-38_
- inherits: `IModuleInterface`
- desc: Material Designer - Build your own materials in a slimline editor!
- L31 _public prototype_ `static FDynamicMaterialModule& Get();`
- L34 _public prototype_ `static bool AreUObjectsSafe();` — Returns true if UObjects are currently safe to use.
- L37 _public prototype_ `static bool IsMaterialExportEnabled();` — Returns true if the material export flag has been enabled. @See DM.ExportMaterials

#### Free symbols / members of external scopes

- L19 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogDynamicMaterial, Log, All);`
- L19 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogDynamicMaterial, Log, All);`
- L22 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(TScriptInterface<IDynamicMaterialModelEditorOnlyDataInterface>, FDMCreateEditorOnlyDataDelegate, UDynamicMaterialModel*) #endif class FDynamicMaterialModule : public IModuleInterface { public: static FDynamicMaterialModule& Get(); static bool AreUObjectsSafe(); static bool IsMaterialExportEnabled(); };`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterial/Public/IDMParameterContainer.h` (Public)


#### class `UDMParameterContainer`  
`class UDMParameterContainer : public UInterface`  
_L11-14_
- reflection: `UINTERFACE(MinimalAPI, BlueprintType)`
- inherits: `UInterface`

#### class `IDMParameterContainer`  
`class IDMParameterContainer`  
_L16-56_
- L22 _public function_ `static void CopyParametersBetween(UObject* InFrom, UObject* InTo)` — Copies the parameter-based values of InFrom to InTo, if possible.
- L42 _public function_ `void CopyParametersTo(UObject* InOther)`
- L47 _public function_ `void CopyParametersFromWrapper(UObject* InOther)`
- L54 _public prototype_ `void CopyParametersFrom(UObject* InOther);` — `UFUNCTION(BlueprintNativeEvent, Category = "Material Designer")` — Copies the parameter-based value of the given value to this value, if possible.
- L55 _public function_ `virtual void CopyParametersFrom_Implementation(UObject* InOther)`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterial/Public/Material/DynamicMaterialInstance.h` (Public)


#### class `UDynamicMaterialInstance`  
`class UDynamicMaterialInstance : public UMaterialInstanceDynamic`  
_L18-64_
- reflection: `UCLASS(MinimalAPI, ClassGroup = "Material Designer", DefaultToInstanced, BlueprintType, meta = (DisplayThumbnail = "true"))`
- inherits: `UMaterialInstanceDynamic`
- desc: A Material Designer Material with its own integrated Material Designer Model that generates the base Material.
- L23 _public member_ `static const FString ModelTypeTag_Material;`
- L24 _public member_ `static const FString ModelTypeTag_Instance;`
- L27 _public prototype_ `static FString GetMaterialTypeTag(const FAssetData& InAssetData);`
- L30 _public prototype_ `UDynamicMaterialInstance();`
- L34 _public prototype_ `UDynamicMaterialModelBase* GetMaterialModelBase() const;` — `UFUNCTION(BlueprintPure, Category = "Material Designer")` — Returns the Material Model associated with this Material Designer Material.
- L38 _public prototype_ `UDynamicMaterialModel* GetMaterialModel() const;` — `UFUNCTION(BlueprintPure, Category = "Material Designer")` — Resolves the base Material Model used with this Instance and returns it.
- L41 _public prototype_ `virtual void GetAssetRegistryTags(FAssetRegistryTagsContext Context) const override;`
- L46 _public prototype_ `void SetMaterialModel(UDynamicMaterialModelBase* InMaterialModel);` — Sets the Material Model used for this Instance.
- L49 _public prototype_ `void OnMaterialBuilt(UDynamicMaterialModelBase* InMaterialModel);` — Event called when the base material is build.
- L52 _public prototype_ `void InitializeMIDPublic();` — Initialises the base MID object with the current Material Model's generated material.
- L55 _public prototype_ `virtual void PostDuplicate(bool bInDuplicateForPIE) override;`
- L56 _public prototype_ `virtual void PostEditImport() override;`
- L57 _public prototype_ `virtual void GetAssetRegistryTagMetadata(TMap<FName, FAssetRegistryTagMetadata>& OutMetadata) const override;`
- L63 _protected member_ `TObjectPtr<UDynamicMaterialModelBase> MaterialModelBase;` — `UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Instanced, Category = "Material Designer")`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterial/Public/Model/DynamicMaterialModel.h` (Public)


#### class `UDynamicMaterialModel`  
`class UDynamicMaterialModel : public UDynamicMaterialModelBase`  
_L39-370_
- reflection: `UCLASS(MinimalAPI, ClassGroup = "Material Designer", DefaultToInstanced, BlueprintType, meta = (DisplayThumbnail = "true"))`
- inherits: `UDynamicMaterialModelBase`
- L45 _public member_ `static const FString ValuesPathToken;` — Tokens used for Components.
- L46 _public member_ `static const FString ParametersPathToken;`
- L49 _public member_ `static const FLazyName GlobalBaseColorValueName;` — FNames for global parameters values.
- L50 _public member_ `static const FLazyName GlobalBaseColorParameterName;`
- L51 _public member_ `static const FLazyName GlobalEmissiveColorValueName;`
- L52 _public member_ `static const FLazyName GlobalEmissiveColorParameterName;`
- L53 _public member_ `static const FLazyName GlobalOpacityValueName;`
- L54 _public member_ `static const FLazyName GlobalOpacityParameterName;`
- L55 _public member_ `static const FLazyName GlobalMetallicValueName;`
- L56 _public member_ `static const FLazyName GlobalMetallicParameterName;`
- L57 _public member_ `static const FLazyName GlobalRoughnessValueName;`
- L58 _public member_ `static const FLazyName GlobalRoughnessParameterName;`
- L59 _public member_ `static const FLazyName GlobalNormalValueName;`
- L60 _public member_ `static const FLazyName GlobalNormalParameterName;`
- L61 _public member_ `static const FLazyName GlobalSpecularValueName;`
- L62 _public member_ `static const FLazyName GlobalSpecularParameterName;`
- L63 _public member_ `static const FLazyName GlobalAnisotropyValueName;`
- L64 _public member_ `static const FLazyName GlobalAnisotropyParameterName;`
- L65 _public member_ `static const FLazyName GlobalWorldPositionOffsetValueName;`
- L66 _public member_ `static const FLazyName GlobalWorldPositionOffsetParameterName;`
- L67 _public member_ `static const FLazyName GlobalAmbientOcclusionValueName;`
- L68 _public member_ `static const FLazyName GlobalAmbientOcclusionParameterName;`
- L69 _public member_ `static const FLazyName GlobalRefractionValueName;`
- L70 _public member_ `static const FLazyName GlobalRefractionParameterName;`
- L71 _public member_ `static const FLazyName GlobalTangentValueName;`
- L72 _public member_ `static const FLazyName GlobalTangentParameterName;`
- L73 _public member_ `static const FLazyName GlobalPixelDepthOffsetValueName;`
- L74 _public member_ `static const FLazyName GlobalPixelDepthOffsetParameterName;`
- L75 _public member_ `static const FLazyName GlobalDisplacementValueName;`
- L76 _public member_ `static const FLazyName GlobalDisplacementParameterName;`
- L77 _public member_ `static const FLazyName GlobalSubsurfaceColorValueName;`
- L78 _public member_ `static const FLazyName GlobalSubsurfaceColorParameterName;`
- L79 _public member_ `static const FLazyName GlobalSurfaceThicknessValueName;`
- L80 _public member_ `static const FLazyName GlobalSurfaceThicknessParameterName;`
- L81 _public member_ `static const FLazyName GlobalOffsetValueName;`
- L82 _public member_ `static const FLazyName GlobalOffsetParameterName;`
- L83 _public member_ `static const FLazyName GlobalTilingValueName;`
- L84 _public member_ `static const FLazyName GlobalTilingParameterName;`
- L85 _public member_ `static const FLazyName GlobalRotationValueName;`
- L86 _public member_ `static const FLazyName GlobalRotationParameterName;`
- L88 _public prototype_ `UDynamicMaterialModel();`
- L92 _public prototype_ `bool IsModelValid() const;` — `UFUNCTION(BlueprintPure, Category = "Material Designer")` — Returns this if this is IsValid() and isn't isn't being destroyed.
- L96 _public prototype_ `UDMMaterialValue* GetGlobalParameterValueForMaterialProperty(EDMMaterialPropertyType InProperty) const;` — `UFUNCTION(BlueprintPure, Category = "Material Designer")` — Returns a specific global parameter value (such as global opacity) for the given material property or nullptr.
- L100 _public function_ `template<typename InValueClass> InValueClass* GetGlobalParameterValueForMaterialProperty(EDMMaterialPropertyType InProperty) const` — Returns a Cast version of a specific global value (such as global opacity) or nullptr.
- L107 _public prototype_ `UDMMaterialValue* GetGlobalParameterValue(FName InName) const;` — `UFUNCTION(BlueprintPure, Category = "Material Designer")` — Returns a specific global parameter value (such as global opacity) of the given object name (see global parameter FNames) or nullptr.
- L111 _public function_ `template<typename InValueClass> InValueClass* GetTypedGlobalParameterValue(FName InName) const` — Returns a Cast version of a specific global value (such as global opacity) or nullptr.
- L116 _public prototype_ `void ForEachGlobalParameter(TFunctionRef<void(UDMMaterialValue* InGlobalParameterValue)> InCallable);`
- L120 _public prototype_ `UDMMaterialComponent* GetComponentByPath(const FString& InPath) const;` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")` — Searches the model for a specific component based on a path.
- L123 _public prototype_ `UDMMaterialComponent* GetComponentByPath(FDMComponentPath& InPath) const;` — Searches the model for a specific component based on a path.
- L127 _public function_ `template<typename InComponentClass> InComponentClass* GetComponentByPath(FDMComponentPath& InPath) const` — Searches the model for a specific component based on a path and Casts it to the given type.
- L134 _public function_ `const TArray<UDMMaterialValue*>& GetValues() const` — `UFUNCTION(BlueprintPure, Category = "Material Designer")` — Returns an array of the (non-global parameter) values used in this Model.
- L138 _public prototype_ `UDMMaterialValue* GetValueByName(FName InName) const;` — `UFUNCTION(BlueprintPure, Category = "Material Designer")` — Returns a specific (non-global parameter) value of the given object name.
- L141 _public function_ `const TSet<TObjectPtr<UDMMaterialComponent>>& GetRuntimeComponents() const` — Returns a set of components that require a runtime reference, such as texture uvs.
- L149 _public prototype_ `TScriptInterface<IDynamicMaterialModelEditorOnlyDataInterface> BP_GetEditorOnlyData() const;` — `UFUNCTION(BlueprintPure, Category = "Material Designer", Meta = (DisplayName = "Get Editor Only Data"))` — Returns the editor only data for this model.
- L152 _public prototype_ `IDynamicMaterialModelEditorOnlyDataInterface* GetEditorOnlyData() const;` — Returns the editor only data for this model.
- L156 _public prototype_ `UDMMaterialValue* AddValue(TSubclassOf<UDMMaterialValue> InValueClass);` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")` — Creates a new value of the given class and returns it.
- L159 _public prototype_ `void AddRuntimeComponentReference(UDMMaterialComponent* InValue);` — Adds a reference to a component so they don't get garbage collected at runtime.
- L162 _public prototype_ `void RemoveRuntimeComponentReference(UDMMaterialComponent* InValue);` — Removes a reference to a component.
- L165 _public prototype_ `void RemoveValueByParameterName(FName InName);` — Removes a value based on its parameter name.
- L172 _public prototype_ `bool HasParameterName(FName InParameterName) const;` — `UFUNCTION(BlueprintPure, Category = "Material Designer")` — Returns true if a parameter has with the given name exists on this Model. Will not include automatically generated component parameter names.
- L175 _public prototype_ `UDMMaterialParameter* CreateUniqueParameter(FName InBaseName);` — Creates a new parameter and assigns it a unique name.
- L178 _public prototype_ `void RenameParameter(UDMMaterialParameter* InParameter, FName InBaseName);` — Updates the name on an existing parameter.
- L181 _public prototype_ `void FreeParameter(UDMMaterialParameter* InParameter);` — Removes parameter by the name assigned to this parameter object.
- L187 _public prototype_ `bool ConditionalFreeParameter(UDMMaterialParameter* InParameter);` — Removes this specific object from the parameter map if the name is in use by a different parameter. Returns true if, after this call, the object is not in the parameter map.
- L191 _public prototype_ `void OnValueUpdated(UDMMaterialValue* InValue, EDMUpdateType InUpdateType);` — Called by the value when it updates. Updates Material Designer Material and triggers the delegate.
- L194 _public prototype_ `void OnTextureUVUpdated(UDMTextureUV* InTextureUV);` — Called by the texture uv when it updates. Updates Material Designer Material and triggers the delegate.
- L197 _public function_ `FDMOnValueUpdated::RegistrationType& GetOnValueUpdateDelegate()` — Returns the value update delegate to (un)subscribe.
- L200 _public function_ `FDMOnTextureUVUpdated::RegistrationType& GetOnTextureUVUpdateDelegate()` — Returns the texture uv update delegate to (un)subscribe.
- L203 _public function_ `virtual UDynamicMaterialModel* ResolveMaterialModel() override`
- L204 _public function_ `virtual UDynamicMaterialInstance* GetDynamicMaterialInstance() const override`
- L205 _public prototype_ `virtual void SetDynamicMaterialInstance(UDynamicMaterialInstance* InDynamicMaterialInstance) override;`
- L206 _public function_ `virtual UMaterial* GetGeneratedMaterial() const override`
- L207 _public prototype_ `virtual void ApplyComponents(UMaterialInstanceDynamic* InMID) override;`
- L211 _public prototype_ `virtual void PostLoad() override;`
- L213 _public prototype_ `virtual void PostEditUndo() override;`
- L214 _public prototype_ `virtual void PostEditImport() override;`
- L215 _public prototype_ `virtual void PostDuplicate(bool bInDuplicateForPIE) override;`
- L219 _public prototype_ `void PostEditorDuplicate();` — Called to ensure that the object hierarchy is correct.
- L224 _public prototype_ `UDMMaterialValueFloat1* GetGlobalOpacityValue() const;` — `UE_DEPRECATED(5.5, "Added to GlobalParameterValues map.")` — `UFUNCTION(BlueprintPure, Category = "Material Designer")`
- L229 _protected member_ `TArray<TObjectPtr<UDMMaterialValue>> Values;` — `UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Instanced, Category = "Material Designer")` — Global values
- L233 _protected member_ `TSet<TObjectPtr<UDMMaterialComponent>> RuntimeComponents;` — `UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Instanced, Category = "Material Designer")` — References to runtime components outered to this model which are not otherwise referenced.
- L237 _protected member_ `TMap<FName, TWeakObjectPtr<UDMMaterialParameter>> ParameterMap;` — `UPROPERTY(VisibleInstanceOnly, TextExportTransient, Category = "Material Designer")` — Map of parameter names to the objects representing that parameter.
- L241 _protected member_ `TObjectPtr<UMaterial> DynamicMaterial = nullptr;` — `UPROPERTY(VisibleInstanceOnly, Instanced, BlueprintReadOnly, TextExportTransient, Category = "Material Designer")` — Material generated by the Model.
- L245 _protected member_ `TObjectPtr<UDynamicMaterialInstance> DynamicMaterialInstance;` — `UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, TextExportTransient, Category = "Material Designer")` — Material Designer Material representing the MID for this Model.
- L250 _protected member_ `TObjectPtr<UObject> EditorOnlyDataSI;` — `UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Instanced, Category = "Material Designer")` — Object holding the editor-only data used by this model.
- L254 _protected member_ `TObjectPtr<UDMMaterialValue> GlobalBaseColorParameterValue;` — `UPROPERTY(BlueprintReadOnly, Instanced, Category = "Material Designer")`
- L257 _protected member_ `TObjectPtr<UDMMaterialValue> GlobalEmissiveColorParameterValue;` — `UPROPERTY(BlueprintReadOnly, Instanced, Category = "Material Designer")`
- L260 _protected member_ `TObjectPtr<UDMMaterialValue> GlobalOpacityParameterValue;` — `UPROPERTY(BlueprintReadOnly, Instanced, Category = "Material Designer")`
- L263 _protected member_ `TObjectPtr<UDMMaterialValue> GlobalRoughnessParameterValue;` — `UPROPERTY(BlueprintReadOnly, Instanced, Category = "Material Designer")`
- L266 _protected member_ `TObjectPtr<UDMMaterialValue> GlobalSpecularParameterValue;` — `UPROPERTY(BlueprintReadOnly, Instanced, Category = "Material Designer")`
- L269 _protected member_ `TObjectPtr<UDMMaterialValue> GlobalMetallicParameterValue;` — `UPROPERTY(BlueprintReadOnly, Instanced, Category = "Material Designer")`
- L272 _protected member_ `TObjectPtr<UDMMaterialValue> GlobalNormalParameterValue;` — `UPROPERTY(BlueprintReadOnly, Instanced, Category = "Material Designer")`
- L275 _protected member_ `TObjectPtr<UDMMaterialValue> GlobalPixelDepthOffsetParameterValue;` — `UPROPERTY(BlueprintReadOnly, Instanced, Category = "Material Designer")`
- L278 _protected member_ `TObjectPtr<UDMMaterialValue> GlobalWorldPositionOffsetParameterValue;` — `UPROPERTY(BlueprintReadOnly, Instanced, Category = "Material Designer")`
- L281 _protected member_ `TObjectPtr<UDMMaterialValue> GlobalAmbientOcclusionParameterValue;` — `UPROPERTY(BlueprintReadOnly, Instanced, Category = "Material Designer")`
- L284 _protected member_ `TObjectPtr<UDMMaterialValue> GlobalAnisotropyParameterValue;` — `UPROPERTY(BlueprintReadOnly, Instanced, Category = "Material Designer")`
- L287 _protected member_ `TObjectPtr<UDMMaterialValue> GlobalRefractionParameterValue;` — `UPROPERTY(BlueprintReadOnly, Instanced, Category = "Material Designer")`
- L290 _protected member_ `TObjectPtr<UDMMaterialValue> GlobalTangentParameterValue;` — `UPROPERTY(BlueprintReadOnly, Instanced, Category = "Material Designer")`
- L293 _protected member_ `TObjectPtr<UDMMaterialValue> GlobalDisplacementParameterValue;` — `UPROPERTY(BlueprintReadOnly, Instanced, Category = "Material Designer")`
- L296 _protected member_ `TObjectPtr<UDMMaterialValue> GlobalSubsurfaceColorParameterValue;` — `UPROPERTY(BlueprintReadOnly, Instanced, Category = "Material Designer")`
- L299 _protected member_ `TObjectPtr<UDMMaterialValue> GlobalSurfaceThicknessParameterValue;` — `UPROPERTY(BlueprintReadOnly, Instanced, Category = "Material Designer")`
- L302 _protected member_ `TObjectPtr<UDMMaterialValue> GlobalOffsetParameterValue;` — `UPROPERTY(BlueprintReadOnly, Instanced, Category = "Material Designer")`
- L305 _protected member_ `TObjectPtr<UDMMaterialValue> GlobalTilingParameterValue;` — `UPROPERTY(BlueprintReadOnly, Instanced, Category = "Material Designer")`
- L308 _protected member_ `TObjectPtr<UDMMaterialValue> GlobalRotationParameterValue;` — `UPROPERTY(BlueprintReadOnly, Instanced, Category = "Material Designer")`
- L311 _protected member_ `FDMOnValueUpdated OnValueUpdateDelegate;` — Delegate called when a value is updated. @See GetOnValueUpdateDelegate.
- L314 _protected member_ `FDMOnTextureUVUpdated OnTextureUVUpdateDelegate;` — Delegate called when a value is updated. @See GetOnValueUpdateDelegate.
- L319 _protected prototype_ `void FixGlobalParameterValues();` — Attempts to fix global opacity to give it a range of 0-1.
- L323 _protected prototype_ `FName CreateUniqueParameterName(FName InBaseName);` — Checks the current parameters and returns the first parameter name that is not in used (BaseName1, 2, etc, etc.)
- L326 _protected prototype_ `void ReinitComponents();` — Called to ensure that all components are correctly initialized. Also calls the editor only data version, if applicable.
- L329 _protected prototype_ `void FixGlobalVars();` — Makes sure the global parameter values have the correct name.
- L340 _protected member_ `TEnumAsByte<EBlendMode> BlendMode;` — `UE_DEPRECATED(5.3, "Moved to editor-only subobject.")` — `UPROPERTY()`
- L344 _protected member_ `EDMMaterialShadingModel ShadingModel;` — `UE_DEPRECATED(5.3, "Moved to editor-only subobject.")` — `UPROPERTY()`
- L348 _protected member_ `TMap<EDMMaterialPropertyType, TObjectPtr<UObject>> Properties;` — `UE_DEPRECATED(5.3, "Moved to editor-only subobject.")` — `UPROPERTY()`
- L352 _protected member_ `TMap<EDMMaterialPropertyType, TObjectPtr<UObject>> PropertySlotMap;` — `UE_DEPRECATED(5.3, "Moved to editor-only subobject.")` — `UPROPERTY()`
- L356 _protected member_ `TArray<TObjectPtr<UObject>> Slots;` — `UE_DEPRECATED(5.3, "Moved to editor-only subobject.")` — `UPROPERTY()`
- L360 _protected member_ `TArray<TObjectPtr<UMaterialExpression>> Expressions;` — `UE_DEPRECATED(5.3, "Moved to editor-only subobject.")` — `UPROPERTY()`
- L364 _protected member_ `bool bCreateMaterialPackage;` — `UE_DEPRECATED(5.3, "Moved to editor-only subobject.")` — `UPROPERTY()`
- L368 _protected member_ `TObjectPtr<UDMMaterialValueFloat1> GlobalOpacityValue;` — `UE_DEPRECATED(5.5, "Moved to GlobalParameterValues map.")` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L35 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FDMOnValueUpdated, UDynamicMaterialModel*, UDMMaterialValue*);`
- L35 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FDMOnValueUpdated, UDynamicMaterialModel*, UDMMaterialValue*);`
- L36 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FDMOnTextureUVUpdated, UDynamicMaterialModel*, UDMTextureUV*);`
- L36 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FDMOnTextureUVUpdated, UDynamicMaterialModel*, UDMTextureUV*);`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterial/Public/Model/DynamicMaterialModelBase.h` (Public)


#### class `UDynamicMaterialModelBase`  
`class UDynamicMaterialModelBase : public UObject`  
_L18-58_
- reflection: `UCLASS(MinimalAPI, BlueprintType, Abstract, ClassGroup = "Material Designer", meta = (DisplayName = "Material Designer Model Base"))`
- inherits: `UObject`
- desc: Base version of a dynamic material model.
- L29 _public function_ `virtual UDynamicMaterialModel* ResolveMaterialModel() PURE_VIRTUAL(UDynamicMaterialModelBase::ResolveMaterialModel, return nullptr;) UFUNCTION(BlueprintPure, Category = "Material Designer") virtual UDynamicMaterialInstance* GetDynamicMaterialInstance() const PURE_VIRTUAL(UDynamicMaterialModelBase::GetDynamicMaterialInstance, return nullptr;) virtual void SetDynamicMaterialInstance(UDynamicMaterialInstance* InDynamicMaterialInstance) PURE_VIRTUAL(UDynamicMaterialModelBase::SetDynamicMaterialInstance) UFUNCTION(BlueprintPure, Category = "Material Designer") virtual UMaterial* GetGeneratedMaterial() const PURE_VIRTUAL(UDynamicMaterialModelBase::GetGeneratedMaterial, return nullptr;) virtual void ApplyComponents(UMaterialInstanceDynamic* InMID) PURE_VIRTUAL(UDynamicMaterialModelBase::ApplyComponents) #if WITH_EDITOR bool IsPreviewModified() const` — `UFUNCTION(BlueprintPure, Category = "Material Designer")` — Returns the Material Designer Model that is the base for this Model. It will be this object for a Model. It will be the parent Model for a Model Instance.
- L48 _public function_ `void MarkPreviewModified()`
- L50 _public function_ `void MarkOriginalUpdated()`
- L56 _protected member_ `bool bPreviewModified = false;` — Set to true when the material designer makes a change to a preview model.

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterial/Public/Model/DynamicMaterialModelDynamic.h` (Public)


#### class `UDynamicMaterialModelDynamic`  
`class UDynamicMaterialModelDynamic : public UDynamicMaterialModelBase`  
_L26-146_
- reflection: `UCLASS(MinimalAPI, BlueprintType, ClassGroup = "Material Designer", meta = (DisplayName = "Material Designer Model Instance"))`
- inherits: `UDynamicMaterialModelBase`
- desc: Represents a MID-like version of a Material Designer Model. Uses dynamic values/texture uvs to link to the original model.
- L31 _public member_ `static const FString ParentModelPathToken;`
- L32 _public member_ `static const FString DynamicComponentsPathToken;`
- L41 _public prototype_ `static UDynamicMaterialModelDynamic* Create(UObject* InOuter, UDynamicMaterialModel* InParentModel);` — `UFUNCTION(BlueprintCallable, Category = "Motion Design")` — Create a new Material Designer Model Instance based on a parent Model. @param InOuter Could be the transient package, an asset package or a Material Designer Material. @return A new Material Designer Model Instance with its components already initialized.
- L44 _public prototype_ `UDynamicMaterialModelDynamic();`
- L48 _public prototype_ `UDynamicMaterialModel* GetParentModel() const;` — `UFUNCTION(BlueprintPure, Category = "Motion Design")` — Resolves and returns the parent model from ParentModelSoft, saving it in the transient ParentModel.
- L53 _public prototype_ `UDMMaterialComponentDynamic* GetComponentDynamic(FName InName);` — `UFUNCTION(BlueprintPure, Category = "Motion Design")` — Returns the component with the given name or nullptr.
- L59 _public prototype_ `bool AddComponentDynamic(UDMMaterialComponentDynamic* InValueDynamic);` — Adds the given component. Won't add if a component with the same name already exists. @return True if the component was added.
- L65 _public prototype_ `bool RemoveComponentDynamic(UDMMaterialComponentDynamic* InValueDynamic);` — Removes the given component. Won't remove if the name doesn't exist or the components don't match. @return True if the component was removed.
- L71 _public prototype_ `void EnsureComponents();` — Checks the parent model to make sure that all components that exist on the parent model are added and that all components that no longer exist on the parent model are removed.
- L75 _public prototype_ `void OnValueUpdated(UDMMaterialValueDynamic* InValueDynamic);` — Called when a value changes so that the Material Designer Material can be updated and the event broadcast
- L78 _public prototype_ `void OnTextureUVUpdated(UDMTextureUVDynamic* InTextureUVDynamic);` — Called when a texture uv changes so that the Material Designer Material can be updated and the event broadcast
- L81 _public function_ `FDMOnValueDynamicUpdated::RegistrationType& GetOnValueDynamicUpdateDelegate()` — Returns the on value update method so it can (un)subscribed to.
- L84 _public function_ `FDMOnTextureUVDynamicUpdated::RegistrationType& GetOnTextureUVDynamicUpdateDelegate()` — Returns the on value update method so it can (un)subscribed to.
- L88 _public prototype_ `UDMMaterialComponent* GetComponentByPath(const FString& InPath) const;` — `UFUNCTION(BlueprintPure, Category = "Motion Design")` — Finds the component with the given path.
- L91 _public prototype_ `UDMMaterialComponent* GetComponentByPath(FDMComponentPath& InPath) const;` — Finds the component with the given path.
- L94 _public prototype_ `const TMap<FName, TObjectPtr<UDMMaterialComponentDynamic>>& GetComponentMap() const;` — Returns the component map.
- L98 _public prototype_ `UDynamicMaterialModel* ToEditable(UObject* InOuter);` — Converts this model dynamic to a new model and returns it.
- L102 _public prototype_ `virtual UDynamicMaterialModel* ResolveMaterialModel() override;`
- L103 _public prototype_ `virtual UDynamicMaterialInstance* GetDynamicMaterialInstance() const override;`
- L104 _public prototype_ `virtual void SetDynamicMaterialInstance(UDynamicMaterialInstance* InDynamicMaterialInstance) override;`
- L105 _public prototype_ `virtual UMaterial* GetGeneratedMaterial() const override;`
- L106 _public prototype_ `virtual void ApplyComponents(UMaterialInstanceDynamic* InMID) override;`
- L110 _public prototype_ `virtual void PostLoad() override;`
- L116 _protected member_ `TSoftObjectPtr<UDynamicMaterialModel> ParentModelSoft;` — `UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Material Designer")` — Soft reference to the parent model.
- L120 _protected member_ `TObjectPtr<UDynamicMaterialModel> ParentModel;` — `UPROPERTY(Transient)` — Hard reference to the parent model, loaded when the model is first accessed.
- L124 _protected member_ `TMap<FName, TObjectPtr<UDMMaterialComponentDynamic>> DynamicComponents;` — `UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Material Designer")` — Map of the dynamic components that reference the parent model.
- L128 _protected member_ `TObjectPtr<UDynamicMaterialInstance> DynamicMaterialInstance;` — `UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, TextExportTransient, Category = "Material Designer")` — Hard reference to the instance, if it exists.
- L131 _protected member_ `FDMOnValueDynamicUpdated OnValueDynamicUpdateDelegate;` — Delegate called when values update. @See GetOnValueDynamicUpdateDelegate
- L134 _protected member_ `FDMOnTextureUVDynamicUpdated OnTextureUVDynamicUpdateDelegate;` — Delegate called when texture uvs update. @See GetOnTextureUVDynamicUpdateDelegate
- L140 _protected prototype_ `UDynamicMaterialModel* EnsureParentModel();` — Loads the parent model from the soft reference, if it is not already loaded. @return The loaded parent model or nullptr.
- L144 _protected prototype_ `void InitComponents();` — Scans the parent Material Model and adds all the components from there as Instance Components. Should not be called twice.

#### Free symbols / members of external scopes

- L19 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FDMOnValueDynamicUpdated, UDynamicMaterialModelDynamic*, UDMMaterialValueDynamic*);`
- L19 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FDMOnValueDynamicUpdated, UDynamicMaterialModelDynamic*, UDMMaterialValueDynamic*);`
- L20 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FDMOnTextureUVDynamicUpdated, UDynamicMaterialModelDynamic*, UDMTextureUVDynamic*);`
- L20 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FDMOnTextureUVDynamicUpdated, UDynamicMaterialModelDynamic*, UDMTextureUVDynamic*);`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterial/Public/Model/IDMMaterialBuildStateInterface.h` (Public)


#### struct `IDMMaterialBuildStateInterface`  
`struct IDMMaterialBuildStateInterface`  
_L23-53_
- desc: BuildState is a class that stores the current state of a material that is being built. It stores useful lists of UMaterialExpressions relating to various object within the builder, such a Stages or Sources. It is an entirely transient object. It is not meant to be saved outside of the material building processs.
- L25 _public prototype_ `virtual ~IDMMaterialBuildStateInterface() = default;`
- L28 _public prototype_ `virtual UMaterial* GetDynamicMaterial() const = 0;` — Returns the dynamic material being built.
- L31 _public prototype_ `virtual UDynamicMaterialModel* GetMaterialModel() const = 0;` — Returns the material model for the material being build.
- L34 _public prototype_ `virtual IDMMaterialBuildUtilsInterface& GetBuildUtils() const = 0;` — Returns the build utils object for this build state, holding helpful material utilities.
- L37 _public prototype_ `virtual bool HasValue(const UDMMaterialValue* InValue) const = 0;` — Material Values
- L39 _public prototype_ `virtual const TArray<UMaterialExpression*>& GetValueExpressions(const UDMMaterialValue* InValue) const = 0;`
- L41 _public prototype_ `virtual UMaterialExpression* GetLastValueExpression(const UDMMaterialValue* InValue) const = 0;`
- L43 _public prototype_ `virtual void AddValueExpressions(const UDMMaterialValue* InValue, const TArray<UMaterialExpression*>& InValueExpressions) = 0;`
- L45 _public prototype_ `virtual TArray<const UDMMaterialValue*> GetValues() const = 0;`
- L47 _public prototype_ `virtual const TMap<const UDMMaterialValue*, TArray<UMaterialExpression*>>& GetValueMap() const = 0;`
- L50 _public prototype_ `virtual void AddOtherExpressions(const TArray<UMaterialExpression*>& InOtherExpressions) = 0;` — Other Expressions.
- L52 _public prototype_ `virtual const TSet<UMaterialExpression*>& GetOtherExpressions() = 0;`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterial/Public/Model/IDMMaterialBuildUtilsInterface.h` (Public)


#### enum `EDMMaterialParameterGroup`  
`enum class EDMMaterialParameterGroup : uint8`  
_L24-29_
- L26 _public enumerator_ `Property`
- L27 _public enumerator_ `Global`
- L28 _public enumerator_ `NotExposed`

#### struct `IDMMaterialBuildUtilsInterface`  
`struct IDMMaterialBuildUtilsInterface`  
_L34-92_
- desc: BuildUtils provides some helper functions for creating UMaterialExpressions during the material build process.
- L36 _public prototype_ `virtual ~IDMMaterialBuildUtilsInterface() = default;`
- L43 _public prototype_ `virtual UMaterialExpression* CreateExpression(TSubclassOf<UMaterialExpression> InExpressionClass, const FString& InComment, UObject* InAsset = nullptr) const = 0;` — Creates an expression of the given class and adds it to the material. @param InComment Comment added to the material node. @param InAsset Object assigned to the node, such as a texture.
- L52 _public prototype_ `virtual UMaterialExpression* CreateExpressionParameter(TSubclassOf<UMaterialExpression> InExpressionClass, FName InParameterName, EDMMaterialParameterGroup InParameterGroup, const FString& InComment, UObject* InAsset = nullptr) const = 0;` — Creates an expression of the given class as a parameter and adds it to the material. @param InParameterName The name of the parameter. @param InComment Comment added to the material node. @param InAsset Object assigned to the node, such as a texture.
- L57 _public function_ `InExpressionClass* CreateExpression(const FString& InComment, UObject* InAsset = nullptr) const`
- L64 _public function_ `InExpressionClass* CreateExpressionParameter(FName InParameterName, EDMMaterialParameterGroup InParameterGroup, const FString& InComment, UObject* InAsset = nullptr) const`
- L71 _public prototype_ `virtual TArray<UMaterialExpression*> CreateExpressionInputs(const TArray<FDMMaterialStageConnection>& InInputConnectionMap, int32 InStageSourceInputIdx, const TArray<UDMMaterialStageInput*>& InStageInputs, int32& OutOutputIndex, int32& OutOutputChannel) const = 0;` — Creates a set of expressions merging all the inputs for each channel into a single output
- L76 _public prototype_ `virtual TArray<UMaterialExpression*> CreateExpressionInput(UDMMaterialStageInput* InInput) const = 0;` — Creates a set of expressions that display this material stage input.
- L79 _public prototype_ `virtual int32 FindOutputForBitmask(UMaterialExpression* InExpression, int32 InOutputChannels) const = 0;` — Searches the outputs of an expression to see if there is an appropriate output to match a requested channel mask. Returns INDEX_NONE on failure.
- L82 _public prototype_ `virtual UMaterialExpressionComponentMask* CreateExpressionBitMask(UMaterialExpression* InExpression, int32 InOutputIndex, int32 InOutputChannels) const = 0;` — Creates a set of expressions merging all the inputs for each channel into a single output
- L86 _public prototype_ `virtual UMaterialExpressionAppendVector* CreateExpressionAppend(UMaterialExpression* InExpressionA, int32 InOutputIndexA, UMaterialExpression* InExpressionB, int32 InOutputIndexB) const = 0;` — Creates an append expression, joining the output of 2 other expressions into a single vector.
- L90 _public prototype_ `virtual void UpdatePreviewMaterial(UMaterialExpression* InLastExpression, int32 InOutputIndex, int32 InOutputChannel, int32 InSize) const = 0;` — Updates a preview material, assigning the output of the "last expression" to an appropriate material property.

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterial/Public/Model/IDynamicMaterialModelEditorOnlyDataInterface.h` (Public)


#### enum `EDMBuildRequestType`  
`enum class EDMBuildRequestType : uint8`  
_L25-38_
- reflection: `UENUM(BlueprintType)`
- L28 _public enumerator_ `Immediate` — Compile the material immediately.
- L31 _public enumerator_ `Async` — Will try to add to the build queue or fallback to immediate compile.
- L37 _public enumerator_ `Preview` — If bAutomaticallyCompilePreviewMaterial is false, will just mark the material as changed, but not actually try to compile. It will fall back to Async if automatic compile is true.

#### class `UDynamicMaterialModelEditorOnlyDataInterface`  
`class UDynamicMaterialModelEditorOnlyDataInterface : public UInterface`  
_L42-45_
- reflection: `UINTERFACE(MinimalAPI, BlueprintType, meta = (CannotImplementInterfaceInBlueprint))`
- inherits: `UInterface`
- desc: Interface for the editor-only data so that editor-only parts of runtime components can interact with editor-only features.

#### class `IDynamicMaterialModelEditorOnlyDataInterface`  
`class IDynamicMaterialModelEditorOnlyDataInterface`  
_L47-87_
- L55 _public prototype_ `virtual void PostEditorDuplicate() = 0;` — Called to ensure that the object hierarchy is correct.
- L58 _public prototype_ `virtual void OnValueUpdated(UDMMaterialValue* InValue, EDMUpdateType InUpdateType) = 0;` — Called when a value is updated.
- L61 _public prototype_ `virtual void OnValueListUpdate() = 0;` — Called when a value is added or removed.
- L64 _public prototype_ `virtual void OnTextureUVUpdated(UDMTextureUV* InTextureUV) = 0;` — Called when a texture uv is updated.
- L69 _public prototype_ `virtual void RequestMaterialBuild(EDMBuildRequestType InRequestType = EDMBuildRequestType::Preview) PURE_VIRTUAL(UDynamicMaterialModelEditorOnlyDataInterface::RequestMaterialBuild) virtual TSharedRef<IDMMaterialBuildStateInterface> CreateBuildStateInterface(UMaterial* InMaterialToBuild) const = 0;` — `UFUNCTION(BlueprintCallable, Category = "Material Designer")` — Called when the model needs to have the material rebuild.
- L75 _public prototype_ `virtual void SetPropertyComponent(EDMMaterialPropertyType InPropertyType, FName InComponentName, UDMMaterialComponent* InComponent) = 0;` — Sets the component on a material property (such as a global parameter).
- L79 _public prototype_ `virtual UDMMaterialComponent* GetSubComponentByPath(FDMComponentPath& InPath) const = 0;` — Searches the model editor only data for a specific component based on a path.
- L82 _public prototype_ `virtual UDMMaterialComponent* GetSubComponentByPath(FDMComponentPath& InPath, const FDMComponentPathSegment& InPathSegment) const = 0;` — Searches the model editor only data for a specific component based on a path.
- L86 _protected prototype_ `virtual void ReinitComponents() = 0;` — Called to ensure that all editor only data is correctly initialized.

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterial/Public/Utils/DMJsonUtils.h` (Public)


#### class `UDMJsonSerializable`  
`class UDMJsonSerializable : public UInterface`  
_L19-22_
- reflection: `UINTERFACE(MinimalAPI, Blueprintable, BlueprintType)`
- inherits: `UInterface`
- desc: Offers custom serialization options for class.

#### class `IDMJsonSerializable`  
`class IDMJsonSerializable`  
_L24-31_

#### class `FDMJsonUtils`  
`class FDMJsonUtils`  
_L35-170_
- desc: Wrapper library to allow quicker (de)serialization to JSON.
- L38 _public prototype_ `static TSharedPtr<FJsonValue> Serialize(bool bInValue);`
- L39 _public prototype_ `static TSharedPtr<FJsonValue> Serialize(const FString& InString);`
- L40 _public prototype_ `static TSharedPtr<FJsonValue> Serialize(const FText& InText);`
- L41 _public prototype_ `static TSharedPtr<FJsonValue> Serialize(const FName& InName);`
- L42 _public prototype_ `static TSharedPtr<FJsonValue> Serialize(const UClass* InClass);`
- L43 _public prototype_ `static TSharedPtr<FJsonValue> Serialize(const UScriptStruct* InScriptStruct, const void* InData);`
- L44 _public prototype_ `static TSharedPtr<FJsonValue> Serialize(const UObject* InObject);`
- L45 _public prototype_ `static TSharedPtr<FJsonValue> Serialize(const FObjectPtr& InObject);`
- L46 _public prototype_ `static TSharedPtr<FJsonValue> Serialize(const TMap<FJsonObject::FStringType, TSharedPtr<FJsonValue>>& InMap);`
- L50 _public function_ `static TSharedPtr<FJsonValue> Serialize(InArithmeticType InValue)`
- L57 _public function_ `static TSharedPtr<FJsonValue> Serialize(InEnumType InValue)`
- L64 _public function_ `static TSharedPtr<FJsonValue> Serialize(const InStructType& InStruct)`
- L71 _public function_ `static TSharedPtr<FJsonValue> Serialize(const TSubclassOf<InClassType>& InClass)`
- L76 _public prototype_ `static bool Deserialize(const TSharedPtr<FJsonValue>& InJsonValue, bool& bOutValue);`
- L77 _public prototype_ `static bool Deserialize(const TSharedPtr<FJsonValue>& InJsonValue, FString& OutString);`
- L78 _public prototype_ `static bool Deserialize(const TSharedPtr<FJsonValue>& InJsonValue, FText& OutText);`
- L79 _public prototype_ `static bool Deserialize(const TSharedPtr<FJsonValue>& InJsonValue, FName& OutName);`
- L80 _public prototype_ `static bool Deserialize(const TSharedPtr<FJsonValue>& InJsonValue, UClass*& OutClass);`
- L81 _public prototype_ `static bool Deserialize(const TSharedPtr<FJsonValue>& InJsonValue, const UScriptStruct* InScriptStruct, void* OutData);`
- L82 _public prototype_ `static bool Deserialize(const TSharedPtr<FJsonValue>& InJsonValue, const UEnum* InEnum, int64& OutValue);`
- L83 _public prototype_ `static bool Deserialize(const TSharedPtr<FJsonValue>& InJsonValue, UObject*& OutObject, UObject* InOuter = nullptr);`
- L84 _public prototype_ `static bool Deserialize(const TSharedPtr<FJsonValue>& InJsonValue, FObjectPtr& OutObject, UObject* InOuter = nullptr);`
- L85 _public prototype_ `static bool Deserialize(const TSharedPtr<FJsonValue>& InJsonValue, TMap<FJsonObject::FStringType, TSharedPtr<FJsonValue>>& OutMap);`
- L89 _public function_ `static bool Deserialize(const TSharedPtr<FJsonValue>& InJsonValue, InArithmeticType& OutValue)`
- L111 _public function_ `static bool Deserialize(const TSharedPtr<FJsonValue>& InJsonValue, InEnumType& OutValue)`
- L126 _public function_ `static bool Deserialize(const TSharedPtr<FJsonValue>& InJsonValue, InStructType& OutStruct)`
- L133 _public function_ `static bool Deserialize(const TSharedPtr<FJsonValue>& InJsonValue, InClassType*& OutObject, UObject* InOuter = nullptr)`
- L151 _public function_ `static bool Deserialize(const TSharedPtr<FJsonValue>& InJsonValue, TSubclassOf<InClassType>& OutSubclass)`
- L168 _private prototype_ `static TSharedPtr<FJsonValue> SerializeNumber(double InNumber);`
- L169 _private prototype_ `static bool DeserializeNumber(const TSharedPtr<FJsonValue>& InJsonValue, double& OutNumber);`

### `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterial/Public/Utils/DMUtils.h` (Public)


#### struct `FDMUtils`  
`struct FDMUtils`  
_L13-31_
- desc: General utilities for use with the Material Designer.
- L17 _public prototype_ `static FString CreateNodeComment(const ANSICHAR* InFile, int InLine, const ANSICHAR* InFunction, const FString* InComment = nullptr);` — Designed to be used with preprocessor macros.
- L21 _public prototype_ `static EDMTextureSetMaterialProperty MaterialPropertyTypeToTextureSetMaterialProperty(EDMMaterialPropertyType InPropertyType);` — Converts EDMMaterialPropertyType to EDMTextureSetMaterialProperty.
- L24 _public prototype_ `static EDMMaterialPropertyType TextureSetMaterialPropertyToMaterialPropertyType(EDMTextureSetMaterialProperty InPropertyType);` — Converts EDMTextureSetMaterialProperty to EDMMaterialPropertyType.
- L27 _public prototype_ `static EMaterialProperty MaterialPropertyTypeToMaterialProperty(EDMMaterialPropertyType InPropertyType);` — Converts EDMMaterialPropertyType to EMaterialProperty.
- L30 _public prototype_ `static EDMMaterialPropertyType MaterialPropertyToMaterialPropertyType(EMaterialProperty InPropertyType);` — Converts EMaterialProperty to EDMMaterialPropertyType.

#### Free symbols / members of external scopes

- L34 _macro_ `#define UE_DM_NodeComment_Default FDMUtils::CreateNodeComment(__FILE__, __LINE__, __FUNCTION__)`
- L35 _macro_ `#define UE_DM_NodeComment(Comment) FDMUtils::CreateNodeComment(__FILE__, __LINE__, __FUNCTION__, &Comment)`
