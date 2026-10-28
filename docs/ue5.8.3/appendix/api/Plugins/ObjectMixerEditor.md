# Plugins / ObjectMixerEditor

- module root: `Plugins/Editor/ObjectMixer/ObjectMixer/Source/ObjectMixer`
- headers: 30; symbols: 834
- symbol kinds: class=26, delegate=8, enum=4, enumerator=16, function=110, macro=18, member=174, namespace=2, prototype=447, struct=29
- PrivateDependencyModuleNames: AdvancedWidgets, ApplicationCore, AssetDefinition, AssetRegistry, AssetTools, ContentBrowser, CoreUObject, DeveloperSettings, EditorConfig, EditorStyle, EditorWidgets, Engine, EngineAssetDefinitions, InputCore, Kismet, LevelEditor, LevelSequence, Projects, Sequencer, Slate, SlateCore, SourceControl, ToolMenus, ToolWidgets, TypedElementFramework, TypedElementRuntime, UMG, UnrealEd, WorkspaceMenuStructure
- PrivateIncludePathModuleNames: PlacementMode
- PublicDependencyModuleNames: Core, OutputLog, PropertyEditor, SceneOutliner

### `Plugins/Editor/ObjectMixer/ObjectMixer/Source/ObjectMixer/Private/AssetDefinition/AssetDefinition_MixerBlueprintObjectFilter.h` (Private)


#### class `UAssetDefinition_MixerBlueprintObjectFilter`  
`class UAssetDefinition_MixerBlueprintObjectFilter : public UAssetDefinition_Blueprint`  
_L9-25_
- reflection: `UCLASS()`
- inherits: `UAssetDefinition_Blueprint`
- L14 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L15 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L16 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`

### `Plugins/Editor/ObjectMixer/ObjectMixer/Source/ObjectMixer/Private/Views/Widgets/SObjectMixerPlacementAssetMenuEntry.h` (Private)


#### class `SObjectMixerPlacementAssetMenuEntry`  
`class SObjectMixerPlacementAssetMenuEntry : public SCompoundWidget`  
_L10-37_
- inherits: `SCompoundWidget`
- L13 _public function_ `SLATE_BEGIN_ARGS(SObjectMixerPlacementAssetMenuEntry)`
- L14 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedPtr<const struct FPlaceableItem>& InItem);`
- L18 _public prototype_ `virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L19 _public prototype_ `virtual FReply OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L20 _public prototype_ `virtual FReply OnDragDetected(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L22 _public prototype_ `bool IsPressed() const;`
- L24 _public member_ `TSharedPtr<const FPlaceableItem> Item;`
- L26 _public prototype_ `virtual FSlateColor GetForegroundColor() const override;`
- L29 _private prototype_ `const FSlateBrush* GetBorder() const;`
- L30 _private prototype_ `const FSlateBrush* GetIcon() const;`
- L32 _private member_ `bool bIsPressed = false;`
- L34 _private member_ `const FButtonStyle* Style = nullptr;`
- L36 _private member_ `mutable const FSlateBrush* AssetImage = nullptr;`

### `Plugins/Editor/ObjectMixer/ObjectMixer/Source/ObjectMixer/Public/ObjectFilter/ObjectMixerEditorActorSubObject.h` (Public)


#### struct `FObjectMixerEditorContainerProperty`  
`struct FObjectMixerEditorContainerProperty`  
_L12-22_
- desc: Container property mixer entry for displaying a container property (e.g. Array) in the mixer
- L18 _public member_ `FName PropertyName = NAME_None;` — If the subobject is stored in a container, supplying the container property's name will allow the mixer to display a row item for the container property itself
- L21 _public member_ `TAttribute<const FSlateBrush*> PropertyIconOverride;` — Optional custom icon to display for the container property; if not provided, a default one will be used

#### struct `FObjectMixerEditorActorSubObject`  
`struct FObjectMixerEditorActorSubObject`  
_L27-40_
- desc: Actor sub-object mixer entry that controls how the sub-object is displayed in the mixer
- L30 _public member_ `TWeakObjectPtr<UObject> Object = nullptr;` — Pointer to the subobject
- L33 _public member_ `FText DisplayName = FText::GetEmpty();` — Optional display name to use when displaying the object in the mixer
- L36 _public member_ `bool bIncludeObjectStack = false;` — Whether to include all parent objects up to the owning actor in the mixer
- L39 _public member_ `FObjectMixerEditorContainerProperty ContainerProperty;` — Optional container property to make the sub-object a child of in the mixer

### `Plugins/Editor/ObjectMixer/ObjectMixer/Source/ObjectMixer/Public/ObjectFilter/ObjectMixerEditorObjectFilter.h` (Public)


#### enum `EObjectMixerInheritanceInclusionOptions`  
`enum class EObjectMixerInheritanceInclusionOptions : uint8`  
_L17-37_
- reflection: `UENUM(BlueprintType)`
- L20 _public enumerator_ `None` — Get only the properties in the specified classes without considering parent or child classes
- L22 _public enumerator_ `IncludeOnlyImmediateParent` — Get properties from the class that the specified classes immediately derive from, but not the parents' parents + Specified Classes
- L24 _public enumerator_ `IncludeOnlyImmediateChildren` — Get properties from child classes but not child classes of child classes + Specified Classes
- L26 _public enumerator_ `IncludeOnlyImmediateParentAndChildren` — IncludeOnlyImmediateParent + IncludeOnlyImmediateChildren + Specified Classes
- L28 _public enumerator_ `IncludeAllParents` — Go up the chain of parent classes to get all properties in the specified classes' ancestries + Specified Classes
- L30 _public enumerator_ `IncludeAllChildren` — Get properties from all derived classes recursively + Specified Classes
- L32 _public enumerator_ `IncludeAllParentsAndChildren` — IncludeAllParents + IncludeAllChildren + Specified Classes
- L34 _public enumerator_ `IncludeAllParentsAndOnlyImmediateChildren` — IncludeAllParents + IncludeOnlyImmediateChildren + Specified Classes
- L36 _public enumerator_ `IncludeOnlyImmediateParentAndAllChildren` — IncludeOnlyImmediateParent + IncludeAllChildren + Specified Classes

#### enum `EObjectMixerTreeViewMode`  
`enum class EObjectMixerTreeViewMode : uint8`  
_L40-46_
- reflection: `UENUM(BlueprintType)`
- L43 _public enumerator_ `NoFolders` — Show all matching objects without folders
- L45 _public enumerator_ `Folders` — Display objects in a hierarchy with folders

#### class `UObjectMixerObjectFilter`  
`class UObjectMixerObjectFilter : public UObject`  
_L53-181_
- reflection: `UCLASS(MinimalAPI, Abstract, BlueprintType)`
- inherits: `UObject`
- desc: Native class for filtering object types to Object Mixer. Native C++ classes should inherit directly from this class.
- L59 _public prototype_ `UObjectMixerObjectFilter() = default;`
- L62 _public prototype_ `virtual void PostCDOCompiled(const FPostCDOCompiledContext& Context) override;` — Begin UObject overrides
- L71 _public function_ `virtual TSet<UClass*> GetObjectClassesToFilter() const` — Return the basic object types you want to filter for in your level. For example, if you want to work with Lights, return ULightComponentBase. If you also want to see the properties for parent or child classes, override the GetObjectMixerPropertyInheritanceInclusionOptions and GetForceAddedColumns functions.
- L78 _public function_ `virtual TSet<TSubclassOf<AActor>> GetObjectClassesToPlace() const` — Return the basic actor types you want to be able to place using the Add button. Note that only subclasses of AActor are supported and only those which have a registered factory. This includes most engine actor types.
- L83 _public prototype_ `virtual bool GetShowTransientObjects() const;` — Determines if transient objects (such as Sequencer Spawnables) should be shown in the list. False by default.
- L88 _public prototype_ `virtual bool ShouldAllowHybridRows() const;` — Determines if hybrid rows should be used when enabled in user settings. True by default.
- L93 _public prototype_ `virtual bool ShouldAllowColumnCustomizationByUser() const;` — Determines if the user should be able to change which columns are displayed. True by default.
- L100 _public prototype_ `virtual TSet<FName> GetColumnsToShowByDefault() const;` — Specify a list of property names corresponding to columns you want to show by default. For example, you can specify "Intensity" and "LightColor" to show only those property columns by default in the UI. Columns not specified will not be shown by default but can be enabled by the user in the UI.
- L107 _public prototype_ `virtual TSet<FName> GetColumnsToExclude() const;` — Specify a list of property names corresponding to columns you don't want to ever show. For example, you can specify "Intensity" and "LightColor" to ensure that they can't be enabled or shown in the UI. Columns not specified can be enabled by the user in the UI.
- L119 _public function_ `virtual TSet<FName> GetForceAddedColumns() const` — Specify a list of property names found in parent classes you want to show that aren't in the specified classes. Note that properties specified here do not override the properties specified in GetColumnsToExclude(), but do override the supported property tests so these will appear even if ShouldIncludeUnsupportedProperties returns false. For example, a ULightComponent displays "LightColor" in the editor's details panel, but ULightComponent itself doesn't have a property named "LightColor". Instead it's in its parent class, ULightComponentBase. In this scenario, ULightComponent is specified and PropertyInheritanceInclusionOptions is None, so "LightColor" won't appear by default. Specify "LightColor" in this function to ensure that "LightColor" will appear as a column as long as the property is accessible to one of the specified classes regardless of which parent class it comes from.
- L126 _public prototype_ `virtual EObjectMixerInheritanceInclusionOptions GetObjectMixerPropertyInheritanceInclusionOptions() const;` — Specify whether we should return only the properties of the specified classes or the properties of parent and child classes. Defaults to 'None' which only considers the properties of the specified classes. If you're not seeing all the properties you expected, try overloading this function.
- L132 _public prototype_ `virtual EObjectMixerInheritanceInclusionOptions GetObjectMixerPlacementClassInclusionOptions() const;` — Specify whether we should return only the specified classes or the parent and child classes in placement mode. Defaults to 'None' which only considers the specified classes.
- L138 _public prototype_ `virtual bool ShouldIncludeUnsupportedProperties() const;` — If true, properties that are not visible in the details panel and properties not supported by SSingleProperty will be selectable. Defaults to false.
- L144 _public prototype_ `virtual TSet<FName> GetPropertiesThatRequireListRefresh() const;` — If a property is changed that has a name found in this set, the panel will be refreshed. Add a property name to this list if you expect the list to change in some way after changing that property.
- L149 _public prototype_ `virtual TArray<AActor*> FindAssociatedActors(AActor* InActor) const;` — Fills OutAssociatedActors with additional actors to include as children in the ObjectMixer hierarchy for the given actor.
- L155 _public prototype_ `virtual bool IsActorAssociated(AActor* Actor, AActor* AssociatedActor) const;` — Returns true if AssociatedActor is associated with Actor. This should return true if the actor would be included in FindAssociatedActors, but is a separate function to avoid allocating an array every time.
- L160 _public prototype_ `virtual TArray<FObjectMixerEditorActorSubObject> GetActorSubObjects(AActor* InActor) const;` — Gets a list of subobjects to add to the outliner under the specified actor
- L165 _public prototype_ `virtual bool HasCustomDropHandling(const ISceneOutlinerTreeItem& DropTarget) const;` — Returns true if the given tree item should override the Object Mixer's standard handling for drop operations (ValidateDrop/OnDrop)
- L168 _public prototype_ `virtual FSceneOutlinerDragValidationInfo ValidateDrop(const ISceneOutlinerTreeItem& DropTarget, const FSceneOutlinerDragDropPayload& Payload) const;` — Test whether the specified payload can be dropped onto a tree item
- L171 _public prototype_ `virtual void OnDrop(ISceneOutlinerTreeItem& DropTarget, const FSceneOutlinerDragDropPayload& Payload, const FSceneOutlinerDragValidationInfo& ValidationInfo) const;` — Called when a payload is dropped onto a target
- L174 _public function_ `virtual void OnContextMenuContextCreated(FToolMenuContext& Context) const` — Called when a context menu is being created from in the hierarchy. Allows subclasses to inject additonal context data.
- L176 _public prototype_ `static TSet<UClass*> GetParentAndChildClassesFromSpecifiedClasses( const TSet<UClass*>& InSpecifiedClasses, EObjectMixerInheritanceInclusionOptions Options);`
- L179 _public prototype_ `static TSet<UClass*> GetParentAndChildClassesFromSpecifiedClasses( const TSet<TSubclassOf<AActor>>& InSpecifiedClasses, EObjectMixerInheritanceInclusionOptions Options);`

#### class `UObjectMixerBlueprintObjectFilter`  
`class UObjectMixerBlueprintObjectFilter : public UObjectMixerObjectFilter`  
_L188-323_
- reflection: `UCLASS(MinimalAPI, Abstract, Blueprintable)`
- inherits: `UObjectMixerObjectFilter`
- desc: Script class for filtering object types to Object Mixer. Blueprint classes should inherit directly from this class.
- L200 _public prototype_ `TSet<UClass*> GetObjectClassesToFilter() const override;` — `UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Object Mixer")` — Return the basic object types you want to filter for in your level. For example, if you want to work with Lights, return ULightComponentBase. If you also want to see the properties for parent or child classes, override the GetObjectMixerPropertyInheritanceInclusionOptions and GetForceAddedColumns functions.
- L202 _public function_ `TSet<UClass*> GetObjectClassesToFilter_Implementation() const`
- L213 _public prototype_ `TSet<TSubclassOf<AActor>> GetObjectClassesToPlace() const override;` — `UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Object Mixer")` — Return the basic actor types you want to be able to place using the Add button. Note that only subclasses of AActor are supported and only those which have a registered factory. This includes most engine actor types.
- L215 _public function_ `TSet<TSubclassOf<AActor>> GetObjectClassesToPlace_Implementation() const`
- L224 _public prototype_ `bool GetShowTransientObjects() const;` — `UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Object Mixer")` — Determines if transient objects (such as Sequencer Spawnables) should be shown in the list. False by default.
- L226 _public function_ `bool GetShowTransientObjects_Implementation() const`
- L237 _public prototype_ `TSet<FName> GetColumnsToShowByDefault() const override;` — `UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Object Mixer")` — Specify a list of property names corresponding to columns you want to show by default. For example, you can specify "Intensity" and "LightColor" to show only those property columns by default in the UI. Columns not specified will not be shown by default but can be enabled by the user in the UI.
- L239 _public function_ `TSet<FName> GetColumnsToShowByDefault_Implementation() const`
- L250 _public prototype_ `TSet<FName> GetColumnsToExclude() const override;` — `UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Object Mixer")` — Specify a list of property names corresponding to columns you don't want to ever show. For example, you can specify "Intensity" and "LightColor" to ensure that they can't be enabled or shown in the UI. Columns not specified can be enabled by the user in the UI.
- L252 _public function_ `TSet<FName> GetColumnsToExclude_Implementation() const`
- L267 _public prototype_ `TSet<FName> GetForceAddedColumns() const override;` — `UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Object Mixer")` — Specify a list of property names found in parent classes you want to show that aren't in the specified classes. Note that properties specified here do not override the properties specified in GetColumnsToExclude(). For example, a ULightComponent displays "LightColor" in the editor's details panel, but ULightComponent itself doesn't have a property named "LightColor". Instead it's in its parent class, ULightComponentBase. In this scenario, ULightComponent is specified and PropertyInheritanceInclusionOptions is None, so "LightColor" won't appear by default. Specify "LightColor" in this function to ensure that "LightColor" will appear as a column as long as the property is accessible to one of the specified classes regardless of which parent class it comes from.
- L269 _public function_ `TSet<FName> GetForceAddedColumns_Implementation() const`
- L280 _public prototype_ `EObjectMixerInheritanceInclusionOptions GetObjectMixerPropertyInheritanceInclusionOptions() const override;` — `UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Object Mixer")` — Specify whether we should return only the properties of the specified classes or the properties of parent and child classes. Defaults to 'None' which only considers the properties of the specified classes. If you're not seeing all the properties you expected, try overloading this function.
- L282 _public function_ `EObjectMixerInheritanceInclusionOptions GetObjectMixerPropertyInheritanceInclusionOptions_Implementation() const`
- L292 _public prototype_ `EObjectMixerInheritanceInclusionOptions GetObjectMixerPlacementClassInclusionOptions() const override;` — `UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Object Mixer")` — Specify whether we should return only the specified classes or the parent and child classes in placement mode. Defaults to 'None' which only considers the specified classes.
- L294 _public function_ `EObjectMixerInheritanceInclusionOptions GetObjectMixerPlacementClassInclusionOptions_Implementation() const`
- L304 _public prototype_ `bool ShouldIncludeUnsupportedProperties() const override;` — `UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Object Mixer")` — If true, properties that are not visible in the details panel and properties not supported by SSingleProperty will be selectable. Defaults to false.
- L306 _public function_ `bool ShouldIncludeUnsupportedProperties_Implementation() const`
- L316 _public prototype_ `TSet<FName> GetPropertiesThatRequireListRefresh() const override;` — `UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Object Mixer")` — If a property is changed that has a name found in this set, the panel will be refreshed. Add a property name to this list if you expect the list to change in some way after changing that property.
- L318 _public function_ `TSet<FName> GetPropertiesThatRequireListRefresh_Implementation() const`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API OBJECTMIXEREDITOR_API`

### `Plugins/Editor/ObjectMixer/ObjectMixer/Source/ObjectMixer/Public/ObjectMixerEditorLog.h` (Public)


#### Free symbols / members of external scopes

- L8 _delegate_ `DECLARE_LOG_CATEGORY_CLASS(LogObjectMixerEditor, Log, All);`
- L8 _prototype_ `DECLARE_LOG_CATEGORY_CLASS(LogObjectMixerEditor, Log, All);`

### `Plugins/Editor/ObjectMixer/ObjectMixer/Source/ObjectMixer/Public/ObjectMixerEditorModule.h` (Public)


#### class `FObjectMixerEditorModule`  
`class FObjectMixerEditorModule : public IModuleInterface`  
_L14-117_
- inherits: `IModuleInterface`
- L19 _public prototype_ `virtual void StartupModule() override;`
- L20 _public prototype_ `virtual void ShutdownModule() override;`
- L23 _public prototype_ `virtual UWorld* GetWorld();`
- L25 _public prototype_ `virtual void Initialize();`
- L26 _public prototype_ `virtual void Teardown();`
- L28 _public prototype_ `static FObjectMixerEditorModule& Get();`
- L30 _public prototype_ `static void OpenProjectSettings();`
- L32 _public prototype_ `virtual FName GetModuleName() const;`
- L34 _public prototype_ `virtual TSharedPtr<SWidget> MakeObjectMixerDialog( TSubclassOf<UObjectMixerObjectFilter> InDefaultFilterClass = {});`
- L38 _public prototype_ `virtual TArray<TWeakPtr<ISequencer>> GetSequencers() const;` — Get a list of sequencers that are currently active in the editor.
- L44 _public prototype_ `virtual TSharedPtr<SDockTab> FindNomadTab();` — Tries to find the nomad tab assigned to this instance of Object Mixer. If DockTab is not set, will try to find the tab using GetTabSpawnerId().
- L50 _public prototype_ `bool RegenerateListWidget();` — Build the List widget from scratch. If DockTab is not set, will try to find the tab using GetTabSpawnerId(). @return True if the widget was regenerated. False if the DockTab was invalid and could not be found.
- L53 _public prototype_ `virtual void OnRenameCommand();` — Called when the Rename command is executed from the UI or hotkey.
- L55 _public prototype_ `void RegisterMenuGroup();`
- L56 _public prototype_ `void UnregisterMenuGroup();`
- L57 _public prototype_ `virtual void SetupMenuItemVariables();`
- L58 _public prototype_ `virtual void RegisterTabSpawner();`
- L59 _public prototype_ `virtual FName GetTabSpawnerId();`
- L65 _public prototype_ `bool RegisterItemInMenuGroup(FWorkspaceItem& InItem);` — Add a tab spawner to the Object Mixer menu group. @return If adding the item to the menu was successful
- L67 _public prototype_ `virtual void UnregisterTabSpawner();`
- L68 _public prototype_ `virtual void RegisterSettings() const;`
- L69 _public prototype_ `virtual void UnregisterSettings() const;`
- L71 _public prototype_ `virtual TSharedRef<SDockTab> SpawnTab(const FSpawnTabArgs& Args);`
- L73 _public prototype_ `TSharedPtr<FWorkspaceItem> GetWorkspaceGroup();`
- L79 _public prototype_ `const TSubclassOf<UObjectMixerObjectFilter>& GetDefaultFilterClass() const;` — This is the filter class used to initialize the ListModel. This filter class cannot be turned off by the end user.
- L81 _public member_ `const static FName BaseObjectMixerModuleName;`
- L83 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnBlueprintFilterCompiled);`
- L84 _public function_ `FOnBlueprintFilterCompiled& OnBlueprintFilterCompiled()`
- L92 _protected member_ `TSharedPtr<FObjectMixerEditorList> ListModel;` — Lives for as long as the module is loaded.
- L95 _protected member_ `FText TabLabel;` — The text that appears on the spawned nomad tab
- L98 _protected member_ `TWeakPtr<SDockTab> DockTab;` — The actual spawned nomad tab
- L101 _protected member_ `FText MenuItemName;` — Menu Item variables
- L102 _protected member_ `FSlateIcon MenuItemIcon;`
- L103 _protected member_ `FText MenuItemTooltip;`
- L104 _protected member_ `ETabSpawnerMenuType::Type TabSpawnerType = ETabSpawnerMenuType::Enabled;`
- L110 _protected member_ `TSubclassOf<UObjectMixerObjectFilter> DefaultFilterClass;` — If set, this is the filter class used to initialize the ListModel. This filter class cannot be turned off by the end user.
- L112 _protected member_ `FOnBlueprintFilterCompiled OnBlueprintFilterCompiledDelegate;`
- L116 _private member_ `TSharedPtr<FWorkspaceItem> WorkspaceGroup;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API OBJECTMIXEREDITOR_API`
- L83 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnBlueprintFilterCompiled);`

### `Plugins/Editor/ObjectMixer/ObjectMixer/Source/ObjectMixer/Public/ObjectMixerEditorSerializedData.h` (Public)


#### struct `FObjectMixerCollectionObjectData`  
`struct FObjectMixerCollectionObjectData`  
_L13-30_
- reflection: `USTRUCT()`
- L18 _public member_ `FSoftObjectPath ObjectPath = {};` — `UPROPERTY()`
- L20 _public function_ `bool operator==(const FObjectMixerCollectionObjectData& Other) const`

#### struct `FObjectMixerCollectionObjectSet`  
`struct FObjectMixerCollectionObjectSet`  
_L33-52_
- reflection: `USTRUCT()`
- L38 _public member_ `FName CollectionName = NAME_None;` — `UPROPERTY()`
- L41 _public member_ `TArray<FObjectMixerCollectionObjectData> CollectionObjects = {};` — `UPROPERTY()`
- L43 _public function_ `bool operator==(const FObjectMixerCollectionObjectSet& Other) const`

#### struct `FObjectMixerColumnData`  
`struct FObjectMixerColumnData`  
_L55-74_
- reflection: `USTRUCT()`
- L60 _public member_ `FName ColumnName = NAME_None;` — `UPROPERTY()`
- L63 _public member_ `bool bShouldBeEnabled = false;` — `UPROPERTY()`
- L65 _public function_ `bool operator==(const FObjectMixerColumnData& Other) const`

#### struct `FObjectMixerSerializationDataPerFilter`  
`struct FObjectMixerSerializationDataPerFilter`  
_L77-99_
- reflection: `USTRUCT()`
- L82 _public member_ `FName FilterClassName = NAME_None;` — `UPROPERTY()`
- L85 _public member_ `TArray<FObjectMixerCollectionObjectSet> SerializedCollections = {};` — `UPROPERTY()`
- L88 _public member_ `TSet<FObjectMixerColumnData> SerializedColumnData = {};` — `UPROPERTY()`
- L90 _public function_ `bool operator==(const FObjectMixerSerializationDataPerFilter& Other) const`

#### class `UObjectMixerEditorSerializedData`  
`class UObjectMixerEditorSerializedData : public UObject`  
_L102-148_
- reflection: `UCLASS(MinimalAPI, config = ObjectMixerSerializedData)`
- inherits: `UObject`
- L107 _public function_ `UObjectMixerEditorSerializedData(const FObjectInitializer& ObjectInitializer)`
- L114 _public member_ `TSet<FObjectMixerSerializationDataPerFilter> SerializedDataPerFilter;` — `UPROPERTY(Config)`
- L116 _public prototype_ `FObjectMixerSerializationDataPerFilter* FindSerializationDataByFilterClassName(const FName& FilterClassName);`
- L118 _public prototype_ `bool AddObjectsToCollection(const FName& FilterClassName, const FName& CollectionName, const TSet<FSoftObjectPath>& ObjectsToAdd);`
- L120 _public prototype_ `bool RemoveObjectsFromCollection(const FName& FilterClassName, const FName& CollectionName, const TSet<FSoftObjectPath>& ObjectsToRemove);`
- L122 _public prototype_ `bool RemoveCollection(const FName& FilterClassName, const FName& CollectionName);`
- L124 _public prototype_ `bool DuplicateCollection(const FName& FilterClassName, const FName& CollectionToDuplicateName, FName& DesiredDuplicateName);`
- L126 _public prototype_ `bool ReorderCollection(const FName& FilterClassName, const FName& CollectionToMoveName, const FName& CollectionInsertBeforeName);`
- L128 _public prototype_ `bool RenameCollection(const FName& FilterClassName, const FName CollectionNameToRename, const FName NewCollectionName);`
- L130 _public prototype_ `bool DoesCollectionExist(const FName& FilterClassName, const FName& CollectionName);`
- L132 _public prototype_ `bool IsObjectInCollection(const FName& FilterClassName, const FName& CollectionName, const FSoftObjectPath& InObject);`
- L134 _public prototype_ `TSet<FName> GetCollectionsForObject(const FName& FilterClassName, const FSoftObjectPath& InObject);`
- L136 _public prototype_ `TArray<FName> GetAllCollectionNames(const FName& FilterClassName);`
- L138 _public prototype_ `void SetShouldShowColumn(const FName& FilterClassName, const FName& ColumnName, const bool bNewShouldShowColumn);`
- L140 _public prototype_ `bool IsColumnDataSerialized(const FName& FilterClassName, const FName& ColumnName);`
- L142 _public prototype_ `bool ShouldShowColumn(const FName& FilterClassName, const FName& ColumnName);`
- L144 _public member_ `static FName AllCollectionName;`
- L146 _public member_ `FOnObjectMixerCollectionChanged OnObjectMixerCollectionMapChanged;`
- L147 _public member_ `FOnObjectMixerCollectionRenamed OnObjectMixerCollectionRenamed;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API OBJECTMIXEREDITOR_API`
- L9 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnObjectMixerCollectionChanged) DECLARE_MULTICAST_DELEGATE_TwoParams(FOnObjectMixerCollectionRenamed, FName, FName) USTRUCT() struct FObjectMixerCollectionObjectData { GENERATED_BODY() UPROPERTY() FSoftObjectPath ObjectPath = {}; bool operator==(const FObjectMixerCollectionObjectData& Other) const { return ObjectPath == Other.ObjectPath; } friend uint32 GetTypeHash (const FObjectMixerCollectionObjectData& Other) { return GetTypeHash(Other.ObjectPath); } };`
- L10 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnObjectMixerCollectionRenamed, FName, FName) USTRUCT() struct FObjectMixerCollectionObjectData { GENERATED_BODY() UPROPERTY() FSoftObjectPath ObjectPath = {}; bool operator==(const FObjectMixerCollectionObjectData& Other) const { return ObjectPath == Other.ObjectPath; } friend uint32 GetTypeHash (const FObjectMixerCollectionObjectData& Other) { return GetTypeHash(Other.ObjectPath); } };`
- L25 _function_ `friend uint32 GetTypeHash (const FObjectMixerCollectionObjectData& Other)`
- L48 _function_ `friend uint32 GetTypeHash (const FObjectMixerCollectionObjectSet& Other)`
- L70 _function_ `friend uint32 GetTypeHash (const FObjectMixerColumnData& Other)`
- L95 _function_ `friend uint32 GetTypeHash (const FObjectMixerSerializationDataPerFilter& Other)`

### `Plugins/Editor/ObjectMixer/ObjectMixer/Source/ObjectMixer/Public/ObjectMixerEditorSettings.h` (Public)


#### enum `EObjectMixerHybridMode`  
`enum class EObjectMixerHybridMode : uint8`  
_L10-15_
- reflection: `UENUM(BlueprintType)`
- L12 _public enumerator_ `HybridActor UMETA(DisplayName="Hybrid Rows (Select Actor)", ToolTip="Makes hybrid rows and selects the actor in the Scene Outliner when an actor with a single matching component is selected.")`
- L13 _public enumerator_ `HybridComponent UMETA(DisplayName="Hybrid Rows (Select Component)", ToolTip="Makes hybrid rows and selects the component in the Scene Outliner when an actor with a single matching component is selected.")`
- L14 _public enumerator_ `HybridNone UMETA(DisplayName="Do not make hybrid rows", ToolTip="Does not make hybrid rows when an actor with a single matching component is selected. Actor and component rows will be split.")`

#### class `UObjectMixerEditorSettings`  
`class UObjectMixerEditorSettings : public UDeveloperSettings`  
_L18-49_
- reflection: `UCLASS(MinimalAPI, config = ObjectMixer)`
- inherits: `UDeveloperSettings`
- L24 _public function_ `static bool DoesPropertyChangeRequireListRebuild(const FPropertyChangedEvent& Event)`
- L29 _public function_ `bool IsHybridRowModeEnabled() const`
- L40 _public member_ `bool bSyncSelection = true;` — `UPROPERTY(Config, EditAnywhere, Category="Object Mixer")` — If enabled, clicking an item in the mixer list will also select the item in the Scene Outliner. Alt + Click to select items in mixer without selecting the item in the Scene outliner. If disabled, selections will not sync unless Alt is held. Effectively, this is the opposite behavior.
- L48 _public member_ `EObjectMixerHybridMode HybridRowPolicy = EObjectMixerHybridMode::HybridActor;` — `UPROPERTY(Config, EditAnywhere, Category="Object Mixer")` — Determines how rows with a single matching component are displayed. By default, these rows are condensed into a single row. Selecting that row will select the actor in the scene outliner, but not the component. You can choose to select the component instead, or choose to not condense the rows and leave them separated.

### `Plugins/Editor/ObjectMixer/ObjectMixer/Source/ObjectMixer/Public/ObjectMixerEditorStyle.h` (Public)


#### class `FObjectMixerEditorStyle`  
`class FObjectMixerEditorStyle : FSlateStyleSet`  
_L9-38_
- inherits: `FSlateStyleSet`
- L13 _public prototype_ `static void Initialize();`
- L15 _public prototype_ `static void Shutdown();`
- L17 _public prototype_ `static void ReloadTextures();`
- L19 _public prototype_ `static const ISlateStyle& Get();`
- L21 _public prototype_ `virtual const FName& GetStyleSetName() const override;`
- L23 _public prototype_ `virtual const FSlateBrush* GetBrush(const FName PropertyName, const ANSICHAR* Specifier = nullptr, const ISlateStyle* RequestingStyle = nullptr) const override;`
- L26 _public function_ `template< typename WidgetStyleType > static const WidgetStyleType& GetWidgetStyle(FName PropertyName, const ANSICHAR* Specifier = nullptr)`
- L33 _private prototype_ `static FString GetExternalPluginContent(const FString& PluginName, const FString& RelativePath, const ANSICHAR* Extension);`
- L35 _private prototype_ `static TSharedRef<FSlateStyleSet> Create();`
- L37 _private member_ `static TSharedPtr<FSlateStyleSet> StyleInstance;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API OBJECTMIXEREDITOR_API`

### `Plugins/Editor/ObjectMixer/ObjectMixer/Source/ObjectMixer/Public/ObjectMixerFilterFactory.h` (Public)


#### class `UObjectMixerBlueprintFilterFactory`  
`class UObjectMixerBlueprintFilterFactory : public UFactory`  
_L12-32_
- reflection: `UCLASS(MinimalAPI, hidecategories = Object)`
- inherits: `UFactory`
- L16 _public prototype_ `UObjectMixerBlueprintFilterFactory();`
- L20 _public member_ `TSubclassOf<UObject> ParentClass;` — `UPROPERTY(VisibleAnywhere, Category="ObjectMixerBlueprintFilterFactory", meta=(AllowAbstract = "", BlueprintBaseOnly = ""))` — The parent class of the created blueprint
- L23 _public prototype_ `virtual FText GetDisplayName() const override;`
- L24 _public prototype_ `virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;`
- L25 _public prototype_ `virtual FString GetDefaultNewAssetName() const override;`
- L26 _public prototype_ `virtual uint32 GetMenuCategories() const override;`
- L27 _public prototype_ `virtual FText GetToolTip() const override;`
- L28 _public prototype_ `virtual FString GetToolTipDocumentationExcerpt() const override;`
- L29 _public prototype_ `virtual TArray<FAssetCategoryPath> GetAssetMenuPathsForCategory(FName InCategory) const override;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API OBJECTMIXEREDITOR_API`

### `Plugins/Editor/ObjectMixer/ObjectMixer/Source/ObjectMixer/Public/SelectionInterface/IObjectMixerSelectionInterface.h` (Public)


#### class `IObjectMixerSelectionInterface`  
`class IObjectMixerSelectionInterface : public TSharedFromThis<IObjectMixerSelectionInterface>`  
_L15-58_
- inherits: `TSharedFromThis<IObjectMixerSelectionInterface>`
- desc: Provides an interface for synchronizing an ObjectMixer's selection with another part of the editor
- L18 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnSelectionChanged);`
- L21 _public prototype_ `virtual ~IObjectMixerSelectionInterface() = default;`
- L29 _public prototype_ `virtual void SelectActors(const TArray<AActor*>& InSelectedActors, bool bShouldSelect, bool bSelectEvenIfHidden) = 0;` — Select or deselect a list of components. @param	InSelectedActors		The actors to select. @param	bShouldSelect			If true, select the actors and deselect all other actors. If false, only deselect the listed actors. @param	bSelectEvenIfHidden		If false, only select actors that are visible (e.g. not filtered out) in the editor.
- L37 _public prototype_ `virtual void SelectComponents(const TArray<UActorComponent*>& InSelectedComponents, bool bShouldSelect, bool bSelectEvenIfHidden) = 0;` — Select or deselect a list of components. @param	InSelectedComponents	The components to select. @param	bShouldSelect			If true, select the components and deselect all other components. If false, only deselect the listed components. @param	bSelectEvenIfHidden		If false, only select components that are visible (e.g. not filtered out) in the editor.
- L45 _public prototype_ `virtual void SelectSubObjects(const TArray<UObject*>& InSelectedSubObjects, bool bShouldSelect, bool bSelectEvenIfHidden) = 0;` — Select or deselect a list of actor sub-objects. @param	InSelectedSubObjects	The sub-objects to select. @param	bShouldSelect			If true, select the sub-objects and deselect all other sub-objects. If false, only deselect the listed sub-objects. @param	bSelectEvenIfHidden		If false, only select sub-objects that are visible (e.g. not filtered out) in the editor.
- L48 _public prototype_ `virtual TArray<AActor*> GetSelectedActors() const = 0;` — Get the list of selected actors.
- L51 _public prototype_ `virtual TArray<UActorComponent*> GetSelectedComponents() const = 0;` — Get the list of selected components.
- L54 _public prototype_ `virtual TArray<UObject*> GetSelectedSubObjects() const = 0;` — Get the list of selected sub-objects
- L57 _public prototype_ `virtual FOnSelectionChanged& OnSelectionChanged() = 0;` — Get the event handler that is raised when the synchronized selection changes.

#### Free symbols / members of external scopes

- L18 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnSelectionChanged);`

### `Plugins/Editor/ObjectMixer/ObjectMixer/Source/ObjectMixer/Public/SelectionInterface/LevelEditorObjectMixerSelectionInterface.h` (Public)


#### class `FLevelEditorObjectMixerSelectionInterface`  
`class FLevelEditorObjectMixerSelectionInterface : public IObjectMixerSelectionInterface`  
_L12-33_
- inherits: `IObjectMixerSelectionInterface`
- desc: Provides an interface for the ObjectMixer to synchronize with the level editor's selections (via GEditor)
- L16 _public prototype_ `FLevelEditorObjectMixerSelectionInterface();`
- L20 _public prototype_ `virtual void SelectActors(const TArray<AActor*>& InSelectedActors, bool bShouldSelect, bool bSelectEvenIfHidden) override;`
- L21 _public prototype_ `virtual void SelectComponents(const TArray<UActorComponent*>& InSelectedComponents, bool bShouldSelect, bool bSelectEvenIfHidden) override;`
- L22 _public function_ `virtual void SelectSubObjects(const TArray<UObject*>& InSelectedSubObjects, bool bShouldSelect, bool bSelectEvenIfHidden) override`
- L23 _public prototype_ `virtual TArray<AActor*> GetSelectedActors() const override;`
- L24 _public prototype_ `virtual TArray<UActorComponent*> GetSelectedComponents() const override;`
- L25 _public function_ `virtual TArray<UObject*> GetSelectedSubObjects() const override`
- L26 _public function_ `virtual FOnSelectionChanged& OnSelectionChanged() override`
- L30 _private prototype_ `void OnLevelSelectionChanged(UObject* Obj);`
- L32 _private member_ `FOnSelectionChanged SelectionChanged;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API OBJECTMIXEREDITOR_API`

### `Plugins/Editor/ObjectMixer/ObjectMixer/Source/ObjectMixer/Public/Views/List/Modes/ObjectMixerOutlinerHierarchy.h` (Public)


#### class `FObjectMixerOutlinerHierarchy`  
`class FObjectMixerOutlinerHierarchy : public ISceneOutlinerHierarchy, public FNoncopyable`  
_L14-124_
- inherits: `ISceneOutlinerHierarchy,FNoncopyable`
- L17 _public prototype_ `virtual ~FObjectMixerOutlinerHierarchy();`
- L19 _public prototype_ `static TUniquePtr<FObjectMixerOutlinerHierarchy> Create(class ISceneOutlinerMode* Mode, const TWeakObjectPtr<UWorld>& World);`
- L21 _public prototype_ `FObjectMixerOutlinerMode* GetCastedMode() const;`
- L22 _public prototype_ `const UObjectMixerObjectFilter* GetObjectFilter() const;`
- L25 _public prototype_ `virtual void CreateItems(TArray<FSceneOutlinerTreeItemPtr>& OutItems) const override;` — Create a linearization of all applicable items in the hierarchy
- L27 _public prototype_ `virtual void CreateChildren(const FSceneOutlinerTreeItemPtr& Item, TArray<FSceneOutlinerTreeItemPtr>& OutChildren) const override;` — Create a linearization of all direct and indirect children of a given item in the hierarchy
- L29 _public prototype_ `virtual FSceneOutlinerTreeItemPtr FindOrCreateParentItem(const ISceneOutlinerTreeItem& Item, const TMap<FSceneOutlinerTreeItemID, FSceneOutlinerTreeItemPtr>& Items, bool bCreate = false) override;` — Forcibly create a parent item for a given tree item
- L31 _public function_ `void SetShowingComponents(bool bInShowingComponents)`
- L32 _public function_ `void SetShowingOnlyActorWithValidComponents(bool bInShowingOnlyActorWithValidComponents)`
- L33 _public function_ `void SetShowingLevelInstances(bool bInShowingLevelInstances)`
- L34 _public function_ `void SetShowingUnloadedActors(bool bInShowingUnloadedActors)`
- L35 _public function_ `void SetShowingEmptyFolders(bool bInShowingEmptyFolders)`
- L39 _protected prototype_ `bool DoesWorldObjectHaveAcceptableClass(const UObject* Object) const;`
- L41 _protected prototype_ `void CreateFolderChild(const FFolder& Folder, UWorld* World, TArray<FSceneOutlinerTreeItemPtr>& OutItems) const;`
- L43 _protected prototype_ `void ForEachActorInLevel(AActor* Actor, const ULevelInstanceSubsystem* LevelInstanceSubsystem, TArray<FSceneOutlinerTreeItemPtr>& OutItems) const;`
- L46 _protected prototype_ `void CreateWorldChildren(UWorld* World, TArray<FSceneOutlinerTreeItemPtr>& OutItems) const;` — Adds all the direct and indirect children of a world to OutItems
- L52 _protected prototype_ `bool CreateComponentItems(AActor* Actor, TArray<FSceneOutlinerTreeItemPtr>& OutItems) const;` — Create all component items for an actor if we are showing components and place them in OutItems. Items not added if filtered out. @return true if any items would have been returned before filtering
- L58 _protected prototype_ `bool CreateAssociatedActorItems(AActor* Actor, TArray<FSceneOutlinerTreeItemPtr>& OutItems) const;` — Create all associated actor items for an actor and place them in OutItems. Items not added if filtered out. @return true if any items would have been returned before filtering
- L66 _protected prototype_ `bool CreateSubObjectItems(AActor* Actor, TArray<FSceneOutlinerTreeItemPtr>& OutItems) const;` — Create all subobject items for an actor and place them in OutItems. @param Actor The actor to get subobjects for @param OutItems The resulting list of tree items @return true if any items would have been returned before filtering
- L72 _protected prototype_ `TArray<FSceneOutlinerTreeItemPtr> ConditionallyCreateActorAndComponentItems(AActor* Actor) const;` — Create all component items for an actor if we are showing components and place them in OutItems. Items not added if filtered out. If components are returned or would be returned before filters, the Actor will be added at the beginning of the array.
- L75 _protected prototype_ `void OnWorldPartitionCreated(UWorld* InWorld);` — Update the hierarchy when actor or world changing events occur
- L77 _protected prototype_ `void OnLevelActorAdded(AActor* InActor);`
- L78 _protected prototype_ `void OnLevelActorDeleted(AActor* InActor);`
- L80 _protected prototype_ `void OnLevelActorAttached(AActor* InActor, const AActor* InParent);`
- L81 _protected prototype_ `void OnLevelActorDetached(AActor* InActor, const AActor* InParent);`
- L83 _protected prototype_ `void OnLevelActorFolderChanged(const AActor* InActor, FName OldPath);`
- L85 _protected prototype_ `void OnLoadedActorAdded(AActor& InActor);`
- L86 _protected prototype_ `void OnLoadedActorRemoved(AActor& InActor);`
- L88 _protected prototype_ `void OnActorDescInstanceRemoved(FWorldPartitionActorDescInstance* ActorDescInstance);`
- L90 _protected prototype_ `void OnComponentsUpdated();`
- L92 _protected prototype_ `void OnLevelActorListChanged();`
- L94 _protected prototype_ `void OnActorFolderAdded(UActorFolder* InActorFolder);`
- L95 _protected prototype_ `void OnActorFoldersUpdatedEvent(ULevel* InLevel);`
- L97 _protected prototype_ `void OnLevelAdded(ULevel* InLevel, UWorld* InWorld);`
- L98 _protected prototype_ `void OnLevelRemoved(ULevel* InLevel, UWorld* InWorld);`
- L100 _protected prototype_ `void OnWorldPartitionInitialized(UWorldPartition* InWorldPartition);`
- L101 _protected prototype_ `void OnWorldPartitionUninitialized(UWorldPartition* InWorldPartition);`
- L104 _protected prototype_ `void OnBroadcastFolderCreate(UWorld& InWorld, const FFolder& InNewFolder);` — Called when a folder is to be created
- L107 _protected prototype_ `void OnBroadcastFolderMove(UWorld& InWorld, const FFolder& InOldFolder, const FFolder& InNewFolder);` — Called when a folder is to be moved
- L110 _protected prototype_ `void OnBroadcastFolderDelete(UWorld& InWorld, const FFolder& InFolder);` — Called when a folder is to be deleted
- L113 _protected prototype_ `void FullRefreshEvent();` — Send a an event indicating a full refresh of the hierarchy is required
- L115 _protected member_ `TWeakObjectPtr<UWorld> RepresentingWorld;`
- L117 _protected member_ `bool bShowingComponents = true;`
- L118 _protected member_ `bool bShowingOnlyActorWithValidComponents = true;`
- L119 _protected member_ `bool bShowingLevelInstances = false;`
- L120 _protected member_ `bool bShowingUnloadedActors = false;`
- L121 _protected member_ `bool bShowingEmptyFolders = false;`
- L123 _protected prototype_ `FObjectMixerOutlinerHierarchy(ISceneOutlinerMode* Mode, const TWeakObjectPtr<UWorld>& Worlds);`

### `Plugins/Editor/ObjectMixer/ObjectMixer/Source/ObjectMixer/Public/Views/List/Modes/ObjectMixerOutlinerMode.h` (Public)


#### struct `ObjectMixerOutliner::FHybridRowSelector`  
`struct FHybridRowSelector`  
_L25-33_
- desc: A row selector that depends on whether hybrid rows are allowed
- L27 _public prototype_ `FHybridRowSelector(const FObjectMixerOutlinerMode* Mode);`
- L29 _public function_ `bool ShouldAllowHybridRows() const`
- L32 _private member_ `bool bAllowHybridRows = true;`

#### struct `ObjectMixerOutliner::FWeakActorSelectorAcceptingComponents`  
`struct FWeakActorSelectorAcceptingComponents`  
_L35-38_
- L37 _public prototype_ `bool operator()(const TWeakPtr<ISceneOutlinerTreeItem>& Item, TWeakObjectPtr<AActor>& DataOut) const;`

#### struct `ObjectMixerOutliner::FComponentSelector`  
`struct FComponentSelector : FHybridRowSelector`  
_L40-45_
- inherits: `FHybridRowSelector`
- L44 _public prototype_ `bool operator()(const TWeakPtr<ISceneOutlinerTreeItem>& Item, UActorComponent*& DataOut) const;`

#### struct `ObjectMixerOutliner::FWeakActorSelector`  
`struct FWeakActorSelector`  
_L48-51_
- desc: Functor which can be used to get weak actor pointers from a selection
- L50 _public prototype_ `bool operator()(const TWeakPtr<ISceneOutlinerTreeItem>& Item, TWeakObjectPtr<AActor>& DataOut) const;`

#### struct `ObjectMixerOutliner::FActorSelector`  
`struct FActorSelector : FHybridRowSelector`  
_L54-59_
- inherits: `FHybridRowSelector`
- desc: Functor which can be used to get actors from a selection including component parents
- L58 _public prototype_ `bool operator()(const TWeakPtr<ISceneOutlinerTreeItem>& Item, AActor*& ActorPtrOut) const;`

#### struct `ObjectMixerOutliner::FActorHandleSelector`  
`struct FActorHandleSelector`  
_L62-65_
- desc: Functor which can be used to get actor descriptors from a selection
- L64 _public prototype_ `bool operator()(const TWeakPtr<ISceneOutlinerTreeItem>& Item, FWorldPartitionHandle& ActorHandleOut) const;`

#### struct `ObjectMixerOutliner::FFolderPathSelector`  
`struct FFolderPathSelector`  
_L67-70_
- L69 _public prototype_ `bool operator()(TWeakPtr<ISceneOutlinerTreeItem> Item, FFolder& DataOut) const;`

#### struct `ObjectMixerOutliner::FObjectSelector`  
`struct FObjectSelector`  
_L72-75_
- L74 _public prototype_ `bool operator()(TWeakPtr<ISceneOutlinerTreeItem> Item, UObject*& OutObject);`

#### struct `FObjectMixerOutlinerModeConfig`  
`struct FObjectMixerOutlinerModeConfig`  
_L79-122_
- reflection: `USTRUCT()`
- L85 _public member_ `bool bHideTemporaryActors = false;` — `UPROPERTY()` — True when the Scene Outliner is hiding temporary/run-time Actors
- L89 _public member_ `bool bShowOnlyActorsInCurrentLevel = false;` — `UPROPERTY()` — True when the Scene Outliner is showing only Actors that exist in the current level
- L93 _public member_ `bool bShowOnlyActorsInCurrentDataLayers = false;` — `UPROPERTY()` — True when the Scene Outliner is showing only Actors that exist in the current data layers
- L97 _public member_ `bool bShowOnlyActorsInCurrentContentBundle = false;` — `UPROPERTY()` — True when the Scene Outliner is showing only Actors that exist in the current content bundle
- L101 _public member_ `bool bShowOnlySelectedActors = false;` — `UPROPERTY()` — True when the Scene Outliner is only displaying selected Actors
- L105 _public member_ `bool bHideActorComponents = true;` — `UPROPERTY()` — True when the Scene Outliner is not displaying Actor Components
- L109 _public member_ `bool bHideLevelInstanceHierarchy = false;` — `UPROPERTY()` — True when the Scene Outliner is not displaying LevelInstances
- L113 _public member_ `bool bHideUnloadedActors = false;` — `UPROPERTY()` — True when the Scene Outliner is not displaying unloaded actors
- L117 _public member_ `bool bHideEmptyFolders = false;` — `UPROPERTY()` — True when the Scene Outliner is not displaying empty folders
- L121 _public member_ `bool bAlwaysFrameSelection = true;` — `UPROPERTY()` — True when the Scene Outliner updates when an actor is selected in the viewport

#### class `UObjectMixerOutlinerModeEditorConfig`  
`class UObjectMixerOutlinerModeEditorConfig : public UEditorConfigBase`  
_L125-146_
- reflection: `UCLASS(EditorConfig="ObjectMixerOutlinerMode")`
- inherits: `UEditorConfigBase`
- L131 _public function_ `static void Initialize()`
- L141 _public member_ `TMap<FName, FObjectMixerOutlinerModeConfig> Browsers;` — `UPROPERTY(meta=(EditorConfig))`
- L145 _private member_ `static TObjectPtr<UObjectMixerOutlinerModeEditorConfig> Instance;`

#### struct `FObjectMixerOutlinerModeParams`  
`struct FObjectMixerOutlinerModeParams : FActorModeParams`  
_L148-161_
- inherits: `FActorModeParams`
- L150 _public function_ `FObjectMixerOutlinerModeParams()`
- L152 _public function_ `FObjectMixerOutlinerModeParams( SSceneOutliner* InSceneOutliner, const TWeakObjectPtr<UWorld>& InSpecifiedWorldToDisplay = nullptr, bool bInHideComponents = true, bool bInHideLevelInstanceHierarchy = true, bool bInHideUnloadedActors = true, bool bInHideEmptyFolders = true, bool bInHideActorWithNoComponent = true) : FActorModeParams(InSceneOutliner, InSpecifiedWorldToDisplay, bInHideComponents, bInHideLevelInstanceHierarchy, bInHideUnloadedActors, bInHideEmptyFolders)`

#### class `FObjectMixerOutlinerMode`  
`class FObjectMixerOutlinerMode : public FActorMode`  
_L163-412_
- inherits: `FActorMode`
- L173 _public prototype_ `FObjectMixerOutlinerMode(const FObjectMixerOutlinerModeParams& Params, const TSharedRef<FObjectMixerEditorList> InListModel);`
- L174 _public prototype_ `virtual ~FObjectMixerOutlinerMode();`
- L176 _public function_ `TWeakPtr<FObjectMixerEditorList> GetListModelPtr() const`
- L181 _public function_ `SSceneOutliner* GetSceneOutliner() const`
- L189 _public prototype_ `EObjectMixerTreeViewMode GetTreeViewMode() const;` — Determines the style of the tree (flat list or hierarchy)
- L193 _public prototype_ `void SetTreeViewMode(EObjectMixerTreeViewMode InViewMode);` — Determine the style of the tree (flat list or hierarchy)
- L195 _public prototype_ `UWorld* GetRepresentingWorld();`
- L198 _public function_ `virtual bool IsInteractive() const override` — Begin ISceneOutlinerMode Interface
- L199 _public prototype_ `virtual TUniquePtr<ISceneOutlinerHierarchy> CreateHierarchy() override;`
- L200 _public prototype_ `virtual void Rebuild() override;`
- L201 _public prototype_ `virtual int32 GetTypeSortPriority(const ISceneOutlinerTreeItem& Item) const override;`
- L202 _public prototype_ `virtual FCreateSceneOutlinerMode CreateFolderPickerMode(const FFolder::FRootObject& InRootObject = FFolder::GetInvalidRootObject()) const override;`
- L203 _public prototype_ `virtual void CreateViewContent(FMenuBuilder& MenuBuilder) override;`
- L204 _public prototype_ `virtual TSharedPtr<FDragDropOperation> CreateDragDropOperation(const FPointerEvent& MouseEvent, const TArray<FSceneOutlinerTreeItemPtr>& InTreeItems) const override;`
- L205 _public prototype_ `virtual bool ParseDragDrop(FSceneOutlinerDragDropPayload& OutPayload, const FDragDropOperation& Operation) const override;`
- L206 _public prototype_ `virtual FSceneOutlinerDragValidationInfo ValidateDrop(const ISceneOutlinerTreeItem& DropTarget, const FSceneOutlinerDragDropPayload& Payload) const override;`
- L207 _public prototype_ `virtual TSharedPtr<SWidget> CreateContextMenu() override;`
- L208 _public prototype_ `virtual void OnItemAdded(FSceneOutlinerTreeItemPtr Item) override;`
- L209 _public prototype_ `virtual void OnItemRemoved(FSceneOutlinerTreeItemPtr Item) override;`
- L210 _public prototype_ `virtual void OnItemSelectionChanged(FSceneOutlinerTreeItemPtr Item, ESelectInfo::Type SelectionType, const FSceneOutlinerItemSelection& Selection) override;`
- L211 _public prototype_ `virtual void OnItemDoubleClick(FSceneOutlinerTreeItemPtr Item) override;`
- L212 _public prototype_ `virtual void OnFilterTextCommited(FSceneOutlinerItemSelection& Selection, ETextCommit::Type CommitType) override;`
- L213 _public prototype_ `virtual void OnItemPassesFilters(const ISceneOutlinerTreeItem& Item) override;`
- L214 _public prototype_ `virtual FReply OnKeyDown(const FKeyEvent& InKeyEvent) override;`
- L215 _public prototype_ `virtual void OnDuplicateSelected() override;`
- L216 _public prototype_ `virtual void OnDrop(ISceneOutlinerTreeItem& DropTarget, const FSceneOutlinerDragDropPayload& Payload, const FSceneOutlinerDragValidationInfo& ValidationInfo) const override;`
- L217 _public prototype_ `virtual bool CanRenameItem(const ISceneOutlinerTreeItem& Item) const override;`
- L218 _public prototype_ `virtual FText GetStatusText() const override;`
- L219 _public prototype_ `virtual FSlateColor GetStatusTextColor() const override;`
- L220 _public function_ `virtual ESelectionMode::Type GetSelectionMode() const override`
- L221 _public function_ `virtual bool SupportsKeyboardFocus() const override`
- L222 _public function_ `virtual bool ShouldShowFolders() const override`
- L223 _public function_ `virtual bool SupportsCreateNewFolder() const override`
- L224 _public function_ `virtual bool ShowStatusBar() const override`
- L225 _public function_ `virtual bool ShowViewButton() const override`
- L226 _public function_ `virtual bool ShowFilterOptions() const override`
- L227 _public prototype_ `virtual bool CanDelete() const override;`
- L228 _public prototype_ `virtual bool CanRename() const override;`
- L229 _public prototype_ `virtual bool CanCut() const override;`
- L230 _public prototype_ `virtual bool CanCopy() const override;`
- L231 _public prototype_ `virtual bool CanPaste() const override;`
- L232 _public function_ `virtual bool CanSupportDragAndDrop() const override`
- L233 _public function_ `virtual bool CanCustomizeToolbar() const override`
- L234 _public prototype_ `virtual bool HasErrors() const override;`
- L235 _public prototype_ `virtual FText GetErrorsText() const override;`
- L236 _public prototype_ `virtual void RepairErrors() const override;`
- L237 _public prototype_ `virtual FFolder CreateNewFolder() override;`
- L238 _public prototype_ `virtual FFolder GetFolder(const FFolder& ParentPath, const FName& LeafName) override;`
- L239 _public prototype_ `virtual bool CreateFolder(const FFolder& NewFolder) override;`
- L240 _public prototype_ `virtual bool ReparentItemToFolder(const FFolder& FolderPath, const FSceneOutlinerTreeItemPtr& Item) override;`
- L241 _public prototype_ `virtual void SelectFoldersDescendants(const TArray<FFolderTreeItem*>& FolderItems, bool bSelectImmediateChildrenOnly) override;`
- L242 _public prototype_ `virtual void PinItems(const TArray<FSceneOutlinerTreeItemPtr>& InItems) override;`
- L243 _public prototype_ `virtual void UnpinItems(const TArray<FSceneOutlinerTreeItemPtr>& InItems) override;`
- L244 _public prototype_ `virtual bool CanPinItems(const TArray<FSceneOutlinerTreeItemPtr>& InItems) const override;`
- L245 _public prototype_ `virtual bool CanUnpinItems(const TArray<FSceneOutlinerTreeItemPtr>& InItems) const override;`
- L246 _public prototype_ `virtual void SynchronizeSelection() override;`
- L252 _public prototype_ `void OnComponentsUpdated();` — Called by the engine when a component is updated
- L254 _public prototype_ `void OnLevelActorDeleted(AActor* Actor);` — Called by the engine when an actor is deleted
- L257 _public prototype_ `void OnSelectUnloadedActors(const TArray<FGuid>& ActorGuids);` — Called by the editor to allow selection of unloaded actors
- L260 _public prototype_ `void OnActorDescInstanceRemoved(FWorldPartitionActorDescInstance* InActorDescInstance);` — Called when an actor desc instance is removed
- L263 _public function_ `void OnActorDescRemoved(FWorldPartitionActorDesc* InActorDesc)` — `UE_DEPRECATED(5.4, "Use OnActorDescInstanceRemoved instead")`
- L266 _public prototype_ `void OnEditCutActorsBegin();` — Called by engine when edit cut actors begins
- L269 _public prototype_ `void OnEditCutActorsEnd();` — Called by engine when edit cut actors ends
- L272 _public prototype_ `void OnEditCopyActorsBegin();` — Called by engine when edit copy actors begins
- L275 _public prototype_ `void OnEditCopyActorsEnd();` — Called by engine when edit copy actors ends
- L278 _public prototype_ `void OnEditPasteActorsBegin();` — Called by engine when edit paste actors begins
- L281 _public prototype_ `void OnEditPasteActorsEnd();` — Called by engine when edit paste actors ends
- L284 _public prototype_ `void OnDuplicateActorsBegin();` — Called by engine when edit duplicate actors begins
- L287 _public prototype_ `void OnDuplicateActorsEnd();` — Called by engine when edit duplicate actors ends
- L290 _public prototype_ `void OnDeleteActorsBegin();` — Called by engine when edit delete actors begins
- L293 _public prototype_ `void OnDeleteActorsEnd();` — Called by engine when edit delete actors ends
- L296 _public prototype_ `virtual bool CompareItemWithClassName(SceneOutliner::FilterBarType InItem, const TSet<FTopLevelAssetPath>&) const override;` — Function called by the Outliner Filter Bar to compare an item with Type Filters
- L299 _public prototype_ `bool ShouldAllowHybridRows() const;` — Check whether hybrid rows are allowed for the associated object list
- L305 _protected prototype_ `void OnMapChange(uint32 MapFlags);`
- L306 _protected prototype_ `void OnNewCurrentLevel();`
- L308 _protected prototype_ `void OnEditorSelectionChanged();`
- L309 _protected prototype_ `void OnActorLabelChanged(AActor* ChangedActor);`
- L310 _protected prototype_ `void OnObjectsReplaced(const TMap<UObject*, UObject*>& ReplacementMap);`
- L311 _protected prototype_ `void OnLevelActorRequestsRename(const AActor* Actor);`
- L312 _protected prototype_ `void OnPostLoadMapWithWorld(UWorld* World);`
- L314 _protected prototype_ `bool ShouldSyncSelectionToEditor();`
- L315 _protected prototype_ `bool ShouldSyncSelectionFromEditor();`
- L316 _protected prototype_ `void SynchronizeAllSelectionsToEditor();`
- L317 _protected prototype_ `bool HasActorSelectionChanged(TArray<AActor*>& OutSelectedActors, bool& bOutAreAnyInPIE);`
- L318 _protected prototype_ `bool HasComponentSelectionChanged(TArray<UActorComponent*>& OutSelectedComponents, bool& bOutAreAnyInPIE);`
- L319 _protected prototype_ `void SelectActorsInEditor(const TArray<AActor*>& InSelectedActors, bool bShouldSelect, bool bSelectEvenIfHidden);`
- L320 _protected prototype_ `void SelectComponentsInEditor(const TArray<UActorComponent*>& InSelectedComponents, bool bShouldSelect, bool bSelectEvenIfHidden);`
- L321 _protected prototype_ `void SelectSubObjectsInEditor(const TArray<UObject*>& InSelectedSubObjects, bool bShouldSelect, bool bSelectEvenIfHidden);`
- L322 _protected prototype_ `void SelectActorsInMixer(const TArray<AActor*>& InSelectedActors, bool bShouldSelect, bool bSelectEvenIfHidden);`
- L323 _protected prototype_ `void SelectComponentsInMixer(const TArray<UActorComponent*>& InSelectedComponents, bool bShouldSelect, bool bSelectEvenIfHidden);`
- L326 _protected prototype_ `TArray<AActor*> GetSelectedActorsInEditor() const;` — Get the list of actors selected in the editor
- L329 _protected prototype_ `TArray<UActorComponent*> GetSelectedComponentsInEditor() const;` — Get the list of components selected in the editor
- L332 _protected prototype_ `TArray<UObject*> GetSelectedSubObjectsInEditor() const;` — Gets the list of actor sub-objects that are selected in the editor.
- L335 _protected prototype_ `bool GetIsObjectOfFilteredClass(const UObject* Object) const;` — Check if an object is a member of one of the classes our list model is filtered to
- L338 _protected prototype_ `TSharedPtr<SWidget> BuildContextMenu();` — Build and up the context menu
- L340 _protected prototype_ `static void RegisterContextMenu();` — Register the context menu with the engine
- L341 _protected prototype_ `bool CanPasteFoldersOnlyFromClipboard() const;`
- L343 _protected prototype_ `bool GetFolderNamesFromPayload(const FSceneOutlinerDragDropPayload& InPayload, TArray<FName>& OutFolders, FFolder::FRootObject& OutCommonRootObject) const;`
- L344 _protected prototype_ `FFolder GetWorldDefaultRootFolder() const;`
- L347 _protected prototype_ `void SynchronizeComponentAndActorSelection();` — Synchronize both the actor and component selection with the editor, with components taking priority over actors
- L348 _protected prototype_ `void SynchronizeSelectedActorDescs();`
- L351 _protected prototype_ `void SynchronizeSubObjectSelection();` — Synchronizes the object mixer's selection with any sub-objects selected elsewhere in the editor
- L353 _protected prototype_ `void OnActorEditorContextSubsystemChanged();`
- L356 _protected prototype_ `static TSharedRef<FSceneOutlinerFilter> CreateShowOnlySelectedActorsFilter();` — Filter factories
- L357 _protected prototype_ `static TSharedRef<FSceneOutlinerFilter> CreateHideTemporaryActorsFilter();`
- L358 _protected prototype_ `static TSharedRef<FSceneOutlinerFilter> CreateIsInCurrentLevelFilter();`
- L359 _protected prototype_ `static TSharedRef<FSceneOutlinerFilter> CreateIsInCurrentDataLayersFilter();`
- L360 _protected prototype_ `static TSharedRef<FSceneOutlinerFilter> CreateHideComponentsFilter();`
- L361 _protected prototype_ `static TSharedRef<FSceneOutlinerFilter> CreateHideLevelInstancesFilter();`
- L362 _protected prototype_ `static TSharedRef<FSceneOutlinerFilter> CreateHideUnloadedActorsFilter();`
- L363 _protected prototype_ `static TSharedRef<FSceneOutlinerFilter> CreateHideEmptyFoldersFilter();`
- L364 _protected prototype_ `TSharedRef<FSceneOutlinerFilter> CreateIsInCurrentContentBundleFilter();`
- L367 _protected prototype_ `void OnToggleAlwaysFrameSelection();` — Functions to expose selection framing to the UI
- L368 _protected prototype_ `bool ShouldAlwaysFrameSelection();`
- L375 _protected prototype_ `FObjectMixerOutlinerModeConfig* GetMutableConfig() const;` — Get a mutable version of the ActorBrowser config for setting values. @returns		The config for this ActorBrowser. @note		If OutlinerIdentifier is not set for this outliner, it is not possible to store settings.
- L382 _protected prototype_ `const FObjectMixerOutlinerModeConfig* GetConstConfig() const;` — Get a const version of the ActorBrowser config for getting values. @returns		The config for this ActorBrowser. @note		If OutlinerIdentifier is not set for this outliner, it is not possible to store settings.
- L385 _protected prototype_ `void SaveConfig();` — Save the config for this ActorBrowser
- L387 _protected member_ `IWorldPartitionEditorModule* WorldPartitionEditorModule;`
- L389 _protected member_ `uint32 FilteredActorCount = 0;` — Number of actors (including unloaded) which have passed through the filters
- L391 _protected member_ `uint32 FilteredUnloadedActorCount = 0;` — Number of unloaded actors which have passed through all the filters
- L393 _protected member_ `TSet<FWorldPartitionHandle> ApplicableUnloadedActors;` — List of unloaded actors which passed through the regular filters and may or may not have passed the search filter
- L395 _protected member_ `TSet<TWeakObjectPtr<AActor>> ApplicableActors;` — List of actors which passed the regular filters and may or may not have passed the search filter
- L397 _protected member_ `bool bRepresentingWorldGameWorld = false;`
- L398 _protected member_ `bool bRepresentingWorldPartitionedWorld = false;`
- L400 _protected member_ `TWeakPtr<FObjectMixerEditorList> ListModelPtr;`
- L402 _protected member_ `TArray<FFilterClassSelectionInfo> FilterClassSelectionInfos;`
- L403 _protected prototype_ `TSharedRef<SWidget> OnGenerateFilterClassMenu();`
- L407 _protected member_ `bool bShouldTemporarilyForceSelectionSyncFromEditor = false;`
- L408 _protected member_ `bool bShouldTemporarilyForceSelectionSyncToEditor = false;`
- L411 _protected member_ `TArray<FSceneOutlinerTreeItemID> SelectedIDs;` — The last selected tree item IDs, stored here so we can maintain the selection across refreshes when not synced with the editor.

#### struct `FObjectMixerOutlinerMode::FFilterClassSelectionInfo`  
`struct FFilterClassSelectionInfo`  
_L167-171_
- L169 _public member_ `UClass* Class;`
- L170 _public member_ `bool bIsUserSelected;`

#### Free symbols / members of external scopes

- L16 _macro_ `#define UE_API OBJECTMIXEREDITOR_API`
- L22 _namespace_ `namespace ObjectMixerOutliner`

### `Plugins/Editor/ObjectMixer/ObjectMixer/Source/ObjectMixer/Public/Views/List/Modes/OutlinerColumns/ObjectMixerOutlinerColumns.h` (Public)


#### class `FObjectMixerOutlinerVisibilityColumn`  
`class FObjectMixerOutlinerVisibilityColumn : public FSceneOutlinerGutter`  
_L15-44_
- inherits: `FSceneOutlinerGutter`
- L18 _public function_ `FObjectMixerOutlinerVisibilityColumn(ISceneOutliner& SceneOutliner) : FSceneOutlinerGutter(SceneOutliner)`
- L30 _public prototype_ `virtual ~FObjectMixerOutlinerVisibilityColumn() override = default;`
- L34 _public prototype_ `virtual const TSharedRef<SWidget> ConstructRowWidget(FSceneOutlinerTreeItemRef TreeItem, const STableRow<FSceneOutlinerTreeItemPtr>& Row) override;`
- L40 _protected member_ `const FSlateBrush* VisibleHoveredBrush = nullptr;`
- L41 _protected member_ `const FSlateBrush* VisibleNotHoveredBrush = nullptr;`
- L42 _protected member_ `const FSlateBrush* NotVisibleHoveredBrush = nullptr;`
- L43 _protected member_ `const FSlateBrush* NotVisibleNotHoveredBrush = nullptr;`

#### class `FObjectMixerOutlinerSoloColumn`  
`class FObjectMixerOutlinerSoloColumn : public ISceneOutlinerColumn`  
_L46-76_
- inherits: `ISceneOutlinerColumn`
- L49 _public function_ `FObjectMixerOutlinerSoloColumn(ISceneOutliner& SceneOutliner)`
- L53 _public prototype_ `virtual ~FObjectMixerOutlinerSoloColumn() override = default;`
- L54 _public prototype_ `static FName GetID();`
- L56 _public prototype_ `static FText GetLocalizedColumnName();`
- L60 _public function_ `virtual FName GetColumnID() override`
- L61 _public prototype_ `virtual SHeaderRow::FColumn::FArguments ConstructHeaderRowColumn() override;`
- L62 _public prototype_ `virtual const TSharedRef<SWidget> ConstructRowWidget(FSceneOutlinerTreeItemRef TreeItem, const STableRow<FSceneOutlinerTreeItemPtr>& Row) override;`
- L63 _public function_ `virtual bool SupportsSorting() const override`
- L64 _public prototype_ `virtual void SortItems(TArray<FSceneOutlinerTreeItemPtr>& OutItems, const EColumnSortMode::Type SortMode) const override;`
- L70 _protected prototype_ `FSlateColor GetForegroundColor( FSceneOutlinerTreeItemRef TreeItem, const STableRow<FSceneOutlinerTreeItemPtr>* Row) const;`
- L73 _protected prototype_ `void OnClickSoloIcon(const FSceneOutlinerTreeItemRef RowPtr);`
- L75 _protected member_ `TWeakPtr<ISceneOutliner> WeakOutliner = nullptr;`

#### class `FObjectMixerOutlinerPropertyColumn`  
`class FObjectMixerOutlinerPropertyColumn : public ISceneOutlinerColumn`  
_L78-106_
- inherits: `ISceneOutlinerColumn`
- L81 _public function_ `FObjectMixerOutlinerPropertyColumn(ISceneOutliner& SceneOutliner, FProperty* InProperty)`
- L86 _public prototype_ `virtual ~FObjectMixerOutlinerPropertyColumn() override = default;`
- L87 _public prototype_ `static FName GetID(const FProperty* InProperty);`
- L89 _public prototype_ `static FText GetDisplayNameText(const FProperty* InProperty);`
- L93 _public function_ `virtual FName GetColumnID() override`
- L94 _public prototype_ `virtual SHeaderRow::FColumn::FArguments ConstructHeaderRowColumn() override;`
- L95 _public prototype_ `virtual const TSharedRef<SWidget> ConstructRowWidget(FSceneOutlinerTreeItemRef TreeItem, const STableRow<FSceneOutlinerTreeItemPtr>& Row) override;`
- L96 _public function_ `virtual bool SupportsSorting() const override`
- L102 _protected prototype_ `void OnPropertyChanged(const FPropertyChangedEvent& Event, TWeakPtr<ISceneOutlinerTreeItem> WeakRowPtr) const;`
- L104 _protected member_ `FProperty* Property = nullptr;`
- L105 _protected member_ `TWeakPtr<ISceneOutliner> WeakOutliner = nullptr;`

#### class `FObjectMixerOutlinerTextInfoColumn`  
`class FObjectMixerOutlinerTextInfoColumn : public FTextInfoColumn`  
_L108-116_
- inherits: `FTextInfoColumn`
- L111 _public function_ `FObjectMixerOutlinerTextInfoColumn( ISceneOutliner& SceneOutliner, const FName InColumnName, const FGetTextForItem& InGetTextForItem, const FText InColumnToolTip) : FTextInfoColumn(SceneOutliner, InColumnName, InGetTextForItem, InColumnToolTip)`

### `Plugins/Editor/ObjectMixer/ObjectMixer/Source/ObjectMixer/Public/Views/List/Modes/SFilterClassMenuItem.h` (Public)


#### struct `FAssetClassMap`  
`struct FAssetClassMap`  
_L15-24_
- L17 _public member_ `TObjectPtr<UClass> Class = nullptr;`
- L18 _public member_ `FAssetData AssetData;`
- L20 _public function_ `bool operator==(const FAssetClassMap& Other) const`

#### class `SFilterClassMenuItem`  
`class SFilterClassMenuItem : public SCompoundWidget`  
_L26-127_
- inherits: `SCompoundWidget`
- L30 _public function_ `SLATE_BEGIN_ARGS(SFilterClassMenuItem)`
- L33 _public function_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, FAssetClassMap AssetClassMap, const bool bIsDefaultClass, TArray<FObjectMixerOutlinerMode::FFilterClassSelectionInfo>& FilterClassSelectionInfos, const FText TooltipText)`

#### Free symbols / members of external scopes

- L64 _function_ `` (scope `SFilterClassMenuItem::SLATE_END_ARGS`)
- L68 _function_ `` (scope `SFilterClassMenuItem::SLATE_END_ARGS::__anona37208040102`)
- L82 _function_ `` (scope `SFilterClassMenuItem::SLATE_END_ARGS::__anona37208040302`)

### `Plugins/Editor/ObjectMixer/ObjectMixer/Source/ObjectMixer/Public/Views/List/ObjectMixerEditorList.h` (Public)


#### class `FObjectMixerEditorList`  
`class FObjectMixerEditorList : public TSharedFromThis<FObjectMixerEditorList>, public FGCObject`  
_L21-250_
- inherits: `TSharedFromThis<FObjectMixerEditorList>,FGCObject`
- L25 _public prototype_ `FObjectMixerEditorList(const FName InModuleName, TSharedPtr<IObjectMixerSelectionInterface> InSelectionInterface = nullptr);`
- L27 _public prototype_ `virtual ~FObjectMixerEditorList();`
- L29 _public prototype_ `void Initialize();`
- L31 _public prototype_ `void RegisterAndMapContextMenuCommands();`
- L34 _public prototype_ `TSharedRef<SWidget> GetOrCreateWidget();` — Creates a new widget only if one does not already exist. Otherwise returns the existing widget.
- L37 _public prototype_ `TSharedRef<SWidget> CreateWidget();` — Creates a new widget, replacing the existing one's pointer. Not useful to call alone, use RequestRegenerateListWidget
- L40 _public prototype_ `void RequestRegenerateListWidget();` — Calls back to the module to replace the widget in the dock tab. Call when columns or the object filters have changed.
- L43 _public prototype_ `void RequestRebuildList() const;` — Rebuild the list items and refresh the list. Call when adding or removing items.
- L49 _public prototype_ `void RefreshList() const;` — Refresh list filters and sorting. Useful for when the list state has gone stale but the variable count has not changed.
- L52 _public function_ `TSharedPtr<IObjectMixerSelectionInterface> GetSelectionInterface() const` — Get the selection interface used to synchronize this with the rest of the editor
- L54 _public prototype_ `void BuildPerformanceCache();`
- L56 _public prototype_ `bool ShouldShowTransientObjects() const;`
- L59 _public prototype_ `void OnRenameCommand();` — Called when the Rename command is executed from the UI or hotkey.
- L61 _public prototype_ `void RebuildCollectionSelector();`
- L63 _public prototype_ `void SetDefaultFilterClass(UClass* InNewClass);`
- L64 _public prototype_ `bool IsClassSelected(UClass* InClass) const;`
- L66 _public prototype_ `const TArray<TObjectPtr<UObjectMixerObjectFilter>>& GetObjectFilterInstances();`
- L68 _public prototype_ `const UObjectMixerObjectFilter* GetMainObjectFilterInstance();`
- L70 _public prototype_ `void CacheObjectFilterInstances();`
- L73 _public function_ `EObjectMixerTreeViewMode GetTreeViewMode()` — Get the style of the tree (flat list or hierarchy)
- L78 _public function_ `void SetTreeViewMode(EObjectMixerTreeViewMode InViewMode)` — Set the style of the tree (flat list or hierarchy)
- L88 _public prototype_ `TSet<UClass*> ForceGetObjectClassesToFilter();` — Force returns result from Filter->ForceGetObjectClassesToFilter. Generally, you want to get this from the public performance cache.
- L94 _public prototype_ `TSet<TSubclassOf<AActor>> ForceGetObjectClassesToPlace();` — Force returns result from Filter->ForceGetObjectClassesToPlace. Generally, you want to get this from the public performance cache.
- L96 _public function_ `const TArray<TSubclassOf<UObjectMixerObjectFilter>>& GetObjectFilterClasses() const`
- L101 _public prototype_ `void AddObjectFilterClass(UClass* InObjectFilterClass, const bool bShouldRebuild = true);`
- L103 _public prototype_ `void RemoveObjectFilterClass(UClass* InObjectFilterClass, const bool bCacheAndRebuild = true);`
- L105 _public function_ `void ResetObjectFilterClasses(const bool bCacheAndRebuild = true)`
- L115 _public function_ `void CacheAndRebuildFilters(const bool bShouldRegenerateWidget = false)`
- L129 _public function_ `FName GetModuleName() const` — Used as a way to differentiate different subclasses of the Object Mixer module
- L134 _public prototype_ `FObjectMixerEditorModule* GetModulePtr() const;`
- L139 _public prototype_ `UObjectMixerEditorSerializedData* GetSerializedData() const;` — Get a pointer to the UObjectMixerEditorSerializedData object along with the name of the filter represented by this ListModel instance.
- L140 _public prototype_ `bool RequestAddObjectsToCollection(const FName& CollectionName, const TSet<FSoftObjectPath>& ObjectsToAdd) const;`
- L141 _public prototype_ `bool RequestRemoveObjectsFromCollection(const FName& CollectionName, const TSet<FSoftObjectPath>& ObjectsToRemove) const;`
- L142 _public prototype_ `bool RequestRemoveCollection(const FName& CollectionName) const;`
- L143 _public prototype_ `bool RequestDuplicateCollection(const FName& CollectionToDuplicateName, FName& DesiredDuplicateName) const;`
- L144 _public prototype_ `bool RequestReorderCollection(const FName& CollectionToMoveName, const FName& CollectionInsertBeforeName) const;`
- L145 _public prototype_ `bool RequestRenameCollection(const FName& CollectionNameToRename, const FName& NewCollectionName) const;`
- L146 _public prototype_ `bool DoesCollectionExist(const FName& CollectionName) const;`
- L147 _public prototype_ `bool IsObjectInCollection(const FName& CollectionName, const FSoftObjectPath& InObject) const;`
- L148 _public prototype_ `TSet<FName> GetCollectionsForObject(const FSoftObjectPath& InObject) const;`
- L149 _public prototype_ `TArray<FName> GetAllCollectionNames() const;`
- L155 _public prototype_ `const TSubclassOf<UObjectMixerObjectFilter>& GetDefaultFilterClass() const;` — This is the filter class used to initialize the ListModel. This filter class cannot be turned off by the end user.
- L157 _public prototype_ `void OnPostFilterChange();`
- L159 _public member_ `FOnPreFilterChange OnPreFilterChangeDelegate;`
- L160 _public member_ `FOnPostFilterChange OnPostFilterChangeDelegate;`
- L162 _public member_ `TSharedPtr<FUICommandList> ObjectMixerElementEditCommands;`
- L163 _public member_ `TSharedPtr<FUICommandList> ObjectMixerFolderEditCommands;`
- L165 _public prototype_ `void FlushWidget();`
- L167 _public prototype_ `[[nodiscard]] TArray<TSharedPtr<ISceneOutlinerTreeItem>> GetSelectedTreeViewItems() const;`
- L168 _public prototype_ `int32 GetSelectedTreeViewItemCount() const;`
- L170 _public prototype_ `TSet<TSharedPtr<ISceneOutlinerTreeItem>> GetSoloRows() const;`
- L171 _public prototype_ `void ClearSoloRows();`
- L174 _public prototype_ `bool IsListInSoloState() const;` — Returns true if at least one row is set to Solo.
- L180 _public prototype_ `void EvaluateAndSetEditorVisibilityPerRow();` — Determines whether rows' objects should be temporarily hidden in editor based on each row's visibility rules, then sets each object's visibility in editor.
- L183 _public prototype_ `[[nodiscard]] const TSet<FName>& GetSelectedCollections() const;` — Represents the collections the user has selected in the UI. If empty, "All" is considered as selected.
- L184 _public prototype_ `[[nodiscard]] bool IsCollectionSelected(const FName& CollectionName) const;`
- L185 _public prototype_ `void SetSelectedCollections(const TSet<FName> InSelectedCollections);`
- L186 _public prototype_ `void SetCollectionSelected(const FName& CollectionName, const bool bNewSelected);`
- L189 _public member_ `TSet<UClass*> ObjectClassesToFilterCache;` — Performance cache
- L190 _public member_ `TSet<FName> ColumnsToShowByDefaultCache;`
- L191 _public member_ `TSet<FName> ColumnsToExcludeCache;`
- L192 _public member_ `TSet<FName> ForceAddedColumnsCache;`
- L193 _public member_ `EObjectMixerInheritanceInclusionOptions PropertyInheritanceInclusionOptionsCache = EObjectMixerInheritanceInclusionOptions::None;`
- L194 _public member_ `bool bShouldIncludeUnsupportedPropertiesCache = false;`
- L195 _public member_ `bool bShouldShowTransientObjectsCache = false;`
- L200 _protected prototype_ `virtual void BindRefreshDelegates();` — Bind delegates to refresh the list when editor state changes.
- L203 _protected prototype_ `virtual void UnbindRefreshDelegates();` — Unbind delegates to refresh the list when editor state changes.
- L206 _protected prototype_ `TSet<FName> GetPropertiesThatRequireRefresh();` — If a property is changed that has a name found in this set, the list will be refreshed.
- L208 _protected function_ `virtual void AddReferencedObjects( FReferenceCollector& Collector ) override`
- L212 _protected function_ `virtual FString GetReferencerName() const override`
- L218 _protected member_ `TSet<FName> SelectedCollections;` — Represents the collections the user has selected in the UI. If empty, "All" is considered as selected.
- L220 _protected member_ `TSharedPtr<SObjectMixerEditorList> ListWidget;`
- L222 _protected member_ `TArray<TObjectPtr<UObjectMixerObjectFilter>> ObjectFilterInstances;`
- L228 _protected member_ `TArray<TSubclassOf<UObjectMixerObjectFilter>> ObjectFilterClasses;` — The classes used to generate property edit columns. Using an array rather than a set because the first class is considered the 'Main' class which determines some filter behaviours.
- L234 _protected member_ `TSubclassOf<UObjectMixerObjectFilter> DefaultFilterClass;` — If set, this is the filter class used to initialize the ListModel. This filter class cannot be turned off by the end user.
- L239 _protected member_ `EObjectMixerTreeViewMode TreeViewMode = EObjectMixerTreeViewMode::Folders;` — Determines the style of the tree (flat list or hierarchy)
- L241 _protected member_ `FName ModuleName = NAME_None;`
- L243 _protected member_ `FDelegateHandle OnBlueprintFilterCompiledHandle;`
- L246 _protected member_ `TSharedPtr<IObjectMixerSelectionInterface> SelectionInterface;` — Interface used to synchronize selection with another part of the editor
- L249 _protected member_ `TSet<FDelegateHandle> DelegateHandles;` — Handles for delegates registered to refresh the list

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API OBJECTMIXEREDITOR_API`
- L17 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnPreFilterChange) DECLARE_MULTICAST_DELEGATE(FOnPostFilterChange) class FObjectMixerEditorList : public TSharedFromThis<FObjectMixerEditorList>, public FGCObject { public: FObjectMixerEditorList(const FName InModuleName, TSharedPtr<IObjectMixerSelectionInterface> InSelectionInterface = nullptr); virtual ~FObjectMixerEditorList(); void Initialize(); void RegisterAndMapContextMenuCommands(); TSharedRef<SWidget> GetOrCreateWidget(); TSharedRef<SWidget> CreateWidget(); void RequestRegenerateListWidget(); void RequestRebuildList() const; void RefreshList() const; TSharedPtr<IObjectMixerSelectionInterface> GetSelectionInterface() const { return SelectionInterface; } void BuildPerformanceCache(); bool ShouldShowTransientObjects() const;`
- L18 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnPostFilterChange) class FObjectMixerEditorList : public TSharedFromThis<FObjectMixerEditorList>, public FGCObject { public: FObjectMixerEditorList(const FName InModuleName, TSharedPtr<IObjectMixerSelectionInterface> InSelectionInterface = nullptr); virtual ~FObjectMixerEditorList(); void Initialize(); void RegisterAndMapContextMenuCommands(); TSharedRef<SWidget> GetOrCreateWidget(); TSharedRef<SWidget> CreateWidget(); void RequestRegenerateListWidget(); void RequestRebuildList() const; void RefreshList() const; TSharedPtr<IObjectMixerSelectionInterface> GetSelectionInterface() const { return SelectionInterface; } void BuildPerformanceCache(); bool ShouldShowTransientObjects() const;`

### `Plugins/Editor/ObjectMixer/ObjectMixer/Source/ObjectMixer/Public/Views/List/ObjectMixerEditorListRowData.h` (Public)


#### struct `FObjectMixerEditorListRowData`  
`struct FObjectMixerEditorListRowData`  
_L16-149_
- desc: Defines data carried by each row type.
- L47 _public function_ `friend uint32 GetTypeHash (const FPropertyPropagationInfo& Other)`
- L53 _public function_ `FObjectMixerEditorListRowData( SSceneOutliner* InSceneOutliner, const FText& InDisplayNameOverride = FText::GetEmpty()) : DisplayNameOverride(InDisplayNameOverride)`
- L63 _public prototype_ `FObjectMixerEditorListRowData() = default;`
- L65 _public prototype_ `~FObjectMixerEditorListRowData() = default;`
- L67 _public function_ `bool IsValid() const`
- L72 _public prototype_ `const TArray<TObjectPtr<UObjectMixerObjectFilter>>& GetObjectFilterInstances() const;`
- L74 _public prototype_ `const UObjectMixerObjectFilter* GetMainObjectFilterInstance() const;`
- L76 _public prototype_ `[[nodiscard]] bool GetIsTreeViewItemExpanded(const TSharedRef<ISceneOutlinerTreeItem> InRow);`
- L77 _public prototype_ `void SetIsTreeViewItemExpanded(const TSharedRef<ISceneOutlinerTreeItem> InRow, const bool bNewExpanded);`
- L79 _public prototype_ `[[nodiscard]] bool GetIsSelected(const TSharedRef<ISceneOutlinerTreeItem> InRow);`
- L80 _public prototype_ `void SetIsSelected(const TSharedRef<ISceneOutlinerTreeItem> InRow, const bool bNewSelected);`
- L82 _public prototype_ `[[nodiscard]] bool HasAtLeastOneChildThatIsNotSolo( const TSharedRef<ISceneOutlinerTreeItem> InRow, const bool bRecursive = true) const;`
- L85 _public function_ `[[nodiscard]] const FText& GetDisplayNameOverride() const`
- L90 _public function_ `void SetDisplayNameOverride(const FText& InDisplayNameOverride)`
- L95 _public prototype_ `[[nodiscard]] TWeakPtr<SObjectMixerEditorList> GetListView() const;`
- L97 _public prototype_ `[[nodiscard]] TArray<TSharedPtr<ISceneOutlinerTreeItem>> GetSelectedTreeViewItems() const;`
- L99 _public prototype_ `void OnChangeVisibility(const FSceneOutlinerTreeItemRef TreeItem, const bool bNewVisible);`
- L101 _public prototype_ `[[nodiscard]] const FTransientEditorVisibilityRules& GetVisibilityRules() const;`
- L102 _public prototype_ `void SetVisibilityRules(const FTransientEditorVisibilityRules& InVisibilityRules);`
- L104 _public prototype_ `bool IsUserSetHiddenInEditor() const;`
- L105 _public prototype_ `void SetUserHiddenInEditor(const bool bNewHidden);`
- L107 _public prototype_ `bool GetRowSoloState() const;`
- L108 _public prototype_ `void SetRowSoloState(const bool bNewSolo);`
- L110 _public prototype_ `void ClearSoloRows() const;`
- L112 _public function_ `bool GetIsHybridRow() const`
- L117 _public function_ `UActorComponent* GetHybridComponent() const`
- L123 _public function_ `void SetHybridComponent(UActorComponent* InHybridComponent)` — If this row represents an actor or other container and should show the data for a single child component, define it here.
- L131 _public prototype_ `bool PropagateChangesToSimilarSelectedRowProperties( const TSharedRef<ISceneOutlinerTreeItem> InRow, const FPropertyPropagationInfo PropertyPropagationInfo);` — Attempt to propagate a property's new value to other selected rows. @return Returns true if the property's handle was found or there is no work to do (i.e., no property name specified or this row is not selected)
- L134 _public member_ `TMap<FName, TWeakPtr<IPropertyHandle>> PropertyNamesToHandles;`
- L136 _public member_ `TWeakPtr<SSceneOutliner> SceneOutlinerPtr;`
- L139 _protected member_ `FTransientEditorVisibilityRules VisibilityRules;`
- L141 _protected member_ `FText DisplayNameOverride;`
- L148 _protected member_ `TSoftObjectPtr<UActorComponent> HybridComponentPath = nullptr;` — A breadcrumb trail to a single component that matches the selected Object Mixer Filters. For example, if your filter is looking for lights and you have an actor with a single light component, this will show the actor and component on the same line rather than requiring the user to unfold the actor row to see one component.

#### struct `FObjectMixerEditorListRowData::FTransientEditorVisibilityRules`  
`struct FTransientEditorVisibilityRules`  
_L18-32_
- L24 _public member_ `bool bShouldBeHiddenInEditor = false;` — If true, the user wants the row to be hidden temporarily in the editor. This is transient visibility like the eye icon in the Scene Outliner, not the bVisible or bHiddenInGame properties.
- L31 _public member_ `bool bShouldBeSolo = false;` — If true, the user wants the row to have solo visibility. Multiple rows at once can be set to solo. Solo rows' objects are exclusively visible, so all other objects found in the panel will be invisible while at least one row is in a solo state.

#### struct `FObjectMixerEditorListRowData::FPropertyPropagationInfo`  
`struct FPropertyPropagationInfo`  
_L34-51_
- L36 _public prototype_ `FPropertyPropagationInfo() = default;`
- L38 _public member_ `FSceneOutlinerTreeItemID RowIdentifier;`
- L39 _public member_ `FName PropertyName = NAME_None;`
- L40 _public member_ `EPropertyValueSetFlags::Type PropertyValueSetFlags = 0;`
- L42 _public function_ `bool operator==(const FPropertyPropagationInfo& Other) const`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API OBJECTMIXEREDITOR_API`

### `Plugins/Editor/ObjectMixer/ObjectMixer/Source/ObjectMixer/Public/Views/List/ObjectMixerUtils.h` (Public)


#### Free symbols / members of external scopes

- L22 _namespace_ `namespace FObjectMixerUtils`
- L24 _prototype_ `FObjectMixerEditorListRowFolder* AsFolderRow(TSharedPtr<ISceneOutlinerTreeItem> InTreeItem);` (scope `FObjectMixerUtils`)
- L25 _prototype_ `FObjectMixerEditorListRowActor* AsActorRow(TSharedPtr<ISceneOutlinerTreeItem> InTreeItem);` (scope `FObjectMixerUtils`)
- L26 _prototype_ `FObjectMixerEditorListRowComponent* AsComponentRow(TSharedPtr<ISceneOutlinerTreeItem> InTreeItem);` (scope `FObjectMixerUtils`)
- L27 _prototype_ `FObjectMixerEditorListRowUObject* AsObjectRow(TSharedPtr<ISceneOutlinerTreeItem> InTreeItem);` (scope `FObjectMixerUtils`)
- L29 _prototype_ `FObjectMixerEditorListRowData* GetRowData(TSharedPtr<ISceneOutlinerTreeItem> InTreeItem);` (scope `FObjectMixerUtils`)
- L31 _prototype_ `UObject* GetRowObject(TSharedPtr<ISceneOutlinerTreeItem> InTreeItem, const bool bGetHybridRowComponent = false);` (scope `FObjectMixerUtils`)
- L33 _prototype_ `[[nodiscard]] AActor* GetSelfOrOuterAsActor(TSharedPtr<ISceneOutlinerTreeItem> InTreeItem);` (scope `FObjectMixerUtils`)
- L35 _prototype_ `bool IsObjectRefInCollection(const FName& CollectionName, const UObject* Object, const TSharedPtr<FObjectMixerEditorList> ListModel);` (scope `FObjectMixerUtils`)
- L36 _prototype_ `bool IsObjectRefInCollection(const FName& CollectionName, TSharedPtr<ISceneOutlinerTreeItem> InTreeItem);` (scope `FObjectMixerUtils`)
- L38 _prototype_ `void SetChildRowsSelected( TSharedPtr<ISceneOutlinerTreeItem> InTreeItem, const bool bNewSelected, const bool bRecursive);` (scope `FObjectMixerUtils`)

### `Plugins/Editor/ObjectMixer/ObjectMixer/Source/ObjectMixer/Public/Views/List/RowTypes/ObjectMixerEditorListRowActor.h` (Public)


#### struct `FObjectMixerEditorListRowActor`  
`struct FObjectMixerEditorListRowActor : FActorTreeItem`  
_L13-41_
- inherits: `FActorTreeItem`
- L15 _public function_ `explicit FObjectMixerEditorListRowActor( AActor* InObject, SSceneOutliner* InSceneOutliner, const FText& InDisplayNameOverride = FText::GetEmpty(), AActor* InOverrideParent = nullptr) : FActorTreeItem(InObject) , OriginalObjectSoftPtr(InObject) , OverrideParent(InOverrideParent)`
- L28 _public member_ `FObjectMixerEditorListRowData RowData;`
- L31 _public member_ `TSoftObjectPtr<AActor> OriginalObjectSoftPtr;` — Used in scenarios where the original object may be reconstructed or trashed, such as when running a construction script.
- L34 _public member_ `TSoftObjectPtr<AActor> OverrideParent;` — If set, the row for this actor will be treated as the current row's parent in the hierarchy
- L37 _public member_ `static const FSceneOutlinerTreeItemType Type;` — Begin ISceneOutlinerTreeItem Implementation
- L38 _public prototype_ `virtual void OnVisibilityChanged(const bool bNewVisibility) override;`
- L39 _public prototype_ `virtual FSceneOutlinerTreeItemID GetID() const override;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API OBJECTMIXEREDITOR_API`

### `Plugins/Editor/ObjectMixer/ObjectMixer/Source/ObjectMixer/Public/Views/List/RowTypes/ObjectMixerEditorListRowComponent.h` (Public)


#### struct `FObjectMixerEditorListRowComponent`  
`struct FObjectMixerEditorListRowComponent : FComponentTreeItem`  
_L12-32_
- inherits: `FComponentTreeItem`
- L14 _public function_ `explicit FObjectMixerEditorListRowComponent( UActorComponent* InObject, SSceneOutliner* InSceneOutliner, const FText& InDisplayNameOverride = FText::GetEmpty()) : FComponentTreeItem(InObject) , OriginalObjectSoftPtr(InObject)`
- L24 _public member_ `FObjectMixerEditorListRowData RowData;`
- L27 _public member_ `TSoftObjectPtr<UActorComponent> OriginalObjectSoftPtr;` — Used in scenarios where the original object may be reconstructed or trashed, such as when running a construction script.
- L30 _public member_ `static const FSceneOutlinerTreeItemType Type;` — Begin ISceneOutlinerTreeItem Implementation

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API OBJECTMIXEREDITOR_API`

### `Plugins/Editor/ObjectMixer/ObjectMixer/Source/ObjectMixer/Public/Views/List/RowTypes/ObjectMixerEditorListRowContainer.h` (Public)


#### struct `FObjectMixerEditorListRowContainer`  
`struct FObjectMixerEditorListRowContainer : ISceneOutlinerTreeItem`  
_L10-43_
- inherits: `ISceneOutlinerTreeItem`
- desc: Object Mixer row that represents container properties such as arrays that contain subobjects
- L13 _public prototype_ `explicit FObjectMixerEditorListRowContainer(UObject* InPropertyOwner, FName InPropertyName, SSceneOutliner* InSceneOutliner);`
- L16 _public member_ `static const FSceneOutlinerTreeItemType Type;` — Begin ISceneOutlinerTreeItem Implementation
- L17 _public prototype_ `virtual FString GetDisplayString() const override;`
- L18 _public function_ `virtual bool CanInteract() const override`
- L19 _public function_ `virtual bool IsValid() const override`
- L20 _public function_ `virtual FSceneOutlinerTreeItemID GetID() const override`
- L21 _public prototype_ `virtual TSharedRef<SWidget> GenerateLabelWidget(ISceneOutliner& Outliner, const STableRow<FSceneOutlinerTreeItemPtr>& InRow) override;`
- L25 _public function_ `UObject* GetPropertyOwner() const` — Gets the object that owns the container property being represented by this row
- L28 _public function_ `const FProperty* GetContainerProperty() const` — Gets the FProperty being represented by this row
- L32 _public member_ `TAttribute<const FSlateBrush*> PropertyIconOverride;` — Optional icon to display in the list row; if not provided, a default icon will be used
- L36 _private member_ `TSoftObjectPtr<UObject> PropertyOwner;` — The explicit object whose container property is being represented by this list row
- L39 _private member_ `FProperty* Property = nullptr;` — The FProperty that is being represented by this list row
- L42 _private member_ `uint64 UniqueId = 0;` — The unique ID of this list row in the scene outliner

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API OBJECTMIXEREDITOR_API`

### `Plugins/Editor/ObjectMixer/ObjectMixer/Source/ObjectMixer/Public/Views/List/RowTypes/ObjectMixerEditorListRowFolder.h` (Public)


#### struct `FObjectMixerEditorListRowFolder`  
`struct FObjectMixerEditorListRowFolder : FActorFolderTreeItem`  
_L14-31_
- inherits: `FActorFolderTreeItem`
- L16 _public function_ `explicit FObjectMixerEditorListRowFolder( const FFolder InFolder, SSceneOutliner* InSceneOutliner, UWorld* World, const FText& InDisplayNameOverride = FText::GetEmpty()) : FActorFolderTreeItem(InFolder, World)`
- L25 _public member_ `FObjectMixerEditorListRowData RowData;`
- L28 _public member_ `static const FSceneOutlinerTreeItemType Type;` — Begin ISceneOutlinerTreeItem Implementation
- L29 _public prototype_ `virtual void OnVisibilityChanged(const bool bNewVisibility) override;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API OBJECTMIXEREDITOR_API`

### `Plugins/Editor/ObjectMixer/ObjectMixer/Source/ObjectMixer/Public/Views/List/RowTypes/ObjectMixerEditorListRowUObject.h` (Public)


#### struct `FObjectMixerEditorListRowUObject`  
`struct FObjectMixerEditorListRowUObject : ISceneOutlinerTreeItem`  
_L14-49_
- inherits: `ISceneOutlinerTreeItem`
- L16 _public function_ `explicit FObjectMixerEditorListRowUObject( UObject* InObject, SSceneOutliner* InSceneOutliner, const FText& InDisplayNameOverride = FText::GetEmpty()) : ISceneOutlinerTreeItem(Type) , ObjectSoftPtr(InObject) , ID(InObject)`
- L27 _public member_ `FObjectMixerEditorListRowData RowData;`
- L30 _public member_ `TSoftObjectPtr<UObject> ObjectSoftPtr;` — Used in scenarios where the original object may be reconstructed or trashed, such as when running a construction script.
- L33 _public member_ `const FObjectKey ID;` — Constant identifier for this tree item
- L36 _public member_ `FName ContainerProperty = NAME_None;` — If the UObject list row should be displayed as part of a container, this is the container's property name in this object's outer
- L39 _public member_ `bool bIncludeObjectStack = false;` — If true, the mixer displays rows for all of this object's parents up to its owning actor; otherwise, it is parented directly to its owning actor
- L42 _public member_ `static const FSceneOutlinerTreeItemType Type;` — Begin ISceneOutlinerTreeItem Implementation
- L43 _public prototype_ `virtual FString GetDisplayString() const override;`
- L44 _public function_ `virtual bool CanInteract() const override`
- L45 _public function_ `virtual bool IsValid() const override`
- L46 _public function_ `virtual FSceneOutlinerTreeItemID GetID() const override`
- L47 _public prototype_ `virtual TSharedRef<SWidget> GenerateLabelWidget(ISceneOutliner& Outliner, const STableRow<FSceneOutlinerTreeItemPtr>& InRow) override;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API OBJECTMIXEREDITOR_API`

### `Plugins/Editor/ObjectMixer/ObjectMixer/Source/ObjectMixer/Public/Views/List/SObjectMixerEditorList.h` (Public)


#### enum `EListViewColumnType`  
`enum class EListViewColumnType`  
_L24-28_
- reflection: `UENUM()`
- L26 _public enumerator_ `BuiltIn`
- L27 _public enumerator_ `PropertyGenerated`

#### struct `FObjectMixerSceneOutlinerColumnInfo`  
`struct FObjectMixerSceneOutlinerColumnInfo`  
_L31-68_
- reflection: `USTRUCT()`
- L36 _public member_ `FProperty* PropertyRef = nullptr;` — The pointer to the actual FProperty
- L40 _public member_ `FName PropertyName = NAME_None;` — `UPROPERTY()` — The FName of the property
- L44 _public member_ `FName ColumnID = NAME_None;` — `UPROPERTY()` — The column identifier for the property. Often this is teh same as PropertyName.
- L48 _public member_ `FText PropertyDisplayText = FText::GetEmpty();` — `UPROPERTY()` — What will be displayed in the column header unless another widget is defined.
- L52 _public member_ `EListViewColumnType PropertyType = EListViewColumnType::PropertyGenerated;` — `UPROPERTY()` — Is this a built-in column, a column displaying a property widget or something else?
- L59 _public member_ `FName PropertyCategoryName = NAME_None;` — `UPROPERTY()` — The category that holds the property. Used for sorting properties in the context menu, similar to the details view.
- L63 _public member_ `bool bCanBeHidden = true;` — `UPROPERTY()` — If true, this column can be enabled and disabled by the user.
- L67 _public member_ `bool bIsDesiredToBeShownByDefault = false;` — `UPROPERTY()` — If true, this column will be shown in a clean environment or when default properties are restored.

#### class `SObjectMixerEditorList`  
`class SObjectMixerEditorList : public SSceneOutliner`  
_L72-230_
- inherits: `SSceneOutliner`
- L76 _public prototype_ `DECLARE_EVENT(SObjectMixerEditorList, FSelectionSynchronizedEvent);`
- L79 _public member_ `static const FName ItemNameColumnName;` — Columns
- L80 _public member_ `static const FName EditorVisibilityColumnName;`
- L81 _public member_ `static const FName EditorVisibilitySoloColumnName;`
- L83 _public prototype_ `void Construct(const FArguments& InArgs, TSharedRef<FObjectMixerEditorList> ListModel);`
- L87 _public prototype_ `virtual FReply OnKeyDown( const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent ) override;`
- L92 _public prototype_ `EObjectMixerTreeViewMode GetTreeViewMode();` — Determines the style of the tree (flat list or hierarchy)
- L96 _public prototype_ `void SetTreeViewMode(EObjectMixerTreeViewMode InViewMode);` — Determine the style of the tree (flat list or hierarchy)
- L98 _public prototype_ `const TSet<FName>& GetSelectedCollections();`
- L99 _public prototype_ `[[nodiscard]] bool IsCollectionSelected(const FName& CollectionName);`
- L101 _public prototype_ `void RebuildCollectionSelector();`
- L103 _public prototype_ `bool RequestRemoveCollection(const FName& CollectionName);`
- L104 _public prototype_ `bool RequestDuplicateCollection(const FName& CollectionToDuplicateName, FName& DesiredDuplicateName) const;`
- L105 _public prototype_ `bool RequestRenameCollection(const FName& CollectionNameToRename, const FName& NewCollectionName);`
- L106 _public prototype_ `bool DoesCollectionExist(const FName& CollectionName) const;`
- L108 _public prototype_ `void OnCollectionCheckedStateChanged(bool bShouldBeChecked, FName CollectionName);`
- L109 _public prototype_ `ECheckBoxState GetCollectionCheckedState(FName CollectionName) const;`
- L111 _public prototype_ `FObjectMixerOutlinerMode* GetCastedMode() const;`
- L112 _public prototype_ `UWorld* GetWorld() const;`
- L114 _public function_ `TWeakPtr<FObjectMixerEditorList> GetListModelPtr() const`
- L123 _public prototype_ `void RefreshList();` — Refresh filters and sorting. Useful for when the list state has gone stale but the variable count has not changed.
- L128 _public prototype_ `void RequestRebuildList(const FString& InItemToScrollTo = "");` — Regenerate the list items and refresh the list. Call when adding or removing items.
- L131 _public prototype_ `void OnRenameCommand();` — Called when the Rename command is executed from the UI or hotkey.
- L133 _public prototype_ `void AddToPendingPropertyPropagations(const FObjectMixerEditorListRowData::FPropertyPropagationInfo& InPropagationInfo);`
- L135 _public prototype_ `[[nodiscard]] TArray<TSharedPtr<ISceneOutlinerTreeItem>> GetSelectedTreeViewItems() const;`
- L136 _public prototype_ `int32 GetSelectedTreeViewItemCount() const;`
- L138 _public prototype_ `void SetTreeViewItemSelected(TSharedRef<ISceneOutlinerTreeItem> Item, const bool bNewSelected);`
- L140 _public prototype_ `bool IsTreeViewItemSelected(TSharedPtr<ISceneOutlinerTreeItem> Item);`
- L142 _public prototype_ `TSet<TSharedPtr<ISceneOutlinerTreeItem>> GetTreeRootItems() const;`
- L143 _public prototype_ `TSet<TWeakPtr<ISceneOutlinerTreeItem>> GetWeakTreeRootItems() const;`
- L145 _public prototype_ `TSet<TSharedPtr<ISceneOutlinerTreeItem>> GetSoloRows() const;`
- L146 _public prototype_ `void ClearSoloRows();`
- L149 _public prototype_ `bool IsListInSoloState() const;` — Returns true if at least one row is set to Solo.
- L155 _public prototype_ `void EvaluateAndSetEditorVisibilityPerRow();` — Determines whether rows' objects should be temporarily hidden in editor based on each row's visibility rules, then sets each object's visibility in editor.
- L157 _public prototype_ `bool IsTreeViewItemExpanded(const TSharedPtr<ISceneOutlinerTreeItem>& Row) const;`
- L158 _public prototype_ `void SetTreeViewItemExpanded(const TSharedPtr<ISceneOutlinerTreeItem>& RowToExpand, const bool bNewExpansion) const;`
- L160 _public prototype_ `void PropagatePropertyChangesToSelectedRows();`
- L164 _public prototype_ `FObjectMixerSceneOutlinerColumnInfo* GetColumnInfoByPropertyName(const FName& InPropertyName);`
- L165 _public prototype_ `void RestoreDefaultPropertyColumns();`
- L166 _public prototype_ `TSharedRef<SWidget> GenerateHeaderRowContextMenu();`
- L169 _public function_ `FSelectionSynchronizedEvent& GetOnSelectionSynchronized()` — Get the event that broadcasts whenever the selection list is synchronized from the editor
- L172 _public prototype_ `virtual void CustomAddToToolbar(TSharedPtr<class SHorizontalBox> Toolbar) override;` — Begin SSceneOutliner Interface
- L178 _protected member_ `TWeakPtr<FObjectMixerEditorList> ListModelPtr;` — A reference to the struct that controls this widget
- L182 _protected member_ `TSharedPtr<SWrapBox> CollectionSelectorBox;`
- L184 _protected member_ `bool bIsRebuildRequested = false;`
- L186 _protected member_ `TSet<FObjectMixerEditorListRowData::FPropertyPropagationInfo> PendingPropertyPropagations;`
- L188 _protected member_ `TArray<FObjectMixerSceneOutlinerColumnInfo> HeaderColumnInfos;`
- L189 _protected member_ `TSharedPtr<SWidget> HeaderRowContextMenuWidget;`
- L191 _protected member_ `TWeakPtr<SHorizontalBox> ToolbarPtr;`
- L193 _protected member_ `FSelectionSynchronizedEvent OnSelectionSynchronizedEvent;`
- L195 _protected prototype_ `bool CanCreateFolder() const;`
- L196 _protected prototype_ `TSharedRef<SWidget> OnGenerateAddObjectButtonMenu() const;`
- L199 _protected prototype_ `void SetSingleCollectionSelection(const FName& CollectionToEnableName = UObjectMixerEditorSerializedData::AllCollectionName);` — Disable all collection filters except CollectionToEnableName
- L201 _protected prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L203 _protected function_ `void OnActorSpawnedOrDestroyed(AActor* Object)`
- L211 _protected prototype_ `void RebuildList();` — Regenerate the list items and refresh the list. Call when adding or removing items.
- L213 _protected prototype_ `void InsertCollectionSelector();`
- L220 _protected prototype_ `bool AddUniquePropertyColumnInfo( FProperty* Property, const bool bForceIncludeProperty = false, const TSet<FName>& PropertySkipList = {} );` — Only adds properties that pass a series of tests, including having only one unique entry in the column list array. @param bForceIncludeProperty If true, only Skiplist and Uniqueness tests will be checked, bypassing class, blueprint editability and other requirements. @param PropertySkipList These property names will be skipped when they are encountered in the iteration.
- L226 _protected prototype_ `FText GetLevelColumnName() const;`
- L227 _protected prototype_ `void CreateActorTextInfoColumns(FSceneOutlinerInitializationOptions& OutInitOptions);`
- L228 _protected prototype_ `void SetupColumns(FSceneOutlinerInitializationOptions& OutInitOptions);`
- L229 _protected prototype_ `void SortColumnsForHeaderContextMenu();`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API OBJECTMIXEREDITOR_API`
- L76 _delegate_ `DECLARE_EVENT(SObjectMixerEditorList, FSelectionSynchronizedEvent);`

### `Plugins/Editor/ObjectMixer/ObjectMixer/Source/ObjectMixer/Public/Views/Widgets/ObjectMixerEditorListMenuContext.h` (Public)


#### class `UObjectMixerEditorListMenuContext`  
`class UObjectMixerEditorListMenuContext : public UObject`  
_L17-51_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- L30 _public prototype_ `static void RegisterFoldersOnlyContextMenu();`
- L31 _public prototype_ `static void RegisterObjectMixerDynamicCollectionsContextMenuExtension(const FName& MenuName);`
- L33 _public member_ `FObjectMixerEditorListMenuContextData Data;`
- L37 _private prototype_ `static bool DoesSelectionHaveType(const FObjectMixerEditorListMenuContextData& InData, UClass* Type);`
- L38 _private prototype_ `static void AddCollectionWidget(const FName& Key, const FObjectMixerEditorListMenuContextData& ContextData, UToolMenu* Menu);`
- L39 _private prototype_ `static void CreateSelectCollectionsSubMenu(UToolMenu* Menu, FObjectMixerEditorListMenuContextData ContextData);`
- L40 _private prototype_ `static void AddCollectionsMenuItem(UToolMenu* InMenu, const FObjectMixerEditorListMenuContextData& ContextData);`
- L41 _private prototype_ `static void OnTextCommitted(const FText& InText, ETextCommit::Type InCommitType, const FObjectMixerEditorListMenuContextData ContextData);`
- L43 _private prototype_ `static void OnCollectionMenuEntryCheckStateChanged(const FName Key, const FObjectMixerEditorListMenuContextData ContextData);`
- L44 _private prototype_ `static void AddObjectsToCollection(const FName Key, const FObjectMixerEditorListMenuContextData ContextData);`
- L45 _private prototype_ `static void RemoveObjectsFromCollection(const FName Key, const FObjectMixerEditorListMenuContextData ContextData);`
- L46 _private prototype_ `static bool AreAllObjectsInCollection(const FName Key, const FObjectMixerEditorListMenuContextData ContextData);`
- L47 _private prototype_ `static ECheckBoxState GetCheckStateForCollection(const FName Key, const FObjectMixerEditorListMenuContextData ContextData);`
- L49 _private prototype_ `static FToolMenuEntry MakeCustomEditMenu(const FObjectMixerEditorListMenuContextData& ContextData);`
- L50 _private prototype_ `static void ReplaceEditSubMenu(const FObjectMixerEditorListMenuContextData& ContextData);`

#### struct `UObjectMixerEditorListMenuContext::FObjectMixerEditorListMenuContextData`  
`struct FObjectMixerEditorListMenuContextData`  
_L24-28_
- L26 _public member_ `TArray<TSharedPtr<ISceneOutlinerTreeItem>> SelectedItems;`
- L27 _public member_ `TWeakPtr<class FObjectMixerEditorList> ListModelPtr;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API OBJECTMIXEREDITOR_API`

### `Plugins/Editor/ObjectMixer/ObjectMixer/Source/ObjectMixer/Public/Views/Widgets/ObjectMixerEditorUWidget.h` (Public)


#### struct `FObjectMixerWidgetUserConfig`  
`struct FObjectMixerWidgetUserConfig`  
_L15-24_
- reflection: `USTRUCT(BlueprintType)`
- desc: User Configurable Variables
- L23 _public member_ `TSubclassOf<UObjectMixerObjectFilter> DefaultFilterClass;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Object Mixer")` — Sets the default filter class to determine what objects and properties to display in this Object Mixer instance.

#### class `UObjectMixerEditorUWidget`  
`class UObjectMixerEditorUWidget : public UWidget`  
_L31-47_
- reflection: `UCLASS(MinimalAPI, meta = (DisplayName="Object Mixer (Generic)"))`
- inherits: `UWidget`
- desc: A UMG widget wrapper for the Object Mixer widget. Uses the same data as the Generic Object Mixer Instance. Only useful in the editor. It is not compatible at runtime.
- L38 _public prototype_ `virtual const FText GetPaletteCategory() override;`
- L42 _public prototype_ `virtual TSharedRef<SWidget> RebuildWidget() override;` — UWidget
- L46 _public member_ `FObjectMixerWidgetUserConfig ObjectMixerWidgetUserConfig;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Object Mixer")`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API OBJECTMIXEREDITOR_API`

### `Plugins/Editor/ObjectMixer/ObjectMixer/Source/ObjectMixer/Public/Views/Widgets/SCollectionSelectionButton.h` (Public)


#### class `SCollectionSelectionButton`  
`class SCollectionSelectionButton final : public SCompoundWidget`  
_L16-71_
- inherits: `SCompoundWidget`
- L20 _public function_ `SLATE_BEGIN_ARGS(SCollectionSelectionButton)`
- L23 _public prototype_ `SLATE_END_ARGS() void Construct( const FArguments& InArgs, const TSharedRef<SObjectMixerEditorList> ListWidget, const FName InCollectionName);`
- L30 _public prototype_ `TSharedRef<SWidget> GetContextMenu() const;`
- L32 _public prototype_ `void OnEditableTextCommitted(const FText& Text, ETextCommit::Type Type);`
- L34 _public prototype_ `virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L36 _public prototype_ `virtual FReply OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L38 _public prototype_ `virtual FReply OnDragDetected(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L40 _public prototype_ `virtual void OnDragEnter(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;`
- L42 _public prototype_ `virtual void OnDragLeave(const FDragDropEvent& DragDropEvent) override;`
- L44 _public prototype_ `virtual FReply OnDrop(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;`
- L46 _public prototype_ `const FSlateBrush* GetBorderBrush() const;`
- L47 _public prototype_ `FSlateColor GetBorderForeground() const;`
- L50 _public prototype_ `bool GetIsSelected() const;` — Whether the associated collection is selected
- L52 _public member_ `TWeakPtr<SObjectMixerEditorList> ListWidgetPtr;`
- L53 _public member_ `FName CollectionName;`
- L57 _private member_ `bool bIsPressed = false;`
- L58 _private member_ `bool bDropIsValid = false;`
- L60 _private member_ `FSlateRoundedBoxBrush UncheckedImage = FSlateRoundedBoxBrush(FStyleColors::Header, 4.0f, FStyleColors::Input, 1.0f);`
- L61 _private member_ `FSlateRoundedBoxBrush UncheckedHoveredImage = FSlateRoundedBoxBrush(FStyleColors::Hover, 4.0f, FStyleColors::Input, 1.0f);`
- L62 _private member_ `FSlateRoundedBoxBrush UncheckedPressedImage = FSlateRoundedBoxBrush(FStyleColors::Hover, 4.0f, FStyleColors::Input, 1.0f);`
- L63 _private member_ `FSlateRoundedBoxBrush UncheckedValidDropImage = FSlateRoundedBoxBrush(FStyleColors::Secondary, 4.0f, FStyleColors::Input, 1.0f);`
- L64 _private member_ `FSlateRoundedBoxBrush CheckedImage = FSlateRoundedBoxBrush(FStyleColors::Primary, 4.0f, FStyleColors::Input, 1.0f);`
- L65 _private member_ `FSlateRoundedBoxBrush CheckedHoveredImage = FSlateRoundedBoxBrush(FStyleColors::PrimaryHover, 4.0f, FStyleColors::Input, 1.0f);`
- L66 _private member_ `FSlateRoundedBoxBrush CheckedPressedImage = FSlateRoundedBoxBrush(FStyleColors::PrimaryHover, 4.0f, FStyleColors::Input, 1.0f);`
- L67 _private member_ `FSlateRoundedBoxBrush CheckedValidDropImage = FSlateRoundedBoxBrush(FStyleColors::Secondary, 4.0f, FStyleColors::Input, 1.0f);`
- L69 _private member_ `TSharedPtr<SInlineEditableTextBlock> EditableTextBlock;`
- L70 _private member_ `TSharedPtr<SMenuAnchor> MenuAnchor;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define LOCTEXT_NAMESPACE "ObjectMixerEditor"`

### `Plugins/Editor/ObjectMixer/ObjectMixer/Source/ObjectMixer/Public/Views/Widgets/SHyperlinkWithTextHighlight.h` (Public)


#### class `SHyperlinkWithTextHighlight`  
`class SHyperlinkWithTextHighlight : public SButton`  
_L25-125_
- inherits: `SButton`
- desc: A hyperlink widget is what you would expect from a browser hyperlink. When a hyperlink is clicked in invokes an OnNavigate() delegate.
- L30 _public function_ `SLATE_BEGIN_ARGS(SHyperlinkWithTextHighlight) : _Text() , _Style(&FAppStyle::Get().GetWidgetStyle< FHyperlinkStyle >("Hyperlink")) , _UnderlineStyle(nullptr) , _Padding() , _OnNavigate() , _TextShapingMethod() , _TextFlowDirection() , _HighlightText()`
- L41 _public function_ `SLATE_ATTRIBUTE( FText, Text ) SLATE_STYLE_ARGUMENT( FHyperlinkStyle, Style ) SLATE_STYLE_ARGUMENT( FButtonStyle, UnderlineStyle ) SLATE_ATTRIBUTE( FMargin, Padding ) SLATE_EVENT( FSimpleDelegate, OnNavigate ) SLATE_ARGUMENT( TOptional<ETextShapingMethod>, TextShapingMethod ) SLATE_ARGUMENT( TOptional<ETextFlowDirection>, TextFlowDirection ) SLATE_EVENT( FIsSelected, IsSelected ) SLATE_EVENT( FOnTextCommitted, OnTextCommitted ) SLATE_ATTRIBUTE( FText, HighlightText ) SLATE_END_ARGS() void Construct( const FArguments& InArgs )`
- L98 _public function_ `virtual FCursorReply OnCursorQuery( const FGeometry& MyGeometry, const FPointerEvent& CursorEvent ) const override`
- L103 _public function_ `virtual TSharedRef<FSlateAccessibleWidget> CreateAccessibleWidget() override`
- L109 _public member_ `TSharedPtr<SInlineEditableTextBlock> EditableTextBlock;`
- L114 _protected function_ `FReply Hyperlink_OnClicked()` — Invoke the OnNavigate method
- L122 _protected member_ `FSimpleDelegate OnNavigate;` — The delegate to invoke when someone clicks the hyperlink
- L124 _protected member_ `FInlineEditableTextBlockStyle EditableTextBlockStyle;`

### `Plugins/Editor/ObjectMixer/ObjectMixer/Source/ObjectMixer/Public/Views/Widgets/SInlinePropertyCellWidget.h` (Public)


#### class `SInlinePropertyCellWidget`  
`class SInlinePropertyCellWidget : public SCompoundWidget`  
_L13-42_
- inherits: `SCompoundWidget`
- L17 _public function_ `SLATE_BEGIN_ARGS(SInlinePropertyCellWidget)`
- L20 _public prototype_ `SLATE_EVENT(TDelegate<void(const FPropertyChangedEvent&)>, OnPropertyValueChanged) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const FName InColumnName, const TSharedRef<ISceneOutlinerTreeItem> RowPtr);`
- L26 _public prototype_ `virtual FReply OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L28 _public prototype_ `FReply MakePropertyContextMenu(const FPointerEvent& MouseEvent);`
- L32 _protected prototype_ `void CopyPropertyValue() const;`
- L34 _protected prototype_ `void PastePropertyValue() const;`
- L36 _protected prototype_ `bool CanPaste() const;`
- L38 _protected prototype_ `void CopyPropertyName() const;`
- L40 _protected member_ `TWeakPtr<ISceneOutlinerTreeItem> WeakRowPtr;`
- L41 _protected member_ `FName ColumnName;`
