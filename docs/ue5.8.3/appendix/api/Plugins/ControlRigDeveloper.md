# Plugins / ControlRigDeveloper

- module root: `Plugins/Animation/ControlRig/Source/ControlRigDeveloper`
- headers: 12; symbols: 511
- symbol kinds: class=14, delegate=6, function=145, macro=8, member=72, prototype=259, struct=5, typedef=2
- DynamicallyLoadedModuleNames: ControlRigEditor
- PrivateDependencyModuleNames: AnimGraph, AnimGraphRuntime, ApplicationCore, BlueprintGraph, ControlRig, Core, CoreUObject, EditorFramework, EditorWidgets, Engine, GraphEditor, InputCore, Kismet, KismetCompiler, MessageLog, MovieScene, MovieSceneTracks, PropertyEditor, PropertyPath, RigVM, RigVMDeveloper, RigVMEditor, Slate, SlateCore, TimeManagement, ToolWidgets, UnrealEd
- PrivateIncludePathModuleNames: ControlRigEditor
- PublicDependencyModuleNames: AnimationCore, AnimationEditorWidgets, VisualGraphUtils

### `Plugins/Animation/ControlRig/Source/ControlRigDeveloper/Private/ControlRigEditorAssetUndoClient.h` (Private)


#### class `FControlRigEditorAssetUndoClient`  
`class FControlRigEditorAssetUndoClient final : public FSelfRegisteringEditorUndoClient , FNoncopyable`  
_L16-37_
- inherits: `FSelfRegisteringEditorUndoClient,FNoncopyable`
- desc: Undo redo handler for the control rig editor asset interface
- L27 _public prototype_ `FControlRigEditorAssetUndoClient(FPrivateToken, const FControlRigAssetInterfacePtr& InOwner);`
- L31 _private prototype_ `virtual void PostUndo(bool bSuccess) override;`
- L32 _private prototype_ `virtual void PostRedo(bool bSuccess) override;`
- L36 _private member_ `TWeakInterfacePtr<IControlRigEditorAssetInterface> WeakOwner;` — The control rig editor asset interface that owns this handler

#### struct `FControlRigEditorAssetUndoClient::FPrivateToken`  
`struct FPrivateToken`  
_L24-24_
- desc: Private token required to construct this class
- L24 _public prototype_ `struct FPrivateToken` — Private token required to construct this class

#### Free symbols / members of external scopes

- L13 _typedef_ `using FControlRigAssetInterfacePtr = TScriptInterface<IControlRigEditorAssetInterface>;`

### `Plugins/Animation/ControlRig/Source/ControlRigDeveloper/Public/AnimGraphNode_ControlRig.h` (Public)


#### class `UAnimGraphNode_ControlRig`  
`class UAnimGraphNode_ControlRig : public UAnimGraphNode_CustomProperty`  
_L14-52_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAnimGraphNode_CustomProperty`
- L19 _private member_ `FAnimNode_ControlRig Node;` — `UPROPERTY(EditAnywhere, Category = Settings)`
- L22 _private prototype_ `virtual void Serialize(FArchive& Ar) override;` — UObject interface
- L25 _private prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`
- L26 _private prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L27 _private prototype_ `virtual void PostReconstructNode() override;`
- L28 _private prototype_ `virtual void PreloadRequiredAssets() override;`
- L29 _private prototype_ `virtual UObject* GetJumpTargetForDoubleClick() const override;`
- L30 _private prototype_ `virtual UStruct* GetTargetSkeletonStruct() const override;`
- L31 _private prototype_ `virtual UStruct* GetTargetStruct() const override;`
- L32 _private prototype_ `virtual FControlRigAssetStrongReference GetTargetAssetReference() const;`
- L36 _private prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;` — UEdGraphNode interface
- L37 _private prototype_ `virtual void CustomizePinData(UEdGraphPin* Pin, FName SourcePropertyName, int32 ArrayIndex) const override;`
- L38 _private prototype_ `virtual FText GetTooltipText() const override;`
- L40 _private function_ `virtual FAnimNode_CustomProperty* GetCustomPropertyNode() override`
- L41 _private function_ `virtual const FAnimNode_CustomProperty* GetCustomPropertyNode() const override`
- L43 _private prototype_ `virtual void CreateCustomPins(TArray<UEdGraphPin*>* OldPins) override;`
- L44 _private prototype_ `virtual void ValidateAnimNodeDuringCompilation(USkeleton* ForSkeleton, FCompilerResultsLog& MessageLog) override;`
- L46 _private prototype_ `void OnPropertyExposeCheckboxChanged(ECheckBoxState NewState, FName PropertyName);`
- L47 _private prototype_ `void OnVariableMappingChanged(const FName& PathName, const FName& Curve, bool bInput);`
- L49 _private prototype_ `USkeleton* GetTargetSkeleton() const;`
- L51 _private member_ `TSharedPtr <FControlRigIOMapping> ControlRigIOMapping;`

### `Plugins/Animation/ControlRig/Source/ControlRigDeveloper/Public/ControlRigBlueprintCompiler.h` (Public)


#### class `FControlRigBlueprintCompiler`  
`class FControlRigBlueprintCompiler : public FRigVMBlueprintCompiler`  
_L9-15_
- inherits: `FRigVMBlueprintCompiler`
- L13 _public prototype_ `virtual bool CanCompile(const UBlueprint* Blueprint) override;` — IBlueprintCompiler interface
- L14 _public prototype_ `virtual void Compile(UBlueprint* Blueprint, const FKismetCompilerOptions& CompileOptions, FCompilerResultsLog& Results) override;`

#### class `FControlRigBlueprintCompilerContext`  
`class FControlRigBlueprintCompilerContext : public FRigVMBlueprintCompilerContext`  
_L17-28_
- inherits: `FRigVMBlueprintCompilerContext`
- L20 _public function_ `FControlRigBlueprintCompilerContext(UBlueprint* SourceSketch, FCompilerResultsLog& InMessageLog, const FKismetCompilerOptions& InCompilerOptions) : FRigVMBlueprintCompilerContext(SourceSketch, InMessageLog, InCompilerOptions)`
- L26 _public prototype_ `virtual void SpawnNewClass(const FString& NewClassName) override;` — FKismetCompilerContext interface
- L27 _public prototype_ `virtual void CopyTermDefaultsToDefaultObject(UObject* DefaultObject) override;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API CONTROLRIGDEVELOPER_API`

### `Plugins/Animation/ControlRig/Source/ControlRigDeveloper/Public/ControlRigBlueprintLegacy.h` (Public)


#### class `UControlRigBlueprint`  
`class UControlRigBlueprint : public URigVMBlueprint, public IControlRigEditorAssetInterface, public IInterface_PreviewMeshProvider, public IRigHierarchyProvider`  
_L34-333_
- reflection: `UCLASS(MinimalAPI, BlueprintType, meta=(IgnoreClassThumbnail))`
- inherits: `URigVMBlueprint,IControlRigEditorAssetInterface,IInterface_PreviewMeshProvider,IRigHierarchyProvider`
- L39 _public prototype_ `UControlRigBlueprint();`
- L42 _public function_ `virtual FRigVMEditorAssetInterfacePtr GetRigVMAssetInterface() override` — --- IControlRigEditorAssetInterface interface ---
- L43 _public function_ `virtual FModularRigModel& GetModularRigModel() override`
- L44 _public function_ `virtual URigHierarchy* GetHierarchy() const override`
- L45 _public function_ `virtual TSoftObjectPtr<USkeletalMesh> GetPreviewSkeletalMesh() const override`
- L46 _public function_ `virtual bool& GetAllowMultipleInstances() override`
- L47 _public function_ `virtual TMap<FRigElementKey, FRigElementKeyCollection>& GetArrayConnectionMap() override`
- L48 _public function_ `virtual void SetControlRigType(EControlRigType InType) override`
- L49 _public function_ `virtual EControlRigType GetControlRigType() const override`
- L50 _public function_ `virtual void SetCustomThumbnail(FString InThumbnail) override`
- L51 _public function_ `virtual FString GetCustomThumbnail() const override`
- L52 _public function_ `virtual float& GetDebugBoneRadius() override`
- L53 _public function_ `virtual bool& GetExposesAnimatableControls() override`
- L54 _public function_ `virtual FRigHierarchySettings& GetHierarchySettings() override`
- L55 _public function_ `virtual FRigInfluenceMapPerEvent& GetInfluences() override`
- L56 _public function_ `virtual void SetItemTypeDisplayName(FName InName) override`
- L57 _public function_ `virtual FName GetItemTypeDisplayName() const override`
- L58 _public function_ `virtual FModularRigSettings& GetModularRigSettings() override`
- L59 _public function_ `virtual FRigModuleSettings& GetRigModuleSettings() override`
- L60 _public function_ `virtual TArray<FModuleReferenceData>& GetModuleReferenceData() override`
- L61 _public function_ `virtual TArray<TSoftObjectPtr<UControlRigShapeLibrary>>& GetShapeLibraries() override`
- L62 _public function_ `virtual TSoftObjectPtr<UObject>& GetSourceCurveImport() override`
- L63 _public function_ `virtual TSoftObjectPtr<UObject>& GetSourceHierarchyImport() override`
- L64 _public function_ `virtual bool& GetSupportsControls() override`
- L65 _public function_ `virtual bool& GetSupportsInversion() override`
- L66 _public function_ `virtual TObjectPtr<UControlRigValidator>& GetValidator() override`
- L67 _public function_ `virtual UObject* GetDefaultHierarchyOuter() override`
- L70 _public function_ `virtual UClass* GetRigVMSchemaClass() const override` — --- IRigVMClientHost interface ---
- L71 _public function_ `virtual UScriptStruct* GetRigVMExecuteContextStruct() const override`
- L72 _public function_ `virtual UClass* GetRigVMEdGraphClass() const override`
- L73 _public function_ `virtual UClass* GetRigVMEdGraphNodeClass() const override`
- L74 _public function_ `virtual UClass* GetRigVMEdGraphSchemaClass() const override`
- L75 _public function_ `virtual UClass* GetRigVMEditorSettingsClass() const override`
- L79 _public function_ `virtual UClass* GetRigVMBlueprintGeneratedClassPrototype() const` — `UE_DEPRECATED(5.7, "Please use GetRigVMGeneratedClassPrototype")` — URigVMBlueprint interface
- L80 _public function_ `virtual UClass* GetRigVMGeneratedClassPrototype() const override`
- L84 _public function_ `virtual TArray<FString> GeneratePythonCommands(const FString InNewBlueprintName) override` — `UE_DEPRECATED(5.8, "Use TArray<FString> GeneratePythonCommands() instead.")`
- L85 _public function_ `virtual TArray<FString> GeneratePythonCommands() override`
- L86 _public prototype_ `virtual TArray<FString> GeneratePythonContextCommands(const FString InNewBlueprintName, bool bCreateAsset) override;`
- L89 _public prototype_ `virtual void GetPreloadDependencies(TArray<UObject*>& OutDeps) override;`
- L91 _public function_ `virtual const FLazyName& GetPanelPinFactoryName() const override`
- L92 _public function_ `virtual IRigVMEditorModule* GetEditorModule() const override`
- L95 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L96 _public function_ `virtual void SerializeSuper(FArchive& Ar) override`
- L101 _public function_ `virtual UClass* GetBlueprintClass() const override` — UBlueprint interface
- L102 _public prototype_ `virtual UClass* RegenerateClass(UClass* ClassToRegenerate, UObject* PreviousCDO) override;`
- L103 _public function_ `virtual bool RequiresForceLoadMembersSuper(UObject* InObject) const override`
- L104 _public function_ `virtual bool SupportedByDefaultBlueprintFactory() const override`
- L105 _public function_ `virtual bool IsValidForBytecodeOnlyRecompile() const override`
- L106 _public function_ `virtual void GetTypeActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override`
- L107 _public function_ `virtual void GetInstanceActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override`
- L108 _public prototype_ `virtual void PreSave(FObjectPreSaveContext ObjectSaveContext) override;`
- L109 _public prototype_ `virtual void PostLoad() override;`
- L110 _public prototype_ `virtual void PostTransacted(const FTransactionObjectEvent& TransactionEvent) override;`
- L111 _public prototype_ `virtual void PostDuplicate(bool bDuplicateForPIE) override;`
- L112 _public prototype_ `virtual void PostRename(UObject* OldOuter, const FName OldName) override;`
- L113 _public function_ `virtual bool RequiresForceLoadMembers(UObject* InObject) const override`
- L115 _public function_ `virtual bool SupportsGlobalVariables() const override`
- L116 _public function_ `virtual bool SupportsLocalVariables() const override`
- L117 _public function_ `virtual bool SupportsFunctions() const override`
- L118 _public function_ `virtual bool SupportsEventGraphs() const override`
- L122 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;` — UObject interface
- L123 _public prototype_ `virtual void PostEditChangeChainProperty(struct FPropertyChangedChainEvent& PropertyChangedEvent) override;`
- L125 _public prototype_ `static bool CopyBlueprintToAsset(UControlRigBlueprint* InBlueprint, UControlRigRuntimeAsset* InAsset);`
- L131 _public prototype_ `virtual UClass* GetControlRigClass() const override;` — `UE_DEPRECATED(5.8, "Use GetControlRigAssetReference instead")` — `UFUNCTION(BlueprintCallable, Category = "VM", meta = (DeprecatedFunction, DeprecationMessage = "Use GetControlRigAssetReference instead"))`
- L133 _public prototype_ `virtual FControlRigAssetStrongReference GetControlRigAssetReference() const override;` — `UFUNCTION(BlueprintCallable, Category = "VM")`
- L136 _public function_ `UControlRig* CreateControlRig()` — `UFUNCTION(BlueprintCallable, Category = "Control Rig Blueprint")`
- L139 _public function_ `UControlRig* GetDebuggedControlRig()` — `UFUNCTION(BlueprintCallable, Category = "Control Rig Blueprint")`
- L143 _public function_ `virtual void SetPreviewMesh(USkeletalMesh* PreviewMesh, bool bMarkAsDirty = true) override` — `UFUNCTION(BlueprintCallable, Category = "Control Rig Blueprint")` — IInterface_PreviewMeshProvider interface
- L144 _public prototype_ `virtual void SetPreviewMeshImpl(USkeletalMesh* PreviewMesh) override;`
- L147 _public function_ `virtual USkeletalMesh* GetPreviewMesh() const override` — `UFUNCTION(BlueprintCallable, Category = "Control Rig Blueprint")`
- L150 _public function_ `virtual bool IsControlRigModule() const` — `UFUNCTION(BlueprintPure, Category = "Control Rig Blueprint")`
- L155 _public function_ `bool TurnIntoControlRigModule_Blueprint()` — `UFUNCTION(BlueprintCallable, meta = (DisplayName = "TurnIntoControlRigModule", ScriptName = "TurnIntoControlRigModule"), Category = "Control Rig Blueprint")`
- L158 _public function_ `bool CanTurnIntoStandaloneRig_Blueprint() const` — `UFUNCTION(BlueprintPure, meta = (DisplayName = "CanTurnIntoStandaloneRig", ScriptName = "CanTurnIntoStandaloneRig"), Category = "Control Rig Blueprint")`
- L161 _public function_ `bool TurnIntoStandaloneRig_Blueprint()` — `UFUNCTION(BlueprintCallable, meta = (DisplayName = "TurnIntoStandaloneRig", ScriptName = "TurnIntoStandaloneRig"), Category = "Control Rig Blueprint")`
- L164 _public function_ `TArray<URigVMNode*> ConvertHierarchyElementsToSpawnerNodes(URigHierarchy* InHierarchy, TArray<FRigElementKey> InKeys, bool bRemoveElements = true)` — `UFUNCTION(BlueprintCallable, Category = "Control Rig Blueprint")`
- L168 _public function_ `virtual UObject* GetOuterForModularModel() override`
- L171 _public function_ `UTexture2D* GetRigModuleIcon() const` — `UFUNCTION(BlueprintPure, Category = "Control Rig Blueprint")`
- L174 _public member_ `FModularRigSettings ModularRigSettings;` — `UPROPERTY(EditAnywhere, Category = "Modular Rig")`
- L177 _public member_ `FRigHierarchySettings HierarchySettings;` — `UPROPERTY(EditAnywhere, Category = "Hierarchy")`
- L180 _public member_ `FRigModuleSettings RigModuleSettings;` — `UPROPERTY(EditAnywhere, Category = "Hierarchy", AssetRegistrySearchable)`
- L186 _public member_ `FString CustomThumbnail;` — `UPROPERTY(EditAnywhere, Category = "Hierarchy", AssetRegistrySearchable)` — This relates to FAssetThumbnailPool::CustomThumbnailTagName and allows the thumbnail pool to show the thumbnail of the icon rather than the rig itself to avoid deploying the 3D renderer.
- L190 _public member_ `TArray<FModuleReferenceData> ModuleReferenceData;` — `UPROPERTY(AssetRegistrySearchable)` — Asset searchable information module references in this rig
- L193 _public member_ `TMap<FRigElementKey, FRigElementKey> ConnectionMap_DEPRECATED;` — `UPROPERTY()`
- L196 _public member_ `TMap<FRigElementKey, FRigElementKeyCollection> ArrayConnectionMap;` — `UPROPERTY()`
- L199 _public function_ `TArray<FModuleReferenceData> FindReferencesToModule() const` — `UFUNCTION(BlueprintPure, Category = "Control Rig Blueprint")`
- L202 _public function_ `virtual void UpdateExposedModuleConnectors() const` — `UFUNCTION(BlueprintCallable, Category = "Control Rig Blueprint")`
- L209 _protected member_ `TArray<FRigVMOldPublicFunctionData> PublicFunctions_DEPRECATED;` — `UPROPERTY(AssetRegistrySearchable)` — Asset searchable information about exposed public functions on this rig
- L211 _protected function_ `virtual void SetupDefaultObjectDuringCompilation(URigVMHost* InCDO) override`
- L215 _public function_ `virtual void SetupPinRedirectorsForBackwardsCompatibility() override`
- L218 _public prototype_ `static TArray<UControlRigBlueprint*> GetCurrentlyOpenRigBlueprints();` — `UFUNCTION(BlueprintCallable, Category = "VM")`
- L222 _public member_ `TSoftObjectPtr<UControlRigShapeLibrary> GizmoLibrary_DEPRECATED;` — `UPROPERTY()`
- L225 _public member_ `TArray<TSoftObjectPtr<UControlRigShapeLibrary>> ShapeLibraries;` — `UPROPERTY(EditAnywhere, Category = Shapes)`
- L228 _public member_ `FRigVMStatistics Statistics_DEPRECATED;` — `UPROPERTY(transient, DuplicateTransient, meta = (DisplayName = "VM Statistics", DisplayAfter = "VMCompileSettings"))`
- L232 _public member_ `FRigVMDrawContainer DrawContainer_DEPRECATED;` — `UPROPERTY(meta=(DeprecatedProperty, DeprecationMessage = "Use RigVMBlueprint::DrawContainer instead"))`
- L235 _public member_ `FRigInfluenceMapPerEvent Influences;` — `UPROPERTY(EditAnywhere, Category = "Influence Map")`
- L241 _public member_ `FRigHierarchyContainer HierarchyContainer_DEPRECATED;` — `UPROPERTY()`
- L245 _public member_ `TObjectPtr<URigHierarchy> Hierarchy;` — `UPROPERTY(BlueprintReadOnly, Category = "Hierarchy")`
- L248 _public function_ `URigHierarchyController* GetHierarchyController()` — `UFUNCTION(BlueprintCallable, Category = "Hierarchy")`
- L251 _public member_ `FModularRigModel ModularRigModel;` — `UPROPERTY(BlueprintReadOnly, Category = "Modules")`
- L254 _public function_ `virtual UModularRigController* GetModularRigController()` — `UFUNCTION(BlueprintCallable, Category = "Modules")`
- L257 _public function_ `virtual void RecompileModularRig()` — `UFUNCTION(BlueprintCallable, Category = "Control Rig Blueprint")`
- L260 _public member_ `EControlRigType ControlRigType;` — `UPROPERTY(AssetRegistrySearchable)`
- L263 _public member_ `FName ItemTypeDisplayName = TEXT("Con` — `UPROPERTY(AssetRegistrySearchable)`
- L269 _private member_ `bool bSupportsInversion;` — `UPROPERTY(AssetRegistrySearchable)` — Whether or not this rig has an Inversion Event
- L273 _private member_ `bool bSupportsControls;` — `UPROPERTY(AssetRegistrySearchable)` — Whether or not this rig has Controls on It
- L278 _private member_ `TSoftObjectPtr<USkeletalMesh> PreviewSkeletalMesh;` — `UPROPERTY(AssetRegistrySearchable, EditAnywhere, Category="Control Rig Blueprint")`
- L283 _private member_ `TSoftObjectPtr<UObject> SourceHierarchyImport;` — `UPROPERTY(DuplicateTransient, AssetRegistrySearchable, EditAnywhere, Category="Control Rig Blueprint")` — The skeleton from import into a hierarchy
- L287 _private member_ `TSoftObjectPtr<UObject> SourceCurveImport;` — `UPROPERTY(DuplicateTransient, AssetRegistrySearchable, EditAnywhere, Category="Control Rig Blueprint")` — The skeleton from import into a curve
- L291 _private member_ `bool bExposesAnimatableControls;` — `UPROPERTY(AssetRegistrySearchable)` — If set to true, this control rig has animatable controls
- L296 _public member_ `bool bAllowMultipleInstances = false;` — `UPROPERTY(EditAnywhere, Category="Sequencer", AssetRegistrySearchable)` — If set to true, multiple control rig tracks can be created for the same rig in sequencer
- L300 _private function_ `virtual void PathDomainSpecificContentOnLoad() override`
- L301 _private prototype_ `virtual void GetBackwardsCompatibilityPublicFunctions(TArray<FName>& BackwardsCompatiblePublicFunctions, TMap<URigVMLibraryNode*, FRigVMGraphFunctionHeader>& OldHeaders) override;`
- L304 _protected function_ `virtual void CreateMemberVariablesOnLoad() override`
- L305 _protected prototype_ `virtual void PatchVariableNodesOnLoad() override;`
- L306 _protected function_ `virtual void SetHierarchy(TObjectPtr<URigHierarchy> InHierarchy) override`
- L307 _protected function_ `virtual FCompilerResultsLog CompileBlueprint() override`
- L312 _private member_ `TObjectPtr<UControlRigValidator> Validator;` — `UPROPERTY()`
- L314 _private member_ `FRigHierarchyModifiedEvent HierarchyModifiedEvent;`
- L315 _private member_ `FOnRigVMRefreshEditorEvent ModularRigPreCompiled;`
- L316 _private member_ `FOnRigVMRefreshEditorEvent ModularRigCompiled;`
- L319 _private member_ `int32 ModulesRecompilationBracket = 0;` — `UPROPERTY(transient, DuplicateTransient)`
- L323 _private function_ `virtual void HandlePackageDone() override`
- L324 _private function_ `virtual void HandlePackageDoneSuper() override`
- L325 _private function_ `virtual void HandleConfigureRigVMController(const FRigVMClient* InClient, URigVMController* InControllerToConfigure) override`
- L329 _private member_ `float DebugBoneRadius;` — `UPROPERTY()`

### `Plugins/Animation/ControlRig/Source/ControlRigDeveloper/Public/ControlRigDeveloper.h` (Public)


#### class `IControlRigDeveloperModule`  
`class IControlRigDeveloperModule : public IModuleInterface`  
_L10-16_
- inherits: `IModuleInterface`
- L13 _public prototype_ `virtual void RegisterPinTypeColor(UStruct* Struct, const FLinearColor Color) = 0;`
- L14 _public prototype_ `virtual void UnRegisterPinTypeColor(UStruct* Struct) = 0;`
- L15 _public prototype_ `virtual const FLinearColor* FindPinTypeColor(UStruct* Struct) const = 0;`

#### Free symbols / members of external scopes

- L8 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogControlRigDeveloper, Log, All);`
- L8 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogControlRigDeveloper, Log, All);`

### `Plugins/Animation/ControlRig/Source/ControlRigDeveloper/Public/ControlRigEditorAsset.h` (Public)


#### class `UControlRigEditorAssetInterface`  
`class UControlRigEditorAssetInterface : public UInterface`  
_L43-46_
- reflection: `UINTERFACE(MinimalAPI, NotBlueprintable)`
- inherits: `UInterface`

#### class `IControlRigEditorAssetInterface`  
`class IControlRigEditorAssetInterface`  
_L48-419_
- L53 _public prototype_ `static FControlRigAssetInterfacePtr GetInterfaceOuter(const UObject* InObject);`
- L54 _public prototype_ `static TArray<UClass*> FindAllImplementingClasses();`
- L55 _public prototype_ `static bool IsAControlRigAsset(UObject* InObject);`
- L57 _public prototype_ `virtual FRigVMEditorAssetInterfacePtr GetRigVMAssetInterface() = 0;`
- L58 _public function_ `virtual const FRigVMEditorAssetInterfacePtr GetRigVMAssetInterface() const`
- L59 _public prototype_ `virtual TScriptInterface<IControlRigRuntimeAssetInterface> GetRuntimeAssetInterface() const;`
- L62 _public prototype_ `virtual URigHierarchy* GetHierarchy() const = 0;` — `UFUNCTION(BlueprintCallable, Category = ControlRigAsset)`
- L63 _public prototype_ `virtual FRigVMClient* GetRigVMClient();`
- L64 _public prototype_ `virtual UObject* GetDefaultHierarchyOuter() = 0;`
- L68 _protected prototype_ `virtual bool RequiresForceLoadMembersSuper(UObject* InObject) const = 0;`
- L69 _protected prototype_ `virtual void SerializeSuper(FArchive& Ar) = 0;`
- L70 _protected prototype_ `virtual void HandlePackageDoneSuper() = 0;`
- L71 _protected prototype_ `virtual void SetHierarchy(TObjectPtr<URigHierarchy> InHierarchy) = 0;`
- L72 _protected prototype_ `virtual FCompilerResultsLog CompileBlueprint() = 0;`
- L74 _protected function_ `UObject* GetObject()`
- L75 _protected function_ `const UObject* GetObject() const`
- L76 _protected function_ `FControlRigAssetInterfacePtr GetControlRigAssetInterface()`
- L79 _public function_ `void Modify()`
- L80 _public function_ `UObject* GetObjectBeingDebugged()`
- L81 _public function_ `const UObject* GetObjectBeingDebugged() const`
- L83 _public prototype_ `static void CommonInitialization(const FObjectInitializer& ObjectInitializer);`
- L84 _public prototype_ `IControlRigEditorAssetInterface();`
- L87 _public function_ `virtual UClass* GetRigVMSchemaClass() const` — --- IRigVMClientHost interface ---
- L88 _public function_ `virtual UScriptStruct* GetRigVMExecuteContextStruct() const`
- L89 _public prototype_ `virtual UClass* GetRigVMEdGraphClass() const;`
- L90 _public prototype_ `virtual UClass* GetRigVMEdGraphNodeClass() const;`
- L91 _public prototype_ `virtual UClass* GetRigVMEdGraphSchemaClass() const;`
- L92 _public prototype_ `virtual UClass* GetRigVMEditorSettingsClass() const;`
- L96 _public prototype_ `virtual void GetPreloadDependencies(TArray<UObject*>& OutDeps);` — URigVMBlueprint interface virtual UClass* GetRigVMGeneratedClassPrototype() const override { return UControlRigBlueprintGeneratedClass::StaticClass(); }
- L98 _public prototype_ `virtual TArray<FString> GeneratePythonCommands();`
- L99 _public prototype_ `virtual TArray<FString> GeneratePythonContextCommands(const FString InNewBlueprintName, bool bCreateAsset) = 0;`
- L100 _public prototype_ `virtual const FLazyName& GetPanelPinFactoryName() const;`
- L101 _public member_ `static inline const FLazyName ControlRigPanelNodeFactoryName = FLazyName(TEXT("FCon`
- L102 _public prototype_ `virtual IRigVMEditorModule* GetEditorModule() const;`
- L105 _public prototype_ `virtual void Serialize(FArchive& Ar);`
- L110 _public prototype_ `virtual UClass* GetBlueprintClass() const;` — UBlueprint interface
- L111 _public prototype_ `void OnRegeneratedClass(UClass* ClassToRegenerate, UObject* PreviousCDO);`
- L112 _public function_ `virtual bool SupportedByDefaultBlueprintFactory() const`
- L113 _public function_ `virtual bool IsValidForBytecodeOnlyRecompile() const`
- L114 _public prototype_ `virtual void GetTypeActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const;`
- L115 _public prototype_ `virtual void GetInstanceActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const;`
- L116 _public prototype_ `virtual void PreSave(FObjectPreSaveContext ObjectSaveContext);`
- L117 _public prototype_ `virtual void PostLoad();`
- L118 _public prototype_ `virtual void PostTransacted(const FTransactionObjectEvent& TransactionEvent);`
- L119 _public prototype_ `virtual void PostDuplicate(bool bDuplicateForPIE);`
- L120 _public prototype_ `virtual void PostRename(UObject* OldOuter, const FName OldName);`
- L121 _public prototype_ `virtual bool RequiresForceLoadMembers(UObject* InObject) const;`
- L123 _public function_ `virtual bool SupportsGlobalVariables() const`
- L124 _public function_ `virtual bool SupportsLocalVariables() const`
- L125 _public function_ `virtual bool SupportsFunctions() const`
- L126 _public function_ `virtual bool SupportsEventGraphs() const`
- L130 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent);` — UObject interface
- L131 _public prototype_ `virtual void PostEditChangeChainProperty(struct FPropertyChangedChainEvent& PropertyChangedEvent);`
- L136 _public prototype_ `virtual UClass* GetControlRigClass() const;` — `UE_DEPRECATED(5.8, "Use GetControlRigAssetReference instead")`
- L138 _public prototype_ `virtual FControlRigAssetStrongReference GetControlRigAssetReference() const = 0;`
- L140 _public prototype_ `bool IsModularRig() const;`
- L142 _public prototype_ `virtual UControlRig* CreateControlRig();`
- L144 _public prototype_ `virtual UControlRig* GetDebuggedControlRig();`
- L147 _public prototype_ `virtual void SetPreviewMesh(USkeletalMesh* PreviewMesh, bool bMarkAsDirty = true);` — IInterface_PreviewMeshProvider interface
- L148 _public prototype_ `virtual void SetPreviewMeshImpl(USkeletalMesh* PreviewMesh) = 0;`
- L150 _public prototype_ `virtual USkeletalMesh* GetPreviewMesh() const;`
- L152 _public prototype_ `virtual bool IsControlRigModule() const;`
- L156 _public prototype_ `bool CanTurnIntoControlRigModule(bool InAutoConvertHierarchy, FString* OutErrorMessage = nullptr) const;`
- L157 _public prototype_ `bool TurnIntoControlRigModule(bool InAutoConvertHierarchy = false, FString* OutErrorMessage = nullptr);`
- L158 _public prototype_ `bool CanTurnIntoStandaloneRig(FString* OutErrorMessage = nullptr) const;`
- L159 _public prototype_ `bool TurnIntoStandaloneRig(FString* OutErrorMessage = nullptr);`
- L161 _public prototype_ `TArray<URigVMNode*> ConvertHierarchyElementsToSpawnerNodes(URigHierarchy* InHierarchy, TArray<FRigElementKey> InKeys, bool bRemoveElements = true);`
- L165 _public prototype_ `UTexture2D* GetRigModuleIcon() const;`
- L167 _public prototype_ `DECLARE_EVENT_OneParam(IControlRigEditorAssetInterface, FOnRigTypeChanged, FControlRigAssetInterfacePtr);`
- L169 _public function_ `FOnRigTypeChanged& OnRigTypeChanged()`
- L171 _public prototype_ `virtual FModularRigSettings& GetModularRigSettings() = 0;`
- L172 _public function_ `const FModularRigSettings& GetModularRigSettings() const`
- L174 _public prototype_ `virtual FRigHierarchySettings& GetHierarchySettings() = 0;`
- L175 _public function_ `const FRigHierarchySettings& GetHierarchySettings() const`
- L177 _public prototype_ `virtual FRigModuleSettings& GetRigModuleSettings() = 0;`
- L178 _public function_ `virtual const FRigModuleSettings& GetRigModuleSettings() const`
- L183 _public prototype_ `virtual void SetCustomThumbnail(FString InThumbnail) = 0;` — This relates to FAssetThumbnailPool::CustomThumbnailTagName and allows the thumbnail pool to show the thumbnail of the icon rather than the rig itself to avoid deploying the 3D renderer.
- L184 _public prototype_ `virtual FString GetCustomThumbnail() const = 0;`
- L187 _public prototype_ `virtual TArray<FModuleReferenceData>& GetModuleReferenceData() = 0;` — Asset searchable information module references in this rig
- L189 _public prototype_ `virtual UObject* GetOuterForModularModel() = 0;`
- L191 _public prototype_ `virtual TMap<FRigElementKey, FRigElementKeyCollection>& GetArrayConnectionMap() = 0;`
- L192 _public function_ `const TMap<FRigElementKey, FRigElementKeyCollection>& GetArrayConnectionMap() const`
- L194 _public prototype_ `TArray<FModuleReferenceData> FindReferencesToModule() const;`
- L196 _public prototype_ `static EControlRigType GetRigType(const FAssetData& InAsset);`
- L197 _public prototype_ `static TArray<FSoftObjectPath> GetReferencesToRigModule(const FAssetData& InModuleAsset);`
- L199 _public prototype_ `virtual void UpdateExposedModuleConnectors() const;`
- L202 _public prototype_ `TArray<FOverrideStatusSubject> GetOverrideSubjects() const;`
- L203 _public prototype_ `uint32 GetOverrideSubjectsHash() const;`
- L206 _public function_ `FRigVMDrawContainer& GetDrawContainer() const`
- L210 _protected prototype_ `FName FindHostMemberVariableUniqueName(TSharedPtr<FRigVMNameValidator> InNameValidator, const FString& InBaseName);`
- L212 _protected prototype_ `TArray<FModuleReferenceData> GetModuleReferenceDataImpl() const;`
- L214 _protected member_ `FOnRigTypeChanged OnRigTypeChangedDelegate;`
- L216 _protected prototype_ `bool ResolveConnector(const FRigElementKey& DraggedKey, const FRigElementKey& TargetKey, bool bSetupUndoRedo = true);`
- L217 _protected prototype_ `bool ResolveConnectorToArray(const FRigElementKey& DraggedKey, const TArray<FRigElementKey>& TargetKeys, bool bSetupUndoRedo = true);`
- L219 _protected prototype_ `void UpdateConnectionMapFromModel();`
- L221 _protected prototype_ `virtual void SetupDefaultObjectDuringCompilation(URigVMHost* InCDO);`
- L225 _public prototype_ `virtual void SetupPinRedirectorsForBackwardsCompatibility();`
- L227 _public prototype_ `static TArray<FControlRigAssetInterfacePtr> GetCurrentlyOpenRigAssets();`
- L230 _public prototype_ `virtual TArray<TSoftObjectPtr<UControlRigShapeLibrary>>& GetShapeLibraries() = 0;`
- L231 _public function_ `const TArray<TSoftObjectPtr<UControlRigShapeLibrary>>& GetShapeLibraries() const`
- L233 _public prototype_ `const FControlRigShapeDefinition* GetControlShapeByName(const FName& InName) const;`
- L239 _public prototype_ `FName AddTransientControl(const URigVMUnitNode* InNode, const FRigDirectManipulationTarget& InTarget);` — Remove a transient / temporary control used to interact with a pin
- L242 _public prototype_ `FName RemoveTransientControl(const URigVMUnitNode* InNode, const FRigDirectManipulationTarget& InTarget);` — Remove a transient / temporary control used to interact with a pin
- L245 _public prototype_ `FName AddTransientControl(const FRigElementKey& InElement);` — Remove a transient / temporary control used to interact with a bone
- L248 _public prototype_ `FName RemoveTransientControl(const FRigElementKey& InElement);` — Remove a transient / temporary control used to interact with a bone
- L251 _public prototype_ `void ClearTransientControls();` — Removes all  transient / temporary control used to interact with pins
- L255 _public prototype_ `virtual FRigInfluenceMapPerEvent& GetInfluences() = 0;`
- L260 _public function_ `virtual URigHierarchyController* GetHierarchyController()` — `UFUNCTION(BlueprintCallable, Category = ControlRigAsset)`
- L262 _public prototype_ `virtual FModularRigModel& GetModularRigModel() = 0;`
- L263 _public function_ `const FModularRigModel& GetModularRigModel() const`
- L265 _public prototype_ `virtual UModularRigController* GetModularRigController();`
- L267 _public prototype_ `virtual void RecompileModularRig();`
- L270 _public prototype_ `virtual void SetControlRigType(EControlRigType InType) = 0;`
- L271 _public prototype_ `virtual EControlRigType GetControlRigType() const = 0;`
- L273 _public prototype_ `virtual void SetItemTypeDisplayName(FName InName) = 0;`
- L274 _public prototype_ `virtual FName GetItemTypeDisplayName() const = 0;`
- L279 _protected prototype_ `virtual bool& GetSupportsInversion() = 0;` — Whether or not this rig has an Inversion Event
- L282 _protected prototype_ `virtual bool& GetSupportsControls() = 0;` — Whether or not this rig has Controls on It
- L286 _protected prototype_ `virtual TSoftObjectPtr<USkeletalMesh> GetPreviewSkeletalMesh() const = 0;`
- L290 _protected prototype_ `virtual TSoftObjectPtr<UObject>& GetSourceHierarchyImport() = 0;` — The skeleton from import into a hierarchy
- L293 _protected prototype_ `virtual TSoftObjectPtr<UObject>& GetSourceCurveImport() = 0;` — The skeleton from import into a curve
- L296 _protected prototype_ `virtual bool& GetExposesAnimatableControls() = 0;` — If set to true, this control rig has animatable controls
- L300 _public prototype_ `virtual bool& GetAllowMultipleInstances() = 0;` — If set to true, multiple control rig tracks can be created for the same rig in sequencer
- L304 _protected member_ `static TArray<FControlRigAssetInterfacePtr> sCurrentlyOpenedRigBlueprints;`
- L306 _protected prototype_ `virtual void PathDomainSpecificContentOnLoad();`
- L307 _protected prototype_ `virtual void GetBackwardsCompatibilityPublicFunctions(TArray<FName>& BackwardsCompatiblePublicFunctions, TMap<URigVMLibraryNode*, FRigVMGraphFunctionHeader>& OldHeaders) = 0;`
- L308 _protected prototype_ `void PatchRigElementKeyCacheOnLoad();`
- L309 _protected prototype_ `void PatchPropagateToChildren();`
- L312 _protected prototype_ `virtual void CreateMemberVariablesOnLoad();`
- L313 _protected prototype_ `virtual void PatchVariableNodesOnLoad();`
- L316 _public prototype_ `void UpdateElementKeyRedirector(UControlRig* InControlRig) const;`
- L317 _public prototype_ `void PropagatePoseFromInstanceToBP(UControlRig* InControlRig) const;`
- L318 _public prototype_ `void PropagatePoseFromBPToInstances() const;`
- L319 _public prototype_ `void PropagateHierarchyFromBPToInstances() const;`
- L320 _public prototype_ `void PropagateDrawInstructionsFromBPToInstances() const;`
- L321 _public prototype_ `void PropagatePropertyFromBPToInstances(FRigElementKey InRigElement, const FProperty* InProperty) const;`
- L322 _public prototype_ `void PropagatePropertyFromInstanceToBP(FRigElementKey InRigElement, const FProperty* InProperty, UControlRig* InInstance) const;`
- L323 _public prototype_ `void PropagateModuleHierarchyFromBPToInstances() const;`
- L324 _public prototype_ `void UpdateModularDependencyDelegates();`
- L325 _public prototype_ `void OnModularDependencyVMCompiled(UObject* InBlueprint, URigVM* InVM, FRigVMExtendedExecuteContext& InExecuteContext);`
- L326 _public prototype_ `void OnModularDependencyChanged(FRigVMEditorAssetInterfacePtr InBlueprint);`
- L327 _public prototype_ `void RequestConstructionOnAllModules();`
- L328 _public prototype_ `void RefreshModuleVariables();`
- L329 _public prototype_ `void RefreshModuleVariables(const FRigModuleReference* InModule);`
- L330 _public prototype_ `void RefreshModuleConnectors();`
- L331 _public prototype_ `void RefreshModuleConnectors(const FRigModuleReference* InModule, bool bPropagateHierarchy = true);`
- L338 _public function_ `FRigHierarchyModifiedEvent& OnHierarchyModified()` — Returns the modified event, which can be used to subscribe to topological changes happening within the hierarchy. The event is broadcast only after all hierarchy instances are up to date @return The event used for subscription.
- L340 _public function_ `FOnRigVMRefreshEditorEvent& OnModularRigPreCompiled()`
- L341 _public function_ `FOnRigVMRefreshEditorEvent& OnModularRigCompiled()`
- L345 _protected prototype_ `virtual TObjectPtr<UControlRigValidator>& GetValidator() = 0;`
- L347 _protected member_ `FRigHierarchyModifiedEvent HierarchyModifiedEvent;`
- L348 _protected member_ `FOnRigVMRefreshEditorEvent ModularRigPreCompiled;`
- L349 _protected member_ `FOnRigVMRefreshEditorEvent ModularRigCompiled;`
- L351 _protected member_ `int32 ModulesRecompilationBracket = 0;`
- L354 _protected prototype_ `void HandleHierarchyModified(ERigHierarchyNotification InNotification, URigHierarchy* InHierarchy, const FRigNotificationSubject& InSubject);`
- L355 _protected prototype_ `void HandleHierarchyElementKeyChanged(const FRigElementKey& InOldKey, const FRigElementKey& InNewKey);`
- L356 _protected prototype_ `void HandleHierarchyComponentKeyChanged(const FRigComponentKey& InOldKey, const FRigComponentKey& InNewKey);`
- L358 _protected prototype_ `void HandleRigModulesModified(EModularRigNotification InNotification, const FRigModuleReference* InModule);`
- L361 _protected prototype_ `virtual void HandlePackageDone();`
- L362 _protected prototype_ `virtual void HandleConfigureRigVMController(const FRigVMClient* InClient, URigVMController* InControllerToConfigure);`
- L365 _protected prototype_ `void UpdateConnectionMapAfterRename(const FString& InOldModuleName);`
- L382 _protected prototype_ `virtual float& GetDebugBoneRadius() = 0;`
- L387 _private member_ `TPimplPtr<FControlRigEditorAssetUndoClient> EditorUndoClient;` — Editor undo client for this interface
- L392 _public member_ `TArray<FString> ShapeLibrariesToLoadOnPackageLoaded;` — Shape libraries to load during package load completed

#### class `IControlRigEditorAssetInterface::FControlValueScope`  
`class FControlValueScope`  
_L370-380_
- desc: Class used to temporarily cache all current control values and reapply them on destruction
- L373 _public prototype_ `FControlValueScope(FControlRigAssetInterfacePtr InBlueprint);`
- L374 _public prototype_ `~FControlValueScope();`
- L378 _protected member_ `FControlRigAssetInterfacePtr Blueprint;`
- L379 _protected member_ `TMap<FName, FRigControlValue> ControlValues;`

#### class `UControlRigEditorAsset`  
`class UControlRigEditorAsset : public URigVMEditorAsset, public IControlRigEditorAssetInterface, public IInterface_PreviewMeshProvider, public IRigHierarchyProvider`  
_L422-507_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `URigVMEditorAsset,IControlRigEditorAssetInterface,IInterface_PreviewMeshProvider,IRigHierarchyProvider`
- L428 _private member_ `TObjectPtr<UControlRigValidator> Validator;` — `UPROPERTY()`
- L431 _private member_ `float DebugBoneRadius;` — `UPROPERTY()`
- L434 _public function_ `virtual FRigVMEditorAssetInterfacePtr GetRigVMAssetInterface() override`
- L437 _public function_ `virtual UClass* GetRigVMSchemaClass() const override` — --- IRigVMClientHost interface ---
- L438 _public function_ `virtual UScriptStruct* GetRigVMExecuteContextStruct() const override`
- L439 _public function_ `virtual UClass* GetRigVMEdGraphClass() const override`
- L440 _public function_ `virtual UClass* GetRigVMEdGraphNodeClass() const override`
- L441 _public function_ `virtual UClass* GetRigVMEdGraphSchemaClass() const override`
- L442 _public function_ `virtual UClass* GetRigVMEditorSettingsClass() const override`
- L447 _public function_ `virtual void SetPreviewMesh(USkeletalMesh* PreviewMesh, bool bMarkAsDirty = true) override` — `UFUNCTION(BlueprintCallable, Category = "Control Rig Asset")` — IInterface_PreviewMeshProvider Overrides Begins
- L448 _public function_ `virtual USkeletalMesh* GetPreviewMesh() const override`
- L452 _public prototype_ `virtual URigHierarchy* GetHierarchy() const override;` — IRigHierarchyProvider Overrides Begins
- L456 _protected prototype_ `virtual void PreSave(FObjectPreSaveContext SaveContext) override;`
- L457 _protected prototype_ `virtual void PostRename(UObject* OldOuter, const FName OldName) override;`
- L460 _protected function_ `virtual FControlRigAssetStrongReference GetControlRigAssetReference() const override` — IControlRigEditorAssetInterface Overrides Begins
- L461 _protected function_ `virtual bool RequiresForceLoadMembersSuper(UObject* InObject) const override`
- L462 _protected function_ `virtual void SerializeSuper(FArchive& Ar) override`
- L463 _protected prototype_ `virtual void SetHierarchy(TObjectPtr<URigHierarchy> InHierarchy) override;`
- L464 _protected prototype_ `virtual FCompilerResultsLog CompileBlueprint() override;`
- L465 _protected prototype_ `virtual FModularRigSettings& GetModularRigSettings() override;`
- L466 _protected prototype_ `virtual FRigHierarchySettings& GetHierarchySettings() override;`
- L467 _protected prototype_ `virtual FRigModuleSettings& GetRigModuleSettings() override;`
- L468 _protected prototype_ `virtual void SetCustomThumbnail(FString InThumbnail) override;`
- L469 _protected prototype_ `virtual FString GetCustomThumbnail() const override;`
- L470 _protected prototype_ `virtual TArray<FModuleReferenceData>& GetModuleReferenceData() override;`
- L471 _protected prototype_ `virtual TMap<FRigElementKey, FRigElementKeyCollection>& GetArrayConnectionMap() override;`
- L472 _protected prototype_ `virtual FRigInfluenceMapPerEvent& GetInfluences() override;`
- L473 _protected prototype_ `virtual FModularRigModel& GetModularRigModel() override;`
- L474 _protected prototype_ `virtual void SetControlRigType(EControlRigType InType) override;`
- L475 _protected prototype_ `virtual EControlRigType GetControlRigType() const override;`
- L476 _protected prototype_ `virtual void SetItemTypeDisplayName(FName InName) override;`
- L477 _protected prototype_ `virtual FName GetItemTypeDisplayName() const override;`
- L478 _protected prototype_ `virtual bool& GetSupportsInversion() override;`
- L479 _protected prototype_ `virtual bool& GetSupportsControls() override;`
- L480 _protected prototype_ `virtual TSoftObjectPtr<USkeletalMesh> GetPreviewSkeletalMesh() const override;`
- L481 _protected prototype_ `virtual TSoftObjectPtr<UObject>& GetSourceHierarchyImport() override;`
- L482 _protected prototype_ `virtual TSoftObjectPtr<UObject>& GetSourceCurveImport() override;`
- L483 _protected prototype_ `virtual bool& GetExposesAnimatableControls() override;`
- L484 _protected prototype_ `virtual bool& GetAllowMultipleInstances() override;`
- L485 _protected function_ `virtual void GetBackwardsCompatibilityPublicFunctions(TArray<FName>& BackwardsCompatiblePublicFunctions, TMap<URigVMLibraryNode*, FRigVMGraphFunctionHeader>& OldHeaders) override`
- L486 _protected prototype_ `virtual TObjectPtr<UControlRigValidator>& GetValidator() override;`
- L487 _protected prototype_ `virtual float& GetDebugBoneRadius() override;`
- L488 _protected prototype_ `virtual TArray<TSoftObjectPtr<UControlRigShapeLibrary>>& GetShapeLibraries() override;`
- L489 _protected prototype_ `virtual UObject* GetDefaultHierarchyOuter() override;`
- L490 _protected function_ `virtual const FLazyName& GetPanelPinFactoryName() const override`
- L491 _protected prototype_ `virtual void SetPreviewMeshImpl(USkeletalMesh* PreviewMesh) override;`
- L492 _protected function_ `virtual UObject* GetOuterForModularModel() override`
- L494 _protected function_ `virtual TArray<FString> GeneratePythonCommands() override`
- L495 _protected prototype_ `virtual TArray<FString> GeneratePythonContextCommands(const FString InNewBlueprintName, bool bCreateAsset) override;`
- L498 _protected function_ `virtual void HandlePackageDone() override`
- L499 _protected function_ `virtual void HandlePackageDoneSuper() override`
- L500 _protected function_ `virtual void HandleConfigureRigVMController(const FRigVMClient* InClient, URigVMController* InControllerToConfigure) override`
- L505 _protected prototype_ `virtual IRigVMEditorModule* GetEditorModule() const override;`

#### Free symbols / members of external scopes

- L26 _macro_ `#define UE_API CONTROLRIGDEVELOPER_API`
- L32 _typedef_ `typedef TScriptInterface<IControlRigEditorAssetInterface> FControlRigAssetInterfacePtr;`
- L167 _delegate_ `DECLARE_EVENT_OneParam(IControlRigEditorAssetInterface, FOnRigTypeChanged, FControlRigAssetInterfacePtr);`

### `Plugins/Animation/ControlRig/Source/ControlRigDeveloper/Public/ControlRigIOMapping.h` (Public)


#### struct `FControlRigIOMapping`  
`struct FControlRigIOMapping : public TSharedFromThis<FControlRigIOMapping>`  
_L21-137_
- inherits: `TSharedFromThis<FControlRigIOMapping>`
- L23 _public prototype_ `DECLARE_DELEGATE_RetVal(USkeleton*, FOnGetTargetSkeleton);`
- L24 _public prototype_ `DECLARE_DELEGATE_RetVal(FControlRigAssetStrongReference, FOnGetTargetAssetReference);`
- L25 _public prototype_ `DECLARE_DELEGATE_TwoParams(FOnPinCheckStateChanged, ECheckBoxState , FName );`
- L26 _public prototype_ `DECLARE_DELEGATE_ThreeParams(FOnVariableMappingChanged, const FName& , const FName& , bool );`
- L28 _public prototype_ `FControlRigIOMapping() = delete;`
- L29 _public prototype_ `FControlRigIOMapping(TMap<FName, FName>& InInputMapping, TMap<FName, FName>& InOutputMapping, TArray<FOptionalPinFromProperty>& InCustomPinProperties);`
- L30 _public prototype_ `virtual ~FControlRigIOMapping();`
- L54 _public prototype_ `bool CreateVariableMappingWidget(IDetailLayoutBuilder& DetailBuilder);`
- L56 _public function_ `const TMap<FName, FRigVMExternalVariable>& GetInputVariables() const`
- L60 _public function_ `const TMap<FName, FRigVMExternalVariable>& GetOutputVariables() const`
- L65 _public prototype_ `const TArray<FControlRigIOMapping::FControlsInfo>& GetControls() const;`
- L67 _public prototype_ `void RebuildExposedProperties();`
- L69 _public function_ `FOnGetTargetSkeleton& GetOnGetTargetSkeletonDelegate()`
- L74 _public function_ `FOnGetTargetAssetReference& GetOnGetTargetAssetReferenceDelegate()`
- L79 _public function_ `FOnPinCheckStateChanged& GetOnPinCheckStateChangedDelegate()`
- L84 _public function_ `FOnVariableMappingChanged& GetOnVariableMappingChanged()`
- L89 _public prototype_ `bool IsInputProperty(const FName& PropertyName) const;`
- L91 _public prototype_ `void SetIOMapping(bool bInput, const FName& SourceProperty, const FName& TargetCurve);`
- L92 _public prototype_ `FName GetIOMapping(bool bInput, const FName& SourceProperty) const;`
- L94 _public function_ `void SetIgnoreVariablesWithNoMemory(bool bIgnore)`
- L97 _private member_ `FOnGetTargetSkeleton OnGetTargetSkeletonDelegate;`
- L98 _private member_ `FOnGetTargetAssetReference OnGetTargetAssetReferenceDelegate;`
- L99 _private member_ `FOnPinCheckStateChanged OnPinCheckStateChangedDelegate;`
- L100 _private member_ `FOnVariableMappingChanged OnVariableMappingChangedDelegate;`
- L102 _private member_ `TMap<FName, FName>& InputMapping;`
- L103 _private member_ `TMap<FName, FName>& OutputMapping;`
- L104 _private member_ `TArray<FOptionalPinFromProperty>& CustomPinProperties;`
- L107 _private member_ `FRigControlsData RigControlsData;` — Controls data
- L109 _private member_ `bool bIgnoreVariablesWithNoMemory = false;`
- L112 _private prototype_ `static void GetVariables(const FControlRigAssetStrongReference& TargetSource, bool bInput, bool bIgnoreVariablesWithNoMemory, TMap<FName, FRigVMExternalVariable>& OutParameters);` — property related things
- L114 _private member_ `TMap<FName, FRigVMExternalVariable> InputVariables;`
- L115 _private member_ `TMap<FName, FRigVMExternalVariable> OutputVariables;`
- L118 _private prototype_ `bool IsPropertyExposeEnabled(FName PropertyName) const;` — pin option related
- L119 _private prototype_ `ECheckBoxState IsPropertyExposed(FName PropertyName) const;`
- L120 _private prototype_ `void OnPropertyExposeCheckboxChanged(ECheckBoxState NewState, FName PropertyName);`
- L124 _private prototype_ `void OnVariableMappingChanged(const FName& PathName, const FName& Curve, bool bInput);` — SRigVMVariableMappingWidget related
- L125 _private prototype_ `FName GetVariableMapping(const FName& PathName, bool bInput);`
- L126 _private prototype_ `void GetAvailableMapping(const FName& PathName, TArray<FName>& OutArray, bool bInput);`
- L127 _private prototype_ `void CreateVariableMapping(const FString& FilteredText, TArray< TSharedPtr<FRigVMVariableMappingInfo> >& OutArray, bool bInput);`
- L130 _private prototype_ `bool IsAvailableToMapToCurve(const FName& PropertyName, bool bInput) const;`
- L131 _private prototype_ `const FControlsInfo* FindControlElement(const FName& InControlName) const;`
- L134 _private prototype_ `const UClass* GetTargetClass() const;` — `UE_DEPRECATED(5.8, "Use GetTargetAssetReference instead")`
- L135 _private prototype_ `FControlRigAssetStrongReference GetTargetAssetReference() const;`
- L136 _private prototype_ `USkeleton* GetTargetSkeleton() const;`

#### struct `FControlRigIOMapping::FControlsInfo`  
`struct FControlsInfo`  
_L32-39_
- L34 _public member_ `FName Name;`
- L35 _public member_ `FString DisplayName;`
- L36 _public member_ `FEdGraphPinType PinType;`
- L37 _public member_ `ERigControlType ControlType;`
- L38 _public member_ `FString DefaultValue;`

#### struct `FControlRigIOMapping::FRigControlsData`  
`struct FRigControlsData`  
_L42-52_
- desc: Helper enabling quering controls in editor from a Control Rig class
- L44 _public prototype_ `FRigControlsData() = default;`
- L46 _public prototype_ `const TArray<FControlsInfo>& GetControls(const FControlRigAssetStrongReference& ControlRigAssetReference, USkeleton* TargetSkeleton) const;`
- L50 _private member_ `mutable FControlRigAssetStrongReference ControlsInfoAssetReference;` — Controls data
- L51 _private member_ `mutable TArray<FControlsInfo> ControlsInfo;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API CONTROLRIGDEVELOPER_API`
- L23 _delegate_ `DECLARE_DELEGATE_RetVal(USkeleton*, FOnGetTargetSkeleton);`
- L24 _delegate_ `DECLARE_DELEGATE_RetVal(FControlRigAssetStrongReference, FOnGetTargetAssetReference);`
- L25 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnPinCheckStateChanged, ECheckBoxState , FName );`
- L26 _delegate_ `DECLARE_DELEGATE_ThreeParams(FOnVariableMappingChanged, const FName& , const FName& , bool );`

### `Plugins/Animation/ControlRig/Source/ControlRigDeveloper/Public/ControlRigSchema.h` (Public)


#### class `UControlRigSchema`  
`class UControlRigSchema : public URigVMSchema`  
_L12-26_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `URigVMSchema`
- L18 _public function_ `virtual UClass* GetEdGraphSchemaClass() const override`
- L23 _public prototype_ `virtual bool ShouldUnfoldStruct(URigVMController* InController, const UStruct* InStruct) const override;`
- L25 _public prototype_ `virtual bool SupportsUnitFunction_NoLock(URigVMController* InController, const FRigVMFunction* InUnitFunction, FRigVMRegistryHandle& InRegistry) const override;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API CONTROLRIGDEVELOPER_API`

### `Plugins/Animation/ControlRig/Source/ControlRigDeveloper/Public/ControlRigVisualGraphUtils.h` (Public)


#### struct `FControlRigVisualGraphUtils`  
`struct FControlRigVisualGraphUtils`  
_L11-14_
- L13 _public prototype_ `static FString DumpRigHierarchyToDotGraph(URigHierarchy* InHierarchy, const FName& InEventName = NAME_None);`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API CONTROLRIGDEVELOPER_API`

### `Plugins/Animation/ControlRig/Source/ControlRigDeveloper/Public/Graph/ControlRigGraph.h` (Public)


#### class `UControlRigGraph`  
`class UControlRigGraph : public URigVMEdGraph`  
_L24-168_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `URigVMEdGraph`
- L29 _public prototype_ `UControlRigGraph();`
- L32 _public prototype_ `virtual void InitializeFromAsset(FRigVMEditorAssetInterfacePtr InBlueprint) override;` — Set up this graph
- L34 _public prototype_ `virtual bool HandleModifiedEvent_Internal(ERigVMGraphNotifType InNotifType, URigVMGraph* InGraph, UObject* InSubject) override;`
- L38 _public function_ `const TArray<TSharedPtr<FRigVMStringWithTag>>* GetBoneNameList(URigVMPin* InPin = nullptr) const`
- L42 _public function_ `const TArray<TSharedPtr<FRigVMStringWithTag>>* GetControlNameList(URigVMPin* InPin = nullptr) const`
- L46 _public function_ `const TArray<TSharedPtr<FRigVMStringWithTag>>* GetControlNameListWithoutAnimationChannels(URigVMPin* InPin = nullptr) const`
- L50 _public function_ `const TArray<TSharedPtr<FRigVMStringWithTag>>* GetNullNameList(URigVMPin* InPin = nullptr) const`
- L54 _public function_ `const TArray<TSharedPtr<FRigVMStringWithTag>>* GetCurveNameList(URigVMPin* InPin = nullptr) const`
- L58 _public function_ `const TArray<TSharedPtr<FRigVMStringWithTag>>* GetConnectorNameList(URigVMPin* InPin = nullptr) const`
- L62 _public function_ `const TArray<TSharedPtr<FRigVMStringWithTag>>* GetSocketNameList(URigVMPin* InPin = nullptr) const`
- L67 _public prototype_ `virtual const TArray<TSharedPtr<FRigVMStringWithTag>>* GetNameListForWidget(const FString& InWidgetName) const override;`
- L69 _public prototype_ `void CacheNameLists(URigHierarchy* InHierarchy, const FRigVMDrawContainer* DrawContainer, TArray<TSoftObjectPtr<UControlRigShapeLibrary>> ShapeLibraries);`
- L70 _public prototype_ `const TArray<TSharedPtr<FRigVMStringWithTag>>* GetElementNameList(ERigElementType InElementType = ERigElementType::Bone) const;`
- L71 _public prototype_ `const TArray<TSharedPtr<FRigVMStringWithTag>>* GetElementNameList(URigVMPin* InPin = nullptr) const;`
- L72 _public prototype_ `const TArray<TSharedPtr<FRigVMStringWithTag>> GetSelectedElementsNameList() const;`
- L73 _public prototype_ `const TArray<TSharedPtr<FRigVMStringWithTag>>* GetDrawingNameList(URigVMPin* InPin = nullptr) const;`
- L74 _public prototype_ `const TArray<TSharedPtr<FRigVMStringWithTag>>* GetShapeNameList(URigVMPin* InPin = nullptr) const;`
- L76 _public prototype_ `FReply HandleGetSelectedClicked(URigVMEdGraph* InEdGraph, URigVMPin* InPin, FString InDefaultValue);`
- L77 _public prototype_ `FReply HandleBrowseClicked(URigVMEdGraph* InEdGraph, URigVMPin* InPin, FString InDefaultValue);`
- L82 _private function_ `template<class T> static bool IncludeElementInNameList(const T* InElement)`
- L88 _private function_ `template<class T> void CacheNameListForHierarchy(UControlRig* InControlRig, URigHierarchy* InHierarchy, TArray<TSharedPtr<FRigVMStringWithTag>>& OutNameList, bool bFilter = true)`
- L138 _private function_ `template<class T> void CacheNameList(const T& ElementList, TArray<TSharedPtr<FRigVMStringWithTag>>& OutNameList)`
- L155 _private member_ `TMap<ERigElementType, TArray<TSharedPtr<FRigVMStringWithTag>>> ElementNameLists;`
- L156 _private member_ `TArray<TSharedPtr<FRigVMStringWithTag>> ControlNameListWithoutAnimationChannels;`
- L157 _private member_ `TArray<TSharedPtr<FRigVMStringWithTag>> DrawingNameList;`
- L158 _private member_ `TArray<TSharedPtr<FRigVMStringWithTag>> ShapeNameList;`
- L159 _private member_ `int32 LastHierarchyTopologyVersion;`
- L161 _private member_ `static TArray<TSharedPtr<FRigVMStringWithTag>> EmptyElementNameList;`
- L171 _function_ `template<> inline bool UControlRigGraph::IncludeElementInNameList<FRigControlElement>(const FRigControlElement* InElement)`

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API CONTROLRIGDEVELOPER_API`

### `Plugins/Animation/ControlRig/Source/ControlRigDeveloper/Public/Graph/ControlRigGraphNode.h` (Public)


#### class `UControlRigGraphNode`  
`class UControlRigGraphNode : public URigVMEdGraphNode`  
_L29-63_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `URigVMEdGraphNode`
- desc: Base class for animation ControlRig-related nodes
- L44 _public prototype_ `UControlRigGraphNode();`
- L48 _public prototype_ `void AddPinSearchMetaDataInfo(const UEdGraphPin* Pin, TArray<FSearchTagDataPair>& OutTaggedMetaData) const;`
- L50 _public prototype_ `void AddRigVMPinSearchMetaDataInfo(const UEdGraphPin* Pin, TArray<UBlueprintExtension::FSearchTagDataPair>& OutTaggedMetaData) const;`

#### Free symbols / members of external scopes

- L17 _macro_ `#define UE_API CONTROLRIGDEVELOPER_API`

### `Plugins/Animation/ControlRig/Source/ControlRigDeveloper/Public/Graph/ControlRigGraphSchema.h` (Public)


#### class `UControlRigGraphSchema`  
`class UControlRigGraphSchema : public URigVMEdGraphSchema`  
_L22-40_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `URigVMEdGraphSchema`
- L28 _public member_ `static inline const FLazyName GraphName_ControlRig = FLazyName(TEXT("Rig"` — Name constants
- L31 _public prototype_ `UControlRigGraphSchema();`
- L34 _public prototype_ `virtual FLinearColor GetPinTypeColor(const FEdGraphPinType& PinType) const override;` — UEdGraphSchema interface
- L37 _public function_ `virtual const FLazyName& GetRootGraphName() const override` — URigVMEdGraphSchema interface
- L38 _public prototype_ `virtual bool IsRigVMDefaultEvent(const FName& InEventName) const override;`
- L39 _public function_ `virtual bool SupportsPreviewFromHereOnNode(const UEdGraphNode* InNode) const override`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API CONTROLRIGDEVELOPER_API`
