# Plugins / SceneStateBinding

- module root: `Plugins/VirtualProduction/SceneState/Source/SceneStateBinding`
- headers: 14; symbols: 190
- symbol kinds: class=2, enum=2, enumerator=24, externvar=1, function=21, macro=8, member=35, namespace=19, prototype=45, struct=28, variable=5
- PrivateDependencyModuleNames: BlueprintGraph, Engine
- PublicDependencyModuleNames: Core, CoreUObject, PropertyBindingUtils

### `Plugins/VirtualProduction/SceneState/Source/SceneStateBinding/Public/SceneStateBinding.h` (Public)


#### struct `FSceneStateBinding`  
`struct FSceneStateBinding : public FPropertyBindingBinding`  
_L13-30_
- reflection: `USTRUCT()`
- inherits: `FPropertyBindingBinding`
- desc: Represents a binding from a source property to a destination property
- L20 _public prototype_ `virtual FConstStructView GetSourceDataHandleStruct() const override;`
- L25 _public member_ `FSceneStateBindingDataHandle SourceDataHandle;` — `UPROPERTY()` — Handle to the data containing the source property
- L29 _public member_ `FSceneStateBindingDataHandle TargetDataHandle;` — `UPROPERTY()` — Handle to the data containing the target property

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API SCENESTATEBINDING_API`

### `Plugins/VirtualProduction/SceneState/Source/SceneStateBinding/Public/SceneStateBindingCollection.h` (Public)


#### struct `FSceneStateBindingCollection`  
`struct FSceneStateBindingCollection : public FPropertyBindingBindingCollection`  
_L27-105_
- reflection: `USTRUCT()`
- inherits: `FPropertyBindingBindingCollection`
- desc: Holds all the property bindings to use in execution
- L31 _public function_ `TArrayView<FSceneStateBindingDesc> GetMutableBindingDescs()`
- L36 _public function_ `TArrayView<FSceneStateBinding> GetMutableBindings()`
- L41 _public function_ `TConstArrayView<FSceneStateBinding> GetBindings() const`
- L47 _public prototype_ `FPropertyBindingPath AddBindingFunction(const UE::SceneState::FBindingFunctionInfo& InFunctionInfo, TConstArrayView<FPropertyBindingPathSegment> InSourcePathSegments, const FPropertyBindingPath& InTargetPath);`
- L51 _public prototype_ `const FSceneStateBindingDesc* FindBindingDesc(FSceneStateBindingDataHandle InDataHandle) const;` — Finds the binding desc matching the given data handle
- L54 _public prototype_ `const FSceneStateBindingResolvedReference* FindResolvedReference(const FSceneStatePropertyReference& InPropertyReference) const;` — Retrieves the resolved reference for the given property reference
- L61 _public prototype_ `uint8* ResolveProperty(const FSceneStateBindingResolvedReference& InResolvedReference, FPropertyBindingDataView InDataView) const;` — Resolves the property access for the given reference and data view @note This does not deal with recursive resolution (for cases where the reference is to another reference). Prefer using UE::SceneState::ResolveProperty instead.
- L65 _public prototype_ `virtual FPropertyBindingBinding* AddBindingInternal(const FPropertyBindingPath& InSourcePath, const FPropertyBindingPath& InTargetPath) override;`
- L66 _public prototype_ `virtual void CopyBindingsInternal(const FGuid InFromStructId, const FGuid InToStructId) override;`
- L67 _public prototype_ `virtual void RemoveBindingsInternal(TFunctionRef<bool(FPropertyBindingBinding&)> InPredicate) override;`
- L68 _public prototype_ `virtual bool HasBindingInternal(TFunctionRef<bool(const FPropertyBindingBinding&)> InPredicate) const override;`
- L69 _public prototype_ `virtual const FPropertyBindingBinding* FindBindingInternal(TFunctionRef<bool(const FPropertyBindingBinding&)> InPredicate) const override;`
- L71 _public prototype_ `virtual int32 GetNumBindings() const override;`
- L72 _public prototype_ `virtual int32 GetNumBindableStructDescriptors() const override;`
- L73 _public prototype_ `virtual const FPropertyBindingBindableStructDescriptor* GetBindableStructDescriptorFromHandle(FConstStructView InSourceHandleView) const override;`
- L74 _public prototype_ `virtual void ForEachBinding(TFunctionRef<void(const FPropertyBindingBinding& Binding)> InFunction) const override;`
- L75 _public prototype_ `virtual void ForEachBinding(FPropertyBindingIndex16 InBegin, FPropertyBindingIndex16 InEnd, TFunctionRef<void(const FPropertyBindingBinding& Binding, const int32 BindingIndex)> InFunction) const override;`
- L76 _public prototype_ `virtual void ForEachMutableBinding(TFunctionRef<void(FPropertyBindingBinding& Binding)> InFunction) override;`
- L77 _public prototype_ `virtual void VisitBindings(TFunctionRef<EVisitResult(const FPropertyBindingBinding& Binding)> InFunction) const override;`
- L78 _public prototype_ `virtual void VisitBindings(FPropertyBindingIndex16 InBegin, FPropertyBindingIndex16 InEnd, TFunctionRef<EVisitResult(const FPropertyBindingBinding& Binding, const int32 BindingIndex)> InFunction) const override;`
- L79 _public prototype_ `virtual void VisitMutableBindings(TFunctionRef<EVisitResult(FPropertyBindingBinding& Binding)> InFunction) override;`
- L80 _public prototype_ `virtual void OnReset() override;`
- L81 _public prototype_ `virtual void VisitSourceStructDescriptorInternal(TFunctionRef<EVisitResult(const FPropertyBindingBindableStructDescriptor&)> InFunction) const override;`
- L82 _public prototype_ `[[nodiscard]] virtual bool OnResolvingPaths() override;`
- L87 _private member_ `TArray<FSceneStateBindingDesc> BindingDescs;` — `UPROPERTY()`
- L91 _private member_ `TArray<FSceneStateBinding> Bindings;` — `UPROPERTY()` — Contains all the bindings from a source data to a target data
- L98 _private member_ `TArray<FSceneStateBindingReference> References;` — `UPROPERTY()` — Contains all the reference bindings from a source data. This gets set and populated during scene state compilation.
- L102 _private member_ `TArray<FSceneStateBindingResolvedReference> ResolvedReferences;` — `UPROPERTY()` — Contains the references that have been resolved for use at runtime

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API SCENESTATEBINDING_API`
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace SceneState` (scope `UE`)
- L19 _namespace_ `namespace Editor` (scope `UE::SceneState`)

### `Plugins/VirtualProduction/SceneState/Source/SceneStateBinding/Public/SceneStateBindingCollectionOwner.h` (Public)


#### class `USceneStateBindingCollectionOwner`  
`class USceneStateBindingCollectionOwner : public UPropertyBindingBindingCollectionOwner`  
_L19-22_
- reflection: `UINTERFACE(MinimalAPI, meta=(CannotImplementInterfaceInBlueprint))`
- inherits: `UPropertyBindingBindingCollectionOwner`

#### class `ISceneStateBindingCollectionOwner`  
`class ISceneStateBindingCollectionOwner : public IPropertyBindingBindingCollectionOwner`  
_L24-39_
- inherits: `IPropertyBindingBindingCollectionOwner`
- L30 _public prototype_ `virtual FSceneStateBindingCollection& GetBindingCollection() = 0;` — Gets a reference to the binding collection (mutable) that the owner has
- L33 _public prototype_ `virtual const FSceneStateBindingCollection& GetBindingCollection() const = 0;` — Gets a reference to the binding collection that the owner has
- L37 _public prototype_ `virtual bool ForEachBindableFunction(TFunctionRef<bool(const FSceneStateBindingDesc&, const UE::SceneState::FBindingFunctionInfo&)> InFunc) const = 0;` — Iterates all functions that can be created and bound

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace SceneState` (scope `UE`)

### `Plugins/VirtualProduction/SceneState/Source/SceneStateBinding/Public/SceneStateBindingDataHandle.h` (Public)


#### enum `ESceneStateDataType`  
`enum class ESceneStateDataType : uint8`  
_L10-20_
- reflection: `UENUM()`
- L12 _public enumerator_ `Root`
- L13 _public enumerator_ `Task`
- L14 _public enumerator_ `EventHandler`
- L15 _public enumerator_ `TaskExtension`
- L16 _public enumerator_ `StateMachine`
- L17 _public enumerator_ `Transition`
- L18 _public enumerator_ `Function`
- L19 _public enumerator_ `State`

#### struct `FSceneStateBindingDataHandle`  
`struct FSceneStateBindingDataHandle`  
_L23-117_
- reflection: `USTRUCT()`
- L27 _public prototype_ `FSceneStateBindingDataHandle() = default;`
- L35 _public prototype_ `static FSceneStateBindingDataHandle MakeExternalDataHandle(const FExternalData& InExternalData);`
- L37 _public function_ `explicit FSceneStateBindingDataHandle(ESceneStateDataType InDataType, int32 InDataIndex = INDEX_NONE, int32 InDataSubIndex = INDEX_NONE) : Type(static_cast<uint16>(InDataType)) , Index(GetIndexSafeChecked(InDataIndex)) , SubIndex(GetIndexSafeChecked(InDataSubIndex))`
- L44 _public function_ `bool operator==(const FSceneStateBindingDataHandle& InOther) const`
- L49 _public function_ `bool IsValid() const`
- L54 _public function_ `bool IsExternalDataType() const`
- L59 _public function_ `bool IsDataType(ESceneStateDataType InDataType) const`
- L64 _public function_ `uint8 GetDataType() const`
- L71 _public function_ `uint16 GetDataIndex() const`
- L76 _public function_ `uint16 GetDataSubIndex() const`
- L81 _public function_ `uint64 AsNumber() const`
- L95 _private member_ `static constexpr uint16 InvalidIndex = std::numeric_limits<uint16>::max();`
- L97 _private function_ `static uint16 GetIndexSafeChecked(int32 InIndex)`
- L108 _private member_ `uint16 Type = InvalidIndex;` — `UPROPERTY()` — The Data Type. The first 8 bits are reserved for Internal Data Types (see ESceneStateDataType) The last 8 bits can be used to represent External Data Types (tracked by external implementations)
- L112 _private member_ `uint16 Index = InvalidIndex;` — `UPROPERTY()` — Primary Index to access the data
- L116 _private member_ `uint16 SubIndex = InvalidIndex;` — `UPROPERTY()` — Secondary Index to the actual data residing somewhere within the data from the Primary Index

#### struct `FSceneStateBindingDataHandle::FExternalData`  
`struct FExternalData`  
_L29-34_
- L31 _public member_ `uint8 Type = 0;`
- L32 _public member_ `int32 Index = INDEX_NONE;`
- L33 _public member_ `int32 SubIndex = INDEX_NONE;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API SCENESTATEBINDING_API`
- L86 _function_ `friend uint32 GetTypeHash(const FSceneStateBindingDataHandle& InDataHandle)`

### `Plugins/VirtualProduction/SceneState/Source/SceneStateBinding/Public/SceneStateBindingDelegates.h` (Public)


#### struct `UE::SceneState::FStructIdChange`  
`struct FStructIdChange`  
_L17-23_
- L20 _public member_ `TObjectPtr<UObject> BindingOwner;` — Owner of the binding collection
- L22 _public member_ `TMap<FGuid, FGuid> OldToNewStructIdMap;` — Map of the old struct id to the new id

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API SCENESTATEBINDING_API`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace SceneState` (scope `UE`)
- L25 _externvar_ `extern TMulticastDelegate<void(const FStructIdChange&)> OnStructIdChanged;` (scope `UE::SceneState`) — Delegate called when a struct id has changed

### `Plugins/VirtualProduction/SceneState/Source/SceneStateBinding/Public/SceneStateBindingDesc.h` (Public)


#### struct `FSceneStateBindingDesc`  
`struct FSceneStateBindingDesc : public FPropertyBindingBindableStructDescriptor`  
_L10-32_
- reflection: `USTRUCT()`
- inherits: `FPropertyBindingBindableStructDescriptor`
- L14 _public prototype_ `FSceneStateBindingDesc() = default;`
- L17 _public function_ `explicit FSceneStateBindingDesc(const FName InName, const UStruct* InStruct, const FGuid InGuid, const FSceneStateBindingDataHandle& InDataHandle) : Super(InName, InStruct, InGuid) , DataHandle(InDataHandle)`
- L25 _public member_ `FSceneStateBindingDataHandle DataHandle;` — `UPROPERTY()`
- L30 _public member_ `FText Section;` — `UPROPERTY()` — Section of the bindable struct. Can be used to group bindable structs within the same category menu.

### `Plugins/VirtualProduction/SceneState/Source/SceneStateBinding/Public/SceneStateBindingFunction.h` (Public)


#### struct `UE::SceneState::FBindingFunctionInfo`  
`struct FBindingFunctionInfo`  
_L16-22_
- desc: Arguments to create a valid FSceneStateBindingFunction
- L19 _public member_ `FConstStructView FunctionTemplate;` — Info to create a new function. Struct type is required. The struct memory is optional and only used as a template to instantiate the function
- L21 _public member_ `FConstStructView InstanceTemplate;` — Info to create a new function instance. Struct type is required. The struct memory is optional and only used as a template to instantiate the function instance

#### struct `FSceneStateBindingFunction`  
`struct FSceneStateBindingFunction`  
_L29-56_
- reflection: `USTRUCT()`
- desc: Holds a function object and its template instance data for compilation. Used in editor only
- L33 _public prototype_ `FSceneStateBindingFunction() = default;`
- L37 _public prototype_ `explicit FSceneStateBindingFunction(const UE::SceneState::FBindingFunctionInfo& InFunctionInfo);` — Initializes the binding function with the given function info
- L40 _public prototype_ `bool IsValid() const;` — Returns whether this object has a valid function and function instance
- L46 _public member_ `FGuid FunctionId;` — `UPROPERTY(VisibleAnywhere, Category="Scene State")` — Id of the function
- L50 _public member_ `FInstancedStruct Function;` — `UPROPERTY(EditAnywhere, Category="Scene State")` — The function template
- L54 _public member_ `mutable FInstancedStruct FunctionInstance;` — `UPROPERTY(EditAnywhere, Category="Scene State")` — The function instance template

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API SCENESTATEBINDING_API`
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace SceneState` (scope `UE`)

### `Plugins/VirtualProduction/SceneState/Source/SceneStateBinding/Public/SceneStateBindingMetadata.h` (Public)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace SceneState` (scope `UE`)
- L7 _namespace_ `namespace Metadata` (scope `UE::SceneState`)
- L14 _variable_ `const FLazyName NoBindingSelfOnly(TEXT("NoBi` (scope `UE::SceneState::Metadata`) — Describes that the property does not allow binding. But this no binding policy does not propagate to its child properties For containers, this policy would apply for both the container and inner properties.
- L22 _variable_ `const FLazyName NoBindingContainerSelfOnly(TEXT("NoBi` (scope `UE::SceneState::Metadata`) — Version of 'NoBindingSelfOnly' where it applies the no binding policy to the container property only, and not its inner properties E.g. for a TArray<FVector> property: If 'NoBindingSelfOnly' is used, both the array as a whole and its FVector inner property would be unbindable and only the FVector's individual components (X, Y, Z) would be bindable. If 'NoBindingContainerSelfOnly' is used, the array would still be non-bindable, but the FVector inner property would now be bindable.

### `Plugins/VirtualProduction/SceneState/Source/SceneStateBinding/Public/SceneStateBindingReference.h` (Public)


#### struct `FSceneStateBindingReference`  
`struct FSceneStateBindingReference`  
_L10-21_
- reflection: `USTRUCT()`
- L16 _public member_ `FPropertyBindingPath SourcePropertyPath;` — `UPROPERTY()` — Source property path of the reference
- L20 _public member_ `FSceneStateBindingDataHandle SourceDataHandle;` — `UPROPERTY()` — Describes how to get the source data pointer

#### struct `FSceneStateBindingResolvedReference`  
`struct FSceneStateBindingResolvedReference`  
_L25-43_
- reflection: `USTRUCT()`
- desc: A resolved FSceneStateReference that contains more information about the source
- L31 _public member_ `FPropertyBindingPropertyIndirection SourceIndirection;` — `UPROPERTY()` — Source property access.
- L34 _public member_ `const FProperty* SourceLeafProperty = nullptr;` — Cached pointer to the leaf property of the access.
- L38 _public member_ `TObjectPtr<const UStruct> SourceStructType = nullptr;` — `UPROPERTY(Transient)` — Type of the source data, used for validation.
- L42 _public member_ `FSceneStateBindingDataHandle SourceDataHandle;` — `UPROPERTY()` — Describes how to get the source data pointer.

### `Plugins/VirtualProduction/SceneState/Source/SceneStateBinding/Public/SceneStateBindingUtils.h` (Public)


#### struct `UE::SceneState::FPatchBindingParams`  
`struct FPatchBindingParams`  
_L29-35_
- L32 _public member_ `FSceneStateBindingCollection& BindingCollection;` — Binding collection to patch
- L34 _public member_ `TFunctionRef<const UStruct*(const FSceneStateBindingDataHandle&)> FindDataStructFunctor;` — Functor to find the data struct for a given Data Handle

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API SCENESTATEBINDING_API`
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace SceneState` (scope `UE`)
- L26 _prototype_ `void HandleStructIdChanged(UObject& InObject, const FGuid& InOldStructId, const FGuid& InNewStructId);` (scope `UE::SceneState`) — Update the bindings of a source struct id into a target one. It goes through the given object's outer chain to get to the binding collection owner to do this operation @param InObject object to use to find the binding collection owner @param InOldStructId the struct id to queue copy bindings from @param InNewStructId the struct id to queue copy bindings to
- L37 _prototype_ `void PatchBindingCollection(const FPatchBindingParams& InParams);` (scope `UE::SceneState`) — Patches invalidated structs (property bags, user defined structs, etc.) in the given binding collection
- L40 _prototype_ `void PatchBindingDescs(const FPatchBindingParams& InParams);` (scope `UE::SceneState`) — Patches any invalidated structs (property bags, user defined structs, etc.) in the binding descs of the given binding collection
- L43 _prototype_ `void PatchBindings(const FPatchBindingParams& InParams);` (scope `UE::SceneState`) — Patches any invalidated structs (property bags, user defined structs, etc.) in the bindings of the given binding collection
- L46 _prototype_ `void PatchCopyBatches(const FPatchBindingParams& InParams);` (scope `UE::SceneState`) — Patches any invalidated structs (property bags, user defined structs, etc.) in the copy batches of the given binding collection

### `Plugins/VirtualProduction/SceneState/Source/SceneStateBinding/Public/SceneStateBlueprintPropertyReference.h` (Public)


#### enum `ESceneStatePropertyReferenceType`  
`enum class ESceneStatePropertyReferenceType : uint8`  
_L15-33_
- reflection: `UENUM()`
- L17 _public enumerator_ `None UMETA(Hidden)`
- L18 _public enumerator_ `Bool UMETA(RefType="bool")`
- L19 _public enumerator_ `Byte UMETA(RefType="byte")`
- L20 _public enumerator_ `Int32 UMETA(RefType="int32")`
- L21 _public enumerator_ `Int64 UMETA(RefType="int64")`
- L22 _public enumerator_ `Float UMETA(RefType="float")`
- L23 _public enumerator_ `Double UMETA(RefType="double")`
- L24 _public enumerator_ `Name UMETA(RefType="Name")`
- L25 _public enumerator_ `String UMETA(RefType="String")`
- L26 _public enumerator_ `Text UMETA(RefType="Text")`
- L27 _public enumerator_ `Enum UMETA(ObjectRef)`
- L28 _public enumerator_ `Struct UMETA(ObjectRef)`
- L29 _public enumerator_ `Object UMETA(ObjectRef)`
- L30 _public enumerator_ `SoftObject UMETA(ObjectRef)`
- L31 _public enumerator_ `Class UMETA(ObjectRef)`
- L32 _public enumerator_ `SoftClass UMETA(ObjectRef)`

#### struct `FSceneStateBlueprintPropertyReference`  
`struct FSceneStateBlueprintPropertyReference : public FSceneStatePropertyReference`  
_L37-88_
- reflection: `USTRUCT(BlueprintType, DisplayName="Scene State Property Reference")`
- inherits: `FSceneStatePropertyReference`
- desc: Property Reference as a Blueprint Type. Usable in blueprints (e.g. tasks) and parameters
- L43 _public prototype_ `static FSceneStateBlueprintPropertyReference BuildFromPinType(const FEdGraphPinType& InPinType);` — Builds a property reference instance based on the given pin type
- L47 _public function_ `ESceneStatePropertyReferenceType GetReferenceType() const` — Returns the property reference's type
- L53 _public function_ `bool IsReferenceToArray() const` — Returns true if referenced property is an array.
- L59 _public function_ `UObject* GetTypeObject() const` — Returns selected ScriptStruct, Class or Enum.
- L64 _public function_ `bool operator==(const FSceneStateBlueprintPropertyReference& InOther) const`
- L72 _public prototype_ `static FName GetReferenceTypeMemberName();` — Get Property Member Name functions
- L73 _public prototype_ `static FName GetIsReferenceToArrayMemberName();`
- L74 _public prototype_ `static FName GetTypeObjectMemberName();`
- L79 _private member_ `ESceneStatePropertyReferenceType ReferenceType = ESceneStatePropertyReferenceType::None;` — `UPROPERTY(EditAnywhere, Category="Reference Type")` — Specifies the type of property to reference
- L83 _private member_ `bool bIsReferenceToArray = false;` — `UPROPERTY(EditAnywhere, Category="Reference Type")` — If specified, the reference is to an TArray<RefType>
- L87 _private member_ `TObjectPtr<UObject> TypeObject = nullptr;` — `UPROPERTY(EditAnywhere, Category="Reference Type")` — Specifies the type of property to reference together with ReferenceType, used for Enums, Structs, Objects and Classes.

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API SCENESTATEBINDING_API`

### `Plugins/VirtualProduction/SceneState/Source/SceneStateBinding/Public/SceneStatePropertyReference.h` (Public)


#### struct `FSceneStatePropertyReference`  
`struct FSceneStatePropertyReference`  
_L31-46_
- reflection: `USTRUCT()`
- desc: Property References allows the binding system to handle a property by reference rather than by copy. A reference holds a single 'ReferenceIndex' that points to the index of both a 'Reference' and its 'Resolved Reference'. To get the property by reference, the binding collection (to get the data handle) and the execution context (to get the data view) are required. @see FSceneStateBindingCollection, FSceneStateBindingReference, FSceneStateBindingResolvedReference. This is useful for tasks that need to write to external properties (e.g. as a form of output). The expected type of the reference should be set in "RefType" meta specifier. Meta specifiers for the type: RefType="<type>" Specifies the type of property that the reference supports. Supported types are: bool, byte, int32, int64, float, double, Name, String, Text, Wildcard, UObject pointers, and structs. Wildcards is a 'bypass' so that any valid FProperty is accepted, and is up to implementer to handle this. Structs and Objects must use full path name. (e.g. for Actor type "/Script/Engine.Actor") IsRefToArray Specified to mean that the reference is to an TArray<RefType> CanRefToArray Specified to mean that the reference can bind to a RefType or TArray<RefType>
- L36 _public member_ `static constexpr uint16 IndexCapacity = std::numeric_limits<uint16>::max();` — Max number of indices that can be used
- L39 _public function_ `bool IsValidIndex() const` — Returns whether the index is a valid index. Does not guarantee that the reference itself is to a valid property
- L45 _public member_ `uint16 ReferenceIndex = IndexCapacity;` — `UPROPERTY()`

### `Plugins/VirtualProduction/SceneState/Source/SceneStateBinding/Public/SceneStatePropertyReferenceMetadata.h` (Public)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace SceneState` (scope `UE`)
- L7 _namespace_ `namespace Metadata` (scope `UE::SceneState`)
- L10 _variable_ `const FLazyName IsRefToArray(TEXT("IsRe` (scope `UE::SceneState::Metadata`)
- L11 _variable_ `const FLazyName CanRefToArray(TEXT("CanR` (scope `UE::SceneState::Metadata`)
- L12 _variable_ `const FLazyName RefType(TEXT("RefT` (scope `UE::SceneState::Metadata`)

### `Plugins/VirtualProduction/SceneState/Source/SceneStateBinding/Public/SceneStatePropertyReferenceUtils.h` (Public)


#### struct `UE::SceneState::TDataTypeHelper`  
`template<class InDataType> struct TDataTypeHelper`  
_L36-38_
- L43 _public function_ `static bool IsValid(const FProperty* InProperty)`

#### struct `UE::SceneState::TDataTypeHelper`  
`template<> struct TDataTypeHelper<void>`  
_L41-47_
- L43 _public function_ `static bool IsValid(const FProperty* InProperty)`

#### struct `UE::SceneState::TDataTypeHelper`  
`template<> struct TDataTypeHelper<FBoolProperty::TCppType>`  
_L50-56_
- L43 _public function_ `static bool IsValid(const FProperty* InProperty)`

#### struct `UE::SceneState::TDataTypeHelper`  
`template<> struct TDataTypeHelper<FByteProperty::TCppType>`  
_L59-65_
- L43 _public function_ `static bool IsValid(const FProperty* InProperty)`

#### struct `UE::SceneState::TDataTypeHelper`  
`template<> struct TDataTypeHelper<FIntProperty::TCppType>`  
_L68-74_
- L43 _public function_ `static bool IsValid(const FProperty* InProperty)`

#### struct `UE::SceneState::TDataTypeHelper`  
`template<> struct TDataTypeHelper<FInt64Property::TCppType>`  
_L77-83_
- L43 _public function_ `static bool IsValid(const FProperty* InProperty)`

#### struct `UE::SceneState::TDataTypeHelper`  
`template<> struct TDataTypeHelper<FFloatProperty::TCppType>`  
_L86-92_
- L43 _public function_ `static bool IsValid(const FProperty* InProperty)`

#### struct `UE::SceneState::TDataTypeHelper`  
`template<> struct TDataTypeHelper<FDoubleProperty::TCppType>`  
_L95-101_
- L43 _public function_ `static bool IsValid(const FProperty* InProperty)`

#### struct `UE::SceneState::TDataTypeHelper`  
`template<> struct TDataTypeHelper<FNameProperty::TCppType>`  
_L104-110_
- L43 _public function_ `static bool IsValid(const FProperty* InProperty)`

#### struct `UE::SceneState::TDataTypeHelper`  
`template<> struct TDataTypeHelper<FStrProperty::TCppType>`  
_L113-119_
- L43 _public function_ `static bool IsValid(const FProperty* InProperty)`

#### struct `UE::SceneState::TDataTypeHelper`  
`template<> struct TDataTypeHelper<FTextProperty::TCppType>`  
_L122-128_
- L43 _public function_ `static bool IsValid(const FProperty* InProperty)`

#### struct `UE::SceneState::TDataTypeHelper`  
`template<class InDataType UE_REQUIRES(TIsTArray_V<InDataType>)> struct TDataTypeHelper<InDataType>`  
_L131-138_
- L43 _public function_ `static bool IsValid(const FProperty* InProperty)`

#### struct `UE::SceneState::TDataTypeHelper`  
`template<class InDataType UE_REQUIRES(TModels_V<CBaseStructureProvider, InDataType>)> struct TDataTypeHelper<InDataType>`  
_L141-148_
- L43 _public function_ `static bool IsValid(const FProperty* InProperty)`

#### struct `UE::SceneState::TDataTypeHelper`  
`template<class InDataType UE_REQUIRES(TModels_V<CStaticClassProvider, typename TRemovePointer<InDataType>::Type>)> struct TDataTypeHelper<InDataType>`  
_L151-158_
- L43 _public function_ `static bool IsValid(const FProperty* InProperty)`

#### struct `UE::SceneState::TDataTypeHelper`  
`template<class InDataType UE_REQUIRES(TIsEnum<InDataType>::Value)> struct TDataTypeHelper<InDataType>`  
_L161-168_
- L43 _public function_ `static bool IsValid(const FProperty* InProperty)`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API SCENESTATEBINDING_API`
- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace SceneState` (scope `UE`)
- L19 _prototype_ `bool IsPropertyReference(const FProperty* InProperty);` (scope `UE::SceneState`) — Returns whether the given property is a struct property of struct FSceneStatePropertyReference
- L23 _prototype_ `bool IsPropertyReferenceCompatible(const FProperty* InReferenceProperty, const void* InReferenceAddress, const FProperty* InSourceProperty, const void* InSourceAddress);` (scope `UE::SceneState`) — Returns whether a source property is compatible with the reference property
- L26 _prototype_ `FEdGraphPinType GetPropertyReferencePinType(const FProperty* InProperty, const void* InReferenceAddress);` (scope `UE::SceneState`) — Returns the first graph pin type based on a given Property Reference property's meta-data
- L29 _prototype_ `TArray<FEdGraphPinType, TInlineAllocator<1>> GetPropertyReferencePinTypes(const FSceneStateBlueprintPropertyReference& InPropertyReference);` (scope `UE::SceneState`) — Returns the graph pin type based on a given Property Reference
- L32 _prototype_ `TArray<FEdGraphPinType, TInlineAllocator<1>> GetPropertyReferencePinTypes(const FProperty* InProperty, const void* InReferenceAddress);` (scope `UE::SceneState`) — Returns the graph pin types based on a given Property Reference property's meta-data
