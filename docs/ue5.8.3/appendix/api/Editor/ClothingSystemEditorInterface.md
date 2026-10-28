# Editor / ClothingSystemEditorInterface

- module root: `Source/Editor/ClothingSystemEditorInterface`
- headers: 3; symbols: 34
- symbol kinds: class=4, function=7, macro=3, member=2, namespace=2, prototype=16
- PrivateDependencyModuleNames: ClothingSystemRuntimeInterface
- PublicDependencyModuleNames: Core, CoreUObject

### `Source/Editor/ClothingSystemEditorInterface/Public/ClothingAssetFactoryInterface.h` (Public)


#### class `UClothingAssetFactoryBase`  
`class UClothingAssetFactoryBase : public UObject`  
_L34-100_
- reflection: `UCLASS(MinimalAPI, Abstract)`
- inherits: `UObject`
- desc: Clothing asset factories should inherit this interface/uobject to provide functionality to build clothing assets from .apx files imported to the engine
- L41 _public prototype_ `virtual const UClass* GetSupportedSourceAssetType() const PURE_VIRTUAL(UClothingAssetFactoryBase::GetSupportedSourceAssetType, return nullptr;);` — Return the supported source asset type for this clothing data. @see CreateFromSourceAsset.
- L50 _public prototype_ `virtual UClothingAssetBase* CreateFromSkeletalMesh(USkeletalMesh* TargetMesh, FSkeletalMeshClothBuildParams& Params) PURE_VIRTUAL(UClothingAssetFactoryBase::CreateFromSkeletalMesh, return nullptr;);` — Given a target mesh and parameters describing the build operation, create a clothing asset for use on the mesh @param TargetMesh - The mesh to target @param Params - Extra operation params (LOD/Section index etc...)
- L58 _public prototype_ `virtual TArray<UClothingAssetBase*> CreateFromSourceAsset(USkeletalMesh* TargetMesh, const UObject* SourceAsset) const PURE_VIRTUAL(UClothingAssetFactoryBase::CreateFromSourceAsset, return TArray<UClothingAssetBase*>(););` — Given a target mesh and a source asset, create clothing data from the source asset to use on the target mesh. @param TargetMesh - The mesh to target @param SourceAsset - The asset to build the clothing data with.
- L67 _public prototype_ `virtual UClothingAssetBase* ImportLodToClothing(USkeletalMesh* TargetMesh, FSkeletalMeshClothBuildParams& Params) PURE_VIRTUAL(UClothingAssetFactoryBase::ImportLodToClothing, return nullptr;);` — Given a target mesh and valid parameters, import a simulation mesh as a LOD for the clothing specified by the build parameters, returning the modified clothing object @param TargetMesh The owner mesh @param Params Build parameters for the operation (target clothing object, source data)
- L72 _public function_ `virtual UClothingAssetBase* Import(const FString& Filename, USkeletalMesh* TargetMesh, FName InName = NAME_None)` — `UE_DEPRECATED(5.7, "Clothing file import is no longer supported.")` — Deprecated methods
- L78 _public function_ `virtual UClothingAssetBase* Reimport(const FString& Filename, USkeletalMesh* TargetMesh, UClothingAssetBase* OriginalAsset)` — `UE_DEPRECATED(5.7, "Clothing file import is no longer supported.")`
- L84 _public function_ `virtual UClothingAssetBase* CreateFromExistingCloth(USkeletalMesh* , USkeletalMesh* , UClothingAssetBase* )` — `UE_DEPRECATED(5.7, "Use UClothingAssetFactory::CreateFromSourceAsset() instead.")`
- L90 _public function_ `virtual bool CanImport(const FString& Filename)` — `UE_DEPRECATED(5.7, "Clothing file import is no longer supported.")`
- L96 _public function_ `virtual UClothingAssetBase* CreateFromApexAsset(nvidia::apex::ClothingAsset* InApexAsset, USkeletalMesh* TargetMesh, FName InName = NAME_None)` — `UE_DEPRECATED(5.7, "Clothing file import is no longer supported.")`

#### class `IClothingAssetFactoryProvider`  
`class IClothingAssetFactoryProvider : public IModularFeature`  
_L104-112_
- inherits: `IModularFeature`
- desc: An interface for a class that will provide a clothing asset factory, this should be registered as a feature under its FeatureName to be picked up by the engine
- L107 _public member_ `static const FName FeatureName;`
- L111 _public prototype_ `virtual UClothingAssetFactoryBase* GetFactory() = 0;` — Called by the engine to retrieve a valid factory from a provider This can be the default object for the factory class or a full instance

#### Free symbols / members of external scopes

- L17 _macro_ `#define UE_API CLOTHINGSYSTEMEDITORINTERFACE_API`
- L19 _namespace_ `namespace nvidia`
- L21 _namespace_ `namespace apex` (scope `nvidia`)

### `Source/Editor/ClothingSystemEditorInterface/Public/ClothingSystemEditorInterfaceModule.h` (Public)


#### class `FClothingSystemEditorInterfaceModule`  
`class FClothingSystemEditorInterfaceModule : public IModuleInterface`  
_L13-31_
- inherits: `IModuleInterface`
- L18 _public member_ `const static FName ExtenderFeatureName;`
- L20 _public prototype_ `FClothingSystemEditorInterfaceModule();`
- L22 _public prototype_ `virtual void StartupModule() override;`
- L23 _public prototype_ `virtual void ShutdownModule() override;`
- L25 _public prototype_ `UClothingAssetFactoryBase* GetClothingAssetFactory();`
- L26 _public prototype_ `TArray<UClothingAssetFactoryBase*> GetClothingAssetFactories();`
- L27 _public prototype_ `ISimulationEditorExtender* GetSimulationEditorExtender(FName InSimulationFactoryClassName);`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API CLOTHINGSYSTEMEDITORINTERFACE_API`

### `Source/Editor/ClothingSystemEditorInterface/Public/SimulationEditorExtender.h` (Public)


#### class `ISimulationEditorExtender`  
`class ISimulationEditorExtender : public IModularFeature`  
_L30-73_
- inherits: `IModularFeature`
- desc: A simulation extender is an object responsible for extending certain editor features with respect to a certain type of clothing simulation. The supported simulation factory class should be returned from GetSupportedSimulationFactoryClass. The engine will call into various interface functions to perform editor functions as outlined in the interface API As this is a modular feature it should be registered under FClothingSystemEditorInterfaceModule::ExtenderFeatureName To be accessible through the clothing editor interface module.
- L34 _public prototype_ `virtual ~ISimulationEditorExtender() = default;`
- L40 _public prototype_ `virtual UClass* GetSupportedSimulationFactoryClass() = 0;` — Called to identify the type of clothing simulation this editor extender can support. Should return a class derived from UClothingSimulationFactory
- L47 _public prototype_ `virtual void ExtendViewportShowMenu(FMenuBuilder& InMenuBuilder, TSharedRef<IPersonaPreviewScene> InPreviewScene) = 0;` — Called from the editor to add simulation specific entries to the "Show" menu on the Persona viewport. @param InMenuBuilder - The menu builder for the show->clothing menu to extend @param InPreviewScene - The Persona preview scene from the editor, contains the current preview component
- L56 _public prototype_ `virtual void DebugDrawSimulation(const IClothingSimulationInterface* InSimulation, USkeletalMeshComponent* InOwnerComponent, FPrimitiveDrawInterface* PDI);` — Called from the editor when clothing is active to process any active debug drawing, recommended to use the show menu extension for controlling what data to draw @param InSimulation - The running clothing simulation @param InOwnerComponent - The component that owns the running clothing simulation @param PDI - The drawing interface to use
- L59 _public function_ `virtual void DebugDrawSimulation(const class IClothingSimulation* InSimulation, USkeletalMeshComponent* InOwnerComponent, FPrimitiveDrawInterface* PDI)` — `UE_DEPRECATED(5.7, "Use IClothingSimulationInterface instead.")`
- L69 _public prototype_ `virtual void DebugDrawSimulationTexts(const IClothingSimulationInterface* InSimulation, USkeletalMeshComponent* InOwnerComponent, FCanvas* Canvas, const FSceneView* SceneView);` — Called from the editor when clothing is active to process any active debug drawing of any text strings Recommended to use the show menu extension for controlling what data to draw @param InSimulation - The running clothing simulation @param InOwnerComponent - The component that owns the running clothing simulation @param Canvas - The canvas to use for drawing the text @param SceneView - The view on which to project the text
- L72 _public function_ `virtual void DebugDrawSimulationTexts(const class IClothingSimulation* InSimulation, USkeletalMeshComponent* InOwnerComponent, FCanvas* Canvas, const FSceneView* SceneView)` — `UE_DEPRECATED(5.7, "Use IClothingSimulationInterface instead.")`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API CLOTHINGSYSTEMEDITORINTERFACE_API`
