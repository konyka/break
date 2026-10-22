# Runtime / CoreUObject (part 2/2)

### `Source/Runtime/CoreUObject/Public/UObject/UnrealType.h` (Public)


#### enum `UE::CoreUObject::Private::ENonNullableBehavior`  
`enum class ENonNullableBehavior`  
_L91-96_
- L93 _public enumerator_ `LogWarning = 0`
- L94 _public enumerator_ `LogError = 1`
- L95 _public enumerator_ `CreateDefaultObjectIfPossible = 2`

#### enum `EPropertyExportCPPFlags`  
`enum EPropertyExportCPPFlags`  
_L105-127_
- L108 _public enumerator_ `CPPF_None = 0x00000000` — Indicates that there are no special C++ export flags
- L110 _public enumerator_ `CPPF_OptionalValue = 0x00000001` — Indicates that we are exporting this property's CPP text for an optional parameter value
- L112 _public enumerator_ `CPPF_ArgumentOrReturnValue = 0x00000002` — Indicates that we are exporting this property's CPP text for an argument or return value
- L114 _public enumerator_ `CPPF_Implementation = 0x00000004` — Indicates thet we are exporting this property's CPP text for C++ definition of a function.
- L116 _public enumerator_ `CPPF_CustomTypeName = 0x00000008` — Indicates that we are exporting this property's CPP text with an custom type name
- L118 _public enumerator_ `CPPF_NoConst = 0x00000010` — No 'const' keyword
- L120 _public enumerator_ `CPPF_NoRef = 0x00000020` — No reference '&' sign
- L122 _public enumerator_ `CPPF_NoStaticArray = 0x00000040` — No static array [%d]
- L124 _public enumerator_ `CPPF_BlueprintCppBackend = 0x00000080` — Blueprint compiler generated C++ code
- L126 _public enumerator_ `CPPF_NoTObjectPtr = 0x00000100` — Indicates to not use TObjectPtr but use USomething* instead

#### enum `EConvertFromTypeResult`  
`enum class EConvertFromTypeResult`  
_L129-139_
- L132 _public enumerator_ `UseSerializeItem` — No conversion was performed. Use SerializeItem to serialize the property value.
- L134 _public enumerator_ `Serialized` — No conversion was performed. The property value was serialized. Skip SerializeItem.
- L136 _public enumerator_ `CannotConvert` — No conversion is possible. Skip SerializeItem.
- L138 _public enumerator_ `Converted` — Conversion of the property value was performed. Skip SerializeItem.

#### enum `EPropertyMemoryAccess`  
`enum class EPropertyMemoryAccess : uint8`  
_L141-149_
- L144 _public enumerator_ `Direct` — Direct memory access - the associated pointer points to the memory at the reflected item.
- L148 _public enumerator_ `InContainer` — Container access - the associated pointer points to the outer of the reflected item. Access via containers will use getter and setters, if present.

#### enum `EPropertyPointerType`  
`enum class EPropertyPointerType`  
_L155-159_
- desc: Type of pointer provided for property API functions
- L157 _public enumerator_ `Direct = 0`
- L158 _public enumerator_ `Container = 1` — Direct = 0,   Raw property access

#### class `FProperty`  
`class FProperty : public FField`  
_L173-1370_
- inherits: `FField`
- desc: An UnrealScript variable.
- L180 _private member_ `int32 ElementSize;` — `UE_DEPRECATED(5.5, "Use GetElementSize/SetElementSize instead.")`
- L182 _public member_ `EPropertyFlags PropertyFlags;`
- L183 _public member_ `uint16 RepIndex;`
- L186 _private member_ `TEnumAsByte<ELifetimeCondition> BlueprintReplicationCondition;`
- L207 _private member_ `int32 Offset_Internal;` — In memory variables (generated during Link()). When UE_WITH_CONSTINIT_UOBJECT is set, this is set at compile time for compiled-in objects.
- L211 _public member_ `FProperty* PropertyLinkNext = nullptr;` — In memory only: Linked list of properties from most-derived to base
- L238 _public member_ `FProperty* PostConstructLinkNext = nullptr;` — In memory only: Linked list of properties requiring post constructor initialization.
- L240 _public member_ `FName RepNotifyFunc;`
- L244 _public prototype_ `FProperty(FFieldVariant InOwner, const FName& InName);` — Constructors.
- L246 _public function_ `FProperty(FFieldVariant InOwner, const FName& InName, EObjectFlags InObjectFlags) : FProperty(InOwner, InName)` — `UE_DEPRECATED(5.8, "FProperty constructor with InObjectFlags is deprecated, remove that parameter.")`
- L253 _public prototype_ `FProperty(FFieldVariant InOwner, const UECodeGen_Private::FPropertyParamsBaseWithOffset& Prop, EPropertyFlags AdditionalPropertyFlags = CPF_None);` — Constructor used for constructing compiled-in properties @param InOwner Owner of the property @param PropBase Pointer to the compiled in structure describing the property
- L260 _public prototype_ `FProperty(FFieldVariant InOwner, const UECodeGen_Private::FPropertyParamsBaseWithoutOffset& Prop, EPropertyFlags AdditionalPropertyFlags = CPF_None);` — Constructor used for constructing compiled-in properties @param InOwner Owner of the property @param PropBase Pointer to the compiled in structure describing the property
- L264 _public function_ `explicit consteval FProperty(UE::CodeGen::ConstInit::FPropertyParams InParams) : Super(ConstEval, InParams.Owner, InParams.NextProperty, InParams.NameUTF8) , ArrayDim(InParams.ArrayDim) , ElementSize(InParams.ElementSize) , PropertyFlags(InParams.PropertyFlags) , RepIndex(0) , BlueprintReplicationCondition() #if WITH_METADATA , NumMetaDataParams(InParams.MetaData.Num()) #endif , Offset_Internal(InParams.Offset) , PropertyLinkNext(nullptr) #if WITH_METADATA , MetaDataParams(InParams.MetaData.GetData()) #endif , RepNotifyFuncNameUTF8(InParams.RepNotifyFuncUTF8)`
- L283 _public prototype_ `void InitializeConstInitProperty(UStruct* InStructOwner);`
- L284 _public prototype_ `void InitializeConstInitProperty(FProperty* InPropertyOwner);`
- L288 _public prototype_ `explicit FProperty(UField* InField);`
- L292 _public prototype_ `void SetElementSize(int32 NewSize);` — ElementSize accessors to facilitate underlying type change
- L293 _public function_ `int32 GetElementSize() const`
- L301 _public prototype_ `virtual void Serialize( FArchive& Ar ) override;` — UObject interface
- L305 _public prototype_ `virtual void PostDuplicate(const FField& InField) override;` — FField interface
- L318 _public prototype_ `static const TCHAR* ImportSingleProperty( const TCHAR* Str, void* DestData, const UStruct* ObjectStruct, UObject* SubobjectOuter, int32 PortFlags, FOutputDevice* Warn, TArray<struct FDefinedProperty>& DefinedProperties );` — parses and imports a text definition of a single property's value (if array, may be an individual element) also includes parsing of special operations for array properties (Add/Remove/RemoveIndex/Empty) @param Str	the string to parse @param DestData	base location the parsed property should place its data (DestData + ParsedProperty->Offset) @param ObjectStruct	the struct containing the valid fields @param SubobjectOuter	owner of DestData and any subobjects within it @param PortFlags	property import flags @param Warn	output device for any error messages @param DefinedProperties (out)	list of properties/indices that have been parsed by previous calls, so duplicate definitions cause an error @return pointer to remaining text in the stream (even on failure, but on failure it may not be advanced past the entire key/value pair)
- L322 _public prototype_ `static FName FindRedirectedPropertyName(const UStruct* ObjectStruct, FName OldName);` — Gets a redirected property name, will return NAME_None if no redirection was found
- L330 _public prototype_ `FString GetNameCPP() const;` — Returns the C++ name of the property, including the _DEPRECATED suffix if the property is deprecated. @return C++ name of property
- L333 _public prototype_ `virtual FString GetCPPMacroType( FString& ExtendedTypeText ) const;` — UHT interface
- L341 _public prototype_ `virtual FString GetCPPType( FString* ExtendedTypeText=NULL, uint32 CPPExportFlags=0 ) const PURE_VIRTUAL(FProperty::GetCPPType,return TEXT(""););` — Returns the text to use for exporting this property to header file. @param	ExtendedTypeText	for property types which use templates, will be filled in with the type @param	CPPExportFlags		flags for modifying the behavior of the export
- L346 _public prototype_ `UPropertyWrapper* GetUPropertyWrapper();` — Gets the wrapper object for this property or creates one if it doesn't exist yet
- L350 _public function_ `virtual bool HasSetter() const` — Checks if this property as a native setter function
- L355 _public function_ `virtual bool HasGetter() const` — Checks if this property as a native getter function
- L360 _public function_ `virtual bool HasSetterOrGetter() const` — Checks if this property as a native setter or getter function
- L369 _public function_ `virtual void CallSetter(void* Container, const void* InValue) const` — Calls the native setter function for this property @param Container Pointer to the owner of this property (either UObject or struct) @param InValue Pointer to the new value
- L378 _public function_ `virtual void CallGetter(const void* Container, void* OutValue) const` — Calls the native getter function for this property @param Container Pointer to the owner of this property (either UObject or struct) @param OutValue Pointer to the value where the existing property value will be copied to
- L384 _public prototype_ `EPropertyVisitorControlFlow Visit(const FPropertyVisitorData& Data, const TFunctionRef<EPropertyVisitorControlFlow(const FPropertyVisitorPath& , const FPropertyVisitorData& )> InFunc) const;` — `UE_DEPRECATED(5.7, "Visit is deprecated, please use Visit with context instead.")`
- L394 _public prototype_ `EPropertyVisitorControlFlow Visit(const FPropertyVisitorData& Data, const TFunctionRef<EPropertyVisitorControlFlow(const FPropertyVisitorContext& )> InFunc) const;` — Visits this property and allows recursion into the inner properties This method allows callers to visit inner properties without knowing about its container type as opposed to TPropertyIterator. This visit property pattern facilitates the recursion into user defined properties and allows users to add specific visit logic on UStruct via traits. @param Data to the property to visit @param InFunc to call on each visited property, the return value controls what is the next behavior once this property has been visited @return the new action to take one visited this property
- L404 _public prototype_ `virtual EPropertyVisitorControlFlow Visit(FPropertyVisitorContext& Context, const TFunctionRef<EPropertyVisitorControlFlow(const FPropertyVisitorContext& )> InFunc) const;` — Visits this property and allows recursion into the inner properties This method allows callers to visit inner properties without knowing about its container type as opposed to TPropertyIterator. This visit property pattern facilitates the recursion into user defined properties and allows users to add specific visit logic on UStruct via traits. @param Context which containes the path that was computed until we reached this property and the sata to the property to visit @param InFunc to call on each visited property, the return value controls what is the next behavior once this property has been visited @return the new action to take one visited this property
- L410 _public prototype_ `virtual void* ResolveVisitedPathInfo(void* Data, const FPropertyVisitorInfo& Info) const;` — Attempt to resolve the given inner path info against this outer property to get the inner property value. @return The inner property value, or null if the path info is incompatible/missing on this property.
- L416 _private prototype_ `int32 SetupOffset();` — Set the alignment offset for this property @return the size of the structure including this newly added property
- L423 _protected prototype_ `void SetOffset_Internal(int32 NewOffset);` — Set the alignment offset for this property - added for FMapProperty
- L428 _protected prototype_ `void Init();` — Initializes internal state.
- L433 _public function_ `UE_INTERNAL UE_FORCEINLINE_HINT int32 GetIndexInOwner() const` — Return the index of the property in its owner. Only valid after Link(). -1 if not linked by a UStruct.
- L439 _public function_ `UE_INTERNAL UE_FORCEINLINE_HINT void SetIndexInOwner(int32 Index)` — Set the index of the property in its owner. Set by the owner in UStruct::Link().
- L446 _public function_ `UE_FORCEINLINE_HINT int32 GetOffset_ForDebug() const` — Return offset of property from container base.
- L451 _public function_ `UE_FORCEINLINE_HINT int32 GetOffset_ForUFunction() const` — Return offset of property from container base.
- L456 _public function_ `UE_FORCEINLINE_HINT int32 GetOffset_ForGC() const` — Return offset of property from container base.
- L461 _public function_ `UE_FORCEINLINE_HINT int32 GetOffset_ForInternal() const` — Return offset of property from container base.
- L466 _public function_ `UE_FORCEINLINE_HINT int32 GetOffset_ReplaceWith_ContainerPtrToValuePtr() const` — Return offset of property from container base.
- L471 _public function_ `void LinkWithoutChangingOffset(FArchive& Ar)`
- L476 _public function_ `int32 Link(FArchive& Ar)`
- L484 _public prototype_ `void InitializeMetaData();` — Move metadata from static memory into metadata object on package
- L488 _protected prototype_ `virtual void LinkInternal(FArchive& Ar);`
- L506 _public prototype_ `virtual EConvertFromTypeResult ConvertFromType(const FPropertyTag& Tag, FStructuredArchive::FSlot Slot, uint8* Data, const UStruct* DefaultsStruct, const uint8* Defaults);` — Allows a property to implement backwards compatibility handling for tagged properties @param	Tag			property tag of the loading data @param	Ar			the archive the data is being loaded from @param	Data		a pointer to the container to write the loaded data to @param	DefaultsStruct @param	Defaults	if available, a pointer to the container containing the default value for this property, or null @return	A state which tells the tagged property system how the property dealt with the data. Converted:        the function handled conversion. CannotConvert:    the tag is not something that the property can convert. Serialized:       the function handled serialization without conversion. UseSerializeItem: no conversion was done on the property - this can mean that the tag is correct and normal serialization applies or that the tag is incompatible.
- L517 _public prototype_ `virtual bool Identical(TNotNull<const void*> A, const void* B, uint32 PortFlags = 0) const PURE_VIRTUAL(FProperty::Identical, return false;);` — Determines whether the property values are identical. @param	A			property data to be compared, already offset @param	B			property data to be compared, already offset @param	PortFlags	allows caller more control over how the property values are compared @return	true if the property values are identical
- L528 _public function_ `bool Identical_InContainer(TNotNull<const void*> A, const void* B, int32 ArrayIndex = 0, uint32 PortFlags = 0) const` — Determines whether the property values are identical. @param	A			property container of data to be compared, NOT offset @param	B			property container of data to be compared, NOT offset @param	PortFlags	allows caller more control over how the property values are compared @return	true if the property values are identical
- L540 _public function_ `void SerializeBinProperty( FStructuredArchive::FSlot Slot, TNotNull<void*> Data, int32 ArrayIdx = -1 )` — Serializes the property with the struct's data residing in Data. @param	Ar				the archive to use for serialization @param	Data			pointer to the location of the beginning of the struct's property data @param	ArrayIdx		if not -1 (default), only this array slot will be serialized
- L563 _public function_ `void SerializeNonMatchingBinProperty(FStructuredArchive::FSlot Slot, TNotNull<void*> Data, void const* DefaultData, UStruct* DefaultStruct)` — Serializes the property with the struct's data residing in Data, unless it matches the default @param	Ar				the archive to use for serialization @param	Data			pointer to the location of the beginning of the struct's property data @param	DefaultData		pointer to the location of the beginning of the data that should be compared against @param	DefaultStruct	struct corresponding to the block of memory located at DefaultData
- L583 _public prototype_ `virtual void SerializeItem(FStructuredArchive::FSlot Slot, TNotNull<void*> Value, void const* Defaults = nullptr) const PURE_VIRTUAL(FProperty::SerializeItem, );`
- L584 _public prototype_ `virtual bool NetSerializeItem(FArchive& Ar, UPackageMap* Map, TNotNull<void*> Data, TArray<uint8> * MetaData = nullptr) const;`
- L585 _public prototype_ `virtual bool SupportsNetSharedSerialization() const;`
- L587 _public function_ `void ExportTextItem_Direct(FString& ValueStr, TNotNull<const void*> PropertyValue, const void* DefaultValue, UObject* Parent, int32 PortFlags, UObject* ExportRootScope = nullptr) const`
- L592 _public function_ `void ExportTextItem_InContainer(FString& ValueStr, TNotNull<const void*> Container, const void* DefaultValue, UObject* Parent, int32 PortFlags, UObject* ExportRootScope = nullptr) const`
- L606 _public function_ `const TCHAR* ImportText_InContainer(const TCHAR* Buffer, TNotNull<void*> Container, UObject* OwnerObject, int32 PortFlags, FOutputDevice* ErrorText = (FOutputDevice*)GWarn) const` — Import a text value @param Buffer		Text representing the property value @param Container	Pointer to the container that owns this property (either UObject pointer or a struct pointer) @param OwnerObject	Object that owns the property container (if the container is an UObject then Container is also OwnerObject) @param PortFlags	Flags controlling the behavior when importing the value @param ErrorText	Output device for throwing warnings or errors on import @returns Buffer pointer advanced by the number of characters consumed when reading the text value
- L625 _public function_ `const TCHAR* ImportText_Direct(const TCHAR* Buffer, TNotNull<void*> PropertyPtr, UObject* OwnerObject, int32 PortFlags, FOutputDevice* ErrorText = (FOutputDevice*)GWarn) const` — Import a text value @param Buffer		Text representing the property value @param PropertyPtr	Pointer to property value @param OwnerObject	Object that owns the property @param PortFlags	Flags controlling the behavior when importing the value @param ErrorText	Output device for throwing warnings or errors on import @returns Buffer pointer advanced by the number of characters consumed when reading the text value
- L635 _public function_ `inline void SetValue_InContainer(void* OutContainer, const void* InValue) const`
- L646 _public function_ `inline void GetValue_InContainer(void const* InContainer, void* OutValue) const`
- L664 _public prototype_ `void SetSingleValue_InContainer(void* OutContainer, const void* InValue, int32 ArrayIndex) const;` — Copies a single value to the property even if the property represents a static array of values @param OutContainer Instance owner of the property @param InValue Pointer to the memory that the value will be copied from. Must be at least ElementSize big @param ArrayIndex Index into the static array to copy the value from. If the property is not a static array it should be 0
- L672 _public prototype_ `void GetSingleValue_InContainer(const void* InContainer, void* OutValue, int32 ArrayIndex) const;` — Copies a single value to OutValue even if the property represents a static array of values @param InContainer Instance owner of the property @param OutValue Pointer to the memory that the value will be copied to. Must be at least ElementSize big @param ArrayIndex Index into the static array to copy the value from. If the property is not a static array it should be 0
- L675 _public prototype_ `void* AllocateAndInitializeValue() const;` — Allocates and initializes memory to hold a value this property represents
- L678 _public prototype_ `void DestroyAndFreeValue(void* InMemory) const;` — Destroys and frees memory with a value this property represents
- L686 _public prototype_ `void PerformOperationWithSetter(void* OutContainer, void* DirectPropertyAddress, TFunctionRef<void(void*)> DirectValueAccessFunc) const;` — Helper function for setting container / struct property value and performing operation directly on the value memory @param OutContainer Pointer to the container that owns the property. Can be null but then setters and getters will not be used. @param DirectPropertyAddress Direct property value address. Can be null only if OutContainer is a valid pointer. @param DirectValueAccessFunc Function that manipulates directly on property value address. The value address can be different than the passed in DirectPropertyAddress if setters and getters are present and OutContainer pointer is valid.
- L694 _public prototype_ `void PerformOperationWithGetter(void* OutContainer, const void* DirectPropertyAddress, TFunctionRef<void(const void*)> DirectValueAccessFunc) const;` — Helper function for getting container / struct property value and performing operation directly on the value memory @param OutContainer Pointer to the container that owns the property. Can be null but then setters and getters will not be used. @param DirectPropertyAddress Direct property value address. Can be null only if OutContainer is a valid pointer. @param DirectValueAccessFunc Function that manipulates directly on property value address. The value address can be different than the passed in DirectPropertyAddress if setters and getters are present and OutContainer pointer is valid.
- L702 _public prototype_ `virtual void* GetValueAddressAtIndex_Direct(const FProperty* Inner, void* InValueAddress, int32 Index) const;` — Gets value address at given index inside of a static array or container @param InValueAddress address of the value represented by this property @param Index into the static array or container @returns address of the value at given index
- L716 _public prototype_ `virtual void AppendSchemaHash(FBlake3& Builder, bool bSkipEditorOnly) const;` — Updates the given HashBuilder with name and type information of this Property. Contract: the hashed data is different from any property that serializes differently in Tagged Property Serialization. If necessary to follow the contract, subclasses should override and add further information after calling Super::AppendSchemaHash. e.g. FStructProperty needs to append the schema hash of its UStruct. @param HashBuilder The builder to Update with property information @param bSkipEditorOnly Used by subclasses with sub- properties that may be editor-only. If true, sub- properties that are editor-only should not be appended to the hash. This property's base data is appended without regard for bSkipEditorOnly.
- L720 _protected prototype_ `virtual void ExportText_Internal(FString& ValueStr, TNotNull<const void*> PropertyValueOrContainer, EPropertyPointerType PointerType, const void* DefaultValue, UObject* Parent, int32 PortFlags, UObject* ExportRootScope = nullptr) const PURE_VIRTUAL(FProperty::ExportText, );`
- L721 _protected prototype_ `virtual const TCHAR* ImportText_Internal(const TCHAR* Buffer, TNotNull<void*> ContainerOrPropertyPtr, EPropertyPointerType PointerType, UObject* OwnerObject, int32 PortFlags, FOutputDevice* ErrorText) const PURE_VIRTUAL(FProperty::ImportText, return nullptr;);`
- L725 _public prototype_ `bool ExportText_Direct(FString& ValueStr, TNotNull<const void*> Data, const void* Delta, UObject* Parent, int32 PortFlags, UObject* ExportRootScope = nullptr) const;`
- L726 _public function_ `UE_FORCEINLINE_HINT bool ExportText_InContainer(int32 Index, FString& ValueStr, TNotNull<const void*> Data, const void* Delta, UObject* Parent, int32 PortFlags, UObject* ExportRootScope = nullptr) const`
- L733 _private function_ `inline void* ContainerVoidPtrToValuePtrInternal(void* ContainerPtr, int32 ArrayIndex) const`
- L747 _private function_ `inline void* ContainerUObjectPtrToValuePtrInternal(UObject* ContainerPtr, int32 ArrayIndex) const`
- L779 _protected function_ `inline void* PointerToValuePtr(void const* ContainerOrPropertyPtr, EPropertyPointerType PropertyPointerType, int32 ArrayIndex = 0) const`
- L801 _public function_ `template<typename ValueType> UE_FORCEINLINE_HINT ValueType* ContainerPtrToValuePtr(UObject* ContainerPtr, int32 ArrayIndex = 0) const` — Get the pointer to property value in a supplied 'container'. You can _only_ call this function on a UObject* or a uint8*. If the property you want is a 'top level' UObject property, you _must_ call the function passing in a UObject* and not a uint8*. There are checks inside the function to vertify this. @param	ContainerPtr			UObject* or uint8* to container of property value @param	ArrayIndex				In array case, index of array element we want
- L806 _public function_ `template<typename ValueType> UE_FORCEINLINE_HINT ValueType* ContainerPtrToValuePtr(void* ContainerPtr, int32 ArrayIndex = 0) const`
- L811 _public function_ `template<typename ValueType> UE_FORCEINLINE_HINT ValueType const* ContainerPtrToValuePtr(UObject const* ContainerPtr, int32 ArrayIndex = 0) const`
- L816 _public function_ `template<typename ValueType> UE_FORCEINLINE_HINT ValueType const* ContainerPtrToValuePtr(void const* ContainerPtr, int32 ArrayIndex = 0) const`
- L824 _public function_ `template<typename ValueType> inline ValueType* ContainerPtrToValuePtrForDefaults(const UStruct* ContainerClass, UObject* ContainerPtr, int32 ArrayIndex = 0) const` — Default variants, these accept and return nullptr, and also check the property against the size of the container. If we copy from a baseclass (like for a CDO), then this will give nullptr for any property that doesn't belong to the baseclass.
- L833 _public function_ `template<typename ValueType> inline ValueType* ContainerPtrToValuePtrForDefaults(const UStruct* ContainerClass, void* ContainerPtr, int32 ArrayIndex = 0) const`
- L842 _public function_ `template<typename ValueType> inline const ValueType* ContainerPtrToValuePtrForDefaults(const UStruct* ContainerClass, const UObject* ContainerPtr, int32 ArrayIndex = 0) const`
- L851 _public function_ `template<typename ValueType> inline const ValueType* ContainerPtrToValuePtrForDefaults(const UStruct* ContainerClass, const void* ContainerPtr, int32 ArrayIndex = 0) const`
- L860 _public function_ `UE_FORCEINLINE_HINT bool IsInContainer(int32 ContainerSize) const` — See if the offset of this property is below the supplied container size
- L865 _public function_ `UE_FORCEINLINE_HINT bool IsInContainer(const UStruct* ContainerClass) const` — See if the offset of this property is below the supplied container size
- L881 _public function_ `inline void CopySingleValue( void* Dest, void const* Src ) const` — Copy the value for a single element of this property. @param	Dest				the address where the value should be copied to.  This should always correspond to the BASE + OFFSET + INDEX * SIZE, where BASE = (for member properties) the address of the UObject which contains this data, (for locals/parameters) the address of the space allocated for the function's locals OFFSET = the Offset of this FProperty INDEX = the index that you want to copy.  for properties which are not arrays, this should always be 0 SIZE = the ElementSize of this FProperty @param	Src					the address of the value to copy from. should be evaluated the same way as Dest @param	InstancingParams	contains information about instancing (if any) to perform
- L899 _public prototype_ `uint32 GetValueTypeHash(const void* Src) const;` — Returns the hash value for an element of this property.
- L902 _protected prototype_ `virtual void CopyValuesInternal( void* Dest, void const* Src, int32 Count ) const;`
- L903 _protected prototype_ `virtual uint32 GetValueTypeHashInternal(const void* Src) const;`
- L915 _public function_ `inline void CopyCompleteValue( void* Dest, void const* Src ) const` — Copy the value for all elements of this property. @param	Dest				the address where the value should be copied to.  This should always correspond to the BASE + OFFSET, where BASE = (for member properties) the address of the UObject which contains this data, (for locals/parameters) the address of the space allocated for the function's locals OFFSET = the Offset of this FProperty @param	Src					the address of the value to copy from. should be evaluated the same way as Dest @param	InstancingParams	contains information about instancing (if any) to perform
- L929 _public function_ `UE_FORCEINLINE_HINT void CopyCompleteValue_InContainer( void* Dest, void const* Src ) const`
- L944 _public prototype_ `virtual void CopySingleValueToScriptVM( void* Dest, void const* Src ) const;` — Copy the value for a single element of this property. To the script VM. @param	Dest				the address where the value should be copied to.  This should always correspond to the BASE + OFFSET + INDEX * SIZE, where BASE = (for member properties) the address of the UObject which contains this data, (for locals/parameters) the address of the space allocated for the function's locals OFFSET = the Offset of this FProperty INDEX = the index that you want to copy.  for properties which are not arrays, this should always be 0 SIZE = the ElementSize of this FProperty @param	Src					the address of the value to copy from. should be evaluated the same way as Dest
- L954 _public prototype_ `virtual void CopyCompleteValueToScriptVM( void* Dest, void const* Src ) const;` — Copy the value for all elements of this property. To the script VM. @param	Dest				the address where the value should be copied to.  This should always correspond to the BASE + OFFSET, where BASE = (for member properties) the address of the UObject which contains this data, (for locals/parameters) the address of the space allocated for the function's locals OFFSET = the Offset of this FProperty @param	Src					the address of the value to copy from. should be evaluated the same way as Dest
- L959 _public prototype_ `virtual void CopyCompleteValueToScriptVM_InContainer( void* OutValue, void const* InContainer ) const;` — Equivalent to the above functions, but using the container and aware of getters/setters when the container has them.
- L960 _public prototype_ `virtual void CopyCompleteValueFromScriptVM_InContainer( void* OutContainer, void const* InValue ) const;`
- L972 _public prototype_ `virtual void CopySingleValueFromScriptVM( void* Dest, void const* Src ) const;` — Copy the value for a single element of this property. From the script VM. @param	Dest				the address where the value should be copied to.  This should always correspond to the BASE + OFFSET + INDEX * SIZE, where BASE = (for member properties) the address of the UObject which contains this data, (for locals/parameters) the address of the space allocated for the function's locals OFFSET = the Offset of this FProperty INDEX = the index that you want to copy.  for properties which are not arrays, this should always be 0 SIZE = the ElementSize of this FProperty @param	Src					the address of the value to copy from. should be evaluated the same way as Dest
- L982 _public prototype_ `virtual void CopyCompleteValueFromScriptVM( void* Dest, void const* Src ) const;` — Copy the value for all elements of this property. From the script VM. @param	Dest				the address where the value should be copied to.  This should always correspond to the BASE + OFFSET, where BASE = (for member properties) the address of the UObject which contains this data, (for locals/parameters) the address of the space allocated for the function's locals OFFSET = the Offset of this FProperty @param	Src					the address of the value to copy from. should be evaluated the same way as Dest
- L990 _public function_ `inline void ClearValue( void* Data ) const` — Zeros the value for this property. The existing data is assumed valid (so for example this calls FString::Empty) This only does one item and not the entire fixed size array. @param	Data		the address of the value for this property that should be cleared.
- L1007 _public function_ `inline void ClearValue_InContainer( void* Data, int32 ArrayIndex = 0 ) const` — Zeros the value for this property. The existing data is assumed valid (so for example this calls FString::Empty) This only does one item and not the entire fixed size array. @param	Data		the address of the container of the value for this property that should be cleared.
- L1019 _protected prototype_ `virtual void ClearValueInternal( void* Data ) const;`
- L1027 _public function_ `inline void DestroyValue( void* Dest ) const` — Destroys the value for this property. The existing data is assumed valid (so for example this calls FString::Empty) This does the entire fixed size array. @param	Dest		the address of the value for this property that should be destroyed.
- L1040 _public function_ `inline void DestroyValue_InContainer( void* Dest ) const` — Destroys the value for this property. The existing data is assumed valid (so for example this calls FString::Empty) This does the entire fixed size array. @param	Dest		the address of the container containing the value that should be destroyed.
- L1049 _protected prototype_ `virtual void DestroyValueInternal( void* Dest ) const;`
- L1055 _public function_ `bool ContainsFinishDestroy(TArray<const FStructProperty*>& EncounteredStructProps) const` — Returns true if the property or any of the child properties should be cleared on FinishDestroy.
- L1072 _public function_ `void FinishDestroy( void* Data ) const` — Applies appropriate finish destroy actions for the property if needed. This is used during UObject destruction to e.g. safely clear values which rely on UScriptStructs. This does the entire fixed size array. @param	Data		the address of the value for this property that should be handled for finish destroy.
- L1089 _public function_ `void FinishDestroy_InContainer( void* Data ) const` — Applies appropriate finish destroy actions for the property if needed. This is used during UObject destruction to e.g. safely clear values which rely on UScriptStructs. This does the entire fixed size array. @param	Data		the address of the container containing the value that should be handled for finish destroy.
- L1099 _protected prototype_ `virtual bool ContainsClearOnFinishDestroyInternal(TArray<const FStructProperty*>& EncounteredStructProps) const;`
- L1100 _protected prototype_ `virtual void FinishDestroyInternal( void* Data ) const;`
- L1110 _public function_ `inline void InitializeValue( void* Dest ) const` — Zeros, copies from the default, or calls the constructor for on the value for this property. The existing data is assumed invalid (so for example this might indirectly call FString::FString, This will do the entire fixed size array. @param	Dest		the address of the value for this property that should be cleared.
- L1128 _public function_ `inline void InitializeValue_InContainer( void* Dest ) const` — Zeros, copies from the default, or calls the constructor for on the value for this property. The existing data is assumed invalid (so for example this might indirectly call FString::FString, This will do the entire fixed size array. @param	Dest		the address of the container of value for this property that should be cleared.
- L1140 _protected prototype_ `virtual void InitializeValueInternal( void* Dest ) const;`
- L1151 _public prototype_ `bool ValidateImportFlags( uint32 PortFlags, FOutputDevice* ErrorText = NULL ) const;` — Verify that modifying this property's value via ImportText is allowed. @param	PortFlags	the flags specified in the call to ImportText @param	ErrorText	[out] set to the error message that should be displayed if returns false @return	true if ImportText should be allowed
- L1152 _public prototype_ `bool ShouldPort( uint32 PortFlags=0 ) const;`
- L1153 _public prototype_ `virtual FName GetID() const;`
- L1163 _public prototype_ `virtual void InstanceSubobjects( void* Data, void const* DefaultData, TNotNull<UObject*> Owner, struct FObjectInstancingGraph* InstanceGraph );` — Creates new copies of components @param	Data				pointer to the address of the instanced object referenced by this UComponentProperty @param	DefaultData			pointer to the address of the default value of the instanced object referenced by this UComponentProperty @param	Owner				the object that contains this property's data @param	InstanceGraph		contains the mappings of instanced objects and components to their templates
- L1165 _public prototype_ `virtual int32 GetMinAlignment() const;`
- L1175 _public prototype_ `virtual bool ContainsObjectReference(TArray<const FStructProperty*>& EncounteredStructProps, EPropertyObjectReferenceType InReferenceType = EPropertyObjectReferenceType::Strong) const;` — Returns true if this property, or in the case of e.g. array or struct properties any sub- property, contains a UObject reference. @param	EncounteredStructProps		used to check for recursion in arrays @param	InReferenceType				type of object reference (strong / weak) @return true if property (or sub- properties) contains the specified type of UObject reference, false otherwise
- L1183 _public function_ `bool ContainsWeakObjectReference() const` — Returns true if this property, or in the case of e.g. array or struct properties any sub- property, contains a weak UObject reference. @return true if property (or sub- properties) contain a weak UObject reference, false otherwise
- L1195 _public function_ `UE_FORCEINLINE_HINT bool ContainsInstancedObjectProperty() const` — Returns true if this property, or in the case of e.g. array or struct properties any sub- property, contains a UObject reference that is marked CPF_NeedCtorLink (i.e. instanced keyword). @return true if property (or sub- properties) contain a FObjectProperty that is marked CPF_NeedCtorLink, false otherwise
- L1204 _public prototype_ `virtual void EmitReferenceInfo(UE::GC::FSchemaBuilder& Schema, int32 BaseOffset, TArray<const FStructProperty*>& EncounteredStructProps, UE::GC::FPropertyStack& DebugPath);` — Emits tokens used by realtime garbage collection code to passed in ReferenceTokenStream. The offset emitted is relative to the passed in BaseOffset which is used by e.g. arrays of structs.
- L1208 _public function_ `UE_FORCEINLINE_HINT int32 GetSize() const` — @TODO: Surely this can have an int32 overflow. This should probably return size_t. Just need to audit all callers to make such a change.
- L1212 _public prototype_ `bool ShouldSerializeValue( FArchive& Ar ) const;`
- L1214 _public prototype_ `virtual bool UseBinaryOrNativeSerialization(const FArchive& Ar) const;`
- L1221 _public function_ `bool ShouldDuplicateValue() const` — Determines whether this property value is eligible for copying when duplicating an object @return	true if this property value should be copied into the duplicate object
- L1231 _public prototype_ `virtual bool LoadTypeName(UE::FPropertyTypeName Type, const FPropertyTag* Tag = nullptr);` — Restores this property and its owned properties from the type name. @return true if this property loaded from the type name and is in a valid and usable state.
- L1236 _public prototype_ `virtual void SaveTypeName(UE::FPropertyTypeNameBuilder& Type) const;` — Saves the type name of this property and its owned properties.
- L1241 _public prototype_ `virtual bool CanSerializeFromTypeName(UE::FPropertyTypeName Type) const;` — Returns true if the type of this property matches the type name.
- L1246 _public function_ `FProperty* GetOwnerProperty()` — Returns the first FProperty in this property's Outer chain that does not have a FProperty for an Outer
- L1256 _public function_ `const FProperty* GetOwnerProperty() const`
- L1269 _public function_ `UE_FORCEINLINE_HINT EPropertyFlags GetPropertyFlags() const` — Returns this property's propertyflags
- L1273 _public function_ `UE_FORCEINLINE_HINT void SetPropertyFlags( EPropertyFlags NewFlags )`
- L1277 _public function_ `UE_FORCEINLINE_HINT void ClearPropertyFlags( EPropertyFlags NewFlags )`
- L1288 _public function_ `UE_FORCEINLINE_HINT bool HasAnyPropertyFlags( uint64 FlagsToCheck ) const` — Used to safely check whether any of the passed in flags are set. @param FlagsToCheck	Object flags to check for. @return				true if any of the passed in flags are set, false otherwise  (including no flags passed in).
- L1299 _public function_ `UE_FORCEINLINE_HINT bool HasAllPropertyFlags( uint64 FlagsToCheck ) const` — Used to safely check whether all of the passed in flags are set. @param FlagsToCheck	Object flags to check for @return true if all of the passed in flags are set (including no flags passed in), false otherwise
- L1308 _public function_ `UE_FORCEINLINE_HINT FProperty* GetRepOwner()` — Returns the replication owner, which is the property itself, or NULL if this isn't important for replication. It is relevant if the property is a net relevant and not being run in the editor
- L1320 _public function_ `UE_FORCEINLINE_HINT bool IsEditorOnlyProperty() const` — Editor-only properties are those that only are used with the editor is present or cannot be removed from serialisation. Editor-only properties include: EditorOnly properties Properties that cannot be removed from serialisation are: Boolean properties (may affect GCC_BITFIELD_MAGIC computation) Native properties (native serialisation)
- L1326 _public prototype_ `virtual bool SameType(const FProperty* Other) const;` — returns true, if Other is property of exactly the same type
- L1328 _public function_ `ELifetimeCondition GetBlueprintReplicationCondition() const`
- L1329 _public function_ `void SetBlueprintReplicationCondition(ELifetimeCondition InBlueprintReplicationCondition)`
- L1337 _public prototype_ `virtual bool HasIntrusiveUnsetOptionalState() const PURE_VIRTUAL(FProperty::HasIntrusiveUnsetOptionalState, return false;) virtual void InitializeIntrusiveUnsetOptionalValue(void* Data) const;` — Returns whether this type has a special state for an unset TOptional meaning the size TOptional<T> and T are the same. Properties must implement this function explicitly even if they do not have such a state. @see Optional.h - HasIntrusiveUnsetOptionalState @see FOptionalProperty
- L1354 _public prototype_ `virtual bool IsIntrusiveOptionalValueSet(const void* Data) const;` — Returns whether an optional value of this inner type is unset. Only valid to call if HasIntrusiveUnsetOptionalState returns true. Equivalent to TOptional<T>::IsSet() @see operator==(FIntrusiveUnsetOptionalState) @param Data Address of value to inspect, already offset. @return true if the value is unset
- L1362 _public prototype_ `virtual void ClearIntrusiveOptionalValue(void* Data) const;` — Set the value to it's special unset state. Equivalent to TOptional<T>::Reset. Only valid to call if HasIntrusiveUnsetOptionalState returns true. @see operator=(FIntrusiveUnsetOptionalState) @param Data Address of the alue, already offset.
- L1369 _public prototype_ `virtual void EmitIntrusiveOptionalReferenceInfo(UE::GC::FSchemaBuilder& Schema, int32 BaseOffset, TArray<const FStructProperty*>& EncounteredStructProps, UE::GC::FPropertyStack& DebugPath);` — For properties returning true from HasIntrusiveUnsetOptionalState which also contain object references, emit information for the garbage collector to safely gather the references from the value whether the optional value is set or unset.

#### union `FProperty::(anonymous)`  
``  
_L190-202_

#### class `FPropertyHelpers`  
`class FPropertyHelpers`  
_L1373-1394_
- L1377 _public prototype_ `static const TCHAR* ReadToken( const TCHAR* Buffer, FString& Out, bool DottedNames = false);` — @param Out Appended to
- L1378 _public prototype_ `static const TCHAR* ReadToken( const TCHAR* Buffer, FStringBuilderBase& Out, bool DottedNames = false);`
- L1392 _public prototype_ `static const TCHAR* ReadTerminatedToken(const TCHAR* Buffer, FString& Out, const TCHAR Terminator, const int32* MaxTokenLen = nullptr);` — Parse a token from the given buffer until we find the given terminating character, or we run out of buffer/hit the given limit. @note This will also parse and unescape any quoted strings found prior to the terminating character, however a terminating character within a quoted string is not considered as a termination point. @param Buffer		The buffer to parse from. @param Out			The value to append to on success. @param Terminator	The token terminator to stop at. @param MaxTokenLen	Optional limit; will fail if we don't find the terminator within this limit. @return The terminating character location in the buffer, or null if parsing failed.
- L1393 _public prototype_ `static const TCHAR* ReadTerminatedToken(const TCHAR* Buffer, FStringBuilderBase& Out, const TCHAR Terminator, const int32* MaxTokenLen = nullptr);`

#### class `UEProperty_Private::FProperty_DoNotUse`  
`class FProperty_DoNotUse`  
_L1399-1414_
- desc: FProperty methods FOR INTERNAL USE ONLY -- only authorized users should be making use of this. -- DO NOT USE!
- L1410 _public function_ `static void Unsafe_AlterOffset(FProperty& Property, const int32 OffsetOverride)` — To facilitate runtime binding with native C++ data-members, we need a way of updating a property's generated offset. This is needed for pre-generated properties, which are then loaded later, and fixed up to point at explicitly mapped C++ data-members. Explicitly exposed for this singular case -- DO NOT USE otherwise.

#### struct `FDefinedProperty`  
`struct FDefinedProperty`  
_L1418-1426_
- desc: reference to a property and optional array index used in property text import to detect duplicate references
- L1420 _public member_ `FProperty* Property;`
- L1421 _public member_ `int32 Index;`
- L1422 _public function_ `bool operator== (const FDefinedProperty& Other) const`

#### class `FDefaultConstructedPropertyElement`  
`class FDefaultConstructedPropertyElement`  
_L1431-1452_
- desc: Creates a temporary object that represents the default constructed value of a FProperty
- L1434 _public prototype_ `FDefaultConstructedPropertyElement() = default;`
- L1435 _public function_ `explicit FDefaultConstructedPropertyElement(const FProperty* InProp) : Obj(FMemory::Malloc(InProp->GetSize(), InProp->GetMinAlignment()), [InProp](void* Object) { InProp->DestroyValue(Object); FMemory::Free(Object); })`
- L1437 _public function_ ``
- L1445 _public function_ `void* GetObjAddress() const`
- L1451 _private member_ `TSharedPtr<void> Obj;`

#### class `TPropertyTypeFundamentals`  
`template<typename InTCppType> class TPropertyTypeFundamentals`  
_L1461-1549_
- L1465 _public typedef_ `typedef InTCppType TCppType;` — Type of the CPP property
- L1472 _public function_ `static UE_FORCEINLINE_HINT TCHAR const* GetTypeName()`
- L1478 _public function_ `static UE_FORCEINLINE_HINT TCppType const* GetPropertyValuePtr(void const* A)` — Convert the address of a value of the property to the proper type
- L1483 _public function_ `static UE_FORCEINLINE_HINT TCppType* GetPropertyValuePtr(void* A)` — Convert the address of a value of the property to the proper type
- L1488 _public function_ `static UE_FORCEINLINE_HINT TCppType const& GetPropertyValue(void const* A)` — Get the value of the property from an address
- L1493 _public function_ `static UE_FORCEINLINE_HINT TCppType GetDefaultPropertyValue()` — Get the default value of the cpp type, just the default constructor, which works even for things like in32
- L1498 _public function_ `static UE_FORCEINLINE_HINT TCppType GetOptionalPropertyValue(void const* B)` — Get the value of the property from an address, unless it is NULL, then return the default value
- L1503 _public function_ `static UE_FORCEINLINE_HINT void SetPropertyValue(void* A, TCppType const& Value)` — Set the value of a property at an address
- L1508 _public function_ `static UE_FORCEINLINE_HINT TCppType* InitializePropertyValue(void* A)` — Initialize the value of a property at an address, this assumes over uninitialized memory
- L1513 _public function_ `static UE_FORCEINLINE_HINT void DestroyPropertyValue(void* A)` — Destroy the value of a property at an address
- L1518 _public function_ `static UE_FORCEINLINE_HINT bool HasIntrusiveUnsetOptionalState()`
- L1523 _public function_ `static UE_FORCEINLINE_HINT void InitializeIntrusiveUnsetOptionalValue(void* Data)`
- L1528 _public function_ `static UE_FORCEINLINE_HINT bool IsIntrusiveOptionalValueSet(const void* A)`
- L1533 _public function_ `static UE_FORCEINLINE_HINT void ClearIntrusiveOptionalValue(void* A)`
- L1540 _protected function_ `static inline EPropertyFlags GetComputedFlagsPropertyFlags()` — Get the property flags corresponding to this C++ type, from the C++ type traits system

#### enum `TPropertyTypeFundamentals::(anonymous)`  
``  
_L1467-1470_

#### class `TProperty`  
`template<typename InTCppType, class TInPropertyBaseClass> class TProperty : public TInPropertyBaseClass, public TPropertyTypeFundamentals<InTCppType>`  
_L1553-1708_
- inherits: `TInPropertyBaseClass,TPropertyTypeFundamentals<InTCppType>`
- L1557 _public typedef_ `typedef InTCppType TCppType;`
- L1558 _public typedef_ `typedef TInPropertyBaseClass Super;`
- L1559 _public typedef_ `typedef TPropertyTypeFundamentals<InTCppType> TTypeFundamentals;`
- L1561 _public function_ `TProperty(EInternal InInernal, FFieldClass* InClass) : Super(EC_InternalUseOnlyConstructor, InClass)`
- L1566 _public function_ `TProperty(FFieldVariant InOwner, const FName& InName) : Super(InOwner, InName)`
- L1572 _public function_ `TProperty(FFieldVariant InOwner, const FName& InName, EObjectFlags InObjectFlags) : TProperty(InOwner, InName)` — `UE_DEPRECATED(5.8, "TProperty constructor with InObjectFlags is deprecated, remove that parameter.")`
- L1580 _public function_ `template <typename PropertyParamsType> TProperty(FFieldVariant InOwner, PropertyParamsType& Prop) : Super(InOwner, Prop, TTypeFundamentals::GetComputedFlagsPropertyFlags())` — Constructor used for constructing compiled in properties @param InOwner Owner of the property @param PropBase Pointer to the compiled in structure describing the property
- L1588 _public function_ `template<typename... Ts> explicit consteval TProperty(`
- L1601 _public function_ `explicit TProperty(UField* InField) : Super(InField)`
- L1609 _public function_ `virtual FString GetCPPType( FString* ExtendedTypeText=NULL, uint32 CPPExportFlags=0 ) const override` — UHT interface
- L1616 _public function_ `virtual int32 GetMinAlignment() const override` — FProperty interface.
- L1620 _public function_ `virtual void LinkInternal(FArchive& Ar) override`
- L1626 _public function_ `virtual void CopyValuesInternal( void* Dest, void const* Src, int32 Count ) const override`
- L1633 _public function_ `virtual void ClearValueInternal( void* Data ) const override`
- L1637 _public function_ `virtual void InitializeValueInternal( void* Dest ) const override`
- L1644 _public function_ `virtual void DestroyValueInternal( void* Dest ) const override`
- L1653 _public function_ `UE_FORCEINLINE_HINT TCppType const* GetPropertyValuePtr_InContainer(void const* A, int32 ArrayIndex = 0) const` — Convert the address of a container to the address of the property value, in the proper type
- L1658 _public function_ `UE_FORCEINLINE_HINT TCppType* GetPropertyValuePtr_InContainer(void* A, int32 ArrayIndex = 0) const` — Convert the address of a container to the address of the property value, in the proper type
- L1663 _public function_ `UE_FORCEINLINE_HINT TCppType const& GetPropertyValue_InContainer(void const* A, int32 ArrayIndex = 0) const` — Get the value of the property from a container address
- L1668 _public function_ `UE_FORCEINLINE_HINT TCppType GetOptionalPropertyValue_InContainer(void const* B, int32 ArrayIndex = 0) const` — Get the value of the property from a container address, unless it is NULL, then return the default value
- L1673 _public function_ `UE_FORCEINLINE_HINT void SetPropertyValue_InContainer(void* A, TCppType const& Value, int32 ArrayIndex = 0) const` — Set the value of a property in a container
- L1678 _public function_ `UE_FORCEINLINE_HINT void SetValue_InContainer(void* OutContainer, const TCppType& InValue) const`
- L1683 _public function_ `UE_FORCEINLINE_HINT void GetValue_InContainer(void const* InContainer, TCppType* OutValue) const`
- L1688 _public function_ `virtual bool HasIntrusiveUnsetOptionalState() const override`
- L1693 _public function_ `virtual void InitializeIntrusiveUnsetOptionalValue(void* Data) const override`
- L1698 _public function_ `virtual bool IsIntrusiveOptionalValueSet(const void* Data) const override`
- L1703 _public function_ `virtual void ClearIntrusiveOptionalValue(void* Data) const override`

#### class `TProperty_WithEqualityAndSerializer`  
`template<typename InTCppType, class TInPropertyBaseClass> class TProperty_WithEqualityAndSerializer : public TProperty<InTCppType, TInPropertyBaseClass>`  
_L1711-1783_
- inherits: `TProperty<InTCppType,TInPropertyBaseClass>`
- L1715 _public typedef_ `typedef TProperty<InTCppType, TInPropertyBaseClass> Super;`
- L1716 _public typedef_ `typedef InTCppType TCppType;`
- L1717 _public typedef_ `typedef typename Super::TTypeFundamentals TTypeFundamentals;`
- L1719 _public function_ `TProperty_WithEqualityAndSerializer(EInternal InInernal, FFieldClass* InClass) : Super(EC_InternalUseOnlyConstructor, InClass)`
- L1724 _public function_ `TProperty_WithEqualityAndSerializer(FFieldVariant InOwner, const FName& InName) : Super(InOwner, InName)`
- L1729 _public function_ `TProperty_WithEqualityAndSerializer(FFieldVariant InOwner, const FName& InName, EObjectFlags InObjectFlags) : TProperty_WithEqualityAndSerializer(InOwner, InName)` — `UE_DEPRECATED(5.8, "TProperty_WithEqualityAndSerializer constructor with InObjectFlags is deprecated, remove that parameter.")`
- L1736 _public function_ `TProperty_WithEqualityAndSerializer(FFieldVariant InOwner, const UECodeGen_Private::FPropertyParamsBaseWithOffset& Prop) : Super(InOwner, Prop)` — Constructor used for constructing compiled in properties @param InOwner Owner of the property @param PropBase Pointer to the compiled in structure describing the property
- L1743 _public function_ `template<typename... Ts> explicit consteval TProperty_WithEqualityAndSerializer( UE::CodeGen::ConstInit::FPropertyParams InBaseParams, Ts&&... Args ) : Super(InBaseParams, Forward<Ts>(Args)...)`
- L1753 _public function_ `explicit TProperty_WithEqualityAndSerializer(UField* InField) : Super(InField)`
- L1760 _public function_ `virtual bool Identical(TNotNull<const void*> A, const void* B, uint32 PortFlags = 0) const override` — FProperty interface.
- L1777 _public function_ `virtual void SerializeItem(FStructuredArchive::FSlot Slot, TNotNull<void*> Value, void const* Defaults) const override`

#### class `FNumericProperty`  
`class FNumericProperty : public FProperty`  
_L1785-1920_
- inherits: `FProperty`
- L1791 _private function_ `FNumericProperty(FFieldVariant InOwner, const FName& InName, EObjectFlags InObjectFlags) : FNumericProperty(InOwner, InName)` — `UE_DEPRECATED(5.8, "FNumericProperty constructor with InObjectFlags is deprecated, remove that parameter.")`
- L1798 _private prototype_ `FNumericProperty(FFieldVariant InOwner, const UECodeGen_Private::FPropertyParamsBaseWithOffset& Prop, EPropertyFlags AdditionalPropertyFlags = CPF_None);` — Constructor used for constructing compiled in properties @param InOwner Owner of the property @param PropBase Pointer to the compiled in structure describing the property
- L1801 _private function_ `explicit consteval FNumericProperty(UE::CodeGen::ConstInit::FPropertyParams InBaseParams) : Super(InBaseParams)`
- L1808 _private prototype_ `explicit FNumericProperty(UField* InField);`
- L1812 _private prototype_ `virtual const TCHAR* ImportText_Internal(const TCHAR* Buffer, TNotNull<void*> ContainerOrPropertyPtr, EPropertyPointerType PropertyPointerType, UObject* Parent, int32 PortFlags, FOutputDevice* ErrorText) const override;` — FProperty interface.
- L1813 _private prototype_ `virtual void ExportText_Internal( FString& ValueStr, TNotNull<const void*> PropertyValueOrContainer, EPropertyPointerType PropertyPointerType, const void* DefaultValue, UObject* Parent, int32 PortFlags, UObject* ExportRootScope ) const override;`
- L1819 _private prototype_ `virtual bool IsFloatingPoint() const;` — Return true if this property is for a floating point number
- L1822 _private prototype_ `virtual bool IsInteger() const;` — Return true if this property is for a integral or enum type
- L1825 _private function_ `template <typename T> bool CanHoldValue(T Value) const`
- L1843 _private function_ `UE_FORCEINLINE_HINT bool IsEnum() const` — Return true if this property is a FByteProperty with a non-null Enum
- L1849 _private prototype_ `virtual UEnum* GetIntPropertyEnum() const;` — Return the UEnum if this property is a FByteProperty with a non-null Enum
- L1856 _private prototype_ `virtual void SetIntPropertyValue(void* Data, uint64 Value) const;` — Set the value of an unsigned integral property type @param Data - pointer to property data to set @param Value - Value to set data to
- L1863 _private prototype_ `virtual void SetIntPropertyValue(void* Data, int64 Value) const;` — Set the value of a signed integral property type @param Data - pointer to property data to set @param Value - Value to set data to
- L1870 _private prototype_ `virtual void SetFloatingPointPropertyValue(void* Data, double Value) const;` — Set the value of a floating point property type @param Data - pointer to property data to set @param Value - Value to set data to
- L1878 _private prototype_ `virtual void SetNumericPropertyValueFromString(void* Data, TCHAR const* Value) const;` — Set the value of any numeric type from a string point @param Data - pointer to property data to set @param Value - Value (as a string) to set CAUTION: This routine does not do enum name conversion
- L1879 _private prototype_ `virtual void SetNumericPropertyValueFromString_InContainer(void* Container, TCHAR const* Value) const;`
- L1886 _private prototype_ `virtual int64 GetSignedIntPropertyValue(void const* Data) const;` — Gets the value of a signed integral property type @param Data - pointer to property data to get @return Data as a signed int
- L1887 _private prototype_ `virtual int64 GetSignedIntPropertyValue_InContainer(void const* Container) const;`
- L1894 _private prototype_ `virtual uint64 GetUnsignedIntPropertyValue(void const* Data) const;` — Gets the value of an unsigned integral property type @param Data - pointer to property data to get @return Data as an unsigned int
- L1895 _private prototype_ `virtual uint64 GetUnsignedIntPropertyValue_InContainer(void const* Container) const;`
- L1902 _private prototype_ `virtual double GetFloatingPointPropertyValue(void const* Data) const;` — Gets the value of an floating point property type @param Data - pointer to property data to get @return Data as a double
- L1910 _private prototype_ `virtual FString GetNumericPropertyValueToString(void const* Data) const;` — Get the value of any numeric type and return it as a string @param Data - pointer to property data to get @return Data as a string CAUTION: This routine does not do enum name conversion
- L1911 _private prototype_ `virtual FString GetNumericPropertyValueToString_InContainer(void const* Container) const;`
- L1914 _private prototype_ `static int64 ReadEnumAsInt64(FStructuredArchive::FSlot Slot, const UStruct* DefaultsStruct, const FPropertyTag& Tag);`
- L1917 _private prototype_ `virtual bool CanHoldDoubleValueInternal (double Value) const PURE_VIRTUAL(FNumericProperty::CanHoldDoubleValueInternal, return false;);`
- L1918 _private prototype_ `virtual bool CanHoldSignedValueInternal (int64 Value) const PURE_VIRTUAL(FNumericProperty::CanHoldSignedValueInternal, return false;);`
- L1919 _private prototype_ `virtual bool CanHoldUnsignedValueInternal(uint64 Value) const PURE_VIRTUAL(FNumericProperty::CanHoldUnsignedValueInternal, return false;);`

#### class `TProperty_Numeric`  
`template<typename InTCppType> class TProperty_Numeric : public TProperty_WithEqualityAndSerializer<InTCppType, FNumericProperty>`  
_L1923-2181_
- inherits: `TProperty_WithEqualityAndSerializer<InTCppType,FNumericProperty>`
- L1926 _public typedef_ `typedef TProperty_WithEqualityAndSerializer<InTCppType, FNumericProperty> Super;`
- L1927 _public typedef_ `typedef InTCppType TCppType;`
- L1928 _public typedef_ `typedef typename Super::TTypeFundamentals TTypeFundamentals;`
- L1930 _public function_ `TProperty_Numeric(EInternal InInernal, FFieldClass* InClass) : Super(EC_InternalUseOnlyConstructor, InClass)`
- L1935 _public function_ `TProperty_Numeric(FFieldVariant InOwner, const FName& InName) : Super(InOwner, InName)`
- L1940 _public function_ `TProperty_Numeric(FFieldVariant InOwner, const FName& InName, EObjectFlags InObjectFlags) : TProperty_Numeric(InOwner, InName)` — `UE_DEPRECATED(5.8, "TProperty_Numeric constructor with InObjectFlags is deprecated, remove that parameter.")`
- L1947 _public function_ `TProperty_Numeric(FFieldVariant InOwner, const UECodeGen_Private::FPropertyParamsBaseWithOffset& Prop) : Super(InOwner, Prop)` — Constructor used for constructing compiled in properties @param InOwner Owner of the property @param PropBase Pointer to the compiled in structure describing the property
- L1953 _public function_ `explicit consteval TProperty_Numeric(UE::CodeGen::ConstInit::FPropertyParams InBaseParams) : Super(InBaseParams)`
- L1960 _public function_ `explicit TProperty_Numeric(UField* InField) : Super(InField)`
- L1967 _public function_ `virtual uint32 GetValueTypeHashInternal(const void* Src) const override` — FProperty interface
- L1974 _protected function_ `template <typename OldNumericType> UE_FORCEINLINE_HINT void ConvertFromArithmeticValue(FStructuredArchive::FSlot Slot, void* Obj, const FPropertyTag& Tag) const`
- L2016 _public function_ `virtual EConvertFromTypeResult ConvertFromType(const FPropertyTag& Tag, FStructuredArchive::FSlot Slot, uint8* Data, const UStruct* DefaultsStruct, const uint8* Defaults) override`
- L2092 _public function_ `virtual bool IsFloatingPoint() const override` — FNumericProperty interface.
- L2096 _public function_ `virtual bool IsInteger() const override`
- L2100 _public function_ `virtual void SetIntPropertyValue(void* Data, uint64 Value) const override`
- L2105 _public function_ `virtual void SetIntPropertyValue(void* Data, int64 Value) const override`
- L2110 _public function_ `virtual void SetFloatingPointPropertyValue(void* Data, double Value) const override`
- L2115 _public function_ `virtual void SetNumericPropertyValueFromString(void* Data, TCHAR const* Value) const override`
- L2119 _public function_ `virtual void SetNumericPropertyValueFromString_InContainer(void* Container, TCHAR const* Value) const override`
- L2125 _public function_ `virtual FString GetNumericPropertyValueToString(void const* Data) const override`
- L2129 _public function_ `virtual FString GetNumericPropertyValueToString_InContainer(void const* Container) const override`
- L2135 _public function_ `virtual int64 GetSignedIntPropertyValue(void const* Data) const override`
- L2140 _public function_ `virtual int64 GetSignedIntPropertyValue_InContainer(void const* Container) const override`
- L2147 _public function_ `virtual uint64 GetUnsignedIntPropertyValue(void const* Data) const override`
- L2152 _public function_ `virtual uint64 GetUnsignedIntPropertyValue_InContainer(void const* Container) const override`
- L2159 _public function_ `virtual double GetFloatingPointPropertyValue(void const* Data) const override`
- L2167 _private function_ `virtual bool CanHoldDoubleValueInternal(double Value) const`
- L2172 _private function_ `virtual bool CanHoldSignedValueInternal(int64 Value) const`
- L2177 _private function_ `virtual bool CanHoldUnsignedValueInternal(uint64 Value) const`

#### struct `TProperty_Numeric::TConvertAndSet`  
`template <typename FromType, typename ToType> struct TConvertAndSet`  
_L1981-2002_
- L1983 _public function_ `TConvertAndSet(const TProperty_Numeric& Property, FStructuredArchive::FSlot Slot, void* Obj, const FPropertyTag& Tag)`
- L2007 _public function_ `inline TConvertAndSet(const TProperty_Numeric& Property, FStructuredArchive::FSlot Slot, void* Obj, const FPropertyTag& Tag)`

#### struct `TProperty_Numeric::TConvertAndSet`  
`template <typename SameType> struct TConvertAndSet<SameType, SameType>`  
_L2005-2013_
- L1983 _public function_ `TConvertAndSet(const TProperty_Numeric& Property, FStructuredArchive::FSlot Slot, void* Obj, const FPropertyTag& Tag)`
- L2007 _public function_ `inline TConvertAndSet(const TProperty_Numeric& Property, FStructuredArchive::FSlot Slot, void* Obj, const FPropertyTag& Tag)`

#### class `FByteProperty`  
`class FByteProperty : public TProperty_Numeric<uint8>`  
_L2190-2258_
- inherits: `TProperty_Numeric<uint8>`
- desc: Describes an unsigned byte value or 255-value enumeration variable.
- L2197 _private prototype_ `FByteProperty(FFieldVariant InOwner, const FName& InName);`
- L2199 _private function_ `FByteProperty(FFieldVariant InOwner, const FName& InName, EObjectFlags InObjectFlags) : FByteProperty(InOwner, InName)` — `UE_DEPRECATED(5.8, "FByteProperty constructor with InObjectFlags is deprecated, remove that parameter.")`
- L2206 _private prototype_ `FByteProperty(FFieldVariant InOwner, const UECodeGen_Private::FBytePropertyParams& Prop);` — Constructor used for constructing compiled in properties @param InOwner Owner of the property @param PropBase Pointer to the compiled in structure describing the property
- L2209 _private function_ `explicit consteval FByteProperty(UE::CodeGen::ConstInit::FPropertyParams InBaseParams, UE::CodeGen::ConstInit::TObjectRefParam<UEnum> InEnum) : Super(InBaseParams) , Enum(InEnum)`
- L2217 _private prototype_ `explicit FByteProperty(UField* InField);`
- L2221 _private prototype_ `virtual void Serialize( FArchive& Ar ) override;` — UObject interface.
- L2222 _private prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;`
- L2223 _private prototype_ `virtual void GetPreloadDependencies(TArray<UObject*>& OutDeps) override;`
- L2225 _private prototype_ `virtual void LinkCompiledInPointerFields(UE::CoreUObject::Private::FCompiledInObjectLinker& Linker);`
- L2230 _private prototype_ `virtual void PostDuplicate(const FField& InField) override;` — Field interface
- L2233 _private prototype_ `virtual FString GetCPPType( FString* ExtendedTypeText=NULL, uint32 CPPExportFlags=0 ) const override;` — UHT interface
- L2237 _private prototype_ `virtual void SerializeItem(FStructuredArchive::FSlot Slot, TNotNull<void*> Value, void const* Defaults) const override;` — FProperty interface.
- L2238 _private prototype_ `virtual bool NetSerializeItem(FArchive& Ar, UPackageMap* Map, TNotNull<void*> Data, TArray<uint8> * MetaData = nullptr) const override;`
- L2240 _protected prototype_ `virtual void ExportText_Internal( FString& ValueStr, TNotNull<const void*> PropertyValueOrContainer, EPropertyPointerType PropertyPointerType, const void* DefaultValue, UObject* Parent, int32 PortFlags, UObject* ExportRootScope ) const override;`
- L2241 _protected prototype_ `virtual const TCHAR* ImportText_Internal(const TCHAR* Buffer, TNotNull<void*> ContainerOrPropertyPtr, EPropertyPointerType PropertyPointerType, UObject* Parent, int32 PortFlags, FOutputDevice* ErrorText) const override;`
- L2243 _public prototype_ `virtual EConvertFromTypeResult ConvertFromType(const FPropertyTag& Tag, FStructuredArchive::FSlot Slot, uint8* Data, const UStruct* DefaultsStruct, const uint8* Defaults) override;`
- L2245 _public prototype_ `virtual void AppendSchemaHash(FBlake3& Builder, bool bSkipEditorOnly) const override;`
- L2247 _public prototype_ `virtual bool LoadTypeName(UE::FPropertyTypeName Type, const FPropertyTag* Tag = nullptr) override;`
- L2248 _public prototype_ `virtual void SaveTypeName(UE::FPropertyTypeNameBuilder& Type) const override;`
- L2249 _public prototype_ `virtual bool CanSerializeFromTypeName(UE::FPropertyTypeName Type) const override;`
- L2253 _public prototype_ `virtual UEnum* GetIntPropertyEnum() const override;` — FNumericProperty interface.
- L2257 _public prototype_ `uint64 GetMaxNetSerializeBits() const;` — Returns the number of bits required by NetSerializeItem to encode this property (may be fewer than 8 if this byte represents an enum)

#### class `FInt8Property`  
`class FInt8Property : public TProperty_Numeric<int8>`  
_L2267-2292_
- inherits: `TProperty_Numeric<int8>`
- desc: Describes a 8-bit signed integer variable.
- L2273 _private function_ `FInt8Property(FFieldVariant InOwner, const FName& InName, EObjectFlags InObjectFlags) : FInt8Property(InOwner, InName)` — `UE_DEPRECATED(5.8, "FInt8Property constructor with InObjectFlags is deprecated, remove that parameter.")`
- L2280 _private prototype_ `FInt8Property(FFieldVariant InOwner, const UECodeGen_Private::FInt8PropertyParams& Prop);` — Constructor used for constructing compiled in properties @param InOwner Owner of the property @param PropBase Pointer to the compiled in structure describing the property
- L2283 _private function_ `explicit consteval FInt8Property(UE::CodeGen::ConstInit::FPropertyParams InBaseParams) : Super(InBaseParams)`
- L2290 _private prototype_ `explicit FInt8Property(UField* InField);`

#### class `FInt16Property`  
`class FInt16Property : public TProperty_Numeric<int16>`  
_L2301-2326_
- inherits: `TProperty_Numeric<int16>`
- desc: Describes a 16-bit signed integer variable.
- L2307 _private function_ `FInt16Property(FFieldVariant InOwner, const FName& InName, EObjectFlags InObjectFlags) : FInt16Property(InOwner, InName)` — `UE_DEPRECATED(5.8, "FInt16Property constructor with InObjectFlags is deprecated, remove that parameter.")`
- L2314 _private prototype_ `FInt16Property(FFieldVariant InOwner, const UECodeGen_Private::FInt16PropertyParams& Prop);` — Constructor used for constructing compiled in properties @param InOwner Owner of the property @param PropBase Pointer to the compiled in structure describing the property
- L2317 _private function_ `explicit consteval FInt16Property(UE::CodeGen::ConstInit::FPropertyParams InBaseParams) : Super(InBaseParams)`
- L2324 _private prototype_ `explicit FInt16Property(UField* InField);`

#### class `FIntProperty`  
`class FIntProperty : public TProperty_Numeric<int32>`  
_L2336-2361_
- inherits: `TProperty_Numeric<int32>`
- desc: Describes a 32-bit signed integer variable.
- L2342 _private function_ `FIntProperty(FFieldVariant InOwner, const FName& InName, EObjectFlags InObjectFlags) : FIntProperty(InOwner, InName)` — `UE_DEPRECATED(5.8, "FIntProperty constructor with InObjectFlags is deprecated, remove that parameter.")`
- L2349 _private prototype_ `FIntProperty(FFieldVariant InOwner, const UECodeGen_Private::FIntPropertyParams& Prop);` — Constructor used for constructing compiled in properties @param InOwner Owner of the property @param PropBase Pointer to the compiled in structure describing the property
- L2352 _private function_ `explicit consteval FIntProperty(UE::CodeGen::ConstInit::FPropertyParams InBaseParams) : Super(InBaseParams)`
- L2359 _private prototype_ `explicit FIntProperty(UField* InField);`

#### class `FInt64Property`  
`class FInt64Property : public TProperty_Numeric<int64>`  
_L2370-2395_
- inherits: `TProperty_Numeric<int64>`
- desc: Describes a 64-bit signed integer variable.
- L2376 _private function_ `FInt64Property(FFieldVariant InOwner, const FName& InName, EObjectFlags InObjectFlags) : FInt64Property(InOwner, InName)` — `UE_DEPRECATED(5.8, "FInt64Property constructor with InObjectFlags is deprecated, remove that parameter.")`
- L2383 _private prototype_ `FInt64Property(FFieldVariant InOwner, const UECodeGen_Private::FInt64PropertyParams& Prop);` — Constructor used for constructing compiled in properties @param InOwner Owner of the property @param PropBase Pointer to the compiled in structure describing the property
- L2386 _private function_ `explicit consteval FInt64Property(UE::CodeGen::ConstInit::FPropertyParams InBaseParams) : Super(InBaseParams)`
- L2393 _private prototype_ `explicit FInt64Property(UField* InField);`

#### class `FUInt16Property`  
`class FUInt16Property : public TProperty_Numeric<uint16>`  
_L2404-2429_
- inherits: `TProperty_Numeric<uint16>`
- desc: Describes a 16-bit unsigned integer variable.
- L2410 _private function_ `FUInt16Property(FFieldVariant InOwner, const FName& InName, EObjectFlags InObjectFlags) : FUInt16Property(InOwner, InName)` — `UE_DEPRECATED(5.8, "FUInt16Property constructor with InObjectFlags is deprecated, remove that parameter.")`
- L2417 _private prototype_ `FUInt16Property(FFieldVariant InOwner, const UECodeGen_Private::FUInt16PropertyParams& Prop);` — Constructor used for constructing compiled in properties @param InOwner Owner of the property @param PropBase Pointer to the compiled in structure describing the property
- L2420 _private function_ `explicit consteval FUInt16Property(UE::CodeGen::ConstInit::FPropertyParams InBaseParams) : Super(InBaseParams)`
- L2427 _private prototype_ `explicit FUInt16Property(UField* InField);`

#### class `FUInt32Property`  
`class FUInt32Property : public TProperty_Numeric<uint32>`  
_L2438-2463_
- inherits: `TProperty_Numeric<uint32>`
- desc: Describes a 32-bit unsigned integer variable.
- L2444 _private function_ `FUInt32Property(FFieldVariant InOwner, const FName& InName, EObjectFlags InObjectFlags) : FUInt32Property(InOwner, InName)` — `UE_DEPRECATED(5.8, "FUInt32Property constructor with InObjectFlags is deprecated, remove that parameter.")`
- L2451 _private prototype_ `FUInt32Property(FFieldVariant InOwner, const UECodeGen_Private::FUInt32PropertyParams& Prop);` — Constructor used for constructing compiled in properties @param InOwner Owner of the property @param PropBase Pointer to the compiled in structure describing the property
- L2454 _private function_ `explicit consteval FUInt32Property(UE::CodeGen::ConstInit::FPropertyParams InBaseParams) : Super(InBaseParams)`
- L2461 _private prototype_ `explicit FUInt32Property(UField* InField);`

#### class `FUInt64Property`  
`class FUInt64Property : public TProperty_Numeric<uint64>`  
_L2472-2497_
- inherits: `TProperty_Numeric<uint64>`
- desc: Describes a 64-bit unsigned integer variable.
- L2478 _private function_ `FUInt64Property(FFieldVariant InOwner, const FName& InName, EObjectFlags InObjectFlags) : FUInt64Property(InOwner, InName)` — `UE_DEPRECATED(5.8, "FUInt64Property constructor with InObjectFlags is deprecated, remove that parameter.")`
- L2485 _private prototype_ `FUInt64Property(FFieldVariant InOwner, const UECodeGen_Private::FUInt64PropertyParams& Prop);` — Constructor used for constructing compiled in properties @param InOwner Owner of the property @param PropBase Pointer to the compiled in structure describing the property
- L2488 _private function_ `explicit consteval FUInt64Property(UE::CodeGen::ConstInit::FPropertyParams InBaseParams) : Super(InBaseParams)`
- L2495 _private prototype_ `explicit FUInt64Property(UField* InField);`

#### class `FFloatProperty`  
`class FFloatProperty : public TProperty_Numeric<float>`  
_L2507-2538_
- inherits: `TProperty_Numeric<float>`
- desc: Describes an IEEE 32-bit floating point variable.
- L2513 _private function_ `FFloatProperty(FFieldVariant InOwner, const FName& InName, EObjectFlags InObjectFlags) : FFloatProperty(InOwner, InName)` — `UE_DEPRECATED(5.8, "FFloatProperty constructor with InObjectFlags is deprecated, remove that parameter.")`
- L2520 _private prototype_ `FFloatProperty(FFieldVariant InOwner, const UECodeGen_Private::FFloatPropertyParams& Prop);` — Constructor used for constructing compiled in properties @param InOwner Owner of the property @param PropBase Pointer to the compiled in structure describing the property
- L2523 _private function_ `explicit consteval FFloatProperty(UE::CodeGen::ConstInit::FPropertyParams InBaseParams) : Super(InBaseParams)`
- L2530 _private prototype_ `explicit FFloatProperty(UField* InField);`
- L2533 _private prototype_ `virtual bool Identical(TNotNull<const void*> A, const void* B, uint32 PortFlags) const override;`
- L2537 _protected prototype_ `virtual uint32 GetValueTypeHashInternal(const void* Src) const override;`

#### class `FDoubleProperty`  
`class FDoubleProperty : public TProperty_Numeric<double>`  
_L2547-2578_
- inherits: `TProperty_Numeric<double>`
- desc: Describes an IEEE 64-bit floating point variable.
- L2553 _private function_ `FDoubleProperty(FFieldVariant InOwner, const FName& InName, EObjectFlags InObjectFlags) : FDoubleProperty(InOwner, InName)` — `UE_DEPRECATED(5.8, "FDoubleProperty constructor with InObjectFlags is deprecated, remove that parameter.")`
- L2560 _private prototype_ `FDoubleProperty(FFieldVariant InOwner, const UECodeGen_Private::FDoublePropertyParams& Prop);` — Constructor used for constructing compiled in properties @param InOwner Owner of the property @param PropBase Pointer to the compiled in structure describing the property
- L2563 _private function_ `explicit consteval FDoubleProperty(UE::CodeGen::ConstInit::FPropertyParams InBaseParams) : Super(InBaseParams)`
- L2570 _private prototype_ `explicit FDoubleProperty(UField* InField);`
- L2573 _private prototype_ `virtual bool Identical(TNotNull<const void*> A, const void* B, uint32 PortFlags) const override;`
- L2577 _protected prototype_ `virtual uint32 GetValueTypeHashInternal(const void* Src) const override;`

#### class `FBoolProperty`  
`class FBoolProperty : public FProperty`  
_L2589-2764_
- inherits: `FProperty`
- desc: Describes a single bit flag variable residing in a 32-bit unsigned double word.
- L2597 _private member_ `uint8 FieldSize;` — Size of the bitfield/bool property. Equal to ElementSize but used to check if the property has been properly initialized (0-8, where 0 means uninitialized).
- L2599 _private member_ `uint8 ByteOffset;` — Offset from the memeber variable to the byte of the property (0-7).
- L2601 _private member_ `uint8 ByteMask;` — Mask of the byte with the property value.
- L2603 _private member_ `uint8 FieldMask;` — Mask of the field with the property value. Either equal to ByteMask or 255 in case of 'bool' type.
- L2607 _private member_ `void (*SetBitFunc)(void*) = nullptr;` — CONSTINIT_UOBJECT_TODO: Size increase
- L2612 _public prototype_ `FBoolProperty(FFieldVariant InOwner, const FName& InName);`
- L2614 _public function_ `FBoolProperty(FFieldVariant InOwner, const FName& InName, EObjectFlags InObjectFlags) : FBoolProperty(InOwner, InName)` — `UE_DEPRECATED(5.8, "FBoolProperty constructor with InObjectFlags is deprecated, remove that parameter.")`
- L2621 _public prototype_ `FBoolProperty(FFieldVariant InOwner, const UECodeGen_Private::FBoolPropertyParams& Prop);` — Constructor used for constructing compiled in properties @param InOwner Owner of the property @param PropBase Pointer to the compiled in structure describing the property
- L2624 _public function_ `explicit consteval FBoolProperty( UE::CodeGen::ConstInit::FPropertyParams InBaseParams, int32 InElementSize, bool bIsNativeBool, void (*InSetBitFunc)(void*) ) : Super(InBaseParams.SetElementSize(InElementSize)) , FieldSize(0) , ByteOffset(0) , ByteMask(1) , FieldMask(bIsNativeBool ? 0xFF : 1) , SetBitFunc(InSetBitFunc)`
- L2642 _public prototype_ `explicit FBoolProperty(UField* InField);`
- L2646 _public prototype_ `virtual void Serialize( FArchive& Ar ) override;` — UObject interface.
- L2650 _public prototype_ `virtual void PostDuplicate(const FField& InField) override;` — Field interface
- L2653 _public prototype_ `virtual FString GetCPPType( FString* ExtendedTypeText, uint32 CPPExportFlags ) const override;` — UHT interface
- L2654 _public prototype_ `virtual FString GetCPPMacroType( FString& ExtendedTypeText ) const override;`
- L2658 _public prototype_ `virtual void LinkInternal(FArchive& Ar) override;` — FProperty interface.
- L2659 _public prototype_ `virtual bool Identical(TNotNull<const void*> A, const void* B, uint32 PortFlags) const override;`
- L2660 _public prototype_ `virtual void SerializeItem(FStructuredArchive::FSlot Slot, TNotNull<void*> Value, void const* Defaults) const override;`
- L2661 _public prototype_ `virtual bool NetSerializeItem(FArchive& Ar, UPackageMap* Map, TNotNull<void*> Data, TArray<uint8> * MetaData = nullptr) const override;`
- L2663 _protected prototype_ `virtual void ExportText_Internal(FString& ValueStr, TNotNull<const void*> PropertyValueOrContainer, EPropertyPointerType PropertyPointerType, const void* DefaultValue, UObject* Parent, int32 PortFlags, UObject* ExportRootScope) const override;`
- L2664 _protected prototype_ `virtual const TCHAR* ImportText_Internal(const TCHAR* Buffer, TNotNull<void*> ContainerOrPropertyPtr, EPropertyPointerType PropertyPointerType, UObject* Parent, int32 PortFlags, FOutputDevice* ErrorText) const override;`
- L2666 _public prototype_ `virtual void CopyValuesInternal( void* Dest, void const* Src, int32 Count ) const override;`
- L2667 _public prototype_ `virtual void ClearValueInternal( void* Data ) const override;`
- L2668 _public prototype_ `virtual void InitializeValueInternal( void* Dest ) const override;`
- L2669 _public prototype_ `virtual int32 GetMinAlignment() const override;`
- L2670 _public prototype_ `virtual EConvertFromTypeResult ConvertFromType(const FPropertyTag& Tag, FStructuredArchive::FSlot Slot, uint8* Data, const UStruct* DefaultsStruct, const uint8* Defaults) override;`
- L2672 _public prototype_ `virtual void AppendSchemaHash(FBlake3& Builder, bool bSkipEditorOnly) const override;`
- L2677 _protected prototype_ `void DetermineBitfieldOffsetAndMask(uint32& Offset, uint32& BitMask, void (*SetBit)(void* Obj), SIZE_T SizeOf);`
- L2681 _public typedef_ `typedef bool TCppType;` — Emulate the CPP type API, see TPropertyTypeFundamentals this is incomplete as some operations make no sense for bitfields, for example they don't have a usable address
- L2682 _public function_ `inline bool GetPropertyValue(void const* A) const`
- L2688 _public function_ `UE_FORCEINLINE_HINT bool GetPropertyValue_InContainer(void const* A, int32 ArrayIndex = 0) const`
- L2692 _public function_ `static UE_FORCEINLINE_HINT bool GetDefaultPropertyValue()`
- L2696 _public function_ `UE_FORCEINLINE_HINT bool GetOptionalPropertyValue(void const* B) const`
- L2700 _public function_ `UE_FORCEINLINE_HINT bool GetOptionalPropertyValue_InContainer(void const* B, int32 ArrayIndex = 0) const`
- L2704 _public function_ `inline void SetPropertyValue(void* A, bool Value) const`
- L2710 _public function_ `UE_FORCEINLINE_HINT void SetPropertyValue_InContainer(void* A, bool Value, int32 ArrayIndex = 0) const`
- L2723 _public prototype_ `void SetBoolSize( const uint32 InSize, const bool bIsNativeBool = false, const uint32 InBitMask = 0 );` — Sets the bitfield/bool type and size. This function must be called before FBoolProperty can be used. @param InSize size of the bitfield/bool type. @param bIsNativeBool true if this property represents C++ bool type.
- L2728 _public function_ `UE_FORCEINLINE_HINT bool IsNativeBool() const` — If the return value is true this FBoolProperty represents C++ bool type.
- L2734 _public function_ `UE_FORCEINLINE_HINT uint8 GetFieldMask() const` — Return the the mask that defines the relevant bit for this boolean, or 0xFF if IsNativeBool() is true
- L2740 _public function_ `UE_FORCEINLINE_HINT uint8 GetByteOffset() const` — Return the byte offset from this property's storage type to the byte that FieldMask applies to. Only valid if IsNativeBool() is true.
- L2746 _public function_ `FORCEINLINE uint8 GetBoolFieldSize() const` — Return the FieldSize, for debugging purposes
- L2752 _public function_ `FORCEINLINE uint8 GetByteMask() const` — Return the ByteMask, for debugging purposes
- L2758 _public prototype_ `uint32 GetValueTypeHashInternal(const void* Src) const override;`
- L2760 _public function_ `virtual bool HasIntrusiveUnsetOptionalState() const override`

#### class `FObjectPropertyBase`  
`class FObjectPropertyBase : public FProperty`  
_L2773-3054_
- inherits: `FProperty`
- desc: Describes a reference variable to another object which may be nil.
- L2780 _public member_ `TObjectPtr<class UClass> PropertyClass;` — Variables.
- L2782 _public prototype_ `FObjectPropertyBase(FFieldVariant InOwner, const FName& InName);`
- L2784 _public function_ `FObjectPropertyBase(FFieldVariant InOwner, const FName& InName, EObjectFlags InObjectFlags) : FObjectPropertyBase(InOwner, InName)` — `UE_DEPRECATED(5.8, "FObjectPropertyBase constructor with InObjectFlags is deprecated, remove that parameter.")`
- L2791 _public prototype_ `FObjectPropertyBase(FFieldVariant InOwner, const UECodeGen_Private::FObjectPropertyParams& Prop, EPropertyFlags AdditionalPropertyFlags = CPF_None);` — Constructor used for constructing compiled-in properties @param InOwner Owner of the property @param PropBase Pointer to the compiled in structure describing the property
- L2792 _public prototype_ `FObjectPropertyBase(FFieldVariant InOwner, const UECodeGen_Private::FObjectPropertyParamsWithoutClass& Prop, EPropertyFlags AdditionalPropertyFlags = CPF_None);`
- L2796 _protected function_ `explicit consteval FObjectPropertyBase(UE::CodeGen::ConstInit::FPropertyParams InBaseParams, UE::CodeGen::ConstInit::TObjectRefParam<UClass> InPropertyClass) : Super(InBaseParams) , PropertyClass(InPropertyClass)`
- L2805 _public prototype_ `explicit FObjectPropertyBase(UField* InField);`
- L2809 _public prototype_ `virtual void Serialize( FArchive& Ar ) override;` — UObject interface
- L2810 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;`
- L2812 _public prototype_ `virtual void LinkCompiledInPointerFields(UE::CoreUObject::Private::FCompiledInObjectLinker& Linker);`
- L2817 _public prototype_ `virtual void PostDuplicate(const FField& InField) override;` — Field interface
- L2820 _public prototype_ `virtual bool Identical(TNotNull<const void*> A, const void* B, uint32 PortFlags ) const override;` — FProperty interface
- L2821 _public prototype_ `virtual bool NetSerializeItem(FArchive& Ar, UPackageMap* Map, TNotNull<void*> Data, TArray<uint8>* MetaData = nullptr) const override;`
- L2822 _public function_ `virtual bool SupportsNetSharedSerialization() const override`
- L2824 _protected prototype_ `virtual void ExportText_Internal(FString& ValueStr, TNotNull<const void*> PropertyValueOrContainer, EPropertyPointerType PropertyPointerType, const void* DefaultValue, UObject* Parent, int32 PortFlags, UObject* ExportRootScope) const override;`
- L2825 _protected prototype_ `virtual const TCHAR* ImportText_Internal(const TCHAR* Buffer, TNotNull<void*> ContainerOrPropertyPtr, EPropertyPointerType PropertyPointerType, UObject* OwnerObject, int32 PortFlags, FOutputDevice* ErrorText) const override;`
- L2827 _public prototype_ `virtual FName GetID() const override;`
- L2828 _public prototype_ `virtual void InstanceSubobjects( void* Data, void const* DefaultData, TNotNull<UObject*> Owner, struct FObjectInstancingGraph* InstanceGraph ) override;`
- L2829 _public prototype_ `virtual bool SameType(const FProperty* Other) const override;`
- L2830 _public prototype_ `virtual EPropertyVisitorControlFlow Visit(FPropertyVisitorContext& Context, const TFunctionRef<EPropertyVisitorControlFlow(const FPropertyVisitorContext& )> InFunc) const override;`
- L2831 _public prototype_ `virtual void* ResolveVisitedPathInfo(void* Data, const FPropertyVisitorInfo& Info) const override;`
- L2838 _public function_ `FString GetCPPTypeCustom(FString* ExtendedTypeText, uint32 CPPExportFlags, const FString& InnerNativeTypeName) const` — `UE_DEPRECATED(5.7, "GetCPPTypeCustom is deprecated, and object properties now implement GetCPPType directly.")`
- L2855 _public prototype_ `static bool ParseObjectPropertyValue( const FProperty* Property, UObject* OwnerObject, UClass* RequiredMetaClass, uint32 PortFlags, const TCHAR*& Buffer, TObjectPtr<UObject>& out_ResolvedValue, FUObjectSerializeContext* InSerializeContext = nullptr, bool bAllowAnyPackage = true );` — Parses a text buffer into an object reference. @param	Property			the property that the value is being importing to @param	OwnerObject			the object that is importing the value; used for determining search scope. @param	RequiredMetaClass	the meta-class for the object to find; if the object that is resolved is not of this class type, the result is NULL. @param	PortFlags			bitmask of EPropertyPortFlags that can modify the behavior of the search @param	Buffer				the text to parse; should point to a textual representation of an object reference.  Can be just the object name (either fully fully qualified or not), or can be formatted as a const object reference (i.e. SomeClass'SomePackage.TheObject') When the function returns, Buffer will be pointing to the first character after the object value text in the input stream. @param	ResolvedValue		receives the object that is resolved from the input text. @param InSerializeContext	Additional context when called during serialization @param bAllowAnyPackage		allows ignoring package name to find any object that happens to be loaded with the same name @return	true if the text is successfully resolved into a valid object reference of the correct type, false otherwise.
- L2856 _public prototype_ `static TObjectPtr<UObject> FindImportedObject( const FProperty* Property, UObject* OwnerObject, UClass* ObjectClass, UClass* RequiredMetaClass, const TCHAR* Text, uint32 PortFlags = 0, FUObjectSerializeContext* InSerializeContext = nullptr, bool bAllowAnyPackage = true );`
- L2866 _public prototype_ `static FString GetExportPath(const TObjectPtr<const UObject>& Object, const UObject* Parent = nullptr, const UObject* ExportRootScope = nullptr, const uint32 PortFlags = PPF_None);` — Returns the qualified export path for a given object, parent, and export root scope @param Object Object to get the export path for @param Parent Outer of the Object used as a root object for generating the Objects path name @param ExportRootScope Similar to Parent but used when exporting from one package or graph to another package or graph @param PortFlags Property port flags @return A string representing the export path of an object, usually in the form of /ClassPackage.ClassName'/Package/Path.Object'
- L2874 _public prototype_ `static FString GetExportPath(FTopLevelAssetPath ClassPathName, const FString& ObjectPathName);` — Returns the qualified export path given a class path name and object path name @param ClassPathName Class path name @param ObjectPathName of the Object used as a root object for generating the Objects path name @return A string representing the export path of an object in the form of /ClassPackage.ClassName'/Package/Path.Object'
- L2877 _public prototype_ `static bool StaticIdentical(UObject* A, UObject* B, uint32 PortFlags);` — Helper method for deep comparing objects
- L2879 _public function_ `virtual UObject* LoadObjectPropertyValue(const void* PropertyValueAddress) const`
- L2883 _public function_ `UE_FORCEINLINE_HINT UObject* LoadObjectPropertyValue_InContainer(const void* PropertyValueAddress, int32 ArrayIndex = 0) const`
- L2889 _protected prototype_ `virtual void SetObjectPropertyValueUnchecked(void* PropertyValueAddress, UObject* Value) const;`
- L2890 _protected prototype_ `virtual void SetObjectPtrPropertyValueUnchecked(void* PropertyValueAddress, TObjectPtr<UObject> Ptr) const;`
- L2891 _protected prototype_ `virtual void SetObjectPropertyValueUnchecked_InContainer(void* ContainerAddress, UObject* Value, int32 ArrayIndex = 0) const;`
- L2892 _protected prototype_ `virtual void SetObjectPtrPropertyValueUnchecked_InContainer(void* ContainerAddress, TObjectPtr<UObject> Ptr, int32 ArrayIndex = 0) const;`
- L2894 _public prototype_ `virtual UObject* GetObjectPropertyValue(const void* PropertyValueAddress) const;`
- L2895 _public prototype_ `virtual TObjectPtr<UObject> GetObjectPtrPropertyValue(const void* PropertyValueAddress) const;`
- L2896 _public prototype_ `virtual UObject* GetObjectPropertyValue_InContainer(const void* ContainerAddress, int32 ArrayIndex = 0) const;`
- L2897 _public prototype_ `virtual TObjectPtr<UObject> GetObjectPtrPropertyValue_InContainer(const void* ContainerAddress, int32 ArrayIndex = 0) const;`
- L2899 _public prototype_ `void SetObjectPropertyValue(void* PropertyValueAddress, UObject* Value) const;`
- L2900 _public prototype_ `void SetObjectPtrPropertyValue(void* PropertyValueAddress, TObjectPtr<UObject> Ptr) const;`
- L2901 _public prototype_ `void SetObjectPropertyValue_InContainer(void* ContainerAddress, UObject* Value, int32 ArrayIndex = 0) const;`
- L2902 _public prototype_ `void SetObjectPtrPropertyValue_InContainer(void* ContainerAddress, TObjectPtr<UObject> Ptr, int32 ArrayIndex = 0) const;`
- L2914 _public prototype_ `void SetPropertyClass(UClass* NewPropertyClass);`
- L2916 _public function_ `UE_FORCEINLINE_HINT void SetPropertyClass(UClass* NewPropertyClass)`
- L2919 _public prototype_ `virtual void CheckValidObject(void* ValueAddress, TObjectPtr<UObject> OldValue, const void* Defaults = nullptr) const;`
- L2920 _public prototype_ `virtual bool AllowObjectTypeReinterpretationTo(const FObjectPropertyBase* Other) const;`
- L2923 _protected prototype_ `virtual bool AllowCrossLevel() const;`
- L2934 _protected prototype_ `UObject* ConstructDefaultObjectValueIfNecessary(UObject* ExistingValue, FString* OutFailureReason = nullptr, const void* Defaults = nullptr) const;` — Constructs a new object if the existing one is missing or is not compatible with the property class Used for making sure non-nullable properties have valid values. @param ExistingValue Previous object value (can be null) @param OutFailureReason An optional output string describing the reason why null was returned. @param Defaults Defaults object to use when constructing the object value (can be null). @return Pointer that should be assigned to the property value, or null if a default value could not be created.
- L2940 _protected function_ `template <typename T, typename OutType> void GetWrappedUObjectPtrValues(OutType* OutObjects, const void* SrcAddress, EPropertyMemoryAccess SrcAccess, int32 ArrayIndex, int32 ArrayCount) const` — Helper functions for UObject property types that wrap the object pointer in a smart pointer
- L2998 _protected function_ `template <typename T, typename ValueType> void SetWrappedUObjectPtrValues(void* DestAddress, EPropertyMemoryAccess DestAccess, ValueType* InValues, int32 ArrayIndex, int32 ArrayCount) const`

#### class `TFObjectPropertyBase`  
`template<typename InTCppType> class TFObjectPropertyBase : public TProperty<InTCppType, FObjectPropertyBase>`  
_L3057-3123_
- inherits: `TProperty<InTCppType,FObjectPropertyBase>`
- L3060 _public typedef_ `typedef TProperty<InTCppType, FObjectPropertyBase> Super;`
- L3061 _public typedef_ `typedef InTCppType TCppType;`
- L3062 _public typedef_ `typedef typename Super::TTypeFundamentals TTypeFundamentals;`
- L3064 _public function_ `TFObjectPropertyBase(EInternal InInernal, FFieldClass* InClass) : Super(EC_InternalUseOnlyConstructor, InClass)`
- L3069 _public function_ `TFObjectPropertyBase(FFieldVariant InOwner, const FName& InName) : Super(InOwner, InName)`
- L3075 _public function_ `TFObjectPropertyBase(FFieldVariant InOwner, const FName& InName, EObjectFlags InObjectFlags) : TFObjectPropertyBase(InOwner, InName)` — `UE_DEPRECATED(5.8, "TFObjectPropertyBase constructor with InObjectFlags is deprecated, remove that parameter.")`
- L3082 _public function_ `TFObjectPropertyBase(FFieldVariant InOwner, const UECodeGen_Private::FObjectPropertyParams& Prop) : Super(InOwner, Prop)` — Constructor used for constructing compiled-in properties @param InOwner Owner of the property @param Prop Pointer to the compiled in structure describing the property
- L3093 _public function_ `TFObjectPropertyBase(FFieldVariant InOwner, const UECodeGen_Private::FObjectPropertyParamsWithoutClass& Prop, UClass* InClass) : Super(InOwner, Prop)` — Constructor used for constructing compiled-in properties @param InOwner Owner of the property @param Prop Pointer to the compiled in structure describing the property @param InClass Class of the object this property represents
- L3101 _protected function_ `explicit consteval TFObjectPropertyBase(UE::CodeGen::ConstInit::FPropertyParams InBaseParams, UE::CodeGen::ConstInit::TObjectRefParam<UClass> InPropertyClass) : Super(InBaseParams, InPropertyClass)`
- L3109 _public function_ `explicit TFObjectPropertyBase(UField* InField) : Super(InField)`
- L3116 _public function_ `virtual bool ContainsObjectReference(TArray<const FStructProperty*>& EncounteredStructProps, EPropertyObjectReferenceType InReferenceType = EPropertyObjectReferenceType::Strong) const override` — FProperty interface.

#### enum `EObjectPropertyOptions`  
`enum class EObjectPropertyOptions`  
_L3125-3129_
- L3127 _public enumerator_ `None = 0`
- L3128 _public enumerator_ `AllowNullValuesOnNonNullableProperty = 1`

#### class `FObjectProperty`  
`class FObjectProperty : public TFObjectPropertyBase<TObjectPtr<UObject>>`  
_L3135-3247_
- inherits: `TFObjectPropertyBase<TObjectPtr<UObject>>`
- desc: Describes a reference variable to another object which may be nil.
- L3141 _private function_ `FObjectProperty(FFieldVariant InOwner, const FName& InName, EObjectFlags InObjectFlags) : FObjectProperty(InOwner, InName)` — `UE_DEPRECATED(5.8, "FObjectProperty constructor with InObjectFlags is deprecated, remove that parameter.")`
- L3148 _private prototype_ `FObjectProperty(FFieldVariant InOwner, const UECodeGen_Private::FObjectPropertyParams& Prop);` — Constructor used for constructing compiled in properties @param InOwner Owner of the property @param PropBase Pointer to the compiled in structure describing the property
- L3151 _private function_ `explicit consteval FObjectProperty(UE::CodeGen::ConstInit::FPropertyParams InBaseParams, UE::CodeGen::ConstInit::TObjectRefParam<UClass> PropertyClass) : Super(InBaseParams, PropertyClass)`
- L3158 _private prototype_ `explicit FObjectProperty(UField* InField);`
- L3162 _private prototype_ `virtual FString GetCPPType(FString* ExtendedTypeText, uint32 CPPExportFlags) const override;` — UHT interface
- L3163 _private prototype_ `virtual FString GetCPPMacroType( FString& ExtendedTypeText ) const override;`
- L3167 _private prototype_ `virtual void SerializeItem(FStructuredArchive::FSlot Slot, TNotNull<void*> Value, void const* Defaults) const override;` — FProperty interface
- L3169 _private prototype_ `virtual bool NetSerializeItem(FArchive& Ar, UPackageMap* Map, TNotNull<void*> Data, TArray<uint8>* MetaData = nullptr) const override;`
- L3171 _private prototype_ `virtual void EmitReferenceInfo(UE::GC::FSchemaBuilder& Schema, int32 BaseOffset, TArray<const FStructProperty*>& EncounteredStructProps, UE::GC::FPropertyStack& DebugPath) override;`
- L3172 _private prototype_ `virtual const TCHAR* ImportText_Internal(const TCHAR* Buffer, TNotNull<void*> ContainerOrPropertyPtr, EPropertyPointerType PropertyPointerType, UObject* OwnerObject, int32 PortFlags, FOutputDevice* ErrorText) const override;`
- L3173 _private prototype_ `virtual EConvertFromTypeResult ConvertFromType(const FPropertyTag& Tag, FStructuredArchive::FSlot Slot, uint8* Data, const UStruct* DefaultsStruct, const uint8* Defaults) override;`
- L3174 _private prototype_ `virtual bool AllowCrossLevel() const override;`
- L3176 _private prototype_ `virtual uint32 GetValueTypeHashInternal(const void* Src) const override;`
- L3177 _private prototype_ `virtual void CopyValuesInternal(void* Dest, void const* Src, int32 Count) const override;`
- L3179 _public prototype_ `virtual void CopySingleValueToScriptVM( void* Dest, void const* Src ) const override;`
- L3180 _public prototype_ `virtual void CopySingleValueFromScriptVM( void* Dest, void const* Src ) const override;`
- L3181 _public prototype_ `virtual void CopyCompleteValueToScriptVM( void* Dest, void const* Src ) const override;`
- L3182 _public prototype_ `virtual void CopyCompleteValueFromScriptVM( void* Dest, void const* Src ) const override;`
- L3183 _public prototype_ `virtual void CopyCompleteValueToScriptVM_InContainer( void* OutValue, void const* InContainer ) const override;`
- L3184 _public prototype_ `virtual void CopyCompleteValueFromScriptVM_InContainer( void* OutContainer, void const* InValue ) const override;`
- L3185 _public prototype_ `virtual bool Identical(TNotNull<const void*> A, const void* B, uint32 PortFlags) const override;`
- L3189 _public prototype_ `virtual UObject* GetObjectPropertyValue(const void* PropertyValueAddress) const override;` — FObjectPropertyBase interface
- L3190 _public prototype_ `virtual TObjectPtr<UObject> GetObjectPtrPropertyValue(const void* PropertyValueAddress) const override;`
- L3191 _public prototype_ `virtual UObject* GetObjectPropertyValue_InContainer(const void* ContainerAddress, int32 ArrayIndex = 0) const override;`
- L3192 _public prototype_ `virtual TObjectPtr<UObject> GetObjectPtrPropertyValue_InContainer(const void* ContainerAddress, int32 ArrayIndex = 0) const override;`
- L3194 _protected prototype_ `virtual void SetObjectPropertyValueUnchecked(void* PropertyValueAddress, UObject* Value) const override;`
- L3195 _protected prototype_ `virtual void SetObjectPtrPropertyValueUnchecked(void* PropertyValueAddress, TObjectPtr<UObject> Ptr) const override;`
- L3196 _protected prototype_ `virtual void SetObjectPropertyValueUnchecked_InContainer(void* ContainerAddress, UObject* Value, int32 ArrayIndex = 0) const override;`
- L3197 _protected prototype_ `virtual void SetObjectPtrPropertyValueUnchecked_InContainer(void* ContainerAddress, TObjectPtr<UObject> Ptr, int32 ArrayIndex = 0) const override;`
- L3209 _public prototype_ `void PostSerializeObjectItem(FArchive& SerializingArchive, void* Value, UObject* CurrentValue, UObject* ObjectValue, EObjectPropertyOptions Options = EObjectPropertyOptions::None, const void* Defaults = nullptr) const;` — Performs post serialization steps after loading a property value @param SerializingArchive Archive used for serialization @param Value Property address @param CurrentValue Current Object value @param ObjectValue Deserialized Object value @param Defaults Defaults used during serialization
- L3211 _public function_ `inline TObjectPtr<UObject>* GetObjectPtrPropertyValuePtr(const void* PropertyValueAddress) const`
- L3216 _public function_ `inline TObjectPtr<UObject>& GetObjectPtrPropertyValueRef(const void* PropertyValueAddress) const`
- L3221 _public function_ `virtual bool HasIntrusiveUnsetOptionalState() const`
- L3229 _public function_ `virtual void InitializeIntrusiveUnsetOptionalValue(void* Data) const override`
- L3234 _public function_ `virtual bool IsIntrusiveOptionalValueSet(const void* Data) const`
- L3240 _public function_ `virtual void ClearIntrusiveOptionalValue(void* Data) const`
- L3246 _public prototype_ `virtual void EmitIntrusiveOptionalReferenceInfo(UE::GC::FSchemaBuilder& Schema, int32 BaseOffset, TArray<const FStructProperty*>& EncounteredStructProps, UE::GC::FPropertyStack& DebugPath) override;`

#### class `FWeakObjectProperty`  
`class FWeakObjectProperty : public TFObjectPropertyBase<FWeakObjectPtr>`  
_L3252-3314_
- inherits: `TFObjectPropertyBase<FWeakObjectPtr>`
- desc: Describes a reference variable to another object which may be nil, and may turn nil at any point
- L3258 _private function_ `FWeakObjectProperty(FFieldVariant InOwner, const FName& InName, EObjectFlags InObjectFlags) : FWeakObjectProperty(InOwner, InName)` — `UE_DEPRECATED(5.8, "FWeakObjectProperty constructor with InObjectFlags is deprecated, remove that parameter.")`
- L3265 _private prototype_ `FWeakObjectProperty(FFieldVariant InOwner, const UECodeGen_Private::FWeakObjectPropertyParams& Prop);` — Constructor used for constructing compiled in properties @param InOwner Owner of the property @param PropBase Pointer to the compiled in structure describing the property
- L3268 _private function_ `explicit consteval FWeakObjectProperty(UE::CodeGen::ConstInit::FPropertyParams InBaseParams, UE::CodeGen::ConstInit::TObjectRefParam<UClass> PropertyClass) : Super(InBaseParams, PropertyClass)`
- L3275 _private prototype_ `explicit FWeakObjectProperty(UField* InField);`
- L3279 _private prototype_ `virtual FString GetCPPMacroType( FString& ExtendedTypeText ) const override;` — UHT interface
- L3280 _private prototype_ `virtual FString GetCPPType( FString* ExtendedTypeText, uint32 CPPExportFlags ) const override;`
- L3284 _private prototype_ `virtual void SerializeItem(FStructuredArchive::FSlot Slot, TNotNull<void*> Value, void const* Defaults) const override;` — FProperty interface
- L3286 _private prototype_ `virtual bool Identical(TNotNull<const void*> A, const void* B, uint32 PortFlags) const override;`
- L3287 _private prototype_ `virtual bool NetSerializeItem(FArchive& Ar, UPackageMap* Map, TNotNull<void*> Data, TArray<uint8>* MetaData = nullptr) const override;`
- L3290 _protected prototype_ `virtual void LinkInternal(FArchive& Ar) override;`
- L3292 _private prototype_ `virtual uint32 GetValueTypeHashInternal(const void* Src) const override;`
- L3294 _public prototype_ `virtual void CopySingleValueToScriptVM( void* Dest, void const* Src ) const override;`
- L3295 _public prototype_ `virtual void CopySingleValueFromScriptVM( void* Dest, void const* Src ) const override;`
- L3296 _public prototype_ `virtual void CopyCompleteValueToScriptVM( void* Dest, void const* Src ) const override;`
- L3297 _public prototype_ `virtual void CopyCompleteValueFromScriptVM( void* Dest, void const* Src ) const override;`
- L3298 _public prototype_ `virtual void CopyCompleteValueToScriptVM_InContainer( void* OutValue, void const* InContainer ) const override;`
- L3299 _public prototype_ `virtual void CopyCompleteValueFromScriptVM_InContainer( void* OutContainer, void const* InValue ) const override;`
- L3303 _public prototype_ `virtual UObject* GetObjectPropertyValue(const void* PropertyValueAddress) const override;` — FObjectProperty interface
- L3304 _public prototype_ `virtual TObjectPtr<UObject> GetObjectPtrPropertyValue(const void* PropertyValueAddress) const override;`
- L3305 _public prototype_ `virtual UObject* GetObjectPropertyValue_InContainer(const void* ContainerAddress, int32 ArrayIndex = 0) const override;`
- L3306 _public prototype_ `virtual TObjectPtr<UObject> GetObjectPtrPropertyValue_InContainer(const void* ContainerAddress, int32 ArrayIndex = 0) const override;`
- L3308 _protected prototype_ `virtual void SetObjectPropertyValueUnchecked(void* PropertyValueAddress, UObject* Value) const override;`
- L3309 _protected prototype_ `virtual void SetObjectPtrPropertyValueUnchecked(void* PropertyValueAddress, TObjectPtr<UObject> Ptr) const override;`
- L3310 _protected prototype_ `virtual void SetObjectPropertyValueUnchecked_InContainer(void* ContainerAddress, UObject* Value, int32 ArrayIndex = 0) const override;`
- L3311 _protected prototype_ `virtual void SetObjectPtrPropertyValueUnchecked_InContainer(void* ContainerAddress, TObjectPtr<UObject> Ptr, int32 ArrayIndex = 0) const override;`

#### class `FLazyObjectProperty`  
`class FLazyObjectProperty : public TFObjectPropertyBase<FLazyObjectPtr>`  
_L3319-3378_
- inherits: `TFObjectPropertyBase<FLazyObjectPtr>`
- desc: Describes a reference variable to another object which may be nil, and will become valid or invalid at any point
- L3325 _private function_ `FLazyObjectProperty(FFieldVariant InOwner, const FName& InName, EObjectFlags InObjectFlags) : FLazyObjectProperty(InOwner, InName)` — `UE_DEPRECATED(5.8, "FLazyObjectProperty constructor with InObjectFlags is deprecated, remove that parameter.")`
- L3332 _private prototype_ `FLazyObjectProperty(FFieldVariant InOwner, const UECodeGen_Private::FLazyObjectPropertyParams& Prop);` — Constructor used for constructing compiled in properties @param InOwner Owner of the property @param PropBase Pointer to the compiled in structure describing the property
- L3335 _private prototype_ `explicit FLazyObjectProperty(UField* InField);`
- L3339 _private function_ `explicit consteval FLazyObjectProperty(UE::CodeGen::ConstInit::FPropertyParams InBaseParams, UE::CodeGen::ConstInit::TObjectRefParam<UClass> PropertyClass) : Super(InBaseParams, PropertyClass)`
- L3346 _private prototype_ `virtual FString GetCPPMacroType( FString& ExtendedTypeText ) const override;` — UHT interface
- L3347 _private prototype_ `virtual FString GetCPPType( FString* ExtendedTypeText, uint32 CPPExportFlags ) const override;`
- L3351 _private prototype_ `virtual FName GetID() const override;` — FProperty interface
- L3352 _private prototype_ `virtual bool Identical(TNotNull<const void*> A, const void* B, uint32 PortFlags) const override;`
- L3353 _private prototype_ `virtual void SerializeItem(FStructuredArchive::FSlot Slot, TNotNull<void*> Value, void const* Defaults) const override;`
- L3354 _private prototype_ `virtual void CopySingleValueToScriptVM( void* Dest, void const* Src ) const override;`
- L3355 _private prototype_ `virtual void CopySingleValueFromScriptVM( void* Dest, void const* Src ) const override;`
- L3356 _private prototype_ `virtual void CopyCompleteValueToScriptVM( void* Dest, void const* Src ) const override;`
- L3357 _private prototype_ `virtual void CopyCompleteValueFromScriptVM( void* Dest, void const* Src ) const override;`
- L3358 _private prototype_ `virtual void CopyCompleteValueToScriptVM_InContainer( void* OutValue, void const* InContainer ) const override;`
- L3359 _private prototype_ `virtual void CopyCompleteValueFromScriptVM_InContainer( void* OutContainer, void const* InValue ) const override;`
- L3363 _private prototype_ `virtual UObject* GetObjectPropertyValue(const void* PropertyValueAddress) const override;` — FObjectProperty interface
- L3364 _private prototype_ `virtual TObjectPtr<UObject> GetObjectPtrPropertyValue(const void* PropertyValueAddress) const override;`
- L3365 _private prototype_ `virtual UObject* GetObjectPropertyValue_InContainer(const void* ContainerAddress, int32 ArrayIndex = 0) const override;`
- L3366 _private prototype_ `virtual TObjectPtr<UObject> GetObjectPtrPropertyValue_InContainer(const void* ContainerAddress, int32 ArrayIndex = 0) const override;`
- L3368 _protected prototype_ `virtual void SetObjectPropertyValueUnchecked(void* PropertyValueAddress, UObject* Value) const override;`
- L3369 _protected prototype_ `virtual void SetObjectPtrPropertyValueUnchecked(void* PropertyValueAddress, TObjectPtr<UObject> Ptr) const override;`
- L3370 _protected prototype_ `virtual void SetObjectPropertyValueUnchecked_InContainer(void* ContainerAddress, UObject* Value, int32 ArrayIndex = 0) const override;`
- L3371 _protected prototype_ `virtual void SetObjectPtrPropertyValueUnchecked_InContainer(void* ContainerAddress, TObjectPtr<UObject> Ptr, int32 ArrayIndex = 0) const override;`
- L3373 _public prototype_ `virtual bool AllowCrossLevel() const override;`
- L3375 _private prototype_ `virtual uint32 GetValueTypeHashInternal(const void* Src) const override;`

#### class `FSoftObjectProperty`  
`class FSoftObjectProperty : public TFObjectPropertyBase<FSoftObjectPtr>`  
_L3383-3456_
- inherits: `TFObjectPropertyBase<FSoftObjectPtr>`
- desc: Describes a reference variable to another object which may be nil, and will become valid or invalid at any point
- L3389 _private function_ `FSoftObjectProperty(FFieldVariant InOwner, const FName& InName, EObjectFlags InObjectFlags) : FSoftObjectProperty(InOwner, InName)` — `UE_DEPRECATED(5.8, "FSoftObjectProperty constructor with InObjectFlags is deprecated, remove that parameter.")`
- L3396 _private prototype_ `FSoftObjectProperty(FFieldVariant InOwner, const UECodeGen_Private::FSoftObjectPropertyParams& Prop);` — Constructor used for constructing compiled-in properties @param InOwner Owner of the property @param PropBase Pointer to the compiled in structure describing the property
- L3404 _private prototype_ `FSoftObjectProperty(FFieldVariant InOwner, const UECodeGen_Private::FObjectPropertyParamsWithoutClass& Prop, UClass* InClass);` — Constructor used for constructing compiled-in properties @param InOwner Owner of the property @param PropBase Pointer to the compiled in structure describing the property @param Class Class of the object this property represents
- L3407 _private function_ `explicit consteval FSoftObjectProperty(UE::CodeGen::ConstInit::FPropertyParams InBaseParams, UE::CodeGen::ConstInit::TObjectRefParam<UClass> PropertyClass) : Super(InBaseParams, PropertyClass)`
- L3414 _private prototype_ `explicit FSoftObjectProperty(UField* InField);`
- L3418 _private prototype_ `virtual FString GetCPPMacroType( FString& ExtendedTypeText ) const override;` — UHT interface
- L3422 _private prototype_ `virtual FName GetID() const override;` — FProperty interface
- L3423 _private prototype_ `virtual bool Identical(TNotNull<const void*> A, const void* B, uint32 PortFlags) const override;`
- L3424 _private prototype_ `virtual void SerializeItem(FStructuredArchive::FSlot Slot, TNotNull<void*> Value, void const* Defaults) const override;`
- L3425 _private prototype_ `virtual bool NetSerializeItem(FArchive& Ar, UPackageMap* Map, TNotNull<void*> Data, TArray<uint8> * MetaData = nullptr) const override;`
- L3427 _protected prototype_ `virtual void LinkInternal(FArchive& Ar) override;`
- L3428 _protected prototype_ `virtual void ExportText_Internal(FString& ValueStr, TNotNull<const void*> PropertyValueOrContainer, EPropertyPointerType PropertyPointerType, const void* DefaultValue, UObject* Parent, int32 PortFlags, UObject* ExportRootScope) const override;`
- L3429 _protected prototype_ `virtual const TCHAR* ImportText_Internal(const TCHAR* Buffer, TNotNull<void*> ContainerOrPropertyPtr, EPropertyPointerType PropertyPointerType, UObject* OwnerObject, int32 PortFlags, FOutputDevice* ErrorText) const override;`
- L3431 _public prototype_ `virtual EConvertFromTypeResult ConvertFromType(const FPropertyTag& Tag, FStructuredArchive::FSlot Slot, uint8* Data, const UStruct* DefaultsStruct, const uint8* Defaults) override;`
- L3435 _public prototype_ `virtual UObject* LoadObjectPropertyValue(const void* PropertyValueAddress) const override;` — FObjectProperty interface
- L3437 _public prototype_ `virtual UObject* GetObjectPropertyValue(const void* PropertyValueAddress) const override;`
- L3438 _public prototype_ `virtual TObjectPtr<UObject> GetObjectPtrPropertyValue(const void* PropertyValueAddress) const override;`
- L3439 _public prototype_ `virtual UObject* GetObjectPropertyValue_InContainer(const void* ContainerAddress, int32 ArrayIndex = 0) const override;`
- L3440 _public prototype_ `virtual TObjectPtr<UObject> GetObjectPtrPropertyValue_InContainer(const void* ContainerAddress, int32 ArrayIndex = 0) const override;`
- L3442 _protected prototype_ `virtual void SetObjectPropertyValueUnchecked(void* PropertyValueAddress, UObject* Value) const override;`
- L3443 _protected prototype_ `virtual void SetObjectPtrPropertyValueUnchecked(void* PropertyValueAddress, TObjectPtr<UObject> Ptr) const override;`
- L3444 _protected prototype_ `virtual void SetObjectPropertyValueUnchecked_InContainer(void* ContainerAddress, UObject* Value, int32 ArrayIndex = 0) const override;`
- L3445 _protected prototype_ `virtual void SetObjectPtrPropertyValueUnchecked_InContainer(void* ContainerAddress, TObjectPtr<UObject> Ptr, int32 ArrayIndex = 0) const override;`
- L3447 _public prototype_ `virtual bool AllowCrossLevel() const override;`
- L3448 _public prototype_ `virtual FString GetCPPType(FString* ExtendedTypeText, uint32 CPPExportFlags) const override;`
- L3451 _private prototype_ `virtual uint32 GetValueTypeHashInternal(const void* Src) const override;`

#### class `FClassProperty`  
`class FClassProperty : public FObjectProperty`  
_L3465-3540_
- inherits: `FObjectProperty`
- desc: Describes a reference variable to another object which may be nil.
- L3473 _public prototype_ `FClassProperty(FFieldVariant InOwner, const FName& InName);`
- L3475 _public function_ `FClassProperty(FFieldVariant InOwner, const FName& InName, EObjectFlags InObjectFlags) : FClassProperty(InOwner, InName)` — `UE_DEPRECATED(5.8, "FClassProperty constructor with InObjectFlags is deprecated, remove that parameter.")`
- L3482 _public prototype_ `FClassProperty(FFieldVariant InOwner, const UECodeGen_Private::FClassPropertyParams& Prop);` — Constructor used for constructing compiled in properties @param InOwner Owner of the property @param PropBase Pointer to the compiled in structure describing the property
- L3485 _public function_ `explicit consteval FClassProperty( UE::CodeGen::ConstInit::FPropertyParams InBaseParams, UE::CodeGen::ConstInit::TObjectRefParam<UClass> InPropertyClass, UE::CodeGen::ConstInit::TObjectRefParam<UClass> InMetaClass ) : Super(InBaseParams, InPropertyClass) , MetaClass(InMetaClass)`
- L3497 _public prototype_ `explicit FClassProperty(UField* InField);`
- L3501 _public prototype_ `virtual void Serialize( FArchive& Ar ) override;` — UObject interface
- L3502 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;`
- L3504 _public prototype_ `virtual void LinkCompiledInPointerFields(UE::CoreUObject::Private::FCompiledInObjectLinker& Linker);`
- L3509 _public prototype_ `virtual void PostDuplicate(const FField& InField) override;` — Field Interface
- L3512 _public prototype_ `virtual FString GetCPPType(FString* ExtendedTypeText, uint32 CPPExportFlags) const override;` — UHT interface
- L3513 _public prototype_ `virtual FString GetCPPMacroType( FString& ExtendedTypeText ) const override;`
- L3517 _public prototype_ `virtual const TCHAR* ImportText_Internal(const TCHAR* Buffer, TNotNull<void*> ContainerOrPropertyPtr, EPropertyPointerType PropertyPointerType, UObject* OwnerObject, int32 PortFlags, FOutputDevice* ErrorText) const override;` — FProperty interface
- L3518 _public prototype_ `virtual bool SameType(const FProperty* Other) const override;`
- L3519 _public prototype_ `virtual bool Identical(TNotNull<const void*> A, const void* B, uint32 PortFlags ) const override;`
- L3521 _public prototype_ `virtual void AppendSchemaHash(FBlake3& Builder, bool bSkipEditorOnly) const override;`
- L3536 _public prototype_ `void SetMetaClass(UClass* NewMetaClass);`
- L3538 _public function_ `UE_FORCEINLINE_HINT void SetMetaClass(UClass* NewMetaClass)`

#### class `FSoftClassProperty`  
`class FSoftClassProperty : public FSoftObjectProperty`  
_L3550-3620_
- inherits: `FSoftObjectProperty`
- desc: Describes a reference variable to another class which may be nil, and will become valid or invalid at any point
- L3558 _public prototype_ `FSoftClassProperty(FFieldVariant InOwner, const FName& InName);`
- L3560 _public function_ `FSoftClassProperty(FFieldVariant InOwner, const FName& InName, EObjectFlags InObjectFlags) : FSoftClassProperty(InOwner, InName)` — `UE_DEPRECATED(5.8, "FSoftClassProperty constructor with InObjectFlags is deprecated, remove that parameter.")`
- L3567 _public prototype_ `FSoftClassProperty(FFieldVariant InOwner, const UECodeGen_Private::FSoftClassPropertyParams& Prop);` — Constructor used for constructing compiled in properties @param InOwner Owner of the property @param PropBase Pointer to the compiled in structure describing the property
- L3570 _public function_ `explicit consteval FSoftClassProperty( UE::CodeGen::ConstInit::FPropertyParams InBaseParams, UE::CodeGen::ConstInit::TObjectRefParam<UClass> ClassClass, UE::CodeGen::ConstInit::TObjectRefParam<UClass> InMetaClass ) : Super(InBaseParams, ClassClass) , MetaClass(InMetaClass)`
- L3582 _public prototype_ `explicit FSoftClassProperty(UField* InField);`
- L3586 _public prototype_ `virtual FString GetCPPType(FString* ExtendedTypeText, uint32 CPPExportFlags) const override;` — UHT interface
- L3587 _public prototype_ `virtual FString GetCPPMacroType( FString& ExtendedTypeText ) const override;`
- L3591 _public prototype_ `virtual void PostDuplicate(const FField& InField) override;` — Field Interface
- L3594 _public prototype_ `virtual void Serialize( FArchive& Ar ) override;` — UObject interface
- L3595 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;`
- L3597 _public prototype_ `virtual void LinkCompiledInPointerFields(UE::CoreUObject::Private::FCompiledInObjectLinker& Linker);`
- L3602 _public prototype_ `virtual bool SameType(const FProperty* Other) const override;` — FProperty interface
- L3616 _public prototype_ `void SetMetaClass(UClass* NewMetaClass);`
- L3618 _public function_ `UE_FORCEINLINE_HINT void SetMetaClass(UClass* NewMetaClass)`

#### class `FInterfaceProperty`  
`class FInterfaceProperty : public TProperty<FScriptInterface, FProperty>`  
_L3631-3713_
- inherits: `TProperty<FScriptInterface,FProperty>`
- L3639 _public typedef_ `typedef Super::TTypeFundamentals TTypeFundamentals;`
- L3640 _public typedef_ `typedef TTypeFundamentals::TCppType TCppType;`
- L3642 _public prototype_ `FInterfaceProperty(FFieldVariant InOwner, const FName& InName);`
- L3644 _public function_ `FInterfaceProperty(FFieldVariant InOwner, const FName& InName, EObjectFlags InObjectFlags) : FInterfaceProperty(InOwner, InName)` — `UE_DEPRECATED(5.8, "FInterfaceProperty constructor with InObjectFlags is deprecated, remove that parameter.")`
- L3651 _public prototype_ `FInterfaceProperty(FFieldVariant InOwner, const UECodeGen_Private::FInterfacePropertyParams& Prop);` — Constructor used for constructing compiled in properties @param InOwner Owner of the property @param PropBase Pointer to the compiled in structure describing the property
- L3654 _public function_ `explicit consteval FInterfaceProperty(UE::CodeGen::ConstInit::FPropertyParams InBaseParams, UE::CodeGen::ConstInit::TObjectRefParam<UClass> InInterfaceClass) : Super(InBaseParams) , InterfaceClass(InInterfaceClass)`
- L3662 _public prototype_ `explicit FInterfaceProperty(UField* InField);`
- L3666 _public prototype_ `virtual FString GetCPPMacroType( FString& ExtendedTypeText ) const override;` — UHT interface
- L3667 _public prototype_ `virtual FString GetCPPType( FString* ExtendedTypeText, uint32 CPPExportFlags ) const override;`
- L3671 _public prototype_ `virtual void PostDuplicate(const FField& InField) override;` — Field interface
- L3674 _public prototype_ `virtual void LinkInternal(FArchive& Ar) override;` — FProperty interface
- L3675 _public prototype_ `virtual bool Identical(TNotNull<const void*> A, const void* B, uint32 PortFlags) const override;`
- L3676 _public prototype_ `virtual void SerializeItem(FStructuredArchive::FSlot Slot, TNotNull<void*> Value, void const* Defaults) const override;`
- L3677 _public prototype_ `virtual bool NetSerializeItem(FArchive& Ar, UPackageMap* Map, TNotNull<void*> Data, TArray<uint8> * MetaData = nullptr) const override;`
- L3678 _public function_ `virtual bool SupportsNetSharedSerialization() const override`
- L3680 _protected prototype_ `virtual void ExportText_Internal( FString& ValueStr, TNotNull<const void*> PropertyValueOrContainer, EPropertyPointerType PropertyPointerType, const void* DefaultValue, UObject* Parent, int32 PortFlags, UObject* ExportRootScope ) const override;`
- L3681 _protected prototype_ `virtual const TCHAR* ImportText_Internal(const TCHAR* Buffer, TNotNull<void*> ContainerOrPropertyPtr, EPropertyPointerType PropertyPointerType, UObject* OwnerObject, int32 PortFlags, FOutputDevice* ErrorText) const override;`
- L3683 _public prototype_ `virtual bool ContainsObjectReference(TArray<const FStructProperty*>& EncounteredStructProps, EPropertyObjectReferenceType InReferenceType = EPropertyObjectReferenceType::Strong) const override;`
- L3684 _public prototype_ `virtual bool SameType(const FProperty* Other) const override;`
- L3686 _public prototype_ `virtual void AppendSchemaHash(FBlake3& Builder, bool bSkipEditorOnly) const override;`
- L3691 _public prototype_ `virtual void Serialize( FArchive& Ar ) override;` — UObject interface
- L3692 _public prototype_ `virtual void EmitReferenceInfo(UE::GC::FSchemaBuilder& Schema, int32 BaseOffset, TArray<const FStructProperty*>& EncounteredStructProps, UE::GC::FPropertyStack& DebugPath) override;`
- L3693 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;`
- L3695 _public prototype_ `virtual void LinkCompiledInPointerFields(UE::CoreUObject::Private::FCompiledInObjectLinker& Linker);`
- L3709 _public prototype_ `void SetInterfaceClass(UClass* NewInterfaceClass);`
- L3711 _public function_ `UE_FORCEINLINE_HINT void SetInterfaceClass(UClass* NewInterfaceClass)`

#### class `FNameProperty`  
`class FNameProperty : public TProperty_WithEqualityAndSerializer<FName, FProperty>`  
_L3723-3760_
- inherits: `TProperty_WithEqualityAndSerializer<FName,FProperty>`
- L3727 _public typedef_ `typedef Super::TTypeFundamentals TTypeFundamentals;`
- L3728 _public typedef_ `typedef TTypeFundamentals::TCppType TCppType;`
- L3730 _public prototype_ `FNameProperty(FFieldVariant InOwner, const FName& InName);`
- L3732 _public function_ `FNameProperty(FFieldVariant InOwner, const FName& InName, EObjectFlags InObjectFlags) : FNameProperty(InOwner, InName)` — `UE_DEPRECATED(5.8, "FNameProperty constructor with InObjectFlags is deprecated, remove that parameter.")`
- L3739 _public prototype_ `FNameProperty(FFieldVariant InOwner, const UECodeGen_Private::FNamePropertyParams& Prop);` — Constructor used for constructing compiled in properties @param InOwner Owner of the property @param PropBase Pointer to the compiled in structure describing the property
- L3742 _public function_ `explicit consteval FNameProperty(UE::CodeGen::ConstInit::FPropertyParams InBaseParams) : Super(InBaseParams)`
- L3749 _public prototype_ `explicit FNameProperty(UField* InField);`
- L3754 _protected prototype_ `virtual void ExportText_Internal(FString& ValueStr, TNotNull<const void*> PropertyValueOrContainer, EPropertyPointerType PropertyPointerType, const void* DefaultValue, UObject* Parent, int32 PortFlags, UObject* ExportRootScope) const override;`
- L3755 _protected prototype_ `virtual const TCHAR* ImportText_Internal(const TCHAR* Buffer, TNotNull<void*> ContainerOrPropertyPtr, EPropertyPointerType PropertyPointerType, UObject* OwnerObject, int32 PortFlags, FOutputDevice* ErrorText) const override;`
- L3757 _public prototype_ `virtual EConvertFromTypeResult ConvertFromType(const FPropertyTag& Tag, FStructuredArchive::FSlot Slot, uint8* Data, const UStruct* DefaultsStruct, const uint8* Defaults) override;`
- L3758 _public prototype_ `uint32 GetValueTypeHashInternal(const void* Src) const override;`

#### class `FArrayProperty`  
`class FArrayProperty : public TProperty<FScriptArray, FProperty>`  
_L3776-3913_
- inherits: `TProperty<FScriptArray,FProperty>`
- L3782 _private member_ `FProperty* Inner;`
- L3793 _public typedef_ `using TTypeFundamentals = Super::TTypeFundamentals;`
- L3794 _public typedef_ `using TCppType = TTypeFundamentals::TCppType;`
- L3796 _public prototype_ `FArrayProperty(FFieldVariant InOwner, const FName& InName, EArrayPropertyFlags InArrayPropertyFlags=EArrayPropertyFlags::None);`
- L3798 _public function_ `FArrayProperty(FFieldVariant InOwner, const FName& InName, EObjectFlags InObjectFlags, EArrayPropertyFlags InArrayPropertyFlags=EArrayPropertyFlags::None) : FArrayProperty(InOwner, InName, InArrayPropertyFlags)` — `UE_DEPRECATED(5.8, "FArrayProperty constructor with InObjectFlags is deprecated, remove that parameter.")`
- L3805 _public prototype_ `FArrayProperty(FFieldVariant InOwner, const UECodeGen_Private::FArrayPropertyParams& Prop);` — Constructor used for constructing compiled in properties @param InOwner Owner of the property @param PropBase Pointer to the compiled in structure describing the property
- L3808 _public function_ `explicit consteval FArrayProperty( UE::CodeGen::ConstInit::FPropertyParams InBaseParams, EArrayPropertyFlags InArrayFlags, FProperty* InInnerProperty ) : Super(InBaseParams) , ArrayFlags(InArrayFlags) , Inner(InInnerProperty)`
- L3818 _public prototype_ `virtual ~FArrayProperty();`
- L3821 _public prototype_ `explicit FArrayProperty(UField* InField);`
- L3825 _public prototype_ `virtual void Serialize( FArchive& Ar ) override;` — UObject interface
- L3826 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;`
- L3827 _public prototype_ `virtual void GetPreloadDependencies(TArray<UObject*>& OutDeps) override;`
- L3829 _public prototype_ `virtual void LinkCompiledInPointerFields(UE::CoreUObject::Private::FCompiledInObjectLinker& Linker);`
- L3834 _public prototype_ `virtual void PostDuplicate(const FField& InField) override;` — Field interface
- L3837 _public prototype_ `virtual void AddCppProperty(FProperty* Property) override;` — UField interface
- L3838 _public prototype_ `virtual FField* GetInnerFieldByName(const FName& InName) override;`
- L3839 _public prototype_ `virtual void GetInnerFields(TArray<FField*>& OutFields) override;`
- L3844 _public prototype_ `virtual FString GetCPPMacroType( FString& ExtendedTypeText ) const override;` — FProperty interface
- L3845 _public prototype_ `virtual FString GetCPPType( FString* ExtendedTypeText, uint32 CPPExportFlags ) const override;`
- L3846 _public prototype_ `virtual void LinkInternal(FArchive& Ar) override;`
- L3847 _public prototype_ `virtual bool Identical(TNotNull<const void*> A, const void* B, uint32 PortFlags) const override;`
- L3848 _public prototype_ `virtual void SerializeItem(FStructuredArchive::FSlot Slot, TNotNull<void*> Value, void const* Defaults) const override;`
- L3849 _public prototype_ `virtual bool NetSerializeItem( FArchive& Ar, UPackageMap* Map, TNotNull<void*> Data, TArray<uint8> * MetaData = NULL ) const override;`
- L3851 _protected prototype_ `virtual void ExportText_Internal(FString& ValueStr, TNotNull<const void*> PropertyValueOrContainer, EPropertyPointerType PropertyPointerType, const void* DefaultValue, UObject* Parent, int32 PortFlags, UObject* ExportRootScope ) const override;`
- L3852 _protected prototype_ `virtual const TCHAR* ImportText_Internal(const TCHAR* Buffer, TNotNull<void*> ContainerOrPropertyPtr, EPropertyPointerType PropertyPointerType, UObject* OwnerObject, int32 PortFlags, FOutputDevice* ErrorText) const override;`
- L3853 _protected prototype_ `virtual bool ContainsClearOnFinishDestroyInternal(TArray<const FStructProperty*>& EncounteredStructProps) const override;`
- L3854 _protected prototype_ `virtual void FinishDestroyInternal(void* Data) const override;`
- L3856 _public function_ `virtual void InitializeValueInternal(void* Dest) const override`
- L3873 _public prototype_ `virtual void CopyValuesInternal( void* Dest, void const* Src, int32 Count ) const override;`
- L3874 _public prototype_ `virtual void ClearValueInternal( void* Data ) const override;`
- L3875 _public prototype_ `virtual void DestroyValueInternal( void* Dest ) const override;`
- L3876 _public prototype_ `virtual void InstanceSubobjects( void* Data, void const* DefaultData, TNotNull<UObject*> Owner, struct FObjectInstancingGraph* InstanceGraph ) override;`
- L3877 _public prototype_ `virtual bool ContainsObjectReference(TArray<const FStructProperty*>& EncounteredStructProps, EPropertyObjectReferenceType InReferenceType = EPropertyObjectReferenceType::Strong) const override;`
- L3878 _public prototype_ `virtual void EmitReferenceInfo(UE::GC::FSchemaBuilder& Schema, int32 BaseOffset, TArray<const FStructProperty*>& EncounteredStructProps, UE::GC::FPropertyStack& DebugPath) override;`
- L3879 _public prototype_ `virtual bool SameType(const FProperty* Other) const override;`
- L3880 _public prototype_ `virtual EConvertFromTypeResult ConvertFromType(const FPropertyTag& Tag, FStructuredArchive::FSlot Slot, uint8* Data, const UStruct* DefaultsStruct, const uint8* Defaults) override;`
- L3882 _public function_ `virtual int32 GetMinAlignment() const override`
- L3888 _public prototype_ `virtual void* GetValueAddressAtIndex_Direct(const FProperty* Inner, void* InValueAddress, int32 Index) const override;`
- L3889 _public prototype_ `virtual bool UseBinaryOrNativeSerialization(const FArchive& Ar) const override;`
- L3890 _public prototype_ `virtual bool LoadTypeName(UE::FPropertyTypeName Type, const FPropertyTag* Tag = nullptr) override;`
- L3891 _public prototype_ `virtual void SaveTypeName(UE::FPropertyTypeNameBuilder& Type) const override;`
- L3892 _public prototype_ `virtual bool CanSerializeFromTypeName(UE::FPropertyTypeName Type) const override;`
- L3893 _public prototype_ `virtual EPropertyVisitorControlFlow Visit(FPropertyVisitorContext& Context, const TFunctionRef<EPropertyVisitorControlFlow(const FPropertyVisitorContext& )> InFunc) const override;`
- L3894 _public prototype_ `virtual void* ResolveVisitedPathInfo(void* Data, const FPropertyVisitorInfo& Info) const override;`
- L3897 _public prototype_ `FString GetCPPTypeCustom(FString* ExtendedTypeText, uint32 CPPExportFlags, const FString& InnerTypeText, const FString& InInnerExtendedTypeText) const;`
- L3900 _public prototype_ `static void ExportTextInnerItem(FString& ValueStr, const FProperty* Inner, const void* PropertyValue, int32 NumElements, const void* DefaultValue, int32 DefaultSize, UObject* Parent = nullptr, int32 PortFlags = 0, UObject* ExportRootScope = nullptr);` — Called by ExportText_Internal, but can also be used by a non-ArrayProperty whose ArrayDim is > 1.
- L3903 _public prototype_ `static const TCHAR* ImportTextInnerItem(const TCHAR* Buffer, const FProperty* Inner, void* Data, int32 PortFlags, UObject* OwnerObject, FScriptArrayHelper* ArrayHelper = nullptr, FOutputDevice* ErrorText = (FOutputDevice*)GWarn);` — Called by ImportTextItem, but can also be used by a non-ArrayProperty whose ArrayDim is > 1. ArrayHelper should be supplied by ArrayProperties and nullptr for fixed-size arrays.
- L3905 _public prototype_ `virtual void AppendSchemaHash(FBlake3& Builder, bool bSkipEditorOnly) const override;`
- L3908 _public prototype_ `virtual bool HasIntrusiveUnsetOptionalState() const override;`
- L3909 _public prototype_ `virtual void InitializeIntrusiveUnsetOptionalValue(void* Data) const override;`
- L3910 _public prototype_ `virtual bool IsIntrusiveOptionalValueSet(const void* Data) const override;`
- L3911 _public prototype_ `virtual void ClearIntrusiveOptionalValue(void* Data) const override;`
- L3912 _public prototype_ `virtual void EmitIntrusiveOptionalReferenceInfo(UE::GC::FSchemaBuilder& Schema, int32 BaseOffset, TArray<const FStructProperty*>& EncounteredStructProps, UE::GC::FPropertyStack& DebugPath) override;`

#### enum `FArrayProperty::(anonymous)`  
``  
_L3787-3791_

#### class `FMapProperty`  
`class FMapProperty : public TProperty<FScriptMap, FProperty>`  
_L3920-4108_
- inherits: `TProperty<FScriptMap,FProperty>`
- L3926 _private member_ `FProperty* ValueProp;`
- L3927 _private member_ `FScriptMapLayout MapLayout;`
- L3928 _private member_ `EMapPropertyFlags MapFlags;`
- L3931 _private function_ `template <typename CallableType> auto WithScriptMap(void* InMap, CallableType&& Callable) const`
- L3944 _public typedef_ `using TTypeFundamentals = Super::TTypeFundamentals;`
- L3945 _public typedef_ `using TCppType = TTypeFundamentals::TCppType;`
- L3947 _public prototype_ `FMapProperty(FFieldVariant InOwner, const FName& InName, EMapPropertyFlags InMapFlags=EMapPropertyFlags::None);`
- L3949 _public function_ `FMapProperty(FFieldVariant InOwner, const FName& InName, EObjectFlags InObjectFlags, EMapPropertyFlags InMapFlags=EMapPropertyFlags::None) : FMapProperty(InOwner, InName, InMapFlags)` — `UE_DEPRECATED(5.8, "FMapProperty constructor with InObjectFlags is deprecated, remove that parameter.")`
- L3956 _public prototype_ `FMapProperty(FFieldVariant InOwner, const UECodeGen_Private::FMapPropertyParams& Prop);` — Constructor used for constructing compiled in properties @param InOwner Owner of the property @param PropBase Pointer to the compiled in structure describing the property
- L3959 _public function_ `explicit consteval FMapProperty( UE::CodeGen::ConstInit::FPropertyParams InBaseParams, FProperty* InKeyProperty, FProperty* InValueProperty, EMapPropertyFlags InMapFlags, int32 InKeySize, int16 InKeyAlignment, int32 InValueSize, int16 InValueAlignment ) : Super(InBaseParams) , KeyProp(InKeyProperty) , ValueProp(InValueProperty) , MapLayout() , MapFlags(InMapFlags)`
- L3980 _public prototype_ `explicit FMapProperty(UField* InField);`
- L3983 _public prototype_ `virtual ~FMapProperty();`
- L3986 _public prototype_ `virtual void Serialize(FArchive& Ar) override;` — UObject interface
- L3987 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;`
- L3988 _public prototype_ `virtual void GetPreloadDependencies(TArray<UObject*>& OutDeps) override;`
- L3990 _public prototype_ `virtual void LinkCompiledInPointerFields(UE::CoreUObject::Private::FCompiledInObjectLinker& Linker);`
- L3995 _public prototype_ `virtual void PostDuplicate(const FField& InField) override;` — Field Interface
- L3996 _public prototype_ `virtual FField* GetInnerFieldByName(const FName& InName) override;`
- L3997 _public prototype_ `virtual void GetInnerFields(TArray<FField*>& OutFields) override;`
- L4000 _public prototype_ `virtual void AddCppProperty(FProperty* Property) override;` — UField interface
- L4004 _public prototype_ `virtual FString GetCPPMacroType(FString& ExtendedTypeText) const override;` — FProperty interface
- L4005 _public prototype_ `virtual FString GetCPPType(FString* ExtendedTypeText, uint32 CPPExportFlags) const override;`
- L4006 _public prototype_ `virtual void LinkInternal(FArchive& Ar) override;`
- L4007 _public prototype_ `virtual bool Identical(TNotNull<const void*> A, const void* B, uint32 PortFlags) const override;`
- L4008 _public prototype_ `virtual void SerializeItem(FStructuredArchive::FSlot Slot, TNotNull<void*> Value, void const* Defaults) const override;`
- L4009 _public prototype_ `virtual bool NetSerializeItem(FArchive& Ar, UPackageMap* Map, TNotNull<void*> Data, TArray<uint8> * MetaData = NULL) const override;`
- L4011 _protected prototype_ `virtual void ExportText_Internal(FString& ValueStr, TNotNull<const void*> PropertyValueOrContainer, EPropertyPointerType PropertyPointerType, const void* DefaultValue, UObject* Parent, int32 PortFlags, UObject* ExportRootScope) const override;`
- L4012 _protected prototype_ `virtual const TCHAR* ImportText_Internal(const TCHAR* Buffer, TNotNull<void*> ContainerOrPropertyPtr, EPropertyPointerType PropertyPointerType, UObject* OwnerObject, int32 PortFlags, FOutputDevice* ErrorText) const override;`
- L4013 _protected prototype_ `virtual bool ContainsClearOnFinishDestroyInternal(TArray<const FStructProperty*>& EncounteredStructProps) const override;`
- L4014 _protected prototype_ `virtual void FinishDestroyInternal(void* Data) const override;`
- L4016 _public function_ `virtual void InitializeValueInternal(void* Dest) const override`
- L4035 _public prototype_ `virtual void CopyValuesInternal(void* Dest, void const* Src, int32 Count) const override;`
- L4036 _public prototype_ `virtual void ClearValueInternal(void* Data) const override;`
- L4037 _public prototype_ `virtual void DestroyValueInternal(void* Dest) const override;`
- L4038 _public prototype_ `virtual void InstanceSubobjects(void* Data, void const* DefaultData, TNotNull<UObject*> Owner, struct FObjectInstancingGraph* InstanceGraph) override;`
- L4039 _public prototype_ `virtual bool ContainsObjectReference(TArray<const FStructProperty*>& EncounteredStructProps, EPropertyObjectReferenceType InReferenceType = EPropertyObjectReferenceType::Strong) const override;`
- L4040 _public prototype_ `virtual void EmitReferenceInfo(UE::GC::FSchemaBuilder& Schema, int32 BaseOffset, TArray<const FStructProperty*>& EncounteredStructProps, UE::GC::FPropertyStack& DebugPath) override;`
- L4041 _public prototype_ `virtual bool SameType(const FProperty* Other) const override;`
- L4042 _public prototype_ `virtual EConvertFromTypeResult ConvertFromType(const FPropertyTag& Tag, FStructuredArchive::FSlot Slot, uint8* Data, const UStruct* DefaultsStruct, const uint8* Defaults) override;`
- L4043 _public prototype_ `virtual void* GetValueAddressAtIndex_Direct(const FProperty* Inner, void* InValueAddress, int32 LogicalIndex) const override;`
- L4044 _public prototype_ `virtual bool UseBinaryOrNativeSerialization(const FArchive& Ar) const override;`
- L4045 _public prototype_ `virtual bool LoadTypeName(UE::FPropertyTypeName Type, const FPropertyTag* Tag = nullptr) override;`
- L4046 _public prototype_ `virtual void SaveTypeName(UE::FPropertyTypeNameBuilder& Type) const override;`
- L4047 _public prototype_ `virtual bool CanSerializeFromTypeName(UE::FPropertyTypeName Type) const override;`
- L4048 _public prototype_ `virtual EPropertyVisitorControlFlow Visit(FPropertyVisitorContext& Context, const TFunctionRef<EPropertyVisitorControlFlow(const FPropertyVisitorContext& )> InFunc) const override;`
- L4049 _public prototype_ `virtual void* ResolveVisitedPathInfo(void* Data, const FPropertyVisitorInfo& Info) const override;`
- L4052 _public prototype_ `FString GetCPPTypeCustom(FString* ExtendedTypeText, uint32 CPPExportFlags, const FString& KeyTypeText, const FString& InKeyExtendedTypeText, const FString& ValueTypeText, const FString& InValueExtendedTypeText) const;`
- L4058 _public function_ `int32 GetNum(void* InMap) const` — Helper function to get the number of key/value pairs inside of a map. Used by the garbage collector where for performance reasons the provided map pointer is not guarded
- L4067 _public function_ `int32 GetPairStride() const` — Helper function to get the sizeof of the map's key/value pair. Used by the garbage collector.
- L4076 _public function_ `bool IsValidIndex(void* InMap, int32 InternalIndex) const` — Helper function to check if the specified index of a key/value pair in the underlying set is valid. Used by the garbage collector where for performance reasons the provided map pointer is not guarded
- L4085 _public function_ `uint8* GetPairPtr(void* InMap, int32 InternalIndex) const` — Helper function to get the pointer to a key/value pair at the specified index. Used by the garbage collector where for performance reasons the provided map pointer is not guarded
- L4090 _public function_ `const FProperty* GetKeyProperty() const`
- L4095 _public function_ `const FProperty* GetValueProperty() const`
- L4100 _public prototype_ `virtual void AppendSchemaHash(FBlake3& Builder, bool bSkipEditorOnly) const override;`
- L4103 _public prototype_ `virtual bool HasIntrusiveUnsetOptionalState() const override;`
- L4104 _public prototype_ `virtual void InitializeIntrusiveUnsetOptionalValue(void* Data) const override;`
- L4105 _public prototype_ `virtual bool IsIntrusiveOptionalValueSet(const void* Data) const override;`
- L4106 _public prototype_ `virtual void ClearIntrusiveOptionalValue(void* Data) const override;`
- L4107 _public prototype_ `virtual void EmitIntrusiveOptionalReferenceInfo(UE::GC::FSchemaBuilder& Schema, int32 BaseOffset, TArray<const FStructProperty*>& EncounteredStructProps, UE::GC::FPropertyStack& DebugPath) override;`

#### class `FSetProperty`  
`class FSetProperty : public TProperty<FScriptSet, FProperty>`  
_L4110-4257_
- inherits: `TProperty<FScriptSet,FProperty>`
- L4116 _private member_ `FScriptSetLayout SetLayout;`
- L4119 _public typedef_ `using TTypeFundamentals = Super::TTypeFundamentals;`
- L4120 _public typedef_ `using TCppType = TTypeFundamentals::TCppType;`
- L4122 _public prototype_ `FSetProperty(FFieldVariant InOwner, const FName& InName);`
- L4124 _public function_ `FSetProperty(FFieldVariant InOwner, const FName& InName, EObjectFlags InObjectFlags) : FSetProperty(InOwner, InName)` — `UE_DEPRECATED(5.8, "FSetProperty constructor with InObjectFlags is deprecated, remove that parameter.")`
- L4131 _public prototype_ `FSetProperty(FFieldVariant InOwner, const UECodeGen_Private::FSetPropertyParams& Prop);` — Constructor used for constructing compiled in properties @param InOwner Owner of the property @param PropBase Pointer to the compiled in structure describing the property
- L4134 _public function_ `explicit consteval FSetProperty( UE::CodeGen::ConstInit::FPropertyParams InBaseParams, FProperty* InElementProperty, int32 InElementPropertySize, int32 InElementPropertyAlignment ) : Super(InBaseParams) , ElementProp(InElementProperty) , SetLayout(FScriptSet::GetScriptLayout(InElementPropertySize, InElementPropertyAlignment))`
- L4149 _public prototype_ `explicit FSetProperty(UField* InField);`
- L4152 _public prototype_ `virtual ~FSetProperty();`
- L4155 _public prototype_ `virtual void Serialize(FArchive& Ar) override;` — UObject interface
- L4156 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;`
- L4157 _public prototype_ `virtual void GetPreloadDependencies(TArray<UObject*>& OutDeps) override;`
- L4159 _public prototype_ `virtual void LinkCompiledInPointerFields(UE::CoreUObject::Private::FCompiledInObjectLinker& Linker);`
- L4164 _public prototype_ `virtual void PostDuplicate(const FField& InField) override;` — Field interface
- L4165 _public prototype_ `virtual FField* GetInnerFieldByName(const FName& InName) override;`
- L4166 _public prototype_ `virtual void GetInnerFields(TArray<FField*>& OutFields) override;`
- L4169 _public prototype_ `virtual void AddCppProperty(FProperty* Property) override;` — UField interface
- L4173 _public prototype_ `virtual FString GetCPPMacroType(FString& ExtendedTypeText) const override;` — FProperty interface
- L4174 _public prototype_ `virtual FString GetCPPType(FString* ExtendedTypeText, uint32 CPPExportFlags) const override;`
- L4175 _public prototype_ `virtual void LinkInternal(FArchive& Ar) override;`
- L4176 _public prototype_ `virtual bool Identical(TNotNull<const void*> A, const void* B, uint32 PortFlags) const override;`
- L4177 _public prototype_ `virtual void SerializeItem(FStructuredArchive::FSlot Slot, TNotNull<void*> Value, void const* Defaults) const override;`
- L4178 _public prototype_ `virtual bool NetSerializeItem(FArchive& Ar, UPackageMap* Map, TNotNull<void*> Data, TArray<uint8> * MetaData = NULL) const override;`
- L4180 _protected prototype_ `virtual void ExportText_Internal(FString& ValueStr, TNotNull<const void*> PropertyValueOrContainer, EPropertyPointerType PropertyPointerType, const void* DefaultValue, UObject* Parent, int32 PortFlags, UObject* ExportRootScope) const override;`
- L4181 _protected prototype_ `virtual const TCHAR* ImportText_Internal(const TCHAR* Buffer, TNotNull<void*> ContainerOrPropertyPtr, EPropertyPointerType PropertyPointerType, UObject* OwnerObject, int32 PortFlags, FOutputDevice* ErrorText) const override;`
- L4182 _protected prototype_ `virtual bool ContainsClearOnFinishDestroyInternal(TArray<const FStructProperty*>& EncounteredStructProps) const override;`
- L4183 _protected prototype_ `virtual void FinishDestroyInternal(void* Data) const override;`
- L4185 _public prototype_ `virtual void CopyValuesInternal(void* Dest, void const* Src, int32 Count) const override;`
- L4186 _public prototype_ `virtual void ClearValueInternal(void* Data) const override;`
- L4187 _public prototype_ `virtual void DestroyValueInternal(void* Dest) const override;`
- L4188 _public prototype_ `virtual void InstanceSubobjects(void* Data, void const* DefaultData, TNotNull<UObject*> Owner, struct FObjectInstancingGraph* InstanceGraph) override;`
- L4189 _public prototype_ `virtual bool ContainsObjectReference(TArray<const FStructProperty*>& EncounteredStructProps, EPropertyObjectReferenceType InReferenceType = EPropertyObjectReferenceType::Strong) const override;`
- L4190 _public prototype_ `virtual void EmitReferenceInfo(UE::GC::FSchemaBuilder& Schema, int32 BaseOffset, TArray<const FStructProperty*>& EncounteredStructProps, UE::GC::FPropertyStack& DebugPath) override;`
- L4191 _public prototype_ `virtual bool SameType(const FProperty* Other) const override;`
- L4192 _public prototype_ `virtual EConvertFromTypeResult ConvertFromType(const FPropertyTag& Tag, FStructuredArchive::FSlot Slot, uint8* Data, const UStruct* DefaultsStruct, const uint8* Defaults) override;`
- L4193 _public prototype_ `virtual void* GetValueAddressAtIndex_Direct(const FProperty* Inner, void* InValueAddress, int32 LogicalIndex) const override;`
- L4194 _public prototype_ `virtual bool UseBinaryOrNativeSerialization(const FArchive& Ar) const override;`
- L4195 _public prototype_ `virtual bool LoadTypeName(UE::FPropertyTypeName Type, const FPropertyTag* Tag = nullptr) override;`
- L4196 _public prototype_ `virtual void SaveTypeName(UE::FPropertyTypeNameBuilder& Type) const override;`
- L4197 _public prototype_ `virtual bool CanSerializeFromTypeName(UE::FPropertyTypeName Type) const override;`
- L4198 _public prototype_ `virtual EPropertyVisitorControlFlow Visit(FPropertyVisitorContext& Context, const TFunctionRef<EPropertyVisitorControlFlow(const FPropertyVisitorContext& )> InFunc) const override;`
- L4199 _public prototype_ `virtual void* ResolveVisitedPathInfo(void* Data, const FPropertyVisitorInfo& Info) const override;`
- L4202 _public prototype_ `FString GetCPPTypeCustom(FString* ExtendedTypeText, uint32 CPPExportFlags, const FString& ElementTypeText, const FString& InElementExtendedTypeText) const;`
- L4208 _public function_ `int32 GetNum(void* InSet) const` — Helper function to get the number of elements inside of a set. Used by the garbage collector where for performance reasons the provided set pointer is not guarded
- L4218 _public function_ `int32 GetStride() const` — Helper function to get the size of the set element. Used by the garbage collector.
- L4227 _public function_ `bool IsValidIndex(void* InSet, int32 InternalIndex) const` — Helper function to check if the specified index of an element is valid. Used by the garbage collector where for performance reasons the provided set pointer is not guarded
- L4237 _public function_ `uint8* GetElementPtr(void* InSet, int32 InternalIndex) const` — Helper function to get the pointer to an element at the specified index. Used by the garbage collector where for performance reasons the provided set pointer is not guarded
- L4243 _public function_ `const FProperty* GetElementProperty() const`
- L4249 _public prototype_ `virtual void AppendSchemaHash(FBlake3& Builder, bool bSkipEditorOnly) const override;`
- L4252 _public prototype_ `virtual bool HasIntrusiveUnsetOptionalState() const override;`
- L4253 _public prototype_ `virtual void InitializeIntrusiveUnsetOptionalValue(void* Data) const override;`
- L4254 _public prototype_ `virtual bool IsIntrusiveOptionalValueSet(const void* Data) const override;`
- L4255 _public prototype_ `virtual void ClearIntrusiveOptionalValue(void* Data) const override;`
- L4256 _public prototype_ `virtual void EmitIntrusiveOptionalReferenceInfo(UE::GC::FSchemaBuilder& Schema, int32 BaseOffset, TArray<const FStructProperty*>& EncounteredStructProps, UE::GC::FPropertyStack& DebugPath) override;`

#### class `FScriptArrayHelper`  
`class FScriptArrayHelper`  
_L4262-4649_
- desc: FScriptArrayHelper: Pseudo dynamic array. Used to work with array properties in a sensible way.
- L4267 _private function_ `template <typename CallableType> auto WithScriptArray(CallableType&& Callable) const`
- L4285 _public function_ `UE_FORCEINLINE_HINT FScriptArrayHelper(const FArrayProperty* InProperty, const void* InArray) : FScriptArrayHelper(Internal, InProperty->Inner, InArray, InProperty->Inner->GetElementSize(), InProperty->Inner->GetMinAlignment(), InProperty->ArrayFlags)` — Constructor, brings together a property and an instance of the property located in memory @param	InProperty: the property associated with this memory @param	InArray: pointer to raw memory that corresponds to this array. This can be NULL, and sometimes is, but in that case almost all operations will crash.
- L4295 _public function_ `UE_FORCEINLINE_HINT bool IsValidIndex( int32 Index ) const` — Index range check @param	Index: Index to check @return true if accessing this element is legal.
- L4303 _public function_ `inline int32 Num() const` — Return the number of elements in the array. @return	The number of elements in the array.
- L4314 _public function_ `inline int32 NumUnchecked() const` — Return the number of elements in the array without validating the state of the array. Needed to allow reading of the num when the array is 'invalid' during its intrusive unset state. @return	The number of elements in the array.
- L4324 _public function_ `inline uint8* GetRawPtr(int32 Index = 0)` — Returns a uint8 pointer to an element in the array @param	Index: index of the item to return a pointer to. @return	Pointer to this element, or NULL if the array is empty
- L4340 _public function_ `UE_FORCEINLINE_HINT uint8* GetElementPtr(int32 Index = 0)` — Returns a uint8 pointer to an element in the array. This call is identical to GetRawPtr and is here to provide interface parity with FScriptSetHelper*. @param	Index: index of the item to return a pointer to. @return	Pointer to this element, or NULL if the array is empty
- L4348 _public function_ `void EmptyAndAddValues(int32 Count)` — Empty the array, then add blank, constructed values to a given size. @param	Count: the number of items the array will have on completion.
- L4359 _public function_ `void EmptyAndAddUninitializedValues(int32 Count)` — Empty the array, then add uninitialized values to a given size. @param	Count: the number of items the array will have on completion.
- L4372 _public function_ `bool ExpandForIndex(int32 Index)` — Expand the array, if needed, so that the given index is valid @param	Index: index for the item that we want to ensure is valid @return true if expansion was necessary NOTE: This is not a count, it is an INDEX, so the final count will be at least Index+1 this matches the usage.
- L4387 _public function_ `void Resize(int32 Count)` — Add or remove elements to set the array to a given size. @param	Count: the number of items the array will have on completion.
- L4409 _public function_ `int32 AddValues(int32 Count)` — Add blank, constructed values to the end of the array. @param	Count: the number of items to insert. @return	the index of the first newly added item.
- L4419 _public function_ `UE_FORCEINLINE_HINT int32 AddValue()` — Add a blank, constructed values to the end of the array. @return	the index of the newly added item.
- L4428 _public function_ `int32 AddUninitializedValues(int32 Count)` — Add uninitialized values to the end of the array. @param	Count: the number of items to insert. @return	the index of the first newly added item.
- L4439 _public function_ `UE_FORCEINLINE_HINT int32 AddUninitializedValue()` — Add an uninitialized value to the end of the array. @return	the index of the newly added item.
- L4448 _public function_ `void InsertValues( int32 Index, int32 Count = 1)` — Insert blank, constructed values into the array. @param	Index: index of the first inserted item after completion @param	Count: the number of items to insert.
- L4459 _public function_ `void EmptyValues(int32 Slack = 0)` — Remove all values from the array, calling destructors, etc as appropriate. @param Slack: used to presize the array for a subsequent add, to avoid reallocation.
- L4477 _public function_ `void RemoveValues(int32 Index, int32 Count = 1)` — Remove values from the array, calling destructors, etc as appropriate. @param Index: first item to remove. @param Count: number of items to remove.
- L4490 _public function_ `void ClearValues(int32 Index, int32 Count = 1)` — Clear values in the array. The meaning of clear is defined by the property system. @param Index: first item to clear. @param Count: number of items to clear.
- L4502 _public function_ `void SwapValues(int32 A, int32 B)` — Swap two elements in the array, does not call constructors and destructors @param A index of one item to swap. @param B index of the other item to swap.
- L4512 _public function_ `void MoveAssign(void* InOtherArray)` — Move the allocation from another array and make it our own. @note The arrays MUST be of the same type, and this function will NOT validate that! @param InOtherArray The array to move the allocation from.
- L4524 _public function_ `void CountBytes( FArchive& Ar ) const` — Used by memory counting archives to accumulate the size of this array. @param Ar archive to accumulate sizes
- L4532 _public function_ `void DestroyContainer_Unsafe()` — Destroys the container object - THERE SHOULD BE NO MORE USE OF THIS HELPER AFTER THIS FUNCTION IS CALLED!
- L4537 _public function_ `static FScriptArrayHelper CreateHelperFormInnerProperty(const FProperty* InInnerProperty, const void *InArray, EArrayPropertyFlags InArrayFlags = EArrayPropertyFlags::None)`
- L4543 _private function_ `FScriptArrayHelper(EInternal, const FProperty* InInnerProperty, const void* InArray, int32 InElementSize, uint32 InElementAlignment, EArrayPropertyFlags InArrayFlags) : InnerProperty(InInnerProperty) , ElementSize(InElementSize) , ElementAlignment(InElementAlignment) , ArrayFlags(InArrayFlags)`
- L4568 _private function_ `void ConstructItems(int32 Index, int32 Count)` — Internal function to call into the property system to construct / initialize elements. @param Index: first item to . @param Count: number of items to .
- L4595 _private function_ `void DestructItems(int32 Index, int32 Count)` — Internal function to call into the property system to destruct elements. @param Index: first item to . @param Count: number of items to .
- L4617 _private function_ `void ClearItems(int32 Index, int32 Count)` — Internal function to call into the property system to clear elements. @param Index: first item to . @param Count: number of items to .
- L4640 _private member_ `const FProperty* InnerProperty;`
- L4646 _private member_ `int32 ElementSize;`
- L4647 _private member_ `uint32 ElementAlignment;`
- L4648 _private member_ `EArrayPropertyFlags ArrayFlags;`

#### enum `FScriptArrayHelper::EInternal`  
`enum EInternal`  
_L4264-4264_
- L4264 _public enumerator_ `enum EInternal { Internal }; template <typename CallableType> auto WithScriptArray(CallableType&& Callable) const { if (!!(ArrayFlags & EArrayPropertyFlags::UsesMemoryImageAllocator)) { return Callable(FreezableArray);`

#### union `FScriptArrayHelper::(anonymous)`  
``  
_L4642-4645_

#### class `FScriptArrayHelper_InContainer`  
`class FScriptArrayHelper_InContainer : public FScriptArrayHelper`  
_L4651-4663_
- inherits: `FScriptArrayHelper`
- L4654 _public function_ `UE_FORCEINLINE_HINT FScriptArrayHelper_InContainer(const FArrayProperty* InProperty, const void* InContainer, int32 FixedArrayIndex=0) :FScriptArrayHelper(InProperty, InProperty->ContainerPtrToValuePtr<void>(InContainer, FixedArrayIndex))`
- L4659 _public function_ `UE_FORCEINLINE_HINT FScriptArrayHelper_InContainer(const FArrayProperty* InProperty, const UObject* InContainer, int32 FixedArrayIndex=0) :FScriptArrayHelper(InProperty, InProperty->ContainerPtrToValuePtr<void>(InContainer, FixedArrayIndex))`

#### struct `TScriptContainerIterator`  
`template<typename ContainerType> struct TScriptContainerIterator`  
_L4675-4743_
- desc: Templated iterator to go through script helper containers that may contain invalid entries that are not part of the valid number of elements (i.e. GetMaxIndex() != Num() ). The iterator - will advance to the first valid entry on creation and when incremented - can be dereferenced to an internal index to be used with methods like Get<Item>Ptr or Get<Item>PtrWithoutCheck - can also be used directly with methods like Get<Item>PtrChecked - can return the associated logical index (number of valid visited entries) by calling GetLogicalIndex()
- L4677 _public function_ `explicit TScriptContainerIterator(const ContainerType& InContainer) : Container(InContainer)`
- L4682 _public function_ `explicit TScriptContainerIterator(const ContainerType& InContainer, const int32 InLogicalIndex) : Container(InContainer)`
- L4699 _public function_ `TScriptContainerIterator& operator++()`
- L4705 _public function_ `TScriptContainerIterator operator++(int)`
- L4712 _public function_ `explicit operator bool() const`
- L4717 _public function_ `int32 GetInternalIndex() const`
- L4722 _public function_ `int32 GetLogicalIndex() const`
- L4728 _private member_ `const ContainerType& Container;`
- L4729 _private member_ `int32 InternalIndex = INDEX_NONE;`
- L4730 _private member_ `int32 LogicalIndex = INDEX_NONE;`
- L4732 _private function_ `void Advance()`

#### class `FScriptMapHelper`  
`class FScriptMapHelper`  
_L4759-5738_
- desc: FScriptMapHelper: Pseudo dynamic map. Used to work with map properties in a sensible way. Note that map can contain invalid entries some number of valid entries (i.e. Num() ) can be smaller that the actual number of elements (i.e. GetMaxIndex() ). Internal index naming is used to identify the actual index in the container which can point to an invalid entry. It can be used for methods like Get<Item>Ptr, Get<Item>PtrWithoutCheck or IsValidIndex. Logical index naming is used to identify only valid entries in the container so it can be smaller than the internal index in case we skipped invalid entries to reach the next valid one. This index is used on method like FindNth<Item>Ptr or FindInternalIndex. This is also the type of index we receive from most editor events (e.g. property change events) so it is strongly suggested to rely on FScriptMapHelper::FIterator to iterate or convert to internal index.
- L4766 _private function_ `template <typename CallableType> auto WithScriptMap(CallableType&& Callable) const`
- L4785 _public function_ `FScriptMapHelper(const FMapProperty* InProperty, const void* InMap) : FScriptMapHelper(Internal, InProperty->KeyProp, InProperty->ValueProp, InMap, InProperty->MapLayout, InProperty->MapFlags)` — Constructor, brings together a property and an instance of the property located in memory @param  InProperty  The property associated with this memory @param  InMap       Pointer to raw memory that corresponds to this map. This can be NULL, and sometimes is, but in that case almost all operations will crash.
- L4790 _public function_ `FScriptMapHelper(FProperty* InKeyProp, FProperty* InValueProp, const void* InMap, const FScriptMapLayout& InMapLayout, EMapPropertyFlags InMapFlags) : FScriptMapHelper(Internal, InKeyProp, InValueProp, InMap, InMapLayout, InMapFlags)`
- L4795 _public typedef_ `using FIterator = TScriptContainerIterator<FScriptMapHelper>;`
- L4797 _public function_ `FIterator CreateIterator() const`
- L4802 _public function_ `FIterator CreateIterator(const int32 InLogicalIndex) const`
- L4814 _public function_ `UE_FORCEINLINE_HINT bool IsValidIndex(int32 InternalIndex) const` — Index range check @param InternalIndex Index to check @return true if accessing this element is legal.
- L4824 _public function_ `inline int32 Num() const` — Returns the number of elements in the map. @return The number of elements in the map.
- L4836 _public function_ `inline int32 NumUnchecked() const` — Returns the number of elements in the map. Needed to allow reading of the num when the map is 'invalid' during its intrusive unset state. @return The number of elements in the map.
- L4848 _public function_ `inline int32 GetMaxIndex() const` — Returns the (non-inclusive) maximum index of elements in the map. @return The (non-inclusive) maximum index of elements in the map.
- L4865 _public function_ `inline uint8* GetPairPtr(int32 InternalIndex)` — Returns a uint8 pointer to the pair in the map @param InternalIndex index of the item to return a pointer to. @return Pointer to the pair, or nullptr if the map is empty.
- L4887 _public function_ `UE_FORCEINLINE_HINT const uint8* GetPairPtr(const int32 InternalIndex) const` — Returns a uint8 pointer to the pair in the map. @param InternalIndex index of the item to return a pointer to. @return Pointer to the pair, or nullptr if the map is empty.
- L4901 _public function_ `inline uint8* GetKeyPtr(int32 InternalIndex)` — Returns a uint8 pointer to the Key (first element) in the map. Currently identical to GetPairPtr, but provides clarity of purpose and avoids exposing implementation details of TMap. @param InternalIndex index of the item to return a pointer to. @return Pointer to the key, or nullptr if the map is empty.
- L4923 _public function_ `inline uint8* GetValuePtr(int32 InternalIndex)` — Returns a uint8 pointer to the Value (second element) in the map. @param InternalIndex index of the item to return a pointer to. @return Pointer to the value, or nullptr if the map is empty.
- L4945 _public function_ `inline uint8* GetPairPtr(const FIterator Iterator)` — Returns a uint8 pointer to the pair in the map @param Iterator A valid iterator of the item to return a pointer to. @return Pointer to the pair, or will fail a check if an invalid iterator is provided.
- L4961 _public function_ `UE_FORCEINLINE_HINT const uint8* GetPairPtr(const FIterator Iterator) const` — Returns a uint8 pointer to the pair in the map. @param Iterator A valid iterator of the item to return a pointer to. @return Pointer to the pair, or will fail a check if an invalid iterator is provided.
- L4975 _public function_ `inline uint8* GetKeyPtr(const FIterator Iterator)` — Returns a uint8 pointer to the Key (first element) in the map. Currently identical to GetPairPtr, but provides clarity of purpose and avoids exposing implementation details of TMap. @param Iterator A valid iterator of the item to return a pointer to. @return Pointer to the key, or will fail a check if an invalid iterator is provided.
- L4993 _public function_ `UE_FORCEINLINE_HINT const uint8* GetKeyPtr(const FIterator Iterator) const` — Returns a const uint8 pointer to the Key (first element) in the map. Currently identical to GetPairPtr, but provides clarity of purpose and avoids exposing implementation details of TMap. @param Iterator A valid iterator of the item to return a pointer to. @return Pointer to the key, or will fail a check if an invalid iterator is provided.
- L5005 _public function_ `inline uint8* GetValuePtr(const FIterator Iterator)` — Returns a uint8 pointer to the Value (second element) in the map. @param Iterator A valid iterator of the item to return a pointer to. @return Pointer to the value, or will fail a check if an invalid iterator is provided.
- L5021 _public function_ `UE_FORCEINLINE_HINT const uint8* GetValuePtr(const FIterator Iterator) const` — Returns a const uint8 pointer to the Value (second element) in the map. @param Iterator A valid iterator of the item to return a pointer to. @return Pointer to the value, or will fail a check if an invalid iterator is provided.
- L5032 _public function_ `uint8* FindNthPairPtr(int32 N)` — Returns a uint8 pointer to the the Nth valid pair in the map (skipping invalid entries). NOTE: This is slow, do not use this for iteration! Use CreateIterator() instead. @return Pointer to the element, or nullptr if the index is invalid.
- L5044 _public function_ `uint8* FindNthKeyPtr(int32 N)` — Returns a uint8 pointer to the the Nth valid key in the map (skipping invalid entries). NOTE: This is slow, do not use this for iteration! Use CreateIterator() instead. @return Pointer to the element, or nullptr if the index is invalid.
- L5056 _public function_ `uint8* FindNthValuePtr(int32 N)` — Returns a uint8 pointer to the the Nth valid value in the map (skipping invalid entries). NOTE: This is slow, do not use this for iteration! Use CreateIterator() instead. @return Pointer to the element, or nullptr if the index is invalid.
- L5068 _public function_ `const uint8* FindNthPairPtr(int32 N) const` — Returns a uint8 pointer to the the Nth valid pair in the map (skipping invalid entries). NOTE: This is slow, do not use this for iteration! Use CreateIterator() instead. @return Pointer to the element, or nullptr if the index is invalid.
- L5080 _public function_ `void MoveAssign(void* InOtherMap)` — Move the allocation from another map and make it our own. @note The maps MUST be of the same type, and this function will NOT validate that! @param InOtherMap The map to move the allocation from.
- L5096 _public function_ `inline int32 AddUninitializedValue()` — Add an uninitialized value to the end of the map. @return  The index of the added element.
- L5110 _public function_ `void EmptyValues(int32 Slack = 0)` — Remove all values from the map, calling destructors, etc as appropriate. @param Slack: used to presize the set for a subsequent add, to avoid reallocation.
- L5134 _public function_ `int32 AddDefaultValue_Invalid_NeedsRehash()` — Adds a blank, constructed value to a given size. Note that this will create an invalid map because all the keys will be default constructed, and the map needs rehashing. @return  The index of the first element added.
- L5152 _public function_ `FProperty* GetKeyProperty() const` — Returns the property representing the key of the map pair. @return The property representing the key of the map pair.
- L5162 _public function_ `FProperty* GetValueProperty() const` — Returns the property representing the value of the map pair. @return The property representing the value of the map pair.
- L5172 _public function_ `void RemoveAt(int32 InternalIndex, int32 Count = 1)` — Removes an element at the specified index, destroying it. @param InternalIndex The index of the element to remove.
- L5223 _public prototype_ `void Rehash();` — Rehashes the keys in the map. This function must be called to create a valid map.
- L5230 _public function_ `int32 FindInternalIndex(int32 LogicalIdx) const` — Maps have gaps in their indices, so this function translates a logical index (ie. Nth element) to an internal index that can be used for the other functions in this class. NOTE: This is slow, do not use this for iteration! Use CreateIterator() instead.
- L5267 _public function_ `int32 FindLogicalIndex(int32 InternalIdx) const` — Maps have gaps in their indices, so this function translates a internal index to an logical index (ie. Nth element). NOTE: This is slow, do not use this for iteration!
- L5304 _public function_ `int32 FindMapIndexWithKey(const void* PairWithKeyToFind, int32 IndexHint = 0) const` — Finds the index of an element in a map which matches the key in another pair. @param  PairWithKeyToFind  The address of a map pair which contains the key to search for. @param  IndexHint          The index to start searching from. @return The index of an element found in MapHelper, or -1 if none was found.
- L5357 _public function_ `inline uint8* FindMapPairPtrWithKey(const void* PairWithKeyToFind, int32 IndexHint = 0)` — Finds the pair in a map which matches the key in another pair. @param  PairWithKeyToFind  The address of a map pair which contains the key to search for. @param  IndexHint          The index to start searching from. @return A pointer to the found pair, or nullptr if none was found.
- L5365 _public function_ `int32 FindMapPairIndexFromHash(const void* KeyPtr)` — Finds the associated pair from hash, rather than linearly searching
- L5380 _public function_ `uint8* FindMapPairPtrFromHash(const void* KeyPtr)` — Finds the associated pair from hash, rather than linearly searching
- L5388 _public function_ `uint8* FindValueFromHash(const void* KeyPtr)` — Finds the associated value from hash, rather than linearly searching
- L5402 _public function_ `void AddPair(const void* KeyPtr, const void* ValuePtr)` — Adds the (key, value) pair to the map, returning true if the element was added, or false if the element was already present and has been overwritten
- L5468 _public function_ `void* FindOrAdd(const void* KeyPtr)` — Finds or adds a new default-constructed value No need to rehash after calling. The hash table must be properly hashed before calling. @return The address to the value, not the pair
- L5505 _public function_ `bool RemovePair(const void* KeyPtr)` — Removes the key and its associated value from the map
- L5527 _public function_ `static FScriptMapHelper CreateHelperFormInnerProperties(FProperty* InKeyProperty, FProperty* InValProperty, const void *InMap, EMapPropertyFlags InMapFlags = EMapPropertyFlags::None)`
- L5540 _private function_ `inline FScriptMapHelper(EInternal, FProperty* InKeyProp, FProperty* InValueProp, const void* InMap, const FScriptMapLayout& InMapLayout, EMapPropertyFlags InMapFlags) : KeyProp (InKeyProp) , ValueProp(InValueProp) , MapLayout(InMapLayout) , MapFlags (InMapFlags)`
- L5567 _private function_ `void ConstructItem(int32 InternalIndex)` — Internal function to call into the property system to construct / initialize elements. @param InternalIndex First item to construct. @param Count Number of items to construct.
- L5596 _private function_ `void DestructItems(int32 InternalIndex, int32 Count)` — Internal function to call into the property system to destruct elements.
- L5663 _private function_ `UE_FORCEINLINE_HINT uint8* GetPairPtrWithoutCheck(int32 InternalIndex)` — Returns a uint8 pointer to the pair in the array without checking the index. @param InternalIndex index of the item to return a pointer to. @return Pointer to the pair, or nullptr if the map is empty.
- L5675 _private function_ `UE_FORCEINLINE_HINT const uint8* GetPairPtrWithoutCheck(int32 InternalIndex) const` — Returns a uint8 pointer to the pair in the array without checking the index. @param InternalIndex index of the item to return a pointer to. @return Pointer to the pair, or nullptr if the map is empty.
- L5687 _private function_ `UE_FORCEINLINE_HINT uint8* GetKeyPtrWithoutCheck(int32 InternalIndex)` — Returns a uint8 pointer to the key in the array without checking the index. @param InternalIndex index of the key to return a pointer to. @return Pointer to the key, or nullptr if the map is empty.
- L5699 _private function_ `UE_FORCEINLINE_HINT const uint8* GetKeyPtrWithoutCheck(int32 InternalIndex) const` — Returns a const uint8 pointer to the pair in the array without checking the index. @param InternalIndex index of the item to return a pointer to. @return Pointer to the pair, or nullptr if the map is empty.
- L5711 _private function_ `UE_FORCEINLINE_HINT uint8* GetValuePtrWithoutCheck(int32 InternalIndex)` — Returns a uint8 pointer to the pair in the array without checking the index. @param InternalIndex index of the item to return a pointer to. @return Pointer to the pair, or nullptr if the map is empty.
- L5723 _private function_ `UE_FORCEINLINE_HINT const uint8* GetValuePtrWithoutCheck(int32 InternalIndex) const` — Returns a const uint8 pointer to the pair in the array without checking the index. @param InternalIndex index of the item to return a pointer to. @return Pointer to the pair, or nullptr if the map is empty.
- L5729 _public member_ `FProperty* KeyProp;`
- L5730 _public member_ `FProperty* ValueProp;`
- L5736 _public member_ `FScriptMapLayout MapLayout;`
- L5737 _public member_ `EMapPropertyFlags MapFlags;`

#### enum `FScriptMapHelper::EInternal`  
`enum EInternal`  
_L4761-4761_
- L4761 _public enumerator_ `enum EInternal { Internal }; friend class FMapProperty; template <typename CallableType> auto WithScriptMap(CallableType&& Callable) const { if (!!(MapFlags & EMapPropertyFlags::UsesMemoryImageAllocator))`

#### union `FScriptMapHelper::(anonymous)`  
``  
_L5732-5735_

#### class `FScriptMapHelper_InContainer`  
`class FScriptMapHelper_InContainer : public FScriptMapHelper`  
_L5740-5747_
- inherits: `FScriptMapHelper`
- L5743 _public function_ `UE_FORCEINLINE_HINT FScriptMapHelper_InContainer(const FMapProperty* InProperty, const void* InArray, int32 FixedArrayIndex=0) :FScriptMapHelper(InProperty, InProperty->ContainerPtrToValuePtr<void>(InArray, FixedArrayIndex))`

#### class `FScriptSetHelper`  
`class FScriptSetHelper`  
_L5763-6368_
- desc: FScriptSetHelper: Pseudo dynamic Set. Used to work with Set properties in a sensible way. Note that the set can contain invalid entries some number of valid entries (i.e. Num() ) can be smaller that the actual number of elements (i.e. GetMaxIndex() ). Internal index naming is used to identify the actual index in the container which can point to an invalid entry. It can be used for methods like Get<Item>Ptr, Get<Item>PtrWithoutCheck or IsValidIndex. Logical index naming is used to identify only valid entries in the container so it can be smaller than the internal index in case we skipped invalid entries to reach the next valid one. This index is used on method like FindNth<Item>Ptr or FindInternalIndex. This is also the type of index we receive from most editor events (e.g. property change events) so it is strongly suggested to rely on FScriptSetHelper::FIterator to iterate or convert to internal index.
- L5769 _public typedef_ `using FIterator = TScriptContainerIterator<FScriptSetHelper>;`
- L5771 _public function_ `FIterator CreateIterator() const`
- L5776 _public function_ `FIterator CreateIterator(const int32 InLogicalIndex) const`
- L5787 _public function_ `FScriptSetHelper(const FSetProperty* InProperty, const void* InSet) : FScriptSetHelper(InProperty->ElementProp, InSet, InProperty->SetLayout)` — Constructor, brings together a property and an instance of the property located in memory @param  InProperty  The property associated with this memory @param  InSet       Pointer to raw memory that corresponds to this Set. This can be NULL, and sometimes is, but in that case almost all operations will crash.
- L5792 _public function_ `FScriptSetHelper(FProperty* InElementProp, const void* InSet, const FScriptSetLayout& InLayout) : ElementProp(InElementProp) , Set((FScriptSet*)InSet)`
- L5807 _public function_ `UE_FORCEINLINE_HINT bool IsValidIndex(int32 InternalIndex) const` — Index range check @param InternalIndex Index to check @return true if accessing this element is legal.
- L5817 _public function_ `inline int32 Num() const` — Returns the number of elements in the set. @return The number of elements in the set.
- L5829 _public function_ `inline int32 NumUnchecked() const` — Returns the number of elements in the set. Needed to allow reading of the num when the set is 'invalid' during its intrusive unset state. @return The number of elements in the set.
- L5840 _public function_ `inline int32 GetMaxIndex() const` — Returns the (non-inclusive) maximum index of elements in the set. @return The (non-inclusive) maximum index of elements in the set.
- L5854 _public function_ `static inline int32 Num(const void* Target)` — Static version of Num() used when you don't need to bother to construct a FScriptSetHelper. Returns the number of elements in the set. @param  Target  Pointer to the raw memory associated with a FScriptSet @return The number of elements in the set.
- L5868 _public function_ `inline uint8* GetElementPtr(int32 InternalIndex)` — Returns a uint8 pointer to the element in the set. @param InternalIndex index of the item to return a pointer to. @return Pointer to the element, or nullptr if the set is empty.
- L5887 _public function_ `UE_FORCEINLINE_HINT const uint8* GetElementPtr(int32 InternalIndex) const` — Returns a uint8 pointer to the element in the set. @param InternalIndex index of the item to return a pointer to. @return Pointer to the element, or nullptr if the set is empty.
- L5899 _public function_ `inline uint8* GetElementPtr(const FIterator Iterator)` — Returns a uint8 pointer to the element in the set. @param Iterator A valid iterator of the item to return a pointer to. @return Pointer to the element, or will fail a check if an invalid iterator is provided.
- L5912 _public function_ `UE_FORCEINLINE_HINT const uint8* GetElementPtr(const FIterator Iterator) const` — Returns a uint8 pointer to the element in the set. @param Iterator A valid iterator of the item to return a pointer to. @return Pointer to the element, or will fail a check if an invalid iterator is provided.
- L5923 _public function_ `uint8* FindNthElementPtr(int32 N)` — Returns a uint8 pointer to the the Nth valid element in the set (skipping invalid entries). NOTE: This is slow, do not use this for iteration! Use CreateIterator() instead. @return Pointer to the element, or nullptr if the index is invalid.
- L5935 _public function_ `const uint8* FindNthElementPtr(int32 N) const` — Returns a uint8 pointer to the the Nth valid element in the set (skipping invalid entries). NOTE: This is slow, do not use this for iteration! Use CreateIterator() instead. @return Pointer to the element, or nullptr if the index is invalid.
- L5947 _public function_ `void MoveAssign(void* InOtherSet)` — Move the allocation from another set and make it our own. @note The sets MUST be of the same type, and this function will NOT validate that! @param InOtherSet The set to move the allocation from.
- L5959 _public function_ `inline int32 AddUninitializedValue()` — Add an uninitialized value to the end of the set. @return  The index of the added element.
- L5970 _public function_ `void EmptyElements(int32 Slack = 0)` — Remove all values from the set, calling destructors, etc as appropriate. @param Slack: used to presize the set for a subsequent add, to avoid reallocation.
- L5991 _public function_ `int32 AddDefaultValue_Invalid_NeedsRehash()` — Adds a blank, constructed value to a given size. Note that this will create an invalid Set because all the keys will be default constructed, and the set needs rehashing. @return  The index of the first element added.
- L6004 _public function_ `FProperty* GetElementProperty() const` — Returns the property representing the element of the set
- L6014 _public function_ `void RemoveAt(int32 InternalIndex, int32 Count = 1)` — Removes an element at the specified index, destroying it. @param InternalIndex The index of the element to remove.
- L6057 _public prototype_ `void Rehash();` — Rehashes the keys in the set. This function must be called to create a valid set.
- L6064 _public function_ `int32 FindInternalIndex(int32 LogicalIdx) const` — Sets have gaps in their indices, so this function translates a logical index (ie. Nth element) to an internal index that can be used for the other functions in this class. NOTE: This is slow, do not use this for iteration! Use CreateIterator() instead.
- L6097 _public function_ `int32 FindLogicalIndex(int32 InternalIdx) const` — Sets have gaps in their indices, so this function translates a internal index to an logical index (ie. Nth element). NOTE: This is slow, do not use this for iteration!
- L6130 _public function_ `int32 FindElementIndex(const void* ElementToFind, int32 IndexHint = 0) const` — Finds the index of an element in a set @param  ElementToFind		The address of an element to search for. @param  IndexHint         The index to start searching from. @return The index of an element found in SetHelper, or -1 if none was found.
- L6180 _public function_ `inline uint8* FindElementPtr(const void* ElementToFind, int32 IndexHint = 0)` — Finds the pair in a map which matches the key in another pair. @param  PairWithKeyToFind  The address of a map pair which contains the key to search for. @param  IndexHint          The index to start searching from. @return A pointer to the found pair, or nullptr if none was found.
- L6188 _public function_ `inline int32 FindElementIndexFromHash(const void* ElementToFind) const` — Finds element index from hash, rather than linearly searching
- L6200 _public function_ `inline uint8* FindElementPtrFromHash(const void* ElementToFind)` — Finds element pointer from hash, rather than linearly searching
- L6208 _public function_ `void AddElement(const void* ElementToAdd)` — Adds the element to the set, returning true if the element was added, or false if the element was already present
- L6241 _public function_ `bool RemoveElement(const void* ElementToRemove)` — Removes the element from the set
- L6261 _public function_ `static FScriptSetHelper CreateHelperFormElementProperty(FProperty* InElementProperty, const void *InSet)`
- L6277 _private function_ `FScriptSetHelper() : ElementProp(nullptr) , Set(nullptr) , SetLayout(FScriptSet::GetScriptLayout(0, 1))`
- L6289 _private function_ `void ConstructItem(int32 InternalIndex)` — Internal function to call into the property system to construct / initialize elements. @param InternalIndex First item to construct. @param Count Number of items to construct.
- L6311 _private function_ `void DestructItems(int32 InternalIndex, int32 Count)` — Internal function to call into the property system to destruct elements.
- L6347 _private function_ `UE_FORCEINLINE_HINT uint8* GetElementPtrWithoutCheck(int32 InternalIndex)` — Returns a uint8 pointer to the element in the array without checking the index. @param InternalIndex index of the item to return a pointer to. @return Pointer to the element, or nullptr if the array is empty.
- L6359 _private function_ `UE_FORCEINLINE_HINT const uint8* GetElementPtrWithoutCheck(int32 InternalIndex) const` — Returns a uint8 pointer to the element in the array without checking the index. @param InternalIndex index of the item to return a pointer to. @return Pointer to the pair, or nullptr if the array is empty.
- L6365 _public member_ `FProperty* ElementProp;`
- L6366 _public member_ `FScriptSet* Set;`
- L6367 _public member_ `FScriptSetLayout SetLayout;`

#### class `FScriptSetHelper_InContainer`  
`class FScriptSetHelper_InContainer : public FScriptSetHelper`  
_L6370-6377_
- inherits: `FScriptSetHelper`
- L6373 _public function_ `UE_FORCEINLINE_HINT FScriptSetHelper_InContainer(const FSetProperty* InProperty, const void* InArray, int32 FixedArrayIndex=0) :FScriptSetHelper(InProperty, InProperty->ContainerPtrToValuePtr<void>(InArray, FixedArrayIndex))`

#### class `FStructProperty`  
`class FStructProperty : public FProperty`  
_L6387-6478_
- inherits: `FProperty`
- desc: Describes a structure variable embedded in (as opposed to referenced by) an object.
- L6394 _public prototype_ `FStructProperty(FFieldVariant InOwner, const FName& InName);`
- L6396 _public function_ `FStructProperty(FFieldVariant InOwner, const FName& InName, EObjectFlags InObjectFlags) : FStructProperty(InOwner, InName)` — `UE_DEPRECATED(5.8, "FStructProperty constructor with InObjectFlags is deprecated, remove that parameter.")`
- L6403 _public prototype_ `FStructProperty(FFieldVariant InOwner, const UECodeGen_Private::FStructPropertyParams& Prop);` — Constructor used for constructing compiled in properties @param InOwner Owner of the property @param PropBase Pointer to the compiled in structure describing the property
- L6406 _public function_ `explicit consteval FStructProperty( UE::CodeGen::ConstInit::FPropertyParams InBaseParams, int32 StructSize, UE::CodeGen::ConstInit::TObjectRefParam<UScriptStruct> InScriptStruct ) : Super(InBaseParams.SetElementSize(StructSize)) , Struct(InScriptStruct)`
- L6418 _public prototype_ `explicit FStructProperty(UField* InField);`
- L6422 _public prototype_ `virtual void Serialize( FArchive& Ar ) override;` — UObject interface
- L6423 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;`
- L6424 _public prototype_ `virtual void GetPreloadDependencies(TArray<UObject*>& OutDeps) override;`
- L6426 _public prototype_ `virtual void LinkCompiledInPointerFields(UE::CoreUObject::Private::FCompiledInObjectLinker& Linker);`
- L6431 _public prototype_ `virtual void PostDuplicate(const FField& InField) override;` — Field interface
- L6434 _public prototype_ `virtual FString GetCPPMacroType( FString& ExtendedTypeText ) const override;` — FProperty interface
- L6435 _public prototype_ `virtual FString GetCPPType( FString* ExtendedTypeText, uint32 CPPExportFlags ) const override;`
- L6436 _public prototype_ `virtual void LinkInternal(FArchive& Ar) override;`
- L6437 _public prototype_ `virtual bool Identical(TNotNull<const void*> A, const void* B, uint32 PortFlags ) const override;`
- L6438 _public prototype_ `virtual void SerializeItem(FStructuredArchive::FSlot Slot, TNotNull<void*> Value, void const* Defaults) const override;`
- L6439 _public prototype_ `virtual bool NetSerializeItem(FArchive& Ar, UPackageMap* Map, TNotNull<void*> Data, TArray<uint8> * MetaData = nullptr) const override;`
- L6440 _public prototype_ `virtual bool SupportsNetSharedSerialization() const override;`
- L6442 _protected prototype_ `virtual void ExportText_Internal(FString& ValueStr, TNotNull<const void*> PropertyValueOrContainer, EPropertyPointerType PropertyPointerType, const void* DefaultValue, UObject* Parent, int32 PortFlags, UObject* ExportRootScope) const override;`
- L6443 _protected prototype_ `virtual const TCHAR* ImportText_Internal(const TCHAR* Buffer, TNotNull<void*> ContainerOrPropertyPtr, EPropertyPointerType PropertyPointerType, UObject* OwnerObject, int32 PortFlags, FOutputDevice* ErrorText) const override;`
- L6444 _protected prototype_ `virtual bool ContainsClearOnFinishDestroyInternal(TArray<const FStructProperty*>& EncounteredStructProps) const override;`
- L6445 _protected prototype_ `virtual void FinishDestroyInternal(void* Data) const override;`
- L6447 _public prototype_ `virtual void CopyValuesInternal( void* Dest, void const* Src, int32 Count ) const override;`
- L6448 _public prototype_ `virtual void ClearValueInternal( void* Data ) const override;`
- L6449 _public prototype_ `virtual void DestroyValueInternal( void* Dest ) const override;`
- L6450 _public prototype_ `virtual void InitializeValueInternal( void* Dest ) const override;`
- L6451 _public prototype_ `virtual void InstanceSubobjects( void* Data, void const* DefaultData, TNotNull<UObject*> Owner, struct FObjectInstancingGraph* InstanceGraph ) override;`
- L6452 _public prototype_ `virtual int32 GetMinAlignment() const override;`
- L6453 _public prototype_ `virtual bool ContainsObjectReference(TArray<const FStructProperty*>& EncounteredStructProps, EPropertyObjectReferenceType InReferenceType = EPropertyObjectReferenceType::Strong) const override;`
- L6454 _public prototype_ `virtual void EmitReferenceInfo(UE::GC::FSchemaBuilder& Schema, int32 BaseOffset, TArray<const FStructProperty*>& EncounteredStructProps, UE::GC::FPropertyStack& DebugPath) override;`
- L6455 _public prototype_ `virtual bool SameType(const FProperty* Other) const override;`
- L6456 _public prototype_ `virtual EConvertFromTypeResult ConvertFromType(const FPropertyTag& Tag, FStructuredArchive::FSlot Slot, uint8* Data, const UStruct* DefaultsStruct, const uint8* Defaults) override;`
- L6458 _public prototype_ `virtual void AppendSchemaHash(FBlake3& Builder, bool bSkipEditorOnly) const override;`
- L6460 _public prototype_ `virtual bool UseBinaryOrNativeSerialization(const FArchive& Ar) const override;`
- L6461 _public prototype_ `virtual bool LoadTypeName(UE::FPropertyTypeName Type, const FPropertyTag* Tag = nullptr) override;`
- L6462 _public prototype_ `virtual void SaveTypeName(UE::FPropertyTypeNameBuilder& Type) const override;`
- L6463 _public prototype_ `virtual bool CanSerializeFromTypeName(UE::FPropertyTypeName Type) const override;`
- L6464 _public prototype_ `virtual EPropertyVisitorControlFlow Visit(FPropertyVisitorContext& Context, const TFunctionRef<EPropertyVisitorControlFlow(const FPropertyVisitorContext& )> InFunc) const override;`
- L6465 _public prototype_ `virtual void* ResolveVisitedPathInfo(void* Data, const FPropertyVisitorInfo& Info) const override;`
- L6468 _public prototype_ `bool FindInnerPropertyInstance(FName PropertyName, const void* Data, const FProperty*& OutProp, const void*& OutData) const;`
- L6470 _public prototype_ `virtual bool HasIntrusiveUnsetOptionalState() const override;`
- L6471 _public prototype_ `virtual void InitializeIntrusiveUnsetOptionalValue(void* Data) const override;`
- L6472 _public prototype_ `virtual bool IsIntrusiveOptionalValueSet(const void* Data) const override;`
- L6473 _public prototype_ `virtual void ClearIntrusiveOptionalValue(void* Data) const override;`
- L6474 _public prototype_ `virtual void EmitIntrusiveOptionalReferenceInfo(UE::GC::FSchemaBuilder& Schema, int32 BaseOffset, TArray<const FStructProperty*>& EncounteredStructProps, UE::GC::FPropertyStack& DebugPath) override;`
- L6477 _private prototype_ `virtual uint32 GetValueTypeHashInternal(const void* Src) const;`

#### class `FDelegateProperty`  
`class FDelegateProperty : public TProperty<FScriptDelegate, FProperty>`  
_L6487-6548_
- inherits: `TProperty<FScriptDelegate,FProperty>`
- desc: Describes a pointer to a function bound to an Object.
- L6495 _public typedef_ `using TTypeFundamentals = Super::TTypeFundamentals;`
- L6496 _public typedef_ `using TCppType = TTypeFundamentals::TCppType;`
- L6498 _public prototype_ `FDelegateProperty(FFieldVariant InOwner, const FName& InName);`
- L6500 _public function_ `FDelegateProperty(FFieldVariant InOwner, const FName& InName, EObjectFlags InObjectFlags) : FDelegateProperty(InOwner, InName)` — `UE_DEPRECATED(5.8, "FDelegateProperty constructor with InObjectFlags is deprecated, remove that parameter.")`
- L6507 _public prototype_ `FDelegateProperty(FFieldVariant InOwner, const UECodeGen_Private::FDelegatePropertyParams& Prop);` — Constructor used for constructing compiled in properties @param InOwner Owner of the property @param PropBase Pointer to the compiled in structure describing the property
- L6510 _public function_ `explicit consteval FDelegateProperty(UE::CodeGen::ConstInit::FPropertyParams InBaseParams, UE::CodeGen::ConstInit::TObjectRefParam<UFunction> InSignatureFunction) : Super(InBaseParams) , SignatureFunction(InSignatureFunction)`
- L6518 _public prototype_ `explicit FDelegateProperty(UField* InField);`
- L6522 _public prototype_ `virtual void Serialize( FArchive& Ar ) override;` — UObject interface
- L6523 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;`
- L6525 _public prototype_ `virtual void LinkCompiledInPointerFields(UE::CoreUObject::Private::FCompiledInObjectLinker& Linker);`
- L6530 _public prototype_ `virtual void PostDuplicate(const FField& InField) override;` — Field interface
- L6533 _public prototype_ `virtual FString GetCPPType( FString* ExtendedTypeText, uint32 CPPExportFlags ) const override;` — FProperty interface
- L6534 _public prototype_ `virtual bool Identical(TNotNull<const void*> A, const void* B, uint32 PortFlags ) const override;`
- L6535 _public prototype_ `virtual void SerializeItem(FStructuredArchive::FSlot Slot, TNotNull<void*> Value, void const* Defaults) const override;`
- L6536 _public prototype_ `virtual bool NetSerializeItem(FArchive& Ar, UPackageMap* Map, TNotNull<void*> Data, TArray<uint8> * MetaData = nullptr) const override;`
- L6538 _protected prototype_ `virtual void ExportText_Internal(FString& ValueStr, TNotNull<const void*> PropertyValueOrContainer, EPropertyPointerType PropertyPointerType, const void* DefaultValue, UObject* Parent, int32 PortFlags, UObject* ExportRootScope) const override;`
- L6539 _protected prototype_ `virtual const TCHAR* ImportText_Internal(const TCHAR* Buffer, TNotNull<void*> ContainerOrPropertyPtr, EPropertyPointerType PropertyPointerType, UObject* OwnerObject, int32 PortFlags, FOutputDevice* ErrorText) const override;`
- L6541 _public prototype_ `virtual bool ContainsObjectReference(TArray<const FStructProperty*>& EncounteredStructProps, EPropertyObjectReferenceType InReferenceType = EPropertyObjectReferenceType::Strong) const override;`
- L6542 _public prototype_ `virtual void InstanceSubobjects( void* Data, void const* DefaultData, TNotNull<UObject*> Owner, struct FObjectInstancingGraph* InstanceGraph ) override;`
- L6543 _public prototype_ `virtual bool SameType(const FProperty* Other) const override;`
- L6545 _public prototype_ `virtual void AppendSchemaHash(FBlake3& Builder, bool bSkipEditorOnly) const override;`

#### class `FMulticastDelegateProperty`  
`class FMulticastDelegateProperty : public FProperty`  
_L6558-6632_
- inherits: `FProperty`
- desc: Describes a list of functions bound to an Object.
- L6567 _public prototype_ `FMulticastDelegateProperty(FFieldVariant InOwner, const FName& InName);`
- L6569 _public function_ `FMulticastDelegateProperty(FFieldVariant InOwner, const FName& InName, EObjectFlags InObjectFlags) : FMulticastDelegateProperty(InOwner, InName)` — `UE_DEPRECATED(5.8, "FMulticastDelegateProperty constructor with InObjectFlags is deprecated, remove that parameter.")`
- L6576 _public prototype_ `FMulticastDelegateProperty(FFieldVariant InOwner, const UECodeGen_Private::FMulticastDelegatePropertyParams& Prop, EPropertyFlags AdditionalPropertyFlags = CPF_None);` — Constructor used for constructing compiled in properties @param InOwner Owner of the property @param PropBase Pointer to the compiled in structure describing the property
- L6579 _public function_ `explicit consteval FMulticastDelegateProperty(UE::CodeGen::ConstInit::FPropertyParams InBaseParams, UE::CodeGen::ConstInit::TObjectRefParam<UFunction> InSignatureFunction) : Super(InBaseParams) , SignatureFunction(InSignatureFunction)`
- L6587 _public prototype_ `explicit FMulticastDelegateProperty(UField* InField);`
- L6591 _public prototype_ `virtual void Serialize( FArchive& Ar ) override;` — UObject interface
- L6592 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;`
- L6594 _public prototype_ `virtual void LinkCompiledInPointerFields(UE::CoreUObject::Private::FCompiledInObjectLinker& Linker);`
- L6599 _public prototype_ `virtual void PostDuplicate(const FField& InField) override;` — Field interface
- L6602 _public prototype_ `virtual FString GetCPPType( FString* ExtendedTypeText, uint32 CPPExportFlags ) const override;` — FProperty interface
- L6603 _public prototype_ `virtual bool Identical(TNotNull<const void*> A, const void* B, uint32 PortFlags) const override;`
- L6604 _public prototype_ `virtual bool NetSerializeItem(FArchive& Ar, UPackageMap* Map, TNotNull<void*> Data, TArray<uint8> * MetaData = nullptr) const override;`
- L6606 _protected prototype_ `virtual void ExportText_Internal(FString& ValueStr, TNotNull<const void*> PropertyValueOrContainer, EPropertyPointerType PropertyPointerType, const void* DefaultValue, UObject* Parent, int32 PortFlags, UObject* ExportRootScope) const override;`
- L6608 _public prototype_ `virtual bool ContainsObjectReference(TArray<const FStructProperty*>& EncounteredStructProps, EPropertyObjectReferenceType InReferenceType = EPropertyObjectReferenceType::Strong) const override;`
- L6609 _public prototype_ `virtual void InstanceSubobjects( void* Data, void const* DefaultData, TNotNull<UObject*> Owner, struct FObjectInstancingGraph* InstanceGraph ) override;`
- L6610 _public prototype_ `virtual bool SameType(const FProperty* Other) const override;`
- L6611 _public prototype_ `virtual EConvertFromTypeResult ConvertFromType(const FPropertyTag& Tag, FStructuredArchive::FSlot Slot, uint8* Data, const UStruct* DefaultsStruct, const uint8* Defaults) override;`
- L6614 _public prototype_ `virtual const FMulticastScriptDelegate* GetMulticastDelegate(const void* PropertyValue) const PURE_VIRTUAL(FMulticastDelegateProperty::GetMulticastDelegate, return nullptr;);`
- L6615 _public prototype_ `virtual void SetMulticastDelegate(void* PropertyValue, FMulticastScriptDelegate ScriptDelegate) const PURE_VIRTUAL(FMulticastDelegateProperty::SetMulticastDelegate, );`
- L6617 _public prototype_ `virtual void AddDelegate(FScriptDelegate ScriptDelegate, UObject* Parent = nullptr, void* PropertyValue = nullptr) const PURE_VIRTUAL(FMulticastDelegateProperty::AddDelegate, );`
- L6618 _public prototype_ `virtual void RemoveDelegate(const FScriptDelegate& ScriptDelegate, UObject* Parent = nullptr, void* PropertyValue = nullptr) const PURE_VIRTUAL(FMulticastDelegateProperty::RemoveDelegate, );`
- L6619 _public prototype_ `virtual void ClearDelegate(UObject* Parent = nullptr, void* PropertyValue = nullptr) const PURE_VIRTUAL(FMulticastDelegateProperty::ClearDelegate, );`
- L6624 _protected member_ `static FMulticastScriptDelegate EmptyDelegate;`
- L6625 _protected prototype_ `virtual FMulticastScriptDelegate& GetMulticastScriptDelegate(const void* PropertyValue, int32 Index) const PURE_VIRTUAL(FMulticastDelegateProperty::GetMulticastScriptDelegate, return EmptyDelegate;);`
- L6628 _protected prototype_ `const TCHAR* ImportText_Add( const TCHAR* Buffer, void* PropertyValue, int32 PortFlags, UObject* Parent, FOutputDevice* ErrorText ) const;`
- L6629 _protected prototype_ `const TCHAR* ImportText_Remove( const TCHAR* Buffer, void* PropertyValue, int32 PortFlags, UObject* Parent, FOutputDevice* ErrorText ) const;`
- L6631 _protected prototype_ `const TCHAR* ImportDelegateFromText(FMulticastScriptDelegate& MulticastDelegate, const TCHAR* Buffer, UObject* OwnerObject, FOutputDevice* ErrorText) const;`

#### class `TProperty_MulticastDelegate`  
`template<class InTCppType> class TProperty_MulticastDelegate : public TProperty<InTCppType, FMulticastDelegateProperty>`  
_L6635-6691_
- inherits: `TProperty<InTCppType,FMulticastDelegateProperty>`
- L6638 _public typedef_ `typedef TProperty<InTCppType, FMulticastDelegateProperty> Super;`
- L6639 _public typedef_ `typedef InTCppType TCppType;`
- L6640 _public typedef_ `typedef typename Super::TTypeFundamentals TTypeFundamentals;`
- L6641 _public function_ `TProperty_MulticastDelegate(FFieldVariant InOwner, const FName& InName, UFunction* InSignatureFunction) : Super(InOwner, InName)`
- L6647 _public function_ `TProperty_MulticastDelegate(FFieldVariant InOwner, const FName& InName) : Super(InOwner, InName)`
- L6653 _public function_ `TProperty_MulticastDelegate(FFieldVariant InOwner, const FName& InName, EObjectFlags InObjectFlags) : TProperty_MulticastDelegate(InOwner, InName)` — `UE_DEPRECATED(5.8, "TProperty_MulticastDelegate constructor with InObjectFlags is deprecated, remove that parameter.")`
- L6655 _public function_ `TProperty_MulticastDelegate(EInternal InInernal, FFieldClass* InClass) : Super(EC_InternalUseOnlyConstructor, InClass)`
- L6665 _public function_ `TProperty_MulticastDelegate(FFieldVariant InOwner, const UECodeGen_Private::FMulticastDelegatePropertyParams& Prop) : Super(InOwner, Prop)` — Constructor used for constructing compiled in properties @param InOwner Owner of the property @param PropBase Pointer to the compiled in structure describing the property
- L6672 _public function_ `explicit consteval TProperty_MulticastDelegate(UE::CodeGen::ConstInit::FPropertyParams InBaseParams, UE::CodeGen::ConstInit::TObjectRefParam<UFunction> InSignatureFunction) : Super(InBaseParams, InSignatureFunction)`
- L6679 _public function_ `explicit TProperty_MulticastDelegate(UField* InField) : Super(InField)`
- L6686 _public function_ `virtual FString GetCPPType(FString* ExtendedTypeText, uint32 CPPExportFlags) const override` — FProperty interface.

#### class `FMulticastInlineDelegateProperty`  
`class FMulticastInlineDelegateProperty : public TProperty_MulticastDelegate<FMulticastScriptDelegate>`  
_L6693-6746_
- inherits: `TProperty_MulticastDelegate<FMulticastScriptDelegate>`
- L6699 _public function_ `FMulticastInlineDelegateProperty(FFieldVariant InOwner, const FName& InName) : TProperty_MulticastDelegate(InOwner, InName)`
- L6704 _public function_ `FMulticastInlineDelegateProperty(FFieldVariant InOwner, const FName& InName, EObjectFlags InObjectFlags) : FMulticastInlineDelegateProperty(InOwner, InName)` — `UE_DEPRECATED(5.8, "FMulticastInlineDelegateProperty constructor with InObjectFlags is deprecated, remove that parameter.")`
- L6711 _public prototype_ `FMulticastInlineDelegateProperty(FFieldVariant InOwner, const UECodeGen_Private::FMulticastDelegatePropertyParams& Prop);` — Constructor used for constructing compiled in properties @param InOwner Owner of the property @param PropBase Pointer to the compiled in structure describing the property
- L6714 _public function_ `explicit consteval FMulticastInlineDelegateProperty( UE::CodeGen::ConstInit::FPropertyParams InBaseParams, UE::CodeGen::ConstInit::TObjectRefParam<UFunction> InSignatureFunction ) : Super(InBaseParams, InSignatureFunction)`
- L6724 _public function_ `explicit FMulticastInlineDelegateProperty(UField* InField) : TProperty_MulticastDelegate(InField)`
- L6731 _public prototype_ `virtual void SerializeItem(FStructuredArchive::FSlot Slot, TNotNull<void*> Value, void const* Defaults) const override;` — FProperty interface
- L6732 _public prototype_ `virtual const TCHAR* ImportText_Internal(const TCHAR* Buffer, TNotNull<void*> ContainerOrPropertyPtr, EPropertyPointerType PropertyPointerType, UObject* OwnerObject, int32 PortFlags, FOutputDevice* ErrorText) const override;`
- L6736 _public prototype_ `virtual const FMulticastScriptDelegate* GetMulticastDelegate(const void* PropertyValue) const override;` — FMulticastDelegateProperty interface
- L6737 _public prototype_ `virtual void SetMulticastDelegate(void* PropertyValue, FMulticastScriptDelegate ScriptDelegate) const override;`
- L6739 _public prototype_ `virtual void AddDelegate(FScriptDelegate ScriptDelegate, UObject* Parent = nullptr, void* PropertyValue = nullptr) const override;`
- L6740 _public prototype_ `virtual void RemoveDelegate(const FScriptDelegate& ScriptDelegate, UObject* Parent = nullptr, void* PropertyValue = nullptr) const override;`
- L6741 _public prototype_ `virtual void ClearDelegate(UObject* Parent = nullptr, void* PropertyValue = nullptr) const override;`
- L6744 _protected prototype_ `virtual FMulticastScriptDelegate& GetMulticastScriptDelegate(const void* PropertyValue, int32 Index) const;`

#### class `FMulticastSparseDelegateProperty`  
`class FMulticastSparseDelegateProperty : public TProperty_MulticastDelegate<FSparseDelegate>`  
_L6748-6805_
- inherits: `TProperty_MulticastDelegate<FSparseDelegate>`
- L6754 _public function_ `FMulticastSparseDelegateProperty(FFieldVariant InOwner, const FName& InName) : TProperty_MulticastDelegate(InOwner, InName)`
- L6759 _public function_ `FMulticastSparseDelegateProperty(FFieldVariant InOwner, const FName& InName, EObjectFlags InObjectFlags) : FMulticastSparseDelegateProperty(InOwner, InName)` — `UE_DEPRECATED(5.8, "FMulticastSparseDelegateProperty constructor with InObjectFlags is deprecated, remove that parameter.")`
- L6766 _public prototype_ `FMulticastSparseDelegateProperty(FFieldVariant InOwner, const UECodeGen_Private::FMulticastDelegatePropertyParams& Prop);` — Constructor used for constructing compiled in properties @param InOwner Owner of the property @param PropBase Pointer to the compiled in structure describing the property
- L6769 _public function_ `explicit consteval FMulticastSparseDelegateProperty( UE::CodeGen::ConstInit::FPropertyParams InBaseParams, UE::CodeGen::ConstInit::TObjectRefParam<UFunction> InSignatureFunction ) : Super(InBaseParams, InSignatureFunction)`
- L6779 _public function_ `explicit FMulticastSparseDelegateProperty(UField* InField) : TProperty_MulticastDelegate(InField)`
- L6786 _public prototype_ `virtual void SerializeItem(FStructuredArchive::FSlot Slot, TNotNull<void*> Value, void const* Defaults) const override;` — FProperty interface
- L6787 _public prototype_ `virtual const TCHAR* ImportText_Internal(const TCHAR* Buffer, TNotNull<void*> ContainerOrPropertyPtr, EPropertyPointerType PropertyPointerType, UObject* OwnerObject, int32 PortFlags, FOutputDevice* ErrorText) const override;`
- L6788 _public prototype_ `virtual bool LoadTypeName(UE::FPropertyTypeName Type, const FPropertyTag* Tag = nullptr) override;`
- L6792 _public prototype_ `virtual const FMulticastScriptDelegate* GetMulticastDelegate(const void* PropertyValue) const override;` — FMulticastDelegateProperty interface
- L6793 _public prototype_ `virtual void SetMulticastDelegate(void* PropertyValue, FMulticastScriptDelegate ScriptDelegate) const override;`
- L6795 _public prototype_ `virtual void AddDelegate(FScriptDelegate ScriptDelegate, UObject* Parent = nullptr, void* PropertyValue = nullptr) const override;`
- L6796 _public prototype_ `virtual void RemoveDelegate(const FScriptDelegate& ScriptDelegate, UObject* Parent = nullptr, void* PropertyValue = nullptr) const override;`
- L6797 _public prototype_ `virtual void ClearDelegate(UObject* Parent = nullptr, void* PropertyValue = nullptr) const override;`
- L6800 _protected prototype_ `virtual FMulticastScriptDelegate& GetMulticastScriptDelegate(const void* PropertyValue, int32 Index) const;`
- L6804 _private prototype_ `virtual void SerializeItemInternal(FArchive& Ar, void* Value, void const* Defaults) const;`

#### struct `FCustomPropertyListNode`  
`struct FCustomPropertyListNode`  
_L6808-6841_
- desc: Describes a single node in a custom property list.
- L6811 _public member_ `FProperty* Property;` — The property that's being referenced at this node.
- L6814 _public member_ `int32 ArrayIndex;` — Used to identify which array index is specifically being referenced if this is an array property. Defaults to 0.
- L6817 _public member_ `struct FCustomPropertyListNode* SubPropertyList;` — If this node represents a struct property, this may contain a "sub" property list for the struct itself.
- L6820 _public member_ `struct FCustomPropertyListNode* PropertyListNext;` — Points to the next node in the list.
- L6823 _public function_ `FCustomPropertyListNode(FProperty* InProperty = nullptr, int32 InArrayIndex = 0) :Property(InProperty) , ArrayIndex(InArrayIndex) , SubPropertyList(nullptr) , PropertyListNext(nullptr)` — Default constructor.
- L6832 _public function_ `inline static FProperty* GetNextPropertyAndAdvance(const FCustomPropertyListNode*& Node)` — Convenience method to return the next property in the list and advance the given ptr.

#### class `FEditPropertyChain`  
`class FEditPropertyChain : public TDoubleLinkedList<FProperty*>`  
_L6848-6938_
- inherits: `TDoubleLinkedList<FProperty*>`
- desc: This class represents the chain of member properties leading to an internal struct property.  It is used for tracking which member property corresponds to the UScriptStruct that owns a particular property.
- L6853 _public function_ `FEditPropertyChain() : ActivePropertyNode(NULL), ActiveMemberPropertyNode(NULL), bFilterAffectedInstances(false)` — Constructors
- L6863 _public prototype_ `bool SetActivePropertyNode( FProperty* NewActiveProperty );` — Sets the ActivePropertyNode to the node associated with the property specified. @param	NewActiveProperty	the FProperty that is currently being evaluated by Pre/PostEditChange @return	true if the ActivePropertyNode was successfully changed to the node associated with the property specified.  false if there was no node corresponding to that property.
- L6874 _public prototype_ `bool SetActiveMemberPropertyNode( FProperty* NewActiveMemberProperty );` — Sets the ActiveMemberPropertyNode to the node associated with the property specified. @param	NewActiveMemberProperty		the member FProperty which contains the property currently being evaluated by Pre/PostEditChange @return	true if the ActiveMemberPropertyNode was successfully changed to the node associated with the property specified.  false if there was no node corresponding to that property.
- L6880 _public function_ `template<typename T> void SetAffectedArchetypeInstances( T&& InAffectedInstances )` — Specify the set of archetype instances that will be affected by the property change.
- L6889 _public prototype_ `bool IsArchetypeInstanceAffected( UObject* InInstance ) const;` — Returns whether the specified archetype instance will be affected by the property change.
- L6894 _public prototype_ `TDoubleLinkedListNode* GetActiveNode() const;` — Returns the node corresponding to the currently active property.
- L6901 _public prototype_ `TDoubleLinkedListNode* GetActiveMemberNode() const;` — Returns the node corresponding to the currently active property, or if the currently active property is not a member variable (i.e. inside of a struct/array), the node corresponding to the member variable which contains the currently active property.
- L6908 _protected member_ `TDoubleLinkedListNode* ActivePropertyNode;` — In a hierarchy of properties being edited, corresponds to the property that is currently being processed by Pre/PostEditChange
- L6916 _protected member_ `TDoubleLinkedListNode* ActiveMemberPropertyNode;` — In a hierarchy of properties being edited, corresponds to the class member property which contains the property that is currently being processed by Pre/PostEditChange.  This will only be different from the ActivePropertyNode if the active property is contained within a struct, dynamic array, or static array.
- L6921 _protected member_ `TSet<UObject*> AffectedInstances;` — Archetype instances that will be affected by the property change.
- L6926 _protected member_ `bool bFilterAffectedInstances;` — Assume all archetype instances are affected unless a set of affected instances is provided.
- L6937 _protected prototype_ `virtual void SetListSize( int32 NewListSize );` — Updates the size reported by Num().  Child classes can use this function to conveniently hook into list additions/removals. This version ensures that the ActivePropertyNode and ActiveMemberPropertyNode point to a valid nodes or NULL if this list is empty. @param	NewListSize		the new size for this list

#### struct `FPropertyChangedEvent`  
`struct FPropertyChangedEvent`  
_L6975-7106_
- desc: Structure for passing pre and post edit change events
- L6977 _public function_ `FPropertyChangedEvent(FProperty* InProperty, EPropertyChangeType::Type InChangeType = EPropertyChangeType::Unspecified, TArrayView<const UObject* const> InTopLevelObjects = TArrayView<const UObject* const>()) : Property(InProperty) , MemberProperty(InProperty) , ChangeType(InChangeType) , ObjectIteratorIndex(INDEX_NONE) , bFilterChangedInstances(false) , TopLevelObjects(InTopLevelObjects)`
- L6987 _public function_ `void SetActiveMemberProperty( FProperty* InActiveMemberProperty )`
- L6995 _public function_ `void SetArrayIndexPerObject(TArrayView<const TMap<FString, int32>> InArrayIndices)` — Saves off map of array indices per object being set.
- L7004 _public function_ `template<typename T> void SetInstancesChanged(T&& InInstancesChanged)` — Specify the set of archetype instances that were modified by the property change.
- L7010 _public function_ `bool GetArrayIndicesPerObject(int32 InObjectIteratorIndex, TMap<FString, int32>& OutArrayIndicesPerObject) const`
- L7025 _public function_ `int32 GetArrayIndex(const FString& InName) const` — Gets the Array Index of the "current object" based on a particular name InName - Name of the property to find the array index for
- L7044 _public function_ `bool HasArchetypeInstanceChanged(UObject* InInstance) const` — Test whether an archetype instance was modified. InInstance - The instance we want to know the status.
- L7052 _public function_ `int32 GetNumObjectsBeingEdited() const` — @return The number of objects being edited during this change event
- L7060 _public function_ `const UObject* GetObjectBeingEdited(int32 Index) const` — Gets an object being edited by this change event.  Multiple objects could be edited at once @param Index	The index of the object being edited. Assumes index is valid.  Call GetNumObjectsBeingEdited first to check if there are valid objects @return The object being edited or nullptr if no object was found
- L7065 _public function_ `FName GetPropertyName() const` — Simple utility to get the name of the property and takes care of the possible null property.
- L7073 _public function_ `FName GetMemberPropertyName() const` — Simple utility to get the name of the object's member property and takes care of the possible null property.
- L7081 _public member_ `FProperty* Property;` — The actual property that changed
- L7087 _public member_ `FProperty* MemberProperty;` — The member property of the object that PostEditChange is being called on. For example if the property that changed is inside a struct on the object, this property is the struct property
- L7090 _public member_ `EPropertyChangeType::Type ChangeType;` — The kind of change event that occurred
- L7093 _public member_ `int32 ObjectIteratorIndex;` — Used by the param system to say which object is receiving the event in the case of multi-select
- L7096 _private member_ `TArrayView<const TMap<FString, int32>> ArrayIndicesPerObject;` — In the property window, multiple objects can be selected at once.  In the case of adding/inserting to an array, each object COULD have different indices for the new entries in the array
- L7099 _private member_ `TSet<UObject*> InstancesChanged;` — In the property window, multiple objects can be selected at once. In this case we want to know if an instance was updated for this operation (used in array/set/map context)
- L7102 _private member_ `bool bFilterChangedInstances;` — Assume all archetype instances were changed unless a set of changed instances is provided.
- L7105 _private member_ `TArrayView<const UObject* const> TopLevelObjects;` — List of top level objects being changed

#### struct `FPropertyChangedChainEvent`  
`struct FPropertyChangedChainEvent : public FPropertyChangedEvent`  
_L7111-7119_
- inherits: `FPropertyChangedEvent`
- desc: Structure for passing pre and post edit change events
- L7113 _public function_ `FPropertyChangedChainEvent(FEditPropertyChain& InPropertyChain, const FPropertyChangedEvent& SrcChangeEvent) : FPropertyChangedEvent(SrcChangeEvent), PropertyChain(InPropertyChain)`
- L7118 _public member_ `FEditPropertyChain& PropertyChain;`

#### enum `EFieldIterationFlags`  
`enum class EFieldIterationFlags : uint8`  
_L7134-7144_
- desc: TFieldIterator construction flags
- L7136 _public enumerator_ `None = 0`
- L7137 _public enumerator_ `IncludeSuper = 1<<0` — Include super class
- L7138 _public enumerator_ `IncludeDeprecated = 1<<1` — Include deprecated properties
- L7139 _public enumerator_ `IncludeInterfaces = 1<<2` — Include interfaces
- L7141 _public enumerator_ `IncludeAll = IncludeSuper | IncludeDeprecated | IncludeInterfaces`
- L7143 _public enumerator_ `Default = IncludeSuper | IncludeDeprecated`

#### enum `EFieldIteratorFlags::SuperClassFlags`  
`enum SuperClassFlags`  
_L7150-7154_
- L7152 _public enumerator_ `ExcludeSuper = (uint8)EFieldIterationFlags::None`
- L7153 _public enumerator_ `IncludeSuper = (uint8)EFieldIterationFlags::IncludeSuper`

#### enum `EFieldIteratorFlags::DeprecatedPropertyFlags`  
`enum DeprecatedPropertyFlags`  
_L7156-7160_
- L7158 _public enumerator_ `ExcludeDeprecated = (uint8)EFieldIterationFlags::None`
- L7159 _public enumerator_ `IncludeDeprecated = (uint8)EFieldIterationFlags::IncludeDeprecated`

#### enum `EFieldIteratorFlags::InterfaceClassFlags`  
`enum InterfaceClassFlags`  
_L7162-7166_
- L7164 _public enumerator_ `ExcludeInterfaces = (uint8)EFieldIterationFlags::None`
- L7165 _public enumerator_ `IncludeInterfaces = (uint8)EFieldIterationFlags::IncludeInterfaces`

#### class `TFieldIterator`  
`template <class T> class TFieldIterator`  
_L7193-7330_
- desc: For iterating through a linked list of fields.
- L7197 _private member_ `const UStruct* Struct;` — The object being searched for the specified field
- L7199 _private member_ `typename T::BaseFieldClass* Field;` — The current location in the list of fields being iterated
- L7201 _private member_ `int32 InterfaceIndex;` — The index of the current interface being iterated
- L7203 _private member_ `const bool bIncludeSuper;` — Whether to include the super class or not
- L7205 _private member_ `const bool bIncludeDeprecated;` — Whether to include deprecated fields or not
- L7207 _private member_ `const bool bIncludeInterface;` — Whether to include interface fields or not
- L7210 _public function_ `TFieldIterator(const UStruct* InStruct, EFieldIterationFlags InIterationFlags = EFieldIterationFlags::Default) : Struct ( InStruct ) , Field ( InStruct ? GetChildFieldsFromStruct<typename T::BaseFieldClass>(InStruct) : NULL ) , InterfaceIndex ( -1 ) , bIncludeSuper ( EnumHasAnyFlags(InIterationFlags, EFieldIterationFlags::IncludeSuper) ) , bIncludeDeprecated( EnumHasAnyFlags(InIterationFlags, EFieldIterationFlags::IncludeDeprecated) ) , bIncludeInterface ( EnumHasAnyFlags(InIterationFlags, EFieldIterationFlags::IncludeInterfaces) && InStruct && InStruct->IsA(UClass::StaticClass()) )`
- L7222 _public function_ `TFieldIterator(const UStruct* InStruct, EFieldIteratorFlags::SuperClassFlags InSuperClassFlags, EFieldIteratorFlags::DeprecatedPropertyFlags InDeprecatedFieldFlags = EFieldIteratorFlags::IncludeDeprecated, EFieldIteratorFlags::InterfaceClassFlags InInterfaceFieldFlags = EFieldIteratorFlags::ExcludeInterfaces) : TFieldIterator(InStruct, (EFieldIterationFlags)(InSuperClassFlags | InDeprecatedFieldFlags | InInterfaceFieldFlags))` — Legacy version taking the flags as 3 separate values
- L7231 _public function_ `UE_FORCEINLINE_HINT explicit operator bool() const` — conversion to "bool" returning true if the iterator is valid.
- L7236 _public function_ `UE_FORCEINLINE_HINT bool operator !() const` — inverse of the "bool" operator
- L7241 _public function_ `inline bool operator==(const TFieldIterator<T>& Rhs) const`
- L7242 _public function_ `inline bool operator!=(const TFieldIterator<T>& Rhs) const`
- L7244 _public function_ `inline void operator++()`
- L7250 _public function_ `inline T* operator*()`
- L7255 _public function_ `inline const T* operator*() const`
- L7260 _public function_ `inline T* operator->()`
- L7265 _public function_ `inline const UStruct* GetStruct()`
- L7270 _protected function_ `inline void IterateToNext()`

#### struct `TFieldRange`  
`template <typename T> struct TFieldRange`  
_L7333-7353_
- L7335 _public function_ `TFieldRange(const UStruct* InStruct, EFieldIterationFlags InIterationFlags = EFieldIterationFlags::Default) : Begin(InStruct, InIterationFlags)`
- L7341 _public function_ `TFieldRange(const UStruct* InStruct, EFieldIteratorFlags::SuperClassFlags InSuperClassFlags, EFieldIteratorFlags::DeprecatedPropertyFlags InDeprecatedFieldFlags = EFieldIteratorFlags::IncludeDeprecated, EFieldIteratorFlags::InterfaceClassFlags InInterfaceFieldFlags = EFieldIteratorFlags::ExcludeInterfaces) : TFieldRange(InStruct, (EFieldIterationFlags)(InSuperClassFlags | InDeprecatedFieldFlags | InInterfaceFieldFlags))` — Legacy version taking the flags as 3 separate values
- L7352 _public member_ `TFieldIterator<T> Begin;`

#### enum `EPropertyValueIteratorFlags`  
`enum class EPropertyValueIteratorFlags : uint8`  
_L7505-7509_
- desc: FPropertyValueIterator construction flags
- L7507 _public enumerator_ `NoRecursion = 0` — Don't recurse at all, only do top level properties
- L7508 _public enumerator_ `FullRecursion = 1` — Recurse into containers and structs

#### class `FPropertyValueIterator`  
`class FPropertyValueIterator`  
_L7512-7703_
- desc: For recursively iterating over a UStruct to find nested FProperty pointers and values
- L7515 _public typedef_ `using BasePairType = TPair<const FProperty*, const void*>;`
- L7526 _public prototype_ `explicit FPropertyValueIterator(FFieldClass* InPropertyClass, const UStruct* InStruct, const void* InStructValue, EPropertyValueIteratorFlags InRecursionFlags = EPropertyValueIteratorFlags::FullRecursion, EFieldIteratorFlags::DeprecatedPropertyFlags InDeprecatedPropertyFlags = EFieldIteratorFlags::IncludeDeprecated);` — Construct an iterator using a struct and struct value @param InPropertyClass	The UClass of the FProperty type you are looking for @param InStruct			The UClass or UScriptStruct containing properties to search for @param InStructValue		Address in memory of struct to search for property values @param InRecursionFlags	Rather to recurse into container and struct properties @param InDeprecatedPropertyFlags	Rather to iterate over deprecated properties
- L7531 _public function_ `FPropertyValueIterator() : PropertyClass(nullptr) , RecursionFlags(EPropertyValueIteratorFlags::FullRecursion) , DeprecatedPropertyFlags(EFieldIteratorFlags::IncludeDeprecated) , bSkipRecursionOnce(false)` — Invalid iterator, start with empty stack
- L7540 _public function_ `inline explicit operator bool() const` — Conversion to "bool" returning true if the iterator is valid
- L7550 _public function_ `UE_FORCEINLINE_HINT bool operator==(const FPropertyValueIterator& Rhs) const`
- L7555 _public function_ `UE_FORCEINLINE_HINT bool operator!=(const FPropertyValueIterator& Rhs) const`
- L7561 _public function_ `inline const BasePairType& operator*() const` — Returns a TPair containing Property/Value currently being iterated
- L7567 _public function_ `inline const BasePairType* operator->() const`
- L7574 _public function_ `UE_FORCEINLINE_HINT const FProperty* Key() const` — Returns Property currently being iterated
- L7580 _public function_ `UE_FORCEINLINE_HINT const void* Value() const` — Returns memory address currently being iterated
- L7586 _public function_ `UE_FORCEINLINE_HINT void operator++()` — Increments iterator
- L7592 _public function_ `UE_FORCEINLINE_HINT void SkipRecursiveProperty()` — Call when iterating a recursive property such as Array or Struct to stop it from iterating into that property
- L7602 _public prototype_ `void GetPropertyChain(TArray<const FProperty*>& PropertyChain) const;` — Returns the full stack of properties for the property currently being iterated. This includes struct and container properties @param PropertyChain	Filled in with ordered list of Properties, with currently active property first and top parent last
- L7617 _public prototype_ `FString GetPropertyPathDebugString() const;` — Returns a string of the property chain in a form that makes reading it easy.  The format may change over time, do not depend on this being in a specific Unreal path format.  It's primary intention is to aid in debugging and in reporting paths to the end developer in an editor environment. Now for the implementation details, normally paths involving an array, will do things like print the array name twice, since an array in the path is actually 2 properties, one for the array and another for the index. Maps are similar.  The end result is stuff like seeing, ActionsArray.ActionsArray.ActionIfo.ActionPower. What this function does is tries to make this stuff a lot more human readable, by printing, ActionsArray[3].ActionIfo.ActionPower, so that you know the index it comes from.  Similarly Maps would print ActionMap["Action Name"].ActionIfo.ActionPower, so that you know the index it comes from.  Similarly Maps would print
- L7672 _private member_ `TArray<FPropertyValueStackEntry, TInlineAllocator<8>> PropertyIteratorStack;` — Internal stack, one per continer/struct
- L7675 _private member_ `FFieldClass* PropertyClass = nullptr;` — Property type that is explicitly checked for
- L7678 _private member_ `const EPropertyValueIteratorFlags RecursionFlags;` — Whether to recurse into containers/structs
- L7681 _private member_ `const EFieldIteratorFlags::DeprecatedPropertyFlags DeprecatedPropertyFlags;` — Inherits to child field iterator
- L7684 _private member_ `bool bSkipRecursionOnce = false;` — If true, next iteration will skip recursing into containers/structs
- L7687 _private member_ `bool bMatchAll = false;` — If true, all properties will be matched without checking IsA(PropertyClass)
- L7690 _private prototype_ `EPropertyValueFlags GetPropertyValueFlags(const FProperty* Property) const;` — Returns EPropertyValueFlags to describe if this Property is a match and/or a container/struct
- L7693 _private prototype_ `void FillStructProperties(const UStruct* Struct, FPropertyValueStackEntry& Entry);` — Fills the Entry.ValueArray with all relevant properties found in Struct
- L7699 _private prototype_ `bool NextValue(EPropertyValueIteratorFlags RecursionFlags);` — Goes to the next Property/value pair. Returns false on a match or out of properties, true when iteration should continue
- L7702 _private prototype_ `void IterateToNext();` — Iterates to next property being checked for or until reaching the end of the structure

#### enum `FPropertyValueIterator::EPropertyValueFlags`  
`enum class EPropertyValueFlags : uint8`  
_L7620-7632_
- L7622 _public enumerator_ `None = 0x0`
- L7623 _public enumerator_ `IsMatch = 0x01`
- L7625 _public enumerator_ `IsOptional = 0x08`
- L7626 _public enumerator_ `IsArray = 0x10`
- L7627 _public enumerator_ `IsMap = 0x20`
- L7628 _public enumerator_ `IsSet = 0x40`
- L7629 _public enumerator_ `IsStruct = 0x80`

#### struct `FPropertyValueIterator::FPropertyValueStackEntry`  
`struct FPropertyValueStackEntry`  
_L7635-7669_
- L7638 _public member_ `const void* Owner = nullptr;` — Address of owning UStruct or FProperty container
- L7641 _public typedef_ `typedef TPair<BasePairType, EPropertyValueFlags> BasePairAndFlags;` — List of current root property+value pairs for the current top level FProperty
- L7642 _public typedef_ `typedef TArray<BasePairAndFlags, TInlineAllocator<8>> FValueArrayType;`
- L7643 _public member_ `FValueArrayType ValueArray;`
- L7646 _public member_ `int32 ValueIndex = -1;` — Current position inside ValueArray
- L7649 _public member_ `int32 NextValueIndex = 0;` — Next position inside ValueArray
- L7651 _public function_ `FPropertyValueStackEntry(const void* InValue) : Owner(InValue)`
- L7655 _public function_ `FPropertyValueStackEntry(const UStruct* InStruct, const void* InValue, EFieldIteratorFlags::DeprecatedPropertyFlags InDeprecatedPropertyFlags) : Owner(InValue)`
- L7659 _public function_ `UE_FORCEINLINE_HINT bool operator==(const FPropertyValueStackEntry& Rhs) const`
- L7664 _public function_ `UE_FORCEINLINE_HINT const BasePairType& GetPropertyValue() const`

#### class `TPropertyValueIterator`  
`template <class T> class TPropertyValueIterator : public FPropertyValueIterator`  
_L7707-7746_
- inherits: `FPropertyValueIterator`
- desc: Templated version, will verify the property type is correct and will skip any properties that are not
- L7710 _public typedef_ `using PairType = TPair<const T*, const void*>;`
- L7720 _public function_ `explicit TPropertyValueIterator(const UStruct* InStruct, const void* InStructValue, EPropertyValueIteratorFlags InRecursionFlags = EPropertyValueIteratorFlags::FullRecursion, EFieldIteratorFlags::DeprecatedPropertyFlags InDeprecatedPropertyFlags = EFieldIteratorFlags::IncludeDeprecated) : FPropertyValueIterator(T::StaticClass(), InStruct, InStructValue, InRecursionFlags, InDeprecatedPropertyFlags)` — Construct an iterator using a struct and struct value @param InStruct			The UClass or UScriptStruct containing properties to search for @param InStructValue		Address in memory of struct to search for property values @param InRecursionFlags	Rather to recurse into container and struct properties @param InDeprecatedPropertyFlags	Rather to iterate over deprecated properties
- L7728 _public prototype_ `TPropertyValueIterator() = default;` — Invalid iterator, start with empty stack
- L7731 _public function_ `UE_FORCEINLINE_HINT const PairType& operator*() const` — Returns a TPair containing Property/Value currently being iterated
- L7736 _public function_ `UE_FORCEINLINE_HINT const PairType* operator->() const`
- L7742 _public function_ `UE_FORCEINLINE_HINT const T* Key() const` — Returns Property currently being iterated

#### struct `TPropertyValueRange`  
`template <class T> struct TPropertyValueRange`  
_L7750-7771_
- desc: Templated range to allow ranged-for syntax
- L7760 _public function_ `TPropertyValueRange(const UStruct* InStruct, const void* InStructValue, EPropertyValueIteratorFlags InRecursionFlags = EPropertyValueIteratorFlags::FullRecursion, EFieldIteratorFlags::DeprecatedPropertyFlags InDeprecatedPropertyFlags = EFieldIteratorFlags::IncludeDeprecated) : Begin(InStruct, InStructValue, InRecursionFlags, InDeprecatedPropertyFlags)` — Construct a range using a struct and struct value @param InStruct			The UClass or UScriptStruct containing properties to search for @param InStructValue		Address in memory of struct to search for property values @param InRecursionFlags	Rather to recurse into container and struct properties @param InDeprecatedPropertyFlags	Rather to iterate over deprecated properties
- L7770 _public member_ `TPropertyValueIterator<T> Begin;`

#### Free symbols / members of external scopes

- L65 _macro_ `#define UE_API COREUOBJECT_API`
- L77 _namespace_ `namespace UE`
- L78 _namespace_ `namespace UE`
- L79 _namespace_ `namespace UE`
- L79 _namespace_ `namespace GC` (scope `UE`)
- L87 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogType, Log, All);`
- L89 _namespace_ `namespace UE`
- L89 _namespace_ `namespace CoreUObject` (scope `UE`)
- L89 _namespace_ `namespace Private` (scope `UE::CoreUObject`)
- L98 _prototype_ `ENonNullableBehavior GetNonNullableBehavior();` (scope `UE::CoreUObject::Private`)
- L151 _namespace_ `namespace UEProperty_Private`
- L161 _namespace_ `namespace UE`
- L161 _namespace_ `namespace CoreUObject` (scope `UE`)
- L161 _namespace_ `namespace Private` (scope `UE::CoreUObject`)
- L165 _prototype_ `const TCHAR* ImportEnumFromBuffer(UEnum* Enum, const FProperty* PropertyToSet, const FNumericProperty* UnderlyingProp, const TCHAR* PropertyClassName, const TCHAR* Buffer, void* ContainerOrPropertyPtr, EPropertyPointerType PropertyPointerType, FOutputDevice* ErrorText);` (scope `UE::CoreUObject::Private`) — Defined in EnumProperty.cpp and used by both FEnumProperty and FByteProperty. They don't have an API macro because they're not intended to be called outside of CoreUObject.
- L167 _prototype_ `void ExportEnumToBuffer(const UEnum* Enum, const FProperty* Prop, const FNumericProperty* NumericProp, FString& ValueStr, const void* PropertyValueOrContainer, EPropertyPointerType PropertyPointerType, const void* DefaultValue, UObject* Parent, int32 PortFlags, UObject* ExportRootScope);` (scope `UE::CoreUObject::Private`)
- L193 _member_ `int32 IndexInOwner = -1;` (scope `FProperty::__anond06f6095010a`) — Index of the property within its owner, inclusive of base properties. Generated during Link().
- L200 _member_ `int32 NumMetaDataParams;` (scope `FProperty::__anond06f6095010a`) — Number of metadata parameters stored in this object at compile time from UHT This union member is active until initial UObject construction in UObjectProcessRegistrants populates runtime metadata
- L216 _member_ `FProperty* NextRef = nullptr;` (scope `FProperty::__anond06f6095020a`) — In memory only: Linked list of object reference properties from most-derived to base
- L222 _member_ `const UE::CodeGen::ConstInit::FMetaData* MetaDataParams;` (scope `FProperty::__anond06f6095020a`) — Metadata parameters stored in this object at compile time from UHT This union member is active until initial UObject construction in UObjectProcessRegistrants populates runtime metadata
- L228 _member_ `FProperty* DestructorLinkNext = nullptr;` (scope `FProperty::__anond06f6095030a`) — In memory only: Linked list of properties requiring destruction. Note this does not include things that will be destroyed by the native destructor
- L234 _member_ `const UTF8CHAR* RepNotifyFuncNameUTF8;` (scope `FProperty::__anond06f6095030a`) — RepNotify function name stored in this object at compile time from UHT This union member is active until initial UObject construction in UObjectProcessRegistrants
- L1396 _namespace_ `namespace UEProperty_Private`
- L1468 _enumerator_ `CPPSize = sizeof(TCppType)` (scope `TPropertyTypeFundamentals::__anond06f60950503`)
- L1469 _enumerator_ `CPPAlignment = alignof(TCppType)` (scope `TPropertyTypeFundamentals::__anond06f60950503`)
- L2580 _typedef_ `using FLargeWorldCoordinatesRealProperty = FDoubleProperty;`
- L3130 _prototype_ `ENUM_CLASS_FLAGS(EObjectPropertyOptions);`
- L3770 _typedef_ `using FFreezableScriptArray = TScriptArray<TMemoryImageAllocator<DEFAULT_ALIGNMENT>>;`
- L3789 _enumerator_ `CPPSize = sizeof(FScriptArray)` (scope `FArrayProperty::__anond06f60950603`) — These need to be the same as FFreezableScriptArray
- L3790 _enumerator_ `CPPAlignment = alignof(FScriptArray)` (scope `FArrayProperty::__anond06f60950603`)
- L3915 _typedef_ `using FFreezableScriptMap = TScriptMap<FMemoryImageSetAllocator>;`
- L4060 _function_ `return WithScriptMap(InMap, [](auto* Map) { return Map->Num(); });` (scope `FMapProperty::GetNum`)
- L4078 _function_ `return WithScriptMap(InMap, [InternalIndex](auto* Map) { return Map->IsValidIndex(InternalIndex); });` (scope `FMapProperty::IsValidIndex`)
- L4087 _function_ `return WithScriptMap(InMap, [this, InternalIndex](auto* Map) { return (uint8*)Map->GetData(InternalIndex, MapLayout); });` (scope `FMapProperty::GetPairPtr`)
- L4305 _function_ `int32 Result = WithScriptArray([](auto* Array) { return Array->Num(); });` (scope `FScriptArrayHelper::Num`)
- L4316 _function_ `int32 Result = WithScriptArray([](auto* Array) { return Array->NumUnchecked(); });` (scope `FScriptArrayHelper::NumUnchecked`)
- L4332 _function_ `return (uint8*)WithScriptArray([](auto* Array) { return Array->GetData(); }) + Index * static_cast<size_t>(ElementSize);` (scope `FScriptArrayHelper::GetRawPtr`)
- L4432 _function_ `const int32 OldNum = WithScriptArray([this, Count](auto* Array) { return Array->Add(Count, ElementSize, ElementAlignment); });` (scope `FScriptArrayHelper::AddUninitializedValues`)
- L4452 _function_ `WithScriptArray([this, Index, Count](auto* Array) { Array->Insert(Index, Count, ElementSize, ElementAlignment); });` (scope `FScriptArrayHelper::InsertValues`)
- L4469 _function_ `WithScriptArray([this, Slack](auto* Array) { Array->Empty(Slack, ElementSize, ElementAlignment); });` (scope `FScriptArrayHelper::EmptyValues`)
- L4482 _function_ `WithScriptArray([this, Index, Count](auto* Array) { Array->Remove(Index, Count, ElementSize, ElementAlignment); });` (scope `FScriptArrayHelper::RemoveValues`)
- L4504 _function_ `WithScriptArray([this, A, B](auto* Array) { Array->SwapMemory(A, B, ElementSize); });` (scope `FScriptArrayHelper::SwapValues`)
- L4517 _function_ `WithScriptArray([this, InOtherArray](auto* Array) { Array->MoveAssign(*static_cast<decltype(Array)>(InOtherArray), ElementSize, ElementAlignment); });` (scope `FScriptArrayHelper::MoveAssign`)
- L4526 _function_ `WithScriptArray([this, &Ar](auto* Array) { Array->CountBytes(Ar, ElementSize); });` (scope `FScriptArrayHelper::CountBytes`)
- L4534 _function_ `WithScriptArray([](auto* Array) { DestructItem(Array); });` (scope `FScriptArrayHelper::DestroyContainer_Unsafe`)
- L4643 _member_ `FScriptArray* HeapArray;` (scope `FScriptArrayHelper::__anond06f6095150a`)
- L4644 _member_ `FFreezableScriptArray* FreezableArray;` (scope `FScriptArrayHelper::__anond06f6095150a`)
- L4816 _function_ `return WithScriptMap([InternalIndex](auto* Map) { return Map->IsValidIndex(InternalIndex); });` (scope `FScriptMapHelper::IsValidIndex`)
- L4826 _function_ `int32 Result = WithScriptMap([](auto* Map) { return Map->Num(); });` (scope `FScriptMapHelper::Num`)
- L4838 _function_ `int32 Result = WithScriptMap([](auto* Map) { return Map->NumUnchecked(); });` (scope `FScriptMapHelper::NumUnchecked`)
- L4851 _function_ `` (scope `FScriptMapHelper::GetMaxIndex`)
- L4868 _function_ `` (scope `FScriptMapHelper::GetPairPtr`)
- L4904 _function_ `` (scope `FScriptMapHelper::GetKeyPtr`)
- L4926 _function_ `` (scope `FScriptMapHelper::GetValuePtr`)
- L5086 _function_ `` (scope `FScriptMapHelper::MoveAssign`)
- L5099 _function_ `` (scope `FScriptMapHelper::AddUninitializedValue`)
- L5122 _function_ `` (scope `FScriptMapHelper::EmptyValues`)
- L5137 _function_ `` (scope `FScriptMapHelper::AddDefaultValue_Invalid_NeedsRehash`)
- L5175 _function_ `` (scope `FScriptMapHelper::RemoveAt`)
- L5183 _function_ `` (scope `FScriptMapHelper::RemoveAt::__anond06f60952402`)
- L5233 _function_ `` (scope `FScriptMapHelper::FindInternalIndex`)
- L5270 _function_ `` (scope `FScriptMapHelper::FindLogicalIndex`)
- L5307 _function_ `` (scope `FScriptMapHelper::FindMapIndexWithKey`)
- L5368 _function_ `` (scope `FScriptMapHelper::FindMapPairIndexFromHash`)
- L5372 _function_ `KeyPtr, MapLayout, [LocalKeyPropForCapture](const void* ElementKey)` (scope `FScriptMapHelper::FindMapPairIndexFromHash::__anond06f60952a02`)
- L5391 _function_ `` (scope `FScriptMapHelper::FindValueFromHash`)
- L5395 _function_ `KeyPtr, MapLayout, [LocalKeyPropForCapture](const void* ElementKey)` (scope `FScriptMapHelper::FindValueFromHash::__anond06f60952d02`)
- L5405 _function_ `` (scope `FScriptMapHelper::AddPair`)
- L5410 _function_ `KeyPtr, ValuePtr, MapLayout, [LocalKeyPropForCapture](const void* ElementKey)` (scope `FScriptMapHelper::AddPair::__anond06f60953002`)
- L5411 _function_ `ValuePtr, MapLayout, [LocalKeyPropForCapture](const void* ElementKey)` (scope `FScriptMapHelper::AddPair::__anond06f60953002`)
- L5413 _function_ `` (scope `FScriptMapHelper::AddPair::__anond06f60953002`)
- L5471 _function_ `` (scope `FScriptMapHelper::FindOrAdd`)
- L5475 _function_ `KeyPtr, MapLayout, [LocalKeyPropForCapture](const void* ElementKey)` (scope `FScriptMapHelper::FindOrAdd::__anond06f60953802`)
- L5478 _function_ `` (scope `FScriptMapHelper::FindOrAdd::__anond06f60953802`)
- L5508 _function_ `` (scope `FScriptMapHelper::RemovePair`)
- L5512 _function_ `KeyPtr, MapLayout, [LocalKeyPropForCapture](const void* ElementKey)` (scope `FScriptMapHelper::RemovePair::__anond06f60953c02`)
- L5574 _function_ `void* Dest = WithScriptMap([this, InternalIndex](auto* Map) { return Map->GetData(InternalIndex, MapLayout); });` (scope `FScriptMapHelper::ConstructItem`)
- L5612 _function_ `uint8* PairPtr = WithScriptMap([this, InternalIndex](auto* Map) { return (uint8*)Map->GetData(InternalIndex, MapLayout); });` (scope `FScriptMapHelper::DestructItems`)
- L5665 _function_ `return WithScriptMap([this, InternalIndex](auto* Map) { return (uint8*)Map->GetData(InternalIndex, MapLayout); });` (scope `FScriptMapHelper::GetPairPtrWithoutCheck`)
- L5689 _function_ `return WithScriptMap([this, InternalIndex](auto* Map) { return (uint8*)Map->GetData(InternalIndex, MapLayout); });` (scope `FScriptMapHelper::GetKeyPtrWithoutCheck`)
- L5713 _function_ `return WithScriptMap([this, InternalIndex](auto* Map) { return (uint8*)Map->GetData(InternalIndex, MapLayout) + MapLayout.ValueOffset; });` (scope `FScriptMapHelper::GetValuePtrWithoutCheck`)
- L5733 _member_ `FScriptMap* HeapMap;` (scope `FScriptMapHelper::__anond06f6095440a`)
- L5734 _member_ `FFreezableScriptMap* FreezableMap;` (scope `FScriptMapHelper::__anond06f6095440a`)
- L6023 _function_ `` (scope `FScriptSetHelper::RemoveAt`)
- L6194 _function_ `ElementToFind, SetLayout, [LocalElementPropForCapture](const void* Element)` (scope `FScriptSetHelper::FindElementIndexFromHash`)
- L6215 _function_ `ElementToAdd, SetLayout, [LocalElementPropForCapture](const void* Element)` (scope `FScriptSetHelper::AddElement`)
- L6218 _function_ `` (scope `FScriptSetHelper::AddElement`)
- L6247 _function_ `ElementToRemove, SetLayout, [LocalElementPropForCapture](const void* Element)` (scope `FScriptSetHelper::RemoveElement`)
- L6944 _namespace_ `namespace EPropertyChangeType`
- L6946 _typedef_ `typedef uint32 Type;` (scope `EPropertyChangeType`)
- L6949 _variable_ `inline const Type Unspecified = 1 << 0;` (scope `EPropertyChangeType`) — default value.  Add new enums to add new functionality.
- L6951 _variable_ `inline const Type ArrayAdd = 1 << 1;` (scope `EPropertyChangeType`) — Array Add
- L6953 _variable_ `inline const Type ArrayRemove = 1 << 2;` (scope `EPropertyChangeType`) — Array Remove
- L6955 _variable_ `inline const Type ArrayClear = 1 << 3;` (scope `EPropertyChangeType`) — Array Clear
- L6957 _variable_ `inline const Type ValueSet = 1 << 4;` (scope `EPropertyChangeType`) — Value Set
- L6959 _variable_ `inline const Type Duplicate = 1 << 5;` (scope `EPropertyChangeType`) — Duplicate
- L6961 _variable_ `inline const Type Interactive = 1 << 6;` (scope `EPropertyChangeType`) — Interactive, e.g. dragging a slider. Will be followed by a ValueSet when finished.
- L6963 _variable_ `inline const Type Redirected = 1 << 7;` (scope `EPropertyChangeType`) — Redirected.  Used when property references are updated due to content hot-reloading, or an asset being replaced during asset deletion (aka, asset consolidation).
- L6965 _variable_ `inline const Type ArrayMove = 1 << 8;` (scope `EPropertyChangeType`) — Array Item Moved Within the Array
- L6967 _variable_ `inline const Type ToggleEditable = 1 << 9;` (scope `EPropertyChangeType`) — Edit Condition State has changed
- L6969 _variable_ `inline const Type ResetToDefault = 1 << 10;` (scope `EPropertyChangeType`)
- L7121 _namespace_ `namespace UEProperty_Private`
- L7123 _typedef_ `using FPropertyListBuilderPropertyLink = TLinkedListBuilder<FProperty, TLinkedListBuilderNextLinkMemberVar<FProperty, &FProperty::PropertyLinkNext>>;` (scope `UEProperty_Private`)
- L7124 _typedef_ `using FPropertyListBuilderRefLink = TLinkedListBuilder<FProperty, TLinkedListBuilderNextLinkMemberVar<FProperty, &FProperty::NextRef>>;` (scope `UEProperty_Private`)
- L7125 _typedef_ `using FPropertyListBuilderDestructorLink = TLinkedListBuilder<FProperty, TLinkedListBuilderNextLinkMemberVar<FProperty, &FProperty::DestructorLinkNext>>;` (scope `UEProperty_Private`)
- L7126 _typedef_ `using FPropertyListBuilderPostConstructLink = TLinkedListBuilder<FProperty, TLinkedListBuilderNextLinkMemberVar<FProperty, &FProperty::PostConstructLinkNext>>;` (scope `UEProperty_Private`)
- L7145 _prototype_ `ENUM_CLASS_FLAGS(EFieldIterationFlags);`
- L7148 _namespace_ `namespace EFieldIteratorFlags`
- L7170 _function_ `template <class FieldType> FieldType* GetChildFieldsFromStruct(const UStruct* Owner)`
- L7177 _function_ `template <> inline UField* GetChildFieldsFromStruct(const UStruct* Owner)`
- L7183 _function_ `template <> inline FField* GetChildFieldsFromStruct(const UStruct* Owner)`
- L7349 _function_ `friend TFieldIterator<T> begin(const TFieldRange& Range)`
- L7350 _function_ `friend TFieldIterator<T> end (const TFieldRange& Range)`
- L7360 _function_ `template <UE::CDerivedFrom<UField> T> T* FindUField(const UStruct* Owner, FName FieldName, EFieldIterationFlags IterationFlags = EFieldIterationFlags::Default)`
- L7384 _function_ `template <UE::CDerivedFrom<UField> T> T* FindUField(const UStruct* Owner, const TCHAR* FieldName, EFieldIterationFlags IterationFlags = EFieldIterationFlags::Default)`
- L7394 _function_ `template <UE::CDerivedFrom<FField> T> T* FindFProperty(const UStruct* Owner, FName FieldName, EFieldIterationFlags IterationFlags = EFieldIterationFlags::Default)`
- L7418 _function_ `template <UE::CDerivedFrom<FField> T> T* FindFProperty(const UStruct* Owner, const TCHAR* FieldName, EFieldIterationFlags IterationFlags = EFieldIterationFlags::Default)`
- L7428 _function_ `inline FFieldVariant FindUFieldOrFProperty(const UStruct* Owner, FName FieldName, EFieldIterationFlags IterationFlags = EFieldIterationFlags::Default)` — Finds FProperties or UFunctions and UEnums
- L7440 _function_ `inline FFieldVariant FindUFieldOrFProperty(const UStruct* Owner, const TCHAR* FieldName, EFieldIterationFlags IterationFlags = EFieldIterationFlags::Default)` — Finds FProperties or UFunctions and UEnums
- L7448 _function_ `template <UE::CDerivedFrom<UField> T> T* FindUFieldOrFProperty(const UStruct* Owner, FName FieldName, EFieldIterationFlags IterationFlags = EFieldIterationFlags::Default)`
- L7454 _function_ `template <UE::CDerivedFrom<UField> T> T* FindUFieldOrFProperty(const UStruct* Owner, const TCHAR* FieldName, EFieldIterationFlags IterationFlags = EFieldIterationFlags::Default)`
- L7460 _function_ `template <UE::CDerivedFrom<FField> T> T* FindUFieldOrFProperty(const UStruct* Owner, FName FieldName, EFieldIterationFlags IterationFlags = EFieldIterationFlags::Default)`
- L7466 _function_ `template <UE::CDerivedFrom<FField> T> T* FindUFieldOrFProperty(const UStruct* Owner, const TCHAR* FieldName, EFieldIterationFlags IterationFlags = EFieldIterationFlags::Default)`
- L7478 _function_ `template<typename T> T* FindFieldChecked( const UStruct* Scope, FName FieldName )` — Search for the named field within the specified scope, including any Outer classes; assert on failure. @param	Scope		the scope to search for the field in @param	FieldName	the name of the field to search for.
- L7767 _function_ `friend TPropertyValueIterator<T> begin(const TPropertyValueRange& Range)`
- L7768 _function_ `friend TPropertyValueIterator<T> end(const TPropertyValueRange& Range)`
- L7776 _function_ `inline bool UObject::IsBasedOnArchetype( const UObject* const SomeObject ) const` (scope `UObject`) — Determine if this object has SomeObject in its archetype chain.
- L7801 _macro_ `#define CPP_ARRAY_DIM(ArrayName, ClassName) \` — helper to calculate an array's dimensions

### `Source/Runtime/CoreUObject/Public/UObject/UnrealTypePrivate.h` (Public)


#### class `UProperty`  
`class UProperty : public UField`  
_L17-182_
- reflection: `UCLASS(Abstract, Config=Engine)`
- inherits: `UField`
- L24 _public member_ `int32 ArrayDim;` — Persistent variables.
- L25 _public member_ `int32 ElementSize;`
- L26 _public member_ `EPropertyFlags PropertyFlags;`
- L27 _public member_ `uint16 RepIndex;`
- L29 _public member_ `TEnumAsByte<ELifetimeCondition> BlueprintReplicationCondition;`
- L32 _public member_ `int32 Offset_Internal;` — In memory variables (generated during Link()).
- L34 _public member_ `FName RepNotifyFunc;`
- L37 _public member_ `UProperty* PropertyLinkNext;` — In memory only: Linked list of properties from most-derived to base
- L39 _public member_ `UProperty* NextRef;` — In memory only: Linked list of object reference properties from most-derived to base
- L41 _public member_ `UProperty* DestructorLinkNext;` — In memory only: Linked list of properties requiring destruction. Note this does not include things that will be destroyed by the native destructor
- L43 _public member_ `UProperty* PostConstructLinkNext;` — In memory only: Linked list of properties requiring post constructor initialization.
- L47 _public prototype_ `UProperty(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());` — Constructors.
- L48 _public prototype_ `UProperty(ECppProperty, int32 InOffset, EPropertyFlags InFlags);`
- L49 _public prototype_ `UProperty( const FObjectInitializer& ObjectInitializer, ECppProperty, int32 InOffset, EPropertyFlags InFlags );`
- L52 _public prototype_ `virtual void Serialize( FArchive& Ar ) override;` — UObject interface
- L58 _public function_ `UProperty* GetOwnerProperty()` — Returns the first UProperty in this property's Outer chain that does not have a UProperty for an Outer
- L68 _public function_ `const UProperty* GetOwnerProperty() const`
- L78 _public function_ `UE_FORCEINLINE_HINT bool HasAnyPropertyFlags( uint64 FlagsToCheck ) const`
- L92 _public function_ `UE_FORCEINLINE_HINT bool HasAllPropertyFlags( uint64 FlagsToCheck ) const` — Used to safely check whether all of the passed in flags are set. This is required as PropertyFlags currently is a 64 bit data type and bool is a 32 bit data type so simply using PropertyFlags&CPF_MyFlagBiggerThanMaxInt won't work correctly when assigned directly to an bool. @param FlagsToCheck	Object flags to check for @return true if all of the passed in flags are set (including no flags passed in), false otherwise
- L104 _public function_ `UE_FORCEINLINE_HINT bool IsEditorOnlyProperty() const` — Editor-only properties are those that only are used with the editor is present or cannot be removed from serialisation. Editor-only properties include: EditorOnly properties Properties that cannot be removed from serialisation are: Boolean properties (may affect GCC_BITFIELD_MAGIC computation) Native properties (native serialisation)
- L111 _private function_ `inline void* ContainerVoidPtrToValuePtrInternal(void* ContainerPtr, int32 ArrayIndex) const`
- L125 _private function_ `inline void* ContainerUObjectPtrToValuePtrInternal(UObject* ContainerPtr, int32 ArrayIndex) const`
- L155 _public function_ `template<typename ValueType> UE_FORCEINLINE_HINT ValueType* ContainerPtrToValuePtr(UObject* ContainerPtr, int32 ArrayIndex = 0) const`
- L160 _public function_ `template<typename ValueType> UE_FORCEINLINE_HINT ValueType* ContainerPtrToValuePtr(void* ContainerPtr, int32 ArrayIndex = 0) const`
- L165 _public function_ `template<typename ValueType> UE_FORCEINLINE_HINT ValueType const* ContainerPtrToValuePtr(UObject const* ContainerPtr, int32 ArrayIndex = 0) const`
- L170 _public function_ `template<typename ValueType> UE_FORCEINLINE_HINT ValueType const* ContainerPtrToValuePtr(void const* ContainerPtr, int32 ArrayIndex = 0) const`
- L177 _public member_ `FField* AssociatedField;`
- L179 _public prototype_ `virtual FField* GetAssociatedFField() override;`
- L180 _public prototype_ `virtual void SetAssociatedFField(FField* InField) override;`

#### class `UNumericProperty`  
`class UNumericProperty : public UProperty`  
_L185-202_
- reflection: `UCLASS(Abstract, Config = Engine)`
- inherits: `UProperty`
- L190 _public function_ `UNumericProperty(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()) : Super(ObjectInitializer)`
- L195 _public function_ `UNumericProperty(ECppProperty, int32 InOffset, EPropertyFlags InFlags) : UProperty(FObjectInitializer::Get(), EC_CppProperty, InOffset, InFlags)`
- L199 _public function_ `UNumericProperty( const FObjectInitializer& ObjectInitializer, ECppProperty, int32 InOffset, EPropertyFlags InFlags ) : UProperty( ObjectInitializer, EC_CppProperty, InOffset, InFlags )`

#### class `UByteProperty`  
`class UByteProperty : public UNumericProperty`  
_L205-235_
- reflection: `UCLASS(Config = Engine)`
- inherits: `UNumericProperty`
- L213 _public member_ `TObjectPtr<UEnum> Enum;` — `UPROPERTY(SkipSerialization)` — Variables.
- L215 _public function_ `UByteProperty(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()) : Super(ObjectInitializer)`
- L220 _public function_ `UByteProperty(ECppProperty, int32 InOffset, EPropertyFlags InFlags, UEnum* InEnum = nullptr) : UNumericProperty(FObjectInitializer::Get(), EC_CppProperty, InOffset, InFlags) , Enum(InEnum)`
- L226 _public function_ `UByteProperty(const FObjectInitializer& ObjectInitializer, ECppProperty, int32 InOffset, EPropertyFlags InFlags, UEnum* InEnum = nullptr) : UNumericProperty( ObjectInitializer, EC_CppProperty, InOffset, InFlags) , Enum( InEnum )`
- L233 _public prototype_ `virtual void Serialize( FArchive& Ar ) override;` — UObject interface.

#### class `UInt8Property`  
`class UInt8Property : public UNumericProperty`  
_L238-257_
- reflection: `UCLASS(Config = Engine)`
- inherits: `UNumericProperty`
- L243 _public function_ `UInt8Property(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()) : Super(ObjectInitializer)`
- L248 _public function_ `UInt8Property(ECppProperty, int32 InOffset, EPropertyFlags InFlags) : UNumericProperty(FObjectInitializer::Get(), EC_CppProperty, InOffset, InFlags)`
- L253 _public function_ `UInt8Property( const FObjectInitializer& ObjectInitializer, ECppProperty, int32 InOffset, EPropertyFlags InFlags ) : UNumericProperty( ObjectInitializer, EC_CppProperty, InOffset, InFlags)`

#### class `UInt16Property`  
`class UInt16Property : public UNumericProperty`  
_L260-279_
- reflection: `UCLASS(Config = Engine)`
- inherits: `UNumericProperty`
- L265 _public function_ `UInt16Property(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()) : Super(ObjectInitializer)`
- L270 _public function_ `UInt16Property(ECppProperty, int32 InOffset, EPropertyFlags InFlags) : UNumericProperty(FObjectInitializer::Get(), EC_CppProperty, InOffset, InFlags)`
- L275 _public function_ `UInt16Property( const FObjectInitializer& ObjectInitializer, ECppProperty, int32 InOffset, EPropertyFlags InFlags ) : UNumericProperty( ObjectInitializer, EC_CppProperty, InOffset, InFlags)`

#### class `UIntProperty`  
`class UIntProperty : public UNumericProperty`  
_L282-301_
- reflection: `UCLASS(Config = Engine)`
- inherits: `UNumericProperty`
- L287 _public function_ `UIntProperty(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()) : Super(ObjectInitializer)`
- L292 _public function_ `UIntProperty(ECppProperty, int32 InOffset, EPropertyFlags InFlags) : UNumericProperty(FObjectInitializer::Get(), EC_CppProperty, InOffset, InFlags)`
- L297 _public function_ `UIntProperty( const FObjectInitializer& ObjectInitializer, ECppProperty, int32 InOffset, EPropertyFlags InFlags ) : UNumericProperty( ObjectInitializer, EC_CppProperty, InOffset, InFlags)`

#### class `UInt64Property`  
`class UInt64Property : public UNumericProperty`  
_L304-323_
- reflection: `UCLASS(Config = Engine)`
- inherits: `UNumericProperty`
- L309 _public function_ `UInt64Property(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()) : Super(ObjectInitializer)`
- L314 _public function_ `UInt64Property(ECppProperty, int32 InOffset, EPropertyFlags InFlags) : UNumericProperty(FObjectInitializer::Get(), EC_CppProperty, InOffset, InFlags)`
- L319 _public function_ `UInt64Property( const FObjectInitializer& ObjectInitializer, ECppProperty, int32 InOffset, EPropertyFlags InFlags ) : UNumericProperty( ObjectInitializer, EC_CppProperty, InOffset, InFlags )`

#### class `UUInt16Property`  
`class UUInt16Property : public UNumericProperty`  
_L326-345_
- reflection: `UCLASS(Config = Engine)`
- inherits: `UNumericProperty`
- L331 _public function_ `UUInt16Property(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()) : Super(ObjectInitializer)`
- L336 _public function_ `UUInt16Property(ECppProperty, int32 InOffset, EPropertyFlags InFlags) : UNumericProperty(FObjectInitializer::Get(), EC_CppProperty, InOffset, InFlags)`
- L341 _public function_ `UUInt16Property( const FObjectInitializer& ObjectInitializer, ECppProperty, int32 InOffset, EPropertyFlags InFlags ) : UNumericProperty( ObjectInitializer, EC_CppProperty, InOffset, InFlags )`

#### class `UUInt32Property`  
`class UUInt32Property : public UNumericProperty`  
_L348-362_
- reflection: `UCLASS(Config = Engine)`
- inherits: `UNumericProperty`
- L353 _public function_ `UUInt32Property(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()) : Super(ObjectInitializer)`
- L358 _public function_ `UUInt32Property( const FObjectInitializer& ObjectInitializer, ECppProperty, int32 InOffset, EPropertyFlags InFlags ) : UNumericProperty( ObjectInitializer, EC_CppProperty, InOffset, InFlags )`

#### class `UUInt64Property`  
`class UUInt64Property : public UNumericProperty`  
_L365-384_
- reflection: `UCLASS(Config = Engine)`
- inherits: `UNumericProperty`
- L370 _public function_ `UUInt64Property(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()) : Super(ObjectInitializer)`
- L375 _public function_ `UUInt64Property(ECppProperty, int32 InOffset, EPropertyFlags InFlags) : UNumericProperty(FObjectInitializer::Get(), EC_CppProperty, InOffset, InFlags)`
- L380 _public function_ `UUInt64Property( const FObjectInitializer& ObjectInitializer, ECppProperty, int32 InOffset, EPropertyFlags InFlags ) : UNumericProperty( ObjectInitializer, EC_CppProperty, InOffset, InFlags )`

#### class `UFloatProperty`  
`class UFloatProperty : public UNumericProperty`  
_L387-406_
- reflection: `UCLASS(Config = Engine)`
- inherits: `UNumericProperty`
- L392 _public function_ `UFloatProperty(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()) : Super(ObjectInitializer)`
- L397 _public function_ `UFloatProperty(ECppProperty, int32 InOffset, EPropertyFlags InFlags) : UNumericProperty(FObjectInitializer::Get(), EC_CppProperty, InOffset, InFlags)`
- L402 _public function_ `UFloatProperty( const FObjectInitializer& ObjectInitializer, ECppProperty, int32 InOffset, EPropertyFlags InFlags ) : UNumericProperty( ObjectInitializer, EC_CppProperty, InOffset, InFlags )`

#### class `UDoubleProperty`  
`class UDoubleProperty : public UNumericProperty`  
_L409-428_
- reflection: `UCLASS(Config=Engine)`
- inherits: `UNumericProperty`
- L414 _public function_ `UDoubleProperty(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()) : Super(ObjectInitializer)`
- L419 _public function_ `UDoubleProperty(ECppProperty, int32 InOffset, EPropertyFlags InFlags) : UNumericProperty(FObjectInitializer::Get(), EC_CppProperty, InOffset, InFlags)`
- L424 _public function_ `UDoubleProperty(const FObjectInitializer& ObjectInitializer, ECppProperty, int32 InOffset, EPropertyFlags InFlags) : UNumericProperty(ObjectInitializer, EC_CppProperty, InOffset, InFlags)`

#### class `UBoolProperty`  
`class UBoolProperty : public UProperty`  
_L431-496_
- reflection: `UCLASS(Config = Engine)`
- inherits: `UProperty`
- L439 _public member_ `uint8 FieldSize;` — Size of the bitfield/bool property. Equal to ElementSize but used to check if the property has been properly initialized (0-8, where 0 means uninitialized).
- L441 _public member_ `uint8 ByteOffset;` — Offset from the memeber variable to the byte of the property (0-7).
- L443 _public member_ `uint8 ByteMask;` — Mask of the byte with the property value.
- L445 _public member_ `uint8 FieldMask;` — Mask of the field with the property value. Either equal to ByteMask or 255 in case of 'bool' type.
- L447 _public prototype_ `UBoolProperty(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());`
- L460 _public prototype_ `UBoolProperty(ECppProperty, int32 InOffset, EPropertyFlags InFlags, uint32 InBitMask, uint32 InElementSize, bool bIsNativeBool);` — Constructor. @param ECppProperty Unused. @param InOffset Offset of the property. @param InCategory Category of the property. @param InFlags Property flags. @param InBitMask Bitmask of the bitfield this property represents. @param InElementSize Sizeof of the boolean type this property represents. @param bIsNativeBool true if this property represents C++ bool type.
- L474 _public prototype_ `UBoolProperty( const FObjectInitializer& ObjectInitializer, ECppProperty, int32 InOffset, EPropertyFlags InFlags, uint32 InBitMask, uint32 InElementSize, bool bIsNativeBool );` — Constructor. @param ObjectInitializer Properties. @param ECppProperty Unused. @param InOffset Offset of the property. @param InCategory Category of the property. @param InFlags Property flags. @param InBitMask Bitmask of the bitfield this property represents. @param InElementSize Sizeof of the boolean type this property represents. @param bIsNativeBool true if this property represents C++ bool type.
- L477 _public prototype_ `virtual void Serialize( FArchive& Ar ) override;` — UObject interface.
- L487 _public prototype_ `void SetBoolSize( const uint32 InSize, const bool bIsNativeBool = false, const uint32 InBitMask = 0 );` — Sets the bitfield/bool type and size. This function must be called before UBoolProperty can be used. @param InSize size of the bitfield/bool type. @param bIsNativeBool true if this property represents C++ bool type.
- L492 _public function_ `UE_FORCEINLINE_HINT bool IsNativeBool() const` — If the return value is true this UBoolProperty represents C++ bool type.

#### class `UObjectPropertyBase`  
`class UObjectPropertyBase : public UProperty`  
_L499-534_
- reflection: `UCLASS(Abstract, Config = Engine)`
- inherits: `UProperty`
- L507 _public member_ `TObjectPtr<class UClass> PropertyClass;` — `UPROPERTY(SkipSerialization)` — Variables.
- L509 _public function_ `UObjectPropertyBase(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()) : Super(ObjectInitializer)`
- L514 _public function_ `UObjectPropertyBase(ECppProperty, int32 InOffset, EPropertyFlags InFlags, UClass* InClass = NULL) : UProperty(FObjectInitializer::Get(), EC_CppProperty, InOffset, InFlags) , PropertyClass(InClass)`
- L519 _public function_ `UObjectPropertyBase( const FObjectInitializer& ObjectInitializer, ECppProperty, int32 InOffset, EPropertyFlags InFlags, UClass* InClass=NULL ) : UProperty( ObjectInitializer, EC_CppProperty, InOffset, InFlags ) , PropertyClass( InClass )`
- L525 _public prototype_ `virtual void Serialize( FArchive& Ar ) override;` — UObject interface
- L526 _public prototype_ `virtual void BeginDestroy() override;`
- L530 _public prototype_ `void SetPropertyClass(UClass* NewPropertyClass);`
- L532 _public function_ `UE_FORCEINLINE_HINT void SetPropertyClass(UClass* NewPropertyClass)`

#### class `UObjectProperty`  
`class UObjectProperty : public UObjectPropertyBase`  
_L537-556_
- reflection: `UCLASS(Config = Engine)`
- inherits: `UObjectPropertyBase`
- L542 _public function_ `UObjectProperty(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()) : Super(ObjectInitializer)`
- L547 _public function_ `UObjectProperty(ECppProperty, int32 InOffset, EPropertyFlags InFlags, UClass* InClass) : UObjectPropertyBase(FObjectInitializer::Get(), EC_CppProperty, InOffset, InFlags, InClass)`
- L552 _public function_ `UObjectProperty( const FObjectInitializer& ObjectInitializer, ECppProperty, int32 InOffset, EPropertyFlags InFlags, UClass* InClass ) : UObjectPropertyBase(ObjectInitializer, EC_CppProperty, InOffset, InFlags, InClass)`

#### class `UWeakObjectProperty`  
`class UWeakObjectProperty : public UObjectPropertyBase`  
_L559-578_
- reflection: `UCLASS(Config = Engine)`
- inherits: `UObjectPropertyBase`
- L564 _public function_ `UWeakObjectProperty(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()) : Super(ObjectInitializer)`
- L569 _public function_ `UWeakObjectProperty(ECppProperty, int32 InOffset, EPropertyFlags InFlags, UClass* InClass) : UObjectPropertyBase(FObjectInitializer::Get(), EC_CppProperty, InOffset, InFlags, InClass)`
- L574 _public function_ `UWeakObjectProperty( const FObjectInitializer& ObjectInitializer, ECppProperty, int32 InOffset, EPropertyFlags InFlags, UClass* InClass ) : UObjectPropertyBase( ObjectInitializer, EC_CppProperty, InOffset, InFlags, InClass )`

#### class `ULazyObjectProperty`  
`class ULazyObjectProperty : public UObjectPropertyBase`  
_L581-600_
- reflection: `UCLASS(Config = Engine)`
- inherits: `UObjectPropertyBase`
- L586 _public function_ `ULazyObjectProperty(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()) : Super(ObjectInitializer)`
- L591 _public function_ `ULazyObjectProperty(ECppProperty, int32 InOffset, EPropertyFlags InFlags, UClass* InClass) : UObjectPropertyBase(FObjectInitializer::Get(), EC_CppProperty, InOffset, InFlags, InClass)`
- L596 _public function_ `ULazyObjectProperty( const FObjectInitializer& ObjectInitializer, ECppProperty, int32 InOffset, EPropertyFlags InFlags, UClass* InClass ) : UObjectPropertyBase(ObjectInitializer, EC_CppProperty, InOffset, InFlags, InClass)`

#### class `USoftObjectProperty`  
`class USoftObjectProperty : public UObjectPropertyBase`  
_L603-620_
- reflection: `UCLASS(Config = Engine)`
- inherits: `UObjectPropertyBase`
- L608 _public function_ `USoftObjectProperty(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()) : Super(ObjectInitializer)`
- L613 _public function_ `USoftObjectProperty(ECppProperty, int32 InOffset, EPropertyFlags InFlags, UClass* InClass) : UObjectPropertyBase(FObjectInitializer::Get(), EC_CppProperty, InOffset, InFlags, InClass)`
- L617 _public function_ `USoftObjectProperty( const FObjectInitializer& ObjectInitializer, ECppProperty, int32 InOffset, EPropertyFlags InFlags, UClass* InClass ) : UObjectPropertyBase(ObjectInitializer, EC_CppProperty, InOffset, InFlags, InClass)`

#### class `UClassProperty`  
`class UClassProperty : public UObjectProperty`  
_L623-669_
- reflection: `UCLASS(Config = Engine)`
- inherits: `UObjectProperty`
- L631 _public member_ `TObjectPtr<class UClass> MetaClass;` — `UPROPERTY(SkipSerialization)` — Variables.
- L633 _public function_ `UClassProperty(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()) : Super(ObjectInitializer)`
- L638 _public function_ `UClassProperty(ECppProperty, int32 InOffset, EPropertyFlags InFlags, UClass* InMetaClass, UClass* InClassType) : UObjectProperty(FObjectInitializer::Get(), EC_CppProperty, InOffset, InFlags, InClassType ? InClassType : UClass::StaticClass()) , MetaClass(InMetaClass)`
- L644 _public function_ `UClassProperty(const FObjectInitializer& ObjectInitializer, ECppProperty, int32 InOffset, EPropertyFlags InFlags, UClass* InMetaClass, UClass* InClassType) : UObjectProperty(ObjectInitializer, EC_CppProperty, InOffset, InFlags, InClassType ? InClassType : UClass::StaticClass()) , MetaClass( InMetaClass )`
- L651 _public prototype_ `virtual void Serialize( FArchive& Ar ) override;` — UObject interface
- L652 _public prototype_ `virtual void BeginDestroy() override;`
- L665 _public prototype_ `void SetMetaClass(UClass* NewMetaClass);`
- L667 _public function_ `UE_FORCEINLINE_HINT void SetMetaClass(UClass* NewMetaClass)`

#### class `USoftClassProperty`  
`class USoftClassProperty : public USoftObjectProperty`  
_L672-716_
- reflection: `UCLASS(Config = Engine)`
- inherits: `USoftObjectProperty`
- L680 _public member_ `TObjectPtr<class UClass> MetaClass;` — `UPROPERTY(SkipSerialization)` — Variables.
- L682 _public function_ `USoftClassProperty(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()) : Super(ObjectInitializer)`
- L687 _public function_ `USoftClassProperty(ECppProperty, int32 InOffset, EPropertyFlags InFlags, UClass* InMetaClass) : Super(FObjectInitializer::Get(), EC_CppProperty, InOffset, InFlags, UClass::StaticClass()) , MetaClass(InMetaClass)`
- L692 _public function_ `USoftClassProperty( const FObjectInitializer& ObjectInitializer, ECppProperty, int32 InOffset, EPropertyFlags InFlags, UClass* InMetaClass ) : Super(ObjectInitializer, EC_CppProperty, InOffset, InFlags, UClass::StaticClass() ) , MetaClass( InMetaClass )`
- L698 _public prototype_ `virtual void Serialize( FArchive& Ar ) override;` — UObject interface
- L699 _public prototype_ `virtual void BeginDestroy() override;`
- L712 _public prototype_ `void SetMetaClass(UClass* NewMetaClass);`
- L714 _public function_ `UE_FORCEINLINE_HINT void SetMetaClass(UClass* NewMetaClass)`

#### class `UInterfaceProperty`  
`class UInterfaceProperty : public UProperty`  
_L719-765_
- reflection: `UCLASS(Config = Engine)`
- inherits: `UProperty`
- L727 _public member_ `TObjectPtr<class UClass> InterfaceClass;` — `UPROPERTY(SkipSerialization)` — The native interface class that this interface property refers to
- L729 _public function_ `UInterfaceProperty(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()) : Super(ObjectInitializer)`
- L734 _public function_ `UInterfaceProperty(ECppProperty, int32 InOffset, EPropertyFlags InFlags, UClass* InInterfaceClass) : UProperty(FObjectInitializer::Get(), EC_CppProperty, InOffset, (InFlags & ~CPF_InterfaceClearMask)) , InterfaceClass(InInterfaceClass)`
- L740 _public function_ `UInterfaceProperty( const FObjectInitializer& ObjectInitializer, ECppProperty, int32 InOffset, EPropertyFlags InFlags, UClass* InInterfaceClass ) : UProperty( ObjectInitializer, EC_CppProperty, InOffset, (InFlags & ~CPF_InterfaceClearMask) ) , InterfaceClass( InInterfaceClass )`
- L747 _public prototype_ `virtual void Serialize( FArchive& Ar ) override;` — UObject interface
- L748 _public prototype_ `virtual void BeginDestroy() override;`
- L761 _public prototype_ `void SetInterfaceClass(UClass* NewInterfaceClass);`
- L763 _public function_ `UE_FORCEINLINE_HINT void SetInterfaceClass(UClass* NewInterfaceClass)`

#### class `UNameProperty`  
`class UNameProperty : public UProperty`  
_L768-787_
- reflection: `UCLASS(Config = Engine)`
- inherits: `UProperty`
- L773 _public function_ `UNameProperty(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()) : Super(ObjectInitializer)`
- L778 _public function_ `UNameProperty(ECppProperty, int32 InOffset, EPropertyFlags InFlags) : UProperty(FObjectInitializer::Get(), EC_CppProperty, InOffset, InFlags)`
- L783 _public function_ `UNameProperty( const FObjectInitializer& ObjectInitializer, ECppProperty, int32 InOffset, EPropertyFlags InFlags ) : UProperty( ObjectInitializer, EC_CppProperty, InOffset, InFlags )`

#### class `UStrProperty`  
`class UStrProperty : public UProperty`  
_L790-809_
- reflection: `UCLASS(Config = Engine)`
- inherits: `UProperty`
- L795 _public function_ `UStrProperty(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()) : Super(ObjectInitializer)`
- L800 _public function_ `UStrProperty(ECppProperty, int32 InOffset, EPropertyFlags InFlags) : UProperty(FObjectInitializer::Get(), EC_CppProperty, InOffset, InFlags)`
- L805 _public function_ `UStrProperty( const FObjectInitializer& ObjectInitializer, ECppProperty, int32 InOffset, EPropertyFlags InFlags ) : UProperty( ObjectInitializer, EC_CppProperty, InOffset, InFlags)`

#### class `UArrayProperty`  
`class UArrayProperty : public UProperty`  
_L812-840_
- reflection: `UCLASS(Config = Engine)`
- inherits: `UProperty`
- L820 _public member_ `TObjectPtr<UProperty> Inner;` — `UPROPERTY(SkipSerialization)` — Variables.
- L822 _public function_ `UArrayProperty(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()) : Super(ObjectInitializer)`
- L827 _public function_ `UArrayProperty(ECppProperty, int32 InOffset, EPropertyFlags InFlags) : UProperty(FObjectInitializer::Get(), EC_CppProperty, InOffset, InFlags)`
- L832 _public function_ `UArrayProperty( const FObjectInitializer& ObjectInitializer, ECppProperty, int32 InOffset, EPropertyFlags InFlags ) : UProperty( ObjectInitializer, EC_CppProperty, InOffset, InFlags)`
- L838 _public prototype_ `virtual void Serialize( FArchive& Ar ) override;` — UObject interface

#### class `UMapProperty`  
`class UMapProperty : public UProperty`  
_L843-865_
- reflection: `UCLASS(Config = Engine)`
- inherits: `UProperty`
- L851 _public member_ `TObjectPtr<UProperty> KeyProp;` — `UPROPERTY(SkipSerialization)` — Properties representing the key type and value type of the contained pairs
- L853 _public member_ `TObjectPtr<UProperty> ValueProp;` — `UPROPERTY(SkipSerialization)`
- L854 _public member_ `FScriptMapLayout MapLayout;`
- L856 _public function_ `UMapProperty(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()) : Super(ObjectInitializer)`
- L860 _public prototype_ `UMapProperty(const FObjectInitializer& ObjectInitializer, ECppProperty, int32 InOffset, EPropertyFlags InFlags);`
- L863 _public prototype_ `virtual void Serialize(FArchive& Ar) override;` — UObject interface

#### class `USetProperty`  
`class USetProperty : public UProperty`  
_L868-888_
- reflection: `UCLASS(Config = Engine)`
- inherits: `UProperty`
- L876 _public member_ `TObjectPtr<UProperty> ElementProp;` — `UPROPERTY(SkipSerialization)` — Properties representing the key type and value type of the contained pairs
- L877 _public member_ `FScriptSetLayout SetLayout;`
- L879 _public function_ `USetProperty(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()) : Super(ObjectInitializer)`
- L883 _public prototype_ `USetProperty(const FObjectInitializer& ObjectInitializer, ECppProperty, int32 InOffset, EPropertyFlags InFlags);`
- L886 _public prototype_ `virtual void Serialize(FArchive& Ar) override;` — UObject interface

#### class `UStructProperty`  
`class UStructProperty : public UProperty`  
_L891-911_
- reflection: `UCLASS(Config = Engine)`
- inherits: `UProperty`
- L899 _public member_ `TObjectPtr<class UScriptStruct> Struct;` — `UPROPERTY(SkipSerialization)` — Variables.
- L901 _public function_ `UStructProperty(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()) : Super(ObjectInitializer)`
- L905 _public prototype_ `UStructProperty(ECppProperty, int32 InOffset, EPropertyFlags InFlags, UScriptStruct* InStruct);`
- L906 _public prototype_ `UStructProperty( const FObjectInitializer& ObjectInitializer, ECppProperty, int32 InOffset, EPropertyFlags InFlags, UScriptStruct* InStruct );`
- L909 _public prototype_ `virtual void Serialize( FArchive& Ar ) override;` — UObject interface

#### class `UDelegateProperty`  
`class UDelegateProperty : public UProperty`  
_L914-945_
- reflection: `UCLASS(Config = Engine)`
- inherits: `UProperty`
- L922 _public member_ `TObjectPtr<UFunction> SignatureFunction;` — `UPROPERTY(SkipSerialization)` — Points to the source delegate function (the function declared with the delegate keyword) used in the declaration of this delegate property.
- L924 _public function_ `UDelegateProperty(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()) : Super(ObjectInitializer)`
- L929 _public function_ `UDelegateProperty(ECppProperty, int32 InOffset, EPropertyFlags InFlags, UFunction* InSignatureFunction = NULL) : UProperty(FObjectInitializer::Get(), EC_CppProperty, InOffset, InFlags) , SignatureFunction(InSignatureFunction)`
- L935 _public function_ `UDelegateProperty( const FObjectInitializer& ObjectInitializer, ECppProperty, int32 InOffset, EPropertyFlags InFlags, UFunction* InSignatureFunction = NULL ) : UProperty( ObjectInitializer, EC_CppProperty, InOffset, InFlags) , SignatureFunction(InSignatureFunction)`
- L942 _public prototype_ `virtual void Serialize( FArchive& Ar ) override;` — UObject interface
- L943 _public prototype_ `virtual void BeginDestroy() override;`

#### class `UMulticastDelegateProperty`  
`class UMulticastDelegateProperty : public UProperty`  
_L948-973_
- reflection: `UCLASS(Abstract, Config = Engine)`
- inherits: `UProperty`
- L956 _public member_ `TObjectPtr<UFunction> SignatureFunction;` — `UPROPERTY(SkipSerialization)` — Points to the source delegate function (the function declared with the delegate keyword) used in the declaration of this delegate property.
- L958 _public function_ `UMulticastDelegateProperty(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()) : Super(ObjectInitializer)`
- L963 _public function_ `UMulticastDelegateProperty(const FObjectInitializer& ObjectInitializer, ECppProperty, int32 InOffset, EPropertyFlags InFlags, UFunction* InSignatureFunction = nullptr) : UProperty(ObjectInitializer, EC_CppProperty, InOffset, InFlags) , SignatureFunction(InSignatureFunction)`
- L970 _public prototype_ `virtual void Serialize( FArchive& Ar ) override;` — UObject interface
- L971 _public prototype_ `virtual void BeginDestroy() override;`

#### class `UMulticastInlineDelegateProperty`  
`class UMulticastInlineDelegateProperty : public UMulticastDelegateProperty`  
_L976-995_
- reflection: `UCLASS(Config = Engine)`
- inherits: `UMulticastDelegateProperty`
- L981 _public function_ `UMulticastInlineDelegateProperty(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()) : Super(ObjectInitializer)`
- L986 _public function_ `UMulticastInlineDelegateProperty(ECppProperty, int32 InOffset, EPropertyFlags InFlags, UFunction* InSignatureFunction = nullptr) : UMulticastDelegateProperty(FObjectInitializer::Get(), EC_CppProperty, InOffset, InFlags, InSignatureFunction)`
- L991 _public function_ `UMulticastInlineDelegateProperty(const FObjectInitializer& ObjectInitializer, ECppProperty, int32 InOffset, EPropertyFlags InFlags, UFunction* InSignatureFunction = nullptr) : UMulticastDelegateProperty(ObjectInitializer, EC_CppProperty, InOffset, InFlags, InSignatureFunction)`

#### class `UMulticastSparseDelegateProperty`  
`class UMulticastSparseDelegateProperty : public UMulticastDelegateProperty`  
_L998-1018_
- reflection: `UCLASS(Config = Engine)`
- inherits: `UMulticastDelegateProperty`
- L1004 _public function_ `UMulticastSparseDelegateProperty(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()) : Super(ObjectInitializer)`
- L1009 _public function_ `UMulticastSparseDelegateProperty(ECppProperty, int32 InOffset, EPropertyFlags InFlags, UFunction* InSignatureFunction = nullptr) : UMulticastDelegateProperty(FObjectInitializer::Get(), EC_CppProperty, InOffset, InFlags, InSignatureFunction)`
- L1014 _public function_ `UMulticastSparseDelegateProperty(const FObjectInitializer& ObjectInitializer, ECppProperty, int32 InOffset, EPropertyFlags InFlags, UFunction* InSignatureFunction = nullptr) : UMulticastDelegateProperty(ObjectInitializer, EC_CppProperty, InOffset, InFlags, InSignatureFunction)`

#### class `UEnumProperty`  
`class UEnumProperty : public UProperty`  
_L1022-1042_
- reflection: `UCLASS(Config = Engine)`
- inherits: `UProperty`
- L1027 _public function_ `UEnumProperty(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()) : Super(ObjectInitializer)`
- L1031 _public prototype_ `UEnumProperty(const FObjectInitializer& ObjectInitializer, UEnum* InEnum);`
- L1032 _public prototype_ `UEnumProperty(const FObjectInitializer& ObjectInitializer, ECppProperty, int32 InOffset, EPropertyFlags InFlags, UEnum* InEnum);`
- L1035 _public prototype_ `virtual void Serialize(FArchive& Ar) override;` — UObject interface
- L1039 _public member_ `TObjectPtr<UNumericProperty> UnderlyingProp;` — `UPROPERTY(SkipSerialization)` — The property which represents the underlying type of the enum
- L1041 _public member_ `TObjectPtr<UEnum> Enum;` — `UPROPERTY(SkipSerialization)` — The enum represented by this property

#### class `UTextProperty`  
`class UTextProperty : public UProperty`  
_L1045-1065_
- reflection: `UCLASS(Config = Engine)`
- inherits: `UProperty`
- L1051 _public function_ `UTextProperty(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()) : UProperty(ObjectInitializer)`
- L1056 _public function_ `UTextProperty(ECppProperty, int32 InOffset, EPropertyFlags InFlags) : UProperty(FObjectInitializer::Get(), EC_CppProperty, InOffset, InFlags)`
- L1061 _public function_ `UTextProperty(const FObjectInitializer& ObjectInitializer, ECppProperty, int32 InOffset, EPropertyFlags InFlags) : UProperty(ObjectInitializer, EC_CppProperty, InOffset, InFlags)`

#### Free symbols / members of external scopes

- L14 _macro_ `#define USE_UPROPERTY_LOAD_DEFERRING (USE_CIRCULAR_DEPENDENCY_LOAD_DEFERRING && WITH_EDITORONLY_DATA)`

### `Source/Runtime/CoreUObject/Public/UObject/Utf8StrProperty.h` (Public)


#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_STRPROPERTY_CLASS FUtf8StrProperty`
- L11 _macro_ `#define UE_STRPROPERTY_STRINGTYPE FUtf8String`
- L12 _macro_ `#define UE_STRPROPERTY_CASTCLASSFLAG CASTCLASS_FUtf8StrProperty`
- L13 _macro_ `#define UE_STRPROPERTY_PROPERTYPARAMSSTRUCT FUtf8StrPropertyParams`

### `Source/Runtime/CoreUObject/Public/UObject/VerseClassProperty.h` (Public)


#### class `FVerseClassProperty`  
`class FVerseClassProperty : public FClassProperty`  
_L10-69_
- inherits: `FClassProperty`
- desc: FVerseClassProperty
- L15 _private member_ `bool bRequiresCastable = false;`
- L18 _public typedef_ `typedef FVerseClassProperty::TTypeFundamentals TTypeFundamentals;`
- L19 _public typedef_ `typedef TTypeFundamentals::TCppType TCppType;`
- L22 _public prototype_ `FVerseClassProperty(FFieldVariant InOwner, const FName& InName);`
- L29 _public prototype_ `FVerseClassProperty(FFieldVariant InOwner, const UECodeGen_Private::FVerseClassPropertyParams& Prop);` — Constructor used for constructing compiled in properties @param InOwner Owner of the property @param PropBase Pointer to the compiled in structure describing the property
- L32 _public function_ `explicit consteval FVerseClassProperty( UE::CodeGen::ConstInit::FPropertyParams InBaseParams, UE::CodeGen::ConstInit::TObjectRefParam<UClass> InPropertyClass, UE::CodeGen::ConstInit::TObjectRefParam<UClass> InMetaClass, bool bInRequiresConcrete, bool bInRequiresCastable ) : Super(InBaseParams, InPropertyClass, InMetaClass) , bRequiresConcrete(bInRequiresConcrete) , bRequiresCastable(bInRequiresCastable)`
- L47 _public prototype_ `virtual void Serialize(FArchive& Ar) override;` — UObject interface
- L51 _public prototype_ `virtual FString GetCPPMacroType(FString& ExtendedTypeText) const override;` — UHT interface
- L55 _public prototype_ `virtual const TCHAR* ImportText_Internal(const TCHAR* Buffer, TNotNull<void*> ContainerOrPropertyPtr, EPropertyPointerType PropertyPointerType, UObject* OwnerObject, int32 PortFlags, FOutputDevice* ErrorText) const override;` — FProperty interface
- L56 _public prototype_ `virtual void PostDuplicate(const FField& InField) override;`
- L57 _public prototype_ `virtual bool SameType(const FProperty* Other) const override;`
- L59 _public prototype_ `virtual void AppendSchemaHash(FBlake3& Builder, bool bSkipEditorOnly) const override;`
- L63 _public prototype_ `static bool StaticIsClassConcrete(const UClass* Class);`
- L64 _public prototype_ `static bool StaticIsClassCastable(const UClass* Class);`
- L68 _private prototype_ `static const UVerseClass* GetVerseClass(const UClass* Class);` — Searches the class hierarchy for a valid Verse class; covers BP generated classes also.

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API COREUOBJECT_API`

### `Source/Runtime/CoreUObject/Public/UObject/VerseStringProperty.h` (Public)


#### class `FVerseStringProperty`  
`class FVerseStringProperty : public FVerseStringProperty_Super`  
_L15-61_
- inherits: `FVerseStringProperty_Super`
- desc: FVerseStringProperty ?
- L19 _public typedef_ `typedef FVerseStringProperty_Super::TTypeFundamentals TTypeFundamentals;`
- L20 _public typedef_ `typedef TTypeFundamentals::TCppType TCppType;`
- L22 _public member_ `FProperty* Inner = nullptr;`
- L24 _public function_ `FVerseStringProperty(FFieldVariant InOwner, const FName& InName) : Super(InOwner, InName)`
- L29 _public function_ `FVerseStringProperty(FFieldVariant InOwner, const UECodeGen_Private::FVerseStringPropertyParams& Prop) : Super(InOwner, (const UECodeGen_Private::FPropertyParamsBaseWithOffset&)Prop)`
- L35 _public function_ `explicit consteval FVerseStringProperty(UE::CodeGen::ConstInit::FPropertyParams InBaseParams, FProperty* InInner) : Super(InBaseParams) , Inner(InInner)`
- L42 _public prototype_ `virtual ~FVerseStringProperty();`
- L45 _public prototype_ `virtual void Serialize(FArchive& Ar) override;` — FField interface
- L46 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;`
- L47 _public prototype_ `virtual void PostDuplicate(const FField& InField) override;`
- L48 _public prototype_ `virtual void AddCppProperty(FProperty* Property) override;`
- L49 _public prototype_ `virtual FField* GetInnerFieldByName(const FName& InName) override;`
- L50 _public prototype_ `virtual void GetInnerFields(TArray<FField*>& OutFields) override;`
- L55 _protected prototype_ `virtual void ExportText_Internal(FString& ValueStr, TNotNull<const void*> PropertyValueOrContainer, EPropertyPointerType PropertyPointerType, const void* DefaultValue, UObject* Parent, int32 PortFlags, UObject* ExportRootScope) const override;`
- L56 _protected prototype_ `virtual const TCHAR* ImportText_Internal(const TCHAR* Buffer, TNotNull<void*> ContainerOrPropertyPtr, EPropertyPointerType PropertyPointerType, UObject* OwnerObject, int32 PortFlags, FOutputDevice* ErrorText) const override;`
- L57 _protected prototype_ `uint32 GetValueTypeHashInternal(const void* Src) const override;`
- L58 _protected prototype_ `virtual bool LoadTypeName(UE::FPropertyTypeName Type, const FPropertyTag* Tag = nullptr) override;`
- L59 _protected prototype_ `virtual void SaveTypeName(UE::FPropertyTypeNameBuilder& Type) const override;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API COREUOBJECT_API`
- L12 _typedef_ `typedef TProperty_WithEqualityAndSerializer<Verse::FNativeString, FProperty> FVerseStringProperty_Super;`

### `Source/Runtime/CoreUObject/Public/UObject/VerseTypesFwd.h` (Public)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace Verse`

### `Source/Runtime/CoreUObject/Public/UObject/VerseValueProperty.h` (Public)


#### class `TFVersePropertyBase`  
`template <typename InTCppType> class TFVersePropertyBase : public TProperty<InTCppType, FProperty>`  
_L64-116_
- inherits: `TProperty<InTCppType,FProperty>`
- desc: Template base class for the verse property types
- L67 _public typedef_ `using Super = TProperty<InTCppType, FProperty>;`
- L68 _public typedef_ `using TCppType = InTCppType;`
- L70 _public function_ `TFVersePropertyBase(EInternal InInternal, FFieldClass* InClass) : Super(EC_InternalUseOnlyConstructor, InClass)`
- L75 _public function_ `TFVersePropertyBase(FFieldVariant InOwner, const FName& InName) : Super(InOwner, InName)`
- L80 _public function_ `TFVersePropertyBase(FFieldVariant InOwner, const UECodeGen_Private::FPropertyParamsBaseWithOffset& Prop) : Super(InOwner, Prop)`
- L86 _public function_ `explicit consteval TFVersePropertyBase(UE::CodeGen::ConstInit::FPropertyParams InBaseParams) : Super(InBaseParams)`
- L93 _public function_ `explicit TFVersePropertyBase(UField* InField) : Super(InField)`
- L100 _public prototype_ `virtual FString GetCPPMacroType(FString& ExtendedTypeText) const override;` — UHT interface
- L104 _public prototype_ `virtual bool Identical(TNotNull<const void*> A, const void* B, uint32 PortFlags) const override;` — FProperty interface
- L105 _public prototype_ `virtual void SerializeItem(FStructuredArchive::FSlot Slot, TNotNull<void*> Value, void const* Defaults) const override;`
- L106 _public prototype_ `virtual void ExportText_Internal(FString& ValueStr, TNotNull<const void*> PropertyValueOrContainer, EPropertyPointerType PointerType, const void* DefaultValue, UObject* Parent, int32 PortFlags, UObject* ExportRootScope) const override;`
- L107 _public prototype_ `virtual const TCHAR* ImportText_Internal(const TCHAR* Buffer, TNotNull<void*> ContainerOrPropertyPtr, EPropertyPointerType PropertyPointerType, UObject* OwnerObject, int32 PortFlags, FOutputDevice* ErrorText) const override;`
- L108 _public prototype_ `virtual bool ContainsObjectReference(TArray<const FStructProperty*>& EncounteredStructProps, EPropertyObjectReferenceType InReferenceType = EPropertyObjectReferenceType::Strong) const override;`
- L109 _public prototype_ `virtual void EmitReferenceInfo(UE::GC::FSchemaBuilder& Schema, int32 BaseOffset, TArray<const FStructProperty*>& EncounteredStructProps, UE::GC::FPropertyStack& DebugPath) override;`
- L111 _public function_ `virtual bool HasIntrusiveUnsetOptionalState() const override`

#### class `FVCellProperty`  
`class FVCellProperty : public TFVersePropertyBase<Verse::TWriteBarrier<Verse::VCell>>`  
_L118-138_
- inherits: `TFVersePropertyBase<Verse::TWriteBarrier<Verse::VCell>>`
- L123 _public prototype_ `FVCellProperty(FFieldVariant InOwner, const FName& InName);`
- L130 _public prototype_ `FVCellProperty(FFieldVariant InOwner, const UECodeGen_Private::FVerseCellValuePropertyParams& Prop);` — Constructor used for constructing compiled in properties @param InOwner Owner of the property @param Prop Pointer to the compiled in structure describing the property
- L133 _public function_ `explicit consteval FVCellProperty(UE::CodeGen::ConstInit::FPropertyParams InBaseParams) : Super(InBaseParams)`

#### class `FVValueProperty`  
`class FVValueProperty : public TFVersePropertyBase<Verse::TWriteBarrier<Verse::VValue>>`  
_L143-163_
- inherits: `TFVersePropertyBase<Verse::TWriteBarrier<Verse::VValue>>`
- desc: Metadata for a property of FVValueProperty type.
- L148 _public prototype_ `FVValueProperty(FFieldVariant InOwner, const FName& InName);`
- L155 _public prototype_ `FVValueProperty(FFieldVariant InOwner, const UECodeGen_Private::FVerseValuePropertyParams& Prop);` — Constructor used for constructing compiled in properties @param InOwner Owner of the property @param Prop Pointer to the compiled in structure describing the property
- L158 _public function_ `explicit consteval FVValueProperty(UE::CodeGen::ConstInit::FPropertyParams InBaseParams) : Super(InBaseParams)`

#### class `FVRestValueProperty`  
`class FVRestValueProperty : public TFVersePropertyBase<Verse::VRestValue>`  
_L168-234_
- inherits: `TFVersePropertyBase<Verse::VRestValue>`
- desc: Metadata for a property of FVRestValueProperty type.
- L174 _public member_ `Verse::TWriteBarrier<Verse::VValue> Type;`
- L175 _public member_ `FProperty* LegacyProperty = nullptr;`
- L178 _public member_ `bool bNativeRepresentation = true;` — See CDataDefinition::IsNativeRepresentation for the meaning of this flag.
- L181 _public prototype_ `FVRestValueProperty(FFieldVariant InOwner, const FName& InName);`
- L188 _public prototype_ `FVRestValueProperty(FFieldVariant InOwner, const UECodeGen_Private::FVerseValuePropertyParams& Prop);` — Constructor used for constructing compiled in properties @param InOwner Owner of the property @param Prop Pointer to the compiled in structure describing the property
- L191 _public function_ `explicit consteval FVRestValueProperty(UE::CodeGen::ConstInit::FPropertyParams InBaseParams) : Super(InBaseParams)`
- L196 _public function_ `explicit consteval FVRestValueProperty(UE::CodeGen::ConstInit::FPropertyParams InBaseParams, FProperty* InLegacyProperty) : Super(InBaseParams) , LegacyProperty(InLegacyProperty) #if WITH_EDITORONLY_DATA , bNativeRepresentation(false) #endif`
- L206 _public prototype_ `virtual ~FVRestValueProperty();`
- L207 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;`
- L208 _public prototype_ `virtual void AddCppProperty(FProperty* Property) override;`
- L209 _public prototype_ `virtual FField* GetInnerFieldByName(const FName& InName) override;`
- L210 _public prototype_ `virtual void GetInnerFields(TArray<FField*>& OutFields) override;`
- L215 _public prototype_ `template <typename NativeType> NativeType GetVersePropertyValue_InContainer(const void* Container) const;` — Defined in VVMNativeConverter.h TODO(SOL-9134): Consider moving this to FVerseValue so consumers don't need to care about FVRestValueProperty.
- L217 _public prototype_ `FProperty* GetOrCreateLegacyProperty(Verse::FAllocationContext Context);`
- L218 _public prototype_ `AUTORTFM_DISABLE void* AllocateAndInitializeLegacyValue(Verse::FAllocationContext Context);`
- L221 _public prototype_ `void VisitProperties(const FPropertyVisitorContext& Context, const TFunctionRef<EPropertyVisitorControlFlow(const FPropertyVisitorContext&)> InFunc) const;` — Like FProperty::Visit, but not an override because this can easily cause stack overflows on cycles in unsuspecting callers.
- L223 _public prototype_ `virtual void PostDuplicate(const FField& InField) override;`
- L227 _public prototype_ `static Verse::VValue ConvertToVValueLegacy(Verse::FAllocationContext Context, const void* Container, FProperty* Property);` — For conversion from uncooked BPVM data during deserialization.
- L228 _public prototype_ `static bool ConvertFromVValueLegacy(Verse::FAllocationContext Context, void* Container, FProperty* Property, Verse::VValue Value);`
- L229 _public prototype_ `virtual EConvertFromTypeResult ConvertFromType(const FPropertyTag& Tag, FStructuredArchive::FSlot Slot, uint8* Data, const UStruct* DefaultsStruct, const uint8* Defaults) override;`
- L232 _public prototype_ `virtual void CopyValuesInternal(void* Dest, const void* Src, int32 Count) const override;`
- L233 _public prototype_ `virtual void InstanceSubobjects(void* Data, const void* DefaultData, TNotNull<UObject*> Owner, FObjectInstancingGraph* InstanceGraph) override;`

#### Free symbols / members of external scopes

- L14 _typedef_ `using FVerseValueProperty = FVerseDynamicProperty;`
- L19 _namespace_ `namespace Verse`
- L26 _typedef_ `using FVerseValueProperty = FVRestValueProperty;` — Note that the property type for FVerseValue is FVRestValueProperty and not FVValueProperty
- L29 _function_ `template <> inline const TCHAR* TPropertyTypeFundamentals<Verse::TWriteBarrier<Verse::VCell>>::GetTypeName()` (scope `TPropertyTypeFundamentals::TWriteBarrier::VCell`)
- L35 _function_ `template <> inline const TCHAR* TPropertyTypeFundamentals<Verse::TWriteBarrier<Verse::VValue>>::GetTypeName()` (scope `TPropertyTypeFundamentals::TWriteBarrier::VValue`)
- L41 _function_ `template <> inline const TCHAR* TPropertyTypeFundamentals<Verse::VRestValue>::GetTypeName()` (scope `TPropertyTypeFundamentals::VRestValue`)
- L47 _function_ `template <> inline Verse::VRestValue TPropertyTypeFundamentals<Verse::VRestValue>::GetDefaultPropertyValue()` (scope `TPropertyTypeFundamentals::VRestValue`)
- L55 _function_ `template <> inline Verse::VRestValue* TPropertyTypeFundamentals<Verse::VRestValue>::InitializePropertyValue(void* A)` (scope `TPropertyTypeFundamentals::VRestValue`)
- L236 _function_ `inline bool IsVerseProperty(const FProperty* Property)`
- L241 _prototype_ `AUTORTFM_DISABLE TSharedPtr<FJsonValue> VersePropertyToJSON(Verse::FRunningContext, const FProperty*, const void* Value, TMap<const void*, Verse::EVisitState>& VisitedObjects, Verse::FToJsonCallback, const uint32 RecursionDepth = 0);`

### `Source/Runtime/CoreUObject/Public/UObject/WeakFieldPtr.h` (Public)


#### struct `TWeakFieldPtr`  
`template<class T> struct TWeakFieldPtr`  
_L64-324_
- L118 _private member_ `TWeakObjectPtr<UObject> Owner;`
- L119 _private member_ `mutable TFieldPath<T> Field;`
- L122 _public typedef_ `using ElementType = T;`
- L124 _public prototype_ `TWeakFieldPtr() = default;`
- L125 _public prototype_ `TWeakFieldPtr(const TWeakFieldPtr&) = default;`
- L126 _public prototype_ `TWeakFieldPtr& operator=(const TWeakFieldPtr&) = default;`
- L127 _public prototype_ `~TWeakFieldPtr() = default;`
- L132 _public function_ `inline TWeakFieldPtr(TYPE_OF_NULLPTR) : Owner((UObject*)nullptr) , Field()` — Construct from a null pointer
- L146 _public function_ `inline TWeakFieldPtr(U* InField, EDummy1 = Dummy1) : Owner(InField ? InField->GetOwnerUObject() : (UObject*)nullptr) , Field(InField)`
- L163 _public function_ `inline TWeakFieldPtr(const TWeakFieldPtr<OtherT>& Other) : Owner(Other.Owner) , Field(Other.Field)`
- L175 _public function_ `inline void Reset()` — Reset the weak pointer back to the NULL state
- L189 _public function_ `inline void operator=(U* InField)`
- L203 _public function_ `inline void operator=(const TWeakFieldPtr<OtherT>& Other)`
- L214 _public function_ `inline T* Get(bool bEvenIfPendingKill) const` — Dereference the weak pointer @param bEvenIfPendingKill, if this is true, pendingkill objects are considered valid @return NULL if this object is gone or the weak pointer was NULL, otherwise a valid uobject pointer
- L231 _public function_ `inline T* Get( ) const` — Dereference the weak pointer. This is an optimized version implying bEvenIfPendingKill=false.
- L246 _public function_ `inline T* GetEvenIfUnreachable() const` — Deferences the weak pointer even if its marked RF_Unreachable. This is needed to resolve weak pointers during GC (such as ::AddReferenceObjects)
- L263 _public function_ `UE_FORCEINLINE_HINT T & operator*() const` — Dereference the weak pointer
- L271 _public function_ `UE_FORCEINLINE_HINT T * operator->() const` — Dereference the weak pointer
- L283 _public function_ `UE_FORCEINLINE_HINT bool IsValid(bool bEvenIfPendingKill, bool bThreadsafeTest = false) const` — Test if this points to a live FField @param bEvenIfPendingKill, if this is true, pendingkill objects are considered valid @param bThreadsafeTest, if true then function will just give you information whether referenced FField is gone forever (@return false) or if it is still there (@return true, no object flags checked). @return true if Get() would return a valid non-null pointer
- L292 _public function_ `UE_FORCEINLINE_HINT bool IsValid( ) const` — Test if this points to a live FField. This is an optimized version implying bEvenIfPendingKill=false, bThreadsafeTest=false. @return true if Get() would return a valid non-null pointer
- L303 _public function_ `UE_FORCEINLINE_HINT bool IsStale(bool bIncludingIfPendingKill = false, bool bThreadsafeTest = false) const` — Slightly different than !IsValid(), returns true if this used to point to a FField, but doesn't any more and has not been assigned or reset in the mean time. @param bIncludingIfPendingKill, if this is true, pendingkill objects are considered stale @param bThreadsafeTest, set it to true when testing outside of Game Thread. Results in false if WeakObjPtr point to an existing object (no flags checked) @return true if this used to point at a real object but no longer does.
- L308 _public function_ `UE_FORCEINLINE_HINT bool HasSameIndexAndSerialNumber(const TWeakFieldPtr& Other) const`
- L319 _public function_ `inline void Serialize(FArchive& Ar)`

#### enum `TWeakFieldPtr::EDummy1`  
`enum EDummy1`  
_L116-116_
- desc: These exists only to disambiguate the two constructors below
- L116 _public enumerator_ `enum EDummy1 { Dummy1 }; TWeakObjectPtr<UObject> Owner; mutable TFieldPath<T> Field; public: using ElementType = T;` — These exists only to disambiguate the two constructors below

#### enum `TIsPODType::(anonymous)`  
`template<class T> struct TIsPODType<TWeakFieldPtr<T> >`  
_L465-465_

#### struct `TIsPODType`  
`template<class T> struct TIsPODType<TWeakFieldPtr<T> >`  
_L465-465_

#### enum `TIsZeroConstructType::(anonymous)`  
`template<class T> struct TIsPODType<TWeakFieldPtr<T> >`  
_L466-466_

#### struct `TIsZeroConstructType`  
`template<class T> struct TIsPODType<TWeakFieldPtr<T> >`  
_L466-466_

#### enum `TIsWeakPointerType::(anonymous)`  
`template<class T> struct TIsPODType<TWeakFieldPtr<T> >`  
_L467-467_

#### struct `TIsWeakPointerType`  
`template<class T> struct TIsPODType<TWeakFieldPtr<T> >`  
_L467-467_

#### struct `TWeakFieldPtrMapKeyFuncs`  
`template <typename KeyType, typename ValueType, bool bInAllowDuplicateKeys = false> struct TWeakFieldPtrMapKeyFuncs : public TDefaultMapKeyFuncs<KeyType, ValueType, bInAllowDuplicateKeys>`  
_L474-487_
- inherits: `TDefaultMapKeyFuncs<KeyType,ValueType,bInAllowDuplicateKeys>`
- desc: MapKeyFuncs for TWeakFieldPtrs which allow the key to become stale without invalidating the map.
- L476 _public typedef_ `typedef typename TDefaultMapKeyFuncs<KeyType, ValueType, bInAllowDuplicateKeys>::KeyInitType KeyInitType;`
- L478 _public function_ `static UE_FORCEINLINE_HINT bool Matches(KeyInitType A, KeyInitType B)`
- L483 _public function_ `static UE_FORCEINLINE_HINT uint32 GetKeyHash(KeyInitType Key)`

#### Free symbols / members of external scopes

- L24 _prototype_ `bool operator==(const TWeakFieldPtr<LhsType>& Lhs, const TWeakFieldPtr<RhsType>& Rhs);`
- L31 _prototype_ `bool operator==(const TWeakFieldPtr<LhsType>& Lhs, const RhsType* Rhs);`
- L38 _prototype_ `bool operator==(const LhsType* Lhs, const TWeakFieldPtr<RhsType>& Rhs);`
- L46 _prototype_ `bool operator!=(const TWeakFieldPtr<LhsType>& Lhs, const TWeakFieldPtr<RhsType>& Rhs);`
- L53 _prototype_ `bool operator!=(const TWeakFieldPtr<LhsType>& Lhs, const RhsType* Rhs);`
- L60 _prototype_ `bool operator!=(const LhsType* Lhs, const TWeakFieldPtr<RhsType>& Rhs);`
- L314 _function_ `[[nodiscard]] UE_FORCEINLINE_HINT friend uint32 GetTypeHash(const TWeakFieldPtr& WeakObjectPtr)` — Hash function.
- L336 _function_ `UE_FORCEINLINE_HINT bool operator==(const TWeakFieldPtr<LhsType>& Lhs, const TWeakFieldPtr<RhsType>& Rhs)`
- L351 _function_ `UE_FORCEINLINE_HINT bool operator==(const TWeakFieldPtr<LhsType>& Lhs, const RhsType* Rhs)`
- L366 _function_ `UE_FORCEINLINE_HINT bool operator==(const LhsType* Lhs, const TWeakFieldPtr<RhsType>& Rhs)`
- L376 _function_ `template <typename LhsType> UE_FORCEINLINE_HINT bool operator==(const TWeakFieldPtr<LhsType>& Lhs, TYPE_OF_NULLPTR)` — Test weak pointer for null @param Lhs weak pointer to test
- L386 _function_ `template <typename RhsType> UE_FORCEINLINE_HINT bool operator==(TYPE_OF_NULLPTR, const TWeakFieldPtr<RhsType>& Rhs)` — Test weak pointer for null @param Rhs weak pointer to test
- L402 _function_ `UE_FORCEINLINE_HINT bool operator!=(const TWeakFieldPtr<LhsType>& Lhs, const TWeakFieldPtr<RhsType>& Rhs)`
- L417 _function_ `UE_FORCEINLINE_HINT bool operator!=(const TWeakFieldPtr<LhsType>& Lhs, const RhsType* Rhs)`
- L432 _function_ `UE_FORCEINLINE_HINT bool operator!=(const LhsType* Lhs, const TWeakFieldPtr<RhsType>& Rhs)`
- L442 _function_ `template <typename LhsType> UE_FORCEINLINE_HINT bool operator!=(const TWeakFieldPtr<LhsType>& Lhs, TYPE_OF_NULLPTR)` — Test weak pointer for non-null @param Lhs weak pointer to test
- L452 _function_ `template <typename RhsType> UE_FORCEINLINE_HINT bool operator!=(TYPE_OF_NULLPTR, const TWeakFieldPtr<RhsType>& Rhs)` — Test weak pointer for non-null @param Rhs weak pointer to test
- L460 _function_ `template <typename T> UE_FORCEINLINE_HINT TWeakFieldPtr<T> MakeWeakFieldPtr(T* Ptr)` — Helper function which deduces the type of the initializer
- L465 _enumerator_ `template<class T> struct TIsPODType<TWeakFieldPtr<T> > { enum { Value = true }; }; template<class T> struct TIsZeroConstructType<TWeakFieldPtr<T> > { enum { Value = true }; }; template<class T> struct TIsWeakPointerType<TWeakFieldPtr<T> > { enum { Value = true }; }; /** * MapKeyFuncs for TWeakFieldPtrs which allow the key to become stale without invalidating the map. */` (scope `TIsPODType::__anon15ba188e0103`)
- L466 _enumerator_ `template<class T> struct TIsZeroConstructType<TWeakFieldPtr<T> > { enum { Value = true }; }; template<class T> struct TIsWeakPointerType<TWeakFieldPtr<T> > { enum { Value = true }; }; /** * MapKeyFuncs for TWeakFieldPtrs which allow the key to become stale without invalidating the map. */ template <typename KeyType` (scope `TIsZeroConstructType::__anon15ba188e0203`)
- L467 _enumerator_ `template<class T> struct TIsWeakPointerType<TWeakFieldPtr<T> > { enum { Value = true }; }; /** * MapKeyFuncs for TWeakFieldPtrs which allow the key to become stale without invalidating the map. */ template <typename KeyType` (scope `TIsWeakPointerType::__anon15ba188e0303`)
- L490 _function_ `template<class T> FArchive& operator<<(FArchive& Ar, TWeakFieldPtr<T>& WeakFieldPtr)`

### `Source/Runtime/CoreUObject/Public/UObject/WeakInterfacePtr.h` (Public)


#### struct `TWeakInterfacePtr`  
`template<class T> struct TWeakInterfacePtr`  
_L17-203_
- desc: An alternative to TWeakObjectPtr that makes it easier to work through an interface.
- L19 _public typedef_ `using ElementType = T;`
- L20 _public typedef_ `using UObjectType = TCopyQualifiersFromTo_T<T, UObject>;`
- L22 _public prototype_ `[[nodiscard]] UE_FORCEINLINE_HINT TWeakInterfacePtr() = default;`
- L23 _public prototype_ `[[nodiscard]] UE_FORCEINLINE_HINT TWeakInterfacePtr(const TWeakInterfacePtr& Other) = default;`
- L24 _public prototype_ `[[nodiscard]] UE_FORCEINLINE_HINT TWeakInterfacePtr(TWeakInterfacePtr&& Other) = default;`
- L25 _public prototype_ `UE_FORCEINLINE_HINT ~TWeakInterfacePtr() = default;`
- L26 _public prototype_ `UE_FORCEINLINE_HINT TWeakInterfacePtr& operator=(const TWeakInterfacePtr& Other) = default;`
- L27 _public prototype_ `UE_FORCEINLINE_HINT TWeakInterfacePtr& operator=(TWeakInterfacePtr&& Other) = default;`
- L32 _public function_ `[[nodiscard]] UE_FORCEINLINE_HINT TWeakInterfacePtr(TYPE_OF_NULLPTR) : ObjectInstance(nullptr)` — Construct from a null pointer
- L45 _public function_ `[[nodiscard]] TWeakInterfacePtr(U&& Object)`
- L58 _public function_ `[[nodiscard]] TWeakInterfacePtr(T* Interface)` — Construct from an interface pointer @param Interface The interface pointer to create a weak pointer to. There must be a UObject behind the interface.
- L72 _public function_ `[[nodiscard]] TWeakInterfacePtr(const TScriptInterface<T>& ScriptInterface)` — Construct from a TScriptInterface of the same interface type @param ScriptInterface 	The TScriptInterface to copy from. No validation is done here; passing an invalid TScriptInterface in will result in an invalid TWeakInterfacePtr.
- L81 _public function_ `inline void Reset()` — Reset the weak pointer back to the null state.
- L90 _public function_ `[[nodiscard]] UE_FORCEINLINE_HINT bool IsValid(bool bEvenIfPendingKill, bool bThreadsafeTest = false) const` — Test if this points to a live object. Parameters are passed to the underlying TWeakObjectPtr.
- L98 _public function_ `[[nodiscard]] UE_FORCEINLINE_HINT bool IsValid() const` — Test if this points to a live object. Calls the underlying TWeakObjectPtr's parameterless IsValid method.
- L106 _public function_ `[[nodiscard]] UE_FORCEINLINE_HINT bool IsStale(bool bEvenIfPendingKill = false, bool bThreadsafeTest = false) const` — Test if this pointer is stale. Parameters are passed to the underlying TWeakObjectPtr.
- L114 _public function_ `[[nodiscard]] UE_FORCEINLINE_HINT T* Get() const` — Dereference the weak pointer into an interface pointer.
- L122 _public function_ `[[nodiscard]] UE_FORCEINLINE_HINT UObjectType* GetObject() const` — Dereference the weak pointer into a UObject pointer.
- L130 _public function_ `[[nodiscard]] inline T& operator*() const` — Dereference the weak pointer.
- L139 _public function_ `[[nodiscard]] inline T* operator->() const` — Dereference the weak pointer.
- L148 _public function_ `inline TWeakInterfacePtr<T>& operator=(T* Other)` — Assign from an interface pointer.
- L157 _public function_ `inline TWeakInterfacePtr<T>& operator=(const TScriptInterface<T>& Other)` — Assign from a script interface.
- L164 _public function_ `[[nodiscard]] UE_FORCEINLINE_HINT bool operator==(const TWeakInterfacePtr<T>& Other) const`
- L169 _public function_ `[[nodiscard]] UE_FORCEINLINE_HINT bool operator!=(const TWeakInterfacePtr<T>& Other) const`
- L174 _public function_ `[[nodiscard]] FORCENOINLINE bool operator==(TYPE_OF_NULLPTR) const`
- L179 _public function_ `[[nodiscard]] UE_FORCEINLINE_HINT bool operator!=(TYPE_OF_NULLPTR) const`
- L184 _public function_ `[[nodiscard]] inline TScriptInterface<T> ToScriptInterface() const`
- L195 _public function_ `[[nodiscard]] UE_FORCEINLINE_HINT TWeakObjectPtr<UObjectType> GetWeakObjectPtr() const`
- L201 _private member_ `TWeakObjectPtr<UObjectType> ObjectInstance;`
- L202 _private member_ `T* InterfaceInstance = nullptr;`

### `Source/Runtime/CoreUObject/Public/UObject/WeakObjectPtr.h` (Public)


#### struct `FWeakObjectPtr`  
`struct FWeakObjectPtr`  
_L48-580_
- desc: FWeakObjectPtr is a weak pointer to a UObject. It can return nullptr later if the object is garbage collected. It has no impact on if the object is garbage collected or not. It can't be directly used across a network. Most often it is used when you explicitly do NOT want to prevent something from being garbage collected.
- L56 _public prototype_ `FWeakObjectPtr() = default;`
- L58 _public function_ `UE_FORCEINLINE_HINT FWeakObjectPtr(TYPE_OF_NULLPTR) : FWeakObjectPtr()`
- L64 _public function_ `UE_FORCEINLINE_HINT FWeakObjectPtr()` — Null constructor
- L73 _public function_ `UE_FORCEINLINE_HINT FWeakObjectPtr(TYPE_OF_NULLPTR)` — Construct from nullptr or something that can be implicitly converted to nullptr (eg: NULL) @param Object object to create a weak pointer to
- L83 _public function_ `UE_FORCEINLINE_HINT FWeakObjectPtr(FObjectPtr Object)` — Construct from an object pointer or something that can be implicitly converted to an object pointer @param Object object to create a weak pointer to
- L87 _public function_ `UE_FORCEINLINE_HINT FWeakObjectPtr(const UObject* Object) : FWeakObjectPtr(FObjectPtr(const_cast<UObject*>(Object)))`
- L92 _public function_ `template <typename T> UE_FORCEINLINE_HINT FWeakObjectPtr(TObjectPtr<T> Object) : FWeakObjectPtr(FObjectPtr(const_cast<UObject*>(ImplicitConv<const UObject*>(Object.Get()))))`
- L106 _public prototype_ `FWeakObjectPtr(const FWeakObjectPtr& Other) = default;` — Construct from another weak pointer @param Other weak pointer to copy from
- L109 _public function_ `explicit FWeakObjectPtr(FRemoteObjectId RemoteId)`
- L123 _public function_ `inline void Reset()` — Reset the weak pointer back to the null state
- L138 _public prototype_ `void operator=(FObjectPtr Object);` — Copy from an object pointer @param Object object to create a weak pointer to
- L139 _public function_ `UE_FORCEINLINE_HINT void operator=(const UObject* Object)`
- L144 _public function_ `template <typename T> UE_FORCEINLINE_HINT void operator=(TObjectPtr<T> Object)`
- L159 _public prototype_ `FWeakObjectPtr& operator=(const FWeakObjectPtr& Other) = default;` — Construct from another weak pointer @param Other weak pointer to copy from
- L166 _public function_ `inline bool operator==(const FWeakObjectPtr& Other) const` — Compare weak pointers for equality. If both pointers would return nullptr from Get() they count as equal even if they were not initialized to the same object. @param Other weak pointer to compare to
- L182 _public function_ `inline bool operator!=(const FWeakObjectPtr& Other) const` — Compare weak pointers for inequality @param Other weak pointer to compare to
- L198 _public function_ `inline bool HasSameIndexAndSerialNumber(const FWeakObjectPtr& Other) const` — Returns true if two weak pointers were originally set to the same object, even if they are now stale @param Other weak pointer to compare to
- L212 _public prototype_ `class UObject* Get(bool bEvenIfGarbage) const;` — Dereference the weak pointer. @param bEvenIfGarbage if this is true, Garbage objects are considered valid @return nullptr if this object is gone or the weak pointer is explicitly null, otherwise a valid uobject pointer
- L218 _public prototype_ `class UObject* Get( ) const;` — Dereference the weak pointer. This is an optimized version implying bEvenIfGarbage=false. @return nullptr if this object is gone or the weak pointer is explicitly null, otherwise a valid uobject pointer
- L221 _public function_ `UE_REWRITE UObject& operator*() const` — Operators for direct access to Get()
- L225 _public function_ `UE_REWRITE UObject* operator->() const`
- L231 _public prototype_ `class UObject* GetEvenIfUnreachable() const;` — Dereference the weak pointer even if it is marked as Garbage or Unreachable
- L238 _public prototype_ `class TStrongObjectPtr<UObject> Pin(bool bEvenIfGarbage) const;` — Get a strong object ptr to the weak pointer. @param bEvenIfGarbage if this is true, Garbage objects are considered valid @return TStrongObjectPtr will be invalid if this object is gone or the weak pointer is explicitly null, otherwise a valid TStrongObjectPtr
- L244 _public prototype_ `class TStrongObjectPtr<UObject> Pin( ) const;` — Get a strong object ptr to the weak pointer. This is an optimized version implying bEvenIfGarbage=false. @return TStrongObjectPtr will be invalid if this object is gone or the weak pointer is explicitly null, otherwise a valid TStrongObjectPtr
- L250 _public prototype_ `class TStrongObjectPtr<UObject> PinEvenIfUnreachable() const;` — Get a strong object ptr even if it is marked as Garbage or Unreachable @return TStrongObjectPtr will be invalid if this object is gone or the weak pointer is explicitly null, otherwise a valid TStrongObjectPtr
- L259 _public prototype_ `class TStrongObjectPtr<UObject> TryPin(bool& bOutPinValid, bool bEvenIfGarbage) const;` — Attempt to get a strong object ptr to the weak pointer, but only if garbage collection is not in progress. @param bEvenIfGarbage if this is true, Garbage objects are considered valid @param bOutPinValid will be true if the pin attempt was successful, and false if it was blocked by garbage collection @return TStrongObjectPtr will be invalid if this object is gone or the weak pointer is explicitly null, otherwise a valid TStrongObjectPtr
- L266 _public prototype_ `class TStrongObjectPtr<UObject> TryPin(bool& bOutPinValid ) const;` — Attempt to get a strong object ptr to the weak pointer, but only if garbage collection is not in progress. This is an optimized version implying bEvenIfGarbage=false. @param bOutPinValid will be true if the pin attempt was successful, and false if it was blocked by garbage collection @return TStrongObjectPtr will be invalid if this object is gone or the weak pointer is explicitly null, otherwise a valid TStrongObjectPtr
- L273 _public prototype_ `bool TryPinEvenIfUnreachable(class TStrongObjectPtr<UObject>& OutResult) const;` — Attempt to get a strong object ptr even if it is marked as Garbage or Unreachable, but only if garbage collection is not in progress @param OutResult will be invalid if this object is gone, or the weak pointer is explicitly null, or garbage collection is in progress. Otherwise a valid TStrongObjectPtr @return  true if garbage collection was not in progress, and OutResult was successfully captured, false if garbage collection was in progress and OutResult was not captured
- L276 _public prototype_ `explicit operator bool() const = delete;` — This is explicitly not added to avoid resolving weak pointers too often - use Get() once in a function.
- L290 _public prototype_ `bool IsValid(bool bEvenIfGarbage, bool bThreadsafeTest = false) const;` — Test if this points to a live UObject This should be done only when needed as excess resolution of the underlying pointer can cause performance issues. @param bEvenIfGarbage if this is true, Garbage objects are considered valid. When false, an object is considered invalid as soon as it is marked for destruction. @param bThreadsafeTest if true then function will just give you information whether referenced UObject is gone forever (return false) or if it is still there (return true, no object flags checked). This is required as without it IsValid can return false during the mark phase of the GC due to the presence of the Unreachable flag. @return true if Get() would return a valid non-null pointer
- L300 _public prototype_ `bool IsValid( ) const;` — Test if this points to a live UObject. This is an optimized version implying bEvenIfGarbage=false, bThreadsafeTest=false. This should be done only when needed as excess resolution of the underlying pointer can cause performance issues. Note that IsValid can not be used on another thread as it will incorrectly return false during the mark phase of the GC due to the Unreachable flag being set. (see bThreadsafeTest above) @return true if Get() would return a valid non-null pointer.
- L308 _public prototype_ `bool IsStale(bool bIncludingGarbage = true, bool bThreadsafeTest = false) const;` — Slightly different than !IsValid(), returns true if this used to point to a UObject, but doesn't any more and has not been assigned or reset in the mean time. @param bIncludingGarbage if this is false, Garbage objects are NOT considered stale @param bThreadsafeTest set it to true when testing outside of Game Thread. Results in false if WeakObjPtr point to an existing object (no flags checked) @return true if this used to point at a real object but no longer does.
- L314 _public function_ `inline bool IsExplicitlyNull() const` — Returns true if this pointer was explicitly assigned to null, was reset, or was never initialized. If this returns true, IsValid() and IsStale() will both return false.
- L332 _public function_ `UE_FORCEINLINE_HINT FRemoteObjectId GetRemoteId() const` — Returns remote Id of the object this pointer is referencing
- L340 _public prototype_ `bool HasSameObject(const UObject* Other) const;` — Returns true if this weak pointer resolves to the specified object
- L345 _public function_ `UE_FORCEINLINE_HINT EResidence GetResidence() const` — Returns true if the object this weak pointer represents is owned by another server
- L354 _public function_ `UE_FORCEINLINE_HINT bool IsRemote() const` — `UE_DEPRECATED(5.8, "Use GetResidence() instead.")` — Returns true if the object this weak pointer represents is owned by another server
- L372 _public function_ `inline uint32 GetTypeHash() const` — Hash function.
- L387 _public prototype_ `void Serialize(FArchive& Ar);` — Weak object pointer serialization.  Weak object pointers only have weak references to objects and won't serialize the object when gathering references for garbage collection.  So in many cases, you don't need to bother serializing weak object pointers.  However, serialization is required if you want to load and save your object.
- L390 _private function_ `inline int32 GetObjectIndex_Private() const`
- L406 _private prototype_ `FUObjectItem* TryResolveRemoteObject() const;`
- L407 _private prototype_ `bool CanBeResolved(UE::RemoteObject::Handle::ECanResolveObjectBehavior CanResolveObjectBehavior) const;`
- L414 _private function_ `inline bool SerialNumbersMatch() const` — internal function to test for serial number matches @return true if the serial number in this matches the central table
- L428 _private function_ `inline bool SerialNumbersMatch(FUObjectItem* ObjectItem) const`
- L442 _private function_ `inline FUObjectItem* Internal_GetObjectItem() const`
- L512 _private function_ `inline bool Internal_IsValid(bool bEvenIfGarbage, bool bThreadsafeTest) const` — Private (inlined) version for internal use only. Remote object version of IsValid does not try to resolve remote objects. WeakObjectPtr is considered valid if it points to an existing local object or to a remote object.
- L560 _private function_ `inline UObject* Internal_Get(bool bEvenIfGarbage) const` — Private (inlined) version for internal use only.
- L566 _private prototype_ `TStrongObjectPtr<UObject> Internal_Pin(bool bEvenIfGarbage) const;`
- L567 _private prototype_ `TStrongObjectPtr<UObject> Internal_TryPin(bool& bOutPinValid, bool bEvenIfGarbage) const;`
- L570 _private member_ `int32 ObjectIndex = UE::Core::Private::InvalidWeakObjectIndex;`
- L571 _private member_ `int32 ObjectSerialNumber = 0;`
- L573 _private member_ `int32 ObjectIndex;`
- L574 _private member_ `int32 ObjectSerialNumber;`
- L577 _private member_ `FRemoteObjectId ObjectRemoteId;`

#### Free symbols / members of external scopes

- L27 _macro_ `#define UE_WEAKOBJECTPTR_ZEROINIT_FIX 1`
- L30 _namespace_ `namespace UE`
- L30 _namespace_ `namespace Core` (scope `UE`)
- L30 _namespace_ `namespace Private` (scope `UE::Core`)
- L34 _variable_ `inline constexpr int32 InvalidWeakObjectIndex = 0;` (scope `UE::Core::Private`)
- L583 _function_ `UE_FORCEINLINE_HINT uint32 GetTypeHash(const FWeakObjectPtr& WeakObjectPtr)` — Hash function.

### `Source/Runtime/CoreUObject/Public/UObject/WeakObjectPtrFwd.h` (Public)


#### enum `TIsPODType::(anonymous)`  
`template<> struct TIsPODType<FWeakObjectPtr>`  
_L19-19_

#### struct `TIsPODType`  
`template<> struct TIsPODType<FWeakObjectPtr>`  
_L19-19_

#### enum `TIsZeroConstructType::(anonymous)`  
`template<> struct TIsPODType<FWeakObjectPtr>`  
_L20-20_

#### struct `TIsZeroConstructType`  
`template<> struct TIsPODType<FWeakObjectPtr>`  
_L20-20_

#### enum `TIsWeakPointerType::(anonymous)`  
`template<> struct TIsPODType<FWeakObjectPtr>`  
_L21-21_

#### struct `TIsWeakPointerType`  
`template<> struct TIsPODType<FWeakObjectPtr>`  
_L21-21_

#### Free symbols / members of external scopes

- L19 _enumerator_ `template<> struct TIsPODType<FWeakObjectPtr> { enum { Value = true }; }; template<> struct TIsZeroConstructType<FWeakObjectPtr> { enum { Value = true }; }; template<> struct TIsWeakPointerType<FWeakObjectPtr> { enum { Value = true }; };` (scope `TIsPODType::__anonb292a9220103`)
- L20 _enumerator_ `template<> struct TIsZeroConstructType<FWeakObjectPtr> { enum { Value = true }; }; template<> struct TIsWeakPointerType<FWeakObjectPtr> { enum { Value = true }; };` (scope `TIsZeroConstructType::__anonb292a9220203`)
- L21 _enumerator_ `template<> struct TIsWeakPointerType<FWeakObjectPtr> { enum { Value = true }; };` (scope `TIsWeakPointerType::__anonb292a9220303`)

### `Source/Runtime/CoreUObject/Public/VerseVM/Inline/VVMAbstractVisitorInline.h` (Public)


#### Free symbols / members of external scopes

- L13 _namespace_ `namespace Verse`
- L16 _function_ `inline FAbstractVisitor::FReferrerContext::FReferrerContext(FAbstractVisitor& InVisitor, FReferenceToken InReferrer) : Visitor(InVisitor) , Referrer(InReferrer)` (scope `Verse::FAbstractVisitor::FReferrerContext`)
- L24 _function_ `inline FAbstractVisitor::FReferrerContext::~FReferrerContext()` (scope `Verse::FAbstractVisitor::FReferrerContext`)
- L30 _function_ `template <typename T> inline void FAbstractVisitor::Visit(T& Value, const TCHAR* ElementName)` (scope `Verse::FAbstractVisitor`)
- L38 _function_ `template <typename T> inline void FAbstractVisitor::Visit(T Begin, T End, const TCHAR* ElementName)` (scope `Verse::FAbstractVisitor`) — Simple arrays
- L49 _function_ `template <typename ElementType, typename AllocatorType> inline void FAbstractVisitor::Visit(TArray<ElementType, AllocatorType>& Values, const TCHAR* ElementName)` (scope `Verse::FAbstractVisitor`) — Arrays
- L56 _function_ `template <typename ElementType, typename KeyFuncs, typename Allocator> inline void FAbstractVisitor::Visit(TSet<ElementType, KeyFuncs, Allocator>& Values, const TCHAR* ElementName)` (scope `Verse::FAbstractVisitor`) — Sets
- L66 _function_ `template <typename KeyType, typename ValueType, typename SetAllocator, typename KeyFuncs> inline void FAbstractVisitor::Visit(TMap<KeyType, ValueType, SetAllocator, KeyFuncs>& Values, const TCHAR* ElementName)` (scope `Verse::FAbstractVisitor`) — Maps

### `Source/Runtime/CoreUObject/Public/VerseVM/Inline/VVMArrayBaseInline.h` (Public)


#### Free symbols / members of external scopes

- L17 _namespace_ `namespace Verse`
- L20 _function_ `template <EWriteMode WriteMode> void VBuffer::SetVValue(FAllocationContext Context, uint32 Index, VValue Value)` (scope `Verse::VBuffer`)
- L33 _function_ `inline bool VArrayBase::IsInBounds(uint32 Index) const` (scope `Verse::VArrayBase`)
- L38 _function_ `inline bool VArrayBase::IsInBounds(const VInt& Index, const uint32 Bounds) const` (scope `Verse::VArrayBase`)
- L53 _function_ `inline VValue VArrayBase::GetValue(uint32 Index)` (scope `Verse::VArrayBase`)
- L72 _function_ `inline const VValue VArrayBase::GetValue(uint32 Index) const` (scope `Verse::VArrayBase`)
- L92 _function_ `template <EWriteMode WriteMode > inline void VArrayBase::ConvertDataToVValues(FAllocationContext Context, uint32 NewCapacity)` (scope `Verse::VArrayBase`)
- L113 _function_ `template <EWriteMode WriteMode > inline void VArrayBase::SetValue(FAllocationContext Context, uint32 Index, VValue Value)` (scope `Verse::VArrayBase`)
- L148 _function_ `inline void VArrayBase::SetValue(FAllocationContext Context, uint32 Index, VValue Value)` (scope `Verse::VArrayBase`)
- L153 _function_ `inline void VArrayBase::SetValueTransactionally(FAllocationContext Context, uint32 Index, VValue Value)` (scope `Verse::VArrayBase`)
- L159 _function_ `template <typename TArray> void VArrayBase::SerializeLayoutImpl(FAllocationContext Context, TArray*& This, FStructuredArchiveVisitor& Visitor)` (scope `Verse::VArrayBase`)

### `Source/Runtime/CoreUObject/Public/VerseVM/Inline/VVMBytecodeInline.h` (Public)


#### Free symbols / members of external scopes

- L11 _namespace_ `namespace Verse`
- L14 _function_ `template <typename FunctionType> void FOp::ForEachReg(VProcedure& Procedure, FunctionType&& Function)` (scope `Verse::FOp`)
- L18 _macro_ `#define VISIT_OP(Name) \`
- L36 _function_ `template <typename FunctionType> void FOp::ForEachRegImpl(VProcedure&, FRegisterIndex& Register, FunctionType&& Function)` (scope `Verse::FOp`)
- L45 _function_ `template <typename FunctionType> void FOp::ForEachRegImpl(VProcedure&, FValueOperand& Operand, FunctionType&& Function)` (scope `Verse::FOp`)
- L54 _function_ `template <typename CellType, typename FunctionType> void FOp::ForEachRegImpl(VProcedure&, TWriteBarrier<CellType>&, FunctionType&&)` (scope `Verse::FOp`)
- L59 _function_ `template <typename FunctionType> void FOp::ForEachRegImpl(VProcedure& Procedure, TOperandRange<FValueOperand> ValueOperands, FunctionType&& Function)` (scope `Verse::FOp`)
- L72 _function_ `template <typename CellType, typename FunctionType> void FOp::ForEachRegImpl(VProcedure&, TOperandRange<TWriteBarrier<CellType>>, FunctionType&&)` (scope `Verse::FOp`)
- L77 _function_ `template <typename FunctionType> void FOp::ForEachJump(VProcedure& Procedure, FunctionType&& Function)` (scope `Verse::FOp`)
- L100 _function_ `template <typename FunctionType> void FOp::ForEachJumpImpl(VProcedure& Procedure, TOperandRange<FLabelOffset> LabelOffsets, const TCHAR* Name, FunctionType&& Function)` (scope `Verse::FOp`)
- L109 _function_ `template <typename FunctionType> void FOp::ForEachJumpImpl(VProcedure&, FLabelOffset& Label, const TCHAR* Name, FunctionType&& Function)` (scope `Verse::FOp`)

### `Source/Runtime/CoreUObject/Public/VerseVM/Inline/VVMCellInline.h` (Public)


#### Free symbols / members of external scopes

- L17 _namespace_ `namespace Verse`
- L19 _function_ `inline VEmergentType* VCell::GetEmergentType() const` (scope `Verse::VCell`)
- L24 _function_ `inline const VCppClassInfo* VCell::GetCppClassInfo() const` (scope `Verse::VCell`)
- L29 _function_ `inline void VCell::AddRef(FAccessContext Context)` (scope `Verse::VCell`)
- L34 _function_ `inline void VCell::ReleaseRef()` (scope `Verse::VCell`)
- L40 _function_ `template <typename CastType> bool VCell::IsA() const` (scope `Verse::VCell`)
- L47 _function_ `template <typename CastType> const CastType& VCell::StaticCast() const` (scope `Verse::VCell`)
- L57 _function_ `template <typename CastType> CastType& VCell::StaticCast()` (scope `Verse::VCell`)
- L67 _function_ `template <typename CastType> CastType* VCell::DynamicCast()` (scope `Verse::VCell`)
- L73 _function_ `template <typename CastType> CastType* VCell::DynamicCast() const` (scope `Verse::VCell`)
- L78 _function_ `inline uint32 GetTypeHash(VCell& Cell)` (scope `Verse`)
- L84 _function_ `template <typename TVisitor> void VCell::VisitReferencesImpl(TVisitor& Visitor)` (scope `Verse::VCell`)
- L101 _prototype_ `DEFINE_TRIVIAL_VISIT_REFERENCES(VHeapValue);` (scope `Verse`)

### `Source/Runtime/CoreUObject/Public/VerseVM/Inline/VVMClassInline.h` (Public)


#### Free symbols / members of external scopes

- L18 _namespace_ `namespace Verse`
- L20 _function_ `inline bool FEmergentTypesCacheKeyFuncs::Matches(FEmergentTypesCacheKeyFuncs::KeyInitType A, FEmergentTypesCacheKeyFuncs::KeyInitType B)` (scope `Verse::FEmergentTypesCacheKeyFuncs`)
- L25 _function_ `inline bool FEmergentTypesCacheKeyFuncs::Matches(FEmergentTypesCacheKeyFuncs::KeyInitType A, const VUniqueStringSet& B)` (scope `Verse::FEmergentTypesCacheKeyFuncs`)
- L30 _function_ `inline uint32 FEmergentTypesCacheKeyFuncs::GetKeyHash(FEmergentTypesCacheKeyFuncs::KeyInitType Key)` (scope `Verse::FEmergentTypesCacheKeyFuncs`)
- L35 _function_ `inline uint32 FEmergentTypesCacheKeyFuncs::GetKeyHash(const VUniqueStringSet& Key)` (scope `Verse::FEmergentTypesCacheKeyFuncs`)
- L40 _function_ `inline VArchetype& VArchetype::New(FAllocationContext Context, VValue InNextArchetype, const TArray<VEntry>& InEntries)` (scope `Verse::VArchetype`)
- L46 _function_ `inline VArchetype::VArchetype(FAllocationContext Context, VValue InNextArchetype, const TArray<VEntry>& InEntries) : VCell(Context, &GlobalTrivialEmergentType.Get(Context)) , NumEntries(InEntries.Num())` (scope `Verse::VArchetype`)
- L58 _function_ `inline VArchetype::VArchetype(FAllocationContext Context, const uint32 InNumEntries) : VCell(Context, &GlobalTrivialEmergentType.Get(Context)) , NumEntries(InNumEntries)` (scope `Verse::VArchetype`)
- L68 _function_ `inline VArchetype::VEntry VArchetype::VEntry::Constant(FAllocationContext Context, VUniqueString& InQualifiedField, VValue InType, VValue InValue)` (scope `Verse::VArchetype::VEntry`)
- L79 _function_ `inline VArchetype::VEntry VArchetype::VEntry::Field(FAllocationContext Context, VUniqueString& InQualifiedField, VValue InType)` (scope `Verse::VArchetype::VEntry`)
- L90 _function_ `inline VArchetype::VEntry VArchetype::VEntry::InitializedField(FAllocationContext Context, VUniqueString& InQualifiedField, VValue InType)` (scope `Verse::VArchetype::VEntry`)
- L101 _function_ `inline VArchetype::VEntry VArchetype::VEntry::ObjectField(FAllocationContext Context, VUniqueString& InQualifiedField)` (scope `Verse::VArchetype::VEntry`)
- L112 _function_ `inline bool VArchetype::VEntry::IsConstant() const` (scope `Verse::VArchetype::VEntry`)
- L117 _function_ `inline bool VArchetype::VEntry::IsNativeRepresentation() const` (scope `Verse::VArchetype::VEntry`)
- L122 _function_ `inline bool VArchetype::VEntry::UseCRCName() const` (scope `Verse::VArchetype::VEntry`)
- L127 _function_ `inline bool VArchetype::VEntry::HasDefaultValueExpression() const` (scope `Verse::VArchetype::VEntry`)
- L134 _function_ `inline bool VArchetype::VEntry::IsInstanced() const` (scope `Verse::VArchetype::VEntry`)
- L139 _function_ `inline bool VArchetype::VEntry::IsPredicts() const` (scope `Verse::VArchetype::VEntry`)
- L144 _function_ `inline bool VArchetype::VEntry::IsVar() const` (scope `Verse::VArchetype::VEntry`)
- L150 _function_ `template <class CppStructType> inline VNativeStruct& VClass::NewNativeStruct(FAllocationContext Context, CppStructType&& Struct)` (scope `Verse::VClass`)
- L156 _function_ `inline VClass& VClass::New( FAllocationContext InContext, VPackage* InPackage, VArray* InRelativePath, VArray* InClassName, VArray* InAttributeIndices, VArray* InAttributes, VValue InImportStruct, bool bInNativeBound, EKind InKind, EFlags InFlags, const TArray<VClass*>& InInherited, VArchetype& InArchetype, VProcedure& InConstructor, VProcedure* InBlocks)` (scope `Verse::VClass`)

### `Source/Runtime/CoreUObject/Public/VerseVM/Inline/VVMContextImplInline.h` (Public)


#### Free symbols / members of external scopes

- L12 _namespace_ `namespace Verse`
- L15 _externvar_ `extern FOpErr StopInterpreterSentry;` (scope `Verse`)
- L18 _function_ `template <typename VFrameCallback, typename NativeFrameCallback> void FNativeFrame::WalkCallstackFrames(const FOp* InPC, VFrame* InFrame, VTask* InTask, VFrameCallback FrameCallback, NativeFrameCallback NativeCallback) const` (scope `Verse::FNativeFrame`)

### `Source/Runtime/CoreUObject/Public/VerseVM/Inline/VVMEnterVMInline.h` (Public)


#### Free symbols / members of external scopes

- L19 _namespace_ `namespace Verse`
- L26 _function_ `template <typename TFunctor> void FRunningContext::EnterVM_Internal(EEnterVMMode Mode, TFunctor F)` (scope `Verse::FRunningContext`) — The entry point that all `C++` calls into Verse should go through Style note: Try not to split this function out into other calls too much... we want anyone who reads this to easily be able to grasp the logic-flow.
- L72 _function_ `auto SetupAndRun = [&]()` (scope `Verse::FRunningContext::EnterVM_Internal`)
- L75 _externvar_ `extern FOpErr StopInterpreterSentry;` (scope `Verse::FRunningContext::EnterVM_Internal::__anonb8d1736f0102`)
- L134 _function_ `AutoRTFM::TransactThenOpen([&] { SetupAndRun(); });` (scope `Verse::FRunningContext::EnterVM_Internal`) — `NativeContext.Start` calls `AutoRTFM::StartTransaction()` which can't start a new transaction stack, so we need to make one first.

### `Source/Runtime/CoreUObject/Public/VerseVM/Inline/VVMEnumerationInline.h` (Public)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace Verse`
- L11 _function_ `inline VEnumerator& VEnumeration::GetEnumeratorChecked(int32 IntValue) const` (scope `Verse::VEnumeration`)
- L17 _function_ `inline VEnumeration& VEnumeration::New(FAllocationContext Context, VPackage* Package, VArray* RelativePath, VArray* EnumName, VArray* AttributeIndices, VArray* Attributes, UEnum* ImportEnum, bool bNative, const TArray<VEnumerator*>& Enumerators)` (scope `Verse::VEnumeration`)

### `Source/Runtime/CoreUObject/Public/VerseVM/Inline/VVMEqualInline.h` (Public)


#### Free symbols / members of external scopes

- L17 _namespace_ `namespace Verse`
- L19 _function_ `inline bool IsEmptyContainer(VValue Value)` (scope `Verse`)
- L33 _function_ `template <typename HandlePlaceholderFunction> inline ECompares VValue::Equal(FAllocationContext Context, VValue Left, VValue Right, HandlePlaceholderFunction HandlePlaceholder)` (scope `Verse::VValue`)

### `Source/Runtime/CoreUObject/Public/VerseVM/Inline/VVMIntInline.h` (Public)


#### Free symbols / members of external scopes

- L12 _namespace_ `namespace Verse`
- L15 _function_ `inline VFloat VInt::ConvertToFloat() const` (scope `Verse::VInt`)
- L25 _function_ `inline VInt VInt::Add(FAllocationContext Context, VInt Lhs, VInt Rhs)` (scope `Verse::VInt`)
- L37 _function_ `inline VInt VInt::Sub(FAllocationContext Context, VInt Lhs, VInt Rhs)` (scope `Verse::VInt`)
- L49 _function_ `inline VInt VInt::Mul(FAllocationContext Context, VInt Lhs, VInt Rhs)` (scope `Verse::VInt`)
- L61 _function_ `inline VInt VInt::Div(FAllocationContext Context, VInt Lhs, VInt Rhs, bool* bOutHasNonZeroRemainder )` (scope `Verse::VInt`)
- L88 _function_ `inline VInt VInt::Mod(FAllocationContext Context, VInt Lhs, VInt Rhs)` (scope `Verse::VInt`)
- L105 _function_ `inline VInt VInt::Neg(FAllocationContext Context, VInt x)` (scope `Verse::VInt`)
- L114 _function_ `inline VInt VInt::Abs(FAllocationContext Context, VInt x)` (scope `Verse::VInt`)
- L124 _function_ `inline bool VInt::Eq(FAllocationContext Context, VInt Lhs, VInt Rhs)` (scope `Verse::VInt`)
- L136 _function_ `inline bool VInt::Eq(FAllocationContext Context, VInt Lhs, VValue Rhs)` (scope `Verse::VInt`)
- L149 _function_ `inline bool VInt::Lt(FAllocationContext Context, VInt Lhs, VInt Rhs)` (scope `Verse::VInt`)
- L158 _function_ `inline bool VInt::Gt(FAllocationContext Context, VInt Lhs, VInt Rhs)` (scope `Verse::VInt`)
- L167 _function_ `inline bool VInt::Lte(FAllocationContext Context, VInt Lhs, VInt Rhs)` (scope `Verse::VInt`)
- L176 _function_ `inline bool VInt::Gte(FAllocationContext Context, VInt Lhs, VInt Rhs)` (scope `Verse::VInt`)
- L185 _function_ `inline VInt VInt::AddSlowPath(FAllocationContext Context, VInt Lhs, VInt Rhs)` (scope `Verse::VInt`)
- L203 _function_ `inline VInt VInt::SubSlowPath(FAllocationContext Context, VInt Lhs, VInt Rhs)` (scope `Verse::VInt`)
- L220 _function_ `inline VInt VInt::MulSlowPath(FAllocationContext Context, VInt Lhs, VInt Rhs)` (scope `Verse::VInt`)
- L237 _function_ `inline VInt VInt::DivSlowPath(FAllocationContext Context, VInt Lhs, VInt Rhs, bool* bOutHasNonZeroRemainder)` (scope `Verse::VInt`)
- L258 _function_ `inline VInt VInt::ModSlowPath(FAllocationContext Context, VInt Lhs, VInt Rhs)` (scope `Verse::VInt`)
- L275 _function_ `inline bool VInt::EqSlowPath(FAllocationContext Context, VInt Lhs, VInt Rhs)` (scope `Verse::VInt`)
- L288 _function_ `inline VInt VInt::NegSlowPath(FAllocationContext Context, VInt N)` (scope `Verse::VInt`)
- L294 _function_ `inline VInt VInt::AbsSlowPath(FAllocationContext Context, VInt N)` (scope `Verse::VInt`)
- L300 _function_ `inline bool VInt::LtSlowPath(FAllocationContext Context, VInt Lhs, VInt Rhs)` (scope `Verse::VInt`)
- L307 _function_ `inline bool VInt::GtSlowPath(FAllocationContext Context, VInt Lhs, VInt Rhs)` (scope `Verse::VInt`)
- L314 _function_ `inline bool VInt::LteSlowPath(FAllocationContext Context, VInt Lhs, VInt Rhs)` (scope `Verse::VInt`)
- L322 _function_ `inline bool VInt::GteSlowPath(FAllocationContext Context, VInt Lhs, VInt Rhs)` (scope `Verse::VInt`)
- L330 _function_ `inline VHeapInt& VInt::AsHeapInt(FAllocationContext Context, VInt N)` (scope `Verse::VInt`)
- L337 _function_ `inline bool VInt::IsInt64() const` (scope `Verse::VInt`)
- L350 _function_ `inline int64 VInt::AsInt64() const` (scope `Verse::VInt`)
- L363 _function_ `inline bool VInt::IsUint32() const` (scope `Verse::VInt`)
- L374 _function_ `inline uint32 VInt::AsUint32() const` (scope `Verse::VInt`)
- L380 _function_ `AUTORTFM_OPEN inline uint32 GetTypeHash(VInt Int)` (scope `Verse`)

### `Source/Runtime/CoreUObject/Public/VerseVM/Inline/VVMMapInline.h` (Public)


#### Free symbols / members of external scopes

- L16 _namespace_ `namespace Verse`
- L19 _function_ `inline void VMapBase::Add(FAllocationContext Context, VValue Key, VValue Value)` (scope `Verse::VMapBase`)
- L28 _function_ `inline void VMapBase::AddTransactionally(FAllocationContext Context, VValue Key, VValue Value)` (scope `Verse::VMapBase`)
- L38 _function_ `inline VMapBase::VMapBase(FAllocationContext Context, uint32 InitialCapacity, VEmergentType* Type) : VHeapValue(Context, Type) , NumElements(0) , Capacity(0)` (scope `Verse::VMapBase`)
- L50 _function_ `template <typename GetEntryByIndex> inline VMapBase::VMapBase(FAllocationContext Context, uint32 MaxNumEntries, const GetEntryByIndex& GetEntry, VEmergentType* Type) : VHeapValue(Context, Type) , NumElements(0) , Capacity(0)` (scope `Verse::VMapBase`)
- L104 _function_ `template <typename MapType, typename GetEntryByIndex> inline MapType& VMapBase::New(FAllocationContext Context, uint32 MaxNumEntries, const GetEntryByIndex& GetEntry)` (scope `Verse::VMapBase`)
- L110 _function_ `template <typename MapType> void VMapBase::SerializeLayoutImpl(FAllocationContext Context, MapType*& This, FStructuredArchiveVisitor& Visitor)` (scope `Verse::VMapBase`)

### `Source/Runtime/CoreUObject/Public/VerseVM/Inline/VVMMarkStackVisitorInline.h` (Public)


#### Free symbols / members of external scopes

- L11 _namespace_ `namespace Verse`
- L14 _function_ `template <typename T> inline void FMarkStackVisitor::Visit(T& Value, const TCHAR*)` (scope `Verse::FMarkStackVisitor`)
- L21 _function_ `template <typename T> inline void FMarkStackVisitor::Visit(T Begin, T End, const TCHAR*)` (scope `Verse::FMarkStackVisitor`)
- L30 _function_ `inline void FMarkStackVisitor::Visit(VValue Value, const TCHAR*)` (scope `Verse::FMarkStackVisitor`)
- L44 _function_ `template <typename ElementType, typename AllocatorType> inline void FMarkStackVisitor::Visit(TArray<ElementType, AllocatorType>& Values, const TCHAR*)` (scope `Verse::FMarkStackVisitor`) — Arrays
- L51 _function_ `template <typename ElementType, typename KeyFuncs, typename Allocator> inline void FMarkStackVisitor::Visit(TSet<ElementType, KeyFuncs, Allocator>& Values, const TCHAR*)` (scope `Verse::FMarkStackVisitor`) — Sets
- L61 _function_ `template <typename KeyType, typename ValueType, typename SetAllocator, typename KeyFuncs> inline void FMarkStackVisitor::Visit(TMap<KeyType, ValueType, SetAllocator, KeyFuncs>& Values, const TCHAR*)` (scope `Verse::FMarkStackVisitor`) — Maps

### `Source/Runtime/CoreUObject/Public/VerseVM/Inline/VVMMutableArrayInline.h` (Public)


#### Free symbols / members of external scopes

- L14 _namespace_ `namespace Verse`
- L18 _function_ `template <EWriteMode WriteMode > inline void VMutableArray::AddValue(FAllocationContext Context, VValue Value)` (scope `Verse::VMutableArray`)
- L84 _function_ `template <typename T> inline void VMutableArray::Append(FAllocationContext Context, VArrayBase& Array)` (scope `Verse::VMutableArray`)
- L114 _function_ `template <> inline void VMutableArray::Append<TWriteBarrier<VValue>>(FAllocationContext Context, VArrayBase& Array)` (scope `Verse::VMutableArray`)
- L123 _function_ `inline VMutableArray& VMutableArray::Concat(FAllocationContext Context, VArrayBase& Lhs, VArrayBase& Rhs)` (scope `Verse::VMutableArray`)
- L131 _function_ `inline void VMutableArray::InPlaceMakeImmutable(FAllocationContext Context)` (scope `Verse::VMutableArray`)

### `Source/Runtime/CoreUObject/Public/VerseVM/Inline/VVMNativeConstructorWrapperInline.h` (Public)


#### Free symbols / members of external scopes

- L17 _namespace_ `namespace Verse`
- L20 _function_ `inline bool VNativeConstructorWrapper::CreateFieldCached(FAllocationContext Context, FCreateFieldCacheCase Cache)` (scope `Verse::VNativeConstructorWrapper`)
- L36 _function_ `FOpResult Result = Context.CloseIf(bClose, [&] { void* Data = NativeStruct.GetData(*NativeStruct.GetEmergentType()->CppClassInfo); Field.UProperty->InitializeValue_InContainer(Data); if (Field.Type == EFieldType::FVerseProperty) { Field.UProperty->ContainerPtrToValuePtr<VRestValue>(Data)->Reset(0); } });` (scope `Verse::VNativeConstructorWrapper::CreateFieldCached`)
- L61 _function_ `FOpResult Result = Context.CloseIf(bClose, [&] { Field.UProperty->InitializeValue_InContainer(UEObject); if (Field.Type == EFieldType::FVerseProperty) { Field.UProperty->ContainerPtrToValuePtr<VRestValue>(UEObject)->Reset(0); } });` (scope `Verse::VNativeConstructorWrapper::CreateFieldCached`)
- L77 _function_ `inline bool VNativeConstructorWrapper::CreateField(FAllocationContext Context, VUniqueString& FieldName, FCreateFieldCacheCase* OutCacheCase)` (scope `Verse::VNativeConstructorWrapper`)
- L109 _function_ `FOpResult Result = Context.CloseIf(bClose, [&] { void* Data = NativeStruct->GetData(*NativeStruct->GetEmergentType()->CppClassInfo); Field.UProperty->InitializeValue_InContainer(Data); if (Field.Type == EFieldType::FVerseProperty) { Field.UProperty->ContainerPtrToValuePtr<VRestValue>(Data)->Reset(0); } });` (scope `Verse::VNativeConstructorWrapper::CreateField`)
- L154 _function_ `FOpResult Result = Context.CloseIf(bClose, [&] { Field.UProperty->InitializeValue_InContainer(UEObject); if (Field.Type == EFieldType::FVerseProperty) { Field.UProperty->ContainerPtrToValuePtr<VRestValue>(UEObject)->Reset(0); } });` (scope `Verse::VNativeConstructorWrapper::CreateField`)
- L171 _function_ `inline VValue VNativeConstructorWrapper::WrappedObject() const` (scope `Verse::VNativeConstructorWrapper`)

### `Source/Runtime/CoreUObject/Public/VerseVM/Inline/VVMNativeStructInline.h` (Public)


#### Free symbols / members of external scopes

- L13 _namespace_ `namespace Verse`
- L17 _function_ `template <class CppStructType> inline CppStructType& VNativeStruct::GetStruct()` (scope `Verse::VNativeStruct`)
- L24 _function_ `inline void* VNativeStruct::GetStruct()` (scope `Verse::VNativeStruct`)
- L29 _function_ `inline UScriptStruct* VNativeStruct::GetUScriptStruct(VEmergentType& EmergentType)` (scope `Verse::VNativeStruct`)
- L35 _function_ `template <class CppStructType> inline VNativeStruct& VNativeStruct::New(FAllocationContext Context, VEmergentType& InEmergentType, CppStructType&& InStruct)` (scope `Verse::VNativeStruct`)
- L42 _function_ `inline VNativeStruct& VNativeStruct::NewUninitialized(FAllocationContext Context, VEmergentType& InEmergentType)` (scope `Verse::VNativeStruct`)
- L49 _function_ `inline std::byte* VNativeStruct::AllocateCell(FAllocationContext Context, size_t Size, bool bHasDestructor)` (scope `Verse::VNativeStruct`)
- L56 _function_ `template <class CppStructType> inline VNativeStruct::VNativeStruct(FAllocationContext Context, VEmergentType& InEmergentType, CppStructType&& InStruct) : VObject(Context, InEmergentType)` (scope `Verse::VNativeStruct`)
- L61 _typedef_ `using StructType = typename TDecay<CppStructType>::Type;` (scope `Verse::VNativeStruct::VNativeStruct`)
- L70 _function_ `FOpResult Result = Context.CloseIf(bConstructInClosed, [&] { new (Data) StructType(Forward<CppStructType>(InStruct)); });` (scope `Verse::VNativeStruct::VNativeStruct`)
- L76 _function_ `inline VNativeStruct::VNativeStruct(FAllocationContext Context, VEmergentType& InEmergentType) : VObject(Context, InEmergentType)` (scope `Verse::VNativeStruct`)
- L88 _function_ `FOpResult Result = Context.CloseIf(bInitializeInClosed, [&] { ScriptStruct->InitializeStruct(Data); });` (scope `Verse::VNativeStruct::VNativeStruct`)
- L94 _function_ `inline VNativeStruct::VNativeStruct(FAllocationContext Context) : VObject(Context, GlobalTrivialEmergentType.Get(Context))` (scope `Verse::VNativeStruct`)
- L100 _function_ `inline VNativeStruct::~VNativeStruct()` (scope `Verse::VNativeStruct`)
- L105 _function_ `AutoRTFM::ETransactionStatus Status = AutoRTFM::CloseIfTransactional([&] { ScriptStruct->DestroyStruct(VObject::GetData(*EmergentType->CppClassInfo)); });` (scope `Verse::VNativeStruct::~VNativeStruct`)

### `Source/Runtime/CoreUObject/Public/VerseVM/Inline/VVMObjectInline.h` (Public)


#### Free symbols / members of external scopes

- L26 _namespace_ `namespace Verse`
- L29 _function_ `template <typename TBinaryFunction> bool VObject::AllFields(FAllocationContext Context, TBinaryFunction F)` (scope `Verse::VObject`)
- L42 _function_ `inline FOpResult VObject::LoadField(FAllocationContext Context, const VUniqueString& Name, VValue Self, FLoadFieldCacheCase* OutCacheCase)` (scope `Verse::VObject`)
- L49 _function_ `template <EWriteMode WriteMode> inline FOpResult VObject::SetField(FAllocationContext Context, const VShape& Shape, const VUniqueString& Name, void* Data, VValue Value)` (scope `Verse::VObject`)
- L57 _function_ `template <EWriteMode WriteMode> inline FOpResult VObject::SetField(FAllocationContext Context, const VShape::VEntry& Field, void* Data, VValue Value)` (scope `Verse::VObject`)
- L81 _function_ `template <EWriteMode WriteMode > inline FOpResult VObject::SetField(FAllocationContext Context, const VUniqueString& Name, VValue Value)` (scope `Verse::VObject`)

### `Source/Runtime/CoreUObject/Public/VerseVM/Inline/VVMPackageInline.h` (Public)


#### Free symbols / members of external scopes

- L13 _namespace_ `namespace Verse`
- L17 _function_ `template <typename FunctorType>` (scope `Verse::VPackage`)
- L21 _function_ `UsedTupleTypes->ForEach([&](VCell* Key, VCell* Value) { F(&Key->StaticCast<VTupleType>()); });` (scope `Verse::VPackage::ForEachUsedTupleType`)
- L26 _function_ `template <typename FunctorType>` (scope `Verse::VPackage`)

### `Source/Runtime/CoreUObject/Public/VerseVM/Inline/VVMPlaceholderInline.h` (Public)


#### Free symbols / members of external scopes

- L9 _namespace_ `namespace Verse`
- L11 _function_ `inline void VPlaceholder::SetModeTrailed(FAllocationContext Context, FTrail& Trail, EMode InMode)` (scope `Verse::VPlaceholder`)

### `Source/Runtime/CoreUObject/Public/VerseVM/Inline/VVMRefInline.h` (Public)


#### Free symbols / members of external scopes

- L14 _namespace_ `namespace Verse`
- L16 _function_ `inline void VRestValue::SetTransactionally(FAccessContext Context, VValue NewValue)` (scope `Verse::VRestValue`)
- L22 _function_ `inline void VRestValue::SetTrailed(FAllocationContext Context, FTrail& Trail, VValue NewValue)` (scope `Verse::VRestValue`)
- L29 _function_ `template <typename UnaryFunction> void FRefAwaiterHeader::ForEach(const TSet<FRefAwaiter>& Set, UnaryFunction F) const` (scope `Verse::FRefAwaiterHeader`)
- L38 _function_ `template <typename UnaryFunction> bool FRefAwaiterHeader::AnyOf(const TSet<FRefAwaiter>& Set, UnaryFunction F) const` (scope `Verse::FRefAwaiterHeader`)
- L56 _function_ `FRefAwaiter::FRefAwaiter(FAccessContext Context, VTask& Task, const FOp& AwaitPC) : Task` (scope `Verse::FRefAwaiter`)
- L62 _function_ `inline bool operator==(const FRefAwaiter& Left, const FRefAwaiter& Right)` (scope `Verse`)
- L67 _function_ `inline uint32 GetTypeHash(const FRefAwaiter& Arg)` (scope `Verse`)
- L76 _function_ `template <typename UnaryFunction> void VRefRareData::ForEachAwaitTask(UnaryFunction F) const` (scope `Verse::VRefRareData`)
- L79 _function_ `AwaiterHeader.ForEach(AwaiterBuffer, [&](const FRefAwaiter& Awaiter) { AutoRTFM::UnreachableIfClosed("#jira SOL-8415"); if (ContainsAwaitTask(*Awaiter.Task, *Awaiter.AwaitPC)) { F(*Awaiter.Task); } });` (scope `Verse::VRefRareData::ForEachAwaitTask`)
- L89 _function_ `template <typename UnaryFunction> bool VRefRareData::AnyAwaitTask(UnaryFunction F) const` (scope `Verse::VRefRareData`)
- L92 _function_ `return AwaiterHeader.AnyOf(AwaiterBuffer, [&](const FRefAwaiter& Awaiter) { AutoRTFM::UnreachableIfClosed("#jira SOL-8415"); return ContainsAwaitTask(*Awaiter.Task, *Awaiter.AwaitPC) && F(*Awaiter.Task); });` (scope `Verse::VRefRareData::AnyAwaitTask`)
- L98 _function_ `inline void VRef::Set(FAllocationContext Context, VValue NewValue)` (scope `Verse::VRef`)

### `Source/Runtime/CoreUObject/Public/VerseVM/Inline/VVMScopeInline.h` (Public)


#### Free symbols / members of external scopes

- L10 _namespace_ `namespace Verse`
- L12 _function_ `inline size_t VScope::NumBytes(uint32 NumCaptures)` (scope `Verse::VScope`)
- L18 _function_ `inline VScope& VScope::New(FAllocationContext Context, VScope* ParentScope, uint32 NumCaptures)` (scope `Verse::VScope`)
- L23 _function_ `inline VScope& VScope::New(FAllocationContext Context, VArchetype& Archetype)` (scope `Verse::VScope`)
- L30 _function_ `inline VScope& VScope::New(FAllocationContext Context)` (scope `Verse::VScope`)
- L35 _function_ `inline VScope& VScope::NewUninitialized(FAllocationContext Context, uint32 NumCaptures)` (scope `Verse::VScope`)
- L40 _function_ `inline VScope& VScope::GetRootScope()` (scope `Verse::VScope`)
- L53 _function_ `inline VScope::VScope(FAllocationContext Context, VScope* ParentScope, uint32 NumCaptures) : VCell` (scope `Verse::VScope`)

### `Source/Runtime/CoreUObject/Public/VerseVM/Inline/VVMShapeInline.h` (Public)


#### Free symbols / members of external scopes

- L16 _namespace_ `namespace Verse`
- L18 _function_ `inline VShape::VEntry::VEntry(const VShape::VEntry& Other) : Type(Other.Type)` (scope `Verse::VShape::VEntry`)
- L37 _function_ `inline bool VShape::VEntry::IsAccessor() const` (scope `Verse::VShape::VEntry`)
- L42 _function_ `inline bool VShape::VEntry::IsMethod() const` (scope `Verse::VShape::VEntry`)
- L55 _function_ `inline VShape::VEntry::VEntry() : Index(0) , Type(EFieldType::Offset)` (scope `Verse::VShape::VEntry`)
- L59 _function_ `inline VShape::VEntry::VEntry(FProperty* InProperty, EFieldType InType) : UProperty(InProperty) , Type(InType)` (scope `Verse::VShape::VEntry`)
- L63 _function_ `inline VShape::VEntry::VEntry(FAccessContext Context, VValue InConstant) : Value(Context, InConstant) , Type(EFieldType::Constant)` (scope `Verse::VShape::VEntry`)
- L67 _function_ `inline bool VShape::VEntry::operator==(const VShape::VEntry& Other) const` (scope `Verse::VShape::VEntry`)
- L84 _function_ `ECompares Cmp = VValue::Equal(FAllocationContext(FRunningContextPromise()), Value.Get(), Other.Value.Get(), [](VValue Left, VValue Right) { checkSlow(!Left.IsPlaceholder()); checkSlow(!Right.IsPlaceholder()); });` (scope `Verse::VShape::VEntry::operator ==`)
- L93 _function_ `inline bool VShape::FFieldsMapKeyFuncs::Matches(KeyInitType A, KeyInitType B)` (scope `Verse::VShape::FFieldsMapKeyFuncs`)
- L98 _function_ `inline bool VShape::FFieldsMapKeyFuncs::Matches(KeyInitType A, const VUniqueString& B)` (scope `Verse::VShape::FFieldsMapKeyFuncs`)
- L103 _function_ `inline uint32 VShape::FFieldsMapKeyFuncs::GetKeyHash(KeyInitType Key)` (scope `Verse::VShape::FFieldsMapKeyFuncs`)
- L108 _function_ `inline uint32 VShape::FFieldsMapKeyFuncs::GetKeyHash(const VUniqueString& Key)` (scope `Verse::VShape::FFieldsMapKeyFuncs`)
- L113 _function_ `inline const VShape::VEntry* VShape::GetField(const VUniqueString& Name) const` (scope `Verse::VShape`)
- L118 _function_ `inline const VShape::VEntry& VShape::GetField(int32 FieldIndex) const` (scope `Verse::VShape`)
- L123 _function_ `inline uint64 VShape::GetNumFields() const` (scope `Verse::VShape`)
- L128 _function_ `inline bool VShape::operator==(const VShape& Other) const` (scope `Verse::VShape`)
- L133 _function_ `inline uint32 GetTypeHash(const VShape::VEntry& Field)` (scope `Verse`)
- L149 _function_ `inline uint32 GetTypeHash(const VShape& Shape)` (scope `Verse`)

### `Source/Runtime/CoreUObject/Public/VerseVM/Inline/VVMUniqueStringInline.h` (Public)


#### Free symbols / members of external scopes

- L11 _namespace_ `namespace Verse`
- L14 _function_ `template <typename T> inline FUtf8StringView FUniqueStringSetKeyFuncsBase<T>::GetSetKey(VUniqueString& Element)` (scope `Verse::FUniqueStringSetKeyFuncsBase`)
- L20 _function_ `template <typename T> inline FUtf8StringView FUniqueStringSetKeyFuncsBase<T>::GetSetKey(const T& Element)` (scope `Verse::FUniqueStringSetKeyFuncsBase`)
- L33 _function_ `template <typename T> inline bool FUniqueStringSetKeyFuncsBase<T>::Matches(FUtf8StringView A, FUtf8StringView B)` (scope `Verse::FUniqueStringSetKeyFuncsBase`)
- L39 _function_ `template <typename T> inline uint32 FUniqueStringSetKeyFuncsBase<T>::GetKeyHash(FUtf8StringView Key)` (scope `Verse::FUniqueStringSetKeyFuncsBase`)
- L44 _variable_ `template struct FUniqueStringSetKeyFuncsBase<TWeakBarrier<VUniqueString>>;` (scope `Verse`)
- L47 _function_ `inline VUniqueStringSet::FConstIterator::FConstIterator(SetType::TRangedForConstIterator InCurrentIteration) : CurrentIteration(InCurrentIteration)` (scope `Verse::VUniqueStringSet::FConstIterator`)
- L50 _function_ `inline const TWriteBarrier<VUniqueString>* VUniqueStringSet::FConstIterator::operator->() const` (scope `Verse::VUniqueStringSet::FConstIterator`)
- L55 _function_ `inline const TWriteBarrier<VUniqueString>& VUniqueStringSet::FConstIterator::operator*() const` (scope `Verse::VUniqueStringSet::FConstIterator`)
- L60 _function_ `inline bool VUniqueStringSet::FConstIterator::operator==(const FConstIterator& Rhs) const` (scope `Verse::VUniqueStringSet::FConstIterator`)
- L65 _function_ `inline bool VUniqueStringSet::FConstIterator::operator!=(const FConstIterator& Rhs) const` (scope `Verse::VUniqueStringSet::FConstIterator`)
- L70 _function_ `inline VUniqueStringSet::FConstIterator& VUniqueStringSet::FConstIterator::operator++()` (scope `Verse::VUniqueStringSet::FConstIterator`)
- L76 _function_ `inline VUniqueStringSet::FConstIterator VUniqueStringSet::begin() const` (scope `Verse::VUniqueStringSet`)
- L81 _function_ `inline VUniqueStringSet::FConstIterator VUniqueStringSet::end() const` (scope `Verse::VUniqueStringSet`)
- L86 _function_ `inline VUniqueStringSet& VUniqueStringSet::New(FAllocationContext Context, TSet<VUniqueString*> InStrings)` (scope `Verse::VUniqueStringSet`)
- L91 _function_ `inline VUniqueStringSet& VUniqueStringSet::New(FAllocationContext Context, const std::initializer_list<FUtf8StringView>& InStrings)` (scope `Verse::VUniqueStringSet`)
- L103 _function_ `inline VUniqueStringSet& VUniqueStringSet::Make(FAllocationContext Context, const TSet<VUniqueString*>& InSet)` (scope `Verse::VUniqueStringSet`)
- L110 _function_ `inline bool VUniqueStringSet::operator==(const VUniqueStringSet& Other) const` (scope `Verse::VUniqueStringSet`)
- L116 _function_ `inline uint32 VUniqueStringSet::Num() const` (scope `Verse::VUniqueStringSet`)
- L121 _function_ `inline FSetElementId VUniqueStringSet::FindId(const FUtf8StringView& String) const` (scope `Verse::VUniqueStringSet`)
- L126 _function_ `inline bool VUniqueStringSet::IsValidId(const FSetElementId& Id) const` (scope `Verse::VUniqueStringSet`)
- L131 _function_ `inline VUniqueStringSet::SetType VUniqueStringSet::FormSet(FAllocationContext Context, const TSet<VUniqueString*>& InSet)` (scope `Verse::VUniqueStringSet`)
- L143 _function_ `inline VUniqueStringSet::VUniqueStringSet(FAllocationContext Context, const TSet<VUniqueString*>& InSet) : VCell(Context, &GlobalTrivialEmergentType.Get(Context)) , Strings(FormSet(Context, InSet))` (scope `Verse::VUniqueStringSet`)
- L149 _function_ `inline bool VUniqueStringSet::Equals(const TSet<VUniqueString*>& A, const TSet<VUniqueString*>& B)` (scope `Verse::VUniqueStringSet`)
- L158 _function_ `inline uint32 GetSetVUniqueStringTypeHash(const TSet<VUniqueString*>& Set)` (scope `Verse`)
- L172 _function_ `inline uint32 GetTypeHash(const VUniqueStringSet& Set)` (scope `Verse`)
- L185 _function_ `inline FHashableUniqueStringSetKey::FHashableUniqueStringSetKey() : Type(EType::Invalid)` (scope `Verse::FHashableUniqueStringSetKey`)
- L188 _function_ `inline FHashableUniqueStringSetKey::FHashableUniqueStringSetKey(const TSet<VUniqueString*>& InSet) : Set(&InSet) , Type(EType::Set)` (scope `Verse::FHashableUniqueStringSetKey`)
- L192 _function_ `inline FHashableUniqueStringSetKey::FHashableUniqueStringSetKey(const VUniqueStringSet& InCell) : Cell(&InCell) , Type(EType::Cell)` (scope `Verse::FHashableUniqueStringSetKey`)
- L196 _function_ `inline bool FHashableUniqueStringSetKey::operator==(const FHashableUniqueStringSetKey& Other) const` (scope `Verse::FHashableUniqueStringSetKey`)
- L198 _function_ `auto CompareCellAndSet = [](const VUniqueStringSet& InCell, const TSet<VUniqueString*>& InSet)` (scope `Verse::FHashableUniqueStringSetKey::operator ==`)
- L213 _function_ `auto CompareCells = [](const VUniqueStringSet& InCell, const VUniqueStringSet& InOther)` (scope `Verse::FHashableUniqueStringSetKey::operator ==`)
- L267 _function_ `inline FHashableUniqueStringSetKeyFuncs::KeyInitType FHashableUniqueStringSetKeyFuncs::GetSetKey(FHashableUniqueStringSetKeyFuncs::ElementInitType& Element)` (scope `Verse::FHashableUniqueStringSetKeyFuncs`)
- L272 _function_ `inline FHashableUniqueStringSetKeyFuncs::KeyInitType FHashableUniqueStringSetKeyFuncs::GetSetKey(const TWeakBarrier<VUniqueStringSet>& Element)` (scope `Verse::FHashableUniqueStringSetKeyFuncs`)
- L285 _function_ `inline bool FHashableUniqueStringSetKeyFuncs::Matches(FHashableUniqueStringSetKeyFuncs::KeyInitType A, FHashableUniqueStringSetKeyFuncs::KeyInitType B)` (scope `Verse::FHashableUniqueStringSetKeyFuncs`)
- L290 _function_ `inline uint32 FHashableUniqueStringSetKeyFuncs::GetKeyHash(KeyInitType Key)` (scope `Verse::FHashableUniqueStringSetKeyFuncs`)

### `Source/Runtime/CoreUObject/Public/VerseVM/Inline/VVMValueInline.h` (Public)


#### Free symbols / members of external scopes

- L21 _namespace_ `namespace Verse`
- L23 _function_ `V_FORCEINLINE VValue VRestValue::Get(FAllocationContext Context)` (scope `Verse::VRestValue`)
- L33 _function_ `V_FORCEINLINE VValue VRestValue::GetTransactionally(FAllocationContext Context)` (scope `Verse::VRestValue`)
- L42 _function_ `inline bool VRestValue::operator==(const VRestValue& Other) const` (scope `Verse::VRestValue`)
- L51 _function_ `inline VValue::VValue(VCell& Cell) : Cell(&Cell)` (scope `Verse::VValue`)
- L58 _function_ `inline VValue::VValue(UObject* Object) : EncodedBits(BitCast<uint64>(Object) | UObjectTag)` (scope `Verse::VValue`)
- L64 _function_ `inline bool VValue::IsInt() const` (scope `Verse::VValue`)
- L69 _function_ `inline VInt VValue::AsInt() const` (scope `Verse::VValue`)
- L74 _function_ `inline bool VValue::IsUint32() const` (scope `Verse::VValue`)
- L79 _function_ `inline uint32 VValue::AsUint32() const` (scope `Verse::VValue`)
- L84 _function_ `inline VValue VValue::FromBool(bool Bool)` (scope `Verse::VValue`)
- L89 _function_ `V_FORCEINLINE VValue VValue::Follow() const` (scope `Verse::VValue`)
- L99 _function_ `inline VPlaceholder& VValue::GetRootPlaceholder()` (scope `Verse::VValue`)
- L104 _function_ `inline void VValue::EnqueueSuspension(FAccessContext Context, VSuspension& Suspension)` (scope `Verse::VValue`)
- L109 _function_ `inline bool VValue::IsLogic() const` (scope `Verse::VValue`)
- L114 _function_ `inline bool VValue::AsBool() const` (scope `Verse::VValue`)
- L120 _function_ `inline bool VValue::IsEnumerator() const` (scope `Verse::VValue`)
- L126 _function_ `template <typename ObjectType> bool VValue::IsCellOfType() const` (scope `Verse::VValue`)
- L132 _function_ `template <typename ObjectType> ObjectType& VValue::StaticCast() const` (scope `Verse::VValue`)
- L138 _function_ `template <typename ObjectType> ObjectType* VValue::DynamicCast() const` (scope `Verse::VValue`)
- L143 _function_ `inline uint32 GetTypeHash(VValue Value)` (scope `Verse`)
- L188 _function_ `inline uint32 GetTypeHash(const VPlaceholder& Placeholder)` (scope `Verse`)
- L196 _function_ `inline uint32 GetTypeHash(VRestValue RestValue)` (scope `Verse`)
- L201 _function_ `inline VValue VValue::Melt(FAllocationContext Context, VValue Value)` (scope `Verse::VValue`)
- L210 _function_ `inline FOpResult VValue::Freeze(FAllocationContext Context, VValue Value, VTask* Task)` (scope `Verse::VValue`)

### `Source/Runtime/CoreUObject/Public/VerseVM/Inline/VVMValueObjectInline.h` (Public)


#### Free symbols / members of external scopes

- L19 _namespace_ `namespace Verse`
- L22 _function_ `inline VValueObject& VValueObject::NewUninitialized(FAllocationContext Context, VEmergentType& InEmergentType)` (scope `Verse::VValueObject`)
- L27 _function_ `inline VValueObject::VValueObject(FAllocationContext Context, VEmergentType& InEmergentType) : VObject(Context, InEmergentType)` (scope `Verse::VValueObject`)
- L41 _function_ `inline bool VValueObject::CreateFieldCached(FAllocationContext Context, FCreateFieldCacheCase Cache)` (scope `Verse::VValueObject`)
- L59 _function_ `inline bool VValueObject::CreateField(FAllocationContext Context, VUniqueString& Name, FCreateFieldCacheCase* OutCacheCase)` (scope `Verse::VValueObject`)

### `Source/Runtime/CoreUObject/Public/VerseVM/Inline/VVMVerseClassInline.h` (Public)


#### Free symbols / members of external scopes

- L8 _function_ `inline Verse::VClass* UVerseClass::GetVerseClass(Verse::FAllocationContext Context, UClass* Class)` (scope `UVerseClass`)
- L25 _function_ `inline Verse::VShape* UVerseClass::GetShape(Verse::FAllocationContext Context, UClass* Class)` (scope `UVerseClass`)
- L38 _function_ `inline Verse::VShape& UVerseClass::GetShapeForLoadField(Verse::FAllocationContext Context, UClass* Class)` (scope `UVerseClass`)
- L55 _function_ `inline Verse::FOpResult UVerseClass::LoadField(Verse::FAllocationContext Context, UObject* Object, Verse::VUniqueString& FieldName, Verse::VValue Self)` (scope `UVerseClass`)

### `Source/Runtime/CoreUObject/Public/VerseVM/Inline/VVMWeakCellMapInline.h` (Public)


#### Free symbols / members of external scopes

- L9 _namespace_ `namespace Verse`
- L13 _function_ `template <typename FunctorType> void VWeakCellMap::ForEach(FunctorType&& F)` (scope `Verse::VWeakCellMap`)

### `Source/Runtime/CoreUObject/Public/VerseVM/Inline/VVMWriteBarrierInline.h` (Public)


#### Free symbols / members of external scopes

- L9 _namespace_ `namespace Verse`
- L13 _function_ `template <typename T> inline void TWriteBarrier<T>::SetTrailed(FAllocationContext Context, FTrail& Trail, TValue NewValue)` (scope `Verse::TWriteBarrier`)
- L20 _function_ `template <typename T> inline void TWriteBarrier<T>::SetNonCellNorPlaceholderTrailed(FAllocationContext Context, FTrail& Trail, VValue NewValue) requires bIsVValue` (scope `Verse::TWriteBarrier`)

### `Source/Runtime/CoreUObject/Public/VerseVM/VBPVMDynamicProperty.h` (Public)


#### class `FVerseDynamicProperty`  
`class FVerseDynamicProperty : public TProperty<UE::FDynamicallyTypedValue, FProperty>`  
_L12-51_
- inherits: `TProperty<UE::FDynamicallyTypedValue,FProperty>`
- desc: Metadata for a property of FVerseValue type.
- L17 _public prototype_ `FVerseDynamicProperty(FFieldVariant InOwner, const FName& InName);`
- L24 _public prototype_ `FVerseDynamicProperty(FFieldVariant InOwner, const UECodeGen_Private::FVerseValuePropertyParams& Prop);` — Constructor used for constructing compiled in properties @param InOwner Owner of the property @param Prop Pointer to the compiled in structure describing the property
- L27 _public function_ `explicit consteval FVerseDynamicProperty(UE::CodeGen::ConstInit::FPropertyParams InBaseParams) : Super(InBaseParams)`
- L34 _public prototype_ `virtual FString GetCPPMacroType(FString& ExtendedTypeText) const override;` — UHT interface
- L38 _public prototype_ `virtual void InstanceSubobjects(void* Data, void const* DefaultData, TNotNull<UObject*> Owner, struct FObjectInstancingGraph* InstanceGraph) override;` — FProperty interface
- L39 _public prototype_ `virtual bool Identical(TNotNull<const void*> A, const void* B, uint32 PortFlags) const override;`
- L40 _public prototype_ `virtual void SerializeItem(FStructuredArchive::FSlot Slot, TNotNull<void*> Value, void const* Defaults) const override;`
- L41 _public prototype_ `virtual void ExportText_Internal(FString& ValueStr, TNotNull<const void*> PropertyValueOrContainer, EPropertyPointerType PointerType, const void* DefaultValue, UObject* Parent, int32 PortFlags, UObject* ExportRootScope) const override;`
- L42 _public prototype_ `virtual const TCHAR* ImportText_Internal(const TCHAR* Buffer, TNotNull<void*> ContainerOrPropertyPtr, EPropertyPointerType PropertyPointerType, UObject* OwnerObject, int32 PortFlags, FOutputDevice* ErrorText) const override;`
- L43 _public prototype_ `virtual bool ContainsObjectReference(TArray<const FStructProperty*>& EncounteredStructProps, EPropertyObjectReferenceType InReferenceType = EPropertyObjectReferenceType::Strong) const override;`
- L44 _public prototype_ `virtual void EmitReferenceInfo(UE::GC::FSchemaBuilder& Schema, int32 BaseOffset, TArray<const FStructProperty*>& EncounteredStructProps, UE::GC::FPropertyStack& DebugPath) override;`
- L45 _public prototype_ `virtual uint32 GetValueTypeHashInternal(const void* Src) const override;`
- L46 _public function_ `virtual bool HasIntrusiveUnsetOptionalState() const override`

### `Source/Runtime/CoreUObject/Public/VerseVM/VBPVMRuntimeType.h` (Public)


#### struct `UE::Verse::FRuntimeType`  
`struct FRuntimeType : FDynamicallyTypedValueType`  
_L39-115_
- inherits: `FDynamicallyTypedValueType`
- L48 _public member_ `const EKind Kind;`
- L50 _public function_ `FRuntimeType(EKind InKind, SIZE_T InNumBytes, uint8 InMinAlignmentLogTwo, EContainsReferences InContainsReferences) : FDynamicallyTypedValueType(InNumBytes, InMinAlignmentLogTwo, InContainsReferences) , Kind(InKind)`
- L57 _public function_ `virtual ~FRuntimeType()` — This can _not_ be = default; for reasons I don't understand
- L59 _public function_ `virtual void InitializeValueFromCopy(void* DestData, const void* SourceData) const override`
- L64 _public prototype_ `virtual void AppendDiagnosticString(FUtf8StringBuilderBase& Builder, const void* Data, uint32 RecursionDepth) const = 0;`
- L66 _public function_ `virtual void MarkReachable(FReferenceCollector& Collector) override`
- L70 _public function_ `void UnmarkReachable()`
- L74 _public function_ `bool IsReachable() const`
- L97 _public prototype_ `virtual bool AreEquivalent(const void* DataA, const FRuntimeType& TypeB, const void* DataB) const = 0;`
- L98 _public prototype_ `virtual void ExportValueToText(FString& OutputString, const void* Data, const void* DefaultData, UObject* Parent, UObject* ExportRootScope) const = 0;`
- L99 _public prototype_ `virtual bool ImportValueFromText(const TCHAR*& InputString, void* Data, UObject* Parent, FOutputDevice* ErrorText) const = 0;`
- L101 _public function_ `virtual void InstanceSubobjects(void* Data, void const* DefaultData, TNotNull<UObject*> Owner, FObjectInstancingGraph* InstanceGraph) const`
- L103 _public function_ `virtual bool IsValid(const void* Data) const`
- L105 _public function_ `virtual bool HasIntrusiveUnsetOptionalState() const`
- L106 _public function_ `virtual void InitializeIntrusiveUnsetOptionalValue(void* Data) const`
- L107 _public function_ `virtual bool IsIntrusiveOptionalValueSet(const void* Data) const`
- L114 _private member_ `std::atomic<bool> bIsReachable{false};`

#### enum `UE::Verse::FRuntimeType::EKind`  
`enum class EKind : uint8`  
_L41-46_
- L44 _public enumerator_ `VERSE_ENUM_RUNTIME_TYPE_KINDS(VISIT_KIND) #undef VISIT_KIND`

#### struct `UE::Verse::FRuntimeTypeDynamic`  
`struct FRuntimeTypeDynamic : FRuntimeType`  
_L140-182_
- inherits: `FRuntimeType`
- L142 _public prototype_ `static FRuntimeTypeDynamic& Get();`
- L145 _public prototype_ `virtual void AppendDiagnosticString(FUtf8StringBuilderBase& Builder, const void* Data, uint32 RecursionDepth) const override;` — Verse::FRuntimeType interface.
- L148 _public prototype_ `virtual void MarkValueReachable(void* Data, FReferenceCollector& Collector) const override;` — FDynamicallyTypedValueType interface.
- L150 _public prototype_ `virtual void InitializeValue(void* Data) const override;`
- L151 _public prototype_ `virtual void InitializeValueFrom(void* DestData, const void* SourceData, const FRuntimeType& SourceType) const override;`
- L152 _public prototype_ `virtual void DestroyValue(void* Data) const override;`
- L155 _public prototype_ `AUTORTFM_DISABLE virtual ::Verse::VValue ToVValue(::Verse::FAllocationContext Context, const void* Data) const override;`
- L158 _public prototype_ `virtual void SerializeValue(FStructuredArchive::FSlot Slot, void* Data, const void* DefaultData) const override;`
- L160 _public prototype_ `virtual void ExportValueToText(FString& OutputString, const void* Data, const void* DefaultData, UObject* Parent, UObject* ExportRootScope) const override;`
- L161 _public prototype_ `virtual bool ImportValueFromText(const TCHAR*& InputString, void* Data, UObject* Parent, FOutputDevice* ErrorText) const override;`
- L163 _public prototype_ `virtual uint32 GetValueHash(const void* Data) const override;`
- L164 _public prototype_ `virtual bool AreIdentical(const void* DataA, const void* DataB) const override;`
- L165 _public prototype_ `virtual bool AreEquivalent(const void* DataA, const FRuntimeType& TypeB, const void* DataB) const override;`
- L167 _public prototype_ `virtual void InstanceSubobjects(void* Data, void const* DefaultData, TNotNull<UObject*> Owner, FObjectInstancingGraph* InstanceGraph) const override;`
- L169 _public prototype_ `virtual bool IsValid(const void* Data) const;`
- L171 _public prototype_ `virtual void ForEachSubobject(const void* Data, TFunctionRef<void(const UObject*)> ObjectFunc) const override;`
- L174 _private function_ `FRuntimeTypeDynamic() : FRuntimeType( FRuntimeType::EKind::Dynamic, sizeof(FDynamicallyTypedValue), UE_FORCE_CONSTEVAL(FMath::ConstExprCeilLogTwo(alignof(FDynamicallyTypedValue))), EContainsReferences::Maybe)`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace Verse` (scope `UE`)
- L19 _macro_ `#define VERSE_ENUM_RUNTIME_TYPE_KINDS(v) \`
- L43 _macro_ `#define VISIT_KIND(Name) Name,`
- L79 _function_ `friend uint32 GetTypeHash(const FRuntimeType& Type)` (scope `UE::Verse`)
- L83 _function_ `friend uint32 GetTypeHash(const TArray<FRuntimeType*>& Types)` (scope `UE::Verse`)
- L92 _function_ `friend bool operator==(FRuntimeType& Lhs, FRuntimeType& Rhs)` (scope `UE::Verse`)
- L120 _macro_ `#define VERSE_DEFINE_NONPARAMETRIC_RUNTIME_TYPE(RuntimeTypeType, CType) \`
- L131 _macro_ `#define VERSE_IMPLEMENT_GLOBAL_RUNTIME_TYPE(RuntimeTypeClass) \` — Implement the static Get functions for the global types.
- L138 _prototype_ `bool AreEquivalent(const FRuntimeType& TypeA, const void* DataA, const FDynamicallyTypedValue& ValueB);` (scope `UE::Verse`)

### `Source/Runtime/CoreUObject/Public/VerseVM/VVMAbstractVisitor.h` (Public)


#### struct `Verse::FAbstractVisitor`  
`struct FAbstractVisitor`  
_L21-117_
- L25 _public member_ `static constexpr bool bIsAbstractVisitor = true;`
- L42 _public prototype_ `virtual ~FAbstractVisitor() = default;`
- L45 _public function_ `FReferrerContext* GetContext() const` — The context provides information about the current cell being visited
- L52 _public prototype_ `virtual void VisitNonNull(VCell* InCell, const TCHAR* ElementName) = 0;`
- L53 _public prototype_ `virtual void VisitNonNull(UObject* InObject, const TCHAR* ElementName) = 0;`
- L54 _public prototype_ `virtual void VisitAuxNonNull(void* InAux, const TCHAR* ElementName) = 0;`
- L58 _public prototype_ `void Visit(VCell* InCell, const TCHAR* ElementName);`
- L59 _public prototype_ `void Visit(UObject* InObject, const TCHAR* ElementName);`
- L60 _public prototype_ `void VisitAux(void* InAux, const TCHAR* ElementName);`
- L62 _public prototype_ `void Visit(VValue Value, const TCHAR* ElementName);`
- L65 _public function_ `template <typename T> void Visit(TWriteBarrier<T>& Value, const TCHAR* ElementName)`
- L71 _public function_ `template <typename T> void Visit(TObjectPtr<T>& Value, const TCHAR* ElementName)`
- L77 _public prototype_ `template <typename T> void Visit(T& Value, const TCHAR* ElementName);`
- L81 _public prototype_ `template <typename T> void Visit(T Begin, T End, const TCHAR* ElementName);` — Simple arrays
- L84 _public function_ `template <typename T> void Visit(T* Values, uint64 Count, const TCHAR* ElementName)`
- L91 _public prototype_ `template <typename ElementType, typename AllocatorType> void Visit(TArray<ElementType, AllocatorType>& Values, const TCHAR* ElementName);` — Arrays
- L95 _public prototype_ `template <typename ElementType, typename KeyFuncs, typename Allocator> void Visit(TSet<ElementType, KeyFuncs, Allocator>& Values, const TCHAR* ElementName);` — Sets
- L99 _public prototype_ `template <typename KeyType, typename ValueType, typename SetAllocator, typename KeyFuncs> void Visit(TMap<KeyType, ValueType, SetAllocator, KeyFuncs>& Values, const TCHAR* ElementName);` — Maps
- L103 _public prototype_ `virtual bool IsMarked(VCell* InCell, const TCHAR* ElementName) = 0;`
- L104 _public prototype_ `virtual void ReportNativeBytes(size_t Bytes) = 0;`
- L105 _public prototype_ `virtual void MarkNativeStructAsReachable(VNativeStruct* NativeStruct) = 0;`
- L109 _public function_ `void Visit(uint8 Value, const TCHAR* ElementName)`
- L110 _public function_ `void Visit(uint32 Value, const TCHAR* ElementName)`
- L113 _protected prototype_ `FAbstractVisitor() = default;`
- L116 _private member_ `FReferrerContext* Context{nullptr};`

#### struct `Verse::FAbstractVisitor::FReferrerContext`  
`struct FReferrerContext`  
_L28-40_
- desc: A stack based context to maintain the chain of referrers
- L30 _public prototype_ `FReferrerContext(FAbstractVisitor& InVisitor, FReferenceToken InReferrer);`
- L31 _public prototype_ `~FReferrerContext();`
- L33 _public function_ `FReferenceToken GetReferrer() const`
- L34 _public function_ `FReferrerContext* GetPrevious() const`
- L37 _private member_ `FAbstractVisitor& Visitor;`
- L38 _private member_ `FReferenceToken Referrer;`
- L39 _private member_ `FReferrerContext* Previous;`

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace Verse`

### `Source/Runtime/CoreUObject/Public/VerseVM/VVMAccessor.h` (Public)


#### struct `Verse::VAccessor`  
`struct AUTORTFM_DISABLE VAccessor : VCell`  
_L19-98_
- inherits: `VCell`
- L22 _public member_ `static TGlobalTrivialEmergentTypePtr<&StaticCppClassInfo> GlobalTrivialEmergentType;`
- L24 _public function_ `static VAccessor& NewUninitialized(FAllocationContext Context, uint32 InNumAccessors)`
- L30 _public prototype_ `static void SerializeLayout(FAllocationContext Context, VAccessor*& This, FStructuredArchiveVisitor& Visitor);`
- L31 _public prototype_ `void SerializeImpl(FAllocationContext Context, FStructuredArchiveVisitor& Visitor);`
- L34 _public function_ `TWriteBarrier<VUniqueString>& FindGetter(uint32 NumParams)` — `NumParams` -1 and -2 for getters and setters respectively to align them to trailing array positions
- L38 _public function_ `TWriteBarrier<VUniqueString>& FindSetter(uint32 NumParams)`
- L42 _public function_ `void AddGetter(FAllocationContext Context, uint32 NumParams, VUniqueString& Name)`
- L46 _public function_ `void AddSetter(FAllocationContext Context, uint32 NumParams, VUniqueString& Name)`
- L52 _private function_ `TWriteBarrier<VUniqueString>* GetGettersBegin()`
- L53 _private function_ `TWriteBarrier<VUniqueString>* GetGettersEnd()`
- L55 _private function_ `TWriteBarrier<VUniqueString>* GetSettersBegin()`
- L56 _private function_ `TWriteBarrier<VUniqueString>* GetSettersEnd()`
- L58 _private member_ `uint32 NumAccessors;`
- L59 _private member_ `TWriteBarrier<VCell> Trailing[];`
- L68 _private function_ `static FLayout CalcLayout(uint32 NumAccessors)`
- L80 _private function_ `FLayout GetLayout() const`
- L85 _private function_ `VAccessor(FAllocationContext Context, uint32 InNumAccessors) : VCell(Context, &GlobalTrivialEmergentType.Get(Context)) , NumAccessors(InNumAccessors)`

#### struct `Verse::VAccessor::FLayout`  
`struct FLayout`  
_L61-66_
- L63 _public member_ `int32 GettersOffset;`
- L64 _public member_ `int32 SettersOffset;`
- L65 _public member_ `int32 TotalSize;`

#### struct `Verse::VAccessorRef`  
`struct AUTORTFM_DISABLE VAccessorRef : VHeapValue`  
_L100-132_
- inherits: `VHeapValue`
- L103 _public member_ `static TGlobalTrivialEmergentTypePtr<&StaticCppClassInfo> GlobalTrivialEmergentType;`
- L105 _public member_ `static TGlobalHeapPtr<VEnumerator> AccessorEnum;`
- L108 _public member_ `TWriteBarrier<VValue> Base;` — The source this ref was projected from. Either an object or another VAccessorRef.
- L111 _public member_ `TWriteBarrier<VValue> Member;` — The member projected from Base. Either a VAccessor or an argument to the getter/setter.
- L113 _public prototype_ `VAccessorRef& Flatten(FAllocationContext Context, TArray<TWriteBarrier<VValue>>& OutArguments, int32 Depth);`
- L115 _public function_ `static VAccessorRef& New(FAllocationContext Context, VValue Base, VAccessor& Member)`
- L120 _public function_ `static VAccessorRef& New(FAllocationContext Context, VAccessorRef& Base, VValue Member)`
- L126 _private function_ `VAccessorRef(FAllocationContext Context, VValue InBase, VValue InMember) : VHeapValue(Context, &GlobalTrivialEmergentType.Get(Context)) , Base(Context, InBase) , Member(Context, InMember)`

#### struct `Verse::VAccessorSuspension`  
`struct AUTORTFM_DISABLE VAccessorSuspension : VCell`  
_L135-168_
- inherits: `VCell`
- desc: A postponed setter call. Used when verse.UObjectLeniency is disabled.
- L138 _public member_ `static TGlobalTrivialEmergentTypePtr<&StaticCppClassInfo> GlobalTrivialEmergentType;`
- L140 _public member_ `TWriteBarrier<VAccessorSuspension> Next;`
- L141 _public member_ `TWriteBarrier<VAccessorSuspension> Prev;`
- L143 _public member_ `TWriteBarrier<VAccessorRef> Ref;`
- L144 _public member_ `TWriteBarrier<VValue> Value;`
- L146 _public function_ `static VAccessorSuspension& New(FAllocationContext Context, VAccessorRef& Ref, VValue Value)`
- L151 _public function_ `void Append(FAllocationContext Context, VAccessorSuspension& Other)`
- L160 _private function_ `VAccessorSuspension(FAllocationContext Context, VAccessorRef& InRef, VValue InValue) : VCell(Context, &GlobalTrivialEmergentType.Get(Context)) , Next(Context, this) , Prev(Context, this) , Ref(Context, InRef) , Value(Context, InValue)`

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace Verse`

### `Source/Runtime/CoreUObject/Public/VerseVM/VVMArray.h` (Public)


#### struct `Verse::VArray`  
`struct VArray : VArrayBase`  
_L18-69_
- inherits: `VArrayBase`
- L21 _public member_ `static TGlobalTrivialEmergentTypePtr<&StaticCppClassInfo> GlobalTrivialEmergentType;`
- L23 _public prototype_ `AUTORTFM_DISABLE static VArray& Concat(FRunningContext Context, VArrayBase& Lhs, VArrayBase& Rhs);`
- L25 _public function_ `AUTORTFM_DISABLE static VArray& New(FAllocationContext Context, uint32 NumValues, EArrayType ArrayType)`
- L30 _public function_ `AUTORTFM_DISABLE static VArray& New(FAllocationContext Context, std::initializer_list<VValue> InitList)`
- L36 _public function_ `template <typename InitIndexFunc, typename = std::enable_if_t<std::is_same_v<VValue, std::invoke_result_t<InitIndexFunc, uint32>>>> AUTORTFM_DISABLE static VArray& New(FAllocationContext Context, uint32 NumValues, InitIndexFunc&& InitFunc)`
- L41 _public function_ `AUTORTFM_DISABLE static VArray& New(FAllocationContext Context, FUtf8StringView String)`
- L46 _public function_ `AUTORTFM_DISABLE static VArray& New(FAllocationContext Context)`
- L51 _public member_ `static constexpr bool SerializeIdentity = false;`
- L52 _public function_ `AUTORTFM_DISABLE static void SerializeLayout(FAllocationContext Context, VArray*& This, FStructuredArchiveVisitor& Visitor)`
- L56 _private function_ `AUTORTFM_DISABLE VArray(FAllocationContext Context, uint32 InNumValues, EArrayType ArrayType) : VArrayBase(Context, InNumValues, InNumValues, ArrayType, &GlobalTrivialEmergentType.Get(Context))`
- L59 _private function_ `AUTORTFM_DISABLE VArray(FAllocationContext Context, std::initializer_list<VValue> InitList) : VArrayBase(Context, InitList, &GlobalTrivialEmergentType.Get(Context))`
- L63 _private function_ `template <typename InitIndexFunc, typename = std::enable_if_t<std::is_same_v<VValue, std::invoke_result_t<InitIndexFunc, uint32>>>> AUTORTFM_DISABLE VArray(FAllocationContext Context, uint32 InNumValues, InitIndexFunc&& InitFunc) : VArrayBase(Context, InNumValues, InitFunc, &GlobalTrivialEmergentType.Get(Context))`
- L67 _protected function_ `AUTORTFM_DISABLE VArray(FAllocationContext Context, FUtf8StringView String, VEmergentType* Type) : VArrayBase(Context, String, Type)`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace Verse`

### `Source/Runtime/CoreUObject/Public/VerseVM/VVMArrayBase.h` (Public)


#### enum `Verse::EArrayType`  
`enum class EArrayType : uint8`  
_L28-35_
- L30 _public enumerator_ `None`
- L31 _public enumerator_ `VValue`
- L32 _public enumerator_ `Int32`
- L33 _public enumerator_ `Char8`
- L34 _public enumerator_ `Char32`

#### struct `Verse::VBuffer`  
`struct VBuffer : TAux<void>`  
_L78-226_
- inherits: `TAux<void>`
- L91 _public prototype_ `VBuffer() = default;`
- L93 _public function_ `AUTORTFM_DISABLE VBuffer(FAllocationContext Context, uint32 NumValues, uint32 Capacity, EArrayType Type)`
- L111 _public function_ `VBuffer(FAllocationContext Context, uint32 NumValues, EArrayType Type) : VBuffer(Context, NumValues, NumValues, Type)`
- L116 _public function_ `Header* GetHeader() const`
- L121 _public function_ `void* GetDataStart()`
- L126 _public function_ `const void* GetDataStart() const`
- L131 _public function_ `EArrayType GetArrayType() const`
- L141 _public function_ `uint32 Num() const`
- L150 _public function_ `uint32 Capacity() const`
- L159 _public function_ `size_t ByteLength() const`
- L165 _public function_ `template <EWriteMode WriteMode = EWriteMode::Default> void SetNullTerminator()`
- L171 _public prototype_ `template <EWriteMode WriteMode = EWriteMode::Default> void SetVValue(FAllocationContext, uint32 Index, VValue);`
- L174 _public function_ `template <EWriteMode WriteMode = EWriteMode::Default> void SetInt32(uint32 Index, int32 Value)`
- L190 _public function_ `template <EWriteMode WriteMode = EWriteMode::Default> void SetChar(uint32 Index, UTF8CHAR Value)`
- L206 _public function_ `template <EWriteMode WriteMode> void SetChar32(uint32 Index, UTF32CHAR Value)`
- L222 _public function_ `template <typename T = void> T* GetData()`
- L225 _public function_ `template <typename T = void> const T* GetData() const`

#### struct `Verse::VBuffer::Header`  
`struct alignas(sizeof(VValue)) Header`  
_L82-89_
- desc: Note: We don't need to align char/char32 arrays this way. However, that will make accessing the data branch on Type. So it might never be worth doing.
- L84 _public member_ `uint32 NumValues;`
- L87 _public member_ `const uint32 Capacity;` — These are immutable per VBuffer. This means that if the GC sees a buffer with a particular type, it's type can't change while it's scanning the buffer.
- L88 _public member_ `const EArrayType Type;`

#### struct `Verse::VArrayBase`  
`struct VArrayBase : VHeapValue`  
_L230-614_
- inherits: `VHeapValue`
- L235 _protected member_ `TWriteBarrier<VBuffer> Buffer;`
- L238 _protected function_ `template <EWriteMode WriteMode = EWriteMode::Default> void SetBufferWithoutStoreBarrier(FAllocationContext Context, VBuffer NewBuffer)`
- L244 _protected function_ `template <EWriteMode WriteMode = EWriteMode::Default> void SetBufferWithStoreBarrier(FAllocationContext Context, VBuffer NewBuffer)`
- L250 _protected function_ `static EArrayType DetermineArrayType(VValue Value)`
- L267 _protected function_ `static EArrayType DetermineCombinedType(EArrayType A, EArrayType B)`
- L287 _protected function_ `VArrayBase(FAllocationContext Context, uint32 NumValues, uint32 Capacity, EArrayType ArrayType, VEmergentType* Type) : VHeapValue(Context, Type)`
- L310 _protected function_ `VArrayBase(FAllocationContext Context, std::initializer_list<VValue> InitList, VEmergentType* Type) : VHeapValue(Context, Type)`
- L328 _protected function_ `template <typename InitIndexFunc, typename = std::enable_if_t<std::is_same_v<VValue, std::invoke_result_t<InitIndexFunc, uint32>>>> VArrayBase(FAllocationContext Context, uint32 NumValues, InitIndexFunc&& InitFunc, VEmergentType* Type) : VHeapValue(Context, Type)`
- L367 _protected function_ `VArrayBase(FAllocationContext Context, FUtf8StringView String, VEmergentType* Type) : VHeapValue(Context, Type) , Buffer(Context, VBuffer(Context, String.Len(), EArrayType::Char8))`
- L379 _protected function_ `template <EWriteMode WriteMode = EWriteMode::Default> void SetNullTerminator()`
- L385 _public function_ `uint32 Num() const`
- L386 _public function_ `uint32 Capacity() const`
- L387 _public prototype_ `bool IsInBounds(uint32 Index) const;`
- L388 _public prototype_ `bool IsInBounds(const VInt& Index, const uint32 Bounds) const;`
- L389 _public prototype_ `VValue GetValue(uint32 Index);`
- L390 _public prototype_ `const VValue GetValue(uint32 Index) const;`
- L393 _public prototype_ `template <EWriteMode WriteMode = EWriteMode::Default> AUTORTFM_DISABLE void ConvertDataToVValues(FAllocationContext Context, uint32 NewCapacity);`
- L396 _public function_ `template <EWriteMode WriteMode = EWriteMode::Default> AUTORTFM_DISABLE void ConvertDataToVValues(FAllocationContext Context)`
- L402 _public prototype_ `template <EWriteMode WriteMode = EWriteMode::NonTransactional> AUTORTFM_DISABLE void SetValue(FAllocationContext, uint32 Index, VValue);`
- L403 _public prototype_ `AUTORTFM_DISABLE void SetValue(FAllocationContext Context, uint32 Index, VValue Value);`
- L404 _public prototype_ `AUTORTFM_DISABLE void SetValueTransactionally(FAllocationContext Context, uint32 Index, VValue Value);`
- L406 _public function_ `template <EWriteMode WriteMode = EWriteMode::Default> void SetVValue(FAllocationContext Context, uint32 Index, VValue Value)`
- L411 _public function_ `template <EWriteMode WriteMode = EWriteMode::Default> void SetInt32(uint32 Index, int32 Value)`
- L416 _public function_ `template <EWriteMode WriteMode = EWriteMode::Default> void SetChar(uint32 Index, UTF8CHAR Value)`
- L421 _public function_ `template <EWriteMode WriteMode = EWriteMode::Default> void SetChar32(uint32 Index, UTF32CHAR Value)`
- L426 _public function_ `void* GetData()`
- L427 _public function_ `const void* GetData() const`
- L430 _public function_ `template <typename T> T* GetData()`
- L432 _public function_ `template <typename T> const T* GetData() const`
- L434 _public function_ `EArrayType GetArrayType() const`
- L436 _public function_ `size_t ByteLength() const`
- L438 _public function_ `TOptional<FUtf8String> AsOptionalUtf8String() const`
- L465 _public function_ `FString AsString() const`
- L474 _public function_ `TOptional<FUtf8StringView> AsOptionalStringView() const`
- L487 _public function_ `FUtf8StringView AsStringView() const`
- L496 _public function_ `bool Equals(const FUtf8StringView String) const`
- L517 _public prototype_ `AUTORTFM_DISABLE ECompares EqualImpl(FAllocationContext Context, VCell* Other, const TFunction<void(::Verse::VValue, ::Verse::VValue)>& HandlePlaceholder);`
- L519 _public prototype_ `uint32 GetTypeHashImpl();`
- L521 _public prototype_ `AUTORTFM_DISABLE VValue MeltImpl(FAllocationContext Context);`
- L523 _public prototype_ `void VisitMembersImpl(FAllocationContext Context, FDebuggerVisitor& Visitor);`
- L525 _public prototype_ `AUTORTFM_DISABLE void AppendToStringImpl(FAllocationContext Context, FUtf8StringBuilderBase& Builder, EValueStringFormat Format, TSet<const void*>& VisitedObjects, uint32 RecursionDepth);`
- L526 _public prototype_ `AUTORTFM_DISABLE TSharedPtr<FJsonValue> ToJSONImpl(FRunningContext, EValueJSONFormat, TMap<const void*, EVisitState>& VisitedObjects, FToJsonCallback, uint32 RecursionDepth, FJsonObject* Defs);`
- L529 _public prototype_ `template <typename ArrayType> AUTORTFM_DISABLE static void SerializeLayoutImpl(FAllocationContext Context, ArrayType*& This, FStructuredArchiveVisitor& Visitor);`
- L530 _public prototype_ `AUTORTFM_DISABLE void SerializeImpl(FAllocationContext Context, FStructuredArchiveVisitor& Visitor);`
- L532 _public member_ `static constexpr bool InstancedCell = true;`
- L612 _public prototype_ `FConstIterator begin() const;`
- L613 _public prototype_ `FConstIterator end() const;`

#### class `Verse::VArrayBase::FConstIterator`  
`class FConstIterator`  
_L535-610_
- desc: C++ ranged-based iteration
- L545 _private member_ `EArrayType ArrayType;`
- L548 _public function_ `inline VValue operator*() const`
- L567 _public function_ `V_FORCEINLINE bool operator==(const FConstIterator& Rhs) const` — Don't need to worry about the data-type here as we are just doing pointer comparison
- L568 _public function_ `V_FORCEINLINE bool operator!=(const FConstIterator& Rhs) const`
- L570 _public function_ `inline FConstIterator& operator++()`
- L595 _private function_ `inline FConstIterator(const TWriteBarrier<VValue>* InCurrentValue) : Barrier(InCurrentValue) , ArrayType(EArrayType::VValue)`
- L598 _private function_ `inline FConstIterator(const int32* InCurrentValue) : Int32(InCurrentValue) , ArrayType(EArrayType::Int32)`
- L601 _private function_ `inline FConstIterator(const UTF8CHAR* InCurrentValue) : Char(InCurrentValue) , ArrayType(EArrayType::Char8)`
- L604 _private function_ `inline FConstIterator(const UTF32CHAR* InCurrentValue) : Char32(InCurrentValue) , ArrayType(EArrayType::Char32)`
- L607 _private function_ `inline FConstIterator(const void* InCurrentValue) : None(InCurrentValue) , ArrayType(EArrayType::None)`

#### union `Verse::VArrayBase::FConstIterator::(anonymous)`  
``  
_L538-544_

#### Free symbols / members of external scopes

- L21 _namespace_ `namespace Verse`
- L37 _function_ `inline const char* ArrayTypeToString(EArrayType ArrayType)` (scope `Verse`)
- L54 _function_ `inline bool IsNullTerminatedString(EArrayType Type)` (scope `Verse`)
- L59 _function_ `inline size_t ByteLength(EArrayType ArrayType)` (scope `Verse`)
- L539 _member_ `const TWriteBarrier<VValue>* Barrier;` (scope `Verse::VArrayBase::FConstIterator::__anon46327d5b010a`)
- L540 _member_ `const int32* Int32;` (scope `Verse::VArrayBase::FConstIterator::__anon46327d5b010a`)
- L541 _member_ `const UTF8CHAR* Char;` (scope `Verse::VArrayBase::FConstIterator::__anon46327d5b010a`)
- L542 _member_ `const UTF32CHAR* Char32;` (scope `Verse::VArrayBase::FConstIterator::__anon46327d5b010a`)
- L543 _member_ `const void* None;` (scope `Verse::VArrayBase::FConstIterator::__anon46327d5b010a`)

### `Source/Runtime/CoreUObject/Public/VerseVM/VVMAtomics.h` (Public)


#### Free symbols / members of external scopes

- L10 _namespace_ `namespace Verse`
- L16 _function_ `inline void CompilerFence()` (scope `Verse`) — Just a compiler fence. Has no effect on the hardware, but tells the compiler not to move things around this call. Should not affect the compiler's ability to do things like register allocation and code motion over pure operations.
- L29 _function_ `inline void ArmDmb()` (scope `Verse`) — Full memory fence. No accesses will float above this, and no accesses will sink below it.
- L36 _function_ `inline void ArmDmbSt()` (scope `Verse`) — Like the above, but only affects stores.
- L42 _function_ `inline void ArmIsb()` (scope `Verse`)
- L48 _function_ `inline void LoadLoadFence()` (scope `Verse`)
- L52 _function_ `inline void LoadStoreFence()` (scope `Verse`)
- L56 _function_ `inline void StoreLoadFence()` (scope `Verse`)
- L60 _function_ `inline void StoreStoreFence()` (scope `Verse`)
- L64 _function_ `inline void CrossModifyingCodeFence()` (scope `Verse`)
- L71 _function_ `inline void X86Ortop()` (scope `Verse`)
- L81 _function_ `inline void X86Cpuid()` (scope `Verse`)

### `Source/Runtime/CoreUObject/Public/VerseVM/VVMAux.h` (Public)


#### class `Verse::TAux`  
`template <typename T> class TAux`  
_L16-45_
- desc: This struct is just a pointer wrapper to be used when you want to allocate `Aux` memory. Aux memory is marked but not put on the MarkStack like VCells and we wrap Aux pointers in this so TWriteBarrier/TWeakBarrier can know to mark its `Ptr` as Aux.
- L19 _protected member_ `T* Ptr;`
- L22 _public function_ `TAux() : Ptr(nullptr)`
- L24 _public function_ `TAux(void* InPtr) : Ptr(static_cast<T*>(InPtr))`
- L27 _public function_ `T* GetPtr()`
- L29 _public function_ `explicit operator bool() const`
- L31 _public function_ `T& operator*()`
- L36 _public function_ `T* operator->()`
- L41 _public function_ `T& operator[](size_t Index)`
- L51 _protected member_ `void* Ptr;`
- L56 _public function_ `TAux(void* InPtr) : Ptr(InPtr)`
- L59 _public function_ `void* GetPtr()`

#### class `Verse::TAux`  
`template <> class TAux<void>`  
_L48-62_
- L19 _protected member_ `T* Ptr;`
- L22 _public function_ `TAux() : Ptr(nullptr)`
- L24 _public function_ `TAux(void* InPtr) : Ptr(static_cast<T*>(InPtr))`
- L27 _public function_ `T* GetPtr()`
- L29 _public function_ `explicit operator bool() const`
- L31 _public function_ `T& operator*()`
- L36 _public function_ `T* operator->()`
- L41 _public function_ `T& operator[](size_t Index)`
- L51 _protected member_ `void* Ptr;`
- L56 _public function_ `TAux(void* InPtr) : Ptr(InPtr)`
- L59 _public function_ `void* GetPtr()`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace Verse`
- L65 _variable_ `template <typename T> constexpr inline bool IsTAux = false;` (scope `Verse`)
- L68 _variable_ `template <typename T> constexpr inline bool IsTAux<TAux<T>> = true;` (scope `Verse`)
- L72 _variable_ `template <> constexpr inline bool IsTAux<VBuffer> = true;` (scope `Verse`)

### `Source/Runtime/CoreUObject/Public/VerseVM/VVMBitMap.h` (Public)


#### struct `Verse::VBitMap`  
`struct VBitMap`  
_L14-165_
- desc: Static bit-map that uses VInt as its storage (Bits are 0-indexed) Thus, its max size is currently `VHeapInt::MaxLength`
- L16 _public member_ `static const uint32 NumDigitBits = 32;`
- L18 _public member_ `TWriteBarrier<VInt> Storage;`
- L21 _public prototype_ `VBitMap() = default;` — one must call init after default construction before using other functionality otherwise one is likely to crash
- L23 _public function_ `AUTORTFM_DISABLE VBitMap(FAllocationContext Context, uint32 InSize, bool bSet = false)`
- L24 _public function_ `AUTORTFM_DISABLE VBitMap(FAllocationContext Context, const VBitMap& Other)`
- L36 _public function_ `AUTORTFM_DISABLE void Init(FAllocationContext Context, uint32 InSize, bool bSet = false)`
- L64 _public function_ `AUTORTFM_DISABLE bool Equals(FAllocationContext Context, const VBitMap& Other) const`
- L73 _public function_ `void SetBit(FAllocationContext Context, uint32 BitIndex)`
- L86 _public function_ `void UnsetBit(FAllocationContext Context, uint32 BitIndex)`
- L100 _public function_ `bool CheckBit(uint32 BitIndex)` — returns true if bit is set
- L113 _public function_ `void Clear(FAllocationContext Context)`
- L126 _public function_ `bool IsZero()`
- L131 _public function_ `uint64 Size()`
- L151 _private function_ `uint32& DigitRef(uint64 BitIndex)`
- L156 _private function_ `int32 AsInt32()`
- L161 _private function_ `bool IsInt32()`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace Verse`
- L145 _function_ `template <typename TVisitor> friend void Visit(TVisitor& Visitor, VBitMap& Value)` (scope `Verse`)
- L167 _function_ `inline uint32 GetTypeHash(const VBitMap& BitMap)` (scope `Verse`)

### `Source/Runtime/CoreUObject/Public/VerseVM/VVMBytecode.h` (Public)


#### enum `Verse::EOpcode`  
`enum class EOpcode : FOpcodeInt`  
_L28-35_
- L31 _public enumerator_ `VERSE_ENUM_OPS(VISIT_OP) #undef VISIT_OP OpcodeCount`

#### enum `Verse::EOperandRole`  
`enum class EOperandRole : uint8`  
_L130-136_
- desc: This _must_ match up with the codegen in `VerseVMBytecodeGenerator.cs`.
- L132 _public enumerator_ `Use`
- L133 _public enumerator_ `Immediate`
- L134 _public enumerator_ `ClobberDef`
- L135 _public enumerator_ `UnifyDef`

#### struct `Verse::FRegisterIndex`  
`struct FRegisterIndex`  
_L164-192_
- L166 _public member_ `static constexpr uint32 UNINITIALIZED = INT32_MAX;`
- L169 _public member_ `static constexpr uint32 SELF = 0;` — These are hardcoded register indices that we will always place the operands in by convention.
- L170 _public member_ `static constexpr uint32 SCOPE = 1;` — for `(super:)` and other generic captures in the future.
- L171 _public member_ `static constexpr uint32 PARAMETER_START = 2;`
- L174 _public member_ `uint32 Index{UNINITIALIZED};` — Unsigned, but must be less than INT32_MAX
- L176 _public function_ `explicit operator bool() const`
- L179 _public function_ `bool operator<(const FRegisterIndex& Other) const`
- L180 _public function_ `bool operator>=(const FRegisterIndex& Other) const`
- L181 _public function_ `FRegisterIndex& operator++()`

#### struct `Verse::FConstantIndex`  
`struct FConstantIndex`  
_L199-203_
- L202 _public member_ `uint32 Index;` — Unsigned, but must be less than or equal to INT32_MAX

#### struct `Verse::FValueOperand`  
`struct FValueOperand`  
_L205-257_
- L207 _public member_ `static constexpr uint32 UNINITIALIZED = INT32_MAX;`
- L218 _public function_ `FValueOperand() : Index(UNINITIALIZED)`
- L223 _public function_ `FValueOperand(FRegisterIndex Register) : Index(Register.Index)`
- L229 _public function_ `FValueOperand(FConstantIndex Constant) : Index`
- L236 _public function_ `V_FORCEINLINE bool IsRegister() const`
- L237 _public function_ `V_FORCEINLINE bool IsConstant() const`
- L238 _public function_ `V_FORCEINLINE explicit operator bool() const`
- L240 _public function_ `V_FORCEINLINE FRegisterIndex& AsRegister()`
- L246 _public function_ `V_FORCEINLINE FConstantIndex AsConstant() const`

#### union `Verse::FValueOperand::(anonymous)`  
``  
_L210-214_

#### struct `Verse::TOperandRange`  
`template <typename OperandType> struct TOperandRange`  
_L260-267_
- L262 _public member_ `int32 Index;`
- L263 _public member_ `int32 Num;`

#### struct `Verse::FOp`  
`struct alignas(OpAlignment) FOp`  
_L276-314_
- L278 _public member_ `EOpcode Opcode;`
- L280 _public function_ `explicit FOp(const EOpcode InOpcode) : Opcode(InOpcode)`
- L286 _public prototype_ `template <typename FunctionType> void ForEachReg(VProcedure& Procedure, FunctionType&& Function);` — Function should take as parameters (EOperandRole, FRegisterIndex) where FRegisterIndex can be a reference or a value. This vends the registers used in this FOp.
- L291 _public prototype_ `template <typename FunctionType> void ForEachJump(VProcedure&, FunctionType&& Function);` — Function should take as parameters (FLabelOffset, const TCHAR*) where FLabelOffset can be a reference or a value. This vends the jumps used in this FOp.
- L295 _private prototype_ `template <typename FunctionType> static void ForEachRegImpl(VProcedure&, FRegisterIndex& Register, FunctionType&& Function);`
- L298 _private prototype_ `template <typename FunctionType> static void ForEachRegImpl(VProcedure&, FValueOperand& Operand, FunctionType&& Function);`
- L301 _private prototype_ `template <typename CellType, typename FunctionType> static void ForEachRegImpl(VProcedure&, TWriteBarrier<CellType>&, FunctionType&&);`
- L304 _private prototype_ `template <typename FunctionType> static void ForEachRegImpl(VProcedure& Procedure, TOperandRange<FValueOperand> ValueOperands, FunctionType&& Function);`
- L307 _private prototype_ `template <typename CellType, typename FunctionType> static void ForEachRegImpl(VProcedure&, TOperandRange<TWriteBarrier<CellType>>, FunctionType&&);`
- L310 _private prototype_ `template <typename FunctionType> static void ForEachJumpImpl(VProcedure&, TOperandRange<FLabelOffset> LabelOffsets, const TCHAR* Name, FunctionType&&);`
- L313 _private prototype_ `template <typename FunctionType> static void ForEachJumpImpl(VProcedure&, FLabelOffset&, const TCHAR* Name, FunctionType&&);`

#### struct `Verse::FLabelOffset`  
`struct FLabelOffset`  
_L316-330_
- L318 _public member_ `int32 Offset;` — In bytes, relative to the address of this FLabelOffset
- L320 _public function_ `FOp* GetLabeledPC() const`

#### struct `Verse::FUnwindEdge`  
`struct FUnwindEdge`  
_L334-347_
- desc: A range of opcode bytes, with a target label for unwinding from calls within that range. VProcedure holds a sorted array of non-overlapping unwind edges.
- L336 _public member_ `int32 Begin;` — Exclusive
- L337 _public member_ `int32 End;` — Inclusive
- L338 _public member_ `FLabelOffset OnUnwind;`

#### struct `Verse::FNamedParam`  
`struct FNamedParam`  
_L350-369_
- desc: Mapping of a parameter name to its corresponding register. VProcedures hold an array of such mappings.
- L352 _public member_ `TWriteBarrier<VUniqueString> Name;`
- L353 _public member_ `FRegisterIndex Index;`
- L355 _public prototype_ `FNamedParam() = default;`
- L357 _public function_ `FNamedParam(FAccessContext Context, VUniqueString& InName, FRegisterIndex InIndex) : Name(Context, InName) , Index(InIndex)`

#### struct `Verse::FOpLocation`  
`struct FOpLocation`  
_L373-384_
- desc: Mapping from an opcode offset to a location.  VProcedure holds a sorted array of such mappings where an op's location is the latest entry with an equal or lesser offset.
- L375 _public member_ `int32 Begin;`
- L376 _public member_ `FLocation Location;`

#### struct `Verse::FFailureContextId`  
`struct FFailureContextId`  
_L388-402_
- L390 _public member_ `uint32 Id;`

#### Free symbols / members of external scopes

- L22 _namespace_ `namespace Verse`
- L26 _typedef_ `using FOpcodeInt = uint16_t;` (scope `Verse`)
- L30 _macro_ `#define VISIT_OP(Name) Name,`
- L37 _prototype_ `const char* ToString(EOpcode Opcode);` (scope `Verse`)
- L39 _function_ `inline bool IsBranch(EOpcode Opcode)` (scope `Verse`)
- L70 _function_ `inline bool IsTerminal(EOpcode Opcode)` (scope `Verse`)
- L84 _function_ `inline bool MightFallThrough(EOpcode Opcode)` (scope `Verse`)
- L138 _function_ `inline bool IsAnyDef(EOperandRole Role)` (scope `Verse`)
- L151 _function_ `inline bool IsAnyUse(EOperandRole Role)` (scope `Verse`)
- L177 _function_ `friend bool operator==(FRegisterIndex Left, FRegisterIndex Right)` (scope `Verse`)
- L178 _function_ `friend bool operator!=(FRegisterIndex Left, FRegisterIndex Right)` (scope `Verse`)
- L188 _function_ `template <typename TVisitor> friend void Visit(TVisitor& Visitor, FRegisterIndex& Value)` (scope `Verse`)
- L194 _function_ `inline uint32 GetTypeHash(FRegisterIndex Register)` (scope `Verse`)
- L211 _member_ `uint32 Index;` (scope `Verse::FValueOperand::__anonc449a310010a`)
- L212 _member_ `FRegisterIndex Register;` (scope `Verse::FValueOperand::__anonc449a310010a`)
- L213 _member_ `FConstantIndex Constant;` (scope `Verse::FValueOperand::__anonc449a310010a`)
- L253 _function_ `template <typename TVisitor> friend void Visit(TVisitor& Visitor, FValueOperand& Value)` (scope `Verse`)
- L266 _function_ `template <typename TVisitor> friend void Visit(TVisitor& Visitor, TOperandRange& Value)` (scope `Verse`)
- L272 _variable_ `constexpr uint8 OpAlignment = alignof(void*);` (scope `Verse`) — We align the bytecode stream to 8 bytes so we don't see tearing from the collector, and in the future other concurrent threads, when writing to a VValue/pointer sized entry.
- L326 _function_ `template <typename TVisitor> friend void Visit(TVisitor& Visitor, FLabelOffset& Value)` (scope `Verse`)
- L341 _function_ `template <typename TVisitor> friend void Visit(TVisitor& Visitor, FUnwindEdge& Value)` (scope `Verse`)
- L364 _function_ `template <typename TVisitor> friend void Visit(TVisitor& Visitor, FNamedParam& Value)` (scope `Verse`)
- L379 _function_ `template <typename TVisitor> friend void Visit(TVisitor& Visitor, FOpLocation& Value)` (scope `Verse`)
- L386 _prototype_ `const FLocation* GetLocation(FOpLocation* First, FOpLocation* Last, uint32 OpOffset);` (scope `Verse`)
- L392 _function_ `friend bool operator==(FFailureContextId Left, FFailureContextId Right)` (scope `Verse`)
- L397 _function_ `friend uint32 GetTypeHash(FFailureContextId Arg)` (scope `Verse`)

### `Source/Runtime/CoreUObject/Public/VerseVM/VVMBytecodeAnalysis.h` (Public)


#### struct `Verse::BytecodeAnalysis::FBasicBlock`  
`struct FBasicBlock`  
_L20-36_
- desc: A basic block is a list of bytecode instructions with a set of predecessors and successors.
- L22 _public member_ `FBlockIndex Index{std::numeric_limits<uint32>::max()};`
- L25 _public function_ `uint32 First() const` — These First/Last bytecodes are inclusive.
- L26 _public function_ `uint32 Last() const`
- L28 _public function_ `bool Contains(uint32 BytecodeOffset) const`
- L32 _public member_ `TArray<uint32> Bytecodes;` — For now, we store these just as offsets from the procedures start bytecode to make it easy to walk backwards. In the future we could compact this by storing it as offsets between instructions.
- L34 _public member_ `TArray<FBasicBlock*> Predecessors;`
- L35 _public member_ `TArray<FBasicBlock*> Successors;`

#### struct `Verse::BytecodeAnalysis::FFailureContext`  
`struct FFailureContext`  
_L38-49_
- L40 _public function_ `FFailureContext(FFailureContextId Id, FOp* FailurePC, FFailureContext* Parent) : Id(Id) , FailurePC(FailurePC) , Parent(Parent)`
- L46 _public member_ `FFailureContextId Id;`
- L47 _public member_ `FOp* FailurePC;`
- L48 _public member_ `FFailureContext* Parent;`

#### struct `Verse::BytecodeAnalysis::FTask`  
`struct FTask`  
_L51-58_
- L53 _public function_ `FTask(FOp* YieldPC) : YieldPC(YieldPC)`
- L57 _public member_ `FOp* YieldPC;`

#### struct `Verse::BytecodeAnalysis::FCFG`  
`struct FCFG`  
_L62-86_
- desc: A CFG is composed of a list of basic blocks and some metadata to tell us about which instructions belong in which tasks and/or failure contexts.
- L64 _public member_ `TArray<TUniquePtr<FBasicBlock>> Blocks;`
- L65 _public member_ `TArray<TUniquePtr<FFailureContext>> FailureContexts;`
- L70 _public member_ `TMap<uint32, FFailureContext*> BytecodeOffsetToFailureContext;` — Maps bytecode offset to innermost failure context. This is exclusive of both BeginFailureContext and EndFailureContext because those instructions can't jump to the FailurePC.
- L74 _public member_ `TMap<uint32, FTask> BytecodeOffsetToTask;` — Maps bytecode offset to innermost task. This is exclusive of BeginTask but inclusive of EndTask. The reason for this is BeginTask won't branch to YieldPC, but any bytecode within the range, including EndTask, might.
- L76 _public prototype_ `FBasicBlock& GetJumpTarget(uint32 BytecodeOffset);`
- L78 _public prototype_ `FFailureContext* FindCurrentFailureContext(uint32 BytecodeOffset);` — Returns the innermost failure context we're in, if we're in one.
- L80 _public prototype_ `FTask* FindCurrentTask(uint32 BytecodeOffset);` — Returns the innermost task we're in, if we're in one.
- L82 _public function_ `uint32 NumBlocks() const`

#### struct `Verse::BytecodeAnalysis::FLiveSet`  
`struct FLiveSet`  
_L91-138_
- desc: Bitset used to represent the live set of registers at a point in the program.
- L93 _public function_ `FLiveSet(uint32 Num)`
- L97 _public prototype_ `FLiveSet(const FLiveSet&) = default;`
- L100 _public function_ `bool Union(const FLiveSet& Other)` — Returns true if this changed.
- L113 _public function_ `bool operator==(const FLiveSet& Other) const`
- L117 _public function_ `bool operator!=(const FLiveSet& Other) const`
- L123 _public function_ `template <typename FunctionType> void ForEach(FunctionType&& Function) const`
- L131 _public function_ `FBitReference operator[](FRegisterIndex Register)`
- L137 _private member_ `FBitArray Live;`

#### struct `Verse::BytecodeAnalysis::FLiveness`  
`struct FLiveness`  
_L143-157_
- desc: This data structure caches liveness at basic block boundaries. To get the liveness in at an individual instruction, use FLocalCalc and walk the basic block backwards.
- L154 _public member_ `FCFG* CFG;`
- L155 _public member_ `TArray<FLiveSet> LiveOut;`
- L156 _public member_ `TArray<FLiveSet> LiveIn;`

#### struct `Verse::BytecodeAnalysis::FLiveness::FLocalCalc`  
`struct FLocalCalc`  
_L145-152_
- L147 _public prototype_ `FLocalCalc(FLiveness*, FBasicBlock*, VProcedure&);`
- L148 _public prototype_ `void Step(FOp*);`
- L149 _public member_ `FLiveSet Live;`
- L150 _public member_ `FLiveness* Liveness;`
- L151 _public member_ `VProcedure& Procedure;`

#### struct `Verse::BytecodeAnalysis::FLiveRange`  
`struct FLiveRange`  
_L159-212_
- L161 _public function_ `bool IsDead() const`
- L166 _public function_ `void Join(uint32 BytecodeOffset)`
- L172 _public function_ `void Join(FLiveRange Right)`
- L178 _public function_ `bool Contains(uint32 BytecodeOffset) const`
- L203 _public function_ `static FLiveRange Top()`
- L210 _public member_ `uint32 Begin{std::numeric_limits<uint32>::max()};` — Range is inclusive, [Begin, End], as bytecode offsets. If you're a bytecode in this range, it means this register is live-in to that bytecode instruction.
- L211 _public member_ `uint32 End{0};`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace Verse`
- L15 _namespace_ `namespace BytecodeAnalysis` (scope `Verse`)
- L17 _typedef_ `using FBlockIndex = uint32;` (scope `Verse::BytecodeAnalysis`)
- L88 _typedef_ `using FBitArray = TBitArray<>;` (scope `Verse::BytecodeAnalysis`)
- L183 _function_ `friend bool operator<(const FLiveRange& Left, const FLiveRange& Right)` (scope `Verse::BytecodeAnalysis`)
- L197 _function_ `template <typename TVisitor> friend void Visit(TVisitor& Visitor, FLiveRange& Value)` (scope `Verse::BytecodeAnalysis`)
- L214 _prototype_ `TUniquePtr<FCFG> MakeBytecodeCFG(VProcedure&);` (scope `Verse::BytecodeAnalysis`)
- L215 _prototype_ `TUniquePtr<FLiveness> ComputeBytecodeLiveness(FCFG&, VProcedure&);` (scope `Verse::BytecodeAnalysis`)
- L216 _prototype_ `TArray<FLiveRange> ComputeLiveRanges(VProcedure& Procedure, FLiveness& Liveness);` (scope `Verse::BytecodeAnalysis`)
- L217 _prototype_ `void AllocateRegisters(VProcedure&, FCFG&);` (scope `Verse::BytecodeAnalysis`)
- L218 _prototype_ `void AnalyzeAndTransformResets(VProcedure&, FCFG&);` (scope `Verse::BytecodeAnalysis`)

### `Source/Runtime/CoreUObject/Public/VerseVM/VVMBytecodeDispatcher.h` (Public)


#### Free symbols / members of external scopes

- L14 _namespace_ `namespace Verse`
- L17 _function_ `template <typename HandlerType> decltype(auto) DispatchOp(FOp& Op, HandlerType&& Handler)` (scope `Verse`)
- L21 _macro_ `#define VISIT_OP(Name) \`
- L33 _function_ `template <typename HandlerType> void DispatchOps(FOp* OpsBegin, FOp* OpsEnd, HandlerType&& Handler)` (scope `Verse`)
- L38 _function_ `Op = DispatchOp(*Op, [&](auto&& Op) -> FOp* { Handler(Op); return &Op + 1; });` (scope `Verse::DispatchOps`)
- L48 _function_ `template <typename HandlerType> void DispatchOps(VProcedure& Procedure, HandlerType&& Handler)` (scope `Verse`) — HandlerType can take in an FOp& or an auto& and descriminate on the actual subtype of FOp being passed in.

### `Source/Runtime/CoreUObject/Public/VerseVM/VVMBytecodeEmitter.h` (Public)


#### struct `Verse::FOpEmitter`  
`struct FOpEmitter`  
_L21-375_
- L34 _public function_ `FOpEmitter(FAllocationContext Context, VUniqueString& FilePath, VUniqueString& ProcedureName, uint32 NumPositionalParameters, uint32 NumNamedParameters) : FilePath(Context, FilePath) , ProcedureName(Context, ProcedureName) , NumRegisters(FRegisterIndex::PARAMETER_START + NumPositionalParameters + NumNamedParameters) , NumPositionalParameters(NumPositionalParameters) , NumNamedParameters(NumNamedParameters)`
- L45 _public function_ `VUniqueString& GetFilePath()`
- L50 _public function_ `VUniqueString& GetProcedureName()`
- L55 _public function_ `bool IsEmpty() const`
- L57 _public function_ `FConstantIndex AllocateConstant(VValue Constant)`
- L63 _public function_ `void BindConstant(FConstantIndex Constant, VValue Value)`
- L68 _public function_ `FRegisterIndex NoRegister()`
- L73 _public function_ `FRegisterIndex Self()`
- L78 _public function_ `FRegisterIndex Scope()`
- L83 _public function_ `FRegisterIndex Argument(uint32 ArgumentIndex)`
- L89 _public function_ `void AddRegisterName(FAccessContext Context, FRegisterIndex Index, VUniqueString& Name)`
- L94 _public function_ `FRegisterIndex AllocateRegisterNoReset()`
- L100 _public function_ `FRegisterIndex AllocateRegisterNoReset(FAccessContext Context, VUniqueString& Name)`
- L107 _public function_ `FRegisterIndex AllocateRegister(const FLocation& Location)`
- L114 _public function_ `FRegisterIndex AllocateRegister(FAccessContext Context, VUniqueString& Name, const FLocation& Location)`
- L121 _public function_ `FLabel AllocateLabel()`
- L127 _public function_ `void BindLabel(FLabel Label)`
- L132 _public function_ `FLabel AllocateAndBindLabel()`
- L139 _public function_ `uint32 GetOffsetForLabel(FLabel Label) const`
- L144 _public function_ `void EnterUnwindRegion(FLabel OnUnwind)`
- L161 _public function_ `void NoteUnwind()`
- L173 _public function_ `bool LeaveUnwindRegion()` — Returns true if any unwinds were recorded at this level of the stack.
- L191 _public prototype_ `AUTORTFM_DISABLE VProcedure& MakeProcedure(FAllocationContext Context);`
- L199 _public function_ `VERSE_ENUM_OPS(VISIT_OP) #undef VISIT_OP int32 Fail(const FLocation& Location)`
- L208 _public function_ `template <typename Opcode, typename... ArgumentTypes> int32 EmitOp(const FLocation& Location, ArgumentTypes&&... Arguments)`
- L226 _public function_ `inline uint32 GetNumPositionalParameters() const`
- L227 _public function_ `inline uint32 GetNumNamedParameters() const`
- L229 _public member_ `TArray<FNamedParam> NamedParameters;`
- L231 _public function_ `FFailureContextId GetNextFailureContextId()`
- L233 _public function_ `void DisableRegisterAllocation()`
- L236 _private member_ `TWriteBarrier<VUniqueString> FilePath;`
- L237 _private member_ `TWriteBarrier<VUniqueString> ProcedureName;`
- L238 _private member_ `uint32 NumRegisters;`
- L239 _private member_ `uint32 NumPositionalParameters;`
- L240 _private member_ `uint32 NumNamedParameters;`
- L241 _private member_ `TArray<VValue> Constants;`
- L242 _private member_ `TArray<uint8> OpBytes;`
- L243 _private member_ `TArray<FValueOperand> Operands;`
- L244 _private member_ `TArray<FLabel> Labels;`
- L245 _private member_ `TArray<FUnwindEdge> UnwindEdges;`
- L246 _private member_ `uint32 NextFailureContextId{0};`
- L247 _private member_ `bool bEnableRegisterAllocation{true};`
- L258 _private member_ `TArray<FUnwindRegion> UnwindStack;`
- L260 _private member_ `TArray<uint32> LabelOffsets;`
- L261 _private member_ `TArray<uint32> LabelOffsetOffsets;`
- L263 _private member_ `TArray<FOpLocation> OpLocations;`
- L266 _private member_ `TArray<FRegisterName> RegisterNames;` — Elements are not guaranteed to be unique and should not be relied on outside of debugging purposes.
- L268 _private member_ `TArray<uint32> ResetOffsets;`
- L271 _private function_ `template <typename ArgumentType> decltype(auto) CoerceOperand(ArgumentType&& Operand)`
- L277 _private function_ `template <typename CellType, typename AllocatorType> TOperandRange<TWriteBarrier<CellType>> CoerceOperand(TArray<TWriteBarrier<CellType>, AllocatorType> InOperands)`
- L295 _private function_ `template <typename AllocatorType> TOperandRange<FValueOperand> CoerceOperand(TArray<FValueOperand, AllocatorType> InOperands)`
- L302 _private function_ `FLabelOffset CoerceOperand(FLabel Label)`
- L310 _private function_ `template <typename AllocatorType> TOperandRange<FLabelOffset> CoerceOperand(TArray<FLabel, AllocatorType> InLabels)`
- L322 _private prototype_ `FLabelOffset CoerceOperand(FLabelOffset LabelOffset) = delete;` — Don't allow emitting label offsets directly.
- L323 _private prototype_ `FLabelOffset CoerceOperand(const TArrayView<FLabel>& LabelOffset) = delete;`
- L326 _private function_ `template <typename OpType> void RegisterJumpRelocation(OpType& Op)`
- L333 _private function_ `void RegisterLabelRelocation(FLabelOffset& LabelOffset)`
- L341 _private function_ `void RegisterLabelRelocation(TOperandRange<FLabelOffset>& InLabelOffsets)`
- L347 _private function_ `template <typename OpType> void MaybeNoteUnwind(OpType& Op)`
- L355 _private function_ `void MaybeNoteUnwind(FOpYield& Op)`
- L360 _private function_ `void MaybeNoteUnwind(FOpCall& Op)`
- L368 _private function_ `void MaybeNoteUnwind(FOpCallWithSelf& Op)`

#### struct `Verse::FOpEmitter::FLabel`  
`struct FLabel`  
_L23-32_
- L27 _private member_ `uint32 Index;`
- L28 _private function_ `FLabel(uint32 InIndex) : Index(InIndex)`

#### struct `Verse::FOpEmitter::FUnwindRegion`  
`struct FUnwindRegion`  
_L251-257_
- desc: An open region of the program with an associated unwind label. Nested regions wrap this label with their own. As code generation proceeds, this stack is flattened into a series of non-overlapping "unwind edges."
- L253 _public member_ `FLabel OnUnwind;`
- L254 _public member_ `int32 Begin;`
- L255 _public member_ `bool bHandlesUnwind;`
- L256 _public member_ `bool bLabelInvoked;`

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace Verse`
- L193 _macro_ `#define VISIT_OP(Name) \`
- L328 _function_ `Op.ForEachJump([&](auto& Label, const TCHAR* Name) { RegisterLabelRelocation(Label); });` (scope `Verse::FOpEmitter::RegisterJumpRelocation`)

### `Source/Runtime/CoreUObject/Public/VerseVM/VVMBytecodeOps.h` (Public)
_(no declarations extracted)_

### `Source/Runtime/CoreUObject/Public/VerseVM/VVMBytecodePrinting.h` (Public)


#### Free symbols / members of external scopes

- L11 _namespace_ `namespace Verse`
- L17 _prototype_ `AUTORTFM_DISABLE FString PrintProcedure(FAllocationContext, VProcedure& Function);` (scope `Verse`)

### `Source/Runtime/CoreUObject/Public/VerseVM/VVMBytecodesAndCaptures.h` (Public)
_(no declarations extracted)_

### `Source/Runtime/CoreUObject/Public/VerseVM/VVMCVars.h` (Public)


#### enum `Verse::BytecodeRegisterAllocation::EBytecodeRegisterAllocation`  
`enum EBytecodeRegisterAllocation : int32`  
_L25-30_
- L27 _public enumerator_ `Off = 0`
- L28 _public enumerator_ `SetLiveRanges = 1`
- L29 _public enumerator_ `AllocateRegisters = 2`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace Verse`
- L14 _prototype_ `const TArray<FString>& GetTraceFuncList();` (scope `Verse`)
- L16 _externvar_ `extern TAutoConsoleVariable<bool> CVarTrace;` (scope `Verse`)
- L17 _externvar_ `extern TAutoConsoleVariable<FString> CVarTraceFuncList;` (scope `Verse`)
- L18 _externvar_ `extern TAutoConsoleVariable<bool> CVarTraceSkipModuleTopLevel;` (scope `Verse`)
- L19 _externvar_ `extern TAutoConsoleVariable<bool> CVarTraceSingleStep;` (scope `Verse`)
- L20 _externvar_ `extern TAutoConsoleVariable<bool> CVarDumpBytecode;` (scope `Verse`)
- L21 _externvar_ `extern TAutoConsoleVariable<bool> CVarDumpBytecodeAsCFG;` (scope `Verse`)
- L22 _externvar_ `extern TAutoConsoleVariable<int32> CVarHeapMinimumTrigger;` (scope `Verse`)
- L23 _namespace_ `namespace BytecodeRegisterAllocation` (scope `Verse`)
- L32 _externvar_ `extern TAutoConsoleVariable<int32> CVarBytecodeRegisterAllocation;` (scope `Verse`)
- L33 _externvar_ `extern TAutoConsoleVariable<float> CVarUObjectProbability;` (scope `Verse`)
- L34 _externvar_ `extern FRandomStream RandomUObjectProbability;` (scope `Verse`)
- L35 _externvar_ `extern TAutoConsoleVariable<bool> CVarUObjectLeniency;` (scope `Verse`)
- L36 _externvar_ `extern TAutoConsoleVariable<bool> CVarEnableFastArrayAppend;` (scope `Verse`)
- L39 _externvar_ `extern TAutoConsoleVariable<bool> CVarUseDynamicSubobjectInstancing;` (scope `Verse`)
- L40 _externvar_ `extern TAutoConsoleVariable<bool> CVarEnableAssetClassRedirectors;` (scope `Verse`)
- L41 _externvar_ `extern TAutoConsoleVariable<bool> CVarFullyQualifyModulesInManifest;` (scope `Verse`)
- L42 _externvar_ `extern TAutoConsoleVariable<bool> CVarForceCompileFramework;` (scope `Verse`)
- L43 _externvar_ `extern TAutoConsoleVariable<bool> CVarBreakOnVerseRuntimeError;` (scope `Verse`)
- L44 _externvar_ `extern TAutoConsoleVariable<int32> CVarTruncatedCallstackMaxDepth;` (scope `Verse`)

### `Source/Runtime/CoreUObject/Public/VerseVM/VVMCaptureSwitch.h` (Public)
_(no declarations extracted)_

### `Source/Runtime/CoreUObject/Public/VerseVM/VVMCell.h` (Public)


#### struct `Verse::Private::VCellMutexParams`  
`struct VCellMutexParams`  
_L36-40_
- L38 _public member_ `static constexpr uint8 IsLockedFlag = 1;`
- L39 _public member_ `static constexpr uint8 MayHaveWaitingLockFlag = 2;`

#### struct `Verse::VCell`  
`struct VCell`  
_L53-286_
- desc: Outside of the Verse VM and CoreUObject, most code should not need to interact with VCells directly. Instead, there are higher level APIs for interacting with Verse values from C++.
- L57 _public member_ `static constexpr uint8 GCDataIsWeakKeyBit = 1;` — If set in GCData, means that this object has an object in the libpas verse_heap client_data for the verse_heap_page_header corresponding to this object. This just means that during marking, we want to process that data structure.
- L59 _public prototype_ `DECLARE_BASE_VCPPCLASSINFO();`
- L63 _public member_ `uint32 EmergentTypeOffset;` — The header word of a VCell is the offset of an emergent type and 4 extra bytes (one reserved for GC)
- L64 _public member_ `std::atomic<uint8> GCData{0};`
- L66 _public member_ `mutable std::atomic<uint8> Mutex{0};` — The first two bits of this are used by TIntrusiveMutexes in VCell subclasses.
- L68 _public member_ `static constexpr uint8 DeeplyMutableTag = 1;` — The first bit of Misc2 being set indicates this cell is deeply mutable.
- L73 _public member_ `static constexpr uint8 MeltedNativeStructTag = 2;` — The second bit of Misc2 being set indicates a melted VNativeStruct. Note: This is being used by VNativeStructs to avoid creating Ref's for all of their fields when melting which is what Verse semantics prescribe. Instead, we check this when loading fields from a VNativeStruct and create Refs as needed.
- L84 _public prototype_ `VCell(const VCell&) = delete;`
- L85 _public prototype_ `VCell& operator=(const VCell&) = delete;`
- L87 _public prototype_ `VCell(FAllocationContext Context, const VEmergentType* EmergentType);`
- L89 _public prototype_ `VEmergentType* GetEmergentType() const;`
- L90 _public prototype_ `const VCppClassInfo* GetCppClassInfo() const;`
- L98 _public prototype_ `void VisitReferences(FMarkStackVisitor& Visitor);` — FIXME: In the future maybe these will take a FRunningContext or FAccessContext rather than the MarkStack or nothing. That's because: 1) Nothing wrong with saying that the GC threads allocate or run arbitrary code if the GC is concurrent by design. Like, maybe we'll want GC-time hash-consing. 2) In a parallel GC, we'll probably want to just reuse the fact that each context has a MarkStack.
- L99 _public prototype_ `void VisitReferences(FAbstractVisitor& Visitor);`
- L100 _public prototype_ `void ConductCensus();`
- L101 _public prototype_ `void RunDestructor();`
- L103 _public prototype_ `void AddRef(FAccessContext Context);` — Temporarily prevent this cell from being GC'ed
- L104 _public prototype_ `void ReleaseRef();`
- L106 _public prototype_ `AUTORTFM_DISABLE ECompares Equal(FAllocationContext Context, VCell* Other, const TFunction<void(::Verse::VValue, ::Verse::VValue)>& HandlePlaceholder);`
- L107 _public prototype_ `AUTORTFM_DISABLE VValue Melt(FAllocationContext Context);`
- L108 _public prototype_ `AUTORTFM_DISABLE FOpResult Freeze(FAllocationContext Context, VTask* Task);`
- L109 _public prototype_ `AUTORTFM_DISABLE bool Subsumes(FAllocationContext Context, VValue);`
- L110 _public prototype_ `AUTORTFM_DISABLE void VisitMembers(FAllocationContext Context, FDebuggerVisitor& Visitor);`
- L111 _public prototype_ `AUTORTFM_DISABLE void AppendToString(FAllocationContext Context, FUtf8StringBuilderBase& Builder, EValueStringFormat Format, TSet<const void*>& VisitedObjects, uint32 RecursionDepth = 0);`
- L112 _public prototype_ `AUTORTFM_DISABLE FUtf8String ToString(FAllocationContext Context, EValueStringFormat Format, uint32 RecursionDepth = 0);`
- L113 _public prototype_ `AUTORTFM_DISABLE TSharedPtr<FJsonValue> ToJSON(FRunningContext, EValueJSONFormat, TMap<const void*, EVisitState>& VisitedObjects, FToJsonCallback, uint32 RecursionDepth = 0, FJsonObject* Defs = nullptr);`
- L114 _public prototype_ `AUTORTFM_DISABLE VValue FromJSON(FRunningContext, const FJsonValue&, EValueJSONFormat, FFromJsonCallback);`
- L115 _public prototype_ `AUTORTFM_DISABLE static void SerializeLayout(FAllocationContext Context, const VCppClassInfo* CppClassInfo, VCell*& This, FArchive& Ar);`
- L116 _public prototype_ `AUTORTFM_DISABLE void Serialize(FAllocationContext Context, FStructuredArchiveVisitor& Visitor);`
- L117 _public prototype_ `AUTORTFM_DISABLE void Serialize(FAllocationContext Context, FArchive& Ar);`
- L119 _public function_ `bool IsDeeplyMutable() const`
- L120 _public function_ `bool SetIsDeeplyMutable()`
- L122 _public function_ `bool IsMeltedNativeStruct() const`
- L123 _public function_ `bool SetIsMeltedNativeStruct()`
- L125 _public prototype_ `static void InitializeGlobals(FAllocationContext Context);`
- L143 _private prototype_ `template <typename TVisitor> void VisitReferencesImpl(TVisitor&);` — Use this if your cell subtype has any outgoing strong references.  It is used by both the GC system and the abstract visitor to collect strong references. Note that this function will run concurrently to the mutator (this function is being called in some collector thread while the VM's other threads are calling other methods on your object) and in parallel (the collector will run multiple threads calling this function). However, you're guaranteed that this function will only be called once per object per collection cycle; i.e. the GC will never call this function simultaneously for the same object. It is defined implicitly by DECLARE_DERIVED_VCPPCLASSINFO, and so you must either implement it or use the DEFINE_TRIVIAL_VISIT_REFERENCES macro to explicitly define a trivial implementation. Visit outgoing references for self. Don't call visit on your super class, or visit references defined by your super class.
- L145 _private member_ `static TNeverDestroyed<TOptional<FStrongCellRegistry>> GlobalStrongCellRegistry;`
- L165 _protected prototype_ `void ConductCensusImpl();` — Override this if your cell subtype has any outgoing weak references. Call ClearWeakDuringCensus on those pointers in this function. Note that this function may run concurrently to the mutator, in parallel, or from within the mutator's allocation slow paths. This means that this function cannot allocate, since it may be called while internal allocator locks are held. It may also be called while mutator locks are held, if those locks are held across allocations. So, this function cannot acquire locks, unless those locks are never held while either handshaking or allocating. This function is called exactly once per collection cycle for any marked objects that belong to the CensusSpace or the DestructorAndCensusSpace. This function is guaranteed to be called only after all marking is finished, so you can use FHeap::IsMarked and that will tell you if the object survived the collection or not. Because census runs before destruction and sweep, you're also guaranteed that any pointed-to dead objects are still fully intact and usable. It's not meaningful to override this function unless the cell is allocated from the CensusSpace or the DestructorAndCensusSpace.
- L168 _protected prototype_ `ECompares EqualImpl(FAllocationContext Context, VCell* Other, const TFunction<void(::Verse::VValue, ::Verse::VValue)>& HandlePlaceholder);` — Override this if your cell requries deep comparison (simple comparisons should be inlined in VValue::Equal).
- L171 _protected prototype_ `uint32 GetTypeHashImpl();` — Override this if your cell subtype requires a deep hash.
- L179 _protected prototype_ `VValue MeltImpl(FAllocationContext Context);` — Override this if your cell requires deep copying. Note: This also acts as "Clone"  for mutable types which is defined as 'Freeze->Melt'. We can ignore the possibility that the skipped 'freeze' could error on placeholders as the mutable data we are operating on requires all values be concrete on creation or we would've suspended.
- L182 _protected prototype_ `FOpResult FreezeImpl(FAllocationContext Context, VTask* Task);` — Override this if your cell is a mutable representation and requires deep copying.
- L185 _protected prototype_ `bool SubsumesImpl(FAllocationContext, VValue);` — Override this if your cell represents a type that can be used in casts.
- L188 _protected prototype_ `void VisitMembersImpl(FAllocationContext, FDebuggerVisitor&);` — Override this if your cell has members that should be visible in the debugger.
- L191 _protected prototype_ `AUTORTFM_DISABLE void AppendToStringImpl(FAllocationContext Context, FUtf8StringBuilderBase& Builder, EValueStringFormat Format, TSet<const void*>& VisitedObjects, uint32 RecursionDepth);` — Override this to customize how your cell is displayed, in the debugger and elsewhere.
- L195 _protected prototype_ `TSharedPtr<FJsonValue> ToJSONImpl(FRunningContext, EValueJSONFormat, TMap<const void*, EVisitState>& VisitedObjects, FToJsonCallback, uint32 RecursionDepth, FJsonObject* Defs);` — Override this to customize how your cell is printed for JSON formats [Analytics, Persistence, Persona] Note: This runs in the closed! So any allocations / most Ref accesses will require an AutoRTFM::Open
- L199 _protected prototype_ `VValue FromJSONImpl(FRunningContext, const FJsonValue&, EValueJSONFormat, FFromJsonCallback);` — Override this if you are a supported Persistence/Persona type TODO: Make a new vtable for VType which inherits our VCell vtable and appends this to it
- L210 _protected member_ `static constexpr bool SerializeIdentity = true;`
- L213 _protected function_ `template <typename CellType> AUTORTFM_DISABLE static void SerializeLayout(FAllocationContext, CellType*&, FStructuredArchiveVisitor&)`
- L218 _protected prototype_ `void SerializeImpl(FAllocationContext, FStructuredArchiveVisitor&);`
- L223 _protected member_ `static constexpr bool InstancedCell = false;` — True if cells of this type should be cloned by APIs like InstanceSubobjects or StaticDuplicateObject. May be necessary because the cell is mutable, or because it may point to other objects that should be cloned. This will need to be made more precise in the future, e.g. via `own`.
- L226 _protected function_ `VCell() : EmergentTypeOffset(0)` — VCell() and SetEmergentType(..) are used during setup when creating some cyclic dependencies.
- L233 _public prototype_ `void SetEmergentType(FAccessContext, VEmergentType* EmergentType);`
- L234 _public prototype_ `void SetEmergentType(FAccessContext, uint32 Offset);`
- L255 _public prototype_ `~VCell() = default;` — Override this if your cell subtype has a destructor. Note that this function may run concurrently to the mutator, in parallel, or from within the mutator's allocation slow paths. This means that this function cannot allocate, since it may be called while internal allocator locks are held. It may also be called while mutator locks are held, if those locks are held across allocations. So, this function cannot acquire locks, unless those locks are never held while either handshaking or allocating. This function is called exactly once per collection cycle for any unmarked objects that belong to the DestructorSpace or the DestructorAndCensusSpace. This function is guaranteed to be called only after all marking and census are finished. Because census doesn't cover unmarked objects, you will see nonnull weak references to dead objects. Because destruction runs before sweep, you're also guaranteed that any pointed-to dead objects are still fully intact and usable. It's not meaningful to override this function unless the cell is allocated from the DestructorSpace or the DestructorAndCensusSpace. Note: You must override this if your cell has external memory to report swept external bytes during destruction.
- L258 _public prototype_ `template <typename CastType> bool IsA() const;`
- L261 _public prototype_ `template <typename CastType> const CastType& StaticCast() const;`
- L264 _public prototype_ `template <typename CastType> CastType& StaticCast();`
- L267 _public prototype_ `template <typename CastType> CastType* DynamicCast();`
- L270 _public prototype_ `template <typename CastType> CastType* DynamicCast() const;`
- L272 _public prototype_ `FString DebugName() const;`
- L278 _public prototype_ `void AddWeakMapping(VCell* Map, VCell* Value);` — Inform the GC that this cell is now a key in the following weak map and it keeps the given value alive. For sound concurrent GC handling of weak maps, both the map and the key must know about the mapping. Hence, every cell in the VVM has the secret ability to become a weak key. This costs just one bit per object if unused. It costs horrors and nightmares if used (but at least the terror is O(1)ish).
- L279 _public prototype_ `void RemoveWeakMapping(VCell* Map);`
- L285 _public prototype_ `bool HasWeakMappings();` — This function is a test-only function because it has a very limited kind of meaning. Requesting the size (or checking the emptiness) of a weap map (including a "transposed" weak map, like the weak key map) gives a kind of upper bound: it means that the map has at most this many entries. But we cannot tell you which of those entries are real. When you query them, you are likely to find fewer entries.

#### union `Verse::VCell::(anonymous)`  
``  
_L75-82_

#### struct `Verse::VCell::__anon17a11b21010a::(anonymous)`  
``  
_L77-80_

#### struct `Verse::VHeapValue`  
`struct VHeapValue : VCell`  
_L296-301_
- inherits: `VCell`
- desc: `VHeapValue` represents Verse-facing values, while `VCell` represents VM-internal structures. To be or not to be ... Keep it here for now.

#### Free symbols / members of external scopes

- L22 _namespace_ `namespace Verse`
- L34 _namespace_ `namespace Private` (scope `Verse`)
- L78 _member_ `uint8_t Misc2;` (scope `Verse::VCell::__anon17a11b21010a::__anon17a11b210208`)
- L79 _member_ `uint8_t Misc3;` (scope `Verse::VCell::__anon17a11b21010a::__anon17a11b210208`)
- L81 _member_ `uint16 Misc2And3{0};` (scope `Verse::VCell::__anon17a11b21010a`)
- L291 _typedef_ `using FCellUniqueLock = UE::TIntrusiveUniqueLock<Private::VCellMutexParams>;` (scope `Verse`) — Each VCell contains an internal mutex byte. `FCellUniqueLock` locks that mutex within a scope.

### `Source/Runtime/CoreUObject/Public/VerseVM/VVMClass.h` (Public)


#### struct `Verse::FEmergentTypesCacheKeyFuncs`  
`struct FEmergentTypesCacheKeyFuncs : TDefaultMapKeyFuncs<TWriteBarrier<VUniqueStringSet>, TWriteBarrier<VEmergentType>, false>`  
_L40-47_
- inherits: `TDefaultMapKeyFuncs<TWriteBarrier<VUniqueStringSet>,TWriteBarrier<VEmergentType>,false>`
- desc: This provides a custom comparison that allows us to do pointer-based compares of each unique string set, rather than hash-based comparisons.
- L43 _public prototype_ `static bool Matches(KeyInitType A, KeyInitType B);`
- L44 _public prototype_ `static bool Matches(KeyInitType A, const VUniqueStringSet& B);`
- L45 _public prototype_ `static uint32 GetKeyHash(KeyInitType Key);`
- L46 _public prototype_ `static uint32 GetKeyHash(const VUniqueStringSet& Key);`

#### enum `Verse::EArchetypeEntryFlags`  
`enum class EArchetypeEntryFlags : uint8`  
_L49-66_
- L51 _public enumerator_ `None = 0`
- L53 _public enumerator_ `NativeRepresentation = 1 << 0` — If the entry in the archetype requires a native property type.
- L55 _public enumerator_ `HasDefaultValueExpression = 1 << 1` — If the entry in the archetype will be default-initialized by an expression.
- L57 _public enumerator_ `Instanced = 1 << 2` — If the field's FProperty should have the CPF_InstancedReference flag.
- L59 _public enumerator_ `UseCRCName = 1 << 3` — If the field's FProperty for this used the entry's qualified name
- L61 _public enumerator_ `Predicts = 1 << 4` — If the field has the <predicts> attribute (for data) or effect (for functions)
- L63 _public enumerator_ `Var = 1 << 5` — If the field is a var
- L65 _public enumerator_ `AccessibleFromEngineGameplay = 1 << 6` — If the field is accessible from engine gameplay systems

#### struct `Verse::VArchetype`  
`struct VArchetype : VCell`  
_L70-148_
- inherits: `VCell`
- desc: Represents the sequence of fields in a class body, a constructor function or an archetype instantiation.
- L73 _public member_ `static TGlobalTrivialEmergentTypePtr<&StaticCppClassInfo> GlobalTrivialEmergentType;`
- L115 _public member_ `VRestValue Class{0};` — The class that this archetype initializes. Not set for operands of NewObject. If `this == Class->Archetype`, then this archetype describes the class body itself. This is a VRestValue because it can be non-concrete during module top-level initialization.
- L121 _public member_ `VRestValue NextArchetype{0};` — The remaining chain of archetypes that this archetype overrides. For operands of NewObject, only set if the archetype calls a constructor function. If this archetype describes a class body, then this is the archetype of the superclass. This is a VRestValue because it can be non-concrete during module top-level initialization.
- L124 _public member_ `uint32 NumEntries;` — The number of entries in this constructor object.
- L125 _public member_ `VEntry Entries[];`
- L127 _public prototype_ `AUTORTFM_DISABLE static VArchetype& New(FAllocationContext Context, VValue InNextArchetype, const TArray<VEntry>& InEntries);`
- L129 _public prototype_ `AUTORTFM_DISABLE void AppendToStringImpl(FAllocationContext Context, FUtf8StringBuilderBase& Builder, EValueStringFormat Format, TSet<const void*>& VisitedObjects, uint32 RecursionDepth);`
- L131 _public prototype_ `AUTORTFM_DISABLE static void SerializeLayout(FAllocationContext Context, VArchetype*& This, FStructuredArchiveVisitor& Visitor);`
- L132 _public prototype_ `AUTORTFM_DISABLE void SerializeImpl(FAllocationContext Context, FStructuredArchiveVisitor& Visitor);`
- L135 _public prototype_ `AUTORTFM_DISABLE VValue LoadFunction(FAllocationContext Context, VUniqueString& FieldName, VValue SelfObject);` — This loads the method that matches the given name. If it does not exist, returns `VValue()`.
- L138 _private function_ `static VArchetype& NewUninitialized(FAllocationContext Context, const uint32 InNumEntries)`
- L144 _private prototype_ `VArchetype(FAllocationContext Context, VValue InNextArchetype, const TArray<VEntry>& InEntries);`
- L145 _private prototype_ `VArchetype(FAllocationContext Context, const uint32 InNumEntries);`

#### struct `Verse::VArchetype::VEntry`  
`struct VEntry`  
_L75-110_
- L77 _public prototype_ `static VEntry Constant(FAllocationContext Context, VUniqueString& InQualifiedField, VValue InType, VValue InValue);`
- L78 _public prototype_ `static VEntry Field(FAllocationContext Context, VUniqueString& InQualifiedField, VValue InType);`
- L79 _public prototype_ `static VEntry InitializedField(FAllocationContext Context, VUniqueString& InQualifiedField, VValue InType);`
- L81 _public prototype_ `static VEntry ObjectField(FAllocationContext Context, VUniqueString& InQualifiedField);`
- L83 _public prototype_ `bool IsConstant() const;`
- L84 _public prototype_ `bool IsNativeRepresentation() const;`
- L85 _public prototype_ `bool UseCRCName() const;`
- L86 _public prototype_ `bool HasDefaultValueExpression() const;`
- L87 _public prototype_ `bool IsInstanced() const;`
- L88 _public prototype_ `bool IsPredicts() const;`
- L89 _public prototype_ `bool IsVar() const;`
- L92 _public prototype_ `bool IsMethod() const;` — Checks if the entry refers to a method that is unbound (i.e. has no `Self`).
- L94 _public member_ `TWriteBarrier<VUniqueString> Name;`
- L97 _public member_ `TWriteBarrier<VValue> Type;` — For data members, the declared type.
- L107 _public member_ `TWriteBarrier<VValue> Value;` — `Value` should be one of the following: - An uninitialized `VValue`, for a field initializer (regardless of whether or not the field is actually uninitialized). - A constant `VValue` representing a default field value. (This may be a `VFunction` without the `Self` member for methods, since they will bind `Self` lazily).
- L109 _public member_ `EArchetypeEntryFlags Flags;`

#### struct `Verse::VClass`  
`struct VClass : VNamedType`  
_L150-330_
- inherits: `VNamedType`
- L153 _public member_ `static TGlobalTrivialEmergentTypePtr<&StaticCppClassInfo> GlobalTrivialEmergentType;`
- L179 _public function_ `EKind GetKind() const`
- L180 _public function_ `bool IsStruct() const`
- L181 _public function_ `bool IsInterface() const`
- L183 _public function_ `bool IsNativeRepresentation() const`
- L184 _public function_ `bool IsNativeStruct() const`
- L185 _public function_ `bool IsNativeStructWithObjectReferences() const`
- L186 _public function_ `bool IsPredicts() const`
- L187 _public function_ `bool IsPersonaConstructible() const`
- L188 _public function_ `bool IsUnique() const`
- L189 _public function_ `bool IsEpicInternal() const`
- L191 _public function_ `TArrayView<TWriteBarrier<VClass>> GetInherited()`
- L192 _public function_ `VArchetype& GetArchetype() const`
- L193 _public function_ `VFunction& GetConstructor() const`
- L194 _public function_ `VFunction& GetBlocks() const`
- L197 _public prototype_ `AUTORTFM_DISABLE VValueObject& NewVObject(FAllocationContext Context, VArchetype& InArchetype);` — Allocates a new `VValueObject` that has enough space to accommodate the entries in the archetype.
- L199 _public prototype_ `AUTORTFM_DISABLE VValueObject& NewVObjectOfEmergentType(FAllocationContext Context, VEmergentType& EmergentType);` — Allocates a new `VValueObject` of a known emergent type.
- L201 _public prototype_ `AUTORTFM_DISABLE VNativeConstructorWrapper& NewNativeStruct(FAllocationContext Context);`
- L205 _public prototype_ `template <class CppStructType> VNativeStruct& NewNativeStruct(FAllocationContext Context, CppStructType&& Struct);` — Allocate a new VNativeStruct and move an existing struct into it
- L208 _public prototype_ `AUTORTFM_DISABLE FOpResult NewUObject(FAllocationContext Context, VArchetype& InArchetype);` — Allocate a new `UObject`, wrapped in a data structure that tracks which fields have been initialized.
- L210 _public prototype_ `AUTORTFM_DISABLE VEmergentType& GetOrCreateEmergentTypeForVObject(FAllocationContext Context, VCppClassInfo* CppClassInfo, VArchetype& InArchetype);`
- L211 _public prototype_ `AUTORTFM_DISABLE VEmergentType& GetOrCreateEmergentTypeForNativeStruct(FAllocationContext Context);`
- L212 _public prototype_ `AUTORTFM_DISABLE VEmergentType& GetOrCreateEmergentTypeForNativeConstructorWrapper(FAllocationContext Context);`
- L213 _public prototype_ `UStruct* GetOrCreateNativeType(FAllocationContext Context);`
- L231 _public prototype_ `static VClass& New( FAllocationContext Context, VPackage* InPackageScope, VArray* InRelativePath, VArray* InClassName, VArray* InAttributeIndices, VArray* InAttributes, VValue InImportStruct, bool bNativeBound, EKind InKind, EFlags InFlags, const TArray<VClass*>& InInherited, VArchetype& InArchetype, VProcedure& InConstructor, VProcedure* InBlocks = nullptr);` — Creates a new class. @param InPackageScope        Containing package or null. @param InRelativePath        Path within containing package. @param InClassName           Unqualified name. @param InAttributeIndices @param InAttributes @param InImportStruct        The Unreal class/struct that is being reflected by this Verse VM type. @param bNativeBound @param InKind                Class, Struct or Interface. @param InFlags @param InInherited           An array of base classes, in order of inheritance. @param InArchetype           The sequence of fields and blocks in the class body. @param InConstructor         The class body's bytecode that initializes its fields.
- L247 _public prototype_ `bool SubsumesImpl(FAllocationContext, VValue);`
- L249 _public prototype_ `AUTORTFM_DISABLE static void SerializeLayout(FAllocationContext Context, VClass*& This, FStructuredArchiveVisitor& Visitor);`
- L250 _public prototype_ `AUTORTFM_DISABLE void SerializeImpl(FAllocationContext Context, FStructuredArchiveVisitor& Visitor);`
- L252 _public prototype_ `AUTORTFM_DISABLE TSharedPtr<FJsonValue> ToJSONImpl(FRunningContext, EValueJSONFormat, TMap<const void*, EVisitState>& VisitedObjects, FToJsonCallback, uint32 RecursionDepth, FJsonObject* Defs);`
- L253 _public prototype_ `AUTORTFM_DISABLE VValue FromJSONImpl(FRunningContext, const FJsonValue&, EValueJSONFormat, FFromJsonCallback);`
- L256 _private prototype_ `AUTORTFM_DISABLE VClass( FAllocationContext Context, VPackage* InPackageScope, VArray* InRelativePath, VArray* InClassName, VArray* InAttributeIndices, VArray* InAttributes, VValue InImportStruct, bool bInNativeBound, EKind InKind, EFlags InFlags, const TArray<VClass*>& InInherited, VArchetype& InArchetype, VProcedure& InConstructor, VProcedure* InBlocks);`
- L272 _private prototype_ `AUTORTFM_DISABLE VClass(FAllocationContext Context, int32 NumInherited);`
- L276 _private prototype_ `AUTORTFM_DISABLE static void WalkArchetypeFields( FAllocationContext Context, VArchetype& InArchetype, VClass& InClass, VArchetype* InNextArchetype, int32& BaseIndex, TFunction<void(int32&)> WalkSuper, TFunction<void(VArchetype::VEntry&, int32, VClass&)> FieldCallbackProc);` — Walks a chain of archetypes recursively, calling FieldCallbackProc for each entry. BaseIndex is added to the entry indices passed to FieldCallbackProc; initial callers probably just want 0.
- L286 _private prototype_ `AUTORTFM_DISABLE FOpResult BindNativeClass(FAllocationContext Context, bool bImported);` — Creates an associated UClass or UScriptStruct for this VClass
- L288 _private prototype_ `void CommonPrepare(FAllocationContext Context, FInitOrValidateUStruct& InitOrValidate, UStruct* Type);`
- L289 _private prototype_ `void Prepare(FAllocationContext Context, FInitOrValidateUVerseStruct& InitOrValidate, UVerseStruct* Type);`
- L290 _private prototype_ `void Prepare(FAllocationContext Context, FInitOrValidateUVerseClass& InitOrValidate, UVerseClass* Type);`
- L291 _private prototype_ `static void LinkSuperInterface(FAllocationContext Context, FInitOrValidateUVerseClass& InitOrValidate, VClass& SuperInterface, EAddInterfaceType InterfaceType);`
- L293 _private prototype_ `AUTORTFM_DISABLE VShape* CreateShapeForUStruct( FAllocationContext Context, TFunction<FProperty*(VArchetype::VEntry&, int32)>&& CreateProperty, TFunction<UFunction*(VArchetype::VEntry&)>&& CreateFunction);`
- L297 _private prototype_ `AUTORTFM_DISABLE VShape* CreateShapeForExistingUStruct(FAllocationContext Context);`
- L298 _private prototype_ `UFunction* MaybeCreateUFunctionForCallee(Verse::FAllocationContext Context, VFunction& Callee);`
- L300 _private prototype_ `AUTORTFM_DISABLE FOpResult ConstructNativeDefaultObject(FRunningContext Context);`
- L301 _private prototype_ `AUTORTFM_DISABLE static FOpResult InitSuperDefaultObject(FRunningContext Context, VValue Self, TArrayView<VValue> Arguments);`
- L303 _private member_ `EKind Kind;`
- L304 _private member_ `EFlags Flags;`
- L307 _private member_ `int32 NumInherited;` — Super classes and interfaces. The single superclass is always first.
- L310 _private member_ `TWriteBarrier<VArchetype> Archetype;` — Represents the fields in the class. Archetype->NextArchetype points to the archetype for the superclass, if there is one.
- L313 _private member_ `TWriteBarrier<VFunction> Constructor;` — Function containing default initializers and blocks, in a scope with `(super:)`.
- L315 _private member_ `TWriteBarrier<VFunction> Blocks;` — When verse.UObjectLeniency is disabled, blocks are split into this separate function.
- L320 _private member_ `TMap<TWriteBarrier<VUniqueStringSet>, TWriteBarrier<VEmergentType>, FDefaultSetAllocator, FEmergentTypesCacheKeyFuncs> EmergentTypesCache;` — TODO: (yiliang.siew) This should be a weak map when we can support it in the GC. https://jira.it.epicgames.com/browse/SOL-5312 This is a cache that allows for fast vending of emergent types based on the fields being overridden. When this is made weak, `VProcedure::VisitReferencesImpl` must be updated to keep OpNewObjectICArchetype's cached emergent type alive.
- L321 _private member_ `TWriteBarrier<VEmergentType> NativeConstructorEmergentType;`
- L324 _private member_ `TWriteBarrier<VClass> Inherited[];` — The in-order list of superclasses that this class inherits from.

#### enum `Verse::VClass::EKind`  
`enum class EKind : uint8`  
_L155-160_
- L157 _public enumerator_ `Class`
- L158 _public enumerator_ `Struct`
- L159 _public enumerator_ `Interface`

#### enum `Verse::VClass::EFlags`  
`enum class EFlags : uint16`  
_L161-177_
- L163 _public enumerator_ `None = 0`
- L164 _public enumerator_ `NativeRepresentation = 1 << 0`
- L165 _public enumerator_ `NativeStructWithObjectReferences = 1 << 1`
- L166 _public enumerator_ `Concrete = 1 << 2`
- L167 _public enumerator_ `FinalSuper = 1 << 3`
- L168 _public enumerator_ `ExplicitlyCastable = 1 << 4`
- L169 _public enumerator_ `Parametric = 1 << 5`
- L170 _public enumerator_ `UniversallyAccessible = 1 << 6`
- L171 _public enumerator_ `EpicInternal = 1 << 7`
- L172 _public enumerator_ `Predicts = 1 << 8`
- L173 _public enumerator_ `PersonaConstructible = 1 << 9`
- L174 _public enumerator_ `CustomAttribute = 1 << 10`
- L175 _public enumerator_ `Unique = 1 << 11`
- L176 _public enumerator_ `EmulateCaseInsensitiveOverrides = 1 << 12`

#### Free symbols / members of external scopes

- L22 _namespace_ `namespace Verse`

### `Source/Runtime/CoreUObject/Public/VerseVM/VVMCollectionCycleRequest.h` (Public)


#### struct `Verse::FCollectionCycleRequest`  
`struct FCollectionCycleRequest`  
_L13-45_
- L15 _public prototype_ `FCollectionCycleRequest() = default;`
- L17 _public prototype_ `bool IsDone() const;`
- L22 _public prototype_ `void Wait(FIOContext Context) const;` — This needs an IO context because waiting for the GC in a running context is sure to deadlock. Waiting on one of these requests is totally optional.
- L24 _public function_ `FCollectionCycleRequest Previous() const`
- L39 _private function_ `explicit FCollectionCycleRequest(uint64 InRequestedCycleVersion) : RequestedCycleVersion(InRequestedCycleVersion)`
- L44 _private member_ `uint64 RequestedCycleVersion = 0;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace Verse`

### `Source/Runtime/CoreUObject/Public/VerseVM/VVMConservativeStackEntryFrame.h` (Public)


#### struct `Verse::FConservativeStackEntryFrame`  
`struct FConservativeStackEntryFrame`  
_L11-14_
- L13 _public member_ `FConservativeStackExitFrame* ExitFrame;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace Verse`

### `Source/Runtime/CoreUObject/Public/VerseVM/VVMConservativeStackExitFrame.h` (Public)


#### struct `Verse::FConservativeStackExitFrame`  
`struct FConservativeStackExitFrame`  
_L13-16_
- L15 _public member_ `FConservativeStackEntryFrame* EntryFrame;`

#### struct `Verse::FConservativeStackExitFrameWithJmpBuf`  
`struct FConservativeStackExitFrameWithJmpBuf : FConservativeStackExitFrame`  
_L21-24_
- inherits: `FConservativeStackExitFrame`
- desc: FIXME: The way that this should really work is that the ExitConservativeStack function is written in assembly and saves all callee-save GPRs but only restores the ones it actually touched. That will be much cheaper than calling setjmp!
- L23 _public member_ `jmp_buf JmpBuf;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace Verse`

### `Source/Runtime/CoreUObject/Public/VerseVM/VVMContentScope.h` (Public)


#### class `verse::FContentScope`  
`class FContentScope`  
_L34-100_
- L37 _public function_ `FContentScope(const UObject* InInstantiationOuter) : InstantiationOuter(InInstantiationOuter)`
- L42 _public prototype_ `virtual ~FContentScope() = default;`
- L44 _public function_ `bool ShouldExecuteCodeWithThisScope() const`
- L45 _public function_ `bool WasTerminated() const`
- L47 _public function_ `const UObject* GetInstantiationOuter() const`
- L48 _public function_ `const UObject* GetWorldContext() const`
- L51 _public prototype_ `virtual verse::task_group* GetTaskGroup() = 0;`
- L53 _public prototype_ `virtual Verse::VTaskGroup* GetTaskGroup() = 0;`
- L56 _public prototype_ `virtual bool HasActiveTasks() const = 0;`
- L57 _public prototype_ `virtual void Terminate() = 0;`
- L58 _public prototype_ `virtual void ResetTerminationState() = 0;`
- L60 _public prototype_ `virtual bool ReserveActorFromQuota() = 0;`
- L61 _public prototype_ `virtual bool CanReserveActorFromQuota() const = 0;`
- L62 _public prototype_ `virtual void ReleaseActorToQuota() = 0;`
- L64 _public prototype_ `virtual bool HasContent() const = 0;`
- L67 _public function_ `bool ShouldRuntimeErrorOnNullObjectAccess()`
- L71 _public function_ `void SetShouldRuntimeErrorOnNullObjectAccess(bool bShould)`
- L74 _public prototype_ `FString GetCreatorDebugName() const;`
- L75 _public prototype_ `void SetCreatorDebugName(const FStringView& InCreatorDebugName);`
- L76 _public prototype_ `void SetCreatorDebugNameFromObject(const UObject* Object);`
- L80 _public function_ `void SetOwner(const UObject* InOwner)` — FORT-687867: Delete this when tag query code is fixed. It depends on the content scope actor and they should not See TagQueryUtils::GetActorFromActiveVerseExecutionContentScope()
- L81 _public function_ `const UObject* GetOwner() const`
- L86 _public member_ `FContentScopeCleanupSignature OnContentScopeCleanup;` — Called whenever the content scope is cleaned up/terminated (either normally or abnormally) If it was terminated abnormally, 'true' is passed to the callback All registered callbacks are removed after the event is broadcast
- L91 _protected member_ `TWeakObjectPtr<const UObject> Owner;` — FORT-687867: Delete this when tag query code is fixed. It depends on the content scope actor and they should not See TagQueryUtils::GetActorFromActiveVerseExecutionContentScope()
- L93 _protected member_ `FString CreatorDebugName;`
- L95 _protected member_ `TWeakObjectPtr<const UObject> InstantiationOuter;`
- L96 _protected member_ `bool bTerminated = false;`
- L99 _private member_ `bool bShouldRuntimeErrorOnNullObjectAccess{true};`

#### class `verse::FContentScopeGuard`  
`class FContentScopeGuard`  
_L102-133_
- L105 _public prototype_ `explicit FContentScopeGuard(const TSharedRef<FContentScope>& InContent);`
- L106 _public prototype_ `~FContentScopeGuard();`
- L108 _public prototype_ `FContentScopeGuard(const FContentScopeGuard&) = delete;`
- L109 _public prototype_ `FContentScopeGuard& operator=(const FContentScopeGuard&) = delete;`
- L111 _public function_ `static bool IsActive()`
- L112 _public function_ `static const TSharedRef<FContentScope>& GetActiveScope()`
- L114 _public prototype_ `static void ScheduleTerminateContentScope(TSharedRef<FContentScope> ContentScope);`
- L118 _public prototype_ `static void OnInactive(TFunction<void()>&& Callback);` — If there is an active content scope, enqueues Callback to be called when the last active content scope is popped from the stack. IF there is no active content scope, calls Callback immediately.
- L120 _public prototype_ `static bool EnforceExecutionTimeForActiveContentScope();`
- L123 _private prototype_ `static FContentScopeGuard*& GetActiveScopeGuard();`
- L124 _private prototype_ `static FContentScopeGuard* GetRootScopeGuard();`
- L126 _private prototype_ `bool EnforceExecutionTime();`
- L128 _private member_ `TSharedRef<FContentScope> ContentScope;`
- L129 _private member_ `FContentScopeGuard* Parent = nullptr;`
- L132 _private member_ `TArray<TFunction<void()>> PendingOnInactiveCallbacks;` — Scheduled for shutdown when the outermost scope guard ends.

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API COREUOBJECT_API`
- L20 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FContentScopeCleanupSignature, bool);`
- L20 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FContentScopeCleanupSignature, bool);`
- L22 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogContentScope, Warning, All);`
- L24 _namespace_ `namespace Verse`
- L29 _namespace_ `namespace verse`
- L135 _prototype_ `UObject* GetInstantiationOuter();` (scope `verse`)
- L136 _prototype_ `EObjectFlags GetInstantiationFlags();` (scope `verse`)

### `Source/Runtime/CoreUObject/Public/VerseVM/VVMContext.h` (Public)


#### enum `Verse::EIsInHandshake`  
`enum class EIsInHandshake`  
_L50-54_
- L52 _public enumerator_ `No`
- L53 _public enumerator_ `Yes`

#### struct `Verse::FContext`  
`struct FContext`  
_L56-183_
- L58 _public prototype_ `FContext() = default;`
- L60 _public function_ `FContext(const FContext& Other) : EncodedWord(Other.EncodedWord)`
- L66 _public prototype_ `FContext& operator=(const FContext&) = default;`
- L68 _public function_ `EIsInHandshake IsInHandshake() const`
- L73 _public function_ `bool operator==(const FContext& Other) const`
- L78 _public function_ `explicit operator bool() const`
- L83 _public function_ `EContextHeapRole GetHeapRole() const`
- L88 _public function_ `void EnableManualStackScanning() const`
- L93 _public function_ `bool UsesManualStackScanning() const`
- L100 _public function_ `bool ManualStackScanRequested() const` — You can use this to guard calling ClearManualStackScanRequest(). But you don't have to, because that function will return quickly if no manual stack scan has been requested!
- L115 _public function_ `void ClearManualStackScanRequest() const` — If a thread is using manual stack scanning, then it should periodically call this function. - It's not OK to call this function if you haven't enabled manual stack scanning. Calling this function if manual stack scanning is not enabled for this context will crash! - It's OK to call this function if GC is not running. This function will quickly return in that case. - It's OK to call this function if manual stack scanning hasn't been requested. This function will quickly return in that case. - If you call this function, you have to make sure you have already somehow marked all roots associated with your context. The way UE GC does that is by calling this function at end of tick, when there are no roots associated with the main thread context!
- L120 _public function_ `bool IsInManuallyEmptyStack() const`
- L125 _public function_ `void SetIsInManuallyEmptyStack(bool bInIsInManuallyEmptyStack) const`
- L130 _public function_ `static FNativeFrame* NativeFrame()`
- L136 _public function_ `static void AttachedDebugger()`
- L140 _public function_ `static void DetachedDebugger()`
- L145 _public prototype_ `void RaiseVerseRuntimeError(const Verse::ERuntimeDiagnostic Diagnostic, const FText& ErrorMsg);`
- L153 _protected function_ `FContext(FContextImpl* Impl, EIsInHandshake IsInHandshake)`
- L160 _protected function_ `void CheckBaseInvariants() const`
- L165 _protected function_ `FContextImpl* GetImpl() const`
- L170 _protected function_ `void SetImpl(FContextImpl* Impl)`
- L175 _protected function_ `void SetIsInHandshake(EIsInHandshake IsInHandshake)`
- L180 _protected member_ `static constexpr uintptr_t IsInHandshakeBit = 1;`
- L182 _protected member_ `uintptr_t EncodedWord = 0;`

#### struct `Verse::FIOContextPromise`  
`struct FIOContextPromise`  
_L185-188_
- L187 _public prototype_ `FIOContextPromise() = default;`

#### struct `Verse::FIOContext`  
`struct FIOContext : FContext`  
_L200-321_
- inherits: `FContext`
- desc: Having an IO context means: - You cannot access the heap. - You cannot allocate. - You can reacquire heap access (and then you'll have a FRunningContext). IO contexts are the default for external native code. When we support a public native API, native code will run in the IO context. IO contexts ARE NOT the default for engine code! Engine code is in a running context by default.
- L202 _public function_ `FIOContext(const FIOContext& Other) : FContext(Other)`
- L208 _public function_ `FIOContext(const FIOContextPromise& Other) : FContext(FContextImpl::GetCurrentImpl(), EIsInHandshake::No)`
- L217 _public function_ `template <typename TFunc> static void Create(AUTORTFM_IMPLICIT_DISABLE const TFunc& Func, EContextHeapRole HeapRole = EContextHeapRole::Mutator)` — Create the context for this thread and run some code in it without heap access. You can only have one context created per thread.
- L226 _public prototype_ `template <typename TFunc> void AcquireAccess(AUTORTFM_IMPLICIT_DISABLE const TFunc& Func) const;`
- L230 _public function_ `static FIOContext CreateForManualStackScanning()` — Create the context for this thread, and enable manual stack scanning. Makes sense in places like the UE game thread that manage their own GC marking without conservative stack.
- L237 _public function_ `void ReleaseForManualStackScanning()`
- L243 _public prototype_ `FRunningContext AcquireAccessForManualStackScanning();`
- L247 _public prototype_ `void PairHandshake(FContext Context, AUTORTFM_IMPLICIT_DISABLE TFunctionRef<void(FHandshakeContext)> HandshakeAction) const;` — Wait until the target context runs the given function. If that context doesn't have access, the action runs immediately and on the calling thread.
- L253 _public prototype_ `void SoftHandshake(AUTORTFM_IMPLICIT_DISABLE TFunctionRef<void(FHandshakeContext)> HandshakeAction) const;` — Wait until all currently running contexts run the given function. For contexts that don't have access, the action runs immediately and on the calling thread. Also calls the function for the calling thread. The soft handshake is the basis for the Verse concurrent GC.
- L271 _public prototype_ `void HardHandshake(AUTORTFM_IMPLICIT_DISABLE TFunctionRef<void(FHardHandshakeContext)> HandshakeAction) const;` — This is the structured stop-the-world API. Threads are stopped before HandshakeAction runs and resumed after it returns. HandshakeAction is a FHardHandshakeContext, which is a subclass of FIOContext - so you can do anything an IO context can do while inside the handshake, including: - Acquiring access and then doing anything a running context lets you do - Start new threads (which aren't going to be stopped) - Do soft and pair handshakes (stopped threads show up as not having access) Of course, that's super dangerous, since who knows what locks are being held by stopped threads. For sure, you won't want to acquire locks that would be held in a running context while inside a hard handshake. Only one hard handshake can happen at any time. Attempting to hard handshake while one is already happening blocks until that one finishes. That's because hard handshakes use StopTheWorld under the hood, and StopTheWorld grabs a lock. FIXME: We should allow hard handshaking a subset of threads. For example, we want to be able to hard handshake all but the GC threads.
- L293 _public prototype_ `FStoppedWorld StopTheWorld() const;` — This is the unstructured stop-the-world API. Threads are resumed whenever the FStoppedWorld object dies. It has move semantics, so you can keep it alive by moving it around. Additionally, the FStoppedWorld can tell you about all of the threads that were stopped and it gives you an access context to each of them. The calling thread is not stopped. It's legal to stop the world and then execute anything that an IO context would let you execute, including: - Acquiring access and then doing anything a running context lets you do - Start new threads (which aren't going to be stopped) - Do soft and pair handshakes (stopped threads show up as not having access) Of course, that's super dangerous, since who knows what locks are being held by stopped threads. For sure, you won't want to stop the world and acquire locks that would be held in a running context. Only one thread can stop the world at any time. Hard handshakes use the StopTheWorld mechanism, so if a hard handshake is happening then stop-the-world blocks and vice-versa. FIXME: We should allow stopping just a subset of threads. For example, we want to be able to hard handshake all but the GC threads.
- L296 _protected prototype_ `FIOContext() = delete;`
- L297 _protected prototype_ `FIOContext& operator=(const FIOContext&) = delete;`
- L299 _protected function_ `void CheckIOInvariants() const`
- L304 _protected prototype_ `void DieIfInvariantsBroken() const;`
- L305 _protected function_ `void CheckInvariants() const`
- L311 _protected function_ `FIOContext(FContextImpl* Impl, EIsInHandshake IsInHandshake) : FContext(Impl, IsInHandshake)`
- L320 _private prototype_ `FIOContext(const FRunningContext& Other);`
- L896 _function_ `inline FIOContext::FIOContext(const FRunningContext& Other) : FContext(Other)`
- L903 _function_ `template <typename TFunc> void FIOContext::AcquireAccess(const TFunc& Func) const`
- L913 _function_ `inline FRunningContext FIOContext::AcquireAccessForManualStackScanning()`

#### class `Verse::FPackageScope`  
`class FPackageScope`  
_L323-349_
- L327 _private member_ `FContextImpl* Impl;`
- L328 _private member_ `VPackage* OldPackage;`
- L337 _public function_ `FPackageScope(FInitializer Initializer) : Impl(Initializer.Impl) , OldPackage(Impl->SetCurrentPackage(Initializer.NewPackage))`
- L343 _public prototype_ `FPackageScope(const FPackageScope&) = delete;`
- L344 _public prototype_ `FPackageScope& operator=(const FPackageScope&) = delete;`
- L345 _public prototype_ `FPackageScope(FPackageScope&&) = delete;`
- L346 _public prototype_ `FPackageScope& operator=(FPackageScope&& Other) = delete;`
- L348 _public function_ `~FPackageScope()`

#### struct `Verse::FPackageScope::FInitializer`  
`struct FInitializer`  
_L330-334_
- L332 _public member_ `FContextImpl* Impl;`
- L333 _public member_ `VPackage* NewPackage;`

#### struct `Verse::FAccessContextPromise`  
`struct FAccessContextPromise`  
_L352-355_
- desc: Our barriers need to be able to run without being passed an FAccessContext in some cases, like copy constructors and operator=.
- L354 _public prototype_ `FAccessContextPromise() = default;`

#### struct `Verse::FAccessContext`  
`struct FAccessContext : FContext`  
_L363-600_
- inherits: `FContext`
- desc: Having an access context means: - You can access the heap. - You cannot allocate. - You cannot handshake. - You cannot relinquish access.
- L365 _public function_ `FAccessContext(const FAccessContext& Other) : FContext(Other)`
- L371 _public function_ `FAccessContext(const FAccessContextPromise& Other) : FContext(FContextImpl::GetCurrentImpl(), EIsInHandshake::No)`
- L377 _public function_ `void StopAllocators() const`
- L382 _public function_ `FMarkStack& GetMarkStack() const`
- L387 _public function_ `void RunWriteBarrier(VCell* Cell) const`
- L392 _public function_ `void RunWriteBarrierNonNull(const VCell* Cell) const`
- L397 _public function_ `void RunWriteBarrierNonNullDuringMarking(VCell* Cell) const`
- L402 _public function_ `void RunWriteBarrierDuringMarking(VCell* Cell) const`
- L407 _public function_ `VCell* RunWeakReadBarrier(VCell* Cell) const`
- L412 _public function_ `VCell* RunWeakReadBarrierUnmarkedWhenActive(VCell* Cell) const`
- L418 _public function_ `void RunAuxWriteBarrier(void* Aux) const`
- L423 _public function_ `void RunAuxWriteBarrierNonNull(const void* Aux) const`
- L428 _public function_ `void RunAuxWriteBarrierNonNullDuringMarking(void* Aux) const`
- L433 _public function_ `void RunAuxWriteBarrierDuringMarking(void* Aux) const`
- L438 _public function_ `void* RunAuxWeakReadBarrier(void* Aux) const`
- L443 _public function_ `void* RunAuxWeakReadBarrierUnmarkedWhenActive(void* Aux) const`
- L449 _public function_ `FTransaction* CurrentTransaction() const`
- L454 _public function_ `void SetCurrentTransaction(FTransaction* Transaction) const`
- L459 _public function_ `VTaskGroup* CurrentTaskGroup() const`
- L464 _public function_ `void SetCurrentTaskGroup(VTaskGroup* TaskGroup) const`
- L469 _public function_ `FNativeFrame* NativeFrame() const`
- L477 _public function_ `template <typename TFunctor> auto PushNativeFrame( VFailureContext* FailureContext, VTask* Task, VBatchedRefs* BatchedRefs, VValue& EffectToken, const VNativeProcedure* Callee, const FOp* CallerPC, VFrame* CallerFrame, const TFunctor& F)` — Run the functor in the same transaction with the given native context stashed in this context TFunctor is ()->T
- L501 _public prototype_ `AUTORTFM_DISABLE FOpResult HandleAutoRTFMFailure(AutoRTFM::ETransactionStatus TransactionResult);` — Called when a native call to C++, via AutoRTFM::Close() returns a result that is not Executing. This function will handle the failure based on the failure kind.
- L511 _public function_ `template <typename FunctorType, typename FunctorReturnType = decltype(std::declval<FunctorType>()())> requires(std::is_same_v<FunctorReturnType, void> || std::is_same_v<FunctorReturnType, FOpResult>) [[nodiscard]] AUTORTFM_DISABLE FOpResult Close(AUTORTFM_IMPLICIT_ENABLE FunctorType&& Functor)` — Calls Functor in the closed. If the transaction fails, then the failure status is translated to an FOpResult and is returned. Functor must either return void or FOpResult. If Functor returns FOpResult then this will be returned by Close() (on transaction success).
- L535 _public function_ `template <typename FunctorType> [[nodiscard]] AUTORTFM_DISABLE FOpResult CloseIf(bool bCondition, AUTORTFM_IMPLICIT_ENABLE FunctorType&& Functor)` — If bCondition is true, then Functor is passed to FAccessContext::Close() and its result is returned, otherwise the function is called immediately in the open and FOpResult::Return is returned.
- L546 _public function_ `uint64 GetWriteEpoch()`
- L551 _public function_ `void BumpWriteEpoch()`
- L556 _public function_ `[[nodiscard]] FPackageScope::FInitializer SetCurrentPackage(VPackage* Package)`
- L561 _public function_ `VPackage* GetCurrentPackage()`
- L566 _public function_ `void RecordCell(VCell* Cell)`
- L571 _public function_ `VPackage* PackageForCell(VCell* Cell)`
- L576 _public function_ `void PushImport(FTopLevelAssetPath Path)`
- L580 _public function_ `FTopLevelAssetPath PopImport()`
- L588 _protected prototype_ `FAccessContext() = delete;`
- L589 _protected prototype_ `FAccessContext& operator=(const FAccessContext&) = delete;`
- L591 _protected function_ `FAccessContext(FContextImpl* Impl, EIsInHandshake IsInHandshake) : FContext(Impl, IsInHandshake)`
- L596 _protected function_ `void CheckAccessInvariants() const`

#### struct `Verse::FRunningContextPromise`  
`struct FRunningContextPromise`  
_L606-609_
- desc: Engine code that doesn't carry around the context but knows that it's in a running state can use this. Sadly, it means that a TLS lookup is required if we really need the context. Code can postpone the context lookup by carrying around `FRunningContextPromise`. It's the coercion from the promise to an actual context that does the TLS lookup.
- L608 _public prototype_ `FRunningContextPromise() = default;`

#### struct `Verse::FRunningContext`  
`struct FRunningContext : FAccessContext`  
_L620-738_
- inherits: `FAccessContext`
- desc: Having a running context means: - You can access the heap. - You cannot allocate, but you can get yourself an allocation context and then allocate. - You can handshake. - You can relinquish access. Running contexts are the default for engine code, so that we only relinquish/acquire heap access around blocking operations.
- L622 _public function_ `FRunningContext(const FRunningContext& Other) : FAccessContext(Other)`
- L628 _public function_ `FRunningContext(const FRunningContextPromise& Promise) : FAccessContext(FContextImpl::GetCurrentImpl(), EIsInHandshake::No)`
- L636 _public prototype_ `FRunningContext(const FAccessContext&) = delete;` — We don't want RunningContexts to be coerced from AccessContexts, because RunningContexts have higher privilege (they can handshake and allocate via AllocationContexts).
- L639 _public prototype_ `FRunningContext(const FAllocationContext&) = delete;` — We don't want RunningContexts to be coerced from AllocationContexts, because RunningContexts have higher privilege (they can handshake).
- L644 _public function_ `template <typename TFunc> static void Create(const TFunc& Func)` — Create the context for this thread and run some code in it with heap access. You can only have one context created per thread.
- L652 _public function_ `template <typename TFunc> void RelinquishAccess(const TFunc& Func) const`
- L663 _public function_ `FIOContext RelinquishAccessForManualStackScanning()`
- L672 _public function_ `template <typename IfDebuggerOrProfilerCallback> void CheckForHandshake(IfDebuggerOrProfilerCallback Callback) const`
- L678 _public function_ `void CheckForHandshake() const`
- L684 _public function_ `void RequestRuntimeError()` — API for non-mutator threads to request runtime errors
- L685 _public function_ `void ClearRuntimeErrorRequest()`
- L686 _public function_ `bool IsRuntimeErrorRequested()`
- L689 _public function_ `template <typename TFunctor> void EnterVM(AUTORTFM_IMPLICIT_DISABLE TFunctor F)`
- L697 _public function_ `template <typename TFunctor> void TransactThenEnterVM(AUTORTFM_IMPLICIT_DISABLE TFunctor F)` — Creates a new transaction and ensure a new matching failure context is created to match
- L709 _private prototype_ `template <typename TFunctor> void EnterVM_Internal(EEnterVMMode Mode, TFunctor F);` — The entry point that all `C++` calls into Verse should go through
- L711 _private function_ `FRunningContext(const FIOContext& Other) : FAccessContext(Other.GetImpl(), EIsInHandshake::No)`
- L721 _protected function_ `FRunningContext(FContextImpl* Impl, EIsInHandshake IsInHandshake) : FAccessContext(Impl, IsInHandshake)`
- L727 _protected function_ `void CheckRunningInvariants() const`
- L732 _protected function_ `void CheckInvariants() const`

#### struct `Verse::FAllocationContextPromise`  
`struct FAllocationContextPromise`  
_L740-743_
- L742 _public prototype_ `FAllocationContextPromise() = default;`

#### struct `Verse::FAllocationContext`  
`struct FAllocationContext : FAccessContext`  
_L755-856_
- inherits: `FAccessContext`
- desc: Having an allocation context means: - You can access the heap. - You can allocate. - You cannot handshake. - You cannot relinquish access. It's important to stay in an allocation context from the point where the object is allocated to the point where it is fully constructed. So, T::New functions and VCell constructors should always take an allocation context!
- L757 _public function_ `FAllocationContext(const FAllocationContext& Other) : FAccessContext(Other)`
- L762 _public function_ `FAllocationContext(const FRunningContext& Other) : FAccessContext(Other)`
- L768 _public function_ `FAllocationContext(const FAllocationContextPromise& Promise) : FAllocationContext(FContextImpl::GetCurrentImpl(), EIsInHandshake::No)`
- L775 _public prototype_ `FAllocationContext(const FAccessContext&) = delete;` — We don't want AllocationContexts to be coerced from AccessContexts, because AllocationContexts have higher privilege (they can allocate).
- L777 _public function_ `~FAllocationContext()`
- L784 _public function_ `AUTORTFM_DISABLE std::byte* AllocateFastCell(size_t NumBytes) const` — It's preferable to call this instead of using Allocate(FHeap::FastSpace) because it's faster. However, it's not wrong to say Allocate(FHeap::FastSpace).
- L790 _public function_ `AUTORTFM_DISABLE std::byte* TryAllocateFastCell(size_t NumBytes) const`
- L796 _public function_ `AUTORTFM_DISABLE std::byte* AllocateAuxCell(size_t NumBytes) const`
- L802 _public function_ `AUTORTFM_DISABLE std::byte* TryAllocateAuxCell(size_t NumBytes) const`
- L809 _public function_ `AUTORTFM_DISABLE std::byte* AllocateEmergentType(size_t NumBytes) const` — Special reservation for EmergentTypes where offset fits in 32 bits.
- L815 _public function_ `AUTORTFM_DISABLE std::byte* TryAllocate(FSubspace* Subspace, size_t NumBytes) const`
- L820 _public function_ `AUTORTFM_DISABLE std::byte* TryAllocate(FSubspace* Subspace, size_t NumBytes, size_t Alignment) const`
- L825 _public function_ `AUTORTFM_DISABLE std::byte* Allocate(FSubspace* Subspace, size_t NumBytes) const`
- L830 _public function_ `AUTORTFM_DISABLE std::byte* Allocate(FSubspace* Subspace, size_t NumBytes, size_t Alignment) const`
- L839 _protected function_ `FAllocationContext(FContextImpl* Impl, EIsInHandshake IsInHandshake) : FAccessContext(Impl, IsInHandshake)`
- L845 _protected function_ `void CheckAllocationInvariants() const`
- L850 _protected function_ `void CheckInvariants() const`

#### struct `Verse::FHandshakeContext`  
`struct FHandshakeContext : FAccessContext`  
_L858-879_
- inherits: `FAccessContext`
- L860 _public prototype_ `FHandshakeContext(const FHandshakeContext& Other) = default;`
- L861 _public prototype_ `FStopRequest RequestStop() const;`
- L863 _public function_ `void MarkConservativeStack() const`
- L868 _public function_ `void MarkReferencedCells() const`
- L875 _private function_ `FHandshakeContext(FContextImpl* Impl) : FAccessContext(Impl, EIsInHandshake::Yes)`

#### struct `Verse::FStopRequest`  
`struct FStopRequest : FAccessContext`  
_L881-894_
- inherits: `FAccessContext`
- L883 _public function_ `void CancelStop() const`
- L890 _private function_ `FStopRequest(FHandshakeContext Context) : FAccessContext(Context)`

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace Verse`
- L415 _function_ `return GetImpl()->RunWeakReadBarrierUnmarkedWhenActive(Cell, [this](const VCell* Cell) { GetImpl()->MarkStack.MarkNonNull(Cell); });` (scope `Verse::FAccessContext::RunWeakReadBarrierUnmarkedWhenActive`)
- L446 _function_ `return GetImpl()->RunWeakReadBarrierUnmarkedWhenActive(Aux, [this](const void* Aux) { GetImpl()->MarkStack.MarkAuxNonNull(Aux); });` (scope `Verse::FAccessContext::RunAuxWeakReadBarrierUnmarkedWhenActive`)
- L514 _function_ `AutoRTFM::ETransactionStatus Status = AutoRTFM::Close([&] { if constexpr (std::is_same_v<FunctorReturnType, FOpResult>) { Result = Functor(); } else { Functor(); } });` (scope `Verse::FAccessContext::Close`)
- L646 _function_ `FIOContext::Create([&Func](FIOContext Context) { Context.AcquireAccess(Func); });` (scope `Verse::FRunningContext::Create`)
- L655 _function_ `GetImpl()->ExitConservativeStack([this, &Func]() { GetImpl()->RelinquishAccess(); Func(FIOContext(*this)); GetImpl()->AcquireAccess(); });` (scope `Verse::FRunningContext::RelinquishAccess`)
- L680 _function_ `CheckForHandshake([] {});` (scope `Verse::FRunningContext::CheckForHandshake`)
- L699 _function_ `AutoRTFM::TransactThenOpen([&] { EnterVM_Internal(EEnterVMMode::NewTransaction, F); });` (scope `Verse::FRunningContext::TransactThenEnterVM`)
- L907 _function_ `GetImpl()->EnterConservativeStack([this, &Func]() { Func(FRunningContext(*this)); });` (scope `Verse::FIOContext::AcquireAccess`)
- L921 _function_ `template <typename TFunctor> auto FContextImpl::PushNativeFrame( VFailureContext* FailureContext, VTask* Task, VBatchedRefs* BatchedRefs, VValue& EffectToken, const VNativeProcedure* Callee, const FOp* CallerPC, VFrame* CallerFrame, const TFunctor& F)` (scope `Verse::FContextImpl`)

### `Source/Runtime/CoreUObject/Public/VerseVM/VVMContextImpl.h` (Public)


#### enum `Verse::EContextHeapRole`  
`enum class EContextHeapRole`  
_L63-67_
- L65 _public enumerator_ `Mutator`
- L66 _public enumerator_ `Collector`

#### enum `Verse::EContextLifecycleState`  
`enum class EContextLifecycleState`  
_L69-84_
- L72 _public enumerator_ `Free` — The context is in FreeContexts and is not associated with any thread.
- L78 _public enumerator_ `LiveButUnused` — The context is in LiveContexts, is associated with a thread, but that thread is not beneath either FIOContext::Create() or FRunningContext::Create() - so from the user's perspective, this context doesn't exist. We maintain the context-thread mapping to make libpas happy and because it's likely to make other aspects of handshakes easier to implement.
- L83 _public enumerator_ `LiveAndInUse` — The context is in LiveContexts, is associated with a thread, and that thread is beneath either FIOContext::Create() or FRunningContext::Create() - so from the user's perspective, this context really is live.

#### enum `Verse::EEnterVMMode`  
`enum class EEnterVMMode`  
_L86-90_
- L88 _public enumerator_ `Auto`
- L89 _public enumerator_ `NewTransaction` — ensures a new transaction is made

#### struct `Verse::FNativeFrame`  
`struct AUTORTFM_DISABLE FNativeFrame`  
_L93-137_
- desc: A frame which we execute C++ from in the VM
- L95 _public member_ `VFailureContext* FailureContext = nullptr;`
- L96 _public member_ `VTask* Task = nullptr;`
- L97 _public member_ `VBatchedRefs* BatchedRefs = nullptr;`
- L99 _public member_ `VValue EffectToken;`
- L101 _public member_ `const VNativeProcedure* Callee = nullptr;`
- L102 _public member_ `const FOp* CallerPC = nullptr;`
- L103 _public member_ `VFrame* CallerFrame = nullptr;`
- L104 _public member_ `FNativeFrame* PreviousNativeFrame = nullptr;`
- L106 _public prototype_ `void Start(FRunningContext Context) const;`
- L107 _public prototype_ `bool IsCurrent(FAccessContext Context) const;`
- L108 _public prototype_ `void CommitIfNoAbort(FRunningContext Context) const;`
- L110 _public prototype_ `void GetStackDescription(FStringBuilderBase& StringBuilder) const;`
- L114 _public prototype_ `VFailureContext* RootFailureContext() const;` — Chases VFailureContext::Parent pointers from FailureContext until reaching and returning the root VFailureContext.
- L127 _public prototype_ `template <typename VFrameCallback, typename NativeFrameCallback> AUTORTFM_INFER void WalkCallstackFrames(const FOp* InPC, VFrame* InFrame, VTask* InTask, VFrameCallback FrameCallback, NativeFrameCallback NativeCallback) const;` — Walks frames in this order: - 'this' native frame if its caller is 'Frame' to handle native call's being the starting point - Loops over VFrame->CallerFrame till we hit a null CallerFrame: - if we hit the 'root frame' of the current task during this loop, swaps to Yield Task/Frame and continues - If 'PreviousNativeFrame', recurses at end with CallerFrame and Task FrameCallback receives (const FOp* PC, VFrame*) where PC is the bytecode op at which that VFrame is paused: InPC for the topmost frame, the previous frame's CallerPC walking down the chain, the parent task's YieldPC across a task-spawn pivot, or the native frame's CallerPC across a native boundary.
- L130 _public function_ `template <typename FrameCallback> void WalkTaskFrames(VTask* InTask, FrameCallback Callback) const`

#### struct `Verse::FContextImpl`  
`struct FContextImpl`  
_L141-748_
- desc: One must have a FContext to talk to Verse VM objects on some thread. Each thread should only have one FContext.
- L143 _public typedef_ `typedef uint8 TState;`
- L145 _public prototype_ `void EnterConservativeStack(AUTORTFM_IMPLICIT_DISABLE TFunctionRef<void()>);`
- L146 _public prototype_ `void ExitConservativeStack(AUTORTFM_IMPLICIT_DISABLE TFunctionRef<void()>);`
- L148 _public function_ `bool InConservativeStack() const`
- L168 _public function_ `void AcquireAccess()`
- L182 _public function_ `void RelinquishAccess()`
- L193 _public function_ `template <typename IfDebuggerOrProfilerCallback> void CheckForHandshake(IfDebuggerOrProfilerCallback Callback)`
- L206 _public prototype_ `void RequestStop();`
- L207 _public prototype_ `void WaitForStop();`
- L208 _public prototype_ `void CancelStop();`
- L210 _public prototype_ `void RequestRuntimeError();`
- L211 _public prototype_ `void ClearRuntimeErrorRequest();`
- L213 _public prototype_ `void PairHandshake(FContextImpl* TargetContext, TFunctionRef<void(FHandshakeContext)> HandshakeAction);`
- L214 _public prototype_ `void SoftHandshake(TFunctionRef<void(FHandshakeContext)> HandshakeAction);`
- L215 _public prototype_ `void HardHandshake(TFunctionRef<void(FHardHandshakeContext)> HandshakeAction);`
- L217 _public prototype_ `FStoppedWorld StopTheWorld();`
- L219 _public function_ `bool IsLive() const`
- L224 _public function_ `bool HasAccess() const`
- L228 _public function_ `bool IsHandshakeRequested() const`
- L232 _public function_ `bool IsStopRequested() const`
- L236 _public function_ `bool HasDebugger() const`
- L240 _public function_ `bool IsRuntimeErrorRequested()`
- L245 _public function_ `void RunWriteBarrierNonNull(const VCell* Cell)`
- L253 _public function_ `void RunWriteBarrier(VCell* Cell)`
- L261 _public function_ `void RunWriteBarrierNonNullDuringMarking(VCell* Cell)`
- L267 _public function_ `void RunWriteBarrierDuringMarking(VCell* Cell)`
- L276 _public function_ `VCell* RunWeakReadBarrier(VCell* Cell)`
- L288 _public function_ `void RunAuxWriteBarrierNonNull(const void* Aux)`
- L296 _public function_ `void RunAuxWriteBarrier(void* Aux)`
- L304 _public function_ `void RunAuxWriteBarrierNonNullDuringMarking(void* Aux)`
- L310 _public function_ `void RunAuxWriteBarrierDuringMarking(void* Aux)`
- L319 _public function_ `void* RunAuxWeakReadBarrier(void* Aux)`
- L332 _public function_ `template <typename T, typename MarkFunction> T* RunWeakReadBarrierUnmarkedWhenActive(T* Cell, MarkFunction&& MarkFunc)`
- L397 _public function_ `std::byte* AllocateFastCell(size_t NumBytes)`
- L402 _public function_ `std::byte* TryAllocateFastCell(size_t NumBytes)`
- L407 _public function_ `std::byte* AllocateAuxCell(size_t NumBytes)`
- L412 _public function_ `std::byte* TryAllocateAuxCell(size_t NumBytes)`
- L417 _public prototype_ `void StopAllocators();`
- L420 _public function_ `void EnableManualStackScanning()` — If we enable manual stack scan, it stays enabled until we destroy the context.
- L425 _public function_ `bool UsesManualStackScanning() const`
- L430 _public function_ `bool ManualStackScanRequested() const`
- L435 _public function_ `bool IsInManuallyEmptyStack() const`
- L440 _public prototype_ `void SetIsInManuallyEmptyStack(bool bInIsInManuallyEmptyStack);`
- L442 _public prototype_ `void MarkConservativeStack();`
- L444 _public prototype_ `void MarkReferencedCells();`
- L446 _public prototype_ `void ClearManualStackScanRequest();`
- L448 _public member_ `FMarkStack MarkStack;`
- L450 _public function_ `EContextHeapRole GetHeapRole() const`
- L455 _public function_ `FTransaction* CurrentTransaction() const`
- L460 _public function_ `void SetCurrentTransaction(FTransaction* Transaction)`
- L465 _public function_ `VTaskGroup* CurrentTaskGroup() const`
- L470 _public function_ `void SetCurrentTaskGroup(VTaskGroup* TaskGroup)`
- L475 _public function_ `FNativeFrame* NativeFrame() const`
- L483 _public prototype_ `template <typename TFunctor> auto PushNativeFrame( VFailureContext* FailureContext, VTask* Task, VBatchedRefs* BatchedRefs, VValue& EffectToken, const VNativeProcedure* Callee, const FOp* CallerPC, VFrame* CallerFrame, const TFunctor&);` — Run the functor in the same transaction with the given native context stashed in this context TFunctor is ()->void
- L493 _public prototype_ `void StartComputationWatchdog();`
- L494 _public prototype_ `void AddOverheadTime(double Duration);`
- L495 _public function_ `void PauseComputationWatchdog()`
- L496 _public prototype_ `void ResumeComputationWatchdog();`
- L497 _public prototype_ `void StopComputationWatchdog();`
- L498 _public prototype_ `static void AttachedDebugger();`
- L499 _public prototype_ `static void DetachedDebugger();`
- L501 _public prototype_ `AUTORTFM_DISABLE VPackage* SetCurrentPackage(VPackage* Package);`
- L502 _public function_ `VPackage* GetCurrentPackage()`
- L510 _public prototype_ `void RecordCell(VCell* Cell);`
- L511 _public prototype_ `VPackage* PackageForCell(VCell* Cell);`
- L513 _public function_ `void PushImport(FTopLevelAssetPath Path)`
- L521 _public function_ `FTopLevelAssetPath PopImport()`
- L546 _private function_ `std::byte* AllocateFastCell_Internal(size_t NumBytes, FastAllocatorArray& Allocators, FSubspace* Subspace)`
- L574 _private function_ `std::byte* TryAllocateFastCell_Internal(size_t NumBytes, FastAllocatorArray& Allocators, FSubspace* Subspace)`
- L589 _private prototype_ `static FContextImpl* ClaimOrAllocateContext(EContextHeapRole);`
- L590 _private prototype_ `void ReleaseContext();`
- L591 _private prototype_ `void FreeContextDueToThreadDeath();`
- L593 _private prototype_ `void ValidateUnclaimedContext();`
- L594 _private prototype_ `void ValidateContextHasEmptyStack();`
- L596 _private prototype_ `FContextImpl();`
- L597 _private prototype_ `~FContextImpl();`
- L599 _private prototype_ `static FContextImpl* GetCurrentImpl();`
- L601 _private prototype_ `void AcquireAccessSlow();`
- L602 _private prototype_ `void RelinquishAccessSlow();`
- L603 _private prototype_ `void CheckForHandshakeSlow();`
- L605 _private prototype_ `VCell* RunWeakReadBarrierNonNullSlow(VCell* Cell);`
- L606 _private prototype_ `void* RunAuxWeakReadBarrierNonNullSlow(void* Aux);`
- L608 _private prototype_ `void RequestHandshake(TUniqueFunction<void(FHandshakeContext)>&& HandshakeAction);`
- L609 _private prototype_ `bool AttemptHandshakeAcknowledgement();`
- L610 _private prototype_ `void WaitForHandshakeAcknowledgement();`
- L611 _private prototype_ `void AcknowledgeHandshakeRequest();`
- L612 _private prototype_ `void AcknowledgeHandshakeRequestWhileHoldingLock();`
- L614 _private prototype_ `void ClearManualStackScanRequestWhileHoldingLock();`
- L617 _private prototype_ `template <typename Function> static void AttachedOrDetachedDebuggerOrProfilerImpl(Function F);`
- L619 _private member_ `EContextLifecycleState LifecycleState = EContextLifecycleState::Free;`
- L621 _private member_ `static constexpr TState HasAccessBit = 1;`
- L622 _private member_ `static constexpr TState HandshakeRequestedBit = 2;`
- L623 _private member_ `static constexpr TState StopRequestedBit = 4;`
- L624 _private member_ `static constexpr TState HasDebuggerBit = 8;`
- L625 _private member_ `static constexpr TState RuntimeErrorRequestedBit = 16;`
- L630 _private member_ `std::atomic<TState> State = 0;` — This variable has a very particular synchronization story: - The thread that this context belongs to may CAS this without holding the StateMutex. - Any other thread may CAS this only while holding the StateMutex.
- L632 _private member_ `size_t StopRequestCount = 0;`
- L637 _private member_ `bool bUsesManualStackScanning = false;` — Threads can request to use manual stack scan. Stack scan is special to the GC; it's when the GC determines termination. Therefore, a thread that uses manual stack scan can block GC termination. This is great for binding the GC to another GC (like the UE GC).
- L640 _private member_ `bool bManualStackScanRequested = false;` — This being set indicates that a manual stack scan has been requested.
- L644 _private member_ `bool bIsInManuallyEmptyStack = false;` — If this is true and we're doing manual stack scans then it means that there's no need to scan the stack. This is intended to be set to true by the engine at the end of a tick.
- L652 _private member_ `UE::FMutex StateMutex;` — This mutex protects the State, but only partly, since the thread that owns the context may CAS the State directly. The idea is that if a handshake is requested then the thread will end up processing the handshake while holding this lock. So, if you hold this lock, then you're running exclusively to the thread's handling of handshakes.
- L660 _private member_ `UE::FConditionVariable StateConditionVariable;` — This condition variable achieves two things: - If we want a thread to stop, like if we're doing a hard handshake, then we have it wait on this condition variable. - If we want to wait for a thread to acknowledge that we asked it for something, then we can wait on this condition variable. We should always use NotifyAll() and never NotifyOne() on this condition variable!
- L665 _private member_ `UE::FMutex HandshakeMutex;` — This mutex protects the act of handshaking with this thread. If any thread wants to do a handshake, then it must hold its own handshake lock (if it has one) and the handshake lock of any thread it is handshaking with. When acquiring multiple handshake locks, acquire them in address order.
- L669 _private member_ `TUniqueFunction<void(FHandshakeContext)> RequestedHandshakeAction;` — When a handshake is requested, the thread acquires the StateMutex, clears the handshake request, runs this callback, and then does a broadcast.
- L674 _private member_ `pas_thread_local_cache_node* ThreadLocalCacheNode = nullptr;` — The libpas TLC node for this thread. Useful for stopping allocators, even from a different thread, so long as we're handshaking. TLC nodes are immortal and point to the actual TLC, which may resize (and move) at any time.
- L680 _private member_ `uint64_t ThreadLocalCacheNodeVersion = 0;` — We could be in this weird state where libpas has already destroyed its TLC node, and the node could even be associated with a different thread, but we still have it because we haven't destroyed our context. For this reason, libpas requires us to refer to the TLC node using both the node and its version. The version is guaranteed to increment when the TLC node is reclaimed.
- L682 _private member_ `FConservativeStackEntryFrame* TopEntryFrame = nullptr;`
- L683 _private member_ `FConservativeStackExitFrame* TopExitFrame = nullptr;`
- L685 _private member_ `FTrail* _CurrentTrail = nullptr;`
- L686 _private member_ `FTransaction* _CurrentTransaction = nullptr;`
- L687 _private member_ `VTaskGroup* _CurrentTaskGroup = nullptr;`
- L688 _private member_ `FNativeFrame* _NativeFrame = nullptr;`
- L691 _private member_ `uint64 CurrentWriteEpoch = 0;` — Incremented by native writes. Used to detect when a nested VNativeRef may have been invalidated.
- L693 _private member_ `EContextHeapRole HeapRole;`
- L695 _private member_ `FastAllocatorArray FastSpaceAllocators;`
- L696 _private member_ `FastAllocatorArray AuxSpaceAllocators;`
- L701 _private member_ `static thread_local FThreadLocalContextHolder CurrentThreadContext;` — The context for the current thread. Even if the thread stops passing around a context and forgets it has one, we must remember that it had one, because of the affinity between our notion of context and other notions of context in the system (libpas's TLC, AutoRTFM's context, etc).
- L706 _private member_ `static TNeverDestroyed<TSet<FContextImpl*>> LiveContexts;` — We need to be able to enumerate over all of the currently live contexts. This is a set so that it's easy for us to remove ourselves from it (but obviously that could be accomplished with an array if we were even a bit smart, FIXME).
- L712 _private member_ `static TNeverDestroyed<TArray<FContextImpl*>> FreeContexts;` — Contexts must be pooled to avoid nasty races in handshakes. Basically, if we request a handshake and the thread decides to die, then we should be able to handshake it anyway. Worst case, we'll either: - Handshake a newly created thread (who cares). - Realize that we're handshaking a dead context (we have to defend against this explicitly, and we do).
- L715 _private member_ `static UE::FMutex LiveAndFreeContextsMutex;` — This mutex protects the LiveContexts/FreeContexts data structures.
- L721 _private member_ `static UE::FMutex ContextCreationMutex;` — This mutex protects context creation. Should be held before LiveAndFreeContextsMutex. Holding this mutex ensures that no new contexts can be created. By "created" we mean both: - Allocating a new FContextImpl. - Pulling a FContextImpl from FreeContexts.
- L730 _private member_ `static UE::FMutex StoppedWorldMutex;` — Mutex to hold when stopping the world so that only one component is stopping the world at any time. It should be held before LiveAndFreeContextsMutex/ContextCreationMutex. Note that context creation holds this mutex also, so if you hold this one, no new contexts can be created. NOTE: This is separate from ContextCreationMutex because we want to be able to perform soft handshakes while the world is stopped, and soft handshakes need to lock out context creation right at the beginning of the soft handshake.
- L733 _private member_ `FThread ComputationWatchdog;` — A thread which is kicked off to check the computation time limit of executing Verse (mutator threads only)
- L734 _private member_ `std::atomic<double> StartTime = 0.0;`
- L735 _private member_ `std::atomic<double> TotalOverheadTime = 0.0;`
- L736 _private member_ `std::atomic<bool> bStopRequested = false;`
- L737 _private member_ `std::atomic<bool> bVerseIsRunning = true;`
- L738 _private member_ `UE::FEventCount WaitForVerseEvent;`
- L739 _private member_ `UE::FEventCount StopWatchdogEvent;`
- L742 _private member_ `VWeakCellMap* CellToPackage = nullptr;`
- L743 _private member_ `VPackage* CurrentPackage = nullptr;`
- L746 _private member_ `FTopLevelAssetPath ImportQueue;` — Single-element "queue" of @import_as paths requested by the compiler.

#### Free symbols / members of external scopes

- L34 _namespace_ `namespace Verse`
- L61 _typedef_ `typedef std::array<FLocalAllocator, (416 >> VERSE_HEAP_MIN_ALIGN_SHIFT) + 1> FastAllocatorArray;` (scope `Verse`) — The size of this must be matched to what is going on in FContextImpl::FContextImpl().
- L347 _function_ `return AutoRTFM::Open([&]() -> T* { if (WeakBarrierState == EWeakBarrierState::MarkOnRead) { MarkFunc(Cell); return Cell; } V_DIE_UNLESS(WeakBarrierState == EWeakBarrierState::AttemptingToTerminate);` (scope `Verse::FContextImpl::RunWeakReadBarrierUnmarkedWhenActive`)

### `Source/Runtime/CoreUObject/Public/VerseVM/VVMCppClassInfo.h` (Public)


#### struct `Verse::VCppClassInfo`  
`struct VCppClassInfo`  
_L180-226_
- desc: C++ information; this is where the "vtable" goes.
- L182 _public member_ `const TCHAR* Name;`
- L183 _public member_ `VCppClassInfo* SuperClass;`
- L184 _public member_ `size_t SizeWithoutFields;`
- L185 _public member_ `void (*MarkReferencesImpl)(VCell* This, FMarkStackVisitor&);`
- L186 _public member_ `void (*VisitReferencesImpl)(VCell* This, FAbstractVisitor&);`
- L187 _public member_ `void (*ConductCensus)(VCell* This);`
- L188 _public member_ `void (*RunDestructor)(VCell* This);`
- L189 _public member_ `ECompares (*Equal)(FAllocationContext Context, VCell* This, VCell* Other, const TFunction<void(::Verse::VValue, ::Verse::VValue)>& HandlePlaceholder);`
- L190 _public member_ `uint32 (*GetTypeHash)(VCell* This);`
- L191 _public member_ `VValue (*Melt)(FAllocationContext Context, VCell* This);`
- L192 _public member_ `FOpResult (*Freeze)(FAllocationContext Context, VCell* This, VTask*);`
- L193 _public member_ `bool (*Subsumes)(FAllocationContext Context, VCell* This, VValue);`
- L194 _public member_ `void (*VisitMembers)(FAllocationContext Context, VCell* This, FDebuggerVisitor& Visitor);`
- L195 _public member_ `void (*AppendToString)(FAllocationContext Context, VCell* This, FUtf8StringBuilderBase& Builder, EValueStringFormat Format, TSet<const void*>& VisitedObjects, uint32 RecursionDepth);`
- L196 _public member_ `TSharedPtr<FJsonValue> (*ToJSON)(FRunningContext, VCell* This, EValueJSONFormat, TMap<const void*, EVisitState>& VisitedObjects, FToJsonCallback, uint32 RecursionDepth, FJsonObject* Defs);`
- L197 _public member_ `VValue (*FromJSON)(FRunningContext, VCell* This, const FJsonValue&, EValueJSONFormat, FFromJsonCallback);`
- L198 _public member_ `void (*SerializeLayout)(FAllocationContext Context, VCell*& This, FStructuredArchiveVisitor& Visitor);`
- L199 _public member_ `void (*Serialize)(FAllocationContext Context, VCell* This, FStructuredArchiveVisitor& Visitor);`
- L200 _public member_ `bool SerializeIdentity;`
- L201 _public member_ `bool InstancedCell;`
- L203 _public function_ `bool IsA(const VCppClassInfo* Other) const`
- L215 _public function_ `V_FORCEINLINE void VisitReferences(VCell* This, FMarkStackVisitor& Visitor)`
- L220 _public function_ `V_FORCEINLINE void VisitReferences(VCell* This, FAbstractVisitor& Visitor)`
- L225 _public prototype_ `FString DebugName() const;`

#### struct `Verse::VCppClassInfoRegister`  
`struct VCppClassInfoRegister`  
_L228-235_
- L230 _public member_ `VCppClassInfo* CppClassInfo;`
- L231 _public member_ `VCppClassInfoRegister* Next;`
- L233 _public prototype_ `VCppClassInfoRegister(VCppClassInfo* InCppClassInfo);`
- L234 _public prototype_ `~VCppClassInfoRegister();`

#### struct `Verse::VCppClassInfoRegistry`  
`struct VCppClassInfoRegistry`  
_L237-240_
- L239 _public prototype_ `static VCppClassInfo* GetCppClassInfo(FStringView Name);`

#### Free symbols / members of external scopes

- L20 _namespace_ `namespace Verse`
- L40 _macro_ `#define VCPPCLASSINFO_PORTABLE_MSC_SUPER \`
- L44 _macro_ `#define VCPPCLASSINFO_PORTABLE_MSC_SUPER Super`
- L47 _macro_ `#define DECLARE_BASE_VCPPCLASSINFO(API) \`
- L60 _macro_ `#define DECLARE_DERIVED_VCPPCLASSINFO(API, SuperClass) \`
- L81 _macro_ `#define DEFINE_BASE_OR_DERIVED_VCPPCLASSINFO(CellType, SuperClassInfoPtr) \`
- L138 _macro_ `#define DEFINE_BASE_VCPPCLASSINFO(CellType) \`
- L152 _macro_ `#define DEFINE_DERIVED_VCPPCLASSINFO(CellType) \`
- L172 _macro_ `#define DEFINE_TRIVIAL_VISIT_REFERENCES(CellType) \`
- L244 _prototype_ `template <typename VisitorType, typename ValueType> void Visit(VisitorType& Visitor, ValueType& Value) = delete;` (scope `Verse`) — Extension point for VisitReferencesImpl and F*Visitor method instantiations
- L247 _function_ `template <typename VisitorType, typename KeyType, typename ValueType> void Visit(VisitorType& Visitor, TPair<KeyType, ValueType>& Value)` (scope `Verse`)

### `Source/Runtime/CoreUObject/Public/VerseVM/VVMCreateFieldInlineCache.h` (Public)


#### struct `Verse::FCreateFieldCacheCase`  
`struct FCreateFieldCacheCase`  
_L12-28_
- L23 _public member_ `EKind Kind = EKind::Invalid;`
- L24 _public member_ `uint32 FieldIndex = 0;`
- L25 _public member_ `uint32 NextEmergentTypeOffset = 0;`
- L27 _public function_ `explicit operator bool()`

#### enum `Verse::FCreateFieldCacheCase::EKind`  
`enum class EKind : uint8`  
_L14-21_
- L16 _public enumerator_ `ValueObjectConstant`
- L17 _public enumerator_ `ValueObjectField`
- L18 _public enumerator_ `NativeStruct`
- L19 _public enumerator_ `UObject`
- L20 _public enumerator_ `Invalid`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace Verse`

### `Source/Runtime/CoreUObject/Public/VerseVM/VVMCustomAttributeHandler.h` (Public)


#### enum `Verse::EAttributeValueType`  
`enum class EAttributeValueType`  
_L10-19_
- L12 _public enumerator_ `Logic`
- L13 _public enumerator_ `Int`
- L14 _public enumerator_ `Float`
- L15 _public enumerator_ `Type`
- L16 _public enumerator_ `Class`
- L17 _public enumerator_ `Array`
- L18 _public enumerator_ `String`

#### class `Verse::CAttributeValue`  
`class CAttributeValue`  
_L21-30_
- L24 _public function_ `CAttributeValue(EAttributeValueType InType) : Type(InType)`
- L29 _public member_ `EAttributeValueType Type;`

#### class `Verse::CAttributeLogicValue`  
`class CAttributeLogicValue : public CAttributeValue`  
_L32-42_
- inherits: `CAttributeValue`
- L35 _public function_ `CAttributeLogicValue(bool InValue) : CAttributeValue(EAttributeValueType::Logic) , Value(InValue)`
- L41 _public member_ `bool Value;`

#### class `Verse::CAttributeIntValue`  
`class CAttributeIntValue : public CAttributeValue`  
_L44-54_
- inherits: `CAttributeValue`
- L47 _public function_ `CAttributeIntValue(int64 InValue) : CAttributeValue(EAttributeValueType::Int) , Value(InValue)`
- L53 _public member_ `int64 Value;`

#### class `Verse::CAttributeFloatValue`  
`class CAttributeFloatValue : public CAttributeValue`  
_L56-66_
- inherits: `CAttributeValue`
- L59 _public function_ `CAttributeFloatValue(double InValue) : CAttributeValue(EAttributeValueType::Float) , Value(InValue)`
- L65 _public member_ `double Value;`

#### class `Verse::CAttributeTypeValue`  
`class CAttributeTypeValue : public CAttributeValue`  
_L68-79_
- inherits: `CAttributeValue`
- L71 _public function_ `CAttributeTypeValue() : CAttributeValue(EAttributeValueType::Type)`
- L76 _public member_ `FString TypeName;`
- L77 _public member_ `FString FullTypeName;`
- L78 _public member_ `TArray<FString> TypeArgs;`

#### class `Verse::CAttributeClassValue`  
`class CAttributeClassValue : public CAttributeValue`  
_L83-93_
- inherits: `CAttributeValue`
- L86 _public function_ `CAttributeClassValue() : CAttributeValue(EAttributeValueType::Class)`
- L91 _public member_ `TSharedPtr<CAttributeTypeValue> ClassType;`
- L92 _public member_ `CAttributeValueMap Value;`

#### class `Verse::CAttributeArrayValue`  
`class CAttributeArrayValue : public CAttributeValue`  
_L95-104_
- inherits: `CAttributeValue`
- L98 _public function_ `CAttributeArrayValue() : CAttributeValue(EAttributeValueType::Array)`
- L103 _public member_ `TArray<TSharedPtr<CAttributeValue>> Value;`

#### class `Verse::CAttributeStringValue`  
`class CAttributeStringValue : public CAttributeValue`  
_L106-116_
- inherits: `CAttributeValue`
- L109 _public function_ `CAttributeStringValue(FString InValue) : CAttributeValue(EAttributeValueType::String) , Value(InValue)`
- L115 _public member_ `FString Value;`

#### struct `Verse::FClassDefinition`  
`struct FClassDefinition`  
_L121-129_
- desc: Structure relating to the definition of a class
- L123 _public function_ `FClassDefinition(UStruct* InClass) : UeClass(InClass)`
- L128 _public member_ `UStruct* UeClass;`

#### struct `Verse::FDataDefinition`  
`struct FDataDefinition`  
_L134-158_
- desc: Structure relating to the definition of a constant
- L143 _public function_ `FDataDefinition(FProperty* InProperty, EKind InKind, bool bInIsAccessibleFromEngineGameplay, bool bInHasNativeRepresentation) : UeProperty(InProperty) , Kind(InKind) , bIsAccessibleFromEngineGameplay(bInIsAccessibleFromEngineGameplay) , bHasNativeRepresentation(bInHasNativeRepresentation)`
- L151 _public member_ `FProperty* UeProperty;`
- L154 _public member_ `EKind Kind;` — What kind of data definition is this?
- L156 _public member_ `uint8 bIsAccessibleFromEngineGameplay : 1;`
- L157 _public member_ `uint8 bHasNativeRepresentation : 1;`

#### enum `Verse::FDataDefinition::EKind`  
`enum class EKind`  
_L137-141_
- desc: Enumeration that specifies the type of an FDefinition, indicating whether it is safe to static_cast to that type or not
- L139 _public enumerator_ `Constant`
- L140 _public enumerator_ `Variable`

#### struct `Verse::FFunctionDefinition`  
`struct FFunctionDefinition`  
_L163-171_
- desc: Structure relating to the definition of a function
- L165 _public function_ `FFunctionDefinition(UFunction* InFunction) : UeFunction(InFunction)`
- L170 _public member_ `UFunction* UeFunction;`

#### struct `Verse::FEnumDefinition`  
`struct FEnumDefinition`  
_L176-184_
- desc: Structure relating to the definition of an enum
- L178 _public function_ `FEnumDefinition(UEnum* InEnum) : UeEnum(InEnum)`
- L183 _public member_ `UEnum* UeEnum;`

#### class `Verse::ICustomAttributeHandler`  
`class ICustomAttributeHandler`  
_L198-223_
- desc: Interface for native processing of Verse Custom Attributes Any Verse attribute that has the attribute @customattribhandler will attempt to call back into native code at UClass construction time, which should be handled by an implementation of this interface. In general, these handlers should be implemented in the native module corresponding to the Verse module that declares the custom attribute. In StartupModule() in that module, the handler should add itself to the AttributeHandlers map, and when UClasses are constructed, any custom attributes with registered names will be processed. When the instance is cleared, the handler is unregistered automatically in the destructor.
- L201 _public typedef_ `using FClassDefinition = Verse::FClassDefinition;`
- L202 _public typedef_ `using FDataDefinition = Verse::FDataDefinition;`
- L203 _public typedef_ `using FFunctionDefinition = Verse::FFunctionDefinition;`
- L204 _public typedef_ `using FEnumDefinition = Verse::FEnumDefinition;`
- L206 _public prototype_ `virtual ~ICustomAttributeHandler();`
- L209 _public prototype_ `static ICustomAttributeHandler* FindHandlerForAttribute(const FName AttributeName);` — Static helper to search for a handler registered for a given custom attribute name
- L215 _public prototype_ `virtual bool ProcessAttribute(const CAttributeValue& Payload, const FClassDefinition& Definition, TArray<FString>& OutErrorMessages);` — Handlers to be implemented by each custom attribute, for each type that custom attributes can be applied to.  Returns false if we were unable to process for the specified name, and implies the linker task will retry again until it succeeds.
- L216 _public prototype_ `virtual bool ProcessAttribute(const CAttributeValue& Payload, const FDataDefinition& Definition, TArray<FString>& OutErrorMessages);`
- L217 _public prototype_ `virtual bool ProcessAttribute(const CAttributeValue& Payload, const FFunctionDefinition& Definition, TArray<FString>& OutErrorMessages);`
- L218 _public prototype_ `virtual bool ProcessAttribute(const CAttributeValue& Payload, const FEnumDefinition& Definition, TArray<FString>& OutErrorMessages);`
- L222 _protected member_ `static TMap<FName, ICustomAttributeHandler*> AttributeHandlers;` — A static map of the name of the custom attribute, to the handler responsible for processing it

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace Verse`
- L81 _typedef_ `using CAttributeValueMap = TMap<FName, TSharedPtr<CAttributeValue>>;` (scope `Verse`)

### `Source/Runtime/CoreUObject/Public/VerseVM/VVMDebugger.h` (Public)


#### struct `Verse::FDebugger`  
`struct FDebugger`  
_L20-27_
- L22 _public prototype_ `virtual ~FDebugger() = default;`
- L23 _public prototype_ `virtual void Notify(FRunningContext, const FOp&, VFrame&, VTask&) = 0;`
- L24 _public prototype_ `virtual void AddLocation(FAllocationContext, VUniqueString& FilePath, const FLocation&) = 0;`
- L25 _public prototype_ `virtual void AddTask(FAccessContext, VTask&) = 0;`
- L26 _public prototype_ `virtual bool HasConnectedClient() = 0;`

#### struct `Verse::Debugger::FFrame`  
`struct FFrame`  
_L37-62_
- L39 _public function_ `explicit FFrame(FAccessContext Context, VUniqueString& Name) : Name`
- L44 _public function_ `explicit FFrame(FAccessContext Context, VUniqueString& Name, VUniqueString& FilePath, FRegisters Registers) : Name`
- L59 _public member_ `TWriteBarrier<VUniqueString> Name;`
- L60 _public member_ `TWriteBarrier<VUniqueString> FilePath;`
- L61 _public member_ `FRegisters Registers;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace Verse`
- L29 _prototype_ `FDebugger* GetDebugger();` (scope `Verse`)
- L31 _prototype_ `void SetDebugger(FDebugger*);` (scope `Verse`)
- L33 _namespace_ `namespace Debugger` (scope `Verse`)
- L35 _typedef_ `using FRegisters = TArray<TTuple<TWriteBarrier<VUniqueString>, VValue>>;` (scope `Verse::Debugger`)
- L52 _function_ `template <typename TVisitor> friend void Visit(TVisitor& Visitor, FFrame& Value)` (scope `Verse::Debugger`)
- L64 _prototype_ `AUTORTFM_DISABLE void ForEachStackFrame( FRunningContext, const FOp*, VFrame*, VTask*, const FNativeFrame*, AUTORTFM_IMPLICIT_DISABLE TFunctionRef<void(const FLocation*, FFrame)>);` (scope `Verse::Debugger`)

### `Source/Runtime/CoreUObject/Public/VerseVM/VVMDebuggerVisitor.h` (Public)


#### struct `Verse::FDebuggerVisitor`  
`struct FDebuggerVisitor`  
_L15-35_
- L19 _public prototype_ `virtual ~FDebuggerVisitor() = default;`
- L21 _public prototype_ `virtual void VisitArray(TFunctionRef<void()> VisitElements) = 0;`
- L23 _public prototype_ `virtual void VisitMap(TFunctionRef<void()> VisitElements) = 0;`
- L25 _public prototype_ `virtual void VisitOption(TFunctionRef<void()> VisitElement) = 0;`
- L27 _public prototype_ `virtual void VisitObject(TFunctionRef<void()> VisitFields) = 0;`
- L29 _public prototype_ `virtual void Visit(VValue Value, FUtf8StringView ElementName) = 0;`
- L31 _public prototype_ `virtual void Visit(const FOpResult& Value, FUtf8StringView ElementName) = 0;`
- L34 _protected prototype_ `FDebuggerVisitor() = default;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace Verse`

### `Source/Runtime/CoreUObject/Public/VerseVM/VVMDuplication.h` (Public)


#### struct `Verse::FDuplicationContext`  
`struct FDuplicationContext`  
_L19-63_
- desc: This class holds VCell-related state shared across the whole cloning operation, so that the shape of the reference graph can be reproduced correctly.
- L23 _public prototype_ `void WriteCellReference(VCell* Cell);` — Record a VCell's presence and dependency information in the old object graph.
- L25 _public prototype_ `void WriteUnserializedCells(FAllocationContext Context, FArchive& Writer);` — Write out the contents of discovered VCells. May discover more UObject references.
- L28 _public prototype_ `void CreateSerializedCells(FAllocationContext Context, FArchive& Reader);` — Populate the new object graph's VCells. Call after the whole graph has been written.
- L31 _public prototype_ `VCell* ReadCellReference(VCell* SourceCell);` — Remap a VCell reference to its equivalent in the new object graph.
- L33 _public prototype_ `void ReadSerializedCells(FAllocationContext Context, FArchive& Reader);` — Read in the contents of the new object graph's VCells. Must be prepared to remap UObject references.
- L36 _private prototype_ `TArray<int32> TopologicalSortCells();`
- L37 _private prototype_ `void GatherCellDependencies(int32 SerializedIndex, TBitArray<>& Visited, TArray<int32>& OutOrder);`
- L55 _private member_ `TMap<VCell*, FDuplicatedCell> DuplicatedCells;` — Map of VCells in the old object graph to their equivalent in the new object graph.
- L57 _private member_ `TArray<VCell*> UnserializedCells;` — Pending stack of VCells that have been discovered but not yet written.
- L60 _private member_ `TArray<FSerializedCell> SerializedCells;` — Index of serialized VCell contents and dependencies.
- L61 _private member_ `TArray<VCell*> ReferencedCells;`

#### struct `Verse::FDuplicationContext::FDuplicatedCell`  
`struct FDuplicatedCell`  
_L39-43_
- L41 _public member_ `VCell* DuplicatedCell = nullptr;`
- L42 _public member_ `int32 SerializedIndex = INDEX_NONE;`

#### struct `Verse::FDuplicationContext::FSerializedCell`  
`struct FSerializedCell`  
_L45-52_
- L47 _public member_ `VCell* Cell;`
- L48 _public member_ `int64 LayoutOffset;`
- L49 _public member_ `int64 Offset;`
- L50 _public member_ `int32 ReferencesBegin;`
- L51 _public member_ `int32 ReferencesEnd;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace Verse`

### `Source/Runtime/CoreUObject/Public/VerseVM/VVMEmergentType.h` (Public)


#### struct `Verse::VEmergentType`  
`struct VEmergentType final : VCell`  
_L18-115_
- inherits: `VCell`
- L22 _public member_ `TWriteBarrier<VShape> Shape;` — This is immutable. If you need to change an object's shape, transition to a new emergent type that points to your new shape instead.
- L23 _public member_ `TWriteBarrier<VType> Type;`
- L24 _public member_ `TWriteBarrier<VEmergentType> MeltTransition;`
- L25 _public member_ `VCppClassInfo* CppClassInfo = nullptr;`
- L28 _public member_ `VBitMap CreatedFields;` — We use this to track what fields have been created for objects
- L31 _public member_ `TWriteBarrier<VMap> CachedFieldTransitions;` — A cache of types made when calling `MarkFieldAsCreated`
- L33 _public function_ `AUTORTFM_DISABLE static VEmergentType* New(FAllocationContext Context, VType* Type, VCppClassInfo* CppClassInfo)`
- L38 _public function_ `AUTORTFM_DISABLE static VEmergentType* New(FAllocationContext Context, VShape* InShape, VType* Type, VCppClassInfo* CppClassInfo)`
- L43 _public function_ `AUTORTFM_DISABLE static VEmergentType* New(FAllocationContext Context, const VEmergentType* Other, const VBitMap* InCreatedFields)`
- L48 _public function_ `AUTORTFM_DISABLE VEmergentType& GetOrCreateMeltTransition(FAllocationContext Context)`
- L57 _public function_ `static bool Equals(const VEmergentType& EmergentType, VType* Type, VCppClassInfo* CppClassInfo)`
- L62 _public function_ `static bool Equals(const VEmergentType& EmergentType, const VShape* InShape, VType* Type, VCppClassInfo* CppClassInfo)`
- L67 _public prototype_ `AUTORTFM_DISABLE static bool Equals(FAllocationContext Context, const VEmergentType& EmergentType, const VEmergentType* Other, const VBitMap* InCreatedFields);`
- L77 _public prototype_ `bool IsFieldCreated(uint32 FieldIndex);`
- L78 _public prototype_ `AUTORTFM_DISABLE VEmergentType* MarkFieldAsCreated(FAllocationContext Context, uint32 FieldIndex);`
- L81 _public member_ `static constexpr bool SerializeIdentity = false;` — Emergent types are not serialized; this also prevents them from being recorded.
- L87 _private function_ `AUTORTFM_DISABLE static VEmergentType* NewIncomplete(FAllocationContext Context, VCppClassInfo* CppClassInfo)` — Need this for the EmergentType of EmergentType.
- L92 _private prototype_ `AUTORTFM_DISABLE VEmergentType& GetOrCreateMeltTransitionSlow(FAllocationContext);`
- L94 _private function_ `void SetEmergentType(FAccessContext Context, VEmergentType* EmergentType)`
- L99 _private function_ `AUTORTFM_DISABLE VEmergentType(FAllocationContext Context, VCppClassInfo* CppClassInfo) : VCell() , CppClassInfo(CppClassInfo)`
- L105 _private function_ `AUTORTFM_DISABLE VEmergentType(FAllocationContext Context, VEmergentType* EmergentType, VType* T, VCppClassInfo* CppClassInfo) : VCell(Context, EmergentType) , Type(Context, T) , CppClassInfo(CppClassInfo)`
- L112 _private prototype_ `AUTORTFM_DISABLE VEmergentType(FAllocationContext Context, VShape* InShape, VEmergentType* EmergentType, VType* InType, VCppClassInfo* InCppClassInfo);`
- L114 _private prototype_ `AUTORTFM_DISABLE VEmergentType(FAllocationContext Context, const VEmergentType* Other, const VBitMap* InCreatedFields);`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace Verse`
- L69 _function_ `friend uint32 GetTypeHash(const VEmergentType& EmergentType)` (scope `Verse`)

### `Source/Runtime/CoreUObject/Public/VerseVM/VVMEmergentTypeCreator.h` (Public)


#### class `Verse::VEmergentTypeCreator`  
`class VEmergentTypeCreator`  
_L27-41_
- desc: Get/creates hash constructed emergent types.
- L29 _private member_ `static TLazyInitialized<VUniqueCreator<VEmergentType>> UniqueCreator;`
- L30 _private member_ `static bool bIsInitialized;`
- L32 _private prototype_ `VEmergentTypeCreator() = delete;`
- L35 _public prototype_ `AUTORTFM_DISABLE static void Initialize(FAllocationContext Context);`
- L36 _public prototype_ `AUTORTFM_DISABLE static VEmergentType* GetOrCreate(FAllocationContext Context, VType* Type, VCppClassInfo* CppClassInfo);`
- L37 _public prototype_ `AUTORTFM_DISABLE static VEmergentType* GetOrCreate(FAllocationContext Context, VShape* InShape, VType* Type, VCppClassInfo* CppClassInfo);`
- L39 _public member_ `static TGlobalHeapPtr<VEmergentType> EmergentTypeForEmergentType;`
- L40 _public member_ `static TGlobalHeapPtr<VEmergentType> EmergentTypeForTrivialType;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace Verse`

### `Source/Runtime/CoreUObject/Public/VerseVM/VVMEngineEnvironment.h` (Public)


#### class `Verse::IEngineEnvironment`  
`class IEngineEnvironment`  
_L41-84_
- desc: This interface must be implemented if Verse needs to create UObject instances.
- L46 _public prototype_ `virtual void AddPersistentVars(UObject* Object, const TArray<FVersePersistentVar>& Vars) = 0;` — Add persistent vars
- L49 _public prototype_ `virtual TSharedRef<IVersePersistence> GetPersistence() = 0;`
- L52 _public prototype_ `virtual bool FitsInPlayerMap(VValue Value) = 0;`
- L54 _public prototype_ `virtual bool IsValidWeakMapKey(VValue Value) = 0;`
- L58 _public prototype_ `virtual void AddSessionVars(UObject* Object, const TArray<FVerseSessionVar>& Vars) = 0;` — Add session vars
- L60 _public prototype_ `virtual void ArchiveType(FStructuredArchive::FSlot Slot, UE::Verse::FRuntimeType*& Type) = 0;`
- L61 _public prototype_ `virtual UE::Verse::FRuntimeType* ImportRuntimeTypeFromText(const TCHAR*& InputCursor, FOutputDevice* ErrorText) = 0;`
- L62 _public prototype_ `virtual void ExportRuntimeTypeToText(FString& OutputString, UE::Verse::FRuntimeType& Type) = 0;`
- L65 _public prototype_ `virtual void TryBindVniType(UField* Type) = 0;`
- L69 _public prototype_ `virtual FProperty* CreateProperty(FAllocationContext Context, UPackage* Package, UStruct* Struct, FUtf8StringView PropertyName, FUtf8StringView CRCPropertyName, VValue Type, bool bIsNative, bool bIsInstanced) = 0;` — Create a property
- L70 _public prototype_ `virtual FProperty* CreateLegacyProperty(FAllocationContext Context, FVRestValueProperty* Property) = 0;`
- L73 _public prototype_ `virtual bool ValidateProperty(FAllocationContext Context, const FName& Name, VType* Type, const FProperty* ExistingProperty, bool bIsNative, bool bIsInstanced) = 0;` — Validate property information during code generation
- L76 _public prototype_ `virtual void TryBindVniType(VPackage* Scope, UStruct* Struct) = 0;` — Bind a native structure
- L79 _public prototype_ `virtual void TryBindVniModule(VPackage* Scope, const FTopLevelAssetPath& Path) = 0;` — Bind a native module
- L82 _public prototype_ `virtual UPackage* CreateUPackage(FAllocationContext Context, const TCHAR* PackageName) = 0;` — Create a new UPackage with the given package name

#### Free symbols / members of external scopes

- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace Verse` (scope `UE`)
- L22 _namespace_ `namespace uLang`
- L29 _namespace_ `namespace Verse`

### `Source/Runtime/CoreUObject/Public/VerseVM/VVMEnsureStillAlive.h` (Public)


#### Free symbols / members of external scopes

- L9 _namespace_ `namespace Verse`
- L12 _function_ `inline void EnsureStillAliveHere(const void* Pointer)` (scope `Verse`)

### `Source/Runtime/CoreUObject/Public/VerseVM/VVMEnumeration.h` (Public)


#### struct `Verse::VEnumeration`  
`struct VEnumeration : VNamedType`  
_L21-64_
- inherits: `VNamedType`
- L24 _public member_ `static TGlobalTrivialEmergentTypePtr<&StaticCppClassInfo> GlobalTrivialEmergentType;`
- L26 _public member_ `int32 NumEnumerators;`
- L29 _public prototype_ `VEnumerator& GetEnumeratorChecked(int32 IntValue) const;` — Find enumerator for a given int value
- L31 _public prototype_ `VEnumerator* GetEnumerator(const VUniqueString& Name) const;`
- L34 _public prototype_ `template <class SubTypeOfUStruct> SubTypeOfUStruct* GetOrCreateUEType(FAllocationContext Context);`
- L46 _public prototype_ `AUTORTFM_DISABLE static VEnumeration& New(FAllocationContext Context, VPackage* Package, VArray* RelativePath, VArray* EnumName, VArray* AttributeIndices, VArray* Attributes, UEnum* ImportEnum, bool bNative, const TArray<VEnumerator*>& Enumerators);` — Creates a new enumeration. @param Scope         Containing package or null. @param Name          Name or null. @param UEMangledName Name to be used when creating the UE version of the class or the UE package.  Can be null. @param ImportStruct  The Unreal class/struct that is being reflected by this Verse VM type. @param bNative       `true` if this represents a native class (i.e. defined in C++). @param Enumerators   The members of this enumeration.
- L48 _public prototype_ `AUTORTFM_DISABLE static void SerializeLayout(FAllocationContext Context, VEnumeration*& This, FStructuredArchiveVisitor& Visitor);`
- L49 _public prototype_ `AUTORTFM_DISABLE void SerializeImpl(FAllocationContext Context, FStructuredArchiveVisitor& Visitor);`
- L51 _public prototype_ `AUTORTFM_DISABLE TSharedPtr<FJsonValue> ToJSONImpl(FRunningContext, EValueJSONFormat, TMap<const void*, EVisitState>& VisitedObjects, FToJsonCallback, uint32 RecursionDepth, FJsonObject* Defs);`
- L52 _public prototype_ `AUTORTFM_DISABLE VValue FromJSONImpl(FRunningContext, const FJsonValue&, EValueJSONFormat, FFromJsonCallback);`
- L55 _private prototype_ `AUTORTFM_DISABLE VEnumeration(FAllocationContext Context, VPackage* InPackage, VArray* InRelativePath, VArray* InEnumName, VArray* InAttributeIndices, VArray* InAttributes, UEnum* InImportEnum, bool bInNative, const TArray<VEnumerator*>& InEnumerators);`
- L56 _private prototype_ `AUTORTFM_DISABLE VEnumeration(FAllocationContext Context, int32 InNumEnumerators);`
- L59 _private prototype_ `UEnum* CreateUEType(FAllocationContext Context);` — Creates an associated UEnum for this VEnumeration
- L61 _private prototype_ `void Prepare(const FInitOrValidateUVerseEnum& InitOrValidate);`
- L63 _private member_ `TWriteBarrier<VEnumerator> Enumerators[];`
- L67 _function_ `template <class SubTypeOfUEnum> inline SubTypeOfUEnum* VEnumeration::GetOrCreateUEType(FAllocationContext Context)`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace Verse`
- L19 _prototype_ `template <typename CppEnumType> VEnumeration& StaticVEnumeration();` (scope `Verse`)

### `Source/Runtime/CoreUObject/Public/VerseVM/VVMEnumerator.h` (Public)


#### struct `Verse::VEnumerator`  
`struct VEnumerator : VHeapValue`  
_L18-62_
- inherits: `VHeapValue`
- L21 _public member_ `static TGlobalTrivialEmergentTypePtr<&StaticCppClassInfo> GlobalTrivialEmergentType;`
- L23 _public function_ `int32 GetIntValue() const`
- L25 _public function_ `void SetEnumeration(FAccessContext Context, VEnumeration* InEnumeration)`
- L30 _public function_ `VEnumeration* GetEnumeration() const`
- L34 _public function_ `VUniqueString* GetName() const`
- L39 _public function_ `static VEnumerator& New(FAllocationContext Context, VUniqueString* InName, int32 IntValue)`
- L44 _public prototype_ `AUTORTFM_DISABLE void AppendToStringImpl(FAllocationContext Context, FUtf8StringBuilderBase& Builder, EValueStringFormat Format, TSet<const void*>& VisitedObjects, uint32 RecursionDepth);`
- L45 _public prototype_ `TSharedPtr<FJsonValue> ToJSONImpl(FRunningContext, EValueJSONFormat, TMap<const void*, EVisitState>& VisitedObjects, FToJsonCallback, uint32 RecursionDepth, FJsonObject* Defs);`
- L46 _public prototype_ `AUTORTFM_DISABLE static void SerializeLayout(FAllocationContext Context, VEnumerator*& This, FStructuredArchiveVisitor& Visitor);`
- L47 _public prototype_ `AUTORTFM_DISABLE void SerializeImpl(FAllocationContext Context, FStructuredArchiveVisitor& Visitor);`
- L50 _private prototype_ `uint32 GetTypeHashImpl();`
- L52 _private function_ `VEnumerator(FAllocationContext Context, VUniqueString* InName, int32 InIntValue) : VHeapValue(Context, &GlobalTrivialEmergentType.Get(Context)) , Name(Context, InName) , IntValue(InIntValue)`
- L59 _private member_ `TWriteBarrier<VEnumeration> Enumeration;`
- L60 _private member_ `TWriteBarrier<VUniqueString> Name;`
- L61 _private member_ `int32 IntValue;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace Verse`

### `Source/Runtime/CoreUObject/Public/VerseVM/VVMExecutionContext.h` (Public)


#### struct `verse::FExecutionContextImpl`  
`struct FExecutionContextImpl`  
_L16-29_
- L21 _private prototype_ `FExecutionContextImpl() = default;`
- L23 _private prototype_ `static FExecutionContextImpl* Claim();`
- L24 _private prototype_ `void Release();`
- L26 _private prototype_ `static FExecutionContextImpl* GetCurrent();`
- L28 _private member_ `bool bActive = false;`

#### struct `verse::FExecutionContext`  
`struct FExecutionContext`  
_L33-95_
- desc: A thread must have an active execution context to run Verse code.
- L35 _public function_ `FExecutionContext(const FExecutionContext& Other) : Impl(Other.Impl)`
- L42 _public function_ `static FExecutionContext Create()`
- L49 _public function_ `static FExecutionContext GetActiveContext()`
- L60 _public function_ `::Verse::FRunningContext GetContext()`
- L66 _public function_ `static bool SetBlockExecution(bool ShouldBlock)`
- L72 _public function_ `static bool IsExecutionBlocked()`
- L76 _private function_ `explicit FExecutionContext(FExecutionContextImpl* InImpl) : Impl(InImpl)`
- L88 _private member_ `static bool bBlockAllExecution;`
- L91 _private member_ `FExecutionContextImpl* Impl;`

#### struct `verse::FEnsureGameThreadScope`  
`struct FEnsureGameThreadScope`  
_L100-106_
- desc: Verse bytecode and AutoRTFM transactions must run on the game thread. Construct an FEnsureGameThreadScope to `ensure` that it is safe to run Verse.
- L102 _public member_ `bool bOriginalValue;`
- L104 _public prototype_ `FEnsureGameThreadScope();`
- L105 _public prototype_ `~FEnsureGameThreadScope();`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace verse`

### `Source/Runtime/CoreUObject/Public/VerseVM/VVMFailureContext.h` (Public)


#### struct `Verse::VFailureContext`  
`struct AUTORTFM_DISABLE VFailureContext : VCell , TIntrusiveTree<VFailureContext>`  
_L24-146_
- inherits: `VCell,TIntrusiveTree<VFailureContext>`
- L28 _public member_ `static TGlobalTrivialEmergentTypePtr<&StaticCppClassInfo> GlobalTrivialEmergentType;`
- L41 _public member_ `TWriteBarrier<VTask> Task;` — Used to restore state when failure is encountered in *this* failure context.
- L42 _public member_ `TWriteBarrier<VFrame> Frame;`
- L43 _public member_ `TWriteBarrier<VValue> IncomingEffectToken;` — Used to restore the effect token when failure is encountered. Used both during lenient and non-lenient execution.
- L44 _public member_ `TWriteBarrier<VBatchedRefs> BatchedRefs;`
- L45 _public member_ `FOp* FailurePC;`
- L48 _public member_ `VRestValue BeforeThenEffectToken{0};` — These fields are used during lenient execution.
- L49 _public member_ `VRestValue DoneEffectToken{0};`
- L50 _public member_ `FOp* ThenPC{nullptr};`
- L51 _public member_ `FOp* DonePC{nullptr};`
- L53 _public member_ `uint32 SuspensionCount{0};`
- L54 _public member_ `bool bFailed{false};`
- L55 _public member_ `bool bExecutedEndFailureContextOpcode{false};`
- L56 _public member_ `FTrail Trail;`
- L57 _public member_ `FTransaction Transaction;`
- L59 _public function_ `static VFailureContext& New( FAllocationContext Context, VTask* Task, VFailureContext* Parent, VFrame& Frame, VValue IncomingEffectToken, VBatchedRefs* BatchedRefs, FOp* FailurePC)`
- L78 _public function_ `void FinishedExecuting(FAllocationContext Context)`
- L84 _public function_ `template <FTransaction::EAbortMode AbortMode = FTransaction::EAbortMode::Default> void Fail(FAccessContext Context)`
- L128 _public function_ `VFailureContext( FAllocationContext Context, VTask* Task, VFailureContext* Parent, VFrame& Frame, VValue IncomingEffectToken, VBatchedRefs* BatchedRefs, FOp* FailurePC) : VCell(Context, &GlobalTrivialEmergentType.Get(Context)) , TIntrusiveTree(Context, Parent) , Task(Context, Task) , Frame(Context, Frame) , IncomingEffectToken(Context, IncomingEffectToken) , BatchedRefs(Context, BatchedRefs) , FailurePC(FailurePC) , Trail(Parent ? &Parent->Trail : nullptr)`

#### Free symbols / members of external scopes

- L20 _namespace_ `namespace Verse`
- L106 _function_ `ForEachInPreOrder([&](VFailureContext& FailureContext) { PreOrder.Push(&FailureContext.Trail); if (FailureContext.Transaction.IsActive()) { ++NumActiveTransactions; } FailureContext.bFailed = true; });` (scope `Verse::VFailureContext::Fail`)

### `Source/Runtime/CoreUObject/Public/VerseVM/VVMFalse.h` (Public)


#### struct `Verse::VFalse`  
`struct VFalse : VType`  
_L17-40_
- inherits: `VType`
- L20 _public member_ `static TGlobalTrivialEmergentTypePtr<&StaticCppClassInfo> GlobalTrivialEmergentType;`
- L22 _public prototype_ `AUTORTFM_DISABLE static void InitializeGlobals(FAllocationContext Context);`
- L24 _public prototype_ `AUTORTFM_DISABLE void AppendToStringImpl(FAllocationContext Context, FUtf8StringBuilderBase& Builder, EValueStringFormat Format, TSet<const void*>& VisitedObjects, uint32 RecursionDepth);`
- L26 _public member_ `static constexpr bool SerializeIdentity = false;`
- L27 _public prototype_ `AUTORTFM_DISABLE static void SerializeLayout(FAllocationContext Context, VFalse*& This, FStructuredArchiveVisitor& Visitor);`
- L28 _public prototype_ `AUTORTFM_DISABLE void SerializeImpl(FAllocationContext Context, FStructuredArchiveVisitor& Visitor);`
- L31 _private function_ `AUTORTFM_DISABLE VFalse(FAllocationContext Context) : VType(Context, &GlobalTrivialEmergentType.Get(Context))`
- L36 _private function_ `AUTORTFM_DISABLE static VFalse& New(FAllocationContext Context)`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace Verse`
- L42 _externvar_ `extern TGlobalHeapPtr<VFalse> GlobalFalsePtr;` (scope `Verse`)
- L43 _externvar_ `extern TGlobalHeapPtr<VOption> GlobalTruePtr;` (scope `Verse`)
- L46 _function_ `inline VOption& GlobalTrue()` (scope `Verse`) — True is represented as VOption(VFalse)
- L51 _function_ `inline VFalse& GlobalFalse()` (scope `Verse`)

### `Source/Runtime/CoreUObject/Public/VerseVM/VVMFloatPrinting.h` (Public)


#### enum `Verse::EFloatStringFormat`  
`enum class EFloatStringFormat`  
_L11-15_
- L13 _public enumerator_ `Legacy` — Reproduces the legacy behavior of Verse's ToString function, which is equivalent to printf("%f", Float).
- L14 _public enumerator_ `ShortestOfFixedOrScientific`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace Verse`
- L17 _prototype_ `void AppendDecimalToString(FUtf8StringBuilderBase& Builder, VFloat Float, EFloatStringFormat Format = EFloatStringFormat::ShortestOfFixedOrScientific);` (scope `Verse`)

### `Source/Runtime/CoreUObject/Public/VerseVM/VVMFloatStateSaveRestore.h` (Public)


#### class `Verse::FFloatStateSaveRestoreGuard`  
`class FFloatStateSaveRestoreGuard final`  
_L14-26_
- desc: Scope guard that saves current FP state (rounding mode, flush-to-zero etc.) and puts us into fully IEEE compliant mode for the duration of the scope.
- L17 _public prototype_ `FFloatStateSaveRestoreGuard();`
- L18 _public prototype_ `~FFloatStateSaveRestoreGuard();`
- L22 _private member_ `uint32 SavedState;` — The relevant control register is 32-bit on all current targets.
- L25 _private member_ `bool bWasSet;` — If we actually had to write the control register during construction.

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace Verse`

### `Source/Runtime/CoreUObject/Public/VerseVM/VVMFloatType.h` (Public)


#### struct `Verse::VFloatType`  
`struct VFloatType : VType`  
_L15-64_
- inherits: `VType`
- desc: An float type with constraints.
- L18 _public member_ `static TGlobalTrivialEmergentTypePtr<&StaticCppClassInfo> GlobalTrivialEmergentType;`
- L20 _public function_ `static VFloatType& New(FAllocationContext Context, VFloat InMin, VFloat InMax)`
- L24 _public function_ `static bool Equals(const VType& Type, VFloat Min, VFloat Max)`
- L34 _public function_ `const VFloat& GetMin() const`
- L39 _public function_ `const VFloat& GetMax() const`
- L44 _public prototype_ `bool SubsumesImpl(FAllocationContext Context, VValue);`
- L46 _public prototype_ `AUTORTFM_DISABLE void AppendToStringImpl(FAllocationContext Context, FUtf8StringBuilderBase& Builder, EValueStringFormat Format, TSet<const void*>& VisitedObjects, uint32 RecursionDepth);`
- L47 _public prototype_ `TSharedPtr<FJsonValue> ToJSONImpl(FRunningContext, EValueJSONFormat, TMap<const void*, EVisitState>& VisitedObjects, FToJsonCallback, uint32 RecursionDepth, FJsonObject* Defs);`
- L48 _public prototype_ `VValue FromJSONImpl(FRunningContext, const FJsonValue&, EValueJSONFormat, FFromJsonCallback);`
- L50 _public member_ `static constexpr bool SerializeIdentity = false;`
- L51 _public prototype_ `AUTORTFM_DISABLE static void SerializeLayout(FAllocationContext Context, VFloatType*& This, FStructuredArchiveVisitor& Visitor);`
- L52 _public prototype_ `AUTORTFM_DISABLE void SerializeImpl(FAllocationContext, FStructuredArchiveVisitor& Visitor);`
- L55 _private function_ `explicit VFloatType(FAllocationContext& Context, VFloat InMin, VFloat InMax) : VType(Context, &GlobalTrivialEmergentType.Get(Context)) , Min(InMin) , Max(InMax)`
- L62 _private member_ `VFloat Min;`
- L63 _private member_ `VFloat Max;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace Verse`

### `Source/Runtime/CoreUObject/Public/VerseVM/VVMFrame.h` (Public)


#### struct `Verse::VFrame`  
`struct VFrame : VCell`  
_L20-89_
- inherits: `VCell`
- L23 _public member_ `static TGlobalTrivialEmergentTypePtr<&StaticCppClassInfo> GlobalTrivialEmergentType;`
- L25 _public member_ `FOp* CallerPC{nullptr};`
- L26 _public member_ `TWriteBarrier<VFrame> CallerFrame;`
- L27 _public member_ `VReturnSlot ReturnSlot;`
- L29 _public member_ `TWriteBarrier<VProcedure> Procedure;`
- L30 _public member_ `const uint32 NumRegisters;`
- L31 _public member_ `VRestValue Registers[];`
- L33 _public member_ `static TGlobalHeapPtr<VFrame> GlobalEmptyFrame;`
- L35 _public prototype_ `AUTORTFM_DISABLE void GetStackDescription(FStringBuilderBase& StringBuilder, const FOp* PC) const;`
- L38 _public function_ `template <typename ReturnSlotType> AUTORTFM_DISABLE static VFrame& New(FAllocationContext Context, FOp* CallerPC, VFrame* CallerFrame, ReturnSlotType ReturnSlot, VProcedure& Procedure)`
- L44 _public function_ `AUTORTFM_DISABLE VFrame& CloneWithoutCallerInfo(FAllocationContext Context)`
- L49 _public prototype_ `AUTORTFM_DISABLE static void InitializeGlobals(FAllocationContext Context);`
- L52 _private function_ `AUTORTFM_DISABLE static VFrame& New(FAllocationContext Context, VFrame& Other)`
- L58 _private function_ `template <typename ReturnSlotType> AUTORTFM_DISABLE VFrame(FAllocationContext Context, FOp* CallerPC, VFrame* CallerFrame, ReturnSlotType ReturnSlot, VProcedure& Procedure) : VCell(Context, &GlobalTrivialEmergentType.Get(Context)) , CallerPC(CallerPC) , CallerFrame(Context, CallerFrame) , ReturnSlot(Context, ReturnSlot) , Procedure(Context, Procedure) , NumRegisters(Procedure.NumRegisters)`
- L75 _private function_ `AUTORTFM_DISABLE VFrame(FAllocationContext Context, VFrame& Other) : VCell(Context, &GlobalTrivialEmergentType.Get(Context)) , ReturnSlot(Context, Other.ReturnSlot.Get(Context)) , Procedure(Context, Other.Procedure.Get()) , NumRegisters(Other.NumRegisters)` — We don't copy the CallerFrame/CallerPC because during lenient execution this won't return to the caller.

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace Verse`

### `Source/Runtime/CoreUObject/Public/VerseVM/VVMFromJsonCallback.h` (Public)


#### Free symbols / members of external scopes

- L11 _namespace_ `namespace Verse`
- L17 _typedef_ `using FFromJsonCallback = TFunctionRef<VValue( FRunningContext, const FJsonValue&, VType&)>;` (scope `Verse`)

### `Source/Runtime/CoreUObject/Public/VerseVM/VVMFunction.h` (Public)


#### struct `Verse::VFunction`  
`struct VFunction : VHeapValue`  
_L19-86_
- inherits: `VHeapValue`
- L22 _public member_ `static TGlobalTrivialEmergentTypePtr<&StaticCppClassInfo> GlobalTrivialEmergentType;`
- L24 _public typedef_ `using Args = TArray<VValue, TInlineAllocator<8>>;`
- L27 _public member_ `TWriteBarrier<VValue> Procedure;` — Either a VProcedure or a VNativeProcedure.
- L32 _public member_ `TWriteBarrier<VValue> Self;` — If specified, the object instance that this function belongs to. Can either be a `VObject` or a `UObject`. When not bound, this should be an uninitialized `VValue` for methods and `VFalse` for functions. This is so we can differentiate between when we should bind `Self` lazily at runtime for calls to methods.
- L35 _public member_ `TWriteBarrier<VScope> ParentScope;` — The lexical scope that this function is allocated with. This includes all lexical captures, including `(super:)`.
- L37 _public function_ `AUTORTFM_DISABLE V_FORCEINLINE FOpResult Invoke(FRunningContext Context, VValue Argument, TWriteBarrier<VUniqueString>* NamedArg = nullptr)`
- L41 _public function_ `AUTORTFM_DISABLE V_FORCEINLINE FOpResult Invoke(FRunningContext Context, Args&& Arguments, TArrayView<TWriteBarrier<VUniqueString>> NamedArgs = {}, TArrayView<VValue> NamedArgVals = {})`
- L45 _public prototype_ `AUTORTFM_DISABLE FOpResult InvokeWithSelf(FRunningContext Context, VValue Self, VValue Argument, TWriteBarrier<VUniqueString>* NamedArg = nullptr);`
- L46 _public prototype_ `AUTORTFM_DISABLE FOpResult InvokeWithSelf(FRunningContext Context, VValue Self, Args&& Arguments, TArrayView<TWriteBarrier<VUniqueString>> NamedArgs = {}, TArrayView<VValue> NamedArgVals = {}, bool bRequireConcreteEffectToken = true);`
- L47 _public prototype_ `AUTORTFM_DISABLE FOpResult Spawn(FRunningContext Context, Args&& Arguments, TArrayView<TWriteBarrier<VUniqueString>> NamedArgs = {}, TArrayView<VValue> NamedArgVals = {});`
- L49 _public function_ `AUTORTFM_DISABLE static VFunction& New(FAllocationContext Context, VValue Procedure, VValue Self, VScope* ParentScope = nullptr)`
- L56 _public function_ `AUTORTFM_DISABLE static VFunction& NewUnbound(FAllocationContext Context, VValue Procedure, VScope& InScope)` — Use this when you're constructing a function where you passing captures to it for its lexical scope - i.e. a method that binds `Self` lazily at runtime, but captures `(super:)` in its current scope.
- L61 _public function_ `AUTORTFM_DISABLE VFunction& Bind(FAllocationContext Context, VValue InSelf)`
- L69 _public prototype_ `bool HasSelf() const;` — Checks if the function is already bound.
- L71 _public prototype_ `AUTORTFM_DISABLE void AppendToStringImpl(FAllocationContext Context, FUtf8StringBuilderBase& Builder, EValueStringFormat Format, TSet<const void*>& VisitedObjects, uint32 RecursionDepth);`
- L73 _public prototype_ `AUTORTFM_DISABLE static void SerializeLayout(FAllocationContext Context, VFunction*& This, FStructuredArchiveVisitor& Visitor);`
- L74 _public prototype_ `AUTORTFM_DISABLE void SerializeImpl(FAllocationContext Context, FStructuredArchiveVisitor& Visitor);`
- L76 _public member_ `static constexpr bool InstancedCell = true;`
- L79 _private function_ `AUTORTFM_DISABLE VFunction(FAllocationContext Context, VValue InProcedure, VValue InSelf, VScope* InParentScope) : VHeapValue(Context, &GlobalTrivialEmergentType.Get(Context)) , Procedure(Context, InProcedure) , Self(Context, InSelf) , ParentScope(Context, InParentScope)`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace Verse`

### `Source/Runtime/CoreUObject/Public/VerseVM/VVMGlobalHeapCensusRoot.h` (Public)


#### struct `Verse::FGlobalHeapCensusRoot`  
`struct FGlobalHeapCensusRoot`  
_L20-25_
- desc: If you have a class that is meant to be used exclusively globally and has weak references, then subclass this to give that class the ability to conduct census and clear those references. Never use this for things that aren't truly global. It's fine to have classes subclass both FGLobalHeapRoot (for strong references) and FGLobalHeapCensusRoot (for weak references).
- L22 _public prototype_ `FGlobalHeapCensusRoot();`
- L24 _public prototype_ `virtual void ConductCensus() = 0;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace Verse`

### `Source/Runtime/CoreUObject/Public/VerseVM/VVMGlobalHeapPtr.h` (Public)


#### struct `Verse::TGlobalHeapPtrImpl`  
`template <typename T> struct TGlobalHeapPtrImpl : FGlobalHeapRoot , TWriteBarrier<T>`  
_L18-38_
- inherits: `FGlobalHeapRoot,TWriteBarrier<T>`
- L21 _public prototype_ `TGlobalHeapPtrImpl() = default;`
- L23 _public function_ `TGlobalHeapPtrImpl(FAccessContext Context, typename TWriteBarrier<T>::TValue Value) : FGlobalHeapRoot() , TWriteBarrier<T>(Context, Value)`
- L29 _public function_ `void Visit(FMarkStackVisitor& Visitor) override`
- L30 _public function_ `void Visit(FAbstractVisitor& Visitor) override`
- L33 _public function_ `template <class VisitorType> void VisitImpl(VisitorType& Visitor)`

#### struct `Verse::TGlobalHeapPtr`  
`template <typename T> struct TGlobalHeapPtr`  
_L41-79_
- L43 _public member_ `static constexpr bool bIsVValue = std::is_same_v<T, VValue>;`
- L44 _public typedef_ `using TValue = typename std::conditional<bIsVValue, VValue, T*>::type;`
- L46 _public prototype_ `TGlobalHeapPtr() = default;`
- L48 _public prototype_ `TGlobalHeapPtr(const TGlobalHeapPtr&) = delete;`
- L49 _public prototype_ `TGlobalHeapPtr& operator=(const TGlobalHeapPtr&) = delete;`
- L50 _public prototype_ `TGlobalHeapPtr(TGlobalHeapPtr&&) = delete;`
- L51 _public prototype_ `TGlobalHeapPtr& operator=(TGlobalHeapPtr&&) = delete;`
- L53 _public function_ `void Set(FAccessContext Context, TValue NewValue)`
- L59 _public function_ `template <typename TResult = void> std::enable_if_t<bIsVValue, TResult> SetNonCellNorPlaceholder(VValue NewValue)`
- L64 _public function_ `TValue Get() const`
- L70 _public function_ `template <typename TResult = TValue> std::enable_if_t<!bIsVValue, TResult> operator->() const`
- L73 _public function_ `template <typename TResult = T> std::enable_if_t<!bIsVValue, TResult&> operator*() const`
- L75 _public function_ `explicit operator bool() const`
- L78 _private member_ `TLazyInitialized<TGlobalHeapPtrImpl<T>> Impl;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace Verse`

### `Source/Runtime/CoreUObject/Public/VerseVM/VVMGlobalHeapRoot.h` (Public)


#### struct `Verse::FGlobalHeapRoot`  
`struct FGlobalHeapRoot`  
_L18-25_
- desc: If you have a class that is meant to be used exclusively for global variables (like TUniqueConstructor), then subclass this to give that class the ability to mark its referenced cells. Never use this for things that aren't truly global.
- L20 _public prototype_ `FGlobalHeapRoot();`
- L21 _public prototype_ `virtual ~FGlobalHeapRoot() = default;`
- L23 _public prototype_ `virtual void Visit(FMarkStackVisitor& Visitor) = 0;`
- L24 _public prototype_ `virtual void Visit(FAbstractVisitor& Visitor) = 0;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace Verse`

### `Source/Runtime/CoreUObject/Public/VerseVM/VVMGlobalProgram.h` (Public)


#### Free symbols / members of external scopes

- L9 _namespace_ `namespace Verse`
- L12 _externvar_ `extern TGlobalHeapPtr<VProgram> GlobalProgram;` (scope `Verse`)

### `Source/Runtime/CoreUObject/Public/VerseVM/VVMGlobalTrivialEmergentTypePtr.h` (Public)


#### struct `Verse::FGlobalTrivialEmergentTypePtr`  
`struct FGlobalTrivialEmergentTypePtr`  
_L16-38_
- L18 _public prototype_ `FGlobalTrivialEmergentTypePtr() = default;`
- L21 _protected function_ `AUTORTFM_DISABLE VEmergentType& Get(FAllocationContext Context, VCppClassInfo* ClassInfo, bool bWithShape)`
- L35 _protected prototype_ `AUTORTFM_DISABLE VEmergentType& GetSlow(FAllocationContext Context, VCppClassInfo* ClassInfo, bool bWithShape);`
- L37 _protected member_ `std::atomic<VEmergentType*> EmergentType = nullptr;`

#### struct `Verse::TGlobalTrivialEmergentTypePtr`  
`template <VCppClassInfo* ClassInfo> struct TGlobalTrivialEmergentTypePtr : public FGlobalTrivialEmergentTypePtr`  
_L41-49_
- inherits: `FGlobalTrivialEmergentTypePtr`
- L43 _public prototype_ `TGlobalTrivialEmergentTypePtr() = default;`
- L45 _public function_ `AUTORTFM_DISABLE VEmergentType& Get(FAllocationContext Context, bool bWithShape = false)`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace Verse`

### `Source/Runtime/CoreUObject/Public/VerseVM/VVMHardHandshakeContext.h` (Public)


#### struct `Verse::FHardHandshakeContext`  
`struct FHardHandshakeContext : FIOContext`  
_L17-33_
- inherits: `FIOContext`
- desc: Hard handshake is another way of saying "stop the world, do something, and resume the world". This is the kind of context you get when you stop the world via FIOContext::HardHandshake(). It lets you do anything an IO context can do, plus it lets you access all of the stopped contexts.
- L19 _public prototype_ `FHardHandshakeContext(const FHardHandshakeContext&) = default;`
- L21 _public function_ `const TArray<FAccessContext>& GetStoppedContexts()`
- L26 _private function_ `FHardHandshakeContext(FContextImpl* Impl, FStoppedWorld* StoppedWorld) : FIOContext(Impl, EIsInHandshake::No) , StoppedWorld(StoppedWorld)`
- L32 _private member_ `FStoppedWorld* StoppedWorld;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace Verse`

### `Source/Runtime/CoreUObject/Public/VerseVM/VVMHeap.h` (Public)


#### enum `Verse::EWeakBarrierState`  
`enum class EWeakBarrierState`  
_L43-49_
- L45 _public enumerator_ `Inactive`
- L46 _public enumerator_ `MarkOnRead`
- L47 _public enumerator_ `AttemptingToTerminate`
- L48 _public enumerator_ `CheckMarkedOnRead`

#### class `Verse::FHeap`  
`class FHeap final`  
_L51-410_
- L66 _public prototype_ `AUTORTFM_DISABLE static void Initialize();` — Must call this before doing anything with the heap.
- L68 _public prototype_ `static void Deinitialize();`
- L72 _public member_ `static FSubspace* FastSpace;` — Space for objects that are fast to GC: they have no destructors and do not require census. Ideally most objects we allocate dynamically are fast.
- L76 _public member_ `static FSubspace* AuxSpace;` — Same as FastSpace above, except allocations in this space are NOT put onto the mark stack. It is up to the callers who allocated into this space to handle marking anything those allocations contain.
- L84 _public member_ `static FSubspace* DestructorSpace;` — Space for objects that require destructors. It's fine for objects to have destructors so long as those objects are relatively infrequently allocated (they have low churn rate). It's fine for this space to get large so long as churn rate stays low. Destructors will be called from any thread. It's possible for destructors to be called on the slow path of allocation. It's possible for them to be called from some GC worker thread.
- L89 _public member_ `static FSubspace* CensusSpace;` — Space for objects that require census. Census is a heap iteration that happens after marking but before sweeping, where every live object in the census space has some callback called. This is mostly for weak handles. It's ideal for performance if this space stays small, but it's fine for the churn rate to be high.
- L92 _public member_ `static FSubspace* DestructorAndCensusSpace;` — Space for objects that require both destruction and census.
- L95 _public member_ `static FSubspace* EmergentSpace;` — Special space for emergent types. It's a limited to make a 32 bit offset enough.
- L101 _public member_ `static FHeapIterationSet* DestructorIterationSet;` — Use this set to iterate destructors. In the future, if we have spaces that require destruction other than the destructor space (like if we need a DestructorAndCensusSpace), then this set will contain all of them. That's important because there is some constant overhead to iterating any iteration set, but iteration sets can contain any number of spaces.
- L105 _public member_ `static FHeapIterationSet* CensusIterationSet;` — Census set, for now just containing the CensusSpace. If we have multiple spaces that require Census (like if we need a DestructorAndCensusSpace), then this will contain all of them.
- L107 _public function_ `static bool IsMarking()`
- L112 _public function_ `static bool IsDestroying()`
- L117 _public function_ `static bool IsCollecting()`
- L122 _public function_ `static EWeakBarrierState GetWeakBarrierState()`
- L127 _public function_ `static std::atomic<uint32>* GetMarkBitWord(const void* Ptr)`
- L137 _public function_ `static uint32 GetMarkBitIndex(const void* Ptr)`
- L144 _public function_ `static uint32 GetMarkBitMask(const void* Ptr)`
- L149 _public function_ `static bool IsMarked(const void* Ptr)`
- L156 _public function_ `static uint32 EmergentTypePtrToOffset(const VEmergentType* EmergentType)`
- L167 _public function_ `static VEmergentType* EmergentTypeOffsetToPtr(uint32 Offset)`
- L172 _public function_ `static void ReportAllocatedNativeBytes(ptrdiff_t Bytes)`
- L181 _public function_ `static void ReportDeallocatedNativeBytes(size_t Bytes)`
- L191 _public function_ `static size_t GetLiveNativeBytes()`
- L209 _public prototype_ `static FCollectionCycleRequest StartCollectingIfNotCollecting();` — If a collection cycle is going right now, then do nothing except return a request object that allows us to wait for when it's done. If a collection cycle is not going right now, then start one, and return a request object that allows us to wait for when it's done. The fact that this won't start a GC cycle if one is already going is quite significant. GC cycles float garbage: anything allocated in this cycle will not be freed in this cycle. So, if you create some garbage, call this function, and then wait, then you're not guaranteed that the garbage you created will be deleted. It might float! This function forms the basis of GC triggers. If you want to trigger GC when there is too much of something (like live bytes in the heap), then use this.
- L227 _public prototype_ `static FCollectionCycleRequest RequestFreshCollectionCycle();` — If a collection cycle is going right now, then request another collection cycle to start immediately after this one. Note that this cycle might be unique to us, since if multiple calls happen to this function within a cycle, then they'll all request the same fresh cycle. If a collection cycle is not going right now, then start one. Either way, return a request object that allows us to wait for the cycle we started. The point of this function is that it allows you to handle floating garbage. If you allocate some garbage, call this function, and then wait, then you're guaranteed that the garbage you created will get collected. It may float in the *current* cycle (if there was one), but it cannot possibly float in the fresh cycle that this requested. Hence this function forms the basis of STW "GC now" equivalents. Like, if you wanted to "synchronously GC" in a concurrent GC, then that means calling this function and then waiting for the request.
- L229 _public function_ `static uint64 GetCompletedCycleVersion()`
- L236 _public prototype_ `static void EnableExternalControl(FIOContext Context);` — Request that the collector allow external control. This will crash if the GC is already externally controlled.
- L239 _public prototype_ `static void DisableExternalControl();` — Disable external control.
- L241 _public function_ `static bool IsExternallyControlled()`
- L246 _public prototype_ `static bool IsGCStartPendingExternalSignal();`
- L247 _public prototype_ `static void ExternallySynchronouslyStartGC(FIOContext Context);`
- L254 _public prototype_ `static bool IsGCTerminationPendingExternalSignal(FIOContext Context);` — To be called from an external control system: Check if the GC wants to terminate. This means that the Verse GC has no more objects to mark. If the Verse GC has no more objects to mark, and other GCs in the system also have no more objects to mark, then it's safe to permit GC termination. This can only be called if the GC is marking. Otherwise it crashes.
- L261 _public prototype_ `static void ExternallySynchronouslyTerminateGC(FIOContext Context);` — To be called from an external control system: Permit the GC to terminate. This crashes if the Verse GC is not pending termination. NOTE: It's only safe to use this if there is no concurrent mutator activity while you're trying to do this.
- L265 _public prototype_ `static bool TryToExternallySynchronouslyTerminateGC(FIOContext Context);` — To be called from an external control system: Permit the GC to terminate. This returns true if the Verse GC was pending termination and was able to terminate, false otherwise.
- L282 _public prototype_ `static void AddExternalMarkStack(FMarkStack&&);` — External GCs are expected to create their own FMarkStack instance(s) and mark VCells using that API. Then, eventually, passing those MarkStacks to Verse using this AddExternalMarkStack() function. This ensures that the Verse GC is aware of external marking activity in its heap. Only use this function with EnableExternalControl(). Never call this function before ExternallySignalGCStartAndWaitUntilItDoes(). Never pass a MarkStack that had objects from a previous collection (i.e. from before ExternallySignalGCStartAndWaitUntilItDoes()). Never call ExternallySynchronouslyTerminateGC() if you have any MarkStacks that you haven't yet passed to the Verse GC using this AddExternalMarkStack() function. This function clears the contents of the MarkStack you give it.
- L287 _public prototype_ `AUTORTFM_OPEN static bool OwnsAddress(void*);` — It doesn't mean it's actually a valid cell, but it does mean that libpas owns this address. This doesn't alter the contents of the heap, so it's safe to call from the closed, and can be useful if you need to do pointer sanity-checking.
- L289 _public function_ `static double GetTotalTimeSpentCollecting()`
- L302 _private prototype_ `FHeap() = delete;`
- L304 _private prototype_ `static bool IsWithoutThreadingDuringCollection();`
- L308 _private prototype_ `static bool NormalizeWithoutThreadingAtCollectionStart();` — If we have threading, this returns false. If we don't have threading, it asserts we aren't GCing right now and checks if we should turn on threading.
- L310 _private prototype_ `static void CollectorThreadMain();`
- L311 _private prototype_ `static void CollectorThreadBody(FIOContext Context);`
- L313 _private prototype_ `static void OnLowLevelMemTrackerTick();`
- L315 _private prototype_ `static void WaitForTrigger(FIOContext Context);`
- L317 _private prototype_ `static void RunCollectionCycle(FIOContext Context);`
- L318 _private prototype_ `static void RunPreMarking(FIOContext Context);`
- L319 _private prototype_ `static void RunPostMarking(FIOContext Context);`
- L320 _private prototype_ `static void MarkForExternalControlWithoutThreading(FIOContext Context);`
- L322 _private prototype_ `static void Terminate();`
- L323 _private prototype_ `static void CancelTermination();`
- L325 _private prototype_ `static void BeginCollection(FIOContext Context);`
- L326 _private prototype_ `static void MarkRoots(FIOContext Context);`
- L327 _private prototype_ `static void Mark(FIOContext Context);`
- L328 _private prototype_ `static bool AttemptToTerminate(FIOContext Context);` — Returns true if we did terminate.
- L329 _private prototype_ `static void ConductCensus(FIOContext Context);`
- L330 _private prototype_ `static void RunDestructors(FIOContext Context);`
- L331 _private prototype_ `static void Sweep(FIOContext Context);`
- L332 _private prototype_ `static void EndCollection(FIOContext Context);`
- L334 _private prototype_ `static void LiveBytesTriggerCallback();`
- L335 _private prototype_ `static void CensusCallback(void* Object, void* Arg);`
- L336 _private prototype_ `static void DestructorCallback(void* Object, void* Arg);`
- L338 _private prototype_ `static void CheckCycleTriggerInvariants();`
- L339 _private prototype_ `static FCollectionCycleRequest RequestCollectionCycle(uint64 DesiredRequestCompleteDelta);`
- L341 _private prototype_ `static bool IsGCTerminationPendingExternalSignalImpl();`
- L343 _private function_ `static void ReportMarkedNativeBytes(size_t Bytes)`
- L349 _private member_ `static bool bWithoutThreading;`
- L351 _private member_ `static FThread* CollectorThread;`
- L352 _private member_ `static FDelegateHandle OnLLMTickHandle;`
- L354 _private member_ `static UE::FMutex GlobalRootMutex;`
- L355 _private member_ `static TNeverDestroyed<TArray<FGlobalHeapRoot*>> GlobalRoots;`
- L356 _private member_ `static UE::FMutex GlobalCensusRootMutex;`
- L357 _private member_ `static TNeverDestroyed<TArray<FGlobalHeapCensusRoot*>> GlobalCensusRoots;`
- L359 _private member_ `static UE::FMutex WeakKeyMapsMutex;`
- L360 _private member_ `static TNeverDestroyed<TArray<FHeapPageHeader*>> WeakKeyMapsByHeader;`
- L363 _private member_ `static UE::FMutex Mutex;` — Controls all of the fields below.
- L364 _private member_ `static UE::FConditionVariable ConditionVariable;`
- L377 _private member_ `static uint64 RequestedCycleVersion;` — Invariant: RequestedCycleVersion >= CompletedCycleVersion If RequestedCycleVersion > CompletedCycleVersion, then we should run a collection, and increment CompletedCycleVersion once finished. If RequestedCycleVersion == CompletedCycleVersion, then we should not run a collection. To request a collection, increment RequestedCycleVersion. To wait for our requested collection to finish, wait for CompletedCycleVersion to catch up to the value we incremented RequestedCycleVersion to.
- L378 _private member_ `static uint64 CompletedMarkingCycleVersion;`
- L379 _private member_ `static uint64 CompletedCycleVersion;`
- L381 _private member_ `static EState State;`
- L382 _private member_ `static EWeakBarrierState WeakBarrierState;`
- L384 _private member_ `static size_t LiveCellBytesAtStart;`
- L386 _private member_ `static std::atomic<size_t> MarkedNativeBytes;`
- L387 _private member_ `static std::atomic<size_t> LiveNativeBytes;`
- L389 _private member_ `static TNeverDestroyed<FMarkStack> MarkStack;` — Must hold Mutex to access safely.
- L390 _private member_ `static unsigned NumThreadsToScanStackManually;`
- L392 _private member_ `static bool bIsExternallyControlled;`
- L393 _private member_ `static bool bIsGCReadyForExternalMarking;`
- L394 _private member_ `static bool bIsGCMarkingExternallySignaled;`
- L395 _private member_ `static bool bIsGCTerminationWaitingForExternalSignal;`
- L396 _private member_ `static bool bIsGCTerminatingExternally;`
- L398 _private member_ `static bool bIsTerminated;`
- L400 _private member_ `static bool bIsInitialized;`
- L402 _private member_ `static double TotalTimeSpentCollecting;`
- L403 _private member_ `static double TimeOfPreMarking;`
- L406 _private member_ `static std::byte* EmergentTypeBase;` — Cached value of the base of the EmergentSpace (i.e. EmergentSpace->GetBase()).
- L408 _private member_ `static constexpr size_t EmergentAlignment = 16;`
- L409 _private member_ `static constexpr size_t EmergentReservationSize = 16 * 1024 * 1024;`

#### enum `Verse::FHeap::EState`  
`enum EState`  
_L54-63_
- L56 _public enumerator_ `Idle`
- L57 _public enumerator_ `Marking` — Finding roots and traversing the heap
- L58 _public enumerator_ `PostMarking` — Successfully completed a marking pass
- L59 _public enumerator_ `Census` — Cleaning up weakly referenced objects
- L60 _public enumerator_ `Destroying` — Running destructors on unreferenced objects
- L61 _public enumerator_ `Sweeping` — Reclaiming memory
- L62 _public enumerator_ `Finishing` — Ending the collection process, returning to idle

#### Free symbols / members of external scopes

- L22 _namespace_ `namespace UE`
- L28 _namespace_ `namespace Verse`

### `Source/Runtime/CoreUObject/Public/VerseVM/VVMHeapClientDataGuard.h` (Public)


#### struct `Verse::FHeapClientDataGuard`  
`struct FHeapClientDataGuard final`  
_L12-38_
- L14 _public function_ `FHeapClientDataGuard(FHeapPageHeader* InHeader) : Header(InHeader) , ClientDataPtr(Header->LockClientData())`
- L20 _public function_ `~FHeapClientDataGuard()`
- L25 _public function_ `FHeapPageHeader* GetHeader() const`
- L30 _public function_ `void** GetClientDataPtr() const`
- L36 _private member_ `FHeapPageHeader* Header;`
- L37 _private member_ `void** ClientDataPtr;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace Verse`

### `Source/Runtime/CoreUObject/Public/VerseVM/VVMHeapInt.h` (Public)


#### struct `Verse::VHeapInt`  
`struct VHeapInt final : VHeapValue`  
_L45-202_
- inherits: `VHeapValue`
- L48 _public member_ `static TGlobalTrivialEmergentTypePtr<&StaticCppClassInfo> GlobalTrivialEmergentType;`
- L50 _public typedef_ `using Digit = uint32;`
- L52 _public function_ `AUTORTFM_DISABLE static VHeapInt& New(FAllocationContext Context, uint32 NumWords)`
- L57 _public function_ `AUTORTFM_DISABLE static VHeapInt& New(FAllocationContext Context, bool Sign, TArrayView<Digit> Digits)`
- L62 _public function_ `AUTORTFM_DISABLE FORCENOINLINE static VHeapInt& FromInt64(FAllocationContext Context, int64 Int64)`
- L67 _public prototype_ `bool IsInt32() const;`
- L68 _public prototype_ `int32 AsInt32() const;`
- L70 _public prototype_ `bool IsInt64() const;`
- L71 _public prototype_ `int64 AsInt64() const;`
- L73 _public prototype_ `VFloat ConvertToFloat() const;`
- L75 _public prototype_ `static bool Equals(VHeapInt& X, VHeapInt& Y);`
- L77 _public prototype_ `AUTORTFM_DISABLE static VHeapInt* CreateZero(FAllocationContext Context);`
- L79 _public prototype_ `AUTORTFM_DISABLE static VHeapInt* Add(FAllocationContext, VHeapInt& X, VHeapInt& Y);`
- L80 _public prototype_ `AUTORTFM_DISABLE static VHeapInt* Sub(FAllocationContext, VHeapInt& X, VHeapInt& Y);`
- L81 _public prototype_ `AUTORTFM_DISABLE static VHeapInt* Multiply(FAllocationContext, VHeapInt& X, VHeapInt& Y);`
- L82 _public prototype_ `AUTORTFM_DISABLE static VHeapInt* Divide(FAllocationContext, VHeapInt& X, VHeapInt& Y, bool* bOutHasNonZeroRemainder = nullptr);`
- L83 _public prototype_ `AUTORTFM_DISABLE static VHeapInt* Modulo(FAllocationContext, VHeapInt& X, VHeapInt& Y);`
- L85 _public prototype_ `AUTORTFM_DISABLE static TTuple<VHeapInt*, Digit> DivideModulo(FAllocationContext, VHeapInt&, Digit);` — Note, modulo result is always positive, even where `Modulo` would produce a negative result.
- L86 _public prototype_ `AUTORTFM_DISABLE static VHeapInt* UnaryMinus(FAllocationContext, VHeapInt& X);`
- L96 _public prototype_ `static ComparisonResult Compare(VHeapInt& X, VHeapInt& Y);`
- L98 _public function_ `inline bool IsZero() const`
- L105 _public function_ `bool GetSign() const` — false means positive, true means negative
- L106 _public prototype_ `Digit GetDigit(const uint32 Index) const;`
- L107 _public function_ `unsigned int GetLength() const`
- L109 _public prototype_ `AUTORTFM_DISABLE void AppendDecimalToString(FUtf8StringBuilderBase& Builder, FAllocationContext Context);`
- L110 _public prototype_ `void AppendHexToString(FUtf8StringBuilderBase& Builder);`
- L112 _public prototype_ `AUTORTFM_DISABLE void AppendToStringImpl(FAllocationContext Context, FUtf8StringBuilderBase& Builder, EValueStringFormat Format, TSet<const void*>& VisitedObjects, uint32 RecursionDepth);`
- L113 _public prototype_ `AUTORTFM_DISABLE TSharedPtr<FJsonValue> ToJSONImpl(FRunningContext, EValueJSONFormat, TMap<const void*, EVisitState>& VisitedObjects, FToJsonCallback, uint32 RecursionDepth, FJsonObject* Defs);`
- L115 _public member_ `static constexpr bool SerializeIdentity = false;`
- L116 _public prototype_ `AUTORTFM_DISABLE static void SerializeLayout(FAllocationContext Context, VHeapInt*& This, FStructuredArchiveVisitor& Visitor);`
- L117 _public prototype_ `AUTORTFM_DISABLE void SerializeImpl(FAllocationContext Context, FStructuredArchiveVisitor& Visitor);`
- L124 _public prototype_ `void Initialize(InitializationType);`
- L125 _public prototype_ `void SetDigit(const uint32 Index, Digit Value);` — Use only when initializing.
- L126 _public prototype_ `AUTORTFM_DISABLE static VHeapInt* CreateWithLength(FAllocationContext, uint32 length);`
- L127 _public prototype_ `AUTORTFM_DISABLE static VHeapInt* Copy(FAllocationContext, const VHeapInt& X);`
- L128 _public function_ `inline Digit* DataStorage()`
- L137 _public member_ `static constexpr unsigned BitsPerByte = 8;` — The maximum length that the current implementation supports would be MaxInt / DigitBits. However, we use A lower limit for now, because raising it later is easier than lowering it. Support up to 1 million bits.
- L138 _public member_ `static constexpr unsigned DigitBits = sizeof(Digit) * BitsPerByte;`
- L139 _public member_ `static constexpr unsigned MaxLengthBits = 1024 * 1024;`
- L140 _public member_ `static constexpr unsigned MaxLength = MaxLengthBits / DigitBits;`
- L144 _private function_ `AUTORTFM_DISABLE explicit VHeapInt(FAllocationContext Context, uint32 NumWords) : VHeapValue(Context, &GlobalTrivialEmergentType.Get(Context)) , Length(NumWords)`
- L150 _private prototype_ `AUTORTFM_DISABLE static VHeapInt* CreateFrom(FAllocationContext, int64 Value);`
- L151 _private prototype_ `AUTORTFM_DISABLE static VHeapInt* CreateWithDigits(FAllocationContext, bool Sign, TArrayView<Digit> Digits);`
- L153 _private function_ `void SetSign(bool NewSign)`
- L155 _private prototype_ `AUTORTFM_DISABLE VHeapInt* RightTrim(FAllocationContext);`
- L157 _private prototype_ `AUTORTFM_DISABLE static VHeapInt* CreateFromImpl(FAllocationContext, uint64 Value, bool sign);`
- L159 _private member_ `static constexpr unsigned HalfDigitBits = DigitBits / 2;`
- L160 _private member_ `static constexpr Digit HalfDigitMask = (1ull << HalfDigitBits) - 1;`
- L161 _private member_ `static constexpr int MaxInt = 0x7FFFFFFF;`
- L163 _private prototype_ `static ComparisonResult AbsoluteCompare(const VHeapInt& X, const VHeapInt& Y);`
- L164 _private prototype_ `static ComparisonResult AbsoluteCompare(const VHeapInt&, Digit);`
- L165 _private prototype_ `static void MultiplyAccumulate(const VHeapInt& Multiplicand, Digit Multiplier, VHeapInt* Accumulator, uint32 AccumulatorIndex);`
- L168 _private prototype_ `static Digit DigitAdd(Digit A, Digit B, Digit& Carry);` — Digit arithmetic helpers.
- L169 _private prototype_ `static Digit DigitSub(Digit A, Digit B, Digit& Borrow);`
- L170 _private prototype_ `static Digit DigitMul(Digit A, Digit B, Digit& High);`
- L172 _private prototype_ `AUTORTFM_DISABLE static VHeapInt* AbsoluteAdd(FAllocationContext, VHeapInt& X, VHeapInt& Y, bool ResultSign);`
- L173 _private prototype_ `AUTORTFM_DISABLE static VHeapInt* AbsoluteSub(FAllocationContext, VHeapInt& X, VHeapInt& Y, bool ResultSign);`
- L175 _private prototype_ `Digit AbsoluteInplaceAdd(const VHeapInt& Summand, uint32 StartIndex);`
- L176 _private prototype_ `Digit AbsoluteInplaceSub(const VHeapInt& Subtrahend, uint32 StartIndex);`
- L177 _private prototype_ `void InplaceRightShift(uint32 Shift);`
- L179 _private prototype_ `AUTORTFM_DISABLE static bool AbsoluteDivWithDigitDivisor(FAllocationContext Context, const VHeapInt& X, Digit Divisor, VHeapInt** Quotient, Digit& Remainder);`
- L180 _private prototype_ `AUTORTFM_DISABLE static void AbsoluteDivWithHeapIntDivisor(FAllocationContext Context, const VHeapInt& Dividend, const VHeapInt& Divisor, VHeapInt** Quotient, VHeapInt** Remainder, bool* bOutHasNonZeroRemainder = nullptr);`
- L181 _private prototype_ `inline static Digit DigitDiv(Digit high, Digit low, Digit divisor, Digit& remainder);`
- L189 _private prototype_ `AUTORTFM_DISABLE static VHeapInt* AbsoluteLeftShiftAlwaysCopy(FAllocationContext Context, const VHeapInt& X, uint32 Shift, LeftShiftMode Mode);`
- L190 _private prototype_ `inline static bool ProductGreaterThan(Digit Factor1, Digit Factor2, Digit High, Digit Low);`
- L192 _private prototype_ `static void InternalMultiplyAdd(const VHeapInt& Source, Digit Factor, Digit Summand, uint32 N, VHeapInt* Result);`
- L194 _private function_ `inline const Digit* DataStorage() const`
- L199 _private member_ `const uint32 Length;`
- L200 _private member_ `uint8 Sign{false};` — false means positive, true means negative
- L201 _private member_ `Digit Digits[];`
- L204 _function_ `inline VHeapInt::Digit VHeapInt::GetDigit(const uint32 Index) const`
- L210 _function_ `inline void VHeapInt::SetDigit(uint32 Index, Digit Value)`

#### enum `Verse::VHeapInt::ComparisonResult`  
`enum class ComparisonResult`  
_L88-94_
- L90 _public enumerator_ `Equal`
- L91 _public enumerator_ `Undefined`
- L92 _public enumerator_ `GreaterThan`
- L93 _public enumerator_ `LessThan`

#### enum `Verse::VHeapInt::InitializationType`  
`enum class InitializationType`  
_L119-123_
- L121 _public enumerator_ `None`
- L122 _public enumerator_ `WithZero`

#### enum `Verse::VHeapInt::LeftShiftMode`  
`enum class LeftShiftMode`  
_L183-187_
- L185 _public enumerator_ `SameSizeResult`
- L186 _public enumerator_ `AlwaysAddOneDigit`

#### Free symbols / members of external scopes

- L41 _namespace_ `namespace Verse`
- L216 _function_ `inline uint32 GetTypeHash(const VHeapInt& HeapInt)` (scope `Verse`)

### `Source/Runtime/CoreUObject/Public/VerseVM/VVMHeapIterationSet.h` (Public)


#### class `Verse::FHeapIterationSet`  
`class FHeapIterationSet final`  
_L15-63_
- L18 _public function_ `static FHeapIterationSet* Create()`
- L23 _public function_ `static FHeapIterationSet* AllObjects()`
- L28 _public function_ `void Add(FSubspace* Subspace)`
- L33 _public function_ `void StartIterateBeforeHandshake()`
- L38 _public function_ `size_t StartIterateAfterHandshake()`
- L44 _public function_ `void IterateRange(size_t Begin, size_t End, verse_heap_iterate_filter Filter, void (*Callback)(void* Object, void* Arg), void* Arg)`
- L55 _public function_ `void EndIterate()`
- L61 _private prototype_ `FHeapIterationSet() = delete;`
- L62 _private prototype_ `FHeapIterationSet(const FHeapIterationSet&) = delete;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace Verse`

### `Source/Runtime/CoreUObject/Public/VerseVM/VVMHeapPageHeader.h` (Public)


#### struct `Verse::FHeapPageHeader`  
`struct FHeapPageHeader final`  
_L14-30_
- L16 _public function_ `static FHeapPageHeader* Get(const void* Ptr)`
- L21 _public function_ `void** LockClientData()`
- L26 _public function_ `void UnlockClientData()`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace Verse`

### `Source/Runtime/CoreUObject/Public/VerseVM/VVMInstantiationContext.h` (Public)


#### struct `Verse::FInstantiationContext`  
`struct FInstantiationContext`  
_L8-14_
- L10 _public member_ `UObject* Outer = nullptr;`
- L11 _public member_ `EObjectFlags Flags = RF_NoFlags;`
- L12 _public member_ `bool bCallInitInstanceFunctions{true};`
- L13 _public member_ `bool bModuleTopLevel{false};`

#### struct `Verse::FInstantiationScope`  
`struct FInstantiationScope`  
_L16-36_
- L18 _public member_ `static FInstantiationContext Context;`
- L19 _public member_ `FInstantiationContext OldContext;`
- L21 _public function_ `explicit FInstantiationScope(const FInstantiationContext& NewContext) : OldContext(Context)`
- L27 _public prototype_ `FInstantiationScope(const FInstantiationScope&) = delete;`
- L28 _public prototype_ `FInstantiationScope& operator=(const FInstantiationScope&) = delete;`
- L29 _public prototype_ `FInstantiationScope(FInstantiationScope&&) = delete;`
- L30 _public prototype_ `FInstantiationScope& operator=(FInstantiationScope&&) = delete;`
- L32 _public function_ `~FInstantiationScope()`

#### Free symbols / members of external scopes

- L6 _namespace_ `namespace Verse`

### `Source/Runtime/CoreUObject/Public/VerseVM/VVMInt.h` (Public)


#### struct `Verse::VInt`  
`struct AUTORTFM_DISABLE VInt : VValue`  
_L20-117_
- inherits: `VValue`
- L24 _public function_ `AUTORTFM_ENABLE explicit VInt() : VValue()` — Be careful using this! Only classes expecting a uninitialized int should use this such as: TWriteBarrier, VIntType, etc.
- L28 _public prototype_ `AUTORTFM_ENABLE VInt(const VInt&) = default;`
- L29 _public function_ `AUTORTFM_ENABLE explicit VInt(VValue InValue) : VValue(InValue)`
- L34 _public function_ `AUTORTFM_ENABLE explicit VInt(int32 InInt32) : VValue(VValue::FromInt32(InInt32))`
- L38 _public prototype_ `VInt(int64) = delete;` — nb: use a constructor that takes F*Context explicitly
- L39 _public function_ `VInt(FAllocationContext Context, int64 Int64) : VValue(Int64 >= INT32_MIN && Int64 <= INT32_MAX ? VValue::FromInt32(static_cast<int32>(Int64)) : VHeapInt::FromInt64(Context, Int64))`
- L45 _public function_ `AUTORTFM_ENABLE VInt(VHeapInt& N) : VValue(N.IsInt32() ? VValue::FromInt32(N.AsInt32()) : VValue(N))`
- L52 _public function_ `bool IsZero() const`
- L62 _public function_ `bool IsNegative() const`
- L72 _public prototype_ `AUTORTFM_ENABLE bool IsInt64() const;`
- L73 _public prototype_ `AUTORTFM_ENABLE int64 AsInt64() const;`
- L75 _public prototype_ `AUTORTFM_ENABLE bool IsUint32() const;`
- L76 _public prototype_ `AUTORTFM_ENABLE uint32 AsUint32() const;`
- L78 _public prototype_ `AUTORTFM_ENABLE VFloat ConvertToFloat() const;`
- L80 _public prototype_ `static VInt Add(FAllocationContext Context, VInt Lhs, VInt Rhs);`
- L81 _public prototype_ `static VInt Sub(FAllocationContext Context, VInt Lhs, VInt Rhs);`
- L82 _public prototype_ `static VInt Mul(FAllocationContext Context, VInt Lhs, VInt Rhs);`
- L83 _public prototype_ `static VInt Div(FAllocationContext Context, VInt Lhs, VInt Rhs, bool* bOutHasNonZeroRemainder = nullptr);`
- L84 _public prototype_ `static VInt Mod(FAllocationContext Context, VInt Lhs, VInt Rhs);`
- L85 _public prototype_ `static VInt Neg(FAllocationContext Context, VInt N);`
- L86 _public prototype_ `static VInt Abs(FAllocationContext Context, VInt N);`
- L87 _public prototype_ `static bool Eq(FAllocationContext Context, VInt Lhs, VInt Rhs);`
- L88 _public prototype_ `static bool Eq(FAllocationContext Context, VInt Lhs, VValue Rhs);`
- L89 _public prototype_ `static bool Gt(FAllocationContext Context, VInt Lhs, VInt Rhs);`
- L90 _public prototype_ `static bool Lt(FAllocationContext Context, VInt Lhs, VInt Rhs);`
- L91 _public prototype_ `static bool Gte(FAllocationContext Context, VInt Lhs, VInt Rhs);`
- L92 _public prototype_ `static bool Lte(FAllocationContext Context, VInt Lhs, VInt Rhs);`
- L96 _public prototype_ `void AppendDecimalToString(FUtf8StringBuilderBase& Builder, FAllocationContext Context) const;`
- L97 _public prototype_ `void AppendHexToString(FUtf8StringBuilderBase& Builder) const;`
- L98 _public prototype_ `TSharedPtr<FJsonValue> ToJSON(FAllocationContext Context, EValueJSONFormat Format) const;`
- L101 _private prototype_ `VFloat ConvertToFloatSlowPath() const;`
- L103 _private prototype_ `static VInt AddSlowPath(FAllocationContext Context, VInt Lhs, VInt Rhs);`
- L104 _private prototype_ `static VInt SubSlowPath(FAllocationContext Context, VInt Lhs, VInt Rhs);`
- L105 _private prototype_ `static VInt MulSlowPath(FAllocationContext Context, VInt Lhs, VInt Rhs);`
- L106 _private prototype_ `static VInt DivSlowPath(FAllocationContext Context, VInt Lhs, VInt Rhs, bool* bOutHasNonZeroRemainder);`
- L107 _private prototype_ `static VInt ModSlowPath(FAllocationContext Context, VInt Lhs, VInt Rhs);`
- L108 _private prototype_ `static VInt NegSlowPath(FAllocationContext Context, VInt N);`
- L109 _private prototype_ `static VInt AbsSlowPath(FAllocationContext Context, VInt N);`
- L110 _private prototype_ `static bool EqSlowPath(FAllocationContext Context, VInt Lhs, VInt Rhs);`
- L111 _private prototype_ `static bool LtSlowPath(FAllocationContext, VInt Lhs, VInt Rhs);`
- L112 _private prototype_ `static bool GtSlowPath(FAllocationContext, VInt Lhs, VInt Rhs);`
- L113 _private prototype_ `static bool LteSlowPath(FAllocationContext, VInt Lhs, VInt Rhs);`
- L114 _private prototype_ `static bool GteSlowPath(FAllocationContext, VInt Lhs, VInt Rhs);`
- L116 _private prototype_ `static VHeapInt& AsHeapInt(FAllocationContext, VInt N);`

#### Free symbols / members of external scopes

- L18 _namespace_ `namespace Verse`

### `Source/Runtime/CoreUObject/Public/VerseVM/VVMIntType.h` (Public)


#### struct `Verse::VIntType`  
`struct VIntType : VType`  
_L18-58_
- inherits: `VType`
- desc: An int type with constraints. A uninitialized min/max means no constraint.
- L21 _public member_ `static TGlobalTrivialEmergentTypePtr<&StaticCppClassInfo> GlobalTrivialEmergentType;`
- L23 _public function_ `AUTORTFM_DISABLE static VIntType& New(FAllocationContext Context, VInt InMin, VInt InMax)`
- L28 _public function_ `const VInt GetMin() const`
- L33 _public function_ `const VInt GetMax() const`
- L38 _public prototype_ `AUTORTFM_DISABLE bool SubsumesImpl(FAllocationContext Context, VValue);`
- L40 _public prototype_ `AUTORTFM_DISABLE void AppendToStringImpl(FAllocationContext Context, FUtf8StringBuilderBase& Builder, EValueStringFormat Format, TSet<const void*>& VisitedObjects, uint32 RecursionDepth);`
- L41 _public prototype_ `AUTORTFM_DISABLE TSharedPtr<FJsonValue> ToJSONImpl(FRunningContext, EValueJSONFormat, TMap<const void*, EVisitState>& VisitedObjects, FToJsonCallback, uint32 RecursionDepth, FJsonObject* Defs);`
- L42 _public prototype_ `AUTORTFM_DISABLE VValue FromJSONImpl(FRunningContext, const FJsonValue&, EValueJSONFormat, FFromJsonCallback);`
- L44 _public member_ `static constexpr bool SerializeIdentity = false;`
- L45 _public prototype_ `AUTORTFM_DISABLE static void SerializeLayout(FAllocationContext Context, VIntType*& This, FStructuredArchiveVisitor& Visitor);`
- L46 _public prototype_ `AUTORTFM_DISABLE void SerializeImpl(FAllocationContext, FStructuredArchiveVisitor& Visitor);`
- L49 _private function_ `explicit VIntType(FAllocationContext& Context, VInt InMin, VInt InMax) : VType(Context, &GlobalTrivialEmergentType.Get(Context)) , Min(Context, InMin) , Max(Context, InMax)`
- L56 _private member_ `TWriteBarrier<VInt> Min;`
- L57 _private member_ `TWriteBarrier<VInt> Max;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace Verse`

### `Source/Runtime/CoreUObject/Public/VerseVM/VVMIntrinsics.h` (Public)


#### struct `Verse::VIntrinsics`  
`struct AUTORTFM_DISABLE VIntrinsics : VCell`  
_L18-52_
- inherits: `VCell`
- desc: A special heap value to store all intrinsic VFunction objects
- L21 _public member_ `static TGlobalTrivialEmergentTypePtr<&StaticCppClassInfo> GlobalTrivialEmergentType;`
- L23 _public member_ `TWriteBarrier<VFunction> Abs;`
- L24 _public member_ `TWriteBarrier<VFunction> Ceil;`
- L25 _public member_ `TWriteBarrier<VFunction> Floor;`
- L26 _public member_ `TWriteBarrier<VFunction> ConcatenateMaps;`
- L27 _public member_ `TWriteBarrier<VFunction> WeakMapType;`
- L28 _public member_ `TWriteBarrier<VFunction> FitsInPlayerMap;`
- L29 _public member_ `TWriteBarrier<VFunction> MakePersistentMap;`
- L30 _public member_ `TWriteBarrier<VFunction> MakeSessionVar;`
- L31 _public member_ `TWriteBarrier<VFunction> NotifyPersistentMapMutation;`
- L33 _public function_ `static VIntrinsics& New(FAllocationContext Context, VPackage& BuiltInPackage)`
- L38 _public prototype_ `static void Initialize(FAllocationContext Context);`
- L41 _private prototype_ `static FNativeCallResult AbsImpl(FRunningContext Context, VValue Self, VNativeProcedure::Args Arguments);`
- L42 _private prototype_ `static FNativeCallResult CeilImpl(FRunningContext Context, VValue Self, VNativeProcedure::Args Arguments);`
- L43 _private prototype_ `static FNativeCallResult FloorImpl(FRunningContext Context, VValue Self, VNativeProcedure::Args Arguments);`
- L44 _private prototype_ `static FNativeCallResult ConcatenateMapsImpl(FRunningContext Context, VValue Self, VNativeProcedure::Args Arguments);`
- L45 _private prototype_ `static FNativeCallResult WeakMapTypeImpl(FRunningContext Context, VValue Self, VNativeProcedure::Args Arguments);`
- L46 _private prototype_ `static FNativeCallResult FitsInPlayerMapImpl(FRunningContext Context, VValue Self, VNativeProcedure::Args Arguments);`
- L47 _private prototype_ `static FNativeCallResult MakePersistentMapImpl(FRunningContext Context, VValue Self, VNativeProcedure::Args Arguments);`
- L48 _private prototype_ `static FNativeCallResult MakeSessionVarImpl(FRunningContext Context, VValue Self, VNativeProcedure::Args Arguments);`
- L49 _private prototype_ `static FNativeCallResult NotifyPersistentMapMutationImpl(FRunningContext Context, VValue Self, VNativeProcedure::Args Arguments);`
- L51 _private prototype_ `VIntrinsics(FAllocationContext Context, VPackage& BuiltInPackage);`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace Verse`

### `Source/Runtime/CoreUObject/Public/VerseVM/VVMJson.h` (Public)


#### enum `Verse::EValueJSONFormat`  
`enum class EValueJSONFormat`  
_L58-63_
- L60 _public enumerator_ `Analytics` — Basic JSON, no schema
- L61 _public enumerator_ `Persistence` — Persistence JSON
- L62 _public enumerator_ `Persona` — Persona JSON, types implementing this should output themselves according to https://ai.google.dev/api/caching#Schema

#### enum `Verse::EVisitState`  
`enum class EVisitState`  
_L65-69_
- L67 _public enumerator_ `Visiting`
- L68 _public enumerator_ `Visited`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace Verse`
- L16 _namespace_ `namespace Persistence` (scope `Verse`)
- L19 _variable_ `constexpr TCHAR PackageNameKey[] = TEXT("$pa` (scope `Verse::Persistence`) — Only needed until PDSS no longer needs this field.
- L21 _variable_ `constexpr TCHAR ClassNameKey[] = TEXT("$cl` (scope `Verse::Persistence`) — Only needed until PDSS no longer needs this field.
- L22 _variable_ `constexpr TCHAR KeyKey[] = TEXT("k")` (scope `Verse::Persistence`)
- L23 _variable_ `constexpr TCHAR ValueKey[] = TEXT("v")` (scope `Verse::Persistence`)
- L27 _namespace_ `namespace Persona` (scope `Verse`)
- L29 _variable_ `constexpr TCHAR StringString[] = TEXT("STR` (scope `Verse::Persona`)
- L30 _variable_ `constexpr TCHAR NumberString[] = TEXT("NUM` (scope `Verse::Persona`)
- L31 _variable_ `constexpr TCHAR ObjectString[] = TEXT("OBJ` (scope `Verse::Persona`)
- L32 _variable_ `constexpr TCHAR ArrayString[] = TEXT("ARR` (scope `Verse::Persona`)
- L33 _variable_ `constexpr TCHAR BooleanString[] = TEXT("BOO` (scope `Verse::Persona`)
- L34 _variable_ `constexpr TCHAR IntegerString[] = TEXT("INT` (scope `Verse::Persona`)
- L36 _variable_ `constexpr TCHAR DescriptionString[] = TEXT("des` (scope `Verse::Persona`)
- L37 _variable_ `constexpr TCHAR EnumString[] = TEXT("enu` (scope `Verse::Persona`)
- L38 _variable_ `constexpr TCHAR ItemsString[] = TEXT("ite` (scope `Verse::Persona`)
- L39 _variable_ `constexpr TCHAR MaximumString[] = TEXT("max` (scope `Verse::Persona`)
- L40 _variable_ `constexpr TCHAR MinimumString[] = TEXT("min` (scope `Verse::Persona`)
- L41 _variable_ `constexpr TCHAR PropertiesString[] = TEXT("pro` (scope `Verse::Persona`)
- L42 _variable_ `constexpr TCHAR RequiredString[] = TEXT("req` (scope `Verse::Persona`)
- L43 _variable_ `constexpr TCHAR TypeString[] = TEXT("typ` (scope `Verse::Persona`)
- L44 _variable_ `constexpr TCHAR AnyOfString[] = TEXT("any` (scope `Verse::Persona`)
- L45 _variable_ `constexpr TCHAR KeyString[] = TEXT("key` (scope `Verse::Persona`)
- L46 _variable_ `constexpr TCHAR ValueString[] = TEXT("val` (scope `Verse::Persona`)
- L47 _variable_ `constexpr TCHAR NullableString[] = TEXT("nul` (scope `Verse::Persona`)
- L49 _variable_ `constexpr TCHAR SchemaString[] = TEXT("$sc` (scope `Verse::Persona`)
- L50 _variable_ `constexpr TCHAR SchemaLink[] = TEXT("htt` (scope `Verse::Persona`) — ai.google.dev/api/caching#Schema");
- L52 _variable_ `inline const FName LLMDescriptionAttributeName(TEXT("llm_` (scope `Verse::Persona`)
- L53 _variable_ `inline const FName LLMDescriptionFieldName(TEXT("Desc` (scope `Verse::Persona`)
- L55 _prototype_ `void InjectLLMDescription(const UStruct* DeclaredIn, FProperty* Property, FJsonObject& FieldObject);` (scope `Verse::Persona`)
- L73 _macro_ `#define JSON_FIELD(Name) Format == EValueJSONFormat::Persona ? Persona::Name##String : TEXT(#Name)` — To handle case differences for field names in JSON code ie: Analytics prefers PascalCase whereas Persona/Persistence use CamelCase
- L78 _prototype_ `AUTORTFM_DISABLE TSharedPtr<FJsonValue> ToJSON(FRunningContext, VValue, EValueJSONFormat, AUTORTFM_IMPLICIT_DISABLE FToJsonCallback, uint32 RecursionDepth = 0, FJsonObject* Defs = nullptr);` (scope `Verse`)
- L81 _prototype_ `TSharedRef<FJsonValue> Int64ToJson(int64 Arg);` (scope `Verse`)
- L83 _prototype_ `bool TryGetInt64(const FJsonValue& JsonValue, int64& Int64Value);` (scope `Verse`)
- L85 _prototype_ `AUTORTFM_DISABLE_IF(WITH_VERSE_VM) TSharedPtr<FJsonValue> Wrap(const TSharedPtr<FJsonValue>& Value, EValueJSONFormat Format);` (scope `Verse`)
- L87 _prototype_ `AUTORTFM_DISABLE_IF(WITH_VERSE_VM) TSharedPtr<FJsonValue> Unwrap(const TSharedPtr<FJsonValue>& Value, EValueJSONFormat Format);` (scope `Verse`)
- L90 _prototype_ `AUTORTFM_DISABLE_IF(WITH_VERSE_VM) TSharedPtr<FJsonValue> Wrap(const TSharedPtr<FJsonValue>& Value);` (scope `Verse`)
- L92 _prototype_ `TSharedPtr<FJsonValue> Unwrap(const FJsonValue& Value);` (scope `Verse`)

### `Source/Runtime/CoreUObject/Public/VerseVM/VVMLazyInitialized.h` (Public)


#### struct `Verse::TLazyInitialized`  
`template <typename T> struct TLazyInitialized`  
_L28-92_
- desc: Acts like a smart pointer to T, meant to be used in global context, that: - Lazily initializes itself. It's only when you first touch it that anything happens. - Never destroys itself. - Is thread-safe. It's fine if you race on initialization. - Doesn't do any fences or atomic ops in steady state. - Has a leak "by design" - if there is a race on initialization, then there will be a leak. Basically, if N threads race on initialization, then you might allocate N versions of T but only one will win, and the others will be allowed to leak. Since this will Never Happen (TM), it's fine.
- L30 _public prototype_ `TLazyInitialized() = default;`
- L32 _public function_ `T& Get()`
- L46 _public function_ `T& operator*()`
- L51 _public function_ `T* operator->()`
- L56 _public function_ `const T& Get() const`
- L61 _public function_ `const T& operator*() const`
- L66 _public function_ `const T* operator->() const`
- L72 _private function_ `FORCENOINLINE T& GetSlow()`
- L91 _private member_ `std::atomic<T*> Data = nullptr;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace Verse`
- L15 _prototype_ `void AddLeakedObjectForLazyInitialization(void* Object);` (scope `Verse`)

### `Source/Runtime/CoreUObject/Public/VerseVM/VVMLoadFieldInlineCache.h` (Public)


#### struct `Verse::FLoadFieldCacheCase`  
`struct FLoadFieldCacheCase`  
_L15-91_
- L17 _public prototype_ `FLoadFieldCacheCase() = default;`
- L18 _public function_ `FLoadFieldCacheCase(const FLoadFieldCacheCase& Other) : Kind(Other.Kind) , EmergentTypeOffset(Other.EmergentTypeOffset)`
- L25 _public function_ `FLoadFieldCacheCase& operator=(const FLoadFieldCacheCase& Other)`
- L42 _public function_ `static FLoadFieldCacheCase Offset(VEmergentType* EmergentType, uint64 Offset)`
- L51 _public function_ `static FLoadFieldCacheCase Constant(VEmergentType* EmergentType, VValue Value)`
- L60 _public function_ `static FLoadFieldCacheCase Function(VEmergentType* EmergentType, VFunction* Function)`
- L70 _public function_ `static FLoadFieldCacheCase Accessor(VEmergentType* EmergentType, VAccessor* Accessor)`
- L80 _public function_ `explicit operator bool()`
- L82 _public member_ `EKind Kind = EKind::Invalid;`
- L83 _public member_ `uint32 EmergentTypeOffset = 0;`
- L90 _public member_ `} U;`

#### enum `Verse::FLoadFieldCacheCase::EKind`  
`enum class EKind : uint8`  
_L33-40_
- L35 _public enumerator_ `Offset`
- L36 _public enumerator_ `ConstantValue`
- L37 _public enumerator_ `ConstantFunction`
- L38 _public enumerator_ `Accessor`
- L39 _public enumerator_ `Invalid`

#### union `Verse::FLoadFieldCacheCase::(anonymous)`  
``  
_L85-90_

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace Verse`
- L86 _member_ `uint64 Offset = 0;` (scope `Verse::FLoadFieldCacheCase::__anonae452c38010a`)
- L87 _member_ `VValue Value;` (scope `Verse::FLoadFieldCacheCase::__anonae452c38010a`)
- L88 _member_ `VFunction* Function;` (scope `Verse::FLoadFieldCacheCase::__anonae452c38010a`)
- L89 _member_ `VAccessor* Accessor;` (scope `Verse::FLoadFieldCacheCase::__anonae452c38010a`)

### `Source/Runtime/CoreUObject/Public/VerseVM/VVMLocalAllocator.h` (Public)


#### struct `Verse::FLocalAllocator`  
`struct alignas(PAS_LOCAL_ALLOCATOR_ALIGNMENT) FLocalAllocator final`  
_L16-41_
- desc: This is really pas_local_allocator.
- L18 _public prototype_ `FLocalAllocator() = default;`
- L19 _public prototype_ `~FLocalAllocator();`
- L21 _public prototype_ `void Initialize(FSubspace* Subspace, size_t Size);`
- L22 _public prototype_ `void Stop();`
- L23 _public prototype_ `std::byte* Allocate();`
- L24 _public prototype_ `std::byte* TryAllocate();`
- L37 _private member_ `char OpaqueData[VERSE_SMALL_SEGREGATED_LOCAL_ALLOCATOR_SIZE];`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace Verse`

### `Source/Runtime/CoreUObject/Public/VerseVM/VVMLocation.h` (Public)


#### struct `Verse::FLocation`  
`struct FLocation`  
_L17-48_
- desc: The line number associated with a Verse VM opcode. Line numbers start at one.
- L19 _public prototype_ `FLocation() = default;`
- L21 _public function_ `explicit FLocation(uint32 Line) : Line(Line)`
- L47 _public member_ `uint32 Line{};`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace Verse`
- L26 _function_ `friend bool operator==(FLocation Left, FLocation Right)` (scope `Verse`)
- L31 _function_ `friend bool operator!=(FLocation Left, FLocation Right)` (scope `Verse`)
- L36 _function_ `friend uint32 GetTypeHash(const FLocation& Location)` (scope `Verse`)
- L42 _function_ `template <typename TVisitor> friend void Visit(TVisitor& Visitor, FLocation& Value)` (scope `Verse`)
- L50 _function_ `inline FLocation EmptyLocation()` (scope `Verse`)

### `Source/Runtime/CoreUObject/Public/VerseVM/VVMLog.h` (Public)


#### Free symbols / members of external scopes

- L8 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogVerseVM, Log, All);`
- L9 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogVerseGC, Log, All);`
- L13 _macro_ `#define V_DIE(Format, ...) \`
- L21 _macro_ `#define V_DIE_IF_MSG(Condition, Format, ...) UE_CLOG(Condition, LogVerseVM, Fatal, TEXT(Format), ##__VA_ARGS__)`
- L22 _macro_ `#define V_DIE_IF(Condition) V_DIE_IF_MSG(Condition, "Unexpected condition: %s", TEXT(#Condition))`
- L23 _macro_ `#define V_DIE_UNLESS_MSG(Condition, Format, ...) UE_CLOG(!(Condition), LogVerseVM, Fatal, TEXT(Format), ##__VA_ARGS__)`
- L24 _macro_ `#define V_DIE_UNLESS(Condition) V_DIE_UNLESS_MSG(Condition, "Assertion failed: %s", TEXT(#Condition))`

### `Source/Runtime/CoreUObject/Public/VerseVM/VVMMap.h` (Public)


#### struct `Verse::VMapBase`  
`struct VMapBase : VHeapValue`  
_L38-219_
- inherits: `VHeapValue`
- desc: The following types can be used as keys: logic int float char string enum A class, if it’s comparable An option, if the element type is comparable An array, if the element type is comparable A map if both the key and the value types are comparable A tuple if all elements in the tuple are comparable
- L41 _public typedef_ `using KeyType = TWriteBarrier<VValue>;`
- L42 _public typedef_ `using ValType = TWriteBarrier<VValue>;`
- L43 _public typedef_ `using PairType = TPair<KeyType, ValType>;`
- L44 _public typedef_ `using SequenceType = uint32;`
- L69 _protected prototype_ `VMapBase(FAllocationContext Context, uint32 InitialCapacity, VEmergentType* Type);`
- L71 _protected prototype_ `template <typename GetEntryByIndex> VMapBase(FAllocationContext Context, uint32 MaxNumEntries, const GetEntryByIndex& GetEntry, VEmergentType* Type);`
- L75 _protected prototype_ `AUTORTFM_DISABLE TPair<uint32, bool> AddWithoutLocking(FAllocationContext Context, uint32 KeyHash, VValue Key, VValue Value, bool bTransactional = false);` — This should only be called if you already have the required mutexes or know you don't need them. Returns the slot in the data table where the value was inserted and a boolean indicating if an existing entry was replaced.
- L78 _public function_ `uint32 Num() const`
- L83 _public prototype_ `AUTORTFM_DISABLE VValue FindByHashWithSlot(FAllocationContext Context, uint32 Hash, VValue Key, uint32* OutSlot);`
- L84 _public function_ `AUTORTFM_DISABLE VValue FindWithSlot(FAllocationContext Context, VValue Key, SequenceType* OutSlot)`
- L89 _public function_ `AUTORTFM_DISABLE VValue FindByHash(FAllocationContext Context, uint32 Hash, VValue Key)`
- L94 _public function_ `AUTORTFM_DISABLE VValue Find(FAllocationContext Context, VValue Key)`
- L102 _public function_ `VValue GetKey(uint32 Index)` — GetKey/GetValue doesn't verify that Index is within limits and only works as long as nothing is removed from the map.
- L110 _public function_ `VValue GetValue(uint32 Index)`
- L118 _public prototype_ `AUTORTFM_DISABLE void Add(FAllocationContext Context, VValue Key, VValue Value);`
- L120 _public prototype_ `void AddTransactionally(FAllocationContext Context, VValue Key, VValue Value);`
- L122 _public prototype_ `AUTORTFM_DISABLE void Reserve(FAllocationContext Context, uint32 InCapacity);`
- L124 _public function_ `size_t GetPairTableSizeForCapacity(uint32 InCapacity) const`
- L128 _public function_ `size_t GetSequenceTableSizeForCapacity(uint32 InCapacity) const`
- L132 _public function_ `size_t GetPairTableSize() const`
- L136 _public function_ `size_t GetSequenceTableSize() const`
- L140 _public function_ `size_t GetAllocatedSize() const`
- L144 _public function_ `const PairType* GetPairTable() const`
- L148 _public function_ `const SequenceType* GetSequenceTable() const`
- L152 _public function_ `PairType* GetPairTable()`
- L156 _public function_ `SequenceType* GetSequenceTable()`
- L163 _public function_ `template <typename MapType> AUTORTFM_DISABLE static MapType& New(FAllocationContext Context, uint32 InitialCapacity = 0)` — These `new` calls are templated so as to avoid boilerplate News/Ctors in VMapBase's subclasses.
- L171 _public prototype_ `template <typename MapType, typename GetEntryByIndex> static MapType& New(FAllocationContext Context, uint32 MaxNumEntries, const GetEntryByIndex& GetEntry);`
- L174 _public prototype_ `template <typename FunctionType> void ForEachImpl(FunctionType);`
- L177 _public prototype_ `template <typename FunctionType> void ForEach(FunctionType);`
- L180 _public prototype_ `template <typename MapType, typename FunctionType> AUTORTFM_DISABLE MapType& TraverseImpl(FAllocationContext, FunctionType);`
- L183 _public prototype_ `template <typename MapType, typename FunctionType> AUTORTFM_DISABLE MapType& Traverse(FAllocationContext, FunctionType);`
- L185 _public prototype_ `AUTORTFM_DISABLE VValue MeltImpl(FAllocationContext Context);`
- L187 _public prototype_ `AUTORTFM_DISABLE ECompares EqualImpl(FAllocationContext Context, VCell* Other, const TFunction<void(::Verse::VValue, ::Verse::VValue)>& HandlePlaceholder);`
- L189 _public prototype_ `uint32 GetTypeHashImpl();`
- L191 _public prototype_ `void VisitMembersImpl(FAllocationContext Context, FDebuggerVisitor& Visitor);`
- L193 _public prototype_ `AUTORTFM_DISABLE void AppendToStringImpl(FAllocationContext Context, FUtf8StringBuilderBase& Builder, EValueStringFormat Format, TSet<const void*>& VisitedObjects, uint32 RecursionDepth);`
- L194 _public prototype_ `AUTORTFM_DISABLE TSharedPtr<FJsonValue> ToJSONImpl(FRunningContext, EValueJSONFormat, TMap<const void*, EVisitState>& VisitedObjects, FToJsonCallback, uint32 RecursionDepth, FJsonObject* Defs);`
- L197 _public prototype_ `template <typename MapType> AUTORTFM_DISABLE static void SerializeLayoutImpl(FAllocationContext Context, MapType*& This, FStructuredArchiveVisitor& Visitor);`
- L199 _public prototype_ `AUTORTFM_DISABLE void SerializeImpl(FAllocationContext Context, FStructuredArchiveVisitor& Visitor);`
- L201 _public member_ `static constexpr bool InstancedCell = true;`
- L203 _public function_ `RangedForIterator begin() const`
- L209 _public function_ `RangedForIterator end() const`
- L215 _public member_ `TWriteBarrier<TAux<PairType>> Data;`
- L216 _public member_ `TWriteBarrier<TAux<SequenceType>> SequenceData;` — initial insert sequence only.  Overwritten values will stay in their original sequence
- L217 _public member_ `uint32 NumElements;`
- L218 _public member_ `uint32 Capacity;`

#### struct `Verse::VMapBase::RangedForIterator`  
`struct RangedForIterator`  
_L46-66_
- L48 _public function_ `RangedForIterator(const VMapBase* Map, uint32 Index) : Map(Map) , Index(Index)`
- L51 _public function_ `TPair<VValue, VValue> operator*() const`
- L56 _public function_ `bool operator==(const RangedForIterator& Rhs) const`
- L57 _public function_ `bool operator!=(const RangedForIterator& Rhs) const`
- L58 _public function_ `RangedForIterator& operator++()`
- L64 _public member_ `const VMapBase* Map;`
- L65 _public member_ `uint32 Index;`

#### struct `Verse::VMap`  
`struct VMap : VMapBase`  
_L221-230_
- inherits: `VMapBase`
- L224 _public member_ `static TGlobalTrivialEmergentTypePtr<&StaticCppClassInfo> GlobalTrivialEmergentType;`
- L228 _public member_ `static constexpr bool SerializeIdentity = false;`
- L229 _public function_ `AUTORTFM_DISABLE static void SerializeLayout(FAllocationContext Context, VMap*& This, FStructuredArchiveVisitor& Visitor)`

#### struct `Verse::VMutableMap`  
`struct VMutableMap : VMapBase`  
_L232-242_
- inherits: `VMapBase`
- L235 _public member_ `static TGlobalTrivialEmergentTypePtr<&StaticCppClassInfo> GlobalTrivialEmergentType;`
- L239 _public prototype_ `AUTORTFM_DISABLE FOpResult FreezeImpl(FAllocationContext Context, VTask* Task);`
- L241 _public function_ `AUTORTFM_DISABLE static void SerializeLayout(FAllocationContext Context, VMutableMap*& This, FStructuredArchiveVisitor& Visitor)`

#### struct `Verse::VPersistentMap`  
`struct VPersistentMap : VMutableMap`  
_L244-281_
- inherits: `VMutableMap`
- L247 _public member_ `static TGlobalTrivialEmergentTypePtr<&StaticCppClassInfo> GlobalTrivialEmergentType;`
- L249 _public prototype_ `AUTORTFM_DISABLE static VPersistentMap& Register(FAllocationContext Context, FString Path, FString RelativePath, EPersistenceExternalAccess, UObject* Outer, VValue ValueType);`
- L251 _public prototype_ `AUTORTFM_DISABLE static void SerializeLayout(FAllocationContext Context, VPersistentMap*& This, FStructuredArchiveVisitor& Visitor);`
- L253 _public prototype_ `AUTORTFM_DISABLE void SerializeImpl(FAllocationContext Context, FStructuredArchiveVisitor& Visitor);`
- L255 _public function_ `VType& GetValueType() const`
- L257 _public prototype_ `void NotifyKeyUpdate(FAllocationContext Context, VValue Key, VValue Value);`
- L259 _public member_ `FString Path;`
- L260 _public member_ `FString RelativePath;`
- L261 _public member_ `EPersistenceExternalAccess ExternalAccess;`
- L262 _public member_ `TWriteBarrier<VValue> ValueType;`
- L263 _public member_ `TMap<VValue, VValue> UpdatedPairs;`
- L266 _private function_ `AUTORTFM_DISABLE VPersistentMap(FAllocationContext Context, FString Path, FString RelativePath, EPersistenceExternalAccess ExternalAccess, VValue ValueType) : VMutableMap(Context, 0, &GlobalTrivialEmergentType.Get(Context)) , Path(::MoveTemp(Path)) , RelativePath(::MoveTemp(RelativePath)) , ExternalAccess(ExternalAccess) , ValueType(Context, ValueType)`
- L275 _private function_ `AUTORTFM_DISABLE VPersistentMap(FAllocationContext Context) : VMutableMap(Context, 0, &GlobalTrivialEmergentType.Get(Context))`
- L280 _private prototype_ `void RegisterWithSaveService(FName MountPointName);`

#### Free symbols / members of external scopes

- L19 _namespace_ `namespace Verse`

### `Source/Runtime/CoreUObject/Public/VerseVM/VVMMarkStack.h` (Public)


#### struct `Verse::FMarkStack`  
`struct FMarkStack`  
_L21-148_
- L23 _public prototype_ `FMarkStack() = default;`
- L26 _public prototype_ `~FMarkStack();` — It's illegal to destroy a mark stack that has anything in it.
- L28 _public function_ `bool IsEmpty() const`
- L33 _public function_ `size_t Num() const`
- L38 _public function_ `VCell* Pop()`
- L50 _public function_ `bool TryMarkNonNull(const VCell* Cell)`
- L60 _public function_ `void MarkNonNull(const VCell* Cell)`
- L68 _public function_ `void FencedMarkNonNull(const VCell* Cell)`
- L76 _public function_ `void Mark(const VCell* Cell)`
- L84 _public function_ `void MarkAuxNonNull(const void* Aux)`
- L92 _public function_ `void FencedMarkAuxNonNull(const void* Aux)`
- L100 _public function_ `void MarkAux(const void* Aux)`
- L108 _public function_ `void MarkNonNull(const UObject* Object)`
- L116 _public function_ `void Mark(const UObject* Object)`
- L124 _public function_ `void Append(FMarkStack&& Other)`
- L129 _public function_ `void ReportNativeBytes(size_t Bytes)`
- L136 _private prototype_ `template <std::memory_order MemoryOrder> void MarkSlowImpl(const VCell* Cell);`
- L138 _private prototype_ `void MarkSlow(const VCell* Cell);`
- L139 _private prototype_ `void FencedMarkSlow(const VCell* Cell);`
- L142 _private prototype_ `template <std::memory_order MemoryOrder> void MarkAuxSlowImpl(const void* Aux);`
- L144 _private prototype_ `void MarkAuxSlow(const void* Aux);`
- L145 _private prototype_ `void FencedMarkAuxSlow(const void* Aux);`
- L147 _private member_ `TArray<VCell*> Stack;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace GC` (scope `UE`)
- L14 _externvar_ `extern bool GIsFrankenGCCollecting;` (scope `UE::GC`)
- L17 _namespace_ `namespace Verse`

### `Source/Runtime/CoreUObject/Public/VerseVM/VVMMarkStackVisitor.h` (Public)


#### struct `Verse::FMarkStackVisitor`  
`struct FMarkStackVisitor`  
_L16-128_
- L20 _public member_ `static constexpr bool bIsAbstractVisitor = false;`
- L22 _public function_ `FMarkStackVisitor(FMarkStack& InMarkStack) : MarkStack(InMarkStack)`
- L27 _public function_ `void VisitNonNull(VCell* InCell, const TCHAR*)`
- L32 _public function_ `void VisitNonNull(UObject* InObject, const TCHAR*)`
- L37 _public function_ `void VisitAuxNonNull(void* InAux, const TCHAR*)`
- L42 _public function_ `void Visit(VCell* InCell, const TCHAR* ElementName)`
- L50 _public function_ `void Visit(UObject* InObject, const TCHAR* ElementName)`
- L58 _public function_ `void VisitAux(void* Aux, const TCHAR*)`
- L66 _public prototype_ `void Visit(VValue, const TCHAR*);`
- L71 _public function_ `template <typename T> void Visit(TWriteBarrier<T>& Value, const TCHAR*)`
- L77 _public function_ `template <typename T> void Visit(TObjectPtr<T>& Value, const TCHAR*)`
- L83 _public prototype_ `template <typename T> void Visit(T&, const TCHAR*);`
- L86 _public function_ `template <typename T> void Visit(T* Values, uint64 Count, const TCHAR*)`
- L92 _public prototype_ `template <typename T> void Visit(T Begin, T End, const TCHAR*);`
- L96 _public prototype_ `template <typename ElementType, typename AllocatorType> void Visit(TArray<ElementType, AllocatorType>& Values, const TCHAR*);` — Arrays
- L100 _public prototype_ `template <typename ElementType, typename KeyFuncs, typename Allocator> void Visit(TSet<ElementType, KeyFuncs, Allocator>& Values, const TCHAR*);` — Sets
- L104 _public prototype_ `template <typename KeyType, typename ValueType, typename SetAllocator, typename KeyFuncs> void Visit(TMap<KeyType, ValueType, SetAllocator, KeyFuncs>& Values, const TCHAR*);` — Maps
- L106 _public function_ `bool IsMarked(VCell* InCell, const TCHAR*)`
- L111 _public function_ `void ReportNativeBytes(size_t Bytes)`
- L116 _public function_ `void MarkNativeStructAsReachable(VNativeStruct* NativeStruct)`
- L123 _public function_ `void Visit(uint8 Value, const TCHAR* ElementName)`
- L124 _public function_ `void Visit(uint32 Value, const TCHAR* ElementName)`
- L127 _private member_ `FMarkStack& MarkStack;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace Verse`

### `Source/Runtime/CoreUObject/Public/VerseVM/VVMMutableArray.h` (Public)


#### struct `Verse::VMutableArray`  
`struct VMutableArray : VArrayBase`  
_L18-114_
- inherits: `VArrayBase`
- L21 _public member_ `static TGlobalTrivialEmergentTypePtr<&StaticCppClassInfo> GlobalTrivialEmergentType;`
- L24 _public prototype_ `void Reset(FAllocationContext Context);`
- L26 _public prototype_ `void ResetTransactionally(FAllocationContext Context);`
- L29 _public function_ `AUTORTFM_DISABLE void AddValue(FAllocationContext Context, VValue Value)` — Adds `Value` at the end of the array.
- L34 _public function_ `AUTORTFM_DISABLE void AddValueTransactionally(FAllocationContext Context, VValue Value)`
- L40 _public prototype_ `template <EWriteMode WriteMode = EWriteMode::NonTransactional> AUTORTFM_DISABLE void AddValue(FAllocationContext, VValue);`
- L43 _public prototype_ `void RemoveRange(FAccessContext, uint32 StartIndex, uint32 Count);` — Removes `Count` array elements, starting from `StartIndex`, keeping all other array elements in order.
- L46 _public prototype_ `void RemoveSwap(FAccessContext, uint32 RemoveIndex);` — Eliminates the array element at `RemoveIndex`, and moves the last array element into its place.
- L49 _public prototype_ `template <typename T> AUTORTFM_DISABLE void Append(FAllocationContext Context, VArrayBase& Array);`
- L50 _public prototype_ `AUTORTFM_DISABLE void Append(FAllocationContext Context, VArrayBase& Array);`
- L52 _public prototype_ `static VMutableArray& Concat(FAllocationContext Context, VArrayBase& Lhs, VArrayBase& Rhs);`
- L54 _public prototype_ `void InPlaceMakeImmutable(FAllocationContext);`
- L56 _public function_ `AUTORTFM_DISABLE static VMutableArray& New(FAllocationContext Context, uint32 NumValues, uint32 InitialCapacity, EArrayType ArrayType)`
- L61 _public function_ `AUTORTFM_DISABLE static VMutableArray& New(FAllocationContext Context, std::initializer_list<VValue> InitList)`
- L67 _public function_ `template <typename InitIndexFunc, typename = std::enable_if_t<std::is_same_v<VValue, std::invoke_result_t<InitIndexFunc, uint32>>>> AUTORTFM_DISABLE static VMutableArray& New(FAllocationContext Context, uint32 InNumValues, InitIndexFunc&& InitFunc)`
- L72 _public function_ `AUTORTFM_DISABLE static VMutableArray& New(FAllocationContext Context, FUtf8StringView String)`
- L77 _public function_ `AUTORTFM_DISABLE static VMutableArray& New(FAllocationContext Context)`
- L82 _public function_ `AUTORTFM_DISABLE static void SerializeLayout(FAllocationContext Context, VMutableArray*& This, FStructuredArchiveVisitor& Visitor)`
- L84 _public prototype_ `AUTORTFM_DISABLE FOpResult FreezeImpl(FAllocationContext Context, VTask* Task);`
- L87 _public prototype_ `void Truncate(uint32 ElementsToRemove);` — Discards the last `ElementsToRemove` elements from the array's backing buffer; does not reclaim memory.
- L90 _private function_ `AUTORTFM_DISABLE VMutableArray(FAllocationContext Context, uint32 NumValues, uint32 InitialCapacity, EArrayType ArrayType) : VArrayBase(Context, NumValues, InitialCapacity, ArrayType, &GlobalTrivialEmergentType.Get(Context))`
- L96 _private function_ `AUTORTFM_DISABLE VMutableArray(FAllocationContext Context, std::initializer_list<VValue> InitList) : VArrayBase(Context, InitList, &GlobalTrivialEmergentType.Get(Context))`
- L102 _private function_ `template <typename InitIndexFunc, typename = std::enable_if_t<std::is_same_v<VValue, std::invoke_result_t<InitIndexFunc, uint32>>>> AUTORTFM_DISABLE VMutableArray(FAllocationContext Context, uint32 InNumValues, InitIndexFunc&& InitFunc) : VArrayBase(Context, InNumValues, InitFunc, &GlobalTrivialEmergentType.Get(Context))`
- L107 _private function_ `AUTORTFM_DISABLE VMutableArray(FAllocationContext Context, FUtf8StringView String) : VArrayBase(Context, String, &GlobalTrivialEmergentType.Get(Context))`
- L113 _private prototype_ `void CopyRange(FAccessContext, uint32 SrcIndex, uint32 DstIndex, uint32 Count);` — Copies `Count` array elements from `SrcIndex` to `DstIndex`.

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace Verse`

### `Source/Runtime/CoreUObject/Public/VerseVM/VVMNameValueMap.h` (Public)


#### struct `Verse::VNameValueMap`  
`struct VNameValueMap`  
_L16-113_
- desc: A helper struct that maps strings to VValues
- L18 _public function_ `AUTORTFM_DISABLE VNameValueMap(FAllocationContext Context, uint32 Capacity) : NameAndValues(Context, &VMutableArray::New(Context, 0, Capacity, EArrayType::VValue))`
- L24 _public member_ `TWriteBarrier<VMutableArray> NameAndValues;` — We keep names at 2*Index and Values at 2*Index+1
- L26 _public function_ `uint32 Num() const`
- L31 _public function_ `void Reset(FAllocationContext Context)`
- L36 _public function_ `VUniqueString& GetName(uint32 Index) const`
- L43 _public function_ `VValue GetValue(uint32 Index) const`
- L50 _public function_ `template <typename CellType> CellType& GetCell(uint32 Index) const`
- L55 _public function_ `void AddValue(FAllocationContext Context, VUniqueString& Name, VValue Value)`
- L61 _public function_ `TOptional<VValue> RemoveValue(FAccessContext Context, FUtf8StringView Name)`
- L74 _public function_ `uint32 IndexOf(FUtf8StringView Name, ESearchCase::Type SearchCase = ESearchCase::CaseSensitive) const`
- L86 _public function_ `VValue Lookup(FUtf8StringView Name, ESearchCase::Type SearchCase = ESearchCase::CaseSensitive) const`
- L93 _public function_ `template <typename CellType> CellType* LookupCell(FUtf8StringView Name) const`
- L100 _public function_ `template <typename CellType> CellType* LookupCellByFName(FName Name) const`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace Verse`
- L109 _function_ `template <typename TVisitor> friend void Visit(TVisitor& Visitor, VNameValueMap& Value)` (scope `Verse`)

### `Source/Runtime/CoreUObject/Public/VerseVM/VVMNamedType.h` (Public)


#### struct `Verse::VNamedType`  
`struct VNamedType : VType`  
_L20-71_
- inherits: `VType`
- desc: Abstract base class for VClass and VEnumeration
- L24 _public function_ `VPackage& GetPackage() const`
- L25 _public function_ `VArray& GetRelativePath() const`
- L26 _public function_ `VArray& GetBaseName() const`
- L28 _public prototype_ `void AppendQualifiedName(FUtf8StringBuilderBase& Builder) const;`
- L29 _public prototype_ `void AppendScopeName(FUtf8StringBuilderBase& Builder) const;`
- L30 _public prototype_ `void AppendMangledName(FUtf8StringBuilderBase& Builder, UTF8CHAR Separator = UTF8CHAR('-')) const;`
- L31 _public prototype_ `FUtf8String GetFullName();` — used by ToJSON
- L33 _public function_ `bool HasUEType() const`
- L35 _public function_ `template <typename FieldType> FieldType* GetUEType() const`
- L37 _public function_ `template <typename FieldType> FieldType* GetUETypeChecked() const`
- L38 _public function_ `bool IsImportAsPlaceholder() const`
- L39 _public function_ `bool IsNativeBound() const`
- L41 _public prototype_ `void AddRedirect(ECoreRedirectFlags Kind);`
- L43 _public prototype_ `AUTORTFM_DISABLE void AppendToStringImpl(FAllocationContext Context, FUtf8StringBuilderBase& Builder, EValueStringFormat Format, TSet<const void*>& VisitedObjects, uint32 RecursionDepth);`
- L45 _public prototype_ `void SerializeImpl(FAllocationContext Context, FStructuredArchiveVisitor& Visitor);`
- L48 _protected prototype_ `AUTORTFM_DISABLE VNamedType(FAllocationContext Context, VEmergentType* EmergentType, VPackage* InPackage, VArray* InRelativePath, VArray* InBaseName, VArray* InAttributeIndices, VArray* InAttributes, VValue InImportType, bool bInNativeBound);`
- L50 _protected prototype_ `AUTORTFM_DISABLE VNamedType(FAllocationContext Context, VEmergentType* EmergentType);`
- L54 _protected member_ `TWriteBarrier<VPackage> Package;`
- L55 _protected member_ `TWriteBarrier<VArray> RelativePath;`
- L56 _protected member_ `TWriteBarrier<VArray> BaseName;`
- L61 _protected member_ `TWriteBarrier<VArray> AttributeIndices;` — Attributes holds all the attributes for this type and its members, flattened into one array. Each entry of AttributeIndices is the starting index of a group in Attributes. AttributeIndices has one extra element at the end, to simplify lookup.
- L62 _protected member_ `TWriteBarrier<VArray> Attributes;`
- L66 _protected member_ `TWriteBarrier<VValue> NativeType;` — A UField that represents this VNamedType when interacting with UE systems. Before linking this is VValue(); for imported types this is a placeholder.
- L68 _protected member_ `bool bNativeBound;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace Verse`

### `Source/Runtime/CoreUObject/Public/VerseVM/VVMNames.h` (Public)


#### Free symbols / members of external scopes

- L11 _namespace_ `namespace Verse`
- L11 _namespace_ `namespace Names` (scope `Verse`)
- L13 _variable_ `static constexpr int32 DefaultNameLength = 64;` (scope `Verse::Names`)
- L19 _namespace_ `namespace Private` (scope `Verse::Names`)
- L29 _prototype_ `FString MangleCasedName(FStringView Name, FStringView CrcName, bool* bOutNameWasMangled = nullptr);` (scope `Verse::Names::Private`) — The following method are intended to take a case sensitive name (which maybe already adorned with package information) and convert it into a case insensitive name. This is done by prepending a CRC of the name. The Crc is calculated on the CrcName, which is a qualified name in the case of fields in interfaces. Otherwise it's the same as Name.
- L30 _prototype_ `FString UnmangleCasedName(const FName MaybeMangledName, bool* bOutNameWasMangled = nullptr);` (scope `Verse::Names::Private`)
- L38 _prototype_ `FUtf8String EncodeName(FUtf8StringView Path);` (scope `Verse::Names::Private`) — Encode and decode a verse names.  This is currently only used to encode functions. The method takes characters that could be considered invalid for UE names and makes them valid
- L39 _prototype_ `FString EncodeName(FStringView Path);` (scope `Verse::Names::Private`)
- L40 _prototype_ `FUtf8String DecodeName(FUtf8StringView Path);` (scope `Verse::Names::Private`)
- L41 _prototype_ `FString DecodeName(FStringView Path);` (scope `Verse::Names::Private`)
- L49 _macro_ `#define UE_MAKE_CONSTANT_STRING_METHODS(Name, Text) \` — Create Get methods to return the given constant strings
- L78 _prototype_ `template <typename CharType> TStringBuilderWithBuffer<CharType, DefaultNameLength> GetDecoratedName(TStringView<CharType> Path, TStringView<CharType> Module, TStringView<CharType> Name);` (scope `Verse::Names`)
- L79 _prototype_ `extern template TUtf8StringBuilder<DefaultNameLength> GetDecoratedName(FUtf8StringView Path, FUtf8StringView Module, FUtf8StringView Name);` (scope `Verse::Names`)
- L80 _prototype_ `extern template TStringBuilder<DefaultNameLength> GetDecoratedName(FStringView Path, FStringView Module, FStringView Name);` (scope `Verse::Names`)
- L83 _prototype_ `template <typename CharType> TStringBuilderWithBuffer<CharType, DefaultNameLength> GetDecoratedName(TStringView<CharType> Path, TStringView<CharType> Name);` (scope `Verse::Names`)
- L84 _prototype_ `extern template TUtf8StringBuilder<DefaultNameLength> GetDecoratedName(FUtf8StringView Path, FUtf8StringView Name);` (scope `Verse::Names`)
- L85 _prototype_ `extern template TStringBuilder<DefaultNameLength> GetDecoratedName(FStringView Path, FStringView Name);` (scope `Verse::Names`)
- L88 _prototype_ `template <typename CharType> TStringBuilderWithBuffer<CharType, DefaultNameLength> GetVersePackageNameForVni(TStringView<CharType> MountPointName, TStringView<CharType> CppModuleName);` (scope `Verse::Names`)
- L89 _prototype_ `extern template TUtf8StringBuilder<DefaultNameLength> GetVersePackageNameForVni(FUtf8StringView MountPointName, FUtf8StringView CppModuleName);` (scope `Verse::Names`)
- L90 _prototype_ `extern template TStringBuilder<DefaultNameLength> GetVersePackageNameForVni(FStringView MountPointName, FStringView CppModuleName);` (scope `Verse::Names`)
- L93 _prototype_ `template <typename CharType> TStringBuilderWithBuffer<CharType, DefaultNameLength> GetVersePackageNameForContent(TStringView<CharType> MountPointName);` (scope `Verse::Names`)
- L94 _prototype_ `extern template TUtf8StringBuilder<DefaultNameLength> GetVersePackageNameForContent(FUtf8StringView MountPointName);` (scope `Verse::Names`)
- L95 _prototype_ `extern template TStringBuilder<DefaultNameLength> GetVersePackageNameForContent(FStringView MountPointName);` (scope `Verse::Names`)
- L98 _prototype_ `template <typename CharType> TStringBuilderWithBuffer<CharType, DefaultNameLength> GetVersePackageNameForPublishedContent(TStringView<CharType> MountPointName);` (scope `Verse::Names`)
- L99 _prototype_ `extern template TUtf8StringBuilder<DefaultNameLength> GetVersePackageNameForPublishedContent(FUtf8StringView MountPointName);` (scope `Verse::Names`)
- L100 _prototype_ `extern template TStringBuilder<DefaultNameLength> GetVersePackageNameForPublishedContent(FStringView MountPointName);` (scope `Verse::Names`)
- L103 _prototype_ `template <typename CharType> TStringBuilderWithBuffer<CharType, DefaultNameLength> GetVersePackageNameForAssets(TStringView<CharType> MountPointName);` (scope `Verse::Names`)
- L104 _prototype_ `extern template TUtf8StringBuilder<DefaultNameLength> GetVersePackageNameForAssets(FUtf8StringView MountPointName);` (scope `Verse::Names`)
- L105 _prototype_ `extern template TStringBuilder<DefaultNameLength> GetVersePackageNameForAssets(FStringView MountPointName);` (scope `Verse::Names`)
- L108 _prototype_ `template <typename CharType> TStringBuilderWithBuffer<CharType, DefaultNameLength> GetVersePackageDirForContent(TStringView<CharType> MountPointName);` (scope `Verse::Names`)
- L109 _prototype_ `extern template TUtf8StringBuilder<DefaultNameLength> GetVersePackageDirForContent(FUtf8StringView MountPointName);` (scope `Verse::Names`)
- L110 _prototype_ `extern template TStringBuilder<DefaultNameLength> GetVersePackageDirForContent(FStringView MountPointName);` (scope `Verse::Names`)
- L113 _prototype_ `template <typename CharType> TStringBuilderWithBuffer<CharType, DefaultNameLength> GetVersePackageDirForAssets(TStringView<CharType> MountPointName);` (scope `Verse::Names`)
- L114 _prototype_ `extern template TUtf8StringBuilder<DefaultNameLength> GetVersePackageDirForAssets(FUtf8StringView MountPointName);` (scope `Verse::Names`)
- L115 _prototype_ `extern template TStringBuilder<DefaultNameLength> GetVersePackageDirForAssets(FStringView MountPointName);` (scope `Verse::Names`)
- L118 _prototype_ `template <typename CharType> TStringBuilderWithBuffer<CharType, DefaultNameLength> GetUPackagePathForVni(TStringView<CharType> MountPointName, TStringView<CharType> CppModuleName);` (scope `Verse::Names`)
- L119 _prototype_ `extern template TUtf8StringBuilder<DefaultNameLength> GetUPackagePathForVni(FUtf8StringView MountPointName, FUtf8StringView CppModuleName);` (scope `Verse::Names`)
- L120 _prototype_ `extern template TStringBuilder<DefaultNameLength> GetUPackagePathForVni(FStringView MountPointName, FStringView CppModuleName);` (scope `Verse::Names`)
- L123 _prototype_ `template <typename CharType> TStringBuilderWithBuffer<CharType, DefaultNameLength> GetUPackagePathForContent(TStringView<CharType> MountPointName);` (scope `Verse::Names`)
- L124 _prototype_ `extern template TUtf8StringBuilder<DefaultNameLength> GetUPackagePathForContent(FUtf8StringView MountPointName);` (scope `Verse::Names`)
- L125 _prototype_ `extern template TStringBuilder<DefaultNameLength> GetUPackagePathForContent(FStringView MountPointName);` (scope `Verse::Names`)
- L128 _prototype_ `template <typename CharType> TStringBuilderWithBuffer<CharType, DefaultNameLength> GetUPackagePathForAssets(TStringView<CharType> MountPointName);` (scope `Verse::Names`)
- L129 _prototype_ `extern template TUtf8StringBuilder<DefaultNameLength> GetUPackagePathForAssets(FUtf8StringView MountPointName);` (scope `Verse::Names`)
- L130 _prototype_ `extern template TStringBuilder<DefaultNameLength> GetUPackagePathForAssets(FStringView MountPointName);` (scope `Verse::Names`)
- L133 _prototype_ `template <typename CharType> TStringBuilderWithBuffer<CharType, DefaultNameLength> GetUPackagePath(TStringView<CharType> VersePackageName, EVersePackageType* OutPackageType = nullptr);` (scope `Verse::Names`)
- L134 _prototype_ `extern template TUtf8StringBuilder<DefaultNameLength> GetUPackagePath(FUtf8StringView VersePackageName, EVersePackageType* OutPackageType);` (scope `Verse::Names`)
- L135 _prototype_ `extern template TStringBuilder<DefaultNameLength> GetUPackagePath(FStringView VersePackageName, EVersePackageType* OutPackageType);` (scope `Verse::Names`)
- L142 _function_ `inline bool IsFullPath(FUtf8StringView Name)` (scope `Verse::Names`) — Test to see if the given path is a full Verse path (begins with open parenthesis)
- L146 _function_ `inline bool IsFullPath(FStringView Name)` (scope `Verse::Names`)
- L150 _function_ `inline FUtf8StringView RemoveQualifier(FUtf8StringView QualifiedName)` (scope `Verse::Names`)
- L159 _function_ `inline FStringView RemoveQualifier(FStringView QualifiedName)` (scope `Verse::Names`)
- L177 _prototype_ `FString VersePropToUEName(FStringView VerseName, FStringView CrcVerseName, bool* bWasVerseName = nullptr);` (scope `Verse::Names`) — Convert a Verse property name to a UE name as a string If bWasVerseName is true, then the name needed to be modified to be used as a UE name
- L178 _prototype_ `FString VersePropToUEName(FStringView VerseName, bool* bWasVerseName = nullptr);` (scope `Verse::Names`)
- L182 _prototype_ `FName VersePropToUEFName(FStringView VerseName, FStringView CrcVerseName, bool* bWasVerseName = nullptr);` (scope `Verse::Names`) — Convert a Verse property name to a UE name as an FName.  If the resulting name is too long, the engine will check. If bWasVerseName is true, then the name needed to be modified to be used as a UE name
- L183 _prototype_ `FName VersePropToUEFName(FStringView VerseName, bool* bWasVerseName = nullptr);` (scope `Verse::Names`)
- L188 _prototype_ `FString UEPropToVerseName(FStringView UEName, bool* bIsVerseName = nullptr);` (scope `Verse::Names`) — Convert a UE property name to the original Verse name. WARNING: The resulting string is case sensitive and should NEVER be converted to an FName If bIsVerseName is true, then the UE name was originally a verse name.
- L189 _prototype_ `FString UEPropToVerseName(FName UEName, bool* bIsVerseName = nullptr);` (scope `Verse::Names`)
- L193 _prototype_ `FName UEPropToVerseFName(FStringView UEName, bool* bIsVerseName = nullptr);` (scope `Verse::Names`) — WARNING: This version is commonly used to signal that the code is depending on the verse name being stored in an FName which is not valid.
- L194 _prototype_ `FName UEPropToVerseFName(FName UEName, bool* bIsVerseName = nullptr);` (scope `Verse::Names`)
- L203 _prototype_ `FString VerseFuncToUEName(FStringView VerseName);` (scope `Verse::Names`) — Convert a Verse function name to a UE name as a string
- L206 _prototype_ `FName VerseFuncToUEFName(FStringView VerseName);` (scope `Verse::Names`) — Convert a Verse function name to a UE name as an FName.  If the resulting name is too long, the engine will check.
- L211 _prototype_ `FString UEFuncToVerseName(FStringView UEName);` (scope `Verse::Names`) — Convert a UE function name to the original Verse name. WARNING: The resulting string is case sensitive and should NEVER be converted to an FName If bIsVerseName is true, then the UE name was originally a verse name.
- L212 _prototype_ `FString UEFuncToVerseName(FName UEName);` (scope `Verse::Names`)
- L219 _prototype_ `FStringView GetVerseDeadPrefix();` (scope `Verse::Names`) — Return the verse dead prefix
- L222 _prototype_ `bool HasVerseDeadPrefix(FStringView Name);` (scope `Verse::Names`) — Test to see if the given name has the prefix
- L225 _prototype_ `FString AddVerseDeadPrefix(FStringView Name);` (scope `Verse::Names`) — Add the verse dead prefix.  Will not add a prefix if one already exists
- L228 _prototype_ `FStringView RemoveVerseDeadPrefix(FStringView Name);` (scope `Verse::Names`) — Remove the verse dead prefix if it exists
- L231 _prototype_ `void MakeTypeDead(UObject* Object, UObject* NewOuter);` (scope `Verse::Names`) — Rename the given type to dead and move it to the given new outer
- L234 _prototype_ `FString GetDecoratedName(FProperty* Property);` (scope `Verse::Names`) — Get the decorated verse name for a property on a UVerseClass or a UVerseStruct

### `Source/Runtime/CoreUObject/Public/VerseVM/VVMNativeAllocationGuard.h` (Public)


#### struct `Verse::TNativeAllocationGuard`  
`template <typename THolder> struct TNativeAllocationGuard`  
_L13-29_
- L15 _public function_ `TNativeAllocationGuard(THolder* InHolder) : Holder(InHolder) , PreviousAllocatedSize(Holder->GetAllocatedSize())`
- L21 _public function_ `~TNativeAllocationGuard()`
- L27 _private member_ `THolder* Holder;`
- L28 _private member_ `size_t PreviousAllocatedSize;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace Verse`

### `Source/Runtime/CoreUObject/Public/VerseVM/VVMNativeConstructorWrapper.h` (Public)


#### struct `Verse::VNativeConstructorWrapper`  
`struct VNativeConstructorWrapper : VCell`  
_L37-88_
- inherits: `VCell`
- desc: This is a wrapper around a native object for us to know what fields have been initialized or not in the object. Why? - For pure-Verse objects, we rely on our emergent type to track field initialization and can directly store placeholders for uninitialized fields. - Native objects don't have an emergent type and since the data lives in the `UObject` itself we can't directly store placeholders for uninitialized fields. To handle this, we wrap native objects in a `VNativeConstructorWrapper` object uses its emergent types bitmap of the fields created and placeholders for self/fields used before they are created. When we are done with archetype construction, we unify any placeholders then unwrap the native object using a special opcode and return it as part of `NewObject`. The wrapper object then gets GC'ed during the next collection. By convention, non-native Verse objects are not wrapped; the unwrap opcode just no-ops and returns the object itself when it encounters it (this is so we can avoid allocating an extra wrapper object in the common non-native case). Therefore, we always favour emitting the unwrap instruction where a native object needs to be unwrapped, since we don't know during codegen whether the object in question is native or not (since we do the wrapping in `NewObject` at runtime). Non-native objects can also be turned into native objects at any time (we test this as well using `--uobject-probability` in our tests.)
- L40 _public prototype_ `AUTORTFM_DISABLE void AppendToStringImpl(FAllocationContext Context, FUtf8StringBuilderBase& Builder, EValueStringFormat Format, TSet<const void*>& VisitedObjects, uint32 RecursionDepth);`
- L42 _public prototype_ `AUTORTFM_DISABLE static VNativeConstructorWrapper& New(FAllocationContext Context, VClass& Class, VNativeStruct& NativeStruct);`
- L43 _public prototype_ `AUTORTFM_DISABLE static VNativeConstructorWrapper& New(FAllocationContext Context, VClass& Class, UObject* NativeObject);`
- L44 _public prototype_ `AUTORTFM_DISABLE static VNativeConstructorWrapper& New(FAllocationContext Context, VClass& Class, VShape& Shape, UObject* NativeObject);`
- L46 _public prototype_ `AUTORTFM_DISABLE bool CreateFieldCached(FAllocationContext Context, FCreateFieldCacheCase Cache);`
- L47 _public prototype_ `AUTORTFM_DISABLE bool CreateField(FAllocationContext Context, VUniqueString& FieldName, FCreateFieldCacheCase* OutCacheCase = nullptr);`
- L49 _public function_ `bool IsFieldCreated(uint32 FieldIndex)`
- L55 _public function_ `VValue LoadField(FAllocationContext Context, uint32 FieldIndex)` — If the field is uninitialized, return a placeholder for it.
- L61 _public function_ `VValue UnifyField(FAllocationContext Context, uint32 FieldIndex)` — Mark a field as initialized. If it was previously loaded, return its placeholder to be unified.
- L69 _public prototype_ `VValue WrappedObject() const;`
- L72 _public member_ `VRestValue SelfPlaceholder;` — Placeholder for self that we pass to anything attempting to unwrap this before its fully created
- L77 _private prototype_ `AUTORTFM_DISABLE VNativeConstructorWrapper(FAllocationContext Context, VClass& Class, VNativeStruct& NativeStruct, VShape* Shape, int32 NumFields);`
- L78 _private prototype_ `AUTORTFM_DISABLE VNativeConstructorWrapper(FAllocationContext Context, VClass& Class, UObject* NativeObject, VShape* Shape, int32 NumFields);`
- L81 _private member_ `TWriteBarrier<VValue> NativeObject;` — This should either be a `VNativeStruct`/`UObject` wrapped in a `VValue`.
- L83 _private member_ `int32 NumFields;`
- L87 _private member_ `VRestValue Fields[];` — These are placeholders until the corresponding native field is initialized, and then they become VValue(). TODO: Consider a scheme that only allocates enough entries in Fields for non-Constants.

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace Verse`

### `Source/Runtime/CoreUObject/Public/VerseVM/VVMNativeConverter.h` (Public)


#### struct `Verse::TIsNativeStruct`  
`template <typename NativeType> struct TIsNativeStruct`  
_L63-66_
- L65 _public member_ `static constexpr bool Value = false;`

#### struct `Verse::TToVValue`  
`template <typename NativeType, typename = void> struct TToVValue`  
_L70-89_
- desc: Assigned to a native implementation return value - a default-emplaceable version of TOptional<NativeType>.
- L72 _public member_ `TOptional<NativeType> Value;`
- L74 _public function_ `void Emplace()`
- L76 _public function_ `TToVValue& operator=(NativeType Other)`
- L81 _public function_ `TToVValue& operator=(TOptional<NativeType> Other)`
- L87 _public function_ `operator TOptional<NativeType>&()`
- L88 _public function_ `NativeType& operator*()`
- L95 _public member_ `TOptional<ObjectType*> Value;`
- L99 _public function_ `TToVValue& operator=(TNonNullPtr<ObjectType> Other)`
- L104 _public function_ `TToVValue& operator=(TOptional<TNonNullPtr<ObjectType>> Other)`

#### struct `Verse::TToVValue`  
`template <typename ObjectType> struct TToVValue<TNonNullPtr<ObjectType>>`  
_L93-116_
- desc: Marshal class objects through a raw pointer.
- L72 _public member_ `TOptional<NativeType> Value;`
- L74 _public function_ `void Emplace()`
- L76 _public function_ `TToVValue& operator=(NativeType Other)`
- L81 _public function_ `TToVValue& operator=(TOptional<NativeType> Other)`
- L87 _public function_ `operator TOptional<NativeType>&()`
- L88 _public function_ `NativeType& operator*()`
- L95 _public member_ `TOptional<ObjectType*> Value;`
- L99 _public function_ `TToVValue& operator=(TNonNullPtr<ObjectType> Other)`
- L104 _public function_ `TToVValue& operator=(TOptional<TNonNullPtr<ObjectType>> Other)`

#### struct `Verse::TFromVValue`  
`template <typename NativeType, typename = void> struct TFromVValue`  
_L124-128_
- desc: Out parameter for FromVValue - a default-constructible version of NativeType.
- L126 _public member_ `NativeType Value;`
- L127 _public function_ `NativeType GetValue()`
- L133 _public member_ `NativeType* Value;`
- L134 _public function_ `TNonNullPtr<NativeType> GetValue()`
- L144 _public member_ `const NativeType* Value;`
- L145 _public function_ `const NativeType& GetValue()`
- L151 _public member_ `NativeType Value{EDefaultConstructNativeType::UnsafeDoNotUse};`

#### struct `Verse::TFromVValue`  
`template <typename NativeType> struct TFromVValue<TNonNullPtr<NativeType>>`  
_L131-135_
- L126 _public member_ `NativeType Value;`
- L127 _public function_ `NativeType GetValue()`
- L133 _public member_ `NativeType* Value;`
- L134 _public function_ `TNonNullPtr<NativeType> GetValue()`
- L144 _public member_ `const NativeType* Value;`
- L145 _public function_ `const NativeType& GetValue()`
- L151 _public member_ `NativeType Value{EDefaultConstructNativeType::UnsafeDoNotUse};`

#### struct `Verse::TFromVValue`  
`template <typename NativeType> struct TFromVValue<NativeType, typename TEnableIf<TIsNativeStruct<NativeType>::Value>::Type>`  
_L142-146_
- L126 _public member_ `NativeType Value;`
- L127 _public function_ `NativeType GetValue()`
- L133 _public member_ `NativeType* Value;`
- L134 _public function_ `TNonNullPtr<NativeType> GetValue()`
- L144 _public member_ `const NativeType* Value;`
- L145 _public function_ `const NativeType& GetValue()`
- L151 _public member_ `NativeType Value{EDefaultConstructNativeType::UnsafeDoNotUse};`

#### struct `Verse::TFromVValue`  
`template <class NativeType UE_REQUIRES(std::is_convertible_v<NativeType*, FNativeType*>)> struct TFromVValue<NativeType>`  
_L149-153_
- L126 _public member_ `NativeType Value;`
- L127 _public function_ `NativeType GetValue()`
- L133 _public member_ `NativeType* Value;`
- L134 _public function_ `TNonNullPtr<NativeType> GetValue()`
- L144 _public member_ `const NativeType* Value;`
- L145 _public function_ `const NativeType& GetValue()`
- L151 _public member_ `NativeType Value{EDefaultConstructNativeType::UnsafeDoNotUse};`

#### struct `Verse::FNativeConverter`  
`struct AUTORTFM_DISABLE FNativeConverter`  
_L157-571_
- desc: This class defines canonical conversion functions between two runtime value representations: VValue-based representation and C++/native-based representation
- L161 _public function_ `static VValue ToVValue(FAllocationContext Context, EVerseFalse)`
- L167 _public function_ `static VValue ToVValue(FAllocationContext Context, EVerseTrue)`
- L172 _public function_ `static VValue ToVValue(FAllocationContext Context, bool Logic)`
- L177 _public function_ `static VValue ToVValue(FAllocationContext Context, int64 Number)`
- L182 _public function_ `static VValue ToVValue(FAllocationContext Context, const FVerseRational& Rational)`
- L189 _public function_ `static VValue ToVValue(FAllocationContext Context, double Number)`
- L194 _public function_ `static VValue ToVValue(FAllocationContext Context, const FNativeString& String)`
- L199 _public function_ `static VValue ToVValue(FAllocationContext Context, UTF8CHAR Char)`
- L204 _public function_ `static VValue ToVValue(FAllocationContext Context, UTF32CHAR Char32)`
- L210 _public function_ `template <typename EnumType, typename = typename TEnableIf<TIsEnumClass<EnumType>::Value>::Type> static VValue ToVValue(FAllocationContext Context, EnumType Enumerator)`
- L218 _public function_ `template <class ObjectType> static VValue ToVValue(FAllocationContext Context, ObjectType* Object)`
- L226 _public function_ `template <class ObjectType> static VValue ToVValue(FAllocationContext Context, TNonNullPtr<ObjectType> Object)`
- L231 _public function_ `template <class ObjectType> static VValue ToVValue(FAllocationContext Context, ::TObjectPtr<ObjectType> Object)`
- L237 _public prototype_ `template <class InterfaceProxyType> static VValue ToVValue(FAllocationContext Context, TInterfaceInstance<InterfaceProxyType> Object);`
- L240 _public function_ `template <class StructType, typename = typename TEnableIf<TIsNativeStruct<typename TDecay<StructType>::Type>::Value>::Type> static VValue ToVValue(FAllocationContext Context, StructType&& Struct)`
- L246 _public function_ `template <typename... ElementTypes> static VValue ToVValue(FAllocationContext Context, const TNativeTuple<ElementTypes...>& Tuple)`
- L252 _public function_ `template <typename... ElementTypes, size_t... Indices> static VValue ToVValue(FAllocationContext Context, const TNativeTuple<ElementTypes...>& Tuple, std::index_sequence<Indices...>)`
- L258 _public function_ `template <class NativeType UE_REQUIRES(std::is_convertible_v<NativeType*, FNativeType*>)> static VValue ToVValue(FAllocationContext Context, const NativeType& Type)`
- L264 _public function_ `template <class ElementType> static VValue ToVValue(FAllocationContext Context, const TArray<ElementType>& Array)`
- L273 _public function_ `template <class KeyType, class ValueType> static VValue ToVValue(FAllocationContext Context, const TMap<KeyType, ValueType>& Map)`
- L286 _public function_ `template <typename ValueType> static VValue ToVValue(FAllocationContext Context, const ::TOptional<ValueType>& Optional)`
- L298 _public function_ `static VValue ToVValue(FAllocationContext Context, const ::FNullOpt& Optional)`
- L303 _public prototype_ `static VValue ToVValue(FAllocationContext Context, const FVerseValue& Value);`
- L304 _public prototype_ `static VValue ToVValue(FAllocationContext Context, const FVerseFunction& Function);`
- L308 _public function_ `static FOpResult FromVValue(FAllocationContext Context, const VValue Value, TFromVValue<EVerseTrue>& OutNative)`
- L315 _public function_ `static FOpResult FromVValue(FAllocationContext Context, const VValue Value, TFromVValue<bool>& OutNative)`
- L323 _public function_ `static FOpResult FromVValue(FAllocationContext Context, const VValue Value, TFromVValue<int64>& OutNative)`
- L337 _public function_ `static FOpResult FromVValue(FAllocationContext Context, const VValue Value, TFromVValue<FVerseRational>& OutNative)`
- L373 _public function_ `static FOpResult FromVValue(FAllocationContext Context, const VValue Value, TFromVValue<double>& OutNative)`
- L381 _public function_ `static FOpResult FromVValue(FAllocationContext Context, const VValue Value, TFromVValue<FNativeString>& OutNative)`
- L400 _public function_ `static FOpResult FromVValue(FAllocationContext Context, const VValue Value, TFromVValue<UTF8CHAR>& OutNative)`
- L408 _public function_ `static FOpResult FromVValue(FAllocationContext Context, const VValue Value, TFromVValue<UTF32CHAR>& OutNative)`
- L418 _public function_ `FromVValue(FAllocationContext Context, const VValue Value, TFromVValue<EnumType>& OutNative)`
- L433 _public function_ `template <class ObjectType> static FOpResult FromVValue(FAllocationContext Context, const VValue Value, TFromVValue<TNonNullPtr<ObjectType>>& OutNative)`
- L443 _public prototype_ `template <class InterfaceProxyType> static FOpResult FromVValue(FAllocationContext Context, const VValue Value, TFromVValue<TInterfaceInstance<InterfaceProxyType>>& OutNative);`
- L447 _public function_ `FromVValue(FAllocationContext Context, const VValue Value, TFromVValue<StructType>& OutNative)`
- L455 _public function_ `template <typename... ElementTypes> static FOpResult FromVValue(FAllocationContext Context, const VValue Value, TFromVValue<TNativeTuple<ElementTypes...>>& OutNative)`
- L461 _public function_ `template <typename... ElementTypes, size_t... Indices> static FOpResult FromVValue(FAllocationContext Context, const VValue Value, TFromVValue<TNativeTuple<ElementTypes...>>& OutNative, std::index_sequence<Indices...>)`
- L483 _public function_ `template <class NativeType UE_REQUIRES(std::is_convertible_v<NativeType*, FNativeType*>)> static FOpResult FromVValue(FAllocationContext Context, const VValue Value, TFromVValue<NativeType>& OutNative)`
- L498 _public function_ `template <class ElementType> static FOpResult FromVValue(FAllocationContext Context, const VValue Value, TFromVValue<TArray<ElementType>>& OutNative)`
- L519 _public function_ `template <class KeyType, class ValueType> static FOpResult FromVValue(FAllocationContext Context, const VValue Value, TFromVValue<TMap<KeyType, ValueType>>& OutNative)`
- L546 _public function_ `template <typename ValueType> static FOpResult FromVValue(FAllocationContext Context, const VValue Value, TFromVValue<TOptional<ValueType>>& OutNative)`
- L567 _public prototype_ `static FOpResult FromVValue(FAllocationContext Context, const VValue Value, TFromVValue<FVerseValue>& OutNative);`
- L570 _public prototype_ `template <typename ReturnType, typename... ParamTypes> static FOpResult FromVValue(FAllocationContext Context, const VValue Value, TFromVValue<TVerseFunction<ReturnType(ParamTypes...)>>& OutNative);`

#### Free symbols / members of external scopes

- L58 _namespace_ `namespace Verse`
- L266 _function_ `VArray& NewArray = VArray::New(Context, Array.Num(), [Context, &Array](uint32 Index) { return ToVValue(Context, Array[Index]); });` (scope `Verse::FNativeConverter::ToVValue`)
- L282 _function_ `return VMapBase::New<VMap>(Context, Pairs.Num(), [&](uint32 I) { return Pairs[I]; });` (scope `Verse::FNativeConverter::ToVValue`)
- L466 _function_ `auto ElementFromVValue = [&](const VValue ElementValue, auto& OutNativeElement)` (scope `Verse::FNativeConverter::FromVValue`)
- L576 _function_ `template <typename NativeType> NativeType FVRestValueProperty::GetVersePropertyValue_InContainer(const void* Container) const` (scope `FVRestValueProperty`)
- L578 _function_ `return AutoRTFM::Open([this, Container] { Verse::FRunningContext Context = Verse::FRunningContextPromise{}; Verse::VRestValue* RestValue = const_cast<Verse::VRestValue*>(GetPropertyValuePtr_InContainer(Container)); Verse::TFromVValue<NativeType> NativeValue; Verse::FOpResult Result = Verse::FNativeConverter::FromVValue(Context, RestValue->Get(Context), NativeValue); V_DIE_UNLESS(Result.IsReturn()); return NativeValue.GetValue(); });` (scope `FVRestValueProperty::GetVersePropertyValue_InContainer`)

### `Source/Runtime/CoreUObject/Public/VerseVM/VVMNativeProcedure.h` (Public)


#### struct `Verse::VNativeProcedure`  
`struct VNativeProcedure : VCell`  
_L25-63_
- inherits: `VCell`
- desc: A function that is implemented in C++
- L28 _public member_ `static TGlobalTrivialEmergentTypePtr<&StaticCppClassInfo> GlobalTrivialEmergentType;`
- L30 _public member_ `static constexpr char DecoratorString[] = "Na`
- L33 _public typedef_ `using Args = TArrayView<VValue>;` — Interface between VerseVM and C++
- L34 _public typedef_ `using FThunkFn = FNativeCallResult (*)(FRunningContext, VValue Self, Args Arguments);`
- L36 _public member_ `uint32 NumPositionalParameters;`
- L39 _public member_ `FThunkFn Thunk;` — The C++ function to call
- L41 _public member_ `TWriteBarrier<VUniqueString> Name;`
- L43 _public function_ `AUTORTFM_DISABLE static VNativeProcedure& New(FAllocationContext Context, uint32 NumPositionalParameters, FThunkFn Thunk, VUniqueString& InName)`
- L49 _public prototype_ `static void SetThunk(Verse::VPackage* Package, FUtf8StringView VerseScopePath, FUtf8StringView DecoratedName, FThunkFn NativeFuncPtr);` — Lookup a native function and set it's thunk to a C++ function
- L51 _public prototype_ `AUTORTFM_DISABLE void AppendToStringImpl(FAllocationContext Context, FUtf8StringBuilderBase& Builder, EValueStringFormat Format, TSet<const void*>& VisitedObjects, uint32 RecursionDepth);`
- L52 _public prototype_ `AUTORTFM_DISABLE static void SerializeLayout(FAllocationContext Context, VNativeProcedure*& This, FStructuredArchiveVisitor& Visitor);`
- L53 _public prototype_ `AUTORTFM_DISABLE void SerializeImpl(FAllocationContext Context, FStructuredArchiveVisitor& Visitor);`
- L56 _private function_ `AUTORTFM_DISABLE VNativeProcedure(FAllocationContext Context, uint32 InNumPositionalParameters, FThunkFn InThunk, VUniqueString* InName) : VCell(Context, &GlobalTrivialEmergentType.Get(Context)) , NumPositionalParameters(InNumPositionalParameters) , Thunk(InThunk) , Name(Context, InName)`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace Verse`
- L22 _typedef_ `using FNativeCallResult = FOpResult;` (scope `Verse`)

### `Source/Runtime/CoreUObject/Public/VerseVM/VVMNativeRational.h` (Public)


#### struct `FVerseRational`  
`struct FVerseRational`  
_L13-79_
- reflection: `USTRUCT()`
- desc: Used to represent integer rational numbers in Verse.
- L18 _public member_ `int64 Numerator{0};` — `UPROPERTY(EditAnywhere, Category = Rational)`
- L21 _public member_ `int64 Denominator{1};` — `UPROPERTY(EditAnywhere, Category = Rational)`
- L23 _public function_ `FVerseRational ReduceAndNormalizeSigns() const`

#### struct `TStructOpsTypeTraits`  
`template <> struct TStructOpsTypeTraits<FVerseRational> : public TStructOpsTypeTraitsBase2<FVerseRational>`  
_L82-88_
- inherits: `TStructOpsTypeTraitsBase2<FVerseRational>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L85-87_

#### Free symbols / members of external scopes

- L53 _function_ `friend bool operator==(const FVerseRational& A, const FVerseRational& B)`
- L61 _function_ `friend uint32 GetTypeHash(const FVerseRational& R)`
- L71 _function_ `friend void operator<<(FStructuredArchive::FSlot Slot, FVerseRational& R)`
- L86 _enumerator_ `WithIdenticalViaEquality = true` (scope `TStructOpsTypeTraits::__anon0048cce20103`)

### `Source/Runtime/CoreUObject/Public/VerseVM/VVMNativeRef.h` (Public)


#### struct `Verse::VNativeRef`  
`struct AUTORTFM_DISABLE VNativeRef : VCell`  
_L15-120_
- inherits: `VCell`
- L18 _public member_ `static TGlobalTrivialEmergentTypePtr<&StaticCppClassInfo> GlobalTrivialEmergentType;`
- L27 _public member_ `TWriteBarrier<VValue> Base;` — The source this ref was projected from. Either a UObject, a VNativeStruct, or another VNativeRef.
- L30 _public member_ `uint64 Epoch;` — The time this ref was projected from Base. A ref may have been invalidated if Base.Epoch < Context.GetWriteEpoch().
- L38 _public member_ `EType Type;`
- L40 _public prototype_ `TPair<void*, FProperty*> GetData(FAllocationContext Context);`
- L42 _public prototype_ `FOpResult Call(FAllocationContext Context, VValue Argument, bool bSet);`
- L43 _public prototype_ `FOpResult LoadField(FAllocationContext Context, VUniqueString& FieldName);`
- L45 _public prototype_ `FOpResult Get(FAllocationContext Context);`
- L51 _public prototype_ `static FOpResult Get(FAllocationContext Context, const void* Container, FProperty* Property);` — Returns FOpResult::Return on success, with a freshly-allocated, VValue-based copy of the property data in the result's Value. If an error occurs while accessing the native field, generates a runtime error and then returns FOpResult::Error.
- L57 _public prototype_ `static VValue Peek(FAllocationContext Context, const void* Container, FProperty* Property);` — Returns a freshly-allocated, VValue-based copy of the property data in the result's Value. If an error occurs while accessing the native field, returns an uninitialized VValue.
- L63 _public prototype_ `static FOpResult GetStruct(FAllocationContext Context, const void* Data, UScriptStruct* Struct);` — Returns FOpResult::Return on success, with a freshly-allocated, VValue-based copy of the struct in the result's Value. If an error occurs while accessing the struct, generates a runtime error and then returns FOpResult::Error.
- L69 _public prototype_ `static VValue PeekStruct(FAllocationContext Context, const void* Data, UScriptStruct* Struct);` — Returns FOpResult::Return on success, with a freshly-allocated, VValue-based copy of the struct in the result's Value. If an error occurs while accessing the native field, returns an uninitialized VValue.
- L71 _public prototype_ `FOpResult Set(FAllocationContext Context, VValue Value);`
- L73 _public prototype_ `FOpResult SetNonTransactionally(FAllocationContext Context, VValue Value);`
- L76 _public prototype_ `template <EWriteMode WriteMode, typename BaseType> static FOpResult Set(FAllocationContext Context, BaseType Base, void* Container, FProperty* Property, VValue Value);`
- L78 _public function_ `static VNativeRef& New(FAllocationContext Context, UObject* Base, FProperty* Property)`
- L83 _public function_ `static VNativeRef& New(FAllocationContext Context, VNativeStruct* Base, FProperty* Property)`
- L88 _public function_ `static VNativeRef& New(FAllocationContext Context, VNativeRef* Base, FProperty* Property)`
- L93 _public function_ `static VNativeRef& New(FAllocationContext Context, VNativeRef* Base, int32 Index)`
- L98 _public prototype_ `FOpResult FreezeImpl(FAllocationContext Context, VTask* Task);`
- L101 _private function_ `VNativeRef(FAllocationContext Context, VValue InBase, FProperty* InProperty) : VCell(Context, &GlobalTrivialEmergentType.Get(Context)) , Base(Context, InBase) , Epoch(Context.GetWriteEpoch()) , UProperty(InProperty) , Type(EType::FProperty)`
- L111 _private function_ `VNativeRef(FAllocationContext Context, VValue InBase, int32 InIndex) : VCell(Context, &GlobalTrivialEmergentType.Get(Context)) , Base(Context, InBase) , Epoch(Context.GetWriteEpoch()) , Index(InIndex) , Type(EType::Index)`
- L122 _prototype_ `extern template FOpResult VNativeRef::Set<EWriteMode::Transactional>(FAllocationContext Context, UObject* Base, void* Container, FProperty* Property, VValue Value);`
- L123 _prototype_ `extern template FOpResult VNativeRef::Set<EWriteMode::Transactional>(FAllocationContext Context, VNativeStruct* Base, void* Container, FProperty* Property, VValue Value);`
- L124 _prototype_ `extern template FOpResult VNativeRef::Set<EWriteMode::NonTransactional>(FAllocationContext Context, std::nullptr_t Base, void* Container, FProperty* Property, VValue Value);`

#### enum `Verse::VNativeRef::EType`  
`enum class EType : uint8`  
_L20-24_
- L22 _public enumerator_ `FProperty`
- L23 _public enumerator_ `Index`

#### union `Verse::VNativeRef::(anonymous)`  
``  
_L33-36_

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace Verse`
- L34 _member_ `FProperty* UProperty;` (scope `Verse::VNativeRef::__anon7bda56a5010a`)
- L35 _member_ `int32 Index;` (scope `Verse::VNativeRef::__anon7bda56a5010a`)

### `Source/Runtime/CoreUObject/Public/VerseVM/VVMNativeString.h` (Public)


#### struct `TIsZeroConstructType`  
`template <> struct TIsZeroConstructType<Verse::FNativeString>`  
_L17-20_
- L19 _public member_ `static constexpr bool Value = true;`

#### struct `TIsContiguousContainer`  
`template <> struct TIsContiguousContainer<Verse::FNativeString>`  
_L23-26_
- L25 _public member_ `static constexpr bool Value = true;`

#### class `Verse::FNativeString`  
`class FNativeString`  
_L33-239_
- desc: Wraps a copy-on-write reference to a Utf8String to give it Verse semantics, and since we copy objects around and don't modify them often in the VM gives us a performance uplift in heavy string workloads.
- L124 _public typedef_ `using ElementType = FUtf8String::ElementType;`
- L127 _public member_ `static constexpr AutoRTFM::EReturnFromOpenMode AutoRTFMReturnFromOpenMode = AutoRTFM::EReturnFromOpenMode::CopyConstructInClosed;` — FNativeString can be returned from AutoRTFM::Open() via a copy-construction in the closed.
- L130 _private member_ `FCopyOnWrite Payload;`
- L133 _public prototype_ `FNativeString() = default;`
- L134 _public prototype_ `FNativeString(FNativeString&&) = default;`
- L135 _public prototype_ `FNativeString(const FNativeString&) = default;`
- L136 _public prototype_ `FNativeString& operator=(FNativeString&&) = default;`
- L137 _public prototype_ `FNativeString& operator=(const FNativeString&) = default;`
- L139 _public function_ `UE_FORCEINLINE_HINT FNativeString(const ANSICHAR* Str) : Payload(Str)`
- L142 _public function_ `UE_FORCEINLINE_HINT FNativeString(FUtf8String&& InString) : Payload(MoveTemp(InString))`
- L149 _public function_ `typename CharRangeType, typename CharRangeElementType = TElementType_T<CharRangeType>> requires(!std::is_same_v<std::decay_t<CharRangeType>, FNativeString> && TIsContiguousContainer<CharRangeType>::Value && TIsCharType_V<CharRangeElementType>) UE_FORCEINLINE_HINT explicit FNativeString(CharRangeType&& Range) : Payload(FUtf8String(Forward<CharRangeType>(Range)))`
- L158 _public function_ `typename CharRangeType, typename CharRangeElementType = TElementType_T<CharRangeType>> requires(!std::is_same_v<std::decay_t<CharRangeType>, FNativeString> && TIsContiguousContainer<CharRangeType>::Value && TIsCharType_V<CharRangeElementType>) inline FNativeString& operator=(CharRangeType&& Range)`
- L169 _public function_ `UE_FORCEINLINE_HINT ElementType& operator[](int32 Index) UE_LIFETIMEBOUND`
- L170 _public function_ `UE_FORCEINLINE_HINT const ElementType& operator[](int32 Index) const UE_LIFETIMEBOUND`
- L172 _public function_ `[[nodiscard]] UE_FORCEINLINE_HINT const ElementType* operator*() const UE_LIFETIMEBOUND`
- L174 _public function_ `[[nodiscard]] UE_FORCEINLINE_HINT int Len() const`
- L175 _public function_ `[[nodiscard]] UE_FORCEINLINE_HINT bool IsEmpty() const`
- L176 _public function_ `[[nodiscard]] UE_FORCEINLINE_HINT bool IsValidIndex(int32 Index) const`
- L190 _public function_ `[[nodiscard]] UE_FORCEINLINE_HINT bool Equals(const FNativeString& Other) const`
- L200 _public function_ `void Reset(int32 NewReservedSize = 0)`
- L206 _public function_ `inline FNativeString& operator+=(CharRangeType&& Str)`
- L211 _public function_ `inline FNativeString& operator+=(const ANSICHAR* Str)`
- L233 _public function_ `template <typename... Types> [[nodiscard]] UE_FORCEINLINE_HINT static FNativeString Printf(UE::Core::TCheckedFormatString<FUtf8String::FmtCharType, Types...> Fmt, Types... Args)`

#### struct `Verse::FNativeString::FCopyOnWriteContents`  
`struct FCopyOnWriteContents final`  
_L35-68_
- L37 _public prototype_ `FCopyOnWriteContents() = default;`
- L38 _public function_ `FCopyOnWriteContents(const FUtf8String& InString) : String(InString)`
- L40 _public function_ `FCopyOnWriteContents(FUtf8String&& InString) : String(MoveTemp(InString))`
- L43 _public member_ `FUtf8String String;`
- L44 _public member_ `mutable int32 CachedHash = 0;`
- L46 _public function_ `inline int32 Hash() const`
- L64 _public function_ `UE_FORCEINLINE_HINT void ResetCachedHash()`

#### struct `Verse::FNativeString::FCopyOnWrite`  
`struct FCopyOnWrite final`  
_L70-121_
- L72 _public prototype_ `UE_FORCEINLINE_HINT FCopyOnWrite() = default;`
- L73 _public function_ `UE_FORCEINLINE_HINT FCopyOnWrite(const FUtf8String& InString) : Payload(MakeShared<FCopyOnWriteContents, ESPMode::ThreadSafe>(InString))`
- L75 _public function_ `UE_FORCEINLINE_HINT FCopyOnWrite(FUtf8String&& InString) : Payload(MakeShared<FCopyOnWriteContents, ESPMode::ThreadSafe>(MoveTemp(InString)))`
- L78 _public function_ `const FUtf8String& Read() const`
- L84 _public function_ `FUtf8String& Write()`
- L100 _public function_ `int32 Hash() const`
- L107 _private member_ `TSharedPtr<FCopyOnWriteContents, ESPMode::ThreadSafe> Payload;`
- L111 _private function_ `inline bool SetIfNull()`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace Verse`
- L28 _namespace_ `namespace Verse`
- L164 _function_ `friend UE_FORCEINLINE_HINT ElementType* GetData(FNativeString& InString)` (scope `Verse`)
- L165 _function_ `friend UE_FORCEINLINE_HINT const ElementType* GetData(const FNativeString& InString)` (scope `Verse`)
- L167 _function_ `friend UE_FORCEINLINE_HINT int32 GetNum(const FNativeString& InString)` (scope `Verse`)
- L178 _function_ `[[nodiscard]] UE_FORCEINLINE_HINT friend bool operator==(const FNativeString& Lhs, const FNativeString& Rhs)` (scope `Verse`)
- L184 _function_ `[[nodiscard]] UE_FORCEINLINE_HINT friend bool operator!=(const FNativeString& Lhs, const FNativeString& Rhs)` (scope `Verse`)
- L195 _function_ `friend UE_FORCEINLINE_HINT int32 GetTypeHash(const FNativeString& S)` (scope `Verse`)
- L221 _function_ `inline friend FNativeString operator+(FNativeString&& Lhs, CharRangeType&& Rhs)` (scope `Verse`)
- L226 _function_ `inline friend FNativeString operator+(FNativeString&& Lhs, const ANSICHAR* Rhs)` (scope `Verse`)
- L238 _function_ `friend UE_FORCEINLINE_HINT FArchive& operator<<(FArchive& Ar, FNativeString& S)` (scope `Verse`)
- L243 _typedef_ `using FVerseString = Verse::FNativeString;` — A more UHT friendly name for a verse native string

### `Source/Runtime/CoreUObject/Public/VerseVM/VVMNativeStruct.h` (Public)


#### struct `Verse::VNativeStruct`  
`struct VNativeStruct : VObject`  
_L17-55_
- inherits: `VObject`
- desc: A variant of Verse object that boxes a native (C++ defined) struct
- L20 _public member_ `static TGlobalTrivialEmergentTypePtr<&StaticCppClassInfo> GlobalTrivialEmergentType;`
- L23 _public prototype_ `template <class CppStructType> CppStructType& GetStruct();`
- L24 _public prototype_ `void* GetStruct();`
- L26 _public prototype_ `static UScriptStruct* GetUScriptStruct(VEmergentType& EmergentType);`
- L30 _public prototype_ `template <class CppStructType> AUTORTFM_DISABLE static VNativeStruct& New(FAllocationContext Context, VEmergentType& InEmergentType, CppStructType&& InStruct);` — Allocate a new VNativeStruct and move an existing struct into it
- L33 _public prototype_ `AUTORTFM_DISABLE static VNativeStruct& NewUninitialized(FAllocationContext Context, VEmergentType& InEmergentType);` — Allocate a new blank VNativeStruct
- L35 _public prototype_ `AUTORTFM_DISABLE VNativeStruct& Duplicate(FAllocationContext Context);`
- L40 _protected prototype_ `AUTORTFM_DISABLE static std::byte* AllocateCell(FAllocationContext Context, size_t Size, bool bHasDestructor);`
- L43 _protected prototype_ `template <class CppStructType> AUTORTFM_DISABLE VNativeStruct(FAllocationContext Context, VEmergentType& InEmergentType, CppStructType&& InStruct);`
- L44 _protected prototype_ `AUTORTFM_DISABLE VNativeStruct(FAllocationContext Context, VEmergentType& InEmergentType);`
- L45 _protected prototype_ `AUTORTFM_DISABLE VNativeStruct(FAllocationContext Context);`
- L46 _protected prototype_ `~VNativeStruct();`
- L48 _protected prototype_ `ECompares EqualImpl(FAllocationContext Context, VCell* Other, const TFunction<void(::Verse::VValue, ::Verse::VValue)>& HandlePlaceholder);`
- L49 _protected prototype_ `uint32 GetTypeHashImpl();`
- L50 _protected prototype_ `AUTORTFM_DISABLE VValue MeltImpl(FAllocationContext Context);`
- L51 _protected prototype_ `AUTORTFM_DISABLE FOpResult FreezeImpl(FAllocationContext Context, VTask* Task);`
- L52 _protected prototype_ `AUTORTFM_DISABLE static void SerializeLayout(FAllocationContext, VNativeStruct*&, FStructuredArchiveVisitor&);`
- L53 _protected prototype_ `AUTORTFM_DISABLE void SerializeImpl(FAllocationContext, FStructuredArchiveVisitor&);`
- L54 _protected member_ `static constexpr bool InstancedCell = true;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace Verse`
- L14 _prototype_ `template <typename CppStructType> VClass& StaticVClass();` (scope `Verse`)

### `Source/Runtime/CoreUObject/Public/VerseVM/VVMNativeTuple.h` (Public)


#### struct `Verse::TNativeTuple`  
`template <> struct TNativeTuple<>`  
_L41-43_
- desc: Verse native tuple - empty specialization
- L51 _public member_ `Type First;`
- L53 _public prototype_ `TNativeTuple() = default;`
- L55 _public function_ `TNativeTuple(const Type& Arg) : First(Arg)`
- L61 _public function_ `template <typename TArg, typename = typename TEnableIf<TIsConstructible<Type, TArg&&>::Value>::Type> TNativeTuple(TArg&& Arg) : First(Forward<TArg>(Arg))`
- L67 _public function_ `template <size_t Idx> constexpr auto& Get()`
- L73 _public function_ `template <size_t Idx> constexpr const auto& Get() const`
- L97 _public member_ `TNativeTuple<RestTypes...> Rest;`
- L101 _public function_ `TNativeTuple(const Type& Arg, const RestTypes&... Args) : First(Arg) , Rest(Args...)`
- L108 _public function_ `template <typename TArg, typename... TArgs, typename = typename TEnableIf<sizeof...(RestTypes) == sizeof...(TArgs)>::Type> TNativeTuple(TArg&& Arg, TArgs&&... Args) : First(Forward<TArg>(Arg)) , Rest(Forward<TArgs>(Args)...)`
- L115 _public function_ `template <typename OtherType, typename... OtherRestTypes, typename = typename TEnableIf<sizeof...(RestTypes) == sizeof...(OtherRestTypes)>::Type> TNativeTuple(const TNativeTuple<OtherType, OtherRestTypes...>& Other) : First(Other.First) , Rest(Other.Rest)`

#### struct `Verse::TNativeTuple`  
`template <typename Type> struct TNativeTuple<Type>`  
_L49-86_
- desc: Singly typed tuple - this is important to provide so that sizeof(TNativeTuple<float>) == sizeof(float), otherwise if the below tuple definition is used, we get sizeof(TNativeTuple<float>) == sizeof(float) + sizeof(TNativeTuple<>)
- L51 _public member_ `Type First;`
- L53 _public prototype_ `TNativeTuple() = default;`
- L55 _public function_ `TNativeTuple(const Type& Arg) : First(Arg)`
- L61 _public function_ `template <typename TArg, typename = typename TEnableIf<TIsConstructible<Type, TArg&&>::Value>::Type> TNativeTuple(TArg&& Arg) : First(Forward<TArg>(Arg))`
- L67 _public function_ `template <size_t Idx> constexpr auto& Get()`
- L73 _public function_ `template <size_t Idx> constexpr const auto& Get() const`
- L97 _public member_ `TNativeTuple<RestTypes...> Rest;`
- L101 _public function_ `TNativeTuple(const Type& Arg, const RestTypes&... Args) : First(Arg) , Rest(Args...)`
- L108 _public function_ `template <typename TArg, typename... TArgs, typename = typename TEnableIf<sizeof...(RestTypes) == sizeof...(TArgs)>::Type> TNativeTuple(TArg&& Arg, TArgs&&... Args) : First(Forward<TArg>(Arg)) , Rest(Forward<TArgs>(Args)...)`
- L115 _public function_ `template <typename OtherType, typename... OtherRestTypes, typename = typename TEnableIf<sizeof...(RestTypes) == sizeof...(OtherRestTypes)>::Type> TNativeTuple(const TNativeTuple<OtherType, OtherRestTypes...>& Other) : First(Other.First) , Rest(Other.Rest)`

#### struct `Verse::TNativeTuple`  
`template <typename Type, typename... RestTypes> struct TNativeTuple<Type, RestTypes...>`  
_L91-145_
- desc: Recursively defined tuple
- L51 _public member_ `Type First;`
- L53 _public prototype_ `TNativeTuple() = default;`
- L55 _public function_ `TNativeTuple(const Type& Arg) : First(Arg)`
- L61 _public function_ `template <typename TArg, typename = typename TEnableIf<TIsConstructible<Type, TArg&&>::Value>::Type> TNativeTuple(TArg&& Arg) : First(Forward<TArg>(Arg))`
- L67 _public function_ `template <size_t Idx> constexpr auto& Get()`
- L73 _public function_ `template <size_t Idx> constexpr const auto& Get() const`
- L97 _public member_ `TNativeTuple<RestTypes...> Rest;`
- L101 _public function_ `TNativeTuple(const Type& Arg, const RestTypes&... Args) : First(Arg) , Rest(Args...)`
- L108 _public function_ `template <typename TArg, typename... TArgs, typename = typename TEnableIf<sizeof...(RestTypes) == sizeof...(TArgs)>::Type> TNativeTuple(TArg&& Arg, TArgs&&... Args) : First(Forward<TArg>(Arg)) , Rest(Forward<TArgs>(Args)...)`
- L115 _public function_ `template <typename OtherType, typename... OtherRestTypes, typename = typename TEnableIf<sizeof...(RestTypes) == sizeof...(OtherRestTypes)>::Type> TNativeTuple(const TNativeTuple<OtherType, OtherRestTypes...>& Other) : First(Other.First) , Rest(Other.Rest)`

#### struct `Verse::TGetTupleElem`  
`template <typename Type, typename... RestTypes> struct TGetTupleElem<0, TNativeTuple<Type, RestTypes...>>`  
_L150-161_
- desc: Helper for tuple element accessor - Zeroth specialization
- L152 _public function_ `constexpr static Type& Get(TNativeTuple<Type, RestTypes...>& Data)`
- L157 _public function_ `constexpr static const Type& Get(const TNativeTuple<Type, RestTypes...>& Data)`
- L168 _public function_ `constexpr static decltype(auto) Get(TNativeTuple<Type, RestTypes...>& Data)`
- L173 _public function_ `constexpr static decltype(auto) Get(const TNativeTuple<Type, RestTypes...>& Data)`

#### struct `Verse::TGetTupleElem`  
`template <size_t Idx, typename Type, typename... RestTypes> struct TGetTupleElem<Idx, TNativeTuple<Type, RestTypes...>>`  
_L166-177_
- desc: Helper for tuple element accessor - recursive definition
- L152 _public function_ `constexpr static Type& Get(TNativeTuple<Type, RestTypes...>& Data)`
- L157 _public function_ `constexpr static const Type& Get(const TNativeTuple<Type, RestTypes...>& Data)`
- L168 _public function_ `constexpr static decltype(auto) Get(TNativeTuple<Type, RestTypes...>& Data)`
- L173 _public function_ `constexpr static decltype(auto) Get(const TNativeTuple<Type, RestTypes...>& Data)`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace Verse`
- L78 _function_ `friend bool operator==(const TNativeTuple<Type>& Lhs, const TNativeTuple<Type>& Rhs)` (scope `Verse`)
- L82 _function_ `friend bool operator!=(const TNativeTuple<Type>& Lhs, const TNativeTuple<Type>& Rhs)` (scope `Verse`)
- L137 _function_ `friend bool operator==(const TNativeTuple<Type, RestTypes...>& Lhs, const TNativeTuple<Type, RestTypes...>& Rhs)` (scope `Verse`)
- L141 _function_ `friend bool operator!=(const TNativeTuple<Type, RestTypes...>& Lhs, const TNativeTuple<Type, RestTypes...>& Rhs)` (scope `Verse`)

### `Source/Runtime/CoreUObject/Public/VerseVM/VVMNativeType.h` (Public)


#### struct `TIsZeroConstructType`  
`template <> struct TIsZeroConstructType<Verse::FNativeType>`  
_L31-34_
- L33 _public member_ `static constexpr bool Value = true;`

#### enum `Verse::EDefaultConstructNativeType`  
`enum class EDefaultConstructNativeType`  
_L39-42_
- L41 _public enumerator_ `UnsafeDoNotUse`

#### class `Verse::FNativeType`  
`class FNativeType`  
_L46-81_
- desc: Opaque wrapper around VM-specific type representation
- L49 _public prototype_ `FNativeType() = delete;`
- L50 _public function_ `FNativeType(EDefaultConstructNativeType)`
- L52 _public function_ `FNativeType(UStruct* InType) : Type(InType)`
- L57 _public function_ `bool IsNullUnsafeDoNotUse() const`
- L58 _public function_ `bool IsEqualUnsafeDoNotUse(const FNativeType& Other) const`
- L59 _public function_ `UStruct* AsUEStructNullableUnsafeDoNotUse() const`
- L60 _public function_ `UClass* AsUEClassNullableUnsafeDoNotUse() const`
- L61 _public function_ `UClass* AsUEClassCheckedUnsafeDoNotUse() const`
- L64 _protected function_ `UClass* AsUEClassChecked() const`
- L69 _protected function_ `bool IsTypeOf(const UObject* Obj) const`
- L80 _private member_ `TObjectPtr<UStruct> Type;` — This class is used via FObjectProperty, so must be a thin wrapper around this pointer.
- L91 _public function_ `FNativeType(UStruct* InType)`
- L116 _public function_ `FNativeType(VType* InType)`
- L144 _public function_ `bool Subsumes(FAllocationContext Context, VCell& Object) const`
- L149 _public function_ `AUTORTFM_DISABLE TSharedPtr<FJsonValue> ToJSON( FRunningContext Context, EValueJSONFormat Format, TMap<const void*, EVisitState>& VisitedObjects, FToJsonCallback Callback, uint32 RecursionDepth, FJsonObject* Defs) const`
- L164 _public function_ `AUTORTFM_DISABLE VValue FromJSON(FRunningContext Context, const FJsonValue& JsonValue, EValueJSONFormat Format, FFromJsonCallback Callback) const`
- L169 _public function_ `bool IsSubtype(const Verse::VType& InType)`
- L194 _private member_ `TWriteBarrier<VType> Type;` — This class is used via FVRestValueProperty, so must be a thin wrapper around this pointer.

#### class `Verse::FNativeType`  
`class FNativeType`  
_L85-195_
- desc: Opaque wrapper around VM-specific type representation
- L49 _public prototype_ `FNativeType() = delete;`
- L50 _public function_ `FNativeType(EDefaultConstructNativeType)`
- L52 _public function_ `FNativeType(UStruct* InType) : Type(InType)`
- L57 _public function_ `bool IsNullUnsafeDoNotUse() const`
- L58 _public function_ `bool IsEqualUnsafeDoNotUse(const FNativeType& Other) const`
- L59 _public function_ `UStruct* AsUEStructNullableUnsafeDoNotUse() const`
- L60 _public function_ `UClass* AsUEClassNullableUnsafeDoNotUse() const`
- L61 _public function_ `UClass* AsUEClassCheckedUnsafeDoNotUse() const`
- L64 _protected function_ `UClass* AsUEClassChecked() const`
- L69 _protected function_ `bool IsTypeOf(const UObject* Obj) const`
- L80 _private member_ `TObjectPtr<UStruct> Type;` — This class is used via FObjectProperty, so must be a thin wrapper around this pointer.
- L91 _public function_ `FNativeType(UStruct* InType)`
- L116 _public function_ `FNativeType(VType* InType)`
- L144 _public function_ `bool Subsumes(FAllocationContext Context, VCell& Object) const`
- L149 _public function_ `AUTORTFM_DISABLE TSharedPtr<FJsonValue> ToJSON( FRunningContext Context, EValueJSONFormat Format, TMap<const void*, EVisitState>& VisitedObjects, FToJsonCallback Callback, uint32 RecursionDepth, FJsonObject* Defs) const`
- L164 _public function_ `AUTORTFM_DISABLE VValue FromJSON(FRunningContext Context, const FJsonValue& JsonValue, EValueJSONFormat Format, FFromJsonCallback Callback) const`
- L169 _public function_ `bool IsSubtype(const Verse::VType& InType)`
- L194 _private member_ `TWriteBarrier<VType> Type;` — This class is used via FVRestValueProperty, so must be a thin wrapper around this pointer.

#### class `Verse::TNativeSubtype`  
`template <class T, class BaseType = FNativeType, bool bAllowInvalid = false> class TNativeSubtype : public BaseType`  
_L199-250_
- inherits: `BaseType`
- L202 _public prototype_ `TNativeSubtype() = delete;`
- L203 _public function_ `TNativeSubtype(EDefaultConstructNativeType) : BaseType(EDefaultConstructNativeType::UnsafeDoNotUse)`
- L205 _public function_ `TNativeSubtype(BaseType&& Other) : BaseType(MoveTemp(Other))`
- L207 _public function_ `TNativeSubtype(const BaseType& Other) : BaseType(Other)`
- L209 _public function_ `TNativeSubtype& operator=(BaseType&& Other)`
- L215 _public function_ `TNativeSubtype& operator=(const BaseType& Other)`
- L225 _public function_ `TNativeSubtype(UClass* InType) : BaseType(InType)`
- L231 _public function_ `bool ValidateOrRaiseRuntimeError() const`
- L242 _private prototype_ `bool IsValid() const;`
- L243 _private function_ `void CheckValid() const`
- L289 _function_ `template <class T, class BaseType, bool bAllowInvalid> inline bool TNativeSubtype<T, BaseType, bAllowInvalid>::IsValid() const`

#### class `Verse::FNativeCastableType`  
`class FNativeCastableType : public FNativeType`  
_L254-259_
- inherits: `FNativeType`

#### class `Verse::FNativeConcreteType`  
`class FNativeConcreteType : public FNativeType`  
_L266-271_
- inherits: `FNativeType`

#### class `Verse::FNativeCastableConcreteType`  
`class FNativeCastableConcreteType : public FNativeType`  
_L278-283_
- inherits: `FNativeType`

#### Free symbols / members of external scopes

- L21 _namespace_ `namespace Verse`
- L36 _namespace_ `namespace Verse`
- L262 _typedef_ `template <class T> using TNativeCastableSubtype = TNativeSubtype<T, FNativeCastableType>;` (scope `Verse`)
- L274 _typedef_ `template <class T> using TNativeConcreteSubtype = TNativeSubtype<T, FNativeConcreteType, true>;` (scope `Verse`)
- L286 _typedef_ `template <class T> using TNativeCastableConcreteSubtype = TNativeSubtype<T, FNativeCastableConcreteType, true>;` (scope `Verse`)

### `Source/Runtime/CoreUObject/Public/VerseVM/VVMNeverDestroyed.h` (Public)


#### struct `Verse::TNeverDestroyed`  
`template <typename T> struct alignas(alignof(T)) TNeverDestroyed`  
_L14-54_
- L16 _public function_ `TNeverDestroyed()`
- L22 _public function_ `T& Get()`
- L27 _public function_ `T& operator*()`
- L32 _public function_ `T* operator->()`
- L37 _public function_ `const T& Get() const`
- L42 _public function_ `const T& operator*() const`
- L47 _public function_ `const T* operator->() const`
- L53 _private member_ `std::byte Data[sizeof(T)];`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace Verse`

### `Source/Runtime/CoreUObject/Public/VerseVM/VVMObject.h` (Public)


#### struct `Verse::VObject`  
`struct VObject : VHeapValue`  
_L20-86_
- inherits: `VHeapValue`
- desc: Base class for Verse objects that may store fields and associated values for those fields on it. An object points to an emergent type, which in turn points to a "shape". A "shape" is a dynamic memory layout of fields and their offsets.
- L24 _public prototype_ `FOpResult LoadField(FAllocationContext Context, const VUniqueString& Name, VValue Self = VValue(), FLoadFieldCacheCase* OutCacheCase = nullptr);`
- L27 _public prototype_ `template <EWriteMode WriteMode = EWriteMode::Default> FOpResult SetField(FAllocationContext Context, const VUniqueString& Name, VValue Value);`
- L29 _public function_ `bool IsStruct()`
- L30 _public function_ `void SetIsStruct()`
- L34 _public prototype_ `template <typename TBinaryFunction> bool AllFields(FAllocationContext Context, TBinaryFunction);` — `TBinaryFunction` should be invocable with `(declval<FUtf8StringView>(), declval<FOpResult>())`.
- L36 _public function_ `VClass& GetClass() const`
- L41 _public prototype_ `void VisitMembersImpl(FAllocationContext Context, FDebuggerVisitor& Visitor);`
- L43 _public prototype_ `AUTORTFM_DISABLE void AppendToStringImpl(FAllocationContext Context, FUtf8StringBuilderBase& Builder, EValueStringFormat Format, TSet<const void*>& VisitedObjects, uint32 RecursionDepth);`
- L45 _public prototype_ `AUTORTFM_DISABLE TSharedPtr<FJsonValue> ToJSONImpl(FRunningContext, EValueJSONFormat, TMap<const void*, EVisitState>& VisitedObjects, FToJsonCallback, uint32 RecursionDepth, FJsonObject* Defs);`
- L52 _protected prototype_ `VObject(FAllocationContext Context, VEmergentType& InEmergentType);`
- L54 _protected member_ `static constexpr const size_t DataAlignment = VERSE_HEAP_MIN_ALIGN;`
- L56 _protected prototype_ `FOpResult LoadField(FAllocationContext Context, VEmergentType& EmergentType, const VShape::VEntry* Field, VValue Self = VValue(), FLoadFieldCacheCase* OutCacheCase = nullptr);`
- L59 _protected prototype_ `template <EWriteMode WriteMode> static FOpResult SetField(FAllocationContext Context, const VShape& Shape, const VUniqueString& Name, void* Data, VValue Value);`
- L62 _protected prototype_ `template <EWriteMode WriteMode> static FOpResult SetField(FAllocationContext Context, const VShape::VEntry& Field, void* Data, VValue Value);`
- L64 _protected prototype_ `static size_t DataOffset(const VCppClassInfo& CppClassInfo);`
- L84 _protected prototype_ `inline void* GetData(const VCppClassInfo& CppClassInfo) const;` — Mutable variables store their data as a `VRestValue`. It's not an array of `VValue`s because you can potentially load a class member before actually defining it. i.e. ``` c := class {x:int} C := c{} Foo(C.X) # allocates a placeholder C.X := 1  # This is the first time `c.X` actually gets defined. ``` This stores the actual data for individual fields. Some constants and procedures are stored in the shape, not the object (since then there's no need to do an unnecessary index lookup). The mapping of offsets to each field are stored in the emergent type's "shape".  The reason why the object doesn't just store the mapping of fields to data itself is that it will eventually help when we implement inline caches for retrieving fields on objects. It also helps reduce memory usage because multiple objects can share the same hash table that describes their layouts.
- L85 _protected prototype_ `inline VRestValue* GetFieldData(const VCppClassInfo& CppClassInfo) const;`
- L88 _function_ `inline VObject::VObject(FAllocationContext Context, VEmergentType& InEmergentType) : VHeapValue(Context, &InEmergentType)`
- L94 _function_ `inline size_t VObject::DataOffset(const VCppClassInfo& CppClassInfo)`
- L99 _function_ `inline void* VObject::GetData(const VCppClassInfo& CppClassInfo) const`
- L104 _function_ `inline VRestValue* VObject::GetFieldData(const VCppClassInfo& CppClassInfo) const`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace Verse`

### `Source/Runtime/CoreUObject/Public/VerseVM/VVMObjectPrinting.h` (Public)


#### struct `Verse::ObjectPrinting::FHandler`  
`struct FHandler`  
_L17-20_
- L19 _public prototype_ `virtual bool TryStringHandle(UObject* Object, FUtf8StringBuilderBase& Builder, EValueStringFormat Format, TSet<const void*>& VisitedObjects, uint32 RecursionDepth) = 0;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace Verse`
- L15 _namespace_ `namespace ObjectPrinting` (scope `Verse`)
- L22 _prototype_ `void RegisterHandler(FHandler* Handler);` (scope `Verse::ObjectPrinting`)
- L23 _prototype_ `void UnregisterHandler(FHandler* Handler);` (scope `Verse::ObjectPrinting`)
- L26 _prototype_ `void AppendToString(FUtf8StringBuilderBase& Builder, UObject* Object, EValueStringFormat Format, TSet<const void*>& VisitedObjects, uint32 RecursionDepth);` (scope `Verse`)

### `Source/Runtime/CoreUObject/Public/VerseVM/VVMOpResult.h` (Public)


#### struct `Verse::FOpResult`  
`struct FOpResult`  
_L41-78_
- desc: Represents the result of a single VM operation
- L44 _public member_ `static constexpr AutoRTFM::EReturnFromOpenMode AutoRTFMReturnFromOpenMode = AutoRTFM::EReturnFromOpenMode::CopyConstructInClosed;` — FOpResult can be returned from AutoRTFM::Open() via a copy-construction in the closed.
- L55 _public function_ `FOpResult() : Kind(FOpResult::Error)`
- L60 _public function_ `FOpResult(EKind Kind, VValue Value = VValue()) : Kind(Kind) , Value(Value)`
- L66 _public function_ `bool IsReturn() const`
- L71 _public function_ `bool IsError() const`
- L76 _public member_ `EKind Kind;`
- L77 _public member_ `VValue Value;`

#### enum `Verse::FOpResult::EKind`  
`enum EKind`  
_L46-53_
- L48 _public enumerator_ `Return` — All went well, and Value is the result.
- L49 _public enumerator_ `Block` — A placeholder was encountered, and this operation should be enqueued on Value.
- L50 _public enumerator_ `Fail` — The current choice failed. Value is undefined.
- L51 _public enumerator_ `Yield` — The task suspended, and execution should continue in the resumer. Value is undefined.
- L52 _public enumerator_ `Error` — A runtime error occurred, and an exception was raised. Value is undefined.

#### Free symbols / members of external scopes

- L11 _macro_ `#define V_RETURN(...) \`
- L16 _macro_ `#define V_REQUIRE_CONCRETE(...) \`
- L21 _macro_ `#define V_FAIL_IF(...) \`
- L26 _macro_ `#define V_FAIL_UNLESS(...) \`
- L31 _macro_ `#define V_YIELD() \`
- L37 _namespace_ `namespace Verse`

### `Source/Runtime/CoreUObject/Public/VerseVM/VVMOption.h` (Public)


#### struct `Verse::VOption`  
`struct VOption : VType`  
_L19-62_
- inherits: `VType`
- desc: Inherits from VType because true, which is option{false}, is a type.
- L22 _public member_ `static TGlobalTrivialEmergentTypePtr<&StaticCppClassInfo> GlobalTrivialEmergentType;`
- L24 _public function_ `AUTORTFM_DISABLE static VOption& New(FAllocationContext Context, VValue InValue)`
- L29 _public function_ `VValue GetValue() const`
- L34 _public function_ `void SetValue(FAllocationContext Context, VValue InValue)`
- L40 _public prototype_ `uint32 GetTypeHashImpl();`
- L41 _public prototype_ `AUTORTFM_DISABLE VValue MeltImpl(FAllocationContext Context);`
- L42 _public prototype_ `AUTORTFM_DISABLE FOpResult FreezeImpl(FAllocationContext Context, VTask* Task);`
- L43 _public prototype_ `void VisitMembersImpl(FAllocationContext Context, FDebuggerVisitor& Visitor);`
- L44 _public prototype_ `AUTORTFM_DISABLE void AppendToStringImpl(FAllocationContext Context, FUtf8StringBuilderBase& Builder, EValueStringFormat Format, TSet<const void*>& VisitedObjects, uint32 RecursionDepth);`
- L45 _public prototype_ `AUTORTFM_DISABLE TSharedPtr<FJsonValue> ToJSONImpl(FRunningContext, EValueJSONFormat, TMap<const void*, EVisitState>& VisitedObjects, FToJsonCallback, uint32 RecursionDepth, FJsonObject* Defs);`
- L47 _public member_ `static constexpr bool SerializeIdentity = false;`
- L48 _public prototype_ `AUTORTFM_DISABLE static void SerializeLayout(FAllocationContext Context, VOption*& This, FStructuredArchiveVisitor& Visitor);`
- L49 _public prototype_ `AUTORTFM_DISABLE void SerializeImpl(FAllocationContext Context, FStructuredArchiveVisitor& Visitor);`
- L51 _public member_ `static constexpr bool InstancedCell = true;`
- L54 _private function_ `AUTORTFM_DISABLE VOption(FAllocationContext Context, VValue InValue) : VType(Context, &GlobalTrivialEmergentType.Get(Context)) , Value(Context, InValue)`
- L61 _private member_ `TWriteBarrier<VValue> Value;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace Verse`

### `Source/Runtime/CoreUObject/Public/VerseVM/VVMOverloaded.h` (Public)


#### struct `FOverloaded`  
`template <typename... T> struct FOverloaded : T...`  
_L12-21_
- inherits: `T...`
- L15 _public function_ `template <typename... U> explicit FOverloaded(U&&... Args) : T(::Forward<U>(Args))...`

#### Free symbols / members of external scopes

- L24 _prototype_ `template <typename... T> FOverloaded(T&&...) -> FOverloaded<std::decay_t<T>...>;`

### `Source/Runtime/CoreUObject/Public/VerseVM/VVMPackage.h` (Public)


#### enum `Verse::EDigestVariant`  
`enum class EDigestVariant : uint8`  
_L24-28_
- L26 _public enumerator_ `PublicAndEpicInternal = 0`
- L27 _public enumerator_ `PublicOnly = 1`

#### struct `Verse::FVersionedDigest`  
`struct FVersionedDigest`  
_L30-35_
- L32 _public member_ `TWriteBarrier<VArray> Code;`
- L33 _public member_ `uint32 EffectiveVerseVersion;`
- L34 _public member_ `TArray<FName> DependencyPackageNames;`

#### struct `Verse::VPackage`  
`struct VPackage : VCell`  
_L37-97_
- inherits: `VCell`
- L40 _public member_ `static TGlobalTrivialEmergentTypePtr<&StaticCppClassInfo> GlobalTrivialEmergentType;`
- L42 _public member_ `TOptional<FVersionedDigest> DigestVariants[2];` — One for each variant
- L44 _public function_ `VUniqueString& GetName() const`
- L45 _public function_ `VUniqueString& GetRootPath() const`
- L47 _public function_ `uint32 NumDefinitions() const`
- L48 _public function_ `VUniqueString& GetDefinitionName(uint32 Index) const`
- L49 _public function_ `VValue GetDefinition(uint32 Index) const`
- L50 _public function_ `void AddDefinition(FAllocationContext Context, VUniqueString& Path, VValue Definition)`
- L51 _public function_ `VValue LookupDefinition(FUtf8StringView Path) const`
- L53 _public function_ `template <typename CellType> CellType* LookupDefinition(FUtf8StringView Path) const`
- L55 _public prototype_ `AUTORTFM_DISABLE void NotifyUsedTupleType(FAllocationContext Context, VTupleType* TupleType);`
- L57 _public prototype_ `template <typename FunctorType>`
- L59 _public prototype_ `AUTORTFM_DISABLE void NotifyUsedImport(FAllocationContext Context, VNamedType* TypeWithImport);`
- L61 _public prototype_ `template <typename FunctorType>`
- L63 _public prototype_ `UPackage* GetUPackage() const;`
- L64 _public prototype_ `UPackage* GetOrCreateUPackage(FAllocationContext Context);`
- L65 _public prototype_ `void AddRedirect(FCoreRedirect&& Redirect);`
- L66 _public prototype_ `void ApplyRedirects();`
- L67 _public prototype_ `void ResetRedirects();`
- L69 _public function_ `AUTORTFM_DISABLE static VPackage& New(FAllocationContext Context, VUniqueString& Name, VUniqueString& RootPath, uint32 Capacity)`
- L74 _public prototype_ `void RecordCells(FAllocationContext Context);`
- L76 _public prototype_ `AUTORTFM_DISABLE static void SerializeLayout(FAllocationContext Context, VPackage*& This, FStructuredArchiveVisitor& Visitor);`
- L77 _public prototype_ `AUTORTFM_DISABLE void SerializeImpl(FAllocationContext Context, FStructuredArchiveVisitor& Visitor);`
- L82 _private prototype_ `AUTORTFM_DISABLE VPackage(FAllocationContext Context, VUniqueString* InName, VUniqueString* InRootPath, uint32 Capacity);`
- L83 _private prototype_ `~VPackage();`
- L85 _private member_ `TWriteBarrier<VUniqueString> Name;`
- L86 _private member_ `TWriteBarrier<VUniqueString> RootPath;`
- L88 _private member_ `VNameValueMap Definitions;`
- L92 _private member_ `TWriteBarrier<VWeakCellMap> UsedTupleTypes;` — Keep track of tuple types and imports here in addition to the corresponding global maps in VProgram so that during incremental compilation we can populate the global maps with these
- L93 _private member_ `TWriteBarrier<VMutableArray> UsedImports;`
- L95 _private member_ `TWriteBarrier<VValue> AssociatedUPackage;`
- L96 _private member_ `TArray<FCoreRedirect> Redirects;`

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace Verse`

### `Source/Runtime/CoreUObject/Public/VerseVM/VVMPackageName.h` (Public)


#### class `Verse::FPackageName`  
`class FPackageName`  
_L18-46_
- L22 _public prototype_ `static FString GetVersePackageNameForVni(const TCHAR* MountPointName, const TCHAR* CppModuleName);` — The following methods are being deprecated and should use Verse::Names methods found in VVMNames.h
- L23 _public prototype_ `static FString GetVersePackageNameForContent(const TCHAR* MountPointName);`
- L24 _public prototype_ `static FString GetVersePackageNameForPublishedContent(const TCHAR* MountPointName);`
- L25 _public prototype_ `static FString GetVersePackageNameForAssets(const TCHAR* MountPointName);`
- L26 _public prototype_ `static FString GetVersePackageDirForContent(const TCHAR* MountPointName);`
- L27 _public prototype_ `static FString GetVersePackageDirForAssets(const TCHAR* MountPointName);`
- L30 _public prototype_ `static FName GetVersePackageNameFromUPackagePath(FName UPackagePath, EVersePackageType* OutPackageType = nullptr);` — The following methods don't have a Verse::Names version yet
- L31 _public prototype_ `static FString GetMountPointName(const TCHAR* VersePackageName);`
- L32 _public prototype_ `static FName GetCppModuleName(const TCHAR* VersePackageName);`
- L33 _public prototype_ `static EVersePackageType GetPackageType(const TCHAR* VersePackageName);`
- L34 _public prototype_ `static EVersePackageType GetPackageType(const UTF8CHAR* VersePackageName);`
- L36 _public prototype_ `static FString GetTaskUClassName(const TCHAR* OwnerScopeName, const TCHAR* DecoratedAndMangledFunctionName);`
- L37 _public prototype_ `static FString GetTaskUClassName(const UObject& OwnerScope, const TCHAR* DecoratedAndMangledFunctionName);`
- L39 _public prototype_ `static bool PackageRequiresInternalAPI(const char* Name, const EVersePackageScope VerseScope);`
- L42 _public member_ `static constexpr char const* const RootModuleClassName = "_R` — Class name substitute for root module classes of a package
- L45 _public member_ `static constexpr TCHAR const* const TaskUClassPrefix = TEXT("tas` — Prefix Constants

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API COREUOBJECT_API`
- L15 _namespace_ `namespace Verse`

### `Source/Runtime/CoreUObject/Public/VerseVM/VVMPackageTypes.h` (Public)


#### enum `EVersePackageScope`  
`enum class EVersePackageScope : uint8`  
_L12-18_
- reflection: `UENUM()`
- L14 _public enumerator_ `PublicAPI` — Created by Epic and only public definitions will be visible to public users
- L15 _public enumerator_ `InternalAPI` — Created by Epic and is entirely hidden from public users
- L16 _public enumerator_ `PublicUser` — Created by a public user
- L17 _public enumerator_ `InternalUser` — Created by an Epic internal user

#### enum `EVersePackageType`  
`enum class EVersePackageType : uint8`  
_L21-27_
- reflection: `UENUM()`
- L23 _public enumerator_ `VNI` — A package associated with a C++ module
- L24 _public enumerator_ `Content` — A package associated with a plugin
- L25 _public enumerator_ `PublishedContent` — A package associated with the published content of a plugin
- L26 _public enumerator_ `Assets` — A package associated with the reflected binary assets of a plugin

#### Free symbols / members of external scopes

- L29 _function_ `static inline TOptional<EVersePackageType> ToVersePackageType(const FStringView String)`

### `Source/Runtime/CoreUObject/Public/VerseVM/VVMPersistence.h` (Public)


#### struct `Verse::FUpdatedPersistentPairSave`  
`struct FUpdatedPersistentPairSave`  
_L46-66_
- L49 _public member_ `FString Path;` — Verse path of the update persistent `var` `weak_map`
- L51 _public member_ `FString RelativePath;` — Package-relative Verse path of the update persistent `var` `weak_map`
- L53 _public member_ `void* Key;` — Key of the updated value in the map.
- L55 _public member_ `TSharedPtr<FJsonValue> Value;` — Updated value in the map.
- L59 _public member_ `const FMapProperty* MapProperty;` — `FProperty` of the related persistent `var` `weak_map`
- L62 _public member_ `void* RawValue;` — Updated value in the map. The structure of the value can be found in `MapProperty->ValueProp`.
- L64 _public member_ `VValue RawValue;`

#### struct `Verse::FUpdatedPersistentPairVM`  
`struct FUpdatedPersistentPairVM`  
_L70-144_
- desc: Represents an update to a persistent `var` `weak_map`. A range of `FUpdatedPair`s is broadcast by `Updated`.
- L73 _public member_ `FString Path;` — Verse path of the update persistent `var` `weak_map`
- L75 _public member_ `FString RelativePath;` — Package-relative verse path of the update persistent `var` `weak_map`
- L78 _public member_ `const FMapProperty* MapProperty;` — `FProperty` of the related persistent `var` `weak_map`
- L80 _public member_ `void* Key;` — Key of the updated value in the map.
- L83 _public member_ `void* Value;` — Updated value in the map. The structure of the value can be found in `MapProperty->ValueProp`.
- L86 _public member_ `VValue Key;` — Key of the updated value in the map.
- L88 _public member_ `VValue Value;` — Updated value in the map.
- L92 _public function_ `FUpdatedPersistentPairVM(FString Path, FString RelativePath, const FMapProperty* MapProperty, void* Key, void* Value) : Path(::MoveTemp(Path)) , RelativePath(::MoveTemp(RelativePath)) , MapProperty(MapProperty) , Key(Key) , Value(Value)`
- L101 _public function_ `FUpdatedPersistentPairVM(FString Path, FString RelativePath, VValue Key, VValue Value) : Path(::MoveTemp(Path)) , RelativePath(::MoveTemp(RelativePath)) , Key(Key) , Value(Value)`

#### enum `Verse::EPersistenceExternalAccess`  
`enum class EPersistenceExternalAccess : uint8`  
_L148-154_
- reflection: `UENUM()`
- desc: The enumerator values must match `uLang::CDataDefinition::EPersistenceExternalAccess`.
- L150 _public enumerator_ `Internal = 0`
- L151 _public enumerator_ `Read = 1 << 0`
- L152 _public enumerator_ `Write = 1 << 1`
- L153 _public enumerator_ `ReadWrite = Read | Write`

#### class `Verse::IVersePersistence`  
`class IVersePersistence`  
_L166-265_
- L169 _protected prototype_ `virtual ~IVersePersistence() = default;`
- L172 _public typedef_ `using TPersistablePredicateSave = TFunction<bool(const TSharedPtr<FJsonValue>&)>;`
- L174 _public typedef_ `using TPersistablePredicateVM = TFunction<bool(const FProperty*, void*)>;`
- L176 _public typedef_ `using TPersistablePredicateVM = TFunction<bool(VValue)>;`
- L182 _public prototype_ `virtual const TPersistablePredicateVM GetPersistablePredicate() const = 0;` — Get the predicate used for `FitsInPlayerMap` intrinsic
- L187 _public prototype_ `virtual void SetPersistablePredicate(TPersistablePredicateSave) = 0;` — Set the predicate used for `FitsInPlayerMap` intrinsic
- L189 _public typedef_ `using EExternalAccess = EPersistenceExternalAccess;`
- L195 _public prototype_ `virtual void AddPersistentMap(const FString& Path, const FString& RelativePath, EExternalAccess, const FMapProperty*, UObject* Container) = 0;` — Notify of the construction of a persistent `var` `weak_map`
- L200 _public prototype_ `virtual void AddPersistentMap(const FString& Path, const FString& RelativePath, EExternalAccess, const FString& MountPointName, VPersistentMap& Map) = 0;` — Notify of the construction of a persistent `var` `weak_map`
- L206 _public prototype_ `virtual void UpdatePersistentPairs(const FUpdatedPersistentPairVM*, const FUpdatedPersistentPairVM*) = 0;` — Update a set of key-value pairs in a persistent `var` `weak_map`
- L211 _public prototype_ `DECLARE_EVENT_FourParams(IVersePersistence, FOnPersistentMapConstructed, const FString& Path, const FString& RelativePath, EExternalAccess, const FString& MountPointName);` — Event indicating when a persistent `var` is constructed (correlating directly with a call to `AddPersistentMap`)
- L212 _public prototype_ `virtual FOnPersistentMapConstructed& OnPersistentMapConstructed() = 0;`
- L214 _public prototype_ `DECLARE_EVENT_OneParam(IVersePersistence, FOnPersistentPairsUpdated, const TArray<FUpdatedPersistentPairSave>&);`
- L215 _public prototype_ `virtual FOnPersistentPairsUpdated& OnPersistentPairsUpdated() = 0;`
- L217 _public prototype_ `DECLARE_EVENT(IVersePersistence, FOnPersistentMapsReleased);`
- L218 _public prototype_ `virtual FOnPersistentMapsReleased& OnPersistentMapsReleased() = 0;`
- L225 _public prototype_ `DECLARE_EVENT_OneParam(IVersePersistence, FOnPersistentMapKeyAdded, void* );` — Persistent map key added event, triggered when a persistent map key is added to Verse @param Key the new key that was added
- L226 _public prototype_ `virtual FOnPersistentMapKeyAdded& OnPersistentMapKeyAdded() = 0;`
- L233 _public prototype_ `DECLARE_EVENT_OneParam(IVersePersistence, FOnPersistentMapKeyRemoved, void* );` — Persistent map key removed event, triggered when a persistent map key is removed from Verse @param Key the key that was removed
- L234 _public prototype_ `virtual FOnPersistentMapKeyRemoved& OnPersistentMapKeyRemoved() = 0;`
- L239 _public prototype_ `virtual void AddPersistentPair(const FString& Path, const void* Key, const TSharedRef<const FJsonValue>& Value) = 0;` — Add key and value to a persistent `var` `weak_map` with Verse path `Path`
- L245 _public prototype_ `virtual void AddPersistentPair(const FString& Path, const void* Key, const void* Data) = 0;` — Add key and value to a persistent `var` `weak_map` with Verse path `Path`
- L250 _public prototype_ `virtual void AddPersistentPair(const FString& Path, const void* Key, VValue Value) = 0;` — Add key and value to a persistent `var` `weak_map` with Verse path `Path`
- L256 _public prototype_ `virtual void RemovePersistentPairs(const void* Key) = 0;` — Remove key from all persistent `var` `weak_map`s
- L264 _public prototype_ `virtual void ResetWeakMaps() = 0;` — Reset persistence by reinitialization all `var`s to a default-constructed value @note this assumes the `var` started out with a default-constructed value

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace Verse`
- L18 _prototype_ `TOptional<TMap<FJsonObject::FStringType, TSharedPtr<FJsonValue>>> MapFromPersistentJson(const FJsonObject& JsonObject);` (scope `Verse`)
- L21 _function_ `template <typename TShortName> FString ShortNameToFieldName(TShortName&& ShortName)` (scope `Verse`)
- L27 _function_ `template <typename TArg> TOptional<TArg> NameToShortName(TArg PropertyName)` (scope `Verse`)
- L110 _function_ `friend bool operator==(const FUpdatedPersistentPairVM& Left, const FUpdatedPersistentPairVM& Right)` (scope `Verse`)
- L119 _function_ `friend uint32 GetTypeHash(const FUpdatedPersistentPairVM& Arg)` (scope `Verse`)
- L124 _function_ `friend bool operator<(const FUpdatedPersistentPairVM& Left, const FUpdatedPersistentPairVM& Right)` (scope `Verse`)
- L156 _function_ `inline bool IsExternallyWritable(EPersistenceExternalAccess Arg)` (scope `Verse`)
- L161 _function_ `inline bool IsExternallyReadable(EPersistenceExternalAccess Arg)` (scope `Verse`)
- L211 _delegate_ `DECLARE_EVENT_FourParams(IVersePersistence, FOnPersistentMapConstructed, const FString& Path, const FString& RelativePath, EExternalAccess, const FString& MountPointName);` — Event indicating when a persistent `var` is constructed (correlating directly with a call to `AddPersistentMap`)
- L214 _delegate_ `DECLARE_EVENT_OneParam(IVersePersistence, FOnPersistentPairsUpdated, const TArray<FUpdatedPersistentPairSave>&);`
- L217 _delegate_ `DECLARE_EVENT(IVersePersistence, FOnPersistentMapsReleased);`
- L225 _delegate_ `DECLARE_EVENT_OneParam(IVersePersistence, FOnPersistentMapKeyAdded, void* );` — Persistent map key added event, triggered when a persistent map key is added to Verse @param Key the new key that was added
- L233 _delegate_ `DECLARE_EVENT_OneParam(IVersePersistence, FOnPersistentMapKeyRemoved, void* );` — Persistent map key removed event, triggered when a persistent map key is removed from Verse @param Key the key that was removed

### `Source/Runtime/CoreUObject/Public/VerseVM/VVMPlaceholder.h` (Public)


#### struct `Verse::VPlaceholder`  
`struct VPlaceholder : public VCell`  
_L14-143_
- inherits: `VCell`
- L17 _public member_ `static TGlobalTrivialEmergentTypePtr<&StaticCppClassInfo> GlobalTrivialEmergentType;`
- L26 _public member_ `TWriteBarrier<VValue> Value;`
- L28 _public function_ `AUTORTFM_DISABLE static VPlaceholder& New(FAllocationContext Context, uint16 SplitDepth)`
- L33 _public function_ `uint16 SplitDepth() const`
- L34 _public function_ `bool HasSuspension() const`
- L35 _public function_ `bool HasValue() const`
- L36 _public function_ `bool HasParent() const`
- L38 _public function_ `VSuspension* GetSuspension() const`
- L51 _public function_ `VValue GetValue() const`
- L57 _public function_ `VPlaceholder* GetParent() const`
- L63 _public function_ `void Unify(FAllocationContext Context, FTrail& Trail, VPlaceholder& Other)`
- L87 _public function_ `VSuspension* SetValue(FAccessContext Context, VValue InValue)`
- L96 _public function_ `VSuspension* SetValueTrailed(FAllocationContext Context, FTrail& Trail, VValue InValue)`
- L105 _public prototype_ `VValue Follow();`
- L108 _public function_ `void EnqueueSuspension(FAccessContext Context, VSuspension& Suspension)` — TODO: For perf, think through if FIFO or LIFO will be faster.
- L119 _private function_ `void SetParent(FAccessContext Context, VPlaceholder& Other)`
- L125 _private function_ `void SetParentTrailed(FAllocationContext Context, FTrail& Trail, VPlaceholder& Other)`
- L131 _private function_ `EMode& Mode() const`
- L133 _private prototype_ `void SetModeTrailed(FAllocationContext Context, FTrail& Trail, EMode InMode);`
- L135 _private function_ `AUTORTFM_DISABLE VPlaceholder(FAllocationContext Context, uint16 InputSplitDepth) : VCell(Context, &GlobalTrivialEmergentType.Get(Context))`

#### enum `Verse::VPlaceholder::EMode`  
`enum class EMode : uint8`  
_L19-24_
- L21 _public enumerator_ `HasSuspension`
- L22 _public enumerator_ `HasValue`
- L23 _public enumerator_ `HasParent`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace Verse`

### `Source/Runtime/CoreUObject/Public/VerseVM/VVMProcedure.h` (Public)


#### struct `Verse::VProcedure`  
`struct VProcedure : VCell`  
_L52-272_
- inherits: `VCell`
- desc: This is laid out in memory with (64-bit) pointers followed by (8-byte aligned) instructions followed by (32-bit) integers: VProcedure FNamedParam                    NamedParam[0] FNamedParam                    NamedParam[1] ... FNamedParam                    NamedParam[NumNamedParameters - 1] TWriteBarrier<VValue>          Constant  [0] TWriteBarrier<VValue>          Constant  [1] ... TWriteBarrier<VValue>          Constant  [NumConstants - 1] FOp                            Ops + NumOpBytes FValueOperand                  Operand   [0] FValueOperand                  Operand   [1] ... FValueOperand                  Operand   [NumOperands - 1] FLabelOffset                   Label     [0] FLabelOffset                   Label     [1] ... FLabelOffset                   Label     [NumLabels - 1] FUnwindEdge                    UnwindEdge[0] FUnwindEdge                    UnwindEdge[1] ... FUnwindEdge                    UnwindEdge[NumUnwindEdges - 1] FOpLocation                    OpLocation[0] FOpLocation                    OpLocation[1] ... FOpLocation                    OpLocation[NumOpLocations - 1] FRegisterName                  RegisterName[0] FRegisterName                  RegisterName[1] ... FRegisterName                  RegisterName[NumRegisterNames - 1]
- L55 _public member_ `static TGlobalTrivialEmergentTypePtr<&StaticCppClassInfo> GlobalTrivialEmergentType;`
- L58 _public member_ `TWriteBarrier<VUniqueString> FilePath;` — Used by the debugger when checking breakpoints
- L60 _public member_ `TWriteBarrier<VUniqueString> Name;` — Used by the debugger when showing stack frames
- L62 _public member_ `uint32 NumRegisters;`
- L63 _public member_ `uint32 NumPositionalParameters;`
- L66 _public member_ `uint32 NumNamedParameters;` — Sizes of trailing arrays
- L67 _public member_ `uint32 NumConstants;`
- L68 _public member_ `uint32 NumOpBytes;`
- L69 _public member_ `uint32 NumOperands;`
- L70 _public member_ `uint32 NumLabels;`
- L71 _public member_ `uint32 NumUnwindEdges;`
- L72 _public member_ `uint32 NumOpLocations;`
- L73 _public member_ `uint32 NumRegisterNames;`
- L75 _public member_ `TWriteBarrier<VCell> Trailing[];`
- L79 _public function_ `FNamedParam* GetNamedParamsBegin()`
- L80 _public function_ `FNamedParam* GetNamedParamsEnd()`
- L82 _public function_ `TWriteBarrier<VValue>* GetConstantsBegin()`
- L83 _public function_ `TWriteBarrier<VValue>* GetConstantsEnd()`
- L85 _public function_ `FOp* GetPCForOffset(uint32 Offset)`
- L86 _public function_ `FOp* GetOpsBegin()`
- L87 _public function_ `FOp* GetOpsEnd()`
- L88 _public function_ `bool ContainsPC(FOp* PC)`
- L93 _public function_ `FValueOperand* GetOperandsBegin()`
- L94 _public function_ `FValueOperand* GetOperandsEnd()`
- L96 _public function_ `FLabelOffset* GetLabelsBegin()`
- L97 _public function_ `FLabelOffset* GetLabelsEnd()`
- L99 _public function_ `FUnwindEdge* GetUnwindEdgesBegin()`
- L100 _public function_ `FUnwindEdge* GetUnwindEdgesEnd()`
- L102 _public function_ `FOpLocation* GetOpLocationsBegin()`
- L103 _public function_ `FOpLocation* GetOpLocationsEnd()`
- L105 _public function_ `FRegisterName* GetRegisterNamesBegin()`
- L106 _public function_ `FRegisterName* GetRegisterNamesEnd()`
- L109 _public function_ `uint32 BytecodeOffset(const FOp& Bytecode)` — In bytes.
- L114 _public function_ `uint32 BytecodeOffset(const void* Data)`
- L120 _public function_ `const FLocation* GetLocation(const FOp& Op)`
- L125 _public function_ `const FLocation* GetLocation(int32 OpOffset)`
- L130 _public function_ `void SetConstant(FAllocationContext Context, FConstantIndex ConstantIndex, VValue Value)`
- L136 _public function_ `VValue GetConstant(FConstantIndex ConstantIndex)`
- L142 _public function_ `AUTORTFM_DISABLE static VProcedure& NewUninitialized( FAllocationContext Context, uint32 NumNamedParameters, uint32 NumConstants, uint32 NumOpBytes, uint32 NumOperands, uint32 NumLabels, uint32 NumUnwindEdges, uint32 NumOpLocations, uint32 NumRegisterNames)`
- L167 _public prototype_ `void ConductCensusImpl();`
- L169 _public prototype_ `AUTORTFM_DISABLE static void SerializeLayout(FAllocationContext Context, VProcedure*& This, FStructuredArchiveVisitor& Visitor);`
- L170 _public prototype_ `AUTORTFM_DISABLE void SerializeImpl(FAllocationContext Context, FStructuredArchiveVisitor& Visitor);`
- L173 _private prototype_ `TArray<uint8> SanitizeOpCodes();`
- L188 _private function_ `static FLayout CalcLayout( uint32 NumNamedParameters, uint32 NumConstants, uint32 NumOpBytes, uint32 NumOperands, uint32 NumLabels, uint32 NumUnwindEdges, uint32 NumOpLocations, uint32 NumRegisterNames)`
- L215 _private function_ `FLayout GetLayout() const`
- L220 _private function_ `AUTORTFM_DISABLE VProcedure( FAllocationContext Context, uint32 InNumNamedParameters, uint32 InNumConstants, uint32 InNumOpBytes, uint32 InNumOperands, uint32 InNumLabels, uint32 InNumUnwindEdges, uint32 InNumOpLocations, uint32 InNumRegisterNames) : VCell(Context, &GlobalTrivialEmergentType.Get(Context)) , NumNamedParameters(InNumNamedParameters) , NumConstants(InNumConstants) , NumOpBytes(InNumOpBytes) , NumOperands(InNumOperands) , NumLabels(InNumLabels) , NumUnwindEdges(InNumUnwindEdges) , NumOpLocations(InNumOpLocations) , NumRegisterNames(InNumRegisterNames)`
- L271 _private prototype_ `template <typename FuncType> void ForEachOpCode(FuncType&& Func);`

#### struct `Verse::VProcedure::FLayout`  
`struct FLayout`  
_L175-186_
- L177 _public member_ `int32 NamedParamsOffset;`
- L178 _public member_ `int32 ConstantsOffset;`
- L179 _public member_ `int32 OpsOffset;`
- L180 _public member_ `int32 OperandsOffset;`
- L181 _public member_ `int32 LabelsOffset;`
- L182 _public member_ `int32 UnwindEdgesOffset;`
- L183 _public member_ `int32 OpLocationsOffset;`
- L184 _public member_ `int32 RegisterNamesOffset;`
- L185 _public member_ `int32 TotalSize;`

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace Verse`

### `Source/Runtime/CoreUObject/Public/VerseVM/VVMProfilingLibrary.h` (Public)


#### struct `FProfileLocus`  
`struct FProfileLocus`  
_L17-27_
- reflection: `USTRUCT()`
- desc: Source range of a profile-time block
- L21 _public member_ `uint64_t BeginRow;` — 1-based, inclusive
- L22 _public member_ `uint64_t BeginColumn;` — 1-based, inclusive (UTF-8 byte offset)
- L23 _public member_ `uint64_t EndRow;` — 1-based
- L24 _public member_ `uint64_t EndColumn;` — 1-based (UTF-8 byte offset)

#### struct `FSolarisProfilingData`  
`struct FSolarisProfilingData`  
_L30-37_
- reflection: `USTRUCT()`
- L35 _public member_ `uint64_t WallTimeStart;`
- L36 _public member_ `FProfileLocus Locus;`

#### class `FVerseProfilingDelegates`  
`class FVerseProfilingDelegates`  
_L42-50_
- L45 _public member_ `static FVerseBeginProfilingEventHandler OnBeginProfilingEvent;`
- L46 _public member_ `static FVerseEndProfilingEventHandler OnEndProfilingEvent;`
- L48 _public prototype_ `static void RaiseBeginProfilingEvent();`
- L49 _public prototype_ `static void RaiseEndProfilingEvent(const char* UserTag, double TimeInMs, const FProfileLocus& );`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API COREUOBJECT_API`
- L39 _delegate_ `DECLARE_MULTICAST_DELEGATE(FVerseBeginProfilingEventHandler);`
- L39 _prototype_ `DECLARE_MULTICAST_DELEGATE(FVerseBeginProfilingEventHandler);`
- L40 _delegate_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FVerseEndProfilingEventHandler, const char* , double , const FProfileLocus& );`
- L40 _prototype_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FVerseEndProfilingEventHandler, const char* , double , const FProfileLocus& );`

### `Source/Runtime/CoreUObject/Public/VerseVM/VVMProgram.h` (Public)


#### struct `Verse::VProgram`  
`struct VProgram : VCell`  
_L19-68_
- inherits: `VCell`
- L22 _public member_ `static TGlobalTrivialEmergentTypePtr<&StaticCppClassInfo> GlobalTrivialEmergentType;`
- L24 _public function_ `uint32 NumPackages() const`
- L25 _public function_ `const VUniqueString& GetPackageName(uint32 Index) const`
- L26 _public function_ `VPackage& GetPackage(uint32 Index) const`
- L27 _public prototype_ `AUTORTFM_DISABLE void AddPackage(FAllocationContext Context, VUniqueString& Name, VPackage& Package);`
- L28 _public prototype_ `void RemovePackage(FAccessContext, FUtf8StringView VersePackageName);`
- L29 _public function_ `VPackage* LookupPackage(FUtf8StringView VersePackageName) const`
- L30 _public function_ `VPackage* LookupPackageByFName(FName VersePackageName) const`
- L33 _public prototype_ `AUTORTFM_DISABLE void AddTupleType(FAllocationContext Context, VUniqueString& MangledName, VTupleType& TupleType);` — Will overwrite existing entry if exists
- L34 _public prototype_ `VTupleType* LookupTupleType(FAccessContext Context, VUniqueString& MangledName) const;`
- L37 _public prototype_ `AUTORTFM_DISABLE void AddImport(FAllocationContext Context, VNamedType& TypeWithImport);` — Will overwrite existing entry if exists
- L38 _public prototype_ `VNamedType* LookupImport(FAllocationContext Context, UField* ImportedType) const;`
- L39 _public prototype_ `VShape* LookupShape(FAllocationContext Context, UField* ImportedType) const;`
- L40 _public prototype_ `VPackage* LookupPackage(FAllocationContext Context, UPackage* Package);`
- L42 _public function_ `VIntrinsics& GetIntrinsics() const`
- L43 _public function_ `void AddIntrinsics(FAllocationContext Context, VIntrinsics& InIntrinsics)`
- L45 _public function_ `VFunction& GetUpdatePersistentWeakMapPlayer() const`
- L46 _public function_ `void AddUpdatePersistentWeakMapPlayer(FAllocationContext Context, VFunction& InUpdatePersistentWeakMapPlayer)`
- L48 _public prototype_ `void Reset(FAllocationContext Context);`
- L50 _public function_ `AUTORTFM_DISABLE static VProgram& New(FAllocationContext Context, uint32 Capacity)`
- L56 _private function_ `AUTORTFM_DISABLE VProgram(FAllocationContext Context, uint32 Capacity) : VCell(Context, &GlobalTrivialEmergentType.Get(Context)) , PackageMap(Context, Capacity)`
- L62 _private member_ `VNameValueMap PackageMap;`
- L63 _private member_ `TWriteBarrier<VWeakCellMap> TupleTypeMap;`
- L64 _private member_ `TMap<TObjectPtr<UField>, VValue> ImportMap;` — For reverse lookup UField -> VNamedType
- L65 _private member_ `TMap<TObjectPtr<UField>, VValue> ShapeMap;` — For reverse lookup UStruct -> VShape
- L66 _private member_ `TWriteBarrier<VIntrinsics> Intrinsics;`
- L67 _private member_ `TWriteBarrier<VFunction> UpdatePersistentWeakMapPlayer;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace Verse`

### `Source/Runtime/CoreUObject/Public/VerseVM/VVMPtrVariant.h` (Public)


#### struct `Verse::TagOf`  
`template <typename T, typename... Ts> struct TagOf<T, T, Ts...>`  
_L15-18_
- L17 _public member_ `static constexpr uintptr_t Value = 0;`
- L23 _public member_ `static constexpr uintptr_t Value = 1 + TagOf<T, Ts...>::Value;`

#### struct `Verse::TagOf`  
`template <typename T, typename U, typename... Ts> struct TagOf<T, U, Ts...>`  
_L21-24_
- L17 _public member_ `static constexpr uintptr_t Value = 0;`
- L23 _public member_ `static constexpr uintptr_t Value = 1 + TagOf<T, Ts...>::Value;`

#### struct `Verse::TPtrVariant`  
`template <typename... Ts> struct TPtrVariant`  
_L41-80_
- desc: Ts... are types which are ultimately pointers. We tag which of Ts... the variant holds by tagging the lower bits, so the pointers must be at least log(sizeof(Ts)...) + 1 byte aligned.
- L45 _public member_ `static constexpr uintptr_t Mask = BitCeil(sizeof...(Ts)) - 1;`
- L48 _public function_ `template <typename T> TPtrVariant(T InT)`
- L57 _public function_ `template <typename T> bool Is()`
- L64 _public function_ `template <typename T> T As()`
- L71 _public function_ `bool operator==(TPtrVariant Other) const`
- L76 _public function_ `uintptr_t RawPtr() const`
- L79 _private member_ `uintptr_t Ptr;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace Verse`
- L27 _function_ `inline constexpr size_t BitCeil(size_t X)` (scope `Verse`) — Can't use std::bit_ceil yet.
- L83 _function_ `template <typename... Ts> inline uint32 GetTypeHash(TPtrVariant<Ts...> Ptr)` (scope `Verse`)

### `Source/Runtime/CoreUObject/Public/VerseVM/VVMRational.h` (Public)


#### struct `Verse::VRational`  
`struct VRational : VHeapValue`  
_L19-60_
- inherits: `VHeapValue`
- L22 _public member_ `static TGlobalTrivialEmergentTypePtr<&StaticCppClassInfo> GlobalTrivialEmergentType;`
- L24 _public member_ `TWriteBarrier<VInt> Numerator;`
- L25 _public member_ `TWriteBarrier<VInt> Denominator;`
- L27 _public prototype_ `AUTORTFM_DISABLE static VRational& Add(FAllocationContext Context, VRational& Lhs, VRational& Rhs);`
- L28 _public prototype_ `AUTORTFM_DISABLE static VRational& Sub(FAllocationContext Context, VRational& Lhs, VRational& Rhs);`
- L29 _public prototype_ `AUTORTFM_DISABLE static VRational& Mul(FAllocationContext Context, VRational& Lhs, VRational& Rhs);`
- L30 _public prototype_ `AUTORTFM_DISABLE static VRational& Div(FAllocationContext Context, VRational& Lhs, VRational& Rhs);`
- L31 _public prototype_ `AUTORTFM_DISABLE static VRational& Neg(FAllocationContext Context, VRational& N);`
- L32 _public prototype_ `AUTORTFM_DISABLE static bool Eq(FAllocationContext Context, VRational& Lhs, VRational& Rhs);`
- L33 _public prototype_ `AUTORTFM_DISABLE static bool Eq(FAllocationContext Context, VRational& Lhs, VInt Rhs);`
- L34 _public prototype_ `AUTORTFM_DISABLE static bool Gt(FAllocationContext Context, VRational& Lhs, VRational& Rhs);`
- L35 _public prototype_ `AUTORTFM_DISABLE static bool Lt(FAllocationContext Context, VRational& Lhs, VRational& Rhs);`
- L36 _public prototype_ `AUTORTFM_DISABLE static bool Gte(FAllocationContext Context, VRational& Lhs, VRational& Rhs);`
- L37 _public prototype_ `AUTORTFM_DISABLE static bool Lte(FAllocationContext Context, VRational& Lhs, VRational& Rhs);`
- L39 _public prototype_ `AUTORTFM_DISABLE VInt Floor(FAllocationContext Context) const;`
- L40 _public prototype_ `AUTORTFM_DISABLE VInt Ceil(FAllocationContext Context) const;`
- L42 _public function_ `bool IsZero() const`
- L44 _public function_ `AUTORTFM_DISABLE static VRational& New(FAllocationContext Context, VInt InNumerator, VInt InDenominator)`
- L49 _public prototype_ `AUTORTFM_DISABLE ECompares EqualImpl(FAllocationContext Context, VCell* Other, const TFunction<void(::Verse::VValue, ::Verse::VValue)>& HandlePlaceholder);`
- L51 _public prototype_ `uint32 GetTypeHashImpl();`
- L53 _public prototype_ `AUTORTFM_DISABLE void AppendToStringImpl(FAllocationContext Context, FUtf8StringBuilderBase& Builder, EValueStringFormat Format, TSet<const void*>& VisitedObjects, uint32 RecursionDepth);`
- L55 _public prototype_ `AUTORTFM_DISABLE static void SerializeLayout(FAllocationContext Context, VRational*& This, FStructuredArchiveVisitor& Visitor);`
- L56 _public prototype_ `AUTORTFM_DISABLE void SerializeImpl(FAllocationContext Context, FStructuredArchiveVisitor& Visitor);`
- L59 _private prototype_ `AUTORTFM_DISABLE VRational(FAllocationContext Context, VInt InNumerator, VInt InDenominator);`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace Verse`

### `Source/Runtime/CoreUObject/Public/VerseVM/VVMRef.h` (Public)


#### struct `Verse::FRefAwaiterHeader`  
`struct FRefAwaiterHeader`  
_L18-32_
- L20 _public prototype_ `FRefAwaiterHeader() = default;`
- L22 _public member_ `FSetElementId Prev;`
- L23 _public member_ `FSetElementId Next;`
- L27 _public prototype_ `template <typename UnaryFunction> void ForEach(const TSet<FRefAwaiter>&, UnaryFunction) const;` — Non-reentrant
- L31 _public prototype_ `template <typename UnaryFunction> bool AnyOf(const TSet<FRefAwaiter>&, UnaryFunction) const;` — Reentrant

#### struct `Verse::FRefAwaiter`  
`struct FRefAwaiter : FRefAwaiterHeader`  
_L34-68_
- inherits: `FRefAwaiterHeader`
- L36 _public prototype_ `inline FRefAwaiter(FAccessContext Context, VTask& Task, const FOp& AwaitPC);`
- L38 _public member_ `TWriteBarrier<VTask> Task;`
- L39 _public member_ `const FOp* AwaitPC;`
- L45 _public function_ `void Attach(TSet<FRefAwaiter>& Set, FRefAwaiterHeader& Header, FSetElementId ThisElementId)`
- L53 _public function_ `void Detach(TSet<FRefAwaiter>& Set, FRefAwaiterHeader& Header)`
- L60 _private function_ `static FRefAwaiterHeader& Get(TSet<FRefAwaiter>& Set, FRefAwaiterHeader& Header, FSetElementId ElementId)`

#### struct `Verse::VRefRareData`  
`struct VRefRareData : VCell`  
_L70-129_
- inherits: `VCell`
- L73 _public member_ `static TGlobalTrivialEmergentTypePtr<&StaticCppClassInfo> EmergentType;`
- L75 _public function_ `AUTORTFM_DISABLE static VRefRareData& New(FAllocationContext Context, VValue Domain)`
- L80 _public function_ `VValue GetDomain() const`
- L85 _public prototype_ `VTask* GetLiveTask() const;`
- L87 _public prototype_ `void SetLiveTask(FAllocationContext, VTask*);`
- L89 _public prototype_ `void AddAwaitTask(FAccessContext, VTask&);`
- L92 _public prototype_ `template <typename UnaryFunction> void ForEachAwaitTask(UnaryFunction) const;`
- L95 _public prototype_ `template <typename UnaryFunction> bool AnyAwaitTask(UnaryFunction) const;`
- L97 _public function_ `size_t GetAllocatedSize() const`
- L103 _private function_ `AUTORTFM_DISABLE explicit VRefRareData(FAllocationContext Context, VValue Domain) : VCell`
- L110 _private prototype_ `VRefRareData(const VRefRareData&) = delete;`
- L112 _private prototype_ `VRefRareData(VRefRareData&&) = delete;`
- L114 _private prototype_ `VRefRareData& operator=(const VRefRareData&) = delete;`
- L116 _private prototype_ `VRefRareData& operator=(VRefRareData&&) = delete;`
- L118 _private function_ `~VRefRareData()`
- L123 _private prototype_ `static bool ContainsAwaitTask(const VTask&, const FOp&);`
- L125 _private member_ `TWriteBarrier<VValue> Domain;`
- L126 _private member_ `TWriteBarrier<VTask> LiveTask;`
- L127 _private member_ `TSet<FRefAwaiter> AwaiterBuffer;`
- L128 _private member_ `FRefAwaiterHeader AwaiterHeader;`

#### struct `Verse::VRef`  
`struct VRef : VHeapValue`  
_L131-198_
- inherits: `VHeapValue`
- L134 _public member_ `static TGlobalTrivialEmergentTypePtr<&StaticCppClassInfo> GlobalTrivialEmergentType;`
- L136 _public function_ `AUTORTFM_DISABLE static VRef& New(FAllocationContext Context, VValue Domain = {})`
- L141 _public function_ `VValue Get(FAllocationContext Context)`
- L146 _public prototype_ `void Set(FAllocationContext Context, VValue NewValue);`
- L148 _public function_ `void SetNonTransactionally(FAccessContext Context, VValue NewValue)`
- L153 _public prototype_ `AUTORTFM_DISABLE void AppendToStringImpl(FAllocationContext Context, FUtf8StringBuilderBase& Builder, EValueStringFormat Format, TSet<const void*>& VisitedObjects, uint32 RecursionDepth);`
- L154 _public prototype_ `AUTORTFM_DISABLE TSharedPtr<FJsonValue> ToJSONImpl(FRunningContext, EValueJSONFormat, TMap<const void*, EVisitState>& VisitedObjects, FToJsonCallback, uint32 RecursionDepth, FJsonObject* Defs);`
- L155 _public prototype_ `AUTORTFM_DISABLE static void SerializeLayout(FAllocationContext Context, VRef*& This, FStructuredArchiveVisitor& Visitor);`
- L156 _public prototype_ `AUTORTFM_DISABLE void SerializeImpl(FAllocationContext Context, FStructuredArchiveVisitor& Visitor);`
- L157 _public member_ `static constexpr bool InstancedCell = true;`
- L159 _public function_ `VValue GetDomain() const`
- L164 _public prototype_ `VTask* GetLiveTask() const;`
- L166 _public prototype_ `AUTORTFM_DISABLE void SetLiveTask(FAllocationContext, VTask*);`
- L168 _public prototype_ `AUTORTFM_DISABLE void AddAwaitTask(FAllocationContext, VTask&);`
- L171 _public function_ `template <typename UnaryFunction> void ForEachAwaitTask(UnaryFunction F) const`
- L180 _public function_ `template <typename UnaryFunction> bool AnyAwaitTask(UnaryFunction F) const`
- L185 _public prototype_ `AUTORTFM_DISABLE void VisitMembersImpl(FAllocationContext, FDebuggerVisitor&);`
- L188 _private member_ `VRestValue Value;`
- L189 _private member_ `TWriteBarrier<VRefRareData> RareData;`
- L191 _private function_ `explicit VRef(FAllocationContext Context, VValue Domain) : VHeapValue`

#### struct `Verse::VBatchedRefs`  
`struct VBatchedRefs : VHeapValue`  
_L235-303_
- inherits: `VHeapValue`
- L238 _public member_ `static TGlobalTrivialEmergentTypePtr<&StaticCppClassInfo> GlobalTrivialEmergentType;`
- L240 _public function_ `static VBatchedRefs& New(FAllocationContext Context)`
- L245 _public function_ `void Add(FAllocationContext Context, VRef& BatchedRef)`
- L251 _public function_ `void BeginBatch()`
- L256 _public function_ `void EndBatch()`
- L262 _public function_ `bool Batched()`
- L268 _public function_ `template <typename UnaryFunction> void ForEach(UnaryFunction F) const`
- L277 _public function_ `template <typename UnaryFunction> bool AnyOf(UnaryFunction F) const`
- L289 _public function_ `void Reset(FAllocationContext Context)`
- L295 _private function_ `explicit VBatchedRefs(FAllocationContext Context) : VHeapValue`
- L301 _private member_ `TWriteBarrier<VMutableArray> BatchedRefs;`
- L302 _private member_ `uint64 BatchNestingDepth{0};`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace Verse`
- L213 _function_ `template <typename SetType> VValue UnwrapTransparentRef(FAllocationContext Context, VValue Value, VTask* Task, SetType Set)` (scope `Verse`) — There are different designs going on in regards to VNativeRef and VTransparentRef in the VM currently, ie: VTransparentRef --> We call `UnwrapTransparentRef` in several OpCodes (see LoadField as example) to unwrap these and return the VCell it points to which allows us to directly mutate it which is our current impl of VCell 'deep mutability'. VNativeRef --> The `UnwrapTransparentRef` design does not work here, as we have no 'value' that can be directly passed around, and instead we create a VNativeRef when loading out of a native object via VObject::LoadField/UVerseClasss::LoadField and rely on `Freeze` OpCodes to unwrap them at the correct point. Long term, when we implement 'correct' deep mutability we will need to change from directly passing VCell's around to passing Ref's around which should let us align these two approaches. But for now they are separate and there may be holes where the VNativeRef returned by `LoadField` is not handled by a freeze before being passed to another OpCode and will most likely crash.

### `Source/Runtime/CoreUObject/Public/VerseVM/VVMRegisterName.h` (Public)


#### struct `Verse::FRegisterName`  
`struct FRegisterName`  
_L14-57_
- desc: Mapping from register index to name. VProcedures hold an array of such mappings.
- L16 _public member_ `FRegisterIndex Index;`
- L17 _public member_ `TWriteBarrier<VUniqueString> Name;`
- L18 _public member_ `BytecodeAnalysis::FLiveRange LiveRange;`
- L20 _public prototype_ `FRegisterName() = default;`
- L22 _public function_ `FRegisterName(FAccessContext InContext, FRegisterIndex InIndex, VUniqueString& InName) : Index(InIndex) , Name(InContext, InName)`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace Verse`
- L28 _function_ `friend bool operator<(const FRegisterName& Left, const FRegisterName& Right)` (scope `Verse`)
- L51 _function_ `template <typename TVisitor> friend void Visit(TVisitor& Visitor, FRegisterName& Value)` (scope `Verse`)

### `Source/Runtime/CoreUObject/Public/VerseVM/VVMRestValue.h` (Public)


#### struct `Verse::VRestValue`  
`struct VRestValue`  
_L27-148_
- desc: VRestValue thus represents either a fresh unbound placeholder encoded as a VValue::Root, which it will convert into an allocated VPlaceholder on-demand, or some other VValue, which it will follow on-demand.
- L29 _public prototype_ `VRestValue(const VRestValue&) = default;`
- L30 _public prototype_ `VRestValue& operator=(const VRestValue&) = default;`
- L32 _public function_ `explicit constexpr VRestValue(uint16 SplitDepth)`
- L37 _public function_ `VRestValue(FAccessContext Context, VValue Value) : Value(Context, Value)`
- L42 _public function_ `constexpr void Reset(uint16 SplitDepth)`
- L47 _public function_ `void ResetTransactionally(uint16 SplitDepth)`
- L52 _public function_ `void ResetTrailed(FAllocationContext Context, FTrail& Trail, uint16 SplitDepth)`
- L58 _public function_ `template <EWriteMode WriteMode> AUTORTFM_DISABLE void Set(FAccessContext Context, VValue NewValue)`
- L70 _public function_ `void Set(FAccessContext Context, VValue NewValue)`
- L76 _public prototype_ `void SetTransactionally(FAccessContext, VValue);`
- L78 _public prototype_ `void SetTrailed(FAllocationContext, FTrail&, VValue);`
- L80 _public function_ `constexpr void SetNonCellNorPlaceholder(VValue NewValue)`
- L85 _public function_ `void SetNonCellNorPlaceholderTransactionally(VValue NewValue)`
- L90 _public function_ `void SetNonCellNorPlaceholderTrailed(FAllocationContext Context, FTrail& Trail, VValue NewValue)`
- L95 _public function_ `bool IsRoot() const`
- L100 _public function_ `bool CanDefQuickly() const`
- L105 _public prototype_ `VValue Get(FAllocationContext Context);`
- L107 _public function_ `VValue GetRaw()`
- L112 _public prototype_ `AUTORTFM_DISABLE VValue GetSlow(FAllocationContext Context);`
- L114 _public prototype_ `VValue GetTransactionally(FAllocationContext Context);`
- L116 _public prototype_ `AUTORTFM_DISABLE VValue GetSlowTransactionally(FAllocationContext Context);`
- L118 _public function_ `bool IsUninitialized() const`
- L123 _public prototype_ `bool operator==(const VRestValue& Other) const;`
- L125 _public prototype_ `AUTORTFM_DISABLE void AppendToString(FAllocationContext Context, FUtf8StringBuilderBase& Builder, EValueStringFormat Format, TSet<const void*>& VisitedObjects, uint32 RecursionDepth = 0) const;`
- L126 _public prototype_ `FUtf8String ToString(FAllocationContext Context, EValueStringFormat Format, uint32 RecursionDepth = 0) const;`
- L127 _public prototype_ `AUTORTFM_DISABLE TSharedPtr<FJsonValue> ToJSON(FRunningContext, EValueJSONFormat, TMap<const void*, EVisitState>& VisitedObjects, FToJsonCallback, uint32 RecursionDepth = 0, FJsonObject* Defs = nullptr) const;`
- L138 _private prototype_ `VRestValue() = default;`
- L139 _private member_ `TWriteBarrier<VValue> Value;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace Verse`
- L130 _function_ `template <typename TVisitor> friend void Visit(TVisitor& Visitor, VRestValue& InValue)` (scope `Verse`)
- L151 _function_ `inline void FReferenceCollector::AddReferencedVerseValue(Verse::VRestValue& InValue, const UObject* ReferencingObject, const FProperty* ReferencingProperty)` (scope `FReferenceCollector`)

### `Source/Runtime/CoreUObject/Public/VerseVM/VVMReturnSlot.h` (Public)


#### struct `Verse::VReturnSlot`  
`struct VReturnSlot`  
_L15-101_
- L24 _public function_ `template <typename ReturnSlotType> VReturnSlot(FAllocationContext Context, ReturnSlotType ReturnSlot)`
- L29 _public function_ `VValue Get(FAllocationContext Context)`
- L48 _public function_ `void Set(FAllocationContext Context, VRestValue* InRestValue)`
- L54 _public function_ `void SetTransactionally(FAllocationContext Context, VRestValue* InRestValue)`
- L60 _public function_ `void Set(FAllocationContext Context, VValue InValue)`
- L66 _public function_ `void SetTransactionally(FAllocationContext Context, VValue InValue)`
- L72 _public function_ `void Reset()`
- L93 _private member_ `VRestValue EffectToken{0};`
- L100 _private member_ `EReturnKind Kind;`

#### enum `Verse::VReturnSlot::EReturnKind`  
`enum class EReturnKind : uint8`  
_L17-21_
- L19 _public enumerator_ `RestValue`
- L20 _public enumerator_ `Value`

#### union `Verse::VReturnSlot::(anonymous)`  
``  
_L95-99_

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace Verse`
- L80 _function_ `template <typename TVisitor> friend void Visit(TVisitor& Visitor, VReturnSlot& Value)` (scope `Verse`)
- L97 _member_ `VRestValue* RestValue;` (scope `Verse::VReturnSlot::__anon4cd97763010a`) — This points into Frame or the C++ stack, so we don't need to tell GC about it.
- L98 _member_ `TWriteBarrier<VValue> Value;` (scope `Verse::VReturnSlot::__anon4cd97763010a`)

### `Source/Runtime/CoreUObject/Public/VerseVM/VVMRuntimeError.h` (Public)


#### enum `Verse::ERuntimeDiagnostic`  
`enum class ERuntimeDiagnostic : uint16_t`  
_L43-48_
- L46 _public enumerator_ `VERSE_RUNTIME_GLITCH_ENUM_DIAGNOSTICS(VISIT_DIAGNOSTIC) #undef VISIT_DIAGNOSTIC`

#### enum `Verse::ERuntimeDiagnosticSeverity`  
`enum class ERuntimeDiagnosticSeverity : uint8_t`  
_L50-53_
- L52 _public enumerator_ `UnrecoverableError`

#### struct `Verse::SRuntimeDiagnosticInfo`  
`struct SRuntimeDiagnosticInfo`  
_L55-60_
- L57 _public member_ `const char* Name;`
- L58 _public member_ `const char* Description;`
- L59 _public member_ `ERuntimeDiagnosticSeverity Severity;`

#### class `FVerseRuntimeErrorDelegates`  
`class FVerseRuntimeErrorDelegates`  
_L72-80_
- L76 _public member_ `static FVerseUnwindRuntimeErrorHandler OnUnwindRuntimeError;`
- L79 _public member_ `static FVerseRuntimeErrorReportHandler OnVerseRuntimeError;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API COREUOBJECT_API`
- L10 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogVerseRuntimeError, Log, All);`
- L12 _namespace_ `namespace Verse`
- L15 _macro_ `#define VERSE_RUNTIME_GLITCH_ENUM_DIAGNOSTICS(v) \` — NOTE: (yiliang.siew) Right now, these are all errors, but in the future there could be warnings potentially.
- L45 _macro_ `#define VISIT_DIAGNOSTIC(Severity, EnumName, Description) EnumName,`
- L62 _prototype_ `const SRuntimeDiagnosticInfo& GetRuntimeDiagnosticInfo(const ERuntimeDiagnostic Diagnostic);` (scope `Verse`)
- L64 _prototype_ `FString AsFormattedString(const ERuntimeDiagnostic& Diagnostic, const FText& MessageText);` (scope `Verse`)
- L66 _prototype_ `void RaiseVerseRuntimeError(const Verse::ERuntimeDiagnostic Diagnostic, const FText& MessageText);` (scope `Verse`)
- L69 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FVerseUnwindRuntimeErrorHandler, const Verse::ERuntimeDiagnostic, const FText&);`
- L69 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FVerseUnwindRuntimeErrorHandler, const Verse::ERuntimeDiagnostic, const FText&);`
- L70 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FVerseRuntimeErrorReportHandler, const Verse::ERuntimeDiagnostic, const FText&);`
- L70 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FVerseRuntimeErrorReportHandler, const Verse::ERuntimeDiagnostic, const FText&);`
- L83 _macro_ `#define RAISE_VERSE_RUNTIME_ERROR_CODE(Diagnostic) \` — Mechanism for raising a Verse runtime error.
- L91 _macro_ `#define RAISE_VERSE_RUNTIME_ERROR(Diagnostic, Message) \`
- L99 _macro_ `#define RAISE_VERSE_RUNTIME_ERROR_FORMAT(Diagnostic, FormatString, ...) \`
- L107 _macro_ `#define RETURN_RAISE_VERSE_RUNTIME_ERROR_UNLESS(Cond, ErrCode, ErrStr, ...) \`

### `Source/Runtime/CoreUObject/Public/VerseVM/VVMSamplingProfiler.h` (Public)


#### struct `Verse::FSampledFrame`  
`struct FSampledFrame`  
_L26-41_
- L28 _public member_ `TWriteBarrier<VFrame> Frame;`
- L29 _public member_ `bool bIsNativeCall{false};`
- L30 _public member_ `TArray<TWriteBarrier<VUniqueString>> Callstack;`
- L31 _public member_ `uint32 BytecodeOffset;`
- L32 _public member_ `uint64 Cycles;`
- L33 _public function_ `void MarkReferencedCells(FMarkStack& MarkStack)`

#### struct `Verse::FSamplingProfiler`  
`struct AUTORTFM_DISABLE FSamplingProfiler final : FRunnable`  
_L44-93_
- inherits: `FRunnable`
- desc: - TODO: Redact non-user visible callstacks
- L55 _public prototype_ `FSamplingProfiler();`
- L57 _public prototype_ `void Start();`
- L58 _public function_ `void Pause()`
- L61 _public prototype_ `uint32 Run() override;` — FRunnable Interface
- L62 _public function_ `void Stop() override`
- L67 _public prototype_ `void Exit() override;`
- L70 _public prototype_ `void Sample(FRunningContext Context, FOp* PC, VFrame* Frame, VTask* Task);`
- L71 _public prototype_ `void ForceSampleCurrentContext();`
- L72 _public prototype_ `void ProcessSamples();`
- L73 _public prototype_ `void MarkReferencedCells(FMarkStack&);`
- L75 _public member_ `TUniquePtr<FRunnableThread> Thread;`
- L76 _public member_ `FProcessor Processor;`
- L78 _public member_ `TArray<FSampledFrame> Samples;` — Written by Sample() under SampleMutex
- L82 _public member_ `uint32 StringIdCounter = 0;` — Used to trace the strings already emitted to insights this session TODO: Reset these upon a new insights connection
- L83 _public member_ `TMap<VUniqueString*, uint32> TracedStringIds;`
- L85 _public member_ `bool bIsRunning = false;`
- L86 _public member_ `std::atomic<bool> SampleRequested = false;`
- L87 _public member_ `std::atomic<bool> bStopRequested = false;`
- L88 _public member_ `std::atomic<bool> bPauseRequested = false;`
- L90 _public member_ `UE::FMutex SampleMutex;` — Sample() (mutator) VS ProcessSamples() (processor)
- L91 _public member_ `UE::FMutex ProcessingMutex;` — MarkReferencedCells() VS ProcessSamples() (processor)
- L92 _public member_ `UE::FEventCount WaitEvent;`

#### struct `Verse::FSamplingProfiler::FProcessor`  
`struct AUTORTFM_DISABLE FProcessor final : FRunnable`  
_L46-53_
- inherits: `FRunnable`
- L48 _public prototype_ `void Start(FSamplingProfiler* InProfiler);`
- L49 _public prototype_ `uint32 Run() override;`
- L51 _public member_ `FSamplingProfiler* Profiler = nullptr;`
- L52 _public member_ `TUniquePtr<FRunnableThread> Thread;`

#### Free symbols / members of external scopes

- L21 _namespace_ `namespace Verse`
- L95 _prototype_ `FSamplingProfiler* GetSamplingProfiler();` (scope `Verse`)
- L96 _prototype_ `FSamplingProfiler* GetRunningSamplingProfiler();` (scope `Verse`)
- L97 _prototype_ `void SetSamplingProfiler(FSamplingProfiler*);` (scope `Verse`)

### `Source/Runtime/CoreUObject/Public/VerseVM/VVMSanitizers.h` (Public)


#### Free symbols / members of external scopes

- L8 _macro_ `#define V_NO_SANITIZE_ADDRESS __attribute__((no_sanitize_address))`
- L10 _macro_ `#define V_NO_SANITIZE_ADDRESS`

### `Source/Runtime/CoreUObject/Public/VerseVM/VVMScope.h` (Public)


#### struct `Verse::VScope`  
`struct VScope : VCell`  
_L13-38_
- inherits: `VCell`
- desc: The lexical scope of a function.
- L16 _public member_ `static TGlobalTrivialEmergentTypePtr<&StaticCppClassInfo> GlobalTrivialEmergentType;`
- L18 _public member_ `TWriteBarrier<VScope> ParentScope;`
- L21 _public member_ `const uint32 NumCaptures;` — Variables free in this scope but not free in `ParentScope`.
- L22 _public member_ `TWriteBarrier<VValue> Captures[];`
- L24 _public prototype_ `static VScope& New(FAllocationContext, VScope* ParentScope, uint32 NumCaptures);`
- L25 _public prototype_ `static VScope& New(FAllocationContext, VArchetype& Archetype);`
- L26 _public prototype_ `static VScope& New(FAllocationContext Context);`
- L27 _public prototype_ `static VScope& NewUninitialized(FAllocationContext, uint32 NumCaptures);`
- L29 _public prototype_ `VScope& GetRootScope();`
- L31 _public prototype_ `AUTORTFM_DISABLE static void SerializeLayout(FAllocationContext, VScope*& This, FStructuredArchiveVisitor&);`
- L32 _public prototype_ `AUTORTFM_DISABLE void SerializeImpl(FAllocationContext, FStructuredArchiveVisitor&);`
- L35 _private prototype_ `static size_t NumBytes(uint32 NumCaptures);`
- L37 _private prototype_ `VScope(FAllocationContext, VScope* ParentScope, uint32 NumCaptures);`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace Verse`

### `Source/Runtime/CoreUObject/Public/VerseVM/VVMSession.h` (Public)


#### class `Verse::FSession`  
`class FSession #if WITH_VERSE_VM : public FGlobalHeapCensusRoot #else : public TSharedFromThis<FSession> #endif`  
_L26-72_
- inherits: `FGlobalHeapCensusRoot`
- desc: This 'session' class exists to clear weak_map session vars inbetween fortnite rounds. Why --> References to devices, widgets, characters, entities, components (literally anything scene graph) etc are all likely to become 'invalid' in a sense between rounds when a world is reloaded (BPVM / UE). Thus, we can't reference them safely from weak_maps unless we make them _all_ invalidatable/disposable which we have not done yet as it would make the APIs quite cumbersome. So, instead we clear these maps inbetween rounds to avoid accessing bad data like SOL-4914 ran into.
- L34 _public prototype_ `FSession() = default;`
- L36 _public prototype_ `FSession(const FSession&) = delete;`
- L38 _public prototype_ `FSession(FSession&&) = delete;`
- L40 _public prototype_ `FSession& operator=(const FSession&) = delete;`
- L42 _public prototype_ `FSession& operator=(FSession&&) = delete;`
- L44 _public prototype_ `~FSession() = default;`
- L46 _public prototype_ `void ResetWeakMaps();`
- L48 _public prototype_ `void AddSessionMap(const FMapProperty*, UObject* Container);`
- L51 _public prototype_ `static FSession& GetSession();`
- L53 _public prototype_ `void AddSessionMap(FRunningContext Context, VRef& SessionMap);`
- L55 _public prototype_ `void ConductCensus() override;`
- L58 _private member_ `UE::FMutex CensusMutex;`
- L59 _private member_ `TArray<TWeakBarrier<VRef>> SessionMapVRefs;`
- L61 _private function_ `static FSession& GetSession()`
- L67 _private member_ `static TSharedPtr<FSession> Session;`
- L71 _private member_ `TArray<TPair<const FMapProperty*, FWeakObjectPtr>> SessionMapReferences;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace Verse`

### `Source/Runtime/CoreUObject/Public/VerseVM/VVMShape.h` (Public)


#### enum `Verse::EFieldType`  
`enum class EFieldType : int8`  
_L23-41_
- L27 _public enumerator_ `Offset` — The field's value is stored in a VObject. e.g. `c := class{ X:int }` or `c := class{ var X:int = 0 }`
- L30 _public enumerator_ `FProperty` — The field's value is a native type stored in a UObject or VNativeStruct.
- L32 _public enumerator_ `FPropertyVar` — The field's value is a mutable native type stored in a UObject or VNativeStruct.
- L34 _public enumerator_ `FVerseProperty` — The field's value is a VRestValue stored in a UObject or VNativeStruct.
- L40 _public enumerator_ `Constant` — The field's value is stored in the shape. This is used for fields default-initialized to a constant, such as methods. e.g. `a := class{ X:int = 3, Y:int = 5, F(Z:int):int = X + Y + Z }; A := a{ X := 8 } Here, `A.Y` and `A.F` are stored in the shape, while `A.X` is stored in the object.

#### struct `Verse::VShape`  
`struct VShape : VCell`  
_L44-140_
- inherits: `VCell`
- desc: Maps fully qualified names to offsets/constants.
- L100 _public typedef_ `using FieldsMap = TMap<TWriteBarrier<VUniqueString>, VEntry, FDefaultSetAllocator, FFieldsMapKeyFuncs>;`
- L103 _public member_ `static TGlobalTrivialEmergentTypePtr<&StaticCppClassInfo> GlobalTrivialEmergentType;`
- L107 _public prototype_ `AUTORTFM_DISABLE static VShape* New(FAllocationContext Context, FieldsMap&& InFields);` — Create a new shape. Note that indices for offset-based fields will be discarded and the fields given re-ordered indices as part of the new shape created.
- L109 _public prototype_ `const VEntry* GetField(const VUniqueString& Name) const;`
- L110 _public prototype_ `const VEntry& GetField(int32 FieldIndex) const;`
- L111 _public function_ `const int32 GetFieldIndex(VUniqueString& Name) const`
- L115 _public function_ `const int32 GetMaxFieldIndex() const`
- L120 _public prototype_ `uint64 GetNumFields() const;`
- L122 _public prototype_ `bool operator==(const VShape& Other) const;`
- L124 _public prototype_ `AUTORTFM_DISABLE VShape& CopyToMeltedShape(FAllocationContext);`
- L126 _public function_ `FieldsMap::TIterator CreateFieldsIterator()`
- L128 _public prototype_ `AUTORTFM_DISABLE VShape(FAllocationContext Context, FieldsMap&& InFields);`
- L134 _public member_ `FieldsMap Fields;` — Mapping of the field names to their data in the layout. This should not be mutated after initialization; if this needs to be modified, you should create a new shape and emergent type instead. We can't mark this map as `const` because we need to be able to mark the entries and names to hold strong references to them.
- L136 _public member_ `uint64 NumIndexedFields;`
- L139 _public member_ `bool bHasAccessors = false;` — Perhaps we should store this as a bit in the VCell header

#### struct `Verse::VShape::VEntry`  
`struct VEntry`  
_L46-88_
- L64 _public member_ `EFieldType Type;`
- L67 _public prototype_ `VEntry(const VEntry& Other);` — Must have a copy/move constructor in order to be used with `TMap` as the value type.
- L68 _public function_ `VEntry(VEntry&& Other) : VEntry(Other)`
- L71 _public function_ `static VEntry Offset()`
- L73 _public function_ `static VEntry Property(FProperty* InProperty = nullptr)` — TODO: (yiliang.siew) Should these initialize to `VRestValue`s? Otherwise `Def` won't work correctly.
- L74 _public function_ `static VEntry PropertyVar(FProperty* InProperty = nullptr)`
- L75 _public function_ `static VEntry VerseProperty(FProperty* InProperty = nullptr)`
- L76 _public function_ `static VEntry Constant(FAccessContext Context, VValue InConstant)`
- L78 _public prototype_ `bool operator==(const VEntry& Other) const;`
- L80 _public function_ `bool IsProperty() const`
- L81 _public prototype_ `bool IsAccessor() const;`
- L82 _public prototype_ `bool IsMethod() const;`
- L85 _private prototype_ `VEntry();`
- L86 _private prototype_ `VEntry(FProperty* InProperty, EFieldType InType);`
- L87 _private prototype_ `VEntry(FAccessContext Context, VValue InConstant);`

#### union `Verse::VShape::VEntry::(anonymous)`  
``  
_L49-62_

#### struct `Verse::VShape::FFieldsMapKeyFuncs`  
`struct FFieldsMapKeyFuncs : TDefaultMapKeyFuncs<TWriteBarrier<VUniqueString>, VEntry, false>`  
_L92-98_
- inherits: `TDefaultMapKeyFuncs<TWriteBarrier<VUniqueString>,VEntry,false>`
- desc: We're providing this in order to be able to lookup into the fields map without having to construct a write barrier around the unique string representing the field name each time.
- L94 _public prototype_ `static bool Matches(KeyInitType A, KeyInitType B);`
- L95 _public prototype_ `static bool Matches(KeyInitType A, const VUniqueString& B);`
- L96 _public prototype_ `static uint32 GetKeyHash(KeyInitType Key);`
- L97 _public prototype_ `static uint32 GetKeyHash(const VUniqueString& Key);`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace Verse`
- L52 _member_ `uint64 Index;` (scope `Verse::VShape::VEntry::__anone1a3cc12010a`) — The zero-based offset for the given entry that can be used to index into the object. Type must be EFieldType::Offset to access.
- L57 _member_ `FProperty* UProperty;` (scope `Verse::VShape::VEntry::__anone1a3cc12010a`) — For shapes of UObjects, this points to the FProperty associated with this field The caller must guarantee that the property lives as long as this shape Type must be EFieldType::FProperty, EFieldType::FPropertyVar or EFieldType::FVerseProperty to access.
- L61 _member_ `TWriteBarrier<VValue> Value;` (scope `Verse::VShape::VEntry::__anone1a3cc12010a`) — The constant value for the given entry. Type must be EFieldType::Constant to access.

### `Source/Runtime/CoreUObject/Public/VerseVM/VVMStoppedWorld.h` (Public)


#### struct `Verse::FStoppedWorld`  
`struct FStoppedWorld`  
_L13-35_
- L15 _public prototype_ `FStoppedWorld() = default;`
- L17 _public prototype_ `FStoppedWorld(FStoppedWorld&&);`
- L18 _public prototype_ `FStoppedWorld(const FStoppedWorld&) = delete;`
- L20 _public prototype_ `FStoppedWorld& operator=(FStoppedWorld&&);`
- L21 _public prototype_ `FStoppedWorld& operator=(const FStoppedWorld&) = delete;`
- L23 _public prototype_ `void CancelStop();`
- L26 _public prototype_ `~FStoppedWorld();` — This will crash if you haven't moved this value to another FStoppedWorld or called CancelStop().
- L28 _public function_ `const TArray<FAccessContext>& GetContexts() const`
- L33 _private member_ `TArray<FAccessContext> Contexts;`
- L34 _private member_ `bool bHoldingStoppedWorldMutex = false;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace Verse`

### `Source/Runtime/CoreUObject/Public/VerseVM/VVMStrongCellRegistry.h` (Public)


#### struct `Verse::FStrongCellRegistry`  
`struct FStrongCellRegistry : FGlobalHeapRoot`  
_L17-66_
- inherits: `FGlobalHeapRoot`
- desc: A global registry that prevents cells from getting GC'ed
- L19 _public prototype_ `~FStrongCellRegistry();`
- L22 _public function_ `uint32 Add(FAccessContext Context, VCell* Cell)` — Adds a VCell reference to the set and returns reference count for the VCell after adding
- L39 _public function_ `uint32 Remove(VCell* Cell)` — Removes a VCell reference from the set and returns reference count for the VCell after removing
- L55 _private prototype_ `void Visit(FMarkStackVisitor& Visitor) override;`
- L56 _private prototype_ `void Visit(FAbstractVisitor& Visitor) override;`
- L59 _private prototype_ `template <class VisitorType> void VisitImpl(VisitorType& Visitor);`
- L61 _private prototype_ `void AddInternal(FAccessContext Context, VCell* Cell);`
- L62 _private prototype_ `void RemoveInternal(FSetElementId Id);`
- L64 _private member_ `UE::FTransactionallySafeMutex Mutex;`
- L65 _private member_ `TMap<VCell*, uint32> Registry;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace Verse`

### `Source/Runtime/CoreUObject/Public/VerseVM/VVMStructuredArchiveVisitor.h` (Public)


#### struct `Verse::FStructuredArchiveVisitor`  
`struct FStructuredArchiveVisitor`  
_L20-184_
- L22 _public function_ `FStructuredArchiveVisitor(FAllocationContext InContext, FStructuredArchiveSlot InSlot) : Context(InContext) , Archive(InSlot.GetUnderlyingArchive()) , CurrentSlot(TInPlaceType<FStructuredArchiveSlot>{}, InSlot)`
- L29 _public function_ `FStructuredArchiveVisitor(FAllocationContext InContext, FStructuredArchiveRecord InRecord) : Context(InContext) , Archive(InRecord.GetUnderlyingArchive()) , CurrentSlot(TInPlaceType<FStructuredArchiveRecord>{}, InRecord)`
- L38 _public prototype_ `void Visit(VCell*& Value, const TCHAR* ElementName);`
- L39 _public prototype_ `void Visit(UObject*& Value, const TCHAR* ElementName);`
- L41 _public prototype_ `void Visit(VValue& Value, const TCHAR* ElementName);`
- L42 _public prototype_ `void Visit(VInt& Value, const TCHAR* ElementName);`
- L44 _public prototype_ `void Visit(bool& Value, const TCHAR* ElementName);`
- L45 _public prototype_ `void Visit(uint8& Value, const TCHAR* ElementName);`
- L46 _public prototype_ `void Visit(uint16& Value, const TCHAR* ElementName);`
- L47 _public prototype_ `void Visit(int32& Value, const TCHAR* ElementName);`
- L48 _public prototype_ `void Visit(uint32& Value, const TCHAR* ElementName);`
- L49 _public prototype_ `void Visit(double& Value, const TCHAR* ElementName);`
- L50 _public prototype_ `void Visit(FUtf8String& Value, const TCHAR* ElementName);`
- L51 _public prototype_ `void VisitBulkData(void* Data, uint64 DataSize, const TCHAR* ElementName);`
- L56 _public function_ `template <typename T> void Visit(TWriteBarrier<T>& Value, const TCHAR* ElementName)`
- L82 _public function_ `void Visit(VRestValue& Value, const TCHAR* ElementName)`
- L89 _public function_ `template <typename T> void Visit(T& Value, const TCHAR* ElementName)`
- L98 _public function_ `template <typename T> void Visit(T Begin, T End, const TCHAR* ElementName)`
- L110 _public function_ `template <typename T> void Visit(T* Values, uint64 Count, const TCHAR* ElementName)`
- L116 _public function_ `template <typename F> void VisitObject(const TCHAR* ElementName, const F& VisitFields)`
- L122 _public function_ `template <typename F> void VisitArray(const TCHAR* ElementName, const F& VisitElements)`
- L127 _public function_ `FString GetArchiveName()`
- L132 _public function_ `bool IsLoading()`
- L137 _public function_ `bool IsModifying()`
- L143 _public prototype_ `FStructuredArchiveSlot Slot(const TCHAR* ElementName);`
- L161 _private prototype_ `static const TArray<FName, TFixedAllocator<uint32(EEncodedType::Count)>>& EncodedTypeNames();` — Read/Write the element type description
- L162 _private prototype_ `void WriteElementType(FStructuredArchiveRecord Record, EEncodedType EncodedType);`
- L163 _private prototype_ `EEncodedType ReadElementType(FStructuredArchiveRecord Record);`
- L167 _private prototype_ `void WriteValueBody(FStructuredArchiveRecord Record, VValue& InValue, bool bAllowBatch = false);` — Read/Write a value Modifying values uses WriteValueBody + IsModifying()
- L168 _private prototype_ `VValue ReadValueBody(FStructuredArchiveRecord Record, EEncodedType EncodedType, bool bAllowBatch = false);`
- L171 _private function_ `template <typename SlotType, typename F> void WithSlot(SlotType Slot, const F& VisitSlot)`
- L181 _private member_ `FAllocationContext Context;`
- L182 _private member_ `FArchive& Archive;`
- L183 _private member_ `TVariant<FStructuredArchiveSlot, FStructuredArchiveRecord, FStructuredArchiveStream> CurrentSlot;`

#### enum `Verse::FStructuredArchiveVisitor::EEncodedType`  
`enum class EEncodedType : uint8`  
_L146-158_
- L148 _public enumerator_ `None`
- L149 _public enumerator_ `Cell`
- L150 _public enumerator_ `TransparentRef`
- L151 _public enumerator_ `Object`
- L152 _public enumerator_ `Char`
- L153 _public enumerator_ `Char32`
- L154 _public enumerator_ `Float`
- L155 _public enumerator_ `Int`
- L157 _public enumerator_ `Count`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace Verse`
- L18 _variable_ `template <typename T> constexpr bool bAlwaysFalse = false;` (scope `Verse`)
- L91 _function_ `VisitObject(ElementName, [this, &Value] { using Verse::Visit; Visit(*this, Value); });` (scope `Verse::FStructuredArchiveVisitor::Visit`)
- L100 _function_ `VisitArray(ElementName, [this, &Begin, &End] { for (; Begin != End; ++Begin) { auto&& Element = *Begin; Visit(Element, TEXT("")); } });` (scope `Verse::FStructuredArchiveVisitor::Visit`)

### `Source/Runtime/CoreUObject/Public/VerseVM/VVMSubspace.h` (Public)


#### class `Verse::FSubspace`  
`class FSubspace final`  
_L16-33_
- desc: This is really a pas_heap. Hence, we don't let you create it directly. We create a pas_heap and cast to this.
- L19 _public prototype_ `static FSubspace* Create(size_t MinAlign = 1, size_t ReservationSize = 0, size_t ReservationAlignment = 1);`
- L20 _public prototype_ `std::byte* GetBase() const;`
- L26 _private prototype_ `std::byte* TryAllocate(size_t Size);`
- L27 _private prototype_ `std::byte* TryAllocate(size_t Size, size_t Alignment);`
- L28 _private prototype_ `std::byte* Allocate(size_t Size);`
- L29 _private prototype_ `std::byte* Allocate(size_t Size, size_t Alignment);`
- L31 _private prototype_ `FSubspace() = delete;`
- L32 _private prototype_ `FSubspace(const FSubspace&) = delete;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace Verse`

### `Source/Runtime/CoreUObject/Public/VerseVM/VVMSuspension.h` (Public)


#### struct `Verse::VSuspension`  
`struct VSuspension : VCell`  
_L21-49_
- inherits: `VCell`
- L25 _public member_ `TWriteBarrier<VFailureContext> FailureContext;`
- L26 _public member_ `TWriteBarrier<VTask> Task;`
- L27 _public member_ `TWriteBarrier<VSuspension> Next;`
- L31 _public member_ `TWriteBarrier<VPackage> CurrentPackage;`
- L34 _public member_ `TWriteBarrier<VValue> CurrentOuter;` — TODO: These fields are needed for CVarForceCompileFramework, but should otherwise be WITH_EDITORONLY_DATA.
- L35 _public member_ `EObjectFlags CurrentFlags;`
- L37 _public function_ `VSuspension& Last()`
- L48 _protected prototype_ `VSuspension(FAllocationContext Context, VEmergentType* EmergentType, VFailureContext* FailureContext, VTask* Task);`

#### struct `Verse::FBytecodeSuspensionCaptures`  
`struct FBytecodeSuspensionCaptures`  
_L52-64_
- desc: Base struct for all bytecode suspension capture structs.
- L54 _public prototype_ `FBytecodeSuspensionCaptures() = default;`
- L62 _public prototype_ `FBytecodeSuspensionCaptures(const FBytecodeSuspensionCaptures&) = delete;` — Copy constructor / assignment operator deleted as attempting to copy a FBytecodeSuspensionCaptures is dangerous and likely a bug. This is because FBytecodeSuspensionCaptures are allocated at the tail end of a VBytecodeSuspension, and are obtained by calling VBytecodeSuspension::FromCaptures(). It is not expected to have these constructed in any other way.
- L63 _public prototype_ `FBytecodeSuspensionCaptures& operator=(const FBytecodeSuspensionCaptures&) = delete;`

#### struct `Verse::VBytecodeSuspension`  
`struct VBytecodeSuspension : public VSuspension`  
_L66-120_
- inherits: `VSuspension`
- L69 _public member_ `static TGlobalTrivialEmergentTypePtr<&StaticCppClassInfo> GlobalTrivialEmergentType;`
- L72 _public function_ `template <typename Captures> static VBytecodeSuspension& New(FAllocationContext Context, VFailureContext& FailureContext, VTask& Task, VProcedure& Procedure, FOp* PC, const Captures& TheCaptures)`
- L81 _public member_ `TWriteBarrier<VProcedure> Procedure;`
- L82 _public member_ `const EOpcode Opcode;`
- L83 _public member_ `const uint32 BytecodeOffset;`
- L86 _public function_ `template <typename Captures UE_REQUIRES(std::is_base_of_v<FBytecodeSuspensionCaptures, Captures>)> Captures& GetCaptures()`
- L93 _public function_ `template <typename Captures UE_REQUIRES(std::is_base_of_v<FBytecodeSuspensionCaptures, Captures>)> static VBytecodeSuspension& FromCaptures(Captures& TheCaptures)`
- L99 _public prototype_ `template <typename TFunc> void CaptureSwitch(const TFunc& Func);`
- L103 _private function_ `template <typename Captures UE_REQUIRES(std::is_base_of_v<FBytecodeSuspensionCaptures, Captures>)> static size_t CapturesOffset()`
- L109 _private function_ `template <typename Captures> VBytecodeSuspension(FAllocationContext Context, VFailureContext& FailureContext, VTask& Task, VProcedure& Procedure, FOp* PC, const Captures& TheCaptures) : VSuspension(Context, &GlobalTrivialEmergentType.Get(Context), &FailureContext, &Task) , Procedure(Context, &Procedure) , Opcode(PC->Opcode) , BytecodeOffset(Procedure.BytecodeOffset(*PC))`
- L119 _private prototype_ `~VBytecodeSuspension();`

#### struct `Verse::VLambdaSuspension`  
`struct VLambdaSuspension : public VSuspension`  
_L125-167_
- inherits: `VSuspension`
- desc: This is used when you want to run a callback when a placeholder resolves its value. The Args array is there to capture and mark the VValue arguments that the lambda wants to use.
- L128 _public member_ `static TGlobalTrivialEmergentTypePtr<&StaticCppClassInfo> GlobalTrivialEmergentType;`
- L130 _public typedef_ `typedef void (*CallbackType)(FRunningContext, VLambdaSuspension& This, VSuspension*& ToFire);`
- L132 _public function_ `TWriteBarrier<VValue>* Args()`
- L137 _public member_ `uint32 NumValues;`
- L138 _public member_ `CallbackType Callback;`
- L141 _public function_ `template <typename... Args> static VLambdaSuspension& New(FAllocationContext Context, VFailureContext& FailureContext, VTask& Task, CallbackType Callback, Args&&... TheArgs)`
- L147 _private function_ `static size_t ArgsOffset()`
- L152 _private function_ `static size_t AllocationSize(uint32 NumValues)`
- L158 _private function_ `template <typename... ArgsType> VLambdaSuspension(FAllocationContext Context, VFailureContext& FailureContext, VTask& Task, CallbackType Callback, ArgsType&&... TheArgs) : VSuspension(Context, &GlobalTrivialEmergentType.Get(Context), &FailureContext, &Task) , NumValues(sizeof...(ArgsType)) , Callback(Callback)`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace Verse`
- L163 _function_ `new (Args()) TWriteBarrier<VValue>[]` (scope `Verse::VLambdaSuspension::VLambdaSuspension`)

### `Source/Runtime/CoreUObject/Public/VerseVM/VVMTask.h` (Public)


#### struct `Verse::VTask`  
`struct VTask : VValueObject , TIntrusiveTree<VTask>`  
_L26-261_
- inherits: `VValueObject,TIntrusiveTree<VTask>`
- L30 _public member_ `static TGlobalHeapPtr<VEmergentType> EmergentType;`
- L37 _public member_ `bool bRunning{true};` — A task is "running" when it is associated with a frame on the native stack. This includes a running interpreter (even if it is just on the `YieldTask` chain), and native functions like `CancelChildren`. Running tasks can only be resumed by falling through a sequence of yields and native returns. This is independent of `Phase`, as both active and cancelling tasks may suspend.
- L48 _public member_ `EPhase Phase{EPhase::Active};`
- L50 _public member_ `bool bAwaitInitializing{false};`
- L54 _public member_ `FOp* AwaitPC{nullptr};` — When the task is in an await, points to the start of the await body. A read during an await registers the current Task/AwaitPC pair with the VRef. This field is only meaningful when the effect token is concrete.
- L57 _public member_ `TWriteBarrier<VTaskNativeHook> NativeDefers;` — To be run on resume or unwind. May point back to the resumer.
- L61 _public member_ `TWriteBarrier<VTaskNativeHook> NativeAwaitsHead;` — Currently tracked suspended native Await() calls. Invoked in FIFO order when this task completes.
- L62 _public member_ `TWriteBarrier<VTaskNativeHook> NativeAwaitsTail;`
- L65 _public member_ `FOp* ResumePC{nullptr};` — Where execution should continue when resuming.
- L66 _public member_ `TWriteBarrier<VFrame> ResumeFrame;`
- L67 _public member_ `VReturnSlot ResumeSlot;` — May point into ResumeFrame or one of its ancestors.
- L70 _public member_ `FOp* YieldPC;` — Where execution should continue when suspending.
- L71 _public member_ `TWriteBarrier<VFrame> YieldFrame;`
- L72 _public member_ `TWriteBarrier<VTask> YieldTask;`
- L77 _public member_ `TWriteBarrier<VFrame> RootFrame;` — First VFrame of this task (created with null CallerFrame by CallTask). When walking VFrame::CallerFrame's we need this to determine where a task boundary is via 'CurrentFrame == RootFrame' in which case we follow our tasks YieldFrame
- L80 _public member_ `TWriteBarrier<VValue> Result;` — Where execution should continue when complete.
- L81 _public member_ `TWriteBarrier<VTask> LastAwait;`
- L82 _public member_ `TWriteBarrier<VTask> LastCancel;`
- L85 _public member_ `TWriteBarrier<VTask> PrevTask;` — Links for the containing LastCancel or LastAwait list.
- L86 _public member_ `TWriteBarrier<VTask> NextTask;`
- L90 _public member_ `TWriteBarrier<VTaskGroup> TaskGroup;` — The task group associated with this task. TODO(SOL-5927): Remove this field when moving away from content scope-based termination.
- L92 _public prototype_ `AUTORTFM_DISABLE static void BindStruct(FAllocationContext Context, VClass& TaskClass);`
- L93 _public prototype_ `AUTORTFM_DISABLE static void BindStructTrivial(FAllocationContext Context);`
- L95 _public function_ `AUTORTFM_DISABLE static VTask& New(FAllocationContext Context, FOp* YieldPC, VFrame* YieldFrame, VTask* YieldTask, VTask* Parent, VFrame* InRootFrame = nullptr)`
- L107 _public prototype_ `void AddToTaskGroup(FAllocationContext Context);`
- L108 _public prototype_ `bool RemoveFromTaskGroup(FAllocationContext Context);`
- L115 _public prototype_ `AUTORTFM_DISABLE void Terminate(FAllocationContext Context);` — Terminates this task and all of its child sub-tasks. This immediately sets their phase to canceled. This is only safe if we are in the process of unwinding the stack, or the stack is already empty. Only a top-level task should be terminated. This is not done transactionally and cannot be rolled back.
- L118 _public prototype_ `int64 GetNumChildrenRecursively() const;` — Returns the total number of child tasks beneath this task (including children-of-children).
- L120 _public prototype_ `AUTORTFM_DISABLE FOpResult::EKind Resume(FRunningContext Context, VValue ResumeArgument);`
- L121 _public prototype_ `AUTORTFM_DISABLE FOpResult::EKind Unwind(FRunningContext Context);`
- L123 _public function_ `bool Active() const`
- L124 _public function_ `bool Completed() const`
- L126 _public prototype_ `static FOpResult ActiveImpl(FRunningContext Context, VValue Scope, VNativeProcedure::Args Arguments);`
- L127 _public prototype_ `static FOpResult CompletedImpl(FRunningContext Context, VValue Scope, VNativeProcedure::Args Arguments);`
- L128 _public prototype_ `static FOpResult CancelingImpl(FRunningContext Context, VValue Scope, VNativeProcedure::Args Arguments);`
- L129 _public prototype_ `static FOpResult CanceledImpl(FRunningContext Context, VValue Scope, VNativeProcedure::Args Arguments);`
- L130 _public prototype_ `static FOpResult UnsettledImpl(FRunningContext Context, VValue Scope, VNativeProcedure::Args Arguments);`
- L131 _public prototype_ `static FOpResult SettledImpl(FRunningContext Context, VValue Scope, VNativeProcedure::Args Arguments);`
- L132 _public prototype_ `static FOpResult UninterruptedImpl(FRunningContext Context, VValue Scope, VNativeProcedure::Args Arguments);`
- L133 _public prototype_ `static FOpResult InterruptedImpl(FRunningContext Context, VValue Scope, VNativeProcedure::Args Arguments);`
- L135 _public prototype_ `AUTORTFM_DISABLE static FOpResult AwaitImpl(FRunningContext Context, VValue Scope, VNativeProcedure::Args Arguments);`
- L136 _public prototype_ `AUTORTFM_DISABLE static FOpResult CancelImpl(FRunningContext Context, VValue Scope, VNativeProcedure::Args Arguments);`
- L138 _public prototype_ `AUTORTFM_DISABLE FOpResult Cancel(FRunningContext Context);`
- L140 _public function_ `AUTORTFM_DISABLE void SetPhaseTransactionally(EPhase NewPhase)`
- L145 _public function_ `AUTORTFM_DISABLE void SetResumePCTransactionally(FOp* NewResumePC)`
- L150 _public function_ `AUTORTFM_DISABLE void SetYieldPCTransactionally(FOp* NewYieldPC)`
- L155 _public prototype_ `AUTORTFM_DISABLE bool RequestCancel(FRunningContext Context);`
- L156 _public prototype_ `AUTORTFM_DISABLE bool CancelChildren(FRunningContext Context);`
- L158 _public function_ `AUTORTFM_DISABLE void Suspend(FAccessContext Context)`
- L163 _public function_ `AUTORTFM_DISABLE void Resume(FAccessContext Context)`
- L168 _public function_ `void Park(FAllocationContext Context, TWriteBarrier<VTask>& LastTask)`
- L179 _public function_ `void Unpark(FAllocationContext Context, TWriteBarrier<VTask>& LastTask)`
- L202 _public function_ `template <typename FunctorType> requires(!TIsTFunction<std::decay_t<FunctorType>>::Value && std::is_invocable_r_v<void, std::decay_t<FunctorType>, FAllocationContext, VTask*>) AUTORTFM_DISABLE void Defer(FAllocationContext Context, AUTORTFM_IMPLICIT_ENABLE FunctorType&& Func)`
- L211 _public function_ `template <typename FunctorType> requires(!TIsTFunction<std::decay_t<FunctorType>>::Value && std::is_invocable_r_v<void, std::decay_t<FunctorType>, FAllocationContext, VTask*>) AUTORTFM_DISABLE void DeferOpen(FAllocationContext Context, AUTORTFM_IMPLICIT_DISABLE FunctorType&& Func)`
- L218 _public function_ `void ClearDefer()`
- L227 _public function_ `void Await(FRunningContext Context, AUTORTFM_IMPLICIT_ENABLE FunctorType&& Func)`
- L232 _public prototype_ `AUTORTFM_DISABLE void ExecNativeDefer(FAllocationContext);`
- L233 _public prototype_ `AUTORTFM_DISABLE void ExecNativeAwaits(FAllocationContext);`
- L241 _public prototype_ `AUTORTFM_DISABLE static FCallerSpec MakeFrameForSpawn(FAllocationContext Context);`
- L243 _public prototype_ `AUTORTFM_DISABLE static void InitializeGlobals(FAllocationContext Context);`
- L245 _public prototype_ `AUTORTFM_DISABLE void AppendToStringImpl(FAllocationContext Context, FUtf8StringBuilderBase& Builder, EValueStringFormat Format, TSet<const void*>& VisitedObjects, uint32 RecursionDepth = 0);`
- L246 _public prototype_ `AUTORTFM_DISABLE static void SerializeLayout(FAllocationContext Context, VTask*& This, FStructuredArchiveVisitor& Visitor);`
- L247 _public prototype_ `AUTORTFM_DISABLE void SerializeImpl(FAllocationContext Context, FStructuredArchiveVisitor& Visitor);`
- L256 _private prototype_ `AUTORTFM_DISABLE VTask(FAllocationContext Context, VEmergentType& TaskEmergentType, FOp* YieldPC, VFrame* YieldFrame, VTask* YieldTask, VTask* Parent, VFrame* InRootFrame);`
- L258 _private prototype_ `AUTORTFM_DISABLE void Await(FAllocationContext Context, VTaskNativeHook& Hook);`
- L260 _private prototype_ `AUTORTFM_DISABLE void TerminateRecursively(FAllocationContext Context);`

#### enum `Verse::VTask::EPhase`  
`enum class EPhase : int8`  
_L40-47_
- desc: See the note on CancelImpl.
- L42 _public enumerator_ `Active`
- L43 _public enumerator_ `CancelRequested`
- L44 _public enumerator_ `CancelStarted`
- L45 _public enumerator_ `CancelUnwind`
- L46 _public enumerator_ `Canceled`

#### struct `Verse::VTask::FCallerSpec`  
`struct FCallerSpec`  
_L235-240_
- L237 _public member_ `FOp* PC;`
- L238 _public member_ `VFrame* Frame;`
- L239 _public member_ `VRestValue* ReturnSlot;`

#### enum `Verse::VTask::EEndTaskProcedureRegister`  
`enum class EEndTaskProcedureRegister : uint32`  
_L250-254_
- L252 _public enumerator_ `TaskResult = FRegisterIndex::PARAMETER_START`
- L253 _public enumerator_ `__MAX`

#### struct `Verse::VSemaphore`  
`struct VSemaphore : VCell`  
_L264-295_
- inherits: `VCell`
- desc: A counting semaphore with room for a single waiting task. Used for structured concurrency.
- L267 _public member_ `static TGlobalTrivialEmergentTypePtr<&StaticCppClassInfo> GlobalTrivialEmergentType;`
- L269 _public member_ `TWriteBarrier<VTask> Await;`
- L271 _public function_ `static VSemaphore& New(FAllocationContext Context)`
- L276 _public function_ `AUTORTFM_DISABLE int32 IncrementCount(int32 Arg)`
- L282 _public function_ `AUTORTFM_DISABLE int32 DecrementCount(int32 Arg)`
- L289 _private function_ `VSemaphore(FAllocationContext Context) : VCell(Context, &GlobalTrivialEmergentType.Get(Context))`
- L294 _private member_ `int32 Count{0};`

#### Free symbols / members of external scopes

- L21 _namespace_ `namespace Verse`

### `Source/Runtime/CoreUObject/Public/VerseVM/VVMTaskGroup.h` (Public)


#### struct `Verse::VTaskGroup`  
`struct VTaskGroup : VCell`  
_L18-62_
- inherits: `VCell`
- L21 _public member_ `static TGlobalTrivialEmergentTypePtr<&StaticCppClassInfo> GlobalTrivialEmergentType;`
- L23 _public function_ `AUTORTFM_OPEN static VTaskGroup& New(FAllocationContext Context)`
- L31 _public prototype_ `AUTORTFM_OPEN bool HasActiveTasks() const;` — Reports if there are any active tasks in the group; analogous to `GetNumActive() > 0`.
- L34 _public prototype_ `AUTORTFM_OPEN int64 GetNumActive() const;` — Reports the number of tasks in the group. The exact number is considered an implementation detail and is meant for use in unit tests.
- L37 _public prototype_ `AUTORTFM_DISABLE bool AddTask(FAllocationContext, VTask& Task);` — If the passed-in VTask is top-level, adds it to the task group and returns true; returns false otherwise.
- L40 _public prototype_ `AUTORTFM_DISABLE bool RemoveTask(FAllocationContext, VTask& Task);` — Removes a VTask from the group. Does not terminate or otherwise affect the task itself. Returns true if the VTask was contained in the group.
- L43 _public prototype_ `bool AddTaskTransactionally(FAllocationContext, VTask& Task);` — If the passed-in VTask is top-level, adds it to the task group (transactionally) and returns true; returns false otherwise.
- L46 _public prototype_ `bool RemoveTaskTransactionally(FAllocationContext, VTask& Task);` — Removes a VTask from the group. Supports rollback. Does not terminate or otherwise affect the task itself. Returns true if the VTask was contained in the group.
- L49 _public prototype_ `AUTORTFM_DISABLE void TerminateAll(FAllocationContext Context);` — Terminates every VTask in the group. This is not safe to do when VTasks are running; only terminate at the top level, or during unwinding.
- L52 _private function_ `AUTORTFM_OPEN VTaskGroup(FAllocationContext Context) : VCell(Context, &GlobalTrivialEmergentType.Get(Context))`
- L57 _private prototype_ `AUTORTFM_DISABLE VTask* GetAnyTask();`
- L59 _private prototype_ `AUTORTFM_DISABLE void ConductCensusImpl();`
- L61 _private member_ `TWeakBarrierSet<VTask> ActiveTasks;`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace Verse`

### `Source/Runtime/CoreUObject/Public/VerseVM/VVMTaskNativeHook.h` (Public)


#### struct `Verse::VTaskNativeHook`  
`struct AUTORTFM_DISABLE VTaskNativeHook : VCell`  
_L20-68_
- inherits: `VCell`
- L23 _public member_ `static TGlobalTrivialEmergentTypePtr<&StaticCppClassInfo> GlobalTrivialEmergentType;`
- L26 _public member_ `TWriteBarrier<VTaskNativeHook> Next;` — If desired, this can point to the hook added after this one
- L29 _public function_ `void Invoke(FAllocationContext Context, VTask* Task)` — The lambda can be mutable, therefore invocation is not const
- L33 _public function_ `void InvokeTransactionally(FAllocationContext Context, VTask* Task)`
- L42 _public prototype_ `template <typename FunctorType, typename FunctorTypeDecayed = std::decay_t<FunctorType>> requires(!TIsTFunction<FunctorTypeDecayed>::Value && std::is_invocable_r_v<void, FunctorTypeDecayed, FAllocationContext, VTask*>) static VTaskNativeHook& New(FAllocationContext Context, AUTORTFM_IMPLICIT_ENABLE FunctorType&& Func);` — WARNING 1: The destructor of the lambda passed in must be thread safe since it can be invoked on the GC thread WARNING 2: Any VCells or UObjects captured by the lambda will not be visited during GC
- L46 _public prototype_ `template <typename FunctorType, typename FunctorTypeDecayed = std::decay_t<FunctorType>> requires(!TIsTFunction<FunctorTypeDecayed>::Value && std::is_invocable_r_v<void, FunctorTypeDecayed, FAllocationContext, VTask*>) static VTaskNativeHook& NewOpen(FAllocationContext Context, AUTORTFM_IMPLICIT_DISABLE FunctorType&& Func);`
- L49 _protected typedef_ `using InvokerType = void (*)(FAllocationContext, VTaskNativeHook*, VTask*);`
- L50 _protected typedef_ `using DestructorType = void (*)(VTaskNativeHook*);`
- L52 _protected function_ `VTaskNativeHook(FAllocationContext Context) : VCell(Context, &GlobalTrivialEmergentType.Get(Context)) , Invoker([](FAllocationContext, VTaskNativeHook*, VTask*) { VERSE_UNREACHABLE(); }) , TransactionalInvoker([](FAllocationContext, VTaskNativeHook*, VTask*) { VERSE_UNREACHABLE(); }) , Destructor([](VTaskNativeHook*) {})`
- L54 _protected function_ `, Invoker([](FAllocationContext, VTaskNativeHook*, VTask*) { VERSE_UNREACHABLE(); }) , TransactionalInvoker([](FAllocationContext, VTaskNativeHook*, VTask*) { VERSE_UNREACHABLE(); }) , Destructor([](VTaskNativeHook*) {})`
- L55 _protected function_ `, TransactionalInvoker([](FAllocationContext, VTaskNativeHook*, VTask*) { VERSE_UNREACHABLE(); }) , Destructor([](VTaskNativeHook*) {})`
- L56 _protected function_ `, Destructor([](VTaskNativeHook*) {})`
- L60 _protected function_ `~VTaskNativeHook()`
- L65 _protected member_ `InvokerType Invoker;`
- L66 _protected member_ `InvokerType TransactionalInvoker;`
- L67 _protected member_ `DestructorType Destructor;`
- L123 _function_ `template <typename FunctorType, typename FunctorTypeDecayed> requires(!TIsTFunction<FunctorTypeDecayed>::Value && std::is_invocable_r_v<void, FunctorTypeDecayed, FAllocationContext, VTask*>) VTaskNativeHook& VTaskNativeHook::New(FAllocationContext Context, FunctorType&& Func)`
- L135 _function_ `template <typename FunctorType, typename FunctorTypeDecayed> requires(!TIsTFunction<FunctorTypeDecayed>::Value && std::is_invocable_r_v<void, FunctorTypeDecayed, FAllocationContext, VTask*>) VTaskNativeHook& VTaskNativeHook::NewOpen(FAllocationContext Context, FunctorType&& Func)`

#### struct `Verse::TTaskNativeHook`  
`template <typename FunctorTypeDecayed, bool bTransactional> struct TTaskNativeHook : VTaskNativeHook`  
_L71-119_
- inherits: `VTaskNativeHook`
- L74 _public function_ `template <typename FunctorType> AUTORTFM_DISABLE TTaskNativeHook(FAllocationContext Context, FunctorType&& InFunc) : VTaskNativeHook(Context) , Func(EInPlace::InPlace, Forward<FunctorType>(InFunc))`
- L89 _public function_ `static void InvokerImpl(FAllocationContext Context, VTaskNativeHook* InThis, VTask* Task)`
- L96 _public function_ `AUTORTFM_DISABLE static void TransactionalInvokerImpl(FAllocationContext Context, VTaskNativeHook* This, VTask* Task)`
- L102 _public function_ `static void DestructorImpl(VTaskNativeHook* This)`
- L109 _public function_ `template <typename FunctorType> AUTORTFM_DISABLE static TTaskNativeHook& New(FAllocationContext Context, FunctorType&& InFunc)`
- L118 _public member_ `TOptional<FunctorTypeDecayed> Func;`

#### struct `Verse::VTaskNativeHook::NewOpen::FOpenFunctor`  
`struct FOpenFunctor`  
_L137-144_
- L139 _public member_ `FunctorTypeDecayed Func;`
- L140 _public function_ `AUTORTFM_OPEN void operator()(FAllocationContext Context, VTask* Task)`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace Verse`
- L98 _function_ `AutoRTFM::ETransactionStatus Status = AutoRTFM::Close([&] { InvokerImpl(Context, This, Task); });` (scope `Verse::TTaskNativeHook::TransactionalInvokerImpl`)

### `Source/Runtime/CoreUObject/Public/VerseVM/VVMTextPrinting.h` (Public)


#### Free symbols / members of external scopes

- L11 _namespace_ `namespace Verse`
- L13 _prototype_ `void AppendVerseToString(FUtf8StringBuilderBase& Builder, UTF8CHAR Char);` (scope `Verse`)
- L14 _prototype_ `void AppendVerseToString(FUtf8StringBuilderBase& Builder, UTF32CHAR Char);` (scope `Verse`)
- L15 _prototype_ `void AppendVerseToString(FUtf8StringBuilderBase& Builder, FUtf8StringView String);` (scope `Verse`)
- L17 _prototype_ `FUtf8String VerseToString(UTF8CHAR Char);` (scope `Verse`)
- L18 _prototype_ `FUtf8String VerseToString(UTF32CHAR Char);` (scope `Verse`)
- L19 _prototype_ `FUtf8String VerseToString(FUtf8StringView String);` (scope `Verse`)

### `Source/Runtime/CoreUObject/Public/VerseVM/VVMThreadLocalContextHolder.h` (Public)


#### struct `Verse::FThreadLocalContextHolder`  
`struct FThreadLocalContextHolder`  
_L14-33_
- desc: For use by FContextImpl.
- L16 _public prototype_ `FThreadLocalContextHolder() = default;`
- L17 _public prototype_ `~FThreadLocalContextHolder();`
- L19 _public function_ `void Set(FContextImpl* InContext)`
- L26 _public function_ `FContextImpl* Get() const`
- L32 _private member_ `FContextImpl* Context = nullptr;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace Verse`

### `Source/Runtime/CoreUObject/Public/VerseVM/VVMToJsonCallback.h` (Public)


#### Free symbols / members of external scopes

- L14 _namespace_ `namespace Verse`
- L24 _typedef_ `using FToJsonCallback = TFunctionRef<TSharedPtr<FJsonValue>( FRunningContext, VValue, EValueJSONFormat, TMap<const void*, EVisitState>& VisitedObjects, uint32 RecursionDepth, FJsonObject* Defs)>;` (scope `Verse`) — This callback is used by `VValue::ToJSON` and is called before any other evaluation is done to allow callers to add custom handling If it returns nullptr, default handling is used Note: be careful of calling `VCell::ToJson` directly as that bypasses this callback

### `Source/Runtime/CoreUObject/Public/VerseVM/VVMTransaction.h` (Public)


#### struct `Verse::FWriteLog`  
`template <typename T> struct FWriteLog`  
_L25-211_
- L27 _public prototype_ `FWriteLog(const FWriteLog&) = delete;`
- L29 _public prototype_ `FWriteLog(FWriteLog&&) = delete;`
- L31 _public prototype_ `FWriteLog& operator=(const FWriteLog&) = delete;`
- L33 _public prototype_ `FWriteLog& operator=(FWriteLog&&) = delete;`
- L35 _public prototype_ `~FWriteLog() = default;`
- L37 _public function_ `FWriteLog()`
- L43 _public function_ `void Append(FAllocationContext Context, FWriteLog& Child)`
- L51 _public function_ `void Backtrack(FAccessContext Context)`
- L59 _public function_ `void Empty()`
- L72 _protected function_ `void AddImpl(FAllocationContext Context, T Entry)`
- L86 _private function_ `V_FORCEINLINE bool IsInline()`
- L88 _private function_ `V_FORCEINLINE bool ShouldGrowTable()`
- L93 _private function_ `static uint64& FindBucket(uint64 Entry, uint64* Table, uint32 Capacity, bool& bIsNewEntry)`
- L110 _private function_ `FORCENOINLINE void GrowTable(FAllocationContext Context)`
- L132 _private function_ `void AddToInlineHashTable(FAllocationContext Context, T Entry)`
- L152 _private function_ `void AddToHashTable(FAllocationContext Context, T Entry)`
- L167 _private function_ `void EmptyInlineHashTable()`
- L175 _private function_ `void EmptyHashTable()`
- L182 _private function_ `void AppendToLog(FAllocationContext Context, T Entry)`
- L198 _private member_ `static constexpr uint32 InitialCapacity = 4;`
- L200 _private member_ `uint64* Table = InlineTable;`
- L201 _private member_ `T* Log = BitCast<T*>(static_cast<char*>(InlineLog));`
- L203 _private member_ `uint64 InlineTable[InitialCapacity];`
- L204 _private member_ `alignas(alignof(T)) char InlineLog[InitialCapacity * sizeof(T)];`
- L206 _private member_ `uint32 Num = 0;`
- L207 _private member_ `uint32 TableCapacity = InitialCapacity;`
- L210 _private member_ `uint32 LogCapacity = InitialCapacity;` — TODO: It's conceivable we could make LogCapacity a function of TableCapacity. But we're just doing the simple thing for now.

#### struct `Verse::FTrailLogEntry`  
`struct FTrailLogEntry`  
_L213-275_
- L222 _public function_ `explicit FTrailLogEntry(VPlaceholder::EMode& Mode) : Ptr`
- L229 _public function_ `explicit FTrailLogEntry(TWriteBarrier<VValue>& InValue) : Ptr`
- L237 _public function_ `explicit FTrailLogEntry(VCell* InValue) : Ptr` — InValue == Cell who's EmergentType we want to log
- L244 _public function_ `uint64 Key() const`
- L249 _public function_ `void Backtrack(FAccessContext Context)`
- L270 _private typedef_ `using EMode = VPlaceholder::EMode;`
- L272 _private member_ `void* Ptr;` — VPlaceholder::Mode() is byte-aligned, leaving no bits for TPtrVariant.
- L273 _private member_ `uint64 Value;`
- L274 _private member_ `EType Type;`

#### enum `Verse::FTrailLogEntry::EType`  
`enum class EType : uint8`  
_L215-220_
- L217 _public enumerator_ `Mode` — VPlaceholder::Mode
- L218 _public enumerator_ `Value`
- L219 _public enumerator_ `EmergentType`

#### struct `Verse::FTrailLog`  
`struct FTrailLog : FWriteLog<FTrailLogEntry>`  
_L277-293_
- inherits: `FWriteLog<FTrailLogEntry>`
- L279 _public function_ `void Add(FAllocationContext Context, VPlaceholder::EMode& Mode)`
- L284 _public function_ `void Add(FAllocationContext Context, TWriteBarrier<VValue>& Value)`
- L289 _public function_ `void Add(FAllocationContext Context, VCell* Value)`

#### struct `Verse::FTrail`  
`struct FTrail`  
_L295-333_
- L297 _public function_ `FTrail(FTrail* Parent) : Parent(Parent)`
- L302 _public function_ `FTrail* GetParent() const`
- L307 _public function_ `void Exit(FAllocationContext Context)`
- L316 _public function_ `void LogBeforeWrite(FAllocationContext Context, VPlaceholder::EMode& Mode)`
- L321 _public function_ `void LogBeforeWrite(FAllocationContext Context, TWriteBarrier<VValue>& Value)`
- L326 _public function_ `void LogEmergentTypeBeforeWrite(FAllocationContext Context, VCell* Value)`
- L331 _public member_ `FTrailLog Log;`
- L332 _public member_ `FTrail* Parent{nullptr};`

#### struct `Verse::FTransactionLogEntry`  
`struct FTransactionLogEntry`  
_L335-384_
- L337 _public function_ `uintptr_t Key()`
- L339 _public typedef_ `using FSlot = TPtrVariant<TWriteBarrier<VValue>*, TWriteBarrier<TAux<void>>*, TWriteBarrier<VCell>*>;`
- L341 _public member_ `FSlot Slot;` — The memory location we write OldValue into on abort.
- L342 _public member_ `uint64 OldValue;` — VValue or TAux<void> depending on how Slot is encoded.
- L347 _public function_ `FTransactionLogEntry(TWriteBarrier<VValue>& InSlot, VValue OldValue) : Slot(&InSlot) , OldValue(OldValue.GetEncodedBits())`
- L354 _public function_ `template <typename T, typename = std::enable_if_t<std::is_convertible_v<T*, VCell*>>> FTransactionLogEntry(TWriteBarrier<T>& InSlot, T* OldValue) : Slot(reinterpret_cast<TWriteBarrier<VCell>*>(&InSlot)) , OldValue(BitCast<uint64>(OldValue))`
- L360 _public function_ `FTransactionLogEntry(TWriteBarrier<TAux<void>>& InSlot, TAux<void> OldValue) : Slot(&InSlot) , OldValue(BitCast<uint64>(OldValue.GetPtr()))`
- L366 _public function_ `void Backtrack(FAccessContext Context)`

#### struct `Verse::FTransaction`  
`struct AUTORTFM_DISABLE FTransaction`  
_L386-531_
- L407 _public function_ `inline bool IsActive() const` — Convenience function for returning true iff State is Active.
- L410 _public member_ `FTransaction* Parent{nullptr};` — The outer transaction. The outer VM transaction will have a null parent.
- L413 _public member_ `EState State = EState::Constructed;` — The current VM transaction state.
- L417 _public member_ `AutoRTFM::TransactionID AutoRTFMTransactionID{0};` — The identifier of the AutoRTFM transaction created with Start()
- L424 _public function_ `void Start(FRunningContext Context)` — Begins the transaction. Creates and pushes a new AutoRTFM transaction, and sets this FTransaction as the current transaction with Context. Must be in EState::Constructed to call.
- L442 _public function_ `void Commit(FRunningContext Context)` — Commits the transaction. Sets the parent transaction (which may be null) as the current transaction with Context. Commits the AutoRTFM transaction which will call on-commit handlers, and pop the AutoRTFM transaction created with Start() from the AutoRTFM transaction stack. Must be in EState::Active to call.
- L469 _public function_ `template <EAbortMode AbortMode = EAbortMode::Default> void Abort(FAccessContext Context)` — Aborts the transaction. Sets the parent transaction (which may be null) as the current transaction with Context. If AbortMode is Default, then aborts the AutoRTFM transaction created with Start(), which will revert any memory writes, call on-abort handlers and pop the AutoRTFM transaction from the AutoRTFM transaction stack. Must be in EState::Active to call.
- L489 _public function_ `inline void SnapshotTransactionID()` — Stores the current AutoRTFM transaction ID to AutoRTFMTransactionID No-op if !ENABLE_VVM_TRANSACTION_ID_VALIDATION
- L498 _public function_ `inline void ClearTransactionID()` — Resets the current AutoRTFM transaction ID to 0 No-op if !ENABLE_VVM_TRANSACTION_ID_VALIDATION
- L507 _public function_ `inline void DieUnlessTransactionIDIsZero() const` — Dies if AutoRTFMTransactionID is not 0 No-op if !ENABLE_VVM_TRANSACTION_ID_VALIDATION
- L516 _public function_ `inline void DieUnlessTransactionIDsMatch() const` — Dies if AutoRTFMTransactionID is not equal to the current AutoRTFM transaction ID No-op if !ENABLE_VVM_TRANSACTION_ID_VALIDATION
- L525 _public function_ `inline void DieIfTransactionIDsMatch() const` — Dies if AutoRTFMTransactionID is equal to the current AutoRTFM transaction ID No-op if !ENABLE_VVM_TRANSACTION_ID_VALIDATION

#### enum `Verse::FTransaction::EState`  
`enum class EState`  
_L388-404_
- L391 _public enumerator_ `Constructed` — Initial constructed state.
- L395 _public enumerator_ `Active` — The transaction has begun, and is on transaction stack. Active can only transition from the Constructed state, and can only transition to the Committed or Aborted state.
- L399 _public enumerator_ `Committed` — The transaction has completed without failure. Committed can only transition from the Active state, and is a terminal state.
- L403 _public enumerator_ `Aborted` — The transaction has completed with failure. Aborted can only transition from the Active state, and is a terminal state.

#### enum `Verse::FTransaction::EAbortMode`  
`enum class EAbortMode`  
_L452-459_
- desc: Controls the behaviour of FTransaction::Abort()
- L455 _public enumerator_ `Default` — Abort() will rollback and pop the current AutoRTFM transaction.
- L458 _public enumerator_ `AutoRTFMTransactionAlreadyAborted` — Abort() will not rollback and pop the current AutoRTFM transaction, as the AutoRTFM transaction was already aborted before calling.

#### Free symbols / members of external scopes

- L19 _macro_ `#define ENABLE_VVM_TRANSACTION_ID_VALIDATION ((UE_BUILD_SHIPPING == 0) && (UE_BUILD_TEST == 0))`
- L22 _namespace_ `namespace Verse`

### `Source/Runtime/CoreUObject/Public/VerseVM/VVMTree.h` (Public)


#### struct `Verse::TIntrusiveTree`  
`template <typename DerivedType> struct TIntrusiveTree`  
_L12-120_
- L14 _public member_ `TWriteBarrier<DerivedType> Parent;`
- L15 _public member_ `TWriteBarrier<DerivedType> LastChild;`
- L16 _public member_ `TWriteBarrier<DerivedType> Prev;`
- L17 _public member_ `TWriteBarrier<DerivedType> Next;`
- L19 _public function_ `TIntrusiveTree(FAccessContext Context, DerivedType* Parent, EWriteMode WriteMode = EWriteMode::Default) : Parent(Context, Parent)`
- L37 _public function_ `template <EWriteMode WriteMode> void Detach(FAllocationContext Context)`
- L58 _public function_ `void Detach(FAllocationContext Context)`
- L63 _public function_ `void DetachTransactionally(FAllocationContext Context)`
- L71 _public function_ `template <typename FunctionType> void ForEachInPreOrder(FunctionType&& Function)` — Visit each element of the subtree rooted at `this`. This visits nodes in pre-order: parents are visited before children.
- L92 _public function_ `DerivedType* This()`
- L98 _public function_ `template <typename TVisitor> void VisitReferencesImpl(TVisitor& Visitor)`
- L108 _private function_ `template <EWriteMode WriteMode> void AttachToParent(FAccessContext Context)`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace Verse`

### `Source/Runtime/CoreUObject/Public/VerseVM/VVMTrue.h` (Public)


#### Free symbols / members of external scopes

- L9 _namespace_ `namespace Verse`
- L13 _externvar_ `extern bool bGTrue;` (scope `Verse`) — This is useful for telling MSVC to cooperate.

### `Source/Runtime/CoreUObject/Public/VerseVM/VVMTupleType.h` (Public)


#### struct `Verse::VTupleType`  
`struct VTupleType : VType`  
_L20-67_
- inherits: `VType`
- L23 _public member_ `static TGlobalTrivialEmergentTypePtr<&StaticCppClassInfo> GlobalTrivialEmergentType;`
- L25 _public function_ `VUniqueString& GetMangledName() const`
- L26 _public function_ `TArrayView<TWriteBarrier<VValue>> GetElements()`
- L28 _public prototype_ `UVerseStruct* GetOrCreateUStruct(FAllocationContext Context, UPackage* Package, bool bIsInstanced);`
- L29 _public prototype_ `void AddUStruct(FAllocationContext, UPackage* Package, UVerseStruct* Struct);`
- L31 _public prototype_ `AUTORTFM_DISABLE static VTupleType& New(FAllocationContext Context, VProgram& Program, VUniqueString& InMangledName, int32 InNumElements, bool& bOutNew);`
- L33 _public member_ `static constexpr bool SerializeIdentity = false;`
- L34 _public prototype_ `AUTORTFM_DISABLE static void SerializeLayout(FAllocationContext Context, VTupleType*& This, FStructuredArchiveVisitor& Visitor);`
- L35 _public prototype_ `AUTORTFM_DISABLE void SerializeImpl(FAllocationContext Context, FStructuredArchiveVisitor& Visitor);`
- L37 _public prototype_ `AUTORTFM_DISABLE TSharedPtr<FJsonValue> ToJSONImpl(FRunningContext, EValueJSONFormat, TMap<const void*, EVisitState>& VisitedObjects, FToJsonCallback, uint32 RecursionDepth = 0, FJsonObject* Defs = nullptr);`
- L38 _public prototype_ `AUTORTFM_DISABLE VValue FromJSONImpl(FRunningContext, const FJsonValue&, EValueJSONFormat, FFromJsonCallback);`
- L41 _private function_ `VTupleType(FAllocationContext Context, VUniqueString& InMangledName, int32 InNumElements) : VType(Context, &GlobalTrivialEmergentType.Get(Context)) , MangledName(Context, InMangledName) , NumElements(InNumElements)`
- L52 _private prototype_ `UVerseStruct* CreateUStruct(FAllocationContext Context, UPackage* Package, bool bIsInstanced);`
- L54 _private member_ `TWriteBarrier<VUniqueString> MangledName;`
- L63 _private member_ `TMap<TWriteBarrier<VValue>, TWriteBarrier<VValue>, FDefaultSetAllocator, FUStructMapKeyFuncs> AssociatedUStructs;`
- L65 _private member_ `int32 NumElements;`
- L66 _private member_ `TWriteBarrier<VValue> Elements[];`
- L69 _function_ `inline UVerseStruct* VTupleType::GetOrCreateUStruct(FAllocationContext Context, UPackage* Package, bool bIsInstanced)`

#### struct `Verse::VTupleType::FUStructMapKeyFuncs`  
`struct FUStructMapKeyFuncs : TDefaultMapKeyFuncs<TWriteBarrier<VValue>, TWriteBarrier<VValue>, false>`  
_L56-62_
- inherits: `TDefaultMapKeyFuncs<TWriteBarrier<VValue>,TWriteBarrier<VValue>,false>`
- L58 _public function_ `static bool Matches(KeyInitType A, KeyInitType B)`
- L59 _public function_ `static bool Matches(KeyInitType A, UPackage* B)`
- L60 _public function_ `static uint32 GetKeyHash(KeyInitType Key)`
- L61 _public function_ `static uint32 GetKeyHash(UPackage* Key)`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace Verse`

### `Source/Runtime/CoreUObject/Public/VerseVM/VVMType.h` (Public)


#### struct `Verse::VType`  
`struct VType : VHeapValue`  
_L23-29_
- inherits: `VHeapValue`
- desc: Represents Verse types, which may be independent of object shape, and independent of C++ type.
- L28 _protected prototype_ `explicit VType(FAllocationContext Context, VEmergentType* Type);`

#### struct `Verse::VTrivialType`  
`struct VTrivialType : VType`  
_L31-41_
- inherits: `VType`
- L35 _public member_ `static TGlobalHeapPtr<VTrivialType> Singleton;`
- L37 _public prototype_ `AUTORTFM_DISABLE static void Initialize(FAllocationContext Context);`
- L40 _private prototype_ `VTrivialType(FAllocationContext Context);`

#### struct `Verse::VAnyType`  
`struct VAnyType : VType`  
_L106-112_
- inherits: `VType`
- L108 _public prototype_ `DECLARE_PRIMITIVE_TYPE_BODY(Any);`
- L111 _public prototype_ `bool SubsumesImpl(FAllocationContext, VValue);`

#### struct `Verse::VMapType`  
`struct VMapType : VWeakMapType`  
_L166-188_
- inherits: `VWeakMapType`
- L169 _public member_ `static TGlobalTrivialEmergentTypePtr<&StaticCppClassInfo> GlobalTrivialEmergentType;`
- L171 _public function_ `static VMapType& New(FAllocationContext Context, VValue KeyType, VValue ValueType)`
- L176 _public member_ `static constexpr bool SerializeIdentity = false;`
- L177 _public prototype_ `AUTORTFM_DISABLE static void SerializeLayout(FAllocationContext Context, VMapType*& This, FStructuredArchiveVisitor& Visitor);`
- L178 _public prototype_ `AUTORTFM_DISABLE void SerializeImpl(FAllocationContext Context, FStructuredArchiveVisitor& Visitor);`
- L180 _public prototype_ `AUTORTFM_DISABLE TSharedPtr<FJsonValue> ToJSONImpl(FRunningContext, EValueJSONFormat, TMap<const void*, EVisitState>& VisitedObjects, FToJsonCallback, uint32 RecursionDepth, FJsonObject* Defs);`
- L181 _public prototype_ `AUTORTFM_DISABLE VValue FromJSONImpl(FRunningContext, const FJsonValue&, EValueJSONFormat, FFromJsonCallback);`
- L184 _private function_ `VMapType(FAllocationContext& Context, VValue KeyType, VValue ValueType) : VWeakMapType(Context, KeyType, ValueType, &GlobalTrivialEmergentType.Get(Context))`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace Verse`
- L43 _macro_ `#define DECLARE_PRIMITIVE_TYPE_BODY(Name) \`
- L61 _macro_ `#define DECLARE_PRIMITIVE_TYPE(Name) \`
- L67 _macro_ `#define DECLARE_STRUCTURAL_TYPE(Name, Fields) \`
- L101 _macro_ `#define DECLARE_STRUCTURAL_TYPE_FIELD(Name) Name`
- L102 _macro_ `#define DECLARE_STRUCTURAL_TYPE_PARAM(Name) VValue In##Name`
- L103 _macro_ `#define NAME_STRUCTURAL_TYPE_PARAM(Name) In##Name`
- L104 _macro_ `#define INIT_STRUCTURAL_TYPE_FIELD(Name) Name(Context, In##Name)`
- L114 _prototype_ `DECLARE_PRIMITIVE_TYPE(Void);` (scope `Verse`)
- L115 _prototype_ `DECLARE_PRIMITIVE_TYPE(Comparable);` (scope `Verse`)
- L116 _prototype_ `DECLARE_PRIMITIVE_TYPE(Logic);` (scope `Verse`)
- L117 _prototype_ `DECLARE_PRIMITIVE_TYPE(Rational);` (scope `Verse`)
- L118 _prototype_ `DECLARE_PRIMITIVE_TYPE(Char8);` (scope `Verse`)
- L119 _prototype_ `DECLARE_PRIMITIVE_TYPE(Char32);` (scope `Verse`)
- L120 _prototype_ `DECLARE_PRIMITIVE_TYPE(Range);` (scope `Verse`)
- L122 _macro_ `#define TYPE_FIELDS(Field) Field(PositiveType)`
- L123 _prototype_ `DECLARE_STRUCTURAL_TYPE(Type, TYPE_FIELDS) #undef TYPE_FIELDS #define TYPE_FIELDS(Field) Field(ElementType) DECLARE_STRUCTURAL_TYPE(Array, TYPE_FIELDS) #undef TYPE_FIELDS #define TYPE_FIELDS(Field) Field(ElementType) DECLARE_STRUCTURAL_TYPE(Generator, TYPE_FIELDS) #undef TYPE_FIELDS #define TYPE_FIELDS(Field) Field(KeyType), Field(ValueType) DECLARE_STRUCTURAL_TYPE(WeakMap, TYPE_FIELDS) #undef TYPE_FIELDS #define TYPE_FIELDS(Field) Field(ValueType) DECLARE_STRUCTURAL_TYPE(Pointer, TYPE_FIELDS) #undef TYPE_FIELDS DECLARE_PRIMITIVE_TYPE(Reference);` (scope `Verse`)
- L126 _macro_ `#define TYPE_FIELDS(Field) Field(ElementType)`
- L134 _macro_ `#define TYPE_FIELDS(Field) Field(KeyType), Field(ValueType)`
- L138 _macro_ `#define TYPE_FIELDS(Field) Field(ValueType)`
- L145 _prototype_ `DECLARE_STRUCTURAL_TYPE(Option, TYPE_FIELDS) #undef TYPE_FIELDS #define TYPE_FIELDS(Field) Field(SuperType) DECLARE_STRUCTURAL_TYPE(Concrete, TYPE_FIELDS) #undef TYPE_FIELDS #define TYPE_FIELDS(Field) Field(SuperType) DECLARE_STRUCTURAL_TYPE(Castable, TYPE_FIELDS) #undef TYPE_FIELDS DECLARE_PRIMITIVE_TYPE(Function);` (scope `Verse`)
- L148 _macro_ `#define TYPE_FIELDS(Field) Field(SuperType)`
- L157 _prototype_ `DECLARE_PRIMITIVE_TYPE(Persistable);` (scope `Verse`)

### `Source/Runtime/CoreUObject/Public/VerseVM/VVMTypeInitOrValidate.h` (Public)


#### enum `Verse::EAddInterfaceType`  
`enum class EAddInterfaceType : uint8`  
_L29-33_
- L31 _public enumerator_ `Direct`
- L32 _public enumerator_ `Indirect`

#### struct `Verse::FInitOrValidateUField`  
`struct FInitOrValidateUField`  
_L35-161_
- L37 _public function_ `FInitOrValidateUField(UField* InField, bool bInIsValidating) : Field(InField) , bIsValidating(bInIsValidating)`
- L42 _public prototype_ `virtual ~FInitOrValidateUField() = default;`
- L44 _public function_ `UField* GetField() const`
- L46 _public function_ `virtual const FInitOrValidateUEnum* AsUEnum() const`
- L47 _public function_ `virtual const FInitOrValidateUVerseEnum* AsUVerseEnum() const`
- L48 _public function_ `virtual const FInitOrValidateUStruct* AsUStruct() const`
- L49 _public function_ `virtual const FInitOrValidateUScriptStruct* AsUScriptStruct() const`
- L50 _public function_ `virtual const FInitOrValidateUVerseStruct* AsUVerseStruct() const`
- L51 _public function_ `virtual const FInitOrValidateUClass* AsUClass() const`
- L52 _public function_ `virtual const FInitOrValidateUVerseClass* AsUVerseClass() const`
- L54 _public function_ `bool IsValidating() const`
- L55 _public function_ `bool IsInitializing() const`
- L58 _public prototype_ `void SetMetaData(bool bEnabled, FName MetaDataName, const TCHAR* MetaDataValue) const;`
- L62 _public function_ `template <typename DestinationType, typename ValueType> void SetValue(DestinationType& Destination, const ValueType& Value, const TCHAR* What) const`
- L76 _public function_ `template <typename DestinationType, typename ValueType> void SetValueNoValidate(DestinationType& Destination, const ValueType& Value) const` — Set value, but skip any validation
- L86 _public function_ `template <typename DestinationType, typename ValueType> void ForceValue(DestinationType& Destination, const ValueType& Value) const` — Set the value regardless of validation step.
- L92 _public function_ `template <typename DestinationType, typename ValueType> void CheckValueMismatch(const DestinationType& Destination, const ValueType& Value, const TCHAR* What, const TCHAR* SubWhat = nullptr) const`
- L102 _protected function_ `template <typename ValueType> static FString FormatValue(ValueType Value)`
- L137 _protected function_ `template <typename ObjectType> static FString FormatValue(TObjectPtr<ObjectType> Value)`
- L143 _protected function_ `template <typename DestinationType, typename ValueType> void LogValueMismatch(const DestinationType& Destination, const ValueType& Value, const TCHAR* What, const TCHAR* SubWhat = nullptr) const`
- L157 _protected prototype_ `virtual void LogError(const FString& text) const = 0;`
- L159 _protected member_ `TObjectPtr<UField> Field;`
- L160 _protected member_ `bool bIsValidating;`

#### struct `Verse::FInitOrValidateUEnum`  
`struct FInitOrValidateUEnum : FInitOrValidateUField`  
_L163-175_
- inherits: `FInitOrValidateUField`
- L165 _public function_ `FInitOrValidateUEnum(UEnum* InEnum, bool bInIsValidating) : FInitOrValidateUField(InEnum, bInIsValidating)`
- L170 _public function_ `virtual const FInitOrValidateUEnum* AsUEnum() const override`
- L172 _public prototype_ `void SetEnums(TArray<TPair<FName, int64>>& InNames, UEnum::ECppForm InCppForm, UEnum::EUnderlyingType InUnderlyingType) const;`
- L174 _public function_ `UEnum* GetUEnum() const`

#### struct `Verse::FInitOrValidateUVerseEnum`  
`struct FInitOrValidateUVerseEnum : FInitOrValidateUEnum`  
_L177-187_
- inherits: `FInitOrValidateUEnum`
- L179 _public function_ `FInitOrValidateUVerseEnum(UVerseEnum* InVerseEnum, bool bInIsValidating) : FInitOrValidateUEnum(InVerseEnum, bInIsValidating)`
- L184 _public function_ `virtual const FInitOrValidateUVerseEnum* AsUVerseEnum() const override`
- L186 _public function_ `UVerseEnum* GetUVerseEnum() const`

#### struct `Verse::FInitOrValidateUStruct`  
`struct FInitOrValidateUStruct : FInitOrValidateUField`  
_L189-201_
- inherits: `FInitOrValidateUField`
- L191 _public function_ `FInitOrValidateUStruct(UStruct* InStruct, bool bInIsValidating) : FInitOrValidateUField(InStruct, bInIsValidating)`
- L196 _public function_ `virtual const FInitOrValidateUStruct* AsUStruct() const override`
- L198 _public prototype_ `void SetSuperStruct(UClass* SuperStruct) const;`
- L200 _public function_ `UStruct* GetUStruct() const`

#### struct `Verse::FInitOrValidateUScriptStruct`  
`struct FInitOrValidateUScriptStruct : FInitOrValidateUStruct`  
_L203-213_
- inherits: `FInitOrValidateUStruct`
- L205 _public function_ `FInitOrValidateUScriptStruct(UScriptStruct* InScriptStruct, bool bInIsValidating) : FInitOrValidateUStruct(InScriptStruct, bInIsValidating)`
- L210 _public function_ `virtual const FInitOrValidateUScriptStruct* AsUScriptStruct() const override`
- L212 _public function_ `UScriptStruct* GetUScriptStruct() const`

#### struct `Verse::FInitOrValidateUVerseStruct`  
`struct FInitOrValidateUVerseStruct : FInitOrValidateUScriptStruct`  
_L215-228_
- inherits: `FInitOrValidateUScriptStruct`
- L217 _public function_ `FInitOrValidateUVerseStruct(UVerseStruct* InVerseStruct, bool bInIsValidating) : FInitOrValidateUScriptStruct(InVerseStruct, bInIsValidating)`
- L222 _public function_ `virtual const FInitOrValidateUVerseStruct* AsUVerseStruct() const override`
- L224 _public prototype_ `void SetVerseClassFlags(uint32 ClassFlags, bool bSetFlags, const TCHAR* What) const;`
- L225 _public prototype_ `void ForceVerseClassFlags(uint32 ClassFlags, bool bSetFlags) const;`
- L227 _public function_ `UVerseStruct* GetUVerseStruct() const`

#### struct `Verse::FInitOrValidateUClass`  
`struct FInitOrValidateUClass : FInitOrValidateUStruct`  
_L230-243_
- inherits: `FInitOrValidateUStruct`
- L232 _public function_ `FInitOrValidateUClass(UClass* InClass, bool bInIsValidating) : FInitOrValidateUStruct(InClass, bInIsValidating)`
- L237 _public function_ `virtual const FInitOrValidateUClass* AsUClass() const override`
- L239 _public prototype_ `void SetClassFlags(EClassFlags ClassFlags, bool bSetFlags, const TCHAR* What) const;`
- L240 _public prototype_ `void SetClassFlagsNoValidate(EClassFlags ClassFlags, bool bSetFlags) const;`
- L242 _public function_ `UClass* GetUClass() const`

#### struct `Verse::FInitOrValidateUVerseClass`  
`struct FInitOrValidateUVerseClass : FInitOrValidateUClass`  
_L245-265_
- inherits: `FInitOrValidateUClass`
- L247 _public function_ `FInitOrValidateUVerseClass(UVerseClass* InVerseClass, bool bInIsValidating) : FInitOrValidateUClass(InVerseClass, bInIsValidating)`
- L252 _public function_ `virtual const FInitOrValidateUVerseClass* AsUVerseClass() const override`
- L254 _public prototype_ `void SetVerseClassFlags(uint32 ClassFlags, bool bSetFlags, const TCHAR* What) const;`
- L255 _public prototype_ `void ForceVerseClassFlags(uint32 ClassFlags, bool bSetFlags) const;`
- L257 _public function_ `UVerseClass* GetUVerseClass() const`
- L259 _public prototype_ `bool AddInterface(UClass* InterfaceClass, EAddInterfaceType InterfaceType);`
- L260 _public prototype_ `void ValidateInterfaces();`
- L263 _private member_ `TArray<UClass*> Interfaces;`
- L264 _private member_ `TArray<UClass*> DirectInterfaces;`

#### struct `Verse::FInitOrValidatorSelector`  
`template <typename UEType> struct FInitOrValidatorSelector`  
_L268-270_
- L275 _public typedef_ `using Validator = FInitOrValidateUVerseClass;`
- L281 _public typedef_ `using Validator = FInitOrValidateUVerseStruct;`
- L287 _public typedef_ `using Validator = FInitOrValidateUVerseEnum;`

#### struct `Verse::FInitOrValidatorSelector`  
`template <> struct FInitOrValidatorSelector<UVerseClass>`  
_L273-276_
- L275 _public typedef_ `using Validator = FInitOrValidateUVerseClass;`
- L281 _public typedef_ `using Validator = FInitOrValidateUVerseStruct;`
- L287 _public typedef_ `using Validator = FInitOrValidateUVerseEnum;`

#### struct `Verse::FInitOrValidatorSelector`  
`template <> struct FInitOrValidatorSelector<UVerseStruct>`  
_L279-282_
- L275 _public typedef_ `using Validator = FInitOrValidateUVerseClass;`
- L281 _public typedef_ `using Validator = FInitOrValidateUVerseStruct;`
- L287 _public typedef_ `using Validator = FInitOrValidateUVerseEnum;`

#### struct `Verse::FInitOrValidatorSelector`  
`template <> struct FInitOrValidatorSelector<UVerseEnum>`  
_L285-288_
- L275 _public typedef_ `using Validator = FInitOrValidateUVerseClass;`
- L281 _public typedef_ `using Validator = FInitOrValidateUVerseStruct;`
- L287 _public typedef_ `using Validator = FInitOrValidateUVerseEnum;`

#### struct `Verse::Private::FVerseVMInitOrValidate`  
`template <typename UEType> struct FVerseVMInitOrValidate : FInitOrValidatorSelector<UEType>::Validator`  
_L295-318_
- inherits: `FInitOrValidatorSelector<UEType>::Validator`
- desc: Wrapper class to implement the logging for the FInitOrValidate types
- L297 _public typedef_ `using Super = FInitOrValidatorSelector<UEType>::Validator;`
- L298 _public function_ `FVerseVMInitOrValidate(UEType* Type) : Super(Type, Type->IsUHTNative())`
- L303 _public function_ `~FVerseVMInitOrValidate()`
- L311 _public function_ `virtual void LogError(const FString& text) const override`
- L317 _public member_ `mutable bool bGotError = false;`

#### Free symbols / members of external scopes

- L16 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogVerseValidation, Log, All);`
- L16 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogVerseValidation, Log, All);`
- L19 _namespace_ `namespace Verse`
- L106 _typedef_ `using UEnumType = std::underlying_type<ValueType>::type;` (scope `Verse::FInitOrValidateUField::FormatValue`)
- L291 _namespace_ `namespace Private` (scope `Verse`)

### `Source/Runtime/CoreUObject/Public/VerseVM/VVMUECodeGen.h` (Public)


#### Free symbols / members of external scopes

- L16 _namespace_ `namespace UECodeGen_Private`
- L22 _namespace_ `namespace Verse`
- L22 _namespace_ `namespace CodeGen` (scope `Verse`)
- L22 _namespace_ `namespace Private` (scope `Verse::CodeGen`)
- L42 _prototype_ `void ConstructUVerseClassNoInit( const TCHAR* PackageName, const TCHAR* Name, UClass*& ReturnClass, void (*RegisterNativeFunc)(), uint32 InSize, uint32 InAlignment, EClassFlags InClassFlags, EClassCastFlags InClassCastFlags, const TCHAR* InConfigName, UClass::ClassConstructorType InClassConstructor, UClass::ClassVTableHelperCtorCallerType InClassVTableHelperCtorCaller, FUObjectCppClassStaticFunctions&& InCppClassStaticFunctions, UClass::StaticClassFunctionType InSuperClassFn, UClass::StaticClassFunctionType InWithinClassFn);` (scope `Verse::CodeGen::Private`) — Construct but do not initialize a UVerseClass @param PackageName name of the package this class will be inside @param Name of the class @param ReturnClass reference to pointer to result. This must be PrivateStaticClass. @param RegisterNativeFunc Native function registration function pointer. @param InSize Size of the class @param InAlignment Alignment of the class @param InClassFlags Class flags @param InClassCastFlags Class cast flags @param InConfigName Class config name @param InClassConstructor Class constructor function pointer @param InClassVTableHelperCtorCaller Class constructor function for vtable pointer @param InCppClassStaticFunctions Function pointers for the class's version of Unreal's reflected static functions @param InSuperClassFn Super class function pointer @param InWithinClassFn Within class function pointer
- L58 _prototype_ `void ConstructUVerseEnum(UEnum*& OutEnum, const UECodeGen_Private::FVerseEnumParams& Params);` (scope `Verse::CodeGen::Private`)
- L59 _prototype_ `void ConstructUVerseStruct(UScriptStruct*& OutStruct, const UECodeGen_Private::FVerseStructParams& Params);` (scope `Verse::CodeGen::Private`)
- L60 _prototype_ `void ConstructUVerseFunction(UFunction** SingletonPtr, const UECodeGen_Private::FVerseFunctionParams& Params);` (scope `Verse::CodeGen::Private`)
- L61 _prototype_ `void ConstructUVerseClass(UClass*& OutClass, const UECodeGen_Private::FVerseClassParams& Params);` (scope `Verse::CodeGen::Private`)
- L64 _prototype_ `void RegisterVerseCallableThunks(UClass* Class, const FVerseCallableThunk* InThunks, uint32 InNumThunks);` (scope `Verse::CodeGen::Private`)

### `Source/Runtime/CoreUObject/Public/VerseVM/VVMUniqueCreator.h` (Public)


#### class `Verse::VUniqueCreator`  
`template <typename Type> class VUniqueCreator : public FGlobalHeapRoot`  
_L22-88_
- inherits: `FGlobalHeapRoot`
- L25 _private member_ `UE::FMutex Mutex;`
- L28 _private member_ `static constexpr uint32 MaxSize = 4 * 1024;` — This should be a hash table
- L29 _private member_ `TWriteBarrier<Type> Items[MaxSize];`
- L30 _private member_ `uint32 ItemsEnd = 0;`
- L33 _private function_ `template <typename SubType, typename... ArgumentTypes> Type* LookupLocked(ArgumentTypes... Arguments)`
- L45 _private function_ `Type* AddLocked(FAccessContext Context, Type* Item)`
- L54 _public prototype_ `VUniqueCreator() = default;`
- L57 _public function_ `template <typename SubType, typename... ArgumentTypes> AUTORTFM_DISABLE Type* GetOrCreate(FAllocationContext Context, ArgumentTypes... Arguments)`
- L73 _public function_ `Type* Add(FAccessContext Context, Type* Item)` — Only call if certain that Item is unique
- L79 _public function_ `void Visit(FMarkStackVisitor& Visitor) override`
- L80 _public function_ `void Visit(FAbstractVisitor& Visitor) override`
- L83 _public function_ `template <class VisitorType> void VisitImpl(VisitorType& Visitor)`

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace Verse`

### `Source/Runtime/CoreUObject/Public/VerseVM/VVMUniqueString.h` (Public)


#### struct `Verse::FUniqueStringSetKeyFuncsBase`  
`template <typename T> struct FUniqueStringSetKeyFuncsBase : BaseKeyFuncs<T, T, false>`  
_L31-43_
- inherits: `BaseKeyFuncs<T,T,false>`
- desc: We're providing this so that we can avoid constructing `TWriteBarrier`/`TWeakBarrier`s to perform lookups in the string pool, which are expensive given that they involve a TLS lookup.
- L33 _public typedef_ `typedef FUtf8StringView KeyInitType;`
- L34 _public typedef_ `typedef VUniqueString& ElementInitType;`
- L36 _public prototype_ `static FUtf8StringView GetSetKey(VUniqueString& Element);`
- L38 _public prototype_ `static FUtf8StringView GetSetKey(const T& Element);`
- L40 _public prototype_ `static bool Matches(FUtf8StringView A, FUtf8StringView B);`
- L42 _public prototype_ `static uint32 GetKeyHash(FUtf8StringView Key);`

#### struct `Verse::FUniqueStringSetKeyFuncs`  
`template <> struct FUniqueStringSetKeyFuncs<TWeakBarrier<VUniqueString>> : FUniqueStringSetKeyFuncsBase<TWeakBarrier<VUniqueString>>`  
_L46-48_
- inherits: `FUniqueStringSetKeyFuncsBase<TWeakBarrier<VUniqueString>>`

#### struct `Verse::FUniqueStringSetKeyFuncs`  
`template <> struct FUniqueStringSetKeyFuncs<TWriteBarrier<VUniqueString>> : FUniqueStringSetKeyFuncsBase<TWriteBarrier<VUniqueString>>`  
_L51-53_
- inherits: `FUniqueStringSetKeyFuncsBase<TWriteBarrier<VUniqueString>>`

#### class `Verse::VStringInternPool`  
`class VStringInternPool final : FGlobalHeapCensusRoot`  
_L55-74_
- inherits: `FGlobalHeapCensusRoot`
- L60 _private prototype_ `VStringInternPool() = default;` — Private constructor since there should only ever be one global instance of this. There's no virtual destructor since `TLazyInitialized` is never destroyed and this is meant to be a global string pool.
- L62 _private prototype_ `AUTORTFM_DISABLE VUniqueString& Intern(FAllocationContext Context, FUtf8StringView String);`
- L65 _private prototype_ `virtual void ConductCensus() override;` — This gives the string intern pool the ability to conduct census on its own to clear references to the strings.
- L69 _private member_ `TWeakBarrierSet<VUniqueString, FUniqueStringSetKeyFuncs<TWeakBarrier<VUniqueString>>> UniqueStrings;` — The pool doesn't own the string data, the context does. So these strings are stored as weakrefs. When the GC conducts a census, this string pool is also cleared of the strings that are unmarked.
- L70 _private member_ `static UE::FMutex Mutex;`

#### struct `Verse::VUniqueString`  
`struct VUniqueString final : VArray`  
_L77-121_
- inherits: `VArray`
- desc: A unique string that lives in the global string intern pool.
- L80 _public member_ `static TGlobalTrivialEmergentTypePtr<&StaticCppClassInfo> GlobalTrivialEmergentType;`
- L86 _public function_ `AUTORTFM_DISABLE static VUniqueString& New(FAllocationContext Context, FUtf8StringView String)` — Creates a new unique string if it does not already exist. Subsequent calls to this function with the same string will return a reference to the string that already exists in the string intern pool.
- L91 _public function_ `bool operator==(const VUniqueString& Other) const`
- L97 _public function_ `FUtf8StringView AsStringView() const` — Shadow `VArrayBase::AsStringView`, avoiding type test.
- L102 _public member_ `static constexpr bool SerializeIdentity = false;`
- L103 _public prototype_ `AUTORTFM_DISABLE static void SerializeLayout(FAllocationContext Context, VUniqueString*& This, FStructuredArchiveVisitor& Visitor);`
- L104 _public prototype_ `AUTORTFM_DISABLE void SerializeImpl(FAllocationContext Context, FStructuredArchiveVisitor& Visitor);`
- L107 _private function_ `AUTORTFM_DISABLE static VUniqueString& Make(FAllocationContext Context, FUtf8StringView String)`
- L112 _private function_ `VUniqueString(FAllocationContext Context, FUtf8StringView String) : VArray(Context, String, &GlobalTrivialEmergentType.Get(Context))`
- L119 _private member_ `static TLazyInitialized<VStringInternPool> StringPool;` — Global unique string table. This has to be wrapped in a `TLazyInitialized` so that the Verse heap is first initialized before this attempts to be initialized.

#### struct `Verse::VUniqueStringSet`  
`struct VUniqueStringSet : VCell`  
_L131-187_
- inherits: `VCell`
- desc: A unique string set. This makes use of a pool so that multiple requests for the same set of unique strings returns the exact same set object in memory.
- L133 _public typedef_ `using SetType = TSet<TWriteBarrier<VUniqueString>, FUniqueStringSetKeyFuncs<TWriteBarrier<VUniqueString>>>;`
- L135 _public member_ `static TGlobalTrivialEmergentTypePtr<&StaticCppClassInfo> GlobalTrivialEmergentType;`
- L152 _public prototype_ `FConstIterator begin() const;`
- L153 _public prototype_ `FConstIterator end() const;`
- L155 _public prototype_ `static VUniqueStringSet& New(FAllocationContext Context, const TSet<VUniqueString*> InSet);`
- L156 _public prototype_ `static VUniqueStringSet& New(FAllocationContext Context, const std::initializer_list<FUtf8StringView>& InStrings);`
- L158 _public prototype_ `bool operator==(const VUniqueStringSet& Other) const;`
- L161 _public prototype_ `bool Equals(const VUniqueStringSet& Other) const;` — This is a slower, deep-equality based check. Suitable for debugging purposes.
- L163 _public prototype_ `uint32 Num() const;`
- L165 _public prototype_ `FSetElementId FindId(const FUtf8StringView& String) const;`
- L167 _public prototype_ `bool IsValidId(const FSetElementId& Id) const;`
- L169 _public prototype_ `AUTORTFM_DISABLE void AppendToStringImpl(FAllocationContext Context, FUtf8StringBuilderBase& Builder, EValueStringFormat Format, TSet<const void*>& VisitedObjects, uint32 RecursionDepth);`
- L172 _private prototype_ `static SetType FormSet(FAllocationContext Context, const TSet<VUniqueString*>& InSet);`
- L173 _private prototype_ `VUniqueStringSet(FAllocationContext Context, const TSet<VUniqueString*>& InSet);`
- L175 _private prototype_ `AUTORTFM_DISABLE static VUniqueStringSet& Make(FAllocationContext Context, const TSet<VUniqueString*>& InSet);`
- L176 _private prototype_ `static bool Equals(const TSet<VUniqueString*>& A, const TSet<VUniqueString*>& B);`
- L180 _private member_ `static TLazyInitialized<VUniqueStringSetInternPool> Pool;` — Global unique string set pool. This has to be wrapped in a `TLazyInitialized` so that the Verse heap is first initialized before this attempts to be initialized.
- L183 _private member_ `SetType Strings;` — The storage for the actual strings in this given set.

#### class `Verse::VUniqueStringSet::FConstIterator`  
`class FConstIterator`  
_L138-151_
- desc: This allows for this type to be used in range-based loops.
- L141 _public prototype_ `const TWriteBarrier<VUniqueString>* operator->() const;`
- L142 _public prototype_ `const TWriteBarrier<VUniqueString>& operator*() const;`
- L143 _public prototype_ `bool operator==(const FConstIterator& Rhs) const;`
- L144 _public prototype_ `bool operator!=(const FConstIterator& Rhs) const;`
- L145 _public prototype_ `FConstIterator& operator++();`
- L149 _private prototype_ `FConstIterator(SetType::TRangedForConstIterator InCurrentIteration);`
- L150 _private member_ `SetType::TRangedForConstIterator CurrentIteration;`

#### struct `Verse::FHashableUniqueStringSetKey`  
`struct FHashableUniqueStringSetKey`  
_L192-218_
- L212 _public member_ `EType Type;`
- L214 _public prototype_ `FHashableUniqueStringSetKey();`
- L215 _public prototype_ `FHashableUniqueStringSetKey(const TSet<VUniqueString*>& InSet);`
- L216 _public prototype_ `FHashableUniqueStringSetKey(const VUniqueStringSet& InCell);`
- L217 _public prototype_ `bool operator==(const FHashableUniqueStringSetKey& Other) const;`

#### enum `Verse::FHashableUniqueStringSetKey::EType`  
`enum class EType : uint8`  
_L194-204_
- L196 _public enumerator_ `Cell`
- L197 _public enumerator_ `Set`
- L203 _public enumerator_ `Invalid` — This means that the key refers to a invalid unique string set - its memory has been swept/is about to be swept and is no longer considered a valid set. This is used as a sentinel value to distinguish between actual empty string sets. When `Type` is set to this, both `Cell` and `Set` are undefined.

#### union `Verse::FHashableUniqueStringSetKey::(anonymous)`  
``  
_L207-210_

#### struct `Verse::FHashableUniqueStringSetKeyFuncs`  
`struct FHashableUniqueStringSetKeyFuncs : BaseKeyFuncs<TWeakBarrier<VUniqueStringSet>, TWeakBarrier<VUniqueStringSet>, false>`  
_L221-233_
- inherits: `BaseKeyFuncs<TWeakBarrier<VUniqueStringSet>,TWeakBarrier<VUniqueStringSet>,false>`
- desc: Allows for lookup into the unique string set pool without unnecessary construction of barriers.
- L223 _public typedef_ `typedef FHashableUniqueStringSetKey KeyInitType;`
- L224 _public typedef_ `typedef VUniqueStringSet& ElementInitType;`
- L226 _public prototype_ `static KeyInitType GetSetKey(ElementInitType& Element);`
- L228 _public prototype_ `static KeyInitType GetSetKey(const TWeakBarrier<VUniqueStringSet>& Element);`
- L230 _public prototype_ `static bool Matches(KeyInitType A, KeyInitType B);`
- L232 _public prototype_ `static uint32 GetKeyHash(KeyInitType Key);`

#### class `Verse::VUniqueStringSetInternPool`  
`class VUniqueStringSetInternPool final : FGlobalHeapCensusRoot`  
_L236-255_
- inherits: `FGlobalHeapCensusRoot`
- desc: A unique set string pool.
- L241 _private prototype_ `VUniqueStringSetInternPool() = default;` — Private constructor since there should only ever be one global instance of this. There's no virtual destructor since `TLazyInitialized` is never destroyed and this is meant to be a global unique string set pool.
- L244 _private prototype_ `AUTORTFM_DISABLE VUniqueStringSet& Intern(FAllocationContext Context, const TSet<VUniqueString*>& InSet);` — Retrieves an existing string set from the set pool if it exists or creates a new one and returns it.
- L247 _private prototype_ `virtual void ConductCensus() override;` — This gives the pool the ability to conduct census on its own to clear references to the sets.
- L249 _private member_ `TWeakBarrierSet<VUniqueStringSet, FHashableUniqueStringSetKeyFuncs> Sets;`
- L251 _private member_ `static UE::FMutex Mutex;`

#### Free symbols / members of external scopes

- L18 _namespace_ `namespace Verse`
- L124 _function_ `inline uint32 GetTypeHash(const VUniqueString& String)` (scope `Verse`) — Allows for `VUniqueString` to be used with Unreal hashtable containers like `TMap`/`TSet`.
- L189 _prototype_ `uint32 GetSetVUniqueStringTypeHash(const TSet<VUniqueString*>& Set);` (scope `Verse`)
- L190 _prototype_ `uint32 GetTypeHash(const VUniqueStringSet& Set);` (scope `Verse`)
- L208 _member_ `const VUniqueStringSet* Cell;` (scope `Verse::FHashableUniqueStringSetKey::__anon97322d6f010a`)
- L209 _member_ `const TSet<VUniqueString*>* Set;` (scope `Verse::FHashableUniqueStringSetKey::__anon97322d6f010a`)

### `Source/Runtime/CoreUObject/Public/VerseVM/VVMUnreachable.h` (Public)


#### Free symbols / members of external scopes

- L8 _macro_ `#define VERSE_UNREACHABLE() \`

### `Source/Runtime/CoreUObject/Public/VerseVM/VVMValue.h` (Public)


#### enum `Verse::ECompares`  
`enum class ECompares : uint8`  
_L44-50_
- L46 _public enumerator_ `Neq`
- L47 _public enumerator_ `Eq`
- L48 _public enumerator_ `Undecidable`
- L49 _public enumerator_ `RuntimeError`

#### struct `Verse::VValue`  
`struct VValue`  
_L52-379_
- L55 _public member_ `static constexpr AutoRTFM::EReturnFromOpenMode AutoRTFMReturnFromOpenMode = AutoRTFM::EReturnFromOpenMode::CopyConstructInClosed;` — VValue can be returned from AutoRTFM::Open() via a copy-construction in the closed.
- L58 _public function_ `constexpr VValue() : EncodedBits(UninitializedValue)` — Default constructor: initializes to an uninitialized sentry value.
- L64 _public prototype_ `VValue(VCell& Cell);` — Untagged value coercion constructors.
- L66 _public prototype_ `VValue(UObject* Object);`
- L69 _public prototype_ `VValue(std::nullptr_t) = delete;` — Instead of using this constructor, consider `GlobalFalse()` instead.
- L71 _public function_ `static VValue FromInt32(int32 Int32)`
- L79 _public function_ `VValue(VFloat Float)`
- L87 _public prototype_ `static VValue FromBool(bool Value);`
- L89 _public function_ `static VValue EffectDoneMarker()`
- L94 _public function_ `static VValue CreateFieldMarker()`
- L100 _public function_ `constexpr VValue(const VValue& Copyee) : EncodedBits(Copyee.EncodedBits)` — Copy constructor/assignment operator
- L104 _public function_ `constexpr VValue& operator=(const VValue& Copyee)`
- L111 _public function_ `bool operator==(const VValue& Other) const` — Note: This isn't what you want if you want a deep equality check.
- L112 _public function_ `bool operator!=(const VValue& Other) const`
- L113 _public function_ `explicit operator bool() const`
- L118 _public prototype_ `template <typename HandlePlaceholderFunction> AUTORTFM_DISABLE static ECompares Equal(FAllocationContext Context, VValue Left, VValue Right, HandlePlaceholderFunction HandlePlaceholder);` — Note: This is what you want if you want a deep equality check. This will return true if left and/or right are placeholders.
- L121 _public prototype_ `AUTORTFM_DISABLE static VValue Melt(FAllocationContext Context, VValue Value);` — This may return a placeholder which is suspended upon as a FOpResult::Block result would be.
- L122 _public prototype_ `AUTORTFM_DISABLE static FOpResult Freeze(FAllocationContext Context, VValue Value, VTask* Task);`
- L124 _public function_ `static constexpr VValue Decode(uint64 EncodedBits)`
- L131 _public function_ `uint64 Encode() const`
- L136 _public prototype_ `VValue(VPlaceholder&) = delete;`
- L137 _public function_ `bool IsPlaceholder() const`
- L138 _public function_ `static VValue Placeholder(const VPlaceholder& Placeholder)`
- L145 _public prototype_ `VValue Follow() const;`
- L149 _public prototype_ `VPlaceholder& GetRootPlaceholder();` — This assumes we're a placeholder, does Follow(), and assumes we don't point (even transitively) to a concrete value. So we must be a placeholder and the placeholder we point at (transitively) isn't resolved.
- L150 _public function_ `VPlaceholder& AsPlaceholder() const`
- L156 _public function_ `VRef* ExtractTransparentRef() const`
- L165 _public function_ `static VValue TransparentRef(VRef& Ref)`
- L170 _public function_ `bool IsInt32() const`
- L171 _public prototype_ `bool IsUint32() const;`
- L172 _public prototype_ `uint32 AsUint32() const;`
- L175 _public function_ `int32 AsInt32() const` — Returns Value as C++ style int32
- L181 _public function_ `bool IsCell() const`
- L182 _public function_ `VCell& AsCell() const`
- L188 _public function_ `VCell* ExtractCell() const`
- L206 _public prototype_ `template <typename ObjectType> bool IsCellOfType() const;`
- L209 _public prototype_ `template <typename ObjectType> ObjectType& StaticCast() const;`
- L212 _public prototype_ `template <typename ObjectType> ObjectType* DynamicCast() const;`
- L214 _public function_ `bool IsUObject() const`
- L215 _public function_ `UObject* AsUObject() const`
- L221 _public function_ `UObject* ExtractUObject() const`
- L233 _public prototype_ `bool IsInt() const;`
- L234 _public prototype_ `VInt AsInt() const;`
- L236 _public prototype_ `bool IsLogic() const;`
- L239 _public prototype_ `bool AsBool() const;` — Returns Value as C++ style bool
- L241 _public function_ `bool IsFloat() const`
- L245 _public function_ `VFloat AsFloat() const`
- L251 _public prototype_ `bool IsEnumerator() const;`
- L253 _public function_ `bool IsUninitialized() const`
- L255 _public function_ `uint64 GetEncodedBits() const`
- L257 _public prototype_ `void EnqueueSuspension(FAccessContext Context, VSuspension& Suspension);`
- L259 _public prototype_ `AUTORTFM_DISABLE void AppendToString(FAllocationContext Context, FUtf8StringBuilderBase& Builder, EValueStringFormat Format, TSet<const void*>& VisitedObjects, uint32 RecursionDepth = 0) const;`
- L260 _public prototype_ `FUtf8String ToString(FAllocationContext Context, EValueStringFormat Format, uint32 RecursionDepth = 0) const;`
- L261 _public prototype_ `AUTORTFM_DISABLE TSharedPtr<FJsonValue> ToJSON(FRunningContext, EValueJSONFormat, TMap<const void*, EVisitState>& VisitedObjects, FToJsonCallback, uint32 RecursionDepth = 0, FJsonObject* Defs = nullptr);`
- L262 _public prototype_ `AUTORTFM_DISABLE VValue FromJSON(FRunningContext, const FJsonValue&, EValueJSONFormat, FFromJsonCallback);`
- L264 _public function_ `static VValue Char(uint8 V)`
- L270 _public function_ `static VValue Char32(uint32 V)`
- L277 _public function_ `bool IsChar() const`
- L278 _public function_ `bool IsChar32() const`
- L280 _public function_ `UTF8CHAR AsChar() const`
- L285 _public function_ `UTF32CHAR AsChar32() const`
- L306 _private function_ `static constexpr VValue Root(uint16 SplitDepth)`
- L312 _private function_ `bool IsRoot() const`
- L314 _private function_ `uint16 GetSplitDepth() const`
- L360 _public member_ `static constexpr uint64 UninitializedValue = 0;` — Special code which means this VValue is uninitialized
- L363 _public member_ `static constexpr uint64 NumberTagMask = 0xffff'0000'0000'0000ull;` — Number-related constants
- L364 _public member_ `static constexpr uint64 Int32Tag = 0xffff'0000'0000'0000ull;`
- L365 _public member_ `static constexpr uint64 FloatOffset = 0x0001'0000'0000'0000ull;`
- L366 _public member_ `static constexpr uint64 MaxPureNaN = 0xfffb'ffff'ffff'ffffull;`
- L367 _public member_ `static constexpr uint64 MaxFloatTag = 0xfffc'0000'0000'0000ull;`
- L370 _public member_ `static constexpr uint64 NumLowerEncodingBits = 4;` — Non-number related constants
- L371 _public member_ `static constexpr uint64 NonCellTagMask = NumberTagMask | 0xfull;` — Used for Placeholder, Root
- L372 _public member_ `static constexpr uint64 UObjectTagMask = NumberTagMask | 0x7ull;` — Used for UObject
- L373 _public member_ `static constexpr uint64 PlaceholderTag = 0x1ull;`
- L374 _public member_ `static constexpr uint64 RootTag = 0x2ull;`
- L375 _public member_ `static constexpr uint64 UObjectTag = 0x3ull;`
- L376 _public member_ `static constexpr uint64 CharTag = 0x4ull;`
- L377 _public member_ `static constexpr uint64 Char32Tag = 0x5ull;`
- L378 _public member_ `static constexpr uint64 TransparentRefTag = 06ull;`

#### union `Verse::VValue::(anonymous)`  
``  
_L295-304_

#### struct `Verse::VValue::__anonb908315e010a::(anonymous)`  
``  
_L300-303_

#### Free symbols / members of external scopes

- L24 _namespace_ `namespace Verse`
- L296 _member_ `uint64 EncodedBits;` (scope `Verse::VValue::__anonb908315e010a`)
- L297 _member_ `VCell* Cell;` (scope `Verse::VValue::__anonb908315e010a`)
- L301 _member_ `int32 Payload;` (scope `Verse::VValue::__anonb908315e010a::__anonb908315e0208`)
- L302 _member_ `int32 Tag;` (scope `Verse::VValue::__anonb908315e010a::__anonb908315e0208`)
- L303 _member_ `} Bits;` (scope `Verse::VValue::__anonb908315e010a`)

### `Source/Runtime/CoreUObject/Public/VerseVM/VVMValueObject.h` (Public)


#### struct `Verse::VValueObject`  
`struct VValueObject : VObject`  
_L16-44_
- inherits: `VObject`
- desc: Specialization of VObject that stores only VValues
- L19 _public member_ `static TGlobalTrivialEmergentTypePtr<&StaticCppClassInfo> GlobalTrivialEmergentType;`
- L22 _public prototype_ `AUTORTFM_DISABLE static VValueObject& NewUninitialized(FAllocationContext Context, VEmergentType& InEmergentType);` — Allocate a new object with the given shape, populated with placeholders
- L24 _public prototype_ `bool CreateFieldCached(FAllocationContext Context, FCreateFieldCacheCase Cache);`
- L25 _public prototype_ `AUTORTFM_DISABLE bool CreateField(FAllocationContext Context, VUniqueString& Name, FCreateFieldCacheCase* OutCacheCase = nullptr);`
- L30 _protected prototype_ `AUTORTFM_DISABLE static std::byte* AllocateCell(FAllocationContext Context, VCppClassInfo& CppClassInfo, uint64 NumIndexedFields);`
- L32 _protected prototype_ `AUTORTFM_DISABLE VValueObject(FAllocationContext Context, VEmergentType& InEmergentType);`
- L34 _protected prototype_ `AUTORTFM_DISABLE ECompares EqualImpl(FAllocationContext Context, VCell* Other, const TFunction<void(::Verse::VValue, ::Verse::VValue)>& HandlePlaceholder);`
- L35 _protected prototype_ `uint32 GetTypeHashImpl();`
- L36 _protected prototype_ `AUTORTFM_DISABLE VValue MeltImpl(FAllocationContext Context);`
- L37 _protected prototype_ `AUTORTFM_DISABLE FOpResult FreezeImpl(FAllocationContext Context, VTask* Task);`
- L38 _protected prototype_ `AUTORTFM_DISABLE static void SerializeLayout(FAllocationContext Context, VValueObject*& This, FStructuredArchiveVisitor& Visitor);`
- L39 _protected prototype_ `AUTORTFM_DISABLE void SerializeImpl(FAllocationContext Context, FStructuredArchiveVisitor& Visitor);`
- L43 _protected member_ `static constexpr bool InstancedCell = true;` — This is subtle: structs are instanced by both InstanceSubobjects and StaticDuplicateObject, but classes are ignored by InstanceSubobjects as they do not have an Outer to be filtered by.
- L46 _function_ `inline std::byte* VValueObject::AllocateCell(FAllocationContext Context, VCppClassInfo& CppClassInfo, uint64 NumIndexedFields)`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace Verse`

### `Source/Runtime/CoreUObject/Public/VerseVM/VVMValuePrinting.h` (Public)


#### enum `Verse::EValueStringFormat`  
`enum class EValueStringFormat`  
_L16-22_
- L18 _public enumerator_ `VerseSyntax` — Verse syntax
- L19 _public enumerator_ `Diagnostic` — For Verse's ToDiagnostic function
- L20 _public enumerator_ `Cells` — Low-level VM cell information
- L21 _public enumerator_ `CellsWithAddresses` — Low-level VM cell information with addresses (non-deterministic).

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace Verse`
- L24 _function_ `constexpr bool IsCellFormat(EValueStringFormat Format)` (scope `Verse`)
- L29 _prototype_ `FUtf8String ToString(VCell* Cell, FAllocationContext Context, EValueStringFormat Format, uint32 RecursionDepth = 0);` (scope `Verse`)
- L30 _prototype_ `FUtf8String ToString(VValue Value, FAllocationContext Context, EValueStringFormat Format, uint32 RecursionDepth = 0);` (scope `Verse`)

### `Source/Runtime/CoreUObject/Public/VerseVM/VVMVerse.h` (Public)


#### class `Verse::VerseVM`  
`class VerseVM`  
_L11-21_
- L15 _public prototype_ `static void Startup();`
- L16 _public prototype_ `static void Shutdown();`
- L18 _public prototype_ `static IEngineEnvironment* GetEngineEnvironment();`
- L19 _public prototype_ `static void SetEngineEnvironment(IEngineEnvironment* Environment);`
- L20 _public prototype_ `static bool IsUHTGeneratedVerseVNIObject(UObject* Object);`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace Verse`
- L26 _macro_ `#define V_FORCEINLINE inline`
- L28 _macro_ `#define V_FORCEINLINE inline __attribute__((always_inline))`
- L30 _macro_ `#define V_FORCEINLINE __forceinline`
- L34 _macro_ `#define V_INLINE_UNLESS_DEBUG_BUILD`
- L36 _macro_ `#define V_INLINE_UNLESS_DEBUG_BUILD [[clang::noinline]]`
- L38 _macro_ `#define V_INLINE_UNLESS_DEBUG_BUILD [[clang::always_inline]]`
- L42 _macro_ `#define V_AUTORTFM_OPEN AUTORTFM_OPEN`
- L44 _macro_ `#define V_AUTORTFM_OPEN`
- L48 _macro_ `#define V_PRESERVE_NONE`
- L50 _macro_ `#define V_PRESERVE_NONE __attribute__((preserve_none))`
- L53 _variable_ `const FName InternalCodegenAssetRegistryTagName("Ver` (scope `Verse`)

### `Source/Runtime/CoreUObject/Public/VerseVM/VVMVerseClass.h` (Public)


#### struct `FVersePersistentVar`  
`struct FVersePersistentVar`  
_L39-61_
- reflection: `USTRUCT()`
- L43 _public function_ `FVersePersistentVar(FString Path, FString RelativePath, Verse::EPersistenceExternalAccess ExternalAccess, TFieldPath<FMapProperty> Property) : Path(::MoveTemp(Path)) , RelativePath(::MoveTemp(RelativePath)) , ExternalAccess(ExternalAccess) , Property(::MoveTemp(Property))`
- L51 _public prototype_ `FVersePersistentVar() = default;`
- L54 _public member_ `FString Path;` — `UPROPERTY()`
- L56 _public member_ `FString RelativePath;` — `UPROPERTY()`
- L58 _public member_ `Verse::EPersistenceExternalAccess ExternalAccess{Verse::EPersistenceExternalAccess::Internal};` — `UPROPERTY()`
- L60 _public member_ `TFieldPath<FMapProperty> Property;` — `UPROPERTY()`

#### struct `FVerseSessionVar`  
`struct FVerseSessionVar`  
_L64-77_
- reflection: `USTRUCT()`
- L68 _public function_ `explicit FVerseSessionVar(TFieldPath<FMapProperty> Property) : Property(::MoveTemp(Property))`
- L73 _public prototype_ `FVerseSessionVar() = default;`
- L76 _public member_ `TFieldPath<FMapProperty> Property;` — `UPROPERTY()`

#### struct `FVerseClassVarAccessor`  
`struct FVerseClassVarAccessor`  
_L80-92_
- reflection: `USTRUCT()`
- L85 _public member_ `TObjectPtr<UFunction> Func{};` — `UPROPERTY()`
- L88 _public member_ `bool bIsInstanceMember{false};` — `UPROPERTY()`
- L91 _public member_ `bool bIsFallible{false};` — `UPROPERTY()`

#### struct `FVerseClassVarAccessors`  
`struct FVerseClassVarAccessors`  
_L95-104_
- reflection: `USTRUCT()`
- L100 _public member_ `TMap<int, FVerseClassVarAccessor> Getters;` — `UPROPERTY()`
- L103 _public member_ `TMap<int, FVerseClassVarAccessor> Setters;` — `UPROPERTY()`

#### struct `FVerseFunctionDescriptor`  
`struct FVerseFunctionDescriptor`  
_L106-123_
- L108 _public member_ `UFunction* Function = nullptr;` — May be nullptr even when valid
- L109 _public member_ `FName DisplayName = NAME_None;`
- L110 _public member_ `FName UEName = NAME_None;`
- L112 _public prototype_ `FVerseFunctionDescriptor() = default;`
- L114 _public function_ `FVerseFunctionDescriptor( UFunction* InFunction, FName InDisplayName, FName InUEName) : Function(InFunction) , DisplayName(InDisplayName) , UEName(InUEName)`

#### struct `FVerseCallableThunk`  
`struct FVerseCallableThunk`  
_L127-131_
- L129 _public member_ `const char* NameUTF8;`
- L130 _public member_ `Verse::VNativeProcedure::FThunkFn Pointer;`

#### class `UVerseClass`  
`class UVerseClass : public UClass`  
_L135-637_
- reflection: `UCLASS(MinimalAPI, within = Package, Config = Engine)`
- inherits: `UClass`
- L140 _public prototype_ `UVerseClass() = default;`
- L141 _public prototype_ `explicit UVerseClass( EStaticConstructor, FName InName, uint32 InSize, uint32 InAlignment, EClassFlags InClassFlags, EClassCastFlags InClassCastFlags, const TCHAR* InClassConfigName, EObjectFlags InFlags, ClassConstructorType InClassConstructor, ClassVTableHelperCtorCallerType InClassVTableHelperCtorCaller, FUObjectCppClassStaticFunctions&& InCppClassStaticFunctions);`
- L153 _public prototype_ `explicit UVerseClass(const FObjectInitializer& ObjectInitializer);`
- L156 _public function_ `consteval UVerseClass( UE::CodeGen::ConstInit::FObjectParams ObjectParams, UE::CodeGen::ConstInit::FUFieldParams UFieldParams, UE::CodeGen::ConstInit::FStructParams StructParams, UE::CodeGen::ConstInit::FClassParams ClassParams, UE::CodeGen::ConstInit::FVerseClassParams InVerseParams) : Super(ObjectParams, UFieldParams, StructParams, ClassParams) , CompiledInMangledPackageVersePath(InVerseParams.MangledPackageVersePath) , SolClassFlags(VCLASS_UHTNative | InVerseParams.VerseClassFlags) , TaskClasses(ConstEval) , PersistentVars(ConstEval) , SessionVars(ConstEval) , VarAccessors(ConstEval) , CompiledInPackageRelativeVersePath(InVerseParams.PackageRelativeVersePath) , PackageRelativeVersePath(ConstEval) , DisplayNameToUENameFunctionMap(ConstEval) , DirectInterfaces(ConstEval) , PropertiesWrittenByInitCDO(ConstEval) , FunctionMangledNames(ConstEval) , PredictsFunctionNames(ConstEval) , PredictsVarNames(ConstEval) , PredictsCoercedFunctions(ConstEval) , PropertyMetadata(ConstEval) #if WITH_VERSE_COMPILER && WITH_EDITORONLY_DATA , PreviousPathName(ConstEval) #endif`
- L192 _public prototype_ `virtual UE::Core::FVersePath GetVersePath() const override;`
- L196 _public prototype_ `UE_INTERNAL void TrackDefaultInitializedProperties(void* DefaultData) const;`
- L199 _public prototype_ `AUTORTFM_DISABLE static void TrackDefaultInitializedPropertiesOfGlobalField( Verse::FAllocationContext Context, UObject* Module, Verse::VValue Value);`
- L208 _private prototype_ `virtual bool IsAsset() const override;`
- L209 _private prototype_ `virtual void GetPreloadDependencies(TArray<UObject*>& OutDeps) override;`
- L210 _private prototype_ `virtual void GetAssetRegistryTags(FAssetRegistryTagsContext Context) const override;`
- L211 _private prototype_ `virtual void PreSave(FObjectPreSaveContext ObjectSaveContext) override;`
- L213 _private prototype_ `virtual void GetAssetRegistryTagMetadata(TMap<FName, FAssetRegistryTagMetadata>& OutMetadata) const override;`
- L218 _private prototype_ `AUTORTFM_DISABLE virtual void Link(FArchive& Ar, bool bRelinkExistingProperties) override;`
- L219 _private prototype_ `virtual void PreloadChildren(FArchive& Ar) override;`
- L220 _private prototype_ `virtual FString GetAuthoredNameForField(const FField* Field) const override;`
- L221 _private prototype_ `UE_INTERNAL virtual EStructPropertyLinkFlags GetPropertyLinkFlags(UStruct* ContainerStruct, FProperty* Property) const override;`
- L225 _private prototype_ `virtual void PostInitInstance(UObject* InObj, FObjectInstancingGraph* InstanceGraph) override;`
- L226 _private prototype_ `virtual void PostLoadInstance(UObject* InObj) override;`
- L227 _private prototype_ `virtual void SetupObjectInitializer(FObjectInitializer& ObjectInitializer) const override;`
- L228 _private function_ `virtual bool CanCreateAssetOfClass() const override`
- L233 _private prototype_ `virtual bool CanCreateInstanceDataObject() const override;`
- L234 _private prototype_ `virtual void SerializeDefaultObject(UObject* Object, FStructuredArchive::FSlot Slot) override;`
- L237 _private prototype_ `virtual FTopLevelAssetPath GetReinstancedClassPathName_Impl() const;`
- L242 _private prototype_ `virtual const TCHAR* GetPrefixCPP() const override;` — UField interface.
- L248 _public member_ `const UTF8CHAR* CompiledInMangledPackageVersePath = nullptr;` — CONSTINIT_UOBJECT_TODO: Size increase
- L252 _public member_ `uint32 SolClassFlags = VCLASS_None;` — `UPROPERTY()`
- L256 _public member_ `TArray<TObjectPtr<UVerseClass>> TaskClasses;` — `UPROPERTY()` — All coroutine task classes belonging to this class (one for each coroutine in this class)
- L260 _public member_ `TObjectPtr<UFunction> InitInstanceFunction;` — `UPROPERTY()` — Initialization function
- L263 _public member_ `TArray<FVersePersistentVar> PersistentVars;` — `UPROPERTY()`
- L266 _public member_ `TArray<FVerseSessionVar> SessionVars;` — `UPROPERTY()`
- L269 _public member_ `TMap<FName, FVerseClassVarAccessors> VarAccessors;` — `UPROPERTY()`
- L272 _public member_ `EVerseEffectSet ConstructorEffects = EVerseEffectSet::None;` — `UPROPERTY()`
- L275 _public member_ `FName MangledPackageVersePath;` — `UPROPERTY()` — Storing as FName since it's shared between classes
- L279 _public member_ `const UTF8CHAR* CompiledInPackageRelativeVersePath = nullptr;` — CONSTINIT_UOBJECT_TODO: Size increase
- L283 _public member_ `FString PackageRelativeVersePath;` — `UPROPERTY()`
- L287 _public member_ `TMap<FName, FName> DisplayNameToUENameFunctionMap;` — `UPROPERTY()`
- L291 _public member_ `TArray<TObjectPtr<UVerseClass>> DirectInterfaces;` — `UPROPERTY()` — All interface class types that this class implements
- L294 _public member_ `TArray<TFieldPath<FProperty>> PropertiesWrittenByInitCDO;` — `UPROPERTY()`
- L302 _public member_ `TMap<FName, FName> FunctionMangledNames;` — `UPROPERTY()` — Store a mapping from all previous function mangled names used by the code generator to the current version of name mangling.  Store NAME_None if there are multiple possible current versions for any previous version.  If a previous function mangled name matches the current mangled name, nothing is stored.
- L305 _public member_ `TArray<FName> PredictsFunctionNames;` — `UPROPERTY()`
- L308 _public member_ `TMap<FAnsiString, FName> PredictsVarNames;` — `UPROPERTY()`
- L311 _public member_ `TMap<FName, FName> PredictsCoercedFunctions;` — `UPROPERTY()`
- L314 _public member_ `TMap<TFieldPath<FProperty>, FVersePropertyMetadata> PropertyMetadata;` — `UPROPERTY()`
- L317 _public member_ `TMap<TFieldPath<FProperty>, TFieldPath<FProperty>> VerseFields;` — `UPROPERTY()`
- L321 _public member_ `FString PreviousPathName;` — Path name this class had before it was marked as DEAD
- L324 _public member_ `static const FName NativeParentClassTagName;`
- L325 _public member_ `static const FName PackageVersePathTagName;`
- L326 _public member_ `static const FName PackageRelativeVersePathTagName;`
- L329 _public member_ `static const FName InitCDOFunctionName;` — Name of the CDO init function
- L330 _public member_ `static const FName StructPaddingDummyName;`
- L333 _public member_ `static const FTopLevelAssetPath VerseClassTopLevelAssetPath;` — This is the asset path that all `UVerseClass` get when generated (we use it to identify assets as Verse classes)
- L337 _public member_ `Verse::TWriteBarrier<Verse::VClass> Class;` — `UPROPERTY()`
- L340 _public member_ `Verse::VRestValue Shape{0};` — The VShape representing this class's layout. This is a placeholder before linking.
- L342 _public prototype_ `void SetShape(Verse::FAllocationContext Context, Verse::VShape* InShape);`
- L344 _public prototype_ `static Verse::VClass* GetVerseClass(Verse::FAllocationContext Context, UClass* Class);`
- L347 _public prototype_ `static Verse::VShape* GetShape(Verse::FAllocationContext Context, UClass* Class);` — Locate a shape for Class, which may be a UVerseClass or some other kind of imported UClass.
- L349 _public prototype_ `static Verse::VShape& GetShapeForLoadField(Verse::FAllocationContext Context, UClass* Class);` — Locate a shape for Class or a superclass. Useful when loading from prefabs that were not reflected to Verse.
- L351 _public prototype_ `static Verse::FOpResult LoadField(Verse::FAllocationContext Context, UObject* Object, Verse::VUniqueString& FieldName, Verse::VValue Self = Verse::VValue());`
- L352 _public prototype_ `AUTORTFM_DISABLE static Verse::FOpResult LoadField(Verse::FAllocationContext Context, UObject* Object, const Verse::VShape::VEntry* Field, Verse::VValue Self = Verse::VValue());`
- L354 _public prototype_ `AUTORTFM_DISABLE static void VisitMembers(Verse::FAllocationContext, UObject* Object, Verse::FDebuggerVisitor& Visitor);`
- L356 _public prototype_ `static void AddReferencedObjects(UObject* InThis, FReferenceCollector& Collector);`
- L363 _public prototype_ `static void RenameDefaultSubobjects(UObject* InObject);` — Renames default sub-objects on a CDO so that they're unique (named after properties they are assigned to) @param  InObject Object (usually a CDO) whose default sub-objects are to be renamed
- L370 _public prototype_ `void PrePopulateVerseFields(UObject* CDO);` — Pre-populates verse fields on a CDO by reading properties tagged with the @field attribute and inserting their values into the corresponding array properties on the CDO. @param  CDO   The class default object to populate
- L376 _public prototype_ `AUTORTFM_DISABLE static void RenameSubobjectsOfGlobalField( Verse::FAllocationContext Context, UObject* Module, const FString& GlobalFieldName, Verse::VValue Value);` — used to rename "subobjects" of module-scope globals so that the serialization system across the server/cooker/editor refers to these objects using consistent names. (this is the module-scope vvm analogue of RenameDefaultSubobjects.)
- L388 _public prototype_ `static bool ValidateSubobjectArchetypes(UObject* InObject, UObject* InArchetype);` — Checks that the sub-objects of a given Verse object are using the correct sub-archetype. @param  InObject Object whose default sub-objects we are validating @param  InArchetype The archetype of InObject
- L390 _public function_ `void SetNeedsSubobjectInstancingForLoadedInstances(bool bNeedsInstancing)`
- L396 _public prototype_ `void EnableDynamicInstancedReferenceSupport();` — Allows dynamic instanced reference support to be toggled on/off for this class.
- L397 _public prototype_ `void DisableDynamicInstancedReferenceSupport();`
- L399 _public function_ `bool IsNativeBound() const`
- L400 _public function_ `bool IsUniversallyAccessible() const`
- L401 _public function_ `bool IsConcrete() const`
- L402 _public function_ `bool IsVerseModule() const`
- L403 _public function_ `bool IsUHTNative() const`
- L404 _public function_ `bool IsEpicInternal() const`
- L405 _public function_ `bool HasInstancedSemantics() const`
- L406 _public function_ `bool HasTransientSubobjects() const`
- L407 _public function_ `bool IsFinalSuper() const`
- L408 _public function_ `bool IsExplicitlyCastable() const`
- L409 _public function_ `bool IsConstructorEpicInternal() const`
- L410 _public function_ `bool IsPersistable() const`
- L411 _public function_ `bool IsParametric() const`
- L412 _public function_ `bool IsPersonaConstructible() const`
- L413 _public function_ `bool IsErrIncomplete() const`
- L415 _public function_ `void SetNativeBound()`
- L416 _public function_ `void SetHasTransientSubobjects()`
- L425 _public function_ `template <typename TFunc> bool ForEachClassInHierarchy(TFunc&& Func, EFieldIterationFlags Flags = EFieldIterationFlags::IncludeAll) const` — Walks the full UVerseClass hierarchy: this class, its super classes, and all DirectInterfaces (recursively). @param Func Callback invoked for each UVerseClass in the hierarchy. Return true to continue, false to stop. @param Flags Controls which axes to walk. Defaults to IncludeAll (supers + interfaces). @return true if the full walk completed, false if the callback stopped it early.
- L457 _public function_ `const FName* FindPredictsVarPropertyName(const FAnsiString& VarName) const`
- L467 _public function_ `const FVerseClassVarAccessors* FindAccessors(FName VarName) const`
- L477 _public function_ `bool CanMemberFunctionBeCalledFromPredicts(FName FuncName)`
- L487 _public prototype_ `bool CanMemberFunctionBeCalledFromGameplaySystems(FName FuncName);`
- L494 _public prototype_ `void ForEachVerseFunction(TFunctionRef<bool(FVerseFunctionDescriptor)> Operation, EFieldIterationFlags IterationFlags = EFieldIterationFlags::None);` — Iterates over Verse Function Properties on the current Verse class and executes a callback with VerseFunction value and its Verse name. @param Operation callback for each of the found Verse Functions. When the callback returns false, iteration is stopped. @param IterationFlags Additional options used when iterating over Verse Function properties
- L496 _public function_ `FName GetFunctionMangledName(FName MangledName)`
- L505 _public function_ `FName* FindFunctionMangledName(FName MangledName)`
- L518 _public function_ `FName* FindInterfaceFunctionMangledName(FName MangledName)`
- L536 _public function_ `FName* FindClassFunctionMangledName(FName MangledName)`
- L549 _public function_ `void AddFunctionMangledNames(FName OldMangledName, FName NewMangledName)`
- L575 _public prototype_ `FVerseFunctionDescriptor FindVerseFunctionByDisplayName(UObject* Object, const FString& DisplayName, EFieldIterationFlags SearchFlags = EFieldIterationFlags::None);`
- L576 _public prototype_ `FVerseFunctionDescriptor FindVerseFunctionByDisplayName(const FString& DisplayName, EFieldIterationFlags SearchFlags = EFieldIterationFlags::None);`
- L582 _public prototype_ `static int32 GetVerseFunctionParameterCount(UFunction* Func);` — Returns the number of parameters a verse function takes
- L595 _public prototype_ `FStaleClassInfo ResetUHTNative();` — Reset the contents of the UHT class and return the reset information so it can be restored if the compiled failed. Being able to restore will probably not be needed once BPVM is removed
- L598 _public prototype_ `void StripVerseGeneratedFunctions(TArray<TKeyValuePair<FName, TObjectPtr<UField>>>* StrippedFields);` — Strip verse generated functions from the function list and place into the output container for later restoring
- L601 _public prototype_ `void BindVerseFunction(const char* DecoratedFunctionName, FNativeFuncPtr NativeThunkPtr);`
- L602 _public prototype_ `void BindVerseCoroClass(const char* DecoratedFunctionName, FNativeFuncPtr NativeThunkPtr);`
- L607 _public prototype_ `void SetVerseCallableThunks(const FVerseCallableThunk* InThunks, uint32 NumThunks);` — Set a table of thunks for native functions callable from Verse. Parameter should be a static array as it will not be copied.
- L608 _public prototype_ `void BindVerseCallableFunctions(Verse::VPackage* VersePackage, FUtf8StringView VerseScopePath);`
- L611 _public function_ `const FVniTypeDesc* GetNativeTypeDesc()`
- L615 _public function_ `void SetNativeTypeDesc(const FVniTypeDesc* InNativeTypeDesc)`
- L618 _private prototype_ `void CallInitInstanceFunctions(UObject* InObj, FObjectInstancingGraph* InstanceGraph);`
- L619 _private prototype_ `void CallPropertyInitInstanceFunctions(UObject* InObj, FObjectInstancingGraph* InstanceGraph);`
- L622 _private prototype_ `void AddPersistentVars(UObject*);`
- L625 _private prototype_ `void AddSessionVars(UObject*);`
- L629 _private member_ `TObjectPtr<UClassCookedMetaData> CachedCookedMetaDataPtr;` — `UPROPERTY()`
- L633 _private member_ `TConstArrayView<FVerseCallableThunk> VerseCallableThunks;`
- L636 _private member_ `const FVniTypeDesc* NativeTypeDesc{nullptr};`

#### struct `UVerseClass::FStaleClassInfo`  
`struct FStaleClassInfo`  
_L584-591_
- L586 _public member_ `TObjectPtr<UVerseClass> SourceClass;`
- L587 _public member_ `TMap<FName, FName> DisplayNameToUENameFunctionMap;`
- L588 _public member_ `TMap<FName, FName> FunctionMangledNames;`
- L589 _public member_ `TArray<TObjectPtr<UVerseClass>> TaskClasses;`
- L590 _public member_ `TArray<TKeyValuePair<FName, TObjectPtr<UField>>> Children;`

#### Free symbols / members of external scopes

- L32 _namespace_ `namespace Verse`
- L460 _function_ `ForEachClassInHierarchy([&Result, &VarName](const UVerseClass* Class) { Result = Class->PredictsVarNames.Find(VarName); return Result == nullptr; });` (scope `UVerseClass::FindPredictsVarPropertyName`)
- L470 _function_ `ForEachClassInHierarchy([&Result, &VarName](const UVerseClass* Class) { Result = Class->VarAccessors.Find(VarName); return Result == nullptr; });` (scope `UVerseClass::FindAccessors`)
- L480 _function_ `ForEachClassInHierarchy([&bFound, &FuncName](const UVerseClass* Class) { bFound = Class->PredictsFunctionNames.Contains(FuncName); return !bFound; });` (scope `UVerseClass::CanMemberFunctionBeCalledFromPredicts`)
- L639 _namespace_ `namespace Verse`
- L641 _prototype_ `bool IsInternalCodegenAsset(const UObject& Object);` (scope `Verse`)

### `Source/Runtime/CoreUObject/Public/VerseVM/VVMVerseClassFlags.h` (Public)


#### enum `EVerseClassFlags`  
`enum EVerseClassFlags`  
_L6-35_
- desc: NOTE: Keep these flags in sync with EVerseClassFlags in UnrealEngineTypes.cs
- L8 _public enumerator_ `VCLASS_None = 0x00000000u`
- L9 _public enumerator_ `VCLASS_NativeBound = 0x00000001u`
- L10 _public enumerator_ `VCLASS_UniversallyAccessible = 0x00000002u` — The class is accessible from any Verse path, and is in a package with a public scope.
- L11 _public enumerator_ `VCLASS_Concrete = 0x00000004u` — The class can be instantiated without explicitly setting any properties
- L12 _public enumerator_ `VCLASS_Module = 0x00000008u` — This class represents a Verse module
- L13 _public enumerator_ `VCLASS_UHTNative = 0x00000010u` — This class was created by UHT
- L14 _public enumerator_ `VCLASS_Tuple = 0x00000020u` — This class represents a tuple
- L15 _public enumerator_ `VCLASS_EpicInternal = 0x00000040u` — This class is epic_internal
- L16 _public enumerator_ `VCLASS_HasInstancedSemantics = 0x00000080u` — This class is using explicit instanced reference semantics (backcompat)
- L17 _public enumerator_ `VCLASS_FinalSuper = 0x00000100u` — This class has a <final_super> attribute
- L18 _public enumerator_ `VCLASS_Castable = 0x00000200u` — This class has a <castable> attribute
- L19 _public enumerator_ `VCLASS_EpicInternalConstructor = 0x00000400u` — This class's constructor is epic_internal
- L20 _public enumerator_ `VCLASS_Persistable = 0x00000800u` — This class has a <persistable> attribute
- L21 _public enumerator_ `VCLASS_Parametric = 0x00001000u` — This class definition is local to a function, i.e. is parametric
- L22 _public enumerator_ `VCLASS_InternalCodegen = 0x00002000u` — This class is generated by the compiler for internal purposes and not represent any user-defined class.
- L23 _public enumerator_ `VCLASS_PersonaConstructible = 0x00004000u` — This class may be constructed by Persona
- L24 _public enumerator_ `VCLASS_HasVar = 0x00008000u` — This class has at least one mutable variable.  (Not needed in new VM)
- L25 _public enumerator_ `VCLASS_InheritsFromBlueprint = 0x00010000u` — This class has a blueprint class as (transitive) superclass
- L26 _public enumerator_ `VCLASS_HasTransientSubobjects = 0x00020000u` — This class has a non-serialized reference to an archetype instantiation
- L27 _public enumerator_ `VCLASS_HasFieldAttribute = 0x00040000u` — This class or a superclass uses the @field attribute
- L30 _public enumerator_ `VCLASS_Err_Inoperable = 0x40000000u` — @TODO: this should be a per-function flag; a class flag is not granular enough
- L32 _public enumerator_ `VCLASS_Err_Incomplete = 0x80000000u` — The class layout is malformed (missing super, illformed data-member, etc.)
- L34 _public enumerator_ `VCLASS_Err = (VCLASS_Err_Incomplete | VCLASS_Err_Inoperable)`

### `Source/Runtime/CoreUObject/Public/VerseVM/VVMVerseConstraints.h` (Public)


#### struct `FVerseIntConstraints`  
`struct FVerseIntConstraints`  
_L8-17_
- reflection: `USTRUCT()`
- L13 _public member_ `TOptional<int64> ClampMin;` — `UPROPERTY()`
- L16 _public member_ `TOptional<int64> ClampMax;` — `UPROPERTY()`

#### struct `FVerseDoubleConstraints`  
`struct FVerseDoubleConstraints`  
_L20-30_
- reflection: `USTRUCT()`
- L26 _public member_ `double ClampMin = -INFINITY;` — `UPROPERTY()` — See CFloatType::IsIntrinsicFloatType
- L29 _public member_ `double ClampMax = NAN;` — `UPROPERTY()`

### `Source/Runtime/CoreUObject/Public/VerseVM/VVMVerseEffectSet.h` (Public)


#### enum `EVerseEffectSet`  
`enum class EVerseEffectSet : uint8`  
_L15-25_
- reflection: `UENUM(Flags)`
- desc: Mirrors uLang::SEffectSet for UE serialization
- L17 _public enumerator_ `None = 0`
- L18 _public enumerator_ `Suspends = 1 << 0`
- L19 _public enumerator_ `Decides = 1 << 1`
- L20 _public enumerator_ `Diverges = 1 << 2`
- L21 _public enumerator_ `Reads = 1 << 3`
- L22 _public enumerator_ `Writes = 1 << 4`
- L23 _public enumerator_ `Allocates = 1 << 5`
- L24 _public enumerator_ `NoRollback = 1 << 6`

#### Free symbols / members of external scopes

- L26 _prototype_ `ENUM_CLASS_FLAGS(EVerseEffectSet);`

### `Source/Runtime/CoreUObject/Public/VerseVM/VVMVerseEnum.h` (Public)


#### enum `EVerseEnumFlags`  
`enum class EVerseEnumFlags : uint32`  
_L26-31_
- reflection: `UENUM(Flags)`
- L28 _public enumerator_ `None = 0x00000000u`
- L29 _public enumerator_ `NativeBound = 0x00000001u`
- L30 _public enumerator_ `UHTNative = 0x00000002u`

#### class `UVerseEnum`  
`class UVerseEnum : public UEnum`  
_L35-93_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UEnum`
- L39 _public prototype_ `UVerseEnum(const FObjectInitializer& ObjectInitialzer);`
- L42 _public function_ `consteval UVerseEnum( UE::CodeGen::ConstInit::FObjectParams ObjectParams, UE::CodeGen::ConstInit::FUFieldParams UFieldParams, UE::CodeGen::ConstInit::FEnumParams EnumParams, UE::CodeGen::ConstInit::FVerseEnumParams InEnumParams) : Super(ObjectParams, UFieldParams, EnumParams) , CompiledInQualifiedName(InEnumParams.QualifiedName) , VerseEnumFlags(EVerseEnumFlags::UHTNative) , QualifiedName(ConstEval) , NativeTypeDesc(InEnumParams.NativeTypeDesc)`
- L58 _public member_ `const UTF8CHAR* CompiledInQualifiedName = nullptr;` — CONSTINIT_UOBJECT_TODO: Size increase
- L62 _public member_ `EVerseEnumFlags VerseEnumFlags = EVerseEnumFlags::None;` — `UPROPERTY()`
- L65 _public member_ `FUtf8String QualifiedName;` — `UPROPERTY()`
- L68 _public prototype_ `virtual void Serialize(FArchive& Ar) override;` — UObject interface.
- L69 _public prototype_ `virtual void PreSave(FObjectPreSaveContext ObjectSaveContext) override;`
- L71 _public function_ `bool IsNativeBound() const`
- L72 _public function_ `bool IsUHTNative() const`
- L74 _public function_ `void SetNativeBound()`
- L77 _public member_ `Verse::TWriteBarrier<Verse::VEnumeration> Enumeration;`
- L80 _public function_ `const FVniTypeDesc* GetNativeTypeDesc()`
- L84 _public function_ `void SetNativeTypeDesc(const FVniTypeDesc* InNativeTypeDesc)`
- L89 _private member_ `TObjectPtr<UEnumCookedMetaData> CachedCookedMetaDataPtr;` — `UPROPERTY()`
- L92 _private member_ `const FVniTypeDesc* NativeTypeDesc{nullptr};`

#### enum `EVerseFalse`  
`enum class EVerseFalse : uint8`  
_L97-100_
- reflection: `UENUM()`
- desc: Corresponds to "false" in Verse, a type with no possible values.
- L99 _public enumerator_ `Value` — UHT doesn't correctly support empty enums, so we need a dummy case to make it compile.

#### enum `EVerseTrue`  
`enum class EVerseTrue : uint8`  
_L104-107_
- reflection: `UENUM()`
- desc: Corresponds to "true" in Verse, a type with one possible value: false.
- L106 _public enumerator_ `Value` — UHT errors if this is called "False".

#### Free symbols / members of external scopes

- L20 _namespace_ `namespace uLang`

### `Source/Runtime/CoreUObject/Public/VerseVM/VVMVerseFunction.h` (Public)


#### enum `EVerseFunctionFlags`  
`enum class EVerseFunctionFlags : uint32`  
_L19-25_
- reflection: `UENUM(Flags)`
- L21 _public enumerator_ `None = 0x00000000u`
- L22 _public enumerator_ `UHTNative = 0x00000001u`
- L23 _public enumerator_ `UHTTaskUpdate = 0x00000002u`
- L24 _public enumerator_ `AccessibleFromEngineGameplay = 0x00000004u`

#### class `UVerseFunction`  
`class UVerseFunction : public UFunction`  
_L30-98_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UFunction`
- desc: A UFunction wrapper for a VerseVM callee
- L35 _public prototype_ `explicit UVerseFunction(const FObjectInitializer& ObjectInitializer);`
- L36 _public prototype_ `explicit UVerseFunction(const FObjectInitializer& ObjectInitializer, UFunction* InSuperFunction, EFunctionFlags InFunctionFlags = FUNC_None, SIZE_T ParamsSize = 0);`
- L39 _public function_ `consteval UVerseFunction( UE::CodeGen::ConstInit::FObjectParams ObjectParams, UE::CodeGen::ConstInit::FUFieldParams UFieldParams, UE::CodeGen::ConstInit::FStructParams StructParams, UE::CodeGen::ConstInit::FFunctionParams FunctionParams, UE::CodeGen::ConstInit::FVerseFunctionParams InParams) : Super(ObjectParams, UFieldParams, StructParams, FunctionParams) , CompiledInAlternateNameUTF8(InParams.AlternateNameUTF8) , VerseFunctionFlags(EVerseFunctionFlags::UHTNative)`
- L63 _public member_ `EVerseFunctionFlags VerseFunctionFlags = EVerseFunctionFlags::None;`
- L65 _public function_ `bool IsUHTNative()`
- L70 _public function_ `bool IsAccessibleFromEngineGameplay() const`
- L75 _public function_ `static bool IsVerseGeneratedFunction(UField* Field)`
- L85 _public prototype_ `static FName GetUFunctionFName(Verse::VFunction& Callee);`
- L87 _public prototype_ `static void AddReferencedObjects(UObject* InThis, FReferenceCollector& Collector);`
- L89 _public member_ `Verse::TWriteBarrier<Verse::VFunction> Callee;`
- L92 _public prototype_ `virtual void Bind() override;`
- L96 _private prototype_ `bool TryBindingCoroutine();`

#### union `UVerseFunction::(anonymous)`  
``  
_L54-61_

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace Verse`
- L57 _member_ `const UTF8CHAR* CompiledInAlternateNameUTF8;` (scope `UVerseFunction::__anonea4e91cc010a`) — CONSTINIT_UOBJECT_TODO: Size increase
- L60 _member_ `FName AlternateName = {};` (scope `UVerseFunction::__anonea4e91cc010a`) — The alternate name is used between the native function declaration and the expected verse name

### `Source/Runtime/CoreUObject/Public/VerseVM/VVMVerseHangDetection.h` (Public)


#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_TRACK_ENSURE_OVERHEAD_DURING_SCRIPTS (DO_CHECK || DO_GUARD_SLOW || DO_ENSURE)`
- L12 _namespace_ `namespace VerseHangDetection`
- L15 _prototype_ `float VerseHangThreshold();` (scope `VerseHangDetection`)
- L16 _prototype_ `bool ShouldExcludeOverhead();` (scope `VerseHangDetection`)
- L17 _prototype_ `bool IsComputationLimitExceeded(const double StartTime, double HangThreshold = VerseHangThreshold());` (scope `VerseHangDetection`)
- L25 _prototype_ `void InstallOverheadTracking(TFunction<void()> OnOverheadBegin, TFunction<void(double Duration)> OnOverheadEnd);` (scope `VerseHangDetection`) — Installs callbacks to be invoked when entering and exiting overhead scopes. @param OnOverheadBegin Callback invoked when entering an overhead scope. @param OnOverheadEnd Callback invoked when exiting an overhead scope (with the time duration spent within it).
- L30 _prototype_ `void UninstallOverheadTracking();` (scope `VerseHangDetection`) — Clears installed callbacks that were being used for tracking overhead scopes.
- L35 _prototype_ `void BeginOverheadScope();` (scope `VerseHangDetection`) — Marks the beginning of an overhead scope.
- L40 _prototype_ `void EndOverheadScope();` (scope `VerseHangDetection`) — Marks the end of an overhead scope.

### `Source/Runtime/CoreUObject/Public/VerseVM/VVMVerseNativeTypeDesc.h` (Public)


#### struct `FVniPackageName`  
`struct FVniPackageName`  
_L10-14_
- desc: Fully qualified name of a VNI package.
- L12 _public member_ `const TCHAR* const MountPointName;`
- L13 _public member_ `const TCHAR* const CppModuleName;`

#### struct `FVniPackageDesc`  
`struct FVniPackageDesc`  
_L17-27_
- desc: Describes a Verse package associated with a C++ module.
- L19 _public member_ `const FVniPackageName Name;`
- L20 _public member_ `const TCHAR* VersePath;` — Verse path of the root module of this package
- L21 _public member_ `const EVerseScope::Type VerseScope;` — Origin/visibility of Verse code in this package
- L22 _public member_ `const TCHAR* const VerseDirectoryPath;`
- L25 _public member_ `const FVniPackageName* const Dependencies;` — All dependencies needed to _incrementally_ compile this package I.e. private UBT module dependencies plus transitive closure of public UBT module dependencies
- L26 _public member_ `const int32 NumDependencies;`

#### struct `FVniTypeDesc`  
`struct FVniTypeDesc`  
_L30-39_
- desc: Describes the definition of a type
- L32 _public member_ `const TCHAR* const UEPackageName;`
- L33 _public member_ `const TCHAR* const UEName;`
- L35 _public member_ `const FVniPackageDesc* VersePackageDesc{nullptr};`
- L36 _public member_ `const TCHAR* VersePackageName{nullptr};`
- L37 _public member_ `const TCHAR* VerseModulePath{nullptr};`
- L38 _public member_ `const TCHAR* VerseScopeName{nullptr};`

### `Source/Runtime/CoreUObject/Public/VerseVM/VVMVersePropertyMetadata.h` (Public)


#### struct `FVersePropertyMetadata`  
`struct FVersePropertyMetadata`  
_L11-24_
- reflection: `USTRUCT()`
- desc: Stores per-property metadata for a Verse property on UVerseClass/UVerseStruct.
- L16 _public member_ `FVerseIntConstraints IntConstraints;` — `UPROPERTY()`
- L19 _public member_ `FVerseDoubleConstraints DoubleConstraints;` — `UPROPERTY()`
- L23 _public member_ `FString LLMDescription;` — `UPROPERTY()` — Only populated in BPVM

### `Source/Runtime/CoreUObject/Public/VerseVM/VVMVerseStruct.h` (Public)


#### class `UVerseStruct`  
`class UVerseStruct : public UScriptStruct`  
_L33-159_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UScriptStruct`
- L38 _public prototype_ `UVerseStruct() = default;`
- L39 _public prototype_ `explicit UVerseStruct( const FObjectInitializer& ObjectInitializer, UScriptStruct* InSuperStruct, ICppStructOps* InCppStructOps = nullptr, EStructFlags InStructFlags = STRUCT_NoFlags, SIZE_T ExplicitSize = 0, SIZE_T ExplicitAlignment = 0);`
- L46 _public prototype_ `explicit UVerseStruct(const FObjectInitializer& ObjectInitializer);`
- L49 _public member_ `static const FTopLevelAssetPath VerseStructTopLevelAssetPath;` — This is the asset path that all `UVerseStruct`s get when generated.
- L52 _public function_ `consteval UVerseStruct( UE::CodeGen::ConstInit::FObjectParams ObjectParams, UE::CodeGen::ConstInit::FUFieldParams UFieldParams, UE::CodeGen::ConstInit::FStructParams StructParams, UE::CodeGen::ConstInit::FScriptStructParams ScriptStructParams, UE::CodeGen::ConstInit::FVerseStructParams InVerseParams) : Super(ObjectParams, UFieldParams, StructParams, ScriptStructParams) , CompiledInQualifiedName(InVerseParams.QualifiedName) , VerseClassFlags(VCLASS_UHTNative | InVerseParams.VerseClassFlags) , QualifiedName(ConstEval) , Guid(InVerseParams.GuidA, InVerseParams.GuidB, InVerseParams.GuidC, InVerseParams.GuidD) , PropertyMetadata(ConstEval) , NativeTypeDesc(InVerseParams.NativeTypeDesc)`
- L70 _public prototype_ `virtual void Serialize(FArchive& Ar) override;` — UObject implementation
- L71 _public prototype_ `virtual void PreSave(FObjectPreSaveContext ObjectSaveContext) override;`
- L72 _public function_ `virtual bool IsNameStableForNetworking() const override`
- L76 _public prototype_ `AUTORTFM_DISABLE virtual void Link(FArchive& Ar, bool bRelinkExistingProperties) override;` — Creates the field/property links and gets structure ready for use at runtime
- L77 _public prototype_ `virtual FString GetAuthoredNameForField(const FField* Field) const override;`
- L80 _public prototype_ `virtual uint32 GetStructTypeHash(const void* Src) const override;` — UScriptStruct implementation
- L81 _public function_ `virtual FGuid GetCustomGuid() const override`
- L84 _private prototype_ `virtual void GetAssetRegistryTags(FAssetRegistryTagsContext Context) const override;`
- L89 _public member_ `const UTF8CHAR* CompiledInQualifiedName = nullptr;` — CONSTINIT_UOBJECT_TODO: This increases size
- L94 _public member_ `uint32 VerseClassFlags = 0;` — `UPROPERTY()` — EVerseClassFlags
- L97 _public member_ `FUtf8String QualifiedName;` — `UPROPERTY()`
- L101 _public member_ `TObjectPtr<UFunction> InitFunction;` — `UPROPERTY()` — Function used for initialization
- L105 _public member_ `TObjectPtr<UVerseClass> ModuleClass;` — `UPROPERTY()` — Parent module class
- L109 _public member_ `FGuid Guid;` — `UPROPERTY()` — GUID to be able to match old version of this struct to new one
- L112 _public member_ `TObjectPtr<UFunction> FactoryFunction;` — `UPROPERTY()`
- L115 _public member_ `TObjectPtr<UFunction> OverrideFactoryFunction;` — `UPROPERTY()`
- L118 _public member_ `EVerseEffectSet ConstructorEffects = EVerseEffectSet::None;` — `UPROPERTY()`
- L121 _public member_ `TMap<TFieldPath<FProperty>, FVersePropertyMetadata> PropertyMetadata;` — `UPROPERTY()`
- L125 _public member_ `Verse::TWriteBarrier<Verse::VClass> Class;` — `UPROPERTY()`
- L127 _public member_ `Verse::VRestValue Shape{0};`
- L130 _public member_ `UE::GC::FSchemaOwner ReferenceSchema;` — GC schema if needed, finalized in AssembleReferenceTokenStream
- L132 _public prototype_ `void ResetUHTNative();`
- L133 _public prototype_ `void SetShape(Verse::FAllocationContext Context, Verse::VShape* InShape);`
- L135 _public prototype_ `static void AddReferencedObjects(UObject* InThis, FReferenceCollector& Collector);`
- L136 _public prototype_ `void AssembleReferenceTokenStream(bool bForce = false);`
- L139 _public prototype_ `void InvokeDefaultFactoryFunction(uint8* InStructData) const;`
- L141 _public function_ `bool IsNativeBound() const`
- L142 _public function_ `bool IsUHTNative() const`
- L143 _public function_ `bool IsTuple() const`
- L144 _public function_ `bool IsParametric() const`
- L145 _public function_ `bool IsPersonaConstructible() const`
- L147 _public function_ `void SetNativeBound()`
- L149 _public function_ `const FVniTypeDesc* GetNativeTypeDesc()`
- L150 _public function_ `void SetNativeTypeDesc(const FVniTypeDesc* InNativeTypeDesc)`
- L155 _private member_ `TObjectPtr<UStructCookedMetaData> CachedCookedMetaDataPtr;` — `UPROPERTY()`
- L158 _private member_ `const FVniTypeDesc* NativeTypeDesc{nullptr};`

#### Free symbols / members of external scopes

- L26 _namespace_ `namespace Verse`

### `Source/Runtime/CoreUObject/Public/VerseVM/VVMWeakBarrier.h` (Public)


#### struct `Verse::TWeakBarrier`  
`template <typename T> struct TWeakBarrier`  
_L16-196_
- L18 _public member_ `static constexpr bool bIsVValue = std::is_same_v<T, VValue>;`
- L19 _public member_ `static constexpr bool bIsAux = IsTAux<T>;`
- L20 _public typedef_ `using TValue = typename std::conditional_t<bIsAux, T, typename std::conditional_t<bIsVValue, VValue, T*>>;`
- L21 _public typedef_ `using TEncodedValue = typename std::conditional<bIsVValue, uint64, T*>::type;`
- L23 _public prototype_ `TWeakBarrier() = default;`
- L26 _public function_ `TWeakBarrier(const TWeakBarrier& Other)` — Making use of this constructor is potentially expensive because it could involve a TLS lookup.
- L31 _public function_ `TWeakBarrier& operator=(const TWeakBarrier& Other)`
- L38 _public function_ `TWeakBarrier(TWeakBarrier&& Other)` — Making use of this constructor is potentially expensive because it could involve a TLS lookup.
- L44 _public function_ `TWeakBarrier& operator=(TWeakBarrier&& Other)`
- L51 _public function_ `TWeakBarrier(TValue Value) : Value(Value)`
- L56 _public function_ `TWeakBarrier& operator=(TValue InValue)`
- L63 _public function_ `template <typename U = T> TWeakBarrier(std::enable_if_t<!bIsVValue, U>& Value) : Value(&Value)`
- L68 _public function_ `bool operator==(const TWeakBarrier& Other) const`
- L74 _public function_ `template <typename TResult = void> std::enable_if_t<!bIsVValue, TResult> Set(T& NewValue)`
- L79 _public function_ `void Set(TValue NewValue)`
- L84 _public function_ `void Reset()`
- L96 _public function_ `TValue Get(FAccessContext Context) const`
- L97 _public function_ `TValue Get() const`
- L103 _public function_ `template <typename TResult = TValue> std::enable_if_t<!bIsVValue && !bIsAux, TResult> operator->() const`
- L106 _public function_ `template <typename TResult = T> std::enable_if_t<!bIsVValue && !bIsAux, TResult&> operator*() const`
- L108 _public function_ `explicit operator bool() const`
- L115 _public function_ `bool ClearWeakDuringCensus()` — Clears out weak references that are unmarked (i.e. non-live). @return 	If the value was/wasn't cleared out.
- L141 _private member_ `TValue Value{};`
- L144 _private function_ `template <typename ContextType> static TValue RunReadBarrier(ContextType Context, TValue Value)`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace Verse`
- L199 _function_ `template <typename T> uint32 GetTypeHash(const TWeakBarrier<T>& WeakBarrier)` (scope `Verse`)
- L208 _typedef_ `template <typename InElementType, typename KeyFuncs = DefaultKeyFuncs<TWeakBarrier<InElementType>>, typename Allocator = FDefaultSparseSetAllocator> using TWeakBarrierSet = TSparseSet<TWeakBarrier<InElementType>, KeyFuncs, Allocator>;` (scope `Verse`) — Define a TWeakBarrierSet that uses TSparseSet to avoid TCompactSet's need to compute hashes on removal. This could also alternatively use TSet/TCompactSet, but wrap the element type in a TStoredHash element type.

### `Source/Runtime/CoreUObject/Public/VerseVM/VVMWeakCellMap.h` (Public)


#### struct `Verse::VWeakCellMap`  
`struct VWeakCellMap : VCell`  
_L15-49_
- inherits: `VCell`
- L18 _public member_ `static TGlobalTrivialEmergentTypePtr<&StaticCppClassInfo> GlobalTrivialEmergentType;`
- L20 _public function_ `AUTORTFM_DISABLE static VWeakCellMap& New(FAllocationContext Context)`
- L25 _public prototype_ `VCell* Find(FAccessContext Context, VCell* Key);`
- L26 _public prototype_ `void Add(FAccessContext Context, VCell* Key, VCell* Value);`
- L27 _public prototype_ `void Remove(VCell* Key);`
- L29 _public prototype_ `template <typename FunctorType>`
- L35 _public function_ `bool IsEmpty() const` — This function is a test-only function because it has a very limited kind of meaning. Requesting the size (or checking the emptiness) of a weak map gives a kind of upper bound: it means that the map has at most this many entries. But we cannot tell you which of those entries are real. When you query them, you are likely to find fewer entries.
- L37 _public function_ `size_t GetAllocatedSize() const`
- L43 _private prototype_ `AUTORTFM_DISABLE VWeakCellMap(FAllocationContext Context);`
- L44 _private prototype_ `~VWeakCellMap();`
- L46 _private prototype_ `void ConductCensusImpl();`
- L48 _private member_ `TMap<VCell*, VCell*> Map;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace Verse`

### `Source/Runtime/CoreUObject/Public/VerseVM/VVMWeakKeyMap.h` (Public)


#### struct `Verse::FWeakKeyMap`  
`struct FWeakKeyMap final`  
_L35-63_
- desc: This is a collection of "transposed" weak maps. A transposed weak map maps maps to values. I.e. while a weak map is a Key -> Value map, a transposed weak map is a Map -> Value map. A weak key map is a collection of transposed weak maps keyed by key. I.e. a weak key map is a Key -> Map -> Value map. For every weak map entry in the world of the form Key -> Value where Map is the owning map (the one that would do the logic in VisitReferences that says "if Key is marked then mark Value"), there must be a weak key map entry of the form Key -> Map -> Value. This ensures that if Key is not yet marked before the Map runs its VisitReferences, then the weak key map that owns the Key will do the marking by running "if Map is marked then mark Value" logic. You could imagine there being one FWeakKeyMap globally for the whole GC. That would work. But we hang FWeakKeyMap off libpas's verse_heap_page_header (aka Verse::FHeapPageHeader). There is one of those per "page" for objects in segregated storage, and one globally for all large objects. Libpas manages the synchronization that protects these maps. Most of this is "owned" by VCell. VCell accesses this via FWeakKeyMapGuard.
- L37 _public prototype_ `FWeakKeyMap();`
- L38 _public prototype_ `~FWeakKeyMap();`
- L40 _public function_ `bool IsEmpty() const`
- L46 _public prototype_ `bool HasEntriesForKey(VCell* Key) const;` — This is just to support testing.
- L48 _public prototype_ `void Add(VCell* Key, VCell* Map, VCell* Value);`
- L49 _public prototype_ `void Remove(VCell* Key, VCell* Map);`
- L52 _public prototype_ `template <typename TVisitor> void Visit(VCell* Key, TVisitor& Visitor);`
- L54 _public prototype_ `void ConductCensus();`
- L56 _public function_ `size_t GetAllocatedSize() const`
- L62 _private member_ `TMap<VCell*, TMap<VCell*, VCell*>> InternalMap;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace Verse`

### `Source/Runtime/CoreUObject/Public/VerseVM/VVMWeakKeyMapGuard.h` (Public)


#### struct `Verse::FWeakKeyMapGuard`  
`struct FWeakKeyMapGuard final`  
_L13-50_
- L15 _public function_ `FWeakKeyMapGuard(FHeapPageHeader* Header) : Guard(Header)`
- L20 _public function_ `FWeakKeyMap* TryGet()`
- L25 _public function_ `FWeakKeyMap* Get()`
- L39 _public prototype_ `bool ConductCensus();` — Returns true if this page no longer has a weak key map. If this returns false, then it also accounts for the native memory usage of this map.
- L42 _private prototype_ `FWeakKeyMap* GetSlow();`
- L44 _private function_ `FWeakKeyMap*& GetRef() const`
- L49 _private member_ `FHeapClientDataGuard Guard;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace Verse`

### `Source/Runtime/CoreUObject/Public/VerseVM/VVMWriteBarrier.h` (Public)


#### enum `Verse::EWriteMode`  
`enum class EWriteMode`  
_L25-33_
- desc: Enumerator used to control whether a TWriteBarrier write is transactional (reverts to its original value on transaction abort) or not.
- L28 _public enumerator_ `Default` — Transactional write if called from the closed, otherwise non-transactional.
- L30 _public enumerator_ `NonTransactional` — Non-transactional write regardless of AutoRTFM mode.
- L32 _public enumerator_ `Transactional` — Transactional write regardless of AutoRTFM mode.

#### struct `Verse::TWriteBarrier`  
`template <typename T> struct TWriteBarrier`  
_L53-286_
- desc: This class is a smart pointer that runs a GC write barrier whenever the stored pointer is changed Fundamental law of concurrent GC: when thoust mutated the heap thou shalt run the barrier template When a VValue of heap pointer type (VCell*) is written, a barrier is run (int32s and floats don't run a barrier) The barrier will inform the GC about a new edge in the heap, and GC will immediately mark the cell if a collection is ongoing This is necessary because GC might have already visited the previous content of Value, and might miss the updated value in that case No barrier is needed when _deleting_ heap references, therefore we don't care about the previous Value during mutation It does not matter if the barrier is run before or after mutation since we unconditionally mark only the new value We also run the barrier during TWriteBarrier construction since a white (= otherwise unreachable) cell might have been assigned New cells are allocated black (marked, reachable) so we are not worried about those here
- L55 _public member_ `static constexpr bool bCanSetTransactionally = std::is_base_of_v<VValue, T> || std::is_base_of_v<TAux<void>, T> || std::is_base_of_v<VCell, T>;`
- L56 _public member_ `static constexpr bool bIsVValue = std::is_same_v<T, VValue> || std::is_same_v<T, VInt>;`
- L57 _public member_ `static constexpr bool bIsAux = IsTAux<T>;`
- L58 _public member_ `static constexpr bool bValueIsTPtr = !bIsVValue && !bIsAux;` — TValue is T*, not T
- L59 _public typedef_ `using TValue = typename std::conditional_t<bValueIsTPtr, T*, T>;`
- L60 _public typedef_ `using TConstValue = typename std::conditional_t<bValueIsTPtr, const T*, T>;`
- L61 _public typedef_ `using TEncodedValue = typename std::conditional<bIsVValue, uint64, T*>::type;`
- L63 _public prototype_ `V_FORCEINLINE TWriteBarrier() = default;`
- L66 _public function_ `V_FORCEINLINE TWriteBarrier(const TWriteBarrier& Other)` — Making use of this constructor is potentially expensive because it could involve a TLS lookup.
- L71 _public function_ `V_FORCEINLINE TWriteBarrier& operator=(const TWriteBarrier& Other)`
- L77 _public function_ `bool Equals(const TWriteBarrier& Other) const`
- L83 _public function_ `bool operator==(const TWriteBarrier& Other) const` — Needed to allow for `TWriteBarrier` to be usable with `TMap`.
- L91 _public function_ `bool operator==(TConstValue Other) const` — Allows `TMap::RemoveByHash` to match a `VCell*` with a `TWriteBarrier<VCell>`, or a `VValue` with a `TWriteBarrier<VValue>`, which lets us remove elements from a container without constructing an extraneous write barrier.
- L96 _public function_ `V_FORCEINLINE TWriteBarrier(FAccessContext Context, TValue Value)`
- L101 _public function_ `V_FORCEINLINE TWriteBarrier(FAccessContext Context, T& Value) requires bValueIsTPtr`
- L107 _public prototype_ `AUTORTFM_OPEN void ResetTransactionally() requires bCanSetTransactionally;`
- L111 _public function_ `template <EWriteMode WriteMode = EWriteMode::Default> V_FORCEINLINE void Reset()`
- L131 _public prototype_ `AUTORTFM_OPEN void SetTransactionally(FAccessContext Context, TValue NewValue) requires bCanSetTransactionally;`
- L135 _public function_ `template <EWriteMode WriteMode = EWriteMode::Default> V_FORCEINLINE void Set(FAccessContext Context, TValue NewValue)`
- L156 _public function_ `V_FORCEINLINE void SetTransactionally(FAccessContext Context, T& NewValue) requires bValueIsTPtr`
- L162 _public function_ `V_FORCEINLINE void Set(FAccessContext Context, T& NewValue) requires bValueIsTPtr`
- L168 _public prototype_ `void SetTrailed(FAllocationContext, FTrail&, TValue);`
- L170 _public function_ `V_FORCEINLINE constexpr void SetNonCellNorPlaceholder(VValue NewValue) requires bIsVValue`
- L192 _public prototype_ `AUTORTFM_OPEN void SetNonCellNorPlaceholderTransactionally(VValue) requires bIsVValue;`
- L195 _public prototype_ `void SetNonCellNorPlaceholderTrailed(FAllocationContext, FTrail&, VValue) requires bIsVValue;`
- L198 _public function_ `TValue Get() const`
- L200 _public function_ `template <typename TResult = TValue> std::enable_if_t<bIsVValue, TResult> Follow() const`
- L205 _public function_ `T* operator->() const requires bValueIsTPtr`
- L212 _public function_ `template <typename TResult = T> T& operator*() const requires bValueIsTPtr`
- L218 _public function_ `explicit operator bool() const`
- L238 _private member_ `TValue Value{};`
- L241 _private function_ `template <typename ContextType> AUTORTFM_OPEN FORCENOINLINE static void RunBarrierSlow(ContextType Context, TValue Value)`
- L279 _private function_ `template <typename ContextType> static void RunBarrier(ContextType Context, TValue Value)`
- L339 _function_ `template <typename T> inline void TWriteBarrier<T>::ResetTransactionally() requires bCanSetTransactionally`
- L346 _function_ `template <typename T> V_FORCEINLINE void TWriteBarrier<T>::SetTransactionally(FAccessContext Context, TValue NewValue) requires bCanSetTransactionally`
- L355 _function_ `template <typename T> V_FORCEINLINE void TWriteBarrier<T>::SetNonCellNorPlaceholderTransactionally(VValue NewValue) requires bIsVValue`

#### struct `Verse::Detail::TAutoRTFMWriteFlagsFor`  
`template <typename T> requires std::is_base_of_v<VValue, T> struct TAutoRTFMWriteFlagsFor<TWriteBarrier<T>>`  
_L299-303_
- L302 _public member_ `static constexpr AutoRTFM::EWriteFlags Value = AutoRTFM::EWriteFlags::CustomRollback;`
- L310 _public member_ `static constexpr AutoRTFM::EWriteFlags Value = AutoRTFM::EWriteFlags::CustomRollback | AutoRTFM::EWriteFlags::CustomFlag0;`
- L317 _public member_ `static constexpr AutoRTFM::EWriteFlags Value = AutoRTFM::EWriteFlags::CustomRollback | AutoRTFM::EWriteFlags::CustomFlag1;`

#### struct `Verse::Detail::TAutoRTFMWriteFlagsFor`  
`template <typename T> requires std::is_base_of_v<TAux<void>, T> struct TAutoRTFMWriteFlagsFor<TWriteBarrier<T>>`  
_L307-311_
- L302 _public member_ `static constexpr AutoRTFM::EWriteFlags Value = AutoRTFM::EWriteFlags::CustomRollback;`
- L310 _public member_ `static constexpr AutoRTFM::EWriteFlags Value = AutoRTFM::EWriteFlags::CustomRollback | AutoRTFM::EWriteFlags::CustomFlag0;`
- L317 _public member_ `static constexpr AutoRTFM::EWriteFlags Value = AutoRTFM::EWriteFlags::CustomRollback | AutoRTFM::EWriteFlags::CustomFlag1;`

#### struct `Verse::Detail::TAutoRTFMWriteFlagsFor`  
`template <typename T> requires std::is_base_of_v<VCell, T> struct TAutoRTFMWriteFlagsFor<TWriteBarrier<T>>`  
_L315-318_
- L302 _public member_ `static constexpr AutoRTFM::EWriteFlags Value = AutoRTFM::EWriteFlags::CustomRollback;`
- L310 _public member_ `static constexpr AutoRTFM::EWriteFlags Value = AutoRTFM::EWriteFlags::CustomRollback | AutoRTFM::EWriteFlags::CustomFlag0;`
- L317 _public member_ `static constexpr AutoRTFM::EWriteFlags Value = AutoRTFM::EWriteFlags::CustomRollback | AutoRTFM::EWriteFlags::CustomFlag1;`

#### Free symbols / members of external scopes

- L18 _namespace_ `namespace Verse`
- L38 _function_ `template <EWriteMode WriteMode> inline bool IsTransactional()` (scope `Verse`) — Returns true if WriteMode is EWriteMode::Transactional, or WriteMode is EWriteMode::Default and is called from the closed.
- L220 _function_ `friend uint32 GetTypeHash(const TWriteBarrier<T>& WriteBarrier)` (scope `Verse`)
- L289 _prototype_ `template <typename TArg> TWriteBarrier(FAccessContext, TArg&& Arg) -> TWriteBarrier<std::decay_t<TArg>>;` (scope `Verse`)
- L291 _namespace_ `namespace Detail` (scope `Verse`)
- L330 _variable_ `template <typename T> static constexpr AutoRTFM::EWriteFlags AutoRTFMWriteFlagsFor = Detail::TAutoRTFMWriteFlagsFor<T>::Value;` (scope `Verse`) — The AutoRTFM::EWriteFlags to use for a call to AutoRTFM::RecordOpenWrite() when recording a change to a TWriteBarrier. The flags will have the AutoRTFM::EWriteFlags::CustomRollback bit set, which will trigger a call to RollbackAutoRTFMWrite() if the transaction is aborted. The flags may also contain one or more AutoRTFM::EWriteFlags::CustomFlagX bits which are used by RollbackAutoRTFMWrite() to use the appropriate write-barrier method for the given templated type.
- L336 _prototype_ `void RollbackAutoRTFMWrite(void* LogicalAddress, const void* Data, size_t Size, autortfm_write_flags Flags);` (scope `Verse`) — Called by AutoRTFM when a transaction is aborted that contains writes with the AutoRTFM::EWriteFlags::CustomRollback flag. This flag is used exclusively by TWriteBarrier so that write-barriers are performed for rollbacks of the TWriteBarrier value.
- L364 _function_ `template <class VCellType> inline void FReferenceCollector::AddReferencedVerseValue(Verse::TWriteBarrier<VCellType>& InValue, const UObject* ReferencingObject, const FProperty* ReferencingProperty)` (scope `FReferenceCollector`)
