# Plugins / MetaHumanCharacterMigrationEditor

- module root: `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacterMigrationEditor`
- headers: 3; symbols: 159
- symbol kinds: class=3, enum=1, enumerator=6, member=115, namespace=2, prototype=14, struct=18
- PrivateDependencyModuleNames: AssetTools, Core, CoreUObject, Engine, HairStrandsCore, Json, JsonUtilities, MetaHumanCharacter, MetaHumanCharacterEditor, MetaHumanCharacterPalette, MetaHumanCharacterPaletteEditor, MetaHumanDefaultPipeline, MetaHumanSDKEditor, MetaHumanSDKRuntime, RigLogicModule, Slate, SlateCore, ToolWidgets, UnrealEd
- PublicDependencyModuleNames: 

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacterMigrationEditor/Private/MetaHumanCharacterMigrationEditorModule.h` (Private)


#### class `FMetaHumanCharacterMigrationEditorModule`  
`class FMetaHumanCharacterMigrationEditorModule final : public IModuleInterface`  
_L17-76_
- inherits: `IModuleInterface`
- L22 _public prototype_ `virtual void StartupModule() override;`
- L23 _public prototype_ `virtual void ShutdownModule() override;`
- L28 _private prototype_ `bool ShouldMigrate() const;`
- L29 _private prototype_ `bool ShouldImport() const;`
- L32 _private prototype_ `bool OnMetaHumanImportStarted(const UE::MetaHuman::FSourceMetaHuman& InSourceMetaHuman);` — Called when an import operation is started from Bridge. If UMetaHumanCharacterEditorSettings::MigrateAction is set to Prompt, asks the users which action to perform
- L35 _private prototype_ `bool OnShouldImportMetaHumanAssetOrFile(const UE::MetaHuman::FSourceMetaHuman& InSourceMetaHuman, const class FString& InDestPath, bool bInIsFile);` — Called for each asset of file to be imported. If only migrating the legacy MetaHuman do not import anything
- L38 _private prototype_ `void MigrateMetaHuman(const UE::MetaHuman::FSourceMetaHuman& InSourceMetaHuman);` — Create a MetaHuman Character from a bridge import
- L41 _private prototype_ `void SetSkin(TNotNull<class UMetaHumanCharacter*> InCharacter, const struct FMetaHumanMigrationInfo& InMigrationInfo);` — Sets the character skin parameters from the migration info struct and commits the changes using the MetaHumanCharacter subsystem
- L44 _private prototype_ `void SetMakeup(TNotNull<class UMetaHumanCharacter*> InCharacter, const struct FMetaHumanMigrationInfo& InMigrationInfo);` — Sets the character makeup parameters from the migration info and commits the changes using UMetaHumanCharacterEditorSubsystem
- L47 _private prototype_ `void SetEyes(TNotNull<class UMetaHumanCharacter*> InCharacter, const struct FMetaHumanMigrationInfo& InMigrationInfo);` — Sets the character eye parameters from the migration info and commits the changes using UMetaHumanCharacterEditorSubsystem
- L50 _private prototype_ `void SetGrooms( TNotNull<class UMetaHumanCharacter*> InCharacter, const struct FMetaHumanMigrationInfo& InMigrationInfo, TMap<EMetaHumanMigrationDataAssetType, struct FMetaHumanPipelineSlotSelection>& OutSlotSelections);` — Sets the character grooms in its palette from the migration info. Appends the instance parameter names of valid grooms in OutInstanceParameters
- L56 _private prototype_ `void UpdateWardrobe( TNotNull<class UMetaHumanCharacter*> InCharacter, const struct FMetaHumanMigrationInfo& InMigrationInfo, const TMap<EMetaHumanMigrationDataAssetType, struct FMetaHumanPipelineSlotSelection>& InSlotSelections);` — Assigns wardrobe items to the character and updates the material property values from the migration info data
- L62 _private prototype_ `void LogWarning(const FText& InMessage);` — Logs warnings or errors in the MessageLog. It also sets the bHasWarnings or bHasErrors flags for further tracking
- L63 _private prototype_ `void LogError(const FText& InMessage);`
- L68 _private member_ `class FMessageLog* MessageLogPtr = nullptr;` — Pointer to the current active message log
- L71 _private member_ `bool bHasErrors = false;` — Keep track of whether errors or warnings were raised during the migration process
- L72 _private member_ `bool bHasWarnings = false;`
- L75 _private member_ `EMetaHumanCharacterMigrationAction MigrateActionInternal;` — Which migration action to take. Used internally to persist the value between function calls

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace MetaHuman` (scope `UE`)

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacterMigrationEditor/Private/MetaHumanMigrationDatabase.h` (Private)


#### enum `EMetaHumanMigrationDataAssetType`  
`enum class EMetaHumanMigrationDataAssetType : uint8`  
_L12-20_
- reflection: `UENUM()`
- L14 _public enumerator_ `Hair`
- L15 _public enumerator_ `Eyebrows`
- L16 _public enumerator_ `Eyelashes`
- L17 _public enumerator_ `Beard`
- L18 _public enumerator_ `Mustache`
- L19 _public enumerator_ `Peachfuzz`

#### class `UMetaHumanMigrationAssetCollection`  
`class UMetaHumanMigrationAssetCollection : public UDataAsset`  
_L26-34_
- reflection: `UCLASS(Blueprintable, BlueprintType)`
- inherits: `UDataAsset`
- desc: Contains assets that are available for migration.
- L33 _public member_ `TMap<FName, TSoftObjectPtr<class UMetaHumanWardrobeItem>> GroomAssetMapping;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Mapping")` — Maps original MHC identifier against the wardrobe item.

#### class `UMetaHumanMigrationDatabase`  
`class UMetaHumanMigrationDatabase : public UDataAsset`  
_L40-48_
- reflection: `UCLASS(Blueprintable, BlueprintType)`
- inherits: `UDataAsset`
- desc: Contains all assets collections that will be used for migration.
- L47 _public member_ `TMap<EMetaHumanMigrationDataAssetType, TObjectPtr<UMetaHumanMigrationAssetCollection>> Assets;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Assets")` — Maps migration asset type against the collection object

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacterMigrationEditor/Private/MetaHumanMigrationInfo.h` (Private)


#### struct `FMetaHumanTextureSynthesisMigrationInfo`  
`struct FMetaHumanTextureSynthesisMigrationInfo`  
_L12-33_
- reflection: `USTRUCT()`
- L17 _public member_ `bool bSkinUnlocked = true;` — `UPROPERTY()`
- L20 _public member_ `float LowFrequency = 0.5f;` — `UPROPERTY()`
- L23 _public member_ `float HighFrequency = 0.5f;` — `UPROPERTY()`
- L26 _public member_ `float Contrast = 0.5f;` — `UPROPERTY()`

#### struct `FMetaHumanFreckesMigrationInfo`  
`struct FMetaHumanFreckesMigrationInfo`  
_L36-54_
- reflection: `USTRUCT()`
- L41 _public member_ `FName Option;` — `UPROPERTY()`
- L44 _public member_ `float Density = 0.5f;` — `UPROPERTY()`
- L47 _public member_ `float Saturation = 0.5f;` — `UPROPERTY()`
- L50 _public member_ `float Strength = 0.5f;` — `UPROPERTY()`
- L53 _public member_ `float ToneShift = 0.5f;` — `UPROPERTY()`

#### struct `FMetaHumanAccentRegionMigrationInfo`  
`struct FMetaHumanAccentRegionMigrationInfo`  
_L57-69_
- reflection: `USTRUCT()`
- L62 _public member_ `float Redness = 0.5f;` — `UPROPERTY()`
- L65 _public member_ `float Saturation = 0.5f;` — `UPROPERTY()`
- L68 _public member_ `float Lightness = 0.5f;` — `UPROPERTY()`

#### struct `FMetaHumanAccentRegionsMigrationInfo`  
`struct FMetaHumanAccentRegionsMigrationInfo`  
_L72-99_
- reflection: `USTRUCT()`
- L77 _public member_ `FMetaHumanAccentRegionMigrationInfo Scalp;` — `UPROPERTY()`
- L80 _public member_ `FMetaHumanAccentRegionMigrationInfo Forehead;` — `UPROPERTY()`
- L83 _public member_ `FMetaHumanAccentRegionMigrationInfo Nose;` — `UPROPERTY()`
- L86 _public member_ `FMetaHumanAccentRegionMigrationInfo UnderEye;` — `UPROPERTY()`
- L89 _public member_ `FMetaHumanAccentRegionMigrationInfo Cheeks;` — `UPROPERTY()`
- L92 _public member_ `FMetaHumanAccentRegionMigrationInfo Lips;` — `UPROPERTY()`
- L95 _public member_ `FMetaHumanAccentRegionMigrationInfo Chin;` — `UPROPERTY()`
- L98 _public member_ `FMetaHumanAccentRegionMigrationInfo Ears;` — `UPROPERTY()`

#### struct `FMetaHumanIrisMigrationInfo`  
`struct FMetaHumanIrisMigrationInfo`  
_L102-139_
- reflection: `USTRUCT()`
- L107 _public member_ `FName Option;` — `UPROPERTY()`
- L111 _public member_ `FVector2D Color1UI = FVector2D(0.8f, 0.3f);` — `UPROPERTY()` — TODO: Need to map these to FLinearColor
- L117 _public member_ `FVector2D Color2UI = FVector2D(0.5f, 0.3f);` — `UPROPERTY()`
- L123 _public member_ `bool bUseRadialBlend = true;` — `UPROPERTY()`
- L126 _public member_ `float ColorBalance = 0.5f;` — `UPROPERTY()`
- L129 _public member_ `float ColorBalanceSmoothness = 0.5f;` — `UPROPERTY()`
- L132 _public member_ `float Size = 0.5f;` — `UPROPERTY()`
- L135 _public member_ `float Saturation = 0.5f;` — `UPROPERTY()`
- L138 _public member_ `float LimbusDarkAmount = 0.5f;` — `UPROPERTY()`

#### struct `FMetaHumanScleraMigrationInfo`  
`struct FMetaHumanScleraMigrationInfo`  
_L142-163_
- reflection: `USTRUCT()`
- L153 _public member_ `float Brightness = 0.5f;` — `UPROPERTY()`
- L156 _public member_ `float Rotation = 0.5f;` — `UPROPERTY()`
- L159 _public member_ `float Vascularity = 0.5f;` — `UPROPERTY()`
- L162 _public member_ `float VeinsRotation = 0.5f;` — `UPROPERTY()`

#### struct `FMetaHumanEyeMigrationInfo`  
`struct FMetaHumanEyeMigrationInfo`  
_L166-175_
- reflection: `USTRUCT()`
- L171 _public member_ `FMetaHumanIrisMigrationInfo Iris;` — `UPROPERTY()`
- L174 _public member_ `FMetaHumanScleraMigrationInfo Sclera;` — `UPROPERTY()`

#### struct `FMetaHumanTeethMigrationInfo`  
`struct FMetaHumanTeethMigrationInfo`  
_L178-202_
- reflection: `USTRUCT()`
- L183 _public member_ `FVector2D TeethColorUI = FVector2D(0.35f);` — `UPROPERTY()`
- L189 _public member_ `FVector2D GumColorUI = FVector2D(0.35f);` — `UPROPERTY()`
- L195 _public member_ `FVector2D PlaqueColorUI = FVector2D(0.35f);` — `UPROPERTY()`
- L201 _public member_ `float PlaqueAmount = 0.12f;` — `UPROPERTY()`

#### struct `FMetaHumanFoundationMakeupMigrationInfo`  
`struct FMetaHumanFoundationMakeupMigrationInfo`  
_L205-223_
- reflection: `USTRUCT()`
- L210 _public member_ `bool bApplyFoundation = false;` — `UPROPERTY()`
- L216 _public member_ `float Intensity = 0.39f;` — `UPROPERTY()`
- L219 _public member_ `float Roughness = 0.25f;` — `UPROPERTY()`
- L222 _public member_ `float Concealer = 0.57f;` — `UPROPERTY()`

#### struct `FMetaHumanEyesMakeupMigrationInfo`  
`struct FMetaHumanEyesMakeupMigrationInfo`  
_L226-247_
- reflection: `USTRUCT()`
- L231 _public member_ `FName Option;` — `UPROPERTY()`
- L240 _public member_ `float Roughness = 0.5f;` — `UPROPERTY()`
- L243 _public member_ `float Transparency = 0.6f;` — `UPROPERTY()`
- L246 _public member_ `float Metalness = 0.0f;` — `UPROPERTY()`

#### struct `FMetaHumanBlusherMakeupMigrationInfo`  
`struct FMetaHumanBlusherMakeupMigrationInfo`  
_L250-265_
- reflection: `USTRUCT()`
- L255 _public member_ `FName Option;` — `UPROPERTY()`
- L261 _public member_ `float Intensity = 0.4f;` — `UPROPERTY()`
- L264 _public member_ `float Roughness = 0.25f;` — `UPROPERTY()`

#### struct `FMetaHumanLipsMakeupMigrationInfo`  
`struct FMetaHumanLipsMakeupMigrationInfo`  
_L268-283_
- reflection: `USTRUCT()`
- L273 _public member_ `FName Option;` — `UPROPERTY()`
- L279 _public member_ `float Roughness = 0.5f;` — `UPROPERTY()`
- L282 _public member_ `float Transparency = 0.85f;` — `UPROPERTY()`

#### struct `FMetaHumanMakeupMigrationInfo`  
`struct FMetaHumanMakeupMigrationInfo`  
_L286-303_
- reflection: `USTRUCT()`
- L293 _public member_ `FMetaHumanFoundationMakeupMigrationInfo Foundation;` — `UPROPERTY()`
- L296 _public member_ `FMetaHumanEyesMakeupMigrationInfo Eyes;` — `UPROPERTY()`
- L299 _public member_ `FMetaHumanBlusherMakeupMigrationInfo Blusher;` — `UPROPERTY()`
- L302 _public member_ `FMetaHumanLipsMakeupMigrationInfo Lips;` — `UPROPERTY()`

#### struct `FMetaHumanFaceMigrationInfo`  
`struct FMetaHumanFaceMigrationInfo`  
_L306-327_
- reflection: `USTRUCT()`
- L311 _public member_ `FMetaHumanFreckesMigrationInfo Freckles;` — `UPROPERTY()`
- L314 _public member_ `FMetaHumanAccentRegionsMigrationInfo Accents;` — `UPROPERTY()`
- L317 _public member_ `FMetaHumanEyeMigrationInfo LeftEye;` — `UPROPERTY()`
- L320 _public member_ `FMetaHumanEyeMigrationInfo RightEye;` — `UPROPERTY()`
- L323 _public member_ `FMetaHumanTeethMigrationInfo Teeth;` — `UPROPERTY()`
- L326 _public member_ `FMetaHumanMakeupMigrationInfo Makeup;` — `UPROPERTY()`

#### struct `FMetaHumanGroomMigrationInfo`  
`struct FMetaHumanGroomMigrationInfo`  
_L330-438_
- reflection: `USTRUCT()`
- L335 _public member_ `FName Option;` — `UPROPERTY()`
- L338 _public member_ `float Length = 1.0f;` — `UPROPERTY()`
- L341 _public member_ `bool bUseCustomProperties = false;` — `UPROPERTY()`
- L344 _public member_ `FVector2D MelaninAndRedness = FVector2D::ZeroVector;` — `UPROPERTY()`
- L347 _public member_ `float Roughness = 0.25f;` — `UPROPERTY()`
- L350 _public member_ `float Whiteness = 0.0f;` — `UPROPERTY()`
- L353 _public member_ `float Lightness = 0.5f;` — `UPROPERTY()`
- L356 _public member_ `FName PresetOption;` — `UPROPERTY()`
- L359 _public member_ `bool bUseDyeColor = false;` — `UPROPERTY()`
- L362 _public member_ `FLinearColor DyeColor = FLinearColor(0.32156899571418762f, 0.0f, 0.69019597768783569f, 0.0f);` — `UPROPERTY()`
- L365 _public member_ `bool bUseRegions = false;` — `UPROPERTY()`
- L368 _public member_ `FVector2D RegionsUV = FVector2D(0.2819f, 0.25f);` — `UPROPERTY()`
- L371 _public member_ `bool bUseRegionsColor = false;` — `UPROPERTY()`
- L374 _public member_ `FLinearColor RegionsColor = FLinearColor::White;` — `UPROPERTY()`
- L377 _public member_ `FName RegionsPresetOption;` — `UPROPERTY()`
- L380 _public member_ `bool bUseOmbre = false;` — `UPROPERTY()`
- L383 _public member_ `FVector2D OmbreUV = FVector2D(0.2819f, 0.25f);` — `UPROPERTY()`
- L386 _public member_ `bool bUseOmbreColor = false;` — `UPROPERTY()`
- L389 _public member_ `FLinearColor OmbreColor = FLinearColor::White;` — `UPROPERTY()`
- L392 _public member_ `float OmbreShift = 0.5f;` — `UPROPERTY()`
- L395 _public member_ `float OmbreContrast = 0.0f;` — `UPROPERTY()`
- L398 _public member_ `float OmbreIntensity = 1.0f;` — `UPROPERTY()`
- L401 _public member_ `FName OmbrePresetOption;` — `UPROPERTY()`
- L404 _public member_ `bool bUseHighlights = false;` — `UPROPERTY()`
- L407 _public member_ `FVector2D HighlightsUV = FVector2D(0.2819f, 0.25f);` — `UPROPERTY()`
- L410 _public member_ `bool bUseHighlightsColor = false;` — `UPROPERTY()`
- L413 _public member_ `FLinearColor HighlightsColor = FLinearColor::White;` — `UPROPERTY()`
- L416 _public member_ `float HighlightsBlending = 0.5f;` — `UPROPERTY()`
- L419 _public member_ `float HighlightsIntensity = 0.5f;` — `UPROPERTY()`
- L422 _public member_ `int32 HighlightsVariation = 0;` — `UPROPERTY()`
- L425 _public member_ `FName HighlightsPresetOption;` — `UPROPERTY()`
- L428 _public member_ `float EyebrowsShading = 1.0f;` — `UPROPERTY()`
- L431 _public member_ `float EyebrowsMicroblading = 1.0f;` — `UPROPERTY()`
- L434 _public member_ `bool bUseMaskModulation = true;` — `UPROPERTY()`
- L437 _public member_ `FName MaskModulationOption;` — `UPROPERTY()`

#### struct `FMetaHumanGroomsMigrationInfo`  
`struct FMetaHumanGroomsMigrationInfo`  
_L441-462_
- reflection: `USTRUCT()`
- L446 _public member_ `FMetaHumanGroomMigrationInfo Hair;` — `UPROPERTY()`
- L449 _public member_ `FMetaHumanGroomMigrationInfo Eyebrows;` — `UPROPERTY()`
- L452 _public member_ `FMetaHumanGroomMigrationInfo Eyelashes;` — `UPROPERTY()`
- L455 _public member_ `FMetaHumanGroomMigrationInfo Beard;` — `UPROPERTY()`
- L458 _public member_ `FMetaHumanGroomMigrationInfo Mustache;` — `UPROPERTY()`
- L461 _public member_ `FMetaHumanGroomMigrationInfo Peachfuzz;` — `UPROPERTY()`

#### struct `FMetaHumanBodyMigrationInfo`  
`struct FMetaHumanBodyMigrationInfo`  
_L465-471_
- reflection: `USTRUCT()`
- L470 _public member_ `EMetaHumanBodyType Type = EMetaHumanBodyType::f_med_nrw;` — `UPROPERTY()`

#### struct `FMetaHumanMigrationInfo`  
`struct FMetaHumanMigrationInfo`  
_L474-489_
- reflection: `USTRUCT()`
- L479 _public member_ `FMetaHumanBodyMigrationInfo Body;` — `UPROPERTY()`
- L482 _public member_ `FMetaHumanFaceMigrationInfo Face;` — `UPROPERTY()`
- L485 _public member_ `FMetaHumanTextureSynthesisMigrationInfo TextureSynthesis;` — `UPROPERTY()`
- L488 _public member_ `FMetaHumanGroomsMigrationInfo Grooms;` — `UPROPERTY()`
