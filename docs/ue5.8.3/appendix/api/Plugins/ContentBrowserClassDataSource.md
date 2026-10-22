# Plugins / ContentBrowserClassDataSource

- module root: `Plugins/Editor/ContentBrowser/ContentBrowserClassDataSource/Source/ContentBrowserClassDataSource`
- headers: 5; symbols: 186
- symbol kinds: class=5, delegate=2, enum=1, enumerator=2, function=20, macro=2, member=33, namespace=1, prototype=114, struct=6
- PrivateDependencyModuleNames: AssetTools, CollectionManager, GameProjectGeneration, Projects, Slate, SlateCore, ToolMenus, UnrealEd
- PublicDependencyModuleNames: ContentBrowserData, Core, CoreUObject

### `Plugins/Editor/ContentBrowser/ContentBrowserClassDataSource/Source/ContentBrowserClassDataSource/Private/NativeClassHierarchy.h` (Private)


#### enum `ENativeClassHierarchyNodeType`  
`enum class ENativeClassHierarchyNodeType : uint8`  
_L13-17_
- desc: Type of hierarchy node
- L15 _public enumerator_ `Folder`
- L16 _public enumerator_ `Class`

#### struct `FNativeClassHierarchyGetClassPathCache`  
`struct FNativeClassHierarchyGetClassPathCache`  
_L22-30_
- desc: Cache to avoid regenerating some necessary data during repeated calls to GetClassPathRootForModule during enumerate
- L24 _public member_ `TSet<FName> GameModules;`
- L26 _public function_ `void Reset()`

#### struct `FNativeClassHierarchyNodeKey`  
`struct FNativeClassHierarchyNodeKey`  
_L35-66_
- desc: Type used as a key in a map to resolve name conflicts between folders and classes
- L37 _public function_ `FNativeClassHierarchyNodeKey(const FName InName, const ENativeClassHierarchyNodeType InType) : Name(InName) , Type(InType)`
- L43 _public function_ `FORCEINLINE bool operator==(const FNativeClassHierarchyNodeKey& Other) const`
- L48 _public function_ `FORCEINLINE bool operator!=(const FNativeClassHierarchyNodeKey& Other) const`
- L62 _public member_ `FName Name;` — Name of this entry
- L65 _public member_ `ENativeClassHierarchyNodeType Type;` — Type of this entry

#### struct `FNativeClassHierarchyNode`  
`struct FNativeClassHierarchyNode`  
_L71-104_
- desc: Single node in the class hierarchy
- L74 _public prototype_ `static TSharedRef<FNativeClassHierarchyNode> MakeFolderEntry(FName InEntryName, FString InEntryPath, TOptional<EPluginLoadedFrom> LoadedFrom);` — Helper function to make a folder node entry
- L77 _public prototype_ `static TSharedRef<FNativeClassHierarchyNode> MakeClassEntry(UClass* InClass, FName InClassModuleName, FString InClassModuleRelativePath, FString InEntryPath, TOptional<EPluginLoadedFrom> LoadedFrom);` — Helper function to make a class node entry
- L79 _public prototype_ `void AddChild(TSharedRef<FNativeClassHierarchyNode> ChildEntry);`
- L82 _public member_ `ENativeClassHierarchyNodeType Type;` — Type of node, folder or class
- L85 _public member_ `UClass* Class;` — The class this node is for (Type == Class)
- L88 _public member_ `FName ClassModuleName;` — The name of the module the class is in (Type == Class)
- L91 _public member_ `FString ClassModuleRelativePath;` — Folder this class is in, relative to the class module (Type == Class)
- L94 _public member_ `FName EntryName;` — Name used when showing this entry in the UI
- L97 _public member_ `FString EntryPath;` — Path to this entry in the class hierarchy (not the same as the location on disk)
- L100 _public member_ `TMap<FNativeClassHierarchyNodeKey, TSharedPtr<FNativeClassHierarchyNode>> Children;` — Child entries (Type == Folder)
- L103 _public member_ `TOptional<EPluginLoadedFrom> LoadedFrom;` — Which type of plugin this data was originally loaded from (if loaded from a plugin)

#### struct `FNativeClassHierarchyFilter`  
`struct FNativeClassHierarchyFilter`  
_L110-145_
- desc: A filter used when querying the native class hierarchy. Each component element is processed as an 'OR' operation while all the components are processed together as an 'AND' operation.
- L113 _public member_ `TArray<FName> ClassPaths;` — The filter component for class paths
- L115 _public member_ `bool bRecursivePaths;` — If true, ClassPaths components will be recursive
- L117 _public function_ `FNativeClassHierarchyFilter()`
- L123 _public function_ `void Append(const FNativeClassHierarchyFilter& Other)` — Appends the other filter to this one
- L131 _public function_ `bool IsEmpty() const` — Returns true if this filter has no entries
- L137 _public function_ `void Clear()` — Clears this filter of all entries

#### class `FNativeClassHierarchy`  
`class FNativeClassHierarchy`  
_L151-446_
- desc: Generates a hierarchical tree of native UObject classes based on their location in the file system as used by the asset view when showing C++ classes This keeps its class hierarchy up-to-date as modules are loaded/unloaded
- L155 _public prototype_ `FNativeClassHierarchy();` — Constructor and destructor
- L156 _public prototype_ `~FNativeClassHierarchy();`
- L159 _public function_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnNodesChanged, const TArrayView<TSharedRef<const FNativeClassHierarchyNode>>) FOnNodesChanged& OnFoldersAdded()`
- L168 _public function_ `FOnNodesChanged& OnClassesAdded()` — Get the delegate called when classes are added to this class hierarchy
- L174 _public function_ `FOnNodesChanged& OnFoldersRemoved()` — Get the delegate called when folders are removed to this class hierarchy
- L180 _public function_ `FOnNodesChanged& OnClassesRemoved()` — Get the delegate called when classes are removed to this class hierarchy
- L191 _public prototype_ `TSharedPtr<const FNativeClassHierarchyNode> FindNode(const FName InClassPath, const ENativeClassHierarchyNodeType InType) const;` — Find the node for the given path, if any. @param InClassPath - The path to get the node of @param InType - The type of node to find
- L199 _public prototype_ `bool HasClasses(const FName InClassPath, const bool bRecursive = false) const;` — Does the given path contain classes, optionally also testing sub-paths? @param InClassPath - The path to query classes in @param bRecursive - If true, the supplied path will be tested recursively
- L207 _public prototype_ `bool HasFolders(const FName InClassPath, const bool bRecursive = false) const;` — Does the given path contain folders, optionally also testing sub-paths? @param InClassPath - The path to query classes in @param bRecursive - If true, the supplied path will be tested recursively
- L215 _public prototype_ `void GetMatchingClasses(const FNativeClassHierarchyFilter& Filter, TArray<UClass*>& OutClasses) const;` — Work out which classes known to the class hierarchy match the given filter @param Filter - The filter to apply when working out which classes match @param OutClasses - Array to be populated with matching classes
- L223 _public prototype_ `void GetMatchingFolders(const FNativeClassHierarchyFilter& Filter, TArray<FString>& OutFolders) const;` — Work out which folders known to the class hierarchy match the given filter @param Filter - The filter to apply when working out which folders match @param OutFolders - Array to be populated with matching folder paths (these are in the form "/Classes_Name/ModuleName/SubFolder")
- L232 _public prototype_ `void GetClassRoots(TArray<FName>& OutClassRoots, const bool bIncludeEngineClasses = true, const bool bIncludePluginClasses = true) const;` — Get all root folders known to the class hierarchy @param OutClassRoots - Array to be populated with the known class path root folders (these are in the form "/Classes_Name") @param bIncludeEngineClasses - Whether we should include the "/Classes_Engine" root (and its associated folders) in the returned results @param bIncludePluginClasses - Whether we should include plugin class path roots (and their associated folders) in the returned results (these are all roots except for "/Classes_Game" and "/Classes_Engine")
- L242 _public prototype_ `void GetClassFolders(TArray<FName>& OutClassRoots, TArray<FString>& OutClassFolders, const bool bIncludeEngineClasses = true, const bool bIncludePluginClasses = true) const;` — Get all folders known to the class hierarchy @param OutClassRoots - Array to be populated with the known class path root folders (these are in the form "/Classes_Name") @param OutClassFolders - Array to be populated with known class folder paths (these are in the form "/Classes_Name/ModuleName/SubFolder") @param bIncludeEngineClasses - Whether we should include the "/Classes_Engine" root (and its associated folders) in the returned results @param bIncludePluginClasses - Whether we should include plugin class path roots (and their associated folders) in the returned results (these are all roots except for "/Classes_Game" and "/Classes_Engine")
- L253 _public prototype_ `bool GetFileSystemPath(const FString& InClassPath, FString& OutFileSystemPath) const;` — Given a class path, work out the corresponding filesystem path on disk eg) Given "/Classes_Game/MyGame/MyAwesomeCode", we might resolve that to "../../../MyGame/Source/MyGame/MyAwesomeCode" @param InClassPath - The class path to try and resolve, eg) "/Classes_Game/MyGame/MyAwesomeCode" @param OutFileSystemPath - The string to fill with the resolved filesystem path, eg) "../../../MyGame/Source/MyGame/MyAwesomeCode" @return true if the file system path could be resolved and OutFileSystemPath was filled in, false otherwise
- L264 _public prototype_ `bool GetClassPath(const UClass* InClass, FString& OutClassPath, TSet<FName>& InGameModuleCache, const bool bIncludeClassName = true) const;` — Work out the class path that should be used for the given class @param InClass - The class path to try and get the class path for @param OutClassPath - The string to fill with the resolved class path, eg) "/Classes_Game/MyGame/MyAwesomeCode/MyAwesomeClass" @param bIncludeClassName - true to include the class name on the returned class path, false to get the class path of the containing folder @return true if the class path could be resolved and OutClassPath was filled in, false otherwise
- L274 _public prototype_ `FName GetFolderPathForModule(FName InModuleName, TSet<FName>& InGameModuleCache) const;` — Work out the folder path that should be used for the given module @param InModuleName - The module we want to find the folder path for @param InGameModuleCache - The list of modules that belong to the "/Classes_Game" root @return The folder path for the module
- L279 _public prototype_ `bool RootNodePassesFilter(const FName InRootName, const TSharedPtr<const FNativeClassHierarchyNode>& InRootNode, const bool bIncludeEngineClasses, const bool bIncludePluginClasses) const;` — Test if root node passes given rules
- L284 _public prototype_ `bool RootNodePassesFilter(const FName InRootName, const bool bIncludeEngineClasses, const bool bIncludePluginClasses) const;` — Test if root node passes given rules
- L311 _private prototype_ `static bool HasClassesRecursive(const TSharedRef<FNativeClassHierarchyNode>& HierarchyNode, const bool bRecurse = true);` — Test to see whether the given node has any child classes @param HierarchyNode - The node to test the children of @param bRecurse - True to recurse into sub-folders, false to only check the given node @return True if the node has child classes, false otherwise
- L321 _private prototype_ `static bool HasFoldersRecursive(const TSharedRef<FNativeClassHierarchyNode>& HierarchyNode, const bool bRecurse = true);` — Test to see whether the given node has any child folders @param HierarchyNode - The node to test the children of @param bRecurse - True to recurse into sub-folders, false to only check the given node @return True if the node has child folders, false otherwise
- L330 _private prototype_ `static void GetClassesRecursive(const TSharedRef<FNativeClassHierarchyNode>& HierarchyNode, TArray<UClass*>& OutClasses, const bool bRecurse = true);` — Update OutClasses with any classes that are children of the given node @param HierarchyNode - The node to add the children of @param OutClasses - Array to be populated with the child classes @param bRecurse - True to recurse into sub-folders, false to only check the given node
- L339 _private prototype_ `static void GetFoldersRecursive(const TSharedRef<FNativeClassHierarchyNode>& HierarchyNode, TArray<FString>& OutFolders, const bool bRecurse = true);` — Update OutFolders with any folders that are children of the given node @param HierarchyNode - The node to add the children of @param OutFolders - Array to be populated with the child folders @param bRecurse - True to recurse into sub-folders, false to only check the given node
- L348 _private prototype_ `void GatherMatchingNodesForPaths(const TArrayView<const FName>& InClassPaths, TArray<TSharedRef<FNativeClassHierarchyNode>, TInlineAllocator<4>>& OutMatchingNodes, const ENativeClassHierarchyNodeType InType = ENativeClassHierarchyNodeType::Folder) const;` — Populate OutMatchingNodes with the nodes that correspond to the given class paths @param InClassPaths - The class paths to find the nodes for, or an empty list to get all root nodes @param OutMatchingNodes - Array to be populated the nodes that correspond to the given class paths @param InType - Type of node to search for, ie: class / folder
- L353 _private prototype_ `void PopulateHierarchy();` — Completely clear and re-populate the known class hierarchy
- L360 _private prototype_ `void AddClassesForModule(const FName& InModuleName);` — Append any classes from the given module to the known class hierarchy @param InModuleName - The name of the module to add
- L367 _private prototype_ `void RemoveClassesForModule(const FName& InModuleName);` — Remove any classes in the given module from the known class hierarchy @param InModuleName - The name of the module to remove
- L376 _private prototype_ `void AddClass(UClass* InClass, const TSet<FName>& InGameModules, FClassChanges& ClassChanges);` — Add a single class to the known class hierarchy, creating any folders as required @param InClass - The class that is to be added @param InGameModules - The list of modules that belong to the "/Classes_Game" root @param FClassChanges - Track the new classes and folders that were added.
- L385 _private prototype_ `void RemoveClass(UClass* InClass, TSet<FName>& InGameModules, FClassChanges& ClassChanges);` — Remove a single class to the known class hierarchy, removing any empty folders left @param InClass - The class that is to be removed @param InGameModules - The list of modules that belong to the "/Classes_Game" root @param FClassChanges - Track the classes and folders that were removed.
- L393 _private prototype_ `void OnModulesChanged(FName InModuleName, EModuleChangeReason InModuleChangeReason);` — Called when we're notified that a module has changed status @param InModuleName - The module that changed status @param InModuleChangeReason - Why the module changed status
- L398 _private prototype_ `void OnReloadReinstancingComplete();` — Called when we're notified that a reloaded module has reinstanced some classes.
- L403 _private prototype_ `void OnReloadClassesAdded(const TArray<UClass*>& InAddedClasses);` — Called when we're notified that a reloaded module has some new classes.
- L412 _private prototype_ `static FName GetClassModuleName(const UClass* InClass);` — Given a class, work out which module it belongs to @param InClass - The class we want to find the module for @return The name of the module that holds the class, eg) "CoreUObject"
- L423 _private prototype_ `static FName GetClassPathRootForModule(const FName& InModuleName, const TSet<FName>& InGameModules, TOptional<EPluginLoadedFrom>& OutWhereLoadedFrom);` — Given a module, work out which root path it should use as a parent @param InModuleName - The module we want to find the root path for @param InGameModules - The list of modules that belong to the "/Classes_Game" root @param WhereLoadedFrom - Determine where this class was loaded from. @return The name of the root path to use, eg "/Classes_Game"
- L428 _private prototype_ `static TSet<FName> GetGameModules();` — Calculate the list of modules that belong to the "/Classes_Game" root
- L430 _private prototype_ `void PopulateClassChanges(const TSharedPtr<FNativeClassHierarchyNode>& InNode, FClassChanges& OutClassChanges);`
- L433 _private member_ `TMap<FName, TSharedPtr<FNativeClassHierarchyNode>> RootNodes;` — Root level nodes corresponding to the root folders used by the Content Browser, eg) Classes_Engine, Classes_Game, etc
- L436 _private member_ `FOnNodesChanged FoldersAddedDelegate;` — Delegate called when the class hierarchy as added some new folders
- L439 _private member_ `FOnNodesChanged ClassesAddedDelegate;` — Delegate called when the class hierarchy as added some new classes
- L442 _private member_ `FOnNodesChanged FoldersRemovedDelegate;` — Delegate called when the class hierarchy as removed some folders
- L445 _private member_ `FOnNodesChanged ClassesRemovedDelegate;` — Delegate called when the class hierarchy as removed some classes

#### struct `FNativeClassHierarchy::FClassChanges`  
`struct FClassChanges`  
_L287-301_
- L289 _public function_ `FClassChanges()`
- L293 _public function_ `void Reset()`
- L299 _public member_ `TArray<TSharedRef<const FNativeClassHierarchyNode>> ClassesModified;`
- L300 _public member_ `TArray<TSharedRef<const FNativeClassHierarchyNode>> FoldersModified;`

#### Free symbols / members of external scopes

- L53 _function_ `friend FORCEINLINE uint32 GetTypeHash(const FNativeClassHierarchyNodeKey& InKey)`
- L159 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnNodesChanged, const TArrayView<TSharedRef<const FNativeClassHierarchyNode>>) FOnNodesChanged& OnFoldersAdded() { return FoldersAddedDelegate; } FOnNodesChanged& OnClassesAdded() { return ClassesAddedDelegate; } FOnNodesChanged& OnFoldersRemoved() { return FoldersRemovedDelegate; } FOnNodesChanged& OnClassesRemoved() { return ClassesRemovedDelegate; } TSharedPtr<const FNativeClassHierarchyNode> FindNode(const FName InClassPath, const ENativeClassHierarchyNodeType InType) const;`

### `Plugins/Editor/ContentBrowser/ContentBrowserClassDataSource/Source/ContentBrowserClassDataSource/Private/NewClassContextMenu.h` (Private)


#### class `FNewClassContextMenu`  
`class FNewClassContextMenu`  
_L9-24_
- L12 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnNewClassRequested, const FName );`
- L15 _public prototype_ `static void MakeContextMenu( UToolMenu* Menu, const TArray<FName>& InSelectedClassPaths, const FOnNewClassRequested& InOnNewClassRequested );` — Makes the context menu widget
- L23 _private prototype_ `static void ExecuteNewClass(FName InPath, FOnNewClassRequested InOnNewClassRequested);` — Create a new class at the specified path

#### Free symbols / members of external scopes

- L12 _delegate_ `DECLARE_DELEGATE_OneParam(FOnNewClassRequested, const FName );`

### `Plugins/Editor/ContentBrowser/ContentBrowserClassDataSource/Source/ContentBrowserClassDataSource/Public/ContentBrowserClassDataCore.h` (Public)


#### Free symbols / members of external scopes

- L14 _namespace_ `namespace ContentBrowserClassData`
- L17 _prototype_ `bool IsEngineClass(const FName InPath);` (scope `ContentBrowserClassData`)
- L19 _prototype_ `bool IsProjectClass(const FName InPath);` (scope `ContentBrowserClassData`)
- L21 _prototype_ `bool IsPluginClass(const FName InPath);` (scope `ContentBrowserClassData`)
- L23 _prototype_ `FContentBrowserItemData CreateClassFolderItem(UContentBrowserDataSource* InOwnerDataSource, const FName InVirtualPath, const FName InFolderPath, const bool bIsFromPlugin);` (scope `ContentBrowserClassData`)
- L25 _prototype_ `FContentBrowserItemData CreateClassFileItem(UContentBrowserDataSource* InOwnerDataSource, const FName InVirtualPath, const FName InClassPath, UClass* InClass, const bool bIsFromPlugin);` (scope `ContentBrowserClassData`)
- L27 _prototype_ `TSharedPtr<const FContentBrowserClassFolderItemDataPayload> GetClassFolderItemPayload(const UContentBrowserDataSource* InOwnerDataSource, const FContentBrowserItemData& InItem);` (scope `ContentBrowserClassData`)
- L29 _prototype_ `TSharedPtr<const FContentBrowserClassFileItemDataPayload> GetClassFileItemPayload(const UContentBrowserDataSource* InOwnerDataSource, const FContentBrowserItemData& InItem);` (scope `ContentBrowserClassData`)
- L31 _prototype_ `void EnumerateClassFolderItemPayloads(const UContentBrowserDataSource* InOwnerDataSource, TArrayView<const FContentBrowserItemData> InItems, TFunctionRef<bool(const TSharedRef<const FContentBrowserClassFolderItemDataPayload>&)> InFolderPayloadCallback);` (scope `ContentBrowserClassData`)
- L33 _prototype_ `void EnumerateClassFileItemPayloads(const UContentBrowserDataSource* InOwnerDataSource, TArrayView<const FContentBrowserItemData> InItems, TFunctionRef<bool(const TSharedRef<const FContentBrowserClassFileItemDataPayload>&)> InClassPayloadCallback);` (scope `ContentBrowserClassData`)
- L35 _prototype_ `void EnumerateClassItemPayloads(const UContentBrowserDataSource* InOwnerDataSource, TArrayView<const FContentBrowserItemData> InItems, TFunctionRef<bool(const TSharedRef<const FContentBrowserClassFolderItemDataPayload>&)> InFolderPayloadCallback, TFunctionRef<bool(const TSharedRef<const FContentBrowserClassFileItemDataPayload>&)> InClassPayloadCallback);` (scope `ContentBrowserClassData`)
- L37 _prototype_ `void SetOptionalErrorMessage(FText* OutErrorMsg, FText InErrorMsg);` (scope `ContentBrowserClassData`)
- L39 _prototype_ `bool CanEditItem(const UContentBrowserDataSource* InOwnerDataSource, const FContentBrowserItemData& InItem, FText* OutErrorMsg);` (scope `ContentBrowserClassData`)
- L41 _prototype_ `bool CanEditClassFileItem(const FContentBrowserClassFileItemDataPayload& InClassPayload, FText* OutErrorMsg);` (scope `ContentBrowserClassData`)
- L43 _prototype_ `bool EditItems(IAssetTypeActions* InClassTypeActions, const UContentBrowserDataSource* InOwnerDataSource, TArrayView<const FContentBrowserItemData> InItems);` (scope `ContentBrowserClassData`)
- L45 _prototype_ `bool EditClassFileItems(IAssetTypeActions* InClassTypeActions, TArrayView<const TSharedRef<const FContentBrowserClassFileItemDataPayload>> InClassPayloads);` (scope `ContentBrowserClassData`)
- L47 _prototype_ `bool UpdateItemThumbnail(const UContentBrowserDataSource* InOwnerDataSource, const FContentBrowserItemData& InItem, FAssetThumbnail& InThumbnail);` (scope `ContentBrowserClassData`)
- L49 _prototype_ `bool UpdateClassFileItemThumbnail(const FContentBrowserClassFileItemDataPayload& InClassPayload, FAssetThumbnail& InThumbnail);` (scope `ContentBrowserClassData`)
- L51 _prototype_ `bool AppendItemReference(const UContentBrowserDataSource* InOwnerDataSource, const FContentBrowserItemData& InItem, FString& InOutStr);` (scope `ContentBrowserClassData`)
- L53 _prototype_ `bool AppendItemObjectPath(const UContentBrowserDataSource* InOwnerDataSource, const FContentBrowserItemData& InItem, FString& InOutStr);` (scope `ContentBrowserClassData`)
- L55 _prototype_ `bool AppendItemPackageName(const UContentBrowserDataSource* InOwnerDataSource, const FContentBrowserItemData& InItem, FString& InOutStr);` (scope `ContentBrowserClassData`)
- L57 _prototype_ `bool AppendClassFileItemReference(const FContentBrowserClassFileItemDataPayload& InClassPayload, FString& InOutStr);` (scope `ContentBrowserClassData`)
- L59 _prototype_ `bool AppendObjectPathFileItemReference(const FContentBrowserClassFileItemDataPayload& InClassPayload, FString& InOutStr);` (scope `ContentBrowserClassData`)
- L61 _prototype_ `bool AppendPackageNameItemReference(const FContentBrowserClassFileItemDataPayload& InClassPayload, FString& InOutStr);` (scope `ContentBrowserClassData`)
- L63 _prototype_ `bool GetItemPhysicalPath(const UContentBrowserDataSource* InOwnerDataSource, const FContentBrowserItemData& InItem, FString& OutDiskPath);` (scope `ContentBrowserClassData`)
- L65 _prototype_ `bool GetClassFolderItemPhysicalPath(const FContentBrowserClassFolderItemDataPayload& InFolderPayload, FString& OutDiskPath);` (scope `ContentBrowserClassData`)
- L67 _prototype_ `bool GetClassFileItemPhysicalPath(const FContentBrowserClassFileItemDataPayload& InClassPayload, FString& OutDiskPath);` (scope `ContentBrowserClassData`)
- L69 _prototype_ `bool GetItemAttribute(IAssetTypeActions* InClassTypeActions, const UContentBrowserDataSource* InOwnerDataSource, const FContentBrowserItemData& InItem, const bool InIncludeMetaData, const FName InAttributeKey, FContentBrowserItemDataAttributeValue& OutAttributeValue);` (scope `ContentBrowserClassData`)
- L71 _prototype_ `bool GetClassFolderItemAttribute(const FContentBrowserClassFolderItemDataPayload& InFolderPayload, const bool InIncludeMetaData, const FName InAttributeKey, FContentBrowserItemDataAttributeValue& OutAttributeValue);` (scope `ContentBrowserClassData`)
- L73 _prototype_ `bool GetClassFileItemAttribute(IAssetTypeActions* InClassTypeActions, const FContentBrowserClassFileItemDataPayload& InClassPayload, const bool InIncludeMetaData, const FName InAttributeKey, FContentBrowserItemDataAttributeValue& OutAttributeValue);` (scope `ContentBrowserClassData`)
- L75 _prototype_ `bool GetItemAttributes(const UContentBrowserDataSource* InOwnerDataSource, const FContentBrowserItemData& InItem, const bool InIncludeMetaData, FContentBrowserItemDataAttributeValues& OutAttributeValues);` (scope `ContentBrowserClassData`)
- L77 _prototype_ `bool GetClassFileItemAttributes(const FContentBrowserClassFileItemDataPayload& InClassPayload, const bool InIncludeMetaData, FContentBrowserItemDataAttributeValues& OutAttributeValues);` (scope `ContentBrowserClassData`)

### `Plugins/Editor/ContentBrowser/ContentBrowserClassDataSource/Source/ContentBrowserClassDataSource/Public/ContentBrowserClassDataPayload.h` (Public)


#### class `FContentBrowserClassFolderItemDataPayload`  
`class FContentBrowserClassFolderItemDataPayload : public IContentBrowserItemDataPayload`  
_L12-32_
- inherits: `IContentBrowserItemDataPayload`
- L15 _public function_ `explicit FContentBrowserClassFolderItemDataPayload(const FName InInternalPath) : InternalPath(InInternalPath)`
- L20 _public function_ `FName GetInternalPath() const`
- L25 _public prototype_ `const FString& GetFilename() const;`
- L28 _private member_ `FName InternalPath;`
- L30 _private member_ `mutable bool bHasCachedFilename = false;`
- L31 _private member_ `mutable FString CachedFilename;`

#### class `FContentBrowserClassFileItemDataPayload`  
`class FContentBrowserClassFileItemDataPayload : public IContentBrowserItemDataPayload`  
_L34-67_
- inherits: `IContentBrowserItemDataPayload`
- L37 _public prototype_ `FContentBrowserClassFileItemDataPayload(const FName InInternalPath, UClass* InClass);`
- L39 _public function_ `FName GetInternalPath() const`
- L44 _public function_ `UClass* GetClass() const`
- L49 _public function_ `const FAssetData& GetAssetData() const`
- L54 _public prototype_ `const FString& GetFilename() const;`
- L56 _public prototype_ `void UpdateThumbnail(FAssetThumbnail& InThumbnail) const;`
- L59 _private member_ `FName InternalPath;`
- L61 _private member_ `TWeakObjectPtr<UClass> Class;`
- L63 _private member_ `FAssetData AssetData;`
- L65 _private member_ `mutable bool bHasCachedFilename = false;`
- L66 _private member_ `mutable FString CachedFilename;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API CONTENTBROWSERCLASSDATASOURCE_API`

### `Plugins/Editor/ContentBrowser/ContentBrowserClassDataSource/Source/ContentBrowserClassDataSource/Public/ContentBrowserClassDataSource.h` (Public)


#### struct `FContentBrowserCompiledClassDataFilter`  
`struct FContentBrowserCompiledClassDataFilter`  
_L21-31_
- reflection: `USTRUCT()`
- L27 _public member_ `TSet<TObjectPtr<UClass>> ValidClasses;` — `UPROPERTY()`
- L30 _public member_ `TSet<FName> ValidFolders;` — `UPROPERTY()`

#### class `UContentBrowserClassDataSource`  
`class UContentBrowserClassDataSource : public UContentBrowserDataSource`  
_L34-128_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UContentBrowserDataSource`
- L39 _public prototype_ `void Initialize(const bool InAutoRegister = true);`
- L41 _public prototype_ `virtual void Shutdown() override;`
- L43 _public prototype_ `virtual void CompileFilter(const FName InPath, const FContentBrowserDataFilter& InFilter, FContentBrowserDataCompiledFilter& OutCompiledFilter) override;`
- L45 _public prototype_ `virtual void EnumerateItemsMatchingFilter(const FContentBrowserDataCompiledFilter& InFilter, TFunctionRef<bool(FContentBrowserItemData&&)> InCallback) override;`
- L47 _public prototype_ `virtual void EnumerateItemsAtPath(const FName InPath, const EContentBrowserItemTypeFilter InItemTypeFilter, TFunctionRef<bool(FContentBrowserItemData&&)> InCallback) override;`
- L49 _public prototype_ `virtual void EnumerateItemsAtUserProvidedPath(const FStringView InPath, const EContentBrowserItemTypeFilter InItemTypeFilter, TFunctionRef<bool(FContentBrowserItemData&&)> InCallback) override;`
- L51 _public prototype_ `virtual bool EnumerateItemsForObjects(const TArrayView<UObject*> InObjects, TFunctionRef<bool(FContentBrowserItemData&&)> InCallback) override;`
- L53 _public prototype_ `virtual bool IsFolderVisible(const FName InPath, const EContentBrowserIsFolderVisibleFlags InFlags, const FContentBrowserFolderContentsFilter& InContentsFilter) override;`
- L55 _public prototype_ `virtual bool DoesItemPassFilter(const FContentBrowserItemData& InItem, const FContentBrowserDataCompiledFilter& InFilter) override;`
- L57 _public prototype_ `virtual bool GetItemAttribute(const FContentBrowserItemData& InItem, const bool InIncludeMetaData, const FName InAttributeKey, FContentBrowserItemDataAttributeValue& OutAttributeValue) override;`
- L59 _public prototype_ `virtual bool GetItemAttributes(const FContentBrowserItemData& InItem, const bool InIncludeMetaData, FContentBrowserItemDataAttributeValues& OutAttributeValues) override;`
- L61 _public prototype_ `virtual bool GetItemPhysicalPath(const FContentBrowserItemData& InItem, FString& OutDiskPath) override;`
- L63 _public prototype_ `virtual bool CanEditItem(const FContentBrowserItemData& InItem, FText* OutErrorMsg) override;`
- L65 _public prototype_ `virtual bool EditItem(const FContentBrowserItemData& InItem) override;`
- L67 _public prototype_ `virtual bool BulkEditItems(TArrayView<const FContentBrowserItemData> InItems) override;`
- L69 _public prototype_ `virtual bool AppendItemReference(const FContentBrowserItemData& InItem, FString& InOutStr) override;`
- L71 _public prototype_ `virtual bool AppendItemObjectPath(const FContentBrowserItemData& InItem, FString& InOutStr) override;`
- L73 _public prototype_ `virtual bool AppendItemPackageName(const FContentBrowserItemData& InItem, FString& InOutStr) override;`
- L75 _public prototype_ `virtual bool UpdateThumbnail(const FContentBrowserItemData& InItem, FAssetThumbnail& InThumbnail) override;`
- L77 _public prototype_ `virtual bool TryGetCollectionId(const FContentBrowserItemData& InItem, FSoftObjectPath& OutCollectionId) override;`
- L79 _public prototype_ `virtual bool Legacy_TryGetPackagePath(const FContentBrowserItemData& InItem, FName& OutPackagePath) override;`
- L81 _public prototype_ `virtual bool Legacy_TryGetAssetData(const FContentBrowserItemData& InItem, FAssetData& OutAssetData) override;`
- L83 _public prototype_ `virtual bool Legacy_TryConvertPackagePathToVirtualPath(const FName InPackagePath, FName& OutPath) override;`
- L85 _public prototype_ `virtual bool Legacy_TryConvertAssetDataToVirtualPath(const FAssetData& InAssetData, const bool InUseFolderPaths, FName& OutPath) override;`
- L88 _protected prototype_ `TSharedPtr<IAssetTypeActions> GetClassTypeActions();`
- L90 _protected prototype_ `virtual void BuildRootPathVirtualTree() override;`
- L91 _protected prototype_ `bool RootClassPathPassesFilter(const FName InRootClassPath, const bool bIncludeEngineClasses, const bool bIncludePluginClasses) const;`
- L94 _private prototype_ `bool IsKnownClassPath(const FName InPackagePath) const;`
- L96 _private prototype_ `bool GetClassPathsForCollections(TArrayView<const FCollectionRef> InCollections, const bool bIncludeChildCollections, TArray<FTopLevelAssetPath>& OutClassPaths);`
- L98 _private prototype_ `FContentBrowserItemData CreateClassFolderItem(const FName InFolderPath);`
- L100 _private prototype_ `FContentBrowserItemData CreateClassFileItem(UClass* InClass, FNativeClassHierarchyGetClassPathCache& InCache);`
- L102 _private prototype_ `FContentBrowserItemData CreateClassFolderItem(const FName InFolderPath, const TSharedPtr<const FNativeClassHierarchyNode>& InFolderNode);`
- L104 _private prototype_ `FContentBrowserItemData CreateClassFileItem(const FName InClassPath, const TSharedPtr<const FNativeClassHierarchyNode>& InClassNode);`
- L106 _private prototype_ `TSharedPtr<const FContentBrowserClassFolderItemDataPayload> GetClassFolderItemPayload(const FContentBrowserItemData& InItem) const;`
- L108 _private prototype_ `TSharedPtr<const FContentBrowserClassFileItemDataPayload> GetClassFileItemPayload(const FContentBrowserItemData& InItem) const;`
- L110 _private prototype_ `void OnNewClassRequested(const FName InSelectedPath);`
- L112 _private prototype_ `void PopulateAddNewContextMenu(UToolMenu* InMenu);`
- L114 _private prototype_ `void ConditionalCreateNativeClassHierarchy();`
- L116 _private prototype_ `void OnFoldersAdded(const TArrayView<TSharedRef<const FNativeClassHierarchyNode>> InFolders);`
- L118 _private prototype_ `void OnFoldersRemoved(const TArrayView<TSharedRef<const FNativeClassHierarchyNode>> InFolders);`
- L120 _private prototype_ `void OnClassesAdded(const TArrayView<TSharedRef<const FNativeClassHierarchyNode>> InClasses);`
- L122 _private prototype_ `void OnClassesRemoved(const TArrayView<TSharedRef<const FNativeClassHierarchyNode>> InClasses);`
- L124 _private member_ `TSharedPtr<FNativeClassHierarchy> NativeClassHierarchy;`
- L125 _private member_ `FNativeClassHierarchyGetClassPathCache NativeClassHierarchyGetClassPathCache;`
- L127 _private member_ `TSharedPtr<IAssetTypeActions> ClassTypeActions;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API CONTENTBROWSERCLASSDATASOURCE_API`
