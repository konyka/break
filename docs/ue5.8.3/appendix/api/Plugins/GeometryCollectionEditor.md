# Plugins / GeometryCollectionEditor

- module root: `Plugins/Experimental/GeometryCollectionPlugin/Source/GeometryCollectionEditor`
- headers: 18; symbols: 185
- symbol kinds: class=18, enum=1, enumerator=4, function=17, macro=4, member=42, namespace=3, prototype=93, typedef=3
- PrivateDependencyModuleNames: ContentBrowser, DataflowMedialSkeleton, DynamicMesh, EditorScriptingUtilities, FractureEngine, GeometryCollectionNodes, GeometryCore, GeometryFramework, MeshModelingTools, ModelingComponents, ModelingComponentsEditorOnly, ModelingToolsEditorMode
- PublicDependencyModuleNames: AssetDefinition, AssetRegistry, AssetTools, Chaos, Core, CoreUObject, DataflowCore, DataflowEditor, DataflowEngine, EditorFramework, EditorStyle, Engine, GeometryCollectionEngine, GraphEditor, InputCore, LevelEditor, MeshDescription, PropertyEditor, RHI, RawMesh, RenderCore, SceneOutliner, Slate, SlateCore, StaticMeshDescription, ToolMenus, UnrealEd

### `Plugins/Experimental/GeometryCollectionPlugin/Source/GeometryCollectionEditor/Private/GeometryCollection/ActorFactoryGeometryCollection.h` (Private)


#### class `UActorFactoryGeometryCollection`  
`class UActorFactoryGeometryCollection : public UActorFactory`  
_L15-23_
- reflection: `UCLASS(MinimalAPI, config=Editor)`
- inherits: `UActorFactory`
- L20 _private prototype_ `virtual void PostSpawnActor( UObject* Asset, AActor* NewActor ) override;`
- L21 _private prototype_ `virtual bool CanCreateActorFrom( const FAssetData& AssetData, FText& OutErrorMsg ) override;`

### `Plugins/Experimental/GeometryCollectionPlugin/Source/GeometryCollectionEditor/Private/GeometryCollection/DetailCustomizations/GeometryCollectionCustomization.h` (Private)


#### class `FGeometryCollectionCustomization`  
`class FGeometryCollectionCustomization : public IDetailCustomization`  
_L11-26_
- inherits: `IDetailCustomization`
- L14 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L15 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder);`
- L18 _private prototype_ `bool IsApplyNeeded() const;`
- L19 _private prototype_ `FReply OnApplyChanges();`
- L20 _private prototype_ `void OnCheckStateChanged(ECheckBoxState InNewState);`
- L21 _private prototype_ `EVisibility ApplyButtonVisibility() const;`
- L23 _private member_ `bool bManualApplyActivated = false;`
- L25 _private member_ `TArray<TWeakObjectPtr<UObject>> ObjectsCustomized;`

### `Plugins/Experimental/GeometryCollectionPlugin/Source/GeometryCollectionEditor/Private/GeometryCollection/DetailCustomizations/WarningMessageCustomization.h` (Private)


#### class `FWarningMessageCustomization`  
`class FWarningMessageCustomization : public IPropertyTypeCustomization`  
_L9-16_
- inherits: `IPropertyTypeCustomization`
- desc: Details customization for warning message in the UI.
- L12 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L14 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L15 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`

### `Plugins/Experimental/GeometryCollectionPlugin/Source/GeometryCollectionEditor/Private/GeometryCollection/GeometryCollectionEditorStyle.h` (Private)


#### class `FGeometryCollectionEditorStyle`  
`class FGeometryCollectionEditorStyle final : public FSlateStyleSet`  
_L7-46_
- inherits: `FSlateStyleSet`
- L10 _public function_ `FGeometryCollectionEditorStyle() : FSlateStyleSet("GeometryCollectionEditorStyle")`
- L23 _public function_ `virtual ~FGeometryCollectionEditorStyle()`
- L30 _public function_ `static FGeometryCollectionEditorStyle& Get()`
- L39 _public function_ `static void Destroy()`
- L45 _private member_ `static TOptional<FGeometryCollectionEditorStyle> Singleton;`

### `Plugins/Experimental/GeometryCollectionPlugin/Source/GeometryCollectionEditor/Private/GeometryCollection/GeometryCollectionSelectRigidBodyEdMode.h` (Private)


#### class `FGeometryCollectionSelectRigidBodyEdMode`  
`class FGeometryCollectionSelectRigidBodyEdMode : public FEdMode`  
_L11-57_
- inherits: `FEdMode`
- L14 _public member_ `static const FEditorModeID EditorModeID;`
- L17 _public prototype_ `static bool CanActivateMode();` — Check whether this mode can be activated (needs to run in SIE/PIE).
- L20 _public prototype_ `static void ActivateMode(TSharedRef<IPropertyHandle> PropertyHandleId, TSharedRef<IPropertyHandle> PropertyHandleSolver, TFunction<void()> OnEnterMode, TFunction<void()> OnExitMode);` — Activate this editor mode.
- L23 _public prototype_ `static void DeactivateMode();` — Deactivate this editor mode.
- L26 _public prototype_ `static bool IsModeActive();` — Return whether this editor mode is active.
- L28 _public function_ `FGeometryCollectionSelectRigidBodyEdMode() : bIsHoveringGeometryCollection(false)`
- L29 _public prototype_ `virtual ~FGeometryCollectionSelectRigidBodyEdMode() = default;`
- L32 _public function_ `virtual void Enter() override` — FEdMode interface
- L33 _public function_ `virtual void Exit() override`
- L34 _public function_ `virtual bool IsCompatibleWith(FEditorModeID ) const override`
- L36 _public function_ `virtual bool GetCursor(EMouseCursor::Type& OutCursor) const`
- L38 _public function_ `virtual bool UsesTransformWidget() const override`
- L39 _public function_ `virtual bool UsesTransformWidget(UE::Widget::EWidgetMode ) const override`
- L41 _public prototype_ `virtual void Tick(FEditorViewportClient* ViewportClient, float DeltaTime) override;`
- L43 _public prototype_ `virtual bool HandleClick(FEditorViewportClient* InViewportClient, HHitProxy* HitProxy, const FViewportClick& Click) override;`
- L44 _public prototype_ `virtual bool MouseMove(FEditorViewportClient* ViewportClient, FViewport* Viewport, int32 x, int32 y) override;`
- L46 _public function_ `virtual bool IsSelectionAllowed(AActor* , bool ) const override`
- L49 _private prototype_ `void EnableTransformSelectionMode(bool bEnable);`
- L52 _private member_ `static const int32 MessageKey;`
- L53 _private member_ `TWeakPtr<IPropertyHandle> PropertyHandleId;` — Handle of the property that will get updated with the selected rigid body id
- L54 _private member_ `TWeakPtr<IPropertyHandle> PropertyHandleSolver;` — Handle of the property that will get updated with the selected solver actor
- L55 _private member_ `TFunction<void()> OnExitMode;` — Callback function called when the edit mode is deactivated
- L56 _private member_ `bool bIsHoveringGeometryCollection;`

### `Plugins/Experimental/GeometryCollectionPlugin/Source/GeometryCollectionEditor/Private/GeometryCollectionRendering/DataflowMedialSkeletonRenderableType.h` (Private)


#### enum `EDataflowMedialSkeletonSpheresColorMethodType`  
`enum class EDataflowMedialSkeletonSpheresColorMethodType : uint8`  
_L11-17_
- reflection: `UENUM(BlueprintType)`
- L13 _public enumerator_ `Constant UMETA(DisplayName = "Constant")`
- L14 _public enumerator_ `Random UMETA(DisplayName = "Random")`
- L15 _public enumerator_ `BySize UMETA(DisplayName = "By Size")`
- L16 _public enumerator_ `ByIDs UMETA(DisplayName = "By IDs")`

#### class `UDataflowMedialSkeletonRenderSettings`  
`class UDataflowMedialSkeletonRenderSettings : public UDataflowRenderableTypeSettings`  
_L20-98_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UDataflowRenderableTypeSettings`
- L24 _private prototype_ `UDataflowMedialSkeletonRenderSettings(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());`
- L29 _public member_ `bool bWireframe = false;` — `UPROPERTY(EditAnywhere, Category = "Display")` — Display surface as wireframe
- L33 _public member_ `float Transparency = 0.75f;` — `UPROPERTY(EditAnywhere, Category = "Display", meta = (UIMin = 0, ClampMin = 0, UIMax = 1, ClampMax = 1))` — Transparency
- L37 _public member_ `bool bShowSpheres = true;` — `UPROPERTY(EditAnywhere, Category = "Spheres")` — Display the medial spheres
- L41 _public member_ `EDataflowMedialSkeletonSpheresColorMethodType SpheresColorMethod = EDataflowMedialSkeletonSpheresColorMethodType::Constant;` — `UPROPERTY(EditAnywhere, Category = "Spheres")` — Method for coloring the medial spheres
- L45 _public member_ `FLinearColor Color = FLinearColor(0.2f, 0.97f, 1.0f);` — `UPROPERTY(EditAnywhere, Category = "Spheres", meta = (EditCondition = "SpheresColorMethod == EDataflowMedialSkeletonSpheresColorMethodType::Constant"))` — Constant color for the spheres
- L49 _public member_ `int32 RandomSeed = 0;` — `UPROPERTY(EditAnywhere, Category = "Spheres", meta = (UIMin = 0, EditCondition = "SpheresColorMethod == EDataflowMedialSkeletonSpheresColorMethodType::Random"))` — Seed for the random color
- L53 _public member_ `bool bShowCenters = true;` — `UPROPERTY(EditAnywhere, Category = "Centers", meta = (InlineEditConditionToggle))` — Show medial spheres centers
- L57 _public member_ `FLinearColor CentersColor = FLinearColor(0.0f, 0.466f, 1.0f);` — `UPROPERTY(EditAnywhere, Category = "Centers", meta = (EditCondition = bShowCenters))` — Color of the centers
- L61 _public member_ `float Size = 10.0f;` — `UPROPERTY(EditAnywhere, Category = "Centers", meta = (UIMin = 0.01f, ClampMin = 0.01f))` — Size of the centers
- L65 _public member_ `bool bShowIDs = false;` — `UPROPERTY(EditAnywhere, Category = "Centers", meta = (InlineEditConditionToggle))` — Display medial sphere IDs
- L69 _public member_ `FLinearColor IDsColor = FLinearColor(0.0, 1.0, 1.0);` — `UPROPERTY(EditAnywhere, Category = "Centers", meta = (EditCondition = bShowIDs))` — Color of the IDs text
- L73 _public member_ `bool bShowLines = true;` — `UPROPERTY(EditAnywhere, Category = "Lines", meta = (InlineEditConditionToggle))` — Show connections
- L77 _public member_ `FLinearColor LinesColor = FLinearColor(0.15f, 0.0f, 1.0f);` — `UPROPERTY(EditAnywhere, Category = "Lines", meta = (EditCondition = bShowLines))` — Color of the connections
- L81 _public member_ `float LineThickness = 2.0;` — `UPROPERTY(EditAnywhere, Category = "Lines", meta = (UIMin = 1.f, ClampMin = 1.f))` — Line thickness for the connections
- L85 _public member_ `bool bShowTriangles = true;` — `UPROPERTY(EditAnywhere, Category = "Triangles", meta = (InlineEditConditionToggle))` — Display triangles
- L89 _public member_ `FLinearColor TrianglesColor = FLinearColor(1.0, 0.0, 1.0);` — `UPROPERTY(EditAnywhere, Category = "Triangles", meta = (EditCondition = bShowTriangles))` — Color of the triangles
- L93 _public member_ `float TrianglesLineThickness = 6.0;` — `UPROPERTY(EditAnywhere, Category = "Triangles", meta = (UIMin = 1.f, ClampMin = 1.f))` — Line thickness for the triangles
- L97 _public member_ `FLinearColorRamp ColorRamp;` — `UPROPERTY(EditAnywhere, Category = "Color", meta = (EditCondition = "SpheresColorMethod == EDataflowMedialSkeletonSpheresColorMethodType::BySize || SpheresColorMethod == EDataflowMedialSkeletonSpheresColorMethodType::ByIDs", EditConditionHides))` — Color ramp for coloring by size/IDs

#### Free symbols / members of external scopes

- L100 _namespace_ `namespace UE`
- L100 _namespace_ `namespace Dataflow` (scope `UE`)
- L100 _namespace_ `namespace Private` (scope `UE::Dataflow`)
- L102 _prototype_ `void RegisterMedialSkeletonRenderableType();` (scope `UE::Dataflow::Private`)

### `Plugins/Experimental/GeometryCollectionPlugin/Source/GeometryCollectionEditor/Public/GeometryCollection/AssetDefinition_GeometryCollection.h` (Public)


#### class `UAssetDefinition_GeometryCollection`  
`class UAssetDefinition_GeometryCollection : public UAssetDefinitionDefault`  
_L12-26_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAssetDefinitionDefault`
- L18 _private prototype_ `virtual FText GetAssetDisplayName() const override;`
- L19 _private prototype_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override;`
- L20 _private prototype_ `virtual FLinearColor GetAssetColor() const override;`
- L21 _private prototype_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override;`
- L22 _private prototype_ `virtual UThumbnailInfo* LoadThumbnailInfo(const FAssetData& InAssetData) const override;`
- L24 _private prototype_ `virtual FAssetOpenSupport GetAssetOpenSupport(const FAssetOpenSupportArgs& OpenSupportArgs) const;`
- L25 _private prototype_ `virtual EAssetCommandResult OpenAssets(const FAssetOpenArgs& OpenArgs) const override;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API GEOMETRYCOLLECTIONEDITOR_API`

### `Plugins/Experimental/GeometryCollectionPlugin/Source/GeometryCollectionEditor/Public/GeometryCollection/DetailCustomizations/GeomComponentCacheCustomization.h` (Public)


#### class `FGeomComponentCacheParametersCustomization`  
`class FGeomComponentCacheParametersCustomization : public IPropertyTypeCustomization, public FGCObject`  
_L11-43_
- inherits: `IPropertyTypeCustomization,FGCObject`
- L15 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L18 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override;` — IPropertyTypeCustomization
- L19 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> PropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L22 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;` — FGCObject
- L23 _public function_ `virtual FString GetReferencerName() const override`
- L31 _private prototype_ `const UGeometryCollection* GetCollection() const;` — Get the collection attached to the parameter struct.
- L32 _private prototype_ `TObjectPtr<const UGeometryCollection>* GetCollectionRef() const;`
- L35 _private prototype_ `bool ShouldFilterAsset(const FAssetData& InData) const;` — Whether we filter out caches. Condition is that the Id guids match.
- L39 _private prototype_ `void CheckTagsMatch(const UGeometryCollection* InCollection, const UGeometryCollectionCache* InCache, bool& bOutIdsMatch, bool& bOutStatesMatch);` — Check the conditions required for a cache to be compatible with recording and playback. bOutIdsMatch describes whether the cache is compatible at all and bOutStatesMatch describes whether playback is possible using that cache and collection combo.
- L42 _private member_ `TSharedPtr<IPropertyHandle> TargetCacheHandle;` — Handle to the target cache property inside the parameters struct

### `Plugins/Experimental/GeometryCollectionPlugin/Source/GeometryCollectionEditor/Public/GeometryCollection/GeometryCollectionAssetBroker.h` (Public)


#### class `FGeometryCollectionAssetBroker`  
`class FGeometryCollectionAssetBroker : public IComponentAssetBroker`  
_L9-17_
- inherits: `IComponentAssetBroker`
- desc: AssetBroker class for GeometryCollection assets
- L13 _public prototype_ `UClass* GetSupportedAssetClass() override;`
- L14 _public prototype_ `virtual bool AssignAssetToComponent(UActorComponent* InComponent, UObject* InAsset) override;`
- L15 _public prototype_ `virtual UObject* GetAssetFromComponent(UActorComponent* InComponent) override;`

### `Plugins/Experimental/GeometryCollectionPlugin/Source/GeometryCollectionEditor/Public/GeometryCollection/GeometryCollectionCacheFactory.h` (Public)


#### class `UGeometryCollectionCacheFactory`  
`class UGeometryCollectionCacheFactory : public UFactory`  
_L14-44_
- reflection: `UCLASS(Experimental)`
- inherits: `UFactory`
- L23 _public member_ `TObjectPtr<UGeometryCollection> TargetCollection;` — `UPROPERTY()`
- L27 _public prototype_ `UGeometryCollectionCacheFactory();`
- L30 _public prototype_ `virtual bool CanCreateNew() const override;` — UFactory Interface
- L31 _public prototype_ `virtual bool FactoryCanImport(const FString& Filename) override;`
- L32 _public prototype_ `virtual bool ShouldShowInNewMenu() const override;`
- L33 _public prototype_ `virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;`
- L34 _public prototype_ `virtual bool ConfigureProperties() override;`
- L40 _private prototype_ `void OnConfigSelection(const FAssetData& InSelectedAssetData);` — Callback from window created in ConfigureProperties once a user picks a target Geometry Collection
- L43 _private member_ `TSharedPtr<SWindow> PickerWindow;` — Window created in ConfigureProperties for target selection

### `Plugins/Experimental/GeometryCollectionPlugin/Source/GeometryCollectionEditor/Public/GeometryCollection/GeometryCollectionCommands.h` (Public)


#### class `FGeometryCollectionCommands`  
`class FGeometryCollectionCommands`  
_L15-152_
- desc: The public interface to this module
- L23 _public prototype_ `static void ToString(UWorld * World);` — Command invoked from "GeometryCollection.ToString", uses the selected GeometryCollectionActor to output the RestCollection to the Log @param World
- L29 _public prototype_ `static void WriteToHeaderFile(const TArray<FString>& Args, UWorld * World);` — Command invoked from "GeometryCollection.WriteToHeaderFile", uses the selected GeometryCollectionActor to output the RestCollection to a header file @param World
- L35 _public prototype_ `static void WriteToOBJFile(const TArray<FString>& Args, UWorld * World);` — Command invoked from "GeometryCollection.WriteToOBJFile", uses the selected GeometryCollectionActor to output the RestCollection to an OBJ file @param World
- L41 _public prototype_ `static void PrintStatistics(UWorld * World);` — Command invoked from "GeometryCollectionAlgo.PrintStatistics", uses the selected GeometryCollectionActor to output statistics @param World
- L47 _public prototype_ `static void PrintDetailedStatistics(UWorld * World);` — Command invoked from "GeometryCollectionAlgo.PrintDetailedStatistics", uses the selected GeometryCollectionActor to output detailed statistics @param World
- L53 _public prototype_ `static void PrintDetailedStatisticsSummary(UWorld * World);` — Command invoked from "GeometryCollectionAlgo.PrintDetailedStatisticsSummary", uses the selected GeometryCollectionActor to output detailed statistics @param World
- L59 _public prototype_ `static void DeleteCoincidentVertices(const TArray<FString>& Args, UWorld * World);` — @param World
- L77 _public prototype_ `static void SetNamedAttributeValues(const TArray<FString>& Args, UWorld* World);` — Command to set attributes within a named group. GeometryCollection.SetNamedAttributeValues <type> <Attribute> <Group> <Value> [<Regex Attribute> <Regex>] Where type is in SupportedAttributeTypes (bool,int32,float) and <Attribute> exists within <Group> with optional regex matching against <RegexAttribute> within <Group> For Example : GeometryCollection.SetNamedAttributeValues bool SimulatableParticlesAttribute Transform 0 BoneName Cube_1_1 This will set the bool attribute SimulatableParticlesAttribute of the Transform group to false where BoneName equals Cube_1_1
- L83 _public prototype_ `static void DeleteZeroAreaFaces(const TArray<FString>& Args, UWorld * World);` — @param World
- L89 _public prototype_ `static void DeleteHiddenFaces(UWorld * World);` — @param World
- L95 _public prototype_ `static void DeleteStaleVertices(UWorld * World);` — @param World
- L100 _public prototype_ `static void SplitAcrossYZPlane(UWorld * World);` — Split across xz-plane
- L105 _public prototype_ `static void DeleteGeometry(const TArray<FString>& Args, UWorld* World);` — Remove the selected geometry entry
- L110 _public prototype_ `static void SelectAllGeometry(const TArray<FString>& Args, UWorld* World);` — Select all geometry in hierarchy
- L115 _public prototype_ `static void SelectNone(const TArray<FString>& Args, UWorld* World);` — Select no geometry in hierarchy
- L120 _public prototype_ `static void SelectLessThenVolume(const TArray<FString>& Args, UWorld* World);` — Select no geometry in hierarchy
- L125 _public prototype_ `static void SelectInverseGeometry(const TArray<FString>& Args, UWorld* World);` — Select inverse of currently selected geometry in hierarchy
- L130 _public prototype_ `static int32 EnsureSingleRoot(UGeometryCollection* RestCollection);` — Ensure single root.
- L135 _public prototype_ `static void BuildProximityDatabase(const TArray<FString>& Args, UWorld * World);` — Build Proximity Database
- L140 _public prototype_ `static void SetupNestedBoneAsset(UWorld * World);` — Test Bone Asset
- L145 _public prototype_ `static void SetupTwoClusteredCubesAsset(UWorld * World);` — Setup two clustered cubes
- L150 _public prototype_ `static void HealGeometry(UWorld * World);` — Remove Holes

#### Free symbols / members of external scopes

- L6 _macro_ `#define UE_API GEOMETRYCOLLECTIONEDITOR_API`

### `Plugins/Experimental/GeometryCollectionPlugin/Source/GeometryCollectionEditor/Public/GeometryCollection/GeometryCollectionConversion.h` (Public)


#### class `FGeometryCollectionConversion`  
`class FGeometryCollectionConversion`  
_L20-84_
- desc: The public interface to this module
- L31 _public prototype_ `static void AppendStaticMesh(const UStaticMesh* StaticMesh, const TArray<UMaterialInterface*>& Materials, const FTransform& StaticMeshTransform, UGeometryCollection* GeometryCollectionObject, bool ReindexMaterials = true);` — Appends a static mesh to a GeometryCollectionComponent. @param StaticMesh : Const mesh to read vertex/normals/index data from @param Materials : Materials fetched from the StaticMeshComponent used to configure this geometry @param StaticMeshTransform : Mesh transform. @param GeometryCollection  : Collection to append the mesh into.
- L39 _public prototype_ `static void AppendStaticMesh(const UStaticMesh * StaticMesh, const UStaticMeshComponent *StaticMeshComponent, const FTransform & StaticMeshTransform, UGeometryCollection * GeometryCollection, bool ReindexMaterials = true);` — Appends a static mesh to a GeometryCollectionComponent. @param StaticMeshComponent : Const mesh to read vertex/normals/index data from @param StaticMeshTransform : Mesh transform. @param GeometryCollection  : Collection to append the mesh into.
- L47 _public prototype_ `static void AppendSkeletalMesh(const USkeletalMesh* SkeletalMesh, const USkeletalMeshComponent *SkeletalMeshComponent, const FTransform & SkeletalMeshTransform, UGeometryCollection * GeometryCollection, bool ReindexMaterials = true);` — Appends a skeletal mesh to a GeometryCollectionComponent. @param SkeletalMeshComponent : Const mesh to read vertex/normals/index data from @param SkeletalMeshTransform : Mesh transform. @param GeometryCollection    : Collection to append the mesh into.
- L56 _public prototype_ `static void AppendGeometryCollection(const UGeometryCollection* SourceGeometryCollection, const TArray<UMaterialInterface*>& Materials, const FTransform& GeometryCollectionTransform, UGeometryCollection* TargetGeometryCollectionObject, bool ReindexMaterials = true);` — Appends a GeometryCollection to a GeometryCollectionComponent. @param SourceGeometryCollection : Const GeometryCollection to read vertex/normals/index data from @param Materials : Materials fetched from the GeometryCollectionComponent used to configure this geometry @param GeometryCollectionTransform : GeometryCollection transform. @param TargetGeometryCollection  : Collection to append the GeometryCollection into.
- L64 _public prototype_ `static void AppendGeometryCollection(const UGeometryCollection* SourceGeometryCollection, const UGeometryCollectionComponent* GeometryCollectionComponent, const FTransform& GeometryCollectionTransform, UGeometryCollection* TargetGeometryCollectionObject, bool ReindexMaterials = true);` — Appends a GeometryCollection to a GeometryCollectionComponent. @param GeometryCollectionComponent : Const GeometryCollection to read vertex/normals/index data from @param GeometryCollectionTransform : GeometryCollection transform. @param TargetGeometryCollection  : Collection to append the GeometryCollection into.
- L71 _public prototype_ `static void CreateGeometryCollectionCommand(UWorld * World);` — Command invoked from "GeometryCollection.CreatGeometryCollection", uses the selected Actors to create a GeometryCollection Asset @param World
- L77 _public prototype_ `static void CreateFromSelectedActorsCommand(UWorld * World);` — Command invoked from "GeometryCollection.CreateFromSelectedActors", uses the selected Actors to create a GeometryCollection Asset @param World
- L83 _public prototype_ `static void CreateFromSelectedAssetsCommand(UWorld * World);` — Command invoked from "GeometryCollection.CreateFromSelectedAssets", uses the selected Assets to create a GeometryCollection Asset @param World

#### Free symbols / members of external scopes

- L6 _macro_ `#define UE_API GEOMETRYCOLLECTIONEDITOR_API`
- L14 _typedef_ `typedef TTuple<const UStaticMesh *, const UStaticMeshComponent *, FTransform> GeometryCollectionStaticMeshConversionTuple;`
- L15 _typedef_ `typedef TTuple<const USkeletalMesh *, const USkeletalMeshComponent *, FTransform> GeometryCollectionSkeletalMeshConversionTuple;`

### `Plugins/Experimental/GeometryCollectionPlugin/Source/GeometryCollectionEditor/Public/GeometryCollection/GeometryCollectionEditorPlugin.h` (Public)


#### class `IGeometryCollectionEditorPlugin`  
`class IGeometryCollectionEditorPlugin : public IModuleInterface`  
_L25-80_
- inherits: `IModuleInterface`
- desc: The public interface to this module
- L28 _public prototype_ `virtual void StartupModule();`
- L29 _public prototype_ `virtual void ShutdownModule();`
- L37 _public function_ `static inline IGeometryCollectionEditorPlugin& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L47 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use
- L52 _public function_ `TSharedPtr<FSlateStyleSet> GetStyleSet()`
- L54 _public prototype_ `static FName GetEditorStyleName();`
- L55 _public prototype_ `static const ISlateStyle* GetEditorStyle();`
- L58 _private prototype_ `void RegisterMenus();`
- L60 _private prototype_ `void CreateGeometrySelectionMenu(FMenuBuilder& InMenuBuilder);`
- L61 _private prototype_ `TSharedRef<FExtender> OnExtendLevelEditorViewMenu(const TSharedRef<FUICommandList> InCommandList);`
- L64 _private member_ `TArray<IConsoleObject*> EditorCommands;`
- L67 _private member_ `FGeometryCollectionAssetBroker* AssetBroker;` — Asset actions for new asset types
- L71 _private member_ `FTargetCacheProviderEditor TargetCacheProvider;` — Modular features Provider for new caches requested from other modules
- L75 _private member_ `TSharedPtr<FSlateStyleSet> StyleSet;` — Styleset for geom collection tool brushes/fonts etc.
- L77 _private member_ `FLevelEditorModule::FLevelEditorMenuExtender ViewMenuExtender;`
- L78 _private member_ `FDelegateHandle ViewMenuExtenderHandle;`
- L79 _private member_ `FDelegateHandle DataflowMenusHandle;`

### `Plugins/Experimental/GeometryCollectionPlugin/Source/GeometryCollectionEditor/Public/GeometryCollection/GeometryCollectionFactory.h` (Public)


#### class `UGeometryCollectionFactory`  
`class UGeometryCollectionFactory : public UFactory`  
_L26-36_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UFactory`
- L31 _private prototype_ `virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;`
- L34 _private prototype_ `static UGeometryCollection* StaticFactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn);`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API GEOMETRYCOLLECTIONEDITOR_API`
- L19 _typedef_ `typedef TTuple<const UGeometryCollection *, const UGeometryCollectionComponent *, FTransform> GeometryCollectionTuple;`

### `Plugins/Experimental/GeometryCollectionPlugin/Source/GeometryCollectionEditor/Public/GeometryCollection/GeometryCollectionProviderEditor.h` (Public)


#### class `FTargetCacheProviderEditor`  
`class FTargetCacheProviderEditor : public ITargetCacheProvider`  
_L7-13_
- inherits: `ITargetCacheProvider`
- L11 _public prototype_ `virtual UGeometryCollectionCache* GetCacheForCollection(const UGeometryCollection* InCollection) override;`

### `Plugins/Experimental/GeometryCollectionPlugin/Source/GeometryCollectionEditor/Public/GeometryCollection/GeometryCollectionSelectionCommands.h` (Public)


#### class `FGeometryCollectionSelectionCommands`  
`class FGeometryCollectionSelectionCommands : public TCommands<FGeometryCollectionSelectionCommands>`  
_L9-33_
- inherits: `TCommands<FGeometryCollectionSelectionCommands>`
- L12 _public function_ `FGeometryCollectionSelectionCommands() : TCommands<FGeometryCollectionSelectionCommands> ( TEXT("GeometryCollectionSelection"), NSLOCTEXT("Contexts", "GeometryCollectionSelection", "Geometry Collection Selection Commands"), NAME_None, FAppStyle::GetAppStyleSetName() )`
- L23 _public prototype_ `virtual void RegisterCommands() override;`
- L26 _public member_ `TSharedPtr<FUICommandInfo> SelectAllGeometry;` — Selects all Geometry Collection geometry
- L29 _public member_ `TSharedPtr<FUICommandInfo> SelectNone;` — Deselects all Geometry Collection geometry
- L32 _public member_ `TSharedPtr<FUICommandInfo> SelectInverseGeometry;` — Selects inverse of currently seleted Geometry Collection geometry

### `Plugins/Experimental/GeometryCollectionPlugin/Source/GeometryCollectionEditor/Public/GeometryCollection/GeometryCollectionThumbnailRenderer.h` (Public)


#### class `UGeometryCollectionThumbnailRenderer`  
`class UGeometryCollectionThumbnailRenderer : public UDefaultSizedThumbnailRenderer`  
_L20-33_
- reflection: `UCLASS(config = Editor, MinimalAPI)`
- inherits: `UDefaultSizedThumbnailRenderer`
- L25 _private prototype_ `virtual void Draw(UObject* Object, int32 X, int32 Y, uint32 Width, uint32 Height, FRenderTarget* RenderTarget, FCanvas* Canvas, bool bAdditionalViewFamily) override;`
- L29 _private prototype_ `virtual void BeginDestroy() override;`
- L32 _private member_ `FGeometryCollectionThumbnailScene* ThumbnailScene;`

### `Plugins/Experimental/GeometryCollectionPlugin/Source/GeometryCollectionEditor/Public/GeometryCollection/GeometryCollectionThumbnailScene.h` (Public)


#### class `FGeometryCollectionThumbnailScene`  
`class FGeometryCollectionThumbnailScene : public FThumbnailPreviewScene`  
_L11-27_
- inherits: `FThumbnailPreviewScene`
- L15 _public prototype_ `FGeometryCollectionThumbnailScene();` — Constructor
- L18 _public prototype_ `void SetGeometryCollection(UGeometryCollection* GeometryCollection);` — Sets the geometry collection to use in the next CreateView()
- L22 _protected prototype_ `virtual void GetViewMatrixParameters(const float InFOVDegrees, FVector& OutOrigin, float& OutOrbitPitch, float& OutOrbitYaw, float& OutOrbitZoom) const override;` — FThumbnailPreviewScene implementation
- L26 _private member_ `AGeometryCollectionActor* PreviewActor;` — The actor used to display all geometry collection thumbnails
