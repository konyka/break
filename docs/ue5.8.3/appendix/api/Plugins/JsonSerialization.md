# Plugins / JsonSerialization

- module root: `Plugins/Experimental/SerializationUtils/Source/JsonSerialization`
- headers: 3; symbols: 150
- symbol kinds: class=3, delegate=1, function=4, member=18, prototype=123, struct=1
- PrivateDependencyModuleNames: Serialization
- PublicDependencyModuleNames: Core, CoreUObject, Json

### `Plugins/Experimental/SerializationUtils/Source/JsonSerialization/Private/JsonSerializationModule.h` (Private)


#### class `FJsonSerializationModule`  
`class FJsonSerializationModule : public IModuleInterface`  
_L10-17_
- inherits: `IModuleInterface`
- L14 _public prototype_ `virtual void StartupModule() override;`
- L15 _public prototype_ `virtual void ShutdownModule() override;`

#### Free symbols / members of external scopes

- L8 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogJsonSerialization, Log, All);`
- L8 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogJsonSerialization, Log, All);`

### `Plugins/Experimental/SerializationUtils/Source/JsonSerialization/Public/Formatters/JsonArchiveInputFormatterEx.h` (Public)


#### class `FJsonArchiveInputFormatterEx`  
`class FJsonArchiveInputFormatterEx final : public FStructuredArchiveFormatter`  
_L32-129_
- inherits: `FStructuredArchiveFormatter`
- L35 _public prototype_ `FJsonArchiveInputFormatterEx(FArchive& InInner, UObject* InRootObject, TFunction<UObject* (const FPackageIndex)> InResolveObject = nullptr);`
- L38 _public prototype_ `virtual FArchive& GetUnderlyingArchive() override;`
- L39 _public prototype_ `virtual FStructuredArchiveFormatter* CreateSubtreeReader() override;`
- L41 _public prototype_ `virtual bool HasDocumentTree() const override;`
- L43 _public prototype_ `virtual void EnterRecord() override;`
- L44 _public prototype_ `virtual void LeaveRecord() override;`
- L45 _public prototype_ `virtual void EnterField(FArchiveFieldName Name) override;`
- L46 _public prototype_ `virtual void LeaveField() override;`
- L47 _public prototype_ `virtual bool TryEnterField(FArchiveFieldName Name, bool bEnterWhenSaving) override;`
- L49 _public prototype_ `virtual void EnterArray(int32& NumElements) override;`
- L50 _public prototype_ `virtual void LeaveArray() override;`
- L51 _public prototype_ `virtual void EnterArrayElement() override;`
- L52 _public prototype_ `virtual void LeaveArrayElement() override;`
- L54 _public prototype_ `virtual void EnterStream() override;`
- L55 _public prototype_ `virtual void LeaveStream() override;`
- L56 _public prototype_ `virtual void EnterStreamElement() override;`
- L57 _public prototype_ `virtual void LeaveStreamElement() override;`
- L59 _public prototype_ `virtual void EnterMap(int32& NumElements) override;`
- L60 _public prototype_ `virtual void LeaveMap() override;`
- L61 _public prototype_ `virtual void EnterMapElement(FString& Name) override;`
- L62 _public prototype_ `virtual void LeaveMapElement() override;`
- L64 _public prototype_ `virtual void EnterAttributedValue() override;`
- L65 _public prototype_ `virtual void EnterAttribute(FArchiveFieldName AttributeName) override;`
- L66 _public prototype_ `virtual void EnterAttributedValueValue() override;`
- L67 _public prototype_ `virtual void LeaveAttribute() override;`
- L68 _public prototype_ `virtual void LeaveAttributedValue() override;`
- L69 _public prototype_ `virtual bool TryEnterAttribute(FArchiveFieldName AttributeName, bool bEnterWhenSavin) override;`
- L70 _public prototype_ `virtual bool TryEnterAttributedValueValue() override;`
- L72 _public prototype_ `virtual void Serialize(uint8& Value) override;`
- L73 _public prototype_ `virtual void Serialize(uint16& Value) override;`
- L74 _public prototype_ `virtual void Serialize(uint32& Value) override;`
- L75 _public prototype_ `virtual void Serialize(uint64& Value) override;`
- L76 _public prototype_ `virtual void Serialize(int8& Value) override;`
- L77 _public prototype_ `virtual void Serialize(int16& Value) override;`
- L78 _public prototype_ `virtual void Serialize(int32& Value) override;`
- L79 _public prototype_ `virtual void Serialize(int64& Value) override;`
- L80 _public prototype_ `virtual void Serialize(float& Value) override;`
- L81 _public prototype_ `virtual void Serialize(double& Value) override;`
- L82 _public prototype_ `virtual void Serialize(bool& Value) override;`
- L83 _public prototype_ `virtual void Serialize(UTF32CHAR& Value) override;`
- L84 _public prototype_ `virtual void Serialize(FString& Value) override;`
- L85 _public prototype_ `virtual void Serialize(FName& Value) override;`
- L86 _public prototype_ `virtual void Serialize(UObject*& Value) override;`
- L88 _public prototype_ `virtual void Serialize(Verse::VCell*& Value) override;`
- L90 _public prototype_ `virtual void Serialize(FText& Value) override;`
- L91 _public prototype_ `virtual void Serialize(FWeakObjectPtr& Value) override;`
- L92 _public prototype_ `virtual void Serialize(FSoftObjectPtr& Value) override;`
- L93 _public prototype_ `virtual void Serialize(FSoftObjectPath& Value) override;`
- L94 _public prototype_ `virtual void Serialize(FLazyObjectPtr& Value) override;`
- L95 _public prototype_ `virtual void Serialize(FObjectPtr& Value) override;`
- L96 _public prototype_ `virtual void Serialize(TArray<uint8>& Value) override;`
- L97 _public prototype_ `virtual void Serialize(void* Data, uint64 DataSize) override;`
- L100 _private prototype_ `bool IsNestedObject();`
- L101 _private prototype_ `UObject* LoadNestedObject();`
- L103 _private member_ `FArchive& Inner;`
- L118 _private member_ `TFunction<UObject* (const FPackageIndex)> ResolveObject;`
- L119 _private member_ `UObject* RootObject;`
- L120 _private member_ `TArray<FObjectRecord> ObjectStack;`
- L121 _private member_ `TArray<TSharedPtr<FJsonValue>> ValueStack;`
- L122 _private member_ `TArray<TMap<FJsonObject::FStringType, TSharedPtr<FJsonValue>>::TIterator> MapIteratorStack;`
- L123 _private member_ `TArray<int32> ArrayValuesRemainingStack;`
- L125 _private prototype_ `static FString EscapeFieldName(const TCHAR* Name);`
- L126 _private prototype_ `static FString UnescapeFieldName(const TCHAR* Name);`
- L128 _private prototype_ `static EArchiveValueType GetValueType(const FJsonValue &Value);`

#### struct `FJsonArchiveInputFormatterEx::FObjectRecord`  
`struct FObjectRecord`  
_L105-116_
- L107 _public function_ `FObjectRecord(TSharedPtr<FJsonObject> InJsonObject, int64 InValueCount) : JsonObject(InJsonObject) , ValueCountOnCreation(InValueCount)`
- L114 _public member_ `TSharedPtr<FJsonObject> JsonObject;`
- L115 _public member_ `int64 ValueCountOnCreation;` — For debugging purposes, so we can ensure all values have been consumed

### `Plugins/Experimental/SerializationUtils/Source/JsonSerialization/Public/Formatters/JsonArchiveOutputFormatterEx.h` (Public)


#### class `FJsonArchiveOutputFormatterEx`  
`class FJsonArchiveOutputFormatterEx : public FStructuredArchiveFormatter`  
_L27-133_
- inherits: `FStructuredArchiveFormatter`
- L30 _public prototype_ `FJsonArchiveOutputFormatterEx(FArchive& InInner);`
- L33 _public function_ `void SerializeObjectsInPlace(bool bEnabled)`
- L34 _public function_ `void SerializeSoftObjectsInPlace(bool bEnabled)`
- L36 _public prototype_ `virtual FArchive& GetUnderlyingArchive() override;`
- L38 _public prototype_ `virtual bool HasDocumentTree() const override;`
- L40 _public prototype_ `virtual void EnterRecord() override;`
- L41 _public prototype_ `virtual void LeaveRecord() override;`
- L42 _public prototype_ `virtual void EnterField(FArchiveFieldName Name) override;`
- L43 _public prototype_ `virtual void LeaveField() override;`
- L44 _public prototype_ `virtual bool TryEnterField(FArchiveFieldName Name, bool bEnterWhenSaving) override;`
- L46 _public prototype_ `virtual void EnterArray(int32& NumElements) override;`
- L47 _public prototype_ `virtual void LeaveArray() override;`
- L48 _public prototype_ `virtual void EnterArrayElement() override;`
- L49 _public prototype_ `virtual void LeaveArrayElement() override;`
- L51 _public prototype_ `virtual void EnterStream() override;`
- L52 _public prototype_ `virtual void LeaveStream() override;`
- L53 _public prototype_ `virtual void EnterStreamElement() override;`
- L54 _public prototype_ `virtual void LeaveStreamElement() override;`
- L56 _public prototype_ `virtual void EnterMap(int32& NumElements) override;`
- L57 _public prototype_ `virtual void LeaveMap() override;`
- L58 _public prototype_ `virtual void EnterMapElement(FString& Name) override;`
- L59 _public prototype_ `virtual void LeaveMapElement() override;`
- L61 _public prototype_ `virtual void EnterAttributedValue() override;`
- L62 _public prototype_ `virtual void EnterAttribute(FArchiveFieldName AttributeName) override;`
- L63 _public prototype_ `virtual void EnterAttributedValueValue() override;`
- L64 _public prototype_ `virtual void LeaveAttribute() override;`
- L65 _public prototype_ `virtual void LeaveAttributedValue() override;`
- L66 _public prototype_ `virtual bool TryEnterAttribute(FArchiveFieldName AttributeName, bool bEnterWhenSaving) override;`
- L68 _public prototype_ `virtual bool TryEnterAttributedValueValue() override;`
- L70 _public prototype_ `virtual void Serialize(uint8& Value) override;`
- L71 _public prototype_ `virtual void Serialize(uint16& Value) override;`
- L72 _public prototype_ `virtual void Serialize(uint32& Value) override;`
- L73 _public prototype_ `virtual void Serialize(uint64& Value) override;`
- L74 _public prototype_ `virtual void Serialize(int8& Value) override;`
- L75 _public prototype_ `virtual void Serialize(int16& Value) override;`
- L76 _public prototype_ `virtual void Serialize(int32& Value) override;`
- L77 _public prototype_ `virtual void Serialize(int64& Value) override;`
- L78 _public prototype_ `virtual void Serialize(float& Value) override;`
- L79 _public prototype_ `virtual void Serialize(double& Value) override;`
- L80 _public prototype_ `virtual void Serialize(bool& Value) override;`
- L81 _public prototype_ `virtual void Serialize(UTF32CHAR& Value) override;`
- L82 _public prototype_ `virtual void Serialize(FString& Value) override;`
- L83 _public prototype_ `virtual void Serialize(FName& Value) override;`
- L84 _public prototype_ `virtual void Serialize(UObject*& Value) override;`
- L86 _public prototype_ `virtual void Serialize(Verse::VCell*& Value) override;`
- L88 _public prototype_ `virtual void Serialize(FText& Value) override;`
- L89 _public prototype_ `virtual void Serialize(FWeakObjectPtr& Value) override;`
- L90 _public prototype_ `virtual void Serialize(FSoftObjectPtr& Value) override;`
- L91 _public prototype_ `virtual void Serialize(FSoftObjectPath& Value) override;`
- L92 _public prototype_ `virtual void Serialize(FLazyObjectPtr& Value) override;`
- L93 _public prototype_ `virtual void Serialize(FObjectPtr& Value) override;`
- L94 _public prototype_ `virtual void Serialize(TArray<uint8>& Value) override;`
- L95 _public prototype_ `virtual void Serialize(void* Data, uint64 DataSize) override;`
- L97 _public function_ `void SetObjectIndicesMap(const TMap<UObject*, FPackageIndex>* InObjectIndicesMap)`
- L103 _private member_ `FArchive& Inner;`
- L105 _private member_ `const TMap<UObject*, FPackageIndex>* ObjectIndicesMap = nullptr;`
- L106 _private member_ `bool bSerializeObjectsInPlace = false;`
- L107 _private member_ `bool bSerializeSoftObjectsInPlace = false;`
- L109 _private member_ `TArray<ANSICHAR> Newline;`
- L110 _private member_ `bool bNeedsComma = false;`
- L111 _private member_ `bool bNeedsNewline = false;`
- L113 _private member_ `TArray<int32> NumAttributesStack;`
- L114 _private member_ `TArray<int64> TextStartPosStack;`
- L116 _private prototype_ `void Write(ANSICHAR Character);`
- L118 _private prototype_ `void Write(const ANSICHAR* Text);`
- L119 _private prototype_ `void Write(const FString& Text);`
- L121 _private prototype_ `void WriteFieldName(const TCHAR* Name);`
- L122 _private prototype_ `void WriteValue(const FString& Value);`
- L124 _private prototype_ `void WriteOptionalComma();`
- L125 _private prototype_ `void WriteOptionalNewline();`
- L126 _private prototype_ `void WriteOptionalAttributedBlockOpening();`
- L127 _private prototype_ `void WriteOptionalAttributedBlockValue();`
- L128 _private prototype_ `void WriteOptionalAttributedBlockClosing();`
- L130 _private prototype_ `void SerializeStringInternal(const FString& String);`
- L132 _private prototype_ `bool IsObjectAllowed(UObject* InObject) const;`
