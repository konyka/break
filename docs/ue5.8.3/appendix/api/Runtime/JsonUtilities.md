# Runtime / JsonUtilities

- module root: `Source/Runtime/JsonUtilities`
- headers: 11; symbols: 186
- symbol kinds: class=8, enum=4, enumerator=15, function=48, macro=2, member=26, namespace=5, prototype=61, struct=9, typedef=8
- PublicDependencyModuleNames: Core, CoreUObject, Json

### `Source/Runtime/JsonUtilities/Private/JsonSchema/JsonSchemaVisitorStack.h` (Private)


#### enum `UE::JsonSchema::EVisitorStackElementFlags`  
`enum class EVisitorStackElementFlags : uint8`  
_L19-25_
- L21 _public enumerator_ `None = 0`
- L22 _public enumerator_ `IsRootStruct = 1 << 0`
- L23 _public enumerator_ `RequireAllProperties = 1 << 1`
- L24 _public enumerator_ `SkipDescription = 1 << 2`

#### struct `UE::JsonSchema::FVisitorStackElement`  
`struct FVisitorStackElement`  
_L28-57_
- L30 _public function_ `explicit FVisitorStackElement(const FVisitorTarget& InVisitorTarget, const EVisitorStackElementFlags InFlags, const FJsonSchemaMemberPath& InMemberPath, const FJsonSchemaPropertyFilter& InPropertyFilter, const TSharedPtr<FJsonObject>& InOutputSchema, const void* InInstanceMemory) : VisitorTarget(InVisitorTarget), Flags(InFlags), MemberPath(InMemberPath), PropertyFilter(InPropertyFilter), OutputSchema(InOutputSchema), InstanceMemory(InInstanceMemory)`
- L49 _public member_ `FVisitorTarget VisitorTarget;`
- L50 _public member_ `EVisitorStackElementFlags Flags = EVisitorStackElementFlags::None;`
- L51 _public member_ `FJsonSchemaMemberPath MemberPath;`
- L52 _public member_ `FJsonSchemaPropertyFilter PropertyFilter;`
- L53 _public member_ `const TSharedPtr<FJsonObject> OutputSchema;`
- L56 _public member_ `const void* InstanceMemory = nullptr;` — Optional pointer to the live instance for this target. Used to generate accurate schemas for types whose structure is only known at runtime (e.g. FInstancedStruct, FInstancedPropertyBag).

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace JsonSchema` (scope `UE`)
- L15 _typedef_ `using FValidConstUStruct = TNotNull<const UStruct*>;` (scope `UE::JsonSchema`)
- L16 _typedef_ `using FValidConstFProperty = TNotNull<const FProperty*>;` (scope `UE::JsonSchema`)
- L17 _typedef_ `using FVisitorTarget = TVariant<FValidConstUStruct, FValidConstFProperty>;` (scope `UE::JsonSchema`)
- L26 _prototype_ `ENUM_CLASS_FLAGS(EVisitorStackElementFlags);` (scope `UE::JsonSchema`)
- L59 _typedef_ `using FVisitorStack = TArray<FVisitorStackElement>;` (scope `UE::JsonSchema`)

### `Source/Runtime/JsonUtilities/Private/JsonUtilitiesModularFeature.h` (Private)


#### class `IJsonUtilitiesModularFeature`  
`class IJsonUtilitiesModularFeature : public IModularFeature`  
_L15-32_
- inherits: `IModularFeature`
- desc: Base class for Modular Feature - Editor functionality that the Runtime module will call when in Editor, to collect metadata. See Editor module for derivation and registration.
- L19 _public member_ `static const FName Name;`
- L21 _public prototype_ `IJsonUtilitiesModularFeature();`
- L22 _public prototype_ `virtual ~IJsonUtilitiesModularFeature() = default;`
- L24 _public prototype_ `static IJsonUtilitiesModularFeature* Get();`
- L27 _public prototype_ `virtual FJsonSchemaEditorMetadata FPropertyToJsonSchemaMetadata(TNotNull<const FProperty*> Property, const FJsonSchemaPropertyFilter& PropertyFilter, const void* InstanceMemory) const = 0;`
- L30 _public prototype_ `virtual FJsonSchemaEditorMetadata UStructToJsonSchemaMetadata(TNotNull<const UStruct*> Struct, const FJsonSchemaPropertyFilter& PropertyFilter, const void* InstanceMemory) const = 0;`

### `Source/Runtime/JsonUtilities/Public/JsonDomBuilder.h` (Public)


#### class `FJsonDomBuilder`  
`class FJsonDomBuilder`  
_L30-193_

#### class `FJsonDomBuilder::FObject`  
`class FObject`  
_L35-118_
- L38 _public function_ `FObject() : Object(MakeShared<FJsonObject>())`
- L43 _public function_ `FObject(TSharedPtr<FJsonObject> InObject) : Object(InObject.ToSharedRef())`
- L48 _public function_ `FObject(TSharedRef<FJsonObject> InObject) : Object(InObject)`
- L53 _public function_ `TSharedRef<FJsonValueObject> AsJsonValue() const`
- L58 _public function_ `TSharedRef<FJsonObject> AsJsonObject() const`
- L64 _public function_ `template <template <class> class TPrintPolicy = TPrettyJsonPrintPolicy> FString ToString() const`
- L73 _public function_ `template <template <class> class TPrintPolicy = TPrettyJsonPrintPolicy> FUtf8String ToUtf8String() const`
- L81 _public function_ `int Num() const`
- L86 _public function_ `FObject& Set(const FString& Key, const FArray& Arr)`
- L87 _public function_ `FObject& Set(const FString& Key, const FObject& Obj)`
- L91 _public function_ `FObject& Set(const FString& Key, const StringType& Str)`
- L95 _public function_ `FObject& Set(const FString& Key, NumberType Number)`
- L99 _public function_ `FObject& Set(const FString& Key, BoolType Boolean)`
- L101 _public function_ `FObject& Set(const FString& Key, TYPE_OF_NULLPTR)`
- L103 _public function_ `FObject& Set(const FString& Key, TSharedPtr<FJsonValue> Value)`
- L105 _public function_ `void CopyIf(const FJsonObject& Src, TFunctionRef<bool (const FJsonObject::FStringType&, const FJsonValue&)> Pred)`
- L117 _private member_ `TSharedRef<FJsonObject> Object;`

#### class `FJsonDomBuilder::FArray`  
`class FArray`  
_L120-192_
- L123 _public function_ `TSharedRef<FJsonValueArray> AsJsonValue() const`
- L129 _public function_ `template <template <class> class TPrintPolicy = TPrettyJsonPrintPolicy> FString ToString() const`
- L138 _public function_ `template <template <class> class TPrintPolicy = TPrettyJsonPrintPolicy> FUtf8String ToUtf8String() const`
- L146 _public function_ `int Num() const`
- L151 _public function_ `FArray& Add(const FArray& Arr)`
- L152 _public function_ `FArray& Add(const FObject& Obj)`
- L156 _public function_ `FArray& Add(const StringType& Str)`
- L160 _public function_ `FArray& Add(NumberType Number)`
- L164 _public function_ `FArray& Add(BoolType Boolean)`
- L165 _public function_ `FArray& Add(TYPE_OF_NULLPTR)`
- L167 _public function_ `FArray& Add(TSharedPtr<FJsonValue> Value)`
- L172 _public function_ `FArray& Add(ValueType&&... Value)`
- L180 _public function_ `void CopyIf(const TArray<TSharedPtr<FJsonValue>>& Src, TFunctionRef<bool (const FJsonValue&)> Pred)`
- L191 _private member_ `TArray<TSharedPtr<FJsonValue>> Array;`

### `Source/Runtime/JsonUtilities/Public/JsonObjectConverter.h` (Public)


#### enum `EJsonObjectConversionFlags`  
`enum class EJsonObjectConversionFlags`  
_L30-47_
- L32 _public enumerator_ `None = 0`
- L33 _public enumerator_ `SkipStandardizeCase = 1 << 0`
- L39 _public enumerator_ `WriteTextAsComplexString = 1 << 1` — Write text in its complex exported format (eg, NSLOCTEXT(...)) rather than as a simple string. @note This is required to correctly support localization
- L46 _public enumerator_ `SuppressClassNameForPersistentObject = 1 << 2` — suppress _ClassName key written for persistent objects that allows them to be deserialized later. This can be useful for times when writing to Json and you don't need to reserialize back into UObjects, as the _ClassName would be unnecessary.

#### class `FJsonObjectConverter`  
`class FJsonObjectConverter`  
_L55-424_
- desc: Class that handles converting Json objects to and from UStructs
- L63 _public prototype_ `[[nodiscard]] static FString StandardizeCase(const FString &StringIn);` — FName case insensitivity can make the casing of UPROPERTIES unpredictable. Attempt to standardize output. See StandardizeCaseInPlace() for an in-place equivalent.
- L65 _public prototype_ `static void StandardizeCaseInPlace(FString& String);`
- L68 _public prototype_ `static bool GetTextFromObject(const TSharedRef<FJsonObject>& Obj, FText& TextOut);` — Parse an FText from a json object (assumed to be of the form where keys are culture codes and values are strings)
- L71 _public prototype_ `static bool GetTextFromField(const FString& FieldName, const TSharedPtr<FJsonValue>& FieldValue, FText& TextOut);` — Convert a Json value to text (takes some hints from the value name)
- L80 _public typedef_ `using CustomExportCallback = TDelegate<TSharedPtr<FJsonValue>(FProperty* Property, const void* Value)>;` — Optional callback that will be run when exporting a single property to Json. If this returns a valid value it will be inserted into the export chain. If this returns nullptr or is not bound, it will try generic type-specific export behavior before falling back to outputting ExportText as a string.
- L87 _public typedef_ `using CustomImportCallback = TDelegate<bool(const TSharedPtr<FJsonValue>& JsonValue, FProperty* Property, void* Value)>;` — Optional callback that will be run when importing a single property from Json. If this returns true, it should have successfully turned the Json value into the property value. If this returns false or is not bound, it will try generic type-specific import behavior before failing.
- L89 _public member_ `static const CustomExportCallback ExportCallback_WriteISO8601Dates;`
- L101 _public function_ `template<typename InStructType> static TSharedPtr<FJsonObject> UStructToJsonObject(const InStructType& InStruct, int64 CheckFlags = 0, int64 SkipFlags = 0, const CustomExportCallback* ExportCb = nullptr)` — Templated version of UStructToJsonObject to try and make most of the params. Also serves as an example use case @param InStruct The UStruct instance to read from @param ExportCb Optional callback to override export behavior, if this returns null it will fallback to the default @param CheckFlags Only convert properties that match at least one of these flags. If 0 check all properties. @param SkipFlags Skip properties that match any of these flags @return FJsonObject pointer. Invalid if an error occurred.
- L124 _public prototype_ `static bool UStructToJsonObject(const UStruct* StructDefinition, const void* Struct, TSharedRef<FJsonObject> OutJsonObject, int64 CheckFlags = 0, int64 SkipFlags = 0, const CustomExportCallback* ExportCb = nullptr, EJsonObjectConversionFlags ConversionFlags = EJsonObjectConversionFlags::None);` — Converts from a UStruct to a Json Object, using exportText @param StructDefinition UStruct definition that is looked over for properties @param Struct The UStruct instance to copy out of @param OutJsonObject Json Object to be filled in with data from the ustruct @param CheckFlags Only convert properties that match at least one of these flags. If 0 check all properties. @param SkipFlags Skip properties that match any of these flags @param ExportCb Optional callback to override export behavior, if this returns null it will fallback to the default @param ConversionFlags Bitwise flags to customize the conversion behavior @return False if any properties failed to write
- L140 _public prototype_ `static bool UStructToJsonObjectString(const UStruct* StructDefinition, const void* Struct, FString& OutJsonString, int64 CheckFlags = 0, int64 SkipFlags = 0, int32 Indent = 0, const CustomExportCallback* ExportCb = nullptr, bool bPrettyPrint = true);` — Converts from a UStruct to a json string containing an object, using exportText @param StructDefinition UStruct definition that is looked over for properties @param Struct The UStruct instance to copy out of @param JsonObject Json Object to be filled in with data from the ustruct @param CheckFlags Only convert properties that match at least one of these flags. If 0 check all properties. @param SkipFlags Skip properties that match any of these flags @param Indent How many tabs to add to the json serializer @param ExportCb Optional callback to override export behavior, if this returns null it will fallback to the default @param bPrettyPrint Option to use pretty print (e.g., adds line endings) or condensed print @return False if any properties failed to write
- L156 _public function_ `template<typename InStructType> static bool UStructToJsonObjectString(const InStructType& InStruct, FString& OutJsonString, int64 CheckFlags = 0, int64 SkipFlags = 0, int32 Indent = 0, const CustomExportCallback* ExportCb = nullptr, bool bPrettyPrint = true)` — Templated version; Converts from a UStruct to a json string containing an object, using exportText @param InStruct The UStruct instance to copy out of @param OutJsonString Json Object to be filled in with data from the ustruct @param CheckFlags Only convert properties that match at least one of these flags. If 0 check all properties. @param SkipFlags Skip properties that match any of these flags @param Indent How many tabs to add to the json serializer @param ExportCb Optional callback to override export behavior, if this returns null it will fallback to the default @param bPrettyPrint Option to use pretty print (e.g., adds line endings) or condensed print @return False if any properties failed to write
- L172 _public function_ `template<typename CharType, template<typename> class PrintPolicy> static bool UStructToFormattedJsonObjectString(const UStruct* StructDefinition, const void* Struct, FString& OutJsonString, int64 CheckFlags = 0, int64 SkipFlags = 0, int32 Indent = 0, const CustomExportCallback* ExportCb = nullptr, EJsonObjectConversionFlags ConversionFlags = EJsonObjectConversionFlags::None)` — Wrapper to UStructToJsonObjectString that allows a print policy to be specified.
- L207 _public prototype_ `static bool UStructToJsonAttributes(const UStruct* StructDefinition, const void* Struct, TSharedRef<FJsonObject> OutJsonObject, int64 CheckFlags = 0, int64 SkipFlags = 0, const CustomExportCallback* ExportCb = nullptr, EJsonObjectConversionFlags ConversionFlags = EJsonObjectConversionFlags::None);` — Converts from a UStruct to a set of json attributes (possibly from within a JsonObject) @param StructDefinition UStruct definition that is looked over for properties @param Struct The UStruct instance to copy out of @param OutJsonAttributes Map of attributes to copy in to @param CheckFlags Only convert properties that match at least one of these flags. If 0 check all properties. @param SkipFlags Skip properties that match any of these flags @param ExportCb Optional callback to override export behavior, if this returns null it will fallback to the default @param ConversionFlags Bitwise flags to customize the conversion behavior @return False if any properties failed to write
- L221 _public prototype_ `static TSharedPtr<FJsonValue> UPropertyToJsonValue(FProperty* Property, const void* Value, int64 CheckFlags = 0, int64 SkipFlags = 0, const CustomExportCallback* ExportCb = nullptr, FProperty* OuterProperty = nullptr, EJsonObjectConversionFlags ConversionFlags = EJsonObjectConversionFlags::None);` — Converts from a FProperty to a Json Value using exportText @param Property			The property to export @param Value				Pointer to the value of the property @param CheckFlags		Only convert properties that match at least one of these flags. If 0 check all properties. @param SkipFlags			Skip properties that match any of these flags @param ExportCb Optional callback to override export behavior, if this returns null it will fallback to the default @param OuterProperty		If applicable, the Array/Set/Map Property that contains this property @param ConversionFlags	Bitwise flags to customize the conversion behavior @return					The constructed JsonValue from the property
- L239 _public prototype_ `static bool JsonObjectToUStruct(const TSharedRef<FJsonObject>& JsonObject, const UStruct* StructDefinition, void* OutStruct, int64 CheckFlags = 0, int64 SkipFlags = 0, const bool bStrictMode = false, FText* OutFailReason = nullptr, const CustomImportCallback* ImportCb = nullptr);` — Converts from a Json Object to a UStruct, using importText @param JsonObject Json Object to copy data out of @param StructDefinition UStruct definition that is looked over for properties @param OutStruct The UStruct instance to copy in to @param CheckFlags Only convert properties that match at least one of these flags. If 0 check all properties. @param SkipFlags Skip properties that match any of these flags @param bStrictMode Whether to strictly check the json attributes @param OutFailReason Reason of the failure if any @param ImportCb Optional callback to override import behaviour, if this returns false it will fallback to the default @return False if any properties matched but failed to deserialize
- L255 _public function_ `template<typename OutStructType> static bool JsonObjectToUStruct(const TSharedRef<FJsonObject>& JsonObject, OutStructType* OutStruct, int64 CheckFlags = 0, int64 SkipFlags = 0, const bool bStrictMode = false, FText* OutFailReason = nullptr, const CustomImportCallback* ImportCb = nullptr)` — Templated version of JsonObjectToUStruct @param JsonObject Json Object to copy data out of @param OutStruct The UStruct instance to copy in to @param CheckFlags Only convert properties that match at least one of these flags. If 0 check all properties. @param SkipFlags Skip properties that match any of these flags @param bStrictMode Whether to strictly check the json attributes @param OutFailReason Reason of the failure if any @param ImportCb Optional callback to override import behaviour, if this returns false it will fallback to the default @return False if any properties matched but failed to deserialize
- L281 _public prototype_ `static bool JsonAttributesToUStruct(const TMap<FJsonObject::FStringType, TSharedPtr<FJsonValue>>& JsonAttributes, const UStruct* StructDefinition, void* OutStruct, int64 CheckFlags = 0, int64 SkipFlags = 0, const bool bStrictMode = false, FText* OutFailReason = nullptr, const CustomImportCallback* ImportCb = nullptr);` — Converts a set of json attributes (possibly from within a JsonObject) to a UStruct, using importText @param JsonAttributes Json Object to copy data out of @param StructDefinition UStruct definition that is looked over for properties @param OutStruct The UStruct instance to copy in to @param CheckFlags Only convert properties that match at least one of these flags. If 0 check all properties. @param SkipFlags Skip properties that match any of these flags @param bStrictMode Whether to strictly check the json attributes @param OutFailReason Reason of the failure if any @param ImportCb Optional callback to override import behaviour, if this returns false it will fallback to the default @return False if any properties matched but failed to deserialize
- L297 _public prototype_ `static bool JsonValueToUProperty(const TSharedPtr<FJsonValue>& JsonValue, FProperty* Property, void* OutValue, int64 CheckFlags = 0, int64 SkipFlags = 0, const bool bStrictMode = false, FText* OutFailReason = nullptr, const CustomImportCallback* ImportCb = nullptr);` — Converts a single JsonValue to the corresponding FProperty (this may recurse if the property is a UStruct for instance). @param JsonValue The value to assign to this property @param Property The FProperty definition of the property we're setting. @param OutValue Pointer to the property instance to be modified. @param CheckFlags Only convert sub-properties that match at least one of these flags. If 0 check all properties. @param SkipFlags Skip sub-properties that match any of these flags @param bStrictMode Whether to strictly check the json attributes @param OutFailReason Reason of the failure if any @param ImportCb Optional callback to override import behaviour, if this returns false it will fallback to the default @return False if the property failed to serialize
- L313 _public function_ `template<typename OutStructType> static bool JsonObjectStringToUStruct(const FString& JsonString, OutStructType* OutStruct, int64 CheckFlags = 0, int64 SkipFlags = 0, const bool bStrictMode = false, FText* OutFailReason = nullptr, const CustomImportCallback* ImportCb = nullptr)` — Converts from a json string containing an object to a UStruct @param JsonString String containing JSON formatted data. @param OutStruct The UStruct instance to copy in to @param CheckFlags Only convert properties that match at least one of these flags. If 0 check all properties. @param SkipFlags Skip properties that match any of these flags @param bStrictMode Whether to strictly check the json attributes @param OutFailReason Reason of the failure if any @param ImportCb Optional callback to override import behaviour, if this returns false it will fallback to the default @return False if any properties matched but failed to deserialize
- L352 _public function_ `template<typename OutStructType> static bool JsonArrayStringToUStruct(const FString& JsonString, TArray<OutStructType>* OutStructArray, int64 CheckFlags = 0, int64 SkipFlags = 0, const bool bStrictMode = false, FText* OutFailReason = nullptr, const CustomImportCallback* ImportCb = nullptr)` — Converts from a json string containing an array to an array of UStructs @param JsonString String containing JSON formatted data. @param OutStructArray The UStruct array to copy in to @param CheckFlags Only convert properties that match at least one of these flags. If 0 check all properties. @param SkipFlags Skip properties that match any of these flags. @param bStrictMode Whether to strictly check the json attributes @param OutFailReason Reason of the failure if any @param ImportCb Optional callback to override import behaviour, if this returns false it will fallback to the default @return False if any properties matched but failed to deserialize.
- L391 _public function_ `template<typename OutStructType> static bool JsonArrayToUStruct(const TArray<TSharedPtr<FJsonValue>>& JsonArray, TArray<OutStructType>* OutStructArray, int64 CheckFlags = 0, int64 SkipFlags = 0, const bool bStrictMode = false, FText* OutFailReason = nullptr, const CustomImportCallback* ImportCb = nullptr)` — Converts from an array of json values to an array of UStructs. @param JsonArray Array containing json values to convert. @param OutStructArray The UStruct array to copy in to @param CheckFlags Only convert properties that match at least one of these flags. If 0 check all properties. @param SkipFlags Skip properties that match any of these flags. @param bStrictMode Whether to strictly check the json attributes @param OutFailReason Reason of the failure if any @param ImportCb Optional callback to override import behaviour, if this returns false it will fallback to the default @return False if any of the matching elements are not an object, or if one of the matching elements could not be converted to the specified UStruct type.
- L423 _public prototype_ `static FFormatNamedArguments ParseTextArgumentsFromJson(const TSharedPtr<const FJsonObject>& JsonObject);` — Parses text arguments from Json into a map @param JsonObject Object to parse arguments from

#### Free symbols / members of external scopes

- L28 _macro_ `#define LOCTEXT_NAMESPACE "JsonObjectConverter"`

### `Source/Runtime/JsonUtilities/Public/JsonObjectStructInterface.h` (Public)


#### struct `FJsonObjectStructInterfaceRegistry`  
`struct FJsonObjectStructInterfaceRegistry`  
_L11-18_
- desc: Global registry for type-registered static-interface converters to override default struct behavior in FJsonObjectConverter.
- L13 _public prototype_ `static void RegisterStructConverter(const UScriptStruct* ScriptStruct, const IJsonObjectStructConverter* ConverterInterface);`
- L14 _public prototype_ `static void UnregisterStructConverter(const UScriptStruct* ScriptStruct);`
- L17 _public prototype_ `static bool HasStructConverterRegistered(const UScriptStruct* ScriptStruct);` — Return whether or not a struct converter has been registered for this ScriptStruct

#### enum `EJsonObjectConvertResult`  
`enum class EJsonObjectConvertResult`  
_L20-30_
- L23 _public enumerator_ `UseDefaultConverter` — No conversion was performed. Fallback to try the default JsonObjectConverter instead.
- L25 _public enumerator_ `FailAndAbort` — No conversion is possible. Abandon further efforts. Ask caller to fail.
- L27 _public enumerator_ `IgnoreAndContinue` — No conversion was performed. Don't try any fallback. Allow caller to still succeed the conversion (if this was a nested convert attempt).
- L29 _public enumerator_ `Converted` — Conversion of the struct was performed.

#### struct `IJsonObjectStructConverter`  
`struct IJsonObjectStructConverter`  
_L40-61_
- desc: UStructs are special and may need to avoid the use of virtual functions via standard interface patterns due to mismatched base-class polymorphism. So use a static TImplementsJsonObjectStructConverter<StructType> which uses a static-interface pattern with global type-registry instead of implementing an interface directly. The registered struct should have the following functions (the compiler will fail without them): EJsonObjectConvertResult ConvertToJson(TSharedPtr<FJsonObject>& OutJsonObject) const; EJsonObjectConvertResult ConvertFromJson(const TSharedPtr<FJsonObject>& InJsonObject);
- L48 _public prototype_ `virtual EJsonObjectConvertResult ConvertToJson(const void* StructMemory, TSharedPtr<FJsonObject>& OutJsonObject) const = 0;` — Result of Converted represents success by the interface call, FailAndAbort will bubble up the failure to its owner converter which may fail the entire converter tree, IgnoreAndContinue will make an empty FJsonObject for this struct and the converter tree can still succeed, and UseDefaultConverter will try to fallback to the non-static-interface behavior instead.
- L56 _public prototype_ `virtual EJsonObjectConvertResult ConvertFromJson(void* StructMemory, const TSharedPtr<FJsonObject>& InJsonObject) const = 0;` — Result of Converted represents success by the interface call, FailAndAbort will bubble up the failure to its owner converter failing the entire converter tree, IgnoreAndContinue should leave the struct untouched/default and the converter tree can still succeed, and UseDefaultConverter will try to fallback to the non-static-interface behavior instead.
- L60 _protected prototype_ `virtual ~IJsonObjectStructConverter() = default;`

#### struct `TImplementsJsonObjectStructConverter`  
`template<typename StructType> struct TImplementsJsonObjectStructConverter : public IJsonObjectStructConverter`  
_L81-94_
- inherits: `IJsonObjectStructConverter`
- desc: This template is to be statically constructed and passed as a parameter to RegisterStructConverter in StartupModule() for the specified StructType. Remember to explicitly call UnregisterStructConverter in ShutdownModule() as well. Example usage: void FExampleModule::StartupModule() { static const TImplementsJsonObjectStructConverter<FExampleStruct> ExampleConverter = TImplementsJsonObjectStructConverter<FExampleStruct>(); FJsonObjectStructInterfaceRegistry::RegisterStructConverter(FExampleStruct::StaticStruct(), &ExampleConverter); } void FExampleModule::ShutdownModule() { FJsonObjectStructInterfaceRegistry::UnregisterStructConverter(FExampleStruct::StaticStruct()); }
- L83 _public function_ `TImplementsJsonObjectStructConverter<StructType>()`
- L85 _public function_ `virtual EJsonObjectConvertResult ConvertToJson(const void* StructMemory, TSharedPtr<FJsonObject>& OutJsonObject) const override`
- L90 _public function_ `virtual EJsonObjectConvertResult ConvertFromJson(void* StructMemory, const TSharedPtr<FJsonObject>& InJsonObject) const override`

#### Free symbols / members of external scopes

- L97 _namespace_ `namespace UE`
- L97 _namespace_ `namespace Json` (scope `UE`)
- L97 _namespace_ `namespace Private` (scope `UE::Json`)
- L99 _prototype_ `const struct IJsonObjectStructConverter* GetStructConverterInterface(const UScriptStruct* ScriptStruct);` (scope `UE::Json::Private`)

### `Source/Runtime/JsonUtilities/Public/JsonObjectWrapper.h` (Public)


#### struct `FJsonObjectWrapper`  
`struct FJsonObjectWrapper`  
_L22-47_
- reflection: `USTRUCT(BlueprintType, meta = (DisplayName = "JsonObject"))`
- desc: UStruct that holds a JsonObject, can be used by structs passed to JsonObjectConverter to pass through JsonObjects directly
- L27 _public prototype_ `FJsonObjectWrapper();`
- L30 _public member_ `FString JsonString;` — `UPROPERTY(EditAnywhere, Category = "JSON")`
- L32 _public member_ `TSharedPtr<FJsonObject> JsonObject;`
- L34 _public prototype_ `bool ImportTextItem(const TCHAR*& Buffer, int32 PortFlags, UObject* Parent, FOutputDevice* ErrorText);`
- L35 _public prototype_ `bool ExportTextItem(FString& ValueStr, FJsonObjectWrapper const& DefaultValue, UObject* Parent, int32 PortFlags, UObject* ExportRootScope) const;`
- L36 _public prototype_ `void PostSerialize(const FArchive& Ar);`
- L38 _public prototype_ `explicit operator bool() const;`
- L40 _public prototype_ `bool JsonObjectToString(FString& Str) const;`
- L41 _public prototype_ `bool JsonObjectFromString(const FString& Str);`
- L46 _public prototype_ `SIZE_T GetAllocatedSize() const;` — Returns the memory allocated by this object in Bytes, should NOT include sizeof(*this).

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FJsonObjectWrapper> : public TStructOpsTypeTraitsBase2<FJsonObjectWrapper>`  
_L50-58_
- inherits: `TStructOpsTypeTraitsBase2<FJsonObjectWrapper>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L53-57_

#### class `UJsonUtilitiesDummyObject`  
`class UJsonUtilitiesDummyObject : public UObject`  
_L60-63_
- reflection: `UCLASS()`
- inherits: `UObject`

#### Free symbols / members of external scopes

- L54 _enumerator_ `WithImportTextItem = true` (scope `TStructOpsTypeTraits::__anon6f480a040103`)
- L55 _enumerator_ `WithExportTextItem = true` (scope `TStructOpsTypeTraits::__anon6f480a040103`)
- L56 _enumerator_ `WithPostSerialize = true` (scope `TStructOpsTypeTraits::__anon6f480a040103`)

### `Source/Runtime/JsonUtilities/Public/JsonSchema/JsonSchemaEditorMetadata.h` (Public)


#### struct `FJsonSchemaEditorMetadata`  
`struct FJsonSchemaEditorMetadata`  
_L14-59_
- desc: Used for constructing a member path for properties, and storing/accessing metadata for multiple property member paths. Also stores metadata for a root struct.
- L16 _public typedef_ `using FJsonSchemaPropertyMemberPathToPropertyMetadataMap = TMap<FString, TSharedPtr<FJsonObject>>;`
- L18 _public prototype_ `FJsonSchemaEditorMetadata();`
- L20 _public prototype_ `FJsonSchemaEditorMetadata(const FJsonSchemaEditorMetadata& Other);`
- L22 _public prototype_ `FJsonSchemaEditorMetadata& operator=(const FJsonSchemaEditorMetadata& Other);`
- L27 _public member_ `TSharedPtr<FJsonObject> RootStructMetadata;` — Top-level metadata (if any) for the root struct only. Mainly used when UStruct is UFunction.
- L33 _public prototype_ `void SetPropertyMetadataForCurrentPropertyMemberPath(const TSharedRef<FJsonObject>& PropertyMetadata);` — Adds property metadata for the current property member path. @param PropertyMetadata Property metadata.
- L39 _public prototype_ `TSharedPtr<FJsonObject> GetPropertyMetadataForCurrentPropertyMemberPath();` — Gets property metadata for the current property member path. @return Property metadata for the current property member path.
- L44 _public prototype_ `const FJsonSchemaPropertyMemberPathToPropertyMetadataMap& GetPropertyMemberPathToPropertyMetadataMap() const;` — Get Property member path -to- property metadata map.
- L45 _public prototype_ `FJsonSchemaPropertyMemberPathToPropertyMetadataMap& GetPropertyMemberPathToPropertyMetadataMap();`
- L50 _public member_ `FJsonSchemaMemberPath CurrentPropertyMemberPath;` — Current property member path being constructed.
- L58 _private member_ `FJsonSchemaPropertyMemberPathToPropertyMetadataMap PropertyMemberPathToPropertyMetadataMap;` — Maps completed property member paths to property metadata, if present. Per-property metadata, including inner properties e.g: Person, Person.Name, Person.Age

### `Source/Runtime/JsonUtilities/Public/JsonSchema/JsonSchemaGenerator.h` (Public)


#### class `FJsonSchemaGenerator`  
`class FJsonSchemaGenerator`  
_L17-231_
- desc: Used for generating a JSON schema from any UStruct or FProperty.
- L51 _public prototype_ `TSharedPtr<FJsonObject> static FPropertyToJsonSchemaObject(TNotNull<const FProperty*> Property, const FJsonSchemaPropertyFilter& PropertyFilter = FJsonSchemaPropertyFilter(), const FJsonSchemaEditorMetadata* CachedEditorMetadata = nullptr, const void* InstanceMemory = nullptr);` — Derives a JSON Schema definition for Property's type. Can be called by a developer directly, but primarily used by UStructToJsonSchemaObject(). Attention - - Property name is not part of the returned schema. - If calling in Editor context, metadata will be included. Otherwise, it will not. (i.e. default and min/max clamp values.) - If Property's owner Struct is a UFunction and calling from an Editor context, metadata will only include default values if UFunction is a Blueprint function. If Property is a struct or container of structs property etc, the nested types will be recursed into using UStructToJsonSchemaObject to derive a fully complete schema. Importantly, the derived JSON Schema describes the JSON which would be produced by FJsonObjectConverter::UPropertyToJsonValue for a property value of this type. And conversely, any JSON adhering to this JSON Schema, may then be deserialized to this property, using FJsonObjectConverter::JsonValueToUProperty. e.g: FBoolProperty -> { "type": "boolean" } FStrProperty & FTextProperty -> { "type": "string" } FStructProperty -> { "type": "object", "properties": { ... } } @param Property The property to build a schema for. @param PropertyFilter Determines how to filter collected struct and property data. @param CachedEditorMetadata If valid, use this metadata instead of collecting it. Otherwise, it will be automatically collected (if running in Editor context.) This is optional, and used for workflows that have cached metadata from an e
- L69 _public prototype_ `static FString FPropertyToJsonSchemaString(TNotNull<const FProperty*> Property, const FJsonSchemaPropertyFilter& PropertyFilter = FJsonSchemaPropertyFilter(), const FJsonSchemaEditorMetadata* CachedEditorMetadata = nullptr, const int32 Indent = 0, const bool bPrettyPrint = true);` — String output variant of FPropertyToJsonSchemaObject() (see above.) Provides JSON string instead of JSON object. @param Property The property to build a schema for. @param PropertyFilter Determines how to filter collected struct and property data. @param CachedEditorMetadata If valid, use this metadata instead of collecting it. Otherwise, it will be automatically collected (if running in Editor context.) This is optional, and used for workflows that have cached metadata from an earlier process. @param Indent How many additional tabs to add to the json serializer output. @param bPrettyPrint Option to use pretty print (e.g., adds line endings), otherwise condensed print. @return Schema for the property, as a JSON string.
- L152 _public prototype_ `static TSharedPtr<FJsonObject> UStructToJsonSchemaObject(TNotNull<const UStruct*> Struct, const FJsonSchemaPropertyFilter& PropertyFilter = FJsonSchemaPropertyFilter(), const FJsonSchemaEditorMetadata* CachedEditorMetadata = nullptr, const void* InstanceMemory = nullptr);` — Recursively walks Struct's property hierarchy to derive a JSON Schema definition for this type. To be called by a developer directly. Attention - - Struct name is not part of the returned schema. - If calling in Editor context, metadata will be included. Otherwise, it will not. (i.e. struct's description) - If Struct is a UFunction, and calling from an Editor context, metadata will only include default values for the function parameters if the function is a Blueprint function. - If Struct is a UClass, its UFunctions will not be included in the returned schema. TODO - Need a UClass version of this function? Importantly, the derived JSON Schema describes the JSON which would be produced by FJsonObjectConverter::StructToJsonObject for an instance of the given UStruct. And conversely, any JSON adhering to this JSON Schema, may then be deserialized to an instance of Struct, using FJsonObjectConverter::JsonObjectToUStruct. e.g: // Details for a person USTRUCT() struct FPerson { GENERATED_BODY() // Full name UPROPERTY() FString Name; // How old they are UPROPERTY(meta = (ClampMin = "1")) int32 Age; } // A family of people USTRUCT() struct FFamily { // Members of this family UPROPERTY() TArray<FPerson> Members; } -> { "type": "object", "properties": { "members": { "type": "array", "description": "Members of this family", "items": { "type": "object", "properties": { "name": { "type": "string", "description": "Full name" }, "age": { "type": "integer", "description": "How old they are",
- L169 _public function_ `template<typename InStructType> static TSharedPtr<FJsonObject> UStructToJsonSchemaObject( const FJsonSchemaPropertyFilter& PropertyFilter = FJsonSchemaPropertyFilter(), FJsonSchemaEditorMetadata* CachedEditorMetadata = nullptr)` — Templated variant of UStructToJsonSchemaObject() (see above.). Works according to struct/class type instead of an taking actual UStruct/UClass reference - i.e. UStructToJsonSchema<FSomeStruct>() or UStructToJsonSchema<USomeClass>(). @param PropertyFilter Determines how to filter collected struct and property data. @param CachedEditorMetadata If valid, use this metadata instead of collecting it. Otherwise, it will be automatically collected (if running in Editor context.) This is optional, and used for workflows that have cached metadata from an earlier process. @return Schema for the UStruct, as a JSON object.
- L197 _public prototype_ `static FString UStructToJsonSchemaString(TNotNull<const UStruct*> Struct, const FJsonSchemaPropertyFilter& PropertyFilter = FJsonSchemaPropertyFilter(), const FJsonSchemaEditorMetadata* CachedEditorMetadata = nullptr, const int32 Indent = 0, const bool bPrettyPrint = true);` — String output variant of UStructToJsonSchemaObject() (see above.) Provides JSON string instead of JSON object. @param Struct The type to build a schema for. Can be either UScriptStruct, UClass or UFunction. @param PropertyFilter Determines how to filter collected struct and property data. @param CachedEditorMetadata If valid, use this metadata instead of collecting it. Otherwise, it will be automatically collected (if running in Editor context.) This is optional, and used for workflows that have cached metadata from an earlier process. @param Indent How many additional tabs to add to the json serializer output. @param bPrettyPrint Option to use pretty print (e.g., adds line endings), otherwise condensed print. @return Schema for the UStruct, as a JSON string.
- L216 _public function_ `template<typename InStructType> static FString UStructToJsonSchemaString( const FJsonSchemaPropertyFilter& PropertyFilter = FJsonSchemaPropertyFilter(), const FJsonSchemaEditorMetadata* CachedEditorMetadata = nullptr, const int32 Indent = 0, const bool bPrettyPrint = true)` — Templated variant of UStructToJsonSchemaString() (see above.). Works according to struct/class type instead of an taking actual UStruct/UClass reference - i.e. UStructToJsonSchema<FSomeStruct>() or UStructToJsonSchema<USomeClass>(). @param PropertyFilter Determines how to filter collected struct and property data. @param CachedEditorMetadata If valid, use this metadata instead of collecting it. Otherwise, it will be automatically collected (if running in Editor context.) This is optional, and used for workflows that have cached metadata from an earlier process. @param Indent How many additional tabs to add to the json serializer output. @param bPrettyPrint Option to use pretty print (e.g., adds line endings), otherwise condensed print. @return Schema for the UStruct, as a JSON string.

### `Source/Runtime/JsonUtilities/Public/JsonSchema/JsonSchemaMemberPath.h` (Public)


#### class `FJsonSchemaMemberPath`  
`class FJsonSchemaMemberPath`  
_L10-78_
- desc: JSON member path builder.
- L17 _public member_ `static const FStringView Delimiter;` — Text used to represent divider between member names and sub-member names.
- L19 _public prototype_ `FJsonSchemaMemberPath();`
- L20 _public prototype_ `FJsonSchemaMemberPath(const FJsonSchemaMemberPath& InMemberPath);`
- L21 _public prototype_ `FJsonSchemaMemberPath(FJsonSchemaMemberPath&& Other) = default;`
- L22 _public prototype_ `explicit FJsonSchemaMemberPath(FStringView InitialString);`
- L24 _public prototype_ `FJsonSchemaMemberPath& operator=(const FJsonSchemaMemberPath& Other);`
- L25 _public prototype_ `FJsonSchemaMemberPath& operator=(FJsonSchemaMemberPath&& Other) = default;`
- L30 _public function_ `int32 Len() const` — Returns the length of the path string.
- L33 _public function_ `const TCHAR* GetData() const` — Returns a pointer to the path string data.
- L36 _public function_ `const TCHAR* operator*() const` — Returns a null-terminated TCHAR pointer to the path string.
- L39 _public function_ `FStringView ToView() const` — Returns a string view of the path.
- L46 _public prototype_ `bool Push(FStringView String);` — Add a string to the end. @param String String add to end. @return Success.
- L53 _public prototype_ `bool Pop(FStringView String);` — Remove a string from the end. @param String String to remove from end. @return Success.
- L60 _public prototype_ `bool PushSubmember(FStringView SubmemberString);` — Add a string to the end, as a submember: Delimiter + SubmemberText @param SubmemberString String add to end. @return Success.
- L67 _public prototype_ `bool PopSubmember(FStringView SubmemberString);` — Remove a string from the end, as a submember: Delimiter + SubmemberText @param SubmemberString String to remove from end. @return Success.
- L73 _public prototype_ `FText ToText() const;` — Converts path to FText. @return FText representation of path.
- L77 _private member_ `FString PathString;`

#### struct `FJsonSchemaScopedMemberPathPush`  
`struct FJsonSchemaScopedMemberPathPush`  
_L85-121_
- desc: Allows RAII scoped control of FJsonSchemaMemberPath. Pushes string on construction, pops string on destruction. Can be used directly, or with macro below.
- L89 _public function_ `explicit FJsonSchemaScopedMemberPathPush(FJsonSchemaMemberPath& InMemberPath, FStringView InString, const bool bInIsSubmember) : MemberPath(InMemberPath), String(InString), bIsSubmember(bInIsSubmember)`
- L104 _public function_ `~FJsonSchemaScopedMemberPathPush()`
- L118 _private member_ `FJsonSchemaMemberPath& MemberPath;`
- L119 _private member_ `FString String;` — ..can't use FStringView, out of scope when dtr called
- L120 _private member_ `bool bIsSubmember;`

#### Free symbols / members of external scopes

- L124 _macro_ `#define UE_JSON_SCHEMA_SCOPED_MEMBER_PATH_PUSH(MemberPathExpr, StringExpr, bIsSubmemberExpr) \` — Declares uniquely named FScopedSubmemberPath.

### `Source/Runtime/JsonUtilities/Public/JsonSchema/JsonSchemaPropertyFilter.h` (Public)


#### struct `FJsonSchemaPropertyFilter`  
`struct FJsonSchemaPropertyFilter`  
_L12-94_
- desc: Filter used during schema generation, used for both FProperties and UStructs.
- L19 _public typedef_ `using CustomCallback = TDelegate<bool(const FProperty* Property, const FString& ParameterDefaultString, const TSharedRef<FJsonObject>& OutputSchema)>;` — Optional callback that will be run when exporting a single property to JsonSchema. This function should return true if it's handled the property by writing to OutputSchema. If ParameterDefaultString is set then only defaults should be written into the OutputSchema object.
- L21 _public prototype_ `explicit FJsonSchemaPropertyFilter( const EPropertyFlags InCheckFlags = CPF_None, const EPropertyFlags InSkipFlags = CPF_None, const TOptional<TSet<FString>>& InRequiredPropertyMemberPaths = TOptional<TSet<FString>>(), const TOptional<TSet<FString>>& InSkipPropertyMemberPaths = TOptional<TSet<FString>>(), const EJsonObjectConversionFlags InConversionFlags = EJsonObjectConversionFlags::None, CustomCallback* CustomCb = nullptr);`
- L29 _public prototype_ `FJsonSchemaPropertyFilter(const FJsonSchemaPropertyFilter& Other);`
- L34 _public member_ `EPropertyFlags CheckFlags = CPF_None;` — If specified (not CPF_None), only properties with any of the specified EPropertyFlags will be considered.
- L39 _public member_ `EPropertyFlags SkipFlags = CPF_None;` — If specified (not CPF_None), any properties with any of the specified EPropertyFlags will be skipped.
- L48 _public member_ `TOptional<TSet<FString>> RequiredPropertyMemberPaths;` — Only considered while generating schemas for UStructs. If specified, only properties in this list will be declared in the 'required' schema attribute. Inner properties should be specified by path e.g: ["StructMember", "StructMember.InnerProperty"] (If unspecified, all properties without default values in StructMetaData will end up automatically listed as required, in code found elsewhere.)
- L55 _public member_ `TOptional<TSet<FString>> SkipPropertyMemberPaths;` — Only considered while generating schemas for UStructs. If specified, any properties in this list will not be described in the resulting schema. Inner properties should be specified by path e.g: ["StructMember", "StructMember.InnerProperty"]
- L61 _public member_ `EJsonObjectConversionFlags ConversionFlags = EJsonObjectConversionFlags::None;` — If passed, ensures generated schema is compatible with FJsonObjectConverter::UStructToJsonObject executed with the same flags e.g: EJsonObjectConversionFlags::SkipStandardizeCase for property name casing.
- L66 _public member_ `FJsonSchemaPropertyFilter::CustomCallback* CustomCb = nullptr;` — If passed, allows for custom property handling.
- L73 _public prototype_ `bool IsPropertyIgnored(TNotNull<const FProperty*> Property) const;` — Checks if a property should be ignored, to its flags compared to our check/skip flags. @param Property The property to test. @return Whether a property should be ignored.
- L80 _public prototype_ `bool IsPropertyMemberPathRequired(const FString& PropertyMemberPath) const;` — Checks if a property is required. @param PropertyMemberPath @return Whether the property path is listed as being required.
- L87 _public prototype_ `bool IsPropertyMemberPathSkipped(const FString& PropertyMemberPath) const;` — Checks if a property should be skipped. @param PropertyMemberPath @return Whether the property path is listed as being skipped.
- L93 _public prototype_ `FString PropertyAuthoredNameToJsonKey(const FString& PropertyAuthoredName) const;` — Converts a property's authored name into a name that respects the ConversionFlags setting. @param PropertyAuthoredName The authored name of a property.

### `Source/Runtime/JsonUtilities/Public/JsonUtilities.h` (Public)
_(no declarations extracted)_
