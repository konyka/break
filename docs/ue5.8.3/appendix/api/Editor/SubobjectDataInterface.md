# Editor / SubobjectDataInterface

- module root: `Source/Editor/SubobjectDataInterface`
- headers: 7; symbols: 312
- symbol kinds: class=6, delegate=1, enum=1, enumerator=1, function=53, macro=5, member=38, namespace=4, prototype=186, struct=15, typedef=2
- PrivateDependencyModuleNames: BlueprintGraph, Engine, GameProjectGeneration, TypedElementFramework, UnrealEd
- PublicDependencyModuleNames: Core, CoreUObject, TypedElementFramework

### `Source/Editor/SubobjectDataInterface/Private/SubobjectDataTedsFactory.h` (Private)


#### class `USubobjectDataTedsFactory`  
`class USubobjectDataTedsFactory final : public UEditorDataStorageFactory`  
_L10-22_
- reflection: `UCLASS()`
- inherits: `UEditorDataStorageFactory`
- L15 _public prototype_ `~USubobjectDataTedsFactory() override = default;`
- L17 _public prototype_ `void RegisterTables(UE::Editor::DataStorage::ICoreProvider& DataStorage) override;`
- L19 _public prototype_ `UE::Editor::DataStorage::TableHandle GetSubobjectDataTableHandle() const;`
- L21 _private member_ `UE::Editor::DataStorage::TableHandle SubobjectDataTableHandle = UE::Editor::DataStorage::InvalidTableHandle;`

### `Source/Editor/SubobjectDataInterface/Public/SubobjectData.h` (Public)


#### struct `FSubobjectData`  
`struct FSubobjectData final`  
_L28-356_
- reflection: `USTRUCT(BlueprintType)`
- desc: A struct that represents a single subobject. This can be anything, but are most commonly components attached to an actor instance or blueprint. Keeps track of the handles to its parent object and any child that it has. If you wish to modify a subobject, use the SubobjectDataSubsystem.
- L34 _public prototype_ `FSubobjectData();`
- L37 _public prototype_ `FSubobjectData(UObject* ContextObject, const FSubobjectDataHandle& ParentHandle, const bool bIsInheritedSCS);` — `UE_DEPRECATED(5.7, "Use FSubobjectData default constructor + Initialize function")`
- L39 _public prototype_ `void Initialize(UObject* ContextObject, const FSubobjectDataHandle& ParentHandle, const bool bIsInheritedSCS);`
- L45 _public function_ `bool IsValid() const` — True if this subobject's handle is valid
- L50 _public prototype_ `const UObject* GetObject(bool bEvenIfPendingKill = false) const;` — @return	A read-only reference to the object represented by this node.
- L64 _public prototype_ `bool CanEdit() const;` — @return Whether or not we can edit properties for this subobject
- L69 _public prototype_ `bool CanDelete() const;` — @return Whether or not this object represents a subobject that can be deleted
- L74 _public prototype_ `bool CanDuplicate() const;` — @return Whether or not this object represents a subobject that can be duplicated
- L79 _public prototype_ `bool CanCopy() const;` — @return Whether or not this object represents a subobject that can be copied
- L85 _public prototype_ `bool CanReparent() const;` — @return Whether or not this object represents a subobject that can be reparented to other subobjects based on its context.
- L91 _public prototype_ `bool CanRename() const;` — @return Whether or not this object represents a subobject that can be renamed.
- L99 _public prototype_ `const UObject* GetObjectForBlueprint(UBlueprint* Blueprint) const;` — @param	InBlueprint			The Blueprint in which the object will be edited. @note	May not be the same as the value returned by GetObject(). @return	A reference to the object represented by this node that can be modified within the given Blueprint.
- L102 _public function_ `template<class T> inline const T* GetObjectForBlueprint(UBlueprint* Blueprint) const`
- L116 _public function_ `template<class T> inline const T* GetObject(bool bEvenIfPendingKill = false) const` — @param	bEvenIfPendingKill	If false, nullptr will be returned if the cached object instance is pending kill. If true, it will be returned regardless (this is used for recaching the object if the objects have been reinstanced following construction script execution). @note	Deliberately non-virtual, for performance reasons. @return	A read-only reference to the object represented by this node.
- L130 _public function_ `inline const UActorComponent* GetComponentTemplate(bool bEvenIfPendingKill = false) const` — @param	bEvenIfPendingKill	If false, nullptr will be returned if the cached component template is pending kill. If true, it will be returned regardless (this is used for recaching the component template if the objects have been reinstanced following construction script execution). @note	Deliberately non-virtual, for performance reasons. @warning This will not return the right component for components overridden by the inherited component handler, you need to call GetOrCreateEditableComponentTemplate instead @return	The component template or instance represented by this node, if it's a component node.
- L135 _public function_ `inline const UActorComponent* FindComponentInstanceInActor(const AActor* InActor) const`
- L137 _public prototype_ `UBlueprint* GetBlueprint() const;`
- L138 _public prototype_ `UBlueprint* GetBlueprintBeingEdited() const;`
- L140 _public prototype_ `bool IsInstancedComponent() const;`
- L141 _public prototype_ `bool IsInstancedActor() const;`
- L142 _public prototype_ `bool IsNativeComponent() const;`
- L143 _public prototype_ `bool IsBlueprintInheritedComponent() const;`
- L144 _public prototype_ `bool IsInheritedComponent() const;`
- L145 _public prototype_ `bool IsSceneComponent() const;`
- L146 _public prototype_ `bool IsRootComponent() const;`
- L147 _public prototype_ `bool IsDefaultSceneRoot() const;`
- L149 _public prototype_ `bool SceneRootHasDefaultName() const;` — Returns true if the component template's FName starts with USceneComponent::GetDefaultSceneRootVariableName
- L151 _public prototype_ `bool IsComponent() const;` — Returns true if this subobject is a component.
- L152 _public prototype_ `bool IsChildActor() const;`
- L155 _public prototype_ `bool IsChildActorSubtreeObject() const;` — Returns true if this subobject is a part of a child actor's hierarchy and not the root actor.
- L156 _public prototype_ `bool IsRootActor() const;`
- L157 _public prototype_ `bool IsActor() const;`
- L159 _public prototype_ `bool IsInstancedInheritedComponent() const;` — True if this subobject is an instance of an inherited component (its owner is an instanced actor)
- L161 _public prototype_ `bool IsAttachedTo(const FSubobjectDataHandle& InHandle) const;`
- L163 _public prototype_ `FString GetDisplayString(bool bShowNativeComponentNames = true) const;`
- L166 _public prototype_ `FText GetDragDropDisplayText() const;` — Get the display name of this subobject that should be used during drag/drop operations
- L173 _public prototype_ `FText GetDisplayNameContextModifiers(bool bShowNativeComponentNames = true) const;` — Returns a string that gives details about this subobject. For Inherited components it will return "(Inherited)". For native components this function will return "(NativeComponentName) (Inherited)"
- L175 _public prototype_ `FText GetDisplayName() const;`
- L177 _public prototype_ `FName GetVariableName() const;`
- L180 _public prototype_ `FText GetSocketName() const;` — Sockets for attaching in the viewport
- L181 _public prototype_ `FName GetSocketFName() const;`
- L182 _public prototype_ `bool HasValidSocket() const;`
- L183 _public prototype_ `void SetSocketName(FName InNewName);`
- L184 _public prototype_ `void SetupAttachment(FName SocketName, const FSubobjectDataHandle& AttachParentHandle = FSubobjectDataHandle::InvalidHandle);`
- L186 _public function_ `FSubobjectDataHandle GetHandle() const`
- L187 _public function_ `FSubobjectDataHandle GetParentHandle() const`
- L188 _public function_ `FSubobjectData* GetParentData() const`
- L189 _public function_ `bool HasParent() const`
- L190 _public function_ `const TArray<FSubobjectDataHandle>& GetChildrenHandles() const`
- L193 _public prototype_ `FSubobjectDataHandle GetRootSubobject() const;` — Walks the parent hierarchy and returns the root subobject in this case
- L196 _public prototype_ `bool HasChild(const FSubobjectDataHandle& ChildHandle) const;` — Return true if the given handle is a child of this subobject
- L199 _public prototype_ `FSubobjectDataHandle FindChild(const FSubobjectDataHandle& ChildHandle) const;` — Attempt to find the given handle in out child array and return a pointer to it
- L200 _public prototype_ `FSubobjectDataHandle FindChildByObject(UObject* ContextObject) const;`
- L203 _public prototype_ `FText GetAssetName() const;` — Get the asset name of this subobject from the asset brokerage
- L206 _public prototype_ `FText GetAssetPath() const;` — Get the asset path of this subobject from the asset brokerage
- L209 _public prototype_ `bool IsAssetVisible() const;` — Returns true if the asset this object represents is visible
- L216 _public prototype_ `FText GetToolTipText() const;` — Retrieves tooltip text describing the specified component. @returns An FText object containing a description of the component
- L223 _public prototype_ `FText GetMobilityToolTipText() const;` — Retrieves tooltip text describing the specified component's mobility. @returns An FText object containing a description of the component's mobility
- L230 _public prototype_ `FText GetComponentEditorOnlyTooltipText() const;` — Retrieves a tooltip text describing if the component is marked Editor only or not @returns An FText object containing a description of if the component is marked Editor only or not
- L237 _public prototype_ `FText GetIntroducedInToolTipText() const;` — Retrieves tooltip text describing where the component was first introduced (for inherited components). @returns An FText object containing a description of when the component was first introduced
- L239 _public prototype_ `FText GetActorDisplayText() const;`
- L245 _public prototype_ `void DisposeUnsafe();` — This type has livliness problems due to cycles in the shared pointer graph. This function clears the pointers involved in cycles, but live FSubobjectDatas will start to behave strangely once it is called
- L259 _private prototype_ `bool AddChildHandleOnly(const FSubobjectDataHandle& InHandle);` — Add the given subobject handle as a child of this. NOTE: This does NOT do any actual manipulation of the subobject structure. This only updates this subobject to have the correct handles in it's child structure. Actual manipulation of subobjects should be done via the SubobjectSubsystem.
- L267 _private prototype_ `bool RemoveChildHandleOnly(const FSubobjectDataHandle& InHandle);` — Add the given subobject handle as a child of this. * NOTE: This does NOT do any actual manipulation of the subobject structure. This only updates this subobject to have the correct handles in it's child structure. Actual manipulation of subobjects should be done via the SubobjectSubsystem.
- L269 _private function_ `void SetParentHandle(const FSubobjectDataHandle& NewParentHandle)`
- L270 _private function_ `void ClearParentHandle()`
- L274 _private member_ `TWeakObjectPtr<UObject> WeakObjectPtr;` — `UPROPERTY()` — Weak ptr to the object instance represented by this node (e.g. component template)
- L278 _private member_ `FSubobjectDataHandle Handle;` — `UPROPERTY()` — Handle that will have a globally unique ID when it is constructed (i.e. when this is constructed)
- L282 _private member_ `FSubobjectDataHandle ParentObjectHandle;` — `UPROPERTY()` — Handle to this object's parent. If this is invalid, then it is the root subobject.
- L286 _private member_ `TArray<FSubobjectDataHandle> ChildrenHandles;` — `UPROPERTY()` — Set of child subobjects that use this subobject as a parent
- L293 _private member_ `TInstancedStruct<FSubobjectDataSubsystemContextDataBase> ContextData;` — `UPROPERTY()` — ContextData is a replacement for ContextObject as a mechanism to allow SubobjectData to serve as an interface for multiple data types (not just single UObject) but multiple non-UObject ContextObject will still be populated with a single UObject if available, but ContextData should be the preferred data source for the SubobjectData instances.
- L297 _private function_ `inline UObject* GetMutableObject(bool bEvenIfPendingKill = false) const` — Muteable accessors for this subobject to be used by the subsystem
- L301 _private prototype_ `AActor* GetMutableActorContext();` — If this subobject is an actor, then return a pointer to that. Otherwise, search for the owning actor on this component and return it.
- L304 _private function_ `template<class T> inline T* GetMutableObject(bool bEvenIfPendingKill = false) const`
- L310 _private function_ `template<class T> inline T* GetMutableObjectForBlueprint(UBlueprint* Blueprint) const`
- L315 _private function_ `inline UActorComponent* GetMutableComponentTemplate(bool bEvenIfPendingKill = false) const`
- L320 _private prototype_ `UActorComponent* FindMutableComponentInstanceInActor(const AActor* InActor) const;`
- L326 _private prototype_ `static USCS_Node* FindSCSNodeForInstance(const UActorComponent* InstanceComponent, UClass* ClassToSearch);` — Tries to find a SCS node that was likely responsible for creating the specified instance component.  Note: This is not always possible to do!
- L328 _private prototype_ `USCS_Node* GetSCSNode(bool bEvenIfPendingKill = false) const;`
- L339 _private prototype_ `bool AttemptToSetSCSNode();` — Attempts to set the SCS node member variable based on the WeakObjectPtr. If the weak obj ptr _is_ an USCS_Node type, then we have to change the component template. If this is an instanced component, then we can find the scs node via FindSCSNodeForInstance. @return True if an SCS node has been set
- L344 _private member_ `TWeakObjectPtr<USCS_Node> SCSNodePtr;` — For now, we need a pointer to the SCS node in order to have the correct component template and to be able to get the UBlueprint* from components. This will only be set upon construction if the given Object Context is an USCS_Node. The context object will be set to its template.
- L350 _private prototype_ `bool IsInheritedSCSNode() const;` — True if this SCS node's blueprint is a child of another Blueprint-generated class, which means that we must use the InheritableComponentHandler
- L353 _private member_ `bool bIsInheritedSubobject = false;` — True if this SCS node is inherited from another blueprint generated class.
- L354 _private member_ `bool bIsInheritedSCS = false;`
- L355 _private member_ `bool bIsChildActor = false;`

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API SUBOBJECTDATAINTERFACE_API`

### `Source/Editor/SubobjectDataInterface/Public/SubobjectDataAdapterBase.h` (Public)


#### struct `FSubobjectDataAdapterHandle`  
`FSubobjectDataAdapterHandle`  
_L28-33_
- L32 _private member_ `uint64 Opaque = 0;`

#### struct `FSubobjectDataSubsystemAdapterHandle`  
`FSubobjectDataSubsystemAdapterHandle`  
_L36-41_
- L40 _private member_ `uint64 Opaque = 0;`

#### struct `FSubobjectDataSubsystemContextDataBase`  
`FSubobjectDataSubsystemContextDataBase`  
_L45-48_

#### struct `FSubobjectDataTag`  
`struct FSubobjectDataTag : public FEditorDataStorageTag`  
_L51-54_
- reflection: `USTRUCT()`
- inherits: `FEditorDataStorageTag`

#### struct `FSubobjectDataSubsystemRowReferenceCollection`  
`struct FSubobjectDataSubsystemRowReferenceCollection : public FEditorDataStorageColumn`  
_L59-65_
- reflection: `USTRUCT()`
- inherits: `FEditorDataStorageColumn`
- desc: TEDS column to store a collection of rows that are being displayed under a node in the subobject editor component tree Used when SubobjectEditor::UseTedsHierarchies() is false
- L64 _public member_ `TArray<FTedsRowHandle> Rows;` — `UPROPERTY()`

#### struct `FSubobjectDataSubsystemContextData_SingleUObjectContextObject`  
`FSubobjectDataSubsystemContextData_SingleUObjectContextObject : public FSubobjectDataSubsystemContextDataBase`  
_L71-80_
- inherits: `FSubobjectDataSubsystemContextDataBase`
- L75 _public prototype_ `FSubobjectDataSubsystemContextData_SingleUObjectContextObject();`
- L76 _public prototype_ `explicit FSubobjectDataSubsystemContextData_SingleUObjectContextObject(UObject* ContextObject);`
- L79 _public member_ `TWeakObjectPtr<UObject> Object;` — `UPROPERTY()`

#### struct `FSubobjectDataSubsystemContextData_TedsRow`  
`FSubobjectDataSubsystemContextData_TedsRow : public FSubobjectDataSubsystemContextDataBase`  
_L84-101_
- inherits: `FSubobjectDataSubsystemContextDataBase`
- L88 _public prototype_ `FSubobjectDataSubsystemContextData_TedsRow();`
- L89 _public prototype_ `explicit FSubobjectDataSubsystemContextData_TedsRow(UE::Editor::DataStorage::RowHandle InRowHandle);`
- L91 _public function_ `UE::Editor::DataStorage::RowHandle GetRow() const`
- L96 _public prototype_ `static UE::Editor::DataStorage::TableHandle GetSubobjectItemTable(const UE::Editor::DataStorage::ICoreProvider& DataStorage);`
- L100 _private member_ `TSharedPtr<UE::Editor::DataStorage::FScopedRow> Row;`

#### class `FSubobjectDataSubsystemAdapterBase`  
`class FSubobjectDataSubsystemAdapterBase`  
_L111-145_
- desc: The base of an adapter/plugin that extends the SubobjectDataSubsystem by intercepting calls to the public API. To handle other types of subobjects (even non-UObject based), implement this base class and register it with the SubobjectDataSubsystem instance. Interception is expected to inspect the input data passed to the CanIntercept_* functions and, if they return true, calls the appropriate override.  Multiple adapters follow FIFO priority - first registered is first given a chance to intercept.
- L114 _public prototype_ `virtual ~FSubobjectDataSubsystemAdapterBase();`
- L115 _public prototype_ `virtual bool CanIntercept_GatherSubobjectData(const UE::Editor::FSubobjectEditorContext& Context) const;`
- L116 _public prototype_ `virtual void GatherSubobjectData(const UE::Editor::FSubobjectEditorContext& Context, TArray<FSubobjectDataHandle>& OutArray, TFunctionRef<FSubobjectDataHandle()> CreateSubobjectData) const;`
- L119 _public prototype_ `virtual bool CanIntercept_FindSceneRootForSubobject(const FSubobjectDataHandle& InHandle) const;` — Call this implementation of FindSceneRootForSubobject if returning true
- L123 _public prototype_ `virtual FSubobjectDataHandle FindSceneRootForSubobject(const FSubobjectDataHandle& InHandle) const;` — Returns the subobject handle of the "scene root" object - the definition dependent on the implementation. In legacy implementation - returns the actor that owns the provided component ~or~ returns the root SceneComponent of the provided Actor
- L125 _public prototype_ `virtual bool CanIntercept_DeleteSubobjects(const FSubobjectDataHandle& ContextHandle, const TArray<FSubobjectDataHandle>& SubobjectsToDelete, UBlueprint* BPContext = nullptr, bool bForce = false) const;`
- L126 _public prototype_ `virtual int32 DeleteSubobjects(const FSubobjectDataHandle& ContextHandle, const TArray<FSubobjectDataHandle>& SubobjectsToDelete) const;`
- L128 _public prototype_ `virtual bool CanIntercept_CanCopySubobjects(const TArray<FSubobjectDataHandle>& Handles) const;`
- L129 _public prototype_ `virtual bool CanCopySubobjects(const TArray<FSubobjectDataHandle>& Handles) const;`
- L131 _public prototype_ `virtual bool CanIntercept_CopySubobjects(const TArray<FSubobjectDataHandle>& Handles, UBlueprint* BpContext) const;`
- L132 _public prototype_ `virtual void CopySubobjects(const TArray<FSubobjectDataHandle>& Handles, UBlueprint* BpContext) const;`
- L134 _public prototype_ `virtual bool CanIntercept_CanPasteSubobjects(const FSubobjectDataHandle& RootHandle, UBlueprint* BPContext) const;`
- L135 _public prototype_ `virtual bool CanPasteSubobjects(const FSubobjectDataHandle& RootHandle,UBlueprint* Blueprint) const;`
- L137 _public prototype_ `virtual bool CanIntercept_PasteSubobjects(const FSubobjectDataHandle& RootHandle, const TArray<FSubobjectDataHandle>& NewParentHandles, UBlueprint* BPContext) const;`
- L138 _public prototype_ `virtual void PasteSubobjects(const FSubobjectDataHandle& RootHandle, const TArray<FSubobjectDataHandle>& NewParentHandles, UBlueprint* Blueprint, TArray<FSubobjectDataHandle>& OutPastedHandles) const;`
- L140 _public prototype_ `virtual bool CanIntercept_CanDuplicateSubobjects(const FSubobjectDataHandle& Context, const TArray<FSubobjectDataHandle>& SubobjectsToDup) const;`
- L141 _public prototype_ `virtual bool CanDuplicateSubobjects(const FSubobjectDataHandle& Context, const TArray<FSubobjectDataHandle>& SubobjectsToDup) const;`
- L143 _public prototype_ `virtual bool CanIntercept_DuplicateSubobjects(const FSubobjectDataHandle& Context, const TArray<FSubobjectDataHandle>& SubobjectsToDup, UBlueprint* BpContext) const;`
- L144 _public prototype_ `virtual void DuplicateSubobjects(const FSubobjectDataHandle& Context, const TArray<FSubobjectDataHandle>& SubobjectsToDup, UBlueprint* BpContext, TArray<FSubobjectDataHandle>& OutNewSubobjects) const;`

#### class `FSubobjectDataAdapterBase`  
`class FSubobjectDataAdapterBase`  
_L148-211_
- L151 _public prototype_ `virtual ~FSubobjectDataAdapterBase();`
- L153 _public prototype_ `virtual bool CanEdit(const FSubobjectData& Data) const;`
- L154 _public prototype_ `virtual bool CanDelete(const FSubobjectData& Data) const;`
- L155 _public prototype_ `virtual bool CanDuplicate(const FSubobjectData& Data) const;`
- L156 _public prototype_ `virtual bool CanCopy(const FSubobjectData& Data) const;`
- L157 _public prototype_ `virtual bool CanReparent(const FSubobjectData& Data) const;`
- L158 _public prototype_ `virtual bool CanRename(const FSubobjectData& Data) const;`
- L160 _public prototype_ `virtual const UObject* GetObject(const FSubobjectData& Data, bool bEventIfPendingKill = false) const;`
- L161 _public prototype_ `virtual const UObject* GetObjectForBlueprint(const FSubobjectData& Data, UBlueprint* Blueprint) const;`
- L162 _public prototype_ `virtual const UActorComponent* GetComponentTemplate(const FSubobjectData& Data, bool bEvenIfPendingKill = false) const;`
- L163 _public prototype_ `virtual const UActorComponent* FindComponentInstanceInActor(const FSubobjectData& Data, const AActor* InActor) const;`
- L164 _public prototype_ `virtual UActorComponent* FindMutableComponentInstanceInActor(const FSubobjectData& Data, const AActor* InActor) const;`
- L166 _public prototype_ `virtual UBlueprint* GetBlueprint(const FSubobjectData& Data) const;`
- L167 _public prototype_ `virtual UBlueprint* GetBlueprintBeingEdited(const FSubobjectData& Data) const;`
- L169 _public prototype_ `virtual bool IsInstancedComponent(const FSubobjectData& Data) const;`
- L170 _public prototype_ `virtual bool IsInstancedActor(const FSubobjectData& Data) const;`
- L171 _public prototype_ `virtual bool IsNativeComponent(const FSubobjectData& Data) const;`
- L172 _public prototype_ `virtual bool IsBlueprintInheritedComponent(const FSubobjectData& Data) const;`
- L173 _public prototype_ `virtual bool IsInheritedComponent(const FSubobjectData& Data) const;`
- L174 _public prototype_ `virtual bool IsSceneComponent(const FSubobjectData& Data) const;`
- L175 _public prototype_ `virtual bool IsRootComponent(const FSubobjectData& Data) const;`
- L176 _public prototype_ `virtual bool IsDefaultSceneRoot(const FSubobjectData& Data) const;`
- L177 _public prototype_ `virtual bool SceneRootHasDefaultName(const FSubobjectData& Data) const;`
- L178 _public prototype_ `virtual bool IsComponent(const FSubobjectData& Data) const;`
- L179 _public prototype_ `virtual bool IsChildActor(const FSubobjectData& Data) const;`
- L180 _public prototype_ `virtual bool IsChildActorSubtreeObject(const FSubobjectData& Data) const;`
- L181 _public prototype_ `virtual bool IsRootActor(const FSubobjectData& Data) const;`
- L182 _public prototype_ `virtual bool IsActor(const FSubobjectData& Data) const;`
- L183 _public prototype_ `virtual bool IsInstancedInheritedComponent(const FSubobjectData& Data) const;`
- L184 _public prototype_ `virtual bool IsAttachedTo(const FSubobjectData& Data, const FSubobjectDataHandle& InHandle) const;`
- L185 _public prototype_ `virtual FString GetDisplayString(const FSubobjectData& Data, bool bShowNativeComponentNames = true) const;`
- L186 _public prototype_ `virtual FText GetDragDropDisplayText(const FSubobjectData& Data) const;`
- L188 _public prototype_ `virtual FText GetDisplayNameContextModifiers(const FSubobjectData& Data, bool bShowNativeComponentNames = true) const;`
- L190 _public prototype_ `virtual FText GetDisplayName(const FSubobjectData& Data) const;`
- L192 _public prototype_ `virtual FName GetVariableName(const FSubobjectData& Data) const;`
- L195 _public prototype_ `virtual FText GetSocketName(const FSubobjectData& Data) const;` — Sockets for attaching in the viewport
- L196 _public prototype_ `virtual FName GetSocketFName(const FSubobjectData& Data) const;`
- L197 _public prototype_ `virtual bool HasValidSocket(const FSubobjectData& Data) const;`
- L198 _public prototype_ `virtual void SetSocketName(FSubobjectData& Data, FName InNewName) const;`
- L199 _public prototype_ `virtual void SetupAttachment(FSubobjectData& Data, FName SocketName, const FSubobjectDataHandle& AttachParentHandle) const;`
- L201 _public prototype_ `virtual FSubobjectDataHandle FindChildByObject(const FSubobjectData& Data, UObject* ContextObject) const;`
- L202 _public prototype_ `virtual FText GetAssetName(const FSubobjectData& Data) const;`
- L203 _public prototype_ `virtual FText GetAssetPath(const FSubobjectData& Data) const;`
- L204 _public prototype_ `virtual bool IsAssetVisible(const FSubobjectData& Data) const;`
- L205 _public prototype_ `virtual FText GetToolTipText(const FSubobjectData& Data) const;`
- L206 _public prototype_ `virtual FText GetMobilityToolTipText(const FSubobjectData& Data) const;`
- L207 _public prototype_ `virtual FText GetComponentEditorOnlyTooltipText(const FSubobjectData& Data) const;`
- L208 _public prototype_ `virtual FText GetIntroducedInToolTipText(const FSubobjectData& Data) const;`
- L210 _public prototype_ `virtual FText GetActorDisplayText(const FSubobjectData& Data) const;`

#### Free symbols / members of external scopes

- L20 _namespace_ `namespace UE`
- L20 _namespace_ `namespace Editor` (scope `UE`)
- L25 _macro_ `#define UE_API SUBOBJECTDATAINTERFACE_API`

### `Source/Editor/SubobjectDataInterface/Public/SubobjectDataBlueprintFunctionLibrary.h` (Public)


#### class `USubobjectDataBlueprintFunctionLibrary`  
`class USubobjectDataBlueprintFunctionLibrary : public UBlueprintFunctionLibrary`  
_L27-140_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBlueprintFunctionLibrary`
- desc: A function library with wrappers around the getter/setter functions for FSubobjectData that will make it easier to use within blueprint contexts.
- L32 _public function_ `static bool IsValid(const FSubobjectData& Data)` — `UFUNCTION(BlueprintCallable, BlueprintPure, Category="Subobject Data")`
- L35 _public function_ `static bool IsHandleValid(const FSubobjectDataHandle& DataHandle)` — `UFUNCTION(BlueprintCallable, BlueprintPure, Category="Subobject Data")`
- L38 _public prototype_ `static void GetData(const FSubobjectDataHandle& DataHandle, FSubobjectData& OutData);` — `UFUNCTION(BlueprintCallable, BlueprintPure, Category="Subobject Data")`
- L44 _public function_ `static void GetHandle(const FSubobjectData& Data, FSubobjectDataHandle& OutHandle)` — `UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Subobject Data")` — @return Get the handle for this subobject data
- L50 _public function_ `static void GetParentHandle(const FSubobjectData& Data, FSubobjectDataHandle& OutHandle)` — `UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Subobject Data")` — @return Get the parent handle for this subobject data
- L53 _public function_ `static FText GetDisplayName(const FSubobjectData& Data)` — `UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Subobject Data")`
- L56 _public function_ `static FName GetVariableName(const FSubobjectData& Data)` — `UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Subobject Data")`
- L59 _public function_ `static bool IsAttachedTo(const FSubobjectData& Data, const FSubobjectDataHandle& InHandle)` — `UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Subobject Data")`
- L65 _public function_ `static bool CanEdit(const FSubobjectData& Data)` — `UFUNCTION(BlueprintCallable, BlueprintPure, Category="Subobject Data")` — @return Whether or not we can edit properties for this subobject
- L71 _public function_ `static bool CanDelete(const FSubobjectData& Data)` — `UFUNCTION(BlueprintCallable, BlueprintPure, Category="Subobject Data")` — @return Whether or not this object represents a subobject that can be deleted
- L77 _public function_ `static bool CanDuplicate(const FSubobjectData& Data)` — `UFUNCTION(BlueprintCallable, BlueprintPure, Category="Subobject Data")` — @return Whether or not this object represents a subobject that can be duplicated
- L83 _public function_ `static bool CanCopy(const FSubobjectData& Data)` — `UFUNCTION(BlueprintCallable, BlueprintPure, Category="Subobject Data")` — @return Whether or not this object represents a subobject that can be copied
- L90 _public function_ `static bool CanReparent(const FSubobjectData& Data)` — `UFUNCTION(BlueprintCallable, BlueprintPure, Category="Subobject Data")` — @return Whether or not this object represents a subobject that can be reparented to other subobjects based on its context.
- L93 _public function_ `static bool CanRename(const FSubobjectData& Data)` — `UFUNCTION(BlueprintCallable, BlueprintPure, Category="Subobject Data")`
- L96 _public prototype_ `static const UObject* GetObject(const FSubobjectData& Data, bool bEvenIfPendingKill = false);` — `UFUNCTION(BlueprintCallable, BlueprintPure, Category="Subobject Data", meta = (DeprecatedFunction="Note", DeprecationMessage = "Use GetAssociatedObject - it will not return template objects for instances"))`
- L99 _public prototype_ `static const UObject* GetAssociatedObject(const FSubobjectData& Data);` — `UFUNCTION(BlueprintCallable, BlueprintPure, Category="Subobject Data")`
- L102 _public prototype_ `static const UObject* GetObjectForBlueprint(const FSubobjectData& Data, UBlueprint* Blueprint);` — `UFUNCTION(BlueprintCallable, Category="Subobject Data")`
- L105 _public function_ `static UBlueprint* GetBlueprint(const FSubobjectData& Data)` — `UFUNCTION(BlueprintCallable, BlueprintPure, Category="Subobject Data")`
- L108 _public function_ `static bool IsInstancedComponent(const FSubobjectData& Data)` — `UFUNCTION(BlueprintCallable, BlueprintPure, Category="Subobject Data")`
- L111 _public function_ `static bool IsInstancedActor(const FSubobjectData& Data)` — `UFUNCTION(BlueprintCallable, BlueprintPure, Category="Subobject Data")`
- L114 _public function_ `static bool IsNativeComponent(const FSubobjectData& Data)` — `UFUNCTION(BlueprintCallable, BlueprintPure, Category="Subobject Data")`
- L117 _public function_ `static bool IsInheritedComponent(const FSubobjectData& Data)` — `UFUNCTION(BlueprintCallable, BlueprintPure, Category="Subobject Data")`
- L120 _public function_ `static bool IsSceneComponent(const FSubobjectData& Data)` — `UFUNCTION(BlueprintCallable, BlueprintPure, Category="Subobject Data")`
- L123 _public function_ `static bool IsRootComponent(const FSubobjectData& Data)` — `UFUNCTION(BlueprintCallable, BlueprintPure, Category="Subobject Data")`
- L126 _public function_ `static bool IsDefaultSceneRoot(const FSubobjectData& Data)` — `UFUNCTION(BlueprintCallable, BlueprintPure, Category="Subobject Data")`
- L130 _public function_ `static bool IsComponent(const FSubobjectData& Data)` — `UFUNCTION(BlueprintCallable, BlueprintPure, Category="Subobject Data")` — Returns true if this subobject is a component.
- L133 _public function_ `static bool IsChildActor(const FSubobjectData& Data)` — `UFUNCTION(BlueprintCallable, BlueprintPure, Category="Subobject Data")`
- L136 _public function_ `static bool IsRootActor(const FSubobjectData& Data)` — `UFUNCTION(BlueprintCallable, BlueprintPure, Category="Subobject Data")`
- L139 _public function_ `static bool IsActor(const FSubobjectData& Data)` — `UFUNCTION(BlueprintCallable, BlueprintPure, Category="Subobject Data")`

#### Free symbols / members of external scopes

- L16 _macro_ `#define UE_API SUBOBJECTDATAINTERFACE_API`

### `Source/Editor/SubobjectDataInterface/Public/SubobjectDataHandle.h` (Public)


#### struct `FSubobjectDataHandle`  
`struct FSubobjectDataHandle`  
_L25-80_
- reflection: `USTRUCT(BlueprintType)`
- desc: A subobject handle is a globally unique identifier for subobjects Upon construction, the handle will be invalid. It is the responsibility of the owning FSubobjectData to set the DataPtr once the subobject data has validated that it has a good context.
- L32 _public function_ `explicit FSubobjectDataHandle() : DataPtr(nullptr)`
- L35 _public function_ `FSubobjectDataHandle(const TSharedPtr<FSubobjectData> Data) : DataPtr(Data)`
- L39 _public function_ `~FSubobjectDataHandle()`
- L49 _public function_ `inline bool IsValid() const` — True if the Handle is valid (i.e. not INDEX_NONE). This is true once GenerateNewHandle is called @return bool		True if this handle is valid
- L51 _public function_ `bool operator==(const FSubobjectDataHandle& Other) const`
- L56 _public function_ `bool operator!=(const FSubobjectDataHandle& Other) const`
- L62 _public function_ `inline TSharedPtr<FSubobjectData> GetSharedDataPtr() const` — Returns a pointer to the subobject data that this is a handle for
- L63 _public function_ `inline FSubobjectData* GetData() const`
- L69 _public member_ `static const FSubobjectDataHandle InvalidHandle;` — A static representation of an invalid handle. Mostly used as a return value for functions that need to return a handle but have the risk of being invalid.
- L79 _private member_ `TSharedPtr<FSubobjectData> DataPtr;` — Pointer to the actual subobject data that this handle represents

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FSubobjectDataHandle> : public TStructOpsTypeTraitsBase2<FSubobjectDataHandle>`  
_L83-89_
- inherits: `TStructOpsTypeTraitsBase2<FSubobjectDataHandle>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L86-88_

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API SUBOBJECTDATAINTERFACE_API`
- L72 _function_ `friend uint32 GetTypeHash(const FSubobjectDataHandle& Key)` — Get the hash code to use for the given FSubobjectDataHandle
- L87 _enumerator_ `WithIdenticalViaEquality = true` (scope `TStructOpsTypeTraits::__anonc9a3c5320103`)

### `Source/Editor/SubobjectDataInterface/Public/SubobjectDataInterfaceModule.h` (Public)


#### class `FSubobjectDataInterfaceModule`  
`class FSubobjectDataInterfaceModule : public IModuleInterface`  
_L8-15_
- inherits: `IModuleInterface`
- L13 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L14 _public prototype_ `virtual void ShutdownModule() override;`

### `Source/Editor/SubobjectDataInterface/Public/SubobjectDataSubsystem.h` (Public)


#### struct `FAddNewSubobjectParams`  
`struct FAddNewSubobjectParams`  
_L24-62_
- reflection: `USTRUCT(BlueprintType, Category = "SubobjectDataSubsystem")`
- desc: Options when adding a new subobject
- L28 _public function_ `FAddNewSubobjectParams() : ParentHandle(FSubobjectDataHandle::InvalidHandle) , NewClass(nullptr) , AssetOverride(nullptr) , BlueprintContext(nullptr) , bSkipMarkBlueprintModified(false) , bConformTransformToParent(true)`
- L39 _public member_ `FSubobjectDataHandle ParentHandle;` — `UPROPERTY(BlueprintReadWrite, Category = "SubobjectDataSubsystem")`
- L43 _public member_ `TObjectPtr<UClass> NewClass;` — `UPROPERTY(BlueprintReadWrite, Category = "SubobjectDataSubsystem")` — The class of the new subobject that will be added
- L46 _public member_ `UObject* AssetOverride;` — Specific asset to use instead of the selected asset in the content browser
- L53 _public member_ `TObjectPtr<UBlueprint> BlueprintContext;` — `UPROPERTY(BlueprintReadWrite, Category = "SubobjectDataSubsystem")` — Pointer to the blueprint context that this subobject is in. If this is null, it is assumed that this subobject is being added to an instance.
- L57 _public member_ `uint8 bSkipMarkBlueprintModified : 1;` — `UPROPERTY(BlueprintReadWrite, Category = "SubobjectDataSubsystem")` — Optionally skip marking this blueprint as modified (e.g. if we're handling that externally
- L61 _public member_ `uint8 bConformTransformToParent : 1;` — `UPROPERTY(BlueprintReadWrite, Category = "SubobjectDataSubsystem")` — Whether the newly created component should keep its transform, or conform it to its parent

#### struct `FReparentSubobjectParams`  
`struct FReparentSubobjectParams`  
_L66-89_
- reflection: `USTRUCT(BlueprintType, Category = "SubobjectDataSubsystem")`
- desc: Options for reparenting subobjects
- L70 _public prototype_ `FReparentSubobjectParams() = default;`
- L74 _public member_ `FSubobjectDataHandle NewParentHandle;` — `UPROPERTY(BlueprintReadWrite, Category = "SubobjectDataSubsystem")` — The handle of the subobject to reparent to.
- L81 _public member_ `TObjectPtr<UBlueprint> BlueprintContext = nullptr;` — `UPROPERTY(BlueprintReadWrite, Category = "SubobjectDataSubsystem")` — Pointer to the blueprint context that this subobject is in. If this is null, it is assumed that this subobject is being added to an instance.
- L88 _public member_ `TObjectPtr<AActor> ActorPreviewContext = nullptr;` — `UPROPERTY(BlueprintReadWrite, Category = "SubobjectDataSubsystem")` — The preview actor context to be used if in a blueprint context. This must have a value if BlueprintContext is needed.

#### struct `UE::Editor::FSubobjectEditorContext`  
`struct FSubobjectEditorContext`  
_L99-108_
- desc: Struct holding information about the context of a subobject editor
- L105 _public member_ `UObject* ObjectContext = nullptr;` — If editor operates on a single object, the object to use. I.e. the object typically returned by GetObjectContext inside a details panel. This might eventually be phased out in favor of always using SelectionSetName or some other way to identify the target objects (since there may be multiple)
- L107 _public member_ `TWeakObjectPtr<UTypedElementSelectionSet> SelectionSet = nullptr;`

#### class `USubobjectDataSubsystem`  
`class USubobjectDataSubsystem : public UEngineSubsystem`  
_L118-510_
- reflection: `UCLASS(MinimalAPI, Category = "SubobjectDataSubsystem")`
- inherits: `UEngineSubsystem`
- desc: The Subobject Data Subsystem will produce the reflected subobject data based on a given root object. A root object can be anything, an actor instance clicked on via the level editor, a UBlueprint* by opening an asset, or something piped in from python or other scripting languages.
- L124 _public prototype_ `virtual void Initialize(FSubsystemCollectionBase& Collection) override;` — Implement this for initialization of instances of the system
- L127 _public prototype_ `virtual void Deinitialize() override;` — Implement this for deinitialization of instances of the system
- L133 _public prototype_ `static USubobjectDataSubsystem* Get();` — Static wrapper for getting this engine subsystem. Will return nullptr if the SubobjectDataInterface module has not been loaded yet.
- L142 _public prototype_ `void GatherSubobjectData(UObject* ObjectContext, TArray<FSubobjectDataHandle>& OutArray);` — Gather all subobjects that the given UObject context has. Populates an array of handles that will have the given context and all it's subobjects. @param ObjectContext	Object to gather subobjects for @param OutArray		Array to populate (will be emptied first)
- L159 _public function_ `FOnNewSubobjectAdded& OnNewSubobjectAdded()` — Delegate invoked when a new subobject is successfully added
- L161 _public typedef_ `using FSubobjectDataAdapterFilter = TFunction<bool(const FSubobjectData&)>;`
- L170 _public typedef_ `using FSubobjectSubsystemAdapterFilter = TFunction<bool(const TInstancedStruct<FSubobjectDataSubsystemContextDataBase>& ContextData)>;`
- L187 _public prototype_ `void K2_GatherSubobjectDataForBlueprint(UBlueprint* Context, TArray<FSubobjectDataHandle>& OutArray);` — `UFUNCTION(BlueprintCallable, Category = "SubobjectDataSubsystem", meta = (DisplayName = "Gather Subobject Data For Blueprint"))` — Gather all subobjects that the given Blueprint context has. Populates an array of handles that will have the given context and all it's subobjects. @param Context		Object to gather subobjects for @param OutArray		Array to populate (will be emptied first)
- L197 _public prototype_ `void K2_GatherSubobjectDataForInstance(AActor* Context, TArray<FSubobjectDataHandle>& OutArray);` — `UFUNCTION(BlueprintCallable, Category = "SubobjectDataSubsystem", meta = (DisplayName = "Gather Subobject Data For Instance"))` — Gather all subobjects that the given actor instance has. Populates an array of handles that will have the given context and all it's subobjects. @param Context		Object to gather subobjects for @param OutArray		Array to populate (will be emptied first)
- L209 _public prototype_ `bool K2_FindSubobjectDataFromHandle(const FSubobjectDataHandle& Handle, FSubobjectData& OutData) const;` — `UFUNCTION(BlueprintCallable, Category = "SubobjectDataSubsystem", meta = (DisplayName = "FindSubobjectDataFromHandle"))` — Attempt to find the subobject data for a given handle. OutData will only be valid if the function returns true. @param Handle		Handle of the subobject data you want to acquire @param OutData	Reference to the subobject data to populate @return bool		true if the data was found
- L220 _public prototype_ `FSubobjectDataHandle FindHandleForObject(const FSubobjectDataHandle& Context, const UObject* ObjectToFind, UBlueprint* BPContext = nullptr) const;` — `UFUNCTION(BlueprintCallable, Category = "SubobjectDataSubsystem")` — Attempt to find an existing handle for the given object. @param Context		The context that the object to find is within @param ObjectToFind	The object that you want to find the handle for within the context @return FSubobjectDataHandle	The subobject handle for the object, Invalid handle if not found.
- L232 _public prototype_ `static UClass* CreateNewCPPComponent(TSubclassOf<UActorComponent> ComponentClass, const FString& NewClassPath, const FString& NewClassName);` — `UFUNCTION(BlueprintCallable, Category = "SubobjectDataSubsystem", meta = (DisplayName = "Create New C++ Component"))` — Creates a new C++ component from the specified class type The user will be prompted to pick a new subclass name and code will be recompiled @return The new class that was created
- L241 _public prototype_ `static UClass* CreateNewBPComponent(TSubclassOf<UActorComponent> ComponentClass, const FString& NewClassPath, const FString& NewClassName);` — `UFUNCTION(BlueprintCallable, Category = "SubobjectDataSubsystem", meta = (DisplayName = "Create New Blueprint Component"))` — Creates a new Blueprint component from the specified class type The user will be prompted to pick a new subclass name and a blueprint asset will be created @return The new class that was created
- L251 _public prototype_ `FSubobjectDataHandle AddNewSubobject(const FAddNewSubobjectParams& Params, FText& FailReason);` — `UFUNCTION(BlueprintCallable, Category = "SubobjectDataSubsystem")` — Add a new subobject as a child to the given parent object @param Params			Options to consider when adding this subobject @return FSubobjectDataHandle		Handle to the newly created subobject, Invalid handle if creation failed
- L263 _public prototype_ `int32 DeleteSubobjects(const FSubobjectDataHandle& ContextHandle, const TArray<FSubobjectDataHandle>& SubobjectsToDelete, UBlueprint* BPContext = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "SubobjectDataSubsystem", meta = (DisplayName = "Delete Subobjects from Blueprint"))` — Attempts to delete the given array of subobjects from their context @param ContextHandle			The owning context of the subobjects that should be removed @param SubobjectsToDelete		Array of subobject handles that should be deleted @param BPContext				The blueprint context for the given @return 	The number of subobjects successfully deleted
- L274 _public prototype_ `int32 K2_DeleteSubobjectsFromInstance(const FSubobjectDataHandle& ContextHandle, const TArray<FSubobjectDataHandle>& SubobjectsToDelete);` — `UFUNCTION(BlueprintCallable, Category = "SubobjectDataSubsystem", meta = (DisplayName = "Delete Subobjects from Instance"))` — Attempts to delete the given array of subobjects from their context @param ContextHandle			The owning context of the subobjects that should be removed @param SubobjectsToDelete		Array of subobject handles that should be deleted @return 	The number of subobjects successfully deleted
- L285 _public prototype_ `int32 DeleteSubobjects(const FSubobjectDataHandle& ContextHandle, const TArray<FSubobjectDataHandle>& SubobjectsToDelete, FSubobjectDataHandle& OutComponentToSelect, UBlueprint* BPContext = nullptr, bool bForce = false);` — Attempts to delete the given array of subobjects from their context @param ContextHandle			The owning context of the subobjects that should be removed @param SubobjectsToDelete		Array of subobject handles that should be deleted @param OutComponentToSelect	Populates this handle with a valid selection in the component hierarchy if desired @param bForce					If true then this will attempt to delete a subobject even if the CanDelete function flags otherwise. @return 	The number of subobjects successfully deleted
- L297 _public prototype_ `int32 DeleteSubobject(const FSubobjectDataHandle& ContextHandle, const FSubobjectDataHandle& SubobjectToDelete, UBlueprint* BPContext = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "SubobjectDataSubsystem", meta = (DisplayName = "Delete Subobject from Blueprint"))` — Attempts to delete the given subobject from its blueprint context @param ContextHandle			The owning context of the subobjects that should be removed @param SubobjectToDelete		The subobject handles that should be deleted @param BPContext				The blueprint context for the given @return 	The number of subobjects successfully deleted
- L308 _public prototype_ `int32 K2_DeleteSubobjectFromInstance(const FSubobjectDataHandle& ContextHandle, const FSubobjectDataHandle& SubobjectToDelete);` — `UFUNCTION(BlueprintCallable, Category = "SubobjectDataSubsystem", meta = (DisplayName = "Delete Subobject from Instance"))` — Attempts to delete the given subobject from its context @param ContextHandle			The owning context of the subobjects that should be removed @param SubobjectToDelete		The subobject handles that should be deleted @return 	The number of subobjects successfully deleted
- L319 _public prototype_ `bool RenameSubobject(const FSubobjectDataHandle& Handle, const FText& InNewName);` — `UFUNCTION(BlueprintCallable, Category = "SubobjectDataSubsystem")` — Attempts to rename the given subobject to the new name. @param Handle			Handle to the subobject to rename @param InNewName		The new name that is desired for the given subobject @return True if the rename was successful, false otherwise.
- L330 _public prototype_ `bool ChangeSubobjectClass(const FSubobjectDataHandle& Handle, const UClass* NewClass);` — `UFUNCTION(BlueprintCallable, Category = "SubobjectDataSubsystem")` — Attempts to change the subclass of a native component @param Handle			Handle to the subobject to change class of @param NewClass		The new class that is desired for the given subobject @return True if the class change was successful, false otherwise.
- L341 _public prototype_ `bool ReparentSubobject(const FReparentSubobjectParams& Params, const FSubobjectDataHandle& ToReparentHandle);` — `UFUNCTION(BlueprintCallable, Category = "SubobjectDataSubsystem")` — Attempts to reparent the given subobject to the new parent @param NewParentHandle		Handle of the new parent @param ToReparentHandle		The handle of the subobject that will get moved @return True if the reparent was successful, false otherwise.
- L344 _public prototype_ `bool MakeNewSceneRoot(const FSubobjectDataHandle& Context, const FSubobjectDataHandle& NewSceneRoot, UBlueprint* BPContext);` — `UFUNCTION(BlueprintCallable, Category = "SubobjectDataSubsystem")`
- L352 _public prototype_ `bool ReparentSubobjects(const FReparentSubobjectParams& Params, const TArray<FSubobjectDataHandle>& HandlesToMove);` — `UFUNCTION(BlueprintCallable, Category = "SubobjectDataSubsystem")` — Attempts to reparent all subobjects in the HandlesToMove array to the new parent handle. @param NewParentHandle		Handle of the new parent
- L360 _public prototype_ `bool DetachSubobject(const FSubobjectDataHandle& OwnerHandle, const FSubobjectDataHandle& ChildToRemove);` — `UFUNCTION(BlueprintCallable, Category = "SubobjectDataSubsystem")` — Remove the child subobject from the owner @return True if the child was successfully removed.
- L372 _public prototype_ `bool AttachSubobject(const FSubobjectDataHandle& OwnerHandle, const FSubobjectDataHandle& ChildToAddHandle);` — `UFUNCTION(BlueprintCallable, Category = "SubobjectDataSubsystem")` — Add the given subobject to a new owner. This will remove the subobject from its previous owner if necessary. @param OwnerHandle		The new owner to attach to @param ChildToAddHandle	Handle to the subobject that will become a child of the owner @return true if the child was added successfully
- L386 _public prototype_ `bool IsValidRename(const FSubobjectDataHandle& Handle, const FText& InNewText, FText& OutErrorMessage) const;` — `UFUNCTION(BlueprintCallable, Category = "SubobjectDataSubsystem")` — Returns true if the given new text is a valid option to rename the subobject with the given handle. Populates the OutErrorMessage if it is not valid. @param Handle			Handle to the subobject that is being checked @param InNewText			The new name that is desired @param OutErrorMessage	The reasoning for an invalid name @return True if the rename is valid
- L393 _public prototype_ `bool CanCopySubobjects(const TArray<FSubobjectDataHandle>& Handles) const;` — `UFUNCTION(BlueprintCallable, Category = "SubobjectDataSubsystem")` — Returns true if the given array of handles represents subobjects that can be copied.
- L396 _public prototype_ `void CopySubobjects(const TArray<FSubobjectDataHandle>& Handles, UBlueprint* BpContext);` — `UFUNCTION(BlueprintCallable, Category = "SubobjectDataSubsystem")`
- L399 _public prototype_ `bool CanPasteSubobjects(const FSubobjectDataHandle& RootHandle, UBlueprint* BPContext = nullptr) const;` — `UFUNCTION(BlueprintCallable, Category = "SubobjectDataSubsystem")`
- L410 _public prototype_ `void PasteSubobjects(const FSubobjectDataHandle& PasteToContext, const TArray<FSubobjectDataHandle>& NewParentHandles, UBlueprint* BpContext, TArray<FSubobjectDataHandle>& OutPastedHandles);` — `UFUNCTION(BlueprintCallable, Category = "SubobjectDataSubsystem")` — Pastes the given subobjects to the PasteToContext. @param PasteToContext		The subobject to paste things onto @param NewParentHandles	Array of Subobject Handles that you would like to paste @param BpContext			Blueprint to use, if you are pasting to a blueprint. Null if pasting to an instanced object @param OutPastedHandles	Array populated with the handles to the newly pasted subobjects
- L412 _public prototype_ `bool CanDuplicateSubobjects(const FSubobjectDataHandle& Context, const TArray<FSubobjectDataHandle>& SubobjectsToDup);`
- L423 _public prototype_ `void DuplicateSubobjects(const FSubobjectDataHandle& Context, const TArray<FSubobjectDataHandle>& SubobjectsToDup, UBlueprint* BpContext, TArray<FSubobjectDataHandle>& OutNewSubobjects);` — `UFUNCTION(BlueprintCallable, Category = "SubobjectDataSubsystem")` — Duplicate the given array of subobjects on the context. @param Context			The owning context that the subobjects to dup come from @param SubobjectsToDup	Array of handles of existing subobjects you would like to have duplicated @param BpContext			Pointer to the current blueprint context if necessary. Use nullptr if dealing with instances @param OutNewSubobjects	Array that will be populated with any newly created subobjects
- L425 _public prototype_ `FScopedTransaction* BeginTransaction(const TArray<FSubobjectDataHandle>& Handles, const FText& Description, UBlueprint* Blueprint);`
- L432 _public prototype_ `FSubobjectDataHandle FindSceneRootForSubobject(const FSubobjectDataHandle& InHandle) const;` — Find the scene root for a given subobject handle. If this is an actor, then it will return the handle pointing to its DefaultSceneRoot. If this is a component, it will walk the parent chain until it finds the DefaultSceneRoot.
- L435 _public prototype_ `static void RenameSubobjectMemberVariable(UBlueprint* BPContext, const FSubobjectDataHandle& InHandle, const FName NewName);` — `UFUNCTION(BlueprintCallable, Category = "SubobjectDataSubsystem")`
- L444 _public prototype_ `static FSubobjectDataHandle GetActorRootHandle(const FSubobjectDataHandle& StartingHandle);` — Walk the hierarchy up to find the AActor root for the given handle @param StartingHandle		The handle to start walking the hierarchy at @return The handle of the root actor if one exists, FSubobjectDataHandle::InvalidHandle otherwise.
- L451 _private prototype_ `FSubobjectDataHandle FindOrCreateAttachParentForComponent(UActorComponent* InActorComponent, const FSubobjectDataHandle& ActorRootHandle, TArray<FSubobjectDataHandle>& ExistingHandles);` — Recursively add the attachment children of the given actor component
- L456 _private prototype_ `FSubobjectDataHandle FindAttachParentForInheritedComponent(UActorComponent* InActorComponent, const FSubobjectDataHandle& ActorRootHandle, UBlueprint* BP);` — Recursively search for an attachment parent that matches the given InActorComponent on the blueprint
- L462 _private prototype_ `void FindAllSubobjectData(FSubobjectData* RootContext, TSet<FSubobjectData*>& OutVisited) const;` — Find all child subobject data related to the given root context. Populates the OutVisited set with all data.
- L468 _private prototype_ `FSubobjectDataHandle CreateSubobjectData();` — Creates an invalid SubobjectData and associates a handle The SubobjectData can be initialized using the Initialize() function
- L473 _private prototype_ `FSubobjectDataHandle CreateSubobjectData(UObject* Context, const FSubobjectDataHandle& ParentHandle = FSubobjectDataHandle::InvalidHandle, bool bIsInheritedSCS = false);` — Gets a ref to subobject data that has been initialized with the given context. It will have a unique ID, but may be reused from the FreeData array.
- L479 _private prototype_ `FSubobjectDataHandle FactoryCreateSubobjectDataWithParent(UObject* Context, const FSubobjectDataHandle& ParentHandle, bool bIsInheritedSCS = false);` — Get a handle to the subobject with the given context with a specific parent. If the context is already a known child of the parent, then it will return an existing subobject handle.
- L486 _private prototype_ `FSubobjectDataHandle FactoryCreateInheritedBpSubobject(UObject* Context, const FSubobjectDataHandle& ParentHandle, bool bIsInherited, TArray<FSubobjectDataHandle>& OutArray);` — Create a subobject data and handle for an inherited blueprint context. This will populate the given array of handles recursively with all possible children (which are USCS_Node* in this case)
- L489 _private prototype_ `FSubobjectDataHandle FindParentForNewSubobject(const UObject* NewSubobject, const FSubobjectDataHandle& SelectedParent);` — Find the parent that this new subobject should attach to
- L491 _private member_ `FOnNewSubobjectAdded OnNewSubobjectAdded_Delegate;`
- L499 _private member_ `uint64 DataAdapterHandleIndex = 0;`
- L500 _private member_ `TArray<FSubobjectDataAdapterEntry> DataAdapters;`
- L507 _private member_ `uint64 SubsystemAdapterHandleIndex = 0;`
- L508 _private member_ `TArray<FSubsystemAdapterEntry> SubsystemAdapters;`

#### struct `USubobjectDataSubsystem::FSubobjectDataAdapterEntry`  
`struct FSubobjectDataAdapterEntry`  
_L493-498_
- L495 _public member_ `TUniquePtr<FSubobjectDataAdapterBase> Adapter;`
- L496 _public member_ `FSubobjectDataAdapterHandle Handle;`
- L497 _public member_ `FSubobjectDataAdapterFilter Filter;`

#### struct `USubobjectDataSubsystem::FSubsystemAdapterEntry`  
`struct FSubsystemAdapterEntry`  
_L502-506_
- L504 _public member_ `TUniquePtr<FSubobjectDataSubsystemAdapterBase> Adapter;`
- L505 _public member_ `FSubobjectDataSubsystemAdapterHandle Handle;`

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API SUBOBJECTDATAINTERFACE_API`
- L20 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnNewSubobjectAdded, const FSubobjectData&);`
- L20 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnNewSubobjectAdded, const FSubobjectData&);`
- L91 _namespace_ `namespace UE`
- L91 _namespace_ `namespace Editor` (scope `UE`)
