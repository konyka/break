# Plugins / ApexDestructionEditor

- module root: `Plugins/Runtime/ApexDestruction/Source/ApexDestructionEditor`
- headers: 6; symbols: 30
- symbol kinds: class=6, function=7, member=4, prototype=13
- PrivateDependencyModuleNames: APEX, ApexDestruction, ApexDestructionLib, AssetRegistry, AssetTools, ContentBrowser, Core, CoreUObject, DesktopPlatform, EditorFramework, EditorStyle, Engine, InputCore, PhysX, Projects, RHI, RenderCore, Slate, SlateCore, UnrealEd

### `Plugins/Runtime/ApexDestruction/Source/ApexDestructionEditor/Private/ActorFactoryDestructible.h` (Private)


#### class `UActorFactoryDestructible`  
`class UActorFactoryDestructible : public UActorFactory`  
_L13-23_
- reflection: `UCLASS(MinimalAPI, config=Editor)`
- inherits: `UActorFactory`
- L18 _private prototype_ `virtual void PostSpawnActor( UObject* Asset, AActor* NewActor ) override;`
- L19 _private prototype_ `virtual bool CanCreateActorFrom( const FAssetData& AssetData, FText& OutErrorMsg ) override;`
- L20 _private prototype_ `virtual UObject* GetAssetFromActorInstance(AActor* ActorInstance) override;`
- L21 _private prototype_ `virtual FQuat AlignObjectToSurfaceNormal(const FVector& InSurfaceNormal, const FQuat& ActorRotation) const override;`

### `Plugins/Runtime/ApexDestruction/Source/ApexDestructionEditor/Private/ApexDestructionEditorModule.h` (Private)


#### class `FDestructibleMeshEditorModule`  
`class UE_DEPRECATED(4.26, "APEX is deprecated. Destruction in future will be supported using Chaos Destruction.") FDestructibleMeshEditorModule : public IModuleInterface`  
_L24-71_
- inherits: `IModuleInterface`
- L29 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface
- L30 _public prototype_ `virtual void ShutdownModule() override;`
- L65 _public member_ `TSharedPtr<class IAssetTypeActions> AssetAction;` — PRAGMA_DISABLE_DEPRECATION_WARNINGS * Creates an instance of table editor object.  Only virtual so that it can be called across the DLL boundary. * * @param	Mode					Mode that this editor should operate in * @param	InitToolkitHost			When Mode is WorldCentric, this is the level editor instance to spawn this editor within * @param	Table					The table to start editing * * @return	Interface to the new table editor virtual TSharedRef<IDestructibleMeshEditor> CreateDestructibleMeshEditor( const EToolkitMode::Type Mode, const TSharedPtr< class IToolkitHost >& InitToolkitHost, class UDestructibleMesh* Table ); * Creates a DestructibleMesh from a StaticMesh * * @param InParent - parent object for the UDestructibleMesh * @param StaticMesh - the StaticMesh to convert * @param Name - the Unreal name for the UDestructibleMesh.  If Name == NAME_None, then a the StaticMesh name followed appended with "_Dest" will be used. * @param Flags - object flags for the UDestructibleMesh * @param OutErrorMsg - if it returns false, this string contains the error * * @return The newly created UDestructibleMesh if successful, NULL otherwise virtual class UDestructibleMesh*	CreateDestructibleMeshFromStaticMesh(UObject* InParent, UStaticMesh* StaticMesh, FName Name, EObjectFlags Flags, FText& OutErrorMsg); PRAGMA_ENABLE_DEPRECATION_WARNINGS Gets the extensibility managers for outside entities to extend static mesh editor's menus and toolbars virtual TSharedPtr<FExtensibilityManager> GetMenuExtensibilityMan
- L66 _public member_ `TSharedPtr<class FDestructibleMeshComponentBroker> DestructibleMeshComponentBroker;`

### `Plugins/Runtime/ApexDestruction/Source/ApexDestructionEditor/Private/AssetTypeActions_DestructibleMesh.h` (Private)


#### class `FAssetTypeActions_DestructibleMesh`  
`class FAssetTypeActions_DestructibleMesh : public FAssetTypeActions_Base`  
_L7-17_
- inherits: `FAssetTypeActions_Base`
- L11 _public function_ `virtual FText GetName() const override` — IAssetTypeActions Implementation
- L12 _public function_ `virtual FColor GetTypeColor() const override`
- L13 _public prototype_ `virtual UClass* GetSupportedClass() const override;`
- L14 _public function_ `virtual uint32 GetCategories() override`
- L15 _public prototype_ `virtual void OpenAssetEditor( const TArray<UObject*>& InObjects, TSharedPtr<class IToolkitHost> EditWithinLevelEditor = TSharedPtr<IToolkitHost>() ) override;`
- L16 _public function_ `virtual bool IsImportedAsset() const override`

### `Plugins/Runtime/ApexDestruction/Source/ApexDestructionEditor/Private/DestructibleMeshComponentBroker.h` (Private)


#### class `FDestructibleMeshComponentBroker`  
`class FDestructibleMeshComponentBroker : public IComponentAssetBroker`  
_L12-44_
- inherits: `IComponentAssetBroker`
- desc: FDestructibleMeshComponentBroker
- L15 _public function_ `UClass* GetSupportedAssetClass() override`
- L20 _public function_ `virtual bool AssignAssetToComponent(UActorComponent* InComponent, UObject* InAsset) override`
- L36 _public function_ `virtual UObject* GetAssetFromComponent(UActorComponent* InComponent) override`

### `Plugins/Runtime/ApexDestruction/Source/ApexDestructionEditor/Private/DestructibleMeshThumbnailRenderer.h` (Private)


#### class `UDestructibleMeshThumbnailRenderer`  
`class UDestructibleMeshThumbnailRenderer : public UDefaultSizedThumbnailRenderer`  
_L17-31_
- reflection: `UCLASS(config=Editor, MinimalAPI)`
- inherits: `UDefaultSizedThumbnailRenderer`
- L23 _private prototype_ `virtual void Draw(UObject* Object, int32 X, int32 Y, uint32 Width, uint32 Height, FRenderTarget*, FCanvas* Canvas, bool bAdditionalViewFamily) override;`
- L27 _private prototype_ `virtual void BeginDestroy() override;` — UObject implementation
- L30 _private member_ `class FDestructibleMeshThumbnailScene* ThumbnailScene;`

### `Plugins/Runtime/ApexDestruction/Source/ApexDestructionEditor/Private/DestructibleMeshThumbnailScene.h` (Private)


#### class `FDestructibleMeshThumbnailScene`  
`class FDestructibleMeshThumbnailScene : public FThumbnailPreviewScene`  
_L13-33_
- inherits: `FThumbnailPreviewScene`
- L17 _public prototype_ `FDestructibleMeshThumbnailScene();` — Constructor
- L21 _public prototype_ `void SetDestructibleMesh(class UDestructibleMesh* InMesh);` — Sets the skeletal mesh to use in the next CreateView()
- L26 _protected prototype_ `virtual void GetViewMatrixParameters(const float InFOVDegrees, FVector& OutOrigin, float& OutOrbitPitch, float& OutOrbitYaw, float& OutOrbitZoom) const override;` — FThumbnailPreviewScene implementation
- L31 _private member_ `class ADestructibleActor* PreviewActor;` — The skeletal mesh actor used to display all skeletal mesh thumbnails
