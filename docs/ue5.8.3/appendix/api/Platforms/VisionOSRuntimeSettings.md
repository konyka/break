# Platforms / VisionOSRuntimeSettings

- module root: `Platforms/VisionOS/Source/Runtime/VisionOSRuntimeSettings`
- headers: 1; symbols: 10
- symbol kinds: class=1, delegate=1, function=1, member=4, prototype=3
- PrivateDependencyModuleNames: Core, CoreUObject

### `Platforms/VisionOS/Source/Runtime/VisionOSRuntimeSettings/Classes/VisionOSRuntimeSettings.h` (Public)


#### class `UVisionOSRuntimeSettings`  
`class UVisionOSRuntimeSettings : public UObject`  
_L17-49_
- reflection: `UCLASS(config=Engine, defaultconfig)`
- inherits: `UObject`
- desc: Implements the settings for the VisionOS target platform.
- L23 _public function_ `virtual const TCHAR* GetConfigOverridePlatform() const override` — Use VisionOS .ini files in the editor
- L29 _public prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;`
- L30 _public prototype_ `virtual void PostInitProperties() override;`
- L36 _public member_ `bool bUseSwiftUIMain;` — `UPROPERTY(config, EditAnywhere, Category = Build, Meta = (DisplayName = "Enable visionOS's Immersion Mode (Experimental)", ConfigRestartRequired = true))` — When building for visionOS, default to Full Immersion mode.  If disabled, switches to Window mode. Note: when enabled, the @main struct in UESwift.swift becomes the new main(). Plus, UIApplicationSceneManifest is auto-generation for Info.plist
- L40 _public member_ `bool bCreateBridgingHeader;` — `UPROPERTY(config, EditAnywhere, Category = Build, Meta = (DisplayName = "Create Swift/ObjC Bridging Headers", ConfigRestartRequired = true))` — If checked, the Swift/ObjC bridging headers will be created.
- L44 _public member_ `int ImmersiveStyle = 0;` — `UPROPERTY(config, EditAnywhere, Category = ImmersiveSpace, Meta = (DisplayName = "ImmersiveStyle"))` — Specify the immersiveStyle we will launch into: 0 = .full, 1 = .mixed.
- L48 _public member_ `int UpperLimbVisibility = 2;` — `UPROPERTY(config, EditAnywhere, Category = ImmersiveSpace, Meta = (DisplayName = "UpperLimbVisibility"))` — Specify the upperLimbVisibility we will start with: 0 = .hidden, 1 = .visible, 2 = .automatic.

#### Free symbols / members of external scopes

- L11 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogVisionOSRuntimeSettings, Log, All);`
- L11 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogVisionOSRuntimeSettings, Log, All);`
