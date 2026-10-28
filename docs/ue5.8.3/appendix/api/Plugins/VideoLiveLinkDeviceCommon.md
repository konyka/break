# Plugins / VideoLiveLinkDeviceCommon

- module root: `Plugins/VirtualProduction/CaptureManager/CaptureManagerDevices/Source/VideoLiveLinkDeviceCommon`
- headers: 3; symbols: 45
- symbol kinds: class=3, function=1, macro=1, member=13, namespace=2, prototype=23, struct=1, typedef=1
- PrivateDependencyModuleNames: CaptureManagerMediaRW, CaptureManagerSettings, CaptureUtils, CoreUObject, Engine, Slate, SlateCore, UnrealEd
- PublicDependencyModuleNames: CaptureManagerTakeMetadata, Core, ImageCore

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerDevices/Source/VideoLiveLinkDeviceCommon/Public/Customizations/TakeDiscoveryExpressionCustomization.h` (Public)


#### struct `FTakeDiscoveryExpression`  
`struct FTakeDiscoveryExpression`  
_L12-24_
- reflection: `USTRUCT(BlueprintType)`
- L17 _public member_ `FString Value;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Discovert Expression Value")`
- L19 _public function_ `FTakeDiscoveryExpression operator=(const FString& InValue)`

#### class `FTakeDiscoveryExpressionCustomization`  
`class FTakeDiscoveryExpressionCustomization : public IPropertyTypeCustomization`  
_L26-42_
- inherits: `IPropertyTypeCustomization`
- L29 _public prototype_ `FTakeDiscoveryExpressionCustomization();`
- L31 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L32 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> PropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L35 _private prototype_ `FText OnGetExpressionValue() const;`
- L36 _private prototype_ `bool OnExpressionValidate(const FText& InText, FText& OutErrorText);`
- L37 _private prototype_ `void OnExpressionCommited(const FText& InText, ETextCommit::Type CommitInfo);`
- L38 _private prototype_ `bool IsReadOnly() const;`
- L39 _private prototype_ `TOptional<FText> ValidateExpression(const FString& InTokens);`
- L41 _private member_ `TSharedPtr<IPropertyHandle> ExpressionProperty;`

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerDevices/Source/VideoLiveLinkDeviceCommon/Public/Utils/TakeDiscoveryExpressionParser.h` (Public)


#### class `FTakeDiscoveryExpressionParser`  
`class FTakeDiscoveryExpressionParser`  
_L7-41_
- L11 _public member_ `static const FString SlateNameToken;`
- L12 _public member_ `static const FString TakeNumberToken;`
- L13 _public member_ `static const FString NameToken;`
- L14 _public member_ `static const FString AnyToken;`
- L16 _public prototype_ `FTakeDiscoveryExpressionParser(const FString& InFormat, const FString& InFormattedValue, const TArray<FString::ElementType>& InDelimiters);`
- L18 _public prototype_ `bool Parse();`
- L20 _public prototype_ `FString GetSlateName() const;`
- L21 _public prototype_ `int32 GetTakeNumber() const;`
- L22 _public prototype_ `FString GetName() const;`
- L26 _private typedef_ `using FComponentValueMap = TMap<FString, FString>;`
- L28 _private prototype_ `TOptional<FComponentValueMap> ParseWithDelimiters(TArray<FString::ElementType> InDelimiters) const;`
- L29 _private prototype_ `TOptional<FComponentValueMap> ParseWithoutDelimiters() const;`
- L30 _private prototype_ `TArray<FString> ParseWithDelimiters(FString InString, const TArray<FString::ElementType>& InDelimiters, int32 InDelimiterIndex = 0) const;`
- L32 _private prototype_ `bool DetermineValues(FComponentValueMap InComponentValueMap);`
- L34 _private member_ `FString Format;`
- L35 _private member_ `FString FormattedValue;`
- L36 _private member_ `const TArray<FString::ElementType>& AllowedDelimiters;`
- L38 _private member_ `FString SlateName;`
- L39 _private member_ `int32 TakeNumber = INDEX_NONE;`
- L40 _private member_ `FString Name;`

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerDevices/Source/VideoLiveLinkDeviceCommon/Public/Utils/VideoDeviceThumbnailExtractor.h` (Public)


#### class `UE::CaptureManager::FVideoDeviceThumbnailExtractor`  
`class FVideoDeviceThumbnailExtractor`  
_L16-34_
- L20 _public prototype_ `UE_INTERNAL FVideoDeviceThumbnailExtractor();`
- L22 _public prototype_ `UE_INTERNAL TOptional<FTakeThumbnailData::FRawImage> ExtractThumbnail(const FString& InCurrentFile);`
- L26 _private prototype_ `TArray<FColor> ConvertThumbnailFromSample(const struct FMediaTextureSample* InSample);`
- L28 _private member_ `static constexpr int32 ThirdPartyEncoderThumbnailWidth = 256;`
- L30 _private prototype_ `TArray<FColor> ObtainThumbnailFromThirdPartyEncoder(const FString& InEncoderPath, const FString& InCurrentFile);`
- L32 _private prototype_ `TArray<uint8> RunProcess(const FString& InProcessName, const FString& InProcessArgs);`
- L33 _private prototype_ `TArray<uint8> ReadFromPipe(void* InPipe);`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API VIDEOLIVELINKDEVICECOMMON_API`
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace CaptureManager` (scope `UE`)
