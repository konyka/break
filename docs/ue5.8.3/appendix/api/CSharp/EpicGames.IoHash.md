# CSharp / EpicGames.IoHash

- project root: `Source/Programs/Shared/EpicGames.IoHash`
- files: 2; symbols: 79
- symbol kinds: class=4, const=5, ctor=2, field=3, method=45, operator=14, property=4, struct=2
- access marked `*` is implicit (not written in source)

### `Source/Programs/Shared/EpicGames.IoHash/Blake3Hash.cs` (EpicGames.IoHash)


#### struct `EpicGames.Core.Blake3Hash`  
`public readonly struct Blake3Hash : IEquatable<Blake3Hash>, IComparable<Blake3Hash>`  
_public; L15-206_
- inherits: `IEquatable<Blake3Hash>, IComparable<Blake3Hash>`
- desc: Struct representing a strongly typed Blake3 hash value (a 32-byte Blake3 hash).
- L20 _public const_ `public const int NumBytes = 32` — Length of an Blake3Hash
- L25 _public const_ `public const int NumBits = NumBytes * 8` — Length of the hash in bits
- L30 _public property_ `public ReadOnlyMemory<byte> Memory { get; }` — Memory storing the digest data
- L35 _public property_ `public ReadOnlySpan<byte> Span => ...` — Span for the underlying memory
- L40 _public property_ `public static Blake3Hash Zero { get; }` — Hash consisting of zeroes
- L46-54 _public ctor_ `public Blake3Hash(ReadOnlyMemory<byte> memory)` — Constructor
- L61-66 _public method_ `public static Blake3Hash Compute(ReadOnlySpan<byte> data)` — Creates a content hash for a block of data.
- L73-91 _public method_ `public static IoHash Compute(ReadOnlySequence<byte> sequence)` — Creates a content hash for a block of data.
- L98-113 _public method_ `public static IoHash Compute(Stream stream)` — Creates a content hash for a stream.
- L121-136 _public method_ `public static async Task<IoHash> ComputeAsync(Stream stream, CancellationToken cancellationToken = default)` — Creates a content hash for a stream asynchronously.
- L143-146 _public method_ `public static Blake3Hash Parse(string text)` — Parses a digest from the given hex string
- L149-163 _public method_ `public int CompareTo(Blake3Hash other)` — (inheritdoc)
- L166 _public method_ `public bool Equals(Blake3Hash other)` — (inheritdoc)
- L169 _public method_ `public override bool Equals(object? obj)` — (inheritdoc)
- L172 _public method_ `public override int GetHashCode()` — (inheritdoc)
- L175 _public method_ `public override string ToString()` — (inheritdoc)
- L180 _public operator_ `public static bool operator ==(Blake3Hash a, Blake3Hash b)` — Test two hash values for equality
- L185 _public operator_ `public static bool operator !=(Blake3Hash a, Blake3Hash b)` — Test two hash values for equality
- L190 _public operator_ `public static bool operator >(Blake3Hash a, Blake3Hash b)` — Tests whether A > B
- L195 _public operator_ `public static bool operator <(Blake3Hash a, Blake3Hash b)` — Tests whether A is less than B
- L200 _public operator_ `public static bool operator >=(Blake3Hash a, Blake3Hash b)` — Tests whether A is greater than or equal to B
- L205 _public operator_ `public static bool operator <=(Blake3Hash a, Blake3Hash b)` — Tests whether A is less than or equal to B

#### class `EpicGames.Core.Blake3HashExtensions`  
`public static class Blake3HashExtensions`  
_public; L211-232_
- desc: Extension methods for dealing with Blake3Hash values
- L218-221 _public method_ `public static Blake3Hash ReadBlake3Hash(this MemoryReader reader)` — Read an Blake3Hash from a memory reader
- L228-231 _public method_ `public static void WriteBlake3Hash(this MemoryWriter writer, Blake3Hash hash)` — Write an Blake3Hash to a memory writer

### `Source/Programs/Shared/EpicGames.IoHash/IoHash.cs` (EpicGames.IoHash)


#### struct `EpicGames.Core.IoHash`  
`public readonly struct IoHash(ulong a, ulong b, uint c) : IEquatable<IoHash>, IComparable<IoHash>`  
_public; L23-420_
- attrs: `[JsonConverter(typeof(IoHashJsonConverter))] [TypeConverter(typeof(IoHashTypeConverter))]`
- desc: Struct representing a strongly typed IoHash value (a 20-byte Blake3 hash).
- L28 _public const_ `public const int NumBytes = 20` — Length of an IoHash
- L33 _public const_ `public const int NumBits = NumBytes * 8` — Length of the hash in bits
- L43 _private* const_ `const int MultiThreadedSize = 1024 * 1024` — Threshold size at which to use multiple threads for hashing
- L45 _private* field_ `readonly ulong _a = a`
- L46 _private* field_ `readonly ulong _b = b`
- L47 _private* field_ `readonly uint _c = c`
- L52 _public property_ `public static IoHash Zero { get; }` — Hash consisting of zeroes
- L58-61 _public ctor_ `public IoHash(ReadOnlySpan<byte> span) : this(BinaryPrimitives.ReadUInt64BigEndian(span), BinaryPrimitives.ReadUInt64BigEndian(span.Slice(8)), BinaryPrimitives.ReadUInt32BigEndian(span.Slice(16)))` — Constructor
- L67-72 _public method_ `public static IoHash FromBlake3(Blake3.Hasher hasher)` — Construct
- L79 _public method_ `public static IoHash Compute(ReadOnlySpan<byte> data)` — Creates the IoHash for a block of data.
- L87-99 _public method_ `public static IoHash Compute<T>(ReadOnlySpan<T> data) where T : unmanaged` — Creates the IoHash for a block of data.
- L106 _public method_ `public static IoHash Compute(ReadOnlySequence<byte> sequence)` — Creates the IoHash for a sequence of data.
- L114-135 _public method_ `public static IoHash Compute<T>(ReadOnlySequence<T> sequence) where T : unmanaged` — Creates the IoHash for a sequence of data.
- L143 _public method_ `public static IoHash Compute(string data, Encoding encoding)` — Creates the IoHash for a string with a given encoding
- L150 _public method_ `public static IoHash Compute(string data)` — Creates the IoHash for a string with the default encoding
- L157-182 _public method_ `public static IoHash Compute(Stream stream)` — Creates the IoHash for a stream.
- L190 _public method_ `public static async Task<IoHash> ComputeAsync(Stream stream, CancellationToken cancellationToken = default)` — Creates the IoHash for a stream asynchronously.
- L199-219 _public method_ `public static async Task<IoHash> ComputeAsync(Stream stream, long fileSizeHint, CancellationToken cancellationToken = default)` — Creates the IoHash for a stream asynchronously.
- L226 _public method_ `public static IoHash Parse(string text)` — Parses a digest from the given hex string
- L233 _public method_ `public static IoHash Parse(ReadOnlySpan<char> text)` — Parses a digest from the given hex string
- L240 _public method_ `public static IoHash Parse(ReadOnlySpan<byte> text)` — Parses a digest from the given hex string
- L248-261 _public method_ `public static bool TryParse(ReadOnlySpan<char> text, out IoHash hash)` — Parses a digest from the given hex string
- L269-282 _public method_ `public static bool TryParse(ReadOnlySpan<byte> text, out IoHash hash)` — Parses a digest from the given hex string
- L285-299 _public method_ `public int CompareTo(IoHash other)` — (inheritdoc)
- L302 _public method_ `public bool Equals(IoHash other)` — (inheritdoc)
- L305 _public method_ `public override bool Equals(object? obj)` — (inheritdoc)
- L308 _public method_ `public override int GetHashCode()` — (inheritdoc)
- L313-318 _public method_ `public Utf8String ToUtf8String()` — Format the hash as a utf8 string
- L324-329 _public method_ `public void ToUtf8String(Span<byte> chars)` — Formats the hash as a utf8 string
- L332-337 _public method_ `public override string ToString()` — (inheritdoc)
- L343-348 _public method_ `public byte[] ToByteArray()` — Convert this hash to a byte array
- L354-359 _public method_ `public void CopyTo(Span<byte> span)` — Copies this hash into a span
- L368-377 _public method_ `public static IoHash Combine(IoHash first, IoHash second)` — Combine two hashes into a new hash
- L382 _public operator_ `public static bool operator ==(IoHash a, IoHash b)` — Test two hash values for equality
- L387 _public operator_ `public static bool operator !=(IoHash a, IoHash b)` — Test two hash values for equality
- L392 _public operator_ `public static bool operator >(IoHash a, IoHash b)` — Tests whether A > B
- L397 _public operator_ `public static bool operator <(IoHash a, IoHash b)` — Tests whether A is less than B
- L402 _public operator_ `public static bool operator >=(IoHash a, IoHash b)` — Tests whether A is greater than or equal to B
- L407 _public operator_ `public static bool operator <=(IoHash a, IoHash b)` — Tests whether A is less than or equal to B
- L413 _public operator_ `public static implicit operator IoHash(Blake3Hash hash)` — Convert a Blake3Hash to an IoHash
- L419 _public operator_ `public static explicit operator uint(IoHash hash)` — Convert an IoHash to a uint by returning the first 32 bits of the hashed value

#### class `EpicGames.Core.IoHashExtensions`  
`public static class IoHashExtensions`  
_public; L425-462_
- desc: Extension methods for dealing with IoHash values
- L432-436 _public method_ `public static IoHash? ReadIoHash(this BinaryArchiveReader reader)` — Read an IoHash from a binary archive
- L443 _public method_ `public static IoHash ReadIoHash(this IMemoryReader reader)` — Read an IoHash from a memory reader
- L450 _public method_ `public static void WriteIoHash(this BinaryArchiveWriter writer, IoHash? hash)` — Write an IoHash to a binary archive
- L457-461 _public method_ `public static void WriteIoHash(this IMemoryWriter writer, IoHash hash)` — Write an IoHash to a memory writer

#### class `EpicGames.Core.IoHashJsonConverter`  
`sealed class IoHashJsonConverter : JsonConverter<IoHash>`  
_internal*; L467-474_
- inherits: `JsonConverter<IoHash>`
- desc: Type converter for IoHash to and from JSON
- L470 _public method_ `public override IoHash Read(ref Utf8JsonReader reader, Type typeToConvert, JsonSerializerOptions options)` — (inheritdoc)
- L473 _public method_ `public override void Write(Utf8JsonWriter writer, IoHash value, JsonSerializerOptions options)` — (inheritdoc)

#### class `EpicGames.Core.IoHashTypeConverter`  
`sealed class IoHashTypeConverter : TypeConverter`  
_internal*; L479-486_
- inherits: `TypeConverter`
- desc: Type converter from strings to IoHash objects
- L482 _public method_ `public override bool CanConvertFrom(ITypeDescriptorContext? context, Type sourceType)` — (inheritdoc)
- L485 _public method_ `public override object ConvertFrom(ITypeDescriptorContext? context, CultureInfo? culture, object value)` — (inheritdoc)
