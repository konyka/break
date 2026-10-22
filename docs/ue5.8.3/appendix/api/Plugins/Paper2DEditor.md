# Plugins / Paper2DEditor

- module root: `Plugins/2D/Paper2D/Source/Paper2DEditor`
- headers: 86; symbols: 1455
- symbol kinds: class=93, delegate=5, enum=6, enumerator=22, function=177, macro=6, member=389, namespace=7, prototype=734, struct=10, typedef=2, variable=4
- PrivateDependencyModuleNames: ApplicationCore, AssetTools, ContentBrowser, Core, CoreUObject, EditorFramework, EditorWidgets, Engine, ImageCore, InputCore, Kismet, KismetWidgets, MeshPaint, NavigationSystem, Paper2D, Projects, PropertyEditor, RenderCore, Slate, SlateCore, ToolMenus, ToolWidgets, UnrealEd, WorkspaceMenuStructure
- PrivateIncludePathModuleNames: LevelEditor, Settings
- PublicDependencyModuleNames: Json

### `Plugins/2D/Paper2D/Source/Paper2DEditor/Classes/PaperFlipbookActorFactory.h` (Public)


#### class `UPaperFlipbookActorFactory`  
`class UPaperFlipbookActorFactory : public UActorFactory`  
_L12-20_
- reflection: `UCLASS()`
- inherits: `UActorFactory`
- L17 _private prototype_ `virtual void PostSpawnActor(UObject* Asset, AActor* NewActor) override;`
- L18 _private prototype_ `virtual bool CanCreateActorFrom(const FAssetData& AssetData, FText& OutErrorMsg) override;`

### `Plugins/2D/Paper2D/Source/Paper2DEditor/Classes/PaperFlipbookFactory.h` (Public)


#### class `UPaperFlipbookFactory`  
`class UPaperFlipbookFactory : public UFactory`  
_L16-25_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UFactory`
- L20 _private member_ `TArray<FPaperFlipbookKeyFrame> KeyFrames;`
- L23 _private prototype_ `virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;` — UFactory interface

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API PAPER2DEDITOR_API`

### `Plugins/2D/Paper2D/Source/Paper2DEditor/Classes/PaperFlipbookThumbnailRenderer.h` (Public)


#### class `UPaperFlipbookThumbnailRenderer`  
`class UPaperFlipbookThumbnailRenderer : public UPaperSpriteThumbnailRenderer`  
_L12-19_
- reflection: `UCLASS()`
- inherits: `UPaperSpriteThumbnailRenderer`
- L17 _private prototype_ `virtual void Draw(UObject* Object, int32 X, int32 Y, uint32 Width, uint32 Height, FRenderTarget*, FCanvas* Canvas, bool bAdditionalViewFamily) override;` — UThumbnailRenderer interface

### `Plugins/2D/Paper2D/Source/Paper2DEditor/Classes/PaperImporterSettings.h` (Public)


#### enum `ESpriteInitMaterialLightingMode`  
`enum class ESpriteInitMaterialLightingMode : uint8`  
_L19-29_
- L22 _public enumerator_ `Automatic` — Use the default in the importer settings
- L25 _public enumerator_ `ForceUnlit` — Force unlit
- L28 _public enumerator_ `ForceLit` — Force lit

#### enum `ESpriteInitMaterialType`  
`enum class ESpriteInitMaterialType : uint8`  
_L31-47_
- L34 _public enumerator_ `LeaveAsIs` — Leave the material alone
- L37 _public enumerator_ `Automatic` — Use the default in the importer settings (typically auto-analyze)
- L40 _public enumerator_ `Masked` — Force masked
- L43 _public enumerator_ `Translucent` — Force translucent
- L46 _public enumerator_ `Opaque` — Force opaque

#### class `UPaperImporterSettings`  
`class UPaperImporterSettings : public UObject`  
_L53-161_
- reflection: `UCLASS(MinimalAPI, config=Editor, defaultconfig)`
- inherits: `UObject`
- desc: Implements the settings for imported Paper2D assets, such as sprite sheet textures.
- L60 _protected member_ `bool bPickBestMaterialWhenCreatingSprites;` — `UPROPERTY(config, EditAnywhere, Category=NewAssetSettings)` — Should the source texture be scanned when creating new sprites to determine the appropriate material? (if false, the Default Masked Material is always used)
- L64 _protected member_ `bool bPickBestMaterialWhenCreatingTileMaps;` — `UPROPERTY(config, EditAnywhere, Category=NewAssetSettings)` — Should the source texture be scanned when creating new tile maps (from a tile set or via importing) to determine the appropriate material? (if false, the Default Masked Material is always used)
- L68 _protected member_ `bool bAnalysisCanUseOpaque;` — `UPROPERTY(config, EditAnywhere, Category=NewAssetSettings)` — Can opaque materials be applied as part of the 'best material' analysis?
- L72 _protected member_ `float DefaultPixelsPerUnrealUnit;` — `UPROPERTY(config, EditAnywhere, Category=NewAssetSettings)` — The default scaling factor between pixels and Unreal units (cm) to use for newly created sprite assets (e.g., 0.64 would make a 64 pixel wide sprite take up 100 cm)
- L76 _protected member_ `TArray<FString> NormalMapTextureSuffixes;` — `UPROPERTY(config, EditAnywhere, Category=ImportSettings)` — A list of default suffixes to use when looking for associated normal maps while importing sprites or creating sprites from textures
- L80 _protected member_ `TArray<FString> BaseMapTextureSuffixes;` — `UPROPERTY(config, EditAnywhere, Category=ImportSettings)` — The default suffix to remove (if present) from a texture name before looking for an associated normal map using NormalMapTextureSuffixes
- L84 _protected member_ `TEnumAsByte<TextureGroup> DefaultSpriteTextureGroup;` — `UPROPERTY(config, EditAnywhere, Category=ImportSettings)` — The default texture group for imported sprite textures, tile sheets, etc... (typically set to UI for 'modern 2D' or 2D pixels for 'retro 2D')
- L88 _protected member_ `bool bOverrideTextureCompression;` — `UPROPERTY(config, EditAnywhere, Category=ImportSettings)` — Should texture compression settings be overridden on imported sprite textures, tile sheets, etc...?
- L93 _protected member_ `TEnumAsByte<TextureCompressionSettings> DefaultSpriteTextureCompression;` — `UPROPERTY(config, EditAnywhere, Category=ImportSettings, meta=(EditCondition=bOverrideTextureCompression))` — Compression settings to use when building the texture. The default texture group for imported sprite textures, tile sheets, etc... (typically set to UI for 'modern 2D' or 2D pixels for 'retro 2D')
- L97 _protected member_ `FSoftObjectPath UnlitDefaultMaskedMaterialName;` — `UPROPERTY(config, EditAnywhere, Category=MaterialSettings, meta=(AllowedClasses="/Script/Engine.MaterialInterface", DisplayName="Unlit Default Masked Material"))` — The unlit default masked material for newly created sprites (masked means binary opacity: things are either opaque or see-thru, with nothing in between)
- L101 _protected member_ `FSoftObjectPath UnlitDefaultTranslucentMaterialName;` — `UPROPERTY(config, EditAnywhere, Category=MaterialSettings, meta=(AllowedClasses="/Script/Engine.MaterialInterface", DisplayName="Unlit Default Translucent Material"))` — The unlit default translucent material for newly created sprites (translucent means smooth opacity which can vary continuously from 0..1, but translucent rendering is more expensive that opaque or masked rendering and has different sorting rules)
- L105 _protected member_ `FSoftObjectPath UnlitDefaultOpaqueMaterialName;` — `UPROPERTY(config, EditAnywhere, Category=MaterialSettings, meta=(AllowedClasses="/Script/Engine.MaterialInterface", DisplayName="Unlit Default Opaque Sprite Material"))` — The unlit default opaque material for newly created sprites
- L109 _protected member_ `FSoftObjectPath LitDefaultMaskedMaterialName;` — `UPROPERTY(config, EditAnywhere, Category=MaterialSettings, meta=(AllowedClasses="/Script/Engine.MaterialInterface", DisplayName="Lit Default Masked Material"))` — The lit default masked material for newly created sprites (masked means binary opacity: things are either opaque or see-thru, with nothing in between)
- L113 _protected member_ `FSoftObjectPath LitDefaultTranslucentMaterialName;` — `UPROPERTY(config, EditAnywhere, Category=MaterialSettings, meta=(AllowedClasses="/Script/Engine.MaterialInterface", DisplayName="Lit Default Translucent Material"))` — The lit default translucent material for newly created sprites (translucent means smooth opacity which can vary continuously from 0..1, but translucent rendering is more expensive that opaque or masked rendering and has different sorting rules)
- L117 _protected member_ `FSoftObjectPath LitDefaultOpaqueMaterialName;` — `UPROPERTY(config, EditAnywhere, Category=MaterialSettings, meta=(AllowedClasses="/Script/Engine.MaterialInterface", DisplayName="Lit Default Opaque Material"))` — The lit default opaque material for newly created sprites
- L120 _public prototype_ `UPaperImporterSettings();`
- L123 _public function_ `bool ShouldPickBestMaterialWhenCreatingTileMaps() const` — Should the source texture be scanned when creating new tile maps (from a tile set or via importing) to determine the appropriate material? (if false, the Default Masked Material is always used)
- L126 _public prototype_ `FString RemoveSuffixFromBaseMapName(const FString& InName) const;` — Removes the suffix from the specified name if it matches something in BaseMapTextureSuffixes
- L129 _public prototype_ `void GenerateNormalMapNamesToTest(const FString& InRoot, TArray<FString>& InOutNames) const;` — Generates names to test for a normal map using NormalMapTextureSuffixes
- L132 _public prototype_ `void ApplyTextureSettings(UTexture2D* Texture) const;` — Applies the compression settings to the specified texture
- L136 _public prototype_ `void ApplySettingsForSpriteInit(FSpriteAssetInitParameters& InitParams, ESpriteInitMaterialLightingMode LightingMode = ESpriteInitMaterialLightingMode::Automatic, ESpriteInitMaterialType MaterialTypeMode = ESpriteInitMaterialType::Automatic) const;` — Fills out the sprite init parameters with the default settings given the desired material type and lighting mode (which can both be automatic) Note: This should be called after the texture has been set, as that will be analyzed if the lighting/material type flags are set to automatic
- L139 _public prototype_ `void ApplySettingsForTileMapInit(UPaperTileMap* TileMap, UPaperTileSet* DefaultTileSet = nullptr, ESpriteInitMaterialLightingMode LightingMode = ESpriteInitMaterialLightingMode::Automatic, ESpriteInitMaterialType MaterialTypeMode = ESpriteInitMaterialType::Automatic, bool bCreateEmptyLayer = true) const;` — Fills out the tile map with the default settings given the desired material type and lighting mode (which can both be automatic)
- L144 _public prototype_ `ESpriteInitMaterialType AnalyzeTextureForDesiredMaterialType(UTexture* Texture, const FIntPoint& Offset, const FIntPoint& Dimensions) const;` — Analyzes the specified texture in the Offset..Offset+Dimensions region and returns the best kind of material to represent the alpha content in the texture (typically masked or translucent, but can return opaque if bAnalysisCanUseOpaque is true Note: Will return Automatic if the texture is null.
- L147 _public prototype_ `UMaterialInterface* GetDefaultTranslucentMaterial(bool bLit) const;` — Returns the default translucent material
- L150 _public prototype_ `UMaterialInterface* GetDefaultOpaqueMaterial(bool bLit) const;` — Returns the default opaque material
- L153 _public prototype_ `UMaterialInterface* GetDefaultMaskedMaterial(bool bLit) const;` — Returns the default masked material
- L157 _public prototype_ `UMaterialInterface* GetDefaultMaterial(ESpriteInitMaterialType MaterialType, bool bUseLitMaterial) const;` — Returns the default material for the specified material type. Input should be Masked, Opaque, or Translucent.  Automatic and LeaveAsIs will be treated like masked!
- L160 _public function_ `float GetDefaultPixelsPerUnrealUnit() const` — Returns the default pixels/uu setting

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API PAPER2DEDITOR_API`

### `Plugins/2D/Paper2D/Source/Paper2DEditor/Classes/PaperSpriteActorFactory.h` (Public)


#### class `UPaperSpriteActorFactory`  
`class UPaperSpriteActorFactory : public UActorFactory`  
_L12-20_
- reflection: `UCLASS()`
- inherits: `UActorFactory`
- L17 _private prototype_ `virtual void PostSpawnActor(UObject* Asset, AActor* NewActor) override;`
- L18 _private prototype_ `virtual bool CanCreateActorFrom(const FAssetData& AssetData, FText& OutErrorMsg) override;`

### `Plugins/2D/Paper2D/Source/Paper2DEditor/Classes/PaperSpriteFactory.h` (Public)


#### class `UPaperSpriteFactory`  
`class UPaperSpriteFactory : public UFactory`  
_L13-29_
- reflection: `UCLASS()`
- inherits: `UFactory`
- L18 _private member_ `class UTexture2D* InitialTexture;` — Initial texture to create the sprite from (Can be nullptr)
- L21 _private member_ `bool bUseSourceRegion;` — Set bUseSourceRegion to get it to use/set initial sourceUV and dimensions
- L22 _private member_ `FIntPoint InitialSourceUV;`
- L23 _private member_ `FIntPoint InitialSourceDimension;`
- L26 _private prototype_ `virtual bool ConfigureProperties() override;` — UFactory interface
- L27 _private prototype_ `virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;`

### `Plugins/2D/Paper2D/Source/Paper2DEditor/Classes/PaperSpriteThumbnailRenderer.h` (Public)


#### class `UPaperSpriteThumbnailRenderer`  
`class UPaperSpriteThumbnailRenderer : public UDefaultSizedThumbnailRenderer`  
_L12-24_
- reflection: `UCLASS()`
- inherits: `UDefaultSizedThumbnailRenderer`
- L17 _private prototype_ `virtual void Draw(UObject* Object, int32 X, int32 Y, uint32 Width, uint32 Height, FRenderTarget*, FCanvas* Canvas, bool bAdditionalViewFamily) override;` — UThumbnailRenderer interface
- L21 _protected prototype_ `void DrawFrame(class UPaperSprite* Sprite, int32 X, int32 Y, uint32 Width, uint32 Height, FRenderTarget*, FCanvas* Canvas, FBoxSphereBounds* OverrideRenderBounds);`
- L23 _protected prototype_ `void DrawGrid(int32 X, int32 Y, uint32 Width, uint32 Height, FCanvas* Canvas);`

### `Plugins/2D/Paper2D/Source/Paper2DEditor/Classes/PaperTileMapFactory.h` (Public)


#### class `UPaperTileMapFactory`  
`class UPaperTileMapFactory : public UFactory`  
_L13-23_
- reflection: `UCLASS()`
- inherits: `UFactory`
- L18 _private member_ `class UPaperTileSet* InitialTileSet;` — Initial tile set to create the tile map from (Can be nullptr)
- L21 _private prototype_ `virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;` — UFactory interface

### `Plugins/2D/Paper2D/Source/Paper2DEditor/Classes/PaperTileMapPromotionFactory.h` (Public)


#### class `UPaperTileMapPromotionFactory`  
`class UPaperTileMapPromotionFactory : public UFactory`  
_L13-24_
- reflection: `UCLASS()`
- inherits: `UFactory`
- L19 _private member_ `TObjectPtr<class UPaperTileMap> AssetToRename;` — `UPROPERTY()` — Object being promoted to an asset
- L22 _private prototype_ `virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;` — UFactory interface

### `Plugins/2D/Paper2D/Source/Paper2DEditor/Classes/PaperTileSetFactory.h` (Public)


#### class `UPaperTileSetFactory`  
`class UPaperTileSetFactory : public UFactory`  
_L13-23_
- reflection: `UCLASS()`
- inherits: `UFactory`
- L18 _private member_ `class UTexture2D* InitialTexture;` — Initial texture to create the tile set from (Can be nullptr)
- L21 _private prototype_ `virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;` — UFactory interface

### `Plugins/2D/Paper2D/Source/Paper2DEditor/Classes/PaperTileSetThumbnailRenderer.h` (Public)


#### class `UPaperTileSetThumbnailRenderer`  
`class UPaperTileSetThumbnailRenderer : public UDefaultSizedThumbnailRenderer`  
_L12-19_
- reflection: `UCLASS()`
- inherits: `UDefaultSizedThumbnailRenderer`
- L17 _private prototype_ `virtual void Draw(UObject* Object, int32 X, int32 Y, uint32 Width, uint32 Height, FRenderTarget*, FCanvas* Canvas, bool bAdditionalViewFamily) override;` — UThumbnailRenderer interface

### `Plugins/2D/Paper2D/Source/Paper2DEditor/Classes/TerrainSplineActorFactory.h` (Public)


#### class `UTerrainSplineActorFactory`  
`class UTerrainSplineActorFactory : public UActorFactory`  
_L12-20_
- reflection: `UCLASS()`
- inherits: `UActorFactory`
- L17 _private prototype_ `virtual void PostSpawnActor(UObject* Asset, AActor* NewActor) override;` — UActorFactory interface
- L18 _private prototype_ `virtual bool CanCreateActorFrom(const FAssetData& AssetData, FText& OutErrorMsg) override;`

### `Plugins/2D/Paper2D/Source/Paper2DEditor/Classes/TileMapActorFactory.h` (Public)


#### class `UTileMapActorFactory`  
`class UTileMapActorFactory : public UActorFactory`  
_L12-20_
- reflection: `UCLASS()`
- inherits: `UActorFactory`
- L17 _private prototype_ `virtual void PostSpawnActor(UObject* Asset, AActor* NewActor) override;` — UActorFactory interface
- L18 _private prototype_ `virtual bool CanCreateActorFrom(const FAssetData& AssetData, FText& OutErrorMsg) override;`

### `Plugins/2D/Paper2D/Source/Paper2DEditor/Classes/TileMapAssetImportData.h` (Public)


#### struct `FTileSetImportMapping`  
`struct FTileSetImportMapping`  
_L13-25_
- reflection: `USTRUCT()`
- L18 _public member_ `FString SourceName;` — `UPROPERTY()`
- L21 _public member_ `TWeakObjectPtr<class UPaperTileSet> ImportedTileSet;` — `UPROPERTY()`
- L24 _public member_ `TWeakObjectPtr<class UTexture> ImportedTexture;` — `UPROPERTY()`

#### class `UTileMapAssetImportData`  
`class UTileMapAssetImportData : public UAssetImportData`  
_L31-39_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAssetImportData`
- desc: Base class for import data and options used when importing a tile map
- L36 _private member_ `TArray<FTileSetImportMapping> TileSetMap;` — `UPROPERTY()`
- L38 _private prototype_ `static UTileMapAssetImportData* GetImportDataForTileMap(class UPaperTileMap* TileMap);`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API PAPER2DEDITOR_API`

### `Plugins/2D/Paper2D/Source/Paper2DEditor/Private/Atlasing/AtlasAssetTypeActions.h` (Private)


#### class `FAtlasAssetTypeActions`  
`class FAtlasAssetTypeActions : public FAssetTypeActions_Base`  
_L9-25_
- inherits: `FAssetTypeActions_Base`
- L12 _public prototype_ `FAtlasAssetTypeActions(EAssetTypeCategories::Type InAssetCategory);`
- L15 _public prototype_ `virtual FText GetName() const override;` — IAssetTypeActions interface
- L16 _public prototype_ `virtual FColor GetTypeColor() const override;`
- L17 _public prototype_ `virtual UClass* GetSupportedClass() const override;`
- L18 _public prototype_ `virtual void OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<class IToolkitHost> EditWithinLevelEditor = TSharedPtr<IToolkitHost>()) override;`
- L19 _public prototype_ `virtual uint32 GetCategories() override;`
- L20 _public prototype_ `virtual FText GetAssetDescription(const FAssetData& AssetData) const override;`
- L24 _private member_ `EAssetTypeCategories::Type MyAssetCategory;`

### `Plugins/2D/Paper2D/Source/Paper2DEditor/Private/Atlasing/PaperAtlasGenerator.h` (Private)


#### struct `FPaperAtlasGenerator`  
`struct FPaperAtlasGenerator`  
_L13-17_
- L16 _public prototype_ `static void HandleAssetChangedEvent(UPaperSpriteAtlas* Atlas);`

### `Plugins/2D/Paper2D/Source/Paper2DEditor/Private/Atlasing/PaperAtlasHelpers.h` (Private)


#### Free symbols / members of external scopes

- L14 _function_ `static void LoadAllReferencedSprites(UPaperSpriteAtlas* AtlasGroup, TArray<UPaperSprite*>& AllSprites)` — Loads and returns a list of sprites referenced in the atlas group (i.e. sprites used in the previous build)
- L31 _function_ `static void LoadAllSpritesWithAtlasGroupGUID(UPaperSpriteAtlas* Atlas, TArray<UPaperSprite*>& SpritesInNewAtlas)` — Find all sprites that reference the atlas and force them loaded
- L54 _function_ `static int32 CreateEmptySlot(TArray<FPaperSpriteAtlasSlot>& Slots, int32 AtlasIndex, int32 X, int32 Y, int32 Width, int32 Height)` — Create an empty slot and return the slot index Returns -1 if the slot can't be created for any reason (eg. width and height too small)
- L74 _function_ `static void InsertSpriteIntoSlot(TArray<FPaperSpriteAtlasSlot>& Slots, int SlotIndexToInsertInto, UPaperSprite* Sprite, int32 Width, int32 Height)` — Insert a sprite into a specified The sprite must be known to fit in the provided slot
- L98 _function_ `static void MergeAdjacentRects(UPaperSpriteAtlas* AtlasGroup)`
- L103 _function_ `static void RemoveTextureSlotWithSprite(UPaperSpriteAtlas* AtlasGroup, UPaperSprite* Sprite)`
- L117 _function_ `static int NumTexturesUsedInAtlasSlots(const TArray<FPaperSpriteAtlasSlot>& AtlasSlots)` — Calculate the number of textures used in the atlas slots (atlas indices could be sparse)
- L130 _function_ `static const FPaperSpriteAtlasSlot& FindBestSlotForTexture(TArray<FPaperSpriteAtlasSlot>& AtlasSlots, int32 AtlasWidth, int32 AtlasHeight, UPaperSprite* Sprite, int32 Width, int32 Height, bool& bOutSpriteChanged)` — FindBestSlotForTexture NOTE: Assumes all UPaperSprites have been loaded

### `Plugins/2D/Paper2D/Source/Paper2DEditor/Private/Atlasing/PaperAtlasTextureHelpers.h` (Private)


#### struct `FPaperAtlasTextureHelpers`  
`struct FPaperAtlasTextureHelpers`  
_L12-36_
- L16 _public prototype_ `static void CopyTextureData(const uint8* Source, uint8* Dest, uint32 SizeX, uint32 SizeY, uint32 BytesPerPixel, uint32 SourceStride, uint32 DestStride);` — Copy texture data from one 32bpp image to another
- L19 _public prototype_ `static bool ReadSpriteTexture(UTexture* SourceTexture, const FIntPoint& SourceXY, const FIntPoint& SourceSize, TArray<uint8>& TargetBuffer);` — Read sprite data into the 4 bytes per pixel target array
- L22 _public prototype_ `static void PadSprite(const FPaperSpriteAtlasSlot& Slot, EPaperSpriteAtlasPadding PaddingType, int32 Padding, const FIntPoint& SpriteSize, int32 AtlasWidth, int32 AtlasBytesPerPixel, TArray<uint8>& TextureData);` — Fills the padding space with the correct values
- L25 _public prototype_ `static void CopySpriteToAtlasTextureData(TArray<uint8>& TextureData, int32 AtlasWidth, int32 AtlasHeight, int32 AtlasBytesPerPixel, EPaperSpriteAtlasPadding PaddingType, int32 Padding, UPaperSprite* Sprite, const FPaperSpriteAtlasSlot& Slot);` — Copies the sprite texture data at the position described by slot
- L28 _public prototype_ `static void CopyTextureRegionToAtlasTextureData(TArray<uint8>& TextureData, int32 AtlasWidth, int32 AtlasHeight, int32 AtlasBytesPerPixel, EPaperSpriteAtlasPadding PaddingType, int32 Padding, TArray<uint8>& SourceData, const FIntPoint& SourceSize, const FPaperSpriteAtlasSlot& Slot);` — Copies the texture data at the position described by slot
- L30 _public prototype_ `static int32 ClampMips(int Width, int Height, int MipCount);`
- L32 _public prototype_ `static void GenerateMipChainARGB(const TArray<FPaperSpriteAtlasSlot>& Slots, TArray<uint8>& AtlasTextureData, int32 MipCount, int32 Width, int32 Height);`
- L35 _private function_ `FPaperAtlasTextureHelpers()`

### `Plugins/2D/Paper2D/Source/Paper2DEditor/Private/Atlasing/PaperSpriteAtlasFactory.h` (Private)


#### class `UPaperSpriteAtlasFactory`  
`class UPaperSpriteAtlasFactory : public UFactory`  
_L9-17_
- reflection: `UCLASS()`
- inherits: `UFactory`
- L14 _private prototype_ `virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;` — UFactory interface
- L15 _private prototype_ `virtual bool CanCreateNew() const override;`

### `Plugins/2D/Paper2D/Source/Paper2DEditor/Private/ContentBrowserExtensions/ContentBrowserExtensions.h` (Private)


#### class `FPaperContentBrowserExtensions`  
`class FPaperContentBrowserExtensions`  
_L7-12_
- desc: Integrate Paper2D actions associated with existing engine types (e.g., Texture2D) into the content browser
- L10 _public prototype_ `static void InstallHooks();`
- L11 _public prototype_ `static void RemoveHooks();`

### `Plugins/2D/Paper2D/Source/Paper2DEditor/Private/ExtractSprites/PaperExtractSpritesSettings.h` (Private)


#### enum `ESpriteExtractMode`  
`enum class ESpriteExtractMode : uint8`  
_L8-15_
- reflection: `UENUM()`
- L11 _public enumerator_ `Auto` — Automatically extract sprites by detecting using alpha
- L14 _public enumerator_ `Grid` — Extract sprites in a grid defined in the properties below

#### class `UPaperExtractSpritesSettings`  
`class UPaperExtractSpritesSettings : public UObject`  
_L23-53_
- reflection: `UCLASS()`
- inherits: `UObject`
- L30 _public member_ `ESpriteExtractMode SpriteExtractMode;` — `UPROPERTY(Category = Settings, EditAnywhere)` — Sprite extract mode
- L34 _public member_ `FLinearColor OutlineColor;` — `UPROPERTY(Category = Settings, EditAnywhere, meta=(HideAlphaChannel))` — The color of the sprite boundary outlines
- L38 _public member_ `FLinearColor ViewportTextureTint;` — `UPROPERTY(Category = Settings, EditAnywhere)` — Apply a tint to the texture in the viewport to improve outline visibility in this editor
- L42 _public member_ `FLinearColor BackgroundColor;` — `UPROPERTY(Category = Settings, EditAnywhere, meta=(HideAlphaChannel))` — The viewport background color
- L46 _public member_ `FString NamingTemplate;` — `UPROPERTY(Category = Naming, EditAnywhere)` — The name of the sprite that will be created. {0} will get replaced by the sprite number.
- L50 _public member_ `int32 NamingStartIndex;` — `UPROPERTY(Category = Naming, EditAnywhere)` — The number to start naming with
- L52 _public prototype_ `UPaperExtractSpritesSettings(const FObjectInitializer& ObjectInitializer);`

#### class `UPaperExtractSpriteGridSettings`  
`class UPaperExtractSpriteGridSettings : public UObject`  
_L56-97_
- reflection: `UCLASS()`
- inherits: `UObject`
- L66 _public member_ `int32 CellWidth = 64;` — `UPROPERTY(Category = Grid, EditAnywhere, meta = (UIMin = 1, ClampMin = 1))` — The width of each sprite in grid mode
- L70 _public member_ `int32 CellHeight = 64;` — `UPROPERTY(Category = Grid, EditAnywhere, meta = (UIMin = 1, ClampMin = 1))` — The height of each sprite in grid mode
- L74 _public member_ `int32 NumCellsX;` — `UPROPERTY(Category = Grid, EditAnywhere, meta = (UIMin = 0, ClampMin = 0))` — Number of cells extracted horizontally. Can be used to limit the number of sprites extracted. Set to 0 to extract all sprites
- L78 _public member_ `int32 NumCellsY;` — `UPROPERTY(Category = Grid, EditAnywhere, meta = (UIMin = 0, ClampMin = 0))` — Number of cells extracted vertically. Can be used to limit the number of sprites extracted. Set to 0 to extract all sprites
- L82 _public member_ `int32 MarginX;` — `UPROPERTY(Category = Grid, EditAnywhere, meta = (UIMin = 0, ClampMin = 0))` — Margin from the left of the texture to the first sprite
- L86 _public member_ `int32 MarginY;` — `UPROPERTY(Category = Grid, EditAnywhere, meta = (UIMin = 0, ClampMin = 0))` — Margin from the top of the texture to the first sprite
- L90 _public member_ `int32 SpacingX;` — `UPROPERTY(Category = Grid, EditAnywhere, meta = (UIMin = 0, ClampMin = 0))` — Horizontal spacing between sprites
- L94 _public member_ `int32 SpacingY;` — `UPROPERTY(Category = Grid, EditAnywhere, meta = (UIMin = 0, ClampMin = 0))` — Vertical spacing between sprites
- L96 _public prototype_ `UPaperExtractSpriteGridSettings(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());`

### `Plugins/2D/Paper2D/Source/Paper2DEditor/Private/ExtractSprites/SPaperExtractSpritesDialog.h` (Private)


#### struct `FPaperExtractedSprite`  
`struct FPaperExtractedSprite`  
_L13-17_
- L15 _public member_ `FString Name;`
- L16 _public member_ `FIntRect Rect;`

#### class `SPaperExtractSpritesDialog`  
`class SPaperExtractSpritesDialog : public SCompoundWidget`  
_L22-65_
- inherits: `SCompoundWidget`
- L25 _public function_ `SLATE_BEGIN_ARGS(SPaperExtractSpritesDialog)`
- L26 _public prototype_ `SLATE_END_ARGS()`
- L31 _public prototype_ `virtual ~SPaperExtractSpritesDialog();`
- L34 _public prototype_ `static bool ShowWindow(UTexture2D* SourceTexture);` — Show the dialog, returns true if successfully extracted sprites
- L38 _private prototype_ `FReply ExtractClicked();` — Handler for Extract button
- L41 _private prototype_ `FReply CancelClicked();` — Handler for Cancel button
- L42 _private prototype_ `void OnFinishedChangingProperties(const FPropertyChangedEvent& PropertyChangedEvent);`
- L43 _private prototype_ `void CloseContainingWindow();`
- L46 _private prototype_ `void PreviewExtractedSprites();` — Calculate a list of extracted sprite rects
- L49 _private prototype_ `void CreateExtractedSprites();` — Actually create extracted sprites
- L52 _private prototype_ `void SetDetailsViewForActiveMode();` — Sets the details panel appropriately for the currently selected panel
- L56 _private member_ `UTexture2D* SourceTexture;` — Source texture to extract from
- L57 _private member_ `bool bDirtyExtractedSprites;`
- L59 _private member_ `class UPaperExtractSpritesSettings* ExtractSpriteSettings;`
- L60 _private member_ `class UPaperExtractSpriteGridSettings* ExtractSpriteGridSettings;`
- L62 _private member_ `TSharedPtr<class IDetailsView> MainPropertyView;`
- L63 _private member_ `TSharedPtr<class IDetailsView> DetailsPropertyView;`
- L64 _private member_ `TArray<FPaperExtractedSprite> ExtractedSprites;`

#### class `SPaperExtractSpritesViewport`  
`class SPaperExtractSpritesViewport : public SPaperEditorViewport`  
_L71-89_
- inherits: `SPaperEditorViewport`
- L74 _public function_ `SLATE_BEGIN_ARGS(SPaperExtractSpritesViewport)`
- L77 _public prototype_ `~SPaperExtractSpritesViewport();`
- L78 _public prototype_ `void Construct(const FArguments& InArgs, UTexture2D* Texture, const TArray<FPaperExtractedSprite>& ExtractedSprites, const class UPaperExtractSpritesSettings* Settings, class SPaperExtractSpritesDialog* InDialog);`
- L82 _protected prototype_ `virtual FText GetTitleText() const override;` — SPaperEditorViewport interface
- L86 _private member_ `TWeakObjectPtr<class UTexture2D> TexturePtr;`
- L87 _private member_ `TSharedPtr<class FPaperExtractSpritesViewportClient> TypedViewportClient;`
- L88 _private member_ `class SPaperExtractSpritesDialog* Dialog;`

### `Plugins/2D/Paper2D/Source/Paper2DEditor/Private/FlipbookAssetTypeActions.h` (Private)


#### class `FFlipbookAssetTypeActions`  
`class FFlipbookAssetTypeActions : public FAssetTypeActions_Base`  
_L7-22_
- inherits: `FAssetTypeActions_Base`
- L10 _public prototype_ `FFlipbookAssetTypeActions(EAssetTypeCategories::Type InAssetCategory);`
- L13 _public prototype_ `virtual FText GetName() const override;` — IAssetTypeActions interface
- L14 _public prototype_ `virtual FColor GetTypeColor() const override;`
- L15 _public prototype_ `virtual UClass* GetSupportedClass() const override;`
- L16 _public prototype_ `virtual void OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<class IToolkitHost> EditWithinLevelEditor = TSharedPtr<IToolkitHost>()) override;`
- L17 _public prototype_ `virtual uint32 GetCategories() override;`
- L21 _private member_ `EAssetTypeCategories::Type MyAssetCategory;`

### `Plugins/2D/Paper2D/Source/Paper2DEditor/Private/FlipbookEditor/FlipbookComponentDetailsCustomization.h` (Private)


#### class `FFlipbookComponentDetailsCustomization`  
`class FFlipbookComponentDetailsCustomization : public IDetailCustomization`  
_L12-21_
- inherits: `IDetailCustomization`
- L16 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L19 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailLayout) override;` — IDetailCustomization interface

### `Plugins/2D/Paper2D/Source/Paper2DEditor/Private/FlipbookEditor/FlipbookEditor.h` (Private)


#### class `FFlipbookEditor`  
`class FFlipbookEditor : public FAssetEditorToolkit, public FGCObject`  
_L17-135_
- inherits: `FAssetEditorToolkit,FGCObject`
- L20 _public prototype_ `FFlipbookEditor();`
- L23 _public prototype_ `virtual void RegisterTabSpawners(const TSharedRef<FTabManager>& TabManager) override;` — IToolkit interface
- L24 _public prototype_ `virtual void UnregisterTabSpawners(const TSharedRef<FTabManager>& TabManager) override;`
- L28 _public prototype_ `virtual FName GetToolkitFName() const override;` — FAssetEditorToolkit
- L29 _public prototype_ `virtual FText GetBaseToolkitName() const override;`
- L30 _public prototype_ `virtual FText GetToolkitName() const override;`
- L31 _public prototype_ `virtual FText GetToolkitToolTipText() const override;`
- L32 _public prototype_ `virtual FLinearColor GetWorldCentricTabColorScale() const override;`
- L33 _public prototype_ `virtual FString GetWorldCentricTabPrefix() const override;`
- L34 _public prototype_ `virtual FString GetDocumentationLink() const override;`
- L38 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;` — FSerializableObject interface
- L39 _public function_ `virtual FString GetReferencerName() const override`
- L46 _public prototype_ `void InitFlipbookEditor(const EToolkitMode::Type Mode, const TSharedPtr< IToolkitHost >& InitToolkitHost, UPaperFlipbook* InitSprite);`
- L48 _public function_ `UPaperFlipbook* GetFlipbookBeingEdited() const`
- L50 _public prototype_ `UPaperFlipbookComponent* GetPreviewComponent() const;`
- L52 _protected member_ `TObjectPtr<UPaperFlipbook> FlipbookBeingEdited;`
- L54 _protected member_ `TSharedPtr<SFlipbookEditorViewport> ViewportPtr;`
- L57 _protected member_ `int32 CurrentSelectedKeyframe;` — Selection set
- L60 _protected member_ `mutable float ViewInputMin;` — Range of times currently being viewed
- L61 _protected member_ `mutable float ViewInputMax;`
- L62 _protected member_ `mutable float LastObservedSequenceLength;`
- L65 _protected function_ `float GetFramesPerSecond() const`
- L70 _protected function_ `int32 GetCurrentFrame() const`
- L84 _protected function_ `void SetCurrentFrame(int32 NewIndex)`
- L99 _protected prototype_ `void BindCommands();`
- L100 _protected prototype_ `void ExtendMenu();`
- L101 _protected prototype_ `void ExtendToolbar();`
- L103 _protected prototype_ `TSharedRef<SDockTab> SpawnTab_Viewport(const FSpawnTabArgs& Args);`
- L104 _protected prototype_ `TSharedRef<SDockTab> SpawnTab_Details(const FSpawnTabArgs& Args);`
- L106 _protected prototype_ `void DeleteSelection();`
- L107 _protected prototype_ `void DuplicateSelection();`
- L108 _protected prototype_ `void SetSelection(int32 NewSelection);`
- L109 _protected prototype_ `bool HasValidSelection() const;`
- L111 _protected prototype_ `void AddKeyFrameAtCurrentTime();`
- L112 _protected prototype_ `void AddNewKeyFrameAtEnd();`
- L113 _protected prototype_ `void AddNewKeyFrameBefore();`
- L114 _protected prototype_ `void AddNewKeyFrameAfter();`
- L116 _protected prototype_ `FReply OnClick_Forward();`
- L117 _protected prototype_ `FReply OnClick_Forward_Step();`
- L118 _protected prototype_ `FReply OnClick_Forward_End();`
- L119 _protected prototype_ `FReply OnClick_Backward();`
- L120 _protected prototype_ `FReply OnClick_Backward_Step();`
- L121 _protected prototype_ `FReply OnClick_Backward_End();`
- L122 _protected prototype_ `FReply OnClick_ToggleLoop();`
- L124 _protected prototype_ `uint32 GetTotalFrameCount() const;`
- L125 _protected prototype_ `uint32 GetTotalFrameCountPlusOne() const;`
- L126 _protected prototype_ `float GetTotalSequenceLength() const;`
- L127 _protected prototype_ `float GetPlaybackPosition() const;`
- L128 _protected prototype_ `void SetPlaybackPosition(float NewTime);`
- L129 _protected prototype_ `bool IsLooping() const;`
- L130 _protected prototype_ `EPlaybackMode::Type GetPlaybackMode() const;`
- L132 _protected prototype_ `float GetViewRangeMin() const;`
- L133 _protected prototype_ `float GetViewRangeMax() const;`
- L134 _protected prototype_ `void SetViewRange(float NewMin, float NewMax);`

### `Plugins/2D/Paper2D/Source/Paper2DEditor/Private/FlipbookEditor/FlipbookEditorCommands.h` (Private)


#### class `FFlipbookEditorCommands`  
`class FFlipbookEditorCommands : public TCommands<FFlipbookEditorCommands>`  
_L9-46_
- inherits: `TCommands<FFlipbookEditorCommands>`
- L12 _public function_ `FFlipbookEditorCommands() : TCommands<FFlipbookEditorCommands>( TEXT("FlipbookEditor"),`
- L23 _public prototype_ `virtual void RegisterCommands() override;` — TCommand<> interface
- L27 _public member_ `TSharedPtr<FUICommandInfo> AddKeyFrame;`
- L29 _public member_ `TSharedPtr<FUICommandInfo> SetShowGrid;`
- L30 _public member_ `TSharedPtr<FUICommandInfo> SetShowBounds;`
- L31 _public member_ `TSharedPtr<FUICommandInfo> SetShowCollision;`
- L34 _public member_ `TSharedPtr<FUICommandInfo> SetShowPivot;` — View Menu Commands
- L35 _public member_ `TSharedPtr<FUICommandInfo> SetShowSockets;`
- L38 _public member_ `TSharedPtr<FUICommandInfo> AddNewFrame;` — Timeline commands
- L39 _public member_ `TSharedPtr<FUICommandInfo> AddNewFrameBefore;`
- L40 _public member_ `TSharedPtr<FUICommandInfo> AddNewFrameAfter;`
- L43 _public member_ `TSharedPtr<FUICommandInfo> PickNewSpriteFrame;` — Asset commands
- L44 _public member_ `TSharedPtr<FUICommandInfo> EditSpriteFrame;`
- L45 _public member_ `TSharedPtr<FUICommandInfo> ShowInContentBrowser;`

### `Plugins/2D/Paper2D/Source/Paper2DEditor/Private/FlipbookEditor/FlipbookEditorSettings.h` (Private)


#### class `UFlipbookEditorSettings`  
`class UFlipbookEditorSettings : public UObject`  
_L9-23_
- reflection: `UCLASS(config=EditorPerProjectUserSettings)`
- inherits: `UObject`
- desc: Settings for the Paper2D sprite editor
- L14 _public prototype_ `UFlipbookEditorSettings();`
- L18 _public member_ `FColor BackgroundColor;` — `UPROPERTY(config, EditAnywhere, Category=Background, meta=(HideAlphaChannel))` — Background color in the flipbook editor
- L22 _public member_ `bool bShowGridByDefault;` — `UPROPERTY(config, EditAnywhere, Category=Background)` — Should the grid be shown by default when the editor is opened?

### `Plugins/2D/Paper2D/Source/Paper2DEditor/Private/FlipbookEditor/FlipbookEditorViewportClient.h` (Private)


#### class `FFlipbookEditorViewportClient`  
`class FFlipbookEditorViewportClient : public FPaperEditorViewportClient`  
_L14-66_
- inherits: `FPaperEditorViewportClient`
- L18 _public prototype_ `FFlipbookEditorViewportClient(const TAttribute<class UPaperFlipbook*>& InFlipbookBeingEdited);` — Constructor
- L21 _public prototype_ `virtual void Draw(const FSceneView* View, FPrimitiveDrawInterface* PDI) override;` — FViewportClient interface
- L22 _public prototype_ `virtual void DrawCanvas(FViewport& InViewport, FSceneView& View, FCanvas& Canvas) override;`
- L23 _public prototype_ `virtual void Tick(float DeltaSeconds) override;`
- L27 _public prototype_ `virtual bool InputKey(const FInputKeyEventArgs& EventArgs) override;` — FEditorViewportClient interface
- L28 _public prototype_ `virtual FLinearColor GetBackgroundColor() const override;`
- L31 _public function_ `void ToggleShowPivot()`
- L32 _public function_ `bool IsShowPivotChecked() const`
- L34 _public function_ `void ToggleShowSockets()`
- L35 _public function_ `bool IsShowSocketsChecked() const`
- L37 _public function_ `UPaperFlipbookComponent* GetPreviewComponent() const`
- L44 _protected prototype_ `virtual FBox GetDesiredFocusBounds() const override;` — FPaperEditorViewportClient interface
- L50 _private member_ `FPreviewScene OwnedPreviewScene;` — The preview scene
- L53 _private member_ `TAttribute<class UPaperFlipbook*> FlipbookBeingEdited;` — The flipbook being displayed in this client
- L56 _private member_ `TWeakObjectPtr<class UPaperFlipbook> FlipbookBeingEditedLastFrame;` — A cached pointer to the flipbook that was being edited last frame. Used for invalidation reasons.
- L59 _private member_ `TWeakObjectPtr<UPaperFlipbookComponent> AnimatedRenderComponent;` — Render component for the sprite being edited
- L62 _private member_ `bool bShowPivot;` — Should we show the sprite pivot?
- L65 _private member_ `bool bShowSockets;` — Should we show sockets?

### `Plugins/2D/Paper2D/Source/Paper2DEditor/Private/FlipbookEditor/SFlipbookEditorViewportToolbar.h` (Private)


#### class `SFlipbookEditorViewportToolbar`  
`class SFlipbookEditorViewportToolbar : public SCommonEditorViewportToolbarBase`  
_L8-19_
- inherits: `SCommonEditorViewportToolbarBase`
- desc: In-viewport toolbar widget used in the flipbook editor
- L11 _public function_ `SLATE_BEGIN_ARGS(SFlipbookEditorViewportToolbar)`
- L12 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedPtr<class ICommonEditorViewportToolbarInfoProvider> InInfoProvider);`
- L17 _public prototype_ `virtual TSharedRef<SWidget> GenerateShowMenu() const override;` — SCommonEditorViewportToolbarBase interface

### `Plugins/2D/Paper2D/Source/Paper2DEditor/Private/FlipbookEditor/SFlipbookTimeline.h` (Private)


#### class `SFlipbookTimeline`  
`class SFlipbookTimeline : public SCompoundWidget`  
_L19-70_
- inherits: `SCompoundWidget`
- L22 _public function_ `SLATE_BEGIN_ARGS(SFlipbookTimeline) : _FlipbookBeingEdited(nullptr) , _PlayTime(0)`
- L27 _public prototype_ `SLATE_ATTRIBUTE(class UPaperFlipbook*, FlipbookBeingEdited) SLATE_ATTRIBUTE(float, PlayTime) SLATE_EVENT(FOnFlipbookKeyframeSelectionChanged, OnSelectionChanged) SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedPtr<FUICommandList> InCommandList);`
- L35 _public prototype_ `virtual void OnDragEnter(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;` — SWidget interface
- L36 _public prototype_ `virtual void OnDragLeave(const FDragDropEvent& DragDropEvent) override;`
- L37 _public prototype_ `virtual FReply OnDrop(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;`
- L38 _public prototype_ `virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;`
- L39 _public prototype_ `virtual FReply OnMouseWheel(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L40 _public prototype_ `virtual FReply OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L41 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L45 _private prototype_ `void OnAssetsDropped(const class FAssetDragDropOp& DragDropOp);`
- L46 _private prototype_ `void RebuildPerFrameBG();`
- L48 _private prototype_ `TSharedRef<SWidget> GenerateContextMenu();`
- L49 _private prototype_ `EVisibility NoFramesWarningVisibility() const;`
- L50 _private prototype_ `void CheckForRebuild(bool bRebuildAll = false);`
- L52 _private function_ `float GetSlateUnitsPerFrame() const`
- L54 _private prototype_ `void AnimationScrollBar_OnUserScrolled(float ScrollOffset);`
- L56 _private member_ `TSharedPtr<SHorizontalBox> BackgroundPerFrameSlices;`
- L57 _private member_ `TSharedPtr<class STimelineHeader> TimelineHeader;`
- L58 _private member_ `TSharedPtr<class SFlipbookTimelineTrack> TimelineTrack;`
- L60 _private member_ `TAttribute<class UPaperFlipbook*> FlipbookBeingEdited;`
- L61 _private member_ `TAttribute<float> PlayTime;`
- L62 _private member_ `TSharedPtr<FUICommandList> CommandList;`
- L63 _private member_ `FOnFlipbookKeyframeSelectionChanged OnSelectionChanged;`
- L64 _private member_ `float SlateUnitsPerFrame;`
- L65 _private member_ `float AnimationScrollBarPosition;`
- L68 _private member_ `int32 NumFramesFromLastRebuild;` — Observer values (used to detect if the widget needs to be rebuilt)
- L69 _private member_ `int32 NumKeyFramesFromLastRebuild;`

#### Free symbols / members of external scopes

- L17 _delegate_ `DECLARE_DELEGATE_OneParam(FOnFlipbookKeyframeSelectionChanged, int32);` — Called when the selection changes
- L17 _prototype_ `DECLARE_DELEGATE_OneParam(FOnFlipbookKeyframeSelectionChanged, int32);` — Called when the selection changes

### `Plugins/2D/Paper2D/Source/Paper2DEditor/Private/FlipbookEditor/SFlipbookTrackHandle.h` (Private)


#### class `SFlipbookTrackHandle`  
`class SFlipbookTrackHandle : public SImage`  
_L14-144_
- inherits: `SImage`
- desc: This is the grab handle at the end of a frame region, which can be dragged to change the duration
- L17 _public function_ `SLATE_BEGIN_ARGS(SFlipbookTrackHandle) : _SlateUnitsPerFrame(1) , _FlipbookBeingEdited(nullptr) , _KeyFrameIdx(INDEX_NONE)`
- L23 _public function_ `SLATE_ATTRIBUTE( float, SlateUnitsPerFrame ) SLATE_ATTRIBUTE( class UPaperFlipbook*, FlipbookBeingEdited ) SLATE_ARGUMENT( int32, KeyFrameIdx ) SLATE_END_ARGS() void Construct(const FArguments& InArgs)`
- L44 _public function_ `virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override`
- L59 _public function_ `virtual FReply OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override`
- L94 _public function_ `virtual FReply OnMouseMove(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override`
- L131 _public function_ `virtual FCursorReply OnCursorQuery(const FGeometry& MyGeometry, const FPointerEvent& CursorEvent) const override`
- L137 _private member_ `float DistanceDragged;`
- L138 _private member_ `int32 StartingFrameRun;`
- L139 _private member_ `bool bDragging;`
- L141 _private member_ `TAttribute<float> SlateUnitsPerFrame;`
- L142 _private member_ `TAttribute<class UPaperFlipbook*> FlipbookBeingEdited;`
- L143 _private member_ `int32 KeyFrameIdx;`

### `Plugins/2D/Paper2D/Source/Paper2DEditor/Private/FlipbookEditor/STimelineHeader.h` (Private)


#### class `STimelineHeader`  
`class STimelineHeader : public SCompoundWidget`  
_L15-85_
- inherits: `SCompoundWidget`
- desc: This is the bar above the timeline which (will someday) shows the frame ticks and current time
- L18 _public function_ `SLATE_BEGIN_ARGS(STimelineHeader) : _SlateUnitsPerFrame(1) , _FlipbookBeingEdited((class UPaperFlipbook*)nullptr) , _PlayTime(0)`
- L24 _public function_ `SLATE_ATTRIBUTE(float, SlateUnitsPerFrame) SLATE_ATTRIBUTE(class UPaperFlipbook*, FlipbookBeingEdited) SLATE_ATTRIBUTE(float, PlayTime) SLATE_END_ARGS() void Construct(const FArguments& InArgs)`
- L45 _public function_ `void Rebuild()`
- L78 _private member_ `TAttribute<float> SlateUnitsPerFrame;`
- L79 _private member_ `TAttribute<class UPaperFlipbook*> FlipbookBeingEdited;`
- L80 _private member_ `TAttribute<float> PlayTime;`
- L82 _private member_ `TSharedPtr<SHorizontalBox> MainBoxPtr;`
- L84 _private member_ `int32 NumFramesFromLastRebuild;`

### `Plugins/2D/Paper2D/Source/Paper2DEditor/Private/FlipbookEditor/STimelineTrack.h` (Private)


#### class `FFlipbookKeyFrameDragDropOp`  
`class FFlipbookKeyFrameDragDropOp : public FDragDropOperation`  
_L25-57_
- inherits: `FDragDropOperation`
- L28 _public prototype_ `DRAG_DROP_OPERATOR_TYPE(FFlipbookKeyFrameDragDropOp, FDragDropOperation) float WidgetWidth;`
- L31 _public member_ `FPaperFlipbookKeyFrame KeyFrameData;`
- L32 _public member_ `int32 SourceFrameIndex;`
- L33 _public member_ `FText BodyText;`
- L34 _public member_ `TWeakObjectPtr<UPaperFlipbook> SourceFlipbook;`
- L35 _public member_ `FScopedTransaction Transaction;`
- L38 _public prototype_ `virtual TSharedPtr<SWidget> GetDefaultDecorator() const override;` — FDragDropOperation interface
- L39 _public prototype_ `virtual void OnDragged(const class FDragDropEvent& DragDropEvent) override;`
- L40 _public prototype_ `virtual void Construct() override;`
- L41 _public prototype_ `virtual void OnDrop(bool bDropWasHandled, const FPointerEvent& MouseEvent) override;`
- L44 _public prototype_ `void AppendToFlipbook(UPaperFlipbook* DestinationFlipbook);`
- L46 _public prototype_ `void InsertInFlipbook(UPaperFlipbook* DestinationFlipbook, int32 Index);`
- L48 _public function_ `void SetCanDropHere(bool bCanDropHere)`
- L53 _public prototype_ `static TSharedRef<FFlipbookKeyFrameDragDropOp> New(int32 InWidth, UPaperFlipbook* InFlipbook, int32 InFrameIndex);`
- L56 _protected prototype_ `FFlipbookKeyFrameDragDropOp();`

#### class `SFlipbookKeyframeWidget`  
`class SFlipbookKeyframeWidget : public SCompoundWidget`  
_L62-110_
- inherits: `SCompoundWidget`
- L65 _public function_ `SLATE_BEGIN_ARGS(SFlipbookKeyframeWidget) : _SlateUnitsPerFrame(1) , _FlipbookBeingEdited(nullptr)`
- L70 _public prototype_ `SLATE_ATTRIBUTE( float, SlateUnitsPerFrame ) SLATE_ATTRIBUTE( class UPaperFlipbook*, FlipbookBeingEdited ) SLATE_EVENT( FOnFlipbookKeyframeSelectionChanged, OnSelectionChanged ) SLATE_END_ARGS() void Construct(const FArguments& InArgs, int32 InFrameIndex, TSharedPtr<FUICommandList> InCommandList);`
- L79 _public prototype_ `virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;` — SWidget interface
- L80 _public prototype_ `virtual FReply OnDragDetected(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L81 _public prototype_ `virtual FReply OnDrop(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;`
- L85 _protected prototype_ `FReply KeyframeOnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent);`
- L87 _protected prototype_ `FText GetKeyframeAssetName() const;`
- L88 _protected prototype_ `FText GetKeyframeText() const;`
- L89 _protected prototype_ `FText GetKeyframeTooltip() const;`
- L91 _protected prototype_ `TSharedRef<SWidget> GenerateContextMenu();`
- L93 _protected prototype_ `FOptionalSize GetFrameWidth() const;`
- L95 _protected prototype_ `void OpenSpritePickerMenu(class FMenuBuilder& MenuBuilder);`
- L96 _protected prototype_ `void OnAssetSelected(const struct FAssetData& AssetData);`
- L97 _protected prototype_ `void CloseMenu();`
- L98 _protected prototype_ `void ShowInContentBrowser();`
- L99 _protected prototype_ `void EditKeyFrame();`
- L102 _protected prototype_ `const struct FPaperFlipbookKeyFrame* GetKeyFrameData() const;` — Can return null
- L105 _protected member_ `int32 FrameIndex;`
- L106 _protected member_ `TAttribute<float> SlateUnitsPerFrame;`
- L107 _protected member_ `TAttribute<class UPaperFlipbook*> FlipbookBeingEdited;`
- L108 _protected member_ `FOnFlipbookKeyframeSelectionChanged OnSelectionChanged;`
- L109 _protected member_ `TSharedPtr<FUICommandList> CommandList;`

#### class `SFlipbookTimelineTrack`  
`class SFlipbookTimelineTrack : public SCompoundWidget`  
_L115-143_
- inherits: `SCompoundWidget`
- L118 _public function_ `SLATE_BEGIN_ARGS(SFlipbookTimelineTrack) : _SlateUnitsPerFrame(1) , _FlipbookBeingEdited(nullptr)`
- L123 _public prototype_ `SLATE_ATTRIBUTE( float, SlateUnitsPerFrame ) SLATE_ATTRIBUTE( class UPaperFlipbook*, FlipbookBeingEdited ) SLATE_EVENT( FOnFlipbookKeyframeSelectionChanged, OnSelectionChanged ) SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedPtr<FUICommandList> InCommandList);`
- L131 _public prototype_ `void Rebuild();`
- L134 _private member_ `TAttribute<float> SlateUnitsPerFrame;`
- L135 _private member_ `TAttribute< class UPaperFlipbook* > FlipbookBeingEdited;`
- L137 _private member_ `TSharedPtr<SHorizontalBox> MainBoxPtr;`
- L139 _private member_ `float HandleWidth;`
- L141 _private member_ `FOnFlipbookKeyframeSelectionChanged OnSelectionChanged;`
- L142 _private member_ `TSharedPtr<FUICommandList> CommandList;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace FFlipbookUIConstants`
- L16 _variable_ `const float HandleWidth = 12.0f;` (scope `FFlipbookUIConstants`)
- L17 _variable_ `const float FrameHeight = 48;` (scope `FFlipbookUIConstants`)
- L18 _variable_ `const float HeightBeforeFrames = 16;` (scope `FFlipbookUIConstants`)
- L19 _variable_ `const FMargin FramePadding(0.0f, 7.0f, 0.0f, 7.0f);` (scope `FFlipbookUIConstants`)

### `Plugins/2D/Paper2D/Source/Paper2DEditor/Private/GroupedSprites/GroupedSpriteDetailsCustomization.h` (Private)


#### class `FGroupedSpriteComponentDetailsCustomization`  
`class FGroupedSpriteComponentDetailsCustomization : public IDetailCustomization`  
_L15-33_
- inherits: `IDetailCustomization`
- L19 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L22 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailLayout) override;` — IDetailCustomization interface
- L26 _protected prototype_ `FGroupedSpriteComponentDetailsCustomization();`
- L28 _protected prototype_ `FReply SplitSprites();`
- L29 _protected prototype_ `FReply SortSprites();`
- L32 _protected member_ `TArray<TWeakObjectPtr<UObject>> ObjectsBeingCustomized;`

### `Plugins/2D/Paper2D/Source/Paper2DEditor/Private/GroupedSprites/PaperGroupedSpriteUtilities.h` (Private)


#### class `FPaperGroupedSpriteUtilities`  
`class FPaperGroupedSpriteUtilities`  
_L12-23_
- L15 _public prototype_ `static void BuildHarvestList(const TArray<UObject*>& ObjectsToConsider, TSubclassOf<UActorComponent> HarvestClassType, TArray<UActorComponent*>& OutComponentsToHarvest, TArray<AActor*>& OutActorsToDelete);`
- L18 _public prototype_ `static FBox ComputeBoundsForComponents(const TArray<UActorComponent*>& ComponentList);` — Computes the enclosing bounding box of the specified components (using their individual bounds)
- L20 _public prototype_ `static void SplitSprites(const TArray<UObject*>& InObjectList);`
- L22 _public prototype_ `static void MergeSprites(const TArray<UObject*>& InObjectList);`

### `Plugins/2D/Paper2D/Source/Paper2DEditor/Private/LevelEditorMenuExtensions/Paper2DLevelEditorExtensions.h` (Private)


#### class `FPaperLevelEditorMenuExtensions`  
`class FPaperLevelEditorMenuExtensions`  
_L7-12_
- desc: Integrate Paper2D actions into the level editor context menu
- L10 _public prototype_ `static void InstallHooks();`
- L11 _public prototype_ `static void RemoveHooks();`

### `Plugins/2D/Paper2D/Source/Paper2DEditor/Private/MeshPainting/MeshPaintSpriteAdapter.h` (Private)


#### class `FMeshPaintSpriteAdapter`  
`class FMeshPaintSpriteAdapter : public IMeshPaintGeometryAdapter`  
_L17-60_
- inherits: `IMeshPaintGeometryAdapter`
- L20 _public function_ `static void InitializeAdapterGlobals()`
- L21 _public function_ `static void AddReferencedObjectsGlobals(FReferenceCollector& Collector)`
- L22 _public function_ `static void CleanupGlobals()`
- L24 _public prototype_ `virtual bool Construct(UMeshComponent* InComponent, int32 InMeshLODIndex) override;`
- L25 _public prototype_ `virtual bool Initialize() override;`
- L26 _public function_ `virtual void OnAdded() override`
- L27 _public function_ `virtual void OnRemoved() override`
- L28 _public function_ `virtual bool IsValid() const override`
- L29 _public function_ `virtual bool SupportsTexturePaint() const override`
- L30 _public function_ `virtual bool SupportsVertexPaint() const override`
- L31 _public prototype_ `virtual bool LineTraceComponent(struct FHitResult& OutHit, const FVector Start, const FVector End, const struct FCollisionQueryParams& Params) const override;`
- L32 _public prototype_ `virtual TArray<uint32> SphereIntersectTriangles(const float ComponentSpaceSquaredBrushRadius, const FVector& ComponentSpaceBrushPosition, const FVector& ComponentSpaceCameraPosition, const bool bOnlyFrontFacing) const override;`
- L33 _public prototype_ `virtual void QueryPaintableTextures(int32 MaterialIndex, int32& OutDefaultIndex, TArray<struct FPaintableTexture>& InOutTextureList) override;`
- L34 _public prototype_ `virtual void ApplyOrRemoveTextureOverride(UTexture* SourceTexture, UTexture* OverrideTexture) const override;`
- L35 _public function_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override`
- L37 _public prototype_ `virtual void PreEdit() override;`
- L38 _public prototype_ `virtual void PostEdit() override;`
- L40 _public function_ `virtual const TArray<FVector>& GetMeshVertices() const override`
- L41 _public function_ `virtual const TArray<uint32>& GetMeshIndices() const override`
- L42 _public prototype_ `virtual void GetVertexPosition(int32 VertexIndex, FVector& OutVertex) const override;`
- L43 _public prototype_ `virtual void GetTextureCoordinate(int32 VertexIndex, int32 ChannelIndex, FVector2D& OutTextureCoordinate) const override;`
- L44 _public prototype_ `virtual void GetVertexColor(int32 VertexIndex, FColor& OutColor, bool bInstance = true) const override;`
- L45 _public prototype_ `virtual void SetVertexColor(int32 VertexIndex, FColor Color, bool bInstance = true) override;`
- L46 _public prototype_ `virtual FMatrix GetComponentToWorldMatrix() const override;`
- L48 _public prototype_ `virtual void GetInfluencedVertexIndices(const float ComponentSpaceSquaredBrushRadius, const FVector& ComponentSpaceBrushPosition, const FVector& ComponentSpaceCameraPosition, const bool bOnlyFrontFacing, TSet<int32> &InfluencedVertices) const override;`
- L49 _public prototype_ `virtual void GetInfluencedVertexData(const float ComponentSpaceSquaredBrushRadius, const FVector& ComponentSpaceBrushPosition, const FVector& ComponentSpaceCameraPosition, const bool bOnlyFrontFacing, TArray<TPair<int32, FVector>>& OutData) const override;`
- L51 _public prototype_ `virtual TArray<FVector> SphereIntersectVertices(const float ComponentSpaceSquaredBrushRadius, const FVector& ComponentSpaceBrushPosition, const FVector& ComponentSpaceCameraPosition, const bool bOnlyFrontFacing) const override;`
- L56 _protected member_ `UPaperSpriteComponent* SpriteComponent;`
- L57 _protected member_ `UPaperSprite* Sprite;`
- L58 _protected member_ `TArray<FVector> MeshVertices;`
- L59 _protected member_ `TArray<uint32> MeshIndices;`

#### class `FMeshPaintSpriteAdapterFactory`  
`class FMeshPaintSpriteAdapterFactory : public IMeshPaintGeometryAdapterFactory`  
_L65-72_
- inherits: `IMeshPaintGeometryAdapterFactory`
- L68 _public prototype_ `virtual TSharedPtr<IMeshPaintGeometryAdapter> Construct(UMeshComponent* InComponent, int32 InMeshLODIndex) const override;`
- L69 _public function_ `virtual void InitializeAdapterGlobals() override`
- L70 _public function_ `virtual void AddReferencedObjectsGlobals(FReferenceCollector& Collector) override`
- L71 _public function_ `virtual void CleanupGlobals() override`

### `Plugins/2D/Paper2D/Source/Paper2DEditor/Private/Paper2DEditorLog.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogPaper2DEditor, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogPaper2DEditor, Log, All);`

### `Plugins/2D/Paper2D/Source/Paper2DEditor/Private/PaperEditorCommands.h` (Private)


#### class `FPaperEditorCommands`  
`class FPaperEditorCommands : public TCommands<FPaperEditorCommands>`  
_L9-28_
- inherits: `TCommands<FPaperEditorCommands>`
- L12 _public function_ `FPaperEditorCommands() : TCommands<FPaperEditorCommands>( TEXT("PaperEditor"),`
- L23 _public prototype_ `virtual void RegisterCommands() override;` — TCommand<> interface

### `Plugins/2D/Paper2D/Source/Paper2DEditor/Private/PaperEditorShared/AssetEditorSelectedItem.h` (Private)


#### class `FSelectedItem`  
`class FSelectedItem`  
_L13-77_
- L16 _protected function_ `FSelectedItem(FName InTypeName) : TypeName(InTypeName)`
- L22 _protected member_ `FName TypeName;`
- L24 _public function_ `virtual bool IsA(FName TestType) const`
- L30 _public function_ `template<typename SelectedType> SelectedType* CastTo(FName TypeID)`
- L35 _public function_ `virtual uint32 GetTypeHash() const`
- L40 _public function_ `virtual bool Equals(const FSelectedItem& OtherItem) const`
- L45 _public function_ `virtual void ApplyDelta(const FVector2D& Delta, const FRotator& Rotation, const FVector& Scale3D, UE::Widget::EWidgetMode MoveMode)`
- L49 _public function_ `virtual FVector GetWorldPos() const`
- L54 _public function_ `virtual EMouseCursor::Type GetMouseCursor() const`
- L60 _public function_ `virtual bool IsBackgroundObject() const` — Is this item a background item (one that can be clicked thru/etc... to select something behind it?)
- L66 _public function_ `virtual bool CanBeDeleted() const` — Can this item be deleted?
- L72 _public function_ `virtual void DeleteThisItem()` — Delete this item
- L76 _public prototype_ `virtual ~FSelectedItem() = default;`

#### struct `HSpriteSelectableObjectHitProxy`  
`struct HSpriteSelectableObjectHitProxy : public HHitProxy`  
_L93-109_
- inherits: `HHitProxy`
- L95 _public prototype_ `DECLARE_HIT_PROXY();`
- L97 _public member_ `TSharedPtr<FSelectedItem> Data;`
- L99 _public function_ `HSpriteSelectableObjectHitProxy(TSharedPtr<FSelectedItem> InData) : HHitProxy(InData->IsBackgroundObject() ? HPP_World : HPP_UI) , Data(InData)`
- L106 _public function_ `virtual bool AlwaysAllowsTranslucentPrimitives() const override` — HHitProxy interface
- L107 _public function_ `virtual EMouseCursor::Type GetMouseCursor() override`

#### Free symbols / members of external scopes

- L79 _function_ `inline uint32 GetTypeHash(const FSelectedItem& Item)`
- L84 _function_ `inline bool operator==(const FSelectedItem& V1, const FSelectedItem& V2)`

### `Plugins/2D/Paper2D/Source/Paper2DEditor/Private/PaperEditorShared/SocketEditing.h` (Private)


#### class `FSpriteSelectedSocket`  
`class FSpriteSelectedSocket : public FSelectedItem`  
_L17-34_
- inherits: `FSelectedItem`
- L20 _public member_ `FName SocketName;`
- L21 _public member_ `TWeakObjectPtr<UPrimitiveComponent> PreviewComponentPtr;`
- L23 _public member_ `static const FName SocketTypeID;`
- L26 _public prototype_ `FSpriteSelectedSocket();`
- L29 _public prototype_ `virtual bool Equals(const FSelectedItem& OtherItem) const override;` — FSelectedItem interface
- L30 _public prototype_ `virtual void ApplyDelta(const FVector2D& Delta, const FRotator& Rotation, const FVector& Scale3D, UE::Widget::EWidgetMode MoveMode) override;`
- L31 _public prototype_ `FVector GetWorldPos() const override;`
- L32 _public prototype_ `virtual void DeleteThisItem() override;`

#### class `FSocketEditingHelper`  
`class FSocketEditingHelper`  
_L39-44_
- L42 _public prototype_ `static void DrawSockets(class FSpriteGeometryEditMode* GeometryEditMode, UPrimitiveComponent* PreviewComponent, const FSceneView* View, FPrimitiveDrawInterface* PDI);`
- L43 _public prototype_ `static void DrawSocketNames(class FSpriteGeometryEditMode* GeometryEditMode, UPrimitiveComponent* PreviewComponent, FViewport& Viewport, FSceneView& View, FCanvas& Canvas);`

### `Plugins/2D/Paper2D/Source/Paper2DEditor/Private/PaperEditorShared/SpriteGeometryEditCommands.h` (Private)


#### class `FSpriteGeometryEditCommands`  
`class FSpriteGeometryEditCommands : public TCommands<FSpriteGeometryEditCommands>`  
_L9-37_
- inherits: `TCommands<FSpriteGeometryEditCommands>`
- L12 _public function_ `FSpriteGeometryEditCommands() : TCommands<FSpriteGeometryEditCommands>( TEXT("SpriteGeometryEditor"),`
- L23 _public prototype_ `virtual void RegisterCommands() override;` — TCommand<> interface
- L28 _public member_ `TSharedPtr<FUICommandInfo> SetShowNormals;` — Show toggles
- L31 _public member_ `TSharedPtr<FUICommandInfo> DeleteSelection;` — Geometry editing commands
- L32 _public member_ `TSharedPtr<FUICommandInfo> SplitEdge;`
- L33 _public member_ `TSharedPtr<FUICommandInfo> AddBoxShape;`
- L34 _public member_ `TSharedPtr<FUICommandInfo> AddCircleShape;`
- L35 _public member_ `TSharedPtr<FUICommandInfo> ToggleAddPolygonMode;`
- L36 _public member_ `TSharedPtr<FUICommandInfo> SnapAllVertices;`

### `Plugins/2D/Paper2D/Source/Paper2DEditor/Private/PaperEditorShared/SpriteGeometryEditMode.h` (Private)


#### class `FSpriteGeometryEditMode`  
`class FSpriteGeometryEditMode : public FEdMode`  
_L20-88_
- inherits: `FEdMode`
- L23 _public member_ `static const FEditorModeID EM_SpriteGeometry;`
- L24 _public member_ `static const FLinearColor MarqueeDrawColor;`
- L27 _public prototype_ `FSpriteGeometryEditMode();`
- L30 _public prototype_ `virtual void Initialize() override;` — FEdMode interface
- L31 _public prototype_ `virtual void DrawHUD(FEditorViewportClient* ViewportClient, FViewport* Viewport, const FSceneView* View, FCanvas* Canvas) override;`
- L32 _public prototype_ `virtual void Render(const FSceneView* View, FViewport* Viewport, FPrimitiveDrawInterface* PDI) override;`
- L33 _public prototype_ `virtual bool HandleClick(FEditorViewportClient* InViewportClient, HHitProxy* HitProxy, const FViewportClick& Click) override;`
- L34 _public prototype_ `virtual bool InputKey(FEditorViewportClient* ViewportClient, FViewport* Viewport, FKey Key, EInputEvent Event) override;`
- L35 _public prototype_ `virtual FVector GetWidgetLocation() const override;`
- L36 _public prototype_ `virtual bool InputDelta(FEditorViewportClient* InViewportClient, FViewport* InViewport, FVector& InDrag, FRotator& InRot, FVector& InScale) override;`
- L37 _public prototype_ `virtual void Tick(FEditorViewportClient* ViewportClient, float DeltaTime) override;`
- L38 _public prototype_ `virtual bool ShouldDrawWidget() const override;`
- L42 _public prototype_ `void SetEditorContext(class ISpriteSelectionContext* InNewEditorContext);` — Changes the editor interface to point to the hosting editor; this is basically required
- L45 _public prototype_ `void SetNewGeometryPreferredBounds(FBox2D& NewDesiredBounds);` — Sets the default bounds for newly created boxes/circles/etc...
- L48 _public prototype_ `void SetGeometryColors(const FLinearColor& NewVertexColor, const FLinearColor& NewNegativeVertexColor);` — Sets the draw color for geometry
- L51 _public prototype_ `void SetGeometryBeingEdited(FSpriteGeometryCollection* NewGeometryBeingEdited, bool bInAllowCircles, bool bInAllowSubtractivePolygons);` — Changes the geometry being edited (clears the selection set in the process)
- L53 _public prototype_ `void BindCommands(TSharedPtr<FUICommandList> InCommandList);`
- L55 _public function_ `FVector2D GetMarqueeStartPos() const`
- L56 _public function_ `FVector2D GetMarqueeEndPos() const`
- L57 _public prototype_ `bool ProcessMarquee(FViewport* Viewport, FKey Key, EInputEvent Event, bool bMarqueeStartModifierPressed);`
- L60 _public prototype_ `bool IsSocketSelected(FName SocketName) const;` — Returns true if the specified socket is selected
- L62 _public prototype_ `static void DrawGeometryStats(FViewport& InViewport, FSceneView& View, FCanvas& Canvas, const FSpriteGeometryCollection& Geometry, bool bIsRenderGeometry, int32& YPos);`
- L63 _public prototype_ `static void DrawCollisionStats(FViewport& InViewport, FSceneView& View, FCanvas& Canvas, class UBodySetup* BodySetup, int32& YPos);`
- L65 _public prototype_ `virtual bool UsesTransformWidget(UE::Widget::EWidgetMode CheckMode) const override;`
- L67 _protected member_ `FBox2D BoundsForNewShapes;`
- L68 _protected member_ `FLinearColor GeometryVertexColor;`
- L69 _protected member_ `FLinearColor NegativeGeometryVertexColor;`
- L72 _protected member_ `FSpriteGeometryEditingHelper SpriteGeometryHelper;` — Sprite geometry editing/rendering helper
- L75 _protected member_ `bool bIsMarqueeTracking;` — Marquee tracking
- L76 _protected member_ `FVector2D MarqueeStartPos;`
- L77 _protected member_ `FVector2D MarqueeEndPos;`
- L80 _protected prototype_ `void AddBoxShape();`
- L81 _protected prototype_ `void AddCircleShape();`
- L83 _protected prototype_ `bool IsEditingGeometry() const;`
- L85 _protected prototype_ `void SelectVerticesInMarquee(FEditorViewportClient* ViewportClient, FViewport* Viewport, bool bAddToSelection);`
- L87 _protected prototype_ `void DrawMarquee(FViewport& InViewport, const FSceneView& View, FCanvas& Canvas, const FLinearColor& Color);`

### `Plugins/2D/Paper2D/Source/Paper2DEditor/Private/PaperEditorShared/SpriteGeometryEditing.h` (Private)


#### struct `FShapeVertexPair`  
`struct FShapeVertexPair`  
_L21-39_
- L24 _public member_ `const int32 ShapeIndex;`
- L25 _public member_ `const int32 VertexIndex;`
- L28 _public function_ `FShapeVertexPair() : ShapeIndex(INDEX_NONE) , VertexIndex(INDEX_NONE)`
- L34 _public function_ `FShapeVertexPair(int32 InShapeIndex, int32 InVertexIndex) : ShapeIndex(InShapeIndex) , VertexIndex(InVertexIndex)`

#### class `FSpriteSelectionHelper`  
`class FSpriteSelectionHelper`  
_L54-78_
- L57 _public function_ `bool HasAnySelectedItems() const`
- L62 _public function_ `const TSet< TSharedPtr<FSelectedItem> >& GetSelectionSet() const`
- L67 _public prototype_ `void SelectItem(TSharedPtr<FSelectedItem> NewItem);`
- L69 _public prototype_ `virtual void ClearSelectionSet();`
- L71 _public prototype_ `virtual bool CanDeleteSelection() const;`
- L73 _public prototype_ `virtual ~FSpriteSelectionHelper() = default;`
- L77 _private member_ `TSet< TSharedPtr<FSelectedItem> > SelectedItemSet;` — Set of selected objects

#### class `FSpriteGeometryEditingHelper`  
`class FSpriteGeometryEditingHelper : public FSpriteSelectionHelper, public FGCObject`  
_L83-194_
- inherits: `FSpriteSelectionHelper,FGCObject`
- L86 _public prototype_ `FSpriteGeometryEditingHelper(class ISpriteSelectionContext* InEditorContext);`
- L89 _public prototype_ `virtual void ClearSelectionSet() override;` — FSpriteSelectionHelper interface
- L93 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;` — FGCObject interface
- L94 _public function_ `virtual FString GetReferencerName() const override`
- L100 _public prototype_ `void DeleteSelectedItems();`
- L101 _public prototype_ `void SetEditorContext(class ISpriteSelectionContext* InNewEditorContext);`
- L102 _public prototype_ `class ISpriteSelectionContext* GetEditorContext() const;`
- L104 _public prototype_ `void DrawGeometry(const FSceneView& View, FPrimitiveDrawInterface& PDI, const FLinearColor& GeometryVertexColor, const FLinearColor& NegativeGeometryVertexColor);`
- L105 _public prototype_ `void DrawGeometry_CanvasPass(FViewport& InViewport, const FSceneView& View, FCanvas& Canvas, int32& YPos, const FLinearColor& GeometryVertexColor, const FLinearColor& NegativeGeometryVertexColor);`
- L109 _public prototype_ `void AddPointToGeometry(const FVector2D& TextureSpacePoint, const int32 SelectedPolygonIndex = INDEX_NONE);` — Adds a point to the currently edited index If SelectedPolygonIndex is set, only that polygon is considered
- L111 _public prototype_ `void SelectGeometry(const FShapeVertexPair& GeometyItem);`
- L112 _public prototype_ `bool IsGeometrySelected(const FShapeVertexPair& GeometyItem) const;`
- L115 _public prototype_ `void AddShapeToSelection(const int32 ShapeIndex);`
- L116 _public prototype_ `void AddPolygonVertexToSelection(const int32 ShapeIndex, const int32 VertexIndex);`
- L117 _public prototype_ `void AddPolygonEdgeToSelection(const int32 ShapeIndex, const int32 FirstVertexIndex);`
- L119 _public prototype_ `void SetShowNormals(bool bShouldShowNormals);`
- L120 _public prototype_ `void ToggleShowNormals();`
- L121 _public function_ `bool IsShowNormalsEnabled() const`
- L124 _public prototype_ `void SetGeometryBeingEdited(FSpriteGeometryCollection* NewGeometryBeingEdited, bool bInAllowCircles, bool bInAllowSubtractivePolygons);` — Changes the geometry being edited (clears the selection set in the process)
- L125 _public prototype_ `FSpriteGeometryCollection* GetGeometryBeingEdited() const;`
- L128 _public prototype_ `void AddNewCircleShape(const FVector2D& CircleLocation, float Radius);` — Adds a new circle shape and selects it
- L129 _public function_ `bool CanAddCircleShape() const`
- L132 _public prototype_ `void AddNewBoxShape(const FVector2D& BoxLocation, const FVector2D& BoxSize);` — Adds a new box shape and selects it
- L133 _public function_ `bool CanAddBoxShape() const`
- L135 _public prototype_ `void ResetAddPolygonMode();`
- L136 _public prototype_ `void ToggleAddPolygonMode();`
- L137 _public function_ `bool IsAddingPolygon() const`
- L138 _public function_ `bool CanAddPolygon() const`
- L139 _public function_ `bool CanAddSubtractivePolygon() const`
- L140 _public prototype_ `void AbandonAddPolygonMode();`
- L142 _public prototype_ `void SnapAllVerticesToPixelGrid();`
- L143 _public function_ `bool CanSnapVerticesToPixelGrid() const`
- L145 _public prototype_ `void HandleAddPolygonClick(const FVector2D& TexturePoint, bool bWantsSubtractive, const FSceneView& View, EInputEvent Event);`
- L147 _public prototype_ `void DeleteLastVertexFromAddPolygonMode();`
- L149 _public function_ `bool IsEditingGeometry() const`
- L154 _private prototype_ `static bool ClosestPointOnLine(const FVector2D& Point, const FVector2D& LineStart, const FVector2D& LineEnd, FVector2D& OutClosestPoint);`
- L158 _private prototype_ `static bool DeleteVertexInPolygonInternal(FSpriteGeometryCollection& Geometry, const int32 ShapeIndex, const int32 VertexIndex);` — Be sure to call this with polygonIndex and VertexIndex in descending order Returns true if the shape went to zero points and should be deleted itself
- L160 _private function_ `FSpriteGeometryCollection& GetGeometryChecked()`
- L167 _private prototype_ `FVector2D TextureSpaceToScreenSpace(const FSceneView& View, const FVector2D& SourcePoint) const;` — @TODO: This is needed for the canvas pass, but most of that code should go into the PDI pass
- L170 _private member_ `class ISpriteSelectionContext* EditorContext;`
- L172 _private member_ `TObjectPtr<UMaterial> WidgetVertexColorMaterial;`
- L175 _private member_ `TSet<FShapeVertexPair> SelectedIDSet;` — Set of selected vertices/shapes
- L178 _private member_ `FSpriteGeometryCollection* GeometryBeingEdited;` — Active geometry being edited
- L181 _private member_ `bool bIsAddingPolygon;` — Is waiting to add geometry
- L184 _private member_ `int32 AddingPolygonIndex;` — The polygon index being added to, INDEX_NONE if we don't have a polygon yet
- L187 _private member_ `bool bShowNormals;` — Should we show polygon edge normals?
- L190 _private member_ `bool bAllowSubtractivePolygons;` — Do we allow subtractive polygons?
- L193 _private member_ `bool bAllowCircles;` — Do we allow circles?

#### Free symbols / members of external scopes

- L41 _function_ `inline bool operator==(const FShapeVertexPair& A, const FShapeVertexPair& B)`
- L46 _function_ `inline uint32 GetTypeHash(const FShapeVertexPair& Item)`

### `Plugins/2D/Paper2D/Source/Paper2DEditor/Private/PaperEditorViewportClient.h` (Private)


#### struct `FViewportSelectionRectangle`  
`struct FViewportSelectionRectangle`  
_L9-14_
- L11 _public member_ `FVector2D TopLeft;`
- L12 _public member_ `FVector2D Dimensions;`
- L13 _public member_ `FLinearColor Color;`

#### class `FPaperEditorViewportClient`  
`class FPaperEditorViewportClient : public FEditorViewportClient`  
_L19-77_
- inherits: `FEditorViewportClient`
- L23 _public prototype_ `explicit FPaperEditorViewportClient(const TWeakPtr<class SEditorViewport>& InEditorViewportWidget = nullptr);` — Constructor
- L24 _public prototype_ `~FPaperEditorViewportClient();`
- L27 _public prototype_ `virtual void Tick(float DeltaSeconds) override;` — FViewportClient interface
- L31 _public prototype_ `virtual FLinearColor GetBackgroundColor() const override;` — FEditorViewportClient interface
- L35 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;` — FSerializableObject interface
- L39 _public prototype_ `virtual void RequestFocusOnSelection(bool bInstant);` — Called to request a focus on the current selection
- L42 _public prototype_ `void ModifyCheckerboardTextureColors();` — Modifies the checkerboard texture's data
- L44 _public function_ `void SetZoomPos(FVector2D InNewPos, float InNewZoom)`
- L51 _public member_ `TArray<FViewportSelectionRectangle> SelectionRectangles;` — List of selection rectangles to draw
- L54 _private prototype_ `void SetupCheckerboardTexture(const FColor& ColorOne, const FColor& ColorTwo, int32 CheckerSize);` — Initialize the checkerboard texture for the texture preview, if necessary
- L57 _private prototype_ `void DestroyCheckerboardTexture();` — Destroy the checkerboard texture if one exists
- L60 _protected prototype_ `void DrawSelectionRectangles(FViewport* Viewport, FCanvas* Canvas);`
- L62 _protected function_ `virtual FBox GetDesiredFocusBounds() const`
- L69 _protected member_ `TObjectPtr<UTexture2D> CheckerboardTexture;` — Checkerboard texture
- L70 _protected member_ `FVector2D ZoomPos;`
- L71 _protected member_ `float ZoomAmount;`
- L75 _private member_ `bool bDeferZoomToSprite;` — Should we zoom to the focus bounds next tick?
- L76 _private member_ `bool bDeferZoomToSpriteIsInstant;`

### `Plugins/2D/Paper2D/Source/Paper2DEditor/Private/PaperFlipbookAssetBroker.h` (Private)


#### class `FPaperFlipbookAssetBroker`  
`class FPaperFlipbookAssetBroker : public IComponentAssetBroker`  
_L12-44_
- inherits: `IComponentAssetBroker`
- L15 _public function_ `UClass* GetSupportedAssetClass() override`
- L20 _public function_ `virtual bool AssignAssetToComponent(UActorComponent* InComponent, UObject* InAsset) override`
- L36 _public function_ `virtual UObject* GetAssetFromComponent(UActorComponent* InComponent) override`

### `Plugins/2D/Paper2D/Source/Paper2DEditor/Private/PaperSpriteAssetBroker.h` (Private)


#### class `FPaperSpriteAssetBroker`  
`class FPaperSpriteAssetBroker : public IComponentAssetBroker`  
_L13-51_
- inherits: `IComponentAssetBroker`
- L16 _public function_ `UClass* GetSupportedAssetClass() override`
- L21 _public function_ `virtual bool AssignAssetToComponent(UActorComponent* InComponent, UObject* InAsset) override`
- L43 _public function_ `virtual UObject* GetAssetFromComponent(UActorComponent* InComponent) override`

### `Plugins/2D/Paper2D/Source/Paper2DEditor/Private/PaperStyle.h` (Private)


#### class `FPaperStyle`  
`class FPaperStyle`  
_L7-22_
- L10 _public prototype_ `static void Initialize();`
- L12 _public prototype_ `static void Shutdown();`
- L14 _public prototype_ `static TSharedPtr< class ISlateStyle > Get();`
- L16 _public prototype_ `static FName GetStyleSetName();`
- L18 _private prototype_ `static FString InContent(const FString& RelativePath, const ANSICHAR* Extension);`
- L21 _private member_ `static TSharedPtr< class FSlateStyleSet > StyleSet;`

### `Plugins/2D/Paper2D/Source/Paper2DEditor/Private/SPaperEditorViewport.h` (Private)


#### struct `FMarqueeOperation`  
`struct FMarqueeOperation`  
_L15-72_
- desc: Helper for managing marquee operations
- L17 _public function_ `FMarqueeOperation() : Operation(Add)`
- L30 _public member_ `} Operation;`
- L32 _public function_ `bool IsValid() const`
- L37 _public function_ `void Start(const FVector2D& InStartLocation, FMarqueeOperation::Type InOperationType)`
- L43 _public function_ `void End()`
- L50 _public function_ `static FMarqueeOperation::Type OperationTypeFromMouseEvent(const FPointerEvent& MouseEvent)` — Given a mouse event, figure out what the marquee selection should do based on the state of Shift and Ctrl keys
- L68 _public member_ `FMarqueeRect Rect;` — The marquee rectangle being dragged by the user
- L71 _public member_ `TSet<class UObject*> AffectedNodes;` — Nodes that will be selected or unselected by the current marquee operation

#### enum `FMarqueeOperation::Type`  
`enum Type`  
_L22-30_
- L25 _public enumerator_ `Toggle` — Holding down Ctrl toggles affected nodes
- L27 _public enumerator_ `Add` — Holding down Shift adds to the selection
- L29 _public enumerator_ `Replace` — When nothing is pressed, marquee replaces selection

#### class `SPaperEditorViewport`  
`class SPaperEditorViewport : public SEditorViewport`  
_L77-166_
- inherits: `SEditorViewport`
- L80 _public prototype_ `DECLARE_DELEGATE_TwoParams(FOnSelectionChanged, FMarqueeOperation , bool );`
- L82 _public function_ `SLATE_BEGIN_ARGS(SPaperEditorViewport)`
- L83 _public prototype_ `SLATE_EVENT(FOnSelectionChanged, OnSelectionChanged);`
- L87 _public prototype_ `~SPaperEditorViewport();` — Destructor
- L90 _public prototype_ `virtual void Tick( const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime ) override;` — SWidget interface
- L91 _public prototype_ `virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L92 _public prototype_ `virtual FReply OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L93 _public prototype_ `virtual FReply OnMouseMove(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L94 _public prototype_ `virtual FReply OnMouseWheel(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L95 _public prototype_ `virtual FCursorReply OnCursorQuery( const FGeometry& MyGeometry, const FPointerEvent& CursorEvent ) const override;`
- L96 _public prototype_ `virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;`
- L99 _public prototype_ `void Construct(const FArguments& InArgs, TSharedRef<class FPaperEditorViewportClient> InViewportClient);`
- L101 _public prototype_ `float GetZoomAmount() const;`
- L102 _public prototype_ `FText GetZoomText() const;`
- L103 _public prototype_ `FSlateColor GetZoomTextColorAndOpacity() const;`
- L104 _public prototype_ `FVector2D GetViewOffset() const;`
- L109 _protected prototype_ `virtual TSharedRef<FEditorViewportClient> MakeEditorViewportClient() override;` — SEditorViewport interface
- L113 _protected prototype_ `int32 FindNearestZoomLevel(float InZoomAmount, bool bRoundDown) const;`
- L116 _protected prototype_ `FVector2D ComputeEdgePanAmount(const FGeometry& MyGeometry, const FVector2D& TargetPosition);`
- L117 _protected prototype_ `void UpdateViewOffset(const FGeometry& MyGeometry, const FVector2D& TargetPosition);`
- L118 _protected prototype_ `void RequestDeferredPan(const FVector2D& UpdatePosition);`
- L119 _protected prototype_ `FVector2D GraphCoordToPanelCoord(const FVector2D& GraphSpaceCoordinate) const;`
- L120 _protected prototype_ `FVector2D PanelCoordToGraphCoord(const FVector2D& PanelSpaceCoordinate) const;`
- L121 _protected prototype_ `FSlateRect PanelRectToGraphRect(const FSlateRect& PanelSpaceRect) const;`
- L122 _protected function_ `virtual bool OnHandleLeftMouseRelease(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)`
- L124 _protected prototype_ `void PaintSoftwareCursor(const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 DrawLayerId) const;`
- L126 _protected prototype_ `virtual FText GetTitleText() const;`
- L129 _protected member_ `FVector2D ViewOffset;` — The position within the graph at which the user is looking
- L132 _protected member_ `int32 ZoomLevel;` — How zoomed in/out we are. e.g. 0.25f results in quarter-sized nodes.
- L135 _protected member_ `int32 PreviousZoomLevel;` — Previous Zoom Level
- L138 _protected member_ `bool bIsPanning;` — Are we panning the view at the moment?
- L141 _protected member_ `float TotalMouseDelta;` — The total distance that the mouse has been dragged while down
- L144 _protected member_ `FMarqueeOperation Marquee;` — A pending marquee operation if it's active
- L147 _protected member_ `FCurveSequence ZoomLevelFade;` — Curve that handles fading the 'Zoom +X' text
- L150 _protected member_ `FVector2D DeferredPanPosition;` — Position to pan to
- L153 _protected member_ `bool bRequestDeferredPan;` — true if pending request for deferred panning
- L156 _protected member_ `FVector2D SoftwareCursorPosition;` — The current position of the software cursor
- L159 _protected member_ `bool bShowSoftwareCursor;` — Whether the software cursor should be drawn
- L162 _protected member_ `TSharedPtr<class FPaperEditorViewportClient> PaperViewportClient;` — Level viewport client
- L165 _protected member_ `FOnSelectionChanged OnSelectionChanged;` — Selection changed delegate

#### Free symbols / members of external scopes

- L80 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnSelectionChanged, FMarqueeOperation , bool );`

### `Plugins/2D/Paper2D/Source/Paper2DEditor/Private/SpriteAssetTypeActions.h` (Private)


#### class `FSpriteAssetTypeActions`  
`class FSpriteAssetTypeActions : public FAssetTypeActions_Base`  
_L9-29_
- inherits: `FAssetTypeActions_Base`
- L12 _public prototype_ `FSpriteAssetTypeActions(EAssetTypeCategories::Type InAssetCategory);`
- L15 _public prototype_ `virtual FText GetName() const override;` — IAssetTypeActions interface
- L16 _public prototype_ `virtual FColor GetTypeColor() const override;`
- L17 _public prototype_ `virtual UClass* GetSupportedClass() const override;`
- L18 _public prototype_ `virtual void GetActions(const TArray<UObject*>& InObjects, struct FToolMenuSection& Section) override;`
- L19 _public prototype_ `virtual void OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<class IToolkitHost> EditWithinLevelEditor = TSharedPtr<IToolkitHost>()) override;`
- L20 _public prototype_ `virtual uint32 GetCategories() override;`
- L24 _private member_ `EAssetTypeCategories::Type MyAssetCategory;`
- L28 _private prototype_ `void ExecuteCreateFlipbook(TArray<TWeakObjectPtr<UPaperSprite>> Objects);` — Handler for "Create Flipbook"

### `Plugins/2D/Paper2D/Source/Paper2DEditor/Private/SpriteCanvas.h` (Private)
_(no declarations extracted)_

### `Plugins/2D/Paper2D/Source/Paper2DEditor/Private/SpriteEditor/SSpriteEditorViewportToolbar.h` (Private)


#### class `SSpriteEditorViewportToolbar`  
`class SSpriteEditorViewportToolbar : public SCommonEditorViewportToolbarBase`  
_L8-20_
- inherits: `SCommonEditorViewportToolbarBase`
- desc: In-viewport toolbar widget used in the sprite editor
- L11 _public function_ `SLATE_BEGIN_ARGS(SSpriteEditorViewportToolbar)`
- L12 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedPtr<class ICommonEditorViewportToolbarInfoProvider> InInfoProvider);`
- L17 _public prototype_ `virtual TSharedRef<SWidget> GenerateShowMenu() const override;` — SCommonEditorViewportToolbarBase interface

### `Plugins/2D/Paper2D/Source/Paper2DEditor/Private/SpriteEditor/SSpriteList.h` (Private)


#### class `SSpriteList`  
`class SSpriteList : public SCompoundWidget`  
_L13-46_
- inherits: `SCompoundWidget`
- L16 _public function_ `SLATE_BEGIN_ARGS(SSpriteList)`
- L19 _public prototype_ `void Construct(const FArguments& InArgs, TSharedPtr<class FSpriteEditor> InSpriteEditor);`
- L22 _public prototype_ `virtual void Tick( const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime ) override;` — SWidget interface
- L25 _public prototype_ `void SelectAsset(UObject* Asset);`
- L28 _protected prototype_ `void RebuildWidget(UTexture2D* NewTextureFilter);`
- L30 _protected prototype_ `void OnSpriteSelected(const struct FAssetData& AssetData);`
- L31 _protected prototype_ `void OnSpriteDoubleClicked(const struct FAssetData& AssetData);`
- L32 _protected prototype_ `bool CanShowColumnForAssetRegistryTag(FName AssetType, FName TagName) const;`
- L36 _protected member_ `TWeakObjectPtr<UTexture2D> SourceTexturePtr;` — Last source texture we saw (used to discern when the texture has changed)
- L39 _protected member_ `TWeakPtr<class FSpriteEditor> SpriteEditorPtr;` — Pointer back to owning sprite editor instance (the keeper of state)
- L42 _protected member_ `TSet<FName> AssetRegistryTagsToIgnore;` — Set of tags to prevent creating details view columns for (infrequently used)
- L45 _protected member_ `FSyncToAssetsDelegate SyncToAssetsDelegate;` — Delegate to sync the asset picker to selected assets

### `Plugins/2D/Paper2D/Source/Paper2DEditor/Private/SpriteEditor/SpriteComponentDetailsCustomization.h` (Private)


#### class `FSpriteComponentDetailsCustomization`  
`class FSpriteComponentDetailsCustomization : public IDetailCustomization`  
_L15-30_
- inherits: `IDetailCustomization`
- L19 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L22 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailLayout) override;` — IDetailCustomization interface
- L26 _protected prototype_ `FReply MergeSprites();`
- L29 _protected member_ `TArray<TWeakObjectPtr<UObject>> ObjectsBeingCustomized;`

### `Plugins/2D/Paper2D/Source/Paper2DEditor/Private/SpriteEditor/SpriteDetailsCustomization.h` (Private)


#### class `FSpriteDetailsCustomization`  
`class FSpriteDetailsCustomization : public IDetailCustomization`  
_L20-66_
- inherits: `IDetailCustomization`
- L24 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L27 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstanceForSpriteEditor(TAttribute<ESpriteEditorMode::Type> InEditMode);` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L30 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailLayout) override;` — IDetailCustomization interface
- L34 _protected prototype_ `FSpriteDetailsCustomization(TAttribute<ESpriteEditorMode::Type> InEditMode);`
- L36 _protected prototype_ `EVisibility EditorModeMatches(ESpriteEditorMode::Type DesiredMode) const;`
- L37 _protected prototype_ `EVisibility EditorModeIsNot(ESpriteEditorMode::Type DesiredMode) const;`
- L38 _protected prototype_ `EVisibility PhysicsModeMatches(TSharedPtr<IPropertyHandle> Property, ESpriteCollisionMode::Type DesiredMode) const;`
- L39 _protected prototype_ `EVisibility AnyPhysicsMode(TSharedPtr<IPropertyHandle> Property) const;`
- L40 _protected prototype_ `EVisibility GetCustomPivotVisibility(TSharedPtr<IPropertyHandle> Property) const;`
- L42 _protected prototype_ `EVisibility PolygonModeMatches(TSharedPtr<IPropertyHandle> Property, ESpritePolygonMode::Type DesiredMode) const;`
- L44 _protected prototype_ `FText GetCollisionHeaderContentText(TSharedPtr<IPropertyHandle> Property) const;`
- L45 _protected prototype_ `FText GetRenderingHeaderContentText(TWeakObjectPtr<class UPaperSprite> WeakSprite) const;`
- L47 _protected prototype_ `static EVisibility GetAtlasGroupVisibility();`
- L49 _protected prototype_ `static FDetailWidgetRow& GenerateWarningRow(IDetailCategoryBuilder& WarningCategory, bool bExperimental, const FText& WarningText, const FText& Tooltip, const FString& ExcerptLink, const FString& ExcerptName);`
- L51 _protected prototype_ `void BuildSpriteSection(IDetailCategoryBuilder& SpriteCategory, IDetailLayoutBuilder& DetailLayout);`
- L52 _protected prototype_ `void BuildCollisionSection(IDetailCategoryBuilder& CollisionCategory, IDetailLayoutBuilder& DetailLayout);`
- L53 _protected prototype_ `void BuildRenderingSection(IDetailCategoryBuilder& RenderingCategory, IDetailLayoutBuilder& DetailLayout);`
- L55 _protected prototype_ `void BuildTextureSection(IDetailCategoryBuilder& SpriteCategory, IDetailLayoutBuilder& DetailLayout);`
- L56 _protected prototype_ `void GenerateAdditionalTextureWidget(TSharedRef<IPropertyHandle> PropertyHandle, int32 ArrayIndex, IDetailChildrenBuilder& ChildrenBuilder);`
- L59 _protected prototype_ `TSharedRef<SWidget> CreateTextureNameWidget(TSharedPtr<IPropertyHandle> PropertyHandle, const FText& OverrideText);` — Creates a name widget with optional captioning label
- L62 _protected member_ `TAttribute<ESpriteEditorMode::Type> SpriteEditMode;`
- L65 _protected member_ `TMap<int32, FText> AdditionalTextureLabels;` — These are labels harvested from the material

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace ESpriteCollisionMode`
- L9 _namespace_ `namespace ESpritePolygonMode`

### `Plugins/2D/Paper2D/Source/Paper2DEditor/Private/SpriteEditor/SpriteEditor.h` (Private)


#### enum `ESpriteEditorMode::Type`  
`enum Type`  
_L20-26_
- L22 _public enumerator_ `ViewMode`
- L23 _public enumerator_ `EditSourceRegionMode`
- L24 _public enumerator_ `EditCollisionMode`
- L25 _public enumerator_ `EditRenderingGeomMode`

#### class `FSpriteEditor`  
`class FSpriteEditor : public FAssetEditorToolkit, public FGCObject`  
_L32-90_
- inherits: `FAssetEditorToolkit,FGCObject`
- L35 _public prototype_ `FSpriteEditor();`
- L38 _public prototype_ `virtual void RegisterTabSpawners(const TSharedRef<class FTabManager>& TabManager) override;` — IToolkit interface
- L39 _public prototype_ `virtual void UnregisterTabSpawners(const TSharedRef<class FTabManager>& TabManager) override;`
- L43 _public prototype_ `virtual FName GetToolkitFName() const override;` — FAssetEditorToolkit
- L44 _public prototype_ `virtual FText GetBaseToolkitName() const override;`
- L45 _public prototype_ `virtual FText GetToolkitName() const override;`
- L46 _public prototype_ `virtual FText GetToolkitToolTipText() const override;`
- L47 _public prototype_ `virtual FLinearColor GetWorldCentricTabColorScale() const override;`
- L48 _public prototype_ `virtual FString GetWorldCentricTabPrefix() const override;`
- L49 _public prototype_ `virtual FString GetDocumentationLink() const override;`
- L50 _public prototype_ `virtual void OnToolkitHostingStarted(const TSharedRef<class IToolkit>& Toolkit) override;`
- L51 _public prototype_ `virtual void OnToolkitHostingFinished(const TSharedRef<class IToolkit>& Toolkit) override;`
- L55 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;` — FSerializableObject interface
- L56 _public function_ `virtual FString GetReferencerName() const override`
- L63 _public prototype_ `UTexture2D* GetSourceTexture() const;` — Get the source texture for the current sprite being edited
- L65 _public prototype_ `void InitSpriteEditor(const EToolkitMode::Type Mode, const TSharedPtr< class IToolkitHost >& InitToolkitHost, class UPaperSprite* InitSprite);`
- L67 _public function_ `UPaperSprite* GetSpriteBeingEdited() const`
- L68 _public prototype_ `void SetSpriteBeingEdited(UPaperSprite* NewSprite);`
- L70 _public prototype_ `ESpriteEditorMode::Type GetCurrentMode() const;`
- L73 _protected member_ `TObjectPtr<UPaperSprite> SpriteBeingEdited;`
- L74 _protected member_ `TSharedPtr<SSpriteEditorViewport> ViewportPtr;`
- L75 _protected member_ `TSharedPtr<SSpriteList> SpriteListPtr;`
- L78 _protected prototype_ `void BindCommands();`
- L79 _protected prototype_ `void ExtendMenu();`
- L80 _protected prototype_ `void ExtendToolbar();`
- L81 _protected prototype_ `virtual void CreateEditorModeManager() override;`
- L83 _protected prototype_ `TSharedRef<SDockTab> SpawnTab_Viewport(const FSpawnTabArgs& Args);`
- L84 _protected prototype_ `TSharedRef<SDockTab> SpawnTab_Details(const FSpawnTabArgs& Args);`
- L85 _protected prototype_ `TSharedRef<SDockTab> SpawnTab_SpriteList(const FSpawnTabArgs& Args);`
- L87 _protected prototype_ `void CreateModeToolbarWidgets(FToolBarBuilder& ToolbarBuilder);`
- L89 _protected prototype_ `FText GetCurrentModeCornerText() const;`

#### Free symbols / members of external scopes

- L18 _namespace_ `namespace ESpriteEditorMode`

### `Plugins/2D/Paper2D/Source/Paper2DEditor/Private/SpriteEditor/SpriteEditorCommands.h` (Private)


#### class `FSpriteEditorCommands`  
`class FSpriteEditorCommands : public TCommands<FSpriteEditorCommands>`  
_L9-48_
- inherits: `TCommands<FSpriteEditorCommands>`
- L12 _public function_ `FSpriteEditorCommands() : TCommands<FSpriteEditorCommands>( TEXT("SpriteEditor"),`
- L23 _public prototype_ `virtual void RegisterCommands() override;` — TCommand<> interface
- L28 _public member_ `TSharedPtr<FUICommandInfo> SetShowGrid;` — Show toggles
- L29 _public member_ `TSharedPtr<FUICommandInfo> SetShowSourceTexture;`
- L30 _public member_ `TSharedPtr<FUICommandInfo> SetShowBounds;`
- L31 _public member_ `TSharedPtr<FUICommandInfo> SetShowCollision;`
- L33 _public member_ `TSharedPtr<FUICommandInfo> SetShowSockets;`
- L35 _public member_ `TSharedPtr<FUICommandInfo> SetShowPivot;`
- L36 _public member_ `TSharedPtr<FUICommandInfo> SetShowMeshEdges;`
- L39 _public member_ `TSharedPtr<FUICommandInfo> ExtractSprites;` — Source region edit mode
- L40 _public member_ `TSharedPtr<FUICommandInfo> ToggleShowRelatedSprites;`
- L41 _public member_ `TSharedPtr<FUICommandInfo> ToggleShowSpriteNames;`
- L44 _public member_ `TSharedPtr<FUICommandInfo> EnterViewMode;` — Editing modes
- L45 _public member_ `TSharedPtr<FUICommandInfo> EnterSourceRegionEditMode;`
- L46 _public member_ `TSharedPtr<FUICommandInfo> EnterCollisionEditMode;`
- L47 _public member_ `TSharedPtr<FUICommandInfo> EnterRenderingEditMode;`

### `Plugins/2D/Paper2D/Source/Paper2DEditor/Private/SpriteEditor/SpriteEditorSelections.h` (Private)


#### class `FSelectionTypes`  
`class FSelectionTypes`  
_L12-22_
- L15 _public member_ `static const FName GeometryShape;`
- L16 _public member_ `static const FName Vertex;`
- L17 _public member_ `static const FName Edge;`
- L18 _public member_ `static const FName Pivot;`
- L19 _public member_ `static const FName SourceRegion;`
- L21 _private function_ `FSelectionTypes()`

#### class `ISpriteSelectionContext`  
`class ISpriteSelectionContext`  
_L27-38_
- L30 _public prototype_ `virtual FVector2D SelectedItemConvertWorldSpaceDeltaToLocalSpace(const FVector& WorldSpaceDelta) const = 0;`
- L31 _public prototype_ `virtual FVector2D WorldSpaceToTextureSpace(const FVector& SourcePoint) const = 0;`
- L32 _public prototype_ `virtual FVector TextureSpaceToWorldSpace(const FVector2D& SourcePoint) const = 0;`
- L33 _public prototype_ `virtual float SelectedItemGetUnitsPerPixel() const = 0;`
- L34 _public prototype_ `virtual void BeginTransaction(const FText& SessionName) = 0;`
- L35 _public prototype_ `virtual void MarkTransactionAsDirty() = 0;`
- L36 _public prototype_ `virtual void EndTransaction() = 0;`
- L37 _public prototype_ `virtual void InvalidateViewportAndHitProxies() = 0;`

#### class `FSpriteSelectedSourceRegion`  
`class FSpriteSelectedSourceRegion : public FSelectedItem`  
_L43-206_
- inherits: `FSelectedItem`
- L46 _public member_ `int32 VertexIndex;`
- L47 _public member_ `TWeakObjectPtr<UPaperSprite> SpritePtr;`
- L50 _public function_ `FSpriteSelectedSourceRegion() : FSelectedItem(FSelectionTypes::SourceRegion) , VertexIndex(0)`
- L56 _public function_ `virtual uint32 GetTypeHash() const override`
- L61 _public function_ `virtual bool Equals(const FSelectedItem& OtherItem) const override`
- L76 _public function_ `virtual void ApplyDeltaIndexed(const FVector2D& WorldSpaceDelta, int32 TargetVertexIndex)`
- L146 _public function_ `FVector GetWorldPosIndexed(int32 TargetVertexIndex) const`
- L194 _public function_ `virtual void ApplyDelta(const FVector2D& Delta, const FRotator& Rotation, const FVector& Scale3D, UE::Widget::EWidgetMode MoveMode) override`
- L202 _public function_ `FVector GetWorldPos() const override`

#### class `FSpriteSelectedShape`  
`class FSpriteSelectedShape : public FSelectedItem`  
_L212-239_
- inherits: `FSelectedItem`
- L216 _public member_ `ISpriteSelectionContext* EditorContext;` — The editor context
- L219 _public member_ `FSpriteGeometryCollection& Geometry;` — The geometry that this shape belongs to
- L222 _public member_ `const int32 ShapeIndex;` — The index of this shape in the geometry above
- L225 _public member_ `const bool bIsBackground;` — Is this a background object that should have lower priority?
- L227 _public member_ `TWeakObjectPtr<UPaperSprite> SpritePtr;`
- L229 _public prototype_ `FSpriteSelectedShape(ISpriteSelectionContext* InEditorContext, FSpriteGeometryCollection& InGeometry, int32 InShapeIndex, bool bInIsBackground = false);`
- L232 _public prototype_ `virtual uint32 GetTypeHash() const override;` — FSelectedItem interface
- L233 _public prototype_ `virtual EMouseCursor::Type GetMouseCursor() const override;`
- L234 _public prototype_ `virtual bool Equals(const FSelectedItem& OtherItem) const override;`
- L235 _public prototype_ `virtual bool IsBackgroundObject() const override;`
- L236 _public prototype_ `virtual void ApplyDelta(const FVector2D& Delta, const FRotator& Rotation, const FVector& Scale3D, UE::Widget::EWidgetMode MoveMode) override;`
- L237 _public prototype_ `virtual FVector GetWorldPos() const override;`

#### class `FSpriteSelectedVertex`  
`class FSpriteSelectedVertex : public FSelectedItem`  
_L244-340_
- inherits: `FSelectedItem`
- L248 _public member_ `ISpriteSelectionContext* EditorContext;` — The editor context
- L251 _public member_ `FSpriteGeometryCollection& Geometry;` — The geometry that this shape belongs to
- L253 _public member_ `const int32 ShapeIndex;`
- L254 _public member_ `const int32 VertexIndex;`
- L257 _public function_ `FSpriteSelectedVertex(ISpriteSelectionContext* InEditorContext, FSpriteGeometryCollection& InGeometry, int32 InShapeIndex, int32 InVertexIndex) : FSelectedItem(FSelectionTypes::Vertex) , EditorContext(InEditorContext) , Geometry(InGeometry) , ShapeIndex(InShapeIndex) , VertexIndex(InVertexIndex)`
- L266 _public function_ `virtual uint32 GetTypeHash() const override`
- L271 _public function_ `virtual bool Equals(const FSelectedItem& OtherItem) const override`
- L286 _public function_ `virtual void ApplyDeltaIndexed(const FVector2D& Delta, int32 TargetVertexIndex)`
- L308 _public function_ `FVector GetWorldPosIndexed(int32 TargetVertexIndex) const`
- L328 _public function_ `virtual void ApplyDelta(const FVector2D& Delta, const FRotator& Rotation, const FVector& Scale3D, UE::Widget::EWidgetMode MoveMode) override`
- L336 _public function_ `FVector GetWorldPos() const override`

#### class `FSpriteSelectedEdge`  
`class FSpriteSelectedEdge : public FSpriteSelectedVertex`  
_L347-389_
- inherits: `FSpriteSelectedVertex`
- desc: Note: Defined based on a vertex index; this is the edge between the vertex and the next one.
- L350 _public function_ `FSpriteSelectedEdge(ISpriteSelectionContext* InEditorContext, FSpriteGeometryCollection& InGeometry, int32 InShapeIndex, int32 InVertexIndex) : FSpriteSelectedVertex(InEditorContext, InGeometry, InShapeIndex, InVertexIndex)`
- L356 _public function_ `virtual bool IsA(FName TestType) const`
- L361 _public function_ `virtual bool Equals(const FSelectedItem& OtherItem) const override`
- L376 _public function_ `virtual void ApplyDelta(const FVector2D& Delta, const FRotator& Rotation, const FVector& Scale3D, UE::Widget::EWidgetMode MoveMode) override`
- L382 _public function_ `FVector GetWorldPos() const override`

### `Plugins/2D/Paper2D/Source/Paper2DEditor/Private/SpriteEditor/SpriteEditorSettings.h` (Private)


#### class `USpriteEditorSettings`  
`class USpriteEditorSettings : public UObject`  
_L9-23_
- reflection: `UCLASS(config=EditorPerProjectUserSettings)`
- inherits: `UObject`
- desc: Settings for the Paper2D sprite editor
- L14 _public prototype_ `USpriteEditorSettings();`
- L18 _public member_ `FColor BackgroundColor;` — `UPROPERTY(config, EditAnywhere, Category=Background, meta=(HideAlphaChannel))` — Background color in the sprite editor
- L22 _public member_ `bool bShowGridByDefault;` — `UPROPERTY(config, EditAnywhere, Category=Background)` — Should the grid be shown by default when the editor is opened?

### `Plugins/2D/Paper2D/Source/Paper2DEditor/Private/SpriteEditor/SpriteEditorViewportClient.h` (Private)


#### struct `FRelatedSprite`  
`struct FRelatedSprite`  
_L16-21_
- L18 _public member_ `FAssetData AssetData;`
- L19 _public member_ `FVector2D SourceUV;`
- L20 _public member_ `FVector2D SourceDimension;`

#### class `FSpriteEditorViewportClient`  
`class FSpriteEditorViewportClient : public FPaperEditorViewportClient, public ISpriteSelectionContext`  
_L26-181_
- inherits: `FPaperEditorViewportClient,ISpriteSelectionContext`
- L30 _public prototype_ `FSpriteEditorViewportClient(TWeakPtr<FSpriteEditor> InSpriteEditor, TWeakPtr<class SEditorViewport> InSpriteEditorViewportPtr);` — Constructor
- L33 _public prototype_ `virtual void Draw(const FSceneView* View, FPrimitiveDrawInterface* PDI) override;` — FViewportClient interface
- L34 _public prototype_ `virtual void DrawCanvas(FViewport& InViewport, FSceneView& View, FCanvas& Canvas) override;`
- L35 _public prototype_ `virtual void Tick(float DeltaSeconds) override;`
- L39 _public prototype_ `virtual void ProcessClick(FSceneView& View, HHitProxy* HitProxy, FKey Key, EInputEvent Event, uint32 HitX, uint32 HitY) override;` — FEditorViewportClient interface
- L40 _public prototype_ `virtual bool InputKey(const FInputKeyEventArgs& EventArgs) override;`
- L41 _public prototype_ `virtual void TrackingStarted(const struct FInputEventState& InInputState, bool bIsDragging, bool bNudge) override;`
- L42 _public prototype_ `virtual void TrackingStopped() override;`
- L43 _public prototype_ `virtual FLinearColor GetBackgroundColor() const override;`
- L47 _public prototype_ `virtual FVector2D SelectedItemConvertWorldSpaceDeltaToLocalSpace(const FVector& WorldSpaceDelta) const override;` — ISpriteSelectionContext interface
- L48 _public prototype_ `virtual FVector2D WorldSpaceToTextureSpace(const FVector& SourcePoint) const override;`
- L49 _public prototype_ `virtual FVector TextureSpaceToWorldSpace(const FVector2D& SourcePoint) const override;`
- L50 _public prototype_ `virtual float SelectedItemGetUnitsPerPixel() const override;`
- L51 _public prototype_ `virtual void BeginTransaction(const FText& SessionName) override;`
- L52 _public prototype_ `virtual void MarkTransactionAsDirty() override;`
- L53 _public prototype_ `virtual void EndTransaction() override;`
- L54 _public prototype_ `virtual void InvalidateViewportAndHitProxies() override;`
- L57 _public prototype_ `void ActivateEditMode();`
- L59 _public function_ `void ToggleShowSockets()`
- L60 _public function_ `bool IsShowSocketsChecked() const`
- L62 _public function_ `void ToggleShowPivot()`
- L63 _public function_ `bool IsShowPivotChecked() const`
- L65 _public prototype_ `void ToggleShowMeshEdges();`
- L66 _public prototype_ `bool IsShowMeshEdgesChecked() const;`
- L68 _public function_ `void EnterViewMode()`
- L69 _public function_ `void EnterSourceRegionEditMode()`
- L70 _public function_ `void EnterCollisionEditMode()`
- L71 _public function_ `void EnterRenderingEditMode()`
- L73 _public function_ `bool IsInViewMode() const`
- L74 _public function_ `bool IsInSourceRegionEditMode() const`
- L75 _public function_ `bool IsInCollisionEditMode() const`
- L76 _public function_ `bool IsInRenderingEditMode() const`
- L79 _public function_ `bool IsEditingGeometry() const`
- L81 _public prototype_ `void ToggleShowSourceTexture();`
- L82 _public function_ `bool IsShowSourceTextureChecked() const`
- L83 _public function_ `bool CanShowSourceTexture() const`
- L85 _public prototype_ `void ToggleShowRelatedSprites();`
- L86 _public function_ `bool IsShowRelatedSpritesChecked() const`
- L88 _public prototype_ `void ToggleShowSpriteNames();`
- L89 _public function_ `bool IsShowSpriteNamesChecked() const`
- L92 _public prototype_ `void NotifySpriteBeingEditedHasChanged();` — Invalidate any references to the sprite being edited; it has changed
- L94 _public prototype_ `void UpdateRelatedSpritesList();`
- L96 _public prototype_ `UPaperSprite* CreateNewSprite(const FIntPoint& TopLeft, const FIntPoint& Dimensions);`
- L98 _public function_ `ESpriteEditorMode::Type GetCurrentMode() const`
- L103 _public prototype_ `static void AnalyzeSpriteMaterialType(UPaperSprite* Sprite, int32& OutNumOpaque, int32& OutNumMasked, int32& OutNumTranslucent);`
- L107 _protected prototype_ `virtual FBox GetDesiredFocusBounds() const override;` — FPaperEditorViewportClient interface
- L112 _private member_ `ESpriteEditorMode::Type CurrentMode;` — Editor mode
- L115 _private member_ `FPreviewScene OwnedPreviewScene;` — The preview scene
- L118 _private member_ `TWeakPtr<FSpriteEditor> SpriteEditorPtr;` — Sprite editor that owns this viewport
- L121 _private member_ `UPaperSpriteComponent* SourceTextureViewComponent;` — Render component for the source texture view
- L124 _private member_ `UPaperSpriteComponent* RenderSpriteComponent;` — Render component for the sprite being edited
- L130 _private member_ `bool bManipulating;` — Are we currently manipulating something?
- L133 _private member_ `bool bManipulationDirtiedSomething;` — Did we dirty something during manipulation?
- L136 _private member_ `TWeakPtr<class SEditorViewport> SpriteEditorViewportPtr;` — Pointer back to the sprite editor viewport control that owns us
- L139 _private member_ `class FScopedTransaction* ScopedTransaction;` — The current transaction for undo/redo
- L142 _private member_ `bool bShowSourceTexture;` — Should we show the source texture?
- L145 _private member_ `bool bShowSockets;` — Should we show sockets?
- L148 _private member_ `bool bShowPivot;` — Should we show the sprite pivot?
- L151 _private member_ `bool bShowRelatedSprites;` — Should we show related sprites in the source texture?
- L154 _private member_ `bool bShowNamesForSprites;` — Should we show names for sprites in the source region edit mode?
- L157 _private member_ `TArray<FRelatedSprite> RelatedSprites;` — Other sprites that share the same source texture
- L160 _private function_ `UPaperSprite* GetSpriteBeingEdited() const`
- L166 _private prototype_ `FVector2D SourceTextureSpaceToScreenSpace(const FSceneView& View, const FVector2D& SourcePoint) const;` — Position relative to source texture (ignoring rotation and other transformations applied to extract the sprite)
- L167 _private prototype_ `FVector SourceTextureSpaceToWorldSpace(const FVector2D& SourcePoint) const;`
- L169 _private prototype_ `void DrawBoundsAsText(FViewport& InViewport, FSceneView& View, FCanvas& Canvas, int32& YPos);`
- L171 _private prototype_ `void DrawRenderStats(FViewport& InViewport, FSceneView& View, FCanvas& Canvas, class UPaperSprite* Sprite, int32& YPos);`
- L172 _private prototype_ `void DrawSourceRegion(FViewport& InViewport, FSceneView& View, FCanvas& Canvas, const FLinearColor& GeometryVertexColor);`
- L173 _private prototype_ `void DrawRelatedSprites(FViewport& InViewport, FSceneView& View, FCanvas& Canvas, const FLinearColor& BoundsColor, const FLinearColor& NameColor);`
- L175 _private prototype_ `void UpdateSourceTextureSpriteFromSprite(UPaperSprite* SourceSprite);`
- L177 _private prototype_ `bool ConvertMarqueeToSourceTextureSpace( FIntPoint& OutStartPos, FIntPoint& OutDimension);`
- L180 _private prototype_ `void InternalActivateNewMode(ESpriteEditorMode::Type NewMode);` — Activates a new mode, clearing selection set, etc...

### `Plugins/2D/Paper2D/Source/Paper2DEditor/Private/SpriteEditor/SpritePolygonCollectionCustomization.h` (Private)


#### class `FSpritePolygonCollectionCustomization`  
`class FSpritePolygonCollectionCustomization : public IPropertyTypeCustomization`  
_L13-26_
- inherits: `IPropertyTypeCustomization`
- L17 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();` — Makes a new instance of this customization
- L20 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;` — IPropertyTypeCustomization interface
- L21 _public prototype_ `virtual void CustomizeChildren(TSharedRef<class IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L25 _protected prototype_ `EVisibility PolygonModeMatches(TSharedPtr<IPropertyHandle> Property, ESpritePolygonMode::Type DesiredMode) const;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace ESpritePolygonMode`

### `Plugins/2D/Paper2D/Source/Paper2DEditor/Private/TileMapEditing/EdModeTileMap.h` (Private)


#### enum `ETileMapEditorTool::Type`  
`enum Type`  
_L19-26_
- L21 _public enumerator_ `Paintbrush`
- L22 _public enumerator_ `Eraser`
- L23 _public enumerator_ `PaintBucket`
- L24 _public enumerator_ `EyeDropper`
- L25 _public enumerator_ `TerrainBrush`

#### struct `FTileMapDirtyRegion`  
`struct FTileMapDirtyRegion`  
_L32-51_
- L35 _public member_ `TWeakObjectPtr<UPaperTileMapComponent> ComponentPtr;`
- L36 _public member_ `FBox DirtyRegionInWorldSpace;`
- L39 _public function_ `FTileMapDirtyRegion()`
- L43 _public prototype_ `FTileMapDirtyRegion(UPaperTileMapComponent* InComponent, const FBox& DirtyRegionInTileSpace);`
- L45 _public prototype_ `void PushToNavSystem() const;`
- L47 _public function_ `UPaperTileMapComponent* GetComponent() const`

#### class `FEdModeTileMap`  
`class FEdModeTileMap : public FEdMode`  
_L56-193_
- inherits: `FEdMode`
- L59 _public member_ `static const FEditorModeID EM_TileMap;`
- L62 _public prototype_ `FEdModeTileMap();`
- L63 _public prototype_ `virtual ~FEdModeTileMap();`
- L66 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;` — FSerializableObject interface
- L70 _public prototype_ `virtual bool UsesToolkits() const override;` — FEdMode interface
- L71 _public prototype_ `virtual void Enter() override;`
- L72 _public prototype_ `virtual void Exit() override;`
- L73 _public prototype_ `virtual void Tick(FEditorViewportClient* ViewportClient, float DeltaTime) override;`
- L74 _public prototype_ `virtual bool MouseEnter(FEditorViewportClient* ViewportClient, FViewport* Viewport, int32 x, int32 y) override;`
- L75 _public prototype_ `virtual bool MouseLeave(FEditorViewportClient* ViewportClient, FViewport* Viewport) override;`
- L76 _public prototype_ `virtual bool MouseMove(FEditorViewportClient* ViewportClient, FViewport* Viewport, int32 x, int32 y) override;`
- L77 _public prototype_ `virtual bool CapturedMouseMove(FEditorViewportClient* InViewportClient, FViewport* InViewport, int32 InMouseX, int32 InMouseY) override;`
- L78 _public prototype_ `virtual bool StartTracking(FEditorViewportClient* InViewportClient, FViewport* InViewport) override;`
- L79 _public prototype_ `virtual bool EndTracking(FEditorViewportClient* InViewportClient, FViewport* InViewport) override;`
- L80 _public prototype_ `virtual bool InputKey(FEditorViewportClient* InViewportClient, FViewport* InViewport, FKey InKey, EInputEvent InEvent) override;`
- L81 _public prototype_ `virtual bool InputDelta(FEditorViewportClient* InViewportClient, FViewport* InViewport, FVector& InDrag, FRotator& InRot, FVector& InScale) override;`
- L82 _public prototype_ `virtual void Render(const FSceneView* View, FViewport* Viewport, FPrimitiveDrawInterface* PDI) override;`
- L83 _public prototype_ `virtual void DrawHUD(FEditorViewportClient* ViewportClient, FViewport* Viewport, const FSceneView* View, FCanvas* Canvas) override;`
- L84 _public prototype_ `virtual void ActorSelectionChangeNotify() override;`
- L85 _public prototype_ `virtual bool AllowWidgetMove() override;`
- L86 _public prototype_ `virtual bool ShouldDrawWidget() const override;`
- L87 _public prototype_ `virtual bool UsesTransformWidget() const override;`
- L90 _public prototype_ `void SetActiveTool(ETileMapEditorTool::Type NewTool);`
- L91 _public prototype_ `ETileMapEditorTool::Type GetActiveTool() const;`
- L93 _public prototype_ `void SetActivePaint(UPaperTileSet* TileSet, FIntPoint TopLeft, FIntPoint Dimensions);`
- L94 _public prototype_ `void SetActivePaintFromLayer(UPaperTileLayer* SourceLayer, FIntPoint TopLeft, FIntPoint Dimensions);`
- L96 _public prototype_ `void DestructiveResizePreviewComponent(int32 NewWidth, int32 NewHeight);`
- L98 _public prototype_ `void FlipSelectionHorizontally();`
- L99 _public prototype_ `void FlipSelectionVertically();`
- L100 _public prototype_ `void RotateSelectionCW();`
- L101 _public prototype_ `void RotateSelectionCCW();`
- L102 _public prototype_ `bool HasValidSelection() const;`
- L104 _public prototype_ `void RefreshBrushSize();`
- L107 _protected prototype_ `bool UseActiveToolAtLocation(const FViewportCursorLocation& Ray);`
- L109 _protected prototype_ `bool SelectTiles(const FViewportCursorLocation& Ray);`
- L110 _protected prototype_ `bool PaintTiles(const FViewportCursorLocation& Ray);`
- L111 _protected prototype_ `bool EraseTiles(const FViewportCursorLocation& Ray);`
- L112 _protected prototype_ `bool FloodFillTiles(const FViewportCursorLocation& Ray);`
- L113 _protected prototype_ `bool PaintTilesWithTerrain(const FViewportCursorLocation& Ray);`
- L116 _protected prototype_ `void UpdatePreviewCursor(const FViewportCursorLocation& Ray);`
- L120 _protected prototype_ `UPaperTileLayer* GetSelectedLayerUnderCursor(const FViewportCursorLocation& Ray, int32& OutTileX, int32& OutTileY, bool bAllowOutOfBounds = false) const;` — Returns the selected layer under the cursor, and the intersection tile coordinates Note: The tile coordinates can be negative if the brush is off the top or left of the tile map, but still overlaps the map!!!
- L123 _protected prototype_ `FViewportCursorLocation CalculateViewRay(FEditorViewportClient* InViewportClient, FViewport* InViewport);` — Compute a world space ray from the screen space mouse coordinates
- L125 _protected prototype_ `TSharedRef<FExtender> AddCreationModeExtender(const TSharedRef<FUICommandList> InCommandList);`
- L127 _protected prototype_ `void EnableTileMapEditMode();`
- L128 _protected prototype_ `bool IsTileMapEditModeActive() const;`
- L130 _protected prototype_ `void SynchronizePreviewWithTileMap(UPaperTileMap* NewTileMap);`
- L132 _protected prototype_ `void RotateTilesInSelection(bool bIsClockwise);`
- L134 _protected prototype_ `bool IsToolReadyToBeUsed() const;`
- L136 _protected prototype_ `bool BlitLayer(UPaperTileLayer* SourceLayer, UPaperTileLayer* TargetLayer, FBox& OutDirtyRect, int32 OffsetX = 0, int32 OffsetY = 0, bool bBlitEmptyTiles = false);`
- L138 _protected prototype_ `void FlushPendingDirtyRegions();`
- L140 _public prototype_ `UPaperTileMapComponent* FindSelectedComponent() const;`
- L142 _public prototype_ `UPaperTileLayer* GetSourceInkLayer() const;`
- L144 _public prototype_ `int32 GetBrushWidth() const;`
- L145 _public prototype_ `int32 GetBrushHeight() const;`
- L147 _public prototype_ `int32 GetCursorWidth() const;`
- L148 _public prototype_ `int32 GetCursorHeight() const;`
- L151 _protected member_ `bool bWasPainting;` — Were we previously painting?
- L154 _protected member_ `bool bIsPainting;` — Are we currently painting?
- L157 _protected member_ `bool bHasValidInkSource;` — Ink source
- L160 _protected member_ `bool bWasHoldingSelectWhenPaintingStarted;` — State for eyedropper
- L161 _protected member_ `FIntPoint EyeDropperStart;`
- L162 _protected member_ `FIntRect LastEyeDropperBounds;`
- L165 _protected member_ `FTransform DrawPreviewSpace;`
- L168 _protected member_ `FVector DrawPreviewLocation;` — Center of preview rectangle
- L171 _protected member_ `int32 LastCursorTileX;` — Size of rectangle
- L172 _protected member_ `int32 LastCursorTileY;`
- L173 _protected member_ `int32 LastCursorTileZ;`
- L174 _protected member_ `bool bIsLastCursorValid;`
- L175 _protected member_ `TWeakObjectPtr<UPaperTileMap> LastCursorTileMap;`
- L177 _protected member_ `FVector DrawPreviewDimensionsLS;`
- L180 _protected member_ `FVector DrawPreviewTopLeft;` — Top left of the component bounds
- L182 _protected member_ `int32 EraseBrushSize;`
- L184 _protected member_ `UPaperTileMapComponent* CursorPreviewComponent;`
- L187 _protected member_ `float TimeUntilNavMeshRebuild;` — Nav mesh rebuilding
- L188 _protected member_ `TArray<FTileMapDirtyRegion> PendingDirtyRegions;`
- L191 _protected member_ `ETileMapEditorTool::Type ActiveTool;`
- L192 _protected member_ `mutable FTransform ComponentToWorld;`

#### Free symbols / members of external scopes

- L17 _namespace_ `namespace ETileMapEditorTool`

### `Plugins/2D/Paper2D/Source/Paper2DEditor/Private/TileMapEditing/PaperTileMapAssetBroker.h` (Private)


#### class `FPaperTileMapAssetBroker`  
`class FPaperTileMapAssetBroker : public IComponentAssetBroker`  
_L12-48_
- inherits: `IComponentAssetBroker`
- L15 _public function_ `UClass* GetSupportedAssetClass() override`
- L20 _public function_ `virtual bool AssignAssetToComponent(UActorComponent* InComponent, UObject* InAsset) override`
- L36 _public function_ `virtual UObject* GetAssetFromComponent(UActorComponent* InComponent) override`

### `Plugins/2D/Paper2D/Source/Paper2DEditor/Private/TileMapEditing/PaperTileMapDetailsCustomization.h` (Private)


#### class `FPaperTileMapDetailsCustomization`  
`class FPaperTileMapDetailsCustomization : public IDetailCustomization`  
_L16-54_
- inherits: `IDetailCustomization`
- L20 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L23 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailLayout) override;` — IDetailCustomization interface
- L27 _private member_ `TWeakObjectPtr<class UPaperTileMap> TileMapPtr;`
- L28 _private member_ `TWeakObjectPtr<class UPaperTileMapComponent> TileMapComponentPtr;`
- L30 _private member_ `IDetailLayoutBuilder* MyDetailLayout;`
- L33 _private prototype_ `FReply EnterTileMapEditingMode();`
- L34 _private prototype_ `FReply OnNewButtonClicked();`
- L35 _private prototype_ `FReply OnPromoteToAssetButtonClicked();`
- L36 _private prototype_ `FReply OnMakeInstanceFromAssetButtonClicked();`
- L38 _private prototype_ `EVisibility GetNonEditModeVisibility() const;`
- L40 _private prototype_ `EVisibility GetVisibilityForInstancedOnlyProperties() const;`
- L42 _private prototype_ `EVisibility GetVisibilityForMakeIntoInstance() const;`
- L44 _private prototype_ `EVisibility GetNewButtonVisiblity() const;`
- L46 _private prototype_ `bool GetIsEditModeEnabled() const;`
- L48 _private prototype_ `bool InLevelEditorContext() const;`
- L49 _private prototype_ `bool IsInstanced() const;`
- L51 _private prototype_ `void OnSelectedLayerChanged();`
- L53 _private prototype_ `FText GetLayerSettingsHeadingText() const;`

### `Plugins/2D/Paper2D/Source/Paper2DEditor/Private/TileMapEditing/STileLayerItem.h` (Private)


#### class `STileLayerItem`  
`class STileLayerItem : public SCompoundWidget`  
_L18-47_
- inherits: `SCompoundWidget`
- L21 _public function_ `SLATE_BEGIN_ARGS(STileLayerItem)`
- L22 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, int32 Index, class UPaperTileMap* InMap, FIsSelected InIsSelectedDelegate);`
- L26 _public prototype_ `void BeginEditingName();`
- L29 _protected member_ `int32 MyIndex;`
- L30 _protected member_ `UPaperTileMap* MyMap;`
- L31 _protected function_ `UPaperTileLayer* GetMyLayer() const`
- L33 _protected member_ `TSharedPtr<SButton> VisibilityButton;`
- L35 _protected member_ `const FSlateBrush* EyeClosed;`
- L36 _protected member_ `const FSlateBrush* EyeOpened;`
- L38 _protected member_ `TSharedPtr<SInlineEditableTextBlock> LayerNameWidget;`
- L41 _protected prototype_ `FText GetLayerDisplayName() const;`
- L42 _protected prototype_ `void OnLayerNameCommitted(const FText& NewText, ETextCommit::Type CommitInfo);`
- L44 _protected prototype_ `const FSlateBrush* GetVisibilityBrushForLayer() const;`
- L45 _protected prototype_ `FSlateColor GetForegroundColorForVisibilityButton() const;`
- L46 _protected prototype_ `FReply OnToggleVisibility();`

### `Plugins/2D/Paper2D/Source/Paper2DEditor/Private/TileMapEditing/STileLayerList.h` (Private)


#### class `STileLayerList`  
`class STileLayerList : public SCompoundWidget, public FEditorUndoClient`  
_L20-99_
- inherits: `SCompoundWidget,FEditorUndoClient`
- L23 _public function_ `SLATE_BEGIN_ARGS(STileLayerList)`
- L24 _public prototype_ `SLATE_EVENT(FSimpleDelegate, OnSelectedLayerChanged) SLATE_END_ARGS() void Construct(const FArguments& InArgs, UPaperTileMap* TileMap, FNotifyHook* InNotifyHook, TSharedPtr<class FUICommandList> InCommandList);`
- L30 _public prototype_ `virtual void PostUndo(bool bSuccess) override;` — FEditorUndoClient Interface
- L31 _public prototype_ `virtual void PostRedo(bool bSuccess) override;`
- L34 _public prototype_ `~STileLayerList();`
- L36 _protected typedef_ `typedef TSharedPtr<int32> FMirrorEntry;`
- L38 _protected member_ `TArray<FMirrorEntry> MirrorList;`
- L39 _protected typedef_ `typedef SListView<FMirrorEntry> SPaperLayerListView;`
- L42 _protected member_ `TSharedPtr<SPaperLayerListView> ListViewWidget;`
- L43 _protected member_ `TSharedPtr<class FUICommandList> CommandList;`
- L44 _protected member_ `TWeakObjectPtr<class UPaperTileMap> TileMapPtr;`
- L45 _protected member_ `FNotifyHook* NotifyHook;`
- L46 _protected member_ `FSimpleDelegate OnSelectedLayerChanged;`
- L48 _protected prototype_ `TSharedRef<ITableRow> OnGenerateLayerListRow(FMirrorEntry Item, const TSharedRef<STableViewBase>& OwnerTable);`
- L50 _protected prototype_ `class UPaperTileLayer* GetSelectedLayer() const;`
- L53 _protected prototype_ `int32 GetSelectionIndex() const;` — Returns the selected index if anything is selected, or the top item otherwise (only returns INDEX_NONE if there are no layers)
- L55 _protected prototype_ `static FText GenerateDuplicatedLayerName(const FString& InputNameRaw, UPaperTileMap* TileMap);`
- L57 _protected prototype_ `class UPaperTileLayer* AddLayer(int32 InsertionIndex = INDEX_NONE);`
- L60 _protected prototype_ `void ChangeLayerOrdering(int32 OldIndex, int32 NewIndex);` — Moves a layer from OldIndex to NewIndex if both are valid, otherwise it does nothing silently
- L62 _protected prototype_ `void AddNewLayerAbove();`
- L63 _protected prototype_ `void AddNewLayerBelow();`
- L65 _protected prototype_ `void CutLayer();`
- L66 _protected prototype_ `void CopyLayer();`
- L67 _protected prototype_ `void PasteLayerAbove();`
- L68 _protected prototype_ `bool CanPasteLayer() const;`
- L70 _protected prototype_ `void DuplicateLayer();`
- L71 _protected prototype_ `void DeleteLayer();`
- L72 _protected prototype_ `void RenameLayer();`
- L74 _protected prototype_ `void DeleteSelectedLayerWithNoTransaction();`
- L76 _protected prototype_ `void MergeLayerDown();`
- L77 _protected prototype_ `void MoveLayerUp(bool bForceToTop);`
- L78 _protected prototype_ `void MoveLayerDown(bool bForceToBottom);`
- L79 _protected prototype_ `void SelectLayerAbove(bool bTopmost);`
- L80 _protected prototype_ `void SelectLayerBelow(bool bBottommost);`
- L83 _protected prototype_ `void SetSelectedLayerIndex(int32 NewIndex);`
- L85 _protected prototype_ `int32 GetNumLayers() const;`
- L86 _protected prototype_ `bool CanExecuteActionNeedingLayerAbove() const;`
- L87 _protected prototype_ `bool CanExecuteActionNeedingLayerBelow() const;`
- L88 _protected prototype_ `bool CanExecuteActionNeedingSelectedLayer() const;`
- L90 _protected prototype_ `void SetSelectedLayer(UPaperTileLayer* SelectedLayer);`
- L92 _protected prototype_ `void OnSelectionChanged(FMirrorEntry ItemChangingState, ESelectInfo::Type SelectInfo);`
- L93 _protected prototype_ `TSharedPtr<SWidget> OnConstructContextMenu();`
- L95 _protected prototype_ `void RefreshMirrorList();`
- L98 _protected prototype_ `void PostEditNotfications();` — Called after edits are finished

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace ESelectInfo`

### `Plugins/2D/Paper2D/Source/Paper2DEditor/Private/TileMapEditing/STileMapEditorViewportToolbar.h` (Private)


#### class `STileMapEditorViewportToolbar`  
`class STileMapEditorViewportToolbar : public SCommonEditorViewportToolbarBase`  
_L8-19_
- inherits: `SCommonEditorViewportToolbarBase`
- desc: In-viewport toolbar widget used in the tile map editor
- L11 _public function_ `SLATE_BEGIN_ARGS(STileMapEditorViewportToolbar)`
- L12 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedPtr<class ICommonEditorViewportToolbarInfoProvider> InInfoProvider);`
- L17 _public prototype_ `virtual TSharedRef<SWidget> GenerateShowMenu() const override;` — SCommonEditorViewportToolbarBase interface

### `Plugins/2D/Paper2D/Source/Paper2DEditor/Private/TileMapEditing/TileMapAssetTypeActions.h` (Private)


#### class `FTileMapAssetTypeActions`  
`class FTileMapAssetTypeActions : public FAssetTypeActions_Base`  
_L7-22_
- inherits: `FAssetTypeActions_Base`
- L10 _public prototype_ `FTileMapAssetTypeActions(EAssetTypeCategories::Type InAssetCategory);`
- L13 _public prototype_ `virtual FText GetName() const override;` — IAssetTypeActions interface
- L14 _public prototype_ `virtual FColor GetTypeColor() const override;`
- L15 _public prototype_ `virtual UClass* GetSupportedClass() const override;`
- L16 _public prototype_ `virtual void OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<class IToolkitHost> EditWithinLevelEditor = TSharedPtr<IToolkitHost>()) override;`
- L17 _public prototype_ `virtual uint32 GetCategories() override;`
- L21 _private member_ `EAssetTypeCategories::Type MyAssetCategory;`

### `Plugins/2D/Paper2D/Source/Paper2DEditor/Private/TileMapEditing/TileMapEdModeToolkit.h` (Private)


#### class `FTileMapEdModeToolkit`  
`class FTileMapEdModeToolkit : public FModeToolkit`  
_L14-66_
- inherits: `FModeToolkit`
- L17 _public prototype_ `FTileMapEdModeToolkit(class FEdModeTileMap* InOwningMode);`
- L20 _public prototype_ `virtual FName GetToolkitFName() const override;` — IToolkit interface
- L21 _public prototype_ `virtual FText GetBaseToolkitName() const override;`
- L22 _public prototype_ `virtual FText GetToolkitName() const override;`
- L23 _public prototype_ `virtual FText GetToolkitToolTipText() const override;`
- L24 _public prototype_ `virtual class FEdMode* GetEditorMode() const override;`
- L25 _public prototype_ `virtual TSharedPtr<class SWidget> GetInlineContent() const override;`
- L29 _public prototype_ `virtual void Init(const TSharedPtr<class IToolkitHost>& InitToolkitHost) override;` — FModeToolkit interface
- L33 _protected prototype_ `void OnAssetsDropped(const FDragDropEvent&, TArrayView<FAssetData> InAssets);`
- L34 _protected prototype_ `void OnChangeTileSet(UObject* NewAsset);`
- L35 _protected prototype_ `UObject* GetCurrentTileSet() const;`
- L37 _protected prototype_ `void BindCommands();`
- L39 _protected prototype_ `void OnSelectTool(ETileMapEditorTool::Type NewTool);`
- L40 _protected prototype_ `bool IsToolSelected(ETileMapEditorTool::Type QueryTool) const;`
- L42 _protected prototype_ `bool DoesSelectedTileSetHaveTerrains() const;`
- L44 _protected prototype_ `TSharedRef<SWidget> BuildToolBar() const;`
- L45 _protected prototype_ `TSharedRef<SWidget> GenerateTerrainMenu();`
- L46 _protected prototype_ `void SetTerrainBrush(int32 NewTerrainTypeIndex);`
- L48 _protected prototype_ `EVisibility GetTileSetPaletteCornerTextVisibility() const;`
- L49 _protected prototype_ `FReply ClickedOnTileSetPaletteCornerText();`
- L51 _protected prototype_ `bool OnAssetDraggedOver(TArrayView<FAssetData> InAssets) const;`
- L54 _private member_ `class FEdModeTileMap* TileMapEditor;`
- L56 _private member_ `TWeakObjectPtr<class UPaperTileSet> CurrentTileSetPtr;`
- L59 _private member_ `TSharedPtr<class SWidget> MyWidget;` — All of the inline content for this toolkit
- L62 _private member_ `TSharedPtr<class STileSetSelectorViewport> TileSetPalette;` — The tile set selector palette
- L65 _private member_ `TSharedPtr<class SContentReference> TileSetAssetReferenceWidget;` — The tile set asset reference widget

### `Plugins/2D/Paper2D/Source/Paper2DEditor/Private/TileMapEditing/TileMapEditor.h` (Private)


#### class `FTileMapEditor`  
`class FTileMapEditor : public FAssetEditorToolkit, public FGCObject`  
_L15-63_
- inherits: `FAssetEditorToolkit,FGCObject`
- L18 _public prototype_ `FTileMapEditor();`
- L21 _public prototype_ `virtual void RegisterTabSpawners(const TSharedRef<class FTabManager>& TabManager) override;` — IToolkit interface
- L22 _public prototype_ `virtual void UnregisterTabSpawners(const TSharedRef<class FTabManager>& TabManager) override;`
- L26 _public prototype_ `virtual FName GetToolkitFName() const override;` — FAssetEditorToolkit
- L27 _public prototype_ `virtual FText GetBaseToolkitName() const override;`
- L28 _public prototype_ `virtual FText GetToolkitName() const override;`
- L29 _public prototype_ `virtual FText GetToolkitToolTipText() const override;`
- L30 _public prototype_ `virtual FLinearColor GetWorldCentricTabColorScale() const override;`
- L31 _public prototype_ `virtual FString GetWorldCentricTabPrefix() const override;`
- L32 _public prototype_ `virtual FString GetDocumentationLink() const override;`
- L33 _public prototype_ `virtual void OnToolkitHostingStarted(const TSharedRef< class IToolkit >& Toolkit) override;`
- L34 _public prototype_ `virtual void OnToolkitHostingFinished(const TSharedRef< class IToolkit >& Toolkit) override;`
- L38 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;` — FSerializableObject interface
- L39 _public function_ `virtual FString GetReferencerName() const override`
- L45 _public prototype_ `void InitTileMapEditor(const EToolkitMode::Type Mode, const TSharedPtr< class IToolkitHost >& InitToolkitHost, class UPaperTileMap* InitTileMap);`
- L47 _public function_ `UPaperTileMap* GetTileMapBeingEdited() const`
- L48 _public prototype_ `void SetTileMapBeingEdited(UPaperTileMap* NewTileMap);`
- L50 _protected member_ `TObjectPtr<UPaperTileMap> TileMapBeingEdited;`
- L51 _protected member_ `TSharedPtr<class STileMapEditorViewport> ViewportPtr;`
- L52 _protected member_ `TSharedPtr<class SBorder> ToolboxPtr;`
- L55 _protected prototype_ `void BindCommands();`
- L56 _protected prototype_ `void ExtendMenu();`
- L57 _protected prototype_ `void ExtendToolbar();`
- L58 _protected prototype_ `virtual void CreateEditorModeManager() override;`
- L60 _protected prototype_ `TSharedRef<SDockTab> SpawnTab_Viewport(const FSpawnTabArgs& Args);`
- L61 _protected prototype_ `TSharedRef<SDockTab> SpawnTab_ToolboxHost(const FSpawnTabArgs& Args);`
- L62 _protected prototype_ `TSharedRef<SDockTab> SpawnTab_Details(const FSpawnTabArgs& Args);`

### `Plugins/2D/Paper2D/Source/Paper2DEditor/Private/TileMapEditing/TileMapEditorCommands.h` (Private)


#### class `FTileMapEditorCommands`  
`class FTileMapEditorCommands : public TCommands<FTileMapEditorCommands>`  
_L9-63_
- inherits: `TCommands<FTileMapEditorCommands>`
- L12 _public function_ `FTileMapEditorCommands() : TCommands<FTileMapEditorCommands>( TEXT("TileMapEditor"),`
- L23 _public prototype_ `virtual void RegisterCommands() override;` — TCommand<> interface
- L28 _public member_ `TSharedPtr<FUICommandInfo> EnterTileMapEditMode;` — Edit mode trigger commands
- L31 _public member_ `TSharedPtr<FUICommandInfo> SelectPaintTool;` — Commands inside tile map editing mode
- L32 _public member_ `TSharedPtr<FUICommandInfo> SelectEraserTool;`
- L33 _public member_ `TSharedPtr<FUICommandInfo> SelectFillTool;`
- L34 _public member_ `TSharedPtr<FUICommandInfo> SelectEyeDropperTool;`
- L35 _public member_ `TSharedPtr<FUICommandInfo> SelectTerrainTool;`
- L38 _public member_ `TSharedPtr<FUICommandInfo> SetShowCollision;` — Show toggles
- L40 _public member_ `TSharedPtr<FUICommandInfo> SetShowPivot;`
- L41 _public member_ `TSharedPtr<FUICommandInfo> SetShowTileGrid;`
- L42 _public member_ `TSharedPtr<FUICommandInfo> SetShowLayerGrid;`
- L44 _public member_ `TSharedPtr<FUICommandInfo> SetShowTileMapStats;`
- L47 _public member_ `TSharedPtr<FUICommandInfo> FlipSelectionHorizontally;` — Selection actions
- L48 _public member_ `TSharedPtr<FUICommandInfo> FlipSelectionVertically;`
- L49 _public member_ `TSharedPtr<FUICommandInfo> RotateSelectionCW;`
- L50 _public member_ `TSharedPtr<FUICommandInfo> RotateSelectionCCW;`
- L53 _public member_ `TSharedPtr<FUICommandInfo> AddNewLayerAbove;` — Layer actions
- L54 _public member_ `TSharedPtr<FUICommandInfo> AddNewLayerBelow;`
- L55 _public member_ `TSharedPtr<FUICommandInfo> DeleteLayer;`
- L56 _public member_ `TSharedPtr<FUICommandInfo> MergeLayerDown;`
- L57 _public member_ `TSharedPtr<FUICommandInfo> MoveLayerUp;`
- L58 _public member_ `TSharedPtr<FUICommandInfo> MoveLayerDown;`
- L59 _public member_ `TSharedPtr<FUICommandInfo> MoveLayerToTop;`
- L60 _public member_ `TSharedPtr<FUICommandInfo> MoveLayerToBottom;`
- L61 _public member_ `TSharedPtr<FUICommandInfo> SelectLayerAbove;`
- L62 _public member_ `TSharedPtr<FUICommandInfo> SelectLayerBelow;`

### `Plugins/2D/Paper2D/Source/Paper2DEditor/Private/TileMapEditing/TileMapEditorSettings.h` (Private)


#### class `UTileMapEditorSettings`  
`class UTileMapEditorSettings : public UObject`  
_L9-51_
- reflection: `UCLASS(config=EditorPerProjectUserSettings)`
- inherits: `UObject`
- desc: Settings for the Paper2D tile map editor
- L14 _public prototype_ `UTileMapEditorSettings();`
- L18 _public member_ `FColor DefaultBackgroundColor;` — `UPROPERTY(config, EditAnywhere, Category=Background, meta=(HideAlphaChannel))` — Default background color for new tile map assets
- L22 _public member_ `bool bShowGridByDefault;` — `UPROPERTY(config, EditAnywhere, Category=Grid)` — Should the grid be shown by default when the editor is opened?
- L26 _public member_ `FColor DefaultTileGridColor;` — `UPROPERTY(config, EditAnywhere, Category=Grid, meta=(HideAlphaChannel))` — Default per tile grid color for new tile map assets
- L30 _public member_ `FColor DefaultMultiTileGridColor;` — `UPROPERTY(config, EditAnywhere, Category=Grid, meta=(HideAlphaChannel))` — Default multi tile grid color for new tile map assets
- L34 _public member_ `int32 DefaultMultiTileGridWidth;` — `UPROPERTY(config, EditAnywhere, Category=Grid)` — Default number of tiles the multi tile grid spans horizontally for new tile map assets. 0 removes vertical lines
- L38 _public member_ `int32 DefaultMultiTileGridHeight;` — `UPROPERTY(config, EditAnywhere, Category=Grid)` — Default number of tiles the multi tile grid spans vertically for new tile map assets. 0 removes horizontal lines
- L42 _public member_ `int32 DefaultMultiTileGridOffsetX;` — `UPROPERTY(config, EditAnywhere, Category=Grid)` — Default number of tiles the multi tile grid is shifted to the right for new tile map assets
- L46 _public member_ `int32 DefaultMultiTileGridOffsetY;` — `UPROPERTY(config, EditAnywhere, Category=Grid)` — Default number of tiles the multi tile grid is shifted downwards for new tile map assets
- L50 _public member_ `FColor DefaultLayerGridColor;` — `UPROPERTY(config, EditAnywhere, Category=Grid, meta=(HideAlphaChannel))` — Default layer grid color for new tile map assets

### `Plugins/2D/Paper2D/Source/Paper2DEditor/Private/TileMapEditing/TileMapEditorViewportClient.h` (Private)


#### class `FTileMapEditorViewportClient`  
`class FTileMapEditorViewportClient : public FPaperEditorViewportClient`  
_L18-103_
- inherits: `FPaperEditorViewportClient`
- L22 _public prototype_ `FTileMapEditorViewportClient(TWeakPtr<FTileMapEditor> InTileMapEditor, TWeakPtr<STileMapEditorViewport> InTileMapEditorViewportPtr);` — Constructor
- L25 _public prototype_ `virtual void Draw(const FSceneView* View, FPrimitiveDrawInterface* PDI) override;` — FViewportClient interface
- L26 _public prototype_ `virtual void DrawCanvas(FViewport& InViewport, FSceneView& View, FCanvas& Canvas) override;`
- L27 _public prototype_ `virtual void Tick(float DeltaSeconds) override;`
- L31 _public prototype_ `virtual FLinearColor GetBackgroundColor() const override;` — FEditorViewportClient interface
- L34 _public function_ `void ToggleShowPivot()`
- L35 _public function_ `bool IsShowPivotChecked() const`
- L37 _public prototype_ `void ToggleShowTileGrid();`
- L38 _public prototype_ `bool IsShowTileGridChecked() const;`
- L40 _public prototype_ `void ToggleShowLayerGrid();`
- L41 _public prototype_ `bool IsShowLayerGridChecked() const;`
- L43 _public prototype_ `void ToggleShowMeshEdges();`
- L44 _public prototype_ `bool IsShowMeshEdgesChecked() const;`
- L46 _public prototype_ `void ToggleShowTileMapStats();`
- L47 _public prototype_ `bool IsShowTileMapStatsChecked() const;`
- L50 _public prototype_ `void FocusOnTileMap();`
- L53 _public prototype_ `void NotifyTileMapBeingEditedHasChanged();` — Invalidate any references to the tile map being edited; it has changed
- L56 _public prototype_ `void ActivateEditMode();` — Note: Has to be delayed due to an unfortunate init ordering
- L59 _private member_ `FPreviewScene OwnedPreviewScene;` — The preview scene
- L62 _private member_ `TWeakPtr<FTileMapEditor> TileMapEditorPtr;` — Tile map editor that owns this viewport
- L65 _private member_ `UPaperTileMapComponent* RenderTileMapComponent;` — Render component for the tile map being edited
- L68 _private member_ `UE::Widget::EWidgetMode WidgetMode;` — Widget mode
- L71 _private member_ `bool bManipulating;` — Are we currently manipulating something?
- L74 _private member_ `bool bManipulationDirtiedSomething;` — Did we dirty something during manipulation?
- L77 _private member_ `bool bShowTileMapStats;` — Are we showing tile map stats?
- L80 _private member_ `TWeakPtr<STileMapEditorViewport> TileMapEditorViewportPtr;` — Pointer back to the tile map editor viewport control that owns us
- L83 _private member_ `FScopedTransaction* ScopedTransaction;` — The current transaction for undo/redo
- L86 _private member_ `bool bShowPivot;` — Should we show the sprite pivot?
- L90 _protected prototype_ `virtual FBox GetDesiredFocusBounds() const override;` — FPaperEditorViewportClient interface
- L94 _private function_ `UPaperTileMap* GetTileMapBeingEdited() const`
- L99 _private prototype_ `void DrawBoundsAsText(FViewport& InViewport, FSceneView& View, FCanvas& Canvas, int32& YPos);`
- L101 _private prototype_ `void BeginTransaction(const FText& SessionName);`
- L102 _private prototype_ `void EndTransaction();`

### `Plugins/2D/Paper2D/Source/Paper2DEditor/Private/TileSetAssetTypeActions.h` (Private)


#### class `FTileSetAssetTypeActions`  
`class FTileSetAssetTypeActions : public FAssetTypeActions_Base`  
_L9-29_
- inherits: `FAssetTypeActions_Base`
- L12 _public prototype_ `FTileSetAssetTypeActions(EAssetTypeCategories::Type InAssetCategory);`
- L15 _public prototype_ `virtual FText GetName() const override;` — IAssetTypeActions interface
- L16 _public prototype_ `virtual FColor GetTypeColor() const override;`
- L17 _public prototype_ `virtual UClass* GetSupportedClass() const override;`
- L18 _public prototype_ `virtual void OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<class IToolkitHost> EditWithinLevelEditor = TSharedPtr<IToolkitHost>()) override;`
- L19 _public prototype_ `virtual uint32 GetCategories() override;`
- L20 _public prototype_ `virtual void GetActions(const TArray<UObject*>& InObjects, struct FToolMenuSection& Section) override;`
- L24 _private member_ `EAssetTypeCategories::Type MyAssetCategory;`
- L27 _private prototype_ `void ExecuteCreateTileMap(TWeakObjectPtr<UPaperTileSet> TileSetPtr);`
- L28 _private prototype_ `void ExecutePadTileSetTexture(TWeakObjectPtr<UPaperTileSet> TileSetPtr);`

### `Plugins/2D/Paper2D/Source/Paper2DEditor/Private/TileSetEditor.h` (Private)


#### class `FTileSetEditor`  
`class FTileSetEditor : public FAssetEditorToolkit, public FGCObject`  
_L16-87_
- inherits: `FAssetEditorToolkit,FGCObject`
- L19 _public prototype_ `FTileSetEditor();`
- L20 _public prototype_ `~FTileSetEditor();`
- L23 _public prototype_ `virtual void RegisterTabSpawners(const TSharedRef<class FTabManager>& TabManager) override;` — IToolkit interface
- L24 _public prototype_ `virtual void UnregisterTabSpawners(const TSharedRef<class FTabManager>& TabManager) override;`
- L28 _public prototype_ `virtual FName GetToolkitFName() const override;` — FAssetEditorToolkit
- L29 _public prototype_ `virtual FText GetBaseToolkitName() const override;`
- L30 _public prototype_ `virtual FText GetToolkitName() const override;`
- L31 _public prototype_ `virtual FText GetToolkitToolTipText() const override;`
- L32 _public prototype_ `virtual FLinearColor GetWorldCentricTabColorScale() const override;`
- L33 _public prototype_ `virtual FString GetWorldCentricTabPrefix() const override;`
- L34 _public prototype_ `virtual FString GetDocumentationLink() const override;`
- L35 _public prototype_ `virtual void OnToolkitHostingStarted(const TSharedRef<class IToolkit>& Toolkit) override;`
- L36 _public prototype_ `virtual void OnToolkitHostingFinished(const TSharedRef<class IToolkit>& Toolkit) override;`
- L40 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;` — FSerializableObject interface
- L41 _public function_ `virtual FString GetReferencerName() const override`
- L48 _public prototype_ `void InitTileSetEditor(const EToolkitMode::Type Mode, const TSharedPtr< class IToolkitHost >& InitToolkitHost, class UPaperTileSet* InitTileSet);`
- L50 _public function_ `UPaperTileSet* GetTileSetBeingEdited() const`
- L52 _public function_ `TSharedPtr<FSingleTileEditorViewportClient> GetSingleTileEditor() const`
- L55 _protected prototype_ `TSharedRef<class SDockTab> SpawnTab_TextureView(const FSpawnTabArgs& Args);`
- L56 _protected prototype_ `TSharedRef<class SDockTab> SpawnTab_Details(const FSpawnTabArgs& Args);`
- L57 _protected prototype_ `TSharedRef<class SDockTab> SpawnTab_SingleTileEditor(const FSpawnTabArgs& Args);`
- L59 _protected prototype_ `void BindCommands();`
- L60 _protected prototype_ `void ExtendMenu();`
- L61 _protected prototype_ `void ExtendToolbar();`
- L62 _protected prototype_ `virtual void CreateEditorModeManager() override;`
- L64 _protected prototype_ `void OnPropertyChanged(UObject* ObjectBeingModified, FPropertyChangedEvent& PropertyChangedEvent);`
- L66 _protected prototype_ `void CreateLayouts();`
- L67 _protected prototype_ `void ToggleActiveLayout();`
- L69 _protected prototype_ `TSharedRef<FTabManager::FLayout> GetDesiredLayout() const;`
- L71 _protected member_ `TObjectPtr<UPaperTileSet> TileSetBeingEdited;`
- L73 _protected member_ `TSharedPtr<STileSetSelectorViewport> TileSetViewport;`
- L74 _protected member_ `TSharedPtr<SSingleTileEditorViewport> TileEditorViewport;`
- L75 _protected member_ `TSharedPtr<FSingleTileEditorViewportClient> TileEditorViewportClient;`
- L77 _protected member_ `FDelegateHandle OnPropertyChangedHandle;`
- L80 _protected member_ `bool bUseAlternateLayout;` — Should we use the default layout or the alternate (single tile editor) layout?
- L83 _protected member_ `TSharedPtr<FTabManager::FLayout> TileSelectorPreferredLayout;` — Layout with the tile selector large and on the left
- L86 _protected member_ `TSharedPtr<FTabManager::FLayout> SingleTileEditorPreferredLayout;` — Layout with the single tile editor large and on the left

### `Plugins/2D/Paper2D/Source/Paper2DEditor/Private/TileSetEditor/SingleTileEditorViewport.h` (Private)


#### class `SSingleTileEditorViewport`  
`class SSingleTileEditorViewport : public SEditorViewport, public ICommonEditorViewportToolbarInfoProvider`  
_L14-43_
- inherits: `SEditorViewport,ICommonEditorViewportToolbarInfoProvider`
- L17 _public function_ `SLATE_BEGIN_ARGS(SSingleTileEditorViewport)`
- L20 _public prototype_ `~SSingleTileEditorViewport();`
- L22 _public prototype_ `void Construct(const FArguments& InArgs, TSharedPtr<FSingleTileEditorViewportClient> InViewportClient);`
- L25 _public prototype_ `virtual TSharedPtr<SWidget> BuildViewportToolbar() override;` — SEditorViewport interface
- L26 _public prototype_ `virtual TSharedRef<FEditorViewportClient> MakeEditorViewportClient() override;`
- L27 _public prototype_ `virtual void BindCommands() override;`
- L28 _public prototype_ `virtual void OnFocusViewportToSelection() override;`
- L32 _public prototype_ `virtual TSharedRef<SEditorViewport> GetViewportWidget() override;` — ICommonEditorViewportToolbarInfoProvider interface
- L33 _public prototype_ `virtual TSharedPtr<FExtender> GetExtenders() const override;`
- L34 _public prototype_ `virtual void OnFloatingButtonClicked() override;`
- L38 _protected prototype_ `FText GetTitleText() const;`
- L41 _private member_ `TSharedPtr<FSingleTileEditorViewportClient> TypedViewportClient;`
- L42 _private member_ `FEdModeTileMap* TileMapEditor;`

### `Plugins/2D/Paper2D/Source/Paper2DEditor/Private/TileSetEditor/SingleTileEditorViewportClient.h` (Private)


#### class `FSingleTileEditorViewportClient`  
`class FSingleTileEditorViewportClient : public FPaperEditorViewportClient, public ISpriteSelectionContext`  
_L23-109_
- inherits: `FPaperEditorViewportClient,ISpriteSelectionContext`
- L26 _public prototype_ `FSingleTileEditorViewportClient(UPaperTileSet* InTileSet);`
- L29 _public prototype_ `virtual void Tick(float DeltaSeconds) override;` — FViewportClient interface
- L33 _public prototype_ `virtual FLinearColor GetBackgroundColor() const override;` — FEditorViewportClient interface
- L34 _public prototype_ `virtual void TrackingStarted(const FInputEventState& InInputState, bool bIsDragging, bool bNudge) override;`
- L35 _public prototype_ `virtual void TrackingStopped() override;`
- L36 _public prototype_ `virtual bool BeginTransform(const FGizmoState& InState) override;`
- L37 _public prototype_ `virtual bool EndTransform(const FGizmoState& InState) override;`
- L38 _public prototype_ `virtual bool OnTransformCanceled(const FGizmoState& InState) override;`
- L39 _public prototype_ `virtual void DrawCanvas(FViewport& Viewport, FSceneView& View, FCanvas& Canvas) override;`
- L43 _public prototype_ `virtual FVector2D SelectedItemConvertWorldSpaceDeltaToLocalSpace(const FVector& WorldSpaceDelta) const override;` — ISpriteSelectionContext interface
- L44 _public prototype_ `virtual FVector2D WorldSpaceToTextureSpace(const FVector& SourcePoint) const override;`
- L45 _public prototype_ `virtual FVector TextureSpaceToWorldSpace(const FVector2D& SourcePoint) const override;`
- L46 _public prototype_ `virtual float SelectedItemGetUnitsPerPixel() const override;`
- L47 _public prototype_ `virtual void BeginTransaction(const FText& SessionName) override;`
- L48 _public prototype_ `virtual void MarkTransactionAsDirty() override;`
- L49 _public prototype_ `virtual void EndTransaction() override;`
- L50 _public prototype_ `virtual void InvalidateViewportAndHitProxies() override;`
- L53 _public prototype_ `void SetTileIndex(int32 InTileIndex);`
- L54 _public prototype_ `int32 GetTileIndex() const;`
- L55 _public prototype_ `void OnTileSelectionRegionChanged(const FIntPoint& TopLeft, const FIntPoint& Dimensions);`
- L57 _public prototype_ `void ActivateEditMode(TSharedPtr<FUICommandList> InCommandList);`
- L59 _public prototype_ `void ApplyCollisionGeometryEdits();`
- L61 _public prototype_ `void ToggleShowStats();`
- L62 _public prototype_ `bool IsShowStatsChecked() const;`
- L65 _public function_ `FOnSingleTileIndexChanged& GetOnSingleTileIndexChanged()` — Delegate for when the index of the single tile being edited changes
- L72 _protected prototype_ `virtual FBox GetDesiredFocusBounds() const override;` — FPaperEditorViewportClient interface
- L77 _private member_ `UPaperTileSet* TileSet;` — Tile set
- L80 _private member_ `int32 TileBeingEditedIndex;` — The current tile being edited or INDEX_NONE
- L83 _private member_ `bool bManipulating;` — Are we currently manipulating something?
- L86 _private member_ `bool bManipulationDirtiedSomething;` — Did we dirty something during manipulation?
- L89 _private member_ `bool bShowStats;` — Should we show stats for the tile?
- L92 _private member_ `TWeakPtr<SEditorViewport> SpriteEditorViewportPtr;` — Pointer back to the sprite editor viewport control that owns us
- L95 _private member_ `FScopedTransaction* ScopedTransaction;` — The current transaction for undo/redo
- L98 _private member_ `FPreviewScene OwnedPreviewScene;` — The preview scene
- L101 _private member_ `UPaperSpriteComponent* PreviewTileSpriteComponent;` — The preview sprite in the scene
- L104 _private member_ `FOnSingleTileIndexChanged OnSingleTileIndexChanged;` — Called when TileBeingEditedIndex changes
- L106 _private prototype_ `bool HandleBeginTransform();`
- L107 _private prototype_ `bool HandleEndTransform();`
- L108 _private prototype_ `bool HandleCancelTransform();`

#### Free symbols / members of external scopes

- L18 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnSingleTileIndexChanged, int32 , int32 );`
- L18 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnSingleTileIndexChanged, int32 , int32 );`

### `Plugins/2D/Paper2D/Source/Paper2DEditor/Private/TileSetEditor/TileSetDetailsCustomization.h` (Private)


#### class `FTileSetDetailsCustomization`  
`class FTileSetDetailsCustomization : public IDetailCustomization`  
_L15-49_
- inherits: `IDetailCustomization`
- L19 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L22 _public prototype_ `static TSharedRef<FTileSetDetailsCustomization> MakeEmbeddedInstance();` — Makes a new instance of this detail layout class for use inside of the tile set editor (with a route to the tile being edited)
- L25 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailLayout) override;` — IDetailCustomization interface
- L29 _public prototype_ `void OnTileIndexChanged(int32 NewIndex, int32 OldIndex);` — Called when the tile being edited index changes
- L33 _private member_ `bool bIsEmbeddedInTileSetEditor;` — Are we embedded in the tile set editor?
- L36 _private member_ `int32 SelectedSingleTileIndex;` — Current index being viewed
- L39 _private member_ `TWeakObjectPtr<class UPaperTileSet> TileSetPtr;` — The tile set being edited
- L42 _private member_ `IDetailLayoutBuilder* MyDetailLayout;` — The detail layout builder that is using us
- L45 _private prototype_ `FTileSetDetailsCustomization(bool bInIsEmbedded);`
- L47 _private prototype_ `FText GetCellDimensionHeaderText() const;`
- L48 _private prototype_ `FSlateColor GetCellDimensionHeaderColor() const;`

### `Plugins/2D/Paper2D/Source/Paper2DEditor/Private/TileSetEditor/TileSetEditorCommands.h` (Private)


#### class `FTileSetEditorCommands`  
`class FTileSetEditorCommands : public TCommands<FTileSetEditorCommands>`  
_L9-38_
- inherits: `TCommands<FTileSetEditorCommands>`
- L12 _public function_ `FTileSetEditorCommands() : TCommands<FTileSetEditorCommands>( TEXT("TileSetEditor"),`
- L23 _public prototype_ `virtual void RegisterCommands() override;` — TCommand<> interface
- L28 _public member_ `TSharedPtr<FUICommandInfo> SetShowGrid;` — Show toggles
- L29 _public member_ `TSharedPtr<FUICommandInfo> SetShowTileStats;`
- L30 _public member_ `TSharedPtr<FUICommandInfo> SetShowTilesWithCollision;`
- L31 _public member_ `TSharedPtr<FUICommandInfo> SetShowTilesWithMetaData;`
- L34 _public member_ `TSharedPtr<FUICommandInfo> ApplyCollisionEdits;` — Collision commands
- L37 _public member_ `TSharedPtr<FUICommandInfo> SwapTileSetEditorViewports;` — Editor mode switches

### `Plugins/2D/Paper2D/Source/Paper2DEditor/Private/TileSetEditor/TileSetEditorSettings.h` (Private)


#### class `UTileSetEditorSettings`  
`class UTileSetEditorSettings : public UObject`  
_L9-35_
- reflection: `UCLASS(config=EditorPerProjectUserSettings)`
- inherits: `UObject`
- desc: Settings for the Paper2D tile set editor
- L14 _public prototype_ `UTileSetEditorSettings();`
- L18 _public member_ `FColor DefaultBackgroundColor;` — `UPROPERTY(config, EditAnywhere, Category=Background, meta=(HideAlphaChannel))` — Default background color for new tile set assets
- L22 _public member_ `bool bShowGridByDefault;` — `UPROPERTY(config, EditAnywhere, Category="Tile Editor")` — Should the grid be shown by default when the editor is opened?
- L26 _public member_ `int32 ExtrusionAmount;` — `UPROPERTY(config, EditAnywhere, Category="Tile Sheet Conditioning", meta=(UIMin=1, ClampMin=1))` — The amount to extrude out from the edge of each tile (in pixels)
- L30 _public member_ `bool bPadToPowerOf2;` — `UPROPERTY(config, EditAnywhere, Category="Tile Sheet Conditioning")` — Should we pad the conditioned texture to the next power of 2?
- L34 _public member_ `bool bFillWithTransparentBlack;` — `UPROPERTY(config, EditAnywhere, Category="Tile Sheet Conditioning")` — Should we use transparent black or white when filling the texture areas that aren't covered by tiles?

### `Plugins/2D/Paper2D/Source/Paper2DEditor/Private/TileSetEditor/TileSetEditorViewportClient.h` (Private)


#### class `FTileSetEditorViewportClient`  
`class FTileSetEditorViewportClient : public FPaperEditorViewportClient`  
_L13-40_
- inherits: `FPaperEditorViewportClient`
- L16 _public prototype_ `FTileSetEditorViewportClient(UPaperTileSet* InTileSet);`
- L19 _public prototype_ `virtual void Draw(FViewport* Viewport, FCanvas* Canvas) override;` — FViewportClient interface
- L23 _public prototype_ `virtual FLinearColor GetBackgroundColor() const override;` — FEditorViewportClient interface
- L26 _public prototype_ `void ToggleShowTilesWithCollision();`
- L27 _public prototype_ `bool IsShowTilesWithCollisionChecked() const;`
- L29 _public prototype_ `void ToggleShowTilesWithMetaData();`
- L30 _public prototype_ `bool IsShowTilesWithMetaDataChecked() const;`
- L33 _public member_ `TWeakObjectPtr<UPaperTileSet> TileSetBeingEdited;` — Tile set
- L35 _public member_ `bool bShowTilesWithCollision;`
- L36 _public member_ `bool bShowTilesWithMetaData;`
- L37 _public member_ `bool bHasValidPaintRectangle;`
- L38 _public member_ `FViewportSelectionRectangle ValidPaintRectangle;`
- L39 _public member_ `int32 CurrentSelectedTileIndex;`

### `Plugins/2D/Paper2D/Source/Paper2DEditor/Private/TileSetEditor/TileSetSelectorViewport.h` (Private)


#### class `STileSetSelectorViewport`  
`class STileSetSelectorViewport : public SPaperEditorViewport`  
_L14-61_
- inherits: `SPaperEditorViewport`
- L17 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnTileViewportSelectionChanged, const FIntPoint& , const FIntPoint& );`
- L19 _public function_ `SLATE_BEGIN_ARGS(STileSetSelectorViewport)`
- L22 _public prototype_ `~STileSetSelectorViewport();`
- L24 _public prototype_ `void Construct(const FArguments& InArgs, UPaperTileSet* InTileSet, class FEdModeTileMap* InTileMapEditor);`
- L26 _public prototype_ `void ChangeTileSet(UPaperTileSet* InTileSet);`
- L28 _public function_ `FOnTileViewportSelectionChanged& GetTileSelectionChanged()`
- L33 _public prototype_ `void RefreshSelectionRectangle();`
- L37 _protected prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;` — SWidget interface
- L41 _protected prototype_ `virtual FText GetTitleText() const override;` — SPaperEditorViewport interface
- L45 _protected prototype_ `virtual void BindCommands() override;` — SEditorViewport interface
- L46 _protected prototype_ `virtual void OnFocusViewportToSelection() override;`
- L50 _private prototype_ `void OnSelectionChanged(FMarqueeOperation Marquee, bool bIsPreview);`
- L53 _private member_ `TWeakObjectPtr<class UPaperTileSet> TileSetPtr;`
- L54 _private member_ `TSharedPtr<class FTileSetEditorViewportClient> TypedViewportClient;`
- L55 _private member_ `class FEdModeTileMap* TileMapEditor;`
- L56 _private member_ `FIntPoint SelectionTopLeft;`
- L57 _private member_ `FIntPoint SelectionDimensions;`
- L58 _private member_ `bool bPendingZoom;`
- L60 _private member_ `FOnTileViewportSelectionChanged OnTileSelectionChanged;`

#### Free symbols / members of external scopes

- L17 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnTileViewportSelectionChanged, const FIntPoint& , const FIntPoint& );`

### `Plugins/2D/Paper2D/Source/Paper2DEditor/Private/TileSetEditor/TileSheetPaddingFactory.h` (Private)


#### class `UTileSheetPaddingFactory`  
`class UTileSheetPaddingFactory : public UFactory`  
_L16-39_
- reflection: `UCLASS()`
- inherits: `UFactory`
- L22 _private member_ `TObjectPtr<UPaperTileSet> SourceTileSet;` — `UPROPERTY()` — Source tile sheet texture
- L26 _private member_ `int32 ExtrusionAmount;` — `UPROPERTY(Category = Settings, EditAnywhere, meta=(UIMin=1, ClampMin=1))` — The amount to extrude out from each tile (in pixels)
- L30 _private member_ `bool bPadToPowerOf2;` — `UPROPERTY(Category=Settings, EditAnywhere)` — Should we pad the texture to the next power of 2?
- L34 _private member_ `bool bFillWithTransparentBlack;` — `UPROPERTY(Category=Settings, EditAnywhere)` — Should we use transparent black or white when filling the texture areas that aren't covered by tiles?
- L37 _private prototype_ `virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;` — UFactory interface

### `Plugins/2D/Paper2D/Source/Paper2DEditor/Public/Paper2DEditorModule.h` (Public)


#### class `IPaper2DEditorModule`  
`class IPaper2DEditorModule : public IModuleInterface`  
_L13-23_
- inherits: `IModuleInterface`
- L16 _public function_ `virtual TSharedPtr<class FExtensibilityManager> GetSpriteEditorMenuExtensibilityManager()`
- L17 _public function_ `virtual TSharedPtr<class FExtensibilityManager> GetSpriteEditorToolBarExtensibilityManager()`
- L19 _public function_ `virtual TSharedPtr<class FExtensibilityManager> GetFlipbookEditorMenuExtensibilityManager()`
- L20 _public function_ `virtual TSharedPtr<class FExtensibilityManager> GetFlipbookEditorToolBarExtensibilityManager()`
- L22 _public prototype_ `virtual uint32 GetPaper2DAssetCategory() const = 0;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define PAPER2D_EDITOR_MODULE_NAME "Paper2DEditor"`

### `Plugins/2D/Paper2D/Source/Paper2DEditor/Public/PaperFlipbookHelpers.h` (Public)


#### class `FPaperFlipbookHelpers`  
`class FPaperFlipbookHelpers`  
_L14-33_
- L25 _public prototype_ `static void ExtractFlipbooksFromSprites(TMap<FString, TArray<UPaperSprite*> >& OutSpriteFlipbookMap, const TArray<UPaperSprite*>& Sprites, const TArray<FString>& SpriteNames);` — Try and best guess split up the sprites into multiple flipbooks based on names Numbers are naturally sorted Eg. Walk01, Walk02, Run01, Run02 -> Walk (Walk01, Walk02), Run (Run01, Run02) if autoGroup is true All ungrouped sprites are stored in one flipbook Expected input: Sprites array contains valid sprites SpriteNames contains an array of sprite names (parallel to Sprites) or, an empty array if Sprite->GetName() is to be used.
- L29 _private prototype_ `static FString GetCleanerSpriteName(const FString& Name);`
- L30 _private prototype_ `static bool ExtractSpriteNumber(const FString& String, FString& BareString, int32& Number);`
- L32 _private function_ `FPaperFlipbookHelpers()`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API PAPER2DEDITOR_API`

### `Plugins/2D/Paper2D/Source/Paper2DEditor/Public/PaperJSONHelpers.h` (Public)


#### class `FPaperJSONHelpers`  
`class FPaperJSONHelpers`  
_L15-53_
- L19 _public prototype_ `static FString ReadString(TSharedPtr<class FJsonObject> Item, const FString& Key, const FString& DefaultValue);` — returns the value of Key in Item, or DefaultValue if the Key is missing or the wrong type
- L22 _public prototype_ `static TSharedPtr<class FJsonObject> ReadObject(TSharedPtr<class FJsonObject> Item, const FString& Key);` — Returns the object named Key or nullptr if it is missing or the wrong type
- L25 _public prototype_ `static const TArray< TSharedPtr<FJsonValue> >& ReadArray(TSharedPtr<class FJsonObject> Item, const FString& Key);` — Returns the array named Key or nullptr if it is missing or the wrong type
- L28 _public prototype_ `static bool ReadBoolean(const TSharedPtr<class FJsonObject> Item, const FString& Key, bool bDefaultIfMissing);` — Returns the bool named Key or bDefaultIfMissing if it is missing or the wrong type (note: no way to determine errors!)
- L31 _public prototype_ `static bool ReadFloatNoDefault(const TSharedPtr<class FJsonObject> Item, const FString& Key, float& Out_Value);` — Returns true if the field named Key is a Number, populating Out_Value, or false if it is missing or the wrong type (Out_Value is set to 0.0f on failure)
- L34 _public prototype_ `static bool ReadFloatNoDefault(const TSharedPtr<class FJsonObject> Item, const FString& Key, double& Out_Value);` — Returns true if the field named Key is a Number, populating Out_Value, or false if it is missing or the wrong type (Out_Value is set to 0.0f on failure)
- L37 _public prototype_ `static bool ReadIntegerNoDefault(const TSharedPtr<class FJsonObject> Item, const FString& Key, int32& Out_Value);` — Returns true if the field named Key is a Number (truncating it to an integer), populating Out_Value, or false if it is missing or the wrong type (Out_Value is set to 0 on failure)
- L40 _public prototype_ `static bool ReadRectangle(const TSharedPtr<class FJsonObject> Item, const FString& Key, FIntPoint& Out_XY, FIntPoint& Out_WH);` — Returns true if the object named Key is a struct containing four integers (x,y,w,h), populating XY and WH with the values)
- L43 _public prototype_ `static bool ReadSize(const TSharedPtr<class FJsonObject> Item, const FString& Key, FVector2D& Out_WH);` — Returns true if the object named Key is a struct containing two floats (w,h), populating WH with the values)
- L46 _public prototype_ `static bool ReadXY(const TSharedPtr<class FJsonObject> Item, const FString& Key, FVector2D& Out_WH);` — Returns true if the object named Key is a struct containing two floats (x,y), populating WH with the values)
- L49 _public prototype_ `static bool ReadIntPoint(const TSharedPtr<class FJsonObject> Item, const FString& Key, FIntPoint& Out_XY);` — Returns true if the object named Key is a struct containing two floats (x,y), populating XY with the values)
- L52 _private function_ `FPaperJSONHelpers()`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API PAPER2DEDITOR_API`
