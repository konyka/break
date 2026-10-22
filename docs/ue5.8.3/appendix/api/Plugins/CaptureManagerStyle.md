# Plugins / CaptureManagerStyle

- module root: `Plugins/VirtualProduction/CaptureManager/CaptureManagerCore/Source/CaptureManagerStyle`
- headers: 2; symbols: 10
- symbol kinds: class=2, macro=1, member=1, prototype=6
- PrivateDependencyModuleNames: Projects, Slate, SlateCore, UnrealEd
- PublicDependencyModuleNames: Core, EditorStyle

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerCore/Source/CaptureManagerStyle/Private/CaptureManagerStyleModule.h` (Private)


#### class `FCaptureManagerStyleModule`  
`class FCaptureManagerStyleModule : public IModuleInterface`  
_L7-12_
- inherits: `IModuleInterface`
- L10 _public prototype_ `virtual void StartupModule() override;`
- L11 _public prototype_ `virtual void ShutdownModule() override;`

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerCore/Source/CaptureManagerStyle/Public/CaptureManagerStyle.h` (Public)


#### class `FCaptureManagerStyle`  
`class FCaptureManagerStyle : public FSlateStyleSet`  
_L11-25_
- inherits: `FSlateStyleSet`
- desc: A style set for Capture Manager
- L15 _public prototype_ `virtual const FName& GetStyleSetName() const override;`
- L16 _public prototype_ `static const FCaptureManagerStyle& Get();`
- L18 _public prototype_ `static void ReloadTextures();`
- L22 _private prototype_ `FCaptureManagerStyle();`
- L24 _private member_ `static FName StyleName;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API CAPTUREMANAGERSTYLE_API`
