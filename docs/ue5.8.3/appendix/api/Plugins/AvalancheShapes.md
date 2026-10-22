# Plugins / AvalancheShapes

- module root: `Plugins/VirtualProduction/Avalanche/Source/AvalancheShapes`
- headers: 32; symbols: 1089
- symbol kinds: class=27, delegate=5, enum=9, enumerator=30, function=219, macro=3, member=251, namespace=8, prototype=517, struct=18, typedef=2
- PrivateDependencyModuleNames: ActorModifierCore, AvalancheEditorCore, DeveloperSettings, DynamicMaterial, DynamicMaterialEditor, DynamicMesh, GeometryAlgorithms, GeometryCore, GeometryFramework, GeometryScriptingCore, InputCore, MovieScene, MovieSceneTracks, TypedElementFramework, UnrealEd
- PublicDependencyModuleNames: Avalanche, AvalancheCore, AvalancheInteractiveToolsRuntime, AvalancheMaterial, Core, CoreUObject, Engine

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheShapes/Private/AvaShapeBuildSystem.h` (Private)


#### class `UAvaShapeBuildSystem`  
`class UAvaShapeBuildSystem : public UTickableWorldSubsystem`  
_L14-47_
- reflection: `UCLASS()`
- inherits: `UTickableWorldSubsystem`
- L20 _public prototype_ `static UAvaShapeBuildSystem* FindBuildSystem(TNotNull<const UObject*> InContextObject);` — Returns the build system for the given context object
- L22 _public prototype_ `void QueueShapeBuild(UAvaShapeDynamicMeshBase* InShape);`
- L25 _public prototype_ `virtual bool DoesSupportWorldType(const EWorldType::Type InWorldType) const override;`
- L29 _public prototype_ `virtual bool IsTickableInEditor() const override;`
- L30 _public prototype_ `virtual void Tick(float InDeltaTime) override;`
- L31 _public prototype_ `virtual TStatId GetStatId() const override;`
- L43 _private prototype_ `void BuildShapes();`
- L46 _private member_ `TArray<TWeakObjectPtr<UAvaShapeDynamicMeshBase>> QueuedShapes;` — `UPROPERTY()`

#### struct `UAvaShapeBuildSystem::FShapeBuild`  
`struct FShapeBuild`  
_L35-42_
- L37 _public prototype_ `explicit FShapeBuild(TNotNull<UAvaShapeDynamicMeshBase*> InShapeBuilder, const UActorModifierCoreSubsystem* InModifierSystem);`
- L39 _public member_ `TNotNull<UAvaShapeDynamicMeshBase*> Shape;` — Shape to build
- L41 _public member_ `FActorModifierCoreScopedLock ModifierLock;` — Keep the modifier locked while build takes place

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheShapes/Private/AvaShapesModule.h` (Private)


#### class `FAvaShapesModule`  
`class FAvaShapesModule : public IModuleInterface`  
_L7-13_
- inherits: `IModuleInterface`
- L11 _public prototype_ `virtual void StartupModule() override;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheShapes/Private/Sequencer/MovieScene/MovieSceneAvaShapeRectCornerSectionTemplate.h` (Private)


#### struct `UE::MovieScene::FMultiChannelShapeRectCorner`  
`struct FMultiChannelShapeRectCorner`  
_L13-25_
- L15 _public prototype_ `FMultiChannelShapeRectCorner() = default;`
- L17 _public function_ `float operator[](int32 Index) const`
- L22 _public member_ `UE::MovieScene::TMultiChannelValue<float, 1> BevelSize;`
- L23 _public member_ `uint8 BevelSubdivisions = 0;`
- L24 _public member_ `EAvaShapeCornerType Type = EAvaShapeCornerType::Point;`

#### struct `UE::MovieScene::FBlendableShapeRectCorner`  
`struct FBlendableShapeRectCorner`  
_L33-111_
- L35 _public function_ `FBlendableShapeRectCorner()`
- L41 _public member_ `TOptional<FMultiChannelShapeRectCorner> InitialValue;`
- L42 _public member_ `FMultiChannelShapeRectCorner Absolute;`
- L43 _public member_ `FMultiChannelShapeRectCorner Additive;`
- L45 _public member_ `float AbsoluteWeights[1];`
- L48 _public function_ `FAvaShapeRectangleCornerSettings Resolve(TMovieSceneInitialValueStore<FAvaShapeRectangleCornerSettings>& InitialValueStore)` — Resolve this structure's data into a final value to pass to the actuator

#### struct `TBlendableTokenTraits`  
`template<> struct TBlendableTokenTraits<FAvaShapeRectangleCornerSettings>`  
_L122-125_
- L124 _public typedef_ `using WorkingDataType = UE::MovieScene::FBlendableShapeRectCorner;`

#### struct `FMovieSceneAvaShapeRectCornerSectionTemplate`  
`struct FMovieSceneAvaShapeRectCornerSectionTemplate : public FMovieScenePropertySectionTemplate`  
_L128-162_
- reflection: `USTRUCT()`
- inherits: `FMovieScenePropertySectionTemplate`
- L134 _public function_ `FMovieSceneAvaShapeRectCornerSectionTemplate() : BlendType(EMovieSceneBlendType::Absolute)`
- L139 _public prototype_ `FMovieSceneAvaShapeRectCornerSectionTemplate(const class UMovieSceneAvaShapeRectCornerSection& Section , const UMovieScenePropertyTrack& Track);`
- L144 _private function_ `virtual UScriptStruct& GetScriptStructImpl() const override`
- L145 _private function_ `virtual void SetupOverrides() override`
- L146 _private prototype_ `virtual void Evaluate(const FMovieSceneEvaluationOperand& Operand , const FMovieSceneContext& Context , const FPersistentEvaluationData& PersistentData , FMovieSceneExecutionTokens& ExecutionTokens) const override;`
- L152 _private member_ `FMovieSceneFloatChannel BevelSize;` — `UPROPERTY()`
- L155 _private member_ `FMovieSceneByteChannel BevelSubdivisions;` — `UPROPERTY()`
- L158 _private member_ `FMovieSceneByteChannel Type;` — `UPROPERTY()`
- L161 _private member_ `EMovieSceneBlendType BlendType;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace MovieScene` (scope `UE`)
- L27 _prototype_ `void MultiChannelFromData(const FAvaShapeRectangleCornerSettings& In , FMultiChannelShapeRectCorner& Out);` (scope `UE::MovieScene`)
- L30 _prototype_ `void ResolveChannelsToData(const FMultiChannelShapeRectCorner& In , FAvaShapeRectangleCornerSettings& Out);` (scope `UE::MovieScene`)
- L113 _prototype_ `void BlendValue(FBlendableShapeRectCorner& OutBlend , const FMultiChannelShapeRectCorner& InValue , float Weight , EMovieSceneBlendType BlendType , TMovieSceneInitialValueStore<FAvaShapeRectangleCornerSettings>& InitialValueStore);` (scope `UE::MovieScene`)
- L120 _prototype_ `template<> FMovieSceneAnimTypeID GetBlendingDataType<FAvaShapeRectangleCornerSettings>();`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheShapes/Public/AvaShapeActor.h` (Public)


#### class `AAvaShapeActor`  
`class AAvaShapeActor : public AActor , public IAvaSnapPointGenerator , public IAvaInteractiveToolsModeDetailsObjectProvider`  
_L14-67_
- reflection: `UCLASS()`
- inherits: `AActor,IAvaSnapPointGenerator,IAvaInteractiveToolsModeDetailsObjectProvider`
- L22 _public prototype_ `AAvaShapeActor();`
- L24 _public function_ `bool HasFinishedCreation() const`
- L25 _public function_ `void FinishCreation()`
- L27 _public function_ `UAvaShapeDynamicMeshBase* GetDynamicMesh() const`
- L28 _public prototype_ `void SetDynamicMesh(UAvaShapeDynamicMeshBase* NewDynamicMesh);`
- L30 _public function_ `UDynamicMeshComponent* GetShapeMeshComponent() const`
- L33 _public prototype_ `virtual FString GetDefaultActorLabel() const override;`
- L34 _public prototype_ `virtual void PostEditUndo() override;`
- L37 _public prototype_ `FAvaColorChangeData GetColorData() const;`
- L38 _public prototype_ `void SetColorData(const FAvaColorChangeData& NewColorData);`
- L41 _public prototype_ `virtual void PostInitProperties() override;`
- L45 _public prototype_ `virtual TArray<FAvaSnapPoint> GetLocalSnapPoints() const override;`
- L49 _public prototype_ `virtual UObject* GetModeDetailsObject_Implementation() const override;`
- L54 _public prototype_ `void RefreshParametricMaterial();` — `UFUNCTION(BlueprintCallable, CallInEditor, Category="Material")` — Used to trigger a refresh of the parametric material if needed through RC or blueprint
- L57 _protected member_ `static const FName ShapeComponentName;`
- L60 _protected member_ `bool bFinishedCreation;` — `UPROPERTY()`
- L63 _protected member_ `TObjectPtr<UAvaShapeDynamicMeshBase> DynamicMesh = nullptr;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Motion Design")`
- L66 _protected member_ `TObjectPtr<UDynamicMeshComponent> ShapeMeshComponent = nullptr;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Motion Design")`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheShapes/Public/AvaShapeMaterialBridge.h` (Public)


#### struct `FAvaShapeMaterialContainerStateMesh`  
`struct FAvaShapeMaterialContainerStateMesh`  
_L17-32_
- reflection: `USTRUCT()`
- desc: Shape mesh state data. Only the items available through FAvaShapeMeshData getters are available
- L22 _public member_ `int32 Index = INDEX_NONE;` — `UPROPERTY()`
- L25 _public member_ `TObjectPtr<UMaterialInterface> Material;` — `UPROPERTY()`
- L28 _public member_ `EMaterialType MaterialType = EMaterialType::Default;` — `UPROPERTY()`
- L31 _public member_ `FAvaShapeParametricMaterial ParametricMaterial;` — `UPROPERTY()`

#### struct `FAvaShapeMaterialContainerState`  
`struct FAvaShapeMaterialContainerState : public FAvaMaterialContainerState`  
_L36-42_
- reflection: `USTRUCT()`
- inherits: `FAvaMaterialContainerState`
- desc: Material container state for UAvaShapeDynamicMeshBase components
- L41 _public member_ `TArray<FAvaShapeMaterialContainerStateMesh> Meshes;` — `UPROPERTY()`

#### class `UE::Ava::FShapeMaterialWriteSlot`  
`class FShapeMaterialWriteSlot : public FMaterialBridgeWriteSlot`  
_L48-64_
- inherits: `FMaterialBridgeWriteSlot`
- desc: Represents a slot in Motion Design Shape Components when accessing the slot with write access
- L51 _public prototype_ `explicit FShapeMaterialWriteSlot(TNotNull<UAvaShapeDynamicMeshBase*> InShape, int32 InMeshIndex);`
- L55 _protected prototype_ `virtual void OnMaterialChanged() override;`
- L56 _protected prototype_ `virtual bool OnFeatureRequest(TConstStructView<FAvaMaterialBridgeFeature> InFeature) override;`
- L60 _protected member_ `TNotNull<TObjectPtr<UAvaShapeDynamicMeshBase>> Shape;` — The dynamic mesh shape component owning the slot
- L63 _protected member_ `int32 MeshIndex;` — The mesh index of the slot

#### class `UE::Ava::FShapeMaterialBridge`  
`class FShapeMaterialBridge : public FMaterialBridge`  
_L67-81_
- inherits: `FMaterialBridge`
- desc: Material Bridge for Motion Design Shape Components
- L70 _public typedef_ `using FContainerState = FAvaShapeMaterialContainerState;`
- L74 _protected prototype_ `virtual const UStruct* OnGetBridgedType() const override;`
- L75 _protected prototype_ `virtual EControlFlow OnAccessSlots(const FReadSlotContext& InContext, TFunctionRef<EControlFlow(const FReadSlotContext&, const FReadSlot&)> InFunc, const FReadSlotOptions& InOptions) const override;`
- L76 _protected prototype_ `virtual EControlFlow OnAccessSlots(const FWriteSlotContext& InContext, TFunctionRef<EControlFlow(const FWriteSlotContext&, FWriteSlot&)> InFunc, const FWriteSlotOptions& InOptions) const override;`
- L77 _protected prototype_ `virtual TSubScriptStructOf<FAvaMaterialContainerState> OnGetContainerStateType() const override;`
- L78 _protected prototype_ `virtual void OnApplyState(const FApplyStateContext& InContext, TConstStructView<FAvaMaterialContainerState> InContainerState, const FApplyStateOptions& InOptions) const override;`
- L79 _protected prototype_ `virtual void OnStoreState(const FStoreStateContext& InContext, TStructView<FAvaMaterialContainerState> InContainerState, const FStoreStateOptions& InOptions) const override;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API AVALANCHESHAPES_API`
- L44 _namespace_ `namespace UE`
- L44 _namespace_ `namespace Ava` (scope `UE`)

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheShapes/Public/AvaShapeMesh.h` (Public)


#### struct `FAvaShapeMesh`  
`struct FAvaShapeMesh`  
_L15-80_
- reflection: `USTRUCT()`
- desc: Represents a mesh section
- L22 _public function_ `explicit FAvaShapeMesh() : FAvaShapeMesh(INDEX_NONE)`
- L26 _public function_ `explicit FAvaShapeMesh(int32 InMeshIndex) : MeshIndex(InMeshIndex) , bUpdateRequired(false)`
- L32 _public prototype_ `void Clear();` — clear the cached data only
- L35 _public prototype_ `void ClearIds();` — clear the mesh ids only
- L37 _public prototype_ `void AddTriangle(int32 A, int32 B, int32 C);`
- L39 _public prototype_ `void EnqueueTriangleIndex(int32 A);`
- L41 _public function_ `int32 GetMeshIndex() const`
- L47 _public member_ `TArray<int32> TriangleIds;` — used to quickly clear the mesh section and avoid looping through all triangles, set automatically
- L50 _public member_ `TArray<int32> VerticeIds;` — reflects id from the dynamic mesh to quickly match with mesh ids for updates, set automatically
- L53 _public member_ `TArray<int32> UVIds;` — reflects id from the dynamic mesh to quickly match with mesh ids for updates, set automatically
- L56 _public member_ `TArray<int32> NormalIds;` — reflects id from the dynamic mesh to quickly match with mesh ids for updates, set automatically
- L59 _public member_ `TArray<int32> ColourIds;` — reflects id from the dynamic mesh to quickly match with mesh ids for updates, set automatically
- L62 _public member_ `TArray<FVector> Vertices;` — cached version to regenerate section quickly
- L64 _public member_ `TArray<int32> Triangles;`
- L66 _public member_ `TArray<FVector> Normals;`
- L68 _public member_ `TArray<FVector2D> UVs;`
- L70 _public member_ `TArray<FLinearColor> VertexColours;`
- L72 _public member_ `TArray<int32> NewTriangleQueue;`
- L77 _protected member_ `int32 MeshIndex;` — `UPROPERTY()` — readonly should not be changed
- L79 _protected member_ `bool bUpdateRequired;`

#### struct `FAvaShapeMeshData`  
`struct FAvaShapeMeshData`  
_L84-177_
- reflection: `USTRUCT(BlueprintType)`
- desc: Represents a mesh section with its material, uv data
- L92 _public function_ `FAvaShapeMeshData(int32 InMeshIndex, FName InMeshName, bool InbMeshVisible) : bMeshVisible(InbMeshVisible) , bUsesPrimaryMaterialParams(InMeshIndex != 0) , MaterialType(EMaterialType::Parametric) , Material(nullptr) , ParametricMaterial(FAvaShapeParametricMaterial()) , bOverridePrimaryUVParams(InMeshIndex == 0) , MaterialUVParams(FAvaShapeMaterialUVParameters()) , MeshIndex(InMeshIndex) , MeshName(InMeshName) , Mesh(FAvaShapeMesh(InMeshIndex)) , bMeshDirty(true)`
- L106 _public function_ `FAvaShapeMeshData() : FAvaShapeMeshData(0, TEXT("PRIMARY"), true)`
- L110 _public function_ `int32 GetMeshIndex() const`
- L115 _public function_ `FName GetMeshName() const`
- L120 _public function_ `EMaterialType GetMaterialType() const`
- L125 _public function_ `UMaterialInterface* GetMaterial() const`
- L130 _public function_ `const FAvaShapeParametricMaterial& GetParametricMaterial() const`
- L138 _protected member_ `bool bMeshVisible;` — `UPROPERTY(EditDefaultsOnly, Category="Shape")` — whether the mesh is currently visible or not and should be editable
- L142 _protected member_ `bool bUsesPrimaryMaterialParams;` — `UPROPERTY(Transient)` — mesh uses same material as primary
- L146 _protected member_ `EMaterialType MaterialType;` — `UPROPERTY(EditInstanceOnly, Category="Material", meta=(NoResetToDefault, DisplayName="Material Type", DisplayAfter="bUsePrimaryMaterialEverywhere", EditCondition="bMeshVisible && !bUsesPrimaryMaterialParams", EditConditionHides, AllowPrivateAccess = "true"))` — mesh material type
- L150 _protected member_ `TObjectPtr<UMaterialInterface> Material;` — `UPROPERTY(EditInstanceOnly, Category="Material", meta=(NoResetToDefault, DisplayName="Material", DisplayAfter="MaterialType", EditCondition="bMeshVisible && !bUsesPrimaryMaterialParams && MaterialType != EMaterialType::Parametric", EditConditionHides, AllowPrivateAccess = "true"))` — mesh material
- L154 _protected member_ `FAvaShapeParametricMaterial ParametricMaterial;` — `UPROPERTY(EditInstanceOnly, Category="Material", meta=(NoResetToDefault, DisplayName="Material", DisplayAfter="Material", EditCondition="bMeshVisible && !bUsesPrimaryMaterialParams && MaterialType == EMaterialType::Parametric", EditConditionHides, AllowPrivateAccess = "true"))` — parametric material settings
- L158 _protected member_ `bool bOverridePrimaryUVParams;` — `UPROPERTY(EditInstanceOnly, Category="Material", meta=(NoResetToDefault, DisplayAfter="ParametricMaterial", EditCondition="bMeshVisible && MeshIndex != 0", EditConditionHides, AllowPrivateAccess = "true"))` — mesh uses same uv params as primary
- L162 _protected member_ `FAvaShapeMaterialUVParameters MaterialUVParams;` — `UPROPERTY(EditInstanceOnly, Category="Material", meta=(NoResetToDefault, DisplayName="UV Params", DisplayAfter="bOverridePrimaryUVParams", EditCondition="bMeshVisible && bOverridePrimaryUVParams", EditConditionHides, AllowPrivateAccess = "true"))` — mesh material UV params
- L166 _protected member_ `int32 MeshIndex;` — `UPROPERTY()` — do not change this once assigned, 0 means primary
- L170 _protected member_ `FName MeshName;` — `UPROPERTY()` — display name of the mesh index for the widget
- L173 _protected member_ `FAvaShapeMesh Mesh;` — `UPROPERTY()`
- L176 _protected member_ `bool bMeshDirty;` — Flag to regenerate this mesh again once updated

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheShapes/Public/AvaShapeMeshComponentMaterialBridge.h` (Public)


#### class `UE::Ava::FShapeMeshComponentMaterialBridge`  
`class FShapeMeshComponentMaterialBridge : public FMaterialBridge`  
_L16-23_
- inherits: `FMaterialBridge`
- desc: Material Bridge for shape mesh components that are managed by the shape builders Slot accessing and material container state are not implemented by design as the material slot access for these is managed by the shape builder component. FShapeMaterialBridge should be used instead.
- L20 _protected prototype_ `virtual const UStruct* OnGetBridgedType() const override;`
- L21 _protected prototype_ `virtual bool OnIsMaterialContainerSupported(FConstDataView InMaterialContainer) const override;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API AVALANCHESHAPES_API`
- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Ava` (scope `UE`)

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheShapes/Public/AvaShapeParametricMaterial.h` (Public)


#### enum `EAvaShapeParametricMaterialTranslucency`  
`enum class EAvaShapeParametricMaterialTranslucency : uint8`  
_L20-28_
- reflection: `UENUM(BlueprintType)`
- L23 _public enumerator_ `Auto` — Switches when parameters have opacity < 1
- L25 _public enumerator_ `Disabled` — Uses opaque material regardless of opacity parameters
- L27 _public enumerator_ `Enabled` — Uses translucent material regardless of opacity parameters

#### struct `FAvaShapeParametricMaterial`  
`struct FAvaShapeParametricMaterial`  
_L31-230_
- reflection: `USTRUCT(BlueprintType)`
- L49 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnMaterialChanged, const FAvaShapeParametricMaterial&) DECLARE_MULTICAST_DELEGATE_OneParam(FOnMaterialParameterChanged, const FAvaShapeParametricMaterial&) static const FName StyleParameterName;`
- L53 _public member_ `static const FName TextureParameterName;`
- L54 _public member_ `static const FName ColorAParameterName;`
- L55 _public member_ `static const FName ColorBParameterName;`
- L56 _public member_ `static const FName GradientOffsetParameterName;`
- L57 _public member_ `static const FName GradientRotationParameterName;`
- L60 _public prototype_ `static FOnMaterialChanged::RegistrationType& OnMaterialChanged();` — Called when active material changed
- L63 _public prototype_ `static FOnMaterialParameterChanged::RegistrationType& OnMaterialParameterChanged();` — Called when active material parameters changed
- L65 _public prototype_ `FAvaShapeParametricMaterial() = default;`
- L66 _public prototype_ `FAvaShapeParametricMaterial(const FAvaShapeParametricMaterial& Other);`
- L67 _public prototype_ `FAvaShapeParametricMaterial& operator=(const FAvaShapeParametricMaterial& Other);`
- L69 _public prototype_ `bool CopyFromMaterialParameters(UMaterialInstance* InMaterial);`
- L72 _public prototype_ `bool IsParametricMaterial(UMaterialInterface* InMaterial, const bool bCheckIfDefault = false) const;` — Check if input material is a parametric material
- L75 _public prototype_ `UMaterialInterface* GetDefaultMaterial() const;` — Get default parent material currently active
- L78 _public prototype_ `UMaterialInstanceDynamic* GetMaterial() const;` — Get active up to date material instance
- L81 _public prototype_ `UMaterialInstanceDynamic* GetOrCreateMaterial(UObject* InOuter);` — Get active up to date material instance or creates it
- L84 _public prototype_ `void SetMaterial(UMaterialInstanceDynamic* InMaterial);` — Set instanced material currently active
- L86 _public prototype_ `void SetTranslucency(EAvaShapeParametricMaterialTranslucency InTranslucency);`
- L88 _public function_ `EAvaShapeParametricMaterialTranslucency GetTranslucency() const`
- L93 _public prototype_ `bool ShouldUseTranslucentMaterial() const;`
- L95 _public function_ `EAvaShapeParametricMaterialStyle GetStyle() const`
- L100 _public prototype_ `void SetStyle(EAvaShapeParametricMaterialStyle InStyle);`
- L102 _public function_ `const FLinearColor& GetPrimaryColor() const`
- L107 _public prototype_ `void SetTexture(UTexture* InTexture);`
- L109 _public function_ `UTexture* GetTexture() const`
- L114 _public prototype_ `void SetPrimaryColor(const FLinearColor& InColor);`
- L116 _public function_ `const FLinearColor& GetSecondaryColor() const`
- L121 _public prototype_ `void SetSecondaryColor(const FLinearColor& InColor);`
- L123 _public function_ `float GetGradientOffset() const`
- L128 _public prototype_ `void SetGradientOffset(float InOffset);`
- L130 _public function_ `float GetGradientRotation() const`
- L135 _public prototype_ `void SetGradientRotation(float InRotation);`
- L137 _public function_ `bool GetUseUnlitMaterial() const`
- L142 _public prototype_ `void SetUseUnlitMaterial(bool bInUse);`
- L144 _public function_ `bool GetUseTwoSidedMaterial() const`
- L149 _public prototype_ `void SetUseTwoSidedMaterial(bool bInUse);`
- L152 _public prototype_ `void SetMaterialParameterValues(UMaterialInstanceDynamic* InMaterialInstance, bool bInNotifyUpdate = false) const;` — Set parameter values on a material instance
- L154 _public prototype_ `void PostEditChange(TConstArrayView<FName> InPropertyNames);`
- L159 _protected member_ `EAvaShapeParametricMaterialStyle Style = EAvaShapeParametricMaterialStyle::Solid;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category="Material", meta=(NoResetToDefault, DisplayName="Material Style", AllowPrivateAccess = "true"))` — Default style for the material
- L163 _protected member_ `TObjectPtr<UTexture> Texture = nullptr;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category="Material", meta=(NoResetToDefault, DisplayName="Texture", EditCondition="Style == EAvaShapeParametricMaterialStyle::Texture", EditConditionHides, AllowPrivateAccess = "true"))` — Simple texture for the material
- L167 _protected member_ `FLinearColor ColorA = FLinearColor::White;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category="Material", meta=(NoResetToDefault, DisplayName="Primary Color", EditCondition="Style != EAvaShapeParametricMaterialStyle::Texture", EditConditionHides, AllowPrivateAccess = "true"))` — Primary colour for the material
- L171 _protected member_ `FLinearColor ColorB = FLinearColor::Black;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category="Material", meta=(NoResetToDefault, DisplayName="Secondary Color", EditCondition="Style == EAvaShapeParametricMaterialStyle::LinearGradient", EditConditionHides, AllowPrivateAccess = "true"))` — Secondary colour for the material
- L175 _protected member_ `float GradientOffset = 0.5f;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category="Material", meta=(NoResetToDefault, ClampMin="0", ClampMax="1", DisplayName="Gradient Offset", EditCondition = "Style == EAvaShapeParametricMaterialStyle::LinearGradient", EditConditionHides, AllowPrivateAccess = "true"))` — Offset for gradient style material
- L179 _protected member_ `float GradientRotation = 0.f;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category="Material", meta=(NoResetToDefault, ClampMin="0", ClampMax="1", DisplayName="Gradient Rotation", EditCondition = "Style == EAvaShapeParametricMaterialStyle::LinearGradient", EditConditionHides, AllowPrivateAccess = "true"))` — Rotation for gradient style material
- L183 _protected member_ `bool bUseUnlitMaterial = false;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category="Material", meta=(NoResetToDefault, DisplayName="Use Unlit Material", AllowPrivateAccess = "true"))` — whether the material is unlit or default lit
- L187 _protected member_ `bool bUseTwoSidedMaterial = false;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Material", meta=(NoResetToDefault, DisplayName = "Use Two Sided Material", AllowPrivateAccess = "true"))` — whether the material is one sided or two sided
- L191 _protected member_ `EAvaShapeParametricMaterialTranslucency Translucency = EAvaShapeParametricMaterialTranslucency::Auto;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category="Material", meta=(NoResetToDefault))` — How to handle translucency for the underlying material
- L194 _private member_ `static FOnMaterialChanged OnMaterialChangedDelegate;`
- L195 _private member_ `static FOnMaterialParameterChanged OnMaterialParameterChangedDelegate;`
- L205 _private member_ `TArray<TObjectPtr<UMaterialInterface>> DefaultMaterials;` — `UPROPERTY(Transient)` — Parent material 1. Opaque Lit 2. Translucent Lit 3. Opaque Unlit 4. Translucent Unlit ...
- L215 _private member_ `TArray<TObjectPtr<UMaterialInstanceDynamic>> InstanceMaterials;` — `UPROPERTY(Transient)` — Material instances corresponding to the parent material instanced 1. Opaque Lit 2. Translucent Lit 3. Opaque Unlit 4. Translucent Unlit ...
- L217 _private member_ `int32 ActiveInstanceIndex = INDEX_NONE;`
- L220 _private prototype_ `void LoadDefaultMaterials() const;` — Load parents materials to create instance materials
- L223 _private prototype_ `UMaterialInstanceDynamic* CreateMaterialInstance(UObject* InOuter);` — Create an instance material based on the current active parent
- L226 _private prototype_ `void OnMaterialParameterUpdated();` — Update parameter values on all instance materials
- L229 _private prototype_ `int32 GetActiveInstanceIndex() const;` — Get the active material index

#### enum `FAvaShapeParametricMaterial::EMaterialType`  
`enum EMaterialType : int32`  
_L35-47_
- L37 _public enumerator_ `Opaque = 0`
- L38 _public enumerator_ `Translucent = 1 << 0`
- L40 _public enumerator_ `Lit = 0`
- L41 _public enumerator_ `Unlit = 1 << 1`
- L43 _public enumerator_ `TwoSided = 0`
- L44 _public enumerator_ `OneSided = 1 << 2`
- L46 _public enumerator_ `MaterialTypeCount = Translucent + Unlit + OneSided + 1`

#### Free symbols / members of external scopes

- L49 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnMaterialChanged, const FAvaShapeParametricMaterial&) DECLARE_MULTICAST_DELEGATE_OneParam(FOnMaterialParameterChanged, const FAvaShapeParametricMaterial&) static const FName StyleParameterName;`
- L50 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnMaterialParameterChanged, const FAvaShapeParametricMaterial&) static const FName StyleParameterName;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheShapes/Public/AvaShapePrimitiveFunctions.h` (Public)


#### class `UAvaShapeMeshFunctions`  
`class UAvaShapeMeshFunctions : public UBlueprintFunctionLibrary`  
_L14-34_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBlueprintFunctionLibrary`
- desc: FunctionLibrary to Create Ava Shape Meshes and apply them to a Shape Actor.
- L21 _public prototype_ `static UPARAM(DisplayName = "Mesh") UAvaShapeRectangleDynamicMesh* SetRectangle(AAvaShapeActor* ShapeActor , const FVector2D& Size , const FTransform& Transform);` — `UFUNCTION(BlueprintCallable, Category = "Shapes", meta = (ScriptMethod))` — Sets the Shape Actor mesh to Rectangle.
- L26 _private prototype_ `static UAvaShapeDynamicMeshBase* SetMesh(AAvaShapeActor* InShapeActor, const TSubclassOf<UAvaShapeDynamicMeshBase>& InMeshClass, const FTransform& InTransform = FTransform::Identity);`
- L30 _private function_ `static InMeshType* SetMesh(AAvaShapeActor* InShapeActor, const FTransform& InTransform = FTransform::Identity)`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheShapes/Public/AvaShapeSettings.h` (Public)


#### class `UAvaShapeSettings`  
`class UAvaShapeSettings : public UDeveloperSettings`  
_L11-39_
- reflection: `UCLASS(MinimalAPI, config=Engine, meta=(DisplayName="Motion Design Shapes"))`
- inherits: `UDeveloperSettings`
- L16 _public prototype_ `UAvaShapeSettings();`
- L19 _public prototype_ `bool ShouldForceDisableShapeCollision() const;` — Returns whether shape collision should be force disabled
- L22 _public prototype_ `virtual void PostInitProperties() override;`
- L24 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& InPropertyChangedEvent) override;`
- L35 _private member_ `bool bForceDisableShapeCollision = true;` — `UPROPERTY(Config, EditAnywhere, Category="Motion Design")` — Option to disable shape collisions globally, as shapes with collisions can have a significant hit on perf. Enabled by default as Motion Design workflows most often do not require collisions. NOTE: Enabling this and saving levels with shapes will leave them in the 'No Collision' state.
- L38 _private member_ `std::atomic<bool> ForceDisableShapeCollision;` — Mirror atomic version of bForceDisableShapeCollision

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API AVALANCHESHAPES_API`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheShapes/Public/AvaShapeUVParameters.h` (Public)


#### struct `FAvaShapeMaterialUVParameters`  
`struct FAvaShapeMaterialUVParameters`  
_L10-95_
- reflection: `USTRUCT(BlueprintType)`
- L17 _public function_ `FAvaShapeMaterialUVParameters() : Mode(EAvaShapeUVMode::Uniform) , AnchorPreset(EAvaAnchors::Center) , Anchor(FVector2D(0.5f, 0.5f)) , Scale(FVector2D(1.f, 1.f)) , Offset(FVector2D::ZeroVector) , Rotation(0.f) , bFlipHorizontal(false) , bFlipVertical(false) , bUVsDirty(false)`
- L29 _public function_ `EAvaShapeUVMode GetMode() const`
- L34 _public function_ `EAvaAnchors GetAnchorPreset() const`
- L39 _public function_ `FVector2D GetAnchor() const`
- L44 _public function_ `FVector2D GetScale() const`
- L49 _public function_ `FVector2D GetOffset() const`
- L54 _public function_ `float GetRotation() const`
- L59 _public function_ `bool GetFlipHorizontal() const`
- L64 _public function_ `bool GetFlipVertical() const`
- L71 _protected member_ `EAvaShapeUVMode Mode;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category="Shape", meta=(NoResetToDefault, AllowPrivateAccess = "true"))`
- L74 _protected member_ `EAvaAnchors AnchorPreset;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category="Shape", meta=(NoResetToDefault, AllowPrivateAccess = "true"))`
- L77 _protected member_ `FVector2D Anchor;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category="Shape", meta=(NoResetToDefault, ClampMin="0.0", ClampMax="1.0", EditCondition="AnchorPreset == EAvaAnchors::Custom", AllowPrivateAccess = "true"))`
- L80 _protected member_ `FVector2D Scale;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category="Shape", meta=(NoResetToDefault, ClampMin="0.01", MotionDesignVectorWidget, AllowPreserveRatio="XY", Delta="0.05", AllowPrivateAccess = "true"))`
- L83 _protected member_ `FVector2D Offset;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category="Shape", meta=(NoResetToDefault, Delta="0.05", AllowPrivateAccess = "true"))`
- L86 _protected member_ `float Rotation;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category="Shape", meta=(NoResetToDefault, ClampMin="-360.0", ClampMax="360.0", AllowPrivateAccess = "true"))`
- L89 _protected member_ `bool bFlipHorizontal;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category="Shape", meta=(NoResetToDefault, AllowPrivateAccess = "true"))`
- L92 _protected member_ `bool bFlipVertical;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category="Shape", meta=(NoResetToDefault, AllowPrivateAccess = "true"))`
- L94 _protected member_ `bool bUVsDirty;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheShapes/Public/AvaShapeVertices.h` (Public)


#### struct `FAvaShapeCachedVertex2D`  
`struct FAvaShapeCachedVertex2D`  
_L9-63_
- L11 _public member_ `FVector2D Location;`
- L12 _public member_ `int32 Index = INDEX_NONE;`
- L14 _public function_ `FAvaShapeCachedVertex2D() : FAvaShapeCachedVertex2D(FVector2D::ZeroVector)`
- L19 _public function_ `FAvaShapeCachedVertex2D(const FVector2D& InLocation, int32 InIndex = INDEX_NONE)`
- L25 _public function_ `bool operator==(const FAvaShapeCachedVertex2D& CachedVertex) const`
- L30 _public function_ `bool operator!=(const FAvaShapeCachedVertex2D& CachedVertex) const`
- L35 _public function_ `FAvaShapeCachedVertex2D& operator=(const FVector2D& InLocation)`
- L43 _public function_ `FVector2D operator+(const FAvaShapeCachedVertex2D& Value) const`
- L44 _public function_ `FVector2D operator+(const FVector2D& Value) const`
- L45 _public function_ `FVector2D operator+(const float& Value) const`
- L46 _public function_ `FVector2D operator-(const FAvaShapeCachedVertex2D& Value) const`
- L47 _public function_ `FVector2D operator-(const FVector2D& Value) const`
- L48 _public function_ `FVector2D operator-(const float& Value) const`
- L49 _public function_ `FVector2D operator*(const FAvaShapeCachedVertex2D& Value) const`
- L50 _public function_ `FVector2D operator*(const FVector2D& Value) const`
- L51 _public function_ `FVector2D operator*(const float& Value) const`
- L52 _public function_ `FVector2D operator/(const FAvaShapeCachedVertex2D& Value) const`
- L53 _public function_ `FVector2D operator/(const FVector2D& Value) const`
- L54 _public function_ `FVector2D operator/(const float& Value) const`
- L56 _public function_ `operator FVector2D() const`
- L61 _public function_ `bool HasIndex() const`
- L62 _public function_ `void ClearIndex()`

#### struct `FAvaShapeCachedVertex3D`  
`struct FAvaShapeCachedVertex3D`  
_L65-137_
- L67 _public member_ `FVector Location;`
- L68 _public member_ `FVector Normal;`
- L69 _public member_ `FVector2D UV;`
- L70 _public member_ `int32 Index = INDEX_NONE;`
- L72 _public function_ `FAvaShapeCachedVertex3D(const FVector& InLocation, const FVector& InNormal, const FVector2D& InUV, int32 InIndex = INDEX_NONE)`
- L80 _public function_ `FAvaShapeCachedVertex3D(const FAvaShapeCachedVertex2D& CachedVertex, int32 InIndex = INDEX_NONE)`
- L88 _public function_ `bool operator==(const FAvaShapeCachedVertex3D& CachedVertex) const`
- L93 _public function_ `bool operator!=(const FAvaShapeCachedVertex3D& CachedVertex) const`
- L98 _public function_ `FAvaShapeCachedVertex3D& operator=(const FAvaShapeCachedVertex3D& CachedVertex)`
- L108 _public function_ `FAvaShapeCachedVertex3D& operator=(const FVector& InLocation)`
- L118 _public function_ `FVector operator+(const FAvaShapeCachedVertex3D& Value) const`
- L119 _public function_ `FVector operator+(const FVector& Value) const`
- L120 _public function_ `FVector operator+(const float& Value) const`
- L121 _public function_ `FVector operator-(const FAvaShapeCachedVertex3D& Value) const`
- L122 _public function_ `FVector operator-(const FVector& Value) const`
- L123 _public function_ `FVector operator-(const float& Value) const`
- L124 _public function_ `FVector operator*(const FAvaShapeCachedVertex3D& Value) const`
- L125 _public function_ `FVector operator*(const FVector& Value) const`
- L126 _public function_ `FVector operator*(const float& Value) const`
- L127 _public function_ `FVector operator/(const FAvaShapeCachedVertex3D& Value) const`
- L128 _public function_ `FVector operator/(const FVector& Value) const`
- L129 _public function_ `FVector operator/(const float& Value) const`
- L131 _public function_ `operator FVector() const`
- L136 _public function_ `bool HasIndex() const`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheShapes/Public/AvaShapesDefs.h` (Public)


#### enum `EAvaShapeRectangleCornerTypeIndex`  
`enum class EAvaShapeRectangleCornerTypeIndex : uint8`  
_L28-33_
- L30 _public enumerator_ `Point = 1`
- L31 _public enumerator_ `InsetVertical = 2`
- L32 _public enumerator_ `InsetHorizontal = 3`

#### enum `EAvaShapeUVMode`  
`enum class EAvaShapeUVMode : uint8`  
_L36-42_
- reflection: `UENUM()`
- L39 _public enumerator_ `Stretch UMETA(DisplayName="Stretch to Fit")` — uvs are stretched to fit the shape size
- L41 _public enumerator_ `Uniform UMETA(DisplayName="Preserve Ratio")` — uvs are uniform to not cause any distortion

#### enum `EAvaShapeCornerType`  
`enum class EAvaShapeCornerType : uint8`  
_L45-50_
- reflection: `UENUM()`
- L47 _public enumerator_ `Point`
- L48 _public enumerator_ `CurveIn`
- L49 _public enumerator_ `CurveOut`

#### enum `EAvaShapeParametricMaterialStyle`  
`enum class EAvaShapeParametricMaterialStyle : uint8`  
_L53-58_
- reflection: `UENUM(BlueprintType)`
- L55 _public enumerator_ `Solid`
- L56 _public enumerator_ `LinearGradient`
- L57 _public enumerator_ `Texture`

#### enum `EMaterialType`  
`enum class EMaterialType : uint8`  
_L61-68_
- reflection: `UENUM(BlueprintType)`
- L63 _public enumerator_ `Asset = 0`
- L64 _public enumerator_ `Parametric = 1 UMETA(DisplayName = "Simple")`
- L65 _public enumerator_ `MaterialDesigner = 2`
- L67 _public enumerator_ `Default = Asset UMETA(Hidden)`

#### enum `ESizeType`  
`enum class ESizeType : uint8`  
_L71-75_
- reflection: `UENUM(BlueprintType)`
- L73 _public enumerator_ `UnrealUnit = 0` — cm
- L74 _public enumerator_ `Pixel = 1`

#### enum `EAvaDynamicMeshUpdateState`  
`enum class EAvaDynamicMeshUpdateState : uint8`  
_L77-85_
- L80 _public enumerator_ `UpdateRequired` — we need to update the mesh
- L82 _public enumerator_ `UpdateInProgress` — the update is in progress
- L84 _public enumerator_ `UpToDate` — the mesh is now up to date with latest changes

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace AvaShapes` (scope `UE`)
- L18 _prototype_ `FVector2D FindClosestPointOnLine(const FVector2D& LineStart, const FVector2D& LineEnd, const FVector2D& TestPoint);` (scope `UE::AvaShapes`)
- L20 _prototype_ `bool TransformMeshUVs(UE::Geometry::FDynamicMesh3& InEditMesh , const TArray<int32>& UVIds , const FAvaShapeMaterialUVParameters& InParams , const FVector2D& InShapeSize , const FVector2D& InUVOffset , float InUVFixRotation);` (scope `UE::AvaShapes`)

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheShapes/Public/DynamicMeshes/AvaShape2DArrowDynMesh.h` (Public)


#### class `UAvaShape2DArrowDynamicMesh`  
`class UAvaShape2DArrowDynamicMesh : public UAvaShape2DDynMeshBase`  
_L9-82_
- reflection: `UCLASS(MinimalAPI, ClassGroup="Shape", BlueprintType, CustomConstructor, Within=AvaShapeActor)`
- inherits: `UAvaShape2DDynMeshBase`
- L14 _public member_ `static const FString MeshName;`
- L16 _public function_ `UAvaShape2DArrowDynamicMesh() : UAvaShape2DArrowDynamicMesh(FVector2D(50.f, 50.f))`
- L20 _public function_ `UAvaShape2DArrowDynamicMesh(const FVector2D& Size2D, const FLinearColor& InVertexColor = FLinearColor::White) : UAvaShape2DDynMeshBase(Size2D, InVertexColor) , RatioArrowLine(0.5f) , RatioLineHeight(0.5f) , RatioArrowY(0.5f) , RatioLineY(0.5f) , bBothSideArrows(false)`
- L29 _public function_ `virtual const FString& GetMeshName() const override`
- L31 _public prototype_ `void SetRatioArrowLine(float InRatio);`
- L32 _public function_ `float GetRatioArrowLine() const`
- L34 _public prototype_ `void SetRatioLineHeight(float InRatio);`
- L35 _public function_ `float GetRatioLineHeight() const`
- L37 _public prototype_ `void SetRatioArrowY(float InRatio);`
- L38 _public function_ `float GetRatioArrowY() const`
- L40 _public prototype_ `void SetRatioLineY(float InRatio);`
- L41 _public function_ `float GetRatioLineY() const`
- L43 _public prototype_ `void SetBothSideArrows(bool bBothSide);`
- L44 _public function_ `bool IsBothSideArrows() const`
- L49 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L53 _protected prototype_ `virtual void OnRatioArrowLineChanged();`
- L54 _protected prototype_ `virtual void OnRatioLineHeightChanged();`
- L55 _protected prototype_ `virtual void OnBothSideArrowsChanged();`
- L56 _protected prototype_ `virtual void OnRatioArrowYChanged();`
- L57 _protected prototype_ `virtual void OnRatioLineYChanged();`
- L59 _protected prototype_ `virtual bool IsMeshVisible(int32 MeshIndex) override;`
- L60 _protected prototype_ `virtual bool CreateMesh(FAvaShapeMesh& InMesh) override;`
- L61 _protected prototype_ `virtual bool CanUpdateMeshInAnyThread() const override;`
- L65 _protected member_ `float RatioArrowLine;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category="Shape", Setter, Getter, meta=(ClampMin="0.0", ClampMax="1.0", DisplayName="Ratio Arrow Line", AllowPrivateAccess="true"))` — represents the ratio for the arrow and the line, 0.6 means 60% arrow and 40% line
- L69 _protected member_ `float RatioLineHeight;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category="Shape", Setter, Getter, meta=(ClampMin="0.0", ClampMax="1.0", DisplayName="Ratio Line Height", AllowPrivateAccess="true"))` — represents the ratio for the line height, 1 means 100% of the height available
- L73 _protected member_ `float RatioArrowY;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category="Shape", Setter, Getter, meta=(ClampMin="0.0", ClampMax="1.0", DisplayName="Ratio Arrow Y", AllowPrivateAccess="true"))` — represents the ratio for the arrow end, 0 means arrow point will be at bottom, 1 means arrow point will be at top
- L77 _protected member_ `float RatioLineY;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category="Shape", Setter, Getter, meta=(ClampMin="0.0", ClampMax="1.0", DisplayName="Ratio Line Y", AllowPrivateAccess="true"))` — represents the ratio for the arrow end, 0 means arrow point will be at bottom, 1 means arrow point will be at top
- L81 _protected member_ `bool bBothSideArrows;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category="Shape", Setter="SetBothSideArrows", Getter="IsBothSideArrows", meta=(DisplayName="Both Side Arrows", AllowPrivateAccess="true"))` — whether there should be an arrow on both side, arrows will have same ratio

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheShapes/Public/DynamicMeshes/AvaShape2DDynMeshBase.h` (Public)


#### class `UAvaShape2DDynMeshBase`  
`class UAvaShape2DDynMeshBase : public UAvaShapeDynamicMeshBase`  
_L12-124_
- reflection: `UCLASS(MinimalAPI, ClassGroup="Shape", Abstract, BlueprintType, CustomConstructor)`
- inherits: `UAvaShapeDynamicMeshBase`
- L21 _public function_ `UAvaShape2DDynMeshBase() : UAvaShape2DDynMeshBase(FVector2D(50.f, 50.f))`
- L25 _public function_ `UAvaShape2DDynMeshBase(const FVector2D& InExtent, const FLinearColor& InVertexColor = FLinearColor::White) : UAvaShapeDynamicMeshBase(InVertexColor) , bDoNotRecenterVertices(false) , Size2D(InExtent) , Size3D(FVector(0.f, InExtent.X, InExtent.Y))`
- L33 _public prototype_ `virtual ~UAvaShape2DDynMeshBase() override = default;`
- L35 _public prototype_ `void SetPixelSize2D(const FVector2D& InPixelSize2D);`
- L36 _public function_ `const FVector2D& GetPixelSize2D() const`
- L41 _public prototype_ `virtual void SetSize2D(const FVector2D& InSize2D) override;`
- L42 _public function_ `virtual FVector2D GetSize2D() const override`
- L47 _public prototype_ `virtual void SetSize3D(const FVector& InSize) override;`
- L48 _public function_ `virtual FVector GetSize3D() const override`
- L53 _public prototype_ `virtual void GetBounds(FVector& Origin, FVector& BoxExtent, FVector& Pivot) const override;`
- L57 _protected prototype_ `virtual void PostLoad() override;`
- L59 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L63 _protected prototype_ `virtual void OnRegisteredMeshes() override;`
- L64 _protected prototype_ `virtual void OnPixelSizeChanged() override;`
- L65 _protected prototype_ `virtual void OnScaledSizeChanged() override;`
- L66 _protected prototype_ `virtual void OnSizeChanged() override;`
- L70 _protected prototype_ `int32 AddVertexRaw(FAvaShapeMesh& InMesh, const FVector2D& Location, bool bForceNew = false);` — For every 3rd vertex added, a new triangle is added. To add existing vertices to the queue, add it via the index. This is skipped if bAddToTriangle is false.
- L72 _protected prototype_ `FAvaShapeCachedVertex2D AddVertexCreate(FAvaShapeMesh& InMesh, const FVector2D& Location, bool bForceNew = false);`
- L75 _protected prototype_ `bool AddVertex(FAvaShapeMesh& InMesh, const FAvaShapeCachedVertex2D& Vertex, bool bForceNew = false);`
- L79 _protected prototype_ `bool AddVertex(FAvaShapeMesh& InMesh, int32 VertexIndex);` — Adds an already existing vertex to the triangle queue.
- L89 _protected prototype_ `int32 CacheVertex(FAvaShapeMesh& InMesh, const FVector2D& Location, bool bForceNew = false);` — Adds a vertex to the Mesh. Converted from the XY to YZ plane. X and Y should be in the range 0->Width/Height, they will be changed to be centered around 0. UVs are generated. Normals point towards the negative X direction. Vertices are checked for duplicates. This is skipped if bForceNew is true. Returns the new vertex index
- L91 _protected prototype_ `bool CacheVertex(FAvaShapeMesh& InMesh, const FAvaShapeCachedVertex2D& Vertex, bool bForceNew = false);`
- L94 _protected prototype_ `FAvaShapeCachedVertex2D CacheVertexCreate(FAvaShapeMesh& InMesh, const FVector2D& Location, bool bForceNew = false);`
- L97 _protected prototype_ `void AddTriangle(FAvaShapeMesh& InMesh, const FAvaShapeCachedVertex2D& A, const FAvaShapeCachedVertex2D& B, const FAvaShapeCachedVertex2D& C);`
- L100 _protected prototype_ `void AddTriangle(FAvaShapeMesh& InMesh, int32 A, int32 B, int32 C);`
- L103 _protected prototype_ `virtual bool CreateMesh(FAvaShapeMesh& InMesh) override;` — Creates the mesh and updates the local snap points
- L105 _protected prototype_ `virtual bool CreateUVs(FAvaShapeMesh& InMesh, FAvaShapeMaterialUVParameters& InParams) override;`
- L108 _protected member_ `bool bDoNotRecenterVertices;` — `UPROPERTY()`
- L112 _protected member_ `FVector2D PixelSize2D = FVector2D::ZeroVector;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Transient, Setter, Getter, Category="Shape", meta=(ClampMin="0.0", DisplayName="Pixel Size", DisplayAfter="SizeType", MotionDesignVectorWidget, AllowPreserveRatio="XY", EditCondition="bAllowEditSize && SizeType == ESizeType::Pixel", EditConditionHides, AllowPrivateAccess="true"))` — pixel size of the mesh, will only be available in editor
- L116 _protected member_ `FVector2D Size2D = FVector2D::ZeroVector;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Setter, Getter, Category="Shape", meta=(ClampMin="0.0", DisplayName="Mesh Size", DisplayAfter="SizeType", MotionDesignVectorWidget, AllowPreserveRatio="XY", Units="Centimeters", EditCondition="bAllowEditSize && SizeType == ESizeType::UnrealUnit", EditConditionHides, AllowPrivateAccess="true"))` — total size in 2D from 0 to mesh size and not origin
- L119 _protected member_ `FVector2D PreEditSize2D = FVector2D::ZeroVector;` — `UPROPERTY(Transient)`
- L123 _protected member_ `FVector Size3D = FVector::ZeroVector;` — `UPROPERTY()` — total size in 3D from 0 to mesh size and not origin, XY remapped to YZ in 3D

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheShapes/Public/DynamicMeshes/AvaShape3DDynMeshBase.h` (Public)


#### class `UAvaShape3DDynMeshBase`  
`class UAvaShape3DDynMeshBase : public UAvaShapeDynamicMeshBase`  
_L11-98_
- reflection: `UCLASS(MinimalAPI, ClassGroup="Shape", Abstract, BlueprintType, CustomConstructor)`
- inherits: `UAvaShapeDynamicMeshBase`
- L19 _public function_ `UAvaShape3DDynMeshBase() : UAvaShape3DDynMeshBase(FVector(50.f, 50.f, 50.f))`
- L23 _public function_ `UAvaShape3DDynMeshBase(const FVector& InSize, const FLinearColor& InVertexColor = FLinearColor::White) : UAvaShapeDynamicMeshBase(InVertexColor) , Size3D(InSize)`
- L28 _public prototype_ `void SetPixelSize3D(const FVector& InPixelSize);`
- L29 _public function_ `const FVector& GetPixelSize3D() const`
- L34 _public prototype_ `virtual void SetSize3D(const FVector& InSize) override;`
- L35 _public function_ `virtual FVector GetSize3D() const override`
- L40 _public prototype_ `virtual void GetBounds(FVector& Origin, FVector& BoxExtent, FVector& Pivot) const override;`
- L44 _protected prototype_ `virtual void PostLoad() override;`
- L46 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L50 _protected prototype_ `virtual void OnRegisteredMeshes() override;`
- L51 _protected prototype_ `virtual void OnPixelSizeChanged() override;`
- L52 _protected prototype_ `virtual void OnSizeChanged() override;`
- L53 _protected prototype_ `virtual void OnScaledSizeChanged() override;`
- L57 _protected prototype_ `int32 AddVertexRaw(FAvaShapeMesh& InMesh, const FVector& Location, const FVector& Normal, bool bAddToTriangle = true);` — Adds a vertex to the Mesh even if it already exists, X, Y and Z should be centered around 0. Normal and UV need to be specified. Adds it to triangle queue by default
- L61 _protected prototype_ `bool AddVertex(FAvaShapeMesh& InMesh, const FAvaShapeCachedVertex3D& Vertex);` — Adds an already existing cached vertex by its index to the triangle queue.
- L65 _protected prototype_ `bool AddVertex(FAvaShapeMesh& InMesh, int32 VertexIndex);` — Adds an already existing vertex by its index to the triangle queue.
- L69 _protected prototype_ `FAvaShapeCachedVertex3D CacheVertexCreate(FAvaShapeMesh& InMesh, const FVector& Location, const FVector& Normal, bool bAddToTriangle = false);` — Creates a cache vertex that can be reused to create another triangle, does not add the vertice to the triangle by default
- L74 _protected prototype_ `bool CacheVertex(FAvaShapeMesh& InMesh, const FAvaShapeCachedVertex3D& Vertex, bool bAddToTriangle = false);` — Adds a cache vertex that can be reused to create another triangle, does not add the vertice to the triangle by default
- L79 _protected prototype_ `void AddTriangle(FAvaShapeMesh& InMesh, const FAvaShapeCachedVertex3D& A, const FAvaShapeCachedVertex3D& B, const FAvaShapeCachedVertex3D& C);` — Adds a triangle based on valid cached vertex
- L84 _protected prototype_ `void AddTriangle(FAvaShapeMesh& InMesh, int32 A, int32 B, int32 C);` — Adds a triangle based on valid indexes
- L88 _protected member_ `FVector PixelSize3D = FVector::ZeroVector;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Transient, Setter, Getter, Category="Shape", meta=(ClampMin="0.0", DisplayName="Pixel Size", DisplayAfter="SizeType", MotionDesignVectorWidget, AllowPreserveRatio="XYZ", EditCondition="bAllowEditSize && SizeType == ESizeType::Pixel", EditConditionHides, AllowPrivateAccess="true"))` — pixel size of the mesh, will only be available in editor
- L94 _protected member_ `FVector Size3D = FVector::ZeroVector;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Setter, Getter, Category="Shape", meta=(ClampMin="0.0", DisplayName="Mesh Size", DisplayAfter="SizeType", MotionDesignVectorWidget, AllowPreserveRatio="XYZ", Units="Centimeters", EditCondition="bAllowEditSize && SizeType == ESizeType::UnrealUnit", EditConditionHides, AllowPrivateAccess="true"))` — Corresponds to the total size from 0 to mesh size
- L97 _protected member_ `FVector PreEditSize3D = FVector::ZeroVector;` — `UPROPERTY(Transient)`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheShapes/Public/DynamicMeshes/AvaShapeChevronDynMesh.h` (Public)


#### class `UAvaShapeChevronDynamicMesh`  
`class UAvaShapeChevronDynamicMesh : public UAvaShape2DDynMeshBase`  
_L9-55_
- reflection: `UCLASS(MinimalAPI, ClassGroup="Shape", BlueprintType, CustomConstructor, Within=AvaShapeActor)`
- inherits: `UAvaShape2DDynMeshBase`
- L14 _public member_ `static const FString MeshName;`
- L16 _public function_ `UAvaShapeChevronDynamicMesh() : UAvaShapeChevronDynamicMesh(FVector2D(50.f, 50.f))`
- L20 _public function_ `UAvaShapeChevronDynamicMesh( const FVector2D& Size2D, const FLinearColor& InVertexColor = FLinearColor::White, const float InRatioChevron = 0.5) : UAvaShape2DDynMeshBase(Size2D, InVertexColor) , RatioChevron(InRatioChevron)`
- L28 _public function_ `virtual const FString& GetMeshName() const override`
- L33 _public prototype_ `void SetRatioChevron(float InRatio);`
- L34 _public function_ `float GetRatioChevron() const`
- L42 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L46 _protected prototype_ `virtual void OnRatioChevronChanged();`
- L48 _protected prototype_ `virtual bool IsMeshVisible(int32 MeshIndex) override;`
- L49 _protected prototype_ `virtual bool CreateMesh(FAvaShapeMesh& InMesh) override;`
- L50 _protected prototype_ `virtual bool CanUpdateMeshInAnyThread() const override;`
- L54 _protected member_ `float RatioChevron;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Setter, Getter, Category="Shape", meta=(ClampMin="0.0", ClampMax="0.99", DisplayName="Ratio Chevron", AllowPrivateAccess="true"))` — represents the ratio for the chevron size

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheShapes/Public/DynamicMeshes/AvaShapeConeDynMesh.h` (Public)


#### class `UAvaShapeConeDynamicMesh`  
`class UAvaShapeConeDynamicMesh : public UAvaShape3DDynMeshBase`  
_L9-136_
- reflection: `UCLASS(MinimalAPI, ClassGroup="Shape", BlueprintType, CustomConstructor, Within=AvaShapeActor)`
- inherits: `UAvaShape3DDynMeshBase`
- L16 _public member_ `static const FString MeshName;`
- L18 _public member_ `static constexpr uint8 MinNumSides = 3;`
- L19 _public member_ `static constexpr uint8 MaxNumSides = 128;`
- L21 _public member_ `static constexpr int32 MESH_INDEX_BOTTOM = 1;`
- L22 _public member_ `static constexpr int32 MESH_INDEX_TOP = 2;`
- L23 _public member_ `static constexpr int32 MESH_INDEX_START = 3;`
- L24 _public member_ `static constexpr int32 MESH_INDEX_END = 4;`
- L26 _public function_ `UAvaShapeConeDynamicMesh() : UAvaShapeConeDynamicMesh(FVector(50.f, 50.f, 50.f))`
- L30 _public function_ `UAvaShapeConeDynamicMesh( const FVector& InSize, const FLinearColor& InVertexColor = FLinearColor::White, float InHeight = 1, float InBaseRadius = 0.5, float InTopRadius = 0, uint8 InNumSides = 32, float InAngleDegree = 360.f, float InStartDegree = 0.f) : UAvaShape3DDynMeshBase(InSize, InVertexColor) , NumSides(InNumSides) , TopRadius(InTopRadius) , AngleDegree(InAngleDegree) , StartDegree(InStartDegree) , Height(InHeight) , BaseRadius(InBaseRadius)`
- L48 _public function_ `virtual const FString& GetMeshName() const override`
- L53 _public prototype_ `void SetNumSides(uint8 InNumSides);`
- L54 _public function_ `uint8 GetNumSides() const`
- L59 _public prototype_ `void SetTopRadius(float InTopRadius);`
- L60 _public function_ `float GetTopRadius() const`
- L65 _public prototype_ `void SetAngleDegree(float InDegree);`
- L66 _public function_ `float GetAngleDegree() const`
- L71 _public prototype_ `void SetStartDegree(float InDegree);`
- L72 _public function_ `float GetStartDegree() const`
- L80 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L84 _protected prototype_ `virtual void OnHeightChanged();`
- L85 _protected prototype_ `virtual void OnBaseRadiusChanged();`
- L86 _protected prototype_ `virtual void OnTopRadiusChanged();`
- L87 _protected prototype_ `virtual void OnNumSidesChanged();`
- L88 _protected prototype_ `virtual void OnAngleDegreeChanged();`
- L89 _protected prototype_ `virtual void OnStartDegreeChanged();`
- L91 _protected prototype_ `virtual bool CreateBaseUVs(FAvaShapeMesh& BaseMesh, FAvaShapeMaterialUVParameters& InUseParams);`
- L92 _protected prototype_ `virtual bool GenerateBaseMeshSections(FAvaShapeMesh& BottomMesh);`
- L94 _protected prototype_ `virtual bool CreateTopUVs(FAvaShapeMesh& TopMesh, FAvaShapeMaterialUVParameters& InUseParams);`
- L95 _protected prototype_ `virtual bool GenerateTopMeshSections(FAvaShapeMesh& TopMesh);`
- L97 _protected prototype_ `virtual bool CreateConeUVs(FAvaShapeMesh& ConeMesh, FAvaShapeMaterialUVParameters& InUseParams);`
- L98 _protected prototype_ `virtual bool GenerateConeMeshSections(FAvaShapeMesh& ConeMesh);`
- L100 _protected prototype_ `virtual bool CreateStartUVs(FAvaShapeMesh& StartMesh, FAvaShapeMaterialUVParameters& InUseParams);`
- L101 _protected prototype_ `virtual bool GenerateStartMeshSections(FAvaShapeMesh& StartMesh);`
- L103 _protected prototype_ `virtual bool CreateEndUVs(FAvaShapeMesh& EndMesh, FAvaShapeMaterialUVParameters& InUseParams);`
- L104 _protected prototype_ `virtual bool GenerateEndMeshSections(FAvaShapeMesh& EndMesh);`
- L106 _protected prototype_ `virtual void RegisterMeshes() override;`
- L107 _protected prototype_ `virtual bool IsMeshVisible(int32 MeshIndex) override;`
- L108 _protected prototype_ `virtual bool CreateMesh(FAvaShapeMesh& InMesh) override;`
- L109 _protected prototype_ `virtual bool CreateUVs(FAvaShapeMesh& InMesh, FAvaShapeMaterialUVParameters& InParams) override;`
- L110 _protected prototype_ `virtual bool CanUpdateMeshInAnyThread() const override;`
- L114 _protected member_ `uint8 NumSides;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Setter, Getter, Category="Shape", meta=(ClampMin="3.0", ClampMax="128.0", DisplayName="Sides", AllowPrivateAccess="true"))` — The number of sides around the base of the cone
- L118 _protected member_ `float TopRadius;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Setter, Getter, Category="Shape", meta=(ClampMin="0.0", ClampMax="1.0", DisplayName="Top radius ratio", AllowPrivateAccess="true"))` — the ratio for the radius of the cone top
- L122 _protected member_ `float AngleDegree;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Setter, Getter, Category="Shape", meta=(ClampMin="0.0", ClampMax="360.0", DisplayName="Angle degree", AllowPrivateAccess="true"))` — represents the base angle in degree for the cone
- L126 _protected member_ `float StartDegree;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Setter, Getter, Category="Shape", meta=(ClampMin="0.0", ClampMax="360.0", DisplayName="Start Degree", AllowPrivateAccess="true"))` — represents the starting angle in degree for the cone
- L131 _private member_ `float Height;` — `UPROPERTY()` — The height of the cone from the base to the top
- L135 _private member_ `float BaseRadius;` — `UPROPERTY()` — the radius of the cone base

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheShapes/Public/DynamicMeshes/AvaShapeCubeDynMesh.h` (Public)


#### class `UAvaShapeCubeDynamicMesh`  
`class UAvaShapeCubeDynamicMesh : public UAvaShape3DDynMeshBase`  
_L9-120_
- reflection: `UCLASS(MinimalAPI, ClassGroup="Shape", BlueprintType, CustomConstructor, Within=AvaShapeActor)`
- inherits: `UAvaShape3DDynMeshBase`
- L16 _public member_ `static const FString MeshName;`
- L18 _public member_ `static constexpr uint8 MinBevelNum = 1;`
- L19 _public member_ `static constexpr uint8 MaxBevelNum = 8;`
- L21 _public member_ `static constexpr int32 MESH_INDEX_TOP = 1;`
- L22 _public member_ `static constexpr int32 MESH_INDEX_BOTTOM = 2;`
- L23 _public member_ `static constexpr int32 MESH_INDEX_BACK = 3;`
- L24 _public member_ `static constexpr int32 MESH_INDEX_LEFT = 4;`
- L25 _public member_ `static constexpr int32 MESH_INDEX_RIGHT = 5;`
- L27 _public function_ `UAvaShapeCubeDynamicMesh() : UAvaShapeCubeDynamicMesh(FVector(50.f, 50.f, 50.f))`
- L31 _public function_ `UAvaShapeCubeDynamicMesh( const FVector& InSize, const FLinearColor& InVertexColor = FLinearColor::White, float InSegment = 1.f, float InBevel = 0.f, uint8 InBevelNum = 1) : UAvaShape3DDynMeshBase(InSize, InVertexColor) , BevelSizeRatio(InBevel) , BevelNum(InBevelNum) , Segment(InSegment)`
- L43 _public function_ `virtual const FString& GetMeshName() const override`
- L48 _public prototype_ `void SetSegment(float InSegment);`
- L49 _public function_ `float GetSegment() const`
- L54 _public prototype_ `void SetBevelSizeRatio(float InBevel);`
- L55 _public function_ `float GetBevelSizeRatio() const`
- L60 _public prototype_ `void SetBevelNum(uint8 InBevel);`
- L61 _public function_ `uint8 GetBevelNum() const`
- L69 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L73 _protected prototype_ `virtual void OnSegmentChanged();`
- L74 _protected prototype_ `virtual void OnBevelSizeChanged();`
- L75 _protected prototype_ `virtual void OnBevelNumChanged();`
- L77 _protected prototype_ `virtual float GetMaxBevelSize() const;`
- L78 _protected prototype_ `virtual FVector GetBevelSize() const;`
- L79 _protected prototype_ `virtual FVector GetSegmentSize() const;`
- L80 _protected prototype_ `virtual FVector GetScaleSize() const;`
- L82 _protected prototype_ `virtual void CreateBevelCorner(FAvaShapeMesh& InMesh, const FVector& CornerStartLoc, const FVector& CornerEndLoc, const FVector& StartNormal, int32 PrevStartIdx, int32 PrevEndIdx, const FVector& BevelSize, const FVector& Scale, const FVector& CornerStartVtxLoc, const FVector& CornerEndVtxLoc);`
- L85 _protected prototype_ `virtual void RegisterMeshes() override;`
- L86 _protected prototype_ `virtual bool IsMeshVisible(int32 MeshIndex) override;`
- L87 _protected prototype_ `virtual void OnSizeChanged() override;`
- L88 _protected prototype_ `virtual bool CanUpdateMeshInAnyThread() const override;`
- L90 _protected prototype_ `virtual bool GenerateBottomMeshSections(FAvaShapeMesh& BottomMesh);`
- L92 _protected prototype_ `virtual bool GenerateTopMeshSections(FAvaShapeMesh& TopMesh);`
- L94 _protected prototype_ `virtual bool GenerateFrontMeshSections(FAvaShapeMesh& FrontMesh);`
- L96 _protected prototype_ `virtual bool GenerateBackMeshSections(FAvaShapeMesh& BackMesh);`
- L98 _protected prototype_ `virtual bool GenerateLeftMeshSections(FAvaShapeMesh& LeftMesh);`
- L100 _protected prototype_ `virtual bool GenerateRightMeshSections(FAvaShapeMesh& RightMesh);`
- L102 _protected prototype_ `virtual bool CreateFaceUVs(FAvaShapeMesh& InMesh, FAvaShapeMaterialUVParameters& InUseParams, FRotator ProjectionDirection, FVector2D UVScale, FVector2D UVOffset);`
- L104 _protected prototype_ `virtual bool CreateMesh(FAvaShapeMesh& InMesh) override;`
- L106 _protected prototype_ `virtual bool CreateUVs(FAvaShapeMesh& InMesh, FAvaShapeMaterialUVParameters& InParams) override;`
- L110 _protected member_ `float BevelSizeRatio;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Setter, Getter, Category="Shape", meta=(ClampMin="0.0", DisplayName="Bevel Size", AllowPrivateAccess="true"))` — represents the bevel size applied on each face of the cube, 0 means no bevels
- L114 _protected member_ `uint8 BevelNum;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Setter, Getter, Category="Shape", meta=(ClampMin="1.0", ClampMax="8.0", DisplayName="Bevel Num", AllowPrivateAccess="true"))` — represents the bevel number of division, only valid when bevel size is greater than zero
- L119 _private member_ `float Segment;` — `UPROPERTY()` — segment size ratio to multiply with mesh size

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheShapes/Public/DynamicMeshes/AvaShapeDynMeshBase.h` (Public)


#### class `UAvaShapeDynamicMeshBase`  
`class UAvaShapeDynamicMeshBase : public UActorComponent , public IAvaInteractiveToolsModeDetailsObject , public IAvaGizmoObjectInterface`  
_L28-530_
- reflection: `UCLASS(MinimalAPI, ClassGroup="Shape", Abstract, BlueprintType, CustomConstructor, EditInlineNew, DefaultToInstanced, HideCategories=(Tags, Activation, Cooking, AssetUserData, Navigation))`
- inherits: `UActorComponent,IAvaInteractiveToolsModeDetailsObject,IAvaGizmoObjectInterface`
- L42 _public member_ `static constexpr float MinSizeValue = UE_SMALL_NUMBER;`
- L43 _public member_ `static inline const FVector2D MinSize2D = FVector2D(MinSizeValue);`
- L44 _public member_ `static inline const FVector MinSize3D = FVector(MinSizeValue);`
- L46 _public member_ `static constexpr uint8 DefaultSubdivisions = 8;`
- L47 _public member_ `static constexpr uint8 MaxSubdivisions = 64;`
- L49 _public member_ `static constexpr int32 MESH_INDEX_NONE = -1;`
- L50 _public member_ `static constexpr int32 MESH_INDEX_ALL = INT_MAX;`
- L51 _public member_ `static constexpr int32 MESH_INDEX_PRIMARY = 0;`
- L53 _public member_ `static inline FMaskEnabledDelegate OnMaskEnabled;`
- L54 _public member_ `static inline FMaskDisabledDelegate OnMaskDisabled;`
- L55 _public member_ `static inline FMaskVisibilityDelegate OnMaskVisibility;`
- L57 _public function_ `UAvaShapeDynamicMeshBase(const FObjectInitializer& ObjectInitializer) : UAvaShapeDynamicMeshBase(FLinearColor::White)`
- L61 _public prototype_ `UAvaShapeDynamicMeshBase(const FLinearColor& InVertexColor = FLinearColor::White, float InUniformScaledSize = 1.f, bool bInAllowEditSize = true);`
- L65 _public prototype_ `AAvaShapeActor* GetShapeActor() const;` — Converts the Outer of this object to a AAvaShapeActor.
- L68 _public prototype_ `UDynamicMeshComponent* GetShapeMeshComponent() const;` — Gets the Dynamic Mesh component from the Shape actor, this will load it if its nullptr
- L71 _public prototype_ `virtual const FString& GetMeshName() const;` — Get the name of the shape
- L75 _public prototype_ `TArray<FName> GetMeshSectionNames() const;` — `UFUNCTION(BlueprintCallable, Category="Shape")` — Returns the name of the sections composing this mesh
- L79 _public function_ `bool GetAllowEditSize() const` — `UFUNCTION(BlueprintPure, Category="Shape")` — Can we change the size of this shape
- L85 _public function_ `virtual void SetSize3D(const FVector& InSize)` — `UFUNCTION(BlueprintCallable, Category="Shape")`
- L88 _public function_ `virtual FVector GetSize3D() const` — `UFUNCTION(BlueprintPure, Category="Shape")`
- L94 _public prototype_ `virtual void SetSize2D(const FVector2D& InSize2D);` — `UFUNCTION(BlueprintCallable, Category="Shape")`
- L97 _public prototype_ `virtual FVector2D GetSize2D() const;` — `UFUNCTION(BlueprintPure, Category="Shape")`
- L101 _public prototype_ `bool IsMeshSectionVisible(int32 InIndex) const;` — `UFUNCTION(BlueprintPure, Category="Shape")` — Checks if a mesh section is currently visible
- L105 _public prototype_ `void SetUsePrimaryMaterialEverywhere(bool bInUse);` — `UFUNCTION(BlueprintCallable, Category="Shape")` — Set Primary material override
- L108 _public function_ `bool GetUsePrimaryMaterialEverywhere() const` — `UFUNCTION(BlueprintPure, Category="Shape")`
- L114 _public prototype_ `void SetUniformScaledSize(float InSize);` — `UFUNCTION(BlueprintCallable, Category="Shape")`
- L117 _public function_ `float GetUniformScaledSize() const` — `UFUNCTION(BlueprintPure, Category="Shape")`
- L124 _public prototype_ `bool IsValidMeshIndex(int32 InMeshIndex) const;` — `UFUNCTION(BlueprintPure, Category="Shape")` — Checks if the mesh section is valid
- L127 _public prototype_ `void SetMaterialType(int32 InMeshIndex, EMaterialType InType);` — `UFUNCTION(BlueprintCallable, Category="Shape")`
- L130 _public prototype_ `EMaterialType GetMaterialType(int32 InMeshIndex);` — `UFUNCTION(BlueprintPure, Category="Shape")`
- L132 _public prototype_ `bool IsMaterialType(int32 MeshIndex, EMaterialType Type);`
- L136 _public prototype_ `UMaterialInterface* GetMaterial(int32 InMeshIndex) const;` — `UFUNCTION(BlueprintPure, Category="Shape")` — Get the material of a mesh section
- L140 _public prototype_ `void SetMaterial(int32 InMeshIndex, UMaterialInterface* InNewMaterial);` — `UFUNCTION(BlueprintCallable, Category="Shape")` — Set the material of a mesh section
- L144 _public prototype_ `void SetParametricMaterial(int32 InMeshIndex, const FAvaShapeParametricMaterial& InNewMaterialParams);` — `UFUNCTION(BlueprintCallable, Category="Shape")` — Set parametric material of a section, internal materials are not copied over, only settings
- L148 _public prototype_ `const FAvaShapeParametricMaterial& GetParametricMaterial(int32 InMeshIndex) const;` — `UFUNCTION(BlueprintPure, Category="Shape")` — Get parametric material of a mesh section
- L150 _public prototype_ `FAvaShapeParametricMaterial* GetParametricMaterialPtr(int32 InMeshIndex);`
- L154 _public prototype_ `void SetOverridePrimaryUVParams(int32 InMeshIndex, bool bInOverride);` — `UFUNCTION(BlueprintCallable, Category="Shape")` — Use custom uv params per mesh section instead of using the primary one
- L157 _public prototype_ `bool GetOverridePrimaryUVParams(int32 InMeshIndex) const;` — `UFUNCTION(BlueprintPure, Category="Shape")`
- L160 _public prototype_ `void SetMaterialUVParams(int32 InMeshIndex, const FAvaShapeMaterialUVParameters& InParams);` — `UFUNCTION(BlueprintCallable, Category="Shape")`
- L163 _public prototype_ `const FAvaShapeMaterialUVParameters& GetMaterialUVParams(int32 InMeshIndex) const;` — `UFUNCTION(BlueprintPure, Category="Shape")`
- L165 _public prototype_ `FAvaShapeMaterialUVParameters* GetMaterialUVParamsPtr(int32 MeshIndex);`
- L169 _public prototype_ `EAvaShapeUVMode GetMaterialUVMode(int32 MeshIndex) const;`
- L170 _public prototype_ `bool SetMaterialUVMode(int32 MeshIndex, EAvaShapeUVMode InUVMode);`
- L172 _public prototype_ `EAvaAnchors GetMaterialUVAnchorPreset(int32 MeshIndex) const;`
- L173 _public prototype_ `bool SetMaterialUVAnchorPreset(int32 MeshIndex, EAvaAnchors InUVAnchorPreset);`
- L175 _public prototype_ `float GetMaterialUVRotation(int32 MeshIndex) const;`
- L176 _public prototype_ `bool SetMaterialUVRotation(int32 MeshIndex, float InUVRotation);`
- L178 _public prototype_ `const FVector2D& GetMaterialUVAnchor(int32 MeshIndex) const;`
- L179 _public prototype_ `bool SetMaterialUVAnchor(int32 MeshIndex, const FVector2D& InUVAnchor);`
- L181 _public prototype_ `const FVector2D& GetMaterialUVScale(int32 MeshIndex) const;`
- L182 _public prototype_ `bool SetMaterialUVScale(int32 MeshIndex, const FVector2D& InUVScale);`
- L184 _public prototype_ `const FVector2D& GetMaterialUVOffset(int32 MeshIndex) const;`
- L185 _public prototype_ `bool SetMaterialUVOffset(int32 MeshIndex, const FVector2D& InUVOffset);`
- L187 _public prototype_ `bool GetMaterialHorizontalFlip(int32 MeshIndex) const;`
- L188 _public prototype_ `bool SetMaterialHorizontalFlip(int32 MeshIndex, bool InHorizontalFlip);`
- L190 _public prototype_ `bool GetMaterialVerticalFlip(int32 MeshIndex) const;`
- L191 _public prototype_ `bool SetMaterialVerticalFlip(int32 MeshIndex, bool InVerticalFlip);`
- L193 _public prototype_ `const FAvaShapeMaterialUVParameters* GetInUseMaterialUVParams(int32 MeshIndex) const;`
- L194 _public prototype_ `FAvaShapeMaterialUVParameters* GetInUseMaterialUVParams(int32 MeshIndex);`
- L196 _public function_ `bool HasMeshRegenWorldLocation() const`
- L197 _public function_ `const FVector& GetMeshRegenWorldLocation() const`
- L198 _public prototype_ `void SetMeshRegenWorldLocation(const FVector& NewLocation, bool bImmediateUpdate = false);`
- L201 _public prototype_ `virtual TArray<FAvaSnapPoint> GetLocalSnapPoints() const;` — Generate a list of 3d-space snap points for this shape
- L202 _public prototype_ `void GetLocalSnapPoints(TArray<FAvaSnapPoint>& Points) const;`
- L204 _public prototype_ `FTransform GetTransform() const;`
- L207 _public prototype_ `bool ClearDynamicMeshSection(int32 MeshIndex);` — Clear the dynamic mesh section with a specific index
- L210 _public prototype_ `bool ClearDynamicMesh();` — Clear the whole dynamic mesh
- L213 _public prototype_ `bool ExportToStaticMesh(UStaticMesh* DestinationMesh);` — Converts dynamic mesh to static mesh
- L217 _public function_ `virtual void GetBounds(FVector& Origin, FVector& BoxExtent, FVector& Pivot) const` — Gets the bounds of the shape, override this in child classes for custom bounds Origin is the center of the box, BoxExtent is half the size, pivot is the default location of the pivot for this shape
- L219 _public prototype_ `virtual void OnColorPicked(const FAvaColorChangeData& InNewColorData);`
- L220 _public prototype_ `virtual FAvaColorChangeData GetActiveColor() const;`
- L223 _public prototype_ `TSet<int32> GetMeshesIndexes() const;` — Get the registered meshes indexes
- L226 _public prototype_ `FAvaShapeMeshData* GetMeshData(int32 InMeshIndex);` — find a registered mesh and gets a pointer to it
- L229 _public prototype_ `const FAvaShapeMeshData* GetMeshData(int32 InMeshIndex) const;` — find a registered mesh and gets a pointer to it
- L231 _public function_ `const TMap<int32, FAvaShapeMeshData>& GetMeshDatas() const`
- L237 _public prototype_ `bool ApplyUVsTransform(FAvaShapeMesh& InMesh, FAvaShapeMaterialUVParameters& InParams, FVector2D ShapeSize, FVector2D UVFixOffset, float UVFixRotation = 0.f);` — apply scale, offset, rotation on dynamic mesh section
- L240 _public prototype_ `void SetRunAsync(bool bInAsync);` — Set whether mesh update should run async or not
- L241 _public function_ `bool GetRunAsync() const`
- L247 _public prototype_ `void RefreshParametricMaterial();` — Updates parametric material by reapplying parameters
- L250 _protected prototype_ `static bool SetAlignmentSize(AActor* InActor, const FVector& InSizeMultiplier);`
- L251 _protected prototype_ `static EAvaAnchors GetAnchorFromNumerics(const FVector2D& AnchorNumeric);`
- L252 _protected prototype_ `static FVector2D GetNumericsFromAnchor(EAvaAnchors AnchorEnum);`
- L255 _protected prototype_ `virtual void OnRegister() override;`
- L256 _protected prototype_ `virtual void OnComponentCreated() override;`
- L257 _protected prototype_ `virtual void OnComponentDestroyed(bool bDestroyingHierarchy) override;`
- L261 _protected prototype_ `virtual void PostLoad() override;`
- L263 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L264 _protected prototype_ `virtual void PostEditChangeChainProperty(FPropertyChangedChainEvent& PropertyChangedEvent) override;`
- L265 _protected prototype_ `virtual void PreEditUndo() override;`
- L266 _protected prototype_ `virtual void PostEditUndo() override;`
- L267 _protected prototype_ `virtual void PostEditImport() override;`
- L268 _protected prototype_ `virtual void PostDuplicate(EDuplicateMode::Type DuplicateMode) override;`
- L272 _protected prototype_ `void OnAssetDropped(UObject* DroppedObj, AActor* TargetActor);` — triggers when we drop an asset (material) onto our actor
- L276 _protected prototype_ `virtual void ToggleGizmo_Implementation(const UAvaGizmoComponent* InGizmoComponent, const bool bShowAsGizmo) override;`
- L279 _protected function_ `EAvaDynamicMeshUpdateState GetMeshUpdateStatus() const`
- L282 _protected prototype_ `bool IsMeshSizeValid() const;` — Checks if shape size is render-able and not minimal
- L285 _protected prototype_ `void MarkAllMeshesDirty();` — Flag all mesh sections dirty to regenerate them
- L288 _protected prototype_ `void MarkVerticesDirty();` — Only update vertices from mesh
- L291 _protected prototype_ `void SetupMeshes();` — Register all meshes once, calls RegisterMeshes()
- L294 _protected function_ `virtual void RegisterMeshes()` — override this in child classes, to register new meshes
- L297 _protected prototype_ `bool RegisterMesh(FAvaShapeMeshData& NewMeshData);` — Call to register meshes used for this shape, call this inside RegisterMeshes()
- L300 _protected function_ `virtual void OnRegisteredMesh(int32 MeshIndex)` — Called when a new mesh has been registered
- L303 _protected function_ `virtual void OnRegisteredMeshes()` — Called when all the meshes have been registered and the setup is done
- L306 _protected prototype_ `virtual bool IsMeshDirty(int32 MeshIndex);` — Returns whether the mesh is dirty, called before creating mesh if visible
- L309 _protected prototype_ `virtual bool IsMeshVisible(int32 MeshIndex);` — override this in child classes, called before creating mesh if visible
- L312 _protected prototype_ `FName GetMeshSectionName(int32 InMeshIndex) const;` — Returns the name of the mesh
- L315 _protected prototype_ `const TArray<UMaterialInterface*> GetMeshDataMaterials();` — Returns the materials used by every mesh
- L318 _protected prototype_ `bool IsDynamicMeshInitialized() const;` — Checks to see if attributes are initialized and mesh is ready
- L321 _protected prototype_ `void InitializeDynamicMesh();` — Clears everything and reinitialize the DM to use it properly
- L323 _protected prototype_ `bool SetMaterialDirect(int32 MeshIndex, UMaterialInterface* NewMaterial);`
- L326 _protected prototype_ `virtual void OnMeshUpdateFinished();` — called once the mesh is done updating
- L329 _protected function_ `virtual void OnPixelSizeChanged()` — called once the pixel size has changed, only in editor
- L331 _protected prototype_ `virtual void OnMeshChanged(int32 MeshIndex);`
- L332 _protected prototype_ `virtual void OnMaterialChanged(int32 MaterialIndex);`
- L333 _protected prototype_ `virtual void OnMaterialTypeChanged(int32 MaterialIndex);`
- L334 _protected prototype_ `virtual void OnParametricMaterialChanged(int32 MaterialIndex);`
- L335 _protected prototype_ `virtual void OnUVParamsChanged(int32 MeshIndex);`
- L336 _protected prototype_ `virtual void OnUsesPrimaryUVParamsChanged(int32 MeshIndex);`
- L338 _protected prototype_ `virtual bool OnMeshSectionUpdated(FAvaShapeMesh& InMesh);`
- L341 _protected function_ `virtual void OnScaledSizeChanged()` — override this in child classes
- L344 _protected function_ `virtual void OnSizeChanged()` — override this in child classes, for 2D and 3D shape to update the scale
- L347 _protected prototype_ `virtual bool ClearMesh();` — Clears the mesh sections that are dirty
- L350 _protected prototype_ `virtual void UpdateVertices();` — Special case when the mesh is scaled, rather than reconfigured.
- L353 _protected prototype_ `bool ApplyUVsManually(FAvaShapeMesh& InMesh);` — sets the uvs manually on a dynamic mesh section
- L356 _protected prototype_ `bool ApplyUVsPlanarProjection(FAvaShapeMesh& InMesh, FRotator PlaneRotation, FVector2D PlaneSize);` — apply a planar projection on a dynamic mesh section
- L359 _protected prototype_ `bool ApplyUVsBoxProjection(FAvaShapeMesh& InMesh, FRotator BoxRotation, FVector BoxSize);` — apply a box projection on a dynamic mesh section
- L362 _protected prototype_ `virtual bool CreateUVs(FAvaShapeMesh& InMesh, FAvaShapeMaterialUVParameters& InParams);` — override this in child classes when you create UV for a specific mesh
- L365 _protected function_ `virtual bool CreateMesh(FAvaShapeMesh& InMesh)` — override this in child classes to create the mesh if it's visible
- L368 _protected prototype_ `bool HasSameTopology(FAvaShapeMesh& InMesh);` — checks whether the topology of the mesh has changed (different vertices count and different triangles count than current)
- L371 _protected prototype_ `bool CreateDynamicMesh(FAvaShapeMesh& InMesh);` — Creates a section in the dynamic mesh component
- L374 _protected prototype_ `bool UpdateDynamicMesh(FAvaShapeMesh& InMesh);` — Updates a section in the dynamic mesh component
- L377 _protected prototype_ `void InvalidateSection(bool& bInvalidatedSection, bool bRequireUpdate = true);` — Invalidates a section and runs the mesh update if necessary
- L380 _protected prototype_ `void MarkMeshDirty(int32 MeshIndex);` — Flag a mesh section dirty to regenerate it
- L386 _protected function_ `virtual bool CanUpdateMeshInAnyThread() const` — Determines whether shape mesh can be done from a different thread. All built-in meshes are safe to build in a different thread. This virtual would need to be overriden for any derived class that ensures thread safety.
- L397 _protected prototype_ `void UpdateMesh(const FMeshUpdateContext& InUpdateContext);` — Takes all dirty flags, regenerate whatever is needed and updates the DMC, called by RunUpdate or RequireUpdate
- L400 _protected prototype_ `void OffsetActorToAlign();` — Offsets actor to account for the mesh generated location
- L403 _protected prototype_ `void PreUpdateMesh();` — Part of update flow that can only be performed safely on the game thread. Should be called before UpdateMesh_AnyThread
- L406 _protected prototype_ `void PostUpdateMesh();` — Part of update flow that can only be performed safely on the game thread. Should be called after UpdateMesh_AnyThread
- L409 _protected prototype_ `void ApplyMeshSectionChanges();` — Pushed mesh section data updates to dynamic mesh and creates/updates geometry data
- L412 _protected prototype_ `void RequestUpdate();` — runs the update for this mesh, async by default
- L415 _protected prototype_ `bool CheckMaterialSlotChanges();` — used to check for material changes in slot of DMC to match with our current material settings
- L418 _protected prototype_ `void SetShapeComponentMaterial(int32 InMaterialIndex, UMaterialInterface* InNewMaterial);` — Changes the material on the shape component and keeps the MDI up to date.
- L421 _protected prototype_ `void ScaleVertices(const FVector& InScale);` — Scale the vertices on all sections of the mesh
- L422 _protected prototype_ `void ScaleVertices(const FVector2D& InScale);`
- L426 _protected member_ `bool bAllowEditSize;` — `UPROPERTY(Getter="GetAllowEditSize")` — Is mesh size editing allowed
- L430 _protected member_ `ESizeType SizeType = ESizeType::UnrealUnit;` — `UPROPERTY(EditInstanceOnly, Category="Shape", Transient, meta=(DisplayName="Size Type", HideEditConditionToggle, EditCondition="bAllowEditSize", EditConditionHides, AllowPrivateAccess="true"))` — the type of size you want to handle
- L434 _protected member_ `float UniformScaledSize = 1.f;` — `UPROPERTY(EditInstanceOnly, Transient, Setter, Getter, Category="Shape", meta=(ClampMin="0.0", DisplayName="Uniform Scaled Size", Units="times", AllowPrivateAccess="true"))` — Uniform scaled size of the mesh
- L438 _protected member_ `bool bUsePrimaryMaterialEverywhere;` — `UPROPERTY(EditInstanceOnly, Setter="SetUsePrimaryMaterialEverywhere", Getter="GetUsePrimaryMaterialEverywhere", Category="Material", meta=(DisplayName="Use Single Material", AllowPrivateAccess="true"))` — use primary material for every slot available
- L442 _protected member_ `TMap<int32, FAvaShapeMeshData> MeshDatas;` — `UPROPERTY(EditInstanceOnly, Category="Material", meta=(EditFixedOrder, EditFixedSize, AllowPrivateAccess="true"))` — Meshes used for the current shape sections
- L444 _protected member_ `TArray<FAvaSnapPoint> LocalSnapPoints;`
- L448 _private prototype_ `FTSTicker& GetTicker() const;` — Gets the ticker to use for shapes
- L450 _private prototype_ `FAvaShapeMesh* GetMesh(int32 MeshIndex);`
- L453 _private prototype_ `void MarkMeshRenderStateDirty() const;` — Update render state (materials)
- L456 _private prototype_ `bool GenerateMesh();` — Generates the dirty mesh sections
- L459 _private prototype_ `bool GenerateUV();` — Generates the uvs for the mesh (all sections)
- L462 _private prototype_ `bool GenerateTangents();` — Generates the tangents for the mesh (all sections)
- L465 _private prototype_ `bool GenerateNormals();` — Generates the normals for the mesh (all sections), needs the uv set on the mesh
- L468 _private prototype_ `void RunUpdate();` — runs the update for this mesh only if it's required (mesh is not up to date)
- L471 _private prototype_ `void RestoreCachedMesh(bool bInReset);` — Restore the existing saved cached mesh on the component
- L474 _private prototype_ `void SaveCachedMesh();` — Save the existing component mesh into a saved cached mesh
- L477 _private prototype_ `void OnUsePrimaryMaterialEverywhereChanged();` — Apply primary material everywhere
- L479 _private prototype_ `void OnMeshTransformChanged(USceneComponent* InComponent, EUpdateTransformFlags InTransformFlags, ETeleportType InTeleport);`
- L482 _private prototype_ `void OnParametricMaterialChanged(const FAvaShapeParametricMaterial& InMaterial);` — When a parametric material is updated, eg: opaque -> translucent
- L485 _private prototype_ `void OnParametricMaterialParameterChanged(const FAvaShapeParametricMaterial& InMaterial);` — When a parametric material parameter is updated
- L488 _private member_ `TOptional<UE::Geometry::FDynamicMesh3> CachedMesh;` — used to quickly restore mesh that has been modified after OnMeshUpdateFinished was called (eg extrude, masking)
- L491 _private member_ `TOptional<FMeshUpdateContext> MeshUpdateContext;` — the context while mesh is being built
- L494 _private member_ `TWeakObjectPtr<UDynamicMeshComponent> CachedComponent;` — Do not access directly use getter to load it if nullptr
- L497 _private member_ `FVector MeshRegenWorldLocation;` — `UPROPERTY()`
- L502 _private member_ `TMap<int32, FAvaShapeMeshData> NonGizmoMeshData;` — `UPROPERTY()` — Stores select settings to allow restoration when Gizmo mode turned off
- L506 _private member_ `EAvaDynamicMeshUpdateState MeshUpdateStatus = EAvaDynamicMeshUpdateState::UpToDate;` — only change this value from the base class to avoid thread lock, use RunUpdate() or RequireUpdate()
- L508 _private member_ `bool bHasNewMeshRegenWorldLocation;`
- L511 _private member_ `bool bMeshRegistered;` — flag to register meshes only once
- L514 _private member_ `bool bInCreateMode;` — whether we are in the tool shape mode and creating this shape
- L517 _private member_ `bool bAllMeshDirty;` — true if all meshes are marked as dirty, false otherwise, use MarkAllMeshesDirty() instead of modifying this
- L520 _private member_ `bool bAnyMeshDirty;` — true if at least one meshes is marked as dirty, false otherwise, use MarkMeshDirty(MeshIndex) instead of modifying this
- L523 _private member_ `bool bVerticesDirty;` — Should only be used when the shape's vertices have changed, but the overall shape has not changed.
- L526 _private member_ `bool bZeroScaled = false;` — Is the mesh scaled to zero ?
- L529 _private member_ `bool bRunAsync = true;` — Run mesh updates async

#### struct `UAvaShapeDynamicMeshBase::FMeshUpdateContext`  
`struct FMeshUpdateContext`  
_L391-395_
- L394 _public member_ `bool bParallel = false;` — Determines whether the update is taking place in parallel (potentially not the game thread)

#### Free symbols / members of external scopes

- L23 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FMaskEnabledDelegate, AActor* );`
- L23 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FMaskEnabledDelegate, AActor* );`
- L24 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FMaskDisabledDelegate, AActor* );`
- L24 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FMaskDisabledDelegate, AActor* );`
- L25 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FMaskVisibilityDelegate, const UWorld* , bool );`
- L25 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FMaskVisibilityDelegate, const UWorld* , bool );`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheShapes/Public/DynamicMeshes/AvaShapeEllipseDynMesh.h` (Public)


#### class `UAvaShapeEllipseDynamicMesh`  
`class UAvaShapeEllipseDynamicMesh : public UAvaShape2DDynMeshBase`  
_L9-83_
- reflection: `UCLASS(MinimalAPI, ClassGroup="Shape", BlueprintType, CustomConstructor, Within=AvaShapeActor)`
- inherits: `UAvaShape2DDynMeshBase`
- L16 _public member_ `static const FString MeshName;`
- L17 _public member_ `static constexpr uint8 MinNumSides = 3;`
- L18 _public member_ `static constexpr uint8 MaxNumSides = 128;`
- L20 _public function_ `UAvaShapeEllipseDynamicMesh() : UAvaShapeEllipseDynamicMesh(FVector2D(50.f, 50.f))`
- L24 _public function_ `UAvaShapeEllipseDynamicMesh(const FVector2D& Size2D, const FLinearColor& InVertexColor = FLinearColor::White, uint8 InNumSides = 64, float InAngleDegree = 360.f, float InStartDegree = 0.f) : UAvaShape2DDynMeshBase(Size2D, InVertexColor) , NumSides(InNumSides) , AngleDegree(InAngleDegree) , StartDegree(InStartDegree)`
- L34 _public function_ `virtual const FString& GetMeshName() const override`
- L39 _public prototype_ `void SetNumSides(uint8 InNumSides);`
- L40 _public function_ `uint8 GetNumSides() const`
- L45 _public prototype_ `void SetAngleDegree(float InDegree);`
- L46 _public function_ `float GetAngleDegree() const`
- L51 _public prototype_ `void SetStartDegree(float InDegree);`
- L52 _public function_ `float GetStartDegree() const`
- L60 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L64 _protected prototype_ `virtual void OnNumSidesChanged();`
- L65 _protected prototype_ `virtual void OnAngleDegreeChanged();`
- L66 _protected prototype_ `virtual void OnStartDegreeChanged();`
- L68 _protected prototype_ `virtual bool IsMeshVisible(int32 MeshIndex) override;`
- L69 _protected prototype_ `virtual bool CreateMesh(FAvaShapeMesh& InMesh) override;`
- L70 _protected prototype_ `virtual bool CanUpdateMeshInAnyThread() const override;`
- L74 _protected member_ `uint8 NumSides;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Setter, Getter, Category="Shape", meta=(ClampMin="3.0", ClampMax="128.0", DisplayName="Sides", AllowPrivateAccess="true"))` — The number of sides for the shape
- L78 _protected member_ `float AngleDegree;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Setter, Getter, Category="Shape", meta=(ClampMin="0.0", ClampMax="360.0", DisplayName="Angle degree", AllowPrivateAccess="true"))` — represents the angle in degree for the ellipse
- L82 _protected member_ `float StartDegree;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Setter, Getter, Category="Shape", meta=(ClampMin="0.0", ClampMax="360.0", DisplayName="Start Degree", AllowPrivateAccess="true"))` — represents the starting angle in degree for the ellipse

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheShapes/Public/DynamicMeshes/AvaShapeIrregularPolygonDynMesh.h` (Public)


#### struct `FAvaShapeRoundedCornerSettings`  
`struct FAvaShapeRoundedCornerSettings`  
_L10-19_
- reflection: `USTRUCT(BlueprintType)`
- L15 _public member_ `float BevelSize = 0.f;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category="Shape", meta=(ClampMin="0.0",ClampMax="1.0"))`
- L18 _public member_ `uint8 BevelSubdivisions = UAvaShapeDynamicMeshBase::DefaultSubdivisions;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category="Shape", meta=(ClampMax="64.0"))`

#### struct `FAvaShapeRoundedCorner`  
`struct FAvaShapeRoundedCorner`  
_L22-45_
- reflection: `USTRUCT(BlueprintType)`
- L26 _public function_ `FAvaShapeRoundedCorner() : FAvaShapeRoundedCorner(FVector2D::ZeroVector)`
- L30 _public function_ `FAvaShapeRoundedCorner(const FVector2D& InLocation)`
- L39 _public member_ `FVector2D Location;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category="Shape")`
- L42 _public member_ `FAvaShapeRoundedCornerSettings Settings;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category="Shape", meta=(DisplayName="Corner"))`
- L44 _public member_ `FAvaShapeRoundedCornerMetrics CornerMetrics;`

#### class `UAvaShapeIrregularPolygonDynamicMesh`  
`class UAvaShapeIrregularPolygonDynamicMesh : public UAvaShape2DDynMeshBase`  
_L48-174_
- reflection: `UCLASS(MinimalAPI, ClassGroup="Shape", BlueprintType, CustomConstructor, Within=AvaShapeActor)`
- inherits: `UAvaShape2DDynMeshBase`
- L55 _public member_ `static const FString MeshName;`
- L56 _public member_ `static const float MinPointDistance;`
- L58 _public prototype_ `static bool DoLinesIntersect(const FVector2D Origin1, const FVector2D End1, const FVector2D Origin2, const FVector2D End2);`
- L60 _public function_ `UAvaShapeIrregularPolygonDynamicMesh(const FObjectInitializer& ObjectInitializer) : UAvaShapeIrregularPolygonDynamicMesh(FLinearColor::White)`
- L64 _public function_ `UAvaShapeIrregularPolygonDynamicMesh(const FLinearColor& InVertexColor) : UAvaShape2DDynMeshBase(FVector2D::Zero(), InVertexColor)`
- L71 _public function_ `virtual const FString& GetMeshName() const override`
- L76 _public prototype_ `void SetGlobalBevelSize(float InBevelSize);`
- L77 _public function_ `float GetGlobalBevelSize() const`
- L82 _public prototype_ `void SetGlobalBevelSubdivisions(uint8 InBevelSubdivisions);`
- L83 _public function_ `uint8 GetGlobalBevelSubdivisions() const`
- L88 _public prototype_ `void SetPoints(const TArray<FVector2D>& InPoints);`
- L89 _public prototype_ `void SetPoints(const TArray<FAvaShapeRoundedCorner>& InPoints);`
- L90 _public function_ `const TArray<FAvaShapeRoundedCorner>& GetPoints() const`
- L95 _public function_ `const FAvaShapeRoundedCorner& GetPoint(int32 PointIdx) const`
- L100 _public function_ `int32 GetNumPoints() const`
- L105 _public prototype_ `bool CanAddPoint(const FVector2D& InPoint);`
- L106 _public prototype_ `bool AddPoint(const FVector2D& InPoint);`
- L107 _public prototype_ `bool RemovePoint(int32 PointIdx);`
- L108 _public prototype_ `bool RemoveFirstPoint();`
- L109 _public prototype_ `bool RemoveLastPoint();`
- L110 _public prototype_ `bool RemoveAllPoints();`
- L111 _public prototype_ `void RecalculateActorPosition();`
- L116 _protected prototype_ `virtual void PreEditChange(FProperty* PropertyAboutToChange) override;`
- L117 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L121 _protected prototype_ `void RecalculateExtent();`
- L123 _protected prototype_ `bool SetLocation(int32 PointIdx, const FVector2D& InPoint);`
- L124 _protected prototype_ `bool SetBevelSize(int32 PointIdx, float InBevelSize);`
- L125 _protected prototype_ `bool SetBevelSubdivisions(int32 PointIdx, uint8 InBevelSubdivisions);`
- L127 _protected prototype_ `bool ShiftPoints(const FVector2D& Amount);`
- L129 _protected prototype_ `bool DoesLineIntersectBorder(const FVector2D CheckOrigin, const FVector2D CheckEnd) const;`
- L132 _protected prototype_ `bool IsPointTooCloseToAnotherPoint(const FVector2D& InPoint, bool bAllowExactlyOneMatch = false) const;` — Checks to see if this point is too near to other points.
- L133 _protected prototype_ `bool IsPointTooCloseToALine(const FVector2D& InPoint) const;`
- L134 _protected prototype_ `bool IsLineTooCloseToAPoint(const FVector2D& Start, const FVector2D& End) const;`
- L135 _protected prototype_ `bool CanBeGenerated() const;`
- L137 _protected prototype_ `bool IsLocationInsideShape(const FVector2D& Location);`
- L139 _protected prototype_ `void BackupPoints();`
- L141 _protected prototype_ `float GetMaxBevelSizeForPoint(int32 PointIdx) const;`
- L144 _protected prototype_ `bool BreakSide(int32 InPointIdx);` — Breaks the line, adding a new point, in between InPointIdx and InPointIdx+1
- L146 _protected prototype_ `void RestorePoints();`
- L147 _protected prototype_ `bool CheckNewPointsArray();`
- L148 _protected prototype_ `void OnPointsUpdated();`
- L149 _protected prototype_ `void OnLocationsUpdated();`
- L150 _protected prototype_ `void OnBevelSizeChanged();`
- L151 _protected prototype_ `void OnBevelSubdivisionsChanged();`
- L152 _protected prototype_ `void OnGlobalBevelSizeChanged();`
- L153 _protected prototype_ `void OnGlobalBevelSubdivisionsChanged();`
- L155 _protected prototype_ `void OnLocationUpdated(int32 InPointIdx);`
- L156 _protected prototype_ `void OnBevelSizeChanged(int32 PointIdx);`
- L157 _protected prototype_ `void OnBevelSubdivisionsChanged(int32 PointIdx);`
- L159 _protected prototype_ `FVector ScreenToWorld(const FVector2D& ScreenLocation) const;`
- L161 _protected prototype_ `virtual bool ClearMesh() override;`
- L162 _protected prototype_ `virtual bool CreateMesh(FAvaShapeMesh& InMesh) override;`
- L163 _protected prototype_ `virtual bool CanUpdateMeshInAnyThread() const override;`
- L166 _protected member_ `float GlobalBevelSize = 0.f;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Setter, Getter, Category="Shape", meta=(ClampMin="0.0",ClampMax="1.0", AllowPrivateAccess="true"))`
- L169 _protected member_ `uint8 GlobalBevelSubdivisions = DefaultSubdivisions;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Setter, Getter, Category="Shape", meta=(ClampMax="64.0", AllowPrivateAccess="true"))`
- L172 _protected member_ `TArray<FAvaShapeRoundedCorner> Points;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Setter, Getter, Category="Shape", meta=(EditFixedOrder, AllowPrivateAccess="true"))`
- L173 _protected member_ `TArray<FAvaShapeRoundedCorner> PreEditPoints;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheShapes/Public/DynamicMeshes/AvaShapeLineDynMesh.h` (Public)


#### class `UAvaShapeLineDynamicMesh`  
`class UAvaShapeLineDynamicMesh : public UAvaShapeRoundedPolygonDynamicMesh`  
_L9-71_
- reflection: `UCLASS(MinimalAPI, ClassGroup="Shape", BlueprintType, CustomConstructor, Within=AvaShapeActor)`
- inherits: `UAvaShapeRoundedPolygonDynamicMesh`
- L16 _public member_ `static const FString MeshName;`
- L18 _public function_ `UAvaShapeLineDynamicMesh() : UAvaShapeLineDynamicMesh(FVector2D(50.f, 1.f))`
- L22 _public function_ `UAvaShapeLineDynamicMesh(const FVector2D& Size2D, const FLinearColor& InVertexColor = FLinearColor::White, float InBevelSize = 0.f, uint8 InBevelSubdivisions = 0, float InLineWidth = 5.f) : UAvaShapeRoundedPolygonDynamicMesh(Size2D, InVertexColor, InBevelSize, InBevelSubdivisions) , LineWidth(InLineWidth) , Vector(FVector2D(50.f, 0.f))`
- L31 _public function_ `virtual const FString& GetMeshName() const override`
- L36 _public prototype_ `void SetLineWidth(float InLineWidth);`
- L37 _public function_ `float GetLineWidth() const`
- L42 _public prototype_ `void SetVector(const FVector2D& InVector);`
- L43 _public function_ `const FVector2D& GetVector() const`
- L51 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L55 _protected prototype_ `void OnLineWidthChanged();`
- L56 _protected prototype_ `void OnVectorChanged();`
- L58 _protected prototype_ `void UpdateExtent();`
- L60 _protected prototype_ `TArray<FVector2D> GenerateLineVertices() const;`
- L62 _protected prototype_ `virtual bool IsMeshVisible(int32 MeshIndex) override;`
- L63 _protected prototype_ `virtual void GenerateBorderVertices(TArray<FVector2D>& BorderVertices) override;`
- L64 _protected prototype_ `virtual bool CanUpdateMeshInAnyThread() const override;`
- L67 _protected member_ `float LineWidth;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Setter, Getter, Category="Shape", meta=(ClampMin="0.0", AllowPrivateAccess="true"))`
- L70 _protected member_ `FVector2D Vector;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Setter, Getter, Category="Shape", meta=(AllowPrivateAccess="true"))`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheShapes/Public/DynamicMeshes/AvaShapeNGonDynMesh.h` (Public)


#### class `UAvaShapeNGonDynamicMesh`  
`class UAvaShapeNGonDynamicMesh : public UAvaShapeRoundedPolygonDynamicMesh`  
_L9-54_
- reflection: `UCLASS(MinimalAPI, ClassGroup="Shape", BlueprintType, CustomConstructor, Within=AvaShapeActor)`
- inherits: `UAvaShapeRoundedPolygonDynamicMesh`
- L16 _public member_ `static const FString MeshName;`
- L17 _public member_ `static inline constexpr float MinNumSides = 3.f;`
- L18 _public member_ `static inline constexpr float MaxNumSides = 128.f;`
- L20 _public function_ `UAvaShapeNGonDynamicMesh() : UAvaShapeNGonDynamicMesh(FVector2D(50.f, 50.f))`
- L24 _public function_ `UAvaShapeNGonDynamicMesh(const FVector2D& Size2D, const FLinearColor& InVertexColor = FLinearColor::White, float InBevelSize = 0.f, uint8 InBevelSubdivisions = 0, uint8 InNumSides = 5) : UAvaShapeRoundedPolygonDynamicMesh(Size2D, InVertexColor, InBevelSize, InBevelSubdivisions) , NumSides(InNumSides)`
- L30 _public function_ `virtual const FString& GetMeshName() const override`
- L35 _public prototype_ `void SetNumSides(uint8 InNumSides);`
- L36 _public function_ `uint8 GetNumSides() const`
- L44 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L48 _protected prototype_ `virtual void OnNumSidesChanged();`
- L49 _protected prototype_ `virtual void GenerateBorderVertices(TArray<FVector2D>& BorderVertices) override;`
- L50 _protected prototype_ `virtual bool CanUpdateMeshInAnyThread() const override;`
- L53 _protected member_ `uint8 NumSides;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Setter, Getter, Category="Shape", meta=(ClampMin="3.0", ClampMax="128.0", DisplayName="Sides", AllowPrivateAccess="true"))`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheShapes/Public/DynamicMeshes/AvaShapeRectangleDynMesh.h` (Public)


#### struct `FAvaShapeRectangleCornerSettings`  
`struct FAvaShapeRectangleCornerSettings`  
_L9-29_
- reflection: `USTRUCT(BlueprintType)`
- L13 _public function_ `bool IsBeveled() const`
- L19 _public member_ `EAvaShapeCornerType Type = EAvaShapeCornerType::Point;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category="Shape")`
- L22 _public member_ `float BevelSize = 0.f;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category="Shape", meta=(ClampMin="0.0",DisplayName="Size"))`
- L25 _public member_ `uint8 BevelSubdivisions = UAvaShapeDynamicMeshBase::DefaultSubdivisions;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category="Shape", meta=(ClampMax="64.0", DisplayName="Subdivisions"))`
- L28 _public member_ `FVector2D CornerPositionCache = FVector2D::ZeroVector;` — `UPROPERTY()`

#### class `UAvaShapeRectangleDynamicMesh`  
`class UAvaShapeRectangleDynamicMesh : public UAvaShape2DDynMeshBase`  
_L32-269_
- reflection: `UCLASS(MinimalAPI, ClassGroup="Shape", BlueprintType, CustomConstructor, Within=AvaShapeActor)`
- inherits: `UAvaShape2DDynMeshBase`
- L39 _public member_ `static const FString MeshName;`
- L40 _public member_ `static inline constexpr float MinSlantAngle = -45.f;`
- L41 _public member_ `static inline constexpr float MaxSlantAngle = 45.f;`
- L42 _public member_ `static inline constexpr float CornerMinMargin = 0.1f;`
- L44 _public function_ `UAvaShapeRectangleDynamicMesh() : UAvaShapeRectangleDynamicMesh(FVector2D(50.f, 50.f))`
- L48 _public function_ `explicit UAvaShapeRectangleDynamicMesh(const FVector2D& Size2D, const FLinearColor& InVertexColor = FLinearColor::White) : UAvaShape2DDynMeshBase(Size2D, InVertexColor)`
- L52 _public function_ `virtual const FString& GetMeshName() const override`
- L57 _public prototype_ `void SetHorizontalAlignment(EAvaHorizontalAlignment InHorizontalAlignment);`
- L58 _public function_ `EAvaHorizontalAlignment GetHorizontalAlignment() const`
- L63 _public prototype_ `void SetVerticalAlignment(EAvaVerticalAlignment InVerticalAlignment);`
- L64 _public function_ `EAvaVerticalAlignment GetVerticalAlignment() const`
- L69 _public prototype_ `void SetLeftSlant(float InSlant);`
- L70 _public function_ `float GetLeftSlant() const`
- L75 _public prototype_ `void SetRightSlant(float InSlant);`
- L76 _public function_ `float GetRightSlant() const`
- L81 _public prototype_ `void SetGlobalBevelSize(float InBevelSize);`
- L82 _public function_ `float GetGlobalBevelSize() const`
- L88 _public prototype_ `void SetGlobalBevelSubdivisions(uint8 InGlobalBevelSubdivisions);` — Controls all corners bevel subdivisions
- L89 _public function_ `uint8 GetGlobalBevelSubdivisions() const`
- L94 _public prototype_ `void SetTopLeft(const FAvaShapeRectangleCornerSettings& InCornerSettings);`
- L95 _public function_ `const FAvaShapeRectangleCornerSettings& GetTopLeft() const`
- L100 _public prototype_ `void SetTopRight(const FAvaShapeRectangleCornerSettings& InCornerSettings);`
- L101 _public function_ `const FAvaShapeRectangleCornerSettings& GetTopRight() const`
- L106 _public prototype_ `void SetBottomLeft(const FAvaShapeRectangleCornerSettings& InCornerSettings);`
- L107 _public function_ `const FAvaShapeRectangleCornerSettings& GetBottomLeft() const`
- L112 _public prototype_ `void SetBottomRight(const FAvaShapeRectangleCornerSettings& InCornerSettings);`
- L113 _public function_ `const FAvaShapeRectangleCornerSettings& GetBottomRight() const`
- L118 _public prototype_ `void SetTopLeftCornerType(EAvaShapeCornerType InType);`
- L119 _public function_ `EAvaShapeCornerType GetTopLeftCornerType() const`
- L124 _public prototype_ `void SetTopLeftBevelSize(float InSize);`
- L125 _public function_ `float GetTopLeftBevelSize() const`
- L131 _public prototype_ `void SetTopLeftBevelSubdivisions(uint8 InBevelSubdivisions);` — Bevel subdivisions for top left corner
- L132 _public function_ `uint8 GetTopLeftBevelSubdivisions() const`
- L137 _public prototype_ `void SetBottomLeftCornerType(EAvaShapeCornerType InType);`
- L138 _public function_ `EAvaShapeCornerType GetBottomLeftCornerType() const`
- L143 _public prototype_ `void SetBottomLeftBevelSize(float InSize);`
- L144 _public function_ `float GetBottomLeftBevelSize() const`
- L150 _public prototype_ `void SetBottomLeftBevelSubdivisions(uint8 InBevelSubdivisions);` — Bevel subdivisions for bottom left corner
- L151 _public function_ `uint8 GetBottomLeftBevelSubdivisions() const`
- L156 _public prototype_ `void SetTopRightCornerType(EAvaShapeCornerType InType);`
- L157 _public function_ `EAvaShapeCornerType GetTopRightCornerType() const`
- L162 _public prototype_ `void SetTopRightBevelSize(float InSize);`
- L163 _public function_ `float GetTopRightBevelSize() const`
- L169 _public prototype_ `void SetTopRightBevelSubdivisions(uint8 InBevelSubdivisions);` — Bevel subdivisions for top right corner
- L170 _public function_ `uint8 GetTopRightBevelSubdivisions() const`
- L175 _public prototype_ `void SetBottomRightCornerType(EAvaShapeCornerType InType);`
- L176 _public function_ `EAvaShapeCornerType GetBottomRightCornerType() const`
- L181 _public prototype_ `void SetBottomRightBevelSize(float InSize);`
- L182 _public function_ `float GetBottomRightBevelSize() const`
- L188 _public prototype_ `void SetBottomRightBevelSubdivisions(uint8 InBevelSubdivisions);` — Bevel subdivisions for bottom right corner
- L189 _public function_ `uint8 GetBottomRightBevelSubdivisions() const`
- L197 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L201 _protected prototype_ `float GetMaximumBevelSize() const;`
- L203 _protected prototype_ `bool IsSlantAngleValid() const;`
- L204 _protected prototype_ `FVector2D GetValidRangeLeftSlantAngle() const;`
- L205 _protected prototype_ `FVector2D GetValidRangeRightSlantAngle() const;`
- L206 _protected prototype_ `void GetValidSlantAngle(float& OutLeftSlant, float& OutRightSlant) const;`
- L208 _protected prototype_ `void OnAlignmentChanged();`
- L210 _protected prototype_ `void OnLeftSlantChanged();`
- L211 _protected prototype_ `void OnRightSlantChanged();`
- L213 _protected prototype_ `void OnGlobalBevelSizeChanged();`
- L214 _protected prototype_ `void OnGlobalBevelSubdivisionsChanged();`
- L216 _protected prototype_ `void OnTopLeftCornerTypeChanged();`
- L217 _protected prototype_ `void OnTopLeftBevelSizeChanged();`
- L218 _protected prototype_ `void OnTopLeftBevelSubdivisionsChanged();`
- L220 _protected prototype_ `void OnBottomLeftCornerTypeChanged();`
- L221 _protected prototype_ `void OnBottomLeftBevelSizeChanged();`
- L222 _protected prototype_ `void OnBottomLeftBevelSubdivisionsChanged();`
- L224 _protected prototype_ `void OnTopRightCornerTypeChanged();`
- L225 _protected prototype_ `void OnTopRightBevelSizeChanged();`
- L226 _protected prototype_ `void OnTopRightBevelSubdivisionsChanged();`
- L228 _protected prototype_ `void OnBottomRightCornerTypeChanged();`
- L229 _protected prototype_ `void OnBottomRightBevelSizeChanged();`
- L230 _protected prototype_ `void OnBottomRightBevelSubdivisionsChanged();`
- L232 _protected prototype_ `bool GenerateBaseMeshSections(FAvaShapeMesh& BaseMesh);`
- L234 _protected prototype_ `virtual bool CreateMesh(FAvaShapeMesh& InMesh) override;`
- L235 _protected prototype_ `virtual void OnSizeChanged() override;`
- L236 _protected prototype_ `virtual bool CanUpdateMeshInAnyThread() const override;`
- L239 _protected member_ `EAvaHorizontalAlignment HorizontalAlignment = EAvaHorizontalAlignment::Center;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Setter, Getter, Category="Shape", meta=(AllowPrivateAccess="true"))`
- L242 _protected member_ `EAvaVerticalAlignment VerticalAlignment = EAvaVerticalAlignment::Center;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Setter, Getter, Category="Shape", meta=(AllowPrivateAccess="true"))`
- L246 _protected member_ `float LeftSlant = 0.f;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Setter, Getter, Category="Shape", meta=(ClampMin="-45.0",ClampMax="45.0", AllowPrivateAccess="true"))` — Angle in degrees for the left slant of the rectangle
- L250 _protected member_ `float RightSlant = 0.f;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Setter, Getter, Category="Shape", meta=(ClampMin="-45.0",ClampMax="45.0", AllowPrivateAccess="true"))` — Angle in degrees for the right slant of the rectangle
- L253 _protected member_ `float GlobalBevelSize = 0.f;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Setter, Getter, Category="Shape", meta=(ClampMin="0.0", AllowPrivateAccess="true"))`
- L256 _protected member_ `uint8 GlobalBevelSubdivisions = DefaultSubdivisions;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Setter, Getter, Category="Shape", meta=(ClampMax="128.0", AllowPrivateAccess="true"))`
- L259 _protected member_ `FAvaShapeRectangleCornerSettings TopLeft;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Setter, Getter, Category="Shape", meta=(AllowPrivateAccess="true"))`
- L262 _protected member_ `FAvaShapeRectangleCornerSettings TopRight;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Setter, Getter, Category="Shape", meta=(AllowPrivateAccess="true"))`
- L265 _protected member_ `FAvaShapeRectangleCornerSettings BottomLeft;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Setter, Getter, Category="Shape", meta=(AllowPrivateAccess="true"))`
- L268 _protected member_ `FAvaShapeRectangleCornerSettings BottomRight;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Setter, Getter, Category="Shape", meta=(AllowPrivateAccess="true"))`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheShapes/Public/DynamicMeshes/AvaShapeRingDynMesh.h` (Public)


#### class `UAvaShapeRingDynamicMesh`  
`class UAvaShapeRingDynamicMesh : public UAvaShape2DDynMeshBase`  
_L9-93_
- reflection: `UCLASS(MinimalAPI, ClassGroup="Shape", BlueprintType, CustomConstructor, Within=AvaShapeActor)`
- inherits: `UAvaShape2DDynMeshBase`
- L16 _public member_ `static const FString MeshName;`
- L17 _public member_ `static inline constexpr uint8 MinNumSides = 3;`
- L18 _public member_ `static inline constexpr uint8 MaxNumSides = 128;`
- L20 _public function_ `UAvaShapeRingDynamicMesh() : UAvaShapeRingDynamicMesh(FVector2D(50.f, 50.f))`
- L24 _public function_ `UAvaShapeRingDynamicMesh(const FVector2D& Size2D, const FLinearColor& InVertexColor = FLinearColor::White, uint8 InNumSides = 64, float InInnerSize = 0.8f, float InAngleDegree = 360.f, float InStartDegree = 0.f) : UAvaShape2DDynMeshBase(Size2D, InVertexColor) , NumSides(InNumSides) , InnerSize(InInnerSize) , AngleDegree(InAngleDegree) , StartDegree (InStartDegree)`
- L35 _public function_ `virtual const FString& GetMeshName() const override`
- L40 _public prototype_ `void SetNumSides(uint8 InNumSides);`
- L41 _public function_ `uint8 GetNumSides() const`
- L46 _public prototype_ `void SetInnerSize(float InInnerSize);`
- L47 _public function_ `float GetInnerSize() const`
- L52 _public prototype_ `void SetAngleDegree(float InDegree);`
- L53 _public function_ `float GetAngleDegree() const`
- L58 _public prototype_ `void SetStartDegree(float InDegree);`
- L59 _public function_ `float GetStartDegree() const`
- L67 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L71 _protected prototype_ `virtual void OnNumSidesChanged();`
- L72 _protected prototype_ `virtual void OnInnerSizeChanged();`
- L73 _protected prototype_ `virtual void OnAngleDegreeChanged();`
- L74 _protected prototype_ `virtual void OnStartDegreeChanged();`
- L76 _protected prototype_ `virtual bool IsMeshVisible(int32 MeshIndex) override;`
- L77 _protected prototype_ `virtual bool CreateMesh(FAvaShapeMesh& InMesh) override;`
- L78 _protected prototype_ `virtual bool CanUpdateMeshInAnyThread() const override;`
- L81 _protected member_ `uint8 NumSides;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Setter, Getter, Category="Shape", meta=(ClampMin="3.0", ClampMax="128.0", DisplayName="Sides", AllowPrivateAccess="true"))`
- L84 _protected member_ `float InnerSize;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Setter, Getter, Category="Shape", meta=(ClampMin="0.0", ClampMax="1.0",DisplayName="Inner Size", AllowPrivateAccess="true"))`
- L88 _protected member_ `float AngleDegree;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Setter, Getter, Category="Shape", meta=(ClampMin="0.0", ClampMax="360.0", DisplayName="Angle degree", AllowPrivateAccess="true"))` — represents the angle in degree for the ring
- L92 _protected member_ `float StartDegree;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Setter, Getter, Category="Shape", meta=(ClampMin="0.0", ClampMax="360.0", DisplayName="Start Degree", AllowPrivateAccess="true"))` — represents the starting angle in degree for the ring

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheShapes/Public/DynamicMeshes/AvaShapeRoundedPolygonDynMesh.h` (Public)


#### struct `FAvaShapeRoundedCornerMetrics`  
`struct FAvaShapeRoundedCornerMetrics`  
_L9-19_
- L11 _public member_ `float Angle;`
- L12 _public member_ `FAvaShapeCachedVertex2D Start;`
- L13 _public member_ `FAvaShapeCachedVertex2D End;`
- L14 _public member_ `FAvaShapeCachedVertex2D VertexAnchor;`
- L15 _public member_ `bool bConvex;`
- L16 _public member_ `FVector2D CenterOfRotation;`
- L17 _public member_ `uint8 BevelSubdivisions;`
- L18 _public member_ `bool bValid = false;`

#### class `UAvaShapeRoundedPolygonDynamicMesh`  
`class UAvaShapeRoundedPolygonDynamicMesh : public UAvaShape2DDynMeshBase`  
_L22-85_
- reflection: `UCLASS(MinimalAPI, ClassGroup="Shape", Abstract, BlueprintType, CustomConstructor)`
- inherits: `UAvaShape2DDynMeshBase`
- L29 _public prototype_ `static FAvaShapeRoundedCornerMetrics CreateCornerInfo(const FVector2D& LineIn, const FVector2D LineOut, const FVector2D& CornerVertex, float Radius, uint8 BevelSubdivisions , bool bConvex);`
- L32 _public prototype_ `static void CreateRoundedCorner(UAvaShape2DDynMeshBase* InDynamicMesh, FAvaShapeMesh& InMesh, const FVector2D& CornerVertex, const FAvaShapeRoundedCornerMetrics& CornerInfo, bool bAddConcaveCornerInsert = true);`
- L36 _public function_ `UAvaShapeRoundedPolygonDynamicMesh() : UAvaShapeRoundedPolygonDynamicMesh(FVector2D(50.f, 50.f))`
- L40 _public function_ `UAvaShapeRoundedPolygonDynamicMesh(const FVector2D& Size2D, const FLinearColor& InVertexColor = FLinearColor::White, float InBevelSize = 0.f, uint8 InBevelSubdivisions = 0) : UAvaShape2DDynMeshBase(Size2D, InVertexColor) , BevelSize(InBevelSize) , BevelSubdivisions(InBevelSubdivisions)`
- L47 _public prototype_ `void SetBevelSize(float InBevelSize);`
- L48 _public function_ `float GetBevelSize() const`
- L53 _public prototype_ `void SetBevelSubdivisions(uint8 InBevelSubdivisions);`
- L54 _public function_ `uint8 GetBevelSubdivisions() const`
- L62 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L66 _protected prototype_ `virtual void OnSizeChanged() override;`
- L68 _protected prototype_ `virtual void OnRoundedRadiusChanged();`
- L69 _protected prototype_ `virtual void OnBevelSubdivisionsChanged();`
- L75 _protected function_ `virtual void GenerateBorderVertices(TArray<FVector2D>& BorderVertices)` — Must be generated by a inheriting class. Cannot have complex shapes. Vertices cannot block each other's path to the center. Example: Triangle, rectangle, pentagram. Vertices must go in a clockwise direction. Inheritors should also adds local snap points
- L77 _protected function_ `virtual bool UseCenteredVertex()`
- L78 _protected prototype_ `virtual bool CreateMesh(FAvaShapeMesh& InMesh) override;`
- L81 _protected member_ `float BevelSize = 0.f;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Setter, Getter, Category="Shape", meta=(ClampMin="0.0", AllowPrivateAccess="true"))`
- L84 _protected member_ `uint8 BevelSubdivisions = UAvaShapeDynamicMeshBase::DefaultSubdivisions;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Setter, Getter, Category="Shape", meta=(ClampMax="64.0", AllowPrivateAccess="true"))`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheShapes/Public/DynamicMeshes/AvaShapeSphereDynMesh.h` (Public)


#### class `UAvaShapeSphereDynamicMesh`  
`class UAvaShapeSphereDynamicMesh : public UAvaShape3DDynMeshBase`  
_L9-146_
- reflection: `UCLASS(MinimalAPI, ClassGroup="Shape", BlueprintType, CustomConstructor, Within=AvaShapeActor)`
- inherits: `UAvaShape3DDynMeshBase`
- L16 _public member_ `static const FString MeshName;`
- L17 _public member_ `static constexpr uint8 MinNumSides = 4;`
- L18 _public member_ `static constexpr uint8 MaxNumSides = 128;`
- L20 _public member_ `static constexpr int32 MESH_INDEX_TOP = 1;`
- L21 _public member_ `static constexpr int32 MESH_INDEX_BOTTOM = 2;`
- L22 _public member_ `static constexpr int32 MESH_INDEX_START = 3;`
- L23 _public member_ `static constexpr int32 MESH_INDEX_END = 4;`
- L25 _public function_ `UAvaShapeSphereDynamicMesh() : UAvaShapeSphereDynamicMesh(FVector(50.f, 50.f, 50.f))`
- L29 _public function_ `UAvaShapeSphereDynamicMesh( const FVector& InSize, const FLinearColor& InVertexColor = FLinearColor::White, float InStartLongitude = 0.f, float InEndLongitude = 180.f, float InStartLatitude = 0.f, float InLatitudeDegree = 360.f, uint8 InNumSides = 32, float InRadius = 1.f) : UAvaShape3DDynMeshBase(InSize, InVertexColor) , StartLongitude(InStartLongitude) , PreEditStartLongitude(0) , EndLongitude(InEndLongitude) , PreEditEndLongitude(0) , StartLatitude(InStartLatitude) , LatitudeDegree(InLatitudeDegree) , NumSides(InNumSides) , Radius(InRadius)`
- L49 _public function_ `virtual const FString& GetMeshName() const override`
- L54 _public prototype_ `void SetNumSides(uint8 InNumSides);`
- L55 _public function_ `uint8 GetNumSides() const`
- L60 _public prototype_ `void SetStartLatitude(float InDegree);`
- L61 _public function_ `float GetStartLatitude() const`
- L66 _public prototype_ `void SetLatitudeDegree(float InDegree);`
- L67 _public function_ `float GetLatitudeDegree() const`
- L72 _public prototype_ `void SetStartLongitude(float InDegree);`
- L73 _public function_ `float GetStartLongitude() const`
- L78 _public prototype_ `void SetEndLongitude(float InDegree);`
- L79 _public function_ `float GetEndLongitude() const`
- L87 _protected prototype_ `virtual void PreEditChange(FProperty* PropertyAboutToChange) override;`
- L88 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L92 _protected prototype_ `virtual void OnNumSidesChanged();`
- L93 _protected prototype_ `virtual void OnRadiusChanged();`
- L94 _protected prototype_ `virtual void OnStartLatitudeChanged();`
- L95 _protected prototype_ `virtual void OnLatitudeDegreeChanged();`
- L96 _protected prototype_ `virtual void OnStartLongitudeChanged();`
- L97 _protected prototype_ `virtual void OnEndLongitudeChanged();`
- L99 _protected prototype_ `virtual bool CreateBaseUVs(FAvaShapeMesh& BaseMesh, FAvaShapeMaterialUVParameters& InUseParams);`
- L100 _protected prototype_ `virtual bool GenerateBaseMeshSections(FAvaShapeMesh& BaseMesh);`
- L102 _protected prototype_ `virtual bool CreateTopUVs(FAvaShapeMesh& TopMesh, FAvaShapeMaterialUVParameters& InUseParams);`
- L103 _protected prototype_ `virtual bool GenerateTopMeshSections(FAvaShapeMesh& TopMesh);`
- L105 _protected prototype_ `virtual bool CreateBottomUVs(FAvaShapeMesh& BottomMesh, FAvaShapeMaterialUVParameters& InUseParams);`
- L106 _protected prototype_ `virtual bool GenerateBottomMeshSections(FAvaShapeMesh& BottomMesh);`
- L108 _protected prototype_ `virtual bool CreateStartUVs(FAvaShapeMesh& StartMesh, FAvaShapeMaterialUVParameters& InUseParams);`
- L109 _protected prototype_ `virtual bool GenerateStartMeshSections(FAvaShapeMesh& StartMesh);`
- L111 _protected prototype_ `virtual bool CreateEndUVs(FAvaShapeMesh& EndMesh, FAvaShapeMaterialUVParameters& InUseParams);`
- L112 _protected prototype_ `virtual bool GenerateEndMeshSections(FAvaShapeMesh& EndMesh);`
- L114 _protected prototype_ `virtual void RegisterMeshes() override;`
- L115 _protected prototype_ `virtual bool IsMeshVisible(int32 MeshIndex) override;`
- L116 _protected prototype_ `virtual bool CreateMesh(FAvaShapeMesh& InMesh) override;`
- L117 _protected prototype_ `virtual bool CreateUVs(FAvaShapeMesh& InMesh, FAvaShapeMaterialUVParameters& InParams) override;`
- L118 _protected prototype_ `virtual bool CanUpdateMeshInAnyThread() const override;`
- L122 _protected member_ `float StartLongitude;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Setter, Getter, Category="Shape", meta=(ClampMin="0.0", ClampMax="180.0", DisplayName="Start Longitude degree", AllowPrivateAccess="true"))` — represents the longitude (Z) angle in degree for the sphere at the start
- L123 _protected member_ `float PreEditStartLongitude;`
- L127 _protected member_ `float EndLongitude;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Setter, Getter, Category="Shape", meta=(ClampMin="0.0", ClampMax="180.0", DisplayName="End Longitude degree", AllowPrivateAccess="true"))` — represents the longitude (Z) angle in degree for the sphere at the end
- L128 _protected member_ `float PreEditEndLongitude;`
- L132 _protected member_ `float StartLatitude;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Setter, Getter, Category="Shape", meta=(ClampMin="0.0", ClampMax="360.0", DisplayName="Start Latitude degree", AllowPrivateAccess="true"))` — represents the latitude (Y) angle in degree for the sphere at the start
- L136 _protected member_ `float LatitudeDegree;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Setter, Getter, Category="Shape", meta=(ClampMin="0.0", ClampMax="360.0", DisplayName="Latitude degree", AllowPrivateAccess="true"))` — represents the total latitude (Y) angle in degree for the sphere
- L140 _protected member_ `uint8 NumSides;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Setter, Getter, Category="Shape", meta=(ClampMin="4.0", ClampMax="128.0", DisplayName="Sides", AllowPrivateAccess="true"))` — represents the precision of the sphere mesh
- L145 _private member_ `float Radius;` — `UPROPERTY()` — represents the radius ratio of the sphere

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheShapes/Public/DynamicMeshes/AvaShapeStarDynMesh.h` (Public)


#### class `UAvaShapeStarDynamicMesh`  
`class UAvaShapeStarDynamicMesh : public UAvaShapeRoundedPolygonDynamicMesh`  
_L9-69_
- reflection: `UCLASS(MinimalAPI, ClassGroup="Shape", BlueprintType, CustomConstructor, Within=AvaShapeActor)`
- inherits: `UAvaShapeRoundedPolygonDynamicMesh`
- L16 _public member_ `static const FString MeshName;`
- L17 _public member_ `static inline constexpr uint8 MinNumPoints = 2;`
- L18 _public member_ `static inline constexpr uint8 MaxNumPoints = 128;`
- L20 _public function_ `UAvaShapeStarDynamicMesh() : UAvaShapeStarDynamicMesh(FVector2D(50.f, 50.f))`
- L24 _public function_ `UAvaShapeStarDynamicMesh(const FVector2D& Size2D, const FLinearColor& InVertexColor = FLinearColor::White, float InBevelSize = 0.f, uint8 InBevelSubdivisions = 0, uint8 InNumPoints = 5, float InInnerSize = 0.5f) : UAvaShapeRoundedPolygonDynamicMesh(Size2D, InVertexColor, InBevelSize, InBevelSubdivisions) , NumPoints(InNumPoints) , InnerSize(InInnerSize)`
- L31 _public function_ `virtual const FString& GetMeshName() const override`
- L36 _public prototype_ `void SetNumPoints(uint8 InNumPoints);`
- L37 _public function_ `uint8 GetNumPoints() const`
- L42 _public prototype_ `void SetInnerSize(float InInnerSize);`
- L43 _public function_ `float GetInnerSize() const`
- L51 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L55 _protected prototype_ `virtual void OnNumSidesChanged();`
- L56 _protected prototype_ `virtual void OnInnerSizeChanged();`
- L58 _protected prototype_ `virtual void GenerateBorderVertices(TArray<FVector2D>& BorderVertices) override;`
- L60 _protected function_ `virtual bool UseCenteredVertex() override`
- L61 _protected prototype_ `virtual bool IsMeshVisible(int32 MeshIndex) override;`
- L62 _protected prototype_ `virtual bool CanUpdateMeshInAnyThread() const override;`
- L65 _protected member_ `uint8 NumPoints = 0;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Setter, Getter, Category="Shape", meta=(ClampMin="2.0", ClampMax="128.0", DisplayName="Points", AllowPrivateAccess="true"))`
- L68 _protected member_ `float InnerSize = 0.f;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Setter, Getter, Category="Shape", meta=(ClampMin="0.0", ClampMax="0.99", DisplayName="Inner Size Fraction", AllowPrivateAccess="true"))`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheShapes/Public/DynamicMeshes/AvaShapeTorusDynMesh.h` (Public)


#### class `UAvaShapeTorusDynamicMesh`  
`class UAvaShapeTorusDynamicMesh : public UAvaShape3DDynMeshBase`  
_L9-127_
- reflection: `UCLASS(MinimalAPI, ClassGroup="Shape", BlueprintType, CustomConstructor, Within=AvaShapeActor)`
- inherits: `UAvaShape3DDynMeshBase`
- L16 _public member_ `static const FString MeshName;`
- L17 _public member_ `static constexpr uint8 MinNumSlices = 3;`
- L18 _public member_ `static constexpr uint8 MaxNumSlices = 128;`
- L19 _public member_ `static constexpr uint8 MinNumSides = 4;`
- L20 _public member_ `static constexpr uint8 MaxNumSides = 128;`
- L22 _public member_ `static constexpr int32 MESH_INDEX_START = 1;`
- L23 _public member_ `static constexpr int32 MESH_INDEX_END = 2;`
- L25 _public function_ `UAvaShapeTorusDynamicMesh() : UAvaShapeTorusDynamicMesh(FVector(50.f, 50.f, 50.f))`
- L29 _public function_ `UAvaShapeTorusDynamicMesh( const FVector& InSize, const FLinearColor& InVertexColor = FLinearColor::White, uint8 InNumSlices = 32, uint8 InNumSides = 32, float InInnerSize = 0.75, float InAngleDegree = 360.f, float InStartDegree = 0.f) : UAvaShape3DDynMeshBase(InSize, InVertexColor) , NumSlices(InNumSlices) , NumSides(InNumSides) , InnerSize(InInnerSize) , AngleDegree(InAngleDegree) , StartDegree(InStartDegree)`
- L45 _public function_ `virtual const FString& GetMeshName() const override`
- L50 _public prototype_ `void SetNumSides(uint8 InNumSides);`
- L51 _public function_ `uint8 GetNumSides() const`
- L56 _public prototype_ `void SetNumSlices(uint8 InNumSlices);`
- L57 _public function_ `uint8 GetNumSlices() const`
- L62 _public prototype_ `void SetInnerSize(float InInnerSize);`
- L63 _public function_ `float GetInnerSize() const`
- L68 _public prototype_ `void SetAngleDegree(float InAngleDegree);`
- L69 _public function_ `float GetAngleDegree() const`
- L74 _public prototype_ `void SetStartDegree(float InStartDegree);`
- L75 _public function_ `float GetStartDegree() const`
- L83 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L87 _protected prototype_ `virtual bool CreateBaseUVs(FAvaShapeMesh& BaseMesh, FAvaShapeMaterialUVParameters& InUseParams);`
- L88 _protected prototype_ `virtual bool GenerateBaseMeshSections(FAvaShapeMesh& BaseMesh);`
- L90 _protected prototype_ `virtual bool CreateStartUVs(FAvaShapeMesh& StartMesh, FAvaShapeMaterialUVParameters& InUseParams);`
- L91 _protected prototype_ `virtual bool GenerateStartMeshSections(FAvaShapeMesh& StartMesh);`
- L93 _protected prototype_ `virtual bool CreateEndUVs(FAvaShapeMesh& EndMesh, FAvaShapeMaterialUVParameters& InUseParams);`
- L94 _protected prototype_ `virtual bool GenerateEndMeshSections(FAvaShapeMesh& EndMesh);`
- L96 _protected prototype_ `virtual void OnNumSidesChanged();`
- L97 _protected prototype_ `virtual void OnNumSlicesChanged();`
- L98 _protected prototype_ `virtual void OnInnerSizeChanged();`
- L99 _protected prototype_ `virtual void OnAngleDegreeChanged();`
- L100 _protected prototype_ `virtual void OnStartDegreeChanged();`
- L102 _protected prototype_ `virtual void RegisterMeshes() override;`
- L103 _protected prototype_ `virtual bool IsMeshVisible(int32 MeshIndex) override;`
- L104 _protected prototype_ `virtual bool CreateMesh(FAvaShapeMesh& InMesh) override;`
- L105 _protected prototype_ `virtual bool CreateUVs(FAvaShapeMesh& InMesh, FAvaShapeMaterialUVParameters& InParams) override;`
- L106 _protected prototype_ `virtual bool CanUpdateMeshInAnyThread() const override;`
- L110 _protected member_ `uint8 NumSlices;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Setter, Getter, Category="Shape", meta=(ClampMin="3.0", ClampMax="128.0", DisplayName="Slices", AllowPrivateAccess="true"))` — represents the number of slices composing the tube
- L114 _protected member_ `uint8 NumSides;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Setter, Getter, Category="Shape", meta=(ClampMin="4.0", ClampMax="128.0", DisplayName="Sides", AllowPrivateAccess="true"))` — represents the precision of each circle composing a slice
- L118 _protected member_ `float InnerSize;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Setter, Getter, Category="Shape", meta=(ClampMin="0.5", ClampMax="0.99", DisplayName="Inner Size", AllowPrivateAccess="true"))` — represents the size ratio available inside the torus
- L122 _protected member_ `float AngleDegree;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Setter, Getter, Category="Shape", meta=(ClampMin="0.0", ClampMax="360.0", DisplayName="Angle degree", AllowPrivateAccess="true"))` — represents the tube angle in degree for the torus
- L126 _protected member_ `float StartDegree;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Setter, Getter, Category="Shape", meta=(ClampMin="0.0", ClampMax="360.0", DisplayName="Start Degree", AllowPrivateAccess="true"))` — represents the starting angle in degree for the torus

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheShapes/Public/Sequencer/MovieScene/MovieSceneAvaShapeRectCornerSection.h` (Public)


#### class `UMovieSceneAvaShapeRectCornerSection`  
`class UMovieSceneAvaShapeRectCornerSection : public UMovieSceneSection`  
_L12-27_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneSection`
- L17 _public prototype_ `UMovieSceneAvaShapeRectCornerSection(const FObjectInitializer& ObjectInitializer);`
- L20 _public member_ `FMovieSceneByteChannel Type;` — `UPROPERTY()`
- L23 _public member_ `FMovieSceneFloatChannel BevelSize;` — `UPROPERTY()`
- L26 _public member_ `FMovieSceneByteChannel BevelSubdivisions;` — `UPROPERTY()`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheShapes/Public/Sequencer/MovieScene/MovieSceneAvaShapeRectCornerTrack.h` (Public)


#### class `UMovieSceneAvaShapeRectCornerTrack`  
`class UMovieSceneAvaShapeRectCornerTrack : public UMovieScenePropertyTrack , public IMovieSceneTrackTemplateProducer`  
_L13-27_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieScenePropertyTrack,IMovieSceneTrackTemplateProducer`
- desc: Track for animating FAvaShapeRectangleCornerSettings properties
- L20 _public prototype_ `UMovieSceneAvaShapeRectCornerTrack(const FObjectInitializer& ObjectInitializer);`
- L23 _public prototype_ `virtual bool SupportsType(TSubclassOf<UMovieSceneSection> SectionClass) const override;` — UMovieSceneTrack Interface
- L24 _public prototype_ `virtual UMovieSceneSection* CreateNewSection() override;`
- L25 _public prototype_ `virtual FMovieSceneEvalTemplatePtr CreateTemplateForSection(const UMovieSceneSection& InSection) const override;`
