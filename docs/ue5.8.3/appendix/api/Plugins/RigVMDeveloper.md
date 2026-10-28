# Plugins / RigVMDeveloper

- module root: `Plugins/Runtime/RigVM/Source/RigVMDeveloper`
- headers: 54; symbols: 4558
- symbol kinds: class=83, delegate=43, enum=16, enumerator=113, externvar=1, function=734, macro=48, member=896, namespace=9, prototype=2492, struct=107, typedef=16
- DynamicallyLoadedModuleNames: RigVMEditor
- PrivateDependencyModuleNames: ApplicationCore, BlueprintGraph, EditorFramework, GraphEditor, Kismet, MessageLog, Slate, SlateCore, UnrealEd
- PrivateIncludePathModuleNames: RigVMEditor
- PublicDependencyModuleNames: AnimationCore, AssetTools, Core, CoreUObject, Engine, Json, KismetCompiler, Projects, RigVM, Scribble, VisualGraphUtils

### `Plugins/Runtime/RigVM/Source/RigVMDeveloper/Public/EdGraph/RigVMEdGraph.h` (Public)


#### struct `FRigVMStringTag`  
`struct FRigVMStringTag`  
_L21-64_
- L25 _public function_ `FRigVMStringTag() : Name(NAME_None) , Color(FLinearColor::Red)`
- L30 _public function_ `explicit FRigVMStringTag(const FName& InName, const FLinearColor& InColor) : Name(InName) , Color(InColor)`
- L36 _public function_ `const FName& GetName() const`
- L41 _public function_ `const FLinearColor& GetColor() const`
- L46 _public function_ `bool IsValid() const`
- L51 _public function_ `bool Equals(const FName& InOther) const`
- L56 _public function_ `bool Equals(const FRigVMStringTag& InOther) const`
- L62 _private member_ `FName Name;`
- L63 _private member_ `FLinearColor Color;`

#### struct `FRigVMStringWithTag`  
`struct FRigVMStringWithTag`  
_L66-131_
- L70 _public prototype_ `FRigVMStringWithTag() = default;`
- L72 _public function_ `FRigVMStringWithTag(const FString& InString, const FRigVMStringTag& InTag = FRigVMStringTag()) : String(InString) , Tag(InTag)`
- L78 _public function_ `const FString& GetString() const`
- L83 _public function_ `FString GetStringWithTag() const`
- L93 _public function_ `bool HasTag() const`
- L98 _public function_ `const FRigVMStringTag& GetTag() const`
- L103 _public function_ `bool operator ==(const FRigVMStringWithTag& InOther) const`
- L108 _public function_ `bool operator >(const FRigVMStringWithTag& InOther) const`
- L113 _public function_ `bool operator <(const FRigVMStringWithTag& InOther) const`
- L118 _public function_ `bool Equals(const FString& InOther) const`
- L123 _public function_ `bool Equals(const FRigVMStringWithTag& InOther) const`
- L129 _private member_ `FString String;`
- L130 _private member_ `FRigVMStringTag Tag;`

#### class `URigVMEdGraph`  
`class URigVMEdGraph : public UEdGraph, public IRigVMEditorSideObject`  
_L136-239_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UEdGraph,IRigVMEditorSideObject`
- L141 _public prototype_ `URigVMEdGraph();`
- L144 _public prototype_ `virtual FRigVMClient* GetRigVMClient() const override;` — IRigVMEditorSideObject interface
- L145 _public prototype_ `virtual FString GetRigVMNodePath() const override;`
- L146 _public prototype_ `virtual void HandleRigVMGraphRenamed(const FString& InOldNodePath, const FString& InNewNodePath) override;`
- L150 _public prototype_ `const URigVMBlueprint* GetBlueprintDefaultObject() const;` — `UE_DEPRECATED(5.7, "Please use const FRigVMEditorAssetInterfacePtr GetAssetDefaultObject() const")` — Set up this graph
- L151 _public prototype_ `const FRigVMEditorAssetInterfacePtr GetAssetDefaultObject() const;`
- L152 _public prototype_ `void SetBlueprintClass(const UClass* InClass);`
- L154 _public function_ `virtual void InitializeFromBlueprint(URigVMBlueprint* InBlueprint)` — `UE_DEPRECATED(5.7, "Please use void InitializeFromAsset(FRigVMEditorAssetInterfacePtr InAsset);")`
- L155 _public prototype_ `virtual void InitializeFromAsset(FRigVMEditorAssetInterfacePtr InAsset);`
- L156 _public prototype_ `bool IsPreviewGraph() const;`
- L159 _public prototype_ `const URigVMEdGraphSchema* GetRigVMEdGraphSchema();` — Get the ed graph schema
- L163 _public prototype_ `virtual void Serialize(FArchive& Ar) override;` — Customize blueprint changes based on backwards compatibility
- L168 _public member_ `bool bSuspendModelNotifications;`
- L169 _public member_ `bool bIsTemporaryGraphForCopyPaste;`
- L170 _public member_ `bool bIsSelecting;`
- L172 _public prototype_ `UEdGraphNode* FindNodeForModelNodeName(const FName& InModelNodeName, const bool bCacheIfRequired = true);`
- L175 _public prototype_ `URigVMBlueprint* GetBlueprint() const;` — `UE_DEPRECATED(5.7, "Please use FRigVMEditorAssetInterfacePtr GetAsset() const")`
- L176 _public prototype_ `FRigVMEditorAssetInterfacePtr GetAsset() const;`
- L177 _public prototype_ `URigVMGraph* GetModel() const;`
- L178 _public prototype_ `URigVMController* GetController() const;`
- L179 _public function_ `bool IsRootGraph() const`
- L180 _public prototype_ `const URigVMEdGraph* GetRootGraph() const;`
- L182 _public prototype_ `void HandleModifiedEvent(ERigVMGraphNotifType InNotifType, URigVMGraph* InGraph, UObject* InSubject);`
- L183 _public prototype_ `virtual bool HandleModifiedEvent_Internal(ERigVMGraphNotifType InNotifType, URigVMGraph* InGraph, UObject* InSubject);`
- L185 _public prototype_ `int32 GetInstructionIndex(const URigVMEdGraphNode* InNode, bool bAsInput);`
- L187 _public prototype_ `void CacheEntryNameList();`
- L188 _public prototype_ `const TArray<TSharedPtr<FRigVMStringWithTag>>* GetEntryNameList(URigVMPin* InPin = nullptr) const;`
- L190 _public function_ `virtual const TArray<TSharedPtr<FRigVMStringWithTag>>* GetNameListForWidget(const FString& InWidgetName) const`
- L192 _public prototype_ `void AddLocalVariableSearchMetaDataInfo(const FName InVariableName, TArray<UBlueprintExtension::FSearchTagDataPair>& OutTaggedMetaData) const;`
- L195 _public member_ `FString ModelNodePath;` — `UPROPERTY()`
- L198 _public member_ `bool bIsFunctionDefinition;` — `UPROPERTY()`
- L202 _protected prototype_ `virtual void AddNode(UEdGraphNode* NodeToAdd, bool bUserAction = false, bool bSelectNewNode = true) override;`
- L206 _private member_ `FRigVMEdGraphNodeClicked OnGraphNodeClicked;`
- L208 _private member_ `TMap<URigVMNode*, TPair<int32, int32>> CachedInstructionIndices;`
- L210 _private prototype_ `void RemoveNode(UEdGraphNode* InNode);`
- L213 _protected prototype_ `void HandleVMCompiledEvent(UObject* InCompiledObject, URigVM* InVM, FRigVMExtendedExecuteContext& InContext);`
- L216 _private member_ `TMap<FName, UEdGraphNode*> ModelNodePathToEdNode;`
- L217 _private member_ `mutable TWeakObjectPtr<URigVMGraph> CachedModelGraph;`
- L218 _private member_ `TArray<TSharedPtr<FRigVMStringWithTag>> EntryNameList;`
- L219 _private member_ `const UClass* RigVMBlueprintClass;`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API RIGVMDEVELOPER_API`
- L133 _delegate_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FRigVMEdGraphNodeClicked, URigVMEdGraphNode*, const FGeometry&, const FPointerEvent&);`
- L133 _prototype_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FRigVMEdGraphNodeClicked, URigVMEdGraphNode*, const FGeometry&, const FPointerEvent&);`

### `Plugins/Runtime/RigVM/Source/RigVMDeveloper/Public/EdGraph/RigVMEdGraphNode.h` (Public)


#### class `URigVMEdGraphNode`  
`class URigVMEdGraphNode : public UEdGraphNode`  
_L23-353_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UEdGraphNode`
- desc: Base class for RigVM editor side nodes
- L41 _private member_ `FString ModelNodePath;` — `UPROPERTY()`
- L44 _private member_ `TWeakObjectPtr<URigVMNode> CachedModelNode;` — `UPROPERTY(transient)`
- L47 _private member_ `TMap<FString, TWeakObjectPtr<URigVMPin>> PinPathToModelPin;` — `UPROPERTY(transient)`
- L52 _private member_ `FName PropertyName_DEPRECATED;` — `UPROPERTY()` — The property we represent. For template nodes this represents the struct/property type name.
- L55 _private member_ `FString StructPath_DEPRECATED;` — `UPROPERTY()`
- L59 _private member_ `FEdGraphPinType PinType_DEPRECATED;` — `UPROPERTY()` — Pin Type for property
- L63 _private member_ `int32 ParameterType_DEPRECATED;` — `UPROPERTY()` — The type of parameter
- L67 _private member_ `TArray<FString> ExpandedPins_DEPRECATED;` — `UPROPERTY()` — Expanded pins
- L71 _private member_ `FVector2D Dimensions;` — Cached dimensions of this node (used for auto-layout)
- L74 _private member_ `mutable FText NodeTitle;` — The cached node titles
- L77 _private member_ `mutable FText FullNodeTitle;` — The cached fulol node title
- L80 _private member_ `bool bSubTitleEnabled;` — Set this to true to enable the sub title
- L84 _public function_ `void SetSubTitleEnabled(bool bEnabled = true)`
- L89 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FNodeTitleDirtied);`
- L90 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FNodePinsChanged);`
- L91 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FNodePinExpansionChanged);`
- L92 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FNodeBeginRemoval);`
- L106 _public prototype_ `URigVMEdGraphNode();`
- L110 _public function_ `virtual bool Modify( bool bAlwaysMarkDirty=true )`
- L114 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;` — UEdGraphNode Interface.
- L115 _public prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L116 _public prototype_ `virtual FLinearColor GetNodeBodyTintColor() const;`
- L117 _public prototype_ `virtual bool ShowPaletteIconOnNode() const override;`
- L118 _public prototype_ `virtual FSlateIcon GetIconAndTint(FLinearColor& OutColor) const override;`
- L119 _public prototype_ `virtual void AllocateDefaultPins() override;`
- L120 _public prototype_ `virtual void ReconstructNode() override;`
- L121 _public prototype_ `virtual void ReconstructNode_Internal(bool bForce = false);`
- L122 _public prototype_ `virtual void GetNodeContextMenuActions(class UToolMenu* Menu, class UGraphNodeContextMenuContext* Context) const override;`
- L123 _public prototype_ `virtual void DestroyNode() override;`
- L124 _public prototype_ `virtual void PinDefaultValueChanged(UEdGraphPin* Pin) override;`
- L125 _public prototype_ `virtual FText GetTooltipText() const override;`
- L126 _public prototype_ `virtual bool CanCreateUnderSpecifiedSchema(const UEdGraphSchema* InSchema) const override;`
- L127 _public prototype_ `virtual void AutowireNewNode(UEdGraphPin* FromPin) override;`
- L128 _public function_ `virtual bool SupportsCommentBubble() const override`
- L129 _public prototype_ `virtual bool IsSelectedInEditor() const;`
- L130 _public prototype_ `virtual bool ShouldDrawNodeAsControlPointOnly(int32& OutInputPinIndex, int32& OutOutputPinIndex) const override;`
- L131 _public prototype_ `virtual void BeginDestroy() override;`
- L134 _public prototype_ `virtual void AddPinSearchMetaDataInfo(const UEdGraphPin* Pin, TArray<FSearchTagDataPair>& OutTaggedMetaData) const override;`
- L136 _public prototype_ `void AddRigVMSearchMetaDataInfo(TArray<struct UBlueprintExtension::FSearchTagDataPair>& OutTaggedMetaData) const;`
- L137 _public prototype_ `void AddRigVMPinSearchMetaDataInfo(const UEdGraphPin* Pin, TArray<UBlueprintExtension::FSearchTagDataPair>& OutTaggedMetaData) const;`
- L140 _public prototype_ `virtual FString GetPinMetaData(FName InPinName, FName InKey) override;`
- L141 _public prototype_ `virtual TSharedPtr<class INameValidatorInterface> MakeNameValidator() const override;`
- L142 _public prototype_ `void RequestRename(float InDelay = 0.f);`
- L144 _public prototype_ `virtual bool IsDeprecated() const override;`
- L145 _public prototype_ `bool IsOutDated() const;`
- L146 _public prototype_ `virtual FEdGraphNodeDeprecationResponse GetDeprecationResponse(EEdGraphNodeDeprecationType DeprecationType) const override;`
- L149 _public function_ `void SetDimensions(const FVector2D& InDimensions)` — Set the cached dimensions of this node
- L152 _public function_ `const FVector2D& GetDimensions() const` — Get the cached dimensions of this node
- L155 _public prototype_ `bool IsPinExpanded(const FString& InPinPath);` — Check a pin's expansion state
- L158 _public prototype_ `void CopyPinDefaultsToModel(UEdGraphPin* Pin, bool bUndo = false, bool bPrintPythonCommand = false);` — Propagate pin defaults to underlying properties if they have changed
- L162 _public prototype_ `URigVMBlueprint* GetBlueprint() const;` — `UE_DEPRECATED(5.7, "Please use FRigVMEditorAssetInterfacePtr GetAsset() const")` — Get the blueprint that this node is contained within
- L163 _public prototype_ `FRigVMEditorAssetInterfacePtr GetAsset() const;`
- L166 _public prototype_ `URigVMGraph* GetModel() const;` — Get the VM model this node lives within
- L169 _public prototype_ `URigVMController* GetController() const;` — Get the blueprint that this node is contained within
- L172 _public prototype_ `URigVMNode* GetModelNode() const;` — Get the VM node this is node is wrapping
- L175 _public prototype_ `FName GetModelNodeName() const;` — Get the VM node name this node is wrapping
- L178 _public prototype_ `const FString& GetModelNodePath() const;` — Get the VM node path this node is wrapping
- L180 _public prototype_ `URigVMPin* GetModelPinFromPinPath(const FString& InPinPath) const;`
- L183 _public prototype_ `void HandleAddAggregateElement(const FString& InNodePath);` — Add a new element to the aggregate node referred to by the property path
- L186 _public prototype_ `void HandleAddArrayElement(FString InPinPath);` — Add a new array element to the array referred to by the property path
- L189 _public prototype_ `void HandleClearArray(FString InPinPath);` — Clear the array referred to by the property path
- L192 _public prototype_ `void HandleRemoveArrayElement(FString InPinPath);` — Remove the array element referred to by the property path
- L195 _public prototype_ `void HandleInsertArrayElement(FString InPinPath);` — Insert a new array element after the element referred to by the property path
- L197 _public prototype_ `int32 GetInstructionIndex(bool bAsInput) const;`
- L198 _public prototype_ `bool IsExcludedFromPreview() const;`
- L200 _public prototype_ `const FRigVMTemplate* GetTemplate() const;`
- L202 _public prototype_ `void ClearErrorInfo();`
- L204 _public prototype_ `void AddErrorInfo(const EMessageSeverity::Type& InSeverity, const FString& InMessage);`
- L206 _public prototype_ `void SetErrorInfo(const EMessageSeverity::Type& InSeverity, const FString& InMessage);`
- L208 _public prototype_ `URigVMPin* FindModelPinFromGraphPin(const UEdGraphPin* InGraphPin) const;`
- L209 _public prototype_ `UEdGraphPin* FindGraphPinFromModelPin(const URigVMPin* InModelPin, bool bAsInput) const;`
- L210 _public prototype_ `UEdGraphPin* FindGraphPinFromCategory(const FString& InCategory, bool bAsInput) const;`
- L214 _public prototype_ `void SynchronizeGraphPinNameWithModelPin(const URigVMPin* InModelPin, bool bNotify = true);` — Synchronize the stored name/value/type on the graph pin with the value stored on the node. If the pin has sub-pins, the value update is done recursively.
- L215 _public prototype_ `void SynchronizeGraphPinValueWithModelPin(const URigVMPin* InModelPin);`
- L216 _public prototype_ `void SynchronizeGraphPinTypeWithModelPin(const URigVMPin* InModelPin);`
- L217 _public prototype_ `void SynchronizeGraphPinExpansionWithModelPin(const URigVMPin* InModelPin);`
- L219 _public prototype_ `void SyncGraphNodeTitleWithModelNodeTitle();`
- L220 _public prototype_ `void SyncGraphNodeNameWithModelNodeName(const URigVMNode* InModelNode);`
- L222 _public function_ `FNodeTitleDirtied& OnNodeTitleDirtied()`
- L223 _public function_ `FNodePinsChanged& OnNodePinsChanged()`
- L224 _public function_ `FNodePinExpansionChanged& OnNodePinExpansionChanged()`
- L225 _public function_ `FNodeBeginRemoval& OnNodeBeginRemoval()`
- L228 _public prototype_ `bool ModelPinsChanged(bool bForce = false);` — Called when there's a drastic change in the pins
- L231 _public prototype_ `bool ModelPinAdded(const URigVMPin* InModelPin);` — Called when a model pin is added after the node creation
- L234 _public prototype_ `bool ModelPinRemoved(const URigVMPin* InModelPin);` — Called when a model pin is being removed
- L237 _public prototype_ `bool DrawAsCompactNode() const;` — Returns true if this node is relying on the cast template
- L240 _public prototype_ `void SetModelNode(URigVMNode* InModelNode);` — Sets the node's content from an external client, used for preview nodes without a graph
- L243 _public function_ `const TArray<URigVMPin*>& GetInputPins() const` — Returns all input pins
- L246 _public function_ `const TArray<URigVMPin*>& GetExecutePins() const` — Returns all execute pins
- L249 _public prototype_ `bool IsFadedOut() const;` — Returns true if this Node should be faded out
- L252 _public prototype_ `float GetFadedOutState() const;` — Returns 1.0 if the node is 100% opaque, and 0.0 if the node isn't visible.
- L255 _public prototype_ `void OverrideFadeOutState(TOptional<float> InFadedOutState);` — Overrides the fade out state of this node
- L258 _public function_ `void ResetFadedOutState()` — Removes any user based fade out state
- L263 _protected prototype_ `void UpdatePinLists();` — Helper function for AllocateDefaultPins
- L264 _protected prototype_ `bool CreateGraphPinFromCategory(const FString& InCategory, EEdGraphPinDirection InDirection);`
- L265 _protected prototype_ `bool CreateGraphPinFromModelPin(const URigVMPin* InModelPin, EEdGraphPinDirection InDirection, UEdGraphPin* InParentPin = nullptr);`
- L266 _protected prototype_ `void RemoveGraphSubPins(UEdGraphPin *InParentPin, const TArray<UEdGraphPin*>& InPinsToKeep = TArray<UEdGraphPin*>());`
- L267 _protected prototype_ `bool ModelPinAdded_Internal(const URigVMPin* InModelPin);`
- L268 _protected prototype_ `bool ModelPinRemoved_Internal(const URigVMPin* InModelPin);`
- L269 _protected prototype_ `bool CategoryPinAdded_Internal(const FString& InCategory, EEdGraphPinDirection InDirection);`
- L270 _protected prototype_ `bool CategoryPinRemoved_Internal(const FString& InCategory);`
- L273 _protected prototype_ `void SetupPinDefaultsFromModel(UEdGraphPin* Pin, const URigVMPin* InModelPin = nullptr);` — Copies default values from underlying properties into pin defaults, for editing
- L276 _protected prototype_ `virtual void ReallocatePinsDuringReconstruction(const TArray<UEdGraphPin*>& OldPins);` — Recreate pins when we reconstruct this node
- L279 _protected prototype_ `virtual void RewireOldPinsToNewPins(TArray<UEdGraphPin*>& InOldPins, TArray<UEdGraphPin*>& InNewPins);` — Wire-up new pins given old pin wiring
- L282 _protected prototype_ `virtual void PostReconstructNode();` — Handle anything post-reconstruction
- L285 _protected prototype_ `void InvalidateNodeTitle() const;` — Something that could change our title has changed
- L288 _protected prototype_ `void InvalidateNodeColor();` — Something that could change our color has changed
- L291 _protected prototype_ `void DestroyPinList(TArray<UEdGraphPin*>& InPins);` — Destroy all pins in an array
- L294 _protected prototype_ `void SetColorFromModel(const FLinearColor& InColor);` — Sets the body + title color from a color provided by the model
- L296 _protected prototype_ `static FEdGraphPinType GetPinTypeForModelPin(const URigVMPin* InModelPin);`
- L297 _protected prototype_ `static FEdGraphPinType GetPinTypeForCategoryPin();`
- L299 _protected prototype_ `virtual void ConfigurePin(UEdGraphPin* EdGraphPin, const URigVMPin* ModelPin) const;`
- L302 _private function_ `int32 GetNodeTopologyVersion() const`
- L303 _private member_ `int32 NodeTopologyVersion;`
- L305 _private prototype_ `TArray<URigVMPin*>& PinListForPin(const URigVMPin* InModelPin);`
- L307 _private member_ `FLinearColor CachedTitleColor;`
- L308 _private member_ `FLinearColor CachedNodeColor;`
- L311 _private prototype_ `void UpdateVisualSettings();`
- L313 _private member_ `TOptional<bool> bIsHighlighted;`
- L314 _private member_ `TOptional<FLinearColor> ProfilingColor;`
- L315 _private member_ `TOptional<FLinearColor> HighlightingColor;`
- L316 _private member_ `TOptional<bool> bEnableProfiling;`
- L317 _private member_ `mutable TOptional<double> MicroSeconds;`
- L318 _private member_ `mutable TArray<double> MicroSecondsFrames;`
- L321 _private member_ `TArray<URigVMPin*> ExecutePins;`
- L322 _private member_ `TArray<URigVMPin*> InputOutputPins;`
- L323 _private member_ `TArray<URigVMPin*> InputPins;`
- L324 _private member_ `TArray<URigVMPin*> OutputPins;`
- L325 _private member_ `TArray<TSharedPtr<FRigVMExternalVariable>> ExternalVariables;`
- L326 _private member_ `TArray<UEdGraphPin*> LastEdGraphPins;`
- L328 _private member_ `mutable TMap<TWeakObjectPtr<URigVMPin>, FPinPair> CachedPins;`
- L329 _private member_ `TMap<FString, FPinPair> CachedCategoryPins;`
- L331 _private member_ `FNodeTitleDirtied NodeTitleDirtied;`
- L332 _private member_ `FNodePinsChanged NodePinsChanged;`
- L333 _private member_ `FNodePinExpansionChanged NodePinExpansionChanged;`
- L334 _private member_ `FNodeBeginRemoval NodeBeginRemoval;`
- L336 _private member_ `TSet<uint32> ErrorMessageHashes;`
- L338 _private member_ `mutable const FRigVMTemplate* CachedTemplate;`
- L339 _private member_ `mutable TOptional<bool> DrawAsCompactNodeCache;`
- L340 _private member_ `FSimpleDelegate RequestRenameDelegate;`
- L341 _private member_ `mutable bool bRenameIsPending;`
- L343 _private member_ `mutable TOptional<bool> bIsFadedOut;`
- L344 _private member_ `mutable TOptional<float> FadedOutOverride;`

#### struct `URigVMEdGraphNode::FPinPair`  
`struct FPinPair`  
_L94-104_
- L96 _public function_ `FPinPair() : InputPin(nullptr) , OutputPin(nullptr)`
- L100 _public member_ `UEdGraphPin* InputPin;`
- L101 _public member_ `UEdGraphPin* OutputPin;`
- L103 _public function_ `bool IsValid() const`

#### class `FRigVMGraphNodeNameValidator`  
`class FRigVMGraphNodeNameValidator : public INameValidatorInterface`  
_L355-368_
- inherits: `INameValidatorInterface`
- L358 _public prototype_ `FRigVMGraphNodeNameValidator(const URigVMController* InController);`
- L361 _public prototype_ `virtual EValidatorResult IsValid(const FString& Name, bool bOriginal) override;`
- L362 _public prototype_ `virtual EValidatorResult IsValid(const FName& Name, bool bOriginal) override;`
- L367 _private member_ `const URigVMController* Controller;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API RIGVMDEVELOPER_API`
- L89 _delegate_ `DECLARE_MULTICAST_DELEGATE(FNodeTitleDirtied);`
- L90 _delegate_ `DECLARE_MULTICAST_DELEGATE(FNodePinsChanged);`
- L91 _delegate_ `DECLARE_MULTICAST_DELEGATE(FNodePinExpansionChanged);`
- L92 _delegate_ `DECLARE_MULTICAST_DELEGATE(FNodeBeginRemoval);`

### `Plugins/Runtime/RigVM/Source/RigVMDeveloper/Public/EdGraph/RigVMEdGraphSchema.h` (Public)


#### struct `FRigVMSearchTags`  
`struct FRigVMSearchTags`  
_L24-54_
- desc: Const values for Find-in-Blueprints to tag searchable data
- L29 _public member_ `static const FText FiB_Name;` — Name tag
- L31 _public member_ `static const FText FiB_ClassName;` — Class Name tag
- L33 _public member_ `static const FText FiB_NodeGuid;` — NodeGuid tag
- L37 _public member_ `static const FText FiB_PinCategory;` — Pin Category tag
- L39 _public member_ `static const FText FiB_PinSubCategory;` — Pin Sub-Category tag
- L41 _public member_ `static const FText FiB_PinBinding;` — Pin Binding tag
- L43 _public member_ `static const FText FiB_ObjectClass;` — Pin object class tag
- L45 _public member_ `static const FText FiB_IsArray;` — Pin IsArray tag
- L47 _public member_ `static const FText FiB_Glyph;` — Glyph icon tag
- L49 _public member_ `static const FText FiB_GlyphStyleSet;` — Style set the glyph belongs to
- L51 _public member_ `static const FText FiB_GlyphColor;` — Glyph icon color tag

#### enum `ECanCreateConnectionResponse_Extended`  
`enum class ECanCreateConnectionResponse_Extended`  
_L57-64_
- desc: Extra operations that can be performed on pin connection
- L59 _public enumerator_ `None`
- L61 _public enumerator_ `BreakChildren`
- L63 _public enumerator_ `BreakParent`

#### struct `FRigVMPinConnectionResponse`  
`struct FRigVMPinConnectionResponse`  
_L67-82_
- desc: Struct used to extend the response to a connection request to include breaking parents/children
- L69 _public function_ `FRigVMPinConnectionResponse(const ECanCreateConnectionResponse InResponse, FText InMessage, ECanCreateConnectionResponse_Extended InExtendedResponse = ECanCreateConnectionResponse_Extended::None) : Response(InResponse, MoveTemp(InMessage)) , ExtendedResponse(InExtendedResponse)`
- L80 _public member_ `FPinConnectionResponse Response;`
- L81 _public member_ `ECanCreateConnectionResponse_Extended ExtendedResponse;`

#### class `FRigVMLocalVariableNameValidator`  
`class FRigVMLocalVariableNameValidator : public FStringSetNameValidator`  
_L86-96_
- inherits: `FStringSetNameValidator`
- desc: FRigVMLocalVariableNameValidator
- L90 _public prototype_ `FRigVMLocalVariableNameValidator(const FRigVMEditorAssetInterfacePtr Blueprint, const URigVMGraph* Graph, FName InExistingName = NAME_None);`
- L93 _public prototype_ `virtual EValidatorResult IsValid(const FString& Name, bool bOriginal) override;`
- L94 _public prototype_ `virtual EValidatorResult IsValid(const FName& Name, bool bOriginal) override;`

#### class `FRigVMNameValidator`  
`class FRigVMNameValidator : public FStringSetNameValidator`  
_L100-111_
- inherits: `FStringSetNameValidator`
- desc: FRigVMNameValidator
- L104 _public prototype_ `FRigVMNameValidator(const class UBlueprint* Blueprint, const UStruct* ValidationScope, FName InExistingName = NAME_None);`
- L105 _public prototype_ `FRigVMNameValidator(const FRigVMEditorAssetInterfacePtr Blueprint, const UStruct* ValidationScope, FName InExistingName = NAME_None);`
- L108 _public prototype_ `virtual EValidatorResult IsValid(const FString& Name, bool bOriginal) override;`
- L109 _public prototype_ `virtual EValidatorResult IsValid(const FName& Name, bool bOriginal) override;`

#### struct `FRigVMEdGraphSchemaAction_LocalVar`  
`struct FRigVMEdGraphSchemaAction_LocalVar : public FEdGraphSchemaAction_BlueprintVariableBase`  
_L114-153_
- reflection: `USTRUCT()`
- inherits: `FEdGraphSchemaAction_BlueprintVariableBase`
- L122 _public function_ `static FName StaticGetTypeId()` — Simple type info
- L127 _public function_ `virtual FName GetTypeId() const override`
- L129 _public function_ `FRigVMEdGraphSchemaAction_LocalVar() : FEdGraphSchemaAction_BlueprintVariableBase()`
- L133 _public function_ `FRigVMEdGraphSchemaAction_LocalVar(FText InNodeCategory, FText InMenuDesc, FText InToolTip, const int32 InGrouping, const int32 InSectionID) : FEdGraphSchemaAction_BlueprintVariableBase(MoveTemp(InNodeCategory), MoveTemp(InMenuDesc), MoveTemp(InToolTip), InGrouping, InSectionID)`
- L137 _public function_ `virtual bool IsA(const FName& InType) const override`
- L142 _public prototype_ `virtual FEdGraphPinType GetPinType() const override;`
- L144 _public prototype_ `virtual void ChangeVariableType(const FEdGraphPinType& NewPinType) override;`
- L146 _public prototype_ `virtual void RenameVariable(const FName& NewName) override;`
- L148 _public prototype_ `virtual bool IsValidName(const FName& NewName, FText& OutErrorMessage) const override;`
- L150 _public prototype_ `virtual void DeleteVariable() override;`
- L152 _public prototype_ `virtual bool IsVariableUsed() override;`

#### struct `FRigVMEdGraphSchemaAction_PromoteToVariable`  
`struct FRigVMEdGraphSchemaAction_PromoteToVariable : public FEdGraphSchemaAction`  
_L156-189_
- reflection: `USTRUCT()`
- inherits: `FEdGraphSchemaAction`
- L163 _public function_ `static FName StaticGetTypeId()` — Simple type info
- L168 _public function_ `virtual FName GetTypeId() const override`
- L170 _public function_ `FRigVMEdGraphSchemaAction_PromoteToVariable() : FEdGraphSchemaAction() , EdGraphPin(nullptr) , bLocalVariable(false)`
- L176 _public prototype_ `FRigVMEdGraphSchemaAction_PromoteToVariable(UEdGraphPin* InEdGraphPin, bool InLocalVariable);`
- L178 _public function_ `virtual bool IsA(const FName& InType) const override`
- L183 _public prototype_ `virtual UEdGraphNode* PerformAction(UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2f& Location, bool bSelectNewNode) override;`
- L187 _private member_ `UEdGraphPin* EdGraphPin;`
- L188 _private member_ `bool bLocalVariable;`

#### struct `FRigVMEdGraphSchemaAction_PromoteToExposedPin`  
`struct FRigVMEdGraphSchemaAction_PromoteToExposedPin : public FEdGraphSchemaAction`  
_L192-223_
- reflection: `USTRUCT()`
- inherits: `FEdGraphSchemaAction`
- L199 _public function_ `static FName StaticGetTypeId()` — Simple type info
- L204 _public function_ `virtual FName GetTypeId() const override`
- L206 _public function_ `FRigVMEdGraphSchemaAction_PromoteToExposedPin() : FEdGraphSchemaAction() , EdGraphPin(nullptr)`
- L211 _public prototype_ `FRigVMEdGraphSchemaAction_PromoteToExposedPin(UEdGraphPin* InEdGraphPin);`
- L213 _public function_ `virtual bool IsA(const FName& InType) const override`
- L218 _public prototype_ `virtual UEdGraphNode* PerformAction(UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2f& Location, bool bSelectNewNode) override;`
- L222 _private member_ `UEdGraphPin* EdGraphPin;`

#### struct `FRigVMEdGraphSchemaAction_Event`  
`struct FRigVMEdGraphSchemaAction_Event : public FEdGraphSchemaAction`  
_L226-258_
- reflection: `USTRUCT()`
- inherits: `FEdGraphSchemaAction`
- L233 _public function_ `static FName StaticGetTypeId()` — Simple type info
- L238 _public function_ `virtual FName GetTypeId() const override`
- L240 _public function_ `FRigVMEdGraphSchemaAction_Event() : FEdGraphSchemaAction()`
- L244 _public prototype_ `FRigVMEdGraphSchemaAction_Event(const FName& InEventName, const FString& InNodePath, const FText& InNodeCategory);`
- L246 _public function_ `virtual bool IsA(const FName& InType) const override`
- L250 _public function_ `virtual bool IsParentable() const override`
- L251 _public prototype_ `virtual FReply OnDoubleClick(UBlueprint* InBlueprint) override;`
- L252 _public function_ `virtual bool CanBeRenamed() const override`
- L253 _public prototype_ `virtual FSlateBrush const* GetPaletteIcon() const override;`
- L257 _private member_ `FString NodePath;`

#### class `FRigVMFunctionDragDropAction`  
`class FRigVMFunctionDragDropAction : public FGraphSchemaActionDragDropAction`  
_L261-296_
- inherits: `FGraphSchemaActionDragDropAction`
- desc: DragDropAction class for drag and dropping an item from the My Blueprints tree (e.g., variable or function)
- L265 _public prototype_ `DRAG_DROP_OPERATOR_TYPE(FRigVMFunctionDragDropAction, FGraphSchemaActionDragDropAction)`
- L269 _public prototype_ `virtual FReply DroppedOnPin(const FVector2f& ScreenPosition, const FVector2f& GraphPosition) override;`
- L270 _public prototype_ `virtual FReply DroppedOnAction(TSharedRef<FEdGraphSchemaAction> Action) override;`
- L271 _public prototype_ `virtual FReply DroppedOnCategory(FText Category) override;`
- L272 _public prototype_ `virtual void HoverTargetChanged() override;`
- L276 _public function_ `void SetAltDrag(bool InIsAltDrag)` — Set if operation is modified by alt
- L279 _public function_ `void SetCtrlDrag(bool InIsCtrlDrag)` — Set if operation is modified by the ctrl key
- L284 _protected prototype_ `FRigVMFunctionDragDropAction();` — Constructor
- L286 _protected prototype_ `static TSharedRef<FRigVMFunctionDragDropAction> New(TSharedPtr<FEdGraphSchemaAction> InAction, FRigVMEditorAssetInterfacePtr InRigBlueprint, URigVMEdGraph* InRigGraph);`
- L290 _protected member_ `TScriptInterface<IRigVMEditorAssetInterface> SourceRigBlueprint;`
- L291 _protected member_ `URigVMEdGraph* SourceRigGraph;`
- L292 _protected member_ `bool bControlDrag;`
- L293 _protected member_ `bool bAltDrag;`

#### class `URigVMEdGraphSchema`  
`class URigVMEdGraphSchema : public UEdGraphSchema`  
_L299-423_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UEdGraphSchema`
- L305 _public member_ `static inline const FLazyName GraphName_RigVM = FLazyName(TEXT("RigV` — Name constants
- L308 _public prototype_ `URigVMEdGraphSchema();`
- L310 _public function_ `virtual const FLazyName& GetRootGraphName() const`
- L313 _public prototype_ `virtual void GetGraphContextActions(FGraphContextMenuBuilder& ContextMenuBuilder) const override;` — UEdGraphSchema interface
- L314 _public prototype_ `virtual void GetContextMenuActions(class UToolMenu* Menu, class UGraphNodeContextMenuContext* Context) const override;`
- L315 _public prototype_ `virtual bool TryCreateConnection(UEdGraphPin* PinA, UEdGraphPin* PinB) const override;`
- L316 _public prototype_ `virtual const FPinConnectionResponse CanCreateConnection(const UEdGraphPin* A, const UEdGraphPin* B) const override;`
- L317 _public prototype_ `virtual FLinearColor GetPinTypeColor(const FEdGraphPinType& PinType) const override;`
- L318 _public prototype_ `virtual bool SupportsPinType(TWeakPtr<const FEdGraphSchemaAction> SchemaAction, const FEdGraphPinType& PinType) const override;`
- L319 _public prototype_ `virtual bool SupportsPinTypeContainer(TWeakPtr<const FEdGraphSchemaAction> SchemaAction, const FEdGraphPinType& PinType, const EPinContainerType& ContainerType) const override;`
- L320 _public prototype_ `virtual void BreakPinLinks(UEdGraphPin& TargetPin, bool bSendsNodeNotifcation) const override;`
- L321 _public prototype_ `virtual void BreakSinglePinLink(UEdGraphPin* SourcePin, UEdGraphPin* TargetPin) const override;`
- L322 _public prototype_ `virtual bool CanGraphBeDropped(TSharedPtr<FEdGraphSchemaAction> InAction) const override;`
- L323 _public prototype_ `virtual FString GetFindReferenceSearchTerm(const FEdGraphSchemaAction* InGraphAction) const override;`
- L324 _public prototype_ `virtual FReply BeginGraphDragAction(TSharedPtr<FEdGraphSchemaAction> InAction, const FPointerEvent& MouseEvent = FPointerEvent() ) const override;`
- L325 _public prototype_ `virtual class FConnectionDrawingPolicy* CreateConnectionDrawingPolicy(int32 InBackLayerID, int32 InFrontLayerID, float InZoomFactor, const FSlateRect& InClippingRect, class FSlateWindowElementList& InDrawElements, class UEdGraph* InGraphObj) const override;`
- L326 _public prototype_ `virtual bool ShouldHidePinDefaultValue(UEdGraphPin* Pin) const override;`
- L327 _public prototype_ `virtual void TrySetDefaultValue(UEdGraphPin& InPin, const FString& InNewDefaultValue, bool bMarkAsModified = true) const override;`
- L328 _public prototype_ `virtual void TrySetDefaultObject(UEdGraphPin& InPin, UObject* InNewDefaultObject, bool bMarkAsModified) const override;`
- L329 _public prototype_ `virtual void TrySetDefaultText(UEdGraphPin& InPin, const FText& InNewDefaultText, bool bMarkAsModified) const override;`
- L330 _public function_ `virtual bool ShouldAlwaysPurgeOnModification() const override`
- L331 _public prototype_ `virtual bool ArePinsCompatible(const UEdGraphPin* PinA, const UEdGraphPin* PinB, const UClass* CallingContext, bool bIgnoreArray ) const override;`
- L332 _public function_ `virtual bool DoesSupportPinWatching() const override`
- L333 _public prototype_ `virtual bool IsPinBeingWatched(UEdGraphPin const* Pin) const override;`
- L334 _public prototype_ `virtual void ClearPinWatch(UEdGraphPin const* Pin) const override;`
- L335 _public prototype_ `virtual void OnPinConnectionDoubleCicked(UEdGraphPin* PinA, UEdGraphPin* PinB, const FVector2f& GraphPosition) const override;`
- L336 _public prototype_ `virtual bool MarkBlueprintDirtyFromNewNode(UBlueprint* InBlueprint, UEdGraphNode* InEdGraphNode) const override;`
- L337 _public prototype_ `virtual bool SafeDeleteNodeFromGraph(UEdGraph* Graph, UEdGraphNode* Node) const override;`
- L338 _public prototype_ `virtual bool CanVariableBeDropped(UEdGraph* InGraph, FProperty* InVariableToDrop) const override;`
- L339 _public prototype_ `virtual bool RequestFunctionDropOnPanel(UEdGraph* InGraph, const FRigVMGraphFunctionIdentifier& InFunction, const FVector2D& InDropPosition, const FVector2D& InScreenPosition) const;`
- L340 _public prototype_ `virtual bool RequestVariableDropOnPanel(UEdGraph* InGraph, FProperty* InVariableToDrop, const FVector2f& InDropPosition, const FVector2f& InScreenPosition) const override;`
- L341 _public prototype_ `virtual bool RequestVariableDropOnPin(UEdGraph* InGraph, FProperty* InVariableToDrop, UEdGraphPin* InPin, const FVector2f& InDropPosition, const FVector2f& InScreenPosition) const override;`
- L343 _public prototype_ `virtual bool RequestVariableDropOnPin(UEdGraph* InGraph, const FRigVMExternalVariable& InVariableToDrop, UEdGraphPin* InPin, const FVector2D& InDropPosition, const FVector2D& InScreenPosition) const;`
- L344 _public prototype_ `virtual bool IsStructEditable(UStruct* InStruct) const;`
- L345 _public prototype_ `virtual void SetNodePosition(UEdGraphNode* Node, const FVector2f& Position) const override;`
- L347 _public prototype_ `void SetNodePosition(UEdGraphNode* Node, const FVector2D& Position, bool bSetupUndo) const;`
- L348 _public prototype_ `virtual void GetGraphDisplayInformation(const UEdGraph& Graph, FGraphDisplayInfo& DisplayInfo) const override;`
- L349 _public prototype_ `virtual bool GetLocalVariables(const UEdGraph* InGraph, TArray<FBPVariableDescription>& OutLocalVariables) const override;`
- L350 _public prototype_ `virtual TSharedPtr<FEdGraphSchemaAction> MakeActionFromVariableDescription(const UEdGraph* InEdGraph, const FBPVariableDescription& Variable) const override;`
- L351 _public prototype_ `virtual FText GetGraphCategory(const UEdGraph* InGraph) const override;`
- L352 _public prototype_ `virtual EGraphType GetGraphType(const UEdGraph* TestEdGraph) const override;`
- L353 _public prototype_ `virtual FReply TrySetGraphCategory(const UEdGraph* InGraph, const FText& InCategory) const override;`
- L354 _public prototype_ `virtual bool TryDeleteGraph(UEdGraph* GraphToDelete) const override;`
- L355 _public prototype_ `virtual bool TryRenameGraph(UEdGraph* GraphToRename, const FName& InNewName) const override;`
- L356 _public prototype_ `virtual bool TryToGetChildEvents(const UEdGraph* Graph, const int32 SectionId, TArray<TSharedPtr<FEdGraphSchemaAction>>& Actions, const FText& ParentCategory) const override;`
- L357 _public function_ `virtual bool CanDuplicateGraph(UEdGraph* InSourceGraph) const`
- L358 _public function_ `virtual bool AllowsFunctionVariants() const override`
- L359 _public prototype_ `virtual UEdGraphPin* DropPinOnNode(UEdGraphNode* InTargetNode, const FName& InSourcePinName, const FEdGraphPinType& InSourcePinType, EEdGraphPinDirection InSourcePinDirection) const override;`
- L360 _public prototype_ `virtual bool SupportsDropPinOnNode(UEdGraphNode* InTargetNode, const FEdGraphPinType& InSourcePinType, EEdGraphPinDirection InSourcePinDirection, FText& OutErrorMessage) const override;`
- L361 _public function_ `virtual void SetPinBeingDroppedOnNode(UEdGraphPin* InSourcePin) const override`
- L362 _public prototype_ `virtual void InsertAdditionalActions(TArray<UBlueprint*> InBlueprints, TArray<UEdGraph*> InGraphs, TArray<UEdGraphPin*> InPins, FGraphActionListBuilderBase& OutAllActions) const override;`
- L363 _public prototype_ `virtual void InsertAdditionalActions(TArray<FRigVMEditorAssetInterfacePtr> InAssets, TArray<UEdGraph*> InGraphs, TArray<UEdGraphPin*> InPins, FGraphActionListBuilderBase& OutAllActions) const;`
- L364 _public prototype_ `virtual TSharedPtr<INameValidatorInterface> GetNameValidator(const UBlueprint* BlueprintObj, const FName& OriginalName, const UStruct* ValidationScope, const FName& ActionTypeId) const override;`
- L365 _public prototype_ `virtual TSharedPtr<INameValidatorInterface> GetNameValidator(const FRigVMEditorAssetInterfacePtr Asset, const FName& OriginalName, const UStruct* ValidationScope) const;`
- L366 _public prototype_ `bool CanPromotePinToVariable(const UEdGraphPin& Pin, bool bCond) const;`
- L367 _public prototype_ `virtual bool SupportsPreviewFromHereOnNode(const UEdGraphNode* InNode) const;`
- L368 _public prototype_ `virtual bool AllowsFuzzyActionFiltering(const FEdGraphSchemaAction& InCurrentAction) const override;`
- L369 _public prototype_ `virtual float GetActionFilteredWeight(const FEdGraphSchemaAction& InCurrentAction, const TArray<FString>& InFilterTerms, const TArray<FString>& InSanitizedFilterTerms, const TArray<UEdGraphPin*>& DraggedFromPins) const override;`
- L372 _public prototype_ `bool SupportsPinType(const UScriptStruct* ScriptStruct) const;` — Returns true if the schema supports the script type
- L375 _public prototype_ `URigVMEdGraphNode* CreateGraphNode(URigVMEdGraph* InGraph, const FName& InPropertyName) const;` — Create a graph node for a rig
- L378 _public prototype_ `void RenameNode(URigVMEdGraphNode* Node, const FName& InNewNodeName) const;` — Helper function to rename a node
- L381 _public prototype_ `virtual void ResetPinDefaultsRecursive(UEdGraphPin* InPin) const;` — Helper function to recursively reset the pin defaults
- L384 _public prototype_ `virtual void GetVariablePinTypes(TArray<FEdGraphPinType>& PinTypes) const;` — Returns all of the applicable pin types for variables within a rigvm host
- L386 _public prototype_ `void StartGraphNodeInteraction(UEdGraphNode* InNode) const;`
- L387 _public prototype_ `void EndGraphNodeInteraction(UEdGraphNode* InNode) const;`
- L388 _public prototype_ `static TArray<UEdGraphNode*> GetNodesToMoveForNode(UEdGraphNode* InNode);`
- L389 _public prototype_ `FVector2D GetNodePositionAtStartOfInteraction(const UEdGraphNode* InNode) const;`
- L391 _public prototype_ `bool AutowireNewNode(URigVMEdGraphNode* NewNode, UEdGraphPin* FromPin) const;`
- L393 _public prototype_ `void HandleModifiedEvent(ERigVMGraphNotifType InNotifType, URigVMGraph* InGraph, UObject* InSubject);`
- L396 _public prototype_ `virtual TSubclassOf<URigVMEdGraphNode> GetGraphNodeClass(const URigVMEdGraph* InGraph) const;` — Allow derived classes to spawn derived node classes
- L398 _public prototype_ `virtual bool IsRigVMDefaultEvent(const FName& InEventName) const;`
- L401 _public prototype_ `virtual bool ShouldHidePinOnNode(const URigVMPin* InModelPin) const;` — Allows to hide an input variable pin from node node
- L405 _protected member_ `mutable UClass* EditorSettingsClass;`
- L410 _private member_ `const UEdGraphPin* LastPinForCompatibleCheck = nullptr;`
- L411 _private member_ `bool bLastPinWasInput;`
- L412 _private member_ `mutable UEdGraphPin* PinBeingDropped = nullptr;`
- L415 _private member_ `mutable TArray<UEdGraphNode*> NodesBeingInteracted;`
- L416 _private member_ `mutable TMap<FName, FVector2D> NodePositionsDuringStart;`

#### Free symbols / members of external scopes

- L16 _macro_ `#define UE_API RIGVMDEVELOPER_API`
- L75 _function_ `friend bool operator==(const FRigVMPinConnectionResponse& A, const FRigVMPinConnectionResponse& B)`

### `Plugins/Runtime/RigVM/Source/RigVMDeveloper/Public/RigVMBlueprintCompiler.h` (Public)


#### class `FRigVMBlueprintCompiler`  
`class FRigVMBlueprintCompiler : public IBlueprintCompiler`  
_L13-19_
- inherits: `IBlueprintCompiler`
- L17 _public function_ `virtual bool CanCompile(const UBlueprint* Blueprint) override` — IBlueprintCompiler interface
- L18 _public prototype_ `virtual void Compile(UBlueprint* Blueprint, const FKismetCompilerOptions& CompileOptions, FCompilerResultsLog& Results) override;`

#### class `FRigVMBlueprintCompilerContext`  
`class FRigVMBlueprintCompilerContext : public FKismetCompilerContext`  
_L21-57_
- inherits: `FKismetCompilerContext`
- L24 _public function_ `FRigVMBlueprintCompilerContext(UBlueprint* SourceSketch, FCompilerResultsLog& InMessageLog, const FKismetCompilerOptions& InCompilerOptions) : FKismetCompilerContext(SourceSketch, InMessageLog, InCompilerOptions) , NewRigVMBlueprintGeneratedClass(nullptr)`
- L31 _public function_ `virtual void ValidateLink(const UEdGraphPin* PinA, const UEdGraphPin* PinB) const override` — FKismetCompilerContext interface
- L32 _public function_ `virtual void ValidatePin(const UEdGraphPin* Pin) const override`
- L33 _public function_ `virtual void ValidateNode(const UEdGraphNode* Node) const override`
- L34 _public function_ `virtual bool CanIgnoreNode(const UEdGraphNode* Node) const override`
- L35 _public function_ `virtual bool ShouldForceKeepNode(const UEdGraphNode* Node) const override`
- L36 _public function_ `virtual void PrecompileFunction(FKismetFunctionContext& Context, EInternalCompilerFlags InternalFlags) override`
- L37 _public prototype_ `virtual void OnPostCDOCompiled(const UObject::FPostCDOCompiledContext& Context) override;`
- L38 _public prototype_ `virtual void CopyTermDefaultsToDefaultObject(UObject* DefaultObject) override;`
- L39 _public prototype_ `virtual void EnsureProperGeneratedClass(UClass*& TargetUClass) override;`
- L40 _public prototype_ `virtual void SpawnNewClass(const FString& NewClassName) override;`
- L41 _public prototype_ `virtual void OnNewClassSet(UBlueprintGeneratedClass* ClassToUse) override;`
- L42 _public function_ `virtual void PruneIsolatedNodes(const TArray<UEdGraphNode*>& RootSet, TArray<UEdGraphNode*>& GraphNodes) override`
- L43 _public prototype_ `virtual void CleanAndSanitizeClass(UBlueprintGeneratedClass* ClassToClean, UObject*& InOldCDO) override;`
- L44 _public function_ `virtual void MergeUbergraphPagesIn(UEdGraph* Ubergraph) override`
- L45 _public prototype_ `virtual void PreCompileUpdateBlueprintOnLoad(UBlueprint* BP) override;`
- L46 _public function_ `virtual void CreateFunctionList() override`
- L47 _public function_ `virtual void ProcessOneFunctionGraph(UEdGraph* SourceGraph, bool bInternalFunction = false) override`
- L52 _private prototype_ `void MarkCompilationFailed(const FString& Message);` — used to fail a compilation and mark the blueprint in error
- L56 _protected member_ `URigVMBlueprintGeneratedClass* NewRigVMBlueprintGeneratedClass;` — the new class we are generating

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API RIGVMDEVELOPER_API`

### `Plugins/Runtime/RigVM/Source/RigVMDeveloper/Public/RigVMBlueprintLegacy.h` (Public)


#### struct `FRigVMOldPublicFunctionArg`  
`struct FRigVMOldPublicFunctionArg`  
_L32-60_
- reflection: `USTRUCT(meta = (Deprecated = "5.2"))`
- L36 _public function_ `FRigVMOldPublicFunctionArg() : Name(NAME_None) , CPPType(NAME_None) , CPPTypeObjectPath(NAME_None) , bIsArray(false) , Direction(ERigVMPinDirection::Input)`
- L45 _public member_ `FName Name;` — `UPROPERTY()`
- L48 _public member_ `FName CPPType;` — `UPROPERTY()`
- L51 _public member_ `FName CPPTypeObjectPath;` — `UPROPERTY()`
- L54 _public member_ `bool bIsArray;` — `UPROPERTY()`
- L57 _public member_ `ERigVMPinDirection Direction;` — `UPROPERTY()`
- L59 _public prototype_ `FEdGraphPinType GetPinType() const;`

#### struct `FRigVMOldPublicFunctionData`  
`struct FRigVMOldPublicFunctionData`  
_L63-92_
- reflection: `USTRUCT(meta = (Deprecated = "5.2"))`
- L67 _public function_ `FRigVMOldPublicFunctionData() :Name(NAME_None)`
- L71 _public prototype_ `virtual ~FRigVMOldPublicFunctionData();`
- L74 _public member_ `FName Name;` — `UPROPERTY()`
- L77 _public member_ `FString DisplayName;` — `UPROPERTY()`
- L80 _public member_ `FString Category;` — `UPROPERTY()`
- L83 _public member_ `FString Keywords;` — `UPROPERTY()`
- L86 _public member_ `FRigVMOldPublicFunctionArg ReturnValue;` — `UPROPERTY()`
- L89 _public member_ `TArray<FRigVMOldPublicFunctionArg> Arguments;` — `UPROPERTY()`
- L91 _public prototype_ `bool IsMutable() const;`

#### class `URigVMBlueprint`  
`class URigVMBlueprint : public UBlueprint, public IRigVMEditorAssetInterface, public IRigVMClientHost, public IRigVMExternalDependencyManager`  
_L95-531_
- reflection: `UCLASS(MinimalAPI, BlueprintType, meta=(IgnoreClassThumbnail))`
- inherits: `UBlueprint,IRigVMEditorAssetInterface,IRigVMClientHost,IRigVMExternalDependencyManager`
- L100 _public function_ `virtual TScriptInterface<IRigVMRuntimeAssetInterface> GetRuntimeAssetInterface() const override`
- L101 _public function_ `virtual UClass* GetRuntimeAssetClass() const override`
- L102 _public function_ `virtual UObject* GetAssetObjectForEditor() override`
- L103 _public prototype_ `virtual void BeginDestroy() override;`
- L104 _public function_ `virtual UObject* GetObject() override`
- L105 _public function_ `virtual const TArray<FRigVMGraphFunctionHeader>& GetPublicGraphFunctions() const override`
- L106 _public function_ `virtual void SetPublicGraphFunctions(const TArray<FRigVMGraphFunctionHeader>& InHeaders) override`
- L107 _public function_ `virtual FRigVMClient* GetRigVMClient() override`
- L108 _public function_ `virtual const FRigVMClient* GetRigVMClient() const override`
- L109 _public function_ `virtual FRigVMVariant& GetAssetVariant() override`
- L110 _public function_ `virtual const FRigVMVariant& GetAssetVariant() const override`
- L111 _public function_ `virtual FRigVMCompileSettings& GetVMCompileSettings() override`
- L112 _public function_ `virtual FRigVMRuntimeSettings& GetVMRuntimeSettings() override`
- L113 _public function_ `virtual bool IsRegeneratingOnLoad() const override`
- L114 _public prototype_ `virtual TArray<FRigVMGraphVariableDescription> GetAssetVariables() const override;`
- L115 _public function_ `virtual TArray<struct FEditedDocumentInfo>& GetLastEditedDocuments() override`
- L116 _public prototype_ `virtual const TArray<FString>& GetRequiredPlugins(bool bRefresh = true) const override;`
- L117 _public function_ `virtual FRigVMEdGraphDisplaySettings& GetRigGraphDisplaySettings() override`
- L120 _public prototype_ `static void AppendToClassSchema(FAppendToClassSchemaContext& Context);`
- L124 _public prototype_ `static bool CopyBlueprintToAsset(URigVMBlueprint* InBlueprint, URigVMRuntimeAsset* InAsset);`
- L128 _protected function_ `virtual UClass* GetRigVMGeneratedClass() const`
- L129 _protected prototype_ `virtual TArray<FRigVMExternalVariable> GetExternalVariables(bool bFallbackToBlueprint) const override;`
- L130 _protected function_ `virtual const UStruct* GetVariablesStruct() override`
- L131 _protected function_ `virtual uint8* GetVariablesMemory() override`
- L132 _protected prototype_ `virtual FString GetVariableDefaultValue(const FName& InName, bool bFromDebuggedObject) const override;`
- L133 _protected prototype_ `virtual URigVM* GetVM(bool bCreateIfNeeded = true) const override;`
- L134 _protected prototype_ `virtual FRigVMExtendedExecuteContext* GetRigVMExtendedExecuteContext() override;`
- L135 _protected function_ `virtual TScriptInterface<IRigVMGraphFunctionHost> GetRigVMGraphFunctionHost() override`
- L136 _protected function_ `virtual TScriptInterface<const IRigVMGraphFunctionHost> GetRigVMGraphFunctionHost() const override`
- L137 _protected function_ `virtual FCompilerResultsLog* GetCurrentMessageLog() const override`
- L138 _protected prototype_ `virtual void SetAssetStatus(const ERigVMAssetStatus& InStatus) override;`
- L139 _protected prototype_ `virtual ERigVMAssetStatus GetAssetStatus() const override;`
- L140 _protected function_ `virtual bool IsUpToDate() const override`
- L141 _protected prototype_ `virtual TArray<UObject*> GetArchetypeInstances(bool bIncludeCDO, bool bIncludeDerivedClasses) const override;`
- L142 _protected function_ `virtual const FString& GetObjectBeingDebuggedPath() const override`
- L143 _protected function_ `virtual UWorld* GetWorldBeingDebugged() const override`
- L144 _protected function_ `virtual void SetWorldBeingDebugged(UWorld* NewWorld) override`
- L145 _protected prototype_ `virtual FRigVMDebugInfo& GetDebugInfo() override;`
- L146 _protected function_ `virtual TObjectPtr<URigVMEdGraph>& GetFunctionLibraryEdGraph() override`
- L147 _protected prototype_ `virtual URigVMHost* CreateRigVMHostSuper(UObject* InOuter, FName InName = NAME_None, EObjectFlags InFlags = RF_NoFlags) override;`
- L148 _protected prototype_ `virtual void MarkAssetAsStructurallyModified(bool bSkipDirtyAssetStatus = false) override;`
- L149 _protected prototype_ `virtual void MarkAssetAsModified(FPropertyChangedEvent PropertyChangedEvent = FPropertyChangedEvent(nullptr)) override;`
- L150 _protected prototype_ `virtual void AddUbergraphPage(URigVMEdGraph* RigVMEdGraph) override;`
- L151 _protected prototype_ `virtual void AddLastEditedDocument(URigVMEdGraph* RigVMEdGraph) override;`
- L152 _protected prototype_ `virtual void Compile() override;`
- L153 _protected prototype_ `virtual FCompilerResultsLog CompileBlueprint() override;`
- L154 _protected prototype_ `virtual void PatchVariableNodesOnLoad() override;`
- L155 _protected prototype_ `virtual void AddPinWatch(UEdGraphPin* InPin) override;`
- L156 _protected prototype_ `virtual void RemovePinWatch(UEdGraphPin* InPin) override;`
- L157 _protected prototype_ `virtual void ClearPinWatches() override;`
- L158 _protected prototype_ `virtual bool IsPinBeingWatched(const UEdGraphPin* InPin) const override;`
- L159 _protected prototype_ `virtual bool NodeContainsWatchedPins(const UEdGraphNode* InNode) const override;`
- L160 _protected prototype_ `virtual void ForeachPinWatch(TFunctionRef<void(UEdGraphPin*)> Task) override;`
- L161 _protected prototype_ `virtual TMap<FString, FSoftObjectPath>& GetUserDefinedStructGuidToPathName(bool bFromCDO) override;`
- L162 _protected prototype_ `virtual TMap<FString, FSoftObjectPath>& GetUserDefinedEnumToPathName(bool bFromCDO) override;`
- L163 _protected prototype_ `virtual TSet<TObjectPtr<UObject>>& GetUserDefinedTypesInUse(bool bFromCDO) override;`
- L164 _protected function_ `virtual TArray<TObjectPtr<UEdGraph>>& GetFunctionGraphs() override`
- L165 _protected function_ `virtual bool& IsReferencedObjectPathsStored() override`
- L166 _protected function_ `virtual TArray<FSoftObjectPath>& GetReferencedObjectPaths() override`
- L167 _protected function_ `virtual TArray<FName>& GetSupportedEventNames() override`
- L168 _protected prototype_ `virtual void UpdateSupportedEventNames() override;`
- L169 _protected function_ `virtual TArray<FRigVMReferenceNodeData>& GetFunctionReferenceNodeData() override`
- L170 _protected function_ `virtual void NotifyGraphRenamedSuper(class UEdGraph* Graph, FName OldName, FName NewName) override`
- L171 _protected prototype_ `virtual UObject* GetDefaultsObject() override;`
- L172 _protected prototype_ `virtual void PostEditChangeBlueprintActors() override;`
- L175 _public prototype_ `URigVMBlueprint();`
- L178 _public prototype_ `URigVMBlueprintGeneratedClass* GetRigVMBlueprintGeneratedClass() const;` — Get the (full) generated class for this rigvm blueprint
- L180 _public function_ `virtual UClass* GetRigVMGeneratedClassPrototype() const` — Returns the class used as the super class for all generated classes
- L182 _public function_ `virtual void Serialize(FArchive& Ar) override`
- L183 _public function_ `virtual void SerializeSuper(FArchive& Ar) override`
- L184 _public prototype_ `virtual void PostSerialize(FArchive& Ar) override;`
- L189 _public prototype_ `virtual UClass* GetBlueprintClass() const override;` — UBlueprint interface
- L190 _public prototype_ `virtual UClass* RegenerateClass(UClass* ClassToRegenerate, UObject* PreviousCDO) override;`
- L191 _public function_ `virtual bool SupportedByDefaultBlueprintFactory() const override`
- L192 _public function_ `virtual bool IsValidForBytecodeOnlyRecompile() const override`
- L193 _public function_ `virtual void LoadModulesRequiredForCompilation() override`
- L194 _public prototype_ `virtual void GetTypeActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;`
- L195 _public prototype_ `virtual void GetInstanceActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;`
- L196 _public function_ `virtual void SetObjectBeingDebugged(UObject* NewObject) override`
- L197 _public function_ `virtual void SetObjectBeingDebuggedSuper(UObject* NewObject) override`
- L198 _public prototype_ `virtual UObject* GetObjectBeingDebugged(bool bEvenIfPendingKill = false) override;`
- L199 _public function_ `virtual UObject* GetObjectBeingDebugged(bool bEvenIfPendingKill = false) const override`
- L200 _public prototype_ `virtual void PreSave(FObjectPreSaveContext ObjectSaveContext) override;`
- L201 _public prototype_ `virtual void PostLoad() override;`
- L203 _public prototype_ `static void DeclareConstructClasses(TArray<FTopLevelAssetPath>& OutConstructClasses, const UClass* SpecificSubclass);`
- L205 _public function_ `virtual bool IsPostLoadThreadSafe() const override`
- L206 _public function_ `virtual void PostTransacted(const FTransactionObjectEvent& TransactionEvent) override`
- L207 _public function_ `virtual void PostTransactedSuper(const FTransactionObjectEvent& TransactionEvent) override`
- L208 _public function_ `virtual void ReplaceDeprecatedNodes() override`
- L209 _public function_ `virtual void ReplaceDeprecatedNodesSuper() override`
- L210 _public function_ `virtual void PreDuplicate(FObjectDuplicationParameters& DupParams) override`
- L211 _public function_ `virtual void PreDuplicateSuper(FObjectDuplicationParameters& DupParams) override`
- L212 _public function_ `virtual void PostDuplicate(bool bDuplicateForPIE) override`
- L213 _public function_ `virtual void PostDuplicateSuper(bool bDuplicateForPIE) override`
- L214 _public function_ `virtual void GetAssetRegistryTags(FAssetRegistryTagsContext Context) const override`
- L215 _public function_ `virtual void GetAssetRegistryTagsSuper(FAssetRegistryTagsContext Context) const override`
- L216 _public function_ `virtual bool SupportsGlobalVariables() const override`
- L217 _public function_ `virtual bool SupportsLocalVariables() const override`
- L218 _public function_ `virtual bool SupportsFunctions() const override`
- L219 _public function_ `virtual bool SupportsMacros() const override`
- L220 _public function_ `virtual bool SupportsDelegates() const override`
- L221 _public function_ `virtual bool SupportsEventGraphs() const override`
- L222 _public function_ `virtual bool SupportsAnimLayers() const override`
- L223 _public function_ `virtual bool ExportGraphToText(UEdGraph* InEdGraph, FString& OutText) override`
- L224 _public function_ `virtual bool TryImportGraphFromText(const FString& InClipboardText, UEdGraph** OutGraphPtr = nullptr) override`
- L225 _public function_ `virtual bool CanImportGraphFromText(const FString& InClipboardText) override`
- L226 _public function_ `virtual bool RequiresForceLoadMembers(UObject* InObject) const override`
- L227 _public function_ `virtual bool RequiresForceLoadMembersSuper(UObject* InObject) const override`
- L231 _public prototype_ `virtual void PostEditChangeChainProperty(struct FPropertyChangedChainEvent& PropertyChangedEvent) override;` — UObject interface
- L232 _public prototype_ `virtual void PostRename(UObject* OldOuter, const FName OldName) override;`
- L234 _public prototype_ `virtual void GetPreloadDependencies(TArray<UObject*>& OutDeps) override;` — Called during cooking. Must return all objects that will be Preload()ed when this is serialized at load time.
- L236 _public function_ `virtual TArray<TObjectPtr<UEdGraph>>& GetUberGraphs() override`
- L237 _public function_ `virtual void GetAllEdGraphs(TArray<UEdGraph*>& Graphs) const override`
- L238 _public function_ `virtual void SetUberGraphs(const TArray<TObjectPtr<UEdGraph>>& InGraphs) override`
- L239 _public prototype_ `virtual void PostSaveRoot(FObjectPostSaveRootContext ObjectSaveContext) override;`
- L242 _public function_ `virtual FString GetAssetName() const override` — --- IRigVMClientHost interface Start---
- L243 _public function_ `virtual UClass* GetRigVMSchemaClass() const override`
- L244 _public function_ `virtual UScriptStruct* GetRigVMExecuteContextStruct() const override`
- L245 _public function_ `virtual UClass* GetRigVMEdGraphClass() const override`
- L246 _public function_ `virtual UClass* GetRigVMEdGraphNodeClass() const override`
- L247 _public function_ `virtual UClass* GetRigVMEdGraphSchemaClass() const override`
- L248 _public function_ `virtual UClass* GetRigVMEditorSettingsClass() const override`
- L249 _public function_ `virtual UObject* GetEditorObjectForRigVMGraph(const URigVMGraph* InVMGraph) const override`
- L250 _public function_ `virtual URigVMGraph* GetRigVMGraphForEditorObject(UObject* InObject) const override`
- L251 _public function_ `virtual void HandleRigVMGraphAdded(const FRigVMClient* InClient, const FString& InNodePath) override`
- L252 _public function_ `virtual void HandleRigVMGraphRemoved(const FRigVMClient* InClient, const FString& InNodePath) override`
- L253 _public function_ `virtual void HandleRigVMGraphRenamed(const FRigVMClient* InClient, const FString& InOldNodePath, const FString& InNewNodePath) override`
- L254 _public function_ `virtual void HandleConfigureRigVMController(const FRigVMClient* InClient, URigVMController* InControllerToConfigure) override`
- L255 _public function_ `virtual void IncrementVMRecompileBracket() override`
- L256 _public function_ `virtual void DecrementVMRecompileBracket() override`
- L257 _public function_ `virtual void RefreshAllModels(ERigVMLoadType InLoadType = ERigVMLoadType::PostLoad) override`
- L258 _public function_ `virtual void OnRigVMRegistryChanged() override`
- L259 _public function_ `virtual URigVMGraph* GetModel(const FString& InNodePath) const override`
- L260 _public function_ `virtual FRigVMGetFocusedGraph& OnGetFocusedGraph() override`
- L261 _public function_ `virtual const FRigVMGetFocusedGraph& OnGetFocusedGraph() const override`
- L262 _public function_ `virtual void SetupPinRedirectorsForBackwardsCompatibility() override`
- L263 _public function_ `virtual FRigVMGraphModifiedEvent& OnModified() override`
- L264 _public function_ `virtual bool IsFunctionPublic(const FName& InFunctionName) const override`
- L265 _public function_ `virtual void MarkFunctionPublic(const FName& InFunctionName, bool bIsPublic = true) override`
- L266 _public function_ `virtual void RenameGraph(const FString& InNodePath, const FName& InNewName) override`
- L270 _public function_ `virtual void RecompileVM() override` — `UFUNCTION(BlueprintCallable, Category = "RigVM Blueprint")`
- L272 _public function_ `virtual void RecompileVMIfRequired() override` — `UFUNCTION(BlueprintCallable, Category = "RigVM Blueprint")`
- L274 _public function_ `virtual void RequestAutoVMRecompilation() override` — `UFUNCTION(BlueprintCallable, Category = "RigVM Blueprint")`
- L276 _public function_ `virtual void SetAutoVMRecompile(bool bAutoRecompile) override` — `UFUNCTION(BlueprintCallable, Category = "RigVM Blueprint")`
- L278 _public function_ `virtual bool GetAutoVMRecompile() const override` — `UFUNCTION(BlueprintPure, Category = "RigVM Blueprint")`
- L281 _public function_ `virtual void RequestRigVMInit() override` — `UFUNCTION(BlueprintCallable, Category = "RigVM Blueprint")`
- L284 _public function_ `virtual URigVMGraph* GetModel(const UEdGraph* InEdGraph = nullptr) const override` — `UFUNCTION(BlueprintCallable, Category = "RigVM Blueprint")`
- L287 _public function_ `virtual URigVMGraph* GetDefaultModel() const override` — `UFUNCTION(BlueprintCallable, Category = "RigVM Blueprint")`
- L290 _public function_ `virtual TArray<URigVMGraph*> GetAllModels() const override` — `UFUNCTION(BlueprintCallable, Category = "RigVM Blueprint")`
- L293 _public function_ `virtual URigVMFunctionLibrary* GetLocalFunctionLibrary() const override` — `UFUNCTION(BlueprintCallable, Category = "RigVM Blueprint")`
- L296 _public function_ `virtual URigVMFunctionLibrary* GetOrCreateLocalFunctionLibrary(bool bSetupUndoRedo = true) override` — `UFUNCTION(BlueprintCallable, Category = "RigVM Blueprint")`
- L299 _public function_ `virtual URigVMGraph* AddModel(FString InName = TEXT("Rig Graph"), bool bSetupUndoRedo = true, bool bPrintPythonCommand = true)` — `UFUNCTION(BlueprintCallable, Category = "RigVM Blueprint")`
- L302 _public function_ `virtual bool RemoveModel(FString InName = TEXT("Rig Graph"), bool bSetupUndoRedo = true, bool bPrintPythonCommand = true)` — `UFUNCTION(BlueprintCallable, Category = "RigVM Blueprint")`
- L306 _public function_ `virtual URigVMGraph* GetFocusedModel() const override` — `UFUNCTION(BlueprintCallable, Category = "RigVM Blueprint")`
- L309 _public function_ `virtual URigVMController* GetController(const URigVMGraph* InGraph = nullptr) const override` — `UFUNCTION(BlueprintCallable, Category = "RigVM Blueprint")`
- L310 _public function_ `virtual URigVMController* GetController(const UEdGraph* InGraph) const override`
- L313 _public function_ `virtual URigVMController* GetControllerByName(const FString InGraphName = TEXT("")) const override` — `UFUNCTION(BlueprintCallable, Category = "RigVM Blueprint")`
- L316 _public function_ `virtual URigVMController* GetOrCreateController(URigVMGraph* InGraph = nullptr) override` — `UFUNCTION(BlueprintCallable, Category = "RigVM Blueprint")`
- L317 _public function_ `virtual URigVMController* GetOrCreateController(const UEdGraph* InGraph) override`
- L320 _public function_ `virtual TArray<FString> GeneratePythonCommands(const FString InNewBlueprintName) override` — `UE_DEPRECATED(5.8, "Use TArray<FString> GeneratePythonCommands() instead.")`
- L323 _public function_ `virtual TArray<FString> GeneratePythonCommands() override` — `UFUNCTION(BlueprintCallable, Category = "RigVM Blueprint")`
- L324 _public prototype_ `virtual TArray<FString> GeneratePythonContextCommands(const FString InNewBlueprintName, bool bCreateAsset) override;`
- L327 _public function_ `virtual TArray<FRigVMExternalDependency> GetExternalDependenciesForCategory(const FName& InCategory) const override`
- L330 _public function_ `virtual bool ShouldBeMarkedDirtyUponTransaction() const override`
- L331 _public function_ `virtual FRigVMPropertyBag* GetVariablesPropertyBag() override`
- L333 _public function_ `virtual FRigVMDrawContainer& GetDrawContainer() override`
- L338 _public member_ `TObjectPtr<URigVMEdGraph> FunctionLibraryEdGraph;` — `UPROPERTY()`
- L343 _public member_ `FRigVMEdGraphDisplaySettings RigGraphDisplaySettings;` — `UPROPERTY(EditAnywhere, Category = "User Interface")`
- L346 _public member_ `FRigVMRuntimeSettings VMRuntimeSettings;` — `UPROPERTY(EditAnywhere, Category = "VM")`
- L349 _public member_ `FRigVMCompileSettings VMCompileSettings;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VM")`
- L352 _public member_ `FRigVMPythonSettings PythonLogSettings;` — `UPROPERTY(EditAnywhere, Category = "Python Log Settings")`
- L355 _public member_ `TMap<FString, FSoftObjectPath> UserDefinedStructGuidToPathName;` — `UPROPERTY()`
- L358 _public member_ `TMap<FString, FSoftObjectPath> UserDefinedEnumToPathName;` — `UPROPERTY()`
- L361 _public member_ `TSet<TObjectPtr<UObject>> UserDefinedTypesInUse;` — `UPROPERTY(transient)`
- L367 _protected member_ `TObjectPtr<URigVMGraph> Model_DEPRECATED;` — `UPROPERTY()`
- L370 _protected member_ `TObjectPtr<URigVMFunctionLibrary> FunctionLibrary_DEPRECATED;` — `UPROPERTY()`
- L374 _protected member_ `FRigVMClient RigVMClient;` — `UPROPERTY()`
- L379 _protected member_ `bool ReferencedObjectPathsStored;` — `UPROPERTY()`
- L382 _protected member_ `TArray<FSoftObjectPath> ReferencedObjectPaths;` — `UPROPERTY()`
- L388 _protected member_ `TArray<FRigVMGraphFunctionHeader> PublicGraphFunctions;` — `UPROPERTY(AssetRegistrySearchable)` — Asset searchable information about exposed public functions on this rig
- L392 _protected member_ `TArray<FRigVMReferenceNodeData> FunctionReferenceNodeData;` — `UPROPERTY(AssetRegistrySearchable)` — Asset searchable information function references in this rig
- L398 _protected member_ `FRigVMVariant AssetVariant;` — `UPROPERTY(EditAnywhere, AssetRegistrySearchable, Category = "Variant")` — Variant information about this asset
- L403 _protected member_ `TArray<FString> RequiredPlugins;` — `UPROPERTY(VisibleAnywhere, AssetRegistrySearchable, Category = "Dependencies")`
- L406 _protected member_ `FRigVMDrawContainer DrawContainer;` — `UPROPERTY(EditAnywhere, Category = "Drawing")`
- L411 _public function_ `virtual UClass* GetRigVMHostClass() const` — `UFUNCTION(BlueprintCallable, Category = "VM")`
- L414 _public function_ `virtual URigVMHost* CreateRigVMHost()` — `UFUNCTION(BlueprintCallable, Category = "VM")`
- L417 _public function_ `virtual URigVMHost* GetDebuggedRigVMHost()` — `UFUNCTION(BlueprintCallable, Category = "VM")`
- L420 _public function_ `virtual TArray<UStruct*> GetAvailableRigVMStructs() const override` — `UFUNCTION(BlueprintCallable, Category = "VM")`
- L424 _public function_ `virtual TArray<FRigVMGraphVariableDescription> GetMemberVariables() const` — `UFUNCTION(BlueprintCallable, Category = "Variables")`
- L427 _public prototype_ `virtual FName AddMemberVariable(const FName& InName, const FString& InCPPType, bool bIsPublic = false, bool bIsReadOnly = false, FString InDefaultValue = TEXT("")) override;` — `UFUNCTION(BlueprintCallable, Category = "Variables")`
- L430 _public prototype_ `virtual bool RemoveMemberVariable(const FName& InName) override;` — `UFUNCTION(BlueprintCallable, Category = "Variables")`
- L433 _public prototype_ `virtual bool BulkRemoveMemberVariables(const TArray<FName>& InNames) override;` — `UFUNCTION(BlueprintCallable, Category = "Variables")`
- L436 _public prototype_ `virtual bool RenameMemberVariable(const FName& InOldName, const FName& InNewName) override;` — `UFUNCTION(BlueprintCallable, Category = "Variables")`
- L439 _public prototype_ `virtual bool ChangeMemberVariableType(const FName& InName, const FString& InCPPType, bool bIsPublic = false, bool bIsReadOnly = false, FString InDefaultValue = TEXT("")) override;` — `UFUNCTION(BlueprintCallable, Category = "Variables")`
- L440 _public prototype_ `virtual bool ChangeMemberVariableType(const FName& InName, const FEdGraphPinType& InType) override;`
- L443 _public prototype_ `virtual bool SetVariableIndex(const FName& InName, int32 NewIndex) override;` — `UFUNCTION(BlueprintCallable, Category = "Variables")`
- L444 _public prototype_ `virtual bool SetVariableIndex(const FGuid& InVariableGuid, int32 NewIndex);`
- L447 _public function_ `virtual FRigVMVariant GetAssetVariantBP() const` — `UFUNCTION(BlueprintPure, Category = "Variants", meta = (DisplayName = "GetAssetVariant", ScriptName = "GetAssetVariant"))`
- L450 _public function_ `virtual FRigVMVariantRef GetAssetVariantRef() const override` — `UFUNCTION(BlueprintPure, Category = "Variants")`
- L454 _public function_ `virtual bool SplitAssetVariant() override` — `UFUNCTION(BlueprintCallable, Category = "Variants")` — Resets the asset's guid to a new one and splits it from the former variant set
- L458 _public function_ `virtual bool JoinAssetVariant(const FGuid& InGuid) override` — `UFUNCTION(BlueprintCallable, Category = "Variants")` — Merges the asset's guid with a provided one to join the variant set
- L461 _public function_ `virtual TArray<FRigVMVariantRef> GetMatchingVariants() const override` — `UFUNCTION(BlueprintPure, Category = "Variants")`
- L469 _private member_ `TArray<FName> SupportedEventNames;` — `UPROPERTY(AssetRegistrySearchable)` — The event names this rigvm blueprint contains
- L473 _private function_ `virtual void SuspendNotifications(bool bSuspendNotifs)` — `UFUNCTION(BlueprintCallable, Category = "RigVM Blueprint")`
- L482 _protected member_ `TObjectPtr<URigVMHost> EditorHost = nullptr;` — `UPROPERTY(transient)` — Declaring these transient properties here instead of the IRigVMEditorAssetInterface class in order to have them as UPROPERTY, to avoid having stale pointers when GC happens
- L483 _protected function_ `virtual TObjectPtr<URigVMHost>& GetEditorHost() override`
- L485 _protected prototype_ `static FName FindHostMemberVariableUniqueName(TSharedPtr<FKismetNameValidator> InNameValidator, const FString& InBaseName);`
- L486 _protected prototype_ `static int32 AddHostMemberVariable(URigVMBlueprint* InBlueprint, const FGuid InVarGuid, const FName& InVarName, FEdGraphPinType InVarType, bool bIsPublic, bool bIsReadOnly, FString InDefaultValue);`
- L487 _protected prototype_ `virtual FName AddHostMemberVariableFromExternal(FRigVMExternalVariable InVariableToCreate, FString InDefaultValue = FString()) override;`
- L490 _public member_ `FOnRigVMPreVariablesChanged OnPreVariablesChangedDelegate;`
- L491 _public member_ `FOnRigVMPostVariablesChanged OnPostVariablesChangedDelegate;`
- L492 _public function_ `virtual FOnRigVMPreVariablesChanged& OnPreVariablesChanged() override`
- L493 _public function_ `virtual FOnRigVMPostVariablesChanged& OnPostVariablesChanged() override`
- L494 _public prototype_ `virtual void HandlePreVariableChange(UObject* InObject);`
- L495 _public prototype_ `virtual void HandlePostVariableChange(UBlueprint* InBlueprint);`
- L496 _public member_ `bool bUpdatingExternalVariables;`
- L498 _public prototype_ `void OnBlueprintChanged(UBlueprint* InBlueprint);`
- L499 _public prototype_ `void OnSetObjectBeingDebuggedReceived(UObject* InObject);`
- L504 _protected function_ `virtual void SetupDefaultObjectDuringCompilation(URigVMHost* InCDO) override`
- L505 _protected prototype_ `virtual void PreCompile() override;`
- L507 _protected prototype_ `virtual FProperty* FindGeneratedPropertyByName(const FName& InName) override;`
- L508 _protected prototype_ `virtual bool SetVariableTooltip(const FName& InName, const FText& InTooltip) override;`
- L509 _protected prototype_ `virtual FText GetVariableTooltip(const FName& InName) const override;`
- L510 _protected prototype_ `virtual bool SetVariableCategory(const FName& InName, const FString& InCategory) override;`
- L511 _protected prototype_ `virtual FString GetVariableCategory(const FName& InName) override;`
- L512 _protected prototype_ `virtual FString GetVariableMetadataValue(const FName& InName, const FName& InKey) override;`
- L513 _protected prototype_ `virtual bool SetVariableExposeOnSpawn(const FName& InName, const bool bInExposeOnSpawn) override;`
- L514 _protected prototype_ `virtual bool SetVariableExposeToCinematics(const FName& InName, const bool bInExposeToCinematics) override;`
- L515 _protected prototype_ `virtual bool SetVariablePrivate(const FName& InName, const bool bInPrivate) override;`
- L516 _protected prototype_ `virtual bool SetVariablePublic(const FName& InName, const bool bIsPublic) override;`
- L518 _protected prototype_ `virtual FString OnCopyVariable(const FName& InName) const override;` — virtual bool ChangeAssetVariableType(const FName& InName, const FEdGraphPinType& InType) override;
- L519 _protected prototype_ `virtual bool OnPasteVariable(const FString& InText) override;`
- L525 _private member_ `TArray<FBPVariableDescription> LastNewVariables;`

#### Free symbols / members of external scopes

- L26 _macro_ `#define UE_API RIGVMDEVELOPER_API`

### `Plugins/Runtime/RigVM/Source/RigVMDeveloper/Public/RigVMBlueprintUtils.h` (Public)


#### struct `FRigVMBlueprintUtils`  
`struct FRigVMBlueprintUtils`  
_L18-53_
- L21 _public prototype_ `static void ForAllRigVMStructs(TFunction<void(UScriptStruct*)> InFunction);` — Call a function for each valid rig unit struct
- L24 _public prototype_ `static void HandleReconstructAllBlueprintNodes(UBlueprint* InBlueprint);` — Handle blueprint node reconstruction
- L25 _public prototype_ `static void HandleReconstructAllBlueprintNodes(FRigVMEditorAssetInterfacePtr InBlueprint);`
- L28 _public prototype_ `static void HandleRefreshAllNodes(FRigVMEditorAssetInterfacePtr InBlueprint);` — Handle blueprint node refresh
- L29 _public prototype_ `static void HandleRefreshAllBlueprintNodes(UBlueprint* InBlueprint);`
- L32 _public prototype_ `static void HandleAssetDeleted(const FAssetData& InAssetData);` — Handle blueprint deleted
- L35 _public prototype_ `static void RemoveMemberVariableIfNotUsed(FRigVMEditorAssetInterfacePtr Blueprint, const FName VarName);` — remove the variable if not used by anybody else but ToBeDeleted
- L38 _public prototype_ `static URigVMEdGraph* CreateNewGraph(UObject* ParentScope, const FName& GraphName, TSubclassOf<class URigVMEdGraph> GraphClass, TSubclassOf<class URigVMEdGraphSchema> SchemaClass);` — Create a new EdGraph
- L40 _public prototype_ `static FName ValidateName(FRigVMEditorAssetInterfacePtr InBlueprint, const FString& InName);`
- L43 _public prototype_ `static UEdGraphNode* GetNodeByGUID(const FRigVMEditorAssetInterfacePtr InBlueprint, const FGuid& InNodeGuid);` — Searches all nodes in a Blueprint and checks for a matching Guid
- L46 _public prototype_ `static FRigVMEditorAssetInterfacePtr FindAssetForGraph(const UEdGraph* Graph);` — Helper function to get the asset that ultimately owns a graph.
- L49 _public prototype_ `static FRigVMEditorAssetInterfacePtr FindAssetForNode(const UEdGraphNode* Node);` — Helper function to get the asset that ultimately owns a graph.
- L52 _public prototype_ `static FName FindUniqueVariableName(const IRigVMEditorAssetInterface* InBlueprint, const FString& InBaseName);` — Helper function to find a unique name for an asset variable

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API RIGVMDEVELOPER_API`

### `Plugins/Runtime/RigVM/Source/RigVMDeveloper/Public/RigVMCompiler/RigVMAST.h` (Public)


#### struct `FRigVMASTLinkDescription`  
`struct FRigVMASTLinkDescription`  
_L41-66_
- desc: A structure to describe a link between two proxies
- L43 _public function_ `FRigVMASTLinkDescription()`
- L45 _public function_ `FRigVMASTLinkDescription(const FRigVMASTProxy& InSourceProxy, const FRigVMASTProxy& InTargetProxy, const FString& InSegmentPath) : SourceProxy(InSourceProxy) , TargetProxy(InTargetProxy) , SegmentPath(InSegmentPath) , LinkIndex(INDEX_NONE)`
- L52 _public function_ `FRigVMASTLinkDescription(const FRigVMASTLinkDescription& InOther) : SourceProxy(InOther.SourceProxy) , TargetProxy(InOther.TargetProxy) , SegmentPath(InOther.SegmentPath) , LinkIndex(INDEX_NONE)`
- L60 _public prototype_ `FRigVMASTLinkDescription& operator=(const FRigVMASTLinkDescription&) = default;` — Note that unlike the copy constructor, LinkIndex is copied by the assignment operator.
- L62 _public member_ `FRigVMASTProxy SourceProxy;`
- L63 _public member_ `FRigVMASTProxy TargetProxy;`
- L64 _public member_ `FString SegmentPath;`
- L65 _public member_ `int32 LinkIndex;`

#### class `FRigVMExprAST`  
`class FRigVMExprAST`  
_L77-356_
- desc: Base class for an expression within an abstract syntax tree. The base implements parent / child relationships as well as a simple typing system. An expression is a multi child / multi parent element of a directed tree (there can be no cycles). Expressions can only be constructed by an AST parser, and are also memory-owned by the parser.
- L100 _public prototype_ `virtual ~FRigVMExprAST() = default;` — virtual destructor
- L103 _public prototype_ `FRigVMExprAST(const FRigVMExprAST&) = delete;` — disable copy constructor
- L107 _public function_ `const FRigVMParserAST* GetParser() const` — returns the parser this expression is owned by @return the parser this expression is owned by
- L111 _public function_ `FName GetName() const` — returns the name of the expression (can be NAME_None) @return the name of the expression
- L115 _public function_ `EType GetType() const` — returns the exact type of the expression @return the exact type of the expression
- L119 _public prototype_ `FName GetTypeName() const;` — returns the name of the expression's type @return the name of the expression's type
- L124 _public prototype_ `virtual bool IsA(EType InType) const = 0;` — provides type checking for inherited types @param InType the type to check against @return true if this expression is of a given type
- L127 _public function_ `virtual bool IsNode() const` — returns true if the expression is a node expression
- L133 _public function_ `virtual bool IsVar() const` — returns true if the expression is a var expression
- L140 _public function_ `int32 GetIndex() const` — returns the index of this expression within the parser's storage @return the index of this expression within the parser's storage
- L143 _public function_ `bool IsValid() const` — returns true if the expressoin is valid
- L146 _public function_ `virtual const FRigVMASTProxy& GetProxy() const` — returns the model proxy this expression relates to
- L154 _public prototype_ `const FRigVMExprAST* GetParent() const;` — returns the parent of this expression @return the parent of this expression
- L159 _public prototype_ `virtual const FRigVMExprAST* GetFirstParentOfType(EType InExprType) const;` — returns the first parent in the tree of a given type @param InExprType The type of expression to look for in the parent tree @return the first parent in the tree of a given type
- L164 _public prototype_ `bool IsParentedTo(const FRigVMExprAST* InParentExpr) const;` — returns true if a given expression is parented to another expression @param InParentExpr The potential parent to check @return True if this expression is parented to the InParentExpr
- L169 _public prototype_ `bool IsParentOf(const FRigVMExprAST* InChildExpr) const;` — returns true if a given expression is a parent of another expression @param InChildExpr The potential child to check @return True if this expression is a parent of the InChildExpr
- L173 _public prototype_ `const FRigVMBlockExprAST* GetBlock() const;` — returns the block of this expression @return the block of this expression
- L177 _public prototype_ `const FRigVMBlockExprAST* GetRootBlock() const;` — returns the root / top level block of this expression @return the root / top level block of this expression
- L182 _public typedef_ `typedef TArray<const FRigVMBlockExprAST*, TInlineAllocator<5>> FRigVMBlockArray;` — returns all of the block this expression is in @param bSortByDepth If true the blocks will be returned sorted (head to tail) @return all of the block this expression is in
- L183 _public prototype_ `FRigVMBlockArray GetBlocks(bool bSortByDepth) const;`
- L187 _public prototype_ `TOptional<uint32> GetBlockCombinationHash() const;` — returns the unique block combination hash for this expression (or INDEX_NONE) @return the unique block combination name for this expression (or INDEX_NONE)
- L191 _public prototype_ `const FString& GetBlockCombinationName() const;` — returns the unique block combination name for this expression (or an empty string) @return the unique block combination name for this expression (or an empty string)
- L195 _public prototype_ `int32 GetMinChildIndexWithinParent(const FRigVMExprAST* InParentExpr) const;` — returns the lowest child index found for this expression within a parent (or INDEX_NONE) @return the lowest child index found for this expression within a parent (or INDEX_NONE)
- L199 _public function_ `int32 NumChildren() const` — returns the number of children of this expression @return the number of children of this expression
- L203 _public prototype_ `virtual bool IsConstant() const;` — returns true if this expressions is constant (non varying) @return true if this expressions is constant (non varying)
- L207 _public function_ `bool IsVarying() const` — returns true if this expressions is varying (non constant) @return true if this expressions is varying (non constant)
- L211 _public prototype_ `int32 GetMaximumDepth() const;` — returns the maximum depth of the expression in tree (number of recursive parents) @return the maximum depth of the expression in tree (number of recursive parents)
- L216 _public function_ `const FRigVMExprAST* operator[](int32 InIndex) const` — accessor operator for a given child @param InIndex the index of the child to retrieve (bound = NumChildren() - 1) @return the child at the given index
- L219 _public function_ `TArray<FRigVMExprAST*>::RangedForConstIteratorType begin() const` — begin iterator accessor for the children
- L221 _public function_ `TArray<FRigVMExprAST*>::RangedForConstIteratorType end() const` — end iterator accessor for the children
- L228 _public function_ `template<class ObjectType> const ObjectType* ChildAt(int32 InIndex) const` — templated getter to retrieve a child with a given index type checking will occur within the ::To method and raise @param InIndex the index of the child to retrieve @return the child at a given index cast to the provided class
- L236 _public function_ `const FRigVMExprAST* ChildAt(int32 InIndex) const` — getter to retrieve a child with a given index @param InIndex the index of the child to retrieve @return the child at a given index
- L244 _public prototype_ `virtual const FRigVMExprAST* GetFirstChildOfType(EType InExprType) const;` — returns the first parent in the tree of a given type @param InExprType The type of expression to look for in the parent tree @return the first parent in the tree of a given type
- L248 _public function_ `int32 NumParents() const` — returns the number of parents of this expression @return the number of parents of this expression
- L255 _public function_ `template<class ObjectType> const ObjectType* ParentAt(int32 InIndex) const` — templated getter to retrieve a parent with a given index type checking will occur within the ::To method and raise @param InIndex the index of the parent to retrieve @return the parent at a given index cast to the provided class
- L263 _public function_ `const FRigVMExprAST* ParentAt(int32 InIndex) const` — getter to retrieve a parent with a given index @param InIndex the index of the parent to retrieve @return the parent at a given index
- L273 _public function_ `template<class ObjectType> const ObjectType* To() const` — const templated cast for casting between different expression types. specializations below are used for type checking @return this object cast to the provided class
- L284 _public function_ `template<class ObjectType> ObjectType* To()` — templated cast for casting between different expression types. specializations below are used for type checking @return this object cast to the provided class
- L292 _protected prototype_ `FRigVMExprAST(EType InType = EType::Invalid, const FRigVMASTProxy& InProxy = FRigVMASTProxy());` — default constructor (protected so that only parser can access it)
- L297 _protected prototype_ `void AddParent(FRigVMExprAST* InParent);` — adds a parent to this expression this in consequence also adds this as a child to the parent @param InParent the parent to add
- L302 _protected prototype_ `void RemoveParent(FRigVMExprAST* InParent);` — removes a parent from this expression this in consequence also removes this as a child from the parent @param InParent the parent to remove
- L307 _protected prototype_ `void RemoveChild(FRigVMExprAST* InChild);` — removes a child from this expression this in consequence also removes this as a parent from the child @param InChild the child to remove
- L313 _protected prototype_ `void ReplaceParent(FRigVMExprAST* InCurrentParent, FRigVMExprAST* InNewParent, TArray<int32>* OutParentIndices = nullptr);` — replaces a parent of this expression with a new one @param InCurrentParent the current parent to replace @param InNewParent the new parent to replace it with @param OutParentIndices The list of parent indices affected
- L319 _protected prototype_ `void ReplaceChild(FRigVMExprAST* InCurrentChild, FRigVMExprAST* InNewChild, TArray<int32>* OutChildIndices = nullptr);` — replaces a child of this expression with a new one @param InCurrentChild the current child to replace @param InNewChild the new child to replace it with @param OutChildIndices The list of child indices affected
- L323 _protected prototype_ `void ReplaceBy(FRigVMExprAST* InReplacement);` — replaces this expression with another one @param InReplacement the expression to replace this one
- L326 _protected prototype_ `void GetBlocksImpl(FRigVMBlockArray& InOutBlocks) const;` — computes all of the block this expression is in
- L332 _protected prototype_ `virtual FString DumpText(const FString& InPrefix = FString()) const;` — returns a string containing an indented tree structure for debugging purposes. this is only used by the parser @param InPrefix the prefix to use for indentation @return the text representation of this part of the tree
- L335 _protected prototype_ `void InvalidateCaches();` — Resets the internal caches of the expression
- L336 _protected prototype_ `void InvalidateCachesImpl(TArray<bool>& OutProcessed);`
- L338 _protected member_ `FName Name;`
- L339 _protected member_ `EType Type;`
- L340 _protected member_ `int32 Index;`
- L341 _protected member_ `const FRigVMParserAST* ParserPtr;`
- L342 _protected member_ `TArray<FRigVMExprAST*> Parents;`
- L343 _protected member_ `TArray<FRigVMExprAST*> Children;`
- L344 _protected member_ `TMap<FName, int32> PinNameToChildIndex;`
- L345 _protected member_ `mutable TOptional<TOptional<uint32>> BlockCombinationHash;`
- L346 _protected member_ `mutable TOptional<int32> MaximumDepth;`
- L347 _protected member_ `mutable TOptional<int32> BlocksCacheVersion;`
- L348 _protected member_ `mutable FRigVMBlockArray CachedBlocks;`
- L349 _protected member_ `mutable TOptional<int32> FirstChildOfTypeCacheVersion;`
- L350 _protected member_ `mutable TMap<int32, const FRigVMExprAST*> CachedFirstChildOfType;`
- L351 _protected member_ `mutable TOptional<int32> FirstParentOfTypeCacheVersion;`
- L352 _protected member_ `mutable TMap<int32, const FRigVMExprAST*> CachedFirstParentOfType;`
- L363 _function_ `template<> inline const FRigVMBlockExprAST* FRigVMExprAST::To() const` — specialized cast for type checking for a Block / FRigVMBlockExprAST expression will raise if types are not compatible @return this expression cast to FRigVMBlockExprAST
- L374 _function_ `template<> inline const FRigVMNodeExprAST* FRigVMExprAST::To() const` — specialized cast for type checking for a Node / FRigVMNodeExprAST expression will raise if types are not compatible @return this expression cast to FRigVMNodeExprAST
- L391 _function_ `template<> inline const FRigVMEntryExprAST* FRigVMExprAST::To() const` — specialized cast for type checking for a Entry / FRigVMEntryExprAST expression will raise if types are not compatible @return this expression cast to FRigVMEntryExprAST
- L402 _function_ `template<> inline const FRigVMInvokeEntryExprAST* FRigVMExprAST::To() const` — specialized cast for type checking for a InvokeEntry / FRigVMInvokeEntryExprAST expression will raise if types are not compatible @return this expression cast to FRigVMInvokeEntryExprAST
- L413 _function_ `template<> inline const FRigVMCallExternExprAST* FRigVMExprAST::To() const` — specialized cast for type checking for a CallExtern / FRigVMCallExternExprAST expression will raise if types are not compatible @return this expression cast to FRigVMCallExternExprAST
- L424 _function_ `template<> inline const FRigVMInlineFunctionExprAST* FRigVMExprAST::To() const` — specialized cast for type checking for a InlineFunction / FRigVMInlineFunctionExprAST expression will raise if types are not compatible @return this expression cast to FRigVMInlineFunctionExprAST
- L435 _function_ `template<> inline const FRigVMNoOpExprAST* FRigVMExprAST::To() const` — specialized cast for type checking for a NoOp / FRigVMNoOpExprAST expression will raise if types are not compatible @return this expression cast to FRigVMNoOpExprASTo
- L446 _function_ `template<> inline const FRigVMVarExprAST* FRigVMExprAST::To() const` — specialized cast for type checking for a Var / FRigVMVarExprAST expression will raise if types are not compatible @return this expression cast to FRigVMVarExprAST
- L457 _function_ `template<> inline const FRigVMLiteralExprAST* FRigVMExprAST::To() const` — specialized cast for type checking for a Literal / FRigVMLiteralExprAST expression will raise if types are not compatible @return this expression cast to FRigVMLiteralExprAST
- L468 _function_ `template<> inline const FRigVMAssignExprAST* FRigVMExprAST::To() const` — specialized cast for type checking for a Assign / FRigVMAssignExprAST expression will raise if types are not compatible @return this expression cast to FRigVMAssignExprAST
- L479 _function_ `template<> inline const FRigVMCopyExprAST* FRigVMExprAST::To() const` — specialized cast for type checking for a Copy / FRigVMCopyExprAST expression will raise if types are not compatible @return this expression cast to FRigVMCopyExprASTo
- L490 _function_ `template<> inline const FRigVMCachedValueExprAST* FRigVMExprAST::To() const` — specialized cast for type checking for a CachedValue / FRigVMCachedValueExprAST expression will raise if types are not compatible @return this expression cast to FRigVMCachedValueExprAST
- L501 _function_ `template<> inline const FRigVMExitExprAST* FRigVMExprAST::To() const` — specialized cast for type checking for a Exit / FRigVMExitExprAST expression will raise if types are not compatible @return this expression cast to FRigVMExitExprAST

#### enum `FRigVMExprAST::EType`  
`enum EType`  
_L82-97_
- desc: Simple enum for differentiating expression types.
- L84 _public enumerator_ `Block`
- L85 _public enumerator_ `Entry`
- L86 _public enumerator_ `InvokeEntry`
- L87 _public enumerator_ `CallExtern`
- L88 _public enumerator_ `InlineFunction`
- L89 _public enumerator_ `NoOp`
- L90 _public enumerator_ `Var`
- L91 _public enumerator_ `Literal`
- L92 _public enumerator_ `Assign`
- L93 _public enumerator_ `Copy`
- L94 _public enumerator_ `CachedValue`
- L95 _public enumerator_ `Exit`
- L96 _public enumerator_ `Invalid`

#### class `FRigVMBlockExprAST`  
`class FRigVMBlockExprAST : public FRigVMExprAST`  
_L512-558_
- inherits: `FRigVMExprAST`
- desc: An abstract syntax tree block expression represents a sequence of child expressions to be executed in order. In C++ a block is represented by the curly braces { expr1, expr2, ...}.
- L517 _public prototype_ `virtual ~FRigVMBlockExprAST() = default;` — virtual destructor
- L520 _public prototype_ `FRigVMBlockExprAST(const FRigVMBlockExprAST&) = delete;` — disable copy constructor
- L525 _public prototype_ `bool ShouldExecute() const;` — returns true if this block needs to execute this is determined by the block containing an entry expression @return true if this block needs to execute
- L529 _public prototype_ `bool ContainsEntry() const;` — returns true if this block contains an entry expression @return true if this block contains an entry expression
- L534 _public prototype_ `bool Contains(const FRigVMExprAST* InExpression, TMap<const FRigVMExprAST*, bool>* ContainedExpressionsCache = nullptr) const;` — returns true if this block contains a given expression @param InExpression the expression to check @return true if this block contains a given expression
- L537 _public function_ `virtual bool IsA(EType InType) const override` — overload of the type checking mechanism
- L543 _public prototype_ `bool IsObsolete() const;` — returns true in case this block should not be executed
- L548 _protected function_ `FRigVMBlockExprAST(EType InType = EType::Block, const FRigVMASTProxy& InProxy = FRigVMASTProxy()) : FRigVMExprAST(InType, InProxy) , bIsObsolete(false)` — default constructor (protected so that only parser can access it)
- L555 _private member_ `bool bIsObsolete;`

#### class `FRigVMNodeExprAST`  
`class FRigVMNodeExprAST : public FRigVMBlockExprAST`  
_L564-613_
- inherits: `FRigVMBlockExprAST`
- desc: An abstract syntax tree node expression represents any expression which references a node from the RigVM model.
- L569 _public prototype_ `virtual ~FRigVMNodeExprAST() = default;` — virtual destructor
- L572 _public prototype_ `FRigVMNodeExprAST(const FRigVMNodeExprAST&) = delete;` — disable copy constructor
- L575 _public function_ `virtual const FRigVMASTProxy& GetProxy() const override` — returns the proxy this expression is using
- L577 _public function_ `virtual bool IsNode() const`
- L584 _public function_ `URigVMNode* GetNode() const` — returns the node from the model this expression is referencing @return the node from the model this expression is referencing
- L586 _public prototype_ `virtual bool IsConstant() const override;`
- L587 _public prototype_ `const FRigVMExprAST* FindExprWithPinName(const FName& InPinName) const;`
- L588 _public prototype_ `const FRigVMVarExprAST* FindVarWithPinName(const FName& InPinName) const;`
- L589 _public prototype_ `const FName& GetPinNameForChildIndex(int32 InChildIndex) const;`
- L591 _public prototype_ `void SetSegmentPathForChild(int32 InChildIndex, const FString& InSegmentPath);`
- L592 _public prototype_ `const FString& GetSegmentPathForChild(int32 InChildIndex) const;`
- L597 _protected prototype_ `FRigVMNodeExprAST(EType InType, const FRigVMASTProxy& InNodeProxy);` — default constructor (protected so that only parser can access it)
- L600 _protected function_ `virtual bool IsA(EType InType) const override` — overload of the type checking mechanism
- L607 _private member_ `TMap<int32,FString> SegmentPathForChild;`
- L609 _private member_ `FRigVMASTProxy Proxy;`

#### class `FRigVMEntryExprAST`  
`class FRigVMEntryExprAST : public FRigVMNodeExprAST`  
_L620-654_
- inherits: `FRigVMNodeExprAST`
- desc: An abstract syntax tree entry expression represents an entry point for a function or an event in an event graph. In C++ the entry point is the declaration: void main(...);
- L625 _public prototype_ `virtual ~FRigVMEntryExprAST() = default;` — virtual destructor
- L628 _public prototype_ `FRigVMEntryExprAST(const FRigVMEntryExprAST&) = delete;` — disable copy constructor
- L631 _public function_ `virtual bool IsA(EType InType) const override` — overload of the type checking mechanism
- L642 _public prototype_ `FName GetEventName() const;` — returns the name of the entry / event @return the name of the entry / event
- L647 _protected function_ `FRigVMEntryExprAST(const FRigVMASTProxy& InNodeProxy) : FRigVMNodeExprAST(EType::Entry, InNodeProxy)` — default constructor (protected so that only parser can access it)

#### class `FRigVMInvokeEntryExprAST`  
`class FRigVMInvokeEntryExprAST : public FRigVMNodeExprAST`  
_L660-694_
- inherits: `FRigVMNodeExprAST`
- desc: An abstract syntax tree entry expression represents an invocation of an entry point.
- L665 _public prototype_ `virtual ~FRigVMInvokeEntryExprAST() = default;` — virtual destructor
- L668 _public prototype_ `FRigVMInvokeEntryExprAST(const FRigVMInvokeEntryExprAST&) = delete;` — disable copy constructor
- L671 _public function_ `virtual bool IsA(EType InType) const override` — overload of the type checking mechanism
- L682 _public prototype_ `FName GetEventName() const;` — returns the name of the entry / event @return the name of the entry / event
- L687 _protected function_ `FRigVMInvokeEntryExprAST(const FRigVMASTProxy& InNodeProxy) : FRigVMNodeExprAST(EType::InvokeEntry, InNodeProxy)` — default constructor (protected so that only parser can access it)

#### class `FRigVMCallExternExprAST`  
`class FRigVMCallExternExprAST: public FRigVMNodeExprAST`  
_L703-729_
- inherits: `FRigVMNodeExprAST`
- desc: An abstract syntax tree call extern expression represents the invocation of an extern function. In C++ the call extern is an invocation: FMath::Clamp(1.4, 0.0, 1.0); The call extern expression references a node (through parent class) from the model providing all of the relevant information for the invocation.
- L708 _public prototype_ `virtual ~FRigVMCallExternExprAST() = default;` — virtual destructor
- L711 _public prototype_ `FRigVMCallExternExprAST(const FRigVMCallExternExprAST&) = delete;` — disable copy constructor
- L714 _public function_ `virtual bool IsA(EType InType) const override` — overload of the type checking mechanism
- L722 _protected function_ `FRigVMCallExternExprAST(const FRigVMASTProxy& InNodeProxy) : FRigVMNodeExprAST(EType::CallExtern, InNodeProxy)` — default constructor (protected so that only parser can access it)

#### class `FRigVMInlineFunctionExprAST`  
`class FRigVMInlineFunctionExprAST: public FRigVMNodeExprAST`  
_L734-763_
- inherits: `FRigVMNodeExprAST`
- L739 _public prototype_ `virtual ~FRigVMInlineFunctionExprAST() = default;` — virtual destructor
- L742 _public prototype_ `FRigVMInlineFunctionExprAST(const FRigVMInlineFunctionExprAST&) = delete;` — disable copy constructor
- L745 _public function_ `virtual bool IsA(EType InType) const override` — overload of the type checking mechanism
- L751 _public function_ `virtual bool IsConstant() const override` — todo: For now, all function references are considered varying (UE-170129)
- L756 _protected function_ `FRigVMInlineFunctionExprAST(const FRigVMASTProxy& InNodeProxy) : FRigVMNodeExprAST(EType::InlineFunction, InNodeProxy)` — default constructor (protected so that only parser can access it)

#### class `FRigVMNoOpExprAST`  
`class FRigVMNoOpExprAST : public FRigVMNodeExprAST`  
_L772-798_
- inherits: `FRigVMNodeExprAST`
- desc: An abstract syntax tree no-op expression represents an expression which is relevant for the structure of the tree (for grouping for example) but which itself has no operation connected to it. For the RigVM AST we use the no-op expression for representing reroute nodes in the model as well as parameter and variable getter nodes.
- L777 _public prototype_ `virtual ~FRigVMNoOpExprAST() = default;` — virtual destructor
- L780 _public prototype_ `FRigVMNoOpExprAST(const FRigVMNoOpExprAST&) = delete;` — disable copy constructor
- L783 _public function_ `virtual bool IsA(EType InType) const override` — overload of the type checking mechanism
- L791 _protected function_ `FRigVMNoOpExprAST(const FRigVMASTProxy& InNodeProxy) : FRigVMNodeExprAST(EType::NoOp, InNodeProxy)` — default constructor (protected so that only parser can access it)

#### class `FRigVMVarExprAST`  
`class FRigVMVarExprAST: public FRigVMExprAST`  
_L806-888_
- inherits: `FRigVMExprAST`
- desc: An abstract syntax tree var expression represents the definition of mutable memory for a single variable. In C++ the var expression is a variable declaration: int A; The var expression references a pin from the model.
- L811 _public prototype_ `virtual ~FRigVMVarExprAST() = default;` — virtual destructor
- L814 _public prototype_ `FRigVMVarExprAST(const FRigVMVarExprAST&) = delete;` — disable copy constructor
- L817 _public function_ `virtual bool IsA(EType InType) const override` — overload of the type checking mechanism
- L822 _public function_ `virtual bool IsVar() const`
- L827 _public prototype_ `virtual bool IsConstant() const override;`
- L830 _public function_ `virtual const FRigVMASTProxy& GetProxy() const override` — returns the proxy this expression is using
- L834 _public function_ `URigVMPin* GetPin() const` — returns the pin in the model this variable is representing @return the pin in the model this variable is representing
- L838 _public prototype_ `FString GetCPPType() const;` — returns the C++ data type of this variable @return the C++ data type of this variable
- L842 _public prototype_ `UObject* GetCPPTypeObject() const;` — returns the C++ data type object (ustruct / uenum) @return the C++ data type object (ustruct / uenum)
- L846 _public prototype_ `ERigVMPinDirection GetPinDirection() const;` — returns the pin direction of this variable (input, output, hidden etc) @return the pin direction of this variable (input, output, hidden etc)
- L850 _public prototype_ `FString GetDefaultValue() const;` — returns the default value on the pin for this variable @return the default value on the pin for this variable
- L854 _public prototype_ `bool IsExecuteContext() const;` — returns true if this variable is an execute context @return true if this variable is an execute context
- L858 _public prototype_ `bool IsGraphVariable() const;` — returns true if this variable is a graph variable @return true if this variable is a graph variable
- L861 _public prototype_ `bool IsEnumValue() const;` — returns true if this is a constant enum index
- L864 _public prototype_ `bool SupportsSoftLinks() const;` — returns true if this variable allows links to be "soft", so without a cache / computed value.
- L867 _public function_ `const FRigVMVarExprAST* GetVariableCloneExpr() const` — Returns the clone this variable expression is using.
- L875 _protected function_ `FRigVMVarExprAST(EType InType, const FRigVMASTProxy& InPinProxy) : FRigVMExprAST(InType) , Proxy(InPinProxy)` — default constructor (protected so that only parser can access it)
- L883 _private member_ `FRigVMASTProxy Proxy;`
- L884 _private member_ `const FRigVMVarExprAST* ClonedVarExpr = nullptr;`

#### class `FRigVMLiteralExprAST`  
`class FRigVMLiteralExprAST : public FRigVMVarExprAST`  
_L896-931_
- inherits: `FRigVMVarExprAST`
- desc: An abstract syntax tree literal expression represents the definition of const memory for a single variable - vs a var expression which is mutable. In C++ the literal expression is a literal declaration, for ex: const float PI = 3.14f; The literal expression references a pin from the model.
- L901 _public prototype_ `virtual ~FRigVMLiteralExprAST() = default;` — virtual destructor
- L904 _public prototype_ `FRigVMLiteralExprAST(const FRigVMLiteralExprAST&) = delete;` — disable copy constructor
- L907 _public function_ `virtual bool IsA(EType InType) const override` — overload of the type checking mechanism
- L916 _public function_ `virtual bool IsConstant() const override`
- L924 _protected function_ `FRigVMLiteralExprAST(const FRigVMASTProxy& InPinProxy) : FRigVMVarExprAST(EType::Literal, InPinProxy)` — default constructor (protected so that only parser can access it)

#### class `FRigVMAssignExprAST`  
`class FRigVMAssignExprAST : public FRigVMExprAST`  
_L940-987_
- inherits: `FRigVMExprAST`
- desc: An abstract syntax tree assign expression represents the assignment of one expression to another. This can result in referencing memory from a to b or copying memory from a to b (thus the copy expression inherits the assign). In C++ the assign expression used for construction and copy, for ex: int32 A = B + 1; The assign expression references two pins / a link from the model.
- L945 _public prototype_ `virtual ~FRigVMAssignExprAST() = default;` — virtual destructor
- L948 _public prototype_ `FRigVMAssignExprAST(const FRigVMAssignExprAST&) = delete;` — disable copy constructor
- L951 _public function_ `const FRigVMASTLinkDescription& GetLink() const` — returns the source proxy this expression is using
- L954 _public function_ `const FRigVMASTProxy& GetSourceProxy() const` — returns the source proxy this expression is using
- L958 _public function_ `URigVMPin* GetSourcePin() const` — returns the source pin for this assignment @return the source pin for this assignment
- L961 _public function_ `const FRigVMASTProxy& GetTargetProxy() const` — returns the target proxy this expression is using
- L965 _public function_ `URigVMPin* GetTargetPin() const` — returns the target pin for this assignment @return the target pin for this assignment
- L967 _public function_ `virtual const FRigVMASTProxy& GetProxy() const override`
- L970 _public function_ `virtual bool IsA(EType InType) const override` — overload of the type checking mechanism
- L978 _protected function_ `FRigVMAssignExprAST(EType InType, const FRigVMASTLinkDescription& InLink) : FRigVMExprAST(InType) , Link(InLink)` — default constructor (protected so that only parser can access it)
- L985 _private member_ `FRigVMASTLinkDescription Link;`

#### class `FRigVMCopyExprAST`  
`class FRigVMCopyExprAST : public FRigVMAssignExprAST`  
_L997-1028_
- inherits: `FRigVMAssignExprAST`
- desc: An abstract syntax tree copy expression represents the an assignment of one expression to another which causes / requires a copy operation. Within the RigVM AST this is only used for copying work state out of / into parameters or when composing / decomposing a structure (for ex: assigning a float to a vector.x). In C++ the copy expression is used for structures, for ex: FVector A = B; The copy expression references two pins / a link from the model.
- L1002 _public prototype_ `virtual ~FRigVMCopyExprAST() = default;` — virtual destructor
- L1005 _public prototype_ `FRigVMCopyExprAST(const FRigVMCopyExprAST&) = delete;` — disable copy constructor
- L1008 _public function_ `virtual bool IsA(EType InType) const override` — overload of the type checking mechanism
- L1020 _protected function_ `FRigVMCopyExprAST(const FRigVMASTLinkDescription& InLink) : FRigVMAssignExprAST(EType::Copy, InLink)` — default constructor (protected so that only parser can access it)

#### class `FRigVMCachedValueExprAST`  
`class FRigVMCachedValueExprAST : public FRigVMExprAST`  
_L1036-1071_
- inherits: `FRigVMExprAST`
- desc: An abstract syntax tree cached value expression represents the reference to a variable which needs to be calculated by a call extern expression. The first child of the cached value expression is the var expression to be computed / cached, the second child is the call extern expression to use.
- L1041 _public prototype_ `virtual ~FRigVMCachedValueExprAST() = default;` — virtual destructor
- L1044 _public prototype_ `FRigVMCachedValueExprAST(const FRigVMCachedValueExprAST&) = delete;` — disable copy constructor
- L1047 _public function_ `virtual bool IsA(EType InType) const override` — overload of the type checking mechanism
- L1054 _public function_ `const FRigVMVarExprAST* GetVarExpr() const` — returns the var expression of this cached value (const) @return the var expression of this cached value (const)
- L1058 _public function_ `const FRigVMCallExternExprAST* GetCallExternExpr() const` — returns the call extern expression of this cached value (const) @return the call extern expression of this cached value (const)
- L1063 _protected function_ `FRigVMCachedValueExprAST(const FRigVMASTProxy& InProxy) : FRigVMExprAST(EType::CachedValue, InProxy)` — default constructor (protected so that only parser can access it)

#### class `FRigVMExitExprAST`  
`class FRigVMExitExprAST : public FRigVMExprAST`  
_L1077-1108_
- inherits: `FRigVMExprAST`
- desc: An abstract syntax tree exit expression represents the exit out of an entry expression. In C++ the exit expression is a return from a main function.
- L1082 _public prototype_ `virtual ~FRigVMExitExprAST() = default;` — virtual destructor
- L1085 _public prototype_ `FRigVMExitExprAST(const FRigVMExitExprAST&) = delete;` — disable copy constructor
- L1088 _public function_ `virtual bool IsA(EType InType) const override` — overload of the type checking mechanism
- L1093 _public function_ `virtual bool IsConstant() const override`
- L1101 _protected function_ `FRigVMExitExprAST(const FRigVMASTProxy& InProxy) : FRigVMExprAST(EType::Exit, InProxy)` — default constructor (protected so that only parser can access it)

#### struct `FRigVMParserASTSettings`  
`struct FRigVMParserASTSettings`  
_L1115-1183_
- reflection: `USTRUCT(BlueprintType)`
- desc: The settings to apply during the parse of the abstract syntax tree. The folding settings can affect the performance of the parse dramatically.
- L1121 _public member_ `bool bFoldAssignments = false;` — `UPROPERTY(EditAnywhere, Category = "AST")` — fold root pin assignments / copies
- L1125 _public member_ `bool bFoldSubPinCopies = false;` — `UPROPERTY(EditAnywhere, Category = "AST")` — fold sub pin assignments / copies
- L1129 _public member_ `bool bFoldLiterals = false;` — `UPROPERTY(EditAnywhere, Category = "AST")` — fold literals and share memory
- L1132 _public member_ `bool bSetupTraits = true;` — `UPROPERTY(EditAnywhere, Transient, BlueprintReadWrite, Category = "AST")`
- L1136 _public member_ `TArray<TObjectPtr<URigVMLink>> LinksToSkip;` — `UPROPERTY()` — links to be ignored during the parse
- L1143 _public member_ `TSet<FObjectKey> InteractiveNodes;` — nodes whose input literals must not be shared with other nodes' literals. used by Direct Manipulation to keep per-node registers during interactive editing so that writing to one node's literal register does not affect other nodes. stored as FObjectKey rather than FName to correctly handle duplicate node names inside collapsed graphs. not a UPROPERTY — session-only, intentionally not serialized.
- L1145 _public member_ `FRigVMReportDelegate ReportDelegate;`
- L1148 _public member_ `TObjectPtr<UScriptStruct> ExecuteContextStruct;` — `UPROPERTY(VisibleAnywhere, Category = "AST", transient)`
- L1151 _public function_ `static FRigVMParserASTSettings Fast(UScriptStruct* InExecuteContextStruct = nullptr)` — static method to provide fast AST parse settings
- L1163 _public function_ `static FRigVMParserASTSettings Optimized(UScriptStruct* InExecuteContextStruct = nullptr)` — static method to provide AST parse settings tuned for a fast executing runtime, but slow parse
- L1173 _public prototype_ `void Report(EMessageSeverity::Type InSeverity, UObject* InSubject, const FString& InMessage) const;`
- L1176 _public function_ `template <typename... Types> void Reportf(EMessageSeverity::Type InSeverity, UObject* InSubject, UE::Core::TCheckedFormatString<FString::FmtCharType, Types...> Fmt, Types... Args) const`

#### class `FRigVMParserAST`  
`class FRigVMParserAST : public TSharedFromThis<FRigVMParserAST>`  
_L1192-1464_
- inherits: `TSharedFromThis<FRigVMParserAST>`
- desc: The abstract syntax tree parser is the main object to parse a RigVM model graph. It's the memory owner for all expressions and provides functionality for introspection of the tree. The abstract syntax tree is then fed into the RigVMCompiler to generate the byte code for the virtual machine.
- L1199 _public prototype_ `FRigVMParserAST(TArray<URigVMGraph*> InGraphs, URigVMController* InController = nullptr, const FRigVMParserASTSettings& InSettings = FRigVMParserASTSettings::Fast(), const TArray<FRigVMExternalVariable>& InExternalVariables = TArray<FRigVMExternalVariable>());` — default constructor @param InGraph The graph / model to parse @param InSettings The parse settings to use
- L1202 _public prototype_ `~FRigVMParserAST();` — default destructor
- L1205 _public function_ `int32 Num() const` — returns the number of root expressions
- L1210 _public function_ `const FRigVMExprAST* operator[](int32 InIndex) const` — operator accessor for a given root expression @param InIndex the index of the expression to retrieve (bound = Num() - 1) @return the root expression with the given index
- L1213 _public function_ `TArray<FRigVMExprAST*>::RangedForConstIteratorType begin() const` — begin iterator accessor for the root expressions
- L1216 _public function_ `TArray<FRigVMExprAST*>::RangedForConstIteratorType end() const` — end iterator accessor for the root expressions
- L1221 _public function_ `const FRigVMExprAST* At(int32 InIndex) const` — accessor method for a given root expression @param InIndex the index of the expression to retrieve (bound = Num() - 1) @return the root expression with the given index
- L1226 _public prototype_ `const FRigVMExprAST* GetExprForSubject(const FRigVMASTProxy& InProxy) const;` — returns the expression for a given subject. subjects include nodes and pins. @param InSubject the subject to retrieve the expression for (node or pin) @return the expressoin for the given subject (or nullptr)
- L1231 _public prototype_ `TArray<const FRigVMExprAST*> GetExpressionsForSubject(UObject* InSubject) const;` — returns all expressions for a given subject. subjects include nodes and pins. @param InSubject the subject to retrieve the expression for (node or pin) @return all expressions for the given subject
- L1237 _public prototype_ `void PrepareCycleChecking(URigVMPin* InPin);` — Prepares the parser for cycle checking on a given pin. This marks up the parents and childen of the corresponding expression in the graph, to allow the client to determine if a new parent / child relationship could cause a cycle. @param InPin the pin to initialize the cycle checking for
- L1244 _public prototype_ `bool CanLink(URigVMPin* InSourcePin, URigVMPin* InTargetPin, FString* OutFailureReason);` — Performs a cycle check for a new potential link (assign or copy) between two pins. @param InSourcePin the source (left) pin of the potential assign / copy @param InTargetPin the target (right) pin of the potential assign / copy @param OutFailureReason an optional storage for the possible failure reason description @return true if the potential link (assign / copy) can be established
- L1249 _public prototype_ `FString DumpText() const;` — returns a string containing an indented tree structure for debugging purposes. @return the simple text representing this abstract syntax tree
- L1254 _public prototype_ `FString DumpDot() const;` — returns a string containing a dot file notation for debugging purposes. @return the dot file text representing this abstract syntax tree
- L1257 _public prototype_ `FRigVMBlockExprAST* GetObsoleteBlock(bool bCreateIfMissing = true);` — returns an obsolete block for unmanaged expression
- L1258 _public prototype_ `const FRigVMBlockExprAST* GetObsoleteBlock(bool bCreateIfMissing = true) const;`
- L1261 _public function_ `const URigVMPin::FPinOverrideMap& GetPinOverrides() const` — returns the AST's override table for pin defaults
- L1264 _public function_ `const FRigVMParserASTSettings& GetSettings() const` — returns the settings used for this parser
- L1270 _private function_ `template<class ExprType> ExprType* MakeExpr(FRigVMExprAST::EType InType, const FRigVMASTProxy& InProxy)` — make function to create an expression
- L1280 _private function_ `template<class ExprType> ExprType* MakeExpr(FRigVMExprAST::EType InType, const FRigVMASTLinkDescription& InLink)` — make function to create an expression
- L1290 _private function_ `template<class ExprType> ExprType* MakeExpr(FRigVMExprAST::EType InType, const FRigVMASTProxy& InProxyA, const FRigVMASTProxy& InProxyB)` — make function to create an expression
- L1300 _private function_ `template<class ExprType> ExprType* MakeExpr(const FRigVMASTProxy& InProxyA, const FRigVMASTProxy& InProxyBB)` — make function to create an expression
- L1310 _private function_ `template<class ExprType> ExprType* MakeExpr(const FRigVMASTProxy& InProxy)` — make function to create an expression
- L1320 _private function_ `template<class ExprType> ExprType* MakeExpr(const FRigVMASTLinkDescription& InLink)` — make function to create an expression
- L1330 _private function_ `template<class ExprType> ExprType* MakeExpr()` — make function to create an expression
- L1340 _private prototype_ `void RemoveExpressions(TArray<FRigVMExprAST*> InExprs);` — removes an array of expressions from the parser @param InExprs the expressions to remove
- L1347 _private prototype_ `static void TraverseParents(const FRigVMExprAST* InExpr, TFunctionRef<bool(const FRigVMExprAST*)> InContinuePredicate);` — a static helper function to traverse along all parents of an expression, provided a predicate to return true if the traverse should continue, and false if the traverse should stop. @param InExpr the expression to start the traverse at @param InContinuePredicate the predicate to use to break out of the traverse (return false)
- L1354 _private prototype_ `static void TraverseChildren(const FRigVMExprAST* InExpr, TFunctionRef<bool(const FRigVMExprAST*)> InContinuePredicate);` — a static helper function to traverse along all children of an expression, provided a predicate to return true if the traverse should continue, and false if the traverse should stop. @param InExpr the expression to start the traverse at @param InContinuePredicate the predicate to use to break out of the traverse (return false)
- L1357 _private prototype_ `void FoldEntries();` — helper function to fold all entries with the same event name into one block
- L1360 _private prototype_ `void InjectExitsToEntries();` — helper function to inject an exit expression at the end of every entry expressoin
- L1363 _private prototype_ `void RefreshExprIndices();` — helper function to refresh the expression indices (used after deleting an expression)
- L1366 _private prototype_ `void FoldNoOps();` — helper function to fold / remove the no op expressions (parameters mostly)
- L1369 _private prototype_ `void FoldLiterals();` — helper function to fold / merge redundant literals with the same value
- L1372 _private prototype_ `void FoldAssignments();` — helper function to fold / remove obsolete assignments and reduce assignment chains
- L1375 _private prototype_ `void FoldSubPinCopies();` — helper function to fold / remove obsolete copies from a sub pin to a root pin
- L1378 _private prototype_ `void Inline(const TArray<URigVMGraph*>& InGraphs);` — helper function to inline all contributing nodes of the graph
- L1379 _private prototype_ `void Inline(const TArray<URigVMGraph*>& InGraphs, const TArray<FRigVMASTProxy>& InNodeProxies);`
- L1382 _private prototype_ `TArray<int32> GetSourceLinkIndices(const FRigVMASTProxy& InPinProxy, bool bRecursive = false) const;` — helper functions to retrieve links for a given pin
- L1383 _private prototype_ `TArray<int32> GetTargetLinkIndices(const FRigVMASTProxy& InPinProxy, bool bRecursive = false) const;`
- L1384 _private prototype_ `TArray<int32> GetLinkIndices(const FRigVMASTProxy& InPinProxy, bool bGetSource, bool bRecursive) const;`
- L1387 _private prototype_ `const FRigVMASTLinkDescription& GetLink(int32 InLinkIndex) const;` — function to retrieve a link given its index
- L1390 _private prototype_ `FRigVMExprAST* TraverseMutableNode(const FRigVMASTProxy& InNodeProxy, FRigVMExprAST* InParentExpr);` — traverse a single mutable node (constructs entry, call extern and other expressions)
- L1393 _private prototype_ `FRigVMExprAST* TraverseNode(const FRigVMASTProxy& InNodeProxy, FRigVMExprAST* InParentExpr);` — traverse a single pure node (constructs call extern expressions)
- L1396 _private prototype_ `FRigVMExprAST* CreateExpressionForNode(const FRigVMASTProxy& InNodeProxy, FRigVMExprAST* InParentExpr);` — returns the expression for a given node
- L1399 _private prototype_ `TArray<FRigVMExprAST*> TraversePins(const FRigVMASTProxy& InNodeProxy, FRigVMExprAST* InParentExpr);` — traverse an array of pins for a given node
- L1402 _private prototype_ `FRigVMExprAST* TraversePin(const FRigVMASTProxy& InPinProxy, FRigVMExprAST* InParentExpr);` — traverse a single pin (constructs var + literal expressions)
- L1405 _private prototype_ `FRigVMExprAST* TraverseLink(int32 InLinkIndex, FRigVMExprAST* InParentExpr);` — traverse a single link (constructs assign + copy expressions)
- L1407 _private prototype_ `bool TraverseNodeExpressionForRequiredVariableClone(FRigVMNodeExprAST* InNodeExpr);`
- L1409 _private prototype_ `bool ShouldLinkBeSkipped(const FRigVMASTLinkDescription& InLink) const;`
- L1411 _private prototype_ `static FString GetLinkAsString(const FRigVMASTLinkDescription& InLink);`
- L1413 _private prototype_ `void IncrementCacheVersion() const;`
- L1415 _private prototype_ `static bool IsNoOpUnitNode(const URigVMNode* InNode);`
- L1416 _private prototype_ `static bool IsConstantDispatchNode(const URigVMNode* InNode);`
- L1417 _private prototype_ `static bool IsConstantDispatchValuePin(const URigVMPin* InPin);`
- L1418 _private prototype_ `static bool IsMakeStructDispatchNode(const URigVMNode* InNode);`
- L1419 _private prototype_ `static bool IsMakeStructDispatchElementsPin(const URigVMPin* InPin);`
- L1420 _private prototype_ `static bool IsMakeStructDispatchStructPin(const URigVMPin* InPin);`
- L1421 _private prototype_ `static bool IsBreakStructDispatchNode(const URigVMNode* InNode);`
- L1422 _private prototype_ `static bool IsBreakStructDispatchStructPin(const URigVMPin* InPin);`
- L1423 _private prototype_ `static bool IsBreakStructDispatchElementsPin(const URigVMPin* InPin);`
- L1425 _private prototype_ `static bool IsFloatOrFloatArrayPinOnVariable(const URigVMPin* InPin);`
- L1427 _private member_ `TMap<FRigVMASTProxy, FRigVMExprAST*> SubjectToExpression;`
- L1428 _private member_ `TMap<FRigVMASTProxy, int32> NodeExpressionIndex;`
- L1429 _private member_ `TArray<FRigVMExprAST*> Expressions;`
- L1430 _private member_ `TArray<FRigVMExprAST*> RootExpressions;`
- L1431 _private member_ `TArray<FRigVMExprAST*> DeletedExpressions;`
- L1432 _private member_ `FRigVMBlockExprAST* ObsoleteBlock;`
- L1433 _private member_ `mutable TMap<uint32, FString> BlockCombinationHashToName;`
- L1434 _private member_ `mutable int32 CacheVersion;`
- L1436 _private member_ `TArray<FRigVMASTProxy> NodeProxies;`
- L1437 _private member_ `TMap<FRigVMASTProxy, FRigVMASTProxy> SharedOperandPins;`
- L1438 _private member_ `TMap<FRigVMASTProxy, TArray<int32>> TargetLinkIndices;`
- L1439 _private member_ `TMap<FRigVMASTProxy, TArray<int32>> SourceLinkIndices;`
- L1440 _private member_ `TArray<FRigVMASTLinkDescription> Links;`
- L1441 _private member_ `static const TArray<FRigVMASTProxy> EmptyProxyArray;`
- L1442 _private member_ `URigVMPin::FPinOverrideMap PinOverrides;`
- L1452 _private member_ `const FRigVMExprAST* LastCycleCheckExpr;`
- L1453 _private member_ `TArray<ETraverseRelationShip> CycleCheckFlags;`
- L1454 _private member_ `TArray<URigVMLink*> LinksToSkip;`
- L1456 _private member_ `FRigVMParserASTSettings Settings;`
- L1457 _private member_ `mutable TMap<TTuple<const FRigVMExprAST*,const FRigVMExprAST*>, int32> MinIndexOfChildWithinParent;`
- L1459 _private member_ `URigVMLibraryNode* LibraryNodeBeingCompiled;`

#### enum `FRigVMParserAST::ETraverseRelationShip`  
`enum ETraverseRelationShip`  
_L1444-1450_
- L1446 _public enumerator_ `ETraverseRelationShip_Unknown`
- L1447 _public enumerator_ `ETraverseRelationShip_Parent`
- L1448 _public enumerator_ `ETraverseRelationShip_Child`
- L1449 _public enumerator_ `ETraverseRelationShip_Self`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API RIGVMDEVELOPER_API`

### `Plugins/Runtime/RigVM/Source/RigVMDeveloper/Public/RigVMCompiler/RigVMASTProxy.h` (Public)


#### class `FRigVMCallstack`  
`class FRigVMCallstack`  
_L15-128_
- desc: A stack describing the model object which led to this invocation. Objects on the stack can be URigVMGraph or URigVMNode.
- L20 _public prototype_ `FString GetCallPath(bool bIncludeLast = true) const;` — Returns the path
- L23 _public prototype_ `int32 Num() const;` — Returns the number of entries on this callstack
- L26 _public prototype_ `const UObject* Last() const;` — Returns the last object in the callstack
- L29 _public prototype_ `const UObject* operator[](int32 InIndex) const;` — Returns the element at a given index
- L32 _public prototype_ `bool Contains(const UObject* InEntry) const;` — Returns true if the stack contains a given entry
- L39 _public function_ `bool operator ==(const FRigVMCallstack& Other) const`
- L55 _public function_ `bool operator !=(const FRigVMCallstack& Other) const`
- L60 _public function_ `bool operator <(const FRigVMCallstack& Other) const`
- L80 _public function_ `bool operator >(const FRigVMCallstack& Other) const`
- L100 _public function_ `TArray<TWeakObjectPtr<UObject>> GetStack() const`
- L102 _public prototype_ `FRigVMCallstack GetCallStackUpTo(int32 InIndex) const;`
- L106 _private function_ `uint32 GetEntryTypeHash(int32 Index) const`
- L122 _private member_ `TArray<TWeakObjectPtr<UObject>> Stack;`

#### class `FRigVMASTProxy`  
`class FRigVMASTProxy`  
_L135-257_
- desc: A proxy which describes an occurence of a subject within a graph. The subject can be a pin, a node, a link, etc. The context is the callstack under which is occured.
- L139 _public function_ `FRigVMASTProxy()`
- L147 _public function_ `FRigVMASTProxy(const FRigVMASTProxy& InOther)`
- L155 _public function_ `FRigVMASTProxy& operator=(const FRigVMASTProxy& InOther)`
- L167 _public prototype_ `static FRigVMASTProxy MakeFromUObject(UObject* InSubject);`
- L168 _public prototype_ `static FRigVMASTProxy MakeFromCallPath(const FString& InCallPath, UObject* InRootObject);`
- L169 _public prototype_ `static FRigVMASTProxy MakeFromCallstack(const FRigVMCallstack& InCallstack);`
- L170 _public prototype_ `static FRigVMASTProxy MakeFromCallstack(const TArray<TWeakObjectPtr<UObject>>* InCallstack);`
- L172 _public function_ `FRigVMASTProxy GetSibling(UObject* InSubject) const`
- L182 _public function_ `FRigVMASTProxy GetParent() const`
- L194 _public function_ `FRigVMASTProxy GetChild(UObject* InSubject) const`
- L210 _public function_ `const FRigVMCallstack& GetCallstack() const`
- L212 _public function_ `UObject* GetSubject() const`
- L215 _public function_ `template<class T> T* GetSubject() const`
- L218 _public function_ `template<class T> T* GetSubjectChecked() const`
- L220 _public function_ `bool IsValid() const`
- L223 _public function_ `template<class T> bool IsA() const`
- L230 _public function_ `bool operator ==(const FRigVMASTProxy& Other) const`
- L235 _public function_ `bool operator !=(const FRigVMASTProxy& Other) const`
- L240 _public function_ `bool operator <(const FRigVMASTProxy& Other) const`
- L245 _public function_ `bool operator >(const FRigVMASTProxy& Other) const`
- L253 _private member_ `FString DebugName;`
- L256 _private member_ `FRigVMCallstack Callstack;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API RIGVMDEVELOPER_API`
- L34 _function_ `friend uint32 GetTypeHash(const FRigVMCallstack& Callstack)`
- L225 _function_ `friend uint32 GetTypeHash(const FRigVMASTProxy& Proxy)`
- L259 _typedef_ `typedef TPair<FRigVMASTProxy, FRigVMASTProxy> FRigVMPinProxyPair;`
- L260 _typedef_ `typedef TMap<FRigVMASTProxy, FString> FRigVMPinDefaultValueOverride;`

### `Plugins/Runtime/RigVM/Source/RigVMDeveloper/Public/RigVMCompiler/RigVMCodeConverter.h` (Public)


#### struct `FRigVMCodeConversionSettings`  
`struct FRigVMCodeConversionSettings`  
_L14-33_
- desc: Settings for RigVM code conversion/nativization.
- L16 _public function_ `FRigVMCodeConversionSettings() : TargetModule(TEXT("Test")) , bWriteFiles(false)`
- L23 _public member_ `FString TargetModule;` — Name of the UE module where generated code will be placed.
- L26 _public member_ `FString OutputFolder;` — Directory where generated files should be written.
- L29 _public member_ `FString JsonFilePath;` — Optional path to write the intermediate JSON representation (for debugging).
- L32 _public member_ `bool bWriteFiles;` — If true, generated files are written to disk automatically.

#### class `FRigVMCodeConverter`  
`class FRigVMCodeConverter`  
_L90-346_
- desc: Converts RigVM bytecode into a JSON representation for template rendering. FRigVMCodeConverter is the core of the nativization pipeline. It parses a compiled RigVM's bytecode and produces a comprehensive JSON structure that Inja templates can use to generate C++ source code. ## Conversion Pipeline 1. **Construction**: Parses the VM's bytecode in a 14-step process: - External variables, memory layouts (literal/work) - Property paths, callables, blocks, entries - Instructions with operand resolution - Dependency tracking (includes, libraries) 2. **Render**: Combines the JSON with an Inja template to produce C++ code. ## JSON Structure Overview The generated JSON contains: - `AssetName`: Name of the source asset - `VMHash`: Hash for validation - `Variables`: External variable definitions - `Memory.Literal`: Constant/default values - `Memory.Work`: Runtime temporaries - `Functions`: Unit functions and dispatch factories - `Blocks`: Control flow blocks (branches) - `Callables`: User-defined callable functions - `Entries`: Entry points into the VM - `Instructions`: Bytecode instructions with resolved operands - `Includes`: Required C++ header files - `Libraries`: Required UE module dependencies ## Usage @code FRigVMCodeConversionSettings Settings; Settings.TargetModule = TEXT("MyGame"); Settings.OutputFolder = TEXT("Source/MyGame/Generated"); auto Converter = MakeShared<FRigVMCodeConverter>(EditorAsset, Settings); if (Converter->HasError()) { // Handle conversion failure return; } 
- L102 _public prototype_ `FRigVMCodeConverter(IRigVMEditorAssetInterface* InEditorAsset, const FRigVMCodeConversionSettings& InSettings);` — Constructs a converter and parses the VM's bytecode into JSON. This is a potentially expensive operation that analyzes the entire VM. Check HasError() after construction to verify success. @param InEditorAsset The editor asset containing the RigVM to nativize. @param InSettings Conversion settings (target module, output paths, etc.).
- L105 _public prototype_ `FString GetAssetName() const;` — Returns the sanitized asset name used for generated class names.
- L113 _public prototype_ `TSharedPtr<FRigVMCodeOutput> Render(const TSharedPtr<FRigVMCodeTemplate>& InTemplate);` — Renders a template using the parsed JSON data. @param InTemplate The template to render. @return The rendered output with content and metadata.
- L116 _public function_ `bool HasError() const` — Returns true if an error occurred during construction or rendering.
- L119 _public function_ `const inja::json& GetJson() const` — Returns the parsed JSON representation of the VM (for debugging/inspection).
- L128 _private prototype_ `inja::json ToJson(const FRigVMGraphVariableDescription& InVariable);` — Converts an external variable description to JSON.
- L131 _private prototype_ `inja::json ToJson(const FRigVMFunction* InFunction);` — Converts a function (unit or dispatch) to JSON.
- L134 _private prototype_ `inja::json ToJson(const FRigVMBranchInfo& InBlock);` — Converts a branch/block to JSON.
- L137 _private prototype_ `inja::json ToJson(const FRigVMPredicateBranch& InPredicateBranch);` — Converts a predicate branch to JSON.
- L140 _private prototype_ `inja::json ToJson(const FRigVMCallableInfo* InCallable);` — Converts a callable (user function) to JSON.
- L143 _private prototype_ `inja::json ToJson(const FRigVMCallableArgument& InCallableArgument);` — Converts a callable argument to JSON.
- L146 _private prototype_ `inja::json ToJson(const FRigVMInstructionArray& InInstructions, int32 InFirstIndex, int32 InLastIndex);` — Converts a range of instructions to JSON.
- L149 _private prototype_ `inja::json ToJson(const FRigVMInstruction& InInstruction);` — Converts a single instruction to JSON.
- L152 _private prototype_ `inja::json ToJson(const FRigVMMemoryStorageStruct& InMemoryStorageStruct);` — Converts a memory storage struct (literal or work memory) to JSON.
- L155 _private prototype_ `inja::json ToJson(const FRigVMPropertyPath& InPropertyPaths);` — Converts a property path to JSON.
- L158 _private prototype_ `inja::json ToJson(ERigVMPinDirection InDirection, const FProperty* InProperty, const FString& InDefaultValue, int32 InMemoryType);` — Converts a property with direction and default value to JSON.
- L161 _private prototype_ `inja::json ToJson(const FRigVMOperand& InOperand, const ERigVMPinDirection& InDirection, int32 InInstructionIndex);` — Converts an operand reference to JSON with access expression.
- L169 _private function_ `template<typename EnumType> static inja::json ToJson(int64 InEnumValue, bool bTrimWhiteSpace = false)` — Converts an enum value to its display name as JSON.
- L176 _private prototype_ `static inja::json ToJson(const UEnum* InEnum, int64 InEnumValue, bool bTrimWhiteSpace = false);` — Converts an enum value to its display name as JSON.
- L179 _private prototype_ `static inja::json ToJson(const FString& InString);` — Converts FString to inja::json (UTF-8 encoded).
- L182 _private prototype_ `static inja::json ToJson(const FName& InName);` — Converts FName to inja::json.
- L185 _private prototype_ `static inja::json ToJson(const FText& InText);` — Converts FText to inja::json.
- L188 _private prototype_ `static FString FromJson(const inja::json& InJson);` — Converts inja::json to FString.
- L191 _private prototype_ `static FString FromJson(const std::string& InJson);` — Converts std::string to FString.
- L203 _private prototype_ `inja::json GetLazyBlocks(int32 InFirstInstruction, int32 InLastInstruction, int32 CallableIndex, int32 BlockIndex);` — Extracts lazy block information for a range of instructions. Lazy values are evaluated on-demand rather than eagerly. This method identifies which blocks contain lazy values and how to access them.
- L218 _private prototype_ `bool ProcessDependency(const UObject* InObject);` — Processes a type dependency and extracts include/library requirements. For native UE types, extracts the header path and module name. Returns false for non-native types (which cannot be nativized). @param InObject The UObject (typically UStruct, UClass, or UEnum) to process. @return True if the dependency is valid for nativization.
- L221 _private prototype_ `void ProcessInclude(const FString& InInclude);` — Adds an include path to the includes list.
- L228 _private prototype_ `static FString SanitizeName(const FString& InString);` — Converts a string to a valid C++ identifier (replaces invalid chars with '_').
- L231 _private prototype_ `FString SanitizeNativeType(const FString& InString) const;` — Sanitizes a native type name, handling 2D array remapping.
- L234 _private prototype_ `FString SanitizePropertyName(const FString& InString, int32 InMemoryType);` — Sanitizes a property name, ensuring uniqueness within a memory type.
- L241 _private prototype_ `static uint32 GetPropertyPathHash(const FRigVMPropertyPath& InPropertyPath);` — Computes a hash for a property path (used for deduplication).
- L244 _private prototype_ `void GetNativePathForProperty(const FProperty* InProperty, inja::json& OutJsonObject);` — Populates JSON object with native path information for a property.
- L247 _private prototype_ `inja::json GetNativePath(const UObject* InObject);` — Gets the native path (UObject path name) as JSON.
- L250 _private prototype_ `FString GetNativeTypeForOperand(const FRigVMOperand& InOperand, int32 InInstructionIndex) const;` — Resolves the C++ type string for an operand.
- L254 _private function_ `template<typename T> const T* FindObjectFromNativePath(const FString& InNativePath) const` — Finds a UObject by its native path (cached lookup).
- L260 _private prototype_ `const UObject* FindObjectFromNativePath(const FString& InNativePath) const;` — Finds a UObject by its native path (cached lookup).
- L267 _private member_ `IRigVMEditorAssetInterface* EditorAsset = nullptr;` — The editor asset being converted.
- L270 _private member_ `inja::json Json;` — The complete JSON representation of the VM.
- L273 _private member_ `FRigVMCodeConversionSettings Settings;` — Conversion settings.
- L276 _private member_ `TArray<FString> Includes;` — Accumulated include paths for generated code.
- L279 _private member_ `TArray<FString> Libraries;` — Accumulated library/module dependencies.
- L282 _private member_ `TSet<const UObject*> KnownDependencies;` — Set of already-processed dependencies (avoids duplicates).
- L285 _private member_ `FString PackageName;` — Sanitized package name (used for class naming).
- L288 _private member_ `URigVM* VM = nullptr;` — The RigVM being converted.
- L291 _private member_ `const FRigVMByteCode* ByteCode = nullptr;` — Direct reference to VM's bytecode.
- L294 _private member_ `TArray<FRigVMBranchInfo> Blocks;` — All blocks (branches) including synthesized RunInstruction blocks.
- L297 _private member_ `FRigVMInstructionArray Instructions;` — All instructions from bytecode.
- L300 _private member_ `TArray<int32> BlockIndexPerInstruction;` — Maps instruction index -> containing block index.
- L303 _private member_ `TArray<int32> CallableIndexPerInstruction;` — Maps instruction index -> containing callable index.
- L306 _private member_ `TMap<TTuple<int32,int32>, int32> RunInstructionBranches;` — Maps (first instruction, last instruction) -> branch info index for RunInstruction blocks.
- L309 _private member_ `TSet<TTuple<int32,FString>> UniquePropertyNames;` — Tracks unique property names per memory type for deduplication.
- L312 _private member_ `TMap<TTuple<int32,int32>, int32> PropertyMap;` — Maps (memory type, register index) -> exported property index.
- L315 _private member_ `TMap<TTuple<int32,int32>, TTuple<int32, int32, FName>> CallableArgumentMap;` — Maps (memory type, register index) -> (callable index, argument index, argument name).
- L318 _private member_ `TMap<uint32, int32> PropertyPathMap;` — Maps property path hash -> property path index.
- L321 _private member_ `TMap<const void*, int32> FunctionIndexMap;` — Maps function pointer -> function index (for deduplication).
- L324 _private member_ `TMap<int32, TSharedPtr<FRigVMFunction>> InstructionToCustomFunction;` — Maps instruction index -> custom function (for dispatch permutations).
- L327 _private member_ `TMap<uint32, TSharedPtr<FRigVMFunction>> HashToCustomFunction;` — Maps type hash -> custom function (for dispatch permutations).
- L330 _private member_ `TSet<TTuple<int32,int32>> LazyFunctionArguments;` — Set of (function index, argument index) pairs that are lazy values.
- L333 _private member_ `mutable TMap<FString, const UObject*> NativePathMap;` — Cache: native path string -> UObject.
- L336 _private member_ `mutable TMap<FString, FString> NativeTypeMap;` — Cache: original type -> sanitized type (for 2D array remapping).
- L339 _private member_ `mutable TArray<TTuple<FString,FString>> LazyProperties;` — Accumulated lazy property definitions.
- L342 _private member_ `bool bHasError = false;` — True if an error occurred during conversion.

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API RIGVMDEVELOPER_API`

### `Plugins/Runtime/RigVM/Source/RigVMDeveloper/Public/RigVMCompiler/RigVMCodeEnvironment.h` (Public)


#### class `FRigVMCodeEnvironment`  
`class FRigVMCodeEnvironment : public inja::Environment`  
_L60-241_
- inherits: `inja::Environment`
- desc: Custom Inja template environment providing C++ code generation helpers. Extends inja::Environment to register custom callback functions that can be invoked from within Inja templates. These functions handle UE-specific types, indentation management, and C++ code generation patterns. ## Template Function Reference ### String Utilities - `sanitize(name)` - Converts a name to a valid C++ identifier - `starts_with(str, prefix)` - Returns true if str starts with prefix - `ends_with(str, suffix)` - Returns true if str ends with suffix - `remove_whitespace(str)` - Removes all spaces and tabs from str - `format_number(format, value)` - Printf-style number formatting (e.g., "%04d") ### Indentation Management - `tabs()` - Returns current indentation as tab characters - `inc_tabs()` - Increases indentation level by 1 (void, no return) - `dec_tabs()` - Decreases indentation level by 1 (void, no return) ### JSON Utilities - `has_key(object, key)` - Returns true if object contains key with truthy value - `count_key(array, key)` - Counts array elements that contain key with truthy value ### C++ Code Generation - `cpp_get_default_for_native_type(type)` - Returns default value for a C++ type (e.g., "FVector" -> "FVector::ZeroVector", "bool" -> "true") - `cpp_get_initialize_code_for_property(memType, name, origName, nativeType, nativePath, default)` Returns array of C++ initialization statements for a property - `cpp_get_block_to_run_operand(instruction)` - Resolves the BlockToRun operand for 
- L69 _public prototype_ `FRigVMCodeEnvironment(const FString& InTemplateFolder, FRigVMCodeConverter* InConverter);` — Constructs the environment and registers all custom template functions. @param InTemplateFolder Base folder for template includes (passed to inja::Environment). @param InConverter Back-reference to converter for context-dependent lookups.
- L78 _private prototype_ `static inja::json sanitize(inja::Renderer* InRenderer, inja::Arguments& InArguments);` — Sanitizes a string to be a valid C++ identifier. Replaces invalid chars with '_'.
- L81 _private prototype_ `static inja::json starts_with(inja::Renderer* InRenderer, inja::Arguments& InArguments);` — Returns true if Arg0 starts with Arg1.
- L84 _private prototype_ `static inja::json ends_with(inja::Renderer* InRenderer, inja::Arguments& InArguments);` — Returns true if Arg0 ends with Arg1.
- L87 _private prototype_ `static inja::json remove_whitespace(inja::Renderer* InRenderer, inja::Arguments& InArguments);` — Removes all whitespace (spaces and tabs) from Arg0.
- L90 _private prototype_ `static inja::json format_number(inja::Renderer* InRenderer, inja::Arguments& InArguments);` — Printf-style formatting: format_number("%04d", 42) -> "0042".
- L97 _private prototype_ `inja::json tabs(inja::Renderer* InRenderer, inja::Arguments& InArguments);` — Returns the current indentation as a string of tab characters.
- L100 _private prototype_ `void inc_tabs(inja::Renderer* InRenderer, inja::Arguments& InArguments);` — Increments the indentation level.
- L103 _private prototype_ `void dec_tabs(inja::Renderer* InRenderer, inja::Arguments& InArguments);` — Decrements the indentation level.
- L110 _private prototype_ `static inja::json has_key(inja::Renderer* InRenderer, inja::Arguments& InArguments);` — Returns true if Arg0 (object) contains Arg1 (key) with a truthy value.
- L113 _private prototype_ `static inja::json count_key(inja::Renderer* InRenderer, inja::Arguments& InArguments);` — Counts elements in Arg0 (array) that contain Arg1 (key) with a truthy value.
- L130 _private prototype_ `inja::json cpp_get_default_for_native_type(inja::Renderer* InRenderer, inja::Arguments& InArguments);` — Returns the default value expression for a C++ native type. Examples: - "bool" -> "true" - "float" -> "0.f" - "FVector" -> "FVector::ZeroVector" - "FTransform" -> "FTransform::Identity" - Enum types -> "(EnumType)0" - Pointers -> "nullptr"
- L145 _private prototype_ `inja::json cpp_get_initialize_code_for_property(inja::Renderer* InRenderer, inja::Arguments& InArguments);` — Generates C++ initialization code for a property. Handles complex types like structs, arrays, enums with proper initialization syntax. Returns an array of code lines that can be iterated in templates. @param Arg0 Memory type string ("Literal" or "Work") @param Arg1 Sanitized property name @param Arg2 Original property name @param Arg3 Native C++ type @param Arg4 Native path for type lookup @param Arg5 Default value string
- L155 _private prototype_ `inja::json cpp_get_block_to_run_operand(inja::Renderer* InRenderer, inja::Arguments& InArguments);` — Resolves the BlockToRun operand for Execute instructions with control flow. Used to generate the operand access expression for instructions that branch to different blocks based on runtime values. @param Arg0 Instruction JSON object (must have Index and Operands keys)
- L168 _private prototype_ `inja::json cpp_is_default_value(inja::Renderer* InRenderer, inja::Arguments& InArguments);` — Checks if a property's default value matches the header inline default. Used to skip redundant constructor initialization when the value equals what the header already initializes to. This reduces code size and improves constructor performance. @param Arg0 Native C++ type (e.g., "FVector", "FTransform", "bool") @param Arg1 Default value string to check @return true if the value matches the header default and can be skipped
- L175 _private prototype_ `static inja::json ToJson(const FString& InString);` — Converts FString to inja::json.
- L178 _private prototype_ `static inja::json ToJson(const FName& InName);` — Converts FName to inja::json.
- L181 _private prototype_ `static inja::json ToJson(const FText& InText);` — Converts FText to inja::json.
- L184 _private prototype_ `static FString FromJson(const inja::json& InJson);` — Converts inja::json to FString.
- L187 _private prototype_ `static FString FromJson(const std::string& InJson);` — Converts std::string to FString.
- L194 _private member_ `int32 Tabs = 0;` — Current indentation level for tabs() output.
- L197 _private member_ `FRigVMCodeConverter* Converter = nullptr;` — Back-reference to converter for type lookups and bytecode access.
- L200 _private member_ `TMap<FString, UObject*> NativeTypeLookup;` — Local cache for looking up native types by name
- L203 _private member_ `inline static const TSet<FString> IntegerTypes = {TEXT("uint8"), TEXT("uint16"), TEXT("uint32"), TEXT("uint64"), TEXT("i` — Set of C++ integer type names for default value lookup.
- L206 _private member_ `inline static const TMap<FString, FString> NativeTypeDefaults = { {TEXT("bool"), TEXT("true")}, {TEXT("float"), TEXT("0.f")}, {TEXT("double"), TEXT("0.0")}, {TEXT("uint8"), TEXT("0")}, {TEXT("uint16"), TEXT("0")}, {TEXT("uint32"), TEXT("0")}, {TEXT("uint64"), TEXT("0")}, {TEXT("int16"), TEXT("0")}, {TEXT("int32"), TEXT("0")}, {TEXT("int64"), TEXT("0")}, {TEXT("FName"), TEXT("NAME_None")}, {TEXT("FVector2D"), TEXT("FVector2D::ZeroVector")}, {TEXT("FVector"), TEXT("FVector::ZeroVector")}, {TEXT("FQuat"), TEXT("FQuat::Identity")}, {TEXT("FRotator"), TEXT("FRotator::ZeroRotator")}, {TEXT("FTransform"), TEXT("FTransform::Identity")}, {TEXT("FEulerTransform"), TEXT("FEulerTransform::Identity")}, {TEXT("FMatrix"), TEXT("FMatrix::Identity")}, {TEXT("FLinearColor"), TEXT("FLinearColor(ForceInitToZero)")} };` — Map of native type names to their default value expressions. O(1) lookup.
- L228 _private member_ `inline static const FLinearColor DefaultLinearColor = FLinearColor(ForceInitToZero);`
- L231 _private member_ `inline static const TMap<FString, const void*> NativeStructTypeDefaults = { {TEXT("FVector2D"), &FVector2D::ZeroVector}, {TEXT("FVector"), &FVector::ZeroVector}, {TEXT("FQuat"), &FQuat::Identity}, {TEXT("FRotator"), &FRotator::ZeroRotator}, {TEXT("FTransform"), &FTransform::Identity}, {TEXT("FEulerTransform"), &FEulerTransform::Identity}, {TEXT("FMatrix"), &FMatrix::Identity}, {TEXT("FLinearColor"), &DefaultLinearColor} };` — Map of native type names to their default value expressions. O(1) lookup.

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API RIGVMDEVELOPER_API`

### `Plugins/Runtime/RigVM/Source/RigVMDeveloper/Public/RigVMCompiler/RigVMCodeGenerator.h` (Public)


#### enum `ERigVMCodeLanguage::Type`  
`enum Type : uint8`  
_L14-21_
- L17 _public enumerator_ `CPlusPlus` — Generate C++ source files (.h and .cpp).
- L20 _public enumerator_ `Verse` — Generate Verse source files (not yet implemented).

#### struct `FRigVMCodeGenerator`  
`struct FRigVMCodeGenerator`  
_L50-108_
- desc: Discovers and manages code generation templates for a target language. FRigVMCodeGenerator is responsible for: - Discovering template files from the Content/CodeGeneration/{Language}/ directory - Providing access to templates by name - Orchestrating code generation by combining a converter with templates Usage: @code // Create generator for C++ FRigVMCodeGenerator Generator(ERigVMCodeLanguage::CPlusPlus); // Create converter from a RigVM asset auto Converter = MakeShared<FRigVMCodeConverter>(EditorAsset, Settings); // Generate all output files TArray<TSharedPtr<FRigVMCodeOutput>> Outputs = Generator.GenerateAll(Converter); // Or generate a specific template auto Output = Generator.Generate(Converter, TEXT("AssetNameVM.h.template")); @endcode @see FRigVMCodeConverter for bytecode parsing and JSON generation @see FRigVMCodeTemplate for template file representation
- L62 _public prototype_ `FRigVMCodeGenerator(ERigVMCodeLanguage::Type InLanguage);` — Constructs a generator and discovers all templates for the specified language. Templates are loaded from: Content/CodeGeneration/{LanguageName}/{FileName}.template For C++, this is: Content/CodeGeneration/CPlusPlus/{FileName}.template @param InLanguage The target language for code generation.
- L65 _public prototype_ `int32 NumTemplates() const;` — Returns the number of discovered templates.
- L73 _public prototype_ `const TSharedPtr<FRigVMCodeTemplate>& GetTemplate(const FString& InName) const;` — Retrieves a template by name. @param InName Template name (e.g., "AssetNameVM.h.template"). @return The template, or an invalid shared pointer if not found.
- L82 _public prototype_ `TSharedPtr<FRigVMCodeOutput> Generate(const TSharedPtr<FRigVMCodeConverter>& InConverter, const FString& InTemplateName) const;` — Generates output from a single template. @param InConverter The converter containing parsed bytecode as JSON. @param InTemplateName Name of the template to render. @return The rendered output, or nullptr if the template was not found.
- L91 _public prototype_ `static TSharedPtr<FRigVMCodeOutput> Generate(const TSharedPtr<FRigVMCodeConverter>& InConverter, const TSharedPtr<FRigVMCodeTemplate>& InCodeTemplate);` — Generates output from a template (static version). @param InConverter The converter containing parsed bytecode as JSON. @param InCodeTemplate The template to render. @return The rendered output.
- L99 _public prototype_ `TArray<TSharedPtr<FRigVMCodeOutput>> GenerateAll(const TSharedPtr<FRigVMCodeConverter>& InConverter) const;` — Generates output from all discovered templates. @param InConverter The converter containing parsed bytecode as JSON. @return Array of rendered outputs, one per template.
- L104 _private member_ `ERigVMCodeLanguage::Type Language;` — The target language for this generator.
- L107 _private member_ `TArray<TSharedPtr<FRigVMCodeTemplate>> CodeTemplates;` — All discovered templates for the target language.

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API RIGVMDEVELOPER_API`
- L12 _namespace_ `namespace ERigVMCodeLanguage`

### `Plugins/Runtime/RigVM/Source/RigVMDeveloper/Public/RigVMCompiler/RigVMCodeTemplate.h` (Public)


#### struct `FRigVMCodeTemplate`  
`struct FRigVMCodeTemplate`  
_L21-40_
- desc: Represents an Inja template file used for code generation. Templates are lazily loaded from disk when first accessed. The template content is cached after loading to avoid repeated file I/O during rendering. Template files use Inja syntax (similar to Jinja2) and are typically stored in: Content/CodeGeneration/CPlusPlus/{FileName}.template @see FRigVMCodeOutput for rendered output handling @see FRigVMCodeGenerator for template discovery and rendering orchestration
- L24 _public prototype_ `void Load();` — Loads the template content from disk. Called automatically by LoadIfRequired().
- L27 _public prototype_ `void LoadIfRequired();` — Loads the template content if not already loaded. Thread-safe lazy initialization.
- L30 _public prototype_ `const FString& GetContent() const;` — Returns the template content. Triggers lazy load if needed.
- L33 _public member_ `FString Name;` — Template identifier (e.g., "AssetNameVM.h" or "AssetNameVM.cpp").
- L36 _public member_ `FString FilePath;` — Absolute path to the template file on disk.
- L39 _public member_ `mutable TOptional<FString> Content;` — Lazily-loaded template content. Mutable to allow const GetContent() to trigger load.

#### struct `FRigVMCodeOutput`  
`struct FRigVMCodeOutput : public FRigVMCodeTemplate`  
_L53-73_
- inherits: `FRigVMCodeTemplate`
- desc: Represents the result of rendering a code template. Extends FRigVMCodeTemplate to hold both the rendered content and metadata about the output file. Can be saved to disk via Save(). After rendering: - Content holds the generated C++ code (inherited from FRigVMCodeTemplate) - ErrorMessage is set if rendering failed - bSaved tracks whether Save() was called and succeeded
- L63 _public prototype_ `bool Save() const;` — Writes the rendered content to disk. Output path is: OutputFolder / Name Sets bSaved to true on success, false on failure. @return True if the file was written successfully.
- L66 _public member_ `FString OutputFolder;` — Directory where the output file should be written.
- L69 _public member_ `FString ErrorMessage;` — Error message if rendering failed (empty on success).
- L72 _public member_ `TOptional<bool> bSaved;` — Tracks save state: unset = not attempted, true = succeeded, false = failed.

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API RIGVMDEVELOPER_API`

### `Plugins/Runtime/RigVM/Source/RigVMDeveloper/Public/RigVMCompiler/RigVMCompiler.h` (Public)


#### struct `FRigVMCompileSettings`  
`struct FRigVMCompileSettings`  
_L30-126_
- reflection: `USTRUCT(BlueprintType)`
- L36 _public prototype_ `FRigVMCompileSettings();`
- L38 _public prototype_ `FRigVMCompileSettings(UScriptStruct* InExecuteContextScriptStruct);`
- L40 _public function_ `UScriptStruct* GetExecuteContextStruct() const`
- L41 _public function_ `void SetExecuteContextStruct(UScriptStruct* InExecuteContextScriptStruct)`
- L44 _public member_ `bool SurpressInfoMessages;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FRigVMCompileSettings)`
- L47 _public member_ `bool SurpressWarnings;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FRigVMCompileSettings)`
- L50 _public member_ `bool SurpressErrors;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FRigVMCompileSettings)`
- L53 _public member_ `bool EnablePinWatches;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FRigVMCompileSettings)`
- L56 _public member_ `bool IsPreprocessorPhase;` — `UPROPERTY(Transient)`
- L59 _public member_ `FRigVMParserASTSettings ASTSettings;` — `UPROPERTY(EditAnywhere, Transient, BlueprintReadWrite, Category = FRigVMCompileSettings)`
- L62 _public member_ `bool SetupNodeInstructionIndex;` — `UPROPERTY()`
- L65 _public member_ `bool ASTErrorsAsNotifications;` — `UPROPERTY()`
- L68 _public member_ `bool bWarnAboutDeprecatedNodes;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, BlueprintReadWrite, Category = FRigVMCompileSettings)`
- L71 _public member_ `bool bWarnAboutDuplicateEvents;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, BlueprintReadWrite, Category = FRigVMCompileSettings)`
- L73 _public function_ `static FRigVMCompileSettings Fast(UScriptStruct* InExecuteContextStruct = nullptr)`
- L82 _public function_ `static FRigVMCompileSettings Optimized(UScriptStruct* InExecuteContextStruct = nullptr)`
- L91 _public prototype_ `void ReportInfo(const FString& InMessage) const;`
- L92 _public prototype_ `void ReportWarning(const FString& InMessage) const;`
- L93 _public prototype_ `void ReportError(const FString& InMessage) const;`
- L96 _public function_ `template <typename... Types> void ReportInfof(UE::Core::TCheckedFormatString<FString::FmtCharType, Types...> Fmt, Types... Args) const`
- L102 _public function_ `template <typename... Types> void ReportWarningf(UE::Core::TCheckedFormatString<FString::FmtCharType, Types...> Fmt, Types... Args) const`
- L108 _public function_ `template <typename... Types> void ReportErrorf(UE::Core::TCheckedFormatString<FString::FmtCharType, Types...> Fmt, Types... Args) const`
- L113 _public function_ `void Report(EMessageSeverity::Type InSeverity, UObject* InSubject, const FString& InMessage) const`
- L119 _public function_ `template <typename... Types> void Reportf(EMessageSeverity::Type InSeverity, UObject* InSubject, UE::Core::TCheckedFormatString<FString::FmtCharType, Types...> Fmt, Types... Args) const`

#### class `FRigVMCompileSettingsDuringLoadGuard`  
`class FRigVMCompileSettingsDuringLoadGuard`  
_L128-139_
- L132 _public function_ `FRigVMCompileSettingsDuringLoadGuard(FRigVMCompileSettings& InSettings) : ASTErrorsAsNotifications(InSettings.ASTErrorsAsNotifications, true)`
- L138 _private member_ `TGuardValue<bool> ASTErrorsAsNotifications;`

#### enum `ERigVMCompilerPhase`  
`enum ERigVMCompilerPhase : uint8`  
_L141-145_
- L143 _public enumerator_ `ERigVMCompilerPhase_SetupMemory`
- L144 _public enumerator_ `ERigVMCompilerPhase_BuildInstructions`

#### struct `FRigVMCompilerWorkData`  
`struct FRigVMCompilerWorkData`  
_L147-351_
- L150 _public member_ `URigVMCompiler* Compiler = nullptr;`
- L151 _public member_ `FRigVMCompileSettings Settings;`
- L152 _public member_ `ERigVMCompilerPhase CompilerPhase = ERigVMCompilerPhase_SetupMemory;`
- L153 _public member_ `URigVM* VM = nullptr;`
- L154 _public member_ `TArray<URigVMGraph*> Graphs;`
- L155 _public member_ `const URigVMLibraryNode* CurrentlyCompilingFunctionNode = nullptr;`
- L156 _public member_ `FRigVMFunctionCompilationData* FunctionCompilationData = nullptr;`
- L157 _public member_ `TMap<uint32,TMap<FRigVMOperand,FRigVMOperand>> OperandMapPerFunction;`
- L158 _public member_ `UScriptStruct* ExecuteContextStruct = nullptr;`
- L159 _public member_ `TMap<FString, FRigVMOperand>* PinPathToOperand = nullptr;`
- L160 _public member_ `FRigVMExtendedExecuteContext* Context = nullptr;`
- L161 _public member_ `TMap<const FRigVMVarExprAST*, FRigVMOperand> ExprToOperand;`
- L162 _public member_ `TMap<const FRigVMExprAST*, bool> ExprComplete;`
- L163 _public member_ `TArray<const FRigVMExprAST*> ExprToSkip;`
- L164 _public member_ `TArray<const FRigVMExprAST*> TraversalExpressions;`
- L165 _public member_ `TMap<FString, int32> ProcessedLinks;`
- L166 _public member_ `TMap<const URigVMNode*, FRigVMOperand> TraitListLiterals;`
- L167 _public member_ `FRigVMOperand ComparisonOperand;`
- L169 _public typedef_ `using FRigVMASTProxyArray = TArray<FRigVMASTProxy, TInlineAllocator<3>>;`
- L170 _public typedef_ `using FRigVMASTProxySourceMap = TMap<FRigVMASTProxy, FRigVMASTProxy>;`
- L171 _public typedef_ `using FRigVMASTProxyTargetsMap = TMap<FRigVMASTProxy, FRigVMASTProxyArray>;`
- L173 _public member_ `TMap<FRigVMASTProxy, FRigVMASTProxyArray> CachedProxiesWithSharedOperand;`
- L174 _public member_ `const FRigVMASTProxySourceMap* ProxySources = nullptr;`
- L175 _public member_ `FRigVMASTProxyTargetsMap ProxyTargets;`
- L176 _public member_ `TMap<URigVMNode*, TArray<FRigVMBranchInfo>> BranchInfos;`
- L184 _public function_ `friend inline uint32 GetTypeHash(const FFunctionRegisterData& Data)`
- L195 _public member_ `TMap<FFunctionRegisterData, FRigVMOperand> FunctionRegisterToOperand;`
- L197 _public member_ `TArray<URigVMPin*> WatchedPins;`
- L199 _public member_ `TMap<ERigVMMemoryType, TArray<FRigVMPropertyPathDescription>> PropertyPathDescriptions;`
- L200 _public member_ `TMap<ERigVMMemoryType, TArray<FRigVMPropertyDescription>> PropertyDescriptions;`
- L206 _public member_ `TSet<int32> InteractiveLiteralIndices;` — literal register indices that belong to interactive nodes (e.g. nodes with DM active). the FindOrAddProperty sharing scan skips these so that non-interactive nodes cannot be mapped to an interactive node's register, which would cause DM writes to bleed into nodes that are not being manipulated.
- L208 _public prototype_ `FRigVMOperand AddProperty(ERigVMMemoryType InMemoryType, const FName& InName, const FString& InCPPType, UObject* InCPPTypeObject, const FString& InDefaultValue = FString());`
- L209 _public prototype_ `FRigVMOperand FindProperty(ERigVMMemoryType InMemoryType, const FName& InName) const;`
- L210 _public prototype_ `FRigVMOperand FindOrAddProperty(const ERigVMMemoryType InMemoryType, const FRigVMFunctionCompilationPropertyDescription& InProperty, const FString& InNewName, const bool bMakeUniqueProperty);`
- L211 _public prototype_ `FRigVMOperand FindOrAddProperty(ERigVMMemoryType InMemoryType, const FName& InName, const FString& InCPPType, UObject* InCPPTypeObject, const FString& InDefaultValue, const bool bMakeUniqueProperty);`
- L212 _public prototype_ `FRigVMPropertyDescription GetProperty(const FRigVMOperand& InOperand);`
- L213 _public prototype_ `int32 FindOrAddPropertyPath(const FRigVMOperand& InOperand, const FString& InHeadCPPType, const FString& InSegmentPath);`
- L214 _public prototype_ `const FProperty* GetPropertyForOperand(const FRigVMOperand& InOperand) const;`
- L215 _public prototype_ `TRigVMTypeIndex GetTypeIndexForOperand(const FRigVMOperand& InOperand) const;`
- L216 _public prototype_ `FName GetUniquePropertyName(ERigVMMemoryType InMemoryType, const FName& InDesiredName) const;`
- L217 _public prototype_ `bool AddPropertiesForFunction( bool InIsCallable, const uint32& InHash, const FRigVMGraphFunctionHeader& InHeader, const FRigVMFunctionCompilationData* InCompilationData, int32 InFirstInstruction, int32 InLastInstruction, const TArray<FRigVMOperand>& InInterfaceOperands, const TMap<FRigVMOperand, FRigVMOperand>& InForwardedHandleToInterfaceOperand, const URigVMFunctionReferenceNode* InFunctionReferenceNode = nullptr);`
- L226 _public prototype_ `void SetupPropertyPathsForFoldedCopies(const FRigVMNodeExprAST* InExpr);`
- L228 _public prototype_ `bool RemapInstructionAt( const FRigVMInstruction& InOldInstruction, const FString& InFunctionIdentifier, const FRigVMFunctionCompilationData* InCompilationData, FRigVMByteCode& InNewByteCode, const FRigVMInstructionArray& InNewInstructions, const URigVMFunctionReferenceNode* InFunctionReferenceNode, const TFunction<int32(const int32&)>& InRemapInstructionIndex, const TFunction<FRigVMOperand(const FRigVMOperand&)>& InRemapOperand, const TFunction<int32(const int32&)>& InRemapBranchIndex, const TFunction<int32(const int32&)>& InRemapCallableIndex);`
- L240 _public member_ `TSharedPtr<FRigVMParserAST> AST;`
- L251 _public member_ `TMap<FRigVMOperand, FCopyOpInfo> DeferredCopyOps;` — operators that have been delayed for injection into the bytecode
- L271 _public member_ `TMap<uint32, TSharedPtr<FLazyBlockInfo>> LazyBlocks;`
- L272 _public member_ `TArray<uint32> LazyBlocksToProcess;`
- L273 _public member_ `TOptional<uint32> CurrentBlockHash;`
- L290 _public member_ `TMap<const FRigVMCallExternExprAST*, TArray<FPendingLoopJump>> PendingLoopJumps;` — Maps each enclosing loop's CallExtern expression to the list of Break/Continue JumpForward ops that must be patched to jump to that loop's EndBlock. Entries are consumed (removed) when the loop's EndBlock is emitted.
- L292 _public prototype_ `void ReportInfo(const FString& InMessage) const;`
- L293 _public prototype_ `void ReportWarning(const FString& InMessage) const;`
- L294 _public prototype_ `void ReportError(const FString& InMessage) const;`
- L297 _public function_ `template <typename... Types> void ReportInfof(UE::Core::TCheckedFormatString<FString::FmtCharType, Types...> Fmt, Types... Args) const`
- L303 _public function_ `template <typename... Types> void ReportWarningf(UE::Core::TCheckedFormatString<FString::FmtCharType, Types...> Fmt, Types... Args) const`
- L309 _public function_ `template <typename... Types> void ReportErrorf(UE::Core::TCheckedFormatString<FString::FmtCharType, Types...> Fmt, Types... Args) const`
- L314 _public member_ `FRigVMReportDelegate OriginalReportDelegate;`
- L315 _public prototype_ `void OverrideReportDelegate(bool& bEncounteredASTError, bool& bSurpressedASTError);`
- L316 _public prototype_ `void RemoveOverrideReportDelegate();`
- L318 _public function_ `void Clear()`

#### struct `FRigVMCompilerWorkData::FFunctionRegisterData`  
`struct FFunctionRegisterData`  
_L178-194_
- L180 _public member_ `uint32 ObjectId;`
- L181 _public member_ `ERigVMMemoryType MemoryType = ERigVMMemoryType::Invalid;`
- L182 _public member_ `int32 RegisterIndex = 0;`
- L190 _public function_ `bool operator==(const FFunctionRegisterData& Other) const`

#### struct `FRigVMCompilerWorkData::FCopyOpInfo`  
`struct FCopyOpInfo`  
_L242-248_
- L244 _public member_ `FRigVMCopyOp Op;`
- L245 _public member_ `const FRigVMAssignExprAST* AssignExpr = nullptr;`
- L246 _public member_ `const FRigVMVarExprAST* SourceExpr = nullptr;`
- L247 _public member_ `const FRigVMVarExprAST* TargetExpr = nullptr;`

#### struct `FRigVMCompilerWorkData::FLazyBlockInfo`  
`struct FLazyBlockInfo`  
_L253-269_
- L255 _public function_ `FLazyBlockInfo() : StartInstruction(INDEX_NONE) , EndInstruction(INDEX_NONE) , bProcessed(false)`
- L261 _public member_ `TOptional<uint32> Hash;`
- L262 _public member_ `FString BlockCombinationName;`
- L263 _public member_ `FRigVMOperand ExecuteStateOperand;`
- L264 _public member_ `int32 StartInstruction;`
- L265 _public member_ `int32 EndInstruction;`
- L266 _public member_ `TArray<const FRigVMExprAST*> Expressions;`
- L267 _public member_ `TArray<int32> RunInstructionsToUpdate;`
- L268 _public member_ `bool bProcessed;`

#### struct `FRigVMCompilerWorkData::FPendingLoopJump`  
`struct FPendingLoopJump`  
_L279-283_
- desc: Tracks a JumpForward op emitted for a Break or Continue node that needs its relative offset patched once the enclosing loop's EndBlock is emitted.
- L281 _public member_ `int32 ByteOffset;` — Byte offset of the JumpForward op in the bytecode stream (returned by AddJumpOp)
- L282 _public member_ `int32 InstructionIndex;` — Instruction index of the JumpForward op (for relative offset calculation)

#### class `URigVMCompiler`  
`class URigVMCompiler : public UObject`  
_L356-474_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UObject`
- L362 _public prototype_ `URigVMCompiler();`
- L365 _public member_ `FRigVMCompileSettings Settings_DEPRECATED;` — `UPROPERTY()`
- L368 _public function_ `bool Compile(TArray<URigVMGraph*> InGraphs, URigVMController* InController, URigVM* OutVM)` — `UFUNCTION(BlueprintCallable, Category = FRigVMCompiler, meta=(DeprecatedFunction, DeprecationMessage="Compile is deprecated, use CompileVM with Context parameter."))`
- L371 _public function_ `bool CompileVM(TArray<URigVMGraph*> InGraphs, URigVMController* InController, URigVM* OutVM, FRigVMExtendedExecuteContext& Context)` — `UFUNCTION(BlueprintCallable, Category = FRigVMCompiler)`
- L376 _public prototype_ `bool Compile(const FRigVMCompileSettings& InSettings, TArray<URigVMGraph*> InGraphs, URigVMController* InController, URigVM* OutVM, FRigVMExtendedExecuteContext& OutVMContext, const TArray<FRigVMExternalVariable>& InExternalVariables, TMap<FString, FRigVMOperand>* OutOperands, TSharedPtr<FRigVMParserAST> InAST = TSharedPtr<FRigVMParserAST>(), FRigVMFunctionCompilationData* OutFunctionCompilationData = nullptr);`
- L378 _public prototype_ `bool CompileFunction(const FRigVMCompileSettings& InSettings, const URigVMLibraryNode* InLibraryNode, URigVMController* InController, const TArray<FRigVMExternalVariable>& InExternalVariables, FRigVMFunctionCompilationData* OutFunctionCompilationData, FRigVMExtendedExecuteContext& OutVMContext);`
- L380 _public prototype_ `bool CompileCallable(FRigVMCompilerWorkData& WorkData, URigVM* OutVM, FRigVMExtendedExecuteContext& OutVMContext, const FRigVMCallableInfo* InCallable, const FRigVMGraphFunctionHeader& InHeader, const FRigVMFunctionCompilationData* InFunctionCompilationData, const URigVMFunctionReferenceNode* InFunctionReferenceNode = nullptr);`
- L382 _public member_ `FRigVMCompiler_GetFunctionCompilationData GetFunctionCompilationData;`
- L390 _public member_ `TMap<FString, FCompiledFunctionData> CompiledFunctions;`
- L392 _public prototype_ `static UScriptStruct* GetScriptStructForCPPType(const FString& InCPPType);`
- L393 _public prototype_ `static FString GetPinHash(const URigVMPin* InPin, const FRigVMVarExprAST* InVarExpr, const URigVMLibraryNode* FunctionCompiling = nullptr, const FRigVMASTProxy& InPinProxy = FRigVMASTProxy());`
- L398 _public prototype_ `static const FRigVMVarExprAST* GetSourceVarExpr(const FRigVMExprAST* InExpr);` — follows assignment expressions to find the source ref counted containers since ref counted containers are not copied for assignments. this is currently only used for arrays.
- L400 _public prototype_ `void MarkDebugWatch(FRigVMExtendedExecuteContext& Context, bool bRequired, URigVMPin* InPin, URigVM* OutVM, TMap<FString, FRigVMOperand>* OutOperands, TSharedPtr<FRigVMParserAST> InRuntimeAST);`
- L404 _private member_ `const URigVMLibraryNode* CurrentlyCompilingFunctionNode = nullptr;`
- L405 _private member_ `TSet<const URigVMLibraryNode*> FunctionCompilationStack;`
- L407 _private prototype_ `TArray<URigVMPin*> GetLinkedPins(URigVMPin* InPin, bool bInputs = true, bool bOutputs = true, bool bRecursive = true);`
- L408 _private prototype_ `int32 GetElementSizeFromCPPType(const FString& InCPPType, UScriptStruct* InScriptStruct);`
- L410 _private prototype_ `static FString GetPinHashImpl(const URigVMPin* InPin, const FRigVMVarExprAST* InVarExpr, const URigVMLibraryNode* FunctionCompiling = nullptr, const FRigVMASTProxy& InPinProxy = FRigVMASTProxy());`
- L412 _private prototype_ `bool TraverseExpression(const FRigVMExprAST* InExpr, FRigVMCompilerWorkData& WorkData);`
- L413 _private prototype_ `bool TraverseChildren(const FRigVMExprAST* InExpr, FRigVMCompilerWorkData& WorkData);`
- L414 _private prototype_ `bool TraverseBlock(const FRigVMBlockExprAST* InExpr, FRigVMCompilerWorkData& WorkData);`
- L415 _private prototype_ `bool TraverseEntry(const FRigVMEntryExprAST* InExpr, FRigVMCompilerWorkData& WorkData);`
- L416 _private prototype_ `bool TraverseCallExtern(const FRigVMCallExternExprAST* InExpr, FRigVMCompilerWorkData& WorkData);`
- L417 _private prototype_ `bool TraverseInlineFunction(const FRigVMInlineFunctionExprAST* InExpr, FRigVMCompilerWorkData& WorkData);`
- L418 _private prototype_ `bool TraverseCallableFunction(const FRigVMInlineFunctionExprAST* InExpr, const uint32 InCallableHash, FRigVMCompilerWorkData& WorkData);`
- L419 _private prototype_ `bool TraverseNoOp(const FRigVMNoOpExprAST* InExpr, FRigVMCompilerWorkData& WorkData);`
- L420 _private prototype_ `bool TraverseVar(const FRigVMVarExprAST* InExpr, FRigVMCompilerWorkData& WorkData);`
- L421 _private prototype_ `bool TraverseLiteral(const FRigVMVarExprAST* InExpr, FRigVMCompilerWorkData& WorkData);`
- L422 _private prototype_ `bool TraverseAssign(const FRigVMAssignExprAST* InExpr, FRigVMCompilerWorkData& WorkData);`
- L423 _private prototype_ `bool TraverseCopy(const FRigVMCopyExprAST* InExpr, FRigVMCompilerWorkData& WorkData);`
- L424 _private prototype_ `bool TraverseCachedValue(const FRigVMCachedValueExprAST* InExpr, FRigVMCompilerWorkData& WorkData);`
- L425 _private prototype_ `bool TraverseExit(const FRigVMExitExprAST* InExpr, FRigVMCompilerWorkData& WorkData);`
- L426 _private prototype_ `bool TraverseInvokeEntry(const FRigVMInvokeEntryExprAST* InExpr, FRigVMCompilerWorkData& WorkData);`
- L428 _private prototype_ `void AddCopyOperator( const FRigVMCopyOp& InOp, const FRigVMAssignExprAST* InAssignExpr, const FRigVMVarExprAST* InSourceExpr, const FRigVMVarExprAST* InTargetExpr, FRigVMCompilerWorkData& WorkData, bool bDelayCopyOperations = true);`
- L436 _private prototype_ `void AddCopyOperator( const FRigVMCompilerWorkData::FCopyOpInfo& CopyOpInfo, FRigVMCompilerWorkData& WorkData, bool bDelayCopyOperations = true);`
- L441 _private prototype_ `FRigVMOperand FindOrAddRegister(const FRigVMVarExprAST* InVarExpr, FRigVMCompilerWorkData& WorkData);`
- L442 _private prototype_ `const FRigVMCompilerWorkData::FRigVMASTProxyArray& FindProxiesWithSharedOperand(const FRigVMVarExprAST* InVarExpr, FRigVMCompilerWorkData& WorkData);`
- L444 _private prototype_ `static FString GetPinNameWithDirectionPrefix(const URigVMPin* Pin);`
- L445 _private prototype_ `static int32 GetOperandFunctionInterfaceParameterIndex(const TArray<FString>& OperandsPinNames, const FRigVMFunctionCompilationData* FunctionCompilationData, const FRigVMOperand& Operand);`
- L447 _private prototype_ `bool ValidateNode(const FRigVMCompileSettings& InSettings, URigVMNode* InNode, bool bCheck = true);`
- L449 _private prototype_ `void ReportInfo(const FRigVMCompileSettings& InSettings, const FString& InMessage);`
- L450 _private prototype_ `void ReportWarning(const FRigVMCompileSettings& InSettings, const FString& InMessage);`
- L451 _private prototype_ `void ReportError(const FRigVMCompileSettings& InSettings, const FString& InMessage);`
- L454 _private function_ `template <typename... Types> void ReportInfof(const FRigVMCompileSettings& InSettings, UE::Core::TCheckedFormatString<FString::FmtCharType, Types...> Fmt, Types... Args)`
- L460 _private function_ `template <typename... Types> void ReportWarningf(const FRigVMCompileSettings& InSettings, UE::Core::TCheckedFormatString<FString::FmtCharType, Types...> Fmt, Types... Args)`
- L466 _private function_ `template <typename... Types> void ReportErrorf(const FRigVMCompileSettings& InSettings, UE::Core::TCheckedFormatString<FString::FmtCharType, Types...> Fmt, Types... Args)`

#### struct `URigVMCompiler::FCompiledFunctionData`  
`struct FCompiledFunctionData`  
_L384-388_
- L386 _public member_ `const URigVMFunctionReferenceNode* FunctionReferenceNode;`
- L387 _public member_ `const FRigVMFunctionCompilationData* CompilationData;`

#### class `FFunctionCompilationScope`  
`class FFunctionCompilationScope`  
_L476-493_
- L479 _public function_ `FFunctionCompilationScope(URigVMCompiler* InCompiler, const URigVMLibraryNode* InLibraryNode) : Compiler(InCompiler), LibraryNode(InLibraryNode)`
- L485 _public function_ `~FFunctionCompilationScope()`
- L491 _private member_ `URigVMCompiler* Compiler;`
- L492 _private member_ `const URigVMLibraryNode* LibraryNode;`

#### Free symbols / members of external scopes

- L21 _macro_ `#define UE_API RIGVMDEVELOPER_API`
- L353 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(const FRigVMFunctionCompilationData*, FRigVMCompiler_GetFunctionCompilationData, const FRigVMGraphFunctionHeader& Header);`
- L353 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(const FRigVMFunctionCompilationData*, FRigVMCompiler_GetFunctionCompilationData, const FRigVMGraphFunctionHeader& Header);`

### `Plugins/Runtime/RigVM/Source/RigVMDeveloper/Public/RigVMDeveloperModule.h` (Public)


#### Free symbols / members of external scopes

- L12 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogRigVMDeveloper, Log, All);`

### `Plugins/Runtime/RigVM/Source/RigVMDeveloper/Public/RigVMDeveloperTypeUtils.h` (Public)


#### Free symbols / members of external scopes

- L14 _namespace_ `namespace RigVMTypeUtils`
- L17 _prototype_ `FEdGraphPinType PinTypeFromTypeIndex(const TRigVMTypeIndex& InTypeIndex);` (scope `RigVMTypeUtils`)
- L19 _prototype_ `FEdGraphPinType PinTypeFromCPPType(const FName& InCPPType, UObject* InCPPTypeObject);` (scope `RigVMTypeUtils`)
- L21 _prototype_ `FEdGraphPinType PinTypeFromExternalVariable(const FRigVMExternalVariable& InExternalVariable);` (scope `RigVMTypeUtils`)
- L23 _prototype_ `FEdGraphPinType PinTypeFromRigVMVariableDescription(const FRigVMGraphVariableDescription& InVariableDescription);` (scope `RigVMTypeUtils`)
- L25 _prototype_ `FEdGraphPinType SubPinType(const FEdGraphPinType& InPinType, const FString& SegmentPath);` (scope `RigVMTypeUtils`)
- L27 _prototype_ `bool CPPTypeFromPin(URigVMPin* InPin, FString& OutCPPType, UObject** OutCPPTypeObject, bool bGetBaseCPPType = false);` (scope `RigVMTypeUtils`)
- L29 _prototype_ `bool CPPTypeFromPin(URigVMPin* InPin, FString& OutCPPType, FName& OutCPPTypeObjectPath, bool bGetBaseCPPType = false);` (scope `RigVMTypeUtils`)
- L31 _prototype_ `bool CPPTypeFromPin(URigVMPin* InPin, FString& OutCPPType, FString& OutCPPTypeObjectPath, bool bGetBaseCPPType = false);` (scope `RigVMTypeUtils`)
- L33 _prototype_ `bool CPPTypeFromPinType(const FEdGraphPinType& InPinType, FString& OutCPPType, UObject** OutCPPTypeObject);` (scope `RigVMTypeUtils`)
- L35 _prototype_ `bool CPPTypeFromPinType(const FEdGraphPinType& InPinType, FString& OutCPPType, FName& OutCPPTypeObjectPath);` (scope `RigVMTypeUtils`)
- L37 _prototype_ `bool CPPTypeFromPinType(const FEdGraphPinType& InPinType, FString& OutCPPType, FString& OutCPPTypeObjectPath);` (scope `RigVMTypeUtils`)
- L39 _prototype_ `TRigVMTypeIndex TypeIndexFromPinType(const FEdGraphPinType& InPinType);` (scope `RigVMTypeUtils`)
- L41 _prototype_ `bool AreCompatible(const FName& InCPPTypeA, UObject* InCPPTypeObjectA, const FName& InCPPTypeB, UObject* InCPPTypeObjectB);` (scope `RigVMTypeUtils`)
- L43 _prototype_ `bool AreCompatible(const FRigVMExternalVariable& InTypeA, const FRigVMExternalVariable& InTypeB, const FString& InSegmentPathA = FString(), const FString& InSegmentPathB = FString());` (scope `RigVMTypeUtils`)
- L45 _prototype_ `bool AreCompatible(const FEdGraphPinType& InTypeA, const FEdGraphPinType& InTypeB, const FString& InSegmentPathA = FString(), const FString& InSegmentPathB = FString());` (scope `RigVMTypeUtils`)
- L47 _prototype_ `const TArray<TRigVMTypeIndex>& GetAvailableCasts(const TRigVMTypeIndex& InTypeIndex, bool bAsInput);` (scope `RigVMTypeUtils`)
- L49 _prototype_ `bool CanCastTypes(const TRigVMTypeIndex& InSourceTypeIndex, const TRigVMTypeIndex& InTargetTypeIndex);` (scope `RigVMTypeUtils`)
- L51 _prototype_ `const FRigVMFunction* GetCastForTypeIndices(const TRigVMTypeIndex& InSourceTypeIndex, const TRigVMTypeIndex& InTargetTypeIndex);` (scope `RigVMTypeUtils`)
- L53 _prototype_ `const FLazyName& GetCastTemplateValueName();` (scope `RigVMTypeUtils`)
- L55 _prototype_ `const FLazyName& GetCastTemplateResultName();` (scope `RigVMTypeUtils`)
- L57 _prototype_ `const FLazyName& GetCastTemplateNotation();` (scope `RigVMTypeUtils`)
- L60 _prototype_ `FText GetDisplayTextForArgumentType(const FRigVMTemplateArgumentType& InType);` (scope `RigVMTypeUtils`) — Get a user-facing name for an argument type

### `Plugins/Runtime/RigVM/Source/RigVMDeveloper/Public/RigVMEditorAsset.h` (Public)


#### struct `FRigVMPythonSettings`  
`struct FRigVMPythonSettings`  
_L65-72_
- reflection: `USTRUCT(MinimalAPI)`
- L69 _public function_ `FRigVMPythonSettings()`

#### enum `ERigVMTagDisplayMode`  
`enum class ERigVMTagDisplayMode : uint8`  
_L75-81_
- reflection: `UENUM(BlueprintType)`
- L77 _public enumerator_ `None = 0`
- L78 _public enumerator_ `All = 0x001`
- L79 _public enumerator_ `DeprecationOnly = 0x002`
- L80 _public enumerator_ `Last = DeprecationOnly UMETA(Hidden)`

#### struct `FRigVMEdGraphDisplaySettings`  
`struct FRigVMEdGraphDisplaySettings`  
_L84-163_
- reflection: `USTRUCT(MinimalAPI)`
- L88 _public prototype_ `FRigVMEdGraphDisplaySettings();`
- L89 _public prototype_ `~FRigVMEdGraphDisplaySettings();`
- L94 _public member_ `bool bShowNodeInstructionIndex;` — `UPROPERTY(EditAnywhere, Category = "Graph Display Settings")` — When enabled shows the first node instruction index matching the execution stack window.
- L103 _public member_ `bool bShowNodeRunCounts;` — `UPROPERTY(EditAnywhere, Category = "Graph Display Settings")` — When enabled shows the node counts both in the graph view as we as in the execution stack window. The number on each node represents how often the node has been run. Keep in mind when looking at nodes in a function the count represents the sum of all counts for each node based on all references of the function currently running.
- L108 _public member_ `int32 NodeRunLowerBound;` — `UPROPERTY(EditAnywhere, Category = "Graph Display Settings")` — A lower limit for counts for nodes used for debugging. Any node lower than this count won't show the run count.
- L116 _public member_ `int32 NodeRunLimit;` — `UPROPERTY(EditAnywhere, Category = "Graph Display Settings")` — A upper limit for counts for nodes used for debugging. If a node reaches this count a warning will be issued for the node and displayed both in the execution stack as well as in the graph. Setting this to <= 1 disables the warning. Note: The count limit doesn't apply to functions / collapse nodes.
- L120 _public member_ `double MinMicroSeconds;` — `UPROPERTY(EditAnywhere, Category = "Graph Display Settings", transient, meta = (EditCondition = "!bAutoDetermineRange"))` — The duration in microseconds of the fastest instruction / node
- L124 _public member_ `double MaxMicroSeconds;` — `UPROPERTY(EditAnywhere, Category = "Graph Display Settings", transient, meta = (EditCondition = "!bAutoDetermineRange"))` — The duration in microseconds of the slowest instruction / node
- L128 _public member_ `double TotalMicroSeconds;` — `UPROPERTY(VisibleAnywhere, Category = "Graph Display Settings", transient)` — The total duration of the last execution of the rig
- L132 _public member_ `int32 AverageFrames;` — `UPROPERTY(EditAnywhere, Category = "Graph Display Settings", meta = (UIMin=1, UIMax=256))` — If you set this to more than 1 the results will be averaged across multiple frames
- L134 _public member_ `TArray<double> MinMicroSecondsFrames;`
- L135 _public member_ `TArray<double> MaxMicroSecondsFrames;`
- L136 _public member_ `TArray<double> TotalMicroSecondsFrames;`
- L139 _public member_ `bool bAutoDetermineRange;` — `UPROPERTY(EditAnywhere, Category = "Graph Display Settings")`
- L142 _public member_ `double LastMinMicroSeconds;` — `UPROPERTY(transient)`
- L145 _public member_ `double LastMaxMicroSeconds;` — `UPROPERTY(transient)`
- L149 _public member_ `FLinearColor MinDurationColor;` — `UPROPERTY(EditAnywhere, Category = "Graph Display Settings")` — The color of the fastest instruction / node
- L153 _public member_ `FLinearColor MaxDurationColor;` — `UPROPERTY(EditAnywhere, Category = "Graph Display Settings")` — The color of the slowest instruction / node
- L157 _public member_ `ERigVMTagDisplayMode TagDisplayMode;` — `UPROPERTY(EditAnywhere, Category = "Graph Display Settings")` — The color of the slowest instruction / node
- L159 _public prototype_ `void SetTotalMicroSeconds(double InTotalMicroSeconds);`
- L160 _public prototype_ `void SetLastMinMicroSeconds(double InMinMicroSeconds);`
- L161 _public prototype_ `void SetLastMaxMicroSeconds(double InMaxMicroSeconds);`
- L162 _public prototype_ `double AggregateAverage(TArray<double>& InFrames, double InPrevious, double InNext) const;`

#### class `URigVMEditorAssetInterface`  
`class URigVMEditorAssetInterface : public UInterface`  
_L166-169_
- reflection: `UINTERFACE(MinimalAPI, BlueprintType)`
- inherits: `UInterface`

#### class `IRigVMEditorAssetInterface`  
`class IRigVMEditorAssetInterface`  
_L171-791_
- L178 _public prototype_ `static FRigVMEditorAssetInterfacePtr GetInterfaceOuter(const UObject* InObject);`
- L180 _public prototype_ `virtual TScriptInterface<IRigVMRuntimeAssetInterface> GetRuntimeAssetInterface() const;`
- L181 _public prototype_ `virtual UClass* GetRuntimeAssetClass() const = 0;`
- L182 _public prototype_ `virtual UObject* GetAssetObjectForEditor() = 0;`
- L184 _public prototype_ `virtual UObject* GetObject() = 0;`
- L185 _public function_ `const UObject* GetObject() const`
- L186 _public prototype_ `bool IsBlueprintAsset() const;`
- L187 _public prototype_ `virtual void BeginDestroy();`
- L189 _public prototype_ `TScriptInterface<IRigVMClientHost> GetRigVMClientHost();`
- L190 _public function_ `const TScriptInterface<IRigVMClientHost> GetRigVMClientHost() const`
- L192 _public function_ `FRigVMClient* GetRigVMClient()`
- L193 _public function_ `const FRigVMClient* GetRigVMClient() const`
- L194 _public prototype_ `void RequestClientHostRigVMInit();`
- L196 _public member_ `static inline const FLazyName RigVMPanelNodeFactoryName = FLazyName(TEXT("FRig`
- L197 _public member_ `static inline const FLazyName RigVMPanelPinFactoryName = FLazyName(TEXT("FRig`
- L199 _public prototype_ `virtual void GetAllEdGraphs(TArray<UEdGraph*>& Graphs) const = 0;`
- L200 _public prototype_ `virtual TArray<FRigVMGraphVariableDescription> GetAssetVariables() const = 0;`
- L201 _public prototype_ `virtual FRigVMGraphVariableDescription FindAssetVariableByGuid(const FGuid& InGuid) const;`
- L202 _public prototype_ `virtual bool IsRegeneratingOnLoad() const = 0;`
- L204 _public prototype_ `virtual FOnRigVMPreVariablesChanged& OnPreVariablesChanged() = 0;`
- L205 _public prototype_ `virtual FOnRigVMPostVariablesChanged& OnPostVariablesChanged() = 0;`
- L206 _public prototype_ `virtual FProperty* FindGeneratedPropertyByName(const FName& InName) = 0;`
- L207 _public function_ `virtual const FProperty* FindGeneratedPropertyByName(const FName& InName) const`
- L208 _public prototype_ `virtual FName AddHostMemberVariableFromExternal(FRigVMExternalVariable InVariableToCreate, FString InDefaultValue = FString()) = 0;`
- L209 _public prototype_ `virtual FName AddMemberVariable(const FName& InName, const FString& InCPPType, bool bIsPublic = false, bool bIsReadOnly = false, FString InDefaultValue = TEXT("")) = 0;`
- L210 _public prototype_ `virtual bool RemoveMemberVariable(const FName& InName) = 0;`
- L211 _public prototype_ `virtual bool BulkRemoveMemberVariables(const TArray<FName>& InNames) = 0;`
- L212 _public prototype_ `virtual bool RenameMemberVariable(const FName& InOldName, const FName& InNewName) = 0;`
- L213 _public prototype_ `virtual bool ChangeMemberVariableType(const FName& InName, const FString& InCPPType, bool bIsPublic = false, bool bIsReadOnly = false, FString InDefaultValue = TEXT("")) = 0;`
- L214 _public prototype_ `virtual bool ChangeMemberVariableType(const FName& InName, const FEdGraphPinType& InType) = 0;`
- L215 _public prototype_ `virtual bool SetVariableIndex(const FName& InName, int32 NewIndex) = 0;`
- L216 _public prototype_ `virtual FText GetVariableTooltip(const FName& InName) const = 0;`
- L217 _public prototype_ `virtual FString GetVariableCategory(const FName& InName) = 0;`
- L218 _public prototype_ `virtual FString GetVariableMetadataValue(const FName& InName, const FName& InKey) = 0;`
- L219 _public prototype_ `virtual bool SetVariableCategory(const FName& InName, const FString& InCategory) = 0;`
- L220 _public prototype_ `virtual bool SetVariableTooltip(const FName& InName, const FText& InTooltip) = 0;`
- L221 _public prototype_ `virtual bool SetVariableExposeOnSpawn(const FName& InName, const bool bInExposeOnSpawn) = 0;`
- L222 _public prototype_ `virtual bool SetVariableExposeToCinematics(const FName& InName, const bool bInExposeToCinematics) = 0;`
- L223 _public prototype_ `virtual bool SetVariablePrivate(const FName& InName, const bool bInPrivate) = 0;`
- L224 _public prototype_ `virtual bool SetVariablePublic(const FName& InName, const bool bIsPublic) = 0;`
- L225 _public prototype_ `virtual FString OnCopyVariable(const FName& InName) const = 0;`
- L226 _public prototype_ `virtual bool OnPasteVariable(const FString& InText) = 0;`
- L227 _public prototype_ `virtual const UStruct* GetVariablesStruct() = 0;`
- L228 _public prototype_ `virtual uint8* GetVariablesMemory() = 0;`
- L230 _public prototype_ `virtual UObject* GetObjectBeingDebugged(bool bEvenIfPendingKill = false) = 0;`
- L231 _public function_ `virtual UObject* GetObjectBeingDebugged(bool bEvenIfPendingKill = false) const`
- L232 _public prototype_ `virtual const FString& GetObjectBeingDebuggedPath() const = 0;`
- L233 _public prototype_ `virtual TArray<UObject*> GetArchetypeInstances(bool bIncludeCDO, bool bIncludeDerivedClass) const = 0;`
- L234 _public prototype_ `virtual UWorld* GetWorldBeingDebugged() const = 0;`
- L235 _public prototype_ `virtual void SetWorldBeingDebugged(UWorld* NewWorld) = 0;`
- L236 _public prototype_ `virtual ERigVMAssetStatus GetAssetStatus() const = 0;`
- L237 _public prototype_ `virtual bool IsUpToDate() const = 0;`
- L238 _public prototype_ `virtual URigVM* GetVM(bool bCreateIfNeeded) const = 0;`
- L239 _public prototype_ `virtual FRigVMDrawContainer& GetDrawContainer() = 0;`
- L240 _public function_ `const FRigVMDrawContainer& GetDrawContainer() const`
- L242 _public prototype_ `virtual bool ExportGraphToText(UEdGraph* InEdGraph, FString& OutText);`
- L243 _public prototype_ `virtual bool TryImportGraphFromText(const FString& InClipboardText, UEdGraph** OutGraphPtr = nullptr);`
- L244 _public prototype_ `virtual bool CanImportGraphFromText(const FString& InClipboardText);`
- L246 _public prototype_ `virtual void RefreshAllNodes() ;`
- L248 _public prototype_ `virtual void RecompileVM() ;`
- L249 _public prototype_ `virtual void RecompileVMIfRequired() ;`
- L250 _public prototype_ `virtual void RequestAutoVMRecompilation() ;`
- L251 _public function_ `virtual void SetAutoVMRecompile(bool bAutoRecompile)`
- L252 _public function_ `virtual bool GetAutoVMRecompile() const`
- L253 _public prototype_ `virtual void IncrementVMRecompileBracket();`
- L254 _public prototype_ `virtual void DecrementVMRecompileBracket();`
- L256 _public prototype_ `virtual void SetEditingLocked(bool InEditingLocked );`
- L257 _public prototype_ `virtual bool IsEditingLocked() const;`
- L258 _public prototype_ `virtual bool CanSetEditingLocked() const;`
- L259 _public prototype_ `virtual bool IsEditingLockedVisible() const;`
- L260 _public prototype_ `virtual FText GetEditingLockedLabel() const;`
- L261 _public prototype_ `virtual FText GetEditingLockedTooltip() const;`
- L263 _public prototype_ `virtual void SetObjectBeingDebugged(UObject* NewObject);`
- L264 _public function_ `virtual FOnRigVMSetObjectBeingDebugged& OnSetObjectBeingDebugged()`
- L267 _public prototype_ `virtual IRigVMEditorModule* GetEditorModule() const;` — Returns the editor module to be used for this blueprint
- L270 _public prototype_ `virtual const FLazyName& GetPanelNodeFactoryName() const;` — Returns true if a given panel node factory is compatible this blueprint
- L272 _public prototype_ `virtual FRigVMRuntimeSettings& GetVMRuntimeSettings() = 0;`
- L273 _public function_ `virtual const FRigVMRuntimeSettings& GetVMRuntimeSettings() const`
- L276 _public prototype_ `static void QueueCompilerMessageDelegate(const FOnRigVMReportCompilerMessage::FDelegate& InDelegate);`
- L277 _public prototype_ `static void ClearQueuedCompilerMessageDelegates();`
- L279 _public prototype_ `virtual FRigVMGraphModifiedEvent& OnModified();`
- L280 _public prototype_ `FOnRigVMCompiledEvent& OnVMCompiled();`
- L282 _public function_ `virtual FOnRigVMReportCompilerMessage& OnReportCompilerMessage()`
- L285 _public prototype_ `virtual const FLazyName& GetPanelPinFactoryName() const;` — Returns true if a given panel pin factory is compatible this blueprint
- L287 _public prototype_ `virtual void AddPinWatch(UEdGraphPin* InPin) = 0;`
- L288 _public prototype_ `virtual bool IsPinBeingWatched(const UEdGraphPin* InPin) const = 0;`
- L289 _public prototype_ `virtual bool NodeContainsWatchedPins(const UEdGraphNode* InNode) const = 0;`
- L291 _public member_ `TMap<FString, FRigVMOperand> PinToOperandMap;`
- L296 _public prototype_ `bool SetEarlyExitInstruction(URigVMNode* InNodeToExitEarlyAfter, int32 InInstruction = INDEX_NONE, bool bRequestHyperLink = false);` — Sets the instruction index to exit early on
- L301 _public prototype_ `bool ResetEarlyExitInstruction(bool bResetCallstack = true);` — Resets / removes the instruction index to exit early on
- L306 _public prototype_ `void TogglePreviewHere(const URigVMGraph* InGraph);` — Toggles the preview here functionality based on the selection
- L311 _public prototype_ `void PreviewHereStepForward();` — Steps forward in a preview here session
- L316 _public prototype_ `bool CanPreviewHereStepForward() const;` — Returns true if we can step forward in a preview here session
- L321 _public prototype_ `bool MarkNodeForPreviewHere(URigVMNode* InNode, int32 InInstructionIndex, bool bRequestHyperLink);` — Returns true if we can step forward in a preview here session
- L326 _public prototype_ `int32 GetPreviewNodeInstructionIndexFromSelection(const URigVMGraph* InGraph) const;` — Returns the instruction index of the currently selected node
- L328 _public function_ `virtual FRigVMController_RequestJumpToHyperlinkDelegate& OnRequestJumpToHyperlink()`
- L331 _public prototype_ `URigVMEditorSettings* GetRigVMEditorSettings() const;` — Returns the settings defaults for this blueprint
- L333 _public prototype_ `virtual UEdGraph* GetEdGraph(const URigVMGraph* InModel) const;`
- L334 _public prototype_ `virtual UEdGraph* GetEdGraph(const FString& InNodePath) const;`
- L336 _public prototype_ `void AddVariableSearchMetaDataInfo(const FName InVariableName, TArray<UBlueprintExtension::FSearchTagDataPair>& OutTaggedMetaData) const;`
- L338 _public prototype_ `virtual FRigVMEdGraphDisplaySettings& GetRigGraphDisplaySettings() = 0;`
- L339 _public function_ `virtual const FRigVMEdGraphDisplaySettings& GetRigGraphDisplaySettings() const`
- L340 _public prototype_ `virtual FRigVMCompileSettings& GetVMCompileSettings() = 0;`
- L341 _public function_ `virtual const FRigVMCompileSettings& GetVMCompileSettings() const`
- L344 _public prototype_ `virtual URigVMHost* GetDebuggedRigVMHost();`
- L346 _public prototype_ `virtual URigVMGraph* GetFocusedModel() const;`
- L347 _public prototype_ `virtual TArray<URigVMGraph*> GetAllModels() const;`
- L348 _public prototype_ `virtual URigVMFunctionLibrary* GetLocalFunctionLibrary() const;`
- L349 _public prototype_ `virtual URigVMGraph* GetModel(const UEdGraph* InEdGraph = nullptr) const;`
- L350 _public prototype_ `virtual URigVMGraph* GetModel(const FString& InNodePath) const;`
- L351 _public prototype_ `virtual URigVMController* GetControllerByName(const FString InGraphName = TEXT("")) const;`
- L352 _public prototype_ `virtual URigVMController* GetOrCreateController(URigVMGraph* InGraph = nullptr);`
- L353 _public prototype_ `virtual URigVMController* GetController(const UEdGraph* InEdGraph) const;`
- L354 _public prototype_ `virtual URigVMController* GetOrCreateController(const UEdGraph* InGraph);`
- L355 _public prototype_ `virtual URigVMController* GetController(const URigVMGraph* InGraph = nullptr) const;`
- L357 _public function_ `virtual FOnRigVMLocalizeFunctionDialogRequested& OnRequestLocalizeFunctionDialog()`
- L358 _public prototype_ `void BroadcastRequestLocalizeFunctionDialog(FRigVMGraphFunctionIdentifier InFunction, bool bForce = false);`
- L360 _public prototype_ `const FCompilerResultsLog& GetCompileLog() const;`
- L361 _public prototype_ `FCompilerResultsLog& GetCompileLog();`
- L362 _public prototype_ `void HandleReportFromCompiler(EMessageSeverity::Type InSeverity, UObject* InSubject, const FString& InMessage);`
- L366 _public prototype_ `TArray<IRigVMEditorAssetInterface*> GetDependencies(bool bRecursive = false) const;` — Returns a list of dependencies of this blueprint. Dependencies are blueprints that contain functions used in this blueprint
- L372 _public prototype_ `TArray<FAssetData> GetDependentAssets() const;` — Returns a list of dependents as unresolved soft object pointers. A dependent is a blueprint which uses a function defined in this blueprint. This function is not recursive, since it avoids opening the asset. Use GetDependentBlueprints as an alternative.
- L378 _public prototype_ `TArray<IRigVMEditorAssetInterface*> GetDependentResolvedAssets(bool bRecursive = false, bool bOnlyLoaded = false) const;` — Returns a list of dependents as resolved blueprints. A dependent is a blueprint which uses a function defined in this blueprint. If bOnlyLoaded is false, this function loads the dependent assets and can introduce a large cost depending on the size / count of assets in the project.
- L380 _public prototype_ `void BroadcastRefreshEditor();`
- L381 _public function_ `virtual FOnRigVMRefreshEditorEvent& OnRefreshEditor()`
- L383 _public prototype_ `FOnRigVMRequestInspectMemoryStorage& OnRequestInspectMemoryStorage();`
- L384 _public prototype_ `void RequestInspectMemoryStorage(const TArray<FRigVMMemoryStorageStruct*>& InMemoryStorageStructs) const;`
- L386 _public function_ `FOnRigVMPostEditChangeChainProperty& OnPostEditChangeChainProperty()`
- L387 _public prototype_ `void BroadcastPostEditChangeChainProperty(FPropertyChangedChainEvent& PropertyChangedChainEvent);`
- L388 _public prototype_ `virtual void MarkAssetAsStructurallyModified(bool bSkipDirtyAssetStatus = false) = 0;`
- L389 _public prototype_ `virtual void MarkAssetAsModified(FPropertyChangedEvent PropertyChangedEvent = FPropertyChangedEvent(nullptr)) = 0;`
- L391 _public prototype_ `virtual URigVMGraph* GetDefaultModel() const;`
- L392 _public prototype_ `virtual TArray<TObjectPtr<UEdGraph>>& GetUberGraphs() = 0;`
- L393 _public function_ `virtual const TArray<TObjectPtr<UEdGraph>>& GetUberGraphs() const`
- L396 _public prototype_ `void SetProfilingEnabled(const bool bEnabled);` — Enables or disables profiling for this asset
- L399 _public prototype_ `virtual const TArray<FString>& GetRequiredPlugins(bool bRefresh = true) const = 0;` — Returns the names of the plugins required to be loaded for this asset to work
- L400 _public prototype_ `virtual TArray<struct FEditedDocumentInfo>& GetLastEditedDocuments() = 0;`
- L401 _public prototype_ `virtual FRigVMPropertyBag* GetVariablesPropertyBag() = 0;`
- L403 _public prototype_ `virtual FRigVMVariant& GetAssetVariant() = 0;`
- L404 _public function_ `virtual const FRigVMVariant& GetAssetVariant() const`
- L405 _public prototype_ `virtual FRigVMVariantRef GetAssetVariantRef() const = 0;`
- L406 _public prototype_ `virtual void SetAssetStatus(const ERigVMAssetStatus& InStatus) = 0;`
- L409 _protected function_ `IRigVMEditorAssetInterface()`
- L410 _protected prototype_ `IRigVMEditorAssetInterface(const FObjectInitializer& ObjectInitializer);`
- L412 _protected prototype_ `virtual const TArray<FRigVMGraphFunctionHeader>& GetPublicGraphFunctions() const = 0;`
- L413 _protected prototype_ `virtual void SetPublicGraphFunctions(const TArray<FRigVMGraphFunctionHeader>& InHeaders) = 0;`
- L415 _protected prototype_ `virtual void RemovePinWatch(UEdGraphPin* InPin) = 0;`
- L416 _protected prototype_ `virtual void ClearPinWatches() = 0;`
- L417 _protected prototype_ `virtual void ForeachPinWatch(TFunctionRef<void(UEdGraphPin*)> Task) = 0;`
- L420 _protected prototype_ `virtual UClass* GetRigVMGeneratedClassPrototype() const = 0;`
- L421 _protected prototype_ `virtual UObject* GetDefaultsObject() = 0;`
- L422 _protected prototype_ `virtual void SetObjectBeingDebuggedSuper(UObject* NewObject) = 0;`
- L423 _protected prototype_ `virtual void SetUberGraphs(const TArray<TObjectPtr<UEdGraph>>& InGraphs) = 0;`
- L424 _protected prototype_ `virtual void PostTransactedSuper(const FTransactionObjectEvent& TransactionEvent) = 0;`
- L425 _protected prototype_ `virtual void ReplaceDeprecatedNodesSuper() = 0;`
- L426 _protected prototype_ `virtual void PreDuplicateSuper(FObjectDuplicationParameters& DupParams) = 0;`
- L427 _protected prototype_ `virtual void PostDuplicateSuper(bool bDuplicateForPIE) = 0;`
- L428 _protected prototype_ `virtual void GetAssetRegistryTagsSuper(FAssetRegistryTagsContext Context) const = 0;`
- L429 _protected prototype_ `virtual bool RequiresForceLoadMembersSuper(UObject* InObject) const = 0;`
- L430 _protected prototype_ `virtual TArray<FRigVMExternalVariable> GetExternalVariables(bool bFallbackToBlueprint) const = 0;`
- L431 _protected prototype_ `virtual FString GetVariableDefaultValue(const FName& InName, bool bFromDebuggedObject) const = 0;`
- L432 _protected prototype_ `virtual FRigVMExtendedExecuteContext* GetRigVMExtendedExecuteContext() = 0;`
- L433 _protected prototype_ `virtual void PreCompile() = 0;`
- L434 _protected prototype_ `virtual TMap<FString, FSoftObjectPath>& GetUserDefinedStructGuidToPathName(bool bFromCDO) = 0;`
- L435 _protected function_ `virtual const TMap<FString, FSoftObjectPath>& GetUserDefinedStructGuidToPathName(bool bFromCDO) const`
- L436 _protected prototype_ `virtual TMap<FString, FSoftObjectPath>& GetUserDefinedEnumToPathName(bool bFromCDO) = 0;`
- L437 _protected function_ `virtual const TMap<FString, FSoftObjectPath>& GetUserDefinedEnumToPathName(bool bFromCDO) const`
- L438 _protected prototype_ `virtual TSet<TObjectPtr<UObject>>& GetUserDefinedTypesInUse(bool bFromCDO) = 0;`
- L439 _protected prototype_ `virtual FCompilerResultsLog* GetCurrentMessageLog() const = 0;`
- L440 _protected prototype_ `virtual FRigVMDebugInfo& GetDebugInfo() = 0;`
- L441 _protected prototype_ `virtual TObjectPtr<URigVMEdGraph>& GetFunctionLibraryEdGraph() = 0;`
- L442 _protected function_ `virtual const TObjectPtr<URigVMEdGraph>& GetFunctionLibraryEdGraph() const`
- L443 _protected prototype_ `virtual TArray<TObjectPtr<UEdGraph>>& GetFunctionGraphs() = 0;`
- L444 _protected function_ `virtual const TArray<TObjectPtr<UEdGraph>>& GetFunctionGraphs() const`
- L445 _protected prototype_ `virtual bool& IsReferencedObjectPathsStored() = 0;`
- L446 _protected function_ `virtual void SetReferencedObjectPathsStored(bool bValue)`
- L447 _protected prototype_ `virtual TArray<FSoftObjectPath>& GetReferencedObjectPaths() = 0;`
- L448 _protected prototype_ `virtual TArray<FName>& GetSupportedEventNames() = 0;`
- L449 _protected prototype_ `virtual void UpdateSupportedEventNames() = 0;`
- L450 _protected prototype_ `virtual TArray<FRigVMReferenceNodeData>& GetFunctionReferenceNodeData() = 0;`
- L451 _protected prototype_ `virtual void NotifyGraphRenamedSuper(class UEdGraph* Graph, FName OldName, FName NewName) = 0;`
- L452 _protected prototype_ `virtual URigVMHost* CreateRigVMHostSuper(UObject* InOuter, FName InName = NAME_None, EObjectFlags InFlags = RF_NoFlags) = 0;`
- L453 _protected prototype_ `virtual void AddUbergraphPage(URigVMEdGraph* RigVMEdGraph) = 0;`
- L454 _protected prototype_ `virtual void AddLastEditedDocument(URigVMEdGraph* RigVMEdGraph) = 0;`
- L455 _protected prototype_ `virtual void Compile() = 0;`
- L456 _protected prototype_ `virtual FCompilerResultsLog CompileBlueprint() = 0;`
- L457 _protected prototype_ `virtual void PostEditChangeBlueprintActors() = 0;`
- L458 _protected prototype_ `virtual bool SplitAssetVariant() = 0;`
- L459 _protected prototype_ `virtual bool JoinAssetVariant(const FGuid& InGuid) = 0;`
- L460 _protected prototype_ `virtual TArray<FRigVMVariantRef> GetMatchingVariants() const = 0;`
- L461 _protected prototype_ `virtual void SerializeSuper(FArchive& Ar) = 0;`
- L462 _protected prototype_ `virtual void PostSerialize(FArchive& Ar) = 0;`
- L466 _protected prototype_ `void CollectExternalDependencies(TArray<FRigVMExternalDependency>& OutDependencies, const FName& InCategory, const FRigVMClient* InClient) const;` — Interface to URigVMExternalDependencyManager
- L467 _protected prototype_ `void CollectExternalDependencies(TArray<FRigVMExternalDependency>& OutDependencies, const FName& InCategory, const FRigVMGraphFunctionStore* InFunctionStore) const;`
- L468 _protected prototype_ `void CollectExternalDependencies(TArray<FRigVMExternalDependency>& OutDependencies, const FName& InCategory, const FRigVMGraphFunctionData* InFunction) const;`
- L469 _protected prototype_ `void CollectExternalDependencies(TArray<FRigVMExternalDependency>& OutDependencies, const FName& InCategory, const FRigVMGraphFunctionHeader* InHeader) const;`
- L470 _protected prototype_ `void CollectExternalDependencies(TArray<FRigVMExternalDependency>& OutDependencies, const FName& InCategory, const FRigVMFunctionCompilationData* InCompilationData) const;`
- L471 _protected prototype_ `void CollectExternalDependencies(TArray<FRigVMExternalDependency>& OutDependencies, const FName& InCategory, const URigVMGraph* InGraph) const;`
- L472 _protected prototype_ `void CollectExternalDependencies(TArray<FRigVMExternalDependency>& OutDependencies, const FName& InCategory, const URigVMNode* InNode) const;`
- L473 _protected prototype_ `void CollectExternalDependencies(TArray<FRigVMExternalDependency>& OutDependencies, const FName& InCategory, const URigVMPin* InPin) const;`
- L474 _protected prototype_ `void CollectExternalDependencies(TArray<FRigVMExternalDependency>& OutDependencies, const FName& InCategory, const UStruct* InStruct) const;`
- L475 _protected prototype_ `void CollectExternalDependencies(TArray<FRigVMExternalDependency>& OutDependencies, const FName& InCategory, const UEnum* InEnum) const;`
- L476 _protected prototype_ `void CollectExternalDependenciesForCPPTypeObject(TArray<FRigVMExternalDependency>& OutDependencies, const FName& InCategory, const UObject* InObject) const;`
- L479 _protected prototype_ `void CommonInitialization(const FObjectInitializer& ObjectInitializer);`
- L481 _protected prototype_ `void InitializeModelIfRequired(bool bRecompileVM = true);`
- L484 _protected prototype_ `void SerializeImpl(FArchive& Ar);`
- L488 _protected prototype_ `virtual void PreSave(FObjectPreSaveContext ObjectSaveContext);`
- L489 _protected prototype_ `virtual void PostLoad();`
- L490 _protected prototype_ `static void DeclareConstructClasses(TArray<FTopLevelAssetPath>& OutConstructClasses, const UClass* SpecificSubclass);`
- L491 _protected function_ `virtual bool IsPostLoadThreadSafe() const`
- L492 _protected prototype_ `virtual void PostTransacted(const FTransactionObjectEvent& TransactionEvent);`
- L493 _protected prototype_ `virtual void ReplaceDeprecatedNodes();`
- L494 _protected prototype_ `virtual void PreDuplicate(FObjectDuplicationParameters& DupParams);`
- L495 _protected prototype_ `virtual void PostDuplicate(bool bDuplicateForPIE);`
- L496 _protected prototype_ `virtual void GetAssetRegistryTags(FAssetRegistryTagsContext Context) const;`
- L499 _protected prototype_ `virtual bool RequiresForceLoadMembers(UObject* InObject) const;`
- L502 _protected prototype_ `virtual void PostEditChangeChainProperty(struct FPropertyChangedChainEvent& PropertyChangedEvent);` — UObject interface
- L504 _protected prototype_ `virtual void GetPreloadDependencies(TArray<UObject*>& OutDeps);` — Called during cooking. Must return all objects that will be Preload()ed when this is serialized at load time.
- L507 _protected prototype_ `virtual UObject* GetEditorObjectForRigVMGraph(const URigVMGraph* InVMGraph) const;` — --- IRigVMClientHost interface Start---
- L508 _protected prototype_ `virtual URigVMGraph* GetRigVMGraphForEditorObject(UObject* InObject) const;`
- L509 _protected prototype_ `virtual void HandleRigVMGraphAdded(const FRigVMClient* InClient, const FString& InNodePath);`
- L510 _protected prototype_ `virtual void HandleRigVMGraphRemoved(const FRigVMClient* InClient, const FString& InNodePath);`
- L511 _protected prototype_ `virtual void HandleRigVMGraphRenamed(const FRigVMClient* InClient, const FString& InOldNodePath, const FString& InNewNodePath);`
- L512 _protected prototype_ `virtual void HandleConfigureRigVMController(const FRigVMClient* InClient, URigVMController* InControllerToConfigure);`
- L515 _protected prototype_ `void GenerateUserDefinedDependenciesData(FRigVMExtendedExecuteContext& Context);`
- L523 _protected prototype_ `virtual void RefreshAllModels(ERigVMLoadType InLoadType = ERigVMLoadType::PostLoad);` — this is needed since even after load model data can change while the RigVM BP is not opened for example, if a user defined struct changed after BP load, any pin that references the struct needs to be regenerated
- L527 _protected prototype_ `virtual void OnRigVMRegistryChanged();` — RigVMRegistry changes can be triggered when new user defined types(structs/enums) are added/removed in which case we have to refresh the model
- L529 _protected prototype_ `void RequestRigVMInit() const;`
- L532 _protected prototype_ `virtual URigVMFunctionLibrary* GetOrCreateLocalFunctionLibrary(bool bSetupUndoRedo = true);`
- L534 _protected prototype_ `virtual URigVMGraph* AddModel(FString InName = TEXT("Rig Graph"), bool bSetupUndoRedo = true, bool bPrintPythonCommand`
- L536 _protected prototype_ `virtual bool RemoveModel(FString InName = TEXT("Rig Graph"), bool bSetupUndoRedo = true, bool bPrintPythonCommand`
- L538 _protected prototype_ `virtual FRigVMGetFocusedGraph& OnGetFocusedGraph();`
- L539 _protected prototype_ `virtual const FRigVMGetFocusedGraph& OnGetFocusedGraph() const;`
- L542 _protected prototype_ `virtual TArray<FString> GeneratePythonCommands();`
- L543 _protected prototype_ `virtual TArray<FString> GeneratePythonContextCommands(const FString InNewBlueprintName, bool bCreateAsset) = 0;`
- L545 _protected function_ `virtual void SetupPinRedirectorsForBackwardsCompatibility()`
- L549 _protected prototype_ `virtual bool IsFunctionPublic(const FName& InFunctionName) const;`
- L550 _protected prototype_ `virtual void MarkFunctionPublic(const FName& InFunctionName, bool bIsPublic = true);`
- L552 _protected prototype_ `virtual void RenameGraph(const FString& InNodePath, const FName& InNewName);`
- L558 _protected prototype_ `virtual TArray<FRigVMExternalDependency> GetExternalDependenciesForCategory(const FName& InCategory) const;`
- L563 _protected function_ `virtual FOnRigVMRequestInspectObject& OnRequestInspectObject()`
- L564 _protected function_ `void RequestInspectObject(const TArray<UObject*>& InObjects)`
- L568 _protected prototype_ `URigVMGraph* GetTemplateModel(bool bIsFunctionLibrary = false);`
- L569 _protected prototype_ `URigVMController* GetTemplateController(bool bIsFunctionLibrary = false);`
- L576 _protected member_ `mutable TArray<UObject::FAssetRegistryTag> CachedAssetTags;`
- L577 _protected member_ `TArray<TPair<TWeakObjectPtr<URigVMNode>,int32>> LastPreviewHereNodes;`
- L580 _protected member_ `bool bSuspendModelNotificationsForSelf;`
- L581 _protected member_ `bool bSuspendAllNotifications;`
- L583 _protected prototype_ `void RebuildGraphFromModel();`
- L585 _protected prototype_ `URigVMHost* CreateRigVMHostImpl();`
- L587 _protected prototype_ `virtual TArray<UStruct*> GetAvailableRigVMStructs() const;`
- L589 _protected prototype_ `FRigVMVariantRef GetAssetVariantRefImpl() const;`
- L592 _protected prototype_ `bool SplitAssetVariantImpl();` — Resets the asset's guid to a new one and splits it from the former variant set
- L595 _protected prototype_ `bool JoinAssetVariantImpl(const FGuid& InGuid);` — Merges the asset's guid with a provided one to join the variant set
- L597 _protected prototype_ `TArray<FRigVMVariantRef> GetMatchingVariantsImpl() const;`
- L601 _protected member_ `bool bAutoRecompileVM;`
- L603 _protected member_ `bool bVMRecompilationRequired;`
- L605 _protected member_ `bool bIsCompiling;`
- L607 _protected member_ `int32 VMRecompilationBracket;`
- L609 _protected member_ `bool bSkipDirtyBlueprintStatus;`
- L611 _protected member_ `FRigVMGraphModifiedEvent ModifiedEvent;`
- L612 _protected prototype_ `void Notify(ERigVMGraphNotifType InNotifType, UObject* InSubject);`
- L613 _protected prototype_ `void HandleModifiedEvent(ERigVMGraphNotifType InNotifType, URigVMGraph* InGraph, UObject* InSubject);`
- L615 _protected member_ `FOnRigVMAssetChangedEvent ChangedEvent;`
- L616 _protected function_ `virtual FOnRigVMAssetChangedEvent& OnChanged()`
- L618 _protected member_ `FOnRigVMSetObjectBeingDebugged SetObjectBeingDebuggedEvent;`
- L621 _protected prototype_ `void ReplaceFunctionIdentifiers(const FString& OldFunctionHostPath, const FString& NewFunctionHostPath, const FString& OldFunctionLibraryPath, const FString& NewFunctionLibraryPath);`
- L623 _protected member_ `FOnRigVMRefreshEditorEvent RefreshEditorEvent;`
- L624 _protected member_ `FOnRigVMVariableDroppedEvent VariableDroppedEvent;`
- L626 _protected prototype_ `void SuspendNotifications(bool bSuspendNotifs);`
- L628 _protected function_ `virtual FOnRigVMVariableDroppedEvent& OnVariableDropped()`
- L631 _protected member_ `FOnRigVMCompiledEvent VMCompiledEvent;`
- L633 _protected function_ `virtual void PathDomainSpecificContentOnLoad()`
- L634 _protected prototype_ `virtual void PatchBoundVariables();`
- L635 _protected prototype_ `virtual void PatchVariableNodesWithIncorrectType();`
- L636 _protected function_ `virtual void PatchParameterNodesOnLoad()`
- L637 _protected prototype_ `virtual void PatchLinksWithCast();`
- L638 _protected prototype_ `virtual void GetBackwardsCompatibilityPublicFunctions(TArray<FName> &BackwardsCompatiblePublicFunctions, TMap<URigVMLibraryNode*, FRigVMGraphFunctionHeader>& OldHeaders);`
- L640 _protected prototype_ `virtual void CreateMemberVariablesOnLoad();`
- L641 _protected prototype_ `virtual void PatchVariableNodesOnLoad();`
- L652 _protected prototype_ `virtual void RepairDuplicateVariableGuidsOnLoad();` — [GuidDedupe] One-shot recovery for the corrupted-state where two member variables in the bag ended up with identical FGuids (a real bug: AddHostMemberVariableFromExternal used to accept whatever Guid the caller passed, so duplicate-paste of a variable carried the source's Guid forward). Detect duplicates, regenerate Guids on later occurrences, and rewrite any variable node that was pointing at the now-old Guid for the regenerated variable. The Guid is the ground truth of variable identity; variable Name is used here ONLY as the disambiguator at the point of corruption (i.e. "of the nodes referencing the duplicate Guid, the ones whose Name pin equals the regenerated variable's name belonged to that variable"). Idempotent: detection scans (a TSet<FGuid> for the asset bag and one per graph) always run, but no writes occur on a healthy asset and bDirtyDuringLoad is left untouched.
- L653 _protected member_ `TMap<FName, int32> AddedMemberVariableMap;`
- L655 _protected prototype_ `void PropagateRuntimeSettingsFromBPToInstances();`
- L656 _protected prototype_ `void InitializeArchetypeInstances();`
- L658 _protected prototype_ `void HandlePackageDone(const FEndLoadPackageContext& Context);`
- L660 _protected prototype_ `virtual void HandlePackageDone();`
- L663 _protected prototype_ `virtual TObjectPtr<URigVMHost>& GetEditorHost() = 0;` — Our currently running rig vm instance
- L666 _protected prototype_ `void BroadcastRigVMPackageDone();` — RigVMBP, once end-loaded, will inform other RigVM-Dependent systems that Host instances are ready.
- L674 _protected prototype_ `void RemoveDeprecatedVMMemoryClass();` — Previously some memory classes were parented to the asset object however it is no longer supported since classes are now identified with only package name + class name, see FTopLevelAssetPath this function removes those deprecated class. new classes should be created by RecompileVM and parented to the Package during PostLoad
- L679 _protected member_ `TArray<TObjectPtr<URigVMMemoryStorageGeneratorClass>> OldMemoryStorageGeneratorClasses;` — During load, we do not want the GC to destroy the generator classes until all URigVMMemoryStorage objects are loaded, so we need to keep a pointer to the classes. These pointers will be removed on PreSave so that the GC can do its work.
- L681 _protected function_ `FOnRigVMExternalVariablesChanged& OnExternalVariablesChanged()`
- L683 _protected prototype_ `virtual void OnVariableAdded(const FName& InVarName);`
- L684 _protected prototype_ `virtual void OnVariableRemoved(const FGuid& InVarGuid);`
- L685 _protected prototype_ `virtual void OnVariableRenamed(const FGuid& InVarGuid, const FName& InNewVarName);`
- L686 _protected prototype_ `virtual void OnVariableTypeChanged(const FGuid& InVarGuid, FEdGraphPinType InOldPinType, FEdGraphPinType InNewPinType);`
- L688 _protected prototype_ `FName AddAssetVariableFromPinType(const FName& InName, const FEdGraphPinType& InType, bool bIsPublic = false, bool bIsReadOnly = false, FString InDefaultValue = FString());`
- L690 _protected function_ `virtual FOnRigVMNodeDoubleClicked& OnNodeDoubleClicked()`
- L691 _protected prototype_ `void BroadcastNodeDoubleClicked(URigVMNode* InNode);`
- L693 _protected function_ `virtual FOnRigVMGraphImported& OnGraphImported()`
- L694 _protected prototype_ `void BroadcastGraphImported(UEdGraph* InGraph);`
- L699 _protected function_ `virtual FRigVMOnBulkEditDialogRequestedDelegate& OnRequestBulkEditDialog()`
- L701 _protected function_ `virtual FRigVMOnBreakLinksDialogRequestedDelegate& OnRequestBreakLinksDialog()`
- L703 _protected function_ `virtual FRigVMOnPinTypeSelectionRequestedDelegate& OnRequestPinTypeSelectionDialog()`
- L708 _protected prototype_ `void BroadCastReportCompilerMessage(EMessageSeverity::Type InSeverity, UObject* InSubject, const FString& InMessage);`
- L711 _protected member_ `FOnRigVMExternalVariablesChanged ExternalVariablesChangedEvent;`
- L712 _protected prototype_ `void BroadcastExternalVariablesChangedEvent();`
- L714 _protected member_ `FOnRigVMNodeDoubleClicked NodeDoubleClickedEvent;`
- L715 _protected member_ `FOnRigVMGraphImported GraphImportedEvent;`
- L716 _protected member_ `FOnRigVMPostEditChangeChainProperty PostEditChangeChainPropertyEvent;`
- L717 _protected member_ `FOnRigVMLocalizeFunctionDialogRequested RequestLocalizeFunctionDialog;`
- L718 _protected member_ `FOnRigVMReportCompilerMessage ReportCompilerMessageEvent;`
- L719 _protected member_ `FRigVMOnBulkEditDialogRequestedDelegate RequestBulkEditDialog;`
- L720 _protected member_ `FRigVMOnBreakLinksDialogRequestedDelegate RequestBreakLinksDialog;`
- L721 _protected member_ `FRigVMOnPinTypeSelectionRequestedDelegate RequestPinTypeSelectionDialog;`
- L722 _protected member_ `FRigVMController_RequestJumpToHyperlinkDelegate RequestJumpToHyperlink;`
- L724 _protected prototype_ `UEdGraph* CreateEdGraph(URigVMGraph* InModel, bool bForce = false);`
- L725 _protected prototype_ `bool RemoveEdGraph(URigVMGraph* InModel);`
- L726 _protected prototype_ `void DestroyObject(UObject* InObject);`
- L727 _protected prototype_ `void CreateEdGraphForCollapseNodeIfNeeded(URigVMCollapseNode* InNode, bool bForce = false);`
- L728 _protected prototype_ `bool RemoveEdGraphForCollapseNode(URigVMCollapseNode* InNode, bool bNotify = false);`
- L730 _protected member_ `FCompilerResultsLog CompileLog;`
- L732 _protected prototype_ `TArray<TScriptInterface<IRigVMGraphFunctionHost>> GetReferencedFunctionHosts(bool bForceLoad) const;`
- L734 _protected member_ `FOnRigVMRequestInspectObject OnRequestInspectObjectEvent;`
- L735 _protected member_ `FOnRigVMRequestInspectMemoryStorage OnRequestInspectMemoryStorageEvent;`
- L737 _protected prototype_ `TArray<FRigVMReferenceNodeData> GetReferenceNodeData() const;`
- L738 _protected prototype_ `virtual void SetupDefaultObjectDuringCompilation(URigVMHost* InCDO);`
- L741 _protected member_ `static FSoftObjectPath PreDuplicateHostPath;`
- L742 _protected member_ `static FSoftObjectPath PreDuplicateFunctionLibraryPath;`
- L743 _protected member_ `static TArray<FRigVMEditorAssetInterfacePtr> sCurrentlyOpenedRigVMBlueprints;`
- L745 _protected prototype_ `void MarkDirtyDuringLoad();`
- L747 _protected prototype_ `bool IsMarkedDirtyDuringLoad() const;`
- L749 _protected member_ `bool bDirtyDuringLoad;`
- L750 _protected member_ `bool bErrorsDuringCompilation;`
- L751 _protected member_ `bool bSuspendPythonMessagesForRigVMClient;`
- L752 _protected member_ `bool bMarkBlueprintAsStructurallyModifiedPending;`
- L754 _protected prototype_ `void UpdateDebugMemoryOnHost(URigVMHost* InHost);`
- L756 _protected member_ `TOptional<TArray<TWeakObjectPtr<URigVMPin>>> WeakWatchedPins;`
- L758 _protected member_ `static FCriticalSection QueuedCompilerMessageDelegatesMutex;`
- L759 _protected member_ `static TArray<FOnRigVMReportCompilerMessage::FDelegate> QueuedCompilerMessageDelegates;`

#### class `URigVMEditorAsset`  
`class URigVMEditorAsset : public UObject, public IRigVMEditorAssetInterface, public IRigVMClientHost`  
_L794-1052_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UObject,IRigVMEditorAssetInterface,IRigVMClientHost`
- L799 _private member_ `FRigVMClient RigVMClient;` — `UPROPERTY()`
- L802 _private member_ `TArray<TObjectPtr<UEdGraph>> RootEdGraphs;` — `UPROPERTY()`
- L805 _private member_ `FRigVMEdGraphDisplaySettings GraphDisplaySettings;` — `UPROPERTY()`
- L808 _private member_ `FRigVMCompileSettings CompileSettings;` — `UPROPERTY()`
- L812 _private member_ `TArray<struct FEditedDocumentInfo> LastEditedDocuments;` — `UPROPERTY()` — Set of documents that were being edited in this blueprint, so we can open them right away
- L815 _private member_ `TUniquePtr<FCompilerResultsLog> CurrentMessageLog;` — If this asset is currently being compiled, the CurrentMessageLog will be the log currently being used to send logs to.
- L819 _private member_ `TObjectPtr<URigVMEdGraph> FunctionLibraryEdGraph;` — `UPROPERTY(Transient)`
- L823 _private member_ `TArray<TObjectPtr<UEdGraph>> FunctionGraphs;` — `UPROPERTY(Transient)` — Set of functions implemented for this class graphically
- L825 _private member_ `TArray<UEdGraphPin*> WatchedPin;`
- L828 _private member_ `bool bReferencedObjectPathsStored;` — `UPROPERTY()`
- L831 _private member_ `TArray<FSoftObjectPath> ReferencedObjectPaths;` — `UPROPERTY()`
- L836 _private member_ `TObjectPtr<URigVMHost> EditorHost = nullptr;` — `UPROPERTY(transient)` — Declaring these transient properties here instead of the IRigVMEditorAssetInterface class in order to have them as UPROPERTY, to avoid having stale pointers when GC happens
- L839 _private prototype_ `URigVMEditorAsset();`
- L841 _private function_ `virtual UClass* GetRuntimeAssetClass() const override`
- L842 _private prototype_ `URigVMRuntimeAsset* GetRuntimeAsset() const;`
- L843 _private function_ `virtual UObject* GetAssetObjectForEditor() override`
- L845 _private prototype_ `virtual void PreSave(FObjectPreSaveContext SaveContext) override;`
- L846 _private prototype_ `virtual void PostLoad() override;`
- L847 _private function_ `virtual bool IsPostLoadThreadSafe() const override`
- L848 _private prototype_ `virtual void PostTransacted(const FTransactionObjectEvent& TransactionEvent) override;`
- L849 _private prototype_ `virtual void PreDuplicate(FObjectDuplicationParameters& DupParams) override;`
- L850 _private prototype_ `virtual void PostDuplicate(bool bDuplicateForPIE) override;`
- L851 _private prototype_ `virtual void PostRename(UObject* OldOuter, const FName OldName) override;`
- L852 _private prototype_ `virtual void BeginDestroy() override;`
- L855 _private function_ `static void DeclareConstructClasses(TArray<FTopLevelAssetPath>& OutConstructClasses, const UClass* SpecificSubclass)`
- L858 _private function_ `virtual UObject* GetObject() override`
- L859 _private prototype_ `virtual void GetAllEdGraphs(TArray<UEdGraph*>& Graphs) const override;`
- L861 _private prototype_ `virtual TArray<FRigVMGraphVariableDescription> GetAssetVariables() const override;` — `UFUNCTION(BlueprintCallable, Category = "VM")`
- L862 _private function_ `virtual bool IsRegeneratingOnLoad() const override`
- L863 _private prototype_ `virtual FOnRigVMPreVariablesChanged& OnPreVariablesChanged() override;`
- L864 _private prototype_ `virtual FOnRigVMPostVariablesChanged& OnPostVariablesChanged() override;`
- L865 _private prototype_ `virtual FProperty* FindGeneratedPropertyByName(const FName& InName) override;`
- L866 _private prototype_ `virtual FName AddHostMemberVariableFromExternal(FRigVMExternalVariable InVariableToCreate, FString InDefaultValue = FString()) override;`
- L868 _private prototype_ `virtual FName AddMemberVariable(const FName& InName, const FString& InCPPType, bool bIsPublic = false, bool bIsReadOnly = false, FString InDefaultValue = TEXT("")) override;` — `UFUNCTION(BlueprintCallable, Category = "VM")`
- L870 _private prototype_ `virtual bool RemoveMemberVariable(const FName& InName) override;` — `UFUNCTION(BlueprintCallable, Category = "VM")`
- L872 _private prototype_ `virtual bool BulkRemoveMemberVariables(const TArray<FName>& InNames) override;` — `UFUNCTION(BlueprintCallable, Category = "VM")`
- L874 _private prototype_ `virtual bool RenameMemberVariable(const FName& InOldName, const FName& InNewName) override;` — `UFUNCTION(BlueprintCallable, Category = "VM")`
- L875 _private prototype_ `virtual bool ChangeMemberVariableType(const FName& InName, const FEdGraphPinType& InType) override;`
- L877 _private prototype_ `virtual bool ChangeMemberVariableType(const FName& InName, const FString& InCPPType, bool bIsPublic = false, bool bIsReadOnly = false, FString InDefaultValue = TEXT("")) override;` — `UFUNCTION(BlueprintCallable, Category = "VM")`
- L879 _private prototype_ `virtual bool SetVariableIndex(const FName& InName, int32 NewIndex) override;` — `UFUNCTION(BlueprintCallable, Category = "VM")`
- L880 _private prototype_ `virtual bool SetVariableIndex(const FGuid& InVariableGuid, int32 NewIndex);`
- L881 _private prototype_ `virtual FText GetVariableTooltip(const FName& InName) const override;`
- L882 _private prototype_ `virtual FString GetVariableCategory(const FName& InName) override;`
- L883 _private prototype_ `virtual FString GetVariableMetadataValue(const FName& InName, const FName& InKey) override;`
- L884 _private prototype_ `virtual bool SetVariableCategory(const FName& InName, const FString& InCategory) override;`
- L885 _private prototype_ `virtual bool SetVariableTooltip(const FName& InName, const FText& InTooltip) override;`
- L886 _private prototype_ `virtual bool SetVariableExposeOnSpawn(const FName& InName, const bool bInExposeOnSpawn) override;`
- L887 _private prototype_ `virtual bool SetVariableExposeToCinematics(const FName& InName, const bool bInExposeToCinematics) override;`
- L888 _private prototype_ `virtual bool SetVariablePrivate(const FName& InName, const bool bInPrivate) override;`
- L889 _private prototype_ `virtual bool SetVariablePublic(const FName& InName, const bool bIsPublic) override;`
- L890 _private prototype_ `virtual FString OnCopyVariable(const FName& InName) const override;`
- L891 _private prototype_ `virtual bool OnPasteVariable(const FString& InText) override;`
- L892 _private prototype_ `virtual UObject* GetObjectBeingDebugged(bool bEvenIfPendingKill = false) override;`
- L893 _private function_ `virtual UObject* GetObjectBeingDebugged(bool bEvenIfPendingKill = false) const override`
- L894 _private prototype_ `virtual const FString& GetObjectBeingDebuggedPath() const override;`
- L895 _private prototype_ `virtual UWorld* GetWorldBeingDebugged() const override;`
- L896 _private prototype_ `virtual void SetWorldBeingDebugged(UWorld* NewWorld) override;`
- L897 _private prototype_ `virtual TArray<UObject*> GetArchetypeInstances(bool bIncludeCDO, bool bIncludeDerivedClass) const override;`
- L898 _private prototype_ `virtual ERigVMAssetStatus GetAssetStatus() const override;`
- L899 _private prototype_ `virtual void SetAssetStatus(const ERigVMAssetStatus& InStatus) override;`
- L900 _private prototype_ `virtual bool IsUpToDate() const override;`
- L902 _private prototype_ `virtual URigVM* GetVM(bool bCreateIfNeeded) const override;` — virtual UClass* GetRigVMGeneratedClass() override { return nullptr; }
- L903 _private prototype_ `virtual FRigVMRuntimeSettings& GetVMRuntimeSettings() override;`
- L904 _private prototype_ `virtual void AddPinWatch(UEdGraphPin* InPin) override;`
- L905 _private prototype_ `virtual void RemovePinWatch(UEdGraphPin* InPin) override;`
- L906 _private prototype_ `virtual bool IsPinBeingWatched(const UEdGraphPin* InPin) const override;`
- L907 _private prototype_ `virtual bool NodeContainsWatchedPins(const UEdGraphNode* InNode) const override;`
- L908 _private prototype_ `virtual void ClearPinWatches() override;`
- L909 _private prototype_ `virtual void ForeachPinWatch(TFunctionRef<void(UEdGraphPin*)> Task) override;`
- L910 _private function_ `virtual FRigVMEdGraphDisplaySettings& GetRigGraphDisplaySettings() override`
- L911 _private function_ `virtual FRigVMCompileSettings& GetVMCompileSettings() override`
- L912 _private prototype_ `virtual void MarkAssetAsStructurallyModified(bool bSkipDirtyAssetStatus = false) override;`
- L913 _private prototype_ `virtual void MarkAssetAsModified(FPropertyChangedEvent PropertyChangedEvent = FPropertyChangedEvent(nullptr)) override;`
- L914 _private function_ `virtual TArray<TObjectPtr<UEdGraph>>& GetUberGraphs() override`
- L916 _private prototype_ `virtual FRigVMVariant& GetAssetVariant() override;` — `UFUNCTION(BlueprintCallable, Category = "VM")`
- L918 _private prototype_ `virtual FRigVMVariantRef GetAssetVariantRef() const override;` — `UFUNCTION(BlueprintCallable, Category = "VM")`
- L919 _private prototype_ `virtual const TArray<FRigVMGraphFunctionHeader>& GetPublicGraphFunctions() const override;`
- L920 _private prototype_ `virtual void SetPublicGraphFunctions(const TArray<FRigVMGraphFunctionHeader>& InHeaders) override;`
- L921 _private function_ `virtual UClass* GetRigVMGeneratedClassPrototype() const override`
- L922 _private function_ `virtual TArray<struct FEditedDocumentInfo>& GetLastEditedDocuments() override`
- L923 _private function_ `virtual UObject* GetDefaultsObject() override`
- L924 _private prototype_ `void DebuggingWorldRegistrationHelper(UObject* ObjectProvidingWorld, UObject* ValueToRegister);`
- L925 _private prototype_ `virtual void SetObjectBeingDebuggedSuper(UObject* NewObject) override;`
- L926 _private function_ `virtual void SetUberGraphs(const TArray<TObjectPtr<UEdGraph>>& InGraphs) override`
- L927 _private function_ `virtual void PostTransactedSuper(const FTransactionObjectEvent& TransactionEvent) override`
- L928 _private function_ `virtual void ReplaceDeprecatedNodesSuper() override`
- L929 _private function_ `virtual void PreDuplicateSuper(FObjectDuplicationParameters& DupParams) override`
- L930 _private prototype_ `virtual void PostDuplicateSuper(bool bDuplicateForPIE) override;`
- L931 _private function_ `virtual void GetAssetRegistryTagsSuper(FAssetRegistryTagsContext Context) const override`
- L932 _private function_ `virtual bool RequiresForceLoadMembersSuper(UObject* InObject) const override`
- L933 _private prototype_ `virtual TArray<FRigVMExternalVariable> GetExternalVariables(bool bFallbackToBlueprint) const override;`
- L934 _private prototype_ `virtual const UStruct* GetVariablesStruct() override;`
- L935 _private prototype_ `virtual uint8* GetVariablesMemory() override;`
- L936 _private prototype_ `virtual FString GetVariableDefaultValue(const FName& InName, bool bFromDebuggedObject) const override;`
- L937 _private prototype_ `virtual FRigVMExtendedExecuteContext* GetRigVMExtendedExecuteContext() override;`
- L938 _private function_ `virtual void PreCompile() override`
- L939 _private prototype_ `virtual TMap<FString, FSoftObjectPath>& GetUserDefinedStructGuidToPathName(bool bFromCDO) override;`
- L940 _private prototype_ `virtual TMap<FString, FSoftObjectPath>& GetUserDefinedEnumToPathName(bool bFromCDO) override;`
- L941 _private prototype_ `virtual TSet<TObjectPtr<UObject>>& GetUserDefinedTypesInUse(bool bFromCDO) override;`
- L942 _private function_ `virtual FCompilerResultsLog* GetCurrentMessageLog() const override`
- L943 _private prototype_ `virtual FRigVMDebugInfo& GetDebugInfo() override;`
- L944 _private function_ `virtual TObjectPtr<URigVMEdGraph>& GetFunctionLibraryEdGraph() override`
- L945 _private function_ `virtual TArray<TObjectPtr<UEdGraph>>& GetFunctionGraphs() override`
- L946 _private function_ `virtual bool& IsReferencedObjectPathsStored() override`
- L947 _private function_ `virtual TArray<FSoftObjectPath>& GetReferencedObjectPaths() override`
- L948 _private prototype_ `virtual TArray<FName>& GetSupportedEventNames() override;`
- L949 _private prototype_ `virtual void UpdateSupportedEventNames() override;`
- L950 _private prototype_ `virtual TArray<FRigVMReferenceNodeData>& GetFunctionReferenceNodeData() override;`
- L951 _private function_ `virtual void NotifyGraphRenamedSuper(class UEdGraph* Graph, FName OldName, FName NewName) override`
- L953 _private function_ `virtual URigVMHost* CreateRigVMHost()` — `UFUNCTION(BlueprintCallable, Category = "VM")`
- L954 _private prototype_ `virtual URigVMHost* CreateRigVMHostSuper(UObject* InOuter, FName InName = NAME_None, EObjectFlags InFlags = RF_NoFlags) override;`
- L955 _private prototype_ `virtual void AddUbergraphPage(URigVMEdGraph* RigVMEdGraph) override;`
- L956 _private prototype_ `virtual void AddLastEditedDocument(URigVMEdGraph* RigVMEdGraph) override;`
- L957 _private function_ `virtual void Compile() override`
- L958 _private prototype_ `virtual FCompilerResultsLog CompileBlueprint() override;`
- L959 _private function_ `virtual void PostEditChangeBlueprintActors() override`
- L961 _private function_ `virtual bool SplitAssetVariant() override` — `UFUNCTION(BlueprintCallable, Category = "Variants")`
- L963 _private function_ `virtual bool JoinAssetVariant(const FGuid& InGuid) override` — `UFUNCTION(BlueprintCallable, Category = "Variants")`
- L965 _private function_ `virtual TArray<FRigVMVariantRef> GetMatchingVariants() const override` — `UFUNCTION(BlueprintCallable, Category = "Variants")`
- L966 _private function_ `virtual void Serialize(FArchive& Ar) override`
- L967 _private function_ `virtual void SerializeSuper(FArchive& Ar) override`
- L968 _private prototype_ `virtual void PostSerialize(FArchive& Ar) override;`
- L969 _private function_ `virtual TObjectPtr<URigVMHost>& GetEditorHost() override`
- L970 _private function_ `virtual FString GetAssetName() const override`
- L971 _private function_ `virtual UClass* GetRigVMSchemaClass() const override`
- L972 _private function_ `virtual UScriptStruct* GetRigVMExecuteContextStruct() const override`
- L973 _private prototype_ `virtual UClass* GetRigVMEdGraphClass() const override;`
- L974 _private prototype_ `virtual UClass* GetRigVMEdGraphNodeClass() const override;`
- L975 _private prototype_ `virtual UClass* GetRigVMEdGraphSchemaClass() const override;`
- L976 _private prototype_ `virtual UClass* GetRigVMEditorSettingsClass() const override;`
- L977 _private function_ `virtual FRigVMClient* GetRigVMClient() override`
- L978 _private function_ `virtual const FRigVMClient* GetRigVMClient() const override`
- L979 _private function_ `virtual TScriptInterface<IRigVMGraphFunctionHost> GetRigVMGraphFunctionHost() override`
- L980 _private function_ `virtual TScriptInterface<const IRigVMGraphFunctionHost> GetRigVMGraphFunctionHost() const override`
- L981 _private function_ `virtual UObject* GetEditorObjectForRigVMGraph(const URigVMGraph* InVMGraph) const override`
- L982 _private function_ `virtual URigVMGraph* GetRigVMGraphForEditorObject(UObject* InObject) const override`
- L983 _private function_ `virtual void HandleRigVMGraphAdded(const FRigVMClient* InClient, const FString& InNodePath) override`
- L984 _private function_ `virtual void HandleRigVMGraphRemoved(const FRigVMClient* InClient, const FString& InNodePath) override`
- L985 _private function_ `virtual void HandleRigVMGraphRenamed(const FRigVMClient* InClient, const FString& InOldNodePath, const FString& InNewNodePath) override`
- L986 _private function_ `virtual void HandleConfigureRigVMController(const FRigVMClient* InClient, URigVMController* InControllerToConfigure) override`
- L987 _private function_ `virtual void IncrementVMRecompileBracket() override`
- L988 _private function_ `virtual void DecrementVMRecompileBracket() override`
- L989 _private function_ `virtual void RefreshAllModels(ERigVMLoadType InLoadType = ERigVMLoadType::PostLoad) override`
- L990 _private function_ `virtual void OnRigVMRegistryChanged() override`
- L991 _private function_ `virtual URigVMGraph* GetModel(const FString& InNodePath) const override`
- L992 _private function_ `virtual FRigVMGetFocusedGraph& OnGetFocusedGraph() override`
- L993 _private function_ `virtual const FRigVMGetFocusedGraph& OnGetFocusedGraph() const override`
- L994 _private function_ `virtual void SetupPinRedirectorsForBackwardsCompatibility() override`
- L995 _private function_ `virtual FRigVMGraphModifiedEvent& OnModified() override`
- L996 _private function_ `virtual bool IsFunctionPublic(const FName& InFunctionName) const override`
- L997 _private function_ `virtual void MarkFunctionPublic(const FName& InFunctionName, bool bIsPublic = true) override`
- L998 _private function_ `virtual void RenameGraph(const FString& InNodePath, const FName& InNewName) override`
- L1001 _private prototype_ `virtual void RecompileVM() override;` — `UFUNCTION(BlueprintCallable, Category = "RigVM Asset")`
- L1003 _private function_ `virtual void RecompileVMIfRequired() override` — `UFUNCTION(BlueprintCallable, Category = "RigVM Asset")`
- L1005 _private function_ `virtual void RequestAutoVMRecompilation() override` — `UFUNCTION(BlueprintCallable, Category = "RigVM Asset")`
- L1007 _private function_ `virtual void SetAutoVMRecompile(bool bAutoRecompile) override` — `UFUNCTION(BlueprintCallable, Category = "RigVM Asset")`
- L1009 _private function_ `virtual bool GetAutoVMRecompile() const override` — `UFUNCTION(BlueprintCallable, Category = "RigVM Asset")`
- L1011 _private function_ `virtual void RequestRigVMInit() override` — `UFUNCTION(BlueprintCallable, Category = "RigVM Asset")`
- L1013 _private function_ `virtual URigVMGraph* GetModel(const UEdGraph* InEdGraph = nullptr) const override` — `UFUNCTION(BlueprintCallable, Category = "RigVM Asset")`
- L1015 _private function_ `virtual URigVMGraph* GetDefaultModel() const override` — `UFUNCTION(BlueprintCallable, Category = "RigVM Asset")`
- L1017 _private function_ `virtual TArray<URigVMGraph*> GetAllModels() const override` — `UFUNCTION(BlueprintCallable, Category = "RigVM Asset")`
- L1019 _private function_ `virtual URigVMFunctionLibrary* GetLocalFunctionLibrary() const override` — `UFUNCTION(BlueprintCallable, Category = "RigVM Asset")`
- L1021 _private function_ `virtual URigVMFunctionLibrary* GetOrCreateLocalFunctionLibrary(bool bSetupUndoRedo = true) override` — `UFUNCTION(BlueprintCallable, Category = "RigVM Asset")`
- L1023 _private function_ `virtual URigVMGraph* AddModel(FString InName = TEXT("Rig Graph"), bool bSetupUndoRedo = true, bool bPrintPythonCommand = true)` — `UFUNCTION(BlueprintCallable, Category = "RigVM Asset")`
- L1025 _private function_ `virtual bool RemoveModel(FString InName = TEXT("Rig Graph"), bool bSetupUndoRedo = true, bool bPrintPythonCommand = true)` — `UFUNCTION(BlueprintCallable, Category = "RigVM Asset")`
- L1027 _private function_ `virtual URigVMGraph* GetFocusedModel() const override` — `UFUNCTION(BlueprintCallable, Category = "RigVM Asset")`
- L1029 _private function_ `virtual URigVMController* GetController(const URigVMGraph* InGraph = nullptr) const override` — `UFUNCTION(BlueprintCallable, Category = "RigVM Asset")`
- L1030 _private function_ `virtual URigVMController* GetController(const UEdGraph* InGraph) const override`
- L1032 _private function_ `virtual URigVMController* GetControllerByName(const FString InGraphName = TEXT("")) const override` — `UFUNCTION(BlueprintCallable, Category = "RigVM Asset")`
- L1034 _private function_ `virtual URigVMController* GetOrCreateController(URigVMGraph* InGraph = nullptr) override` — `UFUNCTION(BlueprintCallable, Category = "RigVM Asset")`
- L1035 _private function_ `virtual URigVMController* GetOrCreateController(const UEdGraph* InGraph) override`
- L1037 _private function_ `virtual TArray<FString> GeneratePythonCommands() override` — `UFUNCTION(BlueprintCallable, Category = "RigVM Asset")`
- L1039 _private function_ `virtual TArray<FString> GeneratePythonCommands(const FString InNewBlueprintName) override` — `UE_DEPRECATED(5.8, "Use TArray<FString> GeneratePythonCommands() instead.")`
- L1040 _private prototype_ `virtual const TArray<FString>& GetRequiredPlugins(bool bRefresh = true) const override;`
- L1041 _private prototype_ `virtual FRigVMPropertyBag* GetVariablesPropertyBag() override;`
- L1042 _private prototype_ `virtual FRigVMDrawContainer& GetDrawContainer() override;`
- L1043 _private function_ `virtual const FLazyName& GetPanelNodeFactoryName() const override`
- L1044 _private function_ `virtual const FLazyName& GetPanelPinFactoryName() const override`
- L1047 _private prototype_ `virtual TArray<FString> GeneratePythonContextCommands(const FString InNewBlueprintName, bool bCreateAsset) override;`
- L1050 _private member_ `FOnRigVMPreVariablesChanged DummyOnPreVariableChanged;`
- L1051 _private member_ `FOnRigVMPostVariablesChanged DummyOnPostVariableChanged;`

#### class `FRigVMBlueprintCompileScope`  
`class FRigVMBlueprintCompileScope`  
_L1054-1065_
- L1058 _public prototype_ `FRigVMBlueprintCompileScope(FRigVMEditorAssetInterfacePtr InBlueprint);`
- L1060 _public prototype_ `~FRigVMBlueprintCompileScope();`
- L1064 _private member_ `FRigVMEditorAssetInterfacePtr Blueprint;`

#### struct `FGuardSkipDirtyBlueprintStatus`  
`struct FGuardSkipDirtyBlueprintStatus : private FNoncopyable`  
_L1067-1092_
- inherits: `FNoncopyable`
- L1069 _public function_ `[[nodiscard]] FGuardSkipDirtyBlueprintStatus(FRigVMEditorAssetInterfacePtr InBlueprint, bool bNewValue)`
- L1078 _public function_ `~FGuardSkipDirtyBlueprintStatus()`
- L1090 _private member_ `TWeakInterfacePtr<IRigVMEditorAssetInterface> WeakBlueprint;`
- L1091 _private member_ `bool bOldValue = false;`

#### Free symbols / members of external scopes

- L23 _macro_ `#define UE_API RIGVMDEVELOPER_API`
- L29 _namespace_ `namespace UE`
- L29 _namespace_ `namespace RigVM` (scope `UE`)
- L29 _namespace_ `namespace Editor` (scope `UE::RigVM`)
- L29 _namespace_ `namespace Tools` (scope `UE::RigVM::Editor`)
- L40 _typedef_ `typedef TScriptInterface<IRigVMEditorAssetInterface> FRigVMEditorAssetInterfacePtr;`
- L42 _typedef_ `using IRigVMAssetInterface = IRigVMEditorAssetInterface;`
- L43 _typedef_ `using URigVMAssetInterface = URigVMEditorAssetInterface;`
- L44 _typedef_ `using FRigVMAssetInterfacePtr = FRigVMEditorAssetInterfacePtr;`
- L46 _delegate_ `DECLARE_EVENT_ThreeParams(IRigVMEditorAssetInterface, FOnRigVMCompiledEvent, UObject*, URigVM*, FRigVMExtendedExecuteContext&);`
- L46 _prototype_ `DECLARE_EVENT_ThreeParams(IRigVMEditorAssetInterface, FOnRigVMCompiledEvent, UObject*, URigVM*, FRigVMExtendedExecuteContext&);`
- L47 _delegate_ `DECLARE_EVENT_OneParam(IRigVMEditorAssetInterface, FOnRigVMRefreshEditorEvent, FRigVMEditorAssetInterfacePtr);`
- L47 _prototype_ `DECLARE_EVENT_OneParam(IRigVMEditorAssetInterface, FOnRigVMRefreshEditorEvent, FRigVMEditorAssetInterfacePtr);`
- L48 _delegate_ `DECLARE_EVENT_FourParams(IRigVMEditorAssetInterface, FOnRigVMVariableDroppedEvent, UObject*, FProperty*, const FVector2D&, const FVector2D&);`
- L48 _prototype_ `DECLARE_EVENT_FourParams(IRigVMEditorAssetInterface, FOnRigVMVariableDroppedEvent, UObject*, FProperty*, const FVector2D&, const FVector2D&);`
- L49 _delegate_ `DECLARE_EVENT_OneParam(IRigVMEditorAssetInterface, FOnRigVMExternalVariablesChanged, const TArray<FRigVMExternalVariable>&);`
- L49 _prototype_ `DECLARE_EVENT_OneParam(IRigVMEditorAssetInterface, FOnRigVMExternalVariablesChanged, const TArray<FRigVMExternalVariable>&);`
- L50 _delegate_ `DECLARE_EVENT_TwoParams(IRigVMEditorAssetInterface, FOnRigVMNodeDoubleClicked, FRigVMEditorAssetInterfacePtr, URigVMNode*);`
- L50 _prototype_ `DECLARE_EVENT_TwoParams(IRigVMEditorAssetInterface, FOnRigVMNodeDoubleClicked, FRigVMEditorAssetInterfacePtr, URigVMNode*);`
- L51 _delegate_ `DECLARE_EVENT_OneParam(IRigVMEditorAssetInterface, FOnRigVMGraphImported, UEdGraph*);`
- L51 _prototype_ `DECLARE_EVENT_OneParam(IRigVMEditorAssetInterface, FOnRigVMGraphImported, UEdGraph*);`
- L52 _delegate_ `DECLARE_EVENT_OneParam(IRigVMEditorAssetInterface, FOnRigVMPostEditChangeChainProperty, FPropertyChangedChainEvent&);`
- L52 _prototype_ `DECLARE_EVENT_OneParam(IRigVMEditorAssetInterface, FOnRigVMPostEditChangeChainProperty, FPropertyChangedChainEvent&);`
- L53 _delegate_ `DECLARE_EVENT_FourParams(IRigVMEditorAssetInterface, FOnRigVMLocalizeFunctionDialogRequested, FRigVMGraphFunctionIdentifier&, URigVMController*, IRigVMGraphFunctionHost*, bool);`
- L53 _prototype_ `DECLARE_EVENT_FourParams(IRigVMEditorAssetInterface, FOnRigVMLocalizeFunctionDialogRequested, FRigVMGraphFunctionIdentifier&, URigVMController*, IRigVMGraphFunctionHost*, bool);`
- L54 _delegate_ `DECLARE_EVENT_ThreeParams(IRigVMEditorAssetInterface, FOnRigVMReportCompilerMessage, EMessageSeverity::Type, UObject*, const FString&);`
- L54 _prototype_ `DECLARE_EVENT_ThreeParams(IRigVMEditorAssetInterface, FOnRigVMReportCompilerMessage, EMessageSeverity::Type, UObject*, const FString&);`
- L55 _delegate_ `DECLARE_DELEGATE_RetVal_FourParams(FRigVMController_BulkEditResult, FRigVMOnBulkEditDialogRequestedDelegate, FRigVMEditorAssetInterfacePtr, URigVMController*, URigVMLibraryNode*, ERigVMControllerBulkEditType);`
- L55 _prototype_ `DECLARE_DELEGATE_RetVal_FourParams(FRigVMController_BulkEditResult, FRigVMOnBulkEditDialogRequestedDelegate, FRigVMEditorAssetInterfacePtr, URigVMController*, URigVMLibraryNode*, ERigVMControllerBulkEditType);`
- L56 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FRigVMOnBreakLinksDialogRequestedDelegate, TArray<URigVMLink*>);`
- L56 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FRigVMOnBreakLinksDialogRequestedDelegate, TArray<URigVMLink*>);`
- L57 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(TRigVMTypeIndex, FRigVMOnPinTypeSelectionRequestedDelegate, const TArray<TRigVMTypeIndex>&);`
- L57 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(TRigVMTypeIndex, FRigVMOnPinTypeSelectionRequestedDelegate, const TArray<TRigVMTypeIndex>&);`
- L58 _delegate_ `DECLARE_EVENT(IRigVMEditorAssetInterface, FOnRigVMBreakpointAdded);`
- L58 _prototype_ `DECLARE_EVENT(IRigVMEditorAssetInterface, FOnRigVMBreakpointAdded);`
- L59 _delegate_ `DECLARE_EVENT_OneParam(IRigVMEditorAssetInterface, FOnRigVMRequestInspectObject, const TArray<UObject*>& );`
- L59 _prototype_ `DECLARE_EVENT_OneParam(IRigVMEditorAssetInterface, FOnRigVMRequestInspectObject, const TArray<UObject*>& );`
- L60 _delegate_ `DECLARE_EVENT_OneParam(IRigVMEditorAssetInterface, FOnRigVMRequestInspectMemoryStorage, const TArray<FRigVMMemoryStorageStruct*>&);`
- L60 _prototype_ `DECLARE_EVENT_OneParam(IRigVMEditorAssetInterface, FOnRigVMRequestInspectMemoryStorage, const TArray<FRigVMMemoryStorageStruct*>&);`
- L61 _delegate_ `DECLARE_EVENT_OneParam( IRigVMEditorAssetInterface, FOnRigVMAssetChangedEvent, class UObject * );`
- L61 _prototype_ `DECLARE_EVENT_OneParam( IRigVMEditorAssetInterface, FOnRigVMAssetChangedEvent, class UObject * );`
- L62 _delegate_ `DECLARE_EVENT_OneParam(IRigVMEditorAssetInterface, FOnRigVMSetObjectBeingDebugged, UObject* );`
- L62 _prototype_ `DECLARE_EVENT_OneParam(IRigVMEditorAssetInterface, FOnRigVMSetObjectBeingDebugged, UObject* );`

### `Plugins/Runtime/RigVM/Source/RigVMDeveloper/Public/RigVMJsonUtils.h` (Public)


#### struct `RigVMJsonUtils::TRigVMJsonPrintPolicy`  
`template <class CharType> struct TRigVMJsonPrintPolicy : public TPrettyJsonPrintPolicy<CharType>`  
_L25-28_
- inherits: `TPrettyJsonPrintPolicy<CharType>`

#### struct `RigVMJsonUtils::FIntrospectionSettings`  
`struct FIntrospectionSettings`  
_L36-53_
- L38 _public prototype_ `FIntrospectionSettings(FRigVMRegistryHandle& InRegistry);`
- L40 _public prototype_ `void AddDiscoveredType(const TRigVMTypeIndex& InTypeIndex);`
- L42 _public member_ `FRigVMRegistryHandle& Registry;`
- L43 _public member_ `TObjectPtr<URigVMSchema> Schema = nullptr;`
- L44 _public member_ `TObjectPtr<URigVMEdGraphSchema> EdGraphSchema = nullptr;`
- L45 _public member_ `bool bExcludeFunctions = false;`
- L46 _public member_ `bool bExcludeDispatches = false;`
- L47 _public member_ `bool bExcludeDeprecated = false;`
- L48 _public member_ `bool bMergeTemplates = false;`
- L49 _public member_ `bool bCreateImages = false;`
- L50 _public member_ `FString FilePath;`
- L51 _public member_ `TSet<TRigVMTypeIndex> DiscoveredTypes;`
- L52 _public member_ `TArray<FString> CommandsToRun;`

#### Free symbols / members of external scopes

- L22 _namespace_ `namespace RigVMJsonUtils`
- L30 _typedef_ `typedef TJsonWriter< TCHAR, TRigVMJsonPrintPolicy< TCHAR > > FJsonWriter;` (scope `RigVMJsonUtils`)
- L31 _typedef_ `typedef TSharedRef< FJsonWriter > FJsonWriterRef;` (scope `RigVMJsonUtils`)
- L32 _typedef_ `typedef TJsonWriterFactory< TCHAR, TRigVMJsonPrintPolicy< TCHAR > > FJsonFactory;` (scope `RigVMJsonUtils`)
- L34 _prototype_ `FJsonWriterRef MakeJsonWriter(FString& OutJsonText);` (scope `RigVMJsonUtils`)
- L56 _prototype_ `TSharedPtr<FJsonObject> AvailableNodesToJson(FIntrospectionSettings& InSettings, TFunction<bool(const UScriptStruct*)> InFilterCallback);` (scope `RigVMJsonUtils`) — introspection for the registry
- L57 _prototype_ `TSharedPtr<FJsonObject> ToJson(FIntrospectionSettings& InSettings, const FRigVMFunction* InFunction);` (scope `RigVMJsonUtils`)
- L58 _prototype_ `TSharedPtr<FJsonObject> ToJson(FIntrospectionSettings& InSettings, const FRigVMDispatchFactory* InFactory);` (scope `RigVMJsonUtils`)
- L59 _prototype_ `TSharedPtr<FJsonObject> ToJson(FIntrospectionSettings& InSettings, const TRigVMTypeIndex& InTypeIndex);` (scope `RigVMJsonUtils`)
- L60 _prototype_ `bool GenericStructAttributesToJson(FIntrospectionSettings& InSettings, const UScriptStruct* InStruct, FJsonObject* OutJsonObject);` (scope `RigVMJsonUtils`)
- L63 _prototype_ `TSharedPtr<FJsonObject> ToJson(FIntrospectionSettings& InSettings, const IRigVMEditorAssetInterface* InAsset);` (scope `RigVMJsonUtils`) — introspection for existing graphs
- L64 _prototype_ `TSharedPtr<FJsonObject> ToJson(FIntrospectionSettings& InSettings, const URigVMGraph* InGraph, bool bOnlySelection = false);` (scope `RigVMJsonUtils`)
- L65 _prototype_ `TSharedPtr<FJsonObject> ToJson(FIntrospectionSettings& InSettings, const URigVMNode* InNode);` (scope `RigVMJsonUtils`)
- L66 _prototype_ `TSharedPtr<FJsonObject> ToJson(FIntrospectionSettings& InSettings, const URigVMPin* InPin);` (scope `RigVMJsonUtils`)
- L67 _prototype_ `TSharedPtr<FJsonObject> ToJson(FIntrospectionSettings& InSettings, const URigVMLink* InLink);` (scope `RigVMJsonUtils`)
- L68 _prototype_ `TSharedPtr<FJsonObject> ToJson(FIntrospectionSettings& InSettings, const FRigVMGraphVariableDescription& InVariable);` (scope `RigVMJsonUtils`)
- L71 _prototype_ `FString StructValueToJson(const UScriptStruct* InScriptStruct, const void* InMemory);` (scope `RigVMJsonUtils`) — string conversion

### `Plugins/Runtime/RigVM/Source/RigVMDeveloper/Public/RigVMModel/Nodes/RigVMAggregateNode.h` (Public)


#### class `URigVMAggregateNode`  
`class URigVMAggregateNode : public URigVMCollapseNode`  
_L19-61_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `URigVMCollapseNode`
- desc: The Aggregate Node contains a subgraph of nodes with aggregate pins (2in+1out or 1out+2in) connected to each other. For example, a unit node IntAdd which adds 2 integers and provides Result=A+B could have A, B and Result as aggregates in order to add additional input pins to construct an Aggregate Node that computes Result=A+B+C.
- L26 _public prototype_ `URigVMAggregateNode();` — default constructor
- L29 _public prototype_ `virtual FString GetNodeTitle() const override;` — URigVMUnitNode interface
- L30 _public prototype_ `virtual FLinearColor GetNodeColor() const override;`
- L31 _public prototype_ `virtual FName GetMethodName() const;`
- L32 _public prototype_ `virtual FText GetToolTipText() const override;`
- L33 _public prototype_ `virtual FText GetToolTipTextForPin(const URigVMPin* InPin) const override;`
- L36 _public function_ `virtual bool IsAggregate() const override`
- L38 _public prototype_ `virtual bool IsInputAggregate() const override;`
- L40 _public prototype_ `URigVMNode* GetFirstInnerNode() const;`
- L41 _public prototype_ `URigVMNode* GetLastInnerNode() const;`
- L43 _public prototype_ `virtual URigVMPin* GetFirstAggregatePin() const override;`
- L44 _public prototype_ `virtual URigVMPin* GetSecondAggregatePin() const override;`
- L45 _public prototype_ `virtual URigVMPin* GetOppositeAggregatePin() const override;`
- L46 _public prototype_ `virtual TArray<URigVMPin*> GetAggregateInputs() const override;`
- L47 _public prototype_ `virtual TArray<URigVMPin*> GetAggregateOutputs() const override;`
- L51 _protected prototype_ `virtual FString GetOriginalDefaultValueForRootPin(const URigVMPin* InRootPin) const override;`
- L55 _private prototype_ `virtual void InvalidateCache() override;`
- L57 _private member_ `mutable URigVMNode* FirstInnerNodeCache;`
- L58 _private member_ `mutable URigVMNode* LastInnerNodeCache;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API RIGVMDEVELOPER_API`

### `Plugins/Runtime/RigVM/Source/RigVMDeveloper/Public/RigVMModel/Nodes/RigVMArrayNode.h` (Public)


#### class `UDEPRECATED_RigVMArrayNode`  
`class UDEPRECATED_RigVMArrayNode : public URigVMTemplateNode`  
_L15-45_
- reflection: `UCLASS(MinimalAPI, BlueprintType, Deprecated)`
- inherits: `URigVMTemplateNode`
- desc: The Array Node represents one of a series available array operations such as SetNum, GetAtIndex etc.
- L22 _public prototype_ `UDEPRECATED_RigVMArrayNode();` — Default constructor
- L26 _public prototype_ `ERigVMOpCode GetOpCode() const;` — `UFUNCTION(BlueprintCallable, Category = RigVMArrayNode)` — Returns the op code of this node
- L30 _public prototype_ `FString GetCPPType() const;` — `UFUNCTION(BlueprintCallable, Category = RigVMArrayNode)` — Returns the C++ data type of the element
- L34 _public prototype_ `UObject* GetCPPTypeObject() const;` — `UFUNCTION(BlueprintCallable, Category = RigVMArrayNode)` — Returns the C++ data type struct of the array (or nullptr)
- L39 _private member_ `ERigVMOpCode OpCode;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API RIGVMDEVELOPER_API`

### `Plugins/Runtime/RigVM/Source/RigVMDeveloper/Public/RigVMModel/Nodes/RigVMBranchNode.h` (Public)


#### class `UDEPRECATED_RigVMBranchNode`  
`class UDEPRECATED_RigVMBranchNode : public URigVMNode`  
_L14-17_
- reflection: `UCLASS(MinimalAPI, BlueprintType, Deprecated)`
- inherits: `URigVMNode`
- desc: A branch node is used to branch between two blocks of execution

### `Plugins/Runtime/RigVM/Source/RigVMDeveloper/Public/RigVMModel/Nodes/RigVMCollapseNode.h` (Public)


#### class `URigVMCollapseNode`  
`class URigVMCollapseNode : public URigVMLibraryNode`  
_L16-59_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `URigVMLibraryNode`
- desc: The Collapse Node is a library node which stores the function and its nodes directly within the node itself.
- L22 _public prototype_ `URigVMCollapseNode();`
- L25 _public prototype_ `virtual FText GetToolTipText() const override;` — RigVM node interface
- L28 _public function_ `virtual FString GetNodeCategory() const override` — Library node interface
- L29 _public function_ `virtual FString GetNodeKeywords() const override`
- L30 _public function_ `virtual FString GetNodeDescription() const override`
- L31 _public prototype_ `virtual URigVMFunctionLibrary* GetLibrary() const override;`
- L32 _public function_ `bool IsGraphFunctionDefinition() const`
- L33 _public function_ `virtual URigVMGraph* GetContainedGraph() const override`
- L34 _public prototype_ `virtual TArray<FRigVMExternalVariable> GetExternalVariables() const override;`
- L35 _public prototype_ `virtual bool IsPure() const override;`
- L37 _public prototype_ `FString GetEditorSubGraphName() const;`
- L39 _public prototype_ `FGuid FindPinGuid(const URigVMPin* InPin) const;`
- L43 _private member_ `TObjectPtr<URigVMGraph> ContainedGraph;` — `UPROPERTY()`
- L46 _private member_ `FString NodeCategory;` — `UPROPERTY()`
- L49 _private member_ `FString NodeKeywords;` — `UPROPERTY()`
- L52 _private member_ `FString NodeDescription;` — `UPROPERTY()`
- L55 _private member_ `TMap<FName, FGuid> PinNameToGuid;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API RIGVMDEVELOPER_API`

### `Plugins/Runtime/RigVM/Source/RigVMDeveloper/Public/RigVMModel/Nodes/RigVMCommentNode.h` (Public)


#### class `URigVMCommentNode`  
`class URigVMCommentNode : public URigVMNode`  
_L25-68_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `URigVMNode`
- desc: Comment Nodes can be used to annotate a Graph by adding colored grouping as well as user provided text. Comment Nodes are purely cosmetic and don't contribute to the runtime result of the Graph / Function.
- L32 _public prototype_ `URigVMCommentNode();` — Default constructor
- L35 _public function_ `virtual FString GetNodeTitle() const override` — Override of node title
- L39 _public prototype_ `FString GetCommentText() const;` — `UFUNCTION(BlueprintCallable, Category = RigVMCommentNode)` — Returns the current user provided text of this comment.
- L43 _public prototype_ `int32 GetCommentFontSize() const;` — `UFUNCTION(BlueprintCallable, Category = RigVMCommentNode)` — Returns the current user provided font size of this comment.
- L47 _public prototype_ `bool GetCommentBubbleVisible() const;` — `UFUNCTION(BlueprintCallable, Category = RigVMCommentNode)` — Returns the current user provided bubble visibility of this comment.
- L51 _public prototype_ `bool GetCommentColorBubble() const;` — `UFUNCTION(BlueprintCallable, Category = RigVMCommentNode)` — Returns the current user provided bubble color inheritance of this comment.
- L56 _private member_ `FString CommentText;` — `UPROPERTY()`
- L59 _private member_ `int32 FontSize;` — `UPROPERTY()`
- L62 _private member_ `bool bBubbleVisible;` — `UPROPERTY()`
- L65 _private member_ `bool bColorBubble;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API RIGVMDEVELOPER_API`

### `Plugins/Runtime/RigVM/Source/RigVMDeveloper/Public/RigVMModel/Nodes/RigVMDispatchNode.h` (Public)


#### class `URigVMDispatchNode`  
`class URigVMDispatchNode : public URigVMTemplateNode`  
_L32-97_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `URigVMTemplateNode`
- desc: The Struct Node represents a Function Invocation of a RIGVM_METHOD declared on a USTRUCT. Struct Nodes have input / output pins for all struct UPROPERTY members.
- L39 _public prototype_ `virtual FString GetNodeTitle() const override;` — Override node functions
- L40 _public prototype_ `virtual bool SupportsRenaming() const override;`
- L41 _public prototype_ `virtual FText GetToolTipText() const override;`
- L42 _public prototype_ `virtual FLinearColor GetNodeColor() const override;`
- L43 _public prototype_ `virtual bool IsDefinedAsConstant() const override;`
- L44 _public prototype_ `virtual bool IsDefinedAsVarying() const override;`
- L45 _public prototype_ `virtual bool IsPure() const override;`
- L46 _public prototype_ `virtual const TArray<FName>& GetControlFlowBlocks() const override;`
- L47 _public prototype_ `virtual const bool IsControlFlowBlockSliced(const FName& InBlockName) const override;`
- L48 _public prototype_ `virtual TArray<URigVMPin*> GetAggregateInputs() const override;`
- L49 _public prototype_ `virtual TArray<URigVMPin*> GetAggregateOutputs() const override;`
- L50 _public prototype_ `virtual FName GetNextAggregateName(const FName& InLastAggregatePinName) const override;`
- L51 _public prototype_ `virtual FRigVMStructUpgradeInfo GetUpgradeInfo() const override;`
- L52 _public prototype_ `virtual FName GetDisplayNameForPin(const URigVMPin* InPin) const override;`
- L54 _public prototype_ `const FRigVMDispatchFactory* GetFactory() const;`
- L55 _public prototype_ `virtual bool IsOutDated() const override;`
- L56 _public prototype_ `virtual FString GetDeprecatedMetadata() const override;`
- L58 _public prototype_ `FRigVMDispatchContext GetDispatchContext() const;`
- L62 _public prototype_ `TSharedPtr<FStructOnScope> ConstructFactoryInstance(bool bUseDefault = false, FString* OutFactoryDefault = nullptr) const;` — Returns an instance of the factory with the current values. @param bUseDefault If set to true the default struct will be created - otherwise the struct will contains the values from the node
- L69 _public function_ `T ConstructFactoryInstance() const`
- L83 _protected prototype_ `virtual FText GetToolTipTextForPin(const URigVMPin* InPin) const override;`
- L84 _protected prototype_ `const UScriptStruct* GetFactoryStruct() const;`
- L85 _protected prototype_ `virtual void InvalidateCache() override;`
- L86 _protected prototype_ `virtual bool ShouldInputPinComputeLazily(const URigVMPin* InPin) const override;`
- L87 _protected prototype_ `virtual bool IsPinConstant(const URigVMPin* InPin) const override;`
- L88 _protected prototype_ `virtual FString GetOriginalDefaultValueForRootPin(const URigVMPin* InRootPin) const override;`
- L89 _protected prototype_ `FString GetFactoryDefaultValue() const;`
- L93 _private member_ `mutable FRigVMTemplateTypeMap TypesFromPins;`
- L94 _private member_ `mutable const FRigVMDispatchFactory* CachedFactory = nullptr;`

#### Free symbols / members of external scopes

- L19 _macro_ `#define UE_API RIGVMDEVELOPER_API`

### `Plugins/Runtime/RigVM/Source/RigVMDeveloper/Public/RigVMModel/Nodes/RigVMEnumNode.h` (Public)


#### class `URigVMEnumNode`  
`class URigVMEnumNode : public URigVMNode`  
_L24-67_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `URigVMNode`
- desc: The Enum Node represents a constant enum value for use within the graph.
- L31 _public prototype_ `URigVMEnumNode();` — Default constructor
- L34 _public prototype_ `virtual FString GetNodeTitle() const;` — Override of node title
- L38 _public prototype_ `UEnum* GetEnum() const;` — `UFUNCTION(BlueprintCallable, Category = RigVMEnumNode)` — Returns the enum itself
- L42 _public prototype_ `FString GetCPPType() const;` — `UFUNCTION(BlueprintCallable, Category = RigVMEnumNode)` — Returns the C++ data type of the parameter
- L46 _public prototype_ `UObject* GetCPPTypeObject() const;` — `UFUNCTION(BlueprintCallable, Category = RigVMEnumNode)` — Returns the C++ data type struct of the parameter (or nullptr)
- L49 _public prototype_ `FString GetDefaultValue(const URigVMPin::FPinOverride& InOverride = URigVMPin::EmptyPinOverride) const;` — Returns the default value of the parameter as a string
- L52 _public function_ `virtual FLinearColor GetNodeColor() const override` — Override of node title
- L54 _public function_ `virtual bool IsDefinedAsVarying() const override`
- L58 _private member_ `static const TCHAR* EnumName;`
- L59 _private member_ `static const inline TCHAR* EnumValueName = TEXT("Enu`
- L60 _private member_ `static const inline TCHAR* EnumIndexName = TEXT("Enu`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API RIGVMDEVELOPER_API`

### `Plugins/Runtime/RigVM/Source/RigVMDeveloper/Public/RigVMModel/Nodes/RigVMFunctionEntryNode.h` (Public)


#### class `URigVMFunctionEntryNode`  
`class URigVMFunctionEntryNode : public URigVMFunctionInterfaceNode`  
_L15-35_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `URigVMFunctionInterfaceNode`
- desc: The Function Entry node is used to provide access to the input pins of the library node for links within.
- L22 _public function_ `virtual UScriptStruct* GetScriptStruct() const override` — Override template node functions
- L23 _public function_ `virtual const FRigVMTemplate* GetTemplate() const override`
- L24 _public function_ `virtual FName GetNotation() const override`
- L27 _public prototype_ `virtual bool IsWithinLoop() const override;` — Override node functions
- L30 _public prototype_ `virtual FString GetNodeTitle() const override;` — URigVMNode interface

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API RIGVMDEVELOPER_API`

### `Plugins/Runtime/RigVM/Source/RigVMDeveloper/Public/RigVMModel/Nodes/RigVMFunctionInterfaceNode.h` (Public)


#### class `URigVMFunctionInterfaceNode`  
`class URigVMFunctionInterfaceNode : public URigVMTemplateNode`  
_L17-47_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `URigVMTemplateNode`
- desc: The Function Interface node is is used as the base class for both the entry and return nodes.
- L24 _public prototype_ `virtual uint32 GetStructureHash() const override;` — Override template node functions
- L27 _public prototype_ `virtual FLinearColor GetNodeColor() const override;` — Override node functions
- L28 _public prototype_ `virtual bool IsDefinedAsVarying() const override;`
- L31 _public prototype_ `virtual FText GetToolTipText() const override;` — URigVMNode interface
- L32 _public prototype_ `virtual FText GetToolTipTextForPin(const URigVMPin* InPin) const override;`
- L35 _public prototype_ `virtual bool IsInterfacePinUsed(const FName& InInterfacePinName) const;` — returns true if the interface pin is used for anything within the function / collapse graph
- L38 _public prototype_ `const URigVMCollapseNode* FindReferencedNode() const;` — find outer node which contains this interface node in its graph
- L41 _public prototype_ `const URigVMPin* FindReferencedPin(const URigVMPin* InPin) const;` — find pin in referenced node that represents this inner pin
- L42 _public prototype_ `const URigVMPin* FindReferencedPin(const FString& InPinPath) const;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API RIGVMDEVELOPER_API`

### `Plugins/Runtime/RigVM/Source/RigVMDeveloper/Public/RigVMModel/Nodes/RigVMFunctionReferenceNode.h` (Public)


#### class `URigVMFunctionReferenceNode`  
`class URigVMFunctionReferenceNode : public URigVMLibraryNode`  
_L19-104_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `URigVMLibraryNode`
- desc: The Function Reference Node is a library node which references a library node from a separate function library graph.
- L26 _public prototype_ `virtual FString GetNodeTitle() const override;` — URigVMNode interface
- L27 _public prototype_ `virtual FLinearColor GetNodeColor() const override;`
- L28 _public prototype_ `virtual FText GetToolTipText() const override;`
- L29 _public prototype_ `virtual FName GetDisplayNameForPin(const URigVMPin* InPin) const override;`
- L30 _public prototype_ `virtual FString GetCategoryForPin(const FString& InPinPath) const override;`
- L31 _public prototype_ `virtual int32 GetIndexInCategoryForPin(const FString& InPinPath) const override;`
- L32 _public prototype_ `virtual FText GetToolTipTextForPin(const URigVMPin* InPin) const override;`
- L33 _public prototype_ `virtual TArray<FString> GetPinCategories() const override;`
- L34 _public prototype_ `virtual FRigVMNodeLayout GetNodeLayout(bool bIncludeEmptyCategories) const override;`
- L38 _public prototype_ `virtual FString GetNodeCategory() const override;` — URigVMLibraryNode interface
- L39 _public prototype_ `virtual FString GetNodeKeywords() const override;`
- L40 _public prototype_ `virtual TArray<FRigVMExternalVariable> GetExternalVariables() const override;`
- L41 _public function_ `virtual const FRigVMTemplate* GetTemplate() const override`
- L42 _public prototype_ `virtual FRigVMGraphFunctionIdentifier GetFunctionIdentifier() const override;`
- L45 _public prototype_ `bool IsReferencedFunctionHostLoaded() const;`
- L46 _public prototype_ `bool IsReferencedNodeLoaded() const;`
- L47 _public prototype_ `URigVMLibraryNode* LoadReferencedNode() const;`
- L50 _public prototype_ `bool ReferencesFunctionInSamePackage() const;` — Variable remapping
- L51 _public prototype_ `bool RequiresVariableRemapping() const;`
- L52 _public prototype_ `bool IsFullyRemapped() const;`
- L53 _public prototype_ `const TMap<FName, FName> GetVariableMap() const;`
- L54 _public prototype_ `FName GetOuterVariableName(const FName& InInnerVariableName) const;`
- L55 _public prototype_ `FString GetOuterVariablePath(const FName& InInnerVariableName) const;`
- L58 _public prototype_ `virtual uint32 GetStructureHash() const override;`
- L61 _public function_ `FRigVMGraphFunctionHeader GetReferencedFunctionHeader_ForBlueprint() const` — `UFUNCTION(BlueprintCallable, Category = RigVMLibraryNode, meta = (DisplayName = "GetReferencedFunctionHeader", ScriptName = "GetReferencedFunctionHeader"))`
- L63 _public function_ `const FRigVMGraphFunctionHeader& GetReferencedFunctionHeader() const`
- L65 _public prototype_ `void UpdateFunctionHeaderFromHost();`
- L67 _public prototype_ `const FRigVMGraphFunctionData* GetReferencedFunctionData(bool bLoadIfNecessary = true) const;`
- L68 _public prototype_ `bool SupportsCallable() const;`
- L70 _public prototype_ `TArray<FRigVMTag> GetVariantTags() const;`
- L72 _public prototype_ `FRigVMReferenceNodeData GetReferenceNodeData() const;`
- L76 _protected prototype_ `virtual FString GetOriginalDefaultValueForRootPin(const URigVMPin* InRootPin) const override;`
- L77 _protected prototype_ `TArray<FRigVMExternalVariable> GetAssetExternalVariables() const;`
- L81 _private prototype_ `virtual TArray<int32> GetInstructionsForVMImpl(const FRigVMExtendedExecuteContext& Context, URigVM* InVM, const FRigVMASTProxy& InProxy = FRigVMASTProxy()) const override;`
- L82 _private prototype_ `const URigVMPin* FindReferencedPin(const URigVMPin* InPin) const;`
- L83 _private prototype_ `const URigVMPin* FindReferencedPin(const FString& InPinPath) const;`
- L88 _private member_ `FRigVMGraphFunctionHeader ReferencedFunctionHeader;` — `UPROPERTY(AssetRegistrySearchable)`
- L91 _private member_ `TSoftObjectPtr<URigVMLibraryNode> ReferencedNodePtr_DEPRECATED;` — `UPROPERTY(AssetRegistrySearchable, meta=(DeprecatedProperty=5.2))`
- L94 _private member_ `TMap<FName, FName> VariableMap_DEPRECATED;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API RIGVMDEVELOPER_API`

### `Plugins/Runtime/RigVM/Source/RigVMDeveloper/Public/RigVMModel/Nodes/RigVMFunctionReturnNode.h` (Public)


#### class `URigVMFunctionReturnNode`  
`class URigVMFunctionReturnNode : public URigVMFunctionInterfaceNode`  
_L15-32_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `URigVMFunctionInterfaceNode`
- desc: The Function Return node is used to provide access to the output pins of the library node for links within.
- L22 _public function_ `virtual UScriptStruct* GetScriptStruct() const override` — Override template node functions
- L23 _public function_ `virtual const FRigVMTemplate* GetTemplate() const override`
- L24 _public function_ `virtual FName GetNotation() const override`
- L27 _public prototype_ `virtual FString GetNodeTitle() const override;` — URigVMNode interface

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API RIGVMDEVELOPER_API`

### `Plugins/Runtime/RigVM/Source/RigVMDeveloper/Public/RigVMModel/Nodes/RigVMIfNode.h` (Public)


#### class `UDEPRECATED_RigVMIfNode`  
`class UDEPRECATED_RigVMIfNode : public URigVMTemplateNode`  
_L23-51_
- reflection: `UCLASS(MinimalAPI, BlueprintType, Deprecated)`
- inherits: `URigVMTemplateNode`
- desc: A if node is used to pick between two values
- L30 _public prototype_ `virtual FName GetNotation() const override;` — Override from URigVMTemplateNode
- L31 _public prototype_ `virtual const FRigVMTemplate* GetTemplate() const override;`
- L32 _public function_ `virtual bool IsSingleton() const override`
- L35 _public function_ `virtual FString GetNodeTitle() const override` — Override from URigVMNode
- L36 _public function_ `virtual FLinearColor GetNodeColor() const override`
- L39 _private member_ `static const inline TCHAR* IfName = TEXT("If"`
- L40 _private member_ `static const inline TCHAR* ConditionName = TEXT("Con`
- L41 _private member_ `static const inline TCHAR* TrueName = TEXT("Tru`
- L42 _private member_ `static const inline TCHAR* FalseName = TEXT("Fal`
- L43 _private member_ `static const inline TCHAR* ResultName = TEXT("Res`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API RIGVMDEVELOPER_API`

### `Plugins/Runtime/RigVM/Source/RigVMDeveloper/Public/RigVMModel/Nodes/RigVMInvokeEntryNode.h` (Public)


#### class `URigVMInvokeEntryNode`  
`class URigVMInvokeEntryNode : public URigVMNode`  
_L15-47_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `URigVMNode`
- desc: The Invoke Entry Node is used to invoke another entry from the the currently running entry.
- L22 _public prototype_ `URigVMInvokeEntryNode();` — Default constructor
- L25 _public prototype_ `virtual FString GetNodeTitle() const;` — Override of node title
- L29 _public prototype_ `FName GetEntryName() const;` — `UFUNCTION(BlueprintCallable, Category = RigVMInvokeEntryNode)` — Returns the name of the entry to run
- L32 _public function_ `virtual FLinearColor GetNodeColor() const override` — Override of node title
- L33 _public function_ `virtual bool IsDefinedAsVarying() const override`
- L37 _private member_ `static const inline TCHAR* EntryName = TEXT("Ent`
- L39 _private prototype_ `URigVMPin* GetEntryNamePin() const;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API RIGVMDEVELOPER_API`

### `Plugins/Runtime/RigVM/Source/RigVMDeveloper/Public/RigVMModel/Nodes/RigVMLibraryNode.h` (Public)


#### class `URigVMLibraryNode`  
`class URigVMLibraryNode : public URigVMTemplateNode`  
_L24-88_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `URigVMTemplateNode`
- desc: The Library Node represents a function invocation of a function specified somewhere else. The function can be expressed as a sub-graph (RigVMGroupNode) or as a referenced function (RigVMFunctionNode).
- L31 _public prototype_ `virtual bool IsDefinedAsConstant() const override;` — Override node functions
- L32 _public prototype_ `virtual bool IsDefinedAsVarying() const override;`
- L36 _public function_ `virtual UScriptStruct* GetScriptStruct() const override` — Override template node functions
- L37 _public function_ `virtual const FRigVMTemplate* GetTemplate() const override`
- L38 _public function_ `virtual FName GetNotation() const override`
- L39 _public prototype_ `virtual uint32 GetStructureHash() const override;`
- L42 _public prototype_ `virtual FText GetToolTipText() const override;` — URigVMNode interface
- L45 _public function_ `virtual FString GetNodeCategory() const` — Library node interface
- L46 _public function_ `virtual FString GetNodeKeywords() const`
- L47 _public function_ `virtual FString GetNodeDescription() const`
- L50 _public function_ `virtual URigVMFunctionLibrary* GetLibrary() const` — `UFUNCTION(BlueprintCallable, Category = RigVMLibraryNode)`
- L53 _public function_ `virtual URigVMGraph* GetContainedGraph() const` — `UFUNCTION(BlueprintCallable, Category = RigVMLibraryNode)`
- L55 _public prototype_ `virtual const TArray<URigVMNode*>& GetContainedNodes() const;`
- L56 _public prototype_ `virtual const TArray<URigVMLink*>& GetContainedLinks() const;`
- L57 _public prototype_ `virtual URigVMFunctionEntryNode* GetEntryNode() const;`
- L58 _public prototype_ `virtual URigVMFunctionReturnNode* GetReturnNode() const;`
- L59 _public prototype_ `virtual bool Contains(URigVMLibraryNode* InContainedNode, bool bRecursive = true) const;`
- L60 _public prototype_ `virtual TArray<FRigVMExternalVariable> GetExternalVariables() const;`
- L61 _public prototype_ `virtual TMap<FRigVMGraphFunctionIdentifier, uint32> GetDependencies() const;`
- L63 _public prototype_ `virtual FRigVMGraphFunctionIdentifier GetFunctionIdentifier() const;`
- L64 _public prototype_ `FRigVMGraphFunctionHeader GetFunctionHeader(IRigVMGraphFunctionHost* InHostObject = nullptr) const;`
- L67 _public prototype_ `FRigVMVariant GetFunctionVariant() const;` — `UFUNCTION(BlueprintPure, Category = RigVMLibraryNode)`
- L70 _public prototype_ `FRigVMVariantRef GetFunctionVariantRef() const;` — `UFUNCTION(BlueprintPure, Category = RigVMLibraryNode)`
- L73 _public prototype_ `TArray<FRigVMVariantRef> GetMatchingVariants() const;` — `UFUNCTION(BlueprintPure, Category = RigVMLibraryNode)`
- L76 _public prototype_ `bool ContainsLocalVariable(const FName& InVariableName) const;` — `UFUNCTION(BlueprintPure, Category = RigVMLibraryNode)`
- L80 _protected prototype_ `virtual TArray<int32> GetInstructionsForVMImpl(const FRigVMExtendedExecuteContext& Context, URigVM* InVM, const FRigVMASTProxy& InProxy = FRigVMASTProxy()) const override;`
- L81 _protected member_ `const static TArray<URigVMNode*> EmptyNodes;`
- L82 _protected member_ `const static TArray<URigVMLink*> EmptyLinks;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API RIGVMDEVELOPER_API`

### `Plugins/Runtime/RigVM/Source/RigVMDeveloper/Public/RigVMModel/Nodes/RigVMParameterNode.h` (Public)


#### struct `FRigVMGraphParameterDescription`  
`struct FRigVMGraphParameterDescription`  
_L29-66_
- reflection: `USTRUCT(BlueprintType, meta = (Deprecated = "5.1"))`
- desc: The parameter description is used to convey information about unique parameters within a Graph. Multiple Parameter Nodes can share the same parameter description.
- L36 _public function_ `bool operator ==(const FRigVMGraphParameterDescription& Other) const` — comparison operator
- L43 _public member_ `FName Name;` — `UPROPERTY(BlueprintReadOnly, Category = RigVMGraphParameterDescription)` — The name of the parameter
- L47 _public member_ `bool bIsInput = false;` — `UPROPERTY(BlueprintReadOnly, Category = RigVMGraphParameterDescription)` — True if the parameter is an input
- L51 _public member_ `FString CPPType;` — `UPROPERTY(BlueprintReadOnly, Category = RigVMGraphParameterDescription)` — The C++ data type of the parameter
- L55 _public member_ `TObjectPtr<UObject> CPPTypeObject = nullptr;` — `UPROPERTY(BlueprintReadOnly, Category = RigVMGraphParameterDescription)` — The Struct of the C++ data type of the parameter (or nullptr)
- L59 _public member_ `FString DefaultValue;` — `UPROPERTY(BlueprintReadOnly, Category = RigVMGraphParameterDescription)` — The default value of the parameter
- L62 _public function_ `FRigVMExternalVariable ToExternalVariable() const` — Returns nullptr external variable matching this description

#### class `URigVMParameterNode`  
`class URigVMParameterNode : public URigVMNode`  
_L73-124_
- reflection: `UCLASS(MinimalAPI, BlueprintType, meta = (Deprecated = "5.1"))`
- inherits: `URigVMNode`
- desc: The Parameter Node represents an input or output argument / parameter of the Function / Graph. Parameter Node have only a single value pin.
- L80 _public prototype_ `URigVMParameterNode();` — Default constructor
- L83 _public prototype_ `virtual FString GetNodeTitle() const;` — Override of node title
- L87 _public prototype_ `FName GetParameterName() const;` — `UFUNCTION(BlueprintCallable, Category = RigVMParameterNode)` — Returns the name of the parameter
- L91 _public prototype_ `bool IsInput() const;` — `UFUNCTION(BlueprintCallable, Category = RigVMParameterNode)` — Returns true if this node is an input
- L95 _public prototype_ `FString GetCPPType() const;` — `UFUNCTION(BlueprintCallable, Category = RigVMParameterNode)` — Returns the C++ data type of the parameter
- L99 _public prototype_ `UObject* GetCPPTypeObject() const;` — `UFUNCTION(BlueprintCallable, Category = RigVMParameterNode)` — Returns the C++ data type struct of the parameter (or nullptr)
- L103 _public prototype_ `FString GetDefaultValue() const;` — `UFUNCTION(BlueprintCallable, Category = RigVMParameterNode)` — Returns the default value of the parameter as a string
- L107 _public prototype_ `FRigVMGraphParameterDescription GetParameterDescription() const;` — `UFUNCTION(BlueprintCallable, Category = RigVMParameterNode)` — Returns this parameter node's parameter description
- L110 _public function_ `virtual FLinearColor GetNodeColor() const override` — Override of node title
- L112 _public function_ `virtual bool IsDefinedAsVarying() const override`
- L116 _private function_ `virtual bool ContributesToResult() const override`
- L118 _private member_ `static const inline TCHAR* ParameterName = TEXT("Par`
- L119 _private member_ `static const inline TCHAR* DefaultName = TEXT("Def`
- L120 _private member_ `static const inline TCHAR* ValueName = TEXT("Val`

#### Free symbols / members of external scopes

- L18 _macro_ `#define UE_API RIGVMDEVELOPER_API`

### `Plugins/Runtime/RigVM/Source/RigVMDeveloper/Public/RigVMModel/Nodes/RigVMRerouteNode.h` (Public)


#### class `URigVMRerouteNode`  
`class URigVMRerouteNode : public URigVMNode`  
_L18-49_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `URigVMNode`
- desc: A reroute node is used to visually improve the data flow within a Graph. Reroutes are purely cosmetic and have no impact on the resulting VM whatsoever. Reroutes can furthermore be displayed as full nodes or as small circles.
- L25 _public prototype_ `URigVMRerouteNode();` — Default constructor
- L28 _public prototype_ `virtual FString GetNodeTitle() const override;` — Override of node title
- L30 _public prototype_ `virtual FLinearColor GetNodeColor() const override;`
- L32 _public prototype_ `virtual FText GetToolTipText() const override;`
- L35 _public prototype_ `bool IsLiteral() const;` — Has no source connections
- L37 _public function_ `virtual bool IsPure() const override`
- L41 _private member_ `static const inline TCHAR* RerouteName = TEXT("Rer`
- L42 _private member_ `static const inline TCHAR* ValueName = TEXT("Val`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API RIGVMDEVELOPER_API`

### `Plugins/Runtime/RigVM/Source/RigVMDeveloper/Public/RigVMModel/Nodes/RigVMSelectNode.h` (Public)


#### class `UDEPRECATED_RigVMSelectNode`  
`class UDEPRECATED_RigVMSelectNode : public URigVMTemplateNode`  
_L24-58_
- reflection: `UCLASS(MinimalAPI, BlueprintType, Deprecated)`
- inherits: `URigVMTemplateNode`
- desc: A select node is used to select between multiple values
- L31 _public prototype_ `virtual FName GetNotation() const override;` — Override from URigVMTemplateNode
- L32 _public prototype_ `virtual const FRigVMTemplate* GetTemplate() const override;`
- L33 _public function_ `virtual bool IsSingleton() const override`
- L36 _public function_ `virtual FString GetNodeTitle() const override` — Override from URigVMNode
- L37 _public function_ `virtual FLinearColor GetNodeColor() const override`
- L41 _protected prototype_ `virtual bool AllowsLinksOn(const URigVMPin* InPin) const override;`
- L45 _private member_ `static const inline TCHAR* SelectName = TEXT("Sel`
- L46 _private member_ `static const inline TCHAR* IndexName = TEXT("Ind`
- L47 _private member_ `static const inline TCHAR* ValueName = TEXT("Val`
- L48 _private member_ `static const inline TCHAR* ResultName = TEXT("Res`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API RIGVMDEVELOPER_API`

### `Plugins/Runtime/RigVM/Source/RigVMDeveloper/Public/RigVMModel/Nodes/RigVMTemplateNode.h` (Public)


#### struct `FRigVMTemplatePreferredType`  
`struct FRigVMTemplatePreferredType`  
_L13-65_
- reflection: `USTRUCT()`
- L19 _public function_ `FRigVMTemplatePreferredType() : Argument(NAME_None) , TypeIndex(INDEX_NONE)`
- L24 _public function_ `FRigVMTemplatePreferredType(const FName& InArgument, TRigVMTypeIndex InTypeIndex) : Argument(InArgument) , TypeIndex(InTypeIndex)`
- L33 _public function_ `const FName& GetArgument() const`
- L34 _public function_ `TRigVMTypeIndex GetTypeIndex() const`
- L44 _public function_ `bool operator==(const FRigVMTemplatePreferredType& Other) const`
- L49 _public prototype_ `void UpdateStringFromIndex();`
- L50 _public prototype_ `void UpdateIndexFromString();`
- L55 _protected member_ `FName Argument;` — `UPROPERTY()`
- L58 _protected member_ `int32 TypeIndex;` — `UPROPERTY()`
- L61 _protected member_ `FString TypeString;` — `UPROPERTY()`

#### class `URigVMTemplateNode`  
`class URigVMTemplateNode : public URigVMNode`  
_L73-183_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `URigVMNode`
- desc: The Template Node represents an unresolved function. Template nodes can morph into all functions implementing the template's template.
- L80 _public prototype_ `URigVMTemplateNode();` — default constructor
- L83 _public prototype_ `virtual void PreSave(FObjectPreSaveContext SaveContext) override;` — UObject interface
- L84 _public prototype_ `virtual void PostLoad() override;`
- L87 _public prototype_ `virtual FString GetNodeTitle() const override;` — URigVMNode interface
- L88 _public prototype_ `virtual FName GetMethodName() const;`
- L89 _public prototype_ `virtual FText GetToolTipText() const override;`
- L90 _public prototype_ `virtual FText GetToolTipTextForPin(const URigVMPin* InPin) const override;`
- L91 _public prototype_ `virtual TArray<URigVMPin*> GetAggregateInputs() const override;`
- L92 _public prototype_ `virtual TArray<URigVMPin*> GetAggregateOutputs() const override;`
- L93 _public prototype_ `TArray<URigVMPin*> GetAggregatePins(const ERigVMPinDirection& InDirection) const;`
- L94 _public prototype_ `virtual FName GetNextAggregateName(const FName& InLastAggregatePinName) const override;`
- L99 _public prototype_ `virtual UScriptStruct* GetScriptStruct() const;` — `UFUNCTION(BlueprintCallable, Category = RigVMUnitNode)` — Returns the UStruct for this unit node (the struct declaring the RIGVM_METHOD)
- L103 _public prototype_ `virtual FName GetNotation() const;` — `UFUNCTION(BlueprintPure, Category = Template)` — Returns the notation of the node
- L106 _public prototype_ `virtual bool IsSingleton() const;` — `UFUNCTION(BlueprintCallable, Category = Template)`
- L109 _public prototype_ `bool SupportsType(const URigVMPin* InPin, TRigVMTypeIndex InTypeIndex, TRigVMTypeIndex* OutTypeIndex = nullptr);` — returns true if a pin supports a given type
- L112 _public prototype_ `TArray<const FRigVMFunction*> GetResolvedPermutations() const;` — returns the resolved functions for the template
- L115 _public prototype_ `TArray<int32> GetResolvedPermutationIndices(bool bAllowFloatingPointCasts) const;` — returns the resolved permutation indices for the template
- L118 _public prototype_ `FRigVMTemplateTypeMap GetTemplatePinTypeMap(bool bIncludeHiddenPins = false, bool bIncludeExecutePins = false) const;` — Returns a map of the resolved pin types
- L121 _public prototype_ `virtual const FRigVMTemplate* GetTemplate() const;` — returns the template used for this node
- L124 _public prototype_ `const FRigVMFunction* GetResolvedFunction() const;` — returns the resolved function or nullptr if there are still unresolved pins left
- L128 _public prototype_ `bool IsResolved() const;` — `UFUNCTION(BlueprintPure, Category = Template)` — returns true if the template node is resolved
- L132 _public prototype_ `bool IsFullyUnresolved() const;` — `UFUNCTION(BlueprintPure, Category = Template)` — returns true if the template is fully unresolved
- L135 _public prototype_ `FString GetInitialDefaultValueForPin(const FName& InRootPinName, const TArray<int32>& InPermutationIndices = TArray<int32>()) const;` — returns a default value for pin if it is known
- L138 _public prototype_ `virtual FName GetDisplayNameForPin(const URigVMPin* InPin) const override;` — returns the display name for a pin
- L139 _public prototype_ `FName GetDisplayNameForPin(const URigVMPin* InPin, const TArray<int32>& InPermutationIndices) const;`
- L143 _public prototype_ `TRigVMTypeIndex TryReduceTypesToSingle(const TArray<TRigVMTypeIndex>& InTypes, const TRigVMTypeIndex PreferredType = TRigVMTypeIndex()) const;` — Tries to reduce the input types to a single type, if all are compatible Will prioritize the InPreferredType if available
- L144 _public prototype_ `TRigVMTypeIndex TryReduceTypesToSingle_NoLock(const TArray<TRigVMTypeIndex>& InTypes, const FRigVMRegistryHandle& InRegistry, const TRigVMTypeIndex PreferredType = TRigVMTypeIndex()) const;`
- L146 _public prototype_ `virtual uint32 GetStructureHash() const override;`
- L150 _protected prototype_ `virtual void InvalidateCache() override;`
- L152 _protected prototype_ `TArray<int32> FindPermutationsForTypes(const TArray<FRigVMTemplatePreferredType>& ArgumentTypes, bool bAllowCasting = false) const;`
- L153 _protected prototype_ `FRigVMTemplateTypeMap GetTypesForPermutation(const int32 InPermutationIndex) const;`
- L156 _protected member_ `FName TemplateNotation;` — `UPROPERTY()`
- L159 _protected member_ `FString ResolvedFunctionName;` — `UPROPERTY()`
- L165 _protected member_ `TArray<FString> PreferredPermutationTypes_DEPRECATED;` — `UPROPERTY()` — Indicates a preferred permutation using the types of the arguments Each element is in the format "ArgumentName:CPPType"
- L169 _protected member_ `TArray<FRigVMTemplatePreferredType> PreferredPermutationPairs_DEPRECATED;` — `UPROPERTY()`
- L171 _protected member_ `mutable const FRigVMTemplate* CachedTemplate;`
- L172 _protected member_ `mutable const FRigVMFunction* CachedFunction;`
- L173 _protected member_ `mutable int32 ResolvedPermutation;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API RIGVMDEVELOPER_API`
- L10 _macro_ `#define UE_RIGVM_MANYTYPES_LIMIT 100`

### `Plugins/Runtime/RigVM/Source/RigVMDeveloper/Public/RigVMModel/Nodes/RigVMUnitNode.h` (Public)


#### class `URigVMUnitNode`  
`class URigVMUnitNode : public URigVMTemplateNode`  
_L21-130_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `URigVMTemplateNode`
- desc: The Struct Node represents a Function Invocation of a RIGVM_METHOD declared on a USTRUCT. Struct Nodes have input / output pins for all struct UPROPERTY members.
- L28 _public prototype_ `virtual void PostLoad() override;` — UObject interface
- L31 _public prototype_ `virtual FString GetNodeTitle() const override;` — Override node functions
- L32 _public prototype_ `virtual FString GetNodeSubTitle() const override;`
- L33 _public prototype_ `virtual FText GetToolTipText() const override;`
- L34 _public prototype_ `virtual bool IsDefinedAsConstant() const override;`
- L35 _public prototype_ `virtual bool IsDefinedAsVarying() const override;`
- L36 _public prototype_ `virtual bool IsPure() const override;`
- L37 _public prototype_ `virtual FName GetEventName() const override;`
- L38 _public prototype_ `virtual bool CanOnlyExistOnce() const override;`
- L39 _public prototype_ `virtual const TArray<FName>& GetControlFlowBlocks() const override;`
- L40 _public prototype_ `virtual const bool IsControlFlowBlockSliced(const FName& InBlockName) const override;`
- L41 _public prototype_ `virtual TArray<FRigVMUserWorkflow> GetSupportedWorkflows(ERigVMUserWorkflowType InType, const UObject* InSubject) const override;`
- L42 _public prototype_ `virtual TArray<URigVMPin*> GetAggregateInputs() const override;`
- L43 _public prototype_ `virtual TArray<URigVMPin*> GetAggregateOutputs() const override;`
- L44 _public prototype_ `virtual FName GetNextAggregateName(const FName& InLastAggregatePinName) const override;`
- L45 _public prototype_ `virtual FName GetDisplayNameForPin(const URigVMPin* InPin) const override;`
- L47 _public prototype_ `virtual bool IsOutDated() const override;`
- L48 _public prototype_ `virtual FString GetDeprecatedMetadata() const override;`
- L51 _public prototype_ `virtual UScriptStruct* GetScriptStruct() const override;` — URigVMTemplateNode interface
- L55 _public prototype_ `virtual FName GetMethodName() const;` — `UFUNCTION(BlueprintCallable, Category = RigVMUnitNode)` — Returns the name of the declared RIGVM_METHOD
- L59 _public prototype_ `FString GetStructDefaultValue() const;` — `UFUNCTION(BlueprintCallable, Category = RigVMUnitNode)` — Returns the default value for the struct as text
- L63 _public prototype_ `TSharedPtr<FStructOnScope> ConstructStructInstance(bool bUseDefault = false) const;` — Returns an instance of the struct with the current values. @param bUseDefault If set to true the default struct will be created - otherwise the struct will contains the values from the node
- L66 _public prototype_ `TSharedPtr<FStructOnScope> ConstructLiveStructInstance(URigVMHost* InHost, int32 InSliceIndex = 0) const;` — Returns an instance of the struct with values backed by the memory of a currently running host
- L69 _public prototype_ `bool UpdateHostFromStructInstance(URigVMHost* InHost, TSharedPtr<FStructOnScope> InInstance, int32 InSliceIndex = 0) const;` — Updates the memory of a host to match a specific struct instance
- L72 _public prototype_ `void ComputePinValueDifferences(TSharedPtr<FStructOnScope> InCurrentInstance, TSharedPtr<FStructOnScope> InDesiredInstance, TMap<FString, FString>& OutNewPinDefaultValues) const;` — Compares two struct instances and returns differences in pin values
- L75 _public prototype_ `void ComputePinValueDifferences(TSharedPtr<FStructOnScope> InDesiredInstance, TMap<FString, FString>& OutNewPinDefaultValues) const;` — Compares a desired struct instance with the node's default and returns differences in pin values
- L78 _public prototype_ `bool IsPartOfRuntime() const;` — Returns true if the node is part of the debugged runtime rig
- L81 _public prototype_ `bool IsPartOfRuntime(URigVMHost* InHost) const;` — Returns true if the node is part of the debugged runtime rig
- L88 _public function_ `T ConstructStructInstance() const`
- L100 _public prototype_ `virtual FRigVMStructUpgradeInfo GetUpgradeInfo() const override;`
- L102 _public prototype_ `virtual uint32 GetStructureHash() const override;`
- L106 _protected prototype_ `virtual FText GetToolTipTextForPin(const URigVMPin* InPin) const override;`
- L107 _protected prototype_ `virtual bool ShouldInputPinComputeLazily(const URigVMPin* InPin) const override;`
- L108 _protected prototype_ `virtual bool IsPinConstant(const URigVMPin* InPin) const override;`
- L109 _protected prototype_ `virtual FString GetOriginalDefaultValueForRootPin(const URigVMPin* InRootPin) const override;`
- L110 _protected prototype_ `void EnumeratePropertiesOnHostAndStructInstance( URigVMHost* InHost, TSharedPtr<FStructOnScope> InInstance, bool bPreferLiterals, TFunction<void(const URigVMPin*,const FProperty*,uint8*,const FProperty*,uint8*)> InEnumerationFunction, int32 InSliceIndex = 0) const;`
- L121 _private member_ `TObjectPtr<UScriptStruct> ScriptStruct_DEPRECATED;` — `UPROPERTY()`
- L124 _private member_ `FName MethodName_DEPRECATED;` — `UPROPERTY()`
- L127 _private member_ `mutable TRigVMModelCachedValue<URigVMUnitNode, FName> CachedEventName;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API RIGVMDEVELOPER_API`

### `Plugins/Runtime/RigVM/Source/RigVMDeveloper/Public/RigVMModel/Nodes/RigVMVariableNode.h` (Public)


#### class `URigVMVariableNode`  
`class URigVMVariableNode : public URigVMNode`  
_L19-107_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `URigVMNode`
- desc: The Variable Node represents a mutable value / local state within the the Function / Graph. Variable Node's can be a getter or a setter. Getters are pure nodes with just an output value pin, while setters are mutable nodes with an execute and input value pin.
- L26 _public prototype_ `URigVMVariableNode();` — Default constructor
- L29 _public prototype_ `virtual FString GetNodeTitle() const;` — Override of node title
- L33 _public prototype_ `FName GetVariableName() const;` — `UFUNCTION(BlueprintCallable, Category = RigVMVariableNode)` — Returns the name of the variable
- L37 _public prototype_ `bool IsGetter() const;` — `UFUNCTION(BlueprintCallable, Category = RigVMVariableNode)` — Returns true if this node is a variable getter
- L41 _public prototype_ `bool IsExternalVariable() const;` — `UFUNCTION(BlueprintCallable, Category = RigVMVariableNode)` — Returns true if this variable is an external variable
- L45 _public prototype_ `bool IsLocalVariable() const;` — `UFUNCTION(BlueprintCallable, Category = RigVMVariableNode)` — Returns true if this variable is a local variable
- L49 _public prototype_ `bool IsInputArgument() const;` — `UFUNCTION(BlueprintCallable, Category = RigVMVariableNode)` — Returns true if this variable is an input argument
- L53 _public prototype_ `bool IsInputVariable() const;` — `UFUNCTION(BlueprintCallable, Category = RigVMVariableNode)` — Returns true if this variable is related to an input variable
- L57 _public prototype_ `FString GetCPPType() const;` — `UFUNCTION(BlueprintCallable, Category = RigVMVariableNode)` — Returns the C++ data type of the variable
- L61 _public prototype_ `UObject* GetCPPTypeObject() const;` — `UFUNCTION(BlueprintCallable, Category = RigVMVariableNode)` — Returns the C++ data type struct of the variable (or nullptr)
- L65 _public prototype_ `FString GetDefaultValue() const;` — `UFUNCTION(BlueprintCallable, Category = RigVMVariableNode)` — Returns the default value of the variable as a string
- L69 _public prototype_ `FRigVMGraphVariableDescription GetVariableDescription() const;` — `UFUNCTION(BlueprintCallable, Category = RigVMVariableNode)` — Returns this variable node's variable description
- L72 _public function_ `virtual FLinearColor GetNodeColor() const override` — Override of node title
- L74 _public function_ `virtual bool IsDefinedAsVarying() const override`
- L75 _public prototype_ `virtual bool IsPure() const override;`
- L78 _public prototype_ `URigVMPin* GetVariableNamePin() const;` — Get the variable name pin
- L81 _public prototype_ `URigVMPin* GetValuePin() const;` — Get the value pin
- L84 _public prototype_ `virtual FString GetNodeSubTitle() const override;` — Get the subtitle of the node
- L87 _public function_ `FGuid GetVariableGuid() const` — Get variable Guid
- L92 _private member_ `FGuid VariableGuid;` — `UPROPERTY()`
- L94 _private member_ `static const inline TCHAR* VariableName = TEXT("Var`
- L95 _private member_ `static const inline TCHAR* ValueName = TEXT("Val`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API RIGVMDEVELOPER_API`

### `Plugins/Runtime/RigVM/Source/RigVMDeveloper/Public/RigVMModel/RigVMBuildData.h` (Public)


#### struct `FRigVMFunctionReferenceArray`  
`struct FRigVMFunctionReferenceArray`  
_L11-29_
- reflection: `USTRUCT(BlueprintType)`
- L16 _public function_ `void Reset()` — Resets the data structure and maintains all storage.
- L19 _public function_ `bool IsValidIndex(int32 InIndex) const` — Returns true if a given function reference index is valid.
- L22 _public function_ `int32 Num() const` — Returns the number of reference functions
- L25 _public function_ `const TSoftObjectPtr<URigVMFunctionReferenceNode>& operator[](int32 InIndex) const` — const accessor for an function reference given its index
- L28 _public member_ `TArray< TSoftObjectPtr<URigVMFunctionReferenceNode> > FunctionReferences;` — `UPROPERTY(VisibleAnywhere, Category = "BuildData")`

#### class `URigVMBuildData`  
`class URigVMBuildData : public UObject`  
_L37-201_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UObject`
- desc: The Build Data is used to store transient / intermediate build information for the RigVM graph to improve the user experience. This object is never serialized.
- L45 _public prototype_ `static URigVMBuildData* Get();` — `UFUNCTION(BlueprintPure, Category=RigVMBuildData)` — Returns the singleton build data
- L48 _public prototype_ `void InitializeIfNeeded();` — Looks for all function references and public functions (in RigVMClientHost metadata) and initializes the URigVMBuildData
- L50 _public prototype_ `static void RegisterReferencesFromAsset(const FAssetData& AssetData);`
- L51 _public prototype_ `static void RegisterPublicFunctionsFromAsset(const FAssetData& AssetData);`
- L54 _public prototype_ `const FRigVMFunctionReferenceArray* FindFunctionReferences(const FRigVMGraphFunctionIdentifier& InFunction) const;` — Returns the list of references for a given function definition
- L62 _public prototype_ `void ForEachFunctionReference(const FRigVMGraphFunctionIdentifier& InFunction, TFunction<void(URigVMFunctionReferenceNode*)> PerReferenceFunction, bool bLoadIfNecessary = true) const;` — Iterator function to invoke a lambda / TFunction for each reference of a function @param InFunction The function to iterate all references for @param PerReferenceFunction The function to invoke for each reference @param bLoadIfNecessary If true, will load packages if necessary
- L69 _public prototype_ `void ForEachFunctionReferenceSoftPtr(const FRigVMGraphFunctionIdentifier& InFunction, TFunction<void(TSoftObjectPtr<URigVMFunctionReferenceNode>)> PerReferenceFunction) const;` — Iterator function to invoke a lambda / TFunction for each reference of a function @param InFunction The function to iterate all references for @param PerReferenceFunction The function to invoke for each reference
- L73 _public prototype_ `void RegisterFunctionReference(const FRigVMGraphFunctionIdentifier& InFunction, URigVMFunctionReferenceNode* InReference);` — registers a new reference node for a given function
- L76 _public prototype_ `void RegisterFunctionReference(const FRigVMGraphFunctionIdentifier& InFunction, TSoftObjectPtr<URigVMFunctionReferenceNode> InReference);` — registers a new reference node for a given function
- L79 _public prototype_ `void RegisterFunctionReference(FRigVMReferenceNodeData InReferenceNodeData);` — registers a new reference node for a given function
- L82 _public prototype_ `void UnregisterFunctionReference(const FRigVMGraphFunctionIdentifier& InFunction, URigVMFunctionReferenceNode* InReference);` — unregisters a new reference node for a given function
- L85 _public prototype_ `void UnregisterFunctionReference(const FRigVMGraphFunctionIdentifier& InFunction, TSoftObjectPtr<URigVMFunctionReferenceNode> InReference);` — unregisters a new reference node for a given function
- L88 _public prototype_ `void ClearInvalidReferences();` — Clear references to temp assets
- L91 _public prototype_ `void RegisterPublicFunction(const FRigVMGraphFunctionIdentifier& InFunction, const FRigVMGraphFunctionHeader& InHeader);` — Register a new public function with its header
- L94 _public prototype_ `void UnregisterPublicFunction(const FRigVMGraphFunctionIdentifier& InFunction);` — Unregisters a public function
- L97 _public prototype_ `void UpdatePublicFunctionHeader(const FRigVMGraphFunctionIdentifier& InFunction, const FRigVMGraphFunctionHeader& InHeader);` — Updates the header of a public function
- L100 _public prototype_ `const FRigVMGraphFunctionHeader& FindFunctionHeader(const FRigVMGraphFunctionIdentifier& InFunction);` — Get header from function identifier
- L103 _public function_ `void SetIsRunningUnitTest(bool bIsRunning)` — Helper function to disable clearing transient package references
- L107 _public prototype_ `TArray<FRigVMVariantRef> GatherAllFunctionVariantRefs() const;` — `UFUNCTION(BlueprintPure, Category=RigVMBuildData)` — Will find all public function variant refs, and private function variant refs from loaded assets
- L111 _public prototype_ `TArray<FRigVMVariantRef> GatherFunctionVariantRefsForAsset(const FAssetData& InAssetData) const;` — `UFUNCTION(BlueprintPure, Category=RigVMBuildData)` — Will find the public function variant refs inside this asset, and private function variant refs if the asset is loaded
- L115 _public prototype_ `TArray<FRigVMVariantRef> FindFunctionVariantRefs(const FGuid& InGuid) const;` — `UFUNCTION(BlueprintPure, Category=RigVMBuildData)` — Will find all the function variants matching the given variant guid
- L119 _public prototype_ `FRigVMGraphFunctionIdentifier GetFunctionIdentifierForVariant(const FRigVMVariantRef& InVariantRef) const;` — `UFUNCTION(BlueprintPure, Category=RigVMBuildData)` — Returns the function identifier given a variant reference
- L123 _public prototype_ `FRigVMVariantRef CreateFunctionVariant(const FRigVMGraphFunctionIdentifier& InFunctionIdentifier, FName InName = NAME_None);` — `UFUNCTION(BlueprintCallable, Category=RigVMBuildData)` — Creates a new variant of a graph function within the same asset
- L127 _public prototype_ `TArray<FRigVMVariantRef> GatherAllAssetVariantRefs() const;` — `UFUNCTION(BlueprintPure, Category=RigVMBuildData)` — Will find all asset variant refs
- L131 _public prototype_ `TArray<FRigVMVariantRef> FindAssetVariantRefs(const FGuid& InGuid) const;` — `UFUNCTION(BlueprintPure, Category=RigVMBuildData)` — Will find all the asset variants matching the given variant guid
- L135 _public prototype_ `FRigVMVariantRef CreateAssetVariant(const FAssetData& InAssetData, FName InName = NAME_None);` — `UFUNCTION(BlueprintCallable, Category=RigVMBuildData)` — Creates a new variant of an asset
- L139 _public prototype_ `FAssetData GetAssetDataForPath(const FSoftObjectPath& InObjectPath) const;` — `UFUNCTION(BlueprintPure, Category=RigVMBuildData)` — Returns the asset data given an object path
- L143 _public prototype_ `FRigVMVariantRef GetVariantRefForAsset(const FAssetData& InAssetData) const;` — `UFUNCTION(BlueprintPure, Category=RigVMBuildData)` — Returns the asset data given a variant reference
- L147 _public prototype_ `FAssetData GetAssetDataForVariant(const FRigVMVariantRef& InVariantRef) const;` — `UFUNCTION(BlueprintPure, Category=RigVMBuildData)` — Returns the asset data given a variant reference
- L151 _public prototype_ `FRigVMVariantRef SplitVariantFromSet(const FRigVMVariantRef& InVariantRef);` — `UFUNCTION(BlueprintPure, Category=RigVMBuildData)` — Splits a variant from its variant set (by assigning a new, unique guid
- L155 _public prototype_ `FRigVMVariantRef JoinVariantSet(const FRigVMVariantRef& InVariantRef, const FGuid& InGuid);` — `UFUNCTION(BlueprintPure, Category=RigVMBuildData)` — Joins a variant with another variant's set
- L160 _public prototype_ `TArray<FRigVMGraphFunctionIdentifier> GetAllFunctionIdentifiers(bool bOnlyPublic = true) const;` — `UFUNCTION(BlueprintPure, Category=RigVMBuildData)` — Returns all known public function identifiers used in the project
- L165 _public prototype_ `TArray<FRigVMGraphFunctionIdentifier> GetUsedFunctionIdentifiers(bool bOnlyPublic = true) const;` — `UFUNCTION(BlueprintPure, Category=RigVMBuildData)` — Returns all known public function identifiers used in the project
- L168 _public prototype_ `FRigVMFunctionReferenceArray GetAllFunctionReferences() const;` — Returns all known function references
- L171 _public prototype_ `void Reset();` — Remove all data, and mark that initialization is needed
- L176 _private prototype_ `URigVMBuildData();` — disable default constructor
- L178 _private prototype_ `static TArray<UClass*> FindAllRigVMAssetClasses();`
- L180 _private prototype_ `void SetupRigVMGraphFunctionPointers();`
- L181 _private prototype_ `static void TearDownRigVMGraphFunctionPointers();`
- L182 _private prototype_ `static TArray<FRigVMGraphFunctionHeader> GetFunctionHeadersForAsset(const FAssetData& InAssetData);`
- L184 _private member_ `static bool bInitialized;`
- L187 _private member_ `TMap< TSoftObjectPtr<URigVMLibraryNode>, FRigVMFunctionReferenceArray > FunctionReferences_DEPRECATED;` — `UPROPERTY(meta=(DeprecatedProperty))`
- L190 _private member_ `TMap< FRigVMGraphFunctionIdentifier, FRigVMFunctionReferenceArray > GraphFunctionReferences;` — `UPROPERTY(VisibleAnywhere, Category = "BuildData")`
- L193 _private member_ `TMap<FRigVMGraphFunctionIdentifier, FRigVMGraphFunctionHeader> PublicGraphFunctions;` — `UPROPERTY(VisibleAnywhere, Category = "BuildData")`
- L195 _private member_ `bool bIsRunningUnitTest;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API RIGVMDEVELOPER_API`

### `Plugins/Runtime/RigVM/Source/RigVMDeveloper/Public/RigVMModel/RigVMClient.h` (Public)


#### class `URigVMClientHost`  
`class URigVMClientHost : public UInterface`  
_L18-21_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UInterface`

#### enum `ERigVMLoadType`  
`enum class ERigVMLoadType : uint8`  
_L23-27_
- L25 _public enumerator_ `PostLoad`
- L26 _public enumerator_ `CheckUserDefinedStructs`

#### class `IRigVMClientHost`  
`class IRigVMClientHost`  
_L32-162_
- desc: Interface that allows an object to host a rig VM client. Used by graph edting code to interact with the controller.
- L39 _public prototype_ `virtual FString GetAssetName() const = 0;` — Returns the expected schema class to use for this blueprint
- L42 _public prototype_ `virtual UClass* GetRigVMSchemaClass() const = 0;` — Returns the expected schema class to use for this blueprint
- L45 _public prototype_ `virtual UScriptStruct* GetRigVMExecuteContextStruct() const = 0;` — Returns the expected execute context struct to use for this blueprint
- L48 _public prototype_ `virtual UClass* GetRigVMEdGraphClass() const = 0;` — Returns the expected ed graph class to use for this blueprint
- L51 _public prototype_ `virtual UClass* GetRigVMEdGraphNodeClass() const = 0;` — Returns the expected ed graph node class to use for this blueprint
- L54 _public prototype_ `virtual UClass* GetRigVMEdGraphSchemaClass() const = 0;` — Returns the expected ed graph schema class to use for this blueprint
- L57 _public prototype_ `virtual UClass* GetRigVMEditorSettingsClass() const = 0;` — Returns the class of the settings to use
- L60 _public prototype_ `virtual FRigVMClient* GetRigVMClient() = 0;` — Returns the rigvm client for this host
- L63 _public prototype_ `virtual const FRigVMClient* GetRigVMClient() const = 0;` — Returns the rigvm client for this host
- L66 _public prototype_ `virtual TScriptInterface<IRigVMGraphFunctionHost> GetRigVMGraphFunctionHost() = 0;` — Returns the rigvm function host
- L69 _public prototype_ `virtual TScriptInterface<const IRigVMGraphFunctionHost> GetRigVMGraphFunctionHost() const = 0;` — Returns the rigvm function host
- L72 _public prototype_ `virtual UObject* GetEditorObjectForRigVMGraph(const URigVMGraph* InVMGraph) const = 0;` — Returns the editor object corresponding with the supplied RigVM graph
- L75 _public prototype_ `virtual URigVMGraph* GetRigVMGraphForEditorObject(UObject* InObject) const = 0;` — Returns the RigVM graph corresponding with the supplied editor object
- L78 _public prototype_ `virtual void HandleRigVMGraphAdded(const FRigVMClient* InClient, const FString& InNodePathOrName) = 0;` — Reacts to adding a graph
- L81 _public prototype_ `virtual void HandleRigVMGraphRemoved(const FRigVMClient* InClient, const FString& InNodePathOrName) = 0;` — Reacts to removing a graph
- L84 _public prototype_ `virtual void HandleRigVMGraphRenamed(const FRigVMClient* InClient, const FString& InOldNodePath, const FString& InNewNodePath) = 0;` — Reacts to renaming a graph
- L87 _public prototype_ `virtual void HandleConfigureRigVMController(const FRigVMClient* InClient, URigVMController* InControllerToConfigure) = 0;` — Reacts to a request to configure a controller
- L91 _public prototype_ `virtual UObject* ResolveUserDefinedTypeById(const FString& InTypeName) const;` — Given a type name for a user-defined type, either struct or an enum, returns a pointer to the object definition or nullptr if the client host has no knowledge of such a type.
- L94 _public prototype_ `virtual void RecompileVM() = 0;` — Recompiles the VM if not already being compiled
- L97 _public prototype_ `virtual void RecompileVMIfRequired() = 0;` — Recompiles VM if flagged for recompiling is set
- L100 _public prototype_ `virtual void RequestAutoVMRecompilation() = 0;` — Flags VM requires recompile, and if auto recompile is enabled and no compile bracket is active, requests a recompilation
- L103 _public prototype_ `virtual void SetAutoVMRecompile(bool bAutoRecompile) = 0;` — Sets flag for automatic recompile on model changes
- L106 _public prototype_ `virtual bool GetAutoVMRecompile() const = 0;` — Returns current state of automatic recompile flag
- L109 _public prototype_ `virtual void IncrementVMRecompileBracket() = 0;` — Helper to increase recompile bracket on nested requests
- L112 _public prototype_ `virtual void DecrementVMRecompileBracket() = 0;` — Helper to decrease recompile bracket on nested requests. When value == 1, if autorecompile is enabled, it triggers a VM recompilation
- L115 _public prototype_ `virtual void RefreshAllModels(ERigVMLoadType InLoadType) = 0;` — Regenerates model pins if data has changed while the RigVM Graph is not opened (i.e. user defined struct is changed)
- L117 _public prototype_ `virtual void OnRigVMRegistryChanged() = 0;`
- L119 _public prototype_ `virtual void RequestRigVMInit() = 0;`
- L121 _public prototype_ `virtual URigVMGraph* GetModel(const UEdGraph* InEdGraph = nullptr) const = 0;`
- L122 _public prototype_ `virtual URigVMGraph* GetModel(const FString& InNodePath) const = 0;`
- L124 _public prototype_ `virtual URigVMGraph* GetDefaultModel() const = 0;`
- L126 _public prototype_ `virtual TArray<URigVMGraph*> GetAllModels() const = 0;`
- L128 _public prototype_ `virtual URigVMFunctionLibrary* GetLocalFunctionLibrary() const = 0;`
- L130 _public prototype_ `virtual URigVMFunctionLibrary* GetOrCreateLocalFunctionLibrary(bool bSetupUndoRedo = true) = 0;`
- L132 _public prototype_ `virtual URigVMGraph* AddModel(FString InName = TEXT("Rig Graph"), bool bSetupUndoRedo = true, bool bPrintPythonCommand = t`
- L134 _public prototype_ `virtual bool RemoveModel(FString InName = TEXT("Rig Graph"), bool bSetupUndoRedo = true, bool bPrintPythonCommand = t`
- L136 _public prototype_ `virtual FRigVMGetFocusedGraph& OnGetFocusedGraph() = 0;`
- L137 _public prototype_ `virtual const FRigVMGetFocusedGraph& OnGetFocusedGraph() const = 0;`
- L139 _public prototype_ `virtual URigVMGraph* GetFocusedModel() const = 0;`
- L141 _public prototype_ `virtual URigVMController* GetController(const URigVMGraph* InGraph = nullptr) const = 0;`
- L143 _public prototype_ `virtual URigVMController* GetControllerByName(const FString InGraphName = TEXT("")) const = 0;`
- L145 _public prototype_ `virtual URigVMController* GetOrCreateController(URigVMGraph* InGraph = nullptr) = 0;`
- L147 _public prototype_ `virtual URigVMController* GetController(const UEdGraph* InEdGraph) const = 0;`
- L148 _public prototype_ `virtual URigVMController* GetOrCreateController(const UEdGraph* InGraph) = 0;`
- L151 _public prototype_ `virtual TArray<FString> GeneratePythonCommands(const FString InNewBlueprintName) = 0;` — `UE_DEPRECATED(5.8, "Use TArray<FString> GeneratePythonCommands() instead.")`
- L152 _public prototype_ `virtual TArray<FString> GeneratePythonCommands() = 0;`
- L154 _public prototype_ `virtual void SetupPinRedirectorsForBackwardsCompatibility() = 0;`
- L156 _public prototype_ `virtual FRigVMGraphModifiedEvent& OnModified() = 0;`
- L158 _public prototype_ `virtual bool IsFunctionPublic(const FName& InFunctionName) const = 0;`
- L159 _public prototype_ `virtual void MarkFunctionPublic(const FName& InFunctionName, bool bIsPublic = true) = 0;`
- L161 _public prototype_ `virtual void RenameGraph(const FString& InNodePath, const FName& InNewName) = 0;`

#### class `URigVMEditorSideObject`  
`class URigVMEditorSideObject : public UInterface`  
_L165-168_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UInterface`

#### class `IRigVMEditorSideObject`  
`class IRigVMEditorSideObject`  
_L171-185_
- desc: Interface that allows a UI graph to identify itself against a model graph
- L178 _public prototype_ `virtual FRigVMClient* GetRigVMClient() const = 0;` — Returns the corresponding VM graph
- L181 _public prototype_ `virtual FString GetRigVMNodePath() const = 0;` — Returns the nodepath for this UI graph
- L184 _public prototype_ `virtual void HandleRigVMGraphRenamed(const FString& InOldNodePath, const FString& InNewNodePath) = 0;` — Reacts to renaming the model

#### class `URigVMClientExternalModelHost`  
`class URigVMClientExternalModelHost : public UInterface`  
_L188-191_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UInterface`

#### class `IRigVMClientExternalModelHost`  
`class IRigVMClientExternalModelHost`  
_L194-205_
- desc: Interface that allows access to externally-hosted models
- L201 _public prototype_ `virtual const TArray<TObjectPtr<URigVMGraph>>& GetExternalModels() const = 0;` — Returns the externally-held models for a client
- L204 _public prototype_ `virtual TObjectPtr<URigVMGraph> CreateContainedGraphModel(URigVMCollapseNode* CollapseNode, const FName& Name) = 0;` — Sets a new created model as

#### struct `FRigVMClient`  
`struct FRigVMClient`  
_L213-429_
- reflection: `USTRUCT()`
- desc: A management struct containing graphs and controllers.
- L219 _public function_ `FRigVMClient() : DefaultSchemaClass(nullptr) , ControllerClass(URigVMController::StaticClass()) , FunctionLibrary(nullptr) , ActionStack(nullptr) , bSuspendNotifications(false) , bIgnoreModelNotifications(false) , bDefaultModelCanBeRemoved(false) , bSuspendModelNotificationsForOthers(false) , OuterClientHost(nullptr) , OuterClientPropertyName(NAME_None) , ExternalModelHost(nullptr)`
- L234 _public prototype_ `void SetDefaultSchemaClass(TSubclassOf<URigVMSchema> InSchemaClass);`
- L235 _public prototype_ `void SetControllerClass(TSubclassOf<URigVMController> InControllerClass);`
- L236 _public prototype_ `void SetOuterClientHost(UObject* InOuterClientHost, const FName& InOuterClientHostPropertyName);`
- L237 _public prototype_ `void SetFromDeprecatedData(URigVMGraph* InDefaultGraph, URigVMFunctionLibrary* InFunctionLibrary);`
- L238 _public prototype_ `void SetExternalModelHost(IRigVMClientExternalModelHost* InExternalModelHost);`
- L240 _public prototype_ `FRigVMClient& operator =(const FRigVMClient& InOther);`
- L242 _public prototype_ `void Reset();`
- L243 _public function_ `int32 Num() const`
- L244 _public prototype_ `URigVMSchema* GetDefaultSchema() const;`
- L245 _public function_ `TSubclassOf<URigVMSchema> GetDefaultSchemaClass() const`
- L246 _public prototype_ `URigVMGraph* GetDefaultModel() const;`
- L247 _public prototype_ `URigVMGraph* GetModel(int32 InIndex) const;`
- L248 _public prototype_ `URigVMGraph* GetModel(const UEdGraph* InEdGraph = nullptr) const;`
- L249 _public prototype_ `URigVMGraph* GetModel(const FString& InNodePathOrName) const;`
- L250 _public prototype_ `URigVMGraph* GetModel(const UObject* InEditorSideObject) const;`
- L251 _public prototype_ `void RefreshAllModels(ERigVMLoadType InLoadType, bool bEnablePostLoadHashing, bool& bIsCompiling);`
- L252 _public prototype_ `void RefreshVariableNodes(const TArray<FRigVMExternalVariable> InPublicVariables);`
- L253 _public prototype_ `const TArray<TObjectPtr<URigVMGraph>>& GetModels() const;`
- L254 _public prototype_ `TArray<URigVMGraph*> GetAllModels(bool bIncludeFunctionLibrary, bool bRecursive) const;`
- L255 _public prototype_ `TArray<URigVMGraph*> GetAllModelsLeavesFirst(bool bIncludeFunctionLibrary) const;`
- L256 _public prototype_ `URigVMController* GetController(int32 InIndex) const;`
- L257 _public prototype_ `URigVMController* GetController(const FString& InNodePathOrName) const;`
- L258 _public prototype_ `URigVMController* GetController(const URigVMGraph* InModel) const;`
- L259 _public prototype_ `URigVMController* GetController(const UObject* InEditorSideObject) const;`
- L260 _public prototype_ `URigVMController* GetOrCreateController(int32 InIndex);`
- L261 _public prototype_ `URigVMController* GetOrCreateController(const FString& InNodePathOrName);`
- L262 _public prototype_ `URigVMController* GetOrCreateController(const URigVMGraph* InModel);`
- L263 _public prototype_ `URigVMController* GetOrCreateController(const UObject* InEditorSideObject);`
- L264 _public prototype_ `URigVMController* GetControllerByName(const FString InGraphName) const;`
- L265 _public prototype_ `bool RemoveController(const URigVMGraph* InModel);`
- L266 _public function_ `URigVMFunctionLibrary* GetFunctionLibrary() const`
- L267 _public prototype_ `void SetGetFunctionHostObjectPathDelegate(URigVMFunctionLibrary* FunctionLibrary);`
- L268 _public prototype_ `URigVMFunctionLibrary* GetOrCreateFunctionLibrary(bool bSetupUndoRedo, const FObjectInitializer* ObjectInitializer = nullptr, bool bCreateController = true);`
- L269 _public prototype_ `URigVMFunctionLibrary* GetOrCreateFunctionLibrary(TSubclassOf<URigVMSchema> InSchemaClass, bool bSetupUndoRedo, const FObjectInitializer* ObjectInitializer = nullptr, bool bCreateController = true);`
- L270 _public prototype_ `TArray<FName> GetEntryNames(UScriptStruct* InUnitScriptStructFilter = nullptr) const;`
- L271 _public prototype_ `UScriptStruct* GetDefaultExecuteContextStruct() const;`
- L272 _public prototype_ `void SetDefaultExecuteContextStruct(UScriptStruct* InExecuteContextStruct);`
- L274 _public function_ `FRigVMGetFocusedGraph& OnGetFocusedGraph()`
- L275 _public function_ `const FRigVMGetFocusedGraph& OnGetFocusedGraph() const`
- L276 _public prototype_ `URigVMGraph* GetFocusedModel() const;`
- L277 _public prototype_ `URigVMGraph* AddModel(const FString InName, bool bSetupUndoRedo, bool bPrintPythonCommand);`
- L278 _public prototype_ `URigVMGraph* AddModel(const FName& InName, bool bSetupUndoRedo, const FObjectInitializer* ObjectInitializer = nullptr, bool bCreateController = true);`
- L279 _public prototype_ `URigVMGraph* AddModel(const FName& InName, TSubclassOf<URigVMSchema> InSchemaClass, bool bSetupUndoRedo, const FObjectInitializer* ObjectInitializer = nullptr, bool bCreateController = true);`
- L281 _public prototype_ `URigVMGraph* CreateModel(const FName& InName, TSubclassOf<URigVMSchema> InSchemaClass, bool bSetupUndoRedo, UObject* InOuter, const FObjectInitializer* ObjectInitializer = nullptr, bool bCreateController = true);`
- L282 _public prototype_ `TObjectPtr<URigVMGraph> CreateContainedGraphModel(URigVMCollapseNode* CollapseNode, const FName& Name);`
- L284 _public prototype_ `void AddModel(URigVMGraph* InModel, bool bCreateController);`
- L285 _public prototype_ `bool RemoveModel(FString InName, bool bSetupUndoRedo, bool bPrintPythonCommand);`
- L286 _public prototype_ `bool RemoveModel(const FString& InNodePathOrName, bool bSetupUndoRedo);`
- L287 _public prototype_ `FName RenameModel(const FString& InNodePathOrName, const FName& InNewName, bool bSetupUndoRedo);`
- L288 _public prototype_ `void PostTransacted(const FTransactionObjectEvent& TransactionEvent);`
- L289 _public prototype_ `void OnCollapseNodeRenamed(const URigVMCollapseNode* InCollapseNode);`
- L290 _public prototype_ `void OnCollapseNodeRemoved(const URigVMCollapseNode* InCollapseNode);`
- L292 _public prototype_ `URigVMNode* FindNode(const FString& InNodePathOrName) const;`
- L293 _public prototype_ `URigVMPin* FindPin(const FString& InPinPath) const;`
- L295 _public function_ `TArray<TObjectPtr<URigVMGraph>>::RangedForIteratorType begin()`
- L296 _public function_ `TArray<TObjectPtr<URigVMGraph>>::RangedForConstIteratorType begin() const`
- L297 _public function_ `TArray<TObjectPtr<URigVMGraph>>::RangedForIteratorType end()`
- L298 _public function_ `TArray<TObjectPtr<URigVMGraph>>::RangedForConstIteratorType end() const`
- L300 _public prototype_ `UObject* GetOuter() const;`
- L301 _public prototype_ `FProperty* GetOuterClientProperty() const;`
- L302 _public prototype_ `void NotifyOuterOfPropertyChange(EPropertyChangeType::Type ChangeType = EPropertyChangeType::Interactive) const;`
- L303 _public prototype_ `FName GetUniqueName(const FName& InDesiredName) const;`
- L304 _public prototype_ `static FName GetUniqueName(UObject* InOuter, const FName& InDesiredName);`
- L305 _public prototype_ `static void DestroyObject(UObject* InObject);`
- L307 _public prototype_ `uint32 GetStructureHash() const;`
- L308 _public prototype_ `uint32 GetSerializedStructureHash() const;`
- L311 _public prototype_ `FRigVMClientPatchResult PatchModelsOnLoad();` — backwards compatibility
- L312 _public prototype_ `void PatchFunctionReferencesOnLoad();`
- L313 _public prototype_ `void PatchFunctionsOnLoad(IRigVMGraphFunctionHost* FunctionHost, TArray<FName>& BackwardsCompatiblePublicFunctions, TMap<URigVMLibraryNode*, FRigVMGraphFunctionHeader>& OldHeaders);`
- L314 _public prototype_ `FRigVMClientPatchResult PatchPinDefaultValues();`
- L317 _public prototype_ `void ProcessDetachedLinks();` — try to reattach detached links and delete remaining ones
- L320 _public prototype_ `void PreSave(FObjectPreSaveContext ObjectSaveContext);` — work to be done before saving
- L322 _public prototype_ `void HandleGraphModifiedEvent(ERigVMGraphNotifType InNotifType, URigVMGraph* InGraph, UObject* InSubject);`
- L324 _public prototype_ `FRigVMGraphFunctionStore* FindFunctionStore(const URigVMLibraryNode* InLibraryNode);`
- L325 _public prototype_ `bool UpdateGraphFunctionData(const URigVMLibraryNode* InLibraryNode);`
- L326 _public prototype_ `bool UpdateExternalVariablesForFunction(const URigVMLibraryNode* InLibraryNode);`
- L327 _public prototype_ `bool UpdateDependenciesForFunction(const URigVMLibraryNode* InLibraryNode);`
- L328 _public prototype_ `bool UpdateFunctionReferences(const FRigVMGraphFunctionHeader& InHeader, bool bUpdateDependencies, bool bUpdateExternalVariables);`
- L329 _public prototype_ `bool DirtyGraphFunctionCompilationData(URigVMLibraryNode* InLibraryNode);`
- L330 _public prototype_ `bool UpdateGraphFunctionSerializedGraph(URigVMLibraryNode* InLibraryNode);`
- L331 _public prototype_ `bool IsFunctionPublic(URigVMLibraryNode* InLibraryNode);`
- L334 _public prototype_ `bool UpgradeAllOccurencesOfNodes(const TArray<URigVMNode*>& InNodesToUpgrade, UObject* InOuter, bool bSetupUndoRedo = true);`
- L337 _public function_ `FRigVMClientPostGraphModified& GetPostGraphModified()` — Returns a delegate raised after a graph in this client was modified. Useful to track changes without keeping track of graphs.
- L340 _public member_ `static constexpr TCHAR RigVMModelPrefix[] = TEXT("Rig`
- L365 _private prototype_ `URigVMController* CreateController(const URigVMGraph* InModel);`
- L366 _private prototype_ `URigVMActionStack* GetOrCreateActionStack();`
- L367 _private prototype_ `void ResetActionStack();`
- L369 _private member_ `FRigVMGetFocusedGraph OnGetFocusedGraphDelegate;`
- L372 _private member_ `TSubclassOf<URigVMSchema> DefaultSchemaClass;` — `UPROPERTY(transient)`
- L375 _private member_ `TSubclassOf<URigVMController> ControllerClass;` — `UPROPERTY(transient)`
- L378 _private member_ `TArray<TObjectPtr<URigVMGraph>> Models;` — `UPROPERTY()`
- L381 _private member_ `TObjectPtr<URigVMFunctionLibrary> FunctionLibrary;` — `UPROPERTY()`
- L386 _private member_ `mutable TMap<FSoftObjectPath, TObjectPtr<URigVMController>> Controllers;` — `UPROPERTY(transient)` — Self-healing cache: GetController() can evict stale entries (orphaned controllers whose graph was replaced by an undo/redo transaction); declared mutable so the const observer path can do that.
- L394 _private prototype_ `void PurgeStaleController(const FSoftObjectPath& Key, URigVMController* StaleController) const;` — Evicts the slot at Key from Controllers and tears down the supplied controller if it is alive. Caller MUST hold ControllersLock. The slot is removed first so any reentrant lookup during teardown misses cleanly. StaleController may be nullptr or already-garbage — both are handled here so callers can pass any controller pointer without pre-checking. When non-null and not garbage, the controller's OnModified delegate is cleared, its action stack is detached, and it is renamed into the transient package, removed from root, and marked garbage (matching the teardown done by RemoveController).
- L397 _private member_ `TObjectPtr<URigVMActionStack> ActionStack;` — `UPROPERTY(transient)`
- L400 _private member_ `int32 UndoRedoIndex = 0;` — `UPROPERTY(transient)`
- L402 _private member_ `TArray<FRigVMClientAction> UndoStack;`
- L403 _private member_ `TArray<FRigVMClientAction> RedoStack;`
- L406 _public member_ `bool bSuspendNotifications;`
- L407 _public member_ `bool bIgnoreModelNotifications;`
- L408 _public member_ `bool bDefaultModelCanBeRemoved;`
- L409 _public member_ `bool bSuspendModelNotificationsForOthers;`
- L411 _private member_ `TWeakObjectPtr<UObject> OuterClientHost;`
- L412 _private member_ `FName OuterClientPropertyName;`
- L414 _private member_ `TWeakInterfacePtr<IRigVMClientExternalModelHost> ExternalModelHost;`
- L418 _private member_ `FRigVMClientPostGraphModified PostGraphModifiedDelegate;` — Delegate raised after any graph in this client was modified and after the client adopted these changes
- L421 _private member_ `mutable FTransactionallySafeCriticalSection OuterClientHostLock;`
- L422 _private member_ `mutable FTransactionallySafeCriticalSection ControllersLock;`

#### enum `FRigVMClient::ERigVMClientAction`  
`enum ERigVMClientAction`  
_L344-349_
- L346 _public enumerator_ `ERigVMClientAction_AddModel`
- L347 _public enumerator_ `ERigVMClientAction_RemoveModel`
- L348 _public enumerator_ `ERigVMClientAction_RenameModel`

#### struct `FRigVMClient::FRigVMClientAction`  
`struct FRigVMClientAction`  
_L351-363_
- L353 _public member_ `ERigVMClientAction Type;`
- L354 _public member_ `FString NodePath;`
- L355 _public member_ `FString OtherNodePath;`
- L362 _public member_ `int32 ModelIndex = INDEX_NONE;` — For ERigVMClientAction_RenameModel only: the index in Models[] the renamed graph occupied at action time. Used by PostTransacted to rebind the renamed graph back into the exact slot that property restoration nulled out, which avoids order corruption when more than one Models[] slot is nullptr simultaneously (e.g. two root-graph renames inside the same outer transaction during redo). INDEX_NONE for non-rename actions or when the graph wasn't tracked in Models.

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FRigVMClient> : public TStructOpsTypeTraitsBase2<FRigVMClient>`  
_L432-438_
- inherits: `TStructOpsTypeTraitsBase2<FRigVMClient>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L435-437_

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API RIGVMDEVELOPER_API`
- L29 _delegate_ `DECLARE_DELEGATE_RetVal(URigVMGraph*, FRigVMGetFocusedGraph);`
- L29 _prototype_ `DECLARE_DELEGATE_RetVal(URigVMGraph*, FRigVMGetFocusedGraph);`
- L208 _delegate_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FRigVMClientPostGraphModified, ERigVMGraphNotifType , URigVMGraph* , UObject* );`
- L208 _prototype_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FRigVMClientPostGraphModified, ERigVMGraphNotifType , URigVMGraph* , UObject* );`
- L436 _enumerator_ `WithCopy = true` (scope `TStructOpsTypeTraits::__anonebd7e8f50103`)

### `Plugins/Runtime/RigVM/Source/RigVMDeveloper/Public/RigVMModel/RigVMController.h` (Public)


#### enum `ERigVMControllerBulkEditType`  
`enum class ERigVMControllerBulkEditType : uint8`  
_L36-48_
- reflection: `UENUM()`
- L38 _public enumerator_ `AddExposedPin`
- L39 _public enumerator_ `RemoveExposedPin`
- L40 _public enumerator_ `RenameExposedPin`
- L41 _public enumerator_ `ChangeExposedPinType`
- L42 _public enumerator_ `AddVariable`
- L43 _public enumerator_ `RemoveVariable`
- L44 _public enumerator_ `RenameVariable`
- L45 _public enumerator_ `ChangeVariableType`
- L46 _public enumerator_ `RemoveFunction`
- L47 _public enumerator_ `Max UMETA(Hidden)`

#### enum `ERigVMControllerBulkEditProgress`  
`enum class ERigVMControllerBulkEditProgress : uint8`  
_L51-58_
- reflection: `UENUM()`
- L53 _public enumerator_ `BeginLoad`
- L54 _public enumerator_ `FinishedLoad`
- L55 _public enumerator_ `BeginEdit`
- L56 _public enumerator_ `FinishedEdit`
- L57 _public enumerator_ `Max UMETA(Hidden)`

#### struct `FRigVMController_BulkEditResult`  
`struct FRigVMController_BulkEditResult`  
_L60-69_
- L62 _public member_ `bool bCanceled;`
- L63 _public member_ `bool bSetupUndoRedo;`
- L65 _public function_ `FRigVMController_BulkEditResult() : bCanceled(false) , bSetupUndoRedo(true)`

#### class `FRigVMControllerCompileBracketScope`  
`class FRigVMControllerCompileBracketScope`  
_L71-83_
- L75 _public prototype_ `FRigVMControllerCompileBracketScope(URigVMController *InController);`
- L77 _public prototype_ `~FRigVMControllerCompileBracketScope();`
- L81 _private member_ `URigVMGraph* Graph;`
- L82 _private member_ `bool bSuspendNotifications;`

#### struct `FRigStructScope`  
`struct FRigStructScope`  
_L101-134_
- reflection: `USTRUCT(BlueprintType)`
- L107 _public function_ `FRigStructScope() : ScriptStruct(nullptr) , Memory(nullptr)`
- L116 _public function_ `FRigStructScope(const T& InInstance) : ScriptStruct(T::StaticStruct()) , Memory((const uint8*)&InInstance)`
- L121 _public function_ `FRigStructScope(const FStructOnScope& InScope) : ScriptStruct(Cast<UScriptStruct>(InScope.GetStruct())) , Memory(InScope.GetStructMemory())`
- L126 _public function_ `const UScriptStruct* GetScriptStruct() const`
- L127 _public function_ `const uint8* GetMemory() const`
- L128 _public function_ `bool IsValid() const`
- L132 _protected member_ `const UScriptStruct* ScriptStruct;`
- L133 _protected member_ `const uint8* Memory;`

#### struct `FRigVMClientPatchResult`  
`struct FRigVMClientPatchResult`  
_L138-172_
- reflection: `USTRUCT()`
- desc: A struct describing the result of a backwards compatibility patch
- L144 _public function_ `FRigVMClientPatchResult() : bSucceeded(true) , bChangedContent(false) , bRequiresToMarkPackageDirty(false)`
- L150 _public function_ `bool Succeeded() const`
- L151 _public function_ `bool ChangedContent() const`
- L152 _public function_ `bool RequiresToMarkPackageDirty() const`
- L154 _public function_ `const TArray<FString>& GetErrorMessages() const`
- L155 _public function_ `const TArray<FString>& GetRemovedNodes() const`
- L156 _public function_ `const TArray<TWeakObjectPtr<const URigVMNode>>& GetAddedNodes() const`
- L160 _private prototype_ `void Merge(const FRigVMClientPatchResult& InOther);`
- L162 _private member_ `bool bSucceeded;`
- L163 _private member_ `bool bChangedContent;`
- L164 _private member_ `bool bRequiresToMarkPackageDirty;`
- L166 _private member_ `TArray<FString> ErrorMessages;`
- L167 _private member_ `TArray<FString> RemovedNodes;`
- L168 _private member_ `TArray<TWeakObjectPtr<const URigVMNode>> AddedNodes;`

#### struct `FRigVMPinInfo`  
`struct FRigVMPinInfo`  
_L174-208_
- L176 _public prototype_ `FRigVMPinInfo();`
- L177 _public prototype_ `FRigVMPinInfo(const URigVMPin* InPin, int32 InParentIndex, ERigVMPinDirection InDirection, ERigVMPinDefaultValueType InDefaultValueType);`
- L178 _public prototype_ `FRigVMPinInfo(FProperty* InProperty, ERigVMPinDirection InDirection, int32 InParentIndex, ERigVMPinDefaultValueType InDefaultValueType, const uint8* InDefaultValueMemory);`
- L180 _public prototype_ `void CorrectExecuteTypeIndex();`
- L182 _public member_ `int32 ParentIndex;`
- L183 _public member_ `FGuid Guid;`
- L184 _public member_ `FName Name;`
- L185 _public member_ `ERigVMPinDirection Direction;`
- L186 _public member_ `TRigVMTypeIndex TypeIndex;`
- L187 _public member_ `bool bIsArray;`
- L188 _public member_ `FProperty* Property;`
- L189 _public member_ `FString PinPath;`
- L190 _public member_ `FString DefaultValue;`
- L191 _public member_ `ERigVMPinDefaultValueType DefaultValueType;`
- L192 _public member_ `FString DisplayName;`
- L193 _public member_ `FString CustomWidgetName;`
- L194 _public member_ `bool bIsExpanded;`
- L195 _public member_ `bool bIsConstant;`
- L196 _public member_ `bool bIsInputVariable;`
- L197 _public member_ `bool bIsDynamicArray;`
- L198 _public member_ `bool bIsTrait;`
- L199 _public member_ `bool bIsLazy;`
- L200 _public member_ `TArray<int32> SubPins;`
- L204 _public function_ `bool ShouldHideSubPins() const`

#### struct `FRigVMPinInfoArray`  
`struct FRigVMPinInfoArray`  
_L210-237_
- L212 _public function_ `FRigVMPinInfoArray()`
- L213 _public prototype_ `explicit FRigVMPinInfoArray(const URigVMNode* InNode, URigVMController* InController);`
- L214 _public prototype_ `FRigVMPinInfoArray(const URigVMNode* InNode, URigVMController* InController, const FRigVMPinInfoArray* InPreviousPinInfos);`
- L215 _public prototype_ `FRigVMPinInfoArray(const FRigVMGraphFunctionHeader& FunctionHeader, URigVMController* InController, const FRigVMPinInfoArray* InPreviousPinInfos = nullptr);`
- L217 _public function_ `int32 Num() const`
- L218 _public function_ `const FRigVMPinInfo& operator[](int32 InIndex) const`
- L219 _public function_ `FRigVMPinInfo& operator[](int32 InIndex)`
- L220 _public function_ `TArray<FRigVMPinInfo>::RangedForIteratorType begin() const`
- L221 _public function_ `TArray<FRigVMPinInfo>::RangedForIteratorType end() const`
- L223 _public prototype_ `int32 AddPin(const URigVMPin* InPin, int32 InParentIndex, ERigVMPinDirection InDirection, ERigVMPinDefaultValueType InDefaultValueType);`
- L224 _public prototype_ `int32 AddPin(FProperty* InProperty, URigVMController* InController, ERigVMPinDirection InDirection, int32 InParentIndex, ERigVMPinDefaultValueType InDefaultValueType, const uint8* InDefaultValueMemory, bool bAddSubPins);`
- L225 _public prototype_ `int32 AddPin(URigVMController* InController, int32 InParentIndex, const FName& InName, ERigVMPinDirection InDirection, TRigVMTypeIndex InTypeIndex, const FString& InDefaultValue, ERigVMPinDefaultValueType InDefaultValueType, const uint8* InDefaultValueMemory, const FRigVMPinInfoArray* InPreviousPinInfos, bool bAddSubPins);`
- L226 _public prototype_ `void AddPins(UScriptStruct* InScriptStruct, URigVMController* InController, ERigVMPinDirection InDirection, int32 InParentIndex, TFunction<ERigVMPinDefaultValueType(const FName&)> InDefaultValueTypeGetter, const uint8* InDefaultValueMemory, bool bAddSubPins);`
- L228 _public prototype_ `const FString& GetPinPath(const int32 InIndex) const;`
- L229 _public prototype_ `int32 GetIndexFromPinPath(const FString& InPinPath) const;`
- L230 _public prototype_ `const FRigVMPinInfo* GetPinFromPinPath(const FString& InPinPath) const;`
- L231 _public prototype_ `int32 GetRootIndex(const int32 InIndex) const;`
- L235 _public member_ `mutable TArray<FRigVMPinInfo> Pins;`
- L236 _public member_ `mutable TMap<FString, int32> PinPathLookup;`

#### class `URigVMController`  
`class URigVMController : public UObject`  
_L254-1793_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UObject`
- desc: The Controller is the sole authority to perform changes on the Graph. The Controller itself is stateless. The Controller offers a Modified event to subscribe to for user interface views - so they can be informed about any change that's happening within the Graph. The Controller routes all changes through the Graph itself, so you can have N Controllers performing edits on 1 Graph, and N Views subscribing to 1 Controller. In Python you can also subscribe to this event to be able to react to topological changes of the Graph there.
- L261 _public prototype_ `URigVMController();` — Default constructor
- L264 _public prototype_ `~URigVMController();` — Default destructor
- L267 _public prototype_ `static void DeclareConstructClasses(TArray<FTopLevelAssetPath>& OutConstructClasses, const UClass* SpecificSubclass);`
- L272 _public prototype_ `URigVMGraph* GetGraph() const;` — `UFUNCTION(BlueprintCallable, Category = RigVMController)` — Returns the currently edited Graph of this controller.
- L277 _public prototype_ `void SetGraph(URigVMGraph* InGraph);` — `UFUNCTION(BlueprintCallable, Category = RigVMController, meta=(DeprecatedFunction, DeprecationMessage="Function has been deprecated, please rely on GetControllerForGraph instead."))` — Sets the currently edited Graph of this controller. This causes a GraphChanged modified event.
- L281 _public prototype_ `URigVMSchema* GetSchema() const;` — `UFUNCTION(BlueprintCallable, Category = RigVMController)` — Returns the schema used by this controller
- L285 _public function_ `void SetSchema(URigVMSchema* InSchema)` — `UE_DEPRECATED(5.5, "Please use SetSchemaClass instead.")` — `UFUNCTION(BlueprintCallable, Category = RigVMController, meta=(DeprecatedFunction, DeprecationMessage="Function has been deprecated, please use SetSchemaClass instead."))`
- L289 _public function_ `void SetSchemaClass(TSubclassOf<URigVMSchema> InSchemaClass)` — `UFUNCTION(BlueprintCallable, Category = RigVMController)` — Sets the schema class on the controller
- L294 _public prototype_ `bool PushGraph(URigVMGraph* InGraph, bool bSetupUndoRedo = true);` — `UFUNCTION(BlueprintCallable, Category = RigVMController, meta=(DeprecatedFunction, DeprecationMessage="Function has been deprecated, please rely on GetControllerForGraph instead."))` — Pushes a new graph to the stack This causes a GraphChanged modified event.
- L299 _public prototype_ `URigVMGraph* PopGraph(bool bSetupUndoRedo = true);` — `UFUNCTION(BlueprintCallable, Category = RigVMController, meta=(DeprecatedFunction, DeprecationMessage="Function has been deprecated, please rely on GetControllerForGraph instead."))` — Pops the last graph off the stack This causes a GraphChanged modified event.
- L303 _public prototype_ `URigVMGraph* GetTopLevelGraph() const;` — `UFUNCTION(BlueprintCallable, Category = RigVMController)` — Returns the top level graph
- L307 _public prototype_ `URigVMController* GetControllerForGraph(const URigVMGraph* InGraph) const;` — `UFUNCTION(BlueprintCallable, Category = RigVMController)` — Returns another controller for a given graph
- L310 _public prototype_ `IRigVMClientHost* GetClientHost() const;` — Returns the client host this controller belongs to
- L313 _public prototype_ `TArray<FName> GetAllEventNames() const;` — Returns all events present on the client host
- L320 _public prototype_ `FRigVMGraphModifiedEvent& OnModified();` — The Modified event used to subscribe to changes happening within the Graph. This is broadcasted to for any change happening - not only the changes performed by this Controller - so it can be used for UI Views to react accordingly.
- L323 _public prototype_ `void Notify(ERigVMGraphNotifType InNotifType, UObject* InSubject) const;` — Submits an event to the graph for broadcasting.
- L326 _public prototype_ `void ResendAllNotifications();` — Resends all notifications
- L330 _public function_ `void EnableReporting(bool bEnabled = true)` — `UFUNCTION(BlueprintCallable, Category = RigVMController)` — Enables or disables the error reporting of this Controller.
- L334 _public function_ `bool IsReportingEnabled() const` — `UFUNCTION(BlueprintPure, Category = RigVMController)` — Returns true if reporting is enabled
- L338 _public function_ `bool IsTransacting() const` — `UFUNCTION(BlueprintPure, Category = RigVMController)` — Returns true if the controller is currently transacting
- L341 _public prototype_ `TArray<FString> GeneratePythonCommands();` — `UFUNCTION(BlueprintCallable, Category = RigVMController)`
- L343 _public prototype_ `TArray<FString> GetAddNodePythonCommands(URigVMNode* Node) const;`
- L344 _public prototype_ `TArray<FString> GetAddTraitPythonCommands(URigVMNode* Node, const FName& TraitName) const;`
- L346 _public prototype_ `FRigVMGraphFunctionStore* GetGraphFunctionStore() const;`
- L347 _public prototype_ `FRigVMGraphFunctionData* FindFunctionData(const FName& InFunctionName) const;`
- L358 _public prototype_ `URigVMUnitNode* AddUnitNode(UScriptStruct* InScriptStruct, const FName& InMethodName = TEXT("Execute"), const FVector2D& InPosition = FVector2D::ZeroVector, const FString& InNodeName = TEXT(""), bool bSetupUndoRedo = true, bool bPrintPythonCommand =` — `UFUNCTION(BlueprintCallable, Category = RigVMController)` — Adds a Function / Struct Node to the edited Graph. UnitNode represent a RIGVM_METHOD declaration on a USTRUCT. This causes a NodeAdded modified event.
- L364 _public prototype_ `URigVMUnitNode* AddUnitNodeFromStructPath(const FString& InScriptStructPath, const FName& InMethodName = TEXT("Execute"), const FVector2D& InPosition = FVector2D::ZeroVector, const FString& InNodeName = TEXT(""), bool bSetupUndoRedo = true, bool bPrintPythonCommand =` — `UFUNCTION(BlueprintCallable, Category = RigVMController)` — Adds a Function / Struct Node to the edited Graph given its struct object path name. UnitNode represent a RIGVM_METHOD declaration on a USTRUCT. This causes a NodeAdded modified event.
- L371 _public function_ `URigVMUnitNode* AddUnitNode(const T& InDefaults, const FName& InMethodName = TEXT("Execute"), const FVector2D& InPosition = FVector2D::ZeroVector, const FString& InNodeName = TEXT(""), bool bSetupUndoRedo = true, bool bPrintPythonCommand = false)`
- L380 _public prototype_ `URigVMUnitNode* AddUnitNodeWithDefaults(UScriptStruct* InScriptStruct, const FString& InDefaults, const FName& InMethodName = TEXT("Execute"), const FVector2D& InPosition = FVector2D::ZeroVector, const FString& InNodeName = TEXT(""), bool bSetupUndoRedo = true, bool bPrintPythonCommand =` — `UFUNCTION(BlueprintCallable, Category = RigVMController)` — Adds a Function / Struct Node to the edited Graph. UnitNode represent a RIGVM_METHOD declaration on a USTRUCT. This causes a NodeAdded modified event.
- L385 _public prototype_ `URigVMUnitNode* AddUnitNodeWithDefaults(UScriptStruct* InScriptStruct, const FRigStructScope& InDefaults, const FName& InMethodName = TEXT("Execute"), const FVector2D& InPosition = FVector2D::ZeroVector, const FString& InNodeName = TEXT(""), bool bSetupUndoRedo = true, bool bPrintPythonCommand =` — Adds a Function / Struct Node to the edited Graph. UnitNode represent a RIGVM_METHOD declaration on a USTRUCT. This causes a NodeAdded modified event.
- L386 _public prototype_ `URigVMUnitNode* AddUnitNodeWithDefaults(UScriptStruct* InScriptStruct, TSubclassOf<URigVMUnitNode> InUnitNodeClass, const FRigStructScope& InDefaults, const FName& InMethodName = TEXT("Execute"), const FVector2D& InPosition = FVector2D::ZeroVector, const FString& InNodeName = TEXT(""), bool bSetupUndoRedo = true, bool bPrintPythonCommand =`
- L392 _public prototype_ `bool SetUnitNodeDefaults(URigVMUnitNode* InNode, const FString& InDefaults, bool bSetupUndoRedo = true, bool bPrintPythonCommand = false);` — `UFUNCTION(BlueprintCallable, Category = RigVMController)` — Adds a Function / Struct Node to the edited Graph. UnitNode represent a RIGVM_METHOD declaration on a USTRUCT. This causes a NodeAdded modified event.
- L393 _public prototype_ `bool SetUnitNodeDefaults(URigVMUnitNode* InNode, const FRigStructScope& InDefaults, bool bSetupUndoRedo = true, bool bPrintPythonCommand = false);`
- L400 _public prototype_ `URigVMVariableNode* AddVariableNode(const FName& InVariableName, const FString& InCPPType, UObject* InCPPTypeObject, bool bIsGetter, const FString& InDefaultValue, const FVector2D& InPosition = FVector2D::ZeroVector, const FString& InNodeName = TEXT(""), bool bSetupUndoRedo = true, bool bPrintPythonCommand = false);` — `UFUNCTION(BlueprintCallable, Category = RigVMController)` — Adds a Variable Node to the edited Graph. Variables represent local work state for the function and can be read from and written to. This causes a NodeAdded modified event.
- L401 _public prototype_ `URigVMVariableNode* AddVariableNode(const FName& InVariableName, TSubclassOf<URigVMVariableNode> InVariableNodeClass, const FString& InCPPType, UObject* InCPPTypeObject, bool bIsGetter, const FString& InDefaultValue, const FVector2D& InPosition = FVector2D::ZeroVector, const FString& InNodeName = TEXT(""), bool bSetupUndoRedo = true, bool bPrintPythonCommand = false);`
- L408 _public prototype_ `URigVMVariableNode* AddVariableNodeFromObjectPath(const FName& InVariableName, const FString& InCPPType, const FString& InCPPTypeObjectPath, bool bIsGetter, const FString& InDefaultValue, const FVector2D& InPosition = FVector2D::ZeroVector, const FString& InNodeName = TEXT(""), bool bSetupUndoRedo = true, bool bPrintPythonCommand = false);` — `UFUNCTION(BlueprintCallable, Category = RigVMController)` — Adds a Variable Node to the edited Graph given a struct object path name. Variables represent local work state for the function and can be read from (bIsGetter == true) or written to (bIsGetter == false). This causes a NodeAdded modified event.
- L412 _public prototype_ `void RefreshVariableNode(const FName& InNodeName, const FName& InVariableName, const FString& InCPPType, UObject* InCPPTypeObject, bool bSetupUndoRedo, bool bSetupOrphanPins = true);` — `UFUNCTION(BlueprintCallable, Category = RigVMController, meta = (DeprecatedFunction, DeprecationMessage = "Use RefreshVariableNode that takes a FGuid"))` — Refreshes the variable node with the new data
- L415 _public prototype_ `void RefreshVariableNode(const FName& InNodeName, const FGuid& InVariableGuid, const FName& InVariableName, const FString& InCPPType, UObject* InCPPTypeObject, bool bSetupUndoRedo, bool bSetupOrphanPins = true);` — Refreshes the variable node with the new data
- L418 _public prototype_ `void OnExternalVariableRemoved(const FGuid& InVarGuid, bool bSetupUndoRedo);` — Removes all nodes related to a given variable
- L421 _public prototype_ `bool OnExternalVariableRenamed(const FGuid& InVarGuid, const FName& InNewVarName, bool bSetupUndoRedo);` — Renames the variable name in all relevant nodes
- L425 _public prototype_ `void OnExternalVariableTypeChanged(const FName& InVarName, const FString& InCPPType, UObject* InCPPTypeObject, bool bSetupUndoRedo);` — `UE_DEPRECATED(5.8, "Use OnExternalVariableTypeChanged that receives the variable Guid")` — Changes the data type of all nodes matching a given variable name
- L426 _public prototype_ `void OnExternalVariableTypeChanged(const FGuid& InVarGuid, const FString& InCPPType, UObject* InCPPTypeObject, bool bSetupUndoRedo);`
- L428 _public prototype_ `void OnExternalVariableTypeChangedFromObjectPath(const FName& InVarName, const FString& InCPPType, const FString& InCPPTypeObjectPath, bool bSetupUndoRedo);` — `UE_DEPRECATED(5.8, "Use OnExternalVariableTypeChangedFromObjectPath that receives the variable Guid")`
- L429 _public prototype_ `void OnExternalVariableTypeChangedFromObjectPath(const FGuid& InVarGuid, const FString& InCPPType, const FString& InCPPTypeObjectPath, bool bSetupUndoRedo);`
- L434 _public prototype_ `URigVMVariableNode* ReplaceParameterNodeWithVariable(const FName& InNodeName, const FName& InVariableName, const FString& InCPPType, UObject* InCPPTypeObject, bool bSetupUndoRedo);` — `UFUNCTION(BlueprintCallable, Category = RigVMController)` — Refreshes the variable node with the new data
- L438 _public prototype_ `bool UnresolveTemplateNodes(const TArray<FName>& InNodeNames, bool bSetupUndoRedo = true, bool bPrintPythonCommand = false);` — `UFUNCTION(BlueprintCallable, Category = RigVMController)` — Turns a resolved templated node(s) back into its template.
- L439 _public prototype_ `bool UnresolveTemplateNodes(const TArray<URigVMNode*>& InNodes, bool bSetupUndoRedo);`
- L443 _public prototype_ `TArray<URigVMNode*> UpgradeNodes(const TArray<FName>& InNodeNames, bool bRecursive = true, bool bSetupUndoRedo = true, bool bPrintPythonCommand = false);` — `UFUNCTION(BlueprintCallable, Category = RigVMController)` — Upgrades a set of nodes with each corresponding next known version
- L450 _public prototype_ `URigVMParameterNode* AddParameterNode(const FName& InParameterName, const FString& InCPPType, UObject* InCPPTypeObject, bool bIsInput, const FString& InDefaultValue, const FVector2D& InPosition = FVector2D::ZeroVector, const FString& InNodeName = TEXT(""), bool bSetupUndoRedo = true, bool bPrintPythonCommand = false);` — `UFUNCTION(BlueprintCallable, Category = RigVMController, meta=(DeprecatedFunction))` — Adds a Parameter Node to the edited Graph. Parameters represent input or output arguments to the Graph / Function. Input Parameters are constant values / literals. This causes a NodeAdded modified event.
- L457 _public prototype_ `URigVMParameterNode* AddParameterNodeFromObjectPath(const FName& InParameterName, const FString& InCPPType, const FString& InCPPTypeObjectPath, bool bIsInput, const FString& InDefaultValue, const FVector2D& InPosition = FVector2D::ZeroVector, const FString& InNodeName = TEXT(""), bool bSetupUndoRedo = true, bool bPrintPythonCommand = false);` — `UFUNCTION(BlueprintCallable, Category = RigVMController, meta=(DeprecatedFunction))` — Adds a Parameter Node to the edited Graph given a struct object path name. Parameters represent input or output arguments to the Graph / Function. Input Parameters are constant values / literals. This causes a NodeAdded modified event.
- L463 _public prototype_ `URigVMCommentNode* AddCommentNode(const FString& InCommentText, const FVector2D& InPosition = FVector2D::ZeroVector, const FVector2D& InSize = FVector2D(400.f, 300.f), const FLinearColor& InColor = FLinearColor::Black, const FString& InNodeName = TEXT(""), bool bSetupUndoRedo = true, bool bPrintPythonCommand = false);` — `UFUNCTION(BlueprintCallable, Category = RigVMController)` — Adds a Comment Node to the edited Graph. Comments can be used to annotate the Graph. This causes a NodeAdded modified event.
- L470 _public prototype_ `URigVMRerouteNode* AddRerouteNodeOnLink(URigVMLink* InLink, const FVector2D& InPosition = FVector2D::ZeroVector, const FString& InNodeName = TEXT(""), bool bSetupUndoRedo = true, bool bPrintPythonCommand = false);` — `UFUNCTION(BlueprintCallable, Category = RigVMController)` — Adds a Reroute Node on an existing Link to the edited Graph. Reroute Nodes can be used to visually improve the data flow, they don't require any additional memory though and are purely cosmetic. This causes a NodeAdded modified event.
- L477 _public prototype_ `URigVMRerouteNode* AddRerouteNodeOnLinkPath(const FString& InLinkPinPathRepresentation, const FVector2D& InPosition = FVector2D::ZeroVector, const FString& InNodeName = TEXT(""), bool bSetupUndoRedo = true, bool bPrintPythonCommand = false);` — `UFUNCTION(BlueprintCallable, Category = RigVMController)` — Adds a Reroute Node on an existing Link to the edited Graph given the Link's string representation. Reroute Nodes can be used to visually improve the data flow, they don't require any additional memory though and are purely cosmetic. This causes a NodeAdded modified event.
- L484 _public prototype_ `URigVMRerouteNode* AddRerouteNodeOnPin(const FString& InPinPath, bool bAsInput, const FVector2D& InPosition = FVector2D::ZeroVector, const FString& InNodeName = TEXT(""), bool bSetupUndoRedo = true, bool bPrintPythonCommand = false);` — `UFUNCTION(BlueprintCallable, Category = RigVMController)` — Adds a Reroute Node on an existing Pin to the editor Graph. Reroute Nodes can be used to visually improve the data flow, they don't require any additional memory though and are purely cosmetic. This causes a NodeAdded modified event.
- L488 _public prototype_ `URigVMRerouteNode* AddFreeRerouteNode(const FString& InCPPType, const FName& InCPPTypeObjectPath, bool bIsConstant, const FName& InCustomWidgetName, const FString& InDefaultValue, const FVector2D& InPosition = FVector2D::ZeroVector, const FString& InNodeName = TEXT(""), bool bSetupUndoRedo = true);` — `UFUNCTION(BlueprintCallable, Category = RigVMController)` — Adds a free Reroute Node
- L491 _public prototype_ `URigVMTemplateNode* AddConstantNode(const FString& InCPPType, const FName& InCPPTypeObjectPath, const FString& InDefaultValue, const FVector2D& InPosition = FVector2D::ZeroVector, const FString& InNodeName = TEXT(""), bool bSetupUndoRedo = true);` — helper function to set up a constant node
- L494 _public prototype_ `URigVMTemplateNode* AddMakeStructNode(const FString& InCPPType, const FName& InCPPTypeObjectPath, const FString& InDefaultValue, const FVector2D& InPosition = FVector2D::ZeroVector, const FString& InNodeName = TEXT(""), bool bSetupUndoRedo = true);` — helper function to set up a make struct node
- L497 _public prototype_ `URigVMTemplateNode* AddBreakStructNode(const FString& InCPPType, const FName& InCPPTypeObjectPath, const FString& InDefaultValue, const FVector2D& InPosition = FVector2D::ZeroVector, const FString& InNodeName = TEXT(""), bool bSetupUndoRedo = true);` — helper function to set up a break struct node
- L500 _public prototype_ `URigVMTemplateNode* AddConstantNodeOnPin(const FString& InPinPath, const FVector2D& InPosition = FVector2D::ZeroVector, const FString& InNodeName = TEXT(""), bool bSetupUndoRedo = true);` — helper function to set up a constant node on a pin
- L503 _public prototype_ `URigVMTemplateNode* AddMakeStructNodeOnPin(const FString& InPinPath, const FVector2D& InPosition = FVector2D::ZeroVector, const FString& InNodeName = TEXT(""), bool bSetupUndoRedo = true);` — helper function to set up a make struct node on a pin
- L506 _public prototype_ `URigVMTemplateNode* AddBreakStructNodeOnPin(const FString& InPinPath, const FVector2D& InPosition = FVector2D::ZeroVector, const FString& InNodeName = TEXT(""), bool bSetupUndoRedo = true);` — helper function to set up a break struct node on a pin
- L512 _public prototype_ `URigVMNode* AddBranchNode(const FVector2D& InPosition = FVector2D::ZeroVector, const FString& InNodeName = TEXT(""), bool bSetupUndoRedo = true, bool bPrintPythonCommand = false);` — `UFUNCTION(BlueprintCallable, Category = RigVMController)` — Adds a branch node to the graph. Branch nodes can be used to split the execution of into multiple branches, allowing to drive behavior by logic.
- L517 _public prototype_ `URigVMNode* AddIfNode(const FString& InCPPType, const FName& InCPPTypeObjectPath, const FVector2D& InPosition = FVector2D::ZeroVector, const FString& InNodeName = TEXT(""), bool bSetupUndoRedo = true, bool bPrintPythonCommand = false);` — `UFUNCTION(BlueprintCallable, Category = RigVMController)` — Adds an if node to the graph. If nodes can be used to pick between two values based on a condition.
- L519 _public prototype_ `URigVMNode* AddIfNodeFromStruct(UScriptStruct* InScriptStruct, const FVector2D& InPosition = FVector2D::ZeroVector, const FString& InNodeName = TEXT(""), bool bSetupUndoRedo = true);` — `UFUNCTION(BlueprintCallable, Category = RigVMController)`
- L524 _public prototype_ `URigVMNode* AddSelectNode(const FString& InCPPType, const FName& InCPPTypeObjectPath, const FVector2D& InPosition = FVector2D::ZeroVector, const FString& InNodeName = TEXT(""), bool bSetupUndoRedo = true, bool bPrintPythonCommand = false);` — `UFUNCTION(BlueprintCallable, Category = RigVMController)` — Adds a select node to the graph. Select nodes can be used to pick between multiple values based on an index.
- L526 _public prototype_ `URigVMNode* AddSelectNodeFromStruct(UScriptStruct* InScriptStruct, const FVector2D& InPosition = FVector2D::ZeroVector, const FString& InNodeName = TEXT(""), bool bSetupUndoRedo = true);` — `UFUNCTION(BlueprintCallable, Category = RigVMController)`
- L530 _public prototype_ `URigVMTemplateNode* AddTemplateNode(const FName& InNotation, const FVector2D& InPosition = FVector2D::ZeroVector, const FString& InNodeName = TEXT(""), bool bSetupUndoRedo = true, bool bPrintPythonCommand = false);` — `UFUNCTION(BlueprintCallable, Category = RigVMController)` — Adds a template node to the graph.
- L534 _public prototype_ `static TArray<UScriptStruct*> GetRegisteredUnitStructs();` — `UFUNCTION(BlueprintCallable, Category = RigVMController)` — Returns all registered unit structs
- L538 _public prototype_ `static TArray<FString> GetRegisteredTemplates();` — `UFUNCTION(BlueprintCallable, Category = RigVMController)` — Returns all registered template notations
- L542 _public prototype_ `static TArray<UScriptStruct*> GetUnitStructsForTemplate(const FName& InNotation);` — `UFUNCTION(BlueprintCallable, Category = RigVMController)` — Returns all supported unit structs for a given template notation
- L546 _public prototype_ `static FString GetTemplateForUnitStruct(UScriptStruct* InFunction, const FString& InMethodName = TEXT("Exec` — `UFUNCTION(BlueprintCallable, Category = RigVMController)` — Returns the template for a given function (or an empty string)
- L550 _public prototype_ `bool ResolveWildCardPin(const FString& InPinPath, const FString& InCPPType, const FName& InCPPTypeObjectPath, bool bSetupUndoRedo = true, bool bPrintPythonCommand = false);` — `UFUNCTION(BlueprintCallable, Category = RigVMController)` — Resolves a wildcard pin on any node
- L551 _public prototype_ `bool ResolveWildCardPin(URigVMPin* InPin, const FRigVMTemplateArgumentType& InType, bool bSetupUndoRedo = true, bool bPrintPythonCommand = false);`
- L552 _public prototype_ `bool ResolveWildCardPin(const FString& InPinPath, TRigVMTypeIndex InTypeIndex, bool bSetupUndoRedo = true, bool bPrintPythonCommand = false);`
- L553 _public prototype_ `bool ResolveWildCardPin(URigVMPin* InPin, TRigVMTypeIndex InTypeIndex, bool bSetupUndoRedo = true, bool bPrintPythonCommand = false);`
- L559 _public prototype_ `URigVMInjectionInfo* AddInjectedNode(const FString& InPinPath, bool bAsInput, UScriptStruct* InScriptStruct, const FName& InMethodName, const FName& InInputPinName, const FName& InOutputPinName, const FString& InNodeName = TEXT(""), bool bSetupUndoRedo = true, bool bPrintPythonCommand = false);` — `UFUNCTION(BlueprintCallable, Category = RigVMController)` — Adds a Function / Struct Node to the edited Graph as an injected node UnitNode represent a RIGVM_METHOD declaration on a USTRUCT. This causes a NodeAdded modified event.
- L565 _public prototype_ `URigVMInjectionInfo* AddInjectedNodeFromStructPath(const FString& InPinPath, bool bAsInput, const FString& InScriptStructPath, const FName& InMethodName, const FName& InInputPinName, const FName& InOutputPinName, const FString& InNodeName = TEXT(""), bool bSetupUndoRedo = true);` — `UFUNCTION(BlueprintCallable, Category = RigVMController)` — Adds a Function / Struct Node to the edited Graph as an injected node UnitNode represent a RIGVM_METHOD declaration on a USTRUCT. This causes a NodeAdded modified event.
- L570 _public prototype_ `bool RemoveInjectedNode(const FString& InPinPath, bool bAsInput, bool bSetupUndoRedo = true, bool bPrintPythonCommand = false);` — `UFUNCTION(BlueprintCallable, Category = RigVMController)` — Removes an injected node This causes a NodeRemoved modified event.
- L574 _public prototype_ `URigVMNode* EjectNodeFromPin(const FString& InPinPath, bool bSetupUndoRedo = true, bool bPrintPythonCommand = false);` — `UFUNCTION(BlueprintCallable, Category = RigVMController)` — Ejects the last injected node on a pin
- L579 _public prototype_ `URigVMEnumNode* AddEnumNode(const FName& InCPPTypeObjectPath, const FVector2D& InPosition = FVector2D::ZeroVector, const FString& InNodeName = TEXT(""), bool bSetupUndoRedo = true, bool bPrintPythonCommand = false);` — `UFUNCTION(BlueprintCallable, Category = RigVMController)` — Adds an enum node to the graph Enum nodes can be used to represent constant enum values within the graph
- L584 _public prototype_ `URigVMNode* AddArrayNode(ERigVMOpCode InOpCode, const FString& InCPPType, UObject* InCPPTypeObject, const FVector2D& InPosition = FVector2D::ZeroVector, const FString& InNodeName = TEXT(""), bool bSetupUndoRedo = true, bool bPrintPythonCommand = false, bool bIsPatching = false);` — `UFUNCTION(BlueprintCallable, Category = RigVMController)` — Adds a Array Node to the edited Graph. This causes a NodeAdded modified event.
- L589 _public prototype_ `URigVMNode* AddArrayNodeFromObjectPath(ERigVMOpCode InOpCode, const FString& InCPPType, const FString& InCPPTypeObjectPath, const FVector2D& InPosition = FVector2D::ZeroVector, const FString& InNodeName = TEXT(""), bool bSetupUndoRedo = true, bool bPrintPythonCommand = false, bool bIsPatching = false);` — `UFUNCTION(BlueprintCallable, Category = RigVMController)` — Adds a Array Node to the edited Graph given a struct object path name. This causes a NodeAdded modified event.
- L594 _public prototype_ `URigVMInvokeEntryNode* AddInvokeEntryNode(const FName& InEntryName, const FVector2D& InPosition = FVector2D::ZeroVector, const FString& InNodeName = TEXT(""), bool bSetupUndoRedo = true, bool bPrintPythonCommand = false);` — `UFUNCTION(BlueprintCallable, Category = RigVMController)` — Adds an entry invocation node This causes a NodeAdded modified event.
- L598 _public prototype_ `FName AddTrait(const FName& InNodeName, const FName& InTraitTypeObjectPath, const FName& InTraitName = NAME_None, const FString& InDefaultValue = TEXT(""), int32 InPinIndex = -1, bool bSetupUndoRedo = true, bool bPrintPythonCommand = false);` — `UFUNCTION(BlueprintCallable, Category = RigVMController)` — Adds a trait to a node
- L599 _public prototype_ `FName AddTrait(URigVMNode* InNode, UScriptStruct* InTraitScriptStruct, const FName& InTraitName, const FString& InDefaultValue, int32 InPinIndex = -1, bool bSetupUndoRedo = true);`
- L603 _public prototype_ `virtual bool RemoveTrait(const FName& InNodeName, const FName& InTraitName, bool bSetupUndoRedo = true, bool bPrintPythonCommand = false);` — `UFUNCTION(BlueprintCallable, Category = RigVMController)` — Removes a trait from a node
- L604 _public prototype_ `bool RemoveTrait(URigVMNode* InNode, const FName& InTraitName, bool bSetupUndoRedo = true);`
- L610 _public prototype_ `bool Undo();` — `UFUNCTION(BlueprintCallable, Category = RigVMController)` — Un-does the last action on the stack. Note: This should really only be used for unit tests, use the GEditor's main Undo method instead.
- L616 _public prototype_ `bool Redo();` — `UFUNCTION(BlueprintCallable, Category = RigVMController)` — Re-does the last action on the stack. Note: This should really only be used for unit tests, use the GEditor's main Undo method instead.
- L623 _public prototype_ `bool OpenUndoBracket(const FString& InTitle);` — `UFUNCTION(BlueprintCallable, Category = RigVMController)` — Opens an undo bracket / scoped transaction for a series of actions to be performed as one step on the Undo stack. This is primarily useful for Python. This causes a UndoBracketOpened modified event.
- L629 _public prototype_ `bool CloseUndoBracket();` — `UFUNCTION(BlueprintCallable, Category = RigVMController)` — Closes an undo bracket / scoped transaction. This is primarily useful for Python. This causes a UndoBracketClosed modified event.
- L635 _public prototype_ `bool CancelUndoBracket();` — `UFUNCTION(BlueprintCallable, Category = RigVMController)` — Cancels an undo bracket / scoped transaction. This is primarily useful for Python. This causes a UndoBracketCanceled modified event.
- L639 _public prototype_ `FString ExportNodesToText(const TArray<FName>& InNodeNames, bool bIncludeExteriorLinks = false);` — `UFUNCTION(BlueprintCallable, Category = RigVMController)` — Exports the given nodes as text
- L643 _public prototype_ `FString ExportNodeToText(const URigVMNode* InNode, bool bIncludeExteriorLinks = false);` — `UFUNCTION(BlueprintCallable, Category = RigVMController)` — Exports the given node as text
- L647 _public prototype_ `FString ExportSelectedNodesToText(bool bIncludeExteriorLinks = false);` — `UFUNCTION(BlueprintCallable, Category = RigVMController)` — Exports the selected nodes as text
- L651 _public prototype_ `bool CanImportNodesFromText(const FString& InText);` — `UFUNCTION(BlueprintCallable, Category = RigVMController)` — Exports the given nodes as text
- L655 _public prototype_ `TArray<FName> ImportNodesFromText(const FString& InText, bool bSetupUndoRedo = true, bool bPrintPythonCommands = false);` — `UFUNCTION(BlueprintCallable, Category = RigVMController)` — Exports the given nodes as text
- L658 _public prototype_ `bool ExportFunctionToArchive(const FName& InFunctionName, FRigVMObjectArchive& OutArchive);` — Exports the given function to a binary archive
- L661 _public prototype_ `URigVMLibraryNode* ImportFunctionFromArchive(const FRigVMObjectArchive& InArchive, const FName& InFunctionName = FName(NAME_None));` — Imports a function from a binary archive
- L665 _public prototype_ `URigVMLibraryNode* LocalizeFunctionFromPath(const FString& InHostPath, const FName& InFunctionName, bool bLocalizeDependentPrivateFunctions = true, bool bSetupUndoRedo = true, bool bPrintPythonCommand = false);` — `UFUNCTION(BlueprintCallable, Category = RigVMController)` — Copies a function declaration into this graph's local function library
- L668 _public prototype_ `URigVMLibraryNode* LocalizeFunction( const FRigVMGraphFunctionIdentifier& InFunctionDefinition, bool bLocalizeDependentPrivateFunctions = true, bool bSetupUndoRedo = true, bool bPrintPythonCommand = false);` — `UFUNCTION(BlueprintCallable, Category = RigVMController)`
- L676 _public prototype_ `TMap<FRigVMGraphFunctionIdentifier, URigVMLibraryNode*> LocalizeFunctions( TArray<FRigVMGraphFunctionIdentifier> InFunctionDefinitions, bool bLocalizeDependentPrivateFunctions = true, bool bSetupUndoRedo = true, bool bPrintPythonCommand = false);` — `UFUNCTION(BlueprintCallable, Category = RigVMController)` — Copies a series of function declaratioms into this graph's local function library
- L685 _public prototype_ `URigVMCollapseNode* CollapseNodes(const TArray<FName>& InNodeNames, const FString& InCollapseNodeName = TEXT(""), bool bSetupUndoRedo = true, bool bPrintPythonCommand = false, bool bIsAggregate = false);` — `UFUNCTION(BlueprintCallable, Category = RigVMController)` — Turns a series of nodes into a Collapse node
- L689 _public prototype_ `TArray<URigVMNode*> ExpandLibraryNode(const FName& InNodeName, bool bSetupUndoRedo = true, bool bPrintPythonCommand = false);` — `UFUNCTION(BlueprintCallable, Category = RigVMController)` — Turns a library node into its contained nodes
- L693 _public prototype_ `FName PromoteCollapseNodeToFunctionReferenceNode(const FName& InNodeName, bool bSetupUndoRedo = true, bool bPrintPythonCommand = false, const FString& InExistingFunctionDefinitionPath = TEXT(""));` — `UFUNCTION(BlueprintCallable, Category = RigVMController)` — Turns a collapse node into a function node
- L697 _public prototype_ `FName PromoteFunctionReferenceNodeToCollapseNode(const FName& InNodeName, bool bSetupUndoRedo = true, bool bPrintPythonCommand = false, bool bRemoveFunctionDefinition = false);` — `UFUNCTION(BlueprintCallable, Category = RigVMController)` — Turns a collapse node into a function node
- L704 _public prototype_ `bool RemoveNode(URigVMNode* InNode, bool bSetupUndoRedo = true, bool bPrintPythonCommand = false);` — `UFUNCTION(BlueprintCallable, Category = RigVMController)` — Removes a node from the graph This causes a NodeRemoved modified event.
- L709 _public prototype_ `bool RemoveNodeByName(const FName& InNodeName, bool bSetupUndoRedo = true, bool bPrintPythonCommand = false);` — `UFUNCTION(BlueprintCallable, Category = RigVMController)` — Removes a node from the graph given the node's name. This causes a NodeRemoved modified event.
- L714 _public prototype_ `bool RemoveNodes(TArray<URigVMNode*> InNodes, bool bSetupUndoRedo = true, bool bPrintPythonCommand = false);` — `UFUNCTION(BlueprintCallable, Category = RigVMController)` — Removes a list of nodes from the graph This causes a NodeRemoved modified event.
- L719 _public prototype_ `bool RemoveNodesByName(const TArray<FName>& InNodeNames, bool bSetupUndoRedo = true, bool bPrintPythonCommand = false);` — `UFUNCTION(BlueprintCallable, Category = RigVMController)` — Removes a list of nodes from the graph given the names This causes a NodeRemoved modified event.
- L724 _public prototype_ `bool RenameNode(URigVMNode* InNode, const FName& InNewName, bool bSetupUndoRedo = true, bool bPrintPythonCommand = false);` — `UFUNCTION(BlueprintCallable, Category = RigVMController)` — Renames a node in the graph This causes a NodeRenamed modified event.
- L729 _public prototype_ `bool SelectNode(URigVMNode* InNode, bool bSelect = true, bool bSetupUndoRedo = true, bool bPrintPythonCommand = false);` — `UFUNCTION(BlueprintCallable, Category = RigVMController)` — Selects a single node in the graph. This causes a NodeSelected / NodeDeselected modified event.
- L734 _public prototype_ `bool SelectNodeByName(const FName& InNodeName, bool bSelect = true, bool bSetupUndoRedo = true);` — `UFUNCTION(BlueprintCallable, Category = RigVMController)` — Selects a single node in the graph by name. This causes a NodeSelected / NodeDeselected modified event.
- L739 _public prototype_ `bool ClearNodeSelection(bool bSetupUndoRedo = true, bool bPrintPythonCommand = false);` — `UFUNCTION(BlueprintCallable, Category = RigVMController)` — Deselects all currently selected nodes in the graph. This might cause several NodeDeselected modified event.
- L744 _public prototype_ `bool SetNodeSelection(const TArray<FName>& InNodeNames, bool bSetupUndoRedo = true, bool bPrintPythonCommand = false);` — `UFUNCTION(BlueprintCallable, Category = RigVMController)` — Selects the nodes given the selection This might cause several NodeDeselected modified event.
- L748 _public prototype_ `bool SelectLinkedNodes(const TArray<FName>& InNodeNames, bool bSelectSourceNodes, bool bClearSelection, bool bSetupUndoRedo = true, bool bPrintPythonCommand = false);` — `UFUNCTION(BlueprintCallable, Category = RigVMController)` — Selects the linked nodes given the input node names
- L752 _public prototype_ `bool SelectNodeIslands(const TArray<FName>& InNodeNames, bool bClearSelection, bool bSetupUndoRedo = true, bool bPrintPythonCommand = false);` — `UFUNCTION(BlueprintCallable, Category = RigVMController)` — Selects the node islands given the input node names
- L757 _public prototype_ `bool SetNodePosition(URigVMNode* InNode, const FVector2D& InPosition, bool bSetupUndoRedo = true, bool bMergeUndoAction = false, bool bPrintPythonCommand = false);` — `UFUNCTION(BlueprintCallable, Category = RigVMController)` — Sets the position of a node in the graph. This causes a NodePositionChanged modified event.
- L762 _public prototype_ `bool SetNodePositionByName(const FName& InNodeName, const FVector2D& InPosition, bool bSetupUndoRedo = true, bool bMergeUndoAction = false, bool bPrintPythonCommand = false);` — `UFUNCTION(BlueprintCallable, Category = RigVMController)` — Sets the position of a node in the graph by name. This causes a NodePositionChanged modified event.
- L767 _public prototype_ `bool SetNodeSize(URigVMNode* InNode, const FVector2D& InSize, bool bSetupUndoRedo = true, bool bMergeUndoAction = false, bool bPrintPythonCommand = false);` — `UFUNCTION(BlueprintCallable, Category = RigVMController)` — Sets the size of a node in the graph. This causes a NodeSizeChanged modified event.
- L772 _public prototype_ `bool SetNodeSizeByName(const FName& InNodeName, const FVector2D& InSize, bool bSetupUndoRedo = true, bool bMergeUndoAction = false, bool bPrintPythonCommand = false);` — `UFUNCTION(BlueprintCallable, Category = RigVMController)` — Sets the size of a node in the graph by name. This causes a NodeSizeChanged modified event.
- L777 _public prototype_ `bool SetNodeTitle(URigVMNode* InNode, const FString InNodeTitle, bool bSetupUndoRedo = true, bool bMergeUndoAction = false, bool bPrintPythonCommand = false);` — `UFUNCTION(BlueprintCallable, Category = RigVMController)` — Sets the raw node title of a node in the graph. Some nodes generate customs node titles that override this setting.
- L782 _public prototype_ `bool SetNodeTitleByName(const FName& InNodeName, const FString InNodeTitle, bool bSetupUndoRedo = true, bool bMergeUndoAction = false);` — `UFUNCTION(BlueprintCallable, Category = RigVMController)` — Sets the raw node title of a node in the graph. Some nodes generate customs node titles that override this setting.
- L787 _public prototype_ `bool SetNodeColor(URigVMNode* InNode, const FLinearColor& InColor, bool bSetupUndoRedo = true, bool bMergeUndoAction = false, bool bPrintPythonCommand = false);` — `UFUNCTION(BlueprintCallable, Category = RigVMController)` — Sets the color of a node in the graph. This causes a NodeColorChanged modified event.
- L792 _public prototype_ `bool SetNodeColorByName(const FName& InNodeName, const FLinearColor& InColor, bool bSetupUndoRedo = true, bool bMergeUndoAction = false);` — `UFUNCTION(BlueprintCallable, Category = RigVMController)` — Sets the color of a node in the graph by name. This causes a NodeColorChanged modified event.
- L797 _public prototype_ `bool SetNodeCategory(URigVMCollapseNode* InNode, const FString& InCategory, bool bSetupUndoRedo = true, bool bMergeUndoAction = false, bool bPrintPythonCommand = false);` — `UFUNCTION(BlueprintCallable, Category = RigVMController)` — Sets the category of a node in the graph. This causes a NodeCategoryChanged modified event.
- L802 _public prototype_ `bool SetNodeCategoryByName(const FName& InNodeName, const FString& InCategory, bool bSetupUndoRedo = true, bool bMergeUndoAction = false);` — `UFUNCTION(BlueprintCallable, Category = RigVMController)` — Sets the category of a node in the graph. This causes a NodeCategoryChanged modified event.
- L807 _public prototype_ `bool SetNodeKeywords(URigVMCollapseNode* InNode, const FString& InKeywords, bool bSetupUndoRedo = true, bool bMergeUndoAction = false, bool bPrintPythonCommand = false);` — `UFUNCTION(BlueprintCallable, Category = RigVMController)` — Sets the keywords of a node in the graph. This causes a NodeKeywordsChanged modified event.
- L812 _public prototype_ `bool SetNodeKeywordsByName(const FName& InNodeName, const FString& InKeywords, bool bSetupUndoRedo = true, bool bMergeUndoAction = false);` — `UFUNCTION(BlueprintCallable, Category = RigVMController)` — Sets the keywords of a node in the graph. This causes a NodeKeywordsChanged modified event.
- L817 _public prototype_ `bool SetNodeDescription(URigVMCollapseNode* InNode, const FString& InDescription, bool bSetupUndoRedo = true, bool bMergeUndoAction = false, bool bPrintPythonCommand = false);` — `UFUNCTION(BlueprintCallable, Category = RigVMController)` — Sets the function description of a node in the graph. This causes a NodeDescriptionChanged modified event.
- L822 _public prototype_ `bool SetNodeDescriptionByName(const FName& InNodeName, const FString& InDescription, bool bSetupUndoRedo = true, bool bMergeUndoAction = false);` — `UFUNCTION(BlueprintCallable, Category = RigVMController)` — Sets the keywords of a node in the graph. This causes a NodeDescriptionChanged modified event.
- L827 _public prototype_ `bool SetCommentText(URigVMNode* InNode, const FString& InCommentText, const int32& InCommentFontSize, const bool& bInCommentBubbleVisible, const bool& bInCommentColorBubble, bool bSetupUndoRedo = true, bool bPrintPythonCommand = false);` — `UFUNCTION(BlueprintCallable, Category = RigVMController)` — Sets the comment text and properties of a comment node in the graph. This causes a CommentTextChanged modified event.
- L832 _public prototype_ `bool SetCommentTextByName(const FName& InNodeName, const FString& InCommentText, const int32& InCommentFontSize, const bool& bInCommentBubbleVisible, const bool& bInCommentColorBubble, bool bSetupUndoRedo = true, bool bPrintPythonCommand = false);` — `UFUNCTION(BlueprintCallable, Category = RigVMController)` — Sets the comment text and properties of a comment node in the graph by name. This causes a CommentTextChanged modified event.
- L837 _public prototype_ `bool RenameVariable(const FName& InOldName, const FName& InNewName, bool bSetupUndoRedo = true);` — `UFUNCTION(BlueprintCallable, Category = RigVMController, meta=(DeprecatedFunction))` — Renames a variable in the graph. This causes a VariableRenamed modified event.
- L838 _public prototype_ `bool RenameVariable(const FGuid& InGuid, const FName& InNewName, bool bSetupUndoRedo = true);`
- L843 _public prototype_ `bool RenameParameter(const FName& InOldName, const FName& InNewName, bool bSetupUndoRedo = true);` — `UFUNCTION(BlueprintCallable, Category = RigVMController, meta=(DeprecatedFunction))` — Renames a parameter in the graph. This causes a ParameterRenamed modified event.
- L846 _public prototype_ `TArray<URigVMNode*> UpgradeNodes(const TArray<URigVMNode*>& InNodes, bool bRecursive = true, bool bSetupUndoRedo = true);` — Upgrades a set of nodes with each corresponding next known version
- L849 _public prototype_ `URigVMNode* UpgradeNode(URigVMNode* InNode, bool bSetupUndoRedo = true, FRigVMController_PinPathRemapDelegate* OutRemapPinDelegate = nullptr);` — Upgrades a single node with its next known version
- L854 _public prototype_ `bool SetPinExpansion(const FString& InPinPath, bool bIsExpanded, bool bSetupUndoRedo = true, bool bPrintPythonCommand = false);` — `UFUNCTION(BlueprintCallable, Category = RigVMController)` — Sets the pin to be expanded or not This causes a PinExpansionChanged modified event.
- L859 _public prototype_ `bool SetPinIsWatched(const FString& InPinPath, bool bIsWatched, bool bSetupUndoRedo = true);` — `UFUNCTION(BlueprintCallable, Category = RigVMController)` — Sets the pin to be watched (or not) This causes a PinWatchedChanged modified event.
- L863 _public prototype_ `bool SetPinDisplayName(const FString& InPinPath, const FString& InDisplayName, bool bSetupUndoRedo = true, bool bPrintPythonCommand = false);` — `UFUNCTION(BlueprintCallable, Category = RigVMController)` — Sets the pin display name. The display name is UI relevant only.
- L868 _public prototype_ `bool AddEmptyPinCategory(const FName& InNodeName, const FString& InCategory, bool bSetupUndoRedo = true, bool bPrintPythonCommand = false);` — `UFUNCTION(BlueprintCallable, Category = RigVMController)` — Adds a new pin category. The category is UI relevant only and used to order pins in the user interface of the node as well as on the details panel.
- L873 _public prototype_ `bool SetPinCategory(const FString& InPinPath, const FString& InCategory, bool bSetupUndoRedo = true, bool bPrintPythonCommand = false);` — `UFUNCTION(BlueprintCallable, Category = RigVMController)` — Sets the pin category. The category is UI relevant only and used to order pins in the user interface of the node as well as on the details panel.
- L878 _public prototype_ `bool ClearPinCategory(const FString& InPinPath, bool bSetupUndoRedo = true, bool bPrintPythonCommand = false);` — `UFUNCTION(BlueprintCallable, Category = RigVMController)` — Clears the pin category. The category is UI relevant only and used to order pins in the user interface of the node as well as on the details panel.
- L883 _public prototype_ `bool RemovePinCategory(const FName& InNodeName, const FString& InPinCategory, bool bSetupUndoRedo = true, bool bPrintPythonCommand = false);` — `UFUNCTION(BlueprintCallable, Category = RigVMController)` — Removes a pin category. The category is UI relevant only and used to order pins in the user interface of the node as well as on the details panel.
- L888 _public prototype_ `bool RenamePinCategory(const FName& InNodeName, const FString& InOldPinCategory, const FString& InNewPinCategory, bool bSetupUndoRedo = true, bool bPrintPythonCommand = false);` — `UFUNCTION(BlueprintCallable, Category = RigVMController)` — Renames a pin category. The category is UI relevant only and used to order pins in the user interface of the node as well as on the details panel.
- L893 _public prototype_ `bool SetPinCategoryIndex(const FName& InNodeName, const FString& InPinCategory, int32 InNewIndex, bool bSetupUndoRedo = true, bool bPrintPythonCommand = false);` — `UFUNCTION(BlueprintCallable, Category = RigVMController)` — Changes a pin category's index. The category is UI relevant only and used to order pins in the user interface of the node as well as on the details panel.
- L898 _public prototype_ `bool SetPinCategoryExpansion(const FName& InNodeName, const FString& InPinCategory, bool bIsExpanded, bool bSetupUndoRedo = true, bool bPrintPythonCommand = false);` — `UFUNCTION(BlueprintCallable, Category = RigVMController)` — Changes a pin category's expansion state. The category is UI relevant only and used to order pins in the user interface of the node as well as on the details panel.
- L903 _public prototype_ `bool SetPinIndexInCategory(const FString& InPinPath, int32 InIndexInCategory, bool bSetupUndoRedo = true, bool bPrintPythonCommand = false);` — `UFUNCTION(BlueprintCallable, Category = RigVMController)` — Changes a pin category's expansion state. The category is UI relevant only and used to order pins in the user interface of the node as well as on the details panel.
- L907 _public prototype_ `bool SetNodeLayout(const FName& InNodeName, FRigVMNodeLayout InLayout, bool bSetupUndoRedo = true, bool bPrintPythonCommand = false);` — `UFUNCTION(BlueprintCallable, Category = RigVMController)` — Applies a complete node layout to a node
- L911 _public prototype_ `bool ClearNodeLayout(const FName& InNodeName, bool bSetupUndoRedo = true, bool bPrintPythonCommand = false);` — `UFUNCTION(BlueprintCallable, Category = RigVMController)` — Removes any layout information from a node
- L915 _public prototype_ `FString GetPinDefaultValue(const FString& InPinPath);` — `UFUNCTION(BlueprintCallable, Category = RigVMController)` — Returns the default value of a pin given its pinpath.
- L920 _public prototype_ `bool SetPinDefaultValue(const FString& InPinPath, const FString& InDefaultValue, bool bResizeArrays = true, bool bSetupUndoRedo = true, bool bMergeUndoAction = false, bool bPrintPythonCommand = false, bool bSetValueOnLinkedPins = true);` — `UFUNCTION(BlueprintCallable, Category = RigVMController)` — Sets the default value of a pin given its pinpath. This causes a PinDefaultValueChanged modified event.
- L921 _public prototype_ `bool SetPinDefaultValue(URigVMPin* InPin, const FString& InDefaultValue, bool bResizeArrays, bool bSetupUndoRedo, bool bMergeUndoAction, bool bSetValueOnLinkedPins = true);`
- L926 _public prototype_ `bool ResetPinDefaultValue(const FString& InPinPath, bool bSetupUndoRedo = true, bool bPrintPythonCommand = false);` — `UFUNCTION(BlueprintCallable, Category = RigVMController)` — Resets the default value of a pin given its pinpath. This causes a PinDefaultValueChanged modified event.
- L930 _public prototype_ `bool ResetDefaultValueForPins(const TArray<FString>& InPinPaths, bool bSetupUndo = true, bool bPrintPythonCommand = false);` — `UFUNCTION(BlueprintCallable, Category = RigVMController)` — Resets the default value of a list of pin given the pinpaths.
- L934 _public prototype_ `bool ResetDefaultValueForAllPinsOnNode(const FName& InNodeName, bool bSetupUndo = true, bool bPrintPythonCommand = false);` — `UFUNCTION(BlueprintCallable, Category = RigVMController)` — Resets the default value of all pins of a given node
- L938 _public prototype_ `bool ResetDefaultValueForAllPinsOnNodes(const TArray<FName>& InNodeNames, bool bSetupUndo = true, bool bPrintPythonCommand = false);` — `UFUNCTION(BlueprintCallable, Category = RigVMController)` — Resets the default value of all pins of a list of nodes
- L942 _public prototype_ `bool AddOverrideToPin(const FString& InPinPath, bool bSetupUndo = true, bool bPrintPythonCommand = false);` — `UFUNCTION(BlueprintCallable, Category = RigVMController)` — Adds an override to the given pin path
- L946 _public prototype_ `bool AddOverrideToPins(const TArray<FString>& InPinPaths, bool bSetupUndo = true, bool bPrintPythonCommand = false);` — `UFUNCTION(BlueprintCallable, Category = RigVMController)` — Adds an override to a given list of pin paths
- L950 _public prototype_ `bool AddOverrideToAllPinsOnNode(const FName& InNodeName, bool bSetupUndo = true, bool bPrintPythonCommand = false);` — `UFUNCTION(BlueprintCallable, Category = RigVMController)` — Adds an override to all pins on a node
- L954 _public prototype_ `bool AddOverrideToAllPinsOnNodes(const TArray<FName>& InNodeNames, bool bSetupUndo = true, bool bPrintPythonCommand = false);` — `UFUNCTION(BlueprintCallable, Category = RigVMController)` — Adds an override to all pins on a list of nodes
- L958 _public prototype_ `bool ClearOverrideOnPin(const FString& InPinPath, bool bSetupUndo = true, bool bPrintPythonCommand = false);` — `UFUNCTION(BlueprintCallable, Category = RigVMController)` — Clears an override on a given pin path
- L962 _public prototype_ `bool ClearOverrideOnPins(const TArray<FString>& InPinPaths, bool bSetupUndo = true, bool bPrintPythonCommand = false);` — `UFUNCTION(BlueprintCallable, Category = RigVMController)` — Clears the overrides on a given list of pin paths
- L966 _public prototype_ `bool ClearOverrideOnAllPinsOnNode(const FName& InNodeName, bool bSetupUndo = true, bool bPrintPythonCommand = false);` — `UFUNCTION(BlueprintCallable, Category = RigVMController)` — Clears the overrides for all pins on a node
- L970 _public prototype_ `bool ClearOverrideOnAllPinsOnNodes(const TArray<FName>& InNodeNames, bool bSetupUndo = true, bool bPrintPythonCommand = false);` — `UFUNCTION(BlueprintCallable, Category = RigVMController)` — Clears the overrides for all pins of a list of nodes
- L973 _public prototype_ `FString AddAggregatePin(const FString& InNodeName, const FString& InPinName, const FString& InDefaultValue = TEXT(""), bool bSetupUndoRedo = true, bool bPrintPythonCommand = false);` — `UFUNCTION(BlueprintCallable, Category = RigVMController)`
- L976 _public prototype_ `bool RemoveAggregatePin(const FString& InPinPath, bool bSetupUndoRedo = true, bool bPrintPythonCommand = false);` — `UFUNCTION(BlueprintCallable, Category = RigVMController)`
- L979 _public prototype_ `FString AddAggregatePin(URigVMNode* InNode, const FString& InPinName, const FString& InDefaultValue = TEXT(""), bool bSetupUndoRedo = true, bool bPrintPythonCommand = false);`
- L980 _public prototype_ `bool RemoveAggregatePin(URigVMPin* InPin, bool bSetupUndoRedo = true, bool bPrintPythonCommand = false);`
- L986 _public prototype_ `FString AddArrayPin(const FString& InArrayPinPath, const FString& InDefaultValue = TEXT(""), bool bSetupUndoRedo = true, bool bPrintPythonCommand = false);` — `UFUNCTION(BlueprintCallable, Category = RigVMController)` — Adds an array element pin to the end of an array pin. This causes a PinArraySizeChanged modified event.
- L991 _public prototype_ `FString DuplicateArrayPin(const FString& InArrayElementPinPath, bool bSetupUndoRedo = true, bool bPrintPythonCommand = false);` — `UFUNCTION(BlueprintCallable, Category = RigVMController)` — Duplicates an array element pin. This causes a PinArraySizeChanged modified event.
- L996 _public prototype_ `FString InsertArrayPin(const FString& InArrayPinPath, int32 InIndex = -1, const FString& InDefaultValue = TEXT(""), bool bSetupUndoRedo = true, bool bPrintPythonCommand = false);` — `UFUNCTION(BlueprintCallable, Category = RigVMController)` — Inserts an array element pin into an array pin. This causes a PinArraySizeChanged modified event.
- L1001 _public prototype_ `bool RemoveArrayPin(const FString& InArrayElementPinPath, bool bSetupUndoRedo = true, bool bPrintPythonCommand = false);` — `UFUNCTION(BlueprintCallable, Category = RigVMController)` — Removes an array element pin from an array pin. This causes a PinArraySizeChanged modified event.
- L1006 _public prototype_ `bool ClearArrayPin(const FString& InArrayPinPath, bool bSetupUndoRedo = true, bool bPrintPythonCommand = false);` — `UFUNCTION(BlueprintCallable, Category = RigVMController)` — Removes all (but one) array element pin from an array pin. This causes a PinArraySizeChanged modified event.
- L1011 _public prototype_ `bool SetArrayPinSize(const FString& InArrayPinPath, int32 InSize, const FString& InDefaultValue = TEXT(""), bool bSetupUndoRedo = true, bool bPrintPythonCommand = false);` — `UFUNCTION(BlueprintCallable, Category = RigVMController)` — Sets the size of the array pin This causes a PinArraySizeChanged modified event.
- L1016 _public prototype_ `bool BindPinToVariable(const FString& InPinPath, const FString& InNewBoundVariablePath, bool bSetupUndoRedo = true, bool bPrintPythonCommand = false);` — `UFUNCTION(BlueprintCallable, Category = RigVMController)` — Binds a pin to a variable (or removes the binding given NAME_None) This causes a PinBoundVariableChanged modified event.
- L1021 _public prototype_ `bool UnbindPinFromVariable(const FString& InPinPath, bool bSetupUndoRedo = true, bool bPrintPythonCommand = false);` — `UFUNCTION(BlueprintCallable, Category = RigVMController)` — Removes the binging of a pin to a variable This causes a PinBoundVariableChanged modified event.
- L1025 _public prototype_ `bool MakeBindingsFromVariableNode(const FName& InNodeName, bool bSetupUndoRedo = true, bool bPrintPythonCommand = false);` — `UFUNCTION(BlueprintCallable, Category = RigVMController)` — Turns a variable node into one or more bindings
- L1029 _public prototype_ `bool MakeVariableNodeFromBinding(const FString& InPinPath, const FVector2D& InNodePosition = FVector2D::ZeroVector, bool bSetupUndoRedo = true, bool bPrintPythonCommand = false);` — `UFUNCTION(BlueprintCallable, Category = RigVMController)` — Turns a binding to a variable node
- L1033 _public prototype_ `bool PromotePinToVariable(const FString& InPinPath, bool bCreateVariableNode, const FVector2D& InNodePosition = FVector2D::ZeroVector, bool bSetupUndoRedo = true, bool bPrintPythonCommand = false);` — `UFUNCTION(BlueprintCallable, Category = RigVMController)` — Promotes a pin to a variable
- L1037 _public prototype_ `bool PromotePinToLocalVariable(const FString& InPinPath, bool bCreateVariableNode, const FVector2D& InNodePosition = FVector2D::ZeroVector, bool bSetupUndoRedo = true, bool bPrintPythonCommand = false);` — `UFUNCTION(BlueprintCallable, Category = RigVMController)` — Promotes a pin to a local variable
- L1042 _public prototype_ `bool AddLink(const FString& InOutputPinPath, const FString& InInputPinPath, bool bSetupUndoRedo = true, bool bPrintPythonCommand = false, ERigVMPinDirection InUserDirection = ERigVMPinDirection::Output, bool bCreateCastNode = false);` — `UFUNCTION(BlueprintCallable, Category = RigVMController)` — Adds a link to the graph. This causes a LinkAdded modified event.
- L1047 _public prototype_ `bool BreakLink(const FString& InOutputPinPath, const FString& InInputPinPath, bool bSetupUndoRedo = true, bool bPrintPythonCommand = false);` — `UFUNCTION(BlueprintCallable, Category = RigVMController)` — Removes a link from the graph. This causes a LinkRemoved modified event.
- L1052 _public prototype_ `bool BreakAllLinks(const FString& InPinPath, bool bAsInput = true, bool bSetupUndoRedo = true, bool bPrintPythonCommand = false);` — `UFUNCTION(BlueprintCallable, Category = RigVMController)` — Removes all links on a given pin from the graph. This might cause multiple LinkRemoved modified event.
- L1056 _public prototype_ `FName AddExposedPin(const FName& InPinName, ERigVMPinDirection InDirection, const FString& InCPPType, const FName& InCPPTypeObjectPath, const FString& InDefaultValue, bool bSetupUndoRedo = true, bool bPrintPythonCommand = false, bool bIsInputVariable = false);` — `UFUNCTION(BlueprintCallable, Category = RigVMController)` — Adds an exposed pin to the graph controlled by this
- L1060 _public prototype_ `bool RemoveExposedPin(const FName& InPinName, bool bSetupUndoRedo = true, bool bPrintPythonCommand = false);` — `UFUNCTION(BlueprintCallable, Category = RigVMController)` — Removes an exposed pin from the graph controlled by this
- L1064 _public prototype_ `bool RenameExposedPin(const FName& InOldPinName, const FName& InNewPinName, bool bSetupUndoRedo = true, bool bPrintPythonCommand = false);` — `UFUNCTION(BlueprintCallable, Category = RigVMController)` — Renames an exposed pin in the graph controlled by this
- L1068 _public prototype_ `bool ChangeExposedPinType(const FName& InPinName, const FString& InCPPType, const FName& InCPPTypeObjectPath, UPARAM(ref) bool& bSetupUndoRedo, bool bSetupOrphanPins = true, bool bPrintPythonCommand = false);` — `UFUNCTION(BlueprintCallable, Category = RigVMController)` — Changes the type of an exposed pin in the graph controlled by this
- L1072 _public prototype_ `bool SetExposedPinIndex(const FName& InPinName, int32 InNewIndex, bool bSetupUndoRedo = true, bool bPrintPythonCommand = false);` — `UFUNCTION(BlueprintCallable, Category = RigVMController)` — Sets the index for an exposed pin. This can be used to move the pin up and down on the node.
- L1076 _public prototype_ `bool MarkExposedPinAsInputVariable(const FName& InPinName, bool bDefinedAsExternalVariable, bool bSetupUndoRedo = true, bool bPrintPythonCommand = false);` — `UFUNCTION(BlueprintCallable, Category = RigVMController)` — Marks an exposed pin as defined as an input variable
- L1079 _public prototype_ `FRigVMGraphFunctionHeader FindGraphFunctionHeaderByName(FString InHostPath, FName InFunctionName) const;` — `UFUNCTION(BlueprintPure, Category = RigVMController)`
- L1082 _public prototype_ `FRigVMGraphFunctionHeader FindGraphFunctionHeader(FRigVMGraphFunctionIdentifier InFunctionIdentifier) const;` — `UFUNCTION(BlueprintPure, Category = RigVMController)`
- L1085 _public prototype_ `FRigVMGraphFunctionIdentifier FindGraphFunctionIdentifier(FString InHostPath, FName InFunctionName) const;` — `UFUNCTION(BlueprintPure, Category = RigVMController)`
- L1089 _public prototype_ `URigVMFunctionReferenceNode* AddFunctionReferenceNodeFromDescription(const FRigVMGraphFunctionHeader& InFunctionDefinition, const FVector2D& InNodePosition = FVector2D::ZeroVector, const FString& InNodeName = TEXT(""), bool bSetupUndoRedo = true, bool bPrintPythonCommand = false);` — `UFUNCTION(BlueprintCallable, Category = RigVMController)` — Adds a function reference / invocation to the graph
- L1092 _public prototype_ `URigVMFunctionReferenceNode* AddExternalFunctionReferenceNode(const FString& InHostPath, const FName& InFunctionName, const FVector2D& InNodePosition = FVector2D::ZeroVector, const FString& InNodeName = TEXT(""), bool bSetupUndoRedo = true, bool bPrintPythonCommand = false);` — `UFUNCTION(BlueprintCallable, Category = RigVMController)`
- L1095 _public prototype_ `URigVMFunctionReferenceNode* AddFunctionReferenceNode(URigVMLibraryNode* InFunctionDefinition, const FVector2D& InNodePosition = FVector2D::ZeroVector, const FString& InNodeName = TEXT(""), bool bSetupUndoRedo = true, bool bPrintPythonCommand = false);` — `UFUNCTION(BlueprintCallable, Category = RigVMController)`
- L1098 _public prototype_ `bool SwapFunctionReferenceByName(const FName& InFunctionReferenceNodeName, const FRigVMGraphFunctionIdentifier& InNewFunctionIdentifier, bool bSetupOrphanPins, bool bSetupUndoRedo = true, bool bPrintPythonCommand = false);` — `UFUNCTION(BlueprintCallable, Category = RigVMController)`
- L1101 _public prototype_ `bool SwapFunctionReference(URigVMFunctionReferenceNode* InFunctionReferenceNode, const FRigVMGraphFunctionIdentifier& InNewFunctionIdentifier, bool bSetupOrphanPins, bool bSetupUndoRedo = true, bool bPrintPythonCommand = false);` — `UFUNCTION(BlueprintCallable, Category = RigVMController)`
- L1104 _public prototype_ `bool SwapAllFunctionReferences(const FRigVMGraphFunctionIdentifier& InOldFunctionIdentifier, const FRigVMGraphFunctionIdentifier& InNewFunctionIdentifier, bool bSetupOrphanPins, bool bSetupUndoRedo = true, bool bPrintPythonCommand = false);` — `UFUNCTION(BlueprintCallable, Category = RigVMController)`
- L1109 _public prototype_ `bool SetRemappedVariable(URigVMFunctionReferenceNode* InFunctionRefNode, const FName& InInnerVariableName, const FName& InOuterVariableName, bool bSetupUndoRedo = true);` — `UE_DEPRECATED(5.8, "Please use BindPinToVariable instead.")` — `UFUNCTION(BlueprintCallable, Category = RigVMController, meta=(DeprecatedFunction, DeprecationMessage="Function has been deprecated, please use BindPinToVariable instead."))` — Sets the remapped variable on a function reference node
- L1113 _public prototype_ `URigVMLibraryNode* AddFunctionToLibrary(const FName& InFunctionName, bool bMutable, const FVector2D& InNodePosition = FVector2D::ZeroVector, bool bSetupUndoRedo = true, bool bPrintPythonCommand = false);` — `UFUNCTION(BlueprintCallable, Category = RigVMController)` — Adds a function definition to a function library graph
- L1117 _public prototype_ `bool RemoveFunctionFromLibrary(const FName& InFunctionName, bool bSetupUndoRedo = true, bool bPrintPythonCommand = false);` — `UFUNCTION(BlueprintCallable, Category = RigVMController)` — Removes a function from a function library graph
- L1121 _public prototype_ `bool RenameFunction(const FName& InOldFunctionName, const FName& InNewFunctionName, bool bSetupUndoRedo = true, bool bPrintPythonCommand = false);` — `UFUNCTION(BlueprintCallable, Category = RigVMController)` — Renames a function in the function library
- L1125 _public prototype_ `bool MarkFunctionAsPublic(const FName& InFunctionName, bool bInIsPublic, bool bSetupUndoRedo = true, bool bPrintPythonCommand = false);` — `UFUNCTION(BlueprintCallable, Category = RigVMController)` — Mark a function as public/private in the function library
- L1129 _public prototype_ `bool IsFunctionPublic(const FName& InFunctionName);` — `UFUNCTION(BlueprintCallable, Category = RigVMController)` — Returns true if a function is marked as public in the function library
- L1135 _public prototype_ `bool SetFunctionIsPure(const FName& InFunctionName, bool bIsPure, bool bSetupUndoRedo = true, bool bPrintPythonCommand = false);` — `UFUNCTION(BlueprintCallable, Category = RigVMController)` — Sets whether a function is pure (no execute pins) or mutable (has execute pins). Call this on the function library controller. Returns true if the function's purity was successfully changed.
- L1139 _public prototype_ `URigVMLibraryNode* CreateFunctionVariant(const FName& InFunctionName, const FName& InVariantName = NAME_None, bool bSetupUndoRedo = true, bool bPrintPythonCommand = false);` — `UFUNCTION(BlueprintCallable, Category = RigVMController)` — Creates a variant of a function given the name of an existing function variant
- L1143 _public prototype_ `bool AddDefaultTagToFunctionVariant(const FName& InFunctionName, const FName& InTagName, bool bSetupUndoRedo = true, bool bPrintPythonCommand = false);` — `UFUNCTION(BlueprintCallable, Category = RigVMController)` — Adds a default tag to a function variant
- L1147 _public prototype_ `bool AddTagToFunctionVariant(const FName& InFunctionName, const FRigVMTag& InTag, bool bSetupUndoRedo = true, bool bPrintPythonCommand = false);` — `UFUNCTION(BlueprintCallable, Category = RigVMController)` — Adds a tag to a function variant
- L1151 _public prototype_ `bool RemoveTagFromFunctionVariant(const FName& InFunctionName, const FName& InTagName, bool bSetupUndoRedo = true, bool bPrintPythonCommand = false);` — `UFUNCTION(BlueprintCallable, Category = RigVMController)` — Adds a tag to a function variant
- L1155 _public prototype_ `TArray<FRigVMVariantRef> FindVariantsOfFunction(const FName& InFunctionName);` — `UFUNCTION(BlueprintCallable, Category = RigVMController)` — Returns all variant refs related to the given function
- L1159 _public prototype_ `bool SplitFunctionVariant(const FName& InFunctionName, bool bSetupUndoRedo = true, bool bPrintPythonCommand = false);` — `UFUNCTION(BlueprintCallable, Category = RigVMController)` — Resets the function's guid to a new one and splits it from the former variant set
- L1163 _public prototype_ `bool JoinFunctionVariant(const FName& InFunctionName, const FGuid& InGuid, bool bSetupUndoRedo = true, bool bPrintPythonCommand = false);` — `UFUNCTION(BlueprintCallable, Category = RigVMController)` — Merges the function's guid with a provided one to join the variant set
- L1167 _public prototype_ `FRigVMGraphVariableDescription AddLocalVariable(const FName& InVariableName, const FString& InCPPType, UObject* InCPPTypeObject, const FString& InDefaultValue, bool bSetupUndoRedo = true, bool bPrintPythonCommand = false);` — `UFUNCTION(BlueprintCallable, Category = RigVMController)` — Add a local variable to the graph
- L1171 _public prototype_ `FRigVMGraphVariableDescription AddLocalVariableFromObjectPath(const FName& InVariableName, const FString& InCPPType, const FString& InCPPTypeObjectPath, const FString& InDefaultValue, bool bSetupUndoRedo = true);` — `UFUNCTION(BlueprintCallable, Category = RigVMController)` — Add a local variable to the graph given a struct object path name.
- L1175 _public prototype_ `bool RemoveLocalVariable(const FName& InVariableName, bool bSetupUndoRedo = true, bool bPrintPythonCommand = false);` — `UFUNCTION(BlueprintCallable, Category = RigVMController)` — Remove a local variable from the graph
- L1179 _public prototype_ `bool RenameLocalVariable(const FName& InVariableName, const FName& InNewVariableName, bool bSetupUndoRedo = true, bool bPrintPythonCommand = false);` — `UFUNCTION(BlueprintCallable, Category = RigVMController)` — Rename a local variable from the graph
- L1183 _public prototype_ `bool SetLocalVariableType(const FName& InVariableName, const FString& InCPPType, UObject* InCPPTypeObject, bool bSetupUndoRedo = true, bool bPrintPythonCommand = false);` — `UFUNCTION(BlueprintCallable, Category = RigVMController)` — Sets the type of the local variable
- L1185 _public prototype_ `bool SetLocalVariableTypeFromObjectPath(const FName& InVariableName, const FString& InCPPType, const FString& InCPPTypeObjectPath, bool bSetupUndoRedo = true, bool bPrintPythonCommand = false);` — `UFUNCTION(BlueprintCallable, Category = RigVMController)`
- L1188 _public prototype_ `bool SetLocalVariableDefaultValue(const FName& InVariableName, const FString& InDefaultValue, bool bSetupUndoRedo = true, bool bPrintPythonCommand = false);` — `UFUNCTION(BlueprintCallable, Category = RigVMController)`
- L1192 _public prototype_ `bool SetLocalVariableIndex(const FName& InVariableName, int32 InNewIndex, bool bSetupUndoRedo = true, bool bPrintPythonCommand = false);` — `UFUNCTION(BlueprintCallable, Category = RigVMController)` — Reorder a local variable to a new index (UFUNCTION wrapper - converts name to GUID)
- L1195 _public prototype_ `bool SetLocalVariableIndex(const FGuid& InVariableGuid, int32 InNewIndex, bool bSetupUndoRedo = true, bool bPrintPythonCommand = false);` — Reorder a local variable to a new index (primary GUID-based implementation)
- L1199 _public prototype_ `URigVMUserWorkflowOptions* MakeOptionsForWorkflow(UObject* InSubject, const FRigVMUserWorkflow& InWorkflow);` — `UFUNCTION(BlueprintCallable, Category = RigVMController)` — creates the options struct for a given workflow
- L1203 _public prototype_ `bool PerformUserWorkflow(const FRigVMUserWorkflow& InWorkflow, const URigVMUserWorkflowOptions* InOptions, bool bSetupUndoRedo = true);` — `UFUNCTION(BlueprintCallable, Category = RigVMController)` — performs all actions representing the workflow
- L1206 _public prototype_ `TArray<TSoftObjectPtr<URigVMFunctionReferenceNode>> GetAffectedReferences(ERigVMControllerBulkEditType InEditType, bool bForceLoad = false);` — Determine affected function references for a potential bulk edit on a library node
- L1209 _public prototype_ `TArray<FAssetData> GetAffectedAssets(ERigVMControllerBulkEditType InEditType, bool bForceLoad = false);` — Determine affected assets for a potential bulk edit on a library node
- L1212 _public member_ `FRigVMController_GetExternalVariablesDelegate GetExternalVariablesDelegate;` — A delegate to retrieve the list of external variables
- L1215 _public member_ `FRigVMController_GetByteCodeDelegate GetCurrentByteCodeDelegate;` — A delegate to retrieve the current bytecode of the graph
- L1218 _public member_ `FRigVMController_RequestLocalizeFunctionDelegate RequestLocalizeFunctionDelegate;` — A delegate to localize a function on demand
- L1221 _public member_ `FRigVMController_RequestNewExternalVariableDelegate RequestNewExternalVariableDelegate;` — A delegate to create a new blueprint member variable
- L1224 _public member_ `FRigVMController_RequestBulkEditDialogDelegate RequestBulkEditDialogDelegate;` — A delegate to ask the host / client for a dialog to confirm a bulk edit
- L1227 _public member_ `FRigVMController_RequestBreakLinksDialogDelegate RequestBreakLinksDialogDelegate;` — A delegate to ask the host / client for a dialog to confirm a bulk edit
- L1230 _public member_ `FRigVMController_RequestPinTypeSelectionDelegate RequestPinTypeSelectionDelegate;` — A delegate to ask the host / client for a dialog to select a pin type
- L1233 _public member_ `FRigVMController_OnBulkEditProgressDelegate OnBulkEditProgressDelegate;` — A delegate to inform the host / client about the progress during a bulk edit
- L1236 _public member_ `FRigVMController_RequestJumpToHyperlinkDelegate RequestJumpToHyperlinkDelegate;` — A delegate to request the client to follow a hyper link
- L1239 _public member_ `FRigVMController_ConfigureWorkflowOptionsDelegate ConfigureWorkflowOptionsDelegate;` — A delegate to request to configure an options instance for a node workflow
- L1241 _public prototype_ `void AddPinRedirector(bool bInput, bool bOutput, const FString& OldPinPath, const FString& NewPinPath);`
- L1242 _public prototype_ `void ClearPinRedirectors();`
- L1245 _public prototype_ `void RemoveStaleNodes();` — Removes nodes which went stale.
- L1248 _public prototype_ `bool ShouldRedirectPin(UScriptStruct* InOwningStruct, const FString& InOldRelativePinPath, FString& InOutNewRelativePinPath) const;`
- L1249 _public prototype_ `bool ShouldRedirectPin(const FString& InOldPinPath, FString& InOutNewPinPath) const;`
- L1275 _public prototype_ `void GenerateRepopulatePinsNodeData(TArray<FRepopulatePinsNodeData>& NodesPinData, URigVMNode* InNode, bool bInFollowCoreRedirectors = true, bool bInSetupOrphanedPins = false, bool bInRecreateLinks = false, bool bInRecurseIntoCollapseNodes = true);` — bInRecurseIntoCollapseNodes: when true (default), if InNode is a collapse node the function recurses into its contained graph and resolves a controller for that sub-graph via GetControllerForGraph. Once the recursion starts, all nested collapse nodes are walked (the flag is not propagated as a per-level switch — it gates the top-level entry only). Callers that only need the node's own pin info should pass false to avoid the recursion (and the side-effect of creating a cached sub-graph controller in FRigVMClient::Controllers).
- L1276 _public prototype_ `void OrphanPins(const TArray<FRepopulatePinsNodeData>& NodesPinData);`
- L1277 _public prototype_ `void RepopulatePins(const TArray<FRepopulatePinsNodeData>& NodesPinData);`
- L1278 _public prototype_ `bool CorrectExecutePinsOnNode(URigVMNode* InOutNode);`
- L1280 _public prototype_ `void RepopulatePinsOnNode(URigVMNode* InNode, bool bFollowCoreRedirectors = true, bool bSetupOrphanedPins = false, bool bRecreateLinks = false);`
- L1281 _public prototype_ `bool GenerateNewPinInfos(const FRigVMRegistry& Registry, URigVMNode* InNode, const FRigVMPinInfoArray& PreviousPinInfos, FRigVMPinInfoArray& NewPinInfos, const bool bSetupOrphanPinsForThisNode);`
- L1282 _public prototype_ `void GenerateRepopulatePinLists(const FRigVMRegistry& Registry, FRepopulatePinsNodeData& NodeData);`
- L1283 _public prototype_ `void RepopulatePinsOnNode(const FRigVMRegistry& Registry, const FRepopulatePinsNodeData& NodeData);`
- L1284 _public prototype_ `void RemovePinsDuringRepopulate(URigVMNode* InNode, TArray<URigVMPin*>& InPins, bool bSetupOrphanedPins);`
- L1288 _public prototype_ `bool RemoveUnusedOrphanedPins(URigVMNode* InNode, bool bRelayLinks = false);` — removes any orphan pins that no longer holds a link @param bRelayLinks If true we'll try to relay the links back to their original pins
- L1291 _public prototype_ `bool PrepareToLink(URigVMPin* FirstToResolve, URigVMPin* SecondToResolve, bool bSetupUndoRedo);` — Update filtered permutations, and propagate both ways of the link before adding this link
- L1295 _public prototype_ `bool FullyResolveTemplateNode(URigVMTemplateNode* InNode, int32 InPermutationIndex, bool bSetupUndoRedo);`
- L1297 _public function_ `FRigVMUnitNodeCreatedContext& GetUnitNodeCreatedContext()`
- L1301 _public prototype_ `void SetupDefaultUnitNodeDelegates(TDelegate<FName(FRigVMExternalVariable, FString)> InCreateExternalVariableDelegate);` — Wires the unit node delegates to the default controller delegates. this is used only within the RigVM Editor currently.
- L1302 _public prototype_ `void ResetUnitNodeDelegates();`
- L1305 _public member_ `bool bValidatePinDefaults;` — A flag that can be used to turn off pin default value validation if necessary
- L1307 _public prototype_ `const FRigVMByteCode* GetCurrentByteCode() const;`
- L1309 _public prototype_ `void ReportInfo(const FString& InMessage) const;`
- L1310 _public prototype_ `void ReportWarning(const FString& InMessage) const;`
- L1311 _public prototype_ `void ReportError(const FString& InMessage) const;`
- L1312 _public prototype_ `void ReportAndNotifyInfo(const FString& InMessage) const;`
- L1313 _public prototype_ `void ReportAndNotifyWarning(const FString& InMessage) const;`
- L1314 _public prototype_ `void ReportAndNotifyError(const FString& InMessage) const;`
- L1315 _public prototype_ `void ReportPinTypeChange(URigVMPin* InPin, const FString& InNewCPPType);`
- L1316 _public prototype_ `void SendUserFacingNotification(const FString& InMessage, float InDuration = 0.f, const UObject* InSubject = nullptr, const FName& InBrushName = TEXT("MessageLog`
- L1317 _public prototype_ `void RequestJumpToHyperLink(const URigVMNode* InSubject);`
- L1320 _public function_ `template <typename... Types> void ReportInfof(UE::Core::TCheckedFormatString<FString::FmtCharType, Types...> Fmt, Types... Args) const`
- L1326 _public function_ `template <typename... Types> void ReportWarningf(UE::Core::TCheckedFormatString<FString::FmtCharType, Types...> Fmt, Types... Args) const`
- L1332 _public function_ `template <typename... Types> void ReportErrorf(UE::Core::TCheckedFormatString<FString::FmtCharType, Types...> Fmt, Types... Args) const`
- L1338 _public function_ `template <typename... Types> void ReportAndNotifyInfof(UE::Core::TCheckedFormatString<FString::FmtCharType, Types...> Fmt, Types... Args) const`
- L1344 _public function_ `template <typename... Types> void ReportAndNotifyWarningf(UE::Core::TCheckedFormatString<FString::FmtCharType, Types...> Fmt, Types... Args) const`
- L1350 _public function_ `template <typename... Types> void ReportAndNotifyErrorf(UE::Core::TCheckedFormatString<FString::FmtCharType, Types...> Fmt, Types... Args) const`
- L1359 _public prototype_ `void SetIsRunningUnitTest(bool bIsRunning);` — `UFUNCTION(BlueprintCallable, Category = RigVMController)` — Helper function to disable a series of checks that can be ignored during a unit test
- L1363 _private prototype_ `FName AddExposedPin_Internal(const FName& InPinName, ERigVMPinDirection InDirection, const FString& InCPPType, const FName& InCPPTypeObjectPath, const FString& InDefaultValue, bool bSetupUndoRedo, bool bPrintPythonCommand, bool bIsInputVariable, bool bAllowExecutePinManagement);`
- L1364 _private prototype_ `bool RemoveExposedPin_Internal(const FName& InPinName, bool bSetupUndoRedo, bool bPrintPythonCommand, bool bAllowExecutePinManagement);`
- L1365 _private prototype_ `bool ChangeExposedPinType_Internal(const FName& InPinName, const FString& InCPPType, const FName& InCPPTypeObjectPath, bool& bSetupUndoRedo, bool bSetupOrphanPins, bool bPrintPythonCommand, bool bAllowExecutePinManagement);`
- L1368 _private member_ `FRigVMGraphModifiedDynamicEvent ModifiedEventDynamic;` — `UPROPERTY(BlueprintReadOnly, Category = RigVMController, meta = (ScriptName = "ModifiedEvent", AllowPrivateAccess = "true"))`
- L1370 _private member_ `FRigVMGraphModifiedEvent ModifiedEventStatic;`
- L1371 _private prototype_ `void HandleModifiedEvent(ERigVMGraphNotifType InNotifType, URigVMGraph* InGraph, UObject* InSubject);`
- L1373 _private prototype_ `bool IsValidNodeForGraph(const URigVMNode* InNode);`
- L1374 _private prototype_ `bool IsValidPinForGraph(const URigVMPin* InPin);`
- L1375 _private prototype_ `bool IsValidLinkForGraph(const URigVMLink* InLink);`
- L1376 _private prototype_ `void AddPinsForStruct(UStruct* InStruct, URigVMNode* InNode, URigVMPin* InParentPin, ERigVMPinDirection InPinDirection, const FString& InDefaultValue, bool bAutoExpandArrays, const FRigVMPinInfoArray* PreviousPins = nullptr);`
- L1377 _private prototype_ `void AddPinsForArray(FArrayProperty* InArrayProperty, URigVMNode* InNode, URigVMPin* InParentPin, ERigVMPinDirection InPinDirection, const TArray<FString>& InDefaultValues, bool bAutoExpandArrays);`
- L1378 _private prototype_ `void AddPinsForTemplate(const FRigVMTemplate* InTemplate, const FRigVMTemplateTypeMap& InPinTypeMap, URigVMNode* InNode);`
- L1379 _private prototype_ `void ConfigurePinFromProperty(FProperty* InProperty, URigVMPin* InOutPin, ERigVMPinDirection InPinDirection = ERigVMPinDirection::Invalid) const;`
- L1380 _private prototype_ `void ConfigurePinFromPin(URigVMPin* InOutPin, const URigVMPin* InPin, bool bCopyDisplayName = false);`
- L1381 _private prototype_ `void ConfigurePinFromArgument(URigVMPin* InOutPin, const FRigVMGraphFunctionArgument& InArgument, bool bCopyDisplayName = false);`
- L1382 _private prototype_ `bool ResetPinDefaultValue(URigVMPin* InPin, bool bSetupUndoRedo);`
- L1383 _private prototype_ `static FString GetPinInitialDefaultValue(const URigVMPin* InPin);`
- L1384 _private prototype_ `static FString GetPinInitialDefaultValueFromStruct(UScriptStruct* ScriptStruct, const URigVMPin* InPin, uint32 InOffset);`
- L1385 _private prototype_ `URigVMPin* InsertArrayPin(URigVMPin* ArrayPin, int32 InIndex, const FString& InDefaultValue, bool bSetupUndoRedo);`
- L1386 _private prototype_ `bool RemovePin(URigVMPin* InPinToRemove, bool bSetupUndoRedo, bool bForceBreakLinks = false);`
- L1387 _private prototype_ `FProperty* FindPropertyForPin(const FString& InPinPath);`
- L1388 _private prototype_ `bool BindPinToVariable(URigVMPin* InPin, const FString& InNewBoundVariablePath, bool bSetupUndoRedo, const FString& InVariableNodeName = FString());`
- L1389 _private prototype_ `bool UnbindPinFromVariable(URigVMPin* InPin, bool bSetupUndoRedo);`
- L1390 _private prototype_ `bool MakeBindingsFromVariableNode(URigVMVariableNode* InNode, bool bSetupUndoRedo);`
- L1391 _private prototype_ `bool PromotePinToVariable(URigVMPin* InPin, bool bCreateLocalVariable, bool bCreateVariableNode, const FVector2D& InNodePosition, bool bSetupUndoRedo);`
- L1392 _private prototype_ `URigVMInjectionInfo* InjectNodeIntoPin(const FString& InPinPath, bool bAsInput, const FName& InInputPinName, const FName& InOutputPinName, bool bSetupUndoRedo = true);`
- L1393 _private prototype_ `URigVMInjectionInfo* InjectNodeIntoPin(URigVMPin* InPin, bool bAsInput, const FName& InInputPinName, const FName& InOutputPinName, bool bSetupUndoRedo = true);`
- L1394 _private prototype_ `URigVMNode* EjectNodeFromPin(URigVMPin* InPin, bool bSetupUndoRedo = true, bool bPrintPythonCommands = false);`
- L1398 _protected prototype_ `bool IsValidGraph() const;`
- L1399 _protected prototype_ `bool IsValidSchema() const;`
- L1400 _protected prototype_ `bool IsGraphEditable() const;`
- L1403 _protected prototype_ `void RewireLinks(URigVMPin* OldPin, URigVMPin* NewPin, bool bAsInput, bool bSetupUndoRedo, TArray<URigVMLink*> InLinks = TArray<URigVMLink*>());`
- L1406 _protected prototype_ `virtual const UClass* GetNodeClassForTemplate(FRigVMTemplate* InTemplate) const;`
- L1407 _protected prototype_ `bool EjectAllInjectedNodes(URigVMNode* InNode, bool bSetupUndoRedo = true, bool bPrintPythonCommands = false);`
- L1411 _public prototype_ `URigVMUnitNode* AddUnitNode(UScriptStruct* InScriptStruct, TSubclassOf<URigVMUnitNode> InUnitNodeClass, const FName& InMethodName, const FVector2D& InPosition, const FString& InNodeName, bool bSetupUndoRedo, bool bPrintPythonCommand);`
- L1415 _public prototype_ `void RelinkSourceAndTargetPins(URigVMNode* RigNode, bool bSetupUndoRedo = true);` — try to reconnect source and target pins after a node deletion
- L1417 _public prototype_ `bool AddLink(URigVMPin* OutputPin, URigVMPin* InputPin, bool bSetupUndoRedo = true, ERigVMPinDirection InUserDirection = ERigVMPinDirection::Invalid, bool bCreateCastNode = false, bool bIsRestoringLinks = false, FString* OutFailureReason = nullptr);`
- L1418 _public prototype_ `bool BreakLink(URigVMPin* OutputPin, URigVMPin* InputPin, bool bSetupUndoRedo = true);`
- L1419 _public prototype_ `bool BreakAllLinks(URigVMPin* Pin, bool bAsInput, bool bSetupUndoRedo = true);`
- L1420 _public function_ `void EnableTypeCasting(bool bEnabled = true)`
- L1423 _private prototype_ `bool BreakAllLinksRecursive(URigVMPin* Pin, bool bAsInput, bool bTowardsParent, bool bSetupUndoRedo);`
- L1424 _private prototype_ `bool SetPinExpansion(URigVMPin* InPin, bool bIsExpanded, bool bSetupUndoRedo = true);`
- L1425 _private prototype_ `void ExpandPinRecursively(URigVMPin* InPin, bool bSetupUndoRedo);`
- L1426 _private prototype_ `bool SetPinIsWatched(URigVMPin* InPin, bool bIsWatched, bool bSetupUndoRedo);`
- L1427 _private prototype_ `bool SetPinDisplayName(URigVMPin* InPin, const FString& InDisplayName, bool bSetupUndoRedo);`
- L1428 _private prototype_ `bool AddEmptyPinCategory(const URigVMNode* InNode, const FString& InPinCategory, bool bSetupUndoRedo);`
- L1429 _private prototype_ `bool SetPinCategory(URigVMPin* InPin, const FString& InCategory, int32 InIndexInCategory, bool bSetupUndoRedo);`
- L1430 _private prototype_ `bool RemovePinCategory(const URigVMNode* InNode, const FString& InPinCategory, bool bSetupUndoRedo);`
- L1431 _private prototype_ `bool RenamePinCategory(const URigVMNode* InNode, const FString& InOldPinCategory, const FString& InNewPinCategory, bool bSetupUndoRedo);`
- L1432 _private prototype_ `bool SetPinCategoryIndex(const URigVMNode* InNode, const FString& InPinCategory, int32 InNewIndex, bool bSetupUndoRedo);`
- L1433 _private prototype_ `bool SetPinCategoryExpansion(const URigVMNode* InNode, const FString& InPinCategory, bool bIsExpanded, bool bSetupUndoRedo);`
- L1434 _private prototype_ `bool SetPinIndexInCategory(URigVMPin* InPin, int32 InIndexInCategory, bool bSetupUndoRedo);`
- L1435 _private prototype_ `bool SetNodeLayout(const URigVMNode* InNode, FRigVMNodeLayout InLayout, bool bSetupUndoRedo, bool bPrintPythonCommand);`
- L1436 _private prototype_ `bool ClearNodeLayout(const URigVMNode* InNode, bool bSetupUndoRedo, bool bPrintPythonCommand);`
- L1437 _private prototype_ `bool SetPinCategories(const FName& InNodeName, const TArray<FString>& InCategories, bool bSetupUndoRedo);`
- L1438 _private prototype_ `bool SetPinCategories(const URigVMNode* InNode, const TArray<FString>& InCategories, bool bSetupUndoRedo);`
- L1439 _private prototype_ `bool SetVariableName(URigVMVariableNode* InVariableNode, const FName& InVariableName, bool bSetupUndoRedo);`
- L1440 _private prototype_ `static void ForEveryPinRecursively(URigVMPin* InPin, TFunction<void(URigVMPin*)> OnEachPinFunction);`
- L1441 _private prototype_ `static void ForEveryPinRecursively(URigVMNode* InNode, TFunction<void(URigVMPin*)> OnEachPinFunction);`
- L1442 _private prototype_ `URigVMCollapseNode* CollapseNodes(const TArray<URigVMNode*>& InNodes, const FString& InCollapseNodeName, bool bSetupUndoRedo, bool bIsAggregate);`
- L1443 _private prototype_ `TArray<URigVMNode*> ExpandLibraryNode(URigVMLibraryNode* InNode, bool bSetupUndoRedo);`
- L1444 _private prototype_ `URigVMFunctionReferenceNode* PromoteCollapseNodeToFunctionReferenceNode(URigVMCollapseNode* InCollapseNode, bool bSetupUndoRedo, const FString& InExistingFunctionDefinitionPath);`
- L1445 _private prototype_ `URigVMCollapseNode* PromoteFunctionReferenceNodeToCollapseNode(URigVMFunctionReferenceNode* InFunctionRefNode, bool bSetupUndoRedo, bool bRemoveFunctionDefinition);`
- L1446 _private prototype_ `void SetReferencedFunction(URigVMFunctionReferenceNode* InFunctionRefNode, URigVMLibraryNode* InNewReferencedNode, bool bSetupUndoRedo);`
- L1448 _private prototype_ `void RefreshFunctionPins(URigVMNode* InNode, bool bSetupUndoRedo = false);`
- L1450 _private prototype_ `void ReportRemovedLink(const FString& InSourcePinPath, const FString& InTargetPinPath, const FString& Reason = FString());`
- L1464 _public prototype_ `TMap<FString, FString> GetRedirectedPinPaths(URigVMNode* InNode) const;`
- L1465 _public prototype_ `FPinState GetPinState(const URigVMPin* InPin, bool bStoreWeakInjectionInfos = false) const;`
- L1466 _public prototype_ `TMap<FString, FPinState> GetPinStates(URigVMNode* InNode, bool bStoreWeakInjectionInfos = false) const;`
- L1467 _public prototype_ `void ApplyPinState(URigVMPin* InPin, const FPinState& InPinState, bool bSetupUndoRedo = false);`
- L1471 _protected prototype_ `static void PostProcessDefaultValue(const URigVMPin* Pin, FString& OutDefaultValue);`
- L1475 _private prototype_ `static FLinearColor GetColorFromMetadata(const FString& InMetadata);`
- L1476 _private prototype_ `static void CreateDefaultValueForStructIfRequired(UScriptStruct* InStruct, FString& InOutDefaultValue);`
- L1477 _private prototype_ `static void OverrideDefaultValueMember(const FString& InMemberName, const FString& InMemberValue, FString& InOutDefaultValue);`
- L1479 _private prototype_ `void ResolveTemplateNodeMetaData(URigVMTemplateNode* InNode, bool bSetupUndoRedo);`
- L1480 _private prototype_ `void ResolveTemplateNodeMetaData(URigVMTemplateNode* InNode, const TArray<int32>& InFilteredPermutationIndices, bool bSetupUndoRedo);`
- L1485 _private prototype_ `bool ChangePinType(const FString& InPinPath, const FString& InCPPType, const FName& InCPPTypeObjectPath, bool bSetupUndoRedo, bool bSetupOrphanPins = true, bool bBreakLinks = true, bool bRemoveSubPins = true, bool bInitializeDefaultValue = true);`
- L1486 _private prototype_ `bool ChangePinType(URigVMPin* InPin, const FString& InCPPType, const FName& InCPPTypeObjectPath, bool bSetupUndoRedo, bool bSetupOrphanPins = true, bool bBreakLinks = true, bool bRemoveSubPins = true, bool bInitializeDefaultValue = true);`
- L1487 _private prototype_ `bool ChangePinType(URigVMPin* InPin, const FString& InCPPType,UObject* InCPPTypeObject, bool bSetupUndoRedo, bool bSetupOrphanPins = true, bool bBreakLinks = true, bool bRemoveSubPins = true, bool bInitializeDefaultValue = true);`
- L1488 _private prototype_ `bool ChangePinType(URigVMPin* InPin, TRigVMTypeIndex InTypeIndex, bool bSetupUndoRedo, bool bSetupOrphanPins = true, bool bBreakLinks = true, bool bRemoveSubPins = true, bool bInitializeDefaultValue = true);`
- L1490 _private prototype_ `bool MarkPackageDirty(const UObject* InObjectToDirty) const;`
- L1491 _private prototype_ `bool RenameObject(UObject* InObjectToRename, const TCHAR* InNewName, UObject* InNewOuter = nullptr, ERenameFlags InFlags = REN_None) const;`
- L1492 _private prototype_ `void DestroyObject(UObject* InObjectToDestroy) const ;`
- L1493 _private prototype_ `static URigVMPin* MakeExecutePin(URigVMNode* InNode, const FName& InName);`
- L1494 _private prototype_ `static bool MakeExecutePin(URigVMPin* InOutPin);`
- L1495 _private prototype_ `bool AddGraphNode(URigVMNode* InNode, bool bNotify);`
- L1496 _private prototype_ `void AddNodePin(URigVMNode* InNode, URigVMPin* InPin);`
- L1497 _private prototype_ `static void AddSubPin(URigVMPin* InParentPin, URigVMPin* InPin);`
- L1498 _private prototype_ `static bool EnsurePinValidity(URigVMPin* InPin, bool bRecursive);`
- L1499 _private prototype_ `static void ValidatePin(URigVMPin* InPin);`
- L1503 _private prototype_ `bool EnsureLocalVariableValidity();` — recreate the CPP type strings for variables that reference a type object they can get out of sync when the variable references a user defined struct
- L1505 _private prototype_ `TArray<FRigVMExternalVariable> GetAllVariables(const bool bIncludeInputArguments = false) const;`
- L1507 _private prototype_ `void RefreshFunctionReferences(const URigVMLibraryNode* InFunctionDefinition, bool bSetupUndoRedo, bool bLoadIfNecessary);`
- L1508 _private prototype_ `void PropagateNotificationToFunctionReferences(const URigVMLibraryNode* InFunctionDefinition, ERigVMGraphNotifType InNotifType, UObject* InSubject, bool bLoadIfNecessary);`
- L1512 _private prototype_ `void PropagateExposedPinTypeChangeToReferencesAndInterface(const URigVMLibraryNode* InFunctionDefinition, bool bSetupOrphanPins);` — Mirror of the cross-graph pin layout propagation in ChangeExposedPinType_Internal — not on the action stack on its own, so FRigVMChangePinTypeAction::Undo/Redo replays it.
- L1516 _public prototype_ `FRigVMExternalVariable GetVariableByProperty(const FProperty* InExternalVariableProperty) const;`
- L1517 _public prototype_ `FRigVMExternalVariable GetVariableByName(const FName& InExternalVariableName, const bool bIncludeInputArguments = false) const;`
- L1518 _public prototype_ `FRigVMExternalVariable GetVariableByGuid(const FGuid& InExternalVariableGuid, const bool bIncludeInputArguments = false) const;`
- L1565 _public prototype_ `TArray<FLinkedPath> GetLinkedPaths() const;`
- L1566 _public prototype_ `static TArray<FLinkedPath> GetLinkedPaths(const TArray<URigVMLink*>& InLinks);`
- L1567 _public prototype_ `static TArray<FLinkedPath> GetLinkedPaths(URigVMNode* InNode, bool bIncludeInjectionNodes = false);`
- L1568 _public prototype_ `static TArray<FLinkedPath> GetLinkedPaths(const TArray<URigVMNode*>& InNodes, bool bIncludeInjectionNodes = false);`
- L1569 _public prototype_ `static TArray<FLinkedPath> GetLinkedPaths(const URigVMPin* InPin, bool bSourceLinksRecursive = false, bool bTargetLinksRecursive = false);`
- L1570 _public prototype_ `bool BreakLinkedPaths(const TArray<FLinkedPath>& InLinkedPaths, bool bSetupUndoRedo = false, bool bRelyOnBreakLink = true);`
- L1571 _public prototype_ `bool RestoreLinkedPaths( const TArray<FLinkedPath>& InLinkedPaths, const FRestoreLinkedPathSettings& InSettings = FRestoreLinkedPathSettings(), bool bSetupUndoRedo = false);`
- L1575 _public prototype_ `TArray<FLinkedPath> RemapLinkedPaths( const TArray<FLinkedPath>& InLinkedPaths, const FRestoreLinkedPathSettings& InSettings = FRestoreLinkedPathSettings(), bool bSetupUndoRedo = false);`
- L1579 _public prototype_ `bool FastBreakLinkedPaths(const TArray<FLinkedPath>& InLinkedPaths, bool bSetupUndoRedo = false);`
- L1580 _public prototype_ `URigVMLink* FindLinkFromPinPathRepresentation(const FString& InPinPathRepresentation, bool bLookForDetachedLink) const;`
- L1581 _public prototype_ `void ProcessDetachedLinks(const FRestoreLinkedPathSettings& InSettings = FRestoreLinkedPathSettings());`
- L1585 _public prototype_ `void RegisterUseOfTemplate(const URigVMTemplateNode* InNode);` — Registers this template node's use for later determining the commonly used types
- L1588 _public prototype_ `FRigVMTemplate::FTypeMap GetCommonlyUsedTypesForTemplate(const URigVMTemplateNode* InNode) const;` — Inquire on the commonly used types for a template node. This can be used to resolve a node without user input (as a default)
- L1592 _public prototype_ `URigVMActionStack* GetActionStack() const;` — `UFUNCTION(BlueprintPure, Category = RigVMController)`
- L1593 _public prototype_ `URigVMActionStack* GetActionStack_NoLock() const;`
- L1596 _public prototype_ `void SetActionStack(URigVMActionStack* InActionStack);` — `UFUNCTION(BlueprintCallable, Category = RigVMController)`
- L1597 _public prototype_ `void SetActionStack_NoLock(URigVMActionStack* InActionStack);`
- L1599 _public prototype_ `URigVMNode* ConvertRerouteNodeToDispatch(URigVMRerouteNode* InRerouteNode, const FName& InTemplateNotation, bool bSetupUndoRedo, bool bPrintPythonCommand);`
- L1603 _protected prototype_ `IRigVMClientHost* GetClientHost_Internal(const URigVMGraph* InGraph) const;`
- L1604 _protected prototype_ `URigVMPin* CreatePinFromPinInfo(const FRigVMRegistry& InRegistry, const FRigVMPinInfoArray& InPreviousPinInfos, const FRigVMPinInfo& InPinInfo, const FString& InPinPath, UObject* InOuter);`
- L1605 _protected prototype_ `void UpdateGraphSectionsIfRequired();`
- L1608 _protected prototype_ `FRigVMClientPatchResult PatchRerouteNodesOnLoad();` — backwards compatibility code
- L1609 _protected prototype_ `FRigVMClientPatchResult PatchUnitNodesOnLoad();`
- L1610 _protected prototype_ `FRigVMClientPatchResult PatchDispatchNodesOnLoad();`
- L1611 _protected prototype_ `FRigVMClientPatchResult PatchBranchNodesOnLoad();`
- L1612 _protected prototype_ `FRigVMClientPatchResult PatchIfSelectNodesOnLoad();`
- L1613 _protected prototype_ `FRigVMClientPatchResult PatchArrayNodesOnLoad();`
- L1614 _protected prototype_ `FRigVMClientPatchResult PatchReduceArrayFloatDoubleConvertsionsOnLoad();`
- L1615 _protected prototype_ `FRigVMClientPatchResult PatchInvalidLinksOnWildcards();`
- L1616 _protected prototype_ `FRigVMClientPatchResult PatchFunctionsWithInvalidReturnPaths();`
- L1617 _protected prototype_ `FRigVMClientPatchResult PatchExecutePins();`
- L1618 _protected prototype_ `FRigVMClientPatchResult PatchLazyPins();`
- L1619 _protected prototype_ `FRigVMClientPatchResult PatchConstantPins();`
- L1620 _protected prototype_ `FRigVMClientPatchResult PatchPinDefaultValues();`
- L1621 _protected prototype_ `FRigVMClientPatchResult PatchUserDefinedStructPinNames();`
- L1622 _protected prototype_ `FRigVMClientPatchResult PatchLocalVariableTypes();`
- L1623 _protected prototype_ `FRigVMClientPatchResult PatchPinGuidInCollapseNodes();`
- L1624 _protected prototype_ `FRigVMClientPatchResult PatchExternalVariablesToArguments(bool bInSetupUndoRedo=false);`
- L1626 _protected prototype_ `ERigVMPinDefaultValueType GetDefaultValueType(const URigVMPin* InPin, const FString& InDefaultValue) const;`
- L1629 _protected function_ `template<typename T> static void SortGraphElementsByGraphDepth(TArray<T*>& InOutElements, bool bReverse = false)`
- L1670 _protected function_ `template<typename T> static void SortGraphElementsByImportOrder( TArray<TObjectPtr<T>> InOutElements, const TArray<T*>& InElementsInImportOrder, const TArray<T*>& InPreviousElementPriorToImport )`
- L1688 _private member_ `TArray<TObjectPtr<URigVMGraph>> Graphs;` — `UPROPERTY(transient)`
- L1691 _private member_ `TSubclassOf<URigVMSchema> SchemaClass;` — `UPROPERTY(transient, DuplicateTransient)`
- L1693 _private member_ `mutable TWeakObjectPtr<URigVMActionStack> WeakActionStack;`
- L1694 _private member_ `mutable FDelegateHandle ActionStackHandle;`
- L1696 _private member_ `bool bSuspendNotifications;`
- L1697 _private member_ `bool bSuspendMarkingPackageDirty;`
- L1698 _private member_ `bool bSuspendRefreshingFunctionReferences;`
- L1699 _private member_ `bool bReportWarningsAndErrors;`
- L1700 _private member_ `bool bIgnoreRerouteCompactnessChanges;`
- L1701 _private member_ `ERigVMPinDirection UserLinkDirection;`
- L1702 _private member_ `bool bEnableTypeCasting;`
- L1703 _private member_ `bool bAllowPrivateFunctions;`
- L1704 _private member_ `bool bSuspendASTLinkChecks;`
- L1705 _private member_ `TOptional<ERigVMPinDefaultValueType> OptionalDefaultValueType;`
- L1709 _private member_ `TMap<FString, FString> InputPinRedirectors;` — temporary maps used for pin redirection only valid between Detach & ReattachLinksToPinObjects
- L1710 _private member_ `TMap<FString, FString> OutputPinRedirectors;`
- L1724 _private function_ `friend uint32 GetTypeHash(const FRigVMStructPinRedirectorKey& Cache)`
- L1743 _private member_ `static TMap<FRigVMStructPinRedirectorKey, FString> PinPathCoreRedirectors;`
- L1744 _private member_ `FTransactionallySafeCriticalSection PinPathCoreRedirectorsLock;`
- L1745 _private member_ `mutable FTransactionallySafeCriticalSection ActionStackLock;`
- L1747 _private member_ `FRigVMUnitNodeCreatedContext UnitNodeCreatedContext;`
- L1749 _private member_ `bool bIsTransacting;` — Performing undo/redo transaction
- L1750 _private member_ `bool bIsRunningUnitTest;`
- L1751 _private member_ `bool bIsFullyResolvingTemplateNode;`
- L1755 _public member_ `bool bSuspendTemplateComputation;`
- L1760 _private member_ `bool bRegisterTemplateNodeUsage;`
- L1763 _private member_ `bool bEnableSchemaRemoveNodeCheck;`
- L1765 _private member_ `int32 UpdateGraphSectionsBracket;`

#### struct `URigVMController::FRepopulatePinsNodeData`  
`struct FRepopulatePinsNodeData`  
_L1252-1267_
- L1254 _public member_ `URigVMNode* Node = nullptr;`
- L1255 _public member_ `uint32 PreviousPinHash = 0;`
- L1256 _public member_ `FRigVMPinInfoArray PreviousPinInfos;`
- L1257 _public member_ `FRigVMPinInfoArray NewPinInfos;`
- L1258 _public member_ `TArray<int32> NewPinsToAdd;`
- L1259 _public member_ `TArray<int32> PreviousPinsToRemove;`
- L1260 _public member_ `TArray<int32> PreviousPinsToOrphan;`
- L1261 _public member_ `TArray<int32> PreviousPinsToUpdate;`
- L1262 _public member_ `bool bSetupOrphanPinsForThisNode = false;`
- L1263 _public member_ `bool bFollowCoreRedirectors = false;`
- L1264 _public member_ `bool bRequirePinStates = false;`
- L1265 _public member_ `bool bRecreateLinks = false;`
- L1266 _public member_ `bool bRequireRecreateLinks = false;`

#### struct `URigVMController::FPinState`  
`struct FPinState`  
_L1452-1462_
- L1454 _public member_ `ERigVMPinDirection Direction;`
- L1455 _public member_ `FString CPPType;`
- L1456 _public member_ `UObject* CPPTypeObject;`
- L1457 _public member_ `FString DefaultValue;`
- L1458 _public member_ `ERigVMPinDefaultValueType DefaultValueType;`
- L1459 _public member_ `bool bIsExpanded;`
- L1460 _public member_ `TArray<URigVMInjectionInfo*> InjectionInfos;`
- L1461 _public member_ `TArray<URigVMInjectionInfo::FWeakInfo> WeakInjectionInfos;`

#### struct `URigVMController::FLinkedPath`  
`struct FLinkedPath`  
_L1520-1545_
- L1522 _public function_ `FLinkedPath() : bSourceNodeIsInjected(false) , bTargetNodeIsInjected(false)`
- L1527 _public prototype_ `FLinkedPath(URigVMLink* InLink);`
- L1529 _public prototype_ `URigVMGraph* GetGraph(URigVMGraph* InGraph = nullptr) const;`
- L1530 _public prototype_ `FString GetPinPathRepresentation() const;`
- L1531 _public prototype_ `URigVMPin* GetSourcePin(URigVMGraph* InGraph = nullptr) const;`
- L1532 _public prototype_ `URigVMPin* GetTargetPin(URigVMGraph* InGraph = nullptr) const;`
- L1536 _public function_ `bool operator ==(const FLinkedPath& InOther) const`
- L1537 _public function_ `bool operator !=(const FLinkedPath& InOther) const`
- L1539 _public member_ `TSoftObjectPtr<URigVMGraph> GraphPtr;`
- L1540 _public member_ `FString SourcePinPath;`
- L1541 _public member_ `FString TargetPinPath;`
- L1542 _public member_ `FString OriginalPinPathRepresentation;`
- L1543 _public member_ `bool bSourceNodeIsInjected;`
- L1544 _public member_ `bool bTargetNodeIsInjected;`

#### struct `URigVMController::FRestoreLinkedPathSettings`  
`struct FRestoreLinkedPathSettings`  
_L1547-1563_
- L1549 _public function_ `FRestoreLinkedPathSettings() : bFollowCoreRedirectors(false) , bRelayToOrphanPins(false) , bIsImportingFromText(false) , UserDirection(ERigVMPinDirection::Invalid)`
- L1556 _public member_ `bool bFollowCoreRedirectors;`
- L1557 _public member_ `bool bRelayToOrphanPins;`
- L1558 _public member_ `bool bIsImportingFromText;`
- L1559 _public member_ `ERigVMPinDirection UserDirection;`
- L1560 _public member_ `TMap<FString, FString> NodeNameMap;`
- L1561 _public member_ `TMap<FString,FRigVMController_PinPathRemapDelegate> RemapDelegates;`
- L1562 _public member_ `FRigVMController_CheckPinCompatibilityDelegate CompatibilityDelegate;`

#### struct `URigVMController::FRigVMStructPinRedirectorKey`  
`struct FRigVMStructPinRedirectorKey`  
_L1712-1741_
- L1714 _public function_ `FRigVMStructPinRedirectorKey()`
- L1718 _public function_ `FRigVMStructPinRedirectorKey(UScriptStruct* InScriptStruct, const FString& InPinPathInNode) : Struct(InScriptStruct) , PinPathInNode(InPinPathInNode)`
- L1729 _public function_ `bool operator ==(const FRigVMStructPinRedirectorKey& Other) const`
- L1734 _public function_ `bool operator !=(const FRigVMStructPinRedirectorKey& Other) const`
- L1739 _public member_ `UScriptStruct* Struct;`
- L1740 _public member_ `FString PinPathInNode;`

#### class `FRigVMControllerNotifGuard`  
`class FRigVMControllerNotifGuard`  
_L1795-1815_
- L1799 _public function_ `FRigVMControllerNotifGuard(URigVMController* InController, bool bInSuspendNotifications = true) : Controller(InController)`
- L1806 _public function_ `~FRigVMControllerNotifGuard()`
- L1813 _private member_ `URigVMController* Controller;`
- L1814 _private member_ `bool bPreviousSuspendNotifications;`

#### class `FRigVMDefaultValueTypeGuard`  
`class FRigVMDefaultValueTypeGuard`  
_L1817-1840_
- L1821 _public function_ `FRigVMDefaultValueTypeGuard(URigVMController* InController, ERigVMPinDefaultValueType InDefaultValueType = ERigVMPinDefaultValueType::Override, bool bForce = false) : Controller(InController)`
- L1831 _public function_ `~FRigVMDefaultValueTypeGuard()`
- L1838 _private member_ `URigVMController* Controller;`
- L1839 _private member_ `TOptional<ERigVMPinDefaultValueType> bPreviousDefaultValueType;`

#### class `FRigVMControllerASTLinkCheckGuard`  
`class FRigVMControllerASTLinkCheckGuard`  
_L1842-1862_
- L1846 _public function_ `explicit FRigVMControllerASTLinkCheckGuard(URigVMController* InController, bool bInSuspendASTLinkChecks = true) : Controller(InController)`
- L1853 _public function_ `~FRigVMControllerASTLinkCheckGuard()`
- L1860 _private member_ `URigVMController* Controller;`
- L1861 _private member_ `bool bPreviousSuspendASTLinkChecks;`

#### struct `FRigVMController_CommonTypePerTemplate`  
`struct FRigVMController_CommonTypePerTemplate`  
_L1866-1872_
- reflection: `USTRUCT()`
- L1871 _public member_ `TMap<FString,int32> Counts;` — `UPROPERTY(EditAnywhere, Category = "RigVMController")`

#### class `URigVMControllerSettings`  
`class URigVMControllerSettings : public UObject`  
_L1878-1896_
- reflection: `UCLASS(MinimalAPI, config = EditorSettings)`
- inherits: `UObject`
- desc: Default settings for the RigVM Controller
- L1881 _public prototype_ `URigVMControllerSettings(const FObjectInitializer& Initializer);`
- L1891 _public member_ `bool bAutoResolveTemplateNodesWhenLinkingExecute;` — `UPROPERTY(EditAnywhere, Category = "RigVMController")` — When adding a link to an execute pin on a template node, this functionality automatically resolves the template node to the most commonly used type.
- L1895 _public member_ `TMap<FName,FRigVMController_CommonTypePerTemplate> TemplateDefaultTypes;` — `UPROPERTY()` — The commonly used types for a template node

#### class `FRigVMControllerGraphSectionsScope`  
`class FRigVMControllerGraphSectionsScope`  
_L1898-1921_
- L1901 _public function_ `FRigVMControllerGraphSectionsScope(URigVMController* InController) : Controller(InController)`
- L1910 _public function_ `~FRigVMControllerGraphSectionsScope()`
- L1920 _private member_ `URigVMController* Controller;`

#### Free symbols / members of external scopes

- L28 _macro_ `#define UE_API RIGVMDEVELOPER_API`
- L85 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FRigVMController_ShouldStructUnfoldDelegate, const UStruct*) DECLARE_DELEGATE_RetVal_OneParam(TArray<FRigVMExternalVariable>, FRigVMController_GetExternalVariablesDelegate, URigVMGraph*) DECLARE_DELEGATE_RetVal(const FRigVMByteCode*, FRigVMController_GetByteCodeDelegate) DECLARE_DELEGATE_RetVal_OneParam(bool, FRigVMController_RequestLocalizeFunctionDelegate, FRigVMGraphFunctionIdentifier&) DECLARE_DELEGATE_RetVal_ThreeParams(FName, FRigVMController_RequestNewExternalVariableDelegate, FRigVMGraphVariableDescription, bool, bool);`
- L85 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FRigVMController_ShouldStructUnfoldDelegate, const UStruct*) DECLARE_DELEGATE_RetVal_OneParam(TArray<FRigVMExternalVariable>, FRigVMController_GetExternalVariablesDelegate, URigVMGraph*) DECLARE_DELEGATE_RetVal(const FRigVMByteCode*, FRigVMController_GetByteCodeDelegate) DECLARE_DELEGATE_RetVal_OneParam(bool, FRigVMController_RequestLocalizeFunctionDelegate, FRigVMGraphFunctionIdentifier&) DECLARE_DELEGATE_RetVal_ThreeParams(FName, FRigVMController_RequestNewExternalVariableDelegate, FRigVMGraphVariableDescription, bool, bool);`
- L86 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(TArray<FRigVMExternalVariable>, FRigVMController_GetExternalVariablesDelegate, URigVMGraph*) DECLARE_DELEGATE_RetVal(const FRigVMByteCode*, FRigVMController_GetByteCodeDelegate) DECLARE_DELEGATE_RetVal_OneParam(bool, FRigVMController_RequestLocalizeFunctionDelegate, FRigVMGraphFunctionIdentifier&) DECLARE_DELEGATE_RetVal_ThreeParams(FName, FRigVMController_RequestNewExternalVariableDelegate, FRigVMGraphVariableDescription, bool, bool);`
- L87 _delegate_ `DECLARE_DELEGATE_RetVal(const FRigVMByteCode*, FRigVMController_GetByteCodeDelegate) DECLARE_DELEGATE_RetVal_OneParam(bool, FRigVMController_RequestLocalizeFunctionDelegate, FRigVMGraphFunctionIdentifier&) DECLARE_DELEGATE_RetVal_ThreeParams(FName, FRigVMController_RequestNewExternalVariableDelegate, FRigVMGraphVariableDescription, bool, bool);`
- L88 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FRigVMController_RequestLocalizeFunctionDelegate, FRigVMGraphFunctionIdentifier&) DECLARE_DELEGATE_RetVal_ThreeParams(FName, FRigVMController_RequestNewExternalVariableDelegate, FRigVMGraphVariableDescription, bool, bool);`
- L89 _delegate_ `DECLARE_DELEGATE_RetVal_ThreeParams(FName, FRigVMController_RequestNewExternalVariableDelegate, FRigVMGraphVariableDescription, bool, bool);`
- L90 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FRigVMController_IsDependencyCyclicDelegate, const FRigVMGraphFunctionHeader& Dependent, const FRigVMGraphFunctionHeader& Dependency) DECLARE_DELEGATE_RetVal_TwoParams(FRigVMController_BulkEditResult, FRigVMController_RequestBulkEditDialogDelegate, URigVMLibraryNode*, ERigVMControllerBulkEditType) DECLARE_DELEGATE_RetVal_OneParam(bool, FRigVMController_RequestBreakLinksDialogDelegate, TArray<URigVMLink*>) DECLARE_DELEGATE_RetVal_OneParam(TRigVMTypeIndex, FRigVMController_RequestPinTypeSelectionDelegate, const TArray<TRigVMTypeIndex>& Types) DECLARE_DELEGATE_FiveParams(FRigVMController_OnBulkEditProgressDelegate, TSoftObjectPtr<URigVMFunctionReferenceNode>, ERigVMControllerBulkEditType, ERigVMControllerBulkEditProgress, int32, int32) DECLARE_DELEGATE_RetVal_TwoParams(FString, FRigVMController_PinPathRemapDelegate, const FString& , bool );`
- L90 _prototype_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FRigVMController_IsDependencyCyclicDelegate, const FRigVMGraphFunctionHeader& Dependent, const FRigVMGraphFunctionHeader& Dependency) DECLARE_DELEGATE_RetVal_TwoParams(FRigVMController_BulkEditResult, FRigVMController_RequestBulkEditDialogDelegate, URigVMLibraryNode*, ERigVMControllerBulkEditType) DECLARE_DELEGATE_RetVal_OneParam(bool, FRigVMController_RequestBreakLinksDialogDelegate, TArray<URigVMLink*>) DECLARE_DELEGATE_RetVal_OneParam(TRigVMTypeIndex, FRigVMController_RequestPinTypeSelectionDelegate, const TArray<TRigVMTypeIndex>& Types) DECLARE_DELEGATE_FiveParams(FRigVMController_OnBulkEditProgressDelegate, TSoftObjectPtr<URigVMFunctionReferenceNode>, ERigVMControllerBulkEditType, ERigVMControllerBulkEditProgress, int32, int32) DECLARE_DELEGATE_RetVal_TwoParams(FString, FRigVMController_PinPathRemapDelegate, const FString& , bool );`
- L91 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(FRigVMController_BulkEditResult, FRigVMController_RequestBulkEditDialogDelegate, URigVMLibraryNode*, ERigVMControllerBulkEditType) DECLARE_DELEGATE_RetVal_OneParam(bool, FRigVMController_RequestBreakLinksDialogDelegate, TArray<URigVMLink*>) DECLARE_DELEGATE_RetVal_OneParam(TRigVMTypeIndex, FRigVMController_RequestPinTypeSelectionDelegate, const TArray<TRigVMTypeIndex>& Types) DECLARE_DELEGATE_FiveParams(FRigVMController_OnBulkEditProgressDelegate, TSoftObjectPtr<URigVMFunctionReferenceNode>, ERigVMControllerBulkEditType, ERigVMControllerBulkEditProgress, int32, int32) DECLARE_DELEGATE_RetVal_TwoParams(FString, FRigVMController_PinPathRemapDelegate, const FString& , bool );`
- L92 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FRigVMController_RequestBreakLinksDialogDelegate, TArray<URigVMLink*>) DECLARE_DELEGATE_RetVal_OneParam(TRigVMTypeIndex, FRigVMController_RequestPinTypeSelectionDelegate, const TArray<TRigVMTypeIndex>& Types) DECLARE_DELEGATE_FiveParams(FRigVMController_OnBulkEditProgressDelegate, TSoftObjectPtr<URigVMFunctionReferenceNode>, ERigVMControllerBulkEditType, ERigVMControllerBulkEditProgress, int32, int32) DECLARE_DELEGATE_RetVal_TwoParams(FString, FRigVMController_PinPathRemapDelegate, const FString& , bool );`
- L93 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(TRigVMTypeIndex, FRigVMController_RequestPinTypeSelectionDelegate, const TArray<TRigVMTypeIndex>& Types) DECLARE_DELEGATE_FiveParams(FRigVMController_OnBulkEditProgressDelegate, TSoftObjectPtr<URigVMFunctionReferenceNode>, ERigVMControllerBulkEditType, ERigVMControllerBulkEditProgress, int32, int32) DECLARE_DELEGATE_RetVal_TwoParams(FString, FRigVMController_PinPathRemapDelegate, const FString& , bool );`
- L94 _delegate_ `DECLARE_DELEGATE_FiveParams(FRigVMController_OnBulkEditProgressDelegate, TSoftObjectPtr<URigVMFunctionReferenceNode>, ERigVMControllerBulkEditType, ERigVMControllerBulkEditProgress, int32, int32) DECLARE_DELEGATE_RetVal_TwoParams(FString, FRigVMController_PinPathRemapDelegate, const FString& , bool );`
- L95 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(FString, FRigVMController_PinPathRemapDelegate, const FString& , bool );`
- L96 _delegate_ `DECLARE_DELEGATE_OneParam(FRigVMController_RequestJumpToHyperlinkDelegate, const UObject* InSubject);`
- L96 _prototype_ `DECLARE_DELEGATE_OneParam(FRigVMController_RequestJumpToHyperlinkDelegate, const UObject* InSubject);`
- L97 _delegate_ `DECLARE_DELEGATE_OneParam(FRigVMController_ConfigureWorkflowOptionsDelegate, URigVMUserWorkflowOptions* InOutOptions);`
- L97 _prototype_ `DECLARE_DELEGATE_OneParam(FRigVMController_ConfigureWorkflowOptionsDelegate, URigVMUserWorkflowOptions* InOutOptions);`
- L98 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FRigVMController_CheckPinCompatibilityDelegate, URigVMPin*, URigVMPin*);`
- L98 _prototype_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FRigVMController_CheckPinCompatibilityDelegate, URigVMPin*, URigVMPin*);`
- L239 _prototype_ `uint32 GetTypeHash(const FRigVMPinInfoArray& InPins);`
- L1676 _function_ `` (scope `URigVMController::SortGraphElementsByImportOrder`)

### `Plugins/Runtime/RigVM/Source/RigVMDeveloper/Public/RigVMModel/RigVMControllerActions.h` (Public)


#### struct `FRigVMActionKey`  
`struct FRigVMActionKey`  
_L45-71_
- reflection: `USTRUCT()`
- desc: The action key is used for serializing and storing an action in the stack, or within another action.
- L50 _public member_ `FString ScriptStructPath;` — `UPROPERTY()`
- L53 _public member_ `FString ExportedText;` — `UPROPERTY()`
- L55 _public prototype_ `UScriptStruct* GetScriptStruct() const;`
- L56 _public prototype_ `TSharedPtr<FStructOnScope> GetAction() const;`
- L59 _public function_ `template<class ActionType> void Set(const ActionType& InAction)`

#### struct `FRigVMActionWrapper`  
`struct FRigVMActionWrapper`  
_L76-91_
- desc: The action wrapper is used to extract an action from a serialized key.
- L79 _public prototype_ `FRigVMActionWrapper(const FRigVMActionKey& Key);`
- L80 _public prototype_ `~FRigVMActionWrapper();`
- L82 _public prototype_ `const UScriptStruct* GetScriptStruct() const;`
- L83 _public prototype_ `FRigVMBaseAction* GetAction(URigVMController* InLastController = nullptr) const;`
- L84 _public prototype_ `FString ExportText() const;`
- L87 _private prototype_ `FRigVMActionWrapper(const FRigVMActionWrapper& Other) = delete;`
- L88 _private prototype_ `FRigVMActionWrapper& operator = (const FRigVMActionWrapper& Other) = delete;`
- L90 _private member_ `TSharedPtr<FStructOnScope> StructOnScope;`

#### struct `FRigVMActionNodeContent`  
`struct FRigVMActionNodeContent`  
_L99-108_
- reflection: `USTRUCT()`
- desc: A tuple access to sub actions, merge functionality as well as undo and redo base implementations.
- L104 _public member_ `FString Old;` — `UPROPERTY()`
- L107 _public member_ `FString New;` — `UPROPERTY()`

#### struct `FRigVMBaseAction`  
`struct FRigVMBaseAction`  
_L116-219_
- reflection: `USTRUCT()`
- desc: The base action is the base struct for all actions, and provides access to sub actions, merge functionality as well as undo and redo base implementations.
- L122 _public member_ `static const inline TCHAR* RedoPrefix = TEXT("Red`
- L123 _public member_ `static const inline TCHAR* UndoPrefix = TEXT("Und`
- L124 _public member_ `static const inline TCHAR* AddActionPrefix = TEXT("Add`
- L125 _public member_ `static const inline TCHAR* BeginActionPrefix = TEXT("Beg`
- L126 _public member_ `static const inline TCHAR* EndActionPrefix = TEXT("End`
- L127 _public member_ `static const inline TCHAR* CancelActionPrefix = TEXT("Can`
- L130 _public prototype_ `FRigVMBaseAction(URigVMController* InController);` — Default constructor
- L133 _public prototype_ `virtual ~FRigVMBaseAction() = default;` — Default destructor
- L136 _public prototype_ `URigVMController* GetController() const;` — Returns the controller of this action
- L139 _public function_ `virtual UScriptStruct* GetScriptStruct() const` — Access to the actions script struct. this needs to be overloaded
- L142 _public function_ `virtual bool IsEmpty() const` — Returns true if this action is empty has no effect
- L145 _public function_ `virtual FString GetTitle() const` — Returns the title of the action - used for the Edit menu's undo / redo
- L148 _public function_ `virtual void SetTitle(const FString& InTitle)` — Sets the title of the action - used for the Edit menu's undo / redo
- L152 _public prototype_ `virtual bool Merge(const FRigVMBaseAction* Other);` — Trys to merge the action with another action and returns true if successfull.
- L155 _public prototype_ `virtual bool MakesObsolete(const FRigVMBaseAction* Other) const;` — Returns true if this action makes the other action obsolete.
- L158 _public function_ `bool CanUndoRedo() const` — Returns true if this action can undo / redo
- L161 _public prototype_ `virtual bool Undo();` — Un-does the action and returns true if successfull.
- L164 _public prototype_ `virtual bool Redo();` — Re-does the action and returns true if successfull.
- L168 _public function_ `template<class ActionType> void AddAction(const ActionType& InAction)` — Adds a child / sub action to this one
- L176 _public prototype_ `bool StoreNode(const URigVMNode* InNode, bool bIsPriorChange = true);`
- L177 _public prototype_ `bool RestoreNode(const FName& InNodeName, bool bIsUndoing);`
- L182 _public prototype_ `void LogAction(const FString& InPrefix) const;` — Logs the action to the console / output log
- L187 _public function_ `FRigVMBaseAction() : WeakController(nullptr) , Title(TEXT("Action"))` — Empty constructor
- L195 _protected prototype_ `void EnsureControllerValidity() const;`
- L197 _protected member_ `mutable TWeakObjectPtr<URigVMController> WeakController;`
- L200 _protected member_ `FSoftObjectPath ControllerPath;` — `UPROPERTY()`
- L203 _protected member_ `FSoftObjectPath ClientHostPath;` — `UPROPERTY()`
- L206 _protected member_ `FString ControllerModelPath;` — `UPROPERTY()`
- L209 _protected member_ `FString Title;` — `UPROPERTY()`
- L212 _protected member_ `TArray<FRigVMActionKey> SubActions;` — `UPROPERTY()`
- L215 _protected member_ `TMap<FName, FRigVMActionNodeContent> ExportedNodes;` — `UPROPERTY()`

#### class `URigVMActionStack`  
`class URigVMActionStack : public UObject`  
_L230-459_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- desc: The Action Stack can be used to track actions happening on a Graph. Currently the only owner of the ActionStack is the Controller. Actions can be added to the stack, or they can be understood as scopes / brackets. For this you can use BeginAction / EndAction / CancelAction to open / close a bracket. Open brackets automatically record additional actions occuring during the bracket's lifetime.
- L234 _private function_ `virtual ~URigVMActionStack()`
- L241 _public prototype_ `static URigVMActionStack* GetDisabledActionStack();`
- L245 _public function_ `template<class ActionType> void BeginAction(ActionType& InAction)` — Begins an action and opens a bracket / scope.
- L268 _public function_ `template<class ActionType> void EndAction(ActionType& InAction, bool bPerformMerge = false)` — Ends an action and closes a bracket / scope.
- L295 _public function_ `template<class ActionType> void CancelAction(ActionType& InAction)` — Cancels an action, closes a bracket / scope and discards all actions to this point.
- L318 _public function_ `template<class ActionType> void AddAction(const ActionType& InAction, bool bPerformMerge = false, bool bMarkDirty = true)` — Adds an action to the stack. Optionally this can perform a potential merge of this action with the previous action to compact the stack.
- L394 _public prototype_ `bool OpenUndoBracket(URigVMController* InController, const FString& InTitle);` — `UFUNCTION()` — Opens an undo bracket / scope to record actions into. This is primary useful for Python.
- L399 _public prototype_ `bool CloseUndoBracket(URigVMController* InController);` — `UFUNCTION()` — Closes an undo bracket / scope. This is primary useful for Python.
- L404 _public prototype_ `bool CancelUndoBracket(URigVMController* InController);` — `UFUNCTION()` — Cancels an undo bracket / scope. This is primary useful for Python.
- L410 _public prototype_ `bool Undo(URigVMController* InController);` — `UFUNCTION()` — Pops the last action from the undo stack and perform undo on it. Note: This should really only be used for unit tests, use the GEditor's main Undo method instead.
- L416 _public prototype_ `bool Redo(URigVMController* InController);` — `UFUNCTION()` — Pops the last action from the redo stack and perform redo on it. Note: This should really only be used for unit tests, use the GEditor's main Redo method instead.
- L419 _public prototype_ `virtual void PostTransacted(const FTransactionObjectEvent& TransactionEvent) override;`
- L422 _public function_ `FRigVMGraphModifiedEvent& OnModified()`
- L428 _private function_ `template<class ActionType> void LogAction(const ActionType& InAction, const FString& InPrefix)`
- L433 _private prototype_ `void LogAction(const UScriptStruct* InActionStruct, const FRigVMBaseAction& InAction, const FString& InPrefix);`
- L436 _private prototype_ `bool IsDisabled() const;`
- L439 _private member_ `int32 ActionIndex;` — `UPROPERTY()`
- L442 _private member_ `TArray<FRigVMActionKey> UndoActions;` — `UPROPERTY(NonTransactional)`
- L445 _private member_ `TArray<FRigVMActionKey> RedoActions;` — `UPROPERTY(NonTransactional)`
- L447 _private member_ `TArray<FRigVMBaseAction*> CurrentActions;`
- L448 _private member_ `TArray<FRigVMBaseAction*> BracketActions;`
- L450 _private member_ `FRigVMGraphModifiedEvent ModifiedEvent;`
- L453 _private member_ `bool bSuspendLogActions = false;`
- L454 _private member_ `int32 LogActionDepth = 0;`

#### struct `FRigVMInjectNodeIntoPinAction`  
`struct FRigVMInjectNodeIntoPinAction : public FRigVMBaseAction`  
_L466-493_
- reflection: `USTRUCT()`
- inherits: `FRigVMBaseAction`
- desc: An action injecting a node into a pin
- L472 _public prototype_ `FRigVMInjectNodeIntoPinAction();`
- L473 _public prototype_ `FRigVMInjectNodeIntoPinAction(URigVMController* InController, URigVMInjectionInfo* InInjectionInfo);`
- L474 _public prototype_ `virtual ~FRigVMInjectNodeIntoPinAction() = default;`
- L475 _public function_ `virtual UScriptStruct* GetScriptStruct() const override`
- L476 _public prototype_ `virtual bool Undo() override;`
- L477 _public prototype_ `virtual bool Redo() override;`
- L480 _public member_ `FString PinPath;` — `UPROPERTY()`
- L483 _public member_ `bool bAsInput;` — `UPROPERTY()`
- L486 _public member_ `FName InputPinName;` — `UPROPERTY()`
- L489 _public member_ `FName OutputPinName;` — `UPROPERTY()`
- L492 _public member_ `FString NodePath;` — `UPROPERTY()`

#### struct `FRigVMEjectNodeFromPinAction`  
`struct FRigVMEjectNodeFromPinAction : public FRigVMInjectNodeIntoPinAction`  
_L499-511_
- reflection: `USTRUCT()`
- inherits: `FRigVMInjectNodeIntoPinAction`
- desc: An action ejecting a node from a pin
- L505 _public prototype_ `FRigVMEjectNodeFromPinAction();`
- L506 _public prototype_ `FRigVMEjectNodeFromPinAction(URigVMController* InController, URigVMInjectionInfo* InInjectionInfo);`
- L507 _public prototype_ `virtual ~FRigVMEjectNodeFromPinAction() = default;`
- L508 _public function_ `virtual UScriptStruct* GetScriptStruct() const override`
- L509 _public prototype_ `virtual bool Undo() override;`
- L510 _public prototype_ `virtual bool Redo() override;`

#### struct `FRigVMRemoveNodesAction`  
`struct FRigVMRemoveNodesAction : public FRigVMBaseAction`  
_L517-535_
- reflection: `USTRUCT()`
- inherits: `FRigVMBaseAction`
- desc: An action removing one or more nodes from the graph.
- L523 _public prototype_ `FRigVMRemoveNodesAction();`
- L524 _public prototype_ `FRigVMRemoveNodesAction(URigVMController* InController, TArray<URigVMNode*> InNodes);`
- L525 _public prototype_ `virtual ~FRigVMRemoveNodesAction() = default;`
- L526 _public function_ `virtual UScriptStruct* GetScriptStruct() const override`
- L527 _public prototype_ `virtual bool Undo() override;`
- L528 _public prototype_ `virtual bool Redo() override;`
- L531 _public member_ `TArray<FName> NodeNames;` — `UPROPERTY()`
- L534 _public member_ `FString ExportedContent;` — `UPROPERTY()`

#### struct `FRigVMSetNodeSelectionAction`  
`struct FRigVMSetNodeSelectionAction : public FRigVMBaseAction`  
_L541-559_
- reflection: `USTRUCT()`
- inherits: `FRigVMBaseAction`
- desc: An action selecting or deselecting a node in the graph.
- L547 _public prototype_ `FRigVMSetNodeSelectionAction();`
- L548 _public prototype_ `FRigVMSetNodeSelectionAction(URigVMController* InController, URigVMGraph* InGraph, TArray<FName> InNewSelection);`
- L549 _public prototype_ `virtual ~FRigVMSetNodeSelectionAction() = default;`
- L550 _public function_ `virtual UScriptStruct* GetScriptStruct() const override`
- L551 _public prototype_ `virtual bool Undo() override;`
- L552 _public prototype_ `virtual bool Redo() override;`
- L555 _public member_ `TArray<FName> NewSelection;` — `UPROPERTY()`
- L558 _public member_ `TArray<FName> OldSelection;` — `UPROPERTY()`

#### struct `FRigVMSetNodePositionAction`  
`struct FRigVMSetNodePositionAction : public FRigVMBaseAction`  
_L565-587_
- reflection: `USTRUCT()`
- inherits: `FRigVMBaseAction`
- desc: An action setting a node's position in the graph.
- L571 _public prototype_ `FRigVMSetNodePositionAction();`
- L572 _public prototype_ `FRigVMSetNodePositionAction(URigVMController* InController, URigVMNode* InNode, const FVector2D& InNewPosition);`
- L573 _public prototype_ `virtual ~FRigVMSetNodePositionAction() = default;`
- L574 _public function_ `virtual UScriptStruct* GetScriptStruct() const override`
- L575 _public prototype_ `virtual bool Merge(const FRigVMBaseAction* Other);`
- L576 _public prototype_ `virtual bool Undo() override;`
- L577 _public prototype_ `virtual bool Redo() override;`
- L580 _public member_ `FString NodePath;` — `UPROPERTY()`
- L583 _public member_ `FVector2D OldPosition;` — `UPROPERTY()`
- L586 _public member_ `FVector2D NewPosition;` — `UPROPERTY()`

#### struct `FRigVMSetNodeSizeAction`  
`struct FRigVMSetNodeSizeAction : public FRigVMBaseAction`  
_L593-615_
- reflection: `USTRUCT()`
- inherits: `FRigVMBaseAction`
- desc: An action setting a node's size in the graph.
- L599 _public prototype_ `FRigVMSetNodeSizeAction();`
- L600 _public prototype_ `FRigVMSetNodeSizeAction(URigVMController* InController, URigVMNode* InNode, const FVector2D& InNewSize);`
- L601 _public prototype_ `virtual ~FRigVMSetNodeSizeAction() = default;`
- L602 _public function_ `virtual UScriptStruct* GetScriptStruct() const override`
- L603 _public prototype_ `virtual bool Merge(const FRigVMBaseAction* Other);`
- L604 _public prototype_ `virtual bool Undo() override;`
- L605 _public prototype_ `virtual bool Redo() override;`
- L608 _public member_ `FString NodePath;` — `UPROPERTY()`
- L611 _public member_ `FVector2D OldSize;` — `UPROPERTY()`
- L614 _public member_ `FVector2D NewSize;` — `UPROPERTY()`

#### struct `FRigVMSetNodeTitleAction`  
`struct FRigVMSetNodeTitleAction : public FRigVMBaseAction`  
_L621-643_
- reflection: `USTRUCT()`
- inherits: `FRigVMBaseAction`
- desc: An action setting a node's title in the graph.
- L627 _public prototype_ `FRigVMSetNodeTitleAction();`
- L628 _public prototype_ `FRigVMSetNodeTitleAction(URigVMController* InController, URigVMNode* InNode, const FString& InNewTitle);`
- L629 _public prototype_ `virtual ~FRigVMSetNodeTitleAction() = default;`
- L630 _public function_ `virtual UScriptStruct* GetScriptStruct() const override`
- L631 _public prototype_ `virtual bool Merge(const FRigVMBaseAction* Other);`
- L632 _public prototype_ `virtual bool Undo() override;`
- L633 _public prototype_ `virtual bool Redo() override;`
- L636 _public member_ `FString NodePath;` — `UPROPERTY()`
- L639 _public member_ `FString OldTitle;` — `UPROPERTY()`
- L642 _public member_ `FString NewTitle;` — `UPROPERTY()`

#### struct `FRigVMSetNodeColorAction`  
`struct FRigVMSetNodeColorAction : public FRigVMBaseAction`  
_L649-671_
- reflection: `USTRUCT()`
- inherits: `FRigVMBaseAction`
- desc: An action setting a node's color in the graph.
- L655 _public prototype_ `FRigVMSetNodeColorAction();`
- L656 _public prototype_ `FRigVMSetNodeColorAction(URigVMController* InController, URigVMNode* InNode, const FLinearColor& InNewColor);`
- L657 _public prototype_ `virtual ~FRigVMSetNodeColorAction() = default;`
- L658 _public function_ `virtual UScriptStruct* GetScriptStruct() const override`
- L659 _public prototype_ `virtual bool Merge(const FRigVMBaseAction* Other);`
- L660 _public prototype_ `virtual bool Undo() override;`
- L661 _public prototype_ `virtual bool Redo() override;`
- L664 _public member_ `FString NodePath;` — `UPROPERTY()`
- L667 _public member_ `FLinearColor OldColor;` — `UPROPERTY()`
- L670 _public member_ `FLinearColor NewColor;` — `UPROPERTY()`

#### struct `FRigVMSetNodeCategoryAction`  
`struct FRigVMSetNodeCategoryAction : public FRigVMBaseAction`  
_L677-699_
- reflection: `USTRUCT()`
- inherits: `FRigVMBaseAction`
- desc: An action setting a node's category in the graph.
- L683 _public prototype_ `FRigVMSetNodeCategoryAction();`
- L684 _public prototype_ `FRigVMSetNodeCategoryAction(URigVMController* InController, URigVMCollapseNode* InNode, const FString& InNewCategory);`
- L685 _public prototype_ `virtual ~FRigVMSetNodeCategoryAction() = default;`
- L686 _public function_ `virtual UScriptStruct* GetScriptStruct() const override`
- L687 _public prototype_ `virtual bool Merge(const FRigVMBaseAction* Other);`
- L688 _public prototype_ `virtual bool Undo() override;`
- L689 _public prototype_ `virtual bool Redo() override;`
- L692 _public member_ `FString NodePath;` — `UPROPERTY()`
- L695 _public member_ `FString OldCategory;` — `UPROPERTY()`
- L698 _public member_ `FString NewCategory;` — `UPROPERTY()`

#### struct `FRigVMSetNodeKeywordsAction`  
`struct FRigVMSetNodeKeywordsAction : public FRigVMBaseAction`  
_L706-728_
- reflection: `USTRUCT()`
- inherits: `FRigVMBaseAction`
- desc: An action setting a node's keywords in the graph.
- L712 _public prototype_ `FRigVMSetNodeKeywordsAction();`
- L713 _public prototype_ `FRigVMSetNodeKeywordsAction(URigVMController* InController, URigVMCollapseNode* InNode, const FString& InNewKeywords);`
- L714 _public prototype_ `virtual ~FRigVMSetNodeKeywordsAction() = default;`
- L715 _public function_ `virtual UScriptStruct* GetScriptStruct() const override`
- L716 _public prototype_ `virtual bool Merge(const FRigVMBaseAction* Other);`
- L717 _public prototype_ `virtual bool Undo() override;`
- L718 _public prototype_ `virtual bool Redo() override;`
- L721 _public member_ `FString NodePath;` — `UPROPERTY()`
- L724 _public member_ `FString OldKeywords;` — `UPROPERTY()`
- L727 _public member_ `FString NewKeywords;` — `UPROPERTY()`

#### struct `FRigVMSetNodeDescriptionAction`  
`struct FRigVMSetNodeDescriptionAction : public FRigVMBaseAction`  
_L734-756_
- reflection: `USTRUCT()`
- inherits: `FRigVMBaseAction`
- desc: An action setting a node's description in the graph.
- L740 _public prototype_ `FRigVMSetNodeDescriptionAction();`
- L741 _public prototype_ `FRigVMSetNodeDescriptionAction(URigVMController* InController, URigVMCollapseNode* InNode, const FString& InNewDescription);`
- L742 _public prototype_ `virtual ~FRigVMSetNodeDescriptionAction() = default;`
- L743 _public function_ `virtual UScriptStruct* GetScriptStruct() const override`
- L744 _public prototype_ `virtual bool Merge(const FRigVMBaseAction* Other);`
- L745 _public prototype_ `virtual bool Undo() override;`
- L746 _public prototype_ `virtual bool Redo() override;`
- L749 _public member_ `FString NodePath;` — `UPROPERTY()`
- L752 _public member_ `FString OldDescription;` — `UPROPERTY()`
- L755 _public member_ `FString NewDescription;` — `UPROPERTY()`

#### struct `FRigVMSetCommentTextAction`  
`struct FRigVMSetCommentTextAction : public FRigVMBaseAction`  
_L762-801_
- reflection: `USTRUCT()`
- inherits: `FRigVMBaseAction`
- desc: An action setting a comment node's text in the graph.
- L768 _public prototype_ `FRigVMSetCommentTextAction();`
- L769 _public prototype_ `FRigVMSetCommentTextAction(URigVMController* InController, URigVMCommentNode* InNode, const FString& InNewText, const int32& InNewFontSize, const bool& bInNewBubbleVisible, const bool& bInNewColorBubble);`
- L770 _public prototype_ `virtual ~FRigVMSetCommentTextAction() = default;`
- L771 _public function_ `virtual UScriptStruct* GetScriptStruct() const override`
- L772 _public prototype_ `virtual bool Undo() override;`
- L773 _public prototype_ `virtual bool Redo() override;`
- L776 _public member_ `FString NodePath;` — `UPROPERTY()`
- L779 _public member_ `FString OldText;` — `UPROPERTY()`
- L782 _public member_ `FString NewText;` — `UPROPERTY()`
- L785 _public member_ `int32 OldFontSize;` — `UPROPERTY()`
- L788 _public member_ `int32 NewFontSize;` — `UPROPERTY()`
- L791 _public member_ `bool bOldBubbleVisible;` — `UPROPERTY()`
- L794 _public member_ `bool bNewBubbleVisible;` — `UPROPERTY()`
- L797 _public member_ `bool bOldColorBubble;` — `UPROPERTY()`
- L800 _public member_ `bool bNewColorBubble;` — `UPROPERTY()`

#### struct `FRigVMRenameVariableAction`  
`struct FRigVMRenameVariableAction : public FRigVMBaseAction`  
_L807-828_
- reflection: `USTRUCT(meta=(Deprecated = "5.1"))`
- inherits: `FRigVMBaseAction`
- desc: An action renaming a variable in the graph.
- L813 _public prototype_ `FRigVMRenameVariableAction();`
- L814 _public prototype_ `FRigVMRenameVariableAction(URigVMController* InController, const FGuid& InVariableGuid, const FName& InOldVariableName, const FName& InNewVariableName);`
- L815 _public prototype_ `virtual ~FRigVMRenameVariableAction() = default;`
- L816 _public function_ `virtual UScriptStruct* GetScriptStruct() const override`
- L817 _public prototype_ `virtual bool Undo() override;`
- L818 _public prototype_ `virtual bool Redo() override;`
- L821 _public member_ `FGuid VariableGuid;` — `UPROPERTY()`
- L824 _public member_ `FString OldVariableName;` — `UPROPERTY()`
- L827 _public member_ `FString NewVariableName;` — `UPROPERTY()`

#### struct `FRigVMSetPinExpansionAction`  
`struct FRigVMSetPinExpansionAction : public FRigVMBaseAction`  
_L834-855_
- reflection: `USTRUCT()`
- inherits: `FRigVMBaseAction`
- desc: An action setting a pin's expansion state in the graph.
- L840 _public prototype_ `FRigVMSetPinExpansionAction();`
- L841 _public prototype_ `FRigVMSetPinExpansionAction(URigVMController* InController, URigVMPin* InPin, bool bNewIsExpanded);`
- L842 _public prototype_ `virtual ~FRigVMSetPinExpansionAction() = default;`
- L843 _public function_ `virtual UScriptStruct* GetScriptStruct() const override`
- L844 _public prototype_ `virtual bool Undo() override;`
- L845 _public prototype_ `virtual bool Redo() override;`
- L848 _public member_ `FString PinPath;` — `UPROPERTY()`
- L851 _public member_ `bool OldIsExpanded;` — `UPROPERTY()`
- L854 _public member_ `bool NewIsExpanded;` — `UPROPERTY()`

#### struct `FRigVMSetPinWatchAction`  
`struct FRigVMSetPinWatchAction : public FRigVMBaseAction`  
_L861-882_
- reflection: `USTRUCT()`
- inherits: `FRigVMBaseAction`
- desc: An action setting a pin's watch state in the graph.
- L867 _public prototype_ `FRigVMSetPinWatchAction();`
- L868 _public prototype_ `FRigVMSetPinWatchAction(URigVMController* InController, URigVMPin* InPin, bool bNewIsWatched);`
- L869 _public prototype_ `virtual ~FRigVMSetPinWatchAction() = default;`
- L870 _public function_ `virtual UScriptStruct* GetScriptStruct() const override`
- L871 _public prototype_ `virtual bool Undo() override;`
- L872 _public prototype_ `virtual bool Redo() override;`
- L875 _public member_ `FString PinPath;` — `UPROPERTY()`
- L878 _public member_ `bool OldIsWatched;` — `UPROPERTY()`
- L881 _public member_ `bool NewIsWatched;` — `UPROPERTY()`

#### struct `FRigVMSetPinDisplayNameAction`  
`struct FRigVMSetPinDisplayNameAction : public FRigVMBaseAction`  
_L888-909_
- reflection: `USTRUCT()`
- inherits: `FRigVMBaseAction`
- desc: An action setting a pin's display name in the graph.
- L894 _public prototype_ `FRigVMSetPinDisplayNameAction();`
- L895 _public prototype_ `FRigVMSetPinDisplayNameAction(URigVMController* InController, URigVMPin* InPin, const FString& InNewDisplayName);`
- L896 _public prototype_ `virtual ~FRigVMSetPinDisplayNameAction() = default;`
- L897 _public function_ `virtual UScriptStruct* GetScriptStruct() const override`
- L898 _public prototype_ `virtual bool Undo() override;`
- L899 _public prototype_ `virtual bool Redo() override;`
- L902 _public member_ `FString PinPath;` — `UPROPERTY()`
- L905 _public member_ `FString OldDisplayName;` — `UPROPERTY()`
- L908 _public member_ `FString NewDisplayName;` — `UPROPERTY()`

#### struct `FRigVMSetPinCategoryAction`  
`struct FRigVMSetPinCategoryAction : public FRigVMBaseAction`  
_L915-939_
- reflection: `USTRUCT()`
- inherits: `FRigVMBaseAction`
- desc: An action setting a pin's category in the graph.
- L921 _public prototype_ `FRigVMSetPinCategoryAction();`
- L922 _public prototype_ `FRigVMSetPinCategoryAction(URigVMController* InController, URigVMPin* InPin, const FString& InNewCategory);`
- L923 _public prototype_ `virtual ~FRigVMSetPinCategoryAction() = default;`
- L924 _public function_ `virtual UScriptStruct* GetScriptStruct() const override`
- L925 _public prototype_ `virtual bool Undo() override;`
- L926 _public prototype_ `virtual bool Redo() override;`
- L929 _public member_ `FString PinPath;` — `UPROPERTY()`
- L932 _public member_ `FString OldCategory;` — `UPROPERTY()`
- L935 _public member_ `int32 OldPinIndex;` — `UPROPERTY()`
- L938 _public member_ `FString NewCategory;` — `UPROPERTY()`

#### struct `FRigVMChangeNodePinCategoriesAction`  
`struct FRigVMChangeNodePinCategoriesAction : public FRigVMBaseAction`  
_L945-968_
- reflection: `USTRUCT()`
- inherits: `FRigVMBaseAction`
- desc: An action setting a pin's category in the graph.
- L951 _public prototype_ `FRigVMChangeNodePinCategoriesAction();`
- L952 _public prototype_ `FRigVMChangeNodePinCategoriesAction(URigVMController* InController, const URigVMNode* InNode);`
- L953 _public prototype_ `virtual ~FRigVMChangeNodePinCategoriesAction() = default;`
- L954 _public function_ `virtual UScriptStruct* GetScriptStruct() const override`
- L955 _public prototype_ `virtual bool Undo() override;`
- L956 _public prototype_ `virtual bool Redo() override;`
- L958 _public prototype_ `void UpdateAfterModification(const URigVMNode* InNode);`
- L961 _public member_ `FString NodeName;` — `UPROPERTY()`
- L964 _public member_ `TArray<FString> OldCategories;` — `UPROPERTY()`
- L967 _public member_ `TArray<FString> NewCategories;` — `UPROPERTY()`

#### struct `FRigVMSetPinCategoryExpansionAction`  
`struct FRigVMSetPinCategoryExpansionAction : public FRigVMBaseAction`  
_L974-995_
- reflection: `USTRUCT()`
- inherits: `FRigVMBaseAction`
- desc: An action to change the expansion on a pin's category in the graph.
- L980 _public prototype_ `FRigVMSetPinCategoryExpansionAction();`
- L981 _public prototype_ `FRigVMSetPinCategoryExpansionAction(URigVMController* InController, const URigVMNode* InNode, const FString& InPinCategory);`
- L982 _public prototype_ `virtual ~FRigVMSetPinCategoryExpansionAction() = default;`
- L983 _public function_ `virtual UScriptStruct* GetScriptStruct() const override`
- L984 _public prototype_ `virtual bool Undo() override;`
- L985 _public prototype_ `virtual bool Redo() override;`
- L988 _public member_ `FString NodeName;` — `UPROPERTY()`
- L991 _public member_ `FString PinCategory;` — `UPROPERTY()`
- L994 _public member_ `bool bOldExpansionState;` — `UPROPERTY()`

#### struct `FRigVMSetPinIndexInCategoryAction`  
`struct FRigVMSetPinIndexInCategoryAction : public FRigVMBaseAction`  
_L1001-1022_
- reflection: `USTRUCT()`
- inherits: `FRigVMBaseAction`
- desc: An action setting a pin's index within a category.
- L1007 _public prototype_ `FRigVMSetPinIndexInCategoryAction();`
- L1008 _public prototype_ `FRigVMSetPinIndexInCategoryAction(URigVMController* InController, URigVMPin* InPin, int32 InNewIndexInCategory);`
- L1009 _public prototype_ `virtual ~FRigVMSetPinIndexInCategoryAction() = default;`
- L1010 _public function_ `virtual UScriptStruct* GetScriptStruct() const override`
- L1011 _public prototype_ `virtual bool Undo() override;`
- L1012 _public prototype_ `virtual bool Redo() override;`
- L1015 _public member_ `FString PinPath;` — `UPROPERTY()`
- L1018 _public member_ `int32 OldIndexInCategory;` — `UPROPERTY()`
- L1021 _public member_ `int32 NewIndexInCategory;` — `UPROPERTY()`

#### struct `FRigVMSetPinDefaultValueAction`  
`struct FRigVMSetPinDefaultValueAction : public FRigVMBaseAction`  
_L1028-1056_
- reflection: `USTRUCT()`
- inherits: `FRigVMBaseAction`
- desc: An action setting a pin's default value in the graph.
- L1034 _public prototype_ `FRigVMSetPinDefaultValueAction();`
- L1035 _public prototype_ `FRigVMSetPinDefaultValueAction(URigVMController* InController, URigVMPin* InPin, const FString& InNewDefaultValue);`
- L1036 _public prototype_ `virtual ~FRigVMSetPinDefaultValueAction() = default;`
- L1037 _public function_ `virtual UScriptStruct* GetScriptStruct() const override`
- L1038 _public prototype_ `virtual bool Merge(const FRigVMBaseAction* Other);`
- L1039 _public prototype_ `virtual bool Undo() override;`
- L1040 _public prototype_ `virtual bool Redo() override;`
- L1043 _public member_ `FString PinPath;` — `UPROPERTY()`
- L1046 _public member_ `FString OldDefaultValue;` — `UPROPERTY()`
- L1049 _public member_ `FString NewDefaultValue;` — `UPROPERTY()`
- L1052 _public member_ `ERigVMPinDefaultValueType OldDefaultValueType;` — `UPROPERTY()`
- L1055 _public member_ `ERigVMPinDefaultValueType NewDefaultValueType;` — `UPROPERTY()`

#### struct `FRigVMInsertArrayPinAction`  
`struct FRigVMInsertArrayPinAction : public FRigVMBaseAction`  
_L1062-1086_
- reflection: `USTRUCT()`
- inherits: `FRigVMBaseAction`
- desc: An action inserting a new array pin in the graph.
- L1068 _public prototype_ `FRigVMInsertArrayPinAction();`
- L1069 _public prototype_ `FRigVMInsertArrayPinAction(URigVMController* InController, URigVMPin* InArrayPin, int32 InIndex, const FString& InNewDefaultValue, const ERigVMPinDefaultValueType& InNewDefaultValueType);`
- L1070 _public prototype_ `virtual ~FRigVMInsertArrayPinAction() = default;`
- L1071 _public function_ `virtual UScriptStruct* GetScriptStruct() const override`
- L1072 _public prototype_ `virtual bool Undo() override;`
- L1073 _public prototype_ `virtual bool Redo() override;`
- L1076 _public member_ `FString ArrayPinPath;` — `UPROPERTY()`
- L1079 _public member_ `int32 Index;` — `UPROPERTY()`
- L1082 _public member_ `FString NewDefaultValue;` — `UPROPERTY()`
- L1085 _public member_ `ERigVMPinDefaultValueType NewDefaultValueType;` — `UPROPERTY()`

#### struct `FRigVMRemoveArrayPinAction`  
`struct FRigVMRemoveArrayPinAction : public FRigVMBaseAction`  
_L1092-1116_
- reflection: `USTRUCT()`
- inherits: `FRigVMBaseAction`
- desc: An action removing an array pin from the graph.
- L1098 _public prototype_ `FRigVMRemoveArrayPinAction();`
- L1099 _public prototype_ `FRigVMRemoveArrayPinAction(URigVMController* InController, URigVMPin* InArrayElementPin);`
- L1100 _public prototype_ `virtual ~FRigVMRemoveArrayPinAction() = default;`
- L1101 _public function_ `virtual UScriptStruct* GetScriptStruct() const override`
- L1102 _public prototype_ `virtual bool Undo() override;`
- L1103 _public prototype_ `virtual bool Redo() override;`
- L1106 _public member_ `FString ArrayPinPath;` — `UPROPERTY()`
- L1109 _public member_ `int32 Index;` — `UPROPERTY()`
- L1112 _public member_ `FString DefaultValue;` — `UPROPERTY()`
- L1115 _public member_ `ERigVMPinDefaultValueType DefaultValueType;` — `UPROPERTY()`

#### struct `FRigVMAddLinkAction`  
`struct FRigVMAddLinkAction : public FRigVMBaseAction`  
_L1122-1140_
- reflection: `USTRUCT()`
- inherits: `FRigVMBaseAction`
- desc: An action adding a new link to the graph.
- L1128 _public prototype_ `FRigVMAddLinkAction();`
- L1129 _public prototype_ `FRigVMAddLinkAction(URigVMController* InController, URigVMPin* InOutputPin, URigVMPin* InInputPin);`
- L1130 _public prototype_ `virtual ~FRigVMAddLinkAction() = default;`
- L1131 _public function_ `virtual UScriptStruct* GetScriptStruct() const override`
- L1132 _public prototype_ `virtual bool Undo() override;`
- L1133 _public prototype_ `virtual bool Redo() override;`
- L1136 _public member_ `FString OutputPinPath;` — `UPROPERTY()`
- L1139 _public member_ `FString InputPinPath;` — `UPROPERTY()`

#### struct `FRigVMBreakLinkAction`  
`struct FRigVMBreakLinkAction : public FRigVMBaseAction`  
_L1146-1167_
- reflection: `USTRUCT()`
- inherits: `FRigVMBaseAction`
- desc: An action removing a link from the graph.
- L1152 _public prototype_ `FRigVMBreakLinkAction();`
- L1153 _public prototype_ `FRigVMBreakLinkAction(URigVMController* InController, URigVMPin* InOutputPin, URigVMPin* InInputPin);`
- L1154 _public prototype_ `virtual ~FRigVMBreakLinkAction() = default;`
- L1155 _public function_ `virtual UScriptStruct* GetScriptStruct() const override`
- L1156 _public prototype_ `virtual bool Undo() override;`
- L1157 _public prototype_ `virtual bool Redo() override;`
- L1160 _public member_ `FSoftObjectPath GraphPath;` — `UPROPERTY()`
- L1163 _public member_ `FString OutputPinPath;` — `UPROPERTY()`
- L1166 _public member_ `FString InputPinPath;` — `UPROPERTY()`

#### struct `FRigVMChangePinTypeAction`  
`struct FRigVMChangePinTypeAction : public FRigVMBaseAction`  
_L1173-1203_
- reflection: `USTRUCT()`
- inherits: `FRigVMBaseAction`
- desc: An action changing a pin type
- L1179 _public prototype_ `FRigVMChangePinTypeAction();`
- L1180 _public prototype_ `FRigVMChangePinTypeAction(URigVMController* InController, URigVMPin* InPin, int32 InTypeIndex, bool InSetupOrphanPins, bool InBreakLinks, bool InRemoveSubPins);`
- L1181 _public prototype_ `virtual ~FRigVMChangePinTypeAction() = default;`
- L1182 _public function_ `virtual UScriptStruct* GetScriptStruct() const override`
- L1183 _public prototype_ `virtual bool Undo() override;`
- L1184 _public prototype_ `virtual bool Redo() override;`
- L1187 _public member_ `FString PinPath;` — `UPROPERTY()`
- L1190 _public member_ `int32 OldTypeIndex;` — `UPROPERTY()`
- L1193 _public member_ `int32 NewTypeIndex;` — `UPROPERTY()`
- L1196 _public member_ `bool bSetupOrphanPins;` — `UPROPERTY()`
- L1199 _public member_ `bool bBreakLinks;` — `UPROPERTY()`
- L1202 _public member_ `bool bRemoveSubPins;` — `UPROPERTY()`

#### struct `FRigVMCollapseNodesAction`  
`struct FRigVMCollapseNodesAction : public FRigVMBaseAction`  
_L1209-1233_
- reflection: `USTRUCT()`
- inherits: `FRigVMBaseAction`
- desc: An action to collapse a selection of nodes
- L1215 _public prototype_ `FRigVMCollapseNodesAction();`
- L1216 _public prototype_ `FRigVMCollapseNodesAction(URigVMController* InController, const TArray<URigVMNode*>& InNodes, const FString& InNodePath, const bool bIsAggregate);`
- L1217 _public prototype_ `virtual ~FRigVMCollapseNodesAction() = default;`
- L1218 _public function_ `virtual UScriptStruct* GetScriptStruct() const override`
- L1219 _public prototype_ `virtual bool Undo() override;`
- L1220 _public prototype_ `virtual bool Redo() override;`
- L1223 _public member_ `FString LibraryNodePath;` — `UPROPERTY()`
- L1226 _public member_ `FString CollapsedNodesContent;` — `UPROPERTY()`
- L1229 _public member_ `TArray<FString> CollapsedNodesPaths;` — `UPROPERTY()`
- L1232 _public member_ `bool bIsAggregate;` — `UPROPERTY()`

#### struct `FRigVMExpandNodeAction`  
`struct FRigVMExpandNodeAction : public FRigVMBaseAction`  
_L1239-1260_
- reflection: `USTRUCT()`
- inherits: `FRigVMBaseAction`
- desc: An action to expand a library node into its content
- L1245 _public prototype_ `FRigVMExpandNodeAction();`
- L1246 _public prototype_ `FRigVMExpandNodeAction(URigVMController* InController, URigVMLibraryNode* InLibraryNode);`
- L1247 _public prototype_ `virtual ~FRigVMExpandNodeAction() = default;`
- L1248 _public function_ `virtual UScriptStruct* GetScriptStruct() const override`
- L1249 _public prototype_ `virtual bool Undo() override;`
- L1250 _public prototype_ `virtual bool Redo() override;`
- L1253 _public member_ `FString LibraryNodePath;` — `UPROPERTY()`
- L1256 _public member_ `FString LibraryNodeContent;` — `UPROPERTY()`
- L1259 _public member_ `TArray<FString> ExpandedNodePaths;` — `UPROPERTY()`

#### struct `FRigVMRenameNodeAction`  
`struct FRigVMRenameNodeAction : public FRigVMBaseAction`  
_L1266-1284_
- reflection: `USTRUCT()`
- inherits: `FRigVMBaseAction`
- desc: An action renaming a node in the graph.
- L1272 _public prototype_ `FRigVMRenameNodeAction();`
- L1273 _public prototype_ `FRigVMRenameNodeAction(URigVMController* InController, const FName& InOldNodeName, const FName& InNewNodeName);`
- L1274 _public prototype_ `virtual ~FRigVMRenameNodeAction() = default;`
- L1275 _public function_ `virtual UScriptStruct* GetScriptStruct() const override`
- L1276 _public prototype_ `virtual bool Undo() override;`
- L1277 _public prototype_ `virtual bool Redo() override;`
- L1280 _public member_ `FString OldNodeName;` — `UPROPERTY()`
- L1283 _public member_ `FString NewNodeName;` — `UPROPERTY()`

#### struct `FRigVMAddExposedPinAction`  
`struct FRigVMAddExposedPinAction : public FRigVMBaseAction`  
_L1290-1317_
- reflection: `USTRUCT()`
- inherits: `FRigVMBaseAction`
- desc: An action exposing a pin as a parameter
- L1296 _public prototype_ `FRigVMAddExposedPinAction();`
- L1297 _public prototype_ `FRigVMAddExposedPinAction(URigVMController* InController, URigVMPin* InPin);`
- L1298 _public prototype_ `virtual ~FRigVMAddExposedPinAction() = default;`
- L1299 _public function_ `virtual UScriptStruct* GetScriptStruct() const override`
- L1300 _public prototype_ `virtual bool Undo() override;`
- L1301 _public prototype_ `virtual bool Redo() override;`
- L1304 _public member_ `FString PinName;` — `UPROPERTY()`
- L1307 _public member_ `ERigVMPinDirection Direction;` — `UPROPERTY()`
- L1310 _public member_ `FString CPPType;` — `UPROPERTY()`
- L1313 _public member_ `FString CPPTypeObjectPath;` — `UPROPERTY()`
- L1316 _public member_ `FString DefaultValue;` — `UPROPERTY()`

#### struct `FRigVMRemoveExposedPinAction`  
`struct FRigVMRemoveExposedPinAction : public FRigVMBaseAction`  
_L1323-1353_
- reflection: `USTRUCT()`
- inherits: `FRigVMBaseAction`
- desc: An action exposing a pin as a parameter
- L1329 _public prototype_ `FRigVMRemoveExposedPinAction();`
- L1330 _public prototype_ `FRigVMRemoveExposedPinAction(URigVMController* InController, URigVMPin* InPin);`
- L1331 _public prototype_ `virtual ~FRigVMRemoveExposedPinAction() = default;`
- L1332 _public function_ `virtual UScriptStruct* GetScriptStruct() const override`
- L1333 _public prototype_ `virtual bool Undo() override;`
- L1334 _public prototype_ `virtual bool Redo() override;`
- L1337 _public member_ `FString PinName;` — `UPROPERTY()`
- L1340 _public member_ `ERigVMPinDirection Direction;` — `UPROPERTY()`
- L1343 _public member_ `FString CPPType;` — `UPROPERTY()`
- L1346 _public member_ `FString CPPTypeObjectPath;` — `UPROPERTY()`
- L1349 _public member_ `FString DefaultValue;` — `UPROPERTY()`
- L1352 _public member_ `int32 PinIndex;` — `UPROPERTY()`

#### struct `FRigVMRenameExposedPinAction`  
`struct FRigVMRenameExposedPinAction : public FRigVMBaseAction`  
_L1359-1377_
- reflection: `USTRUCT()`
- inherits: `FRigVMBaseAction`
- desc: An action renaming an exposed in the graph.
- L1365 _public prototype_ `FRigVMRenameExposedPinAction();`
- L1366 _public prototype_ `FRigVMRenameExposedPinAction(URigVMController* InController, const FName& InOldPinName, const FName& InNewPinName);`
- L1367 _public prototype_ `virtual ~FRigVMRenameExposedPinAction() = default;`
- L1368 _public function_ `virtual UScriptStruct* GetScriptStruct() const override`
- L1369 _public prototype_ `virtual bool Undo() override;`
- L1370 _public prototype_ `virtual bool Redo() override;`
- L1373 _public member_ `FString OldPinName;` — `UPROPERTY()`
- L1376 _public member_ `FString NewPinName;` — `UPROPERTY()`

#### struct `FRigVMSetPinIndexAction`  
`struct FRigVMSetPinIndexAction : public FRigVMBaseAction`  
_L1383-1404_
- reflection: `USTRUCT()`
- inherits: `FRigVMBaseAction`
- desc: An action to reorder pins on a node
- L1389 _public prototype_ `FRigVMSetPinIndexAction();`
- L1390 _public prototype_ `FRigVMSetPinIndexAction(URigVMController* InController, URigVMPin* InPin, int32 InNewIndex);`
- L1391 _public prototype_ `virtual ~FRigVMSetPinIndexAction() = default;`
- L1392 _public function_ `virtual UScriptStruct* GetScriptStruct() const override`
- L1393 _public prototype_ `virtual bool Undo() override;`
- L1394 _public prototype_ `virtual bool Redo() override;`
- L1397 _public member_ `FString PinPath;` — `UPROPERTY()`
- L1400 _public member_ `int32 OldIndex;` — `UPROPERTY()`
- L1403 _public member_ `int32 NewIndex;` — `UPROPERTY()`

#### struct `FRigVMMarkExposedPinAsInputVariableAction`  
`struct FRigVMMarkExposedPinAsInputVariableAction : public FRigVMBaseAction`  
_L1410-1431_
- reflection: `USTRUCT()`
- inherits: `FRigVMBaseAction`
- desc: An action to mark an exposed pin as an input variable
- L1416 _public prototype_ `FRigVMMarkExposedPinAsInputVariableAction();`
- L1417 _public prototype_ `FRigVMMarkExposedPinAsInputVariableAction(URigVMController* InController, URigVMPin* InPin, bool bNewDefinedAsExternalVariableState);`
- L1418 _public prototype_ `virtual ~FRigVMMarkExposedPinAsInputVariableAction() = default;`
- L1419 _public function_ `virtual UScriptStruct* GetScriptStruct() const override`
- L1420 _public prototype_ `virtual bool Undo() override;`
- L1421 _public prototype_ `virtual bool Redo() override;`
- L1424 _public member_ `FString PinPath;` — `UPROPERTY()`
- L1427 _public member_ `bool OldState;` — `UPROPERTY()`
- L1430 _public member_ `bool NewState;` — `UPROPERTY()`

#### struct `FRigVMAddLocalVariableAction`  
`struct FRigVMAddLocalVariableAction : public FRigVMBaseAction`  
_L1437-1452_
- reflection: `USTRUCT()`
- inherits: `FRigVMBaseAction`
- desc: An action to add a local variable.
- L1443 _public prototype_ `FRigVMAddLocalVariableAction();`
- L1444 _public prototype_ `FRigVMAddLocalVariableAction(URigVMController* InController, const FRigVMGraphVariableDescription& InLocalVariable);`
- L1445 _public prototype_ `virtual ~FRigVMAddLocalVariableAction() = default;`
- L1446 _public function_ `virtual UScriptStruct* GetScriptStruct() const override`
- L1447 _public prototype_ `virtual bool Undo() override;`
- L1448 _public prototype_ `virtual bool Redo() override;`
- L1451 _public member_ `FRigVMGraphVariableDescription LocalVariable;` — `UPROPERTY()`

#### struct `FRigVMRemoveLocalVariableAction`  
`struct FRigVMRemoveLocalVariableAction : public FRigVMBaseAction`  
_L1458-1473_
- reflection: `USTRUCT()`
- inherits: `FRigVMBaseAction`
- desc: An action to remove a local variable.
- L1464 _public prototype_ `FRigVMRemoveLocalVariableAction();`
- L1465 _public prototype_ `FRigVMRemoveLocalVariableAction(URigVMController* InController, const FRigVMGraphVariableDescription& InLocalVariable);`
- L1466 _public prototype_ `virtual ~FRigVMRemoveLocalVariableAction() = default;`
- L1467 _public function_ `virtual UScriptStruct* GetScriptStruct() const override`
- L1468 _public prototype_ `virtual bool Undo() override;`
- L1469 _public prototype_ `virtual bool Redo() override;`
- L1472 _public member_ `FRigVMGraphVariableDescription LocalVariable;` — `UPROPERTY()`

#### struct `FRigVMRenameLocalVariableAction`  
`struct FRigVMRenameLocalVariableAction : public FRigVMBaseAction`  
_L1479-1497_
- reflection: `USTRUCT()`
- inherits: `FRigVMBaseAction`
- desc: An action to rename a local variable.
- L1485 _public prototype_ `FRigVMRenameLocalVariableAction();`
- L1486 _public prototype_ `FRigVMRenameLocalVariableAction(URigVMController* InController, const FName& InOldName, const FName& InNewName);`
- L1487 _public prototype_ `virtual ~FRigVMRenameLocalVariableAction() = default;`
- L1488 _public function_ `virtual UScriptStruct* GetScriptStruct() const override`
- L1489 _public prototype_ `virtual bool Undo() override;`
- L1490 _public prototype_ `virtual bool Redo() override;`
- L1493 _public member_ `FName OldVariableName;` — `UPROPERTY()`
- L1496 _public member_ `FName NewVariableName;` — `UPROPERTY()`

#### struct `FRigVMChangeLocalVariableTypeAction`  
`struct FRigVMChangeLocalVariableTypeAction : public FRigVMBaseAction`  
_L1503-1523_
- reflection: `USTRUCT()`
- inherits: `FRigVMBaseAction`
- desc: An action to change the type of a local variable.
- L1508 _public prototype_ `FRigVMChangeLocalVariableTypeAction();`
- L1509 _public prototype_ `FRigVMChangeLocalVariableTypeAction(URigVMController* InController, const FRigVMGraphVariableDescription& InLocalVariable, const FString& InCPPType, UObject* InCPPTypeObject);`
- L1510 _public prototype_ `virtual ~FRigVMChangeLocalVariableTypeAction() = default;`
- L1511 _public function_ `virtual UScriptStruct* GetScriptStruct() const override`
- L1512 _public prototype_ `virtual bool Undo() override;`
- L1513 _public prototype_ `virtual bool Redo() override;`
- L1516 _public member_ `FRigVMGraphVariableDescription LocalVariable;` — `UPROPERTY()`
- L1519 _public member_ `FString CPPType;` — `UPROPERTY()`
- L1522 _public member_ `TObjectPtr<UObject> CPPTypeObject;` — `UPROPERTY()`

#### struct `FRigVMChangeLocalVariableDefaultValueAction`  
`struct FRigVMChangeLocalVariableDefaultValueAction : public FRigVMBaseAction`  
_L1529-1546_
- reflection: `USTRUCT()`
- inherits: `FRigVMBaseAction`
- desc: An action to change the default value of a local variable.
- L1534 _public prototype_ `FRigVMChangeLocalVariableDefaultValueAction();`
- L1535 _public prototype_ `FRigVMChangeLocalVariableDefaultValueAction(URigVMController* InController, const FRigVMGraphVariableDescription& InLocalVariable, const FString& InDefaultValue);`
- L1536 _public prototype_ `virtual ~FRigVMChangeLocalVariableDefaultValueAction() = default;`
- L1537 _public function_ `virtual UScriptStruct* GetScriptStruct() const override`
- L1538 _public prototype_ `virtual bool Undo() override;`
- L1539 _public prototype_ `virtual bool Redo() override;`
- L1542 _public member_ `FRigVMGraphVariableDescription LocalVariable;` — `UPROPERTY()`
- L1545 _public member_ `FString DefaultValue;` — `UPROPERTY()`

#### struct `FRigVMSetLocalVariableIndexAction`  
`struct FRigVMSetLocalVariableIndexAction : public FRigVMBaseAction`  
_L1552-1572_
- reflection: `USTRUCT()`
- inherits: `FRigVMBaseAction`
- desc: An action to reorder a local variable to a new index
- L1557 _public prototype_ `FRigVMSetLocalVariableIndexAction();`
- L1558 _public prototype_ `FRigVMSetLocalVariableIndexAction(URigVMController* InController, const FGuid& InVariableGuid, int32 InOldIndex, int32 InNewIndex);`
- L1559 _public prototype_ `virtual ~FRigVMSetLocalVariableIndexAction() = default;`
- L1560 _public function_ `virtual UScriptStruct* GetScriptStruct() const override`
- L1561 _public prototype_ `virtual bool Undo() override;`
- L1562 _public prototype_ `virtual bool Redo() override;`
- L1565 _public member_ `FGuid VariableGuid;` — `UPROPERTY()`
- L1568 _public member_ `int32 OldIndex;` — `UPROPERTY()`
- L1571 _public member_ `int32 NewIndex;` — `UPROPERTY()`

#### struct `FRigVMPromoteNodeAction`  
`struct FRigVMPromoteNodeAction : public FRigVMBaseAction`  
_L1578-1599_
- reflection: `USTRUCT()`
- inherits: `FRigVMBaseAction`
- desc: An action to promote a function to collapse node or vice versa
- L1584 _public prototype_ `FRigVMPromoteNodeAction();`
- L1585 _public prototype_ `FRigVMPromoteNodeAction(URigVMController* InController, const URigVMNode* InNodeToPromote, const FString& InNodePath, const FString& InFunctionDefinitionPath);`
- L1586 _public prototype_ `virtual ~FRigVMPromoteNodeAction() = default;`
- L1587 _public function_ `virtual UScriptStruct* GetScriptStruct() const override`
- L1588 _public prototype_ `virtual bool Undo() override;`
- L1589 _public prototype_ `virtual bool Redo() override;`
- L1592 _public member_ `FString LibraryNodePath;` — `UPROPERTY()`
- L1595 _public member_ `FString FunctionDefinitionPath;` — `UPROPERTY()`
- L1598 _public member_ `bool bFromFunctionToCollapseNode;` — `UPROPERTY()`

#### struct `FRigVMMarkFunctionPublicAction`  
`struct FRigVMMarkFunctionPublicAction : public FRigVMBaseAction`  
_L1605-1623_
- reflection: `USTRUCT()`
- inherits: `FRigVMBaseAction`
- desc: An action marking a function as public/private.
- L1611 _public prototype_ `FRigVMMarkFunctionPublicAction();`
- L1612 _public prototype_ `FRigVMMarkFunctionPublicAction(URigVMController* InController, const FName& InFunctionName, bool bInIsPublic);`
- L1613 _public prototype_ `virtual ~FRigVMMarkFunctionPublicAction() = default;`
- L1614 _public function_ `virtual UScriptStruct* GetScriptStruct() const override`
- L1615 _public prototype_ `virtual bool Undo() override;`
- L1616 _public prototype_ `virtual bool Redo() override;`
- L1619 _public member_ `FName FunctionName;` — `UPROPERTY()`
- L1622 _public member_ `bool bIsPublic;` — `UPROPERTY()`

#### struct `FRigVMCreateFunctionVariantAction`  
`struct FRigVMCreateFunctionVariantAction : public FRigVMBaseAction`  
_L1629-1647_
- reflection: `USTRUCT()`
- inherits: `FRigVMBaseAction`
- desc: An action creating a function variant
- L1635 _public prototype_ `FRigVMCreateFunctionVariantAction();`
- L1636 _public prototype_ `FRigVMCreateFunctionVariantAction(URigVMController* InController, const FName& InFunctionName, const FName& InNewFunctionName);`
- L1637 _public prototype_ `virtual ~FRigVMCreateFunctionVariantAction() = default;`
- L1638 _public function_ `virtual UScriptStruct* GetScriptStruct() const override`
- L1639 _public prototype_ `virtual bool Undo() override;`
- L1640 _public prototype_ `virtual bool Redo() override;`
- L1643 _public member_ `FName FunctionName;` — `UPROPERTY()`
- L1646 _public member_ `FName NewFunctionName;` — `UPROPERTY()`

#### struct `FRigVMAddFunctionVariantTagAction`  
`struct FRigVMAddFunctionVariantTagAction : public FRigVMBaseAction`  
_L1653-1671_
- reflection: `USTRUCT()`
- inherits: `FRigVMBaseAction`
- desc: An action adding a tag to a function variant
- L1659 _public prototype_ `FRigVMAddFunctionVariantTagAction();`
- L1660 _public prototype_ `FRigVMAddFunctionVariantTagAction(URigVMController* InController, const FName& InFunctionName, const FRigVMTag& InTag);`
- L1661 _public prototype_ `virtual ~FRigVMAddFunctionVariantTagAction() = default;`
- L1662 _public function_ `virtual UScriptStruct* GetScriptStruct() const override`
- L1663 _public prototype_ `virtual bool Undo() override;`
- L1664 _public prototype_ `virtual bool Redo() override;`
- L1667 _public member_ `FName FunctionName;` — `UPROPERTY()`
- L1670 _public member_ `FRigVMTag FunctionTag;` — `UPROPERTY()`

#### struct `FRigVMRemoveFunctionVariantTagAction`  
`struct FRigVMRemoveFunctionVariantTagAction : public FRigVMBaseAction`  
_L1677-1695_
- reflection: `USTRUCT()`
- inherits: `FRigVMBaseAction`
- desc: An action removing a tag from a function variant
- L1683 _public prototype_ `FRigVMRemoveFunctionVariantTagAction();`
- L1684 _public prototype_ `FRigVMRemoveFunctionVariantTagAction(URigVMController* InController, const FName& InFunctionName, const FName& InTagName);`
- L1685 _public prototype_ `virtual ~FRigVMRemoveFunctionVariantTagAction() = default;`
- L1686 _public function_ `virtual UScriptStruct* GetScriptStruct() const override`
- L1687 _public prototype_ `virtual bool Undo() override;`
- L1688 _public prototype_ `virtual bool Redo() override;`
- L1691 _public member_ `FName FunctionName;` — `UPROPERTY()`
- L1694 _public member_ `FRigVMTag FunctionTag;` — `UPROPERTY()`

#### struct `FRigVMImportFromTextAction`  
`struct FRigVMImportFromTextAction : public FRigVMBaseAction`  
_L1701-1722_
- reflection: `USTRUCT()`
- inherits: `FRigVMBaseAction`
- desc: An action importing nodes and links from text
- L1707 _public prototype_ `FRigVMImportFromTextAction();`
- L1708 _public prototype_ `FRigVMImportFromTextAction(URigVMController* InController, const FString& InContent, const TArray<FName>& InTopLevelNodeNames);`
- L1709 _public prototype_ `FRigVMImportFromTextAction(URigVMController* InController, URigVMNode* InNode, bool bIncludeExteriorLinks = true);`
- L1710 _public prototype_ `FRigVMImportFromTextAction(URigVMController* InController, const TArray<URigVMNode*>& InNodes, bool bIncludeExteriorLinks = true);`
- L1711 _public prototype_ `void SetContent(const TArray<URigVMNode*>& InNodes, bool bIncludeExteriorLinks = true);`
- L1712 _public prototype_ `virtual ~FRigVMImportFromTextAction() = default;`
- L1713 _public function_ `virtual UScriptStruct* GetScriptStruct() const override`
- L1714 _public prototype_ `virtual bool Undo() override;`
- L1715 _public prototype_ `virtual bool Redo() override;`
- L1718 _public member_ `FString Content;` — `UPROPERTY()`
- L1721 _public member_ `TArray<FName> TopLevelNodeNames;` — `UPROPERTY()`

#### struct `FRigVMReplaceNodesAction`  
`struct FRigVMReplaceNodesAction : public FRigVMBaseAction`  
_L1728-1740_
- reflection: `USTRUCT()`
- inherits: `FRigVMBaseAction`
- desc: An action to add store / restore a single node
- L1734 _public prototype_ `FRigVMReplaceNodesAction();`
- L1735 _public prototype_ `FRigVMReplaceNodesAction(URigVMController* InController, const TArray<URigVMNode*>& InNodes);`
- L1736 _public prototype_ `virtual ~FRigVMReplaceNodesAction() = default;`
- L1737 _public function_ `virtual UScriptStruct* GetScriptStruct() const override`
- L1738 _public prototype_ `virtual bool Undo() override;`
- L1739 _public prototype_ `virtual bool Redo() override;`

#### struct `FRigVMAddTraitAction`  
`struct FRigVMAddTraitAction : public FRigVMBaseAction`  
_L1746-1773_
- reflection: `USTRUCT()`
- inherits: `FRigVMBaseAction`
- desc: An action to add a trait to a node
- L1752 _public prototype_ `FRigVMAddTraitAction();`
- L1753 _public prototype_ `FRigVMAddTraitAction(URigVMController* InController, const URigVMNode* InNode, const FName& InTraitName, const UScriptStruct* InTraitScriptStruct, const FString& InTraitDefault, int32 InPinIndex);`
- L1754 _public prototype_ `virtual ~FRigVMAddTraitAction() = default;`
- L1755 _public function_ `virtual UScriptStruct* GetScriptStruct() const override`
- L1756 _public prototype_ `virtual bool Undo() override;`
- L1757 _public prototype_ `virtual bool Redo() override;`
- L1760 _public member_ `FName NodeName;` — `UPROPERTY()`
- L1763 _public member_ `FName TraitName;` — `UPROPERTY()`
- L1766 _public member_ `FString ScriptStructPath;` — `UPROPERTY()`
- L1769 _public member_ `FString TraitDefault;` — `UPROPERTY()`
- L1772 _public member_ `int32 PinIndex;` — `UPROPERTY()`

#### struct `FRigVMRemoveTraitAction`  
`struct FRigVMRemoveTraitAction : public FRigVMAddTraitAction`  
_L1779-1791_
- reflection: `USTRUCT()`
- inherits: `FRigVMAddTraitAction`
- desc: An action to remove a trait from a node
- L1785 _public prototype_ `FRigVMRemoveTraitAction();`
- L1786 _public prototype_ `FRigVMRemoveTraitAction(URigVMController* InController, const URigVMNode* InNode, const FName& InTraitName, const UScriptStruct* InTraitScriptStruct, const FString& InTraitDefault, int32 InPinIndex);`
- L1787 _public prototype_ `virtual ~FRigVMRemoveTraitAction() = default;`
- L1788 _public function_ `virtual UScriptStruct* GetScriptStruct() const override`
- L1789 _public prototype_ `virtual bool Undo() override;`
- L1790 _public prototype_ `virtual bool Redo() override;`

#### Free symbols / members of external scopes

- L17 _macro_ `#define RIGVM_ACTIONSTACK_VERBOSE_LOG 0`

### `Plugins/Runtime/RigVM/Source/RigVMDeveloper/Public/RigVMModel/RigVMExternalDependency.h` (Public)


#### struct `FRigVMExternalDependency`  
`struct FRigVMExternalDependency`  
_L12-54_
- reflection: `USTRUCT()`
- L18 _public function_ `FRigVMExternalDependency() : ExternalPath() , InternalPath() , Category(NAME_None)`
- L24 _public function_ `FRigVMExternalDependency(const FString& InPath, const FName& InCategory) : ExternalPath(InPath) , InternalPath() , Category(InCategory)`
- L30 _public function_ `bool IsExternal() const`
- L31 _public function_ `bool IsInternal() const`
- L33 _public function_ `const FString& GetExternalPath() const`
- L34 _public function_ `const FString& GetInternalPath() const`
- L35 _public function_ `const FName& GetCategory() const`
- L37 _public function_ `bool operator==(const FRigVMExternalDependency& InOther) const`
- L47 _private member_ `FString ExternalPath;` — `UPROPERTY()`
- L50 _private member_ `FString InternalPath;` — `UPROPERTY()`
- L53 _private member_ `FName Category;` — `UPROPERTY()`

#### class `URigVMExternalDependencyManager`  
`class URigVMExternalDependencyManager : public UInterface`  
_L57-60_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UInterface`

#### class `IRigVMExternalDependencyManager`  
`class IRigVMExternalDependencyManager`  
_L63-94_
- desc: Interface to deal with mapping external dependencies
- L69 _public prototype_ `virtual const TArray<FName>& GetExternalDependencyCategories() const;`
- L70 _public prototype_ `virtual TArray<FRigVMExternalDependency> GetExternalDependenciesForCategory(const FName& InCategory) const = 0;`
- L71 _public prototype_ `TArray<FRigVMExternalDependency> GetAllExternalDependencies() const;`
- L73 _public member_ `static inline const FLazyName UserDefinedEnumCategory = FLazyName(TEXT("User`
- L74 _public member_ `static inline const FLazyName UserDefinedStructCategory = FLazyName(TEXT("User`
- L75 _public member_ `static inline const FLazyName RigVMGraphFunctionCategory = FLazyName(TEXT("RigV`
- L79 _protected prototype_ `virtual void CollectExternalDependencies(TArray<FRigVMExternalDependency>& OutDependencies, const FName& InCategory, const FRigVMClient* InClient) const;`
- L80 _protected prototype_ `virtual void CollectExternalDependencies(TArray<FRigVMExternalDependency>& OutDependencies, const FName& InCategory, const FRigVMGraphFunctionStore* InFunctionStore) const;`
- L81 _protected prototype_ `virtual void CollectExternalDependencies(TArray<FRigVMExternalDependency>& OutDependencies, const FName& InCategory, const FRigVMGraphFunctionData* InFunction) const;`
- L82 _protected prototype_ `virtual void CollectExternalDependencies(TArray<FRigVMExternalDependency>& OutDependencies, const FName& InCategory, const FRigVMGraphFunctionHeader* InHeader) const;`
- L83 _protected prototype_ `virtual void CollectExternalDependencies(TArray<FRigVMExternalDependency>& OutDependencies, const FName& InCategory, const FRigVMFunctionCompilationData* InCompilationData) const;`
- L84 _protected prototype_ `virtual void CollectExternalDependencies(TArray<FRigVMExternalDependency>& OutDependencies, const FName& InCategory, const URigVMGraph* InGraph) const;`
- L85 _protected prototype_ `virtual void CollectExternalDependencies(TArray<FRigVMExternalDependency>& OutDependencies, const FName& InCategory, const URigVMNode* InNode) const;`
- L86 _protected prototype_ `virtual void CollectExternalDependencies(TArray<FRigVMExternalDependency>& OutDependencies, const FName& InCategory, const URigVMPin* InPin) const;`
- L87 _protected prototype_ `virtual void CollectExternalDependencies(TArray<FRigVMExternalDependency>& OutDependencies, const FName& InCategory, const UStruct* InStruct) const;`
- L88 _protected prototype_ `virtual void CollectExternalDependencies(TArray<FRigVMExternalDependency>& OutDependencies, const FName& InCategory, const UEnum* InEnum) const;`
- L89 _protected prototype_ `virtual void CollectExternalDependenciesForCPPTypeObject(TArray<FRigVMExternalDependency>& OutDependencies, const FName& InCategory, const UObject* InObject) const;`
- L91 _protected member_ `static TArray<FName> DependencyCategories;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API RIGVMDEVELOPER_API`

### `Plugins/Runtime/RigVM/Source/RigVMDeveloper/Public/RigVMModel/RigVMFunctionLibrary.h` (Public)


#### class `URigVMFunctionLibrary`  
`class URigVMFunctionLibrary : public URigVMGraph`  
_L21-108_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `URigVMGraph`
- desc: The Function Library is a graph used only to store the sub graphs used for functions.
- L28 _public prototype_ `URigVMFunctionLibrary();` — Default constructor
- L31 _public prototype_ `virtual FString GetNodePath() const override;` — URigVMGraph interface
- L32 _public prototype_ `virtual URigVMFunctionLibrary* GetDefaultFunctionLibrary() const override;`
- L37 _public prototype_ `TArray<URigVMLibraryNode*> GetFunctions() const;` — `UFUNCTION(BlueprintCallable, Category = RigVMGraph)` — Returns all of the stored functions
- L41 _public prototype_ `URigVMLibraryNode* FindFunction(const FName& InFunctionName) const;` — `UFUNCTION(BlueprintCallable, Category = RigVMGraph)` — Finds a function by name
- L45 _public prototype_ `URigVMLibraryNode* FindFunctionForNode(URigVMNode* InNode) const;` — `UFUNCTION(BlueprintCallable, Category = RigVMGraph)` — Finds a function by a node within a function (or a sub graph of that)
- L49 _public prototype_ `TArray< TSoftObjectPtr<URigVMFunctionReferenceNode> > GetReferencesForFunction(const FName& InFunctionName);` — `UFUNCTION(BlueprintCallable, Category = RigVMGraph)` — Returns all references for a given function name
- L53 _public prototype_ `TArray< FString > GetReferencePathsForFunction(const FName& InFunctionName);` — `UFUNCTION(BlueprintCallable, Category = RigVMGraph)` — Returns all references for a given function name
- L61 _public prototype_ `void ForEachReference(const FName& InFunctionName, TFunction<void(URigVMFunctionReferenceNode*)> PerReferenceFunction, bool bLoadIfNecessary = true) const;` — Iterator function to invoke a lambda / TFunction for each reference of a function @param InFunctionName The function name to iterate all references for @param PerReferenceFunction The function to invoke for each reference @param bLoadIfNecessary If true, will load packages when needed
- L68 _public prototype_ `void ForEachReferenceSoftPtr(const FName& InFunctionName, TFunction<void(TSoftObjectPtr<URigVMFunctionReferenceNode>)> PerReferenceFunction) const;` — Iterator function to invoke a lambda / TFunction for each reference of a function @param InFunctionName The function name to iterate all references for @param PerReferenceFunction The function to invoke for each reference
- L73 _public prototype_ `URigVMLibraryNode* FindPreviouslyLocalizedFunction(FRigVMGraphFunctionIdentifier InFunctionToLocalize);` — Returns a function that has been previously localized based on the provided function to localize. We maintain meta data on what functions have been created locally based on which other ones, and use this method to avoid redundant localizations.
- L75 _public prototype_ `const FSoftObjectPath GetFunctionHostObjectPath() const;`
- L76 _public member_ `URigVMFunctionLibrary_GetFunctionHostObjectPath GetFunctionHostObjectPathDelegate;`
- L78 _public function_ `bool IsFunctionPublic(const FName& InFunctionName) const`
- L80 _public prototype_ `const FRigVMVariant* GetFunctionVariant(const FName& InFunctionName) const;`
- L81 _public prototype_ `FRigVMVariant* GetFunctionVariant(const FName& InFunctionName);`
- L86 _private member_ `TArray<FName> PublicFunctionNames;` — `UPROPERTY()`
- L89 _private member_ `TMap<FName, FRigVMVariant> FunctionToVariant;` — `UPROPERTY()`
- L93 _private member_ `TMap< TObjectPtr<URigVMLibraryNode>, FRigVMFunctionReferenceArray > FunctionReferences_DEPRECATED;` — `UPROPERTY()`
- L100 _private member_ `TMap< FString, TObjectPtr<URigVMLibraryNode> > LocalizedFunctions;` — `UPROPERTY()` — A map which stores a library node per original pathname. The source pathname is the full path of the source function that was localized to the local copy stored in the value of the pair.

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API RIGVMDEVELOPER_API`
- L14 _delegate_ `DECLARE_DELEGATE_RetVal(const FSoftObjectPath, URigVMFunctionLibrary_GetFunctionHostObjectPath);`
- L14 _prototype_ `DECLARE_DELEGATE_RetVal(const FSoftObjectPath, URigVMFunctionLibrary_GetFunctionHostObjectPath);`

### `Plugins/Runtime/RigVM/Source/RigVMDeveloper/Public/RigVMModel/RigVMGraph.h` (Public)


#### class `URigVMGraph`  
`class URigVMGraph : public UObject`  
_L31-270_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UObject`
- desc: The Graph represents a Function definition using Nodes as statements. Graphs can be compiled into a URigVM using the FRigVMCompiler. Graphs provide access to its Nodes, Pins and Links.
- L38 _public prototype_ `URigVMGraph();` — Default constructor
- L40 _public prototype_ `virtual void PostLoad() override;`
- L44 _public prototype_ `const TArray<URigVMNode*>& GetNodes() const;` — `UFUNCTION(BlueprintCallable, Category = RigVMGraph)` — Returns all of the Nodes within this Graph.
- L48 _public prototype_ `const TArray<URigVMLink*>& GetLinks() const;` — `UFUNCTION(BlueprintCallable, Category = RigVMGraph)` — Returns all of the Links within this Graph.
- L52 _public prototype_ `bool ContainsLink(const FString& InPinPathRepresentation) const;` — `UFUNCTION(BlueprintCallable, Category = RigVMGraph)` — Returns true if the graph contains a link given its string representation
- L56 _public prototype_ `TArray<URigVMGraph*> GetContainedGraphs(bool bRecursive = false) const;` — `UFUNCTION(BlueprintCallable, Category = RigVMGraph)` — Returns all of the contained graphs
- L60 _public prototype_ `URigVMGraph* GetParentGraph() const;` — `UFUNCTION(BlueprintCallable, Category = RigVMGraph)` — Returns the parent graph of this graph
- L64 _public prototype_ `URigVMGraph* GetRootGraph() const;` — `UFUNCTION(BlueprintCallable, Category = RigVMGraph)` — Returns the root / top level parent graph of this graph (or this if it is the root graph)
- L68 _public prototype_ `int32 GetGraphDepth() const;` — `UFUNCTION(BlueprintPure, Category = RigVMGraph)` — Returns the root / top level parent graph of this graph (or this if it is the root graph)
- L72 _public prototype_ `bool IsRootGraph() const;` — `UFUNCTION(BlueprintCallable, Category = RigVMGraph)` — Returns true if this graph is a root / top level graph
- L76 _public prototype_ `URigVMFunctionEntryNode* GetEntryNode() const;` — `UFUNCTION(BlueprintCallable, Category = RigVMGraph)` — Returns the entry node of this graph
- L80 _public prototype_ `URigVMFunctionReturnNode* GetReturnNode() const;` — `UFUNCTION(BlueprintCallable, Category = RigVMGraph)` — Returns the return node of this graph
- L84 _public prototype_ `TArray<FName> GetEventNames() const;` — `UFUNCTION(BlueprintCallable, Category = RigVMGraph)` — Returns array of event names
- L89 _public prototype_ `TArray<FRigVMGraphVariableDescription> GetVariableDescriptions() const;` — `UFUNCTION(BlueprintCallable, Category = RigVMGraph)` — Returns a list of unique Variable descriptions within this Graph. Multiple Variable Nodes can share the same description.
- L93 _public prototype_ `virtual FString GetNodePath() const;` — `UFUNCTION(BlueprintCallable, Category = RigVMGraph)` — Returns the path of this graph as defined by its invoking nodes
- L97 _public prototype_ `FString GetGraphName() const;` — `UFUNCTION(BlueprintCallable, Category = RigVMGraph)` — Returns the name of this graph (as defined by the node path)
- L101 _public prototype_ `URigVMNode* FindNodeByName(const FName& InNodeName) const;` — `UFUNCTION(BlueprintCallable, Category = RigVMGraph)` — Returns a Node given its name (or nullptr).
- L106 _public prototype_ `URigVMNode* FindNode(const FString& InNodePath) const;` — `UFUNCTION(BlueprintCallable, Category = RigVMGraph)` — Returns a Node given its path (or nullptr). (for now this is the same as finding a node by its name.)
- L110 _public prototype_ `URigVMPin* FindPin(const FString& InPinPath) const;` — `UFUNCTION(BlueprintCallable, Category = RigVMGraph)` — Returns a Pin given its path, for example "Node.Color.R".
- L115 _public prototype_ `URigVMLink* FindLink(const FString& InLinkPinPathRepresentation) const;` — `UFUNCTION(BlueprintCallable, Category = RigVMGraph)` — Returns a link given its string representation, for example "NodeA.Color.R -> NodeB.Translation.X"
- L119 _public prototype_ `bool IsNodeSelected(const FName& InNodeName) const;` — `UFUNCTION(BlueprintCallable, Category = RigVMGraph)` — Returns true if a Node with a given name is selected.
- L123 _public prototype_ `const TArray<FName>& GetSelectNodes() const;` — `UFUNCTION(BlueprintCallable, Category = RigVMGraph)` — Returns the names of all currently selected Nodes.
- L127 _public prototype_ `bool IsNodeHighlighted(const FName& InNodeName) const;` — `UFUNCTION(BlueprintCallable, Category = RigVMGraph)` — Returns true if a node matches the currently selected subset
- L131 _public prototype_ `bool IsTopLevelGraph() const;` — `UFUNCTION(BlueprintCallable, Category = RigVMGraph)` — Returns true if this graph is the top level graph
- L135 _public prototype_ `virtual URigVMFunctionLibrary* GetDefaultFunctionLibrary() const;` — `UFUNCTION(BlueprintCallable, Category = RigVMGraph)` — Returns the locally available function library
- L138 _public prototype_ `void SetDefaultFunctionLibrary(URigVMFunctionLibrary* InFunctionLibrary);` — `UFUNCTION(BlueprintCallable, Category = RigVMGraph)`
- L140 _public prototype_ `TArray<FRigVMExternalVariable> GetExternalVariables() const;`
- L144 _public prototype_ `TArray<FRigVMGraphVariableDescription> GetLocalVariables(bool bIncludeInputArguments = false) const;` — `UFUNCTION(BlueprintCallable, Category = RigVMGraph)` — Returns the local variables of this function
- L148 _public prototype_ `TArray<FRigVMGraphVariableDescription> GetInputArguments() const;` — `UFUNCTION(BlueprintCallable, Category = RigVMGraph)` — Returns the input arguments of this graph
- L152 _public prototype_ `TArray<FRigVMGraphVariableDescription> GetOutputArguments() const;` — `UFUNCTION(BlueprintCallable, Category = RigVMGraph)` — Returns the output arguments of this graph
- L156 _public prototype_ `TArray<FRigVMGraphVariableDescription> GetInputVariables() const;` — `UFUNCTION(BlueprintCallable, Category = RigVMGraph)` — Returns the input variables of this function
- L160 _public prototype_ `URigVMSchema* GetSchema() const;` — `UFUNCTION(BlueprintCallable, Category = RigVMGraph)` — Returns the schema used by this graph
- L164 _public function_ `TSubclassOf<URigVMSchema> GetSchemaClass() const` — `UFUNCTION(BlueprintCallable, Category = RigVMGraph)` — Returns the schema class used by this graph
- L168 _public prototype_ `void SetSchemaClass(TSubclassOf<URigVMSchema> InSchemaClass);` — `UFUNCTION(BlueprintCallable, Category = RigVMGraph)` — Sets the schema class on the graph
- L172 _public prototype_ `FRigVMGraphModifiedEvent& OnModified();` — Returns the modified event, which can be used to subscribe to changes happening within the Graph.
- L175 _public prototype_ `void SetExecuteContextStruct(UScriptStruct* InExecuteContextStruct);` — Sets the execute context struct type to use
- L177 _public prototype_ `UScriptStruct* GetExecuteContextStruct() const;`
- L179 _public prototype_ `void PrepareCycleChecking(URigVMPin* InPin, bool bAsInput);`
- L180 _public prototype_ `virtual bool CanLink(URigVMPin* InSourcePin, URigVMPin* InTargetPin, FString* OutFailureReason, const FRigVMByteCode* InByteCode, ERigVMPinDirection InUserLinkDirection = ERigVMPinDirection::IO, bool bEnableTypeCasting = true);`
- L182 _public prototype_ `TSharedPtr<FRigVMParserAST> GetDiagnosticsAST(bool bForceRefresh = false, TArray<URigVMLink*> InLinksToSkip = TArray<URigVMLink*>());`
- L183 _public prototype_ `TSharedPtr<FRigVMParserAST> GetRuntimeAST(const FRigVMParserASTSettings& InSettings = FRigVMParserASTSettings::Optimized(), bool bForceRefresh = false);`
- L184 _public prototype_ `void ClearAST(bool bClearDiagnostics = true, bool bClearRuntime = true);`
- L186 _public prototype_ `virtual uint32 GetStructureHash() const;`
- L187 _public function_ `uint32 GetSerializedStructureHash() const`
- L189 _public prototype_ `virtual void PreSave(FObjectPreSaveContext SaveContext) override;`
- L191 _public prototype_ `bool AreSectionsEnabled() const;`
- L192 _public function_ `const TArray<FRigVMGraphSection>& GetSelectedSections() const`
- L193 _public function_ `const TArray<FRigVMGraphSection>& GetSectionsMatchingTheSelection() const`
- L194 _public prototype_ `TArray<FRigVMGraphSection> GetMatchingSections(const FRigVMGraphSection& InSection) const;`
- L195 _public prototype_ `void UpdateSections(bool bForce = false);`
- L197 _public prototype_ `TSharedPtr<FScribbleGraphData> SetupScribbleGraph(bool bCreateIfMissing = false);`
- L201 _private member_ `FRigVMGraphModifiedEvent ModifiedEvent;`
- L202 _private prototype_ `void Notify(ERigVMGraphNotifType InNotifType, UObject* InSubject);`
- L205 _private member_ `TArray<TObjectPtr<URigVMNode>> Nodes;` — `UPROPERTY()`
- L208 _private member_ `TArray<TObjectPtr<URigVMLink>> Links;` — `UPROPERTY()`
- L211 _private member_ `TArray<TObjectPtr<URigVMLink>> DetachedLinks;` — `UPROPERTY(transient)`
- L214 _private member_ `TArray<FName> SelectedNodes;` — `UPROPERTY()`
- L217 _private member_ `TWeakObjectPtr<URigVMGraph> DefaultFunctionLibraryPtr;` — `UPROPERTY()`
- L220 _private member_ `TObjectPtr<UScriptStruct> ExecuteContextStruct;` — `UPROPERTY()`
- L222 _private member_ `TSharedPtr<FRigVMParserAST> DiagnosticsAST;`
- L223 _private member_ `TSharedPtr<FRigVMParserAST> RuntimeAST;`
- L226 _private member_ `TArray<TSharedPtr<FString>> VariableNames;`
- L227 _private member_ `TArray<TSharedPtr<FString>> ParameterNames;`
- L231 _private member_ `uint32 LastStructureHash;` — `UPROPERTY()`
- L234 _private member_ `bool bEditable;` — `UPROPERTY()`
- L237 _private member_ `TArray<FRigVMGraphVariableDescription> LocalVariables;` — `UPROPERTY()`
- L240 _private member_ `TSubclassOf<URigVMSchema> SchemaClass;` — `UPROPERTY()`
- L243 _private member_ `bool bSectionsEnabled;` — `UPROPERTY(transient)`
- L246 _private member_ `TArray<FRigVMGraphSection> SelectedSections;` — `UPROPERTY(transient)`
- L249 _private member_ `TArray<FRigVMGraphSection> SectionsMatchingTheSelection;` — `UPROPERTY(transient)`
- L251 _private prototype_ `bool IsNameAvailable(const FString& InName) const;`
- L252 _private prototype_ `bool IsNameAvailable(FName InName) const;`
- L255 _private member_ `FScribbleGraph ScribbleGraph;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L16 _macro_ `#define UE_API RIGVMDEVELOPER_API`

### `Plugins/Runtime/RigVM/Source/RigVMDeveloper/Public/RigVMModel/RigVMGraphSection.h` (Public)


#### struct `FRigVMGraphSectionLink`  
`struct FRigVMGraphSectionLink`  
_L13-41_
- reflection: `USTRUCT()`
- L18 _public member_ `int32 SourceNodeIndex = INDEX_NONE;` — `UPROPERTY()`
- L21 _public member_ `int32 TargetNodeIndex = INDEX_NONE;` — `UPROPERTY()`
- L24 _public member_ `uint32 SourceNodeHash = UINT32_MAX;` — `UPROPERTY()`
- L27 _public member_ `uint32 TargetNodeHash = UINT32_MAX;` — `UPROPERTY()`
- L30 _public member_ `FString SourcePinPath;` — `UPROPERTY()`
- L33 _public member_ `FString TargetPinPath;` — `UPROPERTY()`
- L35 _public typedef_ `using FPinTuple = TTuple<const URigVMPin*, const URigVMPin*>;`
- L36 _public prototype_ `static URigVMPin* FindSourcePinSkippingReroutes(const URigVMLink* InLink);`
- L37 _public prototype_ `static TArray<URigVMPin*> FindTargetPinsSkippingReroutes(const URigVMLink* InLink);`
- L38 _public prototype_ `static TArray<FPinTuple> FindLinksSkippingReroutes(const URigVMNode* InNode);`
- L39 _public prototype_ `const URigVMNode* FindSourceNode(const URigVMNode* InTargetNode) const;`
- L40 _public prototype_ `TArray<const URigVMNode*> FindTargetNodes(const URigVMNode* InSourceNode) const;`

#### struct `FRigVMGraphSection`  
`struct FRigVMGraphSection`  
_L44-91_
- reflection: `USTRUCT()`
- L50 _public prototype_ `FRigVMGraphSection();`
- L51 _public prototype_ `FRigVMGraphSection(const TArray<URigVMNode*>& InNodes);`
- L53 _public prototype_ `static TArray<FRigVMGraphSection> GetSectionsFromSelection(const URigVMGraph* InGraph);`
- L55 _public prototype_ `bool IsValid() const;`
- L56 _public prototype_ `static bool IsValidNode(const URigVMNode* InNode);`
- L59 _public member_ `uint32 Hash;` — `UPROPERTY()`
- L62 _public member_ `TArray<FName> Nodes;` — `UPROPERTY()`
- L65 _public member_ `TArray<uint32> NodeHashes;` — `UPROPERTY()`
- L68 _public member_ `TArray<int32> LeafNodes;` — `UPROPERTY()`
- L71 _public member_ `TArray<FRigVMGraphSectionLink> Links;` — `UPROPERTY()`
- L73 _public prototype_ `TArray<FRigVMGraphSection> FindMatches(const URigVMGraph* InGraph) const;`
- L74 _public prototype_ `TArray<FRigVMGraphSection> FindMatches(const TArray<URigVMNode*>& InAvailableNodes) const;`
- L76 _public prototype_ `bool ContainsNode(const FName& InNodeName) const;`
- L77 _public prototype_ `bool MatchesNode(const URigVMNode* InNode, const TArray<URigVMNode*>& InAvailableNodes, TArray<URigVMNode*>* OutMatchingNodesForSet = nullptr) const;`
- L81 _private prototype_ `void Reset();`
- L83 _private prototype_ `static TArray<TArray<URigVMNode*>> GetNodeIslands(const TArray<URigVMNode*>& InNodes);`
- L85 _private prototype_ `static uint32 GetNodeHash(const URigVMNode* InNode);`
- L86 _private prototype_ `static uint32 GetLinkHash(const FRigVMGraphSectionLink& InLink);`
- L88 _private prototype_ `bool MatchesNode_Impl(const URigVMNode* InNode, const TArray<URigVMNode*>& InAvailableNodes, int32 InNodeIndex, TArray<URigVMNode*>& VisitedNodes) const;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API RIGVMDEVELOPER_API`

### `Plugins/Runtime/RigVM/Source/RigVMDeveloper/Public/RigVMModel/RigVMLink.h` (Public)


#### class `URigVMLink`  
`class URigVMLink : public UObject`  
_L21-116_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UObject`
- desc: The Link represents a connection between two Pins within a Graph. The Link can be accessed on the Graph itself - or through the URigVMPin::GetLinks() method.
- L28 _public prototype_ `URigVMLink() = default;` — Default constructor
- L31 _public prototype_ `virtual void Serialize(FArchive& Ar) override;` — Serialization override
- L35 _public prototype_ `int32 GetLinkIndex() const;` — `UFUNCTION(BlueprintCallable, Category = RigVMLink)` — Returns the current index of this Link within its owning Graph.
- L39 _public prototype_ `URigVMGraph* GetGraph() const;` — `UFUNCTION(BlueprintCallable, Category = RigVMLink)` — Returns the Link's owning Graph/
- L43 _public prototype_ `int32 GetGraphDepth() const;` — `UFUNCTION(BlueprintCallable, Category = RigVMLink)` — Returns the graph nesting depth of this link
- L47 _public prototype_ `URigVMPin* GetSourcePin() const;` — `UFUNCTION(BlueprintCallable, Category = RigVMLink)` — Returns the source Pin of this Link (or nullptr)
- L51 _public prototype_ `URigVMPin* GetTargetPin() const;` — `UFUNCTION(BlueprintCallable, Category = RigVMLink)` — Returns the target Pin of this Link (or nullptr)
- L55 _public prototype_ `URigVMNode* GetSourceNode() const;` — `UFUNCTION(BlueprintCallable, Category = RigVMLink)` — Returns the source Node of this Link (or nullptr)
- L59 _public prototype_ `URigVMNode* GetTargetNode() const;` — `UFUNCTION(BlueprintCallable, Category = RigVMLink)` — Returns the target Node of this Link (or nullptr)
- L62 _public prototype_ `FString GetSourcePinPath() const;` — Returns the source pin's path pin of this Link
- L65 _public prototype_ `FString GetTargetPinPath() const;` — Returns the target pin's path pin of this Link
- L68 _public prototype_ `bool SetSourcePinPath(const FString& InPinPath);` — Sets the source pin's path pin of this Link
- L71 _public prototype_ `bool SetTargetPinPath(const FString& InPinPath);` — Sets the target pin's path pin of this Link
- L74 _public prototype_ `bool SetSourceAndTargetPinPaths(const FString& InSourcePinPath, const FString& InTargetPinPath);` — Sets the target pin's path pin of this Link
- L78 _public prototype_ `URigVMPin* GetOppositePin(const URigVMPin* InPin) const;` — `UFUNCTION(BlueprintCallable, Category = RigVMLink)` — Returns the opposite Pin of this Link given one of its edges (or nullptr)
- L84 _public prototype_ `FString GetPinPathRepresentation() const;` — `UFUNCTION(BlueprintCallable, Category = RigVMLink)` — Returns a string representation of the Link, for example: "NodeA.Color.R -> NodeB.Translation.X" note: can be split again using SplitPinPathRepresentation
- L89 _public prototype_ `static FString GetPinPathRepresentation(const FString& InSourcePinPath, const FString& InTargetPinPath);` — Returns a string representation of the Link given the two pin paths for example: "NodeA.Color.R -> NodeB.Translation.X" note: can be split again using SplitPinPathRepresentation
- L94 _public prototype_ `static bool SplitPinPathRepresentation(const FString& InString, FString& OutSource, FString& OutTarget);` — Splits a pin path representation of a link for example: "NodeA.Color.R -> NodeB.Translation.X" into its two pin paths
- L96 _public prototype_ `void UpdatePinPaths();`
- L97 _public prototype_ `void UpdatePinPointers() const;`
- L98 _public prototype_ `bool Detach();`
- L105 _private prototype_ `bool IsAttached() const;` — Returns true if the link is attached. Attached links rely on the pin pointers first and the pin path second. Deattached links never rely on the pin pointers and always try to resolve from string.
- L106 _private prototype_ `bool Attach(FString* OutFailureReason = nullptr);`
- L109 _private member_ `FString SourcePinPath;` — `UPROPERTY()`
- L112 _private member_ `FString TargetPinPath;` — `UPROPERTY()`
- L114 _private member_ `mutable URigVMPin* SourcePin = nullptr;`
- L115 _private member_ `mutable URigVMPin* TargetPin = nullptr;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API RIGVMDEVELOPER_API`

### `Plugins/Runtime/RigVM/Source/RigVMDeveloper/Public/RigVMModel/RigVMModelCachedValue.h` (Public)


#### class `TRigVMModelCachedValue`  
`template<typename VersionObjectType, typename ValueType> class TRigVMModelCachedValue`  
_L14-144_
- desc: A cached value which relies on a version providing object. The versioned object needs to provide uint32 GetCachedValueVersion() Values within the cache are considered valid if they are a) set and b) the version of the cache matches the version of the versioned object.
- L19 _public function_ `TRigVMModelCachedValue() : LastObjectVersion(UINT_MAX)` — default empty constructor
- L25 _public function_ `TRigVMModelCachedValue(const VersionObjectType* InObject) : VersionedObjectWeakPtr(InObject) , LastObjectVersion(UINT_MAX)` — constructor for an empty cache bound to a versioned object
- L32 _public function_ `TRigVMModelCachedValue(VersionObjectType* InObject, const ValueType& InValue) : VersionedObjectWeakPtr(InObject) , LastObjectVersion(UINT_MAX)` — constructor for a valid cache bound to a versioned object
- L40 _public function_ `bool IsValid() const` — returns true if the cache is bound, the value has been set and the version is current
- L53 _public function_ `bool IsBound() const` — returns true if the cache is bound to a versioned object
- L59 _public function_ `void Bind(const VersionObjectType* InVersionedObject)` — binds the cache to a new versioned object
- L73 _public function_ `void Unbind()` — unbinds the cache from a versioned object
- L79 _public function_ `const ValueType& Get(const ValueType& InDefault) const` — returns the cached value if it is valid - or otherwise returns the default
- L89 _public function_ `const ValueType& GetValue() const` — returns the cached value
- L96 _public function_ `void Set(const ValueType& InValue)` — sets the cached value and updates the last version given the bound object
- L106 _public function_ `void ResetCachedValue()` — resets the cached value
- L113 _public function_ `TRigVMModelCachedValue& operator =(const ValueType& InValueType)` — sets the value using an assignment operator
- L120 _public function_ `bool operator ==(const ValueType& InValueType) const` — compares the cached value using a comparison operator
- L130 _public function_ `bool operator !=(const ValueType& InValueType) const` — compares the cached value usinga  comparison operator
- L141 _private member_ `TWeakObjectPtr<const VersionObjectType> VersionedObjectWeakPtr;`
- L142 _private member_ `TOptional<ValueType> Value;`
- L143 _private member_ `uint32 LastObjectVersion;`

### `Plugins/Runtime/RigVM/Source/RigVMDeveloper/Public/RigVMModel/RigVMNode.h` (Public)


#### enum `ERigVMNodeDefaultValueOverrideState::Type`  
`enum Type : int`  
_L20-25_
- L22 _public enumerator_ `None` — No override.
- L23 _public enumerator_ `SomePins` — Some pins have been overriden
- L24 _public enumerator_ `AllPins` — All pins contains an override

#### enum `ERigVMNodeColorType`  
`enum class ERigVMNodeColorType : uint8`  
_L29-33_
- reflection: `UENUM()`
- L31 _public enumerator_ `FromMetadata` — The color was determined from node metadata
- L32 _public enumerator_ `UserDefined` — The color was supplied/edited by a user operation

#### class `URigVMNode`  
`class URigVMNode : public UObject`  
_L45-553_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UObject`
- desc: The Node represents a single statement within a Graph. Nodes can represent values such as Variables / Parameters, they can represent Function Invocations or Control Flow logic statements (such as If conditions of For loops). Additionally Nodes are used to represent Comment statements. Nodes contain Pins to represent parameters for Function Invocations or Value access on Variables / Parameters.
- L52 _public prototype_ `URigVMNode();` — Default constructor
- L55 _public prototype_ `virtual ~URigVMNode();` — Default destructor
- L57 _public prototype_ `void Serialize(FArchive& Ar) override;`
- L63 _public prototype_ `FString GetNodePath(bool bRecursive = false) const;` — `UFUNCTION(BlueprintCallable, Category = RigVMNode)` — Returns the a . separated string containing all of the names used to reach this Node within the Graph. (for now this is the same as the Node's name)
- L66 _public prototype_ `static bool SplitNodePathAtStart(const FString& InNodePath, FString& LeftMost, FString& Right);` — Splits a NodePath at the start, so for example "CollapseNodeA|CollapseNodeB|CollapseNodeC" becomes "CollapseNodeA" and "CollapseNodeB|CollapseNodeC"
- L69 _public prototype_ `static bool SplitNodePathAtEnd(const FString& InNodePath, FString& Left, FString& RightMost);` — Splits a NodePath at the end, so for example "CollapseNodeA|CollapseNodeB|CollapseNodeC" becomes "CollapseNodeA|CollapseNodeB" and "CollapseNodeC"
- L72 _public prototype_ `static bool SplitNodePath(const FString& InNodePath, TArray<FString>& Parts);` — Splits a NodePath into all segments, so for example "Node.Color.R" becomes ["Node", "Color", "R"]
- L75 _public prototype_ `static FString JoinNodePath(const FString& Left, const FString& Right);` — Joins a NodePath from to segments, so for example "CollapseNodeA" and "CollapseNodeB|CollapseNodeC" becomes "CollapseNodeA|CollapseNodeB|CollapseNodeC"
- L78 _public prototype_ `static FString JoinNodePath(const TArray<FString>& InParts);` — Joins a NodePath from to segments, so for example ["CollapseNodeA", "CollapseNodeB", "CollapseNodeC"] becomes "CollapseNodeA|CollapseNodeB|CollapseNodeC"
- L82 _public prototype_ `int32 GetNodeIndex() const;` — `UFUNCTION(BlueprintCallable, Category = RigVMNode)` — Returns the current index of the Node within the Graph.
- L86 _public prototype_ `virtual const TArray<URigVMPin*>& GetPins() const;` — `UFUNCTION(BlueprintCallable, Category = RigVMNode)` — Returns all of the top-level Pins of this Node.
- L90 _public prototype_ `TArray<URigVMPin*> GetAllPinsRecursively() const;` — `UFUNCTION(BlueprintCallable, Category = RigVMNode)` — Returns all of the Pins of this Node (including SubPins).
- L94 _public prototype_ `virtual TArray<FString> GetPinCategories() const;` — `UFUNCTION(BlueprintCallable, Category = RigVMNode)` — Returns all user defined categories on this node
- L98 _public prototype_ `FString GetPinCategoryName(const FString InCategory) const;` — `UFUNCTION(BlueprintCallable, Category = RigVMNode)` — Returns the name of pin category
- L102 _public prototype_ `TArray<FString> GetSubPinCategories(const FString InCategory, bool bOnlyExisting = false, bool bRecursive = false) const;` — `UFUNCTION(BlueprintCallable, Category = RigVMNode)` — Returns all sub user defined categories of a given parent category
- L106 _public prototype_ `FString GetParentPinCategory(const FString InCategory, bool bOnlyExisting = false) const;` — `UFUNCTION(BlueprintCallable, Category = RigVMNode)` — Returns the parent pin category of the given category (or an empty string in case there's no parent)
- L110 _public prototype_ `TArray<FString> GetParentPinCategories(const FString InCategory, bool bOnlyExisting = false, bool bIncludeSelf = false) const;` — `UFUNCTION(BlueprintCallable, Category = RigVMNode)` — Returns all parent categories of a given
- L113 _public prototype_ `static int32 GetPinCategoryDepth(const FString& InCategory);` — Returns the depth of the category (starting with 0 for "Foo" and 2 for "Foo|Bar|Waldo")
- L117 _public prototype_ `TArray<URigVMPin*> GetPinsForCategory(FString InCategory) const;` — `UFUNCTION(BlueprintCallable, Category = RigVMNode)` — Returns all pins for a given category
- L121 _public prototype_ `bool IsPinCategoryExpanded(FString InCategory) const;` — `UFUNCTION(BlueprintCallable, Category = RigVMNode)` — Returns all pins for a given category
- L123 _public function_ `const FString& GetLastAffectedPinCategory() const`
- L127 _public prototype_ `virtual FRigVMNodeLayout GetNodeLayout(bool bIncludeEmptyCategories = false) const;` — `UFUNCTION(BlueprintCallable, Category = RigVMNode)` — Returns the pin UI layout for this node
- L130 _public prototype_ `FString GetOriginalPinDefaultValue(const URigVMPin* InPin) const;` — Returns the default value for a given pin
- L135 _public prototype_ `ERigVMNodeDefaultValueOverrideState::Type GetPinDefaultValueOverrideState() const;` — Returns 0 if there's no override on this node, 1 if some pins have an override and 2 if all pins are overriden
- L140 _public prototype_ `URigVMPin* FindPin(const FString& InPinPath) const;` — `UFUNCTION(BlueprintCallable, Category = RigVMNode)` — Returns a Pin given it's partial pin path below this node (for example: "Color.R")
- L144 _public prototype_ `URigVMPin* FindRootPinByName(const FName& InPinName) const;` — `UFUNCTION(BlueprintCallable, Category = RigVMNode)` — Returns a root pin given its name
- L148 _public prototype_ `URigVMPin* FindExecutePin() const;` — `UFUNCTION(BlueprintCallable, Category = RigVMNode)` — Returns the first execute pin
- L152 _public prototype_ `virtual const TArray<URigVMPin*>& GetOrphanedPins() const;` — `UFUNCTION(BlueprintCallable, Category = RigVMNode)` — Returns all of the top-level orphaned Pins of this Node.
- L156 _public function_ `bool HasOrphanedPins() const` — `UFUNCTION(BlueprintPure, Category = RigVMNode)` — Returns true if the node has orphaned pins - which leads to a compiler error
- L160 _public prototype_ `URigVMGraph* GetGraph() const;` — `UFUNCTION(BlueprintCallable, Category = RigVMNode)` — Returns the Graph of this Node
- L164 _public prototype_ `URigVMGraph* GetRootGraph() const;` — `UFUNCTION(BlueprintCallable, Category = RigVMNode)` — Returns the top level / root Graph of this Node
- L168 _public prototype_ `int32 GetGraphDepth() const;` — `UFUNCTION(BlueprintCallable, Category = RigVMNode)` — Returns the graph nesting depth of this node
- L172 _public prototype_ `URigVMInjectionInfo* GetInjectionInfo() const;` — `UFUNCTION(BlueprintCallable, Category = RigVMNode)` — Returns the injection info of this Node (or nullptr)
- L176 _public prototype_ `virtual FString GetNodeTitle() const;` — `UFUNCTION(BlueprintCallable, Category = RigVMNode)` — Returns the title of this Node - used for UI.
- L180 _public prototype_ `const FString& GetNodeTitleRaw() const;` — Returns currently node title set in the node, without any transformations Warning : The raw title might be ignored by some nodes overrides to GetNodeTitle
- L184 _public prototype_ `virtual FString GetNodeSubTitle() const;` — `UFUNCTION(BlueprintCallable, Category = RigVMNode)` — Get the subtitle of the node
- L187 _public prototype_ `virtual bool SupportsRenaming() const;` — Returns true if this node can be renamed by the user
- L191 _public prototype_ `FVector2D GetPosition() const;` — `UFUNCTION(BlueprintCallable, Category = RigVMNode)` — Returns the 2d position of this node - used for UI.
- L195 _public prototype_ `FVector2D GetSize() const;` — `UFUNCTION(BlueprintCallable, Category = RigVMNode)` — Returns the 2d size of this node - used for UI.
- L199 _public prototype_ `virtual FLinearColor GetNodeColor() const;` — `UFUNCTION(BlueprintCallable, Category = RigVMNode)` — Returns the color of this node - used for UI.
- L202 _public prototype_ `virtual FSlateIcon GetNodeIcon() const;` — Returns the icon of this node - used for UI.
- L206 _public prototype_ `virtual FText GetToolTipText() const;` — `UFUNCTION(BlueprintCallable, Category = RigVMNode)` — Returns the tooltip of this node
- L210 _public prototype_ `bool IsSelected() const;` — `UFUNCTION(BlueprintCallable, Category = RigVMNode)` — Returns true if this Node is currently selected.
- L214 _public prototype_ `bool IsHighlighted() const;` — `UFUNCTION(BlueprintCallable, Category = RigVMNode)` — Returns true if this Node should be highlighted
- L219 _public prototype_ `bool IsInjected() const;` — `UFUNCTION(BlueprintCallable, Category = RigVMNode)` — Returns true if this is an injected node. Injected nodes are managed by pins are are not visible to the user.
- L223 _public prototype_ `bool IsVisibleInUI() const;` — `UFUNCTION(BlueprintCallable, Category = RigVMNode)` — Returns true if this should be visible in the UI
- L228 _public prototype_ `virtual bool IsPure() const;` — `UFUNCTION(BlueprintCallable, Category = RigVMNode)` — Returns true if this Node has no side-effects and no internal state.
- L232 _public function_ `virtual bool IsDefinedAsConstant() const` — `UFUNCTION(BlueprintCallable, Category = RigVMNode)` — Returns true if the node is defined as non-varying
- L236 _public function_ `virtual bool IsDefinedAsVarying() const` — `UFUNCTION(BlueprintCallable, Category = RigVMNode)` — Returns true if the node is defined as varying
- L241 _public prototype_ `virtual bool IsMutable() const;` — `UFUNCTION(BlueprintCallable, Category = RigVMNode)` — Returns true if this Node has side effects or internal state.
- L244 _public prototype_ `bool HasWildCardPin() const;` — Returns true if this node has an unknown type pin
- L246 _public function_ `virtual bool ContributesToResult() const`
- L250 _public prototype_ `virtual bool IsEvent() const;` — `UFUNCTION(BlueprintCallable, Category = RigVMNode)` — Returns true if this Node is the beginning of a scope
- L254 _public prototype_ `virtual FName GetEventName() const;` — `UFUNCTION(BlueprintCallable, Category = RigVMNode)` — Returns the name of the event
- L258 _public prototype_ `virtual bool CanOnlyExistOnce() const;` — `UFUNCTION(BlueprintCallable, Category = RigVMNode)` — Returns true if this node can only exist once in a graph
- L262 _public prototype_ `virtual bool HasInputPin(bool bIncludeIO = true) const;` — `UFUNCTION(BlueprintCallable, Category = RigVMNode)` — Returns true if the node has any input pins
- L266 _public prototype_ `virtual bool HasIOPin() const;` — `UFUNCTION(BlueprintCallable, Category = RigVMNode)` — Returns true if the node has any io pins
- L270 _public prototype_ `virtual bool HasLazyPin(bool bOnlyConsiderPinsWithLinks = false) const;` — `UFUNCTION(BlueprintCallable, Category = RigVMNode)` — Returns true if the node has any lazily evaluating pins
- L274 _public prototype_ `virtual bool HasOutputPin(bool bIncludeIO = true) const;` — `UFUNCTION(BlueprintCallable, Category = RigVMNode)` — Returns true if the node has any output pins
- L278 _public prototype_ `virtual bool HasPinOfDirection(ERigVMPinDirection InDirection) const;` — `UFUNCTION(BlueprintCallable, Category = RigVMNode)` — Returns true if the node has any pins of the provided direction
- L283 _public prototype_ `bool IsLinkedTo(URigVMNode* InNode) const;` — `UFUNCTION(BlueprintCallable, Category = RigVMNode)` — Returns true if this Node is linked to another given node through any of the Nodes' Pins.
- L287 _public prototype_ `TArray<URigVMLink*> GetLinks() const;` — `UFUNCTION(BlueprintCallable, Category = RigVMNode)` — Returns all links to any pin on this node
- L292 _public prototype_ `TArray<URigVMNode*> GetLinkedSourceNodes() const;` — `UFUNCTION(BlueprintCallable, Category = RigVMNode)` — Returns a list of Nodes connected as sources to this Node as the target.
- L297 _public prototype_ `TArray<URigVMNode*> GetLinkedTargetNodes() const;` — `UFUNCTION(BlueprintCallable, Category = RigVMNode)` — Returns a list of Nodes connected as targets to this Node as the source.
- L301 _public function_ `FName GetPreviousFName() const` — `UFUNCTION(BlueprintCallable, Category = RigVMNode)` — Returns the name of the node prior to the renaming
- L304 _public prototype_ `const TArray<int32>& GetInstructionsForVM(const FRigVMExtendedExecuteContext& Context, URigVM* InVM, const FRigVMASTProxy& InProxy = FRigVMASTProxy()) const;` — Returns the indices of associated instructions for this node
- L307 _public prototype_ `virtual int32 GetInstructionVisitedCount(const FRigVMExtendedExecuteContext& Context, URigVM* InVM, const FRigVMASTProxy& InProxy = FRigVMASTProxy()) const;` — Returns the number of visited / run instructions for this node
- L310 _public prototype_ `double GetInstructionMicroSeconds(const FRigVMExtendedExecuteContext& Context, URigVM* InVM, const FRigVMASTProxy& InProxy = FRigVMASTProxy()) const;` — Returns the accumulated duration of all of instructions for this node
- L314 _public prototype_ `bool IsLoopNode() const;` — `UFUNCTION(BlueprintPure, Category = RigVMNode)` — return true if this node is a loop node
- L318 _public prototype_ `bool IsControlFlowNode() const;` — `UFUNCTION(BlueprintPure, Category = RigVMNode)` — return true if this node is a control flow node
- L321 _public prototype_ `virtual const TArray<FName>& GetControlFlowBlocks() const;` — returns the names of the control flow blocks of this node
- L324 _public prototype_ `virtual const bool IsControlFlowBlockSliced(const FName& InBlockName) const;` — returns true if a control flow block requires slicing
- L327 _public prototype_ `virtual bool IsWithinLoop() const;` — returns true if the node is within a loop
- L331 _public function_ `virtual bool CanBeUpgraded() const` — `UFUNCTION(BlueprintPure, Category = RigVMNode)` — returns true if the node can be upgraded
- L335 _public prototype_ `virtual TArray<FRigVMUserWorkflow> GetSupportedWorkflows(ERigVMUserWorkflowType InType, const UObject* InSubject) const;` — `UFUNCTION(BlueprintCallable, Category = RigVMNode)` — returns all supported workflows of the node
- L339 _public function_ `bool HasBreakpoint() const` — `UE_DEPRECATED(5.7, "Please, use HasEarlyExitMarker")` — `UFUNCTION(BlueprintCallable, Category = RigVMNode)`
- L343 _public function_ `void SetHasBreakpoint(const bool bValue)` — `UE_DEPRECATED(5.7, "Please, use SetHasEarlyExitMarker")` — `UFUNCTION(BlueprintCallable, Category = RigVMNode)`
- L346 _public prototype_ `bool HasEarlyExitMarker() const;` — `UFUNCTION(BlueprintCallable, Category = RigVMNode)`
- L349 _public prototype_ `void SetHasEarlyExitMarker(const bool bValue);` — `UFUNCTION(BlueprintCallable, Category = RigVMNode)`
- L352 _public prototype_ `bool IsExcludedByEarlyExit() const;` — `UFUNCTION(BlueprintCallable, Category = RigVMNode)`
- L355 _public prototype_ `void SetIsExcludedByEarlyExit(bool bIsExcluded);` — `UFUNCTION(BlueprintCallable, Category = RigVMNode)`
- L359 _public function_ `bool ExecutionIsHaltedAtThisNode() const` — `UE_DEPRECATED(5.7, "Please, use HasEarlyExitMarker")` — `UFUNCTION(BlueprintCallable, Category = RigVMNode)`
- L363 _public function_ `void SetExecutionIsHaltedAtThisNode(const bool bValue)` — `UE_DEPRECATED(5.7, "Please, use SetHasEarlyExitMarker")` — `UFUNCTION(BlueprintCallable, Category = RigVMNode)`
- L366 _public prototype_ `virtual bool IsAggregate() const;` — `UFUNCTION(BlueprintPure, Category = RigVMNode)`
- L369 _public prototype_ `virtual URigVMPin* GetFirstAggregatePin() const;` — `UFUNCTION(BlueprintPure, Category = RigVMNode)`
- L372 _public prototype_ `virtual URigVMPin* GetSecondAggregatePin() const;` — `UFUNCTION(BlueprintPure, Category = RigVMNode)`
- L375 _public prototype_ `virtual URigVMPin* GetOppositeAggregatePin() const;` — `UFUNCTION(BlueprintPure, Category = RigVMNode)`
- L378 _public prototype_ `virtual bool IsInputAggregate() const;` — `UFUNCTION(BlueprintPure, Category = RigVMNode)`
- L381 _public function_ `virtual TArray<URigVMPin*> GetAggregateInputs() const` — `UFUNCTION(BlueprintPure, Category = RigVMNode)`
- L384 _public function_ `virtual TArray<URigVMPin*> GetAggregateOutputs() const` — `UFUNCTION(BlueprintPure, Category = RigVMNode)`
- L387 _public function_ `virtual FName GetNextAggregateName(const FName& InLastAggregatePinName) const` — `UFUNCTION(BlueprintPure, Category = RigVMNode)`
- L390 _public prototype_ `virtual URigVMLibraryNode* FindFunctionForNode() const;` — `UFUNCTION(BlueprintCallable, Category = RigVMNode)`
- L392 _public function_ `virtual FRigVMStructUpgradeInfo GetUpgradeInfo() const`
- L394 _public prototype_ `virtual uint32 GetStructureHash() const;`
- L397 _public function_ `virtual bool HasNonNativePins() const` — allows the node to support non-native pins
- L400 _public prototype_ `TArray<URigVMPin*> GetTraitPins() const;` — `UFUNCTION(BlueprintPure, Category = RigVMNode)`
- L402 _public function_ `const TArray<FString>& GetTraitNames() const`
- L405 _public prototype_ `bool IsTraitPin(FName InName) const;` — `UFUNCTION(BlueprintPure, Category = RigVMNode)`
- L407 _public prototype_ `bool IsTraitPin(const URigVMPin* InTraitPin) const;`
- L409 _public prototype_ `URigVMPin* FindTrait(const FName& InName, const FString& InSubPinPath = FString()) const;`
- L411 _public prototype_ `URigVMPin* FindTrait(const URigVMPin* InTraitPin) const;`
- L413 _public prototype_ `TSharedPtr<FStructOnScope> GetTraitInstance(const FName& InName, bool bUseDefaultValueFromPin = true) const;`
- L415 _public prototype_ `TSharedPtr<FStructOnScope> GetTraitInstance(const URigVMPin* InTraitPin, bool bUseDefaultValueFromPin = true) const;`
- L417 _public prototype_ `UScriptStruct* GetTraitScriptStruct(const FName& InName) const;`
- L419 _public prototype_ `UScriptStruct* GetTraitScriptStruct(const URigVMPin* InTraitPin) const;`
- L421 _public function_ `virtual bool IsOutDated() const`
- L426 _public function_ `virtual FString GetDeprecatedMetadata() const`
- L432 _public prototype_ `FName GetDisplayNameForPin(const FString& InPinPath) const;` — returns the display name for a pin
- L433 _public prototype_ `virtual FName GetDisplayNameForPin(const URigVMPin* InPin) const;`
- L436 _public prototype_ `static FName GetDisplayNameForStructMember(const URigVMPin* InPin);` — returns the display name for a struct member
- L437 _public prototype_ `static FName GetDisplayNameForStructMember(const UStruct* InStruct, const FString& InPath);`
- L440 _public prototype_ `static FName GetDisplayNameForProperty(const FProperty* InProperty, const FString& InRemainingPath);` — returns the display name within a property
- L443 _public prototype_ `virtual FString GetCategoryForPin(const FString& InPinPath) const;` — returns the category for a pin
- L446 _public prototype_ `virtual int32 GetIndexInCategoryForPin(const FString& InPinPath) const;` — returns the index of a pin within a category
- L448 _public prototype_ `virtual FText GetTypedToolTipText(const URigVMPin* InPin, const FText& ToolTipBody) const;`
- L452 _private member_ `static const inline TCHAR* NodeColorName = TEXT("Nod`
- L454 _private prototype_ `bool IsLinkedToRecursive(URigVMPin* InPin, URigVMNode* InNode) const;`
- L455 _private prototype_ `void GetLinkedNodesRecursive(URigVMPin* InPin, bool bLookForSources, TArray<URigVMNode*>& OutNodes) const;`
- L459 _protected prototype_ `virtual void InvalidateCache();`
- L460 _protected prototype_ `virtual TArray<int32> GetInstructionsForVMImpl(const FRigVMExtendedExecuteContext& Context, URigVM* InVM, const FRigVMASTProxy& InProxy = FRigVMASTProxy()) const;`
- L461 _protected prototype_ `virtual FText GetToolTipTextForPin(const URigVMPin* InPin) const;`
- L462 _protected function_ `virtual bool AllowsLinksOn(const URigVMPin* InPin) const`
- L463 _protected function_ `virtual bool ShouldInputPinComputeLazily(const URigVMPin* InPin) const`
- L464 _protected function_ `virtual bool IsPinConstant(const URigVMPin* InPin) const`
- L465 _protected prototype_ `virtual FString GetOriginalDefaultValueForRootPin(const URigVMPin* InRootPin) const;`
- L467 _protected prototype_ `void UpdateTraitRootPinNames();`
- L470 _public function_ `const uint32& GetCachedValueVersion() const`
- L476 _protected prototype_ `void IncrementVersion();`
- L479 _protected member_ `FString NodeTitle;` — `UPROPERTY()`
- L482 _protected member_ `FVector2D Position;` — `UPROPERTY()`
- L485 _protected member_ `FVector2D Size;` — `UPROPERTY()`
- L488 _protected member_ `FLinearColor NodeColor;` — `UPROPERTY()`
- L491 _protected member_ `ERigVMNodeColorType NodeColorType;` — `UPROPERTY()`
- L494 _protected member_ `FName PreviousName;` — `UPROPERTY(transient)`
- L497 _protected member_ `bool bHasEarlyExitMarker;` — `UPROPERTY(transient)`
- L500 _protected member_ `bool bIsExcludedByEarlyExit;` — `UPROPERTY(transient)`
- L503 _protected member_ `TArray<FString> TraitRootPinNames;` — `UPROPERTY()`
- L508 _protected member_ `TMap<FString, FRigVMTraitDefaultValueStruct> TraitDefaultValues;` — `UPROPERTY()` — root trait pin store their default value in a separate property bag so that things like soft object ptr can be used and tracked in a uproperty
- L513 _private member_ `TArray<TObjectPtr<URigVMPin>> Pins;` — `UPROPERTY()`
- L516 _private member_ `TArray<TObjectPtr<URigVMPin>> OrphanedPins;` — `UPROPERTY()`
- L521 _protected member_ `TArray<FString> PinCategories;` — `UPROPERTY()`
- L524 _protected member_ `TMap<FString, bool> PinCategoryExpansion;` — `UPROPERTY()`
- L526 _protected member_ `FString LastAffectedPinCategory;`
- L528 _protected member_ `uint32 NodeVersion;`
- L539 _private prototype_ `const FProfilingCache* UpdateProfilingCacheIfNeeded(const FRigVMExtendedExecuteContext& Context, URigVM* InVM, const FRigVMASTProxy& InProxy) const;`
- L540 _private member_ `mutable uint32 ProfilingHash;`
- L541 _private member_ `mutable TMap<uint32, TSharedPtr<FProfilingCache>> ProfilingCache;`
- L542 _private member_ `static TArray<int32> EmptyInstructionArray;`
- L545 _private member_ `mutable TMap<FString, FString> CachedOriginalPinDefaultValues;`

#### struct `URigVMNode::FProfilingCache`  
`struct FProfilingCache`  
_L533-538_
- L535 _public member_ `mutable int32 VisitedCount;`
- L536 _public member_ `mutable double MicroSeconds;`
- L537 _public member_ `mutable TArray<int32> Instructions;`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API RIGVMDEVELOPER_API`
- L18 _namespace_ `namespace ERigVMNodeDefaultValueOverrideState`

### `Plugins/Runtime/RigVM/Source/RigVMDeveloper/Public/RigVMModel/RigVMNotifications.h` (Public)


#### enum `ERigVMGraphNotifType`  
`enum class ERigVMGraphNotifType : uint8`  
_L16-71_
- reflection: `UENUM(BlueprintType)`
- desc: The Graph Notification Type is used to differentiate between all of the changes that can happen within a graph.
- L18 _public enumerator_ `GraphChanged` — The graph has changed / a new graph has been picked (Subject == nullptr)
- L19 _public enumerator_ `NodeAdded` — A node has been added to the graph (Subject == URigVMNode)
- L20 _public enumerator_ `NodeRemoved` — A node has been removed from the graph (Subject == URigVMNode)
- L21 _public enumerator_ `NodeSelected` — A node has been selected (Subject == URigVMNode)
- L22 _public enumerator_ `NodeDeselected` — A node has been deselected (Subject == URigVMNode)
- L23 _public enumerator_ `NodeSelectionChanged` — The set of selected nodes has changed (Subject == nullptr)
- L24 _public enumerator_ `NodePositionChanged` — A node's position has changed (Subject == URigVMNode)
- L25 _public enumerator_ `NodeSizeChanged` — A node's size has changed (Subject == URigVMNode)
- L26 _public enumerator_ `NodeTitleChanged` — A node's title has changed (Subject == URigVMNode)
- L27 _public enumerator_ `NodeColorChanged` — A node's color has changed (Subject == URigVMNode)
- L28 _public enumerator_ `PinAdded` — A pin has been added to a given node (Subject == URigVMPin)
- L29 _public enumerator_ `PinRemoved` — A pin has been removed from a given node (Subject == URigVMPin)
- L30 _public enumerator_ `PinRenamed` — A pin has been renamed (Subject == URigVMPin)
- L31 _public enumerator_ `PinExpansionChanged` — A pin's expansion state has changed(Subject == URigVMPin)
- L32 _public enumerator_ `PinWatchedChanged` — A pin's watch state has changed (Subject == URigVMPin)
- L33 _public enumerator_ `PinArraySizeChanged` — An array pin's size has changed (Subject == URigVMPin)
- L34 _public enumerator_ `PinDefaultValueChanged` — A pin's default value has changed (Subject == URigVMPin)
- L35 _public enumerator_ `PinDirectionChanged` — A pin's direction has changed (Subject == URigVMPin)
- L36 _public enumerator_ `PinTypeChanged` — A pin's data type has changed (Subject == URigVMPin)
- L37 _public enumerator_ `PinIndexChanged` — A pin's index has changed (Subject == URigVMPin)
- L38 _public enumerator_ `LinkAdded` — A link has been added (Subject == URigVMLink)
- L39 _public enumerator_ `LinkRemoved` — A link has been removed (Subject == URigVMLink)
- L40 _public enumerator_ `CommentTextChanged` — A comment node's text has changed (Subject == URigVMCommentNode)
- L41 _public enumerator_ `VariableAdded` — A variable has been added (Subject == URigVMVariableNode)
- L42 _public enumerator_ `VariableRemoved` — A variable has been removed (Subject == URigVMVariableNode)
- L43 _public enumerator_ `VariableRenamed` — A variable has been renamed (Subject == URigVMVariableNode)
- L44 _public enumerator_ `InteractionBracketOpened` — A bracket has been opened (Subject == nullptr)
- L45 _public enumerator_ `InteractionBracketClosed` — A bracket has been opened (Subject == nullptr)
- L46 _public enumerator_ `InteractionBracketCanceled` — A bracket has been canceled (Subject == nullptr)
- L47 _public enumerator_ `PinBoundVariableChanged` — A pin has been bound or unbound to / from a variable (Subject == URigVMPin)
- L48 _public enumerator_ `NodeRenamed` — A node has been renamed in the graph (Subject == URigVMNode)
- L49 _public enumerator_ `FunctionRenamed` — A function has been renamed in the graph (Subject == URigVMLibraryNode)
- L50 _public enumerator_ `NodeReferenceChanged` — A node has changed it's referenced function
- L51 _public enumerator_ `NodeCategoryChanged` — A node's category has changed (Subject == URigVMNode)
- L52 _public enumerator_ `NodeKeywordsChanged` — A node's keywords have changed (Subject == URigVMNode)
- L53 _public enumerator_ `NodeDescriptionChanged` — A node's description has changed (Subject == URigVMNode)
- L54 _public enumerator_ `VariableRemappingChanged` — (DEPRECATED) A function reference node's remapping has changed (Subject == URigVMFunctionReferenceNode)
- L55 _public enumerator_ `LibraryTemplateChanged` — The definition of a library node's template has changed (Subject == URigVMLibraryNode)
- L56 _public enumerator_ `FunctionAccessChanged` — The function has been made public/private (Subject == URigVMLibraryNode)
- L57 _public enumerator_ `VariantTagsChanged` — The tags in the header of this function variant have changed (Subject == URigVMLibraryNode)
- L58 _public enumerator_ `PinDisplayNameChanged` — The display name of a pin has changed - requiring a rebuild of the node user interface (Subject == URigVMPin)
- L59 _public enumerator_ `PinCategoryChanged` — The category of a pin has changed - requiring a rebuild of the node user interface (Subject == URigVMPin)
- L60 _public enumerator_ `PinCategoriesChanged` — The category list of a node has changed - requiring a rebuild of the node user interface (Subject == URigVMNode)
- L61 _public enumerator_ `PinCategoryExpansionChanged` — The category of a pin expanded / collapsed (Subject == URigVMNode)
- L62 _public enumerator_ `FunctionVariantGuidChanged` — The guid for a function has changed (Subject == URigVMLibraryNode)
- L63 _public enumerator_ `NodeEarlyExitChanged` — The node's early exit state has changed
- L64 _public enumerator_ `LocalVariableDefaultValueChanged` — A local variable default value has been set (Subject == URigVMLibraryNode)
- L65 _public enumerator_ `LocalVariableAdded` — A local variable has been added to a function (Subject == URigVMLibraryNode)
- L66 _public enumerator_ `LocalVariableRemoved` — A local variable has been removed from a function (Subject == URigVMLibraryNode)
- L67 _public enumerator_ `LocalVariableRenamed` — A local variable has been renamed inside a function (Subject == URigVMLibraryNode)
- L68 _public enumerator_ `LocalVariableTypeChanged` — A local variable has been renamed inside a function (Subject == URigVMLibraryNode)
- L69 _public enumerator_ `LocalVariableIndexChanged` — A local variable's index has changed (Subject == URigVMLibraryNode)
- L70 _public enumerator_ `Invalid` — The max for this enum (used for guarding)

#### Free symbols / members of external scopes

- L74 _delegate_ `DECLARE_TS_MULTICAST_DELEGATE_ThreeParams(FRigVMGraphModifiedEvent, ERigVMGraphNotifType , URigVMGraph* , UObject* );` — A delegate for subscribing / reacting to graph modifications.
- L74 _prototype_ `DECLARE_TS_MULTICAST_DELEGATE_ThreeParams(FRigVMGraphModifiedEvent, ERigVMGraphNotifType , URigVMGraph* , UObject* );` — A delegate for subscribing / reacting to graph modifications.
- L77 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FRigVMGraphModifiedDynamicEvent, ERigVMGraphNotifType, NotifType, URigVMGraph*, Graph, UObject*, Subject);` — A dynamic delegate for subscribing / reacting to graph modifications (used for Python integration).
- L77 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FRigVMGraphModifiedDynamicEvent, ERigVMGraphNotifType, NotifType, URigVMGraph*, Graph, UObject*, Subject);` — A dynamic delegate for subscribing / reacting to graph modifications (used for Python integration).

### `Plugins/Runtime/RigVM/Source/RigVMDeveloper/Public/RigVMModel/RigVMPin.h` (Public)


#### class `URigVMInjectionInfo`  
`class URigVMInjectionInfo: public UObject`  
_L35-80_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UObject`
- desc: The Injected Info is used for injecting a node on a pin. Injected nodes are not visible to the user, but they are normal nodes on the graph.
- L41 _public function_ `URigVMInjectionInfo()`
- L48 _public member_ `TObjectPtr<URigVMUnitNode> UnitNode_DEPRECATED;` — `UPROPERTY()`
- L52 _public member_ `TObjectPtr<URigVMNode> Node;` — `UPROPERTY()`
- L55 _public member_ `bool bInjectedAsInput;` — `UPROPERTY()`
- L58 _public member_ `TObjectPtr<URigVMPin> InputPin;` — `UPROPERTY()`
- L61 _public member_ `TObjectPtr<URigVMPin> OutputPin;` — `UPROPERTY()`
- L65 _public prototype_ `URigVMGraph* GetGraph() const;` — `UFUNCTION(BlueprintCallable, Category = RigVMInjectionInfo)` — Returns the graph of this injected node.
- L69 _public prototype_ `URigVMPin* GetPin() const;` — `UFUNCTION(BlueprintCallable, Category = RigVMInjectionInfo)` — Returns the pin of this injected node.
- L79 _public prototype_ `FWeakInfo GetWeakInfo() const;`

#### struct `URigVMInjectionInfo::FWeakInfo`  
`struct FWeakInfo`  
_L71-77_
- L73 _public member_ `TWeakObjectPtr<URigVMNode> Node;`
- L74 _public member_ `bool bInjectedAsInput;`
- L75 _public member_ `FName InputPinName;`
- L76 _public member_ `FName OutputPinName;`

#### enum `ERigVMPinDefaultValueType`  
`enum class ERigVMPinDefaultValueType : uint8`  
_L83-89_
- reflection: `UENUM()`
- L85 _public enumerator_ `AutoDetect` — Detect if this is an unchanged or overridden value based on the delta
- L86 _public enumerator_ `Unset` — The value is unchanged and will remain the original default
- L87 _public enumerator_ `Override` — The value is overridden by the user and should stay like this no matter what
- L88 _public enumerator_ `KeepValueType` — The value type should be kept as well as the value itself (don't touch this)

#### class `URigVMPin`  
`class URigVMPin : public UObject`  
_L103-680_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UObject`
- desc: The Pin represents a single connector / pin on a node in the RigVM model. Pins can be connected based on rules. Pins also provide access to a 'PinPath', which essentially represents . separated list of names to reach the pin within the owning graph. PinPaths are unique. In comparison to the EdGraph Pin the URigVMPin supports the concept of 'SubPins', so child / parent relationships between pins. A FVector Pin for example might have its X, Y and Z components as SubPins. Array Pins will have its elements as SubPins, and so on. A URigVMPin is owned solely by a URigVMNode.
- L109 _public prototype_ `virtual void Serialize(FArchive& Ar) override;` — UObject interface
- L110 _public prototype_ `virtual void PostLoad() override;`
- L137 _public typedef_ `typedef TMap<FRigVMASTProxy, FPinOverrideValue> FPinOverrideMap;` — A map used to override pin default values
- L138 _public typedef_ `typedef TPair<FRigVMASTProxy, const FPinOverrideMap&> FPinOverride;`
- L139 _public member_ `static const URigVMPin::FPinOverrideMap EmptyPinOverrideMap;`
- L140 _public member_ `static const FPinOverride EmptyPinOverride;`
- L143 _public prototype_ `static bool SplitPinPathAtStart(const FString& InPinPath, FString& LeftMost, FString& Right);` — Splits a PinPath at the start, so for example "Node.Color.R" becomes "Node" and "Color.R"
- L144 _public prototype_ `static bool SplitPinPathAtStart(FStringView InPinPath, FStringView& LeftMost, FStringView& Right);`
- L147 _public prototype_ `static bool SplitPinPathAtEnd(const FString& InPinPath, FString& Left, FString& RightMost);` — Splits a PinPath at the start, so for example "Node.Color.R" becomes "Node.Color" and "R"
- L150 _public prototype_ `static bool SplitPinPath(const FString& InPinPath, TArray<FString>& Parts);` — Splits a PinPath into all segments, so for example "Node.Color.R" becomes ["Node", "Color", "R"]
- L153 _public prototype_ `static FString JoinPinPath(const FString& Left, const FString& Right);` — Joins a PinPath from to segments, so for example "Node.Color" and "R" becomes "Node.Color.R"
- L156 _public prototype_ `static FString JoinPinPath(const TArray<FString>& InParts);` — Joins a PinPath from to segments, so for example ["Node", "Color", "R"] becomes "Node.Color.R"
- L159 _public prototype_ `static TArray<FString> SplitDefaultValue(const FString& InDefaultValue);` — Splits the default value into name-value pairs
- L161 _public prototype_ `static FString GetDefaultValueForArray(TConstArrayView<FString> InDefaultValues);` — Joins a collection of element DefaultValues into a default value for an array of those elements
- L164 _public prototype_ `URigVMPin();` — Default constructor
- L167 _public prototype_ `bool NameEquals(FStringView InName, bool bFollowCoreRedirectors = false) const;` — returns true if the name of this pin matches a given name
- L172 _public prototype_ `FString GetPinPath(bool bUseNodePath = false) const;` — `UFUNCTION(BlueprintCallable, Category = RigVMPin)` — Returns a . separated path containing all names of the pin and its owners, this includes the node name, for example "Node.Color.R"
- L177 _public prototype_ `FString GetSubPinPath(const URigVMPin* InParentPin, bool bIncludeParentPinName = false) const;` — `UFUNCTION(BlueprintCallable, Category = RigVMPin)` — Returns a . separated path containing all names of the pin and its owners until we hit the provided parent pin.
- L182 _public prototype_ `FString GetCategory() const;` — `UFUNCTION(BlueprintCallable, Category = RigVMPin)` — Returns the category on a pin. The category is UI relevant only and used to order pins in the user interface of the node as well as on the details panel.
- L187 _public prototype_ `int32 GetIndexInCategory() const;` — `UFUNCTION(BlueprintCallable, Category = RigVMPin)` — Returns index within a category on a pin. The category is UI relevant only and used to order pins in the user interface of the node as well as on the details panel.
- L196 _public prototype_ `FString GetSegmentPath(bool bIncludeRootPin = false) const;` — `UFUNCTION(BlueprintCallable, Category = RigVMPin)` — Returns a . separated path containing all names of the pin within its main memory owner / storage. This is typically used to create an offset pointer within memory (FRigVMRegisterOffset). So for example for a PinPath such as "Node.Transform.Translation.X" the corresponding SegmentPath is "Translation.X", since the transform is the storage / memory.
- L201 _public prototype_ `void GetExposedPinChain(TArray<const URigVMPin*>& OutExposedPins) const;` — Populates an array of pins which will be reduced to the same operand in the VM. This includes Source-Target pins in different nodes, pins in collapse and referenced function nodes, and their corresponding entry and return nodes.
- L205 _public prototype_ `FName GetDisplayName() const;` — `UFUNCTION(BlueprintCallable, Category = RigVMPin)` — Returns the display label of the pin
- L209 _public prototype_ `ERigVMPinDirection GetDirection() const;` — `UFUNCTION(BlueprintCallable, Category = RigVMPin)` — Returns the direction of the pin
- L213 _public prototype_ `bool IsExpanded() const;` — `UFUNCTION(BlueprintCallable, Category = RigVMPin)` — Returns true if the pin is currently expanded
- L217 _public prototype_ `bool IsDefinedAsConstant() const;` — `UFUNCTION(BlueprintCallable, Category = RigVMPin)` — Returns true if the pin is defined as a constant value / literal
- L221 _public prototype_ `bool IsDefinedAsInputVariable() const;` — `UFUNCTION(BlueprintCallable, Category = RigVMPin)` — Returns true if the pin is defined as an input variable
- L224 _public prototype_ `FRigVMGraphVariableDescription GetInputVariableDescription() const;` — Returns the description of the input variable
- L228 _public prototype_ `bool RequiresWatch(const bool bCheckExposedPinChain = false) const;` — `UFUNCTION(BlueprintCallable, Category = RigVMPin)` — Returns true if the pin should be watched
- L232 _public prototype_ `bool IsEnum() const;` — `UFUNCTION(BlueprintCallable, Category = RigVMPin)` — Returns true if the data type of the Pin is a enum
- L236 _public prototype_ `bool IsStruct() const;` — `UFUNCTION(BlueprintCallable, Category = RigVMPin)` — Returns true if the data type of the Pin is a struct
- L240 _public prototype_ `bool IsStructMember() const;` — `UFUNCTION(BlueprintCallable, Category = RigVMPin)` — Returns true if the Pin is a SubPin within a struct
- L244 _public prototype_ `bool IsUObject() const;` — `UFUNCTION(BlueprintCallable, Category = RigVMPin)` — Returns true if the data type of the Pin is a uobject
- L248 _public prototype_ `bool IsInterface() const;` — `UFUNCTION(BlueprintCallable, Category = RigVMPin)` — Returns true if the data type of the Pin is a interface
- L252 _public prototype_ `bool IsArray() const;` — `UFUNCTION(BlueprintCallable, Category = RigVMPin)` — Returns true if the data type of the Pin is an array
- L256 _public prototype_ `bool IsArrayElement() const;` — `UFUNCTION(BlueprintCallable, Category = RigVMPin)` — Returns true if the Pin is a SubPin within an array
- L260 _public prototype_ `bool IsDynamicArray() const;` — `UFUNCTION(BlueprintCallable, Category = RigVMPin)` — Returns true if this pin represents a dynamic array
- L264 _public function_ `bool IsReferenceCountedContainer() const` — `UFUNCTION(BlueprintCallable, Category = RigVMPin)` — Returns true if this data type is referenced counted
- L268 _public prototype_ `bool IsLazy() const;` — `UFUNCTION(BlueprintCallable, Category = RigVMPin)` — Returns true if this pin's value may be executed lazily
- L272 _public prototype_ `int32 GetPinIndex() const;` — `UFUNCTION(BlueprintCallable, Category = RigVMPin)` — Returns the index of the Pin within the node / parent Pin
- L276 _public prototype_ `int32 GetAbsolutePinIndex() const;` — `UFUNCTION(BlueprintCallable, Category = RigVMPin)` — Returns the absolute index of the Pin within the node / parent Pin
- L280 _public prototype_ `int32 GetArraySize() const;` — `UFUNCTION(BlueprintCallable, Category = RigVMPin)` — Returns the number of elements within an array Pin
- L284 _public prototype_ `FString GetCPPType() const;` — `UFUNCTION(BlueprintCallable, Category = RigVMPin)` — Returns the C++ data type of the pin
- L288 _public prototype_ `FString GetArrayElementCppType() const;` — `UFUNCTION(BlueprintCallable, Category = RigVMPin)` — Returns the C++ data type of an element of the Pin array
- L291 _public prototype_ `FRigVMTemplateArgumentType GetTemplateArgumentType() const;` — Returns the argument type this pin would represent within a template
- L294 _public prototype_ `TRigVMTypeIndex GetTypeIndex() const;` — Returns the argument type index this pin would represent within a template
- L298 _public prototype_ `bool IsStringType() const;` — `UFUNCTION(BlueprintCallable, Category = RigVMPin)` — Returns true if the C++ data type is FString or FName
- L302 _public prototype_ `bool IsExecuteContext() const;` — `UFUNCTION(BlueprintCallable, Category = RigVMPin)` — Returns true if the C++ data type is an execute context
- L306 _public prototype_ `bool IsWildCard() const;` — `UFUNCTION(BlueprintCallable, Category = RigVMPin)` — Returns true if the C++ data type is unknown
- L310 _public prototype_ `bool ContainsWildCardSubPin() const;` — `UFUNCTION(BlueprintCallable, Category = RigVMPin)` — Returns true if any of the subpins is a wildcard
- L314 _public prototype_ `bool IsFixedSizeArray() const;` — `UFUNCTION(BlueprintCallable, Category = RigVMPin)` — Returns true if this pin is an array that should be displayed as elements only
- L318 _public prototype_ `bool ShouldOnlyShowSubPins() const;` — `UFUNCTION(BlueprintCallable, Category = RigVMPin)` — Returns true if this pin is an array that should be displayed as elements only
- L322 _public prototype_ `bool ShouldHideSubPins() const;` — `UFUNCTION(BlueprintCallable, Category = RigVMPin)` — Returns true if this pin's subpins should be hidden in the UI
- L325 _public prototype_ `FString GetOriginalDefaultValue() const;` — `UFUNCTION(BlueprintCallable, Category = RigVMPin)`
- L328 _public prototype_ `bool HasOriginalDefaultValue() const;` — `UFUNCTION(BlueprintCallable, Category = RigVMPin)`
- L336 _public prototype_ `FString GetDefaultValue() const;` — `UFUNCTION(BlueprintCallable, Category = RigVMPin)` — Returns the default value of the Pin as a string. Note that this value is computed based on the Pin's SubPins - so for example for a FVector typed Pin the default value is actually composed out of the default values of the X, Y and Z SubPins.
- L339 _public prototype_ `FString GetDefaultValue(const FPinOverride& InOverride, bool bAdaptValueForPinType = true) const;` — Returns the default value with an additional override ma
- L342 _public prototype_ `UObject* GetDefaultValueObject() const;` — Returns the default value object if this pin represents a UObject
- L345 _public prototype_ `FString GetDefaultValueStoredByUserInterface() const;` — Returns the default value as stored by the user.
- L349 _public prototype_ `bool IsValidDefaultValue(const FString& InDefaultValue) const;` — `UFUNCTION(BlueprintPure, Category = RigVMPin)` — Returns true if the default value provided is valid
- L354 _public prototype_ `bool HasUserProvidedDefaultValue() const;` — `UE_DEPRECATED(5.6, "Please use URigVMPin::HasDefaultValueOverride()")` — `UFUNCTION(BlueprintPure, Category = RigVMPin)` — Returns true if the default value was ever changed by the user
- L358 _public prototype_ `bool HasDefaultValueOverride() const;` — `UFUNCTION(BlueprintPure, Category = RigVMPin)` — Returns true if the default value was ever changed by the user
- L362 _public function_ `ERigVMPinDefaultValueType GetDefaultValueType() const` — `UFUNCTION(BlueprintPure, Category = RigVMPin)` — Returns true if the pin can / may provide a default value
- L366 _public prototype_ `bool CanProvideDefaultValue() const;` — `UFUNCTION(BlueprintPure, Category = RigVMPin)` — Returns true if the pin can / may provide a default value
- L369 _public prototype_ `FString ClampDefaultValueFromMetaData(const FString& InDefaultValue) const;` — Returns the default value clamped with the limit meta values defined by the UPROPERTY in URigVMUnitNodes
- L373 _public prototype_ `FString GetMetaData(FName InKey) const;` — `UFUNCTION(BlueprintCallable, Category = RigVMPin)` — Returns the keyed metadata associated with this pin, if any
- L377 _public prototype_ `bool HasMetaData(FName InKey) const;` — `UFUNCTION(BlueprintCallable, Category = RigVMPin)` — Returns whether the keyed metadata associated with this pin exists (can be empty)
- L382 _public prototype_ `FName GetCustomWidgetName() const;` — `UFUNCTION(BlueprintCallable, Category = RigVMPin)` — Returns the name of a custom widget to be used for editing the Pin.
- L386 _public prototype_ `FText GetToolTipText() const;` — `UFUNCTION(BlueprintCallable, Category = RigVMPin)` — Returns the tooltip of this pin
- L391 _public prototype_ `UObject* GetCPPTypeObject() const;` — `UFUNCTION(BlueprintCallable, Category = RigVMPin)` — Returns the struct of the data type of the Pin, or nullptr otherwise.
- L396 _public prototype_ `UScriptStruct* GetScriptStruct() const;` — `UFUNCTION(BlueprintCallable, Category = RigVMPin)` — Returns the struct of the data type of the Pin, or nullptr otherwise.
- L400 _public prototype_ `UScriptStruct* GetParentScriptStruct(const URigVMUnitNode* FallbackNode) const;` — `UFUNCTION(BlueprintCallable, Category = RigVMPin)` — Returns the parent struct of the data type of the Pin
- L405 _public prototype_ `UEnum* GetEnum() const;` — `UFUNCTION(BlueprintCallable, Category = RigVMPin)` — Returns the enum of the data type of the Pin, or nullptr otherwise.
- L410 _public prototype_ `URigVMPin* GetParentPin() const;` — `UFUNCTION(BlueprintCallable, Category = RigVMPin)` — Returns the parent Pin - or nullptr if the Pin is nested directly below a node.
- L416 _public prototype_ `URigVMPin* GetRootPin() const;` — `UFUNCTION(BlueprintCallable, Category = RigVMPin)` — Returns the top-most parent Pin, so for example for "Node.Transform.Translation.X" this returns the Pin for "Node.Transform".
- L420 _public prototype_ `bool IsRootPin() const;` — `UFUNCTION(BlueprintCallable, Category = RigVMPin)` — Returns true if this pin is a root pin
- L426 _public prototype_ `URigVMPin* GetPinForLink() const;` — `UFUNCTION(BlueprintCallable, Category = RigVMPin)` — Returns the pin to be used for a link. This might differ from this actual pin, since the pin might contain injected nodes.
- L432 _public prototype_ `URigVMLink* FindLinkForPin(const URigVMPin* InOtherPin) const;` — `UFUNCTION(BlueprintCallable, Category = RigVMPin)` — Returns the link that represents the connection between this pin and InOtherPin. nullptr is returned if the pins are not connected.
- L438 _public prototype_ `URigVMPin* GetOriginalPinFromInjectedNode() const;` — `UFUNCTION(BlueprintCallable, Category = RigVMPin)` — Returns the original pin for a pin on an injected node. This can be used to determine where a link should go in the user interface
- L442 _public prototype_ `const TArray<URigVMPin*>& GetSubPins() const;` — `UFUNCTION(BlueprintCallable, Category = RigVMPin)` — Returns all of the SubPins of this one.
- L446 _public prototype_ `TArray<URigVMPin*> GetAllSubPinsRecursively() const;` — `UFUNCTION(BlueprintCallable, Category = RigVMPin)` — Returns all of the SubPins of this one including sub-sub-pins
- L450 _public prototype_ `URigVMPin* FindSubPin(const FString& InPinPath) const;` — `UFUNCTION(BlueprintCallable, Category = RigVMPin)` — Returns a SubPin given a name / path or nullptr.
- L451 _public prototype_ `URigVMPin* FindSubPinView(FStringView InPinPath) const;`
- L455 _public prototype_ `bool IsLinkedTo(const URigVMPin* InPin) const;` — `UFUNCTION(BlueprintCallable, Category = RigVMPin)` — Returns true if this Pin is linked to another Pin
- L458 _public prototype_ `bool IsLinked(bool bRecursive = false) const;` — Returns true if the pin has any link
- L462 _public prototype_ `const TArray<URigVMLink*>& GetLinks() const;` — `UFUNCTION(BlueprintCallable, Category = RigVMPin)` — Returns all of the links linked to this Pin.
- L467 _public prototype_ `TArray<URigVMPin*> GetLinkedSourcePins(bool bRecursive = false) const;` — `UFUNCTION(BlueprintCallable, Category = RigVMPin)` — Returns all of the linked source Pins, using this Pin as the target.
- L472 _public prototype_ `TArray<URigVMPin*> GetLinkedTargetPins(bool bRecursive = false) const;` — `UFUNCTION(BlueprintCallable, Category = RigVMPin)` — Returns all of the linked target Pins, using this Pin as the source.
- L477 _public prototype_ `TArray<URigVMLink*> GetSourceLinks(bool bRecursive = false) const;` — `UFUNCTION(BlueprintCallable, Category = RigVMPin)` — Returns all of the source pins using this Pin as the target.
- L482 _public prototype_ `TArray<URigVMLink*> GetTargetLinks(bool bRecursive = false) const;` — `UFUNCTION(BlueprintCallable, Category = RigVMPin)` — Returns all of the target links, using this Pin as the source.
- L486 _public prototype_ `URigVMNode* GetNode() const;` — `UFUNCTION(BlueprintCallable, Category = RigVMPin)` — Returns the node of this Pin.
- L490 _public prototype_ `URigVMGraph* GetGraph() const;` — `UFUNCTION(BlueprintCallable, Category = RigVMPin)` — Returns the graph of this Pin.
- L494 _public prototype_ `static bool CanLink(const URigVMPin* InSourcePin, const URigVMPin* InTargetPin, FString* OutFailureReason, const FRigVMByteCode* InByteCode, ERigVMPinDirection InUserLinkDirection = ERigVMPinDirection::IO, bool bInAllowWildcard = false, bool bEnableTypeCasting = true);` — Returns true is the two provided source and target Pins can be linked to one another.
- L497 _public function_ `bool HasInjectedNodes() const` — Returns true if this pin has injected nodes
- L500 _public prototype_ `bool HasInjectedUnitNodes() const;` — Returns true if this pin has injected nodes
- L503 _public function_ `const TArray<URigVMInjectionInfo*> GetInjectedNodes() const` — Returns the injected nodes this pin contains.
- L505 _public prototype_ `URigVMVariableNode* GetBoundVariableNode() const;`
- L508 _public prototype_ `const FString GetBoundVariablePath() const;` — Returns the variable bound to this pin (or NAME_None)
- L511 _public prototype_ `const FString GetBoundVariablePath(const FPinOverride& InOverride) const;` — Returns the variable bound to this pin (or NAME_None)
- L514 _public prototype_ `FString GetBoundVariableName() const;` — Returns the variable bound to this pin (or NAME_None)
- L517 _public prototype_ `bool IsBoundToVariable() const;` — Returns true if this pin is bound to a variable
- L520 _public prototype_ `bool IsBoundToVariable(const FPinOverride& InOverride) const;` — Returns true if this pin is bound to a variable
- L523 _public prototype_ `bool IsBoundToExternalVariable() const;` — Returns true if this pin is bound to an external variable
- L526 _public prototype_ `bool IsBoundToLocalVariable() const;` — Returns true if this pin is bound to a local variable
- L529 _public prototype_ `bool IsBoundToInputArgument() const;` — Returns true if this pin is bound to an input argument
- L532 _public prototype_ `bool CanBeBoundToVariable(const FRigVMExternalVariable& InExternalVariable, const FString& InSegmentPath = FString()) const;` — Returns true if the pin can be bound to a given variable
- L535 _public prototype_ `bool ShowInDetailsPanelOnly() const;` — Returns true if the pin should not show up on a node, but in the details panel
- L538 _public prototype_ `FRigVMExternalVariable ToExternalVariable() const;` — Returns an external variable matching this pin's type
- L541 _public prototype_ `bool IsOrphanPin() const;` — Returns true if the pin has been orphaned
- L543 _public prototype_ `uint32 GetStructureHash() const;`
- L547 _public prototype_ `bool IsTraitPin() const;` — `UFUNCTION(BlueprintPure, Category = RigVMPin)` — Returns true if this pin represents a trait
- L550 _public prototype_ `bool IsProgrammaticPin() const;` — Returns true if this pin represents a trait's programmatic pin
- L553 _public prototype_ `TArray<URigVMPin*> GetProgrammaticSubPins() const;` — Get all the sub-pins that are programmatic
- L556 _public prototype_ `TSharedPtr<FStructOnScope> GetTraitInstance(bool bUseDefaultValueFromPin = true) const;` — Returns the trait backing up this pin
- L559 _public prototype_ `UScriptStruct* GetTraitScriptStruct() const;` — Returns the struct of the trait backing up this pin
- L561 _public prototype_ `const uint32& GetNodeCachedValueVersion() const;`
- L562 _public prototype_ `const uint32& GetCachedValueVersion() const;`
- L566 _private prototype_ `void UpdateTypeInformationIfRequired() const;`
- L567 _private prototype_ `void SetNameFromIndex();`
- L568 _private prototype_ `void SetDisplayName(const FName& InDisplayName);`
- L569 _private prototype_ `void IncrementVersion(bool bAffectParentPin = true, bool bAffectSubPins = true);`
- L571 _private prototype_ `void GetExposedPinChainImpl(TArray<const URigVMPin*>& OutExposedPins, TArray<const URigVMPin*>& VisitedPins) const;`
- L573 _private prototype_ `void ClearPinPathCache() const;`
- L576 _private member_ `FName DisplayName;` — `UPROPERTY()`
- L583 _private member_ `ERigVMPinDirection Direction;` — `UPROPERTY()`
- L586 _private member_ `bool bIsExpanded;` — `UPROPERTY()`
- L589 _private member_ `bool bIsConstant;` — `UPROPERTY()`
- L592 _private member_ `bool bIsInputVariable;` — `UPROPERTY()`
- L595 _private member_ `bool bRequiresWatch;` — `UPROPERTY(transient)`
- L598 _private member_ `bool bIsDynamicArray;` — `UPROPERTY()`
- L601 _private member_ `bool bIsLazy;` — `UPROPERTY()`
- L604 _private member_ `FString CPPType;` — `UPROPERTY()`
- L611 _private member_ `TObjectPtr<UObject> CPPTypeObject;` — `UPROPERTY()` — serialize object ptr here to keep track of the latest version of the type object, type object can reference assets like user defined struct, which can be renamed or moved to new locations, serializing the type object with the pin ensure automatic update whenever those things happen
- L614 _private member_ `FName CPPTypeObjectPath;` — `UPROPERTY()`
- L617 _private member_ `FString DefaultValue;` — `UPROPERTY()`
- L621 _private member_ `TObjectPtr<UObject> DefaultValueObject;` — `UPROPERTY()` — If the default value for this pin should be an object, we store a pointer to it
- L624 _private member_ `ERigVMPinDefaultValueType DefaultValueType;` — `UPROPERTY()`
- L627 _private member_ `FName CustomWidgetName;` — `UPROPERTY()`
- L630 _private member_ `TArray<TObjectPtr<URigVMPin>> SubPins;` — `UPROPERTY()`
- L633 _private member_ `TArray<TObjectPtr<URigVMLink>> Links;` — `UPROPERTY(transient)`
- L636 _private member_ `TArray<TObjectPtr<URigVMInjectionInfo>> InjectionInfos;` — `UPROPERTY()`
- L639 _private member_ `FString UserDefinedCategory;` — `UPROPERTY()`
- L642 _private member_ `int32 IndexInCategory;` — `UPROPERTY()`
- L646 _private member_ `FString BoundVariablePath_DEPRECATED;` — `UPROPERTY()`
- L649 _private member_ `uint32 PinVersion;`
- L650 _private member_ `mutable uint32 CombinedPinVersion;`
- L652 _private member_ `mutable FString LastKnownCPPType;`
- L653 _private member_ `mutable TRigVMTypeIndex LastKnownTypeIndex;`
- L654 _private member_ `mutable TRigVMModelCachedValue<URigVMPin, bool> CachedIsStringType;`
- L655 _private member_ `mutable TRigVMModelCachedValue<URigVMPin, FString> CachedDefaultValue;`
- L656 _private member_ `mutable TRigVMModelCachedValue<URigVMPin, FString> CachedAdaptedDefaultValue;`
- L657 _private member_ `mutable TRigVMModelCachedValue<URigVMPin, uint32> CachedCPPTypeObjectHash;`
- L658 _private member_ `mutable TRigVMModelCachedValue<URigVMPin, bool> CachedShowInDetailsPanelOnly;`
- L659 _private member_ `mutable TRigVMModelCachedValue<URigVMPin, FString> CachedPinPath;`
- L660 _private member_ `mutable TRigVMModelCachedValue<URigVMPin, FString> CachedPinPathWithNodePath;`
- L661 _private member_ `mutable TRigVMModelCachedValue<URigVMPin, FString> CachedPinCategory;`
- L662 _private member_ `mutable TRigVMModelCachedValue<URigVMPin, FName> CachedDisplayName;`
- L663 _private member_ `mutable TRigVMModelCachedValue<URigVMPin, bool> CachedDefaultValueOverride;`
- L664 _private member_ `mutable TRigVMModelCachedValue<URigVMPin, bool> CachedHasOriginalDefaultValue;`
- L666 _private member_ `static const inline TCHAR* OrphanPinPrefix = TEXT("Orp`

#### struct `URigVMPin::FPinOverrideValue`  
`struct FPinOverrideValue`  
_L113-134_
- desc: A struct to store a pin override value
- L115 _public function_ `FPinOverrideValue() : DefaultValue() , BoundVariablePath()`
- L120 _public function_ `FPinOverrideValue(URigVMPin* InPin) : DefaultValue(InPin->GetDefaultValue()) , BoundVariablePath(InPin->GetBoundVariablePath())`
- L126 _public function_ `FPinOverrideValue(URigVMPin* InPin, const TPair<FRigVMASTProxy, const TMap<FRigVMASTProxy, FPinOverrideValue>&>& InOverride) : DefaultValue(InPin->GetDefaultValue(InOverride)) , BoundVariablePath(InPin->GetBoundVariablePath())`
- L132 _public member_ `FString DefaultValue;`
- L133 _public member_ `FString BoundVariablePath;`

#### class `FRigVMPinDefaultValueImportErrorContext`  
`class FRigVMPinDefaultValueImportErrorContext : public FOutputDevice`  
_L682-707_
- inherits: `FOutputDevice`
- L686 _public member_ `int32 NumErrors;`
- L688 _public function_ `FRigVMPinDefaultValueImportErrorContext( ELogVerbosity::Type InMaxVerbosity = ELogVerbosity::Warning ) : FOutputDevice() , NumErrors(0) , MaxVerbosity(InMaxVerbosity)`
- L695 _public function_ `virtual void Serialize(const TCHAR* V, ELogVerbosity::Type Verbosity, const class FName& Category) override`
- L703 _public function_ `ELogVerbosity::Type GetMaxVerbosity() const`
- L706 _private member_ `ELogVerbosity::Type MaxVerbosity;`

#### Free symbols / members of external scopes

- L18 _macro_ `#define UE_API RIGVMDEVELOPER_API`
- L27 _externvar_ `extern TAutoConsoleVariable<bool> CVarRigVMEnablePinOverrides;`

### `Plugins/Runtime/RigVM/Source/RigVMDeveloper/Public/RigVMModel/RigVMSchema.h` (Public)


#### class `URigVMSchema`  
`class URigVMSchema : public UObject`  
_L34-178_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- desc: The Schema is used to determine which actions are allowed on a graph. This includes any topological change.
- L41 _public prototype_ `URigVMSchema();` — Default constructor
- L44 _public function_ `UScriptStruct* GetExecuteContextStruct() const` — Returns the execute context struct this schema is using
- L47 _public prototype_ `virtual UClass* GetEdGraphSchemaClass() const;` — Returns the corresponding Ed Graph Schema class
- L50 _public prototype_ `virtual UClass* GetRuntimeAssetClass() const;` — Returns the corresponding runtime asset class to use for this schema
- L53 _public prototype_ `virtual UClass* GetEditorAssetClass() const;` — Returns the corresponding editor asset class to use for this schema
- L56 _public prototype_ `bool SupportsType(URigVMController* InController, TRigVMTypeIndex InTypeIndex) const;` — Returns true if a graph supports a given type
- L57 _public prototype_ `virtual bool SupportsType_NoLock(URigVMController* InController, TRigVMTypeIndex InTypeIndex, FRigVMRegistryHandle& InRegistry) const;`
- L60 _public prototype_ `bool SupportsUnitFunction(URigVMController* InController, const FRigVMFunction* InUnitFunction) const;` — Returns true if a graph supports a given unit function
- L61 _public prototype_ `virtual bool SupportsUnitFunction_NoLock(URigVMController* InController, const FRigVMFunction* InUnitFunction, FRigVMRegistryHandle& InRegistry) const;`
- L64 _public prototype_ `bool SupportsDispatchFactory(URigVMController* InController, const FRigVMDispatchFactory* InDispatchFactory) const;` — Returns true if a graph supports a given dispatch factory
- L65 _public prototype_ `virtual bool SupportsDispatchFactory_NoLock(URigVMController* InController, const FRigVMDispatchFactory* InDispatchFactory, FRigVMRegistryHandle& InRegistry) const;`
- L68 _public prototype_ `bool SupportsTemplate(URigVMController* InController, const FRigVMTemplate* InTemplate) const;` — Returns true if a graph supports a given template
- L69 _public prototype_ `virtual bool SupportsTemplate_NoLock(URigVMController* InController, const FRigVMTemplate* InTemplate, FRigVMRegistryHandle& InRegistry) const;`
- L72 _public prototype_ `bool SupportsGraphFunction(URigVMController* InController, const FRigVMGraphFunctionHeader* InGraphFunction) const;` — Returns true if a graph supports a given graph based function
- L73 _public prototype_ `virtual bool SupportsGraphFunction_NoLock(URigVMController* InController, const FRigVMGraphFunctionHeader* InGraphFunction, FRigVMRegistryHandle& InRegistry) const;`
- L76 _public prototype_ `bool SupportsExternalVariable(URigVMController* InController, const FRigVMExternalVariable* InExternalVariable) const;` — Returns true if a graph supports a given external variable
- L77 _public prototype_ `virtual bool SupportsExternalVariable_NoLock(URigVMController* InController, const FRigVMExternalVariable* InExternalVariable, FRigVMRegistryHandle& InRegistry) const;`
- L80 _public prototype_ `virtual bool SupportsNodeLayouts(const URigVMGraph* InGraph) const;` — Returns true if a graph supports pin categories / node layouts
- L83 _public prototype_ `virtual bool ShouldUnfoldStruct(URigVMController* InController, const UStruct* InStruct) const;` — Returns true if the pin for a given struct should be unfolded into subpins for a graph
- L86 _public prototype_ `virtual bool IsValidNodeName(const URigVMGraph* InGraph, const FName& InNodeName) const;` — Returns true if a node name is valid for a given graph
- L89 _public prototype_ `virtual bool CanAddNode(URigVMController* InController, const URigVMNode* InNode) const;` — Returns true if a given node can be added the graph
- L92 _public prototype_ `virtual bool CanRemoveNode(URigVMController* InController, const URigVMNode* InNode) const;` — Returns true if a given node can be removed from the graph
- L95 _public prototype_ `virtual bool CanRenameNode(URigVMController* InController, const URigVMNode* InNode, const FName& InNewNodeName) const;` — Returns true if a given node can be added the graph
- L98 _public prototype_ `virtual bool CanMoveNode(URigVMController* InController, const URigVMNode* InNode, const FVector2D& InNewPosition = FVector2D::ZeroVector) const;` — Returns true if a node can moved to a new position
- L101 _public prototype_ `virtual bool CanResizeNode(URigVMController* InController, const URigVMNode* InNode, const FVector2D& InNewSize = {100, 100}) const;` — Returns true if a node can resized to a new size
- L104 _public prototype_ `virtual bool CanSetNodeTitle(URigVMController* InController, const URigVMNode* InNode) const;` — Returns true if a node supports setting a node title
- L107 _public prototype_ `virtual bool CanRecolorNode(URigVMController* InController, const URigVMNode* InNode, const FLinearColor& InNewColor = FLinearColor::White) const;` — Returns true if a node can recolored to a new color
- L110 _public prototype_ `virtual bool CanAddLink(URigVMController* InController, const URigVMPin* InSourcePin, const URigVMPin* InTargetPin, const FRigVMByteCode* InByteCode, ERigVMPinDirection InUserLinkDirection = ERigVMPinDirection::IO, bool bInAllowWildcard = false, bool bEnableTypeCasting = true, FString* OutFailureReason = nullptr) const;` — Returns true if a link can be added between two pins
- L113 _public prototype_ `virtual bool CanBreakLink(URigVMController* InController, const URigVMPin* InSourcePin, const URigVMPin* InTargetPin) const;` — Returns true if a link exists between two pins and can be broken / removed
- L116 _public prototype_ `virtual bool CanCollapseNodes(URigVMController* InController, const TArrayView<URigVMNode* const>& InNodesToCollapse) const;` — Returns true if a set of nodes can be collapsed
- L119 _public prototype_ `virtual bool CanExpandNode(URigVMController* InController, const URigVMNode* InNodeToExpand) const;` — Returns true if a node can be expanded within a graph
- L122 _public prototype_ `virtual bool CanUnfoldPin(URigVMController* InController, const URigVMPin* InPinToUnfold) const;` — Returns true if a pin should be unfolded (represented by its subpins)
- L125 _public prototype_ `virtual bool CanBindVariable(URigVMController* InController, const URigVMPin* InPinToBind, const FRigVMExternalVariable* InVariableToBind, const FString& InNewBoundVariablePath) const;` — Returns true if a variable can be bound to a pin
- L128 _public prototype_ `virtual bool CanUnbindVariable(URigVMController* InController, const URigVMPin* InBoundPin) const;` — Returns true if a variable can be unbound from a pin
- L131 _public prototype_ `virtual bool CanAddFunction(URigVMController* InController, const URigVMNode* InFunctionNode) const;` — Returns true if functions definitions (not refs) can be added to the graph
- L134 _public prototype_ `virtual bool CanRemoveFunction(URigVMController* InController, const URigVMNode* InFunctionNode) const;` — Returns true if a function can be removed
- L136 _public function_ `static int32 GetMaxNameLength()`
- L137 _public prototype_ `virtual FString GetSanitizedName(const FString& InName, bool bAllowPeriod, bool bAllowSpace) const;`
- L138 _public prototype_ `virtual FString GetSanitizedGraphName(const FString& InName) const;`
- L139 _public prototype_ `virtual FString GetSanitizedNodeName(const FString& InName) const;`
- L140 _public prototype_ `virtual FString GetSanitizedVariableName(const FString& InName) const;`
- L141 _public prototype_ `virtual FString GetSanitizedPinName(const FString& InName) const;`
- L142 _public prototype_ `virtual FString GetSanitizedPinPath(const FString& InName) const;`
- L143 _public prototype_ `virtual FString GetGraphOuterName(const URigVMGraph* InGraph) const;`
- L144 _public prototype_ `virtual FString GetValidNodeName(const URigVMGraph* InGraph, const FString& InPrefix) const;`
- L145 _public prototype_ `static void SanitizeName(FString& InOutName, bool bAllowPeriod, bool bAllowSpace);`
- L148 _public prototype_ `static FName GetUniqueName(const FName& InName, TFunction<bool(const FName&)> IsNameAvailablePredicate, bool bAllowPeriod, bool bAllowSpace);` — Returns a unique name based on a IsNameAvailable predicate
- L153 _protected prototype_ `void SetExecuteContextStruct(UScriptStruct* InExecuteContextStruct);` — Sets the execute context struct this schema is using
- L155 _protected prototype_ `bool IsGraphEditable(const URigVMGraph* InGraph) const;`
- L156 _protected prototype_ `TObjectPtr<URigVMNode> FindEventNode(URigVMController* InController, const UScriptStruct* InScriptStruct) const;`
- L159 _protected function_ `virtual bool ShouldPatchGraphSchema() const`
- L162 _protected member_ `TObjectPtr<UScriptStruct> ExecuteContextStruct;` — `UPROPERTY(transient)`
- L163 _protected member_ `TArray<UStruct*> ValidExecuteContextStructs;`
- L164 _protected member_ `FRigVMRegistry* Registry;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API RIGVMDEVELOPER_API`
- L15 _macro_ `#define RIGVMSCHEMA_DEFAULT_FUNCTION_BODY \`

### `Plugins/Runtime/RigVM/Source/RigVMDeveloper/Public/RigVMModel/RigVMTraitDefaultValueStruct.h` (Public)


#### struct `FRigVMTraitDefaultValueStruct`  
`struct FRigVMTraitDefaultValueStruct`  
_L7-19_
- reflection: `USTRUCT()`
- L11 _public member_ `static const TCHAR* DefaultValuePropertyName;`
- L14 _public member_ `FInstancedPropertyBag PropertyBag;` — `UPROPERTY()`
- L16 _public prototype_ `void Init(UScriptStruct* InTraitScriptStruct);`
- L17 _public prototype_ `void SetValue(const FString& InDefaultValue);`
- L18 _public prototype_ `FString GetValue() const;`

### `Plugins/Runtime/RigVM/Source/RigVMDeveloper/Public/RigVMPythonUtils.h` (Public)


#### enum `RigVMPythonUtils::EPythonizeNameCase`  
`enum EPythonizeNameCase : uint8`  
_L19-25_
- desc: How should PythonizeName adjust the final name?
- L22 _public enumerator_ `Lower` — lower_snake_case
- L24 _public enumerator_ `Upper` — UPPER_SNAKE_CASE

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace RigVMPythonUtils`
- L27 _prototype_ `FString PythonizeName(FStringView InName, const EPythonizeNameCase InNameCase = EPythonizeNameCase::Lower);` (scope `RigVMPythonUtils`)
- L29 _prototype_ `FString TransformToPythonString(const FTransform& Transform);` (scope `RigVMPythonUtils`)
- L31 _prototype_ `FString Vector2DToPythonString(const FVector2D& Vector);` (scope `RigVMPythonUtils`)
- L33 _prototype_ `FString LinearColorToPythonString(const FLinearColor& Color);` (scope `RigVMPythonUtils`)
- L35 _prototype_ `FString EnumValueToPythonString(UEnum* Enum, int64 Value);` (scope `RigVMPythonUtils`)
- L38 _function_ `template<typename T> FString EnumValueToPythonString(int64 Value)` (scope `RigVMPythonUtils`)
- L44 _prototype_ `void Print(const FString& BlueprintTitle, const FString& InMessage);` (scope `RigVMPythonUtils`)
- L46 _prototype_ `void PrintPythonContext(const FString& InBlueprintName);` (scope `RigVMPythonUtils`)

### `Plugins/Runtime/RigVM/Source/RigVMDeveloper/Public/RigVMUserWorkflowRegistry.h` (Public)


#### class `URigVMUserWorkflowRegistry`  
`class URigVMUserWorkflowRegistry : public UObject`  
_L27-53_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UObject`
- L34 _public prototype_ `static URigVMUserWorkflowRegistry* Get();` — `UFUNCTION(BlueprintPure, Category = FRigVMUserWorkflowRegistry)`
- L37 _public prototype_ `int32 RegisterProvider(const UScriptStruct* InStruct, FRigVMUserWorkflowProvider InProvider);` — `UFUNCTION(BlueprintCallable, Category = FRigVMUserWorkflowRegistry)`
- L40 _public prototype_ `int32 RegisterProviderForFunction(const FString InFunctionNotation, FRigVMUserWorkflowProvider InProvider);` — `UFUNCTION(BlueprintCallable, Category = FRigVMUserWorkflowRegistry)`
- L43 _public prototype_ `void UnregisterProvider(int32 InHandle);` — `UFUNCTION(BlueprintCallable, Category = FRigVMUserWorkflowRegistry)`
- L46 _public prototype_ `TArray<FRigVMUserWorkflow> GetWorkflows(ERigVMUserWorkflowType InType, const UScriptStruct* InStruct, const UObject* InSubject) const;` — `UFUNCTION(BlueprintPure, Category = FRigVMUserWorkflowRegistry)`
- L50 _private member_ `int32 MaxHandle = 0;`
- L51 _private member_ `mutable TArray<TTuple<int32, const UScriptStruct*, FRigVMUserWorkflowProvider>> ProvidersForUnits;`
- L52 _private member_ `mutable TArray<TTuple<int32, const FString, FRigVMUserWorkflowProvider>> ProvidersForDispatchFunctions;`

#### Free symbols / members of external scopes

- L19 _macro_ `#define UE_API RIGVMDEVELOPER_API`
- L24 _delegate_ `DECLARE_DYNAMIC_DELEGATE_RetVal_OneParam(TArray<FRigVMUserWorkflow>, FRigVMUserWorkflowProvider, const UObject*, InSubject);`
- L24 _prototype_ `DECLARE_DYNAMIC_DELEGATE_RetVal_OneParam(TArray<FRigVMUserWorkflow>, FRigVMUserWorkflowProvider, const UObject*, InSubject);`
