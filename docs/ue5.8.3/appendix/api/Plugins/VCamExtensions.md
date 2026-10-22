# Plugins / VCamExtensions

- module root: `Plugins/VirtualProduction/VirtualCamera/Source/VCamExtensions`
- headers: 14; symbols: 91
- symbol kinds: class=12, delegate=1, enum=2, enumerator=4, function=1, member=20, namespace=3, prototype=43, struct=5
- PrivateDependencyModuleNames: CoreUObject, DecoupledOutputProvider, Engine, InputCore, Projects, Slate, SlateCore
- PublicDependencyModuleNames: CinematicCamera, Core, VCamCore

### `Plugins/VirtualProduction/VirtualCamera/Source/VCamExtensions/Private/Hierarchies/HierarchyUtils.h` (Private)


#### enum `UE::VCamExtensions::HierarchyUtils::EBreakBehavior`  
`enum class EBreakBehavior`  
_L10-14_
- L12 _public enumerator_ `Continue`
- L13 _public enumerator_ `Break`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace VCamExtensions` (scope `UE`)
- L8 _namespace_ `namespace HierarchyUtils` (scope `UE::VCamExtensions`)
- L24 _function_ `template<typename TNodeType, typename TProcessRelationShipFunc, typename TGetChildrenFunc> void ForEachGroup(TNodeType& RootNode, TProcessRelationShipFunc ProcessRelationShipCallback, TGetChildrenFunc GetChildrenFunc)` (scope `UE::VCamExtensions::HierarchyUtils`) — Utility function for iterating a tree like structure. ProcessRelationShipFunc = EBreakBehavior(TNodeType& CurrentGroup, TNodeType* Parent) GetChildrenFunc = TArray<TNodeType*>(TNodeType& CurrentGroup)

### `Plugins/VirtualProduction/VirtualCamera/Source/VCamExtensions/Private/VCamExtensionsLog.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogVCamExtensions, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogVCamExtensions, Log, All);`

### `Plugins/VirtualProduction/VirtualCamera/Source/VCamExtensions/Public/Hierarchies/BaseModifierGroup.h` (Public)


#### class `UBaseModifierGroup`  
`class UBaseModifierGroup : public UObject`  
_L10-21_
- reflection: `UCLASS(Abstract)`
- inherits: `UObject`
- desc: Implements base logic to keep group names unique within a hierachy
- L16 _public member_ `FName NodeName;` — `UPROPERTY(EditAnywhere, Category = "Hierarchy")`
- L19 _public prototype_ `virtual void PostInitProperties() override;`

### `Plugins/VirtualProduction/VirtualCamera/Source/VCamExtensions/Public/Hierarchies/ModifierHierarchyAsset.h` (Public)


#### class `UModifierHierarchyAsset`  
`class UModifierHierarchyAsset : public UObject`  
_L26-60_
- reflection: `UCLASS(BlueprintType)`
- inherits: `UObject`
- desc: An asset intended to be referenced by Slate widgets. Defines a tree hierarchy. Nodes are called groups. A group consists of modifiers and (sub) groups. An example use case is if you want to have a button menu which should procedurally generate sub-button menus depending on the modifiers in the component. One group could be a Lens group which groups together modifiers that e.g. modify focal distance, filmback, and FOV. The rules are defined generically enough so as modifiers are added or removed, the groupings also update accordingly.
- L32 _public member_ `TObjectPtr<UModifierHierarchyRules> Rules;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Instanced, Category = "Virtual Camera")`
- L36 _public prototype_ `FName GetRootNode() const;` — `UFUNCTION(BlueprintPure, Category = "Virtual Camera|Hierarchies")` — Gets the root of the tree.
- L40 _public prototype_ `bool GetParentNode(FName ChildNode, FName& ParentNode) const;` — `UFUNCTION(BlueprintPure, Category = "Virtual Camera|Hierarchies")` — Gets the parent of this given group. Fails if called on the root node.
- L44 _public prototype_ `TSet<FName> GetChildNodes(FName ParentGroup) const;` — `UFUNCTION(BlueprintPure, Category = "Virtual Camera|Hierarchies")` — Gets the child groups of the given group.
- L48 _public prototype_ `UVCamModifier* GetModifierInNode(UVCamComponent* Component, FName GroupName) const;` — `UFUNCTION(BlueprintPure, Category = "Virtual Camera|Hierarchies")` — Gets all the modifiers on the component that belong in the given group.
- L55 _public prototype_ `bool GetConnectionPointTargetForNode(FName GroupName, UVCamComponent* Component, FVCamModifierConnectionBinding& Connection) const;` — `UFUNCTION(BlueprintPure, Category = "Virtual Camera|Hierarchies")` — Gets the connection point the modifier is configured to be bound to. This function is optional to implement; it is valid for it to always return false.
- L59 _public prototype_ `TSet<FName> GetGroupsContainingModifier(UVCamModifier* Modifier) const;` — `UFUNCTION(BlueprintPure, Category = "Virtual Camera|Hierarchies")` — Utility function to get all groups which contain this modifier.

### `Plugins/VirtualProduction/VirtualCamera/Source/VCamExtensions/Public/Hierarchies/ModifierHierarchyRules.h` (Public)


#### struct `FVCamModifierConnectionBinding`  
`struct FVCamModifierConnectionBinding`  
_L13-22_
- reflection: `USTRUCT(BlueprintType)`
- L18 _public member_ `TObjectPtr<UVCamModifier> Modifier;` — `UPROPERTY(BlueprintReadWrite, Category = "Virtual Camera")`
- L21 _public member_ `FName ConnectionPoint;` — `UPROPERTY(BlueprintReadWrite, Category = "Virtual Camera")`

#### class `UModifierHierarchyRules`  
`class UModifierHierarchyRules : public UObject`  
_L34-66_
- reflection: `UCLASS(Abstract, Blueprintable, EditInlineNew)`
- inherits: `UObject`
- desc: Defines a tree hierarchy. Each node is called a group. A group consists of connections and (sub) groups. A connection is a modifier and a corresponding connection point. An example use case is if you want to have a button menu which should procedurally generate sub-button menus depending on the modifiers in the component. One group could be a Lens group which groups together modifiers that e.g. modify focal distance, filmback, and FOV. The rules are defined generically enough so as modifiers are added or removed, the groupings also update accordingly.
- L41 _public prototype_ `FName GetRootNode() const;` — `UFUNCTION(BlueprintPure, BlueprintNativeEvent, Category = "Virtual Camera|Hierarchies")` — Gets the root of the tree.
- L45 _public prototype_ `bool GetParentNode(FName ChildNode, FName& ParentNode) const;` — `UFUNCTION(BlueprintPure, BlueprintNativeEvent, Category = "Virtual Camera|Hierarchies")` — Gets the parent of this given group. Fails if called on the root node.
- L49 _public prototype_ `TSet<FName> GetChildNodes(FName Node) const;` — `UFUNCTION(BlueprintPure, BlueprintNativeEvent, Category = "Virtual Camera|Hierarchies")` — Gets the child groups of the given group.
- L53 _public prototype_ `UVCamModifier* GetModifierInNode(UVCamComponent* Component, FName NodeName) const;` — `UFUNCTION(BlueprintPure, BlueprintNativeEvent, Category = "Virtual Camera|Hierarchies")` — Gets all the modifiers on the component that belong in the given group.
- L61 _public prototype_ `bool GetConnectionPointTargetForNode(FName GroupName, UVCamComponent* Component, FVCamModifierConnectionBinding& Connection) const;` — `UFUNCTION(BlueprintPure, BlueprintNativeEvent, Category = "Virtual Camera|Hierarchies")` — Gets the connection point the modifier is configured to be bound to, if any. This function is optional to implement; it is valid for it to always return false. @return Whether there is a connection point configured for this hierarchy node.
- L65 _public prototype_ `TSet<FName> GetNodesContainingModifier(UVCamModifier* Modifier) const;` — `UFUNCTION(BlueprintPure, BlueprintNativeEvent, Category = "Virtual Camera|Hierarchies")` — Utility function to get all groups which contain this modifier.

### `Plugins/VirtualProduction/VirtualCamera/Source/VCamExtensions/Public/Hierarchies/TargetModifierPerNodeHierarchyRules.h` (Public)


#### class `USingleModifierPerNodeWithTargetSettings`  
`class USingleModifierPerNodeWithTargetSettings : public UBaseModifierGroup`  
_L12-22_
- reflection: `UCLASS(EditInlineNew)`
- inherits: `UBaseModifierGroup`
- L18 _public member_ `FVCamConnectionTargetSettings TargetSettings;` — `UPROPERTY(EditAnywhere, Category = "Hierarchy")`
- L21 _public member_ `TArray<TObjectPtr<USingleModifierPerNodeWithTargetSettings>> ChildElements;` — `UPROPERTY(EditAnywhere, Instanced, Category = "Hierarchy")`

#### class `UTargetModifierPerNodeHierarchyRules`  
`class UTargetModifierPerNodeHierarchyRules : public UModifierHierarchyRules`  
_L28-58_
- reflection: `UCLASS()`
- inherits: `UModifierHierarchyRules`
- L33 _public prototype_ `UTargetModifierPerNodeHierarchyRules();`
- L36 _public prototype_ `virtual FName GetRootNode_Implementation() const override;`
- L37 _public prototype_ `virtual bool GetParentNode_Implementation(FName ChildGroup, FName& ParentGroup) const override;`
- L38 _public prototype_ `virtual TSet<FName> GetChildNodes_Implementation(FName ParentGroup) const override;`
- L39 _public prototype_ `virtual UVCamModifier* GetModifierInNode_Implementation(UVCamComponent* Component, FName GroupName) const override;`
- L40 _public prototype_ `virtual bool GetConnectionPointTargetForNode_Implementation(FName GroupName, UVCamComponent* Component, FVCamModifierConnectionBinding& Connection) const override;`
- L41 _public prototype_ `virtual TSet<FName> GetNodesContainingModifier_Implementation(UVCamModifier* Modifier) const override;`
- L47 _private member_ `TObjectPtr<USingleModifierPerNodeWithTargetSettings> Root;` — `UPROPERTY(EditAnywhere, Instanced, Category = "Hierarchy")`
- L49 _private prototype_ `TSet<USingleModifierPerNodeWithTargetSettings*> GetNodeForModifier(UVCamModifier* Modifier) const;`
- L50 _private prototype_ `USingleModifierPerNodeWithTargetSettings* FindNodeByName(FName GroupName) const;`
- L57 _private prototype_ `void ForEachGroup(TFunctionRef<EBreakBehavior(USingleModifierPerNodeWithTargetSettings& CurrentGroup, USingleModifierPerNodeWithTargetSettings* Parent)> Callback) const;`

#### enum `UTargetModifierPerNodeHierarchyRules::EBreakBehavior`  
`enum class EBreakBehavior`  
_L52-56_
- L54 _public enumerator_ `Continue`
- L55 _public enumerator_ `Break`

### `Plugins/VirtualProduction/VirtualCamera/Source/VCamExtensions/Public/Styling/ButtonWidgetStyleData.h` (Public)


#### class `UButtonWidgetStyleData`  
`class UButtonWidgetStyleData : public UWidgetStyleData`  
_L11-18_
- reflection: `UCLASS()`
- inherits: `UWidgetStyleData`
- desc: Associates a button style for widgets that want to display a button for a modifier / connection point.
- L17 _public member_ `FButtonStyle ButtonStyle;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Virtual Camera")`

### `Plugins/VirtualProduction/VirtualCamera/Source/VCamExtensions/Public/Styling/ClassBasedWidgetStyleDefinitions.h` (Public)


#### struct `FWidgetStyleDataConfig`  
`struct FWidgetStyleDataConfig`  
_L13-23_
- reflection: `USTRUCT()`
- L18 _public member_ `TArray<TObjectPtr<UWidgetStyleData>> ModifierMetaData;` — `UPROPERTY(EditAnywhere, Instanced, Category = "Virtual Camera")`
- L22 _public member_ `bool bInherit = false;` — `UPROPERTY(EditAnywhere, Category = "Virtual Camera", AdvancedDisplay)` — Whether to inherit the meta data of modifier's parent class(es).

#### struct `FPerModifierClassWidgetSytleData`  
`struct FPerModifierClassWidgetSytleData`  
_L26-37_
- reflection: `USTRUCT()`
- L32 _public member_ `FWidgetStyleDataConfig ModifierStyles;` — `UPROPERTY(EditAnywhere, Category = "Virtual Camera")` — Data to attach to modifiers matching the associated class.
- L36 _public member_ `TMap<FName, FWidgetStyleDataConfig> ConnectionPointStyles;` — `UPROPERTY(EditAnywhere, Category = "Virtual Camera")` — Meta data that is attached to a custom name, such as a connection point or group name (if using e.g. UClassBasedModifierHierarchyRules)

#### class `UClassBasedWidgetStyleDefinitions`  
`class UClassBasedWidgetStyleDefinitions : public UModifierBoundWidgetStyleDefinitions`  
_L43-60_
- reflection: `UCLASS()`
- inherits: `UModifierBoundWidgetStyleDefinitions`
- desc: Assigns meta data based on modifier class. To every modifier class you can assign meta data.
- L49 _public member_ `TMap<TSubclassOf<UVCamModifier>, FPerModifierClassWidgetSytleData> Config;` — `UPROPERTY(EditAnywhere, Category = "Virtual Camera")`
- L53 _public member_ `TMap<FName, FWidgetStyleDataArray> CategoriesWithoutModifier;` — `UPROPERTY(EditAnywhere, Category = "Virtual Camera")` — Meta data that is not bound to any modifier but just to a simple name.
- L56 _public prototype_ `virtual TArray<UWidgetStyleData*> GetStylesForModifier_Implementation(UVCamModifier* Modifier) const override;`
- L57 _public prototype_ `virtual TArray<UWidgetStyleData*> GetStylesForConnectionPoint_Implementation(UVCamModifier* Modifier, FName ConnectionPointId) const override;`
- L58 _public prototype_ `virtual TArray<UWidgetStyleData*> GetStylesForName_Implementation(FName Category) const override;`

### `Plugins/VirtualProduction/VirtualCamera/Source/VCamExtensions/Public/Styling/ModifierBoundWidgetStyleDefinitions.h` (Public)


#### class `UModifierBoundWidgetStyleDefinitions`  
`class UModifierBoundWidgetStyleDefinitions : public UObject`  
_L19-44_
- reflection: `UCLASS(Abstract, Blueprintable, EditInlineNew)`
- inherits: `UObject`
- desc: Associates information with modifiers and their connection points. You can use it to retrieve custom information assigned to a modifier and / or its connections, such as what icon a button representing that widget should have.
- L26 _public prototype_ `TArray<UWidgetStyleData*> GetStylesForModifier(UVCamModifier* Modifier) const;` — `UFUNCTION(BlueprintPure, BlueprintNativeEvent, Category = "Virtual Camera")` — Retrieves all meta data that is associated for a given modifier.
- L30 _public prototype_ `TArray<UWidgetStyleData*> GetStylesForConnectionPoint(UVCamModifier* Modifier, FName ConnectionPoint) const;` — `UFUNCTION(BlueprintPure, BlueprintNativeEvent, Category = "Virtual Camera")` — Retrieves all meta data that is associated for a given modifier and a sub-category name.
- L34 _public prototype_ `TArray<UWidgetStyleData*> GetStylesForName(FName Category) const;` — `UFUNCTION(BlueprintPure, BlueprintNativeEvent, Category = "Virtual Camera")` — Retrieves all meta data that is associated with a given a category name; this data is not associated with any kind of modifier.
- L37 _public prototype_ `UWidgetStyleData* GetStyleForModifierByClass(UVCamModifier* Modifier, TSubclassOf<UWidgetStyleData> Class) const;` — `UFUNCTION(BlueprintPure, Category = "Virtual Camera", meta = (DeterminesOutputType = "Class"))`
- L40 _public prototype_ `UWidgetStyleData* GetStyleForConnectionPointByClass(UVCamModifier* Modifier, FName ConnectionPoint, TSubclassOf<UWidgetStyleData> Class) const;` — `UFUNCTION(BlueprintPure, Category = "Virtual Camera", meta = (DeterminesOutputType = "Class"))`
- L43 _public prototype_ `UWidgetStyleData* GetStyleForNameByClass(FName Category, TSubclassOf<UWidgetStyleData> Class) const;` — `UFUNCTION(BlueprintPure, Category = "Virtual Camera", meta = (DeterminesOutputType = "Class"))`

### `Plugins/VirtualProduction/VirtualCamera/Source/VCamExtensions/Public/Styling/ModifierBoundWidgetStylesAsset.h` (Public)


#### class `UModifierBoundWidgetStylesAsset`  
`class UModifierBoundWidgetStylesAsset : public UObject`  
_L16-44_
- reflection: `UCLASS(BlueprintType)`
- inherits: `UObject`
- desc: An asset intended to be referenced by Slate widgets. For example, you can retrieve custom style info assigned to a modifier and / or its connections, such as what icon a button representing that widget should have.
- L22 _public member_ `TObjectPtr<UModifierBoundWidgetStyleDefinitions> Rules;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Instanced, Category = "Virtual Camera")`
- L26 _public prototype_ `TArray<UWidgetStyleData*> GetStylesForModifier(UVCamModifier* Modifier) const;` — `UFUNCTION(BlueprintPure, Category = "Virtual Camera")` — Retrieves all meta data that is associated for a given modifier.
- L30 _public prototype_ `TArray<UWidgetStyleData*> GetStylesForConnectionPoint(UVCamModifier* Modifier, FName ConnectionPoint) const;` — `UFUNCTION(BlueprintPure, Category = "Virtual Camera")` — Retrieves all meta data that is associated for a given modifier and a sub-category name.
- L34 _public prototype_ `TArray<UWidgetStyleData*> GetStylesForName(FName Category) const;` — `UFUNCTION(BlueprintPure, Category = "Virtual Camera")` — Retrieves all meta data that is associated with a given a category name; this data is not associated with any kind of modifier.
- L37 _public prototype_ `UWidgetStyleData* GetStyleForModifierByClass(UVCamModifier* Modifier, TSubclassOf<UWidgetStyleData> Class) const;` — `UFUNCTION(BlueprintPure, Category = "Virtual Camera", meta = (DeterminesOutputType = "Class"))`
- L40 _public prototype_ `UWidgetStyleData* GetStyleForConnectionPointByClass(UVCamModifier* Modifier, FName ConnectionPoint, TSubclassOf<UWidgetStyleData> Class) const;` — `UFUNCTION(BlueprintPure, Category = "Virtual Camera", meta = (DeterminesOutputType = "Class"))`
- L43 _public prototype_ `UWidgetStyleData* GetStyleForNameByClass(FName Name, TSubclassOf<UWidgetStyleData> Class) const;` — `UFUNCTION(BlueprintPure, Category = "Virtual Camera", meta = (DeterminesOutputType = "Class"))`

### `Plugins/VirtualProduction/VirtualCamera/Source/VCamExtensions/Public/Styling/TargetBasedWidgetStyleDefinitions.h` (Public)


#### struct `FTargettedModifierStyleConfig`  
`struct FTargettedModifierStyleConfig`  
_L10-20_
- reflection: `USTRUCT()`
- L15 _public member_ `FWidgetStyleDataArray ModifierStyles;` — `UPROPERTY(EditAnywhere, Category = "Virtual Camera")`
- L19 _public member_ `TMap<FName, FWidgetStyleDataArray> ConnectionPointStyles;` — `UPROPERTY(EditAnywhere, Category = "Virtual Camera")` — Key: Name of a connection point on the modifier

#### class `UTargetBasedWidgetStyleDefinitions`  
`class UTargetBasedWidgetStyleDefinitions : public UModifierBoundWidgetStyleDefinitions`  
_L23-41_
- reflection: `UCLASS()`
- inherits: `UModifierBoundWidgetStyleDefinitions`
- L30 _public member_ `TMap<FName, FTargettedModifierStyleConfig> ModifierToStyle;` — `UPROPERTY(EditAnywhere, Category = "Virtual Camera")` — Key: Name of a modifier in a VCam's stack entry.
- L34 _public member_ `TMap<FName, FWidgetStyleDataArray> CategoriesWithoutModifier;` — `UPROPERTY(EditAnywhere, Category = "Virtual Camera")` — Styles that is not bound to any modifier but just to a name.
- L37 _public prototype_ `virtual TArray<UWidgetStyleData*> GetStylesForModifier_Implementation(UVCamModifier* Modifier) const override;`
- L38 _public prototype_ `virtual TArray<UWidgetStyleData*> GetStylesForConnectionPoint_Implementation(UVCamModifier* Modifier, FName ConnectionPointId) const override;`
- L39 _public prototype_ `virtual TArray<UWidgetStyleData*> GetStylesForName_Implementation(FName Category) const override;`

### `Plugins/VirtualProduction/VirtualCamera/Source/VCamExtensions/Public/Styling/WidgetStyleData.h` (Public)


#### class `UWidgetStyleData`  
`class UWidgetStyleData : public UObject`  
_L10-13_
- reflection: `UCLASS(Abstract, Blueprintable, EditInlineNew)`
- inherits: `UObject`
- desc: Base class for data that can be associated with modifiers / their connection points.

### `Plugins/VirtualProduction/VirtualCamera/Source/VCamExtensions/Public/Styling/WidgetStyleDataArray.h` (Public)


#### struct `FWidgetStyleDataArray`  
`struct FWidgetStyleDataArray`  
_L10-16_
- reflection: `USTRUCT()`
- L15 _public member_ `TArray<TObjectPtr<UWidgetStyleData>> Styles;` — `UPROPERTY(EditAnywhere, Instanced, Category = "Virtual Camera")`

### `Plugins/VirtualProduction/VirtualCamera/Source/VCamExtensions/Public/VCamBaseActorWithPreset.h` (Public)


#### class `AVCamBaseActorWithPreset`  
`class AVCamBaseActorWithPreset : public AVCamBaseActor`  
_L15-23_
- reflection: `UCLASS(Abstract)`
- inherits: `AVCamBaseActor`
- desc: Base class for the VCamActor preset Blueprint. If the platform supports pixel streaming, this activates all pixel streaming and deactivates all remote session output providers. The child Blueprint is expected to contain 1 pixel streaming and 1 remote session output provider.
- L21 _public prototype_ `virtual void PostActorCreated() override;`
