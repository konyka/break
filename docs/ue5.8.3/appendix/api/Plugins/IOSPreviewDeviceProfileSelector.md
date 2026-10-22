# Plugins / IOSPreviewDeviceProfileSelector

- module root: `Plugins/Runtime/IOSDeviceProfileSelector/Source/IOSPreviewDeviceProfileSelector`
- headers: 1; symbols: 15
- symbol kinds: class=1, function=2, member=1, prototype=11
- PrivateDependencyModuleNames: Core, CoreUObject, Engine, IOSTargetPlatformControls, Json, JsonUtilities, PIEPreviewDeviceSpecification, Projects
- PublicDependencyModuleNames: Core, RHI
- PublicIncludePathModuleNames: IOSTargetPlatformControls

### `Plugins/Runtime/IOSDeviceProfileSelector/Source/IOSPreviewDeviceProfileSelector/Private/IOSPreviewDeviceProfileSelectorModule.h` (Private)


#### class `FIOSPreviewDeviceProfileSelectorModule`  
`class FIOSPreviewDeviceProfileSelectorModule : public IDeviceProfileSelectorModule`  
_L11-46_
- inherits: `IDeviceProfileSelectorModule`
- desc: Implements the IOS Device Profile Selector module.
- L17 _public prototype_ `virtual const FString GetDeviceProfileName() override;`
- L18 _public prototype_ `virtual const FString GetRuntimeDeviceProfileName() override;`
- L20 _public prototype_ `virtual bool CanExportDeviceParametersToJson() override;`
- L21 _public prototype_ `virtual bool IsJsonCompatible(const FString& JsonLocation) override;`
- L22 _public prototype_ `virtual void ExportDeviceParametersToJson(FString& FolderLocation, TArray<FString>& OutExportedFiles) override;`
- L23 _public prototype_ `virtual void GetDeviceParametersFromJson(FString& JsonLocation, TMap<FString, FString>& OutDeviceParameters) override;`
- L24 _public function_ `virtual bool CanGetDeviceParametersFromJson() override`
- L25 _public prototype_ `virtual const EShaderPlatform GetPreviewShaderPlatform() override;`
- L26 _public prototype_ `virtual void SetSelectorProperties(const TMap<FString, FString>& InSelectorProperties) override;`
- L27 _public prototype_ `virtual bool GetSelectorPropertyValue(const FName& PropertyType, FString& PropertyValueOUT) override;`
- L33 _public prototype_ `virtual void StartupModule() override;`
- L34 _public prototype_ `virtual void ShutdownModule() override;`
- L41 _public function_ `virtual ~FIOSPreviewDeviceProfileSelectorModule()` — Virtual destructor.
- L45 _private member_ `TMap<FString, FString> SelectorProperties;`
