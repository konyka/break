# Plugins / XmlSerialization

- module root: `Plugins/Experimental/SerializationUtils/Source/XmlSerialization`
- headers: 8; symbols: 171
- symbol kinds: class=5, delegate=1, enum=1, enumerator=8, function=9, macro=4, member=12, namespace=8, prototype=123
- PrivateDependencyModuleNames: Serialization, pugixml
- PublicDependencyModuleNames: Core, CoreUObject

### `Plugins/Experimental/SerializationUtils/Source/XmlSerialization/Private/Formatters/XmlFormatterHelper.h` (Private)


#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace XmlSerialization` (scope `UE`)
- L11 _namespace_ `namespace Private` (scope `UE::XmlSerialization`)
- L11 _namespace_ `namespace FormatterHelper` (scope `UE::XmlSerialization::Private`)
- L13 _prototype_ `void SerializeObject(FStructuredArchiveRecord& InRootRecord, UObject* InObject , const TFunction<bool(FProperty*)>& ShouldSkipProperty = TFunction<bool(FProperty*)>());` (scope `UE::XmlSerialization::Private::FormatterHelper`)

### `Plugins/Experimental/SerializationUtils/Source/XmlSerialization/Private/Utils/XmlUtils.h` (Private)


#### Free symbols / members of external scopes

- L20 _macro_ `# define STRING_CAST_UE_TO_PUGI(InString) InString`
- L21 _macro_ `# define STRING_CAST_PUGI_TO_UE(InString) InString`
- L23 _macro_ `# define STRING_CAST_UE_TO_PUGI(InString) StringCast<ANSICHAR>(InString).Get()`
- L24 _macro_ `# define STRING_CAST_PUGI_TO_UE(InString) StringCast<TCHAR>(InString).Get()`
- L27 _namespace_ `namespace UE`
- L27 _namespace_ `namespace XmlSerialization` (scope `UE`)
- L27 _namespace_ `namespace Private` (scope `UE::XmlSerialization`)
- L27 _namespace_ `namespace Utils` (scope `UE::XmlSerialization::Private`)
- L30 _function_ `inline FString GetInfo(const pugi::xml_node& XmlElement)` (scope `UE::XmlSerialization::Private::Utils`) — Helper for pretty log
- L43 _function_ `inline bool IsElementA(const pugi::xml_node& Element, const TCHAR* TagName)` (scope `UE::XmlSerialization::Private::Utils`)
- L48 _function_ `inline bool IsElementShouldBe(const pugi::xml_node& Element, const TCHAR* TagName)` (scope `UE::XmlSerialization::Private::Utils`)
- L58 _function_ `inline pugi::xml_encoding ToPugiEncoding(EXmlSerializationEncoding InEncoding)` (scope `UE::XmlSerialization::Private::Utils`)

### `Plugins/Experimental/SerializationUtils/Source/XmlSerialization/Private/Utils/XmlWriter.h` (Private)


#### class `FXmlWriter`  
`class FXmlWriter : public pugi::xml_writer`  
_L9-23_
- inherits: `pugi::xml_writer`
- L12 _public function_ `FXmlWriter( FArchive* const InStream) : Stream(InStream)`
- L14 _public function_ `virtual void write(const void* data, size_t size) override`
- L22 _private member_ `FArchive* const Stream;`

### `Plugins/Experimental/SerializationUtils/Source/XmlSerialization/Private/XmlSerializationModule.h` (Private)


#### class `FXmlSerializationModule`  
`class FXmlSerializationModule : public IModuleInterface`  
_L10-17_
- inherits: `IModuleInterface`
- L14 _public prototype_ `virtual void StartupModule() override;`
- L15 _public prototype_ `virtual void ShutdownModule() override;`

#### Free symbols / members of external scopes

- L8 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogXmlSerialization, Log, All);`
- L8 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogXmlSerialization, Log, All);`

### `Plugins/Experimental/SerializationUtils/Source/XmlSerialization/Public/Backends/XmlStructSerializerBackend.h` (Public)


#### class `FXmlStructSerializerBackend`  
`class FXmlStructSerializerBackend : public IStructSerializerBackend`  
_L11-47_
- inherits: `IStructSerializerBackend`
- desc: Implements a writer for UStruct serialization using Xml.
- L22 _public prototype_ `FXmlStructSerializerBackend( FArchive& InArchive, const EStructSerializerBackendFlags InFlags );` — Creates and initializes a new instance with the given flags. @param InArchive The archive to serialize into. @param InFlags The flags that control the serialization behavior (typically EStructSerializerBackendFlags::Default).
- L29 _public prototype_ `void SaveDocument(EXmlSerializationEncoding InEncoding = EXmlSerializationEncoding::Utf8);` — Flush to archive.
- L32 _public prototype_ `virtual void BeginArray(const FStructSerializerState& InState) override;`
- L33 _public prototype_ `virtual void BeginStructure(const FStructSerializerState& InState) override;`
- L34 _public prototype_ `virtual void EndArray(const FStructSerializerState& InState) override;`
- L35 _public prototype_ `virtual void EndStructure(const FStructSerializerState& InState) override;`
- L36 _public prototype_ `virtual void WriteComment(const FString& InComment) override;`
- L37 _public prototype_ `virtual void WriteProperty(const FStructSerializerState& InState, int32 InArrayIndex) override;`
- L43 _private member_ `FImpl* Impl;`
- L46 _private member_ `EStructSerializerBackendFlags Flags;` — Flags controlling the serialization behavior.

### `Plugins/Experimental/SerializationUtils/Source/XmlSerialization/Public/Formatters/XmlArchiveInputFormatter.h` (Public)


#### class `FXmlArchiveInputFormatter`  
`class FXmlArchiveInputFormatter final : public FStructuredArchiveFormatter`  
_L11-97_
- inherits: `FStructuredArchiveFormatter`
- L21 _public prototype_ `FXmlArchiveInputFormatter(FArchive& InInner, UObject* InRootObject, const TFunction<UObject* (const FPackageIndex)>& InResolveObject = nullptr);` — Parse the given archive into an xml DOM for deserializing objects. @param InInner Inner archive to read from. The whole archive is read in the constructor to parse into xml DOM. @param InRootObject Specifies the root object to be the owner for nested objects. Can't be null. @param InResolveObject Resolves reference for the UObject properties. This is not used if objects where serialized nested.
- L22 _public prototype_ `FXmlArchiveInputFormatter(const FXmlArchiveInputFormatter& InOther);`
- L26 _public prototype_ `bool IsParseResultStatusOk() const;`
- L28 _public prototype_ `virtual FArchive& GetUnderlyingArchive() override;`
- L29 _public prototype_ `virtual FStructuredArchiveFormatter* CreateSubtreeReader() override;`
- L31 _public prototype_ `virtual bool HasDocumentTree() const override;`
- L33 _public prototype_ `virtual void EnterRecord() override;`
- L34 _public prototype_ `virtual void LeaveRecord() override;`
- L35 _public prototype_ `virtual void EnterField(FArchiveFieldName InName) override;`
- L36 _public prototype_ `virtual void LeaveField() override;`
- L37 _public prototype_ `virtual bool TryEnterField(FArchiveFieldName InName, bool bInEnterWhenSaving) override;`
- L39 _public prototype_ `virtual void EnterArray(int32& OutNumElements) override;`
- L40 _public prototype_ `virtual void LeaveArray() override;`
- L41 _public prototype_ `virtual void EnterArrayElement() override;`
- L42 _public prototype_ `virtual void LeaveArrayElement() override;`
- L44 _public prototype_ `virtual void EnterStream() override;`
- L45 _public prototype_ `virtual void LeaveStream() override;`
- L46 _public prototype_ `virtual void EnterStreamElement() override;`
- L47 _public prototype_ `virtual void LeaveStreamElement() override;`
- L49 _public prototype_ `virtual void EnterMap(int32& OutNumElements) override;`
- L50 _public prototype_ `virtual void LeaveMap() override;`
- L51 _public prototype_ `virtual void EnterMapElement(FString& OutName) override;`
- L52 _public prototype_ `virtual void LeaveMapElement() override;`
- L54 _public prototype_ `virtual void EnterAttributedValue() override;`
- L55 _public prototype_ `virtual void EnterAttribute(FArchiveFieldName InAttributeName) override;`
- L56 _public prototype_ `virtual void EnterAttributedValueValue() override;`
- L57 _public prototype_ `virtual void LeaveAttribute() override;`
- L58 _public prototype_ `virtual void LeaveAttributedValue() override;`
- L59 _public prototype_ `virtual bool TryEnterAttribute(FArchiveFieldName InAttributeName, bool bInEnterWhenSavin) override;`
- L60 _public prototype_ `virtual bool TryEnterAttributedValueValue() override;`
- L62 _public prototype_ `virtual void Serialize(uint8& Value) override;`
- L63 _public prototype_ `virtual void Serialize(uint16& Value) override;`
- L64 _public prototype_ `virtual void Serialize(uint32& Value) override;`
- L65 _public prototype_ `virtual void Serialize(uint64& Value) override;`
- L66 _public prototype_ `virtual void Serialize(int8& Value) override;`
- L67 _public prototype_ `virtual void Serialize(int16& Value) override;`
- L68 _public prototype_ `virtual void Serialize(int32& Value) override;`
- L69 _public prototype_ `virtual void Serialize(int64& Value) override;`
- L70 _public prototype_ `virtual void Serialize(float& Value) override;`
- L71 _public prototype_ `virtual void Serialize(double& Value) override;`
- L72 _public prototype_ `virtual void Serialize(bool& Value) override;`
- L73 _public prototype_ `virtual void Serialize(UTF32CHAR& Value) override;`
- L74 _public prototype_ `virtual void Serialize(FString& Value) override;`
- L75 _public prototype_ `virtual void Serialize(FName& Value) override;`
- L76 _public prototype_ `virtual void Serialize(UObject*& Value) override;`
- L77 _public prototype_ `virtual void Serialize(FText& Value) override;`
- L78 _public prototype_ `virtual void Serialize(FWeakObjectPtr& Value) override;`
- L79 _public prototype_ `virtual void Serialize(FSoftObjectPtr& Value) override;`
- L80 _public prototype_ `virtual void Serialize(FSoftObjectPath& Value) override;`
- L81 _public prototype_ `virtual void Serialize(FLazyObjectPtr& Value) override;`
- L82 _public prototype_ `virtual void Serialize(FObjectPtr& Value) override;`
- L83 _public prototype_ `virtual void Serialize(TArray<uint8>& Value) override;`
- L84 _public prototype_ `virtual void Serialize(void* Data, uint64 DataSize) override;`
- L87 _private prototype_ `bool IsNestedObject() const;`
- L88 _private prototype_ `UObject* LoadNestedObject();`
- L92 _private member_ `FImpl* Impl;`
- L94 _private member_ `FArchive& Inner;`
- L95 _private member_ `TFunction<UObject* (const FPackageIndex)> ResolveObject;`
- L96 _private member_ `UObject* RootObject;`

### `Plugins/Experimental/SerializationUtils/Source/XmlSerialization/Public/Formatters/XmlArchiveOutputFormatter.h` (Public)


#### class `FXmlArchiveOutputFormatter`  
`class FXmlArchiveOutputFormatter final : public FStructuredArchiveFormatter`  
_L11-109_
- inherits: `FStructuredArchiveFormatter`
- L15 _private prototype_ `FXmlArchiveOutputFormatter(FXmlArchiveOutputFormatter&) = delete;` — Non-copyable - Need to implement if needed.
- L16 _private prototype_ `FXmlArchiveOutputFormatter& operator=(const FXmlArchiveOutputFormatter&) = delete;`
- L18 _private prototype_ `FXmlArchiveOutputFormatter(FXmlArchiveOutputFormatter&&) = delete;` — Non-movable - Need to implement if needed.
- L19 _private prototype_ `FXmlArchiveOutputFormatter& operator=(FXmlArchiveOutputFormatter&&) = delete;`
- L25 _public prototype_ `FXmlArchiveOutputFormatter(FArchive& InInner);` — @remark Inner archive must remain valid throughout the lifetime of this object.
- L29 _public prototype_ `bool SaveDocumentToInnerArchive(EXmlSerializationEncoding InEncoding = EXmlSerializationEncoding::Utf8);`
- L31 _public function_ `void SerializeObjectsInPlace(bool bEnabled)`
- L32 _public function_ `void SerializeSoftObjectsInPlace(bool bEnabled)`
- L34 _public prototype_ `virtual FArchive& GetUnderlyingArchive() override;`
- L36 _public prototype_ `virtual bool HasDocumentTree() const override;`
- L38 _public prototype_ `virtual void EnterRecord() override;`
- L39 _public prototype_ `virtual void LeaveRecord() override;`
- L40 _public prototype_ `virtual void EnterField(FArchiveFieldName Name) override;`
- L41 _public prototype_ `virtual void LeaveField() override;`
- L42 _public prototype_ `virtual bool TryEnterField(FArchiveFieldName Name, bool bEnterWhenSaving) override;`
- L44 _public prototype_ `virtual void EnterArray(int32& NumElements) override;`
- L45 _public prototype_ `virtual void LeaveArray() override;`
- L46 _public prototype_ `virtual void EnterArrayElement() override;`
- L47 _public prototype_ `virtual void LeaveArrayElement() override;`
- L49 _public prototype_ `virtual void EnterStream() override;`
- L50 _public prototype_ `virtual void LeaveStream() override;`
- L51 _public prototype_ `virtual void EnterStreamElement() override;`
- L52 _public prototype_ `virtual void LeaveStreamElement() override;`
- L54 _public prototype_ `virtual void EnterMap(int32& NumElements) override;`
- L55 _public prototype_ `virtual void LeaveMap() override;`
- L56 _public prototype_ `virtual void EnterMapElement(FString& Name) override;`
- L57 _public prototype_ `virtual void LeaveMapElement() override;`
- L59 _public prototype_ `virtual void EnterAttributedValue() override;`
- L60 _public prototype_ `virtual void EnterAttribute(FArchiveFieldName AttributeName) override;`
- L61 _public prototype_ `virtual void EnterAttributedValueValue() override;`
- L62 _public prototype_ `virtual void LeaveAttribute() override;`
- L63 _public prototype_ `virtual void LeaveAttributedValue() override;`
- L64 _public prototype_ `virtual bool TryEnterAttribute(FArchiveFieldName AttributeName, bool bEnterWhenSaving) override;`
- L66 _public prototype_ `virtual bool TryEnterAttributedValueValue() override;`
- L68 _public prototype_ `virtual void Serialize(uint8& Value) override;`
- L69 _public prototype_ `virtual void Serialize(uint16& Value) override;`
- L70 _public prototype_ `virtual void Serialize(uint32& Value) override;`
- L71 _public prototype_ `virtual void Serialize(uint64& Value) override;`
- L72 _public prototype_ `virtual void Serialize(int8& Value) override;`
- L73 _public prototype_ `virtual void Serialize(int16& Value) override;`
- L74 _public prototype_ `virtual void Serialize(int32& Value) override;`
- L75 _public prototype_ `virtual void Serialize(int64& Value) override;`
- L76 _public prototype_ `virtual void Serialize(float& Value) override;`
- L77 _public prototype_ `virtual void Serialize(double& Value) override;`
- L78 _public prototype_ `virtual void Serialize(bool& Value) override;`
- L79 _public prototype_ `virtual void Serialize(UTF32CHAR& Value) override;`
- L80 _public prototype_ `virtual void Serialize(FString& Value) override;`
- L81 _public prototype_ `virtual void Serialize(FName& Value) override;`
- L82 _public prototype_ `virtual void Serialize(UObject*& Value) override;`
- L83 _public prototype_ `virtual void Serialize(FText& Value) override;`
- L84 _public prototype_ `virtual void Serialize(FWeakObjectPtr& Value) override;`
- L85 _public prototype_ `virtual void Serialize(FSoftObjectPtr& Value) override;`
- L86 _public prototype_ `virtual void Serialize(FSoftObjectPath& Value) override;`
- L87 _public prototype_ `virtual void Serialize(FLazyObjectPtr& Value) override;`
- L88 _public prototype_ `virtual void Serialize(FObjectPtr& Value) override;`
- L89 _public prototype_ `virtual void Serialize(TArray<uint8>& Value) override;`
- L90 _public prototype_ `virtual void Serialize(void* Data, uint64 DataSize) override;`
- L92 _public function_ `void SetObjectIndicesMap(const TMap<UObject*, FPackageIndex>* InObjectIndicesMap)`
- L98 _private prototype_ `bool IsObjectAllowed(UObject* InObject) const;`
- L102 _private member_ `FImpl* Impl;`
- L104 _private member_ `FArchive& Inner;`
- L106 _private member_ `const TMap<UObject*, FPackageIndex>* ObjectIndicesMap = nullptr;`
- L107 _private member_ `bool bSerializeObjectsInPlace = false;`
- L108 _private member_ `bool bSerializeSoftObjectsInPlace = false;`

### `Plugins/Experimental/SerializationUtils/Source/XmlSerialization/Public/XmlSerializationDefines.h` (Public)


#### enum `EXmlSerializationEncoding`  
`enum class EXmlSerializationEncoding`  
_L6-24_
- desc: These flags determine the encoding of input data for XML document.
- L9 _public enumerator_ `Utf8` — UTF8 encoding
- L11 _public enumerator_ `Utf16_Le` — Little-endian UTF16
- L13 _public enumerator_ `Utf16_Be` — Big-endian UTF16
- L15 _public enumerator_ `Utf16` — UTF16 with native endianness
- L17 _public enumerator_ `Utf32_Le` — Little-endian UTF32
- L19 _public enumerator_ `Utf32_Be` — Big-endian UTF32
- L21 _public enumerator_ `Utf32` — UTF32 with native endianness
- L23 _public enumerator_ `WChar` — The same encoding wchar_t has (either UTF16 or UTF32)
