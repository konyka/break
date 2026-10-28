# Runtime / MaterialShaderQualitySettings

- module root: `Source/Runtime/MaterialShaderQualitySettings`
- headers: 4; symbols: 56
- symbol kinds: class=3, delegate=1, enum=1, enumerator=4, function=7, member=20, prototype=17, struct=2, typedef=1
- PrivateDependencyModuleNames: Core, CoreUObject, InputCore, PropertyEditor, RHI, Slate, SlateCore, TargetPlatform
- PrivateIncludePathModuleNames: Engine

### `Source/Runtime/MaterialShaderQualitySettings/Classes/MaterialShaderQualitySettings.h` (Public)


#### class `UMaterialShaderQualitySettings`  
`class UMaterialShaderQualitySettings : public UObject`  
_L16-49_
- reflection: `UCLASS(config = Engine, defaultconfig)`
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- L21 _public prototype_ `UShaderPlatformQualitySettings* GetShaderPlatformQualitySettings(FName PlatformName);`
- L23 _public prototype_ `const UShaderPlatformQualitySettings* GetShaderPlatformQualitySettings(EShaderPlatform ShaderPlatform);`
- L25 _public prototype_ `bool HasPlatformQualitySettings(EShaderPlatform ShaderPlatform, EMaterialQualityLevel::Type QualityLevel);`
- L31 _public prototype_ `void SetPreviewPlatform(FName PlatformName);` — Override GetShaderPlatformQualitySettings() return value with the specified platform's settings. An empty PlatformName or otherwise non existent platform will cause GetShaderPlatformQualitySettings() to revert to its default behaviour.
- L32 _public prototype_ `const FName& GetPreviewPlatform();`
- L35 _public prototype_ `static UMaterialShaderQualitySettings* Get();`
- L38 _private prototype_ `UShaderPlatformQualitySettings* GetOrCreatePlatformSettings(FName ShaderPlatformName);`
- L41 _private member_ `TMap<FName, TObjectPtr<UShaderPlatformQualitySettings>> ForwardSettingMap;` — `UPROPERTY()`
- L44 _private member_ `UShaderPlatformQualitySettings* PreviewPlatformSettings;`
- L45 _private member_ `FName PreviewPlatformName;`
- L48 _private member_ `static class UMaterialShaderQualitySettings* RenderQualitySingleton;`

### `Source/Runtime/MaterialShaderQualitySettings/Classes/MaterialShaderQualitySettingsCustomization.h` (Public)


#### class `FMaterialShaderQualitySettingsCustomization`  
`class FMaterialShaderQualitySettingsCustomization : public IDetailCustomization`  
_L26-46_
- inherits: `IDetailCustomization`
- L30 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance(const FOnUpdateMaterialShaderQuality InUpdateMaterials);` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L32 _public prototype_ `FMaterialShaderQualitySettingsCustomization(const FOnUpdateMaterialShaderQuality InUpdateMaterials);`
- L35 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailLayout) override;` — IDetailCustomization interface
- L40 _private prototype_ `TSharedRef<ITableRow> HandleGenerateQualityWidget(TSharedPtr< struct FShaderQualityOverridesListItem > InItem, const TSharedRef<STableViewBase>& OwnerTable);`
- L41 _private prototype_ `FReply UpdatePreviewShaders();`
- L42 _private member_ `FOnUpdateMaterialShaderQuality UpdateMaterials;`
- L43 _private prototype_ `FMaterialShaderQualitySettingsCustomization();`
- L44 _private member_ `TSharedPtr<SMaterialQualityOverridesListView> MaterialQualityOverridesListView;`
- L45 _private member_ `TArray< TSharedPtr< struct FShaderQualityOverridesListItem > > QualityOverrideListSource;`

#### Free symbols / members of external scopes

- L22 _typedef_ `typedef SListView< TSharedPtr< struct FShaderQualityOverridesListItem > > SMaterialQualityOverridesListView;`
- L24 _delegate_ `DECLARE_DELEGATE(FOnUpdateMaterialShaderQuality);`
- L24 _prototype_ `DECLARE_DELEGATE(FOnUpdateMaterialShaderQuality);`

### `Source/Runtime/MaterialShaderQualitySettings/Classes/ShaderPlatformQualitySettings.h` (Public)


#### enum `EMobileShadowQuality`  
`enum class EMobileShadowQuality : uint8`  
_L17-27_
- reflection: `UENUM()`
- L20 _public enumerator_ `NoFiltering` — Lowest quality, no filtering.
- L22 _public enumerator_ `PCF_1x1 UMETA(DisplayName = "1x1 PCF")` — Medium quality, 1x1 PCF filtering.
- L24 _public enumerator_ `PCF_3x3 UMETA(DisplayName = "3x3 PCF")` — Medium/High quality, 3x3 PCF filtering.
- L26 _public enumerator_ `PCF_5x5 UMETA(DisplayName = "5x5 PCF")` — Highest quality, 5x5 PCF filtering.

#### struct `FMaterialQualityOverrides`  
`struct FMaterialQualityOverrides`  
_L31-74_
- reflection: `USTRUCT()`
- desc: FMaterialQualityOverrides represents the full set of possible material overrides per quality level.
- L36 _public function_ `FMaterialQualityOverrides() : bDiscardQualityDuringCook(false) , bEnableOverride(false) , bForceFullyRough(false) , bForceNonMetal(false) , bForceDisableLMDirectionality(false) , bForceDisablePreintegratedGF(false) , bDisableMaterialNormalCalculation(false) , MobileShadowQuality(EMobileShadowQuality::PCF_3x3)`
- L49 _public member_ `bool bDiscardQualityDuringCook;` — `UPROPERTY(EditAnywhere, Config, Meta = (DisplayName = "Discard Quality During Cook"), Category = "Quality")`
- L52 _public member_ `bool bEnableOverride;` — `UPROPERTY(EditAnywhere, Config, Meta = (DisplayName = "Enable Quality Override"), Category = "Quality")`
- L55 _public member_ `bool bForceFullyRough;` — `UPROPERTY(EditAnywhere, Config, Meta = (DisplayName = "Force Fully Rough"), Category = "Quality")`
- L58 _public member_ `bool bForceNonMetal;` — `UPROPERTY(EditAnywhere, Config, Meta = (DisplayName = "Force Non-metal"), Category = "Quality")`
- L61 _public member_ `bool bForceDisableLMDirectionality;` — `UPROPERTY(EditAnywhere, Config, Meta = (DisplayName = "Disable Lightmap directionality"), Category = "Quality")`
- L64 _public member_ `bool bForceDisablePreintegratedGF;` — `UPROPERTY(EditAnywhere, Config, Meta = (DisplayName = "Force not use preintegrated GF for simple IBL"), Category = "Quality")`
- L67 _public member_ `bool bDisableMaterialNormalCalculation;` — `UPROPERTY(EditAnywhere, Config, Meta = (DisplayName = "Disable material normal calculation"), Category = "Quality")`
- L70 _public member_ `EMobileShadowQuality MobileShadowQuality;` — `UPROPERTY(EditAnywhere, Config, Meta = (DisplayName = "Mobile shadow mapping quality"), Category = "Quality")`
- L72 _public prototype_ `bool CanOverride(EShaderPlatform ShaderPlatform) const;`
- L73 _public prototype_ `bool HasAnyOverridesSet() const;`

#### class `UShaderPlatformQualitySettings`  
`class UShaderPlatformQualitySettings : public UObject`  
_L78-117_
- reflection: `UCLASS(config = Engine, defaultconfig, perObjectConfig, MinimalAPI)`
- inherits: `UObject`
- L84 _public member_ `FMaterialQualityOverrides QualityOverrides[EMaterialQualityLevel::Num];` — `UPROPERTY(EditAnywhere, Config, Category="Quality")`
- L86 _public function_ `FMaterialQualityOverrides& GetQualityOverrides(EMaterialQualityLevel::Type QualityLevel)`
- L92 _public prototype_ `const FMaterialQualityOverrides& GetQualityOverrides(EMaterialQualityLevel::Type QualityLevel) const;`
- L94 _public function_ `inline void BuildHash(EMaterialQualityLevel::Type QualityLevel, class FSHAHash& OutHash) const` — `UE_DEPRECATED(5.8, "UShaderPlatformQualitySettings::BuildHash is unused in engine code and has been deprecated; use AppendToHashState instead if needed.")`
- L102 _public function_ `template <typename THasher> void AppendToHashState(EMaterialQualityLevel::Type QualityLevel, THasher& HashState) const`
- L111 _public function_ `virtual const TCHAR* GetConfigOverridePlatform() const override`
- L116 _public member_ `FString ConfigPlatformName;`

### `Source/Runtime/MaterialShaderQualitySettings/Private/ShaderQualityOverridesListItem.h` (Private)


#### struct `FShaderQualityOverridesListItem`  
`struct FShaderQualityOverridesListItem`  
_L12-31_
- desc: FShaderQualityOverridesListItem Helper struct for FMaterialShaderQualitySettingsCustomization, contains info required to populate a material quality row.
- L15 _public member_ `FString RangeName;`
- L18 _public member_ `TMap<EMaterialQualityLevel::Type, TSharedRef<IPropertyHandle>> OverrideHandles;` — Property handles for this item's each override setting for each QL
- L21 _public member_ `TMap<EMaterialQualityLevel::Type, TSharedRef<IPropertyHandle>> EnabledHandles;` — Property handles for each QL's bEnabled flag, used to determine if this item's widgets should be enabled.
- L23 _public function_ `FShaderQualityOverridesListItem()`
- L25 _public function_ `FShaderQualityOverridesListItem(FString InRangeName, const TMap<EMaterialQualityLevel::Type, TSharedRef<IPropertyHandle>>& InOverrideHandles, const TMap<EMaterialQualityLevel::Type, TSharedRef<IPropertyHandle>> &InEnabledHandles) : RangeName(InRangeName) , OverrideHandles(InOverrideHandles) , EnabledHandles(InEnabledHandles)`
