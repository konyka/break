# Developer / ShaderPlatformConfigEditor

- module root: `Source/Developer/ShaderPlatformConfigEditor`
- headers: 2; symbols: 23
- symbol kinds: class=1, enum=1, enumerator=4, member=6, namespace=2, prototype=9
- PrivateDependencyModuleNames: Core, CoreUObject, Engine, InputCore, PropertyEditor, RHI, RenderCore, Slate, SlateCore, TargetPlatform, UnrealEd
- PublicIncludePathModuleNames: Engine, RHI

### `Source/Developer/ShaderPlatformConfigEditor/Internal/ShaderPlatformConfigEditor.h` (Internal)


#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace ShaderPlatformConfigEditor` (scope `UE`)
- L15 _prototype_ `void AddShaderPlatformConfig(IDetailLayoutBuilder& DetailBuilder, EShaderPlatform ShaderPlatform);` (scope `UE::ShaderPlatformConfigEditor`)
- L16 _prototype_ `void AddShaderPlatformConfig(IDetailLayoutBuilder& DetailBuilder, FName ShaderFormat);` (scope `UE::ShaderPlatformConfigEditor`)
- L19 _prototype_ `void AddShaderPlatformConfigs(IDetailLayoutBuilder& DetailBuilder, const ITargetPlatformSettings* TargetPlatformSettings);` (scope `UE::ShaderPlatformConfigEditor`) — Shortcuts for adding all shader formats/platforms based on ITargetPlatformSettings
- L20 _prototype_ `void AddShaderPlatformConfigsFromSettingsModule(IDetailLayoutBuilder& DetailBuilder, FName SettingsModuleName);` (scope `UE::ShaderPlatformConfigEditor`)

### `Source/Developer/ShaderPlatformConfigEditor/Private/ShaderPlatformConfigSettings.h` (Private)


#### enum `EBindlessConfigurationSetting`  
`enum class EBindlessConfigurationSetting : uint8`  
_L11-17_
- reflection: `UENUM()`
- L13 _public enumerator_ `Disabled UMETA(DisplayName = "Disabled", ToolTip = "Bindless rendering is disabled. All resources use traditional binding.")`
- L14 _public enumerator_ `RayTracing UMETA(DisplayName = "Ray Tracing", ToolTip = "Bindless enabled for Ray Tracing shaders only.")`
- L15 _public enumerator_ `Minimal UMETA(DisplayName = "Minimal", ToolTip = "Bindless enabled for a minimal set of shaders, notably Ray Tracing shaders and surface Materials.")`
- L16 _public enumerator_ `All UMETA(DisplayName = "All", ToolTip = "Bindless enabled for all shaders - may reduce performance (Experimental).")`

#### class `UShaderPlatformConfigSettings`  
`class UShaderPlatformConfigSettings : public UObject`  
_L21-53_
- reflection: `UCLASS(MinimalAPI, config=Engine, DefaultConfig, PerObjectConfig)`
- inherits: `UObject`
- desc: Temporary solution for getting editing up and running, should be replaced with custom Slate code in the future
- L28 _public member_ `EBindlessConfigurationSetting BindlessConfiguration = EBindlessConfigurationSetting::Disabled;` — `UPROPERTY(config, EditAnywhere, Category="ShaderPlatformConfigSettings", meta = (EditCondition = "CanEditBindlessConfiguration()", ToolTip = "Set Bindless configuration for this shader platform."))`
- L32 _public member_ `bool bEnableNaniteBindlessShading = false;` — `UPROPERTY(config, EditAnywhere, Category="ShaderPlatformConfigSettings", meta = (EditCondition = "IsBindlessEnabledForGraphics()", ToolTip = "Enable Nanite bindless-aware shading for this shader platform. Only usable when Bindless is Minimal or higher. (Experimental)"))`
- L36 _public member_ `bool bEnableNaniteBindlessRasterization = false;` — `UPROPERTY(config, EditAnywhere, Category="ShaderPlatformConfigSettings", meta = (EditCondition = "IsBindlessEnabledForGraphics()", ToolTip = "Enable Nanite bindless-aware rasterization for this shader platform. Only usable when Bindless is Minimal or higher. (Experimental)"))`
- L38 _public prototype_ `virtual const TCHAR* GetConfigOverridePlatform() const final;`
- L39 _public prototype_ `virtual void OverridePerObjectConfigSection(FString& InOutSectionName) final;`
- L42 _public prototype_ `bool CanEditBindlessConfiguration() const;` — `UFUNCTION()`
- L45 _public prototype_ `bool IsBindlessEnabledForGraphics() const;` — `UFUNCTION()`
- L47 _public prototype_ `void SetConfiguration(EShaderPlatform InShaderPlatform, const TCHAR* InConfigSection);`
- L50 _private member_ `EShaderPlatform ShaderPlatform{};`
- L51 _private member_ `FString ConfigPlatform;`
- L52 _private member_ `FString ConfigSection;`
