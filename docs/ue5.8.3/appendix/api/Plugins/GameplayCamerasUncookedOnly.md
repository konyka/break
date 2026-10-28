# Plugins / GameplayCamerasUncookedOnly

- module root: `Plugins/Cameras/GameplayCameras/Source/GameplayCamerasUncookedOnly`
- headers: 9; symbols: 86
- symbol kinds: class=9, enum=1, enumerator=3, function=3, macro=2, member=11, namespace=4, prototype=53
- PrivateDependencyModuleNames: BlueprintGraph, Core, CoreUObject, Engine, Kismet, KismetCompiler, SlateCore, UnrealEd
- PublicDependencyModuleNames: GameplayCameras

### `Plugins/Cameras/GameplayCameras/Source/GameplayCamerasUncookedOnly/Private/BlueprintGraph/K2Node_CameraRigBase.h` (Private)


#### class `UK2Node_CameraRigBase`  
`class UK2Node_CameraRigBase : public UK2Node`  
_L23-77_
- reflection: `UCLASS(MinimalAPI, Abstract)`
- inherits: `UK2Node`
- desc: Utility base class for Blueprint nodes that can set camera rig parameters.
- L29 _public prototype_ `UK2Node_CameraRigBase(const FObjectInitializer& ObjectInit);`
- L34 _public prototype_ `virtual void BeginDestroy() override;` — UObject interface.
- L37 _public prototype_ `virtual void AllocateDefaultPins() override;` — UEdGraphNode interface.
- L38 _public prototype_ `virtual void ValidateNodeDuringCompilation(FCompilerResultsLog& MessageLog) const override;`
- L39 _public prototype_ `virtual bool CanJumpToDefinition() const override;`
- L40 _public prototype_ `virtual void JumpToDefinition() const override;`
- L43 _public prototype_ `virtual FText GetMenuCategory() const override;` — UK2Node interface.
- L44 _public prototype_ `virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;`
- L48 _public prototype_ `static FEdGraphPinType MakeBlendableParameterPinType(const UCameraObjectInterfaceBlendableParameter* BlendableParameter);`
- L49 _public prototype_ `static FEdGraphPinType MakeBlendableParameterPinType(ECameraVariableType CameraVariableType, const UScriptStruct* BlendableStructType);`
- L50 _public prototype_ `static FEdGraphPinType MakeDataParameterPinType(const UCameraObjectInterfaceDataParameter* DataParameter);`
- L51 _public prototype_ `static FEdGraphPinType MakeDataParameterPinType(ECameraContextDataType CameraContextDataType, ECameraContextDataContainerType CameraContextDataContainerType, const UObject* CameraContextDataTypeObject);`
- L56 _protected function_ `virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar, const FAssetData& CameraRigAssetData) const` — UK2Node_CameraRigBase interface.
- L60 _protected member_ `static const FName CameraNodeEvaluationResultPinName;`
- L62 _protected prototype_ `UEdGraphPin* GetCameraNodeEvaluationResultPin() const;`
- L63 _protected prototype_ `bool ValidateCameraRigBeforeExpandNode(FKismetCompilerContext& CompilerContext) const;`
- L65 _protected prototype_ `void OnCameraRigAssetBuilt(const UCameraRigAsset* InBuiltCameraRig);`
- L69 _protected prototype_ `static UK2Node_CallFunction* CreateMakeLiteralNode(FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph, UK2Node* SourceNode, UClass* FunctionLibraryClass, const TCHAR* FunctionName, UEdGraphPin* SourceValuePin);`
- L71 _protected prototype_ `static UK2Node* MakeLiteralValueForPin(FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph, UK2Node* SourceNode, UEdGraphPin* InValuePin);`
- L76 _protected member_ `TObjectPtr<UCameraRigAsset> CameraRig;` — `UPROPERTY()`

### `Plugins/Cameras/GameplayCameras/Source/GameplayCamerasUncookedOnly/Private/BlueprintGraph/K2Node_GetCameraRigParameter.h` (Private)


#### class `UK2Node_GetCameraRigParameter`  
`class UK2Node_GetCameraRigParameter : public UK2Node_SingleCameraRigParameterBase`  
_L17-35_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UK2Node_SingleCameraRigParameterBase`
- desc: Blueprint node that, given a camera rig, lets the user get the value of one single exposed parameter.
- L24 _public prototype_ `virtual void AllocateDefaultPins() override;` — UEdGraphNode interface.
- L25 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L26 _public prototype_ `virtual FText GetTooltipText() const override;`
- L28 _public function_ `virtual bool IsNodePure() const override` — virtual bool ShouldDrawCompact() const override { return true; }
- L29 _public prototype_ `virtual void ExpandNode(FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph) override;`
- L34 _protected prototype_ `void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar, const FAssetData& CameraRigAssetData) const;` — UK2Node_CameraRigBase interface.

### `Plugins/Cameras/GameplayCameras/Source/GameplayCamerasUncookedOnly/Private/BlueprintGraph/K2Node_GetCameraRigParameters.h` (Private)


#### class `UK2Node_GetCameraRigParameters`  
`class UK2Node_GetCameraRigParameters : public UK2Node_MultiCameraRigParametersBase`  
_L16-34_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UK2Node_MultiCameraRigParametersBase`
- desc: Blueprint node that, given a camera rig, lets the user get the values of all exposed parameters on that camera rig.
- L23 _public prototype_ `virtual void AllocateDefaultPins() override;` — UEdGraphNode interface.
- L24 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L25 _public prototype_ `virtual FText GetTooltipText() const override;`
- L27 _public function_ `virtual bool IsNodePure() const override` — virtual bool ShouldDrawCompact() const override { return true; }
- L28 _public prototype_ `virtual void ExpandNode(class FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph) override;`
- L33 _protected prototype_ `virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar, const FAssetData& CameraRigAssetData) const override;` — UK2Node_CameraRigBase interface.

### `Plugins/Cameras/GameplayCameras/Source/GameplayCamerasUncookedOnly/Private/BlueprintGraph/K2Node_MultiCameraRigParametersBase.h` (Private)


#### class `UK2Node_MultiCameraRigParametersBase`  
`class UK2Node_MultiCameraRigParametersBase : public UK2Node_CameraRigBase`  
_L15-44_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UK2Node_CameraRigBase`
- desc: A base class for a Blueprint node that gets or sets multiple camera rig parameters.
- L21 _public prototype_ `UK2Node_MultiCameraRigParametersBase(const FObjectInitializer& ObjectInit);`
- L23 _public prototype_ `void Initialize(const FAssetData& UnloadedCameraRig, bool bIsTemplateNode);`
- L28 _public prototype_ `virtual void ReallocatePinsDuringReconstruction(TArray<UEdGraphPin*>& OldPins) override;` — UK2Node interface.
- L32 _protected prototype_ `void EnsureCameraRigAssetLoaded();`
- L33 _protected prototype_ `void CreateParameterPins(EEdGraphPinDirection PinDirection);`
- L34 _protected prototype_ `void FindBlendableParameterPins(TArray<UEdGraphPin*>& OutPins) const;`
- L35 _protected prototype_ `void FindDataParameterPins(TArray<UEdGraphPin*>& OutPins) const;`
- L40 _protected member_ `TArray<FName> BlendableParameterPinNames;` — `UPROPERTY()`
- L43 _protected member_ `TArray<FName> DataParameterPinNames;` — `UPROPERTY()`

### `Plugins/Cameras/GameplayCameras/Source/GameplayCamerasUncookedOnly/Private/BlueprintGraph/K2Node_SetCameraRigParameter.h` (Private)


#### class `UK2Node_SetCameraRigParameter`  
`class UK2Node_SetCameraRigParameter : public UK2Node_SingleCameraRigParameterBase`  
_L17-33_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UK2Node_SingleCameraRigParameterBase`
- desc: Blueprint node that, given a camera rig, lets the user set the value of one single exposed parameter.
- L24 _public prototype_ `virtual void AllocateDefaultPins() override;` — UEdGraphNode interface.
- L25 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L26 _public prototype_ `virtual FText GetTooltipText() const override;`
- L27 _public prototype_ `virtual void ExpandNode(FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph) override;`
- L32 _protected prototype_ `void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar, const FAssetData& CameraRigAssetData) const;` — UK2Node_CameraRigBase interface.

### `Plugins/Cameras/GameplayCameras/Source/GameplayCamerasUncookedOnly/Private/BlueprintGraph/K2Node_SetCameraRigParameters.h` (Private)


#### class `UK2Node_SetCameraRigParameters`  
`class UK2Node_SetCameraRigParameters : public UK2Node_MultiCameraRigParametersBase`  
_L17-36_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UK2Node_MultiCameraRigParametersBase`
- desc: Blueprint node that, given a camera rig, lets the user set the values of all exposed parameters on that camera rig. Any camera rig running with the specific evaluation data will use those values.
- L24 _public prototype_ `virtual void AllocateDefaultPins() override;` — UEdGraphNode interface.
- L25 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L26 _public prototype_ `virtual FText GetTooltipText() const override;`
- L27 _public prototype_ `virtual void ExpandNode(class FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph) override;`
- L30 _public prototype_ `virtual void ReallocatePinsDuringReconstruction(TArray<UEdGraphPin*>& OldPins) override;` — UK2Node interface.
- L35 _protected prototype_ `virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar, const FAssetData& CameraRigAssetData) const override;` — UK2Node_CameraRigBase interface.

### `Plugins/Cameras/GameplayCameras/Source/GameplayCamerasUncookedOnly/Private/BlueprintGraph/K2Node_SingleCameraRigParameterBase.h` (Private)


#### enum `EK2Node_CameraParameterType`  
`enum class EK2Node_CameraParameterType : uint8`  
_L13-18_
- reflection: `UENUM()`
- L15 _public enumerator_ `Unknown`
- L16 _public enumerator_ `Blendable`
- L17 _public enumerator_ `Data`

#### class `UK2Node_SingleCameraRigParameterBase`  
`class UK2Node_SingleCameraRigParameterBase : public UK2Node_CameraRigBase`  
_L24-67_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UK2Node_CameraRigBase`
- desc: A base class for a Blueprint node that gets or sets a single camera rig parameter.
- L30 _public prototype_ `UK2Node_SingleCameraRigParameterBase(const FObjectInitializer& ObjectInit);`
- L32 _public prototype_ `void Initialize(const FAssetData& UnloadedCameraRig, const FString& InCameraParameterName, bool bIsTemplateNode);`
- L33 _public prototype_ `void Initialize(UCameraRigAsset* InCameraRig, const FString& InCameraParameterName, ECameraVariableType InCameraVariableType, const UScriptStruct* InBlendableStructType);`
- L34 _public prototype_ `void Initialize(UCameraRigAsset* InCameraRig, const FString& InCameraParameterName, ECameraContextDataType InCameraContextDataType, ECameraContextDataContainerType InCameraContextDataContainerType, const UObject* InCameraContextDataTypeObject);`
- L39 _public prototype_ `virtual FSlateIcon GetIconAndTint(FLinearColor& OutColor) const override;` — UEdGraphNode interface.
- L43 _protected prototype_ `FEdGraphPinType GetParameterPinType() const;`
- L48 _protected member_ `FString CameraParameterName;` — `UPROPERTY()`
- L51 _protected member_ `EK2Node_CameraParameterType CameraParameterType = EK2Node_CameraParameterType::Unknown;` — `UPROPERTY()`
- L54 _protected member_ `ECameraVariableType BlendableCameraParameterType;` — `UPROPERTY()`
- L57 _protected member_ `TObjectPtr<const UScriptStruct> BlendableStructType;` — `UPROPERTY()`
- L60 _protected member_ `ECameraContextDataType DataCameraParameterType;` — `UPROPERTY()`
- L63 _protected member_ `ECameraContextDataContainerType DataCameraParameterContainerType;` — `UPROPERTY()`
- L66 _protected member_ `TObjectPtr<UObject> DataCameraParameterTypeObject;` — `UPROPERTY()`

### `Plugins/Cameras/GameplayCameras/Source/GameplayCamerasUncookedOnly/Public/Helpers/CameraContextDataPinTypeHelper.h` (Public)


#### class `UE::Cameras::FCameraContextDataPinTypeHelper`  
`class FCameraContextDataPinTypeHelper`  
_L13-18_
- L17 _public prototype_ `static FEdGraphPinType GetPinType(ECameraContextDataType DataType, ECameraContextDataContainerType DataContainerType, const UObject* DataTypeObject);`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API GAMEPLAYCAMERASUNCOOKEDONLY_API`
- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Cameras` (scope `UE`)

### `Plugins/Cameras/GameplayCameras/Source/GameplayCamerasUncookedOnly/Public/Helpers/CameraVariablePinTypeHelper.h` (Public)


#### class `UE::Cameras::FCameraVariablePinTypeHelper`  
`class FCameraVariablePinTypeHelper`  
_L13-18_
- L17 _public prototype_ `static FEdGraphPinType GetPinType(ECameraVariableType VariableType, const UScriptStruct* BlendableStructType);`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API GAMEPLAYCAMERASUNCOOKEDONLY_API`
- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Cameras` (scope `UE`)
