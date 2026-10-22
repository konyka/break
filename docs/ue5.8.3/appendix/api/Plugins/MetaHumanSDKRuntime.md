# Plugins / MetaHumanSDKRuntime

- module root: `Plugins/MetaHuman/MetaHumanSDK/Source/MetaHumanSDKRuntime`
- headers: 5; symbols: 104
- symbol kinds: class=3, enum=5, enumerator=53, function=2, macro=2, member=18, namespace=1, prototype=19, struct=1
- PrivateDependencyModuleNames: AnimGraphRuntime, AnimationCore, ControlRig, CoreUObject, Engine, RigVM, Slate, SlateCore
- PublicDependencyModuleNames: Core

### `Plugins/MetaHuman/MetaHumanSDK/Source/MetaHumanSDKRuntime/Public/MetaHumanBodyType.h` (Public)


#### enum `EMetaHumanBodyType`  
`enum class EMetaHumanBodyType : uint8`  
_L10-32_
- reflection: `UENUM()`
- L12 _public enumerator_ `f_med_nrw = 0`
- L13 _public enumerator_ `f_med_ovw`
- L14 _public enumerator_ `f_med_unw`
- L15 _public enumerator_ `f_srt_nrw`
- L16 _public enumerator_ `f_srt_ovw`
- L17 _public enumerator_ `f_srt_unw`
- L18 _public enumerator_ `f_tal_nrw`
- L19 _public enumerator_ `f_tal_ovw`
- L20 _public enumerator_ `f_tal_unw`
- L21 _public enumerator_ `m_med_nrw`
- L22 _public enumerator_ `m_med_ovw`
- L23 _public enumerator_ `m_med_unw`
- L24 _public enumerator_ `m_srt_nrw`
- L25 _public enumerator_ `m_srt_ovw`
- L26 _public enumerator_ `m_srt_unw`
- L27 _public enumerator_ `m_tal_nrw`
- L28 _public enumerator_ `m_tal_ovw`
- L29 _public enumerator_ `m_tal_unw`
- L30 _public enumerator_ `BlendableBody` — This is not required for CharacterBodyIdentity initialization. Keep it as last entry on enum list (before Count)
- L31 _public enumerator_ `Count UMETA(Hidden)`

#### enum `EMetaHumanBodyBodyPartIndex`  
`enum class EMetaHumanBodyBodyPartIndex : uint32`  
_L36-44_
- reflection: `UENUM()`
- L38 _public enumerator_ `Body = 0`
- L39 _public enumerator_ `Face`
- L40 _public enumerator_ `Torso`
- L41 _public enumerator_ `Legs`
- L42 _public enumerator_ `Feet`
- L43 _public enumerator_ `Count UMETA(Hidden)`

#### Free symbols / members of external scopes

- L33 _prototype_ `ENUM_RANGE_BY_COUNT(EMetaHumanBodyType, EMetaHumanBodyType::Count);`

### `Plugins/MetaHuman/MetaHumanSDK/Source/MetaHumanSDKRuntime/Public/MetaHumanComponentBase.h` (Public)


#### struct `FMetaHumanCustomizableBodyPart`  
`struct FMetaHumanCustomizableBodyPart`  
_L47-75_
- reflection: `USTRUCT()`
- L53 _public member_ `TSubclassOf<UControlRig> ControlRigClass;` — `UPROPERTY(EditDefaultsOnly, Category = BodyParts, meta = (DisallowCreateNew))` — Control rig to run on the body part. Evaluation happens after the base skeleton.
- L60 _public member_ `int32 ControlRigLODThreshold = INDEX_NONE;` — `UPROPERTY(EditDefaultsOnly, Category = BodyParts, meta = (EditCondition = "ControlRigClass != nullptr", EditConditionHides))` — Max LOD level to evaluate the assigned control rig for the body part. For example if you have the threshold set to 2, the control rig will be evaluated for LOD 0, 1, and 2. Setting it to -1 will always evaluate it and disable LODing.
- L64 _public member_ `TObjectPtr<UPhysicsAsset> PhysicsAsset;` — `UPROPERTY(EditDefaultsOnly, Category = BodyParts)` — Physics asset used for rigid body simulation on the body part. Evaluation happens after the base skeleton.
- L71 _public member_ `int32 RigidBodyLODThreshold = INDEX_NONE;` — `UPROPERTY(EditDefaultsOnly, Category = BodyParts, meta = (EditCondition = "PhysicsAsset != nullptr", EditConditionHides))` — Max LOD level to simulate the rigid bodies of the assigned physics asset. For example if you have the threshold set to 2, simulation will be enabled for LOD 0, 1, and 2. Setting it to -1 will make it simulate always and disable LODing.
- L74 _public member_ `FString ComponentName;` — `UPROPERTY(EditDefaultsOnly, Category = BodyParts, AdvancedDisplay)`

#### class `UMetaHumanComponentBase`  
`class UMetaHumanComponentBase : public UActorComponent`  
_L78-179_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UActorComponent`
- L84 _protected prototype_ `UMetaHumanComponentBase();`
- L87 _protected prototype_ `USkeletalMeshComponent* GetSkelMeshComponentByName(const FString& ComponentName) const;` — Get the first skeletal mesh component with the given name from the owning actor.
- L90 _protected prototype_ `USkeletalMeshComponent* GetBodySkelMeshComponent() const;` — Get skeletal mesh component for the Body (based on the specified name) of the owning actor.
- L93 _protected prototype_ `void RunAndInitPostAnimBP(USkeletalMeshComponent* SkelMeshComponent, TSubclassOf<UAnimInstance> AnimInstance, bool bRunAsOverridePostAnimBP, bool bReinitAnimInstances = true) const;` — Run the given AnimBP either on the skeletal mesh asset or on the instance, the component and initialize it afterwards.
- L96 _protected prototype_ `void LoadAndRunAnimBP(TSoftClassPtr<UAnimInstance> AnimBlueprint, TWeakObjectPtr<USkeletalMeshComponent> SkelMeshComponent, bool bIsPostProcessingAnimBP, bool bRunAsOverridePostAnimBP = false);` — Load and run AnimBP on the given skeletal mesh component.
- L99 _protected prototype_ `virtual void PostInitAnimBP(USkeletalMeshComponent* SkeletalMeshComponent, UAnimInstance* AnimInstance) const;` — Post-loading callback to be used to connect AnimBP variables.
- L101 _protected prototype_ `void PostConnectAnimBPVariables(const FMetaHumanCustomizableBodyPart& BodyPart, USkeletalMeshComponent* SkeletalMeshComponent, UAnimInstance* AnimInstance) const;`
- L106 _protected prototype_ `void SetFollowBody(USkeletalMeshComponent* SkelMeshComponent) const;`
- L109 _protected member_ `FString BodyComponentName = "Bo` — `UPROPERTY(EditDefaultsOnly, Category = Body, AdvancedDisplay)`
- L112 _protected member_ `EMetaHumanBodyType BodyType = EMetaHumanBodyType::BlendableBody;` — `UPROPERTY()`
- L120 _protected member_ `bool bEnableBodyCorrectives = true;` — `UPROPERTY(EditDefaultsOnly, Category = Body)` — Enable evaluation of the body procedural control rig, the head movement IK control rig and the arm and finger pose drivers. When enabled, evaluation for LODs can still be controlled via the Body LOD threshold. When disabled, the body procedural control rig, the head movement IK control rig and the arm and finger pose drivers will not be evaluated which will result in higher performance but decreases mesh deformation quality.
- L126 _protected member_ `FString FaceComponentName = "Fa` — `UPROPERTY(EditDefaultsOnly, Category = Face, AdvancedDisplay)`
- L134 _protected member_ `int32 RigLogicLODThreshold = INDEX_NONE;` — `UPROPERTY(EditDefaultsOnly, Category = Face, meta = (DisplayName = "Facial Animation LOD Threshold"))` — Max LOD level where Rig Logic is evaluated. For example if you have the threshold set to 2, it will evaluate until including LOD 2 (based on 0 index). In case the LOD level gets set to 3, it will stop evaluating Rig Logic. Setting it to -1 will always evaluate it and disable LODing.
- L142 _protected member_ `bool bEnableNeckCorrectives = true;` — `UPROPERTY(EditDefaultsOnly, Category = Face, meta = (EditCondition = "BodyType!=EMetaHumanBodyType::BlendableBody", EditConditionHides))` — Enable evaluation of neck correctives. When enabled, evaluation for LODs can still be controlled via the LOD threshold. When disabled, neck correctives will not be evaluated which will result in higher performance but decreases mesh deformation quality.
- L150 _protected member_ `int32 NeckCorrectivesLODThreshold = INDEX_NONE;` — `UPROPERTY(EditDefaultsOnly, Category = Face, meta = (EditCondition = "bEnableNeckCorrectives==true && BodyType!=EMetaHumanBodyType::BlendableBody", EditConditionHides))` — Max LOD level where neck correctives (pose drivers) are evaluated. For example if you have the threshold set to 2, it will evaluate until including LOD 2 (based on 0 index). In case the LOD level gets set to 3, it will stop evaluating neck correctives. Setting it to -1 will always evaluate it and disable LODing.
- L158 _protected member_ `bool bEnableNeckProcControlRig = true;` — `UPROPERTY(EditDefaultsOnly, Category = Face, meta = (EditCondition = "BodyType!=EMetaHumanBodyType::BlendableBody", EditConditionHides))` — Enable evaluation of the neck procedural control rig. When enabled, evaluation for LODs can still be controlled via the LOD threshold. When disabled, the neck procedural control rig will not be evaluated which will result in higher performance but decreases mesh deformation quality.
- L166 _protected member_ `int32 NeckProcControlRigLODThreshold = INDEX_NONE;` — `UPROPERTY(EditDefaultsOnly, Category = Face, meta = (EditCondition = "bEnableNeckProcControlRig==true && BodyType!=EMetaHumanBodyType::BlendableBody", EditConditionHides))` — Max LOD level where the neck procedural control rig is evaluated. For example if you have the threshold set to 2, it will evaluate until including LOD 2 (based on 0 index). In case the LOD level gets set to 3, it will stop evaluating the neck procedural control rig. Setting it to -1 will always evaluate it and disable LODing.
- L172 _protected member_ `FMetaHumanCustomizableBodyPart Torso;` — `UPROPERTY(EditAnywhere, Category = BodyParts)`
- L175 _protected member_ `FMetaHumanCustomizableBodyPart Legs;` — `UPROPERTY(EditAnywhere, Category = BodyParts)`
- L178 _protected member_ `FMetaHumanCustomizableBodyPart Feet;` — `UPROPERTY(EditAnywhere, Category = BodyParts)`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API METAHUMANSDKRUNTIME_API`
- L19 _namespace_ `namespace MetaHumanComponentHelpers`
- L22 _function_ `template <typename PropertyBPType, typename PropertyVarType> void ConnectVariable(UAnimInstance* AnimInstance, const FName& InIdentifier, const PropertyVarType& InVar)` (scope `MetaHumanComponentHelpers`)
- L35 _function_ `template<typename T> static bool GetPropertyValue(UObject* InObject, FStringView InPropertyName, T& OutPropertyValue)` (scope `MetaHumanComponentHelpers`)

### `Plugins/MetaHuman/MetaHumanSDK/Source/MetaHumanSDKRuntime/Public/MetaHumanComponentUE.h` (Public)


#### class `UMetaHumanComponentUE`  
`class UMetaHumanComponentUE : public UMetaHumanComponentBase`  
_L12-35_
- reflection: `UCLASS(MinimalAPI, Blueprintable, ClassGroup = "Animation", HideCategories = (Navigation, Variable, Sockets, Tags, Activation, Cooking, Events, ComponentTick, ComponentReplication, AssetUserData, Replication), meta = (BlueprintSpawnableComponent, DisplayName = "MetaHuman Component"))`
- inherits: `UMetaHumanComponentBase`
- L19 _public prototype_ `virtual void OnRegister() override;` — UActorComponent interface
- L20 _public prototype_ `virtual void OnUnregister() override;`
- L21 _public prototype_ `virtual void BeginPlay() override;`
- L25 _private prototype_ `void SetupCustomizableBodyPart(FMetaHumanCustomizableBodyPart& BodyPart);`
- L26 _private prototype_ `virtual void PostInitAnimBP(USkeletalMeshComponent* SkeletalMeshComponent, UAnimInstance* AnimInstance) const override final;`
- L34 _private member_ `TSoftClassPtr<UAnimInstance> PostProcessAnimBP;` — `UPROPERTY(EditDefaultsOnly, Category = BodyParts)` — The post-processing AnimBP to use for the body parts when either the physics asset or the control rig are set. Use the ABP_Clothing_PostProcess shipped along with MetaHumans. The MetaHuman component will control given variables to e.g. set the LOD thresholds.

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API METAHUMANSDKRUNTIME_API`

### `Plugins/MetaHuman/MetaHumanSDK/Source/MetaHumanSDKRuntime/Public/MetaHumanSDKRuntime.h` (Public)


#### class `FMetaHumanSDKRuntimeModule`  
`class FMetaHumanSDKRuntimeModule : public IModuleInterface`  
_L8-15_
- inherits: `IModuleInterface`
- L13 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L14 _public prototype_ `virtual void ShutdownModule() override;`

### `Plugins/MetaHuman/MetaHumanSDK/Source/MetaHumanSDKRuntime/Public/MetaHumanTypes.h` (Public)


#### enum `EFaceTextureType`  
`enum class EFaceTextureType : uint8`  
_L15-30_
- reflection: `UENUM()`
- desc: This enum defines the Texture objects stored in a MetaHumanCharacter by indexing the SynthesizedFaceTextures array. The values match the names of the material slots for the MetaHumanCharacter Editable preview material, and correspond to the expected outputs of the TS model in the TitanLib module.
- L17 _public enumerator_ `Basecolor = 0 UMETA(DisplayName = "Base Color")`
- L18 _public enumerator_ `Basecolor_Animated_CM1 UMETA(DisplayName = "Base Color Animated CM1")`
- L19 _public enumerator_ `Basecolor_Animated_CM2 UMETA(DisplayName = "Base Color Animated CM2")`
- L20 _public enumerator_ `Basecolor_Animated_CM3 UMETA(DisplayName = "Base Color Animated CM3")`
- L22 _public enumerator_ `Normal`
- L23 _public enumerator_ `Normal_Animated_WM1 UMETA(DisplayName = "Normal Animated WM1")`
- L24 _public enumerator_ `Normal_Animated_WM2 UMETA(DisplayName = "Normal Animated WM2")`
- L25 _public enumerator_ `Normal_Animated_WM3 UMETA(DisplayName = "Normal Animated WM3")`
- L27 _public enumerator_ `Cavity`
- L29 _public enumerator_ `Count UMETA(Hidden)`

#### enum `EBodyTextureType`  
`enum class EBodyTextureType : uint8`  
_L34-49_
- reflection: `UENUM()`
- L36 _public enumerator_ `Body_Basecolor = 0 UMETA(DisplayName = "Body Base Color")`
- L37 _public enumerator_ `Body_Normal UMETA(DisplayName = "Body Normal")`
- L38 _public enumerator_ `Body_Cavity UMETA(DisplayName = "Body Cavity")`
- L39 _public enumerator_ `Body_Underwear_Basecolor UMETA(DisplayName = "Body Underwear Base Color")`
- L40 _public enumerator_ `Body_Underwear_Normal UMETA(DisplayName = "Body Underwear Normal")`
- L41 _public enumerator_ `Body_Underwear_Mask UMETA(DisplayName = "Body Underwear Mask")`
- L42 _public enumerator_ `Chest_Basecolor UMETA(DisplayName = "Chest Base Color")`
- L43 _public enumerator_ `Chest_Normal UMETA(DisplayName = "Chest Normal")`
- L44 _public enumerator_ `Chest_Cavity UMETA(DisplayName = "Chest Cavity")`
- L45 _public enumerator_ `Chest_Underwear_Basecolor UMETA(DisplayName = "Chest Underwear Base Color")`
- L46 _public enumerator_ `Chest_Underwear_Normal UMETA(DisplayName = "Chest Underwear Normal")`
- L48 _public enumerator_ `Count UMETA(Hidden)`

#### enum `EMetaHumanQualityLevel`  
`enum class EMetaHumanQualityLevel : uint8`  
_L53-61_
- reflection: `UENUM()`
- L55 _public enumerator_ `Low`
- L56 _public enumerator_ `Medium`
- L57 _public enumerator_ `High`
- L58 _public enumerator_ `Cinematic`
- L60 _public enumerator_ `Count UMETA(Hidden)`

#### Free symbols / members of external scopes

- L31 _prototype_ `ENUM_RANGE_BY_COUNT(EFaceTextureType, EFaceTextureType::Count);`
- L50 _prototype_ `ENUM_RANGE_BY_COUNT(EBodyTextureType, EBodyTextureType::Count);`
- L62 _prototype_ `ENUM_RANGE_BY_COUNT(EMetaHumanQualityLevel, EMetaHumanQualityLevel::Count);`
