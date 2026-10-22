# Runtime / Json

- module root: `Source/Runtime/Json`
- headers: 22; symbols: 862
- symbol kinds: class=23, delegate=4, enum=4, enumerator=31, function=306, macro=45, member=49, namespace=17, prototype=307, struct=20, typedef=56
- PrivateDependencyModuleNames: TraceLog
- PublicDependencyModuleNames: Core, RapidJSON

### `Source/Runtime/Json/Public/Dom/JsonObject.h` (Public)


#### class `UE::JSON::Private::FJsonStringSet`  
`class FJsonStringSet`  
_L59-80_
- desc: A set of shared strings that appear as keys in a FJsonObject. They are shared among the entire Json structure to reduce memory usage.
- L62 _public prototype_ `UE::FSharedString Place(FStringView Text);`
- L63 _public prototype_ `SIZE_T GetAllocatedSize() const;`
- L79 _private member_ `TCompactSet<UE::FSharedString, FCaseSensitiveStringKeyFuncs> Strings;`

#### struct `UE::JSON::Private::FJsonStringSet::FCaseSensitiveStringKeyFuncs`  
`struct FCaseSensitiveStringKeyFuncs : BaseKeyFuncs<UE::FSharedString, UE::FSharedString>`  
_L66-77_
- inherits: `BaseKeyFuncs<UE::FSharedString,UE::FSharedString>`
- desc: Case sensitive hashing function for TSet
- L68 _public function_ `static FORCEINLINE const UE::FSharedString& GetSetKey(const UE::FSharedString& Element)`
- L72 _public function_ `static FORCEINLINE bool Matches(const UE::FSharedString& A, const UE::FSharedString& B)`
- L76 _public prototype_ `static uint32 GetKeyHash(const UE::FSharedString& Key);`

#### class `UE::JSON::Private::FJsonObjectSharedStringStorage`  
`class FJsonObjectSharedStringStorage`  
_L86-238_
- desc: Base class for UE::FSharedString based FJsonObject. This class will go away in a future release. Only use FJsonObject directly.
- L88 _private member_ `TSharedPtr<UE::JSON::Private::FJsonStringSet> StringSet;`
- L89 _private function_ `TSharedPtr<UE::JSON::Private::FJsonStringSet> GetOrAddStringSet()`
- L99 _public typedef_ `using FStringType = UE::FSharedString;`
- L102 _public prototype_ `FJsonObjectSharedStringStorage() = default;` — Default constructor
- L105 _public prototype_ `explicit FJsonObjectSharedStringStorage(TSharedPtr<UE::JSON::Private::FJsonStringSet> StringSet);` — Constructor taking a shared stringset that's shared with other json objects.
- L110 _public function_ `TSharedPtr<UE::JSON::Private::FJsonStringSet> GetStringSet() const` — Returns the stringset used to store shared key strings. Can be a null pointer if no keys were added yet.
- L118 _public function_ `SIZE_T GetMemoryFootprint() const` — Returns the memory footprint for this object in Bytes, including sizeof(*this) and allocated memory.
- L124 _public prototype_ `SIZE_T GetAllocatedSize() const;` — Helper to calculate allocated size of the Values map and its contents
- L131 _public prototype_ `void SetField(FStringView FieldName, const TSharedPtr<FJsonValue>& Value);` — Sets the generic json value of the field with the specified name. @param FieldName The name of the field to set. @param Value The value to set.
- L132 _public function_ `UE_DEPRECATED(5.8, "Use SetField(FStringView, ...)") UE_REWRITE void SetField(const ANSICHAR* FieldName, const TSharedPtr<FJsonValue>& Value)`
- L142 _public prototype_ `void SetNumberField(FStringView FieldName, double Number);` — Sets the number value of the field with the specified name. @param FieldName The name of the field to set. @param Value The value to set.
- L143 _public function_ `UE_DEPRECATED(5.8, "Use SetNumberField(FStringView, ...)") UE_REWRITE void SetNumberField(const ANSICHAR* FieldName, double Number)`
- L153 _public prototype_ `void SetStringField(FStringView FieldName, const ANSICHAR* StringValue);` — Sets the string value of the field with the specified name. @param FieldName The name of the field to set. @param Value The value to set.
- L154 _public prototype_ `void SetStringField(FStringView FieldName, const TCHAR* StringValue);`
- L155 _public prototype_ `void SetStringField(FStringView FieldName, const UTF8CHAR* StringValue);`
- L156 _public prototype_ `void SetStringField(FStringView FieldName, FString&& StringValue);`
- L157 _public prototype_ `void SetStringField(FStringView FieldName, const FString& StringValue);`
- L158 _public prototype_ `void SetStringField(FStringView FieldName, FUtf8String&& StringValue);`
- L159 _public prototype_ `void SetStringField(FStringView FieldName, const FUtf8String& StringValue);`
- L160 _public prototype_ `void SetStringField(FStringView FieldName, const UE::FSharedString& StringValue);`
- L161 _public function_ `UE_DEPRECATED(5.8, "Use SetStringField(FStringView, ...)") UE_REWRITE void SetStringField(const ANSICHAR* FieldName, const ANSICHAR* StringValue)`
- L165 _public function_ `UE_DEPRECATED(5.8, "Use SetStringField(FStringView, ...)") UE_REWRITE void SetStringField(const ANSICHAR* FieldName, const TCHAR* StringValue)`
- L169 _public function_ `UE_DEPRECATED(5.8, "Use SetStringField(FStringView, ...)") UE_REWRITE void SetStringField(const ANSICHAR* FieldName, const UTF8CHAR* StringValue)`
- L173 _public function_ `UE_DEPRECATED(5.8, "Use SetStringField(FStringView, ...)") UE_REWRITE void SetStringField(const ANSICHAR* FieldName, FString&& StringValue)`
- L177 _public function_ `UE_DEPRECATED(5.8, "Use SetStringField(FStringView, ...)") UE_REWRITE void SetStringField(const ANSICHAR* FieldName, const FString& StringValue)`
- L181 _public function_ `UE_DEPRECATED(5.8, "Use SetStringField(FStringView, ...)") UE_REWRITE void SetStringField(const ANSICHAR* FieldName, FUtf8String&& StringValue)`
- L185 _public function_ `UE_DEPRECATED(5.8, "Use SetStringField(FStringView, ...)") UE_REWRITE void SetStringField(const ANSICHAR* FieldName, const FUtf8String& StringValue)`
- L189 _public function_ `UE_DEPRECATED(5.8, "Use SetStringField(FStringView, ...)") UE_REWRITE void SetStringField(const ANSICHAR* FieldName, const UE::FSharedString& StringValue)`
- L199 _public prototype_ `void SetBoolField(FStringView FieldName, bool InValue);` — Sets the bool value of the field with the specified name. @param FieldName The name of the field to set. @param Value The value to set.
- L200 _public function_ `UE_DEPRECATED(5.8, "Use SetBoolField(FStringView, ...)") UE_REWRITE void SetBoolField(const ANSICHAR* FieldName, bool InValue)`
- L210 _public prototype_ `void SetArrayField(FStringView FieldName, TArray<TSharedPtr<FJsonValue>>&& Array);` — Sets the array value of the field with the specified name. @param FieldName The name of the field to set. @param Value The value to set.
- L211 _public prototype_ `void SetArrayField(FStringView FieldName, const TArray<TSharedPtr<FJsonValue>>& Array);`
- L212 _public function_ `UE_DEPRECATED(5.8, "Use SetArrayField(FStringView, ...)") UE_REWRITE void SetArrayField(const ANSICHAR* FieldName, TArray<TSharedPtr<FJsonValue>>&& Array)`
- L216 _public function_ `UE_DEPRECATED(5.8, "Use SetArrayField(FStringView, ...)") UE_REWRITE void SetArrayField(const ANSICHAR* FieldName, const TArray<TSharedPtr<FJsonValue>>& Array)`
- L226 _public prototype_ `void SetObjectField(FStringView FieldName, TSharedPtr<FJsonObject>&& JsonObject);` — Sets the object value of the field with the specified name. @param FieldName The name of the field to set. @param Value The value to set.
- L227 _public prototype_ `void SetObjectField(FStringView FieldName, const TSharedPtr<FJsonObject>& JsonObject);`
- L228 _public function_ `UE_DEPRECATED(5.8, "Use SetObjectField(FStringView, ...)") UE_REWRITE void SetObjectField(const ANSICHAR* FieldName, TSharedPtr<FJsonObject>&& JsonObject)`
- L232 _public function_ `UE_DEPRECATED(5.8, "Use SetObjectField(FStringView, ...)") UE_REWRITE void SetObjectField(const ANSICHAR* FieldName, const TSharedPtr<FJsonObject>& JsonObject)`
- L237 _public member_ `TMap<FStringType, TSharedPtr<FJsonValue>> Values;`

#### class `FJsonObject`  
`class FJsonObject #if !UE_JSONOBJECT_LEGACY_STRING_KEYS : public UE::JSON::Private::FJsonObjectSharedStringStorage #else : public UE::JSON::Private::FJsonObjectStringStorage #endif`  
_L322-511_
- inherits: `UE::JSON::Private::FJsonObjectSharedStringStorage`
- desc: A Json Object is a structure holding an unordered set of name/value pairs. Can use either FString (old) or UE::FSharedString (new) as the key type. In a Json file, it is represented by everything between curly braces {}.
- L337 _public function_ `template<EJson JsonType> TSharedPtr<FJsonValue> GetField(FStringView FieldName) const`
- L341 _public prototype_ `TSharedPtr<FJsonValue> GetField(FStringView FieldName, EJson JsonType) const;`
- L346 _public prototype_ `const TSharedPtr<FJsonValue> GetFieldUntyped(FStringView FieldName) const;` — Gets a shared pointer to a field by name, if it exists.
- L354 _public prototype_ `TSharedPtr<FJsonValue> TryGetField(FStringView FieldName) const;` — Attempts to get the field with the specified name. @param FieldName The name of the field to get. @return A pointer to the field, or nullptr if the field doesn't exist.
- L362 _public prototype_ `bool HasField(FStringView FieldName) const;` — Checks whether a field with the specified name exists in the object. @param FieldName The name of the field to check. @return true if the field exists, false otherwise.
- L372 _public function_ `template<EJson JsonType> bool HasTypedField(FStringView FieldName) const` — Checks whether a field with the specified name and type exists in the object. @tparam JsonType The type of the field to check. @param FieldName The name of the field to check. @return true if the field exists, false otherwise.
- L384 _public prototype_ `bool HasTypedField(FStringView FieldName, EJson JsonType) const;` — Checks whether a field with the specified name and type exists in the object. @param JsonType The type of the field to check. @param FieldName The name of the field to check. @return true if the field exists, false otherwise.
- L391 _public prototype_ `void RemoveField(FStringView FieldName);` — Removes the field with the specified name. @param FieldName The name of the field to remove.
- L396 _public prototype_ `void RemoveIf(TFunctionRef<bool(const FStringType&, TSharedPtr<const FJsonValue>)> Predicate);` — Removes all fields the predicate returns true for.
- L406 _public prototype_ `double GetNumberField(FStringView FieldName) const;` — Gets the field with the specified name as a number. Ensures that the field is present and is of type Json number. @param FieldName The name of the field to get. @return The field's value as a number.
- L411 _public prototype_ `int32 GetIntegerField(FStringView FieldName) const;` — Gets a numeric field and casts to an int32
- L414 _public prototype_ `bool TryGetNumberField(FStringView FieldName, float& OutNumber) const;` — Get the field named FieldName as a number. Returns false if it doesn't exist or cannot be converted.
- L417 _public prototype_ `bool TryGetNumberField(FStringView FieldName, double& OutNumber) const;` — Get the field named FieldName as a number. Returns false if it doesn't exist or cannot be converted.
- L420 _public prototype_ `bool TryGetNumberField(FStringView FieldName, int8& OutNumber) const;` — Get the field named FieldName as a number, and makes sure it's within int8 range. Returns false if it doesn't exist or cannot be converted.
- L423 _public prototype_ `bool TryGetNumberField(FStringView FieldName, int16& OutNumber) const;` — Get the field named FieldName as a number, and makes sure it's within int16 range. Returns false if it doesn't exist or cannot be converted.
- L426 _public prototype_ `bool TryGetNumberField(FStringView FieldName, int32& OutNumber) const;` — Get the field named FieldName as a number, and makes sure it's within int32 range. Returns false if it doesn't exist or cannot be converted.
- L429 _public prototype_ `bool TryGetNumberField(FStringView FieldName, int64& OutNumber) const;` — Get the field named FieldName as a number. Returns false if it doesn't exist or cannot be converted.
- L432 _public prototype_ `bool TryGetNumberField(FStringView FieldName, uint8& OutNumber) const;` — Get the field named FieldName as a number, and makes sure it's within uint8 range. Returns false if it doesn't exist or cannot be converted.
- L435 _public prototype_ `bool TryGetNumberField(FStringView FieldName, uint16& OutNumber) const;` — Get the field named FieldName as a number, and makes sure it's within uint16 range. Returns false if it doesn't exist or cannot be converted.
- L438 _public prototype_ `bool TryGetNumberField(FStringView FieldName, uint32& OutNumber) const;` — Get the field named FieldName as a number, and makes sure it's within uint32 range. Returns false if it doesn't exist or cannot be converted.
- L441 _public prototype_ `bool TryGetNumberField(FStringView FieldName, uint64& OutNumber) const;` — Get the field named FieldName as a number, and makes sure it's within uint64 range. Returns false if it doesn't exist or cannot be converted.
- L444 _public prototype_ `FString GetStringField(FStringView FieldName) const;` — Get the field named FieldName as a string.
- L447 _public prototype_ `FUtf8String GetUtf8StringField(FStringView FieldName) const;` — Get the field named FieldName as a UTF8 string.
- L450 _public prototype_ `bool TryGetStringField(FStringView FieldName, FString& OutString) const;` — Get the field named FieldName as a string. Returns false if it doesn't exist or cannot be converted.
- L453 _public prototype_ `bool TryGetStringArrayField(FStringView FieldName, TArray<FString>& OutArray) const;` — Get the field named FieldName as an array of strings. Returns false if it doesn't exist or any member cannot be converted.
- L457 _public function_ `template<typename TEnum> bool TryGetEnumArrayField(FStringView FieldName, TArray<TEnum>& OutArray) const` — Get the field named FieldName as an array of enums. Returns false if it doesn't exist or any member is not a string.
- L485 _public prototype_ `bool GetBoolField(FStringView FieldName) const;` — Gets the field with the specified name as a boolean. Ensures that the field is present and is of type Json number. @param FieldName The name of the field to get. @return The field's value as a boolean.
- L488 _public prototype_ `bool TryGetBoolField(FStringView FieldName, bool& OutBool) const;` — Get the field named FieldName as a string. Returns false if it doesn't exist or cannot be converted.
- L491 _public prototype_ `const TArray<TSharedPtr<FJsonValue>>& GetArrayField(FStringView FieldName) const;` — Get the field named FieldName as an array.
- L494 _public prototype_ `bool TryGetArrayField(FStringView FieldName, const TArray<TSharedPtr<FJsonValue>>*& OutArray) const;` — Try to get the field named FieldName as an array, or return false if it's another type
- L504 _public prototype_ `const TSharedPtr<FJsonObject>& GetObjectField(FStringView FieldName) const;` — Gets the field with the specified name as a Json object. Ensures that the field is present and is of type Json object. @param FieldName The name of the field to get. @return The field's value as a Json object.
- L507 _public prototype_ `bool TryGetObjectField(FStringView FieldName, const TSharedPtr<FJsonObject>*& OutObject) const;` — Try to get the field named FieldName as an object, or return false if it's another type
- L509 _public prototype_ `static void Duplicate(const TSharedPtr<const FJsonObject>& Source, const TSharedPtr<FJsonObject>& Dest);`
- L510 _public prototype_ `static void Duplicate(const TSharedPtr<FJsonObject>& Source, TSharedPtr<FJsonObject>& Dest);`

#### Free symbols / members of external scopes

- L47 _macro_ `#define UE_JSONOBJECT_LEGACY_STRING_KEYS 0`
- L50 _namespace_ `namespace UE`
- L50 _namespace_ `namespace JSON` (scope `UE`)
- L50 _namespace_ `namespace Private` (scope `UE::JSON`)

### `Source/Runtime/Json/Public/Dom/JsonValue.h` (Public)


#### class `FJsonValue`  
`class FJsonValue`  
_L21-160_
- desc: A Json Value is a structure that can be any of the Json Types. It should never be used on its, only its derived types should be used.
- L26 _public prototype_ `double AsNumber() const;` — Returns this value as a double, logging an error and returning zero if this is not an Json Number
- L29 _public prototype_ `FString AsString() const;` — Returns this value as a string, logging an error and returning an empty string if not possible
- L32 _public prototype_ `FUtf8String AsUtf8String() const;` — Returns this value as a utf8 string, logging an error and returning an empty string if not possible
- L35 _public prototype_ `bool AsBool() const;` — Returns this value as a boolean, logging an error and returning false if not possible
- L38 _public prototype_ `const TArray<TSharedPtr<FJsonValue>>& AsArray() const;` — Returns this value as an array, logging an error and returning an empty array reference if not possible
- L41 _public prototype_ `virtual const TSharedPtr<FJsonObject>& AsObject() const;` — Returns this value as an object, throwing an error if this is not an Json Object
- L44 _public prototype_ `virtual bool TryGetNumber(double& OutNumber) const;` — Tries to convert this value to a number, returning false if not possible
- L47 _public prototype_ `virtual bool TryGetNumber(float& OutNumber) const;` — Tries to convert this value to a number, returning false if not possible
- L50 _public prototype_ `virtual bool TryGetNumber(int8& OutNumber) const;` — Tries to convert this value to a number, returning false if not possible
- L53 _public prototype_ `virtual bool TryGetNumber(int16& OutNumber) const;` — Tries to convert this value to a number, returning false if not possible
- L56 _public prototype_ `virtual bool TryGetNumber(int32& OutNumber) const;` — Tries to convert this value to a number, returning false if not possible
- L59 _public prototype_ `virtual bool TryGetNumber(int64& OutNumber) const;` — Tries to convert this value to a number, returning false if not possible
- L62 _public prototype_ `virtual bool TryGetNumber(uint8& OutNumber) const;` — Tries to convert this value to a number, returning false if not possible
- L65 _public prototype_ `virtual bool TryGetNumber(uint16& OutNumber) const;` — Tries to convert this value to a number, returning false if not possible
- L68 _public prototype_ `virtual bool TryGetNumber(uint32& OutNumber) const;` — Tries to convert this value to a number, returning false if not possible
- L71 _public prototype_ `virtual bool TryGetNumber(uint64& OutNumber) const;` — Tries to convert this value to a number, returning false if not possible
- L74 _public prototype_ `virtual bool TryGetString(FString& OutString) const;` — Tries to convert this value to a string, returning false if not possible
- L77 _public prototype_ `virtual bool TryGetUtf8String(FUtf8String& OutString) const;` — Tries to convert this value to a utf8 string, returning false if not possible
- L80 _public prototype_ `virtual bool TryGetBool(bool& OutBool) const;` — Tries to convert this value to a bool, returning false if not possible
- L83 _public prototype_ `virtual bool TryGetArray(const TArray<TSharedPtr<FJsonValue>>*& OutArray) const;` — Tries to convert this value to an array, returning false if not possible
- L86 _public prototype_ `virtual bool TryGetArray(TArray<TSharedPtr<FJsonValue>>*& OutArray);` — Tries to convert this value to an array, returning false if not possible
- L89 _public prototype_ `virtual bool TryGetObject(const TSharedPtr<FJsonObject>*& Object) const;` — Tries to convert this value to an object, returning false if not possible
- L92 _public prototype_ `virtual bool TryGetObject(TSharedPtr<FJsonObject>*& Object);` — Tries to convert this value to an object, returning false if not possible
- L95 _public prototype_ `virtual bool PreferStringRepresentation() const;` — Returns whether or not a caller should prefer a string representation of the value, rather than the natural JSON type
- L98 _public function_ `bool IsNull() const` — Returns true if this value is a 'null'
- L104 _public function_ `void AsArgumentType(double& Value)` — Get a field of the same type as the argument
- L109 _public function_ `void AsArgumentType(FString& Value)`
- L114 _public function_ `void AsArgumentType(bool& Value)`
- L119 _public function_ `void AsArgumentType(TArray<TSharedPtr<FJsonValue>>& Value)`
- L123 _public function_ `void AsArgumentType(TSharedPtr<FJsonObject>& Value)`
- L132 _public prototype_ `virtual SIZE_T GetMemoryFootprint() const;` — Returns the memory footprint for this object in Bytes, including sizeof(*this) and allocated memory. All children should implement this so their memory layout is properly accounted for
- L134 _public member_ `EJson Type;`
- L136 _public prototype_ `static TSharedPtr<FJsonValue> Duplicate(const TSharedPtr<const FJsonValue>& Src);`
- L137 _public prototype_ `static TSharedPtr<FJsonValue> Duplicate(const TSharedPtr<FJsonValue>& Src);`
- L139 _public prototype_ `static bool CompareEqual(const FJsonValue& Lhs, const FJsonValue& Rhs);`
- L144 _protected prototype_ `FJsonValue();`
- L145 _protected prototype_ `virtual ~FJsonValue();`
- L147 _protected prototype_ `virtual FString GetType() const = 0;`
- L149 _protected prototype_ `void ErrorMessage(const FString& InType) const;`

#### class `TJsonValueString`  
`template <typename CharType> class TJsonValueString : public FJsonValue`  
_L164-194_
- inherits: `FJsonValue`
- desc: A Json String Value.
- L167 _public prototype_ `inline TJsonValueString(const TString<CharType>& InString);`
- L168 _public prototype_ `inline TJsonValueString(TString<CharType>&& InString);`
- L170 _public prototype_ `inline virtual bool TryGetString(FString& OutString) const override;`
- L171 _public prototype_ `inline virtual bool TryGetUtf8String(FUtf8String& OutString) const override;`
- L172 _public prototype_ `inline virtual bool TryGetNumber(double& OutDouble) const override;`
- L173 _public prototype_ `inline virtual bool TryGetNumber(int32& OutValue) const override;`
- L174 _public prototype_ `inline virtual bool TryGetNumber(uint32& OutValue) const override;`
- L175 _public prototype_ `inline virtual bool TryGetNumber(int64& OutValue) const override;`
- L176 _public prototype_ `inline virtual bool TryGetNumber(uint64& OutValue) const override;`
- L177 _public prototype_ `inline virtual bool TryGetBool(bool& OutBool) const override;`
- L180 _public function_ `inline bool IsEmpty() const` — Way to check if string value is empty without copying the string
- L185 _public prototype_ `inline virtual SIZE_T GetMemoryFootprint() const override;`
- L188 _protected member_ `TString<CharType> Value;`
- L190 _protected prototype_ `inline virtual FString GetType() const override;`
- L193 _protected prototype_ `inline SIZE_T GetAllocatedSize() const;` — Helper to calculate allocated size of the Value string
- L409 _function_ `template <typename CharType> TJsonValueString<CharType>::TJsonValueString(const TString<CharType>& InString) : Value(InString)`
- L416 _function_ `template <typename CharType> TJsonValueString<CharType>::TJsonValueString(TString<CharType>&& InString) : Value(MoveTemp(InString))`
- L423 _function_ `template <typename CharType> bool TJsonValueString<CharType>::TryGetString(FString& OutString) const`
- L437 _function_ `template <typename CharType> bool TJsonValueString<CharType>::TryGetUtf8String(FUtf8String& OutString) const`
- L451 _function_ `template <typename CharType> bool TJsonValueString<CharType>::TryGetNumber(double& OutDouble) const`
- L465 _function_ `template <typename CharType> bool TJsonValueString<CharType>::TryGetNumber(int32& OutValue) const`
- L472 _function_ `template <typename CharType> bool TJsonValueString<CharType>::TryGetNumber(uint32& OutValue) const`
- L479 _function_ `template <typename CharType> bool TJsonValueString<CharType>::TryGetNumber(int64& OutValue) const`
- L486 _function_ `template <typename CharType> bool TJsonValueString<CharType>::TryGetNumber(uint64& OutValue) const`
- L493 _function_ `template <typename CharType> bool TJsonValueString<CharType>::TryGetBool(bool& OutBool) const`
- L500 _function_ `template <typename CharType> SIZE_T TJsonValueString<CharType>::GetMemoryFootprint() const`
- L506 _function_ `template <typename CharType> FString TJsonValueString<CharType>::GetType() const`
- L512 _function_ `template <typename CharType> SIZE_T TJsonValueString<CharType>::GetAllocatedSize() const`

#### class `FJsonValueNumber`  
`class FJsonValueNumber : public FJsonValue`  
_L199-215_
- inherits: `FJsonValue`
- desc: /  A Json Number Value.
- L202 _public prototype_ `FJsonValueNumber(double InNumber);`
- L203 _public prototype_ `virtual ~FJsonValueNumber();`
- L205 _public prototype_ `virtual bool TryGetNumber(double& OutNumber) const override;`
- L206 _public prototype_ `virtual bool TryGetBool(bool& OutBool) const override;`
- L207 _public prototype_ `virtual bool TryGetString(FString& OutString) const override;`
- L208 _public prototype_ `virtual bool TryGetUtf8String(FUtf8String& OutString) const override;`
- L209 _public prototype_ `virtual SIZE_T GetMemoryFootprint() const override;`
- L212 _protected member_ `double Value;`
- L214 _protected prototype_ `virtual FString GetType() const override;`

#### class `TJsonValueNumberString`  
`template <typename CharType> class TJsonValueNumberString : public FJsonValue`  
_L219-248_
- inherits: `FJsonValue`
- desc: A Json Number Value, stored internally as a string so as not to lose precision
- L222 _public prototype_ `inline TJsonValueNumberString(const TString<CharType>& InString);`
- L223 _public prototype_ `inline TJsonValueNumberString(TString<CharType>&& InString);`
- L225 _public prototype_ `inline virtual bool TryGetString(FString& OutString) const override;`
- L226 _public prototype_ `inline virtual bool TryGetUtf8String(FUtf8String& OutString) const override;`
- L227 _public prototype_ `inline virtual bool TryGetNumber(double& OutDouble) const override;`
- L228 _public prototype_ `inline virtual bool TryGetNumber(float &OutDouble) const override;`
- L229 _public prototype_ `inline virtual bool TryGetNumber(int8& OutValue) const override;`
- L230 _public prototype_ `inline virtual bool TryGetNumber(int16& OutValue) const override;`
- L231 _public prototype_ `inline virtual bool TryGetNumber(int32& OutValue) const override;`
- L232 _public prototype_ `inline virtual bool TryGetNumber(int64& OutValue) const override;`
- L233 _public prototype_ `inline virtual bool TryGetNumber(uint8& OutValue) const override;`
- L234 _public prototype_ `inline virtual bool TryGetNumber(uint16& OutValue) const override;`
- L235 _public prototype_ `inline virtual bool TryGetNumber(uint32& OutValue) const override;`
- L236 _public prototype_ `inline virtual bool TryGetNumber(uint64& OutValue) const override;`
- L237 _public prototype_ `inline virtual bool TryGetBool(bool& OutBool) const override;`
- L238 _public prototype_ `inline virtual bool PreferStringRepresentation() const override;`
- L239 _public prototype_ `inline virtual SIZE_T GetMemoryFootprint() const override;`
- L242 _protected member_ `TString<CharType> Value;`
- L244 _protected prototype_ `inline virtual FString GetType() const override;`
- L247 _protected prototype_ `inline SIZE_T GetAllocatedSize() const;` — Helper to calculate allocated size of the Value string
- L545 _function_ `template <typename CharType> TJsonValueNumberString<CharType>::TJsonValueNumberString(const TString<CharType>& InString) : Value(InString)`
- L552 _function_ `template <typename CharType> TJsonValueNumberString<CharType>::TJsonValueNumberString(TString<CharType>&& InString) : Value(MoveTemp(InString))`
- L559 _function_ `template <typename CharType> bool TJsonValueNumberString<CharType>::TryGetString(FString& OutString) const`
- L573 _function_ `template <typename CharType> bool TJsonValueNumberString<CharType>::TryGetUtf8String(FUtf8String& OutString) const`
- L587 _function_ `template <typename CharType> bool TJsonValueNumberString<CharType>::TryGetNumber(double& OutDouble) const`
- L593 _function_ `template <typename CharType> bool TJsonValueNumberString<CharType>::TryGetNumber(float& OutDouble) const`
- L599 _function_ `template <typename CharType> bool TJsonValueNumberString<CharType>::TryGetNumber(int8& OutValue) const`
- L605 _function_ `template <typename CharType> bool TJsonValueNumberString<CharType>::TryGetNumber(int16& OutValue) const`
- L611 _function_ `template <typename CharType> bool TJsonValueNumberString<CharType>::TryGetNumber(int32& OutValue) const`
- L617 _function_ `template <typename CharType> bool TJsonValueNumberString<CharType>::TryGetNumber(int64& OutValue) const`
- L623 _function_ `template <typename CharType> bool TJsonValueNumberString<CharType>::TryGetNumber(uint8& OutValue) const`
- L629 _function_ `template <typename CharType> bool TJsonValueNumberString<CharType>::TryGetNumber(uint16& OutValue) const`
- L635 _function_ `template <typename CharType> bool TJsonValueNumberString<CharType>::TryGetNumber(uint32& OutValue) const`
- L641 _function_ `template <typename CharType> bool TJsonValueNumberString<CharType>::TryGetNumber(uint64& OutValue) const`
- L647 _function_ `template <typename CharType> bool TJsonValueNumberString<CharType>::TryGetBool(bool& OutBool) const`
- L654 _function_ `template <typename CharType> bool TJsonValueNumberString<CharType>::PreferStringRepresentation() const`
- L660 _function_ `template <typename CharType> SIZE_T TJsonValueNumberString<CharType>::GetMemoryFootprint() const`
- L666 _function_ `template <typename CharType> FString TJsonValueNumberString<CharType>::GetType() const`
- L672 _function_ `template <typename CharType> SIZE_T TJsonValueNumberString<CharType>::GetAllocatedSize() const`

#### class `FJsonValueBoolean`  
`class FJsonValueBoolean : public FJsonValue`  
_L253-269_
- inherits: `FJsonValue`
- desc: A Json Boolean Value.
- L256 _public prototype_ `FJsonValueBoolean(bool InBool);`
- L257 _public prototype_ `virtual ~FJsonValueBoolean();`
- L259 _public prototype_ `virtual bool TryGetNumber(double& OutNumber) const override;`
- L260 _public prototype_ `virtual bool TryGetBool(bool& OutBool) const override;`
- L261 _public prototype_ `virtual bool TryGetString(FString& OutString) const override;`
- L262 _public prototype_ `virtual bool TryGetUtf8String(FUtf8String& OutString) const override;`
- L263 _public prototype_ `virtual SIZE_T GetMemoryFootprint() const override;`
- L266 _protected member_ `bool Value;`
- L268 _protected prototype_ `virtual FString GetType() const override;`

#### class `FJsonValueArray`  
`class FJsonValueArray : public FJsonValue`  
_L272-289_
- inherits: `FJsonValue`
- desc: A Json Array Value.
- L275 _public prototype_ `FJsonValueArray(const TArray<TSharedPtr<FJsonValue>>& InArray);`
- L276 _public prototype_ `FJsonValueArray(TArray<TSharedPtr<FJsonValue>>&& InArray);`
- L277 _public prototype_ `virtual ~FJsonValueArray();`
- L279 _public prototype_ `virtual bool TryGetArray(const TArray<TSharedPtr<FJsonValue>>*& OutArray) const override;`
- L280 _public prototype_ `virtual bool TryGetArray(TArray<TSharedPtr<FJsonValue>>*& OutArray) override;`
- L281 _public prototype_ `virtual SIZE_T GetMemoryFootprint() const override;`
- L284 _protected member_ `TArray<TSharedPtr<FJsonValue>> Value;`
- L286 _protected prototype_ `virtual FString GetType() const override;`
- L288 _protected prototype_ `SIZE_T GetAllocatedSize() const;` — Helper to calculate allocated size of the Value array and its contents

#### class `FJsonValueObject`  
`class FJsonValueObject : public FJsonValue`  
_L293-308_
- inherits: `FJsonValue`
- desc: A Json Object Value.
- L296 _public prototype_ `FJsonValueObject(TSharedPtr<FJsonObject> InObject);`
- L297 _public prototype_ `virtual ~FJsonValueObject();`
- L299 _public prototype_ `virtual bool TryGetObject(const TSharedPtr<FJsonObject>*& OutObject) const override;`
- L300 _public prototype_ `virtual bool TryGetObject(TSharedPtr<FJsonObject>*& OutObject) override;`
- L301 _public prototype_ `virtual SIZE_T GetMemoryFootprint() const override;`
- L303 _protected member_ `TSharedPtr<FJsonObject> Value;`
- L305 _protected prototype_ `virtual FString GetType() const override;`
- L307 _protected prototype_ `SIZE_T GetAllocatedSize() const;` — Helper to calculate allocated size of the Value object and its contents

#### class `FJsonValueNull`  
`class FJsonValueNull : public FJsonValue`  
_L312-322_
- inherits: `FJsonValue`
- desc: A Json Null Value.
- L315 _public prototype_ `FJsonValueNull();`
- L316 _public prototype_ `virtual ~FJsonValueNull();`
- L318 _public prototype_ `virtual SIZE_T GetMemoryFootprint() const override;`
- L321 _protected prototype_ `virtual FString GetType() const override;`

#### struct `__anon9160771c0111::TJsonValueStringType`  
`template <typename CharType> struct TJsonValueStringType`  
_L384-387_
- L392 _public function_ `static FString GetType()`

#### struct `__anon9160771c0111::TJsonValueStringType`  
`template <> struct TJsonValueStringType<TCHAR>`  
_L390-396_
- L392 _public function_ `static FString GetType()`

#### struct `__anon9160771c0111::TJsonValueStringType`  
`template <> struct TJsonValueStringType<UTF8CHAR>`  
_L399-405_
- L392 _public function_ `static FString GetType()`

#### struct `__anon9160771c0211::TJsonValueNumberType`  
`template <typename CharType> struct TJsonValueNumberType`  
_L520-523_
- L528 _public function_ `static FString GetType()`

#### struct `__anon9160771c0211::TJsonValueNumberType`  
`template <> struct TJsonValueNumberType<TCHAR>`  
_L526-532_
- L528 _public function_ `static FString GetType()`

#### struct `__anon9160771c0211::TJsonValueNumberType`  
`template <> struct TJsonValueNumberType<UTF8CHAR>`  
_L535-541_
- L528 _public function_ `static FString GetType()`

#### Free symbols / members of external scopes

- L151 _function_ `friend inline bool operator==(const FJsonValue& Lhs, const FJsonValue& Rhs)`
- L156 _function_ `friend inline bool operator!=(const FJsonValue& Lhs, const FJsonValue& Rhs)`
- L196 _typedef_ `using FJsonValueString = TJsonValueString<TCHAR>;`
- L250 _typedef_ `using FJsonValueNumberString = TJsonValueNumberString<TCHAR>;`
- L324 _namespace_ `namespace UE`
- L324 _namespace_ `namespace Json` (scope `UE`)
- L328 _function_ `template<typename T, typename = typename std::enable_if<!std::is_same_v<T, FJsonValue>>> inline JsonSimpleValueVariant ToSimpleJsonVariant(const T& InSimpleValue)` (scope `UE::Json`)
- L330 _typedef_ `using InSimpleValueType = std::decay_t<decltype(InSimpleValue)>;` (scope `UE::Json::ToSimpleJsonVariant`)
- L341 _prototype_ `JsonSimpleValueVariant ToSimpleJsonVariant(const FJsonValue& InJsonValue);` (scope `UE::Json`)
- L345 _prototype_ `FString ToString(const JsonNumberValueVariants& InNumberVariant);`
- L348 _prototype_ `bool operator==(const JsonSimpleValueVariant& Lhs, const JsonSimpleValueVariant& Rhs);` — Global operators
- L349 _prototype_ `bool operator==(const JsonNumberValueVariants& Lhs, const JsonNumberValueVariants& Rhs);`
- L350 _prototype_ `bool operator==(const JsonNumberValueVariants& Lhs, const FString& Rhs);`
- L355 _function_ `inline bool operator==(const FString& Lhs, const JsonNumberValueVariants& Rhs)`
- L360 _function_ `inline bool operator!=(const JsonNumberValueVariants& Lhs, const FString& Rhs)`
- L365 _function_ `inline bool operator!=(const FString& Lhs, const JsonNumberValueVariants& Rhs)`
- L370 _function_ `inline bool operator!=(const JsonNumberValueVariants& Lhs, const JsonNumberValueVariants& Rhs)`
- L375 _function_ `inline bool operator!=(const JsonSimpleValueVariant& Lhs, const JsonSimpleValueVariant& Rhs)`
- L382 _namespace_ `namespace (anonymous)`
- L518 _namespace_ `namespace (anonymous)`

### `Source/Runtime/Json/Public/Json.h` (Public)
_(no declarations extracted)_

### `Source/Runtime/Json/Public/JsonGlobals.h` (Public)


#### Free symbols / members of external scopes

- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogJson, Log, All);`

### `Source/Runtime/Json/Public/JsonUtils/JsonConversion.h` (Public)


#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Json` (scope `UE`)
- L17 _prototype_ `TSharedPtr<FJsonValue> ConvertRapidJsonToSharedJsonValue(const FValue& Value);` (scope `UE::Json`) — Converts from a RapidJSON value to a shared json value
- L22 _prototype_ `TSharedPtr<FJsonObject> ConvertRapidJsonToSharedJsonObject(FConstObject Object);` (scope `UE::Json`) — Converts from a RapidJSON object to a shared json object
- L27 _prototype_ `TOptional<FDocument> ConvertSharedJsonToRapidJsonDocument(const FJsonObject& SrcObject);` (scope `UE::Json`) — Converts from shared JSON object to a RapidJSON Document.

### `Source/Runtime/Json/Public/JsonUtils/JsonObjectArrayUpdater.h` (Public)


#### struct `FJsonObjectArrayUpdater`  
`template <typename ElementType, typename KeyType> struct FJsonObjectArrayUpdater`  
_L20-98_
- desc: Utility to update an array of json objects from an array of elements (of arbitrary type). Elements in the source array and the destination json object array are matched based on an arbitrary key (provided by the FGetElementKey and FTryGetJsonObjectKey delegates respectively). Existing elements get "updated" via the FUpdateJsonObject delegate. The update scheme is entirely customizable; for example, it can be non-destructive and leave some json fields unchanged. Elements from the source array that are not in the json array (based on the "key") are added to it. Elements that are not present in the source array (based on the "key") are removed from the json array. If the source array is empty the json array field is removed.
- L22 _public prototype_ `DECLARE_DELEGATE_RetVal_OneParam(KeyType, FGetElementKey, const ElementType&);`
- L24 _public prototype_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FTryGetJsonObjectKey, const FJsonObject&, KeyType& );`
- L26 _public prototype_ `DECLARE_DELEGATE_TwoParams(FUpdateJsonObject, const ElementType&, FJsonObject&);`
- L28 _public prototype_ `DECLARE_DELEGATE_OneParam(FSortArray, TArray<TSharedPtr<FJsonValue>>&);`
- L30 _public function_ `static void Execute(FJsonObject& JsonObject, const FString& ArrayName, const TArray<ElementType>& SourceArray, FGetElementKey GetElementKey, FTryGetJsonObjectKey TryGetJsonObjectKey, FUpdateJsonObject UpdateJsonObject, FSortArray SortJsonArray = FSortArray())`

#### Free symbols / members of external scopes

- L22 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(KeyType, FGetElementKey, const ElementType&);`
- L24 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FTryGetJsonObjectKey, const FJsonObject&, KeyType& );`
- L26 _delegate_ `DECLARE_DELEGATE_TwoParams(FUpdateJsonObject, const ElementType&, FJsonObject&);`
- L28 _delegate_ `DECLARE_DELEGATE_OneParam(FSortArray, TArray<TSharedPtr<FJsonValue>>&);`

### `Source/Runtime/Json/Public/JsonUtils/JsonPointer.h` (Public)


#### class `UE::Json::FJsonPointer`  
`class FJsonPointer`  
_L24-89_
- desc: JSON Pointer defines a string syntax for identifying a specific value within a JavaScript Object Notation (JSON) document (from rfc6901). @see https://datatracker.ietf.org/doc/html/rfc6901 @note Array append ("-") is currently unsupported.
- L27 _public prototype_ `FJsonPointer() = default;`
- L28 _public prototype_ `FJsonPointer(FStringView Path);`
- L29 _public prototype_ `FJsonPointer(const FJsonPointer& Other);`
- L30 _public prototype_ `FJsonPointer(FJsonPointer&& Other) noexcept;`
- L33 _public prototype_ `bool TryGet(const TSharedPtr<FJsonObject>& RootObject, TSharedPtr<FJsonValue>& OutValue) const;` — Attempt to retrieve the value specified by this Json Pointer from the provided Json Value.
- L36 _public prototype_ `bool TryGet(const TSharedPtr<FJsonValue>& RootValue, TSharedPtr<FJsonValue>& OutValue) const;` — Attempt to retrieve the value specified by this Json Pointer from the provided Json Object.
- L39 _public prototype_ `bool TryGet(const TArray<TSharedPtr<FJsonValue>>& RootValues, TSharedPtr<FJsonValue>& OutValue) const;` — Attempt to retrieve the value specified by this Json Pointer from the provided Json Array.
- L42 _public function_ `inline bool IsValid() const` — Checks that the path has one or more parts.
- L48 _public function_ `inline int32 Length() const` — The number of parts in the path.
- L54 _public prototype_ `void Append(FStringView Part);` — Appends the given part to the path
- L57 _public prototype_ `void SetArrayIndex(int32 Index);` — Sets the last path part to the given array index.
- L60 _public prototype_ `FJsonPointer GetSubPath(int32 NumParts) const;` — Gets the sub-path up to the given part length.
- L63 _public prototype_ `FString ToString() const;` — Get the JsonPointer's string representation.
- L66 _public function_ `inline const FString& operator[](int32 Idx) const` — Get the path part at the given index.
- L72 _public function_ `inline const TArray<FString>& GetAll() const` — Get the path parts as an array.
- L78 _public prototype_ `static FString EscapePart(const FString& Part);` — Substitutes characters in the provided Part with their escaped counterparts (as per the spec).
- L81 _public prototype_ `static FString UnescapePart(const FString& Part);` — Substitutes escaped characters in the Provided path with their original character (as per the spec).
- L85 _private prototype_ `bool ParsePath(const FString& InPath);` — Parses the provided path, populating PathParts and validating the result.
- L88 _private member_ `TArray<FString> PathParts;`

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace Json` (scope `UE`)

### `Source/Runtime/Json/Public/JsonUtils/RapidJsonUtils.h` (Public)


#### class `UE::Json::Private::FAllocatorImpl`  
`class FAllocatorImpl`  
_L19-53_
- desc: TODO: Can remove this and just use rapidjson::CrtAllocator once RapidJsonIncludes.h starts overriding RAPIDJSON_MALLOC, etc
- L22 _public member_ `static const bool kNeedFree = true;`
- L24 _public function_ `void* Malloc(size_t Count)`
- L29 _public function_ `void* Realloc(void* Original, size_t, size_t Count)`
- L39 _public function_ `static void Free(void* Ptr)`
- L44 _public function_ `bool operator==(const FAllocatorImpl&) const`
- L49 _public function_ `bool operator!=(const FAllocatorImpl&) const`

#### struct `UE::Json::FParseError`  
`struct FParseError`  
_L201-210_
- L203 _public member_ `rapidjson::ParseErrorCode ErrorCode = rapidjson::kParseErrorNone;`
- L204 _public member_ `size_t Offset = 0;`
- L209 _public prototype_ `FString CreateMessage(const FStringView JsonText) const;` — Create a user-readable error message. Takes the source text parameter to find the line number from the offset

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Json` (scope `UE`)
- L16 _namespace_ `namespace Private` (scope `UE::Json`)
- L57 _typedef_ `using FEncoding = rapidjson::UTF16<TCHAR>;` (scope `UE::Json`) — types that use TCHAR (common)
- L58 _typedef_ `using FAllocator = Private::FAllocatorImpl;` (scope `UE::Json`)
- L59 _typedef_ `using FDocument = rapidjson::GenericDocument<FEncoding, FAllocator>;` (scope `UE::Json`)
- L60 _typedef_ `using FStringRef = FDocument::StringRefType;` (scope `UE::Json`)
- L61 _typedef_ `using FValue = FDocument::ValueType;` (scope `UE::Json`)
- L62 _typedef_ `using FMember = FValue::Member;` (scope `UE::Json`)
- L65 _typedef_ `using FConstObject = FValue::ConstObject;` (scope `UE::Json`) — types that use TCHAR (for reading)
- L66 _typedef_ `using FConstArray = FValue::ConstArray;` (scope `UE::Json`)
- L69 _typedef_ `using FObject = FValue::Object;` (scope `UE::Json`) — types that use TCHAR (for writing)
- L70 _typedef_ `using FArray = FValue::Array;` (scope `UE::Json`)
- L71 _typedef_ `using FStringBuffer = rapidjson::GenericStringBuffer<FEncoding, FAllocator>;` (scope `UE::Json`)
- L72 _typedef_ `using FStringWriter = rapidjson::Writer<FStringBuffer, FEncoding, FEncoding, FAllocator>;` (scope `UE::Json`)
- L73 _typedef_ `using FPrettyStringWriter = rapidjson::PrettyWriter<FStringBuffer, FEncoding, FEncoding, FAllocator>;` (scope `UE::Json`)
- L79 _function_ `inline FStringRef MakeStringRef(FStringView Str)` (scope `UE::Json`) — Make a RapidJSON reference to the given string. @note The given string must outlive the returned reference.
- L87 _function_ `inline FValue MakeStringValue(FStringView Str, FAllocator& Allocator)` (scope `UE::Json`) — Make a RapidJSON value that has a copy of the given string.
- L96 _function_ `inline FStringView ValueAsStringView(const FValue& Value)` (scope `UE::Json`) — Reads a string from the specified value. @note The given value must be a string.
- L107 _prototype_ `TOptional<FStringView> GetStringValue(const FValue& Value);` (scope `UE::Json`) — Attempts to read a string from the specified value. Returns the value, if it matches the type explicitly
- L114 _prototype_ `TOptional<bool> GetBoolField(FConstObject Object, const TCHAR* FieldName);` (scope `UE::Json`) — Attempts to read a boolean with a specified name. Returns the value, if found and matches the type explicitly
- L121 _prototype_ `TOptional<int32> GetInt32Field(FConstObject Object, const TCHAR* FieldName);` (scope `UE::Json`) — Attempts to read an int32 with a specified name. Returns the value, if found and matches the type explicitly
- L128 _prototype_ `TOptional<uint32> GetUint32Field(FConstObject Object, const TCHAR* FieldName);` (scope `UE::Json`) — Attempts to read an uint32 with a specified name. Returns the value, if found and matches the type explicitly
- L135 _prototype_ `TOptional<int64> GetInt64Field(FConstObject Object, const TCHAR* FieldName);` (scope `UE::Json`) — Attempts to read an int64 with a specified name. Returns the value, if found and matches the type explicitly
- L142 _prototype_ `TOptional<uint64> GetUint64Field(FConstObject Object, const TCHAR* FieldName);` (scope `UE::Json`) — Attempts to read an uint64 with a specified name. Returns the value, if found and matches the type explicitly
- L149 _prototype_ `TOptional<double> GetDoubleField(FConstObject Object, const TCHAR* FieldName);` (scope `UE::Json`) — Attempts to read an double with a specified name. Returns the value, if found and matches the type explicitly
- L156 _prototype_ `TOptional<FStringView> GetStringField(FConstObject Object, const TCHAR* FieldName);` (scope `UE::Json`) — Attempts to read a string with a specified name Returns the value, if found and matches the type explicitly
- L164 _function_ `template<typename TEnum> inline TOptional<TEnum> GetEnumField(FConstObject Object, const TCHAR* FieldName)` (scope `UE::Json`) — Attempts to parse an enum from a string with a specified name Returns the value, if found and matches the type explicitly
- L182 _prototype_ `TOptional<FConstObject> GetObjectField(FConstObject Object, const TCHAR* FieldName);` (scope `UE::Json`) — Attempts to find an object with the specified name Returns a valid object ref if the field was found and it matches an object.
- L189 _prototype_ `TOptional<FConstArray> GetArrayField(FConstObject Object, const TCHAR* FieldName);` (scope `UE::Json`) — Attempts to find an array with the specified name Returns a valid array ref if the field was found and it matches an array
- L194 _prototype_ `bool HasNullField(FConstObject Object, const TCHAR* FieldName);` (scope `UE::Json`) — Returns true if a field exists that is a null type
- L199 _prototype_ `TOptional<FConstObject> GetRootObject(const FDocument& Document);` (scope `UE::Json`) — Returns the root object, if that was the root type for the document
- L215 _prototype_ `TValueOrError<FDocument, FParseError> Parse(const FStringView JsonText);` (scope `UE::Json`) — Parse RapidJSON with default flags
- L222 _prototype_ `TValueOrError<FDocument, FParseError> ParseInPlace(TArrayView<TCHAR> JsonText);` (scope `UE::Json`) — Parse RapidJSON with default flags, into destructible memory, to reduce allocation counts. JsonText must be a zero terminated string per the rapidjson documentation
- L227 _prototype_ `FString WriteCompact(const FDocument& Document);` (scope `UE::Json`) — Write a RapidJSON document as a compact string with default flags.
- L232 _prototype_ `FString WritePretty(const FDocument& Document);` (scope `UE::Json`) — Write a RapidJSON document as a pretty string with default flags and tab indentation.
- L237 _prototype_ `const TCHAR* GetValueTypeName(const FValue& Value);` (scope `UE::Json`) — Return a string representation of type name, for debug logging purposes

### `Source/Runtime/Json/Public/Policies/CondensedJsonPrintPolicy.h` (Public)


#### struct `TCondensedJsonPrintPolicy`  
`template <class CharType> struct TCondensedJsonPrintPolicy : public TJsonPrintPolicy<CharType>`  
_L14-20_
- inherits: `TJsonPrintPolicy<CharType>`
- desc: Template for print policies that generate compressed output. @param CharType The type of characters to print, i.e. TCHAR or ANSICHAR.
- L17 _public function_ `static inline void WriteLineTerminator(FArchive* Stream)`
- L18 _public function_ `static inline void WriteTabs(FArchive* Stream, int32 Count)`
- L19 _public function_ `static inline void WriteSpace(FArchive* Stream)`

### `Source/Runtime/Json/Public/Policies/JsonPrintPolicy.h` (Public)


#### struct `TJsonPrintPolicy`  
`template <class InCharType> struct TJsonPrintPolicy`  
_L14-76_
- desc: Base template for Json print policies. @param CharType The type of characters to print, i.e. TCHAR or ANSICHAR.
- L16 _public typedef_ `using CharType = InCharType;`
- L24 _public function_ `static inline void WriteChar( FArchive* Stream, CharType Char )` — Writes a single character to the output stream. @param Stream The stream to write to. @param Char The character to write.
- L35 _public function_ `static inline void WriteString(FArchive* Stream, FStringView String)` — Writes a string to the output stream. @param Stream The stream to write to. @param String The string to write.
- L47 _public function_ `static inline void WriteString(FArchive* Stream, FUtf8StringView String)` — Writes a utf8 string to the output stream. @param Stream The stream to write to. @param String The string to write.
- L59 _public function_ `static inline void WriteFloat( FArchive* Stream, float Value )` — Writes a float to the output stream. @param Stream The stream to write to. @param Value The float to write.
- L70 _public function_ `static inline void WriteDouble( FArchive* Stream, double Value )` — Writes a double to the output stream. @param Stream The stream to write to. @param Value The double to write.
- L85 _function_ `template <> inline void TJsonPrintPolicy<UTF16CHAR>::WriteString(FArchive* Stream, FStringView String)` — Specialization for UTF16CHAR that writes FString data UTF-16.

### `Source/Runtime/Json/Public/Policies/PrettyJsonPrintPolicy.h` (Public)


#### struct `TPrettyJsonPrintPolicy`  
`template <class CharType> struct TPrettyJsonPrintPolicy : public TJsonPrintPolicy<CharType>`  
_L14-36_
- inherits: `TJsonPrintPolicy<CharType>`
- desc: Template for print policies that generate human readable output. @param CharType The type of characters to print, i.e. TCHAR or ANSICHAR.
- L17 _public function_ `static inline void WriteLineTerminator( FArchive* Stream )`
- L22 _public function_ `static inline void WriteTabs( FArchive* Stream, int32 Count )`
- L32 _public function_ `static inline void WriteSpace( FArchive* Stream )`

### `Source/Runtime/Json/Public/RapidJsonIncludes.h` (Public)


#### Free symbols / members of external scopes

- L18 _macro_ `#define RAPIDJSON_ASSERT(x) check(x)`
- L22 _macro_ `#define RAPIDJSON_ERROR_CHARTYPE TCHAR`
- L26 _macro_ `#define RAPIDJSON_ERROR_STRING(x) TEXT(x)`
- L47 _macro_ `#define RAPIDJSON_ENDIAN RAPIDJSON_LITTLEENDIAN`
- L53 _macro_ `#define RAPIDJSON_NEON`

### `Source/Runtime/Json/Public/Serialization/JsonDataBag.h` (Public)


#### struct `FJsonDataBag`  
`struct FJsonDataBag : public FJsonSerializable`  
_L13-37_
- inherits: `FJsonSerializable`
- desc: Useful if you just want access to the underlying FJsonObject (for cases where the schema is loose or an outer system will do further de/serialization)
- L15 _public prototype_ `virtual void Serialize(FJsonSerializerBase& Serializer, bool bFlatObject) override;`
- L17 _public prototype_ `double GetDouble(const FString& Key) const;`
- L19 _public prototype_ `FString GetString(const FString& Key) const;`
- L21 _public prototype_ `bool GetBool(const FString& Key) const;`
- L23 _public prototype_ `TSharedPtr<const FJsonValue> GetField(const FString& Key) const;`
- L26 _public function_ `template<typename JSON_TYPE, typename Arg> void SetField(const FString& Key, Arg&& Value)`
- L31 _public prototype_ `void SetFieldJson(const FString& Key, const TSharedPtr<FJsonValue>& Value);`
- L33 _public member_ `TSharedPtr<FJsonObject> JsonObject;`
- L36 _public member_ `TOptional<int32> NumPrintIndents;` — If set, will use TPrettyJsonPrintPolicy

#### struct `TPrettyJsonBag`  
`template<int32 PrintIndentCount> struct TPrettyJsonBag : public FJsonDataBag`  
_L40-47_
- inherits: `FJsonDataBag`
- L42 _public function_ `TPrettyJsonBag() : FJsonDataBag()`

### `Source/Runtime/Json/Public/Serialization/JsonReader.h` (Public)


#### class `TJsonReader`  
`template <class CharType = TCHAR> class TJsonReader`  
_L40-962_
- L44 _public typedef_ `using StoredStringType = std::conditional_t<std::is_same_v<CharType, ANSICHAR>, FUtf8String, TString<CharType>>;` — Store ANSICHAR in FUtf8String because JSON may contain scaped unicode characters that would not be recoverable otherwise. Use default string type for the char type otherwise
- L45 _public typedef_ `using StoredCharType = TElementType_T<StoredStringType>;`
- L46 _public typedef_ `using ValueAsStringReturnType = std::conditional_t<std::is_same_v<StoredStringType, FString>, const FString&, FString>;`
- L48 _public function_ `static TSharedRef< TJsonReader<CharType> > Create( FArchive* const Stream )`
- L55 _public prototype_ `virtual ~TJsonReader() = default;`
- L57 _public function_ `bool ReadNext( EJsonNotation& Notation )`
- L154 _public function_ `bool SkipObject()`
- L159 _public function_ `bool SkipArray()`
- L164 _public function_ `inline virtual const FString& GetIdentifier() const`
- L166 _public function_ `inline virtual ValueAsStringReturnType GetValueAsString() const`
- L180 _public function_ `inline virtual const StoredStringType& GetInternalValueAsString() const`
- L186 _public function_ `inline virtual StoredStringType StealInternalValueAsString()`
- L192 _public function_ `inline double GetValueAsNumber() const`
- L198 _public function_ `inline const StoredStringType& GetValueAsNumberString() const`
- L204 _public function_ `inline bool GetValueAsBoolean() const`
- L210 _public function_ `inline const FString& GetErrorMessage() const`
- L215 _public function_ `inline const uint32 GetLineNumber() const`
- L220 _public function_ `inline const uint32 GetCharacterNumber() const`
- L228 _protected function_ `TJsonReader() : ParseState() , CurrentToken( EJsonToken::None ) , Stream( nullptr ) , Identifier() , ErrorMessage() , StringValue() , NumberValue( 0.0f ) , LineNumber( 1 ) , CharacterNumber( 0 ) , BoolValue( false ) , FinishedReadingRootObject( false )` — Hidden default constructor.
- L247 _protected function_ `explicit TJsonReader(FArchive* InStream) : ParseState() , CurrentToken(EJsonToken::None) , Stream(InStream) , Identifier() , ErrorMessage() , StringValue() , NumberValue(0.0f) , LineNumber(1) , CharacterNumber(0) , BoolValue(false) , FinishedReadingRootObject(false)` — Creates and initializes a new instance with the given input. @param InStream An archive containing the input.
- L263 _private function_ `void SetErrorMessage( const FString& Message )`
- L268 _private function_ `bool ReadUntilMatching( const EJsonNotation ExpectedNotation )`
- L307 _private function_ `bool ReadStart( EJsonToken& Token )`
- L330 _private function_ `bool ReadNextObjectValue( EJsonToken& Token )`
- L394 _private function_ `bool ReadNextArrayValue( EJsonToken& Token )`
- L431 _private function_ `bool NextToken( EJsonToken& OutToken )`
- L627 _private function_ `bool ParseStringToken()`
- L737 _private function_ `bool ParseNumberToken( CharType FirstChar )`
- L868 _private function_ `bool ParseWhiteSpace()`
- L896 _private function_ `bool IsLineBreak( const CharType& Char )`
- L902 _private function_ `bool IsWhitespace( const CharType& Char )` — Can't use FChar::IsWhitespace because it is TCHAR specific, and it doesn't handle newlines
- L908 _private function_ `bool IsJsonNumber( const CharType& Char )` — Can't use FChar::IsDigit because it is TCHAR specific, and it doesn't handle all the other Json number characters
- L915 _private function_ `bool IsDigit( const CharType& Char )` — Can't use FChar::IsDigit because it is TCHAR specific
- L920 _private function_ `bool IsNonZeroDigit( const CharType& Char )`
- L926 _private function_ `bool IsAlphaNumber( const CharType& Char )` — Can't use FChar::IsAlpha because it is TCHAR specific. Also, this only checks A through Z (no underscores or other characters).
- L932 _protected function_ `bool Serialize(void* V, int64 Length)`
- L945 _protected function_ `void InlineCombineSurrogates(Type& String)` — `UE_DEPRECATED(5.8, "Remove calls to this function because it does nothing.")`
- L950 _protected member_ `TArray<EJson> ParseState;`
- L951 _protected member_ `EJsonToken CurrentToken;`
- L953 _protected member_ `FArchive* Stream;`
- L954 _protected member_ `FString Identifier;`
- L955 _protected member_ `FString ErrorMessage;`
- L956 _protected member_ `StoredStringType StringValue;`
- L957 _protected member_ `double NumberValue;`
- L958 _protected member_ `uint32 LineNumber;`
- L959 _protected member_ `uint32 CharacterNumber;`
- L960 _protected member_ `bool BoolValue;`
- L961 _protected member_ `bool FinishedReadingRootObject;`

#### class `TJsonStringReader`  
`template <typename CharType> class TJsonStringReader : public TJsonReader<CharType>`  
_L966-1028_
- inherits: `TJsonReader<CharType>`
- L970 _public function_ `static TSharedRef<TJsonStringReader> Create(const TString<CharType>& JsonString)`
- L975 _public function_ `static TSharedRef<TJsonStringReader> Create(TString<CharType>&& JsonString)`
- L980 _public function_ `const TString<CharType>& GetSourceString() const`
- L986 _public prototype_ `virtual ~TJsonStringReader() = default;`
- L995 _protected function_ `explicit TJsonStringReader(const TString<CharType>& JsonString) : Content(JsonString) , Reader(nullptr)` — Parses a string containing Json information. @param JsonString The Json string to parse.
- L1007 _protected function_ `explicit TJsonStringReader(TString<CharType>&& JsonString) : Content(MoveTemp(JsonString)) , Reader(nullptr)` — Parses a string containing Json information. @param JsonString The Json string to parse.
- L1014 _protected function_ `inline void InitReader()`
- L1026 _protected member_ `const TString<CharType> Content;`
- L1027 _protected member_ `TUniquePtr<FBufferReader> Reader;`

#### class `TJsonStringViewReader`  
`template <class CharType> class TJsonStringViewReader : public TJsonReader<CharType>`  
_L1033-1075_
- inherits: `TJsonReader<CharType>`
- L1038 _public function_ `static TSharedRef<TJsonStringViewReader> Create(TStringView<CharType> JsonString)`
- L1045 _public prototype_ `virtual ~TJsonStringViewReader() = default;`
- L1054 _protected function_ `explicit TJsonStringViewReader(TStringView<CharType> JsonString) : Content(JsonString) , Reader(nullptr)` — Parses a string containing Json information. @param JsonString The Json string to parse.
- L1061 _protected function_ `void InitReader()`
- L1073 _protected member_ `TStringView<CharType> Content;`
- L1074 _protected member_ `TUniquePtr<FBufferReader> Reader;`

#### class `TJsonReaderFactory`  
`template <class CharType = TCHAR> class TJsonReaderFactory`  
_L1078-1102_
- L1081 _public typedef_ `using StringType = TString<CharType>;`
- L1083 _public function_ `static TSharedRef<TJsonReader<TElementType_T<StringType>>> Create(StringType&& JsonString)`
- L1088 _public function_ `static TSharedRef<TJsonReader<TElementType_T<StringType>>> Create(const StringType& JsonString)`
- L1093 _public function_ `static TSharedRef<TJsonReader<CharType>> Create(FArchive* const Stream)`
- L1098 _public function_ `static TSharedRef<TJsonReader<CharType>> CreateFromView(TStringView<CharType> JsonString)`

#### Free symbols / members of external scopes

- L14 _macro_ `#define JSON_NOTATIONMAP_DEF \`
- L32 _macro_ `#define WITH_JSON_INLINED_NOTATIONMAP 0`
- L634 _function_ `` (scope `TJsonReader::ParseStringToken`)
- L1030 _typedef_ `using FJsonStringReader = TJsonStringReader<TCHAR>;`

### `Source/Runtime/Json/Public/Serialization/JsonSerializable.h` (Public)


#### struct `FJsonSerializable`  
`struct FJsonSerializable`  
_L17-91_
- desc: Base class for a JSON serializable object
- L22 _public prototype_ `virtual ~FJsonSerializable();` — Virtualize destructor as we provide overridable functions
- L29 _public prototype_ `const FString ToJson(bool bPrettyPrint = true) const;` — Used to allow serialization of a const ref @return the corresponding json string
- L30 _public prototype_ `const FUtf8String ToJsonUtf8(bool bPrettyPrint = true) const;`
- L38 _public prototype_ `virtual const FString ToJson(bool bPrettyPrint=true);` — Serializes this object to its JSON string form @param bPrettyPrint - If true, will use the pretty json formatter @return the corresponding json string
- L39 _public prototype_ `virtual const FUtf8String ToJsonUtf8(bool bPrettyPrint = true);`
- L48 _public prototype_ `template<class CharType, class PrintPolicy, ESPMode SPMode> void ToJson(TSharedRef<TJsonWriter<CharType, PrintPolicy>, SPMode> JsonWriter, bool bFlatObject = false) const;` — Serializes this object with a Json Writer @param JsonWriter - The writer to use @param bFlatObject if true then no object wrapper is used
- L55 _public prototype_ `virtual bool FromJson(const TCHAR* Json);` — Serializes the contents of a JSON string into this object @param Json the JSON data to serialize from
- L56 _public prototype_ `virtual bool FromJson(const UTF8CHAR* Json);`
- L57 _public prototype_ `virtual bool FromJson(const FString& Json);`
- L58 _public prototype_ `virtual bool FromJson(const FUtf8String& Json);`
- L65 _public prototype_ `virtual bool FromJson(FString&& Json);` — Serializes the contents of a JSON string into this object @param Json the JSON data to serialize from
- L66 _public prototype_ `virtual bool FromJson(FUtf8String&& Json);`
- L73 _public prototype_ `bool FromJsonStringView(FUtf8StringView JsonStringView);` — Serializes the contents of a JSON string into this object using FUtf8StringView @param JsonStringView the JSON data to serialize from
- L80 _public prototype_ `bool FromJsonStringView(FWideStringView JsonStringView);` — Serializes the contents of a JSON string into this object using FWideStringView @param JsonStringView the JSON data to serialize from
- L82 _public prototype_ `virtual bool FromJson(TSharedPtr<FJsonObject> JsonObject);`
- L90 _public prototype_ `virtual void Serialize(FJsonSerializerBase& Serializer, bool bFlatObject) = 0;` — Abstract method that needs to be supplied using the macros @param Serializer the object that will perform serialization in/out of JSON @param bFlatObject if true then no object wrapper is used
- L94 _function_ `template<class CharType, class PrintPolicy, ESPMode SPMode> inline void FJsonSerializable::ToJson(TSharedRef<TJsonWriter<CharType, PrintPolicy>, SPMode> JsonWriter, bool bFlatObject) const`

#### Free symbols / members of external scopes

- L100 _namespace_ `namespace UE`
- L100 _namespace_ `namespace JsonArray` (scope `UE`)
- L103 _namespace_ `namespace Private` (scope `UE::JsonArray`)
- L107 _function_ `template<typename T, typename CharType> inline bool FromJson(TArray<T>& OutArray, TStringView<CharType> JsonString)` (scope `UE::JsonArray::Private`)
- L139 _typedef_ `using FReturnStringArgs = TTuple<FString* , bool >;` (scope `UE::JsonArray::Private`)
- L141 _typedef_ `using FPrettyWriter = TSharedRef<TJsonWriter<>>;` (scope `UE::JsonArray::Private`)
- L142 _typedef_ `using FCondensedWriter = TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>>;` (scope `UE::JsonArray::Private`)
- L143 _typedef_ `using FWriterVariants = TVariant<FPrettyWriter, FCondensedWriter>;` (scope `UE::JsonArray::Private`)
- L145 _typedef_ `using FToJsonVariantArgs = TVariant<FReturnStringArgs, FWriterVariants>;` (scope `UE::JsonArray::Private`)
- L147 _typedef_ `using FPrettySerializer = FJsonSerializerWriter<>;` (scope `UE::JsonArray::Private`)
- L148 _typedef_ `using FCondensedSerializer = FJsonSerializerWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>;` (scope `UE::JsonArray::Private`)
- L151 _function_ `template<typename T, typename...SerializerArgsT> inline void ToJson_SerializeArrayElements(TArray<T>& InArray, SerializerArgsT...Args)` (scope `UE::JsonArray::Private`)
- L160 _function_ `template<typename T, typename...SerializerArgsT> inline void ToJson_SerializeArrayElements(TArray<T*>& InArray, SerializerArgsT...Args)` (scope `UE::JsonArray::Private`)
- L169 _function_ `template<typename T> inline void ToJson(TArray<T>& InArray, const FToJsonVariantArgs& InArgs)` (scope `UE::JsonArray::Private`)
- L171 _typedef_ `using FPrettySerializerAndWriter = TTuple<FPrettySerializer, FPrettyWriter>;` (scope `UE::JsonArray::Private::ToJson`)
- L172 _typedef_ `using FCondensedSerializerAndWriter = TTuple<FCondensedSerializer, FCondensedWriter>;` (scope `UE::JsonArray::Private::ToJson`)
- L174 _typedef_ `using FSerializerVariant = TVariant<FPrettySerializerAndWriter, FCondensedSerializerAndWriter>;` (scope `UE::JsonArray::Private::ToJson`)
- L178 _function_ `` (scope `UE::JsonArray::Private::ToJson`)
- L194 _function_ `` (scope `UE::JsonArray::Private::ToJson::__anon85b917140202`)
- L224 _function_ `template<typename T> static bool FromJson(TArray<T>& OutArray, const FString& JsonString)` (scope `UE::JsonArray`)
- L230 _function_ `template<typename T> static bool FromJson(TArray<T>& OutArray, FString&& JsonString)` (scope `UE::JsonArray`)
- L236 _function_ `template<typename T> static bool FromJson(TArray<T>& OutArray, FUtf8StringView JsonStringView)` (scope `UE::JsonArray`)
- L242 _function_ `template<typename T> static bool FromJson(TArray<T>& OutArray, FWideStringView JsonStringView)` (scope `UE::JsonArray`)
- L249 _function_ `template<typename T> static const FString ToJson(TArray<T>& InArray, const bool bPrettyPrint = true)` (scope `UE::JsonArray`) — non-const due to T::Serialize being a non-const function
- L257 _function_ `template<typename T> static void ToJson(TArray<T>& InArray, Private::FPrettyWriter& JsonWriter)` (scope `UE::JsonArray`)
- L263 _function_ `template<typename T> static void ToJson(TArray<T>& InArray, Private::FCondensedWriter& JsonWriter)` (scope `UE::JsonArray`)

### `Source/Runtime/Json/Public/Serialization/JsonSerializer.h` (Public)


#### struct `FJsonSerializerPolicy_JsonObject`  
`struct FJsonSerializerPolicy_JsonObject`  
_L14-287_
- L16 _public typedef_ `using FValue = TSharedPtr<FJsonValue>;`
- L17 _public typedef_ `using FArrayOfValues = TArray<TSharedPtr<FJsonValue>>;`
- L18 _public typedef_ `using FMapOfValues = TSharedPtr<FJsonObject>;`
- L75 _public prototype_ `static bool GetValueFromState(const FStackState& State, FValue& OutValue);`
- L76 _public prototype_ `static bool GetValueFromState(const FStackState& State, FArrayOfValues& OutArray);`
- L77 _public prototype_ `static bool GetValueFromState(const FStackState& State, FMapOfValues& OutMap);`
- L78 _public prototype_ `static void ResetValue(FValue& OutValue);`
- L79 _public prototype_ `static void ReadObjectStart(FStackState& State);`
- L80 _public prototype_ `static void ReadObjectEnd(FStackState& State, FValue& OutValue);`
- L81 _public prototype_ `static void ReadArrayStart(FStackState& State);`
- L82 _public prototype_ `static void ReadArrayEnd(FStackState& State, FValue& OutValue);`
- L85 _public function_ `template<class CharType> static void ReadBoolean(TJsonReader<CharType>& Reader, FValue& OutValue)`
- L91 _public function_ `template<class CharType> static void ReadString(TJsonReader<CharType>& Reader, FValue& OutValue)`
- L98 _public function_ `template<class CharType> static void ReadNumberAsString(TJsonReader<CharType>& Reader, FValue& OutValue)`
- L105 _public function_ `template<class CharType> static void ReadNumber(TJsonReader<CharType>& Reader, FValue& OutValue)`
- L110 _public prototype_ `static void ReadNull(FValue& OutValue);`
- L111 _public prototype_ `static void AddValueToObject(FStackState& State, const FString& Identifier, FValue& NewValue);`
- L112 _public prototype_ `static void AddValueToArray(FStackState& State, FValue& NewValue);`
- L115 _public function_ `template<class CharType, class PrintPolicy> static bool SerializeIfBool(TSharedRef<FElement>& Element, TJsonWriter<CharType, PrintPolicy>& Writer, bool bWriteValueOnly)`
- L135 _public function_ `template<class CharType, class PrintPolicy> static bool SerializeIfNumber(TSharedRef<FElement>& Element, TJsonWriter<CharType, PrintPolicy>& Writer, bool bWriteValueOnly)`
- L169 _public function_ `template<class CharType, class PrintPolicy> static bool SerializeIfString(TSharedRef<FElement>& Element, TJsonWriter<CharType, PrintPolicy>& Writer, bool bWriteValueOnly)`
- L189 _public function_ `template<class CharType, class PrintPolicy> static bool SerializeIfNull(TSharedRef<FElement>& Element, TJsonWriter<CharType, PrintPolicy>& Writer, bool bWriteValueOnly)`
- L209 _public function_ `template<class CharType, class PrintPolicy> static bool SerializeIfArray(TArray<TSharedRef<FElement>>& ElementStack, TSharedRef<FElement>& Element, TJsonWriter<CharType, PrintPolicy>& Writer, bool bWriteValueOnly)`
- L246 _public function_ `template<class CharType, class PrintPolicy> static bool SerializeIfObject(TArray<TSharedRef<FElement>>& ElementStack, TSharedRef<FElement>& Element, TJsonWriter<CharType, PrintPolicy>& Writer, bool bWriteValueOnly)`

#### struct `FJsonSerializerPolicy_JsonObject::FGlobalState`  
`struct FGlobalState`  
_L20-25_
- L23 _public member_ `TSharedPtr<UE::JSON::Private::FJsonStringSet> StringSet = MakeShared<UE::JSON::Private::FJsonStringSet>();`

#### struct `FJsonSerializerPolicy_JsonObject::FStackState`  
`struct FStackState`  
_L27-44_
- L29 _public prototype_ `FStackState() = default;`
- L30 _public function_ `explicit FStackState(const FGlobalState& GlobalState) #if !UE_JSONOBJECT_LEGACY_STRING_KEYS : StringSet(GlobalState.StringSet) #endif`
- L37 _public member_ `EJson Type;`
- L38 _public member_ `FString Identifier;`
- L39 _public member_ `TArray<TSharedPtr<FJsonValue>> Array;`
- L40 _public member_ `TSharedPtr<FJsonObject> Object;`
- L42 _public member_ `TSharedPtr<UE::JSON::Private::FJsonStringSet> StringSet;`

#### struct `FJsonSerializerPolicy_JsonObject::FElement`  
`struct FElement`  
_L46-73_
- L48 _public function_ `FElement( const FValue& InValue ) : Identifier() , Value(InValue)`
- L53 _public function_ `FElement( const FMapOfValues& Object ) : Identifier() , Value(MakeShared<FJsonValueObject>(Object))`
- L58 _public function_ `FElement( const FArrayOfValues& Array ) : Identifier() , Value(MakeShared<FJsonValueArray>(Array))`
- L63 _public function_ `FElement( const FString& InIdentifier, const FValue& InValue ) : Identifier( InIdentifier ) , Value( InValue ) , bIsKeyValuePair( true )`
- L69 _public member_ `FString Identifier;`
- L70 _public member_ `FValue Value;`
- L71 _public member_ `bool bHasBeenProcessed = false;`
- L72 _public member_ `bool bIsKeyValuePair = false;`

#### class `TJsonSerializer`  
`template<typename Policy = FJsonSerializerPolicy_JsonObject> class TJsonSerializer`  
_L290-674_
- L301 _public function_ `template <class CharType> static bool Deserialize(const TSharedRef<TJsonReader<CharType>>& Reader, typename Policy::FValue& OutValue, EFlags InOptions = EFlags::None)`
- L307 _public function_ `template <class CharType> static bool Deserialize(TJsonReader<CharType>& Reader, typename Policy::FValue& OutValue, EFlags InOptions = EFlags::None)`
- L319 _public function_ `template <class CharType> static bool Deserialize(const TSharedRef<TJsonReader<CharType>>& Reader, typename Policy::FArrayOfValues& OutArray, EFlags InOptions = EFlags::None)`
- L325 _public function_ `template <class CharType> static bool Deserialize(TJsonReader<CharType>& Reader, typename Policy::FArrayOfValues& OutArray, EFlags InOptions = EFlags::None)`
- L337 _public function_ `template <class CharType> static bool Deserialize(const TSharedRef<TJsonReader<CharType>>& Reader, typename Policy::FMapOfValues& OutMap, EFlags InOptions = EFlags::None)`
- L343 _public function_ `template <class CharType> static bool Deserialize(TJsonReader<CharType>& Reader, typename Policy::FMapOfValues& OutMap, EFlags InOptions = EFlags::None)`
- L377 _public function_ `template <class CharType, class PrintPolicy> static bool Serialize(const typename Policy::FValue& Value, const FString& Identifier, const TSharedRef<TJsonWriter<CharType, PrintPolicy>>& Writer, bool bCloseWriter = true)` — Serialize the passed value and identifier into the writer. Empty string identifiers will be ignored when the writer is not writing inside of a map of values and only the value will be serialized. If the writer is in a state where it's currently writing inside of a map of values, then the identifier will always be serialized. Json Examples: - Writer state: { "foo": "bar" <writer position> Parameters: Identifier: "" Value: "baz" Serialization result: { "foo": "bar", "": "baz" <writer position> //empty identifier is serialized as a valid key for the key:value pair "":"baz" - Writer state: { "foo": ["bar" <writer position> Parameters: Identifier: "" Value: "baz" Serialization result: { foo: ["bar", "baz" <writer position> //empty identifier is ignored since we are writing into an array and not an object. @param Value			The value we are serializing @param Identifier	The identifier of the value, empty identifiers are ignored outside of maps of values. @param Writer		The writer the value and identifier are written into. @param bCloseWriter	When set to true the Writer will be closed after the serialization. @return				Returns true if the serialization was successful, false otherwise.
- L405 _public function_ `template <class CharType, class PrintPolicy> static bool Serialize(const typename Policy::FValue& Value, const FString& Identifier, TJsonWriter<CharType, PrintPolicy>& Writer, bool bCloseWriter = true)` — Serialize the passed value and identifier into the writer. Empty string identifiers will be ignored when the writer is not writing inside of a map of values and only the value will be serialized. If the writer is in a state where it's currently writing inside of a map of values, then the identifier will always be serialized. Json Examples: - Writer state: { "foo": "bar" <writer position> Parameters: Identifier: "" Value: "baz" Serialization result: { "foo": "bar", "": "baz" <writer position> //empty identifier is serialized as a valid key for the key:value pair "":"baz" - Writer state: { "foo": ["bar" <writer position> Parameters: Identifier: "" Value: "baz" Serialization result: { foo: ["bar", "baz" <writer position> //empty identifier is ignored since we are writing into an array and not an object. @param Value			The value we are serializing @param Identifier	The identifier of the value, empty identifiers are ignored outside of maps of values. @param Writer		The writer the value and identifier are written into. @param bCloseWriter	When set to true the Writer will be closed after the serialization. @return				Returns true if the serialization was successful, false otherwise.
- L426 _public function_ `template <class CharType, class PrintPolicy> static bool Serialize(const typename Policy::FArrayOfValues& Array, const TSharedRef<TJsonWriter<CharType, PrintPolicy>>& Writer, bool bCloseWriter = true)` — Serialize the passed array of values into the writer. This will effectively serialize all of the values enclosed in [] square brackets. Json Example: - Writer state: [123 <writer position> Parameter: Array: ["foo", "bar", "", 456] Serialization result: [123, ["foo", "bar", "", 456] <writer position> @param Array		    The array we are serializing @param Writer		The writer the array is written into. @param bCloseWriter	When set to true the Writer will be closed after the serialization. @return				Returns true if the serialization was successful, false otherwise.
- L446 _public function_ `template <class CharType, class PrintPolicy> static bool Serialize(const typename Policy::FArrayOfValues& Array, TJsonWriter<CharType, PrintPolicy>& Writer, bool bCloseWriter = true )` — Serialize the passed array of values into the writer. This will effectively serialize all of the values enclosed in [] square brackets. Json Example: - Writer state: [123 <writer position> Parameter: Array: ["foo", "bar", "", 456] Serialization result: [123, ["foo", "bar", "", 456] <writer position> @param Array		    The array we are serializing @param Writer		The writer the array is written into. @param bCloseWriter	When set to true the Writer will be closed after the serialization. @return				Returns true if the serialization was successful, false otherwise.
- L467 _public function_ `template <class CharType, class PrintPolicy> static bool Serialize(const typename Policy::FMapOfValues& Object, const TSharedRef<TJsonWriter<CharType, PrintPolicy>>& Writer, bool bCloseWriter = true )` — Serialize the passed map of values into the writer. This will effectively serialize all of the identifier:value pairs of the map, enclosed in {} curly brackets. Json Example: - Writer state: [123 <writer position> Parameter: Object: {"foo": "bar", "baz": "", "": 456} Serialization result: [123, {"foo": "bar", "baz": "", "": 456} <writer position> @param Object		The map of values we are serializing @param Writer		The writer the object is written into. @param bCloseWriter	When set to true the Writer will be closed after the serialization. @return				Returns true if the serialization was successful, false otherwise.
- L487 _public function_ `template <class CharType, class PrintPolicy> static bool Serialize(const typename Policy::FMapOfValues& Object, TJsonWriter<CharType, PrintPolicy>& Writer, bool bCloseWriter = true)` — Serialize the passed map of values into the writer. This will effectively serialize all of the identifier:value pairs of the map, enclosed in {} curly brackets. Json Example: - Writer state: [123 <writer position> Parameter: Object: {"foo": "bar", "baz": "", "": 456} Serialization result: [123, {"foo": "bar", "baz": "", "": 456} <writer position> @param Object		The map of values we are serializing @param Writer		The writer the object is written into. @param bCloseWriter	When set to true the Writer will be closed after the serialization. @return				Returns true if the serialization was successful, false otherwise.
- L495 _private function_ `template <class CharType> static bool Deserialize(TJsonReader<CharType>& Reader, typename Policy::FStackState& OutStackState, EFlags InOptions)`
- L620 _private function_ `template <class CharType, class PrintPolicy> static bool Serialize(const TSharedRef<typename Policy::FElement>& StartingElement, TJsonWriter<CharType, PrintPolicy>& Writer, bool bCloseWriter)`

#### enum `TJsonSerializer::EFlags`  
`enum class EFlags`  
_L294-298_
- L296 _public enumerator_ `None = 0`
- L297 _public enumerator_ `StoreNumbersAsStrings = 1`

#### Free symbols / members of external scopes

- L93 _typedef_ `using StoredCharType = typename TJsonReader<CharType>::StoredCharType;` (scope `FJsonSerializerPolicy_JsonObject::ReadString`)
- L100 _typedef_ `using StoredCharType = typename TJsonReader<CharType>::StoredCharType;` (scope `FJsonSerializerPolicy_JsonObject::ReadNumberAsString`)
- L676 _typedef_ `using FJsonSerializer = TJsonSerializer<FJsonSerializerPolicy_JsonObject>;`

### `Source/Runtime/Json/Public/Serialization/JsonSerializerBase.h` (Public)


#### struct `FJsonSerializerBase`  
`struct FJsonSerializerBase`  
_L11-64_
- desc: Base interface used to serialize to/from JSON. Hides the fact there are separate read/write classes
- L13 _public prototype_ `virtual bool IsLoading() const = 0;`
- L14 _public prototype_ `virtual bool IsSaving() const = 0;`
- L15 _public prototype_ `virtual void StartObject() = 0;`
- L16 _public prototype_ `virtual void StartObject(FStringView Name) = 0;`
- L17 _public prototype_ `virtual void EndObject() = 0;`
- L18 _public prototype_ `virtual void StartArray() = 0;`
- L19 _public prototype_ `virtual void StartArray(FStringView Name) = 0;`
- L20 _public prototype_ `virtual void EndArray() = 0;`
- L21 _public prototype_ `virtual void Serialize(FStringView Name, int32& Value) = 0;`
- L22 _public prototype_ `virtual void Serialize(FStringView Name, uint32& Value) = 0;`
- L23 _public prototype_ `virtual void Serialize(FStringView Name, int64& Value) = 0;`
- L24 _public prototype_ `virtual void Serialize(FStringView Name, bool& Value) = 0;`
- L25 _public prototype_ `virtual void Serialize(FStringView Name, FString& Value) = 0;`
- L26 _public prototype_ `virtual void Serialize(FStringView Name, FUtf8String& Value) = 0;`
- L27 _public prototype_ `virtual void Serialize(FStringView Name, FText& Value) = 0;`
- L28 _public prototype_ `virtual void Serialize(FStringView Name, float& Value) = 0;`
- L29 _public prototype_ `virtual void Serialize(FStringView Name, double& Value) = 0;`
- L30 _public prototype_ `virtual void Serialize(FStringView Name, FDateTime& Value) = 0;`
- L31 _public prototype_ `virtual void Serialize(FStringView Name, JsonSimpleValueVariant& InVariant) = 0;`
- L32 _public prototype_ `virtual void SerializeArray(FJsonSerializableArray& Array) = 0;`
- L33 _public prototype_ `virtual void SerializeArray(FStringView Name, FJsonSerializableArray& Value) = 0;`
- L34 _public prototype_ `virtual void SerializeArray(FStringView Name, FJsonSerializableArrayInt& Value) = 0;`
- L35 _public prototype_ `virtual void SerializeArray(FStringView Name, FJsonSerializableArrayFloat& Value) = 0;`
- L36 _public prototype_ `virtual void SerializeMap(FStringView Name, FJsonSerializableKeyValueMap& Map) = 0;`
- L37 _public prototype_ `virtual void SerializeMap(FStringView Name, FJsonSerializableKeyValueMapInt& Map) = 0;`
- L38 _public prototype_ `virtual void SerializeMap(FStringView Name, FJsonSerializableKeyValueMapArrayInt& Map) = 0;`
- L39 _public prototype_ `virtual void SerializeMap(FStringView Name, FJsonSerializableKeyValueMapInt64& Map) = 0;`
- L40 _public prototype_ `virtual void SerializeMap(FStringView Name, FJsonSerializableKeyValueMapFloat& Map) = 0;`
- L41 _public prototype_ `virtual void SerializeMap(FStringView Name, FJsonSerializableKeySimpleValueVariantMap& Map) = 0;`
- L42 _public prototype_ `virtual void SerializeSimpleMap(FJsonSerializableKeyValueMap& Map) = 0;`
- L43 _public prototype_ `virtual void SerializeMapSafe(FStringView Name, FJsonSerializableKeyValueMap& Map) = 0;`
- L44 _public prototype_ `virtual TSharedPtr<FJsonObject> GetObject() = 0;`
- L45 _public prototype_ `virtual void WriteIdentifierPrefix(FStringView Name) = 0;`
- L46 _public prototype_ `virtual void WriteRawJSONValue(FStringView Value) = 0;`
- L47 _public prototype_ `virtual void WriteRawJSONValue(FUtf8StringView Value) = 0;`
- L52 _public function_ `void StartObject(FAnsiStringView Name)` — `UE_DEPRECATED(5.4, "Passing an ANSI string to StartObject has been deprecated outside of UTF-8 mode. Please use the overload that takes a TCHAR string.")`
- L58 _public function_ `void StartArray(FAnsiStringView Name)` — `UE_DEPRECATED(5.4, "Passing an ANSI string to StartArray has been deprecated outside of UTF-8 mode. Please use the overload that takes a TCHAR string.")`

### `Source/Runtime/Json/Public/Serialization/JsonSerializerMacros.h` (Public)


#### Free symbols / members of external scopes

- L21 _macro_ `#define BEGIN_JSON_SERIALIZER \` — Macros used to generate a serialization function for a class derived from FJsonSerializable
- L26 _macro_ `#define END_JSON_SERIALIZER \`
- L30 _macro_ `#define JSON_SERIALIZE(JsonName, JsonValue) \`
- L33 _macro_ `#define JSON_SERIALIZE_NAME(JsonName, JsonValue) \`
- L46 _macro_ `#define JSON_SERIALIZE_WITHDEFAULT(JsonName, JsonValue, DefaultJsonValue) \`
- L56 _macro_ `#define JSON_SERIALIZE_OPTIONAL(JsonName, OptionalJsonValue) \`
- L72 _macro_ `#define JSON_SERIALIZE_OPTIONAL_MAP(JsonName, JsonMap) \`
- L83 _macro_ `#define JSON_SERIALIZE_OPTIONAL_ARRAY(JsonName, JsonArray) \`
- L94 _macro_ `#define JSON_SERIALIZE_ARRAY(JsonName, JsonArray) \`
- L97 _macro_ `#define JSON_SERIALIZE_ARRAY_WITHDEFAULT(JsonName, JsonArray, DefaultArray) \`
- L107 _macro_ `#define JSON_SERIALIZE_OBJECT_WITHDEFAULT(JsonName, JsonObject, DefaultObject) \`
- L117 _macro_ `#define JSON_SERIALIZE_MAP(JsonName, JsonMap) \`
- L120 _macro_ `#define JSON_SERIALIZE_SIMPLECOPY(JsonMap) \`
- L123 _macro_ `#define JSON_SERIALIZE_MAP_SAFE(JsonName, JsonMap) \`
- L126 _macro_ `#define JSON_SERIALIZE_RAW_JSON_STRING(JsonName, JsonValue) \`
- L153 _macro_ `#define JSON_SERIALIZE_ARRAY_SERIALIZABLE(JsonName, JsonArray, ElementType) \`
- L175 _macro_ `#define JSON_SERIALIZE_ARRAY_SERIALIZABLE_WITHDEFAULT(JsonName, JsonArray, ElementType, DefaultArray) \`
- L201 _macro_ `#define JSON_SERIALIZE_OPTIONAL_ARRAY_SERIALIZABLE(JsonName, OptionalJsonArray, ElementType) \`
- L227 _macro_ `#define JSON_SERIALIZE_MAP_SERIALIZABLE(JsonName, JsonMap, ElementType) \`
- L253 _macro_ `#define JSON_SERIALIZE_MAP_ARRAY_SERIALIZABLE(JsonName, JsonMap, ElementType) \`
- L286 _macro_ `#define JSON_SERIALIZE_MEMBERS_OF(JsonValue) \` — Use this to read/write JsonValue with its own keys and values corresponding to its members
- L289 _macro_ `#define JSON_SERIALIZE_SERIALIZABLE(JsonName, JsonValue) UE_DEPRECATED_MACRO(5.6, "JSON_SERIALIZE_SERIALIZABLE has been deprecated, use JSON_SERIALIZE_MEMBERS_OF instead") JSON_SERIALIZE_MEMBERS_OF(JsonValue)`
- L292 _macro_ `#define JSON_SERIALIZE_OBJECT_SERIALIZABLE(JsonName, JsonSerializableObject) \` — Use this when JsonSerializableObject will be read/write as json object, while JsonName is the key
- L314 _macro_ `#define JSON_SERIALIZE_OBJECT_SERIALIZABLE_WITHDEFAULT(JsonName, JsonSerializableObject, JsonSerializableObjectDefault) \`
- L340 _macro_ `#define JSON_SERIALIZE_OPTIONAL_OBJECT_SERIALIZABLE(JsonName, JsonSerializableObject) \`
- L364 _macro_ `#define JSON_SERIALIZE_SHARED_OBJECT_SERIALIZABLE(JsonName, JsonSerializableObject) \`
- L388 _macro_ `#define JSON_SERIALIZE_DATETIME_UNIX_TIMESTAMP(JsonName, JsonDateTime) \`
- L401 _macro_ `#define JSON_SERIALIZE_DATETIME_UNIX_TIMESTAMP_MILLISECONDS(JsonName, JsonDateTime) \`
- L414 _macro_ `#define JSON_SERIALIZE_ENUM(JsonName, JsonEnum) \`
- L427 _macro_ `#define JSON_SERIALIZE_ENUM_ARRAY(JsonName, JsonArray, EnumType) \`
- L454 _macro_ `#define JSON_SERIALIZE_PRIVATE_VARIANT_BEGIN(JsonName, JsonValue) \` — Private macros for Variant JSON serialization
- L485 _macro_ `#define JSON_SERIALIZE_PRIVATE_VARIANT_END() \`
- L497 _macro_ `#define JSON_SERIALIZE_VARIANT_BEGIN(JsonName, JsonValue) \` — Macros for begin/end of regular TVariant<...> value, insert JSON_SERIALIZE_VARIANT_IFTYPE_SERIALIZABLE in between BEGIN/END pair
- L503 _macro_ `#define JSON_SERIALIZE_VARIANT_END() \`
- L510 _macro_ `#define JSON_SERIALIZE_OPTIONAL_VARIANT_BEGIN(JsonName, JsonValue) \` — Macros for begin/end of TOptional<TVariant<...>> value, insert JSON_SERIALIZE_VARIANT_IFTYPE_SERIALIZABLE in between BEGIN/END pair
- L523 _macro_ `#define JSON_SERIALIZE_OPTIONAL_VARIANT_END() \`
- L530 _macro_ `#define JSON_SERIALIZE_VARIANT_IFTYPE_SERIALIZABLE(TypeName, Type) \` — Macros for serializing a specific sub type of a variant, only to be insert in between (optional) VARIANT begin/end pair

### `Source/Runtime/Json/Public/Serialization/JsonSerializerReader.h` (Public)


#### class `FJsonSerializerReader`  
`class FJsonSerializerReader : public FJsonSerializerBase`  
_L11-214_
- inherits: `FJsonSerializerBase`
- desc: Implements the abstract serializer interface hiding the underlying reader object
- L19 _public prototype_ `FJsonSerializerReader(TSharedPtr<FJsonObject> InJsonObject);` — Inits the base JSON object that is being read from @param InJsonObject the JSON object to serialize from
- L21 _public prototype_ `virtual ~FJsonSerializerReader();`
- L24 _public prototype_ `virtual bool IsLoading() const override;` — Is the JSON being read from
- L26 _public prototype_ `virtual bool IsSaving() const override;` — Is the JSON being written to
- L28 _public prototype_ `virtual TSharedPtr<FJsonObject> GetObject() override;` — Access to the root Json object being read
- L31 _public prototype_ `virtual void StartObject() override;` — Ignored
- L33 _public prototype_ `virtual void StartObject(FStringView Name) override;` — Ignored
- L35 _public prototype_ `virtual void EndObject() override;` — Ignored
- L37 _public prototype_ `virtual void StartArray() override;` — Ignored
- L39 _public prototype_ `virtual void StartArray(FStringView Name) override;` — Ignored
- L41 _public prototype_ `virtual void EndArray() override;` — Ignored
- L48 _public prototype_ `virtual void Serialize(FStringView Name, int32& Value) override;` — If the underlying json object has the field, it is read into the value @param Name the name of the field to read @param Value the out value to read the data into
- L55 _public prototype_ `virtual void Serialize(FStringView Name, uint32& Value) override;` — If the underlying json object has the field, it is read into the value @param Name the name of the field to read @param Value the out value to read the data into
- L62 _public prototype_ `virtual void Serialize(FStringView Name, int64& Value) override;` — If the underlying json object has the field, it is read into the value @param Name the name of the field to read @param Value the out value to read the data into
- L69 _public prototype_ `virtual void Serialize(FStringView Name, bool& Value) override;` — If the underlying json object has the field, it is read into the value @param Name the name of the field to read @param Value the out value to read the data into
- L76 _public prototype_ `virtual void Serialize(FStringView Name, FString& Value) override;` — If the underlying json object has the field, it is read into the value @param Name the name of the field to read @param Value the out value to read the data into
- L83 _public prototype_ `virtual void Serialize(FStringView Name, FUtf8String& Value) override;` — If the underlying json object has the field, it is read into the value @param Name the name of the field to read @param Value the out value to read the data into
- L90 _public prototype_ `virtual void Serialize(FStringView Name, FText& Value) override;` — If the underlying json object has the field, it is read into the value @param Name the name of the field to read @param Value the out value to read the data into
- L97 _public prototype_ `virtual void Serialize(FStringView Name, float& Value) override;` — If the underlying json object has the field, it is read into the value @param Name the name of the field to read @param Value the out value to read the data into
- L104 _public prototype_ `virtual void Serialize(FStringView Name, double& Value) override;` — If the underlying json object has the field, it is read into the value @param Name the name of the field to read @param Value the out value to read the data into
- L111 _public prototype_ `virtual void Serialize(FStringView Name, FDateTime& Value) override;` — Writes the field name and the corresponding value to the JSON data @param Name the field name to write out @param Value the value to write out
- L118 _public prototype_ `virtual void Serialize(FStringView Name, JsonSimpleValueVariant& InVariant) override;` — Writes the field name and the corresponding value to the JSON data @param Name the field name to write out @param Value the value to write out
- L126 _public prototype_ `virtual void SerializeArray(FJsonSerializableArray& Array) override;` — Serializes an array of values @param Name the name of the property to serialize @param Array the array to serialize
- L133 _public prototype_ `virtual void SerializeArray(FStringView Name, FJsonSerializableArray& Array) override;` — Serializes an array of values with an identifier @param Name the name of the property to serialize @param Array the array to serialize
- L140 _public prototype_ `virtual void SerializeArray(FStringView Name, FJsonSerializableArrayInt& Array) override;` — Serializes an array of values with an identifier @param Name the name of the property to serialize @param Array the array to serialize
- L147 _public prototype_ `virtual void SerializeArray(FStringView Name, FJsonSerializableArrayFloat& Array) override;` — Serializes an array of values with an identifier @param Name the name of the property to serialize @param Array the array to serialize
- L154 _public prototype_ `virtual void SerializeMap(FStringView Name, FJsonSerializableKeyValueMap& Map) override;` — Serializes the keys & values for map @param Name the name of the property to serialize @param Map the map to serialize
- L162 _public prototype_ `virtual void SerializeMap(FStringView Name, FJsonSerializableKeyValueMapInt& Map) override;` — Serializes the keys & values for map @param Name the name of the property to serialize @param Map the map to serialize
- L170 _public prototype_ `virtual void SerializeMap(FStringView Name, FJsonSerializableKeyValueMapArrayInt& Map) override;` — Serializes the keys & values for map @param Name the name of the property to serialize @param Map the map to serialize
- L178 _public prototype_ `virtual void SerializeMap(FStringView Name, FJsonSerializableKeyValueMapInt64& Map) override;` — Serializes the keys & values for map @param Name the name of the property to serialize @param Map the map to serialize
- L186 _public prototype_ `virtual void SerializeMap(FStringView Name, FJsonSerializableKeyValueMapFloat& Map) override;` — Serializes the keys & values for map @param Name the name of the property to serialize @param Map the map to serialize
- L194 _public prototype_ `virtual void SerializeMap(FStringView Name, FJsonSerializableKeySimpleValueVariantMap& Map) override;` — Serializes the keys & values for map @param Name the name of the property to serialize @param Map the map to serialize
- L196 _public prototype_ `virtual void SerializeSimpleMap(FJsonSerializableKeyValueMap& Map) override;`
- L204 _public prototype_ `virtual void SerializeMapSafe(FStringView Name, FJsonSerializableKeyValueMap& Map) override;` — Deserializes keys and values from an object into a map, but only if the value is trivially convertable to string. @param Name Name of property to deserialize @param Map The Map to fill with String values found
- L206 _public prototype_ `virtual void WriteIdentifierPrefix(FStringView Name) override;`
- L208 _public prototype_ `virtual void WriteRawJSONValue(FStringView Value) override;`
- L210 _public prototype_ `virtual void WriteRawJSONValue(FUtf8StringView Value) override;`
- L213 _private member_ `TSharedPtr<FJsonObject> JsonObject;` — The object that holds the parsed JSON data

### `Source/Runtime/Json/Public/Serialization/JsonSerializerWriter.h` (Public)


#### class `FJsonSerializerWriter`  
`template <class CharType = TCHAR, class PrintPolicy = TPrettyJsonPrintPolicy<CharType> > class FJsonSerializerWriter : public FJsonSerializerBase`  
_L14-407_
- inherits: `FJsonSerializerBase`
- desc: Implements the abstract serializer interface hiding the underlying writer object
- L18 _private member_ `TSharedRef<TJsonWriter<CharType, PrintPolicy> > JsonWriter;` — The object to write the JSON output to
- L27 _public function_ `FJsonSerializerWriter(TSharedRef<TJsonWriter<CharType, PrintPolicy> > InJsonWriter) : JsonWriter(InJsonWriter)` — Initializes the writer object @param InJsonWriter the object to write the JSON output to
- L32 _public prototype_ `virtual ~FJsonSerializerWriter() = default;`
- L35 _public function_ `virtual bool IsLoading() const override` — Is the JSON being read from
- L37 _public function_ `virtual bool IsSaving() const override` — Is the JSON being written to
- L39 _public function_ `virtual TSharedPtr<FJsonObject> GetObject() override` — Access to the root object
- L44 _public function_ `virtual void StartObject() override` — Starts a new object "{"
- L52 _public function_ `virtual void StartObject(FStringView Name) override` — Starts a new object "{"
- L59 _public function_ `virtual void EndObject() override` — Completes the definition of an object "}"
- L64 _public function_ `virtual void StartArray() override`
- L69 _public function_ `virtual void StartArray(FStringView Name) override`
- L74 _public function_ `virtual void EndArray() override`
- L84 _public function_ `virtual void Serialize(FStringView Name, int32& Value) override` — Writes the field name and the corresponding value to the JSON data @param Name the field name to write out @param Value the value to write out
- L94 _public function_ `virtual void Serialize(FStringView Name, uint32& Value) override` — Writes the field name and the corresponding value to the JSON data @param Name the field name to write out @param Value the value to write out
- L104 _public function_ `virtual void Serialize(FStringView Name, int64& Value) override` — Writes the field name and the corresponding value to the JSON data @param Name the field name to write out @param Value the value to write out
- L114 _public function_ `virtual void Serialize(FStringView Name, bool& Value) override` — Writes the field name and the corresponding value to the JSON data @param Name the field name to write out @param Value the value to write out
- L124 _public function_ `virtual void Serialize(FStringView Name, FString& Value) override` — Writes the field name and the corresponding value to the JSON data @param Name the field name to write out @param Value the value to write out
- L134 _public function_ `virtual void Serialize(FStringView Name, FUtf8String& Value) override` — Writes the field name and the corresponding value to the JSON data @param Name the field name to write out @param Value the value to write out
- L144 _public function_ `virtual void Serialize(FStringView Name, FText& Value) override` — Writes the field name and the corresponding value to the JSON data @param Name the field name to write out @param Value the value to write out
- L154 _public function_ `virtual void Serialize(FStringView Name, float& Value) override` — Writes the field name and the corresponding value to the JSON data @param Name the field name to write out @param Value the value to write out
- L164 _public function_ `virtual void Serialize(FStringView Name, double& Value) override` — Writes the field name and the corresponding value to the JSON data @param Name the field name to write out @param Value the value to write out
- L174 _public function_ `virtual void Serialize(FStringView Name, FDateTime& Value) override` — Writes the field name and the corresponding value to the JSON data @param Name the field name to write out @param Value the value to write out
- L182 _public function_ `virtual void Serialize(FStringView Name, JsonSimpleValueVariant& InVariant) override`
- L207 _public function_ `virtual void SerializeArray(FJsonSerializableArray& Array) override` — Serializes an array of values @param Name the name of the property to serialize @param Array the array to serialize
- L223 _public function_ `virtual void SerializeArray(FStringView Name, FJsonSerializableArray& Array) override` — Serializes an array of values with an identifier @param Name the name of the property to serialize @param Array the array to serialize
- L239 _public function_ `virtual void SerializeArray(FStringView Name, FJsonSerializableArrayInt& Array) override` — Serializes an array of values with an identifier @param Name the name of the property to serialize @param Array the array to serialize
- L256 _public function_ `virtual void SerializeArray(FStringView Name, FJsonSerializableArrayFloat& Array) override` — Serializes an array of values with an identifier @param Name the name of the property to serialize @param Array the array to serialize
- L273 _public function_ `virtual void SerializeMap(FStringView Name, FJsonSerializableKeyValueMap& Map) override` — Serializes the keys & values for map @param Name the name of the property to serialize @param Map the map to serialize
- L290 _public function_ `virtual void SerializeMap(FStringView Name, FJsonSerializableKeyValueMapInt& Map) override` — Serializes the keys & values for map @param Name the name of the property to serialize @param Map the map to serialize
- L306 _public function_ `virtual void SerializeMap(FStringView Name, FJsonSerializableKeyValueMapArrayInt& Map) override` — Serializes the keys & values for map @param Name the name of the property to serialize @param Map the map to serialize
- L323 _public function_ `virtual void SerializeMap(FStringView Name, FJsonSerializableKeyValueMapInt64& Map) override` — Serializes the keys & values for map @param Name the name of the property to serialize @param Map the map to serialize
- L340 _public function_ `virtual void SerializeMap(FStringView Name, FJsonSerializableKeyValueMapFloat& Map) override` — Serializes the keys & values for map @param Name the name of the property to serialize @param Map the map to serialize
- L351 _public function_ `virtual void SerializeMap(FStringView Name, FJsonSerializableKeySimpleValueVariantMap& Map) override`
- L376 _public function_ `virtual void SerializeSimpleMap(FJsonSerializableKeyValueMap& Map) override`
- L388 _public function_ `virtual void SerializeMapSafe(FStringView Name, FJsonSerializableKeyValueMap& Map)` — Serializes keys and values from an object into a map. @param Name Name of property to serialize @param Map The Map to copy String values from
- L393 _public function_ `virtual void WriteIdentifierPrefix(FStringView Name)`
- L398 _public function_ `virtual void WriteRawJSONValue(FStringView Value)`
- L403 _public function_ `virtual void WriteRawJSONValue(FUtf8StringView Value)`

#### Free symbols / members of external scopes

- L185 _function_ `` (scope `FJsonSerializerWriter::Serialize`)
- L186 _typedef_ `using StoredValueType = std::decay_t<decltype(StoredValue)>;` (scope `FJsonSerializerWriter::Serialize::__anonc5c945b40102`)
- L190 _function_ `` (scope `FJsonSerializerWriter::Serialize::__anonc5c945b40102`)
- L358 _function_ `` (scope `FJsonSerializerWriter::SerializeMap`)
- L359 _typedef_ `using StoredValueType = std::decay_t<decltype(StoredValue)>;` (scope `FJsonSerializerWriter::SerializeMap::__anonc5c945b40302`)
- L363 _function_ `` (scope `FJsonSerializerWriter::SerializeMap::__anonc5c945b40302`)

### `Source/Runtime/Json/Public/Serialization/JsonTypes.h` (Public)


#### enum `EJson`  
`enum class EJson`  
_L22-31_
- desc: Represents all the types a Json Value can be.
- L24 _public enumerator_ `None`
- L25 _public enumerator_ `Null`
- L26 _public enumerator_ `String`
- L27 _public enumerator_ `Number`
- L28 _public enumerator_ `Boolean`
- L29 _public enumerator_ `Array`
- L30 _public enumerator_ `Object`

#### enum `EJsonToken`  
`enum class EJsonToken`  
_L34-52_
- L36 _public enumerator_ `None`
- L37 _public enumerator_ `Comma`
- L38 _public enumerator_ `CurlyOpen`
- L39 _public enumerator_ `CurlyClose`
- L40 _public enumerator_ `SquareOpen`
- L41 _public enumerator_ `SquareClose`
- L42 _public enumerator_ `Colon`
- L43 _public enumerator_ `String`
- L46 _public enumerator_ `Number` — short values
- L47 _public enumerator_ `True`
- L48 _public enumerator_ `False`
- L49 _public enumerator_ `Null`
- L51 _public enumerator_ `Identifier`

#### enum `EJsonNotation`  
`enum class EJsonNotation`  
_L59-70_
- L61 _public enumerator_ `ObjectStart`
- L62 _public enumerator_ `ObjectEnd`
- L63 _public enumerator_ `ArrayStart`
- L64 _public enumerator_ `ArrayEnd`
- L65 _public enumerator_ `Boolean`
- L66 _public enumerator_ `String`
- L67 _public enumerator_ `Number`
- L68 _public enumerator_ `Null`
- L69 _public enumerator_ `Error`

#### Free symbols / members of external scopes

- L54 _function_ `inline bool EJsonToken_IsShortValue(EJsonToken Token)`
- L73 _typedef_ `using FJsonSerializableArray = TArray<FString>;` — Array of data
- L74 _typedef_ `using FJsonSerializableArrayInt = TArray<int32>;`
- L75 _typedef_ `using FJsonSerializableArrayFloat = TArray<float>;`
- L78 _typedef_ `using FJsonSerializableKeyValueMap = TMap<FString, FString>;` — Maps a key to a value
- L79 _typedef_ `using FJsonSerializableKeyValueMapInt = TMap<FString, int32>;`
- L80 _typedef_ `using FJsonSerializableKeyValueMapInt64 = TMap<FString, int64>;`
- L81 _typedef_ `using FJsonSerializableKeyValueMapFloat = TMap<FString, float>;`
- L82 _typedef_ `using FJsonSerializableKeyValueMapArrayInt = TMap<FString, FJsonSerializableArrayInt>;`
- L85 _typedef_ `using JsonNumberValueVariants = TVariant<int32, uint32, int64, float, double>;` — We always read with the highest precisions (int64 or double), but we can write with any level of precision
- L87 _typedef_ `using JsonSimpleValueVariant = TVariant<bool , JsonNumberValueVariants , FString >;`
- L90 _typedef_ `using FJsonSerializableKeySimpleValueVariantMap = TMap<FString, JsonSimpleValueVariant>;` — Helps keep key values unique

### `Source/Runtime/Json/Public/Serialization/JsonWriter.h` (Public)


#### class `TJsonWriter`  
`template <class CharType = TCHAR, class PrintPolicy = TPrettyJsonPrintPolicy<CharType> > class TJsonWriter`  
_L84-731_
- desc: Template for Json writers. @param CharType The type of characters to print, i.e. TCHAR or ANSICHAR. @param PrintPolicy The print policy to use when writing the output string (default = TPrettyJsonPrintPolicy).
- L88 _public function_ `static TSharedRef< TJsonWriter > Create( FArchive* const Stream, int32 InitialIndentLevel = 0 )`
- L95 _public prototype_ `virtual ~TJsonWriter() = default;`
- L97 _public function_ `inline int32 GetIndentLevel() const`
- L99 _public function_ `bool CanWriteObjectStart() const`
- L104 _public function_ `EJson GetCurrentElementType() const`
- L109 _public function_ `void WriteObjectStart()`
- L127 _public function_ `template<typename IdentifierType> void WriteObjectStart(IdentifierType&& Identifier)`
- L140 _public function_ `void WriteObjectEnd()`
- L153 _public function_ `void WriteArrayStart()`
- L171 _public function_ `template<typename IdentifierType> void WriteArrayStart(IdentifierType&& Identifier)`
- L183 _public function_ `void WriteArrayEnd()`
- L201 _public function_ `void WriteValue(uint8 Value)` — Special case for bit fields
- L220 _public function_ `template <class FValue> void WriteValue(FValue&& Value)`
- L238 _public function_ `void WriteValue(FStringView Value)`
- L248 _public function_ `void WriteValue(const FString& Value)`
- L260 _public function_ `template<typename IdentifierType> void WriteValue(IdentifierType&& Identifier, uint8 Value)` — Special case for bit fields
- L270 _public function_ `template<class FValue, typename IdentifierType> void WriteValue(IdentifierType&& Identifier, FValue&& Value)`
- L280 _public function_ `template<class ElementType, typename IdentifierType> void WriteValue(IdentifierType&& Identifier, const TArray<ElementType>& Array)`
- L291 _public function_ `template<typename IdentifierType, typename MapIdentifierType, class MapElementType> void WriteValue(IdentifierType&& Identifier, const TMap<MapIdentifierType, MapElementType>& Map)`
- L302 _public function_ `template<typename MapIdentifierType, class MapElementType> void WriteValue(const TMap<MapIdentifierType, MapElementType>& Map)`
- L312 _public function_ `void WriteValue(FStringView Identifier, const TCHAR* Value)`
- L319 _public function_ `void WriteRawJSONValue( FStringView Identifier, FStringView Value )` — WARNING: THIS IS DANGEROUS. Use this only if you know for a fact that the Value is valid JSON! Use this to insert the results of a different JSON Writer in.
- L326 _public function_ `void WriteRawJSONValue( FUtf8StringView Identifier, FUtf8StringView Value )` — WARNING: THIS IS DANGEROUS. Use this only if you know for a fact that the Value is valid JSON! Use this to insert the results of a different JSON Writer in.
- L332 _public function_ `template<typename IdentifierType> void WriteNull(IdentifierType&& Identifier)`
- L337 _public function_ `void WriteValue(const TCHAR* Value)`
- L344 _public function_ `void WriteRawJSONValue(FStringView Value)` — WARNING: THIS IS DANGEROUS. Use this only if you know for a fact that the Value is valid JSON! Use this to insert the results of a different JSON Writer in.
- L351 _public function_ `void WriteRawJSONValue(FUtf8StringView Value)` — WARNING: THIS IS DANGEROUS. Use this only if you know for a fact that the Value is valid JSON! Use this to insert the results of a different JSON Writer in.
- L356 _public function_ `void WriteNull()`
- L361 _public function_ `virtual bool Close()`
- L373 _public function_ `template<typename IdentifierType> void WriteIdentifierPrefix(IdentifierType&& Identifier)` — WriteValue("Foo", Bar) should be equivalent to WriteIdentifierPrefix("Foo"), WriteValue(Bar)
- L389 _protected function_ `TJsonWriter( FArchive* const InStream, int32 InitialIndentLevel ) : Stream( InStream ) , Stack() , PreviousTokenWritten(EJsonToken::None) , IndentLevel(InitialIndentLevel)` — Creates and initializes a new instance. @param InStream An archive containing the input. @param InitialIndentLevel The initial indentation level.
- L398 _protected function_ `inline bool CanWriteValueWithoutIdentifier() const`
- L403 _protected function_ `inline bool CanWriteObjectWithoutIdentifier() const`
- L408 _protected function_ `inline void WriteCommaIfNeeded()`
- L419 _protected function_ `template <typename InCharType> void WriteIdentifier(const InCharType* Identifier)`
- L432 _protected function_ `template <typename InCharType> void WriteIdentifier(TStringView<InCharType> Identifier)`
- L444 _protected function_ `void WriteIdentifier(const FText& Identifier)`
- L449 _protected function_ `inline void WriteIdentifier(const FString& Identifier)`
- L461 _protected function_ `inline EJsonToken WriteValueOnly(bool Value)`
- L467 _protected function_ `inline EJsonToken WriteValueOnly(float Value)`
- L473 _protected function_ `inline EJsonToken WriteValueOnly(double Value)`
- L481 _protected function_ `inline EJsonToken WriteValueOnly(int32 Value)`
- L486 _protected function_ `inline EJsonToken WriteValueOnly(int64 Value)`
- L493 _protected function_ `inline EJsonToken WriteValueOnly(uint8 Value)` — Special case for bit fields
- L498 _protected function_ `inline EJsonToken WriteValueOnly(uint32 Value)`
- L503 _protected function_ `inline EJsonToken WriteValueOnly(uint64 Value)`
- L509 _protected function_ `inline EJsonToken WriteValueOnly(TYPE_OF_NULLPTR)`
- L515 _protected function_ `inline EJsonToken WriteValueOnly(const TCHAR* Value)`
- L521 _protected function_ `inline EJsonToken WriteValueOnly(FStringView Value)`
- L527 _protected function_ `inline EJsonToken WriteValueOnly(FUtf8StringView Value)`
- L534 _protected function_ `template<typename ValueType> EJsonToken WriteValueOnly(TSharedRef<ValueType> ValueRef)`
- L540 _protected function_ `template<typename ValueType> EJsonToken WriteValueOnly(TSharedPtr<ValueType> ValuePtr)`
- L553 _protected function_ `template<typename... ValueTypes> EJsonToken WriteValueOnly(const TVariant<ValueTypes...>& Variant)`
- L562 _protected function_ `template<typename MapIdentifierType, typename MapElementType> EJsonToken WriteValueOnly(const TMap<MapIdentifierType, MapElementType>& Map)`
- L575 _protected function_ `template<typename ArrayElementType> EJsonToken WriteValueOnly(const TArray<ArrayElementType>& Array)`
- L587 _protected function_ `virtual void WriteStringValue(FAnsiStringView String)`
- L594 _protected function_ `virtual void WriteStringValue(FStringView String)`
- L601 _protected function_ `virtual void WriteStringValue(const FString& String)`
- L606 _protected function_ `virtual void WriteStringValue(FUtf8StringView String)`
- L613 _protected function_ `virtual void WriteStringValue(const FUtf8String& String)`
- L621 _protected function_ `template <typename InCharType> void WriteRawJSONValueImpl(FStringView Identifier, TStringView<InCharType> Value)` — WARNING: THIS IS DANGEROUS. Use this only if you know for a fact that the Value is valid JSON! Use this to insert the results of a different JSON Writer in.
- L632 _protected function_ `template <typename InCharType> void WriteRawJSONValueImpl(TStringView<InCharType> Value)`
- L652 _protected function_ `template<typename InCharType> void WriteEscapedString(TStringView<InCharType> InView)`
- L727 _protected member_ `FArchive* const Stream;`
- L728 _protected member_ `TArray<EJson> Stack;`
- L729 _protected member_ `EJsonToken PreviousTokenWritten;`
- L730 _protected member_ `int32 IndentLevel;`

#### class `TJsonStringWriter`  
`template <class PrintPolicy = TPrettyJsonPrintPolicy<TCHAR>> class TJsonStringWriter : public TJsonWriter<typename PrintPolicy::CharType, PrintPolicy>`  
_L735-775_
- inherits: `TJsonWriter<typenamePrintPolicy::CharType,PrintPolicy>`
- L739 _public typedef_ `using CharType = typename PrintPolicy::CharType;`
- L740 _public typedef_ `using StringType = TString<CharType>;`
- L742 _public function_ `static TSharedRef<TJsonStringWriter> Create(StringType* const InStream, int32 InitialIndent = 0 )`
- L749 _public function_ `virtual ~TJsonStringWriter()`
- L755 _public function_ `virtual bool Close() override`
- L765 _protected function_ `TJsonStringWriter(StringType* const InOutString, int32 InitialIndent ) : TJsonWriter<CharType, PrintPolicy>(new FMemoryWriter(Bytes), InitialIndent) , Bytes() , OutString(InOutString)`
- L773 _private member_ `TArray<uint8> Bytes;`
- L774 _private member_ `StringType* OutString;`

#### class `TJsonWriterFactory`  
`template <class CharType = TCHAR, class PrintPolicy = TPrettyJsonPrintPolicy<CharType>> class TJsonWriterFactory`  
_L778-792_
- L781 _public typedef_ `using StringType = TString<CharType>;`
- L783 _public function_ `static TSharedRef<TJsonWriter<CharType, PrintPolicy>> Create(FArchive* const Stream, int32 InitialIndent = 0)`
- L788 _public function_ `static TSharedRef<TJsonWriter<CharType, PrintPolicy>> Create(StringType* const Stream, int32 InitialIndent = 0)`

#### Free symbols / members of external scopes

- L18 _function_ `template <typename DstChar, typename SrcChar> bool HasDestinationJsonStringCharRepresentation(SrcChar Char)` — Takes an input source char representing and returns if it is possible to represent in DstChar expected encoding @param Char source char @return false if character is a control char or if it is out of range of representation in case of converting to ANSICHAR. true otherwise
- L33 _function_ `template<typename StringType> inline StringType& AppendEscapeJsonString(StringType& AppendTo, const FString& StringVal)` — Takes an input string and escapes it so it can be written as a valid Json string. Also adds the quotes. Appends to a given string-like object to avoid reallocations. String-like object must support operator+=(const TCHAR*) and operation+=(TCHAR) @param AppendTo the string to append to. @param StringVal the string to escape @return the AppendTo string for convenience.
- L35 _typedef_ `using CharType = typename StringType::ElementType;` (scope `AppendEscapeJsonString`)
- L71 _function_ `inline FString EscapeJsonString(const FString& StringVal)` — Takes an input string and escapes it so it can be written as a valid Json string. Also adds the quotes. @param StringVal the string to escape @return the given string, escaped to produce a valid Json string.
- L556 _function_ `` (scope `TJsonWriter::WriteValueOnly`)
- L655 _function_ `` (scope `TJsonWriter::WriteEscapedString`)
