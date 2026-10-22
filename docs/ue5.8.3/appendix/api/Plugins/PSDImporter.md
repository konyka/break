# Plugins / PSDImporter

- module root: `Plugins/Experimental/PSDImporter/Source/PSDImporter`
- headers: 5; symbols: 144
- symbol kinds: class=4, delegate=1, enum=3, enumerator=10, function=19, member=43, namespace=2, prototype=48, struct=3, variable=11
- PrivateDependencyModuleNames: Engine, ImageCore, ImageWrapper, UnrealEd
- PublicDependencyModuleNames: Core, CoreUObject, PSDImporterCore

### `Plugins/Experimental/PSDImporter/Source/PSDImporter/Public/PSDDocument.h` (Public)


#### class `UPSDDocument`  
`class UPSDDocument : public UObject`  
_L22-87_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UObject`
- desc: @class UPSDDocument @brief Represents a PSD document in Unreal Engine. This class is used to store information about a PSD document, such as its name, size, and layers. It is intended to be used as part of the PSD Importer API in Unreal Engine.
- L32 _public prototype_ `UPSDDocument();`
- L35 _public prototype_ `const FString& GetDocumentName() const;` — `UFUNCTION(BlueprintPure, Category = "PSD Document")`
- L38 _public prototype_ `const FIntPoint& GetSize() const;` — `UFUNCTION(BlueprintPure, Category = "PSD Document")`
- L41 _public prototype_ `const TArray<FPSDFileLayer>& GetLayers() const;` — `UFUNCTION(BlueprintPure, Category = "PSD Document")`
- L44 _public prototype_ `bool WereLayersResizedOnImport() const;` — `UFUNCTION(BlueprintPure, Category = "PSD Document")`
- L47 _public prototype_ `TArray<const FPSDFileLayer*> GetValidLayers() const;` — Returns the layers with a valid size, that are visible, that aren't completely opaque and have a supported type.
- L50 _public prototype_ `int32 GetTextureCount() const;` — @return the number of textures, including mask textures, of "valid" layers.
- L54 _public prototype_ `virtual void GetAssetRegistryTags(FAssetRegistryTagsContext InContext) const override;`
- L61 _private member_ `FString DocumentName;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PSD Document", meta = (AllowPrivateAccess = "true"))` — Original document name, the asset may differ (if the user renamed it).
- L65 _private member_ `FIntPoint Size;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PSD Document", meta = (AllowPrivateAccess = "true"))` — Resolution (in pixels);
- L69 _private member_ `TArray<FPSDFileLayer> Layers;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, NoClear, EditFixedSize, Category = "PSD Document", meta = (AllowPrivateAccess = "true", ShowOnlyInnerProperties, EditFixedOrder, NoResetToDefault))`
- L72 _private member_ `bool bLayersResizedOnImport = false;` — `UPROPERTY()`
- L76 _private member_ `bool bImportInvisibleLayers = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PSD Document|Import Settings", meta = (AllowPrivateAccess = "true"))`
- L79 _private member_ `bool bResizeLayersToDocument = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PSD Document|Import Settings", meta = (AllowPrivateAccess = "true"))`
- L82 _private member_ `FPSDFileDocument FileDocument;` — `UPROPERTY()`
- L85 _private member_ `TObjectPtr<UAssetImportData> AssetImportData;` — `UPROPERTY(EditAnywhere, Instanced, Category = "PSD Document|Import Settings")`

### `Plugins/Experimental/PSDImporter/Source/PSDImporter/Public/PSDFile.h` (Public)


#### enum `EPSDFileLayerImportOperation`  
`enum class EPSDFileLayerImportOperation : uint8`  
_L13-19_
- reflection: `UENUM(BlueprintType)`
- L15 _public enumerator_ `Ignore = 0`
- L16 _public enumerator_ `Import = 1`
- L17 _public enumerator_ `ImportMerged = 2`
- L18 _public enumerator_ `Rasterize = 4`

#### enum `EPSDFileLayerType`  
`enum class EPSDFileLayerType : uint8`  
_L23-27_
- reflection: `UENUM()`
- L25 _public enumerator_ `Any = 0`
- L26 _public enumerator_ `Group = 1`

#### struct `FPSDFileLayerId`  
`struct FPSDFileLayerId`  
_L30-72_
- reflection: `USTRUCT(BlueprintType)`
- L36 _public member_ `int32 Index = INDEX_NONE;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Layer")` — Maps to the layer index in the PSD file.
- L39 _public member_ `FString Name;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Layer")`
- L41 _public function_ `FPSDFileLayerId() : FPSDFileLayerId(INDEX_NONE, FString(TEXT("")))`
- L46 _public function_ `FPSDFileLayerId(int32 InIndex, const FString& InName) : Index(InIndex) , Name(InName)`
- L52 _public function_ `bool operator==(const FPSDFileLayerId& InOther) const`
- L58 _public function_ `bool operator!=(const FPSDFileLayerId& InOther) const`
- L63 _public function_ `bool operator<(const FPSDFileLayerId& InOther) const`
- L68 _public function_ `bool operator<=(const FPSDFileLayerId& InOther) const`

#### struct `FPSDFileLayer`  
`struct FPSDFileLayer`  
_L80-201_
- reflection: `USTRUCT(BlueprintType)`
- L85 _public prototype_ `FPSDFileLayer() = default;`
- L88 _public function_ `FPSDFileLayer(const FPSDFileLayerId& InId) : Id(InId) , Type(EPSDFileLayerType::Any) , Bounds() , BlendMode(EPSDBlendMode::PassThrough)` — Implicit conversion from Id
- L96 _public function_ `explicit FPSDFileLayer(int32 InIndex, const FString& InName, EPSDFileLayerType InType) : Id(InIndex, InName) , Type(InType) , Bounds() , BlendMode(EPSDBlendMode::PassThrough)`
- L105 _public member_ `TOptional<FPSDFileLayerId> ParentId;` — `UPROPERTY(BlueprintReadOnly, Category = "Layer")`
- L109 _public member_ `FPSDFileLayerId Id;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Layer")` — Index, Name tuple.
- L112 _public member_ `EPSDFileLayerType Type = EPSDFileLayerType::Any;` — `UPROPERTY(BlueprintReadOnly, Category = "Layer")`
- L116 _public member_ `FIntRect Bounds;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Layer")` — Bounds of the layer.
- L120 _public member_ `bool bIsVisible = true;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Layer")` — Visibility state of the layer.
- L124 _public member_ `EPSDBlendMode BlendMode = EPSDBlendMode::PassThrough;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Layer")` — The blending mode applied to the layer.
- L128 _public member_ `double Opacity = 1.0;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Layer", meta = (ClampMin = 0.0, ClampMax = 1.0, UIMin = 0.0, UIMax = 1.0))` — Opacity level of the layer, value ranging from 0.0 (fully transparent) to 1.0 (fully opaque).
- L132 _public member_ `bool bIsSupportedLayerType = true;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Layer")` — A flag indicating whether the layer's type is supported.
- L136 _public member_ `EPSDFileLayerImportOperation ImportOperation = EPSDFileLayerImportOperation::Import;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Layer")` — User specified import operation/option.
- L140 _public member_ `TObjectPtr<UTexture2D> ThumbnailTexture;` — `UPROPERTY(VisibleAnywhere, NoClear, Category = "Layer")` — Optional thumbnail preview of the layer's contents.
- L144 _public member_ `TSoftObjectPtr<UTexture2D> Texture;` — `UPROPERTY(VisibleAnywhere, NoClear, Category = "Layer")` — Imported texture.
- L148 _public member_ `TSoftObjectPtr<UTexture2D> Mask;` — `UPROPERTY(VisibleAnywhere, NoClear, Category = "Layer")` — Imported mask.
- L152 _public member_ `FIntRect MaskBounds;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Layer")` — Bounds of the mask.
- L156 _public member_ `float MaskDefaultValue = 1.f;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Layer")` — Value of the mask outside the bounds.
- L160 _public member_ `uint8 Clipping = 0;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Layer")` — Whether this is a clipping layer.
- L162 _public function_ `bool operator==(const FPSDFileLayer& InOther) const`
- L167 _public function_ `bool operator!=(const FPSDFileLayer& InOther) const`
- L172 _public function_ `bool operator<(const FPSDFileLayer& InOther) const`
- L177 _public function_ `bool operator<=(const FPSDFileLayer& InOther) const`
- L182 _public function_ `bool HasMask() const`
- L187 _public function_ `bool IsLayerFullSize(const FIntPoint& InDocumentSize) const`
- L192 _public function_ `bool IsMaskFullSize(const FIntPoint& InDocumentSize) const`
- L197 _public function_ `bool NeedsCrop(const FIntPoint& InDocumentSize) const`

#### struct `FPSDFileDocument`  
`struct FPSDFileDocument`  
_L210-233_
- reflection: `USTRUCT(BlueprintType)`
- desc: Representation of a PSD file document.
- L216 _public member_ `int32 Height = 0;` — `UPROPERTY()` — Height of the document in pixels.
- L220 _public member_ `int32 Width = 0;` — `UPROPERTY()` — Width of the document in pixels.
- L224 _public member_ `uint8 Depth = 8;` — `UPROPERTY()` — Bit depth of the document. It can be 8, 16 or 32.
- L228 _public member_ `FName ColorMode = TEXT("RGB` — `UPROPERTY()` — Color mode of the document e.g., RGB, CMYK, etc.
- L232 _public member_ `TSet<FPSDFileLayer> Layers;` — `UPROPERTY()` — Set of layers contained in the document.

#### Free symbols / members of external scopes

- L20 _prototype_ `ENUM_CLASS_FLAGS(EPSDFileLayerImportOperation);`
- L74 _function_ `inline uint32 GetTypeHash(const FPSDFileLayerId& InValue)`
- L203 _function_ `inline uint32 GetTypeHash(const FPSDFileLayer& InValue)`

### `Plugins/Experimental/PSDImporter/Source/PSDImporter/Public/PSDLayerTextureUserData.h` (Public)


#### class `UPSDLayerTextureUserData`  
`class UPSDLayerTextureUserData : public UAssetUserData`  
_L15-31_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAssetUserData`
- L22 _public member_ `FPSDFileLayerId LayerId;` — `UPROPERTY(VisibleAnywhere, Category = "Layer")`
- L26 _public member_ `FBox2D NormalizedBounds;` — `UPROPERTY(VisibleAnywhere, Category = "Layer")` — Stored in 0.0-1.0 space.
- L30 _public member_ `FIntRect PixelBounds;` — `UPROPERTY(VisibleAnywhere, Category = "Layer")` — Stored in pixel space.

### `Plugins/Experimental/PSDImporter/Source/PSDImporter/Public/PSDQuadActor.h` (Public)


#### class `APSDQuadActor`  
`class APSDQuadActor : public AActor`  
_L17-99_
- reflection: `UCLASS(MinimalAPI, DisplayName = "PSD Layer Root Actor")`
- inherits: `AActor`
- L22 _public prototype_ `APSDQuadActor();`
- L24 _public prototype_ `virtual ~APSDQuadActor() override = default;`
- L26 _public prototype_ `UPSDDocument* GetPSDDocument() const;`
- L28 _public prototype_ `TArray<APSDQuadMeshActor*> GetQuadMeshes() const;`
- L30 _public prototype_ `float GetLayerDepthOffset() const;`
- L32 _public prototype_ `void SetLayerDepthOffset(float InDistance);`
- L34 _public prototype_ `bool IsAdjustingForViewDistance() const;`
- L36 _public prototype_ `float GetAdjustForViewDistance() const;`
- L38 _public prototype_ `void SetAdjustForViewDistance(float InDistance);`
- L40 _public prototype_ `bool IsSettingTranslucentSortPriority() const;`
- L42 _public prototype_ `float GetBaseTranslucentSortPriority() const;`
- L44 _public prototype_ `void SetBaseTranslucentSortPriority(int32 InPriority);`
- L47 _public prototype_ `void SetPSDDocument(UPSDDocument& InPSDDocument);`
- L49 _public prototype_ `void AddQuadMesh(APSDQuadMeshActor& InMeshActor);`
- L51 _public prototype_ `void InitComplete();`
- L54 _public prototype_ `virtual FString GetDefaultActorLabel() const override;`
- L58 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& InPropertyChangedEvent) override;`
- L63 _public prototype_ `virtual void Destroyed() override;`
- L68 _private member_ `TObjectPtr<UPSDDocument> PSDDocument;` — `UPROPERTY()`
- L71 _private member_ `TArray<TWeakObjectPtr<APSDQuadMeshActor>> MeshListWeak;` — `UPROPERTY()`
- L74 _private member_ `TObjectPtr<USceneComponent> LayerRoot;` — `UPROPERTY(VisibleAnywhere, Category = "PSD")`
- L78 _private member_ `float LayerDepthOffset = 1.f;` — `UPROPERTY(EditInstanceOnly, Setter, Category = "PSD")` — WIll separate each layer by this amount.
- L82 _private member_ `float AdjustForViewDistance = 0.f;` — `UPROPERTY()` — Will reduce the size of nearer quads to account for view distance with respect to the layer separation distance. 0 to disable.
- L86 _private member_ `int32 BaseTranslucentSortPriority = 1;` — `UPROPERTY(EditInstanceOnly, Category = "PSD")` — When assigning sort priority, use this as the first layer's priority. 0 to disable setting sort priority.
- L88 _private prototype_ `void OnLayerDepthOffsetChanged();`
- L90 _private prototype_ `void UpdateQuadSeparationDistances();`
- L92 _private prototype_ `void OnAdjustForViewDistanceChanged();`
- L94 _private prototype_ `void UpdateQuadSizeForViewDistance();`
- L96 _private prototype_ `void OnBaseTranslucentSortPriorityChanged();`
- L98 _private prototype_ `void UpdateQuadTranslucency();`

### `Plugins/Experimental/PSDImporter/Source/PSDImporter/Public/PSDQuadMeshActor.h` (Public)


#### enum `EPSDImporterLayerMaterialType`  
`enum class EPSDImporterLayerMaterialType : uint8`  
_L33-39_
- L35 _public enumerator_ `Default = 0`
- L36 _public enumerator_ `HasMask = 1 << 0`
- L37 _public enumerator_ `IsClipping = 1 << 1`
- L38 _public enumerator_ `ClipHasMask = 1 << 2`

#### class `APSDQuadMeshActor`  
`class APSDQuadMeshActor : public AActor`  
_L49-109_
- reflection: `UCLASS(MinimalAPI, DisplayName = "PSD Layer Actor")`
- inherits: `AActor`
- L56 _public function_ `static FPSDImporterTextureResetDelegate::RegistrationType& GetTextureResetDelegate()`
- L58 _public prototype_ `APSDQuadMeshActor();`
- L60 _public prototype_ `virtual ~APSDQuadMeshActor() override = default;`
- L62 _public prototype_ `APSDQuadActor* GetQuadActor() const;`
- L64 _public prototype_ `const FPSDFileLayer* GetLayer() const;`
- L66 _public prototype_ `const FPSDFileLayer* GetClippingLayer() const;`
- L68 _public prototype_ `UMaterialInterface* GetQuadMaterial() const;`
- L71 _public prototype_ `void InitLayer(APSDQuadActor& InQuadActor, int32 InLayerIndex, UMaterialInterface* InLayerMaterial);`
- L75 _public prototype_ `void ResetQuad();` — `UFUNCTION(CallInEditor, Category = "PSD", DisplayName = "Reset All")`
- L78 _public prototype_ `void ResetQuadDepth();` — `UFUNCTION(CallInEditor, Category = "PSD", DisplayName = "Reset Depth")`
- L81 _public prototype_ `void ResetQuadPosition();` — `UFUNCTION(CallInEditor, Category = "PSD", DisplayName = "Reset Position")`
- L84 _public prototype_ `void ResetQuadSize();` — `UFUNCTION(CallInEditor, Category = "PSD", DisplayName = "Reset Size")`
- L87 _public prototype_ `void ResetQuadTexture();` — `UFUNCTION(CallInEditor, Category = "PSD", DisplayName = "Reset Texture")`
- L90 _public prototype_ `void ResetQuadTranslucentSortPriority();` — `UFUNCTION(CallInEditor, Category = "PSD", DisplayName = "Reset Translucent Sort Priority")`
- L94 _public prototype_ `virtual FString GetDefaultActorLabel() const override;`
- L99 _private member_ `static FPSDImporterTextureResetDelegate TextureResetDelegate;`
- L102 _private member_ `TWeakObjectPtr<APSDQuadActor> QuadActorWeak;` — `UPROPERTY(VisibleAnywhere, DisplayName = "Layer Root Actor", Category = "PSD")`
- L105 _private member_ `int32 LayerIndex = INDEX_NONE;` — `UPROPERTY(VisibleAnywhere, Category = "PSD")`
- L108 _private member_ `TObjectPtr<UStaticMeshComponent> Mesh;` — `UPROPERTY(VisibleAnywhere, Category = "PSD")`

#### Free symbols / members of external scopes

- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace PSDImporter` (scope `UE`)
- L20 _variable_ `constexpr const TCHAR* LayerTextureParameterName = TEXT("Lay` (scope `UE::PSDImporter`)
- L21 _variable_ `constexpr const TCHAR* LayerBoundsParameterName = TEXT("Lay` (scope `UE::PSDImporter`)
- L22 _variable_ `constexpr const TCHAR* MaskTextureParameterName = TEXT("Mas` (scope `UE::PSDImporter`)
- L23 _variable_ `constexpr const TCHAR* MaskBoundsParameterName = TEXT("Mas` (scope `UE::PSDImporter`)
- L24 _variable_ `constexpr const TCHAR* MaskDefaultValueParameterName = TEXT("Mas` (scope `UE::PSDImporter`)
- L25 _variable_ `constexpr const TCHAR* ClippingLayerTextureParameterName = TEXT("Cli` (scope `UE::PSDImporter`)
- L26 _variable_ `constexpr const TCHAR* ClippingLayerBoundsParameterName = TEXT("Cli` (scope `UE::PSDImporter`)
- L27 _variable_ `constexpr const TCHAR* ClippingMaskTextureParameterName = TEXT("Cli` (scope `UE::PSDImporter`)
- L28 _variable_ `constexpr const TCHAR* ClippingMaskBoundsParameterName = TEXT("Cli` (scope `UE::PSDImporter`)
- L29 _variable_ `constexpr const TCHAR* ClippingMaskDefaultValueParameterName = TEXT("Cli` (scope `UE::PSDImporter`)
- L30 _variable_ `constexpr int32 MaxSamplerCount = 32;` (scope `UE::PSDImporter`)
- L46 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FPSDImporterTextureResetDelegate, APSDQuadMeshActor& ) UCLASS(MinimalAPI, DisplayName = "PSD Layer Actor") class APSDQuadMeshActor : public AActor { GENERATED_BODY() friend class UPSDQuadsFactory; public: static FPSDImporterTextureResetDelegate::RegistrationType& GetTextureResetDelegate() { return TextureResetDelegate; } APSDQuadMeshActor(); virtual ~APSDQuadMeshActor() override = default; APSDQuadActor* GetQuadActor() const; const FPSDFileLayer* GetLayer() const; const FPSDFileLayer* GetClippingLayer() const; UMaterialInterface* GetQuadMaterial() const; #if WITH_EDITOR void InitLayer(APSDQuadActor& InQuadActor, int32 InLayerIndex, UMaterialInterface* InLayerMaterial); #endif UFUNCTION(CallInEditor, Category = "PSD", DisplayName = "Reset All") void ResetQuad(); UFUNCTION(CallInEditor, Category = "PSD", DisplayName = "Reset Depth") void ResetQuadDepth(); UFUNCTION(CallInEditor, Category = "PSD", DisplayName = "Reset Position") void ResetQuadPosition(); UFUNCTION(CallInEditor, Category = "PSD", DisplayName = "Reset Size") void ResetQuadSize();` — We cannot know exactly what sort of material is being used on the actor, so we create a way for other material systems to hook into the reset call.
