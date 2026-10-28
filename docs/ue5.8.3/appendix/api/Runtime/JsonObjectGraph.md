# Runtime / JsonObjectGraph

- module root: `Source/Runtime/Experimental/JsonObjectGraph`
- headers: 6; symbols: 233
- symbol kinds: enum=1, enumerator=4, function=3, macro=23, member=37, namespace=10, prototype=144, struct=7, typedef=4
- PrivateDependencyModuleNames: CoreUObject, Json
- PublicDependencyModuleNames: Core

### `Source/Runtime/Experimental/JsonObjectGraph/Private/JsonObjectGraphConventions.h` (Private)


#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_JSON_ROOT_OBJECTS_KEY_TCHAR TEXT("__RootObjects")` — 'Package' level conventions, these are used at the root level:
- L14 _macro_ `#define UE_JSON_PACKAGE_SUMMARY_KEY_TCHAR TEXT("__PackageSummary")`
- L16 _macro_ `#define UE_JSON_CUSTOM_VERSIONS_KEY_TCHAR TEXT("__CustomVersions")`
- L17 _macro_ `#define UE_JSON_PACKAGE_NAME_KEY_TCHAR TEXT("__PackageName")`
- L20 _macro_ `#define UE_JSON_OBJECT_INSTANCE_KEY_TCHAR TEXT("__UObject")` — UObject instance conventions:
- L21 _macro_ `#define UE_JSON_OBJECT_NAME_KEY_TCHAR TEXT("Name")`
- L22 _macro_ `#define UE_JSON_OBJECT_CLASS_KEY_TCHAR TEXT("Class")`
- L23 _macro_ `#define UE_JSON_OBJECT_FLAGS_KEY_TCHAR TEXT("Flags")`
- L24 _macro_ `#define UE_JSON_OBJECT_STRUCTURED_DATA_KEY_TCHAR TEXT("__StructuredData")`
- L25 _macro_ `#define UE_JSON_OBJECT_SERIAL_DATA_KEY_TCHAR TEXT("__SerialData")`
- L26 _macro_ `#define UE_JSON_OBJECT_SPARSE_CLASS_DATA_KEY_TCHAR TEXT("__SparseClassData")`
- L27 _macro_ `#define UE_JSON_OBJECT_INDIRECTLY_REFERENCED_KEY_TCHAR TEXT("__IndirectlyReferenced")`
- L28 _macro_ `#define UE_JSON_SCRIPTSTRUCT_TCHAR TEXT("__UScriptStruct")`
- L29 _macro_ `#define UE_JSON_PROPERTYBAG_TCHAR TEXT("__UPropertyBag")`
- L30 _macro_ `#define UE_JSON_PROPERTYDESCS_TCHAR TEXT("PropertyDescs")`
- L33 _macro_ `#define UE_JSON_OBJECT_REF_PREFIX "uobject:"` — Reference encoding related conventions:
- L34 _macro_ `#define UE_JSON_FIELD_REF_PREFIX "ffield:"`
- L35 _macro_ `#define UE_JSON_REF_NONE "None"`
- L38 _macro_ `#define UE_JSON_TMAP_KEY_KEY_TCHAR TEXT("Key")` — Conventions related to encoding generic intrinsic types (TMap and TOptional):
- L39 _macro_ `#define UE_JSON_TMAP_VALUE_KEY_TCHAR TEXT("Value")`
- L40 _macro_ `#define UE_JSON_OPTIONAL_VALUE_KEY_TCHAR TEXT("OptionalValue")`
- L45 _macro_ `#define UE_JSON_LINKER_NAME_TABLE_KEY_TCHAR TEXT("PackageNameTable")` — Linker tables written under __PackageSummary in UE_INTERNAL_UNIVERSAL_PLACEHOLDERS builds, where placeholder stubs hide import class/outer information from the object graph.  Encoding the raw tables makes every name and reference auditable from the JSON.
- L46 _macro_ `#define UE_JSON_LINKER_IMPORT_TABLE_KEY_TCHAR TEXT("PackageImportTable")`

### `Source/Runtime/Experimental/JsonObjectGraph/Private/JsonStringifyArchive.h` (Private)


#### struct `UE::Private::FJsonStringifyArchive`  
`struct FJsonStringifyArchive final : private FArchiveUObject`  
_L18-59_
- inherits: `FArchiveUObject`
- desc: Serial in the name of this type is meant to refer to 'UObject::Serialize(FArchive&)'. This writer writes the resulting byte stream safely to json.
- L20 _public prototype_ `FJsonStringifyArchive( const UObject* InObject, int32 InitialIndentLevel, FJsonStringifyImpl* InRootImpl, TArray<FCustomVersion>& InVersionsToHarvest, bool bFilterEditorOnly);`
- L29 _public prototype_ `TArray<uint8> ToJson();` — FMemoryWriter wants to work with TArray<uint8> so that's what we're returning:
- L31 _private prototype_ `TArray<uint8> GetNullStream() const;`
- L33 _private prototype_ `virtual void Serialize(void* V, int64 Length) override;`
- L35 _private prototype_ `virtual void SerializeBool(bool& D) override;`
- L37 _private prototype_ `virtual FArchive& operator<<(UObject*& Value) override;`
- L38 _private prototype_ `virtual FArchive& operator<<(FField*& Value) override;`
- L40 _private prototype_ `virtual FArchive& operator<<(Verse::VCell*& Value) override;`
- L42 _private prototype_ `virtual FArchive& operator<<(struct FLazyObjectPtr& Value) override;`
- L43 _private prototype_ `virtual FArchive& operator<<(struct FObjectPtr& Value) override;`
- L44 _private prototype_ `virtual FArchive& operator<<(struct FSoftObjectPtr& Value) override;`
- L45 _private prototype_ `virtual FArchive& operator<<(struct FSoftObjectPath& Value) override;`
- L46 _private prototype_ `virtual FArchive& operator<<(struct FWeakObjectPtr& Value) override;`
- L48 _private prototype_ `virtual FArchive& operator<<(FName& Value) override;` — overrides for strings:
- L49 _private prototype_ `virtual FArchive& operator<<(FText& Value) override;`
- L51 _private member_ `const UObject* const ObjectBeingStreamSerialized;`
- L52 _private member_ `FJsonStringifyImpl* RootImpl;`
- L54 _private member_ `TArray<uint8> Result;`
- L55 _private member_ `FMemoryWriter MemoryWriter;`
- L56 _private member_ `TSharedRef<UE::Private::FPrettyJsonWriter> Writer;`
- L57 _private member_ `int32 InitialIndentLevel;`
- L58 _private member_ `TArray<FCustomVersion>& VersionsToHarvest;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Private` (scope `UE`)

### `Source/Runtime/Experimental/JsonObjectGraph/Private/JsonStringifyImpl.h` (Private)


#### struct `UE::Private::FJsonStringifyImpl`  
`struct FJsonStringifyImpl`  
_L23-125_
- L25 _public prototype_ `FJsonStringifyImpl(TConstArrayView<const UObject*> Roots, const FJsonStringifyOptions& Options);`
- L29 _public prototype_ `FUtf8String ToJson();` — Writes and returns the provided root objects as a UTF8 encode Json string, honoring options specified in our constructor:
- L36 _public prototype_ `void WriteObjectAsJsonToWriter(const UObject* OwningObject, const UObject* InObject, TSharedRef<FJsonWriter> WriterToUse);` — Helpers for writing to an object to a specific FJsonWriter, or specific FArchive. These are used by the native stream serializers and native structured serializers respectively - WriteObjectAsJsonToWriter is also used as objects are encountered in reflected properties. The owning object must be provided so that we can determine whether to write InObject as a peer reference, or inline. For root level serialization use ToJson():
- L37 _public prototype_ `void WriteObjectAsJsonToArchive(const UObject* OwningObject, const UObject* InObject, FArchive* ArchiveToUse, int32 InitialIndentLevel);`
- L40 _public prototype_ `void WriteFieldReferenceTo(const UObject* OwningObject, const FField* Value, TSharedRef<FJsonWriter> WriterToUse);` — Helper to improve support for FField references, which are not uncommon:
- L43 _private prototype_ `void ToJsonBytes();`
- L44 _private prototype_ `void WriteObjectToJson(const UObject* Object);`
- L49 _private prototype_ `void WriteNativeObjectData();` — Utility for unreflected UObject data - name, class, and flags - this data is placed into a special key for a loader that needs to order UObject construction (find archetypes, UClasses, UStructs, etc):
- L51 _private prototype_ `bool TryWriteInstanceDataObjectProperties(const UObject* ForObject);`
- L53 _private prototype_ `void WriteIndirectlyReferencedContainedObjects(const UObject* ForObject);`
- L54 _private prototype_ `FUtf8String WriteObjectReference(const UObject* Object) const;`
- L55 _private prototype_ `FUtf8String WriteFieldReference(const FField* Value) const;`
- L57 _private prototype_ `void WriteIdentifierAndValueToJson(const void* Container, const void* DefaultContainer, const FProperty* Property);`
- L58 _private prototype_ `void WriteValueToJson(const void* Value, const void* DefaultValue, const FProperty* Property);`
- L59 _private prototype_ `void WriteIntrinsicToJson(const void* Value, const FProperty* Property);`
- L62 _private prototype_ `void WriteStructToJsonWithIdentifier(const TCHAR* Identifier, const void* StructInstance, const void* DefaultInstance, const UScriptStruct* Struct, const UScriptStruct* DefaultStruct);` — May want to expose WriteStructToJsonWithIdentifier for users to manually write USTRUCT instances into json:
- L63 _private prototype_ `void WriteStructToJson(const void* StructInstance, const void* DefaultInstance, const UScriptStruct* Struct, const UScriptStruct* DefaultStruct);`
- L64 _private prototype_ `void WriteArrayToJson(const void* ArrayInstance, const FArrayProperty* Array);`
- L65 _private prototype_ `void WriteSetToJson(const void* SetInstance, const FSetProperty* SetProperty);`
- L66 _private prototype_ `void WriteMapToJson(const void* MapInstance, const FMapProperty* MapProperty);`
- L67 _private prototype_ `void WriteOptionalToJson(const void* OptionalInstnace, const FOptionalProperty* OptionalProperty);`
- L68 _private prototype_ `void WritePropertyBagDescToJson(const UPropertyBag* PropertyBag);`
- L70 _private prototype_ `TArray<uint8> SerialDataToJson(const UObject* Object, int32 InitialIndentLevel);`
- L72 _private prototype_ `TArray<uint8> StructuredDataToJson(const UObject* Object, int32 InitialIndentLevel);`
- L75 _private prototype_ `void WritePackageSummary();`
- L76 _private prototype_ `void WriteCustomVersions();`
- L77 _private prototype_ `void WritePackageMetadata();`
- L83 _private prototype_ `void WriteLinkerTables();` — Writes __LinkerNameTable and __LinkerImportTable into the package summary. In this configuration the live object graph contains placeholder stubs for imports, so the linker tables are the only reliable source for the full set of names and external references stored in the binary.
- L86 _private prototype_ `bool IsDeltaEncoding() const;`
- L88 _private member_ `const FJsonStringifyOptions& WriteOptions;`
- L90 _private member_ `TArray<uint8> Result;`
- L91 _private member_ `FMemoryWriter MemoryWriter;`
- L114 _private member_ `FPendingScope* CurrentScope = nullptr;`
- L116 _private member_ `TSharedRef<FJsonWriter> Writer;`
- L118 _private member_ `const UObject* CurrentObject;`
- L119 _private member_ `TArray<const UObject*> RootObjects;`
- L120 _private member_ `TSet<const UObject*> ObjectsToExport;`
- L121 _private member_ `TSet<const UObject*> ObjectsExported;`
- L122 _private member_ `const UPackage* RootPackage;`
- L124 _private member_ `TArray<FCustomVersion> Versions;`

#### struct `UE::Private::FJsonStringifyImpl::FPendingScope`  
`struct FPendingScope`  
_L95-113_
- desc: helper for enqueuing writes that may not need to be applied, e.g. if there are values that match the default value we won't write out the enclosing scope:
- L97 _public prototype_ `FPendingScope(FJsonStringifyImpl* To, const TFunction<void()>& Prefix);`
- L98 _public prototype_ `FPendingScope(FJsonStringifyImpl* To, const TFunction<void()>& Prefix, const TFunction<void()>& Postfix);`
- L99 _public prototype_ `~FPendingScope();`
- L100 _public prototype_ `void Apply();`
- L102 _private member_ `FJsonStringifyImpl* Owner = nullptr;`
- L103 _private member_ `FPendingScope* Outer = nullptr;`
- L104 _private member_ `TFunction<void()> PendingPrefix;`
- L105 _private member_ `TOptional<TFunction<void()>> PendingPostfix;`
- L107 _private member_ `bool bHasBeenApplied = false;`
- L109 _private prototype_ `FPendingScope(const FPendingScope& RHS) = delete;`
- L110 _private prototype_ `FPendingScope(FPendingScope&& RHS) = delete;`
- L111 _private prototype_ `FPendingScope& operator=(const FPendingScope& RHS) = delete;`
- L112 _private prototype_ `FPendingScope& operator=(FPendingScope&& RHS) = delete;`

#### Free symbols / members of external scopes

- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace Private` (scope `UE`)
- L21 _typedef_ `using FJsonWriter = FPrettyJsonWriter;` (scope `UE::Private`)

### `Source/Runtime/Experimental/JsonObjectGraph/Private/JsonStringifyStructuredArchive.h` (Private)


#### struct `UE::Private::FJsonStringifyStructuredArchive`  
`struct FJsonStringifyStructuredArchive : private FStructuredArchiveFormatter`  
_L22-136_
- inherits: `FStructuredArchiveFormatter`
- desc: FJsonStringifyStructuredArchive is an implementation detail of JsonObjectGraph. It provides support for saving the relatively rare data that provides a native Serialize(FStructuredArchive::FRecord) but explicitly disables serialization of reflected properties and versioning data, which are handled by the root implementation
- L24 _public prototype_ `FJsonStringifyStructuredArchive( const UObject* InObject, int32 InitialIndentLevel, FJsonStringifyImpl* InRootImpl, TArray<FCustomVersion>& InVersionsToHarvest, bool bFilterEditorOnly);`
- L32 _public prototype_ `TArray<uint8> ToJson();` — FMemoryWriter wants a byte array, so that's what we're working with at this level:
- L36 _public prototype_ `static void WriteTextValueInline(FText Value, int32 IndentLevel, FArchive& ToWriter);` — Unsure if we want to use the structured archive for FText or the string encoding long term, this provides us the option:
- L38 _public prototype_ `static void WriteCustomVersionValueInline(const TArray<FCustomVersion>& Version, int32 IndentLevel, FArchive& ToWriter);` — FCustomVersion is best encoded via operator<<(FStructuredArchive::FSlot Slot, FCustomVersion& Version):
- L40 _private prototype_ `FJsonStringifyStructuredArchive(FArchive& ToWriter, int32 InitialIndentLevel);`
- L42 _private prototype_ `virtual FArchive& GetUnderlyingArchive() override;`
- L44 _private prototype_ `virtual bool HasDocumentTree() const override;`
- L46 _private prototype_ `virtual void EnterRecord() override;`
- L47 _private prototype_ `virtual void LeaveRecord() override;`
- L48 _private prototype_ `virtual void EnterField(FArchiveFieldName Name) override;`
- L49 _private prototype_ `virtual void LeaveField() override;`
- L50 _private prototype_ `virtual bool TryEnterField(FArchiveFieldName Name, bool bEnterWhenSaving) override;`
- L52 _private prototype_ `virtual void EnterArray(int32& NumElements) override;`
- L53 _private prototype_ `virtual void LeaveArray() override;`
- L54 _private prototype_ `virtual void EnterArrayElement() override;`
- L55 _private prototype_ `virtual void LeaveArrayElement() override;`
- L57 _private prototype_ `virtual void EnterStream() override;`
- L58 _private prototype_ `virtual void LeaveStream() override;`
- L59 _private prototype_ `virtual void EnterStreamElement() override;`
- L60 _private prototype_ `virtual void LeaveStreamElement() override;`
- L62 _private prototype_ `virtual void EnterMap(int32& NumElements) override;`
- L63 _private prototype_ `virtual void LeaveMap() override;`
- L64 _private prototype_ `virtual void EnterMapElement(FString& Name) override;`
- L65 _private prototype_ `virtual void LeaveMapElement() override;`
- L67 _private prototype_ `virtual void EnterAttributedValue() override;`
- L68 _private prototype_ `virtual void EnterAttribute(FArchiveFieldName AttributeName) override;`
- L69 _private prototype_ `virtual void EnterAttributedValueValue() override;`
- L70 _private prototype_ `virtual void LeaveAttribute() override;`
- L71 _private prototype_ `virtual void LeaveAttributedValue() override;`
- L72 _private prototype_ `virtual bool TryEnterAttribute(FArchiveFieldName AttributeName, bool bEnterWhenSaving) override;`
- L74 _private prototype_ `virtual bool TryEnterAttributedValueValue() override;`
- L76 _private prototype_ `virtual void Serialize(uint8& Value) override;`
- L77 _private prototype_ `virtual void Serialize(uint16& Value) override;`
- L78 _private prototype_ `virtual void Serialize(uint32& Value) override;`
- L79 _private prototype_ `virtual void Serialize(uint64& Value) override;`
- L80 _private prototype_ `virtual void Serialize(int8& Value) override;`
- L81 _private prototype_ `virtual void Serialize(int16& Value) override;`
- L82 _private prototype_ `virtual void Serialize(int32& Value) override;`
- L83 _private prototype_ `virtual void Serialize(int64& Value) override;`
- L84 _private prototype_ `virtual void Serialize(float& Value) override;`
- L85 _private prototype_ `virtual void Serialize(double& Value) override;`
- L86 _private prototype_ `virtual void Serialize(bool& Value) override;`
- L87 _private prototype_ `virtual void Serialize(UTF32CHAR& Value) override;`
- L88 _private prototype_ `virtual void Serialize(FString& Value) override;`
- L89 _private prototype_ `virtual void Serialize(FName& Value) override;`
- L90 _private prototype_ `virtual void Serialize(UObject*& Value) override;`
- L92 _private prototype_ `virtual void Serialize(Verse::VCell*& Value) override;`
- L94 _private prototype_ `virtual void Serialize(FText& Value) override;`
- L95 _private prototype_ `virtual void Serialize(FWeakObjectPtr& Value) override;`
- L96 _private prototype_ `virtual void Serialize(FSoftObjectPtr& Value) override;`
- L97 _private prototype_ `virtual void Serialize(FSoftObjectPath& Value) override;`
- L98 _private prototype_ `virtual void Serialize(FLazyObjectPtr& Value) override;`
- L99 _private prototype_ `virtual void Serialize(FObjectPtr& Value) override;`
- L100 _private prototype_ `virtual void Serialize(TArray<uint8>& Value) override;`
- L101 _private prototype_ `virtual void Serialize(void* Data, uint64 DataSize) override;`
- L103 _private prototype_ `void Write(ANSICHAR Character);`
- L105 _private prototype_ `void Write(const ANSICHAR* Text);`
- L106 _private prototype_ `void Write(const FString& Text);`
- L108 _private prototype_ `void WriteFieldName(const TCHAR* Name);`
- L109 _private prototype_ `void WriteValue(const FString& Value);`
- L111 _private prototype_ `void WriteOptionalComma();`
- L112 _private prototype_ `void WriteOptionalNewline();`
- L113 _private prototype_ `void WriteOptionalAttributedBlockOpening();`
- L114 _private prototype_ `void WriteOptionalAttributedBlockValue();`
- L115 _private prototype_ `void WriteOptionalAttributedBlockClosing();`
- L117 _private prototype_ `void SerializeStringInternal(const FString& String);`
- L119 _private member_ `TArray<FCustomVersion>* VersionsToHarvest;`
- L120 _private member_ `TArray<ANSICHAR> Newline;`
- L122 _private member_ `TArray<int32> NumAttributesStack;`
- L123 _private member_ `TArray<int64> TextStartPosStack;`
- L125 _private member_ `const UObject* const Object;`
- L126 _private member_ `FJsonStringifyImpl* RootImpl;`
- L128 _private member_ `TArray<uint8> ResultBuff;`
- L129 _private member_ `FMemoryWriter Inner;`
- L130 _private member_ `FArchive* Override = nullptr;`
- L132 _private member_ `int64_t ScopeSkipCount = 0;`
- L133 _private member_ `int32_t IndentLevel = 0;`
- L134 _private member_ `bool bNeedsComma = false;`
- L135 _private member_ `bool bNeedsNewline = false;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Private` (scope `UE`)

### `Source/Runtime/Experimental/JsonObjectGraph/Private/PrettyJsonWriter.h` (Private)


#### struct `UE::Private::TPrettyJsonPrintPolicySingleNewLine`  
`struct TPrettyJsonPrintPolicySingleNewLine : public TPrettyJsonPrintPolicy<UTF8CHAR>`  
_L10-17_
- inherits: `TPrettyJsonPrintPolicy<UTF8CHAR>`
- L13 _public function_ `static inline void WriteLineTerminator(FArchive* Stream)`

#### struct `UE::Private::FPrettyJsonWriter`  
`struct FPrettyJsonWriter : public TJsonWriter<UTF8CHAR, TPrettyJsonPrintPolicySingleNewLine>`  
_L20-57_
- inherits: `TJsonWriter<UTF8CHAR,TPrettyJsonPrintPolicySingleNewLine>`
- desc: Extending TJsonWriter to get some control over whitespace and tabbing:
- L22 _public typedef_ `using Super = TJsonWriter<UTF8CHAR, TPrettyJsonPrintPolicySingleNewLine>;`
- L23 _public typedef_ `using PrintPolicy = TPrettyJsonPrintPolicySingleNewLine;`
- L24 _public typedef_ `using CharType = UTF8CHAR;`
- L26 _public prototype_ `FPrettyJsonWriter(FArchive* const InStream, int32 InitialIndentLevel);`
- L28 _public prototype_ `static TSharedRef<FPrettyJsonWriter> Create(FArchive* const InStream, int32 InitialIndent = 0);`
- L31 _public prototype_ `void WriteJsonRaw(FAnsiStringView Value);` — useful for composing blocks of json
- L33 _public prototype_ `void WriteValueInline(FText Value);`
- L34 _public prototype_ `void WriteValueInline(const FString& Value);`
- L35 _public prototype_ `void WriteValueInline(FAnsiStringView UTF8Value);`
- L36 _public prototype_ `void WriteValueInline(FUtf8StringView UTF8Value);`
- L37 _public prototype_ `void WriteValueInline(int16 Value);`
- L38 _public prototype_ `void WriteValueInline(uint16 Value);`
- L39 _public prototype_ `void WriteValueInline(uint32 Value);`
- L41 _public function_ `template<typename T> void WriteValueInline(T Value)`
- L47 _public prototype_ `void WriteUtf8Value(FStringView Identifier, FUtf8StringView UTF8Value);`
- L49 _public prototype_ `void WriteObjectStartInline();`
- L50 _public prototype_ `void WriteArrayStartInline();`
- L51 _public prototype_ `void WriteNewlineAndArrayEnd();`
- L52 _public prototype_ `void WriteLineTerminator();`
- L53 _public prototype_ `void HACK_SetPreviousTokenWritten();`
- L54 _public prototype_ `void HACK_SetPreviousTokenWrittenSquareClose();`
- L56 _public prototype_ `void WriteCommaAndNewlineIfNeeded();`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace Private` (scope `UE`)

### `Source/Runtime/Experimental/JsonObjectGraph/Public/JsonObjectGraph/Stringify.h` (Public)


#### enum `EJsonStringifyFlags`  
`enum class EJsonStringifyFlags : uint8`  
_L13-23_
- reflection: `UENUM(BlueprintType, Flags, meta = (Bitflags, UseEnumValuesAsMaskValuesInEditor = "true"))`
- L16 _public enumerator_ `Default = 0` — The default representation of an object attempts to be complete and stable across time
- L18 _public enumerator_ `FilterEditorOnlyData = 1 << 0` — Filters editor only data such that it is not written to the Json
- L20 _public enumerator_ `DisableDeltaEncoding = 1 << 1` — Disables delta encoding such that all properties are encoded in the Json, rather than only changes from the objects' archetypes
- L22 _public enumerator_ `DisableNativeSerializers = 1 << 2` — Disables running the native serializers, reduces size and improves performance when the native data is less important

#### struct `FJsonStringifyOptions`  
`struct FJsonStringifyOptions`  
_L27-45_
- reflection: `USTRUCT(BlueprintType)`
- L31 _public function_ `FJsonStringifyOptions(EJsonStringifyFlags InFlags) : Flags(InFlags)`
- L36 _public prototype_ `FJsonStringifyOptions() = default;`
- L37 _public prototype_ `~FJsonStringifyOptions() = default;`
- L38 _public prototype_ `FJsonStringifyOptions(const FJsonStringifyOptions&) = default;`
- L39 _public prototype_ `FJsonStringifyOptions(FJsonStringifyOptions&&) = default;`
- L40 _public prototype_ `FJsonStringifyOptions& operator=(const FJsonStringifyOptions&) = default;`
- L41 _public prototype_ `FJsonStringifyOptions& operator=(FJsonStringifyOptions&&) = default;`
- L44 _public member_ `EJsonStringifyFlags Flags = EJsonStringifyFlags::Default;` — `UPROPERTY(BlueprintReadWrite, Category = "Options")`

#### Free symbols / members of external scopes

- L24 _prototype_ `ENUM_CLASS_FLAGS(EJsonStringifyFlags);`
- L47 _namespace_ `namespace UE`
- L47 _namespace_ `namespace JsonObjectGraph` (scope `UE`)
- L56 _prototype_ `FUtf8String Stringify(TConstArrayView<const UObject*> RootObjects, const FJsonStringifyOptions& Options = FJsonStringifyOptions());` (scope `UE::JsonObjectGraph`) — ! EXPERIMENTAL ! contents of return string will change. Currently this is used as a debugging facility. @return: A string containing single JSON object with serialized representations of the provided Objects in that single object's __RootObjects field.
