# Plugins / PlainPropsUObject

- module root: `Plugins/Experimental/PlainPropsUObject/Source`
- headers: 8; symbols: 483
- symbol kinds: class=3, delegate=1, enum=4, enumerator=17, externvar=1, function=56, macro=4, member=135, namespace=18, prototype=137, struct=76, typedef=30, variable=1
- PrivateDependencyModuleNames: Core, CorePreciseFP, CoreUObject, JsonObjectGraph, PlainProps

### `Plugins/Experimental/PlainPropsUObject/Source/Internal/PlainPropsUObjectMetaBindingsInternal.h` (Internal)


#### struct `PlainProps::UE::FPropertyBinding`  
`struct FPropertyBinding : ICustomBinding`  
_L206-218_
- inherits: `ICustomBinding`
- L208 _public prototype_ `UE_CUSTOM_BIND_MEMBERS(FProperty, NamePrivate, ArrayDim, ElementSize, PropertyFlags, RepIndex, BlueprintReplicationCondition);`
- L210 _public prototype_ `FPropertyBinding(TPropertySpecifier<NumMembers>& Spec);`
- L212 _public member_ `const FEnumId PropertyFlagsId;`
- L213 _public member_ `const FEnumId LifetimeConditionId;`
- L215 _public prototype_ `void Save(FMemberBuilder& Dst, const Type& Src, const Type* Default, const FSaveContext& Ctx) const;`
- L216 _public prototype_ `void Load(Type& Dst, FStructLoadView Src, ECustomLoadMethod Method) const;`
- L217 _public function_ `static bool Diff(const Type& A, const Type& B, const FBindContext& Ctx)`

#### struct `PlainProps::UE::FBoolPropertyBinding`  
`struct FBoolPropertyBinding : ICustomBinding`  
_L220-228_
- inherits: `ICustomBinding`
- L222 _public prototype_ `UE_CUSTOM_BIND_MEMBERS(FBoolProperty, FieldSize, ByteOffset, ByteMask, FieldMask);`
- L223 _public prototype_ `FBoolPropertyBinding(TPropertySpecifier<NumMembers>& Spec);`
- L225 _public prototype_ `void Save(FMemberBuilder& Dst, const Type& Src, const Type* Default, const FSaveContext& Ctx) const;`
- L226 _public prototype_ `void Load(Type& Dst, FStructLoadView Src, ECustomLoadMethod Method) const;`
- L227 _public function_ `static bool Diff(const Type& A, const Type& B, const FBindContext& Ctx)`

#### struct `PlainProps::UE::FStructPropertyBinding`  
`struct FStructPropertyBinding : ICustomBinding`  
_L230-238_
- inherits: `ICustomBinding`
- L232 _public prototype_ `UE_CUSTOM_BIND_MEMBERS(FStructProperty, Struct);`
- L233 _public prototype_ `FStructPropertyBinding(TPropertySpecifier<NumMembers>& Spec);`
- L235 _public prototype_ `void Save(FMemberBuilder& Dst, const Type& Src, const Type* Default, const FSaveContext& Ctx) const;`
- L236 _public prototype_ `void Load(Type& Dst, FStructLoadView Src, ECustomLoadMethod Method) const;`
- L237 _public function_ `static bool Diff(const Type& A, const Type& B, const FBindContext& Ctx)`

#### struct `PlainProps::UE::FClassPropertyBinding`  
`struct FClassPropertyBinding : ICustomBinding`  
_L240-248_
- inherits: `ICustomBinding`
- L242 _public prototype_ `UE_CUSTOM_BIND_MEMBERS(FClassProperty, MetaClass);`
- L243 _public prototype_ `FClassPropertyBinding(TPropertySpecifier<NumMembers>& Spec);`
- L245 _public prototype_ `void Save(FMemberBuilder& Dst, const Type& Src, const Type* Default, const FSaveContext& Ctx) const;`
- L246 _public prototype_ `void Load(Type& Dst, FStructLoadView Src, ECustomLoadMethod Method) const;`
- L247 _public function_ `static bool Diff(const Type& A, const Type& B, const FBindContext& Ctx)`

#### struct `PlainProps::UE::FObjectPropertyBaseBinding`  
`struct FObjectPropertyBaseBinding : ICustomBinding`  
_L250-258_
- inherits: `ICustomBinding`
- L252 _public prototype_ `UE_CUSTOM_BIND_MEMBERS(FObjectPropertyBase, PropertyClass);`
- L253 _public prototype_ `FObjectPropertyBaseBinding(TPropertySpecifier<NumMembers>& Spec);`
- L255 _public prototype_ `void Save(FMemberBuilder& Dst, const Type& Src, const Type* Default, const FSaveContext& Ctx) const;`
- L256 _public prototype_ `void Load(Type& Dst, FStructLoadView Src, ECustomLoadMethod Method) const;`
- L257 _public function_ `static bool Diff(const Type& A, const Type& B, const FBindContext& Ctx)`

#### struct `PlainProps::UE::FArrayPropertyBinding`  
`struct FArrayPropertyBinding : ICustomBinding`  
_L260-268_
- inherits: `ICustomBinding`
- L262 _public prototype_ `UE_CUSTOM_BIND_MEMBERS(FArrayProperty, InnerPropertyTypeName, InnerProperty);`
- L263 _public prototype_ `FArrayPropertyBinding(TPropertySpecifier<NumMembers>& Spec);`
- L265 _public prototype_ `void Save(FMemberBuilder& Dst, const Type& Src, const Type* Default, const FSaveContext& Ctx) const;`
- L266 _public prototype_ `void Load(Type& Dst, FStructLoadView Src, ECustomLoadMethod Method) const;`
- L267 _public function_ `static bool Diff(const Type& A, const Type& B, const FBindContext& Ctx)`

#### struct `PlainProps::UE::FSetPropertyBinding`  
`struct FSetPropertyBinding : ICustomBinding`  
_L270-278_
- inherits: `ICustomBinding`
- L272 _public prototype_ `UE_CUSTOM_BIND_MEMBERS(FSetProperty, InnerPropertyTypeName, InnerProperty);`
- L273 _public prototype_ `FSetPropertyBinding(TPropertySpecifier<NumMembers>& Spec);`
- L275 _public prototype_ `void Save(FMemberBuilder& Dst, const Type& Src, const Type* Default, const FSaveContext& Ctx) const;`
- L276 _public prototype_ `void Load(Type& Dst, FStructLoadView Src, ECustomLoadMethod Method) const;`
- L277 _public function_ `static bool Diff(const Type& A, const Type& B, const FBindContext& Ctx)`

#### struct `PlainProps::UE::FMapPropertyBinding`  
`struct FMapPropertyBinding : ICustomBinding`  
_L280-288_
- inherits: `ICustomBinding`
- L282 _public prototype_ `UE_CUSTOM_BIND_MEMBERS(FMapProperty, KeyPropertyTypeName, KeyProperty, ValuePropertyTypeName, ValueProperty);`
- L283 _public prototype_ `FMapPropertyBinding(TPropertySpecifier<NumMembers>& Spec);`
- L285 _public prototype_ `void Save(FMemberBuilder& Dst, const Type& Src, const Type* Default, const FSaveContext& Ctx) const;`
- L286 _public prototype_ `void Load(Type& Dst, FStructLoadView Src, ECustomLoadMethod Method) const;`
- L287 _public function_ `static bool Diff(const Type& A, const Type& B, const FBindContext& Ctx)`

#### struct `PlainProps::UE::FOptionalPropertyBinding`  
`struct FOptionalPropertyBinding : ICustomBinding`  
_L290-298_
- inherits: `ICustomBinding`
- L292 _public prototype_ `UE_CUSTOM_BIND_MEMBERS(FOptionalProperty, ValuePropertyTypeName, ValueProperty);`
- L293 _public prototype_ `FOptionalPropertyBinding(TPropertySpecifier<NumMembers>& Spec);`
- L295 _public prototype_ `void Save(FMemberBuilder& Dst, const Type& Src, const Type* Default, const FSaveContext& Ctx) const;`
- L296 _public prototype_ `void Load(Type& Dst, FStructLoadView Src, ECustomLoadMethod Method) const;`
- L297 _public function_ `static bool Diff(const Type& A, const Type& B, const FBindContext& Ctx)`

#### struct `PlainProps::UE::FBytePropertyBinding`  
`struct FBytePropertyBinding : ICustomBinding`  
_L300-308_
- inherits: `ICustomBinding`
- L302 _public prototype_ `UE_CUSTOM_BIND_MEMBERS(FByteProperty, Enum);`
- L303 _public prototype_ `FBytePropertyBinding(TPropertySpecifier<NumMembers>& Spec);`
- L305 _public prototype_ `void Save(FMemberBuilder& Dst, const Type& Src, const Type* Default, const FSaveContext& Ctx) const;`
- L306 _public prototype_ `void Load(Type& Dst, FStructLoadView Src, ECustomLoadMethod Method) const;`
- L307 _public function_ `static bool Diff(const Type& A, const Type& B, const FBindContext& Ctx)`

#### struct `PlainProps::UE::FEnumPropertyBinding`  
`struct FEnumPropertyBinding : ICustomBinding`  
_L310-318_
- inherits: `ICustomBinding`
- L312 _public prototype_ `UE_CUSTOM_BIND_MEMBERS(FEnumProperty, UnderlyingPropertyTypeName, UnderlyingProperty, Enum);`
- L313 _public prototype_ `FEnumPropertyBinding(TPropertySpecifier<NumMembers>& Spec);`
- L315 _public prototype_ `void Save(FMemberBuilder& Dst, const Type& Src, const Type* Default, const FSaveContext& Ctx) const;`
- L316 _public prototype_ `void Load(Type& Dst, FStructLoadView Src, ECustomLoadMethod Method) const;`
- L317 _public function_ `static bool Diff(const Type& A, const Type& B, const FBindContext& Ctx)`

#### struct `PlainProps::UE::UStructBinding`  
`struct UStructBinding : ICustomBinding`  
_L323-336_
- inherits: `ICustomBinding`
- L325 _public prototype_ `UE_CUSTOM_BIND_MEMBERS(UStruct, SuperStruct, Children, ChildPropertyClasses);`
- L326 _public prototype_ `UStructBinding(TPropertySpecifier<NumMembers>& Spec);`
- L328 _public prototype_ `static FTypedRange SaveChildrenStatic(const UField* Children, int32 Num, const FSaveContext& Ctx);`
- L329 _public prototype_ `static FTypedRange SaveChildPropertyClassesStatic(const FField* ChildProperties, int32 Num, const FSaveContext& Ctx);`
- L330 _public prototype_ `static void LoadChildrenStatic(TObjectPtr<UField>& Children, FStructRangeLoadView Src);`
- L331 _public prototype_ `static void LoadChildPropertyClassesStatic(UStruct& Dst, FStructRangeLoadView Src);`
- L333 _public prototype_ `void Save(FMemberBuilder& Dst, const Type& Src, const Type* Default, const FSaveContext& Ctx) const;`
- L334 _public prototype_ `void Load(Type& Dst, FStructLoadView Src, ECustomLoadMethod Method) const;`
- L335 _public function_ `static bool Diff(const Type& A, const Type& B, const FBindContext& Ctx)`

#### struct `PlainProps::UE::UClassBinding`  
`struct UClassBinding : ICustomBinding`  
_L338-356_
- inherits: `ICustomBinding`
- L341 _public prototype_ `UE_CUSTOM_BIND_MEMBERS(UClass, ClassFlags, ClassWithin, ClassConfigName, ClassGeneratedBy, Interfaces);`
- L345 _public prototype_ `UClassBinding(TPropertySpecifier<NumMembers>& Spec);`
- L347 _public member_ `const FEnumId ClassFlagsId;`
- L348 _public member_ `const FDualStructId ImplementedInterfaceId;`
- L350 _public prototype_ `static FTypedRange SaveInterfacesStatic(FBindId Id, TConstArrayView<FImplementedInterface> Interfaces, const FSaveContext& Ctx);`
- L351 _public prototype_ `static void LoadInterfacesStatic(TArray<FImplementedInterface>& Interfaces, FStructRangeLoadView Src);`
- L353 _public prototype_ `void Save(FMemberBuilder& Dst, const Type& Src, const Type* Default, const FSaveContext& Ctx) const;`
- L354 _public prototype_ `void Load(Type& Dst, FStructLoadView Src, ECustomLoadMethod Method) const;`
- L355 _public function_ `static bool Diff(const Type& A, const Type& B, const FBindContext& Ctx)`

#### struct `PlainProps::UE::UFunctionBinding`  
`struct UFunctionBinding : ICustomBinding`  
_L358-368_
- inherits: `ICustomBinding`
- L360 _public prototype_ `UE_CUSTOM_BIND_MEMBERS(UFunction, FunctionFlags, EventGraphFunction, EventGraphCallOffset);`
- L361 _public prototype_ `UFunctionBinding(TPropertySpecifier<NumMembers>& Spec);`
- L363 _public member_ `const FEnumId FunctionFlagsId;`
- L365 _public prototype_ `void Save(FMemberBuilder& Dst, const Type& Src, const Type* Default, const FSaveContext& Ctx) const;`
- L366 _public prototype_ `void Load(Type& Dst, FStructLoadView Src, ECustomLoadMethod Method) const;`
- L367 _public function_ `static bool Diff(const Type& A, const Type& B, const FBindContext& Ctx)`

#### struct `PlainProps::UE::UScriptStructBinding`  
`struct UScriptStructBinding : ICustomBinding`  
_L370-380_
- inherits: `ICustomBinding`
- L372 _public prototype_ `UE_CUSTOM_BIND_MEMBERS(UScriptStruct, StructFlags);`
- L373 _public prototype_ `UScriptStructBinding(TPropertySpecifier<NumMembers>& Spec);`
- L375 _public member_ `const FEnumId StructFlagsId;`
- L377 _public prototype_ `void Save(FMemberBuilder& Dst, const Type& Src, const Type* Default, const FSaveContext& Ctx) const;`
- L378 _public prototype_ `void Load(Type& Dst, FStructLoadView Src, ECustomLoadMethod Method) const;`
- L379 _public function_ `static bool Diff(const Type& A, const Type& B, const FBindContext& Ctx)`

#### struct `PlainProps::TCustomBind`  
`template<> struct TCustomBind<FProperty>`  
_L389-389_
- desc: custom FProperty meta bindings
- L389 _public typedef_ `template<> struct TCustomBind<FProperty> { using Type = UE::FPropertyBinding; };` — custom FProperty meta bindings
- L393 _public typedef_ `template<> struct TCustomBind<FEnumProperty> { using Type = UE::FEnumPropertyBinding; };`
- L394 _public typedef_ `template<> struct TCustomBind<FBoolProperty> { using Type = UE::FBoolPropertyBinding; };`
- L395 _public typedef_ `template<> struct TCustomBind<FByteProperty> { using Type = UE::FBytePropertyBinding; };`
- L396 _public typedef_ `template<> struct TCustomBind<FStructProperty> { using Type = UE::FStructPropertyBinding; };`
- L397 _public typedef_ `template<> struct TCustomBind<FClassProperty> { using Type = UE::FClassPropertyBinding; };`
- L398 _public typedef_ `template<> struct TCustomBind<FObjectPropertyBase> { using Type = UE::FObjectPropertyBaseBinding; };`
- L399 _public typedef_ `template<> struct TCustomBind<FArrayProperty> { using Type = UE::FArrayPropertyBinding; };`
- L402 _public typedef_ `template<> struct TCustomBind<UStruct> { using Type = UE::UStructBinding; };` — custom UField meta bindings

#### struct `PlainProps::TCustomBind`  
`template<> struct TCustomBind<FProperty>`  
_L390-390_
- desc: custom FProperty meta bindings
- L389 _public typedef_ `template<> struct TCustomBind<FProperty> { using Type = UE::FPropertyBinding; };` — custom FProperty meta bindings
- L393 _public typedef_ `template<> struct TCustomBind<FEnumProperty> { using Type = UE::FEnumPropertyBinding; };`
- L394 _public typedef_ `template<> struct TCustomBind<FBoolProperty> { using Type = UE::FBoolPropertyBinding; };`
- L395 _public typedef_ `template<> struct TCustomBind<FByteProperty> { using Type = UE::FBytePropertyBinding; };`
- L396 _public typedef_ `template<> struct TCustomBind<FStructProperty> { using Type = UE::FStructPropertyBinding; };`
- L397 _public typedef_ `template<> struct TCustomBind<FClassProperty> { using Type = UE::FClassPropertyBinding; };`
- L398 _public typedef_ `template<> struct TCustomBind<FObjectPropertyBase> { using Type = UE::FObjectPropertyBaseBinding; };`
- L399 _public typedef_ `template<> struct TCustomBind<FArrayProperty> { using Type = UE::FArrayPropertyBinding; };`
- L402 _public typedef_ `template<> struct TCustomBind<UStruct> { using Type = UE::UStructBinding; };` — custom UField meta bindings

#### struct `PlainProps::TCustomBind`  
`template<> struct TCustomBind<FProperty>`  
_L391-391_
- desc: custom FProperty meta bindings
- L389 _public typedef_ `template<> struct TCustomBind<FProperty> { using Type = UE::FPropertyBinding; };` — custom FProperty meta bindings
- L393 _public typedef_ `template<> struct TCustomBind<FEnumProperty> { using Type = UE::FEnumPropertyBinding; };`
- L394 _public typedef_ `template<> struct TCustomBind<FBoolProperty> { using Type = UE::FBoolPropertyBinding; };`
- L395 _public typedef_ `template<> struct TCustomBind<FByteProperty> { using Type = UE::FBytePropertyBinding; };`
- L396 _public typedef_ `template<> struct TCustomBind<FStructProperty> { using Type = UE::FStructPropertyBinding; };`
- L397 _public typedef_ `template<> struct TCustomBind<FClassProperty> { using Type = UE::FClassPropertyBinding; };`
- L398 _public typedef_ `template<> struct TCustomBind<FObjectPropertyBase> { using Type = UE::FObjectPropertyBaseBinding; };`
- L399 _public typedef_ `template<> struct TCustomBind<FArrayProperty> { using Type = UE::FArrayPropertyBinding; };`
- L402 _public typedef_ `template<> struct TCustomBind<UStruct> { using Type = UE::UStructBinding; };` — custom UField meta bindings

#### struct `PlainProps::TCustomBind`  
`template<> struct TCustomBind<FProperty>`  
_L392-392_
- desc: custom FProperty meta bindings
- L389 _public typedef_ `template<> struct TCustomBind<FProperty> { using Type = UE::FPropertyBinding; };` — custom FProperty meta bindings
- L393 _public typedef_ `template<> struct TCustomBind<FEnumProperty> { using Type = UE::FEnumPropertyBinding; };`
- L394 _public typedef_ `template<> struct TCustomBind<FBoolProperty> { using Type = UE::FBoolPropertyBinding; };`
- L395 _public typedef_ `template<> struct TCustomBind<FByteProperty> { using Type = UE::FBytePropertyBinding; };`
- L396 _public typedef_ `template<> struct TCustomBind<FStructProperty> { using Type = UE::FStructPropertyBinding; };`
- L397 _public typedef_ `template<> struct TCustomBind<FClassProperty> { using Type = UE::FClassPropertyBinding; };`
- L398 _public typedef_ `template<> struct TCustomBind<FObjectPropertyBase> { using Type = UE::FObjectPropertyBaseBinding; };`
- L399 _public typedef_ `template<> struct TCustomBind<FArrayProperty> { using Type = UE::FArrayPropertyBinding; };`
- L402 _public typedef_ `template<> struct TCustomBind<UStruct> { using Type = UE::UStructBinding; };` — custom UField meta bindings

#### struct `PlainProps::TCustomBind`  
`template<> struct TCustomBind<FEnumProperty>`  
_L393-393_
- L389 _public typedef_ `template<> struct TCustomBind<FProperty> { using Type = UE::FPropertyBinding; };` — custom FProperty meta bindings
- L393 _public typedef_ `template<> struct TCustomBind<FEnumProperty> { using Type = UE::FEnumPropertyBinding; };`
- L394 _public typedef_ `template<> struct TCustomBind<FBoolProperty> { using Type = UE::FBoolPropertyBinding; };`
- L395 _public typedef_ `template<> struct TCustomBind<FByteProperty> { using Type = UE::FBytePropertyBinding; };`
- L396 _public typedef_ `template<> struct TCustomBind<FStructProperty> { using Type = UE::FStructPropertyBinding; };`
- L397 _public typedef_ `template<> struct TCustomBind<FClassProperty> { using Type = UE::FClassPropertyBinding; };`
- L398 _public typedef_ `template<> struct TCustomBind<FObjectPropertyBase> { using Type = UE::FObjectPropertyBaseBinding; };`
- L399 _public typedef_ `template<> struct TCustomBind<FArrayProperty> { using Type = UE::FArrayPropertyBinding; };`
- L402 _public typedef_ `template<> struct TCustomBind<UStruct> { using Type = UE::UStructBinding; };` — custom UField meta bindings

#### struct `PlainProps::TCustomBind`  
`template<> struct TCustomBind<FBoolProperty>`  
_L394-394_
- L389 _public typedef_ `template<> struct TCustomBind<FProperty> { using Type = UE::FPropertyBinding; };` — custom FProperty meta bindings
- L393 _public typedef_ `template<> struct TCustomBind<FEnumProperty> { using Type = UE::FEnumPropertyBinding; };`
- L394 _public typedef_ `template<> struct TCustomBind<FBoolProperty> { using Type = UE::FBoolPropertyBinding; };`
- L395 _public typedef_ `template<> struct TCustomBind<FByteProperty> { using Type = UE::FBytePropertyBinding; };`
- L396 _public typedef_ `template<> struct TCustomBind<FStructProperty> { using Type = UE::FStructPropertyBinding; };`
- L397 _public typedef_ `template<> struct TCustomBind<FClassProperty> { using Type = UE::FClassPropertyBinding; };`
- L398 _public typedef_ `template<> struct TCustomBind<FObjectPropertyBase> { using Type = UE::FObjectPropertyBaseBinding; };`
- L399 _public typedef_ `template<> struct TCustomBind<FArrayProperty> { using Type = UE::FArrayPropertyBinding; };`
- L402 _public typedef_ `template<> struct TCustomBind<UStruct> { using Type = UE::UStructBinding; };` — custom UField meta bindings

#### struct `PlainProps::TCustomBind`  
`template<> struct TCustomBind<FByteProperty>`  
_L395-395_
- L389 _public typedef_ `template<> struct TCustomBind<FProperty> { using Type = UE::FPropertyBinding; };` — custom FProperty meta bindings
- L393 _public typedef_ `template<> struct TCustomBind<FEnumProperty> { using Type = UE::FEnumPropertyBinding; };`
- L394 _public typedef_ `template<> struct TCustomBind<FBoolProperty> { using Type = UE::FBoolPropertyBinding; };`
- L395 _public typedef_ `template<> struct TCustomBind<FByteProperty> { using Type = UE::FBytePropertyBinding; };`
- L396 _public typedef_ `template<> struct TCustomBind<FStructProperty> { using Type = UE::FStructPropertyBinding; };`
- L397 _public typedef_ `template<> struct TCustomBind<FClassProperty> { using Type = UE::FClassPropertyBinding; };`
- L398 _public typedef_ `template<> struct TCustomBind<FObjectPropertyBase> { using Type = UE::FObjectPropertyBaseBinding; };`
- L399 _public typedef_ `template<> struct TCustomBind<FArrayProperty> { using Type = UE::FArrayPropertyBinding; };`
- L402 _public typedef_ `template<> struct TCustomBind<UStruct> { using Type = UE::UStructBinding; };` — custom UField meta bindings

#### struct `PlainProps::TCustomBind`  
`template<> struct TCustomBind<FStructProperty>`  
_L396-396_
- L389 _public typedef_ `template<> struct TCustomBind<FProperty> { using Type = UE::FPropertyBinding; };` — custom FProperty meta bindings
- L393 _public typedef_ `template<> struct TCustomBind<FEnumProperty> { using Type = UE::FEnumPropertyBinding; };`
- L394 _public typedef_ `template<> struct TCustomBind<FBoolProperty> { using Type = UE::FBoolPropertyBinding; };`
- L395 _public typedef_ `template<> struct TCustomBind<FByteProperty> { using Type = UE::FBytePropertyBinding; };`
- L396 _public typedef_ `template<> struct TCustomBind<FStructProperty> { using Type = UE::FStructPropertyBinding; };`
- L397 _public typedef_ `template<> struct TCustomBind<FClassProperty> { using Type = UE::FClassPropertyBinding; };`
- L398 _public typedef_ `template<> struct TCustomBind<FObjectPropertyBase> { using Type = UE::FObjectPropertyBaseBinding; };`
- L399 _public typedef_ `template<> struct TCustomBind<FArrayProperty> { using Type = UE::FArrayPropertyBinding; };`
- L402 _public typedef_ `template<> struct TCustomBind<UStruct> { using Type = UE::UStructBinding; };` — custom UField meta bindings

#### struct `PlainProps::TCustomBind`  
`template<> struct TCustomBind<FClassProperty>`  
_L397-397_
- L389 _public typedef_ `template<> struct TCustomBind<FProperty> { using Type = UE::FPropertyBinding; };` — custom FProperty meta bindings
- L393 _public typedef_ `template<> struct TCustomBind<FEnumProperty> { using Type = UE::FEnumPropertyBinding; };`
- L394 _public typedef_ `template<> struct TCustomBind<FBoolProperty> { using Type = UE::FBoolPropertyBinding; };`
- L395 _public typedef_ `template<> struct TCustomBind<FByteProperty> { using Type = UE::FBytePropertyBinding; };`
- L396 _public typedef_ `template<> struct TCustomBind<FStructProperty> { using Type = UE::FStructPropertyBinding; };`
- L397 _public typedef_ `template<> struct TCustomBind<FClassProperty> { using Type = UE::FClassPropertyBinding; };`
- L398 _public typedef_ `template<> struct TCustomBind<FObjectPropertyBase> { using Type = UE::FObjectPropertyBaseBinding; };`
- L399 _public typedef_ `template<> struct TCustomBind<FArrayProperty> { using Type = UE::FArrayPropertyBinding; };`
- L402 _public typedef_ `template<> struct TCustomBind<UStruct> { using Type = UE::UStructBinding; };` — custom UField meta bindings

#### struct `PlainProps::TCustomBind`  
`template<> struct TCustomBind<FObjectPropertyBase>`  
_L398-398_
- L389 _public typedef_ `template<> struct TCustomBind<FProperty> { using Type = UE::FPropertyBinding; };` — custom FProperty meta bindings
- L393 _public typedef_ `template<> struct TCustomBind<FEnumProperty> { using Type = UE::FEnumPropertyBinding; };`
- L394 _public typedef_ `template<> struct TCustomBind<FBoolProperty> { using Type = UE::FBoolPropertyBinding; };`
- L395 _public typedef_ `template<> struct TCustomBind<FByteProperty> { using Type = UE::FBytePropertyBinding; };`
- L396 _public typedef_ `template<> struct TCustomBind<FStructProperty> { using Type = UE::FStructPropertyBinding; };`
- L397 _public typedef_ `template<> struct TCustomBind<FClassProperty> { using Type = UE::FClassPropertyBinding; };`
- L398 _public typedef_ `template<> struct TCustomBind<FObjectPropertyBase> { using Type = UE::FObjectPropertyBaseBinding; };`
- L399 _public typedef_ `template<> struct TCustomBind<FArrayProperty> { using Type = UE::FArrayPropertyBinding; };`
- L402 _public typedef_ `template<> struct TCustomBind<UStruct> { using Type = UE::UStructBinding; };` — custom UField meta bindings

#### struct `PlainProps::TCustomBind`  
`template<> struct TCustomBind<FArrayProperty>`  
_L399-399_
- L389 _public typedef_ `template<> struct TCustomBind<FProperty> { using Type = UE::FPropertyBinding; };` — custom FProperty meta bindings
- L393 _public typedef_ `template<> struct TCustomBind<FEnumProperty> { using Type = UE::FEnumPropertyBinding; };`
- L394 _public typedef_ `template<> struct TCustomBind<FBoolProperty> { using Type = UE::FBoolPropertyBinding; };`
- L395 _public typedef_ `template<> struct TCustomBind<FByteProperty> { using Type = UE::FBytePropertyBinding; };`
- L396 _public typedef_ `template<> struct TCustomBind<FStructProperty> { using Type = UE::FStructPropertyBinding; };`
- L397 _public typedef_ `template<> struct TCustomBind<FClassProperty> { using Type = UE::FClassPropertyBinding; };`
- L398 _public typedef_ `template<> struct TCustomBind<FObjectPropertyBase> { using Type = UE::FObjectPropertyBaseBinding; };`
- L399 _public typedef_ `template<> struct TCustomBind<FArrayProperty> { using Type = UE::FArrayPropertyBinding; };`
- L402 _public typedef_ `template<> struct TCustomBind<UStruct> { using Type = UE::UStructBinding; };` — custom UField meta bindings

#### struct `PlainProps::TCustomBind`  
`template<> struct TCustomBind<UStruct>`  
_L402-402_
- desc: custom UField meta bindings
- L389 _public typedef_ `template<> struct TCustomBind<FProperty> { using Type = UE::FPropertyBinding; };` — custom FProperty meta bindings
- L393 _public typedef_ `template<> struct TCustomBind<FEnumProperty> { using Type = UE::FEnumPropertyBinding; };`
- L394 _public typedef_ `template<> struct TCustomBind<FBoolProperty> { using Type = UE::FBoolPropertyBinding; };`
- L395 _public typedef_ `template<> struct TCustomBind<FByteProperty> { using Type = UE::FBytePropertyBinding; };`
- L396 _public typedef_ `template<> struct TCustomBind<FStructProperty> { using Type = UE::FStructPropertyBinding; };`
- L397 _public typedef_ `template<> struct TCustomBind<FClassProperty> { using Type = UE::FClassPropertyBinding; };`
- L398 _public typedef_ `template<> struct TCustomBind<FObjectPropertyBase> { using Type = UE::FObjectPropertyBaseBinding; };`
- L399 _public typedef_ `template<> struct TCustomBind<FArrayProperty> { using Type = UE::FArrayPropertyBinding; };`
- L402 _public typedef_ `template<> struct TCustomBind<UStruct> { using Type = UE::UStructBinding; };` — custom UField meta bindings

#### struct `PlainProps::TCustomBind`  
`template<> struct TCustomBind<UStruct>`  
_L403-403_
- desc: custom UField meta bindings
- L389 _public typedef_ `template<> struct TCustomBind<FProperty> { using Type = UE::FPropertyBinding; };` — custom FProperty meta bindings
- L393 _public typedef_ `template<> struct TCustomBind<FEnumProperty> { using Type = UE::FEnumPropertyBinding; };`
- L394 _public typedef_ `template<> struct TCustomBind<FBoolProperty> { using Type = UE::FBoolPropertyBinding; };`
- L395 _public typedef_ `template<> struct TCustomBind<FByteProperty> { using Type = UE::FBytePropertyBinding; };`
- L396 _public typedef_ `template<> struct TCustomBind<FStructProperty> { using Type = UE::FStructPropertyBinding; };`
- L397 _public typedef_ `template<> struct TCustomBind<FClassProperty> { using Type = UE::FClassPropertyBinding; };`
- L398 _public typedef_ `template<> struct TCustomBind<FObjectPropertyBase> { using Type = UE::FObjectPropertyBaseBinding; };`
- L399 _public typedef_ `template<> struct TCustomBind<FArrayProperty> { using Type = UE::FArrayPropertyBinding; };`
- L402 _public typedef_ `template<> struct TCustomBind<UStruct> { using Type = UE::UStructBinding; };` — custom UField meta bindings

#### struct `PlainProps::TCustomBind`  
`template<> struct TCustomBind<UStruct>`  
_L404-404_
- desc: custom UField meta bindings
- L389 _public typedef_ `template<> struct TCustomBind<FProperty> { using Type = UE::FPropertyBinding; };` — custom FProperty meta bindings
- L393 _public typedef_ `template<> struct TCustomBind<FEnumProperty> { using Type = UE::FEnumPropertyBinding; };`
- L394 _public typedef_ `template<> struct TCustomBind<FBoolProperty> { using Type = UE::FBoolPropertyBinding; };`
- L395 _public typedef_ `template<> struct TCustomBind<FByteProperty> { using Type = UE::FBytePropertyBinding; };`
- L396 _public typedef_ `template<> struct TCustomBind<FStructProperty> { using Type = UE::FStructPropertyBinding; };`
- L397 _public typedef_ `template<> struct TCustomBind<FClassProperty> { using Type = UE::FClassPropertyBinding; };`
- L398 _public typedef_ `template<> struct TCustomBind<FObjectPropertyBase> { using Type = UE::FObjectPropertyBaseBinding; };`
- L399 _public typedef_ `template<> struct TCustomBind<FArrayProperty> { using Type = UE::FArrayPropertyBinding; };`
- L402 _public typedef_ `template<> struct TCustomBind<UStruct> { using Type = UE::UStructBinding; };` — custom UField meta bindings

#### struct `PlainProps::TCustomBind`  
`template<> struct TCustomBind<UStruct>`  
_L405-405_
- desc: custom UField meta bindings
- L389 _public typedef_ `template<> struct TCustomBind<FProperty> { using Type = UE::FPropertyBinding; };` — custom FProperty meta bindings
- L393 _public typedef_ `template<> struct TCustomBind<FEnumProperty> { using Type = UE::FEnumPropertyBinding; };`
- L394 _public typedef_ `template<> struct TCustomBind<FBoolProperty> { using Type = UE::FBoolPropertyBinding; };`
- L395 _public typedef_ `template<> struct TCustomBind<FByteProperty> { using Type = UE::FBytePropertyBinding; };`
- L396 _public typedef_ `template<> struct TCustomBind<FStructProperty> { using Type = UE::FStructPropertyBinding; };`
- L397 _public typedef_ `template<> struct TCustomBind<FClassProperty> { using Type = UE::FClassPropertyBinding; };`
- L398 _public typedef_ `template<> struct TCustomBind<FObjectPropertyBase> { using Type = UE::FObjectPropertyBaseBinding; };`
- L399 _public typedef_ `template<> struct TCustomBind<FArrayProperty> { using Type = UE::FArrayPropertyBinding; };`
- L402 _public typedef_ `template<> struct TCustomBind<UStruct> { using Type = UE::UStructBinding; };` — custom UField meta bindings

#### struct `PlainProps::TOccupancyOf`  
`template<> struct TOccupancyOf<FImplementedInterface> : FRequireAll`  
_L408-408_
- inherits: `FRequireAll`
- desc: traits for aux bindings

#### Free symbols / members of external scopes

- L11 _macro_ `#define _PP_MEMBER_ID(N, NS, T, M) Ids::IndexMember(#M),`
- L13 _macro_ `#define _PP_CUSTOM_BIND_MEMBERS(N, ...) \`
- L21 _macro_ `#define UE_CUSTOM_BIND_MEMBERS(T, ...) \` — Temporary UE_CUSTOM_BIND_MEMBERS macro that eliminates the manual hassle of of sizing arrays, indexing names and keeping track of indices when modifying custom bindings. Todo: Handle Name-Spec pairs and interleaving of custom members with schema members.
- L29 _macro_ `#define PP_OVERRIDE_OBJECT_LOADING 0` — Temporary macro to switch between property override loading and object override loading
- L195 _namespace_ `namespace PlainProps`
- L195 _namespace_ `namespace UE` (scope `PlainProps`)
- L201 _prototype_ `void BindStruct(FBindId Id, const UStruct* Struct);` (scope `PlainProps::UE`) — Todo: Move back to PlainPropsUObjectBindingsInternal.h, where it is used to bind dynamic structs as they are being loaded. It is temporarily exposed here for allowing duplication of a UStruct binding with a different bind id.
- L386 _namespace_ `namespace PlainProps`
- L409 _function_ `template<> struct TOccupancyOf<FImplementedInterface> : FRequireAll` (scope `PlainProps`) — traits for aux bindings

### `Plugins/Experimental/PlainPropsUObject/Source/Private/PlainPropsRestoreOverridableInternal.h` (Private)


#### struct `PlainProps::UE::FRestoreContext`  
`struct FRestoreContext`  
_L24-30_
- L26 _public member_ `const FSchemaBindings& Schemas;`
- L27 _public member_ `FCustomBindings& Customs;`
- L28 _public member_ `const FMetadataBindings& Metadatas;`
- L29 _public member_ `TConstArrayView<FStructId> RuntimeIds;`

#### class `PlainProps::UE::FScopeRestoreOverrides`  
`class FScopeRestoreOverrides`  
_L36-44_
- L39 _public prototype_ `FScopeRestoreOverrides(FOverriddenPropertySet* OverriddenProperties);`
- L40 _public prototype_ `~FScopeRestoreOverrides();`
- L43 _private member_ `FOverriddenPropertySet* PrevOverrides;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace PlainProps`
- L19 _namespace_ `namespace PlainProps`
- L19 _namespace_ `namespace UE` (scope `PlainProps`)
- L32 _prototype_ `void RestoreStructOverrides(const UStruct* Struct, FStructView StructView, FOverriddenPropertySet& Overrides, const FRestoreContext& Ctx);` (scope `PlainProps::UE`)
- L34 _prototype_ `void ResetOverriddenPropertyNode(FOverriddenPropertyNode& Node, EOverriddenPropertyOperation Op, TArray<FOverriddenPropertyNode> SubPropertyNodes = TArray<FOverriddenPropertyNode>());` (scope `PlainProps::UE`)
- L46 _prototype_ `FOverriddenPropertySet* GetRestoreOverrides();` (scope `PlainProps::UE`)

### `Plugins/Experimental/PlainPropsUObject/Source/Private/PlainPropsSaveOverridableInternal.h` (Private)


#### Free symbols / members of external scopes

- L11 _namespace_ `namespace PlainProps`
- L14 _namespace_ `namespace UE` (scope `PlainProps`)
- L17 _prototype_ `FName GetOverridePropertyName(const FOverriddenPropertyNode& Override);` (scope `PlainProps::UE`)
- L19 _prototype_ `FBuiltStruct* SaveStructOverrides(const FOverriddenPropertySet& Overrides, FBaseline Base, FBindId BindId, const FSaveContext& Context);` (scope `PlainProps::UE`)
- L21 _prototype_ `const FOverriddenPropertySet* GetSaveOverrides();` (scope `PlainProps::UE`)

### `Plugins/Experimental/PlainPropsUObject/Source/Private/PlainPropsUObjectBindingsInternal.h` (Private)


#### Free symbols / members of external scopes

- L9 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogPlainPropsUObject, Log, All);`
- L9 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogPlainPropsUObject, Log, All);`
- L14 _namespace_ `namespace PlainProps`
- L16 _namespace_ `namespace PlainProps`
- L16 _namespace_ `namespace UE` (scope `PlainProps`)
- L19 _prototype_ `FType IndexStruct(const UStruct* Struct);` (scope `PlainProps::UE`)
- L20 _prototype_ `bool ShouldBind(const UStruct* Struct);` (scope `PlainProps::UE`)
- L21 _prototype_ `const UStruct* SkipEmptyBases(const UStruct* Struct);` (scope `PlainProps::UE`)
- L24 _prototype_ `FType IndexStructMeta(const UStruct* Struct);` (scope `PlainProps::UE`) — Helpers for native UField and FProperty meta bindings
- L25 _prototype_ `void BindStructMeta(FBindId Id, const UStruct* Struct);` (scope `PlainProps::UE`)
- L26 _prototype_ `FDualStructId IndexPropertyMeta(const FField* Property);` (scope `PlainProps::UE`)

### `Plugins/Experimental/PlainPropsUObject/Source/Private/PlainPropsUObjectDiffInternal.h` (Private)


#### enum `PlainProps::UE::EDiffObjectNodeType`  
`enum class EDiffObjectNodeType : uint8`  
_L23-35_
- L25 _public enumerator_ `NotInA` — An object under RootB is missing in RootA
- L26 _public enumerator_ `NotInB` — An object under RootA is missing in RootB
- L27 _public enumerator_ `Class` — Two object pointers A and B are different if:
- L29 _public enumerator_ `Object` — - both are set but the UClass is different, i.e. A->GetClass() != B->GetClass()
- L34 _public enumerator_ `Property` — - only one of them is null, i.e. (A==nullptr != B==nullptr) - only one of them is an internal reference, i.e. (A->IsIn(RootA) != B->IsIn(RootB)) - both are internal references but the relative paths inside their roots are different - both are external references and they have member properties with different values.

#### struct `PlainProps::UE::FDiffObjectNode`  
`struct FDiffObjectNode`  
_L37-54_
- L39 _public member_ `EDiffObjectNodeType Type;`
- L40 _public member_ `const void* A;`
- L41 _public member_ `const void* B;`
- L42 _public member_ `const void* TypePtr = nullptr;`
- L43 _public member_ `uint64 Idx = ~0ull;`
- L45 _public function_ `const FProperty* GetProperty() const`
- L50 _public function_ `const UClass* GetClass() const`

#### struct `PlainProps::UE::FDiffOverride`  
`struct FDiffOverride`  
_L56-60_
- L58 _public member_ `const UObject* A;`
- L59 _public member_ `const UObject* B;`

#### struct `PlainProps::UE::FDiffObjectFilter`  
`struct FDiffObjectFilter`  
_L62-74_
- L65 _public member_ `TSet<FName> BypassNativeIdenticalStructs;` — Structs for which to bypass the native identical function
- L67 _public member_ `TSet<FName> IgnoreStructs;` — Structs for which to ignore any diffs
- L69 _public member_ `TSet<TPair<FName, FName>> IgnorePropertiesForStructs;` — Struct specific properties for which to ignore any diffs
- L71 _public member_ `TMap<FName, FName> IgnorePropertiesForBases;` — Base class properties for which to ignore any diffs (more expensive to check)
- L73 _public member_ `uint64 IgnoreCastFlags = 0;` — Cast flags for properties for which to ignore any diffs

#### struct `PlainProps::UE::FDiffObjectContext`  
`struct FDiffObjectContext`  
_L76-90_
- L79 _public member_ `const UObject* const RootA = nullptr;` — in
- L80 _public member_ `const UObject* const RootB = nullptr;`
- L81 _public member_ `const FDiffObjectFilter& Filter;`
- L84 _public member_ `TSet<TPair<const UObject*, const UObject*>> Visited;` — temporary data structures
- L87 _public member_ `TArray<FDiffObjectNode> Diffs;` — out
- L88 _public member_ `TArray<FDiffOverride> OverrideDiffs;`
- L89 _public member_ `uint32 NumIgnoredDiffs = 0;`

#### Free symbols / members of external scopes

- L20 _namespace_ `namespace PlainProps`
- L20 _namespace_ `namespace UE` (scope `PlainProps`)
- L92 _prototype_ `bool DiffObjects(FDiffObjectContext& Ctx);` (scope `PlainProps::UE`)
- L94 _prototype_ `void PrintDiff(FUtf8StringBuilderBase& Out, FDiffObjectContext& Ctx);` (scope `PlainProps::UE`)

### `Plugins/Experimental/PlainPropsUObject/Source/Public/PlainPropsRoundtripTest.h` (Public)


#### enum `PlainProps::UE::EBindMode`  
`enum class EBindMode : uint8`  
_L17-17_
- L17 _public enumerator_ `enum class EBindMode : uint8 { All, Source, Runtime }; enum class EBatchType : uint8 { Plain, Linker} ; enum class ERoundtrip : uint8 { None = 0, PP = 1 << 0,`
- L17 _public enumerator_ `enum class EBindMode : uint8 { All, Source, Runtime }; enum class EBatchType : uint8 { Plain, Linker} ; enum class ERoundtrip : uint8 { None = 0, PP = 1 << 0,`
- L17 _public enumerator_ `enum class EBindMode : uint8 { All, Source, Runtime }; enum class EBatchType : uint8 { Plain, Linker} ; enum class ERoundtrip : uint8 { None = 0, PP = 1 << 0,`

#### enum `PlainProps::UE::EBatchType`  
`enum class EBatchType : uint8`  
_L19-19_
- desc: todo: Iostore, Zen
- L19 _public enumerator_ `enum class EBatchType : uint8 { Plain, Linker} ; enum class ERoundtrip : uint8 { None = 0, PP = 1 << 0, TPS = 1 << 1, UPS = 1 << 2,` — todo: Iostore, Zen
- L19 _public enumerator_ `enum class EBatchType : uint8 { Plain, Linker} ; enum class ERoundtrip : uint8 { None = 0, PP = 1 << 0, TPS = 1 << 1, UPS = 1 << 2,` — todo: Iostore, Zen

#### enum `PlainProps::UE::ERoundtrip`  
`enum class ERoundtrip : uint8`  
_L21-30_
- L23 _public enumerator_ `None = 0`
- L24 _public enumerator_ `PP = 1 << 0`
- L25 _public enumerator_ `TPS = 1 << 1`
- L26 _public enumerator_ `UPS = 1 << 2`
- L27 _public enumerator_ `TextMemory = 1 << 3`
- L28 _public enumerator_ `TextStable = 1 << 4`
- L29 _public enumerator_ `JSON = 1 << 5`

#### struct `PlainProps::UE::FLinkerDiffFilter`  
`struct FLinkerDiffFilter`  
_L33-45_
- L36 _public member_ `TSet<FName> BypassNativeIdenticalStructs;` — Structs for which to bypass the native identical function
- L38 _public member_ `TSet<FName> IgnoreStructs;` — Structs for which to ignore any diffs
- L40 _public member_ `TSet<TPair<FName, FName>> IgnorePropertiesForStructs;` — Struct specific properties for which to ignore any diffs
- L42 _public member_ `TMap<FName, FName> IgnorePropertiesForBases;` — Base class properties for which to ignore any diffs (more expensive to check)
- L44 _public member_ `uint64 IgnoreCastFlags = 0;` — Cast flags for properties for which to ignore any diffs

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace PlainProps`
- L14 _namespace_ `namespace UE` (scope `PlainProps`)
- L31 _prototype_ `ENUM_CLASS_FLAGS(ERoundtrip);` (scope `PlainProps::UE`)
- L47 _typedef_ `using FDropPackagesFunc = void (*)(TArray<UPackage*>&&, int32);` (scope `PlainProps::UE`)
- L49 _prototype_ `void SchemaBindAllTypes(EBindMode Mode, EBatchType BatchType);` (scope `PlainProps::UE`)
- L50 _prototype_ `int32 RoundtripViaPlainBatch(TConstArrayView<UObject*> Objects, ERoundtrip Options);` (scope `PlainProps::UE`)
- L51 _prototype_ `int32 RoundtripViaLinkerBatch( TConstArrayView<UObject*> Objects, ERoundtrip Options, const FLinkerDiffFilter& DiffFilter, FDropPackagesFunc DropPackagesFunc);` (scope `PlainProps::UE`)
- L57 _prototype_ `bool SaveTestPackage(UPackage* Package, const FString& Filename, const FSavePackageArgs& SaveArgs);` (scope `PlainProps::UE`)
- L58 _prototype_ `UPackage* LoadTestPackage(const FString& Filename);` (scope `PlainProps::UE`)

### `Plugins/Experimental/PlainPropsUObject/Source/Public/PlainPropsUObjectModule.h` (Public)


#### class `FPlainPropsUObjectModule`  
`class FPlainPropsUObjectModule final : public IModuleInterface`  
_L7-11_
- inherits: `IModuleInterface`
- L9 _private prototype_ `virtual void StartupModule();`
- L10 _private prototype_ `virtual void ShutdownModule();`

### `Plugins/Experimental/PlainPropsUObject/Source/Public/PlainPropsUObjectRuntime.h` (Public)


#### struct `PlainProps::UE::FDefaultInstance`  
`struct FDefaultInstance`  
_L24-24_
- L24 _public member_ `struct FDefaultInstance { uint64 Ptr; };`

#### class `PlainProps::UE::FDefaultStructs`  
`class FDefaultStructs final : public IDefaultStructs`  
_L26-48_
- inherits: `IDefaultStructs`
- L29 _public prototype_ `~FDefaultStructs();`
- L30 _public prototype_ `void Bind(FBindId Id, const UScriptStruct* Struct);`
- L31 _public prototype_ `void BindZeroes(FBindId Id, SIZE_T Size, uint32 Alignment);`
- L32 _public prototype_ `void BindStatic(FBindId Id, const void* Struct);`
- L33 _public prototype_ `void Drop(FBindId Id);`
- L34 _public prototype_ `virtual const void* Get(FBindId Id) override;`
- L37 _public function_ `template<class T> void BindZeroes(FBindId Id)`
- L40 _private member_ `FMutableMemoryView Zeroes;`
- L41 _private member_ `TBitArray<> Instanced;`
- L42 _private member_ `TMap<FBindId, FDefaultInstance> Instances;`
- L44 _private member_ `TBitArray<> Bound;`
- L47 _private prototype_ `void ReserveFlags(uint32 Idx);`

#### struct `PlainProps::UE::FCommonScopeIds`  
`struct FCommonScopeIds`  
_L50-56_
- L52 _public prototype_ `explicit FCommonScopeIds(TIdIndexer<FSensitiveName>& Names);`
- L54 _public member_ `FScopeId CoreUObject;`
- L55 _public member_ `FScopeId Engine;` — Move out?

#### struct `PlainProps::UE::FCommonTypenameIds`  
`struct FCommonTypenameIds`  
_L58-77_
- L60 _public prototype_ `explicit FCommonTypenameIds(TIdIndexer<FSensitiveName>& Names);`
- L62 _public member_ `FConcreteTypenameId Optional;`
- L63 _public member_ `FConcreteTypenameId Map;`
- L64 _public member_ `FConcreteTypenameId Set;`
- L65 _public member_ `FConcreteTypenameId Pair;`
- L66 _public member_ `FConcreteTypenameId LeafArray;`
- L67 _public member_ `FConcreteTypenameId TrivialArray;`
- L68 _public member_ `FConcreteTypenameId NonTrivialArray;`
- L69 _public member_ `FConcreteTypenameId StaticArray;`
- L70 _public member_ `FConcreteTypenameId TrivialOptional;`
- L71 _public member_ `FConcreteTypenameId IntrusiveOptional;`
- L72 _public member_ `FConcreteTypenameId NonIntrusiveOptional;`
- L73 _public member_ `FConcreteTypenameId String;`
- L74 _public member_ `FConcreteTypenameId Utf8String;`
- L75 _public member_ `FConcreteTypenameId AnsiString;`
- L76 _public member_ `FConcreteTypenameId VerseString;`

#### struct `PlainProps::UE::FCommonEnumIds`  
`struct FCommonEnumIds`  
_L79-84_
- L81 _public prototype_ `explicit FCommonEnumIds(const FCommonScopeIds& Scopes, TIdIndexer<FSensitiveName>& Names);`
- L83 _public member_ `FEnumId PixelFormat;`

#### struct `PlainProps::UE::FCommonPropertyStructIds`  
`struct FCommonPropertyStructIds`  
_L86-101_
- L88 _public prototype_ `explicit FCommonPropertyStructIds(const FCommonScopeIds& Scopes, TIdIndexer<FSensitiveName>& Names);`
- L90 _public member_ `FDualStructId Property;`
- L91 _public member_ `FDualStructId EnumProperty;`
- L92 _public member_ `FDualStructId BoolProperty;`
- L93 _public member_ `FDualStructId ByteProperty;`
- L94 _public member_ `FDualStructId StructProperty;`
- L95 _public member_ `FDualStructId ClassProperty;`
- L96 _public member_ `FDualStructId ObjectPropertyBase;`
- L97 _public member_ `FDualStructId ArrayProperty;`
- L98 _public member_ `FDualStructId SetProperty;`
- L99 _public member_ `FDualStructId MapProperty;`
- L100 _public member_ `FDualStructId OptionalProperty;`

#### struct `PlainProps::UE::FCommonStructIds`  
`struct FCommonStructIds`  
_L103-131_
- L105 _public prototype_ `explicit FCommonStructIds(const FCommonScopeIds& Scopes, TIdIndexer<FSensitiveName>& Names);`
- L107 _public member_ `FDualStructId Name;`
- L108 _public member_ `FDualStructId Text;`
- L109 _public member_ `FDualStructId Guid;`
- L110 _public member_ `FDualStructId FieldPath;`
- L111 _public member_ `FDualStructId Struct;`
- L112 _public member_ `FDualStructId Class;`
- L113 _public member_ `FDualStructId Function;`
- L114 _public member_ `FDualStructId ScriptStruct;`
- L115 _public member_ `FDualStructId SoftObjectPath;`
- L116 _public member_ `FDualStructId ClassPtr;`
- L117 _public member_ `FDualStructId ObjectPtr;`
- L118 _public member_ `FDualStructId WeakObjectPtr;`
- L119 _public member_ `FDualStructId LazyObjectPtr;`
- L120 _public member_ `FDualStructId SoftObjectPtr;`
- L121 _public member_ `FDualStructId ScriptInterface;`
- L122 _public member_ `FDualStructId Delegate;`
- L123 _public member_ `FDeclId MulticastDelegate;`
- L124 _public member_ `FBindId MulticastInlineDelegate;`
- L125 _public member_ `FDualStructId MulticastSparseDelegate;`
- L126 _public member_ `FDualStructId VerseFunction;`
- L127 _public member_ `FDualStructId DynamicallyTypedValue;`
- L128 _public member_ `FDualStructId ReferencePropertyValue;`
- L129 _public member_ `FDualStructId PropertyBag;`
- L130 _public member_ `FDualStructId InstancedStruct;`

#### struct `PlainProps::UE::FCommonMemberIds`  
`struct FCommonMemberIds`  
_L133-149_
- L135 _public prototype_ `explicit FCommonMemberIds(TIdIndexer<FSensitiveName>& Names);`
- L137 _public member_ `FMemberId Key;`
- L138 _public member_ `FMemberId Value;`
- L139 _public member_ `FMemberId Assign;`
- L140 _public member_ `FMemberId Remove;`
- L141 _public member_ `FMemberId Insert;`
- L142 _public member_ `FMemberId Modify;`
- L143 _public member_ `FMemberId Id;`
- L144 _public member_ `FMemberId Object;`
- L145 _public member_ `FMemberId Function;`
- L146 _public member_ `FMemberId Invocations;`
- L147 _public member_ `FMemberId Path;`
- L148 _public member_ `FMemberId Owner;`

#### struct `PlainProps::UE::FDynamicIds`  
`struct FDynamicIds`  
_L153-172_
- desc: temporary non-intrusive mapping from UEnum->FEnumId and UStruct->FBindId, these ids will be owned directly by UEnum and UStruct in a future integration
- L155 _public function_ `void AddEnum(const UEnum* Enum, FEnumId Id)`
- L156 _public function_ `void AddStruct(const UStruct* Struct, FBindId Id)`
- L166 _public function_ `FEnumId GetEnum(const UEnum* Enum) const`
- L167 _public function_ `FDualStructId GetStruct(const UStruct* Struct) const`
- L170 _private member_ `TMap<const UEnum*, FEnumId> Enums;`
- L171 _private member_ `TMap<const UStruct*, FDualStructId> Structs;`

#### struct `PlainProps::UE::FMemberMetadata`  
`struct FMemberMetadata`  
_L174-180_
- L176 _public function_ `bool IsValid() const`
- L177 _public function_ `void Reset()`
- L179 _public member_ `TArray<EPropertyFlags> Flags;`

#### struct `PlainProps::UE::FMetadataBindings`  
`struct FMetadataBindings`  
_L182-194_
- L184 _public function_ `explicit FMetadataBindings(FDebugIds In) : Debug(In)`
- L186 _public prototype_ `void BindMetadata(FBindId Id, TConstArrayView<EPropertyFlags> Members);`
- L187 _public prototype_ `void DropMetadata(FBindId Id);`
- L189 _public prototype_ `TConstArrayView<EPropertyFlags> GetMemberFlags(FBindId Id) const;`
- L192 _private member_ `TArray<FMemberMetadata> Metadatas;`
- L193 _private member_ `FDebugIds Debug;`

#### struct `PlainProps::UE::FGlobals`  
`struct FGlobals`  
_L196-216_
- L198 _public prototype_ `FGlobals();`
- L200 _public member_ `TIdIndexer<FSensitiveName> Names;`
- L201 _public member_ `FEnumDeclarations Enums;`
- L202 _public member_ `FSchemaBindings Schemas;`
- L203 _public member_ `FMetadataBindings Metadatas;`
- L204 _public member_ `FCustomBindingsBottom Customs;`
- L205 _public member_ `FDefaultStructs Defaults;`
- L206 _public member_ `FCommonScopeIds Scopes;`
- L207 _public member_ `FCommonEnumIds EnumIds;`
- L208 _public member_ `FCommonStructIds Structs;`
- L209 _public member_ `FCommonPropertyStructIds Properties;`
- L210 _public member_ `FCommonTypenameIds Typenames;`
- L211 _public member_ `FCommonMemberIds Members;`
- L212 _public member_ `FDynamicIds DynamicIds;`
- L213 _public member_ `FNumeralGenerator Numerals;`
- L215 _public member_ `FDebugIds Debug;` — Upgrade::FHistory			Upgrades;

#### struct `PlainProps::UE::FRuntimeIds`  
`struct FRuntimeIds`  
_L219-232_
- L221 _public function_ `static FNameId IndexName(FAnsiStringView Name)`
- L222 _public function_ `static FMemberId IndexMember(FAnsiStringView Name)`
- L223 _public function_ `static FConcreteTypenameId IndexTypename(FAnsiStringView Name)`
- L224 _public function_ `static FFlatScopeId IndexScope(FAnsiStringView Name)`
- L225 _public function_ `static FEnumId IndexEnum(FScopeId Scope, FAnsiStringView Name)`
- L226 _public function_ `static FStructId IndexStruct(FScopeId Scope, FAnsiStringView Name)`
- L227 _public function_ `static FEnumId IndexEnum(FType Type)`
- L228 _public function_ `static FStructId IndexStruct(FType Type)`
- L231 _public function_ `static FIdIndexerBase& GetIndexer()`

#### struct `PlainProps::UE::FDefaultRuntime`  
`struct FDefaultRuntime`  
_L234-243_
- L236 _public typedef_ `using Ids = FRuntimeIds;`
- L237 _public typedef_ `template<class T> using CustomBindings = TCustomBind<T>;`
- L239 _public function_ `static FEnumDeclarations& GetEnums()`
- L240 _public function_ `static FSchemaBindings& GetSchemas()`
- L241 _public function_ `static FCustomBindings& GetCustoms()`
- L242 _public function_ `static IDefaultStructs* GetDefaults()`

#### struct `PlainProps::UE::FDeltaRuntime`  
`struct FDeltaRuntime : FDefaultRuntime`  
_L245-250_
- inherits: `FDefaultRuntime`
- L247 _public typedef_ `template<class T> using CustomBindings = TCustomDeltaBind<T>;`
- L249 _public function_ `static IDefaultStructs* GetDefaults()`

#### struct `PlainProps::UE::TScopedUStructBinding`  
`template<class T, class Runtime, typename CustomBinding> struct TScopedUStructBinding : TScopedStructBinding<T, Runtime, CustomBinding>`  
_L267-272_
- inherits: `TScopedStructBinding<T,Runtime,CustomBinding>`
- desc: Runtime scope to declare and custom bind an override for a schema bound UStruct
- L269 _public function_ `TScopedUStructBinding() : TScopedStructBinding<T, Runtime, CustomBinding>(GUE.DynamicIds.GetStruct(T::StaticStruct()))`

#### struct `PlainProps::UE::TScopedUClassBinding`  
`template<class T, class Runtime, typename CustomBinding> struct TScopedUClassBinding : TScopedStructBinding<T, Runtime, CustomBinding>`  
_L276-281_
- inherits: `TScopedStructBinding<T,Runtime,CustomBinding>`
- desc: Runtime scope to declare and custom bind an override for a schema bound UClass
- L278 _public function_ `TScopedUClassBinding() : TScopedStructBinding<T, Runtime, CustomBinding>(GUE.DynamicIds.GetStruct(T::StaticClass()))`

#### struct `PlainProps::UE::TUEnumAsByteBinding`  
`template <Enumeration E> struct TUEnumAsByteBinding : ICustomBinding`  
_L294-315_
- inherits: `ICustomBinding`
- L296 _public typedef_ `using Type = TEnumAsByte<E>;`
- L298 _public member_ `const FMemberId MemberIds[1];`
- L299 _public member_ `const FEnumId EnumId;`
- L301 _public function_ `TUEnumAsByteBinding(TPropertySpecifier<1>& Spec) : MemberIds`
- L309 _public function_ `void Save(FMemberBuilder& Dst, const TEnumAsByte<E>& Src, const TEnumAsByte<E>* Default, const FSaveContext& Ctx) const`
- L313 _public function_ `static void Plan(FMemcpyLoadPlan& Out)`
- L314 _public function_ `static bool Diff(TEnumAsByte<E> A, TEnumAsByte<E> B, const FBindContext&)`

#### struct `PlainProps::UE::FFieldPathBinding`  
`struct FFieldPathBinding : ICustomBinding`  
_L318-328_
- inherits: `ICustomBinding`
- L320 _public typedef_ `using Type = FFieldPath;`
- L321 _public member_ `const FMemberId MemberIds[2];`
- L323 _public prototype_ `FFieldPathBinding(TPropertySpecifier<2>& Spec);`
- L325 _public prototype_ `void Save(FMemberBuilder& Dst, const Type& Src, const Type* Default, const FSaveContext&) const;`
- L326 _public prototype_ `void Load(Type& Dst, FStructLoadView Src, ECustomLoadMethod Method) const;`
- L327 _public prototype_ `static bool Diff(const Type& A, const Type& B, const FBindContext&);`

#### struct `PlainProps::UE::FDelegateBinding`  
`struct FDelegateBinding : ICustomBinding`  
_L330-340_
- inherits: `ICustomBinding`
- L332 _public typedef_ `using Type = FScriptDelegate;`
- L333 _public member_ `const FMemberId MemberIds[2];`
- L335 _public prototype_ `FDelegateBinding(TPropertySpecifier<2>& Spec);`
- L337 _public prototype_ `void Save(FMemberBuilder& Dst, const Type& Src, const Type* Default, const FSaveContext&) const;`
- L338 _public prototype_ `void Load(Type& Dst, FStructLoadView Src, ECustomLoadMethod Method) const;`
- L339 _public prototype_ `static bool Diff(const Type& A, const Type& B, const FBindContext&);`

#### struct `PlainProps::UE::FMulticastInlineDelegateBinding`  
`struct FMulticastInlineDelegateBinding : ICustomBinding`  
_L342-352_
- inherits: `ICustomBinding`
- L344 _public typedef_ `using Type = FMulticastScriptDelegate;`
- L345 _public member_ `const FMemberId MemberIds[1];`
- L347 _public prototype_ `FMulticastInlineDelegateBinding(TPropertySpecifier<1>& Spec);`
- L349 _public prototype_ `void Save(FMemberBuilder& Dst, const Type& Src, const Type* Default, const FSaveContext&) const;`
- L350 _public prototype_ `void Load(Type& Dst, FStructLoadView Src, ECustomLoadMethod Method) const;`
- L351 _public prototype_ `static bool Diff(const Type& A, const Type& B, const FBindContext&);`

#### struct `PlainProps::UE::FVerseFunctionBinding`  
`struct FVerseFunctionBinding : ICustomBinding`  
_L356-366_
- inherits: `ICustomBinding`
- L358 _public typedef_ `using Type = FVerseFunction;`
- L359 _public member_ `const FMemberId MemberIds[1];`
- L361 _public prototype_ `FVerseFunctionBinding(TPropertySpecifier<1>& Spec);`
- L363 _public prototype_ `void Save(FMemberBuilder& Dst, const Type& Src, const Type* Default, const FSaveContext&) const;`
- L364 _public prototype_ `void Load(Type& Dst, FStructLoadView Src, ECustomLoadMethod Method) const;`
- L365 _public prototype_ `static bool Diff(const Type& A, const Type& B, const FBindContext&);`

#### struct `PlainProps::UE::FDynamicallyTypedValueBinding`  
`struct FDynamicallyTypedValueBinding : ICustomBinding`  
_L368-378_
- inherits: `ICustomBinding`
- L370 _public typedef_ `using Type = ::UE::FDynamicallyTypedValue;`
- L371 _public member_ `const FMemberId MemberIds[1];`
- L373 _public prototype_ `FDynamicallyTypedValueBinding(TPropertySpecifier<1>& Spec);`
- L375 _public prototype_ `void Save(FMemberBuilder& Dst, const Type& Src, const Type* Default, const FSaveContext&) const;`
- L376 _public prototype_ `void Load(Type& Dst, FStructLoadView Src, ECustomLoadMethod Method) const;`
- L377 _public prototype_ `static bool Diff(const Type& A, const Type& B, const FBindContext&);`

#### struct `PlainProps::UE::FReferencePropertyBinding`  
`struct FReferencePropertyBinding : ICustomBinding`  
_L380-390_
- inherits: `ICustomBinding`
- L382 _public typedef_ `using Type = FReferencePropertyValue;`
- L383 _public member_ `const FMemberId MemberIds[1];`
- L385 _public prototype_ `FReferencePropertyBinding(TPropertySpecifier<1>& Spec);`
- L387 _public prototype_ `void Save(FMemberBuilder& Dst, const Type& Src, const Type* Default, const FSaveContext&) const;`
- L388 _public prototype_ `void Load(Type& Dst, FStructLoadView Src, ECustomLoadMethod Method) const;`
- L389 _public prototype_ `static bool Diff(const Type& A, const Type& B, const FBindContext&);`

#### struct `PlainProps::UE::FInstancedStructBinding`  
`struct FInstancedStructBinding : ICustomBinding`  
_L392-402_
- inherits: `ICustomBinding`
- L394 _public typedef_ `using Type = FInstancedStruct;`
- L395 _public member_ `const FMemberId MemberIds[2];`
- L397 _public prototype_ `FInstancedStructBinding(TPropertySpecifier<2>& Spec);`
- L399 _public prototype_ `void Save(FMemberBuilder& Dst, const Type& Src, const Type* Default, const FSaveContext&) const;`
- L400 _public prototype_ `void Load(Type& Dst, FStructLoadView Src, ECustomLoadMethod Method) const;`
- L401 _public prototype_ `static bool Diff(const Type& A, const Type& B, const FBindContext&);`

#### struct `PlainProps::TCustomBind`  
`template<Enumeration E> requires (requires { StaticEnum<E>(); }) struct TCustomBind<TEnumAsByte<E>>`  
_L409-409_
- L409 _public typedef_ `template<Enumeration E> requires (requires { StaticEnum<E>(); }) struct TCustomBind<TEnumAsByte<E>> { using Type = UE::TUEnumAsByteBinding<E>; };`
- L424 _public typedef_ `template<> struct TCustomBind<FFieldPath> { using Type = UE::FFieldPathBinding; };` — custom bindings
- L428 _public typedef_ `template<> struct TCustomBind<FScriptDelegate> { using Type = UE::FDelegateBinding; };`
- L429 _public typedef_ `template<> struct TCustomBind<FMulticastScriptDelegate> { using Type = UE::FMulticastInlineDelegateBinding; };`
- L430 _public typedef_ `template<> struct TCustomBind<::UE::FDynamicallyTypedValue> { using Type = UE::FDynamicallyTypedValueBinding; };`

#### struct `PlainProps::TExternallyBound`  
`template<> struct TExternallyBound<FGuid, UE::FDefaultRuntime> : std::true_type`  
_L411-411_
- inherits: `std::true_type`

#### struct `PlainProps::TExternallyBound`  
`template<> struct TExternallyBound<FGuid, UE::FDefaultRuntime> : std::true_type`  
_L412-412_
- inherits: `std::true_type`

#### struct `PlainProps::TExternallyBound`  
`template<> struct TExternallyBound<FGuid, UE::FDefaultRuntime> : std::true_type`  
_L413-413_
- inherits: `std::true_type`

#### struct `PlainProps::TExternallyBound`  
`template<> struct TExternallyBound<FGuid, UE::FDefaultRuntime> : std::true_type`  
_L414-414_
- inherits: `std::true_type`

#### struct `PlainProps::TTypename`  
`template<typename T> struct TTypename<TObjectPtr<T>>`  
_L417-417_
- desc: Enable usage of TObjectPtr<T> as members in ctti reflected structs
- L418 _public member_ `template<typename T> struct TTypename<TObjectPtr<T>> { static_assert(!sizeof(T), "Unsupp` — Enable usage of TObjectPtr<T> as members in ctti reflected structs

#### struct `PlainProps::TTypename`  
`template<typename T> struct TTypename<TObjectPtr<T>>`  
_L418-418_
- desc: Enable usage of TObjectPtr<T> as members in ctti reflected structs
- L418 _public member_ `template<typename T> struct TTypename<TObjectPtr<T>> { static_assert(!sizeof(T), "Unsupp` — Enable usage of TObjectPtr<T> as members in ctti reflected structs

#### struct `PlainProps::TTypename`  
`template<typename T> struct TTypename<TObjectPtr<T>>`  
_L419-419_
- desc: Enable usage of TObjectPtr<T> as members in ctti reflected structs
- L418 _public member_ `template<typename T> struct TTypename<TObjectPtr<T>> { static_assert(!sizeof(T), "Unsupp` — Enable usage of TObjectPtr<T> as members in ctti reflected structs

#### struct `PlainProps::TCustomBind`  
`template<> struct TCustomBind<FFieldPath>`  
_L424-424_
- desc: custom bindings
- L409 _public typedef_ `template<Enumeration E> requires (requires { StaticEnum<E>(); }) struct TCustomBind<TEnumAsByte<E>> { using Type = UE::TUEnumAsByteBinding<E>; };`
- L424 _public typedef_ `template<> struct TCustomBind<FFieldPath> { using Type = UE::FFieldPathBinding; };` — custom bindings
- L428 _public typedef_ `template<> struct TCustomBind<FScriptDelegate> { using Type = UE::FDelegateBinding; };`
- L429 _public typedef_ `template<> struct TCustomBind<FMulticastScriptDelegate> { using Type = UE::FMulticastInlineDelegateBinding; };`
- L430 _public typedef_ `template<> struct TCustomBind<::UE::FDynamicallyTypedValue> { using Type = UE::FDynamicallyTypedValueBinding; };`

#### struct `PlainProps::TCustomBind`  
`template<> struct TCustomBind<FFieldPath>`  
_L425-425_
- desc: custom bindings
- L409 _public typedef_ `template<Enumeration E> requires (requires { StaticEnum<E>(); }) struct TCustomBind<TEnumAsByte<E>> { using Type = UE::TUEnumAsByteBinding<E>; };`
- L424 _public typedef_ `template<> struct TCustomBind<FFieldPath> { using Type = UE::FFieldPathBinding; };` — custom bindings
- L428 _public typedef_ `template<> struct TCustomBind<FScriptDelegate> { using Type = UE::FDelegateBinding; };`
- L429 _public typedef_ `template<> struct TCustomBind<FMulticastScriptDelegate> { using Type = UE::FMulticastInlineDelegateBinding; };`
- L430 _public typedef_ `template<> struct TCustomBind<::UE::FDynamicallyTypedValue> { using Type = UE::FDynamicallyTypedValueBinding; };`

#### struct `PlainProps::TCustomBind`  
`template<> struct TCustomBind<FFieldPath>`  
_L426-426_
- desc: custom bindings
- L409 _public typedef_ `template<Enumeration E> requires (requires { StaticEnum<E>(); }) struct TCustomBind<TEnumAsByte<E>> { using Type = UE::TUEnumAsByteBinding<E>; };`
- L424 _public typedef_ `template<> struct TCustomBind<FFieldPath> { using Type = UE::FFieldPathBinding; };` — custom bindings
- L428 _public typedef_ `template<> struct TCustomBind<FScriptDelegate> { using Type = UE::FDelegateBinding; };`
- L429 _public typedef_ `template<> struct TCustomBind<FMulticastScriptDelegate> { using Type = UE::FMulticastInlineDelegateBinding; };`
- L430 _public typedef_ `template<> struct TCustomBind<::UE::FDynamicallyTypedValue> { using Type = UE::FDynamicallyTypedValueBinding; };`

#### struct `PlainProps::TCustomBind`  
`template<> struct TCustomBind<FFieldPath>`  
_L427-427_
- desc: custom bindings
- L409 _public typedef_ `template<Enumeration E> requires (requires { StaticEnum<E>(); }) struct TCustomBind<TEnumAsByte<E>> { using Type = UE::TUEnumAsByteBinding<E>; };`
- L424 _public typedef_ `template<> struct TCustomBind<FFieldPath> { using Type = UE::FFieldPathBinding; };` — custom bindings
- L428 _public typedef_ `template<> struct TCustomBind<FScriptDelegate> { using Type = UE::FDelegateBinding; };`
- L429 _public typedef_ `template<> struct TCustomBind<FMulticastScriptDelegate> { using Type = UE::FMulticastInlineDelegateBinding; };`
- L430 _public typedef_ `template<> struct TCustomBind<::UE::FDynamicallyTypedValue> { using Type = UE::FDynamicallyTypedValueBinding; };`

#### struct `PlainProps::TCustomBind`  
`template<> struct TCustomBind<FScriptDelegate>`  
_L428-428_
- L409 _public typedef_ `template<Enumeration E> requires (requires { StaticEnum<E>(); }) struct TCustomBind<TEnumAsByte<E>> { using Type = UE::TUEnumAsByteBinding<E>; };`
- L424 _public typedef_ `template<> struct TCustomBind<FFieldPath> { using Type = UE::FFieldPathBinding; };` — custom bindings
- L428 _public typedef_ `template<> struct TCustomBind<FScriptDelegate> { using Type = UE::FDelegateBinding; };`
- L429 _public typedef_ `template<> struct TCustomBind<FMulticastScriptDelegate> { using Type = UE::FMulticastInlineDelegateBinding; };`
- L430 _public typedef_ `template<> struct TCustomBind<::UE::FDynamicallyTypedValue> { using Type = UE::FDynamicallyTypedValueBinding; };`

#### struct `PlainProps::TCustomBind`  
`template<> struct TCustomBind<FMulticastScriptDelegate>`  
_L429-429_
- L409 _public typedef_ `template<Enumeration E> requires (requires { StaticEnum<E>(); }) struct TCustomBind<TEnumAsByte<E>> { using Type = UE::TUEnumAsByteBinding<E>; };`
- L424 _public typedef_ `template<> struct TCustomBind<FFieldPath> { using Type = UE::FFieldPathBinding; };` — custom bindings
- L428 _public typedef_ `template<> struct TCustomBind<FScriptDelegate> { using Type = UE::FDelegateBinding; };`
- L429 _public typedef_ `template<> struct TCustomBind<FMulticastScriptDelegate> { using Type = UE::FMulticastInlineDelegateBinding; };`
- L430 _public typedef_ `template<> struct TCustomBind<::UE::FDynamicallyTypedValue> { using Type = UE::FDynamicallyTypedValueBinding; };`

#### struct `PlainProps::TCustomBind`  
`template<> struct TCustomBind<::UE::FDynamicallyTypedValue>`  
_L430-430_
- L409 _public typedef_ `template<Enumeration E> requires (requires { StaticEnum<E>(); }) struct TCustomBind<TEnumAsByte<E>> { using Type = UE::TUEnumAsByteBinding<E>; };`
- L424 _public typedef_ `template<> struct TCustomBind<FFieldPath> { using Type = UE::FFieldPathBinding; };` — custom bindings
- L428 _public typedef_ `template<> struct TCustomBind<FScriptDelegate> { using Type = UE::FDelegateBinding; };`
- L429 _public typedef_ `template<> struct TCustomBind<FMulticastScriptDelegate> { using Type = UE::FMulticastInlineDelegateBinding; };`
- L430 _public typedef_ `template<> struct TCustomBind<::UE::FDynamicallyTypedValue> { using Type = UE::FDynamicallyTypedValueBinding; };`

#### Free symbols / members of external scopes

- L21 _namespace_ `namespace PlainProps`
- L21 _namespace_ `namespace UE` (scope `PlainProps`)
- L217 _externvar_ `extern FGlobals GUE;` (scope `PlainProps::UE`)
- L254 _variable_ `static constexpr ESizeType DefaultRangeMax = RangeSizeOf(FDefaultAllocator::SizeType{});` (scope `PlainProps::UE`)
- L256 _function_ `inline FMemberSpec DefaultRangeOf(FMemberSpec Item)` (scope `PlainProps::UE`)
- L259 _typedef_ `template<uint32 N> using TPropertySpecifier = TCustomSpecifier<FRuntimeIds, N>;` (scope `PlainProps::UE`)
- L263 _typedef_ `template<typename Enum, EEnumMode Mode> using TScopedDefaultEnumDeclaration = TScopedEnumDeclaration<Enum, Mode, FDefaultRuntime>;` (scope `PlainProps::UE`) — Default runtime scope to declare a ctti reflected native enum
- L285 _typedef_ `template<class T, typename CustomBinding> using TScopedDefaultUStructBinding = TScopedUStructBinding<T, FDefaultRuntime, CustomBinding>;` (scope `PlainProps::UE`) — Default runtime scope to declare and custom bind an override for a schema bound UStruct
- L289 _typedef_ `template<class T, typename CustomBinding> using TScopedDefaultUClassBinding = TScopedUClassBinding<T, FDefaultRuntime, CustomBinding>;` (scope `PlainProps::UE`) — Default runtime scope to declare and custom bind an override for a schema bound UClass
- L406 _namespace_ `namespace PlainProps`
- L420 _function_ `template<typename T> struct TTypename<TObjectPtr<T>>` (scope `PlainProps`) — Enable usage of TObjectPtr<T> as members in ctti reflected structs
- L421 _function_ `template<> struct TTypename<TObjectPtr<UClass>>` (scope `PlainProps`)
- L433 _function_ `template<> inline FScopeId GetOuterScope<UE::FRuntimeIds, TTypename<FName>>()` (scope `PlainProps`) — Temporary way to tie certain Core types to /Script/CoreUObject scope
- L437 _function_ `template<> inline FScopeId GetOuterScope<UE::FRuntimeIds, TTypename<FText>>()` (scope `PlainProps`)
- L438 _function_ `template<> inline FScopeId GetOuterScope<UE::FRuntimeIds, TTypename<FIntPoint>>()` (scope `PlainProps`)
- L439 _function_ `template<> inline FScopeId GetOuterScope<UE::FRuntimeIds, TTypename<FQuat>>()` (scope `PlainProps`)
- L440 _function_ `template<> inline FScopeId GetOuterScope<UE::FRuntimeIds, TTypename<FTransform>>()` (scope `PlainProps`)
- L441 _function_ `template<> inline FScopeId GetOuterScope<UE::FRuntimeIds, TTypename<FVector>>()` (scope `PlainProps`)
- L442 _function_ `template<> inline FScopeId GetOuterScope<UE::FRuntimeIds, TTypename<FVector4>>()` (scope `PlainProps`)
