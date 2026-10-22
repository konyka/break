# Plugins / AndroidDeviceProfileSelector

- module root: `Plugins/Runtime/AndroidDeviceProfileSelector/Source/AndroidDeviceProfileSelector`
- headers: 4; symbols: 94
- symbol kinds: class=4, enum=2, enumerator=33, function=4, macro=1, member=10, namespace=1, prototype=15, struct=3, variable=21
- PrivateDependencyModuleNames: AndroidDeviceDetection, ApplicationCore, Engine, PIEPreviewDeviceSpecification, RHI
- PublicDependencyModuleNames: Core, CoreUObject, Json, JsonUtilities

### `Plugins/Runtime/AndroidDeviceProfileSelector/Source/AndroidDeviceProfileSelector/Private/AndroidDeviceProfileMatchingRules.h` (Private)


#### enum `ESourceType`  
`enum ESourceType : int`  
_L8-28_
- reflection: `UENUM()`
- L10 _public enumerator_ `SRC_PreviousRegexMatch`
- L11 _public enumerator_ `SRC_GpuFamily`
- L12 _public enumerator_ `SRC_GlVersion`
- L13 _public enumerator_ `SRC_AndroidVersion`
- L14 _public enumerator_ `SRC_DeviceMake`
- L15 _public enumerator_ `SRC_DeviceModel`
- L16 _public enumerator_ `SRC_DeviceBuildNumber`
- L17 _public enumerator_ `SRC_VulkanVersion`
- L18 _public enumerator_ `SRC_UsingHoudini`
- L19 _public enumerator_ `SRC_VulkanAvailable`
- L20 _public enumerator_ `SRC_CommandLine`
- L21 _public enumerator_ `SRC_Hardware`
- L22 _public enumerator_ `SRC_Chipset`
- L23 _public enumerator_ `SRC_ConfigRuleVar`
- L24 _public enumerator_ `SRC_HMDSystemName`
- L25 _public enumerator_ `SRC_SM5Available`
- L26 _public enumerator_ `SRC_VKQuality`
- L27 _public enumerator_ `SRC_MAX`

#### enum `ECompareType`  
`enum ECompareType : int`  
_L31-48_
- reflection: `UENUM()`
- L33 _public enumerator_ `CMP_Equal`
- L34 _public enumerator_ `CMP_Less`
- L35 _public enumerator_ `CMP_LessEqual`
- L36 _public enumerator_ `CMP_Greater`
- L37 _public enumerator_ `CMP_GreaterEqual`
- L38 _public enumerator_ `CMP_NotEqual`
- L39 _public enumerator_ `CMP_Regex`
- L40 _public enumerator_ `CMP_EqualIgnore`
- L41 _public enumerator_ `CMP_LessIgnore`
- L42 _public enumerator_ `CMP_LessEqualIgnore`
- L43 _public enumerator_ `CMP_GreaterIgnore`
- L44 _public enumerator_ `CMP_GreaterEqualIgnore`
- L45 _public enumerator_ `CMP_NotEqualIgnore`
- L46 _public enumerator_ `CMP_Hash`
- L47 _public enumerator_ `CMP_MAX`

#### struct `FProfileMatchItem`  
`struct FProfileMatchItem`  
_L51-63_
- reflection: `USTRUCT()`
- L56 _public member_ `TEnumAsByte<ESourceType> SourceType=ESourceType::SRC_MAX;` — `UPROPERTY()`
- L59 _public member_ `TEnumAsByte<ECompareType> CompareType=ECompareType::CMP_MAX;` — `UPROPERTY()`
- L62 _public member_ `FString MatchString;` — `UPROPERTY()`

#### struct `FProfileMatch`  
`struct FProfileMatch`  
_L66-75_
- reflection: `USTRUCT()`
- L71 _public member_ `FString Profile;` — `UPROPERTY()`
- L74 _public member_ `TArray<FProfileMatchItem> Match;` — `UPROPERTY()`

#### class `UAndroidDeviceProfileMatchingRules`  
`class UAndroidDeviceProfileMatchingRules : public UObject`  
_L78-93_
- reflection: `UCLASS(config = DeviceProfiles)`
- inherits: `UObject`
- L85 _public function_ `virtual const TCHAR* GetConfigOverridePlatform() const override` — Use Android .ini files in the editor
- L92 _public member_ `TArray<FProfileMatch> MatchProfile;` — `UPROPERTY(EditAnywhere, config, Category = "Matching Rules")` — Array of rules to match

### `Plugins/Runtime/AndroidDeviceProfileSelector/Source/AndroidDeviceProfileSelector/Private/AndroidDeviceProfileSelectorModule.h` (Private)


#### class `FAndroidDeviceProfileSelectorModule`  
`class FAndroidDeviceProfileSelectorModule : public IDeviceProfileSelectorModule`  
_L11-41_
- inherits: `IDeviceProfileSelectorModule`
- desc: Implements the Android Device Profile Selector module. Used to emulate an android device's IDeviceProfileSelectorModule behaviour.
- L17 _public prototype_ `virtual const FString GetDeviceProfileName() override;`
- L18 _public prototype_ `virtual const FString GetRuntimeDeviceProfileName() override;`
- L20 _public prototype_ `virtual void ExportDeviceParametersToJson(FString& FolderLocation, TArray<FString>& OutExportedFiles) override;`
- L21 _public prototype_ `virtual bool CanExportDeviceParametersToJson() override;`
- L22 _public prototype_ `virtual bool IsJsonCompatible(const FString& JsonLocation) override;`
- L23 _public prototype_ `virtual void GetDeviceParametersFromJson(FString& JsonLocation, TMap<FString, FString>& OutDeviceParameters) override;`
- L24 _public function_ `virtual bool CanGetDeviceParametersFromJson() override`
- L25 _public prototype_ `virtual const EShaderPlatform GetPreviewShaderPlatform() override;`
- L28 _public prototype_ `virtual void SetSelectorProperties(const TMap<FString, FString>& SelectorProperties) override;` — Set the device parameters this selector will use.
- L29 _public prototype_ `virtual bool GetSelectorPropertyValue(const FName& PropertyType, FString& PropertyValueOUT) override;`
- L33 _public prototype_ `virtual void StartupModule() override;`
- L34 _public prototype_ `virtual void ShutdownModule() override;`
- L40 _public prototype_ `virtual ~FAndroidDeviceProfileSelectorModule() = default;` — Virtual destructor.

### `Plugins/Runtime/AndroidDeviceProfileSelector/Source/AndroidDeviceProfileSelector/Public/AndroidDeviceProfileSelector.h` (Public)


#### class `FAndroidDeviceProfileSelector`  
`class FAndroidDeviceProfileSelector`  
_L35-46_
- L38 _private member_ `static TMap<FString, FString> SelectorProperties;` — Container of various device properties used for device profile matching.
- L39 _private prototype_ `static void VerifySelectorParams();`
- L42 _public prototype_ `static FString FindMatchingProfile(const FString& FallbackProfileName);`
- L43 _public prototype_ `static int32 GetNumProfiles();`
- L44 _public function_ `static void SetSelectorProperties(const TMap<FString, FString>& Params)`
- L45 _public function_ `static const TMap<FString, FString>& GetSelectorProperties()`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API ANDROIDDEVICEPROFILESELECTOR_API`
- L10 _namespace_ `namespace FAndroidProfileSelectorSourceProperties`
- L12 _variable_ `static FStringView SRC_GPUFamily(TEXT("SRC_` (scope `FAndroidProfileSelectorSourceProperties`)
- L13 _variable_ `static FStringView SRC_GLVersion(TEXT("SRC_` (scope `FAndroidProfileSelectorSourceProperties`)
- L14 _variable_ `static FStringView SRC_VulkanAvailable(TEXT("SRC_` (scope `FAndroidProfileSelectorSourceProperties`)
- L15 _variable_ `static FStringView SRC_VulkanVersion(TEXT("SRC_` (scope `FAndroidProfileSelectorSourceProperties`)
- L16 _variable_ `static FStringView SRC_AndroidVersion(TEXT("SRC_` (scope `FAndroidProfileSelectorSourceProperties`)
- L17 _variable_ `static FStringView SRC_DeviceMake(TEXT("SRC_` (scope `FAndroidProfileSelectorSourceProperties`)
- L18 _variable_ `static FStringView SRC_DeviceModel(TEXT("SRC_` (scope `FAndroidProfileSelectorSourceProperties`)
- L19 _variable_ `static FStringView SRC_DeviceBuildNumber(TEXT("SRC_` (scope `FAndroidProfileSelectorSourceProperties`)
- L20 _variable_ `static FStringView SRC_UsingHoudini(TEXT("SRC_` (scope `FAndroidProfileSelectorSourceProperties`)
- L21 _variable_ `static FStringView SRC_Hardware(TEXT("SRC_` (scope `FAndroidProfileSelectorSourceProperties`)
- L22 _variable_ `static FStringView SRC_Chipset(TEXT("SRC_` (scope `FAndroidProfileSelectorSourceProperties`)
- L23 _variable_ `static FStringView SRC_HMDSystemName(TEXT("SRC_` (scope `FAndroidProfileSelectorSourceProperties`)
- L24 _variable_ `static FStringView SRC_TotalPhysicalGB(TEXT("SRC_` (scope `FAndroidProfileSelectorSourceProperties`)
- L25 _variable_ `static FStringView SRC_SM5Available(TEXT("SRC_` (scope `FAndroidProfileSelectorSourceProperties`)
- L26 _variable_ `static FStringView SRC_ResolutionX(TEXT("SRC_` (scope `FAndroidProfileSelectorSourceProperties`)
- L27 _variable_ `static FStringView SRC_ResolutionY(TEXT("SRC_` (scope `FAndroidProfileSelectorSourceProperties`)
- L28 _variable_ `static FStringView SRC_InsetsLeft(TEXT("SRC_` (scope `FAndroidProfileSelectorSourceProperties`)
- L29 _variable_ `static FStringView SRC_InsetsTop(TEXT("SRC_` (scope `FAndroidProfileSelectorSourceProperties`)
- L30 _variable_ `static FStringView SRC_InsetsRight(TEXT("SRC_` (scope `FAndroidProfileSelectorSourceProperties`)
- L31 _variable_ `static FStringView SRC_InsetsBottom(TEXT("SRC_` (scope `FAndroidProfileSelectorSourceProperties`)
- L32 _variable_ `static FStringView SRC_VKQuality(TEXT("SRC_` (scope `FAndroidProfileSelectorSourceProperties`)

### `Plugins/Runtime/AndroidDeviceProfileSelector/Source/AndroidDeviceProfileSelector/Public/AndroidJavaSurfaceViewDevices.h` (Public)


#### struct `FJavaSurfaceViewDevice`  
`struct FJavaSurfaceViewDevice`  
_L8-17_
- reflection: `USTRUCT()`
- L13 _public member_ `FString Manufacturer;` — `UPROPERTY()`
- L16 _public member_ `FString Model;` — `UPROPERTY()`

#### class `UAndroidJavaSurfaceViewDevices`  
`class UAndroidJavaSurfaceViewDevices : public UObject`  
_L20-29_
- reflection: `UCLASS(config = DeviceProfiles)`
- inherits: `UObject`
- L28 _public member_ `TArray<FJavaSurfaceViewDevice> SurfaceViewDevices;` — `UPROPERTY(EditAnywhere, config, Category = "Matching Rules")` — Array of devices that require the java view scaling workaround
