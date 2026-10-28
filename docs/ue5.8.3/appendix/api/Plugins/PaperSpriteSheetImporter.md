# Plugins / PaperSpriteSheetImporter

- module root: `Plugins/2D/Paper2D/Source/PaperSpriteSheetImporter`
- headers: 6; symbols: 65
- symbol kinds: class=5, delegate=1, member=28, prototype=30, struct=1
- DynamicallyLoadedModuleNames: AssetRegistry
- PrivateDependencyModuleNames: AssetTools, ContentBrowser, Core, CoreUObject, Engine, Json, Paper2D, Paper2DEditor, Slate, SlateCore, ToolMenus, UnrealEd
- PrivateIncludePathModuleNames: AssetRegistry

### `Plugins/2D/Paper2D/Source/PaperSpriteSheetImporter/Private/PaperJsonSpriteSheetImporter.h` (Private)


#### struct `FSpriteFrame`  
`struct FSpriteFrame`  
_L16-32_
- desc: Represents one parsed frame in a sprite sheet
- L18 _public member_ `FName FrameName;`
- L20 _public member_ `FIntPoint SpritePosInSheet;`
- L21 _public member_ `FIntPoint SpriteSizeInSheet;`
- L23 _public member_ `FIntPoint SpriteSourcePos;`
- L24 _public member_ `FIntPoint SpriteSourceSize;`
- L26 _public member_ `FVector2D ImageSourceSize;`
- L28 _public member_ `FVector2D Pivot;`
- L30 _public member_ `bool bTrimmed;`
- L31 _public member_ `bool bRotated;`

#### class `FPaperJsonSpriteSheetImporter`  
`class FPaperJsonSpriteSheetImporter`  
_L38-87_
- desc: Parses a json from FileContents and imports / reimports a spritesheet
- L41 _public prototype_ `FPaperJsonSpriteSheetImporter();`
- L43 _public prototype_ `static bool CanImportJSON(const FString& FileContents);`
- L45 _public prototype_ `bool ImportFromString(const FString& FileContents, const FString& NameForErrors, bool bSilent);`
- L46 _public prototype_ `bool ImportFromArchive(FArchive* Archive, const FString& NameForErrors, bool bSilent);`
- L48 _public prototype_ `bool ImportTextures(const FString& LongPackagePath, const FString& SourcePath);`
- L50 _public prototype_ `bool PerformImport(const FString& LongPackagePath, EObjectFlags Flags, UPaperSpriteSheet* SpriteSheet);`
- L52 _public prototype_ `void SetReimportData(const TArray<FString>& ExistingSpriteNames, const TArray< TSoftObjectPtr<class UPaperSprite> >& ExistingSpriteSoftPtrs);`
- L54 _public prototype_ `static UTexture2D* ImportOrReimportTexture(UTexture2D* ExistingTexture, const FString& TextureSourcePath, const FString& DestinationAssetFolder);`
- L55 _public prototype_ `static UTexture2D* ImportTexture(const FString& TextureSourcePath, const FString& DestinationAssetFolder);`
- L58 _protected prototype_ `bool Import(TSharedPtr<FJsonObject> SpriteDescriptorObject, const FString& NameForErrors, bool bSilent);`
- L59 _protected prototype_ `UPaperSprite* FindExistingSprite(const FString& Name);`
- L62 _protected member_ `TArray<FSpriteFrame> Frames;`
- L64 _protected member_ `FString ImageName;`
- L65 _protected member_ `UTexture2D* ImageTexture;`
- L67 _protected member_ `FString ComputedNormalMapName;`
- L68 _protected member_ `UTexture2D* NormalMapTexture;`
- L71 _public member_ `bool bIsReimporting;`
- L74 _public member_ `FString ExistingBaseTextureName;` — The name of the default or diffuse texture during a previous import
- L77 _public member_ `UTexture2D* ExistingBaseTexture;` — The asset that was created for ExistingBaseTextureName during a previous import
- L80 _public member_ `FString ExistingNormalMapTextureName;` — The name of the normal map texture during a previous import (if any)
- L83 _public member_ `UTexture2D* ExistingNormalMapTexture;` — The asset that was created for ExistingNormalMapTextureName  during a previous import (if any)
- L86 _public member_ `TMap<FString, UPaperSprite*> ExistingSprites;` — Map of a sprite name (as seen in the importer) -> UPaperSprite

### `Plugins/2D/Paper2D/Source/PaperSpriteSheetImporter/Private/PaperSpriteSheet.h` (Private)


#### class `UPaperSpriteSheet`  
`class UPaperSpriteSheet : public UObject`  
_L10-49_
- reflection: `UCLASS(BlueprintType, meta = (DisplayThumbnail = "true"))`
- inherits: `UObject`
- L17 _public member_ `TArray<FString> SpriteNames;` — `UPROPERTY(VisibleAnywhere, Category=Data)` — The names of sprites during import
- L20 _public member_ `TArray< TSoftObjectPtr<class UPaperSprite> > Sprites;` — `UPROPERTY(VisibleAnywhere, Category=Data)`
- L24 _public member_ `FString TextureName;` — `UPROPERTY(VisibleAnywhere, Category=Data)` — The name of the default or diffuse texture during import
- L28 _public member_ `TObjectPtr<UTexture2D> Texture;` — `UPROPERTY(VisibleAnywhere, Category=Data)` — The asset that was created for TextureName
- L32 _public member_ `FString NormalMapTextureName;` — `UPROPERTY(VisibleAnywhere, Category=Data)` — The name of the normal map texture during import (if any)
- L36 _public member_ `TObjectPtr<UTexture2D> NormalMapTexture;` — `UPROPERTY(VisibleAnywhere, Category=Data)` — The asset that was created for NormalMapTextureName (if any)
- L41 _public member_ `TObjectPtr<class UAssetImportData> AssetImportData;` — `UPROPERTY(VisibleAnywhere, Instanced, Category=ImportSettings)` — Import data for this
- L44 _public prototype_ `virtual void PostInitProperties() override;` — UObject interface
- L45 _public prototype_ `virtual void GetAssetRegistryTags(FAssetRegistryTagsContext Context) const override;`
- L46 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`

### `Plugins/2D/Paper2D/Source/PaperSpriteSheetImporter/Private/PaperSpriteSheetAssetTypeActions.h` (Private)


#### class `FPaperSpriteSheetAssetTypeActions`  
`class FPaperSpriteSheetAssetTypeActions : public FAssetTypeActions_Base`  
_L9-24_
- inherits: `FAssetTypeActions_Base`
- L13 _public prototype_ `virtual FText GetName() const override;` — IAssetTypeActions interface
- L14 _public prototype_ `virtual FColor GetTypeColor() const override;`
- L15 _public prototype_ `virtual UClass* GetSupportedClass() const override;`
- L16 _public prototype_ `virtual void GetActions(const TArray<UObject*>& InObjects, struct FToolMenuSection& Section) override;`
- L17 _public prototype_ `virtual uint32 GetCategories() override;`
- L18 _public prototype_ `virtual bool IsImportedAsset() const override;`
- L19 _public prototype_ `virtual void GetResolvedSourceFilePaths(const TArray<UObject*>& TypeAssets, TArray<FString>& OutSourceFilePaths) const override;`
- L23 _private prototype_ `void ExecuteCreateFlipbooks(TArray<TWeakObjectPtr<UPaperSpriteSheet>> Objects);`

### `Plugins/2D/Paper2D/Source/PaperSpriteSheetImporter/Private/PaperSpriteSheetImportFactory.h` (Private)


#### class `UPaperSpriteSheetImportFactory`  
`class UPaperSpriteSheetImportFactory : public UFactory`  
_L11-24_
- reflection: `UCLASS()`
- inherits: `UFactory`
- desc: Imports a sprite sheet (and associated paper sprites and textures) from a JSON file exported from Adobe Flash CS6, Texture Packer, or other compatible tool
- L16 _private prototype_ `virtual FText GetToolTip() const override;` — UFactory interface
- L17 _private prototype_ `virtual bool FactoryCanImport(const FString& Filename) override;`
- L18 _private prototype_ `virtual UObject* FactoryCreateText(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, const TCHAR* Type, const TCHAR*& Buffer, const TCHAR* BufferEnd, FFeedbackContext* Warn) override;`
- L23 _protected member_ `FPaperJsonSpriteSheetImporter Importer;` — The actual import worker, which may be already configured by the more derived reimport factory by the time FactoryCreateText is called

### `Plugins/2D/Paper2D/Source/PaperSpriteSheetImporter/Private/PaperSpriteSheetImporterLog.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogPaperSpriteSheetImporter, Verbose, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogPaperSpriteSheetImporter, Verbose, All);`

### `Plugins/2D/Paper2D/Source/PaperSpriteSheetImporter/Private/PaperSpriteSheetReimportFactory.h` (Private)


#### class `UPaperSpriteSheetReimportFactory`  
`class UPaperSpriteSheetReimportFactory : public UPaperSpriteSheetImportFactory, public FReimportHandler`  
_L11-21_
- reflection: `UCLASS()`
- inherits: `UPaperSpriteSheetImportFactory,FReimportHandler`
- desc: Reimports a UPaperSpriteSheet asset
- L16 _private prototype_ `virtual bool CanReimport(UObject* Obj, TArray<FString>& OutFilenames) override;`
- L17 _private prototype_ `virtual void SetReimportPaths(UObject* Obj, const TArray<FString>& NewReimportPaths) override;`
- L18 _private prototype_ `virtual EReimportResult::Type Reimport(UObject* Obj) override;`
- L19 _private prototype_ `virtual int32 GetPriority() const override;`
