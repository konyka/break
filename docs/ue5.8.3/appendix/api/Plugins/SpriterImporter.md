# Plugins / SpriterImporter

- module root: `Plugins/2D/Paper2D/Source/SpriterImporter`
- headers: 4; symbols: 212
- symbol kinds: class=2, delegate=1, enum=4, enumerator=21, function=1, macro=2, member=92, prototype=64, struct=25
- DynamicallyLoadedModuleNames: AssetRegistry, AssetTools
- PrivateDependencyModuleNames: Core, CoreUObject, EditorFramework, Engine, Json, Paper2D, Paper2DEditor, UnrealEd
- PrivateIncludePathModuleNames: AssetRegistry, AssetTools

### `Plugins/2D/Paper2D/Source/SpriterImporter/Private/PaperSpriterImportData.h` (Private)


#### class `UPaperSpriterImportData`  
`class UPaperSpriterImportData : public UObject`  
_L10-44_
- reflection: `UCLASS(Experimental)`
- inherits: `UObject`
- desc: This is the 'hub' asset that tracks other imported assets for a rigged sprite character exported from Spriter
- L17 _public member_ `FSpriterSCON ImportedData;` — `UPROPERTY(VisibleAnywhere, Category = Spriter)` — @TODO: For debug only
- L40 _public member_ `class UAssetImportData* AssetImportData;` — `UPROPERTY(VisibleAnywhere, Instanced, Category=ImportSettings)` — Import data for this
- L43 _public prototype_ `virtual void GetAssetRegistryTags(FAssetRegistryTagsContext Context) const override;` — Override to ensure we write out the asset import data

### `Plugins/2D/Paper2D/Source/SpriterImporter/Private/SpriterDataModel.h` (Private)


#### enum `ESpriterObjectType`  
`enum class ESpriterObjectType : uint8`  
_L15-27_
- reflection: `UENUM()`
- L17 _public enumerator_ `INVALID`
- L19 _public enumerator_ `Sprite` — Default when not specified
- L20 _public enumerator_ `Bone`
- L21 _public enumerator_ `Box`
- L22 _public enumerator_ `Point`
- L23 _public enumerator_ `Sound` — ?
- L24 _public enumerator_ `Entity` — ?
- L25 _public enumerator_ `Variable` — ?
- L26 _public enumerator_ `Event`

#### enum `ESpriterCurveType`  
`enum class ESpriterCurveType : uint8`  
_L30-38_
- reflection: `UENUM()`
- L32 _public enumerator_ `INVALID`
- L33 _public enumerator_ `Instant`
- L35 _public enumerator_ `Linear` — Default when not specified
- L36 _public enumerator_ `Quadratic`
- L37 _public enumerator_ `Cubic`

#### enum `ESpriterVariableType`  
`enum class ESpriterVariableType : uint8`  
_L41-47_
- reflection: `UENUM()`
- L43 _public enumerator_ `INVALID`
- L44 _public enumerator_ `Float`
- L45 _public enumerator_ `Integer`
- L46 _public enumerator_ `String`

#### enum `ESpriterFileType`  
`enum class ESpriterFileType : uint8`  
_L50-55_
- reflection: `UENUM()`
- L52 _public enumerator_ `INVALID`
- L53 _public enumerator_ `Sprite`
- L54 _public enumerator_ `Sound`

#### struct `FSpriterEnumHelper`  
`struct FSpriterEnumHelper`  
_L57-67_
- L60 _public prototype_ `static ESpriterObjectType StringToObjectType(const FString& InString);`
- L61 _public prototype_ `static ESpriterCurveType StringToCurveType(const FString& InString);`
- L62 _public prototype_ `static ESpriterVariableType StringToVariableType(const FString& InString);`
- L63 _public prototype_ `static ESpriterFileType StringToFileType(const FString& InString);`
- L66 _private function_ `FSpriterEnumHelper()`

#### struct `FSpriterSpatialInfo`  
`struct FSpriterSpatialInfo`  
_L73-102_
- reflection: `USTRUCT()`
- L78 _public member_ `double X;` — `UPROPERTY(VisibleAnywhere, Category = "Spriter")`
- L81 _public member_ `double Y;` — `UPROPERTY(VisibleAnywhere, Category = "Spriter")`
- L85 _public member_ `double AngleInDegrees;` — `UPROPERTY(VisibleAnywhere, Category = "Spriter")` — Angle (in degrees)
- L88 _public member_ `double ScaleX;` — `UPROPERTY(VisibleAnywhere, Category = "Spriter")`
- L91 _public member_ `double ScaleY;` — `UPROPERTY(VisibleAnywhere, Category = "Spriter")`
- L94 _public member_ `FLinearColor Color;` — `UPROPERTY(VisibleAnywhere, Category = "Spriter")`
- L97 _public prototype_ `FSpriterSpatialInfo();`
- L99 _public prototype_ `bool ParseFromJSON(TSharedPtr<FJsonObject> Tree, const FString& NameForErrors, bool bSilent);`
- L101 _public prototype_ `FTransform ConvertToTransform() const;`

#### struct `FSpriterFile`  
`struct FSpriterFile`  
_L108-133_
- reflection: `USTRUCT()`
- L113 _public member_ `FString Name;` — `UPROPERTY(VisibleAnywhere, Category = "Spriter")`
- L116 _public member_ `double PivotX;` — `UPROPERTY(VisibleAnywhere, Category = "Spriter")`
- L119 _public member_ `double PivotY;` — `UPROPERTY(VisibleAnywhere, Category = "Spriter")`
- L122 _public member_ `int32 Width;` — `UPROPERTY(VisibleAnywhere, Category = "Spriter")`
- L125 _public member_ `int32 Height;` — `UPROPERTY(VisibleAnywhere, Category = "Spriter")`
- L128 _public member_ `ESpriterFileType FileType;` — `UPROPERTY(VisibleAnywhere, Category = "Spriter")`
- L131 _public prototype_ `FSpriterFile();`
- L132 _public prototype_ `bool ParseFromJSON(TSharedPtr<FJsonObject> Tree, const FString& NameForErrors, bool bSilent);`

#### struct `FSpriterFolder`  
`struct FSpriterFolder`  
_L139-153_
- reflection: `USTRUCT()`
- L145 _public member_ `FString Name;` — `UPROPERTY(VisibleAnywhere, Category = "Spriter")`
- L148 _public member_ `TArray<FSpriterFile> Files;` — `UPROPERTY(VisibleAnywhere, Category = "Spriter")`
- L151 _public prototype_ `FSpriterFolder();`
- L152 _public prototype_ `bool ParseFromJSON(TSharedPtr<FJsonObject> Tree, const FString& NameForErrors, bool bSilent);`

#### struct `FSpriterMapInstruction`  
`struct FSpriterMapInstruction`  
_L159-179_
- reflection: `USTRUCT()`
- L165 _public member_ `int32 Folder;` — `UPROPERTY(VisibleAnywhere, Category = "Spriter")`
- L168 _public member_ `int32 File;` — `UPROPERTY(VisibleAnywhere, Category = "Spriter")`
- L171 _public member_ `int32 TargetFolder;` — `UPROPERTY(VisibleAnywhere, Category = "Spriter")`
- L174 _public member_ `int32 TargetFile;` — `UPROPERTY(VisibleAnywhere, Category = "Spriter")`
- L177 _public prototype_ `FSpriterMapInstruction();`
- L178 _public prototype_ `bool ParseFromJSON(TSharedPtr<FJsonObject> Tree, const FString& NameForErrors, bool bSilent);`

#### struct `FSpriterTagLineKey`  
`struct FSpriterTagLineKey`  
_L185-199_
- reflection: `USTRUCT()`
- L191 _public member_ `int32 TimeInMS;` — `UPROPERTY(VisibleAnywhere, Category = "Spriter")`
- L194 _public member_ `TArray<int32> Tags;` — `UPROPERTY(VisibleAnywhere, Category = "Spriter")`
- L197 _public prototype_ `FSpriterTagLineKey();`
- L198 _public prototype_ `bool ParseFromJSON(TSharedPtr<FJsonObject> Tree, const FString& NameForErrors, bool bSilent);`

#### struct `FSpriterTagLine`  
`struct FSpriterTagLine`  
_L205-216_
- reflection: `USTRUCT()`
- L211 _public member_ `TArray<FSpriterTagLineKey> Keys;` — `UPROPERTY(VisibleAnywhere, Category = "Spriter")`
- L214 _public prototype_ `FSpriterTagLine();`
- L215 _public prototype_ `bool ParseFromJSON(TSharedPtr<FJsonObject> Tree, const FString& NameForErrors, bool bSilent);`

#### struct `FSpriterValLineKey`  
`struct FSpriterValLineKey`  
_L222-242_
- reflection: `USTRUCT()`
- L228 _public member_ `int32 TimeInMS;` — `UPROPERTY(VisibleAnywhere, Category = "Spriter")`
- L231 _public member_ `bool bReadAsNumber;` — `UPROPERTY(VisibleAnywhere, Category = "Spriter")`
- L234 _public member_ `double ValueAsNumber;` — `UPROPERTY(VisibleAnywhere, Category = "Spriter")`
- L237 _public member_ `FString ValueAsString;` — `UPROPERTY(VisibleAnywhere, Category = "Spriter")`
- L240 _public prototype_ `FSpriterValLineKey();`
- L241 _public prototype_ `bool ParseFromJSON(TSharedPtr<FJsonObject> Tree, const FString& NameForErrors, bool bSilent);`

#### struct `FSpriterValLine`  
`struct FSpriterValLine`  
_L248-262_
- reflection: `USTRUCT()`
- L254 _public member_ `TArray<FSpriterValLineKey> Keys;` — `UPROPERTY(VisibleAnywhere, Category = "Spriter")`
- L257 _public member_ `int32 DefinitionIndex;` — `UPROPERTY(VisibleAnywhere, Category = "Spriter")`
- L260 _public prototype_ `FSpriterValLine();`
- L261 _public prototype_ `bool ParseFromJSON(TSharedPtr<FJsonObject> Tree, const FString& NameForErrors, bool bSilent);`

#### struct `FSpriterMeta`  
`struct FSpriterMeta`  
_L268-282_
- reflection: `USTRUCT()`
- L274 _public member_ `TArray<FSpriterTagLine> TagLines;` — `UPROPERTY(VisibleAnywhere, Category = "Spriter")`
- L277 _public member_ `TArray<FSpriterValLine> ValLines;` — `UPROPERTY(VisibleAnywhere, Category = "Spriter")`
- L280 _public prototype_ `FSpriterMeta();`
- L281 _public prototype_ `bool ParseFromJSON(TSharedPtr<FJsonObject> Tree, const FString& NameForErrors, bool bSilent);`

#### struct `FSpriterRefCommon`  
`struct FSpriterRefCommon`  
_L288-305_
- reflection: `USTRUCT()`
- L294 _public member_ `int32 ParentIndex;` — `UPROPERTY(VisibleAnywhere, Category = "Spriter")`
- L297 _public member_ `int32 TimelineIndex;` — `UPROPERTY(VisibleAnywhere, Category = "Spriter")`
- L300 _public member_ `int32 KeyIndex;` — `UPROPERTY(VisibleAnywhere, Category = "Spriter")`
- L303 _public prototype_ `FSpriterRefCommon();`
- L304 _public prototype_ `bool ParseCommonFromJSON(TSharedPtr<FJsonObject> Tree, const FString& NameForErrors, bool bSilent);`

#### struct `FSpriterRef`  
`struct FSpriterRef : public FSpriterRefCommon`  
_L311-317_
- reflection: `USTRUCT()`
- inherits: `FSpriterRefCommon`
- L316 _public prototype_ `bool ParseFromJSON(TSharedPtr<FJsonObject> Tree, const FString& NameForErrors, bool bSilent);`

#### struct `FSpriterObjectRef`  
`struct FSpriterObjectRef : public FSpriterRefCommon`  
_L323-334_
- reflection: `USTRUCT()`
- inherits: `FSpriterRefCommon`
- L329 _public member_ `int32 ZIndex;` — `UPROPERTY(VisibleAnywhere, Category = "Spriter")`
- L332 _public prototype_ `FSpriterObjectRef();`
- L333 _public prototype_ `bool ParseFromJSON(TSharedPtr<FJsonObject> Tree, const FString& NameForErrors, bool bSilent);`

#### struct `FSpriterMainlineKey`  
`struct FSpriterMainlineKey`  
_L340-360_
- reflection: `USTRUCT()`
- L346 _public member_ `int32 TimeInMS;` — `UPROPERTY(VisibleAnywhere, Category = "Spriter")`
- L349 _public member_ `TArray<FSpriterRef> BoneRefs;` — `UPROPERTY(VisibleAnywhere, Category = "Spriter")`
- L352 _public member_ `TArray<FSpriterObjectRef> ObjectRefs;` — `UPROPERTY(VisibleAnywhere, Category = "Spriter")`
- L355 _public member_ `ESpriterCurveType CurveType;` — `UPROPERTY(VisibleAnywhere, Category = "Spriter")`
- L358 _public prototype_ `FSpriterMainlineKey();`
- L359 _public prototype_ `bool ParseFromJSON(TSharedPtr<FJsonObject> Tree, const FString& NameForErrors, bool bSilent);`

#### struct `FSpriterTimelineKey`  
`struct FSpriterTimelineKey`  
_L366-389_
- reflection: `USTRUCT()`
- L372 _public member_ `int32 TimeInMS;` — `UPROPERTY(VisibleAnywhere, Category = "Spriter")`
- L375 _public member_ `ESpriterCurveType CurveType;` — `UPROPERTY(VisibleAnywhere, Category = "Spriter")`
- L378 _public member_ `double C1;` — `UPROPERTY(VisibleAnywhere, Category = "Spriter")`
- L381 _public member_ `double C2;` — `UPROPERTY(VisibleAnywhere, Category = "Spriter")`
- L384 _public member_ `int32 Spin;` — `UPROPERTY(VisibleAnywhere, Category = "Spriter")`
- L387 _public prototype_ `FSpriterTimelineKey();`
- L388 _public prototype_ `bool ParseBasicsFromJSON(TSharedPtr<FJsonObject> Tree, const FString& NameForErrors, bool bSilent);`

#### struct `FSpriterFatTimelineKey`  
`struct FSpriterFatTimelineKey : public FSpriterTimelineKey`  
_L395-425_
- reflection: `USTRUCT()`
- inherits: `FSpriterTimelineKey`
- L400 _public member_ `FSpriterSpatialInfo Info;` — `UPROPERTY(VisibleAnywhere, Category = "Spriter")`
- L404 _public member_ `int32 Folder;` — `UPROPERTY(VisibleAnywhere, Category = "Spriter")` — Only valid in 'object' keys (Sprite, Point, etc...)
- L407 _public member_ `int32 File;` — `UPROPERTY(VisibleAnywhere, Category = "Spriter")`
- L410 _public member_ `double PivotX;` — `UPROPERTY(VisibleAnywhere, Category = "Spriter")`
- L413 _public member_ `double PivotY;` — `UPROPERTY(VisibleAnywhere, Category = "Spriter")`
- L416 _public member_ `bool bUseDefaultPivot;` — `UPROPERTY(VisibleAnywhere, Category = "Spriter")`
- L420 _public prototype_ `FSpriterFatTimelineKey();`
- L422 _public prototype_ `bool ParseFromJSON(TSharedPtr<FJsonObject> Tree, const FString& NameForErrors, bool bSilent, const ESpriterObjectType ObjectType);`
- L423 _public prototype_ `bool ParseBoneFromJSON(TSharedPtr<FJsonObject> Tree, const FString& NameForErrors, bool bSilent);`
- L424 _public prototype_ `bool ParseObjectFromJSON(TSharedPtr<FJsonObject> Tree, const FString& NameForErrors, bool bSilent, const ESpriterObjectType ObjectType);`

#### struct `FSpriterTimeline`  
`struct FSpriterTimeline`  
_L431-454_
- reflection: `USTRUCT()`
- L437 _public member_ `FString Name;` — `UPROPERTY(VisibleAnywhere, Category="Spriter")`
- L440 _public member_ `int32 ObjectIndex;` — `UPROPERTY(VisibleAnywhere, Category = "Spriter")`
- L443 _public member_ `ESpriterObjectType ObjectType;` — `UPROPERTY(VisibleAnywhere, Category = "Spriter")`
- L446 _public member_ `TArray<FSpriterFatTimelineKey> Keys;` — `UPROPERTY(VisibleAnywhere, Category = "Spriter")`
- L449 _public member_ `FSpriterMeta Metadata;` — `UPROPERTY(VisibleAnywhere, Category = "Spriter")`
- L452 _public prototype_ `FSpriterTimeline();`
- L453 _public prototype_ `bool ParseFromJSON(TSharedPtr<FJsonObject> Tree, const FString& NameForErrors, bool bSilent);`

#### struct `FSpriterEventLineKey`  
`struct FSpriterEventLineKey`  
_L460-471_
- reflection: `USTRUCT()`
- L466 _public member_ `int32 TimeInMS;` — `UPROPERTY(VisibleAnywhere, Category = "Spriter")`
- L469 _public prototype_ `FSpriterEventLineKey();`
- L470 _public prototype_ `bool ParseFromJSON(TSharedPtr<FJsonObject> Tree, const FString& NameForErrors, bool bSilent);`

#### struct `FSpriterEventLine`  
`struct FSpriterEventLine`  
_L477-494_
- reflection: `USTRUCT()`
- L483 _public member_ `FString Name;` — `UPROPERTY(VisibleAnywhere, Category = "Spriter")`
- L486 _public member_ `TArray<FSpriterEventLineKey> Keys;` — `UPROPERTY(VisibleAnywhere, Category = "Spriter")`
- L489 _public member_ `int32 ObjectIndex;` — `UPROPERTY(VisibleAnywhere, Category = "Spriter")`
- L492 _public prototype_ `FSpriterEventLine();`
- L493 _public prototype_ `bool ParseFromJSON(TSharedPtr<FJsonObject> Tree, const FString& NameForErrors, bool bSilent);`

#### struct `FSpriterAnimation`  
`struct FSpriterAnimation`  
_L500-532_
- reflection: `USTRUCT()`
- L506 _public member_ `FString Name;` — `UPROPERTY(VisibleAnywhere, Category = "Spriter")`
- L509 _public member_ `int32 LengthInMS;` — `UPROPERTY(VisibleAnywhere, Category = "Spriter")`
- L512 _public member_ `int32 IntervalInMS;` — `UPROPERTY(VisibleAnywhere, Category = "Spriter")`
- L515 _public member_ `bool bIsLooping;` — `UPROPERTY(VisibleAnywhere, Category = "Spriter")`
- L518 _public member_ `FSpriterMeta Metadata;` — `UPROPERTY(VisibleAnywhere, Category = "Spriter")`
- L521 _public member_ `TArray<FSpriterMainlineKey> MainlineKeys;` — `UPROPERTY(VisibleAnywhere, Category = "Spriter")`
- L524 _public member_ `TArray<FSpriterTimeline> Timelines;` — `UPROPERTY(VisibleAnywhere, Category = "Spriter")`
- L527 _public member_ `TArray<FSpriterEventLine> EventLines;` — `UPROPERTY(VisibleAnywhere, Category = "Spriter")`
- L530 _public prototype_ `FSpriterAnimation();`
- L531 _public prototype_ `bool ParseFromJSON(TSharedPtr<FJsonObject> Tree, const FString& NameForErrors, bool bSilent);`

#### struct `FSpriterCharacterMap`  
`struct FSpriterCharacterMap`  
_L538-552_
- reflection: `USTRUCT()`
- L544 _public member_ `FString Name;` — `UPROPERTY(VisibleAnywhere, Category = "Spriter")`
- L547 _public member_ `TArray<FSpriterMapInstruction> Maps;` — `UPROPERTY(VisibleAnywhere, Category = "Spriter")`
- L550 _public prototype_ `FSpriterCharacterMap();`
- L551 _public prototype_ `bool ParseFromJSON(TSharedPtr<FJsonObject> Tree, const FString& NameForErrors, bool bSilent);`

#### struct `FSpriterVariableDefinition`  
`struct FSpriterVariableDefinition`  
_L558-578_
- reflection: `USTRUCT()`
- L564 _public member_ `FString Name;` — `UPROPERTY(VisibleAnywhere, Category = "Spriter")`
- L567 _public member_ `ESpriterVariableType VariableType;` — `UPROPERTY(VisibleAnywhere, Category = "Spriter")`
- L570 _public member_ `double DefaultValueNumber;` — `UPROPERTY(VisibleAnywhere, Category = "Spriter")`
- L573 _public member_ `FString DefaultValueString;` — `UPROPERTY(VisibleAnywhere, Category = "Spriter")`
- L576 _public prototype_ `FSpriterVariableDefinition();`
- L577 _public prototype_ `bool ParseFromJSON(TSharedPtr<FJsonObject> Tree, const FString& NameForErrors, bool bSilent);`

#### struct `FSpriterObjectInfo`  
`struct FSpriterObjectInfo`  
_L584-613_
- reflection: `USTRUCT()`
- L590 _public member_ `FName ObjectName;` — `UPROPERTY(VisibleAnywhere, Category = "Spriter")`
- L593 _public member_ `double Width;` — `UPROPERTY(VisibleAnywhere, Category = "Spriter")`
- L596 _public member_ `double Height;` — `UPROPERTY(VisibleAnywhere, Category = "Spriter")`
- L599 _public member_ `double PivotX;` — `UPROPERTY(VisibleAnywhere, Category = "Spriter")`
- L602 _public member_ `double PivotY;` — `UPROPERTY(VisibleAnywhere, Category = "Spriter")`
- L605 _public member_ `ESpriterObjectType ObjectType;` — `UPROPERTY(VisibleAnywhere, Category = "Spriter")`
- L608 _public member_ `TArray<FSpriterVariableDefinition> VariableDefinitions;` — `UPROPERTY(VisibleAnywhere, Category = "Spriter")`
- L611 _public prototype_ `FSpriterObjectInfo();`
- L612 _public prototype_ `bool ParseFromJSON(TSharedPtr<FJsonObject> Tree, const FString& NameForErrors, bool bSilent);`

#### struct `FSpriterEntity`  
`struct FSpriterEntity`  
_L619-642_
- reflection: `USTRUCT()`
- L625 _public member_ `FString Name;` — `UPROPERTY(VisibleAnywhere, Category = "Spriter")`
- L628 _public member_ `TArray<FSpriterCharacterMap> CharacterMaps;` — `UPROPERTY(VisibleAnywhere, Category = "Spriter")`
- L631 _public member_ `TArray<FSpriterAnimation> Animations;` — `UPROPERTY(VisibleAnywhere, Category = "Spriter")`
- L634 _public member_ `TArray<FSpriterObjectInfo> Objects;` — `UPROPERTY(VisibleAnywhere, Category = "Spriter")`
- L637 _public member_ `TArray<FSpriterVariableDefinition> VariableDefinitions;` — `UPROPERTY(VisibleAnywhere, Category = "Spriter")`
- L640 _public prototype_ `FSpriterEntity();`
- L641 _public prototype_ `bool ParseFromJSON(TSharedPtr<FJsonObject> Tree, const FString& NameForErrors, bool bSilent);`

#### struct `FSpriterSCON`  
`struct FSpriterSCON`  
_L648-682_
- reflection: `USTRUCT()`
- L655 _public member_ `FString Generator;` — `UPROPERTY(VisibleAnywhere, Category = "Spriter")` — "generator" : "BrashMonkey Spriter",
- L659 _public member_ `FString GeneratorVersion;` — `UPROPERTY(VisibleAnywhere, Category = "Spriter")` — "generator_version" : "r2",
- L663 _public member_ `FString SconVersion;` — `UPROPERTY(VisibleAnywhere, Category = "Spriter")` — "scon_version" : "1.0"
- L666 _public member_ `TArray<FSpriterFolder> Folders;` — `UPROPERTY(VisibleAnywhere, Category = "Spriter")`
- L669 _public member_ `TArray<FSpriterEntity> Entities;` — `UPROPERTY(VisibleAnywhere, Category = "Spriter")`
- L672 _public member_ `TArray<FString> Tags;` — `UPROPERTY(VisibleAnywhere, Category = "Spriter")`
- L674 _public member_ `bool bSuccessfullyParsed;`
- L677 _public prototype_ `FSpriterSCON();`
- L679 _public prototype_ `void ParseFromJSON(TSharedPtr<FJsonObject> Tree, const FString& NameForErrors, bool bSilent, bool bPreparseOnly);`
- L681 _public prototype_ `bool IsValid() const;`

### `Plugins/2D/Paper2D/Source/SpriterImporter/Private/SpriterImporterFactory.h` (Private)


#### class `USpriterImporterFactory`  
`class USpriterImporterFactory : public UFactory`  
_L11-27_
- reflection: `UCLASS()`
- inherits: `UFactory`
- desc: Imports a rigged sprite character (and associated textures & animations) exported from Spriter (http://www.brashmonkey.com/)
- L16 _private prototype_ `virtual FText GetToolTip() const override;` — UFactory interface
- L17 _private prototype_ `virtual bool FactoryCanImport(const FString& Filename) override;`
- L18 _private prototype_ `virtual UObject* FactoryCreateText(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, const TCHAR* Type, const TCHAR*& Buffer, const TCHAR* BufferEnd, FFeedbackContext* Warn) override;`
- L22 _protected prototype_ `TSharedPtr<FJsonObject> ParseJSON(const FString& FileContents, const FString& NameForErrors, bool bSilent = false);`
- L24 _protected prototype_ `static UObject* CreateNewAsset(UClass* AssetClass, const FString& TargetPath, const FString& DesiredName, EObjectFlags Flags);`
- L25 _protected prototype_ `static UObject* ImportAsset(const FString& SourceFilename, const FString& TargetSubPath);`
- L26 _protected prototype_ `static UTexture2D* ImportTexture(const FString& SourceFilename, const FString& TargetSubPath);`

### `Plugins/2D/Paper2D/Source/SpriterImporter/Private/SpriterImporterLog.h` (Private)


#### Free symbols / members of external scopes

- L8 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogSpriterImporter, Verbose, All);`
- L8 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogSpriterImporter, Verbose, All);`
- L10 _macro_ `#define SPRITER_IMPORT_ERROR(FormatString, ...) \`
- L12 _macro_ `#define SPRITER_IMPORT_WARNING(FormatString, ...) \`
