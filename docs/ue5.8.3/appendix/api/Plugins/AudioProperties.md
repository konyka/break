# Plugins / AudioProperties

- module root: `Plugins/Experimental/AudioProperties/Source/AudioProperties`
- headers: 10; symbols: 96
- symbol kinds: class=7, delegate=3, enum=1, enumerator=4, function=4, macro=1, member=19, namespace=8, prototype=42, struct=3, typedef=3, variable=1
- PublicDependencyModuleNames: AssetRegistry, AudioExtensions, Core, CoreUObject, TargetPlatform

### `Plugins/Experimental/AudioProperties/Source/AudioProperties/Private/AudioPropertiesParser.h` (Private)


#### class `FAudioPropertiesParser`  
`class FAudioPropertiesParser`  
_L17-27_
- L20 _public prototype_ `static void GenerateNameMatchedParsingData(UE::AudioGameplay::FAudioPropertiesParsingData& ParsingData);`
- L21 _public prototype_ `static void InjectPropertyValuesIntoObject(UObject& TargetObject, const UE::AudioGameplay::FAudioPropertiesParsingData& ParsingData);`
- L24 _public prototype_ `static bool ShouldApplyTargetMetadataToProperties(const UE::AudioGameplay::FAudioPropertiesParsingData& ParsingData);`
- L25 _public prototype_ `static void ApplyTargetMetadataToSheetTree(UAudioPropertiesSheetAsset& InSheetAsset, const UE::AudioGameplay::FAudioPropertiesParsingData& ParsingData);`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L11 _namespace_ `namespace AudioGameplay` (scope `UE`)

### `Plugins/Experimental/AudioProperties/Source/AudioProperties/Public/AudioPropertiesBindings.h` (Public)


#### class `UAudioPropertiesBindings`  
`class UAudioPropertiesBindings : public UObject`  
_L10-19_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- L14 _private prototype_ `UAudioPropertiesBindings() = default;`
- L18 _public member_ `TMap<FName, FName> ObjectPropertyToSheetPropertyMap;` — `UPROPERTY(EditDefaultsOnly, Category = "Default")`

### `Plugins/Experimental/AudioProperties/Source/AudioProperties/Public/AudioPropertiesLogs.h` (Public)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogAudioProperties, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogAudioProperties, Log, All);`

### `Plugins/Experimental/AudioProperties/Source/AudioProperties/Public/AudioPropertiesModule.h` (Public)


#### class `FAudioPropertiesModule`  
`class FAudioPropertiesModule : public IModuleInterface`  
_L7-12_
- inherits: `IModuleInterface`
- L10 _public prototype_ `virtual void StartupModule() override;`
- L11 _public prototype_ `virtual void ShutdownModule() override;`

### `Plugins/Experimental/AudioProperties/Source/AudioProperties/Public/AudioPropertiesParserBase.h` (Public)


#### struct `FInstancedObjectParsingInstructions`  
`struct FInstancedObjectParsingInstructions`  
_L22-40_
- reflection: `USTRUCT()`
- L28 _public member_ `TSubclassOf<UObject> InstancedObjectClass;` — `UPROPERTY(EditAnywhere, Category = "Parsing Instructions")` — The instanced object class that will be targeted by these instructions
- L32 _public member_ `bool bCreateIfMissing = false;` — `UPROPERTY(EditAnywhere, Category = "Parsing Instructions")` — If the target instanced uobject is missing, create one with the properties that should have been parsed
- L36 _public member_ `bool bOverrideParsing = false;` — `UPROPERTY(EditAnywhere, Category = "Parsing Instructions")` — Use this to signal that you would like to use a different parser for the instanced objects
- L39 _public member_ `TObjectPtr<UAudioPropertiesParserBase> PropertiesParser;` — `UPROPERTY(EditAnywhere, Instanced, Category = "Parsing Instructions", meta = (EditCondition = "bOverrideParsing", EditConditionHides))`

#### class `UAudioPropertiesParserBase`  
`class UAudioPropertiesParserBase : public UObject`  
_L45-58_
- reflection: `UCLASS(Abstract, EditInlineNew, MinimalAPI)`
- inherits: `UObject`
- L50 _public function_ `virtual bool GenerateParsingData(TObjectPtr<const UObject> TargetObject, const FAudioPropertiesSheet& SourceSheet, UE::AudioGameplay::FAudioPropertiesParsingData& InOutData) const`
- L51 _public function_ `virtual bool ParseProperties(TObjectPtr<UObject> TargetObject, const FAudioPropertiesSheet& PropertiesToParse) const`
- L54 _public function_ `virtual bool ValidatePropertiesOnAssetTree(const UAudioPropertiesSheetAsset& InSheetAsset) const`
- L55 _public function_ `virtual void FitPropertiesOnAssetTree(UAudioPropertiesSheetAsset& InSheetAsset) const`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L15 _namespace_ `namespace AudioGameplay` (scope `UE`)

### `Plugins/Experimental/AudioProperties/Source/AudioProperties/Public/AudioPropertiesParserBindings.h` (Public)


#### class `UAudioPropertiesParserBindings`  
`class UAudioPropertiesParserBindings : public UAudioPropertiesParserNameMatch`  
_L22-39_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAudioPropertiesParserNameMatch`
- desc: UAudioPropertiesParserBindings Parses values from a Property Sheet to a target UObject following the name mappings defined in the BindingsAsset. Properties need to be of compatible types for values to be parsed.
- L29 _public member_ `TObjectPtr<UAudioPropertiesBindings> BindingsAsset;` — `UPROPERTY(EditAnywhere, Category = "AudioProperties")` — The bindings that will be used to parse properties from the Sheet to the target asset
- L31 _public prototype_ `virtual bool GenerateParsingData(TObjectPtr<const UObject> TargetObject, const FAudioPropertiesSheet& SourceSheet, UE::AudioGameplay::FAudioPropertiesParsingData& InOutData) const override;`
- L32 _public prototype_ `virtual bool ParseProperties(TObjectPtr<UObject> TargetObject, const FAudioPropertiesSheet& PropertiesToParse) const override;`
- L37 _protected prototype_ `virtual bool GenerateParsingDataFromTargetClass(UClass* TargetClass, UE::AudioGameplay::FAudioPropertiesParsingData& InOutData) const override;`

### `Plugins/Experimental/AudioProperties/Source/AudioProperties/Public/AudioPropertiesParserNameMatch.h` (Public)


#### class `UAudioPropertiesParserNameMatch`  
`class UAudioPropertiesParserNameMatch : public UAudioPropertiesParserBase`  
_L18-42_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAudioPropertiesParserBase`
- desc: UAudioPropertiesParserNameMatch Parses values from a Property Sheet to a target UObject of compatible type properties with the same name
- L23 _public prototype_ `virtual bool GenerateParsingData(TObjectPtr<const UObject> TargetObject, const FAudioPropertiesSheet& SourceSheet, UE::AudioGameplay::FAudioPropertiesParsingData& InOutData) const override;`
- L24 _public prototype_ `virtual bool ParseProperties(TObjectPtr<UObject> TargetObject, const FAudioPropertiesSheet& PropertiesToParse) const override;`
- L27 _public member_ `TArray<FInstancedObjectParsingInstructions> InstancedObjectsRules;` — `UPROPERTY(EditAnywhere, Category = "Instanced Objects Parsing")`
- L30 _public prototype_ `bool ValidatePropertiesOnAssetTree(const UAudioPropertiesSheetAsset& InSheetAsset) const override;`
- L31 _public prototype_ `virtual void FitPropertiesOnAssetTree(UAudioPropertiesSheetAsset& InSheetAsset) const override;`
- L34 _public member_ `TSubclassOf<UObject> ValidationClass;` — `UPROPERTY(EditAnywhere, Category = "Validation")`
- L40 _protected prototype_ `virtual bool GenerateParsingDataFromTargetClass(UClass* TargetClass, UE::AudioGameplay::FAudioPropertiesParsingData& InOutData) const;`

### `Plugins/Experimental/AudioProperties/Source/AudioProperties/Public/AudioPropertiesParsingData.h` (Public)


#### struct `UE::AudioGameplay::FAudioPropertiesParsingData`  
`struct FAudioPropertiesParsingData`  
_L17-24_
- L19 _public member_ `const FAudioPropertiesSheet* SourcePropertySheet = nullptr;`
- L20 _public member_ `UClass* TargetClass = nullptr;`
- L21 _public member_ `FAudioPropertiesBindings SourceToTargetPropertyBindings;`
- L22 _public member_ `bool bCreateNewObjects = false;`
- L23 _public member_ `TArray<FAudioPropertiesParsingData> InstancedObjectsParsingData;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L13 _namespace_ `namespace AudioGameplay` (scope `UE`)
- L15 _typedef_ `using FAudioPropertiesBindings = TMap<FName, FName>;` (scope `UE::AudioGameplay`)

### `Plugins/Experimental/AudioProperties/Source/AudioProperties/Public/AudioPropertiesSheet.h` (Public)


#### enum `AudioPropertiesSheet::PostEditChangeType`  
`enum class PostEditChangeType : uint8`  
_L23-29_
- L25 _public enumerator_ `Other`
- L26 _public enumerator_ `ParentChange`
- L27 _public enumerator_ `PropertyBag`
- L28 _public enumerator_ `PropertiesParser`

#### struct `FAudioPropertiesSheet`  
`struct FAudioPropertiesSheet`  
_L39-65_
- reflection: `USTRUCT()`
- L44 _public member_ `TObjectPtr<const UAudioPropertiesSheetAsset> Parent;` — `UPROPERTY(EditAnywhere, Category = "Default")`
- L47 _public member_ `FInstancedPropertyBag Properties;` — `UPROPERTY(EditAnywhere, Category = "Default")`
- L49 _public prototype_ `bool UpdatePropertyOverride(const FProperty& InProperty, bool bMarkAsOverridden);`
- L51 _public prototype_ `bool IsPropertyOverridden(const FProperty& InProperty) const;`
- L53 _public prototype_ `void ReconcileProperties();`
- L55 _public prototype_ `void OnPreSave(const FObjectPreSaveContext& SaveContext);`
- L57 _public prototype_ `AudioPropertiesSheet::PropertyDescParentPair FindClosestParentWithProperty(const FProperty& InProperty) const;`
- L60 _public member_ `FOnAudioPropertyOverride OnAudioPropertyOverrideChange;`
- L63 _private prototype_ `void FlattenSheet();`

#### class `UAudioPropertiesSheetAsset`  
`class UAudioPropertiesSheetAsset : public UAudioPropertiesSheetAssetBase`  
_L68-111_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UAudioPropertiesSheetAssetBase`
- L73 _public prototype_ `UAudioPropertiesSheetAsset(const FObjectInitializer& ObjectInitializer);`
- L76 _public member_ `FAudioPropertiesSheet PropertiesSheet;` — `UPROPERTY(EditAnywhere, Category = "Default")`
- L81 _public member_ `TObjectPtr<UAudioPropertiesParserBase> PropertiesParser;` — `UPROPERTY(EditAnywhere, Instanced, Category = "Parser")` — The properties parser determines how the properties on this sheet are applied to target UObjects NOTE: A null parser will mean no properties are applied - a child sheet will however inherit the parent parser automatically
- L87 _public prototype_ `void FitPropertiesForValidation();` — `UFUNCTION(CallInEditor, meta=(DisplayName="Fit Properties For Validation"))` — Calling this method will apply the parser validation rules to the sheet NOTE will dirty this asset and all the parents where property changes are applied
- L89 _public prototype_ `virtual bool CopyToObjectProperties(UObject* TargetObject) const override;`
- L91 _public prototype_ `virtual FDelegateHandle BindPropertiesCopyToSheetChanges(UObject* TargetObject) override;`
- L92 _public prototype_ `virtual void UnbindCopyFromPropertySheetChanges(UObject* ObjectToUnbind) override;`
- L94 _public prototype_ `void PreEditChange(FProperty* PropertyAboutToChange) override;`
- L95 _public prototype_ `void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;`
- L96 _public member_ `FOnAudioPropertySheetPostEditChange OnPostEditChange;`
- L98 _public prototype_ `void PostLoad();`
- L100 _public prototype_ `EDataValidationResult IsDataValid(class FDataValidationContext& Context) const override;`
- L102 _public prototype_ `AudioPropertiesSheet::ParserParentPair FindClosestParserInInheritanceTree() const;`
- L104 _public prototype_ `void GetTargetedPropertyNames(TObjectPtr<const UObject> TargetObject, TArray<FName>& OutProperties) const;`
- L106 _public prototype_ `void OnParentPostEditChange(const AudioPropertiesSheet::PostEditChangeType& ChangeType);`
- L109 _public prototype_ `void PreSave(FObjectPreSaveContext SaveContext) override;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API AUDIOPROPERTIES_API`
- L17 _namespace_ `namespace AudioPropertiesSheet`
- L19 _typedef_ `typedef TPair<const FPropertyBagPropertyDesc*, TObjectPtr<const UAudioPropertiesSheetAsset>> PropertyDescParentPair;` (scope `AudioPropertiesSheet`)
- L20 _typedef_ `typedef TPair<TObjectPtr<const UAudioPropertiesParserBase>, TObjectPtr<const UAudioPropertiesSheetAsset>> ParserParentPair;` (scope `AudioPropertiesSheet`)
- L34 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnAudioPropertySheetPostEditChange, AudioPropertiesSheet::PostEditChangeType);`
- L34 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnAudioPropertySheetPostEditChange, AudioPropertiesSheet::PostEditChangeType);`
- L35 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnAudioPropertyOverride, const FProperty& , bool );`
- L35 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnAudioPropertyOverride, const FProperty& , bool );`

### `Plugins/Experimental/AudioProperties/Source/AudioProperties/Public/AudioPropertiesUtils.h` (Public)


#### Free symbols / members of external scopes

- L11 _namespace_ `namespace AudioPropertiesUtils`
- L13 _variable_ `static const FLazyName AudioPropertiesOverrideTagName = "Au` (scope `AudioPropertiesUtils`)
- L15 _prototype_ `bool IsSheetInInheritanceTree(const UAudioPropertiesSheetAsset& InLeafSheet, const TObjectPtr<const UAudioPropertiesSheetAsset> InSheetToFind);` (scope `AudioPropertiesUtils`)
- L16 _prototype_ `void GetAudioPropertiesSheetAssetReferencers(const UAudioPropertiesSheetAsset& InAsset, TArray<FAssetData>& OutReferencersData, const UClass* ClassFilter = nullptr);` (scope `AudioPropertiesUtils`)
- L17 _prototype_ `void VisitAudioPropertiesSheetAssetReferencers(const UAudioPropertiesSheetAsset& InAsset, TFunctionRef<void(FAssetData&)> OnAssetVisited, const UClass* ClassFilter = nullptr);` (scope `AudioPropertiesUtils`)
- L18 _prototype_ `void VisitLeafMostProperties(const UAudioPropertiesSheetAsset& InSheetAsset, TFunction<void(const FPropertyBagPropertyDesc& , const FAudioPropertiesSheet& )> OnPropertyVisited);` (scope `AudioPropertiesUtils`)
- L19 _prototype_ `void VisitLeafMostProperties(const FAudioPropertiesSheet& InSheetAsset, TFunction<void(const FPropertyBagPropertyDesc& , const FAudioPropertiesSheet& )> OnPropertyVisited);` (scope `AudioPropertiesUtils`)
