# Plugins / ConcertReplicationScripting

- module root: `Plugins/Developer/Concert/ConcertScripting/ConcertReplicationScripting/Source/ConcertReplicationScripting`
- headers: 4; symbols: 27
- symbol kinds: class=2, delegate=1, function=3, member=2, namespace=2, prototype=15, struct=2
- PrivateDependencyModuleNames: ConcertTransport
- PublicDependencyModuleNames: ConcertSyncCore, Core, CoreUObject, Engine

### `Plugins/Developer/Concert/ConcertScripting/ConcertReplicationScripting/Source/ConcertReplicationScripting/Private/ConcertReplicationScriptingModule.h` (Private)


#### class `UE::ConcertReplicationScripting::FConcertReplicationScriptingModule`  
`class FConcertReplicationScriptingModule : public IModuleInterface`  
_L9-17_
- inherits: `IModuleInterface`
- L14 _public prototype_ `virtual void StartupModule() override;`
- L15 _public prototype_ `virtual void ShutdownModule() override;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace ConcertReplicationScripting` (scope `UE`)

### `Plugins/Developer/Concert/ConcertScripting/ConcertReplicationScripting/Source/ConcertReplicationScripting/Public/ConcertPropertyChainWrapper.h` (Public)


#### struct `FConcertPropertyChainWrapper`  
`struct FConcertPropertyChainWrapper`  
_L9-23_
- reflection: `USTRUCT(BlueprintType, meta = (DisplayName = "Concert Property Chain"))`
- L14 _public member_ `FConcertPropertyChain PropertyChain;` — `UPROPERTY()`
- L16 _public prototype_ `FConcertPropertyChainWrapper() = default;`
- L17 _public function_ `explicit FConcertPropertyChainWrapper(FConcertPropertyChain InPropertyChain) : PropertyChain(MoveTemp(InPropertyChain))`

#### Free symbols / members of external scopes

- L21 _function_ `friend bool operator==(const FConcertPropertyChainWrapper& Left, const FConcertPropertyChainWrapper& Right)`
- L22 _function_ `friend bool operator!=(const FConcertPropertyChainWrapper& Left, const FConcertPropertyChainWrapper& Right)`
- L25 _prototype_ `uint32 GetTypeHash(const FConcertPropertyChainWrapper& ChainWrapper);`

### `Plugins/Developer/Concert/ConcertScripting/ConcertReplicationScripting/Source/ConcertReplicationScripting/Public/ConcertPropertyChainWrapperContainer.h` (Public)


#### struct `FConcertPropertyChainWrapperContainer`  
`struct FConcertPropertyChainWrapperContainer`  
_L11-17_
- reflection: `USTRUCT(BlueprintType, meta = (DisplayName = "Concert Property Chain Container"))`
- desc: Special array of property chains. Used to allow for detail customization.
- L16 _public member_ `TArray<FConcertPropertyChainWrapper> PropertyChains;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Concert|Replication")`

### `Plugins/Developer/Concert/ConcertScripting/ConcertReplicationScripting/Source/ConcertReplicationScripting/Public/ConcertReplicationBlueprintFunctionLibrary.h` (Public)


#### class `UConcertReplicationBlueprintFunctionLibrary`  
`class UConcertReplicationBlueprintFunctionLibrary : public UBlueprintFunctionLibrary`  
_L12-124_
- reflection: `UCLASS(BlueprintType)`
- inherits: `UBlueprintFunctionLibrary`
- L17 _public prototype_ `DECLARE_DYNAMIC_DELEGATE_RetVal_OneParam(bool, FPropertyChainPredicate, const FConcertPropertyChainWrapper&, PathToProperty);`
- L31 _public prototype_ `static bool MakePropertyChainByLiteralPath(const TSubclassOf<UObject>& Class, const TArray<FName>& PathToProperty, FConcertPropertyChainWrapper& Result);` — `UFUNCTION(BlueprintPure, Category = "Concert|Replication")` — Tries to make concert property chain by specifying a path manually. @param Class The class in which to search for the property path @param PathToProperty The path to the property @param Result The resulting path @return Whether Result is valid.
- L42 _public prototype_ `static TArray<FConcertPropertyChainWrapper> GetPropertiesIn(const TSubclassOf<UObject>& Class, FPropertyChainPredicate Filter);` — `UFUNCTION(BlueprintPure, Category = "Concert|Replication", meta = (KeyWords = "Get Properties In Find Enumerate List"))` — Builds an array of property paths that pass the given filter. @param Class The class in which to search for properties @param Filter Decides whether a property path should be included @return An array of all property paths in the given class that passed the filter
- L50 _public prototype_ `static TArray<FConcertPropertyChainWrapper> GetAllProperties(const TSubclassOf<UObject>& Class);` — `UFUNCTION(BlueprintPure, Category = "Concert|Replication")` — Gets all properties in the class that are valid for replicating. @param Class The class in which to search @return All properties in the class that are valid for replicating.
- L60 _public prototype_ `static TArray<FConcertPropertyChainWrapper> GetChildProperties(const FConcertPropertyChainWrapper& Parent, const TSubclassOf<UObject>& Class, bool bOnlyDirect = false);` — `UFUNCTION(BlueprintPure, Category = "Concert|Replication", meta = (ScriptMethod))` — Returns all child properties of Parent that are valid for replicating. @param Parent The property of which to find child properties @param Class The class in which to search @param bOnlyDirect Whether you only want direct children of Parent @return All child properties of Parent that are valid for replicating.
- L64 _public prototype_ `static FString ToString(const FConcertPropertyChainWrapper& PropertyChain);` — `UFUNCTION(BlueprintPure, Category = "Concert|Replication", meta = (ScriptMethod))` — Converts the the property to a string.
- L77 _public prototype_ `static const TArray<FName>& GetPropertyStringPath(const FConcertPropertyChainWrapper& Path);` — `UFUNCTION(BlueprintPure, Category = "Concert|Replication")` — Gets the path as string array. Example: ["RelativeLocation", "X"] @param Path The property path to extract from @return The path as string array
- L89 _public prototype_ `static FName GetPropertyFromRoot(const FConcertPropertyChainWrapper& Path, int32 Index = 0);` — `UFUNCTION(BlueprintPure, Category = "Concert|Replication")` — Gets the property at Index starting from the root most property. Example: The root Index 0 for ["RelativeLocation", "X"] would return "RelativeLocation". @param Path The property path to get the sub-property from. @param Index The index in the path counting from the left, root property. @return The property name at Index or None if Index is invalid.
- L101 _public prototype_ `static FName GetPropertyFromLeaf(const FConcertPropertyChainWrapper& Path, int32 Index = 0);` — `UFUNCTION(BlueprintPure, Category = "Concert|Replication")` — Gets the property at Index starting from the leaf most property. Example: The leaf Index 0 for ["RelativeLocation", "X"] would return "X". @param Path The property path to get the sub-property from. @param Index The index in the path counting from the right, leaf property. @return The property name at Index or None if Index is invalid.
- L112 _public prototype_ `static bool IsChildOf(const FConcertPropertyChainWrapper& ToTest, const FConcertPropertyChainWrapper& Parent);` — `UFUNCTION(BlueprintPure, Category = "Concert|Replication")` — Checks whether ToTest is a child property of Parent. @param ToTest The property for which to check whether it is a child property @param Parent The property which is supposed to be the parent of ToTest @return Whether ToTest is a child property of Parent
- L123 _public prototype_ `static bool IsDirectChildOf(const FConcertPropertyChainWrapper& ToTest, const FConcertPropertyChainWrapper& Parent);` — `UFUNCTION(BlueprintPure, Category = "Concert|Replication")` — Checks whether ToTest is a direct child property of Parent. @param ToTest The property for which to check whether it is a child property @param Parent The property which is supposed to be the parent of ToTest @return Whether ToTest is a direct child property of Parent

#### Free symbols / members of external scopes

- L17 _delegate_ `DECLARE_DYNAMIC_DELEGATE_RetVal_OneParam(bool, FPropertyChainPredicate, const FConcertPropertyChainWrapper&, PathToProperty);`
