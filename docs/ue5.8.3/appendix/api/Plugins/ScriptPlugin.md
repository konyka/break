# Plugins / ScriptPlugin

- module root: `Plugins/ScriptPlugin/Source/ScriptPlugin`
- headers: 10; symbols: 142
- symbol kinds: class=10, delegate=1, function=9, macro=1, member=23, prototype=90, struct=8
- PublicDependencyModuleNames: Core, CoreUObject, EditorFramework, Engine, InputCore, SlateCore, UnrealEd

### `Plugins/ScriptPlugin/Source/ScriptPlugin/Classes/ScriptBlueprint.h` (Public)


#### class `UScriptBlueprint`  
`class UScriptBlueprint : public UBlueprint`  
_L13-61_
- reflection: `UCLASS(BlueprintType, EarlyAccessPreview)`
- inherits: `UBlueprint`
- desc: The Script blueprint generates script-defined classes
- L20 _public member_ `FString SourceFilePath_DEPRECATED;` — `UPROPERTY()`
- L23 _public member_ `TObjectPtr<class UAssetImportData> AssetImportData;` — `UPROPERTY()`
- L30 _public member_ `TArray<uint8> ByteCode;` — `UPROPERTY()` — Generated script bytecode
- L34 _public member_ `FString SourceCode;` — `UPROPERTY()` — Script source code. @todo: this should be editor-only
- L38 _public prototype_ `virtual void GetAssetRegistryTags(FAssetRegistryTagsContext Context) const override;` — Override to ensure we write out the asset import data
- L39 _public prototype_ `virtual void PostLoad() override;`
- L43 _public prototype_ `virtual UClass* GetBlueprintClass() const override;`
- L45 _public function_ `virtual bool SupportedByDefaultBlueprintFactory() const override`
- L51 _public prototype_ `static bool ValidateGeneratedClass(const UClass* InClass);`
- L53 _public prototype_ `bool IsCodeDirty() const;`
- L54 _public prototype_ `void UpdateScriptStatus();`
- L59 _public prototype_ `void UpdateSourceCodeIfChanged();` — Checks if the source code changed and updates it if so (does not recompile the class)

### `Plugins/ScriptPlugin/Source/ScriptPlugin/Classes/ScriptBlueprintGeneratedClass.h` (Public)


#### struct `FScriptField`  
`struct FScriptField`  
_L15-41_
- desc: Script-defined field (variable or function)
- L18 _public member_ `FName Name;` — Field name
- L20 _public member_ `UClass* Class;` — Field type
- L22 _public member_ `FFieldClass* PropertyClass;` — Property type
- L24 _public function_ `FScriptField() : Class(nullptr) , PropertyClass(nullptr)`
- L29 _public function_ `FScriptField(FName InName, UClass* InClass) : Name(InName) , Class(InClass) , PropertyClass(nullptr)`
- L35 _public function_ `FScriptField(FName InName, FFieldClass* InPropertyClass) : Name(InName) , Class(nullptr) , PropertyClass(InPropertyClass)`

#### class `FScriptContextBase`  
`class FScriptContextBase`  
_L44-129_
- desc: Script context for this component
- L48 _public function_ `virtual ~FScriptContextBase()`
- L53 _public prototype_ `static FScriptContextBase* CreateContext(const FString& SourceCode, UScriptBlueprintGeneratedClass* Class, UObject* Owner);` — Creates a script context object
- L58 _public prototype_ `static void GetSupportedScriptFileFormats(TArray<FString>& OutFormats);` — Gets supported script file formats (UFactory formats)
- L65 _public prototype_ `virtual bool Initialize(const FString& Code, UObject* Owner) = 0;` — Initializes script context given script code @param Code Script code @param Owner Owner of this context
- L70 _public prototype_ `virtual void BeginPlay() = 0;` — Sends BeginPlay event to the script
- L75 _public prototype_ `virtual void Tick(float DeltaTime) = 0;` — Sends Tick event to the script
- L80 _public prototype_ `virtual void Destroy() = 0;` — Sends Destroy event to the script and destroys the script.
- L85 _public prototype_ `virtual bool CanTick() = 0;` — @return true if script defines Tick function
- L91 _public prototype_ `virtual bool CallFunction(const FString& FunctionName) = 0;` — Calls arbitrary script function (no arguments) given its name. @param FunctionName Name of the function to call
- L95 _public prototype_ `virtual bool SetFloatProperty(const FString& PropertyName, float NewValue) = 0;`
- L96 _public prototype_ `virtual float GetFloatProperty(const FString& PropertyName) = 0;`
- L97 _public prototype_ `virtual bool SetIntProperty(const FString& PropertyName, int32 NewValue) = 0;`
- L98 _public prototype_ `virtual int32 GetIntProperty(const FString& PropertyName) = 0;`
- L99 _public prototype_ `virtual bool SetObjectProperty(const FString& PropertyName, UObject* NewValue) = 0;`
- L100 _public prototype_ `virtual UObject* GetObjectProperty(const FString& PropertyName) = 0;`
- L101 _public prototype_ `virtual bool SetBoolProperty(const FString& PropertyName, bool NewValue) = 0;`
- L102 _public prototype_ `virtual bool GetBoolProperty(const FString& PropertyName) = 0;`
- L103 _public prototype_ `virtual bool SetStringProperty(const FString& PropertyName, const FString& NewValue) = 0;`
- L104 _public prototype_ `virtual FString GetStringProperty(const FString& PropertyName) = 0;`
- L109 _public prototype_ `virtual void InvokeScriptFunction(FFrame& Stack, RESULT_DECL) = 0;` — Invokes script function from Blueprint code
- L115 _public prototype_ `virtual void GetScriptDefinedFields(TArray<FScriptField>& OutFields) = 0;` — Returns a list of exported fields from script (member variables and functions).
- L123 _public prototype_ `virtual void PushScriptPropertyValues(UScriptBlueprintGeneratedClass* Class, const UObject* Obj);` — Pushes all property values from class instance to script.
- L128 _public prototype_ `virtual void FetchScriptPropertyValues(UScriptBlueprintGeneratedClass* Class, UObject* Obj);` — Fetches all property values from script to class instance.

#### class `UScriptBlueprintGeneratedClass`  
`class UScriptBlueprintGeneratedClass : public UBlueprintGeneratedClass`  
_L135-184_
- reflection: `UCLASS(EarlyAccessPreview)`
- inherits: `UBlueprintGeneratedClass`
- desc: Script generated class
- L143 _public member_ `TArray<uint8> ByteCode;` — `UPROPERTY()` — Generated script bytecode
- L147 _public member_ `FString SourceCode;` — `UPROPERTY()` — Script source code. @todo: this should be editor-only
- L151 _public member_ `TArray<TObjectPtr<UProperty>> ScriptProperties_DEPRECATED;` — `UPROPERTY()` — Script-generated properties
- L152 _public member_ `TArray<TFieldPath<FProperty>> ScriptProperties;`
- L154 _public prototype_ `virtual void PurgeClass(bool bRecompilingOnLoad) override;`
- L161 _public prototype_ `void AddUniqueNativeFunction(const FName& InName, FNativeFuncPtr InPointer);` — Adds a unique native function mapping @param InName Name of the native function @param InPointer Pointer to the native member function
- L167 _public prototype_ `void RemoveNativeFunction(const FName& InName);` — Removes native function mapping @param InName Name of the native function
- L173 _public function_ `inline static UScriptBlueprintGeneratedClass* GetScriptGeneratedClass(UClass* InClass)` — Gets UScriptBlueprintGeneratedClass from class hierarchy @return UScriptBlueprintGeneratedClass or NULL
- L183 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`

### `Plugins/ScriptPlugin/Source/ScriptPlugin/Classes/ScriptContext.h` (Public)


#### class `UScriptContext`  
`class UScriptContext : public UObject`  
_L15-29_
- reflection: `UCLASS(DefaultToInstanced, EarlyAccessPreview)`
- inherits: `UObject`
- desc: Script context subobject
- L19 _private prototype_ `virtual void PostInitProperties() override;`
- L20 _private prototype_ `virtual void BeginDestroy() override;`
- L23 _private prototype_ `void CallScriptFunction(FString FunctionName);` — `UFUNCTION(BlueprintCallable, Category="ScriptContext")`
- L28 _protected member_ `FScriptContextBase* Context;` — Script context (code)

### `Plugins/ScriptPlugin/Source/ScriptPlugin/Classes/ScriptContextComponent.h` (Public)


#### class `UScriptContextComponent`  
`class UScriptContextComponent : public UActorComponent`  
_L14-38_
- reflection: `UCLASS(EarlyAccessPreview)`
- inherits: `UActorComponent`
- desc: Script-extendable component class
- L21 _public prototype_ `virtual void OnRegister() override;`
- L22 _public prototype_ `virtual void InitializeComponent() override;`
- L23 _public prototype_ `virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;`
- L24 _public prototype_ `virtual void BeginDestroy() override;`
- L32 _public prototype_ `void CallScriptFunction(FString FunctionName);` — `UFUNCTION(BlueprintCallable, Category = "ScriptContext")` — Calls a script-defined function (no arguments) @param FunctionName Name of the function to call
- L37 _protected member_ `FScriptContextBase* Context;` — Script context (code)

### `Plugins/ScriptPlugin/Source/ScriptPlugin/Classes/ScriptPluginComponent.h` (Public)


#### class `UScriptPluginComponent`  
`class UScriptPluginComponent : public UActorComponent`  
_L15-39_
- reflection: `UCLASS(Blueprintable, hidecategories = (Object, ActorComponent), editinlinenew, meta = (BlueprintSpawnableComponent), ClassGroup = Script, Abstract, EarlyAccessPreview)`
- inherits: `UActorComponent`
- desc: Script-extendable component class
- L26 _public prototype_ `virtual bool CallScriptFunction(FString FunctionName);` — `UFUNCTION(BlueprintCallable, Category = "Script|Functions")` — Calls a script-defined function (no arguments) @param FunctionName Name of the function to call
- L29 _public prototype_ `virtual void OnRegister() override;`
- L30 _public prototype_ `virtual void InitializeComponent() override;`
- L31 _public prototype_ `virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;`
- L32 _public prototype_ `virtual void OnUnregister() override;`
- L38 _protected member_ `FScriptContextBase* Context;` — Script context (code)

### `Plugins/ScriptPlugin/Source/ScriptPlugin/Classes/ScriptTestActor.h` (Public)


#### class `AScriptTestActor`  
`class AScriptTestActor : public AActor`  
_L11-26_
- reflection: `UCLASS(BlueprintType, MinimalAPI, EarlyAccessPreview, notplaceable)`
- inherits: `AActor`
- desc: Test Actor. To be removed at some point.
- L16 _private member_ `FString TestString;` — `UPROPERTY(Category = Test, EditAnywhere, BlueprintReadWrite)`
- L19 _private member_ `float TestValue;` — `UPROPERTY(Category = Test, EditAnywhere, BlueprintReadWrite)`
- L22 _private member_ `bool TestBool;` — `UPROPERTY(Category = Test, EditAnywhere, BlueprintReadWrite)`
- L25 _private prototype_ `float TestFunction(float InValue, float InFactor, bool bMultiply);` — `UFUNCTION()`

### `Plugins/ScriptPlugin/Source/ScriptPlugin/Private/LuaIntegration.h` (Private)


#### class `FLuaContext`  
`class FLuaContext : public FScriptContextBase`  
_L14-52_
- inherits: `FScriptContextBase`
- L16 _private member_ `bool bHasTick;`
- L17 _private member_ `bool bHasDestroy;`
- L18 _private member_ `bool bHasBeginPlay;`
- L19 _private member_ `lua_State* LuaState;`
- L21 _private prototype_ `void CloseLua();`
- L25 _public prototype_ `FLuaContext();`
- L26 _public prototype_ `virtual ~FLuaContext();`
- L29 _public prototype_ `virtual bool Initialize(const FString& Code, UObject* Owner) override;` — FScriptContextBase interface
- L30 _public prototype_ `virtual void BeginPlay() override;`
- L31 _public prototype_ `virtual void Tick(float DeltaTime) override;`
- L32 _public prototype_ `virtual void Destroy() override;`
- L33 _public prototype_ `virtual bool CanTick() override;`
- L35 _public prototype_ `virtual bool SetFloatProperty(const FString& PropertyName, float NewValue) override;`
- L36 _public prototype_ `virtual float GetFloatProperty(const FString& PropertyName) override;`
- L37 _public prototype_ `virtual bool SetIntProperty(const FString& PropertyName, int32 NewValue) override;`
- L38 _public prototype_ `virtual int32 GetIntProperty(const FString& PropertyName) override;`
- L39 _public prototype_ `virtual bool SetObjectProperty(const FString& PropertyName, UObject* NewValue) override;`
- L40 _public prototype_ `virtual UObject* GetObjectProperty(const FString& PropertyName) override;`
- L41 _public prototype_ `virtual bool SetBoolProperty(const FString& PropertyName, bool NewValue) override;`
- L42 _public prototype_ `virtual bool GetBoolProperty(const FString& PropertyName) override;`
- L43 _public prototype_ `virtual bool SetStringProperty(const FString& PropertyName, const FString& NewValue) override;`
- L44 _public prototype_ `virtual FString GetStringProperty(const FString& PropertyName) override;`
- L46 _public prototype_ `virtual bool CallFunction(const FString& FunctionName) override;`
- L47 _public prototype_ `virtual void InvokeScriptFunction(FFrame& Stack, RESULT_DECL) override;`
- L50 _public prototype_ `virtual void GetScriptDefinedFields(TArray<FScriptField>& OutFields) override;`

#### struct `FLuaUtils`  
`struct FLuaUtils`  
_L54-59_
- L56 _public prototype_ `static void RegisterLibrary(lua_State* LuaState, const luaL_Reg Lib[], const ANSICHAR* LibName);`
- L57 _public prototype_ `static bool CallFunction(lua_State* LuaState, const ANSICHAR* FunctionName);`
- L58 _public prototype_ `static bool DoesFunctionExist(lua_State* LuaState, const char* FunctionName);`

#### struct `FLuaVector2D`  
`struct FLuaVector2D`  
_L61-65_
- L63 _public prototype_ `static FVector2D Get(lua_State *LuaState, int ParamIndex);`
- L64 _public prototype_ `static void Return(lua_State *LuaState, const FVector2D& Vec);`

#### struct `FLuaVector`  
`struct FLuaVector`  
_L67-71_
- L69 _public prototype_ `static FVector Get(lua_State *LuaState, int ParamIndex);`
- L70 _public prototype_ `static void Return(lua_State *LuaState, const FVector& Vec);`

#### struct `FLuaVector4`  
`struct FLuaVector4`  
_L73-77_
- L75 _public prototype_ `static FVector4 Get(lua_State *LuaState, int ParamIndex);`
- L76 _public prototype_ `static void Return(lua_State *LuaState, const FVector4& Vec);`

#### struct `FLuaQuat`  
`struct FLuaQuat`  
_L79-83_
- L81 _public prototype_ `static FQuat Get(lua_State *LuaState, int ParamIndex);`
- L82 _public prototype_ `static void Return(lua_State *LuaState, const FQuat& Vec);`

#### struct `FLuaLinearColor`  
`struct FLuaLinearColor`  
_L85-89_
- L87 _public prototype_ `static FLinearColor Get(lua_State *LuaState, int ParamIndex);`
- L88 _public prototype_ `static void Return(lua_State *LuaState, const FLinearColor& Vec);`

#### struct `FLuaTransform`  
`struct FLuaTransform`  
_L91-95_
- L93 _public prototype_ `static FTransform Get(lua_State *LuaState, int ParamIndex);`
- L94 _public prototype_ `static void Return(lua_State *LuaState, const FTransform& Transform);`

#### Free symbols / members of external scopes

- L8 _macro_ `#define LUA_COMPAT_APIINTCASTS 1`

### `Plugins/ScriptPlugin/Source/ScriptPlugin/Private/ScriptObjectReferencer.h` (Private)


#### class `FScriptObjectReferencer`  
`class FScriptObjectReferencer : FGCObject`  
_L7-46_
- inherits: `FGCObject`
- L10 _private member_ `static FScriptObjectReferencer* Singleton;` — Singleton for easy access
- L13 _private member_ `TArray<TObjectPtr<UObject>> ScriptCreatedObjects;` — List of all objects currently existing in one of the script contexts
- L18 _public prototype_ `static void Init();` — Initializes the singleton instance
- L21 _public prototype_ `static void Shutdown();` — Destroys the singleton
- L24 _public prototype_ `static FScriptObjectReferencer& Get();` — Access to the singleton instance
- L31 _public prototype_ `void AddObjectReference(UObject* Object);` — Adds a new object reference @param Object Object reference
- L38 _public prototype_ `void RemoveObjectReference(UObject* Object);` — Removes an existing object reference @param Object Object reference
- L41 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;` — FGCObject Interface
- L42 _public function_ `virtual FString GetReferencerName() const override`

### `Plugins/ScriptPlugin/Source/ScriptPlugin/Private/ScriptPluginLog.h` (Private)


#### Free symbols / members of external scopes

- L6 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogScriptPlugin, Log, All);`
- L6 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogScriptPlugin, Log, All);`

### `Plugins/ScriptPlugin/Source/ScriptPlugin/Public/IScriptPlugin.h` (Public)


#### class `IScriptPlugin`  
`class IScriptPlugin : public IModuleInterface`  
_L11-36_
- inherits: `IModuleInterface`
- desc: The public interface to this module.  In most cases, this interface is only public to sibling modules within this plugin.
- L22 _public function_ `static inline IScriptPlugin& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L32 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use
