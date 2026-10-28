# Editor / EditorConfig

- module root: `Source/Editor/EditorConfig`
- headers: 7; symbols: 242
- symbol kinds: class=7, delegate=2, enum=3, enumerator=11, function=23, macro=4, member=30, namespace=2, prototype=154, struct=5, typedef=1
- PrivateDependencyModuleNames: Core, CoreUObject, EditorSubsystem, Engine, Json, UnrealEd

### `Source/Editor/EditorConfig/Public/EditorConfig.h` (Public)


#### class `FEditorConfig`  
`class FEditorConfig`  
_L32-112_
- L41 _public prototype_ `FEditorConfig();`
- L43 _public prototype_ `void SetParent(TSharedPtr<FEditorConfig> InConfig);`
- L45 _public prototype_ `bool LoadFromString(FStringView Content);`
- L46 _public prototype_ `bool LoadFromFile(FStringView FilePath);`
- L47 _public prototype_ `bool SaveToString(FString& OutResult) const;`
- L49 _public function_ `bool IsValid() const`
- L53 _public prototype_ `template <typename T> bool TryGetStruct(FStringView Key, T& OutValue, EPropertyFilter Filter = EPropertyFilter::MetadataOnly) const;` — UStruct & UObject
- L55 _public prototype_ `template <typename T> bool TryGetUObject(FStringView Key, T& OutValue, EPropertyFilter Filter = EPropertyFilter::MetadataOnly) const;`
- L58 _public prototype_ `template <typename T> bool TryGetRootStruct(T& OutValue, EPropertyFilter Filter = EPropertyFilter::MetadataOnly) const;`
- L60 _public prototype_ `template <typename T> bool TryGetRootUObject(T& OutValue, EPropertyFilter Filter = EPropertyFilter::MetadataOnly) const;`
- L62 _public prototype_ `template <typename T> bool TryGetRootUObject(T* OutValue, EPropertyFilter Filter = EPropertyFilter::MetadataOnly) const;`
- L64 _public prototype_ `bool TryGetRootStruct(const UStruct* Class, void* OutValue, EPropertyFilter Filter = EPropertyFilter::MetadataOnly) const;`
- L65 _public prototype_ `bool TryGetRootUObject(const UClass* Class, UObject* OutValue, EPropertyFilter Filter = EPropertyFilter::MetadataOnly) const;`
- L68 _public prototype_ `template <typename T> void SetStruct(FStringView Key, const T& InValue, EPropertyFilter Filter = EPropertyFilter::MetadataOnly);`
- L70 _public prototype_ `template <typename T> void SetUObject(FStringView Key, const T& InValue, EPropertyFilter Filter = EPropertyFilter::MetadataOnly);`
- L73 _public prototype_ `template <typename T> void SetRootStruct(const T& InValue, EPropertyFilter Filter = EPropertyFilter::MetadataOnly);`
- L75 _public prototype_ `template <typename T> void SetRootUObject(const T& InValue, EPropertyFilter Filter = EPropertyFilter::MetadataOnly);`
- L77 _public prototype_ `void SetRootStruct(const UStruct* Class, const void* Instance, EPropertyFilter Filter = EPropertyFilter::MetadataOnly);`
- L78 _public prototype_ `void SetRootUObject(const UClass* Class, const UObject* Instance, EPropertyFilter Filter = EPropertyFilter::MetadataOnly);`
- L80 _public prototype_ `bool HasOverride(FStringView Key) const;`
- L82 _public prototype_ `void OnSaved();`
- L84 _public prototype_ `DECLARE_EVENT_OneParam(FEditorConfig, FOnEditorConfigDirtied, const FEditorConfig&);`
- L85 _public function_ `FOnEditorConfigDirtied& OnEditorConfigDirtied()`
- L91 _private prototype_ `static void ReadUObject(const TSharedPtr<FJsonObject>& JsonObject, const UClass* Class, UObject* Instance, EPropertyFilter Filter);`
- L92 _private prototype_ `static void ReadStruct(const TSharedPtr<FJsonObject>& JsonObject, const UStruct* Struct, void* Instance, UObject* Owner, EPropertyFilter Filter);`
- L93 _private prototype_ `static void ReadValue(const TSharedPtr<FJsonValue>& JsonValue, const FProperty* Property, void* DataPtr, UObject* Owner);`
- L95 _private prototype_ `static TSharedPtr<FJsonObject> WriteStruct(const UStruct* Struct, const void* Instance, const void* Defaults, EPropertyFilter Filter);`
- L96 _private prototype_ `static TSharedPtr<FJsonObject> WriteUObject(const UClass* Class, const UObject* Instance, EPropertyFilter Filter);`
- L97 _private prototype_ `static TSharedPtr<FJsonValue> WriteArray(const FArrayProperty* ArrayProperty, const void* DataPtr);`
- L98 _private prototype_ `static TSharedPtr<FJsonValue> WriteSet(const FSetProperty* Property, const void* DataPtr);`
- L99 _private prototype_ `static TSharedPtr<FJsonValue> WriteMap(const FMapProperty* Property, const void* DataPtr);`
- L100 _private prototype_ `static TSharedPtr<FJsonValue> WriteValue(const FProperty* Property, const void* DataPtr, const void* Defaults);`
- L102 _private prototype_ `bool SaveToFile(FStringView FilePath) const;`
- L104 _private prototype_ `void SetDirty();`
- L107 _private member_ `TSharedPtr<UE::FJsonConfig> JsonConfig;`
- L108 _private member_ `TSharedPtr<FEditorConfig> ParentConfig;`
- L110 _private member_ `FOnEditorConfigDirtied EditorConfigDirtiedEvent;`
- L111 _private member_ `bool Dirty { false };`
- L115 _function_ `template <typename T> bool FEditorConfig::TryGetStruct(FStringView Key, T& OutValue, EPropertyFilter Filter) const`
- L141 _function_ `template <typename T> bool FEditorConfig::TryGetUObject(FStringView Key, T& OutValue, EPropertyFilter Filter) const`
- L169 _function_ `template <typename T> bool FEditorConfig::TryGetRootStruct(T& OutValue, EPropertyFilter Filter) const`
- L175 _function_ `template <typename T> bool FEditorConfig::TryGetRootUObject(T& OutValue, EPropertyFilter Filter) const`
- L183 _function_ `template <typename T> bool FEditorConfig::TryGetRootUObject(T* OutValue, EPropertyFilter Filter) const`
- L192 _function_ `template <typename T> void FEditorConfig::SetStruct(FStringView Key, const T& InValue, EPropertyFilter Filter)`
- L206 _function_ `template <typename T> void FEditorConfig::SetUObject(FStringView Key, const T& InValue, EPropertyFilter Filter)`
- L222 _function_ `template <typename T> void FEditorConfig::SetRootStruct(const T& InValue, EPropertyFilter Filter)`
- L228 _function_ `template <typename T> void FEditorConfig::SetRootUObject(const T& InValue, EPropertyFilter Filter)`

#### enum `FEditorConfig::EPropertyFilter`  
`enum class EPropertyFilter`  
_L35-39_
- L37 _public enumerator_ `All`
- L38 _public enumerator_ `MetadataOnly`

#### Free symbols / members of external scopes

- L19 _macro_ `#define UE_API EDITORCONFIG_API`
- L84 _delegate_ `DECLARE_EVENT_OneParam(FEditorConfig, FOnEditorConfigDirtied, const FEditorConfig&);`

### `Source/Editor/EditorConfig/Public/EditorConfigBase.h` (Public)


#### class `UEditorConfigBase`  
`class UEditorConfigBase : public UObject`  
_L15-26_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- desc: Inherit from this class to simplify saving and loading properties from editor configs.
- L22 _public prototype_ `bool LoadEditorConfig();` — Load any properties of this class into properties marked with metadata tag "EditorConfig" from the class's EditorConfig
- L25 _public prototype_ `bool SaveEditorConfig() const;` — Save any properties of this class in properties marked with metadata tag "EditorConfig" into the class's EditorConfig.

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API EDITORCONFIG_API`

### `Source/Editor/EditorConfig/Public/EditorConfigModule.h` (Public)


#### class `FEditorConfigModule`  
`class FEditorConfigModule : public IModuleInterface`  
_L10-12_
- inherits: `IModuleInterface`

#### Free symbols / members of external scopes

- L8 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogEditorConfig, Log, All);`
- L8 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogEditorConfig, Log, All);`

### `Source/Editor/EditorConfig/Public/EditorConfigSubsystem.h` (Public)


#### class `UEditorConfigSubsystem`  
`class UEditorConfigSubsystem : public UEditorSubsystem, public FTickableEditorObject`  
_L15-123_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UEditorSubsystem,FTickableEditorObject`
- L22 _public prototype_ `UEditorConfigSubsystem();`
- L31 _public prototype_ `template <typename TObject> bool LoadConfigObject(TObject* Object, FEditorConfig::EPropertyFilter Filter = FEditorConfig::EPropertyFilter::MetadataOnly);` — Load a config from the root of the JSON file into a given UObject. This loads the config from the UCLASS's EditorConfig="ConfigName" metadata. @param Object The object to load into. @param Filter Whether to load all properties, or only ones marked with the EditorConfig metadata.
- L40 _public prototype_ `template <typename TObject> bool SaveConfigObject(const TObject* Object, FEditorConfig::EPropertyFilter Filter = FEditorConfig::EPropertyFilter::MetadataOnly);` — Save the given UObject to the root of the JSON config. This saves the config to the UCLASS's EditorConfig="ConfigName" metadata. @param Object The object to save. @param Filter Whether to save all properties, or only ones marked with the EditorConfig metadata.
- L49 _public prototype_ `bool LoadConfigObject(const UClass* Class, UObject* Object, FEditorConfig::EPropertyFilter = FEditorConfig::EPropertyFilter::MetadataOnly);` — Load a config from the root of the JSON file into a given UObject. This loads the config from the UCLASS's EditorConfig="ConfigName" metadata. @param Class The UClass of the object. @param Object The UObject instance to load into. @param Filter Whether to load all properties, or only ones marked with the EditorConfig metadata.
- L58 _public prototype_ `bool SaveConfigObject(const UClass* Class, const UObject* Object, FEditorConfig::EPropertyFilter = FEditorConfig::EPropertyFilter::MetadataOnly);` — Save the given UObject of the given class to the root of the JSON config. This saves the config to the UCLASS's EditorConfig="ConfigName" metadata. @param Class The UClass of the object. @param Object The UObject instance to save. @param Filter Whether to save all properties, or only ones marked with the EditorConfig metadata.
- L73 _public prototype_ `TSharedRef<FEditorConfig> FindOrLoadConfig(FStringView ConfigName, ESearchDirectoryType IncludedTypes = ESearchDirectoryType::User);` — Find a config with the given name that has already been loaded, load it if it hasn't been, or create one with the given name. @param IncludedTypes The "lowest" level of search directory types to include, ex. If IncludedTypes is set to Project, only Engine and Project paths will be loaded
- L78 _public prototype_ `void SaveConfig(TSharedRef<FEditorConfig> Config);` — Save the given config to the location it was loaded.
- L81 _public prototype_ `bool ReloadConfig(TSharedRef<FEditorConfig> Config);` — Force reload the given config and all its (current and potential) parents from disk.
- L87 _public prototype_ `void AddSearchDirectory(ESearchDirectoryType Type, FStringView SearchDir);` — Append a new config search directory to the given type. Engine directories are searched first, then Project, then ProjectOverrides, then User.
- L96 _public prototype_ `static void EarlyAddSearchDirectory(ESearchDirectoryType Type, FStringView SearchDir);` — Append a new config search directory to the given type early. Engine directories are searched first, then Project, then ProjectOverrides, then User. Note: this function can only be called before the UEditorConfigSubsystem is initialized otherwise it will assert. This function is useful if there is a need to register a layer of config before any config read could happen.
- L99 _private prototype_ `void Initialize(FSubsystemCollectionBase& Collection) override;`
- L100 _private prototype_ `void Deinitialize() override;`
- L101 _private prototype_ `void OnSaveCompleted(TSharedPtr<FEditorConfig> Config);`
- L102 _private prototype_ `void OnEditorConfigDirtied(const FEditorConfig& Config);`
- L105 _private prototype_ `void Tick(float DeltaTime) override;` — FTickableEditorObject interface
- L106 _private prototype_ `TStatId GetStatId() const override;`
- L117 _private member_ `FCriticalSection SaveLock;`
- L118 _private member_ `TArray<FPendingSave> PendingSaves;`
- L119 _private member_ `TArray<TPair<ESearchDirectoryType, FString>> SearchDirectories;`
- L120 _private member_ `TMap<FString, TSharedPtr<FEditorConfig>> LoadedConfigs;`
- L122 _private member_ `static TArray<TPair<ESearchDirectoryType, FString>> EarlyRegistredSearchDirectories;`
- L126 _function_ `template <typename TObject> bool UEditorConfigSubsystem::LoadConfigObject(TObject* Object, FEditorConfig::EPropertyFilter Filter)`
- L136 _function_ `template <typename TObject> bool UEditorConfigSubsystem::SaveConfigObject(const TObject* Object, FEditorConfig::EPropertyFilter Filter)`

#### enum `UEditorConfigSubsystem::ESearchDirectoryType`  
`enum class ESearchDirectoryType : uint8`  
_L60-66_
- L62 _public enumerator_ `Engine`
- L63 _public enumerator_ `Project`
- L64 _public enumerator_ `ProjectOverrides`
- L65 _public enumerator_ `User`

#### struct `UEditorConfigSubsystem::FPendingSave`  
`struct FPendingSave`  
_L109-115_
- L111 _public member_ `FString FileName;`
- L112 _public member_ `TSharedPtr<FEditorConfig> Config;`
- L113 _public member_ `TFuture<bool> WasSuccess;`
- L114 _public member_ `float TimeSinceQueued { 0 };`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API EDITORCONFIG_API`

### `Source/Editor/EditorConfig/Public/EditorMetadataOverrides.h` (Public)


#### struct `FMetadataSet`  
`struct FMetadataSet`  
_L31-47_
- reflection: `USTRUCT()`
- L37 _public member_ `TMap<FName, FString> Strings;` — `UPROPERTY()` — map of metadata key to metadata value
- L40 _public member_ `TMap<FName, bool> Bools;` — `UPROPERTY()`
- L43 _public member_ `TMap<FName, int32> Ints;` — `UPROPERTY()`
- L46 _public member_ `TMap<FName, float> Floats;` — `UPROPERTY()`

#### struct `FStructMetadata`  
`struct FStructMetadata`  
_L50-60_
- reflection: `USTRUCT()`
- L56 _public member_ `TMap<FName, FMetadataSet> Fields;` — `UPROPERTY()` — map of field name to field metadata
- L59 _public member_ `FMetadataSet StructMetadata;` — `UPROPERTY()`

#### struct `FMetadataConfig`  
`struct FMetadataConfig`  
_L63-70_
- reflection: `USTRUCT()`
- L69 _public member_ `TMap<FName, FStructMetadata> Classes;` — `UPROPERTY()` — map of class name to class metadata

#### enum `EMetadataType`  
`enum class EMetadataType`  
_L73-80_
- reflection: `UENUM()`
- L75 _public enumerator_ `None`
- L76 _public enumerator_ `Bool`
- L77 _public enumerator_ `Int`
- L78 _public enumerator_ `Float`
- L79 _public enumerator_ `String`

#### class `UEditorMetadataOverrides`  
`class UEditorMetadataOverrides : public UEditorSubsystem`  
_L83-160_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UEditorSubsystem`
- L89 _public prototype_ `UEditorMetadataOverrides();`
- L90 _public prototype_ `virtual ~UEditorMetadataOverrides() = default;`
- L92 _public prototype_ `virtual void Initialize(FSubsystemCollectionBase& Collection) override;`
- L94 _public prototype_ `bool LoadFromConfig(TSharedPtr<FEditorConfig> Config);`
- L95 _public prototype_ `void Save();`
- L97 _public prototype_ `EMetadataType GetMetadataType(const FField* Field, FName Key) const;`
- L98 _public prototype_ `EMetadataType GetMetadataType(const UStruct* Struct, FName Key) const;`
- L100 _public prototype_ `bool GetStringMetadata(const FField* Field, FName Key, FString& OutValue) const;`
- L101 _public prototype_ `void SetStringMetadata(const FField* Field, FName Key, FStringView Value);`
- L103 _public prototype_ `bool GetFloatMetadata(const FField* Field, FName Key, float& OutValue) const;`
- L104 _public prototype_ `void SetFloatMetadata(const FField* Field, FName Key, float Value);`
- L106 _public prototype_ `bool GetIntMetadata(const FField* Field, FName Key, int32& OutValue) const;`
- L107 _public prototype_ `void SetIntMetadata(const FField* Field, FName Key, int32 Value);`
- L109 _public prototype_ `bool GetBoolMetadata(const FField* Field, FName Key, bool& OutValue) const;`
- L110 _public prototype_ `void SetBoolMetadata(const FField* Field, FName Key, bool Value);`
- L112 _public prototype_ `bool GetClassMetadata(const FField* Field, FName Key, UClass*& OutValue) const;`
- L113 _public prototype_ `void SetClassMetadata(const FField* Field, FName Key, UClass* Value);`
- L115 _public prototype_ `bool GetArrayMetadata(const FField* Field, FName Key, TArray<FString>& OutValue) const;`
- L116 _public prototype_ `void SetArrayMetadata(const FField* Field, FName Key, const TArray<FString>& Value);`
- L118 _public prototype_ `void AddToArrayMetadata(const FField* Field, FName Key, const FString& Value);`
- L119 _public prototype_ `void RemoveFromArrayMetadata(const FField* Field, FName Key, const FString& Value);`
- L121 _public prototype_ `void RemoveMetadata(const FField* Field, FName Key);`
- L123 _public prototype_ `bool GetStringMetadata(const UStruct* Struct, FName Key, FString& OutValue) const;`
- L124 _public prototype_ `void SetStringMetadata(const UStruct* Struct, FName Key, FStringView Value);`
- L126 _public prototype_ `bool GetFloatMetadata(const UStruct* Struct, FName Key, float& OutValue) const;`
- L127 _public prototype_ `void SetFloatMetadata(const UStruct* Struct, FName Key, float Value);`
- L129 _public prototype_ `bool GetIntMetadata(const UStruct* Struct, FName Key, int32& OutValue) const;`
- L130 _public prototype_ `void SetIntMetadata(const UStruct* Struct, FName Key, int32 Value);`
- L132 _public prototype_ `bool GetBoolMetadata(const UStruct* Struct, FName Key, bool& OutValue) const;`
- L133 _public prototype_ `void SetBoolMetadata(const UStruct* Struct, FName Key, bool Value);`
- L135 _public prototype_ `bool GetClassMetadata(const UStruct* Struct, FName Key, UClass*& OutValue) const;`
- L136 _public prototype_ `void SetClassMetadata(const UStruct* Struct, FName Key, UClass* Value);`
- L138 _public prototype_ `bool GetArrayMetadata(const UStruct* Struct, FName Key, TArray<FString>& OutValue) const;`
- L139 _public prototype_ `void SetArrayMetadata(const UStruct* Struct, FName Key, const TArray<FString>& Value);`
- L141 _public prototype_ `void AddToArrayMetadata(const UStruct* Struct, FName Key, const FString& Value);`
- L142 _public prototype_ `void RemoveFromArrayMetadata(const UStruct* Struct, FName Key, const FString& Value);`
- L144 _public prototype_ `void RemoveMetadata(const UStruct* Struct, FName Key);`
- L147 _private prototype_ `const FMetadataSet* FindFieldMetadata(const FField* Field) const;`
- L148 _private prototype_ `FMetadataSet* FindFieldMetadata(const FField* Field);`
- L149 _private prototype_ `FMetadataSet* FindOrAddFieldMetadata(const FField* Field);`
- L151 _private prototype_ `const FMetadataSet* FindStructMetadata(const UStruct* Struct) const;`
- L152 _private prototype_ `FMetadataSet* FindStructMetadata(const UStruct* Struct);`
- L153 _private prototype_ `FMetadataSet* FindOrAddStructMetadata(const UStruct* Struct);`
- L155 _private prototype_ `void OnCompleted(bool bSuccess);`
- L158 _private member_ `TSharedPtr<FEditorConfig> SourceConfig;`
- L159 _private member_ `FMetadataConfig LoadedMetadata;`

#### Free symbols / members of external scopes

- L21 _macro_ `#define UE_API EDITORCONFIG_API`

### `Source/Editor/EditorConfig/Public/JsonConfig.h` (Public)


#### class `UE::FJsonPath`  
`class FJsonPath`  
_L26-59_
- L35 _public prototype_ `FJsonPath();`
- L36 _public prototype_ `FJsonPath(const TCHAR* Path);`
- L37 _public prototype_ `FJsonPath(FStringView Path);`
- L38 _public prototype_ `FJsonPath(const FJsonPath& Other);`
- L39 _public prototype_ `FJsonPath(FJsonPath&& Other);`
- L41 _public function_ `bool IsValid() const`
- L42 _public function_ `const int32 Length() const`
- L44 _public prototype_ `void Append(FStringView Name);`
- L45 _public prototype_ `void SetArrayIndex(int32 Index);`
- L47 _public prototype_ `FJsonPath GetSubPath(int32 NumParts) const;`
- L49 _public prototype_ `FString ToString() const;`
- L51 _public function_ `const FPart& operator[](int32 Idx) const`
- L52 _public function_ `const TArray<FPart>& GetAll() const`
- L55 _private prototype_ `void ParsePath(const FString& InPath);`
- L58 _private member_ `TArray<FPart> PathParts;`

#### struct `UE::FJsonPath::FPart`  
`struct FPart`  
_L29-33_
- L31 _public member_ `FString Name;`
- L32 _public member_ `int32 Index = INDEX_NONE;`

#### class `UE::FJsonConfig`  
`class FJsonConfig`  
_L63-156_
- L66 _public prototype_ `FJsonConfig();`
- L68 _public prototype_ `void SetParent(const TSharedPtr<FJsonConfig>& Parent);`
- L70 _public prototype_ `bool LoadFromFile(FStringView FilePath);`
- L71 _public prototype_ `bool LoadFromString(FStringView Content);`
- L73 _public prototype_ `bool SaveToFile(FStringView FilePath) const;`
- L74 _public prototype_ `bool SaveToString(FString& OutResult) const;`
- L76 _public function_ `bool IsValid() const`
- L78 _public prototype_ `const FJsonConfig* GetParentConfig() const;`
- L81 _public prototype_ `template <typename T> bool TryGetNumber(const FJsonPath& Path, T& OutValue) const;`
- L82 _public prototype_ `bool TryGetBool(const FJsonPath& Path, bool& OutValue) const;`
- L83 _public prototype_ `bool TryGetString(const FJsonPath& Path, FString& OutValue) const;`
- L84 _public prototype_ `bool TryGetString(const FJsonPath& Path, FName& OutValue) const;`
- L85 _public prototype_ `bool TryGetString(const FJsonPath& Path, FText& OutValue) const;`
- L86 _public prototype_ `bool TryGetJsonValue(const FJsonPath& Path, TSharedPtr<FJsonValue>& OutValue) const;`
- L87 _public prototype_ `bool TryGetJsonObject(const FJsonPath& Path, TSharedPtr<FJsonObject>& OutValue) const;`
- L88 _public prototype_ `bool TryGetArray(const FJsonPath& Path, TArray<TSharedPtr<FJsonValue>>& OutArray) const;`
- L90 _public prototype_ `TSharedPtr<FJsonObject> GetRootObject() const;`
- L95 _public prototype_ `bool TryGetArray(const FJsonPath& Path, TArray<bool>& OutArray) const;` — these are specializations for arithmetic and string arrays these could be templated with enable-ifs, but it ended up being more lines of incomprehensible template SFINAE than this clear list of types is
- L96 _public prototype_ `bool TryGetArray(const FJsonPath& Path, TArray<int8>& OutArray) const;`
- L97 _public prototype_ `bool TryGetArray(const FJsonPath& Path, TArray<int16>& OutArray) const;`
- L98 _public prototype_ `bool TryGetArray(const FJsonPath& Path, TArray<int32>& OutArray) const;`
- L99 _public prototype_ `bool TryGetArray(const FJsonPath& Path, TArray<int64>& OutArray) const;`
- L100 _public prototype_ `bool TryGetArray(const FJsonPath& Path, TArray<uint8>& OutArray) const;`
- L101 _public prototype_ `bool TryGetArray(const FJsonPath& Path, TArray<uint16>& OutArray) const;`
- L102 _public prototype_ `bool TryGetArray(const FJsonPath& Path, TArray<uint32>& OutArray) const;`
- L103 _public prototype_ `bool TryGetArray(const FJsonPath& Path, TArray<uint64>& OutArray) const;`
- L104 _public prototype_ `bool TryGetArray(const FJsonPath& Path, TArray<float>& OutArray) const;`
- L105 _public prototype_ `bool TryGetArray(const FJsonPath& Path, TArray<double>& OutArray) const;`
- L106 _public prototype_ `bool TryGetArray(const FJsonPath& Path, TArray<FString>& OutArray) const;`
- L107 _public prototype_ `bool TryGetArray(const FJsonPath& Path, TArray<FText>& OutArray) const;`
- L108 _public prototype_ `bool TryGetArray(const FJsonPath& Path, TArray<FName>& OutArray) const;`
- L110 _public prototype_ `bool TryGetMap(const FJsonPath& Path, TArray<FJsonValuePair>& OutMap) const;`
- L116 _public prototype_ `template <typename T> bool SetNumber(const FJsonPath& Path, T Value);` — try to set a number - returns false if: - the path references an object that doesn't exist - the path references an index in an array that doesn't exist
- L117 _public prototype_ `bool SetBool(const FJsonPath& Path, bool Value);`
- L118 _public prototype_ `bool SetString(const FJsonPath& Path, FStringView Value);`
- L119 _public prototype_ `bool SetString(const FJsonPath& Path, const FText& Value);`
- L120 _public prototype_ `bool SetJsonValue(const FJsonPath& Path, const TSharedPtr<FJsonValue>& Value);`
- L121 _public prototype_ `bool SetJsonObject(const FJsonPath& Path, const TSharedPtr<FJsonObject>& Object);`
- L122 _public prototype_ `bool SetJsonArray(const FJsonPath& Path, const TArray<TSharedPtr<FJsonValue>>& Array);`
- L124 _public prototype_ `bool SetRootObject(const TSharedPtr<FJsonObject>& Object);`
- L126 _public prototype_ `bool HasOverride(const FJsonPath& Path) const;`
- L131 _private prototype_ `template <typename T, typename TGetter> bool TryGetArrayHelper(const FJsonPath& Path, TArray<T>& OutArray, TGetter Getter) const;`
- L134 _private prototype_ `template <typename T> bool TryGetNumericArrayHelper(const FJsonPath& Path, TArray<T>& OutArray) const;`
- L136 _private prototype_ `bool SetJsonValueInMerged(const FJsonPath& Path, const TSharedPtr<FJsonValue>& Value);`
- L137 _private prototype_ `bool SetJsonValueInOverride(const FJsonPath& Path, const TSharedPtr<FJsonValue>& NewValue, const TSharedPtr<FJsonValue>& PreviousValue, const TSharedPtr<FJsonValue>& ParentValue);`
- L138 _private prototype_ `bool SetArrayValueInOverride(const TSharedPtr<FJsonValue>& CurrentValue, const TArray<TSharedPtr<FJsonValue>>& NewArray, const TSharedPtr<FJsonValue>& ParentValue);`
- L139 _private prototype_ `bool SetObjectValueInOverride(const TSharedPtr<FJsonObject>& CurrentObject, const TSharedPtr<FJsonObject>& NewObject, const TSharedPtr<FJsonValue>& ParentValue);`
- L141 _private prototype_ `bool RemoveJsonValueFromOverride(const FJsonPath& Path, const TSharedPtr<FJsonValue>& PreviousValue);`
- L143 _private prototype_ `bool MergeThisWithParent();`
- L144 _private prototype_ `void OnParentConfigChanged();`
- L148 _private member_ `TFuture<void> SaveFuture;`
- L150 _private member_ `FSimpleDelegate OnConfigChanged;`
- L152 _private member_ `TSharedPtr<FJsonConfig> ParentConfig;`
- L154 _private member_ `TSharedPtr<FJsonObject> OverrideObject;`
- L155 _private member_ `TSharedPtr<FJsonObject> MergedObject;`

#### Free symbols / members of external scopes

- L24 _namespace_ `namespace UE`
- L61 _typedef_ `using FJsonValuePair = TPair<TSharedPtr<FJsonValue>, TSharedPtr<FJsonValue>>;` (scope `UE`)

### `Source/Editor/EditorConfig/Public/JsonConfig.inl` (Public)


#### Free symbols / members of external scopes

- L5 _namespace_ `namespace UE`
- L8 _function_ `template <typename T> bool FJsonConfig::TryGetNumber(const FJsonPath& Path, T& OutValue) const` (scope `UE::FJsonConfig`)
- L20 _function_ `template <typename T, typename TGetter> bool FJsonConfig::TryGetArrayHelper(const FJsonPath& Path, TArray<T>& OutArray, TGetter Getter) const` (scope `UE::FJsonConfig`)
- L51 _function_ `template <typename T> bool FJsonConfig::TryGetNumericArrayHelper(const FJsonPath& Path, TArray<T>& OutArray) const` (scope `UE::FJsonConfig`)
- L55 _function_ `` (scope `UE::FJsonConfig::TryGetNumericArrayHelper`)
- L61 _function_ `template <typename T> bool FJsonConfig::SetNumber(const FJsonPath& Path, T Value)` (scope `UE::FJsonConfig`)
