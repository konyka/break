# Plugins / ChaosFleshEditor

- module root: `Plugins/Experimental/ChaosFlesh/Source/ChaosFleshEditor`
- headers: 13; symbols: 74
- symbol kinds: class=13, function=7, member=17, namespace=9, prototype=28
- DynamicallyLoadedModuleNames: 
- PrivateDependencyModuleNames: ModelingComponents, USDClasses, USDUtilities, UnrealUSDWrapper
- PublicDependencyModuleNames: AdvancedPreviewScene, AssetDefinition, AssetRegistry, AssetTools, ChaosCaching, ChaosCachingUSD, ChaosFlesh, ChaosFleshEngine, ChaosFleshNodes, Core, CoreUObject, DataflowCore, DataflowEditor, DataflowEngine, DataflowEnginePlugin, DataflowSimulation, EditorFramework, EditorStyle, Engine, GeometryCache, GeometryCore, GraphEditor, InputCore, LevelEditor, MeshConversion, MeshDescription, Projects, PropertyEditor, RHI, RawMesh, RenderCore, SceneOutliner, SkeletonEditor, Slate, SlateCore, StaticMeshDescription, ToolMenus, UnrealEd

### `Plugins/Experimental/ChaosFlesh/Source/ChaosFleshEditor/Private/ChaosFlesh/Asset/ActorFactoryFlesh.h` (Private)


#### class `UActorFactoryFlesh`  
`class UActorFactoryFlesh : public UActorFactory`  
_L13-21_
- reflection: `UCLASS(MinimalAPI, config=Editor)`
- inherits: `UActorFactory`
- L18 _private prototype_ `virtual void PostSpawnActor( UObject* Asset, AActor* NewActor ) override;`
- L19 _private prototype_ `virtual bool CanCreateActorFrom( const FAssetData& AssetData, FText& OutErrorMsg ) override;`

### `Plugins/Experimental/ChaosFlesh/Source/ChaosFleshEditor/Private/ChaosFlesh/Asset/FleshDeformableInterfaceDetails.h` (Private)


#### class `FDeformableInterfaceDetails`  
`class FDeformableInterfaceDetails : public IDetailCustomization`  
_L12-20_
- inherits: `IDetailCustomization`
- L16 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L19 _public prototype_ `virtual void CustomizeDetails( IDetailLayoutBuilder& DetailBuilder ) override;` — IDetailCustomization interface

### `Plugins/Experimental/ChaosFlesh/Source/ChaosFleshEditor/Private/ChaosFlesh/Editor/FleshEditorStyle.h` (Private)


#### class `FChaosFleshEditorStyle`  
`class FChaosFleshEditorStyle final : public FSlateStyleSet`  
_L9-48_
- inherits: `FSlateStyleSet`
- L12 _public function_ `FChaosFleshEditorStyle() : FSlateStyleSet("ChaosFleshEditorStyle")`
- L25 _public function_ `~FChaosFleshEditorStyle()`
- L32 _public function_ `static FChaosFleshEditorStyle& Get()`
- L41 _public function_ `static void Destroy()`
- L47 _private member_ `static TOptional<FChaosFleshEditorStyle> Singleton;`

### `Plugins/Experimental/ChaosFlesh/Source/ChaosFleshEditor/Private/ChaosFleshRendering/FleshFiberFieldRenderableType.h` (Private)


#### class `UDataflowFleshFiberFieldRenderSettings`  
`class UDataflowFleshFiberFieldRenderSettings : public UDataflowRenderableTypeSettings`  
_L11-30_
- reflection: `UCLASS(MinimalAPI, AutoExpandCategories="")`
- inherits: `UDataflowRenderableTypeSettings`
- L17 _public member_ `bool bVisible = false;` — `UPROPERTY(EditAnywhere, Category = "FiberField")` — Controls the visibility of the fiber field
- L21 _public member_ `FLinearColor Color = FLinearColor::Red;` — `UPROPERTY(EditAnywhere, Category = "FiberField", meta = (EditCondition = "bVisible"))` — Color of the fibers
- L25 _public member_ `float LineThickness = 0.5f;` — `UPROPERTY(EditAnywhere, Category = "FiberField", meta = (EditCondition = "bVisible"))` — Line thickness of the fiber field vectors
- L29 _public member_ `float LengthScalar = 1.0f;` — `UPROPERTY(EditAnywhere, Category = "FiberField", meta = (EditCondition = "bVisible"))` — Scalar to control the length of the fiber field vectors

#### Free symbols / members of external scopes

- L32 _namespace_ `namespace UE`
- L32 _namespace_ `namespace Flesh` (scope `UE`)
- L32 _namespace_ `namespace Private` (scope `UE::Flesh`)
- L34 _prototype_ `void RegisterFleshFiberFieldRenderableTypes();` (scope `UE::Flesh::Private`)

### `Plugins/Experimental/ChaosFlesh/Source/ChaosFleshEditor/Private/ChaosFleshRendering/FleshTetrahedronRenderableType.h` (Private)


#### class `UDataflowFleshTetrahedronRenderSettings`  
`class UDataflowFleshTetrahedronRenderSettings : public UDataflowRenderableTypeSettings`  
_L11-26_
- reflection: `UCLASS(MinimalAPI, AutoExpandCategories="")`
- inherits: `UDataflowRenderableTypeSettings`
- L17 _public member_ `bool bVisible = false;` — `UPROPERTY(EditAnywhere, Category = "Tetrahedrons")` — Controls the visibility of the tetrahedrons
- L21 _public member_ `float LineThickness = 1.0f;` — `UPROPERTY(EditAnywhere, Category = "Tetrahedrons", meta = (EditCondition = "bVisible"))` — Thickness of lines displaying the tetrahedrons
- L25 _public member_ `FColor LineColor = FColor::Yellow;` — `UPROPERTY(EditAnywhere, Category = "Tetrahedrons", meta = (EditCondition = "bVisible"))` — Color of lines displaying the tetrahedrons

#### Free symbols / members of external scopes

- L28 _namespace_ `namespace UE`
- L28 _namespace_ `namespace Flesh` (scope `UE`)
- L28 _namespace_ `namespace Private` (scope `UE::Flesh`)
- L30 _prototype_ `void RegisterFleshTetrahedronRenderableTypes();` (scope `UE::Flesh::Private`)

### `Plugins/Experimental/ChaosFlesh/Source/ChaosFleshEditor/Private/ChaosFleshRendering/FleshVectorFieldRenderableType.h` (Private)


#### class `UDataflowFleshVectorFieldRenderSettings`  
`class UDataflowFleshVectorFieldRenderSettings : public UDataflowRenderableTypeSettings`  
_L11-26_
- reflection: `UCLASS(MinimalAPI, AutoExpandCategories="")`
- inherits: `UDataflowRenderableTypeSettings`
- L17 _public member_ `bool bVisible = false;` — `UPROPERTY(EditAnywhere, Category = "VectorField")` — Controls the visibility of the vector field
- L21 _public member_ `float LineThickness = 1.0f;` — `UPROPERTY(EditAnywhere, Category = "VectorField", meta = (EditCondition = "bVisible"))` — Thickness of lines displaying the vector field
- L25 _public member_ `float LengthScalar = 1.0f;` — `UPROPERTY(EditAnywhere, Category = "VectorField", meta = (EditCondition = "bVisible"))` — Scalar to modify the length of the vectors in the vector field

#### Free symbols / members of external scopes

- L28 _namespace_ `namespace UE`
- L28 _namespace_ `namespace Flesh` (scope `UE`)
- L28 _namespace_ `namespace Private` (scope `UE::Flesh`)
- L30 _prototype_ `void RegisterFleshVectorFieldRenderableTypes();` (scope `UE::Flesh::Private`)

### `Plugins/Experimental/ChaosFlesh/Source/ChaosFleshEditor/Public/ChaosFlesh/Asset/AssetDefinition_FleshAsset.h` (Public)


#### class `UAssetDefinition_FleshAsset`  
`class UAssetDefinition_FleshAsset : public UAssetDefinitionDefault`  
_L10-23_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L16 _private prototype_ `virtual FText GetAssetDisplayName() const override;`
- L17 _private prototype_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override;`
- L18 _private prototype_ `virtual FLinearColor GetAssetColor() const override;`
- L19 _private prototype_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override;`
- L20 _private prototype_ `virtual UThumbnailInfo* LoadThumbnailInfo(const FAssetData& InAssetData) const override;`
- L22 _private prototype_ `virtual EAssetCommandResult OpenAssets(const FAssetOpenArgs& OpenArgs) const override;`

### `Plugins/Experimental/ChaosFlesh/Source/ChaosFleshEditor/Public/ChaosFlesh/Asset/FleshAssetFactory.h` (Public)


#### class `UFleshAssetFactory`  
`class UFleshAssetFactory : public UFactory`  
_L17-24_
- reflection: `UCLASS()`
- inherits: `UFactory`
- desc: Factory for FleshAsset
- L22 _private prototype_ `virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;`

### `Plugins/Experimental/ChaosFlesh/Source/ChaosFleshEditor/Public/ChaosFlesh/Asset/FleshAssetThumbnailRenderer.h` (Public)


#### class `UFleshAssetThumbnailRenderer`  
`class UFleshAssetThumbnailRenderer : public UDefaultSizedThumbnailRenderer`  
_L20-33_
- reflection: `UCLASS(config = Editor, MinimalAPI)`
- inherits: `UDefaultSizedThumbnailRenderer`
- L25 _private prototype_ `virtual void Draw(UObject* Object, int32 X, int32 Y, uint32 Width, uint32 Height, FRenderTarget* RenderTarget, FCanvas* Canvas, bool bAdditionalViewFamily) override;`
- L29 _private prototype_ `virtual void BeginDestroy() override;`
- L32 _private member_ `FFleshAssetThumbnailScene* ThumbnailScene;`

### `Plugins/Experimental/ChaosFlesh/Source/ChaosFleshEditor/Public/ChaosFlesh/Asset/FleshAssetThumbnailScene.h` (Public)


#### class `FFleshAssetThumbnailScene`  
`class FFleshAssetThumbnailScene : public FThumbnailPreviewScene`  
_L11-27_
- inherits: `FThumbnailPreviewScene`
- L15 _public prototype_ `FFleshAssetThumbnailScene();` — Constructor
- L18 _public prototype_ `void SetFleshAsset(UFleshAsset* FleshAsset);` — Sets the geometry collection to use in the next CreateView()
- L22 _protected prototype_ `virtual void GetViewMatrixParameters(const float InFOVDegrees, FVector& OutOrigin, float& OutOrbitPitch, float& OutOrbitYaw, float& OutOrbitZoom) const override;` — FThumbnailPreviewScene implementation
- L26 _private member_ `AFleshActor* PreviewActor;` — The actor used to display all geometry collection thumbnails

### `Plugins/Experimental/ChaosFlesh/Source/ChaosFleshEditor/Public/ChaosFlesh/ChaosFleshEditorPlugin.h` (Public)


#### class `IChaosFleshEditorPlugin`  
`class IChaosFleshEditorPlugin : public IModuleInterface`  
_L20-65_
- inherits: `IModuleInterface`
- desc: The public interface to this module
- L23 _public prototype_ `virtual void StartupModule();`
- L24 _public prototype_ `virtual void ShutdownModule();`
- L32 _public function_ `static inline IChaosFleshEditorPlugin& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L42 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use
- L47 _public function_ `TSharedPtr<FSlateStyleSet> GetStyleSet()`
- L49 _public prototype_ `static FName GetEditorStyleName();`
- L50 _public prototype_ `static const ISlateStyle* GetEditorStyle();`
- L53 _private prototype_ `void RegisterMenus();`
- L56 _private member_ `TArray<IConsoleObject*> EditorCommands;`
- L59 _private member_ `FAssetTypeActions_ChaosDeformableSolver* ChaosDeformableSolverAssetActions;` — Asset actions for new asset types
- L62 _private member_ `TSharedPtr<FSlateStyleSet> StyleSet;` — Styleset for flesh tool brushes/fonts etc.
- L64 _private member_ `FDelegateHandle DataflowMenusHandle;`

### `Plugins/Experimental/ChaosFlesh/Source/ChaosFleshEditor/Public/ChaosFlesh/Cmd/ChaosFleshCommands.h` (Public)


#### class `FChaosFleshCommands`  
`class FChaosFleshCommands`  
_L9-47_
- desc: The public interface to this module
- L17 _public prototype_ `static void ImportFile(const TArray<FString>& Args, UWorld* World);` — Import file.
- L30 _public prototype_ `static void FindQualifyingTetrahedra(const TArray<FString>& Args, UWorld* World);` — Commmand invoked from "FChaosDeformableCommands.FindHighAspectRatioTetrahedra", uses the selected FleshComponent and outputs tetrahedra indices to the log. @param Args - Supported arguments: 'MaxAR <float>' selects tetrahedra with aspect ratio greater than this value. 'MinVol <float>' selects tetrahedra with (signed) volume less than this value. 'XCoordGT <float>', 'YCoordGT <float>', 'ZCoordGT <float>' selects tetrahedra with all vertices greater than these values. 'XCoordLT <float>', 'YCoordLT <float>', 'ZCoordLT <float>' selects tetrahedra with all vertices less than these values. 'HideTets' adds selected tets to the selected flesh component's list of tets to skip drawing. @param World
- L45 _public prototype_ `static void CreateGeometryCache(const TArray<FString>& Args, UWorld* World);` — Create GeometryCache asset from a cached flesh simulation. Command invoked from "FChaosDeformableCommands.CreateGeometryCache", uses the selected Actor's FleshComponent and SkeletalMeshComponent, optionally along with a Chaos Cache Manager. Deforms the SkeletalMesh's import geometry by the cached simulation results, and stores that surface in a new GeometryCache asset.  The rest collection asset on the flesh component(s) needs to contain deformer bindings for the import geometry. @param Args - Supported arguments: 'UsdFile </path/to/file.usd>' overrides which usd file to use, rather than inferring it from a chaos cache manager. 'FrameRate 24' overrides the default 24 FPS frame rate for the output cache samples. 'MaxNumFrames <int>' clamps the number of frames to MaxNumFrames.

### `Plugins/Experimental/ChaosFlesh/Source/ChaosFleshEditor/Public/ChaosFlesh/Cmd/FleshAssetConversion.h` (Public)


#### class `FFleshAssetConversion`  
`class FFleshAssetConversion`  
_L12-28_
- desc: The public interface to this module
- L20 _public prototype_ `static TUniquePtr<FFleshCollection> ImportTetFromFile(const FString& Filename);` — Supports reading .tet and .geo (compatible with version 19). Currently disabled.
