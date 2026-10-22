# Plugins / StereoVideoIngestDevice

- module root: `Plugins/VirtualProduction/CaptureManager/CaptureManagerDevices/Source/StereoVideoIngestDevice`
- headers: 1; symbols: 46
- symbol kinds: class=2, enum=1, enumerator=3, function=1, member=11, prototype=25, struct=2, typedef=1
- PrivateDependencyModuleNames: CaptureManagerMediaRW, CaptureManagerSettings, CaptureManagerTakeMetadata, CaptureMetadataExtraction, CoreUObject, DataIngestCore, Engine, IngestLiveLinkDevice, Json, LiveLinkCapabilities, LiveLinkDevice, LiveLinkHub, LiveLinkHubCaptureMessaging, Media, Slate, SlateCore, ToolWidgets, UnrealEd, VideoLiveLinkDeviceCommon
- PublicDependencyModuleNames: CaptureUtils, Core

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerDevices/Source/StereoVideoIngestDevice/Private/StereoVideoIngestDevice.h` (Private)


#### class `UStereoVideoIngestDeviceSettings`  
`class UStereoVideoIngestDeviceSettings : public ULiveLinkDeviceSettings`  
_L21-85_
- reflection: `UCLASS(BlueprintType)`
- inherits: `ULiveLinkDeviceSettings`
- L26 _public function_ `UStereoVideoIngestDeviceSettings()`
- L36 _public member_ `FDirectoryPath TakeDirectory;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stereo Video Ingest")` — Path to a directory containing the take(s) data
- L60 _public member_ `FTakeDiscoveryExpression VideoDiscoveryExpression;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stereo Video Ingest")` — Format of the file name that the device expects Available expressions: * <Slate> - slate name * <Name> - identifier for the camera in the stereo pair * <Take> - take number * <Any> - any string * <Auto> - used alone to automatically figure out takes based on directory structure Available delimiters: '_', '-', '.', '\' Examples: Considering input video MyTakeFolder/MySlate_MyName_SomeString-005.mov Video File Name Pattern <Auto> - will set Slate to the containing folder “MyTakeFolder”, Name will be set to the video filename “MySlate_MyName_SomeString-005” and Take will be set to 1 by default Video File Name Pattern <Slate>_<Name>_<Any>-<Take> - will extract Slate as “MySlate”, Name as “MyName” and Take as 5. <Any> ensures that the “SomeString” part of the filename is ignored. In both cases, extension '.mov' is stripped out. Note: when not using <Auto> expression, then both <Slate> and <Name> must be present in the pattern
- L84 _public member_ `FTakeDiscoveryExpression AudioDiscoveryExpression;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stereo Video Ingest")` — Format of the file name that the device expects Available expressions: * <Slate> - slate name * <Name> - identifier for the camera in the stereo pair * <Take> - take number * <Any> - any string * <Auto> - used alone to automatically figure out takes based on directory structure Available delimiters: '_', '-', '.', '\' Examples: Considering input audio MyTakeFolder/MySlate_MyName_SomeString-005.wav Audio File Name Pattern <Auto> - will set Slate to the containing folder “MyTakeFolder”, Name will be set to the audio filename “MySlate_MyName_SomeString-005” and Take will be set to 1 by default Audio File Name Pattern <Slate>_<Name>_<Any>-<Take> - will extract Slate as “MySlate”, Name as “MyName” and Take as 5. <Any> ensures that the “SomeString” part of the filename is ignored. In both cases, extension '.wav' is stripped out. Note: when not using <Auto> expression, then both <Slate> and <Name> must be present in the pattern

#### class `UStereoVideoIngestDevice`  
`class UStereoVideoIngestDevice final : public UBaseIngestLiveLinkDevice , public ILiveLinkDeviceCapability_Connection`  
_L89-167_
- reflection: `UCLASS(BlueprintType, meta = (DisplayName = "Stereo Video Ingest", ToolTip = "Ingest subfolders containing pairs of video files as stereo takes"))`
- inherits: `UBaseIngestLiveLinkDevice,ILiveLinkDeviceCapability_Connection`
- L95 _public prototype_ `UStereoVideoIngestDevice() = default;`
- L96 _public prototype_ `~UStereoVideoIngestDevice() = default;`
- L99 _public prototype_ `const UStereoVideoIngestDeviceSettings* GetSettings() const;` — `UFUNCTION(BlueprintCallable, Category = "GenericArchiveDeviceSettings")`
- L102 _public prototype_ `virtual TSubclassOf<ULiveLinkDeviceSettings> GetSettingsClass() const override;`
- L103 _public prototype_ `virtual EDeviceHealth GetDeviceHealth() const override;`
- L104 _public prototype_ `virtual FText GetHealthText() const override;`
- L106 _public prototype_ `virtual void OnSettingChanged(const FPropertyChangedEvent& InPropertyChangedEvent) override;`
- L137 _private typedef_ `using FTakesWithComponents = TArray<struct FTakeWithComponents>;`
- L139 _private prototype_ `virtual FString GetFullTakePath(UE::CaptureManager::FTakeId InTakeId) const override;`
- L142 _private prototype_ `virtual void RunConvertAndUploadTake(const UIngestCapability_ProcessHandle* InProcessHandle, const UIngestCapability_Options* InIngestOptions) override;`
- L144 _private prototype_ `virtual void RunUpdateTakeList(UIngestCapability_UpdateTakeListCallback* InCallback) override;`
- L148 _private prototype_ `virtual ELiveLinkDeviceConnectionStatus GetConnectionStatus_Implementation() const override;`
- L149 _private prototype_ `virtual FString GetHardwareId_Implementation() const override;`
- L150 _private prototype_ `virtual bool SetHardwareId_Implementation(const FString& HardwareID) override;`
- L151 _private prototype_ `virtual bool Connect_Implementation() override;`
- L152 _private prototype_ `virtual bool Disconnect_Implementation() override;`
- L155 _private prototype_ `bool IsVideoFile(const FString& InFileNameWithExtension);`
- L156 _private prototype_ `bool IsFrameInSequenceFile(const FString& InFileNameWithExtension);`
- L157 _private prototype_ `bool IsAudioFile(const FString& InFileNameWithExtension);`
- L159 _private prototype_ `TOptional<FTakeWithComponents> ExtractTakeComponentsUsingTokens(FString ComponentPath, FString StoragePath, FString Format, ETakeComponentType ComponentType);`
- L160 _private prototype_ `TOptional<FTakeWithComponents> ExtractTakeComponentsFromDirectoryStructure(FString ComponentPath, FString StoragePath, ETakeComponentType ComponentType);`
- L161 _private prototype_ `void GroupFoundComponents(TMap<FString, UStereoVideoIngestDevice::FTakeWithComponents>& TakesWithComponentsCandidates, FTakeWithComponents TakeWithComponents);`
- L162 _private prototype_ `void ExtractTakeComponents(FString ComponentPath, FString StoragePath, ETakeComponentType ComponentType, FString Format, FString UnknownComponentName, TMap<FString, UStereoVideoIngestDevice::FTakeWithComponents>& OutTakesWithComponentsCandidates);`
- L163 _private prototype_ `TMap<FString, FTakeWithComponents> DiscoverTakes(FString StoragePath);`
- L164 _private prototype_ `TOptional<FTakeMetadata> CreateTakeMetadata(const FTakeWithComponents & InTakesWithComponents) const;`
- L166 _private member_ `TMap<int32, FString> FullTakePaths;`

#### enum `UStereoVideoIngestDevice::ETakeComponentType`  
`enum class ETakeComponentType`  
_L111-116_
- L113 _public enumerator_ `VIDEO`
- L114 _public enumerator_ `IMAGE_SEQUENCE`
- L115 _public enumerator_ `AUDIO`

#### struct `UStereoVideoIngestDevice::FTakeWithComponents`  
`struct FTakeWithComponents`  
_L118-135_
- L127 _public member_ `FString TakePath;`
- L129 _public member_ `FString SlateName;`
- L130 _public member_ `int32 TakeNumber;`
- L132 _public member_ `TArray<Component> Components;`
- L134 _public prototype_ `int32 CountComponents(ETakeComponentType Type);`

#### struct `UStereoVideoIngestDevice::FTakeWithComponents::Component`  
`struct Component`  
_L120-125_
- L122 _public member_ `FString Name;`
- L123 _public member_ `ETakeComponentType Type;`
- L124 _public member_ `FString Path;`
