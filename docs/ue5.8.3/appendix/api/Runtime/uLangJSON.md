# Runtime / uLangJSON

- module root: `Source/Runtime/Solaris/uLangJSON`
- headers: 1; symbols: 31
- symbol kinds: class=1, function=20, namespace=1, prototype=2, typedef=7
- PublicDependencyModuleNames: Core, RapidJSON, uLangCore

### `Source/Runtime/Solaris/uLangJSON/Public/uLang/JSON/JSON.h` (Public)


#### class `uLang::JSONAllocator`  
`class JSONAllocator`  
_L24-39_
- desc: Custom allocator class that routes RapidJSON allocations through the uLang memory interface
- L27 _public function_ `static void* Malloc(size_t Size)`
- L31 _public function_ `static void* Realloc(void* OriginalPtr, size_t OriginalSize, size_t NewSize)`
- L35 _public function_ `static void Free(void* Ptr)`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace uLang`
- L41 _typedef_ `using JSONMemoryPoolAllocator = rapidjson::MemoryPoolAllocator<JSONAllocator>;` (scope `uLang`)
- L42 _typedef_ `using JSONDocument = rapidjson::GenericDocument<rapidjson::UTF8<char>, JSONMemoryPoolAllocator, JSONAllocator>;` (scope `uLang`)
- L43 _typedef_ `using JSONGenericMemberIterator = rapidjson::GenericMemberIterator<false, rapidjson::UTF8<char>, JSONMemoryPoolAllocator>;` (scope `uLang`)
- L44 _typedef_ `using JSONValue = JSONDocument::ValueType;` (scope `uLang`)
- L45 _typedef_ `using JSONStringBuffer = rapidjson::StringBuffer;` (scope `uLang`)
- L46 _typedef_ `using JSONStringWriter = rapidjson::PrettyWriter<JSONStringBuffer>;` (scope `uLang`)
- L47 _typedef_ `using JSONStringRef = rapidjson::GenericStringRef<char>;` (scope `uLang`)
- L56 _prototype_ `CUTF8String EscapeJSON(const CUTF8StringView& RawText);` (scope `uLang`) — Given a raw string, return the escaped JSON encoded string (using backslashes)
- L59 _prototype_ `CUTF8String EscapeJSON(const UTF8Char Ch);` (scope `uLang`) — @overload
- L71 _function_ `inline bool FromJSON(const JSONValue& JSON, bool* Value)` (scope `uLang`) — Read a bool from JSON
- L84 _function_ `inline bool FromJSON(const JSONValue& JSON, int* Value)` (scope `uLang`) — Read an integer from JSON
- L97 _function_ `inline bool FromJSON(const JSONValue& JSON, uint32_t* Value)` (scope `uLang`) — Read an unsigned 32-bit integer from JSON
- L110 _function_ `inline bool FromJSON(const JSONValue& JSON, uint64_t* Value)` (scope `uLang`) — Read an unsigned 64-bit integer from JSON
- L123 _function_ `inline bool FromJSON(const JSONValue& JSON, CUTF8String* Value)` (scope `uLang`) — Read a string from JSON
- L133 _function_ `inline bool FromJSON(const JSONValue& JSON, CUTF8StringView* Value)` (scope `uLang`)
- L147 _function_ `template<class T> bool FromJSON(const JSONValue& JSON, TOptional<T>* OptionalValue)` (scope `uLang`) — Read an optional from JSON (which can be null meaning it's unset)
- L169 _function_ `template<class T> bool FromJSON(const JSONValue& JSON, TArray<T>* ArrayValue)` (scope `uLang`) — Read an array from JSON
- L191 _function_ `template<class T> bool FromJSON(const JSONValue& JSON, const char* MemberName, T* MemberValue, TOptional<bool> bRequired = EResult::Unspecified)` (scope `uLang`) — Read member of a JSON object
- L211 _function_ `inline bool ToJSON(bool Value, JSONValue* JSON, JSONMemoryPoolAllocator&)` (scope `uLang`) — Write a bool to JSON
- L225 _function_ `inline bool ToJSON(int Value, JSONValue* JSON, JSONMemoryPoolAllocator&)` (scope `uLang`) — Write an integer to JSON
- L239 _function_ `inline bool ToJSON(uint32_t Value, JSONValue* JSON, JSONMemoryPoolAllocator&)` (scope `uLang`) — Write an unsigned integer to JSON
- L253 _function_ `inline bool ToJSON(CUTF8StringView Value, JSONValue* JSON, JSONMemoryPoolAllocator& Allocator)` (scope `uLang`) — Write a string to JSON
- L268 _function_ `template<class T> bool ToJSON(const TOptional<T>& OptionalValue, JSONValue* JSON, JSONMemoryPoolAllocator& Allocator)` (scope `uLang`) — Write an optional to JSON (which can be null meaning it's unset)
- L287 _function_ `template<class T> bool ToJSON(const TArray<T>& ArrayValue, JSONValue* JSON, JSONMemoryPoolAllocator& Allocator)` (scope `uLang`) — Write an array to JSON
- L315 _function_ `template<class T> bool ToJSON(const T& MemberValue, const char* MemberName, JSONValue* JSON, JSONMemoryPoolAllocator& Allocator)` (scope `uLang`) — Write member of a JSON object
- L337 _function_ `template<class T> bool ToJSON(const TOptional<T>& MemberValue, const char* MemberName, JSONValue* JSON, JSONMemoryPoolAllocator& Allocator)` (scope `uLang`) — Write optional member of a JSON object
