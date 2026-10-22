# Plugins / MonoVideoIngestDevice

- module root: `Plugins/VirtualProduction/CaptureManager/CaptureManagerDevices/Source/MonoVideoIngestDevice`
- headers: 1; symbols: 21
- symbol kinds: class=2, function=1, member=3, prototype=15
- PrivateDependencyModuleNames: CaptureManagerMediaRW, CaptureManagerSettings, CaptureManagerTakeMetadata, CaptureMetadataExtraction, CoreUObject, Engine, IngestLiveLinkDevice, Json, LiveLinkCapabilities, LiveLinkDevice, LiveLinkHub, LiveLinkHubCaptureMessaging, Media, Slate, SlateCore, ToolWidgets, UnrealEd, VideoLiveLinkDeviceCommon
- PublicDependencyModuleNames: CaptureUtils, Core

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerDevices/Source/MonoVideoIngestDevice/Private/MonoVideoIngestDevice.h` (Private)


#### class `UMonoVideoIngestDeviceSettings`  
`class UMonoVideoIngestDeviceSettings : public ULiveLinkDeviceSettings`  
_L21-59_
- reflection: `UCLASS(BlueprintType)`
- inherits: `ULiveLinkDeviceSettings`
- L26 _public function_ `UMonoVideoIngestDeviceSettings()`
- L34 _public member_ `FDirectoryPath TakeDirectory;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mono Video Ingest")` — Path to a directory containing the take(s) data
- L58 _public member_ `FTakeDiscoveryExpression VideoDiscoveryExpression;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mono Video Ingest")` — Format of the file name that the device expects Available expressions: * <Slate> - slate name * <Name> - identifier for the camera * <Take> - take number * <Any> - any string * <Auto> - used alone to automatically figure out takes based on directory structure Available delimiters: '_', '-', '.' Examples: Considering input video MyTakeFolder/MySlate_MyName_SomeString-005.mov Video File Name Pattern <Auto> - will set Slate to the video filename “MySlate_MyName_SomeString_005” (dash converted to underline), Name will be set to just "video" and Take will be set to 1 by default. Video File Name Pattern <Slate>_<Name>_<Any>-<Take> - will extract Slate as “MySlate”, Name as “MyName” and Take as 5. <Any> ensures that the “SomeString” part of the filename is ignored. In both cases, extension '.mov' is stripped out. Note: when not using <Auto> expression, then both <Slate> and <Name> must be present in the pattern.

#### class `UMonoVideoIngestDevice`  
`class UMonoVideoIngestDevice final : public UBaseIngestLiveLinkDevice , public ILiveLinkDeviceCapability_Connection`  
_L63-102_
- reflection: `UCLASS(BlueprintType, meta = (DisplayName = "Mono Video Ingest", ToolTip = "Ingest video files as mono takes"))`
- inherits: `UBaseIngestLiveLinkDevice,ILiveLinkDeviceCapability_Connection`
- L71 _public prototype_ `const UMonoVideoIngestDeviceSettings* GetSettings() const;` — `UFUNCTION(BlueprintCallable, Category = "GenericArchiveDeviceSettings")`
- L74 _public prototype_ `virtual TSubclassOf<ULiveLinkDeviceSettings> GetSettingsClass() const override;`
- L75 _public prototype_ `virtual EDeviceHealth GetDeviceHealth() const override;`
- L76 _public prototype_ `virtual FText GetHealthText() const override;`
- L78 _public prototype_ `virtual void OnSettingChanged(const FPropertyChangedEvent& InPropertyChangedEvent) override;`
- L82 _private prototype_ `virtual FString GetFullTakePath(UE::CaptureManager::FTakeId InTakeId) const override;`
- L85 _private prototype_ `virtual void RunConvertAndUploadTake(const UIngestCapability_ProcessHandle* InProcessHandle, const UIngestCapability_Options* InIngestOptions) override;`
- L86 _private prototype_ `virtual void RunUpdateTakeList(UIngestCapability_UpdateTakeListCallback* InCallback) override;`
- L90 _private prototype_ `virtual ELiveLinkDeviceConnectionStatus GetConnectionStatus_Implementation() const override;`
- L91 _private prototype_ `virtual FString GetHardwareId_Implementation() const override;`
- L92 _private prototype_ `virtual bool SetHardwareId_Implementation(const FString& HardwareID) override;`
- L93 _private prototype_ `virtual bool Connect_Implementation() override;`
- L94 _private prototype_ `virtual bool Disconnect_Implementation() override;`
- L97 _private prototype_ `bool IsVideoFile(const FString& InFileNameWithExtension);`
- L99 _private prototype_ `TOptional<FTakeMetadata> ReadTake(const FString& InCurrentVideoFile) const;`
- L101 _private member_ `TMap<int32, FString> FullTakePaths;`
