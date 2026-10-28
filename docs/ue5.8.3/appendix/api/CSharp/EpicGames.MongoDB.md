# CSharp / EpicGames.MongoDB

- project root: `Source/Programs/Shared/EpicGames.MongoDB`
- files: 4; symbols: 49
- symbol kinds: class=9, ctor=6, field=5, interface=1, method=22, property=6
- access marked `*` is implicit (not written in source)

### `Source/Programs/Shared/EpicGames.MongoDB/MongoExtensions.cs` (EpicGames.MongoDB)


#### class `EpicGames.MongoDB.MongoExtensions`  
`public static class MongoExtensions`  
_public; L14-138_
- desc: Extension methods for MongoDB
- L23-34 _public method_ `public static IFindFluent<TDocument, TProjection> Range<TDocument, TProjection>(this IFindFluent<TDocument, TProjection> query, int? index, int? count)` — Filters the documents returned from a search
- L41-55 _public method_ `public static async Task<List<TResult>> ToListAsync<TDocument, TResult>(this IAsyncCursorSource<TDocument> query) where TDocument : TResult` — Filters the documents returned from a search
- L64-82 _public method_ `public static async Task<bool> InsertOneIgnoreDuplicatesAsync<TDocument>(this IMongoCollection<TDocument> collection, TDocument newDocument)` — Attempts to insert a document into a collection, handling the error case that a document with the given key already exists
- L93-103 _public method_ `public static UpdateDefinition<TDocument> SetOrUnsetNull<TDocument, TField>(this UpdateDefinitionBuilder<TDocument> updateBuilder, Expression<Func<TDocument, TField?>> field, TField? value) where TField : struct` — Sets a field to a value, or unsets it if the value is null
- L114-124 _public method_ `public static UpdateDefinition<TDocument> SetOrUnsetNullRef<TDocument, TField>(this UpdateDefinitionBuilder<TDocument> updateBuilder, Expression<Func<TDocument, TField?>> field, TField? value) where TField : class` — Sets a field to a value, or unsets it if the value is null
- L134-137 _public method_ `public static FilterDefinition<TDocument> Expr<TDocument>(this FilterDefinitionBuilder<TDocument> filter, Expression<Func<TDocument, bool>> expression)` — attrs: `[System.Diagnostics.CodeAnalysis.SuppressMessage("Style", "IDE0060:Remove unused parameter")]` — Creates a filter definition from a linq expression. This is not generally explicitly castable, so expose it as a FilterDefinitionBuilder method.

### `Source/Programs/Shared/EpicGames.MongoDB/ObjectIdHelpers.cs` (EpicGames.MongoDB)


#### class `EpicGames.MongoDB.ObjectIdHelpers`  
`static class ObjectIdHelpers`  
_internal*; L7-20_
- L9-19 _public method_ `public static ObjectId ToObjectId(this string text)`

### `Source/Programs/Shared/EpicGames.MongoDB/SingletonDocument.cs` (EpicGames.MongoDB)


#### class `EpicGames.MongoDB.SingletonDocumentAttribute`  
`public sealed class SingletonDocumentAttribute : Attribute`  
_public; L17-32_
- attrs: `[AttributeUsage(AttributeTargets.Class)]`
- inherits: `Attribute`
- desc: Attribute specifying the unique id for a singleton document
- L22 _public property_ `public string Id { get; }` — Unique id for the singleton document
- L28-31 _public ctor_ `public SingletonDocumentAttribute(string id)` — Constructor

#### class `EpicGames.MongoDB.SingletonBase`  
`public class SingletonBase`  
_public; L37-89_
- desc: Base class for singletons
- L42 _public property_ `public ObjectId Id { get; set; }` — Unique id of the
- L47 _public property_ `public int Revision { get; set; }` — Current revision number
- L53-55 _protected ctor_ `protected SingletonBase()` — attrs: `[BsonConstructor]` — Private constructor for serialization
- L61-64 _public ctor_ `public SingletonBase(ObjectId id)` — Constructor
- L85-88 _public method_ `public static ObjectId GetId<T>() where T : SingletonBase` — Gets the id for a singleton type

#### class `EpicGames.MongoDB.SingletonBase.CachedId`  
`class CachedId<T>`  
_private*; L69-78_
- desc: Base class for singleton documents
- L71 _public property_ `public static ObjectId Value { get; }`
- L73-77 _private* method_ `static ObjectId GetSingletonId()`

#### interface `EpicGames.MongoDB.ISingletonDocument`  
`public interface ISingletonDocument<T>`  
_public; L95-109_
- desc: Interface for the getting and setting the singleton
- L101 _public* method_ `Task<T> GetAsync()` — Gets the current document
- L108 _public* method_ `Task<bool> TryUpdateAsync(T value)` — Attempts to update the document

#### class `EpicGames.MongoDB.SingletonDocument`  
`public class SingletonDocument<T> : ISingletonDocument<T> where T : SingletonBase, new()`  
_public; L115-186_
- inherits: `ISingletonDocument<T>`
- constraints: `where T : SingletonBase, new()`
- desc: Concrete implementation of ISingletonDocument{T}
- L120 _private* field_ `readonly IMongoCollection<T> _collection` — The database service instance
- L125 _private* field_ `readonly ObjectId _objectId` — Unique id for the singleton document
- L130-133 _private* ctor_ `static SingletonDocument()` — Static constructor. Registers the document using the automapper.
- L139-145 _public ctor_ `public SingletonDocument(IMongoCollection<SingletonBase> collection)` — Constructor
- L148-162 _public method_ `public async Task<T> GetAsync()` — (inheritdoc)
- L165-185 _public method_ `public async Task<bool> TryUpdateAsync(T value)` — (inheritdoc)

### `Source/Programs/Shared/EpicGames.MongoDB/TransactionBuilder.cs` (EpicGames.MongoDB)


#### class `EpicGames.MongoDB.TransactionBuilder`  
`public class TransactionBuilder<TDocument> where TDocument : class`  
_public; L16-299_
- constraints: `where TDocument : class`
- desc: Allows building a transactional MongoDB update of several fields, and applying those to an in-memory object. Useful for transactional updates.
- L76 _private* field_ `readonly List<FieldUpdate> _fieldUpdates = []` — List of field updates
- L81 _public property_ `public bool IsEmpty => ...` — Whether the transaction is currenty empty
- L89-94 _public method_ `public void Set<TField>(Expression<Func<TDocument, TField>> expr, TField value)` — Adds a setting to this transaction
- L100-105 _public method_ `public void Unset(Expression<Func<TDocument, object>> expr)` — Adds an update to remove a field
- L112-129 _public method_ `public void UpdateDictionary<TKey, TValue>(Expression<Func<TDocument, Dictionary<TKey, TValue>>> expr, IEnumerable<KeyValuePair<TKey, TValue?>> updates) where TKey : class where TValue : class` — Updates a property dictionary with a set of adds and removes
- L135-141 _public method_ `public void ApplyTo(TDocument target)` — Applies this transaction to the given update
- L149-190 _private* method_ `static void Assign(object? target, LambdaExpression fieldExpression, object? value)` — Assign a value to a field
- L197-237 _private* method_ `static void Unassign(object? target, Expression body)` — Removes an entry from a dictionary
- L245-290 _private* method_ `static object? Evaluate(Expression expression, object? parameter)` — Evaluates an expression
- L295-298 _public method_ `public UpdateDefinition<TDocument> ToUpdateDefinition()` — Converts this transaction to an update definition

#### class `EpicGames.MongoDB.TransactionBuilder.FieldUpdate`  
`class FieldUpdate`  
_private*; L21-43_
- desc: Information about an update to a field
- L26 _public field_ `public UpdateDefinition<TDocument> _update` — The update definition
- L31 _public field_ `public Action<object> _apply` — Applies an update to the given object
- L38-42 _public ctor_ `public FieldUpdate(UpdateDefinition<TDocument> update, Action<object> apply)` — Constructor

#### class `EpicGames.MongoDB.TransactionBuilder.Reflection`  
`static class Reflection<T>`  
_private*; L49-71_
- desc: Helper class for determining the indexer for a particular type
- L54 _public property_ `public static PropertyInfo Indexer { get; }` — Caches the indexer for this type
- L60-70 _private* method_ `static PropertyInfo GetIndexerProperty()` — Finds the indexer property from a type
