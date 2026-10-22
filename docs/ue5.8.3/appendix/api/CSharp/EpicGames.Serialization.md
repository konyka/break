# CSharp / EpicGames.Serialization

- project root: `Source/Programs/Shared/EpicGames.Serialization`
- files: 16; symbols: 763
- symbol kinds: class=76, const=22, ctor=30, enum=4, enumerator=33, field=68, indexer=2, interface=2, method=415, operator=17, property=88, record struct=1, struct=5
- access marked `*` is implicit (not written in source)

### `Source/Programs/Shared/EpicGames.Serialization/CbConverter.cs` (EpicGames.Serialization)


#### class `EpicGames.Serialization.CbConverterAttribute`  
`public sealed class CbConverterAttribute(Type converterType) : Attribute`  
_public; L18-24_
- attrs: `[AttributeUsage(AttributeTargets.Class | AttributeTargets.Struct | AttributeTargets.Property)]`
- desc: Attribute declaring the converter to use for a type
- L23 _public property_ `public Type ConverterType { get; }` — The converter type

#### class `EpicGames.Serialization.CbConverter`  
`public abstract partial class CbConverter`  
_public; L29-52_
- desc: Base class for all converters.
- L36 _public method_ `public abstract object? ReadObject(CbField field)` — Reads an object from a field
- L43 _public method_ `public abstract void WriteObject(CbWriter writer, object? value)` — Writes an object to a field
- L51 _public method_ `public abstract void WriteNamedObject(CbWriter writer, CbFieldName name, object? value)` — Writes an object to a named field, if not equal to the default value

#### class `EpicGames.Serialization.CbConverter`  
`public abstract class CbConverter<T> : CbConverter`  
_public; L57-89_
- inherits: `CbConverter`
- desc: Converter for a particular type
- L60 _public method_ `public sealed override object? ReadObject(CbField field)` — (inheritdoc)
- L63 _public method_ `public sealed override void WriteObject(CbWriter writer, object? value)` — (inheritdoc)
- L66 _public method_ `public sealed override void WriteNamedObject(CbWriter writer, CbFieldName name, object? value)` — (inheritdoc)
- L73 _public method_ `public abstract T Read(CbField field)` — Reads an object from a field
- L80 _public method_ `public abstract void Write(CbWriter writer, T value)` — Writes an object to a field
- L88 _public method_ `public abstract void WriteNamed(CbWriter writer, CbFieldName name, T value)` — Writes an object to a named field, if not equal to the default value

#### interface `EpicGames.Serialization.ICbConverterMethods`  
`public interface ICbConverterMethods`  
_public; L94-110_
- desc: Interface for obtaining static methods that can be invoked directly
- L99 _public property_ `public MethodInfo ReadMethod { get; }` — Method with the signature CbField -> T
- L104 _public property_ `public MethodInfo WriteMethod { get; }` — Method with the signature CbWriter, T -> void
- L109 _public property_ `public MethodInfo WriteNamedMethod { get; }` — Method with the signature CbWriter, CbFieldName, T -> void

#### class `EpicGames.Serialization.CbConverterMethods`  
`public static class CbConverterMethods`  
_public; L115-182_
- desc: Helper class for wrapping regular converters in a ICbConverterMethods interface
- L140 _private* field_ `static readonly Dictionary<PropertyInfo, ICbConverterMethods> s_propertyToMethods = ...`
- L140 _private* field_ `static readonly Dictionary< s_propertyToMethods = []`
- L141 _private* field_ `static readonly Dictionary<Type, ICbConverterMethods> s_typeToMethods = ...`
- L141 _private* field_ `static readonly Dictionary< s_typeToMethods = []`
- L143-147 _private* method_ `static ICbConverterMethods CreateWrapper(Type type, CbConverter converter)`
- L154-164 _public method_ `public static ICbConverterMethods Get(PropertyInfo property)` — Gets a ICbConverterMethods interface for the given property
- L171-181 _public method_ `public static ICbConverterMethods Get(Type type)` — Gets a ICbConverterMethods interface for the given type

#### class `EpicGames.Serialization.CbConverterMethods.CbConverterMethodsWrapper`  
`class CbConverterMethodsWrapper<TConverter, T> : ICbConverterMethods where TConverter : CbConverter<T>`  
_private*; L117-138_
- inherits: `ICbConverterMethods`
- constraints: `where TConverter : CbConverter<T>`
- L119 _private* field_ `static TConverter s_staticConverter = null!`
- L121 _private* method_ `static T Read(CbField field)`
- L122 _private* method_ `static void Write(CbWriter writer, T value)`
- L123 _private* method_ `static void WriteNamed(CbWriter writer, CbFieldName name, T value)`
- L125 _public property_ `public MethodInfo ReadMethod { get; }`
- L126 _public property_ `public MethodInfo WriteMethod { get; }`
- L127 _public property_ `public MethodInfo WriteNamedMethod { get; }`
- L129-132 _public ctor_ `public CbConverterMethodsWrapper(TConverter converter)`
- L134-137 _private* method_ `static MethodInfo GetMethodInfo(Expression<Action> expr)`

#### class `EpicGames.Serialization.CbConverterFactory`  
`public abstract class CbConverterFactory`  
_public; L187-195_
- desc: Base class for converter factories
- L194 _public method_ `public abstract CbConverter? CreateConverter(Type type)` — Create a converter for the given type

#### class `EpicGames.Serialization.CbConverter`  
`public partial class CbConverter`  
_public; L200-381_
- desc: Utility functions for creating converters
- L205 _private* field_ `static readonly Lock s_lockObject = new()` — Object used for locking access to shared objects
- L210 _private* field_ `static readonly Dictionary<PropertyInfo, CbConverter> s_propertyToConverter = ...` — Cache of property to converter
- L210 _private* field_ `static readonly Dictionary< s_propertyToConverter = []` — Cache of property to converter
- L215 _private property_ `private static Dictionary<Type, CbConverter> TypeToConverter { get; }` — Cache of type to converter
- L239 _public property_ `public static List<CbConverterFactory> ConverterFactories { get; }` — List of converter factories. Must be
- L292-310 _public method_ `public static CbConverter GetConverter(PropertyInfo property)` — Gets the converter for a particular property
- L317-323 _public method_ `public static void AddConverter(Type type, CbConverter converter)` — Adds a new converter to the type to converter mapping if it does not exist
- L330-363 _public method_ `public static CbConverter GetConverter(Type type)` — Gets the converter for a particular type
- L370-380 _public method_ `public static CbConverter<T> GetConverter<T>()` — Gets the converter for a given type

#### class `EpicGames.Serialization.CbConverter.CbConverterCache`  
`class CbConverterCache<T>`  
_private*; L254-285_
- desc: Class used to cache values returned by CreateConverterInfo without having to do a dictionary lookup.
- L259 _public property_ `public static CbConverter<T> Instance { get; }` — The converter instance
- L265-269 _private* method_ `static CbConverter<T> CreateConverter()` — Create a typed converter

#### class `EpicGames.Serialization.CbConverter.CbConverterCache.CbConverterWrapper`  
`class CbConverterWrapper(CbConverter inner) : CbConverter<T>`  
_private*; L274-284_
- desc: Wrapper class to convert an untyped converter into a typed one
- L277 _public method_ `public override T Read(CbField field)` — (inheritdoc)
- L280 _public method_ `public override void Write(CbWriter writer, T value)` — (inheritdoc)
- L283 _public method_ `public override void WriteNamed(CbWriter writer, CbFieldName name, T value)` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.Serialization/CbField.cs` (EpicGames.Serialization)


#### enum `EpicGames.Serialization.CbFieldType`  
`public enum CbFieldType : byte`  
_public; L31-190_
- attrs: `[Flags]`
- inherits: `byte`
- desc: Field types and flags for FCbField[View]. DO NOT CHANGE THE VALUE OF ANY MEMBERS OF THIS ENUM! BACKWARD COMPATIBILITY REQUIRES THAT THESE VALUES BE FIXED! SERIALIZATION USES HARD-CODED CONSTANTS BASED ON THESE VALUES!
- L36 _public* enumerator_ `None = 0x00` — A field type that does not occur in a valid object.
- L41 _public* enumerator_ `Null = 0x01` — Null. Payload is empty.
- L48 _public* enumerator_ `Object = 0x02` — Object is an array of fields with unique non-empty names. Payload is a VarUInt byte count for the encoded fields followed by the fields.
- L55 _public* enumerator_ `UniformObject = 0x03` — UniformObject is an array of fields with the same field types and unique non-empty names. Payload is a VarUInt byte count for the encoded fields followed by the fields.
- L62 _public* enumerator_ `Array = 0x04` — Array is an array of fields with no name that may be of different types. Payload is a VarUInt byte count, followed by a VarUInt item count, followed by the fields.
- L70 _public* enumerator_ `UniformArray = 0x05` — UniformArray is an array of fields with no name and with the same field type. Payload is a VarUInt byte count, followed by a VarUInt item count, followed by field type, followed by the fields without their field type.
- L75 _public* enumerator_ `Binary = 0x06` — Binary. Payload is a VarUInt byte count followed by the data. ///
- L80 _public* enumerator_ `String = 0x07` — String in UTF-8. Payload is a VarUInt byte count then an unterminated UTF-8 string.
- L87 _public* enumerator_ `IntegerPositive = 0x08` — Non-negative integer with the range of a 64-bit unsigned integer. Payload is the value encoded as a VarUInt.
- L94 _public* enumerator_ `IntegerNegative = 0x09` — Negative integer with the range of a 64-bit signed integer. Payload is the ones' complement of the value encoded as a VarUInt.
- L99 _public* enumerator_ `Float32 = 0x0a` — Single precision float. Payload is one big endian IEEE 754 binary32 float. ///
- L104 _public* enumerator_ `Float64 = 0x0b` — Double precision float. Payload is one big endian IEEE 754 binary64 float.
- L109 _public* enumerator_ `BoolFalse = 0x0c` — Boolean false value. Payload is empty.
- L114 _public* enumerator_ `BoolTrue = 0x0d` — Boolean true value. Payload is empty.
- L121 _public* enumerator_ `ObjectAttachment = 0x0e` — CompactBinaryAttachment is a reference to a compact binary attachment stored externally. Payload is a 160-bit hash digest of the referenced compact binary data.
- L128 _public* enumerator_ `BinaryAttachment = 0x0f` — BinaryAttachment is a reference to a binary attachment stored externally. Payload is a 160-bit hash digest of the referenced binary data.
- L133 _public* enumerator_ `Hash = 0x10` — Hash. Payload is a 160-bit hash digest.
- L138 _public* enumerator_ `Uuid = 0x11` — UUID/GUID. Payload is a 128-bit UUID as defined by RFC 4122.
- L145 _public* enumerator_ `DateTime = 0x12` — Date and time between 0001-01-01 00:00:00.0000000 and 9999-12-31 23:59:59.9999999. Payload is a big endian int64 count of 100ns ticks since 0001-01-01 00:00:00.0000000.
- L152 _public* enumerator_ `TimeSpan = 0x13` — Difference between two date/time values. Payload is a big endian int64 count of 100ns ticks in the span, and may be negative.
- L159 _public* enumerator_ `ObjectId = 0x14` — ObjectId is an opaque object identifier. See FCbObjectId. Payload is a 12-byte object identifier.
- L167 _public* enumerator_ `CustomById = 0x1e` — CustomById identifies the sub-type of its payload by an integer identifier. Payload is a VarUInt byte count of the sub-type identifier and the sub-type payload, followed by a VarUInt of the sub-type identifier then the payload of the sub-type.
- L176 _public* enumerator_ `CustomByName = 0x1f` — CustomByType identifies the sub-type of its payload by a string identifier. Payload is a VarUInt byte count of the sub-type identifier and the sub-type payload, followed by a VarUInt byte count of the unterminated sub-type identifier, then the sub-type identifier without termination, then the payload of the sub-type.
- L184 _public* enumerator_ `HasFieldType = 0x40` — A transient flag which indicates that the object or array containing this field has stored the field type before the payload and name. Non-uniform objects and fields will set this. Note: Since the flag must never be serialized, this bit may be repurposed in the future.
- L189 _public* enumerator_ `HasFieldName = 0x80` — A persisted flag which indicates that the field has a name stored before the payload.

#### struct `EpicGames.Serialization.CbBinaryAttachment`  
`public readonly struct CbBinaryAttachment(IoHash hash) : IEquatable<CbBinaryAttachment>`  
_public; L199-240_
- attrs: `[DebuggerDisplay("{Hash}")] [JsonConverter(typeof(CbBinaryAttachmentJsonConverter))] [TypeConverter(typeof(CbBinaryAttachmentTypeConverter))]`
- desc: A binary attachment, referenced by IoHash
- L204 _public property_ `public static CbBinaryAttachment Zero { get; }` — Attachment with a hash of zero
- L209 _public property_ `public IoHash Hash { get; }` — Hash of the referenced object
- L212 _public method_ `public override string ToString()` — (inheritdoc)
- L215 _public method_ `public override bool Equals(object? obj)` — (inheritdoc)
- L218 _public method_ `public bool Equals(CbBinaryAttachment other)` — (inheritdoc)
- L221 _public method_ `public override int GetHashCode()` — (inheritdoc)
- L224 _public operator_ `public static bool operator ==(CbBinaryAttachment lhs, CbBinaryAttachment rhs)` — (inheritdoc)
- L227 _public operator_ `public static bool operator !=(CbBinaryAttachment lhs, CbBinaryAttachment rhs)` — (inheritdoc)
- L233 _public operator_ `public static implicit operator CbBinaryAttachment(IoHash hash)` — Convert a hash to a binary attachment
- L239 _public operator_ `public static implicit operator IoHash(CbBinaryAttachment attachment)` — Use a binary attachment as a hash

#### class `EpicGames.Serialization.CbBinaryAttachmentJsonConverter`  
`sealed class CbBinaryAttachmentJsonConverter : JsonConverter<CbBinaryAttachment>`  
_internal*; L245-252_
- inherits: `JsonConverter<CbBinaryAttachment>`
- desc: Type converter for IoHash to and from JSON
- L248 _public method_ `public override CbBinaryAttachment Read(ref Utf8JsonReader reader, Type typeToConvert, JsonSerializerOptions options)` — (inheritdoc)
- L251 _public method_ `public override void Write(Utf8JsonWriter writer, CbBinaryAttachment value, JsonSerializerOptions options)` — (inheritdoc)

#### class `EpicGames.Serialization.CbBinaryAttachmentTypeConverter`  
`sealed class CbBinaryAttachmentTypeConverter : TypeConverter`  
_internal*; L257-264_
- inherits: `TypeConverter`
- desc: Type converter from strings to IoHash objects
- L260 _public method_ `public override bool CanConvertFrom(ITypeDescriptorContext? context, Type sourceType)` — (inheritdoc)
- L263 _public method_ `public override object ConvertFrom(ITypeDescriptorContext? context, CultureInfo? culture, object value)` — (inheritdoc)

#### struct `EpicGames.Serialization.CbObjectAttachment`  
`public readonly struct CbObjectAttachment(IoHash hash) : IEquatable<CbObjectAttachment>`  
_public; L273-314_
- attrs: `[DebuggerDisplay("{Hash}")] [JsonConverter(typeof(CbObjectAttachmentJsonConverter))] [TypeConverter(typeof(CbObjectAttachmentTypeConverter))]`
- desc: An object attachment, referenced by IoHash
- L278 _public property_ `public static CbObjectAttachment Zero { get; }` — Attachment with a hash of zero
- L283 _public property_ `public IoHash Hash { get; }` — Hash of the referenced object
- L286 _public method_ `public override string ToString()` — (inheritdoc)
- L289 _public method_ `public override bool Equals(object? obj)` — (inheritdoc)
- L292 _public method_ `public bool Equals(CbObjectAttachment other)` — (inheritdoc)
- L295 _public method_ `public override int GetHashCode()` — (inheritdoc)
- L298 _public operator_ `public static bool operator ==(CbObjectAttachment lhs, CbObjectAttachment rhs)` — (inheritdoc)
- L301 _public operator_ `public static bool operator !=(CbObjectAttachment lhs, CbObjectAttachment rhs)` — (inheritdoc)
- L307 _public operator_ `public static implicit operator CbObjectAttachment(IoHash hash)` — Use an object attachment as a hash
- L313 _public operator_ `public static implicit operator IoHash(CbObjectAttachment attachment)` — Use an object attachment as a hash

#### class `EpicGames.Serialization.CbObjectAttachmentJsonConverter`  
`sealed class CbObjectAttachmentJsonConverter : JsonConverter<CbObjectAttachment>`  
_internal*; L319-326_
- inherits: `JsonConverter<CbObjectAttachment>`
- desc: Type converter for IoHash to and from JSON
- L322 _public method_ `public override CbObjectAttachment Read(ref Utf8JsonReader reader, Type typeToConvert, JsonSerializerOptions options)` — (inheritdoc)
- L325 _public method_ `public override void Write(Utf8JsonWriter writer, CbObjectAttachment value, JsonSerializerOptions options)` — (inheritdoc)

#### class `EpicGames.Serialization.CbObjectAttachmentTypeConverter`  
`sealed class CbObjectAttachmentTypeConverter : TypeConverter`  
_internal*; L331-338_
- inherits: `TypeConverter`
- desc: Type converter from strings to IoHash objects
- L334 _public method_ `public override bool CanConvertFrom(ITypeDescriptorContext? context, Type sourceType)` — (inheritdoc)
- L337 _public method_ `public override object ConvertFrom(ITypeDescriptorContext? context, CultureInfo? culture, object value)` — (inheritdoc)

#### class `EpicGames.Serialization.CbFieldUtils`  
`public static class CbFieldUtils`  
_public; L343-605_
- desc: Methods that operate on CbFieldType.
- L345 _private const_ `private const CbFieldType SerializedTypeMask = (CbFieldType)0b_1001_1111`
- L346 _private const_ `private const CbFieldType TypeMask = (CbFieldType)0b_0001_1111`
- L348 _private const_ `private const CbFieldType ObjectMask = (CbFieldType)0b_0001_1110`
- L349 _private const_ `private const CbFieldType ObjectBase = (CbFieldType)0b_0000_0010`
- L351 _private const_ `private const CbFieldType ArrayMask = (CbFieldType)0b_0001_1110`
- L352 _private const_ `private const CbFieldType ArrayBase = (CbFieldType)0b_0000_0100`
- L354 _private const_ `private const CbFieldType IntegerMask = (CbFieldType)0b_0011_1110`
- L355 _private const_ `private const CbFieldType IntegerBase = (CbFieldType)0b_0000_1000`
- L357 _private const_ `private const CbFieldType FloatMask = (CbFieldType)0b_0001_1100`
- L358 _private const_ `private const CbFieldType FloatBase = (CbFieldType)0b_0000_1000`
- L360 _private const_ `private const CbFieldType BoolMask = (CbFieldType)0b_0001_1110`
- L361 _private const_ `private const CbFieldType BoolBase = (CbFieldType)0b_0000_1100`
- L363 _private const_ `private const CbFieldType AttachmentMask = (CbFieldType)0b_0001_1110`
- L364 _private const_ `private const CbFieldType AttachmentBase = (CbFieldType)0b_0000_1110`
- L371-374 _public method_ `public static CbFieldType GetType(CbFieldType type)` — Removes flags from the given type
- L381-384 _public method_ `public static CbFieldType GetSerializedType(CbFieldType type)` — Gets the serialized type
- L391-394 _public method_ `public static bool HasFieldType(CbFieldType type)` — Tests if the given field has a type
- L401-404 _public method_ `public static bool HasFieldName(CbFieldType type)` — Tests if the given field has a name
- L411-414 _public method_ `public static bool IsNone(CbFieldType type)` — Tests if the given field type is none
- L421-424 _public method_ `public static bool IsNull(CbFieldType type)` — Tests if the given field type is a null value
- L431-434 _public method_ `public static bool IsObject(CbFieldType type)` — Tests if the given field type is an object
- L441-444 _public method_ `public static bool IsArray(CbFieldType type)` — Tests if the given field type is an array
- L451-454 _public method_ `public static bool IsBinary(CbFieldType type)` — Tests if the given field type is binary
- L461-464 _public method_ `public static bool IsString(CbFieldType type)` — Tests if the given field type is a string
- L471-474 _public method_ `public static bool IsInteger(CbFieldType type)` — Tests if the given field type is an integer
- L481-484 _public method_ `public static bool IsFloat(CbFieldType type)` — Tests if the given field type is a float (or integer, due to implicit conversion)
- L491-494 _public method_ `public static bool IsBool(CbFieldType type)` — Tests if the given field type is a boolean
- L501-504 _public method_ `public static bool IsObjectAttachment(CbFieldType type)` — Tests if the given field type is a compact binary attachment
- L511-514 _public method_ `public static bool IsBinaryAttachment(CbFieldType type)` — Tests if the given field type is a binary attachment
- L521-524 _public method_ `public static bool IsAttachment(CbFieldType type)` — Tests if the given field type is an attachment
- L531-534 _public method_ `public static bool IsHash(CbFieldType type)` — Tests if the given field type is a hash
- L541-544 _public method_ `public static bool IsUuid(CbFieldType type)` — Tests if the given field type is a UUID
- L551-554 _public method_ `public static bool IsDateTime(CbFieldType type)` — Tests if the given field type is a date/time
- L561-564 _public method_ `public static bool IsTimeSpan(CbFieldType type)` — Tests if the given field type is a timespan
- L571-574 _public method_ `public static bool IsObjectId(CbFieldType type)` — Tests if the given field type is a object id
- L581-585 _public method_ `public static bool HasFields(CbFieldType type)` — Tests if the given field type has fields
- L592-596 _public method_ `public static bool HasUniformFields(CbFieldType type)` — Tests if the given field type has uniform fields (array/object)
- L601-604 _public method_ `public static bool MayContainAttachments(CbFieldType type)` — Tests if the type is or may contain fields of any attachment type.

#### enum `EpicGames.Serialization.CbFieldError`  
`public enum CbFieldError : byte`  
_public; L610-626_
- inherits: `byte`
- desc: Errors that can occur when accessing a field. */
- L615 _public* enumerator_ `None` — The field is not in an error state.
- L620 _public* enumerator_ `TypeError` — The value type does not match the requested type.
- L625 _public* enumerator_ `RangeError` — The value is out of range for the requested type.

#### class `EpicGames.Serialization.CbFieldWithNameDebugView`  
`class CbFieldWithNameDebugView`  
_internal*; L631-635_
- desc: Simplified view of CbField in the debugger, for fields with a name
- L633 _public property_ `public string? Name { get; set; }`
- L634 _public property_ `public object? Value { get; set; }`

#### class `EpicGames.Serialization.CbFieldDebugView`  
`class CbFieldDebugView`  
_internal*; L640-648_
- desc: Simplified view of CbField for the debugger
- L642 _public ctor_ `public CbFieldDebugView(CbField field)`
- L647 _public property_ `public object? Value { get; }` — attrs: `[DebuggerBrowsable(DebuggerBrowsableState.RootHidden)]`

#### class `EpicGames.Serialization.CbField`  
`public class CbField : IEquatable<CbField>, IEnumerable<CbField>`  
_public; L670-1744_
- attrs: `[DebuggerDisplay("{DebugValue,nq}")] [DebuggerTypeProxy(typeof(CbFieldDebugView))] [JsonConverter(typeof(CbFieldJsonConverter))]`
- inherits: `IEquatable<CbField>, IEnumerable<CbField>`
- desc: An atom of data in the compact binary format. Accessing the value of a field is always a safe operation, even if accessed as the wrong type. An invalid access will return a default value for the requested type, and set an error code on the field that can be checked with GetLastError and HasLastError. A valid access will clear an error from a previous invalid access. A field is encoded in one or more bytes, depending on its type and the type of object or array that contains it. A field of an object or array which is non-uniform encodes its field type in the first byte, and includes the HasFieldName flag for a field in an object. The field name is encoded in a variable-length unsigned integer of its size in bytes, for named fields, followed by that many bytes of the UTF-8 encoding of the name with no null terminator.The remainder of the field is the payload and is described in the field type enum. Every field must be uniquely addressable when encoded, which means a zero-byte field is not
- L683 _private* property_ `static NoneValueType None { get; }` — Special value returned for "none" fields.
- L688 _private* property_ `object? DebugValue => ...` — Formatter for the debug string
- L693 _public property_ `public static CbField Empty { get; }` — Default empty field
- L698 _public property_ `public CbFieldType TypeWithFlags { get; }` — The field type, with the transient HasFieldType flag if the field contains its type
- L703 _public property_ `public ReadOnlyMemory<byte> Memory { get; }` — Data for this field
- L708 _internal field_ `internal int _nameLen` — Offset of the name with the memory
- L713 _internal field_ `internal int _payloadOffset` — Offset of the payload within the memory
- L718 _public property_ `public CbFieldError Error { get; set; }` — Error for parsing the current field type
- L723-726 _public ctor_ `public CbField() : this(ReadOnlyMemory<byte>.Empty, CbFieldType.None)` — Default constructor
- L732-739 _public ctor_ `public CbField(CbField other)` — Copy constructor
- L746-766 _public ctor_ `public CbField(ReadOnlyMemory<byte> data, CbFieldType type = CbFieldType.HasFieldType)` — Construct a field from a pointer to its data and an optional externally-provided type.
- L771 _public property_ `public Utf8String Name => ...` — Returns the name of the field if it has a name, otherwise an empty view.
- L776-827 _public property_ `public object? Value { get; }` — Gets the value of this field
- L830 _public method_ `public Utf8String GetName()` — (inheritdoc)
- L836-848 _public method_ `public CbObject AsObject()` — Access the field as an object. Defaults to an empty object on error.
- L854-866 _public method_ `public CbArray AsArray()` — Access the field as an array. Defaults to an empty array on error.
- L872-875 _public method_ `public ReadOnlyMemory<byte> AsBinary()` — Access the field as binary data.
- L881-895 _public method_ `public ReadOnlyMemory<byte> AsBinary(ReadOnlyMemory<byte> defaultValue)` — Access the field as binary data.
- L901-904 _public method_ `public byte[] AsBinaryArray()` — Access the field as binary data.
- L910-913 _public method_ `public byte[] AsBinaryArray(byte[] defaultValue)` — Access the field as binary data.
- L919 _public method_ `public string AsString()` — Access the field as a UTF-8 string.
- L925 _public method_ `public string AsString(string defaultValue)` — Access the field as a UTF-8 string.
- L931-934 _public method_ `public Utf8String AsUtf8String()` — Access the field as a UTF-8 string.
- L941-962 _public method_ `public Utf8String AsUtf8String(Utf8String defaultValue)` — Access the field as a UTF-8 string. Returns the provided default on error.
- L967-970 _public method_ `public sbyte AsInt8(sbyte defaultValue = 0)` — Access the field as an int8. Returns the provided default on error.
- L975-978 _public method_ `public short AsInt16(short defaultValue = 0)` — Access the field as an int16. Returns the provided default on error.
- L983-986 _public method_ `public int AsInt32()` — Access the field as an int32. Returns the provided default on error.
- L991-994 _public method_ `public int AsInt32(int defaultValue)` — Access the field as an int32. Returns the provided default on error.
- L999-1002 _public method_ `public long AsInt64()` — Access the field as an int64. Returns the provided default on error.
- L1007-1010 _public method_ `public long AsInt64(long defaultValue)` — Access the field as an int64. Returns the provided default on error.
- L1015-1018 _public method_ `public byte AsUInt8(byte defaultValue = 0)` — Access the field as an int8. Returns the provided default on error.
- L1023-1026 _public method_ `public ushort AsUInt16(ushort defaultValue = 0)` — Access the field as an int16. Returns the provided default on error.
- L1031-1034 _public method_ `public uint AsUInt32()` — Access the field as an int32. Returns the provided default on error.
- L1039-1042 _public method_ `public uint AsUInt32(uint defaultValue)` — Access the field as an int32. Returns the provided default on error.
- L1047-1050 _public method_ `public ulong AsUInt64()` — Access the field as an int64. Returns the provided default on error.
- L1055-1058 _public method_ `public ulong AsUInt64(ulong defaultValue)` — Access the field as an int64. Returns the provided default on error.
- L1067-1094 _private method_ `private ulong AsInteger(ulong defaultValue, int magnitudeBits, bool isSigned)` — Access the field as an integer, checking that it's in the correct range
- L1101-1126 _public method_ `public float AsFloat(float defaultValue = 0.0f)` — Access the field as a float. Returns the provided default on error.
- L1132 _public method_ `public double AsDouble()` — Access the field as a double.
- L1139-1168 _public method_ `public double AsDouble(double defaultValue)` — Access the field as a double. Returns the provided default on error.
- L1174 _public method_ `public bool AsBool()` — Access the field as a bool. Returns the provided default on error.
- L1181-1195 _public method_ `public bool AsBool(bool defaultValue)` — Access the field as a bool. Returns the provided default on error.
- L1201 _public method_ `public CbObjectAttachment AsObjectAttachment()` — Access the field as a hash referencing an object attachment. Returns the provided default on error.
- L1208-1220 _public method_ `public CbObjectAttachment AsObjectAttachment(CbObjectAttachment defaultValue)` — Access the field as a hash referencing an object attachment. Returns the provided default on error.
- L1226 _public method_ `public CbBinaryAttachment AsBinaryAttachment()` — Access the field as a hash referencing a binary attachment. Returns the provided default on error.
- L1233-1245 _public method_ `public CbBinaryAttachment AsBinaryAttachment(CbBinaryAttachment defaultValue)` — Access the field as a hash referencing a binary attachment. Returns the provided default on error.
- L1251 _public method_ `public IoHash AsAttachment()` — Access the field as a hash referencing an attachment. Returns the provided default on error.
- L1258-1270 _public method_ `public IoHash AsAttachment(IoHash defaultValue)` — Access the field as a hash referencing an attachment. Returns the provided default on error.
- L1276 _public method_ `public IoHash AsHash()` — Access the field as a hash referencing an attachment. Returns the provided default on error.
- L1283-1295 _public method_ `public IoHash AsHash(IoHash defaultValue)` — Access the field as a hash referencing an attachment. Returns the provided default on error.
- L1302-1320 _public method_ `public Guid AsUuid(Guid defaultValue = default)` — Access the field as a UUID. Returns a nil UUID on error.
- L1326 _public method_ `public Guid AsUuid()` — Access the field as a UUID. Returns a nil UUID on error.
- L1333-1345 _public method_ `public long AsDateTimeTicks(long defaultValue = 0)` — Reads a date time as number of ticks from the stream
- L1351-1354 _public method_ `public DateTime AsDateTime()` — Access the field as a DateTime.
- L1361-1364 _public method_ `public DateTime AsDateTime(DateTime defaultValue)` — Access the field as a DateTime.
- L1371-1383 _public method_ `public long AsTimeSpanTicks(long defaultValue = 0)` — Reads a timespan as number of ticks from the stream
- L1390 _public method_ `public TimeSpan AsTimeSpan(TimeSpan defaultValue = default)` — Reads a timespan as number of ticks from the stream
- L1396 _public method_ `public CbObjectId AsObjectId()` — Access the field as a object id
- L1403-1416 _public method_ `public CbObjectId AsObjectId(CbObjectId defaultValue)` — Access the field as a object id
- L1419 _public method_ `public bool HasName()` — (inheritdoc)
- L1422 _public method_ `public bool IsNull()` — (inheritdoc)
- L1425 _public method_ `public bool IsObject()` — (inheritdoc)
- L1428 _public method_ `public bool IsArray()` — (inheritdoc)
- L1431 _public method_ `public bool IsBinary()` — (inheritdoc)
- L1434 _public method_ `public bool IsString()` — (inheritdoc)
- L1437 _public method_ `public bool IsInteger()` — (inheritdoc)
- L1440 _public method_ `public bool IsFloat()` — (inheritdoc)
- L1443 _public method_ `public bool IsBool()` — (inheritdoc)
- L1446 _public method_ `public bool IsObjectAttachment()` — (inheritdoc)
- L1449 _public method_ `public bool IsBinaryAttachment()` — (inheritdoc)
- L1452 _public method_ `public bool IsAttachment()` — (inheritdoc)
- L1455 _public method_ `public bool IsHash()` — (inheritdoc)
- L1458 _public method_ `public bool IsUuid()` — (inheritdoc)
- L1461 _public method_ `public bool IsDateTime()` — (inheritdoc)
- L1464 _public method_ `public bool IsTimeSpan()` — (inheritdoc)
- L1467 _public method_ `public bool IsObjectId()` — (inheritdoc)
- L1473 _public operator_ `public static explicit operator bool(CbField field)` — Whether the field has a value
- L1481 _public method_ `public bool HasValue()` — Whether the field has a value. All fields in a valid object or array have a value. A field with no value is returned when finding a field by name fails or when accessing an iterator past the end.
- L1486 _public method_ `public bool HasError()` — Whether the last field access encountered an error.
- L1489 _public method_ `public CbFieldError GetError()` — (inheritdoc)
- L1495 _public method_ `public int GetSize()` — Returns the size of the field in bytes, including the type and name
- L1501-1512 _public method_ `public Blake3Hash GetHash()` — Calculate the hash of the field, including the type and name.
- L1518-1524 _private* method_ `void AppendHash(Blake3.Hasher hasher)` — Append the hash of the field, including the type and name
- L1527 _public method_ `public override int GetHashCode()` — (inheritdoc)
- L1530 _public method_ `public override bool Equals(object? other)` — (inheritdoc)
- L1543-1546 _public method_ `public bool Equals(CbField? other)` — Whether this field is identical to the other field. Performs a deep comparison of any contained arrays or objects and their fields. Comparison assumes that both fields are valid and are written in the canonical format. Fields must be written in the same order in arrays and objects, and name comparison is case sensitive. If these assumptions do not hold, this may return false for equivalent inputs. Validation can be performed with ValidateCompactBinary, except for field order and field name case.
- L1552-1556 _public method_ `public void CopyTo(Span<byte> buffer)` — Copy the field into a buffer of exactly GetSize() bytes, including the type and name.
- L1562-1579 _public method_ `public void IterateAttachments(Action<CbField> visitor)` — Invoke the visitor for every attachment in the field.
- L1589-1601 _public method_ `public bool TryGetView(out ReadOnlyMemory<byte> outView)` — Try to get a view of the field as it would be serialized, such as by CopyTo. A view is available if the field contains its type. Access the equivalent for other fields through FCbField::GetBuffer, FCbField::Clone, or CopyTo.
- L1609 _public indexer_ `public CbField this[CbFieldName name]` — Find a field of an object by case-sensitive name comparison, otherwise a field with no value.
- L1616-1641 _public method_ `public CbFieldIterator CreateIterator()` — Create an iterator for the fields of an array or object, otherwise an empty iterator.
- L1644-1650 _public method_ `public IEnumerator<CbField> GetEnumerator()` — (inheritdoc)
- L1653 _private* method_ `IEnumerator IEnumerable.GetEnumerator()` — (inheritdoc)
- L1659-1663 _private method_ `private ReadOnlyMemory<byte> GetViewNoType()` — Returns a view of the name and value payload, which excludes the type.
- L1668 _internal property_ `internal ReadOnlyMemory<byte> Payload => ...` — Accessor for the payload
- L1674 _internal method_ `internal ReadOnlyMemory<byte> GetPayloadView()` — Returns a view of the value payload, which excludes the type and name.
- L1679 _internal method_ `internal new CbFieldType GetType()` — Returns the type of the field excluding flags.
- L1684 _internal method_ `internal CbFieldType GetTypeWithFlags()` — Returns the type of the field excluding flags.
- L1690-1733 _public method_ `public ulong GetPayloadSize()` — Returns the size of the value payload in bytes, which is the field excluding the type and name.
- L1740-1743 _public method_ `public bool ValueEquals(CbField? other)` — Verifies if type and value is equal between two fields, ignoring the name

#### class `EpicGames.Serialization.CbField.NoneValueType`  
`class NoneValueType`  
_private*; L676-678_
- attrs: `[DebuggerDisplay("<none>")]`
- desc: Type returned for none values

#### class `EpicGames.Serialization.CbFieldJsonConverter`  
`public class CbFieldJsonConverter : JsonConverter<CbField>`  
_public; L1749-1936_
- inherits: `JsonConverter<CbField>`
- desc: Converter to and from JSON objects
- L1752-1755 _public method_ `public override CbField Read(ref Utf8JsonReader reader, Type typeToConvert, JsonSerializerOptions options)` — (inheritdoc)
- L1758-1761 _public method_ `public override void Write(Utf8JsonWriter writer, CbField field, JsonSerializerOptions options)` — (inheritdoc)
- L1770-1935 _public method_ `public static void WriteField(Utf8JsonWriter writer, CbField field, JsonSerializerOptions options)` — Writes a CbField to a Jtf8JsonWriter

#### class `EpicGames.Serialization.CbObjectJsonConverter`  
`public class CbObjectJsonConverter : JsonConverter<CbObject>`  
_public; L1941-1964_
- inherits: `JsonConverter<CbObject>`
- desc: Converter to and from JSON objects
- L1944-1951 _public method_ `public override CbObject Read(ref Utf8JsonReader reader, Type typeToConvert, JsonSerializerOptions options)` — (inheritdoc)
- L1954-1963 _public method_ `public override void Write(Utf8JsonWriter writer, CbObject o, JsonSerializerOptions options)` — (inheritdoc)

#### class `EpicGames.Serialization.CbFieldEnumerator`  
`public sealed class CbFieldEnumerator(ReadOnlyMemory<byte> data, CbFieldType uniformType) : IEnumerator<CbField>`  
_public; L1970-2013_
- desc: Enumerator for contents of a field
- L1974 _public property_ `public CbField Current { get; set; }` — (inheritdoc)
- L1977 _private* property_ `object? IEnumerator.Current => ...` — (inheritdoc)
- L1980-1982 _public method_ `public void Dispose()` — (inheritdoc)
- L1985-1988 _public method_ `public void Reset()` — (inheritdoc)
- L1991-2003 _public method_ `public bool MoveNext()` — (inheritdoc)
- L2009-2012 _public method_ `public CbFieldEnumerator Clone()` — Clone this enumerator

#### class `EpicGames.Serialization.CbFieldIterator`  
`public class CbFieldIterator`  
_public; L2018-2207_
- desc: Iterator for fields
- L2023 _private* field_ `ReadOnlyMemory<byte> _nextData` — The underlying buffer
- L2028 _private* field_ `readonly CbFieldType _uniformType` — Type for all fields
- L2033 _public property_ `public CbField Current { get; set; }` — The current iterator
- L2038-2041 _public ctor_ `public CbFieldIterator() : this(ReadOnlyMemory<byte>.Empty, CbFieldType.HasFieldType)` — Default constructor
- L2047-2051 _private ctor_ `private CbFieldIterator(CbField field)` — Constructor for single field iterator
- L2058-2064 _public ctor_ `public CbFieldIterator(ReadOnlyMemory<byte> data, CbFieldType uniformType)` — Constructor
- L2070-2075 _public ctor_ `public CbFieldIterator(CbFieldIterator other)` — Copy constructor
- L2082-2085 _public method_ `public static CbFieldIterator MakeSingle(CbField field)` — Construct a field range that contains exactly one field.
- L2093-2096 _public method_ `public static CbFieldIterator MakeRange(ReadOnlyMemory<byte> view, CbFieldType type = CbFieldType.HasFieldType)` — Construct a field range from a buffer containing zero or more valid fields.
- L2102-2105 _public method_ `public bool IsValid()` — Check if the current value is valid
- L2111-2114 _public method_ `public CbField GetCurrent()` — Accessor for the current value
- L2120-2144 _public method_ `public void IterateRangeAttachments(Action<CbField> visitor)` — Invoke the visitor for every attachment in the field range.
- L2150-2163 _public method_ `public bool MoveNext()` — Move to the next element
- L2169-2172 _public operator_ `public static implicit operator bool(CbFieldIterator iterator)` — Test whether the iterator is valid
- L2179-2182 _public operator_ `public static CbFieldIterator operator ++(CbFieldIterator iterator)` — Move to the next item
- L2185-2188 _public method_ `public override bool Equals(object? obj)` — (inheritdoc)
- L2191-2194 _public method_ `public override int GetHashCode()` — (inheritdoc)
- L2197-2200 _public operator_ `public static bool operator ==(CbFieldIterator a, CbFieldIterator b)` — (inheritdoc)
- L2203-2206 _public operator_ `public static bool operator !=(CbFieldIterator a, CbFieldIterator b)` — (inheritdoc)

#### class `EpicGames.Serialization.CbArrayDebugView`  
`class CbArrayDebugView(CbArray array)`  
_internal*; L2212-2216_
- desc: Simplified view of CbArray for display in the debugger
- L2215 _public property_ `public object?[] Value => ...` — attrs: `[DebuggerBrowsable(DebuggerBrowsableState.RootHidden)]`

#### class `EpicGames.Serialization.CbArray`  
`public class CbArray : IEnumerable<CbField>`  
_public; L2226-2396_
- attrs: `[DebuggerDisplay("Count = {Count}")] [DebuggerTypeProxy(typeof(CbArrayDebugView))]`
- inherits: `IEnumerable<CbField>`
- desc: Array of CbField that have no names. Accessing a field of the array requires iteration. Access by index is not provided because the cost of accessing an item by index scales linearly with the index.
- L2231 _private* field_ `readonly CbField _innerField` — The field containing this array
- L2236 _public property_ `public static CbArray Empty { get; }` — Empty array constant
- L2241-2244 _public ctor_ `public CbArray()` — Construct an array with no fields
- L2250-2253 _private ctor_ `private CbArray(CbField field)` — Constructor
- L2260-2263 _public ctor_ `public CbArray(ReadOnlyMemory<byte> data, CbFieldType type = CbFieldType.HasFieldType)` — Constructor
- L2268-2276 _public property_ `public int Count { get; }` — Number of items in this array
- L2282 _public method_ `public CbField AsField()` — Access the array as an array field.
- L2289 _public method_ `public static CbArray FromFieldNoCheck(CbField field)` — Construct an array from an array field. No type check is performed!
- L2295-2298 _public method_ `public int GetSize()` — Returns the size of the array in bytes if serialized by itself with no name.
- L2304-2315 _public method_ `public Blake3Hash GetHash()` — Calculate the hash of the array if serialized by itself with no name.
- L2320-2325 _public method_ `public void AppendHash(Blake3.Hasher hasher)` — Append the hash of the array if serialized by itself with no name.
- L2328 _public method_ `public override bool Equals(object? obj)` — (inheritdoc)
- L2331 _public method_ `public override int GetHashCode()` — (inheritdoc)
- L2344-2347 _public method_ `public bool Equals(CbArray? other)` — Whether this array is identical to the other array. Performs a deep comparison of any contained arrays or objects and their fields. Comparison assumes that both fields are valid and are written in the canonical format.Fields must be written in the same order in arrays and objects, and name comparison is case sensitive.If these assumptions do not hold, this may return false for equivalent inputs. Validation can be done with the All mode to check these assumptions about the format of the inputs.
- L2353-2357 _public method_ `public void CopyTo(Span<byte> buffer)` — Copy the array into a buffer of exactly GetSize() bytes, with no name.
- L2360 _public method_ `public void IterateAttachments(Action<CbField> visitor)`
- L2368-2376 _public method_ `public bool TryGetView(out ReadOnlyMemory<byte> outView)` — Try to get a view of the array as it would be serialized, such as by CopyTo. A view is available if the array contains its type and has no name. Access the equivalent for other arrays through FCbArray::GetBuffer, FCbArray::Clone, or CopyTo.
- L2379 _public method_ `public CbFieldIterator CreateIterator()` — (inheritdoc)
- L2382 _public method_ `public IEnumerator<CbField> GetEnumerator()` — (inheritdoc)
- L2385 _private* method_ `IEnumerator IEnumerable.GetEnumerator()` — (inheritdoc)
- L2390 _internal method_ `internal new CbFieldType GetType()` — (inheritdoc)
- L2393 _internal method_ `internal ReadOnlyMemory<byte> GetPayloadView()` — (inheritdoc)

#### class `EpicGames.Serialization.CbObjectDebugView`  
`class CbObjectDebugView(CbObject obj)`  
_internal*; L2401-2412_
- desc: Simplified view of CbObject for display in the debugger
- L2411 _public property_ `public Property[] Properties => ...` — attrs: `[DebuggerBrowsable(DebuggerBrowsableState.RootHidden)]`

#### class `EpicGames.Serialization.CbObjectDebugView.Property`  
`public class Property`  
_public; L2404-2408_
- attrs: `[DebuggerDisplay("{Name}: {Value}")]`
- L2406 _public property_ `public string? Name { get; set; }`
- L2407 _public property_ `public object? Value { get; set; }`

#### class `EpicGames.Serialization.CbObject`  
`public class CbObject : IEnumerable<CbField>`  
_public; L2424-2687_
- attrs: `[DebuggerTypeProxy(typeof(CbObjectDebugView))] [JsonConverter(typeof(CbObjectJsonConverter))]`
- inherits: `IEnumerable<CbField>`
- desc: Array of CbField that have unique names. Accessing the fields of an object is always a safe operation, even if the requested field does not exist. Fields may be accessed by name or through iteration. When a field is requested that is not found in the object, the field that it returns has no value (evaluates to false) though attempting to access the empty field is also safe, as described by FCbFieldView.
- L2429 _public property_ `public static CbObject Empty { get; }` — Empty array constant
- L2434 _private field_ `private readonly CbField _innerField` — The inner field object
- L2440-2443 _private ctor_ `private CbObject(CbField field)` — Constructor
- L2450-2453 _public ctor_ `public CbObject(ReadOnlyMemory<byte> buffer, CbFieldType fieldType = CbFieldType.HasFieldType)` — Constructor
- L2460-2467 _public method_ `public static CbObject Build(Action<CbWriter> build)` — Builds an object by calling a delegate with a writer
- L2477 _public method_ `public CbField Find(CbFieldName name)` — Find a field by case-sensitive name comparison. The cost of this operation scales linearly with the number of fields in the object. Prefer to iterate over the fields only once when consuming an object.
- L2484 _public method_ `public CbField FindIgnoreCase(CbFieldName name)` — Find a field by case-insensitive name comparison.
- L2492 _public indexer_ `public CbField this[CbFieldName name]` — Find a field by case-sensitive name comparison.
- L2499 _public method_ `public CbField AsField()` — Gets the underlying field for this object
- L2506 _public method_ `public static CbObject FromFieldNoCheck(CbField field)` — Construct an object from an object field. No type check is performed!
- L2512-2515 _public method_ `public int GetSize()` — Returns the size of the object in bytes if serialized by itself with no name.
- L2521-2532 _public method_ `public Blake3Hash GetHash()` — Calculate the hash of the object if serialized by itself with no name.
- L2538-2543 _public method_ `public void AppendHash(Blake3.Hasher hasher)` — Append the hash of the object if serialized by itself with no name.
- L2546 _public method_ `public override bool Equals(object? obj)` — (inheritdoc)
- L2549 _public method_ `public override int GetHashCode()` — (inheritdoc)
- L2562-2565 _public method_ `public bool Equals(CbObject? other)` — Whether this object is identical to the other object. Performs a deep comparison of any contained arrays or objects and their fields. Comparison assumes that both fields are valid and are written in the canonical format. Fields must be written in the same order in arrays and objects, and name comparison is case sensitive. If these assumptions do not hold, this may return false for equivalent inputs. Validation can be done with the All mode to check these assumptions about the format of the inputs.
- L2571-2575 _public method_ `public void CopyTo(Span<byte> buffer)` — Copy the object into a buffer of exactly GetSize() bytes, with no name.
- L2581 _public method_ `public void IterateAttachments(Action<CbField> visitor)` — Invoke the visitor for every attachment in the object.
- L2587-2597 _public method_ `public ReadOnlyMemory<byte> GetView()` — Creates a view of the object, excluding the name
- L2607-2615 _public method_ `public bool TryGetView(out ReadOnlyMemory<byte> outView)` — Try to get a view of the object as it would be serialized, such as by CopyTo. A view is available if the object contains its type and has no name. Access the equivalent for other objects through FCbObject::GetBuffer, FCbObject::Clone, or CopyTo.
- L2618 _public method_ `public CbFieldIterator CreateIterator()` — (inheritdoc)
- L2621 _public method_ `public IEnumerator<CbField> GetEnumerator()` — (inheritdoc)
- L2624 _private* method_ `IEnumerator IEnumerable.GetEnumerator()` — (inheritdoc)
- L2631 _public method_ `public static CbObject Clone(CbObject obj)` — Clone this object
- L2638-2646 _public method_ `public string ToJson()` — Convert this object to JSON
- L2652-2660 _public method_ `public void ToJson(Utf8JsonWriter writer)` — Write this object to JSON
- L2667-2675 _public method_ `public void ToJson(Utf8JsonWriter writer, JsonSerializerOptions options)` — Write this object to JSON
- L2681-2684 _public method_ `public static CbObject FromJson(string json)` — Converts a json object into a CbObject

#### struct `EpicGames.Serialization.CbObjectId`  
`public readonly struct CbObjectId(uint a, uint b, uint c) : IEquatable<CbObjectId>, IComparer<CbObjectId>, IComparable<CbObjectId>`  
_public; L2698-2859_
- attrs: `[JsonConverter(typeof(CbObjectIdJsonConverter))] [TypeConverter(typeof(CbObjectIdTypeConverter))]`
- desc: ObjectId used within compact binary, similar to an uuid type 4
- L2701 _private* field_ `readonly uint _a = a`
- L2702 _private* field_ `readonly uint _b = b`
- L2703 _private* field_ `readonly uint _c = c`
- L2706 _private field_ `private static uint s_objectIdSerial = CalculateRunId()`
- L2711 _public property_ `public static CbObjectId Zero { get; }` — The zero value of an object id
- L2717-2719 _public ctor_ `public CbObjectId(ReadOnlySpan<byte> payload) : this(BinaryPrimitives.ReadUInt32BigEndian(payload[0..4]), BinaryPrimitives.ReadUInt32BigEndian(payload[4..8]), BinaryPrimitives.ReadUInt32BigEndian(payload[8..12]))` — Constructor
- L2726-2730 _public method_ `public static CbObjectId Parse(string text)` — Parses a object id from the given hex string
- L2738-2752 _public method_ `public static bool TryParse(string text, out CbObjectId objectId)` — Parses a digest from the given hex string
- L2758-2766 _public method_ `public static CbObjectId NewObjectId()` — Generates a new object id
- L2768 _private property_ `private static uint RunId { get; }`
- L2770-2774 _private method_ `private static uint CalculateRunId()`
- L2780-2785 _public method_ `public void CopyTo(Span<byte> span)` — Copies this objectid into a span
- L2791-2796 _public method_ `public byte[] ToByteArray()` — Converts this object id to a byte array
- L2802-2805 _public method_ `public Utf8String ToUtf8String()` — Creates a utf8string of the object id
- L2808-2811 _public method_ `public override string ToString()` — (inheritdoc)
- L2814 _public method_ `public bool Equals(CbObjectId other)` — (inheritdoc)
- L2817 _public method_ `public override bool Equals(object? obj)` — (inheritdoc)
- L2820 _public method_ `public override int GetHashCode()` — (inheritdoc)
- L2825 _public operator_ `public static bool operator ==(CbObjectId a, CbObjectId b)` — Test two object ids for equality
- L2830 _public operator_ `public static bool operator !=(CbObjectId a, CbObjectId b)` — Test two object ids for equality
- L2835-2850 _public method_ `public int Compare(CbObjectId x, CbObjectId y)` — Compare two object ids by comparing their components
- L2855-2858 _public method_ `public int CompareTo(CbObjectId other)` — Compare two object ids by comparing their components

#### class `EpicGames.Serialization.CbObjectIdReverseComparer`  
`public sealed class CbObjectIdReverseComparer : IComparer<CbObjectId>`  
_public; L2864-2873_
- inherits: `IComparer<CbObjectId>`
- desc: A comparer for inverse comparisons of a cb object (newest first)
- L2869-2872 _public method_ `public int Compare(CbObjectId x, CbObjectId y)` — Compare two cb objects returning the newst first

#### class `EpicGames.Serialization.CbObjectIdJsonConverter`  
`sealed class CbObjectIdJsonConverter : JsonConverter<CbObjectId>`  
_internal*; L2878-2885_
- inherits: `JsonConverter<CbObjectId>`
- desc: Type converter for CbObjectId to and from JSON
- L2881 _public method_ `public override CbObjectId Read(ref Utf8JsonReader reader, Type typeToConvert, JsonSerializerOptions options)` — (inheritdoc)
- L2884 _public method_ `public override void Write(Utf8JsonWriter writer, CbObjectId value, JsonSerializerOptions options)` — (inheritdoc)

#### class `EpicGames.Serialization.CbObjectIdTypeConverter`  
`sealed class CbObjectIdTypeConverter : TypeConverter`  
_internal*; L2890-2896_
- inherits: `TypeConverter`
- desc: Type converter for CbObjectId
- L2892 _public method_ `public override bool CanConvertFrom(ITypeDescriptorContext? context, Type sourceType)`
- L2895 _public method_ `public override object ConvertFrom(ITypeDescriptorContext? context, CultureInfo? culture, object value)` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.Serialization/CbPackage.cs` (EpicGames.Serialization)


#### class `EpicGames.Serialization.CbPackageConstants`  
`static class CbPackageConstants`  
_internal*; L15-18_
- L17 _public const_ `public const uint CbPackageHeaderMagic = 0xaa77aacc`

#### struct `EpicGames.Serialization.CbPackageHeader`  
`struct CbPackageHeader`  
_internal*; L24-78_
- desc: Header in the CbPackage format
- L26-33 _private ctor_ `private CbPackageHeader(uint attachmentCount, uint reserved1 = 0, uint reserved2 = 0)`
- L35 _public property_ `public uint HeaderMagic { get; set; }`
- L37 _public property_ `public uint AttachmentCount { get; set; }`
- L39 _public property_ `public uint Reserved1 { get; set; }`
- L41 _public property_ `public uint Reserved2 { get; set; }`
- L43 _private const_ `private const int Length = sizeof(uint) * 4`
- L45-68 _public method_ `public static async Task<CbPackageHeader> ReadAsync(Stream s)`
- L70-77 _public method_ `public readonly void Write(Stream stream)`

#### enum `EpicGames.Serialization.CbPackageAttachmentFlags`  
`public enum CbPackageAttachmentFlags : uint`  
_public; L84-100_
- attrs: `[Flags]`
- inherits: `uint`
- desc: Per attachment entry flags
- L89 _public* enumerator_ `IsCompressed = (1u << 0)` — Is marshaled using compressed buffer storage format
- L94 _public* enumerator_ `IsObject = (1u << 1)` — Is compact binary object
- L99 _public* enumerator_ `IsError = (1u << 2)` — Is error (compact binary formatted) object

#### struct `EpicGames.Serialization.CbPackageAttachmentEntry`  
`public struct CbPackageAttachmentEntry`  
_public; L105-163_
- desc: Header for each attachment in the package
- L110 _public property_ `public ulong PayloadSize { get; set; }` — The size of the attachment
- L115 _public property_ `public CbPackageAttachmentFlags Flags { get; set; }` — Flags description the attachment
- L120 _public property_ `public IoHash AttachmentHash { get; set; }` — The hash of the attachment
- L127-148 _internal method_ `internal static async Task<CbPackageAttachmentEntry> ReadAsync(Stream s)` — Reads a package attachment struct from a stream
- L150 _private const_ `private const int Length = IoHash.NumBytes + sizeof(ulong) + sizeof(uint)`
- L156-162 _internal method_ `internal readonly void Write(Stream stream)` — Write a package attachment entry to the stream

#### class `EpicGames.Serialization.CbPackageReader`  
`public class CbPackageReader`  
_public; L168-283_
- desc: Reads a CbPackage (a bundle of both a cb object and its attachments)
- L171 _private field_ `private readonly CbPackageHeader _header`
- L173 _private field_ `private readonly Stream _attachmentsStream`
- L174 _private field_ `private readonly List<CbPackageAttachmentEntry> _attachmentEntries = []`
- L176-183 _private ctor_ `private CbPackageReader(CbPackageHeader header, CbObject rootObject, IoHash rootHash, List<CbPackageAttachmentEntry> attachmentEntries, Stream attachmentsStream)`
- L185-202 _private method_ `private static async Task<byte[]> ReadStreamAsync(Stream s, int count)`
- L209-252 _public method_ `public static async Task<CbPackageReader> CreateAsync(Stream s)` — Create a package reader from a stream, used to stream in the attachments of the package
- L258-272 _public method_ `public async IAsyncEnumerable<(CbPackageAttachmentEntry, byte[])> IterateAttachmentsAsync()` — Iterates over the attachments, returning the attachment entry and the attachment (in memory)
- L277 _public property_ `public CbObject RootObject { get; }` — The CbObject that is the root object (that references the other attachments in the package)
- L282 _public property_ `public IoHash RootHash { get; }` — The hash of the root object

#### class `EpicGames.Serialization.CbPackageBuilder`  
`public sealed class CbPackageBuilder : IDisposable`  
_public; L288-381_
- inherits: `IDisposable`
- desc: Builds a in-memory representation of a CbPackage
- L290 _private field_ `private readonly List<(CbPackageAttachmentEntry, Stream)> _streamAttachments = []`
- L295-297 _public ctor_ `public CbPackageBuilder()` — Constructor for the package builder
- L300-306 _public method_ `public void Dispose()` — (inheritdoc)
- L315-325 _public method_ `public void AddAttachment(IoHash attachmentHash, CbPackageAttachmentFlags flags, byte[] blobMemory)` — Add a attachment to the package builder using in memory buffer
- L335-345 _public method_ `public void AddAttachment(IoHash attachmentHash, CbPackageAttachmentFlags flags, Stream stream, ulong length)` — Add a attachment to the package builder from a stream, will be cache in memory for the lifetime of the package builder
- L351-380 _public method_ `public async Task<byte[]> ToByteArrayAsync()` — Generate a contiguous buffer of the cb package

### `Source/Programs/Shared/EpicGames.Serialization/CbSerializer.cs` (EpicGames.Serialization)


#### class `EpicGames.Serialization.CbObjectAttribute`  
`public sealed class CbObjectAttribute : Attribute`  
_public; L14-16_
- attrs: `[AttributeUsage(AttributeTargets.Class)]`
- inherits: `Attribute`
- desc: Marks a class as supporting serialization to compact-binary, even if it does not have exposed fields. This suppresses errors when base class objects are empty.

#### class `EpicGames.Serialization.CbFieldAttribute`  
`public sealed class CbFieldAttribute : Attribute`  
_public; L22-44_
- attrs: `[AttributeUsage(AttributeTargets.Property)]`
- inherits: `Attribute`
- desc: Attribute used to mark a property that should be serialized to compact binary
- L27 _public property_ `public string? Name { get; }` — Name of the serialized field
- L32-34 _public ctor_ `public CbFieldAttribute()` — Default constructor
- L40-43 _public ctor_ `public CbFieldAttribute(string name)` — Constructor

#### class `EpicGames.Serialization.CbIgnoreAttribute`  
`public sealed class CbIgnoreAttribute : Attribute`  
_public; L50-52_
- attrs: `[AttributeUsage(AttributeTargets.Property)]`
- inherits: `Attribute`
- desc: Attribute used to mark that a property should not be serialized to compact binary

#### class `EpicGames.Serialization.CbPolymorphicAttribute`  
`public sealed class CbPolymorphicAttribute : Attribute`  
_public; L58-60_
- attrs: `[AttributeUsage(AttributeTargets.Class)]`
- inherits: `Attribute`
- desc: Attribute used to indicate that this object is the base for a class hierarchy. Each derived class must have a [CbDiscriminator] attribute.

#### class `EpicGames.Serialization.CbDiscriminatorAttribute`  
`public sealed class CbDiscriminatorAttribute(string name) : Attribute`  
_public; L67-73_
- attrs: `[AttributeUsage(AttributeTargets.Class)]`
- desc: Sets the name used for discriminating between derived classes during serialization
- L72 _public property_ `public string Name { get; }` — Name used to identify this class

#### class `EpicGames.Serialization.CbException`  
`public class CbException : Exception`  
_public; L78-89_
- inherits: `Exception`
- desc: Exception thrown when serializing cb objects
- L81-83 _public ctor_ `public CbException(string message) : base(message)` — (inheritdoc)
- L86-88 _public ctor_ `public CbException(string message, Exception inner) : base(message, inner)` — (inheritdoc)

#### class `EpicGames.Serialization.CbEmptyClassException`  
`public sealed class CbEmptyClassException(Type classType) : CbException($"{classType.Name} does not have any fields marked with a [CbField] attribute. If this is intended, explicitly mark the class with a [CbObject] attribute.")`  
_public; L97-103_
- desc: Exception indicating that a class does not have any fields to serialize
- L102 _public property_ `public Type ClassType { get; }` — Type with missing field annotations

#### class `EpicGames.Serialization.CbSerializer`  
`public static class CbSerializer`  
_public; L108-209_
- desc: Attribute-driven compact binary serializer
- L116-121 _public method_ `public static CbObject Serialize(Type type, object value)` — Serialize an object
- L129-134 _public method_ `public static CbObject Serialize<T>(T value)` — Serialize an object
- L142-147 _public method_ `public static byte[] SerializeToByteArray<T>(T value)` — Serialize an object
- L155-158 _public method_ `public static void Serialize<T>(CbWriter writer, T value)` — Serialize a property to a given writer
- L167-170 _public method_ `public static void Serialize<T>(CbWriter writer, CbFieldName name, T value)` — Serialize a named property to the given writer
- L178-181 _public method_ `public static object? Deserialize(CbField field, Type type)` — Deserialize an object from a CbObject
- L189-192 _public method_ `public static T Deserialize<T>(CbField field)` — Deserialize an object from a CbField
- L200 _public method_ `public static T Deserialize<T>(CbObject obj)` — Deserialize an object from a CbObject
- L208 _public method_ `public static T Deserialize<T>(ReadOnlyMemory<byte> data)` — Deserialize an object from a block of memory

#### class `EpicGames.Serialization.CbJsonReader`  
`public static class CbJsonReader`  
_public; L214-410_
- desc: Helper to convert a json string into a cb object with conventions for how to detect types that json can not naturally encode
- L220-227 _public method_ `public static CbObject FromJson(string json)` — Converts a json object into a CbObject
- L229-406 _internal method_ `internal static void ReadJsonField(JsonElement jsonElement, string? fieldName, CbWriter writer)`
- L408 _private const_ `private const string CompactBinaryAttachmentPrefix = "obj/"`
- L409 _private const_ `private const string BinaryAttachmentPrefix = "bin/"`

### `Source/Programs/Shared/EpicGames.Serialization/CbWriter.cs` (EpicGames.Serialization)


#### class `EpicGames.Serialization.CbWriterException`  
`public class CbWriterException : Exception`  
_public; L16-36_
- inherits: `Exception`
- desc: Exception for CbWriter
- L22-25 _public ctor_ `public CbWriterException(string message) : base(message)` — Constructor
- L32-35 _public ctor_ `public CbWriterException(string message, Exception? ex) : base(message, ex)` — Constructor

#### interface `EpicGames.Serialization.ICbWriter`  
`public interface ICbWriter`  
_public; L41-79_
- desc: Interface for compact binary writers
- L47 _public* method_ `void BeginObject(CbFieldName name)` — Begin writing an object field
- L52 _public* method_ `void EndObject()` — End the current object
- L59 _public* method_ `void BeginArray(CbFieldName name, CbFieldType elementType)` — Begin writing a named array field
- L64 _public* method_ `void EndArray()` — End the current array
- L72 _public* method_ `Span<byte> WriteField(CbFieldType type, CbFieldName name, int length)` — Writes the header for a named field
- L78 _public* method_ `void WriteReference(ReadOnlyMemory<byte> data)` — Writes a reference to an external binary field into the output stream

#### record struct `EpicGames.Serialization.CbFieldName`  
`public record struct CbFieldName(Utf8String Text)`  
_public; L84-95_
- desc: Wrapper for a field name, which can come from an encoded UTF8 string or regular C# string
- L89 _public operator_ `public static implicit operator CbFieldName(string text)` — Implicit conversion from a string
- L94 _public operator_ `public static implicit operator CbFieldName(Utf8String text)` — Implicit conversion from a utf8 string

#### class `EpicGames.Serialization.CbWriterBase`  
`public abstract class CbWriterBase : ICbWriter`  
_public; L100-676_
- inherits: `ICbWriter`
- desc: Base class for ICbWriter implementations. Tracks structural data for fixing up lengths and offsets, without managing any buffers for field data.
- L147 _private* field_ `readonly Scope _rootScope = new() { _fieldType = CbFieldType.Array }`
- L148 _private* field_ `readonly Stack<Scope> _openScopes = new()`
- L149 _private* field_ `readonly Stack<Scope> _freeScopes = new()`
- L151 _private* field_ `Memory<byte> _buffer = Memory<byte>.Empty`
- L152 _private* field_ `int _bufferPos = 0`
- L153 _private* field_ `int _bufferEnd = 0`
- L158-161 _protected ctor_ `protected CbWriterBase()` — Constructor
- L166-170 _protected method_ `protected void Reset()` — Resets the current contents of the writer
- L172-180 _private* method_ `void AddChildrenToFreeList(Scope root)`
- L186-194 _private* method_ `Scope AllocScope()` — Allocate a scope object
- L200-208 _private* method_ `void AddLeafData(ReadOnlyMemory<byte> data)` — Creates a scope containing leaf data
- L213-226 _private* method_ `Scope EnterScope(CbFieldType fieldType, CbFieldName name)` — Insert a new scope
- L231-320 _private* method_ `void LeaveScope()` — Pop a scope from the current open list
- L326-334 _public method_ `public void BeginObject(CbFieldName name)` — Begin writing an object field
- L341-350 _public method_ `public void BeginUniformObject(CbFieldName name, CbFieldType elementType)` — Begin writing a uniform object field, an object which fields are all the same type
- L355 _public method_ `public void EndObject()` — End the current object
- L362-371 _public method_ `public void BeginArray(CbFieldName name, CbFieldType elementType)` — Begin writing a named array field
- L376 _public method_ `public void EndArray()` — End the current array
- L378-385 _private* method_ `void WriteFields()`
- L387-401 _private method_ `private Memory<byte> Allocate(int length)`
- L408 _protected method_ `protected abstract Memory<byte> AllocateChunk(int minSize)` — Allocates a chunk of data for storing CB fragments. This should be relatively coarse; the returned chunk will be reused for subsequent writes until full.
- L416-427 _public method_ `public Span<byte> WriteField(CbFieldType type, CbFieldName name, int size)` — Writes the header for a named field
- L429-481 _private* method_ `void WriteFieldHeader(CbFieldType type, Utf8String name)`
- L484-488 _public method_ `public void WriteReference(ReadOnlyMemory<byte> data)` — (inheritdoc)
- L495-501 _private* method_ `static void WriteBinaryPayload(Span<byte> output, ReadOnlySpan<byte> value)` — Writes the payload for a binary value
- L507-521 _public method_ `public int GetSize()` — Gets the size of the serialized data
- L527-530 _public method_ `public void CopyTo(Span<byte> buffer)` — Copy the data from this writer to a buffer
- L532-544 _private* method_ `static Span<byte> Copy(Scope scope, Span<byte> span)`
- L550-560 _public method_ `public IoHash ComputeHash()` — Computes the hash for this object
- L566-569 _public method_ `public CbObject ToObject()` — Convert the data into a compact binary object
- L575-580 _public method_ `public byte[] ToByteArray()` — Convert the data into a flat array
- L586-591 _public method_ `public List<ReadOnlyMemory<byte>> GetSegments()` — Enumerate all the segments in the data that has been written
- L593-603 _private* method_ `static void GetSegments(Scope scope, List<ReadOnlyMemory<byte>> segments)`
- L609 _public method_ `public Stream AsStream()` — Gets the contents of this writer as a stream

#### class `EpicGames.Serialization.CbWriterBase.Scope`  
`class Scope`  
_private*; L106-145_
- desc: Stores information about an object or array scope within the written buffer which requires a header to be inserted containing the size or number of elements when copied to an output buffer
- L108 _public field_ `public CbFieldType _fieldType`
- L109 _public field_ `public bool _writeFieldType`
- L110 _public field_ `public CbFieldType _uniformFieldType`
- L111 _public field_ `public Utf8String _name`
- L112 _public field_ `public int _itemCount`
- L113 _public field_ `public ReadOnlyMemory<byte> _data`
- L114 _public field_ `public int _length`
- L115 _public field_ `public Scope? _firstChild`
- L116 _public field_ `public Scope? _lastChild`
- L117 _public field_ `public Scope? _nextSibling`
- L119-131 _public method_ `public void Reset()`
- L133-144 _public method_ `public void AddChild(Scope child)`

#### class `EpicGames.Serialization.CbWriterBase.ReadStream`  
`class ReadStream(IEnumerator<ReadOnlyMemory<byte>> segments, long length) : Stream`  
_private*; L611-675_
- L613 _private* field_ `ReadOnlyMemory<byte> _segment`
- L614 _private* field_ `long _positionInternal`
- L617 _public property_ `public override bool CanRead => ...` — (inheritdoc)
- L620 _public property_ `public override bool CanSeek => ...` — (inheritdoc)
- L623 _public property_ `public override bool CanWrite => ...` — (inheritdoc)
- L626 _public property_ `public override long Length { get; }` — (inheritdoc)
- L629-633 _public property_ `public override long Position { get; set; }` — (inheritdoc)
- L636 _public method_ `public override void Flush()` — (inheritdoc)
- L639-662 _public method_ `public override int Read(Span<byte> buffer)` — (inheritdoc)
- L665 _public method_ `public override int Read(byte[] buffer, int offset, int count)` — (inheritdoc)
- L668 _public method_ `public override long Seek(long offset, SeekOrigin origin)` — (inheritdoc)
- L671 _public method_ `public override void SetLength(long value)` — (inheritdoc)
- L674 _public method_ `public override void Write(byte[] buffer, int offset, int count)` — (inheritdoc)

#### class `EpicGames.Serialization.CbWriter`  
`public class CbWriter : CbWriterBase`  
_public; L681-745_
- inherits: `CbWriterBase`
- desc: Forward-only writer for compact binary objects
- L686 _public const_ `public const int DefaultChunkSize = 1024` — Size of data to preallocate by default
- L688 _private* field_ `readonly List<byte[]> _chunks = []`
- L689 _private* field_ `readonly List<byte[]> _freeChunks = []`
- L694-696 _public ctor_ `public CbWriter()` — Constructor
- L702-705 _public ctor_ `public CbWriter(int reserve)` — Constructor
- L710-716 _public method_ `public void Clear()` — Clear the current contents of the writer
- L722-729 _public method_ `public void Reserve(int reserve)` — Ensures that the required space is available in a contiguous chunk
- L732-744 _protected method_ `protected override Memory<byte> AllocateChunk(int minSize)` — (inheritdoc)

#### class `EpicGames.Serialization.CbWriterExtensions`  
`public static class CbWriterExtensions`  
_public; L750-1187_
- desc: Extension methods for CbWriter
- L752 _private* method_ `static int MeasureFieldWithLength(int length)`
- L754-761 _private* method_ `static Span<byte> WriteFieldWithLength(this ICbWriter writer, CbFieldType type, CbFieldName name, int length)`
- L767 _public method_ `public static void BeginObject(this ICbWriter writer)` — Begin writing an object field
- L773 _public method_ `public static void BeginArray(this ICbWriter writer)` — Begin writing an array field
- L780 _public method_ `public static void BeginArray(this ICbWriter writer, CbFieldName name)` — Begin writing a named array field
- L787 _public method_ `public static void BeginUniformArray(this ICbWriter writer, CbFieldType fieldType)` — Begin writing a uniform array field
- L795 _public method_ `public static void BeginUniformArray(this ICbWriter writer, CbFieldName name, CbFieldType fieldType)` — Begin writing a named uniform array field
- L801 _public method_ `public static void EndUniformArray(this ICbWriter writer)` — End writing a uniform array field
- L808 _public method_ `public static void WriteFieldValue(this ICbWriter writer, CbField field)` — Copies an entire field value to the output
- L815 _public method_ `public static void WriteField(this ICbWriter writer, CbField field)` — Copies an entire field value to the output, using the name from the field
- L823-828 _public method_ `public static void WriteField(this ICbWriter writer, CbFieldName name, CbField field)` — Copies an entire field value to the output
- L834 _public method_ `public static void WriteNullValue(this ICbWriter writer)` — Write a null field
- L841 _public method_ `public static void WriteNull(this ICbWriter writer, CbFieldName name)` — Write a named null field
- L848 _public method_ `public static void WriteBoolValue(this ICbWriter writer, bool value)` — Writes a boolean value
- L856 _public method_ `public static void WriteBool(this ICbWriter writer, CbFieldName name, bool value)` — Writes a boolean value
- L863 _public method_ `public static void WriteIntegerValue(this ICbWriter writer, int value)` — Writes an unnamed integer field
- L870 _public method_ `public static void WriteIntegerValue(this ICbWriter writer, long value)` — Writes an unnamed integer field
- L878 _public method_ `public static void WriteInteger(this ICbWriter writer, CbFieldName name, int value)` — Writes an named integer field
- L886-900 _public method_ `public static void WriteInteger(this ICbWriter writer, CbFieldName name, long value)` — Writes an named integer field
- L907 _public method_ `public static void WriteIntegerValue(this ICbWriter writer, ulong value)` — Writes an unnamed integer field
- L915-920 _public method_ `public static void WriteInteger(this ICbWriter writer, CbFieldName name, ulong value)` — Writes a named integer field
- L927 _public method_ `public static void WriteDoubleValue(this ICbWriter writer, double value)` — Writes an unnamed double field
- L935-939 _public method_ `public static void WriteDouble(this ICbWriter writer, CbFieldName name, double value)` — Writes a named double field
- L946 _public method_ `public static void WriteDateTimeValue(this ICbWriter writer, DateTime value)` — Writes an unnamed DateTime field
- L954-958 _public method_ `public static void WriteDateTime(this ICbWriter writer, CbFieldName name, DateTime value)` — Writes a named DateTime field
- L965 _public method_ `public static void WriteHashValue(this ICbWriter writer, IoHash value)` — Writes an unnamed IoHash field
- L973-977 _public method_ `public static void WriteHash(this ICbWriter writer, CbFieldName name, IoHash value)` — Writes a named IoHash field
- L984 _public method_ `public static void WriteBinaryAttachmentValue(this ICbWriter writer, IoHash hash)` — Writes an unnamed reference to a binary attachment
- L992-996 _public method_ `public static void WriteBinaryAttachment(this ICbWriter writer, CbFieldName name, IoHash hash)` — Writes a named reference to a binary attachment
- L1003 _public method_ `public static void WriteObject(this ICbWriter writer, CbObject obj)` — Writes an object directly into the writer
- L1011-1016 _public method_ `public static void WriteObject(this ICbWriter writer, CbFieldName name, CbObject obj)` — Writes an object directly into the writer
- L1023 _public method_ `public static void WriteObjectAttachmentValue(this ICbWriter writer, IoHash hash)` — Writes an unnamed reference to an object attachment
- L1031-1035 _public method_ `public static void WriteObjectAttachment(this ICbWriter writer, CbFieldName name, IoHash hash)` — Writes a named reference to an object attachment
- L1044-1048 _public method_ `public static void WriteObjectId(this ICbWriter writer, CbFieldName name, CbObjectId objectId)` — Writes a named object id
- L1056-1060 _public method_ `public static void WriteObjectIdValue(this ICbWriter writer, CbObjectId objectId)` — Writes a unnamed object id
- L1067 _public method_ `public static void WriteStringValue(this ICbWriter writer, string value)` — Writes an unnamed string value
- L1075-1081 _public method_ `public static void WriteString(this ICbWriter writer, CbFieldName name, string? value)` — Writes a named string value
- L1088 _public method_ `public static void WriteUtf8StringValue(this ICbWriter writer, Utf8String value)` — Writes an unnamed string value
- L1096-1100 _public method_ `public static void WriteUtf8String(this ICbWriter writer, CbFieldName name, Utf8String value)` — Writes a named string value
- L1108-1112 _public method_ `public static void WriteUuid(this ICbWriter writer, CbFieldName name, Guid value)` — Writes a named uuid/guid value
- L1119-1123 _public method_ `public static void WriteUuidValue(this ICbWriter writer, Guid value)` — Writes a unnamed uuid/guid value
- L1131-1137 _public method_ `public static void WriteBinaryReference(this ICbWriter writer, CbFieldName name, ReadOnlyMemory<byte> data)` — Writes an external binary value into the output stream
- L1144 _public method_ `public static void WriteBinarySpanValue(this ICbWriter writer, ReadOnlySpan<byte> value)` — Writes an unnamed binary value
- L1152-1156 _public method_ `public static void WriteBinarySpan(this ICbWriter writer, CbFieldName name, ReadOnlySpan<byte> value)` — Writes a named binary value
- L1163 _public method_ `public static void WriteBinaryValue(this ICbWriter writer, ReadOnlyMemory<byte> value)` — Writes an unnamed binary value
- L1171 _public method_ `public static void WriteBinary(this ICbWriter writer, CbFieldName name, ReadOnlyMemory<byte> value)` — Writes a named binary value
- L1178 _public method_ `public static void WriteBinaryArrayValue(this ICbWriter writer, byte[] value)` — Writes an unnamed binary value
- L1186 _public method_ `public static void WriteBinaryArray(this ICbWriter writer, CbFieldName name, byte[] value)` — Writes a named binary value

### `Source/Programs/Shared/EpicGames.Serialization/CompressedBuffer.cs` (EpicGames.Serialization)


#### class `EpicGames.Serialization.CompressedBufferHeader`  
`public class CompressedBufferHeader`  
_public; L21-109_
- desc: Binary header for the Unreal compressed buffer format.
- L44 _public const_ `public const uint ExpectedMagic = 0xb7756362` — A sequence of four bytes identifying a byte-stream as an Unreal compressed buffer.
- L48 _public const_ `public const uint HeaderLength = 64` — The length of the binary header.
- L53 _public property_ `public uint Magic { get; set; }` — A magic number to identify a compressed buffer. Should always equal ExpectedMagic.
- L58 _public property_ `public uint Crc32 { get; set; }` — A CRC-32 used to check integrity of the buffer. Uses the polynomial 0x04c11db7.
- L63 _public property_ `public CompressionMethod Method { get; set; }` — The method used to compress the buffer. Affects layout of data following the header.
- L67 _public property_ `public byte CompressionLevel { get; set; }` — The numerical compression level of the data. See OodleCompressionLevel for values for Oodle-compressed data.
- L71 _public property_ `public byte CompressionMethodUsed { get; set; }` — For Oodle compression, represents the Oodle algorithm used (Mermaid, Selkie etc), see OodleCompressorType.
- L76 _public property_ `public byte BlockSizeExponent { get; set; }` — The power of two size of every uncompressed block except the last. Size is 1 binary-left-shifted by BlockSizeExponent.
- L81 _public property_ `public uint BlockCount { get; set; }` — The number of blocks that follow the header.
- L86 _public property_ `public ulong TotalRawSize { get; set; }` — The total size of the uncompressed data.
- L91 _public property_ `public ulong TotalCompressedSize { get; set; }` — The total size of the compressed data including the header.
- L96 _public property_ `public byte[] RawHash { get; set; }` — The hash of the uncompressed data.
- L101-108 _public method_ `public void ByteSwap()` — Swap endianness of the header if the running system is not big-endian.

#### enum `EpicGames.Serialization.CompressedBufferHeader.CompressionMethod`  
`public enum CompressionMethod : byte`  
_public; L27-39_
- attrs: `[System.Diagnostics.CodeAnalysis.SuppressMessage("Design", "CA1028:Enum Storage should be Int32", Justification = "Interop requires byte")]`
- inherits: `byte`
- desc: The type of compression for this buffer.
- L32 _public* enumerator_ `None = 0` — Header is followed by one uncompressed block.
- L36 _public* enumerator_ `Oodle = 3` — Header is followed by an array of compressed block sizes then the compressed blocks.

#### class `EpicGames.Serialization.CompressedBuffer`  
`public static class CompressedBuffer`  
_public; L114-464_
- desc: Utilities for working with compressed buffers
- L116-186 _private method_ `private static (CompressedBufferHeader, uint[]) ExtractHeader(BinaryReader br)`
- L188-217 _private method_ `private static void WriteHeader(CompressedBufferHeader header, BinaryWriter writer)`
- L228-271 _public method_ `public static async Task<CompressedBufferHeader> DecompressContentAsync(Stream sourceStream, ulong streamSize, Stream targetStream, CancellationToken cancellationToken = default)` — Decompress a compressed buffer into a stream
- L273-294 _private method_ `private static int DecompressPayload(ReadOnlySpan<byte> compressedPayload, CompressedBufferHeader header, ulong rawBlockSize, Stream target)`
- L304-321 _public method_ `public static IoHash CompressContent(Stream s, OodleCompressorType method, OodleCompressionLevel compressionLevel, byte[] rawContents)` — Compress a stream into a compressed buffer stream.
- L331-348 _public method_ `public static IoHash CompressContent(Stream s, OodleCompressorType method, OodleCompressionLevel compressionLevel, Stream sourceStream)` — Compress a stream into a compressed buffer stream.
- L360-423 _public method_ `public static IoHash CompressContent(Stream s, OodleCompressorType method, OodleCompressionLevel compressionLevel, List<byte[]> blocks, long blockSize)` — Compress a stream into a compressed buffer stream
- L425-463 _private method_ `private static byte[] WriteHeaderToBuffer(CompressedBufferHeader header, uint[] compressedBlockLengths)`

#### class `EpicGames.Serialization.InvalidHashException`  
`public class InvalidHashException(uint headerCrc32, uint calculatedCrc) : Exception($"Header specified crc \"{headerCrc32}\" but calculated hash was \"{calculatedCrc}\"")`  
_public; L471-471_
- desc: Thrown when the crc32 of the header does not align with the decompressed content, usually indicating that the full content was not present.

#### class `EpicGames.Serialization.InvalidMagicException`  
`public class InvalidMagicException(uint headerMagic, uint expectedMagic) : Exception($"Header magic \"{headerMagic}\" was incorrect, expected to be {expectedMagic}")`  
_public; L479-479_
- desc: Thrown when a byte buffer is encountered that is not a compressed buffer

### `Source/Programs/Shared/EpicGames.Serialization/Converters/CbArrayConverter.cs` (EpicGames.Serialization)


#### class `EpicGames.Serialization.Converters.CbArrayConverter`  
`class CbArrayConverter<T> : CbConverter<T[]>`  
_internal*; L12-65_
- inherits: `CbConverter<T[]>`
- desc: Converter for array types
- L15-28 _public method_ `public override T[] Read(CbField field)` — (inheritdoc)
- L31-46 _public method_ `public override void Write(CbWriter writer, T[] list)` — (inheritdoc)
- L49-64 _public method_ `public override void WriteNamed(CbWriter writer, CbFieldName name, T[] array)` — (inheritdoc)

#### class `EpicGames.Serialization.Converters.CbArrayConverterFactory`  
`class CbArrayConverterFactory : CbConverterFactory`  
_internal*; L70-83_
- inherits: `CbConverterFactory`
- desc: Factory for CbListConverter
- L73-82 _public method_ `public override CbConverter? CreateConverter(Type type)` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.Serialization/Converters/CbClassConverter.cs` (EpicGames.Serialization)


#### class `EpicGames.Serialization.Converters.CbClassConverterMethods`  
`class CbClassConverterMethods`  
_internal*; L14-498_
- L27 _private* field_ `static readonly Utf8String s_discriminatorKey = new("_t")`
- L29 _public property_ `public Type ClassType { get; }`
- L30 _public property_ `public bool IsPolymorphic { get; }`
- L32 _public property_ `public DynamicMethod ReadMethod { get; }`
- L33 _public property_ `public DynamicMethod WriteMethod { get; }`
- L34 _public property_ `public DynamicMethod WriteNamedMethod { get; }`
- L36 _public property_ `public DynamicMethod WriteContentsMethod { get; }`
- L38 _public property_ `public DynamicMethod ReadConcreteMethod { get; }`
- L39 _public property_ `public DynamicMethod WriteConcreteContentsMethod { get; }`
- L41 _private* field_ `static readonly Dictionary<Type, CbClassConverterMethods> s_typeToMethods = ...`
- L41 _private* field_ `static readonly Dictionary< s_typeToMethods = []`
- L43-53 _public method_ `public static CbClassConverterMethods Create(Type classType)`
- L55-76 _private ctor_ `private CbClassConverterMethods(Type classType)`
- L78-113 _private method_ `private void GenerateBytecode()`
- L115-164 _private* method_ `static void PopulateDispatchType(Type classType, Type dispatchType)`
- L166-185 _private* method_ `static void CreateObjectWriter(ILGenerator generator, DynamicMethod contentsWriter)`
- L187-207 _private* method_ `static void CreateNamedObjectWriter(ILGenerator generator, DynamicMethod contentsWriter)`
- L209-275 _private* method_ `static void CreateConcreteObjectContentsWriter(Type type, ILGenerator generator)`
- L295-298 _private* method_ `static T CreateDelegate<T>(DynamicMethod method) where T : Delegate`
- L300-435 _private* method_ `static void CreateConcreteObjectReader(Type type, ILGenerator generator)`
- L437-451 _private* method_ `static bool TryGetCollectionCopyMethod(Type type, [NotNullWhen(true)] out MethodInfo? method)`
- L453-459 _private* method_ `static void CopyCollection<TCollection, TElement>(TCollection source, TCollection target) where TCollection : ICollection<TElement>`
- L461-482 _private* method_ `static (Utf8String, PropertyInfo)[] GetProperties(Type type)`
- L484-487 _private* method_ `static FieldInfo GetFieldInfo<T>(Expression<Func<T>> expr)`
- L489-492 _private* method_ `static MethodInfo GetMethodInfo(Expression<Action> expr)`
- L494-497 _private* method_ `static MethodInfo GetMethodInfo<T>(Expression<Action<T>> expr)`

#### class `EpicGames.Serialization.Converters.CbClassConverterMethods.CbReflectedTypeInfo`  
`class CbReflectedTypeInfo<T> where T : class`  
_private*; L16-25_
- constraints: `where T : class`
- L18 _public field_ `public static Utf8String[]? Names = null`
- L19 _public field_ `public static PropertyInfo[]? Properties = null`
- L21-24 _public method_ `public static bool MatchName(CbField field, int idx)`

#### class `EpicGames.Serialization.Converters.CbClassConverterMethods.CbPolymorphicDispatch`  
`class CbPolymorphicDispatch<T>`  
_private*; L277-293_
- L279 _public field_ `public static Dictionary<Utf8String, Func<CbField, object>> NameToReadFunc = ...`
- L279 _public field_ `public static Dictionary< CbField`
- L279 _public field_ `public static Dictionary< NameToReadFunc = []`
- L280 _public field_ `public static Dictionary<Type, Action<CbWriter, object>> TypeToWriteContentsFunc = ...`
- L280 _public field_ `public static Dictionary< CbWriter`
- L280 _public field_ `public static Dictionary< TypeToWriteContentsFunc = []`
- L282-286 _public method_ `public static object Read(CbField field)`
- L288-292 _public method_ `public static void WriteContents(CbWriter writer, object value)`

#### class `EpicGames.Serialization.Converters.CbClassConverter`  
`class CbClassConverter<T> : CbConverter<T>, ICbConverterMethods where T : class`  
_internal*; L500-530_
- inherits: `CbConverter<T>, ICbConverterMethods`
- constraints: `where T : class`
- L502 _private* field_ `readonly CbClassConverterMethods _methods`
- L504 _private* field_ `readonly Func<CbField, T> _readFunc`
- L504 _private* field_ `readonly Func< _readFunc`
- L505 _private* field_ `readonly Action<CbWriter, T> _writeFunc`
- L505 _private* field_ `readonly Action< _writeFunc`
- L506 _private* field_ `readonly Action<CbWriter, CbFieldName, T> _writeNamedFunc`
- L506 _private* field_ `readonly Action< CbFieldName`
- L506 _private* field_ `readonly Action< _writeNamedFunc`
- L508-515 _public ctor_ `public CbClassConverter()`
- L517 _public property_ `public MethodInfo ReadMethod => ...`
- L519 _public property_ `public MethodInfo WriteMethod => ...`
- L521 _public property_ `public MethodInfo WriteNamedMethod => ...`
- L523 _private* method_ `static TDelegate CreateDelegate<TDelegate>(DynamicMethod method) where TDelegate : Delegate`
- L525 _public method_ `public override T Read(CbField field)`
- L527 _public method_ `public override void Write(CbWriter writer, T value)`
- L529 _public method_ `public override void WriteNamed(CbWriter writer, CbFieldName name, T value)`

#### class `EpicGames.Serialization.Converters.CbClassConverterFactory`  
`class CbClassConverterFactory : CbConverterFactory`  
_internal*; L532-551_
- inherits: `CbConverterFactory`
- L534-550 _public method_ `public override CbConverter? CreateConverter(Type type)`

### `Source/Programs/Shared/EpicGames.Serialization/Converters/CbDictionaryConverter.cs` (EpicGames.Serialization)


#### class `EpicGames.Serialization.Converters.CbDictionaryConverter`  
`class CbDictionaryConverter<TKey, TValue> : CbConverter<Dictionary<TKey, TValue>> where TKey : notnull`  
_internal*; L12-85_
- inherits: `CbConverter<Dictionary<TKey, TValue>>`
- constraints: `where TKey : notnull`
- desc: Converter for dictionary types
- L15-42 _public method_ `public override Dictionary<TKey, TValue> Read(CbField field)` — (inheritdoc)
- L45-63 _public method_ `public override void Write(CbWriter writer, Dictionary<TKey, TValue> value)` — (inheritdoc)
- L66-84 _public method_ `public override void WriteNamed(CbWriter writer, CbFieldName name, Dictionary<TKey, TValue> value)` — (inheritdoc)

#### class `EpicGames.Serialization.Converters.CbDictionaryConverterFactory`  
`class CbDictionaryConverterFactory : CbConverterFactory`  
_internal*; L90-112_
- inherits: `CbConverterFactory`
- desc: Factory for CbDictionaryConverter
- L93-111 _public method_ `public override CbConverter? CreateConverter(Type type)` — (inheritdoc)

#### class `EpicGames.Serialization.Converters.CbStringDictionaryConverter`  
`class CbStringDictionaryConverter<TValue> : CbConverter<Dictionary<string, TValue>>`  
_internal*; L117-174_
- inherits: `CbConverter<Dictionary<string, TValue>>`
- desc: Converter for dictionary types with string keys, serialized as objects
- L120-137 _public method_ `public override Dictionary<string, TValue> Read(CbField field)` — (inheritdoc)
- L140-155 _public method_ `public override void Write(CbWriter writer, Dictionary<string, TValue> value)` — (inheritdoc)
- L158-173 _public method_ `public override void WriteNamed(CbWriter writer, CbFieldName name, Dictionary<string, TValue> value)` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.Serialization/Converters/CbEnumConverter.cs` (EpicGames.Serialization)


#### class `EpicGames.Serialization.Converters.CbEnumConverter`  
`class CbEnumConverter<T> : CbConverter<T>, ICbConverterMethods where T : Enum`  
_internal*; L10-92_
- inherits: `CbConverter<T>, ICbConverterMethods`
- constraints: `where T : Enum`
- L12 _private* field_ `readonly Func<CbField, T> _readFunc`
- L12 _private* field_ `readonly Func< _readFunc`
- L13 _private* field_ `readonly Action<CbWriter, T> _writeFunc`
- L13 _private* field_ `readonly Action< _writeFunc`
- L14 _private* field_ `readonly Action<CbWriter, CbFieldName, T> _writeNamedFunc`
- L14 _private* field_ `readonly Action< CbFieldName`
- L14 _private* field_ `readonly Action< _writeNamedFunc`
- L16-31 _public ctor_ `public CbEnumConverter()`
- L33 _public property_ `public DynamicMethod ReadMethod { get; }`
- L34 _private* property_ `MethodInfo ICbConverterMethods.ReadMethod => ...`
- L36 _public property_ `public DynamicMethod WriteMethod { get; }`
- L37 _private* property_ `MethodInfo ICbConverterMethods.WriteMethod => ...`
- L39 _public property_ `public DynamicMethod WriteNamedMethod { get; }`
- L40 _private* property_ `MethodInfo ICbConverterMethods.WriteNamedMethod => ...`
- L42 _public method_ `public override T Read(CbField field)`
- L44 _public method_ `public override void Write(CbWriter writer, T value)`
- L46 _public method_ `public override void WriteNamed(CbWriter writer, CbFieldName name, T value)`
- L48-53 _private* method_ `static void CreateEnumReader(ILGenerator generator)`
- L55-69 _private* method_ `static void CreateEnumWriter(ILGenerator generator)`
- L71-86 _private* method_ `static void CreateNamedEnumWriter(ILGenerator generator)`
- L88-91 _private* method_ `static MethodInfo GetMethodInfo<TArg>(Expression<Action<TArg>> expr)`

#### class `EpicGames.Serialization.Converters.CbEnumConverterFactory`  
`class CbEnumConverterFactory : CbConverterFactory`  
_internal*; L94-106_
- inherits: `CbConverterFactory`
- L96-105 _public method_ `public override CbConverter? CreateConverter(Type type)`

### `Source/Programs/Shared/EpicGames.Serialization/Converters/CbFieldConverter.cs` (EpicGames.Serialization)


#### class `EpicGames.Serialization.Converters.CbFieldConverter`  
`class CbFieldConverter : CbConverter<CbField>`  
_internal*; L8-27_
- inherits: `CbConverter<CbField>`
- desc: Converter for raw CbField types
- L11-14 _public method_ `public override CbField Read(CbField field)` — (inheritdoc)
- L17-20 _public method_ `public override void Write(CbWriter writer, CbField field)` — (inheritdoc)
- L23-26 _public method_ `public override void WriteNamed(CbWriter writer, CbFieldName name, CbField value)` — (inheritdoc)

#### class `EpicGames.Serialization.Converters.CbObjectConverter`  
`class CbObjectConverter : CbConverter<CbObject>`  
_internal*; L32-51_
- inherits: `CbConverter<CbObject>`
- desc: Converter for raw CbObject types
- L35-38 _public method_ `public override CbObject Read(CbField field)` — (inheritdoc)
- L41-44 _public method_ `public override void Write(CbWriter writer, CbObject obj)` — (inheritdoc)
- L47-50 _public method_ `public override void WriteNamed(CbWriter writer, CbFieldName name, CbObject obj)` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.Serialization/Converters/CbListConverter.cs` (EpicGames.Serialization)


#### class `EpicGames.Serialization.Converters.CbListConverter`  
`class CbListConverter<T> : CbConverter<List<T>>`  
_internal*; L13-68_
- inherits: `CbConverter<List<T>>`
- desc: Converter for list types
- L16-31 _public method_ `public override List<T> Read(CbField field)` — (inheritdoc)
- L34-49 _public method_ `public override void Write(CbWriter writer, List<T> list)` — (inheritdoc)
- L52-67 _public method_ `public override void WriteNamed(CbWriter writer, CbFieldName name, List<T> list)` — (inheritdoc)

#### class `EpicGames.Serialization.Converters.CbUniformObjectListConverter`  
`public class CbUniformObjectListConverter<T> : CbConverter<List<T>>`  
_public; L74-129_
- inherits: `CbConverter<List<T>>`
- desc: Specialization that writes a list as a uniform array of objects - a more efficient representation if you know the elements are always of the same type
- L77-92 _public method_ `public override List<T> Read(CbField field)` — (inheritdoc)
- L95-110 _public method_ `public override void Write(CbWriter writer, List<T> list)` — (inheritdoc)
- L113-128 _public method_ `public override void WriteNamed(CbWriter writer, CbFieldName name, List<T> list)` — (inheritdoc)

#### class `EpicGames.Serialization.Converters.CbStringListConverter`  
`sealed class CbStringListConverter : CbConverter<List<Utf8String>>`  
_internal*; L134-171_
- inherits: `CbConverter<List<Utf8String>>`
- desc: Specialization for serializing string lists
- L137-145 _public method_ `public override List<Utf8String> Read(CbField field)` — (inheritdoc)
- L148-156 _public method_ `public override void Write(CbWriter writer, List<Utf8String> list)` — (inheritdoc)
- L159-170 _public method_ `public override void WriteNamed(CbWriter writer, CbFieldName name, List<Utf8String> list)` — (inheritdoc)

#### class `EpicGames.Serialization.Converters.CbListConverterFactory`  
`class CbListConverterFactory : CbConverterFactory`  
_internal*; L176-195_
- inherits: `CbConverterFactory`
- desc: Factory for CbListConverter
- L179-194 _public method_ `public override CbConverter? CreateConverter(Type type)` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.Serialization/Converters/CbNullableConverter.cs` (EpicGames.Serialization)


#### class `EpicGames.Serialization.Converters.CbNullableConverter`  
`class CbNullableConverter<T> : CbConverter<Nullable<T>> where T : struct`  
_internal*; L11-36_
- inherits: `CbConverter<Nullable<T>>`
- constraints: `where T : struct`
- desc: Converter for list types
- L14-17 _public method_ `public override T? Read(CbField field)` — (inheritdoc)
- L20-26 _public method_ `public override void Write(CbWriter writer, T? nullable)` — (inheritdoc)
- L29-35 _public method_ `public override void WriteNamed(CbWriter writer, CbFieldName name, T? nullable)` — (inheritdoc)

#### class `EpicGames.Serialization.Converters.CbNullableConverterFactory`  
`class CbNullableConverterFactory : CbConverterFactory`  
_internal*; L41-53_
- inherits: `CbConverterFactory`
- desc: Factory for CbNullableConverter
- L44-52 _public method_ `public override CbConverter? CreateConverter(Type type)` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.Serialization/Converters/CbPrimitiveConverter.cs` (EpicGames.Serialization)


#### class `EpicGames.Serialization.Converters.CbPrimitiveConverter`  
`class CbPrimitiveConverter<T>(Expression<Func<CbField, T>> read, Expression<Action<CbWriter, T>> write, Expression<Action<CbWriter, CbFieldName, T>> writeNamed) : CbConverter<T>, ICbConverterMethods`  
_internal*; L9-25_
- L11 _public property_ `public MethodInfo ReadMethod { get; }`
- L12 _public property_ `public Func<CbField, T> ReadFunc { get; }`
- L14 _public property_ `public MethodInfo WriteMethod { get; }`
- L15 _public property_ `public Action<CbWriter, T> WriteFunc { get; }`
- L17 _public property_ `public MethodInfo WriteNamedMethod { get; }`
- L18 _public property_ `public Action<CbWriter, CbFieldName, T> WriteNamedFunc { get; }`
- L20 _public method_ `public override T Read(CbField field)`
- L22 _public method_ `public override void Write(CbWriter writer, T value)`
- L24 _public method_ `public override void WriteNamed(CbWriter writer, CbFieldName name, T value)`

### `Source/Programs/Shared/EpicGames.Serialization/Converters/CbStringConverter.cs` (EpicGames.Serialization)


#### class `EpicGames.Serialization.Converters.CbStringConverter`  
`class CbStringConverter<T>(TypeConverter typeConverter) : CbConverter<T>`  
_internal*; L8-24_
- L10-13 _public method_ `public override T Read(CbField field)`
- L15-18 _public method_ `public override void WriteNamed(CbWriter writer, CbFieldName name, T value)`
- L20-23 _public method_ `public override void Write(CbWriter writer, T value)`

#### class `EpicGames.Serialization.Converters.CbStringConverterFactory`  
`class CbStringConverterFactory : CbConverterFactory`  
_internal*; L26-39_
- inherits: `CbConverterFactory`
- L28-38 _public method_ `public override CbConverter? CreateConverter(Type type)`

### `Source/Programs/Shared/EpicGames.Serialization/HttpExtensions.cs` (EpicGames.Serialization)


#### class `EpicGames.Serialization.HttpExtensions`  
`public static class HttpExtensions`  
_public; L13-27_
- desc: Extension methods for System.Net.Http
- L21-26 _public method_ `public static async Task<T> ReadAsCompactBinaryAsync<T>(this HttpContent content)` — Read content using CbSerializer, make sure the type T is correctly annotated to deserialize Compact Binary
