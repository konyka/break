# Plugins / AppleImageUtils

- module root: `Plugins/Runtime/AppleImageUtils/Source/AppleImageUtils`
- headers: 4; symbols: 92
- symbol kinds: class=7, delegate=1, enum=2, enumerator=13, function=18, macro=15, member=12, prototype=23, struct=1
- DynamicallyLoadedModuleNames: 
- PrivateDependencyModuleNames: CoreUObject
- PublicDependencyModuleNames: Core, Engine

### `Plugins/Runtime/AppleImageUtils/Source/AppleImageUtils/Public/AppleImageUtilsAvailability.h` (Public)


#### class `FAppleImageUtilsAvailability`  
`class FAppleImageUtilsAvailability`  
_L78-134_
- L81 _public function_ `static bool SupportsImageUtils10()`
- L99 _public function_ `static bool SupportsImageUtils20()`
- L117 _public function_ `static bool SupportsImageUtils21()`

#### Free symbols / members of external scopes

- L6 _macro_ `#define PLATFORM_IOS 0`
- L10 _macro_ `#define PLATFORM_TVOS 0`
- L14 _macro_ `#define PLATFORM_MAC 0`
- L21 _macro_ `#define SUPPORTS_IMAGE_UTILS_1_0 1`
- L22 _macro_ `#define RT_CHECK_IMAGE_UTILS_1_0 @available(iOS 10.0, *)`
- L24 _macro_ `#define SUPPORTS_IMAGE_UTILS_1_0 0`
- L29 _macro_ `#define SUPPORTS_IMAGE_UTILS_2_0 1`
- L30 _macro_ `#define RT_CHECK_IMAGE_UTILS_2_0 @available(iOS 11.0, *)`
- L32 _macro_ `#define SUPPORTS_IMAGE_UTILS_2_0 0`
- L37 _macro_ `#define SUPPORTS_IMAGE_UTILS_2_1 1`
- L38 _macro_ `#define RT_CHECK_IMAGE_UTILS_2_1 @available(iOS 11.0, *)`
- L40 _macro_ `#define SUPPORTS_IMAGE_UTILS_2_1 0`
- L48 _macro_ `#define RT_CHECK_IMAGE_UTILS_1_0 @available(macOS 10.12, *)`
- L56 _macro_ `#define RT_CHECK_IMAGE_UTILS_2_0 @available(macOS 10.13, *)`
- L65 _macro_ `#define RT_CHECK_IMAGE_UTILS_2_1 @available(macOS 10.13.4, *)`

### `Plugins/Runtime/AppleImageUtils/Source/AppleImageUtils/Public/AppleImageUtilsBlueprintProxy.h` (Public)


#### struct `FAppleImageUtilsImageConversionResult`  
`struct FAppleImageUtilsImageConversionResult`  
_L16-25_
- reflection: `USTRUCT(BlueprintType)`
- L21 _public member_ `FString Error;` — `UPROPERTY(BlueprintReadOnly, Category="Image Conversion")`
- L24 _public member_ `TArray<uint8> ImageData;` — `UPROPERTY(BlueprintReadOnly, Category="Image Conversion")`

#### class `UAppleImageUtilsBaseAsyncTaskBlueprintProxy`  
`class UAppleImageUtilsBaseAsyncTaskBlueprintProxy : public UObject, public FTickableGameObject`  
_L30-110_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject,FTickableGameObject`
- L38 _public member_ `FAppleImageConversionDelegate OnSuccess;` — `UPROPERTY(BlueprintAssignable)`
- L41 _public member_ `FAppleImageConversionDelegate OnFailure;` — `UPROPERTY(BlueprintAssignable)`
- L54 _public prototype_ `static UAppleImageUtilsBaseAsyncTaskBlueprintProxy* CreateProxyObjectForConvertToJPEG(UTexture* SourceImage, int32 Quality = 85, bool bWantColor = true, bool bUseGpu = true, float Scale = 1.f, ETextureRotationDirection Rotate = ETextureRotationDirection::None);` — `UFUNCTION(BlueprintCallable, Meta=(BlueprintInternalUseOnly="true", DisplayName="Convert To JPEG"), Category="Image Conversion")` — Converts a image to an array of JPEG data in a background task @param SourceImage the image to compress @param Quality the quality level to compress to @param bWantColor whether the JPEG is color (true) or monochrome (false) @param bUseGpu whether to use the GPU (true) or the CPU (false) to compress @param Scale whether to scale the image before conversion, defaults to no scaling @param Rotate a direction to rotate the image in during conversion, defaults to none
- L67 _public prototype_ `static UAppleImageUtilsBaseAsyncTaskBlueprintProxy* CreateProxyObjectForConvertToHEIF(UTexture* SourceImage, int32 Quality = 85, bool bWantColor = true, bool bUseGpu = true, float Scale = 1.f, ETextureRotationDirection Rotate = ETextureRotationDirection::None);` — `UFUNCTION(BlueprintCallable, Meta=(BlueprintInternalUseOnly="true", DisplayName="Convert To HEIF"), Category="Image Conversion")` — Converts a image to an array of HEIF data in a background task @param SourceImage the image to compress @param Quality the quality level to compress to @param bWantColor whether the HEIF is color (true) or monochrome (false) @param bUseGpu whether to use the GPU (true) or the CPU (false) to compress @param Scale whether to scale the image before conversion, defaults to no scaling @param Rotate a direction to rotate the image in during conversion, defaults to none
- L80 _public prototype_ `static UAppleImageUtilsBaseAsyncTaskBlueprintProxy* CreateProxyObjectForConvertToTIFF(UTexture* SourceImage, bool bWantColor = true, bool bUseGpu = true, float Scale = 1.f, ETextureRotationDirection Rotate = ETextureRotationDirection::None);` — `UFUNCTION(BlueprintCallable, Meta=(BlueprintInternalUseOnly="true", DisplayName="Convert To TIFF"), Category="Image Conversion")` — Converts a image to an array of TIFF data in a background task @param SourceImage the image to compress @param Quality the quality level to compress to @param bWantColor whether the TIFF is color (true) or monochrome (false) @param bUseGpu whether to use the GPU (true) or the CPU (false) to compress @param Scale whether to scale the image before conversion, defaults to no scaling @param Rotate a direction to rotate the image in during conversion, defaults to none
- L93 _public prototype_ `static UAppleImageUtilsBaseAsyncTaskBlueprintProxy* CreateProxyObjectForConvertToPNG(UTexture* SourceImage, bool bWantColor = true, bool bUseGpu = true, float Scale = 1.f, ETextureRotationDirection Rotate = ETextureRotationDirection::None);` — `UFUNCTION(BlueprintCallable, Meta=(BlueprintInternalUseOnly="true", DisplayName="Convert To PNG"), Category="Image Conversion")` — Converts a image to an array of TIFF data in a background task @param SourceImage the image to compress @param Quality the quality level to compress to @param bWantColor whether the PNG is color (true) or monochrome (false) @param bUseGpu whether to use the GPU (true) or the CPU (false) to compress @param Scale whether to scale the image before conversion, defaults to no scaling @param Rotate a direction to rotate the image in during conversion, defaults to none
- L96 _public prototype_ `virtual void Tick(float DeltaTime) override;`
- L97 _public function_ `virtual bool IsTickable() const override`
- L98 _public function_ `virtual TStatId GetStatId() const override`
- L102 _public member_ `TSharedPtr<FAppleImageUtilsConversionTaskBase, ESPMode::ThreadSafe> ConversionTask;` — The async task to check during Tick()
- L105 _public member_ `FAppleImageUtilsImageConversionResult ConversionResult;` — `UPROPERTY(BlueprintReadOnly, Category="Image Conversion")`
- L109 _private member_ `bool bShouldTick;` — True until the async task completes, then false

#### Free symbols / members of external scopes

- L27 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAppleImageConversionDelegate, const FAppleImageUtilsImageConversionResult&, ConversionResult);`
- L27 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAppleImageConversionDelegate, const FAppleImageUtilsImageConversionResult&, ConversionResult);`

### `Plugins/Runtime/AppleImageUtils/Source/AppleImageUtils/Public/AppleImageUtilsTypes.h` (Public)


#### enum `ETextureRotationDirection`  
`enum class ETextureRotationDirection : uint8`  
_L16-26_
- reflection: `UENUM(BlueprintType, Category="AppleImageUtils", meta=(Experimental))`
- L18 _public enumerator_ `None`
- L19 _public enumerator_ `Left`
- L20 _public enumerator_ `Right`
- L21 _public enumerator_ `Down`
- L22 _public enumerator_ `LeftMirrored`
- L23 _public enumerator_ `RightMirrored`
- L24 _public enumerator_ `DownMirrored`
- L25 _public enumerator_ `UpMirrored`

#### enum `EAppleTextureType`  
`enum class EAppleTextureType : uint8`  
_L29-36_
- reflection: `UENUM(BlueprintType, Category="AppleImageUtils", meta=(Experimental))`
- L31 _public enumerator_ `Unknown`
- L32 _public enumerator_ `Image`
- L33 _public enumerator_ `PixelBuffer`
- L34 _public enumerator_ `Surface`
- L35 _public enumerator_ `MetalTexture`

#### class `UAppleImageInterface`  
`class UAppleImageInterface : public UInterface`  
_L40-43_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UInterface`
- desc: Dummy class needed to support Cast<IAppleImageInterface>(Object).

#### class `IAppleImageInterface`  
`class IAppleImageInterface`  
_L48-67_
- desc: Base class for accessing the raw Apple image data
- L54 _public prototype_ `virtual EAppleTextureType GetTextureType() const = 0;` — @return the type of image held by the implementing object
- L58 _public function_ `virtual CIImage* GetImage() const` — @return the CIImage held by the implementing object
- L60 _public function_ `virtual CVPixelBufferRef GetPixelBuffer() const` — @return the CVPixelBuffer held by the implementing object
- L62 _public function_ `virtual IOSurfaceRef GetSurface() const` — @return the IOSurface held by the implementing object
- L65 _public function_ `virtual id<MTLTexture> GetMetalTexture() const` — @return the MTLTextureid<MTL held by the implementing object

### `Plugins/Runtime/AppleImageUtils/Source/AppleImageUtils/Public/IAppleImageUtilsPlugin.h` (Public)


#### class `IAppleImageUtilsConversionTask`  
`class IAppleImageUtilsConversionTask`  
_L22-37_
- desc: Interface to access the async compression request
- L26 _public prototype_ `virtual bool HadError() const = 0;` — @return whether the task succeeded or not
- L28 _public prototype_ `virtual FString GetErrorReason() const = 0;` — @return information about the error if there was one
- L30 _public prototype_ `virtual bool IsDone() const = 0;` — @return whether the task has completed or not
- L32 _public prototype_ `virtual float GetElapsedTime() const = 0;` — @return how long it took this task to complete
- L34 _public prototype_ `virtual TArray<uint8> GetData() = 0;` — @return the data once the task has completed or empty array if still in progress. NOTE: this should use MoveTemp() to avoid duplication so call once :)
- L36 _public prototype_ `virtual FIntPoint GetConvertedImageSize() const = 0;` — @return the size of the converted image

#### class `FAppleImageUtilsConversionTaskBase`  
`class FAppleImageUtilsConversionTaskBase : public IAppleImageUtilsConversionTask`  
_L42-62_
- inherits: `IAppleImageUtilsConversionTask`
- desc: Base class for implementing IAppleImageUtilsCompressionTasks
- L46 _protected function_ `FAppleImageUtilsConversionTaskBase()`
- L47 _protected prototype_ `virtual ~FAppleImageUtilsConversionTaskBase() = default;`
- L50 _public function_ `virtual bool IsDone() const override`
- L51 _public function_ `virtual bool HadError() const override`
- L52 _public function_ `virtual FString GetErrorReason() const override`
- L53 _public function_ `virtual float GetElapsedTime() const override`
- L54 _public function_ `virtual FIntPoint GetConvertedImageSize() const override`
- L57 _protected member_ `FThreadSafeBool bIsDone;`
- L58 _protected member_ `FThreadSafeBool bHadError;`
- L59 _protected member_ `double StartTime = 0.f;`
- L60 _protected member_ `double EndTime = 0.f;`
- L61 _protected member_ `FString Error;`

#### class `IAppleImageUtilsPlugin`  
`class IAppleImageUtilsPlugin : public IModuleInterface`  
_L64-223_
- inherits: `IModuleInterface`
- L75 _public function_ `static inline IAppleImageUtilsPlugin& Load()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L86 _public function_ `static inline IAppleImageUtilsPlugin& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance
- L96 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use
- L113 _public prototype_ `virtual TSharedPtr<FAppleImageUtilsConversionTaskBase, ESPMode::ThreadSafe> ConvertToJPEG(UTexture* SourceImage, int32 Quality = 85, bool bWantColor = true, bool bUseGpu = true, float Scale = 1.f, ETextureRotationDirection Rotate = ETextureRotationDirection::None) = 0;` — Converts a image to an array of JPEG data in a background task @param SourceImage the image to compress (NOTE: must support UAppleImageInterface) @param Quality the quality level to compress to @param bWantColor whether the JPEG is color (true) or monochrome (false) @param bUseGpu whether to use the GPU (true) or the CPU (false) to compress @param Scale whether to scale the image before converting, defaults to no scale operation @param Rotate a direction to rotate the image in during conversion, defaults to none @return the async task that is doing the conversion
- L127 _public prototype_ `virtual TSharedPtr<FAppleImageUtilsConversionTaskBase, ESPMode::ThreadSafe> ConvertToHEIF(UTexture* SourceImage, int32 Quality = 85, bool bWantColor = true, bool bUseGpu = true, float Scale = 1.f, ETextureRotationDirection Rotate = ETextureRotationDirection::None) = 0;` — Converts a image to an array of HEIF data in a background task @param SourceImage the image to compress (NOTE: must support UAppleImageInterface) @param Quality the quality level to compress to @param bWantColor whether the HEIF is color (true) or monochrome (false) @param bUseGpu whether to use the GPU (true) or the CPU (false) to compress @param Scale whether to scale the image before converting, defaults to no scale operation @param Rotate a direction to rotate the image in during conversion, defaults to none @return the async task that is doing the conversion
- L141 _public prototype_ `virtual TSharedPtr<FAppleImageUtilsConversionTaskBase, ESPMode::ThreadSafe> ConvertToPNG(UTexture* SourceImage, bool bWantColor = true, bool bUseGpu = true, float Scale = 1.f, ETextureRotationDirection Rotate = ETextureRotationDirection::None) = 0;` — Converts a image to an array of PNG data in a background task @param SourceImage the image to compress (NOTE: must support UAppleImageInterface) @param Quality the quality level to compress to @param bWantColor whether the PNG is color (true) or monochrome (false) @param bUseGpu whether to use the GPU (true) or the CPU (false) to compress @param Scale whether to scale the image before converting, defaults to no scale operation @param Rotate a direction to rotate the image in during conversion, defaults to none @return the async task that is doing the conversion
- L154 _public prototype_ `virtual TSharedPtr<FAppleImageUtilsConversionTaskBase, ESPMode::ThreadSafe> ConvertToTIFF(UTexture* SourceImage, bool bWantColor = true, bool bUseGpu = true, float Scale = 1.f, ETextureRotationDirection Rotate = ETextureRotationDirection::None) = 0;` — Converts a image to an array of TIFF data in a background task @param SourceImage the image to compress (NOTE: must support UAppleImageInterface) @param Quality the quality level to compress to @param bUseGpu whether to use the GPU (true) or the CPU (false) to compress @param Scale whether to scale the image before converting, defaults to no scale operation @param Rotate a direction to rotate the image in during conversion, defaults to none @return the async task that is doing the conversion
- L164 _public prototype_ `virtual CGImageRef UTexture2DToCGImage(UTexture2D* Source) = 0;` — Copies the contents of a UTexture2D to a CGImage object @param SourceImage the image to create a CGImage from @return the CGImage if conversion was possible
- L178 _public prototype_ `virtual void ConvertToJPEG(CIImage* SourceImage, TArray<uint8>& OutBytes, int32 Quality = 85, bool bWantColor = true, bool bUseGpu = true, float Scale = 1.f, ETextureRotationDirection Rotate = ETextureRotationDirection::None, FIntPoint* ConvertedImageSize = nullptr) = 0;` — Converts a image to an array of JPEG data synchronously @param SourceImage the image to compress @param OutBytes the buffer that is populated during compression @param Quality the quality level to compress to @param bWantColor whether the JPEG is color (true) or monochrome (false) @param bUseGpu whether to use the GPU (true) or the CPU (false) to compress @param Scale whether to scale the image before converting, defaults to no scale operation @param Rotate a direction to rotate the image in during conversion, defaults to none @param ConvertedImageSize if set, returns the size of the converted image
- L193 _public prototype_ `virtual void ConvertToHEIF(CIImage* SourceImage, TArray<uint8>& OutBytes, int32 Quality = 85, bool bWantColor = true, bool bUseGpu = true, float Scale = 1.f, ETextureRotationDirection Rotate = ETextureRotationDirection::None, FIntPoint* ConvertedImageSize = nullptr) = 0;` — Converts a image to an array of HEIF data synchronously @param SourceImage the image to compress @param OutBytes the buffer that is populated during compression @param Quality the quality level to compress to @param bWantColor whether the HEIF is color (true) or monochrome (false) @param bUseGpu whether to use the GPU (true) or the CPU (false) to compress @param Scale whether to scale the image before converting, defaults to no scale operation @param Rotate a direction to rotate the image in during conversion, defaults to none @param ConvertedImageSize if set, returns the size of the converted image
- L207 _public prototype_ `virtual void ConvertToPNG(CIImage* SourceImage, TArray<uint8>& OutBytes, bool bWantColor = true, bool bUseGpu = true, float Scale = 1.f, ETextureRotationDirection Rotate = ETextureRotationDirection::None, FIntPoint* ConvertedImageSize = nullptr) = 0;` — Converts a image to an array of PNG data synchronously @param SourceImage the image to compress @param OutBytes the buffer that is populated during compression @param Quality the quality level to compress to @param bWantColor whether the PNG is color (true) or monochrome (false) @param bUseGpu whether to use the GPU (true) or the CPU (false) to compress @param Scale whether to scale the image before converting, defaults to no scale operation @param Rotate a direction to rotate the image in during conversion, defaults to none @param ConvertedImageSize if set, returns the size of the converted image
- L220 _public prototype_ `virtual void ConvertToTIFF(CIImage* SourceImage, TArray<uint8>& OutBytes, bool bWantColor = true, bool bUseGpu = true, float Scale = 1.f, ETextureRotationDirection Rotate = ETextureRotationDirection::None, FIntPoint* ConvertedImageSize = nullptr) = 0;` — Converts a image to an array of TIFF data synchronously @param SourceImage the image to compress @param OutBytes the buffer that is populated during compression @param Quality the quality level to compress to @param bUseGpu whether to use the GPU (true) or the CPU (false) to compress @param Scale whether to scale the image before converting, defaults to no scale operation @param Rotate a direction to rotate the image in during conversion, defaults to none @param ConvertedImageSize if set, returns the size of the converted image
