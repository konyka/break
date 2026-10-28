# Plugins / UAFControlRig

- module root: `Plugins/Experimental/UAF/UAFControlRig/Source/UAFControlRig`
- headers: 7; symbols: 221
- symbol kinds: class=2, delegate=2, enum=1, enumerator=1, function=21, member=71, namespace=20, prototype=83, struct=15, typedef=5
- PrivateDependencyModuleNames: AnimationCore, RigVMDeveloper, Slate, SlateCore, UAFUncookedOnly, WorkspaceEditor
- PublicDependencyModuleNames: ControlRig, ControlRigDeveloper, Core, CoreUObject, Engine, RigVM, UAF, UAFAnimGraph

### `Plugins/Experimental/UAF/UAFControlRig/Source/UAFControlRig/Internal/AnimNextControlRigHierarchyMappings.h` (Internal)


#### struct `UE::UAF::ControlRig::FAnimNextControlRigHierarchyMappings`  
`struct FAnimNextControlRigHierarchyMappings`  
_L28-134_
- L30 _public prototype_ `FAnimNextControlRigHierarchyMappings() = default;`
- L32 _public prototype_ `void InitializeInstance();`
- L34 _public prototype_ `void LinkToHierarchy(URigHierarchy* InHierarchy);`
- L36 _public function_ `bool CanExecute() const`
- L41 _public function_ `void ResetRefPoseSetterHash()`
- L46 _public prototype_ `void UpdateControlRigRefPoseIfNeeded(UControlRig* ControlRig , const UObject* InstanceObject , const USkeletalMeshComponent* SkeletalMeshComponent , const UE::UAF::FReferencePose& InRefPose , bool bInSetRefPoseFromSkeleton , bool bIncludePoseInHash);`
- L53 _public prototype_ `void UpdateInputOutputMappingIfRequired(UControlRig* InControlRig , URigHierarchy* InHierarchy , const UE::UAF::FReferencePose& InRefPose , int32 InCurrentLOD , const TArray<FBoneReference>& InInputBonesToTransfer , const TArray<FBoneReference>& InOutputBonesToTransfer , const TWeakObjectPtr<UNodeMappingContainer>& InNodeMappingContainer , bool bInTransferPoseInGlobalSpace , bool bResetInputPoseToInitial);`
- L63 _public prototype_ `void UpdateInput(UControlRig* ControlRig , UE::UAF::FKeyframeState& InOutput , const FControlRigIOSettings& InInputSettings , const FControlRigIOSettings& InOutputSettings , const TWeakObjectPtr<UNodeMappingContainer>& InNodeMappingContainer , bool bInExecute , bool bInTransferInputPose , bool bInResetInputPoseToInitial , bool bInTransferPoseInGlobalSpace , bool bInTransferInputCurves);`
- L74 _public prototype_ `void UpdateOutput(UControlRig* ControlRig , UE::UAF::FKeyframeState& InOutput , const FControlRigIOSettings& InOutputSettings , const TWeakObjectPtr<UNodeMappingContainer>& InNodeMappingContainer , bool bInExecute , bool bInTransferPoseInGlobalSpace);`
- L81 _public function_ `const TArray<TPair<uint16, uint16>>& GetControlRigBoneInputMappingByIndex() const`
- L86 _public function_ `TArray<TPair<uint16, uint16>>& GetControlRigBoneOutputMappingByIndex()`
- L91 _public function_ `const TMap<FName, uint16>& GetControlRigBoneInputMappingByName() const`
- L96 _public function_ `TMap<FName, uint16>& GetControlRigBoneOutputMappingByName()`
- L101 _public prototype_ `bool CheckPoseAdapter() const;`
- L103 _public prototype_ `bool IsUpdateToDate(const URigHierarchy* InHierarchy) const;`
- L105 _public prototype_ `void PerformUpdateToDate(UControlRig* ControlRig , URigHierarchy* InHierarchy , const UE::UAF::FReferencePose& InRefPose , int32 InCurrentLOD , const TWeakObjectPtr<UNodeMappingContainer>& InNodeMappingContainer , bool bInTransferPoseInGlobalSpace , bool bInResetInputPoseToInitial);`
- L115 _protected member_ `TArray<TPair<uint16, uint16>> ControlRigBoneInputMappingByIndex;` — Complete mapping from skeleton to control rig bone index
- L116 _protected member_ `TArray<TPair<uint16, uint16>> ControlRigBoneOutputMappingByIndex;`
- L119 _protected member_ `TArray<TPair<uint16, FName>> ControlRigCurveMappingByIndex;` — Complete mapping from skeleton to curve name
- L122 _protected member_ `TMap<FName, uint16> ControlRigBoneInputMappingByName;` — Rig Hierarchy bone name to required array index mapping
- L123 _protected member_ `TMap<FName, uint16> ControlRigBoneOutputMappingByName;`
- L126 _protected member_ `TMap<FName, FName> ControlRigCurveMappingByName;` — Rig Curve name to Curve mapping
- L128 _protected member_ `TArray<bool> HierarchyCurveCopied;`
- L130 _protected member_ `TSharedPtr<FAnimNextControlRigPoseAdapter> PoseAdapter;`
- L133 _protected member_ `TOptional<int32> RefPoseSetterHash;` — A hash to encode the pointer to anim instance

#### Free symbols / members of external scopes

- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace UAF` (scope `UE`)
- L23 _namespace_ `namespace UE`
- L23 _namespace_ `namespace UAF` (scope `UE`)
- L23 _namespace_ `namespace ControlRig` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAFControlRig/Source/UAFControlRig/Internal/AnimNextControlRigModule.h` (Internal)


#### class `UE::UAF::ControlRig::FAnimNextControlRigModule`  
`class FAnimNextControlRigModule : public IModuleInterface`  
_L15-44_
- inherits: `IModuleInterface`
- L18 _public prototype_ `virtual void StartupModule() override;`
- L19 _public prototype_ `virtual void ShutdownModule() override;`
- L22 _public prototype_ `void RegisterGraphFactories() const;` — Register asset class -> graph factory mappings
- L25 _public prototype_ `void RegisterSystemFactories() const;` — Register asset class -> system factory mappings
- L27 _public prototype_ `void RegisterAssetData();`
- L28 _public prototype_ `void UnregisterAssetData() const;`
- L31 _public typedef_ `using FReplacementObjectMap = FCoreUObjectDelegates::FReplacementObjectMap;`
- L32 _public prototype_ `DECLARE_TS_MULTICAST_DELEGATE_OneParam(FOnObjectsReinstanced, const FReplacementObjectMap&);`
- L33 _public member_ `static FOnObjectsReinstanced OnObjectsReinstanced;`
- L35 _public member_ `FDelegateHandle OnObjectsReinstancedHandle;`
- L37 _public member_ `TSharedPtr<FAnimNextControlRigVariableProvider> VariableProvider;`
- L41 _public member_ `FTopLevelAssetPath ControlRigBlueprintClassPath;`
- L43 _public member_ `FTopLevelAssetPath ControlRigBlueprintGeneratedClassPath;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace UAF` (scope `UE`)
- L10 _namespace_ `namespace ControlRig` (scope `UE::UAF`)
- L32 _delegate_ `DECLARE_TS_MULTICAST_DELEGATE_OneParam(FOnObjectsReinstanced, const FReplacementObjectMap&);`

### `Plugins/Experimental/UAF/UAFControlRig/Source/UAFControlRig/Internal/AnimNextControlRigPoseAdapter.h` (Internal)


#### class `UE::UAF::ControlRig::FAnimNextControlRigPoseAdapter`  
`class FAnimNextControlRigPoseAdapter : public FControlRigPoseAdapter`  
_L23-42_
- inherits: `FControlRigPoseAdapter`
- L26 _public prototype_ `FAnimNextControlRigPoseAdapter() = default;`
- L28 _public function_ `void CopyBonesFrom(const FLODPoseStack& InPose)`
- L33 _public prototype_ `void UpdateInputOutputMappingIfRequired(UControlRig* InControlRig , URigHierarchy* InHierarchy , const UE::UAF::FReferencePose& InRefPose , const int32 InCurentLOD , const TWeakObjectPtr<UNodeMappingContainer>& InNodeMappingContainer , bool bInTransferPoseInGlobalSpace , bool bInResetInputPoseToInitial);`
- L41 _public prototype_ `static const FReferenceSkeleton* GetReferenceSkeleton(const UE::UAF::FReferencePose& InRefPose);`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace UAF` (scope `UE`)
- L20 _namespace_ `namespace UE`
- L20 _namespace_ `namespace UAF` (scope `UE`)
- L20 _namespace_ `namespace ControlRig` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAFControlRig/Source/UAFControlRig/Internal/ControlRigTrait.h` (Internal)


#### struct `FControlRigExposedProperty`  
`struct FControlRigExposedProperty`  
_L30-45_
- reflection: `USTRUCT()`
- L34 _public prototype_ `FControlRigExposedProperty() = default;`
- L35 _public function_ `FControlRigExposedProperty(const FName& InExposedPropertyName, bool bInIsvariable) : ExposedPropertyName(InExposedPropertyName) , bIsVaraible(bInIsvariable)`
- L41 _public member_ `FName ExposedPropertyName = NAME_None;` — `UPROPERTY(meta = (Hidden))`
- L44 _public member_ `bool bIsVaraible = false;` — `UPROPERTY(meta = (Hidden))`

#### struct `FControlRigTraitSharedDataBase`  
`struct FControlRigTraitSharedDataBase : public FAnimNextTraitSharedData`  
_L48-155_
- reflection: `USTRUCT()`
- inherits: `FAnimNextTraitSharedData`
- L54 _public member_ `FAnimNextTraitHandle Input;` — `UPROPERTY()` — Input to be processed.
- L58 _public member_ `TObjectPtr<USkeleton> ControlRigSkeleton;` — `UPROPERTY(EditAnywhere, Category = ControlRig, meta = (Hidden))` — Skeleton to use as source to extract the Rig Controls. If null, the system will use the preview skeleton that was used to create the rig.
- L65 _public member_ `bool bResetInputPoseToInitial = true;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Category = Settings, meta = (Hidden))` — If this is checked the rig's pose needs to be reset to its initial prior to evaluating the rig.
- L72 _public member_ `bool bTransferInputPose = true;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Category = Settings, meta = (Hidden))` — If this is checked the bone pose coming from the Input will be transferred into the Control Rig.
- L79 _public member_ `bool bTransferInputCurves = true;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Category = Settings, meta = (Hidden))` — If this is checked the curves coming from the AnimBP will be transferred into the Control Rig.
- L85 _public member_ `bool bSetRefPoseFromSkeleton = false;` — `UPROPERTY(EditAnywhere, Category=Settings, meta = (DisplayName = "Set Initial Transforms From Mesh", Hidden))` — Is set, override the initial transforms with those taken from the mesh component
- L95 _public member_ `bool bTransferPoseInGlobalSpace = false;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, meta = (Hidden), Category = Settings)` — Transferring the pose in global space guarantees a global pose match, while transferring in local space ensures a match of the local transforms. In general transforms only differ if the hierarchy topology differs between the Control Rig and the skeleton used in the AnimBP. Note: Turning this off can potentially improve performance.
- L99 _public member_ `TArray<FControlRigEventName> EventQueue;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, meta = (Hidden), Category = Settings)` — The customized event queue to run
- L121 _public member_ `TMap<FName, FName> InputMapping;` — `UPROPERTY(meta = (Hidden))` — we only save mapping, we have to query control rig when runtime to ensure type and everything is still valid or not
- L124 _public member_ `TMap<FName, FName> OutputMapping;` — `UPROPERTY(meta = (Hidden))`
- L127 _public member_ `TArray<FName> ExposedPropertyVariableNames;` — `UPROPERTY(meta = (Hidden))`
- L130 _public member_ `TArray<FName> ExposedPropertyControlNames;` — `UPROPERTY(meta = (Hidden))`
- L133 _public member_ `TArray<ERigControlType> ExposedPropertyControlTypes;` — `UPROPERTY(meta = (Hidden))`
- L136 _public member_ `TArray<FString> ExposedPropertyControlDefaultValues;` — `UPROPERTY(meta = (Hidden))`
- L141 _public member_ `TArray<FName> LatentProperties;` — `UPROPERTY(Transient, meta = (Hidden))` — This is the array of latent input properties This is computed at load time based on the selected ControlRig asset
- L146 _public member_ `TArray<uint32> LatentPropertyMemoryLayouts;` — `UPROPERTY(Transient, meta = (Hidden))` — This is the array that maps a latent property to its memory layout in the trait instance data This is computed at load time based on the selected ControlRig asset
- L149 _public prototype_ `static void InitializeLatentProperties(const TArray<FControlRigVariableMappings::FCustomPropertyData>& Mappings);` — Manual handling of latent properties
- L151 _public prototype_ `static void DestructLatentPropertiesValues(const TArray<FControlRigVariableMappings::FCustomPropertyData>& Mappings);`
- L153 _public prototype_ `static void InitializeControlLatentPinDefaultValue(ERigControlType InControlType, uint8* InTargetLatentPinMemory);`

#### struct `FControlRigTraitSharedData`  
`struct FControlRigTraitSharedData : public FControlRigTraitSharedDataBase`  
_L158-178_
- reflection: `USTRUCT(meta = (Hidden, DisplayName = "Control Rig (Legacy)"))`
- inherits: `FControlRigTraitSharedDataBase`
- L163 _public member_ `TSubclassOf<UControlRig> ControlRigClass;` — `UPROPERTY(EditAnywhere, Category = ControlRig, meta = (Hidden, DisallowCreateNew))`
- L165 _public function_ `FControlRigAssetStrongReference GetControlRigAssetReference() const`
- L166 _public function_ `bool HasValidControlRigReference() const`
- L169 _public prototype_ `static void ConstructLatentProperties(const UE::UAF::FTraitBinding& Binding);` — Manual handling of latent properties
- L171 _public prototype_ `static void DestructLatentProperties(const UE::UAF::FTraitBinding& Binding);`
- L175 _public prototype_ `USkeleton* GetPreviewSkeleton() const;`
- L176 _public prototype_ `TScriptInterface<const IControlRigEditorAssetInterface> GetControlRigEditorAsset() const;`

#### struct `FControlRigTraitSharedData_v2`  
`struct FControlRigTraitSharedData_v2 : public FControlRigTraitSharedDataBase`  
_L181-201_
- reflection: `USTRUCT(meta = (DisplayName = "Control Rig"))`
- inherits: `FControlRigTraitSharedDataBase`
- L186 _public member_ `FControlRigAssetStrongReference ControlRigAssetReference;` — `UPROPERTY(EditAnywhere, Category = ControlRig, meta = (Hidden, DisallowCreateNew))`
- L188 _public function_ `FControlRigAssetStrongReference GetControlRigAssetReference() const`
- L189 _public function_ `bool HasValidControlRigReference() const`
- L192 _public prototype_ `static void ConstructLatentProperties(const UE::UAF::FTraitBinding& Binding);` — Manual handling of latent properties
- L194 _public prototype_ `static void DestructLatentProperties(const UE::UAF::FTraitBinding& Binding);`
- L198 _public prototype_ `USkeleton* GetPreviewSkeleton() const;`
- L199 _public prototype_ `TScriptInterface<const IControlRigEditorAssetInterface> GetControlRigEditorAsset() const;`

#### struct `UE::UAF::TControlRigTraitBase`  
`template<typename TSharedData> struct TControlRigTraitBase : FBaseTrait, IEvaluate, IUpdate, IHierarchy, IGarbageCollection`  
_L207-301_
- inherits: `FBaseTrait,IEvaluate,IUpdate,IHierarchy,IGarbageCollection`
- L209 _public typedef_ `typedef FBaseTrait Super;`
- L211 _public typedef_ `using FSharedData = TSharedData;`
- L254 _public prototype_ `virtual void SerializeTraitSharedData(FArchive& Ar, FAnimNextTraitSharedData& SharedData) const override;` — FTrait impl
- L255 _public prototype_ `virtual uint32 GetNumLatentTraitProperties() const override;`
- L256 _public prototype_ `virtual UE::UAF::FTraitLatentPropertyMemoryLayout GetLatentPropertyMemoryLayout(const FAnimNextTraitSharedData& SharedData, FName PropertyName, uint32 PropertyIndex) const override;`
- L259 _public prototype_ `virtual void OnBecomeRelevant(FUpdateTraversalContext& Context, const TTraitBinding<IUpdate>& Binding, const FTraitUpdateState& TraitState) const override;` — IUpdate impl
- L260 _public prototype_ `virtual void PreUpdate(FUpdateTraversalContext& Context, const TTraitBinding<IUpdate>& Binding, const FTraitUpdateState& TraitState) const override;`
- L263 _public prototype_ `virtual void PostEvaluate(FEvaluateTraversalContext& Context, const TTraitBinding<IEvaluate>& Binding) const override;` — IEvaluate impl
- L266 _public prototype_ `virtual uint32 GetNumChildren(const FExecutionContext& Context, const TTraitBinding<IHierarchy>& Binding) const override;` — IHierarchy impl
- L267 _public prototype_ `virtual void GetChildren(const FExecutionContext& Context, const TTraitBinding<IHierarchy>& Binding, FChildrenArray& Children) const override;`
- L270 _public prototype_ `virtual void AddReferencedObjects(const FExecutionContext& Context, const TTraitBinding<IGarbageCollection>& Binding, FReferenceCollector& Collector) const override;` — IGarbageCollection impl
- L273 _protected prototype_ `static UControlRig* GetControlRig(FInstanceData* InstanceData);`
- L275 _protected prototype_ `static bool CreateControlRig(UObject* InAnimContext, UObject* InBindableObject, FControlRigAssetStrongReference InControlRigAssetReference, FInstanceData* InstanceData);`
- L276 _protected prototype_ `static bool SetBindableObject(UControlRig* ControlRig, UObject* InAnimContext, UObject* InBindableObject);`
- L278 _protected prototype_ `static FControlRigAssetStrongReference GetTargetAssetReference(const FSharedData* SharedData, const TTraitBinding<IUpdate>& Binding);`
- L281 _protected prototype_ `virtual void GetProgrammaticPins(FAnimNextTraitSharedData* InSharedData, URigVMController* InController, int32 InParentPinIndex, const URigVMPin* TraitPin, const FString& InDefaultValue, struct FRigVMPinInfoArray& OutPinArray) const override;`
- L288 _protected prototype_ `virtual int32 GetLatentPropertyIndex(const FAnimNextTraitSharedData& InSharedData, FName PropertyName) const override;`
- L290 _protected prototype_ `virtual uint32 GetLatentPropertyHandles( const FAnimNextTraitSharedData* InSharedData, TArray<FLatentPropertyMetadata>& OutLatentPropertyHandles, bool bFilterEditorOnly, const TFunction<uint16(FName PropertyName)>& GetTraitLatentPropertyIndex) const override;`
- L296 _protected member_ `FControlRigIOMapping::FRigControlsData RigControlsData;`
- L299 _protected prototype_ `static bool GetVariableSizeAndAlignment(const FRigVMExternalVariable& Variable, uint32& PropertySize, uint32& PropertyAlignment);`
- L300 _protected prototype_ `static bool GetControlSizeAndAlignment(ERigControlType ControlType, uint32& PropertySize, uint32& PropertyAlignment);`

#### struct `UE::UAF::TControlRigTraitBase::FInstanceData`  
`struct FInstanceData : FTrait::FInstanceData`  
_L213-251_
- inherits: `FTrait::FInstanceData`
- L215 _public member_ `FTraitPtr Input;`
- L217 _public member_ `TSharedPtr<FAnimNextControlRigTask> EvaluationTask;`
- L219 _public member_ `TObjectPtr<UControlRig> ControlRig;`
- L221 _public member_ `FDelegateHandle OnObjectsReinstancedHandle;`
- L222 _public member_ `FDelegateHandle OnInitializedHandle;`
- L224 _public member_ `FControlRigVariableMappings::FCustomPropertyMappings PropertyMappings;`
- L226 _public prototype_ `void Construct(const FExecutionContext& Context, const FTraitBinding& Binding);`
- L227 _public prototype_ `void Destruct(const FExecutionContext& Context, const FTraitBinding& Binding);`
- L229 _public prototype_ `void InitializeControlRig(const FExecutionContext& Context, const FTraitBinding& Binding);`
- L230 _public prototype_ `void DestroyControlRig(const FExecutionContext& Context, const FTraitBinding& Binding);`
- L232 _public prototype_ `static UObject* GetAnimContext(const FExecutionContext& Context);`
- L233 _public prototype_ `static const USkeletalMeshComponent* GetBindableObject(const FExecutionContext& Context);`
- L234 _public prototype_ `static FControlRigAssetStrongReference GetTargetAssetReference(const TSharedData* SharedData);`
- L237 _public prototype_ `static int32 GetExposedVariablesData(const UE::UAF::FTraitBinding& Binding, const TSharedData* SharedData, FControlRigVariableMappings::FCustomPropertyMappings& OutMappings);` — Returns the property, variable name and the memory of the variable (as target) and the memory of the latent property (as source)
- L238 _public prototype_ `static int32 GetExposedControlsData(const UE::UAF::FTraitBinding& Binding, const TSharedData* SharedData, FControlRigVariableMappings::FCustomPropertyMappings& OutMappings);`
- L239 _public prototype_ `static void MapUAFVariablesToControlRig(const UE::UAF::FTraitBinding& Binding, const TSharedData* SharedData, FControlRigVariableMappings::FCustomPropertyMappings& OutMappings);`
- L241 _public prototype_ `void HandleOnInitialized_AnyThread(URigVMHost*, const FName&);`
- L243 _public prototype_ `void InitializeCustomProperties(const FTraitBinding& Binding, const TSharedData* SharedData);`
- L246 _public prototype_ `void OnObjectsReinstanced(const TMap<UObject*, UObject*>& OldToNewInstanceMap);`
- L247 _public member_ `bool bRefreshBindableObject = false;`
- L248 _public member_ `bool bReinitializeControlRig = false;`
- L249 _public member_ `bool bRegenerateVariableMappings = false;`

#### struct `UE::UAF::FControlRigTrait`  
`struct FControlRigTrait : TControlRigTraitBase<FControlRigTraitSharedData>`  
_L303-311_
- inherits: `TControlRigTraitBase<FControlRigTraitSharedData>`
- L305 _public typedef_ `using Super = TControlRigTraitBase<FControlRigTraitSharedData>;`

#### struct `UE::UAF::FControlRigTrait_v2`  
`struct FControlRigTrait_v2 : TControlRigTraitBase<FControlRigTraitSharedData_v2>`  
_L313-321_
- inherits: `TControlRigTraitBase<FControlRigTraitSharedData_v2>`
- L315 _public typedef_ `using Super = TControlRigTraitBase<FControlRigTraitSharedData_v2>;`

#### Free symbols / members of external scopes

- L203 _namespace_ `namespace UE`
- L203 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAFControlRig/Source/UAFControlRig/Private/AnimNextControlRigVariableProvider.h` (Private)


#### struct `UE::UAF::ControlRig::FAnimNextControlRigVariableProvider`  
`struct FAnimNextControlRigVariableProvider`  
_L17-30_
- L20 _public prototype_ `FAnimNextControlRigVariableProvider();`
- L21 _public prototype_ `~FAnimNextControlRigVariableProvider();`
- L23 _public prototype_ `static FAnimNextVariableReference GetVariableReferenceFromControlRig(const FRigVMExternalVariable& RigVMVariable, const IRigVMRuntimeAssetInterface* Asset);`
- L26 _protected prototype_ `static void GetAssetRegistryTags(FAssetRegistryTagsContext Context);`
- L29 _private member_ `FDelegateHandle OnGetExtraObjectTagsHandle;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace UAF` (scope `UE`)
- L12 _namespace_ `namespace ControlRig` (scope `UE::UAF`)
- L14 _prototype_ `FAnimNextVariableReference GetAnimNextVariableReferenceFromRigVMExternalVariable(const FRigVMExternalVariable& RigVMVariable, const IRigVMRuntimeAssetInterface* Asset);` (scope `UE::UAF::ControlRig`)

### `Plugins/Experimental/UAF/UAFControlRig/Source/UAFControlRig/Public/ControlRigTask.h` (Public)


#### struct `FControlRigEventName`  
`struct FControlRigEventName`  
_L30-41_
- reflection: `USTRUCT()`
- L34 _public function_ `FControlRigEventName() : EventName(NAME_None)`
- L40 _public member_ `FName EventName;` — `UPROPERTY(EditAnywhere, Category = Links)`

#### struct `FAnimNextControlRigTaskParams`  
`struct FAnimNextControlRigTaskParams`  
_L44-70_
- reflection: `USTRUCT()`
- L48 _public member_ `bool bResetInputPoseToInitial = true;`
- L49 _public member_ `bool bTransferInputPose = true;`
- L50 _public member_ `bool bTransferInputCurves = true;`
- L51 _public member_ `bool bSetRefPoseFromSkeleton = false;`
- L52 _public member_ `bool bTransferPoseInGlobalSpace = false;`
- L53 _public member_ `TArray<FControlRigEventName> EventQueue;`
- L54 _public member_ `TMap<FName, FName> InputMapping;`
- L55 _public member_ `TMap<FName, FName> OutputMapping;`
- L57 _public member_ `FRigVMDrawInterface* DebugDrawInterface = nullptr;`
- L59 _public member_ `FControlRigVariableMappings ControlRigVariableMappings;`
- L60 _public member_ `mutable UE::UAF::ControlRig::FAnimNextControlRigHierarchyMappings ControlRigHierarchyMappings;`
- L62 _public member_ `TObjectPtr<UControlRig> ControlRig;`
- L64 _public member_ `uint16 LastBonesSerialNumberForCacheBones = 0;`
- L65 _public member_ `mutable bool bControlRigRequiresInitialization = false;`
- L66 _public member_ `mutable bool bUpdateInputOutputMapping = false;`
- L67 _public member_ `FTransform ComponentTransform;`
- L69 _public member_ `bool bConsumesPreviousPose = true;`

#### struct `FAnimNextControlRigTask`  
`struct FAnimNextControlRigTask : public FAnimNextEvaluationTask`  
_L73-132_
- reflection: `USTRUCT()`
- inherits: `FAnimNextEvaluationTask`
- L79 _public prototype_ `FAnimNextControlRigTask() = default;`
- L80 _public function_ `explicit FAnimNextControlRigTask(FAnimNextControlRigTaskParams&& InParams) : Params(MoveTemp(InParams))`
- L86 _public prototype_ `virtual void Execute(UE::UAF::FEvaluationVM& VM) const override;` — Task entry point
- L89 _public function_ `const FAnimNextControlRigTaskParams& GetParams() const`
- L92 _public prototype_ `void Initialize(bool bInitControlRig, const FControlRigVariableMappings::FCustomPropertyMappings* PropertyMappings = nullptr);` — Initializes the control rig
- L95 _public prototype_ `void RequestInit();` — Marks the control rig as needing initialization on the next execute
- L98 _public prototype_ `void OnControlRigInitialized();` — Called when the control rig has been initialized
- L101 _public prototype_ `void SetComponentTransform(const FTransform& InComponentTransform);`
- L104 _public function_ `FControlRigVariableMappings& GetControlRigVariableMappings()`
- L105 _public function_ `const FControlRigVariableMappings& GetControlRigVariableMappings() const`
- L107 _public function_ `UE::UAF::ControlRig::FAnimNextControlRigHierarchyMappings& GetControlRigHierarchyMappings()`
- L108 _public function_ `const UE::UAF::ControlRig::FAnimNextControlRigHierarchyMappings& GetControlRigHierarchyMappings() const`
- L110 _public function_ `UControlRig* GetControlRig() const`
- L113 _private member_ `FAnimNextControlRigTaskParams Params;`
- L115 _private member_ `FControlRigIOSettings InputSettings;`
- L116 _private member_ `FControlRigIOSettings OutputSettings;`
- L118 _private member_ `mutable int32 LastLOD = INDEX_NONE;`
- L120 _private member_ `bool bExecute = true;`
- L121 _private member_ `mutable bool bClearEventQueueRequired = false;`
- L122 _private prototype_ `void ExecuteControlRig(UE::UAF::FEvaluationVM& VM, UE::UAF::FKeyframeState& KeyFrameState) const;`
- L123 _private prototype_ `void UpdateInput(UE::UAF::FEvaluationVM& VM, UE::UAF::FKeyframeState& KeyFrameState, UE::UAF::FKeyframeState& InOutput) const;`
- L124 _private prototype_ `void UpdateOutput(UE::UAF::FEvaluationVM& VM, UE::UAF::FKeyframeState& KeyFrameState, UE::UAF::FKeyframeState& InOutput) const;`
- L126 _private prototype_ `bool CanExecute() const;`
- L128 _private prototype_ `void QueueControlRigDrawInstructions(FRigVMDrawInterface* DebugDrawInterface, const FTransform& ComponentTransform) const;`

#### Free symbols / members of external scopes

- L22 _namespace_ `namespace UE`
- L22 _namespace_ `namespace UAF` (scope `UE`)
- L27 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("UAF Task: ControlRig"), STAT_AnimNext_Task_ControlRig, STATGROUP_AnimNext,`

### `Plugins/Experimental/UAF/UAFControlRig/Source/UAFControlRig/Public/UAFControlRigAssetData.h` (Public)


#### struct `FUAFGraphFactoryAsset_ControlRig`  
`struct FUAFGraphFactoryAsset_ControlRig : public FUAFGraphFactoryAsset`  
_L15-38_
- reflection: `USTRUCT(DisplayName="Control Rig Asset")`
- inherits: `FUAFGraphFactoryAsset`
- L18 _public function_ `FUAFGraphFactoryAsset_ControlRig(const FControlRigAssetStrongReference& InControlRigReference) : ControlRigAssetReference(InControlRigReference)`
- L19 _public prototype_ `FUAFGraphFactoryAsset_ControlRig() = default;`
- L21 _public prototype_ `virtual bool Validate() const override;`
- L23 _public prototype_ `virtual void GetObjectReferences(TArray<const UObject*>& OutReferencedObjects) const override;`
- L28 _public member_ `TSubclassOf<UControlRig> ControlRigClass_DEPRECATED;` — `UPROPERTY(meta=(DeprecatedProperty))` — The type of this animation ControlRig
- L33 _public member_ `FControlRigAssetStrongReference ControlRigAssetReference;` — `UPROPERTY(EditAnywhere, Category = ControlRig)` — The type of this animation ControlRig
- L36 _public prototype_ `void PostSerialize(const FArchive& Ar);`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FUAFGraphFactoryAsset_ControlRig> : public TStructOpsTypeTraitsBase2<FUAFGraphFactoryAsset_ControlRig>`  
_L43-49_
- inherits: `TStructOpsTypeTraitsBase2<FUAFGraphFactoryAsset_ControlRig>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L46-48_

#### Free symbols / members of external scopes

- L47 _enumerator_ `WithPostSerialize = true` (scope `TStructOpsTypeTraits::__anonee478e680103`)
