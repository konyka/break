# Runtime / Serialization

- module root: `Source/Runtime/Serialization`
- headers: 10; symbols: 159
- symbol kinds: class=8, enum=8, enumerator=29, function=23, member=31, namespace=1, prototype=55, struct=4
- PrivateDependencyModuleNames: CoreUObject
- PublicDependencyModuleNames: Cbor, Core, Json

### `Source/Runtime/Serialization/Private/Backends/StructDeserializerBackendUtilities.h` (Private)


#### struct `StructDeserializerBackendUtilities`  
`struct StructDeserializerBackendUtilities`  
_L13-102_
- L25 _public function_ `static bool ClearPropertyValue(FProperty* Property, FProperty* Outer, void* Data, int32 ArrayIndex)` — Clears the value of the given property. @param Property The property to clear. @param Outer The property that contains the property to be cleared, if any. @param Data A pointer to the memory holding the property's data. @param ArrayIndex The index of the element to clear (if the property is an array). @return true on success, false otherwise. @see SetPropertyValue
- L56 _public function_ `static void* GetPropertyValuePtr(FProperty* Property, FProperty* Outer, void* Data, int32 ArrayIndex)` — Gets a pointer to object of the given property. @param Property The property to get. @param Outer The property that contains the property to be get, if any. @param Data A pointer to the memory holding the property's data. @param ArrayIndex The index of the element to set (if the property is an array). @return A pointer to the object represented by the property, null otherwise.. @see ClearPropertyValue
- L92 _public function_ `template<typename PropertyType, typename ValueType> static bool SetPropertyValue(PropertyType* Property, FProperty* Outer, void* Data, int32 ArrayIndex, const ValueType& Value)` — Sets the value of the given property. @param Property The property to set. @param Outer The property that contains the property to be set, if any. @param Data A pointer to the memory holding the property's data. @param ArrayIndex The index of the element to set (if the property is an array). @return true on success, false otherwise. @see ClearPropertyValue

### `Source/Runtime/Serialization/Private/StructSerializationUtilities.h` (Private)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace StructSerializationUtilities`
- L9 _function_ `static bool IsLWCType(const UStruct* Type)` (scope `StructSerializationUtilities`)

### `Source/Runtime/Serialization/Public/Backends/CborStructDeserializerBackend.h` (Public)


#### class `FCborStructDeserializerBackend`  
`class FCborStructDeserializerBackend : public IStructDeserializerBackend`  
_L19-63_
- inherits: `IStructDeserializerBackend`
- desc: Implements a reader for UStruct deserialization using Cbor.
- L30 _public prototype_ `FCborStructDeserializerBackend(FArchive& Archive, ECborEndianness CborDataEndianness = ECborEndianness::Platform, bool bInIsLWCCompatibilityMode = false);` — Creates and initializes a new instance. @param Archive The archive to deserialize from. @param CborDataEndianness The CBOR data endianness stored in the archive. @note For backward compatibility and performance, the implementation default to the the platform endianness rather than the CBOR standard one (big endian).
- L31 _public prototype_ `virtual ~FCborStructDeserializerBackend();`
- L36 _public prototype_ `virtual const FString& GetCurrentPropertyName() const override;` — IStructDeserializerBackend interface
- L37 _public prototype_ `virtual FString GetDebugString() const override;`
- L38 _public prototype_ `virtual const FString& GetLastErrorMessage() const override;`
- L39 _public prototype_ `virtual bool GetNextToken(EStructDeserializerBackendTokens& OutToken) override;`
- L40 _public prototype_ `virtual bool ReadProperty(FProperty* Property, FProperty* Outer, void* Data, int32 ArrayIndex) override;`
- L41 _public prototype_ `virtual bool ReadPODArray(FArrayProperty* ArrayProperty, void* Data) override;`
- L42 _public prototype_ `virtual void SkipArray() override;`
- L43 _public prototype_ `virtual void SkipStructure() override;`
- L47 _private member_ `FCborReader CborReader;` — Holds the Cbor reader used for the actual reading of the archive.
- L50 _private member_ `FCborContext LastContext;` — Holds the last read Cbor Context.
- L53 _private member_ `FString LastMapKey;` — Holds the last map key.
- L56 _private member_ `int32 DeserializingByteArrayIndex = 0;` — The index of the next byte to copy from the CBOR byte stream into the corresponding TArray<uint8>/TArray<int8> property.
- L59 _private member_ `bool bDeserializingByteArray = false;` — Whether a TArray<uint8>/TArray<int8> property is being deserialized.
- L62 _private member_ `bool bIsLWCCompatibilityMode = false;` — Whether we are deserializing for LWC backward compability mode. Incoming FloatProperties of LWC types deserialized into Double

### `Source/Runtime/Serialization/Public/Backends/CborStructSerializerBackend.h` (Public)


#### class `FCborStructSerializerBackend`  
`class FCborStructSerializerBackend : public IStructSerializerBackend`  
_L17-55_
- inherits: `IStructSerializerBackend`
- desc: Implements a writer for UStruct serialization using Cbor.
- L28 _public prototype_ `FCborStructSerializerBackend(FArchive& InArchive, const EStructSerializerBackendFlags InFlags);` — Creates and initializes a new instance with the given flags. @param InArchive The archive to serialize into. @param InFlags The flags that control the serialization behavior (typically EStructSerializerBackendFlags::Default).
- L30 _public prototype_ `virtual ~FCborStructSerializerBackend();`
- L35 _public prototype_ `virtual void BeginArray(const FStructSerializerState& State) override;` — IStructSerializerBackend interface
- L36 _public prototype_ `virtual void BeginStructure(const FStructSerializerState& State) override;`
- L37 _public prototype_ `virtual void EndArray(const FStructSerializerState& State) override;`
- L38 _public prototype_ `virtual void EndStructure(const FStructSerializerState& State) override;`
- L39 _public prototype_ `virtual void WriteComment(const FString& Comment) override;`
- L40 _public prototype_ `virtual void WriteProperty(const FStructSerializerState& State, int32 ArrayIndex = 0) override;`
- L41 _public prototype_ `virtual bool WritePODArray(const FStructSerializerState& State) override;`
- L45 _private member_ `FCborWriter CborWriter;` — Holds the Cbor writer used for the actual serialization.
- L48 _private member_ `EStructSerializerBackendFlags Flags;` — Flags controlling the serialization behavior.
- L51 _private member_ `TArray<uint8> AccumulatedBytes;` — Stores the accumulated bytes extracted from UByteProperty/UIntProperty when writing a TArray<uint8>/TArray<int8>.
- L54 _private member_ `bool bSerializingByteArray = false;` — Whether the serializer is encoding array of uint8/int8

### `Source/Runtime/Serialization/Public/Backends/JsonStructDeserializerBackend.h` (Public)


#### class `FJsonStructDeserializerBackend`  
`class FJsonStructDeserializerBackend : public IStructDeserializerBackend`  
_L24-76_
- inherits: `IStructDeserializerBackend`
- desc: Implements a reader for UStruct deserialization using Json. Note: The underlying Json de-serializer is currently hard-coded to use UCS2CHAR. This is because the current JsonReader API does not allow writers to be substituted since it's all based on templates. At some point we will refactor the low-level Json API to provide more flexibility for serialization.
- L34 _public function_ `FJsonStructDeserializerBackend( FArchive& Archive ) : JsonReader(TJsonReader<WIDECHAR>::Create(&Archive))` — Creates and initializes a new instance. @param Archive The archive to deserialize from.
- L42 _public prototype_ `virtual const FString& GetCurrentPropertyName() const override;`
- L43 _public prototype_ `virtual FString GetDebugString() const override;`
- L44 _public prototype_ `virtual const FString& GetLastErrorMessage() const override;`
- L45 _public prototype_ `virtual bool GetNextToken( EStructDeserializerBackendTokens& OutToken ) override;`
- L46 _public prototype_ `virtual bool ReadProperty( FProperty* Property, FProperty* Outer, void* Data, int32 ArrayIndex ) override;`
- L47 _public prototype_ `virtual void SkipArray() override;`
- L48 _public prototype_ `virtual void SkipStructure() override;`
- L51 _protected function_ `FString& GetLastIdentifier()`
- L56 _protected function_ `EJsonNotation GetLastNotation()`
- L61 _protected function_ `TSharedRef<TJsonReader<WIDECHAR>>& GetReader()`
- L69 _private member_ `FString LastIdentifier;` — Holds the name of the last read Json identifier.
- L72 _private member_ `EJsonNotation LastNotation;` — Holds the last read Json notation.
- L75 _private member_ `TSharedRef<TJsonReader<WIDECHAR>> JsonReader;` — Holds the Json reader used for the actual reading of the archive.

### `Source/Runtime/Serialization/Public/Backends/JsonStructSerializerBackend.h` (Public)


#### class `FJsonStructSerializerBackend`  
`class FJsonStructSerializerBackend : public IStructSerializerBackend`  
_L25-118_
- inherits: `IStructSerializerBackend`
- desc: Implements a writer for UStruct serialization using Json. Note: The underlying Json serializer is currently hard-coded to use UCS2CHAR and pretty-print. This is because the current JsonWriter API does not allow writers to be substituted since it's all based on templates. At some point we will refactor the low-level Json API to provide more flexibility for serialization.
- L36 _public function_ `FJsonStructSerializerBackend( FArchive& InArchive, const EStructSerializerBackendFlags InFlags ) : JsonWriter(TJsonWriter<UCS2CHAR>::Create(&InArchive)) , Flags(InFlags)` — Creates and initializes a new instance with the given flags. @param InArchive The archive to serialize into. @param InFlags The flags that control the serialization behavior (typically EStructSerializerBackendFlags::Default).
- L45 _public prototype_ `virtual void BeginArray(const FStructSerializerState& State) override;`
- L46 _public prototype_ `virtual void BeginStructure(const FStructSerializerState& State) override;`
- L47 _public prototype_ `virtual void EndArray(const FStructSerializerState& State) override;`
- L48 _public prototype_ `virtual void EndStructure(const FStructSerializerState& State) override;`
- L49 _public prototype_ `virtual void WriteComment(const FString& Comment) override;`
- L50 _public prototype_ `virtual void WriteProperty(const FStructSerializerState& State, int32 ArrayIndex = 0) override;`
- L51 _public prototype_ `virtual bool WritePODArray(const FStructSerializerState& State) override;`
- L56 _protected function_ `TSharedRef<TJsonWriter<UCS2CHAR>>& GetWriter()` — Allow access to the internal JsonWriter to subclasses
- L63 _protected function_ `template<typename ValueType> void WritePropertyValue(const FStructSerializerState& State, const ValueType& Value)` — Writes a property value to the serialization output.
- L89 _protected function_ `void WriteNull(const FStructSerializerState& State)` — Writes a null value to the serialization output.
- L114 _private member_ `TSharedRef<TJsonWriter<UCS2CHAR>> JsonWriter;` — Holds the Json writer used for the actual serialization.
- L117 _private member_ `EStructSerializerBackendFlags Flags;` — Flags controlling the serialization behavior.

### `Source/Runtime/Serialization/Public/IStructDeserializerBackend.h` (Public)


#### enum `EStructDeserializerBackendTokens`  
`enum class EStructDeserializerBackendTokens`  
_L12-37_
- desc: Enumerates serialization tokens.
- L15 _public enumerator_ `ArrayEnd` — End of an array.
- L18 _public enumerator_ `ArrayStart` — Beginning of an array.
- L21 _public enumerator_ `Comment` — A comment.
- L24 _public enumerator_ `Error` — An error occurred when reading the token.
- L27 _public enumerator_ `None` — No token available.
- L30 _public enumerator_ `Property` — A scalar property.
- L33 _public enumerator_ `StructureEnd` — End of a data structure.
- L36 _public enumerator_ `StructureStart` — Beginning of a data structure.

#### class `IStructDeserializerBackend`  
`class IStructDeserializerBackend`  
_L43-111_
- desc: Interface for UStruct serializer backends.
- L52 _public prototype_ `virtual const FString& GetCurrentPropertyName() const = 0;` — Gets the identifier of the current field. @return The field's name.
- L63 _public prototype_ `virtual FString GetDebugString() const = 0;` — Gets a debug string for the reader's current state. The returned string contains debug information that is relevant to the reader's serialization format. For example, it could be a line and column number for text based formats, or a byte offset for binary serialization formats. @return The debug string.
- L70 _public prototype_ `virtual const FString& GetLastErrorMessage() const = 0;` — Gets the last error message. @return Error message.
- L78 _public prototype_ `virtual bool GetNextToken( EStructDeserializerBackendTokens& OutToken ) = 0;` — Reads the next token from the stream. @param OutToken Will contain the read token, if any. @return true if a token was read, false otherwise.
- L89 _public prototype_ `virtual bool ReadProperty( FProperty* Property, FProperty* Outer, void* Data, int32 ArrayIndex ) = 0;` — Reads the specified property from the stream. @param Property The property to read into. @param Outer The outer property holding the property to read (in case of arrays). @param Data The buffer that will hold the read data. @param ArrayIndex An index into the property array (for static arrays). @return true on success, false otherwise.
- L99 _public function_ `virtual bool ReadPODArray(FArrayProperty* ArrayProperty, void* Data)` — Reads the specified POD Array property from the stream. @note implementations will support only a Int8 or Byte array at the moment @param ArrayProperty The array property to read into. @param Data The location of array to read the data into. @return true on success, false if need to fall back to per element array serialization.
- L102 _public prototype_ `virtual void SkipArray() = 0;` — Skips the array that is currently being read from the stream.
- L105 _public prototype_ `virtual void SkipStructure() = 0;` — Skips the object that is currently being read from the stream.
- L110 _public prototype_ `virtual ~IStructDeserializerBackend() = default;` — Virtual destructor.

### `Source/Runtime/Serialization/Public/IStructSerializerBackend.h` (Public)


#### enum `EStructSerializerBackendFlags`  
`enum class EStructSerializerBackendFlags`  
_L13-51_
- desc: Flags controlling the behavior of struct serializer backends.
- L18 _public enumerator_ `None = 0` — No special behavior.
- L24 _public enumerator_ `WriteTextAsComplexString = 1<<0` — Write text in its complex exported format (eg, NSLOCTEXT(...)) rather than as a simple string. @note This is required to correctly support localization
- L29 _public enumerator_ `WriteByteArrayAsByteStream = 1<<1` — Write TArray<uint8>/TArray<int> as byte string if possible (CBOR), starting at 4.25.
- L35 _public enumerator_ `WriteCborStandardEndianness = 1 << 2` — Force the CBOR backend to write CBOR data in big endian (CBOR compliant endianness), available from 4.25. Caller must be opt-in. By default, the CBOR backend uses the endianness of the platform.
- L40 _public enumerator_ `WriteLWCTypesAsFloats = 1 << 3` — Support backward compatibility for LWC types by writing double properties as floats.
- L45 _public enumerator_ `LegacyUE4 = WriteTextAsComplexString | WriteByteArrayAsByteStream | WriteLWCTypesAsFloats` — Legacy settings for backwards compatibility with code compiled for 4.25 up to UE5.
- L50 _public enumerator_ `Default = WriteTextAsComplexString | WriteByteArrayAsByteStream` — Default settings for code compiled for 5.0 onwards.

#### enum `EStructSerializerStateFlags`  
`enum class EStructSerializerStateFlags`  
_L58-69_
- desc: Flags related to the current state being serialized.
- L63 _public enumerator_ `None = 0` — Nothing special.
- L68 _public enumerator_ `WritingContainerElement = 1 << 0` — Whether its serializing a single element from a container (array, set, map)

#### struct `FStructSerializerState`  
`struct FStructSerializerState`  
_L75-113_
- desc: Structure for the write state stack.
- L77 _public prototype_ `FStructSerializerState() = default;`
- L79 _public function_ `FStructSerializerState(void* InValuePtr, FProperty* InProperty, EStructSerializerStateFlags InFlags) : ValueData(InValuePtr) , ValueProperty(InProperty) , FieldType(InProperty->GetClass()) , StateFlags(InFlags)`
- L88 _public member_ `bool HasBeenProcessed = false;` — Holds a flag indicating whether the property has been processed.
- L91 _public member_ `const void* KeyData = nullptr;` — Holds a pointer to the key property's data.
- L94 _public member_ `FProperty* KeyProperty = nullptr;` — Holds the key property's meta data (only used for TMap).
- L97 _public member_ `const void* ValueData = nullptr;` — Holds a pointer to the property value's data.
- L100 _public member_ `FProperty* ValueProperty = nullptr;` — Holds the property value's meta data.
- L103 _public member_ `UStruct* ValueType = nullptr;` — Holds a pointer to the UStruct describing the data.
- L106 _public member_ `FFieldClass* FieldType = nullptr;` — Holds a pointer to the field type describing the data.
- L109 _public member_ `int32 ElementIndex = INDEX_NONE;` — Holds the element index that is targeted if an array/set/map
- L112 _public member_ `EStructSerializerStateFlags StateFlags = EStructSerializerStateFlags::None;` — Flags related for the current state

#### class `IStructSerializerBackend`  
`class IStructSerializerBackend`  
_L119-206_
- desc: Interface for UStruct serializer backends.
- L131 _public prototype_ `virtual void BeginArray(const FStructSerializerState& State) = 0;` — Signals the beginning of an array. State.ValueProperty points to the property that holds the array. @param State The serializer's current state. @see BeginStructure, EndArray
- L141 _public prototype_ `virtual void BeginStructure(const FStructSerializerState& State) = 0;` — Signals the beginning of a child structure. State.ValueProperty points to the property that holds the struct. @param State The serializer's current state. @see BeginArray, EndStructure
- L151 _public prototype_ `virtual void EndArray(const FStructSerializerState& State) = 0;` — Signals the end of an array. State.ValueProperty points to the property that holds the array. @param State The serializer's current state. @see BeginArray, EndStructure
- L161 _public prototype_ `virtual void EndStructure(const FStructSerializerState& State) = 0;` — Signals the end of an object. State.ValueProperty points to the property that holds the struct. @param State The serializer's current state. @see BeginStructure, EndArray
- L169 _public prototype_ `virtual void WriteComment(const FString& Comment) = 0;` — Writes a comment to the output stream. @param Comment The comment text. @see BeginArray, BeginStructure, EndArray, EndStructure, WriteProperty
- L186 _public prototype_ `virtual void WriteProperty(const FStructSerializerState& State, int32 ArrayIndex = 0) = 0;` — Writes a property to the output stream. Depending on the context, properties to be written can be either object properties or array elements. State.KeyProperty points to the key property that holds the data to write. State.KeyData points to the key property's data. State.ValueProperty points to the property that holds the value to write. State.ValueData points to the actual data to write. State.TypeInfo contains the data's type information State.ArrayIndex is the optional index if the data is a value in an array. @param State The serializer's current state. @see BeginArray, BeginStructure, EndArray, EndStructure, WriteComment
- L200 _public function_ `virtual bool WritePODArray(const FStructSerializerState& State)` — Writes a POD Array property to the output stream. @note implementations will support only a Int8 or Byte array at the moment State.ValueProperty points to the property that holds the value to write. needs to be an ArrayProperty with a properly supported InnerProperty. State.ValueData points to the actual data to write. The array itself in this case State.TypeInfo contains the data's type information @param State The serializer's current state. @return true if the array was properly written entirely as a pod array, false is we need to fallback to per element serialization @see BeginArray, BeginStructure, EndArray, EndStructure, WriteComment
- L205 _public prototype_ `virtual ~IStructSerializerBackend() = default;` — Virtual destructor.

#### Free symbols / members of external scopes

- L52 _prototype_ `ENUM_CLASS_FLAGS(EStructSerializerBackendFlags);`
- L70 _prototype_ `ENUM_CLASS_FLAGS(EStructSerializerStateFlags);`

### `Source/Runtime/Serialization/Public/StructDeserializer.h` (Public)


#### enum `EStructDeserializerErrorPolicies`  
`enum class EStructDeserializerErrorPolicies`  
_L17-27_
- desc: Enumerates policies for various errors during de-serialization.
- L20 _public enumerator_ `Error` — Fail the de-serialization.
- L23 _public enumerator_ `Ignore` — Ignore the error (default).
- L26 _public enumerator_ `Warning` — Print a warning to the log.

#### enum `EStructDeserializerMapPolicies`  
`enum class EStructDeserializerMapPolicies`  
_L32-39_
- desc: Enumerates policies for map de-serialization.
- L35 _public enumerator_ `KeyValuePair` — Deserialize maps as key-value pair - default.
- L38 _public enumerator_ `Array` — Treat map properties as array using index.

#### struct `FStructDeserializerPolicies`  
`struct FStructDeserializerPolicies`  
_L45-64_
- desc: Structure for UStruct serialization policies.
- L48 _public member_ `EStructDeserializerErrorPolicies MissingFields;` — Holds the policy for handling missing fields.
- L51 _public member_ `EStructDeserializerMapPolicies MapPolicies;` — Policy about map property deserialization
- L56 _public member_ `TFunction<bool (const FProperty* , const FProperty* )> PropertyFilter;` — Predicate for performing advanced filtering of struct properties. If set, the predicate should return true for all properties it wishes to include in the output.
- L59 _public function_ `FStructDeserializerPolicies() : MissingFields(EStructDeserializerErrorPolicies::Ignore) , MapPolicies(EStructDeserializerMapPolicies::KeyValuePair) , PropertyFilter()` — Default constructor.

#### class `FStructDeserializer`  
`class FStructDeserializer`  
_L75-143_
- desc: Implements a static class that can deserialize UStruct based types. This class implements the basic functionality for the serialization of UStructs, such as iterating a structure's properties and writing property values. The actual reading of serialized input data is performed by de-serialization backends, which allows this class to remain serialization format agnostic.
- L88 _public prototype_ `static bool Deserialize( void* OutStruct, UStruct& TypeInfo, IStructDeserializerBackend& Backend, const FStructDeserializerPolicies& Policies );` — Deserializes a data structure from an archive using the specified policy. @param OutStruct A pointer to the data structure to deserialize into. @param TypeInfo The data structure's type information. @param Backend The de-serialization backend to use. @param Policies The de-serialization policies to use. @return true if deserialization was successful, false otherwise.
- L100 _public prototype_ `static bool DeserializeElement(void* OutStruct, UStruct& TypeInfo, int32 ElementIndex, IStructDeserializerBackend& Backend, const FStructDeserializerPolicies& Policies);` — Deserializes a data structure element from an archive using the specified policy. @param OutStruct A pointer to the data structure to deserialize into. @param TypeInfo The data structure's type information. @param ElementIndex The element index to deserialize in case of a container property. @param Backend The de-serialization backend to use. @param Policies The de-serialization policies to use. @return true if deserialization was successful, false otherwise.
- L110 _public function_ `static bool Deserialize( void* OutStruct, UStruct& TypeInfo, IStructDeserializerBackend& Backend )` — Deserializes a data structure from an archive using the default policy. @param OutStruct A pointer to the data structure to deserialize into. @param TypeInfo The data structure's type information. @param Backend The de-serialization backend to use. @return true if deserialization was successful, false otherwise.
- L125 _public function_ `template<typename StructType> static bool Deserialize( StructType& OutStruct, IStructDeserializerBackend& Backend )` — Deserializes a data structure from an archive using the default policy. @param OutStruct The struct to deserialize into. @param Backend The de-serialization backend to use. @return true if deserialization was successful, false otherwise.
- L139 _public function_ `template<typename StructType> static bool Deserialize( StructType& OutStruct, IStructDeserializerBackend& Backend, const FStructDeserializerPolicies& Policies )` — Deserializes a data structure from an archive using the specified policy. @param OutStruct The struct to deserialize into. @param Backend The de-serialization backend to use. @param Policies The de-serialization policies to use. @return true if deserialization was successful, false otherwise.

### `Source/Runtime/Serialization/Public/StructSerializer.h` (Public)


#### enum `EStructSerializerNullValuePolicies`  
`enum class EStructSerializerNullValuePolicies`  
_L17-24_
- desc: Enumerates policies for serializing null values.
- L20 _public enumerator_ `Ignore` — Do not serialize NULL values.
- L23 _public enumerator_ `Serialize` — Serialize NULL values.

#### enum `EStructSerializerReferenceLoopPolicies`  
`enum class EStructSerializerReferenceLoopPolicies`  
_L30-40_
- desc: Enumerates policies for serializing object reference loops.
- L33 _public enumerator_ `Error` — Circular references generate an error.
- L36 _public enumerator_ `Ignore` — Ignore circular references.
- L39 _public enumerator_ `Serialize` — Serialize circular references.

#### enum `EStructSerializerMapPolicies`  
`enum class EStructSerializerMapPolicies`  
_L45-52_
- desc: Enumerates policies for serializing map property type.
- L48 _public enumerator_ `KeyValuePair` — Write map normally, as key value pair.
- L51 _public enumerator_ `Array` — Ignore keys and write values as array.

#### struct `FStructSerializerPolicies`  
`struct FStructSerializerPolicies`  
_L58-81_
- desc: Structure for UStruct serialization policies.
- L61 _public member_ `EStructSerializerNullValuePolicies NullValues;` — Holds the policy for null values.
- L64 _public member_ `EStructSerializerReferenceLoopPolicies ReferenceLoops;` — Holds the policy for reference loops.
- L67 _public member_ `EStructSerializerMapPolicies MapSerialization;` — Policies dicting how maps are being written out
- L72 _public member_ `TFunction<bool (const FProperty* , const FProperty* )> PropertyFilter;` — Predicate for performing advanced filtering of struct properties. If set, the predicate should return true for all properties it wishes to include in the output.
- L75 _public function_ `FStructSerializerPolicies() : NullValues(EStructSerializerNullValuePolicies::Serialize) , ReferenceLoops(EStructSerializerReferenceLoopPolicies::Ignore) , MapSerialization(EStructSerializerMapPolicies::KeyValuePair) , PropertyFilter()` — Default constructor.

#### class `FStructSerializer`  
`class FStructSerializer`  
_L95-166_
- desc: Implements a static class that can serialize UStruct based types. This class implements the basic functionality for the serialization of UStructs, such as iterating a structure's properties and writing property values. The actual writing of serialized output data is performed by serialization backends, which allows this class to remain serialization format agnostic. The serializer's behavior can be customized with serialization policies. This allows for control over how to handle null values, circular references and other edge cases.
- L108 _public prototype_ `static void Serialize( const void* Struct, UStruct& TypeInfo, IStructSerializerBackend& Backend, const FStructSerializerPolicies& Policies );` — Serializes a given data structure of the specified type using the specified policy. @param Struct The data structure to serialize. @param TypeInfo The structure's type information. @param Backend The serialization backend to use. @param Policies The serialization policies to use. @see Deserialize
- L120 _public prototype_ `static void SerializeElement(const void* Address, FProperty* Property, int32 ElementIndex, IStructSerializerBackend& Backend, const FStructSerializerPolicies& Policies);` — Serializes a given element of a data structure of the specified type using the specified policy. @param Address The address of the container of the property to serialize. @param Property The property to serialize. @param ElementIndex The index of the element to serialize if property is a container. @param Backend The serialization backend to use. @param Policies The serialization policies to use. @see Deserialize
- L131 _public function_ `static void Serialize( const void* Struct, UStruct& TypeInfo, IStructSerializerBackend& Backend )` — Serializes a given data structure of the specified type using the default policy. @param Struct The data structure to serialize. @param TypeInfo The structure's type information. @param Backend The serialization backend to use. @see Deserialize
- L147 _public function_ `template<typename StructType> static void Serialize( const StructType& Struct, IStructSerializerBackend& Backend )` — Serializes a given USTRUCT to a string using the default policy. @param StructType The type of the struct to serialize. @param Struct The struct to serialize. @param Backend The serialization backend to use. @return A string holding the serialized object.
- L162 _public function_ `template<typename StructType> static void Serialize( const StructType& Struct, IStructSerializerBackend& Backend, const FStructSerializerPolicies& Policies )` — Serializes a given USTRUCT to a string using the specified policy. @param StructType The type of the struct to serialize. @param Struct The struct to serialize. @param Backend The serialization backend to use. @param Policies The serialization policies to use. @return A string holding the serialized object.
