# Plugins / ChaosOutfitAssetDataflowNodes

- module root: `Plugins/ChaosOutfitAsset/Source/ChaosOutfitAssetDataflowNodes`
- headers: 15; symbols: 136
- symbol kinds: enum=1, enumerator=1, function=15, member=53, prototype=32, struct=26, typedef=8
- PrivateDependencyModuleNames: AssetRegistry, Chaos, ChaosClothAsset, ChaosClothAssetEngine, ChaosOutfitAssetEngine, Core, CoreUObject, DataflowCore, Engine, MeshResizingCore

### `Plugins/ChaosOutfitAsset/Source/ChaosOutfitAssetDataflowNodes/Private/ChaosOutfitAsset/ClothAssetAnyType.h` (Private)


#### struct `FChaosClothAssetOrArrayType`  
`struct FChaosClothAssetOrArrayType`  
_L14-54_
- reflection: `USTRUCT()`
- L18 _public member_ `TVariant<TObjectPtr<UChaosClothAssetBase>, TArray<TObjectPtr<UChaosClothAssetBase>>> AssetOrArray;`
- L20 _public prototype_ `FChaosClothAssetOrArrayType() = default;`
- L23 _public function_ `template <typename T UE_REQUIRES(TIsDerivedFrom<T, UChaosClothAssetBase>::Value)> FChaosClothAssetOrArrayType(const TObjectPtr<T>& Asset) : AssetOrArray(TInPlaceType<TObjectPtr<UChaosClothAssetBase>>(), Asset)`
- L28 _public function_ `template <typename T UE_REQUIRES(TIsDerivedFrom<T, UChaosClothAssetBase>::Value)> FChaosClothAssetOrArrayType(const TArray<TObjectPtr<T>>& Array) : AssetOrArray(TInPlaceType<TArray<TObjectPtr<UChaosClothAssetBase>>>(), Array)`
- L32 _public function_ `bool IsArray() const`
- L37 _public function_ `const TObjectPtr<UChaosClothAssetBase>& Get() const`
- L43 _public function_ `const TArray<TObjectPtr<UChaosClothAssetBase>>& GetArray() const`
- L49 _public function_ `bool Serialize(FArchive& Ar)`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FChaosClothAssetOrArrayType> : public TStructOpsTypeTraitsBase2<FChaosClothAssetOrArrayType>`  
_L56-62_
- inherits: `TStructOpsTypeTraitsBase2<FChaosClothAssetOrArrayType>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L59-61_

#### struct `FChaosClothAssetAnyType`  
`struct FChaosClothAssetAnyType : public FDataflowAnyType`  
_L71-87_
- reflection: `USTRUCT()`
- inherits: `FDataflowAnyType`
- desc: UChaosClothAssetBase types.
- L82 _public typedef_ `using FPolicyType = FTypePolicy;`
- L83 _public typedef_ `using FStorageType = TObjectPtr<UChaosClothAssetBase>;`
- L86 _public member_ `TObjectPtr<UChaosClothAssetBase> Value = nullptr;` — `UPROPERTY(EditAnywhere, Category = Value)`

#### struct `FChaosClothAssetAnyType::FTypePolicy`  
`struct FTypePolicy : public TDataflowMultiTypePolicy< TObjectPtr<UChaosClothAssetBase>, TObjectPtr<UChaosClothAsset>, TObjectPtr<UChaosOutfitAsset>>`  
_L75-80_
- inherits: `TDataflowMultiTypePolicy<TObjectPtr<UChaosClothAssetBase>,TObjectPtr<UChaosClothAsset>,TObjectPtr<UChaosOutfitAsset>>`

#### struct `FChaosClothAssetArrayAnyType`  
`struct FChaosClothAssetArrayAnyType : public FDataflowAnyType`  
_L91-107_
- reflection: `USTRUCT()`
- inherits: `FDataflowAnyType`
- desc: UChaosClothAssetBase array types.
- L102 _public typedef_ `using FPolicyType = FArrayPolicy;`
- L103 _public typedef_ `using FStorageType = TArray<TObjectPtr<UChaosClothAssetBase>>;`
- L106 _public member_ `TArray<TObjectPtr<UChaosClothAssetBase>> Value;` — `UPROPERTY(EditAnywhere, Category = Value)`

#### struct `FChaosClothAssetArrayAnyType::FArrayPolicy`  
`struct FArrayPolicy : public TDataflowMultiTypePolicy< TArray<TObjectPtr<UChaosClothAssetBase>>, TArray<TObjectPtr<UChaosClothAsset>>, TArray<TObjectPtr<UChaosOutfitAsset>>>`  
_L95-100_
- inherits: `TDataflowMultiTypePolicy<TArray<TObjectPtr<UChaosClothAssetBase>>,TArray<TObjectPtr<UChaosClothAsset>>,TArray<TObjectPtr<UChaosOutfitAsset>>>`

#### struct `FChaosClothAssetOrArrayAnyType`  
`struct FChaosClothAssetOrArrayAnyType : public FDataflowAnyType`  
_L111-130_
- reflection: `USTRUCT()`
- inherits: `FDataflowAnyType`
- desc: UChaosClothAssetBase or array types.
- L125 _public typedef_ `using FPolicyType = FAssetOrArrayPolicy;`
- L126 _public typedef_ `using FStorageType = FChaosClothAssetOrArrayType;`
- L129 _public member_ `FChaosClothAssetOrArrayType Value;` — `UPROPERTY(EditAnywhere, Category = Value)`

#### struct `FChaosClothAssetOrArrayAnyType::FAssetOrArrayPolicy`  
`struct FAssetOrArrayPolicy : public TDataflowMultiTypePolicy< TObjectPtr<UChaosClothAssetBase>, TObjectPtr<UChaosClothAsset>, TObjectPtr<UChaosOutfitAsset>, TArray<TObjectPtr<UChaosClothAssetBase>>, TArray<TObjectPtr<UChaosClothAsset>>, TArray<TObjectPtr<UChaosOutfitAsset>>>`  
_L115-123_
- inherits: `TDataflowMultiTypePolicy<TObjectPtr<UChaosClothAssetBase>,TObjectPtr<UChaosClothAsset>,TObjectPtr<UChaosOutfitAsset>,TArray<TObjectPtr<UChaosClothAssetBase>>,TArray<TObjectPtr<UChaosClothAsset>>,TArray<TObjectPtr<UChaosOutfitAsset>>>`

#### Free symbols / members of external scopes

- L60 _enumerator_ `WithSerializer = true` (scope `TStructOpsTypeTraits::__anon363b367e0103`)

### `Plugins/ChaosOutfitAsset/Source/ChaosOutfitAssetDataflowNodes/Private/ChaosOutfitAsset/FilterSizedOutfitNode.h` (Private)


#### struct `FChaosOutfitAssetFilterSizedOutfitNode`  
`struct FChaosOutfitAssetFilterSizedOutfitNode final : public FDataflowNode`  
_L16-50_
- reflection: `USTRUCT(Meta = (DataflowOutfit))`
- inherits: `FDataflowNode`
- desc: Select a single size for the passed Outfit and filter out all non matching sizes.
- L26 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L31 _private member_ `TObjectPtr<const UChaosOutfit> Outfit;` — `UPROPERTY(Meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "Outfit"))` — The Outfit to filter.
- L35 _private member_ `FManagedArrayCollection OutfitCollection;` — `UPROPERTY(Meta = (DataflowOutput))` — The Outfit Collection output, provided for convenience as a view into the Outfit object metadata.
- L42 _private member_ `FString SizeName;` — `UPROPERTY(EditAnywhere, Category = "FilterSizedOutfit", Meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "SizeName"))` — The name of the body size to use to filter. If the input Size Name is empty, the output will be set to a name set from the Target Body's measurements.
- L49 _private member_ `TObjectPtr<const USkeletalMesh> TargetBody;` — `UPROPERTY(EditAnywhere, Category = "FilterSizedOutfit", Meta = (DataflowInput))` — The target body Skeletal Mesh containing the measurements to select the required size to use to filter. The target body is unused if Size Name is a valid name.

### `Plugins/ChaosOutfitAsset/Source/ChaosOutfitAssetDataflowNodes/Private/ChaosOutfitAsset/GetClothAssetNode.h` (Private)


#### struct `FChaosGetClothAssetNode`  
`struct FChaosGetClothAssetNode final : public FDataflowNode`  
_L15-31_
- reflection: `USTRUCT(Meta = (DataflowOutfit))`
- inherits: `FDataflowNode`
- desc: Get a Cloth Asset object into the graph.
- L25 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L30 _private member_ `TObjectPtr<const UChaosClothAsset> ClothAsset;` — `UPROPERTY(EditAnywhere, Category = "GetClothAsset", Meta = (DataflowOutput))` — The Cloth Asset to import into a collection.

### `Plugins/ChaosOutfitAsset/Source/ChaosOutfitAssetDataflowNodes/Private/ChaosOutfitAsset/GetOrMakeOutfitFromAssetNode.h` (Private)


#### struct `FChaosOutfitAssetGetOrMakeOutfitFromAssetNode`  
`struct FChaosOutfitAssetGetOrMakeOutfitFromAssetNode final : public FDataflowNode`  
_L18-38_
- reflection: `USTRUCT(Meta = (DataflowOutfit))`
- inherits: `FDataflowNode`
- desc: Extract the Outfit from an Outfit Asset. If the Outfit does not exist (e.g., this OutfitAsset has been cooked), recreate a new one.
- L28 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L33 _private member_ `TObjectPtr<const UChaosOutfitAsset> OutfitAsset;` — `UPROPERTY(meta = (DataflowInput))` — The Outfit Asset input.
- L37 _private member_ `TObjectPtr<const UChaosOutfit> Outfit;` — `UPROPERTY(Meta = (DataflowOutput))` — The Outfit output.

### `Plugins/ChaosOutfitAsset/Source/ChaosOutfitAssetDataflowNodes/Private/ChaosOutfitAsset/GetOutfitAssetNode.h` (Private)


#### struct `FChaosGetOutfitAssetNode`  
`struct FChaosGetOutfitAssetNode final : public FDataflowNode`  
_L15-31_
- reflection: `USTRUCT(Meta = (DataflowOutfit))`
- inherits: `FDataflowNode`
- desc: Get an Outfit Asset object into the graph.
- L25 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L30 _private member_ `TObjectPtr<const UChaosOutfitAsset> OutfitAsset;` — `UPROPERTY(EditAnywhere, Category = "GetOutfitAsset", Meta = (DataflowOutput))` — The Outfit Asset to import into a collection.

### `Plugins/ChaosOutfitAsset/Source/ChaosOutfitAssetDataflowNodes/Private/ChaosOutfitAsset/GetOutfitBodyPartsNode.h` (Private)


#### struct `FChaosOutfitBodySizeBodyParts`  
`struct FChaosOutfitBodySizeBodyParts`  
_L16-21_
- reflection: `USTRUCT()`
- desc: Skeletal Mesh body parts for a single body size.
- L20 _public member_ `TArray<TObjectPtr<const USkeletalMesh>> BodyParts;` — `UPROPERTY()`

#### struct `FChaosGetOutfitBodyPartsNode`  
`struct FChaosGetOutfitBodyPartsNode final : public FDataflowNode`  
_L27-47_
- reflection: `USTRUCT(Meta = (DataflowOutfit))`
- inherits: `FDataflowNode`
- desc: Extract the body part Skeletal Meshes from an Outfit, grouped by body size.
- L37 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L42 _private member_ `TObjectPtr<const UChaosOutfit> Outfit;` — `UPROPERTY(Meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "Outfit"))` — The source Outfit.
- L46 _private member_ `TArray<FChaosOutfitBodySizeBodyParts> BodySizeParts;` — `UPROPERTY(Meta = (DataflowOutput))` — The Outfit body parts grouped by body size.

#### struct `FChaosExtractBodyPartsArrayFromBodySizePartsNode`  
`struct FChaosExtractBodyPartsArrayFromBodySizePartsNode final : public FDataflowNode`  
_L53-73_
- reflection: `USTRUCT(Meta = (DataflowOutfit))`
- inherits: `FDataflowNode`
- desc: Extract the array of Skeletal Mesh body parts for a single body size.
- L59 _public prototype_ `FChaosExtractBodyPartsArrayFromBodySizePartsNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L63 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L68 _private member_ `FChaosOutfitBodySizeBodyParts BodySizeParts;` — `UPROPERTY(Meta = (DataflowInput))` — The source Outfit body parts for a single body size.
- L72 _private member_ `TArray<TObjectPtr<const USkeletalMesh>> BodyParts;` — `UPROPERTY(Meta = (DataflowOutput))` — The Outfit body part Skeletal Meshes for the input body size.

### `Plugins/ChaosOutfitAsset/Source/ChaosOutfitAssetDataflowNodes/Private/ChaosOutfitAsset/GetOutfitClothCollectionsNode.h` (Private)


#### struct `FChaosGetOutfitClothCollectionsNode`  
`struct FChaosGetOutfitClothCollectionsNode final : public FDataflowNode`  
_L15-47_
- reflection: `USTRUCT(Meta = (Experimental, DataflowOutfit))`
- inherits: `FDataflowNode`
- desc: Extract the Cloth Collections contained into the specified source Outfit.
- L25 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L30 _private member_ `TObjectPtr<const UChaosOutfit> Outfit;` — `UPROPERTY(Meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "Outfit"))` — The source Outfit.
- L34 _private member_ `TArray<FManagedArrayCollection> ClothCollections;` — `UPROPERTY(Meta = (DataflowOutput))` — The outfit cloth collections array in group of consecutives LODs for each of the outfit pieces.
- L38 _private member_ `int32 LodIndex = -1;` — `UPROPERTY(EditAnywhere, Category = "Get Outfit Cloth Collections", DisplayName = "LOD Index", Meta = (UIMin = -1, DataflowInput))` — The LOD to output in the cloth collections array. Set to -1 to output all LODs
- L42 _private member_ `int32 NumLods = 0;` — `UPROPERTY(DisplayName = "Num LODs", Meta = (DataflowOutput))` — The number of LODs output in the cloth collections array.
- L46 _private member_ `int32 NumPieces = 0;` — `UPROPERTY(Meta = (DataflowOutput))` — The number of cloth pieces output in the cloth collections array.

### `Plugins/ChaosOutfitAsset/Source/ChaosOutfitAssetDataflowNodes/Private/ChaosOutfitAsset/GetOutfitRBFInterpolationDataNode.h` (Private)


#### struct `FChaosGetOutfitRBFInterpolationDataNode`  
`struct FChaosGetOutfitRBFInterpolationDataNode final : public FDataflowNode`  
_L15-43_
- reflection: `USTRUCT(Meta = (DataflowOutfit))`
- inherits: `FDataflowNode`
- desc: Extract the Body Part RBF Interpolation Data from an Outfit.
- L25 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L30 _private member_ `TObjectPtr<const UChaosOutfit> Outfit;` — `UPROPERTY(Meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "Outfit"))` — The source Outfit.
- L34 _private member_ `int32 BodySizeIndex = 0;` — `UPROPERTY(EditAnywhere, Category = "Outfit RBF Interpolation", Meta = (DataflowInput, ClampMin = 0))` — The body size index.
- L38 _private member_ `int32 BodyPartIndex = 0;` — `UPROPERTY(EditAnywhere, Category = "Outfit RBF Interpolation", Meta = (DataflowInput, ClampMin = 0))` — The body part (sub) index.
- L42 _private member_ `FMeshResizingRBFInterpolationData InterpolationData;` — `UPROPERTY(Meta = (DataflowOutput))` — The interpolation data.

### `Plugins/ChaosOutfitAsset/Source/ChaosOutfitAssetDataflowNodes/Private/ChaosOutfitAsset/MakeOutfitNode.h` (Private)


#### struct `FChaosOutfitAssetMakeOutfitNode`  
`struct FChaosOutfitAssetMakeOutfitNode final : public FDataflowNode`  
_L17-54_
- reflection: `USTRUCT(Meta = (DataflowOutfit))`
- inherits: `FDataflowNode`
- desc: Make multiple Cloth Asset objects into an Outfit.
- L27 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L28 _private prototype_ `virtual TArray<UE::Dataflow::FPin> AddPins() override;`
- L29 _private function_ `virtual bool CanAddPin() const override`
- L33 _private function_ `virtual bool CanRemovePin() const override`
- L37 _private prototype_ `virtual TArray<UE::Dataflow::FPin> GetPinsToRemove() const override;`
- L38 _private prototype_ `virtual void OnPinRemoved(const UE::Dataflow::FPin& Pin) override;`
- L39 _private prototype_ `virtual void PostSerialize(const FArchive& Ar) override;`
- L42 _private prototype_ `UE::Dataflow::TConnectionReference<FChaosClothAssetOrArrayAnyType> GetConnectionReference(int32 Index) const;`
- L44 _private member_ `static constexpr int32 NumRequiredInputs = 0;`
- L45 _private member_ `static constexpr int32 NumInitialClothAssets = 1;`
- L49 _private member_ `TObjectPtr<const UChaosOutfit> Outfit;` — `UPROPERTY(Meta = (DataflowOutput))` — The Outfit output.
- L53 _private member_ `TArray<FChaosClothAssetOrArrayAnyType> ClothAssets;` — `UPROPERTY()` — The Cloth or Outfit Assets to import into a new Outfit.

### `Plugins/ChaosOutfitAsset/Source/ChaosOutfitAssetDataflowNodes/Private/ChaosOutfitAsset/MakeSizedOutfitNode.h` (Private)


#### struct `FChaosOutfitAssetMakeSizedOutfitNode`  
`struct FChaosOutfitAssetMakeSizedOutfitNode final : public FDataflowNode`  
_L16-57_
- reflection: `USTRUCT(Meta = ( DataflowOutfit))`
- inherits: `FDataflowNode`
- desc: Make multiple Cloth Assets into a sized Outfit.
- L26 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L27 _private prototype_ `virtual TArray<UE::Dataflow::FPin> AddPins() override;`
- L28 _private function_ `virtual bool CanAddPin() const override`
- L32 _private function_ `virtual bool CanRemovePin() const override`
- L36 _private prototype_ `virtual TArray<UE::Dataflow::FPin> GetPinsToRemove() const override;`
- L37 _private prototype_ `virtual void OnPinRemoved(const UE::Dataflow::FPin& Pin) override;`
- L38 _private prototype_ `virtual void PostSerialize(const FArchive& Ar) override;`
- L41 _private prototype_ `UE::Dataflow::TConnectionReference<FChaosSizedOutfitSourceOrArrayAnyType> GetConnectionReference(int32 Index) const;`
- L43 _private member_ `static constexpr int32 NumRequiredInputs = 0;`
- L44 _private member_ `static constexpr int32 NumInitialSizedOutfitSources = 1;`
- L48 _private member_ `TObjectPtr<const UChaosOutfit> Outfit;` — `UPROPERTY(Meta = (DataflowOutput))` — The Outfit output.
- L52 _private member_ `FManagedArrayCollection OutfitCollection;` — `UPROPERTY(Meta = (DataflowOutput))` — The Outfit Collection output, provided for convenience as a view into the Outfit object metadata.
- L56 _private member_ `TArray<FChaosSizedOutfitSourceOrArrayAnyType> SizedOutfitSources;` — `UPROPERTY()` — The Cloth/Outfit assets and body references to import into as a new sized Outfit.

### `Plugins/ChaosOutfitAsset/Source/ChaosOutfitAssetDataflowNodes/Private/ChaosOutfitAsset/MergeOutfitsNode.h` (Private)


#### struct `FChaosOutfitAssetMergeOutfitsNode`  
`struct FChaosOutfitAssetMergeOutfitsNode : public FDataflowNode`  
_L14-51_
- reflection: `USTRUCT(Meta = (DataflowOutfit))`
- inherits: `FDataflowNode`
- desc: Merge multiple Outfits into a single Outfit.
- L24 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L25 _private prototype_ `virtual TArray<UE::Dataflow::FPin> AddPins() override;`
- L26 _private function_ `virtual bool CanAddPin() const override`
- L30 _private function_ `virtual bool CanRemovePin() const override`
- L34 _private prototype_ `virtual TArray<UE::Dataflow::FPin> GetPinsToRemove() const override;`
- L35 _private prototype_ `virtual void OnPinRemoved(const UE::Dataflow::FPin& Pin) override;`
- L36 _private prototype_ `virtual void PostSerialize(const FArchive& Ar) override;`
- L39 _private prototype_ `UE::Dataflow::TConnectionReference<TObjectPtr<const UChaosOutfit>> GetConnectionReference(int32 Index) const;`
- L43 _private member_ `TArray<TObjectPtr<const UChaosOutfit>> Outfits;` — `UPROPERTY()` — The Outfit inputs to merge into a single Outfit.
- L47 _private member_ `TObjectPtr<const UChaosOutfit> Outfit;` — `UPROPERTY(Meta = (DataflowOutput, DataflowPassthrough = "Outfits[0]"))` — The Outfit output.
- L49 _private member_ `static constexpr int32 NumRequiredInputs = 0;`
- L50 _private member_ `static constexpr int32 NumInitialOptionalInputs = 2;`

### `Plugins/ChaosOutfitAsset/Source/ChaosOutfitAssetDataflowNodes/Private/ChaosOutfitAsset/OutfitAssetTerminalNode.h` (Private)


#### struct `FChaosOutfitAssetTerminalNode`  
`struct FChaosOutfitAssetTerminalNode final : public FDataflowTerminalNode`  
_L15-36_
- reflection: `USTRUCT(Meta = (DataflowOutfit, DataflowTerminal))`
- inherits: `FDataflowTerminalNode`
- desc: Outfit Terminal Node to generate an Outfit Asset.
- L25 _private prototype_ `virtual void SetAssetValue(TObjectPtr<UObject> Asset, UE::Dataflow::FContext& Context) const override;`
- L26 _private function_ `virtual void Evaluate(UE::Dataflow::FContext& Context) const override`
- L31 _private member_ `TObjectPtr<const UChaosOutfit> Outfit;` — `UPROPERTY(Meta = (DataflowInput))` — Input Outfit.
- L35 _private member_ `FDataflowFunctionProperty ConvertToSkeletalMesh;` — `UPROPERTY(EditAnywhere, Category = "Outfit Asset Terminal", Meta = (ButtonImage = "Icons.Convert"))` — Convert this Outfit to a Skeletal Mesh asset.

### `Plugins/ChaosOutfitAsset/Source/ChaosOutfitAssetDataflowNodes/Private/ChaosOutfitAsset/OutfitQueryNode.h` (Private)


#### struct `FChaosOutfitAssetOutfitQueryNode`  
`struct FChaosOutfitAssetOutfitQueryNode : public FDataflowNode`  
_L17-53_
- reflection: `USTRUCT(Meta = (DataflowOutfit))`
- inherits: `FDataflowNode`
- desc: Query an Outfit about its properties.
- L26 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L32 _private member_ `TObjectPtr<const UChaosOutfit> Outfit;` — `UPROPERTY(Meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "Outfit"))` — Input/output collection (output is always a passthrough).
- L36 _private member_ `bool bHasAnyValidPieces = false;` — `UPROPERTY(Meta = (DataflowOutput))` — Whether this Outfit has any valid pieces.
- L40 _private member_ `bool bHasAnyValidBodySizes = false;` — `UPROPERTY(Meta = (DataflowOutput))` — Whether this Outfit has any valid body sizes.
- L44 _private member_ `bool bBodyPartMustExist = false;` — `UPROPERTY(EditAnywhere, Category = "Outfit Query")` — Check that body parts are present in the asset registry when checking for valid body sizes.
- L48 _private member_ `bool bMeasurementsMustExist = true;` — `UPROPERTY(EditAnywhere, Category = "Outfit Query")` — Check that measurements are valid when checking for valid body sizes.
- L52 _private member_ `bool bInterpolationDataMustExist = true;` — `UPROPERTY(EditAnywhere, Category = "Outfit Query")` — Check that some interpolation data exists when checking for valid body sizes.

### `Plugins/ChaosOutfitAsset/Source/ChaosOutfitAssetDataflowNodes/Private/ChaosOutfitAsset/SetOutfitClothCollectionNode.h` (Private)


#### struct `FChaosSetOutfitClothCollectionNode`  
`struct FChaosSetOutfitClothCollectionNode final : public FDataflowNode`  
_L16-44_
- reflection: `USTRUCT(Meta = (Experimental, DataflowOutfit))`
- inherits: `FDataflowNode`
- desc: Replace the ClothCollection in an Outfit with a new one. Any data derived from the ClothCollection (e.g., Simulation Model, Render Data) will NOT be regenerated in the Outfit.
- L26 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L31 _private member_ `TObjectPtr<const UChaosOutfit> Outfit;` — `UPROPERTY(Meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "Outfit"))` — The Outfit to be edited.
- L35 _private member_ `FManagedArrayCollection ClothCollection;` — `UPROPERTY(Meta = (DataflowInput))` — The replacement cloth collection.
- L39 _private member_ `int32 PieceIndex = 0;` — `UPROPERTY(EditAnywhere, Category = "Set Cloth Collection", Meta =(ClampMin = 0, DataflowInput))` — The Outfit Piece to replace.
- L43 _private member_ `int32 LODIndex = 0;` — `UPROPERTY(EditAnywhere, Category = "Set Cloth Collection", Meta = (ClampMin = 0, DataflowInput))` — The Outfit LOD to replace.

### `Plugins/ChaosOutfitAsset/Source/ChaosOutfitAssetDataflowNodes/Private/ChaosOutfitAsset/SizedOutfitSourceAnyType.h` (Private)


#### struct `FChaosSizedOutfitSourceOrArrayType`  
`struct FChaosSizedOutfitSourceOrArrayType`  
_L13-29_
- reflection: `USTRUCT()`
- L18 _public member_ `TArray<FChaosSizedOutfitSource> Array;` — `UPROPERTY()`
- L20 _public prototype_ `FChaosSizedOutfitSourceOrArrayType() = default;`
- L22 _public function_ `FChaosSizedOutfitSourceOrArrayType(const FChaosSizedOutfitSource& SizedOutfitSource) : Array(&SizedOutfitSource, 1)`
- L26 _public function_ `FChaosSizedOutfitSourceOrArrayType(const TArray<FChaosSizedOutfitSource>& SizedOutfitSources) : Array(SizedOutfitSources)`

#### struct `FChaosSizedOutfitSourceOrArrayAnyType`  
`struct FChaosSizedOutfitSourceOrArrayAnyType : public FDataflowAnyType`  
_L36-51_
- reflection: `USTRUCT()`
- inherits: `FDataflowAnyType`
- desc: FChaosSizedOutfitSource or array types.
- L46 _public typedef_ `using FPolicyType = FPolicy;`
- L47 _public typedef_ `using FStorageType = FChaosSizedOutfitSourceOrArrayType;`
- L50 _public member_ `FChaosSizedOutfitSourceOrArrayType Value;` — `UPROPERTY(EditAnywhere, Category = Value)`

#### struct `FChaosSizedOutfitSourceOrArrayAnyType::FPolicy`  
`struct FPolicy : public TDataflowMultiTypePolicy< FChaosSizedOutfitSource, TArray<FChaosSizedOutfitSource>>`  
_L40-44_
- inherits: `TDataflowMultiTypePolicy<FChaosSizedOutfitSource,TArray<FChaosSizedOutfitSource>>`
