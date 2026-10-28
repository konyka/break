# Plugins / ChaosRigidAssetEditor

- module root: `Plugins/Experimental/ChaosRigidAsset/Source/ChaosRigidAssetEditor`
- headers: 2; symbols: 24
- symbol kinds: class=4, member=3, namespace=3, prototype=14
- PrivateDependencyModuleNames: CoreUObject
- PublicDependencyModuleNames: ChaosRigidAssetEngine, ChaosRigidAssetNodes, Core, DataflowCore, DataflowEditor, DataflowEngine, DataflowEnginePlugin, Engine, PhysicsAssetEditor, Slate, SlateCore, UnrealEd

### `Plugins/Experimental/ChaosRigidAsset/Source/ChaosRigidAssetEditor/Public/ChaosRigidAssetEditorModule.h` (Public)


#### class `FChaosRigidAssetEditorModule`  
`class FChaosRigidAssetEditorModule : public IModuleInterface`  
_L11-22_
- inherits: `IModuleInterface`
- L15 _public prototype_ `virtual void StartupModule() override;`
- L16 _public prototype_ `virtual void ShutdownModule() override;`
- L19 _private member_ `TUniquePtr<FDataflowPhysicsAssetEditorOverride> EditorFeature;`
- L20 _private member_ `FDelegateHandle AssetMenuExtenderHandle;`
- L21 _private member_ `FDelegateHandle DataflowMenusHandle;`

### `Plugins/Experimental/ChaosRigidAsset/Source/ChaosRigidAssetEditor/Public/DataflowRendering.h` (Public)


#### class `UE::Chaos::RigidAsset::FAggregateGeometryGeomRenderCallbacks`  
`class FAggregateGeometryGeomRenderCallbacks : public UE::Dataflow::FRenderingFactory::ICallbackInterface`  
_L9-19_
- inherits: `UE::Dataflow::FRenderingFactory::ICallbackInterface`
- L13 _public prototype_ `static UE::Dataflow::FRenderKey StaticGetRenderKey();`
- L15 _public prototype_ `UE::Dataflow::FRenderKey GetRenderKey() const override;`
- L16 _public prototype_ `bool CanRender(const UE::Dataflow::IDataflowConstructionViewMode& ViewMode) const override;`
- L17 _public prototype_ `void Render(GeometryCollection::Facades::FRenderingFacade& RenderingFacade, const UE::Dataflow::FGraphRenderingState& State) override;`

#### class `UE::Chaos::RigidAsset::FBoneSelectionRenderCallbacks`  
`class FBoneSelectionRenderCallbacks : public UE::Dataflow::FRenderingFactory::ICallbackInterface`  
_L21-30_
- inherits: `UE::Dataflow::FRenderingFactory::ICallbackInterface`
- L25 _public prototype_ `static UE::Dataflow::FRenderKey StaticGetRenderKey();`
- L27 _public prototype_ `UE::Dataflow::FRenderKey GetRenderKey() const override;`
- L28 _public prototype_ `bool CanRender(const UE::Dataflow::IDataflowConstructionViewMode& ViewMode) const override;`
- L29 _public prototype_ `void Render(GeometryCollection::Facades::FRenderingFacade& RenderingFacade, const UE::Dataflow::FGraphRenderingState& State) override;`

#### class `UE::Chaos::RigidAsset::FPhysAssetStateRenderCallbacks`  
`class FPhysAssetStateRenderCallbacks : public UE::Dataflow::FRenderingFactory::ICallbackInterface`  
_L32-41_
- inherits: `UE::Dataflow::FRenderingFactory::ICallbackInterface`
- L36 _public prototype_ `static UE::Dataflow::FRenderKey StaticGetRenderKey();`
- L38 _public prototype_ `UE::Dataflow::FRenderKey GetRenderKey() const override;`
- L39 _public prototype_ `bool CanRender(const UE::Dataflow::IDataflowConstructionViewMode& ViewMode) const override;`
- L40 _public prototype_ `void Render(GeometryCollection::Facades::FRenderingFacade& RenderingFacade, const UE::Dataflow::FGraphRenderingState& State) override;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace Chaos` (scope `UE`)
- L7 _namespace_ `namespace RigidAsset` (scope `UE::Chaos`)
