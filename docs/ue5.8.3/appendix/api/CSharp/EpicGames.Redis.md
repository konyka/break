# CSharp / EpicGames.Redis

- project root: `Source/Programs/Shared/EpicGames.Redis`
- files: 21; symbols: 465
- symbol kinds: class=35, ctor=21, field=38, interface=2, method=321, operator=19, property=13, record=1, record struct=12, struct=3
- access marked `*` is implicit (not written in source)

### `Source/Programs/Shared/EpicGames.Redis/Converters/RedisClassConverter.cs` (EpicGames.Redis)


#### class `EpicGames.Redis.Converters.RedisClassConverter`  
`public class RedisClassConverter<T> : IRedisConverter<T>`  
_public; L16-176_
- inherits: `IRedisConverter<T>`
- desc: Converter for records to Redis values.
- L18 _private* field_ `readonly PropertyInfo[] _properties`
- L19 _private* field_ `readonly Func<Utf8String, object?>[] _typeReaders`
- L19 _private* field_ `readonly Func< _typeReaders`
- L20 _private* field_ `readonly Action<object?, Utf8StringBuilder>[] _typeWriters`
- L20 _private* field_ `readonly Action< _typeWriters`
- L21 _private* field_ `readonly ConstructorInfo _constructor`
- L26-64 _public ctor_ `public RedisClassConverter()` — Constructor
- L66-70 _private* method_ `static bool TryGetUtf8StringTypeConverter(Type propertyType, [NotNullWhen(true)] out TypeConverter? converter)`
- L72-76 _private* method_ `static bool TryGetStringTypeConverter(Type propertyType, [NotNullWhen(true)] out TypeConverter? converter)`
- L78-112 _private* method_ `static Utf8String ReadEscapedString(byte[] data, ref int idx)`
- L114-130 _private* method_ `static void WriteEscapedString(Utf8String str, Utf8StringBuilder builder)`
- L132-136 _private* method_ `void AppendProperty(T value, int propertyIdx, Utf8StringBuilder builder)`
- L139-152 _public method_ `public RedisValue ToRedisValue(T value)` — (inheritdoc)
- L155 _public method_ `public T FromRedisValue(RedisValue value)` — (inheritdoc)
- L157-175 _private* method_ `T FromBytes(byte[]? data)`

### `Source/Programs/Shared/EpicGames.Redis/Converters/RedisProtobufConverter.cs` (EpicGames.Redis)


#### class `EpicGames.Redis.Converters.RedisProtobufConverter`  
`public class RedisProtobufConverter<T> : IRedisConverter<T> where T : IMessage<T>, new()`  
_public; L16-39_
- inherits: `IRedisConverter<T>`
- constraints: `where T : IMessage<T>, new()`
- desc: Converter for records to Redis values using protobuf serialization.
- L18 _private* field_ `readonly MessageDescriptor _descriptor`
- L23-26 _public ctor_ `public RedisProtobufConverter()` — Constructor
- L29-32 _public method_ `public T FromRedisValue(RedisValue value)` — (inheritdoc)
- L35-38 _public method_ `public RedisValue ToRedisValue(T value)` — (inheritdoc)

#### class `EpicGames.Redis.Converters.RedisProtobufNetConverter`  
`public class RedisProtobufNetConverter<T> : IRedisConverter<T>`  
_public; L45-66_
- inherits: `IRedisConverter<T>`
- desc: Converter for records to Redis values using ProtoBuf-Net annotations.
- L48-55 _public method_ `public RedisValue ToRedisValue(T value)` — (inheritdoc)
- L58-65 _public method_ `public T FromRedisValue(RedisValue value)` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.Redis/IRedisTypedKey.cs` (EpicGames.Redis)


#### interface `EpicGames.Redis.IRedisTypedKey`  
`public interface IRedisTypedKey`  
_public; L14-20_
- desc: Interface for typed redis keys
- L19 _public property_ `public RedisKey Inner { get; }` — The inner untyped key

#### class `EpicGames.Redis.RedisTypedKeyExtensions`  
`public static class RedisTypedKeyExtensions`  
_public; L25-74_
- desc: Extension methods for IRedisTypedKey
- L30 _public method_ `public static Condition KeyExists(this IRedisTypedKey key)` — (inheritdoc)
- L34 _public method_ `public static Condition KeyNotExists(this IRedisTypedKey key)` — (inheritdoc)
- L42 _public method_ `public static Task KeyDeleteAsync(this IDatabaseAsync target, IRedisTypedKey key, CommandFlags flags = CommandFlags.None)` — (inheritdoc)
- L46 _public method_ `public static Task KeyDeleteAsync(this IDatabaseAsync target, IRedisTypedKey[] keys, CommandFlags flags = CommandFlags.None)` — (inheritdoc)
- L54 _public method_ `public static Task<bool> KeyExistsAsync(this IDatabaseAsync target, IRedisTypedKey key, CommandFlags flags = CommandFlags.None)` — (inheritdoc)
- L58 _public method_ `public static Task<long> KeyExistsAsync(this IDatabaseAsync target, IEnumerable<IRedisTypedKey> keys, CommandFlags flags = CommandFlags.None)` — (inheritdoc)
- L66 _public method_ `public static Task KeyExpireAsync(this IDatabaseAsync target, IRedisTypedKey key, DateTime? expiry = null, ExpireWhen when = ExpireWhen.Always, CommandFlags flags = CommandFlags.None)` — (inheritdoc)
- L70 _public method_ `public static Task KeyExpireAsync(this IDatabaseAsync target, IRedisTypedKey key, TimeSpan? expiry, ExpireWhen when = ExpireWhen.Always, CommandFlags flags = CommandFlags.None)` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.Redis/RedisChannel.cs` (EpicGames.Redis)


#### struct `EpicGames.Redis.RedisChannel`  
`public readonly struct RedisChannel<T> : IEquatable<RedisChannel<T>>`  
_public; L14-80_
- inherits: `IEquatable<RedisChannel<T>>`
- desc: Represents a typed pub/sub channel with a particular value
- L19 _public property_ `public readonly RedisChannel Channel { get; }` — The key for the list
- L25 _public ctor_ `public RedisChannel(RedisChannel channel)` — Constructor
- L32 _public ctor_ `public RedisChannel(Utf8String value, RedisChannel.PatternMode mode)` — Constructor
- L39 _public ctor_ `public RedisChannel(string value, RedisChannel.PatternMode mode)` — Constructor
- L46 _public ctor_ `public RedisChannel(byte[] value, RedisChannel.PatternMode mode)` — Constructor
- L49 _public method_ `public override bool Equals(object? obj)` — (inheritdoc)
- L52 _public method_ `public bool Equals(RedisChannel<T> other)` — (inheritdoc)
- L55 _public method_ `public override int GetHashCode()` — (inheritdoc)
- L58 _public operator_ `public static bool operator ==(RedisChannel<T> left, RedisChannel<T> right)` — Compares two instances for equality
- L61 _public operator_ `public static bool operator !=(RedisChannel<T> left, RedisChannel<T> right)` — Compares two instances for equality
- L67 _public operator_ `public static implicit operator RedisChannel<T>(Utf8String key)` — Create a channel name from a Utf8String.
- L73 _public operator_ `public static implicit operator RedisChannel<T>(string key)` — Create a channel name from a byte array.
- L79 _public operator_ `public static implicit operator RedisChannel<T>(byte[] key)` — Create a channel name from a byte array.

#### class `EpicGames.Redis.RedisChannelExtensions`  
`public static class RedisChannelExtensions`  
_public; L85-93_
- desc: Extension methods for channels
- L88-92 _public method_ `public static Task PublishAsync<T>(this IDatabaseAsync database, RedisChannel<T> channel, T item, CommandFlags flags = CommandFlags.None)` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.Redis/RedisConnectionPool.cs` (EpicGames.Redis)


#### class `EpicGames.Redis.RedisConnectionPool`  
`public sealed class RedisConnectionPool : IDisposable`  
_public; L15-108_
- inherits: `IDisposable`
- desc: A connection pool for Redis client Wraps multiple ConnectionMultiplexers as lazy values and initializes them as needed. If full, the least loaded connection will be picked.
- L17 _private field_ `private readonly Lazy<IConnectionMultiplexer>[] _connections`
- L18 _private field_ `private readonly int _defaultDatabaseIndex`
- L26-42 _public ctor_ `public RedisConnectionPool(int poolSize, string redisConfString, int defaultDatabaseIndex = -1)` — Constructor
- L45-54 _public method_ `public void Dispose()` — (inheritdoc)
- L62-98 _public method_ `public IConnectionMultiplexer GetConnection()` — Get a connection from the pool It will pick the least loaded connection or create a new one (if pool size allows)
- L104-107 _public method_ `public IDatabase GetDatabase()` — Shortcut to getting a IDatabase

### `Source/Programs/Shared/EpicGames.Redis/RedisExtensions.cs` (EpicGames.Redis)


#### class `EpicGames.Redis.RedisExtensions`  
`public static class RedisExtensions`  
_public; L10-31_
- desc: Extension methods for Redis
- L17-20 _public method_ `public static RedisKey AsKey(this RedisValue value)` — Convert a RedisValue to a RedisKey
- L27-30 _public method_ `public static RedisValue AsValue(this RedisKey key)` — Convert a RedisKey to a RedisValue

### `Source/Programs/Shared/EpicGames.Redis/RedisHash.cs` (EpicGames.Redis)


#### record struct `EpicGames.Redis.RedisHash`  
`public record struct RedisHash<T>(IDatabaseAsync Database, RedisHashKey<T> Key)`  
_public; L14-14_
- desc: Redis hash, with members corresponding to the property names of a type

#### record struct `EpicGames.Redis.RedisHash`  
`public record struct RedisHash<TName, TValue>(IDatabaseAsync Database, RedisHashKey<TName, TValue> Key)`  
_public; L19-19_
- desc: Redis hash, with members of the given key and value types

#### class `EpicGames.Redis.RedisHashExtensions`  
`public static class RedisHashExtensions`  
_public; L24-209_
- desc: Extension methods for hashes
- L29 _public method_ `public static Condition HashEqual<TRecord, TValue>(this RedisHash<TRecord> target, Expression<Func<TRecord, TValue>> selector, TValue value)` — (inheritdoc)
- L33 _public method_ `public static Condition HashEqual<TName, TValue>(this RedisHash<TName, TValue> target, TName name, TValue value)` — (inheritdoc)
- L37 _public method_ `public static Condition HashExists<TRecord, TValue>(this RedisHash<TRecord> target, Expression<Func<TRecord, TValue>> selector)` — (inheritdoc)
- L41 _public method_ `public static Condition HashExists<TName, TValue>(this RedisHash<TName, TValue> target, TName name)` — (inheritdoc)
- L45 _public method_ `public static Condition HashLengthEqual<TName, TValue>(this RedisHash<TName, TValue> target, long length)` — (inheritdoc)
- L49 _public method_ `public static Condition HashLengthGreaterThan<TName, TValue>(this RedisHash<TName, TValue> target, long length)` — (inheritdoc)
- L53 _public method_ `public static Condition HashLengthLessThan<TName, TValue>(this RedisHash<TName, TValue> target, long length)` — (inheritdoc)
- L57 _public method_ `public static Condition HashNotExists<TRecord, TValue>(this RedisHash<TRecord> target, Expression<Func<TRecord, TValue>> selector)` — (inheritdoc)
- L61 _public method_ `public static Condition HashNotExists<TName, TValue>(this RedisHash<TName, TValue> target, TName name)` — (inheritdoc)
- L65 _public method_ `public static Condition HashNotEqual<TRecord, TValue>(this RedisHash<TRecord> target, Expression<Func<TRecord, TValue>> selector, TValue value)` — (inheritdoc)
- L69 _public method_ `public static Condition HashNotEqual<TName, TValue>(this RedisHash<TName, TValue> target, TName name, TValue value)` — (inheritdoc)
- L77 _public method_ `public static Task<long> DecrementAsync<TRecord>(this RedisHash<TRecord> target, Expression<Func<TRecord, long>> selector, long value = 1L, CommandFlags flags = CommandFlags.None)` — (inheritdoc)
- L81 _public method_ `public static Task<double> DecrementAsync<TRecord>(this RedisHash<TRecord> target, Expression<Func<TRecord, double>> selector, double value = 1.0, CommandFlags flags = CommandFlags.None)` — (inheritdoc)
- L85 _public method_ `public static Task<long> DecrementAsync<TName>(this RedisHash<TName, long> target, TName name, long value = 1L, CommandFlags flags = CommandFlags.None)` — (inheritdoc)
- L89 _public method_ `public static Task<double> DecrementAsync<TName>(this RedisHash<TName, double> target, TName name, double value = 1.0, CommandFlags flags = CommandFlags.None)` — (inheritdoc)
- L97 _public method_ `public static Task<bool> DeleteAsync<TRecord>(this RedisHash<TRecord> target, Expression<Func<TRecord, double>> selector, CommandFlags flags = CommandFlags.None)` — (inheritdoc)
- L101 _public method_ `public static Task<bool> DeleteAsync<TName, TValue>(this RedisHash<TName, TValue> target, TName name, CommandFlags flags = CommandFlags.None)` — (inheritdoc)
- L105 _public method_ `public static Task<long> DeleteAsync<TName, TValue>(this RedisHash<TName, TValue> target, TName[] names, CommandFlags flags = CommandFlags.None)` — (inheritdoc)
- L113 _public method_ `public static Task<bool> ExistsAsync<TName, TValue>(this RedisHash<TName, TValue> target, TName name, CommandFlags flags = CommandFlags.None)` — (inheritdoc)
- L121 _public method_ `public static Task<TValue> GetAsync<TRecord, TValue>(this RedisHash<TRecord> target, Expression<Func<TRecord, TValue>> selector, CommandFlags flags = CommandFlags.None)` — (inheritdoc)
- L125 _public method_ `public static Task<TValue> GetAsync<TName, TValue>(this RedisHash<TName, TValue> target, TName name, CommandFlags flags = CommandFlags.None)` — (inheritdoc)
- L129 _public method_ `public static Task<TValue[]> GetAsync<TName, TValue>(this RedisHash<TName, TValue> target, TName[] names, CommandFlags flags = CommandFlags.None)` — (inheritdoc)
- L137 _public method_ `public static Task<HashEntry<TName, TValue>[]> GetAllAsync<TName, TValue>(this RedisHash<TName, TValue> target, CommandFlags flags = CommandFlags.None)` — (inheritdoc)
- L145 _public method_ `public static Task<long> IncrementAsync<TRecord>(this RedisHash<TRecord> target, Expression<Func<TRecord, long>> selector, long value = 1L, CommandFlags flags = CommandFlags.None)` — (inheritdoc)
- L149 _public method_ `public static Task<double> IncrementAsync<TRecord>(this RedisHash<TRecord> target, Expression<Func<TRecord, double>> selector, double value = 1.0, CommandFlags flags = CommandFlags.None)` — (inheritdoc)
- L153 _public method_ `public static Task<long> IncrementAsync<TName>(this RedisHash<TName, long> target, TName name, long value = 1L, CommandFlags flags = CommandFlags.None)` — (inheritdoc)
- L157 _public method_ `public static Task<double> IncrementAsync<TName>(this RedisHash<TName, double> target, TName name, double value = 1.0, CommandFlags flags = CommandFlags.None)` — (inheritdoc)
- L165 _public method_ `public static Task<TName[]> KeysAsync<TName, TValue>(this RedisHash<TName, TValue> target, CommandFlags flags = CommandFlags.None)` — (inheritdoc)
- L173 _public method_ `public static Task<long> LengthAsync<TName, TValue>(this RedisHash<TName, TValue> target, CommandFlags flags = CommandFlags.None)` — (inheritdoc)
- L181 _public method_ `public static IAsyncEnumerable<HashEntry<TName, TValue>> ScanAsync<TName, TValue>(this RedisHash<TName, TValue> target, RedisValue pattern, int pageSize = 250, long cursor = 0, int pageOffset = 0, CommandFlags flags = CommandFlags.None)` — (inheritdoc)
- L189 _public method_ `public static Task SetAsync<TRecord, TValue>(this RedisHash<TRecord> target, Expression<Func<TRecord, TValue>> selector, TValue value, When when = When.Always, CommandFlags flags = CommandFlags.None)` — (inheritdoc)
- L193 _public method_ `public static Task SetAsync<TName, TValue>(this RedisHash<TName, TValue> target, TName name, TValue value, When when = When.Always, CommandFlags flags = CommandFlags.None)` — (inheritdoc)
- L197 _public method_ `public static Task SetAsync<TName, TValue>(this RedisHash<TName, TValue> target, IEnumerable<HashEntry<TName, TValue>> entries, CommandFlags flags = CommandFlags.None)` — (inheritdoc)
- L205 _public method_ `public static Task<TValue[]> ValuesAsync<TName, TValue>(this RedisHash<TName, TValue> target, CommandFlags flags = CommandFlags.None)` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.Redis/RedisHashKey.cs` (EpicGames.Redis)


#### record struct `EpicGames.Redis.RedisHashKey`  
`public record struct RedisHashKey<T>(RedisKey Inner) : IRedisTypedKey`  
_public; L17-24_
- inherits: `IRedisTypedKey`
- desc: Represents a redis hash key, with members corresponding to the property names of a type
- L23 _public operator_ `public static implicit operator RedisHashKey<T>(string key)` — Implicit conversion to typed redis key.

#### record struct `EpicGames.Redis.RedisHashKey`  
`public record struct RedisHashKey<TName, TValue>(RedisKey Inner) : IRedisTypedKey`  
_public; L31-38_
- inherits: `IRedisTypedKey`
- desc: Represents a typed Redis hash with given key/value types
- L37 _public operator_ `public static implicit operator RedisHashKey<TName, TValue>(string key)` — Implicit conversion to typed redis key.

#### struct `EpicGames.Redis.HashEntry`  
`public readonly struct HashEntry<TName, TValue>`  
_public; L41-86_
- desc: (inheritdoc)
- L44 _public property_ `public readonly TName Name { get; }` — (inheritdoc)
- L47 _public property_ `public readonly TValue Value { get; }` — (inheritdoc)
- L54-58 _public ctor_ `public HashEntry(TName name, TValue value)` — Constructor
- L63-67 _public method_ `public void Deconstruct(out TName name, out TValue value)` — Deconstructor helper method
- L73-76 _public operator_ `public static implicit operator HashEntry(HashEntry<TName, TValue> entry)` — Implicit conversion to a HashEntry
- L82-85 _public operator_ `public static implicit operator KeyValuePair<TName, TValue>(HashEntry<TName, TValue> entry)` — Implicit conversion to a KeyValuePair{TName, TValue}

#### class `EpicGames.Redis.RedisHashKeyExtensions`  
`public static class RedisHashKeyExtensions`  
_public; L91-463_
- desc: Extension methods for hashes
- L96 _public method_ `public static async Task<Dictionary<TName, TValue>> ToDictionaryAsync<TName, TValue>(this Task<HashEntry<TName, TValue>[]> entries) where TName : notnull` — Helper method to convert an array of hash entries into a dictionary
- L102 _public method_ `public static async Task<Dictionary<TName, TValue>> ToDictionaryAsync<TName, TValue>(this Task<HashEntry<TName, TValue>[]> entries, IEqualityComparer<TName>? comparer) where TName : notnull` — Helper method to convert an array of hash entries into a dictionary
- L108-112 _public method_ `public static Condition HashEqual<TRecord, TValue>(this RedisHashKey<TRecord> key, Expression<Func<TRecord, TValue>> selector, TValue value)` — (inheritdoc)
- L115 _public method_ `public static Condition HashEqual<TName, TValue>(this RedisHashKey<TName, TValue> key, TName name, TValue value)` — (inheritdoc)
- L119-123 _public method_ `public static Condition HashExists<TRecord, TValue>(this RedisHashKey<TRecord> key, Expression<Func<TRecord, TValue>> selector)` — (inheritdoc)
- L126 _public method_ `public static Condition HashExists<TName, TValue>(this RedisHashKey<TName, TValue> key, TName name)` — (inheritdoc)
- L130 _public method_ `public static Condition HashLengthEqual<TName, TValue>(this RedisHashKey<TName, TValue> key, long length)` — (inheritdoc)
- L134 _public method_ `public static Condition HashLengthGreaterThan<TName, TValue>(this RedisHashKey<TName, TValue> key, long length)` — (inheritdoc)
- L138 _public method_ `public static Condition HashLengthLessThan<TName, TValue>(this RedisHashKey<TName, TValue> key, long length)` — (inheritdoc)
- L142-146 _public method_ `public static Condition HashNotExists<TRecord, TValue>(this RedisHashKey<TRecord> key, Expression<Func<TRecord, TValue>> selector)` — (inheritdoc)
- L149 _public method_ `public static Condition HashNotExists<TName, TValue>(this RedisHashKey<TName, TValue> key, TName name)` — (inheritdoc)
- L153-157 _public method_ `public static Condition HashNotEqual<TRecord, TValue>(this RedisHashKey<TRecord> key, Expression<Func<TRecord, TValue>> selector, TValue value)` — (inheritdoc)
- L160 _public method_ `public static Condition HashNotEqual<TName, TValue>(this RedisHashKey<TName, TValue> key, TName name, TValue value)` — (inheritdoc)
- L168-172 _public method_ `public static Task<long> HashDecrementAsync<TRecord>(this IDatabaseAsync target, RedisHashKey<TRecord> key, Expression<Func<TRecord, long>> selector, long value = 1L, CommandFlags flags = CommandFlags.None)` — (inheritdoc)
- L175-179 _public method_ `public static Task<double> HashDecrementAsync<TRecord>(this IDatabaseAsync target, RedisHashKey<TRecord> key, Expression<Func<TRecord, double>> selector, double value = 1.0, CommandFlags flags = CommandFlags.None)` — (inheritdoc)
- L182-185 _public method_ `public static Task<long> HashDecrementAsync<TName>(this IDatabaseAsync target, RedisHashKey<TName, long> key, TName name, long value = 1L, CommandFlags flags = CommandFlags.None)` — (inheritdoc)
- L188-191 _public method_ `public static Task<double> HashDecrementAsync<TName>(this IDatabaseAsync target, RedisHashKey<TName, double> key, TName name, double value = 1.0, CommandFlags flags = CommandFlags.None)` — (inheritdoc)
- L198-202 _public method_ `public static Task<bool> HashDeleteAsync<TRecord>(this IDatabaseAsync target, RedisHashKey<TRecord> key, Expression<Func<TRecord, double>> selector, CommandFlags flags = CommandFlags.None)` — (inheritdoc)
- L205-208 _public method_ `public static Task<bool> HashDeleteAsync<TName, TValue>(this IDatabaseAsync target, RedisHashKey<TName, TValue> key, TName name, CommandFlags flags = CommandFlags.None)` — (inheritdoc)
- L211-214 _public method_ `public static Task<long> HashDeleteAsync<TName, TValue>(this IDatabaseAsync target, RedisHashKey<TName, TValue> key, TName[] names, CommandFlags flags = CommandFlags.None)` — (inheritdoc)
- L221-224 _public method_ `public static Task<bool> HashExistsAsync<TName, TValue>(this IDatabaseAsync target, RedisHashKey<TName, TValue> key, TName name, CommandFlags flags = CommandFlags.None)` — (inheritdoc)
- L231-257 _public method_ `public static async Task<TRecord> HashGetAsync<TRecord>(this IDatabaseAsync target, RedisHashKey<TRecord> key, Expression<Func<TRecord, object>>[] selectors, CommandFlags flags = CommandFlags.None) where TRecord : new()` — (inheritdoc)
- L260-264 _public method_ `public static Task<TValue> HashGetAsync<TRecord, TValue>(this IDatabaseAsync target, RedisHashKey<TRecord> key, Expression<Func<TRecord, TValue>> selector, CommandFlags flags = CommandFlags.None)` — (inheritdoc)
- L267-270 _public method_ `public static Task<TValue> HashGetAsync<TName, TValue>(this IDatabaseAsync target, RedisHashKey<TName, TValue> key, TName name, CommandFlags flags = CommandFlags.None)` — (inheritdoc)
- L273-276 _public method_ `public static Task<TValue[]> HashGetAsync<TName, TValue>(this IDatabaseAsync target, RedisHashKey<TName, TValue> key, TName[] names, CommandFlags flags = CommandFlags.None)` — (inheritdoc)
- L283-287 _public method_ `public static async Task<HashEntry<TName, TValue>[]> HashGetAllAsync<TName, TValue>(this IDatabaseAsync target, RedisHashKey<TName, TValue> key, CommandFlags flags = CommandFlags.None)` — (inheritdoc)
- L290-303 _public method_ `public static async Task<TRecord> HashGetAllAsync<TRecord>(this IDatabaseAsync target, RedisHashKey<TRecord> key, CommandFlags flags = CommandFlags.None) where TRecord : new()` — (inheritdoc)
- L310-314 _public method_ `public static Task<long> HashIncrementAsync<TRecord>(this IDatabaseAsync target, RedisHashKey<TRecord> key, Expression<Func<TRecord, long>> selector, long value = 1L, CommandFlags flags = CommandFlags.None)` — (inheritdoc)
- L317-321 _public method_ `public static Task<double> HashIncrementAsync<TRecord>(this IDatabaseAsync target, RedisHashKey<TRecord> key, Expression<Func<TRecord, double>> selector, double value = 1.0, CommandFlags flags = CommandFlags.None)` — (inheritdoc)
- L324-327 _public method_ `public static Task<long> HashIncrementAsync<TName>(this IDatabaseAsync target, RedisHashKey<TName, long> key, TName name, long value = 1L, CommandFlags flags = CommandFlags.None)` — (inheritdoc)
- L330-333 _public method_ `public static Task<double> HashIncrementAsync<TName>(this IDatabaseAsync target, RedisHashKey<TName, double> key, TName name, double value = 1.0, CommandFlags flags = CommandFlags.None)` — (inheritdoc)
- L340-343 _public method_ `public static Task<TName[]> HashKeysAsync<TName, TValue>(this IDatabaseAsync target, RedisHashKey<TName, TValue> key, CommandFlags flags = CommandFlags.None)` — (inheritdoc)
- L350-353 _public method_ `public static Task<long> HashLengthAsync<TName, TValue>(this IDatabaseAsync target, RedisHashKey<TName, TValue> key, CommandFlags flags = CommandFlags.None)` — (inheritdoc)
- L360-366 _public method_ `public static async IAsyncEnumerable<HashEntry<TName, TValue>> HashScanAsync<TName, TValue>(this IDatabaseAsync target, RedisHashKey<TName, TValue> key, RedisValue pattern, int pageSize = 250, long cursor = 0, int pageOffset = 0, CommandFlags flags = CommandFlags.None)` — (inheritdoc)
- L419-423 _public method_ `public static Task<bool> HashSetAsync<TRecord, TValue>(this IDatabaseAsync target, RedisHashKey<TRecord> key, Expression<Func<TRecord, TValue>> selector, TValue value, When when = When.Always, CommandFlags flags = CommandFlags.None)` — (inheritdoc)
- L426-438 _public method_ `public static Task HashSetAsync<TRecord>(this IDatabaseAsync target, RedisHashKey<TRecord> key, TRecord value, CommandFlags flags = CommandFlags.None)` — (inheritdoc)
- L441-444 _public method_ `public static Task<bool> HashSetAsync<TName, TValue>(this IDatabaseAsync target, RedisHashKey<TName, TValue> key, TName name, TValue value, When when = When.Always, CommandFlags flags = CommandFlags.None)` — (inheritdoc)
- L447-450 _public method_ `public static Task HashSetAsync<TName, TValue>(this IDatabaseAsync target, RedisHashKey<TName, TValue> key, IEnumerable<HashEntry<TName, TValue>> entries, CommandFlags flags = CommandFlags.None)` — (inheritdoc)
- L457-460 _public method_ `public static Task<TValue[]> HashValuesAsync<TName, TValue>(this IDatabaseAsync target, RedisHashKey<TName, TValue> key, CommandFlags flags = CommandFlags.None)` — (inheritdoc)

#### class `EpicGames.Redis.RedisHashKeyExtensions.HashRecordInfo`  
`class HashRecordInfo<T>`  
_private*; L372-405_
- L374 _public property_ `public static HashRecordInfo<T> Instance { get; }`
- L376 _public property_ `public IReadOnlyList<HashPropertyInfo<T>> Properties { get; }`
- L378 _public property_ `public IReadOnlyDictionary<string, HashPropertyInfo<T>> PropertiesByName { get; }`
- L380-389 _public ctor_ `public HashRecordInfo()`
- L391-404 _public method_ `public bool SetProperty(T record, RedisValue name, RedisValue value)`

#### record `EpicGames.Redis.RedisHashKeyExtensions.HashPropertyInfo`  
`record class HashPropertyInfo<T>(string Name, Func<T, RedisValue> GetValue, Action<T, RedisValue> SetValue)`  
_private*; L407-416_
- L409-415 _public ctor_ `public HashPropertyInfo(PropertyInfo propertyInfo) : this( propertyInfo.Name, record => RedisSerializer.Serialize(propertyInfo.GetValue(record), propertyInfo.PropertyType), (record, value) => propertyInfo.SetValue(record, RedisSerializer.Deserialize(value, propertyInfo.PropertyType)) )`

### `Source/Programs/Shared/EpicGames.Redis/RedisList.cs` (EpicGames.Redis)


#### record struct `EpicGames.Redis.RedisList`  
`public record struct RedisList<TElement>(IDatabaseAsync Database, RedisListKey<TElement> Key)`  
_public; L13-13_
- desc: Represents a typed Redis list with a given key

#### class `EpicGames.Redis.RedisListExtensions`  
`public static class RedisListExtensions`  
_public; L18-155_
- desc: Extension methods for sets
- L23 _public method_ `public static Condition ListIndexEqual<TElement>(this RedisList<TElement> target, long index, TElement value)` — (inheritdoc)
- L27 _public method_ `public static Condition ListIndexExists<TElement>(this RedisList<TElement> target, long index)` — (inheritdoc)
- L31 _public method_ `public static Condition ListIndexNotEqual<TElement>(this RedisList<TElement> target, long index, TElement value)` — (inheritdoc)
- L35 _public method_ `public static Condition ListIndexNotExists<TElement>(this RedisList<TElement> target, long index)` — (inheritdoc)
- L39 _public method_ `public static Condition ListLengthEqual<TElement>(this RedisList<TElement> target, long length)` — (inheritdoc)
- L43 _public method_ `public static Condition ListLengthGreaterThan<TElement>(this RedisList<TElement> target, long length)` — (inheritdoc)
- L47 _public method_ `public static Condition ListLengthLessThan<TElement>(this RedisList<TElement> target, long length)` — (inheritdoc)
- L55 _public method_ `public static Task<TElement> GetByIndexAsync<TElement>(this RedisList<TElement> target, long index, CommandFlags flags = CommandFlags.None)` — (inheritdoc)
- L63 _public method_ `public static Task<long> InsertAfterAsync<TElement>(this RedisList<TElement> target, TElement pivot, TElement item, CommandFlags flags = CommandFlags.None)` — (inheritdoc)
- L71 _public method_ `public static Task<long> InsertBeforeAsync<TElement>(this RedisList<TElement> target, TElement pivot, TElement item, CommandFlags flags = CommandFlags.None)` — (inheritdoc)
- L79 _public method_ `public static Task<TElement> LeftPopAsync<TElement>(this RedisList<TElement> target, CommandFlags flags = CommandFlags.None)` — (inheritdoc)
- L87 _public method_ `public static Task<long> LeftPushAsync<TElement>(this RedisList<TElement> target, TElement item, When when = When.Always, CommandFlags flags = CommandFlags.None)` — (inheritdoc)
- L91 _public method_ `public static Task<long> LeftPushAsync<TElement>(this RedisList<TElement> target, TElement[] values, When when = When.Always, CommandFlags flags = CommandFlags.None)` — (inheritdoc)
- L99 _public method_ `public static Task<long> LengthAsync<TElement>(this RedisList<TElement> target)` — (inheritdoc)
- L107 _public method_ `public static Task<TElement[]> RangeAsync<TElement>(this RedisList<TElement> target, long start = 0, long stop = -1, CommandFlags flags = CommandFlags.None)` — (inheritdoc)
- L115 _public method_ `public static Task<long> RemoveAsync<TElement>(this RedisList<TElement> target, TElement value, long count = 0L, CommandFlags flags = CommandFlags.None)` — (inheritdoc)
- L123 _public method_ `public static Task<TElement> RightPopAsync<TElement>(this RedisList<TElement> target, CommandFlags flags = CommandFlags.None)` — (inheritdoc)
- L131 _public method_ `public static Task<long> RightPushAsync<TElement>(this RedisList<TElement> target, TElement item, When when = When.Always, CommandFlags flags = CommandFlags.None)` — (inheritdoc)
- L135 _public method_ `public static Task<long> RightPushAsync<TElement>(this RedisList<TElement> target, IEnumerable<TElement> values, When when = When.Always, CommandFlags flags = CommandFlags.None)` — (inheritdoc)
- L143 _public method_ `public static Task SetByIndexAsync<TElement>(this RedisList<TElement> target, long index, TElement value, CommandFlags flags = CommandFlags.None)` — (inheritdoc)
- L151 _public method_ `public static Task TrimAsync<TElement>(this RedisList<TElement> target, long start, long stop, CommandFlags flags = CommandFlags.None)` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.Redis/RedisListKey.cs` (EpicGames.Redis)


#### record struct `EpicGames.Redis.RedisListKey`  
`public record struct RedisListKey<TElement>(RedisKey Inner) : IRedisTypedKey`  
_public; L14-21_
- inherits: `IRedisTypedKey`
- desc: Represents a typed Redis list with a given key
- L20 _public operator_ `public static implicit operator RedisListKey<TElement>(string key)` — Implicit conversion to typed redis key.

#### class `EpicGames.Redis.RedisListKeyExtensions`  
`public static class RedisListKeyExtensions`  
_public; L26-193_
- desc: Extension methods for sets
- L31 _public method_ `public static Condition ListIndexEqual<TElement>(this RedisListKey<TElement> key, long index, TElement value)` — (inheritdoc)
- L35 _public method_ `public static Condition ListIndexExists<TElement>(this RedisListKey<TElement> key, long index)` — (inheritdoc)
- L39 _public method_ `public static Condition ListIndexNotEqual<TElement>(this RedisListKey<TElement> key, long index, TElement value)` — (inheritdoc)
- L43 _public method_ `public static Condition ListIndexNotExists<TElement>(this RedisListKey<TElement> key, long index)` — (inheritdoc)
- L47 _public method_ `public static Condition ListLengthEqual<TElement>(this RedisListKey<TElement> key, long length)` — (inheritdoc)
- L51 _public method_ `public static Condition ListLengthGreaterThan<TElement>(this RedisListKey<TElement> key, long length)` — (inheritdoc)
- L55 _public method_ `public static Condition ListLengthLessThan<TElement>(this RedisListKey<TElement> key, long length)` — (inheritdoc)
- L63-66 _public method_ `public static Task<TElement> ListGetByIndexAsync<TElement>(this IDatabaseAsync target, RedisListKey<TElement> key, long index, CommandFlags flags = CommandFlags.None)` — (inheritdoc)
- L73-76 _public method_ `public static Task<long> ListInsertAfterAsync<TElement>(this IDatabaseAsync target, RedisListKey<TElement> key, TElement pivot, TElement item, CommandFlags flags = CommandFlags.None)` — (inheritdoc)
- L83-88 _public method_ `public static Task<long> ListInsertBeforeAsync<TElement>(this IDatabaseAsync target, RedisListKey<TElement> key, TElement pivot, TElement item, CommandFlags flags = CommandFlags.None)` — (inheritdoc)
- L95-98 _public method_ `public static Task<TElement> ListLeftPopAsync<TElement>(this IDatabaseAsync target, RedisListKey<TElement> key, CommandFlags flags = CommandFlags.None)` — (inheritdoc)
- L105-108 _public method_ `public static Task<long> ListLeftPushAsync<TElement>(this IDatabaseAsync target, RedisListKey<TElement> key, TElement item, When when = When.Always, CommandFlags flags = CommandFlags.None)` — (inheritdoc)
- L111-114 _public method_ `public static Task<long> ListLeftPushAsync<TElement>(this IDatabaseAsync target, RedisListKey<TElement> key, TElement[] values, When when = When.Always, CommandFlags flags = CommandFlags.None)` — (inheritdoc)
- L121-124 _public method_ `public static Task<long> ListLengthAsync<TElement>(this IDatabaseAsync target, RedisListKey<TElement> key)` — (inheritdoc)
- L131-134 _public method_ `public static Task<TElement[]> ListRangeAsync<TElement>(this IDatabaseAsync target, RedisListKey<TElement> key, long start = 0, long stop = -1, CommandFlags flags = CommandFlags.None)` — (inheritdoc)
- L141-144 _public method_ `public static Task<long> ListRemoveAsync<TElement>(this IDatabaseAsync target, RedisListKey<TElement> key, TElement value, long count = 0L, CommandFlags flags = CommandFlags.None)` — (inheritdoc)
- L151-154 _public method_ `public static Task<TElement> ListRightPopAsync<TElement>(this IDatabaseAsync target, RedisListKey<TElement> key, CommandFlags flags = CommandFlags.None)` — (inheritdoc)
- L161-164 _public method_ `public static Task<long> ListRightPushAsync<TElement>(this IDatabaseAsync target, RedisListKey<TElement> key, TElement item, When when = When.Always, CommandFlags flags = CommandFlags.None)` — (inheritdoc)
- L167-170 _public method_ `public static Task<long> ListRightPushAsync<TElement>(this IDatabaseAsync target, RedisListKey<TElement> key, IEnumerable<TElement> values, When when = When.Always, CommandFlags flags = CommandFlags.None)` — (inheritdoc)
- L177-180 _public method_ `public static Task ListSetByIndexAsync<TElement>(this IDatabaseAsync target, RedisListKey<TElement> key, long index, TElement value, CommandFlags flags = CommandFlags.None)` — (inheritdoc)
- L187-190 _public method_ `public static Task ListTrimAsync<TElement>(this IDatabaseAsync target, RedisListKey<TElement> key, long start, long stop, CommandFlags flags = CommandFlags.None)` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.Redis/RedisSerializer.cs` (EpicGames.Redis)


#### class `EpicGames.Redis.RedisConverterAttribute`  
`public sealed class RedisConverterAttribute : Attribute`  
_public; L23-38_
- attrs: `[AttributeUsage(AttributeTargets.Class | AttributeTargets.Struct)]`
- inherits: `Attribute`
- desc: Attribute specifying the converter type to use for a class
- L28 _public property_ `public Type ConverterType { get; }` — Type of the converter to use
- L34-37 _public ctor_ `public RedisConverterAttribute(Type converterType)` — Constructor

#### interface `EpicGames.Redis.IRedisConverter`  
`public interface IRedisConverter<T>`  
_public; L43-58_
- desc: Converter to and from RedisValue types
- L50 _public* method_ `RedisValue ToRedisValue(T value)` — Serailize an object to a RedisValue
- L57 _public* method_ `T FromRedisValue(RedisValue value)` — Deserialize an object from a RedisValue

#### class `EpicGames.Redis.RedisCbConverter`  
`public sealed class RedisCbConverter<T> : IRedisConverter<T>`  
_public; L64-77_
- inherits: `IRedisConverter<T>`
- desc: Redis serializer that uses compact binary to serialize objects
- L67-70 _public method_ `public RedisValue ToRedisValue(T value)` — (inheritdoc)
- L73-76 _public method_ `public T FromRedisValue(RedisValue value)` — (inheritdoc)

#### class `EpicGames.Redis.RedisJsonConverter`  
`public sealed class RedisJsonConverter<T> : IRedisConverter<T>`  
_public; L82-97_
- inherits: `IRedisConverter<T>`
- desc: Redis serializer that uses JSON to serialize objects
- L84 _private* field_ `static readonly JsonSerializerOptions s_options = new() { PropertyNameCaseInsensitive = true, PropertyNamingPolicy = JsonNamingPolicy.CamelCase }`
- L87-90 _public method_ `public RedisValue ToRedisValue(T value)` — (inheritdoc)
- L93-96 _public method_ `public T FromRedisValue(RedisValue value)` — (inheritdoc)

#### class `EpicGames.Redis.RedisSerializer`  
`public static class RedisSerializer`  
_public; L102-389_
- desc: Handles serialization of types to RedisValue instances
- L145 _private* field_ `static readonly Dictionary<Type, object> s_nativeConverters = ...`
- L145 _private* field_ `static readonly Dictionary< s_nativeConverters = CreateNativeConverterLookup()`
- L147-169 _private* method_ `static Dictionary<Type, object> CreateNativeConverterLookup()`
- L171-174 _private* method_ `static KeyValuePair<Type, object> CreateNativeConverter<T>(Func<RedisValue, T> fromRedisValueFunc, Func<T, RedisValue> toRedisValueFunc)`
- L176 _private* field_ `static readonly Dictionary<Type, Type> s_typeToConverterType = ...`
- L176 _private* field_ `static readonly Dictionary< s_typeToConverterType = []`
- L187 _private* field_ `static readonly ConcurrentDictionary<Type, IRedisConverter<object>> s_typeToObjectConverter = ...`
- L187 _private* field_ `static readonly ConcurrentDictionary< s_typeToObjectConverter = new()`
- L192-201 _public method_ `public static void RegisterConverter<T, TConverter>() where TConverter : IRedisConverter<T>` — Register a custom converter for a particular type
- L206-274 _private* method_ `static IRedisConverter<T> CreateConverter<T>()` — Creates a converter for a given type
- L290-293 _public method_ `public static IRedisConverter<T> GetConverter<T>()` — Gets the converter for a particular type
- L300-308 _public method_ `public static IRedisConverter<object> GetObjectConverter(Type type)` — Gets a type converter which casts to/from an object value
- L316-319 _public method_ `public static RedisValue Serialize(object? value, Type type)` — Serialize an object to a RedisValue
- L327-330 _public method_ `public static RedisValue Serialize<T>(T value)` — Serialize an object to a RedisValue
- L338-348 _public method_ `public static RedisValue[] Serialize<T>(T[] inputs)` — Serialize an object to a RedisValue
- L356-359 _public method_ `public static object? Deserialize(RedisValue value, Type type)` — Deserialize a RedisValue
- L367-370 _public method_ `public static T Deserialize<T>(RedisValue value)` — Deserialize a RedisValue
- L378-388 _public method_ `public static T[] Deserialize<T>(RedisValue[] inputs)` — Deserialize an array of RedisValue objects

#### class `EpicGames.Redis.RedisSerializer.RedisStringConverter`  
`class RedisStringConverter<T> : IRedisConverter<T>`  
_private*; L104-115_
- inherits: `IRedisConverter<T>`
- L106 _private* field_ `readonly TypeConverter _typeConverter`
- L108-111 _public ctor_ `public RedisStringConverter(TypeConverter typeConverter)`
- L113 _public method_ `public RedisValue ToRedisValue(T value)`
- L114 _public method_ `public T FromRedisValue(RedisValue value)`

#### class `EpicGames.Redis.RedisSerializer.RedisUtf8StringConverter`  
`class RedisUtf8StringConverter<T> : IRedisConverter<T>`  
_private*; L117-128_
- inherits: `IRedisConverter<T>`
- L119 _private* field_ `readonly TypeConverter _typeConverter`
- L121-124 _public ctor_ `public RedisUtf8StringConverter(TypeConverter typeConverter)`
- L126 _public method_ `public RedisValue ToRedisValue(T value)`
- L127 _public method_ `public T FromRedisValue(RedisValue value)`

#### class `EpicGames.Redis.RedisSerializer.RedisNativeConverter`  
`class RedisNativeConverter<T> : IRedisConverter<T>`  
_private*; L130-143_
- inherits: `IRedisConverter<T>`
- L132 _private* field_ `readonly Func<RedisValue, T> _fromRedisValueFunc`
- L132 _private* field_ `readonly Func< _fromRedisValueFunc`
- L133 _private* field_ `readonly Func<T, RedisValue> _toRedisValueFunc`
- L133 _private* field_ `readonly Func< _toRedisValueFunc`
- L135-139 _public ctor_ `public RedisNativeConverter(Func<RedisValue, T> fromRedisValueFunc, Func<T, RedisValue> toRedisValueFunc)`
- L141 _public method_ `public T FromRedisValue(RedisValue value)`
- L142 _public method_ `public RedisValue ToRedisValue(T value)`

#### class `EpicGames.Redis.RedisSerializer.RedisObjectConverter`  
`class RedisObjectConverter<T> : IRedisConverter<object>`  
_private*; L178-185_
- inherits: `IRedisConverter<object>`
- L180 _public method_ `public object FromRedisValue(RedisValue value)`
- L183 _public method_ `public RedisValue ToRedisValue(object value)`

#### class `EpicGames.Redis.RedisSerializer.CachedConverter`  
`class CachedConverter<T>`  
_private*; L280-283_
- desc: Static class for caching converter lookups
- L282 _public field_ `public static IRedisConverter<T> Converter = CreateConverter<T>()`

#### class `EpicGames.Redis.RedisSerializerExtensions`  
`public static class RedisSerializerExtensions`  
_public; L394-425_
- desc: Extension methods for serialization
- L402-413 _public method_ `public static async Task<T> DeserializeAsync<T>(this Task<RedisValue> value)` — Deserialize a RedisValue
- L421-424 _public method_ `public static async Task<T[]> DeserializeAsync<T>(this Task<RedisValue[]> values)` — Deserialize a RedisValue

### `Source/Programs/Shared/EpicGames.Redis/RedisSet.cs` (EpicGames.Redis)


#### record struct `EpicGames.Redis.RedisSet`  
`public record struct RedisSet<TElement>(IDatabaseAsync Database, RedisSetKey<TElement> Key)`  
_public; L14-14_
- desc: Represents a typed Redis set with a given key

#### class `EpicGames.Redis.RedisSetExtensions`  
`public static class RedisSetExtensions`  
_public; L19-120_
- desc: Extension methods for sets
- L24 _public method_ `public static Condition SetContains<TElement>(this RedisSet<TElement> target, TElement value)` — (inheritdoc)
- L28 _public method_ `public static Condition SetLengthEqual<TElement>(this RedisSet<TElement> target, long length)` — (inheritdoc)
- L32 _public method_ `public static Condition SetLengthGreaterThan<TElement>(this RedisSet<TElement> target, long length)` — (inheritdoc)
- L36 _public method_ `public static Condition SetLengthLessThan<TElement>(this RedisSet<TElement> target, long length)` — (inheritdoc)
- L40 _public method_ `public static Condition SetNotContains<TElement>(this RedisSet<TElement> target, TElement value)` — (inheritdoc)
- L48 _public method_ `public static Task<bool> AddAsync<TElement>(this RedisSet<TElement> target, TElement item, CommandFlags flags = CommandFlags.None)` — (inheritdoc)
- L52 _public method_ `public static Task<long> AddAsync<TElement>(this RedisSet<TElement> target, TElement[] values, CommandFlags flags = CommandFlags.None)` — (inheritdoc)
- L60 _public method_ `public static Task<bool> ContainsAsync<TElement>(this RedisSet<TElement> target, TElement value, CommandFlags flags = CommandFlags.None)` — (inheritdoc)
- L68 _public method_ `public static Task<long> LengthAsync<TElement>(this RedisSet<TElement> target, CommandFlags flags = CommandFlags.None)` — (inheritdoc)
- L76 _public method_ `public static Task<TElement[]> MembersAsync<TElement>(this RedisSet<TElement> target, CommandFlags flags = CommandFlags.None)` — (inheritdoc)
- L84 _public method_ `public static Task<TElement> PopAsync<TElement>(this RedisSet<TElement> target, CommandFlags flags = CommandFlags.None)` — (inheritdoc)
- L88 _public method_ `public static Task<TElement[]> PopAsync<TElement>(this RedisSet<TElement> target, long count, CommandFlags flags = CommandFlags.None)` — (inheritdoc)
- L96 _public method_ `public static Task<TElement> RandomMemberAsync<TElement>(this RedisSet<TElement> target, CommandFlags flags = CommandFlags.None)` — (inheritdoc)
- L104 _public method_ `public static Task<bool> RemoveAsync<TElement>(this RedisSet<TElement> target, TElement item, CommandFlags flags = CommandFlags.None)` — (inheritdoc)
- L108 _public method_ `public static Task<long> RemoveAsync<TElement>(this RedisSet<TElement> target, TElement[] values, CommandFlags flags = CommandFlags.None)` — (inheritdoc)
- L116 _public method_ `public static IAsyncEnumerable<TElement> ScanAsync<TElement>(this RedisSet<TElement> target, RedisValue pattern = default, int pageSize = 250, long cursor = 0, int pageOffset = 0, CommandFlags flags = CommandFlags.None)` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.Redis/RedisSetKey.cs` (EpicGames.Redis)


#### record struct `EpicGames.Redis.RedisSetKey`  
`public record struct RedisSetKey<TElement>(RedisKey Inner) : IRedisTypedKey`  
_public; L14-21_
- inherits: `IRedisTypedKey`
- desc: Represents a typed Redis set with a given key
- L20 _public operator_ `public static implicit operator RedisSetKey<TElement>(string key)` — Implicit conversion to typed redis key.

#### class `EpicGames.Redis.RedisSetKeyExtensions`  
`public static class RedisSetKeyExtensions`  
_public; L26-158_
- desc: Extension methods for sets
- L31 _public method_ `public static Condition SetContains<TElement>(this RedisSetKey<TElement> key, TElement value)` — (inheritdoc)
- L35 _public method_ `public static Condition SetLengthEqual<TElement>(this RedisSetKey<TElement> key, long length)` — (inheritdoc)
- L39 _public method_ `public static Condition SetLengthGreaterThan<TElement>(this RedisSetKey<TElement> key, long length)` — (inheritdoc)
- L43 _public method_ `public static Condition SetLengthLessThan<TElement>(this RedisSetKey<TElement> key, long length)` — (inheritdoc)
- L47 _public method_ `public static Condition SetNotContains<TElement>(this RedisSetKey<TElement> key, TElement value)` — (inheritdoc)
- L55-58 _public method_ `public static Task<bool> SetAddAsync<TElement>(this IDatabaseAsync target, RedisSetKey<TElement> key, TElement item, CommandFlags flags = CommandFlags.None)` — (inheritdoc)
- L61-64 _public method_ `public static Task<long> SetAddAsync<TElement>(this IDatabaseAsync target, RedisSetKey<TElement> key, TElement[] values, CommandFlags flags = CommandFlags.None)` — (inheritdoc)
- L71-74 _public method_ `public static Task<bool> SetContainsAsync<TElement>(this IDatabaseAsync target, RedisSetKey<TElement> key, TElement value, CommandFlags flags = CommandFlags.None)` — (inheritdoc)
- L81-84 _public method_ `public static Task<long> SetLengthAsync<TElement>(this IDatabaseAsync target, RedisSetKey<TElement> key, CommandFlags flags = CommandFlags.None)` — (inheritdoc)
- L91-94 _public method_ `public static Task<TElement[]> SetMembersAsync<TElement>(this IDatabaseAsync target, RedisSetKey<TElement> key, CommandFlags flags = CommandFlags.None)` — (inheritdoc)
- L101-104 _public method_ `public static Task<TElement> SetPopAsync<TElement>(this IDatabaseAsync target, RedisSetKey<TElement> key, CommandFlags flags = CommandFlags.None)` — (inheritdoc)
- L107-110 _public method_ `public static Task<TElement[]> SetPopAsync<TElement>(this IDatabaseAsync target, RedisSetKey<TElement> key, long count, CommandFlags flags = CommandFlags.None)` — (inheritdoc)
- L117 _public method_ `public static Task<TElement> SetRandomMemberAsync<TElement>(this IDatabaseAsync target, RedisSetKey<TElement> key, CommandFlags flags = CommandFlags.None)` — (inheritdoc)
- L125 _public method_ `public static Task<TElement[]> SetRandomMembersAsync<TElement>(this IDatabaseAsync target, RedisSetKey<TElement> key, long count, CommandFlags flags = CommandFlags.None)` — (inheritdoc)
- L133-136 _public method_ `public static Task<bool> SetRemoveAsync<TElement>(this IDatabaseAsync target, RedisSetKey<TElement> key, TElement item, CommandFlags flags = CommandFlags.None)` — (inheritdoc)
- L139-142 _public method_ `public static Task<long> SetRemoveAsync<TElement>(this IDatabaseAsync target, RedisSetKey<TElement> key, TElement[] values, CommandFlags flags = CommandFlags.None)` — (inheritdoc)
- L149-155 _public method_ `public static async IAsyncEnumerable<TElement> SetScanAsync<TElement>(this IDatabaseAsync target, RedisSetKey<TElement> key, RedisValue pattern = default, int pageSize = 250, long cursor = 0, int pageOffset = 0, CommandFlags flags = CommandFlags.None)` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.Redis/RedisSortedSet.cs` (EpicGames.Redis)


#### record struct `EpicGames.Redis.RedisSortedSet`  
`public record struct RedisSortedSet<TElement>(IDatabaseAsync Database, RedisSortedSetKey<TElement> Key)`  
_public; L13-13_
- desc: Represents a typed Redis sorted set with a given key

#### class `EpicGames.Redis.RedisSortedSetExtensions`  
`public static class RedisSortedSetExtensions`  
_public; L18-199_
- desc: Extension methods for sets
- L23 _public method_ `public static Condition SortedSetContains<TElement>(this RedisSortedSet<TElement> target, TElement value)` — (inheritdoc)
- L27 _public method_ `public static Condition SortedSetEqual<TElement>(this RedisSortedSet<TElement> target, TElement value, RedisValue score)` — (inheritdoc)
- L31 _public method_ `public static Condition SortedSetLengthEqual<TElement>(this RedisSortedSet<TElement> target, long length)` — (inheritdoc)
- L35 _public method_ `public static Condition SortedSetLengthGreaterThan<TElement>(this RedisSortedSet<TElement> target, long length)` — (inheritdoc)
- L39 _public method_ `public static Condition SortedSetLengthLessThan<TElement>(this RedisSortedSet<TElement> target, long length)` — (inheritdoc)
- L43 _public method_ `public static Condition SortedSetNotContains<TElement>(this RedisSortedSet<TElement> target, TElement value)` — (inheritdoc)
- L47 _public method_ `public static Condition SortedSetNotEqual<TElement>(this RedisSortedSet<TElement> target, TElement value, RedisValue score)` — (inheritdoc)
- L51 _public method_ `public static Condition SortedSetScoreExists<TElement>(this RedisSortedSet<TElement> target, RedisValue score)` — (inheritdoc)
- L55 _public method_ `public static Condition SortedSetScoreExists<TElement>(this RedisSortedSet<TElement> target, RedisValue score, RedisValue count)` — (inheritdoc)
- L63 _public method_ `public static Task<bool> AddAsync<TElement>(this RedisSortedSet<TElement> target, TElement value, double score, SortedSetWhen when = SortedSetWhen.Always, CommandFlags flags = CommandFlags.None)` — (inheritdoc)
- L67 _public method_ `public static Task<long> AddAsync<TElement>(this RedisSortedSet<TElement> target, SortedSetEntry<TElement>[] values, SortedSetWhen when = SortedSetWhen.Always, CommandFlags flags = CommandFlags.None)` — (inheritdoc)
- L75 _public method_ `public static Task<long> LengthAsync<TElement>(this RedisSortedSet<TElement> target, double min = Double.NegativeInfinity, double max = Double.PositiveInfinity, Exclude exclude = Exclude.None, CommandFlags flags = CommandFlags.None)` — (inheritdoc)
- L83 _public method_ `public static Task<long> LengthByValueAsync<TElement>(this RedisSortedSet<TElement> target, TElement min, TElement max, Exclude exclude = Exclude.None, CommandFlags flags = CommandFlags.None)` — (inheritdoc)
- L91 _public method_ `public static Task<TElement[]> RangeByRankAsync<TElement>(this RedisSortedSet<TElement> target, long start = 0, long stop = -1, Order order = Order.Ascending, CommandFlags flags = CommandFlags.None)` — (inheritdoc)
- L99 _public method_ `public static Task<SortedSetEntry<TElement>[]> RangeByRankWithScoresAsync<TElement>(this RedisSortedSet<TElement> target, long start, long stop = -1, Order order = Order.Ascending, CommandFlags flags = CommandFlags.None)` — (inheritdoc)
- L107 _public method_ `public static Task<TElement[]> RangeByScoreAsync<TElement>(this RedisSortedSet<TElement> target, double start = Double.NegativeInfinity, double stop = Double.PositiveInfinity, Exclude exclude = Exclude.None, Order order = Order.Ascending, long skip = 0L, long take = -1L, CommandFlags flags = CommandFlags.None)` — (inheritdoc)
- L115 _public method_ `public static Task<SortedSetEntry<TElement>[]> SortedSetRangeByScoreWithScoresAsync<TElement>(this RedisSortedSet<TElement> target, double start = Double.NegativeInfinity, double stop = Double.PositiveInfinity, Exclude exclude = Exclude.None, Order order = Order.Ascending, long skip = 0L, long take = -1L, CommandFlags flags = CommandFlags.None)` — (inheritdoc)
- L123 _public method_ `public static Task<TElement[]> RangeByValueAsync<TElement>(this RedisSortedSet<TElement> target, TElement min, TElement max, Exclude exclude = Exclude.None, Order order = Order.Ascending, long skip = 0L, long take = -1L, CommandFlags flags = CommandFlags.None)` — (inheritdoc)
- L131 _public method_ `public static Task<long?> RankAsync<TElement>(this RedisSortedSet<TElement> target, TElement item, Order order = Order.Ascending, CommandFlags flags = CommandFlags.None)` — (inheritdoc)
- L139 _public method_ `public static Task<bool> RemoveAsync<TElement>(this RedisSortedSet<TElement> target, TElement value, CommandFlags flags = CommandFlags.None)` — (inheritdoc)
- L143 _public method_ `public static Task<long> RemoveAsync<TElement>(this RedisSortedSet<TElement> target, TElement[] values, CommandFlags flags = CommandFlags.None)` — (inheritdoc)
- L151 _public method_ `public static Task<long> RemoveRangeByRankAsync<TElement>(this RedisSortedSet<TElement> target, long start, long stop, CommandFlags flags = CommandFlags.None)` — (inheritdoc)
- L159 _public method_ `public static Task<long> RemoveRangeByScoreAsync<TElement>(this RedisSortedSet<TElement> target, double start, double stop, Exclude exclude = Exclude.None, CommandFlags flags = CommandFlags.None)` — (inheritdoc)
- L167 _public method_ `public static Task<long> RemoveRangeByValueAsync<TElement>(this RedisSortedSet<TElement> target, TElement min, TElement max, Exclude exclude = Exclude.None, CommandFlags flags = CommandFlags.None)` — (inheritdoc)
- L175 _public method_ `public static IAsyncEnumerable<SortedSetEntry<TElement>> ScanAsync<TElement>(this RedisSortedSet<TElement> target, RedisValue pattern = default, int pageSize = 250, long cursor = 0, int pageOffset = 0, CommandFlags flags = CommandFlags.None)` — (inheritdoc)
- L183 _public method_ `public static Task<double?> ScoreAsync<TElement>(this RedisSortedSet<TElement> target, TElement member, CommandFlags flags = CommandFlags.None)` — (inheritdoc)
- L191 _public method_ `public static Task<bool> UpdateAsync<TElement>(this RedisSortedSet<TElement> target, TElement member, double score, SortedSetWhen when = SortedSetWhen.Always, CommandFlags flags = CommandFlags.None)` — (inheritdoc)
- L195 _public method_ `public static Task<long> UpdateAsync<TElement>(this RedisSortedSet<TElement> target, SortedSetEntry<TElement>[] values, SortedSetWhen when = SortedSetWhen.Always, CommandFlags flags = CommandFlags.None)` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.Redis/RedisSortedSetKey.cs` (EpicGames.Redis)


#### record struct `EpicGames.Redis.RedisSortedSetKey`  
`public record struct RedisSortedSetKey<TElement>(RedisKey Inner) : IRedisTypedKey`  
_public; L15-22_
- inherits: `IRedisTypedKey`
- desc: Represents a typed Redis sorted set with a given key
- L21 _public operator_ `public static implicit operator RedisSortedSetKey<TElement>(string key)` — Implicit conversion to typed redis key.

#### struct `EpicGames.Redis.SortedSetEntry`  
`public readonly struct SortedSetEntry<T> : IEquatable<SortedSetEntry<T>>, IComparable, IComparable<SortedSetEntry<T>>`  
_public; L28-122_
- inherits: `IEquatable<SortedSetEntry<T>>, IComparable, IComparable<SortedSetEntry<T>>`
- desc: Typed implementation of SortedSetEntry
- L33 _public property_ `public readonly T Element { get; }` — Accessor for the element type
- L38 _public property_ `public readonly RedisValue ElementValue { get; }` — The encoded element value
- L43 _public property_ `public readonly double Score { get; }` — Score for the entry
- L49-54 _public ctor_ `public SortedSetEntry(SortedSetEntry entry)` — Constructor
- L61-66 _public ctor_ `public SortedSetEntry(T element, double score)` — Constructor
- L73-77 _public method_ `public void Deconstruct(out T outElement, out double outScore)` — Deconstruct this item into a tuple
- L80 _public method_ `public override bool Equals(object? obj)` — (inheritdoc)
- L84 _public method_ `public override int GetHashCode()` — (inheritdoc)
- L88 _public method_ `public bool Equals(SortedSetEntry<T> other)` — (inheritdoc)
- L92 _public method_ `public int CompareTo(SortedSetEntry<T> other)` — (inheritdoc)
- L96 _public method_ `public int CompareTo(object? obj)` — (inheritdoc)
- L100 _public operator_ `public static bool operator ==(SortedSetEntry<T> a, SortedSetEntry<T> b)` — (inheritdoc)
- L104 _public operator_ `public static bool operator !=(SortedSetEntry<T> a, SortedSetEntry<T> b)` — (inheritdoc)
- L108 _public operator_ `public static bool operator <=(SortedSetEntry<T> a, SortedSetEntry<T> b)` — (inheritdoc)
- L112 _public operator_ `public static bool operator <(SortedSetEntry<T> a, SortedSetEntry<T> b)` — (inheritdoc)
- L116 _public operator_ `public static bool operator >=(SortedSetEntry<T> a, SortedSetEntry<T> b)` — (inheritdoc)
- L120 _public operator_ `public static bool operator >(SortedSetEntry<T> a, SortedSetEntry<T> b)` — (inheritdoc)

#### class `EpicGames.Redis.RedisSortedSetKeyExtensions`  
`public static class RedisSortedSetKeyExtensions`  
_public; L127-371_
- desc: Extension methods for sets
- L132 _public method_ `public static Condition SortedSetContains<TElement>(this RedisSortedSetKey<TElement> key, TElement value)` — (inheritdoc)
- L136 _public method_ `public static Condition SortedSetEqual<TElement>(this RedisSortedSetKey<TElement> key, TElement value, RedisValue score)` — (inheritdoc)
- L140 _public method_ `public static Condition SortedSetLengthEqual<TElement>(this RedisSortedSetKey<TElement> key, long length)` — (inheritdoc)
- L144 _public method_ `public static Condition SortedSetLengthGreaterThan<TElement>(this RedisSortedSetKey<TElement> key, long length)` — (inheritdoc)
- L148 _public method_ `public static Condition SortedSetLengthLessThan<TElement>(this RedisSortedSetKey<TElement> key, long length)` — (inheritdoc)
- L152 _public method_ `public static Condition SortedSetNotContains<TElement>(this RedisSortedSetKey<TElement> key, TElement value)` — (inheritdoc)
- L156 _public method_ `public static Condition SortedSetNotEqual<TElement>(this RedisSortedSetKey<TElement> key, TElement value, RedisValue score)` — (inheritdoc)
- L160 _public method_ `public static Condition SortedSetScoreExists<TElement>(this RedisSortedSetKey<TElement> key, RedisValue score)` — (inheritdoc)
- L164 _public method_ `public static Condition SortedSetScoreExists<TElement>(this RedisSortedSetKey<TElement> key, RedisValue score, RedisValue count)` — (inheritdoc)
- L172-175 _public method_ `public static Task<bool> SortedSetAddAsync<TElement>(this IDatabaseAsync target, RedisSortedSetKey<TElement> key, TElement value, double score, SortedSetWhen when = SortedSetWhen.Always, CommandFlags flags = CommandFlags.None)` — (inheritdoc)
- L178-181 _public method_ `public static Task<long> SortedSetAddAsync<TElement>(this IDatabaseAsync target, RedisSortedSetKey<TElement> key, SortedSetEntry<TElement>[] values, SortedSetWhen when = SortedSetWhen.Always, CommandFlags flags = CommandFlags.None)` — (inheritdoc)
- L188-191 _public method_ `public static Task<long> SortedSetLengthAsync<TElement>(this IDatabaseAsync target, RedisSortedSetKey<TElement> key, double min = Double.NegativeInfinity, double max = Double.PositiveInfinity, Exclude exclude = Exclude.None, CommandFlags flags = CommandFlags.None)` — (inheritdoc)
- L198-201 _public method_ `public static Task<long> SortedSetLengthByValueAsync<TElement>(this IDatabaseAsync target, RedisSortedSetKey<TElement> key, TElement min, TElement max, Exclude exclude = Exclude.None, CommandFlags flags = CommandFlags.None)` — (inheritdoc)
- L208-211 _public method_ `public static Task<TElement> SortedSetRandomMemberAsync<TElement>(this IDatabaseAsync target, RedisSortedSetKey<TElement> key, CommandFlags flags = CommandFlags.None)` — (inheritdoc)
- L218-221 _public method_ `public static Task<TElement[]> SortedSetRandomMembersAsync<TElement>(this IDatabaseAsync target, RedisSortedSetKey<TElement> key, long count, CommandFlags flags = CommandFlags.None)` — (inheritdoc)
- L228-231 _public method_ `public static Task<TElement[]> SortedSetRangeByRankAsync<TElement>(this IDatabaseAsync target, RedisSortedSetKey<TElement> key, long start = 0, long stop = -1, Order order = Order.Ascending, CommandFlags flags = CommandFlags.None)` — (inheritdoc)
- L238-242 _public method_ `public static async Task<SortedSetEntry<TElement>[]> SortedSetRangeByRankWithScoresAsync<TElement>(this IDatabaseAsync target, RedisSortedSetKey<TElement> key, long start = 0, long stop = -1, Order order = Order.Ascending, CommandFlags flags = CommandFlags.None)` — (inheritdoc)
- L249-252 _public method_ `public static Task<TElement[]> SortedSetRangeByScoreAsync<TElement>(this IDatabaseAsync target, RedisSortedSetKey<TElement> key, double start = Double.NegativeInfinity, double stop = Double.PositiveInfinity, Exclude exclude = Exclude.None, Order order = Order.Ascending, long skip = 0L, long take = -1L, CommandFlags flags = CommandFlags.None)` — (inheritdoc)
- L259-263 _public method_ `public static async Task<SortedSetEntry<TElement>[]> SortedSetRangeByScoreWithScoresAsync<TElement>(this IDatabaseAsync target, RedisSortedSetKey<TElement> key, double start = Double.NegativeInfinity, double stop = Double.PositiveInfinity, Exclude exclude = Exclude.None, Order order = Order.Ascending, long skip = 0L, long take = -1L, CommandFlags flags = CommandFlags.None)` — (inheritdoc)
- L270-273 _public method_ `public static Task<TElement[]> SortedSetRangeByValueAsync<TElement>(this IDatabaseAsync target, RedisSortedSetKey<TElement> key, TElement min, TElement max, Exclude exclude = Exclude.None, Order order = Order.Ascending, long skip = 0L, long take = -1L, CommandFlags flags = CommandFlags.None)` — (inheritdoc)
- L280-283 _public method_ `public static Task<long?> SortedSetRankAsync<TElement>(this IDatabaseAsync target, RedisSortedSetKey<TElement> key, TElement item, Order order = Order.Ascending, CommandFlags flags = CommandFlags.None)` — (inheritdoc)
- L290-293 _public method_ `public static Task<bool> SortedSetRemoveAsync<TElement>(this IDatabaseAsync target, RedisSortedSetKey<TElement> key, TElement value, CommandFlags flags = CommandFlags.None)` — (inheritdoc)
- L296-299 _public method_ `public static Task<long> SortedSetRemoveAsync<TElement>(this IDatabaseAsync target, RedisSortedSetKey<TElement> key, TElement[] values, CommandFlags flags = CommandFlags.None)` — (inheritdoc)
- L306-309 _public method_ `public static Task<long> SortedSetRemoveRangeByRankAsync<TElement>(this IDatabaseAsync target, RedisSortedSetKey<TElement> key, long start, long stop, CommandFlags flags = CommandFlags.None)` — (inheritdoc)
- L316-319 _public method_ `public static Task<long> SortedSetRemoveRangeByScoreAsync<TElement>(this IDatabaseAsync target, RedisSortedSetKey<TElement> key, double start, double stop, Exclude exclude = Exclude.None, CommandFlags flags = CommandFlags.None)` — (inheritdoc)
- L326-329 _public method_ `public static Task<long> SortedSetRemoveRangeByValueAsync<TElement>(this IDatabaseAsync target, RedisSortedSetKey<TElement> key, TElement min, TElement max, Exclude exclude = Exclude.None, CommandFlags flags = CommandFlags.None)` — (inheritdoc)
- L336-342 _public method_ `public static async IAsyncEnumerable<SortedSetEntry<TElement>> SortedSetScanAsync<TElement>(this IDatabaseAsync target, RedisSortedSetKey<TElement> key, RedisValue pattern = default, int pageSize = 250, long cursor = 0, int pageOffset = 0, CommandFlags flags = CommandFlags.None)` — (inheritdoc)
- L349-352 _public method_ `public static Task<double?> SortedSetScoreAsync<TElement>(this IDatabaseAsync target, RedisSortedSetKey<TElement> key, TElement member, CommandFlags flags = CommandFlags.None)` — (inheritdoc)
- L359-362 _public method_ `public static Task<bool> SortedSetUpdateAsync<TElement>(this IDatabaseAsync target, RedisSortedSetKey<TElement> key, TElement member, double score, SortedSetWhen when = SortedSetWhen.Always, CommandFlags flags = CommandFlags.None)` — (inheritdoc)
- L365-368 _public method_ `public static Task<long> SortedSetUpdateAsync<TElement>(this IDatabaseAsync target, RedisSortedSetKey<TElement> key, SortedSetEntry<TElement>[] values, SortedSetWhen when = SortedSetWhen.Always, CommandFlags flags = CommandFlags.None)` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.Redis/RedisString.cs` (EpicGames.Redis)


#### record struct `EpicGames.Redis.RedisString`  
`public record struct RedisString<TValue>(IDatabaseAsync Database, RedisStringKey<TValue> Key)`  
_public; L15-15_
- desc: Accessor for a typed Redis string

#### class `EpicGames.Redis.RedisStringExtensions`  
`public static class RedisStringExtensions`  
_public; L20-93_
- desc: Extension methods for strings
- L25 _public method_ `public static Condition StringEqual<TElement>(this RedisString<TElement> target, TElement value)` — (inheritdoc)
- L29 _public method_ `public static Condition StringLengthEqual<TElement>(this RedisString<TElement> target, long length)` — (inheritdoc)
- L33 _public method_ `public static Condition StringLengthGreaterThan<TElement>(this RedisString<TElement> target, long length)` — (inheritdoc)
- L37 _public method_ `public static Condition StringLengthLessThan<TElement>(this RedisString<TElement> target, long length)` — (inheritdoc)
- L41 _public method_ `public static Condition StringNotEqual<TElement>(this RedisString<TElement> target, TElement value)` — (inheritdoc)
- L49 _public method_ `public static Task<long> StringDecrementAsync(this RedisString<long> target, long value = 1L, CommandFlags flags = CommandFlags.None)` — (inheritdoc)
- L53 _public method_ `public static Task<double> StringDecrementAsync(this RedisString<double> target, double value = 1.0, CommandFlags flags = CommandFlags.None)` — (inheritdoc)
- L61 _public method_ `public static Task<TValue?> GetAsync<TValue>(this RedisString<TValue> target, CommandFlags flags = CommandFlags.None)` — (inheritdoc)
- L65 _public method_ `public static Task<TValue> GetAsync<TValue>(this RedisString<TValue> target, TValue defaultValue, CommandFlags flags = CommandFlags.None)` — (inheritdoc)
- L73 _public method_ `public static Task<long> IncrementAsync(this RedisString<long> target, long value = 1L, CommandFlags flags = CommandFlags.None)` — (inheritdoc)
- L81 _public method_ `public static Task<long> LengthAsync<TValue>(this RedisString<TValue> target, CommandFlags flags = CommandFlags.None)` — (inheritdoc)
- L89 _public method_ `public static Task<bool> SetAsync<TValue>(this RedisString<TValue> target, TValue value, TimeSpan? expiry = null, When when = When.Always, CommandFlags flags = CommandFlags.None)` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.Redis/RedisStringKey.cs` (EpicGames.Redis)


#### record struct `EpicGames.Redis.RedisStringKey`  
`public record struct RedisStringKey<TValue>(RedisKey Inner) : IRedisTypedKey`  
_public; L15-22_
- inherits: `IRedisTypedKey`
- desc: Represents a typed Redis string with a given value type
- L21 _public operator_ `public static implicit operator RedisStringKey<TValue>(string key)` — Implicit conversion to typed redis key.

#### class `EpicGames.Redis.RedisStringKeyExtensions`  
`public static class RedisStringKeyExtensions`  
_public; L27-154_
- desc: Extension methods for strings
- L32 _public method_ `public static Condition StringEqual<TElement>(this RedisStringKey<TElement> key, TElement value)` — (inheritdoc)
- L36 _public method_ `public static Condition StringLengthEqual<TElement>(this RedisStringKey<TElement> key, long length)` — (inheritdoc)
- L40 _public method_ `public static Condition StringLengthGreaterThan<TElement>(this RedisStringKey<TElement> key, long length)` — (inheritdoc)
- L44 _public method_ `public static Condition StringLengthLessThan<TElement>(this RedisStringKey<TElement> key, long length)` — (inheritdoc)
- L48 _public method_ `public static Condition StringNotEqual<TElement>(this RedisStringKey<TElement> key, TElement value)` — (inheritdoc)
- L56-59 _public method_ `public static Task<long> StringDecrementAsync(this IDatabaseAsync target, RedisKey key, long value = 1L, CommandFlags flags = CommandFlags.None)` — (inheritdoc)
- L62-65 _public method_ `public static Task<long> StringDecrementAsync(this IDatabaseAsync target, RedisStringKey<long> key, long value = 1L, CommandFlags flags = CommandFlags.None)` — (inheritdoc)
- L68-71 _public method_ `public static Task<double> StringDecrementAsync(this IDatabaseAsync target, RedisStringKey<double> key, double value = 1.0, CommandFlags flags = CommandFlags.None)` — (inheritdoc)
- L78-86 _public method_ `public static async Task<TValue?> StringGetAsync<TValue>(this IDatabaseAsync target, RedisStringKey<TValue> key, CommandFlags flags = CommandFlags.None)` — (inheritdoc)
- L89-97 _public method_ `public static async Task<TValue> StringGetAsync<TValue>(this IDatabaseAsync target, RedisStringKey<TValue> key, TValue defaultValue, CommandFlags flags = CommandFlags.None)` — (inheritdoc)
- L104-107 _public method_ `public static Task<long> StringIncrementAsync(this IDatabaseAsync target, RedisKey key, long value = 1L, CommandFlags flags = CommandFlags.None)` — (inheritdoc)
- L110-113 _public method_ `public static Task<long> StringIncrementAsync(this IDatabaseAsync target, RedisStringKey<long> key, long value = 1L, CommandFlags flags = CommandFlags.None)` — (inheritdoc)
- L116-119 _public method_ `public static Task<double> StringIncrementAsync(this IDatabaseAsync target, RedisKey key, double value, CommandFlags flags = CommandFlags.None)` — (inheritdoc)
- L122-125 _public method_ `public static Task<double> StringIncrementAsync(this IDatabaseAsync target, RedisStringKey<double> key, double value = 1.0, CommandFlags flags = CommandFlags.None)` — (inheritdoc)
- L132-135 _public method_ `public static Task<long> StringLengthAsync<TValue>(this IDatabaseAsync target, RedisStringKey<TValue> key, CommandFlags flags = CommandFlags.None)` — (inheritdoc)
- L142-145 _public method_ `public static Task<bool> StringSetAsync<TValue>(this IDatabaseAsync target, RedisStringKey<TValue> key, TValue value, TimeSpan? expiry = null, When when = When.Always, CommandFlags flags = CommandFlags.None)` — (inheritdoc)
- L148-151 _public method_ `public static Task<bool> StringSetAsync<TValue>(this IDatabaseAsync target, KeyValuePair<RedisStringKey<TValue>, TValue>[] pairs, When when = When.Always, CommandFlags flags = CommandFlags.None)` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.Redis/RedisSubscription.cs` (EpicGames.Redis)


#### class `EpicGames.Redis.RedisSubscription`  
`public sealed class RedisSubscription : IDisposable, IAsyncDisposable`  
_public; L12-74_
- inherits: `IDisposable, IAsyncDisposable`
- desc: Subscription to a RedisChannel
- L14 _private* field_ `ISubscriber? _subscriber`
- L15 _private* field_ `readonly RedisChannel _channel`
- L16 _private* field_ `readonly Action<RedisChannel, RedisValue> _handler`
- L16 _private* field_ `readonly Action< _handler`
- L21 _public property_ `public RedisChannel Channel => ...` — Accessor for the channel
- L28-32 _public ctor_ `public RedisSubscription(RedisChannel channel, Action<RedisChannel, RedisValue> handler)` — Constructor
- L35-38 _public method_ `public void Dispose()` — (inheritdoc)
- L41-44 _public method_ `public async ValueTask DisposeAsync()` — (inheritdoc)
- L51-60 _public method_ `public async Task SubscribeAsync(ISubscriber subscriber, CommandFlags flags = CommandFlags.None)` — Subscribes to the channel
- L66-73 _public method_ `public async Task UnsubscribeAsync(CommandFlags flags = CommandFlags.None)` — Unsubscribe from the channel

#### class `EpicGames.Redis.RedisSubscriptionExtensions`  
`public static class RedisSubscriptionExtensions`  
_public; L79-112_
- desc: Extension methods for typed lists
- L84-87 _public method_ `public static Task<RedisSubscription> SubscribeAsync(this IConnectionMultiplexer connection, RedisChannel channel, Action<RedisValue> handler, CommandFlags flags = CommandFlags.None)` — (inheritdoc)
- L90-95 _public method_ `public static async Task<RedisSubscription> SubscribeAsync(this IConnectionMultiplexer connection, RedisChannel channel, Action<RedisChannel, RedisValue> handler, CommandFlags flags = CommandFlags.None)` — (inheritdoc)
- L98-102 _public method_ `public static Task<RedisSubscription> SubscribeAsync<T>(this IConnectionMultiplexer connection, RedisChannel<T> channel, Action<T> handler, CommandFlags flags = CommandFlags.None)` — (inheritdoc)
- L105-109 _public method_ `public static Task<RedisSubscription> SubscribeAsync<T>(this IConnectionMultiplexer connection, RedisChannel<T> channel, Action<RedisChannel<T>, T> handler, CommandFlags flags = CommandFlags.None)` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.Redis/Utility/RedisEvent.cs` (EpicGames.Redis)


#### class `EpicGames.Redis.RedisEvent`  
`public sealed class RedisEvent : IAsyncDisposable`  
_public; L14-66_
- inherits: `IAsyncDisposable`
- desc: Distributed version of AsyncEvent. The event will be pulsed via a pub/sub channel in Redis.
- L16 _private* field_ `readonly IConnectionMultiplexer _multiplexer`
- L17 _private* field_ `readonly RedisChannel _channel`
- L18 _private* field_ `readonly AsyncEvent _asyncEvent`
- L19 _private* field_ `readonly RedisSubscription _subscription`
- L24 _public property_ `public Task Task => ...` — Accessor for the inner task. Can be captured and awaited by clients.
- L26-32 _private* ctor_ `RedisEvent(IConnectionMultiplexer multiplexer, RedisChannel channel, AsyncEvent asyncEvent, RedisSubscription subscription)`
- L35 _public method_ `public ValueTask DisposeAsync()` — (inheritdoc)
- L45-57 _public method_ `public static async Task<RedisEvent> CreateAsync(IConnectionMultiplexer multiplexer, RedisChannel channel, CancellationToken cancellationToken = default)` — Create a new async event using the given channel name
- L62-65 _public method_ `public void Pulse()` — Pulse the event, allowing any captured copies of the task to continue.

### `Source/Programs/Shared/EpicGames.Redis/Utility/RedisLock.cs` (EpicGames.Redis)


#### class `EpicGames.Redis.Utility.RedisLock`  
`public class RedisLock : IAsyncDisposable, IDisposable`  
_public; L14-119_
- inherits: `IAsyncDisposable, IDisposable`
- desc: Implements a named single-entry lock which expires after a period of time if the process terminates.
- L16 _private* field_ `readonly IDatabase _database`
- L17 _private* field_ `readonly RedisKey _key`
- L18 _private* field_ `CancellationTokenSource? _cancellationSource`
- L19 _private* field_ `Task? _backgroundTask`
- L26-30 _public ctor_ `public RedisLock(IDatabase database, RedisKey key)` — Constructor
- L33-37 _public method_ `public void Dispose()` — (inheritdoc)
- L43-49 _protected method_ `protected virtual void Dispose(bool disposing)` — Dispose pattern
- L52-67 _public method_ `public async ValueTask DisposeAsync()` — (inheritdoc)
- L75-84 _public method_ `public async ValueTask<bool> AcquireAsync(TimeSpan duration, bool releaseOnDispose = true)` — Attempts to acquire the lock for the given period of time. The lock will be renewed once half of this interval has elapsed.
- L93-118 _private* method_ `async Task RenewAsync(TimeSpan duration, bool releaseOnDispose, CancellationToken cancellationToken)` — Background task which renews the lock while the service is running

#### class `EpicGames.Redis.Utility.RedisLock`  
`public class RedisLock<T> : RedisLock`  
_public; L125-137_
- inherits: `RedisLock`
- desc: Implements a named single-entry lock which expires after a period of time if the process terminates.
- L133-136 _public ctor_ `public RedisLock(IDatabase database, RedisKey baseKey, T value) : base(database, baseKey.Append(RedisSerializer.Serialize<T>(value).AsKey()))` — Constructor

### `Source/Programs/Shared/EpicGames.Redis/Utility/RedisQueue.cs` (EpicGames.Redis)


#### class `EpicGames.Redis.Utility.RedisQueue`  
`public static class RedisQueue`  
_public; L13-27_
- desc: Utility method for queue instances
- L22-26 _public method_ `public static async Task<RedisQueue<T>> CreateAsync<T>(IConnectionMultiplexer multiplexer, RedisKey queueKey, RedisChannel eventChannel, CancellationToken cancellationToken = default)` — Create a new queue instance

#### class `EpicGames.Redis.Utility.RedisQueue`  
`public sealed class RedisQueue<T> : IAsyncDisposable`  
_public; L33-87_
- inherits: `IAsyncDisposable`
- desc: Implements a waitable FIFO queue with Redis. Wraps a pub/sub channel and list, ensuring that each item is only popped from the queue once.
- L35 _private* field_ `readonly IConnectionMultiplexer _multiplexer`
- L36 _private* field_ `readonly RedisEvent _asyncEvent`
- L37 _private* field_ `readonly RedisListKey<T> _listKey`
- L39-44 _internal ctor_ `internal RedisQueue(IConnectionMultiplexer multiplexer, RedisEvent asyncEvent, RedisListKey<T> listKey)`
- L47 _public method_ `public ValueTask DisposeAsync()` — (inheritdoc)
- L55-60 _public method_ `public async Task PushAsync(T item, CommandFlags flags = CommandFlags.None)` — Push a new item onto the queue
- L65-71 _public method_ `public async Task<T> TryPopAsync(CancellationToken cancellationToken = default)` — Attempt to pop an item from the front of the queue. Returns the default value for the item if the queue is empty.
- L77-86 _public method_ `public async Task WaitForDataAsync(CancellationToken cancellationToken = default)` — Wait for a new item to be pushed onto the queue
