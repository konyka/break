# Runtime / FieldNotification

- module root: `Source/Runtime/FieldNotification`
- headers: 7; symbols: 139
- symbol kinds: class=3, delegate=1, enum=1, enumerator=1, function=37, macro=21, member=24, namespace=11, prototype=26, struct=10, typedef=4
- PublicDependencyModuleNames: Core, CoreUObject

### `Source/Runtime/FieldNotification/Public/FieldNotificationDeclaration.h` (Public)


#### Free symbols / members of external scopes

- L30 _macro_ `#define UE_FIELD_NOTIFICATION_OVERRIDE_GET_FIELD_NOTIFICATION_DESCRIPTOR() \`
- L36 _macro_ `#define UE_FIELD_NOTIFICATION_DECLARE_CLASS_DESCRIPTOR_BEGIN(API_STRING) \`
- L47 _macro_ `#define UE_FIELD_NOTIFICATION_DECLARE_CLASS_DESCRIPTOR_END() \`
- L63 _macro_ `#define UE_FIELD_NOTIFICATION_DECLARE_CLASS_DESCRIPTOR_BASE_BEGIN(API_STRING) \`
- L75 _macro_ `#define UE_FIELD_NOTIFICATION_DECLARE_CLASS_DESCRIPTOR_BASE_END() \`
- L80 _macro_ `#define UE_FIELD_NOTIFICATION_DECLARE_ENUM_FIELD_BEGIN(Name) \`
- L86 _macro_ `#define UE_FIELD_NOTIFICATION_DECLARE_ENUM_FIELD_END() \`
- L91 _macro_ `#define UE_FIELD_NOTIFICATION_DECLARE_FIELD(Name, API_STRING) \`
- L95 _macro_ `#define UE_FIELD_NOTIFICATION_DECLARE_ENUM_FIELD(Name) \`
- L99 _macro_ `#define UE_FIELD_NOTIFICATION_IMPLEMENTATION_BEGIN(ClassName) \`
- L108 _macro_ `#define UE_FIELD_NOTIFICATION_IMPLEMENTATION_END(ClassName) }`
- L144 _macro_ `#define UE_FIELD_NOTIFICATION_IMPLEMENT_FIELD(ClassName, MemberName) const ::UE::FieldNotification::FFieldId ClassName::FFieldNotificationClassDescriptor::MemberName( FName(TEXT(#MemberName)), ClassName::FFieldNotificationClassDescriptor::I`
- L145 _macro_ `#define UE_FIELD_NOTIFICATION_IMPLEMENT_ENUM_FIELD(ClassName, MemberName) &ClassName::FFieldNotificationClassDescriptor::MemberName,`
- L148 _macro_ `#define UE_FIELD_NOTIFICATION_IMPLEMENT_CLASS_DESCRIPTOR_OneField(ClassName, Field1) \`
- L154 _macro_ `#define UE_FIELD_NOTIFICATION_IMPLEMENT_CLASS_DESCRIPTOR_TwoFields(ClassName, Field1, Field2) \`
- L162 _macro_ `#define UE_FIELD_NOTIFICATION_IMPLEMENT_CLASS_DESCRIPTOR_ThreeFields(ClassName, Field1, Field2, Field3) \`
- L172 _macro_ `#define UE_FIELD_NOTIFICATION_IMPLEMENT_CLASS_DESCRIPTOR_FourFields(ClassName, Field1, Field2, Field3, Field4) \`
- L184 _macro_ `#define UE_FIELD_NOTIFICATION_IMPLEMENT_CLASS_DESCRIPTOR_FiveFields(ClassName, Field1, Field2, Field3, Field4, Field5) \`
- L198 _macro_ `#define UE_FIELD_NOTIFICATION_IMPLEMENT_CLASS_DESCRIPTOR_SixFields(ClassName, Field1, Field2, Field3, Field4, Field5, Field6) \`
- L214 _macro_ `#define UE_FIELD_NOTIFICATION_IMPLEMENT_CLASS_DESCRIPTOR_SevenFields(ClassName, Field1, Field2, Field3, Field4, Field5, Field6, Field7) \`
- L232 _macro_ `#define UE_FIELD_NOTIFICATION_IMPLEMENT_CLASS_DESCRIPTOR_EightFields(ClassName, Field1, Field2, Field3, Field4, Field5, Field6, Field7, Field8) \`

### `Source/Runtime/FieldNotification/Public/FieldNotificationDelegate.h` (Public)


#### class `UE::FieldNotification::FFieldMulticastDelegate`  
`class FFieldMulticastDelegate`  
_L25-154_
- L28 _public typedef_ `using FDelegate = INotifyFieldValueChanged::FFieldValueChangedDelegate;`
- L29 _public typedef_ `using FDynamicDelegate = FFieldValueChangedDynamicDelegate;`
- L70 _private typedef_ `using InvocationListType = TArray<FInvocationElement>;`
- L73 _public prototype_ `FDelegateHandle Add(const UObject* InObject, FFieldId InFieldId, FDelegate InNewDelegate);`
- L74 _public prototype_ `FDelegateHandle Add(const UObject* InObject, FFieldId InFieldId, const FDynamicDelegate& InDynamicDelegate);`
- L83 _public prototype_ `FRemoveResult Remove(FDelegateHandle InDelegate);`
- L84 _public prototype_ `FRemoveResult Remove(const FDynamicDelegate& InDynamicDelegate);`
- L91 _public prototype_ `FRemoveFromResult RemoveFrom(const UObject* InObject, FFieldId InFieldId, FDelegateHandle InDelegate);`
- L92 _public prototype_ `FRemoveFromResult RemoveFrom(const UObject* InObject, FFieldId InFieldId, const FDynamicDelegate& InDynamicDelegate);`
- L99 _public prototype_ `FRemoveAllResult RemoveAll(const UObject* InObject, FDelegateUserObjectConst InUserObject);`
- L100 _public prototype_ `FRemoveAllResult RemoveAll(const UObject* InObject, FFieldId InFieldId, FDelegateUserObjectConst InUserObject);`
- L102 _public prototype_ `void Broadcast(UObject* InObject, FFieldId InFieldId);`
- L104 _public prototype_ `void Reset();`
- L116 _public prototype_ `TArray<FDelegateView> GetView() const;`
- L119 _private function_ `int32 LowerBound(FFieldId InFieldId) const`
- L125 _private function_ `int32 LowerBound(const FInvocationKey& InKey) const`
- L131 _private function_ `int32 UpperBound(FFieldId InFieldId) const`
- L137 _private function_ `int32 UpperBound(const FInvocationKey& InKey) const`
- L143 _private prototype_ `void ExecuteLockOperations();`
- L144 _private prototype_ `void RemoveElement(FInvocationElement& Element, int32 Index, FRemoveResult& Result);`
- L145 _private prototype_ `void CompleteRemove(FRemoveResult& Result) const;`
- L147 _private prototype_ `template<typename TRemoveOrUnbind> void RemoveFrom(TRemoveOrUnbind& RemoveOrUnbind, FFieldId FieldId, bool& bFieldPresent);`
- L150 _private member_ `InvocationListType Delegates;`
- L151 _private member_ `int16 DelegateLockCount = 0;`
- L152 _private member_ `int16 CompactionCount = 0;`
- L153 _private member_ `uint16 AddedEmplaceAt = std::numeric_limits<uint16>::max();`

#### struct `UE::FieldNotification::FFieldMulticastDelegate::FInvocationKey`  
`struct FInvocationKey`  
_L32-41_
- L34 _public member_ `TWeakObjectPtr<const UObject> Object;`
- L35 _public member_ `FFieldId Id;`
- L36 _public member_ `FName DynamicName;`
- L37 _public function_ `bool operator<(const FInvocationKey& Element) const`

#### struct `UE::FieldNotification::FFieldMulticastDelegate::FInvocationElement`  
`struct FInvocationElement`  
_L43-51_
- L45 _public member_ `FInvocationKey Key;`
- L46 _public member_ `FDelegate Delegate;`
- L47 _public function_ `bool operator<(const FInvocationElement& InElement) const`

#### struct `UE::FieldNotification::FFieldMulticastDelegate::FRemoveResult`  
`struct FRemoveResult`  
_L76-82_
- L78 _public member_ `bool bRemoved = false;`
- L79 _public member_ `bool bHasOtherBoundDelegates = false;`
- L80 _public member_ `const UObject* Object = nullptr;`
- L81 _public member_ `FFieldId FieldId;`

#### struct `UE::FieldNotification::FFieldMulticastDelegate::FRemoveFromResult`  
`struct FRemoveFromResult`  
_L86-90_
- L88 _public member_ `bool bRemoved = false;`
- L89 _public member_ `bool bHasOtherBoundDelegates = false;`

#### struct `UE::FieldNotification::FFieldMulticastDelegate::FRemoveAllResult`  
`struct FRemoveAllResult`  
_L94-98_
- L96 _public member_ `int32 RemoveCount = 0;`
- L97 _public member_ `TBitArray<> HasFields;`

#### struct `UE::FieldNotification::FFieldMulticastDelegate::FDelegateView`  
`struct FDelegateView`  
_L106-115_
- L108 _public function_ `FDelegateView(const UObject* InKeyObj, FFieldId InKeyId, const UObject* InObj, FName InFunction) : KeyObject(InKeyObj), KeyField(InKeyId), BindingObject(InObj), BindingFunctionName(InFunction)`
- L111 _public member_ `const UObject* KeyObject;`
- L112 _public member_ `FFieldId KeyField;`
- L113 _public member_ `const UObject* BindingObject;`
- L114 _public member_ `FName BindingFunctionName;`

#### Free symbols / members of external scopes

- L22 _namespace_ `namespace UE`
- L22 _namespace_ `namespace FieldNotification` (scope `UE`)
- L53 _function_ `friend bool operator<(const FInvocationElement& A, const FInvocationKey& B)` (scope `UE::FieldNotification`)
- L57 _function_ `friend bool operator<(const FInvocationKey& A, const FInvocationElement& B)` (scope `UE::FieldNotification`)
- L61 _function_ `friend bool operator<(const FInvocationElement& A, const FFieldId& B)` (scope `UE::FieldNotification`)
- L65 _function_ `friend bool operator<(const FFieldId& A, const FInvocationElement& B)` (scope `UE::FieldNotification`)

### `Source/Runtime/FieldNotification/Public/FieldNotificationHelpers.h` (Public)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace FieldNotification` (scope `UE`)
- L8 _namespace_ `namespace Helpers` (scope `UE::FieldNotification`)
- L10 _function_ `[[nodiscard]] inline bool IsValidAsField(const UFunction* InFunction)` (scope `UE::FieldNotification::Helpers`)

### `Source/Runtime/FieldNotification/Public/FieldNotificationId.h` (Public)


#### struct `UE::FieldNotification::FFieldId`  
`struct FFieldId`  
_L15-79_
- L18 _public prototype_ `FFieldId() = default;`
- L20 _public function_ `explicit FFieldId(FName InFieldName, int32 InBitNumber) : FieldName(InFieldName) , BitNumber(InBitNumber)`
- L28 _public function_ `bool IsValid() const`
- L33 _public function_ `int32 GetIndex() const`
- L38 _public function_ `FName GetName() const`
- L43 _public function_ `FFieldVariant ToVariant(UObject* InContainer) const`
- L59 _public function_ `bool operator==(const FFieldId& Other) const`
- L64 _public function_ `bool operator!=(const FFieldId& Other) const`
- L76 _private member_ `FName FieldName;` — Name of the field. It can be a FProperty or UFunction.
- L78 _private member_ `int32 BitNumber;` — The bit this field is linked to.

#### struct `FFieldNotificationId`  
`struct FFieldNotificationId`  
_L85-127_
- reflection: `USTRUCT(BlueprintType)`
- L90 _public prototype_ `FFieldNotificationId() = default;`
- L92 _public function_ `explicit FFieldNotificationId(FName InFieldName) : FieldName(InFieldName)`
- L99 _public function_ `bool IsValid() const`
- L104 _public function_ `FName GetFieldName() const`
- L109 _public function_ `bool operator== (const FFieldNotificationId& Other) const`
- L114 _public function_ `bool operator!= (const FFieldNotificationId& Other) const`
- L126 _public member_ `FName FieldName;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "FieldNotify")`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace FieldNotification` (scope `UE`)
- L69 _function_ `friend int32 GetTypeHash(const FFieldId& Value)` (scope `UE::FieldNotification`)
- L119 _function_ `friend int32 GetTypeHash(const FFieldNotificationId& Value)`

### `Source/Runtime/FieldNotification/Public/FieldNotificationVariant.h` (Public)


#### struct `UE::FieldNotification::FFieldVariant`  
`struct FFieldVariant : private ::FFieldVariant`  
_L13-68_
- inherits: `::FFieldVariant`
- L16 _public prototype_ `FFieldVariant() = default;`
- L18 _public function_ `explicit FFieldVariant(const FProperty* InProperty) : ::FFieldVariant(InProperty)`
- L23 _public function_ `explicit FFieldVariant(const UFunction* InFunction) : ::FFieldVariant(InFunction)`
- L39 _public function_ `inline bool IsProperty() const`
- L44 _public function_ `inline bool IsFunction() const`
- L49 _public function_ `inline FProperty* GetProperty()`
- L54 _public function_ `inline const FProperty* GetProperty() const`
- L59 _public function_ `inline UFunction* GetFunction()`
- L64 _public function_ `inline const UFunction* GetFunction() const`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace FieldNotification` (scope `UE`)

### `Source/Runtime/FieldNotification/Public/IFieldNotificationClassDescriptor.h` (Public)


#### struct `UE::FieldNotification::IClassDescriptor`  
`struct IClassDescriptor`  
_L11-42_
- L19 _public function_ `FFieldId GetField(const UClass* Class, FName InFieldName) const` — Find the FieldId by name. Returns an invalid FFIeldId if not found.
- L35 _public function_ `virtual void ForEachField(const UClass* Class, TFunctionRef<bool(FFieldId FielId)> Callback) const` — Execute the callback for every FieldId in the ClassDescriptor.
- L41 _public prototype_ `virtual ~IClassDescriptor() = default;`

#### enum `UE::FieldNotification::IClassDescriptor::(anonymous)`  
``  
_L14-16_

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace FieldNotification` (scope `UE`)
- L15 _enumerator_ `Max_IndexOf_ = 0` (scope `UE::FieldNotification::IClassDescriptor::__anonba8550900103`)
- L23 _function_ `` (scope `UE::FieldNotification::IClassDescriptor::GetField`)

### `Source/Runtime/FieldNotification/Public/INotifyFieldValueChanged.h` (Public)


#### class `UNotifyFieldValueChanged`  
`class UNotifyFieldValueChanged : public UInterface`  
_L16-19_
- reflection: `UINTERFACE(MinimalAPI, NotBlueprintable)`
- inherits: `UInterface`

#### class `INotifyFieldValueChanged`  
`class INotifyFieldValueChanged : public IInterface`  
_L22-49_
- inherits: `IInterface`
- L29 _public typedef_ `using FFieldValueChangedDelegate = TDelegate<void(UObject*, UE::FieldNotification::FFieldId), FNotThreadSafeNotCheckedDelegateUserPolicy>;` — using "not checked" user policy (means race detection is disabled) because this delegate is stored in a container and causes its reallocation from inside delegate's execution. This is incompatible with race detection that needs to access the delegate instance after its execution
- L33 _public prototype_ `virtual FDelegateHandle AddFieldValueChangedDelegate(UE::FieldNotification::FFieldId InFieldId, FFieldValueChangedDelegate InNewDelegate) = 0;` — Add a delegate that will be notified when the FieldId is value changed.
- L36 _public prototype_ `virtual bool RemoveFieldValueChangedDelegate(UE::FieldNotification::FFieldId InFieldId, FDelegateHandle InHandle) = 0;` — Remove a delegate that was added.
- L39 _public prototype_ `virtual int32 RemoveAllFieldValueChangedDelegates(FDelegateUserObjectConst InUserObject) = 0;` — Remove all the delegate that are bound to the specified UserObject.
- L42 _public prototype_ `virtual int32 RemoveAllFieldValueChangedDelegates(UE::FieldNotification::FFieldId InFieldId, FDelegateUserObjectConst InUserObject) = 0;` — Remove all the delegate that are bound to the specified Field and UserObject.
- L45 _public prototype_ `virtual const UE::FieldNotification::IClassDescriptor& GetFieldNotificationDescriptor() const = 0;` — @returns the list of all the field that can notify when their value changes.
- L48 _public prototype_ `virtual void BroadcastFieldValueChanged(UE::FieldNotification::FFieldId InFieldId) = 0;` — Broadcast to the registered delegate that the FieldId value changed.

#### Free symbols / members of external scopes

- L12 _delegate_ `DECLARE_DYNAMIC_DELEGATE_TwoParams(FFieldValueChangedDynamicDelegate, UObject*, Object, FFieldNotificationId, Field);`
- L12 _prototype_ `DECLARE_DYNAMIC_DELEGATE_TwoParams(FFieldValueChangedDynamicDelegate, UObject*, Object, FFieldNotificationId, Field);`
