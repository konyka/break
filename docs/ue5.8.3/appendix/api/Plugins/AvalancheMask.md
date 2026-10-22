# Plugins / AvalancheMask

- module root: `Plugins/VirtualProduction/Avalanche/Source/AvalancheMask`
- headers: 29; symbols: 643
- symbol kinds: class=31, delegate=1, enum=1, enumerator=2, function=65, macro=3, member=128, namespace=15, prototype=366, struct=16, typedef=8, variable=7
- PrivateDependencyModuleNames: ActorModifier, ActorModifierCore, AssetRegistry, AssetTools, Avalanche, AvalancheCore, AvalancheText, DeveloperSettings, DynamicMaterial, DynamicMaterialEditor, Engine, GeometryFramework, MediaPlate, Projects, Slate, SlateCore, Text3D, UnrealEd
- PublicDependencyModuleNames: AvalancheMaterial, AvalancheModifiers, AvalancheShapes, Core, CoreUObject, GeometryMask

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMask/Internal/Materials/AvaMaskMaterialInstanceSubsystem.h` (Internal)


#### struct `FAvaMaskMaterialInstanceKey`  
`struct FAvaMaskMaterialInstanceKey`  
_L23-39_
- reflection: `USTRUCT()`
- desc: A material instance is identified by a combination of it's parent and requested parameter values
- L28 _public member_ `TSoftObjectPtr<UMaterialInterface> ParentMaterial;` — `UPROPERTY()`
- L31 _public member_ `uint32 PermutationKey = 0;` — `UPROPERTY()`

#### struct `FAvaMaskMaterialPermutations`  
`struct FAvaMaskMaterialPermutations`  
_L42-51_
- reflection: `USTRUCT()`
- L47 _public member_ `TSoftObjectPtr<UMaterialInterface> ParentMaterial;` — `UPROPERTY()`
- L50 _public member_ `TMap<uint32, TWeakObjectPtr<UMaterialInstanceDynamic>> Instances;` — `UPROPERTY()`

#### class `UAvaMaskMaterialInstanceProvider`  
`class UAvaMaskMaterialInstanceProvider : public UObject`  
_L54-77_
- reflection: `UCLASS(DisplayName = "Motion Design Mask MaterialInstance Provider")`
- inherits: `UObject`
- L61 _public prototype_ `UMaterialInstanceDynamic* FindOrAddMID(UMaterialInterface* InParentMaterial, const uint32& InInstanceKey, const EBlendMode InBlendMode = EBlendMode::BLEND_Masked);` — Instance Key will usually be the product of the Component and Slot.
- L63 _public prototype_ `void SetParent(UAvaMaskMaterialInstanceProvider* InParentProvider);`
- L64 _public prototype_ `void SetFactories(const TMap<TSubclassOf<UMaterialInterface>, TObjectPtr<UAvaMaskMaterialFactoryBase>>& InFactories);`
- L70 _private member_ `TWeakObjectPtr<UAvaMaskMaterialInstanceProvider> ParentProvider;` — `UPROPERTY(Transient)`
- L73 _private member_ `TMap<TSubclassOf<UMaterialInterface>, TObjectPtr<UAvaMaskMaterialFactoryBase>> MaterialInstanceFactories;` — `UPROPERTY()`
- L76 _private member_ `TMap<TSoftObjectPtr<UMaterialInterface>, FAvaMaskMaterialPermutations> MaterialInstanceCache;` — `UPROPERTY()`

#### class `UAvaMaskMaterialInstanceWorldSubsystem`  
`class UAvaMaskMaterialInstanceWorldSubsystem : public UWorldSubsystem`  
_L81-99_
- reflection: `UCLASS(DisplayName = "Motion Design Mask MaterialInstance World Subsystem")`
- inherits: `UWorldSubsystem`
- desc: Stores duplicates of the MID's provided by the engine subsystem, allowing level actors to reference them.
- L88 _public prototype_ `virtual void Initialize(FSubsystemCollectionBase& Collection) override;`
- L91 _public prototype_ `UAvaMaskMaterialInstanceProvider* GetMaterialInstanceProvider() const;`
- L95 _private member_ `TObjectPtr<UAvaMaskMaterialInstanceProvider> MaterialInstanceProvider;` — `UPROPERTY()`
- L98 _private member_ `TObjectPtr<UAvaMaskMaterialInstanceSubsystem> MaterialInstanceEngineSubsystem;` — `UPROPERTY()`

#### class `UAvaMaskMaterialInstanceSubsystem`  
`class UAvaMaskMaterialInstanceSubsystem : public UEngineSubsystem`  
_L103-124_
- reflection: `UCLASS(DisplayName = "Motion Design Mask MaterialInstance Engine Subsystem")`
- inherits: `UEngineSubsystem`
- desc: Responsible for providing MID's for a given Material.
- L110 _public prototype_ `virtual void Initialize(FSubsystemCollectionBase& Collection) override;`
- L113 _public prototype_ `UAvaMaskMaterialInstanceProvider* GetMaterialInstanceProvider() const;`
- L116 _public prototype_ `void ClearCached();` — Call to forcibly clear cached MID's.
- L119 _private prototype_ `void FindMaterialFactories();`
- L123 _private member_ `TObjectPtr<UAvaMaskMaterialInstanceProvider> MaterialInstanceProvider;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L33 _function_ `friend uint32 GetTypeHash(const FAvaMaskMaterialInstanceKey& Value)`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMask/Private/AvaMaskLog.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogAvaMask, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogAvaMask, Log, All);`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMask/Private/AvaMaskSettings.h` (Private)


#### class `UAvaMaskSettings`  
`class UAvaMaskSettings : public UDeveloperSettings`  
_L18-38_
- reflection: `UCLASS(Config = Engine, meta = (DisplayName = "Mask"))`
- inherits: `UDeveloperSettings`
- desc: Settings for Motion Design Mask
- L24 _public prototype_ `UAvaMaskSettings();`
- L28 _public prototype_ `UMaterialFunctionInterface* GetMaterialFunction() const;` — Get the user specified or default material function.
- L33 _private member_ `TSoftObjectPtr<UMaterialFunctionInterface> MaterialFunction;` — `UPROPERTY(Config, EditAnywhere, NoClear, Category = "Material", meta=(ConfigRestartRequired=true))` — Material Function to use to expect or add to a material.
- L36 _private member_ `mutable TObjectPtr<UMaterialFunctionInterface> ResolvedMaterialFunction;` — `UPROPERTY(Transient)`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMask/Private/AvaMaskSubsystem.h` (Private)


#### class `UAvaMaskSubsystem`  
`class UAvaMaskSubsystem : public UEngineSubsystem`  
_L11-45_
- reflection: `UCLASS()`
- inherits: `UEngineSubsystem`
- L17 _public prototype_ `static UMaterialInterface* StaticGetDefaultMaskMaterial();` — Gets the material to use for masking when there's no material set
- L20 _public prototype_ `UMaterialInterface* GetDefaultMaskMaterial() const;` — Gets the material to use for masking when there's no material set
- L24 _public prototype_ `void SetLastSpecifiedChannelName(const FName InName);` — Stores the last specified (user or auto) channel name to use for subsequently added modifiers in Target mode.
- L28 _public prototype_ `virtual void Initialize(FSubsystemCollectionBase& InCollection) override;`
- L34 _private member_ `TSoftObjectPtr<UMaterialInterface> DefaultMaskMaterialSoft;` — `UPROPERTY()` — Soft object ptr to the default mask material to use when there's no material set
- L38 _private member_ `mutable TObjectPtr<UMaterialInterface> DefaultMaskMaterial;` — `UPROPERTY()` — Default mask material to use when there's no material set
- L43 _private member_ `FName LastSpecifiedChannelName;` — `UPROPERTY(Transient, Getter = "Auto", Setter)` — Stores the last specified (user or auto) channel name to use for subsequently added modifiers in Target mode.

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMask/Private/AvaMaskUtilities.h` (Private)


#### Free symbols / members of external scopes

- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace AvaMask` (scope `UE`)
- L16 _namespace_ `namespace Internal` (scope `UE::AvaMask`)
- L19 _variable_ `static FMaterialParameterInfo MaskTexturesParameterInfo = { TEXT("Mask_` (scope `UE::AvaMask::Internal`) — Note that this assumes the parameters have the same name for all materials, which they should if using the provided material function.
- L20 _variable_ `static FMaterialParameterInfo MaskIndicesParameterInfo = { TEXT("Mask_` (scope `UE::AvaMask::Internal`)
- L21 _variable_ `static FMaterialParameterInfo BaseOpacityParameterInfo = { TEXT("Mask_` (scope `UE::AvaMask::Internal`)
- L22 _variable_ `static FMaterialParameterInfo InvertParameterInfo = { TEXT("Mask_` (scope `UE::AvaMask::Internal`)
- L23 _variable_ `static FMaterialParameterInfo PaddingParameterInfo = { TEXT("Mask_` (scope `UE::AvaMask::Internal`)
- L24 _variable_ `static FMaterialParameterInfo FeatherParameterInfo = { TEXT("Mask_` (scope `UE::AvaMask::Internal`)
- L26 _variable_ `static FName HandleTag = TEXT("Mod` (scope `UE::AvaMask::Internal`)
- L29 _prototype_ `FSoftComponentReference MakeComponentReference(const AActor* InOwner, const UActorComponent* InComponent);` (scope `UE::AvaMask::Internal`) — Utility function, will set "OtherActor" if the components owner differs from the provided one.
- L32 _prototype_ `uint32 MakeMaterialInstanceKey(const UMaterialInterface* InMaterial, const FName InMaskChannelName, EBlendMode InBlendMode, const int32 InSeed = 128);` (scope `UE::AvaMask::Internal`) — Creates a unique (deterministic) key based on the provided parameters.
- L34 _prototype_ `UActorComponent* FindOrAddComponent(const TSubclassOf<UActorComponent>& InComponentClass, AActor* InActor);` (scope `UE::AvaMask::Internal`)
- L39 _function_ `InComponentClass* FindOrAddComponent(AActor* InActor)` (scope `UE::AvaMask::Internal`)
- L44 _prototype_ `void RemoveComponentByInterface(const TSubclassOf<UInterface>& InInterfaceType, const AActor* InActor);` (scope `UE::AvaMask::Internal`)
- L46 _prototype_ `FString GetGeneratedMaterialPath();` (scope `UE::AvaMask::Internal`)
- L48 _prototype_ `FString GetBlendModeString(const EBlendMode InBlendMode);` (scope `UE::AvaMask::Internal`)
- L51 _prototype_ `EBlendMode GetTargetBlendMode(const EBlendMode InFromMaterial, const EBlendMode InRequired);` (scope `UE::AvaMask::Internal`) — Returns whichever blend mode satisfies the requirement AND user specified blend mode
- L53 _prototype_ `UMaterialInterface* GetNonTransientParentMaterial(const UMaterialInstance* InMaterialInstance);` (scope `UE::AvaMask::Internal`)
- L57 _prototype_ `void SetOutputProcessor(TNotNull<UMaterialInterface*> InMaterial, UMaterialFunctionInterface* InOutputProcessor, EBlendMode InBlendMode);` (scope `UE::AvaMask::Internal`) — Sets the output processor for Material Designer  materials
- L60 _prototype_ `UMaterialFunctionInterface* GetOutputProcessor(TNotNull<UMaterialInterface*> InMaterial, EBlendMode InBlendMode);` (scope `UE::AvaMask::Internal`) — Gets the output process from Material Designer materials

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMask/Private/Handling/AvaDesignedMaterialHandle.h` (Private)


#### class `FAvaDesignedMaterialHandle`  
`class FAvaDesignedMaterialHandle: public FAvaMaterialInstanceHandle`  
_L11-30_
- inherits: `FAvaMaterialInstanceHandle`
- L14 _public prototype_ `UE_AVA_INHERITS_WITH_SUPER(FAvaDesignedMaterialHandle, FAvaMaterialInstanceHandle);`
- L16 _public prototype_ `explicit FAvaDesignedMaterialHandle(const TWeakObjectPtr<UDynamicMaterialInstance>& InWeakDesignedMaterial);`
- L19 _public prototype_ `virtual void CopyParametersFrom(UMaterialInstance* InSourceMaterial) override;`
- L23 _public prototype_ `virtual bool IsValid() const override;`
- L26 _public prototype_ `static bool IsSupported(const FAvaMaskMaterialReference& InInstance, FName InTag = NAME_None);`
- L29 _protected member_ `TWeakObjectPtr<UDynamicMaterialInstance> WeakDesignedMaterial;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMask/Private/Handling/AvaHandleUtilities.h` (Private)


#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Ava` (scope `UE`)
- L13 _namespace_ `namespace Internal` (scope `UE::Ava`)
- L15 _prototype_ `UAvaObjectHandleSubsystem* GetObjectHandleSubsystem();` (scope `UE::Ava::Internal`)
- L17 _prototype_ `bool IsDefaultMaterial(UMaterialInterface* InMaterial);` (scope `UE::Ava::Internal`)
- L21 _function_ `bool IsHandleValid(const TSharedPtr<HandleType>& InHandle)` (scope `UE::Ava::Internal`)
- L28 _function_ `bool IsHandleValid(const TSharedPtr<HandleType>* InHandle)` (scope `UE::Ava::Internal`)
- L35 _function_ `TSharedPtr<HandleType>& FindOrAddHandleByLambda(TMap<KeyType, TSharedPtr<HandleType>, AllocatorType, KeyFuncs>& Map, InitKeyType&& Key, LambdaType Lambda)` (scope `UE::Ava::Internal`)
- L53 _function_ `FStructView FindOrAddMaterialHandleData( ParentHandleDataType* InParentHandleData , const TSharedPtr<IAvaMaskMaterialHandle>& InMaterialHandle , const int32 InSlotIdx)` (scope `UE::Ava::Internal`)
- L77 _function_ `int32 GetComponents(const AActor* InActor, TSet<ComponentType*>& OutComponents, const bool bInIncludeInstanceComponents = true)` (scope `UE::Ava::Internal`)

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMask/Private/Handling/AvaMaskActorMaterialCollectionHandle.h` (Private)


#### struct `FAvaMaskActorMaterialCollectionHandleData`  
`struct FAvaMaskActorMaterialCollectionHandleData`  
_L26-32_
- reflection: `USTRUCT()`
- L31 _public member_ `TMap<FAvaMask2DComponentMaterialPath, FInstancedStruct> ComponentMaterialData;` — `UPROPERTY()`

#### class `FAvaMaskActorMaterialCollectionHandle`  
`class FAvaMaskActorMaterialCollectionHandle : public TAvaMaskMaterialCollectionHandle<FAvaMaskActorMaterialCollectionHandleData> , public TSharedFromThis<FAvaMaskActorMaterialCollectionHandle>`  
_L34-121_
- inherits: `TAvaMaskMaterialCollectionHandle<FAvaMaskActorMaterialCollectionHandleData>,TSharedFromThis<FAvaMaskActorMaterialCollectionHandle>`
- L39 _public prototype_ `UE_AVA_INHERITS_WITH_SUPER(FAvaMaskActorMaterialCollectionHandle, TAvaMaskMaterialCollectionHandle<FAvaMaskActorMaterialCollectionHandleData>);`
- L41 _public prototype_ `explicit FAvaMaskActorMaterialCollectionHandle(AActor* InActor);`
- L42 _public prototype_ `virtual ~FAvaMaskActorMaterialCollectionHandle() override = default;`
- L45 _public prototype_ `virtual TArray<TObjectPtr<UMaterialInterface>> GetMaterials() override;`
- L46 _public prototype_ `virtual TArray<TSharedPtr<IAvaMaskMaterialHandle>> GetMaterialHandles() override;`
- L47 _public prototype_ `virtual int32 GetNumMaterials() const override;`
- L49 _public prototype_ `virtual void SetMaterial(const FSoftComponentReference& InComponent, const int32 InSlotIdx, UMaterialInterface* InMaterial) override;`
- L50 _public prototype_ `virtual void SetMaterials(const TArray<TObjectPtr<UMaterialInterface>>& InMaterials, const TBitArray<>& InSetToggle) override;`
- L52 _public prototype_ `virtual void ForEachMaterial( TFunctionRef<bool( const FSoftComponentReference& InComponent , const int32 InIdx , UMaterialInterface* InMaterial)> InFunction) override;`
- L58 _public prototype_ `virtual void ForEachMaterialHandle( TFunctionRef<bool( const FSoftComponentReference& InComponent , const int32 InIdx , const bool bInIsSlotOccupied , const TSharedPtr<IAvaMaskMaterialHandle>& InMaterialHandle)> InFunction) override;`
- L65 _public prototype_ `virtual void MapEachMaterial( TFunctionRef<UMaterialInterface*( const FSoftComponentReference& InComponent , const int32 InIdx , UMaterialInterface* InMaterial)> InFunction) override;`
- L71 _public prototype_ `virtual void MapEachMaterialHandle( TFunctionRef<TSharedPtr<IAvaMaskMaterialHandle>( const FSoftComponentReference& InComponent , const int32 InIdx , const bool bInIsSlotOccupied , const TSharedPtr<IAvaMaskMaterialHandle>& InMaterialHandle)> InFunction) override;`
- L78 _public prototype_ `virtual bool SaveOriginalState(const FStructView& InHandleData) override;`
- L79 _public prototype_ `virtual bool ApplyOriginalState(const FStructView& InHandleData) override;`
- L81 _public prototype_ `virtual bool IsValid() const override;`
- L84 _public prototype_ `static bool IsSupported(const FAvaMaskMaterialReference& InInstance, FName InTag = NAME_None);`
- L88 _protected prototype_ `virtual FStructView GetMaterialHandleData( FHandleData* InParentHandleData , const FSoftComponentReference& InComponent , const int32 InSlotIdx) override;`
- L93 _protected prototype_ `virtual ::FStructView GetOrAddMaterialHandleData( FHandleData* InParentHandleData , const TSharedPtr<IAvaMaskMaterialHandle>& InMaterialHandle , const FSoftComponentReference& InComponent , const int32 InSlotIdx) override;`
- L100 _protected prototype_ `bool IsSlotOccupied(const FSoftComponentReference& InComponent, const int32 InSlotIdx);`
- L102 _protected prototype_ `void OnMaterialAssignmentChanged(UPrimitiveComponent* InPrimitiveComponent, const int32 InPrevSlotNum, const int32 InNewSlotNum, const TArray<int32>& InChangedMaterialSlots);`
- L104 _protected prototype_ `AActor* GetActor() const;`
- L105 _protected prototype_ `TConstArrayView<UPrimitiveComponent*> GetPrimitiveComponents();`
- L107 _protected prototype_ `void RefreshComponents();`
- L110 _protected prototype_ `bool RefreshMaterials();` — Return false if Actor invalid.
- L113 _protected member_ `TWeakObjectPtr<AActor> WeakActor;`
- L114 _protected member_ `TArray<FSoftComponentReference> WeakComponents;`
- L115 _protected member_ `TArray<UPrimitiveComponent*> LastResolvedComponents;`
- L116 _protected member_ `TMap<FSoftComponentReference, TBitArray<>> OccupiedMaterialSlots;`
- L117 _protected member_ `TMap<FSoftComponentReference, TArray<TWeakObjectPtr<UMaterialInterface>>> WeakMaterials;`
- L118 _protected member_ `TMap<FSoftComponentReference, TArray<TSharedPtr<IAvaMaskMaterialHandle>>> MaterialHandles;`
- L119 _protected member_ `TMap<FSoftComponentReference, TUniquePtr<FAvaMaskMaterialAssignmentObserver>> MaterialAssignmentObservers;`
- L120 _protected member_ `bool bIsIteratingMaterials = false;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMask/Private/Handling/AvaMaskAvaShapeMaterialCollectionHandle.h` (Private)


#### struct `FAvaMaskAvaShapeMaterialCollectionHandleData`  
`struct FAvaMaskAvaShapeMaterialCollectionHandleData`  
_L28-35_
- reflection: `USTRUCT()`
- L34 _public member_ `TMap<int32, FInstancedStruct> MaterialHandleData;` — `UPROPERTY()` — Per MeshIdx.

#### class `FAvaMaskAvaShapeMaterialCollectionHandle`  
`class FAvaMaskAvaShapeMaterialCollectionHandle : public TAvaMaskMaterialCollectionHandle<FAvaMaskAvaShapeMaterialCollectionHandleData>`  
_L37-117_
- inherits: `TAvaMaskMaterialCollectionHandle<FAvaMaskAvaShapeMaterialCollectionHandleData>`
- L41 _public prototype_ `UE_AVA_INHERITS_WITH_SUPER(FAvaMaskAvaShapeMaterialCollectionHandle, TAvaMaskMaterialCollectionHandle<FAvaMaskAvaShapeMaterialCollectionHandleData>);`
- L43 _public prototype_ `explicit FAvaMaskAvaShapeMaterialCollectionHandle(AActor* InActor);`
- L44 _public prototype_ `virtual ~FAvaMaskAvaShapeMaterialCollectionHandle() override = default;`
- L47 _public prototype_ `virtual FInstancedStruct MakeDataStruct() override;`
- L49 _public prototype_ `virtual TArray<TObjectPtr<UMaterialInterface>> GetMaterials() override;`
- L50 _public prototype_ `virtual TArray<TSharedPtr<IAvaMaskMaterialHandle>> GetMaterialHandles() override;`
- L51 _public prototype_ `virtual int32 GetNumMaterials() const override;`
- L53 _public prototype_ `virtual void SetMaterial(const FSoftComponentReference& InComponent, const int32 InSlotIdx, UMaterialInterface* InMaterial) override;`
- L54 _public prototype_ `virtual void SetMaterials(const TArray<TObjectPtr<UMaterialInterface>>& InMaterials, const TBitArray<>& InSetToggle) override;`
- L56 _public prototype_ `virtual void ForEachMaterial( TFunctionRef<bool( const FSoftComponentReference& InComponent , const int32 InIdx , UMaterialInterface* InMaterial)> InFunction) override;`
- L62 _public prototype_ `virtual void ForEachMaterialHandle( TFunctionRef<bool( const FSoftComponentReference& InComponent , const int32 InIdx , const bool bInIsSlotOccupied , const TSharedPtr<IAvaMaskMaterialHandle>& InMaterialHandle)> InFunction) override;`
- L69 _public prototype_ `virtual void MapEachMaterial( TFunctionRef<UMaterialInterface*( const FSoftComponentReference& InComponent , const int32 InIdx , UMaterialInterface* InMaterial)> InFunction) override;`
- L75 _public prototype_ `virtual void MapEachMaterialHandle( TFunctionRef<TSharedPtr<IAvaMaskMaterialHandle>( const FSoftComponentReference& InComponent , const int32 InIdx , const bool bInIsSlotOccupied , const TSharedPtr<IAvaMaskMaterialHandle>& InMaterialHandle)> InFunction) override;`
- L82 _public prototype_ `virtual bool IsValid() const override;`
- L85 _public prototype_ `static bool IsSupported(const FAvaMaskMaterialReference& InInstance, FName InTag = NAME_None);`
- L89 _protected prototype_ `virtual FStructView GetMaterialHandleData( FHandleData* InParentHandleData , const FSoftComponentReference& InComponent , const int32 InSlotIdx) override;`
- L94 _protected prototype_ `virtual ::FStructView GetOrAddMaterialHandleData( FHandleData* InParentHandleData , const TSharedPtr<IAvaMaskMaterialHandle>& InMaterialHandle , const FSoftComponentReference& InComponent , const int32 InSlotIdx) override;`
- L101 _protected prototype_ `bool IsSlotOccupied(const int32 InIdx);`
- L103 _protected prototype_ `UAvaShapeDynamicMeshBase* GetComponent();`
- L105 _protected prototype_ `void OnMaterialAssignmentChanged(UPrimitiveComponent* InPrimitiveComponent, const int32 InPrevSlotNum, const int32 InNewSlotNum, const TArray<int32>& InChangedMaterialSlots);`
- L108 _protected prototype_ `bool RefreshMaterials();` — Return false if Actor invalid.
- L111 _protected member_ `TWeakObjectPtr<AActor> WeakActor;`
- L112 _protected member_ `TWeakObjectPtr<UAvaShapeDynamicMeshBase> WeakComponent;`
- L113 _protected member_ `TBitArray<> OccupiedMaterialSlots;`
- L114 _protected member_ `TMap<int32, TWeakObjectPtr<UMaterialInterface>> WeakMaterials;`
- L115 _protected member_ `TMap<int32, TSharedPtr<IAvaMaskMaterialHandle>> MaterialHandles;`
- L116 _protected member_ `TUniquePtr<FAvaMaskMaterialAssignmentObserver> MaterialAssignmentObserver;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMask/Private/Handling/AvaMaskDesignedMaterialHandle.h` (Private)


#### struct `FAvaMaskDesignedMaterialHandleData`  
`struct FAvaMaskDesignedMaterialHandleData`  
_L18-30_
- reflection: `USTRUCT()`
- L23 _public member_ `FAvaMask2DMaterialParameters OriginalMaskMaterialParameters;` — `UPROPERTY()`
- L26 _public member_ `TEnumAsByte<EBlendMode> OriginalBlendMode = EBlendMode::BLEND_Opaque;` — `UPROPERTY()`
- L29 _public member_ `TSoftObjectPtr<UMaterialFunctionInterface> OriginalOutputProcessor;` — `UPROPERTY()`

#### class `FAvaMaskDesignedMaterialHandle`  
`class FAvaMaskDesignedMaterialHandle : public FAvaDesignedMaterialHandle , public TAvaMaskMaterialHandle<FAvaMaskDesignedMaterialHandleData>`  
_L32-89_
- inherits: `FAvaDesignedMaterialHandle,TAvaMaskMaterialHandle<FAvaMaskDesignedMaterialHandleData>`
- L37 _public prototype_ `UE_AVA_INHERITS_WITH_SUPER(FAvaMaskDesignedMaterialHandle, FAvaDesignedMaterialHandle);`
- L39 _public prototype_ `explicit FAvaMaskDesignedMaterialHandle(const TWeakObjectPtr<UDynamicMaterialInstance>& InWeakDesignedMaterial);`
- L43 _public prototype_ `virtual bool GetMaskParameters(FAvaMask2DMaterialParameters& OutParameters) override;`
- L44 _public prototype_ `virtual bool SetMaskParameters(UTexture* InTexture, float InBaseOpacity, bool bInInverted, const FVector2f& InPadding, bool bInApplyFeathering, float InOuterFeathering, float InInnerFeathering) override;`
- L45 _public prototype_ `virtual const EBlendMode GetBlendMode() override;`
- L46 _public prototype_ `virtual void SetBlendMode(const EBlendMode InBlendMode) override;`
- L47 _public function_ `virtual void SetChildMaterial(UMaterialInstanceDynamic* InChildMaterial) override`
- L48 _public prototype_ `virtual bool SaveOriginalState(const FStructView& InHandleData) override;`
- L49 _public prototype_ `virtual bool ApplyOriginalState(const FStructView& InHandleData , TUniqueFunction<void(UMaterialInterface*)>&& InMaterialSetter) override;`
- L51 _public prototype_ `virtual bool ApplyModifiedState(const FAvaMask2DSubjectParameters& InModifiedParameters , const FStructView& InHandleData , TUniqueFunction<void(UMaterialInterface*)>&& InMaterialSetter) override;`
- L57 _public function_ `virtual FString GetMaterialName() override`
- L58 _public function_ `virtual UMaterialInterface* GetMaterial() override`
- L59 _public function_ `virtual void CopyParametersFrom(UMaterialInstance* InSourceMaterial) override`
- L60 _public prototype_ `virtual bool HasRequiredParameters(TArray<FString>& OutMissingParameterNames) override;`
- L61 _public function_ `virtual void SetParentMaterial(UMaterialInterface* InMaterial) override`
- L62 _public function_ `virtual UMaterialInterface* GetParentMaterial() override`
- L66 _public prototype_ `virtual bool IsValid() const override;`
- L69 _public prototype_ `static bool IsSupported(const FAvaMaskMaterialReference& InInstance, FName InTag = NAME_None);`
- L72 _protected prototype_ `virtual UMaterialInstanceDynamic* GetMaterialInstance() override;`
- L75 _protected prototype_ `void OnMaterialBuilt(UDynamicMaterialModelBase* InMaterialModel);`
- L77 _protected prototype_ `UMaterialFunctionInterface* GetOutputProcessor(EBlendMode InBlendMode);`
- L78 _protected prototype_ `void SetOutputProcessor(EBlendMode InBlendMode, UMaterialFunctionInterface* InMaterialFunction);`
- L85 _private member_ `FAvaMask2DSubjectParameters LastAppliedParameters;`
- L87 _private member_ `FDelegateHandle OnMaterialBuiltHandle;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMask/Private/Handling/AvaMaskMaterialAssignmentObserver.h` (Private)


#### class `FAvaMaskMaterialAssignmentObserver`  
`class FAvaMaskMaterialAssignmentObserver`  
_L15-35_
- L18 _public typedef_ `using FOnMaterialAssignedDelegate = TMulticastDelegate<void(UPrimitiveComponent* InComponent, const int32 InPrevSlotNum, const int32 InNewSlotNum, const TArray<int32>& InChangedMaterialSlots)>;`
- L20 _public prototype_ `explicit FAvaMaskMaterialAssignmentObserver(UPrimitiveComponent* InComponent);`
- L21 _public prototype_ `~FAvaMaskMaterialAssignmentObserver();`
- L23 _public prototype_ `FOnMaterialAssignedDelegate& OnMaterialAssigned();`
- L25 _public prototype_ `UPrimitiveComponent* GetPrimitiveComponent() const;`
- L28 _private prototype_ `void OnComponentRenderStateDirty(UActorComponent& InComponent);`
- L30 _private member_ `TWeakObjectPtr<UPrimitiveComponent> ComponentWeak;`
- L31 _private member_ `FDelegateHandle RenderStateDirtyHandle;`
- L32 _private member_ `FOnMaterialAssignedDelegate OnMaterialAssignedDelegate;`
- L33 _private member_ `int32 SlotCount = 0;`
- L34 _private member_ `TArray<FObjectKey> Materials;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMask/Private/Handling/AvaMaskMaterialInstanceHandle.h` (Private)


#### struct `FAvaMaskMaterialInstanceHandleData`  
`struct FAvaMaskMaterialInstanceHandleData`  
_L17-29_
- reflection: `USTRUCT()`
- L22 _public member_ `TObjectPtr<UMaterialInterface> OriginalMaterial;` — `UPROPERTY()`
- L25 _public member_ `FAvaMask2DMaterialParameters OriginalMaskMaterialParameters;` — `UPROPERTY()`
- L28 _public member_ `TEnumAsByte<EBlendMode> OriginalBlendMode = EBlendMode::BLEND_Opaque;` — `UPROPERTY()`

#### class `FAvaMaskMaterialInstanceHandle`  
`class FAvaMaskMaterialInstanceHandle : public FAvaMaterialInstanceHandle , public TAvaMaskMaterialHandle<FAvaMaskMaterialInstanceHandleData>`  
_L32-74_
- inherits: `FAvaMaterialInstanceHandle,TAvaMaskMaterialHandle<FAvaMaskMaterialInstanceHandleData>`
- desc: This handles a Parent and (optionally) a Material Instance. It can also create the MaterialInstance.
- L37 _public prototype_ `UE_AVA_INHERITS_WITH_SUPER(FAvaMaskMaterialInstanceHandle, FAvaMaterialInstanceHandle);`
- L39 _public prototype_ `explicit FAvaMaskMaterialInstanceHandle(const TWeakObjectPtr<UMaterialInterface>& InWeakParentMaterial);`
- L40 _public prototype_ `virtual ~FAvaMaskMaterialInstanceHandle() override = default;`
- L43 _public prototype_ `virtual const EBlendMode GetBlendMode() override;`
- L44 _public prototype_ `virtual void SetBlendMode(const EBlendMode InBlendMode) override;`
- L45 _public function_ `virtual void SetChildMaterial(UMaterialInstanceDynamic* InChildMaterial) override`
- L46 _public prototype_ `virtual bool SaveOriginalState(const FStructView& InHandleData) override;`
- L47 _public prototype_ `virtual bool ApplyOriginalState( const FStructView& InHandleData , TUniqueFunction<void(UMaterialInterface*)>&& InMaterialSetter) override;`
- L50 _public prototype_ `virtual bool ApplyModifiedState( const FAvaMask2DSubjectParameters& InModifiedParameters , const FStructView& InHandleData , TUniqueFunction<void(UMaterialInterface*)>&& InMaterialSetter) override;`
- L57 _public function_ `virtual FString GetMaterialName() override`
- L58 _public function_ `virtual UMaterialInterface* GetMaterial() override`
- L59 _public function_ `virtual void CopyParametersFrom(UMaterialInstance* InSourceMaterial) override`
- L60 _public function_ `virtual void SetParentMaterial(UMaterialInterface* InMaterial) override`
- L61 _public function_ `virtual UMaterialInterface* GetParentMaterial() override`
- L65 _public prototype_ `virtual bool IsValid() const override;`
- L68 _public prototype_ `static bool IsSupported(const FAvaMaskMaterialReference& InInstance, FName InTag = NAME_None);`
- L71 _protected prototype_ `virtual UMaterialInstanceDynamic* GetMaterialInstance() override;`
- L72 _protected prototype_ `virtual UMaterialInstanceDynamic* GetOrCreateMaterialInstance(const FName InMaskName, const EBlendMode InBlendMode);`
- L73 _protected prototype_ `virtual UMaterialInstanceDynamic* GetOrCreateMaterialInstance() override;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMask/Private/Handling/AvaMaskMaterialReference.h` (Private)


#### struct `FAvaMaskMaterialReference`  
`struct FAvaMaskMaterialReference`  
_L8-34_
- desc: Describes a reference to an object containing a material, or the material itself
- L10 _public prototype_ `FAvaMaskMaterialReference() = default;`
- L12 _public function_ `explicit FAvaMaskMaterialReference(UObject* InObject, int32 InIndex = INDEX_NONE) : ObjectWeak(InObject) , Index(InIndex)`
- L18 _public prototype_ `FString ToString() const;`
- L21 _public prototype_ `UObject* GetObject() const;` — Resolves the weak object reference
- L24 _public function_ `template<typename T> T* GetTypedObject() const`
- L30 _public member_ `FWeakObjectPtr ObjectWeak;` — The material itself or the object holding the material
- L33 _public member_ `int32 Index = INDEX_NONE;` — Optional index to further identify a material in the object

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMask/Private/Handling/AvaMaskMediaPlateMaterialHandle.h` (Private)


#### class `FAvaMaskMediaPlateMaterialHandle`  
`class FAvaMaskMediaPlateMaterialHandle : public FAvaMaskMaterialInstanceHandle`  
_L7-31_
- inherits: `FAvaMaskMaterialInstanceHandle`
- L10 _public prototype_ `UE_AVA_INHERITS_WITH_SUPER(FAvaMaskMediaPlateMaterialHandle, FAvaMaskMaterialInstanceHandle);`
- L12 _public prototype_ `explicit FAvaMaskMediaPlateMaterialHandle(const TWeakObjectPtr<UMaterialInterface>& InWeakParentMaterial);`
- L13 _public prototype_ `virtual ~FAvaMaskMediaPlateMaterialHandle() override = default;`
- L16 _public prototype_ `virtual void SetBlendMode(const EBlendMode InBlendMode) override;`
- L19 _public prototype_ `static bool IsSupported(const FAvaMaskMaterialReference& InInstance, FName InTag = NAME_None);`
- L23 _protected prototype_ `virtual UMaterialInstanceDynamic* GetOrCreateMaterialInstance(const FName InMaskName, const EBlendMode InBlendMode) override;`
- L27 _protected prototype_ `virtual UMaterialInstanceDynamic* GetOrCreateMaterialInstance() override;`
- L30 _protected prototype_ `UMaterialInstanceDynamic* GetOrCreateMaterialInstanceImpl();`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMask/Private/Handling/AvaMaskParametricMaterialHandle.h` (Private)


#### struct `FAvaMaskParametricMaterialData`  
`struct FAvaMaskParametricMaterialData`  
_L14-26_
- reflection: `USTRUCT()`
- L19 _public member_ `FAvaMask2DMaterialParameters OriginalMaskMaterialParameters;` — `UPROPERTY()`
- L22 _public member_ `TEnumAsByte<EBlendMode> OriginalBlendMode = EBlendMode::BLEND_Opaque;` — `UPROPERTY()`
- L25 _public member_ `EAvaShapeParametricMaterialStyle OriginalMaterialStyle = EAvaShapeParametricMaterialStyle::Solid;` — `UPROPERTY()`

#### class `FAvaMaskParametricMaterialHandle`  
`class FAvaMaskParametricMaterialHandle : public FAvaParametricMaterialHandle , public TAvaMaskMaterialHandle<FAvaMaskParametricMaterialData>`  
_L28-78_
- inherits: `FAvaParametricMaterialHandle,TAvaMaskMaterialHandle<FAvaMaskParametricMaterialData>`
- L33 _public prototype_ `UE_AVA_INHERITS_WITH_SUPER(FAvaMaskParametricMaterialHandle, FAvaParametricMaterialHandle);`
- L35 _public prototype_ `explicit FAvaMaskParametricMaterialHandle(const FAvaMaskMaterialReference& InParametricMaterial);`
- L39 _public prototype_ `virtual bool GetMaskParameters(FAvaMask2DMaterialParameters& OutParameters) override;`
- L40 _public prototype_ `virtual bool SetMaskParameters(UTexture* InTexture, float InBaseOpacity, bool bInInverted, const FVector2f& InPadding, bool bInApplyFeathering, float InOuterFeathering, float InInnerFeathering) override;`
- L41 _public prototype_ `virtual const EBlendMode GetBlendMode() override;`
- L42 _public prototype_ `virtual void SetBlendMode(const EBlendMode InBlendMode) override;`
- L43 _public prototype_ `virtual void SetChildMaterial(UMaterialInstanceDynamic* InChildMaterial) override;`
- L44 _public prototype_ `virtual bool SaveOriginalState(const FStructView& InHandleData) override;`
- L45 _public prototype_ `virtual bool ApplyOriginalState(const FStructView& InHandleData , TUniqueFunction<void(UMaterialInterface*)>&& InMaterialSetter) override;`
- L47 _public prototype_ `virtual bool ApplyModifiedState(const FAvaMask2DSubjectParameters& InModifiedParameters , const FStructView& InHandleData , TUniqueFunction<void(UMaterialInterface*)>&& InMaterialSetter) override;`
- L53 _public function_ `virtual FString GetMaterialName() override`
- L54 _public function_ `virtual UMaterialInterface* GetMaterial() override`
- L55 _public function_ `virtual void CopyParametersFrom(UMaterialInstance* InSourceMaterial) override`
- L56 _public function_ `virtual void SetParentMaterial(UMaterialInterface* InMaterial) override`
- L57 _public function_ `virtual UMaterialInterface* GetParentMaterial() override`
- L61 _public prototype_ `virtual bool IsValid() const override;`
- L64 _public prototype_ `static bool IsSupported(const FAvaMaskMaterialReference& InInstance, FName InTag = NAME_None);`
- L67 _protected prototype_ `virtual UMaterialInstanceDynamic* GetMaterialInstance() override;`
- L69 _protected prototype_ `void OnMaterialChanged(const FAvaShapeParametricMaterial& InMaterial);`
- L72 _private member_ `FMaterialShadingModelField LastShadingModel;`
- L73 _private member_ `EBlendMode LastBlendMode;`
- L74 _private member_ `TWeakObjectPtr<UMaterialInstance> LastMaterialInstance;`
- L75 _private member_ `TWeakObjectPtr<UMaterialInstanceDynamic> ChildMaterial = nullptr;`
- L77 _private member_ `FDelegateHandle OnMaterialParameterChangedHandle;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMask/Private/Handling/AvaMaskText3DActorMaterialCollectionHandle.h` (Private)


#### struct `FAvaMaskText3DActorMaterialCollectionHandleData`  
`struct FAvaMaskText3DActorMaterialCollectionHandleData`  
_L27-36_
- reflection: `USTRUCT()`
- L32 _public member_ `EText3DMaterialBlendMode BlendMode = EText3DMaterialBlendMode::Opaque;` — `UPROPERTY()`
- L35 _public member_ `TMap<int32, FInstancedStruct> GroupMaterialData;` — `UPROPERTY()`

#### class `FAvaMaskText3DActorMaterialCollectionHandle`  
`class FAvaMaskText3DActorMaterialCollectionHandle : public TAvaMaskMaterialCollectionHandle<FAvaMaskText3DActorMaterialCollectionHandleData>`  
_L39-113_
- inherits: `TAvaMaskMaterialCollectionHandle<FAvaMaskText3DActorMaterialCollectionHandleData>`
- desc: Note that this doesn't explicitly require a Text3D Actor, it just checks that whatever Actor is given has a UText3DComponent (or derived).
- L43 _public prototype_ `UE_AVA_INHERITS_WITH_SUPER(FAvaMaskText3DActorMaterialCollectionHandle, TAvaMaskMaterialCollectionHandle<FAvaMaskText3DActorMaterialCollectionHandleData>);`
- L45 _public prototype_ `explicit FAvaMaskText3DActorMaterialCollectionHandle(AActor* InActor);`
- L49 _public prototype_ `virtual TArray<TObjectPtr<UMaterialInterface>> GetMaterials() override;`
- L51 _public prototype_ `virtual TArray<TSharedPtr<IAvaMaskMaterialHandle>> GetMaterialHandles() override;`
- L53 _public prototype_ `virtual void SetMaterial(const FSoftComponentReference& InComponent, const int32 InSlotIdx, UMaterialInterface* InMaterial) override;`
- L54 _public prototype_ `virtual void SetMaterials(const TArray<TObjectPtr<UMaterialInterface>>& InMaterials, const TBitArray<>& InSetToggle) override;`
- L56 _public prototype_ `virtual int32 GetNumMaterials() const override;`
- L58 _public prototype_ `virtual void ForEachMaterial( TFunctionRef<bool( const FSoftComponentReference& InComponent , const int32 InIdx , UMaterialInterface* InMaterial)> InFunction) override;`
- L64 _public prototype_ `virtual void ForEachMaterialHandle( TFunctionRef<bool( const FSoftComponentReference& InComponent , const int32 InIdx , const bool bInIsSlotOccupied , const TSharedPtr<IAvaMaskMaterialHandle>& InMaterialHandle)> InFunction) override;`
- L71 _public prototype_ `virtual void MapEachMaterial( TFunctionRef<UMaterialInterface*( const FSoftComponentReference& InComponent , const int32 InIdx , UMaterialInterface* InMaterial)> InFunction) override;`
- L77 _public prototype_ `virtual void MapEachMaterialHandle( TFunctionRef<TSharedPtr<IAvaMaskMaterialHandle>( const FSoftComponentReference& InComponent , const int32 InIdx , const bool bInIsSlotOccupied , const TSharedPtr<IAvaMaskMaterialHandle>& InMaterialHandle)> InFunction) override;`
- L84 _public prototype_ `virtual bool IsValid() const override;`
- L85 _public prototype_ `virtual bool SaveOriginalState(const FStructView& InHandleData) override;`
- L86 _public prototype_ `virtual bool ApplyOriginalState(const FStructView& InHandleData) override;`
- L87 _public prototype_ `virtual bool ApplyModifiedState(const FAvaMask2DSubjectParameters& InModifiedParameters, const FStructView& InHandleData) override;`
- L90 _public prototype_ `static bool IsSupported(const FAvaMaskMaterialReference& InInstance, FName InTag = NAME_None);`
- L94 _protected prototype_ `virtual FStructView GetMaterialHandleData( FHandleData* InParentHandleData , const FSoftComponentReference& InComponent , const int32 InSlotIdx) override;`
- L99 _protected prototype_ `virtual ::FStructView GetOrAddMaterialHandleData( FHandleData* InParentHandleData , const TSharedPtr<IAvaMaskMaterialHandle>& InMaterialHandle , const FSoftComponentReference& InComponent , const int32 InSlotIdx) override;`
- L106 _protected prototype_ `UText3DComponent* GetComponent() const;`
- L108 _protected prototype_ `void OnTextPostUpdate(UText3DComponent* InComponent, EText3DRendererFlags InFlags);`
- L110 _protected member_ `TWeakObjectPtr<AActor> WeakActor;`
- L111 _protected member_ `TWeakObjectPtr<UText3DComponent> WeakComponent;`
- L112 _protected member_ `TArray<TSharedPtr<IAvaMaskMaterialHandle>> MaterialHandles;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMask/Private/Handling/AvaMaterialInstanceHandle.h` (Private)


#### class `FAvaMaterialInstanceHandle`  
`class FAvaMaterialInstanceHandle : public IAvaMaterialHandle`  
_L17-46_
- inherits: `IAvaMaterialHandle`
- L21 _public prototype_ `UE_AVA_INHERITS_WITH_SUPER(FAvaMaterialInstanceHandle, IAvaMaterialHandle);`
- L23 _public prototype_ `static bool IsSupported(const FAvaMaskMaterialReference& InInstance, FName InTag = NAME_None);`
- L25 _public prototype_ `explicit FAvaMaterialInstanceHandle(const TWeakObjectPtr<UMaterialInterface>& InWeakParentMaterial);`
- L26 _public prototype_ `virtual ~FAvaMaterialInstanceHandle() override = default;`
- L29 _public prototype_ `virtual FString GetMaterialName() override;`
- L30 _public prototype_ `virtual UMaterialInterface* GetMaterial() override;`
- L31 _public prototype_ `virtual UMaterialInterface* GetParentMaterial() override;`
- L32 _public prototype_ `virtual void CopyParametersFrom(UMaterialInstance* InSourceMaterial) override;`
- L33 _public prototype_ `virtual void SetParentMaterial(UMaterialInterface* InMaterial) override;`
- L37 _public prototype_ `virtual bool IsValid() const override;`
- L41 _protected prototype_ `virtual UMaterialInstanceDynamic* GetMaterialInstance();`
- L42 _protected prototype_ `virtual UMaterialInstanceDynamic* GetOrCreateMaterialInstance();`
- L44 _protected member_ `TWeakObjectPtr<UMaterialInterface> WeakParentMaterial;`
- L45 _protected member_ `TWeakObjectPtr<UMaterialInstanceDynamic> WeakMaterialInstance;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMask/Private/Handling/AvaObjectHandleSubsystem.h` (Private)


#### class `UAvaObjectHandleSubsystem`  
`class UAvaObjectHandleSubsystem : public UEngineSubsystem`  
_L19-87_
- reflection: `UCLASS()`
- inherits: `UEngineSubsystem`
- desc: Responsible for providing Handlers for a given UObject.
- L24 _public member_ `static FString DefaultMaterialPath;`
- L27 _public prototype_ `virtual void Initialize(FSubsystemCollectionBase& Collection) override;`
- L30 _public prototype_ `TSharedPtr<IAvaObjectHandle> MakeHandleDirect(const FAvaMaskMaterialReference& InInstance, FName InTag = NAME_None);`
- L37 _public function_ `TSharedPtr<HandleType> MakeCollectionHandle(UObject* InOwner, FName InTag = NAME_None)`
- L47 _public function_ `TSharedPtr<HandleType> MakeMaterialHandle(UMaterialInterface* InInstance, FName InTag = NAME_None)`
- L60 _public function_ `TSharedPtr<HandleType> MakeHandle(ObjectType* InInstance, FName InTag = NAME_None)`
- L72 _public function_ `template<typename HandleType UE_REQUIRES(!std::is_const_v<HandleType> && std::is_base_of_v<IAvaObjectHandle, HandleType>)> TSharedPtr<HandleType> MakeHandle(const FAvaMaskMaterialReference& InInstance, FName InTag = NAME_None)`
- L78 _private prototype_ `void FindObjectHandleFactories();`
- L80 _private typedef_ `using FIsSupportedFunction = TFunction<bool(const FAvaMaskMaterialReference&, FName)>;`
- L81 _private typedef_ `using FMakeHandleFunction = TFunction<TSharedPtr<IAvaObjectHandle>(const FAvaMaskMaterialReference&)>;`
- L83 _private member_ `TArray<TPair<FIsSupportedFunction, FMakeHandleFunction>> ObjectHandleFactories;`
- L86 _private member_ `TSoftObjectPtr<UMaterialInterface> DefaultMaterial;` — `UPROPERTY()`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMask/Private/Handling/AvaParametricMaterialHandle.h` (Private)


#### class `FAvaParametricMaterialHandle`  
`class FAvaParametricMaterialHandle : public FAvaMaterialInstanceHandle`  
_L13-35_
- inherits: `FAvaMaterialInstanceHandle`
- L16 _public prototype_ `UE_AVA_INHERITS_WITH_SUPER(FAvaParametricMaterialHandle, FAvaMaterialInstanceHandle);`
- L18 _public prototype_ `explicit FAvaParametricMaterialHandle(const FAvaMaskMaterialReference& InParametricMaterial);`
- L21 _public prototype_ `virtual void CopyParametersFrom(UMaterialInstance* InSourceMaterial) override;`
- L25 _public prototype_ `virtual bool IsValid() const override;`
- L28 _public prototype_ `static bool IsSupported(const FAvaMaskMaterialReference& InInstance, FName InTag = NAME_None);`
- L31 _protected prototype_ `FAvaShapeParametricMaterial* GetParametricMaterial();`
- L32 _protected prototype_ `virtual UMaterialInstanceDynamic* GetMaterialInstance() override;`
- L34 _protected member_ `FAvaMaskMaterialReference MaterialReference;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMask/Private/Handling/IAvaMaskMaterialCollectionHandle.h` (Private)


#### class `IAvaMaskMaterialCollectionHandle`  
`class IAvaMaskMaterialCollectionHandle : public IAvaObjectHandle`  
_L23-89_
- inherits: `IAvaObjectHandle`
- desc: Interface between the mask system and an arbitrary number of materials that need to be instantiated and parameters manipulated.
- L27 _public prototype_ `UE_AVA_INHERITS(IAvaMaskMaterialCollectionHandle, IAvaObjectHandle);`
- L29 _public typedef_ `using FOnSourceMaterialPreAssignment = TDelegate<UMaterialInterface*(const UMaterialInterface* InPreviousMaterial, UMaterialInterface* InNewMaterial)>;`
- L30 _public typedef_ `using FOnSourceMaterialsChanged = TDelegate<void(UObject* InMaterialOwner, const TArray<TSharedPtr<IAvaMaskMaterialHandle>>& InMaterialHandles)>;`
- L33 _public prototype_ `virtual ~IAvaMaskMaterialCollectionHandle() override = default;`
- L35 _public prototype_ `virtual FInstancedStruct MakeDataStruct() = 0;`
- L37 _public prototype_ `virtual TArray<TObjectPtr<UMaterialInterface>> GetMaterials() = 0;`
- L38 _public prototype_ `virtual TArray<TSharedPtr<IAvaMaskMaterialHandle>> GetMaterialHandles() = 0;`
- L39 _public prototype_ `virtual int32 GetNumMaterials() const = 0;`
- L41 _public prototype_ `virtual void SetMaterial(const FSoftComponentReference& InComponent, const int32 InSlotIdx, UMaterialInterface* InMaterial) = 0;`
- L42 _public prototype_ `virtual void SetMaterials(const TArray<TObjectPtr<UMaterialInterface>>& InMaterials) = 0;`
- L43 _public prototype_ `virtual void SetMaterials(const TArray<TObjectPtr<UMaterialInterface>>& InMaterials, const TBitArray<>& InSetToggle) = 0;`
- L45 _public prototype_ `virtual void ForEachMaterial( TFunctionRef<bool( const FSoftComponentReference& InComponent , const int32 InIdx , UMaterialInterface* InMaterial)> InFunction) = 0;`
- L51 _public prototype_ `virtual void ForEachMaterialHandle( TFunctionRef<bool( const FSoftComponentReference& InComponent , const int32 InIdx , const bool bInIsSlotOccupied , const TSharedPtr<IAvaMaskMaterialHandle>& InMaterialHandle)> InFunction) = 0;`
- L58 _public prototype_ `virtual void MapEachMaterial( TFunctionRef<UMaterialInterface*( const FSoftComponentReference& InComponent , const int32 InIdx , UMaterialInterface* InMaterial)> InFunction) = 0;`
- L64 _public prototype_ `virtual void MapEachMaterialHandle( TFunctionRef<TSharedPtr<IAvaMaskMaterialHandle>( const FSoftComponentReference& InComponent , const int32 InIdx , const bool bInIsSlotOccupied , const TSharedPtr<IAvaMaskMaterialHandle>& InMaterialHandle)> InFunction) = 0;`
- L72 _public prototype_ `virtual bool GetComponentAndSlotForMaterial( const UMaterialInterface* InMaterial, FSoftComponentReference& OutComponent, int32& OutSlotIdx) = 0;` — Return if found.
- L77 _public prototype_ `virtual bool SaveOriginalState(const FStructView& InHandleData) = 0;`
- L78 _public prototype_ `virtual bool ApplyOriginalState(const FStructView& InHandleData) = 0;`
- L79 _public prototype_ `virtual bool ApplyModifiedState( const FAvaMask2DSubjectParameters& InModifiedParameters , const FStructView& InHandleData) = 0;`
- L84 _public prototype_ `virtual FOnSourceMaterialPreAssignment& OnSourceMaterialPreAssignment() = 0;` — Provides the opportunity to modify or replace a material on assignment.
- L86 _public prototype_ `virtual FOnSourceMaterialsChanged& OnSourceMaterialsChanged() = 0;`
- L88 _public prototype_ `virtual bool ValidateMaterials(FText& OutFailReason) = 0;`

#### class `TAvaMaskMaterialCollectionHandle`  
`template <typename HandleDataType> class TAvaMaskMaterialCollectionHandle : public IAvaMaskMaterialCollectionHandle`  
_L92-143_
- inherits: `IAvaMaskMaterialCollectionHandle`
- L98 _public prototype_ `UE_AVA_INHERITS_WITH_SUPER(TAvaMaskMaterialCollectionHandle, IAvaMaskMaterialCollectionHandle);`
- L100 _public typedef_ `using FHandleData = HandleDataType;`
- L103 _public prototype_ `virtual FInstancedStruct MakeDataStruct() override;`
- L105 _public prototype_ `virtual void SetMaterials(const TArray<TObjectPtr<UMaterialInterface>>& InMaterials) override;`
- L106 _public prototype_ `virtual void SetMaterials(const TArray<TObjectPtr<UMaterialInterface>>& InMaterials, const TBitArray<>& InSetToggle) override = 0;`
- L109 _public prototype_ `virtual bool GetComponentAndSlotForMaterial( const UMaterialInterface* InMaterial, FSoftComponentReference& OutComponent, int32& OutSlotIdx) override;` — Return if found.
- L114 _public prototype_ `virtual bool SaveOriginalState(const FStructView& InHandleData) override;`
- L115 _public prototype_ `virtual bool ApplyOriginalState(const FStructView& InHandleData) override;`
- L116 _public prototype_ `virtual bool ApplyModifiedState( const FAvaMask2DSubjectParameters& InModifiedParameters , const FStructView& InHandleData) override;`
- L121 _public prototype_ `virtual IAvaMaskMaterialCollectionHandle::FOnSourceMaterialPreAssignment& OnSourceMaterialPreAssignment() override;` — Provides the opportunity to modify or replace a material on assignment.
- L123 _public prototype_ `virtual FOnSourceMaterialsChanged& OnSourceMaterialsChanged() override;`
- L125 _public prototype_ `virtual bool ValidateMaterials(FText& OutFailReason) override;`
- L128 _protected prototype_ `virtual FStructView GetMaterialHandleData( FHandleData* InParentHandleData , const FSoftComponentReference& InComponent , const int32 InSlotIdx) = 0;`
- L133 _protected prototype_ `virtual FStructView GetOrAddMaterialHandleData( FHandleData* InParentHandleData , const TSharedPtr<IAvaMaskMaterialHandle>& InMaterialHandle , const FSoftComponentReference& InComponent , const int32 InSlotIdx) = 0;`
- L140 _protected member_ `IAvaMaskMaterialCollectionHandle::FOnSourceMaterialPreAssignment OnSourceMaterialPreAssignmentDelegate;`
- L141 _protected member_ `FOnSourceMaterialsChanged OnSourceMaterialsChangedDelegate;`
- L142 _protected member_ `FAvaMask2DSubjectParameters LastAppliedParameters;`
- L146 _function_ `template <typename HandleDataType> FInstancedStruct TAvaMaskMaterialCollectionHandle<HandleDataType>::MakeDataStruct()`
- L153 _function_ `template <typename HandleDataType> void TAvaMaskMaterialCollectionHandle<HandleDataType>::SetMaterials( const TArray<TObjectPtr<UMaterialInterface>>& InMaterials)`
- L161 _function_ `template <typename HandleDataType> bool TAvaMaskMaterialCollectionHandle<HandleDataType>::GetComponentAndSlotForMaterial( const UMaterialInterface* InMaterial , FSoftComponentReference& OutComponent , int32& OutSlotIdx)`
- L189 _function_ `template <typename HandleDataType> bool TAvaMaskMaterialCollectionHandle<HandleDataType>::SaveOriginalState(const FStructView& InHandleData)`
- L220 _function_ `template <typename HandleDataType> bool TAvaMaskMaterialCollectionHandle<HandleDataType>::ApplyOriginalState(const FStructView& InHandleData)`
- L265 _function_ `template <typename HandleDataType> bool TAvaMaskMaterialCollectionHandle<HandleDataType>::ApplyModifiedState( const FAvaMask2DSubjectParameters& InModifiedParameters , const FStructView& InHandleData)`
- L309 _function_ `template <typename HandleDataType> IAvaMaskMaterialCollectionHandle::FOnSourceMaterialPreAssignment& TAvaMaskMaterialCollectionHandle<HandleDataType>::OnSourceMaterialPreAssignment()`
- L315 _function_ `template <typename HandleDataType> IAvaMaskMaterialCollectionHandle::FOnSourceMaterialsChanged& TAvaMaskMaterialCollectionHandle<HandleDataType>::OnSourceMaterialsChanged()`
- L321 _function_ `template <typename HandleDataType> bool TAvaMaskMaterialCollectionHandle<HandleDataType>::ValidateMaterials(FText& OutFailReason)`

#### Free symbols / members of external scopes

- L175 _function_ `` (scope `TAvaMaskMaterialCollectionHandle::GetComponentAndSlotForMaterial`)
- L198 _function_ `` (scope `TAvaMaskMaterialCollectionHandle::SaveOriginalState`)
- L229 _function_ `` (scope `TAvaMaskMaterialCollectionHandle::ApplyOriginalState`)
- L242 _function_ `` (scope `TAvaMaskMaterialCollectionHandle::ApplyOriginalState::__anondce57f7c0302`)
- L278 _function_ `` (scope `TAvaMaskMaterialCollectionHandle::ApplyModifiedState`)
- L292 _function_ `` (scope `TAvaMaskMaterialCollectionHandle::ApplyModifiedState::__anondce57f7c0502`)
- L333 _function_ `` (scope `TAvaMaskMaterialCollectionHandle::ValidateMaterials`)

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMask/Private/Handling/IAvaMaskMaterialHandle.h` (Private)


#### class `IAvaMaskMaterialHandle`  
`class IAvaMaskMaterialHandle : public IAvaMaterialHandle`  
_L24-56_
- inherits: `IAvaMaterialHandle`
- desc: Interface between the mask system and an individual material.
- L28 _public prototype_ `UE_AVA_INHERITS(IAvaMaskMaterialHandle, IAvaMaterialHandle);`
- L30 _public prototype_ `virtual ~IAvaMaskMaterialHandle() override = default;`
- L32 _public prototype_ `virtual FInstancedStruct MakeDataStruct() = 0;`
- L33 _public prototype_ `virtual const UScriptStruct* GetDataStructType() = 0;`
- L35 _public prototype_ `virtual bool GetMaskParameters(FAvaMask2DMaterialParameters& OutParameters) = 0;`
- L36 _public prototype_ `virtual bool SetMaskParameters(UTexture* InTexture, float InBaseOpacity, bool bInInverted = false, const FVector2f& InPadding = FVector2f::Zero(), bool bInApplyFeathering = false, float InOuterFeathering = 0.0f, float InInnerFeathering = 0.0f) = 0;`
- L38 _public prototype_ `virtual const EBlendMode GetBlendMode() = 0;`
- L39 _public prototype_ `virtual void SetBlendMode(const EBlendMode InBlendMode) = 0;`
- L42 _public prototype_ `virtual void SetChildMaterial(UMaterialInstanceDynamic* InChildMaterial) = 0;` — Provides the opportunity to propagate changes to a derived material.
- L44 _public prototype_ `virtual bool SaveOriginalState(const FStructView& InHandleData) = 0;`
- L46 _public prototype_ `virtual bool ApplyOriginalState( const FStructView& InHandleData , TUniqueFunction<void(UMaterialInterface*)>&& InMaterialSetter) = 0;`
- L50 _public prototype_ `virtual bool ApplyModifiedState( const FAvaMask2DSubjectParameters& InModifiedParameters , const FStructView& InHandleData , TUniqueFunction<void(UMaterialInterface*)>&& InMaterialSetter) = 0;`
- L55 _public prototype_ `virtual bool HasRequiredParameters(TArray<FString>& OutMissingParameterNames) = 0;`

#### class `TAvaMaskMaterialHandle`  
`template <typename HandleDataType> class TAvaMaskMaterialHandle : public IAvaMaskMaterialHandle`  
_L59-80_
- inherits: `IAvaMaskMaterialHandle`
- L65 _public prototype_ `UE_AVA_INHERITS_WITH_SUPER(TAvaMaskMaterialHandle, IAvaMaskMaterialHandle);`
- L67 _public typedef_ `using FHandleData = HandleDataType;`
- L70 _public prototype_ `virtual FInstancedStruct MakeDataStruct() override;`
- L71 _public prototype_ `virtual const UScriptStruct* GetDataStructType() override;`
- L73 _public prototype_ `virtual bool GetMaskParameters(FAvaMask2DMaterialParameters& OutParameters) override;`
- L74 _public prototype_ `virtual bool SetMaskParameters(UTexture* InTexture, float InBaseOpacity, bool bInInverted = false, const FVector2f& InPadding = FVector2f::Zero(), bool bInApplyFeathering = false, float InOuterFeathering = 0.0f, float InInnerFeathering = 0.0f) override;`
- L76 _public prototype_ `virtual bool HasRequiredParameters(TArray<FString>& OutMissingParameterNames) override;`
- L79 _protected prototype_ `virtual UMaterialInstanceDynamic* GetMaterialInstance() = 0;`
- L83 _function_ `template <typename HandleDataType> FInstancedStruct TAvaMaskMaterialHandle<HandleDataType>::MakeDataStruct()`
- L90 _function_ `template <typename HandleDataType> const UScriptStruct* TAvaMaskMaterialHandle<HandleDataType>::GetDataStructType()`
- L96 _function_ `template <typename HandleDataType> bool TAvaMaskMaterialHandle<HandleDataType>::GetMaskParameters(FAvaMask2DMaterialParameters& OutParameters)`
- L108 _function_ `template <typename HandleDataType> bool TAvaMaskMaterialHandle<HandleDataType>::SetMaskParameters(UTexture* InTexture , float InBaseOpacity , bool bInInverted , const FVector2f& InPadding , bool bInApplyFeathering , float InOuterFeathering , float InInnerFeathering)`
- L135 _function_ `template <typename HandleDataType> bool TAvaMaskMaterialHandle<HandleDataType>::HasRequiredParameters(TArray<FString>& OutMissingParameterNames)`

#### Free symbols / members of external scopes

- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace AvaMask` (scope `UE`)
- L18 _namespace_ `namespace Internal` (scope `UE::AvaMask`)
- L20 _prototype_ `UAvaMaskMaterialInstanceSubsystem* GetMaterialInstanceSubsystem();` (scope `UE::AvaMask::Internal`)

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMask/Private/Handling/IAvaMaterialHandle.h` (Private)


#### class `IAvaMaterialHandle`  
`class IAvaMaterialHandle : public IAvaObjectHandle`  
_L11-25_
- inherits: `IAvaObjectHandle`
- L15 _public prototype_ `UE_AVA_INHERITS(IAvaMaterialHandle, IAvaObjectHandle);`
- L17 _public prototype_ `virtual ~IAvaMaterialHandle() override = default;`
- L19 _public prototype_ `virtual FString GetMaterialName() = 0;`
- L20 _public prototype_ `virtual UMaterialInterface* GetMaterial() = 0;`
- L21 _public prototype_ `virtual UMaterialInterface* GetParentMaterial() = 0;`
- L22 _public prototype_ `virtual void SetParentMaterial(UMaterialInterface* InMaterial) = 0;`
- L24 _public prototype_ `virtual void CopyParametersFrom(UMaterialInstance* InSourceMaterial) = 0;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMask/Private/Handling/IAvaObjectHandle.h` (Private)


#### class `IAvaObjectHandle`  
`class IAvaObjectHandle : public IAvaTypeCastable`  
_L16-27_
- inherits: `IAvaTypeCastable`
- desc: Interface between a calling system to perform operations on a specific object.
- L22 _public typedef_ `using FIsSupportedFunction = TFunction<bool(const UStruct*, const void*)>;`
- L24 _public prototype_ `virtual ~IAvaObjectHandle() = default;`
- L26 _public prototype_ `virtual bool IsValid() const = 0;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMask/Private/Materials/AvaMaskMaterialFactory.h` (Private)


#### class `UAvaMaskMaterialFactoryBase`  
`class UAvaMaskMaterialFactoryBase : public UObject`  
_L19-30_
- reflection: `UCLASS(Abstract)`
- inherits: `UObject`
- desc: Implementations are responsible for creating MaterialInstanceDynamic's for a given parent UMaterialInterface. This differs to AvaObjectHandle implementations, as they only deal with existing object instances and don't create them.

#### class `UAvaMaskMaterialFactory`  
`class UAvaMaskMaterialFactory : public UAvaMaskMaterialFactoryBase`  
_L34-42_
- reflection: `UCLASS()`
- inherits: `UAvaMaskMaterialFactoryBase`
- desc: Creates an MID for a given Material asset.
- L40 _public prototype_ `virtual TSubclassOf<UMaterialInterface> GetSupportedMaterialClass() const override;`
- L41 _public prototype_ `virtual UMaterialInstanceDynamic* CreateMID(UObject* InOuter, const TObjectPtr<UMaterialInterface>& InParentMaterial, const EBlendMode InBlendMode) const override;`

#### class `UAvaMaskMaterialInstanceConstantFactory`  
`class UAvaMaskMaterialInstanceConstantFactory : public UAvaMaskMaterialFactoryBase`  
_L46-55_
- reflection: `UCLASS()`
- inherits: `UAvaMaskMaterialFactoryBase`
- desc: Creates an MID for a given MIC.
- L52 _public prototype_ `virtual TSubclassOf<UMaterialInterface> GetSupportedMaterialClass() const override;`
- L53 _public prototype_ `virtual UMaterialInstanceDynamic* CreateMID(UObject* InOuter, const TObjectPtr<UMaterialInterface>& InParentMaterial, const EBlendMode InBlendMode) const override;`
- L54 _public prototype_ `UMaterialInstanceConstant* CreateMIC(UObject* InOuter, const TObjectPtr<UMaterialInterface>& InParentMaterial, const EBlendMode InBlendMode) const;`

#### class `UAvaMaskMaterialInstanceDynamicFactory`  
`class UAvaMaskMaterialInstanceDynamicFactory : public UAvaMaskMaterialFactoryBase`  
_L59-67_
- reflection: `UCLASS()`
- inherits: `UAvaMaskMaterialFactoryBase`
- desc: Creates an MID for a given MID.
- L65 _public prototype_ `virtual TSubclassOf<UMaterialInterface> GetSupportedMaterialClass() const override;`
- L66 _public prototype_ `virtual UMaterialInstanceDynamic* CreateMID(UObject* InOuter, const TObjectPtr<UMaterialInterface>& InParentMaterial, const EBlendMode InBlendMode) const override;`

#### class `UAvaMaskDesignedMaterialFactory`  
`class UAvaMaskDesignedMaterialFactory : public UAvaMaskMaterialFactoryBase`  
_L71-79_
- reflection: `UCLASS()`
- inherits: `UAvaMaskMaterialFactoryBase`
- desc: Creates an MID for a given Material Designer material.
- L77 _public prototype_ `virtual TSubclassOf<UMaterialInterface> GetSupportedMaterialClass() const override;`
- L78 _public prototype_ `virtual UMaterialInstanceDynamic* CreateMID(UObject* InOuter, const TObjectPtr<UMaterialInterface>& InParentMaterial, const EBlendMode InBlendMode) const override;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMask/Public/AvaMaskTypes.h` (Public)


#### struct `FAvaMask2DComponentMaterialPath`  
`struct FAvaMask2DComponentMaterialPath`  
_L16-31_
- reflection: `USTRUCT()`
- desc: Describes a component/material slot pair.
- L21 _public member_ `FSoftComponentReference Component;` — `UPROPERTY()`
- L24 _public member_ `int32 SlotIdx = 0;` — `UPROPERTY()`
- L27 _public function_ `bool operator==(const FAvaMask2DComponentMaterialPath& Other) const` — FAvaMask2DComponentMaterialPath == operator

#### struct `FAvaMask2DMaterialParameters`  
`struct FAvaMask2DMaterialParameters`  
_L40-110_
- reflection: `USTRUCT()`
- desc: Used to store, set and compare material parameter values.
- L45 _public prototype_ `FAvaMask2DMaterialParameters() = default;`
- L46 _public prototype_ `FAvaMask2DMaterialParameters(const FAvaMask2DMaterialParameters&) = default;`
- L47 _public prototype_ `FAvaMask2DMaterialParameters(FAvaMask2DMaterialParameters&&) = default;`
- L48 _public prototype_ `FAvaMask2DMaterialParameters& operator=(const FAvaMask2DMaterialParameters&) = default;`
- L49 _public prototype_ `FAvaMask2DMaterialParameters& operator=(FAvaMask2DMaterialParameters&&) = default;`
- L52 _public prototype_ `bool HasSameParameters(const FAvaMask2DMaterialParameters& InOther) const;`
- L56 _public member_ `FName CanvasName;` — `UPROPERTY()` — Canvas/Channel name.
- L61 _public member_ `TObjectPtr<UTexture> Texture_DEPRECATED = nullptr;` — `UE_DEPRECATED(5.8, "Mask texture is deprecated. Use the mask texture collection member variable instead")` — `UPROPERTY()` — Mask texture.
- L65 _public member_ `TObjectPtr<UTextureRenderTarget2DArray> RenderTarget;` — `UPROPERTY()` — Render target array to use for masking
- L69 _public member_ `FLinearColor MaskIndices = FLinearColor(-1, -1, -1, -1);` — `UPROPERTY()` — Indices to the mask textures array. Each component (R,G,B,A) represents an index
- L74 _public member_ `EGeometryMaskColorChannel Channel_DEPRECATED = EGeometryMaskColorChannel::Red;` — `UE_DEPRECATED(5.8, "Color channel management has been deprecated as it's no longer needed")` — `UPROPERTY()` — Multiplies the mask texture to determine which channel to read from.
- L79 _public member_ `FLinearColor ChannelAsVector_DEPRECATED = FLinearColor::Red;` — `UE_DEPRECATED(5.8, "Color channel management has been deprecated as it's no longer needed")` — `UPROPERTY()` — Multiplies the mask texture to determine which channel to read from.
- L83 _public member_ `bool bInvert = false;` — `UPROPERTY()` — Whether the mask result should be inverted when applied. This is stored in the material as a float to allow runtime modification.
- L87 _public member_ `float BaseOpacity = 0.0f;` — `UPROPERTY()` — Base opacity/alpha to use in Read mode.
- L91 _public member_ `FVector2f Padding = FVector2f::Zero();` — `UPROPERTY()` — The render target might be larger/overscanned, so we need to compensate.
- L94 _public member_ `bool bApplyFeathering = false;` — `UPROPERTY()`
- L97 _public member_ `float OuterFeatherRadius = 0.0f;` — `UPROPERTY()`
- L100 _public member_ `float InnerFeatherRadius = 0.0f;` — `UPROPERTY()`
- L103 _public member_ `TEnumAsByte<EBlendMode> BlendMode = EBlendMode::BLEND_Opaque;` — `UPROPERTY()`
- L106 _public prototype_ `bool ApplyToMID(UMaterialInstanceDynamic* InMaterial) const;` — Applies the current values of this struct to the given material parameters. Returns true if successful.
- L109 _public prototype_ `bool StoreFromMaterial(const UMaterialInterface* InMaterial);` — Set current values of the given material and stores it in the member variables of this struct. Returns true if successful.

#### struct `FAvaMask2DSubjectParameters`  
`struct FAvaMask2DSubjectParameters`  
_L114-120_
- reflection: `USTRUCT()`
- desc: Encapsulates all parameters to apply to a given modifier subject.
- L119 _public member_ `FAvaMask2DMaterialParameters MaterialParameters;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L33 _function_ `inline uint32 GetTypeHash(const FAvaMask2DComponentMaterialPath& MaterialPath)`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMask/Public/Mask2D/AvaMask2DBaseModifier.h` (Public)


#### enum `EAvaMask2DMode`  
`enum class EAvaMask2DMode : uint8`  
_L34-38_
- reflection: `UENUM(BlueprintType)`
- L36 _public enumerator_ `Read UMETA(DisplayName = "Target", ToolTip = "Use the specified Mask Channel to apply to this geometry")`
- L37 _public enumerator_ `Write UMETA(DisplayName = "Source", ToolTip = "Use the specified Mask Channel to render this geometry to")`

#### struct `FAvaMask2DActorData`  
`struct FAvaMask2DActorData`  
_L45-56_
- reflection: `USTRUCT(meta=(Deprecated="5.8"))`
- desc: DEPRECATED for 5.8 Used for target actors to store essential information
- L51 _public member_ `TWeakObjectPtr<UTexture> CanvasTextureWeak;` — `UPROPERTY(Transient)` — The canvas texture to apply to this actor materials
- L55 _public member_ `TMap<FAvaMask2DComponentMaterialPath, TObjectPtr<UMaterialInterface>> OriginalMaterials;` — `UPROPERTY()` — Original assigned materials, used to create instances from, and restore to when modifier removed.

#### class `UAvaMask2DBaseModifier`  
`class UAvaMask2DBaseModifier : public UActorModifierArrangeBaseModifier, public IGeometryMaskClient`  
_L60-313_
- reflection: `UCLASS(Abstract, MinimalAPI)`
- inherits: `UActorModifierArrangeBaseModifier,IGeometryMaskClient`
- desc: Uses scene actors to create a mask texture and applies it to attached actors
- L69 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& InPropertyChangedEvent) override;`
- L73 _public function_ `bool UseParentChannel() const`
- L77 _public prototype_ `void SetUseParentChannel(const bool bInUseParentChannel);`
- L79 _public prototype_ `const FName GetChannel() const;`
- L80 _public prototype_ `void SetChannel(FName InChannel);`
- L82 _public function_ `bool IsInverted() const`
- L86 _public prototype_ `void SetIsInverted(const bool bInInvert);`
- L88 _public function_ `bool UseBlur() const`
- L92 _public prototype_ `void UseBlur(bool bInUseBlur);`
- L94 _public function_ `float GetBlurStrength() const`
- L98 _public prototype_ `void SetBlurStrength(float InBlurStrength);`
- L100 _public function_ `bool UseFeathering() const`
- L104 _public prototype_ `void UseFeathering(bool bInUseFeathering);`
- L106 _public function_ `int32 GetOuterFeatherRadius() const`
- L110 _public prototype_ `void SetOuterFeatherRadius(int32 InFeatherRadius);`
- L112 _public function_ `int32 GetInnerFeatherRadius() const`
- L116 _public prototype_ `void SetInnerFeatherRadius(int32 InFeatherRadius);`
- L119 _public prototype_ `FName GenerateUniqueMaskName() const;` — Utility to generate a unique mask name based on the associated Actor
- L122 _public prototype_ `static UAvaMask2DBaseModifier* FindMaskModifierOnActor(const AActor* InActor);` — Utility to find an existing modifier on the provided actor or it's parent
- L126 _protected prototype_ `virtual bool ForEachUsedCanvasName(TFunctionRef<bool(FName)> InFunc) const override;`
- L130 _protected prototype_ `virtual void OnModifierCDOSetup(FActorModifierCoreMetadata& InMetadata) override;`
- L131 _protected prototype_ `virtual void OnModifierAdded(EActorModifierCoreEnableReason InReason) override;`
- L132 _protected prototype_ `virtual void OnModifierRemoved(EActorModifierCoreDisableReason InReason) override;`
- L133 _protected prototype_ `virtual void OnModifiedActorTransformed() override;`
- L134 _protected prototype_ `virtual void RestorePreState() override;`
- L135 _protected prototype_ `virtual void Apply() override;`
- L139 _protected prototype_ `virtual void OnSceneTreeTrackedActorParentChanged(int32 InIdx, const TArray<TWeakObjectPtr<AActor>>& InPreviousParentActor, const TArray<TWeakObjectPtr<AActor>>& InNewParentActor) override;`
- L140 _protected prototype_ `virtual void OnSceneTreeTrackedActorChildrenChanged(int32 InIdx, const TSet<TWeakObjectPtr<AActor>>& InPreviousChildrenActors, const TSet<TWeakObjectPtr<AActor>>& InNewChildrenActors) override;`
- L144 _protected prototype_ `virtual void OnRenderStateUpdated(AActor* InActor, UActorComponent* InComponent) override;`
- L148 _protected prototype_ `virtual void SaveActorPreState(AActor* InActor, FAvaMask2DActorData& InActorData);` — `UE_DEPRECATED(5.8, "Actor pre state logic has been moved to the Read modifier.")`
- L151 _protected prototype_ `virtual void RestoreActorPreState(AActor* InActor, FAvaMask2DActorData& InActorData);` — `UE_DEPRECATED(5.8, "Actor pre state logic has been moved to the Read modifier.")`
- L153 _protected prototype_ `void OnUseParentChannelChanged();`
- L154 _protected prototype_ `void OnChannelChanged();`
- L155 _protected prototype_ `void OnInvertedChanged();`
- L156 _protected prototype_ `void OnBlurChanged();`
- L157 _protected prototype_ `void OnFeatherChanged();`
- L158 _protected prototype_ `void OnCanvasChanged();`
- L160 _protected prototype_ `void UpdateCanvas();`
- L166 _protected prototype_ `void CanvasParamsToLocal(bool bInResolveCanvas=true);` — Stores specific properties on the canvas locally. @param bInResolveCanvas whether to resolve canvas if the cached one is not valid
- L169 _protected prototype_ `void LocalParamsToCanvas();` — Apply locally stored parameters to the canvas.
- L171 _protected prototype_ `void SetupChannelName();`
- L172 _protected prototype_ `virtual void SetupMaskComponent(UActorComponent* InComponent);`
- L173 _protected prototype_ `virtual void RemoveFromActor(AActor* InActor);`
- L176 _protected prototype_ `void OnMaskSetCanvas(const UGeometryMaskCanvas* InCanvas, AActor* InActor);` — `UE_DEPRECATED(5.8, "ActorData has been deprecated. Actor restore takes place in the Material Read Modifier directly.")`
- L178 _protected prototype_ `UActorComponent* FindOrAddMaskComponent(TSubclassOf<UActorComponent> InComponentClass, AActor* InActor);`
- L181 _protected function_ `template<typename InComponentClass UE_REQUIRES(std::is_base_of_v<UActorComponent, InComponentClass>)> InComponentClass* FindOrAddMaskComponent(AActor* InActor)`
- L186 _protected prototype_ `static bool ActorSupportsMaskReadWrite(const AActor* InActor);`
- L189 _protected prototype_ `bool TryResolveParentChannel();` — Returns true if parent channel was found
- L192 _protected prototype_ `UGeometryMaskWorldSubsystem* GetGeometryMaskWorldSubsystem(const ULevel** OutLevel = nullptr) const;` — Returns world subsystem and, optionally, the level for this modifier
- L194 _protected prototype_ `void TryResolveCanvas();`
- L197 _protected prototype_ `UTexture* TryResolveCanvasTexture(AActor* InActor, FAvaMask2DActorData& InActorData);` — `UE_DEPRECATED(5.8, "ActorData has been deprecated. TryResolveCanvasTexture with actor data is no longer supported.")`
- L200 _protected prototype_ `UAvaObjectHandleSubsystem* GetObjectHandleSubsystem();` — `UE_DEPRECATED(5.8, "Material Mask Handles have been deprecated. Material Bridge is used instead.")`
- L202 _protected prototype_ `UAvaMaskMaterialInstanceSubsystem* GetMaterialInstanceSubsystem();`
- L208 _protected prototype_ `UGeometryMaskCanvas* GetCurrentCanvas(bool bInResolveCanvas=true);` — Returns or resolves the currently referenced canvas. @param bInResolveCanvas whether to resolve for a new canvas if the cached canvas is not valid
- L211 _protected prototype_ `virtual void OnMaterialsChanged(UObject* InMaterialOwner, const TArray<TSharedPtr<IAvaMaskMaterialHandle>>& InMaterialHandles);` — `UE_DEPRECATED(5.8, "Material Mask Handles have been deprecated. Material Bridge is used instead.")`
- L215 _protected prototype_ `void RestoreActors();` — `UE_DEPRECATED(5.8, "ActorData has been deprecated. Actor restore takes place in the Material Read Modifier directly.")` — Restores modified actors to their original state and clears cache data
- L218 _protected prototype_ `void ResetCanvas();` — Called to reset the canvas. Calls OnCanvasReset
- L221 _protected function_ `virtual void OnCanvasSet(TNotNull<UGeometryMaskCanvas*> InCanvas)` — Called when the canvas has been set
- L226 _protected function_ `virtual void OnCanvasReset()` — Called when the canvas has reset
- L232 _protected prototype_ `void VisualizeMask();` — `UFUNCTION(CallInEditor, Category = "Mask2D")`
- L237 _protected member_ `bool bUseParentChannel = false;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Getter = "UseParentChannel", Setter = "SetUseParentChannel", Category = "Mask2D", meta = (AllowPrivateAccess = "true", ValidEnumValues = "Self,Parent"))` — Whether to get the channel from the parent (first one that specifies a mask channel)
- L241 _protected member_ `FName ParentChannel = NAME_None;` — `UPROPERTY(VisibleAnywhere, Category = "Mask2D", meta = (EditCondition = "bUseParentChannel", EditConditionHides))` — Channel found when GetChannelFromParent is true
- L245 _protected member_ `FName Channel = NAME_None;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Getter, Setter, Category = "Mask2D", meta = (EditCondition = "!bUseParentChannel", EditConditionHides, AllowPrivateAccess = "true"))` — Channel to read to or write from
- L249 _protected member_ `bool bInverted = false;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Getter = "IsInverted", Setter = "SetIsInverted", Category = "Mask2D", meta = (AllowPrivateAccess = "true"))` — Whether to apply the mask as inverted (visible becomes invisible and vice versa)
- L252 _protected member_ `bool bUseBlur = false;` — `UPROPERTY(BlueprintReadWrite, Getter = "UseBlur", Setter = "UseBlur", Category = "Mask2D|Shared", meta = (AllowPrivateAccess = "true"))`
- L255 _protected member_ `float BlurStrength = 16.0f;` — `UPROPERTY(BlueprintReadWrite, Getter, Setter, Category = "Mask2D|Shared", meta = (ClampMin = 0.0, AllowPrivateAccess = "true", EditCondition = "bUseBlur", EditConditionHides))`
- L258 _protected member_ `bool bUseFeathering = false;` — `UPROPERTY(BlueprintReadWrite, Getter = "UseFeathering", Setter = "UseFeathering", Category = "Mask2D|Shared", meta = (AllowPrivateAccess = "true"))`
- L261 _protected member_ `int32 OuterFeatherRadius = 16;` — `UPROPERTY(BlueprintReadWrite, Getter, Setter, Category = "Mask2D|Shared", meta = (ClampMin = 0, AllowPrivateAccess = "true", EditCondition = "bUseFeathering", EditConditionHides))`
- L264 _protected member_ `int32 InnerFeatherRadius = 16;` — `UPROPERTY(BlueprintReadWrite, Getter, Setter, Category = "Mask2D|Shared", meta = (ClampMin = 0, AllowPrivateAccess = "true", EditCondition = "bUseFeathering", EditConditionHides))`
- L268 _protected member_ `TWeakObjectPtr<UAvaObjectHandleSubsystem> ObjectHandleSubsystem;` — `UE_DEPRECATED(5.8, "Material Mask Handles have been deprecated. Material Bridge is used instead.")` — `UPROPERTY(Transient)`
- L271 _protected member_ `TWeakObjectPtr<UAvaMaskMaterialInstanceSubsystem> MaterialInstanceSubsystem;` — `UPROPERTY(Transient)`
- L278 _protected member_ `FName AutoChannelName;` — `UPROPERTY(Transient)` — Cached auto channel name, used when the user adds the modifier and immediately sets the mode to Source, in which case a different channel name is chosen.
- L283 _protected member_ `TMap<TWeakObjectPtr<AActor>, FAvaMask2DActorData> ActorData_DEPRECATED;` — `UE_DEPRECATED(5.8, "ActorData has been deprecated. Material Container State is used instead.")` — `UPROPERTY(NonPIEDuplicateTransient, meta=(DeprecatedProperty))` — Cached actor data to apply/restore
- L287 _protected member_ `FName LastResolvedCanvasName;` — `UPROPERTY(Transient, DuplicateTransient)` — Reference to the last resolved canvas name, as stored in CanvasWeak
- L291 _protected member_ `TWeakObjectPtr<UGeometryMaskCanvas> CanvasWeak;` — `UPROPERTY(EditAnywhere, Transient, DuplicateTransient, Category = "Mask2D|Shared", NoClear, meta = (DisplayName = "Canvas", AllowPrivateAccess = "true", ShowInnerProperties, NoResetToDefault))` — Reference to the Canvas used
- L295 _protected member_ `TMap<TWeakObjectPtr<UObject>, FInstancedStruct> MaterialCollectionHandleData_DEPRECATED;` — `UE_DEPRECATED(5.8, "Material Collection Handles have been deprecated. Material Container State is used instead.")` — `UPROPERTY()`
- L299 _protected member_ `TMap<TWeakObjectPtr<UMaterialInterface>, FInstancedStruct> MaterialHandleData_DEPRECATED;` — `UE_DEPRECATED(5.8, "Material Handles have been deprecated. Material Pre State is used instead.")` — `UPROPERTY(DuplicateTransient)`
- L302 _protected member_ `TMap<TObjectKey<UObject>, TSharedPtr<IAvaMaskMaterialCollectionHandle>> MaterialCollectionHandles;` — `UE_DEPRECATED(5.8, "Material Collection Handles have been deprecated. Material Container State is used instead.")`
- L306 _protected member_ `TSet<TObjectKey<UPrimitiveComponent>> ScannedPrimitiveComponents;` — `UE_DEPRECATED(5.8, "ScannedPrimitiveComponents has been deprecated. Material Container State is used instead.")` — Last scanned primitive components
- L311 _private member_ `static const TAvaPropertyChangeDispatcher<UAvaMask2DBaseModifier> PropertyChangeDispatcher;` — Used for PECP

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API AVALANCHEMASK_API`
- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace Ava` (scope `UE`)

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMask/Public/Mask2D/AvaMask2DMaskState.h` (Public)


#### struct `FAvaMask2DMaskState`  
`struct FAvaMask2DMaskState`  
_L16-37_
- reflection: `USTRUCT()`
- desc: Represents the state for a mask to apply to / restore from a material
- L20 _public prototype_ `FAvaMask2DMaskState() = default;`
- L23 _public prototype_ `void Apply(UMaterialInstanceDynamic* InMaterial) const;` — Applies this state to the given material
- L26 _public prototype_ `void Store(UMaterialInstanceDynamic* InMaterial);` — Stores the given material's mask state
- L30 _public member_ `FAvaMask2DMaterialParameters MaterialParameters;` — `UPROPERTY()` — The material parameters to save / restore
- L35 _public member_ `TObjectPtr<UMaterialFunctionInterface> OutputProcessor;` — `UPROPERTY()` — The output processor was added to the material if material was from material designer

#### struct `FAvaMask2DMaterialSlotId`  
`struct FAvaMask2DMaterialSlotId`  
_L41-65_
- reflection: `USTRUCT()`
- desc: Struct identifying a slot by its slot id and material
- L45 _public prototype_ `FAvaMask2DMaterialSlotId() = default;`
- L47 _public prototype_ `explicit FAvaMask2DMaterialSlotId(FString&& InMaterialContainerPath, const FAvaMaterialBridgeSlotId& InSlotId, const UMaterialInterface* InMaterial);`
- L49 _public prototype_ `bool operator==(const FAvaMask2DMaterialSlotId& InOther) const;`
- L53 _public member_ `FString MaterialContainerPath;` — `UPROPERTY()` — Object containing the material slot
- L57 _public member_ `FAvaMaterialBridgeSlotId SlotId;` — `UPROPERTY()` — The slot id to save / restore the material parameters for
- L64 _public member_ `TObjectPtr<const UMaterial> BaseMaterial;` — `UPROPERTY()` — Base material of the material whose parameter state to save / restore This base is expected to be non-transient.

#### struct `FAvaMask2DMaterialMaskState`  
`struct FAvaMask2DMaterialMaskState`  
_L69-101_
- reflection: `USTRUCT()`
- desc: Represents a material and its mask state
- L73 _public prototype_ `FAvaMask2DMaterialMaskState() = default;`
- L75 _public prototype_ `explicit FAvaMask2DMaterialMaskState(const FAvaMask2DMaterialSlotId& InSlotId);`
- L77 _public prototype_ `bool operator==(const FAvaMask2DMaterialSlotId& InSlotId) const;`
- L80 _public prototype_ `void Apply() const;` — Applies the mask state to the material
- L83 _public prototype_ `void Store();` — Stores the material's mask state
- L86 _public prototype_ `bool IsDependentOf(UMaterialInterface* InMaterial) const;` — Determines whether this material is dependent of the given material interface
- L90 _public member_ `FAvaMask2DMaterialSlotId SlotMaterialId;` — `UPROPERTY()` — The slot id to save / restore the material parameters for
- L94 _public member_ `FAvaMask2DMaskState MaskState;` — `UPROPERTY()` — The mask state of the material
- L97 _public member_ `TWeakObjectPtr<UMaterialInstanceDynamic> MaterialWeak;` — Material instance dynamic assigned for this state
- L100 _public member_ `TWeakObjectPtr<UObject> TopmostMaterialContainer;` — The topmost material containers that this state belongs to

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMask/Public/Mask2D/AvaMask2DReadModifier.h` (Public)


#### class `UAvaMask2DReadModifier`  
`class UAvaMask2DReadModifier : public UAvaMask2DBaseModifier`  
_L42-132_
- reflection: `UCLASS(BlueprintType, MinimalAPI)`
- inherits: `UAvaMask2DBaseModifier`
- desc: Uses scene actors to create a mask texture and applies it to attached actors
- L49 _private member_ `static constexpr int32 MaxCanvasCount = 4;` — Limit canvas count to 4 because a single linear color parameter is used to transmit the indices over.
- L54 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& InPropertyChangedEvent) override;`
- L58 _public function_ `float GetBaseOpacity() const`
- L62 _public prototype_ `void SetBaseOpacity(float InBaseOpacity);`
- L66 _protected prototype_ `virtual bool ForEachUsedCanvasName(TFunctionRef<bool(FName)> InFunc) const override;`
- L70 _protected prototype_ `virtual void OnModifierCDOSetup(FActorModifierCoreMetadata& InMetadata) override;`
- L71 _protected prototype_ `virtual void OnModifierEnabled(EActorModifierCoreEnableReason InReason) override;`
- L72 _protected prototype_ `virtual void OnModifierDisabled(EActorModifierCoreDisableReason InReason) override;`
- L73 _protected prototype_ `virtual void SavePreState() override;`
- L74 _protected prototype_ `virtual void RestorePreState() override;`
- L75 _protected prototype_ `virtual void Apply() override;`
- L79 _protected prototype_ `virtual void OnRenderStateUpdated(AActor* InActor, UActorComponent* InComponent) override;`
- L80 _protected prototype_ `virtual void RemoveFromActor(AActor* InActor) override;`
- L84 _protected prototype_ `EBlendMode GetBlendMode() const;` — Get target blend mode dependent on modifier settings.
- L86 _protected prototype_ `void OnBaseOpacityChanged();`
- L87 _protected prototype_ `void OnAdditionalChannelsChanged();`
- L90 _protected prototype_ `virtual void SetupMaskComponent(UActorComponent* InComponent) override;` — `UE_DEPRECATED(5.8, "SetupMaskReadComponent is deprecated. Mask Read Modifier no longer allocates a component")`
- L93 _protected prototype_ `void SetupMaskReadComponent(IGeometryMaskReadInterface* InMaskReader);` — `UE_DEPRECATED(5.8, "SetupMaskReadComponent is deprecated. Mask Read Modifier no longer allocates a component")`
- L95 _protected prototype_ `bool ApplyRead(TNotNull<UObject*> InMaterialContainer, TConstArrayView<TNotNull<const UGeometryMaskCanvas*>> InCanvases);`
- L97 _protected prototype_ `bool ApplyMaskState(const UE::Ava::FMaterialBridgeWriteSlotContext& InContext, UE::Ava::FMaterialBridgeWriteSlot& InSlot, const FAvaMask2DMaskState& InMaskState);`
- L100 _protected prototype_ `bool ApplyRead(AActor* InActor, FAvaMask2DActorData& InActorData);` — `UE_DEPRECATED(5.8, "Use ApplyRead that takes in an array of canvas instead")`
- L103 _protected prototype_ `bool ApplyRead(AActor* InActor, FAvaMask2DActorData& InActorData, FText& OutFailReason);` — `UE_DEPRECATED(5.8, "Use ApplyRead that takes in an array of canvas instead")`
- L106 _protected prototype_ `void StoreActorState(AActor* InActor);` — Stores the container and material states for a given actor
- L110 _protected member_ `TArray<FName> AdditionalChannels;` — `UPROPERTY(EditInstanceOnly, Category = "Mask2D", meta = (AllowPrivateAccess = "true", DisplayAfter="Channel"))` — Additional channels to read from
- L114 _protected member_ `float BaseOpacity = 0.0f;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Getter, Setter, Category = "Mask2D", meta = (ClampMin = 0.0, ClampMax = 1.0, AllowPrivateAccess = "true"))` — Base opacity/alpha to use in Read mode
- L118 _protected member_ `TMap<TObjectPtr<UObject>, TInstancedStruct<FAvaMaterialContainerState>> MaterialContainerStates;` — `UPROPERTY(NonPIEDuplicateTransient)` — The state of the actors to their material containers to save / restore
- L122 _protected member_ `TArray<FAvaMask2DMaterialMaskState> MaterialStates;` — `UPROPERTY(NonPIEDuplicateTransient)` — State of the materials to save/restore
- L127 _private member_ `static const TAvaPropertyChangeDispatcher<UAvaMask2DReadModifier> PropertyChangeDispatcher;` — Used for PECP
- L129 _private prototype_ `void OnMaterialCompiled(UMaterialInterface* InMaterial);`
- L130 _private prototype_ `void OnPIEEnded(bool bInIsSimulating);`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API AVALANCHEMASK_API`
- L34 _namespace_ `namespace UE`
- L34 _namespace_ `namespace Ava` (scope `UE`)

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMask/Public/Mask2D/AvaMask2DWriteModifier.h` (Public)


#### class `UAvaMask2DWriteModifier`  
`class UAvaMask2DWriteModifier : public UAvaMask2DBaseModifier, public IGeometryMaskWriteInterface`  
_L43-117_
- reflection: `UCLASS(BlueprintType)`
- inherits: `UAvaMask2DBaseModifier,IGeometryMaskWriteInterface`
- desc: Uses scene actors to create a mask texture and applies it to attached actors
- L50 _public prototype_ `UAvaMask2DWriteModifier();`
- L52 _public function_ `EGeometryMaskCompositeOperation GetWriteOperation() const`
- L56 _public prototype_ `void SetWriteOperation(const EGeometryMaskCompositeOperation InWriteOperation);`
- L61 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& InPropertyChangedEvent) override;`
- L66 _protected prototype_ `virtual void OnModifierCDOSetup(FActorModifierCoreMetadata& InMetadata) override;`
- L67 _protected prototype_ `virtual void OnModifierEnabled(EActorModifierCoreEnableReason InReason) override;`
- L68 _protected prototype_ `virtual void OnModifierDisabled(EActorModifierCoreDisableReason InReason) override;`
- L69 _protected prototype_ `virtual void Apply() override;`
- L73 _protected prototype_ `virtual void OnRenderStateUpdated(AActor* InActor, UActorComponent* InComponent) override;`
- L74 _protected prototype_ `virtual void SetupMaskComponent(UActorComponent* InComponent) override;`
- L75 _protected prototype_ `virtual void OnCanvasSet(TNotNull<UGeometryMaskCanvas*> InCanvas) override;`
- L76 _protected prototype_ `virtual void OnCanvasReset() override;`
- L77 _protected prototype_ `virtual void RemoveFromActor(AActor* InActor) override;`
- L81 _protected prototype_ `virtual bool IsMaskWriterEnabled() const override;`
- L82 _protected prototype_ `virtual const FGeometryMaskWriteParameters& GetParameters() const override;`
- L83 _protected prototype_ `virtual void SetParameters(FGeometryMaskWriteParameters& InParameters) override;`
- L84 _protected prototype_ `virtual void DrawToCanvas(FCanvas* InCanvas) override;`
- L85 _protected prototype_ `virtual FOnGeometryMaskSetCanvasNativeDelegate& OnSetCanvas() override;`
- L86 _protected prototype_ `virtual UE::GeometryMask::FMaskWriter* GetMaskWriter() override;`
- L89 _protected prototype_ `void OnWriteOperationChanged();`
- L90 _protected prototype_ `void SetupMaskWriteComponent(IGeometryMaskWriteInterface* InMaskWriter);`
- L92 _protected prototype_ `bool ApplyWrite(TNotNull<AActor*> InActor);`
- L95 _protected prototype_ `bool ApplyWrite(AActor* InActor, FAvaMask2DActorData& InActorData);` — `UE_DEPRECATED(5.8, "Actor data has been deprecated. Use the overload that takes in an actor only")`
- L99 _protected member_ `EGeometryMaskCompositeOperation WriteOperation = EGeometryMaskCompositeOperation::Add;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Getter, Setter, Category = "Mask2D", meta = (ValidEnumValues = "Add, Subtract", AllowPrivateAccess = "true"))` — How to write to the chosen mask channel
- L103 _protected member_ `TArray<TObjectPtr<AActor>> MaskActors;` — `UPROPERTY(Transient, DuplicateTransient)` — Actors to get the components to mask with
- L106 _protected member_ `TSharedPtr<UE::GeometryMask::FMaskWriter> MaskWriter;` — Object handling masking and component caching
- L109 _protected member_ `FGeometryMaskWriteParameters Parameters;` — `UPROPERTY(Transient, DuplicateTransient)`
- L111 _protected member_ `FOnGeometryMaskSetCanvasNativeDelegate OnSetCanvasDelegate;`
- L115 _protected member_ `static const TAvaPropertyChangeDispatcher<UAvaMask2DWriteModifier> PropertyChangeDispatcher;` — Used for PECP

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API AVALANCHEMASK_API`
- L36 _namespace_ `namespace UE`
- L36 _namespace_ `namespace GeometryMask` (scope `UE`)
