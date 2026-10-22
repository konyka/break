# Plugins / NaniteAssemblyEditorUtils

- module root: `Plugins/Experimental/NaniteAssemblyEditorUtils/Source/NaniteAssemblyEditorUtils`
- headers: 4; symbols: 71
- symbol kinds: class=4, delegate=1, enum=1, enumerator=3, function=11, member=16, prototype=31, struct=4
- DynamicallyLoadedModuleNames: AssetTools
- PrivateDependencyModuleNames: Core, CoreUObject, Engine, Renderer, UnrealEd
- PrivateIncludePathModuleNames: AssetTools

### `Plugins/Experimental/NaniteAssemblyEditorUtils/Source/NaniteAssemblyEditorUtils/Public/NaniteAssemblyBuilder.h` (Public)


#### enum `ENaniteAssemblyPartMaterialMerge`  
`enum class ENaniteAssemblyPartMaterialMerge : uint8`  
_L11-28_
- reflection: `UENUM(BlueprintType)`
- L17 _public enumerator_ `MergeIdenticalMaterials` — Will remap the part mesh's material slots to material slots with identical materials and will only create new material slots for those that are unmatched.
- L22 _public enumerator_ `MergeIdenticalSlotNames` — Will remap the part mesh's material slots to material slots with identical slot names and will only create new material slots for those that are unmatched.
- L27 _public enumerator_ `MergeMaterialIndices` — Will remap the part mesh's material slots to material slots in the group by their index, and will only create new slots if the part mesh has more materials than is currently in the slot group.

#### struct `FNaniteAssemblyMaterialMergeOptions`  
`struct FNaniteAssemblyMaterialMergeOptions`  
_L31-53_
- reflection: `USTRUCT(BlueprintType)`
- L37 _public member_ `int32 MaterialSlotGroup = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)` — The material slot group index. Only use 0, or values provided by `AddMaterialSlotGroup` on the Nanite Assembly Builder.
- L41 _public member_ `ENaniteAssemblyPartMaterialMerge MergeBehavior = ENaniteAssemblyPartMaterialMerge::MergeIdenticalMaterials;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)` — Specifies how to merge the materials within the material slot group.
- L45 _public member_ `TArray<TObjectPtr<UMaterialInterface>> MaterialOverrides;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)` — (Optional) An array of material overrides to use.
- L47 _public function_ `bool operator==(const FNaniteAssemblyMaterialMergeOptions& Other)`

#### struct `FNaniteAssemblyCreateNewParameters`  
`struct FNaniteAssemblyCreateNewParameters`  
_L56-74_
- reflection: `USTRUCT(BlueprintType)`
- L62 _public member_ `FDirectoryPath TargetDirectory;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default, meta = (RelativePath, ContentDir))` — The content directory in which to store the new mesh asset
- L69 _public member_ `FString AssetName;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)` — The desired name of the new asset. NOTE: Will be amended if bOverwriteExisting=false
- L73 _public member_ `bool bOverwriteExisting = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)` — Whether or not to overwrite the asset if it already exists

#### struct `FNaniteAssemblySkeletalMeshPartBinding`  
`struct FNaniteAssemblySkeletalMeshPartBinding`  
_L77-92_
- reflection: `USTRUCT(BlueprintType)`
- L83 _public member_ `TArray<FNaniteAssemblyBoneInfluence> BoneInfluences;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)` — The bone influences and their weights for the binding.
- L87 _public member_ `FTransform Transform;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)` — The transform of the binding.
- L91 _public member_ `ENaniteAssemblyNodeTransformSpace TransformSpace = ENaniteAssemblyNodeTransformSpace::Local;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)` — Identifies the space to treat `Transform` as being in.

#### class `UNaniteAssemblyBuilder`  
`class UNaniteAssemblyBuilder : public UObject`  
_L95-177_
- reflection: `UCLASS(Abstract)`
- inherits: `UObject`
- L100 _public prototype_ `UNaniteAssemblyBuilder(const FObjectInitializer& Initializer);`
- L105 _public function_ `virtual UObject* GetTargetMeshObject() const PURE_VIRTUAL(UNaniteAssemblyBuilder::GetTargetMeshObject, return nullptr;) UFUNCTION(BlueprintCallable, Category = Default) bool IsBuildingAssembly() const` — `UFUNCTION(BlueprintCallable, Category = Default)` — Retrieves the target object of the current assembly build
- L116 _public function_ `int32 AddMaterialSlotGroup()` — `UFUNCTION(BlueprintCallable, Category = "Materials")` — Creates a new material slot group on the builder, which allows you to be selective about which assembly parts' materials can be merged together. Use the return value when adding a part to the assembly.
- L123 _public prototype_ `int32 AddMaterialSlot(UMaterialInterface* Material, int32 MaterialSlotGroup = 0, FName SlotName = NAME_None);` — `UFUNCTION(BlueprintCallable, Category = "Materials")` — Creates a material slot in the specified material slot group with a given material. If the slot name provided is "None", the resulting material slot will take the name of the material.
- L133 _protected prototype_ `void Reset();`
- L135 _protected prototype_ `FAddPartsResult FindOrAddPartMesh(FSoftObjectPath MeshObjectPath, const FNaniteAssemblyMaterialMergeOptions& MaterialMergeOptions);`
- L137 _protected prototype_ `FAddPartsResult AddParts( FSoftObjectPath MeshObjectPath, TArrayView<const FTransform> LocalTransforms, const FNaniteAssemblyMaterialMergeOptions& MaterialMergeOptions );`
- L143 _protected prototype_ `FAddPartsResult AddParts( FSoftObjectPath MeshObjectPath, TArrayView<const FNaniteAssemblySkeletalMeshPartBinding> Bindings, const FNaniteAssemblyMaterialMergeOptions& MaterialMergeOptions );`
- L149 _protected prototype_ `int32 MergeMaterialSlot( int32 SourceSlotIndex, const FNaniteAssemblyDataBuilder::FMaterialSlot& Slot, ENaniteAssemblyPartMaterialMerge MergeOption );`
- L155 _protected prototype_ `bool ValidateBuildStatus(const TCHAR* Label, bool bExpectedIsBuilding) const;`
- L157 _protected prototype_ `template <typename TMesh> bool ValidateCandidatePartMesh(const TMesh* Mesh) const;`
- L159 _protected prototype_ `static UObject* CreateNewMeshForAssemblyBuild( const FNaniteAssemblyCreateNewParameters& Parameters, const UClass* Class, const UObject* ObjectToDuplicate = nullptr );`
- L165 _protected function_ `template <typename TMesh> static TMesh* CreateNewMeshForAssemblyBuild( const FNaniteAssemblyCreateNewParameters& Parameters, const TMesh* ObjectToDuplicate = nullptr )`
- L174 _protected member_ `FNaniteAssemblyDataBuilder Builder;`
- L176 _protected member_ `TArray<FNaniteAssemblyMaterialMergeOptions> PartMaterialMergeOptions;` — `UPROPERTY(Transient)`
- L180 _function_ `template <typename TMesh> bool UNaniteAssemblyBuilder::ValidateCandidatePartMesh(const TMesh* PartMesh) const`

#### struct `UNaniteAssemblyBuilder::FAddPartsResult`  
`struct FAddPartsResult`  
_L126-131_
- L128 _public member_ `int32 PartIndex;`
- L129 _public member_ `int32 FirstNodeIndex;`
- L130 _public member_ `bool bNewPart;`

### `Plugins/Experimental/NaniteAssemblyEditorUtils/Source/NaniteAssemblyEditorUtils/Public/NaniteAssemblyEditorUtilsModule.h` (Public)


#### class `FNaniteAssemblyEditorUtilsModule`  
`class FNaniteAssemblyEditorUtilsModule : public IModuleInterface`  
_L11-22_
- inherits: `IModuleInterface`
- L15 _public prototype_ `virtual void StartupModule() override;`
- L16 _public prototype_ `virtual void ShutdownModule() override;`
- L18 _public prototype_ `static FNaniteAssemblyEditorUtilsModule& GetModule();`

#### Free symbols / members of external scopes

- L9 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogNaniteAssemblyBuilder, Log, All);`
- L9 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogNaniteAssemblyBuilder, Log, All);`

### `Plugins/Experimental/NaniteAssemblyEditorUtils/Source/NaniteAssemblyEditorUtils/Public/NaniteAssemblySkeletalMeshBuilder.h` (Public)


#### class `UNaniteAssemblySkeletalMeshBuilder`  
`class UNaniteAssemblySkeletalMeshBuilder : public UNaniteAssemblyBuilder`  
_L14-112_
- reflection: `UCLASS(BlueprintType)`
- inherits: `UNaniteAssemblyBuilder`
- L19 _public prototype_ `UNaniteAssemblySkeletalMeshBuilder(const FObjectInitializer& Initializer);`
- L21 _public function_ `virtual UObject* GetTargetMeshObject() const override`
- L28 _public prototype_ `static UNaniteAssemblySkeletalMeshBuilder* BeginNewSkeletalMeshAssemblyBuild( const FNaniteAssemblyCreateNewParameters& Parameters, const USkeletalMesh* BaseMesh );` — `UFUNCTION(BlueprintCallable, Category = "Skeletal Mesh")` — Creates a Nanite Assembly Skeletal Mesh builder to generate a new Skeletal Mesh asset. Requires a base mesh with a valid skeleton to be duplicated for the base mesh.
- L38 _public prototype_ `static UNaniteAssemblySkeletalMeshBuilder* BeginEditSkeletalMeshAssemblyBuild(USkeletalMesh* BaseMesh);` — `UFUNCTION(BlueprintCallable, Category = "Skeletal Mesh")` — Creates a Nanite Assembly Skeletal Mesh builder to add assembly parts to the specified Skeletal Mesh, or overwrite its assembly parts if it is an existing Nanite Assembly mesh.
- L40 _public prototype_ `bool BeginAssemblyBuild(USkeletalMesh* InTargetMesh);`
- L44 _public prototype_ `bool FinishAssemblyBuild(USkeletalMesh*& OutSkeletalMesh);` — `UFUNCTION(BlueprintCallable, Category = "Skeletal Mesh", meta = ( ReturnDisplayName = "Success" ))` — Finalizes the assembly build and returns the finished assembly mesh.
- L46 _public prototype_ `bool AddAssemblyParts( const USkeletalMesh* PartMesh, TArrayView<const FNaniteAssemblySkeletalMeshPartBinding> Bindings, const FNaniteAssemblyMaterialMergeOptions& MaterialMergeOptions = FNaniteAssemblyMaterialMergeOptions() );`
- L54 _public function_ `bool AddAssemblyParts( const USkeletalMesh* PartMesh, const TArray<FNaniteAssemblySkeletalMeshPartBinding>& Bindings, const FNaniteAssemblyMaterialMergeOptions& MaterialMergeOptions = FNaniteAssemblyMaterialMergeOptions() )` — `UFUNCTION(BlueprintCallable, Category = "Assembly Parts", meta = ( ReturnDisplayName = "Success", AutoCreateRefTerm = "MaterialMergeOptions" ))` — Adds instances of the specified mesh to the assembly with the specified bindings
- L65 _public function_ `bool AddAssemblyPart( const USkeletalMesh* PartMesh, const FNaniteAssemblySkeletalMeshPartBinding& Binding, const FNaniteAssemblyMaterialMergeOptions& MaterialMergeOptions = FNaniteAssemblyMaterialMergeOptions() )` — `UFUNCTION(BlueprintCallable, Category = "Assembly Parts", meta = ( ReturnDisplayName = "Success", AutoCreateRefTerm = "MaterialMergeOptions" ))` — Adds an instance of the specified mesh to the assembly with the specified binding
- L79 _public prototype_ `bool CreateBindingByBoneName( FNaniteAssemblySkeletalMeshPartBinding& OutBinding, FName BoneName, float Weight = 1.0f, const FTransform& Transform = FTransform(), ENaniteAssemblyNodeTransformSpace TransformSpace = ENaniteAssemblyNodeTransformSpace::BoneRelative );` — `UFUNCTION(BlueprintCallable, Category = Default, meta = ( ReturnDisplayName = "Success", AutoCreateRefTerm = "Transform" ))` — Attempts to create a new skeletal mesh part binding from the specified bone's name. For multiple bone influence, use `AddBoneInfluenceByName` for each additional bone.
- L92 _public prototype_ `bool CreateBindingBySocketName( FNaniteAssemblySkeletalMeshPartBinding& OutBinding, FName SocketName, const FTransform& Transform = FTransform(), ENaniteAssemblyNodeTransformSpace TransformSpace = ENaniteAssemblyNodeTransformSpace::BoneRelative);` — `UFUNCTION(BlueprintCallable, Category = Default, meta = ( ReturnDisplayName = "Success", AutoCreateRefTerm = "Transform" ))` — Attempts to create a new skeletal mesh part binding from a socket's name. WARNING: Don't add additional bone influences to the binding when creating from a socket, or the attachment won't look right.
- L100 _public prototype_ `bool AddBoneInfluenceByName( UPARAM(ref) FNaniteAssemblySkeletalMeshPartBinding& Binding, FName BoneName, float Weight = 1.0f );` — `UFUNCTION(BlueprintCallable, Category = Default, meta = ( ReturnDisplayName = "Success" ))` — Attempts to add a bone influence to a skeletal mesh binding based on the bone's name.
- L107 _private prototype_ `bool ValidateBindings(TArrayView<const FNaniteAssemblySkeletalMeshPartBinding> Bindings) const;`
- L111 _private member_ `TObjectPtr<USkeletalMesh> TargetMesh;` — `UPROPERTY(Transient)`

### `Plugins/Experimental/NaniteAssemblyEditorUtils/Source/NaniteAssemblyEditorUtils/Public/NaniteAssemblyStaticMeshBuilder.h` (Public)


#### class `UNaniteAssemblyStaticMeshBuilder`  
`class UNaniteAssemblyStaticMeshBuilder : public UNaniteAssemblyBuilder`  
_L13-85_
- reflection: `UCLASS(BlueprintType)`
- inherits: `UNaniteAssemblyBuilder`
- L18 _public prototype_ `UNaniteAssemblyStaticMeshBuilder(const FObjectInitializer& Initializer);`
- L20 _public function_ `virtual UObject* GetTargetMeshObject() const override`
- L26 _public prototype_ `static UNaniteAssemblyStaticMeshBuilder* BeginNewStaticMeshAssemblyBuild(const FNaniteAssemblyCreateNewParameters& Parameters);` — `UFUNCTION(BlueprintCallable, Category = "Static Mesh")` — Creates a Nanite Assembly Static Mesh builder to generate a new Static Mesh asset.
- L33 _public prototype_ `static UNaniteAssemblyStaticMeshBuilder* BeginEditStaticMeshAssemblyBuild(UStaticMesh* BaseMesh);` — `UFUNCTION(BlueprintCallable, Category = "Static Mesh")` — Creates a Nanite Assembly Static Mesh builder to add assembly parts to the specified Static Mesh, or overwrite its assembly parts if it is an existing Nanite Assembly mesh.
- L35 _public prototype_ `bool BeginAssemblyBuild(UStaticMesh* InTargetMesh);`
- L39 _public prototype_ `bool FinishAssemblyBuild(UStaticMesh*& OutStaticMesh);` — `UFUNCTION(BlueprintCallable, Category = "Static Mesh", meta = ( ReturnDisplayName = "Success" ))` — Finalizes the assembly build and returns the finished assembly mesh.
- L41 _public prototype_ `bool AddAssemblyParts( const UStaticMesh* PartMesh, TArrayView<const FTransform> LocalTransforms, const FNaniteAssemblyMaterialMergeOptions& MaterialMergeOptions = FNaniteAssemblyMaterialMergeOptions() );`
- L49 _public function_ `bool AddAssemblyParts( const UStaticMesh* PartMesh, const TArray<FTransform>& LocalTransforms, const FNaniteAssemblyMaterialMergeOptions& MaterialMergeOptions = FNaniteAssemblyMaterialMergeOptions() )` — `UFUNCTION(BlueprintCallable, Category = "Assembly Parts", meta = ( ReturnDisplayName = "Success", AutoCreateRefTerm = "MaterialMergeOptions" ))` — Adds instances of the specified mesh to the assembly with the specified local transforms
- L60 _public function_ `bool AddAssemblyPart( const UStaticMesh* PartMesh, const FTransform& LocalTransform, const FNaniteAssemblyMaterialMergeOptions& MaterialMergeOptions = FNaniteAssemblyMaterialMergeOptions() )` — `UFUNCTION(BlueprintCallable, Category = "Assembly Parts", meta = ( ReturnDisplayName = "Success", AutoCreateRefTerm = "MaterialMergeOptions" ))` — Adds an instance of the specified mesh to the assembly with the specified local transform
- L75 _public prototype_ `bool AddAssemblyPartsFromComponent( const UStaticMeshComponent* PartComponent, const FTransform& OriginTransform = FTransform(), const USceneComponent* OriginObject = nullptr, const FNaniteAssemblyMaterialMergeOptions& MaterialMergeOptions = FNaniteAssemblyMaterialMergeOptions() );` — `UFUNCTION(BlueprintCallable, Category = "Assembly Parts", meta = ( ReturnDisplayName = "Success", AutoCreateRefTerm = "OriginTransform, MaterialMergeOptions" ))` — Adds the meshes, materials, and instances of the specified component to the assembly. If an origin object is specified, all instance transforms of the component will be made relative to that object's world transform, and OriginTransform will be considered relative to the origin object's world-space transform.
- L84 _private member_ `TObjectPtr<UStaticMesh> TargetMesh;` — `UPROPERTY(Transient)`
