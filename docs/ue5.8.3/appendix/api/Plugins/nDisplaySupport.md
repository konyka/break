# Plugins / nDisplaySupport

- module root: `Plugins/VirtualProduction/LevelSnapshots/Source/nDisplaySupport`
- headers: 8; symbols: 97
- symbol kinds: class=8, function=18, member=2, namespace=46, prototype=23
- PrivateDependencyModuleNames: CoreUObject, Engine, LevelSnapshots
- PublicDependencyModuleNames: Core

### `Plugins/VirtualProduction/LevelSnapshots/Source/nDisplaySupport/Private/Helpers/MapSubobjectSerializer.h` (Private)


#### class `UE::LevelSnapshots::nDisplay::Private::TMapSubobjectSerializer`  
`template<typename TDerived> class TMapSubobjectSerializer : public ICustomObjectSnapshotSerializer, public TSharedFromThis<TDerived>`  
_L26-121_
- inherits: `ICustomObjectSnapshotSerializer,TSharedFromThis<TDerived>`
- desc: Helper class for a subobject which has a TMap<FString, UObject> Super class must implement this function: const FMapProperty* GetMapProperty().
- L31 _private function_ `TDerived* This()`
- L32 _private function_ `const TDerived* This() const`
- L34 _private function_ `UObject* FindSubobject(UObject* Owner, const ISnapshotSubobjectMetaData& ObjectData)`
- L46 _private function_ `FScriptMapHelper GetSubobjectMap(UObject* Owner) const`
- L52 _private function_ `const FString& GetKey(FScriptMapHelper& Map, int32 Index) const`
- L61 _private function_ `UObject* GetValue(FScriptMapHelper& Map, int32 Index) const`
- L70 _private function_ `UObject* GetValue(FScriptMapHelper& Map, const FString& Key) const`
- L82 _public function_ `virtual void OnTakeSnapshot(UObject* EditorObject, ICustomSnapshotSerializationData& DataStorage) override`
- L108 _public function_ `virtual UObject* FindOrRecreateSubobjectInSnapshotWorld(UObject* SnapshotObject, const ISnapshotSubobjectMetaData& ObjectData, const ICustomSnapshotSerializationData& DataStorage) override`
- L112 _public function_ `virtual UObject* FindOrRecreateSubobjectInEditorWorld(UObject* EditorObject, const ISnapshotSubobjectMetaData& ObjectData, const ICustomSnapshotSerializationData& DataStorage) override`
- L116 _public function_ `virtual UObject* FindSubobjectInEditorWorld(UObject* EditorObject, const ISnapshotSubobjectMetaData& ObjectData, const ICustomSnapshotSerializationData& DataStorage) override`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace LevelSnapshots` (scope `UE`)
- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace LevelSnapshots` (scope `UE`)
- L19 _namespace_ `namespace nDisplay` (scope `UE::LevelSnapshots`)
- L19 _namespace_ `namespace Private` (scope `UE::LevelSnapshots::nDisplay`)
- L38 _function_ `` (scope `UE::LevelSnapshots::nDisplay::Private::TMapSubobjectSerializer::FindSubobject`)
- L96 _function_ `` (scope `UE::LevelSnapshots::nDisplay::Private::TMapSubobjectSerializer::OnTakeSnapshot`)

### `Plugins/VirtualProduction/LevelSnapshots/Source/nDisplaySupport/Private/Helpers/ReferenceSubobjectSerializer.h` (Private)


#### class `UE::LevelSnapshots::nDisplay::Private::TReferenceSubobjectSerializer`  
`template<typename TDerived> class TReferenceSubobjectSerializer : public ICustomObjectSnapshotSerializer, public TSharedFromThis<TDerived>`  
_L17-49_
- inherits: `ICustomObjectSnapshotSerializer,TSharedFromThis<TDerived>`
- L22 _private function_ `TDerived* This()`
- L25 _public prototype_ `static void Register(ILevelSnapshotsModule& Module);`
- L28 _public function_ `virtual void OnTakeSnapshot(UObject* EditorObject, ICustomSnapshotSerializationData& DataStorage) override`
- L36 _public function_ `virtual UObject* FindOrRecreateSubobjectInSnapshotWorld(UObject* SnapshotObject, const ISnapshotSubobjectMetaData& ObjectData, const ICustomSnapshotSerializationData& DataStorage) override`
- L40 _public function_ `virtual UObject* FindOrRecreateSubobjectInEditorWorld(UObject* EditorObject, const ISnapshotSubobjectMetaData& ObjectData, const ICustomSnapshotSerializationData& DataStorage) override`
- L44 _public function_ `virtual UObject* FindSubobjectInEditorWorld(UObject* EditorObject, const ISnapshotSubobjectMetaData& ObjectData, const ICustomSnapshotSerializationData& DataStorage) override`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace LevelSnapshots` (scope `UE`)
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace LevelSnapshots` (scope `UE`)
- L14 _namespace_ `namespace nDisplay` (scope `UE::LevelSnapshots`)
- L14 _namespace_ `namespace Private` (scope `UE::LevelSnapshots::nDisplay`)

### `Plugins/VirtualProduction/LevelSnapshots/Source/nDisplaySupport/Private/Map/DisplayClusterConfigurationClusterNodeSerializer.h` (Private)


#### class `UE::LevelSnapshots::nDisplay::Private::FDisplayClusterConfigurationClusterNodeSerializer`  
`class FDisplayClusterConfigurationClusterNodeSerializer : public TMapSubobjectSerializer<FDisplayClusterConfigurationClusterNodeSerializer>`  
_L16-28_
- inherits: `TMapSubobjectSerializer<FDisplayClusterConfigurationClusterNodeSerializer>`
- L18 _private prototype_ `static UClass* GetSupportedClass();`
- L19 _private prototype_ `static void MarkPropertiesAsExplicitlyUnsupported(ILevelSnapshotsModule& Module);`
- L23 _public prototype_ `static void Register(ILevelSnapshotsModule& Module);`
- L26 _public prototype_ `static const FMapProperty* GetMapProperty();`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace LevelSnapshots` (scope `UE`)
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace LevelSnapshots` (scope `UE`)
- L13 _namespace_ `namespace nDisplay` (scope `UE::LevelSnapshots`)
- L13 _namespace_ `namespace Private` (scope `UE::LevelSnapshots::nDisplay`)

### `Plugins/VirtualProduction/LevelSnapshots/Source/nDisplaySupport/Private/Map/DisplayClusterConfigurationClusterSerializer.h` (Private)


#### class `UE::LevelSnapshots::nDisplay::Private::FDisplayClusterConfigurationClusterSerializer`  
`class FDisplayClusterConfigurationClusterSerializer : public TMapSubobjectSerializer<FDisplayClusterConfigurationClusterSerializer>`  
_L15-26_
- inherits: `TMapSubobjectSerializer<FDisplayClusterConfigurationClusterSerializer>`
- L17 _private prototype_ `static UClass* GetSupportedClass();`
- L18 _private prototype_ `static void MarkPropertiesAsExplicitlyUnsupported(ILevelSnapshotsModule& Module);`
- L21 _public prototype_ `static void Register(ILevelSnapshotsModule& Module);`
- L24 _public prototype_ `static const FMapProperty* GetMapProperty();`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace LevelSnapshots` (scope `UE`)
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace LevelSnapshots` (scope `UE`)
- L13 _namespace_ `namespace nDisplay` (scope `UE::LevelSnapshots`)
- L13 _namespace_ `namespace Private` (scope `UE::LevelSnapshots::nDisplay`)

### `Plugins/VirtualProduction/LevelSnapshots/Source/nDisplaySupport/Private/Material/DisplayMaterialOverrideFix.h` (Private)


#### class `UE::LevelSnapshots::nDisplay::Private::FDisplayMaterialOverrideFix`  
`class FDisplayMaterialOverrideFix : public IPropertyComparer`  
_L16-27_
- inherits: `IPropertyComparer`
- desc: Fixes material instances in UDisplayClusterPreviewComponent showing up as changed
- L18 _private member_ `FProperty* OverrideMaterials{};`
- L22 _public prototype_ `static void Register(ILevelSnapshotsModule& Module);`
- L25 _public prototype_ `virtual EPropertyComparison ShouldConsiderPropertyEqual(const FPropertyComparisonParams& Params) const override;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace LevelSnapshots` (scope `UE`)
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace LevelSnapshots` (scope `UE`)
- L13 _namespace_ `namespace nDisplay` (scope `UE::LevelSnapshots`)
- L13 _namespace_ `namespace Private` (scope `UE::LevelSnapshots::nDisplay`)

### `Plugins/VirtualProduction/LevelSnapshots/Source/nDisplaySupport/Private/Reference/DisplayClusterConfigurationDataSerializer.h` (Private)


#### class `UE::LevelSnapshots::nDisplay::Private::FDisplayClusterConfigurationDataSerializer`  
`class FDisplayClusterConfigurationDataSerializer : public TReferenceSubobjectSerializer<FDisplayClusterConfigurationDataSerializer>`  
_L15-27_
- inherits: `TReferenceSubobjectSerializer<FDisplayClusterConfigurationDataSerializer>`
- L17 _private prototype_ `static UClass* GetSupportedClass();`
- L18 _private prototype_ `static void MarkPropertiesAsExplicitlyUnsupported(ILevelSnapshotsModule& Module);`
- L22 _public prototype_ `static void Register(ILevelSnapshotsModule& Module);`
- L25 _public prototype_ `UObject* FindSubobject(UObject* Owner) const;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace LevelSnapshots` (scope `UE`)
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace LevelSnapshots` (scope `UE`)
- L13 _namespace_ `namespace nDisplay` (scope `UE::LevelSnapshots`)
- L13 _namespace_ `namespace Private` (scope `UE::LevelSnapshots::nDisplay`)

### `Plugins/VirtualProduction/LevelSnapshots/Source/nDisplaySupport/Private/Reference/DisplayClusterRootActorSerializer.h` (Private)


#### class `UE::LevelSnapshots::nDisplay::Private::FDisplayClusterRootActorSerializer`  
`class FDisplayClusterRootActorSerializer : public TReferenceSubobjectSerializer<FDisplayClusterRootActorSerializer>, public IPropertyComparer`  
_L16-39_
- inherits: `TReferenceSubobjectSerializer<FDisplayClusterRootActorSerializer>,IPropertyComparer`
- L21 _private prototype_ `static UClass* GetSupportedClass();`
- L22 _private prototype_ `static void MarkPropertiesAsExplicitlyUnsupported(ILevelSnapshotsModule& Module);`
- L24 _private member_ `const FProperty* OverrideMaterials;`
- L28 _public prototype_ `static void Register(ILevelSnapshotsModule& Module);`
- L30 _public prototype_ `FDisplayClusterRootActorSerializer();`
- L33 _public prototype_ `virtual EPropertyComparison ShouldConsiderPropertyEqual(const FPropertyComparisonParams& Params) const override;`
- L37 _public prototype_ `UObject* FindSubobject(UObject* Owner) const;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace LevelSnapshots` (scope `UE`)
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace LevelSnapshots` (scope `UE`)
- L14 _namespace_ `namespace nDisplay` (scope `UE::LevelSnapshots`)
- L14 _namespace_ `namespace Private` (scope `UE::LevelSnapshots::nDisplay`)

### `Plugins/VirtualProduction/LevelSnapshots/Source/nDisplaySupport/Private/nDisplaySupportModule.h` (Private)


#### class `UE::LevelSnapshots::nDisplay::Private::FnDisplaySupportModule`  
`class FnDisplaySupportModule : public IModuleInterface`  
_L10-17_
- inherits: `IModuleInterface`
- L15 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L16 _public prototype_ `virtual void ShutdownModule() override;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace LevelSnapshots` (scope `UE`)
- L8 _namespace_ `namespace nDisplay` (scope `UE::LevelSnapshots`)
- L8 _namespace_ `namespace Private` (scope `UE::LevelSnapshots::nDisplay`)
