# Plugins / RemoteControlLogic

- module root: `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlLogic`
- headers: 32; symbols: 415
- symbol kinds: class=25, delegate=2, enum=1, enumerator=7, function=38, member=72, namespace=13, prototype=230, struct=13, typedef=1, variable=13
- PrivateDependencyModuleNames: AssetRegistry, Cbor, Engine, HTTP, ImageCore, RHI, RemoteControl, RemoteControlCommon, RenderCore, Serialization, UnrealEd
- PublicDependencyModuleNames: Core, CoreUObject

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlLogic/Private/Action/Bind/RCCustomBindActionUtilitiesPrivate.h` (Private)


#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace RCCustomBindActionUtilities` (scope `UE`)
- L12 _prototype_ `UTexture* LoadTextureFromPath(UObject* InOuter, const FString& InPath);` (scope `UE::RCCustomBindActionUtilities`)
- L18 _prototype_ `bool SetTexturePropertyFromPath(const TSharedRef<FRemoteControlProperty>& InRemoteControlEntityAsProperty, UObject* InOuter, const FString& InPath);` (scope `UE::RCCustomBindActionUtilities`) — Loads the texture found at the specified path, and uses it to set a Texture value in the specified RC Property Useful e.g. for Custom External Texture Controller
- L20 _prototype_ `bool SetTextureProperty(const TSharedRef<FRemoteControlProperty>& InRemoteControlEntityAsProperty, UTexture* InTexture);` (scope `UE::RCCustomBindActionUtilities`)

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlLogic/Private/Action/Bind/RCExternalTexture.h` (Private)


#### struct `FRCExternalTextureInfo`  
`struct FRCExternalTextureInfo`  
_L10-29_
- reflection: `USTRUCT()`
- desc: Cached information on the external texture.
- L15 _public member_ `int32 SizeX = 1;` — `UPROPERTY()`
- L18 _public member_ `int32 SizeY = 1;` — `UPROPERTY()`
- L23 _public function_ `void Set(int32 InSizeX, int32 InSizeY, EPixelFormat InFormat)`

#### class `URCExternalTexture`  
`class URCExternalTexture : public UTexture2DDynamic`  
_L41-87_
- reflection: `UCLASS(hidecategories=Object)`
- inherits: `UTexture2DDynamic`
- desc: Texture object that automatically loads the content from an external file. The texture object itself does not store anything, except the filename. This is intended to be used with texture controllers in external mode. The texture is embedded in the RCP itself to have a valid texture object during loading. This avoids breaking the materials that require valid texture objects.
- L51 _public member_ `FString Path;` — `UPROPERTY()` — Path to the external texture file.
- L58 _public member_ `FRCExternalTextureInfo CachedInfo;` — `UPROPERTY()` — Cached information from the last time the texture was loaded. This is only used as backed up the texture file is not accessible.
- L61 _public prototype_ `virtual void PostLoad() override;`
- L65 _public prototype_ `virtual FTextureResource* CreateResource() override;`
- L72 _public prototype_ `void LoadFromPath(const FString& InPath);` — @brief Load the content of the texture from the given path. @param InPath Path of the texture file.
- L79 _public prototype_ `static URCExternalTexture* Create(const FTexture2DDynamicCreateInfo& InCreateInfo = FTexture2DDynamicCreateInfo());` — @brief Utility function to create an empty, uninitialized external texture. Need to call Init() or LoadFromPath() after this. @param InCreateInfo creation parameters @return created texture
- L86 _public prototype_ `static URCExternalTexture* Create(const FString& InPath, const FTexture2DDynamicCreateInfo& InCreateInfo = FTexture2DDynamicCreateInfo());` — @brief Utility function to create and initialize the texture from the given file path. @param InCreateInfo creation parameters @return created and initialized texture

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlLogic/Private/Signature/RCSignatureControllerAction.h` (Private)


#### struct `FRCSignatureControllerAction`  
`struct FRCSignatureControllerAction : public FRCSignatureAction`  
_L14-77_
- reflection: `USTRUCT(meta=(Hidden))`
- inherits: `FRCSignatureAction`
- L19 _public prototype_ `virtual void Initialize(const FRCSignatureField& InField) override;`
- L20 _public prototype_ `virtual bool Execute(const FRCSignatureActionContext& InContext) const override;`
- L22 _public prototype_ `virtual FRCSignatureActionIcon GetIcon() const override;`
- L32 _public function_ `virtual bool IsControllerCompatible(const FRCSignatureActionContext& InContext, URCController* InController) const` — Determines whether a found Controller is compatible for re-use @param InContext context of the action (preset, exposed property, etc) @param InController the existing controller to check @return true if compatible
- L43 _public function_ `virtual bool MakeControllerDesc(const FRCSignatureActionContext& InContext, FPropertyBagPropertyDesc& OutDesc) const` — Retrieves the Property Desc to use for creating a new controller @param InContext context of the action (preset, exposed property, etc) @param OutDesc the property description to use for creating the controller @return true if the property desc was filled in
- L53 _public function_ `virtual void OnControllerCreated(const FRCSignatureActionContext& InContext, URCController* InController) const` — Called after a controller has been created @param InContext context of the action (preset, exposed property, etc) @param InController the controller created
- L63 _public function_ `virtual bool ExecuteControllerAction(const FRCSignatureActionContext& InContext, URCController* InController) const` — The main logic of the action @param InContext context of the action (preset, exposed property, etc) @param InController the controller to use for the action @return true if the action modified the controller or some other object; false if nothing happened
- L68 _public prototype_ `URCController* FindOrAddController(const FRCSignatureActionContext& InContext, bool* bOutControllerAdded = nullptr) const;`
- L70 _public prototype_ `URCAction* FindActionInBehavior(const FRCSignatureActionContext& InContext, const URCBehaviour& InBehavior) const;`
- L73 _public member_ `FName ControllerName;` — `UPROPERTY(EditAnywhere, Category = "Controller")`
- L76 _public member_ `bool bCreateControllerIfNotFound = true;` — `UPROPERTY(EditAnywhere, Category = "Controller")`

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlLogic/Private/Signature/RCSignatureControllerBindAction.h` (Private)


#### struct `FRCSignatureControllerBindAction`  
`struct FRCSignatureControllerBindAction : public FRCSignatureControllerAction`  
_L9-23_
- reflection: `USTRUCT(DisplayName="Controller Bind Action")`
- inherits: `FRCSignatureControllerAction`
- L14 _public prototype_ `virtual bool IsSupported(const FRCSignatureField& InField) const override;`
- L18 _public prototype_ `virtual bool IsControllerCompatible(const FRCSignatureActionContext& InContext, URCController* InController) const override;`
- L19 _public prototype_ `virtual bool MakeControllerDesc(const FRCSignatureActionContext& InContext, FPropertyBagPropertyDesc& OutDesc) const override;`
- L20 _public prototype_ `virtual void OnControllerCreated(const FRCSignatureActionContext& InContext, URCController* InController) const override;`
- L21 _public prototype_ `virtual bool ExecuteControllerAction(const FRCSignatureActionContext& InContext, URCController* InController) const override;`

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlLogic/Public/Action/Bind/RCCustomBindActionUtilities.h` (Public)


#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace RCCustomBindActionUtilities` (scope `UE`)
- L12 _prototype_ `UTexture2D* LoadTextureFromPath(const FString& InPath);` (scope `UE::RCCustomBindActionUtilities`)
- L18 _prototype_ `void SetTexturePropertyFromPath(const TSharedRef<FRemoteControlProperty>& InRemoteControlEntityAsProperty, const FString& InPath);` (scope `UE::RCCustomBindActionUtilities`) — Loads the texture found at the specified path, and uses it to set a Texture value in the specified RC Property Useful e.g. for Custom External Texture Controller

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlLogic/Public/Action/Bind/RCPropertyBindAction.h` (Public)


#### class `URCPropertyBindAction`  
`class URCPropertyBindAction : public URCPropertyAction`  
_L14-28_
- reflection: `UCLASS()`
- inherits: `URCPropertyAction`
- desc: Property Bind Action specifically for Bind Behaviour
- L19 _public prototype_ `URCPropertyBindAction() = default;`
- L22 _public prototype_ `virtual void Execute() const override;`
- L27 _public member_ `TObjectPtr<URCController> Controller;` — `UPROPERTY()` — The Controller that drives us

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlLogic/Public/Action/Path/RCSetAssetByPathActionNew.h` (Public)


#### class `URCSetAssetByPathActionNew`  
`class URCSetAssetByPathActionNew : public URCPropertyAction`  
_L17-49_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `URCPropertyAction`
- desc: Property Set Asset By Path Action (New) specifically for Set Asset By Path Behaviour (New)
- L23 _public prototype_ `virtual void Execute() const override;`
- L26 _public prototype_ `URCSetAssetByPathBehaviorNew* GetSetAssetByPathBehavior() const;`
- L29 _public prototype_ `bool IsInternal() const;` — Internal -> Asset. External -> File. External is only supported by textures.
- L33 _private prototype_ `FString GetPath() const;` — Gets the path to the asset.
- L36 _private prototype_ `bool UpdateInternal();` — Updates property with a existing asset.
- L39 _private prototype_ `bool UpdateExternal();` — Updates property with an imported, external texture.
- L42 _private prototype_ `bool SetInternalAsset(UObject* InSetterObject);` — Auxiliary Function which sets the given InSetterObject Asset onto the Exposed Property.
- L45 _private prototype_ `bool SetExternalAsset(const FString& InExternalPath);` — Given an External Path towards a external location, loads the asset associated and places it onto an object
- L48 _private prototype_ `bool SetTextureFromPath(TSharedPtr<FRemoteControlProperty> InRCPropertyToSet, const FString& InFileName);` — Auxiliary Function to apply a Texture onto a given Property

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlLogic/Public/Action/RCAction.h` (Public)


#### class `URCAction`  
`class URCAction : public UObject`  
_L15-53_
- reflection: `UCLASS()`
- inherits: `UObject`
- desc: Base class for remote control action
- L21 _public function_ `virtual void Execute() const` — Execute action
- L23 _public prototype_ `FName GetExposedFieldLabel() const;`
- L25 _public function_ `virtual void CopyTo(URCAction* Action)`
- L28 _public prototype_ `URCBehaviour* GetParentBehaviour() const;` — Returns the parent Behaviour associated with this Action
- L31 _public prototype_ `void NotifyActionValueChanged();` — Invoked when this Action item value change
- L37 _public prototype_ `virtual void UpdateEntityIds(const TMap<FGuid, FGuid>& InEntityIdMap);` — @brief Called internally when entity Ids are renewed. @param InEntityIdMap Map of old Id to new Id.
- L39 _public prototype_ `virtual void UpdateEntityUsage(const URCBehaviour* InBehavior, TMap<FGuid, TSet<UObject*>>& InEntityToBehavior) const;`
- L44 _public member_ `FGuid ExposedFieldId;` — `UPROPERTY()` — Exposed Property or Function field Id
- L48 _public member_ `FGuid Id;` — `UPROPERTY()` — Action Id
- L52 _public member_ `TWeakObjectPtr<URemoteControlPreset> PresetWeakPtr;` — `UPROPERTY()` — Reference to preset

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlLogic/Public/Action/RCActionContainer.h` (Public)


#### class `URCActionContainer`  
`class URCActionContainer : public UObject`  
_L31-113_
- reflection: `UCLASS()`
- inherits: `UObject`
- desc: Container for created actions
- L37 _public prototype_ `void ExecuteActions();` — Execute container actions
- L39 _public prototype_ `TRCActionUniquenessTest GetDefaultActionUniquenessTest(const TSharedRef<const FRemoteControlField> InRemoteControlField);`
- L42 _public prototype_ `URCAction* AddAction();` — Add remote control identity action.
- L45 _public prototype_ `URCAction* AddAction(FName InFieldId);` — Add remote control identity action.
- L48 _public prototype_ `URCAction* AddAction(const TSharedRef<const FRemoteControlField> InRemoteControlField);` — Add remote control property action
- L51 _public prototype_ `URCAction* AddAction(TRCActionUniquenessTest InUniquenessTest, const TSharedRef<const FRemoteControlField> InRemoteControlField);` — Add remote control property action
- L54 _public prototype_ `URCAction* FindActionByFieldId(const FGuid InFieldId) const;` — Find Action by given exposed filed id
- L57 _public prototype_ `URCAction* FindActionByField(const TSharedRef<const FRemoteControlField> InRemoteControlField) const;` — Find Action by given remote control field
- L60 _public prototype_ `virtual int32 RemoveAction(const FGuid InExposedFieldId);` — Remove action by exposed field Id
- L63 _public prototype_ `virtual int32 RemoveAction(URCAction* InAction);` — Remove Action by given action UObject
- L66 _public prototype_ `void EmptyActions();` — Empty action set
- L69 _public prototype_ `void AddAction(URCAction* NewAction);` — Register a newly created Action with the Action container, provides Undo/Redo support.
- L72 _public function_ `const TSet<TObjectPtr<URCAction>>& GetActions() const` — Retrieves the actions present in this container
- L75 _public prototype_ `TArray<const URCPropertyAction*> GetPropertyActions() const;` — Retrieves all the Property Actions present in this container
- L80 _public prototype_ `virtual void PostEditUndo() override;` — Called after applying a transaction to the object. Used to broadcast Undo related container changes to UI
- L86 _public member_ `TSet<TObjectPtr<URCActionContainer>> ActionContainers;` — `UPROPERTY()` — Set of child action container
- L90 _public member_ `TWeakObjectPtr<URemoteControlPreset> PresetWeakPtr;` — `UPROPERTY()` — Reference to Preset
- L93 _public member_ `FOnActionsListModified OnActionsListModified;` — Delegate that notifies changes to the list of actions to a single listener
- L96 _public prototype_ `URCBehaviour* GetParentBehaviour();` — Derive the parent Behaviour holding this Action Container
- L99 _public prototype_ `void ForEachAction(TFunctionRef<void(URCAction*)> InActionFunction, bool bInRecursive);` — Call the given function on all actions of the container.
- L101 _public prototype_ `void UpdateEntityUsage(const URCBehaviour* InBehavior, TMap<FGuid, TSet<UObject*>>& InEntityToBehavior) const;`
- L105 _private prototype_ `URCPropertyAction* AddPropertyAction(const TSharedRef<const FRemoteControlProperty> InRemoteControlProperty);` — Add remote control property action
- L108 _private prototype_ `URCFunctionAction* AddFunctionAction(const TSharedRef<const FRemoteControlFunction> InRemoteControlFunction);` — Add remote control property function
- L112 _private member_ `TSet<TObjectPtr<URCAction>> Actions;` — `UPROPERTY()` — The list of Actions present in this container

#### Free symbols / members of external scopes

- L23 _typedef_ `typedef TFunction<bool(const TSet<TObjectPtr<URCAction>>& Actions)> TRCActionUniquenessTest;`
- L25 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnActionsListModified);`
- L25 _prototype_ `DECLARE_MULTICAST_DELEGATE(FOnActionsListModified);`

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlLogic/Public/Action/RCFunctionAction.h` (Public)


#### class `URCFunctionAction`  
`class URCFunctionAction : public URCAction`  
_L12-20_
- reflection: `UCLASS()`
- inherits: `URCAction`
- desc: Function Action which is executes bound exposed function
- L18 _public prototype_ `virtual void Execute() const override;`

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlLogic/Public/Action/RCPropertyAction.h` (Public)


#### class `URCPropertyAction`  
`class URCPropertyAction : public URCAction`  
_L16-40_
- reflection: `UCLASS()`
- inherits: `URCAction`
- desc: Property Action which is set property value from the action to exposed property
- L21 _public prototype_ `URCPropertyAction();`
- L24 _public prototype_ `virtual void Execute() const override;`
- L25 _public prototype_ `virtual void UpdateEntityIds(const TMap<FGuid, FGuid>& InEntityIdMap) override;`
- L29 _public prototype_ `FProperty* GetProperty() const;` — Returns the FProperty underlying this Action
- L32 _public prototype_ `void UpdateValueBasedOnRCProperty() const;` — Update the value of this Action with the current value of the RC property it is bound to
- L37 _public member_ `TObjectPtr<URCVirtualPropertySelfContainer> PropertySelfContainer = nullptr;` — `UPROPERTY()` — Virtual Property Container
- L39 _public prototype_ `TSharedPtr<FRemoteControlProperty> GetRemoteControlProperty() const;`

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlLogic/Public/Action/RCPropertyIdAction.h` (Public)


#### struct `FPropertyIdContainerKey`  
`struct FPropertyIdContainerKey`  
_L15-50_
- reflection: `USTRUCT()`
- desc: Key for the PropertyContainer of the PropertyId Action
- L19 _public function_ `FPropertyIdContainerKey()`
- L21 _public function_ `FPropertyIdContainerKey(FName InPropertyId, FName InContainerName) : PropertyId(InPropertyId) , ContainerName(InContainerName)`
- L28 _public member_ `FName PropertyId;` — `UPROPERTY()` — PropertyId
- L32 _public member_ `FName ContainerName;` — `UPROPERTY()` — Name of the container
- L41 _public function_ `bool operator==(const FPropertyIdContainerKey& InOtherKey) const` — Comparison operator, used by hashing containers.
- L46 _public function_ `bool operator<(const FPropertyIdContainerKey& InOtherKey) const`

#### class `URCPropertyIdAction`  
`class URCPropertyIdAction : public URCAction`  
_L56-99_
- reflection: `UCLASS()`
- inherits: `URCAction`
- desc: Action for PropertyId
- L63 _public prototype_ `virtual void Execute() const override;`
- L64 _public prototype_ `virtual void UpdateEntityIds(const TMap<FGuid, FGuid>& InEntityIdMap) override;`
- L68 _public prototype_ `virtual void PostLoad() override;`
- L70 _public prototype_ `virtual void PostEditChangeChainProperty(struct FPropertyChangedChainEvent& PropertyChangedEvent) override;`
- L74 _public prototype_ `void UpdatePropertyId();`
- L76 _public prototype_ `void Initialize();`
- L78 _public prototype_ `void OnEntityUnexposed(URemoteControlPreset* InPreset, const FGuid& InGuid);`
- L83 _public member_ `FName PropertyId = NAME_None;` — `UPROPERTY()` — Holds the field identifier associated with this.
- L87 _public member_ `TMap<FPropertyIdContainerKey, TObjectPtr<URCVirtualPropertySelfContainer>> PropertySelfContainer;` — `UPROPERTY()` — Virtual Property Container
- L91 _public member_ `TMap<FPropertyIdContainerKey, TObjectPtr<URCVirtualPropertySelfContainer>> CachedPropertySelfContainer;` — `UPROPERTY()` — Cached Virtual Property Container
- L95 _public member_ `TMap<FGuid, TObjectPtr<URCVirtualPropertySelfContainer>> RealPropertySelfContainer;` — `UPROPERTY()` — Contains the real property container
- L98 _private member_ `static TSet<FName> AllowedStructNameToCopy;`

#### Free symbols / members of external scopes

- L35 _function_ `friend uint32 GetTypeHash(const FPropertyIdContainerKey& InKey)` — Return hash value for this object, used when using this object as a key inside hashing containers.

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlLogic/Public/Behaviour/Builtin/Bind/RCBehaviourBind.h` (Public)


#### class `URCBehaviourBind`  
`class URCBehaviourBind : public URCBehaviour`  
_L22-65_
- reflection: `UCLASS()`
- inherits: `URCBehaviour`
- desc: [Bind Behaviour] Binds a given Controller with multiple exposed properties. Any changes to the value of the controller are directly propagated to the linked properties by Bind Behaviour.
- L27 _public prototype_ `URCBehaviourBind();`
- L30 _public prototype_ `virtual void Initialize() override;`
- L33 _public prototype_ `virtual URCAction* AddAction(const TSharedRef<const FRemoteControlField> InRemoteControlField) override;` — Add a Logic action using a remote control field as input
- L36 _public prototype_ `virtual bool CanHaveActionForField(const TSharedPtr<FRemoteControlField> InRemoteControlField) const override;` — Whether we can create an action pertaining to a given remote control field for the current behaviour
- L39 _public function_ `virtual bool SupportPropertyId() const override` — Whether the behaviour support property id
- L43 _public prototype_ `static bool CanHaveActionForField(URCController* InController, TSharedRef<const FRemoteControlField> InRemoteControlField, const bool bInAllowNumericInputAsStrings);` — Contains behaviour-independent validation logic for determining whether a Remote Controller property can be bound to a given Controller
- L47 _public prototype_ `static bool CopyPropertyValueToController(URCController* InController, TSharedRef<const FRemoteControlProperty> InRemoteControlProperty);` — Transfers the value of a given Remote Control Property to a Controller. Used for Auto Bind workflow where matching Controller types for bind are automatically created from a given Remote Control Property
- L50 _public prototype_ `URCPropertyBindAction* AddPropertyBindAction(const TSharedRef<const FRemoteControlProperty> InRemoteControlProperty);` — Add an action specifically for Bind Behaviour
- L57 _public prototype_ `static bool GetPropertyBagTypeFromFieldProperty(const FProperty* InProperty, EPropertyBagPropertyType& OutPropertyBagType, UObject*& OutStructObject);` — GetPropertyBagTypeFromFieldProperty Given a Remote Control Exposed Property type this function determines the appropriate EPropertyBagType and struct object required (if any) In the Logic realm we use a single type like (eg: String / Int) to represent various related types (String/Name/Text, Int32, Int64, etc) For this reason explicit mapping conversion is required between a given FProperty type and the desired Controller (Property Bag) type
- L61 _public function_ `bool AreNumericInputsAllowedAsStrings() const` — Indicates whether we support binding of strings to numeric fields and vice versa. This flag determines the list of bindable properties the user sees in the "Add Action" menu
- L62 _public function_ `void SetAllowNumericInputAsStrings(bool Value)`
- L64 _private member_ `bool bAllowNumericInputAsStrings = false;`

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlLogic/Public/Behaviour/Builtin/Bind/RCBehaviourBindNode.h` (Public)


#### class `URCBehaviourBindNode`  
`class URCBehaviourBindNode : public URCBehaviourNode`  
_L12-32_
- reflection: `UCLASS()`
- inherits: `URCBehaviourNode`
- desc: Behaviour Node class for Bind Behaviour
- L18 _public prototype_ `URCBehaviourBindNode();`
- L22 _public prototype_ `bool Execute(URCBehaviour* InBehaviour) const override;` — `UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Remote Control Behaviour")`
- L25 _public prototype_ `bool IsSupported(URCBehaviour* InBehaviour) const override;` — `UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Remote Control Behaviour")`
- L28 _public prototype_ `void OnPassed(URCBehaviour* InBehaviour) const;` — `UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Remote Control Behaviour")`
- L30 _public prototype_ `UClass* GetBehaviourClass() const override;`

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlLogic/Public/Behaviour/Builtin/Conditional/RCBehaviourConditional.h` (Public)


#### enum `ERCBehaviourConditionType`  
`enum class ERCBehaviourConditionType : uint8`  
_L17-26_
- reflection: `UENUM()`
- desc: Condition Typess
- L19 _public enumerator_ `IsEqual`
- L20 _public enumerator_ `IsGreaterThan`
- L21 _public enumerator_ `IsLesserThan`
- L22 _public enumerator_ `IsGreaterThanOrEqualTo`
- L23 _public enumerator_ `IsLesserThanOrEqualTo`
- L24 _public enumerator_ `Else`
- L25 _public enumerator_ `None`

#### struct `FRCBehaviourCondition`  
`struct FRCBehaviourCondition`  
_L34-49_
- reflection: `USTRUCT()`
- desc: Struct representing a single Condition Serialization and GC support are automatically provided by standard container types, as all relevant fields have been marked as UPROPERTY()
- L38 _public function_ `FRCBehaviourCondition()`
- L39 _public function_ `FRCBehaviourCondition(const ERCBehaviourConditionType InConditionType, const TObjectPtr<URCVirtualPropertySelfContainer> InComparand) : ConditionType(InConditionType), Comparand(InComparand)`
- L44 _public member_ `ERCBehaviourConditionType ConditionType = ERCBehaviourConditionType::None;` — `UPROPERTY()` — The type of condition to be used for comparison
- L48 _public member_ `TObjectPtr<URCVirtualPropertySelfContainer> Comparand;` — `UPROPERTY()` — The value with which to compare

#### class `URCBehaviourConditional`  
`class URCBehaviourConditional : public URCBehaviour`  
_L58-107_
- reflection: `UCLASS()`
- inherits: `URCBehaviour`
- desc: [Conditional Behaviour] Supports unique conditions per action that allow powerful Logic & Rigging of multiple usecases including Tricode based multi-mapping (selector behaviour), simulation of Hide On Empty behaviours, etc.
- L63 _public prototype_ `URCBehaviourConditional();`
- L66 _public prototype_ `virtual void Initialize() override;`
- L69 _public prototype_ `virtual URCAction* DuplicateAction(URCAction* InAction, URCBehaviour* InBehaviour) override;` — Duplicates an Action belonging to us into a given target behaviour
- L72 _public prototype_ `virtual void NotifyActionValueChanged(URCAction* InChangedAction) override;` — Called when an action value changed
- L78 _public prototype_ `void OnActionAdded(URCAction* Action, const ERCBehaviourConditionType InConditionType, const TObjectPtr<URCVirtualPropertySelfContainer> InComparand);` — ~ OnActionAdded ~ Invoked after a new condition action has just been created. Used to link the newly created action with its condition data
- L81 _public prototype_ `URCAction* AddConditionalAction(const TSharedRef<const FRemoteControlField> InRemoteControlField, const ERCBehaviourConditionType InConditionType, const TObjectPtr<URCVirtualPropertySelfContainer> InComparand);` — Add a Logic action using a remote control field as input
- L84 _public prototype_ `virtual bool CanHaveActionForField(const TSharedPtr<FRemoteControlField> InRemoteControlField) const override;` — Whether we can create an action pertaining to a given remote control field for the current behaviour
- L87 _public function_ `virtual bool SupportPropertyId() const override` — Whether the behaviour support property id
- L90 _public prototype_ `FText GetConditionTypeAsText(ERCBehaviourConditionType ConditionType) const;` — User-friendly text representation of a condition enum. Used to display comparator info in the Actions table
- L95 _protected prototype_ `virtual void ExecuteInternal(const TSet<TObjectPtr<URCAction>>& InActionsToExecute) override;` — Execute all the action if not provided a valid Action otherwise will only execute the given action
- L102 _public member_ `TMap<TObjectPtr<URCAction>, FRCBehaviourCondition> Conditions;` — `UPROPERTY()` — Data storage for Actions and related Conditions; stored as a mapping of Action object and associated condition data Each Action is associated with a unique condition (for the Conditional Behaviour)
- L106 _public member_ `TObjectPtr<URCVirtualPropertySelfContainer> Comparand;` — `UPROPERTY()` — Virtual property used to build the Comparand - i.e. the property with which the Controller will be compared for a given condition

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlLogic/Public/Behaviour/Builtin/Conditional/RCBehaviourConditionalNode.h` (Public)


#### class `URCBehaviourConditionalNode`  
`class URCBehaviourConditionalNode : public URCBehaviourNode`  
_L12-32_
- reflection: `UCLASS()`
- inherits: `URCBehaviourNode`
- desc: Compares given property value with controller property value
- L18 _public prototype_ `URCBehaviourConditionalNode();`
- L22 _public prototype_ `bool Execute(URCBehaviour* InBehaviour) const override;` — `UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Remote Control Behaviour")`
- L25 _public prototype_ `bool IsSupported(URCBehaviour* InBehaviour) const override;` — `UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Remote Control Behaviour")`
- L28 _public prototype_ `void OnPassed(URCBehaviour* InBehaviour) const;` — `UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Remote Control Behaviour")`
- L30 _public prototype_ `UClass* GetBehaviourClass() const override;`

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlLogic/Public/Behaviour/Builtin/Path/RCBehaviorSetAssetByPathNodeNew.h` (Public)


#### class `URCBehaviorSetAssetByPathNodeNew`  
`class URCBehaviorSetAssetByPathNodeNew : public URCBehaviourNode`  
_L12-28_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `URCBehaviourNode`
- desc: Takes the string as a path and goes on to search for the Asset it is connected to, setting it on the list of bound entities.
- L17 _public prototype_ `URCBehaviorSetAssetByPathNodeNew();`
- L21 _public prototype_ `bool Execute(URCBehaviour* InBehavior) const override;` — `UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Remote Control Behaviour")`
- L24 _public prototype_ `bool IsSupported(URCBehaviour* InBehavior) const override;` — `UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Remote Control Behaviour")`
- L26 _public prototype_ `UClass* GetBehaviourClass() const override;`

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlLogic/Public/Behaviour/Builtin/Path/RCBehaviourSetAssetByPathNode.h` (Public)


#### class `URCBehaviourSetAssetByPathNode`  
`class URCBehaviourSetAssetByPathNode : public URCBehaviourNode`  
_L12-28_
- reflection: `UCLASS()`
- inherits: `URCBehaviourNode`
- desc: Takes the string as a path and goes on to search for the Asset it is connected to, setting it to a Target Exposed Property.
- L17 _public prototype_ `URCBehaviourSetAssetByPathNode();`
- L21 _public prototype_ `bool Execute(URCBehaviour* InBehaviour) const override;` — `UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Remote Control Behaviour")`
- L24 _public prototype_ `bool IsSupported(URCBehaviour* InBehaviour) const override;` — `UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Remote Control Behaviour")`
- L26 _public prototype_ `UClass* GetBehaviourClass() const override;`

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlLogic/Public/Behaviour/Builtin/Path/RCSetAssetByPathBehaviorNew.h` (Public)


#### struct `FRCAssetPathElementNew`  
`struct FRCAssetPathElementNew`  
_L30-49_
- reflection: `USTRUCT()`
- L34 _public function_ `FRCAssetPathElementNew() : bIsInput(false) , Path(TEXT(""))`
- L39 _public function_ `FRCAssetPathElementNew(bool bInIsInput, const FString& InPath) : bIsInput(bInIsInput) , Path(InPath)`
- L45 _public member_ `bool bIsInput;` — `UPROPERTY(EditAnywhere, Category="Path")`
- L48 _public member_ `FString Path;` — `UPROPERTY(EditAnywhere, Category="Path")`

#### struct `FRCSetAssetPathNew`  
`struct FRCSetAssetPathNew`  
_L53-71_
- reflection: `USTRUCT()`
- desc: Struct to help generate Widgets for the DetailsPanel of the Behaviour
- L57 _public function_ `FRCSetAssetPathNew()`
- L62 _public prototype_ `~FRCSetAssetPathNew() = default;`
- L63 _public prototype_ `FRCSetAssetPathNew(const FRCSetAssetPathNew&) = default;`
- L64 _public prototype_ `FRCSetAssetPathNew(FRCSetAssetPathNew&&) = default;`
- L65 _public prototype_ `FRCSetAssetPathNew& operator=(const FRCSetAssetPathNew&) = default;`
- L66 _public prototype_ `FRCSetAssetPathNew& operator=(FRCSetAssetPathNew&&) = default;`
- L70 _public member_ `TArray<FRCAssetPathElementNew> AssetPath;` — `UPROPERTY(EditAnywhere, Category="Path")` — An Array of Strings holding the Path of an Asset, seperated in several String. Will concatenated back together later.

#### struct `FRCSetAssetByPathBehaviorNewPathElement`  
`struct FRCSetAssetByPathBehaviorNewPathElement`  
_L73-79_
- L75 _public member_ `FString Path;`
- L76 _public member_ `URCVirtualPropertyBase* Controller = nullptr;`
- L77 _public member_ `FName ControllerName = NAME_None;`
- L78 _public member_ `bool bIsError = false;`

#### class `URCSetAssetByPathBehaviorNew`  
`class URCSetAssetByPathBehaviorNew : public URCBehaviour`  
_L85-125_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `URCBehaviour`
- desc: Custom behaviour for Set Asset By Path
- L92 _public prototype_ `virtual void Initialize() override;` — Add default entries to the path.
- L94 _public prototype_ `virtual URCAction* AddAction(const TSharedRef<const FRemoteControlField> InRemoteControlField) override;` — Add a Logic action using a remote control field as input
- L95 _public function_ `virtual bool SupportPropertyId() const override`
- L98 _public prototype_ `virtual bool CanHaveActionForField(const TSharedPtr<FRemoteControlField> InRemoteControlField) const override;`
- L103 _public prototype_ `FString GetCurrentPath() const;` — Returns the Path as the completed version, including Token Inputs.
- L109 _public prototype_ `TArray<FRCSetAssetByPathBehaviorNewPathElement> GetPathElements() const;` — Returns an array of path elements, indicating whether the element was sourced from a controller and the controller itself, if it is still valid.
- L112 _public prototype_ `void RefreshPathArray();` — Called whenever a change has occured in the Slate
- L115 _public prototype_ `URCSetAssetByPathActionNew* AddPropertyBindAction(const TSharedRef<const FRemoteControlProperty> InRemoteControlProperty);` — Add an action specifically for Set Asset By Path Behaviour
- L120 _public member_ `FRCSetAssetPathNew PathStruct;` — `UPROPERTY()` — Struct holding the Path Information to help load Assets.
- L124 _public member_ `bool bInternal = true;` — `UPROPERTY()` — Bool used to help tell if the path given is an internal or external one.

#### Free symbols / members of external scopes

- L20 _namespace_ `namespace UE`
- L20 _namespace_ `namespace RemoteControl` (scope `UE`)
- L20 _namespace_ `namespace Logic` (scope `UE::RemoteControl`)
- L22 _namespace_ `namespace SetAssetByPathNew` (scope `UE::RemoteControl::Logic`)
- L24 _variable_ `const FString ContentFolder = FString(TEXT("/Gam` (scope `UE::RemoteControl::Logic::SetAssetByPathNew`)
- L25 _variable_ `const FName SetAssetByPathBehaviour = FName(TEXT("Set` (scope `UE::RemoteControl::Logic::SetAssetByPathNew`)

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlLogic/Public/Behaviour/Builtin/Path/RCSetAssetByPathBehaviour.h` (Public)


#### struct `FPendingFileRequest`  
`struct FPendingFileRequest`  
_L26-46_
- desc: Info used to send request for a file
- L31 _public function_ `FPendingFileRequest(const FString& InFileName=FString(TEXT(""))) : FileName(InFileName)` — Constructor
- L39 _public function_ `inline bool operator==(const FPendingFileRequest& Other) const` — Equality op
- L45 _public member_ `FString FileName;` — File being operated on by the pending request

#### struct `FRCAssetPathElement`  
`struct FRCAssetPathElement`  
_L49-68_
- reflection: `USTRUCT()`
- L53 _public function_ `FRCAssetPathElement() : bIsInput(false) , Path(TEXT(""))`
- L58 _public function_ `FRCAssetPathElement(bool bInIsInput, const FString& InPath) : bIsInput(bInIsInput) , Path(InPath)`
- L64 _public member_ `bool bIsInput;` — `UPROPERTY(EditAnywhere, Category="Path")`
- L67 _public member_ `FString Path;` — `UPROPERTY(EditAnywhere, Category="Path")`

#### struct `FRCSetAssetPath`  
`struct FRCSetAssetPath`  
_L72-98_
- reflection: `USTRUCT()`
- desc: Struct to help generate Widgets for the DetailsPanel of the Behaviour
- L78 _public function_ `FRCSetAssetPath()` — `UE_DEPRECATED(5.4)`
- L83 _public prototype_ `~FRCSetAssetPath() = default;`
- L84 _public prototype_ `FRCSetAssetPath(const FRCSetAssetPath&) = default;`
- L85 _public prototype_ `FRCSetAssetPath(FRCSetAssetPath&&) = default;`
- L86 _public prototype_ `FRCSetAssetPath& operator=(const FRCSetAssetPath&) = default;`
- L87 _public prototype_ `FRCSetAssetPath& operator=(FRCSetAssetPath&&) = default;`
- L92 _public member_ `TArray<FRCAssetPathElement> AssetPath;` — `UPROPERTY(EditAnywhere, Category="Path")` — An Array of Strings holding the Path of an Asset, seperated in several String. Will concatenated back together later.
- L97 _public member_ `TArray<FString> PathArray_DEPRECATED;` — `UE_DEPRECATED(5.4, "This property is deprecated please use AssetPathArray instead")` — `UPROPERTY()` — An Array of Strings holding the Path of an Asset, seperated in several String. Will concatenated back together later.

#### class `URCSetAssetByPathBehaviour`  
`class URCSetAssetByPathBehaviour : public URCBehaviour`  
_L104-182_
- reflection: `UCLASS()`
- inherits: `URCBehaviour`
- desc: Custom behaviour for Set Asset By Path
- L108 _public prototype_ `URCSetAssetByPathBehaviour();`
- L111 _public prototype_ `virtual void Initialize() override;`
- L112 _public function_ `virtual bool SupportPropertyId() const override`
- L113 _public prototype_ `virtual void UpdateEntityIds(const TMap<FGuid, FGuid>& InEntityIdMap) override;`
- L116 _public prototype_ `virtual void PostLoad() override;`
- L119 _public prototype_ `bool SetAssetByPath(const FString& AssetPath, const FString& DefaultString);` — Given an Input Path, sets the Target Exposed Property to the Asset.
- L122 _public prototype_ `TArray<UClass*> GetSupportedClasses() const;` — List of Supported Assets SetAssetByPath Logic Behaviour can set and change.
- L125 _public prototype_ `FString GetCurrentPath();` — Returns the Path as the completed version, including Token Inputs.
- L128 _public prototype_ `void SetTargetEntity(const TSharedPtr<const FRemoteControlEntity>& InEntity);` — Sets the target entity upon which the asset will be set upon.
- L131 _public prototype_ `TWeakPtr<const FRemoteControlEntity> GetTargetEntity() const;` — Returns a Pointer to the current Target Entity
- L134 _public prototype_ `const FGuid& GetTargetEntityId() const;` — Returns the current Target Entity Id
- L137 _public prototype_ `void UpdateTargetEntity();` — Auxiliary Function to apply to update the Target Texture
- L140 _public prototype_ `void RefreshPathArray();` — Called whenever a change has occured in the Slate
- L145 _public member_ `TObjectPtr<URCVirtualPropertyContainerBase> PropertyInContainer;` — `UPROPERTY()` — Pointer to property container
- L149 _public member_ `TObjectPtr<UClass> AssetClass = GetSupportedClasses()[0];` — `UPROPERTY()` — Pointer to the current Class the Asset will use to set the Targeted Exposed Object.
- L153 _public member_ `FRCSetAssetPath PathStruct;` — `UPROPERTY()` — Struct holding the Path Information to help load Assets.
- L157 _public member_ `bool bInternal = true;` — `UPROPERTY()` — Bool used to help tell if the path given is an internal or external one.
- L162 _private member_ `FGuid TargetEntityId;` — `UPROPERTY()` — Targeted Property Id
- L165 _private member_ `TSharedPtr<const FRemoteControlEntity> TargetEntity;` — Internal Targeted Property, used for any of the setter operations
- L169 _private prototype_ `bool SetInternalAsset(UObject* SetterObject);` — Auxiliary Function which sets the given SetterObject Asset onto the Exposed Asset with the given PropertyString name.
- L172 _private prototype_ `bool SetExternalAsset(FString InExternalPath);` — Given an External Path towards a external location, loads the asset associated and places it onto an object
- L175 _private prototype_ `bool SetTextureAsset(TSharedPtr<FRemoteControlProperty> InRemoteControlPropertyPtr, UTexture* InObject);` — Auxiliary Function to apply a Texture onto a given Property
- L178 _private prototype_ `bool SetTextureFromPath(TSharedPtr<FRemoteControlProperty> TexturePtr, FString& FileName);` — Auxiliary Function to apply a Texture onto a given Property
- L181 _private prototype_ `void ReadFileHttpHandler(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, TSharedPtr<FRemoteControlProperty> InRCPropertyToSet);` — Http Request Process Handler

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace SetAssetByPathBehaviourHelpers`
- L18 _variable_ `const FString ContentFolder = FString(TEXT("/Gam` (scope `SetAssetByPathBehaviourHelpers`)
- L19 _variable_ `const FString InputToken = FString(TEXT("{INP` (scope `SetAssetByPathBehaviourHelpers`)
- L20 _variable_ `const FName TargetProperty = FName(TEXT("Targ` (scope `SetAssetByPathBehaviourHelpers`)
- L21 _variable_ `const FName DefaultInput = FName(TEXT("Defa` (scope `SetAssetByPathBehaviourHelpers`)
- L22 _variable_ `const FName SetAssetByPathBehaviour = FName(TEXT("Set` (scope `SetAssetByPathBehaviourHelpers`)

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlLogic/Public/Behaviour/Builtin/RCBehaviourOnValueChangedNode.h` (Public)


#### class `URCBehaviourOnValueChangedNode`  
`class URCBehaviourOnValueChangedNode : public URCBehaviourNode`  
_L14-29_
- reflection: `UCLASS()`
- inherits: `URCBehaviourNode`
- desc: On Value Changed Behaviour Node This behaviour always returns true and thus executes all actions any time the Controller value is modified
- L20 _public prototype_ `URCBehaviourOnValueChangedNode();`
- L24 _public prototype_ `bool Execute(URCBehaviour* InBehaviour) const override;` — `UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Remote Control Behaviour")`
- L27 _public prototype_ `bool IsSupported(URCBehaviour* InBehaviour) const override;` — `UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Remote Control Behaviour")`

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlLogic/Public/Behaviour/Builtin/RangeMap/RCBehaviourRangeMapNode.h` (Public)


#### class `URCBehaviourRangeMapNode`  
`class URCBehaviourRangeMapNode : public URCBehaviourNode`  
_L12-32_
- reflection: `UCLASS()`
- inherits: `URCBehaviourNode`
- desc: Uses the given properties and values to limit the values of the Controller and perform lerp operations for the values.
- L18 _public prototype_ `URCBehaviourRangeMapNode();`
- L22 _public prototype_ `bool Execute(URCBehaviour* InBehaviour) const override;` — `UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Remote Control Behaviour")`
- L25 _public prototype_ `bool IsSupported(URCBehaviour* InBehaviour) const override;` — `UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Remote Control Behaviour")`
- L28 _public prototype_ `void OnPassed(URCBehaviour* InBehaviour) const;` — `UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Remote Control Behaviour")`
- L30 _public prototype_ `UClass* GetBehaviourClass() const override;`

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlLogic/Public/Behaviour/Builtin/RangeMap/RCRangeMapBehaviour.h` (Public)


#### struct `FRCRangeMapInput`  
`struct FRCRangeMapInput`  
_L13-36_
- reflection: `USTRUCT()`
- L17 _public function_ `FRCRangeMapInput()`
- L18 _public function_ `FRCRangeMapInput(URCVirtualPropertySelfContainer* InSelfContainer, URCVirtualPropertySelfContainer* InPropertyValue) : InputProperty(InSelfContainer), PropertyValue(InPropertyValue)`
- L25 _public member_ `TObjectPtr<URCVirtualPropertySelfContainer> InputProperty;` — `UPROPERTY()` — The Value which we use represent the action based on a normalized step.
- L29 _public member_ `TObjectPtr<URCVirtualPropertySelfContainer> PropertyValue;` — `UPROPERTY()` — The Property this Action holds and will be used for calculations for the lerp.
- L32 _public prototype_ `bool GetInputValue(double& OutValue) const;` — Returns the Step value from the virtual property, safely
- L35 _public prototype_ `bool SetInputValue(double InValue) const;` — Set the Step value for the virtual property, return true if successful

#### class `URCRangeMapBehaviour`  
`class URCRangeMapBehaviour : public URCBehaviour`  
_L42-123_
- reflection: `UCLASS()`
- inherits: `URCBehaviour`
- desc: Custom behaviour for Set Asset By Path Logic Behaviour
- L49 _public member_ `TObjectPtr<URCVirtualPropertyContainerBase> PropertyContainer;` — `UPROPERTY()` — Pointer to property container
- L53 _public member_ `TMap<TObjectPtr<URCAction>, FRCRangeMapInput> RangeMapActionContainer;` — `UPROPERTY()` — Container holding all FRCRangeMapInputs correlating to each Action in the ActionContainer.
- L56 _public prototype_ `URCRangeMapBehaviour();`
- L59 _public prototype_ `virtual void Initialize() override;`
- L62 _public prototype_ `virtual URCAction* DuplicateAction(URCAction* InAction, URCBehaviour* InBehaviour) override;` — Duplicates an Action belonging to us into a given target behaviour
- L65 _public prototype_ `virtual void NotifyActionValueChanged(URCAction* InChangedAction) override;` — Called when an action value changed
- L69 _public prototype_ `void Refresh();` — Refresh function being called whenever either the Controller or the Properties of the Behaviour Details Panel change
- L72 _public prototype_ `void OnActionAdded(URCAction* Action, URCVirtualPropertySelfContainer* InPropertyValue);` — Called whenever a new action is added into the ActionContainer. Will add a FRCRangeMapInput into RangeMapActionContainer corresponding to the Action.
- L75 _public prototype_ `virtual URCAction* AddAction(const TSharedRef<const FRemoteControlField> InRemoteControlField) override;` — Adds an Action to the ActionContainer, whilst making sure that it is unique.
- L78 _public prototype_ `virtual bool CanHaveActionForField(const TSharedPtr<FRemoteControlField> InRemoteControlField) const override;` — Checks whether or not one of the following fields can be added to the AddAction Menu. Makes sure they're unique.
- L81 _public function_ `virtual bool SupportPropertyId() const override` — Whether the behaviour support property id
- L84 _public prototype_ `bool GetValueForAction(const URCAction* InAction, double& OutValue);` — Returns the Step value associated with a given Action
- L89 _protected prototype_ `virtual void ExecuteInternal(const TSet<TObjectPtr<URCAction>>& InActionsToExecute) override;` — Execute all the action if not provided a valid Action otherwise will only execute the given action
- L94 _private member_ `double InputMin;` — Minimum Value which the Range has
- L97 _private member_ `double InputMax;` — Maximum Value which the Range has
- L100 _private member_ `float ControllerFloatValue;` — Controller Value of Type Float, which is used for the purpose of readability.
- L104 _private prototype_ `bool IsSupportedActionLerpType(TObjectPtr<URCAction> InAction) const;` — Boolean Function to help differentiate Custom Actions
- L107 _private prototype_ `bool GetNearestActionByThreshold(TTuple<URCAction*, bool>& OutTuple);` — Return the nearest Action and whether or not the distance between is less than the threshold.
- L110 _private prototype_ `void GetLerpActions(TMap<FGuid, TArray<URCAction*>>& OutNumericActionsByField, const TSet<TObjectPtr<URCAction>>& InActionsToExecute);` — Returns a Map of Numeric Actions, mapped by a double value, bound to a given FieldId
- L113 _private prototype_ `bool GetRangeValuePairsForLerp(TMap<FGuid, TTuple<URCAction*, URCAction*>>& OutPairs, const TSet<TObjectPtr<URCAction>>& InActionsToExecute);` — Gives out all pairs per Unique Exposed Field, which are applicable for Lerp.
- L116 _private prototype_ `TMap<double, URCAction*> GetNonLerpActions();` — Gives out all Actions which do not fall under as being able to Lerp. Used for Executing them based on Threshold and Distance
- L119 _private prototype_ `void ApplyLerpOnStruct(const FRCRangeMapInput* MinRangeInput, const FRCRangeMapInput* MaxRangeInput, const double& InputAlpha, const FGuid& FieldId);` — Auxiliary Function used to calculate and apply the Lerp on Structs, like FVectors or FRotators.
- L122 _private prototype_ `bool IsActionUnique(const TSharedRef<const FRemoteControlField> InRemoteControlField, const double& InValue, const TSet<TObjectPtr<URCAction>>& InActions);` — Returns whether or not an Action created with a given RemoteControlField can be considered unique.

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlLogic/Public/Behaviour/RCBehaviour.h` (Public)


#### class `URCBehaviour`  
`class URCBehaviour : public UObject`  
_L32-154_
- reflection: `UCLASS(BlueprintType)`
- inherits: `UObject`
- desc: Base class for remote control behaviour. Behaviour is container for: - Set of behaviour conditions - And associated actions which should be executed if that is passed the behaviour Behaviour can be extended in Blueprints or CPP classes
- L37 _public prototype_ `URCBehaviour();`
- L40 _public function_ `virtual void Initialize()` — Initialize behaviour functionality. Called just once when created by a controller.
- L43 _public prototype_ `void Execute();` — Execute the behaviour
- L46 _public prototype_ `virtual URCAction* AddAction();` — Add a Logic action as an identity action.
- L49 _public prototype_ `virtual URCAction* AddAction(FName InFieldId);` — Add a Logic action as an identity action.
- L52 _public prototype_ `virtual URCAction* AddAction(const TSharedRef<const FRemoteControlField> InRemoteControlField);` — Add a Logic action using a remote control field as input
- L55 _public prototype_ `virtual URCAction* DuplicateAction(URCAction* InAction, URCBehaviour* InBehaviour);` — Duplicates an Action belonging to us into a given target behaviour
- L58 _public prototype_ `int32 GetNumActions() const;` — Get number of action associated with behaviour
- L60 _public prototype_ `bool HasAction(const URCAction* InAction) const;`
- L63 _public prototype_ `virtual bool CanHaveActionForField(const TSharedPtr<FRemoteControlField> InRemoteControlField) const;` — Whether we can create an action pertaining to a given remote control field for the current behaviour
- L66 _public function_ `virtual bool SupportPropertyId() const` — Whether the behaviour support property id, by default true because of the OnModify Behaviour
- L71 _public prototype_ `UClass* GetOverrideBehaviourBlueprintClass() const;` — Return blueprint class associated with behaviour if exists
- L77 _public prototype_ `UBlueprint* GetBlueprint() const;` — Return blueprint instance associated with behaviour if exists
- L83 _public prototype_ `void SetOverrideBehaviourBlueprintClass(UBlueprint* InBlueprint);` — Set blueprint class for this behaviour
- L87 _public prototype_ `const FText& GetDisplayName();` — Get Display Name for this Behaviour
- L90 _public prototype_ `const FText& GetBehaviorDescription();` — Get Description for this Behaviour
- L97 _public prototype_ `virtual void UpdateEntityIds(const TMap<FGuid, FGuid>& InEntityIdMap);` — @brief Called internally when entity Ids are renewed. @param InEntityIdMap Map of old Id to new Id.
- L100 _public function_ `virtual void NotifyActionValueChanged(URCAction* InChangedAction)` — Called when an action value changed
- L107 _public prototype_ `URCBehaviourNode* GetBehaviourNode();` — It created the node if it called first time If BehaviourNodeClass changes it creates new instance Or just return cached one
- L109 _public prototype_ `void UpdateEntityUsage(const URCController* InController, TMap<FGuid, TSet<UObject*>>& InEntityToBehavior) const;`
- L113 _protected prototype_ `virtual void ExecuteInternal(const TSet<TObjectPtr<URCAction>>& InActionsToExecute);` — Execute all the action if not provided a valid Action otherwise will only execute the given action
- L116 _protected prototype_ `void ExecuteSingleAction(URCAction* InAction);` — Execute the given Action
- L121 _public member_ `TSubclassOf<URCBehaviourNode> BehaviourNodeClass;` — `UPROPERTY()` — Associated cpp behaviour
- L125 _public member_ `FSoftClassPath OverrideBehaviourBlueprintClassPath;` — `UPROPERTY()` — Class path to associated blueprint class behaviour
- L129 _public member_ `FGuid Id;` — `UPROPERTY()` — Behaviour Id
- L133 _public member_ `TObjectPtr<URCActionContainer> ActionContainer;` — `UPROPERTY()` — Action container which is associated with current behaviour
- L137 _public member_ `TWeakObjectPtr<URCController> ControllerWeakPtr;` — `UPROPERTY()` — Reference to controller virtual property with this behaviour
- L142 _private member_ `TObjectPtr<URCBehaviourNode> CachedBehaviourNode;` — `UPROPERTY(Instanced)` — Cached behaviour node
- L148 _public member_ `bool bIsEnabled = true;` — `UPROPERTY()` — Whether this Behaviour is currently enabled. If disabled, it will be not evaluated when the associated Controller changes
- L153 _public member_ `bool bExecuteBehavioursDuringPreChange = false;` — `UPROPERTY()` — Indicates whether we want a behavour to trigger during live scrubbing of values. For example, for a light intensity value controlled via Bind behavour we want the bound properties to update live even while the float widget is being scrubbed by the user.

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlLogic/Public/Behaviour/RCBehaviourBlueprintNode.h` (Public)


#### class `URCBehaviourBlueprintNode`  
`class URCBehaviourBlueprintNode : public URCBehaviourNode`  
_L12-28_
- reflection: `UCLASS(Abstract, Blueprintable)`
- inherits: `URCBehaviourNode`
- desc: Base blueprint class for behaviour node which holds the logic to execute behaviour
- L18 _public prototype_ `bool IsSupported(URCBehaviour* InBehaviour) const override;` — `UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Remote Control Behaviour")`
- L21 _public prototype_ `bool Execute(URCBehaviour* InBehaviour) const override;` — `UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Remote Control Behaviour")`
- L24 _public prototype_ `void PreExecute(URCBehaviour* InBehaviour) const override;` — `UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Remote Control Behaviour")`
- L27 _public prototype_ `void OnPassed(URCBehaviour* InBehaviour) const override;` — `UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Remote Control Behaviour")`

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlLogic/Public/Behaviour/RCBehaviourNode.h` (Public)


#### class `URCBehaviourNode`  
`class URCBehaviourNode : public UObject`  
_L16-69_
- reflection: `UCLASS(Abstract, BlueprintType, Blueprintable, EditInlineNew)`
- inherits: `UObject`
- desc: Base class for behaviour node which holds the logic to execute behaviour
- L26 _public prototype_ `virtual bool IsSupported(URCBehaviour* InBehaviour) const;` — Whether node supported based on input handle @param InBehaviour Remote Control Behaviour
- L33 _public prototype_ `virtual void PreExecute(URCBehaviour* InBehaviour) const;` — Called before behaviour event @param InBehaviour Remote Control Behaviour
- L40 _public prototype_ `virtual bool Execute(URCBehaviour* InBehaviour) const;` — Execute behaviour event @param InBehaviour Remote Control Behaviour
- L47 _public prototype_ `virtual void OnPassed(URCBehaviour* InBehaviour) const;` — Called if executed with true @param InBehaviour Remote Control Behaviour
- L50 _public prototype_ `virtual UClass* GetBehaviourClass() const;` — Get the Behaviour class for this Behaviour node
- L57 _public member_ `FText DisplayName;` — `UPROPERTY(EditDefaultsOnly, Category = "Remote Control Behavior")` — User-friendly display name for this Behavior, displayed in Action Panel's Header. Custom behavior blueprints can set this value in defaults to update the display name
- L64 _public member_ `FText BehaviorDescription;` — `UPROPERTY(EditDefaultsOnly, Category = "Remote Control Behavior")` — Detailed description of what this behavior does, displayed in Action Panel's Header. Custom behavior blueprints can set this value in defaults to update the display name
- L68 _protected prototype_ `static TFunction<bool(const TPair<EPropertyBagPropertyType, UObject*>)> GetIsSupportedCallback(URCBehaviour* InBehaviour);` — Return supported check callback

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlLogic/Public/Controller/RCController.h` (Public)


#### class `URCController`  
`class URCController : public URCVirtualPropertyInContainer`  
_L17-94_
- reflection: `UCLASS(BlueprintType)`
- inherits: `URCVirtualPropertyInContainer`
- desc: Remote Control Controller. Container for Behaviours and Actions
- L24 _public prototype_ `virtual void UpdateEntityIds(const TMap<FGuid, FGuid>& InEntityIdMap) override;`
- L29 _public prototype_ `virtual void PostEditUndo();` — Called after applying a transaction to the object. Used to broadcast Undo related container changes to UI Used to broadcast Undo related container changes to UI
- L33 _public prototype_ `virtual URCBehaviour* AddBehaviour(TSubclassOf<URCBehaviourNode> InBehaviourNodeClass);` — Create and add behaviour to behaviour set
- L36 _public prototype_ `virtual URCBehaviour* CreateBehaviour(TSubclassOf<URCBehaviourNode> InBehaviourNodeClass);` — Create new behaviour
- L39 _public prototype_ `virtual URCBehaviour* CreateBehaviourWithoutCheck(TSubclassOf<URCBehaviourNode> InBehaviourNodeClass);` — Create new behaviour without checking if supported
- L42 _public prototype_ `virtual int32 RemoveBehaviour(URCBehaviour* InBehaviour);` — Remove the behaviour by behaviour UObject pointer
- L45 _public prototype_ `virtual int32 RemoveBehaviour(const FGuid InBehaviourId);` — Remove the behaviour by behaviour id
- L48 _public prototype_ `bool HasBehavior(const URCBehaviour* InBehavior) const;` — Returns true if the behaviour exist in this controller.
- L51 _public prototype_ `virtual void EmptyBehaviours();` — Removes all behaviours.
- L54 _public prototype_ `virtual void ExecuteBehaviours(const bool bIsPreChange = false);` — Execute all behaviours for this controller.
- L57 _public prototype_ `virtual void OnPreChangePropertyValue() override;` — Pre-change notification for Controllers. Triggered while the user is scrubbing a float or vector slider in the UI
- L60 _public prototype_ `virtual void OnModifyPropertyValue() override;` — Handles modifications to controller value; evaluates all behaviours
- L62 _public function_ `TConstArrayView<TObjectPtr<URCBehaviour>> GetBehaviors() const`
- L68 _public prototype_ `static URCBehaviour* DuplicateBehaviour(URCController* InController, URCBehaviour* InBehaviour);` — Duplicates an existing behaviour and adds it to the behaviour set of a given Controller
- L71 _public prototype_ `bool ReorderBehaviorItems(URCBehaviour* InDroppedOnBehavior, bool bInBelowItem, TArray<URCBehaviour*> InDroppedBehaviors);` — Rearranges the behaviors based on the dropped behaviours.
- L74 _public member_ `FOnBehaviourListModified OnBehaviourListModified;` — Delegate that notifies changes to the list of behaviours
- L77 _public prototype_ `virtual void UpdateEntityUsage(const URemoteControlPreset* InPreset, TMap<FGuid, TSet<UObject*>>& InEntityToBehavior) const override;`
- L81 _public prototype_ `virtual void PostLoad() override;`
- L88 _public member_ `TSet<TObjectPtr<URCBehaviour>> Behaviours;` — `UE_DEPRECATED(5.7, "Please use the array Behaviors instead.")` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "Please use the array Behaviors instead."))` — Deprecated set of behaviors
- L93 _protected member_ `TArray<TObjectPtr<URCBehaviour>> Behaviors;` — `UPROPERTY()` — Array of the behaviors

#### Free symbols / members of external scopes

- L11 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnBehaviourListModified);`
- L11 _prototype_ `DECLARE_MULTICAST_DELEGATE(FOnBehaviourListModified);`

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlLogic/Public/Controller/RCControllerContainer.h` (Public)


#### class `URCControllerContainer`  
`class URCControllerContainer : public URCVirtualPropertyContainerBase`  
_L15-43_
- reflection: `UCLASS()`
- inherits: `URCVirtualPropertyContainerBase`
- desc: Controller Container which holds all virtual controller properties
- L21 _public prototype_ `virtual void UpdateEntityIds(const TMap<FGuid, FGuid>& InEntityIdMap) override;`
- L25 _public prototype_ `virtual URCVirtualPropertyInContainer* AddProperty(const FName& InPropertyName, TSubclassOf<URCVirtualPropertyInContainer> InPropertyClass, const EPropertyBagPropertyType InValueType, UObject* InValueTypeObject = nullptr, TArray<FPropertyBagPropertyDescMetaData> MetaData = TArray<FPropertyBagPropertyDescMetaData>()) override;` — Adds a new Controller to this container
- L30 _private prototype_ `URCController* GetControllerFromChangeEvent(const FPropertyChangedEvent& Event);` — Fetches the Controller underlying a given a Property Changed Event
- L33 _private prototype_ `virtual void OnPreChangePropertyValue(const FPropertyChangedEvent& PropertyChangedEvent) override;` — Delegate when the value is being scrubbed in UI
- L36 _private prototype_ `virtual void OnModifyPropertyValue(const FPropertyChangedEvent& PropertyChangedEvent) override;` — Delegate when object changed
- L42 _protected member_ `TSet<TObjectPtr<URCActionContainer>> SharedActionContainers;` — `UPROPERTY()` — Controller Container could holds the set of shared Action containers which is holds some action but independent from the behaviour

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlLogic/Public/Controller/RCControllerUtilities.h` (Public)


#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace RCControllers` (scope `UE`)
- L18 _prototype_ `bool CanCreateControllerFromPropertyDesc(const FPropertyBagPropertyDesc& InPropertyDesc);` (scope `UE::RCControllers`) — Determines whether a controller can be created from a given property desc explicitly Explicit meaning that it won't use IsChildOf or recurse up its Super Types for Object/Struct properties
- L24 _prototype_ `bool CanCreateControllerFromEntity(const TSharedPtr<const FRemoteControlProperty>& InPropertyEntity);` (scope `UE::RCControllers`) — Determines whether a controller can be created from a given property entity explicitly Explicit meaning that it won't use IsChildOf or recurse up its Super Types for Object/Struct properties
- L30 _prototype_ `bool CanCreateControllerFromProperty(const FProperty* InProperty);` (scope `UE::RCControllers`) — Determines whether a controller can be created from a given property type explicitly Explicit meaning that it won't use IsChildOf or recurse up its Super Types for Object/Struct properties

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlLogic/Public/Controller/RCCustomControllerUtilities.h` (Public)


#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace RCCustomControllers` (scope `UE`)
- L15 _prototype_ `bool IsCustomController(const URCVirtualPropertyBase* InController);` (scope `UE::RCCustomControllers`) — Checks if the passed virtual property has Custom Controller metadata available
- L18 _prototype_ `bool IsValidCustomController(const FName& InCustomControllerTypeName);` (scope `UE::RCCustomControllers`) — Checks if the specified Custom Controller Type Name exists (e.g. is not a made up type)
- L21 _prototype_ `FString GetCustomControllerTypeName(const URCVirtualPropertyBase* InController);` (scope `UE::RCCustomControllers`) — Returns the Custom Controller Type Name (e.g. Asset Path). Empty string if Controller is not a custom one.
- L24 _function_ `inline bool CustomControllerExecutesOnLoad(const URCVirtualPropertyBase* InController)` (scope `UE::RCCustomControllers`) — `UE_DEPRECATED(5.4, "Custom Controllers execution on load is deprecated. Function will always return false.")`
- L27 _function_ `inline bool CustomControllerExecutesOnLoad(const FName& InCustomControllerTypeName)` (scope `UE::RCCustomControllers`) — `UE_DEPRECATED(5.4, "Custom Controllers execution on load is deprecated. Function will always return false.")`
- L30 _prototype_ `EPropertyBagPropertyType GetCustomControllerType(const FName& InCustomControllerTypeName);` (scope `UE::RCCustomControllers`) — Returns the type associated to the specified Custom Controller Type Name
- L33 _prototype_ `EPropertyBagPropertyType GetCustomControllerType(const FString& InCustomControllerTypeName);` (scope `UE::RCCustomControllers`) — Returns the type associated to the specified Custom Controller Type Name
- L35 _prototype_ `TMap<FName, FString> GetCustomControllerMetaData(const FString& InCustomControllerTypeName);` (scope `UE::RCCustomControllers`)
- L41 _prototype_ `FName GetUniqueNameForController(const URCVirtualPropertyInContainer* InController);` (scope `UE::RCCustomControllers`) — Generates a unique name for a Custom Controller, based on its Custom Type Name Useful when creating a new controller.
- L43 _prototype_ `bool GetEntitiesControlledByController(const URemoteControlPreset* InRemoteControlPreset, const URCVirtualPropertyBase* InVirtualProperty, TSet<FGuid>& OutEntityIds);` (scope `UE::RCCustomControllers`)
- L45 _prototype_ `bool GetControllersOfEntity(const URemoteControlPreset* InRemoteControlPreset, const FGuid& InEntity, TSet<const URCVirtualPropertyBase*>& OutControllers);` (scope `UE::RCCustomControllers`)
- L47 _variable_ `inline static FName CustomControllerNameKey = "Cu` (scope `UE::RCCustomControllers`)
- L48 _variable_ `inline static FName CustomControllerExecuteOnLoadNameKey = "Cu` (scope `UE::RCCustomControllers`)
- L50 _variable_ `inline static FString CustomTextureControllerName = TEXT("Tex` (scope `UE::RCCustomControllers`)
- L51 _variable_ `inline static FString CustomStringListControllerName = TEXT("Str` (scope `UE::RCCustomControllers`)
- L52 _variable_ `inline static FString CustomStatelessEventControllerName = TEXT("Sta` (scope `UE::RCCustomControllers`)
- L54 _variable_ `inline static FName StringListControllerEntriesName = "St` (scope `UE::RCCustomControllers`)

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlLogic/Public/Controller/RCStatelessEventController.h` (Public)


#### struct `FRCStatelessEventController`  
`struct FRCStatelessEventController`  
_L13-18_
- reflection: `USTRUCT()`
- L17 _public prototype_ `static bool IsStatelessEventController(const URCVirtualPropertyBase* InController);`

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlLogic/Public/RemoteControlLogicConfig.h` (Public)


#### class `URemoteControlLogicConfig`  
`class URemoteControlLogicConfig: public UObject`  
_L13-37_
- reflection: `UCLASS(config=RemoteControl)`
- inherits: `UObject`
- desc: Config class for Remote Control Logic related settings. Supports configuration of a valid list of Controller types.
- L20 _public member_ `TArray<EPropertyBagPropertyType> SupportedControllerTypes;` — `UPROPERTY(config)` — PropertyBag types that are supported for use as Controllers
- L25 _public member_ `TArray<FName> SupportedControllerStructTypes;` — `UPROPERTY(config)` — Certain types such as FVector / FRotator / FColor are specializations of UStructProperty This config represents the list of such types that may be used as Controllers
- L29 _public member_ `TArray<FName> SupportedControllerObjectClassPaths;` — `UPROPERTY(config)` — Add specific Object types Class Paths to this list in order to provide support for them
- L36 _public member_ `TArray<FName> SupportedControllerCustomTypes;` — `UPROPERTY(config)` — Custom Controllers list. The elements in this list are used to generate customized versions of available controllers e.g. External Texture controller generates a specialized version of a String Controller. Support is introduced by adding MetaData to each newly created controller.
