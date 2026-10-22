# Plugins / DisplayClusterTests

- module root: `Plugins/Runtime/nDisplay/Source/DisplayClusterTests`
- headers: 2; symbols: 24
- symbol kinds: class=1, delegate=1, function=7, namespace=1, prototype=14
- PrivateDependencyModuleNames: Core, CoreUObject, DisplayCluster, DisplayClusterConfiguration, DisplayClusterConfigurator, Engine, OpenColorIO, SlateCore, SubobjectDataInterface, UnrealEd

### `Plugins/Runtime/nDisplay/Source/DisplayClusterTests/Private/DisplayClusterTestUtils.h` (Private)


#### Free symbols / members of external scopes

- L20 _namespace_ `namespace DisplayClusterTestUtils`
- L26 _prototype_ `UDisplayClusterBlueprint* CreateDisplayClusterAsset();` (scope `DisplayClusterTestUtils`) — Create a display cluster asset using a new UDisplayClusterConfiguratorFactory. If the asset is invalid or not a UDisplayClusterBlueprint, the package will be immediately cleaned up.
- L32 _prototype_ `UDisplayClusterConfigurationClusterNode* AddClusterNodeToCluster(UBlueprint* Blueprint, UDisplayClusterConfigurationCluster* RootCluster, FString Name = "", bool bCallPostEditChange = true);` (scope `DisplayClusterTestUtils`) — Add a cluster node to a cluster asset. This will automatically create the template node and discard it when finished.
- L38 _prototype_ `UDisplayClusterConfigurationViewport* AddViewportToClusterNode(UBlueprint* Blueprint, UDisplayClusterConfigurationClusterNode* Node, FString Name = "", bool bCallPostEditChange = true);` (scope `DisplayClusterTestUtils`) — Add a viewport to a cluster asset. This will automatically create the template viewport and discard it when finished.
- L43 _prototype_ `UWorld* CreateWorld();` (scope `DisplayClusterTestUtils`) — Create a world and set it as the current world.
- L48 _prototype_ `void CleanUpPackage(UPackage* Package);` (scope `DisplayClusterTestUtils`) — Clean up a package that was created during a test.
- L53 _prototype_ `void CleanUpAsset(UObject* Asset);` (scope `DisplayClusterTestUtils`) — Clean up an asset that was created during a test.
- L58 _prototype_ `void CleanUpAssetAndPackage(UObject* Asset);` (scope `DisplayClusterTestUtils`) — Clean up an asset that was created during a test as well as its containing package (if the package exists).
- L63 _prototype_ `void CleanUpWorld(UWorld* World);` (scope `DisplayClusterTestUtils`) — Clean up a world that was created during a test.
- L76 _prototype_ `bool GetPropertyViewAndHandleFromFieldNames(UObject* Owner, const TArray<FName>& FieldNames, bool bAllowAdd, TSharedPtr<ISinglePropertyView>& OutPropertyView, TSharedPtr<IPropertyHandle>& OutPropertyHandle);` (scope `DisplayClusterTestUtils`) — Get a property view based on a list of nested field names. @param Owner The root owner of the field. @param FieldNames A list of field names, where the first name is the top-most field, and subsequent names are nested fields (e.g. a field within a struct). @param bAllowAdd If true and one of the fields encountered is a container, an element will be added. If false, this will return false in the same situation. @param OutPropertyView The property will be stored here. @param OutPropertyHandle The property handle will be stored here. @return Whether the property view and handle were successfully found.
- L82 _prototype_ `template <typename T> FPropertyAccess::Result SetPropertyHandleValue(TSharedPtr<IPropertyHandle> Handle, const T& Value);` (scope `DisplayClusterTestUtils`) — Set the value of a property handle.
- L88 _prototype_ `template <typename T> FPropertyAccess::Result GetPropertyHandleValue(TSharedPtr<IPropertyHandle> Handle, T& OutValue);` (scope `DisplayClusterTestUtils`) — Get the value of a property handle.
- L102 _prototype_ `template <typename T> bool SetBlueprintPropertyValue(UObject* Owner, UBlueprint* Blueprint, const TArray<FName>& FieldNames, const T& Value);` (scope `DisplayClusterTestUtils`) — Set a property (or nested property) of an object using a PropertyView and notify its root blueprint of any changes as if the change happened through the Blueprint editor. @param Owner The root owner of the field. @param Blueprint The Blueprint asset to notify after changing the value (optional). @param FieldNames A list of field names, where the first name is the top-most field, and subsequent names are nested fields (e.g. a field within a struct). @param Value The value to set the field to. @return Whether the field was successfully found and set.
- L114 _prototype_ `template <typename T> bool GetBlueprintPropertyValue(UObject* Owner, const TArray<FName>& FieldNames, T& OutValue);` (scope `DisplayClusterTestUtils`) — Get the value of a property (or nested property) of an object using a PropertyView. @param Owner The root owner of the field. @param FieldNames A list of field names, where the first name is the top-most field, and subsequent names are nested fields (e.g. a field within a struct). @param OutValue The value of the property will be stored here. @return Whether the value was successfully retrieved.
- L118 _function_ `template <typename T> FPropertyAccess::Result DisplayClusterTestUtils::SetPropertyHandleValue(TSharedPtr<IPropertyHandle> Handle, const T& Value)` (scope `DisplayClusterTestUtils`)
- L124 _function_ `template <typename T> FPropertyAccess::Result DisplayClusterTestUtils::GetPropertyHandleValue(TSharedPtr<IPropertyHandle> Handle, T& OutValue)` (scope `DisplayClusterTestUtils`)
- L131 _function_ `template <> inline FPropertyAccess::Result DisplayClusterTestUtils::SetPropertyHandleValue(TSharedPtr<IPropertyHandle> Handle, const FLinearColor& Value)` (scope `DisplayClusterTestUtils`) — Get/set specializations for colors since they have to be set/retrieved as strings rather than directly
- L137 _function_ `template <> inline FPropertyAccess::Result DisplayClusterTestUtils::GetPropertyHandleValue(TSharedPtr<IPropertyHandle> Handle, FLinearColor& Value)` (scope `DisplayClusterTestUtils`)
- L154 _function_ `template <typename T> bool DisplayClusterTestUtils::SetBlueprintPropertyValue(UObject* Owner, UBlueprint* Blueprint, const TArray<FName>& FieldNames, const T& OutValue)` (scope `DisplayClusterTestUtils`)
- L180 _function_ `template <typename T> bool DisplayClusterTestUtils::GetBlueprintPropertyValue(UObject* Owner, const TArray<FName>& FieldNames, T& OutValue)` (scope `DisplayClusterTestUtils`)

### `Plugins/Runtime/nDisplay/Source/DisplayClusterTests/Private/DisplayClusterTestsModule.h` (Private)


#### class `FDisplayClusterTestsModule`  
`class FDisplayClusterTestsModule : public IModuleInterface`  
_L10-15_
- inherits: `IModuleInterface`
- L12 _private function_ `virtual void StartupModule() override`

#### Free symbols / members of external scopes

- L8 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogDisplayClusterTests, Log, All);`
- L8 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogDisplayClusterTests, Log, All);`
