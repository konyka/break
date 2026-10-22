# Runtime / Cbor

- module root: `Source/Runtime/Cbor`
- headers: 4; symbols: 129
- symbol kinds: class=4, enum=2, enumerator=35, function=36, member=17, prototype=33, struct=1, union=1
- PublicDependencyModuleNames: Core

### `Source/Runtime/Cbor/Public/CborGlobals.h` (Public)


#### Free symbols / members of external scopes

- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogCbor, Log, All);`

### `Source/Runtime/Cbor/Public/CborReader.h` (Public)


#### class `FCborReader`  
`class FCborReader`  
_L16-73_
- desc: Reader for a the cbor protocol encoded stream @see http://cbor.io
- L25 _public prototype_ `FCborReader(FArchive* InStream, ECborEndianness InReaderEndianness = ECborEndianness::Platform);` — Construct a CBOR reader. @param InStream The stream containing the CBOR data. @param InReaderEndianness Specify which endianness should be use to read the archive. @note CBOR standard endianness is big endian. For interoperability with external tools, the standard endianness should be used. For internal usage, the platform endianness is faster.
- L26 _public prototype_ `~FCborReader();`
- L29 _public prototype_ `const FArchive* GetArchive() const;` — @return the archive we are reading from.
- L32 _public prototype_ `bool IsError() const;` — @return true if the reader is in error.
- L35 _public prototype_ `FCborHeader GetError() const;` — @return A cbor Header containing an error code as its raw code.
- L42 _public prototype_ `const FCborContext& GetContext() const;` — The cbor context of the reader can either be a container context or a dummy. A reference to the context shouldn't be held while calling ReadNext. @return The current cbor context.
- L49 _public prototype_ `bool ReadNext(FCborContext& OutContext);` — Read the next value from the cbor stream. @param OutContext the context to read the value into. @return true if successful, false if an error was returned or the end of the stream was reached.
- L56 _public prototype_ `bool SkipContainer(ECborCode ContainerType);` — Skip a container of ContainerType type @param ContainerType the container we expect to skip. @return true if successful, false if the current container wasn't a ContainerType or an error occurred.
- L60 _private prototype_ `static uint64 ReadUIntValue(FCborContext& OutContext, FArchive& Ar);` — Read a uint value from Ar into OutContext and also return it.
- L62 _private prototype_ `static void ReadPrimValue(FCborContext& OutContext, FArchive& Ar);` — Read a Prim value from Ar into OutContext.
- L65 _private prototype_ `FCborHeader SetError(ECborCode ErrorCode);` — Set an error in the reader and return it.
- L68 _private member_ `FArchive* Stream;` — The archive we are reading from.
- L70 _private member_ `TArray<FCborContext> ContextStack;` — Holds the context stack for the reader.
- L72 _private member_ `ECborEndianness Endianness;` — Read the CBOR data using the specified endianness.

### `Source/Runtime/Cbor/Public/CborTypes.h` (Public)


#### enum `ECborCode`  
`enum class ECborCode : uint8`  
_L14-58_
- desc: Possible cbor code for cbor headers. @see http://cbor.io
- L16 _public enumerator_ `None = 0` — no code
- L18 _public enumerator_ `Uint = 0 << 5` — Major Types
- L19 _public enumerator_ `Int = 1 << 5` — negative number
- L20 _public enumerator_ `ByteString = 2 << 5` — byte string
- L21 _public enumerator_ `TextString = 3 << 5` — text string
- L22 _public enumerator_ `Array = 4 << 5` — array
- L23 _public enumerator_ `Map = 5 << 5` — map
- L24 _public enumerator_ `Tag = 6 << 5` — semantic tag
- L25 _public enumerator_ `Prim = 7 << 5` — bool, null, char, half-float, float, double, break code
- L28 _public enumerator_ `Value_1Byte = 0x18` — Additional Value Info
- L29 _public enumerator_ `Value_2Bytes = 0x19` — Additional value in next 2 bytes
- L30 _public enumerator_ `Value_4Bytes = 0x1A` — Additional value in next 4 bytes
- L31 _public enumerator_ `Value_8Bytes = 0x1B` — Additional value in next 8 bytes
- L32 _public enumerator_ `Unused_28 = 0x1C` — Unused value in protocol
- L33 _public enumerator_ `Unused_29 = 0x1D` — Unused value in protocol
- L34 _public enumerator_ `Unused_30 = 0x1E` — Unused value in protocol
- L35 _public enumerator_ `Indefinite = 0x1F` — Indicate indefinite containers
- L38 _public enumerator_ `False = 0x14` — Prim type codes
- L39 _public enumerator_ `True = 0x15` — boolean
- L40 _public enumerator_ `Null = 0x16` — null value
- L41 _public enumerator_ `Undefined = 0x17` — undefined, unused in the writer
- L44 _public enumerator_ `Break = 0xFF` — Special values
- L48 _public enumerator_ `Dummy = 0x1C` — Protocol unused values, used to report context or errors State
- L49 _public enumerator_ `StreamEnd = 0x3C` — stream end					(Int | 28)
- L51 _public enumerator_ `ErrorReservedItem = 0x1D` — Errors
- L52 _public enumerator_ `ErrorStreamFailure = 0x1E` — stream error					(Uint | 30)
- L53 _public enumerator_ `ErrorBreak = 0x3D` — break not allowed			(Int | 29)
- L54 _public enumerator_ `ErrorMapContainer = 0x3E` — odd item number in map		(Int | 30)
- L55 _public enumerator_ `ErrorContext = 0x5E` — reader/writer context error	(ByteString | 30)
- L56 _public enumerator_ `ErrorStringNesting = 0x7D` — infinite string wrong type	(TextString | 29)
- L57 _public enumerator_ `ErrorStringLength = 0x7E` — invalid string length		(TextString | 30)

#### class `FCborHeader`  
`class FCborHeader`  
_L67-122_
- desc: class that represent a cbor header
- L70 _public function_ `FCborHeader(uint8 InHeader = 0) : Header(InHeader)`
- L73 _public function_ `FCborHeader(ECborCode InHeader) : Header((uint8)InHeader)`
- L78 _public function_ `void Set(ECborCode Code)` — Set a cbor code for the header.
- L84 _public function_ `void Set(uint8 Code)` — Set a cbor code as a uint8.
- L90 _public function_ `uint8 Raw() const` — Get the cbor header as a uint8
- L96 _public function_ `ECborCode RawCode() const` — Get the cbor header raw code.
- L102 _public function_ `ECborCode MajorType() const` — Get the major type part of the cbor header.
- L108 _public function_ `ECborCode AdditionalValue() const` — Get the additional value part of the cbor header.
- L121 _private member_ `uint8 Header;` — Hold the header value.

#### struct `FCborContext`  
`struct FCborContext`  
_L128-313_
- desc: class that represent a cbor context which consists of a header and value pair
- L130 _public function_ `FCborContext() : Header(ECborCode::Dummy) , IntValue(0)`
- L136 _public function_ `void Reset()` — Reset the context to a dummy state.
- L142 _public function_ `ECborCode RawCode() const` — @return the context header raw code.
- L148 _public function_ `ECborCode MajorType() const` — @return the context header major type.
- L154 _public function_ `ECborCode AdditionalValue() const` — @return the context header additional value.
- L160 _public function_ `bool IsDummy()` — @return true if this is a dummy context.
- L166 _public function_ `bool IsError() const` — @return true if this context represents an error code.
- L173 _public function_ `bool IsBreak() const` — @return true if this context represent a break code.
- L179 _public function_ `bool IsString() const` — @return true if this context represents a string type.
- L185 _public function_ `bool IsContainer() const` — @return true if this context represents a container. (indefinite string are containers.)
- L191 _public function_ `bool IsIndefiniteContainer() const` — @return true if this context represents an indefinite container.
- L198 _public function_ `bool IsFiniteContainer() const` — @return true if this context represents an finite container.
- L205 _public function_ `ECborCode AsBreak() const` — @return the context as the container code the break context is associated with.
- L212 _public function_ `uint64 AsLength() const` — @return the context as a container length. Map container returns their length as twice their number of pairs.
- L219 _public function_ `uint64 AsUInt() const` — @return the context as an unsigned int.
- L226 _public function_ `int64 AsInt() const` — @return the context as an int.
- L233 _public function_ `bool AsBool() const` — @return the context as a bool.
- L240 _public function_ `float AsFloat() const` — @return the context as a float.
- L247 _public function_ `double AsDouble() const` — @return the context as a double.
- L254 _public function_ `FString AsString() const` — @return the context as a string.
- L261 _public function_ `FAnsiString AsAnsiString() const` — @return the context as a string.
- L269 _public function_ `FUtf8String AsUtf8String() const` — @return the context as a string.
- L276 _public function_ `const char* AsCString() const` — @return the context as a C string.
- L283 _public function_ `TArrayView<const uint8> AsByteArray() const` — @return the context as a raw byte array.
- L293 _private function_ `FCborContext(ECborCode Code) : Header(Code) , IntValue(0)`
- L299 _private member_ `FCborHeader Header;` — Holds the context header.
- L312 _private member_ `TArray<char> RawTextValue;` — Hold text value separately since, non trivial type are a mess in union, also used to report container type for break code

#### union `FCborContext::(anonymous)`  
``  
_L303-310_

#### enum `ECborEndianness`  
`enum class ECborEndianness`  
_L316-329_
- desc: Defines in which endianness the CBOR data must be written. The official endiannes is 'big endian' but Unreal use both.
- L319 _public enumerator_ `Platform` — Read or write the CBOR using the current platform endianness.
- L322 _public enumerator_ `BigEndian` — Read or write the CBOR data in big endian (CBOR standard compliant)
- L325 _public enumerator_ `LittleEndian` — Read or write the CBOR data in little endian (Fine for internal usage, but not usable with CBOR standard tools)
- L328 _public enumerator_ `StandardCompliant = BigEndian` — The endianness complying to the CBOR specifications.

#### class `ScopedCborArchiveEndianness`  
`class ScopedCborArchiveEndianness`  
_L335-353_
- desc: Ensure an archive is swapping the bytes according to which endianness was requested to read or write the CBOR. @node The official CBOR endianness is 'big endian', but Unreal uses boths for backward compability reasons.
- L339 _public function_ `ScopedCborArchiveEndianness(FArchive& InArchive, ECborEndianness Endianness) : Archive(InArchive), bOldByteSwappingState(InArchive.IsByteSwapping())` — Set the archive to read or write the data according to the selected endianness.
- L345 _public function_ `~ScopedCborArchiveEndianness()`
- L351 _private member_ `FArchive& Archive;`
- L352 _private member_ `bool bOldByteSwappingState;`

#### Free symbols / members of external scopes

- L59 _prototype_ `ENUM_CLASS_FLAGS(ECborCode);`
- L114 _function_ `friend FArchive& operator<<(FArchive& Ar, FCborHeader& InHeader)` — Serialization helper
- L304 _member_ `int64 IntValue;` (scope `FCborContext::__anon4a1df87d010a`)
- L305 _member_ `uint64 UIntValue;` (scope `FCborContext::__anon4a1df87d010a`)
- L306 _member_ `bool BoolValue;` (scope `FCborContext::__anon4a1df87d010a`)
- L307 _member_ `float FloatValue;` (scope `FCborContext::__anon4a1df87d010a`)
- L308 _member_ `double DoubleValue;` (scope `FCborContext::__anon4a1df87d010a`)
- L309 _member_ `uint64 Length;` (scope `FCborContext::__anon4a1df87d010a`)

### `Source/Runtime/Cbor/Public/CborWriter.h` (Public)


#### class `FCborWriter`  
`class FCborWriter`  
_L19-74_
- desc: Writer for encoding a stream with the cbor protocol @see http://cbor.io
- L28 _public prototype_ `FCborWriter(FArchive* InStream, ECborEndianness InWriterEndianness = ECborEndianness::Platform);` — Construct a CBOR writer. @param InStream The stream used to write the CBOR data. @param InWriterEndianness Specify which endianness should be use to write the archive. @note CBOR standard endianness is big endian. For interoperability with external tools, the standard endianness should be used. For internal usage, the platform endianness is faster.
- L29 _public prototype_ `~FCborWriter();`
- L33 _public prototype_ `const FArchive* GetArchive() const;` — @return the archive we are writing to.
- L40 _public prototype_ `void WriteContainerStart(ECborCode ContainerType, int64 NbItem);` — Write a container start code. @param ContainerType container major type, either array or map. @param NbItem the number of item in the container or negative to indicate indefinite containers.
- L43 _public prototype_ `void WriteContainerEnd();` — Write a container break code, need a indefinite container context.
- L47 _public prototype_ `void WriteNull();`
- L48 _public prototype_ `void WriteValue(uint64 Value);`
- L49 _public prototype_ `void WriteValue(int64 Value);`
- L50 _public prototype_ `void WriteValue(bool Value);`
- L51 _public prototype_ `void WriteValue(float Value);`
- L52 _public prototype_ `void WriteValue(double Value);`
- L53 _public prototype_ `void WriteValue(const FString& Value);`
- L54 _public prototype_ `void WriteValue(const FAnsiString& Value);`
- L55 _public prototype_ `void WriteValue(const FUtf8String& Value);`
- L56 _public prototype_ `void WriteValue(const FStringView& Value);`
- L57 _public prototype_ `void WriteValue(const FUtf8StringView& Value);`
- L58 _public prototype_ `void WriteValue(const char* CString, uint64 Length);`
- L59 _public prototype_ `void WriteValue(const uint8* Bytes, uint64 Length);`
- L63 _private prototype_ `static FCborHeader WriteUIntValue(FCborHeader Header, FArchive& Ar, uint64 Value);` — Write a uint Value for Header in Ar and return the final generated cbor Header.
- L66 _private prototype_ `void CheckContext(ECborCode MajorType);` — Validate the current writer context for MajorType.
- L69 _private member_ `FArchive* Stream;` — The archive being written to.
- L71 _private member_ `TArray<FCborContext> ContextStack;` — The writer context stack.
- L73 _private member_ `ECborEndianness Endianness;` — Write the CBOR data using the specified endianness.
