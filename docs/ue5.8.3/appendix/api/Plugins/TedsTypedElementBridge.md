# Plugins / TedsTypedElementBridge

- module root: `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsTypedElementBridge`
- headers: 3; symbols: 33
- symbol kinds: class=2, delegate=1, member=7, namespace=4, prototype=19
- PrivateDependencyModuleNames: Core, CoreUObject, Engine, InputCore, Slate, SlateCore, TedsActorCompatibility, ToolWidgets, WorkspaceMenuStructure
- PublicDependencyModuleNames: TedsQueryStack, TypedElementFramework

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsTypedElementBridge/Private/TedsTypedElementBridge/TedsTypedElementActorHandleFactory.h` (Private)


#### class `UTypedElementActorHandleDataStorageFactory`  
`class UTypedElementActorHandleDataStorageFactory : public UEditorDataStorageFactory`  
_L19-37_
- reflection: `UCLASS(Transient)`
- inherits: `UEditorDataStorageFactory`
- desc: This class is responsible for acquiring and registering Actor Typed Element Handles with TEDS/
- L24 _public prototype_ `virtual void PreRegister(UE::Editor::DataStorage::ICoreProvider& DataStorage) override;`
- L25 _public prototype_ `virtual void RegisterQueries(UE::Editor::DataStorage::ICoreProvider& DataStorage) override;`
- L26 _public prototype_ `virtual void PreShutdown(UE::Editor::DataStorage::ICoreProvider& DataStorage) override;`
- L28 _private prototype_ `virtual void RegisterQuery_ActorHandlePopulate(UE::Editor::DataStorage::ICoreProvider& DataStorage);`
- L29 _private prototype_ `virtual void RegisterQuery_ActorComponentHandlePopulate(UE::Editor::DataStorage::ICoreProvider& DataStorage);`
- L30 _private prototype_ `void HandleBridgeEnabled(bool bEnabled);`
- L32 _private member_ `FDelegateHandle BridgeEnableDelegateHandle;`
- L33 _private member_ `UE::Editor::DataStorage::QueryHandle ActorHandlePopulateQuery = UE::Editor::DataStorage::InvalidQueryHandle;`
- L34 _private member_ `UE::Editor::DataStorage::QueryHandle GetAllActorsQuery = UE::Editor::DataStorage::InvalidQueryHandle;`
- L35 _private member_ `UE::Editor::DataStorage::QueryHandle ActorComponentHandlePopulateQuery = UE::Editor::DataStorage::InvalidQueryHandle;`
- L36 _private member_ `UE::Editor::DataStorage::QueryHandle GetAllActorComponentsQuery = UE::Editor::DataStorage::InvalidQueryHandle;`

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsTypedElementBridge/Private/TedsTypedElementBridge/TedsTypedElementBridgeQueries.h` (Private)


#### class `UTypedElementBridgeDataStorageFactory`  
`class UTypedElementBridgeDataStorageFactory : public UEditorDataStorageFactory`  
_L17-37_
- reflection: `UCLASS(Transient)`
- inherits: `UEditorDataStorageFactory`
- desc: This class is responsible for running queries that will ensure Typed Element Handles are cleaned up when TEDS is shut down.
- L21 _public prototype_ `~UTypedElementBridgeDataStorageFactory() override = default;`
- L22 _public prototype_ `virtual uint8 GetOrder() const override;`
- L23 _public prototype_ `virtual void PreRegister(UE::Editor::DataStorage::ICoreProvider& DataStorage) override;`
- L24 _public prototype_ `virtual void PreShutdown(UE::Editor::DataStorage::ICoreProvider& DataStorage) override;`
- L25 _public prototype_ `virtual void RegisterQueries(UE::Editor::DataStorage::ICoreProvider& DataStorage) override;`
- L27 _public prototype_ `static bool IsEnabled();`
- L30 _private prototype_ `void RegisterQuery_NewUObject(UE::Editor::DataStorage::ICoreProvider& DataStorage);`
- L31 _private prototype_ `void UnregisterQuery_NewUObject(UE::Editor::DataStorage::ICoreProvider& DataStorage);`
- L32 _private prototype_ `void CleanupTypedElementColumns(UE::Editor::DataStorage::ICoreProvider& DataStorage);`
- L33 _private prototype_ `void HandleOnEnabled(IConsoleVariable* CVar);`
- L35 _private member_ `UE::Editor::DataStorage::QueryHandle RemoveTypedElementRowHandleQuery = UE::Editor::DataStorage::InvalidQueryHandle;`
- L36 _private member_ `FDelegateHandle DebugEnabledDelegateHandle;`

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsTypedElementBridge/Public/TedsTypedElementBridge/TedsTypedElementBridgeCapabilities.h` (Public)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace Editor` (scope `UE`)
- L7 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L7 _namespace_ `namespace Compatibility` (scope `UE::Editor::DataStorage`)
- L9 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnTypedElementBridgeEnabled, bool );`
- L9 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnTypedElementBridgeEnabled, bool );` (scope `UE::Editor::DataStorage::Compatibility`)
- L11 _prototype_ `FOnTypedElementBridgeEnabled& OnTypedElementBridgeEnabled();` (scope `UE::Editor::DataStorage::Compatibility`)
- L12 _prototype_ `bool IsTypedElementBridgeEnabled();` (scope `UE::Editor::DataStorage::Compatibility`)
