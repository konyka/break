# Plugins / PerformanceCaptureCoreEditor

- module root: `Plugins/Animation/PerformanceCaptureCore/Source/PerformanceCaptureCoreEditor`
- headers: 1; symbols: 5
- symbol kinds: class=1, member=1, prototype=3
- PrivateDependencyModuleNames: CoreUObject, Engine, IKRig, LiveLinkAnimationCore, LiveLinkInterface, PerformanceCaptureCore
- PublicDependencyModuleNames: Core

### `Plugins/Animation/PerformanceCaptureCore/Source/PerformanceCaptureCoreEditor/Private/CaptureCharacterCustomization.h` (Private)


#### class `FCaptureCharacterCustomization`  
`class FCaptureCharacterCustomization : public IDetailCustomization`  
_L15-31_
- inherits: `IDetailCustomization`
- desc: Detail customization for ACaptureCharacter
- L19 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L22 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;` — Makes a new instance of this detail layout class for a specific detail view requesting it static TSharedRef<IDetailCustomization> MakeInstance(); ~ Begin IDetailCustomization interface
- L26 _private prototype_ `void CustomizePerformanceCaptureCategory(IDetailLayoutBuilder& DetailBuilder);`
- L30 _private member_ `ACaptureCharacter* CustomizedCharacter;` — The CaptureCharacter being customized
