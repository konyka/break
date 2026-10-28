# Runtime / FieldSystemEngine

- module root: `Source/Runtime/Experimental/FieldSystem/Source/FieldSystemEngine`
- headers: 6; symbols: 251
- symbol kinds: class=29, function=47, member=79, prototype=94, struct=2
- PublicDependencyModuleNames: Chaos, ChaosSolverEngine, Core, CoreUObject, Engine, PhysicsCore, RHI, RenderCore

### `Source/Runtime/Experimental/FieldSystem/Source/FieldSystemEngine/Private/Field/FieldSystemSceneProxy.h` (Private)


#### struct `FFieldSystemSampleData`  
`struct FFieldSystemSampleData`  
_L11-13_
- desc: Immutable rendering data

#### class `FFieldSystemSceneProxy`  
`class FFieldSystemSceneProxy final : public FPrimitiveSceneProxy`  
_L20-42_
- inherits: `FPrimitiveSceneProxy`
- desc: FFieldSystemSceneProxy
- L24 _public prototype_ `FFieldSystemSceneProxy(UFieldSystemComponent* Component);`
- L27 _public prototype_ `virtual ~FFieldSystemSceneProxy();` — virtual destructor
- L29 _public function_ `SIZE_T GetTypeHash() const override`
- L36 _public function_ `virtual uint32 GetMemoryFootprint(void) const override` — @todo allocated size : make this reflect internally allocated memory.
- L39 _public function_ `SIZE_T GetAllocatedSize(void) const` — Size of the base class

### `Source/Runtime/Experimental/FieldSystem/Source/FieldSystemEngine/Public/Field/FieldSystemActor.h` (Public)


#### class `AFieldSystemActor`  
`class AFieldSystemActor: public AActor`  
_L18-29_
- reflection: `UCLASS(meta=(ChildCanTick), MinimalAPI)`
- inherits: `AActor`
- L26 _public member_ `TObjectPtr<UFieldSystemComponent> FieldSystemComponent;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Field, meta = (ExposeFunctionCategories = "Components|FieldSystem", AllowPrivateAccess = "true"))` — FieldSystemComponent
- L27 _public function_ `UFieldSystemComponent* GetFieldSystemComponent() const`
- L28 _public prototype_ `virtual void OnConstruction(const FTransform& Transform) override;`

### `Source/Runtime/Experimental/FieldSystem/Source/FieldSystemEngine/Public/Field/FieldSystemAsset.h` (Public)


#### class `UFieldSystem`  
`class UFieldSystem : public UObject`  
_L20-35_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- L26 _public function_ `UFieldSystem() : UObject()`
- L27 _public prototype_ `virtual ~UFieldSystem() = default;`
- L29 _public function_ `void Reset()`
- L31 _public prototype_ `void Serialize(FArchive& Ar);`
- L33 _public member_ `TArray< FFieldSystemCommand > Commands;`

### `Source/Runtime/Experimental/FieldSystem/Source/FieldSystemEngine/Public/Field/FieldSystemComponent.h` (Public)


#### class `UFieldSystemComponent`  
`class UFieldSystemComponent : public UPrimitiveComponent`  
_L37-325_
- reflection: `UCLASS(meta = (BlueprintSpawnableComponent), MinimalAPI)`
- inherits: `UPrimitiveComponent`
- desc: FieldSystemComponent
- L44 _public function_ `virtual bool HasAnySockets() const override`
- L48 _public prototype_ `virtual FPrimitiveSceneProxy* CreateSceneProxy() override;`
- L52 _public function_ `void SetFieldSystem(UFieldSystem* FieldSystemIn)` — Set the field system asset @todo(remove the field system, we dont need the asset
- L55 _public function_ `inline const UFieldSystem* GetFieldSystem() const` — Get the field system asset
- L59 _public member_ `TObjectPtr<UFieldSystem> FieldSystem;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, BlueprintReadOnly, Category = "Field", meta = (ToolTip = "Field system asset to be used to store the construction fields. This asset is not required anymore and will be deprecated soon."))` — Field system asset to be used to store the construction fields
- L63 _public member_ `bool bIsWorldField;` — `UPROPERTY(EditAnywhere, Category = "Field", meta = (ToolTip = "If enabled the field will be pushed to the world fields and will be available to materials and niagara"))` — If enabled the field will be pushed to the world fields and will be available to materials and niagara
- L67 _public member_ `bool bIsChaosField;` — `UPROPERTY(EditAnywhere, Category = "Field", meta = (ToolTip = "If enabled the field will be used by all the chaos solvers"))` — If enabled the field will be used by all the chaos solvers
- L71 _public member_ `TArray<TSoftObjectPtr<AChaosSolverActor>> SupportedSolvers;` — `UPROPERTY(EditAnywhere, Category = "Field", meta = (EditCondition = "bIsChaosField == true", ToolTip = "List of chaos solvers that will use the field"))` — List of solvers this field will affect. An empty list makes this field affect all solvers.
- L75 _public member_ `FFieldObjectCommands ConstructionCommands;` — `UPROPERTY()` — List of all the construction command
- L79 _public member_ `FFieldObjectCommands BufferCommands;` — `UPROPERTY()` — List of all the buffer command
- L96 _public prototype_ `void ApplyLinearForce(UPARAM(DisplayName = "Enable Field") bool Enabled, UPARAM(DisplayName = "Uniform Direction") FVector Direction, UPARAM(DisplayName = "Field Magnitude") fl` — `UFUNCTION(BlueprintCallable, Category = "Field", DisplayName = "Apply Uniform Force", meta = (UnsafeDuringActorConstruction = "true"))` — ApplyUniformForce This function will dispatch a command to the physics thread to apply a uniform linear force on each particle within the simulation. @param Enabled Is this force enabled for evaluation. @param Direction The direction of the linear force @param Magnitude The size of the linear force.
- L111 _public prototype_ `void ApplyStayDynamicField(UPARAM(DisplayName = "Enable Field") bool Enabled, UPARAM(DisplayName = "Center Position") FVector Position, UPARAM(DisplayName = "Field Radius") fl` — `UFUNCTION(BlueprintCallable, Category = "Field", DisplayName = "Set Dynamic State", meta = (UnsafeDuringActorConstruction = "true"))` — SetDynamicState This function will dispatch a command to the physics thread to apply a kinematic to dynamic state change for the particles within the field. @param Enabled Is this force enabled for evaluation. @param Position The location of the command @param Radius Radial influence from the position
- L126 _public prototype_ `void ApplyRadialForce(UPARAM(DisplayName = "Enable Field") bool Enabled, UPARAM(DisplayName = "Center Position") FVector Position, UPARAM(DisplayName = "Field Magnitude") fl` — `UFUNCTION(BlueprintCallable, Category = "Field", DisplayName = "Apply Radial Force", meta = (UnsafeDuringActorConstruction = "true"))` — ApplyRadialForce This function will dispatch a command to the physics thread to apply a linear force that points away from a position. @param Enabled Is this force enabled for evaluation. @param Position The origin point of the force @param Magnitude The size of the linear force.
- L143 _public prototype_ `void ApplyRadialVectorFalloffForce(UPARAM(DisplayName = "Enable Field") bool Enabled, UPARAM(DisplayName = "Center Position") FVector Position, UPARAM(DisplayName = "Falloff Radius") float Radius, UPARAM(DisplayName = "Field Magnitude") fl` — `UFUNCTION(BlueprintCallable, Category = "Field", DisplayName = "Falloff Radial Force", meta = (UnsafeDuringActorConstruction = "true"))` — FalloffRadialForce This function will dispatch a command to the physics thread to apply a linear force from a position in space. The force vector is weaker as it moves away from the center. @param Enabled Is this force enabled for evaluation. @param Position The origin point of the force @param Radius Radial influence from the position, positions further away are weaker. @param Magnitude The size of the linear force.
- L162 _public prototype_ `void ApplyUniformVectorFalloffForce(UPARAM(DisplayName = "Enable Field") bool Enabled, UPARAM(DisplayName = "Center Position") FVector Position, UPARAM(DisplayName = "Uniform Direction") FVector Direction, UPARAM(DisplayName = "Falloff Radius") float Radius, UPARAM(DisplayName = "Field Magnitude") fl` — `UFUNCTION(BlueprintCallable, Category = "Field", DisplayName = "Falloff Uniform Force", meta = (UnsafeDuringActorConstruction = "true"))` — FalloffUniformForce This function will dispatch a command to the physics thread to apply a linear force in a uniform direction. The force vector is weaker as it moves away from the center. @param Enabled Is this force enabled for evaluation. @param Position The origin point of the force @param Direction The direction of the linear force @param Radius Radial influence from the position, positions further away are weaker. @param Magnitude The size of the linear force.
- L182 _public prototype_ `void ApplyStrainField(UPARAM(DisplayName = "Enable Field") bool Enabled, UPARAM(DisplayName = "Center Position") FVector Position, UPARAM(DisplayName = "Falloff Radius") float Radius, UPARAM(DisplayName = "Field Magnitude") float Magnitude, UPARAM(DisplayName = "Cluster Levels") int3` — `UFUNCTION(BlueprintCallable, Category = "Field", DisplayName = "Apply External Strain", meta = (UnsafeDuringActorConstruction = "true"))` — ApplyExternalStran This function will dispatch a command to the physics thread to apply a strain field on a clustered set of geometry. This is used to trigger a breaking event within the solver. @param Enabled Is this force enabled for evaluation. @param Position The origin point of the force @param Radius Radial influence from the position, positions further away are weaker. @param Magnitude The size of the linear force. @param Iterations Levels of evaluation into the cluster hierarchy.
- L202 _public prototype_ `void ApplyPhysicsField(UPARAM(DisplayName = "Enable Field") bool Enabled, UPARAM(DisplayName = "Physics Type") EFieldPhysicsType Target, UPARAM(DisplayName = "Meta Data") UFieldSystemMetaData* MetaData, UPARAM(DisplayName = "Field Node") UFieldNodeBas` — `UFUNCTION(BlueprintCallable, Category = "Field", DisplayName = "Add Transient Field", meta = (UnsafeDuringActorConstruction = "true"))` — AddTransientField This function will dispatch a command to the physics thread to apply a generic evaluation of a user defined transient field network. See documentation, for examples of how to recreate variations of the above generic fields using field networks @param Enabled Is this force enabled for evaluation. @param Target Type of field supported by the solver. @param MetaData Meta data used to assist in evaluation @param Field Base evaluation node for the field network.
- L226 _public prototype_ `void AddPersistentField(UPARAM(DisplayName = "Enable Field") bool Enabled, UPARAM(DisplayName = "Physics Type") EFieldPhysicsType Target, UPARAM(DisplayName = "Meta Data") UFieldSystemMetaData* MetaData, UPARAM(DisplayName = "Field Node") UFieldNodeBas` — `UFUNCTION(BlueprintCallable, Category = "Field", DisplayName = "Add Persistent Field", meta = (UnsafeDuringActorConstruction = "true"))` — AddPersistentField This function will dispatch a command to the physics thread to apply a generic evaluation of a user defined field network. This command will be persistent in time and will live until the component is destroyed or until the RemovePersistenFields function is called. See documentation, for examples of how to recreate variations of the above generic fields using field networks @param Enabled Is this force enabled for evaluation. @param Target Type of field supported by the solver. @param MetaData Meta data used to assist in evaluation @param Field Base evaluation node for the field network.
- L237 _public prototype_ `void RemovePersistentFields();` — `UFUNCTION(BlueprintCallable, Category = "Field", DisplayName = "Remove Persistent Fields", meta = (UnsafeDuringActorConstruction = "true"))` — RemovePersistentFields This function will remove all the field component persistent fields from chaos and from the world
- L259 _public prototype_ `void AddFieldCommand(UPARAM(DisplayName = "Enable Field") bool Enabled, UPARAM(DisplayName = "Physics Type") EFieldPhysicsType Target, UPARAM(DisplayName = "Meta Data") UFieldSystemMetaData* MetaData, UPARAM(DisplayName = "Field Node") UFieldNodeBas` — `UFUNCTION(BlueprintCallable, Category = "Field", DisplayName = "Add Construction Field")`
- L271 _public prototype_ `void ResetFieldSystem();` — `UFUNCTION(BlueprintCallable, Category = "Field", DisplayName = "Remove Construction Fields")`
- L274 _public function_ `const TArray< FFieldSystemCommand >& GetConstructionFields() const` — Get all the construction fields
- L279 _protected prototype_ `TSet<FPhysScene_Chaos*> GetPhysicsScenes() const;` — Get ell ethe supported physics scenes
- L282 _protected prototype_ `TArray<Chaos::FPhysicsSolverBase*> GetPhysicsSolvers() const;` — Get ell the supported physics solvers
- L285 _protected prototype_ `void BuildFieldCommand(bool Enabled, EFieldPhysicsType Target, UFieldSystemMetaData* MetaData, UFieldNodeBase* Field, const bool IsTransient);` — Build a physics field command and dispatch it
- L288 _protected prototype_ `void DispatchFieldCommand(const FFieldSystemCommand& InCommand, const bool IsTransient);` — Dispatch the field command to chaos/world
- L291 _protected prototype_ `void ClearFieldCommands();` — Remove the persistent commands from chaos/world
- L294 _protected prototype_ `virtual void OnCreatePhysicsState() override;`
- L295 _protected prototype_ `virtual void OnDestroyPhysicsState() override;`
- L296 _protected prototype_ `virtual bool ShouldCreatePhysicsState() const override;`
- L297 _protected prototype_ `virtual bool HasValidPhysicsState() const override;`
- L302 _protected member_ `bool bEnableInEditorWorlds;` — `UPROPERTY(EditDefaultsOnly, Category=Field)` — Whether to intialise this component in Editor worlds
- L306 _protected member_ `bool bEnableInPreviewWorlds;` — `UPROPERTY(EditDefaultsOnly, Category=Field)` — Whether to intialise this component in Preview worlds (both game and editor)
- L309 _protected member_ `FChaosSolversModule* ChaosModule;` — Chaos module linked to that component
- L312 _protected member_ `bool bHasPhysicsState;` — Boolean to check that the physics state has been built
- L315 _protected member_ `TArray< FFieldSystemCommand > SetupConstructionFields;` — List of all the field used to setup chaos (anchor...)
- L318 _protected member_ `TArray< FFieldSystemCommand > ChaosPersistentFields;` — List of all the chaos peristent fields
- L321 _protected member_ `TArray< FFieldSystemCommand > WorldGPUPersistentFields;` — List of the world GPU peristent fields created by this field component
- L324 _protected member_ `TArray< FFieldSystemCommand > WorldCPUPersistentFields;` — List of the world CPU peristent fields created by this field component

### `Source/Runtime/Experimental/FieldSystem/Source/FieldSystemEngine/Public/Field/FieldSystemComponentTypes.h` (Public)
_(no declarations extracted)_

### `Source/Runtime/Experimental/FieldSystem/Source/FieldSystemEngine/Public/Field/FieldSystemObjects.h` (Public)


#### class `UFieldSystemMetaData`  
`class UFieldSystemMetaData : public UActorComponent`  
_L23-31_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UActorComponent`
- desc: Context : Contexts are used to pass extra data into the field evaluation.
- L28 _public prototype_ `virtual ~UFieldSystemMetaData() = default;`
- L29 _public function_ `virtual FFieldSystemMetaData::EMetaType Type() const`
- L30 _public function_ `virtual FFieldSystemMetaData* NewMetaData() const`

#### class `UFieldSystemMetaDataIteration`  
`class UFieldSystemMetaDataIteration : public UFieldSystemMetaData`  
_L37-57_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UFieldSystemMetaData`
- desc: UFieldSystemMetaDataIteration : Not used anymore, just hiding it right now but will probably be deprecated if not used in the future
- L42 _public prototype_ `virtual ~UFieldSystemMetaDataIteration() = default;`
- L43 _public function_ `virtual FFieldSystemMetaData::EMetaType Type() const override`
- L45 _public prototype_ `virtual FFieldSystemMetaData* NewMetaData() const override;`
- L52 _public prototype_ `UFieldSystemMetaDataIteration* SetMetaDataIteration(UPARAM(DisplayName = "Iteration Count") i` — `UFUNCTION(BlueprintPure, Category = "Field", meta = (Iterations = "1"))` — Set the number of iteration type @param    Iterations Number of iterations (WIP)
- L56 _public member_ `int Iterations;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Field", DisplayName = "Iteration Count")` — Number of iterations (WIP)

#### class `UFieldSystemMetaDataProcessingResolution`  
`class UFieldSystemMetaDataProcessingResolution : public UFieldSystemMetaData`  
_L63-82_
- reflection: `UCLASS(ClassGroup = "Field", meta = (BlueprintSpawnableComponent, ToolTip = "Control the set of particles on which the field will be applied"), ShowCategories = ("Field"), DisplayName = "MetaDataResolution", MinimalAPI)`
- inherits: `UFieldSystemMetaData`
- desc: UFieldSystemMetaDataProcessingResolution
- L68 _public prototype_ `virtual ~UFieldSystemMetaDataProcessingResolution() = default;`
- L69 _public function_ `virtual FFieldSystemMetaData::EMetaType Type() const override`
- L70 _public prototype_ `virtual FFieldSystemMetaData* NewMetaData() const override;`
- L77 _public prototype_ `UFieldSystemMetaDataProcessingResolution* SetMetaDataaProcessingResolutionType(EFieldResolutionType ResolutionType);` — `UFUNCTION(BlueprintPure, Category = "Field", DisplayName = "Set Meta Data Resolution")` — Set the processing resolution type @param    ResolutionType Type of processing resolution used to select the particles on which the field will be applied
- L81 _public member_ `TEnumAsByte<EFieldResolutionType> ResolutionType;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Field")` — Precessing resolution type used to select the particles on which the field will be applied

#### class `UFieldSystemMetaDataFilter`  
`class UFieldSystemMetaDataFilter : public UFieldSystemMetaData`  
_L88-119_
- reflection: `UCLASS(ClassGroup = "Field", meta = (BlueprintSpawnableComponent, ToolTip = "Filter the particles on which the field will be applied"), ShowCategories = ("Field"), DisplayName = "MetaDataFilter", MinimalAPI)`
- inherits: `UFieldSystemMetaData`
- desc: UFieldSystemMetaDataFilter
- L93 _public prototype_ `virtual ~UFieldSystemMetaDataFilter() = default;`
- L94 _public function_ `virtual FFieldSystemMetaData::EMetaType Type() const override`
- L95 _public prototype_ `virtual FFieldSystemMetaData* NewMetaData() const override;`
- L104 _public prototype_ `UFieldSystemMetaDataFilter* SetMetaDataFilterType(UPARAM(DisplayName = "State Type") EFieldFilterType FilterType, UPARAM(DisplayName = "Object Type") EFieldObjectType ObjectType, UPARAM(DisplayName = "Position Type") EFieldPositionType Po` — `UFUNCTION(BlueprintPure, Category = "Field", DisplayName = "Set Meta Data Filter")` — Set the particles filter type @param    FilterType State type used to select the state particles on which the field will be applied @param    ObjectType Object type used to select the type of objects(rigid, cloth...) on which the field will be applied @param    PositionType Position type used to compute the samples positions
- L110 _public member_ `TEnumAsByte<EFieldFilterType> FilterType;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Field", DisplayName = "State Type")` — Filter state type used to select the particles on which the field will be applied
- L114 _public member_ `TEnumAsByte<EFieldObjectType> ObjectType;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Field", DisplayName = "Object Type")` — Filter object type used to select the particles on which the field will be applied
- L118 _public member_ `TEnumAsByte<EFieldPositionType> PositionType;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Field", DisplayName = "Position Type")` — Specify which position type will be used for the field evaluation

#### class `UFieldNodeBase`  
`class UFieldNodeBase : public UActorComponent`  
_L125-134_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UActorComponent`
- desc: Field Evaluation
- L130 _public prototype_ `virtual ~UFieldNodeBase() = default;`
- L131 _public function_ `virtual FFieldNodeBase::EFieldType Type() const`
- L132 _public function_ `virtual bool ResultsExpector() const`
- L133 _public function_ `virtual FFieldNodeBase* NewEvaluationGraph(TArray<const UFieldNodeBase*>& Nodes) const`

#### class `UFieldNodeInt`  
`class UFieldNodeInt : public UFieldNodeBase`  
_L141-148_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UFieldNodeBase`
- desc: FieldNodeInt
- L146 _public prototype_ `virtual ~UFieldNodeInt() = default;`
- L147 _public function_ `virtual FFieldNodeBase::EFieldType Type() const override`

#### class `UFieldNodeFloat`  
`class UFieldNodeFloat : public UFieldNodeBase`  
_L154-161_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UFieldNodeBase`
- desc: FieldNodeFloat
- L159 _public prototype_ `virtual ~UFieldNodeFloat() = default;`
- L160 _public function_ `virtual FFieldNodeBase::EFieldType Type() const override`

#### class `UFieldNodeVector`  
`class UFieldNodeVector : public UFieldNodeBase`  
_L167-173_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UFieldNodeBase`
- desc: FieldNodeVector
- L171 _public prototype_ `virtual ~UFieldNodeVector() = default;`
- L172 _public function_ `virtual FFieldNodeBase::EFieldType Type() const override`

#### class `UUniformInteger`  
`class UUniformInteger : public UFieldNodeInt`  
_L180-204_
- reflection: `UCLASS(ClassGroup = "Field", meta = (BlueprintSpawnableComponent, ToolTip = "Set a uniform integer value independently of the sample position. The output is equal to magnitude"), ShowCategories = ("Field"), MinimalAPI)`
- inherits: `UFieldNodeInt`
- desc: UUniformInteger
- L185 _public function_ `UUniformInteger() : Super() , Magnitude(0)`
- L190 _public prototype_ `virtual ~UUniformInteger() = default;`
- L192 _public prototype_ `virtual FFieldNodeBase* NewEvaluationGraph(TArray<const UFieldNodeBase*>& Nodes) const override;`
- L199 _public prototype_ `UUniformInteger* SetUniformInteger(UPARAM(DisplayName = "Field Magnitude") in` — `UFUNCTION(BlueprintPure, Category = "Field", meta = (Magnitude = "0"))` — Set a uniform integer value independently of the sample position. The output is equal to magnitude @param    Magnitude The field output will be equal the magnitude
- L203 _public member_ `int32 Magnitude;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Field", DisplayName = "Field Magnitude")` — The field output will be equal the magnitude

#### class `URadialIntMask`  
`class URadialIntMask : public UFieldNodeInt`  
_L211-265_
- reflection: `UCLASS(ClassGroup = "Field", meta = (BlueprintSpawnableComponent, ToolTip = "This function first defines a radial integer field equal to Interior-value inside a sphere / Exterior-value outside. This field will be used alongside the particle input value and the mask condition to compute the particle output value."), ShowCategories = ("Field"), MinimalAPI)`
- inherits: `UFieldNodeInt`
- desc: URadialIntMask
- L216 _public function_ `URadialIntMask() : Super() , Radius(0) , Position(FVector(0, 0, 0)) , InteriorValue(1) , ExteriorValue(0) , SetMaskCondition(ESetMaskConditionType::Field_Set_Always)`
- L224 _public prototype_ `virtual ~URadialIntMask() = default;`
- L226 _public prototype_ `virtual FFieldNodeBase* NewEvaluationGraph(TArray<const UFieldNodeBase*>& Nodes) const override;`
- L240 _public prototype_ `URadialIntMask* SetRadialIntMask(UPARAM(DisplayName = "Mask Radius") float Radius, UPARAM(DisplayName = "Center Position") FVector Position, UPARAM(DisplayName = "Interior Value") int32 InteriorValue, UPARAM(DisplayName = "Exterior Value") int32 ExteriorValue, UPARAM(DisplayName = "Mask Condition") ESetMaskConditionType SetMas` — `UFUNCTION(BlueprintPure, Category = "Field", meta = (InteriorValue = "1"), DisplayName = "Set Radial Mask")` — This function first defines a radial integer field equal to Interior-value inside a sphere / Exterior-value outside. This field will be used alongside the particle input value and the mask condition to compute the particle output value. - If Mask-condition = set-always : the particle output value will be equal to Interior-value if the particle position is inside a sphere / Exterior-value otherwise. - If Mask-condition = merge-interior : the particle output value will be equal to Interior-value if the particle position is inside the sphere or if the particle input value is already Interior-Value / Exterior-value otherwise. - If Mask-condition = merge-exterior : the particle output value will be equal to Exterior-value if the particle position is outside the sphere or if the particle input value is already Exterior-Value / Interior-value otherwise. @param    Radius Radius of the radial field @param    Position Center position of the radial field" @param    InteriorValue If the sample distance from the center is less than radius, the intermediate value will be set the interior value @param    ExteriorValue If the sample distance from the center is greater than radius, the intermediate value will be set the exterior value @param    SetMaskConditionIn If the mask condition is set to always the output value will be the intermediate one. If set to not interior/exterior the output value will be the intermediate one if the input is different from the interior/exterior value
- L248 _public member_ `float Radius;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Field", DisplayName = "Mask Radius")` — Radius of the radial mask field
- L252 _public member_ `FVector Position;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Field", DisplayName = "Center Position")` — Center position of the radial mask field
- L256 _public member_ `int32 InteriorValue;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Field", DisplayName = "Interior Value")` — If the sample distance from the center is less than radius, the intermediate value will be set the interior value
- L260 _public member_ `int32 ExteriorValue;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Field", DisplayName = "Exterior Value")` — If the sample distance from the center is greater than radius, the intermediate value will be set the exterior value
- L264 _public member_ `TEnumAsByte<ESetMaskConditionType> SetMaskCondition;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Field", DisplayName = "Mask Condition")` — If the mask condition is set to always the output value will be the intermediate one. If set to not interior/exterior the output value will be the intermediate one if the input is different from the interior/exterior value

#### class `UUniformScalar`  
`class UUniformScalar : public UFieldNodeFloat`  
_L272-297_
- reflection: `UCLASS(ClassGroup = "Field", meta = (BlueprintSpawnableComponent, ToolTip = "Set a uniform scalar value independently of the sample position. The output is equal to magnitude"), ShowCategories = ("Field"), MinimalAPI)`
- inherits: `UFieldNodeFloat`
- desc: UUniformScalar
- L277 _public function_ `UUniformScalar() : Super() , Magnitude(1.0)`
- L282 _public prototype_ `virtual ~UUniformScalar() = default;`
- L284 _public prototype_ `virtual FFieldNodeBase* NewEvaluationGraph(TArray<const UFieldNodeBase*>& Nodes) const override;`
- L291 _public prototype_ `UUniformScalar* SetUniformScalar(UPARAM(DisplayName = "Field Magnitude") fl` — `UFUNCTION(BlueprintPure, Category = "Field", meta = (Magnitude = "1.0"))` — Set a uniform scalar value independently of the sample position. The output is equal to magnitude @param    Magnitude The field output will be equal the magnitude
- L295 _public member_ `float Magnitude;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Field", DisplayName = "Field Magnitude")` — The field output will be equal the magnitude

#### class `UWaveScalar`  
`class UWaveScalar : public UFieldNodeFloat`  
_L303-363_
- reflection: `UCLASS(ClassGroup = "Field", meta = (BlueprintSpawnableComponent, ToolTip = "Set a temporal wave scalar value according to the sample distance from the field position."), ShowCategories = ("Field"), MinimalAPI)`
- inherits: `UFieldNodeFloat`
- desc: UWaveScalar
- L308 _public function_ `UWaveScalar() : Super() , Magnitude(1.0) , Position(0, 0, 0) , Wavelength(10000) , Period(1.0) , Function(EWaveFunctionType::Field_Wave_Cosine) , Falloff(EFieldFalloffType::Field_Falloff_Linear)`
- L318 _public prototype_ `virtual ~UWaveScalar() = default;`
- L320 _public prototype_ `virtual FFieldNodeBase* NewEvaluationGraph(TArray<const UFieldNodeBase*>& Nodes) const override;`
- L332 _public prototype_ `UWaveScalar* SetWaveScalar(UPARAM(DisplayName = "Field Magnitude") float Magnitude, UPARAM(DisplayName = "Center Position") FVector Position, UPARAM(DisplayName = "Wave Length") float Wavelength, UPARAM(DisplayName = "Wave Period") float Period, UPARAM(DisplayName = "Time Offset") float Time, UPARAM(DisplayName = "Wave Function") EWaveFunctionType Function, UPARAM(DisplayName = "Falloff Type") EFieldFalloffTy` — `UFUNCTION(BlueprintPure, Category = "Field", meta = (Magnitude = "1.0", Wavelength = "1000", Period = "1", HidePin = "Time"), DisplayName = "Set Wave Scalar")` — Set a temporal wave scalar value according to the sample distance from the field position. @param    Magnitude Magnitude of the wave function @param    Position Center position of the wave field @param    Wavelength Distance between 2 wave peaks @param    Period Time over which the wave will travel from one peak to another one. The wave velocity is proportional to wavelength/period @param    Function Wave function used for the field @param    Falloff Type of falloff function used if the falloff function is picked
- L342 _public member_ `float Magnitude;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Field", DisplayName = "Field Magnitude")` — Magnitude of the wave function
- L346 _public member_ `FVector Position;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Field", DisplayName = "Center Position")` — Center position of the wave field
- L350 _public member_ `float Wavelength;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Field", DisplayName = "Wave Length")` — Distance between 2 wave peaks
- L354 _public member_ `float Period;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Field", DisplayName = "Wave Period")` — Time over which the wave will travel from one peak to another one. The wave velocity is proportional to wavelength/period
- L358 _public member_ `TEnumAsByte<EWaveFunctionType> Function;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Field", DisplayName = "Wave Function")` — Wave function used for the field
- L362 _public member_ `TEnumAsByte<EFieldFalloffType> Falloff;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Field", DisplayName = "Falloff Type")` — Type of falloff function used if the falloff function is picked

#### class `URadialFalloff`  
`class URadialFalloff : public UFieldNodeFloat`  
_L371-437_
- reflection: `UCLASS(ClassGroup = "Field", meta = (BlueprintSpawnableComponent, ToolTip = "Sphere scalar field that will be defined only within a sphere"), ShowCategories = ("Field"), MinimalAPI)`
- inherits: `UFieldNodeFloat`
- desc: RadialFalloff
- L376 _public function_ `URadialFalloff() : Super() , Magnitude(1.0) , MinRange(0.f) , MaxRange(1.f) , Default(0.f) , Radius(0) , Position(FVector(0, 0, 0)) , Falloff(EFieldFalloffType::Field_Falloff_Linear)`
- L387 _public prototype_ `virtual ~URadialFalloff() = default;`
- L389 _public prototype_ `virtual FFieldNodeBase* NewEvaluationGraph(TArray<const UFieldNodeBase*>& Nodes) const override;`
- L402 _public prototype_ `URadialFalloff* SetRadialFalloff(UPARAM(DisplayName = "Field Magnitude") float Magnitude, UPARAM(DisplayName = "Min Range") float MinRange, UPARAM(DisplayName = "Max Range") float MaxRange, UPARAM(DisplayName = "Default Value") float Default, UPARAM(DisplayName = "Sphere Radius") float Radius, UPARAM(DisplayName = "Center Position") FVector Position, UPARAM(DisplayName = "Falloff Type") EFieldFalloffTy` — `UFUNCTION(BlueprintPure, Category = "Field", meta = (Magnitude = "1.0", MinRange = "0.0", MaxRange = "1.0"), DisplayName = "Set Radial Falloff")` — Sphere scalar field that will be defined only within a sphere @param    Magnitude Magnitude of the sphere falloff field @param    MinRange The initial function value between 0 and 1 will be scaled between MinRange and MaxRange before being multiplied by magnitude @param    MaxRange The initial function value between 0 and 1 will be scaled between MinRange and MaxRange before being multiplied by magnitude @param    Default The field value will be set to Default if the sample distance from the center is higher than the radius @param    Radius Radius of the sphere falloff field @param    Position Center position of the sphere falloff field @param    Falloff Type of falloff function used if the falloff function is picked
- L412 _public member_ `float Magnitude;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Field", DisplayName = "Field Magnitude")` — Magnitude of the sphere falloff field
- L416 _public member_ `float MinRange;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Field", DisplayName = "Min Range")` — The initial function value between 0 and 1 will be scaled between MinRange and MaxRange before being multiplied by magnitude
- L420 _public member_ `float MaxRange;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Field", DisplayName = "Max Range")` — The initial function value between 0 and 1 will be scaled between MinRange and MaxRange before being multiplied by magnitude
- L424 _public member_ `float Default;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Field", DisplayName = "Default Value")` — The field value will be set to Default if the sample distance from the center is higher than the radius
- L428 _public member_ `float Radius;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Field", DisplayName = "Sphere Radius")` — Radius of the sphere falloff field
- L432 _public member_ `FVector Position;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Field", DisplayName = "Center Position")` — Center position of the sphere falloff field
- L436 _public member_ `TEnumAsByte<EFieldFalloffType> Falloff;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Field", DisplayName = "Falloff Type")` — Type of falloff function used to model the evolution of the field from the sphere center to the sample position

#### class `UPlaneFalloff`  
`class UPlaneFalloff : public UFieldNodeFloat`  
_L443-517_
- reflection: `UCLASS(ClassGroup = "Field", meta = (BlueprintSpawnableComponent, ToolTip = "Plane scalar field that will be defined only within a distance from a plane"), ShowCategories = ("Field"), MinimalAPI)`
- inherits: `UFieldNodeFloat`
- desc: PlaneFalloff
- L449 _public function_ `UPlaneFalloff() : Super() , Magnitude(1.0) , MinRange(0.f) , MaxRange(1.f) , Default(0.f) , Distance(0.f) , Position(FVector(0, 0, 0)) , Normal(FVector(0, 0, 1)) , Falloff(EFieldFalloffType::Field_Falloff_Linear)`
- L461 _public prototype_ `virtual ~UPlaneFalloff() = default;`
- L463 _public prototype_ `virtual FFieldNodeBase* NewEvaluationGraph(TArray<const UFieldNodeBase*>& Nodes) const override;`
- L477 _public prototype_ `UPlaneFalloff* SetPlaneFalloff(UPARAM(DisplayName = "Field Magnitude") float Magnitude, UPARAM(DisplayName = "Min Range") float MinRange, UPARAM(DisplayName = "Max Range") float MaxRange, UPARAM(DisplayName = "Default Value") float Default, UPARAM(DisplayName = "Plane Distance") float Distance, UPARAM(DisplayName = "Center Position") FVector Position, UPARAM(DisplayName = "Plane Normal") FVector Normal, UPARAM(DisplayName = "Falloff Type") EFieldFalloffTy` — `UFUNCTION(BlueprintPure, Category = "Field", meta = (Magnitude = "1.0", MinRange = "0.0", MaxRange = "1.0"))` — Plane scalar field that will be defined only within a distance from a plane @param    Magnitude Magnitude of the plane falloff field @param    MinRange The initial function value between 0 and 1 will be scaled between MinRange and MaxRange before being multiplied by magnitude @param    MaxRange The initial function value between 0 and 1 will be scaled between MinRange and MaxRange before being multiplied by magnitude @param    Default The field value will be set to default if the sample projected distance ((Sample Position - Center Position).dot(Plane Normal)) is higher than the Plane Distance @param    Distance Distance limit for the plane falloff field starting from the center position and extending in the direction of the plane normal @param    Position Plane center position of the plane falloff field @param    Normal Plane normal of the plane falloff field @param    Falloff Type of falloff function used to model the evolution of the field from the plane surface to the distance isosurface
- L488 _public member_ `float Magnitude;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Field", DisplayName = "Field Magnitude")` — Magnitude of the plane falloff field
- L492 _public member_ `float MinRange;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Field", DisplayName = "Min Range")` — The initial function value between 0 and 1 will be scaled between MinRange and MaxRange before being multiplied by magnitude
- L496 _public member_ `float MaxRange;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Field", DisplayName = "Max Range")` — The initial function value between 0 and 1 will be scaled between MinRange and MaxRange before being multiplied by magnitude
- L500 _public member_ `float Default;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Field", DisplayName = "Default Value")` — The field value will be set to Default if the sample distance from the plane is higher than the distance
- L504 _public member_ `float Distance;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Field", DisplayName = "Plane Distance")` — Distance limit for the plane falloff field
- L508 _public member_ `FVector Position;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Field", DisplayName = "Center Position")` — Plane position of the plane falloff field
- L512 _public member_ `FVector Normal;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Field", DisplayName = "Plane Normal")` — Plane normal of the plane falloff field
- L516 _public member_ `TEnumAsByte<EFieldFalloffType> Falloff;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Field", DisplayName = "Falloff Type")` — Type of falloff function used to model the evolution of the field from the plane surface to the distance isosurface

#### class `UBoxFalloff`  
`class UBoxFalloff : public UFieldNodeFloat`  
_L523-583_
- reflection: `UCLASS(ClassGroup = "Field", meta = (BlueprintSpawnableComponent, ToolTip = "Box scalar field that will be defined only within a box"), ShowCategories = ("Field"), MinimalAPI)`
- inherits: `UFieldNodeFloat`
- desc: BoxFalloff
- L529 _public function_ `UBoxFalloff() : Super() , Magnitude(1.0) , MinRange(0.f) , MaxRange(1.f) , Default(0.0) , Transform(FTransform::Identity) , Falloff(EFieldFalloffType::Field_Falloff_Linear)`
- L539 _public prototype_ `virtual ~UBoxFalloff() = default;`
- L541 _public prototype_ `virtual FFieldNodeBase* NewEvaluationGraph(TArray<const UFieldNodeBase*>& Nodes) const override;`
- L553 _public prototype_ `UBoxFalloff* SetBoxFalloff(UPARAM(DisplayName = "Field Magnitude") float Magnitude, UPARAM(DisplayName = "Min Range") float MinRange, UPARAM(DisplayName = "Max Range") float MaxRange, UPARAM(DisplayName = "Default Value") float Default, UPARAM(DisplayName = "Box Transform") FTransform Transform, UPARAM(DisplayName = "Falloff Type") EFieldFalloffTy` — `UFUNCTION(BlueprintPure, Category = "Field", meta = (Magnitude = "1.0", MinRange = "0.0", MaxRange = "1.0"))` — Box scalar field that will be defined only within a box @param    Magnitude Magnitude of the box falloff field @param    MinRange The initial function value between 0 and 1 will be scaled between MinRange and MaxRange before being multiplied by magnitude @param    MaxRange The initial function value between 0 and 1 will be scaled between MinRange and MaxRange before being multiplied by magnitude @param    Default The field value will be set to Default if the sample distance from the box is higher than the scale of the transform @param    Transform Translation, Rotation and Scale of the unit box @param    Falloff Type of falloff function used to model the evolution of the field from the box surface to the sample position
- L562 _public member_ `float Magnitude;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Field", DisplayName = "Field Magnitude")` — Magnitude of the box falloff field
- L566 _public member_ `float MinRange;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Field", DisplayName = "Min Range")` — The initial function value between 0 and 1 will be scaled between MinRange and MaxRange before being multiplied by magnitude
- L570 _public member_ `float MaxRange;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Field", DisplayName = "Max Range")` — The initial function value between 0 and 1 will be scaled between MinRange and MaxRange before being multiplied by magnitude
- L574 _public member_ `float Default;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Field", DisplayName = "Default Value")` — The field value will be set to Default if the sample distance from the box is higher than the scale of the transform
- L578 _public member_ `FTransform Transform;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Field", DisplayName = "Box Transform")` — Translation, Rotation and Scale of the unit box
- L582 _public member_ `TEnumAsByte<EFieldFalloffType> Falloff;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Field", DisplayName = "Falloff Type")` — Type of falloff function used to model the evolution of the field from the box surface to the sample position

#### class `UNoiseField`  
`class UNoiseField : public UFieldNodeFloat`  
_L590-629_
- reflection: `UCLASS(ClassGroup = "Field", meta = (BlueprintSpawnableComponent, ToolTip = "Defines a perlin noise scalar value if the sample is within a box"), ShowCategories = ("Field"), MinimalAPI)`
- inherits: `UFieldNodeFloat`
- desc: NoiseField
- L596 _public function_ `UNoiseField() : Super() , MinRange(0.f) , MaxRange(1.f) , Transform()`
- L603 _public prototype_ `virtual ~UNoiseField() = default;`
- L605 _public prototype_ `virtual FFieldNodeBase* NewEvaluationGraph(TArray<const UFieldNodeBase*>& Nodes) const override;`
- L614 _public prototype_ `UNoiseField* SetNoiseField(UPARAM(DisplayName = "Min Range") float MinRange, UPARAM(DisplayName = "Max Range") float MaxRange, UPARAM(DisplayName = "Noise Transform") FTransf` — `UFUNCTION(BlueprintPure, Category = "Field", meta = (MinRange = "0.0", MaxRange = "1.0"), DisplayName = "Set Noise Field")` — Defines a perlin noise scalar value if the sample is within a box @param    MinRange The initial function value between 0 and 1 will be scaled between MinRange and MaxRange before being multiplied by magnitude @param    MaxRange The initial function value between 0 and 1 will be scaled between MinRange and MaxRange before being multiplied by magnitude @param    Transform Transform of the box in which the perlin noise will be defined
- L620 _public member_ `float MinRange;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Field", DisplayName = "Min Range")` — The initial function value between 0 and 1 will be scaled between MinRange and MaxRange
- L624 _public member_ `float MaxRange;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Field", DisplayName = "Max Range")` — The initial function value between 0 and 1 will be scaled between MinRange and MaxRange
- L628 _public member_ `FTransform Transform;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Field", DisplayName = "Noise Transform")` — Transform of the box in which the perlin noise will be defined

#### class `UUniformVector`  
`class UUniformVector : public UFieldNodeVector`  
_L635-666_
- reflection: `UCLASS(ClassGroup = "Field", meta = (BlueprintSpawnableComponent, ToolTip = "Set a uniform vector value independently of the sample position.The output is equal to magnitude * direction"), ShowCategories = ("Field"), MinimalAPI)`
- inherits: `UFieldNodeVector`
- desc: UniformVector
- L640 _public function_ `UUniformVector() : Super() , Magnitude(1.0) , Direction(FVector(0, 0, 0))`
- L646 _public prototype_ `virtual ~UUniformVector() = default;`
- L648 _public prototype_ `virtual FFieldNodeBase* NewEvaluationGraph(TArray<const UFieldNodeBase*>& Nodes) const override;`
- L656 _public prototype_ `UUniformVector* SetUniformVector(UPARAM(DisplayName = "Field Magnitude") float Magnitude, UPARAM(DisplayName = "Uniform Direction") FV` — `UFUNCTION(BlueprintPure, Category = "Field", meta = (Magnitude = "1.0"))` — Set a uniform vector value independently of the sample position.The output is equal to magnitude * direction @param    Magnitude Magnitude of the uniform vector field @param    Direction Normalized direction of the uniform vector field
- L661 _public member_ `float Magnitude;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Field", DisplayName = "Field Magnitude")` — Magnitude of the uniform vector field
- L665 _public member_ `FVector Direction;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Field", DisplayName = "Uniform Direction")` — Normalized direction of the uniform vector field

#### class `URadialVector`  
`class URadialVector : public UFieldNodeVector`  
_L673-704_
- reflection: `UCLASS(ClassGroup = "Field", meta = (BlueprintSpawnableComponent, ToolTip = "Set a radial vector value, the direction being the vector from the sample position to the field one. The output is equal to magnitude * direction"), ShowCategories = ("Field"), MinimalAPI)`
- inherits: `UFieldNodeVector`
- desc: RadialVector
- L678 _public function_ `URadialVector() : Super() , Magnitude(1.0) , Position(FVector(0, 0, 0))`
- L684 _public prototype_ `virtual ~URadialVector() = default;`
- L686 _public prototype_ `virtual FFieldNodeBase* NewEvaluationGraph(TArray<const UFieldNodeBase*>& Nodes) const override;`
- L694 _public prototype_ `URadialVector* SetRadialVector(UPARAM(DisplayName = "Field Magnitude") float Magnitude, UPARAM(DisplayName = "Center Position") FVe` — `UFUNCTION(BlueprintPure, Category = "Field", meta = (Magnitude = "1.0"))` — Set a radial vector value. The direction is the normalized vector from the field position to the sample one. The output is equal to this direction * magnitude. @param    Magnitude Magnitude of the radial vector field @param    Position Center position of the radial vector field
- L699 _public member_ `float Magnitude;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Field", DisplayName = "Field Magnitude")` — Magnitude of the radial vector field
- L703 _public member_ `FVector Position;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Field", DisplayName = "Center Position")` — Center position of the radial vector field

#### class `URotatedRadialVector`  
`class URotatedRadialVector : public UFieldNodeVector`  
_L710-756_
- reflection: `UCLASS(ClassGroup = "Field", meta = (BlueprintSpawnableComponent, ToolTip = "Set a radial vector value rotated around an axis. The direction is the normalized vector from the field position to the sample, rotated by Angle degrees around Axis. The output is equal to magnitude * rotated direction"), ShowCategories = ("Field"), MinimalAPI)`
- inherits: `UFieldNodeVector`
- desc: RotatedRadialVector
- L715 _public function_ `URotatedRadialVector() : Super() , Magnitude(1.0) , Position(FVector(0, 0, 0)) , Angle(0.0f) , Axis(FVector(0, 0, 1))`
- L723 _public prototype_ `virtual ~URotatedRadialVector() = default;`
- L725 _public prototype_ `virtual FFieldNodeBase* NewEvaluationGraph(TArray<const UFieldNodeBase*>& Nodes) const override;`
- L736 _public prototype_ `UPARAM(DisplayName = "Field Magnitude") float Magnitude, UPARAM(DisplayName = "Center Position") FVector Position, UPARAM(DisplayName = "Rotation Angle") float Angle, UPARAM(DisplayName = "Rotation Axis") F`
- L743 _public member_ `float Magnitude;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Field", DisplayName = "Field Magnitude")` — Magnitude of the radial vector field
- L747 _public member_ `FVector Position;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Field", DisplayName = "Center Position")` — Center position of the radial vector field
- L751 _public member_ `float Angle;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Field", DisplayName = "Rotation Angle")` — Rotation angle in degrees applied to the radial direction
- L755 _public member_ `FVector Axis;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Field", DisplayName = "Rotation Axis")` — Axis around which the radial direction is rotated

#### class `URandomVector`  
`class URandomVector : public UFieldNodeVector`  
_L762-786_
- reflection: `UCLASS(ClassGroup = "Field", meta = (BlueprintSpawnableComponent, ToolTip = "Set a random vector value independently of the sample position. The output is equal to magnitude * random direction "), ShowCategories = ("Field"), MinimalAPI)`
- inherits: `UFieldNodeVector`
- desc: URandomVector
- L767 _public function_ `URandomVector() : Super() , Magnitude(1.0)`
- L772 _public prototype_ `virtual ~URandomVector() = default;`
- L774 _public prototype_ `virtual FFieldNodeBase* NewEvaluationGraph(TArray<const UFieldNodeBase*>& Nodes) const override;`
- L781 _public prototype_ `URandomVector* SetRandomVector(UPARAM(DisplayName = "Field Magnitude") fl` — `UFUNCTION(BlueprintPure, Category = "Field", meta = (Magnitude = "1.0"))` — Set a random vector value independently of the sample position. The output is equal to magnitude * random direction @param    Magnitude Magnitude of the random vector field
- L785 _public member_ `float Magnitude;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Field", DisplayName = "Field Magnitude")` — Magnitude of the random vector field

#### class `UOperatorField`  
`class UOperatorField : public UFieldNodeBase`  
_L793-841_
- reflection: `UCLASS(ClassGroup = "Field", meta = (BlueprintSpawnableComponent, ToolTip = "Compute an operation between 2 incoming fields"), ShowCategories = ("Field"), MinimalAPI)`
- inherits: `UFieldNodeBase`
- desc: UOperatorField
- L798 _public function_ `UOperatorField() : Super() , Magnitude(1.0) , RightField(nullptr) , LeftField(nullptr) , Operation(EFieldOperationType::Field_Multiply)`
- L806 _public prototype_ `virtual ~UOperatorField() = default;`
- L808 _public prototype_ `virtual FFieldNodeBase::EFieldType Type() const;`
- L809 _public function_ `virtual bool ResultsExpector() const override`
- L811 _public prototype_ `virtual FFieldNodeBase* NewEvaluationGraph(TArray<const UFieldNodeBase*>& Nodes) const override;`
- L821 _public prototype_ `UOperatorField* SetOperatorField(UPARAM(DisplayName = "Field Magnitude") float Magnitude, UPARAM(DisplayName = "Left Field") const UFieldNodeBase* LeftField, UPARAM(DisplayName = "Right Field") const UFieldNodeBase* RightField, UPARAM(DisplayName = "Field Operation") EFieldOperationT` — `UFUNCTION(BlueprintPure, Category = "Field", meta = (Magnitude = "1.0"))` — Compute an operation between 2 incoming fields @param    Magnitude Magnitude of the operator field @param    LeftField Input field A to be processed @param    RightField Input field B to be processed @param    Operation Type of math operation you want to perform between the 2 fields
- L828 _public member_ `float Magnitude;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Field", DisplayName = "Field Magnitude")` — Magnitude of the operator field
- L832 _public member_ `TObjectPtr<const UFieldNodeBase> RightField;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Field", DisplayName = "Right Field")` — Right field to be processed
- L836 _public member_ `TObjectPtr<const UFieldNodeBase> LeftField;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Field", DisplayName = "Left Field")` — Left field to be processed
- L840 _public member_ `TEnumAsByte<EFieldOperationType> Operation;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Field", DisplayName = "Field Operation")` — Type of operation you want to perform between the 2 fields

#### class `UToIntegerField`  
`class UToIntegerField : public UFieldNodeInt`  
_L847-871_
- reflection: `UCLASS(ClassGroup = "Field", meta = (BlueprintSpawnableComponent, ToolTip = "Convert a scalar field to a integer one"), ShowCategories = ("Field"), MinimalAPI)`
- inherits: `UFieldNodeInt`
- desc: UToIntegerField
- L852 _public function_ `UToIntegerField() : Super() , FloatField(nullptr)`
- L857 _public prototype_ `virtual ~UToIntegerField() = default;`
- L859 _public prototype_ `virtual FFieldNodeBase* NewEvaluationGraph(TArray<const UFieldNodeBase*>& Nodes) const override;`
- L866 _public prototype_ `UToIntegerField* SetToIntegerField(UPARAM(DisplayName = "Float Field") const UFieldNodeFloat* F` — `UFUNCTION(BlueprintPure, Category = "Field", DisplayName = "Set To Integer Field")` — Convert a float field to a integer one @param    FloatField Float field to be converted to an an integer one
- L870 _public member_ `TObjectPtr<const UFieldNodeFloat> FloatField;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Field", DisplayName = "Float Field")` — Scalar field to be converted to an an integer one

#### class `UToFloatField`  
`class UToFloatField : public UFieldNodeFloat`  
_L877-901_
- reflection: `UCLASS(ClassGroup = "Field", meta = (BlueprintSpawnableComponent, ToolTip = "Convert an integer field to a scalar one"), ShowCategories = ("Field"), MinimalAPI)`
- inherits: `UFieldNodeFloat`
- desc: UToFloatField
- L882 _public function_ `UToFloatField() : Super() , IntField(nullptr)`
- L887 _public prototype_ `virtual ~UToFloatField() = default;`
- L889 _public prototype_ `virtual FFieldNodeBase* NewEvaluationGraph(TArray<const UFieldNodeBase*>& Nodes) const override;`
- L896 _public prototype_ `UToFloatField* SetToFloatField(UPARAM(DisplayName = "Integer Field") const UFieldNodeInt* I` — `UFUNCTION(BlueprintPure, Category = "Field", DisplayName = "Set To Float Field")` — Convert an integer field to a float one @param    IntegerField Integer field to be converted to an a float one
- L900 _public member_ `TObjectPtr<const UFieldNodeInt> IntField;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Field", DisplayName = "Integer Field")` — Integer field to be converted to an a scalar one

#### class `UCullingField`  
`class UCullingField : public UFieldNodeBase`  
_L907-948_
- reflection: `UCLASS(ClassGroup = "Field", meta = (BlueprintSpawnableComponent, ToolTip = "Evaluate the input field according to the result of the culling field"), ShowCategories = ("Field"), MinimalAPI)`
- inherits: `UFieldNodeBase`
- desc: UCullingField
- L912 _public function_ `UCullingField() : Super() , Culling(nullptr) , Field(nullptr) , Operation(EFieldCullingOperationType::Field_Culling_Inside)`
- L919 _public prototype_ `virtual ~UCullingField() = default;`
- L921 _public prototype_ `virtual FFieldNodeBase* NewEvaluationGraph(TArray<const UFieldNodeBase*>& Nodes) const override;`
- L923 _public prototype_ `virtual FFieldNodeBase::EFieldType Type() const override;`
- L933 _public prototype_ `UCullingField* SetCullingField(UPARAM(DisplayName = "Culling Field") const UFieldNodeBase* Culling, UPARAM(DisplayName = "Input Field") const UFieldNodeBase* Field, UPARAM(DisplayName = "Culling Operation") EFieldCullingOperatio` — `UFUNCTION(BlueprintPure, Category = "Field")` — Evaluate the input field according to the result of the culling field. @param    Culling Culling field to be used. @param    Field Input field that will be evaluated according to the culling field result. @param    Operation Evaluate the input field if the result of the culling field is equal to 0 (Inside) or different from 0 (Outside).
- L939 _public member_ `TObjectPtr<const UFieldNodeBase> Culling;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Field", DisplayName = "Culling Field")` — Culling field to be used
- L943 _public member_ `TObjectPtr<const UFieldNodeBase> Field;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Field", DisplayName = "Input Field")` — Input field that will be evaluated according to the culling field result
- L947 _public member_ `TEnumAsByte<EFieldCullingOperationType> Operation;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Field", DisplayName = "Culling Operation")` — Evaluate the input field if the result of the culling field is equal to 0 (Inside) or different from 0 (Outside)

#### class `UReturnResultsTerminal`  
`class UReturnResultsTerminal : public UFieldNodeBase`  
_L954-971_
- reflection: `UCLASS(ClassGroup = "Field", meta = (BlueprintSpawnableComponent, ToolTip = "Terminal field of a graph"), ShowCategories = ("Field"), MinimalAPI)`
- inherits: `UFieldNodeBase`
- desc: UReturnResultsField
- L959 _public function_ `UReturnResultsTerminal() : Super()`
- L962 _public prototype_ `virtual ~UReturnResultsTerminal() = default;`
- L964 _public prototype_ `virtual FFieldNodeBase* NewEvaluationGraph(TArray<const UFieldNodeBase*>& Nodes) const override;`
- L965 _public function_ `virtual FFieldNodeBase::EFieldType Type() const override`
- L969 _public prototype_ `UReturnResultsTerminal* SetReturnResultsTerminal();` — `UFUNCTION(BlueprintPure, Category = "Field", DisplayName = "Set Terminal Field")` — Terminal field of a graph

#### struct `FFieldObjectCommands`  
`struct FFieldObjectCommands`  
_L977-1081_
- reflection: `USTRUCT(BlueprintType)`
- desc: Field Commands container that will be stored in the construction script
- L981 _public function_ `FFieldObjectCommands() : TargetNames() , RootNodes() , MetaDatas()`
- L987 _public prototype_ `~FFieldObjectCommands() = default;`
- L990 _public function_ `void AddFieldCommand(const FName& TargetName, UFieldNodeBase* RootNode, UFieldSystemMetaData* MetaData)` — Add a command to the container
- L998 _public function_ `void ResetFieldCommands()` — Reset the commands container to empty
- L1006 _public function_ `int32 GetNumCommands() const` — Get the number of commands in the container
- L1012 _public function_ `static FFieldSystemCommand CreateFieldCommand(const EFieldPhysicsType PhysicsType, UFieldNodeBase* RootNode, UFieldSystemMetaData* MetaData)` — Create a FFieldCommand from a given target + Unode + metadata
- L1049 _public function_ `static FFieldSystemCommand CreateFieldCommand(const EFieldPhysicsType PhysicsType, FFieldNodeBase* RootNode)` — Create a FFieldCommand from a given target + Fnode
- L1065 _public function_ `FFieldSystemCommand BuildFieldCommand(const int32 CommandIndex) const` — Build the FFieldCommand from one item in the container
- L1072 _public member_ `TArray<FName> TargetNames;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Field", DisplayName = "Target Names")` — Commands Target Name
- L1076 _public member_ `TArray<TObjectPtr<UFieldNodeBase>> RootNodes;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Field", DisplayName = "Root Nodes")` — Commands Root Node
- L1080 _public member_ `TArray<TObjectPtr<UFieldSystemMetaData>> MetaDatas;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Field", DisplayName = "Meta Datas")` — Commands Meta Data
