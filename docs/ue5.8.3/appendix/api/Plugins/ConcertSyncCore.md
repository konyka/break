# Plugins / ConcertSyncCore

- module root: `Plugins/Developer/Concert/ConcertSync/ConcertSyncCore/Source/ConcertSyncCore`
- headers: 87; symbols: 1850
- symbol kinds: class=41, delegate=9, enum=48, enumerator=190, function=326, macro=23, member=437, namespace=154, prototype=420, struct=174, typedef=27, variable=1
- PrivateDependencyModuleNames: ConcertTransport, Json, SQLiteCore, TraceLog
- PublicDependencyModuleNames: Concert, Core, CoreUObject, Engine

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncCore/Source/ConcertSyncCore/Public/ConcertCloudFileSharingService.h` (Public)


#### class `FConcertCloudFileSharingService`  
`class FConcertCloudFileSharingService : public IConcertFileSharingService`  
_L14-62_
- inherits: `IConcertFileSharingService`
- desc: Share files using a path that is connected to a cloud based shared file service, e.g. a shared drive. It will work across all clients and server assuming that the drive is visible. Validation checks are run during session connection to establish that both the server and client can see the same system.
- L20 _public prototype_ `FConcertCloudFileSharingService(const FString& Role);` — Construct the cloud file sharing service.
- L23 _public prototype_ `virtual ~FConcertCloudFileSharingService();` — Destructor
- L26 _public prototype_ `virtual IConcertFileSharingService* Clone() const override;` — Make a clone of this sharing service to be used. Ownership is transferred to the caller. Callers can choose to wrap this into a unique or shared pointer.
- L29 _public prototype_ `virtual bool IsEnabled() const override;` — Is the file sharing service on / off.
- L32 _public prototype_ `virtual void SetEnabled(bool bInEnabled) override;` — Turn on/off the file sharing service.
- L35 _public prototype_ `virtual void SetPath(const FString& Path) override;` — Sets the desired path to use for the service.
- L38 _public prototype_ `virtual FString GetPath() const override;` — Get the assigned sharing path.
- L41 _public prototype_ `virtual void Delete(const FString& InFileId) override;` — Delete the given InFileId if it exists. Directories are supported and if a directory is supplied then DeleteDirectoryRecursively is called.
- L44 _public prototype_ `virtual bool Publish(const FString& Pathname, FString& OutFileId) override;` — Copies the specified file in the service storage and return a unique ID required to consume it back.
- L47 _public prototype_ `virtual bool Publish(FArchive& SrcAr, int64 Size, FString& OutFileId) override;` — Copies the content of the archive in the service storage and return a unique ID required to consume it back.
- L50 _public prototype_ `virtual TSharedPtr<FArchive> CreateReader(const FString& InFileId) override;` — Consumes a file corresponding to the unique file ID, if available.
- L53 _public prototype_ `virtual TSharedPtr<FArchive> CreateWriter(FString& OutFileId) override;` — Opens a file for writing. The file id is provided as a return argument.
- L57 _private prototype_ `bool PathIsValid() const;` — Checks to see if the desired sharing path is valid and writable.
- L59 _private member_ `bool bEnabled = false;`
- L61 _private member_ `FString SharedRootPathname;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API CONCERTSYNCCORE_API`

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncCore/Source/ConcertSyncCore/Public/ConcertDataStore.h` (Public)


#### class `FConcertDataStore`  
`class FConcertDataStore`  
_L50-136_
- desc: Maintains a type-safe key/value map where the values are USTRUCT() structs serialized into a FConcertDataStore_StoreValue. Each key/value pair has a version, starting at 1 which incremented every times the value change. @remarks The implementation is not thread safe. It is left to the user to synchronize access to the store. <b>How to set up a value in the store.</b> @code template<typename T> void MyClass::Store(const FName& Key, const T& Value) { // Wraps T into its corresponding USTRUCT() if this is not already a USTRUCT() const typename TConcertDataStoreType<T>::StructType& StructWrappedValue = TConcertDataStoreType<T>::AsStructType(Value); // Serialize the value. FConcertSessionSerializedPayload SerializedValue; SerializedValue.SetPayload(TConcertDataStoreType<T>::StructType::StaticStruct(), &StructWrappedValue); // Store the value at version 1. DataStore.Store(Key, TConcertDataStoreType::GetFName(), SerializedValue); } @endcode <b>How to read a value from the store.</b> @code template<typename T> TOptional<T> MyClass::Fetch(const FName& Key) { FConcertDataStoreResult Result = DataStore.Fetch(Key, TConcertDataStoreType<T>::GetFName()); if (Result.Code == EConcertDataStoreResultCode::Fetched) { return Result.Value->DeserializeUnchecked<T>(); } return TOptional<T>(); } @endcode
- L66 _public function_ `FConcertDataStore(EUpdatePolicy InUpdatePolicy = EUpdatePolicy::Replace) : UpdatePolicy(InUpdatePolicy)` — Construct the store. @param InUpdatePolicy The store update policy.
- L84 _public prototype_ `FConcertDataStoreResult FetchOrAdd(const FName& Key, const FName& TypeName, const FConcertSessionSerializedPayload& SerializedValue);` — Searches the store for the specified key, if not found, adds a new key/value pair, otherwise, if the stored value type matches the initial value type, fetches the stored value. The store always sets the value version to 1 when the value is added. @param Key The value name to fetch or add. @param TypeName The value type name as returned by TConcertDataStoreType::GetFName(). @param SerializedValue The value to store if the key doesn't already exist. @return The operation result. The possible result codes are: - EConcertDataStoreResultCode::Added if the key/value was added. The result holds a pointer on the newly added value. - EConcertDataStoreResultCode::Fetched if the key was already taken and type matched. The result holds a pointer on the fetched value. - EConcertDataStoreResultCode::TypeMismatch if the key was already taken but the types did not match. The result holds a null pointer.
- L100 _public prototype_ `FConcertDataStoreResult Store(const FName& Key, const FName& TypeName, const FConcertSessionSerializedPayload& SerializedValue, const TOptional<uint32>& Version = TOptional<uint32>());` — Looks up the specified key, if it doesn't exist yet, adds new key/value pair, else, if the stored value type matches the specified value type, updates the value. @param Key The value name to store. @param TypeName The value type name as returned by TConcertDataStoreType::GetFName(). @param SerializedValue The value to store. @param Version If set, store the value with the specified version, otherwise, the server will set the version to 1 if the value is inserted or increment it by one if updated. @return The operation result. The possible result codes are: - EConcertDataStoreResultCode::Added if the key/value was added. The result holds a pointer on the newly added value. - EConcertDataStoreResultCode::Exchanged if the existing key value was updated. The result holds a pointer on the latest stored value. - EConcertDataStoreResultCode::TypeMismatch if the key was already taken but the value types did not match. The result holds a null pointer. @see[The example in the class documentation.](@ref FConcertDataStore)
- L114 _public prototype_ `FConcertDataStoreResult Fetch(const FName& Key, const FName& TypeName) const;` — Looks up the specified key, if found and types match, fetches the corresponding value. If the key is not found or the requested type doesn't match the stored type, the operation fails. @param Key The value name to lookup. @param TypeName The value type name as returned by TConcertDataStoreType::GetFName(). @return The operation result. The possible result codes are: - EConcertDataStoreResultCode::Fetched if the key value was retrieved. The result holds a pointer on the fetched value. - EConcertDataStoreResultCode::NotFound if the key could not be found. The result holds a null pointer. - EConcertDataStoreResultCode::TypeMismatch if the key was found, but the requested type did not match the stored type. The result holds a null pointer. @see[The example in the class documentation.](@ref FConcertDataStore)
- L120 _public prototype_ `void Visit(const TFunctionRef<void(const FName&, const FConcertDataStore_StoreValue&)>& Visitor) const;` — Visits all the key/value currently stored. @param Visitor The function invoked for each key/value pair.
- L123 _public prototype_ `TOptional<uint32> GetVersion(const FName& Key) const;` — Returns the version of the specified key if found.
- L126 _public function_ `int32 GetSize() const` — Returns the number of key/value pairs currently stored.
- L129 _private prototype_ `FConcertDataStoreResult InternalAdd(const FName& Key, const FName& TypeName, const FConcertSessionSerializedPayload& Value, uint32 Version);`
- L132 _private member_ `EUpdatePolicy UpdatePolicy;` — Defines how the values are updated in the store.
- L135 _private member_ `TMap<FName, FConcertDataStoreValueRef> KeyValueMap;` — Maps keyName/keyValue.

#### enum `FConcertDataStore::EUpdatePolicy`  
`enum class EUpdatePolicy : int`  
_L54-60_
- desc: Defines how the store updates an existing value.
- L57 _public enumerator_ `Overwrite` — The existing value pointed by the shared pointer is overwritten, instantaneously updating all returned values still held by the client.
- L59 _public enumerator_ `Replace` — The existing shared pointer is replaced with a new shared pointer, leaving values returned to the client (shared pointers) unchanged.

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API CONCERTSYNCCORE_API`

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncCore/Source/ConcertSyncCore/Public/ConcertDataStoreMessages.h` (Public)


#### enum `EConcertDataStoreResultCode`  
`enum class EConcertDataStoreResultCode : uint8`  
_L11-25_
- reflection: `UENUM()`
- desc: Response codes for Concert data store operations.
- L14 _public enumerator_ `Added` — The key/value pair was added.
- L16 _public enumerator_ `Fetched` — The specified key value was fetched.
- L18 _public enumerator_ `Exchanged` — The specified key value was exchanged.
- L20 _public enumerator_ `NotFound` — Reading or writing a key value in the data store failed because the specified key could not be found.
- L22 _public enumerator_ `TypeMismatch` — Reading or writing a key value in the data store failed because the specified value type did not match the stored value type.
- L24 _public enumerator_ `UnexpectedError` — An unexpected error occurred.

#### struct `FConcertDataStore_Integer`  
`struct FConcertDataStore_Integer`  
_L32-66_
- reflection: `USTRUCT()`
- desc: A USTRUCT() wrapper struct, used by the implementation, to serialize/deserialize integers (of any type) or bool values passed to the Concert data store API.
- L38 _public member_ `uint64 Value = 0;` — `UPROPERTY(VisibleAnywhere, Category = "Concert Data Store Value")` — The stored value.
- L41 _public function_ `explicit operator uint8() const` — Converts the struct to a uint8. @see FConcertDataStore_StoreValue::DeserializeUnchecked<T>().
- L44 _public function_ `explicit operator int8() const` — Converts the struct to a int8. @see FConcertDataStore_StoreValue::DeserializeUnchecked<T>().
- L47 _public function_ `explicit operator uint16() const` — Converts the struct to a uint16. @see FConcertDataStore_StoreValue::DeserializeUnchecked<T>().
- L50 _public function_ `explicit operator int16() const` — Converts the struct to a int16. @see FConcertDataStore_StoreValue::DeserializeUnchecked<T>().
- L53 _public function_ `explicit operator uint32() const` — Converts the struct to a uint32. @see FConcertDataStore_StoreValue::DeserializeUnchecked<T>().
- L56 _public function_ `explicit operator int32() const` — Converts the struct to a int32. @see FConcertDataStore_StoreValue::DeserializeUnchecked<T>().
- L59 _public function_ `explicit operator uint64() const` — Converts the struct to a uint64. @see FConcertDataStore_StoreValue::DeserializeUnchecked<T>().
- L62 _public function_ `explicit operator int64() const` — Converts the struct to a int64. @see FConcertDataStore_StoreValue::DeserializeUnchecked<T>().
- L65 _public function_ `explicit operator bool() const` — Converts the struct to a boolean. @see FConcertDataStore_StoreValue::DeserializeUnchecked<T>().

#### struct `FConcertDataStore_Double`  
`struct FConcertDataStore_Double`  
_L73-85_
- reflection: `USTRUCT()`
- desc: A USTRUCT() wrapper struct, used by the implementation, to serialize/deserialize floating point values passed to the Concert data store API.
- L78 _public member_ `double Value = 0.0;` — `UPROPERTY(VisibleAnywhere, Category = "Concert Data Store Value")`
- L81 _public function_ `explicit operator double() const` — Converts the struct to a double. @see FConcertDataStore_StoreValue::DeserializeUnchecked<T>().
- L84 _public function_ `explicit operator float() const` — Converts the struct to a double. @see FConcertDataStore_StoreValue::DeserializeUnchecked<T>().

#### struct `FConcertDataStore_String`  
`struct FConcertDataStore_String`  
_L92-104_
- reflection: `USTRUCT()`
- desc: A USTRUCT() wrapper struct, used by the implementation, to serialize/deserialize FName and FString passed to the Concert data store API.
- L97 _public member_ `FString Value;` — `UPROPERTY(VisibleAnywhere, Category = "Concert Data Store Value")`
- L100 _public function_ `explicit operator FString() const` — Converts the struct to a FString. @see FConcertDataStore_StoreValue::DeserializeUnchecked<T>().
- L103 _public function_ `explicit operator FName() const` — Converts the struct to a FName. @see FConcertDataStore_StoreValue::DeserializeUnchecked<T>().

#### struct `FConcertDataStore_Text`  
`struct FConcertDataStore_Text`  
_L111-120_
- reflection: `USTRUCT()`
- desc: A USTRUCT() wrapper struct, used by the implementation, to serialize/deserialize FText passed to the Concert data store API.
- L116 _public member_ `FText Value;` — `UPROPERTY(VisibleAnywhere, Category = "Concert Data Store Value")`
- L119 _public function_ `explicit operator FText() const` — Converts the struct to a FText. @see FConcertDataStore_StoreValue::DeserializeUnchecked<T>().

#### struct `TConcertDataStoreType`  
`template<typename T> struct TConcertDataStoreType`  
_L129-139_
- desc: Maps a type to its corresponding USTRUCT() type. This enables deducing the USTRUCT() struct when calling the Concert data store API. The non-specialized version is expected to match all USTRUCT() structs "as-is" while the specialized versions are meant to map basic types such as int, bool or float to their corresponding USTRUCT() wrapper.
- L132 _public typedef_ `typedef T StructType;` — `USTRUCT()`
- L135 _public function_ `static const StructType& AsStructType(const StructType& Value)` — `USTRUCT()` — This is a 'pass through', no copy, no conversion.
- L138 _public function_ `static FName GetFName()` — Returns the data type name.
- L144 _public typedef_ `typedef FConcertDataStore_Integer StructType;`
- L145 _public function_ `static StructType AsStructType(uint8 Value)`
- L153 _public function_ `static StructType AsStructType(int8 Value)`
- L161 _public function_ `static StructType AsStructType(uint16 Value)`
- L169 _public function_ `static StructType AsStructType(int16 Value)`
- L177 _public function_ `static StructType AsStructType(uint32 Value)`
- L185 _public function_ `static StructType AsStructType(int32 Value)`
- L193 _public function_ `static StructType AsStructType(uint64 Value)`
- L201 _public function_ `static StructType AsStructType(int64 Value)`
- L208 _public typedef_ `typedef FConcertDataStore_Double StructType;`
- L209 _public function_ `static StructType AsStructType(float Value)`
- L217 _public function_ `static StructType AsStructType(double Value)`
- L225 _public function_ `static StructType AsStructType(bool Value)`
- L232 _public typedef_ `typedef FConcertDataStore_String StructType;`
- L233 _public function_ `static StructType AsStructType(const FName& Value)`
- L241 _public function_ `static StructType AsStructType(const FString& Value)`
- L248 _public typedef_ `typedef FConcertDataStore_Text StructType;`
- L249 _public function_ `static StructType AsStructType(const FText& Value)`

#### struct `TConcertDataStoreType`  
`template<> struct TConcertDataStoreType<uint8>`  
_L142-147_
- reflection: `USTRUCT()`
- L132 _public typedef_ `typedef T StructType;` — `USTRUCT()`
- L135 _public function_ `static const StructType& AsStructType(const StructType& Value)` — `USTRUCT()` — This is a 'pass through', no copy, no conversion.
- L138 _public function_ `static FName GetFName()` — Returns the data type name.
- L144 _public typedef_ `typedef FConcertDataStore_Integer StructType;`
- L145 _public function_ `static StructType AsStructType(uint8 Value)`
- L153 _public function_ `static StructType AsStructType(int8 Value)`
- L161 _public function_ `static StructType AsStructType(uint16 Value)`
- L169 _public function_ `static StructType AsStructType(int16 Value)`
- L177 _public function_ `static StructType AsStructType(uint32 Value)`
- L185 _public function_ `static StructType AsStructType(int32 Value)`
- L193 _public function_ `static StructType AsStructType(uint64 Value)`
- L201 _public function_ `static StructType AsStructType(int64 Value)`
- L208 _public typedef_ `typedef FConcertDataStore_Double StructType;`
- L209 _public function_ `static StructType AsStructType(float Value)`
- L217 _public function_ `static StructType AsStructType(double Value)`
- L225 _public function_ `static StructType AsStructType(bool Value)`
- L232 _public typedef_ `typedef FConcertDataStore_String StructType;`
- L233 _public function_ `static StructType AsStructType(const FName& Value)`
- L241 _public function_ `static StructType AsStructType(const FString& Value)`
- L248 _public typedef_ `typedef FConcertDataStore_Text StructType;`
- L249 _public function_ `static StructType AsStructType(const FText& Value)`

#### struct `TConcertDataStoreType`  
`template<> struct TConcertDataStoreType<int8>`  
_L150-155_
- reflection: `USTRUCT()`
- L132 _public typedef_ `typedef T StructType;` — `USTRUCT()`
- L135 _public function_ `static const StructType& AsStructType(const StructType& Value)` — `USTRUCT()` — This is a 'pass through', no copy, no conversion.
- L138 _public function_ `static FName GetFName()` — Returns the data type name.
- L144 _public typedef_ `typedef FConcertDataStore_Integer StructType;`
- L145 _public function_ `static StructType AsStructType(uint8 Value)`
- L153 _public function_ `static StructType AsStructType(int8 Value)`
- L161 _public function_ `static StructType AsStructType(uint16 Value)`
- L169 _public function_ `static StructType AsStructType(int16 Value)`
- L177 _public function_ `static StructType AsStructType(uint32 Value)`
- L185 _public function_ `static StructType AsStructType(int32 Value)`
- L193 _public function_ `static StructType AsStructType(uint64 Value)`
- L201 _public function_ `static StructType AsStructType(int64 Value)`
- L208 _public typedef_ `typedef FConcertDataStore_Double StructType;`
- L209 _public function_ `static StructType AsStructType(float Value)`
- L217 _public function_ `static StructType AsStructType(double Value)`
- L225 _public function_ `static StructType AsStructType(bool Value)`
- L232 _public typedef_ `typedef FConcertDataStore_String StructType;`
- L233 _public function_ `static StructType AsStructType(const FName& Value)`
- L241 _public function_ `static StructType AsStructType(const FString& Value)`
- L248 _public typedef_ `typedef FConcertDataStore_Text StructType;`
- L249 _public function_ `static StructType AsStructType(const FText& Value)`

#### struct `TConcertDataStoreType`  
`template<> struct TConcertDataStoreType<uint16>`  
_L158-163_
- reflection: `USTRUCT()`
- L132 _public typedef_ `typedef T StructType;` — `USTRUCT()`
- L135 _public function_ `static const StructType& AsStructType(const StructType& Value)` — `USTRUCT()` — This is a 'pass through', no copy, no conversion.
- L138 _public function_ `static FName GetFName()` — Returns the data type name.
- L144 _public typedef_ `typedef FConcertDataStore_Integer StructType;`
- L145 _public function_ `static StructType AsStructType(uint8 Value)`
- L153 _public function_ `static StructType AsStructType(int8 Value)`
- L161 _public function_ `static StructType AsStructType(uint16 Value)`
- L169 _public function_ `static StructType AsStructType(int16 Value)`
- L177 _public function_ `static StructType AsStructType(uint32 Value)`
- L185 _public function_ `static StructType AsStructType(int32 Value)`
- L193 _public function_ `static StructType AsStructType(uint64 Value)`
- L201 _public function_ `static StructType AsStructType(int64 Value)`
- L208 _public typedef_ `typedef FConcertDataStore_Double StructType;`
- L209 _public function_ `static StructType AsStructType(float Value)`
- L217 _public function_ `static StructType AsStructType(double Value)`
- L225 _public function_ `static StructType AsStructType(bool Value)`
- L232 _public typedef_ `typedef FConcertDataStore_String StructType;`
- L233 _public function_ `static StructType AsStructType(const FName& Value)`
- L241 _public function_ `static StructType AsStructType(const FString& Value)`
- L248 _public typedef_ `typedef FConcertDataStore_Text StructType;`
- L249 _public function_ `static StructType AsStructType(const FText& Value)`

#### struct `TConcertDataStoreType`  
`template<> struct TConcertDataStoreType<int16>`  
_L166-171_
- reflection: `USTRUCT()`
- L132 _public typedef_ `typedef T StructType;` — `USTRUCT()`
- L135 _public function_ `static const StructType& AsStructType(const StructType& Value)` — `USTRUCT()` — This is a 'pass through', no copy, no conversion.
- L138 _public function_ `static FName GetFName()` — Returns the data type name.
- L144 _public typedef_ `typedef FConcertDataStore_Integer StructType;`
- L145 _public function_ `static StructType AsStructType(uint8 Value)`
- L153 _public function_ `static StructType AsStructType(int8 Value)`
- L161 _public function_ `static StructType AsStructType(uint16 Value)`
- L169 _public function_ `static StructType AsStructType(int16 Value)`
- L177 _public function_ `static StructType AsStructType(uint32 Value)`
- L185 _public function_ `static StructType AsStructType(int32 Value)`
- L193 _public function_ `static StructType AsStructType(uint64 Value)`
- L201 _public function_ `static StructType AsStructType(int64 Value)`
- L208 _public typedef_ `typedef FConcertDataStore_Double StructType;`
- L209 _public function_ `static StructType AsStructType(float Value)`
- L217 _public function_ `static StructType AsStructType(double Value)`
- L225 _public function_ `static StructType AsStructType(bool Value)`
- L232 _public typedef_ `typedef FConcertDataStore_String StructType;`
- L233 _public function_ `static StructType AsStructType(const FName& Value)`
- L241 _public function_ `static StructType AsStructType(const FString& Value)`
- L248 _public typedef_ `typedef FConcertDataStore_Text StructType;`
- L249 _public function_ `static StructType AsStructType(const FText& Value)`

#### struct `TConcertDataStoreType`  
`template<> struct TConcertDataStoreType<uint32>`  
_L174-179_
- reflection: `USTRUCT()`
- L132 _public typedef_ `typedef T StructType;` — `USTRUCT()`
- L135 _public function_ `static const StructType& AsStructType(const StructType& Value)` — `USTRUCT()` — This is a 'pass through', no copy, no conversion.
- L138 _public function_ `static FName GetFName()` — Returns the data type name.
- L144 _public typedef_ `typedef FConcertDataStore_Integer StructType;`
- L145 _public function_ `static StructType AsStructType(uint8 Value)`
- L153 _public function_ `static StructType AsStructType(int8 Value)`
- L161 _public function_ `static StructType AsStructType(uint16 Value)`
- L169 _public function_ `static StructType AsStructType(int16 Value)`
- L177 _public function_ `static StructType AsStructType(uint32 Value)`
- L185 _public function_ `static StructType AsStructType(int32 Value)`
- L193 _public function_ `static StructType AsStructType(uint64 Value)`
- L201 _public function_ `static StructType AsStructType(int64 Value)`
- L208 _public typedef_ `typedef FConcertDataStore_Double StructType;`
- L209 _public function_ `static StructType AsStructType(float Value)`
- L217 _public function_ `static StructType AsStructType(double Value)`
- L225 _public function_ `static StructType AsStructType(bool Value)`
- L232 _public typedef_ `typedef FConcertDataStore_String StructType;`
- L233 _public function_ `static StructType AsStructType(const FName& Value)`
- L241 _public function_ `static StructType AsStructType(const FString& Value)`
- L248 _public typedef_ `typedef FConcertDataStore_Text StructType;`
- L249 _public function_ `static StructType AsStructType(const FText& Value)`

#### struct `TConcertDataStoreType`  
`template<> struct TConcertDataStoreType<int32>`  
_L182-187_
- reflection: `USTRUCT()`
- L132 _public typedef_ `typedef T StructType;` — `USTRUCT()`
- L135 _public function_ `static const StructType& AsStructType(const StructType& Value)` — `USTRUCT()` — This is a 'pass through', no copy, no conversion.
- L138 _public function_ `static FName GetFName()` — Returns the data type name.
- L144 _public typedef_ `typedef FConcertDataStore_Integer StructType;`
- L145 _public function_ `static StructType AsStructType(uint8 Value)`
- L153 _public function_ `static StructType AsStructType(int8 Value)`
- L161 _public function_ `static StructType AsStructType(uint16 Value)`
- L169 _public function_ `static StructType AsStructType(int16 Value)`
- L177 _public function_ `static StructType AsStructType(uint32 Value)`
- L185 _public function_ `static StructType AsStructType(int32 Value)`
- L193 _public function_ `static StructType AsStructType(uint64 Value)`
- L201 _public function_ `static StructType AsStructType(int64 Value)`
- L208 _public typedef_ `typedef FConcertDataStore_Double StructType;`
- L209 _public function_ `static StructType AsStructType(float Value)`
- L217 _public function_ `static StructType AsStructType(double Value)`
- L225 _public function_ `static StructType AsStructType(bool Value)`
- L232 _public typedef_ `typedef FConcertDataStore_String StructType;`
- L233 _public function_ `static StructType AsStructType(const FName& Value)`
- L241 _public function_ `static StructType AsStructType(const FString& Value)`
- L248 _public typedef_ `typedef FConcertDataStore_Text StructType;`
- L249 _public function_ `static StructType AsStructType(const FText& Value)`

#### struct `TConcertDataStoreType`  
`template<> struct TConcertDataStoreType<uint64>`  
_L190-195_
- reflection: `USTRUCT()`
- L132 _public typedef_ `typedef T StructType;` — `USTRUCT()`
- L135 _public function_ `static const StructType& AsStructType(const StructType& Value)` — `USTRUCT()` — This is a 'pass through', no copy, no conversion.
- L138 _public function_ `static FName GetFName()` — Returns the data type name.
- L144 _public typedef_ `typedef FConcertDataStore_Integer StructType;`
- L145 _public function_ `static StructType AsStructType(uint8 Value)`
- L153 _public function_ `static StructType AsStructType(int8 Value)`
- L161 _public function_ `static StructType AsStructType(uint16 Value)`
- L169 _public function_ `static StructType AsStructType(int16 Value)`
- L177 _public function_ `static StructType AsStructType(uint32 Value)`
- L185 _public function_ `static StructType AsStructType(int32 Value)`
- L193 _public function_ `static StructType AsStructType(uint64 Value)`
- L201 _public function_ `static StructType AsStructType(int64 Value)`
- L208 _public typedef_ `typedef FConcertDataStore_Double StructType;`
- L209 _public function_ `static StructType AsStructType(float Value)`
- L217 _public function_ `static StructType AsStructType(double Value)`
- L225 _public function_ `static StructType AsStructType(bool Value)`
- L232 _public typedef_ `typedef FConcertDataStore_String StructType;`
- L233 _public function_ `static StructType AsStructType(const FName& Value)`
- L241 _public function_ `static StructType AsStructType(const FString& Value)`
- L248 _public typedef_ `typedef FConcertDataStore_Text StructType;`
- L249 _public function_ `static StructType AsStructType(const FText& Value)`

#### struct `TConcertDataStoreType`  
`template<> struct TConcertDataStoreType<int64>`  
_L198-203_
- reflection: `USTRUCT()`
- L132 _public typedef_ `typedef T StructType;` — `USTRUCT()`
- L135 _public function_ `static const StructType& AsStructType(const StructType& Value)` — `USTRUCT()` — This is a 'pass through', no copy, no conversion.
- L138 _public function_ `static FName GetFName()` — Returns the data type name.
- L144 _public typedef_ `typedef FConcertDataStore_Integer StructType;`
- L145 _public function_ `static StructType AsStructType(uint8 Value)`
- L153 _public function_ `static StructType AsStructType(int8 Value)`
- L161 _public function_ `static StructType AsStructType(uint16 Value)`
- L169 _public function_ `static StructType AsStructType(int16 Value)`
- L177 _public function_ `static StructType AsStructType(uint32 Value)`
- L185 _public function_ `static StructType AsStructType(int32 Value)`
- L193 _public function_ `static StructType AsStructType(uint64 Value)`
- L201 _public function_ `static StructType AsStructType(int64 Value)`
- L208 _public typedef_ `typedef FConcertDataStore_Double StructType;`
- L209 _public function_ `static StructType AsStructType(float Value)`
- L217 _public function_ `static StructType AsStructType(double Value)`
- L225 _public function_ `static StructType AsStructType(bool Value)`
- L232 _public typedef_ `typedef FConcertDataStore_String StructType;`
- L233 _public function_ `static StructType AsStructType(const FName& Value)`
- L241 _public function_ `static StructType AsStructType(const FString& Value)`
- L248 _public typedef_ `typedef FConcertDataStore_Text StructType;`
- L249 _public function_ `static StructType AsStructType(const FText& Value)`

#### struct `TConcertDataStoreType`  
`template<> struct TConcertDataStoreType<float>`  
_L206-211_
- reflection: `USTRUCT()`
- L132 _public typedef_ `typedef T StructType;` — `USTRUCT()`
- L135 _public function_ `static const StructType& AsStructType(const StructType& Value)` — `USTRUCT()` — This is a 'pass through', no copy, no conversion.
- L138 _public function_ `static FName GetFName()` — Returns the data type name.
- L144 _public typedef_ `typedef FConcertDataStore_Integer StructType;`
- L145 _public function_ `static StructType AsStructType(uint8 Value)`
- L153 _public function_ `static StructType AsStructType(int8 Value)`
- L161 _public function_ `static StructType AsStructType(uint16 Value)`
- L169 _public function_ `static StructType AsStructType(int16 Value)`
- L177 _public function_ `static StructType AsStructType(uint32 Value)`
- L185 _public function_ `static StructType AsStructType(int32 Value)`
- L193 _public function_ `static StructType AsStructType(uint64 Value)`
- L201 _public function_ `static StructType AsStructType(int64 Value)`
- L208 _public typedef_ `typedef FConcertDataStore_Double StructType;`
- L209 _public function_ `static StructType AsStructType(float Value)`
- L217 _public function_ `static StructType AsStructType(double Value)`
- L225 _public function_ `static StructType AsStructType(bool Value)`
- L232 _public typedef_ `typedef FConcertDataStore_String StructType;`
- L233 _public function_ `static StructType AsStructType(const FName& Value)`
- L241 _public function_ `static StructType AsStructType(const FString& Value)`
- L248 _public typedef_ `typedef FConcertDataStore_Text StructType;`
- L249 _public function_ `static StructType AsStructType(const FText& Value)`

#### struct `TConcertDataStoreType`  
`template<> struct TConcertDataStoreType<double>`  
_L214-219_
- reflection: `USTRUCT()`
- L132 _public typedef_ `typedef T StructType;` — `USTRUCT()`
- L135 _public function_ `static const StructType& AsStructType(const StructType& Value)` — `USTRUCT()` — This is a 'pass through', no copy, no conversion.
- L138 _public function_ `static FName GetFName()` — Returns the data type name.
- L144 _public typedef_ `typedef FConcertDataStore_Integer StructType;`
- L145 _public function_ `static StructType AsStructType(uint8 Value)`
- L153 _public function_ `static StructType AsStructType(int8 Value)`
- L161 _public function_ `static StructType AsStructType(uint16 Value)`
- L169 _public function_ `static StructType AsStructType(int16 Value)`
- L177 _public function_ `static StructType AsStructType(uint32 Value)`
- L185 _public function_ `static StructType AsStructType(int32 Value)`
- L193 _public function_ `static StructType AsStructType(uint64 Value)`
- L201 _public function_ `static StructType AsStructType(int64 Value)`
- L208 _public typedef_ `typedef FConcertDataStore_Double StructType;`
- L209 _public function_ `static StructType AsStructType(float Value)`
- L217 _public function_ `static StructType AsStructType(double Value)`
- L225 _public function_ `static StructType AsStructType(bool Value)`
- L232 _public typedef_ `typedef FConcertDataStore_String StructType;`
- L233 _public function_ `static StructType AsStructType(const FName& Value)`
- L241 _public function_ `static StructType AsStructType(const FString& Value)`
- L248 _public typedef_ `typedef FConcertDataStore_Text StructType;`
- L249 _public function_ `static StructType AsStructType(const FText& Value)`

#### struct `TConcertDataStoreType`  
`template<> struct TConcertDataStoreType<bool>`  
_L222-227_
- reflection: `USTRUCT()`
- L132 _public typedef_ `typedef T StructType;` — `USTRUCT()`
- L135 _public function_ `static const StructType& AsStructType(const StructType& Value)` — `USTRUCT()` — This is a 'pass through', no copy, no conversion.
- L138 _public function_ `static FName GetFName()` — Returns the data type name.
- L144 _public typedef_ `typedef FConcertDataStore_Integer StructType;`
- L145 _public function_ `static StructType AsStructType(uint8 Value)`
- L153 _public function_ `static StructType AsStructType(int8 Value)`
- L161 _public function_ `static StructType AsStructType(uint16 Value)`
- L169 _public function_ `static StructType AsStructType(int16 Value)`
- L177 _public function_ `static StructType AsStructType(uint32 Value)`
- L185 _public function_ `static StructType AsStructType(int32 Value)`
- L193 _public function_ `static StructType AsStructType(uint64 Value)`
- L201 _public function_ `static StructType AsStructType(int64 Value)`
- L208 _public typedef_ `typedef FConcertDataStore_Double StructType;`
- L209 _public function_ `static StructType AsStructType(float Value)`
- L217 _public function_ `static StructType AsStructType(double Value)`
- L225 _public function_ `static StructType AsStructType(bool Value)`
- L232 _public typedef_ `typedef FConcertDataStore_String StructType;`
- L233 _public function_ `static StructType AsStructType(const FName& Value)`
- L241 _public function_ `static StructType AsStructType(const FString& Value)`
- L248 _public typedef_ `typedef FConcertDataStore_Text StructType;`
- L249 _public function_ `static StructType AsStructType(const FText& Value)`

#### struct `TConcertDataStoreType`  
`template<> struct TConcertDataStoreType<FName>`  
_L230-235_
- reflection: `USTRUCT()`
- L132 _public typedef_ `typedef T StructType;` — `USTRUCT()`
- L135 _public function_ `static const StructType& AsStructType(const StructType& Value)` — `USTRUCT()` — This is a 'pass through', no copy, no conversion.
- L138 _public function_ `static FName GetFName()` — Returns the data type name.
- L144 _public typedef_ `typedef FConcertDataStore_Integer StructType;`
- L145 _public function_ `static StructType AsStructType(uint8 Value)`
- L153 _public function_ `static StructType AsStructType(int8 Value)`
- L161 _public function_ `static StructType AsStructType(uint16 Value)`
- L169 _public function_ `static StructType AsStructType(int16 Value)`
- L177 _public function_ `static StructType AsStructType(uint32 Value)`
- L185 _public function_ `static StructType AsStructType(int32 Value)`
- L193 _public function_ `static StructType AsStructType(uint64 Value)`
- L201 _public function_ `static StructType AsStructType(int64 Value)`
- L208 _public typedef_ `typedef FConcertDataStore_Double StructType;`
- L209 _public function_ `static StructType AsStructType(float Value)`
- L217 _public function_ `static StructType AsStructType(double Value)`
- L225 _public function_ `static StructType AsStructType(bool Value)`
- L232 _public typedef_ `typedef FConcertDataStore_String StructType;`
- L233 _public function_ `static StructType AsStructType(const FName& Value)`
- L241 _public function_ `static StructType AsStructType(const FString& Value)`
- L248 _public typedef_ `typedef FConcertDataStore_Text StructType;`
- L249 _public function_ `static StructType AsStructType(const FText& Value)`

#### struct `TConcertDataStoreType`  
`template<> struct TConcertDataStoreType<FString>`  
_L238-243_
- reflection: `USTRUCT()`
- L132 _public typedef_ `typedef T StructType;` — `USTRUCT()`
- L135 _public function_ `static const StructType& AsStructType(const StructType& Value)` — `USTRUCT()` — This is a 'pass through', no copy, no conversion.
- L138 _public function_ `static FName GetFName()` — Returns the data type name.
- L144 _public typedef_ `typedef FConcertDataStore_Integer StructType;`
- L145 _public function_ `static StructType AsStructType(uint8 Value)`
- L153 _public function_ `static StructType AsStructType(int8 Value)`
- L161 _public function_ `static StructType AsStructType(uint16 Value)`
- L169 _public function_ `static StructType AsStructType(int16 Value)`
- L177 _public function_ `static StructType AsStructType(uint32 Value)`
- L185 _public function_ `static StructType AsStructType(int32 Value)`
- L193 _public function_ `static StructType AsStructType(uint64 Value)`
- L201 _public function_ `static StructType AsStructType(int64 Value)`
- L208 _public typedef_ `typedef FConcertDataStore_Double StructType;`
- L209 _public function_ `static StructType AsStructType(float Value)`
- L217 _public function_ `static StructType AsStructType(double Value)`
- L225 _public function_ `static StructType AsStructType(bool Value)`
- L232 _public typedef_ `typedef FConcertDataStore_String StructType;`
- L233 _public function_ `static StructType AsStructType(const FName& Value)`
- L241 _public function_ `static StructType AsStructType(const FString& Value)`
- L248 _public typedef_ `typedef FConcertDataStore_Text StructType;`
- L249 _public function_ `static StructType AsStructType(const FText& Value)`

#### struct `TConcertDataStoreType`  
`template<> struct TConcertDataStoreType<FText>`  
_L246-251_
- reflection: `USTRUCT()`
- L132 _public typedef_ `typedef T StructType;` — `USTRUCT()`
- L135 _public function_ `static const StructType& AsStructType(const StructType& Value)` — `USTRUCT()` — This is a 'pass through', no copy, no conversion.
- L138 _public function_ `static FName GetFName()` — Returns the data type name.
- L144 _public typedef_ `typedef FConcertDataStore_Integer StructType;`
- L145 _public function_ `static StructType AsStructType(uint8 Value)`
- L153 _public function_ `static StructType AsStructType(int8 Value)`
- L161 _public function_ `static StructType AsStructType(uint16 Value)`
- L169 _public function_ `static StructType AsStructType(int16 Value)`
- L177 _public function_ `static StructType AsStructType(uint32 Value)`
- L185 _public function_ `static StructType AsStructType(int32 Value)`
- L193 _public function_ `static StructType AsStructType(uint64 Value)`
- L201 _public function_ `static StructType AsStructType(int64 Value)`
- L208 _public typedef_ `typedef FConcertDataStore_Double StructType;`
- L209 _public function_ `static StructType AsStructType(float Value)`
- L217 _public function_ `static StructType AsStructType(double Value)`
- L225 _public function_ `static StructType AsStructType(bool Value)`
- L232 _public typedef_ `typedef FConcertDataStore_String StructType;`
- L233 _public function_ `static StructType AsStructType(const FName& Value)`
- L241 _public function_ `static StructType AsStructType(const FString& Value)`
- L248 _public typedef_ `typedef FConcertDataStore_Text StructType;`
- L249 _public function_ `static StructType AsStructType(const FText& Value)`

#### struct `FConcertDataStore_StoreValue`  
`struct FConcertDataStore_StoreValue`  
_L256-292_
- reflection: `USTRUCT()`
- desc: A value and its meta-data as stored by a Concert data store and transported between a client and a server.
- L264 _public member_ `FName TypeName;` — `UPROPERTY(VisibleAnywhere, Category = "Concert Data Store Value")` — The data type name as returned by TConcertDataStoreType::GetFName().
- L274 _public member_ `uint32 Version = 0;` — `UPROPERTY(VisibleAnywhere, Category = "Concert Data Store Value")` — The value version number set by the server. Starting at 1 when a key/value pair is inserted, incremented by one every time it is exchanged. As an optimization in the implementation, the client may substitute, when possible, the expected value by its expected version during a CompareExchange operation if the value is large.
- L278 _public member_ `FConcertSessionSerializedPayload SerializedValue;` — `UPROPERTY(VisibleAnywhere, Category = "Concert Data Store Value")` — Contains the value in its serialized and compact form. @see DeserializeUnchecked().
- L282 _public function_ `template<typename T> T DeserializeUnchecked() const` — Deserialize @ref FConcertDataStore_StoreValue.SerializedValue field into type T, without type checking.

#### struct `FConcertDataStore_KeyValuePair`  
`struct FConcertDataStore_KeyValuePair`  
_L308-319_
- reflection: `USTRUCT()`
- desc: Contains a key and its value, used by the client/server cache replication mechanism. @see FConcertDataStore_ReplicateEvent
- L314 _public member_ `FName Key;` — `UPROPERTY(VisibleAnywhere, Category = "Concert Data Store Message")` — The property name.
- L318 _public member_ `FConcertDataStore_StoreValue Value;` — `UPROPERTY(VisibleAnywhere, Category = "Concert Data Store Message")` — The property value.

#### struct `FConcertDataStore_ReplicateEvent`  
`struct FConcertDataStore_ReplicateEvent`  
_L327-334_
- reflection: `USTRUCT()`
- desc: The event message sent by the server to the client to perform the initial replication, sending all currently stored key/value pairs to a new session client(s) or to notify any further changes, pushing an updated key/value pair to all clients except the one who performed the change.
- L333 _public member_ `TArray<FConcertDataStore_KeyValuePair> Values;` — `UPROPERTY(VisibleAnywhere, Category = "Concert Data Store Message")` — The initial values or the values that recently changed.

#### struct `FConcertDataStore_Request`  
`struct FConcertDataStore_Request`  
_L345-356_
- reflection: `USTRUCT()`
- desc: The request used as the base class for fetch or add and compare exchange requests. The end user should not use this structure directly, but use the FetchOrAdd() or CompareExchange() API instead. @see IConcertClientDataStore::FetchAs() methods. @see IConcertClientDataStore::FetchOrAdd() methods. @see IConcertClientDataStore::CompareExchange() methods.
- L351 _public member_ `FName Key;` — `UPROPERTY(VisibleAnywhere, Category = "Concert Data Store Message")` — The name of the value to add/fetch/compare exchange.
- L355 _public member_ `FName TypeName;` — `UPROPERTY(VisibleAnywhere, Category = "Concert Data Store Message")` — The type name of the value USTRUCT to compare and exchange as returned by TConcertDataStoreType::GetFName().

#### struct `FConcertDataStore_FetchOrAddRequest`  
`struct FConcertDataStore_FetchOrAddRequest : public FConcertDataStore_Request`  
_L366-379_
- reflection: `USTRUCT()`
- inherits: `FConcertDataStore_Request`
- desc: The request passed from the client to the server to fetch or add a key/value pair from/in the data store. The end user should not use this structure directly, but use the IConcertClientDataStore::FetchOrAdd() API instead. The response type for this request is FConcertDataStore_Response. @see IConcertClientDataStore::FetchOrAdd() methods.
- L378 _public member_ `FConcertSessionSerializedPayload SerializedValue;` — `UPROPERTY(VisibleAnywhere, Category = "Concert Data Store Message")` — The property value to add if it doesn't already exist, in its serialized form. This implies the serialization is consistent across platforms and that no padding is serialized. When this is true, the serialized data is compact, binary comparable and the data store backend doesn't need to know the content format, it can only map a name and a blob and use memcmp() to compare and exchange a value.

#### struct `FConcertDataStore_CompareExchangeRequest`  
`struct FConcertDataStore_CompareExchangeRequest : public FConcertDataStore_Request`  
_L388-415_
- reflection: `USTRUCT()`
- inherits: `FConcertDataStore_Request`
- desc: The request passed from the client to the server to compare and exchange a stored value. The end user should not use this structure directly, but use the IConcertClientDataStore::CompareExchange() API instead. The response type for this request is a FConcertDataStore_Response. @see IConcertClientDataStore::CompareExchange() methods.
- L402 _public member_ `uint32 ExpectedVersion = 0;` — `UPROPERTY(VisibleAnywhere, Category = "Concert Data Store Message")` — The expected version of the value. If non-zero, the server uses this fields to identify the expected value and ignore the 'Expected' field. This is an optimization implemented in the client/server protocol. If the expected payload is large and correspond to the value currently cached in the client, the client will send the expected version rather than the expected value to save bandwidth. The server will compare version and if they match, will perform the exchange.
- L410 _public member_ `FConcertSessionSerializedPayload Expected;` — `UPROPERTY(VisibleAnywhere, Category = "Concert Data Store Message")` — The expected value if 'ExpectedVersion' is zero. The field is ignored if 'ExpectedVersion' is not zero and should be left empty. @see FConcertDataStore_FetchOrAddRequest for more explanation about the format.
- L414 _public member_ `FConcertSessionSerializedPayload Desired;` — `UPROPERTY(VisibleAnywhere, Category = "Concert Data Store Message")` — The desired value to store. @see FConcertDataStore_FetchOrAdd request for more explanation about the format.

#### struct `FConcertDataStore_Response`  
`struct FConcertDataStore_Response`  
_L419-440_
- reflection: `USTRUCT()`
- desc: The response to a FConcertDataStore_FetchOrAddRequest or FConcertDataStore_CompareExchangeRequest requests, sent from the server to the client.
- L430 _public member_ `EConcertDataStoreResultCode ResultCode = EConcertDataStoreResultCode::UnexpectedError;` — `UPROPERTY(VisibleAnywhere, Category = "Concert Data Store Message")` — The result code to the request. Possible values depends on the request. @see IConcertClientDataStore::FetchOrAdd() @see IConcertClientDataStore::FetchAs() @see IConcertClientDataStore::CompareExchange().
- L439 _public member_ `FConcertDataStore_StoreValue Value;` — `UPROPERTY(VisibleAnywhere, Category = "Concert Data Store Message")` — Contains the stored value if the ResponseCode == EConcertDataStoreResultCode::Fetched, otherwise, it is left empty. The server doesn't sent back the stored value when the client successfully stores it. The client is expected to keep the value it sent. @see TConcertDataStoreResult::GetValue() to deserialize the payload.

#### class `FConcertDataStoreResult`  
`class FConcertDataStoreResult`  
_L447-464_
- desc: Contains the result of a Concert data store operation. This class, as opposed to FConcertDataStore_Response, contains a shared pointer on the value to manage the lifetime of a value in the multi-versions client cache.
- L451 _public function_ `FConcertDataStoreResult() : Code(EConcertDataStoreResultCode::UnexpectedError)` — Constructs a result containing the EConcertDataStoreResultCode::UnexpectedError code and no value.
- L454 _public function_ `FConcertDataStoreResult(EConcertDataStoreResultCode InErrorCode) : Code(InErrorCode)` — Construct a result containing the specified error code and no value.
- L457 _public function_ `FConcertDataStoreResult(EConcertDataStoreResultCode InCode, FConcertDataStoreValueConstPtr InValue) : Code(InCode), Value(MoveTemp(InValue))` — Construct a result containing the specified code (added, fetched, exchanged) and its corresponding value.
- L460 _public member_ `EConcertDataStoreResultCode Code;` — The operation result code.
- L463 _public member_ `FConcertDataStoreValueConstPtr Value;` — The value returned to the caller unless an error occurred.

#### class `TConcertDataStoreResult`  
`template<typename T> class TConcertDataStoreResult`  
_L478-512_
- desc: Wraps the weakly typed result of a Concert data store operation into a strongly typed result. Type checking occurs during the transaction with the store and as long as the result is valid, the stored value can be read safely. @tparam T - Must be a USTRUCT() struct or one of the basic type from which a USTRUCT() struct can be deduced like int, float, bool, ... @see TConcertDataStoreType.
- L482 _public function_ `TConcertDataStoreResult()` — Constructs a result containing the EConcertDataStoreResultCode::UnexpectedError code and no value.
- L485 _public function_ `TConcertDataStoreResult(const FConcertDataStoreResult& InResult) : Result(InResult)` — Constructs a strongly typed result from a weakly typed one.
- L488 _public function_ `TConcertDataStoreResult(FConcertDataStoreResult&& InResult) : Result(Forward<FConcertDataStoreResult>(InResult))` — Constructs a strongly typed result from a weakly typed one.
- L491 _public function_ `operator bool() const` — Returns true if the result hold a value that the value can be read.
- L494 _public function_ `EConcertDataStoreResultCode GetCode() const` — Returns the data store result code for the operation.
- L501 _public function_ `bool IsValid() const` — Returns true if the underlying value is valid. The value is not valid if the result code is EConcertDataStoreResultCode::TypeMismatch or EConcertDataStoreResultCode::NotFound.
- L507 _public function_ `T GetValue() const` — Deserializes the stored value into type T. The data store performs type checking and the deserialization is type safe as long as IsValid() or operator bool() returns true.
- L511 _private member_ `FConcertDataStoreResult Result;` — The weakly-typed operation result.

#### Free symbols / members of external scopes

- L295 _typedef_ `typedef TSharedRef<FConcertDataStore_StoreValue, ESPMode::ThreadSafe> FConcertDataStoreValueRef;` — Thread safe shared reference to a FConcertDataStore_StoreValue.
- L297 _typedef_ `typedef TSharedPtr<FConcertDataStore_StoreValue, ESPMode::ThreadSafe> FConcertDataStoreValuePtr;` — Thread safe shared pointer to a FConcertDataStore_StoreValue.
- L299 _typedef_ `typedef TSharedRef<const FConcertDataStore_StoreValue, ESPMode::ThreadSafe> FConcertDataStoreValueConstRef;` — Thread safe shared reference to a const FConcertDataStore_StoreValue.
- L301 _typedef_ `typedef TSharedPtr<const FConcertDataStore_StoreValue, ESPMode::ThreadSafe> FConcertDataStoreValueConstPtr;` — Thread safe shared pointer to a const FConcertDataStore_StoreValue.

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncCore/Source/ConcertSyncCore/Public/ConcertFileCache.h` (Public)


#### class `FConcertFileCache`  
`class FConcertFileCache`  
_L15-120_
- desc: Maintains an in-memory cache of file data, attempting to keep the cache within the given upper memory threshold. @note Will automatically re-cache files if they are changed on disk (via a timestamp change), and un-cache files that are deleted from disk.
- L18 _public prototype_ `FConcertFileCache(const int32 InMinimumNumberOfFilesToCache, const uint64 InMaximumNumberOfBytesToCache);`
- L19 _public prototype_ `~FConcertFileCache();`
- L24 _public prototype_ `FConcertFileCache(const FConcertFileCache&) = delete;` — Non-copyable.
- L25 _public prototype_ `FConcertFileCache& operator=(const FConcertFileCache&) = delete;`
- L32 _public prototype_ `bool CacheFile(const FString& InFilename);` — Cache the given file (if valid). @note This function ignores the current cached file state, so will re-cache the file even if it has already been cached. @return True if the file was cached, false otherwise.
- L38 _public prototype_ `bool SaveAndCacheFile(const FString& InFilename, TArray<uint8>&& InFileData);` — Save the given file and add it to the cache. @return True if the file was cached, false otherwise.
- L43 _public prototype_ `void UncacheFile(const FString& InFilename);` — Uncache the given file.
- L49 _public prototype_ `bool FindOrCacheFile(const FString& InFilename, TArray<uint8>& OutFileData);` — Find or cache the given file, and get its data. @return True if the file was found or cached, false otherwise.
- L55 _public prototype_ `bool FindFile(const FString& InFilename, TArray<uint8>& OutFileData) const;` — Find the given file, and get its data. @return True if the file was found, false otherwise.
- L61 _public prototype_ `bool HasCachedFile(const FString& InFilename) const;` — Is the given file cached? @return True if the file is cached, false otherwise.
- L67 _private prototype_ `void TrimCache();` — Trim the cache to attempt to keep it within the requested upper memory threshold.
- L115 _private member_ `const int32 MinimumNumberOfFilesToCache;`
- L116 _private member_ `const uint64 MaximumNumberOfBytesToCache;`
- L118 _private member_ `uint64 TotalCachedFileDataBytes;`
- L119 _private member_ `TLruCache<FString, TSharedPtr<FInternalCacheEntry>> InternalCache;`

#### class `FConcertFileCache::FInternalCacheEntry`  
`class FInternalCacheEntry`  
_L70-113_
- desc: Internal cache entry that scopes counting the cached file size into the outer file-cache
- L73 _public function_ `FInternalCacheEntry(TArray<uint8>&& InFileData, const FDateTime& InFileTimestamp, uint64& InTotalCachedFileDataBytesRef) : FileData(MoveTemp(InFileData)) , FileTimestamp(InFileTimestamp) , TotalCachedFileDataBytesRef(InTotalCachedFileDataBytesRef)`
- L81 _public function_ `~FInternalCacheEntry()`
- L86 _public prototype_ `FInternalCacheEntry(const FInternalCacheEntry&) = delete;`
- L87 _public prototype_ `FInternalCacheEntry& operator=(const FInternalCacheEntry&) = delete;`
- L89 _public function_ `const TArray<uint8>& GetFileData() const`
- L94 _public function_ `const FDateTime& GetFileTimestamp() const`
- L99 _public function_ `void SetFile(TArray<uint8>&& InFileData, const FDateTime& InFileTimestamp)`
- L110 _private member_ `TArray<uint8> FileData;`
- L111 _private member_ `FDateTime FileTimestamp;`
- L112 _private member_ `uint64& TotalCachedFileDataBytesRef;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API CONCERTSYNCCORE_API`

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncCore/Source/ConcertSyncCore/Public/ConcertLocalFileSharingService.h` (Public)


#### class `FConcertLocalFileSharingService`  
`class FConcertLocalFileSharingService : public IConcertFileSharingService`  
_L17-72_
- inherits: `IConcertFileSharingService`
- desc: Share files using a local directory. It works only for one client and one server running on the same machine. The publisher of a file stores a file for sharing and gets a unique ID to consume the file back. It is the publisher responsibility to share the ID with the consumer (i.e. through a concert msg). The shared files are automatically deleted once consumed or when the file expires. @note This is mainly designed for the recovery system.
- L26 _public prototype_ `FConcertLocalFileSharingService(const FString& Role);` — Construct the local file sharing service. @param Role Appended to the shared directory (like DisasterRecovery) as a hint for the temp folder purpose. Client and server must use the same value. @note The service uses the Engine intermediate directory to share the files. The files are automatically deleted after consumption. In case of crash the temporary shared files are deleted on next reboot if no other client/server on the machine are not running.
- L27 _public prototype_ `virtual ~FConcertLocalFileSharingService();`
- L30 _public prototype_ `virtual IConcertFileSharingService* Clone() const override;` — Make a clone of this sharing service to be used. Ownership is transferred to the caller. Callers can choose to wrap this into a unique or shared pointer.
- L33 _public prototype_ `virtual bool IsEnabled() const override;` — Indicates if this file sharing service is enabled. Local file sharing is always enabled and it is not possible to disable at runtime.
- L36 _public prototype_ `virtual void SetEnabled(bool bInEnabled) override;` — This is a no-op and disabling the local file sharing service is not supported.
- L39 _public prototype_ `virtual void SetPath(const FString& Path) override;` — Sets the desired path to use for the service.  Implementors have the right to ignore the path specified.  This class does.
- L42 _public prototype_ `virtual FString GetPath() const override;` — Get the assigned sharing path.
- L45 _public prototype_ `virtual void Delete(const FString& InFileId) override;` — Delete is not supported for local file sharing and only provided to satisfy interfac requirement.
- L48 _public prototype_ `virtual bool Publish(const FString& Pathname, FString& OutFileId) override;` — Copies the specified file in the service storage and return a unique ID required to consume it back. The stored file expires in 1 hour.
- L51 _public prototype_ `virtual bool Publish(FArchive& SrcAr, int64 Size, FString& OutFileId) override;` — Copies the content of the archive in the service storage and return a unique ID required to consume it back. The stored file expires in 1 hour.
- L54 _public prototype_ `virtual TSharedPtr<FArchive> CreateReader(const FString& InFileId) override;` — Consumes a file corresponding to the unique file ID, if available. The file is deleted from the service storage when the shared pointer goes out of scope.
- L57 _public prototype_ `virtual TSharedPtr<FArchive> CreateWriter(FString& OutFileId) override;` — Opens a file for writing. The file id is provided as a return argument.
- L60 _private prototype_ `void LoadActiveServices(TArray<uint32>& OutPids);` — Load the list of concurrent file sharing service running across all processes.
- L63 _private prototype_ `void SaveActiveServices(const TArray<uint32>& InPids);` — Saved the list of concurrent file sharing service running across all processes.
- L66 _private prototype_ `void RemoveDeadProcessesAndFiles(TArray<uint32>& InOutPids);` — Track active services instances across all processes and clean up any left over files that expired if no services are running anymore.
- L69 _private member_ `FString SharedRootPathname;`
- L70 _private member_ `FString SystemMutexName;`
- L71 _private member_ `FString ActiveServicesRepositoryPathname;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API CONCERTSYNCCORE_API`

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncCore/Source/ConcertSyncCore/Public/ConcertPackageEvents.h` (Public)


#### struct `UE::ConcertSyncCore::ConcertPackageEvents::FConcertBaseSendPackageParams`  
`struct FConcertBaseSendPackageParams`  
_L12-28_
- L15 _public member_ `FGuid TransmissionId;` — Identifies begin and finish send events so you can map them to each other.
- L18 _public member_ `const FConcertPackageInfo& PackageInfo;` — General information about the package
- L27 _public member_ `FGuid RemoteEndpointId;` — The remote endpoint that is interacting with this package. If we're the server, then there are 2 options: 1. This is a client that's sending us data 2. This is a client that we're sending the data to

#### struct `UE::ConcertSyncCore::ConcertPackageEvents::FConcertBeginSendPackageParams`  
`struct FConcertBeginSendPackageParams : FConcertBaseSendPackageParams`  
_L30-34_
- inherits: `FConcertBaseSendPackageParams`
- L33 _public member_ `uint64 PackageNumBytes;` — The size of the package data to be received

#### struct `UE::ConcertSyncCore::ConcertPackageEvents::FConcertFinishSendPackageParams`  
`struct FConcertFinishSendPackageParams : FConcertBaseSendPackageParams`  
_L36-45_
- inherits: `FConcertBaseSendPackageParams`
- L44 _public member_ `FGuid MessageId;` — The ID of the message that causes the package to be acknowledged. In the case of sending to a client, it is the acknowledgement message. In the case of receiving from client, it is the message transmitting the sync activity.

#### struct `UE::ConcertSyncCore::ConcertPackageEvents::FConcertRejectSendPackageParams`  
`struct FConcertRejectSendPackageParams : FConcertFinishSendPackageParams`  
_L47-48_
- inherits: `FConcertFinishSendPackageParams`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace ConcertSyncCore` (scope `UE`)
- L10 _namespace_ `namespace ConcertPackageEvents` (scope `UE::ConcertSyncCore`)
- L50 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FConcertBeginSendPackageDelegate, const FConcertBeginSendPackageParams&);`
- L50 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FConcertBeginSendPackageDelegate, const FConcertBeginSendPackageParams&);` (scope `UE::ConcertSyncCore::ConcertPackageEvents`)
- L51 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FConcertFinishSendPackageDelegate, const FConcertFinishSendPackageParams&);`
- L51 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FConcertFinishSendPackageDelegate, const FConcertFinishSendPackageParams&);` (scope `UE::ConcertSyncCore::ConcertPackageEvents`)
- L52 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FConcertRejectSendPackageDelegate, const FConcertRejectSendPackageParams&);`
- L52 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FConcertRejectSendPackageDelegate, const FConcertRejectSendPackageParams&);` (scope `UE::ConcertSyncCore::ConcertPackageEvents`)
- L58 _prototype_ `FConcertBeginSendPackageDelegate& OnLocalBeginSendPackage();` (scope `UE::ConcertSyncCore::ConcertPackageEvents`) — Called when we begin sending a package to a remote endpoint. RemoteEndpointId is to be interpreted as the receiver.
- L60 _prototype_ `FConcertFinishSendPackageDelegate& OnLocalFinishSendPackage();` (scope `UE::ConcertSyncCore::ConcertPackageEvents`) — Called when we finish sending a package to a remote endpoint. They've sent us an ACK. RemoteEndpointId is to be interpreted as the receiver.
- L63 _prototype_ `FConcertBeginSendPackageDelegate& OnRemoteBeginSendPackage();` (scope `UE::ConcertSyncCore::ConcertPackageEvents`) — Called when we begin receiving a package from a remote endpoint. They've let us know in advance via an event. RemoteEndpointId is to be interpreted as the sender.
- L65 _prototype_ `FConcertFinishSendPackageDelegate& OnRemoteFinishSendPackage();` (scope `UE::ConcertSyncCore::ConcertPackageEvents`) — Called when we finished receiving a package from a remote endpoint. We've processed the data locally. RemoteEndpointId is to be interpreted as the sender.
- L67 _prototype_ `FConcertRejectSendPackageDelegate& OnRejectRemoteSendPackage();` (scope `UE::ConcertSyncCore::ConcertPackageEvents`) — Called when we finished receiving a package from a remote endpoint but decided to reject the data. Called only on the server. RemoteEndpointId is to be interpreted as the sender.

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncCore/Source/ConcertSyncCore/Public/ConcertPresenceEvents.h` (Public)


#### struct `FConcertClientPresenceEventBase`  
`struct FConcertClientPresenceEventBase`  
_L8-14_
- reflection: `USTRUCT()`
- L13 _public member_ `uint32 TransactionUpdateIndex = 0;` — `UPROPERTY()`

#### struct `FConcertClientPresenceVisibilityUpdateEvent`  
`struct FConcertClientPresenceVisibilityUpdateEvent`  
_L17-26_
- reflection: `USTRUCT()`
- L22 _public member_ `FGuid ModifiedEndpointId;` — `UPROPERTY()`
- L25 _public member_ `bool bVisibility = true;` — `UPROPERTY()`

#### struct `FConcertClientPresenceInVREvent`  
`struct FConcertClientPresenceInVREvent`  
_L29-35_
- reflection: `USTRUCT()`
- L34 _public member_ `FName VRDevice;` — `UPROPERTY()`

#### enum `EPresenceModeType`  
`enum class EPresenceModeType`  
_L38-42_
- reflection: `UENUM()`
- L40 _public enumerator_ `Desktop`
- L41 _public enumerator_ `VRMode`

#### struct `FConcertClientPresenceDataUpdateEvent`  
`struct FConcertClientPresenceDataUpdateEvent : public FConcertClientPresenceEventBase`  
_L45-70_
- reflection: `USTRUCT()`
- inherits: `FConcertClientPresenceEventBase`
- L49 _public function_ `FConcertClientPresenceDataUpdateEvent() : WorldPath() , Position(FVector::ZeroVector) , Orientation(FQuat::Identity) , PresenceType(EPresenceModeType::Desktop)`
- L60 _public member_ `FName WorldPath;` — `UPROPERTY()` — The non-PIE/SIE world path. In PIE/SIE, the world context and its path is different than the non-PIE/SIE context. For presence management, we are interested in the Non-PIE/SIE world path and this is what is emitted even if the user is in PIE/SIE.
- L63 _public member_ `FVector Position;` — `UPROPERTY()`
- L66 _public member_ `FQuat Orientation;` — `UPROPERTY()`
- L69 _public member_ `EPresenceModeType PresenceType;` — `UPROPERTY()`

#### struct `FConcertClientDesktopPresenceUpdateEvent`  
`struct FConcertClientDesktopPresenceUpdateEvent : public FConcertClientPresenceEventBase`  
_L73-92_
- reflection: `USTRUCT()`
- inherits: `FConcertClientPresenceEventBase`
- L77 _public function_ `FConcertClientDesktopPresenceUpdateEvent() : TraceStart(FVector::ZeroVector) , TraceEnd(FVector::ZeroVector) , bMovingCamera(false)`
- L85 _public member_ `FVector TraceStart;` — `UPROPERTY()`
- L88 _public member_ `FVector TraceEnd;` — `UPROPERTY()`
- L91 _public member_ `bool bMovingCamera;` — `UPROPERTY()`

#### struct `FConcertLaserData`  
`struct FConcertLaserData`  
_L95-119_
- reflection: `USTRUCT()`
- L99 _public function_ `FConcertLaserData() : LaserStart(FVector::ZeroVector) , LaserEnd(FVector::ZeroVector)`
- L104 _public function_ `FConcertLaserData(FVector Start, FVector End) : LaserStart(MoveTemp(Start)) , LaserEnd(MoveTemp(End))`
- L109 _public function_ `bool IsValid() const`
- L115 _public member_ `FVector LaserStart;` — `UPROPERTY()`
- L118 _public member_ `FVector LaserEnd;` — `UPROPERTY()`

#### struct `FConcertClientVRPresenceUpdateEvent`  
`struct FConcertClientVRPresenceUpdateEvent : public FConcertClientPresenceEventBase`  
_L122-147_
- reflection: `USTRUCT()`
- inherits: `FConcertClientPresenceEventBase`
- L126 _public function_ `FConcertClientVRPresenceUpdateEvent() : LeftMotionControllerPosition(FVector::ZeroVector) , LeftMotionControllerOrientation(FQuat::Identity) , RightMotionControllerPosition(FVector::ZeroVector) , RightMotionControllerOrientation(FQuat::Identity)`
- L134 _public member_ `FVector LeftMotionControllerPosition;` — `UPROPERTY()`
- L137 _public member_ `FQuat LeftMotionControllerOrientation;` — `UPROPERTY()`
- L140 _public member_ `FVector RightMotionControllerPosition;` — `UPROPERTY()`
- L143 _public member_ `FQuat RightMotionControllerOrientation;` — `UPROPERTY()`
- L146 _public member_ `FConcertLaserData Lasers[2];` — `UPROPERTY()`

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncCore/Source/ConcertSyncCore/Public/ConcertSequencerMessages.h` (Public)


#### enum `EConcertMovieScenePlayerStatus`  
`enum class EConcertMovieScenePlayerStatus : uint8`  
_L15-24_
- reflection: `UENUM()`
- desc: Enum for the current Sequencer player status, should match EMovieScenePlayerStatus::Type Defined here to not have a dependency on the MovieScene module.
- L17 _public enumerator_ `Stopped`
- L18 _public enumerator_ `Playing`
- L19 _public enumerator_ `Scrubbing`
- L20 _public enumerator_ `Jumping`
- L21 _public enumerator_ `Stepping`
- L22 _public enumerator_ `Paused`
- L23 _public enumerator_ `MAX`

#### struct `FConcertSequencerState`  
`struct FConcertSequencerState`  
_L27-66_
- reflection: `USTRUCT()`
- L33 _public member_ `FString SequenceObjectPath;` — `UPROPERTY()` — The full path name to the root sequence that is open on the sequencer
- L37 _public member_ `FQualifiedFrameTime Time;` — `UPROPERTY()` — The time that the sequence is at
- L41 _public member_ `EConcertMovieScenePlayerStatus PlayerStatus;` — `UPROPERTY()` — The current status of the sequencer player
- L44 _public member_ `FFrameNumberRange PlaybackRange;` — `UPROPERTY()`
- L48 _public member_ `float PlaybackSpeed;` — `UPROPERTY()` — The current playback speed
- L52 _public member_ `bool bLoopMode = false;` — `UPROPERTY()` — Indicate if we are currently looping
- L60 _public member_ `FConcertByteArray TakeData;` — `UPROPERTY()` — In the case that the SequenceObjectPath points to a take preset, we capture the preset data into a payload that can be applied to take that we are going to open. We store it in the state so that we can play it back when new users join.
- L62 _public function_ `FConcertSequencerState() : PlayerStatus(EConcertMovieScenePlayerStatus::Stopped) , PlaybackSpeed(1.0f)`

#### struct `FConcertSequencerOpenEvent`  
`struct FConcertSequencerOpenEvent`  
_L72-87_
- reflection: `USTRUCT()`
- desc: Event that signals a Sequencer just been opened.
- L78 _public member_ `FString SequenceObjectPath;` — `UPROPERTY()` — The full path name to the root sequence of the sequencer that just opened.
- L86 _public member_ `FConcertByteArray TakeData;` — `UPROPERTY()` — In the case that the SequenceObjectPath points to a take preset, we capture the preset data into a payload that can be applied to take that we are going to open. We store it in the state so that we can play it back when new users join.

#### struct `FConcertSequencerCloseEvent`  
`struct FConcertSequencerCloseEvent`  
_L93-106_
- reflection: `USTRUCT()`
- desc: Event that signals a Sequencer just been closed.
- L99 _public member_ `FString SequenceObjectPath;` — `UPROPERTY()` — The full path name to the root sequence of the sequencer that just closed.
- L102 _public member_ `bool bControllerClose = false;` — `UPROPERTY()`
- L105 _public member_ `int32 EditorsWithSequencerOpened = -1;` — `UPROPERTY()`

#### struct `FConcertSequencerStateEvent`  
`struct FConcertSequencerStateEvent`  
_L112-119_
- reflection: `USTRUCT()`
- desc: Event that signals a sequencer UI has changed the current state
- L118 _public member_ `FConcertSequencerState State;` — `UPROPERTY()` — The new state that the sequence is at

#### struct `FConcertSequencerStateSyncEvent`  
`struct FConcertSequencerStateSyncEvent`  
_L125-131_
- reflection: `USTRUCT()`
- desc: Event that represent the current open sequencer states to a newly connected client
- L130 _public member_ `TArray<FConcertSequencerState> SequencerStates;` — `UPROPERTY()`

#### struct `FConcertSequencerTimeAdjustmentEvent`  
`struct FConcertSequencerTimeAdjustmentEvent`  
_L138-147_
- reflection: `USTRUCT()`
- desc: An event that represents a time changes on the sequencer. This can happen via take recorder which will shift the active take _if_ Start At Timecode is enabled.
- L143 _public member_ `FFrameNumber PlaybackStartFrame;` — `UPROPERTY()`
- L146 _public member_ `FString SequenceObjectPath;` — `UPROPERTY()`

#### struct `FConcertSequencerPreloadRequest`  
`struct FConcertSequencerPreloadRequest`  
_L160-171_
- reflection: `USTRUCT()`
- desc: Event indicating one or more sequences have been added or removed from the set of sequences to keep preloaded for quick dynamic instantiation. Can be sent by clients as a request to add or remove their references. Can also be received from the server in response to changes to the active set, or as an initial snapshot of the complete set when joining a session.
- L166 _public member_ `TArray<FTopLevelAssetPath> SequenceObjectPaths;` — `UPROPERTY()` — The list of full paths to affected sequences.
- L170 _public member_ `bool bShouldBePreloaded = false;` — `UPROPERTY()` — True if being added to the preload set, false if being removed.

#### enum `EConcertSequencerPreloadStatus`  
`enum class EConcertSequencerPreloadStatus : uint8`  
_L174-179_
- reflection: `UENUM()`
- L176 _public enumerator_ `Pending`
- L177 _public enumerator_ `Succeeded`
- L178 _public enumerator_ `Failed`

#### struct `FConcertSequencerPreloadAssetStatusMap`  
`struct FConcertSequencerPreloadAssetStatusMap`  
_L186-192_
- reflection: `USTRUCT()`
- desc: Can be sent as an event by clients to indicate loading success/failure result of attempting to preload one or more sequence assets.
- L191 _public member_ `TMap<FTopLevelAssetPath, EConcertSequencerPreloadStatus> Sequences;` — `UPROPERTY()`

#### struct `FConcertSequencerPreloadClientStatusMap`  
`struct FConcertSequencerPreloadClientStatusMap`  
_L198-223_
- reflection: `USTRUCT()`
- desc: Sent as an event by server with preload status of one or more clients.
- L203 _public member_ `TMap<FGuid, FConcertSequencerPreloadAssetStatusMap> ClientEndpoints;` — `UPROPERTY()`
- L206 _public function_ `void UpdateFrom(const FGuid& Client, const FConcertSequencerPreloadAssetStatusMap& Updates)` — Merge (add or replace) statuses for a specified client into this object.
- L216 _public function_ `void Remove(const FTopLevelAssetPath& Sequence)` — Clear all clients' references to a specified asset.

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncCore/Source/ConcertSyncCore/Public/ConcertSyncArchives.h` (Public)


#### struct `ConcertSyncUtil::FResetValueOptions`  
`struct FResetValueOptions`  
_L28-65_
- L33 _public member_ `bool bIncludeEditorOnlyData = true;` — True if we should also reset editor-only properties.
- L39 _public member_ `bool bIsDuplicate = false;` — True when Object is considered a duplicate of Template (eg, two instances with the same archetype, where we want to make Object the same as Template). @note If true this sets PPF_Duplicate on the archive when copying data, and automatically skips CPF_DuplicateTransient properties.
- L45 _public member_ `bool bSaveGameOnly = false;` — True to only consider things marked CPF_SaveGame. @note If true this sets the ArIsSaveGame flag on the archive when copying the data.
- L51 _public member_ `TSet<FSoftObjectPath> ObjectsToSkip;` — Set of objects that should have their references skipped when resetting values. @note Objects skipped via this set are not passed to ShouldSkipObjectReference.
- L57 _public member_ `TFunction<bool(const FArchive& Ar, const FProperty* Property)> ShouldSkipProperty;` — Filter used to decide whether the given property should be skipped when resetting values. @note Properties skipped internally by the archive will not be passed to this function.
- L64 _public member_ `TFunction<bool(const FArchive& Ar, const FSoftObjectPath& OldValue, const FSoftObjectPath& NewValue)> ShouldSkipObjectReference;` — Filter used to decide whether the given property reference should be skipped when resetting values. @param OldValue The current object reference from Object. @param NewValue The proposed new object reference from Template.

#### class `FConcertSyncWorldRemapper`  
`class FConcertSyncWorldRemapper`  
_L73-96_
- desc: Util to handle remapping objects within the source world to be the equivalent objects in the destination world
- L76 _public prototype_ `FConcertSyncWorldRemapper() = default;`
- L78 _public function_ `FConcertSyncWorldRemapper(FString InSourceWorldPathName, FString InDestWorldPathName) : SourceWorldPathName(MoveTemp(InSourceWorldPathName)) , DestWorldPathName(MoveTemp(InDestWorldPathName))`
- L84 _public prototype_ `FString RemapObjectPathName(const FString& InObjectPathName) const;`
- L86 _public prototype_ `bool ObjectBelongsToWorld(const FString& InObjectPathName) const;`
- L88 _public prototype_ `bool HasMapping() const;`
- L90 _public member_ `FConcertSyncRemapObjectPath RemapDelegate;`
- L91 _public member_ `FConcertSyncObjectPathBelongsToWorld ObjectPathBelongsToWorldDelegate;`
- L94 _private member_ `FString SourceWorldPathName;`
- L95 _private member_ `FString DestWorldPathName;`

#### class `FConcertSyncObjectWriter`  
`class FConcertSyncObjectWriter : public FConcertIdentifierWriter`  
_L99-134_
- inherits: `FConcertIdentifierWriter`
- desc: Archive for writing objects in a way that they can be sent to another instance via Concert
- L103 _public prototype_ `FConcertSyncObjectWriter(FConcertLocalIdentifierTable* InLocalIdentifierTable, UObject* InObj, TArray<uint8>& OutBytes, const bool InIncludeEditorOnlyData, const bool InSkipAssets, const FConcertSyncRemapObjectPath& InRemapDelegate);`
- L104 _public prototype_ `FConcertSyncObjectWriter(FConcertLocalIdentifierTable* InLocalIdentifierTable, UObject* InObj, TArray<uint8>& OutBytes, const bool InIncludeEditorOnlyData, const bool InSkipAssets);`
- L106 _public prototype_ `void SerializeObject(const UObject* InObject, const TArray<const FProperty*>* InPropertiesToWrite = nullptr, bool bAllowOuters = false);`
- L107 _public prototype_ `void SerializeProperty(const FProperty* InProp, const UObject* InObject);`
- L112 _public prototype_ `virtual FArchive& operator<<(UObject*& Obj) override;`
- L113 _public prototype_ `virtual FArchive& operator<<(FLazyObjectPtr& LazyObjectPtr) override;`
- L114 _public prototype_ `virtual FArchive& operator<<(FObjectPtr& Obj) override;`
- L115 _public prototype_ `virtual FArchive& operator<<(FSoftObjectPtr& AssetPtr) override;`
- L116 _public prototype_ `virtual FArchive& operator<<(FSoftObjectPath& AssetPtr) override;`
- L117 _public prototype_ `virtual FArchive& operator<<(FWeakObjectPtr& Value) override;`
- L118 _public prototype_ `virtual FString GetArchiveName() const override;`
- L119 _public prototype_ `virtual bool ShouldSkipProperty(const FProperty* InProperty) const override;`
- L122 _public function_ `void SetSerializeNestedObjects(bool bInSerializeNestedObjects)`
- L127 _private typedef_ `typedef TFunction<bool(const FProperty*)> FShouldSkipPropertyFunc;`
- L128 _private member_ `bool bSkipAssets;`
- L129 _private member_ `bool bSerializeNestedObjects = false;`
- L130 _private member_ `FString PackageName;`
- L131 _private member_ `FShouldSkipPropertyFunc ShouldSkipPropertyFunc;`
- L132 _private member_ `FConcertSyncRemapObjectPath RemapObjectPathDelegate;`
- L133 _private member_ `TSet<FString> CollectedObjects;`

#### class `FConcertSyncObjectReader`  
`class FConcertSyncObjectReader : public FConcertIdentifierReader`  
_L137-170_
- inherits: `FConcertIdentifierReader`
- desc: Archive for reading objects that have been received from another instance via Concert
- L140 _public prototype_ `FConcertSyncObjectReader(const FConcertLocalIdentifierTable* InLocalIdentifierTable, FConcertSyncWorldRemapper InWorldRemapper, const FConcertSessionVersionInfo* InVersionInfo, UObject* InObj, const TArray<uint8>& InBytes, const FConcertSyncEncounteredMissingObject& InEncounteredMissingObjectDelegate);`
- L143 _public prototype_ `void SerializeObject(UObject* InObject);`
- L144 _public prototype_ `void SerializeProperty(const FProperty* InProp, UObject* InObject);`
- L149 _public prototype_ `virtual FArchive& operator<<(UObject*& Obj) override;`
- L150 _public prototype_ `virtual FArchive& operator<<(FLazyObjectPtr& LazyObjectPtr) override;`
- L151 _public prototype_ `virtual FArchive& operator<<(FObjectPtr& Obj) override;`
- L152 _public prototype_ `virtual FArchive& operator<<(FSoftObjectPtr& AssetPtr) override;`
- L153 _public prototype_ `virtual FArchive& operator<<(FSoftObjectPath& AssetPtr) override;`
- L154 _public prototype_ `virtual FArchive& operator<<(FWeakObjectPtr& Value) override;`
- L155 _public prototype_ `virtual FString GetArchiveName() const override;`
- L158 _public function_ `void SetSerializeNestedObjects(bool bInSerializeNestedObjects)`
- L163 _protected function_ `virtual void OnObjectSerialized(const FSoftObjectPath& Obj)`
- L166 _private member_ `bool bSerializeNestedObjects = false;`
- L167 _private member_ `UObject* CurrentOuter = nullptr;`
- L168 _private member_ `FConcertSyncWorldRemapper WorldRemapper;`
- L169 _private member_ `FConcertSyncEncounteredMissingObject EncounteredMissingObjectDelegate;`

#### class `FConcertSyncObjectRewriter`  
`class FConcertSyncObjectRewriter : public FConcertIdentifierRewriter`  
_L173-199_
- inherits: `FConcertIdentifierRewriter`
- desc: Archive for rewriting identifiers (currently names) so that they belong to a different identifier table
- L176 _public prototype_ `FConcertSyncObjectRewriter(const FConcertLocalIdentifierTable* InLocalIdentifierTable, FConcertLocalIdentifierTable* InRewriteIdentifierTable, const FConcertSessionVersionInfo* InVersionInfo, TArray<uint8>& InBytes);`
- L178 _public prototype_ `void RewriteObject(const UClass* InClass);`
- L179 _public prototype_ `void RewriteProperty(const FProperty* InProp);`
- L184 _public prototype_ `virtual FArchive& operator<<(UObject*& Obj) override;`
- L185 _public prototype_ `virtual FArchive& operator<<(FLazyObjectPtr& LazyObjectPtr) override;`
- L186 _public prototype_ `virtual FArchive& operator<<(FObjectPtr& Obj) override;`
- L187 _public prototype_ `virtual FArchive& operator<<(FSoftObjectPtr& AssetPtr) override;`
- L188 _public prototype_ `virtual FArchive& operator<<(FSoftObjectPath& AssetPtr) override;`
- L189 _public prototype_ `virtual FArchive& operator<<(FWeakObjectPtr& Value) override;`
- L190 _public prototype_ `virtual FString GetArchiveName() const override;`
- L195 _protected function_ `virtual void OnObjectSerialized(FSoftObjectPath& Obj)` — Called to rewrite the object path that will be stored in the persistent object value (InBytes)
- L198 _protected function_ `virtual FSoftObjectPath GetOutputObjectPath(const FSoftObjectPath& Obj)` — Called with the result of OnObjectSerialized to get the object path to set on the in-memory object value (the output of operator<<)

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API CONCERTSYNCCORE_API`
- L18 _delegate_ `DECLARE_DELEGATE_OneParam(FConcertSyncRemapObjectPath, FString& ) DECLARE_DELEGATE_RetVal_OneParam(bool, FConcertSyncObjectPathBelongsToWorld, const FStringView ) DECLARE_DELEGATE_OneParam(FConcertSyncEncounteredMissingObject, const FStringView ) namespace ConcertSyncUtil { bool CanExportProperty(const FProperty* Property, const bool InIncludeEditorOnlyData); void ResetObjectPropertiesToArchetypeValues(UObject* Object, const bool InIncludeEditorOnlyData); struct FResetValueOptions { bool bIncludeEditorOnlyData = true; bool bIsDuplicate = false; bool bSaveGameOnly = false; TSet<FSoftObjectPath> ObjectsToSkip; TFunction<bool(const FArchive& Ar, const FProperty* Property)> ShouldSkipProperty;`
- L19 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FConcertSyncObjectPathBelongsToWorld, const FStringView ) DECLARE_DELEGATE_OneParam(FConcertSyncEncounteredMissingObject, const FStringView ) namespace ConcertSyncUtil { bool CanExportProperty(const FProperty* Property, const bool InIncludeEditorOnlyData); void ResetObjectPropertiesToArchetypeValues(UObject* Object, const bool InIncludeEditorOnlyData); struct FResetValueOptions { bool bIncludeEditorOnlyData = true; bool bIsDuplicate = false; bool bSaveGameOnly = false; TSet<FSoftObjectPath> ObjectsToSkip; TFunction<bool(const FArchive& Ar, const FProperty* Property)> ShouldSkipProperty;`
- L20 _delegate_ `DECLARE_DELEGATE_OneParam(FConcertSyncEncounteredMissingObject, const FStringView ) namespace ConcertSyncUtil { bool CanExportProperty(const FProperty* Property, const bool InIncludeEditorOnlyData); void ResetObjectPropertiesToArchetypeValues(UObject* Object, const bool InIncludeEditorOnlyData); struct FResetValueOptions { bool bIncludeEditorOnlyData = true; bool bIsDuplicate = false; bool bSaveGameOnly = false; TSet<FSoftObjectPath> ObjectsToSkip; TFunction<bool(const FArchive& Ar, const FProperty* Property)> ShouldSkipProperty; /**`
- L22 _namespace_ `namespace ConcertSyncUtil`
- L24 _prototype_ `bool CanExportProperty(const FProperty* Property, const bool InIncludeEditorOnlyData);` (scope `ConcertSyncUtil`)
- L26 _prototype_ `void ResetObjectPropertiesToArchetypeValues(UObject* Object, const bool InIncludeEditorOnlyData);` (scope `ConcertSyncUtil`)
- L67 _prototype_ `void ResetObjectPropertiesToTemplateValues(UObject* Object, const UObject* Template, const FResetValueOptions& Options);` (scope `ConcertSyncUtil`)
- L69 _prototype_ `const FSoftObjectPath& GetSkipObjectPath();` (scope `ConcertSyncUtil`)

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncCore/Source/ConcertSyncCore/Public/ConcertSyncSessionDatabase.h` (Public)


#### class `FConcertSyncSessionDatabase`  
`class FConcertSyncSessionDatabase`  
_L51-1101_
- desc: Database of activities that have happened in a Concert Sync Session. Stores the activity index and their associated data.
- L55 _public prototype_ `FConcertSyncSessionDatabase();`
- L56 _public prototype_ `~FConcertSyncSessionDatabase();`
- L58 _public prototype_ `FConcertSyncSessionDatabase(const FConcertSyncSessionDatabase&) = delete;`
- L59 _public prototype_ `FConcertSyncSessionDatabase& operator=(const FConcertSyncSessionDatabase&) = delete;`
- L61 _public prototype_ `FConcertSyncSessionDatabase(FConcertSyncSessionDatabase&&);`
- L62 _public prototype_ `FConcertSyncSessionDatabase& operator=(FConcertSyncSessionDatabase&&);`
- L67 _public prototype_ `bool IsValid() const;` — Is this a valid database? (ie, has been successfully opened).
- L76 _public prototype_ `bool Open(const FString& InSessionPath);` — Open (or create) a database file. @param InSessionPath				The root path to store all the data for this session under. @return True if the database was opened, false otherwise.
- L86 _public prototype_ `bool Open(const FString& InSessionPath, const ESQLiteDatabaseOpenMode InOpenMode);` — Open (or create) a database file. @param InSessionPath				The root path to store all the data for this session under. @param InOpenMode				How should the database be opened? @return True if the database was opened, false otherwise.
- L93 _public prototype_ `bool Close(const bool InDeleteDatabase = false);` — Close an open database file. @param InDeleteDatabase			True if the session database and its associated data should be deleted after closing the database.
- L99 _public prototype_ `FString GetFilename() const;` — Get the filename of the currently open database, or an empty string. @note The returned filename will be an absolute pathname.
- L104 _public prototype_ `FString GetLastError() const;` — Get the last error reported by this database.
- L117 _public prototype_ `bool AddConnectionActivity(const FConcertSyncConnectionActivity& InConnectionActivity, int64& OutActivityId, int64& OutConnectionEventId);` — Add a new connection activity to this database, assigning it both an activity and connection event ID. @note The endpoint ID referenced by the activity must exist in the database (@see SetEndpoint). @note This function is expected to be called on the server to populate its version of the session database. @param InConnectionActivity		The connection activity to add (the ActivityId, EventTime, EventType, and EventId members are ignored). @param OutActivityId				Populated with the ID of this activity in the database. @param OutConnectionEventId		Populated with the ID of the connection event in the database (@see GetConnectionEvent). @return True if the connection activity was added, false otherwise.
- L130 _public prototype_ `bool AddLockActivity(const FConcertSyncLockActivity& InLockActivity, int64& OutActivityId, int64& OutLockEventId);` — Add a new lock activity to this database, assigning it both an activity and lock event ID. @note The endpoint ID referenced by the activity must exist in the database (@see SetEndpoint). @note This function is expected to be called on the server to populate its version of the session database. @param InLockActivity			The lock activity to add (the ActivityId, EventTime, EventType, and EventId members are ignored). @param OutActivityId				Populated with the ID of this activity in the database. @param OutLockEventId			Populated with the ID of the lock event in the database (@see GetLockEvent). @return True if the lock activity was added, false otherwise.
- L143 _public prototype_ `bool AddTransactionActivity(const FConcertSyncTransactionActivity& InTransactionActivity, int64& OutActivityId, int64& OutTransactionEventId);` — Add a new transaction activity to this database, assigning it both an activity and transaction event ID. @note The endpoint ID referenced by the activity must exist in the database (@see SetEndpoint). @note This function is expected to be called on the server to populate its version of the session database. @param InTransactionActivity		The transaction activity to add (the ActivityId, EventTime, EventType, and EventId members are ignored). @param OutActivityId				Populated with the ID of this activity in the database. @param OutTransactionEventId		Populated with the ID of the transaction event in the database (@see GetTransactionEvent). @return True if the transaction activity was added, false otherwise.
- L158 _public prototype_ `bool AddPackageActivity(const FConcertSyncActivity& InPackageActivity, const FConcertPackageInfo& InPackageInfo, FConcertPackageDataStream& InPackageDataStream, int64& OutActivityId, int64& OutPackageEventId);` — Add a new package activity to this database, assigning it both an activity and package event ID. @note The endpoint ID referenced by the activity must exist in the database (@see SetEndpoint). @note This function is expected to be called on the server to populate its version of the session database. @param InPackageActivity			The base part of the package activity to add (the ActivityId, EventTime, EventType, EventId, and PackageRevision members are ignored). @param InPackageInfo				Information about the package affected. @param InPackageDataStream		A stream to the package data if the activty is about adding or modifying a package. Can be empty when the activity is about deleting or discarding changes. @param OutActivityId				Populated with the ID of this activity in the database. @param OutPackageEventId			Populated with the ID of the package event in the database (@see GetPackageEvent). @return True if the package activity was added, false otherwise.
- L171 _public prototype_ `bool AddReplicationActivity(const FConcertSyncReplicationActivity& InReplicationActivity, int64& OutActivityId, int64& OutReplicationEventId);` — Add a new replication activity to this database, assigning it both an activity and lock event ID. @note The endpoint ID referenced by the activity must exist in the database (@see SetEndpoint). @note This function is expected to be called on the server to populate its version of the session database. @param InReplicationActivity		The lock activity to add (the ActivityId, EventTime, EventType, and EventId members are ignored). @param OutActivityId				Populated with the ID of this activity in the database. @param OutReplicationEventId			Populated with the ID of the lock event in the database (@see GetLockEvent). @return True if the lock activity was added, false otherwise.
- L176 _public prototype_ `bool SetActivities(const TSet<int64>& ActivityIds, TFunctionRef<void(FConcertSyncActivity&)> UpdateCallback);` — Iterates the given range, calls UpdateCallback on each element, and commits the update.
- L187 _public prototype_ `bool SetConnectionActivity(const FConcertSyncConnectionActivity& InConnectionActivity);` — Set a connection activity in this database, creating or replacing it. @note The endpoint ID referenced by the activity must exist in the database (@see SetEndpoint). @note This function is expected to be called on the client to populate its version of the session database from data synced from the server. @param InConnectionActivity		The connection activity to set. @return True if the connection activity was set, false otherwise.
- L198 _public prototype_ `bool SetLockActivity(const FConcertSyncLockActivity& InLockActivity);` — Set a lock activity in this database, creating or replacing it. @note The endpoint ID referenced by the activity must exist in the database (@see SetEndpoint). @note This function is expected to be called on the client to populate its version of the session database from data synced from the server. @param InLockActivity			The lock activity to set. @return True if the lock activity was set, false otherwise.
- L210 _public prototype_ `bool SetTransactionActivity(const FConcertSyncTransactionActivity& InTransactionActivity, const bool bMetaDataOnly = false);` — Set a transaction activity in this database, creating or replacing it. @note The endpoint ID referenced by the activity must exist in the database (@see SetEndpoint). @note This function is expected to be called on the client to populate its version of the session database from data synced from the server. @param InTransactionActivity		The transaction activity to set. @param bMetaDataOnly				True to store the meta data only, omitting the transaction data required to replay the transaction. @return True if the transaction activity was set, false otherwise.
- L223 _public prototype_ `bool SetPackageActivity(const FConcertSyncActivity& InPackageActivity, FConcertSyncPackageEventData& InPackageActivityEvent, const bool bMetaDataOnly = false);` — Set a package activity in this database, creating or replacing it. @note The endpoint ID referenced by the activity must exist in the database (@see SetEndpoint). @note This function is expected to be called on the client to populate its version of the session database from data synced from the server. @param InPackageActivity			The base part of the package activity to set. @param InPackageActivityEvent	The event meta data (package info + revision) and possibly the corresponding package data. @param bMetaDataOnly				True to store the meta data only, omitting the package data itself. @return True if the package activity was set, false otherwise.
- L234 _public prototype_ `bool SetReplicationActivity(const FConcertSyncReplicationActivity& InReplicationActivity);` — Set a replication activity in this database, creating or replacing it. @note The endpoint ID referenced by the activity must exist in the database (@see SetEndpoint). @note This function is expected to be called on the client to populate its version of the session database from data synced from the server. @param InReplicationActivity		The replication activity to set. @return True if the transaction activity was set, false otherwise.
- L244 _public prototype_ `bool GetActivity(const int64 InActivityId, FConcertSyncActivity& OutActivity) const;` — Get the generic part of an activity from this database. @param InActivityId				The ID of the activity to find. @param OutActivity				The generic part of an activity to populate with the result. @return True if the activity was found, false otherwise.
- L254 _public prototype_ `bool GetConnectionActivity(const int64 InActivityId, FConcertSyncConnectionActivity& OutConnectionActivity) const;` — Get a connection activity from this database. @param InActivityId				The ID of the activity to find. @param OutConnectionActivity		The connection activity to populate with the result. @return True if the connection activity was found, false otherwise.
- L264 _public prototype_ `bool GetLockActivity(const int64 InActivityId, FConcertSyncLockActivity& OutLockActivity) const;` — Get a lock activity from this database. @param InActivityId				The ID of the activity to find. @param OutLockActivity			The lock activity to populate with the result. @return True if the lock activity was found, false otherwise.
- L274 _public prototype_ `bool GetTransactionActivity(const int64 InActivityId, FConcertSyncTransactionActivity& OutTransactionActivity) const;` — Get a transaction activity from this database. @param InActivityId				The ID of the activity to find. @param OutTransactionActivity	The transaction activity to populate with the result. @return True if the transaction activity was found, false otherwise.
- L285 _public prototype_ `bool GetPackageActivity(const int64 InActivityId, FConsumePackageActivityFunc PackageActivityFn) const;` — Get a package activity from this database. @param InActivityId			The ID of the activity to find. @param PackageActivityFn		A callback invoked with the package activity components (the base activity part and the event part). @note The package data stream passed to the callback through the FConcertSycnPackageEventData is only valid during the callback. @return True if the package activity was found, false otherwise.
- L295 _public prototype_ `bool GetReplicationActivity(const int64 InActivityId, FConcertSyncReplicationActivity& OutReplicationActivity) const;` — Get a replication activity from this database. @param InActivityId				The ID of the activity to find. @param OutReplicationActivity	The replication activity to populate with the result. @return True if the replication activity was found, false otherwise.
- L305 _public prototype_ `bool GetReplicationActivityForEvent(const int64 InEventId, FConcertSyncReplicationActivity& OutReplicationActivity) const;` — Get a replication activity from this database by its event ID @param InEventId					The ID of the event that is saved in a replication activity. @param OutReplicationActivity	The replication activity to populate with the result. @return True if the replication activity was found, false otherwise.
- L315 _public prototype_ `bool GetActivityEventType(const int64 InActivityId, EConcertSyncActivityEventType& OutEventType) const;` — Get the type of an activity in this database. @param InActivityId				The ID of the activity to query. @param OutEventType				The event type to populate with the result. @return True if the activity was found, false otherwise.
- L326 _public prototype_ `bool GetActivityForEvent(const int64 InEventId, const EConcertSyncActivityEventType InEventType, FConcertSyncActivity& OutActivity) const;` — Get the generic part of an activity for an event in this database. @param InEventId					The ID of the event to find the activity for. @param InEventType				The type of the event to find the activity for. @param OutActivity				The generic part of an activity to populate with the result. @return True if the activity was found, false otherwise.
- L336 _public prototype_ `bool GetConnectionActivityForEvent(const int64 InConnectionEventId, FConcertSyncConnectionActivity& OutConnectionActivity) const;` — Get a connection activity for an event in this database. @param InConnectionEventId		The ID of the connection event to find the activity for. @param OutConnectionActivity		The connection activity to populate with the result. @return True if the connection activity was found, false otherwise.
- L346 _public prototype_ `bool GetLockActivityForEvent(const int64 InLockEventId, FConcertSyncLockActivity& OutLockActivity) const;` — Get a lock activity for an event in this database. @param InLockEventId				The ID of the lock event to find the activity for. @param OutLockActivity			The lock activity to populate with the result. @return True if the lock activity was found, false otherwise.
- L356 _public prototype_ `bool GetTransactionActivityForEvent(const int64 InTransactionEventId, FConcertSyncTransactionActivity& OutTransactionActivity) const;` — Get a transaction activity for an event in this database. @param InTransactionEventId		The ID of the transaction event to find the activity for. @param OutTransactionActivity	The transaction activity to populate with the result. @return True if the transaction activity was found, false otherwise.
- L367 _public prototype_ `bool GetPackageActivityForEvent(const int64 InPackageEventId, FIteratePackageActivityFunc PackageActivityFn) const;` — Get a package activity for an event in this database. @param InPackageEventId		The ID of the package event to find the activity for. @param PackageActivityFn		A callback invoked with the package activity components (the base activity part and the event part). @note The package data stream passed to the callback through the FConcertSycnPackageEventData is only valid during the callback. @return True if the package activity was found, false otherwise.
- L376 _public prototype_ `bool EnumerateActivities(FIterateActivityFunc InCallback) const;` — Enumerate the generic part of the activities in this database. @param InCallback				Callback invoked for each activity; return true to continue enumeration, or false to stop. @return True if the activities were enumerated without error, false otherwise.
- L385 _public prototype_ `bool EnumerateConnectionActivities(TFunctionRef<bool(FConcertSyncConnectionActivity&&)> InCallback) const;` — Enumerate all the connection activities in this database. @param InCallback				Callback invoked for each activity; return true to continue enumeration, or false to stop. @return True if the connection activities were enumerated without error, false otherwise.
- L394 _public prototype_ `bool EnumerateLockActivities(TFunctionRef<bool(FConcertSyncLockActivity&&)> InCallback) const;` — Enumerate all the lock activities in this database. @param InCallback				Callback invoked for each activity; return true to continue enumeration, or false to stop. @return True if the lock activities were enumerated without error, false otherwise.
- L403 _public prototype_ `bool EnumerateTransactionActivities(TFunctionRef<bool(FConcertSyncTransactionActivity&&)> InCallback) const;` — Enumerate all the transaction activities in this database. @param InCallback				Callback invoked for each activity; return true to continue enumeration, or false to stop. @return True if the transaction activities were enumerated without error, false otherwise.
- L412 _public prototype_ `bool EnumeratePackageActivities(FIteratePackageActivityFunc InCallback) const;` — Enumerate all the package activities in this database. @param InCallback				Callback invoked for each activity; return true to continue enumeration, or false to stop. @return True if the package activities were enumerated without error, false otherwise.
- L421 _public prototype_ `bool EnumerateReplicationActivities(TFunctionRef<bool(FConcertSyncReplicationActivity&&)> InCallback) const;` — Enumerate all the replication activities in this database. @param InCallback				Callback invoked for each activity; return true to continue enumeration, or false to stop. @return True if the replication activities were enumerated without error, false otherwise.
- L431 _public prototype_ `bool EnumerateActivitiesForEventType(const EConcertSyncActivityEventType InEventType, FIterateActivityFunc InCallback) const;` — Enumerate all the activities in this database of the given type. @param InEventType				The type of the event to enumerate the activities for. @param InCallback				Callback invoked for each activity; return true to continue enumeration, or false to stop. @return True if the activities were enumerated without error, false otherwise.
- L442 _public prototype_ `bool EnumerateActivitiesInRange(const int64 InFirstActivityId, const int64 InMaxNumActivities, FIterateActivityFunc InCallback) const;` — Enumerate all the activities in this database in the given range. @param InFirstActivityId			The first activity ID to include in the results. @param InMaxNumActivities		The maximum number of activities to include in the results. @param InCallback				Callback invoked for each activity; return true to continue enumeration, or false to stop. @return True if the activities were enumerated without error, false otherwise.
- L451 _public prototype_ `bool EnumerateActivityIdsAndEventTypes(TFunctionRef<bool(int64, EConcertSyncActivityEventType)> InCallback) const;` — Enumerate the IDs and event types of all the activities in this database. @param InCallback				Callback invoked for each activity; return true to continue enumeration, or false to stop. @return True if the activities were enumerated without error, false otherwise.
- L462 _public prototype_ `bool EnumerateActivityIdsAndEventTypesInRange(const int64 InFirstActivityId, const int64 InMaxNumActivities, TFunctionRef<bool(int64, EConcertSyncActivityEventType)> InCallback) const;` — Enumerate the IDs and event types of the activities in this database in the given range. @param InFirstActivityId			The first activity ID to include in the results. @param InMaxNumActivities		The maximum number of activities to include in the results. @param InCallback				Callback invoked for each activity; return true to continue enumeration, or false to stop. @return True if the activities were enumerated without error, false otherwise.
- L473 _public prototype_ `bool EnumerateActivityIdsWithEventTypesAndFlagsInRange(const int64 InFirstActivityId, const int64 InMaxNumActivities, TFunctionRef<bool(int64, EConcertSyncActivityEventType, EConcertSyncActivityFlags)> InCallback) const;` — Enumerate the IDs, event types and flags of the activities in this database in the given range. @param InFirstActivityId			The first activity ID to include in the results. @param InMaxNumActivities		The maximum number of activities to include in the results. @param InCallback				Callback invoked for each activity; return true to continue enumeration, or false to stop. @return True if the activities were enumerated without error, false otherwise.
- L482 _public prototype_ `bool GetActivityMaxId(int64& OutActivityId) const;` — Get the maximum ID of the activities in this database. @param OutActivityId				The activity ID to populate with the result. @return True if the activity ID was resolved, false otherwise.
- L492 _public prototype_ `bool SetEndpoint(const FGuid& InEndpointId, const FConcertSyncEndpointData& InEndpointData);` — Set an endpoint in this database, creating or replacing it. @param InEndpointId				The ID of the endpoint to set. @param InEndpointData			The endpoint data to set. @return True if the endpoint was set, false otherwise.
- L502 _public prototype_ `bool GetEndpoint(const FGuid& InEndpointId, FConcertSyncEndpointData& OutEndpointData) const;` — Get an endpoint from this database. @param InEndpointId				The ID of the endpoint to find. @param OutEndpointData			The endpoint data to populate with the result. @return True if the endpoint was found, false otherwise.
- L511 _public prototype_ `bool EnumerateEndpoints(TFunctionRef<bool(FConcertSyncEndpointIdAndData&&)> InCallback) const;` — Enumerate all the endpoints in this database. @param InCallback				Callback invoked for each endpoint; return true to continue enumeration, or false to stop. @return True if the endpoints were enumerated without error, false otherwise.
- L520 _public prototype_ `bool EnumerateEndpointIds(TFunctionRef<bool(FGuid)> InCallback) const;` — Enumerate all the endpoint IDs in this database. @param InCallback				Callback invoked for each endpoint ID; return true to continue enumeration, or false to stop. @return True if the endpoint IDs were enumerated without error, false otherwise.
- L530 _public prototype_ `bool GetConnectionEvent(const int64 InConnectionEventId, FConcertSyncConnectionEvent& OutConnectionEvent) const;` — Get a connection event from this database. @param InConnectionEventId		The ID of the connection event to find. @param OutConnectionEvent		The connection event to populate with the result. @return True if the connection event was found, false otherwise.
- L540 _public prototype_ `bool GetLockEvent(const int64 InLockEventId, FConcertSyncLockEvent& OutLockEvent) const;` — Get a lock event from this database. @param InLockEventId				The ID of the lock event to find. @param OutLockEvent				The lock event to populate with the result. @return True if the lock event was found, false otherwise.
- L551 _public prototype_ `bool GetTransactionEvent(const int64 InTransactionEventId, FConcertSyncTransactionEvent& OutTransactionEvent, const bool InMetaDataOnly = false) const;` — Get a transaction event from this database. @param InTransactionEventId		The ID of the transaction event to find. @param OutTransactionEvent		The transaction event to populate with the result. @param InMetaDataOnly			True to only get the meta-data for the transaction, and skip the bulk of the data. @return True if the transaction event was found, false otherwise.
- L561 _public prototype_ `bool GetReplicationEvent(const int64 InReplicationEventId, FConcertSyncReplicationEvent& OutReplicationEvent) const;` — Get a replication event from this database. @param InReplicationEventId		The ID of the replication event to find. @param OutReplicationEvent		The replication event to populate with the result. @return True if the replication event was found, false otherwise.
- L570 _public prototype_ `bool GetTransactionMaxEventId(int64& OutTransactionEventId) const;` — Get the maximum ID of the transaction events in this database. @param OutTransactionEventId		The transaction event ID to populate with the result. @return True if the transaction event ID was resolved, false otherwise.
- L580 _public prototype_ `bool IsLiveTransactionEvent(const int64 InTransactionEventId, bool& OutIsLive) const;` — Check whether the given transaction event ID is currently for a live transaction event. @param InTransactionEventId		The ID of the transaction event to check. @param OutIsLive					Bool to populate with the result. @return True if the transaction event ID was queried successfully, false otherwise.
- L589 _public prototype_ `bool GetLiveTransactionEventIds(TArray<int64>& OutTransactionEventIds) const;` — Get the IDs of any live transaction events. @param OutTransactionEventIds	The array of transaction event IDs to populate with the result (will be sorted in ascending order). @return True if the live transaction event IDs were resolved, false otherwise.
- L599 _public prototype_ `bool GetLiveTransactionEventIdsForPackage(const FName InPackageName, TArray<int64>& OutTransactionEventIds) const;` — Get the IDs of any live transaction events for the given package name. @param InPackageName				The name of the package to get the live transaction event IDs for. @param OutTransactionEventIds	The array of transaction event IDs to populate with the result (will be sorted in ascending order). @return True if the live transaction event IDs were resolved, false otherwise.
- L609 _public prototype_ `bool PackageHasLiveTransactions(const FName InPackageName, bool& OutHasLiveTransaction) const;` — Get if a Package has any live transactions @param InPackageName				The name of the package to check if it has live transactions. @param OutHasLiveTransaction		Bool to populate with the result. @return True if query was resolved correctly, false otherwise.
- L619 _public prototype_ `bool EnumerateLiveTransactionEventIdsForPackage(const FName InPackageName, TFunctionRef<bool(int64)> InCallback) const;` — Enumerate the IDs of any live transaction events for the given package name. @param InPackageName				The name of the package to get the live transaction event IDs for. @param InCallback				Callback invoked for each transaction event ID; return true to continue enumeration, or false to stop. @return True if the live transaction event IDs were enumerated without error, false otherwise.
- L628 _public prototype_ `bool EnumeratePackageNamesWithLiveTransactions(TFunctionRef<bool(FName)> InCallback) const;` — Enumerate the names of of any packages that have live transaction events. @param InCallback				Callback invoked for each package name; return true to continue enumeration, or false to stop. @return True if the package names were enumerated without error, false otherwise.
- L639 _public prototype_ `bool AddDummyPackageEvent(const FName InPackageName, int64& OutPackageEventId);` — Add a new dummy package event to this database, assigning it a package event ID. @note These are use to fence live transactions without generating a full activity entry (eg, when saving packages locally on the client during a persist operation). @param InPackageName				The name of the package to add the event for. @param OutPackageEventId			Populated with the ID of the package event in the database. @return True if the package event was added, false otherwise.
- L650 _public prototype_ `bool GetPackageEventMetaData(const int64 InPackageEventId, int64& OuptPackageRevision, FConcertPackageInfo& OutPackageInfo) const;` — Get a package event meta data (omitting the package data itself) from this database. @param InPackageEventId		The ID of the package event to find. @param OuptPackageRevision	The package revision number. @param OutPackageInfo		The Package info. @return True if the package event was found, false otherwise.
- L660 _public prototype_ `bool GetPackageHeadEventFromName(const FName InPackageName, int64& OutPackageEventId);` — Get Package Event Id from Package Name.  The event id will be from the head revision of the package. @param InPackageName @param OutPackageEventId @return True if the package event was found, false otherwise
- L670 _public prototype_ `bool GetPackageEvent(const int64 InPackageEventId, const TFunctionRef<void(FConcertSyncPackageEventData&)>& PackageEventFn) const;` — Get a package event from this database. @param InPackageEventId			The ID of the package event to find. @param PackageEventFn			The callback invoked with the package event containing the event meta data and the package data if available. @return True if the package event was found, false otherwise.
- L680 _public prototype_ `bool EnumeratePackageNamesWithHeadRevision(TFunctionRef<bool(FName)> InCallback, bool IgnorePersisted) const;` — Enumerate package names for packages with a head revision (at least one package event) @param InCallback				Callback invoked for each package name; return true to continue enumeration, or false to stop. @param IgnorePersisted			Will skip enumeration of packages which head revision have been persisted. @return True if the package data was enumerated without error, false otherwise.
- L689 _public prototype_ `bool EnumerateHeadRevisionPackageData(TFunctionRef<bool(const FConcertPackageInfo&, FConcertPackageDataStream&)> InCallback) const;` — Enumerate the head revision package data for all packages in this database. @param InCallback				Callback invoked for each package; return true to continue enumeration, or false to stop. @return True if the package data was enumerated without error, false otherwise.
- L700 _public prototype_ `bool GetPackageInfoForRevision(const FName InPackageName, FConcertPackageInfo& OutPackageInfo, const int64* InPackageRevision = nullptr) const;` — Get the data from this database for the given package name for the given revision. @param InPackageName				The name of the package to get the head revision for. @param OutPackageInfo			The package info to populate with the result. @param InPackageRevision			The revision of the package to get the data for, or null to get the head revision. @return True if package data could be found for the given revision, false otherwise.
- L711 _public prototype_ `bool GetPackageDataForRevision(const FName InPackageName, const TFunctionRef<void(const FConcertPackageInfo&, FConcertPackageDataStream&)>& InCallback, const int64* InPackageRevision = nullptr) const;` — Get the data from this database for the given package name for the given revision. @param InPackageName				The name of the package to get the head revision for. @param InCallback				A callback invoked with the package info and package data. @param InPackageRevision			The revision of the package to get the data for, or null to get the head revision. @return True if package data could be found for the given revision, false otherwise.
- L721 _public prototype_ `TOptional<int64> GetPackageSizeForRevision(const FName InPackageName, const int64* InPackageRevision = nullptr) const;` — Gets the package size in bytes of a package @param InPackageName				The name of the package to get the head revision for. @param InPackageRevision			The revision of the package to get the data for, or null to get the head revision. @return True if package data could be found for the given revision, false otherwise.
- L731 _public prototype_ `bool GetPackageHeadRevision(const FName InPackageName, int64& OutRevision) const;` — Get the head revision in this database for the given package name. @param InPackageName				The name of the package to get the head revision for. @param OutRevision				The package revision to populate with the result. @return True if the head revision was resolved, false otherwise.
- L741 _public prototype_ `bool IsHeadRevisionPackageEvent(const int64 InPackageEventId, bool& OutIsHeadRevision) const;` — Check whether the given package event ID is currently for the head revision of the package in the event. @param InPackageEventId			The ID of the package event to check. @param OutIsHeadRevision			Bool to populate with the result. @return True if the package event ID was queried successfully, false otherwise.
- L752 _public prototype_ `bool GetReplicationMaxEventIdByClientAndType(const FGuid& EndpointId, EConcertSyncReplicationActivityType ActivityType, int64& OutReplicationEventId) const;` — Get the maximum ID of the replication events in this database that was triggered by EndpointId and had ActivityType. @param EndpointId				The ID of the client that created the activity @param ActivityType				The activity type the replication activity should have @param OutReplicationEventId		The replication event ID to populate with the result. @return True if the replication event ID was resolved, false otherwise.
- L762 _public prototype_ `bool AddPersistEventForHeadRevision(FName InPackageName, int64& OutPersistEventId);` — Add a package event ID for the head revision to the persist events in this database, if not already existing. @param PackageName				The package name to add an event for. @param OutPersistEventId			Populated with the ID of the persist event in the database. @return True if the persist event was added, false otherwise.
- L771 _public prototype_ `bool UpdateTransactionEvent(const int64 InTransactionEventId, const FConcertSyncTransactionEvent& InTransactionEvent);` — Update the specified transaction event. @note The function is meant to update a transaction event that was partially synced to store the corresponding transaction data. @param InTransactionEventId		The ID of the event to update. @param InTransactionEvent		The event to store. @return True if the transaction was updated.
- L780 _public prototype_ `bool UpdatePackageEvent(const int64 InPackageEventId, FConcertSyncPackageEventData& PackageEvent);` — Update the specified package event. @note The function is meant to be update a partially synced package event to store the corresponding package data. @param InPackageEventId			The ID of the event to update. @param PackageEvent				The event to store. @return True if the package was updated.
- L785 _public prototype_ `void UpdateAsynchronousTasks();` — Check Asynchronous Tasks Status
- L790 _public prototype_ `void FlushAsynchronousTasks();` — Flush any ongoing asynchronous tasks.
- L795 _public prototype_ `bool HasWritePackageTasksCompleted() const;` — Has all asynchronous package tasks completed.
- L797 _public function_ `FOnActivityProduced& OnActivityProduced()`
- L801 _private typedef_ `using FProcessPackageRequest = TFunctionRef<bool(const FConcertPackageInfo& PackageInfo, const FString& DataFilename)>;`
- L803 _private prototype_ `bool HandleRequestPackageRequest(const FName InPackageName, const int64* InPackageRevision, FProcessPackageRequest HandleFunc) const;` — Helper function which obtains package information and passes it to HandleFunc.
- L806 _private prototype_ `TOptional<int64> GetSpecifiedOrHeadPackageRevision(FName InPackageName, const int64* InPackageRevision) const;` — Helper functions that for getting a package revision for an optional package revision argument
- L816 _private prototype_ `void ScheduleAsyncWrite(const FName& InPackageName, const FString& InDstPackageBlobPathname, FConcertPackageDataStream& InPackageDataStream);` — Schedule an asynchronous write for the given Package Stream.  The stream must be in-memory. File sharing asynchronous write is not supported. @param InPackageName	            Name of the package in content area. @param InDstPackageBlobPathName  Full path of the destination package. @param InPackageDataStream       The package data stream.
- L826 _private prototype_ `bool SetActivityIgnoredState(const int64 InActivityId, const bool InIsIgnored);` — Set the active ignored state for the given activity. @param InActivityId				The ID of the activity to update. @param InIsIgnored				True if this activity should be ignored, false otherwise. @return True if the ignored state was set, false otherwise.
- L836 _private prototype_ `bool AddConnectionEvent(const FConcertSyncConnectionEvent& InConnectionEvent, int64& OutConnectionEventId);` — Add a new connection event to this database, assigning it a connection event ID. @param InConnectionEvent			The connection event to add. @param OutConnectionEventId		Populated with the ID of the connection event in the database. @return True if the connection event was added, false otherwise.
- L846 _private prototype_ `bool SetConnectionEvent(const int64 InConnectionEventId, const FConcertSyncConnectionEvent& InConnectionEvent);` — Set a connection event in this database, creating or replacing it. @param InConnectionEventId		The ID of the connection event to set. @param InConnectionEvent			The connection event to set. @return True if the connection event was set, false otherwise.
- L856 _private prototype_ `bool AddLockEvent(const FConcertSyncLockEvent& InLockEvent, int64& OutLockEventId);` — Add a new lock event to this database, assigning it a lock event ID. @param InLockEvent				The lock event to add. @param OutLockEventId			Populated with the ID of the lock event in the database. @return True if the lock event was added, false otherwise.
- L866 _private prototype_ `bool SetLockEvent(const int64 InLockEventId, const FConcertSyncLockEvent& InLockEvent);` — Set a lock event in this database, creating or replacing it. @param InLockEventId				The ID of the lock event to set. @param InLockEvent				The lock event to set. @return True if the lock event was set, false otherwise.
- L876 _private prototype_ `bool AddTransactionEvent(const FConcertSyncTransactionEvent& InTransactionEvent, int64& OutTransactionEventId);` — Add a new transaction event to this database, assigning it a transaction event ID. @param InTransactionEvent		The transaction event to add. @param OutTransactionEventId		Populated with the ID of the transaction event in the database. @return True if the transaction event was added, false otherwise.
- L887 _private prototype_ `bool SetTransactionEvent(const int64 InTransactionEventId, const FConcertSyncTransactionEvent& InTransactionEvent, const bool bMetaDataOnly = false);` — Set a transaction event in this database, creating or replacing it. @param InTransactionEventId		The ID of the transaction event to set. @param InTransactionEvent		The transaction event to set. @param bMetaDataOnly				True to store the meta data only, omitting the transaction data. @return True if the transaction event was set, false otherwise.
- L897 _private prototype_ `bool EnumerateLiveTransactionEventIdsForPackage(const int64 InPackageNameId, TFunctionRef<bool(int64)> InCallback) const;` — Enumerate the IDs of any live transaction events for the given package name ID. @param InPackageNameId			The package name ID to get the live transaction event IDs for. @param InCallback				Callback invoked for each transaction event ID; return true to continue enumeration, or false to stop. @return True if the live transaction event IDs were enumerated without error, false otherwise.
- L908 _private prototype_ `bool AddPackageEvent(const FConcertPackageInfo& InPackageInfo, FConcertPackageDataStream& InPackageDataStream, int64& OutPackageEventId);` — Add a new package event to this database, assigning it a package event ID. @param InPackageInfo				The package info to add for this event. @param InPackageDataStream		The package data to add for this event (may be empty if the event doesn't carry package data). @param OutPackageEventId			Populated with the ID of the package event in the database. @return True if the package event was added, false otherwise.
- L920 _private prototype_ `bool SetPackageEvent(const int64 InPackageEventId, int64 PackageRevision, const FConcertPackageInfo& PackageInfo, FConcertPackageDataStream* InPackageDataStream);` — Set a package event in this database, creating or replacing it. @param InPackageEventId			The ID of the package event to set. @param PackageRevision			The package revision number. @param PackageInfo				The package info. @param InPackageDataStream		The package data stream or null to set only the package meta data (revision and package info). @return True if the package event was set, false otherwise.
- L930 _private prototype_ `bool AddReplicationEvent(const FConcertSyncReplicationEvent& InReplicationEvent, int64& OutReplicationEventId);` — Add a new replication event to this database, assigning it a replication event ID. @param InReplicationEvent		The transaction event to add. @param OutReplicationEventId		Populated with the ID of the transaction event in the database. @return True if the replication event was added, false otherwise.
- L940 _private prototype_ `bool SetReplicationEvent(const int64 InReplicationEventId, const FConcertSyncReplicationEvent& InReplicationEvent);` — Set a replication event in this database, creating or replacing it. @param InReplicationEventId		The ID of the replication event to set. @param InReplicationEvent		The replication event to set. @return True if the replication event was set, false otherwise.
- L949 _private prototype_ `bool GetPackageMaxEventId(int64& OutPackageEventId) const;` — Get the maximum ID of the package events in this database. @param OutPackageId				The package event ID to populate with the result. @return True if the package event ID was resolved, false otherwise.
- L959 _private prototype_ `bool GetObjectPathName(const int64 InObjectNameId, FName& OutObjectPathName) const;` — Get the object path name from this database that matches the given object name ID. @param InObjectNameId			The ID of the object path name to get the result for. @param OutObjectPathName			The object path name to populate with the result. @return True if the object path name was resolved, false otherwise.
- L969 _private prototype_ `bool GetObjectNameId(const FName InObjectPathName, int64& OutObjectNameId) const;` — Get the object name ID from this database that matches the given object path name. @param InObjectPathName			The object path name to get the result for. @param OutObjectNameId			The object name ID to populate with the result. @return True if the object name ID name was resolved, false otherwise.
- L979 _private prototype_ `bool EnsureObjectNameId(const FName InObjectPathName, int64& OutObjectNameId);` — Ensure that an object name ID in this database matches the given object path name, creating it if required. @param InObjectPathName			The object path name to get the result for. @param OutObjectNameId			The object name ID to populate with the result. @return True if the object name ID name was resolved, false otherwise.
- L989 _private prototype_ `bool GetPackageName(const int64 InPackageNameId, FName& OutPackageName) const;` — Get the package name from this database that matches the given package name ID. @param InPackageNameId			The ID of the package name to get the result for. @param OutPackageName			The package name to populate with the result. @return True if the package name was resolved, false otherwise.
- L999 _private prototype_ `bool GetPackageNameId(const FName InPackageName, int64& OutPackageNameId) const;` — Get the package name ID from this database that matches the given package name. @param InPackageName				The package name to get the result for. @param OutPackageNameId			The package name ID to populate with the result. @return True if the package name ID name was resolved, false otherwise.
- L1009 _private prototype_ `bool EnsurePackageNameId(const FName InPackageName, int64& OutPackageNameId);` — Ensure that a package name ID in this database matches the given package name, creating it if required. @param InPackageName				The package name to get the result for. @param OutPackageNameId			The package name ID to populate with the result. @return True if the package name ID name was resolved, false otherwise.
- L1019 _private prototype_ `bool MapResourceNamesForLock(const int64 InLockEventId, const TArray<FName>& InResourceNames);` — Map the resource names so that they have an association with the given lock event ID in this database. @param InLockEventId				The lock event ID to map resource references to. @param InResourceNames			The array of resource names to map. @return True if the resource name references were mapped, false otherwise.
- L1029 _private prototype_ `bool MapPackageNamesForTransaction(const int64 InTransactionEventId, const FConcertTransactionFinalizedEvent& InTransactionEvent);` — Map the package names in the given transaction so that they have an association with the given transaction event ID in this database. @param InTransactionEventId		The transaction event ID to map package references to. @param InTransactionEvent		The transaction containing potential package references. @return True if the package name references were mapped, false otherwise.
- L1039 _private prototype_ `bool MapObjectNamesForTransaction(const int64 InTransactionEventId, const FConcertTransactionFinalizedEvent& InTransactionEvent);` — Map the object path names in the given transaction so that they have an association with the given transaction event ID in this database. @param InTransactionEventId		The transaction event ID to map object references to. @param InTransactionEvent		The transaction containing potential object references. @return True if the object path name references were mapped, false otherwise.
- L1049 _private prototype_ `bool SaveTransaction(const FString& InTransactionFilename, const FStructOnScope& InTransaction) const;` — Save and cache the given transaction data with the given filename. @param InTransactionFilename		The filename to save the transaction data as. @param InTransaction				The transaction data to save. @return True if the transaction data was saved, false otherwise.
- L1059 _private prototype_ `bool LoadTransaction(const FString& InTransactionFilename, FStructOnScope& OutTransaction) const;` — Load and cache the transaction data for the given filename. @param InTransactionFilename		The filename to load the transaction data from. @param OutTransaction			The transaction data to populate with the result. @return True if the transaction data was loaded, false otherwise.
- L1070 _private prototype_ `bool SavePackage(const FString& InDstPackageBlobPathname, const FConcertPackageInfo& InPackageInfo, FConcertPackageDataStream& InPackageDataStream);` — Save and cache the given package data with the given filename. @param InDstPackageBlobPathname	The pathname to save the package data as. The package data may or may not be compressed. @param InPackageInfo				The package info to save. @param InPackageDataStream		The package data to save. @return True if the package data was saved, false otherwise.
- L1080 _private prototype_ `bool LoadPackage(const FString& InPackageBlobFilename, const TFunctionRef<void(FConcertPackageDataStream&)>& PackageDataStreamFn) const;` — Load the package data for the given filename. @param InPackageBlobFilename			The blob filename containing the package data to extract. @param PackageDataStreamFn			Callback invoked to let the caller stream the package data. @note The archive passed as output is only valid during the callback, its position is set at the beginning of the data (not necessarily zero) and may contain data passed the supplied size. @return True if the package data was loaded, false otherwise.
- L1083 _private member_ `FOnActivityProduced ActivityProducedEvent;` — Called when an activity is produced
- L1086 _private member_ `FString SessionPath;` — Root path to store all session data under
- L1089 _private member_ `TUniquePtr<FConcertFileCache> TransactionFileCache;` — In-memory cache of on-disk transaction files
- L1092 _private member_ `TUniquePtr<FConcertFileCache> PackageFileCache;` — In-memory cache of on-disk package files
- L1095 _private member_ `TUniquePtr<FConcertSyncSessionDatabaseStatements> Statements;` — Prepared statements for the currently open database
- L1098 _private member_ `TUniquePtr<FSQLiteDatabase> Database;` — Internal SQLite database
- L1100 _private member_ `TPimplPtr<struct FDeferredLargePackageIOImpl> DeferredLargePackageIOPtr;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API CONCERTSYNCCORE_API`
- L40 _typedef_ `using FConsumePackageActivityFunc = TFunctionRef<void(FConcertSyncActivity&& , FConcertSyncPackageEventData& )>;`
- L41 _typedef_ `using FIteratePackageActivityFunc = TFunctionRef<EBreakBehavior(FConcertSyncActivity&& , FConcertSyncPackageEventData& )>;`
- L42 _typedef_ `using FIterateActivityFunc = TFunctionRef<EBreakBehavior(FConcertSyncActivity&&)>;`
- L44 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnActivityProduced, const FConcertSyncActivity&);`
- L44 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnActivityProduced, const FConcertSyncActivity&);`
- L45 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnPackageSaved, const FName& PackageName);`
- L45 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnPackageSaved, const FName& PackageName);`
- L1103 _namespace_ `namespace UE`
- L1103 _namespace_ `namespace ConcertSyncCore` (scope `UE`)
- L1103 _namespace_ `namespace SyncDatabase` (scope `UE::ConcertSyncCore`)
- L1106 _prototype_ `FOnPackageSaved& GetOnPackageSavedDelegate();` (scope `UE::ConcertSyncCore::SyncDatabase`) — Get the global saved package delegate
- L1109 _namespace_ `namespace ConcertSyncSessionDatabaseFilterUtil`
- L1121 _prototype_ `bool TransactionEventPassesFilter(const int64 InTransactionEventId, const FConcertSessionFilter& InSessionFilter, const FConcertSyncSessionDatabase& InDatabase);` (scope `ConcertSyncSessionDatabaseFilterUtil`) — Check to see whether the transaction event with the given ID passes the given filter. @param InTransactionEventId		The ID of the transaction event to query for. @param InSessionFilter			The session filter used to query the event against. @param InDatabase				The database to query data from. @return True if the transaction event passes the filter, false otherwise.
- L1132 _prototype_ `bool PackageEventPassesFilter(const int64 InPackageEventId, const FConcertSessionFilter& InSessionFilter, const FConcertSyncSessionDatabase& InDatabase);` (scope `ConcertSyncSessionDatabaseFilterUtil`) — Check to see whether the package event with the given ID passes the given filter. @param InPackageEventId			The ID of the package event to query for. @param InSessionFilter			The session filter used to query the event against. @param InDatabase				The database to query data from. @return True if the package event passes the filter, false otherwise.

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncCore/Source/ConcertSyncCore/Public/ConcertSyncSessionFlags.h` (Public)


#### enum `EConcertSyncSessionFlags`  
`enum class EConcertSyncSessionFlags : uint32`  
_L8-68_
- L10 _public enumerator_ `None = 0`
- L17 _public enumerator_ `EnableLiveSync = 1<<0` — Enable live-syncing of data from the server to the client
- L19 _public enumerator_ `EnableConnectionHistory = 1<<1` — Enable historic connection activity tracking
- L21 _public enumerator_ `EnableLocking = 1<<2` — Enable live and historic lock activity tracking
- L23 _public enumerator_ `EnableTransactions = 1<<3` — Enable live and historic transaction activity tracking
- L25 _public enumerator_ `EnablePackages = 1<<4` — Enable live and historic package activity tracking
- L27 _public enumerator_ `EnableSequencer = 1<<5` — Enable sequencer playback tracking
- L29 _public enumerator_ `EnablePresence = 1<<6` — Enable client presence tracking
- L31 _public enumerator_ `EnableFileSharing = 1<<7` — Enable usage of file sharing to share large blobs (like package data) rather than embedding that data in message/event.
- L33 _public enumerator_ `EnableReplication = 1<<8` — Enable high-performance property replication. Clients will send data to server and the server replicates it back to other clients interested in that data.
- L40 _public enumerator_ `ShouldDiscardTransactionsOnPackageUnload = 1<<9` — Discard transactions when a package is unloaded, eg) from a content hot-reload or closing a world editor (requires EnableTransactions)
- L42 _public enumerator_ `ShouldSendTransactionSnapshots = 1<<10` — Send snapshots of multi-frame transactions (like drags) to other clients (requires EnableTransactions)
- L44 _public enumerator_ `ShouldSendPackagePristineState = 1<<11` — Send the pristine state of a package (as revision 0) before saving it for the first time (requires EnablePackages)
- L46 _public enumerator_ `ShouldSendPackageAutoSaves = 1<<12` — Send package auto-saves, in addition to user-saves (requires EnablePackages)
- L48 _public enumerator_ `ShouldUsePackageSandbox = 1<<13` — Use a sandbox to hold package writes during a session (requires EnablePackages)
- L54 _public enumerator_ `ShouldAllowGlobalMuting = 1<<14` — For Concert Replication, clients are allowed to globally mute objects. More formally, allows the use of FConcertReplication_ChangeMuteState_Requests.
- L56 _public enumerator_ `ShouldEnableReplicationActivities = 1<<15` — Whether EConcertSyncActivityEventType::Replication activities should be generated.
- L58 _public enumerator_ `ShouldEnableRemoteEditing = 1 << 16` — Whether clients are allowed to edit each other's streams & authority (via FConcertReplication_PutState_Request).
- L65 _public enumerator_ `Default_MultiUserSession = EnableLiveSync | EnableConnectionHistory | EnableLocking | EnableTransactions | EnablePackages | EnableFileSharing | EnableSequencer | EnablePresence | ShouldSendTransactionSnapshots | ShouldUsePackageSandbox | EnableReplication | ShouldAllowGlobalMuting | ShouldEnableReplicationActivities | ShouldEnableRemoteEditing` — Default settings for a multi-user session
- L67 _public enumerator_ `Default_DisasterRecoverySession = EnableTransactions | EnablePackages | EnableFileSharing | ShouldDiscardTransactionsOnPackageUnload | ShouldSendPackagePristineState | ShouldSendPackageAutoSaves` — Default settings for a disaster recovery session

#### Free symbols / members of external scopes

- L69 _prototype_ `ENUM_CLASS_FLAGS(EConcertSyncSessionFlags);`

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncCore/Source/ConcertSyncCore/Public/ConcertSyncSessionTypes.h` (Public)


#### enum `EConcertSyncConnectionEventType`  
`enum class EConcertSyncConnectionEventType : uint8`  
_L14-18_
- reflection: `UENUM()`
- desc: Types of connection events
- L16 _public enumerator_ `Connected = 0`
- L17 _public enumerator_ `Disconnected`

#### enum `EConcertSyncLockEventType`  
`enum class EConcertSyncLockEventType : uint8`  
_L22-26_
- reflection: `UENUM()`
- desc: Types of lock events
- L24 _public enumerator_ `Locked = 0`
- L25 _public enumerator_ `Unlocked`

#### enum `EConcertSyncActivityEventType`  
`enum class EConcertSyncActivityEventType : uint8`  
_L30-41_
- reflection: `UENUM()`
- desc: Types of activity events
- L32 _public enumerator_ `None = 0`
- L33 _public enumerator_ `Connection`
- L34 _public enumerator_ `Lock`
- L35 _public enumerator_ `Transaction`
- L36 _public enumerator_ `Package`
- L37 _public enumerator_ `Replication`
- L40 _public enumerator_ `Count` — ADD NEW ENTRIES ABOVE

#### enum `EConcertSyncTransactionActivitySummaryType`  
`enum class EConcertSyncTransactionActivitySummaryType : uint8`  
_L45-51_
- reflection: `UENUM()`
- desc: Type of transaction summaries
- L47 _public enumerator_ `Added`
- L48 _public enumerator_ `Updated`
- L49 _public enumerator_ `Renamed`
- L50 _public enumerator_ `Deleted`

#### struct `FConcertSyncEndpointData`  
`struct FConcertSyncEndpointData`  
_L55-62_
- reflection: `USTRUCT()`
- desc: Data for an endpoint in a Concert Sync Session
- L61 _public member_ `FConcertClientInfo ClientInfo;` — `UPROPERTY()` — The information about the Concert client connected through this endpoint

#### struct `FConcertSyncEndpointIdAndData`  
`struct FConcertSyncEndpointIdAndData`  
_L66-77_
- reflection: `USTRUCT()`
- desc: ID and data pair for an endpoint in a Concert Sync Session
- L72 _public member_ `FGuid EndpointId;` — `UPROPERTY()` — The ID of the endpoint
- L76 _public member_ `FConcertSyncEndpointData EndpointData;` — `UPROPERTY()` — The data for the endpoint

#### struct `FConcertSyncConnectionEvent`  
`struct FConcertSyncConnectionEvent`  
_L81-88_
- reflection: `USTRUCT()`
- desc: Data for a connection event in a Concert Sync Session
- L87 _public member_ `EConcertSyncConnectionEventType ConnectionEventType = EConcertSyncConnectionEventType::Connected;` — `UPROPERTY()` — The type of this connection event

#### struct `FConcertSyncLockEvent`  
`struct FConcertSyncLockEvent`  
_L92-103_
- reflection: `USTRUCT()`
- desc: Data for a lock event in a Concert Sync Session
- L98 _public member_ `EConcertSyncLockEventType LockEventType = EConcertSyncLockEventType::Locked;` — `UPROPERTY()` — The type of this lock event
- L102 _public member_ `TArray<FName> ResourceNames;` — `UPROPERTY()` — The resources affected by this lock event

#### struct `FConcertSyncTransactionEvent`  
`struct FConcertSyncTransactionEvent`  
_L107-114_
- reflection: `USTRUCT()`
- desc: Data for a transaction event in a Concert Sync Session
- L113 _public member_ `FConcertTransactionFinalizedEvent Transaction;` — `UPROPERTY()` — The transaction data for this event

#### struct `FConcertSyncPackageEvent`  
`struct FConcertSyncPackageEvent`  
_L118-129_
- reflection: `USTRUCT()`
- desc: Data for a package event in a Concert Sync Session
- L124 _public member_ `int64 PackageRevision = 0;` — `UPROPERTY()` — The revision of this package within the session?
- L128 _public member_ `FConcertPackage Package;` — `UPROPERTY()` — The package data for this event

#### struct `FConcertSyncPackageEventMetaData`  
`struct FConcertSyncPackageEventMetaData`  
_L133-144_
- reflection: `USTRUCT()`
- desc: Meta data for a package event in a Concert Sync Session.
- L139 _public member_ `int64 PackageRevision = 0;` — `UPROPERTY()` — The revision of this package within the session.
- L143 _public member_ `FConcertPackageInfo PackageInfo;` — `UPROPERTY()` — Contains information about the package event such as the package name, the event type, if this was triggered by an auto-save, etc.

#### struct `FConcertPackageDataStream`  
`struct FConcertPackageDataStream`  
_L147-157_
- desc: Used to stream the package data.
- L150 _public member_ `FArchive* DataAr = nullptr;` — The package data, positioned to read the first byte of package data, not necessarily at zero, some unrelated data can be store before. Can be null.
- L153 _public member_ `int64 DataSize = 0;` — The size of the package data. Can 0 up to several GB large. Does't necessarily extend to the end of the archive, some unrelated data can be stored after.
- L156 _public member_ `const TArray<uint8>* DataBlob = nullptr;` — An array of bytes containing the package data if the data was already available in memory, null otherwise. Can optimize few cases when available.

#### struct `FConcertSyncPackageEventData`  
`struct FConcertSyncPackageEventData`  
_L160-167_
- desc: Contains a package event where the package data is represented by a stream because it can be very large (several GB)
- L163 _public member_ `FConcertSyncPackageEventMetaData MetaData;` — The package event meta data.
- L166 _public member_ `FConcertPackageDataStream PackageDataStream;` — The package data.

#### enum `EConcertSyncActivityFlags`  
`enum class EConcertSyncActivityFlags : uint8`  
_L170-178_
- reflection: `UENUM(Flags)`
- L172 _public enumerator_ `None = 0`
- L177 _public enumerator_ `Muted = 1 << 0` — This activity will never be sent to clients by the server. For all activities a client receives (Flags & EConcertSyncActivityFlags::Muted) == EConcertSyncActivityFlags::None holds.

#### struct `FConcertSyncActivity`  
`struct FConcertSyncActivity`  
_L183-218_
- reflection: `USTRUCT()`
- desc: Data for an activity entry in a Concert Sync Session
- L189 _public member_ `int64 ActivityId = 0;` — `UPROPERTY()` — The ID of the activity
- L193 _public member_ `bool bIgnored = false;` — `UPROPERTY()` — True if this activity is included for tracking purposes only, and can be ignored when migrating a database
- L197 _public member_ `EConcertSyncActivityFlags Flags = EConcertSyncActivityFlags::None;` — `UPROPERTY()` — Additional information about this activity
- L201 _public member_ `FGuid EndpointId;` — `UPROPERTY()` — The ID of the endpoint that produced the activity
- L205 _public member_ `FDateTime EventTime = {0};` — `UPROPERTY()` — The time at which the activity was produced (UTC)
- L209 _public member_ `EConcertSyncActivityEventType EventType = EConcertSyncActivityEventType::None;` — `UPROPERTY()` — The type of this activity
- L213 _public member_ `int64 EventId = 0;` — `UPROPERTY()` — The ID of the event associated with this activity (@see EventType to work out how to resolve this)
- L217 _public member_ `FConcertSessionSerializedPayload EventSummary{EConcertPayloadSerializationMethod::Cbor};` — `UPROPERTY()` — The minimal summary of the event associated with this activity (@see FConcertSyncActivitySummary)

#### struct `FConcertSyncConnectionActivity`  
`struct FConcertSyncConnectionActivity : public FConcertSyncActivity`  
_L222-234_
- reflection: `USTRUCT()`
- inherits: `FConcertSyncActivity`
- desc: Data for a connection activity entry in a Concert Sync Session
- L226 _public function_ `FConcertSyncConnectionActivity()`
- L233 _public member_ `FConcertSyncConnectionEvent EventData;` — `UPROPERTY()` — The connection event data associated with this activity

#### struct `FConcertSyncLockActivity`  
`struct FConcertSyncLockActivity : public FConcertSyncActivity`  
_L238-250_
- reflection: `USTRUCT()`
- inherits: `FConcertSyncActivity`
- desc: Data for a lock activity entry in a Concert Sync Session
- L242 _public function_ `FConcertSyncLockActivity()`
- L249 _public member_ `FConcertSyncLockEvent EventData;` — `UPROPERTY()` — The lock event data associated with this activity

#### struct `FConcertSyncTransactionActivity`  
`struct FConcertSyncTransactionActivity : public FConcertSyncActivity`  
_L254-266_
- reflection: `USTRUCT()`
- inherits: `FConcertSyncActivity`
- desc: Data for a transaction activity entry in a Concert Sync Session
- L258 _public function_ `FConcertSyncTransactionActivity()`
- L265 _public member_ `FConcertSyncTransactionEvent EventData;` — `UPROPERTY()` — The transaction event data associated with this activity

#### struct `FConcertSyncPackageActivity`  
`struct FConcertSyncPackageActivity : public FConcertSyncActivity`  
_L270-282_
- reflection: `USTRUCT()`
- inherits: `FConcertSyncActivity`
- desc: Data for a package activity entry in a Concert Sync Session
- L274 _public function_ `FConcertSyncPackageActivity()`
- L281 _public member_ `FConcertSyncPackageEvent EventData;` — `UPROPERTY()` — The package event data associated with this activity

#### struct `FConcertSyncActivitySummary`  
`struct FConcertSyncActivitySummary`  
_L286-304_
- reflection: `USTRUCT()`
- desc: Base summary for an activity entry in a Concert Sync Session
- L290 _public prototype_ `virtual ~FConcertSyncActivitySummary() = default;`
- L299 _public prototype_ `FText ToDisplayText(const FText InUserDisplayName, const bool InUseRichText = false) const;` — Get the display text of the activity summary. @param InUserDisplayName		The display name of the user the activity belongs to, or an empty text to skip the user information. @param InUseRichText			True if the output should be suitable for consumption as rich-text, or false for plain-text.
- L302 _protected prototype_ `virtual FText CreateDisplayText(const bool InUseRichText) const;`
- L303 _protected prototype_ `virtual FText CreateDisplayTextForUser(const FText InUserDisplayName, const bool InUseRichText) const;`

#### struct `FConcertSyncConnectionActivitySummary`  
`struct FConcertSyncConnectionActivitySummary : public FConcertSyncActivitySummary`  
_L308-323_
- reflection: `USTRUCT()`
- inherits: `FConcertSyncActivitySummary`
- desc: Summary for a connection activity entry in a Concert Sync Session
- L314 _public member_ `EConcertSyncConnectionEventType ConnectionEventType = EConcertSyncConnectionEventType::Connected;` — `UPROPERTY()` — The type of connection event we summarize
- L317 _public prototype_ `static FConcertSyncConnectionActivitySummary CreateSummaryForEvent(const FConcertSyncConnectionEvent& InEvent);` — Create this summary from an connection event
- L321 _protected prototype_ `virtual FText CreateDisplayText(const bool InUseRichText) const override;`
- L322 _protected prototype_ `virtual FText CreateDisplayTextForUser(const FText InUserDisplayName, const bool InUseRichText) const override;`

#### struct `FConcertSyncLockActivitySummary`  
`struct FConcertSyncLockActivitySummary : public FConcertSyncActivitySummary`  
_L327-354_
- reflection: `USTRUCT()`
- inherits: `FConcertSyncActivitySummary`
- desc: Summary for a lock activity entry in a Concert Sync Session
- L333 _public member_ `EConcertSyncLockEventType LockEventType = EConcertSyncLockEventType::Locked;` — `UPROPERTY()` — The type of lock event we summarize
- L337 _public member_ `FName PrimaryResourceName;` — `UPROPERTY()` — The primary resource affected by the lock event we summarize
- L341 _public member_ `FName PrimaryPackageName;` — `UPROPERTY()` — The primary package affected by the lock event we summarize
- L345 _public member_ `int32 NumResources = 0;` — `UPROPERTY()` — The total number of resources affected by the lock event we summarize
- L348 _public prototype_ `static FConcertSyncLockActivitySummary CreateSummaryForEvent(const FConcertSyncLockEvent& InEvent);` — Create this summary from a lock event
- L352 _protected prototype_ `virtual FText CreateDisplayText(const bool InUseRichText) const override;`
- L353 _protected prototype_ `virtual FText CreateDisplayTextForUser(const FText InUserDisplayName, const bool InUseRichText) const override;`

#### struct `FConcertSyncTransactionActivitySummary`  
`struct FConcertSyncTransactionActivitySummary : public FConcertSyncActivitySummary`  
_L358-393_
- reflection: `USTRUCT()`
- inherits: `FConcertSyncActivitySummary`
- desc: Summary for a transaction activity entry in a Concert Sync Session
- L364 _public member_ `EConcertSyncTransactionActivitySummaryType TransactionSummaryType = EConcertSyncTransactionActivitySummaryType::Updated;` — `UPROPERTY()` — The type of summary that the transaction event we summarize produced
- L368 _public member_ `FText TransactionTitle;` — `UPROPERTY()` — The title of transaction in the transaction event we summarize
- L372 _public member_ `FName PrimaryObjectName;` — `UPROPERTY()` — The primary object affected by the transaction event we summarize
- L376 _public member_ `FName PrimaryPackageName;` — `UPROPERTY()` — The primary package affected by the transaction event we summarize
- L380 _public member_ `FName NewObjectName;` — `UPROPERTY()` — The new object name for the event we summarize (if TransactionSummaryType == EConcertSyncTransactionActivitySummaryType::Renamed)
- L384 _public member_ `int32 NumActions = 0;` — `UPROPERTY()` — The total number of actions created by the transaction event we summarize
- L387 _public prototype_ `static FConcertSyncTransactionActivitySummary CreateSummaryForEvent(const FConcertSyncTransactionEvent& InEvent);` — Create this summary from a transaction event
- L391 _protected prototype_ `virtual FText CreateDisplayText(const bool InUseRichText) const override;`
- L392 _protected prototype_ `virtual FText CreateDisplayTextForUser(const FText InUserDisplayName, const bool InUseRichText) const override;`

#### struct `FConcertSyncPackageActivitySummary`  
`struct FConcertSyncPackageActivitySummary : public FConcertSyncActivitySummary`  
_L397-428_
- reflection: `USTRUCT()`
- inherits: `FConcertSyncActivitySummary`
- desc: Summary for a package activity entry in a Concert Sync Session
- L403 _public member_ `FName PackageName;` — `UPROPERTY()` — The package affected by the package event we summarize
- L407 _public member_ `FName NewPackageName;` — `UPROPERTY()` — The new package name for the event we summarize (if PackageUpdateType == EConcertPackageUpdateType::Renamed)
- L411 _public member_ `EConcertPackageUpdateType PackageUpdateType = EConcertPackageUpdateType::Dummy;` — `UPROPERTY()` — The type of package update we summarize
- L415 _public member_ `bool bAutoSave = false;` — `UPROPERTY()` — Are we summarizing an auto-save update?
- L419 _public member_ `bool bPreSave = false;` — `UPROPERTY()` — Are we summarizing a pre-save update?
- L422 _public prototype_ `static FConcertSyncPackageActivitySummary CreateSummaryForEvent(const FConcertPackageInfo& InEvent);` — Create this summary from a package event
- L426 _protected prototype_ `virtual FText CreateDisplayText(const bool InUseRichText) const override;`
- L427 _protected prototype_ `virtual FText CreateDisplayTextForUser(const FText InUserDisplayName, const bool InUseRichText) const override;`

#### struct `FConcertSessionActivity`  
`struct FConcertSessionActivity`  
_L430-462_
- L432 _public prototype_ `FConcertSessionActivity() = default;`
- L434 _public function_ `FConcertSessionActivity(const FConcertSyncActivity& InActivity, const FStructOnScope& InActivitySummary, TUniquePtr<FConcertSessionSerializedPayload> OptionalEventPayload = nullptr) : Activity(InActivity) , EventPayload(MoveTemp(OptionalEventPayload))`
- L441 _public function_ `FConcertSessionActivity(FConcertSyncActivity&& InActivity, FStructOnScope&& InActivitySummary, TUniquePtr<FConcertSessionSerializedPayload> OptionalEventPayload = nullptr) : Activity(MoveTemp(InActivity)) , EventPayload(MoveTemp(OptionalEventPayload))`
- L449 _public member_ `FConcertSyncActivity Activity;` — The generic activity part.
- L452 _public member_ `TStructOnScope<FConcertSyncActivitySummary> ActivitySummary;` — Contains the activity summary to display as text.
- L461 _public member_ `TUniquePtr<FConcertSessionSerializedPayload> EventPayload;` — The activity event payload usable for activity inspection. Might be null if it was not requested or did not provide insightful information. - If the activity type is 'transaction' and EventPayload is not null, it contains a FConcertSyncTransactionEvent with full transaction data. - If the activity type is 'package' and EventPayload is not null, it contains a FConcertSyncPackageEvent with the package meta data only. - Not set for other activity types (connection/lock). @see FConcertActivityStream

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API CONCERTSYNCCORE_API`

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncCore/Source/ConcertSyncCore/Public/ConcertSyncSettings.h` (Public)


#### struct `FTransactionClassFilter`  
`struct FTransactionClassFilter`  
_L11-26_
- reflection: `USTRUCT()`
- L19 _public member_ `FSoftClassPath ObjectOuterClass;` — `UPROPERTY(config, EditAnywhere, Category="Sync Settings")` — Optional Outer Class that will allow object only if one of their outer match this class.
- L25 _public member_ `TArray<FSoftClassPath> ObjectClasses;` — `UPROPERTY(config, EditAnywhere, Category = "Sync Settings")` — Object classes to filter transaction object on.

#### struct `FPackageClassFilter`  
`struct FPackageClassFilter`  
_L29-44_
- reflection: `USTRUCT()`
- L37 _public member_ `FSoftClassPath AssetClass;` — `UPROPERTY(config, EditAnywhere, Category = "Sync Settings")` — Optional Class that will filter a specific asset type.
- L43 _public member_ `TArray<FString> ContentPaths;` — `UPROPERTY(config, EditAnywhere, Category = "Sync Settings")` — Paths on which package of a certain asset type will pass the filter, if no asset is specified all asset in those paths pass the filter

#### enum `EShowPresenceInGame`  
`enum class EShowPresenceInGame`  
_L47-57_
- reflection: `UENUM()`
- L50 _public enumerator_ `NotVisibleInGame` — The presence actor is not visible in game mode.
- L53 _public enumerator_ `VisibleInGameOnlyEditor` — The presence actor is visible in game only in editor sessions.
- L56 _public enumerator_ `VisibleInGameAlways` — The presence actor is always visible in game including -game modes. This is equivalent to Concert.EnablePresenceInGame

#### class `UConcertSyncConfig`  
`class UConcertSyncConfig : public UObject`  
_L60-151_
- reflection: `UCLASS(MinimalAPI, config=ConcertSyncCore)`
- inherits: `UObject`
- L65 _public function_ `UConcertSyncConfig() : bInteractiveHotReload(false) , bShowPresenceInPIE(true) , bIncludeAnnotationObjectChanges(true) , SnapshotTransactionsPerSecond(30.0f)`
- L73 _public function_ `static UConcertSyncConfig* Get()` — @return The global settings objects.
- L80 _public member_ `bool bInteractiveHotReload;` — `UPROPERTY(config, EditAnywhere, AdvancedDisplay, Category="Transaction Settings")` — Should we ask before hot-reloading changed packages? If disabled we will clobber any local changes when reloading packages.
- L86 _public member_ `bool bShowPresenceInPIE;` — `UPROPERTY(config, EditAnywhere, AdvancedDisplay, Category="Transaction Settings")` — Should we show presence when in PIE?
- L92 _public member_ `EShowPresenceInGame ShowPresenceInGame = EShowPresenceInGame::NotVisibleInGame;` — `UPROPERTY(config, EditAnywhere, AdvancedDisplay, Category="Transaction Settings")` — Should we show presence when we are in game mode when running the editor.
- L99 _public member_ `bool bIncludeAnnotationObjectChanges;` — `UPROPERTY(config, EditAnywhere, AdvancedDisplay, Category="Transaction Settings")` — Should we include object changes that have been generated via a transaction annotation (where possible), or should we send the entire transaction annotation blob instead.
- L105 _public member_ `float SnapshotTransactionsPerSecond;` — `UPROPERTY(config, EditAnywhere, Category="Transaction Settings", meta=(ClampMin="1", UIMin="1"))` — Number of snapshot transactions (eg, moving an object or dragging a slider) that should be sent per-second to other clients.
- L113 _public member_ `TArray<FTransactionClassFilter> IncludeObjectClassFilters;` — `UPROPERTY(config, EditAnywhere, Category="Transaction Settings")` — Array of Transaction class filter. Only objects that pass those filters will be included in transaction updates. @note If this is empty, then all class types will send transaction updates.
- L121 _public member_ `TArray<FTransactionClassFilter> ExcludeTransactionClassFilters;` — `UPROPERTY(config, EditAnywhere, Category = "Transaction Settings")` — Array of additional Transaction class filter. Objects that matches those filters, will prevent the whole transaction from propagation. @note These filters takes precedence over the IncludeObjectClassFilters
- L127 _public member_ `TArray<TFieldPath<FProperty>> AllowedTransientProperties;` — `UPROPERTY(config, EditAnywhere, Category="Transaction Settings", meta=(AllowedClasses="/Script/CoreUObject.Property"))` — Array of transient class properties that we should send transaction updates for even if usually filtered out.
- L133 _public member_ `TArray<TFieldPath<FProperty>> ExcludedProperties;` — `UPROPERTY(config, EditAnywhere, Category="Transaction Settings", meta=(AllowedClasses="/Script/CoreUObject.Property"))` — Array of class properties that we should filtered out.
- L139 _public member_ `TArray<FName> ExcludedPropertyTypes;` — `UPROPERTY(config, EditAnywhere, Category="Transaction Settings")` — Array of property types that we should filtered out.
- L146 _public member_ `TArray<FPackageClassFilter> ExcludePackageClassFilters;` — `UPROPERTY(config, EditAnywhere, Category = "Package Settings")` — Array of package class filter. Packages that matches those filters, will be excluded from propagating to the server when saved.
- L150 _public member_ `TArray<FConcertReplicationActionEntry> PostReplicateActions;` — `UPROPERTY(Config, EditAnywhere, Category = "Actions")` — Defines actions that are to be executed after certain properties are replicated, such as calling PostEditChange, etc.

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncCore/Source/ConcertSyncCore/Public/ConcertTransactionEvents.h` (Public)


#### enum `ETransactionFilterResult`  
`enum class ETransactionFilterResult : uint8`  
_L10-20_
- reflection: `UENUM()`
- L13 _public enumerator_ `IncludeObject` — Include the object in the Concert Transaction
- L15 _public enumerator_ `ExcludeObject` — Filter the object from the Concert Transaction
- L17 _public enumerator_ `ExcludeTransaction` — Filter the entire transaction and prevent propagation
- L19 _public enumerator_ `UseDefault` — Delegate the filtering decision to the default handlers.

#### struct `FConcertObjectId`  
`struct FConcertObjectId`  
_L23-91_
- reflection: `USTRUCT()`
- L27 _public prototype_ `FConcertObjectId() = default;`
- L29 _public function_ `explicit FConcertObjectId(const UObject* InObject) : FConcertObjectId(FTransactionObjectId(InObject), InObject->GetFlags())`
- L34 _public function_ `FConcertObjectId(const FTransactionObjectId& InObjectId, const uint32 InObjectFlags) : FConcertObjectId(InObjectId.ObjectClassPathName, InObjectId.ObjectPackageName, InObjectId.ObjectName, InObjectId.ObjectOuterPathName, InObjectId.ObjectExternalPackageName, InObjectFlags)`
- L39 _public function_ `FConcertObjectId(const FName InObjectClassPathName, const FName InObjectPackageName, const FName InObjectName, const FName InObjectOuterPathName, const FName InObjectExternalPackageName, const uint32 InObjectFlags) : ObjectClassPathName(InObjectClassPathName) , ObjectPackageName(InObjectPackageName) , ObjectName(InObjectName) , ObjectOuterPathName(InObjectOuterPathName) , ObjectExternalPackageName(InObjectExternalPackageName) , ObjectPersistentFlags(InObjectFlags & RF_Load)`
- L49 _public function_ `FTransactionObjectId ToTransactionObjectId() const`
- L69 _public function_ `bool IsValid() const`
- L75 _public member_ `FName ObjectClassPathName;` — `UPROPERTY()`
- L78 _public member_ `FName ObjectPackageName;` — `UPROPERTY()`
- L81 _public member_ `FName ObjectName;` — `UPROPERTY()`
- L84 _public member_ `FName ObjectOuterPathName;` — `UPROPERTY()`
- L87 _public member_ `FName ObjectExternalPackageName;` — `UPROPERTY()`
- L90 _public member_ `uint32 ObjectPersistentFlags = 0;` — `UPROPERTY()`

#### struct `FConcertSerializedObjectData`  
`struct FConcertSerializedObjectData`  
_L106-136_
- reflection: `USTRUCT()`
- L111 _public member_ `bool bAllowCreate = false;` — `UPROPERTY()`
- L114 _public member_ `bool bResetExisting = false;` — `UPROPERTY()`
- L117 _public member_ `bool bIsPendingKill = false;` — `UPROPERTY()`
- L120 _public member_ `FName NewPackageName;` — `UPROPERTY()`
- L123 _public member_ `FName NewName;` — `UPROPERTY()`
- L126 _public member_ `FName NewOuterPathName;` — `UPROPERTY()`
- L129 _public member_ `FName NewExternalPackageName;` — `UPROPERTY()`
- L132 _public member_ `FSoftObjectPath SourceObject;` — `UPROPERTY()`
- L135 _public member_ `TArray<uint8> SerializedData;` — `UPROPERTY()`

#### struct `FConcertSerializedPropertyData`  
`struct FConcertSerializedPropertyData`  
_L139-148_
- reflection: `USTRUCT()`
- L144 _public member_ `FName PropertyName;` — `UPROPERTY()`
- L147 _public member_ `TArray<uint8> SerializedData;` — `UPROPERTY()`

#### struct `FConcertExportedObject`  
`struct FConcertExportedObject`  
_L151-172_
- reflection: `USTRUCT()`
- L156 _public member_ `FConcertObjectId ObjectId;` — `UPROPERTY()`
- L159 _public member_ `int32 ObjectPathDepth = 0;` — `UPROPERTY()`
- L162 _public member_ `bool bHasLevelInstanceObject = false;` — `UPROPERTY()`
- L165 _public member_ `FConcertSerializedObjectData ObjectData;` — `UPROPERTY()`
- L168 _public member_ `TArray<FConcertSerializedPropertyData> PropertyDatas;` — `UPROPERTY()`
- L171 _public member_ `TArray<uint8> SerializedAnnotationData;` — `UPROPERTY()`

#### struct `FConcertTransactionEventBase`  
`struct FConcertTransactionEventBase`  
_L175-202_
- reflection: `USTRUCT()`
- L180 _public member_ `FGuid TransactionId;` — `UPROPERTY()`
- L183 _public member_ `FGuid OperationId;` — `UPROPERTY()`
- L186 _public member_ `FGuid TransactionEndpointId;` — `UPROPERTY()`
- L189 _public member_ `uint8 TransactionUpdateIndex = 0;` — `UPROPERTY()`
- L192 _public member_ `int32 VersionIndex = INDEX_NONE;` — `UPROPERTY()`
- L195 _public member_ `TArray<FName> ModifiedPackages;` — `UPROPERTY()`
- L198 _public member_ `FConcertObjectId PrimaryObjectId;` — `UPROPERTY()`
- L201 _public member_ `TArray<FConcertExportedObject> ExportedObjects;` — `UPROPERTY()`

#### struct `FConcertTransactionFinalizedEvent`  
`struct FConcertTransactionFinalizedEvent : public FConcertTransactionEventBase`  
_L205-214_
- reflection: `USTRUCT()`
- inherits: `FConcertTransactionEventBase`
- L210 _public member_ `FConcertLocalIdentifierState LocalIdentifierState;` — `UPROPERTY()`
- L213 _public member_ `FText Title;` — `UPROPERTY()`

#### struct `FConcertTransactionSnapshotEvent`  
`struct FConcertTransactionSnapshotEvent : public FConcertTransactionEventBase`  
_L217-220_
- reflection: `USTRUCT()`
- inherits: `FConcertTransactionEventBase`

#### struct `FConcertTransactionRejectedEvent`  
`struct FConcertTransactionRejectedEvent`  
_L223-229_
- reflection: `USTRUCT()`
- L228 _public member_ `FGuid TransactionId;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L93 _function_ `inline bool operator ==(const FConcertObjectId& A, const FConcertObjectId& B)`
- L100 _function_ `inline uint32 GetTypeHash(const FConcertObjectId& ConcertObjectId)`

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncCore/Source/ConcertSyncCore/Public/ConcertWorkspaceData.h` (Public)


#### enum `EConcertPackageUpdateType`  
`enum class EConcertPackageUpdateType : uint8`  
_L9-23_
- reflection: `UENUM()`
- L12 _public enumerator_ `Dummy` — A dummy update, typically used to fence some transactions as no longer relevant
- L14 _public enumerator_ `Added` — This package has been added, but not yet saved
- L16 _public enumerator_ `Saved` — This package has been saved
- L18 _public enumerator_ `Renamed` — This package has been renamed (leaving a redirector)
- L20 _public enumerator_ `Deleted` — This package has been deleted
- L22 _public enumerator_ `Count`

#### struct `FConcertPackageInfo`  
`struct FConcertPackageInfo`  
_L26-71_
- reflection: `USTRUCT()`
- L32 _public member_ `FName PackageName;` — `UPROPERTY()` — The name of the package
- L36 _public member_ `FName NewPackageName;` — `UPROPERTY()` — The new name of the package (if PackageUpdateType == EConcertPackageUpdateType::Renamed)
- L40 _public member_ `FString AssetClass;` — `UPROPERTY()` — The class of the asset contained in this package.
- L44 _public member_ `FString PackageFileExtension;` — `UPROPERTY()` — The extension of the package file on disk (eg, .umap or .uasset)
- L48 _public member_ `EConcertPackageUpdateType PackageUpdateType = EConcertPackageUpdateType::Dummy;` — `UPROPERTY()` — What kind of package update is this?
- L52 _public member_ `int64 TransactionEventIdAtSave = 0;` — `UPROPERTY()` — What was the max transaction event ID when this update was made? (to discard older transactions that applied to this package)
- L56 _public member_ `bool bPreSave = false;` — `UPROPERTY()` — Was this update caused by a pre-save?
- L60 _public member_ `bool bAutoSave = false;` — `UPROPERTY()` — Was this update caused by an auto-save?
- L70 _public member_ `bool bCanSkipHotReload = false;` — `UPROPERTY()` — Can we skip hot reload on this package? Hot reload is required to update changes to a loaded asset to a newer versoin modified in a multi-user session.  Take recordings are packages that do not need to go through hot reload as they have no live assets. This flag can be set to true to indicate to the replay system the package can bypass hot reload. @see IConcertClientClientPackageBridge::RegisterPackageHotReloadHint

#### struct `FConcertPackage`  
`struct FConcertPackage`  
_L74-114_
- reflection: `USTRUCT()`
- L80 _public member_ `FConcertPackageInfo Info;` — `UPROPERTY()` — Contains information about the package event such as the package name, the event type, if this was triggered by an auto-save, etc.
- L84 _public member_ `FConcertByteArray PackageData;` — `UPROPERTY()` — Contains the package data, unless the package size was too large (according to the hard limit or a configuration).
- L88 _public member_ `FString FileId;` — `UPROPERTY()` — A link to a file containing the data if the package size was too large to be directly embedded. The package data needs to be retrieved using IConcertFileSharingService interface.
- L91 _public function_ `bool HasPackageData() const` — Whether some package data is embedded or linked.
- L97 _public function_ `static bool ShouldEmbedPackageDataAsByteArray(uint64 PackageDataSize)` — Whether the package data should be embedded in 'PackageData'. Larger packages could still be embedded as byte array if file sharing is not enabled.
- L103 _public function_ `static bool CanEmbedPackageDataAsByteArray(uint64 PackageDataSize)` — Whether the package data can safely be embedded in 'PackageData' without overflow (ex 3GB overflows int32 type). Not necessarily reasonable, but safe.
- L109 _public function_ `static constexpr uint64 GetMaxPackageDataSizeEmbeddableAsByteArray()` — The maximum package data size that can be safely embedded in 'PackageData'. (Not necessarily reasonable, but safe).

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncCore/Source/ConcertSyncCore/Public/ConcertWorkspaceMessages.h` (Public)


#### struct `FConcertWorkspaceSyncEventBase`  
`struct FConcertWorkspaceSyncEventBase`  
_L9-15_
- reflection: `USTRUCT()`
- L14 _public member_ `int32 NumRemainingSyncEvents = 0;` — `UPROPERTY()`

#### struct `FConcertWorkspaceSyncEndpointEvent`  
`struct FConcertWorkspaceSyncEndpointEvent : public FConcertWorkspaceSyncEventBase`  
_L18-24_
- reflection: `USTRUCT()`
- inherits: `FConcertWorkspaceSyncEventBase`
- L23 _public member_ `FConcertSyncEndpointIdAndData Endpoint;` — `UPROPERTY()`

#### struct `FConcertWorkspaceSyncActivityEvent`  
`struct FConcertWorkspaceSyncActivityEvent : public FConcertWorkspaceSyncEventBase`  
_L27-33_
- reflection: `USTRUCT()`
- inherits: `FConcertWorkspaceSyncEventBase`
- L32 _public member_ `FConcertSessionSerializedPayload Activity;` — `UPROPERTY()`

#### struct `FConcertWorkspaceSyncLockEvent`  
`struct FConcertWorkspaceSyncLockEvent : public FConcertWorkspaceSyncEventBase`  
_L36-42_
- reflection: `USTRUCT()`
- inherits: `FConcertWorkspaceSyncEventBase`
- L41 _public member_ `TMap<FName, FGuid> LockedResources;` — `UPROPERTY()`

#### struct `FConcertWorkspaceSyncRequestedEvent`  
`struct FConcertWorkspaceSyncRequestedEvent`  
_L45-60_
- reflection: `USTRUCT()`
- L51 _public member_ `int64 FirstActivityIdToSync = 1;` — `UPROPERTY()` — The ID of the first activity to sync
- L55 _public member_ `int64 LastActivityIdToSync = MAX_int64;` — `UPROPERTY()` — The ID of the last activity to sync (ignored if bEnableLiveSync is true)
- L59 _public member_ `bool bEnableLiveSync = true;` — `UPROPERTY()` — True if the server workspace should be live-synced to this client as new activity is added, or false if syncing should only happen in response to these sync request events

#### struct `FConcertWorkspaceSyncCompletedEvent`  
`struct FConcertWorkspaceSyncCompletedEvent`  
_L63-66_
- reflection: `USTRUCT()`

#### struct `FConcertWorkspaceSyncAndFinalizeCompletedEvent`  
`struct FConcertWorkspaceSyncAndFinalizeCompletedEvent`  
_L70-73_
- reflection: `USTRUCT()`
- desc: An event emitted by a client after its workspace has been completely synced and finalized. All transactions are posted and packages have been loaded.

#### struct `FConcertSyncEventRequest`  
`struct FConcertSyncEventRequest`  
_L77-88_
- reflection: `USTRUCT()`
- desc: Request to sync an event that was partially synced on the client but for which the full data is required for inspection. FConcertSyncEventResponse is the corresponding response.
- L83 _public member_ `EConcertSyncActivityEventType EventType = EConcertSyncActivityEventType::None;` — `UPROPERTY()` — The type of event to sync. Only Package and Transaction event types are supported.
- L87 _public member_ `int64 EventId = 0;` — `UPROPERTY()` — The ID of the event to sync.

#### struct `FConcertSyncEventResponse`  
`struct FConcertSyncEventResponse`  
_L92-99_
- reflection: `USTRUCT()`
- desc: Response to a FConcertSyncEventRequest request.
- L98 _public member_ `FConcertSessionSerializedPayload Event;` — `UPROPERTY()` — The payload contains the event corresponding to the requested event type like FConcertSyncTransactionEvent/FConcertSyncPackageEvent or an empty payload if the request failed.

#### struct `FConcertServerLogging`  
`struct FConcertServerLogging`  
_L102-108_
- reflection: `USTRUCT()`
- L107 _public member_ `bool bLoggingEnabled = false;` — `UPROPERTY()`

#### struct `FConcertPackageTransmissionStartEvent`  
`struct FConcertPackageTransmissionStartEvent`  
_L112-124_
- reflection: `USTRUCT()`
- desc: Sent to let the receiver know something is coming. For now only sent from client to server.
- L117 _public member_ `FGuid TransmissionId;` — `UPROPERTY()`
- L120 _public member_ `FConcertPackageInfo PackageInfo;` — `UPROPERTY()`
- L123 _public member_ `uint64 PackageNumBytes = 0;` — `UPROPERTY()`

#### struct `FConcertPackageUpdateEvent`  
`struct FConcertPackageUpdateEvent`  
_L128-137_
- reflection: `USTRUCT()`
- L133 _public member_ `FGuid TransmissionId;` — `UPROPERTY()`
- L136 _public member_ `FConcertPackage Package;` — `UPROPERTY()`

#### struct `FConcertPackageRejectedEvent`  
`struct FConcertPackageRejectedEvent`  
_L140-146_
- reflection: `USTRUCT()`
- L145 _public member_ `FName PackageName;` — `UPROPERTY()`

#### enum `EConcertResourceLockType`  
`enum class EConcertResourceLockType : uint8`  
_L149-154_
- reflection: `UENUM()`
- L151 _public enumerator_ `None`
- L152 _public enumerator_ `Lock`
- L153 _public enumerator_ `Unlock`

#### struct `FConcertResourceLockEvent`  
`struct FConcertResourceLockEvent`  
_L157-169_
- reflection: `USTRUCT()`
- L162 _public member_ `FGuid ClientId;` — `UPROPERTY()`
- L165 _public member_ `TArray<FName> ResourceNames;` — `UPROPERTY()`
- L168 _public member_ `EConcertResourceLockType LockType = EConcertResourceLockType::None;` — `UPROPERTY()`

#### struct `FConcertResourceLockRequest`  
`struct FConcertResourceLockRequest`  
_L172-184_
- reflection: `USTRUCT()`
- L177 _public member_ `FGuid ClientId;` — `UPROPERTY()`
- L180 _public member_ `TArray<FName> ResourceNames;` — `UPROPERTY()`
- L183 _public member_ `EConcertResourceLockType LockType = EConcertResourceLockType::None;` — `UPROPERTY()`

#### struct `FConcertResourceLockResponse`  
`struct FConcertResourceLockResponse`  
_L187-196_
- reflection: `USTRUCT()`
- L192 _public member_ `TMap<FName, FGuid> FailedResources;` — `UPROPERTY()`
- L195 _public member_ `EConcertResourceLockType LockType = EConcertResourceLockType::None;` — `UPROPERTY()`

#### enum `EConcertPlaySessionEventType`  
`enum class EConcertPlaySessionEventType : uint8`  
_L199-205_
- reflection: `UENUM()`
- L201 _public enumerator_ `None`
- L202 _public enumerator_ `BeginPlay`
- L203 _public enumerator_ `SwitchPlay`
- L204 _public enumerator_ `EndPlay`

#### struct `FConcertPlaySessionEvent`  
`struct FConcertPlaySessionEvent`  
_L208-223_
- reflection: `USTRUCT()`
- L213 _public member_ `EConcertPlaySessionEventType EventType = EConcertPlaySessionEventType::None;` — `UPROPERTY()`
- L216 _public member_ `FGuid PlayEndpointId;` — `UPROPERTY()`
- L219 _public member_ `FName PlayPackageName;` — `UPROPERTY()`
- L222 _public member_ `bool bIsSimulating = false;` — `UPROPERTY()`

#### struct `FConcertIgnoreActivityStateChangedEvent`  
`struct FConcertIgnoreActivityStateChangedEvent`  
_L231-240_
- reflection: `USTRUCT()`
- desc: Sets the specified client 'ignore on restore' state for further activities. The 'ignored' flag can be raised to mark a series of activities as 'should not be restored'. @note This can be used to record and monitor session activities for inspection purpose, for example allowing disaster recovery to record what happens in a multi-user session without restoring such activities in case of crash (because they occurred in a transient sandbox).
- L236 _public member_ `FGuid EndpointId;` — `UPROPERTY()`
- L239 _public member_ `bool bIgnore = false;` — `UPROPERTY()`

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncCore/Source/ConcertSyncCore/Public/HistoryEdition/ActivityDependencyEdge.h` (Public)


#### enum `UE::ConcertSyncCore::EActivityDependencyReason`  
`enum class EActivityDependencyReason`  
_L13-76_
- desc: Describes why there is a dependency
- L21 _public enumerator_ `PackageCreation` — The depended-on activity created the package that this activity operates on. Example: 1: Create level > 2: Add actor 2 cannot take place without 1.
- L29 _public enumerator_ `PackageRemoval` — The depended-on activity deleted a package with the same path name of the package this activity created. Example: 1: Delete level Game/Foo 2: Create new level Game/Foo. 2 cannot take place without 1.
- L40 _public enumerator_ `PackageRename` — The depended-on activity renamed a package that is used by this activity. Example: 1: Create level 'Foo' > 2: Rename 'Foo' to 'Bar' > 3: Edit actor 3 depends on 2. Example: 1: Create level 'Foo' > 2: Rename 'Foo' to 'Bar' > 3: Create level 'Foo' 3 depends on 1.
- L48 _public enumerator_ `PackageEdited` — The depended-on activity edits the package that is required by this activity. Example: 1: Move actor 2: Save level 2 depends on 1 (because the save operation would save different data if 1 was not performed).
- L56 _public enumerator_ `EditAfterPreviousPackageEdit` — The depended-on activity changes the state of a package that is depended on by a package this activity modifies. Example: 1: Edit actor to reference data asset 2: Edit data asset 3: Edit actor, triggering the construction script. 3 executes the construction script which may execute differently depending on the data changed in 2.
- L64 _public enumerator_ `SubobjectCreation` — The depended-on activity created a subobject that this activity operates on. Example: 1: Add actor > 2. Edit actor 2 cannot take place without 1.
- L72 _public enumerator_ `SubobjectRemoval` — The depended-on activity removed a subobject that this activity requires to be dead. Example: 1: Remove actor > 2. Create actor with same name 2 cannot take place without 1.
- L75 _public enumerator_ `Count` — ADD BEFORE THIS ENTRY

#### enum `UE::ConcertSyncCore::EDependencyStrength`  
`enum class EDependencyStrength`  
_L80-94_
- L86 _public enumerator_ `HardDependency` — An activity A has a hard dependency to activity B when A cannot exist in an activity history without B. Example: You create a level and add an actor to it. You cannot create the actor without the level.
- L93 _public enumerator_ `PossibleDependency` — An activity A has a possible dependency to activity B when A could possibly exist without B but we cannot rule out that B does not affect A. Example: You modify an actor twice each time triggering the construction script

#### class `UE::ConcertSyncCore::FActivityDependencyEdge`  
`class FActivityDependencyEdge`  
_L98-133_
- desc: Describes a dependency from one activity to an earlier activity.
- L102 _public function_ `FActivityDependencyEdge(FActivityNodeID DependedOnActivityNode, EActivityDependencyReason DependencyReason, EDependencyStrength DependencyStrength) : Parent(DependedOnActivityNode) , DependencyReason(DependencyReason) , DependencyStrength(DependencyStrength)`
- L108 _public function_ `FActivityNodeID GetDependedOnNodeID() const`
- L109 _public function_ `EActivityDependencyReason GetDependencyReason() const`
- L110 _public function_ `EDependencyStrength GetDependencyStrength() const`
- L126 _private member_ `const FActivityNodeID Parent;` — The node that an activity depends on
- L129 _private member_ `const EActivityDependencyReason DependencyReason;` — Why this dependency exists
- L132 _private member_ `const EDependencyStrength DependencyStrength;` — How much the activity is depended on

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace ConcertSyncCore` (scope `UE`)
- L78 _prototype_ `FString LexToString(EActivityDependencyReason Reason);` (scope `UE::ConcertSyncCore`)
- L112 _function_ `friend bool operator==(const FActivityDependencyEdge& Left, const FActivityDependencyEdge& Right)` (scope `UE::ConcertSyncCore`)
- L118 _function_ `friend bool operator!=(const FActivityDependencyEdge& Left, const FActivityDependencyEdge& Right)` (scope `UE::ConcertSyncCore`)

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncCore/Source/ConcertSyncCore/Public/HistoryEdition/ActivityDependencyGraph.h` (Public)


#### class `UE::ConcertSyncCore::FActivityDependencyGraph`  
`class FActivityDependencyGraph`  
_L62-85_
- desc: The graph models activities as nodes and dependencies to activities as edges. Activities can only affect each other from left-to-right: an earlier activity affects a later activity. We say an activity A has a hard dependency to activity B when A cannot exist in an activity history without B. We say an activity A has a possible dependency to activity B when A may exist with B but we cannot rule out that B does not affect A. Example: You modify an actor twice each time triggering the construction script. See EDependencyType. A node corresponds to an activity. A root node has depends on no other activity. An edge from a A to B means that B depends on A. Dependencies do not necessarily need to be transitive: 1. Remove package Foo 2. Create package Foo 3. Edit Foo The existence of 3 can requires that either - 1 and 2 both exist - 1 and 2 are deleted (among other details, e.g. that the underlying assets must have equal classes) Example: 1: Create level named Foo 2: Create level named Bar 3: Add actor named 'Cube' to level Foo 4. Add actor named 'Sphere" to level Foo 6: Edit 'Cube'. Resulting graph: 1		2 / \ 3	  4 / 5 Example: 1. Create data asset A 2. Edit and save A (remember: transactions do not happen for all .uasset only for .umaps) 3. Create actor in level 4. Edit actor to reference data assets A 5. Edit actor whose construction script reads data from A Resulting Graph: 1 I 2   3 \ / 4 I 5
- L67 _public prototype_ `FActivityNodeID AddActivity(int64 ActivityIndex, EActivityNodeFlags NodeFlags = EActivityNodeFlags::None);` — Adds a node. Invalidates the results of GetNodeById.
- L70 _public prototype_ `bool AddDependency(FActivityNodeID From, FActivityDependencyEdge To);` — Adds a dependency from an existing node to another existing node
- L73 _public prototype_ `TOptional<FActivityNodeID> FindNodeByActivity(int64 ActivityID) const;` — Tries to find a corresponding node for an activity ID.
- L76 _public prototype_ `const FActivityNode& GetNodeById(FActivityNodeID ID) const;` — Gets the node identified by the given ID, if it is valid. Only valid as long as no new node is added.
- L78 _public prototype_ `void ForEachNode(TFunctionRef<void(const FActivityNode&)> ConsumerFunc) const;`
- L82 _private member_ `TArray<FActivityNode> Nodes;`
- L84 _private prototype_ `FActivityNode& GetNodeByIdInternal(FActivityNodeID ID);`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API CONCERTSYNCCORE_API`
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace ConcertSyncCore` (scope `UE`)
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace ConcertSyncCore` (scope `UE`)
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace ConcertSyncCore` (scope `UE`)

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncCore/Source/ConcertSyncCore/Public/HistoryEdition/ActivityGraphIDs.h` (Public)


#### struct `UE::ConcertSyncCore::FActivityNodeID`  
`struct FActivityNodeID`  
_L12-45_
- desc: Enforces type-safe usage of IDs by avoiding implicit conversions.
- L14 _public member_ `size_t ID;`
- L16 _public prototype_ `FActivityNodeID() = default;`
- L19 _public function_ `template<typename T> explicit FActivityNodeID(T&& ID) : ID(Forward<T>(ID))`
- L24 _public function_ `explicit operator size_t() const` — Conversion back to to size_t is not a common programmer mistake

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace ConcertSyncCore` (scope `UE`)
- L26 _function_ `friend bool operator==(const FActivityNodeID& Left, const FActivityNodeID& Right)` (scope `UE::ConcertSyncCore`)
- L31 _function_ `friend bool operator!=(const FActivityNodeID& Left, const FActivityNodeID& Right)` (scope `UE::ConcertSyncCore`)
- L36 _function_ `FORCEINLINE friend uint32 GetTypeHash(const FActivityNodeID& NodeID)` (scope `UE::ConcertSyncCore`)

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncCore/Source/ConcertSyncCore/Public/HistoryEdition/ActivityNode.h` (Public)


#### enum `UE::ConcertSyncCore::EActivityNodeFlags`  
`enum class EActivityNodeFlags`  
_L18-24_
- L20 _public enumerator_ `None = 0x00`
- L23 _public enumerator_ `RenameActivity = 0x01` — This activity renames a package

#### class `UE::ConcertSyncCore::FActivityNode`  
`class FActivityNode`  
_L28-73_
- desc: A node corresponds to an activity and can depend on preceding activity
- L33 _public function_ `FActivityNode(int64 ActivityId, FActivityNodeID NodeIndex, EActivityNodeFlags NodeFlags) : ActivityId(ActivityId) , NodeIndex(NodeIndex) , NodeFlags(NodeFlags)`
- L39 _public function_ `bool HasAnyDependency() const`
- L40 _public prototype_ `bool DependsOnNode(FActivityNodeID NodeId, TOptional<EActivityDependencyReason> WithReason = {}, TOptional<EDependencyStrength> WithStrength = {}) const;`
- L41 _public prototype_ `bool DependsOnActivity(int64 InActivityId, const FActivityDependencyGraph& Graph, TOptional<EActivityDependencyReason> WithReason = {}, TOptional<EDependencyStrength> WithStrength = {}) const;`
- L43 _public function_ `bool AffectsAnyActivity() const`
- L44 _public function_ `bool AffectsNode(FActivityNodeID NodeID) const`
- L45 _public prototype_ `bool AffectsActivity(int64 InActivityId, const FActivityDependencyGraph& Graph) const;`
- L47 _public function_ `int64 GetActivityId() const`
- L48 _public function_ `FActivityNodeID GetNodeIndex() const`
- L49 _public function_ `EActivityNodeFlags GetNodeFlags() const`
- L50 _public function_ `const TArray<FActivityDependencyEdge>& GetDependencies() const`
- L51 _public function_ `const TArray<FActivityNodeID>& GetAffectedChildren() const`
- L56 _private member_ `const int64 ActivityId;` — The activity this node corresponds to
- L59 _private member_ `const FActivityNodeID NodeIndex;` — Index in parent tree's node array (graph uses TArray to avoid bad memory footprint)
- L62 _private member_ `const EActivityNodeFlags NodeFlags;` — Additional info about this activity node
- L65 _private member_ `TArray<FActivityDependencyEdge> Dependencies;` — This node's parents. Unset implies this is the root node.
- L72 _private member_ `TArray<FActivityNodeID> AffectedChildren;` — This node's children. Children have dependencies to this node. Activities can only depend on activities that precede them. Since activity IDs are historic, every child's activity ID > ActivityId.

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API CONCERTSYNCCORE_API`
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace ConcertSyncCore` (scope `UE`)

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncCore/Source/ConcertSyncCore/Public/HistoryEdition/DebugDependencyGraph.h` (Public)


#### enum `UE::ConcertSyncCore::Graphviz::ENodeTitleFlags`  
`enum class ENodeTitleFlags`  
_L39-48_
- L41 _public enumerator_ `None = 0x00`
- L43 _public enumerator_ `Summary = 0x01` — Use FConcertSyncActivitySummary::ToDisplayText
- L45 _public enumerator_ `ActivityID = 0x02` — Append activity ID
- L47 _public enumerator_ `Default = Summary | ActivityID`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace ConcertSyncCore` (scope `UE`)
- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace ConcertSyncCore` (scope `UE`)
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace ConcertSyncCore` (scope `UE`)
- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace ConcertSyncCore` (scope `UE`)
- L16 _namespace_ `namespace Graphviz` (scope `UE::ConcertSyncCore`)
- L28 _typedef_ `using FGraphStringBuilder = TStringBuilder<512>;` (scope `UE::ConcertSyncCore::Graphviz`)
- L29 _typedef_ `using FStringifyNode = TFunctionRef<void(FGraphStringBuilder& WriteTo, FActivityNodeID ToStringify)>;` (scope `UE::ConcertSyncCore::Graphviz`)
- L30 _typedef_ `using FStringifyEdge = TFunctionRef<void(FGraphStringBuilder& WriteTo, FActivityNodeID EdgeStart, const FActivityDependencyEdge& ToStringify)>;` (scope `UE::ConcertSyncCore::Graphviz`)
- L33 _typedef_ `using FMakeNodeTitle = FStringifyNode;` (scope `UE::ConcertSyncCore::Graphviz`) — Name of node without quotes, e.g. TEXT("start node name") (see above)
- L35 _typedef_ `using FGetNodeStyle = FStringifyNode;` (scope `UE::ConcertSyncCore::Graphviz`) — Style of the node which is printed right after the name, e.g. TEXT("[shape="ellipse" style="filled" fillcolor="#1f77b4"]") (see above)
- L37 _typedef_ `using FGetEdgeStyle = FStringifyEdge;` (scope `UE::ConcertSyncCore::Graphviz`) — Style of the edge which is printed right after an edge, e.g. TEXT("[fillcolor="#a6cee3" color="#1f78b4" label="Edge label"]") (see above)
- L49 _prototype_ `ENUM_CLASS_FLAGS(ENodeTitleFlags) void MakeNodeTitle(FGraphStringBuilder& WriteTo, FActivityNodeID ToStringify, const FActivityDependencyGraph& Graph, const FConcertSyncSessionDatabase& SessionDatabase, ENodeTitleFlags NodeTitleFlags = ENodeTitleFlags::Default);` (scope `UE::ConcertSyncCore::Graphviz`)
- L54 _prototype_ `void GetNodeStyle(FGraphStringBuilder& WriteTo, FActivityNodeID ToStringify, const FActivityDependencyGraph& Graph, const FConcertSyncSessionDatabase& SessionDatabase);` (scope `UE::ConcertSyncCore::Graphviz`) — Changes colour depending on activity type
- L56 _prototype_ `void GetEdgeStyle(FGraphStringBuilder& WriteTo, const FActivityDependencyEdge& ToStringify);` (scope `UE::ConcertSyncCore::Graphviz`) — Prints dependency reason and changes the arrow icon depending on dependency strength (half arrow for PossibleDependency, full arrow for HardDependency).
- L60 _prototype_ `FString ExportToGraphviz(const FActivityDependencyGraph& Graph, const FConcertSyncSessionDatabase& SessionDatabase, ENodeTitleFlags NodeTitleFlags = ENodeTitleFlags::Default);` (scope `UE::ConcertSyncCore::Graphviz`) — Calls ExportToGraphviz with the default formatting functions defined above.
- L68 _prototype_ `FString ExportToGraphviz(const FActivityDependencyGraph& Graph, FMakeNodeTitle MakeNodeTitleFunc, FGetNodeStyle GetNodeStyleFunc, FGetEdgeStyle GetEdgeStyleFunc);` (scope `UE::ConcertSyncCore::Graphviz`) — Exports the graph in a syntax that Graphviz (see:http://www.graphviz.org/) understands. Several online editors exist and can be found by searching for "graphviz online", e.g. - https://dreampuf.github.io/GraphvizOnline/ - http://magjac.com/graphviz-visual-editor/

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncCore/Source/ConcertSyncCore/Public/HistoryEdition/DependencyGraphBuilder.h` (Public)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace ConcertSyncCore` (scope `UE`)
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace ConcertSyncCore` (scope `UE`)
- L16 _prototype_ `FActivityDependencyGraph BuildDependencyGraphFrom(const FConcertSyncSessionDatabase& SessionDatabase);` (scope `UE::ConcertSyncCore`) — Builds a dependency graph from the given session database.

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncCore/Source/ConcertSyncCore/Public/HistoryEdition/HistoryAnalysis.h` (Public)


#### struct `UE::ConcertSyncCore::FHistoryAnalysisResult`  
`struct FHistoryAnalysisResult`  
_L14-28_
- desc: Describes the activities that must be considered when deleting an activity
- L17 _public member_ `TSet<FActivityID> HardDependencies;` — The activities that must be removed.
- L22 _public member_ `TSet<FActivityID> PossibleDependencies;` — The activities may want to be removed. It's not certain that they are affected (but it should be safe to keep them in). This will not contain any elements in HardDependencies.
- L24 _public function_ `FHistoryAnalysisResult(TSet<FActivityID> HardDependencies = {}, TSet<FActivityID> PossibleDependencies = {}) : HardDependencies(MoveTemp(HardDependencies)) , PossibleDependencies(MoveTemp(PossibleDependencies))`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace ConcertSyncCore` (scope `UE`)
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace ConcertSyncCore` (scope `UE`)
- L31 _prototype_ `FHistoryAnalysisResult AnalyseActivityDependencies_TopDown(const TSet<FActivityID>& ActivitiesToDelete, const FConcertSyncSessionDatabase& Database, bool bAddActivitiesToDelete = false);` (scope `UE::ConcertSyncCore`) — Utility function for one-off operations: just computes the dependency graph before calling AnalyseActivityDeletion.
- L43 _prototype_ `FHistoryAnalysisResult AnalyseActivityDependencies_TopDown(const TSet<FActivityID>& ActivitiesToEdit, const FActivityDependencyGraph& DependencyGraph, bool bAddEditedAsHardDependencies = false);` (scope `UE::ConcertSyncCore`) — Given a set of activities to be edited (e.g. deleted or muted), returns which activities 1. must be and 2. may want to be considered in addition. This algorithm proceeds top-down meaning it will start at ActivitiesToEdit and recursively process child nodes that depend on it. This approach is good for finding activities that depends on a set of activities, e.g. for deleting or muting ActivitiesToEdit. @param ActivitiesToEdit The activities whose children to search @param DependencyGraph The graph encoding the activity dependencies @param bAddEditedAsHardDependencies Whether to add ActivitiesToEdit to the result's HardDependencies @return The activities to consider as well if ActivitiesToEdit are edited; ActivitiesToEdit is included in HardDependencies if bAddActivitiesToDelete == true.
- L55 _prototype_ `FHistoryAnalysisResult AnalyseActivityDependencies_BottomUp(const TSet<FActivityID>& ActivitiesToEdit, const FActivityDependencyGraph& DependencyGraph, bool bAddEditedAsHardDependencies = false);` (scope `UE::ConcertSyncCore`) — Given a set of activities to be edited (e.g. to be unmuted), returns which activities 1. must be and 2. may want to be considered in addition. This algorithm proceeds bottom-up meaning it will start at ActivitiesToEdit and recursively process parent nodes it depends on. This approach is good for finding the activities that are depended on by set of activities, e.g. unmuting ActivitiesToEdit. @param ActivitiesToEdit The activities whose parents to search @param DependencyGraph The graph encoding the activity dependencies @param bAddEditedAsHardDependencies Whether to add ActivitiesToEdit to the result's HardDependencies @return The activities to consider as well if ActivitiesToEdit are edited; ActivitiesToEdit is included in HardDependencies if bAddActivitiesToDelete == true.

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncCore/Source/ConcertSyncCore/Public/HistoryEdition/HistoryEdition.h` (Public)


#### struct `UE::ConcertSyncCore::FOperationErrorResult`  
`struct FOperationErrorResult`  
_L14-27_
- L16 _public member_ `TOptional<FText> ErrorMessage;`
- L18 _public function_ `explicit FOperationErrorResult(TOptional<FText> ErrorMessage = {}) : ErrorMessage(ErrorMessage)`
- L22 _public function_ `static FOperationErrorResult MakeSuccess()`
- L23 _public function_ `static FOperationErrorResult MakeError(FText Error)`
- L25 _public function_ `bool WasSuccessful() const`
- L26 _public function_ `bool HadError() const`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace ConcertSyncCore` (scope `UE`)
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace ConcertSyncCore` (scope `UE`)
- L30 _prototype_ `TSet<FActivityID> CombineRequirements(const FHistoryAnalysisResult& ToDelete);` (scope `UE::ConcertSyncCore`) — Utility functions that converts FHistoryDeletionRequirements into a single TSet.

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncCore/Source/ConcertSyncCore/Public/Misc/EBreakBehavior.h` (Public)


#### enum `EBreakBehavior`  
`enum class EBreakBehavior : uint8`  
_L7-11_
- L9 _public enumerator_ `Break`
- L10 _public enumerator_ `Continue`

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncCore/Source/ConcertSyncCore/Public/Misc/ObjectPathHierarchy.h` (Public)


#### enum `UE::ConcertSyncCore::ETreeTraversalBehavior`  
`enum class ETreeTraversalBehavior : uint8`  
_L17-25_
- L20 _public enumerator_ `Continue` — Gives us the next element (may be child or neigbhour)
- L22 _public enumerator_ `SkipSubtree` — Gives us the next neighbour element - do not list any children of this node.
- L24 _public enumerator_ `Break` — Stop iteration

#### enum `UE::ConcertSyncCore::EHierarchyObjectType`  
`enum class EHierarchyObjectType`  
_L27-39_
- L33 _public enumerator_ `Explicit` — The object entry was added through an AddObject call. Example: AddObject(/Game/Maps.Map:PersistentLevel.Cube.StaticMeshComponent1)
- L38 _public enumerator_ `Implicit` — The object entry was added indirectly because of a AddObject to a child. Example: AddObject(/Game/Maps.Map:PersistentLevel.Cube.StaticMeshComponent1) adds /Game/Maps.Map:PersistentLevel.Cube implicitly.

#### struct `UE::ConcertSyncCore::FObjectHierarchyInfo`  
`struct FObjectHierarchyInfo`  
_L41-45_
- L43 _public member_ `FSoftObjectPath Object;`
- L44 _public member_ `EHierarchyObjectType Type;`

#### struct `UE::ConcertSyncCore::FChildRelation`  
`struct FChildRelation`  
_L47-51_
- L49 _public member_ `FObjectHierarchyInfo Parent;`
- L50 _public member_ `FObjectHierarchyInfo Child;`

#### class `UE::ConcertSyncCore::FObjectPathHierarchy`  
`class FObjectPathHierarchy`  
_L54-174_
- inherits: `FNoncopyable`
- desc: Keeps track of the outer tree hierarchy of FSoftObjectPath.
- L60 _public prototype_ `FObjectPathHierarchy() = default;`
- L61 _public prototype_ `FObjectPathHierarchy(FObjectPathHierarchy&& Other);`
- L62 _public prototype_ `FObjectPathHierarchy& operator=(FObjectPathHierarchy&& Other);`
- L86 _public prototype_ `void TraverseTopToBottom(TFunctionRef<ETreeTraversalBehavior(const FChildRelation& Relation)> Callback, const FSoftObjectPath& Start = {}) const;` — Traverses the hierarchy in pre-order (root first, then its children), starting at an optional parent object. Example sequence of callback invocations: 1. (/Game/Maps.Map,							/Game/Maps.Map:PersistentLevel) 2. (/Game/Maps.Map:PersistentLevel,			/Game/Maps.Map:PersistentLevel.Cube) 3. (/Game/Maps.Map:PersistentLevel.Cube,		/Game/Maps.Map:PersistentLevel.Cube.StaticMeshComponent0) 4. (/Game/Maps.Map:PersistentLevel.Cube,		/Game/Maps.Map:PersistentLevel.Cube.StaticMeshComponent1) 5. (/Game/Maps.Map:PersistentLevel,			/Game/Maps.Map:PersistentLevel.Sphere) 6. (/Game/Maps.Map:PersistentLevel.Sphere,	/Game/Maps.Map:PersistentLevel.Sphere.StaticMeshComponent0) @important This lists implicit parents. For example, if you called AddObject(/Game/Maps.Map:PersistentLevel.Cube.StaticMeshComponent0), then its outers will be implicitly considered part of the hierarchy (i.e. /Game/Maps.Map:PersistentLevel.Cube, /Game/Maps.Map:PersistentLevel, /Game/Maps.Map). Use the FChildRelation to determine whether an object is part of the hiearchy implicitly or explicitly. Assets without subobjects are not listed. For example, if you called AddObject(/Game/Maps.Map) and the hierarchy was otherwise empty, Callback would not be invoked. @param Callback The callback to invoke @param Start The object at which to start walking down the hierarchy
- L110 _public prototype_ `void TraverseBottomToTop(TFunctionRef<EBreakBehavior(const FChildRelation& Relation)> Callback, const FSoftObjectPath& Start = {}) const;` — Traverses the hierarchy in post-order (children first, then the root), starting at an optional parent object. Example sequence of callback invocations: 1. (/Game/Maps.Map:PersistentLevel.Cube,		/Game/Maps.Map:PersistentLevel.Cube.StaticMeshComponent0) 2. (/Game/Maps.Map:PersistentLevel.Cube,		/Game/Maps.Map:PersistentLevel.Cube.StaticMeshComponent1) 3. (/Game/Maps.Map:PersistentLevel,			/Game/Maps.Map:PersistentLevel.Cube) 4. (/Game/Maps.Map:PersistentLevel.Sphere,	/Game/Maps.Map:PersistentLevel.Sphere.StaticMeshComponent0) 5. (/Game/Maps.Map:PersistentLevel,			/Game/Maps.Map:PersistentLevel.Sphere) 6. (/Game/Maps.Map,							/Game/Maps.Map:PersistentLevel) @important This lists implicit parents. For example, if you called AddObject(/Game/Maps.Map:PersistentLevel.Cube.StaticMeshComponent0), then its outers will be implicitly considered part of the hierarchy (i.e. /Game/Maps.Map:PersistentLevel.Cube, /Game/Maps.Map:PersistentLevel, /Game/Maps.Map). Use the FChildRelation to determine whether an object is part of the hiearchy implicitly or explicitly. Assets without children are not listed. For example, if you called AddObject(/Game/Maps.Map) and the hierarchy was otherwise empty, Callback would not be invoked. @param Callback The callback to invoke @param Start The object at which to start walking up the hierarchy
- L113 _public prototype_ `TOptional<EHierarchyObjectType> IsInHierarchy(const FSoftObjectPath& Object) const;` — @return A valid TOptional if the object is in the hierarchy with the value indicating whether implicitly or explicitly. Unset if the object does not appear in the hierarchy.
- L115 _public prototype_ `bool HasChildren(const FSoftObjectPath& Object) const;` — @return Whether Object has any subobjects in the hierarchy.
- L117 _public prototype_ `bool IsAssetInHierarchy(const FSoftObjectPath& Object) const;` — @return Whether Object is an asset, i.e. a top-level asset that has never have any parents.
- L120 _public function_ `bool IsEmpty() const` — Checks there is an hierarchy.
- L127 _public prototype_ `void AddObject(const FSoftObjectPath& ObjectPath);` — Adds Object to the hierarchy. Henceforth, the object shall be tracked as EHierarchyObjectType::Explicit. Calling this more than once has no effect.
- L135 _public prototype_ `void RemoveObject(const FSoftObjectPath& Object);` — Removes Object from the hierarchy. If the object has no children, the object is removed entirely. If the object has children, it shall henceforth be tacked as EHierarchyObjectType::Implicit.
- L138 _public function_ `void Clear()` — Empties the entire hierarchy to the empty state.
- L160 _private member_ `TArray<TUniquePtr<FTreeNode>> AssetNodes;` — Each node represents an asset, e.g. /Game/Maps.Map. That means every node in this array is of the form /package/path.assetname (i.e. FSoftObjectPath::AssetPath is set and FSoftObjectPath::SubPathString is empty). Remember in general FSoftObjectPath strings look like this: /package/path.assetname[:subpath] where /package/path.assetname is the FSoftObjectPath::AssetPath.
- L162 _private member_ `TMap<FSoftObjectPath, FTreeNode*> CachedNodes;` — Maps every path to the corresponding node.
- L164 _private prototype_ `static ETreeTraversalBehavior TraverseTopToBottomInternal( const FObjectHierarchyInfo& Owner, const TArray<TUniquePtr<FTreeNode>>& Nodes, TFunctionRef<ETreeTraversalBehavior(const FChildRelation& Relation)> Callback );`
- L169 _private prototype_ `static EBreakBehavior TraverseBottomToTopInternal( const FObjectHierarchyInfo& Owner, const TArray<TUniquePtr<FTreeNode>>& Nodes, TFunctionRef<EBreakBehavior(const FChildRelation& Relation)> Callback );`

#### struct `UE::ConcertSyncCore::FObjectPathHierarchy::FTreeNode`  
`struct FTreeNode`  
_L142-152_
- L144 _public member_ `FObjectHierarchyInfo Data;`
- L145 _public member_ `FTreeNode* Parent = nullptr;`
- L146 _public member_ `TArray<TUniquePtr<FTreeNode>> Children;`
- L148 _public function_ `explicit FTreeNode(FObjectHierarchyInfo Data) : Data(MoveTemp(Data))`
- L151 _public function_ `bool IsAssetNode() const`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API CONCERTSYNCCORE_API`
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace ConcertSyncCore` (scope `UE`)

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncCore/Source/ConcertSyncCore/Public/Misc/ObjectPathOuterIterator.h` (Public)


#### class `UE::ConcertSyncCore::FObjectPathOuterIterator`  
`class FObjectPathOuterIterator`  
_L29-61_
- desc: Parses a FSoftObjectPath string and iterates through all outer objects of the Start path. Example: Start = /Game/Maps.Map:PersistentLevel.Cube.StaticMeshComponent0.Foo would invoke Callback in this order: 1. /Game/Maps.Map:PersistentLevel.Cube.StaticMeshComponent0 2. /Game/Maps.Map:PersistentLevel.Cube 3. /Game/Maps.Map:PersistentLevel 4. /Game/Maps.Map Example usage: const FSoftObjectPath ComponentPath{ TEXT("/Game/Maps.Map:PersistentLevel.Cube.StaticMeshComponent0") }; for (ConcertSyncCore::FObjectPathOuterIterator It(ComponentPath); It; ++It) { const FSoftObjectPath& Path = *It; // 1st iteration = /Game/Maps.Map:PersistentLevel.Cube const FString String = It->ToString(); // 1st iteration = /Game/Maps.Map:PersistentLevel.Cube }
- L33 _public function_ `explicit FObjectPathOuterIterator(const FSoftObjectPath& Start) : Current(Start)`
- L39 _public function_ `FORCEINLINE void operator++()`
- L41 _public function_ `FORCEINLINE explicit operator bool() const`
- L42 _public function_ `FORCEINLINE bool operator !() const`
- L44 _public function_ `FORCEINLINE const FSoftObjectPath& operator*() const`
- L45 _public function_ `FORCEINLINE const FSoftObjectPath* operator->() const`
- L47 _public function_ `FORCEINLINE bool operator==(const FObjectPathOuterIterator& Right) const`
- L48 _public function_ `FORCEINLINE bool operator!=(const FObjectPathOuterIterator& Right) const`
- L52 _private member_ `TOptional<FSoftObjectPath> Current;`
- L54 _private function_ `void Advance()`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace ConcertSyncCore` (scope `UE`)

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncCore/Source/ConcertSyncCore/Public/Misc/ObjectPathUtils.h` (Public)


#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace ConcertSyncCore` (scope `UE`)
- L23 _prototype_ `TOptional<FSoftObjectPath> GetOuterPath(const FSoftObjectPath& ObjectPath);` (scope `UE::ConcertSyncCore`) — Gets the outer of ObjectPath. Examples: - GetOuterPath(/Game/Map.Map:PersistentLevel.Actor.Component)	= /Game/Map.Map:PersistentLevel.Actor - GetOuterPath(/Game/Map.Map:PersistentLevel.Actor)				= /Game/Map.Map:PersistentLevel - GetOuterPath(/Game/Map.Map:PersistentLevel)					= /Game/Map.Map - GetOuterPath(/Game/Map.Map)									= unset optional - GetOuterPath({})												= unset optional @return The outer of ObjectPath, if there is one. Unset if ObjectPath points to a package.
- L26 _namespace_ `namespace UE`
- L26 _namespace_ `namespace ConcertSyncCore` (scope `UE`)
- L28 _function_ `inline TOptional<FSoftObjectPath> GetOuterPath(const FSoftObjectPath& ObjectPath)` (scope `UE::ConcertSyncCore`)

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncCore/Source/ConcertSyncCore/Public/Misc/ObjectUtils.h` (Public)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace ConcertSyncCore` (scope `UE`)
- L11 _prototype_ `bool IsActor(const FSoftObjectPath& Object);` (scope `UE::ConcertSyncCore`) — @return Checks whether the given object is an actor.
- L14 _prototype_ `TOptional<FSoftObjectPath> GetActorOf(const FSoftObjectPath& Subobject);` (scope `UE::ConcertSyncCore`) — @return Get the owning actor of Subobject. If Subobject is an actor, then this returns unset.
- L16 _function_ `FORCEINLINE TOptional<FSoftObjectPath> GetActorPathIn(const FSoftObjectPath& Path)` (scope `UE::ConcertSyncCore`) — @return The actor portion of the path. Difference to GetActorOf: returns a set value whenever the path is an object in the level (actor, component, etc.)
- L19 _prototype_ `FUtf8String ExtractObjectNameFromPath(const FSoftObjectPath& Object);` (scope `UE::ConcertSyncCore`) — @return Gets the last object name in the subpath.
- L42 _prototype_ `TOptional<FSoftObjectPath> ReplaceActorInPath(const FSoftObjectPath& OldPath, const FSoftObjectPath& NewActor);` (scope `UE::ConcertSyncCore`) — Replaces the package path and actor name from NewActor witht that of NewActor. Valid example 1: - OldPath:		/Game/OldMap.OldMap:PersistentLevel.OldActor.Subobject - NewActor:		/Game/NewMap.NewMap:PersistentLevel.NewActor - Result:		/Game/NewMap.NewMap:PersistentLevel.NewActor.Subobject Invalid examples: - Missing actor path: - OldPath:		/Game/Map.Map.Actor,	NewPath: /Game/Map.Map - OldPath:		/Game/Map.Map,			NewPath: /Game/Map.Map.Actor - Subobject in NewActor are not allowed: - OldPath:		/Game/Map.Map:PersistentLevel.OldActor.Subobject - NewActor:		/Game/Map.Map:PersistentLevel.NewActor.Subobject @param OldPath A path to an object in a UWorld in which the actor is supposed to be replaced @param NewActor A path to an actor @return The replaced object paths. Unset if the arguments were invalid.

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncCore/Source/ConcertSyncCore/Public/Replication/AuthorityConflictSharedUtils.h` (Public)


#### enum `UE::ConcertSyncCore::Replication::AuthorityConflictUtils::EAuthorityConflict`  
`enum class EAuthorityConflict : uint8`  
_L21-27_
- L24 _public enumerator_ `Allowed` — The client is allowed to take authority
- L26 _public enumerator_ `Conflict` — There was at least one conflict

#### Free symbols / members of external scopes

- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace ConcertSyncCore` (scope `UE`)
- L17 _namespace_ `namespace Replication` (scope `UE::ConcertSyncCore`)
- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace ConcertSyncCore` (scope `UE`)
- L19 _namespace_ `namespace Replication` (scope `UE::ConcertSyncCore`)
- L19 _namespace_ `namespace AuthorityConflictUtils` (scope `UE::ConcertSyncCore::Replication`)
- L29 _typedef_ `using FProcessAuthorityConflict = TFunctionRef<EBreakBehavior(const FGuid& ClientId, const FGuid& StreamId, const FConcertPropertyChain& ConflictingProperty)>;` (scope `UE::ConcertSyncCore::Replication::AuthorityConflictUtils`)
- L43 _prototype_ `EAuthorityConflict EnumerateAuthorityConflicts( const FGuid& ClientId, const FSoftObjectPath& Object, const TSet<FConcertPropertyChain>& OverwriteProperties, const IReplicationGroundTruth& GroundTruth, FProcessAuthorityConflict ProcessConflict = [](const FGuid&, const FGuid&, const FConcertPropertyChain&){ return EBreakBehavior::Break; } );` (scope `UE::ConcertSyncCore::Replication::AuthorityConflictUtils`) — Enumerates all authority conflicts, if any, that would occur if Object were to be replicated with the given Properties. @param ClientId The client that wants to take authority @param Object Describes the object, the client, and the stream to be replicated. @param OverwriteProperties The properties that will be registered with the object (i.e. not what IClientInfoSource reports currently) @param GroundTruth Provides information about clients. On the server, it is the definite state whereas on client machines it would be what the local client thinks what the server state is. @param ProcessConflict Callback to be called for each permutation of conflicting client, stream and property. @return Whether there were any conflicts
- L48 _function_ `const FSoftObjectPath& Object, const TSet<FConcertPropertyChain>& OverwriteProperties, const IReplicationGroundTruth& GroundTruth, FProcessAuthorityConflict ProcessConflict = [](const FGuid&, const FGuid&, const FConcertPropertyChain&)` (scope `UE::ConcertSyncCore::Replication::AuthorityConflictUtils`)
- L59 _prototype_ `void CleanseConflictsFromAuthorityRequest(FConcertReplication_ChangeAuthority_Request& Request, const FGuid& SendingClient, const IReplicationGroundTruth& GroundTruth);` (scope `UE::ConcertSyncCore::Replication::AuthorityConflictUtils`) — Removes entries from Request that would generate conflicts. @param Request The request to clense @param SendingClient The client that will send the request @param GroundTruth Provides information about clients. On the server, it is the definite state whereas on client machines it would be what the local client thinks what the server state is.
- L69 _prototype_ `void CleanseConflictsFromStreamRequest(FConcertReplication_ChangeStream_Request& Request, const FGuid& SendingClient, const IReplicationGroundTruth& GroundTruth);` (scope `UE::ConcertSyncCore::Replication::AuthorityConflictUtils`) — Removes entries from Request that would generate conflicts. @param Request The request to clense @param SendingClient The client that will send the request @param GroundTruth Provides information about clients. On the server, it is the definite state whereas on client machines it would be what the local client thinks what the server state is.

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncCore/Source/ConcertSyncCore/Public/Replication/ChangeStreamSharedUtils.h` (Public)


#### Free symbols / members of external scopes

- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace ConcertSyncCore` (scope `UE`)
- L19 _namespace_ `namespace Replication` (scope `UE::ConcertSyncCore`)
- L19 _namespace_ `namespace ChangeStreamUtils` (scope `UE::ConcertSyncCore::Replication`)
- L29 _prototype_ `void ForEachRemovedObject( const FConcertReplication_ChangeStream_Request& Request, const TArray<FConcertReplicationStream>& ExistingStreams, TFunctionRef<EBreakBehavior(const FConcertObjectInStreamID&)> Callback );` (scope `UE::ConcertSyncCore::Replication::ChangeStreamUtils`) — Iterates through all objects that are removed and therefore the requesting client would lose authority over. This function assumes that Request was validated. @param Request The request to parse @param ExistingStreams The streams the request would be applied to @param Callback The callback to process the objects
- L43 _prototype_ `void ForEachAddedObject( const FConcertReplication_ChangeStream_Request& Request, const TArray<FConcertReplicationStream>& ExistingStreams, TFunctionRef<EBreakBehavior(const FConcertObjectInStreamID&)> Callback );` (scope `UE::ConcertSyncCore::Replication::ChangeStreamUtils`) — Iterates through all objects that are added by Request but not yet in ExistingStreams. This function assumes that Request was validated. @param Request The request to parse @param ExistingStreams The streams the request would be applied to @param Callback The callback to process the objects
- L54 _prototype_ `void ApplyValidatedRequest( const FConcertReplication_ChangeStream_Request& Request, IN OUT TArray<FConcertReplicationStream>& StreamsToModify );` (scope `UE::ConcertSyncCore::Replication::ChangeStreamUtils`) — Modifies RegisteredStreams as described by the request without validating that the Request is valid to apply. @param Request The request to parse @param StreamsToModify The streams to apply the request to
- L68 _prototype_ `void ApplyValidatedFrequencyChanges( const FConcertReplication_ChangeStream_Frequency& Request, FConcertStreamFrequencySettings& SettingsToModify );` (scope `UE::ConcertSyncCore::Replication::ChangeStreamUtils`) — Modifies StreamToModify as described by the request. Validate the request before calling. This function does use ensure conditions where it makes sense but it does not check all failure cases. @param Request The request to parse @param SettingsToModify The streams to apply the request to
- L81 _prototype_ `bool ValidateFrequencyChanges( const FConcertReplication_ChangeStream_Request& Request, const TConstArrayView<FConcertReplicationStream>& Streams, OUT FConcertReplication_ChangeStream_FrequencyResponse* OptionalErrors = nullptr );` (scope `UE::ConcertSyncCore::Replication::ChangeStreamUtils`) — Validates a FConcertReplication_ChangeStream_Request and optionally outputs the errors into OptionalErrors if set. @param Request The request to validate. Note that the full request is needed (if an object is added through this @param Streams The streams array Request would be run on @param OptionalErrors Errors are written into this struct if set @return Whether Request is valid to apply to Streams
- L88 _prototype_ `void IterateInvalidEntries(const FConcertObjectReplicationMap& ReplicationMap, TFunctionRef<EBreakBehavior(const FSoftObjectPath&, const FConcertReplicatedObjectInfo&)> Callback);` (scope `UE::ConcertSyncCore::Replication::ChangeStreamUtils`) — Iterates entries with incomplete data, which are entries for which IsValidForSendingToServer returns false.
- L103 _prototype_ `FConcertReplication_ChangeStream_Request BuildRequestFromDiff( const FGuid& StreamId, const FConcertObjectReplicationMap& Base, const FConcertObjectReplicationMap& Desired );` (scope `UE::ConcertSyncCore::Replication::ChangeStreamUtils`) — Builds PutObject and RemoveObject requests that would transform Base to Desired. The state of an object in a replication map is only valid if all its members have values: that means the class is non-null and not the property selection is non-empty. This function enforces (and ensure()s) that the Base and Desired states are valid. The changes are validated using FConcertChangeStream_PutObject's factories MakeFromInfo and MakeFromChange. @param StreamId The ID of the changed stream: it is inserted into the request @param Base The base stream @param Desired The state the stream should end up in @return A semantically correct FConcertChangeStream_Request which Base to Desired (note is can be rejected due to authority conflicts).

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncCore/Source/ConcertSyncCore/Public/Replication/Data/ActorLabelRemapping.h` (Public)


#### struct `FConcertReplicationRemappingData_Actor`  
`struct FConcertReplicationRemappingData_Actor`  
_L14-42_
- reflection: `USTRUCT()`
- desc: Metadata about an actor in a FConcertObjectReplicationMap.
- L25 _public member_ `FString Label;` — `UPROPERTY()` — Label of the actor. This is typically AActor::ActorLabel. Practically, the API is generic enough to allow using some other actor identifying string at runtime instead if you really wanted to.
- L41 _public member_ `FSoftClassPath Class;` — `UPROPERTY()` — The class the actor had when the remapping data was generated. Note that the actor's itself may not even have been in the FConcertObjectReplicationMap when the data was generated. During generation, when processing a component (or other subobject), the owning actor instance can be looked up by path and its class is recorded here. If the actor does not resolve, it is not recorded. Example: - Suppose the replication contains a single component: "/Game/World.World:PersistentLevel.Actor.Component" - If during data generation, the class of "/Game/World.World:PersistentLevel.Actor" - can be obtained, the corresponding FConcertReplicationRemappingData::ActorData contains the actor path and its class. - can not be obtained, then FConcertReplicationRemappingData::Actor.IsEmpty()

#### struct `FConcertReplicationRemappingData`  
`struct FConcertReplicationRemappingData`  
_L66-73_
- reflection: `USTRUCT()`
- desc: Supplementary data for a FConcertObjectReplicationMap. This data can be used to remap FSoftObjectPaths in FConcertObjectReplicationMap to different FConcertObjectReplicationMap based on AActor::ActorLabel. The primary use case is replication presets being translated multiple sessions. Example: 1. In session 1, suppose a FConcertObjectReplicationMap is created like this: - { "/Game/World.World:PersistentLevel.ActorOld", { "ActorTags" } } - { "/Game/World.World:PersistentLevel.ActorOld.StaticMeshComponentOld", { "RelativeLocation", "RelativeLocation.X" } } - Actor_0 has the actor label "MyStaticMeshActor" 2. As part of creating the FConcertObjectReplicationMap, you also create a FConcertReplicationRemappingData (@see ActorLabelRemappingCore.h) 3. In session 2, suppose there is world: - /Game/OtherWorld.OtherWorld:PersistentLevel.ActorNew - /Game/OtherWorld.OtherWorld.PersistentLevel.ActorNew.StaticMeshComponentNew - OtherActor_0 has the actor label "MyStaticMeshActor" In the above scenario, you can now remap the FConcertObjectReplicationMap from step 1 using the FConcertReplicationRemappingData from step 2. Effectively, "ActorNew" would get the properties of "ActorOld", and "StaticMeshComponentNew" the properties of "StaticMeshComponentOld", because the labels of "ActorNew" and "ActorOld" are both "MyStaticMeshActor". @see ActorLabelRemappingUtils.h
- L72 _public member_ `TMap<FSoftObjectPath, FConcertReplicationRemappingData_Actor> ActorData;` — `UPROPERTY()` — Data about actors.

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncCore/Source/ConcertSyncCore/Public/Replication/Data/AuthorityConflict.h` (Public)


#### struct `FConcertAuthorityConflict`  
`struct FConcertAuthorityConflict`  
_L12-23_
- reflection: `USTRUCT()`
- desc: Describes an authority conflict for two objects.
- L18 _public member_ `FConcertObjectInStreamID AttemptedObject;` — `UPROPERTY()` — The object that was attempted to take authority over but could not be.
- L22 _public member_ `FConcertReplicatedObjectId ConflictingObject;` — `UPROPERTY()` — The object of another client that Source conflicts with.

#### struct `FConcertAuthorityConflictArray`  
`struct FConcertAuthorityConflictArray`  
_L26-48_
- reflection: `USTRUCT()`
- L32 _public member_ `TArray<FConcertAuthorityConflict> Conflicts;` — `UPROPERTY()` — Each AttemptedObject is unique.
- L34 _public function_ `FConcertAuthorityConflict& FindOrAdd(const FConcertObjectInStreamID& AttemptedObject)`

#### Free symbols / members of external scopes

- L37 _function_ `` (scope `FConcertAuthorityConflictArray::FindOrAdd`)

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncCore/Source/ConcertSyncCore/Public/Replication/Data/ClientQueriedInfo.h` (Public)


#### struct `FConcertAuthorityClientInfo`  
`struct FConcertAuthorityClientInfo`  
_L11-25_
- reflection: `USTRUCT()`
- desc: Describes objects a client has authority over
- L17 _public member_ `FGuid StreamId;` — `UPROPERTY()` — The stream ID the client has registered
- L24 _public member_ `TArray<FSoftObjectPath> AuthoredObjects;` — `UPROPERTY()` — The objects the client has authority over. You can figure out the properties by inspecting the corresponding client's stream using the object path.

#### struct `FConcertQueriedClientInfo`  
`struct FConcertQueriedClientInfo`  
_L29-59_
- reflection: `USTRUCT()`
- desc: This is info a client receives about another client via FConcertQueryClientStreams_Request.
- L41 _public member_ `TArray<FConcertBaseStreamInfo> Streams;` — `UPROPERTY()` — The streams the client has registered. If EConcertQueryClientStreamFlags::SkipStreamInfo was set, this is empty. If EConcertQueryClientStreamFlags::SkipProperties was set, streams' FConcertReplicatedObjectInfo::PropertySelection are empty. If EConcertQueryClientStreamFlags::SkipFrequency was set, the FrequencySettings are empty.
- L49 _public member_ `TArray<FConcertAuthorityClientInfo> Authority;` — `UPROPERTY()` — Indirectly describes which object properties the client has authority over. If EConcertQueryClientStreamFlags::SkipAuthority was set, this is empty.
- L51 _public function_ `bool IsEmpty() const`
- L54 _public function_ `bool HasAuthority(const FConcertObjectInStreamID& Object) const` — @return Whether Object is owned

#### Free symbols / members of external scopes

- L56 _function_ `const FConcertAuthorityClientInfo* Info = Authority.FindByPredicate([StreamId = Object.StreamId](const FConcertAuthorityClientInfo& Info){ return Info.StreamId == StreamId; });` (scope `FConcertQueriedClientInfo::HasAuthority`)

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncCore/Source/ConcertSyncCore/Public/Replication/Data/ConcertPropertySelection.h` (Public)


#### struct `FConcertPropertyChain`  
`struct FConcertPropertyChain`  
_L18-129_
- reflection: `USTRUCT()`
- desc: Describes the path to a FProperty replicated by Concert. @see FConcertPropertyChain::PathToProperty.
- L23 _public prototype_ `static TOptional<FConcertPropertyChain> CreateFromPath(const UStruct& Class, const TArray<FName>& NamePath);` — Constructs a FConcertPropertyChain from a path if it is valid. If you need to create many paths in one go, use PropertyUtils::BulkConstructConcertChainsFromPaths instead.
- L25 _public prototype_ `FConcertPropertyChain() = default;`
- L30 _public prototype_ `FConcertPropertyChain(const FArchiveSerializedPropertyChain* OptionalChain, const FProperty& LeafProperty);` — @param OptionalChain The chain leading up to LeafProperty. If it is a root property it can either be empty or nullptr. This mimics the behaviours of FArchive. @param LeafProperty The property the chain leads to. It will be the last property in PathToProperty. This can be the inner property of a container but ONLY for primitive types (float, etc.) or structs with a custom Serialize function.
- L33 _public function_ `FName GetLeafProperty() const` — Gets the leaf property, which is the property the path leads towards.
- L34 _public function_ `FName GetRootProperty() const`
- L35 _public function_ `bool IsRootProperty() const`
- L36 _public function_ `bool IsEmpty() const`
- L39 _public function_ `bool IsParentOf(const FConcertPropertyChain& ChildToCheck) const` — @return Whether this is a parent of ChildToCheck
- L42 _public prototype_ `bool IsChildOf(const FConcertPropertyChain& ParentToCheck) const;` — @return Whether the leaf property is a child of the given property chain.
- L44 _public prototype_ `bool IsDirectChildOf(const FConcertPropertyChain& ParentToCheck) const;` — @return Whether the leaf property is a direct child of the given property chain.
- L52 _public prototype_ `bool MatchesExactly(const FArchiveSerializedPropertyChain* OptionalChain, const FProperty& LeafProperty) const;` — Utility for checking whether this path corresponds to OptionalChain leading to LeafProperty. @param OptionalChain Contains all properties leading up to the LeafProperty. You can skip inner container properties. @param LeafProperty The last property @return Whether OptionalChain and LeafProperty correspond to this path.
- L55 _public prototype_ `FProperty* ResolveProperty(const UStruct& Class, bool bLogOnFail = true) const;` — @return Attempts to resolve this property given the class
- L58 _public prototype_ `FConcertPropertyChain GetParent() const;` — @return The property immediately before the current one in the chain
- L60 _public prototype_ `FConcertPropertyChain GetRootParent() const;` — @return The root-most parent in the chain.
- L62 _public function_ `const TArray<FName>& GetPathToProperty() const` — @return The property path
- L69 _public prototype_ `FString ToString(EToStringMethod Method = EToStringMethod::Path) const;`
- L128 _private member_ `TArray<FName> PathToProperty;` — `UPROPERTY()` — Path from root of UObject to leaf property. Includes the leaf property. Inner container properties, i.e. FArrayProperty::Inner, FSetProperty::ElementProp, FMapProperty::KeyProp, and FMapProperty::ValueProp, are never listed in the property path. Listing some paths (see example code below): - { "Struct", "Foo" } - { "ArrayOfStructs", "Foo" } - { "MapOfStructs" } - { "MapOfStructs", "Foo" } See Concert.Replication.Data.ForEachReplicatableConcertProperty for path examples (just CTRL+SHIFT+F or go to ConcertSyncTest/Replication/ConcertPropertyTests.cpp). FConcertPropertyChains do NOT cross the UObject border. In the above example, there would be no such thing as { "UnsupportedInstanced", ... }. You'd start a new FConcertPropertyChain for properties for objects of type UFooSubobject. This property is kept private to force the use of the exposed constructors. Code for example: class AFooActor { UPROPERTY() FFooStruct Struct; UPROPERTY() TArray<FFooStruct> ArrayOfStructs; UPROPERTY() TMap<int32, FFooStruct> MapOfStructs; UPROPERTY() TMap<int32, float> MapIntToFloat; UPROPERTY(Instanced) TArray<UFooSubobject*> UnsupportedInstanced; }; struct FFooStruct { UPROPERTY() int32 Foo; UPROPERTY() int32 Bar; };

#### enum `FConcertPropertyChain::EToStringMethod`  
`enum class EToStringMethod`  
_L64-68_
- L66 _public enumerator_ `Path`
- L67 _public enumerator_ `LeafProperty`

#### struct `FConcertPropertySelection`  
`struct FConcertPropertySelection`  
_L133-175_
- reflection: `USTRUCT()`
- desc: List of properties to be replicated for a given object
- L139 _public member_ `TSet<FConcertPropertyChain> ReplicatedProperties;` — `UPROPERTY()` — List of replicated properties.
- L142 _public function_ `bool OverlapsWith(const FConcertPropertySelection& Other) const` — @return Whether this and Other contain at least one property that is the same.
- L145 _public function_ `bool Includes(const FConcertPropertySelection& Other) const` — @return Whether this includes all properties of Other
- L153 _public prototype_ `void DiscoverAndAddImplicitParentProperties();` — Adds all parent properties if they are missing. Suppose ReplicatedProperties = { ["Vector", "X"] }. After execution, it would be { ["Vector", "X"], ["Vector"] }
- L161 _public prototype_ `static bool EnumeratePropertyOverlaps( const TSet<FConcertPropertyChain>& First, const TSet<FConcertPropertyChain>& Second, TFunctionRef<EBreakBehavior(const FConcertPropertyChain&)> Callback = [](const FConcertPropertyChain&){ return EBreakBehavior::Break; } );` — Determines all properties that overlap. This algorithm is strictly O(n^2) but runs O(n) on average. @return Whether there were any property overlaps.
- L164 _public function_ `const TSet<FConcertPropertyChain>& First, const TSet<FConcertPropertyChain>& Second, TFunctionRef<EBreakBehavior(const FConcertPropertyChain&)> Callback = [](const FConcertPropertyChain&)`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API CONCERTSYNCCORE_API`
- L71 _function_ `friend bool operator==(const FConcertPropertyChain& Left, const FConcertPropertyChain& Right)`
- L72 _function_ `friend bool operator!=(const FConcertPropertyChain& Left, const FConcertPropertyChain& Right)`
- L74 _function_ `friend bool operator==(const FConcertPropertyChain& Left, const TArray<FName>& Path)`
- L75 _function_ `friend bool operator!=(const FConcertPropertyChain& Left, const TArray<FName>& Path)`
- L77 _function_ `friend bool operator==(const TArray<FName>& Path, const FConcertPropertyChain& Left)`
- L78 _function_ `friend bool operator!=(const TArray<FName>& Path, const FConcertPropertyChain& Left)`
- L167 _function_ `friend bool operator==(const FConcertPropertySelection& Left, const FConcertPropertySelection& Right)`
- L171 _function_ `friend bool operator!=(const FConcertPropertySelection& Left, const FConcertPropertySelection& Right)`
- L177 _namespace_ `namespace UE`
- L177 _namespace_ `namespace ConcertSyncCore` (scope `UE`)
- L183 _prototype_ `uint32 ComputeHashForPropertyChainContent(const TArray<FName>& PropertyChain);` (scope `UE::ConcertSyncCore`) — Implementation of hashing FConcertPropertyChain. Allows you to use TSet::ContainsByHash without constructing a FConcertPropertyChain, which is expensive because it searches the property tree. You can rely on the fact that this function is either updated or deprecated when the hasing algorithm for FConcertPropertyChain is changed.
- L185 _function_ `inline uint32 GetTypeHash(const FConcertPropertyChain& Chain)`

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncCore/Source/ConcertSyncCore/Public/Replication/Data/ObjectIds.h` (Public)


#### struct `FConcertObjectInStreamID`  
`struct FConcertObjectInStreamID`  
_L11-33_
- reflection: `USTRUCT()`
- desc: Utility for identifying an object part of a replication stream definition.
- L17 _public member_ `FGuid StreamId;` — `UPROPERTY()` — The replication stream that produces data for this object.
- L20 _public member_ `FSoftObjectPath Object;` — `UPROPERTY()` — The object to process
- L22 _public function_ `FString ToString() const`

#### struct `FConcertReplicatedObjectId`  
`struct FConcertReplicatedObjectId : public FConcertObjectInStreamID`  
_L37-57_
- reflection: `USTRUCT()`
- inherits: `FConcertObjectInStreamID`
- desc: Identifies an object that was replicated by a client based on an underlying stream.
- L42 _public member_ `FGuid SenderEndpointId;` — The ID of the endpoint that sent this object. This can be the client or server endpoint depending on who receives it.
- L44 _public function_ `FString ToString() const`
- L45 _public function_ `FString ToString(const FString& ClientName) const`

#### struct `FConcertObjectInStreamArray`  
`struct FConcertObjectInStreamArray`  
_L60-66_
- reflection: `USTRUCT()`
- L65 _public member_ `TArray<FConcertObjectInStreamID> Objects;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L24 _function_ `friend bool operator==(const FConcertObjectInStreamID& Left, const FConcertObjectInStreamID& Right)`
- L29 _function_ `friend bool operator!=(const FConcertObjectInStreamID& Left, const FConcertObjectInStreamID& Right)`
- L47 _function_ `friend bool operator==(const FConcertReplicatedObjectId& Left, const FConcertReplicatedObjectId& Right)`
- L53 _function_ `friend bool operator!=(const FConcertReplicatedObjectId& Left, const FConcertReplicatedObjectId& Right)`
- L68 _prototype_ `uint32 GetTypeHash(const FConcertObjectInStreamID& StreamObject);`
- L69 _prototype_ `uint32 GetTypeHash(const FConcertReplicatedObjectId& StreamObject);`

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncCore/Source/ConcertSyncCore/Public/Replication/Data/ObjectReplicationMap.h` (Public)


#### struct `FConcertReplicatedObjectInfo`  
`struct FConcertReplicatedObjectInfo`  
_L10-44_
- reflection: `USTRUCT()`
- L16 _public member_ `FSoftClassPath ClassPath;` — `UPROPERTY()` — The exact class of the object being replicated.
- L20 _public member_ `FConcertPropertySelection PropertySelection;` — `UPROPERTY()` — The properties to replicate for the object
- L23 _public function_ `static FConcertReplicatedObjectInfo Make(const UObject& Object)` — Use static factories instead of user-provided constructors to continue allowing brace-initialization
- L29 _public function_ `bool IsValidForSendingToServer() const` — @return Whether this data is valid for sending to the server.

#### struct `FConcertObjectReplicationMap`  
`struct FConcertObjectReplicationMap`  
_L48-82_
- reflection: `USTRUCT()`
- desc: Maps objects to their replicated properties.
- L59 _public member_ `TMap<FSoftObjectPath, FConcertReplicatedObjectInfo> ReplicatedObjects;` — `UPROPERTY()` — List of replicated objects. Can be actors or its subobjects. Technically, this can also be non-UWorld objects.
- L62 _public function_ `bool HasProperties(const FSoftObjectPath& ObjectPath) const` — @return Whether ObjectPath has any properties assigned to it.
- L69 _public function_ `bool IsEmpty() const` — @return Whether there are any properties assigned.

#### Free symbols / members of external scopes

- L35 _function_ `friend bool operator==(const FConcertReplicatedObjectInfo& Left, const FConcertReplicatedObjectInfo& Right)`
- L40 _function_ `friend bool operator!=(const FConcertReplicatedObjectInfo& Left, const FConcertReplicatedObjectInfo& Right)`
- L74 _function_ `friend bool operator==(const FConcertObjectReplicationMap& Left, const FConcertObjectReplicationMap& Right)`
- L78 _function_ `friend bool operator!=(const FConcertObjectReplicationMap& Left, const FConcertObjectReplicationMap& Right)`

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncCore/Source/ConcertSyncCore/Public/Replication/Data/ReplicationActionEntry.h` (Public)


#### struct `FConcertReplicationActionEntry`  
`struct FConcertReplicationActionEntry`  
_L12-23_
- reflection: `USTRUCT()`
- desc: Defines an action that should be performed when a property is replicated.
- L18 _public member_ `TInstancedStruct<FConcertReplicationAction> Action;` — `UPROPERTY(EditAnywhere, Category = "Replication")` — The action to perform when a property is matched.
- L22 _public member_ `TArray<TFieldPath<FProperty>> Properties;` — `UPROPERTY(EditAnywhere, Category = "Replication")` — If any of these properties is replicated, perform Action on the replicated object.

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncCore/Source/ConcertSyncCore/Public/Replication/Data/ReplicationFrequencySettings.h` (Public)


#### enum `EConcertObjectReplicationMode`  
`enum class EConcertObjectReplicationMode : uint8`  
_L9-20_
- reflection: `UENUM()`
- L12 _public enumerator_ `SpecifiedRate` — Replicate at the rate specified at FConcertReplicatedObjectInfo::ReplicationRate
- L14 _public enumerator_ `Realtime` — Replicate the object as often as possible: every tick.
- L19 _public enumerator_ `Count` — Not a real mode.

#### enum `UE::ConcertSyncCore::ECanProcessObject`  
`enum class ECanProcessObject : uint8`  
_L24-30_
- L27 _public enumerator_ `CanProcess` — Enough time has elapsed: the object can be processed.
- L29 _public enumerator_ `TooEarly` — Not enough time has elapsed: wait with processing the object.

#### struct `FConcertObjectReplicationSettings`  
`struct FConcertObjectReplicationSettings`  
_L35-115_
- reflection: `USTRUCT()`
- desc: Specifies replication frequency settings for a single object.
- L41 _public member_ `EConcertObjectReplicationMode ReplicationMode = EConcertObjectReplicationMode::SpecifiedRate;` — `UPROPERTY(EditAnywhere, Category = "Concert")` — Controls how often this object should be replicated.
- L50 _public member_ `uint8 ReplicationRate = 30;` — `UPROPERTY(EditAnywhere, Category = "Concert")` — How often per second the object is supposed to be replicated per second. The update in seconds is given by 1 / ReplicationRate. The default rate of 30 results in an update interval every 0.033s
- L52 _public function_ `bool IsValid() const`
- L59 _public function_ `UE::ConcertSyncCore::ECanProcessObject CanProcessObject(const double LastTimeProcessed, const double Now = FPlatformTime::Seconds()) const` — Whether an object with this config can be replicated given the current time and the time it was last replicated. @param LastTimeProcessed The time the object was last processed - past result of FPlatformTime::Seconds() @param Now The current time - result of FPlatformTime::Seconds(). Pass this in to avoid excessive time spent on timing
- L76 _public function_ `double GetUpdateIntervalInSeconds() const` — Gets the time to wait between frames replicating an object with this config.

#### struct `FConcertStreamFrequencySettings`  
`struct FConcertStreamFrequencySettings`  
_L119-150_
- reflection: `USTRUCT()`
- desc: Specifies replication frequency settings for an entire stream.
- L125 _public member_ `FConcertObjectReplicationSettings Defaults;` — `UPROPERTY()` — Settings for all objects by default.
- L133 _public member_ `TMap<FSoftObjectPath, FConcertObjectReplicationSettings> ObjectOverrides;` — `UPROPERTY()` — Special settings to use for specific objects. Overrides DefaultSettings. May contain the same values as in DefaultSettings. Only contains entries for objects that are registered in the corresponding stream.
- L135 _public function_ `const FConcertObjectReplicationSettings& GetSettingsFor(const FSoftObjectPath& Object) const`

#### Free symbols / members of external scopes

- L22 _namespace_ `namespace UE`
- L22 _namespace_ `namespace ConcertSyncCore` (scope `UE`)
- L83 _function_ `friend bool operator==(const FConcertObjectReplicationSettings& Left, const FConcertObjectReplicationSettings& Right)`
- L88 _function_ `friend bool operator!=(const FConcertObjectReplicationSettings& Left, const FConcertObjectReplicationSettings& Right)`
- L94 _function_ `friend bool operator<(const FConcertObjectReplicationSettings& Left, const FConcertObjectReplicationSettings& Right)` — @return Whether Left replicates less frequently than Right.
- L105 _function_ `friend bool operator<=(const FConcertObjectReplicationSettings& Left, const FConcertObjectReplicationSettings& Right)` — @return Whether Left replicates less or equally frequently than Right.
- L141 _function_ `friend bool operator==(const FConcertStreamFrequencySettings& Left, const FConcertStreamFrequencySettings& Right)`
- L146 _function_ `friend bool operator!=(const FConcertStreamFrequencySettings& Left, const FConcertStreamFrequencySettings& Right)`

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncCore/Source/ConcertSyncCore/Public/Replication/Data/ReplicationStream.h` (Public)


#### enum `UE::ConcertSyncCore::EReplicationStreamCloneFlags`  
`enum class EReplicationStreamCloneFlags : uint8`  
_L14-19_
- L16 _public enumerator_ `None`
- L17 _public enumerator_ `SkipProperties = 1 << 0`
- L18 _public enumerator_ `SkipFrequency = 1 << 1`

#### struct `FConcertBaseStreamInfo`  
`struct FConcertBaseStreamInfo`  
_L30-73_
- reflection: `USTRUCT()`
- desc: Holds the base info of a replication stream: it knows the data that was registered to be sent and at what frequency. This struct exists to future proof the change UE-190167, which will add UObject rule objects to streams. When that happens, this struct holds all non-UObject data for the stream.
- L36 _public member_ `FGuid Identifier;` — `UPROPERTY()` — Unique id for this stream.
- L40 _public member_ `FConcertObjectReplicationMap ReplicationMap;` — `UPROPERTY()` — Identifies the data that this stream will send.
- L58 _public member_ `FConcertStreamFrequencySettings FrequencySettings;` — `UPROPERTY()` — Determines how often updates are sent for objects. The purposes of registering frequency with the server communicates the sending client's intent and has these advantages: - If the server receives replicated data more often than specified here, it will combine and throttle the events forwarded to the other clients. - The receiving clients can query how often per frame to expect updates for an object On a technical level, this field is not required for replicating objects: in a hypothetical, alternate implementation, the sending client could just keep the replication frequency local to themselves and send at the rate it wants to send. This field is here mostly to allow inspection by other parties, which does add overhead (engineering and runtime) because we must support FConcertReplication_ChangeStream_Frequency requests). With that said, the sending implementation uses the rate that is specified here to throttle the rate at which it sends update to the server. @see FObjectReplicationProcessor::ProcessObjects.
- L61 _public prototype_ `FConcertBaseStreamInfo Clone(UE::ConcertSyncCore::EReplicationStreamCloneFlags Flags = UE::ConcertSyncCore::EReplicationStreamCloneFlags::None) const;` — Util for efficiently cloning stream info and optionally skipping some info.
- L111 _function_ `inline FConcertBaseStreamInfo FConcertBaseStreamInfo::Clone(UE::ConcertSyncCore::EReplicationStreamCloneFlags Flags) const`

#### struct `FConcertReplicationStream`  
`struct FConcertReplicationStream`  
_L94-109_
- reflection: `USTRUCT()`
- desc: A replication stream a related set of data that is to be replicated. The application using this frame work (e.g. Multi User) defines what it means for data to be "related". The stream defines: - a map of objects to their replicated properties, - at what frequencies the data replicates, - a set of stream attributes which receiving clients can use to tell the server what data they want to receive (rules are TODO UE-190167) Streams exist mostly for logical grouping and organization. It is completely acceptable for an application to only register one stream per client (Multi User does this). However, there is a minor technical detail: While streams registered by the same client can replicate the same UObjects (and even overlap properties), streams send data independently. The consequence is that each stream: - has its own frequency counter - streams data is not combined / merged (i.e. there is an overhead of the book-keeping data that is sent with each update). This struct only contains FConcertBaseStreamInfo for to future proof the change UE-190167, which will add rule data to streams. When that happens, this struct holds all the UObject rule data for the stream while FConcertBaseStreamInfo will continue to hold non-UObject data.
- L99 _public member_ `FConcertBaseStreamInfo BaseDescription;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace ConcertSyncCore` (scope `UE`)
- L63 _function_ `friend bool operator==(const FConcertBaseStreamInfo& Left, const FConcertBaseStreamInfo& Right)`
- L69 _function_ `friend bool operator!=(const FConcertBaseStreamInfo& Left, const FConcertBaseStreamInfo& Right)`
- L101 _function_ `friend bool operator==(const FConcertReplicationStream& Left, const FConcertReplicationStream& Right)`
- L105 _function_ `friend bool operator!=(const FConcertReplicationStream& Left, const FConcertReplicationStream& Right)`

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncCore/Source/ConcertSyncCore/Public/Replication/Data/ReplicationStreamArray.h` (Public)


#### struct `FConcertReplicationStreamArray`  
`struct FConcertReplicationStreamArray`  
_L9-15_
- reflection: `USTRUCT()`
- L14 _public member_ `TArray<FConcertReplicationStream> Streams;` — `UPROPERTY()`

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncCore/Source/ConcertSyncCore/Public/Replication/Data/SequenceId.h` (Public)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace ConcertSyncCore` (scope `UE`)
- L14 _typedef_ `using FSequenceId = uint32;` (scope `UE::ConcertSyncCore`) — A sequence ID is associated with every update made to a replicated object. Every time a replicated change is sent, the ID is incremented by the original data source. This is used primarily for tracing object replication performance.

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncCore/Source/ConcertSyncCore/Public/Replication/Formats/FullObjectFormat.h` (Public)


#### class `UE::ConcertSyncCore::FFullObjectFormat`  
`class FFullObjectFormat : public IObjectReplicationFormat`  
_L22-32_
- inherits: `IObjectReplicationFormat`
- desc: Full object format is a blob of serialized UObject data. Since there no additional property information in this format, the server cannot merge data. Every update the entire blob must be sent. This format is inefficient. The only upside it that it is straight-forward to understand. This format is used for the initial Concert Replication prototype. TODO: After the prototype phase, more efficient formats should be developed. @see FFullObjectReplicationData
- L27 _public prototype_ `virtual TOptional<FConcertSessionSerializedPayload> CreateReplicationEvent(UObject& Object, FAllowPropertyFunc IsPropertyAllowedFunc) override;`
- L28 _public function_ `virtual void ClearInternalCache(TArrayView<UObject> ObjectsToClear) override`
- L29 _public prototype_ `virtual void CombineReplicationEvents(FConcertSessionSerializedPayload& Base, const FConcertSessionSerializedPayload& Newer) override;`
- L30 _public prototype_ `virtual void ApplyReplicationEvent(UObject& Object, const FConcertSessionSerializedPayload& Payload, const FOnPropertyVisitedFunc& OnPrePropertySerialized) override;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API CONCERTSYNCCORE_API`
- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace ConcertSyncCore` (scope `UE`)

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncCore/Source/ConcertSyncCore/Public/Replication/Formats/FullObjectReplicationData.h` (Public)


#### struct `FFullObjectReplicationData`  
`struct FFullObjectReplicationData`  
_L13-19_
- reflection: `USTRUCT()`
- desc: Full object format is a blob of serialized UObject data. @see FFullObjectFormat
- L18 _public member_ `FConcertByteArray SerializedObjectData;` — `UPROPERTY()`

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncCore/Source/ConcertSyncCore/Public/Replication/Formats/IObjectReplicationFormat.h` (Public)


#### class `UE::ConcertSyncCore::IObjectReplicationFormat`  
`class IObjectReplicationFormat`  
_L24-74_
- desc: Abstracts the concept of a replication format for data passed into FConcertReplicationEvent::SerializedPayload. Example implementations: - full-object format that serializes all replicated properties and never does any combining (inefficient). - partial-object format that keeps track of past properties and only sends changed replicated properties.
- L29 _public typedef_ `using FAllowPropertyFunc = TFunctionRef<bool(const FArchiveSerializedPropertyChain* Chain, const FProperty& Property)>;` — Chain can be nullptr or non-null and empty - both imply the Property is a root property.
- L30 _public typedef_ `using FOnPropertyVisitedFunc = TFunctionRef<void(const FArchiveSerializedPropertyChain&, FProperty&)>;`
- L46 _public prototype_ `virtual TOptional<FConcertSessionSerializedPayload> CreateReplicationEvent(UObject& Object, FAllowPropertyFunc IsPropertyAllowedFunc) = 0;` — Produces a new payload from Object. TODO: Probably the signature of this function will be extended so you can build from a passed-in FConcertSessionSerializedPayload. Maybe for server sending to clients. Implementations may create a diff from a previous version of the Object. This function may update the internal cache. If there is not data to apply since the last call, then this returns an empty optional. @param Object The object to serialize @param IsPropertyAllowedFunc Decides whether a given property is generally supposed to be replicated. Note: IObjectReplicationFormat does diffing itself - only return whether you ever want to replicate the property! @return	Data to be placed into FConcertReplicationEvent::SerializedPayload. This can be a diff from the last time CreateReplicationEvent was called. If there is no data to apply since the last time, the optional is empty.
- L52 _public prototype_ `virtual void ClearInternalCache(TArrayView<UObject> ObjectsToClear) = 0;` — Clears the internal cache that subclass implementations may rely on for building diffed payload version in CreateReplicationEvent. The next call to CreateReplicationEvent will serialize all data.
- L61 _public prototype_ `virtual void CombineReplicationEvents(FConcertSessionSerializedPayload& Base, const FConcertSessionSerializedPayload& Newer) = 0;` — Combines Base and Newer to form a single payload. Calling ApplyReplicationEvent(CombineReplicationEvents(Base, Other)) should be equivalent to calling ApplyReplicationEvent(Base) followed by ApplyReplicationEvent(Newer). @param Base Payload produced by CreateReplicationEvent. Produced before Newer. This will be overwritten to contain the combined result. @param Newer Payload produced by CreateReplicationEvent. Produced after Base and on the same UObject.
- L69 _public prototype_ `virtual void ApplyReplicationEvent(UObject& Object, const FConcertSessionSerializedPayload& Payload, const FOnPropertyVisitedFunc& OnPrePropertySerialized = [](const FArchiveSerializedPropertyChain&, FProperty&){} ) = 0;` — Applies Payload to Object. @param Object The object to apply to @param Payload The payload to apply. Must have been created via CreateReplicationEvent. @param OnPrePropertySerialized Invoked when a property is about to be serialized. Useful for determining whether e.g. render state needs to be dirtied, etc.
- L70 _public function_ `virtual void ApplyReplicationEvent(UObject& Object, const FConcertSessionSerializedPayload& Payload, const FOnPropertyVisitedFunc& OnPrePropertySerialized = [](const FArchiveSerializedPropertyChain&, FProperty&){} ) = 0;` — Applies Payload to Object. @param Object The object to apply to @param Payload The payload to apply. Must have been created via CreateReplicationEvent. @param OnPrePropertySerialized Invoked when a property is about to be serialized. Useful for determining whether e.g. render state needs to be dirtied, etc.
- L73 _public prototype_ `virtual ~IObjectReplicationFormat() = default;`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace ConcertSyncCore` (scope `UE`)

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncCore/Source/ConcertSyncCore/Public/Replication/Messages/ChangeAuthority.h` (Public)


#### struct `FConcertStreamArray`  
`struct FConcertStreamArray`  
_L10-16_
- reflection: `USTRUCT()`
- L15 _public member_ `TArray<FGuid> StreamIds;` — `UPROPERTY()`

#### struct `FConcertReplication_ChangeAuthority_Request`  
`struct FConcertReplication_ChangeAuthority_Request`  
_L26-50_
- reflection: `USTRUCT()`
- desc: Sent by clients to the server to attempt to take or release authority over properties on objects. Clients must have authority over object properties before sending FConcertBatchReplicationEvent, or the server will reject the updates. Multiple clients can have authority over the same objects as long as the properties do not overlap. The properties are defined implicitly by providing the stream ID that will be writing the properties.
- L38 _public member_ `TMap<FSoftObjectPath, FConcertStreamArray> TakeAuthority;` — `UPROPERTY()` — Objects the client requests to take authority over. Mapping of object to stream identifiers the client has previously registered.
- L47 _public member_ `TMap<FSoftObjectPath, FConcertStreamArray> ReleaseAuthority;` — `UPROPERTY()` — Objects the client no longer needs authority over. Mapping of object to stream identifiers the client has previously registered. The request will not fail if it contains objects it has no authority over.
- L49 _public function_ `bool IsEmpty() const`

#### struct `FConcertReplication_ChangeAuthority_Response`  
`struct FConcertReplication_ChangeAuthority_Response`  
_L53-77_
- reflection: `USTRUCT()`
- L59 _public member_ `EReplicationResponseErrorCode ErrorCode = EReplicationResponseErrorCode::Timeout;` — `UPROPERTY()` — Concert's custom requests are default constructed when they timeout. Server always sets this to Handled when processed.
- L66 _public member_ `TMap<FSoftObjectPath, FConcertStreamArray> RejectedObjects;` — `UPROPERTY()` — Objects streams the client did not receive authority over. The client is implied to have authority over all other request objects.
- L76 _public member_ `FConcertReplication_ChangeSyncControl SyncControl;` — `UPROPERTY()` — Contains the new sync control for objects you requested authority over; objects you released authority over are not contained because they can be implicitly determined using FSyncControlState::AppendChanges. @see FSyncControlState::Aggregate. @see FConcertReplication_ChangeSyncControl

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncCore/Source/ConcertSyncCore/Public/Replication/Messages/ChangeClientEvent.h` (Public)


#### enum `EConcertReplicationChangeClientReason`  
`enum class EConcertReplicationChangeClientReason : uint8`  
_L11-18_
- reflection: `UENUM()`
- desc: A reason why a FConcertReplication_ChangeClientEvent is sent.
- L14 _public enumerator_ `Unknown` — The code is unknown
- L17 _public enumerator_ `PutRequest` — A FConcertReplication_PutState_Request edited this client.

#### struct `FConcertReplication_ClientChangeData`  
`struct FConcertReplication_ClientChangeData`  
_L22-37_
- reflection: `USTRUCT()`
- desc: Describes what aspects about a client have changed.
- L28 _public member_ `FConcertReplication_ChangeStream_Request StreamChange;` — `UPROPERTY()` — The change made to the client's streams.
- L32 _public member_ `FConcertReplication_ChangeAuthority_Request AuthorityChange;` — `UPROPERTY()` — The change made to the client's authority.
- L36 _public member_ `FConcertReplication_ChangeSyncControl SyncControlChange;` — `UPROPERTY()` — The change made to the client's sync control in response to the above changes.

#### struct `FConcertReplication_ChangeClientEvent`  
`struct FConcertReplication_ChangeClientEvent`  
_L44-55_
- reflection: `USTRUCT()`
- desc: Sent by server to notify a client that their stream content and / or authority has been changed by an external entity, i.e. when the change was not initiated by the client itself.
- L50 _public member_ `EConcertReplicationChangeClientReason Reason = EConcertReplicationChangeClientReason::Unknown;` — `UPROPERTY()` — The reason for this event
- L54 _public member_ `FConcertReplication_ClientChangeData ChangeData;` — `UPROPERTY()` — Info about what has changed.

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncCore/Source/ConcertSyncCore/Public/Replication/Messages/ChangeStream.h` (Public)


#### struct `FConcertReplication_ChangeStream_PutObject`  
`struct FConcertReplication_ChangeStream_PutObject`  
_L20-64_
- reflection: `USTRUCT()`
- desc: A request to add a new object to a stream or overwrite a pre-existing object's properties / class.
- L33 _public member_ `FConcertPropertySelection Properties;` — `UPROPERTY()` — The property selection the object should have. Objects must always have a non-empty selection: use FConcertChangeStream_Request::ObjectsToRemove to remove objects. Any request that would leave an object's property selection empty will result in failure.
- L42 _public member_ `FSoftClassPath ClassPath;` — `UPROPERTY()` — If Object is pre-existing, this property is optional. If different than None, this will change the class If a new object is added, this property is mandatory. Not doing so will fail the request. Not specifying ClassPath nor Properties is an error: use FConcertChangeStream_Request::ObjectsToRemove to remove objects.
- L58 _public prototype_ `static TOptional<FConcertReplication_ChangeStream_PutObject> MakeFromInfo(const FConcertReplicatedObjectInfo& New);` — @return The PutObject request if New contained sufficient info - empty otherwise
- L60 _public prototype_ `static TOptional<FConcertReplication_ChangeStream_PutObject> MakeFromChange(const FConcertReplicatedObjectInfo& Base, const FConcertReplicatedObjectInfo& Desired);` — @return The PutObject request if changing Base to Desired contained sufficient info - empty otherwise
- L63 _public prototype_ `TOptional<FConcertReplicatedObjectInfo> MakeObjectInfoIfValid() const;` — Creates a new object info if there is sufficient data (all fields must be set for this).

#### enum `EConcertReplicationChangeFrequencyFlags`  
`enum class EConcertReplicationChangeFrequencyFlags : uint8`  
_L67-72_
- reflection: `UENUM(Flags)`
- L69 _public enumerator_ `None = 0`
- L71 _public enumerator_ `SetDefaults = 1 << 0` — FConcertReplication_ChangeStream_Frequency::NewDefaults contains the new defaults to set.

#### struct `FConcertReplication_ChangeStream_Frequency`  
`struct FConcertReplication_ChangeStream_Frequency`  
_L77-115_
- reflection: `USTRUCT()`
- desc: Changes to set to make to the stream's replication frequency.
- L89 _public member_ `TMap<FSoftObjectPath, FConcertObjectReplicationSettings> OverridesToPut;` — `UPROPERTY()` — Replaces the entire overrides with this content. If a specified object is not specified in the associated stream, this request DOES fail. Usually you want to specify either OverridesToPut, or OverridesToPut & OverridesToRemove but not both. A put is useful for situations where you don't care what objects have been overriden thus far and want to straight out replace them all.
- L98 _public member_ `TSet<FSoftObjectPath> OverridesToRemove;` — `UPROPERTY()` — Removes the specified overrides. If a specified object is not specified in the associated stream, this request DOES NOT fail. Executed after OverridesToPut (but you should either use OverridesToPut, or OverridesToRemove & OverridesToAdd).
- L107 _public member_ `TMap<FSoftObjectPath, FConcertObjectReplicationSettings> OverridesToAdd;` — `UPROPERTY()` — Adds the specified overrides. If a specified object is not specified in the associated stream, this request DOES fail. Executed after OverridesToAdd (but you should either use OverridesToPut, or OverridesToRemove & OverridesToAdd).
- L111 _public member_ `FConcertObjectReplicationSettings NewDefaults;` — `UPROPERTY()` — Only applied if Flags contains the SetDefaults flag.
- L114 _public member_ `EConcertReplicationChangeFrequencyFlags Flags = EConcertReplicationChangeFrequencyFlags::None;` — `UPROPERTY()`

#### struct `FConcertReplication_ChangeStream_Request`  
`struct FConcertReplication_ChangeStream_Request`  
_L124-204_
- reflection: `USTRUCT()`
- desc: Let's a client change its streams owned on the server. This request is processed atomically: it either succeeds completely or fails completely. If any sub-change causes a failure, the failure reason will be returned in the response and the client must make a new request.
- L136 _public member_ `TSet<FConcertObjectInStreamID> ObjectsToRemove;` — `UPROPERTY()` — Removes objects from pre-existing streams. Supplying an object that is not in the specified stream does not cause failure (but is nonsensical). If a stream has no registered objects after this operation, it is automatically removed. If the requesting client has authority over these objects, authority is removed.
- L152 _public member_ `TMap<FConcertObjectInStreamID, FConcertReplication_ChangeStream_PutObject> ObjectsToPut;` — `UPROPERTY()` — Adds new or modifies preexisting object definitions in pre-existing streams. If the requesting client and a different client have authority over the same object, you will get a conflict if the different client already has authority over one of the properties you're adding here. @see FConcertChangeStream_Response::AuthorityConflicts for some examples of conflicts. If the key identifies a stream that does not exist, the request will fail. TODO UE-201167: Make the request no longer fail If the key identifies a stream that is in StreamsToAdd, the request will fail to avoid allowing the construction of ambiguous requests, e.g. both StreamsToAdd and ObjectsToPut containing object Foo but with different property selections.
- L164 _public member_ `TMap<FGuid, FConcertReplication_ChangeStream_Frequency> FrequencyChanges;` — `UPROPERTY()` — Changes the replication frequency settings for a stream. If a specified stream does not exist, the request fails. Specifying a request that changes nothing does not result in any failure. TODO UE-201167: Change StreamsToAdd such that no ambiguous requests are even possible and update this doc's wording. If the key may identify a stream that is in StreamsToAdd, in which case the frequency is what is specified in FrequencyChanges.
- L176 _public member_ `TArray<FConcertReplicationStream> StreamsToAdd;` — `UPROPERTY()` — New streams to add to the server. Fails if any ID overlaps with a pre-existing one. It is valid to have the same stream in StreamsToRemove: StreamsToAdd is applied after StreamsToRemove resulting in the stream's content being replaced.
- L188 _public member_ `TSet<FGuid> StreamsToRemove;` — `UPROPERTY()` — Streams to remove from the server. Supplying a stream that does not exist does not cause failure (but is nonsensical). If the requesting client has authority over any of the objects contained in the stream, authority is removed. It is valid to have the same stream in StreamsToAdd: StreamsToAdd is applied after StreamsToRemove resulting in the stream's content being replaced.
- L190 _public function_ `bool IsEmpty() const`

#### enum `EConcertPutObjectErrorCode`  
`enum class EConcertPutObjectErrorCode : uint8`  
_L207-219_
- reflection: `UENUM()`
- L210 _public enumerator_ `UnresolvedStream` — Stream that ObjectsToPut referenced was not registered on the server.
- L215 _public enumerator_ `MissingData` — Either PutObject contained no data to update with (ensure either ClassPath or Properties is set), or it tried to create a new object with insufficient data (make sure ClassPath and Properties are both specified).
- L218 _public enumerator_ `Count` — Not an actual parameter. Make sure it's always last.

#### enum `EConcertChangeObjectFrequencyErrorCode`  
`enum class EConcertChangeObjectFrequencyErrorCode : uint8`  
_L222-231_
- reflection: `UENUM()`
- L225 _public enumerator_ `NotRegistered` — The object for which the frequency was being changed was not registered.
- L227 _public enumerator_ `InvalidReplicationRate` — The replication rate parameter was rejected (it cannot be 0).
- L230 _public enumerator_ `Count` — Not an actual parameter. Make sure it's always last.

#### enum `EConcertChangeStreamFrequencyErrorCode`  
`enum class EConcertChangeStreamFrequencyErrorCode : uint8`  
_L234-243_
- reflection: `UENUM()`
- L237 _public enumerator_ `UnknownStream` — The stream was not registered
- L239 _public enumerator_ `InvalidReplicationRate` — The replication rate parameter was rejected (it cannot be 0).
- L242 _public enumerator_ `Count` — Not an actual parameter. Make sure it's always last.

#### struct `FConcertReplication_ChangeStream_FrequencyResponse`  
`struct FConcertReplication_ChangeStream_FrequencyResponse`  
_L246-260_
- reflection: `USTRUCT()`
- L252 _public member_ `TMap<FConcertObjectInStreamID, EConcertChangeObjectFrequencyErrorCode> OverrideFailures;` — `UPROPERTY()` — Streams that could not have their frequencies overriden.
- L256 _public member_ `TMap<FGuid, EConcertChangeStreamFrequencyErrorCode> DefaultFailures;` — `UPROPERTY()` — Streams that could not have their frequency defaults overriden.
- L258 _public function_ `bool IsSuccess() const`
- L259 _public function_ `bool IsFailure() const`

#### struct `FConcertReplication_ChangeStream_Response`  
`struct FConcertReplication_ChangeStream_Response`  
_L267-316_
- reflection: `USTRUCT()`
- desc: Contains information about why a request failed. This info could be parsed and displayed to the end user as error. If there is even just one error, the entire request fails and no changes are made server-side.
- L273 _public member_ `EReplicationResponseErrorCode ErrorCode = EReplicationResponseErrorCode::Timeout;` — `UPROPERTY()` — Concert's custom requests are default constructed when they timeout. Server always sets this to Handled when processed.
- L291 _public member_ `TMap<FConcertObjectInStreamID, FConcertReplicatedObjectId> AuthorityConflicts;` — `UPROPERTY()` — Reports dynamic authority errors with ObjectsToPut: Changing an object over which a client already has authority can yield unresolvable conflicts for which the entire FConcertChangeStream_Request is rejected. Let client R be the requester and client A be another client. Example 1: Overlapping authority on different clients > Conflict - R has authority over Foo's relative rotation property in stream S. - A has authority over actor Foo's relative location property in some stream. - R requests S to include Foo's relative location property: this conflicts with client A's authority. Example 2: Overlapping, properties on same client > No conflict There is no conflict if another stream owned by the requester already has authority over a property you're adding to a different stream. Streams of the same client may overlap properties. While this may not make much sense and actually be performance degrading, it would result in no logical errors so it is allowed. Example: R has two streams S1 and S2. S1 contains the transform properties and S2 does not. Both S1 and S2 have authority over object Foo. It is legal to request S2 to contain the transform properties.
- L295 _public member_ `TMap<FConcertObjectInStreamID, EConcertPutObjectErrorCode> ObjectsToPutSemanticErrors;` — `UPROPERTY()` — Reports semantic errors with ObjectsToPut.
- L299 _public member_ `TSet<FGuid> FailedStreamCreation;` — `UPROPERTY()` — Streams that were in StreamsToAdd but that were not created (stream was already registered, or was empty).
- L303 _public member_ `FConcertReplication_ChangeStream_FrequencyResponse FrequencyErrors;` — `UPROPERTY()` — Errors updating the frequency
- L305 _public function_ `bool IsSuccess() const`
- L313 _public function_ `bool IsFailure() const`
- L315 _public function_ `bool WasObjectPutSuccessful(const FConcertObjectInStreamID& Object) const`

#### Free symbols / members of external scopes

- L44 _function_ `friend bool operator==(const FConcertReplication_ChangeStream_PutObject& Left, const FConcertReplication_ChangeStream_PutObject& Right)`
- L49 _function_ `friend bool operator!=(const FConcertReplication_ChangeStream_PutObject& Left, const FConcertReplication_ChangeStream_PutObject& Right)`
- L73 _prototype_ `ENUM_CLASS_FLAGS(EConcertReplicationChangeFrequencyFlags);`
- L192 _function_ `friend bool operator==(const FConcertReplication_ChangeStream_Request& Left, const FConcertReplication_ChangeStream_Request& Right)`
- L194 _function_ `const auto OrderIndependentEquals = [](const auto& Left, const auto& Right)` (scope `FConcertReplication_ChangeStream_Request::operator ==`)
- L200 _function_ `friend bool operator!=(const FConcertReplication_ChangeStream_Request& Lhs, const FConcertReplication_ChangeStream_Request& RHS)`

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncCore/Source/ConcertSyncCore/Public/Replication/Messages/ClientQuery.h` (Public)


#### enum `EConcertQueryClientStreamFlags`  
`enum class EConcertQueryClientStreamFlags : uint8`  
_L11-33_
- reflection: `UENUM()`
- desc: Flags to affect FConcertQueryClientStreams_Request
- L13 _public enumerator_ `None = 0`
- L16 _public enumerator_ `SkipStreamInfo = 1 << 0` — If set, FReplicationClientQueriedInfo::Streams will be empty.
- L23 _public enumerator_ `SkipProperties = 1 << 1` — Optimization. The returned streams will not contain the properties that are sent. Set this if the request only cares for the objects being replicated but not its content. Only has an effect if SkipStreamInfo is not set.
- L26 _public enumerator_ `SkipAuthority = 1 << 2` — If set, FReplicationClientQueriedInfo::Authority will be empty.
- L32 _public enumerator_ `SkipFrequency = 1 << 3` — Optimization. Ignored if SkipStreamInfo is set. If set, FReplicationClientQueriedInfo::Streams.FrequencySettings will not be set.

#### struct `FConcertReplication_QueryReplicationInfo_Request`  
`struct FConcertReplication_QueryReplicationInfo_Request`  
_L44-54_
- reflection: `USTRUCT()`
- desc: Allows a client query about another client's registered streams. Currently, clients must continuously poll to detect when a client changes this data. TODO: Add an event with which clients can be notified when another client changes their profile. TODO: Alternative to an event, we can add a version int which is incremented every time the info changes.
- L50 _public member_ `TSet<FGuid> ClientEndpointIds;` — `UPROPERTY()` — The clients to query about
- L53 _public member_ `EConcertQueryClientStreamFlags QueryFlags = EConcertQueryClientStreamFlags::None;` — `UPROPERTY()`

#### struct `FConcertReplication_QueryReplicationInfo_Response`  
`struct FConcertReplication_QueryReplicationInfo_Response`  
_L57-77_
- reflection: `USTRUCT()`
- L63 _public member_ `EReplicationResponseErrorCode ErrorCode = EReplicationResponseErrorCode::Timeout;` — `UPROPERTY()` — Concert's custom requests are default constructed when they timeout. Server always sets this to Handled when processed.
- L76 _public member_ `TMap<FGuid, FConcertQueriedClientInfo> ClientInfo;` — `UPROPERTY()` — Binds client participating in the replication session to their info. @note This contains only the client endpoint IDs that are in the replication session at the time of processing the request. That means not every endpoint ID that was in the request's ClientEndpointIds will necessarily be in this result. For example, if client A sends a FConcertQueryReplicationInfo_Request while client B disconnects, client B may not show up in ClientInfo. Key: Client endpoint ID. Value: Info about the client.

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncCore/Source/ConcertSyncCore/Public/Replication/Messages/EReplicationResponseErrorCode.h` (Public)


#### enum `EReplicationResponseErrorCode`  
`enum class EReplicationResponseErrorCode : uint8`  
_L15-21_
- reflection: `UENUM()`
- desc: Added as field to all replication response data. Used to detect timeouts or other delivery failures. Custom requests and responses are considered failed if they are default constructed. The default constructed responses should be EReplicationResponseErrorCode::Timout by default.
- L18 _public enumerator_ `Timeout` — Value to set when default constructed. Indicates responses not received.
- L20 _public enumerator_ `Handled` — Set when request was handled and there is valid response data

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncCore/Source/ConcertSyncCore/Public/Replication/Messages/Handshake.h` (Public)


#### enum `EJoinReplicationErrorCode`  
`enum class EJoinReplicationErrorCode : uint8`  
_L12-47_
- reflection: `UENUM()`
- L14 _public enumerator_ `Success = 0`
- L16 _public enumerator_ `NetworkError = 1` — Indicates generic error obtaining a response from the server. Responses are default constructed if an error occurs. This is the default value.
- L21 _public enumerator_ `Cancelled = 2` — Cancelled while initialization was in progress. Most likely LeaveReplicationSession was called while handshake was in progress.
- L23 _public enumerator_ `AlreadyInProgress = 3` — Another request is already in progress.
- L32 _public enumerator_ `NotInAnyConcertSession = 4` — Client is not in any session but has requested to join a replication session. This case should never happen under normal conditions e.g. when using Multi User Browser, but malicious users could make invalid requests.
- L34 _public enumerator_ `AlreadyInSession = 5` — Client has already joined a replication session. Send FConcertLeaveReplicationSessionEvent first.
- L38 _public enumerator_ `InvalidClass = 6` — One of the specified classes was null or otherwise invalid
- L40 _public enumerator_ `DuplicateStreamId = 7` — Your input contained the same stream id twice.
- L42 _public enumerator_ `FailedToUnpackStream = 8` — Failed to unpack the stream, likely because one of the attribute classes could not be resolved.
- L44 _public enumerator_ `MaxPlusOne`
- L46 _public enumerator_ `Max = MaxPlusOne - 1` — The maximum possible entry value

#### struct `FConcertReplication_Join_Request`  
`struct FConcertReplication_Join_Request`  
_L59-66_
- reflection: `USTRUCT()`
- desc: Sent by client to request joining a replication session. This is sent by clients want to send or receive replicated data, or both.
- L65 _public member_ `TArray<FConcertReplicationStream> Streams;` — `UPROPERTY()` — The data the client offers to send.

#### struct `FConcertReplication_Join_Response`  
`struct FConcertReplication_Join_Response`  
_L72-92_
- reflection: `USTRUCT()`
- desc: Sent by server to accept the previously sent replication session.
- L83 _public member_ `EJoinReplicationErrorCode JoinErrorCode = EJoinReplicationErrorCode::NetworkError;` — `UPROPERTY()` — Anything other than Success indicates failure. Remember that Concert default constructs a response when it fails to obtain a response. Hence NetworkError means timeout, etc.
- L87 _public member_ `FString DetailedErrorMessage;` — `UPROPERTY()` — More information about ErrorCode to help the user resolve the issue.
- L91 _public member_ `FConcertReplication_ChangeSyncControl SyncControl;` — `UPROPERTY()` — This is the initial sync control this client has

#### struct `FConcertReplication_LeaveEvent`  
`struct FConcertReplication_LeaveEvent`  
_L96-99_
- reflection: `USTRUCT()`
- desc: Sent by client to notify server that no more replication data should be sent.

#### Free symbols / members of external scopes

- L49 _namespace_ `namespace UE`
- L49 _namespace_ `namespace ConcertSyncCore` (scope `UE`)
- L49 _namespace_ `namespace Replication` (scope `UE::ConcertSyncCore`)
- L51 _prototype_ `FString LexJoinErrorCode(EJoinReplicationErrorCode ErrorCode);` (scope `UE::ConcertSyncCore::Replication`)

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncCore/Source/ConcertSyncCore/Public/Replication/Messages/Muting.h` (Public)


#### enum `EConcertReplicationMuteOption`  
`enum class EConcertReplicationMuteOption : uint8`  
_L13-19_
- reflection: `UENUM()`
- L16 _public enumerator_ `OnlyObject` — Only the specified object is affected; subobjects are not.
- L18 _public enumerator_ `ObjectAndSubobjects = 1 << 0` — The setting applies for all subobjects of the object as well. If subobjects are added in the future, the setting will apply to them as well.

#### struct `FConcertReplication_ObjectMuteSetting`  
`struct FConcertReplication_ObjectMuteSetting`  
_L29-38_
- reflection: `USTRUCT()`
- desc: Describes how an object is to be muted.
- L35 _public member_ `EConcertReplicationMuteOption Flags = EConcertReplicationMuteOption::ObjectAndSubobjects;` — `UPROPERTY()` — Modify the default behavior of the mute operation

#### enum `EConcertReplicationMuteRequestFlags`  
`enum class EConcertReplicationMuteRequestFlags : uint8`  
_L41-47_
- reflection: `UENUM(Flags)`
- L43 _public enumerator_ `None`
- L46 _public enumerator_ `ClearMuteState = 1 << 0` — Before the request is applied, all mute state is reset. This means that ObjectsToUnmute is effectively ignored and the mute state is replaced with what is saved in ObjectsToMute.

#### struct `FConcertReplication_ChangeMuteState_Request`  
`struct FConcertReplication_ChangeMuteState_Request`  
_L75-110_
- reflection: `USTRUCT()`
- desc: A request to globally pause / resume replication of objects. Muted objects will not be replicated to any clients. For security reasons, muting is only available in sessions with the EConcertSyncSessionFlags::ShouldAllowGlobalMuting flag set. If a muted objects is unregistered (i.e. by a stream change request), the mute state is also removed. That the object is later re-registered, it will not be muted. Requests are processed atomically: it is completed either completely or not at all. The following operations are invalid: - Unmuting / muting an object without the IncludeSubobjects flag if that object is not registered in any stream. - Unmuting / muting an object with the IncludeSubobjects flag if that object is not registered in any stream, and that object has no subobjects registered in any streams. The reason for making these operations invalid is to prevent memory leaks on the server (e.g. client unregisters an object and forgets to remove the mute state, too). The following operations are valid: - Unmuting an object that is already unmuted (no-op) - Muting an object that is already muted (no-op); changing the EConcertReplicationMuteFlags is not a no-op. Sync control: This request may update sync control. The following rules apply: - This request may cause FConcertReplication_ChangeSyncControl events to be sent to OTHER clients. - This request will NOT cause any FConcertReplication_ChangeSyncControl event to be sent to the requesting client: - When muting, the requesting c
- L81 _public member_ `EConcertReplicationMuteRequestFlags Flags = EConcertReplicationMuteRequestFlags::None;` — `UPROPERTY()` — Flags that modify the request's behavior.
- L85 _public member_ `TMap<FSoftObjectPath, FConcertReplication_ObjectMuteSetting> ObjectsToMute;` — `UPROPERTY()` — The objects to explicitly mute.
- L100 _public member_ `TMap<FSoftObjectPath, FConcertReplication_ObjectMuteSetting> ObjectsToUnmute;` — `UPROPERTY()` — The objects to explicitly unmute. If a specified object is implicitly muted, i.e. one of its outers is muted with the EConcertReplicationMuteFlags::ObjectAndSubobjects flag, this will allow it to replicate again. If you specify the EConcertReplicationMuteFlags::ObjectAndSubobjects flag, then its subobjects will also be allowed to be replicated again. If a specified object is explicitly muted, then it and all the subobjects that were implicitly muted because of it are unmuted; in this case, it does not matter whether EConcertReplicationMuteFlags::ObjectAndSubobjects flag is set. If Flags specifies ClearMuteState and ObjectsToUnmute is non-empty, the request is rejected.
- L109 _public function_ `bool IsEmpty() const` — @return Whether this requests makes no changes

#### enum `EConcertReplicationMuteErrorCode`  
`enum class EConcertReplicationMuteErrorCode : uint8`  
_L114-127_
- reflection: `UENUM()`
- desc: Result of a FConcertReplication_ChangeMuteState_Request.
- L120 _public enumerator_ `Timeout` — Value to set when default constructed (Concert does this to responses when they timeout or the request in invalid). Happens when timed out or because EConcertSyncSessionFlags::ShouldAllowGlobalMuting is not set.
- L123 _public enumerator_ `Accepted` — Changes were applied.
- L126 _public enumerator_ `Rejected` — No change were made. The request was malformed.

#### struct `FConcertReplication_ChangeMuteState_Response`  
`struct FConcertReplication_ChangeMuteState_Response`  
_L131-153_
- reflection: `USTRUCT()`
- desc: If the ErrorCode != Accepted, then no changes were made on the server.
- L136 _public member_ `EConcertReplicationMuteErrorCode ErrorCode = EConcertReplicationMuteErrorCode::Timeout;` — `UPROPERTY()`
- L140 _public member_ `TSet<FSoftObjectPath> RejectionReasons;` — `UPROPERTY()` — The objects that caused the request to be rejected. Only valid if EConcertReplicationMuteErrorCode::Rejected.
- L149 _public member_ `FConcertReplication_ChangeSyncControl SyncControl;` — `UPROPERTY()` — If the request unmuted objects, this contains the objects that the requester gained sync control over. @note When muting, the requesting client is expected to infer that sync control is lost for the muted objects. Hence, this will not contain objects the requester lost sync control over.
- L151 _public function_ `bool IsSuccess() const`
- L152 _public function_ `bool IsFailure() const`

#### struct `FConcertReplication_QueryMuteState_Request`  
`struct FConcertReplication_QueryMuteState_Request`  
_L157-166_
- reflection: `USTRUCT()`
- desc: Queries the effective mute state for.
- L163 _public member_ `TSet<FSoftObjectPath> QueriedObjects;` — `UPROPERTY()` — Specifies the objects for which to get the mute states. If left empty, get the states of all objects.
- L165 _public function_ `bool WantsAllObjects() const`

#### struct `FConcertReplication_QueryMuteState_Response`  
`struct FConcertReplication_QueryMuteState_Response`  
_L169-202_
- reflection: `USTRUCT()`
- L174 _public member_ `EReplicationResponseErrorCode ErrorCode = EReplicationResponseErrorCode::Timeout;` — `UPROPERTY()`
- L180 _public member_ `TMap<FSoftObjectPath, FConcertReplication_ObjectMuteSetting> ExplicitlyMutedObjects;` — `UPROPERTY()` — Objects that were explicitly muted, i.e. specified with FConcertReplication_ChangeMuteState_Request::ObjectsToMute.
- L187 _public member_ `TMap<FSoftObjectPath, FConcertReplication_ObjectMuteSetting> ExplicitlyUnmutedObjects;` — `UPROPERTY()` — After an outer object is muted with EConcertReplicationMuteFlags::ObjectAndSubobjects, this contains the objects that were explicitly unmuted, i.e. specified with FConcertReplication_ChangeMuteState_Request::ObjectsToUnmute.
- L193 _public member_ `TSet<FSoftObjectPath> ImplicitlyMutedObjects;` — `UPROPERTY()` — Objects that were implicitly muted, i.e. some their outers are explicitly muted with EConcertReplicationMuteFlags::ObjectAndSubobjects.
- L197 _public member_ `TSet<FSoftObjectPath> ImplicitlyUnmutedObjects;` — `UPROPERTY()` — Objects that were implicitly unmuted, i.e. 1. a parent is muted and 2. a child of parent is unmuted with EConcertReplicationMuteFlags::ObjectAndSubobjects
- L199 _public function_ `bool IsSuccess() const`
- L200 _public function_ `bool IsFailure() const`
- L201 _public function_ `bool IsEmpty() const`

#### Free symbols / members of external scopes

- L21 _namespace_ `namespace UE`
- L21 _namespace_ `namespace ConcertSyncCore` (scope `UE`)
- L24 _function_ `inline bool AffectSubobjects(EConcertReplicationMuteOption Option)` (scope `UE::ConcertSyncCore`) — @return Whether subobjects are affected by this Option. Used for future proofing (in case new entries are added to the enum).
- L48 _prototype_ `ENUM_CLASS_FLAGS(EConcertReplicationMuteRequestFlags);`
- L102 _function_ `friend bool operator==(const FConcertReplication_ChangeMuteState_Request& Left, const FConcertReplication_ChangeMuteState_Request& Right)`

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncCore/Source/ConcertSyncCore/Public/Replication/Messages/ObjectReplication.h` (Public)


#### struct `FConcertReplication_ObjectReplicationEvent`  
`struct FConcertReplication_ObjectReplicationEvent`  
_L13-31_
- reflection: `USTRUCT()`
- desc: Contains data to be applied to a replicated object.
- L22 _public member_ `FSoftObjectPath ReplicatedObject;` — `UPROPERTY()` — The object to serialize into. TODO: To reduce network load, replace this with an int32 that maps into FObjectToIdTable (custom) / UPackageMap (engine)  shared by all clients and the server.
- L26 _public member_ `int32 ReplicationSequenceId = -1;` — `UPROPERTY()` — Incremented every time replication data is sent out. Used for performance tracing.
- L30 _public member_ `FConcertSessionSerializedPayload SerializedPayload;` — `UPROPERTY()` — Contains another struct as payload, such as FConcertFullObjectReplicationData.

#### struct `FConcertReplication_StreamReplicationEvent`  
`struct FConcertReplication_StreamReplicationEvent`  
_L35-51_
- reflection: `USTRUCT()`
- desc: Contains data produced by a specific replication stream.
- L41 _public member_ `FGuid StreamId;` — `UPROPERTY()` — The stream that produced this data.
- L45 _public member_ `TArray<FConcertReplication_ObjectReplicationEvent> ReplicatedObjects;` — `UPROPERTY()` — The objects replicated by this event
- L47 _public prototype_ `FConcertReplication_StreamReplicationEvent() = default;`
- L48 _public function_ `explicit FConcertReplication_StreamReplicationEvent(const FGuid& StreamId) : StreamId(StreamId)`

#### struct `FConcertReplication_BatchReplicationEvent`  
`struct FConcertReplication_BatchReplicationEvent`  
_L62-69_
- reflection: `USTRUCT()`
- desc: Contains multiple objects to be replicated. Sent from - Authoritative client to server - Server to clients. Every event may be customized for each client (clients can choose to ignore object updates). TODO DP UE-193261: This should be split up into FConcertBatchReplicationEvent_ToServer and FConcertBatchReplicationEvent_ToClient; clients do not need FConcertStreamReplicationEvent::StreamId.
- L68 _public member_ `TArray<FConcertReplication_StreamReplicationEvent> Streams;` — `UPROPERTY()` — The objects replicated by this event

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncCore/Source/ConcertSyncCore/Public/Replication/Messages/PutState.h` (Public)


#### enum `EConcertReplicationPutStateFlags`  
`enum class EConcertReplicationPutStateFlags : uint8`  
_L11-19_
- reflection: `UENUM(Flags)`
- L13 _public enumerator_ `None`
- L16 _public enumerator_ `SkipDisconnectedClients = 1 << 0` — If another client has disconnected between the time the request was sent and received by the client, do not fail the request.
- L18 _public enumerator_ `Default = SkipDisconnectedClients`

#### struct `FConcertReplication_PutState_Request`  
`struct FConcertReplication_PutState_Request`  
_L39-58_
- reflection: `USTRUCT()`
- desc: Requests that sets the state of replication atomically. It can be used to change the streams and / or authority of multiple clients together with the mute state in a single request. This is useful i.e. for setting the session to a preset state. Upon successful execution, the server will send a FConcertReplication_ChangeClientEvent notification to all affected clients except the requesting client to update them about the changed information; the requesting client receives only sync control changes (since they know the rest they changed). Upon failure, it is guaranteed no changes have taken place. The request fails whenever any of the following occurs: - applying the request would generate any authority conflict. For example, a request that wants client 1 and 2 to both replicate the same properties of the same object would fail. - a client leaves replication before the request is processed and the SkipDisconnectedClients is not set. This request is only available if EConcertSyncSessionFlags::ShouldEnableRemoteEditing.
- L45 _public member_ `EConcertReplicationPutStateFlags Flags = EConcertReplicationPutStateFlags::Default;` — `UPROPERTY()` — Additional flags that alter the behavior of the request.
- L49 _public member_ `TMap<FGuid, FConcertReplicationStreamArray> NewStreams;` — `UPROPERTY()` — Maps a client's endpoint ID to the stream content it should have.
- L53 _public member_ `TMap<FGuid, FConcertObjectInStreamArray> NewAuthorityState;` — `UPROPERTY()` — Maps a client's endpoint ID to new authority it should have.
- L57 _public member_ `FConcertReplication_ChangeMuteState_Request MuteChange;` — `UPROPERTY()` — Mute state to apply after NewStreams and NewAuthorityState has been applied.

#### enum `EConcertReplicationPutStateResponseCode`  
`enum class EConcertReplicationPutStateResponseCode : uint8`  
_L67-110_
- reflection: `UENUM()`
- desc: Indicates success or failure of the FConcertReplication_PutState_Request. While a request may have multiple errors, the errors are returned in declaration order of this enum. Hence, the response code is the first thing that fails when reading top to bottom.
- L70 _public enumerator_ `Timeout` — The request timed out.
- L72 _public enumerator_ `Success` — The request was executed successfully.
- L79 _public enumerator_ `FeatureDisabled` — Either: - Session does not allow remote editing (EConcertSyncSessionFlags::ShouldEnableRemoteEditing is disabled). - Session does not allow muting (EConcertSyncSessionFlags::ShouldAllowGlobalMuting is disabled) and a mute request was made.
- L90 _public enumerator_ `ClientUnknown` — No changes have been made. Only returned if the flag EConcertReplicationChangeClientsFlags:: SkipDisconnectedClients was not set and FConcertReplication_PutState_Request::StreamChanges or FConcertReplication_PutState_Request::AuthorityChanges referenced a client endpoint not in the session or that has not joined replication. FConcertReplication_PutState_Response::UnknownEndpoints contains the unknown endpoints.
- L97 _public enumerator_ `StreamError` — No changes have been made. The StreamChanges was produced an error incorrect, e.g. if a stream change references an unknown stream or if a mute request references an object unknown to the server.
- L103 _public enumerator_ `AuthorityConflict` — No changes have been made. The request failed because the AuthorityChanges portion would generate a conflict with other clients if applied.
- L109 _public enumerator_ `MuteError` — No changes have been made. The request failed because

#### struct `FConcertReplication_PutState_Response`  
`struct FConcertReplication_PutState_Response`  
_L113-149_
- reflection: `USTRUCT()`
- L118 _public member_ `EConcertReplicationPutStateResponseCode ResponseCode = EConcertReplicationPutStateResponseCode::Timeout;` — `UPROPERTY()`
- L125 _public member_ `TMap<FGuid, FConcertAuthorityConflictArray> AuthorityChangeConflicts;` — `UPROPERTY()` — Maps a key from AuthorityChanges to the errors it had. Set if ResponseCode == EConcertReplicationChangeClientsResponseCode::AuthorityConflict.
- L129 _public member_ `TSet<FGuid> UnknownEndpoints;` — `UPROPERTY()` — Sets if ResponseCode == EConcertReplicationChangeClientsResponseCode::ClientUnknown.
- L146 _public member_ `FConcertReplication_ChangeSyncControl SyncControl;` — `UPROPERTY()` — The sync control changes that happened to the requesting client. Generally, this does not contain changes that the client can predict locally, i.e. - Retaining sync control. If the requesting client had sync control for an object (before the request) and the request does not modify it, that object is not contained in SyncControl. For example, if the client has sync control over Foo, and NewStreams & NewAuthorityState still contain Foo, Foo is not listed in SyncControl (since the client can predict the change). - Muting: If the requesting client had sync control for an object (before the request) and the request mutes it, that object is not contained in SyncControl. For example, if the client has sync control over Foo, and MuteChanges mutes Foo, Foo is not listed in SyncControl (since the client can predict the change).
- L148 _public function_ `bool IsSuccess() const`

#### Free symbols / members of external scopes

- L20 _prototype_ `ENUM_CLASS_FLAGS(EConcertReplicationPutStateFlags);`

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncCore/Source/ConcertSyncCore/Public/Replication/Messages/ReplicationActivity.h` (Public)


#### enum `EConcertSyncReplicationActivityType`  
`enum class EConcertSyncReplicationActivityType : uint8`  
_L19-31_
- reflection: `UENUM()`
- desc: Identifies the FConcertSyncReplicationEvent::Payload struct type
- L21 _public enumerator_ `None`
- L24 _public enumerator_ `LeaveReplication` — Client left the replication session (either because they left the MU session or because they sent a FConcertReplication_LeaveEvent).
- L27 _public enumerator_ `Mute` — Client muted or unmuted some objects.
- L30 _public enumerator_ `Count` — ADD NEW ENTRIES ABOVE

#### struct `FConcertSyncReplicationPayload_LeaveReplication`  
`struct FConcertSyncReplicationPayload_LeaveReplication`  
_L38-52_
- reflection: `USTRUCT()`
- desc: Contains the streams and authority a client had when they left a session. Used for restoring content when the client rejoins.
- L44 _public member_ `TArray<FConcertReplicationStream> Streams;` — `UPROPERTY()` — The streams the client had registered when they left.
- L48 _public member_ `TArray<FConcertObjectInStreamID> OwnedObjects;` — `UPROPERTY()` — The objects the client had authority over when they left.

#### struct `FConcertSyncReplicationSummary_LeaveReplication`  
`struct FConcertSyncReplicationSummary_LeaveReplication`  
_L55-67_
- reflection: `USTRUCT()`
- L59 _public prototype_ `FConcertSyncReplicationSummary_LeaveReplication() = default;`
- L60 _public function_ `explicit FConcertSyncReplicationSummary_LeaveReplication(const FConcertSyncReplicationPayload_LeaveReplication& Event) : OwnedObjects(Event.OwnedObjects)`
- L66 _public member_ `TArray<FConcertObjectInStreamID> OwnedObjects;` — `UPROPERTY()` — The objects the client had authority over when they left.

#### struct `FConcertSyncReplicationPayload_Mute`  
`struct FConcertSyncReplicationPayload_Mute`  
_L71-81_
- reflection: `USTRUCT()`
- desc: Stores objects that were muted / unmuted
- L77 _public member_ `FConcertReplication_ChangeMuteState_Request Request;` — `UPROPERTY()` — The request that changed mute state

#### struct `FConcertSyncReplicationSummary_Mute`  
`struct FConcertSyncReplicationSummary_Mute`  
_L85-97_
- reflection: `USTRUCT()`
- desc: Info displayed in the UI.
- L89 _public prototype_ `FConcertSyncReplicationSummary_Mute() = default;`
- L90 _public function_ `explicit FConcertSyncReplicationSummary_Mute(const FConcertSyncReplicationPayload_Mute& Event) : Request(Event.Request)`
- L96 _public member_ `FConcertReplication_ChangeMuteState_Request Request;` — `UPROPERTY()` — The request that changed mute state

#### struct `FConcertSyncReplicationEvent`  
`struct FConcertSyncReplicationEvent`  
_L115-165_
- reflection: `USTRUCT()`
- desc: Data for a replication event in a Concert Sync Session
- L121 _public member_ `EConcertSyncReplicationActivityType ActivityType = EConcertSyncReplicationActivityType::None;` — `UPROPERTY()` — Identifies the Payload struct type
- L132 _public member_ `FConcertSessionSerializedPayload Payload{ EConcertPayloadSerializationMethod::Cbor };` — `UPROPERTY()` — A FConcertSyncReplicationPayload_X type depending on ActivityType. Serialized into the database using Cbor; do not change (for simplicity we always assume it is Cbor). If you change the serialization method, you'll get a failing check. If for whatever reason you MUST save it using a different method, adjust FConcertSyncSessionDatabaseStatements::AddReplicationData and FConcertSyncSessionDatabaseStatements::SetReplicationData.
- L134 _public prototype_ `FConcertSyncReplicationEvent() = default;`
- L136 _public function_ `template<typename TPayload> explicit FConcertSyncReplicationEvent(const TPayload& Data)`
- L141 _public function_ `void SetPayload(const FConcertSyncReplicationPayload_LeaveReplication& Data)`
- L146 _public function_ `void SetPayload(const FConcertSyncReplicationPayload_Mute& Data)`
- L152 _public function_ `bool GetPayload(FConcertSyncReplicationPayload_LeaveReplication& Result) const`
- L157 _public function_ `bool GetPayload(FConcertSyncReplicationPayload_Mute& Result) const`

#### struct `FConcertSyncReplicationActivity`  
`struct FConcertSyncReplicationActivity : public FConcertSyncActivity`  
_L169-188_
- reflection: `USTRUCT()`
- inherits: `FConcertSyncActivity`
- desc: Data for a replication activity entry in a Concert Sync Session
- L173 _public function_ `FConcertSyncReplicationActivity()`
- L179 _public function_ `template<typename TPayload> explicit FConcertSyncReplicationActivity(const TPayload& PayloadData) : EventData(PayloadData)`
- L187 _public member_ `FConcertSyncReplicationEvent EventData;` — `UPROPERTY()` — The replication event data associated with this activity

#### struct `FConcertSyncReplicationActivitySummary`  
`struct FConcertSyncReplicationActivitySummary : public FConcertSyncActivitySummary`  
_L192-227_
- reflection: `USTRUCT()`
- inherits: `FConcertSyncActivitySummary`
- desc: Summary for a lock activity entry in a Concert Sync Session
- L198 _public member_ `EConcertSyncReplicationActivityType ActivityType { EConcertSyncReplicationActivityType::None };` — `UPROPERTY()` — The type of replication event we summarize
- L202 _public member_ `FConcertSessionSerializedPayload Payload{ EConcertPayloadSerializationMethod::Cbor };` — `UPROPERTY()` — The summary data. The underlying type depends on ActivityType.
- L204 _public function_ `bool GetSummaryData(FConcertSyncReplicationSummary_LeaveReplication& Data) const`
- L209 _public function_ `bool GetSummaryData(FConcertSyncReplicationSummary_Mute& Data) const`
- L216 _public prototype_ `static FConcertSyncReplicationActivitySummary CreateSummaryForEvent(const FConcertSyncReplicationEvent& InEvent);` — Create this summary from a replication event
- L219 _public prototype_ `FText ToDisplayTitle() const;` — Gets the title for this summary
- L224 _protected prototype_ `virtual FText CreateDisplayText(const bool InUseRichText) const override;`
- L225 _protected prototype_ `virtual FText CreateDisplayTextForUser(const FText InUserDisplayName, const bool InUseRichText) const override;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API CONCERTSYNCCORE_API`
- L99 _namespace_ `namespace UE`
- L99 _namespace_ `namespace ConcertSyncCore` (scope `UE`)
- L101 _function_ `inline FString GetReplicationActivityPayloadTypePathName(EConcertSyncReplicationActivityType Type)` (scope `UE::ConcertSyncCore`)

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncCore/Source/ConcertSyncCore/Public/Replication/Messages/RestoreContent.h` (Public)


#### enum `EConcertReplicationRestoreContentFlags`  
`enum class EConcertReplicationRestoreContentFlags : uint8`  
_L12-36_
- reflection: `UENUM(Flags)`
- L14 _public enumerator_ `None = 0`
- L20 _public enumerator_ `RestoreOnTop = 1 << 0` — If set, the client's final streams & authority shall be the union of the current registered streams & authority and that of the activity. If unset, the client's streams and authority are cleared (effectively replaced by what is stored in the activity).
- L23 _public enumerator_ `ValidateUniqueClient = 1 << 1` — If set, checks that there is no other client with the same display and device name. If there is, the request fails with NameConflict.
- L26 _public enumerator_ `RestoreAuthority = 1 << 2` — Also restore the authority the client had.
- L29 _public enumerator_ `SendNewState = 1 << 3` — The response should include the new stream and authority state.
- L32 _public enumerator_ `RestoreMute = 1 << 4` — Also restore the mute states of the objects. This is done by going through the activity history and replaying the mute & unmute actions.
- L34 _public enumerator_ `StreamsAndAuthority = RestoreAuthority`
- L35 _public enumerator_ `All = StreamsAndAuthority | RestoreMute`

#### enum `EConcertReplicationAuthorityRestoreMode`  
`enum class EConcertReplicationAuthorityRestoreMode : uint8`  
_L40-57_
- reflection: `UENUM()`
- L52 _public enumerator_ `ExcludeAlreadyOwnedObjectPropertiesFromStream` — If another client already has authority over a would-be restored object' restored properties, do not restore object in the client's stream. This only affects the restore properties; if RestoreOnTop is set and there are conflicts with non-restored properties, this filter does not apply.
- L54 _public enumerator_ `IncludeAlreadyOwnedObjectPropertiesInStream` — If another client already has authority over a would-be restored object's restored properties, restore it into the client's stream (but obviously don't take authority).
- L56 _public enumerator_ `AllOrNothing` — If another client already has authority over a would-be restored object's restored properties, do not restore anything.

#### struct `FConcertReplication_RestoreContent_Request`  
`struct FConcertReplication_RestoreContent_Request`  
_L67-88_
- reflection: `USTRUCT()`
- desc: Request the sending client's stream and optionally authority to be aggregated with what a client had when they left the session. A FConcertSyncFConcertSyncReplicationActivity is generated whenever a client leaves a replication session which has EConcertSyncSessionFlags::ShouldEnableReplicationActivities flag set. This activity contains the stream content and authority of the client at that point. This request is used to restore the client's state when they last left.
- L73 _public member_ `EConcertReplicationRestoreContentFlags Flags = EConcertReplicationRestoreContentFlags::StreamsAndAuthority;` — `UPROPERTY()` — Describes what and how content is to be restored.
- L77 _public member_ `EConcertReplicationAuthorityRestoreMode AuthorityRestorationMode = EConcertReplicationAuthorityRestoreMode::ExcludeAlreadyOwnedObjectPropertiesFromStream;` — `UPROPERTY()` — If EConcertReplicationRestoreContentFlags::RestoreAuthority is set, describes how to deal with authority conflicts.
- L87 _public member_ `TOptional<int64> ActivityId;` — `UPROPERTY()` — The ID of an activity that contains a client's replication state. The activity must be a FConcertSyncReplicationActivity with whose EventData.ActivityType == EConcertSyncReplicationActivityType::LeaveReplication. If left unset, use the latest activity of matching the sending endpoint's display and device name. This can be a different client.

#### enum `EConcertReplicationRestoreErrorCode`  
`enum class EConcertReplicationRestoreErrorCode : uint8`  
_L91-112_
- reflection: `UENUM()`
- L94 _public enumerator_ `Timeout` — The request timed out.
- L100 _public enumerator_ `Success` — The request was successful. The request is also successful if there was no activity to restore since the client is in the "right" state.
- L103 _public enumerator_ `Invalid` — Requesting client has not joined replication.
- L105 _public enumerator_ `NotSupported` — EConcertSyncSessionFlags::ShouldEnableReplicationActivities is not set.
- L107 _public enumerator_ `NoSuchActivity` — The request's ActivityId was set but did not point to an appropriate activity.
- L109 _public enumerator_ `NameConflict` — Nothing could be restored because another client with the same display and device name already is in the session.
- L111 _public enumerator_ `AuthorityConflict` — EConcertReplicationAuthorityRestoreMode::AllOrNothing was set and another client had authority over one of the would-be restore objects.

#### struct `FConcertReplication_RestoreContent_Response`  
`struct FConcertReplication_RestoreContent_Response`  
_L133-156_
- reflection: `USTRUCT()`
- L138 _public member_ `EConcertReplicationRestoreErrorCode ErrorCode = EConcertReplicationRestoreErrorCode::Timeout;` — `UPROPERTY()`
- L145 _public member_ `FConcertQueriedClientInfo ClientInfo;` — `UPROPERTY()` — This includes the full stream and authority content if ErrorCode == EConcertReplicationRestoreErrorCode::Success and the request had EConcertReplicationRestoreContentFlags::SendNewState set.
- L153 _public member_ `FConcertReplication_ChangeSyncControl SyncControl;` — `UPROPERTY()` — The full sync control the client has on the server. Only valid if ErrorCode == EConcertReplicationRestoreErrorCode::Success. The client does not receive a separate event for this and is expected to apply it instantly.
- L155 _public function_ `bool IsSuccess() const`

#### Free symbols / members of external scopes

- L37 _prototype_ `ENUM_CLASS_FLAGS(EConcertReplicationRestoreContentFlags);`
- L114 _namespace_ `namespace UE`
- L114 _namespace_ `namespace ConcertSyncCore` (scope `UE`)
- L116 _function_ `inline FString LexToString(EConcertReplicationRestoreErrorCode ErrorCode)` (scope `UE::ConcertSyncCore`)

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncCore/Source/ConcertSyncCore/Public/Replication/Messages/SyncControl.h` (Public)


#### struct `FConcertReplication_ChangeSyncControl`  
`struct FConcertReplication_ChangeSyncControl`  
_L36-48_
- reflection: `USTRUCT()`
- desc: Notifies clients about the ability to start or stop replicating specific objects. Sync control serves to inform clients whether the data they wish to replicate has any receivers. Replicating data when no one is listening is unnecessary. Until a sync control event is received, clients should assume no interest in the data. Special Circumstances: 1. FConcertReplication_Join_Request: The server doesn't send any FConcertReplication_ChangeSyncControl event in response to the handshake. Instead, the resulting sync control is in FConcertReplication_Join_Response::SyncControl. 2. Explicit authority change via FConcertReplication_ChangeAuthority_Request: No sync control event is sent. FConcertReplication_ChangeAuthority_Response::SyncControl contains the objects for which the client received instant sync control. Objects losing sync control are implicitly determined by using FSyncControlState::Aggregate. 3. Implicit authority change via FConcertReplication_ChangeStream_Request: No sync control event is generated as its result is implicit from the request and response. Stream changes can only cause the client to lose authority, thus sync control, over objects. Therefore, objects losing sync control can be enumerated using FSyncControlState::Aggregate. Example Flow: 1. Client 1 registers stream 's' with object 'x' (and associated properties) using FConcertReplication_ChangeStream_Request. 2. Client 1 takes authority over 'x' with 's' using FConcertReplication_ChangeAuthority_Request. 3.
- L42 _public member_ `TMap<FConcertObjectInStreamID, bool> NewControlStates;` — `UPROPERTY()` — Toggles the objects (which the receiving client 1. has previously registered and 2. taken authority over) to replicate or not.
- L44 _public function_ `bool IsEmpty() const`
- L46 _public function_ `bool DoesAtLeastOneObjectGainSyncControl() const`
- L47 _public function_ `bool DoesAtLeastOneObjectLoseSyncControl() const`

#### Free symbols / members of external scopes

- L46 _function_ `bool DoesAtLeastOneObjectGainSyncControl() const` (scope `FConcertReplication_ChangeSyncControl::DoesAtLeastOneObjectGainSyncControl`)
- L47 _function_ `bool DoesAtLeastOneObjectLoseSyncControl() const` (scope `FConcertReplication_ChangeSyncControl::DoesAtLeastOneObjectLoseSyncControl`)

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncCore/Source/ConcertSyncCore/Public/Replication/Misc/ActorLabelRemappingCore.h` (Public)


#### Free symbols / members of external scopes

- L20 _namespace_ `namespace UE`
- L20 _namespace_ `namespace ConcertSyncCore` (scope `UE`)
- L30 _prototype_ `template<CGetObjectLabelCallable TGetObjectLabel, CGetObjectClassCallable TGetObjectClass> void GenerateRemappingData( const FConcertObjectReplicationMap& Origin, TGetObjectLabel&& GetLabelFunc, TGetObjectClass&& GetClassFunc, FConcertReplicationRemappingData& Result );` (scope `UE::ConcertSyncCore`) — Creates the remapping data for a replication map. @param Origin The replication map to generate the remapping data for @param GetLabelFunc Gets the label of an object @param GetClassFunc Gets the class of an object @return The remapping data you can use to remap Origin to.
- L38 _function_ `template<CGetObjectLabelCallable TGetObjectLabel, CGetObjectClassCallable TGetObjectClass> FConcertReplicationRemappingData GenerateRemappingData( const FConcertObjectReplicationMap& Origin, TGetObjectLabel&& GetLabelFunc, TGetObjectClass&& GetClassFunc )` (scope `UE::ConcertSyncCore`) — Util version that creates a new replication mapping.
- L69 _function_ `void RemapReplicationMap( const FConcertObjectReplicationMap& Origin, const FConcertReplicationRemappingData& RemappingData, TIsRemappingCompatible&& IsRemappingCompatibleFunc, TForEachObjectWithLabel&& ForEachObjectWithLabelFunc, TGetObjectLabel&& GetLabelFunc, TProcessRemapping&& ProcessRemapping )` (scope `UE::ConcertSyncCore`)
- L80 _function_ `` (scope `UE::ConcertSyncCore::RemapReplicationMap`)
- L86 _function_ `template<CIsRemappingCompatibleCallable TIsRemappingCompatible, CForEachObjectWithLabelCallable TForEachObjectWithLabel, CGetObjectLabelCallable TGetObjectLabel> void RemapReplicationMap( const FConcertObjectReplicationMap& Origin, const FConcertReplicationRemappingData& RemappingData, TIsRemappingCompatible&& IsRemappingCompatibleFunc, TForEachObjectWithLabel&& ForEachObjectWithLabelFunc, TGetObjectLabel&& GetLabelFunc, FConcertObjectReplicationMap& OutTargetMap )` (scope `UE::ConcertSyncCore`) — Alternate version that directly writes into OutTargetMap.
- L103 _function_ `template<CIsRemappingCompatibleCallable TIsRemappingCompatible, CForEachObjectWithLabelCallable TForEachObjectWithLabel, CGetObjectLabelCallable TGetObjectLabel> FConcertObjectReplicationMap RemapReplicationMap( const FConcertObjectReplicationMap& Origin, const FConcertReplicationRemappingData& RemappingData, TIsRemappingCompatible&& IsRemappingCompatibleFunc, TForEachObjectWithLabel&& ForEachObjectWithLabelFunc, TGetObjectLabel&& GetLabelFunc )` (scope `UE::ConcertSyncCore`) — Util version that creates a new replication mapping.
- L117 _namespace_ `namespace UE`
- L117 _namespace_ `namespace ConcertSyncCore` (scope `UE`)
- L120 _function_ `template <CGetObjectLabelCallable TGetObjectLabel, CGetObjectClassCallable TGetObjectClass> void GenerateRemappingData( const FConcertObjectReplicationMap& Origin, TGetObjectLabel&& GetLabelFunc, TGetObjectClass&& GetClassFunc, FConcertReplicationRemappingData& Result )` (scope `UE::ConcertSyncCore`)

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncCore/Source/ConcertSyncCore/Public/Replication/Misc/ActorLabelRemappingEditor.h` (Public)


#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace ConcertSyncCore` (scope `UE`)
- L19 _prototype_ `void GenerateRemappingData( const FConcertObjectReplicationMap& Origin, FConcertReplicationRemappingData& Result );` (scope `UE::ConcertSyncCore`) — This version of GenerateRemappingData uses AActor::ActorLabel.
- L24 _prototype_ `FConcertReplicationRemappingData GenerateRemappingData(const FConcertObjectReplicationMap& Origin);` (scope `UE::ConcertSyncCore`) — Util version that creates a new replication mapping.
- L28 _prototype_ `template<CProcessRemappingCallbable TProcessRemapping> void RemapReplicationMap( const FConcertObjectReplicationMap& Origin, const FConcertReplicationRemappingData& RemappingData, const UWorld& TargetWorld, TProcessRemapping&& ProcessRemapping );` (scope `UE::ConcertSyncCore`) — This version of RemapReplicationMap uses AActor::ActorLabel and tries to remap to actors in TargetWorld.
- L35 _prototype_ `void RemapReplicationMap( const FConcertObjectReplicationMap& Origin, const FConcertReplicationRemappingData& RemappingData, const UWorld& TargetWorld, FConcertObjectReplicationMap& OutTargetMap );` (scope `UE::ConcertSyncCore`) — Alternate version that directly writes into OutTargetMap.
- L42 _prototype_ `FConcertObjectReplicationMap RemapReplicationMap( const FConcertObjectReplicationMap& Origin, const FConcertReplicationRemappingData& RemappingData, const UWorld& TargetWorld );` (scope `UE::ConcertSyncCore`) — Util version that creates a new replication mapping.
- L49 _namespace_ `namespace UE`
- L49 _namespace_ `namespace ConcertSyncCore` (scope `UE`)
- L51 _function_ `FORCEINLINE void GenerateRemappingData( const FConcertObjectReplicationMap& Origin, FConcertReplicationRemappingData& Result )` (scope `UE::ConcertSyncCore`)
- L58 _function_ `Origin, [](const FSoftObjectPtr& Object)` (scope `UE::ConcertSyncCore::GenerateRemappingData`)
- L64 _function_ `FORCEINLINE FConcertReplicationRemappingData GenerateRemappingData(const FConcertObjectReplicationMap& Origin)` (scope `UE::ConcertSyncCore`)
- L72 _function_ `template <CProcessRemappingCallbable TProcessRemapping> void RemapReplicationMap( const FConcertObjectReplicationMap& Origin, const FConcertReplicationRemappingData& RemappingData, const UWorld& TargetWorld, TProcessRemapping&& ProcessRemapping)` (scope `UE::ConcertSyncCore`)
- L81 _function_ `FORCEINLINE void RemapReplicationMap( const FConcertObjectReplicationMap& Origin, const FConcertReplicationRemappingData& RemappingData, const UWorld& TargetWorld, FConcertObjectReplicationMap& OutTargetMap )` (scope `UE::ConcertSyncCore`)
- L91 _function_ `FORCEINLINE FConcertObjectReplicationMap RemapReplicationMap( const FConcertObjectReplicationMap& Origin, const FConcertReplicationRemappingData& RemappingData, const UWorld& TargetWorld )` (scope `UE::ConcertSyncCore`)

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncCore/Source/ConcertSyncCore/Public/Replication/Misc/ActorLabelRemappingInput.h` (Public)


#### Free symbols / members of external scopes

- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace ConcertSyncCore` (scope `UE`)

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncCore/Source/ConcertSyncCore/Public/Replication/Misc/IReplicationGroundTruth.h` (Public)


#### class `UE::ConcertSyncCore::Replication::IReplicationGroundTruth`  
`class IReplicationGroundTruth`  
_L15-29_
- desc: Defines a way to obtain streaming information about clients.
- L20 _public prototype_ `virtual void ForEachStream(const FGuid& ClientEndpointId, TFunctionRef<EBreakBehavior(const FGuid& StreamId, const FConcertObjectReplicationMap& ReplicationMap)> Callback) const = 0;` — Provides a way to extract all streams registered to a given client.
- L23 _public prototype_ `virtual void ForEachClient(TFunctionRef<EBreakBehavior(const FGuid& ClientEndpointId)> Callback) const = 0;` — Iterates through all clients have registered to send any data.
- L26 _public prototype_ `virtual bool HasAuthority(const FGuid& ClientId, const FGuid& StreamId, const FSoftObjectPath& ObjectPath) const = 0;` — @return Whether ClientId's stream StreamId has authority over ObjectPath.
- L28 _public prototype_ `virtual ~IReplicationGroundTruth() = default;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace ConcertSyncCore` (scope `UE`)
- L12 _namespace_ `namespace Replication` (scope `UE::ConcertSyncCore`)

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncCore/Source/ConcertSyncCore/Public/Replication/Misc/Private/EditorRemappingUtils.h` (Public)


#### Free symbols / members of external scopes

- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace ConcertSyncCore` (scope `UE`)
- L18 _namespace_ `namespace Private` (scope `UE::ConcertSyncCore`)
- L20 _variable_ `constexpr bool bCreateActorLabelDuringRead = false;` (scope `UE::ConcertSyncCore::Private`)
- L22 _function_ `inline TOptional<FString> GetActorLabel(const FSoftObjectPtr& Object)` (scope `UE::ConcertSyncCore::Private`)
- L30 _function_ `inline FSoftClassPath GetClassPath(const FSoftObjectPtr& Object)` (scope `UE::ConcertSyncCore::Private`)
- L36 _function_ `inline TMap<FString, TArray<FSoftObjectPtr>> CacheByActorLabel(const UWorld& World)` (scope `UE::ConcertSyncCore::Private`)
- L54 _function_ `template<typename TFinalArg> static void GenericRemapReplicationMap( const FConcertObjectReplicationMap& Origin, const FConcertReplicationRemappingData& RemappingData, const UWorld& TargetWorld, TFinalArg&& Argument )` (scope `UE::ConcertSyncCore::Private`) — This functions sole purpose is to avoid code duplication for the overloads of GenerateRemappingData.
- L67 _function_ `` (scope `UE::ConcertSyncCore::Private::GenericRemapReplicationMap`)
- L105 _function_ `RemappingData, IsRemappingCompatibleFunc, ForEachObjectWithLabel, [](const FSoftObjectPtr& Object)` (scope `UE::ConcertSyncCore::Private::GenericRemapReplicationMap`)

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncCore/Source/ConcertSyncCore/Public/Replication/Misc/Private/RemapAlgorithm.h` (Public)


#### class `UE::ConcertSyncCore::Private::TRemapAlgorithm`  
`template<CIsRemappingCompatibleCallable TIsRemappingCompatible, CForEachObjectWithLabelCallable TForEachObjectWithLabel, CGetObjectLabelCallable TGetObjectLabel> class TRemapAlgorithm`  
_L22-370_
- desc: This algorithm remaps FSoftObjectPaths from an origin FConcertObjectReplicationMap to target FSoftObjectPaths based on the owning actors sharing actor labels. @see FConcertReplicationRemappingData for example.
- L26 _public function_ `TRemapAlgorithm( const FConcertObjectReplicationMap& Origin, const FConcertReplicationRemappingData& RemappingData, const TIsRemappingCompatible& ForEachObjectWithOuterFunc, const TForEachObjectWithLabel& ForEachObjectWithLabelFunc, const TGetObjectLabel& GetLabelFunc ) : Origin(Origin) , RemappingData(RemappingData) , IsRemappingCompatibleFunc(ForEachObjectWithOuterFunc) , ForEachObjectWithLabelFunc(ForEachObjectWithLabelFunc) , GetLabelFunc(GetLabelFunc)`
- L41 _public function_ `template<CProcessRemappingCallbable TProcessRemappingLambda> void Run(TProcessRemappingLambda&& ProcessRemapping)`
- L56 _private member_ `const FConcertObjectReplicationMap& Origin;` — Input data to the algorithm
- L57 _private member_ `const FConcertReplicationRemappingData& RemappingData;`
- L58 _private member_ `const TIsRemappingCompatible& IsRemappingCompatibleFunc;`
- L59 _private member_ `const TForEachObjectWithLabel& ForEachObjectWithLabelFunc;`
- L60 _private member_ `const TGetObjectLabel& GetLabelFunc;`
- L78 _private member_ `FObjectPathHierarchy ObjectPathHierarchy;` — Hierarchy that is used by ComputeTargetCandidates to efficiently determine objects that need to be reassigned.
- L80 _private member_ `TMap<FString, TArray<FActorAndClassPair>> LabelsToPendingActors;` — Maps actor labels to object path from the original map that had that label.
- L81 _private member_ `int32 ExpectedNumberRemappedActors = 0;`
- L88 _private function_ `void BuildOriginObjectHierarchyAndActorsNeedingRemapping()` — Processes the input replication map: - Builds ObjectPathHierarchy based on what the original replication map contained - this is used in later for analyzing the hierarchy. - Groups all actors that need processing by label in LabelsToPendingActors.
- L127 _private typedef_ `template<typename T> using TSmallInlineArray = TArray<T, TInlineAllocator<ExpectedNumLabelCollisions>>;`
- L144 _private member_ `TArray<FActorWithSolutions> ObjectsWithSolutions;` — Holds original paths that can be remapped. This is a TArray instead of TMap because RemapActors will iterate it often.
- L151 _private function_ `void ComputeRemappingCandidates()` — Goes through all actors of which the hierarchy needs remapping. Invokes ForEachObjectWithLabelFunc to get candidate actors with the same label. Proceeds to check whether the candidates' subobject hierarchy is compatible and if so, adds the candiate to ObjectsWithSolutions.
- L187 _private function_ `template<typename TGetActorSolutionData> requires std::is_invocable_r_v<FActorWithSolutions&, TGetActorSolutionData, int32> void FindSolutionsIn( const TArray<FActorAndClassPair>& PendingActors, const FSoftObjectPtr& TargetCandidate, TGetActorSolutionData&& GetSolutionData )` — Analyzes for every provided actor whether PossibleTargetActor is a suitable substitute.
- L209 _private function_ `bool IsHierarchyCompatible(const FSoftObjectPath& OriginalActor, const FSoftObjectPtr& TargetCandidate) const` — Validates that PossibleTargetActor's replicated hierarchy is compatible with that of OriginalActor.
- L253 _private function_ `template<CProcessRemappingCallbable TProcessRemappingLambda> void RemapActors(TProcessRemappingLambda&& ProcessRemapping)` — For each object that needs remapping, tries to pick a candidate we previously determined suitable. The remapping is done greedily by always remapping the actor with least remaining options first with the goal of preventing accidental starvation, see more explaination below.
- L276 _private function_ `int32 GetMostConstrainedIndex() const` — Finds the index of an actor that has the least amount of options left.
- L297 _private function_ `void RemoveFromSolutionSpace(const FSoftObjectPath& TargetActor)` — Update ObjectsWithSolutions, removing TargetActor from the solution pool. Entries without solutions are removed.
- L323 _private function_ `template<CProcessRemappingCallbable TProcessRemappingLambda> FSoftObjectPath PickSolutionAndRemap(const FActorWithSolutions& ObjectRemapData, TProcessRemappingLambda&& ProcessRemapping) const` — Picks the first solution, and replaces the original actor path to the new actor path. Subobject paths are translated with the new actor name.
- L348 _private function_ `template<CProcessRemappingCallbable TProcessRemappingLambda> void RemapActorHierarchy( const FSoftObjectPath& OriginActor, const FSoftObjectPath& PickedSolution, TProcessRemappingLambda&& ProcessRemapping ) const` — For each original component that had replicated properties, replace the actor bit of their path with the chosen solution actor.

#### struct `UE::ConcertSyncCore::Private::TRemapAlgorithm::FActorAndClassPair`  
`struct FActorAndClassPair`  
_L64-75_
- L67 _public member_ `const FSoftObjectPath OriginActor;` — The path of an actor that is directly or indirectly referenced by the replication map.
- L69 _public member_ `const FSoftClassPath& Class;` — The class that OriginActor is expected to have, as recorded by FConcertReplicationRemappingData_Actor.
- L71 _public function_ `FActorAndClassPair(FSoftObjectPath OriginActor, const FSoftClassPath& Class) : OriginActor(MoveTemp(OriginActor)) , Class(Class)`

#### enum `UE::ConcertSyncCore::Private::TRemapAlgorithm::(anonymous)`  
`enum`  
_L124-124_
- desc: The max number of actors in a level we expect to have share the same label. We expect a typical level to have at most 4 actors with the same label... if we're wrong we're punished with dynamic memory allocs.

#### struct `UE::ConcertSyncCore::Private::TRemapAlgorithm::FActorWithSolutions`  
`struct FActorWithSolutions`  
_L129-142_
- L135 _public member_ `const FSoftObjectPath& OriginActor;` — An actor directly or indirectly referenced by the Origin replication map. This is a reference to FActorAndClassPair::OriginActor.
- L137 _public member_ `TSmallInlineArray<FSoftObjectPath> PossibleSolutions;` — Actors that OriginActor can be replaced with. It had been validated that the hierarchy is compatible.
- L139 _public function_ `explicit FActorWithSolutions(const FSoftObjectPath& OriginActor) : OriginActor(OriginActor)`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace ConcertSyncCore` (scope `UE`)
- L14 _namespace_ `namespace Private` (scope `UE::ConcertSyncCore`)
- L106 _function_ `` (scope `UE::ConcertSyncCore::Private::TRemapAlgorithm::BuildOriginObjectHierarchyAndActorsNeedingRemapping`)
- L124 _enumerator_ `enum { ExpectedNumLabelCollisions = 4 }; template<typename T> using TSmallInlineArray = TArray<T` (scope `UE::ConcertSyncCore::Private::TRemapAlgorithm::__anon443d29270203`) — The max number of actors in a level we expect to have share the same label. We expect a typical level to have at most 4 actors with the same label... if we're wrong we're punished with dynamic memory allocs.
- L165 _function_ `` (scope `UE::ConcertSyncCore::Private::TRemapAlgorithm::ComputeRemappingCandidates`)
- L214 _function_ `` (scope `UE::ConcertSyncCore::Private::TRemapAlgorithm::IsHierarchyCompatible`)
- L355 _function_ `` (scope `UE::ConcertSyncCore::Private::TRemapAlgorithm::RemapActorHierarchy`)

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncCore/Source/ConcertSyncCore/Public/Replication/Misc/ReplicatedObjectHierarchyCache.h` (Public)


#### class `UE::ConcertSyncCore::FReplicatedObjectHierarchyCache`  
`class FReplicatedObjectHierarchyCache : FObjectPathHierarchy`  
_L24-76_
- inherits: `FObjectPathHierarchy`
- desc: Holds the outer hierarchy of all objects registered in any stream. Updates the hierarchy when a relevant event changing stream content happens.
- L36 _public prototype_ `void Clear();` — Removes all saved state.
- L47 _public prototype_ `bool IsObjectReferencedDirectly(const FSoftObjectPath& ObjectPath, TConstArrayView<FGuid> IgnoredClients = {}) const;` — Checks whether the object is registered by any client (except for this in IgnoredClients). This function ignores implicit knowledge of the hierarchy. For example if you register ONLY /Game/Maps.Map:PersistentLevel.Cube.StaticMeshComponent0, then - IsObjectReferencedDirectly(/Game/Maps.Map:PersistentLevel.Cube.StaticMeshComponent0) == true, - IsObjectReferencedDirectly(/Game/Maps.Map:PersistentLevel.Cube) == false but e.g. TraverseTopToBottom would list both paths.
- L50 _public prototype_ `void OnJoin(const FGuid& ClientId, const FConcertReplication_Join_Request& Request);` — Validated network events that modify the known hierarchy of objects.
- L51 _public prototype_ `void OnPostClientLeft(const FGuid& ClientId, TConstArrayView<FConcertReplicationStream> Streams);`
- L52 _public prototype_ `void OnChangeStreams(const FGuid& ClientId, TConstArrayView<FConcertObjectInStreamID> AddedObjects, TConstArrayView<FConcertObjectInStreamID> RemovedObjects);`
- L61 _private function_ `friend bool operator==(const FStreamReferencer& Left, const FStreamReferencer& Right)`
- L62 _private function_ `friend bool operator!=(const FStreamReferencer& Left, const FStreamReferencer& Right)`
- L71 _private member_ `TMap<FSoftObjectPath, FObjectMetaData> ObjectMetaData;`
- L73 _private prototype_ `void AddObjectInternal(const FConcertReplicatedObjectId& ObjectInfo);`
- L74 _private prototype_ `void RemoveObjectInternal(const FConcertReplicatedObjectId& Object);`
- L75 _private prototype_ `bool RemoveMetaData(const FConcertReplicatedObjectId& Object);`

#### struct `UE::ConcertSyncCore::FReplicatedObjectHierarchyCache::FStreamReferencer`  
`struct FStreamReferencer`  
_L56-63_
- L58 _public member_ `FGuid ClientId;`
- L59 _public member_ `FGuid StreamId;`

#### struct `UE::ConcertSyncCore::FReplicatedObjectHierarchyCache::FObjectMetaData`  
`struct FObjectMetaData`  
_L65-69_
- L68 _public member_ `TArray<FStreamReferencer> ReferencingStreams;` — Keeps track of all clients referencing the stream.

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API CONCERTSYNCCORE_API`
- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace ConcertSyncCore` (scope `UE`)

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncCore/Source/ConcertSyncCore/Public/Replication/Misc/ReplicationStreamUtils.h` (Public)


#### Free symbols / members of external scopes

- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace ConcertSyncCore` (scope `UE`)
- L19 _prototype_ `const FConcertReplicationStream* FindStream(const TConstArrayView<FConcertReplicationStream> Streams, const FGuid& StreamId);` (scope `UE::ConcertSyncCore`) — Util for finding a stream in an array of streams by id.
- L21 _prototype_ `FConcertReplicationStream* FindStreamEditable(const TArrayView<FConcertReplicationStream> Streams, const FGuid& StreamId);` (scope `UE::ConcertSyncCore`) — Util for finding a stream in an array of streams by id.
- L24 _prototype_ `const FConcertReplicatedObjectInfo* FindObjectInfo(const TConstArrayView<FConcertReplicationStream> Streams, const FConcertObjectInStreamID& ObjectId);` (scope `UE::ConcertSyncCore`) — Util for finding an object in an array of streams.
- L26 _prototype_ `FConcertReplicatedObjectInfo* FindObjectInfoEditable(const TArrayView<FConcertReplicationStream> Streams, const FConcertObjectInStreamID& ObjectId);` (scope `UE::ConcertSyncCore`) — Util for finding an object an array of streams.
- L29 _prototype_ `const FConcertReplicatedObjectInfo* FindObjectInfo(const FConcertReplicationStream& Stream, const FSoftObjectPath& ObjectPath);` (scope `UE::ConcertSyncCore`) — Util for finding an object in a stream.
- L31 _prototype_ `FConcertReplicatedObjectInfo* FindObjectInfoEditable(FConcertReplicationStream& Stream, const FSoftObjectPath& ObjectPath);` (scope `UE::ConcertSyncCore`) — Util for finding an object in a stream.
- L34 _prototype_ `const FConcertObjectReplicationSettings* FindObjectFrequency(const TConstArrayView<FConcertReplicationStream> Streams, const FConcertObjectInStreamID& ObjectId);` (scope `UE::ConcertSyncCore`) — Util for finding an object's frequency override settings in a stream in an array of streams.
- L36 _prototype_ `FConcertObjectReplicationSettings* FindObjectFrequencyEditable(const TArrayView<FConcertReplicationStream> Streams, const FConcertObjectInStreamID& ObjectId);` (scope `UE::ConcertSyncCore`) — Util for finding an object's frequency override settings in a stream in an array of streams.
- L39 _prototype_ `bool IsObjectOrChildReferenced(const TConstArrayView<FConcertReplicationStream> Streams, const FSoftObjectPath& ObjectPath);` (scope `UE::ConcertSyncCore`) — @return Whether ObjectPath or any its child objects, i.e. any object that ObjectPath is an indirect or direct outer of, are referenced by Streams.
- L42 _namespace_ `namespace UE`
- L42 _namespace_ `namespace ConcertSyncCore` (scope `UE`)
- L44 _function_ `inline const FConcertReplicationStream* FindStream(const TConstArrayView<FConcertReplicationStream> Streams, const FGuid& StreamId)` (scope `UE::ConcertSyncCore`)
- L46 _function_ `return Streams.FindByPredicate([&StreamId](const FConcertReplicationStream& Stream) { return Stream.BaseDescription.Identifier == StreamId; });` (scope `UE::ConcertSyncCore::FindStream`)
- L48 _function_ `inline FConcertReplicationStream* FindStreamEditable(const TArrayView<FConcertReplicationStream> Streams, const FGuid& StreamId)` (scope `UE::ConcertSyncCore`)
- L50 _function_ `return Streams.FindByPredicate([&StreamId](const FConcertReplicationStream& Stream) { return Stream.BaseDescription.Identifier == StreamId; });` (scope `UE::ConcertSyncCore::FindStreamEditable`)
- L53 _function_ `inline const FConcertReplicatedObjectInfo* FindObjectInfo(const TConstArrayView<FConcertReplicationStream> Streams, const FConcertObjectInStreamID& ObjectId)` (scope `UE::ConcertSyncCore`)
- L58 _function_ `inline FConcertReplicatedObjectInfo* FindObjectInfoEditable(const TArrayView<FConcertReplicationStream> Streams, const FConcertObjectInStreamID& ObjectId)` (scope `UE::ConcertSyncCore`)
- L64 _function_ `inline const FConcertReplicatedObjectInfo* FindObjectInfo(const FConcertReplicationStream& Stream, const FSoftObjectPath& ObjectPath)` (scope `UE::ConcertSyncCore`)
- L68 _function_ `inline FConcertReplicatedObjectInfo* FindObjectInfoEditable(FConcertReplicationStream& Stream, const FSoftObjectPath& ObjectPath)` (scope `UE::ConcertSyncCore`)
- L73 _function_ `inline const FConcertObjectReplicationSettings* FindObjectFrequency(const TConstArrayView<FConcertReplicationStream> Streams, const FConcertObjectInStreamID& ObjectId)` (scope `UE::ConcertSyncCore`)
- L78 _function_ `inline FConcertObjectReplicationSettings* FindObjectFrequencyEditable(const TArrayView<FConcertReplicationStream> Streams, const FConcertObjectInStreamID& ObjectId)` (scope `UE::ConcertSyncCore`)
- L84 _function_ `inline bool IsObjectOrChildReferenced(const TConstArrayView<FConcertReplicationStream> Streams, const FSoftObjectPath& ObjectPath)` (scope `UE::ConcertSyncCore`)

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncCore/Source/ConcertSyncCore/Public/Replication/Misc/StreamAndAuthorityPredictionUtils.h` (Public)


#### Free symbols / members of external scopes

- L20 _namespace_ `namespace UE`
- L20 _namespace_ `namespace ConcertSyncCore` (scope `UE`)
- L20 _namespace_ `namespace Replication` (scope `UE::ConcertSyncCore`)
- L22 _typedef_ `using FExtractReplicationEventFunc = TFunctionRef<void( const int64 EventId, TFunctionRef<void(const FConcertSyncReplicationEvent& Event)> Callback )>;` (scope `UE::ConcertSyncCore::Replication`)
- L42 _prototype_ `TOptional<int64> BacktrackActivityHistoryForActivityThatSetsContent( TConstArrayView<FConcertSyncActivity> Activities, TFunctionRef<bool(const FGuid& EndpointId)> IsTargetEndpointFunc, FExtractReplicationEventFunc GetReplicationEventFunc, TArray<FConcertBaseStreamInfo>& OutStreams, TArray<FConcertObjectInStreamID>& OutAuthority );` (scope `UE::ConcertSyncCore::Replication`) — Walks back the activity history and finds the latest activity that sets the target client's state. For now, the state is only determined by EConcertSyncReplicationActivityType::LeaveReplication replication activities. In the future, additional types may also affect it, e.g. PutState, may then each in turn produce activities. @param Activities The activities to analyze @param IsTargetEndpointFunc Returns whether the endpoint ID corresponds to the client to which we want to get the state. Usually when restoring, you'll want to match the client's DisplayName and DeviceName to that in an activity. @param GetReplicationEventFunc Gets the replication event for the given EventId. This is called when iterating Activities. @param OutStreams The streams the client had, if successful @param OutAuthority The authority the client had, if successful @return The activity ID that contained the state. Unset if not found.
- L50 _prototype_ `TOptional<int64> BacktrackActivityHistoryForActivityThatSetsContent( TConstArrayView<FConcertSessionActivity> Activities, TFunctionRef<bool(const FGuid& EndpointId)> IsTargetEndpointFunc, FExtractReplicationEventFunc GetReplicationEventFunc, TArray<FConcertBaseStreamInfo>& OutStreams, TArray<FConcertObjectInStreamID>& OutAuthority );` (scope `UE::ConcertSyncCore::Replication`) — Equivalent version that accepts FConcertSessionActivity instead. This is useful if your activities come from IConcertClientWorkspace::GetActivities.
- L66 _prototype_ `bool AreLogicallySameClients(const FConcertClientInfo& First, const FConcertClientInfo& Second);` (scope `UE::ConcertSyncCore::Replication`) — Decides whether First and Second should be considered to represent the same user across several Concert sessions. Every time a user joins a Concert session, a new endpoint ID is generated for that user and saved in the database. Even though the endpoint ID is different, we can associate the same user across the IDs by using the DisplayName and DeviceName. @return Whether First and Second logically describe the same client (i.e. DisplayName and DeviceName of both clients are equal).

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncCore/Source/ConcertSyncCore/Public/Replication/Misc/SyncControlUtils.h` (Public)


#### enum `UE::ConcertSyncCore::EAppendSyncControlFlags`  
`enum class EAppendSyncControlFlags : uint8`  
_L13-18_
- L15 _public enumerator_ `None`
- L17 _public enumerator_ `SkipLostControl = 1 << 0` — The resulting SyncControlToUpdate should not contain any false values.

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace ConcertSyncCore` (scope `UE`)
- L19 _prototype_ `ENUM_CLASS_FLAGS(EAppendSyncControlFlags);` (scope `UE::ConcertSyncCore`)
- L22 _prototype_ `void AppendSyncControl(FConcertReplication_ChangeSyncControl& SyncControlToUpdate, const FConcertReplication_ChangeSyncControl& AppendedSyncControl, EAppendSyncControlFlags Flags = EAppendSyncControlFlags::None);` (scope `UE::ConcertSyncCore`) — Appends AppendedSyncControl to SyncControlToUpdate overriding old entries.
- L25 _namespace_ `namespace UE`
- L25 _namespace_ `namespace ConcertSyncCore` (scope `UE`)
- L27 _function_ `inline void AppendSyncControl(FConcertReplication_ChangeSyncControl& SyncControlToUpdate, const FConcertReplication_ChangeSyncControl& AppendedSyncControl, EAppendSyncControlFlags Flags)` (scope `UE::ConcertSyncCore`)

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncCore/Source/ConcertSyncCore/Public/Replication/MuteUtils.h` (Public)


#### enum `UE::ConcertSyncCore::Replication::MuteUtils::EMuteState`  
`enum class EMuteState : uint8`  
_L14-23_
- L17 _public enumerator_ `None` — Default state: the object was not explicitly muted / unmuted, nor was any of its parent objects affected.
- L19 _public enumerator_ `ExplicitlyMuted`
- L20 _public enumerator_ `ExplicitlyUnmuted`
- L21 _public enumerator_ `ImplicitlyMuted`
- L22 _public enumerator_ `ImplicitlyUnmuted`

#### class `UE::ConcertSyncCore::Replication::MuteUtils::IMuteStateGroundTruth`  
`class IMuteStateGroundTruth`  
_L26-49_
- desc: Holds information that is used to rebuilding mute state.
- L31 _public prototype_ `virtual EMuteState GetMuteState(const FSoftObjectPath& Object) const = 0;` — @return The object's mute state.
- L34 _public prototype_ `virtual TOptional<FConcertReplication_ObjectMuteSetting> GetExplicitSetting(const FSoftObjectPath& Object) const = 0;` — @return The mute setting set for Object, if GetMuteState(Object) == ExplicitlyMuted or ExplicitlyUnmuted. Unset otherwise.
- L46 _public prototype_ `virtual bool IsObjectKnown(const FSoftObjectPath& Object) const = 0;` — Checks whether an object is known. Only known objects can be muted on the server. @see FConcertReplication_ChangeMuteState_Request @return Whether the object is known on the server.
- L48 _public prototype_ `virtual ~IMuteStateGroundTruth() = default;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace ConcertSyncCore` (scope `UE`)
- L12 _namespace_ `namespace Replication` (scope `UE::ConcertSyncCore`)
- L12 _namespace_ `namespace MuteUtils` (scope `UE::ConcertSyncCore::Replication`)
- L61 _prototype_ `void CombineMuteRequests( FConcertReplication_ChangeMuteState_Request& InOutBase, const FConcertReplication_ChangeMuteState_Request& InRequestToMerge, const IMuteStateGroundTruth& InGroundTruth );` (scope `UE::ConcertSyncCore::Replication::MuteUtils`) — Adds a request into a base request, which gets its data overriden accordingly. This is useful for replaying mute requests. For example, suppose the base request mutes Foo and InRequestToMerge unmutes it, the final result would be that Foo is not muted. @param InOutBase The result will be combined into this request. @param InRequestToMerge The request to add onto InOutBase. @param InGroundTruth Used for determining whether an object can be muted.

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncCore/Source/ConcertSyncCore/Public/Replication/Processing/Actions/ConcertReplicationAction.h` (Public)


#### struct `UE::ConcertSyncCore::FReplicationActionArgs`  
`struct FReplicationActionArgs`  
_L12-24_
- desc: Arguments for FConcertReplicationAction::Apply.
- L15 _public member_ `const FConcertReplicatedObjectId& ObjectId;` — Replication info about the object.
- L18 _public member_ `const TNotNull<UObject*> Object;` — The resolved object that was replicated.
- L20 _public function_ `explicit FReplicationActionArgs(const FConcertReplicatedObjectId& InObjectId, TNotNull<UObject*> InObject) : ObjectId(InObjectId) , Object(InObject)`

#### struct `FConcertReplicationAction`  
`struct FConcertReplicationAction`  
_L35-41_
- reflection: `USTRUCT()`
- desc: An action to be performed in relation to replication, such as after an object has been replicated. Sub-structs implement Apply, which e.g. calls PostEditChange, MarkRenderStateDirty, or some other custom action. This can be used in conjunction with TInstancedStruct so these actions can be set up in .ini files, i.e. UPROPERTY(Config) TInstancedStruct<FConcertReplicationAction>.
- L39 _public prototype_ `virtual ~FConcertReplicationAction() = default;`
- L40 _public function_ `virtual void Apply(const UE::ConcertSyncCore::FReplicationActionArgs& InArgs) const`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace ConcertSyncCore` (scope `UE`)

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncCore/Source/ConcertSyncCore/Public/Replication/Processing/Actions/ConcertReplicationAction_MarkRenderStateDirty.h` (Public)


#### struct `FConcertReplicationAction_MarkRenderStateDirty`  
`struct FConcertReplicationAction_MarkRenderStateDirty : public FConcertReplicationAction`  
_L13-26_
- reflection: `USTRUCT(DisplayName = "Mark Render State Dirty")`
- inherits: `FConcertReplicationAction`
- desc: Calls MarkRenderStateDirty on the object if it is a USceneComponent.
- L17 _public function_ `virtual void Apply(const UE::ConcertSyncCore::FReplicationActionArgs& InArgs) const override`

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncCore/Source/ConcertSyncCore/Public/Replication/Processing/Actions/ConcertReplicationAction_PostEditChange.h` (Public)


#### struct `FConcertReplicationAction_PostEditChange`  
`struct FConcertReplicationAction_PostEditChange : public FConcertReplicationAction`  
_L11-21_
- reflection: `USTRUCT(DisplayName = "Post Edit Change")`
- inherits: `FConcertReplicationAction`
- desc: Calls PostEditChange on the object.
- L15 _public function_ `virtual void Apply(const UE::ConcertSyncCore::FReplicationActionArgs& InArgs) const override`

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncCore/Source/ConcertSyncCore/Public/Replication/Processing/Actions/ConcertReplicationAction_UpdateComponentToWorld.h` (Public)


#### struct `FConcertReplicationAction_UpdateComponentToWorld`  
`struct FConcertReplicationAction_UpdateComponentToWorld : public FConcertReplicationAction`  
_L13-26_
- reflection: `USTRUCT(DisplayName = "Update Component To World")`
- inherits: `FConcertReplicationAction`
- desc: Calls ConcertReplicationAction_UpdateComponentToWorld on the object if it is a USceneComponent.
- L17 _public function_ `virtual void Apply(const UE::ConcertSyncCore::FReplicationActionArgs& InArgs) const override`

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncCore/Source/ConcertSyncCore/Public/Replication/Processing/Actions/ReplicationActionDispatcher.h` (Public)


#### class `UE::ConcertSyncCore::FReplicationActionDispatcher`  
`class FReplicationActionDispatcher`  
_L16-38_
- desc: Util that you can use when calling IObjectReplicationFormat::ApplyReplicationEvent to execute actions.
- L20 _public prototype_ `explicit FReplicationActionDispatcher(const TArray<FConcertReplicationActionEntry>& InActions UE_LIFETIMEBOUND, bool bDebugActions = false);`
- L23 _public prototype_ `void OnReplicateProperty(const FProperty& InProperty);` — Checks whether InProperty should trigger actions.
- L26 _public prototype_ `void ExecuteActions(const FReplicationActionArgs& InArgs);` — Call all properties have been processed using OnReplicateProperty. Triggers the actions that need to triggered.
- L31 _private member_ `const TArray<FConcertReplicationActionEntry>& Actions;` — The actions to perform.
- L34 _private member_ `const bool bDebugActions;` — Whether the actions should be debugged.
- L37 _private member_ `TBitArray<> ActionsToTrigger;` — Bit mask of equal length as the action array. Each index marks whether the action at the equivalent action array index should be performed.

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API CONCERTSYNCCORE_API`
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace ConcertSyncCore` (scope `UE`)

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncCore/Source/ConcertSyncCore/Public/Replication/Processing/IReplicationDataItem.h` (Public)


#### class `UE::ConcertSyncCore::IReplicationDataItem`  
`class IReplicationDataItem`  
_L12-37_
- desc: An item that is cached by IReplicationDataSource. Provides interface for extracting the replication data.
- L25 _public prototype_ `virtual void ExtractReplicationDataForObject( TFunctionRef<void(const FConcertSessionSerializedPayload& Payload)> ProcessCopyable, TFunctionRef<void(FConcertSessionSerializedPayload&& Payload)> ProcessMoveable ) = 0;` — Extracts data for an object iterated by IReplicationDataSource. This can update the SequenceId associated with the object (if this data source generates data as opposed to queuing it). Either ProcessCopyable or ProcessMoveable will be called, never both, and it will be called at most once. @param ProcessCopyable Callback if the event was retrieved and not owned by this IReplicationDataSource (hence not being moveable). @param ProcessMoveable Callback if the event was just constructed (and hence can be moved)
- L31 _public function_ `void ExtractReplicationDataForObject(TFunctionRef<void(const FConcertSessionSerializedPayload& Payload)> ProcessCopyable)` — Util version for callers that only want to read and do not want to store the payload.
- L36 _public prototype_ `virtual ~IReplicationDataItem() = default;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace ConcertSyncCore` (scope `UE`)
- L33 _function_ `ExtractReplicationDataForObject(ProcessCopyable, [&ProcessCopyable](FConcertSessionSerializedPayload&& Payload){ ProcessCopyable(Payload); });` (scope `UE::ConcertSyncCore::IReplicationDataItem::ExtractReplicationDataForObject`)

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncCore/Source/ConcertSyncCore/Public/Replication/Processing/IReplicationDataSource.h` (Public)


#### struct `UE::ConcertSyncCore::FPendingObjectReplicationInfo`  
`struct FPendingObjectReplicationInfo`  
_L17-26_
- L20 _public member_ `FConcertReplicatedObjectId ObjectId;` — The object to be replicated
- L25 _public member_ `FSequenceId SequenceId;` — The ID of the change that is pending. If previous changes were combined, this is the ID of the highest combined change.

#### class `UE::ConcertSyncCore::IReplicationDataSource`  
`class IReplicationDataSource`  
_L35-86_
- desc: Responsible for obtaining replication data. Implementation examples: - serialize the object path (client), - cache received object data and return it (client & server)
- L45 _public prototype_ `virtual void ConsumePendingObjects(TFunctionRef<void(const FPendingObjectReplicationInfo& Info, IReplicationDataItem& Item)> InProcess) = 0;` — Iterates the objects that must be processed for replication. It allows the extraction of the data using IReplicationDataItem. If the data is extracted, the data is "dequeued", i.e. will not be passed again in subsequent calls to ConsumePendingObjects unless new data becomes available.
- L49 _public function_ `virtual void ForEachPendingObject(TFunctionRef<void(const FPendingObjectReplicationInfo&)> ProcessItemFunc) const` — `UE_DEPRECATED(5.8, "Use ConsumePendingObjects instead.")` — Iterates the objects that must be processed for replication (the result of ExtractReplicationDataForObject MAY return something new).
- L53 _public function_ `virtual int32 NumObjects() const` — `UE_DEPRECATED(5.8, "This function no longer has a use and will be removed.")` — @return The number of objects ForEachPendingObject would iterate. Can be used, e.g. for Reserve()-ing a container.
- L69 _public function_ `virtual bool ExtractReplicationDataForObject( const FConcertReplicatedObjectId& Object, TFunctionRef<void(const FConcertSessionSerializedPayload& Payload)> ProcessCopyable, TFunctionRef<void(FConcertSessionSerializedPayload&& Payload)> ProcessMoveable )` — `UE_DEPRECATED(5.8, "Use ConsumePendingObjects and call IReplicationDataItem::ExtractReplicationDataForObject instead.")` — Extracts data for Object. Object must have been previously returned by ForEachPendingObject. This "dequeues" Object so it will not be mentioned by ForEachPendingObject again until it is again marked as "dirty". This might also update the SequenceId associated with the object (if this data source generates data as opposed to queuing it). The call to ProcessCopyable / ProcessMoveable may be skipped if there is no new data to send. Either ProcessCopyable or ProcessMoveable will be called, never both, and it will be called at most once. @param Object The object for which to obtain data @param ProcessCopyable Callback if the event was retrieved and not owned by this IReplicationDataSource (hence not being moveable). @param ProcessMoveable Callback if the event was just constructed (and hence can be moved) @return Whether successful. False indicates the call was invalid to make (ForEachPendingObject did not return Object). True indicates success, even if ProcessCopyable was not called.
- L80 _public function_ `bool ExtractReplicationDataForObject(const FConcertReplicatedObjectId& Object, TFunctionRef<void(const FConcertSessionSerializedPayload& Payload)> ProcessCopyable)` — `UE_DEPRECATED(5.8, "Use ConsumePendingObjects and call IReplicationDataItem::ExtractReplicationDataForObject instead.")` — Util version for callers that only want to read and do not want to store the payload.
- L85 _public prototype_ `virtual ~IReplicationDataSource() = default;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace ConcertSyncCore` (scope `UE`)

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncCore/Source/ConcertSyncCore/Public/Replication/Processing/ObjectReplicationCache.h` (Public)


#### class `UE::ConcertSyncCore::IReplicationCacheUser`  
`class IReplicationCacheUser`  
_L27-50_
- desc: Interface for objects that want to latently use received FConcertObjectReplicationEvent data. The data is continuously updated until it is consumed.
- L32 _public prototype_ `virtual bool WantsToAcceptObject(const FConcertReplicatedObjectId& Object) const = 0;` — @return Whether this user is interested in data from this object.
- L40 _public prototype_ `virtual void OnDataCached(const FConcertReplicatedObjectId& Object, FSequenceId SequenceId, TSharedRef<const FConcertReplication_ObjectReplicationEvent> Data) = 0;` — Called when data that is interesting to this user becomes available. The user can keep hold of Data until it is used, at which point it just let's Data get out of scope. If new data is received while this user is referencing Data, the Data will be combined and OnCachedDataUpdated called.
- L47 _public function_ `virtual void OnCachedDataUpdated(const FConcertReplicatedObjectId& Object, FSequenceId SequenceId)` — This function is called when new data is received while this cache user is still holding on to an object previously received with OnDataCached. @param Object The object for which data was updated. @param SequenceId The ID of the event data that was combined
- L49 _public prototype_ `virtual ~IReplicationCacheUser() = default;`

#### struct `UE::ConcertSyncCore::FCacheStoreStats`  
`struct FCacheStoreStats`  
_L52-58_
- L54 _public member_ `uint32 NumInsertions = 0;`
- L55 _public member_ `uint32 NumCacheUpdates = 0;`
- L57 _public function_ `bool NoChangesMade() const`

#### class `UE::ConcertSyncCore::FObjectReplicationCache`  
`class FObjectReplicationCache : public TSharedFromThis<FObjectReplicationCache>`  
_L72-127_
- inherits: `TSharedFromThis<FObjectReplicationCache>`
- desc: This is an intermediate place for received data to live before it is further processed. IObjectCacheUsers register with the cache and decide which data is to be received. When replication data comes in IObjectCacheUsers::WantsToAcceptObject is used to determine whether the object wants the data. If the data should be received, IObjectCacheUsers::OnDataCached is called receiving a shared ptr to the data. When the data is finally consumed latently, e.g. sent to other endpoints, the cache user resets the shared ptr. If new data comes in before a cache user consumes it, the new data and old data are combined (using IObjectReplicationFormat::CombineReplicationEvents). This allows multiple systems to reuse replication data. For example, on the server the same data may need to be distributed to different clients but the clients send the data at different times.
- L76 _public prototype_ `FObjectReplicationCache(IObjectReplicationFormat& ReplicationFormat UE_LIFETIMEBOUND);`
- L86 _public prototype_ `FCacheStoreStats StoreUntilConsumed(const FGuid& SendingEndpointId, const FGuid& OriginStreamId, const FSequenceId SequenceId, const FConcertReplication_ObjectReplicationEvent& ObjectReplicationEvent);` — Called when new data is received for an object and shares it with any IObjectCacheUser that is possibly interested in it. @param SendingEndpointId The ID of the client endpoint that sent this data @param OriginStreamId The stream from which the object was replicated @param SequenceId The ID of the change. Used primarily for performance tracing. @param ObjectReplicationEvent The data that was replicated @return The number of cache users that accepted this event.
- L89 _public prototype_ `void RegisterDataCacheUser(TSharedRef<IReplicationCacheUser> User);` — Registers a new user, which will start receiving data for any new data received from now on.
- L90 _public prototype_ `void UnregisterDataCacheUser(const TSharedRef<IReplicationCacheUser>& User);`
- L95 _private member_ `IObjectReplicationFormat& ReplicationFormat;` — Used for combining events to save network bandwidth.
- L98 _private member_ `TArray<TSharedRef<IReplicationCacheUser>> CacheUsers;` — Everyone who registered for receiving data.
- L115 _private member_ `TMap<FConcertObjectInStreamID, FObjectCache> Cache;` — Maps every object to the events cached for it.
- L121 _private prototype_ `uint32 CombineCachedDataWithNewData( const FConcertReplicatedObjectId& ObjectId, FSequenceId NewSequenceId, const FConcertReplication_ObjectReplicationEvent& NewData, const FObjectCache& ObjectCacheBeforeAddition ) const;` — Combines old data that cache users may have associated for ObjectId with the NewData and notifies the users with OnCachedDataUpdated. @return Number of cache users that were updated

#### struct `UE::ConcertSyncCore::FObjectReplicationCache::FObjectCache`  
`struct FObjectCache`  
_L100-113_
- L112 _public member_ `TMap<TWeakPtr<IReplicationCacheUser>, TWeakPtr<FConcertReplication_ObjectReplicationEvent>> DataInUse;` — Past data that is still in use by users. StoreUntilConsumed asks all IReplicationCacheUser and if at least one is interested, creates exactly 1 TSharedRef<FConcertObjectReplicationEvent>. Every IReplicationCacheUser receives essentially a MakeShareable of the above instance: its own TSharedRef with a custom deleter that simply keeps the event instance. This mechanism allows detecting whether a IReplicationCacheUser already is using old data which needs to be combined with the new incoming data, or needs a new instance. The intention is that as soon as IReplicationCacheUser has finished using a data event, it will receive a new instance: we do not want IReplicationCacheUsers to have large histories of events being combined into them.

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API CONCERTSYNCCORE_API`
- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace ConcertSyncCore` (scope `UE`)

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncCore/Source/ConcertSyncCore/Public/Replication/Processing/ObjectReplicationProcessor.h` (Public)


#### struct `UE::ConcertSyncCore::FProcessObjectsParams`  
`struct FProcessObjectsParams`  
_L24-29_
- desc: Params for FObjectReplicationProcessor::ProcessObjects. Exists as struct so we can add params (e.g. UE-190714) without affecting the signature and can avoid deprecation.
- L27 _public member_ `float DeltaTime;` — The current frame's delta time

#### class `UE::ConcertSyncCore::FObjectReplicationProcessor`  
`class FObjectReplicationProcessor`  
_L41-77_
- desc: Responsible for prioritizing a list of objects and processing them. Processing is defined by the subclass. Some example implementations: - serialize the object and send (client), - find loaded object and apply replication data (client), - send object data to interested clients (server) FObjectReplicationProcessor is backed by an IReplicationDataSource, which is a source of replicated object data.
- L48 _public prototype_ `FObjectReplicationProcessor(IReplicationDataSource& DataSource UE_LIFETIMEBOUND);` — @param DataSource Source of the data that is to be sent
- L49 _public prototype_ `virtual ~FObjectReplicationProcessor() = default;`
- L51 _public prototype_ `virtual void ProcessObjects(const FProcessObjectsParams& Params);`
- L68 _protected function_ `FORCEINLINE IReplicationDataSource& GetDataSource() const`
- L71 _protected prototype_ `virtual void ProcessObject(const FObjectProcessArgs& Args) = 0;` — Processes the object.
- L76 _private member_ `IReplicationDataSource& DataSource;` — Abstracts where replication data comes from: could be generated (clients) or received (server or client)

#### struct `UE::ConcertSyncCore::FObjectReplicationProcessor::FObjectProcessArgs`  
`struct FObjectProcessArgs`  
_L55-66_
- L58 _public member_ `FPendingObjectReplicationInfo ObjectInfo;` — Info about the object to process
- L61 _public member_ `IReplicationDataItem& Item;` — Item you can use to extract the replication info from.
- L63 _public function_ `explicit FObjectProcessArgs(FPendingObjectReplicationInfo InObjectInfo, IReplicationDataItem& InItem) : ObjectInfo(MoveTemp(InObjectInfo)) , Item(InItem)`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API CONCERTSYNCCORE_API`
- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace ConcertSyncCore` (scope `UE`)

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncCore/Source/ConcertSyncCore/Public/Replication/Processing/ObjectReplicationReceiver.h` (Public)


#### class `UE::ConcertSyncCore::FObjectReplicationReceiver`  
`class FObjectReplicationReceiver`  
_L20-40_
- desc: Receives replicated object data from all message endpoints and stores it in a FObjectReplicationCache.
- L24 _public prototype_ `FObjectReplicationReceiver(IConcertSession& Session UE_LIFETIMEBOUND, FObjectReplicationCache& ReplicationCache UE_LIFETIMEBOUND);`
- L25 _public prototype_ `virtual ~FObjectReplicationReceiver();`
- L30 _protected function_ `virtual bool ShouldAcceptObject(const FConcertSessionContext& SessionContext, const FConcertReplication_StreamReplicationEvent& StreamEvent, const FConcertReplication_ObjectReplicationEvent& ObjectEvent) const` — Whether the object should be processed.
- L35 _private member_ `IConcertSession& Session;` — The session that is being received on.
- L37 _private member_ `FObjectReplicationCache& ReplicationCache;` — Where received data is stored.
- L39 _private prototype_ `void HandleBatchReplicationEvent(const FConcertSessionContext& SessionContext, const FConcertReplication_BatchReplicationEvent& Event);`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API CONCERTSYNCCORE_API`
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace ConcertSyncCore` (scope `UE`)

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncCore/Source/ConcertSyncCore/Public/Replication/Processing/ObjectReplicationSender.h` (Public)


#### class `UE::ConcertSyncCore::FObjectReplicationSender`  
`class FObjectReplicationSender : public FObjectReplicationProcessor`  
_L18-61_
- inherits: `FObjectReplicationProcessor`
- desc: Sends object data to a specific endpoint ID.
- L27 _public prototype_ `FObjectReplicationSender( const FGuid& TargetEndpointId, IConcertSession& Session UE_LIFETIMEBOUND, IReplicationDataSource& DataSource UE_LIFETIMEBOUND );` — @param TargetEndpointId The endpoints to send to @param Session The session to use for sending @param DataSource Source of the data that is to be sent
- L34 _public prototype_ `virtual void ProcessObjects(const FProcessObjectsParams& Params) override;`
- L40 _protected prototype_ `virtual void ProcessObject(const FObjectProcessArgs& Args) override;`
- L46 _private member_ `const FGuid TargetEndpointId;` — The endpoint data will be sent to
- L49 _private member_ `IConcertSession& Session;` — The session through which replication messages are sent.
- L53 _private member_ `TMap<FConcertReplicatedObjectId, FSequenceId> ObjectsToTraceThisFrame;` — Set by ProcessObject. Used when we actually start sending the data.
- L57 _private member_ `FConcertReplication_BatchReplicationEvent EventToSend;` — This event is filled in ProcessObjects and finally sent to TargetEndpointId.
- L59 _private prototype_ `void MarkObjectForTrace(const FConcertReplicatedObjectId& Object, FSequenceId Id);`
- L60 _private prototype_ `void TraceStartSendingMarkedObjects();`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API CONCERTSYNCCORE_API`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace ConcertSyncCore` (scope `UE`)

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncCore/Source/ConcertSyncCore/Public/Replication/Processing/Proxy/FrequencyTracker.h` (Public)


#### class `UE::ConcertSyncCore::FFrequencyTracker`  
`class FFrequencyTracker`  
_L25-76_
- desc: Keeps track of when objects are processed. Allows querying of whether in a given frame an object is allowed to be processed (or whether it is too early). This keeps a TMap<FSoftObjectPath, FGuid> of objects that were processed in the past. You must periodically call CleanseOutdatedObjects() to avoid leaking objects that are no longer sent. @see FFrequencyTracker_CleanByTick
- L30 _public typedef_ `using FPlatformSecondsTimestamp = double;` — Holds the return value of FPlatformTime::Seconds()
- L46 _public prototype_ `ECanProcessObject TrackAndCheckObject( const FConcertObjectInStreamID& ObjectPath, const FConcertObjectReplicationSettings& ReplicationSettings, const FPlatformSecondsTimestamp NowAsPlatformSeconds = FPlatformTime::Seconds() );` — Ensures ObjectPath is tracked in the cache and returns whether it can be processed now given its frequency settings. Note that multiple streams may be replicating the object and each stream has a different frequency settings for an object, e.g. object StaticMeshActor in stream A may be replicating RelativeLocation at 60 FPS and in stream B may be replicating RelativeRotation at 30 FPS (contrived example). The object can send immediately when it is first added, i.e. TrackAndCheckObject returns ECanProcessObject::CanProcess if the object was not yet registered. @param ObjectPath The object that should be processed @param ReplicationSettings The frequency settings for the object. @param NowAsPlatformSeconds The current time - result of FPlatformTime::Seconds(). Pass this in to avoid excessive time spent on timing. @return Whether the object can be processed now
- L59 _public prototype_ `void OnProcessObject(const FConcertObjectInStreamID& Object, const FPlatformSecondsTimestamp NowAsPlatformSeconds = FPlatformTime::Seconds());` — Called when an object is processed. This is allowed to be called even if TrackAndCheckObject reported it being too early to process the object. @param Object The object that was processed @param NowAsPlatformSeconds The current time - result of FPlatformTime::Seconds(). Pass this in to avoid excessive time spent on timing.
- L65 _public prototype_ `void CleanseOutdatedObjects(const FPlatformSecondsTimestamp CutoffTime);` — Removes all tracked objects were last processed before CutoffTime. @param CutoffTime A past value of FPlatformTime::Seconds()
- L70 _protected function_ `const TMap<FConcertObjectInStreamID, FPlatformSecondsTimestamp>& GetObjectsToLastProcessed() const` — For unit tests
- L75 _private member_ `TMap<FConcertObjectInStreamID, FPlatformSecondsTimestamp> ObjectsToLastProcessed;` — It is important to call CleanseOutdatedObjects to avoid this mapping leaking objects that used to be replicated.

#### class `UE::ConcertSyncCore::FFrequencyTracker_CleanByTick`  
`class FFrequencyTracker_CleanByTick : public FFrequencyTracker`  
_L79-93_
- inherits: `FFrequencyTracker`
- desc: Subclass of FFrequencyTracker that you call Tick on. Every x seconds, this will call CleanseOutdatedObjects itself.
- L83 _public function_ `FFrequencyTracker_CleanByTick(const double InCleanUpInterval = 5.0) : CleanUpIntervalSeconds(InCleanUpInterval)`
- L87 _public prototype_ `void Tick(float DeltaTime, const FPlatformSecondsTimestamp NowAsPlatformSeconds = FPlatformTime::Seconds());`
- L91 _private member_ `const double CleanUpIntervalSeconds;`
- L92 _private member_ `double SecondsSinceLastCleanse = 0.f;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API CONCERTSYNCCORE_API`
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace ConcertSyncCore` (scope `UE`)

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncCore/Source/ConcertSyncCore/Public/Replication/Processing/Proxy/ObjectProcessorProxy.h` (Public)


#### class `UE::ConcertSyncCore::TObjectProcessorProxy`  
`template<TIsObjectProcessorConcept TRealProcessorImpl> class TObjectProcessorProxy : public TRealProcessorImpl`  
_L22-38_
- inherits: `TRealProcessorImpl`
- desc: A proxy processor adds additional operations on top of FObjectReplicationProcessor at compile time. The advantage of this approach is that multiple behaviours can flexibly be chained on top of a real processor implementation with minimal overhead. This class is supposed to be subclassed and call functions on the real processor implementation. The point of this class is to be a marker interface (i.e. when somebody reads TObjectProcessorProxy they know what the intention is).
- L30 _public function_ `template<typename... TArg> TObjectProcessorProxy(TArg&&... Arg) : TRealProcessorImpl(Forward<TArg>(Arg)...)` — @param Arg Perfectly forwarded args for constructing the real processor implementation
- L36 _protected function_ `const TRealProcessorImpl& GetInnerProcessor() const`
- L37 _protected function_ `TRealProcessorImpl& GetInnerProcessor()`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace ConcertSyncCore` (scope `UE`)

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncCore/Source/ConcertSyncCore/Public/Replication/Processing/Proxy/ObjectProcessorProxy_Frequency.h` (Public)


#### class `UE::ConcertSyncCore::TObjectProcessorProxy_Frequency`  
`template<TIsObjectProcessorConcept TRealProcessorImpl> class TObjectProcessorProxy_Frequency : public TObjectProcessorProxy<TRealProcessorImpl>`  
_L21-70_
- inherits: `TObjectProcessorProxy<TRealProcessorImpl>`
- desc: Maps every FSoftObjectPath to FConcertObjectReplicationSettings. Extends the inner IObjectReplicationProcessor by throttling the processing of objects according to the associated frequency settings.
- L30 _public function_ `template<typename... TArg> TObjectProcessorProxy_Frequency(FGetObjectFrequencySettings GetObjectFrequencySettingsDelegate, TArg&&... Arg) : TObjectProcessorProxy<TRealProcessorImpl>(Forward<TArg>(Arg)...) , GetObjectFrequencySettingsDelegate(MoveTemp(GetObjectFrequencySettingsDelegate))` — @param GetObjectFrequencySettingsDelegate Gets the frequency settings for an object in a stream @param Arg Perfectly forwarded args for constructing the real processor implementation
- L41 _public function_ `template<typename... TArg> TObjectProcessorProxy_Frequency(FGetObjectFrequencySettings GetObjectFrequencySettingsDelegate, const float ObjectCacheRetentionSeconds, TArg&&... Arg) : TObjectProcessorProxy<TRealProcessorImpl>(Forward<TArg>(Arg)...) , GetObjectFrequencySettingsDelegate(MoveTemp(GetObjectFrequencySettingsDelegate)) , FrequencyTracker(ObjectCacheRetentionSeconds)` — @param GetObjectFrequencySettingsDelegate Gets the frequency settings for an object in a stream @param ObjectCacheRetentionSeconds If an object goes this time without being processed, it is removed from the cache. @param Arg Perfectly forwarded args for constructing the real processor implementation
- L48 _public prototype_ `virtual void ProcessObjects(const FProcessObjectsParams& Params) override;`
- L54 _protected prototype_ `virtual void ProcessObject(const FObjectReplicationProcessor::FObjectProcessArgs& Args) override;`
- L60 _private member_ `const FGetObjectFrequencySettings GetObjectFrequencySettingsDelegate;` — Gets an objet's frequency settings
- L66 _private member_ `FFrequencyTracker_CleanByTick FrequencyTracker;` — Used for throttling object replication. Tracks when an object is processed and can be queried whether it is time to process the object again.
- L69 _private member_ `double CurrentProcessingTime{};` — Updated with every invocation of ProcessObjects and used by ProcessObject. The result of FPlatformTime::Seconds().
- L73 _function_ `template <TIsObjectProcessorConcept TRealProcessorImpl> void TObjectProcessorProxy_Frequency<TRealProcessorImpl>::ProcessObjects(const FProcessObjectsParams& Params)`
- L84 _function_ `template <TIsObjectProcessorConcept TRealProcessorImpl> void TObjectProcessorProxy_Frequency<TRealProcessorImpl>::ProcessObject(const FObjectReplicationProcessor::FObjectProcessArgs& Args)`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace ConcertSyncCore` (scope `UE`)
- L14 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(FConcertObjectReplicationSettings, FGetObjectFrequencySettings, const FConcertReplicatedObjectId& Object);`
- L14 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(FConcertObjectReplicationSettings, FGetObjectFrequencySettings, const FConcertReplicatedObjectId& Object);` (scope `UE::ConcertSyncCore`)

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncCore/Source/ConcertSyncCore/Public/Replication/Processing/ReplicationDataQueuer.h` (Public)


#### class `UE::ConcertSyncCore::FReplicationDataQueuer`  
`class FReplicationDataQueuer : public IReplicationDataSource , public IReplicationCacheUser , public TSharedFromThis<FReplicationDataQueuer>`  
_L22-61_
- inherits: `IReplicationDataSource,IReplicationCacheUser,TSharedFromThis<FReplicationDataQueuer>`
- desc: Holds on to events received from remote endpoints and exposes them as a source. Received events are received from a FObjectReplicationCache, which makes sure that event data is shared effectively if you created multiple FReplicationDataQueuer based on the same cache. This is relevant server side, where a FReplicationDataQueuer is created for each client. Child classes need to implement IReplicationCacheUser::WantsToAcceptObject. TODO: Remove object data if the object is is meant for becomes unavailable.
- L30 _public prototype_ `virtual void ConsumePendingObjects(TFunctionRef<void(const FPendingObjectReplicationInfo& Info, IReplicationDataItem& Item)> InProcess) override;`
- L34 _public prototype_ `virtual void OnDataCached(const FConcertReplicatedObjectId& Object, FSequenceId SequenceId, TSharedRef<const FConcertReplication_ObjectReplicationEvent> Data) override;`
- L35 _public prototype_ `virtual void OnCachedDataUpdated(const FConcertReplicatedObjectId& Object, FSequenceId SequenceId) override;`
- L44 _protected prototype_ `void BindToCache(FObjectReplicationCache& InReplicationCache);` — Called by subclass factory functions. @param InReplicationCache The cache that the data is sent to. The caller ensures it outlives the lifetime of the widget.
- L57 _private member_ `TMap<FConcertReplicatedObjectId, FPendingObjectData> PendingEvents;` — Stores events as they are received.
- L60 _private member_ `FObjectReplicationCache* ReplicationCache = nullptr;` — Provides us with replication events and shares them effectively.

#### struct `UE::ConcertSyncCore::FReplicationDataQueuer::FPendingObjectData`  
`struct FPendingObjectData`  
_L48-54_
- L51 _public member_ `TSharedPtr<const FConcertReplication_ObjectReplicationEvent> DataToApply;` — Pointer to what OnDataCached passed to us.
- L53 _public member_ `FSequenceId SequenceId;` — The latest SequenceId that the data contains. The data might contain data from multiple sequences.

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API CONCERTSYNCCORE_API`
- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace ConcertSyncCore` (scope `UE`)

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncCore/Source/ConcertSyncCore/Public/Replication/PropertyChainUtils.h` (Public)


#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace ConcertSyncCore` (scope `UE`)
- L13 _namespace_ `namespace PropertyChain` (scope `UE::ConcertSyncCore`)
- L16 _prototype_ `FProperty* ResolveProperty(const UStruct& Class, const FConcertPropertyChain& ChainToResolve, bool bLogOnFail = true);` (scope `UE::ConcertSyncCore::PropertyChain`) — Tries to find the property referenced by the Chain.
- L28 _prototype_ `void ForEachReplicatableProperty( const UStruct& Class, TFunctionRef<EBreakBehavior(const FArchiveSerializedPropertyChain& Chain, FProperty& LeafProperty)> ProcessProperty );` (scope `UE::ConcertSyncCore::PropertyChain`) — Iterates all properties that are supported for replication. This iterates every property as described by FConcertPropertyChain::PathToProperty, which means inner properties of containers, like TArray, TSet, and TMap, are skipped. @param Class The class whose properties to look at @param ProcessProperty Callback @param OnlyChildrenOf Instead of iterating all properties, you can restrict to only receive the child properties of OnlyChildrenOf.
- L43 _prototype_ `void ForEachReplicatableConcertProperty( const UStruct& Class, TFunctionRef<EBreakBehavior(FConcertPropertyChain&& PropertyChain)> ProcessProperty );` (scope `UE::ConcertSyncCore::PropertyChain`) — Iterates all properties that are supported for replication and converts them to FConcertPropertyChain. This iterates every property as described by FConcertPropertyChain::PathToProperty, which means inner properties of containers, like TArray, TSet, and TMap, are skipped. @param Class The class whose properties to look at @param ProcessProperty Callback @param OnlyChildrenOf Instead of iterating all properties, you can restrict to only receive the child properties of OnlyChildrenOf.
- L56 _prototype_ `void BulkConstructConcertChainsFromPaths( const UStruct& Class, uint32 NumPaths, TFunctionRef<bool(const FArchiveSerializedPropertyChain& Chain, FProperty& LeafProperty)> MatchesPath );` (scope `UE::ConcertSyncCore::PropertyChain`) — Efficiently create a batch of paths from the same class hierarchy. @param Class The class for which the paths are created @param NumPaths The number of paths we're looking to create. Once MatchesPath has returned true NumPaths times, this function terminates. @param MatchesPath Determines whether you are interested in this path. If so, do something with it and return true.
- L63 _prototype_ `bool DoPathAndChainsMatch(const TArray<FName>& Path, const FArchiveSerializedPropertyChain& Chain, const FProperty& LeafProperty);` (scope `UE::ConcertSyncCore::PropertyChain`) — Util that can be used with BulkConstructConcertChainsFromPaths. Checks whether Path coincides with Chain & LeafProperty.
- L70 _prototype_ `bool IsReplicatableProperty(const FProperty& LeafProperty);` (scope `UE::ConcertSyncCore::PropertyChain`) — Decides whether the property is allowed for replication. @param LeafProperty The property being considered.
- L73 _prototype_ `bool IsInnerContainerProperty(const FProperty& Property);` (scope `UE::ConcertSyncCore::PropertyChain`) — Util for determining whether this property is the inner property of a container.
- L79 _prototype_ `bool IsPrimitiveProperty(const FProperty& Property);` (scope `UE::ConcertSyncCore::PropertyChain`) — Util for determining whether this property is considered primitive (numeric, bool, enum). Primitive properties in containers are indicated as FConcertPropertyChain::InternalContainerPropertyValueName, which is "Value".
- L84 _prototype_ `bool IsNativeStructProperty(const FProperty& Property);` (scope `UE::ConcertSyncCore::PropertyChain`) — Util for determining whether this struct is considered native. Native struct properties in containers are indicated as FConcertPropertyChain::InternalContainerPropertyValueName, which is "Value".

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncCore/Source/ConcertSyncCore/Public/Replication/PropertyResolutionCache.h` (Public)


#### class `UE::ConcertSyncCore::PropertyChain::FPropertyResolutionCache`  
`class FPropertyResolutionCache`  
_L20-40_
- desc: FConcertPropertyChain::ResolveProperty is expensive because it has to iterate the property hierarchy. This caches look-up results of native classes. By default, properties in Blueprint classes are not cached because they can change at runtime and leave dangling FProperty pointers.
- L25 _public prototype_ `FProperty* ResolveAndCache(const UStruct& Struct, const FConcertPropertyChain& Chain);` — Resolves the property chain and caches the result;
- L28 _public function_ `void Invalidate(const UStruct& Struct)` — Removes the class from the cache.
- L30 _public function_ `void Clear(int32 ExpectedNumElements = 0)` — Removes everything from the cache.
- L39 _private member_ `TMap<const UStruct*, FClassCache> CachedProperties;`

#### struct `UE::ConcertSyncCore::PropertyChain::FPropertyResolutionCache::FClassCache`  
`struct FClassCache`  
_L34-37_
- L36 _public member_ `TMap<FConcertPropertyChain, FProperty*> Cache;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API CONCERTSYNCCORE_API`
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace ConcertSyncCore` (scope `UE`)
- L12 _namespace_ `namespace PropertyChain` (scope `UE::ConcertSyncCore`)

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncCore/Source/ConcertSyncCore/Public/Replication/ReplicationPropertyFilter.h` (Public)


#### class `UE::ConcertSyncCore::FReplicationPropertyFilter`  
`class FReplicationPropertyFilter`  
_L32-51_
- desc: Util that bridges IObjectReplicationFormat::FAllowPropertyFunc and FConcertPropertySelection. Intended to be used like this: { const FConcertPropertySelection& Selection = ...; IObjectReplicationFormat& Format = ...; UObject& ReplicatedObject = ...; FReplicationPropertyFilter Filter(Selection); Format.CreateReplicationEvent(Object, [&Filter](const FArchiveSerializedPropertyChain* Chain, const FProperty&& Property){ return Filter.IsPropertyInSelection(Chain, Property); } }
- L34 _private member_ `const FConcertPropertySelection& PropertySelection;`
- L40 _private member_ `TMap<FName, TArray<const FConcertPropertyChain*>> LeafToChain;` — Maps the name of every leaf property to the chaisn PropertySelection.ReplicatedProperties that contain the property name at the end of the chain. This speeds up matching chain and property.
- L43 _public prototype_ `FReplicationPropertyFilter(const FConcertPropertySelection& PropertySelection);`
- L50 _public prototype_ `bool ShouldSerializeProperty(const FArchiveSerializedPropertyChain* Chain, const FProperty& Property) const;` — @param Chain Can be nullptr or non-null and empty - both imply the Property is a root property. @param Property The property that Chain leads to @return Whether Property is in PropertySelection.

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API CONCERTSYNCCORE_API`
- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace ConcertSyncCore` (scope `UE`)

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncCore/Source/ConcertSyncCore/Public/Replication/SyncControlState.h` (Public)


#### class `UE::ConcertSyncCore::Replication::FSyncControlState`  
`class FSyncControlState`  
_L30-118_
- desc: Keeps track of the sync control (AllowedObjects), which is a set of objects a client is allowed to replicate. It knows how to parse network messages that explicitly and implicitly change sync control and update AllowedObjects. This class does not know where the network messages come from and is designed to be used as utility by lower level systems.
- L40 _public prototype_ `FSyncControlState() = default;`
- L43 _public function_ `FSyncControlState(TSet<FConcertObjectInStreamID>&& AllowedObjects) : AllowedObjects(MoveTemp(AllowedObjects))` — Not explicit to make it useful to use
- L46 _public function_ `FSyncControlState(const TSet<FConcertObjectInStreamID>& AllowedObjects) : AllowedObjects(AllowedObjects)`
- L51 _public function_ `bool IsObjectAllowed(const FConcertObjectInStreamID& Object) const` — @return Whether Object is allowed to be replicated.
- L53 _public function_ `uint32 Num() const` — @return Number of allowed objects
- L57 _public prototype_ `template<typename TProcessObject> bool EnumerateAllowedObjects(TProcessObject Callback) const requires std::is_invocable_r_v<EBreakBehavior, TProcessObject, const FConcertObjectInStreamID&>;` — Enumerates all sync controlled objects.
- L61 _public prototype_ `template<CObjectInStreamInvocable TOnAllowed, CObjectInStreamInvocable TOnDisallowed> static void EnumerateChanges(const FConcertReplication_ChangeSyncControl& Event, TOnAllowed&& OnAllowed, TOnDisallowed&& OnDisallowed);` — Enumerates the changes that would be made by applying this event.
- L65 _public prototype_ `template<CObjectInStreamInvocable TOnAllowed, CObjectInStreamInvocable TOnDisallowed> void AppendChanges(const FConcertReplication_ChangeSyncControl& Event, TOnAllowed&& OnAllowed, TOnDisallowed&& OnDisallowed);` — Combines past state with an incoming sync control event.
- L66 _public prototype_ `void AppendChanges(const FConcertReplication_ChangeSyncControl& Event);`
- L70 _public prototype_ `template<CObjectInStreamInvocable TOnAllowed, CObjectInStreamInvocable TOnDisallowed> void AppendAuthorityChange(const FConcertReplication_ChangeAuthority_Request& Request, const FConcertReplication_ChangeSyncControl& Response, TOnAllowed&& OnAllowed, TOnDisallowed&& OnDisallowed);` — Combines implicit and explicit sync control changes caused by authority changes.
- L71 _public prototype_ `void AppendAuthorityChange(const FConcertReplication_ChangeAuthority_Request& Request, const FConcertReplication_ChangeSyncControl& Response);`
- L75 _public prototype_ `template<CObjectInStreamInvocable TOnDisallowed> void AppendStreamChange(const FConcertReplication_ChangeStream_Request& Request, TOnDisallowed&& OnDisallowed);` — Combines implicit sync control changes caused by stream change.
- L76 _public prototype_ `void AppendStreamChange(const FConcertReplication_ChangeStream_Request& Request);`
- L83 _public prototype_ `template<CObjectInStreamInvocable TOnDisallowed> FPredictedObjectRemoval PredictAndApplyMuteChanges(const FConcertReplication_ChangeMuteState_Request& Request, TOnDisallowed&& OnDisallowed);` — Combines implicit sync control changes caused by the local client sending a mute event. @return The objects that were predictively removed by the request. Pass this back into AppendChanges once you get the response.
- L84 _public prototype_ `FPredictedObjectRemoval PredictAndApplyMuteChanges(const FConcertReplication_ChangeMuteState_Request& Request);`
- L91 _public prototype_ `template<CObjectInStreamInvocable TOnAllowed> void ApplyOrRevertMuteResponse(const FPredictedObjectRemoval& ObjectsRemovedInRequest, const FConcertReplication_ChangeMuteState_Response& Response, TOnAllowed&& OnAllowed);` — Looks at the response: - if the change failed, reverts the predictively removed sync control - if the change succeeded, appends the contained sync control
- L92 _public prototype_ `void ApplyOrRevertMuteResponse(const FPredictedObjectRemoval& ObjectsRemovedInRequest, const FConcertReplication_ChangeMuteState_Response& Response);`
- L99 _public prototype_ `template<CObjectInStreamInvocable TOnDisallowed> FPredictedObjectRemoval PredictAndApplyRestoreContentChanges(const FConcertReplication_RestoreContent_Request& Request, TOnDisallowed&& OnDisallowed);` — If the request replaces the content, removes sync control for all objects. @return The objects that were predictively removed by the request. Pass this back into AppendChanges once you get the response.
- L106 _public prototype_ `template<CObjectInStreamInvocable TOnAllowed, CObjectInStreamInvocable TOnDisallowed> void ApplyOrRevertRestoreContentResponse(const FPredictedObjectRemoval& ObjectsRemovedInRequest, const FConcertReplication_RestoreContent_Response& Response, TOnAllowed&& OnAllowed, TOnDisallowed&& OnDisallowed);` — Looks at the response - if the change failed, reverts the predictively removed sync control. - if the change succeeded, appends the contained sync control.
- L117 _private member_ `TSet<FConcertObjectInStreamID> AllowedObjects;` — The objects the client has sync control over, i.e. is allowed to replicate.
- L121 _function_ `template<typename TProcessObject> bool FSyncControlState::EnumerateAllowedObjects(TProcessObject Callback) const requires std::is_invocable_r_v<EBreakBehavior, TProcessObject, const FConcertObjectInStreamID&>`
- L135 _function_ `template <CObjectInStreamInvocable TOnAllowed, CObjectInStreamInvocable TOnDisallowed> void FSyncControlState::EnumerateChanges(const FConcertReplication_ChangeSyncControl& Event, TOnAllowed&& OnAllowed, TOnDisallowed&& OnDisallowed)`
- L152 _function_ `template<CObjectInStreamInvocable TOnAllowed, CObjectInStreamInvocable TOnDisallowed> void FSyncControlState::AppendChanges(const FConcertReplication_ChangeSyncControl& Event, TOnAllowed&& OnAllowed, TOnDisallowed&& OnDisallowed)`
- L160 _function_ `inline void FSyncControlState::AppendChanges(const FConcertReplication_ChangeSyncControl& Event)`
- L166 _function_ `template <CObjectInStreamInvocable TOnAllowed, CObjectInStreamInvocable TOnDisallowed> void FSyncControlState::AppendAuthorityChange(const FConcertReplication_ChangeAuthority_Request& Request, const FConcertReplication_ChangeSyncControl& Response, TOnAllowed&& OnAllowed, TOnDisallowed&& OnDisallowed)`
- L185 _function_ `inline void FSyncControlState::AppendAuthorityChange(const FConcertReplication_ChangeAuthority_Request& Request, const FConcertReplication_ChangeSyncControl& Response)`
- L191 _function_ `template <CObjectInStreamInvocable TOnDisallowed> void FSyncControlState::AppendStreamChange(const FConcertReplication_ChangeStream_Request& Request, TOnDisallowed&& OnDisallowed)`
- L223 _function_ `inline void FSyncControlState::AppendStreamChange(const FConcertReplication_ChangeStream_Request& Request)`
- L229 _function_ `template <CObjectInStreamInvocable TOnDisallowed> FSyncControlState::FPredictedObjectRemoval FSyncControlState::PredictAndApplyMuteChanges(const FConcertReplication_ChangeMuteState_Request& Request, TOnDisallowed&& OnDisallowed)`
- L272 _function_ `inline FSyncControlState::FPredictedObjectRemoval FSyncControlState::PredictAndApplyMuteChanges(const FConcertReplication_ChangeMuteState_Request& Request)`
- L278 _function_ `template <CObjectInStreamInvocable TOnAllowed> void FSyncControlState::ApplyOrRevertMuteResponse(const FPredictedObjectRemoval& ObjectsRemovedInRequest, const FConcertReplication_ChangeMuteState_Response& Response, TOnAllowed&& OnAllowed)`
- L295 _function_ `inline void FSyncControlState::ApplyOrRevertMuteResponse(const FPredictedObjectRemoval& ObjectsRemovedInRequest, const FConcertReplication_ChangeMuteState_Response& Response)`
- L301 _function_ `template <CObjectInStreamInvocable TOnDisallowed> FSyncControlState::FPredictedObjectRemoval FSyncControlState::PredictAndApplyRestoreContentChanges( const FConcertReplication_RestoreContent_Request& Request, TOnDisallowed&& OnDisallowed )`
- L323 _function_ `template <CObjectInStreamInvocable TOnAllowed, CObjectInStreamInvocable TOnDisallowed> void FSyncControlState::ApplyOrRevertRestoreContentResponse( const FPredictedObjectRemoval& ObjectsRemovedInRequest, const FConcertReplication_RestoreContent_Response& Response, TOnAllowed&& OnAllowed, TOnDisallowed&& OnDisallowed )`

#### class `UE::ConcertSyncCore::Replication::FSyncControlState::FPredictedObjectRemoval`  
`class FPredictedObjectRemoval`  
_L34-38_
- L37 _private member_ `TSet<FConcertObjectInStreamID> Objects;`

#### Free symbols / members of external scopes

- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace ConcertSyncCore` (scope `UE`)
- L19 _namespace_ `namespace Replication` (scope `UE::ConcertSyncCore`)
- L108 _function_ `friend bool operator==(const FSyncControlState& Left, const FSyncControlState& Right)` (scope `UE::ConcertSyncCore::Replication`)
- L112 _function_ `friend bool operator!=(const FSyncControlState& Left, const FSyncControlState& Right)` (scope `UE::ConcertSyncCore::Replication`)
- L155 _function_ `EnumerateChanges(Event, [this, &OnAllowed](const FConcertObjectInStreamID& Object){ AllowedObjects.Add(Object); OnAllowed(Object); }, [this, &OnDisallowed](const FConcertObjectInStreamID& Object){ AllowedObjects.Remove(Object); OnDisallowed(Object); } );` (scope `UE::ConcertSyncCore::Replication::FSyncControlState::AppendChanges`)
- L162 _function_ `AppendChanges(Event, [](const FConcertObjectInStreamID&){}, [](const FConcertObjectInStreamID&){});` (scope `UE::ConcertSyncCore::Replication::FSyncControlState::AppendChanges`)
- L187 _function_ `AppendAuthorityChange(Request, Response, [](const FConcertObjectInStreamID&){}, [](const FConcertObjectInStreamID&){});` (scope `UE::ConcertSyncCore::Replication::FSyncControlState::AppendAuthorityChange`)
- L225 _function_ `AppendStreamChange(Request, [](const FConcertObjectInStreamID&){});` (scope `UE::ConcertSyncCore::Replication::FSyncControlState::AppendStreamChange`)
- L233 _function_ `` (scope `UE::ConcertSyncCore::Replication::FSyncControlState::PredictAndApplyMuteChanges`)
- L274 _function_ `return PredictAndApplyMuteChanges(Request, [](const FConcertObjectInStreamID&){});` (scope `UE::ConcertSyncCore::Replication::FSyncControlState::PredictAndApplyMuteChanges`)
- L285 _function_ `` (scope `UE::ConcertSyncCore::Replication::FSyncControlState::ApplyOrRevertMuteResponse`)
- L297 _function_ `ApplyOrRevertMuteResponse(ObjectsRemovedInRequest, Response, [](const FConcertObjectInStreamID&){});` (scope `UE::ConcertSyncCore::Replication::FSyncControlState::ApplyOrRevertMuteResponse`)
