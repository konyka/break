# Runtime / TypedElementRuntime

- module root: `Source/Runtime/TypedElementRuntime`
- headers: 9; symbols: 318
- symbol kinds: class=16, delegate=4, enum=2, enumerator=6, function=140, member=29, namespace=4, prototype=106, struct=11
- PublicDependencyModuleNames: Core, CoreUObject, TypedElementFramework

### `Source/Runtime/TypedElementRuntime/Private/Elements/Framework/TypedElementSelectionSetLibrary.h` (Private)


#### class `UTypedElementSelectionSetLibrary`  
`class UTypedElementSelectionSetLibrary : public UObject`  
_L33-132_
- reflection: `UCLASS()`
- inherits: `UObject`
- desc: Library of functions for the scripting of Typed Elements that use both a selection set and a element list Note: These functions should only be used for scripting purposes only as they come at higher performance cost then their non script implementation
- L43 _public function_ `static bool SelectElementsFromList(UTypedElementSelectionSet* SelectionSet, const FScriptTypedElementListProxy ElementList, const FTypedElementSelectionOptions SelectionOptions)` — `UFUNCTION(BlueprintCallable, Category="TypedElementFramework|Selection", meta=(ScriptMethod))` — Attempt to select the given elements. @return True if the selection was changed, false otherwise.
- L65 _public function_ `static bool DeselectElementsFromList(UTypedElementSelectionSet* SelectionSet, const FScriptTypedElementListProxy ElementList, const FTypedElementSelectionOptions SelectionOptions)` — `UFUNCTION(BlueprintCallable, Category="TypedElementFramework|Selection", meta=(ScriptMethod))` — Attempt to deselect the given elements. @return True if the selection was changed, false otherwise.
- L88 _public function_ `static bool SetSelectionFromList(UTypedElementSelectionSet* SelectionSet, const FScriptTypedElementListProxy ElementList, const FTypedElementSelectionOptions SelectionOptions)` — `UFUNCTION(BlueprintCallable, Category="TypedElementFramework|Selection", meta=(ScriptMethod))` — Attempt to make the selection the given elements. @note Equivalent to calling ClearSelection then SelectElements, but happens in a single batch. @return True if the selection was changed, false otherwise.
- L106 _public function_ `static FScriptTypedElementListProxy GetNormalizedSelection(UTypedElementSelectionSet* SelectionSet, const FTypedElementSelectionNormalizationOptions NormalizationOptions)` — `UFUNCTION(BlueprintPure, Category="TypedElementFramework|Selection", meta=(ScriptMethod))` — Get a normalized version of this selection set that can be used to perform operations like gizmo manipulation, deletion, copying, etc. This will do things like expand out groups, and resolve any parent<->child elements so that duplication operations aren't performed on both the parent and the child.
- L122 _public function_ `static FScriptTypedElementListProxy GetNormalizedElementList(UTypedElementSelectionSet* SelectionSet, const FScriptTypedElementListProxy ElementList, const FTypedElementSelectionNormalizationOptions NormalizationOptions)` — `UFUNCTION(BlueprintPure, Category="TypedElementFramework|Selection", meta=(ScriptMethod))` — Get a normalized version of the given element list that can be used to perform operations like gizmo manipulation, deletion, copying, etc. This will do things like expand out groups, and resolve any parent<->child elements so that duplication operations aren't performed on both the parent and the child.

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace TypedElementFramework` (scope `UE`)
- L13 _namespace_ `namespace Private` (scope `UE::TypedElementFramework`)
- L16 _function_ `inline bool CheckForInvalidSelectionSet(UTypedElementSelectionSet* SelectionSet)` (scope `UE::TypedElementFramework::Private`) — Return true if the selection set is invalid

### `Source/Runtime/TypedElementRuntime/Public/Elements/Framework/TypedElementInterfaceCustomization.h` (Public)


#### class `FTypedElementInterfaceCustomizationRegistryBase`  
`class FTypedElementInterfaceCustomizationRegistryBase`  
_L16-33_
- desc: Non-templated base class for the interface customization registry.
- L19 _public prototype_ `virtual ~FTypedElementInterfaceCustomizationRegistryBase() = default;`
- L26 _protected prototype_ `FTypedHandleTypeId GetElementTypeIdFromName(const FName InElementTypeName) const;` — Given an element name, attempt to get its registered type ID from the global registry. @return The registered type ID, or 0 if the element name is not registered.
- L32 _protected prototype_ `FTypedHandleTypeId GetElementTypeIdFromNameChecked(const FName InElementTypeName) const;` — Given an element name, attempt to get its registered type ID from the global registry. @return The registered type ID, or asserts if the element name is not registered.

#### class `TTypedElementInterfaceCustomizationRegistry`  
`template <typename CustomizationBaseType, typename DefaultCustomizationType = CustomizationBaseType> class TTypedElementInterfaceCustomizationRegistry : public FTypedElementInterfaceCustomizationRegistryBase`  
_L39-134_
- inherits: `FTypedElementInterfaceCustomizationRegistryBase`
- desc: Utility to register and retrieve interface customizations for a given type.
- L43 _public function_ `template <typename... TDefaultArgs> TTypedElementInterfaceCustomizationRegistry(TDefaultArgs&&... DefaultArgs) : DefaultInterfaceCustomization(MakeUnique<DefaultCustomizationType>(Forward<TDefaultArgs>(DefaultArgs)...))`
- L48 _public prototype_ `virtual ~TTypedElementInterfaceCustomizationRegistry() = default;`
- L50 _public prototype_ `TTypedElementInterfaceCustomizationRegistry(const TTypedElementInterfaceCustomizationRegistry&) = delete;`
- L51 _public prototype_ `TTypedElementInterfaceCustomizationRegistry& operator=(const TTypedElementInterfaceCustomizationRegistry&) = delete;`
- L53 _public prototype_ `TTypedElementInterfaceCustomizationRegistry(TTypedElementInterfaceCustomizationRegistry&&) = delete;`
- L54 _public prototype_ `TTypedElementInterfaceCustomizationRegistry& operator=(TTypedElementInterfaceCustomizationRegistry&&) = delete;`
- L59 _public function_ `void SetDefaultInterfaceCustomization(TUniquePtr<CustomizationBaseType>&& InInterfaceCustomization)` — Set the default interface customization instance.
- L68 _public function_ `CustomizationBaseType* GetDefaultInterfaceCustomization() const` — Return the default interface customization instance.
- L76 _public function_ `void RegisterInterfaceCustomizationByTypeName(const FName InElementTypeName, TUniquePtr<CustomizationBaseType>&& InInterfaceCustomization)` — Register an interface customization for the given element type.
- L84 _public function_ `void RegisterInterfaceCustomizationByTypeId(const FTypedHandleTypeId InElementTypeId, TUniquePtr<CustomizationBaseType>&& InInterfaceCustomization)` — Register an interface customization for the given element type.
- L92 _public function_ `void UnregisterInterfaceCustomizationByTypeName(const FName InElementTypeName)` — Unregister an interface customization for the given element type.
- L100 _public function_ `void UnregisterInterfaceCustomizationByTypeId(const FTypedHandleTypeId InElementTypeId)` — Unregister an interface customization for the given element type.
- L109 _public function_ `CustomizationBaseType* GetInterfaceCustomizationByTypeName(const FName InElementTypeName, const bool bAllowFallback = true) const` — Get the interface customization for the given element type. @note If bAllowFallback is true, then this will return the default interface customization if no override is present, otherwise it will return null.
- L118 _public function_ `CustomizationBaseType* GetInterfaceCustomizationByTypeId(const FTypedHandleTypeId InElementTypeId, const bool bAllowFallback = true) const` — Get the interface customization for the given element type. @note If bAllowFallback is true, then this will return the default interface customization if no override is present, otherwise it will return null.
- L130 _private member_ `TUniquePtr<CustomizationBaseType> DefaultInterfaceCustomization;` — Default interface customization, used if no type-specific override is present.
- L133 _private member_ `TUniquePtr<CustomizationBaseType> RegisteredInterfaceCustomizations[TypedHandleMaxTypeId - 1];` — Array of registered interface customizations, indexed by ElementTypeId-1.

### `Source/Runtime/TypedElementRuntime/Public/Elements/Framework/TypedElementListObjectUtil.h` (Public)


#### Free symbols / members of external scopes

- L16 _namespace_ `namespace TypedElementListObjectUtil`
- L22 _prototype_ `bool HasObjects(FTypedElementListConstRef InElementList, const UClass* InRequiredClass = nullptr);` (scope `TypedElementListObjectUtil`) — Test whether there are any objects in the given list of elements.
- L28 _function_ `template <typename RequiredClassType> bool HasObjects(FTypedElementListConstRef InElementList)` (scope `TypedElementListObjectUtil`) — Test whether there are any objects in the given list of elements.
- L36 _prototype_ `int32 CountObjects(FTypedElementListConstRef InElementList, const UClass* InRequiredClass = nullptr);` (scope `TypedElementListObjectUtil`) — Count the number of objects in the given list of elements.
- L42 _function_ `template <typename RequiredClassType> int32 CountObjects(FTypedElementListConstRef InElementList)` (scope `TypedElementListObjectUtil`) — Count the number of objects in the given list of elements.
- L51 _prototype_ `void ForEachObject(FTypedElementListConstRef InElementList, TFunctionRef<bool(UObject*)> InCallback, const UClass* InRequiredClass = nullptr);` (scope `TypedElementListObjectUtil`) — Enumerate the objects from the given list of elements. @note Return true from the callback to continue enumeration.
- L58 _function_ `template <typename RequiredClassType> void ForEachObject(FTypedElementListConstRef InElementList, TFunctionRef<bool(RequiredClassType*)> InCallback)` (scope `TypedElementListObjectUtil`) — Enumerate the objects from the given list of elements. @note Return true from the callback to continue enumeration.
- L61 _function_ `` (scope `TypedElementListObjectUtil::ForEachObject`)
- L69 _prototype_ `TArray<UObject*> GetObjects(FTypedElementListConstRef InElementList, const UClass* InRequiredClass = nullptr);` (scope `TypedElementListObjectUtil`) — Get the array of objects from the given list of elements.
- L75 _function_ `template <typename RequiredClassType> TArray<RequiredClassType*> GetObjects(FTypedElementListConstRef InElementList)` (scope `TypedElementListObjectUtil`) — Get the array of objects from the given list of elements.
- L81 _function_ `` (scope `TypedElementListObjectUtil::GetObjects`)
- L92 _prototype_ `UObject* GetTopObject(FTypedElementListConstRef InElementList, const UClass* InRequiredClass = nullptr);` (scope `TypedElementListObjectUtil`) — Get the first object of the given type from the given list of elements.
- L98 _function_ `template <typename RequiredClassType> RequiredClassType* GetTopObject(FTypedElementListConstRef InElementList)` (scope `TypedElementListObjectUtil`) — Get the first object of the given type from the given list of elements.
- L106 _prototype_ `UObject* GetBottomObject(FTypedElementListConstRef InElementList, const UClass* InRequiredClass = nullptr);` (scope `TypedElementListObjectUtil`) — Get the last object of the given type from the given list of elements.
- L112 _function_ `template <typename RequiredClassType> RequiredClassType* GetBottomObject(FTypedElementListConstRef InElementList)` (scope `TypedElementListObjectUtil`) — Get the last object of the given type from the given list of elements.
- L120 _prototype_ `bool HasObjectsOfExactClass(FTypedElementListConstRef InElementList, const UClass* InClass);` (scope `TypedElementListObjectUtil`) — Test if there are any objects of the exact class in the given list of elements (a quick test using the class counter, skipping derived types).
- L126 _function_ `template <typename ClassType> bool HasObjectsOfExactClass(FTypedElementListConstRef InElementList)` (scope `TypedElementListObjectUtil`) — Test if there are any objects of the exact class in the given list of elements (a quick test using the class counter, skipping derived types).
- L134 _prototype_ `int32 CountObjectsOfExactClass(FTypedElementListConstRef InElementList, const UClass* InClass);` (scope `TypedElementListObjectUtil`) — Count the number of objects of the exact class in the given list of elements (a quick test using the class counter, skipping derived types).
- L140 _function_ `template <typename ClassType> bool CountObjectsOfExactClass(FTypedElementListConstRef InElementList)` (scope `TypedElementListObjectUtil`) — Count the number of objects of the exact class in the given list of elements (a quick test using the class counter, skipping derived types).
- L149 _prototype_ `void ForEachObjectClass(FTypedElementListConstRef InElementList, TFunctionRef<bool(UClass*)> InCallback);` (scope `TypedElementListObjectUtil`) — Enumerate the classes of the objects in the given list of elements. @note Return true from the callback to continue enumeration.

### `Source/Runtime/TypedElementRuntime/Public/Elements/Framework/TypedElementSelectionSet.h` (Public)


#### struct `FTypedElementSelectionNormalizationOptions`  
`struct FTypedElementSelectionNormalizationOptions`  
_L36-59_
- reflection: `USTRUCT(BlueprintType)`
- L41 _public function_ `FTypedElementSelectionNormalizationOptions& SetExpandGroups(const bool InExpandGroups)`
- L42 _public function_ `bool ExpandGroups() const`
- L44 _public function_ `FTypedElementSelectionNormalizationOptions& SetFollowAttachment(const bool InFollowAttachment)`
- L45 _public function_ `bool FollowAttachment() const`
- L48 _public function_ `FTypedElementSelectionNormalizationOptions& SetNameForTEDSIntegration(const FName& InTEDSIntegrationSelectionSetName)` — Set the selection set name that will be passed into the selection column in TEDS (if it is enabled)
- L49 _public function_ `FName GetNameForTEDSIntegration() const`
- L53 _private member_ `bool bExpandGroups = false;` — `UPROPERTY(BlueprintReadWrite, Category="TypedElementInterfaces|Selection|NormalizationOptions", meta=(AllowPrivateAccess=true))`
- L56 _private member_ `bool bFollowAttachment = false;` — `UPROPERTY(BlueprintReadWrite, Category="TypedElementInterfaces|Selection|NormalizationOptions", meta=(AllowPrivateAccess=true))`
- L58 _private member_ `FName TEDSIntegrationSelectionSetName = FName();`

#### class `FTypedElementSelectionCustomization`  
`class FTypedElementSelectionCustomization`  
_L65-79_
- desc: Customization type used to allow asset editors (such as the level editor) to override the base behavior of element selection, by injecting extra pre/post selection logic around the call into the selection interface for an element type.
- L68 _public prototype_ `virtual ~FTypedElementSelectionCustomization() = default;`
- L71 _public function_ `virtual bool IsElementSelected(const TTypedElement<ITypedElementSelectionInterface>& InElementSelectionHandle, FTypedElementListConstRef InSelectionSet, const FTypedElementIsSelectedOptions& InSelectionOptions)`
- L72 _public function_ `virtual bool CanSelectElement(const TTypedElement<ITypedElementSelectionInterface>& InElementSelectionHandle, const FTypedElementSelectionOptions& InSelectionOptions)`
- L73 _public function_ `virtual bool CanDeselectElement(const TTypedElement<ITypedElementSelectionInterface>& InElementSelectionHandle, const FTypedElementSelectionOptions& InSelectionOptions)`
- L74 _public function_ `virtual bool SelectElement(const TTypedElement<ITypedElementSelectionInterface>& InElementSelectionHandle, FTypedElementListRef InSelectionSet, const FTypedElementSelectionOptions& InSelectionOptions)`
- L75 _public function_ `virtual bool DeselectElement(const TTypedElement<ITypedElementSelectionInterface>& InElementSelectionHandle, FTypedElementListRef InSelectionSet, const FTypedElementSelectionOptions& InSelectionOptions)`
- L76 _public function_ `virtual bool AllowSelectionModifiers(const TTypedElement<ITypedElementSelectionInterface>& InElementSelectionHandle, FTypedElementListConstRef InSelectionSet)`
- L77 _public function_ `virtual FTypedElementHandle GetSelectionElement(const TTypedElement<ITypedElementSelectionInterface>& InElementSelectionHandle, FTypedElementListConstRef InCurrentSelection, const ETypedElementSelectionMethod InSelectionMethod)`
- L78 _public prototype_ `virtual void GetNormalizedElements(const TTypedElement<ITypedElementSelectionInterface>& InElementSelectionHandle, FTypedElementListConstRef InSelectionSet, const FTypedElementSelectionNormalizationOptions& InNormalizationOptions, FTypedElementListRef OutNormalizedElements);`

#### struct `FTypedElementSelectionSetElement`  
`struct FTypedElementSelectionSetElement`  
_L84-128_
- desc: Utility to hold a typed element handle and its associated selection interface and selection customization.
- L87 _public prototype_ `FTypedElementSelectionSetElement() = default;`
- L89 _public function_ `FTypedElementSelectionSetElement(TTypedElement<ITypedElementSelectionInterface> InElementSelectionHandle, FTypedElementListPtr InElementList, FTypedElementSelectionCustomization* InSelectionCustomization) : ElementSelectionHandle(MoveTemp(InElementSelectionHandle)) , ElementList(InElementList) , SelectionCustomization(InSelectionCustomization)`
- L96 _public prototype_ `FTypedElementSelectionSetElement(const FTypedElementSelectionSetElement&) = default;`
- L97 _public prototype_ `FTypedElementSelectionSetElement& operator=(const FTypedElementSelectionSetElement&) = default;`
- L99 _public prototype_ `FTypedElementSelectionSetElement(FTypedElementSelectionSetElement&&) = default;`
- L100 _public prototype_ `FTypedElementSelectionSetElement& operator=(FTypedElementSelectionSetElement&&) = default;`
- L102 _public function_ `inline explicit operator bool() const`
- L107 _public function_ `inline bool IsSet() const`
- L115 _public function_ `bool IsElementSelected(const FTypedElementIsSelectedOptions& InSelectionOptions) const`
- L116 _public function_ `bool CanSelectElement(const FTypedElementSelectionOptions& InSelectionOptions) const`
- L117 _public function_ `bool CanDeselectElement(const FTypedElementSelectionOptions& InSelectionOptions) const`
- L118 _public function_ `bool SelectElement(const FTypedElementSelectionOptions& InSelectionOptions) const`
- L119 _public function_ `bool DeselectElement(const FTypedElementSelectionOptions& InSelectionOptions) const`
- L120 _public function_ `bool AllowSelectionModifiers() const`
- L121 _public function_ `FTypedElementHandle GetSelectionElement(const ETypedElementSelectionMethod InSelectionMethod) const`
- L122 _public function_ `void GetNormalizedElements(const FTypedElementSelectionNormalizationOptions& InNormalizationOptions, FTypedElementListRef OutNormalizedElements) const`
- L125 _private member_ `TTypedElement<ITypedElementSelectionInterface> ElementSelectionHandle;`
- L126 _private member_ `FTypedElementListPtr ElementList;`
- L127 _private member_ `FTypedElementSelectionCustomization* SelectionCustomization = nullptr;`

#### struct `FTypedElementSelectionSetState`  
`struct FTypedElementSelectionSetState`  
_L131-172_
- reflection: `USTRUCT(BlueprintType)`
- L137 _public prototype_ `FTypedElementSelectionSetState() = default;`
- L139 _public prototype_ `FTypedElementSelectionSetState(FTypedElementSelectionSetState&&) = default;`
- L140 _public prototype_ `FTypedElementSelectionSetState& operator=(FTypedElementSelectionSetState&&) = default;`
- L142 _public function_ `FTypedElementSelectionSetState(const FTypedElementSelectionSetState& InOther) : CreatedFromSelectionSet(InOther.CreatedFromSelectionSet)`
- L152 _public function_ `FTypedElementSelectionSetState& operator=(const FTypedElementSelectionSetState& InOther)`
- L169 _private member_ `TWeakObjectPtr<const UTypedElementSelectionSet> CreatedFromSelectionSet;` — `UPROPERTY()`
- L171 _private member_ `TArray<TUniquePtr<ITypedElementTransactedElement>> TransactedElements;`

#### class `UTypedElementSelectionSet`  
`class UTypedElementSelectionSet : public UObject, public TTypedElementInterfaceCustomizationRegistry<FTypedElementSelectionCustomization>`  
_L179-709_
- reflection: `UCLASS(Transient, BlueprintType, meta=(DontUseGenericSpawnObject="True"), MinimalAPI)`
- inherits: `UObject,TTypedElementInterfaceCustomizationRegistry<FTypedElementSelectionCustomization>`
- desc: A wrapper around an element list that ensures mutation goes via the selection interfaces, as well as providing some utilities for batching operations.
- L184 _public prototype_ `UTypedElementSelectionSet();`
- L188 _public prototype_ `virtual void PreEditUndo() override;`
- L189 _public prototype_ `virtual void PostEditUndo() override;`
- L190 _public prototype_ `virtual bool Modify(bool bAlwaysMarkDirty = true) override;`
- L192 _public prototype_ `virtual void BeginDestroy() override;`
- L193 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L198 _public prototype_ `bool IsElementSelected(const FTypedElementHandle& InElementHandle, const FTypedElementIsSelectedOptions InSelectionOptions) const;` — Test to see whether the given element is currently considered selected.
- L203 _public prototype_ `bool CanSelectElement(const FTypedElementHandle& InElementHandle, const FTypedElementSelectionOptions InSelectionOptions) const;` — Test to see whether the given element can be selected.
- L208 _public prototype_ `bool CanDeselectElement(const FTypedElementHandle& InElementHandle, const FTypedElementSelectionOptions InSelectionOptions) const;` — Test to see whether the given element can be deselected.
- L214 _public prototype_ `bool SelectElement(const FTypedElementHandle& InElementHandle, FTypedElementSelectionOptions InSelectionOptions);` — Attempt to select the given element. @return True if the selection was changed, false otherwise.
- L220 _public prototype_ `bool SelectElements(const TArray<FTypedElementHandle>& InElementHandles, const FTypedElementSelectionOptions InSelectionOptions);` — Attempt to select the given elements. @return True if the selection was changed, false otherwise.
- L221 _public prototype_ `bool SelectElements(TArrayView<const FTypedElementHandle> InElementHandles, const FTypedElementSelectionOptions InSelectionOptions);`
- L222 _public prototype_ `bool SelectElements(FTypedElementListConstRef InElementList, const FTypedElementSelectionOptions InSelectionOptions);`
- L228 _public prototype_ `bool DeselectElement(const FTypedElementHandle& InElementHandle, FTypedElementSelectionOptions InSelectionOptions);` — Attempt to deselect the given element. @return True if the selection was changed, false otherwise.
- L234 _public prototype_ `bool DeselectElements(const TArray<FTypedElementHandle>& InElementHandles, const FTypedElementSelectionOptions InSelectionOptions);` — Attempt to deselect the given elements. @return True if the selection was changed, false otherwise.
- L235 _public prototype_ `bool DeselectElements(TArrayView<const FTypedElementHandle> InElementHandles, const FTypedElementSelectionOptions InSelectionOptions);`
- L236 _public prototype_ `bool DeselectElements(FTypedElementListConstRef InElementList, const FTypedElementSelectionOptions InSelectionOptions);`
- L243 _public prototype_ `bool ClearSelection(const FTypedElementSelectionOptions InSelectionOptions);` — `UFUNCTION(BlueprintCallable, Category="TypedElementFramework|Selection")` — Clear the current selection. @return True if the selection was changed, false otherwise.
- L250 _public prototype_ `bool SetSelection(const TArray<FTypedElementHandle>& InElementHandles, const FTypedElementSelectionOptions InSelectionOptions);` — Attempt to make the selection the given elements. @note Equivalent to calling ClearSelection then SelectElements, but happens in a single batch. @return True if the selection was changed, false otherwise.
- L251 _public prototype_ `bool SetSelection(TArrayView<const FTypedElementHandle> InElementHandles, const FTypedElementSelectionOptions InSelectionOptions);`
- L252 _public prototype_ `bool SetSelection(FTypedElementListConstRef InElementList, const FTypedElementSelectionOptions InSelectionOptions);`
- L257 _public prototype_ `bool AllowSelectionModifiers(const FTypedElementHandle& InElementHandle) const;` — Test to see whether selection modifiers (Ctrl or Shift) are allowed while selecting this element.
- L262 _public prototype_ `void SetNameForTedsIntegration(const FName InNameForIntegration);` — Sets the name to use for teds integration so that it can be reapplied on undo/redo
- L264 _public prototype_ `FName GetNameForTedsIntegration() const;`
- L269 _public prototype_ `FTypedElementHandle GetSelectionElement(const FTypedElementHandle& InElementHandle, const ETypedElementSelectionMethod InSelectionMethod) const;` — Given an element, return the element that should actually perform a selection operation.
- L275 _public prototype_ `FTypedElementListRef GetNormalizedSelection(const FTypedElementSelectionNormalizationOptions InNormalizationOptions) const;` — Get a normalized version of this selection set that can be used to perform operations like gizmo manipulation, deletion, copying, etc. This will do things like expand out groups, and resolve any parent<->child elements so that duplication operations aren't performed on both the parent and the child.
- L276 _public prototype_ `void GetNormalizedSelection(const FTypedElementSelectionNormalizationOptions& InNormalizationOptions, FTypedElementListRef OutNormalizedElements) const;`
- L282 _public prototype_ `FTypedElementListRef GetNormalizedElementList(FTypedElementListConstRef InElementList, const FTypedElementSelectionNormalizationOptions InNormalizationOptions) const;` — Get a normalized version of the given element list that can be used to perform operations like gizmo manipulation, deletion, copying, etc. This will do things like expand out groups, and resolve any parent<->child elements so that duplication operations aren't performed on both the parent and the child.
- L283 _public prototype_ `void GetNormalizedElementList(FTypedElementListConstRef InElementList, const FTypedElementSelectionNormalizationOptions& InNormalizationOptions, FTypedElementListRef OutNormalizedElements) const;`
- L289 _public function_ `int32 GetNumSelectedElements() const` — `UFUNCTION(BlueprintPure, Category="TypedElementFramework|Selection")` — Get the number of selected elements.
- L298 _public function_ `bool HasSelectedElements(const TSubclassOf<UInterface> InBaseInterfaceType = {}) const` — `UFUNCTION(BlueprintCallable, BlueprintPure=false, Category="TypedElementFramework|Selection")` — Test whether there selected elements, optionally filtering to elements that implement the given interface.
- L307 _public function_ `int32 CountSelectedElements(const TSubclassOf<UInterface> InBaseInterfaceType = {}) const` — `UFUNCTION(BlueprintCallable, BlueprintPure=false, Category="TypedElementFramework|Selection")` — Count the number of selected elements, optionally filtering to elements that implement the given interface.
- L315 _public function_ `TArray<FTypedElementHandle> GetSelectedElementHandles(const TSubclassOf<UInterface> InBaseInterfaceType = {}) const` — Get the handle of every selected element, optionally filtering to elements that implement the given interface.
- L324 _public function_ `template <typename ArrayAllocator> void GetSelectedElementHandles(TArray<FTypedElementHandle, ArrayAllocator>& OutArray, const TSubclassOf<UInterface>& InBaseInterfaceType = {}) const` — Get the handle of every selected element, optionally filtering to elements that implement the given interface.
- L333 _public function_ `void ForEachSelectedElementHandle(TFunctionRef<bool(const FTypedElementHandle&)> InCallback, const TSubclassOf<UInterface>& InBaseInterfaceType = {}) const` — Enumerate the handle of every selected element, optionally filtering to elements that implement the given interface. @note Return true from the callback to continue enumeration.
- L343 _public function_ `template <typename BaseInterfaceType> void ForEachSelectedElement(TFunctionRef<bool(const TTypedElement<BaseInterfaceType>&)> InCallback) const` — Enumerate the selected elements that implement the given interface. @note Return true from the callback to continue enumeration.
- L352 _public function_ `template <typename BaseInterfaceType> TTypedElement<BaseInterfaceType> GetTopSelectedElement() const` — Get the first selected element implementing the given interface.
- L362 _public function_ `template <typename BaseInterfaceType> TTypedElement<BaseInterfaceType> GetTopSelectedElement(TFunctionRef<bool (const TTypedElement<BaseInterfaceType>&)> Predicate) const` — Get the first element that implement the given interface and pass the predicate @Predicate A function that should return true when the element is desirable
- L371 _public function_ `template <typename BaseInterfaceType> TTypedElement<BaseInterfaceType> GetBottomSelectedElement() const` — Get the last selected element implementing the given interface.
- L381 _public function_ `template <typename BaseInterfaceType> TTypedElement<BaseInterfaceType> GetBottomSelectedElement(TFunctionRef<bool (const TTypedElement<BaseInterfaceType>&)> Predicate) const` — Get the last element that implement the given interface and pass the predicate. @Predicate A function that return should true when the element is desirable
- L390 _public function_ `bool HasSelectedObjects(const UClass* InRequiredClass = nullptr) const` — `UFUNCTION(BlueprintCallable, BlueprintPure=false, Category="TypedElementFramework|Selection")` — Test whether there are any selected objects.
- L399 _public function_ `template <typename RequiredClassType> bool HasSelectedObjects() const` — Test whether there are any selected objects.
- L408 _public function_ `int32 CountSelectedObjects(const UClass* InRequiredClass = nullptr) const` — `UFUNCTION(BlueprintCallable, BlueprintPure=false, Category="TypedElementFramework|Selection")` — Count the number of selected objects.
- L417 _public function_ `template <typename RequiredClassType> int32 CountSelectedObjects() const` — Count the number of selected objects.
- L426 _public function_ `TArray<UObject*> GetSelectedObjects(const UClass* InRequiredClass = nullptr) const` — `UFUNCTION(BlueprintCallable, BlueprintPure=false, Category="TypedElementFramework|Selection")` — Get the array of selected objects from the currently selected elements.
- L435 _public function_ `template <typename RequiredClassType> TArray<RequiredClassType*> GetSelectedObjects() const` — Get the array of selected objects from the currently selected elements.
- L444 _public function_ `void ForEachSelectedObject(TFunctionRef<bool(UObject*)> InCallback, const UClass* InRequiredClass = nullptr) const` — Enumerate the selected objects from the currently selected elements. @note Return true from the callback to continue enumeration.
- L454 _public function_ `template <typename RequiredClassType> void ForEachSelectedObject(TFunctionRef<bool(RequiredClassType*)> InCallback) const` — Enumerate the selected objects from the currently selected elements. @note Return true from the callback to continue enumeration.
- L463 _public function_ `UObject* GetTopSelectedObject(const UClass* InRequiredClass = nullptr) const` — `UFUNCTION(BlueprintPure, Category="TypedElementFramework|Selection")` — Get the first selected object of the given type.
- L472 _public function_ `template <typename RequiredClassType> RequiredClassType* GetTopSelectedObject() const` — Get the first selected object of the given type.
- L481 _public function_ `UObject* GetBottomSelectedObject(const UClass* InRequiredClass = nullptr) const` — `UFUNCTION(BlueprintPure, Category="TypedElementFramework|Selection")` — Get the last selected object of the given type.
- L490 _public function_ `template <typename RequiredClassType> RequiredClassType* GetBottomSelectedObject() const` — Get the last selected object of the given type.
- L499 _public prototype_ `DECLARE_EVENT_OneParam(UTypedElementSelectionSet, FOnPreChange, const UTypedElementSelectionSet* );` — Access the delegate that is invoked whenever the underlying element list is potentially about to change. @note This may be called even if no actual change happens, so may be called multiple times without a corresponding OnChanged notification.
- L500 _public function_ `FOnPreChange& OnPreChange()`
- L509 _public prototype_ `DECLARE_EVENT_OneParam(UTypedElementSelectionSet, FOnChanged, const UTypedElementSelectionSet* );` — Access the delegate that is invoked whenever the underlying element list has been changed. @note This is called automatically at the end of each frame, but can also be manually invoked by NotifyPendingChanges.
- L510 _public function_ `FOnChanged& OnChanged()`
- L518 _public function_ `void NotifyPendingChanges()` — Invoke the delegate called whenever the underlying element list has been changed.
- L526 _public function_ `FTypedElementList::FScopedClearNewPendingChange GetScopedClearNewPendingChange()` — Get a scoped object that when destroyed it clear a pending change notification without emitting the notification if it happened during its lifecycle.
- L535 _public function_ `FTypedElementList::FLegacySync& Legacy_GetElementListSync()` — Access the interface to allow external systems (such as USelection) to receive immediate sync notifications as the underlying element list is changed. This exists purely as a bridging mechanism and shouldn't be relied on for new code. It is lazily created as needed.
- L544 _public function_ `FTypedElementList::FLegacySync* Legacy_GetElementListSyncPtr()` — Access the interface to allow external systems (such as USelection) to receive immediate sync notifications as the underlying element list is changed. This exists purely as a bridging mechanism and shouldn't be relied on for new code. This will return null if no legacy sync has been created for this instance.
- L552 _public function_ `FTypedElementListConstRef GetElementList() const` — Get the underlying element list holding the selection state.
- L564 _public prototype_ `FTypedElementSelectionSetState GetCurrentSelectionState() const;` — `UFUNCTION(BlueprintPure, Category = "TypedElementFramework|Selection")` — Serializes the current selection set. The calling code is responsible for storing any state information. The selection set can be returned to a prior state using RestoreSelectionState. @returns the current state of the selection set.
- L571 _public prototype_ `void RestoreSelectionState(const FTypedElementSelectionSetState& InSelectionState);` — `UFUNCTION(BlueprintCallable, Category = "TypedElementFramework|Selection")` — Restores the selection set from the given state. The calling code is responsible for managing any undo state.
- L582 _public prototype_ `bool IsElementSelected(const FScriptTypedElementHandle& InElementHandle, const FTypedElementIsSelectedOptions InSelectionOptions) const;` — `UFUNCTION(BlueprintPure, Category="TypedElementFramework|Selection")` — Test to see whether the given element is currently considered selected.
- L588 _public prototype_ `bool CanSelectElement(const FScriptTypedElementHandle& InElementHandle, const FTypedElementSelectionOptions InSelectionOptions) const;` — `UFUNCTION(BlueprintPure, Category="TypedElementFramework|Selection")` — Test to see whether the given element can be selected.
- L594 _public prototype_ `bool CanDeselectElement(const FScriptTypedElementHandle& InElementHandle, const FTypedElementSelectionOptions InSelectionOptions) const;` — `UFUNCTION(BlueprintPure, Category="TypedElementFramework|Selection")` — Test to see whether the given element can be deselected.
- L601 _public prototype_ `bool SelectElement(const FScriptTypedElementHandle& InElementHandle, const FTypedElementSelectionOptions InSelectionOptions);` — `UFUNCTION(BlueprintCallable, Category="TypedElementFramework|Selection")` — Attempt to select the given element. @return True if the selection was changed, false otherwise.
- L608 _public prototype_ `bool SelectElements(const TArray<FScriptTypedElementHandle>& InElementHandles, const FTypedElementSelectionOptions InSelectionOptions);` — `UFUNCTION(BlueprintCallable, Category="TypedElementFramework|Selection")` — Attempt to select the given elements. @return True if the selection was changed, false otherwise.
- L615 _public prototype_ `bool DeselectElement(const FScriptTypedElementHandle& InElementHandle, const FTypedElementSelectionOptions InSelectionOptions);` — `UFUNCTION(BlueprintCallable, Category="TypedElementFramework|Selection")` — Attempt to deselect the given element. @return True if the selection was changed, false otherwise.
- L622 _public prototype_ `bool DeselectElements(const TArray<FScriptTypedElementHandle>& InElementHandles, const FTypedElementSelectionOptions InSelectionOptions);` — `UFUNCTION(BlueprintCallable, Category="TypedElementFramework|Selection")` — Attempt to deselect the given elements. @return True if the selection was changed, false otherwise.
- L630 _public prototype_ `bool SetSelection(const TArray<FScriptTypedElementHandle>& InElementHandles, const FTypedElementSelectionOptions InSelectionOptions);` — `UFUNCTION(BlueprintCallable, Category="TypedElementFramework|Selection")` — Attempt to make the selection the given elements. @note Equivalent to calling ClearSelection then SelectElements, but happens in a single batch. @return True if the selection was changed, false otherwise.
- L636 _public prototype_ `bool AllowSelectionModifiers(const FScriptTypedElementHandle& InElementHandle) const;` — `UFUNCTION(BlueprintPure, Category="TypedElementFramework|Selection")` — Test to see whether selection modifiers (Ctrl or Shift) are allowed while selecting this element.
- L642 _public prototype_ `FScriptTypedElementHandle GetSelectionElement(const FScriptTypedElementHandle& InElementHandle, const ETypedElementSelectionMethod InSelectionMethod) const;` — `UFUNCTION(BlueprintPure, Category = "TypedElementFramework|Selection")` — Given an element, return the element that should actually perform a selection operation.
- L649 _public prototype_ `TArray<FScriptTypedElementHandle> K2_GetSelectedElementHandles(const TSubclassOf<UInterface> InBaseInterfaceType = {}) const;` — `UFUNCTION(BlueprintCallable, BlueprintPure=false, DisplayName="Get Selected Element Handles", Category="TypedElementFramework|Selection", meta=(ScriptName="GetSelectedElementHandles"))` — Get the handle of every selected element, optionally filtering to elements that implement the given interface.
- L651 _public prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPreChangeDynamic, const UTypedElementSelectionSet*, SelectionSet);`
- L655 _public member_ `FOnPreChangeDynamic OnPreSelectionChange;` — `UPROPERTY(BlueprintAssignable, Category = "TypedElementFramework|Selection")` — Delegate that is invoked whenever the underlying element list is potentially about to change.
- L657 _public prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnChangeDynamic, const UTypedElementSelectionSet*, SelectionSet);`
- L661 _public member_ `FOnChangeDynamic OnSelectionChange;` — `UPROPERTY(BlueprintAssignable, Category = "TypedElementFramework|Selection")` — Delegate that is invoked whenever the underlying element list has been changed.
- L667 _private prototype_ `FTypedElementSelectionSetElement ResolveSelectionSetElement(const FTypedElementHandle& InElementHandle) const;` — Attempt to resolve the selection interface and selection customization for the given element, if any.
- L672 _private prototype_ `void OnElementReplaced(TArrayView<const TTuple<FTypedElementHandle, FTypedElementHandle>> InReplacedElements);` — Update the selection from a replacement request.
- L677 _private prototype_ `void OnElementUpdated(TArrayView<const FTypedElementHandle> InUpdatedElements);` — Force a selection update if an element internal state changes.
- L682 _private prototype_ `void OnElementListPreChange(const FTypedElementList& InElementList);` — Proxy the internal OnPreChange event from the underlying element list.
- L687 _private prototype_ `void OnElementListChanged(const FTypedElementList& InElementList);` — Proxy the internal OnChanged event from the underlying element list.
- L690 _private member_ `FTypedElementListPtr ElementList;` — Underlying element list holding the selection state.
- L693 _private member_ `FOnPreChange OnPreChangeDelegate;` — Delegate that is invoked whenever the underlying element list is potentially about to change.
- L696 _private member_ `FOnChanged OnChangedDelegate;` — Delegate that is invoked whenever the underlying element list has been changed.
- L699 _private member_ `bool bIsRestoringState = false;` — Set when we are currently restoring the selection state (eg, from an undo/redo)
- L706 _private member_ `TUniquePtr<FTypedElementSelectionSetState> PendingUndoRedoState;` — Set between a PreEditUndo->PostEditUndo call. Initially holds the state cached during PreEditUndo which is saved during Serialize, and is then replaced with the state loaded from Serialize to be applied in PostEditUndo.
- L708 _private member_ `FName ListNameForTedsIntegration;`

#### Free symbols / members of external scopes

- L499 _delegate_ `DECLARE_EVENT_OneParam(UTypedElementSelectionSet, FOnPreChange, const UTypedElementSelectionSet* );` — Access the delegate that is invoked whenever the underlying element list is potentially about to change. @note This may be called even if no actual change happens, so may be called multiple times without a corresponding OnChanged notification.
- L509 _delegate_ `DECLARE_EVENT_OneParam(UTypedElementSelectionSet, FOnChanged, const UTypedElementSelectionSet* );` — Access the delegate that is invoked whenever the underlying element list has been changed. @note This is called automatically at the end of each frame, but can also be manually invoked by NotifyPendingChanges.
- L651 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPreChangeDynamic, const UTypedElementSelectionSet*, SelectionSet);`
- L657 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnChangeDynamic, const UTypedElementSelectionSet*, SelectionSet);`

### `Source/Runtime/TypedElementRuntime/Public/Elements/Interfaces/TypedElementAssetDataInterface.h` (Public)


#### struct `FTypedElementAssetDataReferencedOptions`  
`struct FTypedElementAssetDataReferencedOptions`  
_L18-29_
- reflection: `USTRUCT(BlueprintType)`
- L23 _public function_ `FTypedElementAssetDataReferencedOptions& SetOnlyTopLevelAsset(const bool InTopLevelAsset)`
- L24 _public function_ `bool OnlyTopLevelAsset() const`
- L28 _private member_ `bool bOnlyTopLevelAsset = false;` — `UPROPERTY(BlueprintReadWrite, Category = "TypedElementInterfaces|AssetData|GetReferencedOptions", meta = (AllowPrivateAccess = true))`

#### class `UTypedElementAssetDataInterface`  
`class UTypedElementAssetDataInterface : public UInterface`  
_L32-35_
- reflection: `UINTERFACE(MinimalAPI, BlueprintType, meta = (CannotImplementInterfaceInBlueprint))`
- inherits: `UInterface`

#### class `ITypedElementAssetDataInterface`  
`class ITypedElementAssetDataInterface`  
_L37-73_
- L48 _public prototype_ `virtual TArray<FAssetData> GetAllReferencedAssetDatas(const FTypedElementHandle& InElementHandle, const FTypedElementAssetDataReferencedOptions& InOptions = FTypedElementAssetDataReferencedOptions());` — Returns any asset datas for content objects referenced by handle. If the given handle itself has valid asset data, it should be returned as the last element of the array. @returns An array of valid asset datas.
- L53 _public prototype_ `virtual FAssetData GetAssetData(const FTypedElementHandle& InElementHandle);` — Returns the asset data for the given handle, if it exists.
- L66 _public prototype_ `virtual TArray<FAssetData> GetAllReferencedAssetDatas(const FScriptTypedElementHandle& InElementHandle);` — `UFUNCTION(BlueprintCallable, Category = "TypedElementInterfaces|AssetData")` — Returns any asset datas for content objects referenced by handle. If the given handle itself has valid asset data, it should be returned as the last element of the array. @returns An array of valid asset datas.
- L72 _public prototype_ `virtual FAssetData GetAssetData(const FScriptTypedElementHandle& InElementHandle);` — `UFUNCTION(BlueprintCallable, Category = "TypedElementInterfaces|AssetData")` — Returns the asset data for the given handle, if it exists.

#### struct `TTypedElement`  
`template <> struct TTypedElement<ITypedElementAssetDataInterface> : public TTypedElementBase<ITypedElementAssetDataInterface>`  
_L76-80_
- inherits: `TTypedElementBase<ITypedElementAssetDataInterface>`
- L78 _public function_ `TArray<FAssetData> GetAllReferencedAssetDatas(const FTypedElementAssetDataReferencedOptions& InOptions = FTypedElementAssetDataReferencedOptions()) const`
- L79 _public function_ `FAssetData GetAssetData() const`

### `Source/Runtime/TypedElementRuntime/Public/Elements/Interfaces/TypedElementHierarchyInterface.h` (Public)


#### class `UTypedElementHierarchyInterface`  
`class UTypedElementHierarchyInterface : public UInterface`  
_L17-20_
- reflection: `UINTERFACE(MinimalAPI, BlueprintType, meta = (CannotImplementInterfaceInBlueprint))`
- inherits: `UInterface`

#### class `ITypedElementHierarchyInterface`  
`class ITypedElementHierarchyInterface`  
_L22-67_
- L31 _public function_ `virtual FTypedElementHandle GetParentElement(const FTypedElementHandle& InElementHandle, const bool bAllowCreate = true)` — Get the logical parent of this element, if any. eg) A component might return its actor, or a static mesh instance might return its ISM component.
- L39 _public function_ `virtual void GetChildElements(const FTypedElementHandle& InElementHandle, TArray<FTypedElementHandle>& OutElementHandles, const bool bAllowCreate = true)` — Get the logical children of this element, if any. eg) An actor might return its component, or an ISM component might return its static mesh instances. @note Appends to OutElementHandles.
- L50 _public prototype_ `virtual FScriptTypedElementHandle GetParentElement(const FScriptTypedElementHandle& InElementHandle, const bool bAllowCreate = true);` — `UFUNCTION(BlueprintCallable, Category="TypedElementInterfaces|Hierarchy")` — Get the logical parent of this element, if any. eg) A component might return its actor, or a static mesh instance might return its ISM component.
- L59 _public prototype_ `virtual void GetChildElements(const FScriptTypedElementHandle& InElementHandle, TArray<FScriptTypedElementHandle>& OutElementHandles, const bool bAllowCreate = true);` — `UFUNCTION(BlueprintCallable, Category="TypedElementInterfaces|Hierarchy")` — Get the logical children of this element, if any. eg) An actor might return its component, or an ISM component might return its static mesh instances. @note Appends to OutElementHandles.
- L66 _private prototype_ `virtual class UTypedElementRegistry& GetRegistry() const;` — Return the registry used when creating new elements.

#### struct `TTypedElement`  
`template <> struct TTypedElement<ITypedElementHierarchyInterface> : public TTypedElementBase<ITypedElementHierarchyInterface>`  
_L70-74_
- inherits: `TTypedElementBase<ITypedElementHierarchyInterface>`
- L72 _public function_ `FTypedElementHandle GetParentElement(const bool bAllowCreate = true) const`
- L73 _public function_ `void GetChildElements(TArray<FTypedElementHandle>& OutElementHandles, const bool bAllowCreate = true) const`

### `Source/Runtime/TypedElementRuntime/Public/Elements/Interfaces/TypedElementObjectInterface.h` (Public)


#### class `UTypedElementObjectInterface`  
`class UTypedElementObjectInterface : public UInterface`  
_L19-22_
- reflection: `UINTERFACE(MinimalAPI, BlueprintType, meta = (CannotImplementInterfaceInBlueprint))`
- inherits: `UInterface`

#### class `ITypedElementObjectInterface`  
`class ITypedElementObjectInterface`  
_L24-89_
- L32 _public prototype_ `virtual UObject* GetObject(const FTypedElementHandle& InElementHandle);` — Get the object instance that this handle represents, if any.
- L37 _public prototype_ `virtual UClass* GetObjectClass(const FTypedElementHandle& InElementHandle);` — Gets the object instance's class that the handle represents, if any.
- L45 _public function_ `template <class CastTo> CastTo* GetObjectAs(const FTypedElementHandle& InElementHandle)` — Attempts to cast the given handle to another class. @returns the casted object if successful, otherwise nullptr.
- L57 _public function_ `template <class CastTo = UObject> CastTo* GetObjectAs(const FTypedElementHandle& InElementHandle, TSubclassOf<CastTo> TargetClass)` — Attempts to cast the given handle to another class, if it can also be casted to TargetClass. This is intended for use in cases where the calling code may only need an actor pointer, but also wants to be sure it's a specific type of actor. @returns the casted object if successful, otherwise nullptr.
- L82 _public prototype_ `virtual UObject* GetObject(const FScriptTypedElementHandle& InElementHandle);` — `UFUNCTION(BlueprintCallable, Category="TypedElementInterfaces|Object")` — Get the object instance that this handle represents, if any.
- L88 _public prototype_ `virtual UClass* GetObjectClass(const FScriptTypedElementHandle& InElementHandle);` — `UFUNCTION(BlueprintCallable, Category = "TypedElementInterfaces|Object")` — Gets the object instance's class that the handle represents, if any.

#### struct `TTypedElement`  
`template <> struct TTypedElement<ITypedElementObjectInterface> : public TTypedElementBase<ITypedElementObjectInterface>`  
_L92-102_
- inherits: `TTypedElementBase<ITypedElementObjectInterface>`
- L94 _public function_ `UObject* GetObject() const`
- L95 _public function_ `UClass* GetObjectClass() const`
- L98 _public function_ `template <class CastTo> CastTo* GetObjectAs() const`
- L101 _public function_ `template <class CastTo> CastTo* GetObjectAs(TSubclassOf<CastTo> TargetClass) const`

### `Source/Runtime/TypedElementRuntime/Public/Elements/Interfaces/TypedElementPrimitiveCustomDataInterface.h` (Public)


#### class `UTypedElementPrimitiveCustomDataInterface`  
`class UTypedElementPrimitiveCustomDataInterface : public UInterface`  
_L11-14_
- reflection: `UINTERFACE(MinimalAPI, BlueprintType, meta = (CannotImplementInterfaceInBlueprint))`
- inherits: `UInterface`

#### class `ITypedElementPrimitiveCustomDataInterface`  
`class ITypedElementPrimitiveCustomDataInterface`  
_L20-38_
- desc: An interface for use with the TypedElement Framework which exposes Primitive CustomData for use within Materials.
- L26 _public function_ `virtual void SetCustomData(const FTypedElementHandle& InElementHandle, TArrayView<const float> CustomDataFloats, bool bMarkRenderStateDirty = false)`
- L27 _public function_ `virtual void SetCustomDataValue(const FTypedElementHandle& InElementHandle, int32 CustomDataIndex, float CustomDataValue, bool bMarkRenderStateDirty = false)`
- L33 _public prototype_ `virtual void SetCustomData(const FScriptTypedElementHandle& InElementHandle, const TArray<float>& CustomDataFloats, bool bMarkRenderStateDirty = false);` — `UFUNCTION(BlueprintCallable, Category="TypedElementInterfaces|CustomData")` — Sets all Primitive's CustomData values
- L37 _public prototype_ `virtual void SetCustomDataValue(const FScriptTypedElementHandle& InElementHandle, int32 CustomDataIndex, float CustomDataValue, bool bMarkRenderStateDirty = false);` — `UFUNCTION(BlueprintCallable, Category="TypedElementInterfaces|CustomData")` — Sets a single Primitive's CustomData value

#### struct `TTypedElement`  
`template <> struct TTypedElement<ITypedElementPrimitiveCustomDataInterface> : public TTypedElementBase<ITypedElementPrimitiveCustomDataInterface>`  
_L41-45_
- inherits: `TTypedElementBase<ITypedElementPrimitiveCustomDataInterface>`
- L43 _public function_ `void SetCustomData(TArrayView<float> CustomDataFloats, bool bMarkRenderStateDirty = false) const`
- L44 _public function_ `void SetCustomDataValue(int32 CustomDataIndex, float CustomDataValue, bool bMarkRenderStateDirty = false)`

### `Source/Runtime/TypedElementRuntime/Public/Elements/Interfaces/TypedElementSelectionInterface.h` (Public)


#### enum `ETypedElementSelectionMethod`  
`enum class ETypedElementSelectionMethod : uint8`  
_L24-32_
- reflection: `UENUM()`
- L27 _public enumerator_ `Primary` — Select the "primary" element (eg, a component would favor selecting its owner actor)
- L29 _public enumerator_ `Secondary` — Select the "secondary" element (eg, a component would favor selecting itself)
- L31 _public enumerator_ `FromSecondary` — The "secondary" element is choosing to pass back up the chain (eg. an ISM was selected, but we want to traverse back to the parent element)

#### enum `ETypedElementChildInclusionMethod`  
`enum class ETypedElementChildInclusionMethod : uint8`  
_L35-43_
- reflection: `UENUM()`
- L38 _public enumerator_ `None` — Do not include child elements
- L40 _public enumerator_ `Immediate` — Include the immediate child elements, but do not recurse
- L42 _public enumerator_ `Recursive` — Include the immediate child elements, and recurse into their children too

#### struct `FTypedElementIsSelectedOptions`  
`struct FTypedElementIsSelectedOptions`  
_L46-63_
- reflection: `USTRUCT(BlueprintType)`
- L51 _public function_ `FTypedElementIsSelectedOptions& SetAllowIndirect(const bool InAllowIndirect)`
- L52 _public function_ `bool AllowIndirect() const`
- L55 _public function_ `FTypedElementIsSelectedOptions& SetNameForTEDSIntegration(const FName& InTEDSIntegrationSelectionSetName)` — Set the selection set name that will be passed into the selection column in TEDS (if it is enabled)
- L56 _public function_ `FName GetNameForTEDSIntegration() const`
- L60 _private member_ `bool bAllowIndirect = false;` — `UPROPERTY(BlueprintReadWrite, Category="TypedElementInterfaces|Selection|IsSelectedOptions", meta=(AllowPrivateAccess=true))`
- L62 _private member_ `FName TEDSIntegrationSelectionSetName = FName();`

#### struct `FTypedElementSelectionOptions`  
`struct FTypedElementSelectionOptions`  
_L66-112_
- reflection: `USTRUCT(BlueprintType)`
- L71 _public function_ `FTypedElementSelectionOptions& SetAllowHidden(const bool InAllowHidden)`
- L72 _public function_ `bool AllowHidden() const`
- L74 _public function_ `FTypedElementSelectionOptions& SetAllowGroups(const bool InAllowGroups)`
- L75 _public function_ `bool AllowGroups() const`
- L77 _public function_ `FTypedElementSelectionOptions& SetAllowLegacyNotifications(const bool InAllowLegacyNotifications)`
- L78 _public function_ `bool AllowLegacyNotifications() const`
- L80 _public function_ `FTypedElementSelectionOptions& SetWarnIfLocked(const bool InWarnIfLocked)`
- L81 _public function_ `bool WarnIfLocked() const`
- L83 _public function_ `FTypedElementSelectionOptions& SetAllowSubRootSelection(const bool InAllowSubRootSelectioin)`
- L84 _public function_ `bool AllowSubRootSelection() const`
- L86 _public function_ `FTypedElementSelectionOptions& SetChildElementInclusionMethod(const ETypedElementChildInclusionMethod InChildElementInclusionMethod)`
- L87 _public function_ `ETypedElementChildInclusionMethod GetChildElementInclusionMethod() const`
- L90 _public function_ `FTypedElementSelectionOptions& SetNameForTEDSIntegration(const FName& InTEDSIntegrationSelectionSetName)` — Set the selection set name that will be passed into the selection column in TEDS (if it is enabled)
- L91 _public function_ `FName GetNameForTEDSIntegration() const`
- L94 _private member_ `bool bAllowHidden = false;` — `UPROPERTY(BlueprintReadWrite, Category="TypedElementInterfaces|Selection|SelectionOptions", meta=(AllowPrivateAccess=true))`
- L97 _private member_ `bool bAllowGroups = true;` — `UPROPERTY(BlueprintReadWrite, Category="TypedElementInterfaces|Selection|SelectionOptions", meta=(AllowPrivateAccess=true))`
- L100 _private member_ `bool bAllowLegacyNotifications = true;` — `UPROPERTY(BlueprintReadWrite, Category="TypedElementInterfaces|Selection|SelectionOptions", meta=(AllowPrivateAccess=true))`
- L103 _private member_ `bool bWarnIfLocked = false;` — `UPROPERTY(BlueprintReadWrite, Category="TypedElementInterfaces|Selection|SelectionOptions", meta=(AllowPrivateAccess=true))`
- L106 _private member_ `bool bAllowSubRootSelection = false;` — `UPROPERTY(BlueprintReadWrite, Category = "TypedElementInterfaces|Selection|SelectionOptions", meta = (AllowPrivateAccess = true))`
- L109 _private member_ `ETypedElementChildInclusionMethod ChildElementInclusionMethod = ETypedElementChildInclusionMethod::None;` — `UPROPERTY(BlueprintReadWrite, Category="TypedElementInterfaces|Selection|SelectionOptions", meta=(AllowPrivateAccess=true))`
- L111 _private member_ `FName TEDSIntegrationSelectionSetName = FName();`

#### class `ITypedElementTransactedElement`  
`class ITypedElementTransactedElement`  
_L114-161_
- L117 _public prototype_ `virtual ~ITypedElementTransactedElement() = default;`
- L119 _public function_ `TUniquePtr<ITypedElementTransactedElement> Clone() const`
- L126 _public function_ `FTypedElementHandle GetElement() const`
- L131 _public function_ `FTypedHandleTypeId GetElementType() const`
- L136 _public function_ `void SetElement(const FTypedElementHandle& InElementHandle)`
- L142 _public function_ `void SetElementType(const FTypedHandleTypeId InTypeId)`
- L147 _public function_ `void Serialize(FArchive& InArchive)`
- L154 _protected prototype_ `virtual TUniquePtr<ITypedElementTransactedElement> CloneImpl() const = 0;`
- L155 _protected prototype_ `virtual FTypedElementHandle GetElementImpl() const = 0;`
- L156 _protected prototype_ `virtual void SetElementImpl(const FTypedElementHandle& InElementHandle) = 0;`
- L157 _protected prototype_ `virtual void SerializeImpl(FArchive& InArchive) = 0;`
- L160 _private member_ `FTypedHandleTypeId TypeId = 0;`

#### class `UTypedElementSelectionInterface`  
`class UTypedElementSelectionInterface : public UInterface`  
_L164-167_
- reflection: `UINTERFACE(MinimalAPI, BlueprintType, meta = (CannotImplementInterfaceInBlueprint))`
- inherits: `UInterface`

#### class `ITypedElementSelectionInterface`  
`class ITypedElementSelectionInterface`  
_L169-297_
- L177 _public prototype_ `virtual bool IsElementSelected(const FTypedElementHandle& InElementHandle, const FTypedElementListConstPtr& SelectionSetPtr, const FTypedElementIsSelectedOptions& InSelectionOptions);` — Test to see whether the given element is currently considered selected.
- L182 _public function_ `virtual bool CanSelectElement(const FTypedElementHandle& InElementHandle, const FTypedElementSelectionOptions& InSelectionOptions)` — Test to see whether the given element can be selected.
- L187 _public function_ `virtual bool CanDeselectElement(const FTypedElementHandle& InElementHandle, const FTypedElementSelectionOptions& InSelectionOptions)` — Test to see whether the given element can be deselected.
- L193 _public prototype_ `virtual bool SelectElement(const FTypedElementHandle& InElementHandle, const FTypedElementListPtr& InSelectionSet, const FTypedElementSelectionOptions& InSelectionOptions);` — Attempt to select the given element. @return True if the selection was changed, false otherwise.
- L199 _public prototype_ `virtual bool DeselectElement(const FTypedElementHandle& InElementHandle, const FTypedElementListPtr& InSelectionSet, const FTypedElementSelectionOptions& InSelectionOptions);` — Attempt to deselect the given element. @return True if the selection was changed, false otherwise.
- L204 _public function_ `virtual bool AllowSelectionModifiers(const FTypedElementHandle& InElementHandle, const FTypedElementListConstPtr& InSelectionSet)` — Test to see whether selection modifiers (Ctrl or Shift) are allowed while selecting this element.
- L209 _public function_ `virtual FTypedElementHandle GetSelectionElement(const FTypedElementHandle& InElementHandle, const FTypedElementListConstPtr& InCurrentSelection, const ETypedElementSelectionMethod InSelectionMethod)` — Given an element, return the element that should actually perform a selection operation.
- L214 _public function_ `virtual bool ShouldPreventTransactions(const FTypedElementHandle& InElementHandle)` — Test to see whether the given element prevents the selection set state from being transacted for undo/redo (eg, if the element belongs to a PIE instance).
- L219 _public function_ `TUniquePtr<ITypedElementTransactedElement> CreateTransactedElement(const FTypedElementHandle& InElementHandle)` — Create a transacted element instance that can be used to save the given element for undo/redo.
- L232 _public function_ `TUniquePtr<ITypedElementTransactedElement> CreateTransactedElement(const FTypedHandleTypeId InTypeId)` — Create a transacted element instance that can be used to load an element previously saved for undo/redo.
- L251 _public prototype_ `virtual bool IsElementSelected(const FScriptTypedElementHandle& InElementHandle, const FScriptTypedElementListProxy InSelectionSet, const FTypedElementIsSelectedOptions& InSelectionOptions);` — `UFUNCTION(BlueprintCallable, Category = "TypedElementInterfaces|Selection")` — Test to see whether the given element is currently considered selected.
- L257 _public prototype_ `virtual bool CanSelectElement(const FScriptTypedElementHandle& InElementHandle, const FTypedElementSelectionOptions& InSelectionOptions);` — `UFUNCTION(BlueprintCallable, Category="TypedElementInterfaces|Selection")` — Test to see whether the given element can be selected.
- L263 _public prototype_ `virtual bool CanDeselectElement(const FScriptTypedElementHandle& InElementHandle, const FTypedElementSelectionOptions& InSelectionOptions);` — `UFUNCTION(BlueprintCallable, Category="TypedElementInterfaces|Selection")` — Test to see whether the given element can be deselected.
- L270 _public prototype_ `virtual bool SelectElement(const FScriptTypedElementHandle& InElementHandle, FScriptTypedElementListProxy InSelectionSet, const FTypedElementSelectionOptions& InSelectionOptions);` — `UFUNCTION(BlueprintCallable, Category="TypedElementInterfaces|Selection")` — Attempt to select the given element. @return True if the selection was changed, false otherwise.
- L277 _public prototype_ `virtual bool DeselectElement(const FScriptTypedElementHandle& InElementHandle, FScriptTypedElementListProxy InSelectionSet, const FTypedElementSelectionOptions& InSelectionOptions);` — `UFUNCTION(BlueprintCallable, Category="TypedElementInterfaces|Selection")` — Attempt to deselect the given element. @return True if the selection was changed, false otherwise.
- L283 _public prototype_ `virtual bool AllowSelectionModifiers(const FScriptTypedElementHandle& InElementHandle, const FScriptTypedElementListProxy InSelectionSet);` — `UFUNCTION(BlueprintCallable, Category="TypedElementInterfaces|Selection")` — Test to see whether selection modifiers (Ctrl or Shift) are allowed while selecting this element.
- L289 _public prototype_ `virtual FScriptTypedElementHandle GetSelectionElement(const FScriptTypedElementHandle& InElementHandle, const FScriptTypedElementListProxy InCurrentSelection, const ETypedElementSelectionMethod InSelectionMethod);` — `UFUNCTION(BlueprintCallable, Category="TypedElementInterfaces|Selection")` — Given an element, return the element that should actually perform a selection operation.
- L296 _protected function_ `virtual TUniquePtr<ITypedElementTransactedElement> CreateTransactedElementImpl()` — Create a transacted element instance that can be used to save/load elements of the implementation type for undo/redo. @note The instance returned from this function must have either SetElement or SetElementType called on it prior to being used.

#### struct `TTypedElement`  
`template <> struct TTypedElement<ITypedElementSelectionInterface> : public TTypedElementBase<ITypedElementSelectionInterface>`  
_L300-311_
- inherits: `TTypedElementBase<ITypedElementSelectionInterface>`
- L302 _public function_ `bool IsElementSelected(FTypedElementListConstRef InSelectionSet, const FTypedElementIsSelectedOptions& InSelectionOptions) const`
- L303 _public function_ `bool CanSelectElement(const FTypedElementSelectionOptions& InSelectionOptions) const`
- L304 _public function_ `bool CanDeselectElement(const FTypedElementSelectionOptions& InSelectionOptions) const`
- L305 _public function_ `bool SelectElement(FTypedElementListRef InSelectionSet, const FTypedElementSelectionOptions& InSelectionOptions) const`
- L306 _public function_ `bool DeselectElement(FTypedElementListRef InSelectionSet, const FTypedElementSelectionOptions& InSelectionOptions) const`
- L307 _public function_ `bool AllowSelectionModifiers(FTypedElementListConstRef InSelectionSet) const`
- L308 _public function_ `FTypedElementHandle GetSelectionElement(FTypedElementListConstRef InCurrentSelection, const ETypedElementSelectionMethod InSelectionMethod) const`
- L309 _public function_ `bool ShouldPreventTransactions() const`
- L310 _public function_ `TUniquePtr<ITypedElementTransactedElement> CreateTransactedElement() const`
