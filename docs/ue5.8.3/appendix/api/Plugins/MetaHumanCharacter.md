# Plugins / MetaHumanCharacter

- module root: `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacter`
- headers: 14; symbols: 632
- symbol kinds: class=4, delegate=4, enum=23, enumerator=133, function=42, macro=1, member=279, namespace=3, prototype=97, struct=46
- PublicDependencyModuleNames: Core, CoreUObject, Engine, ImageCore, MetaHumanCharacterPalette, MetaHumanSDKRuntime, Projects, SlateCore

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacter/Private/MetaHumanCharacterLog.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogMetaHumanCharacter, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogMetaHumanCharacter, Log, All);`

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacter/Private/MetaHumanCharacterStyle.h` (Private)


#### class `FMetaHumanCharacterStyle`  
`class FMetaHumanCharacterStyle : public FSlateStyleSet`  
_L10-20_
- inherits: `FSlateStyleSet`
- desc: Slate style set for the MetaHuman Character
- L13 _public prototype_ `static const FMetaHumanCharacterStyle& Get();`
- L15 _public prototype_ `static void Register();`
- L16 _public prototype_ `static void Unregister();`
- L19 _private prototype_ `FMetaHumanCharacterStyle();`

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacter/Public/MetaHumanCharacter.h` (Public)


#### enum `EMetaHumanCharacterRigState`  
`enum class EMetaHumanCharacterRigState : uint8`  
_L29-34_
- desc: The rigging state of the Character
- L31 _public enumerator_ `Unrigged = 0`
- L32 _public enumerator_ `RigPending`
- L33 _public enumerator_ `Rigged`

#### struct `FMetaHumanCharacterAssetsSection`  
`struct FMetaHumanCharacterAssetsSection`  
_L40-61_
- reflection: `USTRUCT()`
- desc: Configures single section of the wardrobe asset view.
- L46 _public member_ `FDirectoryPath ContentDirectoryToMonitor;` — `UPROPERTY(EditAnywhere, Category = "Section", meta = (LongPackageName))` — Long package directory name where to look for the assets
- L50 _public member_ `FName SlotName;` — `UPROPERTY(EditAnywhere, Category = "Section")` — Palette slot to target when the asset from this section is added.
- L54 _public member_ `TArray<TSubclassOf<UObject>> ClassesToFilter;` — `UPROPERTY(EditAnywhere, Category = "Section")` — Specifies the list of classes to look for in the given directory
- L58 _public member_ `bool bPureVirtual = false;` — `UPROPERTY()` — True if this section should be considered a pure virtual folder
- L60 _public prototype_ `bool operator==(const FMetaHumanCharacterAssetsSection& Other) const;`

#### struct `FMetaHumanCharacterWardrobeIndividualAssets`  
`struct FMetaHumanCharacterWardrobeIndividualAssets`  
_L64-70_
- reflection: `USTRUCT()`
- L69 _public member_ `TArray<TSoftObjectPtr<class UMetaHumanWardrobeItem>> Items;` — `UPROPERTY(EditAnywhere, Category = "Section")`

#### struct `FMetaHumanCharacterIndividualAssets`  
`struct FMetaHumanCharacterIndividualAssets`  
_L73-79_
- reflection: `USTRUCT()`
- L78 _public member_ `TArray<TSoftObjectPtr<UMetaHumanCharacter>> Characters;` — `UPROPERTY(EditAnywhere, Category = "Section")`

#### enum `EMetaHumanCharacterTemplateType`  
`enum class EMetaHumanCharacterTemplateType : uint8`  
_L82-85_
- reflection: `UENUM()`
- L84 _public enumerator_ `MetaHuman`

#### struct `FMetaHumanCharacterFaceEvaluationSettings`  
`struct FMetaHumanCharacterFaceEvaluationSettings`  
_L88-112_
- reflection: `USTRUCT(BlueprintType)`
- L93 _public member_ `float GlobalDelta = 1.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Face", meta = (UIMin = "0", UIMax = "1", ClampMin = "0", ClampMax = "1"))`
- L96 _public member_ `float HighFrequencyDelta = 1.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "Texture Position Offset", Category = "Face", meta = (UIMin = "0", UIMax = "1", ClampMin = "0", ClampMax = "1"))`
- L99 _public member_ `float HeadScale = 1.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Face", meta = (UIMin = "0.8", UIMax = "1.3", ClampMin = "0.8", ClampMax = "1.3"))`
- L101 _public function_ `bool operator==(const FMetaHumanCharacterFaceEvaluationSettings& InOther) const`
- L108 _public function_ `bool operator!=(const FMetaHumanCharacterFaceEvaluationSettings& InOther) const`

#### struct `FMetaHumanCharacterTextureInfo`  
`struct FMetaHumanCharacterTextureInfo`  
_L119-159_
- reflection: `USTRUCT(BlueprintType)`
- desc: Struct used to serialize information about a synthesized texture
- L124 _public member_ `int32 SizeX = 0;` — `UPROPERTY(VisibleAnywhere, Category = "Textures")`
- L127 _public member_ `int32 SizeY = 0;` — `UPROPERTY(VisibleAnywhere, Category = "Textures")`
- L130 _public member_ `int32 NumSlices = 0;` — `UPROPERTY(VisibleAnywhere, Category = "Textures")`
- L133 _public member_ `uint8 Format = ERawImageFormat::BGRA8;` — `UPROPERTY(VisibleAnywhere, Category = "Textures")`
- L136 _public member_ `uint8 GammaSpace = (uint8) EGammaSpace::sRGB;` — `UPROPERTY(VisibleAnywhere, Category = "Textures")`
- L138 _public function_ `void Init(const FImageInfo& InImageInfo)`
- L147 _public function_ `FImage GetBlankImage() const`
- L155 _public function_ `FImageInfo ToImageInfo() const`

#### struct `FMetaHumanCharacterHeadModelSettings`  
`struct FMetaHumanCharacterHeadModelSettings`  
_L162-173_
- reflection: `USTRUCT(BlueprintType)`
- L169 _public member_ `FMetaHumanCharacterEyelashesProperties Eyelashes;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Eyelashes", meta = (ShowOnlyInnerProperties))`
- L172 _public member_ `FMetaHumanCharacterTeethProperties Teeth;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Teeth", meta = (ShowOnlyInnerProperties))`

#### class `UMetaHumanCharacterThumbnailAux`  
`class UMetaHumanCharacterThumbnailAux : public UObject`  
_L182-185_
- reflection: `UCLASS()`
- inherits: `UObject`
- desc: Used by thumbnail system to generate additional thumbnails (e.g. face, body) and store them inside the character package.

#### enum `EMetaHumanCharacterThumbnailCameraPosition`  
`enum class EMetaHumanCharacterThumbnailCameraPosition : uint8`  
_L191-197_
- reflection: `UENUM()`
- desc: Camera framing positions for taking character's thumbnail.
- L193 _public enumerator_ `Face`
- L194 _public enumerator_ `Body`
- L195 _public enumerator_ `Character_Body`
- L196 _public enumerator_ `Character_Face`

#### class `UMetaHumanCharacter`  
`class UMetaHumanCharacter : public UObject`  
_L206-544_
- reflection: `UCLASS(BlueprintType)`
- inherits: `UObject`
- desc: The MetaHuman Character Asset holds all the information required build a MetaHuman. Any data that needs to be serialized for a MetaHuman should be stored in this class This class relies on the UMetaHumanCharacterEditorSubsystem to have its properties initialized and its basically a container for data associated with a MetaHuman
- L212 _public prototype_ `UMetaHumanCharacter();`
- L216 _public prototype_ `virtual void PostInitProperties() override;`
- L217 _public prototype_ `virtual void PostLoad() override;`
- L218 _public prototype_ `virtual void PostRename(UObject* OldOuter, const FName OldName) override;`
- L219 _public prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& InPropertyChangedEvent) override;`
- L220 _public prototype_ `virtual void PostTransacted(const FTransactionObjectEvent& InTransactionEvent) override;`
- L222 _public prototype_ `virtual void Serialize(FArchive& InAr) override;`
- L230 _public prototype_ `bool IsCharacterValid() const;` — Returns true if the character is in a valid state, meaning all of its components are properly initialized. Call UMetaHumanCharacterEditorSubsystem::InitializeMetaHumanCharacter to make sure the character is in a valid state
- L235 _public prototype_ `void SetFaceStateData(const FSharedBuffer& InFaceStateData);` — Stores Face State data in a compressed buffer
- L240 _public prototype_ `[[nodiscard]] FSharedBuffer GetFaceStateData() const;` — Retrieves the Face State data from the internal bulk data
- L245 _public prototype_ `void SetFaceDNABuffer(TConstArrayView<uint8> InFaceDNABuffer, bool bInHasFaceDNABlendshapes);` — Stores Face DNA in a compressed buffer.
- L250 _public prototype_ `bool HasFaceDNA() const;` — Returns true if the character has a face DNA stored in it
- L255 _public prototype_ `[[nodiscard]] TArray<uint8> GetFaceDNABuffer() const;` — Returns a buffer with the Face DNA from the internal bulk data
- L260 _public prototype_ `bool HasFaceDNABlendshapes() const;` — Returns true if the character has blendshapes in the attached face DNA.
- L265 _public prototype_ `void SetBodyStateData(const FSharedBuffer& InBodyStateData);` — Stores the Body State data in a compressed buffer
- L270 _public prototype_ `void SetBodyTargetPoseStateData(const FMetaHumanCharacterTargetMeshKey& InTargetMeshKey, const FSharedBuffer& InBodyStateData);` — Stores the Body State data in a compressed buffer
- L275 _public prototype_ `void SetTargetFaceModelCoefficients(const FMetaHumanCharacterTargetMeshKey& InTargetMeshKey, const TArray<float>& InCoefficients);` — Stores the face model coefficients corresponding to when the target pose state was serialized
- L280 _public prototype_ `[[nodiscard]] TArray<float> GetTargetFaceModelCoefficients(const FMetaHumanCharacterTargetMeshKey& InTargetMeshKey) const;` — Retrieves the face model coefficients corresponding to when the target pose state was serialized
- L285 _public prototype_ `[[nodiscard]] FSharedBuffer GetBodyStateData() const;` — Retrieves the Body State data from the internal bulk data
- L290 _public prototype_ `[[nodiscard]] FSharedBuffer GetBodyTargetPoseStateData(const FMetaHumanCharacterTargetMeshKey& InTargetMeshKey) const;` — Retrieves the Body State data from the internal bulk data
- L295 _public prototype_ `void SetBodyDNABuffer(TConstArrayView<uint8> InBodyDNABuffer);` — Stores Body DNA in a compressed buffer
- L300 _public prototype_ `bool HasBodyDNA() const;` — Returns true if the character has a body DNA stored in it
- L305 _public prototype_ `[[nodiscard]] TArray<uint8> GetBodyDNABuffer() const;` — Returns a buffer with the Body DNA from the internal bulk data
- L310 _public prototype_ `bool HasSynthesizedTextures() const;` — Returns true if the character has any synthesized textures stored in it
- L316 _public prototype_ `void SetHasHighResolutionTextures(bool bInHasHighResolutionTextures);` — Mark the character as having high resolution textures which can be used to prevent it from being overridden
- L321 _public prototype_ `bool HasHighResolutionTextures() const;` — Returns true if the character was marked as having high resolution textures
- L326 _public prototype_ `void StoreSynthesizedFaceTexture(EFaceTextureType InTextureType, const FImage& InTextureData);` — Stores face texture data to be serialized
- L331 _public prototype_ `FInt32Point GetSynthesizedFaceTexturesResolution(EFaceTextureType InFaceTextureType) const;` — Gets the synthesized face texture resolution.
- L336 _public prototype_ `bool NeedsToDownloadTextureSources() const;` — @brief Returns true if textures needs to be download to match the desired texture sources resolutions.
- L342 _public prototype_ `TMap<EFaceTextureType, TObjectPtr<UTexture2D>> GetValidFaceTextures() const;` — Gets the map of valid face textures. A texture is considered valid if its type is being referenced in SynthesizedFaceTexturesInfo
- L347 _public prototype_ `void StoreHighResBodyTexture(EBodyTextureType InTextureType, const FImage& InTextureData);` — Stores high res body texture data to be serialized
- L352 _public prototype_ `void ResetUnreferencedHighResTextureData();` — Resets the bulk data for any texture types that are missing texture infos
- L357 _public prototype_ `void RemoveAllTextures();` — Removes all textures stored in character
- L362 _public prototype_ `[[nodiscard]] TFuture<FSharedBuffer> GetSynthesizedFaceTextureDataAsync(EFaceTextureType InTextureType) const;` — Gets a future that can be used to obtain the actual face texture data
- L367 _public prototype_ `[[nodiscard]] TFuture<FSharedBuffer> GetHighResBodyTextureDataAsync(EBodyTextureType InTextureType) const;` — Gets a future that can be used to obtain the actual body texture data
- L372 _public prototype_ `FInt32Point GetSynthesizedBodyTexturesResolution(EBodyTextureType InBodyTextureType) const;` — Gets the synthesized body texture resolution.
- L376 _public prototype_ `[[nodiscard]] TObjectPtr<UMetaHumanCollection> GetMutableInternalCollection();` — Gets the Character's internal Collection
- L377 _public prototype_ `[[nodiscard]] const TObjectPtr<UMetaHumanCollection> GetInternalCollection() const;`
- L378 _public prototype_ `[[nodiscard]] FMetaHumanPaletteItemKey GetInternalCollectionKey() const;`
- L384 _public member_ `EMetaHumanCharacterTemplateType TemplateType = EMetaHumanCharacterTemplateType::MetaHuman;` — `UPROPERTY(VisibleAnywhere, Category = "Template")` — The character type used to load the appropriate identity template model
- L387 _public member_ `FMetaHumanCharacterFaceEvaluationSettings FaceEvaluationSettings;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Face")`
- L390 _public member_ `FMetaHumanCharacterHeadModelSettings HeadModelSettings;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Head")`
- L393 _public member_ `FMetaHumanCharacterSkinSettings SkinSettings;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Skin")`
- L396 _public member_ `FMetaHumanCharacterEyesSettings EyesSettings;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Eyes")`
- L399 _public member_ `FMetaHumanCharacterMakeupSettings MakeupSettings;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Makeup")`
- L402 _public member_ `bool bHasHighResolutionTextures = false;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Textures", AssetRegistrySearchable)`
- L406 _public member_ `bool bFixedBodyType = false;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Body", AssetRegistrySearchable)` — Fixed body types are either imported from dna as a whole rig, or a fixed compatibility body
- L410 _public member_ `TMap<EFaceTextureType, FMetaHumanCharacterTextureInfo> SynthesizedFaceTexturesInfo;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Textures|Face")` — Information about each of the face textures used to build the UTexture assets when the character is loaded
- L414 _public member_ `TMap<EFaceTextureType, TObjectPtr<class UTexture2D>> SynthesizedFaceTextures;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Textures|Face", Transient)` — Transient face textures created from the data stored in SynthesizedFaceTexturesData
- L418 _public member_ `TMap<EBodyTextureType, FMetaHumanCharacterTextureInfo> HighResBodyTexturesInfo;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Textures|Body")` — Information about each of the high res body textures used to build the UTexture assets when the character is loaded
- L422 _public member_ `TMap<EBodyTextureType, TObjectPtr<class UTexture2D>> BodyTextures;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Textures|Body", Transient)` — Transient body textures, can be created from the data stored in HighResBodyTexturesData
- L425 _public member_ `FMetaHumanCharacterViewportSettings ViewportSettings;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lighting")`
- L430 _public member_ `EMetaHumanCharacterSkinPreviewMaterial PreviewMaterialType = EMetaHumanCharacterSkinPreviewMaterial::Default;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skin")` — Serialized preview material, so that the editor can load the last used one
- L434 _public member_ `TObjectPtr<class UThumbnailInfo> ThumbnailInfo;` — `UPROPERTY(VisibleAnywhere, Instanced, AdvancedDisplay, Category = "Thumbnail")` — Information for thumbnail rendering
- L438 _public member_ `TArray<FMetaHumanCharacterAssetsSection> WardrobePaths;` — `UPROPERTY(VisibleAnywhere, Category = "Wardrobe")` — Character defined wardrobe paths
- L442 _public member_ `TMap<FName, FMetaHumanCharacterWardrobeIndividualAssets> WardrobeIndividualAssets;` — `UPROPERTY(VisibleAnywhere, Category = "Wardrobe")` — Wardrobe individual assets per slot name
- L446 _public member_ `TMap<FName, FMetaHumanCharacterIndividualAssets> CharacterIndividualAssets;` — `UPROPERTY(VisibleAnywhere, Category = "Pipeline")` — Character individual assets for blend tool and presets library
- L453 _public member_ `TMap<TSubclassOf<UMetaHumanCollectionPipeline>, TObjectPtr<UMetaHumanCollectionPipeline>> PipelinesPerClass;` — `UPROPERTY(VisibleAnywhere, Category = "Pipeline")` — A list of Collection pipelines that have been instanced for this character, used to track pipeline properties. There should be only a single instance of a pipeline class. Stored in a map for convenience.
- L456 _public member_ `FMetaHumanCharacterAssemblySettings AssemblySettings;` — `UPROPERTY(VisibleAnywhere, Category = "Pipeline")`
- L459 _public member_ `FMetaHumanCharacterTargetMeshKey LastTargetMeshKey;` — `UPROPERTY(VisibleAnywhere, Category = "Target Mesh")`
- L462 _public member_ `FMetaHumanCharacterTargetKeyPointCollection TargetMeshKeyPointsCollection;` — `UPROPERTY(VisibleAnywhere, Category = "Target Mesh")`
- L465 _public member_ `FMetaHumanCharacterTargetTrackingResultsCollection TargetMeshTrackingResultsCollection;` — `UPROPERTY(VisibleAnywhere, Category = "Target Mesh")`
- L470 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnWardrobePathsChanged);` — Callback when wardrobe settings changes in editor
- L471 _public member_ `FOnWardrobePathsChanged OnWardrobePathsChanged;`
- L474 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnRiggingStateChanged);` — Callback when rigging state changes in editor
- L475 _public member_ `FOnRiggingStateChanged OnRiggingStateChanged;`
- L478 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnAnimationReinitialized);` — Callback when animation is reinitialized and anim data needs a refresh
- L479 _public member_ `FOnAnimationReinitialized OnAnimationReinitialized;`
- L484 _public prototype_ `void NotifyRiggingStateChanged() const;` — Notifies that the rigging state of the character changed
- L487 _public prototype_ `static FName GetThumbnailPathInPackage(const FString& InCharacterAssetPath, EMetaHumanCharacterThumbnailCameraPosition InThumbnailPosition);` — Generates a full object path from the character object path and camera position to be used in the package thumbnail map.
- L496 _private prototype_ `void ConfigureCollection();` — Ensures the internal Collection is correctly set up to build this Character. Should be called when the Collection is initialized and any time the Collection's Character slot may have been modified.
- L501 _private member_ `TObjectPtr<UMetaHumanCharacterThumbnailAux> ThumbnailAux_CharacterBody;` — `UPROPERTY()`
- L504 _private member_ `TObjectPtr<UMetaHumanCharacterThumbnailAux> ThumbnailAux_Face;` — `UPROPERTY()`
- L507 _private member_ `TObjectPtr<UMetaHumanCharacterThumbnailAux> ThumbnailAux_Body;` — `UPROPERTY()`
- L515 _private member_ `TObjectPtr<UMetaHumanCollection> InternalCollection;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Instanced, DisplayName = "Internal Palette (build)", Category = "Pipeline", meta=(AllowPrivateAccess))` — The Character's built-in palette that is used for the build. Determines which build pipeline to use and contains all of the prepared assets that will be built for the platform.
- L518 _private member_ `FMetaHumanPaletteItemKey InternalCollectionKey;` — `UPROPERTY()`
- L521 _private member_ `UE::Serialization::FEditorBulkData FaceStateBulkData;` — Stores the Character Face State
- L524 _private member_ `UE::Serialization::FEditorBulkData FaceDNABulkData;` — Stores the Character Face DNA (optional)
- L528 _private member_ `bool bHasFaceDNABlendshapes = false;` — `UPROPERTY(VisibleAnywhere, Category = "DNA", AssetRegistrySearchable)` — Stores whether the face DNA contains blendshapes
- L531 _private member_ `UE::Serialization::FEditorBulkData BodyStateBulkData;` — Stores the Character Body State
- L534 _private member_ `TMap<FMetaHumanCharacterTargetMeshKey, TUniquePtr<UE::Serialization::FEditorBulkData>> BodyTargetPoseStateBulkData;` — Stores posed body states for target meshes
- L535 _private member_ `TMap<FMetaHumanCharacterTargetMeshKey, TArray<float>> FaceModelCoefficientsAtTargetPoseMap;`
- L538 _private member_ `UE::Serialization::FEditorBulkData BodyDNABulkData;` — Stores the Character Body DNA (optional)
- L541 _private member_ `TSortedMap<EFaceTextureType, UE::Serialization::FEditorBulkData> SynthesizedFaceTexturesData;` — Stores the Synthesized Face Textures data
- L543 _private member_ `TSortedMap<EBodyTextureType, UE::Serialization::FEditorBulkData> HighResBodyTexturesData;` — Stores the high res body Textures data

#### Free symbols / members of external scopes

- L470 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnWardrobePathsChanged);` — Callback when wardrobe settings changes in editor
- L474 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnRiggingStateChanged);` — Callback when rigging state changes in editor
- L478 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnAnimationReinitialized);` — Callback when animation is reinitialized and anim data needs a refresh

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacter/Public/MetaHumanCharacterAssemblySettings.h` (Public)


#### enum `EMetaHumanDefaultPipelineType`  
`enum class EMetaHumanDefaultPipelineType : uint8`  
_L14-19_
- reflection: `UENUM()`
- desc: Default pipelines for selection in the tool, should be in sync with the pipelines in UMetaHumanCharacterPaletteProjectSettings
- L16 _public enumerator_ `Cinematic UMETA(DisplayName = "UE Cine (Complete)")`
- L17 _public enumerator_ `Optimized UMETA(DisplayName = "UE Optimized")`
- L18 _public enumerator_ `UEFN UMETA(DisplayName = "UEFN Export")`

#### struct `FMetaHumanCharacterAssemblySettings`  
`struct FMetaHumanCharacterAssemblySettings`  
_L22-61_
- reflection: `USTRUCT(BlueprintType)`
- L27 _public prototype_ `FMetaHumanCharacterAssemblySettings();`
- L28 _public prototype_ `~FMetaHumanCharacterAssemblySettings();`
- L31 _public member_ `EMetaHumanDefaultPipelineType PipelineType = EMetaHumanDefaultPipelineType::Cinematic;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Assembly")`
- L34 _public member_ `EMetaHumanQualityLevel PipelineQuality = EMetaHumanQualityLevel::High;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Assembly")`
- L37 _public member_ `FDirectoryPath RootDirectory{ TEXT("/Game` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Assembly")`
- L40 _public member_ `FDirectoryPath CommonDirectory{ TEXT("/Game` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Assembly")`
- L42 _public member_ `static inline const FName AnimationSystemNameAnimBP = TEXT("Ani`
- L45 _public member_ `FName AnimationSystemName = AnimationSystemNameAnimBP;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Assembly")`
- L48 _public member_ `FString NameOverride;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Assembly")`
- L51 _public member_ `FString ArchiveName;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Assembly")`
- L54 _public member_ `FDirectoryPath OutputFolder;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Assembly")`
- L57 _public member_ `bool bBakeMakeup = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Assembly")`
- L60 _public member_ `bool bExportZipFile = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Assembly")`

#### class `IMetaHumanCharacterAssemblySettingsExtender`  
`class IMetaHumanCharacterAssemblySettingsExtender : public IModularFeature`  
_L63-70_
- inherits: `IModularFeature`
- L66 _public prototype_ `virtual ~IMetaHumanCharacterAssemblySettingsExtender() = default;`
- L67 _public member_ `static inline const FName FeatureName = TEXT("Met`
- L69 _public function_ `virtual void PostConstructionEdit(FMetaHumanCharacterAssemblySettings* AssemblySettings)`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API METAHUMANCHARACTER_API`

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacter/Public/MetaHumanCharacterCustomVersion.h` (Public)


#### struct `FMetaHumanCharacterCustomVersion`  
`struct FMetaHumanCharacterCustomVersion`  
_L8-31_
- L26 _public member_ `static const FGuid GUID;`
- L30 _private prototype_ `FMetaHumanCharacterCustomVersion() = default;`

#### enum `FMetaHumanCharacterCustomVersion::Type`  
`enum Type : int32`  
_L10-24_
- L13 _public enumerator_ `CharcterBase = 0` — Before any version changes
- L15 _public enumerator_ `BodyTexturesSerialized` — High res body textures serialized to character
- L17 _public enumerator_ `BodyTargetPoseStatesSerialized` — Body target pose states serialized to character
- L19 _public enumerator_ `FaceModelCoefficientsAtTargetPoseSerialized` — Face model coefficients at target pose serialized to character
- L22 _public enumerator_ `VersionPlusOne` — -----<new versions can be added above this line>-------------------------------------------------
- L23 _public enumerator_ `LatestVersion = VersionPlusOne - 1`

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacter/Public/MetaHumanCharacterEyes.h` (Public)


#### enum `EMetaHumanCharacterEyesBlendMethod`  
`enum class EMetaHumanCharacterEyesBlendMethod : uint8`  
_L10-14_
- reflection: `UENUM()`
- L12 _public enumerator_ `Radial = 0`
- L13 _public enumerator_ `Structural = 1`

#### enum `EMetaHumanCharacterEyesIrisPattern`  
`enum class EMetaHumanCharacterEyesIrisPattern : uint8`  
_L17-30_
- reflection: `UENUM()`
- L19 _public enumerator_ `Iris001 = 0`
- L20 _public enumerator_ `Iris002`
- L21 _public enumerator_ `Iris003`
- L22 _public enumerator_ `Iris004`
- L23 _public enumerator_ `Iris005`
- L24 _public enumerator_ `Iris006`
- L25 _public enumerator_ `Iris007`
- L26 _public enumerator_ `Iris008`
- L27 _public enumerator_ `Iris009`
- L29 _public enumerator_ `Count UMETA(Hidden)`

#### struct `FMetaHumanCharacterEyeIrisProperties`  
`struct FMetaHumanCharacterEyeIrisProperties`  
_L34-121_
- reflection: `USTRUCT(BlueprintType)`
- L40 _public member_ `EMetaHumanCharacterEyesIrisPattern IrisPattern = EMetaHumanCharacterEyesIrisPattern::Iris001;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "Pattern", Category = "Iris", meta = (ScriptName = "Pattern"))` — Iris Pattern Masks / Iris Normal
- L44 _public member_ `float IrisRotation = 0.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "Rotation", Category = "Iris", meta = (UIMin = "0", UIMax = "1", ClampMin = "0", ClampMax = "1", ScriptName = "Rotation"))` — Iris Rotation
- L48 _public member_ `float PrimaryColorU = 0.5f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Iris", meta = (UIMin = "0", UIMax = "1", ClampMin = "0", ClampMax = "1"))` — Iris Primary Color Hue
- L52 _public member_ `float PrimaryColorV = 0.5f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Iris", meta = (UIMin = "0", UIMax = "1", ClampMin = "0", ClampMax = "1"))` — Iris Primary Color Value
- L56 _public member_ `float SecondaryColorU = 0.5f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Iris", meta = (UIMin = "0", UIMax = "1", ClampMin = "0", ClampMax = "1"))` — Iris Secondary Color Hue
- L60 _public member_ `float SecondaryColorV = 0.5f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Iris", meta = (UIMin = "0", UIMax = "1", ClampMin = "0", ClampMax = "1"))` — Iris Secondary Color Value
- L64 _public member_ `float ColorBlend = 0.5f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Iris", meta = (UIMin = "0", UIMax = "1", ClampMin = "0", ClampMax = "1"))` — Iris Color Blend Coverage
- L68 _public member_ `float ColorBlendSoftness = 0.5f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Iris", meta = (UIMin = "0", UIMax = "1", ClampMin = "0", ClampMax = "1"))` — Iris Color Blend Coverage Softness
- L72 _public member_ `EMetaHumanCharacterEyesBlendMethod BlendMethod = EMetaHumanCharacterEyesBlendMethod::Structural;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Iris")` — Iris Color Blend Switch
- L76 _public member_ `float ShadowDetails = 0.5f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Iris", meta = (UIMin = "0", UIMax = "1", ClampMin = "0", ClampMax = "1"))` — Iris Shadow Details Amount
- L80 _public member_ `float LimbalRingSize = 0.725f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Iris", meta = (UIMin = "0", UIMax = "1", ClampMin = "0.6", ClampMax = "0.85"))` — Limbal Ring Size. Ranges from 0.6 to 0.85
- L84 _public member_ `float LimbalRingSoftness = 0.085f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Iris", meta = (UIMin = "0", UIMax = "1", ClampMin = "0.02", ClampMax = "0.15"))` — Limbal Ring Softness. Ranges from 0.02 to 0.15
- L88 _public member_ `FLinearColor LimbalRingColor = FLinearColor::Black;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Iris", meta = (HideAlphaChannel))` — Limbal Ring Color (Mult)
- L92 _public member_ `float GlobalSaturation = 2.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Iris", meta = (UIMin = "0", UIMax = "1", ClampMin = "0.0", ClampMax = "4.0"))` — Iris Global Saturation. Ranges from 0.0 to 4.0
- L96 _public member_ `FLinearColor GlobalTint = FLinearColor::White;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Iris", meta = (HideAlphaChannel))` — Iris Color Multiplyblend
- L98 _public function_ `bool operator==(const FMetaHumanCharacterEyeIrisProperties& InOther) const`
- L117 _public function_ `bool operator!=(const FMetaHumanCharacterEyeIrisProperties& InOther) const`

#### struct `FMetaHumanCharacterEyePupilProperties`  
`struct FMetaHumanCharacterEyePupilProperties`  
_L124-144_
- reflection: `USTRUCT(BlueprintType)`
- L129 _public member_ `float Dilation = 0.95f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pupil", meta = (UIMin = "0", UIMax = "1", ClampMin = "0.85", ClampMax = "1.2"))`
- L132 _public member_ `float Feather = 0.45f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pupil", meta = (UIMin = "0", UIMax = "1", ClampMin = "0", ClampMax = "1"))`
- L134 _public function_ `bool operator==(const FMetaHumanCharacterEyePupilProperties& InOther) const`
- L140 _public function_ `bool operator!=(const FMetaHumanCharacterEyePupilProperties& InOther) const`

#### struct `FMetaHumanCharacterEyeScleraProperties`  
`struct FMetaHumanCharacterEyeScleraProperties`  
_L147-190_
- reflection: `USTRUCT(BlueprintType)`
- L152 _public member_ `float Rotation = 0.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sclera", meta = (UIMin = "0", UIMax = "1", ClampMin = "0", ClampMax = "1"))`
- L157 _public member_ `bool bUseCustomTint = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sclera")` — If enabled allows the use of a custom sclera tint value. If disabled, the Sclera tint will be calculated based on the Skin Tone
- L160 _public member_ `FLinearColor Tint = FLinearColor::White;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sclera", meta = (HideAlphaChannel, EditCondition = "bUseCustomTint"))`
- L163 _public member_ `float TransmissionSpread = 0.115f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sclera", meta = (UIMin = "0", UIMax = "1", ClampMin = "0.03", ClampMax = "0.2"))`
- L166 _public member_ `FLinearColor TransmissionColor = FLinearColor::White;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sclera")`
- L169 _public member_ `float VascularityIntensity = 1.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sclera", meta = (UIMin = "0", UIMax = "1", ClampMin = "0.0", ClampMax = "2.0"))`
- L172 _public member_ `float VascularityCoverage = 0.2f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sclera", meta = (UIMin = "0", UIMax = "1", ClampMin = "0.1", ClampMax = "0.4"))`
- L174 _public function_ `bool operator==(const FMetaHumanCharacterEyeScleraProperties& InOther) const`
- L185 _public function_ `bool operator!=(const FMetaHumanCharacterEyeScleraProperties& InOther) const`

#### struct `FMetaHumanCharacterEyeCorneaProperties`  
`struct FMetaHumanCharacterEyeCorneaProperties`  
_L193-217_
- reflection: `USTRUCT(BlueprintType)`
- L198 _public member_ `float Size = 0.165f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cornea", meta = (UIMin = "0", UIMax = "1", ClampMin = "0.145", ClampMax = "0.185"))`
- L201 _public member_ `float LimbusSoftness = 0.09f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cornea", meta = (UIMin = "0", UIMax = "1", ClampMin = "0.03", ClampMax = "0.15"))`
- L204 _public member_ `FLinearColor LimbusColor = FLinearColor::White;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cornea", meta = (HideAlphaChannel))`
- L206 _public function_ `bool operator==(const FMetaHumanCharacterEyeCorneaProperties& InOther) const`
- L213 _public function_ `bool operator!=(const FMetaHumanCharacterEyeCorneaProperties& InOther) const`

#### struct `FMetaHumanCharacterEyeProperties`  
`struct FMetaHumanCharacterEyeProperties`  
_L220-238_
- reflection: `USTRUCT(BlueprintType)`
- L225 _public member_ `FMetaHumanCharacterEyeIrisProperties Iris;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Iris", meta = (ShowOnlyInnerProperties))`
- L228 _public member_ `FMetaHumanCharacterEyePupilProperties Pupil;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pupil", meta = (ShowOnlyInnerProperties))`
- L231 _public member_ `FMetaHumanCharacterEyeCorneaProperties Cornea;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cornea", meta = (ShowOnlyInnerProperties))`
- L234 _public member_ `FMetaHumanCharacterEyeScleraProperties Sclera;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sclera", meta = (ShowOnlyInnerProperties))`
- L236 _public prototype_ `bool operator==(const FMetaHumanCharacterEyeProperties& InOther) const;`
- L237 _public prototype_ `bool operator!=(const FMetaHumanCharacterEyeProperties& InOther) const;`

#### struct `FMetaHumanCharacterEyesSettings`  
`struct FMetaHumanCharacterEyesSettings`  
_L241-253_
- reflection: `USTRUCT(BlueprintType)`
- L246 _public member_ `FMetaHumanCharacterEyeProperties EyeLeft;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Eye", meta = (ShowOnlyInnerProperties))`
- L249 _public member_ `FMetaHumanCharacterEyeProperties EyeRight;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Eye", meta = (ShowOnlyInnerProperties))`
- L251 _public prototype_ `bool operator==(const FMetaHumanCharacterEyesSettings& InOther) const;`
- L252 _public prototype_ `bool operator!=(const FMetaHumanCharacterEyesSettings& InOther) const;`

#### enum `EMetaHumanCharacterEyelashesType`  
`enum class EMetaHumanCharacterEyelashesType : uint8`  
_L256-267_
- reflection: `UENUM()`
- L258 _public enumerator_ `None`
- L259 _public enumerator_ `ShortSparse`
- L260 _public enumerator_ `ShortFine`
- L261 _public enumerator_ `ShortThin`
- L262 _public enumerator_ `LongSlightCurl`
- L263 _public enumerator_ `LongCurl`
- L264 _public enumerator_ `LongThickCurl`
- L266 _public enumerator_ `Count UMETA(Hidden)`

#### struct `FMetaHumanCharacterEyelashesProperties`  
`struct FMetaHumanCharacterEyelashesProperties`  
_L271-323_
- reflection: `USTRUCT(BlueprintType)`
- L276 _public member_ `EMetaHumanCharacterEyelashesType Type = EMetaHumanCharacterEyelashesType::None;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Eyelashes")`
- L279 _public member_ `FLinearColor DyeColor = FLinearColor::White;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Eyelashes", meta = (HideAlphaChannel))`
- L282 _public member_ `float Melanin = 0.3f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Eyelashes", meta = (UIMin = "0", UIMax = "1", ClampMin = "0", ClampMax = "1"))`
- L285 _public member_ `float Redness = 0.28f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Eyelashes", meta = (UIMin = "0", UIMax = "1", ClampMin = "0", ClampMax = "1"))`
- L288 _public member_ `float Roughness = 0.25f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Eyelashes", meta = (UIMin = "0", UIMax = "1", ClampMin = "0", ClampMax = "1"))`
- L291 _public member_ `float SaltAndPepper = 0.20f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Eyelashes", meta = (UIMin = "0", UIMax = "1", ClampMin = "0", ClampMax = "1"))`
- L294 _public member_ `float Lightness = 0.50f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Eyelashes", meta = (UIMin = "0", UIMax = "1", ClampMin = "0", ClampMax = "1"))`
- L297 _public member_ `bool bEnableGrooms = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Eyelashes")`
- L299 _public function_ `bool operator==(const FMetaHumanCharacterEyelashesProperties& InOther) const`
- L311 _public function_ `bool operator!=(const FMetaHumanCharacterEyelashesProperties& InOther) const`
- L316 _public function_ `bool AreMaterialsUpdated(const FMetaHumanCharacterEyelashesProperties& InOther) const`

#### Free symbols / members of external scopes

- L31 _prototype_ `ENUM_RANGE_BY_COUNT(EMetaHumanCharacterEyesIrisPattern, EMetaHumanCharacterEyesIrisPattern::Count);`
- L268 _prototype_ `ENUM_RANGE_BY_COUNT(EMetaHumanCharacterEyelashesType, EMetaHumanCharacterEyelashesType::Count);`

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacter/Public/MetaHumanCharacterGeneratedAssets.h` (Public)


#### struct `FMetaHumanBodyRigLogicGeneratedAsset`  
`struct FMetaHumanBodyRigLogicGeneratedAsset`  
_L11-23_
- reflection: `USTRUCT()`
- L16 _public member_ `FString SolverName;` — `UPROPERTY(EditAnywhere, Category = "RigLogic")`
- L19 _public member_ `TObjectPtr<class UAnimSequence> AnimSequence;` — `UPROPERTY(EditAnywhere, Category = "RigLogic")`
- L22 _public member_ `TObjectPtr<class UPoseAsset> PoseAsset;` — `UPROPERTY(EditAnywhere, Category = "RigLogic")`

#### struct `FMetaHumanCharacterGeneratedAssets`  
`struct FMetaHumanCharacterGeneratedAssets`  
_L27-71_
- reflection: `USTRUCT()`
- desc: A manifest of the assets generated by a UMetaHumanCharacter
- L32 _public member_ `TObjectPtr<class USkeletalMesh> FaceMesh;` — `UPROPERTY()`
- L35 _public member_ `TMap<EFaceTextureType, TObjectPtr<class UTexture2D>> SynthesizedFaceTextures;` — `UPROPERTY()`
- L38 _public member_ `TMap<EBodyTextureType, TObjectPtr<class UTexture2D>> BodyTextures;` — `UPROPERTY()`
- L41 _public member_ `TObjectPtr<class USkeletalMesh> BodyMesh;` — `UPROPERTY()`
- L44 _public member_ `TObjectPtr<class UPhysicsAsset> PhysicsAsset;` — `UPROPERTY()`
- L47 _public member_ `TArray<FMetaHumanBodyRigLogicGeneratedAsset> BodyRigLogicAssets;` — `UPROPERTY()`
- L51 _public member_ `TObjectPtr<USkeletalMesh> MergedHeadAndBodyMesh;` — `UPROPERTY()` — A merged head and body mesh skinned to the body skeleton. Used for resizing outfits.
- L55 _public member_ `TMap<FString, float> BodyMeasurements;` — `UPROPERTY()` — Model parameters generated by fitting the model to the face and body geometry
- L65 _public member_ `TArray<FMetaHumanGeneratedAssetMetadata> Metadata;` — `UPROPERTY()` — Metadata about each generated asset referenced from properties on this struct. Callers expect to be able to iterate over all generated objects by iterating this array, so every object created in the Outer provided to UMetaHumanCharacterEditorSubsystem::TryGenerateCharacterAssets must have an entry in this array, even if they have no specific metadata.
- L70 _public prototype_ `bool RemoveAssetMetadata(TNotNull<const UObject*> InAsset);` — Utility to remove metadata for a given asset

#### struct `FMetaHumanCharacterGeneratedAssetOptions`  
`struct FMetaHumanCharacterGeneratedAssetOptions`  
_L73-83_
- L75 _public member_ `bool bGenerateFaceMesh = true;`
- L76 _public member_ `bool bGenerateBodyMesh = true;`
- L78 _public member_ `bool bGenerateMergedHeadAndBodyMesh = false;`
- L79 _public member_ `bool bGenerateBodyMeasurements = false;`
- L81 _public prototype_ `bool operator==(const FMetaHumanCharacterGeneratedAssetOptions& Other) const = default;`
- L82 _public prototype_ `bool operator!=(const FMetaHumanCharacterGeneratedAssetOptions& Other) const = default;`

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacter/Public/MetaHumanCharacterMakeup.h` (Public)


#### struct `FMetaHumanCharacterFoundationMakeupProperties`  
`struct FMetaHumanCharacterFoundationMakeupProperties`  
_L10-46_
- reflection: `USTRUCT(BlueprintType)`
- L15 _public member_ `bool bApplyFoundation = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Foundation")`
- L18 _public member_ `int32 PresetIndex = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Foundation")`
- L24 _public member_ `float Intensity = 0.5f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Foundation", meta = (UIMin = "0", UIMax = "1", ClampMin = "0", ClampMax = "1", EditCondition = "bApplyFoundation"))`
- L27 _public member_ `float Roughness = 0.65f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Foundation", meta = (UIMin = "0", UIMax = "1", ClampMin = "0", ClampMax = "1", EditCondition = "bApplyFoundation"))`
- L30 _public member_ `float Concealer = 0.57f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Foundation", meta = (UIMin = "0", UIMax = "1", ClampMin = "0", ClampMax = "1", EditCondition = "bApplyFoundation"))`
- L32 _public function_ `bool operator==(const FMetaHumanCharacterFoundationMakeupProperties& InOther) const`
- L42 _public function_ `bool operator!=(const FMetaHumanCharacterFoundationMakeupProperties& InOther) const`

#### enum `EMetaHumanCharacterEyeMakeupType`  
`enum class EMetaHumanCharacterEyeMakeupType : uint8`  
_L49-62_
- reflection: `UENUM()`
- L51 _public enumerator_ `None`
- L52 _public enumerator_ `ThinLiner`
- L53 _public enumerator_ `SoftSmokey`
- L54 _public enumerator_ `FullThinLiner`
- L55 _public enumerator_ `CatEye`
- L56 _public enumerator_ `PandaSmudge`
- L57 _public enumerator_ `DramaticSmudge`
- L58 _public enumerator_ `DoubleMod`
- L59 _public enumerator_ `ClassicBar`
- L61 _public enumerator_ `Count UMETA(Hidden)`

#### struct `FMetaHumanCharacterEyeMakeupProperties`  
`struct FMetaHumanCharacterEyeMakeupProperties`  
_L66-102_
- reflection: `USTRUCT(BlueprintType)`
- L71 _public member_ `EMetaHumanCharacterEyeMakeupType Type = EMetaHumanCharacterEyeMakeupType::None;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Eyes")`
- L77 _public member_ `FLinearColor SecondaryColor = FLinearColor::Black;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Eyes", meta = (HideAlphaChannel, EditCondition = "Type != EMetaHumanCharacterEyeMakeupType::None"))`
- L80 _public member_ `float Roughness = 0.75f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Eyes", meta = (UIMin = "0", UIMax = "1", ClampMin = "0", ClampMax = "1", EditCondition = "Type != EMetaHumanCharacterEyeMakeupType::None"))`
- L83 _public member_ `float Opacity = 0.85f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Eyes", meta = (UIMin = "0", UIMax = "1", ClampMin = "0", ClampMax = "1", EditCondition = "Type != EMetaHumanCharacterEyeMakeupType::None"))`
- L86 _public member_ `float Metalness = 0.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Eyes", meta = (UIMin = "0", UIMax = "1", ClampMin = "0", ClampMax = "1", EditCondition = "Type != EMetaHumanCharacterEyeMakeupType::None"))`
- L88 _public function_ `bool operator==(const FMetaHumanCharacterEyeMakeupProperties& InOther) const`
- L98 _public function_ `bool operator!=(const FMetaHumanCharacterEyeMakeupProperties& InOther) const`

#### enum `EMetaHumanCharacterBlushMakeupType`  
`enum class EMetaHumanCharacterBlushMakeupType : uint8`  
_L105-114_
- reflection: `UENUM()`
- L107 _public enumerator_ `None`
- L108 _public enumerator_ `Angled`
- L109 _public enumerator_ `Apple`
- L110 _public enumerator_ `LowSweep`
- L111 _public enumerator_ `HighCurve`
- L113 _public enumerator_ `Count UMETA(Hidden)`

#### struct `FMetaHumanCharacterBlushMakeupProperties`  
`struct FMetaHumanCharacterBlushMakeupProperties`  
_L118-146_
- reflection: `USTRUCT(BlueprintType)`
- L123 _public member_ `EMetaHumanCharacterBlushMakeupType Type = EMetaHumanCharacterBlushMakeupType::None;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blush")`
- L129 _public member_ `float Intensity = 0.4f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blush", meta = (UIMin = "0", UIMax = "1", ClampMin = "0", ClampMax = "1", EditCondition = "Type != EMetaHumanCharacterBlushMakeupType::None"))`
- L132 _public member_ `float Roughness = 0.6f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blush", meta = (UIMin = "0", UIMax = "1", ClampMin = "0", ClampMax = "1", EditCondition = "Type != EMetaHumanCharacterBlushMakeupType::None"))`
- L134 _public function_ `bool operator==(const FMetaHumanCharacterBlushMakeupProperties& InOther) const`
- L142 _public function_ `bool operator!=(const FMetaHumanCharacterBlushMakeupProperties& InOther) const`

#### enum `EMetaHumanCharacterLipsMakeupType`  
`enum class EMetaHumanCharacterLipsMakeupType : uint8`  
_L149-157_
- reflection: `UENUM()`
- L151 _public enumerator_ `None`
- L152 _public enumerator_ `Natural`
- L153 _public enumerator_ `Hollywood`
- L154 _public enumerator_ `Cupid`
- L156 _public enumerator_ `Count UMETA(Hidden)`

#### struct `FMetaHumanCharacterLipsMakeupProperties`  
`struct FMetaHumanCharacterLipsMakeupProperties`  
_L161-193_
- reflection: `USTRUCT(BlueprintType)`
- L166 _public member_ `EMetaHumanCharacterLipsMakeupType Type = EMetaHumanCharacterLipsMakeupType::None;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lips")`
- L172 _public member_ `float Roughness = 0.25f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lips", meta = (UIMin = "0", UIMax = "1", ClampMin = "0", ClampMax = "1", EditCondition = "Type != EMetaHumanCharacterLipsMakeupType::None"))`
- L175 _public member_ `float Opacity = 0.7f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lips", meta = (UIMin = "0", UIMax = "1", ClampMin = "0", ClampMax = "1", EditCondition = "Type != EMetaHumanCharacterLipsMakeupType::None"))`
- L178 _public member_ `float Metalness = 1.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blush", meta = (UIMin = "0", UIMax = "1", ClampMin = "0", ClampMax = "1", EditCondition = "Type != EMetaHumanCharacterLipsMakeupType::None"))`
- L180 _public function_ `bool operator==(const FMetaHumanCharacterLipsMakeupProperties& InOther) const`
- L189 _public function_ `bool operator!=(const FMetaHumanCharacterLipsMakeupProperties& InOther) const`

#### struct `FMetaHumanCharacterMakeupSettings`  
`struct FMetaHumanCharacterMakeupSettings`  
_L196-226_
- reflection: `USTRUCT(BlueprintType)`
- L203 _public member_ `FMetaHumanCharacterFoundationMakeupProperties Foundation;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Foundation", meta = (ShowOnlyInnerProperties))`
- L206 _public member_ `FMetaHumanCharacterEyeMakeupProperties Eyes;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Eyes", meta = (ShowOnlyInnerProperties))`
- L209 _public member_ `FMetaHumanCharacterBlushMakeupProperties Blush;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blush", meta = (ShowOnlyInnerProperties))`
- L212 _public member_ `FMetaHumanCharacterLipsMakeupProperties Lips;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lips", meta = (ShowOnlyInnerProperties))`
- L214 _public function_ `bool operator==(const FMetaHumanCharacterMakeupSettings& InOther) const`
- L222 _public function_ `bool operator!=(const FMetaHumanCharacterMakeupSettings& InOther) const`

#### Free symbols / members of external scopes

- L63 _prototype_ `ENUM_RANGE_BY_COUNT(EMetaHumanCharacterEyeMakeupType, EMetaHumanCharacterEyeMakeupType::Count);`
- L115 _prototype_ `ENUM_RANGE_BY_COUNT(EMetaHumanCharacterBlushMakeupType, EMetaHumanCharacterBlushMakeupType::Count);`

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacter/Public/MetaHumanCharacterMaterialSet.h` (Public)


#### enum `EMetaHumanCharacterSkinMaterialSlot`  
`enum class EMetaHumanCharacterSkinMaterialSlot : uint8`  
_L10-20_
- reflection: `UENUM()`
- L12 _public enumerator_ `LOD0 = 0`
- L13 _public enumerator_ `LOD1`
- L14 _public enumerator_ `LOD2`
- L15 _public enumerator_ `LOD3`
- L16 _public enumerator_ `LOD4`
- L17 _public enumerator_ `LOD5to7`
- L19 _public enumerator_ `Count UMETA(Hidden)`

#### struct `FMetaHumanCharacterFaceMaterialSet`  
`struct FMetaHumanCharacterFaceMaterialSet`  
_L24-83_
- reflection: `USTRUCT()`
- L29 _public member_ `TMap<EMetaHumanCharacterSkinMaterialSlot, TObjectPtr<class UMaterialInstance>> Skin;` — `UPROPERTY()`
- L32 _public member_ `TObjectPtr<class UMaterialInstance> EyeLeft;` — `UPROPERTY()`
- L35 _public member_ `TObjectPtr<class UMaterialInstance> EyeRight;` — `UPROPERTY()`
- L38 _public member_ `TObjectPtr<class UMaterialInstance> EyeShell;` — `UPROPERTY()`
- L41 _public member_ `TObjectPtr<class UMaterialInstance> LacrimalFluid;` — `UPROPERTY()`
- L44 _public member_ `TObjectPtr<class UMaterialInstance> Teeth;` — `UPROPERTY()`
- L47 _public member_ `TObjectPtr<class UMaterialInstance> Eyelashes;` — `UPROPERTY()`
- L50 _public member_ `TObjectPtr<class UMaterialInstance> EyelashesHiLods;` — `UPROPERTY()`
- L56 _public function_ `template<typename MaterialType> void ForEachSkinMaterial(TFunction<void(EMetaHumanCharacterSkinMaterialSlot, MaterialType*)> InCallback) const` — Utility to iterate over all the skin materials casting them to a particular type
- L71 _public function_ `template<typename MaterialType> void ForEachEyelashMaterial(TFunction<void(MaterialType*)> InCallback) const`

#### Free symbols / members of external scopes

- L21 _prototype_ `ENUM_RANGE_BY_COUNT(EMetaHumanCharacterSkinMaterialSlot, EMetaHumanCharacterSkinMaterialSlot::Count);`

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacter/Public/MetaHumanCharacterSkin.h` (Public)


#### struct `FMetaHumanCharacterSkinProperties`  
`struct FMetaHumanCharacterSkinProperties`  
_L14-85_
- reflection: `USTRUCT(BlueprintType)`
- L19 _public member_ `float U = 0.5f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skin", meta = (UIMin = "0", UIMax = "1", ClampMin = "0", ClampMax = "1"))`
- L22 _public member_ `float V = 0.5f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skin", meta = (UIMin = "0", UIMax = "1", ClampMin = "0", ClampMax = "1"))`
- L25 _public member_ `FVector3f BodyBias = {74.f, 28.f, 15.f};` — `UPROPERTY(VisibleAnywhere, Category = "Skin")`
- L28 _public member_ `FVector3f BodyGain = {30.f, 10.f, 5.f};` — `UPROPERTY(VisibleAnywhere, Category = "Skin")`
- L31 _public member_ `bool bShowTopUnderwear = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skin")`
- L34 _public member_ `int32 BodyTextureIndex = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skin", meta = (UIMin = "0", UIMax = "8", ClampMin = "0", ClampMax = "8"))`
- L37 _public member_ `int32 FaceTextureIndex = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skin", meta = (UIMin = "0", UIMax = "1", ClampMin = "0", ClampMax = "1"))`
- L41 _public member_ `float Roughness = 1.06f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skin", meta = (UIMin = "0", UIMax = "1", ClampMin = "0.85", ClampMax = "1.15"))` — Roughness UI Multiply. Range from 0.85 to 1.15
- L45 _public member_ `float PalmLightness = 0.75f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hands & Feet", meta = (UIMin = "0", UIMax = "1", ClampMin = "0", ClampMax = "1"))` — Palm Props
- L48 _public member_ `float PalmTint = 0.5f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hands & Feet", meta = (UIMin = "0", UIMax = "1", ClampMin = "0", ClampMax = "1"))`
- L51 _public member_ `float PalmCavityDarkness = 0.15f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hands & Feet", meta = (UIMin = "0", UIMax = "1", ClampMin = "0", ClampMax = "0.5"))`
- L58 _public member_ `float FingernailTintIntensity = 0.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hands & Feet", meta = (UIMin = "0", UIMax = "1", ClampMin = "0", ClampMax = "1"))`
- L61 _public member_ `float FingernailMetallic = 0.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hands & Feet", meta = (UIMin = "0", UIMax = "1", ClampMin = "0", ClampMax = "1"))`
- L64 _public member_ `float FingernailRoughness = 0.5f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hands & Feet", meta = (UIMin = "0", UIMax = "1", ClampMin = "0", ClampMax = "1"))`
- L71 _public member_ `float ToenailTintIntensity = 0.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hands & Feet", meta = (UIMin = "0", UIMax = "1", ClampMin = "0", ClampMax = "1"))`
- L74 _public member_ `float ToenailMetallic = 0.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hands & Feet", meta = (UIMin = "0", UIMax = "1", ClampMin = "0", ClampMax = "1"))`
- L77 _public member_ `float ToenailRoughness = 0.5f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hands & Feet", meta = (UIMin = "0", UIMax = "1", ClampMin = "0", ClampMax = "1"))`
- L82 _public prototype_ `bool EqualForTextureSynthesis(const FMetaHumanCharacterSkinProperties& InOther) const;` — Returns true if the properties that drive texture synthesis are equal. Used to skip re-synthesis when only non-texture properties (e.g. roughness, nail/palm settings) changed. Keep in sync with UMetaHumanCharacterEditorSkinTool::Setup() WatchProperty -> UpdateSkinSynthesizedTexture bindings.
- L83 _public prototype_ `bool operator==(const FMetaHumanCharacterSkinProperties& InOther) const;`
- L84 _public prototype_ `bool operator!=(const FMetaHumanCharacterSkinProperties& InOther) const;`

#### enum `EMetaHumanCharacterFrecklesMask`  
`enum class EMetaHumanCharacterFrecklesMask : uint8`  
_L88-96_
- reflection: `UENUM()`
- L90 _public enumerator_ `None`
- L91 _public enumerator_ `Type1`
- L92 _public enumerator_ `Type2`
- L93 _public enumerator_ `Type3`
- L95 _public enumerator_ `Count UMETA(Hidden)`

#### struct `FMetaHumanCharacterFrecklesProperties`  
`struct FMetaHumanCharacterFrecklesProperties`  
_L100-118_
- reflection: `USTRUCT(BlueprintType)`
- L105 _public member_ `float Density = 0.5f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Freckles", meta = (UIMin = "0", UIMax = "1", ClampMin = "0", ClampMax = "1"))`
- L108 _public member_ `float Strength = 0.2f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Freckles", meta = (UIMin = "0", UIMax = "1", ClampMin = "0", ClampMax = "1"))`
- L111 _public member_ `float Saturation = 0.6f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Freckles", meta = (UIMin = "0", UIMax = "1", ClampMin = "0", ClampMax = "1"))`
- L114 _public member_ `float ToneShift = 0.65f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Freckles", meta = (UIMin = "0", UIMax = "1", ClampMin = "0", ClampMax = "1"))`
- L117 _public member_ `EMetaHumanCharacterFrecklesMask Mask = EMetaHumanCharacterFrecklesMask::None;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Freckles")`

#### struct `FMetaHumanCharacterAccentRegionProperties`  
`struct FMetaHumanCharacterAccentRegionProperties`  
_L121-133_
- reflection: `USTRUCT(BlueprintType)`
- L126 _public member_ `float Redness = 0.5f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Accents", meta = (UIMin = "0", UIMax = "1", ClampMin = "0", ClampMax = "1"))`
- L129 _public member_ `float Saturation = 0.5f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Accents", meta = (UIMin = "0", UIMax = "1", ClampMin = "0", ClampMax = "1"))`
- L132 _public member_ `float Lightness = 0.5f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Accents", meta = (UIMin = "0", UIMax = "1", ClampMin = "0", ClampMax = "1"))`

#### struct `FMetaHumanCharacterAccentRegions`  
`struct FMetaHumanCharacterAccentRegions`  
_L136-163_
- reflection: `USTRUCT(BlueprintType)`
- L141 _public member_ `FMetaHumanCharacterAccentRegionProperties Scalp;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Accents")`
- L144 _public member_ `FMetaHumanCharacterAccentRegionProperties Forehead;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Accents")`
- L147 _public member_ `FMetaHumanCharacterAccentRegionProperties Nose;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Accents")`
- L150 _public member_ `FMetaHumanCharacterAccentRegionProperties UnderEye;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Accents")`
- L153 _public member_ `FMetaHumanCharacterAccentRegionProperties Cheeks;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Accents")`
- L156 _public member_ `FMetaHumanCharacterAccentRegionProperties Lips;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Accents")`
- L159 _public member_ `FMetaHumanCharacterAccentRegionProperties Chin;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Accents")`
- L162 _public member_ `FMetaHumanCharacterAccentRegionProperties Ears;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Accents")`

#### enum `EMetaHumanCharacterSkinPreviewMaterial`  
`enum class EMetaHumanCharacterSkinPreviewMaterial : uint8`  
_L166-173_
- reflection: `UENUM()`
- L168 _public enumerator_ `Default UMETA(DisplayName = "Topology")`
- L169 _public enumerator_ `Editable UMETA(DisplayName = "Skin")`
- L170 _public enumerator_ `Clay UMETA(DisplayName = "Clay")`
- L171 _public enumerator_ `Count UMETA(Hidden)`
- L172 _public enumerator_ `Gray UMETA(Hidden)`

#### struct `FMetaHumanCharacterSkinTextureSet`  
`struct FMetaHumanCharacterSkinTextureSet`  
_L181-196_
- reflection: `USTRUCT()`
- desc: Struct that hard references to all possible textures used in the skin material. This is also used as a utility to pass around skin textures sets
- L186 _public member_ `TMap<EFaceTextureType, TObjectPtr<class UTexture2D>> Face;` — `UPROPERTY()`
- L189 _public member_ `TMap<EBodyTextureType, TObjectPtr<class UTexture2D>> Body;` — `UPROPERTY()`
- L195 _public prototype_ `void Append(const FMetaHumanCharacterSkinTextureSet& InOther);` — Appends another texture set to this one. Replaces or adds any new textures from InOther

#### struct `FMetaHumanCharacterSkinTextureSoftSet`  
`struct FMetaHumanCharacterSkinTextureSoftSet`  
_L204-218_
- reflection: `USTRUCT(BlueprintType)`
- desc: Struct used to hold soft references to a skin texture set. This is used to store override textures in the MetaHuman Character object which are not loaded by default.
- L209 _public member_ `TMap<EFaceTextureType, TSoftObjectPtr<class UTexture2D>> Face;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Textures")`
- L212 _public member_ `TMap<EBodyTextureType, TSoftObjectPtr<class UTexture2D>> Body;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Textures")`
- L217 _public prototype_ `FMetaHumanCharacterSkinTextureSet LoadTextureSet() const;` — Load the textures and returns a texture set

#### enum `EMetaHumanCharacterTeethAndEyesSlot`  
`enum class EMetaHumanCharacterTeethAndEyesSlot : uint8`  
_L221-232_
- reflection: `UENUM(BlueprintType)`
- L223 _public enumerator_ `EyeLeft`
- L224 _public enumerator_ `EyeRight`
- L225 _public enumerator_ `EyeShell`
- L226 _public enumerator_ `LacrimalFluid`
- L227 _public enumerator_ `Teeth`
- L228 _public enumerator_ `Eyelashes`
- L229 _public enumerator_ `EyelashesHiLods`
- L231 _public enumerator_ `Count UMETA(Hidden)`

#### struct `FMetaHumanCharacterMaterialOverrideSet`  
`struct FMetaHumanCharacterMaterialOverrideSet`  
_L241-256_
- reflection: `USTRUCT(BlueprintType)`
- desc: Struct used to hold soft references to skin material overrides. When enabled, these materials replace the default preview MICs used for face and body rendering.
- L246 _public member_ `TMap<EMetaHumanCharacterSkinMaterialSlot, TSoftObjectPtr<UMaterialInstanceConstant>> Skin;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Materials|Face")`
- L249 _public member_ `TMap<EMetaHumanCharacterTeethAndEyesSlot, TSoftObjectPtr<UMaterialInstanceConstant>> TeethAndEyes;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Materials|Face", DisplayName = "Teeth & Eyes")`
- L252 _public member_ `TSoftObjectPtr<UMaterialInstanceConstant> Body;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Materials|Body")`
- L254 _public prototype_ `bool operator==(const FMetaHumanCharacterMaterialOverrideSet& InOther) const;`
- L255 _public prototype_ `bool operator!=(const FMetaHumanCharacterMaterialOverrideSet& InOther) const;`

#### enum `ERequestTextureResolution`  
`enum class ERequestTextureResolution : int32`  
_L262-267_
- reflection: `UENUM()`
- desc: Enum with the valid texture resolutions to request from the service
- L264 _public enumerator_ `Res2k = 2048 UMETA(DisplayName = "2k")`
- L265 _public enumerator_ `Res4k = 4096 UMETA(DisplayName = "4k")`
- L266 _public enumerator_ `Res8k = 8192 UMETA(DisplayName = "8k")`

#### struct `FMetaHumanCharacterTextureSourceResolutions`  
`struct FMetaHumanCharacterTextureSourceResolutions`  
_L271-308_
- reflection: `USTRUCT(BlueprintType)`
- L276 _public member_ `ERequestTextureResolution FaceAlbedo = ERequestTextureResolution::Res2k;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Face")`
- L279 _public member_ `ERequestTextureResolution FaceNormal = ERequestTextureResolution::Res2k;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Face")`
- L282 _public member_ `ERequestTextureResolution FaceCavity = ERequestTextureResolution::Res2k;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Face")`
- L285 _public member_ `ERequestTextureResolution FaceAnimatedMaps = ERequestTextureResolution::Res2k;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Face")`
- L288 _public member_ `ERequestTextureResolution BodyAlbedo = ERequestTextureResolution::Res2k;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Body")`
- L291 _public member_ `ERequestTextureResolution BodyNormal = ERequestTextureResolution::Res2k;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Body")`
- L294 _public member_ `ERequestTextureResolution BodyCavity = ERequestTextureResolution::Res2k;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Body")`
- L297 _public member_ `ERequestTextureResolution BodyMasks = ERequestTextureResolution::Res2k;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Body")`
- L302 _public prototype_ `void SetAllResolutionsTo(ERequestTextureResolution InResolution);` — @brief Sets all resolutions to be the same
- L307 _public prototype_ `bool AreAllResolutionsEqualTo(ERequestTextureResolution InResolution) const;` — @brief Returns true if all resolutions are the same as InResolution

#### struct `FMetaHumanCharacterTextureMaterialOverrides`  
`struct FMetaHumanCharacterTextureMaterialOverrides`  
_L312-337_
- reflection: `USTRUCT(BlueprintType)`
- desc: Holds texture and material override settings
- L317 _public member_ `bool bEnableTextureOverrides = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Texture Overrides")`
- L320 _public member_ `FMetaHumanCharacterSkinTextureSoftSet TextureOverrides;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Texture Overrides", meta = (EditCondition = "bEnableTextureOverrides"))`
- L323 _public member_ `bool bEnableMaterialOverrides = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Material Overrides")`
- L326 _public member_ `FMetaHumanCharacterMaterialOverrideSet MaterialOverrides;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Material Overrides", meta = (EditCondition = "bEnableMaterialOverrides"))`
- L330 _public member_ `bool bInheritUIParamsAndSrcTextures = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Material Overrides", DisplayName = "Inherit UI Parameters and Source Textures", meta = (EditCondition = "bEnableMaterialOverrides", ToolTip = "When enabled, UI material parameters (Skin, Eyes, Makeup, Teeth & Eyelashes) and source textures are applied on top of the override materials. When disabled, override materials are used as-is."))`
- L333 _public function_ `bool ShouldInheritUIParamsAndSrcTextures() const` — Returns true if UI material parameters and source textures should be applied to the current materials.

#### struct `FMetaHumanCharacterSkinSettings`  
`struct FMetaHumanCharacterSkinSettings`  
_L340-387_
- reflection: `USTRUCT(BlueprintType)`
- L345 _public prototype_ `FMetaHumanCharacterSkinSettings() = default;`
- L346 _public prototype_ `FMetaHumanCharacterSkinSettings(const FMetaHumanCharacterSkinSettings& Other) = default;`
- L347 _public prototype_ `FMetaHumanCharacterSkinSettings(FMetaHumanCharacterSkinSettings&& Other) = default;`
- L348 _public prototype_ `FMetaHumanCharacterSkinSettings& operator=(const FMetaHumanCharacterSkinSettings& Other) = default;`
- L349 _public prototype_ `FMetaHumanCharacterSkinSettings& operator=(FMetaHumanCharacterSkinSettings&& Other) = default;`
- L352 _public member_ `public: UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skin", meta = (ShowOnlyInnerProperties)) FMetaHumanCharacterSkinProperties Skin;`
- L358 _public member_ `FMetaHumanCharacterFrecklesProperties Freckles;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Freckles", meta = (ShowOnlyInnerProperties))`
- L361 _public member_ `FMetaHumanCharacterAccentRegions Accents;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Accents", meta = (ShowOnlyInnerProperties))`
- L365 _public member_ `FMetaHumanCharacterTextureSourceResolutions DesiredTextureSourcesResolutions;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Texture Sources")` — Desired resolutions to request when Downloading Source Textures
- L369 _public member_ `bool bEnableTextureOverrides = false;` — `UE_DEPRECATED(5.8, "bEnableTextureOverrides is deprecated, use TextureMaterialOverrides instead.")` — `UPROPERTY(BlueprintReadWrite, Category = "Texture Overrides", meta = (DeprecatedProperty, DeprecationMessage = "bEnableTextureOverrides is deprecated, use TextureMaterialOverrides instead."))`
- L373 _public member_ `FMetaHumanCharacterSkinTextureSoftSet TextureOverrides;` — `UE_DEPRECATED(5.8, "TextureOverrides is deprecated, use TextureMaterialOverrides instead.")` — `UPROPERTY(BlueprintReadWrite, Category = "Texture Overrides", meta = (DeprecatedProperty, DeprecationMessage = "TextureOverrides is deprecated, use TextureMaterialOverrides instead."))`
- L376 _public member_ `FMetaHumanCharacterTextureMaterialOverrides TextureMaterialOverrides;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Texture & Material Overrides")`
- L383 _public prototype_ `FMetaHumanCharacterSkinTextureSet GetFinalSkinTextureSet(const FMetaHumanCharacterSkinTextureSet& InSkinTextureSet) const;` — Returns a texture set considering the TextureMaterialOverrides.bEnableTextureOverrides flag. If the flag is enabled any texture in TextureMaterialOverrides.TextureOverrides are going to be present in the returned texture set
- L386 _public prototype_ `void PostSerialize(const FArchive& Ar);` — Migrates deprecated properties to TextureMaterialOverrides

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FMetaHumanCharacterSkinSettings> : public TStructOpsTypeTraitsBase2<FMetaHumanCharacterSkinSettings>`  
_L390-396_
- inherits: `TStructOpsTypeTraitsBase2<FMetaHumanCharacterSkinSettings>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L393-395_

#### Free symbols / members of external scopes

- L97 _prototype_ `ENUM_RANGE_BY_COUNT(EMetaHumanCharacterFrecklesMask, EMetaHumanCharacterFrecklesMask::Count);`
- L174 _prototype_ `ENUM_RANGE_BY_COUNT(EMetaHumanCharacterSkinPreviewMaterial, EMetaHumanCharacterSkinPreviewMaterial::Count);`
- L233 _prototype_ `ENUM_RANGE_BY_COUNT(EMetaHumanCharacterTeethAndEyesSlot, EMetaHumanCharacterTeethAndEyesSlot::Count);`
- L268 _prototype_ `ENUM_RANGE_BY_VALUES(ERequestTextureResolution, ERequestTextureResolution::Res2k, ERequestTextureResolution::Res4k, ERequestTextureResolution::Res8k);`
- L394 _enumerator_ `WithPostSerialize = true` (scope `TStructOpsTypeTraits::__anona69551340103`)

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacter/Public/MetaHumanCharacterTargetKeyPoints.h` (Public)


#### enum `EKeyPointType`  
`enum class EKeyPointType : uint8`  
_L10-15_
- reflection: `UENUM(BlueprintType)`
- L12 _public enumerator_ `Custom`
- L13 _public enumerator_ `PresetMH`
- L14 _public enumerator_ `PresetTarget`

#### struct `FMetaHumanCharacterTargetKeyPoints`  
`struct FMetaHumanCharacterTargetKeyPoints`  
_L18-47_
- reflection: `USTRUCT(BlueprintType)`
- L23 _public member_ `TMap<FName, int32> CharacterBodyVertexIndexes;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Key Points")`
- L26 _public member_ `TMap<FName, int32> CharacterHeadVertexIndexes;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Key Points")`
- L29 _public member_ `TMap<FName, FVector3f> TargetBodyPositions;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Key Points")`
- L32 _public member_ `TMap<FName, FVector3f> TargetHeadPositions;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Key Points")`
- L35 _public function_ `bool operator==(const FMetaHumanCharacterTargetKeyPoints& Other) const`
- L43 _public function_ `bool operator!=(const FMetaHumanCharacterTargetKeyPoints& Other) const`

#### struct `FMetaHumanCharacterTargetMeshKey`  
`struct FMetaHumanCharacterTargetMeshKey`  
_L50-72_
- reflection: `USTRUCT(BlueprintType)`
- L55 _public member_ `TSoftObjectPtr<UObject> BodyMesh;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Conform")`
- L58 _public member_ `TSoftObjectPtr<UObject> HeadMesh;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Conform")`
- L61 _public member_ `TSoftObjectPtr<UObject> CombinedMesh;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Conform")`
- L63 _public function_ `bool operator==(const FMetaHumanCharacterTargetMeshKey& Other) const`
- L68 _public function_ `bool operator!=(const FMetaHumanCharacterTargetMeshKey& Other) const`

#### struct `FMetaHumanCharacterTargetKeyPointCollection`  
`struct FMetaHumanCharacterTargetKeyPointCollection`  
_L106-112_
- reflection: `USTRUCT(BlueprintType)`
- L111 _public member_ `TMap<FMetaHumanCharacterTargetMeshKey, FMetaHumanCharacterTargetKeyPoints> PerMeshTargetKeyPoints;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Key Points")`

#### struct `FMetaHumanCharacterCurveTrackingPoints`  
`struct FMetaHumanCharacterCurveTrackingPoints`  
_L115-121_
- reflection: `USTRUCT(BlueprintType)`
- L120 _public member_ `TArray<FVector2D> Points;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Conform")`

#### struct `FMetaHumanCharacterTargetTrackingResults`  
`struct FMetaHumanCharacterTargetTrackingResults`  
_L124-144_
- reflection: `USTRUCT(BlueprintType)`
- L129 _public member_ `FMinimalViewInfo CameraViewInfo;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Conform")`
- L132 _public member_ `FIntPoint ImageSize = FIntPoint::ZeroValue;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Conform")`
- L135 _public member_ `TMap<FString, FMetaHumanCharacterCurveTrackingPoints> CurveTrackingPoints;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Conform")`
- L138 _public member_ `TArray<FColor> TrackedImage;` — `UPROPERTY(BlueprintReadWrite, Category = "Conform")`
- L143 _public member_ `TMap<FString, FMetaHumanCharacterCurveTrackingPoints> ControlVertexPoints;` — `UPROPERTY()` — Control vertex positions per curve, saved after tracking so they can be restored exactly on reload without re-running the lossy shape-annotation fitting pass.

#### struct `FMetaHumanCharacterTargetTrackingResultsCollection`  
`struct FMetaHumanCharacterTargetTrackingResultsCollection`  
_L147-153_
- reflection: `USTRUCT(BlueprintType)`
- L152 _public member_ `TMap<FMetaHumanCharacterTargetMeshKey, FMetaHumanCharacterTargetTrackingResults> PerMeshTrackingResults;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Conform")`

#### Free symbols / members of external scopes

- L74 _function_ `FORCEINLINE FArchive& operator<<(FArchive& Ar, FMetaHumanCharacterTargetMeshKey& K)`
- L82 _function_ `FORCEINLINE uint32 GetTypeHash(const FMetaHumanCharacterTargetMeshKey& Key)`
- L87 _function_ `FORCEINLINE bool operator<(const FMetaHumanCharacterTargetMeshKey& Left, const FMetaHumanCharacterTargetMeshKey& Right)`
- L92 _function_ `` (scope `operator <`)

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacter/Public/MetaHumanCharacterTeeth.h` (Public)


#### enum `EMetaHumanCharacterTeethType`  
`enum class EMetaHumanCharacterTeethType : uint8`  
_L10-24_
- reflection: `UENUM()`
- L13 _public enumerator_ `None` — TODO names may change; this is how it is in titan currently
- L14 _public enumerator_ `Variant_01`
- L15 _public enumerator_ `Variant_02`
- L16 _public enumerator_ `Variant_03`
- L17 _public enumerator_ `Variant_04`
- L18 _public enumerator_ `Variant_05`
- L19 _public enumerator_ `Variant_06`
- L20 _public enumerator_ `Variant_07`
- L21 _public enumerator_ `Variant_08`
- L23 _public enumerator_ `Count UMETA(Hidden)`

#### struct `FMetaHumanCharacterTeethProperties`  
`struct FMetaHumanCharacterTeethProperties`  
_L28-133_
- reflection: `USTRUCT(BlueprintType)`
- L33 _public member_ `float ToothLength = 0.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Teeth", meta = (UIMin = "-1", UIMax = "1", ClampMin = "-1", ClampMax = "1"))`
- L36 _public member_ `float ToothSpacing = 0.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Teeth", meta = (UIMin = "-1", UIMax = "1", ClampMin = "-1", ClampMax = "1"))`
- L39 _public member_ `float UpperShift = 0.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Teeth", meta = (UIMin = "-1", UIMax = "1", ClampMin = "-1", ClampMax = "1"))`
- L42 _public member_ `float LowerShift = 0.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Teeth", meta = (UIMin = "-1", UIMax = "1", ClampMin = "-1", ClampMax = "1"))`
- L45 _public member_ `float Overbite = 0.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Teeth", meta = (UIMin = "-1", UIMax = "1", ClampMin = "-1", ClampMax = "1"))`
- L48 _public member_ `float Overjet = 0.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Teeth", meta = (UIMin = "-1", UIMax = "1", ClampMin = "-1", ClampMax = "1"))`
- L51 _public member_ `float WornDown = 0.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Teeth", meta = (UIMin = "0", UIMax = "1", ClampMin = "0", ClampMax = "1"))`
- L54 _public member_ `float Polycanine = 0.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Teeth", meta = (UIMin = "0", UIMax = "1", ClampMin = "0", ClampMax = "1"))`
- L57 _public member_ `float RecedingGums = 0.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Teeth", meta = (UIMin = "0", UIMax = "1", ClampMin = "0", ClampMax = "1"))`
- L60 _public member_ `float Narrowness = 0.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Teeth", meta = (UIMin = "0", UIMax = "1", ClampMin = "0", ClampMax = "1"))`
- L63 _public member_ `float Variation = 0.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Teeth", meta = (UIMin = "0", UIMax = "1", ClampMin = "0", ClampMax = "1"))`
- L66 _public member_ `float JawOpen = 0.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Teeth", meta = (UIMin = "0", UIMax = "1", ClampMin = "0", ClampMax = "1"))`
- L69 _public member_ `FLinearColor TeethColor = FLinearColor::White;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Teeth", meta = (HideAlphaChannel))`
- L72 _public member_ `FLinearColor GumColor = FLinearColor::White;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Teeth", meta = (HideAlphaChannel))`
- L75 _public member_ `FLinearColor PlaqueColor = FLinearColor::White;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Teeth", meta = (HideAlphaChannel))`
- L78 _public member_ `float PlaqueAmount = 0.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Teeth", meta = (UIMin = "0", UIMax = "1", ClampMin = "0", ClampMax = "1"))`
- L82 _public member_ `bool EnableShowTeethExpression = false;` — `UPROPERTY(Transient)` — TODO: Can probably be moved to Character Editor data
- L84 _public function_ `bool operator==(const FMetaHumanCharacterTeethProperties& InOther) const`
- L105 _public function_ `bool operator!=(const FMetaHumanCharacterTeethProperties& InOther) const`
- L110 _public function_ `bool AreMaterialsUpdated(const FMetaHumanCharacterTeethProperties& InOther) const`
- L118 _public function_ `bool IsVariantUpdated(const FMetaHumanCharacterTeethProperties& InOther) const`

#### Free symbols / members of external scopes

- L25 _prototype_ `ENUM_RANGE_BY_COUNT(EMetaHumanCharacterTeethType, EMetaHumanCharacterTeethType::Count);`

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacter/Public/MetaHumanCharacterViewport.h` (Public)


#### enum `EMetaHumanCharacterEnvironment`  
`enum class EMetaHumanCharacterEnvironment : uint8`  
_L12-30_
- reflection: `UENUM()`
- L14 _public enumerator_ `Studio`
- L15 _public enumerator_ `Split`
- L16 _public enumerator_ `Fireside`
- L17 _public enumerator_ `Moonlight`
- L18 _public enumerator_ `Tungsten`
- L19 _public enumerator_ `Portrait`
- L20 _public enumerator_ `RedLantern`
- L21 _public enumerator_ `TextureBooth`
- L23 _public enumerator_ `Count UMETA(Hidden)`
- L28 _public enumerator_ `Custom` — Custom and Default are not real environments. They live after Count so TEnumRange skips them. Custom means the character is using a lighting world picked from the Custom Light Presets list. Default means use whatever the project setting "Default Lighting Environment" is set to.
- L29 _public enumerator_ `Default`

#### enum `EMetaHumanCharacterLOD`  
`enum class EMetaHumanCharacterLOD : uint8`  
_L34-46_
- reflection: `UENUM()`
- L36 _public enumerator_ `LOD0`
- L37 _public enumerator_ `LOD1`
- L38 _public enumerator_ `LOD2`
- L39 _public enumerator_ `LOD3`
- L40 _public enumerator_ `LOD4`
- L41 _public enumerator_ `LOD5`
- L42 _public enumerator_ `LOD6`
- L43 _public enumerator_ `LOD7`
- L44 _public enumerator_ `Auto`
- L45 _public enumerator_ `Count UMETA(Hidden)`

#### enum `EMetaHumanCharacterCameraFrame`  
`enum class EMetaHumanCharacterCameraFrame : uint8`  
_L51-61_
- reflection: `UENUM()`
- L53 _public enumerator_ `Auto`
- L54 _public enumerator_ `Face`
- L55 _public enumerator_ `Body`
- L56 _public enumerator_ `Far`
- L57 _public enumerator_ `Hands`
- L58 _public enumerator_ `Feet`
- L59 _public enumerator_ `SelectedPoint`
- L60 _public enumerator_ `Count UMETA(Hidden)`

#### enum `EMetaHumanCharacterRenderingQuality`  
`enum class EMetaHumanCharacterRenderingQuality : uint8`  
_L66-72_
- reflection: `UENUM()`
- L68 _public enumerator_ `Medium`
- L69 _public enumerator_ `High`
- L70 _public enumerator_ `Epic`
- L71 _public enumerator_ `Count UMETA(Hidden)`

#### struct `FMetaHumanCharacterViewportSettings`  
`struct FMetaHumanCharacterViewportSettings`  
_L77-163_
- reflection: `USTRUCT(BlueprintType)`
- L82 _public prototype_ `FMetaHumanCharacterViewportSettings() = default;`
- L83 _public prototype_ `FMetaHumanCharacterViewportSettings(const FMetaHumanCharacterViewportSettings& Other) = default;`
- L84 _public prototype_ `FMetaHumanCharacterViewportSettings(FMetaHumanCharacterViewportSettings&& Other) = default;`
- L85 _public prototype_ `FMetaHumanCharacterViewportSettings& operator=(const FMetaHumanCharacterViewportSettings& Other) = default;`
- L86 _public prototype_ `FMetaHumanCharacterViewportSettings& operator=(FMetaHumanCharacterViewportSettings&& Other) = default;`
- L90 _public member_ `EMetaHumanCharacterEnvironment CharacterEnvironment = EMetaHumanCharacterEnvironment::Default;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Viewport")`
- L93 _public member_ `TSoftObjectPtr<UWorld> CustomLightingEnvironment;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Viewport")`
- L96 _public member_ `FString CustomLightingEnvironmentKey;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Viewport")`
- L99 _public member_ `FLinearColor BackgroundColor = FLinearColor::Gray;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Viewport")`
- L102 _public member_ `float LightRotation = 0.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Viewport", meta = (UIMin = "-270", UIMax = "270", ClampMin = "-270", ClampMax = "270"))`
- L106 _public member_ `bool bTonemapperEnabled = true;` — `UE_DEPRECATED(5.8, "bTonemapperEnabled is deprecated. Tonemapper is now controlled via RenderingQualityProfiles in UMetaHumanCharacterEditorSettings.")` — `UPROPERTY(BlueprintReadWrite, Transient, Category = "Viewport", meta = (DeprecatedProperty, DeprecationMessage = "bTonemapperEnabled is deprecated. Tonemapper is now controlled via RenderingQualityProfiles in UMetaHumanCharacterEditorSettings."))`
- L109 _public member_ `EMetaHumanCharacterLOD LevelOfDetail = EMetaHumanCharacterLOD::LOD0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Viewport")`
- L112 _public member_ `EMetaHumanCharacterCameraFrame CameraFrame = EMetaHumanCharacterCameraFrame::Face;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Viewport")`
- L116 _public member_ `bool bUseDistanceScaledCameraSpeed = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Viewport", Transient)` — When enabled, scales the perspective camera speed based on the distance between the camera and its look-at position.
- L120 _public member_ `EMetaHumanCharacterRenderingQuality RenderingQuality = EMetaHumanCharacterRenderingQuality::Epic;` — `UE_DEPRECATED(5.8, "RenderingQuality is deprecated, please use RenderingQualityProfileIndex instead.")` — `UPROPERTY(BlueprintReadWrite, Transient, Category = "Viewport", meta = (DeprecatedProperty, DeprecationMessage = "RenderingQuality is deprecated, please use RenderingQualityProfileIndex instead."))`
- L123 _public member_ `int32 RenderingQualityProfileIndex = INDEX_NONE;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Viewport")`
- L126 _public member_ `bool bAlwaysUseHairCards = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Viewport")`
- L129 _public member_ `bool bHairHiddenInPreviewScene = false;` — `UPROPERTY(Transient)`
- L132 _public member_ `bool bShowViewportOverlays = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Viewport")`
- L135 _public member_ `bool bShowFaceBones = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Viewport")`
- L138 _public member_ `float FaceBoneSize = 1.0f;` — `UPROPERTY(EditAnywhere, Category = "Viewport", meta = (UIMin = "0.0", UIMax = "1.0", ClampMin = "0.0", ClampMax = "1.0"))`
- L141 _public member_ `bool bShowBodyBones = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Viewport")`
- L144 _public member_ `float BodyBoneSize = 1.0f;` — `UPROPERTY(EditAnywhere, Category = "Viewport", meta = (UIMin = "0.0", UIMax = "1.0", ClampMin = "0.0", ClampMax = "1.0"))`
- L147 _public member_ `bool bShowFaceNormals = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Viewport")`
- L150 _public member_ `bool bShowBodyNormals = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Viewport")`
- L153 _public member_ `bool bShowFaceTangents = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Viewport")`
- L156 _public member_ `bool bShowBodyTangents = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Viewport")`
- L159 _public member_ `bool bShowFaceBinormals = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Viewport")`
- L162 _public member_ `bool bShowBodyBinormals = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Viewport")`

#### Free symbols / members of external scopes

- L31 _prototype_ `ENUM_RANGE_BY_COUNT(EMetaHumanCharacterEnvironment, EMetaHumanCharacterEnvironment::Count);`
- L47 _prototype_ `ENUM_RANGE_BY_COUNT(EMetaHumanCharacterLOD, EMetaHumanCharacterLOD::Count);`
- L62 _prototype_ `ENUM_RANGE_BY_COUNT(EMetaHumanCharacterCameraFrame, EMetaHumanCharacterCameraFrame::Count);`
- L73 _prototype_ `ENUM_RANGE_BY_COUNT(EMetaHumanCharacterRenderingQuality, EMetaHumanCharacterRenderingQuality::Count);`

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacter/Public/MetaHumanGeometryRemovalTypes.h` (Public)


#### struct `UE::MetaHuman::GeometryRemoval::FHiddenFaceMapSettings`  
`struct FHiddenFaceMapSettings`  
_L15-51_
- reflection: `USTRUCT(BlueprintType)`
- desc: Settings that specify how the pixel values in a hidden face map should be interpreted.
- L26 _public member_ `float MaxCullValue = 0.1f;` — `UPROPERTY(EditAnywhere, Category = "HiddenFaceMap")` — Any triangles *fully* covered by pixel values below this threshold will be removed. In other words, geometry will be removed in regions of the hidden face map that are closer to zero (i.e. black) than this.
- L33 _public member_ `float MinKeepValue = 0.9f;` — `UPROPERTY(EditAnywhere, Category = "HiddenFaceMap")` — Geometry in regions of the hidden face map that are closer to one (i.e. white) than this will be left untouched.
- L50 _public member_ `float MaxShrinkDistance = 0.0f;` — `UPROPERTY(EditAnywhere, Category = "HiddenFaceMap")` — Vertices in regions of the hidden face map that are between MaxCullValue and MinKeepValue will be "shrunk", i.e. moved in the opposite direction of their vertex normal. This helps to keep them out of the way of any overlapping geometry without removing them completely. The distance a vertex will be moved depends on its pixel value in the hidden face map. The distance is calculated by using the pixel value as a weight to interpolate between 0 and the specified maximum distance. In other words, pixels close to MaxCullValue will be shrunk the maximum distance, whereas pixels close to MinKeepValue will be moved very little.

#### struct `UE::MetaHuman::GeometryRemoval::FHiddenFaceMapTexture`  
`struct FHiddenFaceMapTexture`  
_L55-64_
- reflection: `USTRUCT(BlueprintType)`
- desc: A hidden face map texture and the settings to use when applying it
- L60 _public member_ `TObjectPtr<UTexture2D> Texture;` — `UPROPERTY(EditAnywhere, Category = "HiddenFaceMap")`
- L63 _public member_ `FHiddenFaceMapSettings Settings;` — `UPROPERTY(EditAnywhere, Category = "HiddenFaceMap")`

#### struct `UE::MetaHuman::GeometryRemoval::FHiddenFaceMapImage`  
`struct FHiddenFaceMapImage`  
_L67-75_
- desc: A hidden face map image and the settings to use when applying it
- L69 _public member_ `FImage Image;`
- L72 _public member_ `FString DebugName;` — An optional debug string that will be used in error messages to identify this hidden face map
- L74 _public member_ `FHiddenFaceMapSettings Settings;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace MetaHuman` (scope `UE`)
- L11 _namespace_ `namespace GeometryRemoval` (scope `UE::MetaHuman`)
