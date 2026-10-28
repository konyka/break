# Plugins / AvalancheMedia

- module root: `Plugins/VirtualProduction/Avalanche/Source/AvalancheMedia`
- headers: 133; symbols: 4108
- symbol kinds: class=119, delegate=48, enum=54, enumerator=252, function=545, macro=3, member=1042, namespace=53, prototype=1780, struct=207, typedef=3, variable=2
- DynamicallyLoadedModuleNames: Messaging
- PrivateDependencyModuleNames: ApplicationCore, AssetRegistry, AvalancheCore, AvalancheMaterial, AvalancheRemoteControl, GraphEditor, HTTPServer, HeadMountedDisplay, ImageCore, InputCore, Json, JsonUtilities, Projects, RHI, RemoteControlCommon, RenderCore, Renderer, Serialization, Slate, SlateCore, StateTreeModule, UMG, UnrealEd, XmlSerialization
- PrivateIncludePathModuleNames: Messaging, MessagingCommon
- PublicDependencyModuleNames: Avalanche, AvalancheSequence, AvalancheTag, AvalancheTransition, Core, CoreUObject, DeveloperSettings, Engine, MediaIOCore, RemoteControl, RemoteControlLogic

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMedia/Internal/AvaMediaMessageUtils.h` (Internal)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace AvaMediaMessageUtils` (scope `UE`)
- L14 _prototype_ `uint32 GetSafeMessageSizeLimit();` (scope `UE::AvaMediaMessageUtils`) — Some of the message bus bridge have limitations to the size of the messages. This function returns the current largest message size that can "safely" be sent through the message bus without causing (known) issues.

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMedia/Internal/AvaMediaRenderTargetUtils.h` (Internal)


#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace AvaMediaRenderTargetUtils` (scope `UE`)
- L17 _prototype_ `UTextureRenderTarget2D* CreateDefaultRenderTarget(FName InBaseName);` (scope `UE::AvaMediaRenderTargetUtils`) — Creates a Render Target with default settings like bForceLinearGamma to be false.
- L20 _prototype_ `void UpdateRenderTarget(UTextureRenderTarget2D* InRenderTarget, const FIntPoint& InSize, EPixelFormat InFormat, const FLinearColor& InClearColor);` (scope `UE::AvaMediaRenderTargetUtils`) — Update the render target with the given parameters.
- L26 _prototype_ `bool SetupRenderTargetGamma(UTextureRenderTarget2D* InRenderTarget);` (scope `UE::AvaMediaRenderTargetUtils`) — Setup the render target gamma appropriately depending on the format. @return true if the TargetGamma was modified, false otherwise.
- L32 _prototype_ `FIntPoint GetRenderTargetSizeSafe(const UTextureRenderTarget2D* InRenderTarget);` (scope `UE::AvaMediaRenderTargetUtils`) — Returns the size of the render target. This version of the function doesn't ensure if the render target is not valid.
- L38 _prototype_ `FIntPoint GetRenderTargetSize(const UTextureRenderTarget2D* InRenderTarget);` (scope `UE::AvaMediaRenderTargetUtils`) — Returns the size of the render target. An ensure will be fired if the render target is not valid.
- L41 _prototype_ `bool IsFloatFormat(const UTextureRenderTarget2D* InRenderTarget);` (scope `UE::AvaMediaRenderTargetUtils`) — Returns true if render target's format is floating point.
- L44 _prototype_ `int32 GetNumColorComponents(EPixelFormat InFormat);` (scope `UE::AvaMediaRenderTargetUtils`) — Returns the number of color components for the given pixel format.
- L47 _prototype_ `bool HasAlpha(EPixelFormat InFormat);` (scope `UE::AvaMediaRenderTargetUtils`) — Returns true if the given format has an alpha channel.
- L53 _prototype_ `int32 GetNumColorChannelBits(EPixelFormat InFormat);` (scope `UE::AvaMediaRenderTargetUtils`) — Returns the number of bits per color component (assuming all the same) for the given pixel format. Known exceptions: PF_R5G6B5_UNORM, PF_FloatR11G11B10. But those are not render target formats.
- L56 _prototype_ `int32 GetNumAlphaChannelBits(EPixelFormat InFormat);` (scope `UE::AvaMediaRenderTargetUtils`) — Returns the number of bits for the alpha channel.

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMedia/Internal/AvaMediaSerializationUtils.h` (Internal)


#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace AvaMediaSerializationUtils` (scope `UE`)
- L16 _prototype_ `void SerializeObject(FStructuredArchiveFormatter& Formatter, UObject* InObject, const TFunction<bool(FProperty*)>& InShouldSkipProperty = TFunction<bool(FProperty*)>());` (scope `UE::AvaMediaSerializationUtils`) — Serialize the given object with the given formatter.
- L24 _namespace_ `namespace JsonValueConversion` (scope `UE::AvaMediaSerializationUtils`)
- L27 _prototype_ `void BytesToString(const TArray<uint8>& InValueAsBytes, FString& OutValueAsString);` (scope `UE::AvaMediaSerializationUtils::JsonValueConversion`) — Converts a serialized value stored as raw bytes into a string. In place version.
- L30 _function_ `inline TArrayView<const uint8> ValueToConstBytesView(const FString& InValueAsString)` (scope `UE::AvaMediaSerializationUtils::JsonValueConversion`) — This ArrayView version is meant to work with FMemoryReaderView.

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMedia/Internal/Broadcast/AvaBroadcastDevice.h` (Internal)


#### struct `FAvaBroadcastDevice`  
`struct FAvaBroadcastDevice`  
_L12-59_
- L14 _public function_ `FAvaBroadcastDevice(const FMediaIODevice& InDevice, const FName& InDeviceProviderName, const FString& InServerName) : Device(InDevice) , DeviceProviderName(InDeviceProviderName) , ServerName(InServerName)`
- L21 _public function_ `bool IsValid() const`
- L26 _public function_ `bool operator==(const FAvaBroadcastDevice& Other) const`
- L33 _public function_ `FText GetDisplayNameText() const`
- L47 _public function_ `const FMediaIODevice& GetDevice() const`
- L48 _public function_ `const FName& GetDeviceProviderName() const`
- L49 _public function_ `const FString& GetServerName() const`
- L52 _protected member_ `FMediaIODevice Device;`
- L55 _protected member_ `FName DeviceProviderName;` — Name of the device provider for this device.
- L58 _protected member_ `FString ServerName;` — Name of the server hosting this device.

#### Free symbols / members of external scopes

- L10 _macro_ `#define LOCTEXT_NAMESPACE "AvaBroadcastDevice"`
- L39 _function_ `friend uint32 GetTypeHash(const FAvaBroadcastDevice& InDevice)`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMedia/Internal/Broadcast/OutputDevices/AvaBroadcastDeviceProviderData.h` (Internal)


#### struct `FAvaBroadcastDeviceProviderData`  
`struct FAvaBroadcastDeviceProviderData`  
_L9-71_
- reflection: `USTRUCT()`
- L15 _public member_ `FName Name;` — `UPROPERTY()`
- L18 _public member_ `TArray<FMediaIOConnection> Connections;` — `UPROPERTY()`
- L21 _public member_ `TArray<FMediaIOConfiguration> Configurations;` — `UPROPERTY()`
- L24 _public member_ `TArray<FMediaIODevice> Devices;` — `UPROPERTY()`
- L27 _public member_ `TArray<FMediaIOMode> Modes;` — `UPROPERTY()`
- L30 _public member_ `TArray<FMediaIOInputConfiguration> InputConfigurations;` — `UPROPERTY()`
- L33 _public member_ `TArray<FMediaIOOutputConfiguration> OutputConfigurations;` — `UPROPERTY()`
- L36 _public member_ `TArray<FMediaIOVideoTimecodeConfiguration> TimecodeConfigurations;` — `UPROPERTY()`
- L39 _public member_ `FMediaIOConfiguration DefaultConfiguration;` — `UPROPERTY()`
- L42 _public member_ `FMediaIOMode DefaultMode;` — `UPROPERTY()`
- L45 _public member_ `FMediaIOInputConfiguration DefaultInputConfiguration;` — `UPROPERTY()`
- L48 _public member_ `FMediaIOOutputConfiguration DefaultOutputConfiguration;` — `UPROPERTY()`
- L51 _public member_ `FMediaIOVideoTimecodeConfiguration DefaultTimecodeConfiguration;` — `UPROPERTY()`
- L54 _public member_ `bool bShowInputTransportInSelector = true;` — `UPROPERTY()`
- L57 _public member_ `bool bShowOutputTransportInSelector = true;` — `UPROPERTY()`
- L60 _public member_ `bool bShowInputKeyInSelector = true;` — `UPROPERTY()`
- L63 _public member_ `bool bShowOutputKeyInSelector = true;` — `UPROPERTY()`
- L66 _public member_ `bool bShowReferenceInSelector = true;` — `UPROPERTY()`
- L69 _public prototype_ `void PopulateFrom(const FName& InName, const IMediaIOCoreDeviceProvider* InDeviceProvider);`
- L70 _public prototype_ `void ApplyServerName(const FString& InServerName);`

#### struct `FAvaBroadcastDeviceProviderDataList`  
`struct FAvaBroadcastDeviceProviderDataList`  
_L74-89_
- reflection: `USTRUCT()`
- L80 _public member_ `FString ServerName;` — `UPROPERTY()`
- L83 _public member_ `TArray<FAvaBroadcastDeviceProviderData> DeviceProviders;` — `UPROPERTY()`
- L85 _public prototype_ `bool SaveToJson();`
- L86 _public prototype_ `bool SaveToXml();`
- L87 _public prototype_ `bool LoadFromJson();`
- L88 _public prototype_ `void Populate(const FString& InAssignedServerName);`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMedia/Internal/Broadcast/OutputDevices/AvaBroadcastOutputRootItem.h` (Internal)


#### class `FAvaBroadcastOutputRootItem`  
`class FAvaBroadcastOutputRootItem : public FAvaBroadcastOutputTreeItem`  
_L7-25_
- inherits: `FAvaBroadcastOutputTreeItem`
- L10 _public prototype_ `UE_AVA_INHERITS_WITH_SUPER(FAvaBroadcastOutputRootItem, FAvaBroadcastOutputTreeItem);`
- L12 _public function_ `FAvaBroadcastOutputRootItem() : Super(nullptr)`
- L17 _public prototype_ `virtual void RefreshChildren(const FRefreshChildrenParams& InParams) override;`
- L19 _private prototype_ `virtual FText GetDisplayName() const override;`
- L20 _private prototype_ `virtual const FSlateBrush* GetIconBrush() const override;`
- L21 _private prototype_ `virtual TSharedPtr<SWidget> GenerateRowWidget() override;`
- L22 _private prototype_ `virtual FReply OnDragDetected(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L23 _private prototype_ `virtual UMediaOutput* AddMediaOutputToChannel(FName InTargetChannel, const FAvaBroadcastMediaOutputInfo& InOutputInfo) override;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMedia/Internal/Broadcast/OutputDevices/AvaBroadcastOutputTreeItem.h` (Internal)


#### class `IAvaBroadcastOutputTreeItem`  
`class IAvaBroadcastOutputTreeItem : public IAvaTypeCastable, public TSharedFromThis<IAvaBroadcastOutputTreeItem>`  
_L20-54_
- inherits: `IAvaTypeCastable,TSharedFromThis<IAvaBroadcastOutputTreeItem>`
- L23 _public prototype_ `UE_AVA_INHERITS(IAvaBroadcastOutputTreeItem, IAvaTypeCastable);`
- L25 _public prototype_ `virtual FText GetDisplayName() const = 0;`
- L27 _public prototype_ `virtual const FSlateBrush* GetIconBrush() const = 0;`
- L36 _public prototype_ `virtual void RefreshChildren(const FRefreshChildrenParams& InParams) = 0;` — Refreshes what the Children are of this Item. (not recursive!)
- L38 _public prototype_ `virtual TSharedPtr<SWidget> GenerateRowWidget() = 0;`
- L40 _public prototype_ `virtual const TWeakPtr<FAvaBroadcastOutputTreeItem>& GetParent() const = 0;`
- L42 _public prototype_ `virtual const TArray<FAvaOutputTreeItemPtr>& GetChildren() const = 0;`
- L44 _public prototype_ `virtual FReply OnDragDetected(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) = 0;`
- L47 _public prototype_ `virtual bool IsValidToDropInChannel(FName InTargetChannelName) = 0;` — Returns true if it is valid to add this item to the given channel.
- L49 _public prototype_ `virtual UMediaOutput* AddMediaOutputToChannel(FName InTargetChannel, const FAvaBroadcastMediaOutputInfo& InOutputInfo) = 0;`
- L52 _public prototype_ `DECLARE_DELEGATE_RetVal_OneParam(TSharedRef<FDragDropOperation>, FOnCreateDragDropOperation, const FAvaOutputTreeItemPtr&) virtual FOnCreateDragDropOperation& OnCreateDragDropOperation() = 0;` — Delegating the drag and drop operation to editor module.

#### struct `IAvaBroadcastOutputTreeItem::FRefreshChildrenParams`  
`struct FRefreshChildrenParams`  
_L29-33_
- L32 _public member_ `bool bShowAllMediaOutputClasses = false;` — Include all the media output classes. If false, only classes with a device provider will be included.

#### class `FAvaBroadcastOutputTreeItem`  
`class FAvaBroadcastOutputTreeItem : public IAvaBroadcastOutputTreeItem`  
_L56-82_
- inherits: `IAvaBroadcastOutputTreeItem`
- L59 _public prototype_ `UE_AVA_INHERITS(FAvaBroadcastOutputTreeItem, IAvaBroadcastOutputTreeItem);`
- L61 _public function_ `FAvaBroadcastOutputTreeItem(const TSharedPtr<FAvaBroadcastOutputTreeItem>& InParent) : ParentWeak(InParent)`
- L67 _public function_ `virtual ~FAvaBroadcastOutputTreeItem() override`
- L68 _public prototype_ `virtual const TWeakPtr<FAvaBroadcastOutputTreeItem>& GetParent() const override;`
- L69 _public prototype_ `virtual const TArray<FAvaOutputTreeItemPtr>& GetChildren() const override;`
- L70 _public prototype_ `virtual FReply OnDragDetected(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L71 _public function_ `virtual bool IsValidToDropInChannel(FName InTargetChannelName) override`
- L72 _public function_ `virtual FOnCreateDragDropOperation& OnCreateDragDropOperation() override`
- L76 _public prototype_ `static void RefreshTree(const FAvaOutputTreeItemPtr& InItem, const FRefreshChildrenParams& InParams);` — Calls RefreshChildren() on the tree of item.
- L79 _protected member_ `TWeakPtr<FAvaBroadcastOutputTreeItem> ParentWeak;`
- L80 _protected member_ `TArray<FAvaOutputTreeItemPtr> Children;`
- L81 _protected member_ `FOnCreateDragDropOperation OnCreateDragDropOperationDelegate;`

#### Free symbols / members of external scopes

- L18 _typedef_ `using FAvaOutputTreeItemPtr = TSharedPtr<IAvaBroadcastOutputTreeItem>;`
- L52 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(TSharedRef<FDragDropOperation>, FOnCreateDragDropOperation, const FAvaOutputTreeItemPtr&) virtual FOnCreateDragDropOperation& OnCreateDragDropOperation() = 0;` — Delegating the drag and drop operation to editor module.

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMedia/Internal/Broadcast/OutputDevices/AvaBroadcastOutputUtils.h` (Internal)


#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace AvaBroadcastOutputUtils` (scope `UE`)
- L15 _prototype_ `FString GetDeviceName(const UMediaOutput* InMediaOutput);` (scope `UE::AvaBroadcastOutputUtils`) — Get the device's name from the given MediaOutput.
- L18 _prototype_ `bool HasDeviceProviderName(const UClass* InMediaOutputClass);` (scope `UE::AvaBroadcastOutputUtils`) — Returns true if the class has MediaIOCustomLayout meta data.
- L21 _prototype_ `FName GetDeviceProviderName(const UClass* InMediaOutputClass);` (scope `UE::AvaBroadcastOutputUtils`) — Retrieves the device provider name from the MediaIOCustomLayout class meta data.
- L24 _prototype_ `FName GetDeviceProviderName(const UMediaOutput* InMediaOutput);` (scope `UE::AvaBroadcastOutputUtils`) — Retrieves the device provider name from the MediaIOCustomLayout class meta data.
- L27 _prototype_ `bool IsGameViewportOutput(const UMediaOutput* InMediaOutput);` (scope `UE::AvaBroadcastOutputUtils`) — Returns true if the given media output is a game viewport output.
- L30 _prototype_ `FAvaBroadcastOutputData CreateMediaOutputData(UMediaOutput* InMediaOutput);` (scope `UE::AvaBroadcastOutputUtils`) — Serializes the given MediaOutput object into a FAvaBroadcastOutputData.
- L33 _prototype_ `UMediaOutput* CreateMediaOutput(const FAvaBroadcastOutputData& InMediaOutputData, UObject* InOuter);` (scope `UE::AvaBroadcastOutputUtils`) — Create a MediaOutput object from the given data.

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMedia/Internal/Broadcast/OutputDevices/AvaBroadcastRenderTargetMediaUtils.h` (Internal)


#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace AvaBroadcastRenderTargetMediaUtils` (scope `UE`)
- L12 _variable_ `static inline const TCHAR* VirtualShaderMountPoint = TEXT("/Pl` (scope `UE::AvaBroadcastRenderTargetMediaUtils`)
- L18 _prototype_ `void ClearRenderTarget(UTextureRenderTarget2D* InRenderTarget);` (scope `UE::AvaBroadcastRenderTargetMediaUtils`) — Clears the given render target to it's specified clear color. @remark called from the main thread.
- L25 _prototype_ `void CopyTexture(FRHICommandListImmediate& InRHICmdList, FTextureRHIRef InSourceTexture, FTextureRHIRef InDestTarget);` (scope `UE::AvaBroadcastRenderTargetMediaUtils`) — Copy a texture from source to destination. Handles different sizes, will rescale. Handles different formats, will convert.
- L28 _prototype_ `void ConvertTextureRGBGamma(FRHICommandListImmediate& InRHICmdList, FTextureRHIRef InSourceTexture, FTextureRHIRef InDestTarget, bool bInSrgbToLinear, float InGamma);` (scope `UE::AvaBroadcastRenderTargetMediaUtils`) — Implementation of texture conversion from SCS_FinalColorSDR back to SCS_FinalToneCurveHDR.

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMedia/Internal/Broadcast/OutputDevices/Slate/SAvaBroadcastCaptureImage.h` (Internal)


#### class `SAvaBroadcastCaptureImage`  
`class SAvaBroadcastCaptureImage : public SImage`  
_L13-41_
- inherits: `SImage`
- L16 _public function_ `SLATE_BEGIN_ARGS(SAvaBroadcastCaptureImage) : _ImageArgs() , _EnableGammaCorrection(true)`
- L20 _public prototype_ `SLATE_ARGUMENT(SImage::FArguments, ImageArgs) SLATE_ARGUMENT(bool, EnableGammaCorrection) SLATE_ATTRIBUTE(bool, EnableBlending) SLATE_ATTRIBUTE(bool, ShouldInvertAlpha) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L29 _public prototype_ `virtual int32 OnPaint(const FPaintArgs& Args , const FGeometry& AllottedGeometry , const FSlateRect& MyCullingRect , FSlateWindowElementList& OutDrawElements , int32 LayerId , const FWidgetStyle& InWidgetStyle , bool bParentEnabled) const override;`
- L38 _protected member_ `bool bEnableGammaCorrection = true;`
- L39 _protected member_ `TAttribute<bool> EnableBlending;`
- L40 _protected member_ `TAttribute<bool> ShouldInvertAlpha;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMedia/Internal/ModularFeature/AvaMediaSynchronizedEventsFeature.h` (Internal)


#### class `FAvaMediaSynchronizedEventsFeature`  
`class FAvaMediaSynchronizedEventsFeature`  
_L7-37_
- L10 _public prototype_ `static void Startup();`
- L12 _public prototype_ `static void Shutdown();`
- L18 _public prototype_ `static IAvaMediaSynchronizedEventsFeature* Get();` — Returns currently selected implementation. This function always returns a valid implementation.
- L23 _public prototype_ `static TSharedPtr<IAvaMediaSynchronizedEventDispatcher> CreateDispatcher(const FString& InSignature);` — Creates a new event dispatcher from the currently selected implementation.
- L25 _public prototype_ `static void EnumerateImplementations(TFunctionRef<void(const IAvaMediaSynchronizedEventsFeature*)> InCallback);`
- L33 _public prototype_ `static IAvaMediaSynchronizedEventsFeature* FindImplementation(FName InImplementation);` — Find the implementation with the given name. The name can be "default", in which case it will automatically select the highest priority implementation. If no implementation match the given name, it will return an internal "no sync" implementation. This function always returns a valid implementation.
- L36 _private prototype_ `static IAvaMediaSynchronizedEventsFeature* GetInternalImplementation();`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMedia/Internal/Playable/AvaPlayableRemoteControl.h` (Internal)


#### enum `EAvaPlayableRemoteControlResult`  
`enum class EAvaPlayableRemoteControlResult : int8`  
_L15-31_
- reflection: `UENUM()`
- desc: Return code for Remote Control operations.
- L18 _public enumerator_ `Completed = 0` — Operation completed successfully
- L20 _public enumerator_ `UpToDate = 1` — Operation was not necessary.
- L22 _public enumerator_ `InvalidParameter = -1` — Input parameter is invalid
- L24 _public enumerator_ `ReadAccessDenied = -2` — Object reference read access failed.
- L26 _public enumerator_ `WriteAccessDenied = -3` — Object reference write access failed.
- L28 _public enumerator_ `ReadPropertyFailed = -4` — Serialization from property failed.
- L30 _public enumerator_ `WritePropertyFailed = -5` — Serialization to property failed.

#### class `UE::AvaPlayableRemoteControl::FScopedPushControllerBehavioursEnable`  
`class FScopedPushControllerBehavioursEnable`  
_L70-79_
- desc: Utility class to temporarily push the enabled state of the controller's behaviours. This class is intended to be used temporarily on local stack. Lifetime of virtual property is not managed.
- L73 _public prototype_ `FScopedPushControllerBehavioursEnable(URCVirtualPropertyBase* InVirtualProperty, bool bInBehavioursEnabled);`
- L74 _public prototype_ `~FScopedPushControllerBehavioursEnable();`
- L77 _private member_ `URCVirtualPropertyBase* VirtualProperty = nullptr;`
- L78 _private member_ `TArray<bool> PreviousBehavioursEnabled;`

#### Free symbols / members of external scopes

- L9 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogAvaPlayableRemoteControl, Log, All);`
- L33 _namespace_ `namespace UE`
- L33 _namespace_ `namespace AvaPlayableRemoteControl` (scope `UE`)
- L36 _prototype_ `bool HasReadAccess(const TSharedPtr<const FRemoteControlEntity>& InRemoteControlEntity, FString& OutErrorText);` (scope `UE::AvaPlayableRemoteControl`) — Returns true if the binding is valid and access to read the property.
- L39 _prototype_ `bool HasWriteAccess(const TSharedPtr<const FRemoteControlEntity>& InRemoteControlEntity, FString& OutErrorText);` (scope `UE::AvaPlayableRemoteControl`) — Returns true if the binding is valid and access to write the property.
- L42 _prototype_ `EAvaPlayableRemoteControlResult GetValueOfEntity(const TSharedPtr<const FRemoteControlEntity>& InRemoteControlEntity, TArray<uint8>& OutValue);` (scope `UE::AvaPlayableRemoteControl`) — Gets the value (as bytes) of the given property (remote control entity). Returns true if the operation was successful, false otherwise.
- L43 _prototype_ `EAvaPlayableRemoteControlResult GetValueOfEntity(const TSharedPtr<const FRemoteControlEntity>& InRemoteControlEntity, FString& OutValue);` (scope `UE::AvaPlayableRemoteControl`)
- L46 _prototype_ `EAvaPlayableRemoteControlResult SetValueOfEntity(const TSharedPtr<FRemoteControlEntity>& InRemoteControlEntity, const TArrayView<const uint8>& InValue);` (scope `UE::AvaPlayableRemoteControl`) — Set the value (as bytes) of the given property (remote control entity). Returns true if the operation was successful, false otherwise.
- L47 _prototype_ `EAvaPlayableRemoteControlResult SetValueOfEntity(const TSharedPtr<FRemoteControlEntity>& InRemoteControlEntity, const FString& InValue);` (scope `UE::AvaPlayableRemoteControl`)
- L50 _prototype_ `EAvaPlayableRemoteControlResult GetValueOfController(URCVirtualPropertyBase* InController, TArray<uint8>& OutValue);` (scope `UE::AvaPlayableRemoteControl`) — Gets the value (as bytes) of the given controller. Returns true if the operation was successful, false otherwise.
- L51 _prototype_ `EAvaPlayableRemoteControlResult GetValueOfController(URCVirtualPropertyBase* InController, FString& OutValue);` (scope `UE::AvaPlayableRemoteControl`)
- L54 _prototype_ `EAvaPlayableRemoteControlResult SetValueOfController(URCVirtualPropertyBase* InController, const TArrayView<const uint8>& InValue);` (scope `UE::AvaPlayableRemoteControl`) — Set the value (as bytes) of the given controller. Returns true if the operation was successful, false otherwise.
- L55 _prototype_ `EAvaPlayableRemoteControlResult SetValueOfController(URCVirtualPropertyBase* InController, const FString& InValue);` (scope `UE::AvaPlayableRemoteControl`)
- L56 _prototype_ `EAvaPlayableRemoteControlResult SetValueOfController(URCVirtualPropertyBase* InController, const FString& InValue, bool bInBehaviorsEnabled);` (scope `UE::AvaPlayableRemoteControl`)
- L58 _function_ `inline bool Failed(EAvaPlayableRemoteControlResult InResult)` (scope `UE::AvaPlayableRemoteControl`)
- L64 _prototype_ `FString EnumToString(EAvaPlayableRemoteControlResult InValue);` (scope `UE::AvaPlayableRemoteControl`)

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMedia/Internal/Playback/AvaPlaybackUtils.h` (Internal)


#### class `FAvaPlaybackUtils`  
`class FAvaPlaybackUtils`  
_L16-57_
- L22 _public prototype_ `static void FlushPackageLoading(UPackage* InPackage, bool bInResetLoaders=false);` — Flushes loaded packages so the client can write to the files.
- L29 _public prototype_ `static bool IsPackageDeleted(const UPackage* InExistingPackage);` — Checks if the given packages has been deleted on disk. @remark With Editor only. @return true if the package was deleted, false if the package still exists on disk.
- L34 _public prototype_ `static void PurgePackages(const TArray<UPackage*>& InExistingPackages);` — Purge all the objects in memory owned by the given packages.
- L41 _public prototype_ `static bool ReloadPackages(const TArray<UPackage*>& InExistingPackages);` — Reloads the given package. @remark With Editor only. @return true if the package was reloaded.
- L49 _public prototype_ `static bool IsMapAsset(const FString& InPackageName);` — @brief Determines if the asset is a map by checking the file extension. @remark The file must exist on disk. @param InPackageName Package name. @return true if the file on disk is a .umap file.
- L56 _public prototype_ `static bool IsPlayableAsset(const FAssetData& InAssetData);` — @brief Determines if the asset is a playable (can be used as template) asset, using the asset class. @param InAssetData Asset Data @return true if the asset is an ava playable.

#### class `UE::AvaPlayback::Utils::FAsyncAssetLoader`  
`class FAsyncAssetLoader : public FGCObject, public TSharedFromThis<FAsyncAssetLoader>`  
_L89-124_
- inherits: `FGCObject,TSharedFromThis<FAsyncAssetLoader>`
- desc: Utility class to perform async load of assets.
- L92 _public prototype_ `void ProcessLoadedObject(UObject* InObject, FName InShaderProfile);`
- L100 _public prototype_ `void BeginLoadingAssets(const TArray<FSoftObjectPath>& InAssetsToLoad);` — @brief Issue the async load command. Returns immediately. @param InAssetsToLoad Assets to load. The specified asset to load will added to the current set of pending assets.
- L103 _public prototype_ `bool IsLoadingCompleted() const;` — Returns true when all the requested assets have finished loading.
- L106 _public prototype_ `void CleanupObjectsWithCompleteMaterials() const;` — Removes objects that have all their materials completed
- L109 _public prototype_ `void CleanupStreamingAssets() const;` — Removes streamable render assets that have fully been streamed in
- L112 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& InCollector) override;`
- L113 _public prototype_ `virtual FString GetReferencerName() const override;`
- L117 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnLoadingCompleted);` — Delegate called when all assets have finished loading.
- L118 _public member_ `FOnLoadingCompleted OnLoadingCompleted;`
- L121 _private member_ `TSet<FSoftObjectPath> PendingAssets;`
- L122 _private member_ `mutable TArray<TObjectPtr<UObject>> PendingMaterialCompletionObjects;`
- L123 _private member_ `mutable TArray<TObjectPtr<UStreamableRenderAsset>> PendingStreamingAssets;`

#### Free symbols / members of external scopes

- L59 _namespace_ `namespace UE`
- L59 _namespace_ `namespace AvaPlayback` (scope `UE`)
- L59 _namespace_ `namespace Utils` (scope `UE::AvaPlayback`)
- L65 _prototype_ `FString GetBriefFrameInfo();` (scope `UE::AvaPlayback::Utils`) — Returns a compactly formatted time stamp information for the current frame. This is to used for logging and tracing.
- L68 _function_ `template<typename InEnumType> FString StaticEnumToString(InEnumType InValue)` (scope `UE::AvaPlayback::Utils`)
- L77 _prototype_ `UStreamableRenderAsset* StreamRenderAsset(UObject* InObject);` (scope `UE::AvaPlayback::Utils`) — Streams in the given object if it's a streamable asset. returns a valid pointer to the object as a render asset if the asset was streamable
- L84 _prototype_ `bool CacheObjectMaterials(UObject* InObject, FName InShaderProfile);` (scope `UE::AvaPlayback::Utils`) — Caches the materials of the given object using the material bridge api @param InObject the object to gather and cache materials for @param InShaderProfile the shader profile to use for caching
- L117 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnLoadingCompleted);` — Delegate called when all assets have finished loading.

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMedia/Internal/Playback/Nodes/AvaPlaybackNodeLevelPlayer.h` (Internal)


#### class `UAvaPlaybackNodeLevelPlayer`  
`class UAvaPlaybackNodeLevelPlayer : public UAvaPlaybackNodePlayer`  
_L14-36_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAvaPlaybackNodePlayer`
- L19 _public prototype_ `UAvaPlaybackNodeLevelPlayer();`
- L21 _public prototype_ `virtual void RefreshNode(bool bDryRunGraph) override;`
- L22 _public prototype_ `virtual void PostLoad() override;`
- L24 _public function_ `TSoftObjectPtr<UWorld> GetAsset() const`
- L25 _public prototype_ `void SetAsset(const TSoftObjectPtr<UWorld>& InAsset);`
- L27 _public prototype_ `void UpdateDisplayNameText();`
- L29 _public function_ `virtual const FSoftObjectPath& GetAssetPath() const override`
- L31 _public prototype_ `virtual FAvaSoftAssetPtr GetAssetPtr() const override;`
- L35 _protected member_ `TSoftObjectPtr<UWorld> LevelAsset;` — `UPROPERTY(EditAnywhere, Category = "Motion Design")`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMedia/Internal/Rundown/AvaRundownManagedInstance.h` (Internal)


#### class `FAvaRundownManagedInstance`  
`class FAvaRundownManagedInstance : public IAvaTypeCastable, public FGCObject, public TSharedFromThis<FAvaRundownManagedInstance>`  
_L17-92_
- inherits: `IAvaTypeCastable,FGCObject,TSharedFromThis<FAvaRundownManagedInstance>`
- L20 _public prototype_ `UE_AVA_INHERITS(FAvaRundownManagedInstance, IAvaTypeCastable);`
- L22 _public prototype_ `FAvaRundownManagedInstance(FAvaRundownManagedInstanceCache* InParentCache, const FSoftObjectPath& InAssetPath);`
- L26 _public function_ `virtual bool IsValid() const` — Returns true if the instanced asset is valid.
- L29 _public function_ `virtual URemoteControlPreset* GetRemoteControlPreset() const` — Get the Managed Motion Design Asset's (top level) Remote Control Preset.
- L32 _public function_ `const FAvaPlayableRemoteControlValues& GetDefaultRemoteControlValues() const` — Access a copy of the Remote Control values from the source (a.k.a. template).
- L35 _public function_ `const FAvaPlayableRemoteControlPresetInfo& GetRemoteControlPresetInfo() const` — Access cached preset info for this instance.
- L42 _public function_ `virtual IAvaSceneInterface* GetSceneInterface() const` — Get the Ava scene interface from the asset.
- L44 _public function_ `const FSoftObjectPath& GetSourceAssetPath() const`
- L47 _public prototype_ `void SetCurrentRundownPageForEvents(UAvaRundown* InRundown, int32 InPageId);` — Set the current rundown page for routing controller events from this managed instance.
- L50 _public function_ `UAvaRundown* GetRundownForEvents() const` — Returns the rundown currently set to receive the RC Controller events from this managed instance.
- L56 _public function_ `int32 GetActivePageIdForEvents() const` — Returns the rundown page id that is currently set to receive RC Controller events from this managed instance.
- L62 _protected prototype_ `FAvaPlayableRemoteControlPresetInfo& GetRemoteControlPresetInfoFromCache(URemoteControlPreset* InRemoteControlPreset) const;`
- L63 _protected prototype_ `void InvalidateFromCache();`
- L65 _protected prototype_ `void RegisterSourceRemoteControlPresetDelegates(URemoteControlPreset* InSourceRemoteControlPreset);`
- L66 _protected prototype_ `void UnregisterSourceRemoteControlPresetDelegates(URemoteControlPreset* InSourceRemoteControlPreset) const;`
- L67 _protected prototype_ `void RegisterManagedRemoteControlPresetDelegates(URemoteControlPreset* InManagedRemoteControlPreset);`
- L68 _protected prototype_ `void UnregisterManagedRemoteControlPresetDelegates(URemoteControlPreset* InManagedRemoteControlPreset) const;`
- L70 _protected prototype_ `void OnSourceRemoteControlEntitiesExposed(URemoteControlPreset* InSourcePreset, const FGuid& InEntityId);`
- L71 _protected prototype_ `void OnSourceRemoteControlEntitiesUnexposed(URemoteControlPreset* InSourcePreset, const FGuid& InEntityId);`
- L72 _protected prototype_ `void OnSourceRemoteControlEntitiesUpdated(URemoteControlPreset* InSourcePreset, const TSet<FGuid>& InModifiedEntities);`
- L73 _protected prototype_ `void OnSourceRemoteControlExposedPropertiesModified(URemoteControlPreset* InSourcePreset, const TSet<FGuid>& InModifiedProperties);`
- L74 _protected prototype_ `void OnSourceRemoteControlControllerAdded(URemoteControlPreset* InSourcePreset, const FName NewControllerName, const FGuid& InControllerId);`
- L75 _protected prototype_ `void OnSourceRemoteControlControllerRemoved(URemoteControlPreset* InSourcePreset, const FGuid& InControllerId);`
- L76 _protected prototype_ `void OnSourceRemoteControlControllerRenamed(URemoteControlPreset* InSourcePreset, const FName InOldLabel, const FName InNewLabel);`
- L77 _protected prototype_ `void OnSourceRemoteControlControllerModified(URemoteControlPreset* InSourcePreset, const TSet<FGuid>& InModifiedControllerIds);`
- L79 _protected prototype_ `void OnManagedRemoteControlControllerModified(URemoteControlPreset* InPreset, const TSet<FGuid>& InModifiedControllerIds);`
- L82 _protected member_ `FAvaRundownManagedInstanceCache* ParentCache;`
- L83 _protected member_ `FSoftObjectPath SourceAssetPath;`
- L84 _protected member_ `FAvaPlayableRemoteControlValues DefaultRemoteControlValues;`
- L85 _protected member_ `mutable TSharedPtr<FAvaPlayableRemoteControlPresetInfo> RemoteControlPresetInfo;`
- L88 _protected member_ `TWeakObjectPtr<UAvaRundown> RundownForEvents;` — Current rundown for routing controller events.
- L91 _protected member_ `int32 ActivePageId;` — Current active page for routing controller events.

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMedia/Internal/Rundown/AvaRundownManagedInstanceCache.h` (Internal)


#### class `FAvaRundownManagedInstanceCache`  
`class FAvaRundownManagedInstanceCache`  
_L23-113_
- desc: Cache for the managed Motion Design instances. This is LRU cache. Todo: This needs to be refactored as a pool instead. A managed asset instance is needed for each page that is edited. Since rundown editor and server can edit different pages (of the same template), it needs more than one instance and it needs to be tied to the rundown (for RC event routing).
- L26 _public prototype_ `FAvaRundownManagedInstanceCache();`
- L27 _public prototype_ `virtual ~FAvaRundownManagedInstanceCache();`
- L33 _public prototype_ `TSharedPtr<FAvaRundownManagedInstance> GetOrLoadInstance(const FSoftObjectPath& InAssetPath);` — Retrieves elements from the cache or load a new one if not present. If the cache size is exceeded, the oldest elements are going to be flushed.
- L39 _public prototype_ `void InvalidateNoDelete(const FSoftObjectPath& InAssetPath);` — Invalidates a cached entry without deleting it immediately. It will be deleted and reloaded on the next access query.
- L44 _public prototype_ `void Invalidate(const FSoftObjectPath& InAssetPath);` — Invalidates a cached entry. The entry may be deleted as a result.
- L50 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnEntryInvalidated, const FSoftObjectPath& );` — Delegate called when an entry is invalidated. Reason for an entry to be invalidated is if the source has been modified.
- L51 _public member_ `FOnEntryInvalidated OnEntryInvalidated;`
- L56 _public prototype_ `int32 GetMaximumCacheSize() const;` — Get the maximum size of the cache beyond witch it will start flushing elements.
- L61 _public prototype_ `void Flush(const FSoftObjectPath& InAssetPath);` — Flush specified entry from the cache.
- L66 _public prototype_ `void Flush();` — Flush all unused entries from the cache.
- L71 _public prototype_ `void TrimCache();` — Trim the cache elements that exceed the cache capacity according to LRU replacement policy.
- L77 _public prototype_ `void FinishPendingActions();` — Perform any pending actions, such has removing invalidated entries. This may lead to objects being deleted.
- L85 _public prototype_ `TArray<TSharedPtr<FAvaRundownManagedInstance>> GetManagedInstancesForPage(const UAvaRundown* InRundown, const FAvaRundownPage& InPage);` — Utility function to get all the managed instances for a given page, including all sub-pages in case of a combo page. @param InRundown Rundown owning the current page. @param InPage Page to get the assets from. @return managed asset instances for the given page.
- L96 _public prototype_ `FAvaRundownManagedInstanceHandles GetManagedHandlesForPage(UAvaRundown* InRundown, const FAvaRundownPage& InPage);` — Utility function to acquire all the managed instances for a given page, including all sub-pages in case of a combo page. This will register the given rundown page for controller events routing in the managed instances (potentially overriding previous rundown or page). @param InRundown Rundown owning the current page. @param InPage Page to get the assets from. @return managed asset instance handles for the given page.
- L99 _private prototype_ `void RemovePendingInvalidatedPaths();`
- L100 _private prototype_ `void RemoveEntry(const FSoftObjectPath& InAssetPath);`
- L101 _private prototype_ `void RemoveEntries(TFunctionRef<bool(const FSoftObjectPath&, const TSharedPtr<FAvaRundownManagedInstance>&)> InRemovePredicate, bool bInNotify);`
- L103 _private prototype_ `void OnPackageSaved(const FString& InPackageFileName, UPackage* InPackage, FObjectPostSaveContext InObjectSaveContext);`
- L104 _private prototype_ `void OnAvaSyncPackageModified(IAvaMediaSyncProvider* InAvaMediaSyncProvider, const FName& InPackageName);`
- L105 _private prototype_ `void OnAssetRemoved(const FAssetData& InAssetData);`
- L106 _private prototype_ `void OnPackageModified(const FName& InPackageName);`
- L107 _private prototype_ `void OnSettingChanged(UObject* , struct FPropertyChangedEvent&);`
- L110 _private member_ `TMap<FSoftObjectPath, TSharedPtr<FAvaRundownManagedInstance>> Instances;`
- L111 _private member_ `TSet<FSoftObjectPath> PendingInvalidatedPaths;`
- L112 _private member_ `TArray<FSoftObjectPath> OrderQueue;`

#### Free symbols / members of external scopes

- L50 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnEntryInvalidated, const FSoftObjectPath& );` — Delegate called when an entry is invalidated. Reason for an entry to be invalidated is if the source has been modified.

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMedia/Internal/Rundown/AvaRundownManagedInstanceHandle.h` (Internal)


#### struct `FAvaRundownManagedInstanceHandles`  
`struct FAvaRundownManagedInstanceHandles`  
_L23-73_
- desc: Set of rundown managed asset instances tied to a given rundown for RC editing operations. It will hook the controller events routing to the provided rundown and page on construction and handles auto-unregister of Rundown on destruction. As this object represents the ownership of the "event routing" for a given rundown and page, it is not copiable.
- L25 _public prototype_ `FAvaRundownManagedInstanceHandles() = default;`
- L31 _public prototype_ `FAvaRundownManagedInstanceHandles(const TArray<TSharedPtr<FAvaRundownManagedInstance>>& InInstances, UAvaRundown* InRundown, int32 InPageId);` — The constructor will register the given rundown page for controller events routing in the managed instances (potentially overriding previous rundown or page).
- L33 _public prototype_ `FAvaRundownManagedInstanceHandles(const FAvaRundownManagedInstanceHandles& InOther) = delete;`
- L34 _public prototype_ `FAvaRundownManagedInstanceHandles& operator=(const FAvaRundownManagedInstanceHandles& InOther) = delete;`
- L36 _public function_ `FAvaRundownManagedInstanceHandles(FAvaRundownManagedInstanceHandles&& InOther)`
- L42 _public prototype_ `FAvaRundownManagedInstanceHandles& operator=(FAvaRundownManagedInstanceHandles&& InOther);` — Move operator handles unregistering instances if needed.
- L44 _public function_ `~FAvaRundownManagedInstanceHandles()`
- L49 _public function_ `bool IsEmpty() const`
- L54 _public function_ `int32 Num() const`
- L62 _public prototype_ `void Reset();` — Unregisters the rundown from the instances (only if it hasn't been overriden already) and resets the array of instances.
- L65 _public member_ `TArray<TSharedPtr<FAvaRundownManagedInstance>> Instances;` — Array of managed asset instances.
- L69 _private member_ `TWeakObjectPtr<UAvaRundown> RegisteredRundown;` — Keep track of the registered Rundown to be able to unregister if needed.
- L72 _private member_ `int32 RegisteredPageId = UE::AvaMedia::Rundown::InvalidPageId;` — Keep track of the registered page id to be able to unregister if needed.

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API AVALANCHEMEDIA_API`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMedia/Internal/Rundown/AvaRundownMessages.h` (Internal)


#### enum `EAvaRundownApiVersion::Type`  
`enum Type`  
_L20-38_
- desc: Defines the protocol version of the Rundown Server API. API versioning is used to provide legacy support either on the client side or server side for non compatible changes. Clients can request a version of the API that they where implemented against, if the server can still honor the request it will accept.
- L22 _public enumerator_ `Unspecified = -1`
- L24 _public enumerator_ `Initial = 1`
- L32 _public enumerator_ `MoveToRuntime = 2` — The rundown server has been moved to the runtime module. All message scripts paths moved from AvalancheMediaEditor to AvalancheMedia. However, all server requests messages have been added to core redirect, so previous path will still get through, but all response messages will be the new path. Clients can still issue a ping with the old path and will get a response.
- L36 _public enumerator_ `VersionPlusOne` — -----<new versions can be added before this line>------------------------------------------------- - this needs to be the last line (see note below)
- L37 _public enumerator_ `LatestVersion = VersionPlusOne - 1`

#### enum `EAvaRundownServerBuildTargetType`  
`enum class EAvaRundownServerBuildTargetType : uint8`  
_L46-54_
- reflection: `UENUM()`
- desc: Build targets. This will help determine the set of features that are available.
- L48 _public enumerator_ `Unknown = 0`
- L49 _public enumerator_ `Editor`
- L50 _public enumerator_ `Game`
- L51 _public enumerator_ `Server`
- L52 _public enumerator_ `Client`
- L53 _public enumerator_ `Program`

#### enum `EAvaRundownServerEngineMode`  
`enum class EAvaRundownServerEngineMode : uint8`  
_L62-70_
- reflection: `UENUM()`
- desc: An editor build can be launched in different modes but it could also be a dedicated build target. The engine mode combined with the build target will determine the set of functionalities available.
- L64 _public enumerator_ `Unknown = 0`
- L65 _public enumerator_ `Editor`
- L66 _public enumerator_ `Game`
- L67 _public enumerator_ `Server`
- L68 _public enumerator_ `Commandlet`
- L69 _public enumerator_ `Other`

#### struct `FAvaRundownMsgBase`  
`struct FAvaRundownMsgBase`  
_L74-83_
- reflection: `USTRUCT()`
- desc: Base class for all rundown server messages.
- L82 _public member_ `int32 RequestId = INDEX_NONE;` — `UPROPERTY()` — Request Identifier (client assigned) for matching server responses with their corresponding requests.

#### struct `FAvaRundownServerMsg`  
`struct FAvaRundownServerMsg : public FAvaRundownMsgBase`  
_L93-108_
- reflection: `USTRUCT()`
- inherits: `FAvaRundownMsgBase`
- desc: This message is the default response message for all requests, unless a specific response message type is specified for the request. On success, the message will have a Verbosity of "Log" and the text may contain response payload related data. On failure, a message with Verbosity "Error" will be sent. This message's RequestId mirrors that of the corresponding request from the client.
- L101 _public member_ `FString Verbosity;` — `UPROPERTY()` — Debug, Log, Warning, Error, etc.
- L107 _public member_ `FString Text;` — `UPROPERTY()` — Message Text.

#### struct `FAvaRundownPing`  
`struct FAvaRundownPing : public FAvaRundownMsgBase`  
_L115-129_
- reflection: `USTRUCT()`
- inherits: `FAvaRundownMsgBase`
- desc: Request published by client to discover servers on the message bus. The available servers will respond with a FAvaRundownPong.
- L121 _public member_ `bool bAuto = true;` — `UPROPERTY()` — True if the request originates from an automatic timer. False if request originates from user interaction.
- L128 _public member_ `int32 RequestedApiVersion = EAvaRundownApiVersion::Unspecified;` — `UPROPERTY()` — API Version the client has been implemented against. If unspecified the server will consider the latest version is requested.

#### struct `FAvaRundownPong`  
`struct FAvaRundownPong : public FAvaRundownMsgBase`  
_L136-165_
- reflection: `USTRUCT()`
- inherits: `FAvaRundownMsgBase`
- desc: The server will send this message to the client in response to FAvaRundownPing. This is used to discover the server's entry point on the message bus.
- L143 _public member_ `bool bAuto = true;` — `UPROPERTY()` — True if it is a reply to an auto ping. Mirrors the bAuto flag from Ping message.
- L152 _public member_ `int32 ApiVersion = EAvaRundownApiVersion::Unspecified;` — `UPROPERTY()` — API Version the server will communicate with for this client. The server may honor the requested version if possible. Versions newer than server implementation will obviously not be honored either. Clients should expect an older server to reply with an older version.
- L156 _public member_ `int32 MinimumApiVersion = EAvaRundownApiVersion::Unspecified;` — `UPROPERTY()` — Minimum API Version the server implements.
- L160 _public member_ `int32 LatestApiVersion = EAvaRundownApiVersion::Unspecified;` — `UPROPERTY()` — Latest API Version the server support.
- L164 _public member_ `FString HostName;` — `UPROPERTY()` — Server Host Name

#### struct `FAvaRundownGetServerInfo`  
`struct FAvaRundownGetServerInfo : public FAvaRundownMsgBase`  
_L172-175_
- reflection: `USTRUCT()`
- inherits: `FAvaRundownMsgBase`
- desc: Requests the extended server information. Response is FAvaRundownServerInfo.

#### struct `FAvaRundownServerInfo`  
`struct FAvaRundownServerInfo : public FAvaRundownMsgBase`  
_L181-234_
- reflection: `USTRUCT()`
- inherits: `FAvaRundownMsgBase`
- desc: Extended server information.
- L187 _public member_ `int32 ApiVersion = EAvaRundownApiVersion::Unspecified;` — `UPROPERTY()` — API Version the server will communicate with for this client.
- L191 _public member_ `int32 MinimumApiVersion = EAvaRundownApiVersion::Unspecified;` — `UPROPERTY()` — Minimum API Version the server implements.
- L195 _public member_ `int32 LatestApiVersion = EAvaRundownApiVersion::Unspecified;` — `UPROPERTY()` — Latest API Version the server support.
- L199 _public member_ `FString HostName;` — `UPROPERTY()` — Server Host Name
- L203 _public member_ `uint32 EngineVersion = 0;` — `UPROPERTY()` — Holds the engine version checksum
- L207 _public member_ `FGuid InstanceId;` — `UPROPERTY()` — Application Instance Identifier.
- L210 _public member_ `EAvaRundownServerBuildTargetType InstanceBuild = EAvaRundownServerBuildTargetType::Unknown;` — `UPROPERTY()`
- L213 _public member_ `EAvaRundownServerEngineMode InstanceMode = EAvaRundownServerEngineMode::Unknown;` — `UPROPERTY()`
- L217 _public member_ `FGuid SessionId;` — `UPROPERTY()` — Holds the identifier of the session that the application belongs to.
- L221 _public member_ `FString ProjectName;` — `UPROPERTY()` — The unreal project name this server is running from.
- L225 _public member_ `FString ProjectDir;` — `UPROPERTY()` — The unreal project directory this server is running from.
- L229 _public member_ `uint32 RemoteControlHttpServerPort = 0;` — `UPROPERTY()` — Http Server Port of the remote control service.
- L233 _public member_ `uint32 RemoteControlWebSocketServerPort = 0;` — `UPROPERTY()` — WebSocket Server Port of the remote control service.

#### struct `FAvaRundownGetPlayableAssets`  
`struct FAvaRundownGetPlayableAssets : public FAvaRundownMsgBase`  
_L242-257_
- reflection: `USTRUCT()`
- inherits: `FAvaRundownMsgBase`
- desc: Requests a list of playable assets that can be added to a rundown template. Response is FAvaRundownPlayableAssets.
- L250 _public member_ `FString Query;` — `UPROPERTY()` — The search query which will be compared with the asset names.
- L256 _public member_ `int32 Limit = 0;` — `UPROPERTY()` — The maximum number of search results returned.

#### struct `FAvaRundownPlayableAssets`  
`struct FAvaRundownPlayableAssets : public FAvaRundownMsgBase`  
_L264-270_
- reflection: `USTRUCT()`
- inherits: `FAvaRundownMsgBase`
- desc: List of all available playable assets on the server. Expected Response from FAvaRundownGetPlayableAssets.
- L269 _public member_ `TArray<FSoftObjectPath> Assets;` — `UPROPERTY()`

#### struct `FAvaRundownGetRundowns`  
`struct FAvaRundownGetRundowns : public FAvaRundownMsgBase`  
_L277-280_
- reflection: `USTRUCT()`
- inherits: `FAvaRundownMsgBase`
- desc: Requests the list of rundowns that can be opened on the current server. Response is FAvaRundownRundowns.

#### struct `FAvaRundownRundowns`  
`struct FAvaRundownRundowns : public FAvaRundownMsgBase`  
_L287-297_
- reflection: `USTRUCT()`
- inherits: `FAvaRundownMsgBase`
- desc: List of all rundowns. Expected Response from FAvaRundownGetRundowns.
- L296 _public member_ `TArray<FString> Rundowns;` — `UPROPERTY()` — List of Rundown asset paths in format: [PackagePath]/[AssetName].[AssetName]

#### struct `FAvaRundownLoadRundown`  
`struct FAvaRundownLoadRundown : public FAvaRundownMsgBase`  
_L310-320_
- reflection: `USTRUCT()`
- inherits: `FAvaRundownMsgBase`
- desc: Loads the given rundown for playback operations. This will also open an associated playback context. Only one rundown can be opened for playback at a time by the rundown server. If another rundown is opened, the previous one will be closed and all currently playing pages stopped, unless the rundown editor is opened. The rundown editor will keep the playback context alive. If the path is empty, nothing will be done and the server will reply with a FAvaRundownServerMsg message indicating which rundown is currently loaded.
- L319 _public member_ `FString Rundown;` — `UPROPERTY()` — Rundown asset path: [PackagePath]/[AssetName].[AssetName]

#### struct `FAvaRundownCreateRundown`  
`struct FAvaRundownCreateRundown : public FAvaRundownMsgBase`  
_L332-351_
- reflection: `USTRUCT()`
- inherits: `FAvaRundownMsgBase`
- desc: Creates a new rundown asset. The full package name is going to be: [PackagePath]/[AssetName] The full asset path is going to be: [PackagePath]/[AssetName].[AssetName] For all other requests, the rundown reference is the full asset path. Response is FAvaRundownServerMsg.
- L339 _public member_ `FString PackagePath;` — `UPROPERTY()` — Package path (excluding the package name)
- L343 _public member_ `FString AssetName;` — `UPROPERTY()` — Asset Name.
- L350 _public member_ `bool bTransient = true;` — `UPROPERTY()` — Create the rundown as a transient object. @remark For game builds, the created rundown will always be transient, regardless of this flag.

#### struct `FAvaRundownDeleteRundown`  
`struct FAvaRundownDeleteRundown : public FAvaRundownMsgBase`  
_L359-367_
- reflection: `USTRUCT()`
- inherits: `FAvaRundownMsgBase`
- desc: Deletes an existing rundown. Response is FAvaRundownServerMsg.
- L366 _public member_ `FString Rundown;` — `UPROPERTY()` — Rundown asset path: [PackagePath]/[AssetName].[AssetName]

#### struct `FAvaRundownImportRundown`  
`struct FAvaRundownImportRundown : public FAvaRundownMsgBase`  
_L373-393_
- reflection: `USTRUCT()`
- inherits: `FAvaRundownMsgBase`
- desc: Imports rundown from json data or file.
- L380 _public member_ `FString Rundown;` — `UPROPERTY()` — Rundown asset path: [PackagePath]/[AssetName].[AssetName]
- L386 _public member_ `FString RundownFile;` — `UPROPERTY()` — If specified, this is a server local path to a json file from which the rundown will be imported.
- L392 _public member_ `FString RundownData;` — `UPROPERTY()` — If specified, json data containing the rundown to import.

#### struct `FAvaRundownExportRundown`  
`struct FAvaRundownExportRundown : public FAvaRundownMsgBase`  
_L400-412_
- reflection: `USTRUCT()`
- inherits: `FAvaRundownMsgBase`
- desc: Exports a rundown to json data or file. This command is supported in game build.
- L407 _public member_ `FString Rundown;` — `UPROPERTY()` — Rundown asset path: [PackagePath]/[AssetName].[AssetName]
- L411 _public member_ `FString RundownFile;` — `UPROPERTY()` — Optional path to a server local file where the rundown will be saved.

#### struct `FAvaRundownExportedRundown`  
`struct FAvaRundownExportedRundown : public FAvaRundownMsgBase`  
_L418-430_
- reflection: `USTRUCT()`
- inherits: `FAvaRundownMsgBase`
- desc: Server reply to FAvaRundownExportRundown containing the exported rundown.
- L425 _public member_ `FString Rundown;` — `UPROPERTY()` — Rundown asset path: [PackagePath]/[AssetName].[AssetName]
- L429 _public member_ `FString RundownData;` — `UPROPERTY()` — Exported rundown in json format.

#### struct `FAvaRundownSaveRundown`  
`struct FAvaRundownSaveRundown : public FAvaRundownMsgBase`  
_L440-452_
- reflection: `USTRUCT()`
- inherits: `FAvaRundownMsgBase`
- desc: Requests that the given rundown be saved to disk. The rundown asset must have been loaded, either by an edit command or playback, prior to this command. Unloaded assets will not be loaded by this command. This command is not supported in game builds.
- L447 _public member_ `FString Rundown;` — `UPROPERTY()` — Rundown asset path: [PackagePath]/[AssetName].[AssetName]
- L451 _public member_ `bool bOnlyIfIsDirty = false;` — `UPROPERTY()` — The save command will be executed only if the asset package is dirty.

#### struct `FAvaRundownPlaybackContextChanged`  
`struct FAvaRundownPlaybackContextChanged : public FAvaRundownMsgBase`  
_L458-474_
- reflection: `USTRUCT()`
- inherits: `FAvaRundownMsgBase`
- desc: Rundown specific events broadcast by the server to help status display or related contexts in control applications.
- L467 _public member_ `FString PreviousRundown;` — `UPROPERTY()` — Previous rundown (can be empty).
- L473 _public member_ `FString NewRundown;` — `UPROPERTY()` — New current rundown (can be empty).

#### struct `FAvaRundownGetPages`  
`struct FAvaRundownGetPages : public FAvaRundownMsgBase`  
_L480-487_
- reflection: `USTRUCT()`
- inherits: `FAvaRundownMsgBase`
- desc: Requests the list of pages from the given rundown.
- L486 _public member_ `FString Rundown;` — `UPROPERTY()` — Rundown asset path: [PackagePath]/[AssetName].[AssetName]

#### struct `FAvaRundownCreatePageIdGeneratorParams`  
`struct FAvaRundownCreatePageIdGeneratorParams`  
_L495-510_
- reflection: `USTRUCT()`
- desc: Defines the parameters for the page id generator algorithm. The Id generator uses a sequence strategy to search for an unused id. It is defined by a starting id and a search direction.
- L501 _public member_ `int32 ReferenceId = FAvaRundownPage::InvalidPageId;` — `UPROPERTY()` — Starting Id for the search.
- L509 _public member_ `int32 Increment = 1;` — `UPROPERTY()` — @brief (Initial) Search increment. @remark For negative increment search, the limit of the search space can be reached. If no unique id is found, the search will continue in the positive direction instead.

#### struct `FAvaRundownCreatePage`  
`struct FAvaRundownCreatePage : public FAvaRundownMsgBase`  
_L516-531_
- reflection: `USTRUCT()`
- inherits: `FAvaRundownMsgBase`
- desc: Requests a new page be created from the specified template in the given rundown.
- L522 _public member_ `FString Rundown;` — `UPROPERTY()` — Rundown asset path: [PackagePath]/[AssetName].[AssetName]
- L526 _public member_ `FAvaRundownCreatePageIdGeneratorParams IdGeneratorParams;` — `UPROPERTY()` — Defines the parameters for the page id generator algorithm.
- L530 _public member_ `int32 TemplateId = FAvaRundownPage::InvalidPageId;` — `UPROPERTY()` — Specifies the template for the newly created page.

#### struct `FAvaRundownDeletePage`  
`struct FAvaRundownDeletePage : public FAvaRundownMsgBase`  
_L537-548_
- reflection: `USTRUCT()`
- inherits: `FAvaRundownMsgBase`
- desc: Requests the page be deleted from the given rundown.
- L543 _public member_ `FString Rundown;` — `UPROPERTY()` — Rundown asset path: [PackagePath]/[AssetName].[AssetName]
- L547 _public member_ `int32 PageId = FAvaRundownPage::InvalidPageId;` — `UPROPERTY()` — Id of the page to be deleted.

#### struct `FAvaRundownCreateTemplate`  
`struct FAvaRundownCreateTemplate : public FAvaRundownMsgBase`  
_L557-572_
- reflection: `USTRUCT()`
- inherits: `FAvaRundownMsgBase`
- desc: Requests the creation of a new template. If successful, the response is FAvaRundownServerMsg with a "Template [Id] Created" text. The id of the created template can be parsed from that message's text. Also a secondary FAvaRundownPageListChanged event with added template id will be sent.
- L563 _public member_ `FString Rundown;` — `UPROPERTY()` — Rundown asset path: [PackagePath]/[AssetName].[AssetName]
- L567 _public member_ `FAvaRundownCreatePageIdGeneratorParams IdGeneratorParams;` — `UPROPERTY()` — Defines the parameters for the page id generator algorithm.
- L571 _public member_ `FString AssetPath;` — `UPROPERTY()` — Specifies the asset path to assign to the template.

#### struct `FAvaRundownCreateComboTemplate`  
`struct FAvaRundownCreateComboTemplate : public FAvaRundownMsgBase`  
_L583-598_
- reflection: `USTRUCT()`
- inherits: `FAvaRundownMsgBase`
- desc: Requests the creation of a new combo template. If successful, the response is FAvaRundownServerMsg with a "Template [Id] Created" text. The id of the created template can be parsed from that message's text. Also a secondary FAvaRundownPageListChanged event with added template id will be sent. @remark A combination template can only be created using transition logic templates that are in different transition layers.
- L589 _public member_ `FString Rundown;` — `UPROPERTY()` — Rundown asset path: [PackagePath]/[AssetName].[AssetName]
- L593 _public member_ `FAvaRundownCreatePageIdGeneratorParams IdGeneratorParams;` — `UPROPERTY()` — Defines the parameters for the page id generator algorithm.
- L597 _public member_ `TArray<int32> CombinedTemplateIds;` — `UPROPERTY()` — Specifies the template ids that are combined.

#### struct `FAvaRundownDeleteTemplate`  
`struct FAvaRundownDeleteTemplate : public FAvaRundownMsgBase`  
_L602-613_
- reflection: `USTRUCT()`
- inherits: `FAvaRundownMsgBase`
- desc: Requests deletion of the given template.
- L608 _public member_ `FString Rundown;` — `UPROPERTY()` — Rundown asset path: [PackagePath]/[AssetName].[AssetName]
- L612 _public member_ `int32 PageId = FAvaRundownPage::InvalidPageId;` — `UPROPERTY()` — Specifies the *template* id to delete.

#### struct `FAvaRundownChangeTemplateBP`  
`struct FAvaRundownChangeTemplateBP : public FAvaRundownMsgBase`  
_L619-638_
- reflection: `USTRUCT()`
- inherits: `FAvaRundownMsgBase`
- desc: Sets the Page's template asset. This applies to template pages only.
- L625 _public member_ `FString Rundown;` — `UPROPERTY()` — Rundown asset path: [PackagePath]/[AssetName].[AssetName]
- L629 _public member_ `int32 TemplateId = FAvaRundownPage::InvalidPageId;` — `UPROPERTY()` — Specifies the template id to modify.
- L633 _public member_ `FString AssetPath;` — `UPROPERTY()` — Specifies the asset path to assign.
- L637 _public member_ `bool bReimport = false;` — `UPROPERTY()` — If true, the asset will be re-imported and the template information will be refresh from the source asset.

#### struct `FAvaRundownPageInfo`  
`struct FAvaRundownPageInfo`  
_L642-715_
- reflection: `USTRUCT()`
- desc: Page Information
- L648 _public member_ `int32 PageId = FAvaRundownPage::InvalidPageId;` — `UPROPERTY()` — Unique identifier for the page within the rundown.
- L655 _public member_ `FString PageName;` — `UPROPERTY()` — Short page name, usually the asset name for templates. It is displayed as the page description if there is no page summary or user friendly name specified.
- L662 _public member_ `FString PageSummary;` — `UPROPERTY()` — Summary is generated from the remote control values for this page. It is displayed as the page description if there is no user friendly name specified.
- L666 _public member_ `FString FriendlyName;` — `UPROPERTY()` — User editable page description. If not empty, this should be used as the page description.
- L670 _public member_ `bool IsTemplate = false;` — `UPROPERTY()` — Indicates if the page is a template (true) or an instance (false).
- L674 _public member_ `int32 TemplateId = FAvaRundownPage::InvalidPageId;` — `UPROPERTY()` — Page Instance property: Template Id for this page.
- L678 _public member_ `TArray<int32> CombinedTemplateIds;` — `UPROPERTY()` — Template property: For combination template, lists the templates that are combined.
- L682 _public member_ `FSoftObjectPath AssetPath;` — `UPROPERTY()` — Template property: playable asset path for this template.
- L689 _public member_ `TArray<FAvaRundownChannelPageStatus> Statuses;` — `UPROPERTY()` — List of page channel statuses. There will be an entry for each channel the page is playing/previewing in.
- L693 _public member_ `FString TransitionLayerName;` — `UPROPERTY()` — Transition Layer Name (indicates the page has transition logic).
- L697 _public member_ `bool bTransitionLogicEnabled = false;` — `UPROPERTY()` — Indicate if the template asset has transition logic.
- L701 _public member_ `TArray<FAvaRundownPageCommandData> Commands;` — `UPROPERTY()` — Page Commands that can be executed when playing this page.
- L704 _public member_ `FString OutputChannel;` — `UPROPERTY()`
- L708 _public member_ `bool bIsEnabled = false;` — `UPROPERTY()` — Specifies if the page is enabled (i.e. can be played).
- L714 _public member_ `bool bIsPlaying = false;` — `UPROPERTY()` — Indicates if the page is currently playing in it's program channel.

#### struct `FAvaRundownPages`  
`struct FAvaRundownPages : public FAvaRundownMsgBase`  
_L721-728_
- reflection: `USTRUCT()`
- inherits: `FAvaRundownMsgBase`
- desc: List of pages from the current rundown.
- L727 _public member_ `TArray<FAvaRundownPageInfo> Pages;` — `UPROPERTY()` — List of page descriptors

#### struct `FAvaRundownGetPageDetails`  
`struct FAvaRundownGetPageDetails : public FAvaRundownMsgBase`  
_L735-752_
- reflection: `USTRUCT()`
- inherits: `FAvaRundownMsgBase`
- desc: Requests the page details from the given rundown. Response is FAvaRundownPageDetails.
- L742 _public member_ `FString Rundown;` — `UPROPERTY()` — Rundown asset path: [PackagePath]/[AssetName].[AssetName]
- L746 _public member_ `int32 PageId = FAvaRundownPage::InvalidPageId;` — `UPROPERTY()` — Specified the requested page id.
- L751 _public member_ `bool bLoadRemoteControlPreset = false;` — `UPROPERTY()` — This will request that a managed asset instance gets loaded to be accessible through WebRC.

#### struct `FAvaRundownPageDetails`  
`struct FAvaRundownPageDetails : public FAvaRundownMsgBase`  
_L758-802_
- reflection: `USTRUCT()`
- inherits: `FAvaRundownMsgBase`
- desc: Server response to FAvaRundownGetPageDetails request.
- L765 _public member_ `FString Rundown;` — `UPROPERTY()` — Rundown asset path: [PackagePath]/[AssetName].[AssetName]
- L769 _public member_ `FAvaRundownPageInfo PageInfo;` — `UPROPERTY()` — Page Information.
- L773 _public member_ `FAvaPlayableRemoteControlValues RemoteControlValues;` — `UPROPERTY()` — Remote Control Values for this page.
- L780 _public member_ `FString RemoteControlPresetName;` — `UPROPERTY()` — Name of the remote control preset to resolve through WebRC API. In case of combo page, this is the first sub-page only. See RemoteControlPresetNames for all the names in that case.
- L787 _public member_ `FString RemoteControlPresetId;` — `UPROPERTY()` — Uuid of the remote control preset to resolve through WebRC API. In case of combo page, this is the first sub-page only. See RemoteControlPresetIds for all the uuids in that case.
- L794 _public member_ `TArray<FString> RemoteControlPresetNames;` — `UPROPERTY()` — This list will be populated with the names of the remote control preset of each sub-page in case of a combo page. The provided Uuids can be used to with the WebRC API.
- L801 _public member_ `TArray<FString> RemoteControlPresetIds;` — `UPROPERTY()` — This list will be populated with the uuid of the remote control preset of each sub-page in case of a combo page. The provided uuids can be used to with the WebRC API.

#### struct `FAvaRundownPagesStatuses`  
`struct FAvaRundownPagesStatuses : public FAvaRundownMsgBase`  
_L808-820_
- reflection: `USTRUCT()`
- inherits: `FAvaRundownMsgBase`
- desc: Event sent when a page status changes.
- L815 _public member_ `FString Rundown;` — `UPROPERTY()` — Rundown asset path: [PackagePath]/[AssetName].[AssetName]
- L819 _public member_ `FAvaRundownPageInfo PageInfo;` — `UPROPERTY()` — Page Information.

#### struct `FAvaRundownPageListChanged`  
`struct FAvaRundownPageListChanged : public FAvaRundownMsgBase`  
_L826-859_
- reflection: `USTRUCT()`
- inherits: `FAvaRundownMsgBase`
- desc: Event sent when a page list (can be templates, pages or page views) has been modified.
- L832 _public member_ `FString Rundown;` — `UPROPERTY()` — Rundown asset path: [PackagePath]/[AssetName].[AssetName]
- L836 _public member_ `EAvaRundownPageListType ListType = EAvaRundownPageListType::Instance;` — `UPROPERTY()` — Specifies which page list has been modified.
- L840 _public member_ `FGuid SubListId;` — `UPROPERTY()` — Specifies the uuid of the page view, in case the event concerns a page view.
- L854 _public member_ `uint8 ChangeType = 0;` — `UPROPERTY()` — Bitfield value indicating what has changed: - bit 0: Added Pages - bit 1: Remove Pages - bit 2: Page Id Renumbered - bit 3: Sublist added or removed - bit 4: Sublist renamed - bit 5: Page View reordered See EAvaPageListChange flags.
- L858 _public member_ `TArray<int32> AffectedPages;` — `UPROPERTY()` — List of page Ids affected by this event.

#### struct `FAvaRundownPageBlueprintChanged`  
`struct FAvaRundownPageBlueprintChanged : public FAvaRundownMsgBase`  
_L866-881_
- reflection: `USTRUCT()`
- inherits: `FAvaRundownMsgBase`
- desc: Event sent when a page's asset is modified. Note: this applies to templates only.
- L872 _public member_ `FString Rundown;` — `UPROPERTY()` — Rundown asset path: [PackagePath]/[AssetName].[AssetName]
- L876 _public member_ `int32 PageId = FAvaRundownPage::InvalidPageId;` — `UPROPERTY()` — Specified the modified page id.
- L880 _public member_ `FString BlueprintPath;` — `UPROPERTY()` — Asset the page is currently assigned to (post modification).

#### struct `FAvaRundownPageChannelChanged`  
`struct FAvaRundownPageChannelChanged : public FAvaRundownMsgBase`  
_L887-902_
- reflection: `USTRUCT()`
- inherits: `FAvaRundownMsgBase`
- desc: Event sent when a page's channel is modified.
- L893 _public member_ `FString Rundown;` — `UPROPERTY()` — Rundown asset path: [PackagePath]/[AssetName].[AssetName]
- L897 _public member_ `int32 PageId = FAvaRundownPage::InvalidPageId;` — `UPROPERTY()` — Specified the modified page id.
- L901 _public member_ `FString ChannelName;` — `UPROPERTY()` — Channel the page is currently assigned to (post modification).

#### struct `FAvaRundownPageNameChanged`  
`struct FAvaRundownPageNameChanged : public FAvaRundownMsgBase`  
_L908-927_
- reflection: `USTRUCT()`
- inherits: `FAvaRundownMsgBase`
- desc: Event sent when a page's name is modified.
- L914 _public member_ `FString Rundown;` — `UPROPERTY()` — Rundown asset path: [PackagePath]/[AssetName].[AssetName]
- L918 _public member_ `int32 PageId = FAvaRundownPage::InvalidPageId;` — `UPROPERTY()` — Specified the modified page id.
- L922 _public member_ `FString PageName;` — `UPROPERTY()` — new page name is currently assigned to (post modification).
- L926 _public member_ `bool bFriendlyName = true;` — `UPROPERTY()` — Indicate whether the name or friendly name that changed.

#### struct `FAvaRundownPageAnimSettingsChanged`  
`struct FAvaRundownPageAnimSettingsChanged : public FAvaRundownMsgBase`  
_L933-944_
- reflection: `USTRUCT()`
- inherits: `FAvaRundownMsgBase`
- desc: Event sent when a page's animation settings is modified.
- L939 _public member_ `FString Rundown;` — `UPROPERTY()` — Rundown asset path: [PackagePath]/[AssetName].[AssetName]
- L943 _public member_ `int32 PageId = FAvaRundownPage::InvalidPageId;` — `UPROPERTY()` — Specified the modified page id.

#### struct `FAvaRundownPageChangeChannel`  
`struct FAvaRundownPageChangeChannel : public FAvaRundownMsgBase`  
_L952-967_
- reflection: `USTRUCT()`
- inherits: `FAvaRundownMsgBase`
- desc: Sets the channel of the given page. The page must be valid (and not a template) and the channel must exist in the current profile. Along with the corresponding response, this will also trigger a FAvaRundownPageChannelChanged event.
- L958 _public member_ `FString Rundown;` — `UPROPERTY()` — Rundown asset path: [PackagePath]/[AssetName].[AssetName]
- L962 _public member_ `int32 PageId = FAvaRundownPage::InvalidPageId;` — `UPROPERTY()` — Specifies the page that will be modified.
- L966 _public member_ `FString ChannelName;` — `UPROPERTY()` — Specifies a valid channel to set for the specified page.

#### struct `FAvaRundownChangePageName`  
`struct FAvaRundownChangePageName : public FAvaRundownMsgBase`  
_L976-999_
- reflection: `USTRUCT()`
- inherits: `FAvaRundownMsgBase`
- desc: Sets page name. Works for template or instance pages. By default, the command will set the page's "friendly" name as it is the one used for display purposes. The page name is reserved for native code uses. Along with the corresponding response, this will also trigger a FAvaRundownPageNameChanged event.
- L982 _public member_ `FString Rundown;` — `UPROPERTY()` — Rundown asset path: [PackagePath]/[AssetName].[AssetName]
- L986 _public member_ `int32 PageId = FAvaRundownPage::InvalidPageId;` — `UPROPERTY()` — Specifies the page or template that will be modified.
- L990 _public member_ `FString PageName;` — `UPROPERTY()` — Specifies the new page name.
- L998 _public member_ `bool bSetFriendlyName = true;` — `UPROPERTY()` — If true, the page's friendly name will be set. The page name is usually set by the native code. For display purposes, it is preferable to use the "friendly" name.

#### struct `FAvaRundownUpdatePageFromRCP`  
`struct FAvaRundownUpdatePageFromRCP : public FAvaRundownMsgBase`  
_L1004-1012_
- reflection: `USTRUCT()`
- inherits: `FAvaRundownMsgBase`
- desc: This is a request to save the managed Remote Control Preset (RCP) back to the corresponding page values.
- L1011 _public member_ `bool bUnregister = false;` — `UPROPERTY()` — Unregister the Remote Control Preset from the WebRC.

#### enum `EAvaRundownPageActions`  
`enum class EAvaRundownPageActions`  
_L1016-1028_
- reflection: `UENUM()`
- desc: Supported Page actions for playback.
- L1018 _public enumerator_ `None UMETA(Hidden)`
- L1019 _public enumerator_ `Load`
- L1020 _public enumerator_ `Unload`
- L1021 _public enumerator_ `Play`
- L1022 _public enumerator_ `PlayNext`
- L1023 _public enumerator_ `Stop`
- L1024 _public enumerator_ `ForceStop`
- L1025 _public enumerator_ `Continue`
- L1026 _public enumerator_ `UpdateValues`
- L1027 _public enumerator_ `TakeToProgram`

#### struct `FAvaRundownPageAction`  
`struct FAvaRundownPageAction : public FAvaRundownMsgBase`  
_L1034-1045_
- reflection: `USTRUCT()`
- inherits: `FAvaRundownMsgBase`
- desc: Request for a program page command on the current playback rundown.
- L1040 _public member_ `int32 PageId = FAvaRundownPage::InvalidPageId;` — `UPROPERTY()` — Specifies the Page Id that is the target of this action command.
- L1044 _public member_ `EAvaRundownPageActions Action = EAvaRundownPageActions::None;` — `UPROPERTY()` — Specifies the page action to execute.

#### struct `FAvaRundownPagePreviewAction`  
`struct FAvaRundownPagePreviewAction : public FAvaRundownPageAction`  
_L1051-1058_
- reflection: `USTRUCT()`
- inherits: `FAvaRundownPageAction`
- desc: Request for a preview page command on the current playback rundown.
- L1057 _public member_ `FString PreviewChannelName;` — `UPROPERTY()` — Specifies which preview channel to use. If left empty, the rundown's default preview channel is used.

#### struct `FAvaRundownPageActions`  
`struct FAvaRundownPageActions : public FAvaRundownMsgBase`  
_L1065-1076_
- reflection: `USTRUCT()`
- inherits: `FAvaRundownMsgBase`
- desc: Command to execute a program action on multiple pages at the same time. This is necessary for pages to be part of the same transition.
- L1071 _public member_ `TArray<int32> PageIds;` — `UPROPERTY()` — Specifies a list of page Ids that are the target of this action command.
- L1075 _public member_ `EAvaRundownPageActions Action = EAvaRundownPageActions::None;` — `UPROPERTY()` — Specifies the page action to execute.

#### struct `FAvaRundownPagePreviewActions`  
`struct FAvaRundownPagePreviewActions : public FAvaRundownPageActions`  
_L1083-1090_
- reflection: `USTRUCT()`
- inherits: `FAvaRundownPageActions`
- desc: Command to execute a preview action on multiple pages at the same time. This is necessary for pages to be part of the same transition.
- L1089 _public member_ `FString PreviewChannelName;` — `UPROPERTY()` — Specifies which preview channel to use. If left empty, the rundown's default preview channel is used.

#### enum `EAvaRundownTransitionActions`  
`enum class EAvaRundownTransitionActions`  
_L1094-1099_
- reflection: `UENUM()`
- desc: Supported Transition actions for playback.
- L1096 _public enumerator_ `None UMETA(Hidden)`
- L1098 _public enumerator_ `ForceStop` — This action will forcefully stop specified transitions.

#### struct `FAvaRundownTransitionAction`  
`struct FAvaRundownTransitionAction : public FAvaRundownMsgBase`  
_L1107-1119_
- reflection: `USTRUCT()`
- inherits: `FAvaRundownMsgBase`
- desc: Command to override transition logic directly. As it currently stands, we can only have 1 transition per channel. If there is an issue with it, it may block further playback.
- L1114 _public member_ `FString ChannelName;` — `UPROPERTY()` — Specifies the channel that is the target of this action command.
- L1118 _public member_ `EAvaRundownTransitionActions Action = EAvaRundownTransitionActions::None;` — `UPROPERTY()` — Specifies the page transition action to execute.

#### enum `EAvaRundownTransitionLayerActions`  
`enum class EAvaRundownTransitionLayerActions`  
_L1123-1130_
- reflection: `UENUM()`
- desc: Supported Page Logic Layer actions for playback.
- L1125 _public enumerator_ `None UMETA(Hidden)`
- L1127 _public enumerator_ `Stop` — Trigger the out transition for the specified layer.
- L1129 _public enumerator_ `ForceStop` — Forcefully stop, without transition, pages on the specified layer.

#### struct `FAvaRundownTransitionLayerAction`  
`struct FAvaRundownTransitionLayerAction : public FAvaRundownMsgBase`  
_L1136-1152_
- reflection: `USTRUCT()`
- inherits: `FAvaRundownMsgBase`
- desc: Command to override transition logic.
- L1143 _public member_ `FString ChannelName;` — `UPROPERTY()` — Specifies the channel that is the target of this action command.
- L1147 _public member_ `TArray<FString> LayerNames;` — `UPROPERTY()` — Specifies the transition logic layers for this action command.
- L1151 _public member_ `EAvaRundownTransitionLayerActions Action = EAvaRundownTransitionLayerActions::None;` — `UPROPERTY()` — Specifies the page layer action to execute.

#### struct `FAvaRundownPageSequenceEvent`  
`struct FAvaRundownPageSequenceEvent : public FAvaRundownMsgBase`  
_L1158-1185_
- reflection: `USTRUCT()`
- inherits: `FAvaRundownMsgBase`
- desc: This message is sent by the server when a page sequence event occurs.
- L1164 _public member_ `FString Channel;` — `UPROPERTY()` — Specifies the broadcast channel the event occurred in.
- L1168 _public member_ `int32 PageId = FAvaRundownPage::InvalidPageId;` — `UPROPERTY()` — Page Id associated with this event.
- L1172 _public member_ `FGuid InstanceId;` — `UPROPERTY()` — Playable Instance uuid.
- L1176 _public member_ `FString AssetPath;` — `UPROPERTY()` — Full asset path: /PackagePath/PackageName.AssetName
- L1180 _public member_ `FString SequenceLabel;` — `UPROPERTY()` — Specifies the label used to identify the sequence.
- L1184 _public member_ `EAvaPlayableSequenceEventType Event = EAvaPlayableSequenceEventType::None;` — `UPROPERTY()` — Started, Paused, Finished

#### enum `EAvaRundownPageTransitionEvents`  
`enum class EAvaRundownPageTransitionEvents`  
_L1188-1193_
- reflection: `UENUM()`
- L1190 _public enumerator_ `None UMETA(Hidden)`
- L1191 _public enumerator_ `Started`
- L1192 _public enumerator_ `Finished`

#### struct `FAvaRundownPageTransitionEvent`  
`struct FAvaRundownPageTransitionEvent : public FAvaRundownMsgBase`  
_L1199-1226_
- reflection: `USTRUCT()`
- inherits: `FAvaRundownMsgBase`
- desc: This message is sent by the server when a page transition event occurs.
- L1205 _public member_ `FString Channel;` — `UPROPERTY()` — Specifies the broadcast channel the event occurred in.
- L1209 _public member_ `FGuid TransitionId;` — `UPROPERTY()` — UUID of the transition.
- L1213 _public member_ `TArray<int32> EnteringPageIds;` — `UPROPERTY()` — Pages that are entering the scene during this transition.
- L1217 _public member_ `TArray<int32> PlayingPageIds;` — `UPROPERTY()` — Pages that are already in the scene. May get kicked out or change during this transition.
- L1221 _public member_ `TArray<int32> ExitingPageIds;` — `UPROPERTY()` — Pages that are requested to exit the scene during this transition. Typically part of a "Take Out" transition.
- L1225 _public member_ `EAvaRundownPageTransitionEvents Event = EAvaRundownPageTransitionEvents::None;` — `UPROPERTY()` — Started, Finished

#### struct `FAvaRundownGetProfiles`  
`struct FAvaRundownGetProfiles : public FAvaRundownMsgBase`  
_L1233-1236_
- reflection: `USTRUCT()`
- inherits: `FAvaRundownMsgBase`
- desc: Requests a list of all profiles loaded for the current broadcast configuration. Response is FAvaRundownProfiles.

#### struct `FAvaRundownProfiles`  
`struct FAvaRundownProfiles : public FAvaRundownMsgBase`  
_L1243-1254_
- reflection: `USTRUCT()`
- inherits: `FAvaRundownMsgBase`
- desc: Response to FAvaRundownGetProfiles. Contains the list of all profiles in the broadcast configuration.
- L1249 _public member_ `TArray<FString> Profiles;` — `UPROPERTY()` — List of all profiles.
- L1253 _public member_ `FString CurrentProfile;` — `UPROPERTY()` — Current Active Profile.

#### struct `FAvaRundownCreateProfile`  
`struct FAvaRundownCreateProfile : public FAvaRundownMsgBase`  
_L1261-1275_
- reflection: `USTRUCT()`
- inherits: `FAvaRundownMsgBase`
- desc: Creates a new empty profile with the given name. Fails if the profile already exist.
- L1267 _public member_ `FString ProfileName;` — `UPROPERTY()` — Name to be given to the newly created profile.
- L1274 _public member_ `bool bMakeCurrent = true;` — `UPROPERTY()` — If true the created profile is also made "current". Equivalent to FAvaRundownSetCurrentProfile.

#### struct `FAvaRundownDuplicateProfile`  
`struct FAvaRundownDuplicateProfile : public FAvaRundownMsgBase`  
_L1283-1301_
- reflection: `USTRUCT()`
- inherits: `FAvaRundownMsgBase`
- desc: Duplicates an existing profile. Fails if the new profile name already exist. Fails if the source profile does not exist.
- L1289 _public member_ `FString SourceProfileName;` — `UPROPERTY()` — Specifies the existing profile to be duplicated.
- L1293 _public member_ `FString NewProfileName;` — `UPROPERTY()` — Specifies the name of the new profile to be created.
- L1300 _public member_ `bool bMakeCurrent = true;` — `UPROPERTY()` — If true the created profile is also made "current". Equivalent to FAvaRundownSetCurrentProfile.

#### struct `FAvaRundownRenameProfile`  
`struct FAvaRundownRenameProfile : public FAvaRundownMsgBase`  
_L1307-1318_
- reflection: `USTRUCT()`
- inherits: `FAvaRundownMsgBase`
- desc: Renames an existing profile.
- L1313 _public member_ `FString OldProfileName;` — `UPROPERTY()` — Specifies the name of the existing profile to be renamed.
- L1317 _public member_ `FString NewProfileName;` — `UPROPERTY()` — Specifies the new name.

#### struct `FAvaRundownDeleteProfile`  
`struct FAvaRundownDeleteProfile : public FAvaRundownMsgBase`  
_L1325-1332_
- reflection: `USTRUCT()`
- inherits: `FAvaRundownMsgBase`
- desc: Deletes the specified profile. Fails if profile to be deleted is the current profile.
- L1331 _public member_ `FString ProfileName;` — `UPROPERTY()` — Specifies the target profile.

#### struct `FAvaRundownSetCurrentProfile`  
`struct FAvaRundownSetCurrentProfile : public FAvaRundownMsgBase`  
_L1340-1347_
- reflection: `USTRUCT()`
- inherits: `FAvaRundownMsgBase`
- desc: Specified profile is made "current". The current profile becomes the context for all other broadcasts commands. Fails if some channels are currently broadcasting.
- L1346 _public member_ `FString ProfileName;` — `UPROPERTY()` — Specifies the requested profile.

#### struct `FAvaRundownOutputDeviceItem`  
`struct FAvaRundownOutputDeviceItem`  
_L1353-1386_
- reflection: `USTRUCT()`
- desc: Output Device information
- L1362 _public member_ `FString Name;` — `UPROPERTY()` — Specifies the device name. This is used as "MediaOutputName" in FAvaRundownAddChannelDevice and FAvaRundownEditChannelDevice.
- L1366 _public member_ `FAvaBroadcastMediaOutputInfo OutputInfo;` — `UPROPERTY()` — Extra information about the device.
- L1370 _public member_ `EAvaBroadcastOutputState OutputState = EAvaBroadcastOutputState::Invalid;` — `UPROPERTY()` — Specifies the status of the output device.
- L1374 _public member_ `EAvaBroadcastIssueSeverity IssueSeverity = EAvaBroadcastIssueSeverity::None;` — `UPROPERTY()` — In case the device is live, this extra status indicates if the device is operating normally.
- L1378 _public member_ `TArray<FString> IssueMessages;` — `UPROPERTY()` — List of errors or warnings.
- L1385 _public member_ `FString Data;` — `UPROPERTY()` — Raw Json string representing a serialized UMediaOutput. This data can be edited, then used in FAvaRundownEditChannelDevice.

#### struct `FAvaRundownOutputClassItem`  
`struct FAvaRundownOutputClassItem`  
_L1392-1413_
- reflection: `USTRUCT()`
- desc: Output Device Class Information
- L1398 _public member_ `FString Name;` — `UPROPERTY()` — Class name
- L1405 _public member_ `FString Server;` — `UPROPERTY()` — Name of the playback server this class was seen on. The name will be empty for the "local process" device.
- L1412 _public member_ `TArray<FAvaRundownOutputDeviceItem> Devices;` — `UPROPERTY()` — Enumeration of the available devices of this class on the given host. Note that not all classes can be enumerated.

#### struct `FAvaRundownDevicesList`  
`struct FAvaRundownDevicesList : public FAvaRundownMsgBase`  
_L1419-1428_
- reflection: `USTRUCT()`
- inherits: `FAvaRundownMsgBase`
- desc: Response to FAvaRundownGetDevices.
- L1427 _public member_ `TArray<FAvaRundownOutputClassItem> DeviceClasses;` — `UPROPERTY()` — List of Output Device Classes

#### struct `FAvaRundownGetChannel`  
`struct FAvaRundownGetChannel : public FAvaRundownMsgBase`  
_L1436-1443_
- reflection: `USTRUCT()`
- inherits: `FAvaRundownMsgBase`
- desc: Requests information (devices, status, etc) on a specified channel. Response is FAvaRundownChannelResponse.
- L1442 _public member_ `FString ChannelName;` — `UPROPERTY()` — Specifies the requested channel.

#### struct `FAvaRundownGetChannels`  
`struct FAvaRundownGetChannels : public FAvaRundownMsgBase`  
_L1451-1454_
- reflection: `USTRUCT()`
- inherits: `FAvaRundownMsgBase`
- desc: Requests information (devices, status, etc) on all channels of the current profile. Response is FAvaRundownChannels.

#### struct `FAvaRundownChannel`  
`struct FAvaRundownChannel`  
_L1458-1478_
- reflection: `USTRUCT()`
- desc: Channel Information
- L1464 _public member_ `FString Name;` — `UPROPERTY()` — Specifies the Channel Name.
- L1467 _public member_ `EAvaBroadcastChannelType Type = EAvaBroadcastChannelType::Program;` — `UPROPERTY()`
- L1470 _public member_ `EAvaBroadcastChannelState State = EAvaBroadcastChannelState::Offline;` — `UPROPERTY()`
- L1473 _public member_ `EAvaBroadcastIssueSeverity IssueSeverity = EAvaBroadcastIssueSeverity::None;` — `UPROPERTY()`
- L1477 _public member_ `TArray<FAvaRundownOutputDeviceItem> Devices;` — `UPROPERTY()` — List of devices.

#### struct `FAvaRundownChannelListChanged`  
`struct FAvaRundownChannelListChanged : public FAvaRundownMsgBase`  
_L1485-1492_
- reflection: `USTRUCT()`
- inherits: `FAvaRundownMsgBase`
- desc: This message is sent by the server if the list of channels is modified in the current profile. Channel added, removed, pinned or type (preview vs program) changed.
- L1491 _public member_ `TArray<FAvaRundownChannel> Channels;` — `UPROPERTY()` — List of channel information.

#### struct `FAvaRundownChannelResponse`  
`struct FAvaRundownChannelResponse : public FAvaRundownMsgBase`  
_L1499-1506_
- reflection: `USTRUCT()`
- inherits: `FAvaRundownMsgBase`
- desc: This message is sent by the server in response to FAvaRundownGetChannel or as an event if a channel's states, render target, devices or settings is changed.
- L1505 _public member_ `FAvaRundownChannel Channel;` — `UPROPERTY()` — Channel Information

#### struct `FAvaRundownChannels`  
`struct FAvaRundownChannels : public FAvaRundownMsgBase`  
_L1510-1517_
- reflection: `USTRUCT()`
- inherits: `FAvaRundownMsgBase`
- desc: Response to FAvaRundownGetChannels
- L1516 _public member_ `TArray<FAvaRundownChannel> Channels;` — `UPROPERTY()` — List of channel information.

#### enum `EAvaRundownAssetEvent`  
`enum class EAvaRundownAssetEvent : uint8`  
_L1523-1530_
- reflection: `UENUM()`
- desc: Generic asset event
- L1525 _public enumerator_ `Unknown = 0 UMETA(Hidden)`
- L1526 _public enumerator_ `Added`
- L1527 _public enumerator_ `Removed`

#### struct `FAvaRundownAssetsChanged`  
`struct FAvaRundownAssetsChanged : public FAvaRundownMsgBase`  
_L1536-1559_
- reflection: `USTRUCT()`
- inherits: `FAvaRundownMsgBase`
- desc: Event broadcast when an asset event occurs on the server.
- L1542 _public member_ `FString AssetName;` — `UPROPERTY()` — Asset name only, without the package path. (Keeping for legacy)
- L1546 _public member_ `FString AssetPath;` — `UPROPERTY()` — Full asset path: /PackagePath/PackageName.AssetName
- L1550 _public member_ `FString AssetClass;` — `UPROPERTY()` — Full asset class path.
- L1554 _public member_ `bool bIsPlayable = false;` — `UPROPERTY()` — true if the asset is a "playable" asset, i.e. an asset that can be set in a page's asset.
- L1558 _public member_ `EAvaRundownAssetEvent EventType = EAvaRundownAssetEvent::Unknown;` — `UPROPERTY()` — Specifies the event type, i.e. Added, Remove, etc.

#### enum `EAvaRundownChannelActions`  
`enum class EAvaRundownChannelActions`  
_L1565-1572_
- reflection: `UENUM()`
- desc: Channel broadcast actions
- L1567 _public enumerator_ `None UMETA(Hidden)`
- L1569 _public enumerator_ `Start` — Start broadcast of the specified channel(s).
- L1571 _public enumerator_ `Stop` — Stops broadcast of the specified channel(s).

#### struct `FAvaRundownChannelAction`  
`struct FAvaRundownChannelAction : public FAvaRundownMsgBase`  
_L1578-1592_
- reflection: `USTRUCT()`
- inherits: `FAvaRundownMsgBase`
- desc: Requests a broadcast action on the specified channel(s).
- L1587 _public member_ `FString ChannelName;` — `UPROPERTY()` — Specifies the target channel for the action. If left empty, the action will apply to all channels of the current profile.
- L1591 _public member_ `EAvaRundownChannelActions Action = EAvaRundownChannelActions::None;` — `UPROPERTY()` — Specifies the broadcast action to perform on the target channel(s).

#### enum `EAvaRundownChannelEditActions`  
`enum class EAvaRundownChannelEditActions`  
_L1595-1602_
- reflection: `UENUM()`
- L1597 _public enumerator_ `None UMETA(Hidden)`
- L1599 _public enumerator_ `Add` — Add new channel with given name.
- L1601 _public enumerator_ `Remove` — Removes channel with given name.

#### struct `FAvaRundownChannelEditAction`  
`struct FAvaRundownChannelEditAction : public FAvaRundownMsgBase`  
_L1606-1617_
- reflection: `USTRUCT()`
- inherits: `FAvaRundownMsgBase`
- desc: Requests an edit action on the specified channel.
- L1612 _public member_ `FString ChannelName;` — `UPROPERTY()` — Specifies the target channel for the action.
- L1616 _public member_ `EAvaRundownChannelEditActions Action = EAvaRundownChannelEditActions::None;` — `UPROPERTY()` — Specifies the edit action to perform on the target channel.

#### struct `FAvaRundownRenameChannel`  
`struct FAvaRundownRenameChannel : public FAvaRundownMsgBase`  
_L1621-1632_
- reflection: `USTRUCT()`
- inherits: `FAvaRundownMsgBase`
- desc: Requests a channel to be renamed.
- L1627 _public member_ `FString OldChannelName;` — `UPROPERTY()` — Existing channel to be renamed.
- L1631 _public member_ `FString NewChannelName;` — `UPROPERTY()` — Specifies the new channel name.

#### struct `FAvaRundownGetDevices`  
`struct FAvaRundownGetDevices : public FAvaRundownMsgBase`  
_L1641-1650_
- reflection: `USTRUCT()`
- inherits: `FAvaRundownMsgBase`
- desc: Requests a list of devices from the rundown server. The server will reply with FAvaRundownDevicesList containing the devices that can be enumerated from the local host and all connected hosts through the motion design playback service.
- L1649 _public member_ `bool bShowAllMediaOutputClasses = false;` — `UPROPERTY()` — If true, listing all media output classes on the server, even if they don't have a device provider.

#### struct `FAvaRundownAddChannelDevice`  
`struct FAvaRundownAddChannelDevice : public FAvaRundownMsgBase`  
_L1657-1675_
- reflection: `USTRUCT()`
- inherits: `FAvaRundownMsgBase`
- desc: Add an enumerated device to the given channel. This command will fail if the channel is live.
- L1663 _public member_ `FString ChannelName;` — `UPROPERTY()` — Specifies the target channel.
- L1670 _public member_ `FString MediaOutputName;` — `UPROPERTY()` — The specified name is one of the enumerated device from FAvaRundownDevicesList, FAvaRundownOutputDeviceItem::Name.
- L1674 _public member_ `bool bSaveBroadcast = true;` — `UPROPERTY()` — Save broadcast configuration after this operation (true by default).

#### struct `FAvaRundownEditChannelDevice`  
`struct FAvaRundownEditChannelDevice : public FAvaRundownMsgBase`  
_L1682-1709_
- reflection: `USTRUCT()`
- inherits: `FAvaRundownMsgBase`
- desc: Modify an existing device in the given channel. This command will fail if the channel is live.
- L1688 _public member_ `FString ChannelName;` — `UPROPERTY()` — Specifies the target channel.
- L1697 _public member_ `FString MediaOutputName;` — `UPROPERTY()` — The specified name is one of the enumerated device from FAvaRundownChannel::Devices, FAvaRundownOutputDeviceItem::Name field. Must be the instanced devices from either FAvaRundownChannels, FAvaRundownChannelResponse or FAvaRundownChannelListChanged. These names are not the same as when adding a device.
- L1704 _public member_ `FString Data;` — `UPROPERTY()` — (Modified) Device Data in the same format as FAvaRundownOutputDeviceItem::Data. See: FAvaRundownChannel, FAvaRundownDevicesList
- L1708 _public member_ `bool bSaveBroadcast = true;` — `UPROPERTY()` — Save broadcast configuration after this operation (true by default).

#### struct `FAvaRundownRemoveChannelDevice`  
`struct FAvaRundownRemoveChannelDevice : public FAvaRundownMsgBase`  
_L1716-1736_
- reflection: `USTRUCT()`
- inherits: `FAvaRundownMsgBase`
- desc: Remove an existing device from the given channel. This command will fail if the channel is live.
- L1722 _public member_ `FString ChannelName;` — `UPROPERTY()` — Specifies the target channel.
- L1731 _public member_ `FString MediaOutputName;` — `UPROPERTY()` — The specified name is one of the enumerated device from FAvaRundownChannel::Devices, FAvaRundownOutputDeviceItem::Name field. Must be the instanced devices from either FAvaRundownChannels, FAvaRundownChannelResponse or FAvaRundownChannelListChanged. These names are not the same as when adding a device.
- L1735 _public member_ `bool bSaveBroadcast = true;` — `UPROPERTY()` — Save broadcast configuration after this operation (true by default).

#### struct `FAvaRundownGetChannelImage`  
`struct FAvaRundownGetChannelImage : public FAvaRundownMsgBase`  
_L1745-1752_
- reflection: `USTRUCT()`
- inherits: `FAvaRundownMsgBase`
- desc: Captures an image from the specified channel. The captured image is 25% of the channel's resolution. Intended for preview. Response is FAvaRundownChannelImage.
- L1751 _public member_ `FString ChannelName;` — `UPROPERTY()` — Specifies the target channel.

#### struct `FAvaRundownChannelImage`  
`struct FAvaRundownChannelImage : public FAvaRundownMsgBase`  
_L1758-1768_
- reflection: `USTRUCT()`
- inherits: `FAvaRundownMsgBase`
- desc: Response to FAvaRundownGetChannelImage.
- L1767 _public member_ `TArray<uint8> ImageData;` — `UPROPERTY()` — Byte array containing the image data. Expected format is compressed jpeg.

#### struct `FAvaRundownGetChannelQualitySettings`  
`struct FAvaRundownGetChannelQualitySettings : public FAvaRundownMsgBase`  
_L1775-1782_
- reflection: `USTRUCT()`
- inherits: `FAvaRundownMsgBase`
- desc: Queries the given channel's quality settings. Response is FAvaRundownChannelQualitySettings.
- L1781 _public member_ `FString ChannelName;` — `UPROPERTY()` — Specifies the target channel.

#### struct `FAvaRundownChannelQualitySettings`  
`struct FAvaRundownChannelQualitySettings : public FAvaRundownMsgBase`  
_L1786-1797_
- reflection: `USTRUCT()`
- inherits: `FAvaRundownMsgBase`
- desc: Response to FAvaRundownGetChannelQualitySettings.
- L1792 _public member_ `FString ChannelName;` — `UPROPERTY()` — Specifies the target channel.
- L1796 _public member_ `TArray<FAvaViewportQualitySettingsFeature> Features;` — `UPROPERTY()` — Advanced viewport client engine features indexed by FEngineShowFlags names.

#### struct `FAvaRundownSetChannelQualitySettings`  
`struct FAvaRundownSetChannelQualitySettings : public FAvaRundownMsgBase`  
_L1801-1812_
- reflection: `USTRUCT()`
- inherits: `FAvaRundownMsgBase`
- desc: Sets the given channel's quality settings.
- L1807 _public member_ `FString ChannelName;` — `UPROPERTY()` — Specifies the target channel.
- L1811 _public member_ `TArray<FAvaViewportQualitySettingsFeature> Features;` — `UPROPERTY()` — Advanced viewport client engine features indexed by FEngineShowFlags names.

#### struct `FAvaRundownSaveBroadcast`  
`struct FAvaRundownSaveBroadcast : public FAvaRundownMsgBase`  
_L1818-1821_
- reflection: `USTRUCT()`
- inherits: `FAvaRundownMsgBase`
- desc: Save current broadcast configuration to a json file in the Config folder on the server.

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace EAvaRundownApiVersion`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMedia/Internal/Rundown/AvaRundownPlaybackUtils.h` (Internal)


#### struct `FAvaRundownPlaybackUtils`  
`struct FAvaRundownPlaybackUtils`  
_L9-33_
- L11 _public function_ `static bool IsPageIdValid(int32 InPageId)`
- L16 _public prototype_ `static int32 GetPageIdToPlayNext(const UAvaRundown* InRundown, const FAvaRundownPageListReference& InPageListReference, bool bInPreview, FName InPreviewChannelName);`
- L18 _public prototype_ `static TArray<int32> GetPagesToTakeToProgram(const UAvaRundown* InRundown, const TArray<int32>& InSelectedPageIds, FName InPreviewChannel = NAME_None);`
- L21 _public function_ `static void AddTagHandleUnique(TArray<FAvaTagHandle>& InTagHandles, const FAvaTagHandle& InTagHandleToAdd)` — Version of AddUnique that will only add the tag handle to the array if it does not have an ExactMatch.

#### Free symbols / members of external scopes

- L24 _function_ `` (scope `FAvaRundownPlaybackUtils::AddTagHandleUnique`)

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMedia/Internal/Rundown/AvaRundownSerializationUtils.h` (Internal)


#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace AvaMedia` (scope `UE`)
- L14 _namespace_ `namespace RundownSerializationUtils` (scope `UE::AvaMedia`)
- L16 _prototype_ `bool SaveRundownToJson(const UAvaRundown* InRundown, FArchive& InArchive, FText& OutErrorMessage);` (scope `UE::AvaMedia::RundownSerializationUtils`)
- L17 _prototype_ `bool SaveRundownToJson(const UAvaRundown* InRundown, const TCHAR* InFilepath, FText& OutErrorMessage);` (scope `UE::AvaMedia::RundownSerializationUtils`)
- L19 _prototype_ `bool LoadRundownFromJson(UAvaRundown* InRundown, FArchive& InArchive, FText& OutErrorMessage);` (scope `UE::AvaMedia::RundownSerializationUtils`)
- L20 _prototype_ `bool LoadRundownFromJson(UAvaRundown* InRundown, const TCHAR* InFilepath, FText& OutErrorMessage);` (scope `UE::AvaMedia::RundownSerializationUtils`)
- L22 _prototype_ `bool SerializeRundownPageCommandToJsonString(const FAvaRundownPageCommand* InRundownPageCommand, UStruct& InStruct, FString& OutString);` (scope `UE::AvaMedia::RundownSerializationUtils`)
- L23 _prototype_ `bool DeserializeRundownPageCommandFromJson(FAvaRundownPageCommand* InRundownPageCommand, UStruct& InStruct, const FString& InString);` (scope `UE::AvaMedia::RundownSerializationUtils`)

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMedia/Internal/Rundown/AvaRundownServerMediaOutputUtils.h` (Internal)


#### struct `FAvaRundownServerMediaOutputUtils`  
`struct FAvaRundownServerMediaOutputUtils`  
_L16-20_
- desc: Class designed to deal with Serialization and Editing of Media Output device data coming from Rundown Server It is meant to give full control and provide all information to Rundown server in a form that is usable outside of unreal engine
- L18 _public prototype_ `static FString SerializeMediaOutput(const UMediaOutput* InMediaOutput);`
- L19 _public prototype_ `static void EditMediaOutput(UMediaOutput* InMediaOutput, const FString& InDeviceData);`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMedia/Private/AvaMediaModule.h` (Private)


#### class `FAvaMediaModule`  
`class FAvaMediaModule : public IAvaMediaModule`  
_L22-179_
- inherits: `IAvaMediaModule`
- L25 _public prototype_ `FAvaMediaModule();`
- L28 _public prototype_ `virtual void StartupModule() override;`
- L29 _public prototype_ `virtual void ShutdownModule() override;`
- L30 _public function_ `virtual bool IsPlaybackClientStarted() const override`
- L31 _public prototype_ `virtual void StartPlaybackClient() override;`
- L32 _public prototype_ `virtual void StopPlaybackClient() override;`
- L33 _public function_ `virtual bool IsPlaybackServerStarted() const override`
- L34 _public prototype_ `virtual void StartPlaybackServer(const FString& InPlaybackServerName) override;`
- L35 _public prototype_ `virtual void StopPlaybackServer() override;`
- L37 _public prototype_ `virtual IAvaPlaybackClient& GetPlaybackClient() override;`
- L38 _public function_ `virtual IAvaPlaybackServer* GetPlaybackServer() const override`
- L39 _public prototype_ `virtual const IMediaIOCoreDeviceProvider* GetDeviceProvider(FName InProviderName, const FMediaIOOutputConfiguration* InMediaIOOutputConfiguration) const override;`
- L40 _public prototype_ `virtual TArray<const IMediaIOCoreDeviceProvider*> GetDeviceProvidersForServer(const FString& InServerName) const override;`
- L41 _public prototype_ `virtual FString GetServerNameForDevice(const FName& InDeviceProviderName, const FName& InDeviceName) const override;`
- L42 _public prototype_ `virtual bool IsLocalDevice(const FName& InDeviceProviderName, const FName& InDeviceName) const override;`
- L43 _public prototype_ `virtual void LaunchGameModeLocalPlaybackServer() override;`
- L44 _public prototype_ `virtual void StopGameModeLocalPlaybackServer() override;`
- L45 _public prototype_ `virtual bool IsGameModeLocalPlaybackServerLaunched() const override;`
- L46 _public prototype_ `virtual const IAvaBroadcastSettings& GetBroadcastSettings() const override;`
- L47 _public prototype_ `virtual const FAvaInstanceSettings& GetAvaInstanceSettings() const override;`
- L48 _public prototype_ `virtual const FAvaPlayableSettings& GetPlayableSettings() const override;`
- L49 _public prototype_ `virtual bool IsLocalPlaybackManagerAvailable() const override;`
- L50 _public prototype_ `virtual FAvaPlaybackManager& GetLocalPlaybackManager() const override;`
- L51 _public prototype_ `virtual bool IsManagedInstanceCacheAvailable() const override;`
- L52 _public prototype_ `virtual FAvaRundownManagedInstanceCache& GetManagedInstanceCache() const override;`
- L53 _public prototype_ `virtual bool IsAvaMediaSyncProviderFeatureAvailable() const override;`
- L54 _public prototype_ `virtual IAvaMediaSyncProvider* GetAvaMediaSyncProvider() const override;`
- L55 _public prototype_ `virtual void NotifyMapChangedEvent(UWorld* InWorld, EAvaMediaMapChangeType InEventType) override;`
- L56 _public function_ `virtual FOnAvaMediaSyncProviderChanged& GetOnAvaMediaSyncProviderChanged() override`
- L57 _public function_ `virtual FOnAvaMediaSyncPackageModified& GetOnAvaMediaSyncPackageModified() override`
- L58 _public function_ `virtual FOnMapChangedEvent& GetOnMapChangedEvent() override`
- L59 _public function_ `virtual FOnAvaPlaybackClientStarted& GetOnAvaPlaybackClientStarted() override`
- L60 _public function_ `virtual FOnAvaPlaybackClientStopped& GetAvaPlaybackClientStopped() override`
- L61 _public function_ `virtual FOnAvaPlaybackServerStarted& GetOnAvaPlaybackServerStarted() override`
- L62 _public function_ `virtual FOnAvaPlaybackServerStopped& GetAvaPlaybackServerStopped() override`
- L63 _public function_ `virtual FGetEditorViewportClient& GetEditorViewportClientDelegate() override`
- L64 _public function_ `virtual FOnRundownServerEvent& GetOnRundownServerStarted() override`
- L65 _public function_ `virtual FOnRundownServerEvent& GetOnRundownServerStopping() override`
- L66 _public function_ `virtual bool IsRundownServerStarted() const override`
- L67 _public prototype_ `virtual void StartRundownServer(const FString& InRundownServerName) override;`
- L68 _public prototype_ `virtual void StopRundownServer() override;`
- L69 _public function_ `virtual TSharedPtr<IAvaRundownServer> GetRundownServer() const override`
- L70 _public prototype_ `virtual TSharedPtr<IAvaRundownServer> MakeDetachedRundownServer(const FString& InServerName) override;`
- L71 _public prototype_ `virtual IAvaBroadcastDeviceProviderProxyManager& GetDeviceProviderProxyManager() override;`
- L72 _public prototype_ `virtual IAvaPlayableRemoteControlPresetInfoCache& GetPlayableRemoteControlPresetInfoCache() const override;`
- L76 _private prototype_ `void PostEngineInit();`
- L77 _private prototype_ `void EnginePreExit();`
- L78 _private prototype_ `void PrePIEEnded(const bool);`
- L79 _private prototype_ `void StopAllServices();`
- L80 _private prototype_ `void ConditionalCreateLocalPlaybackManager();`
- L81 _private prototype_ `void ConditionalCreateManagedInstanceCache();`
- L84 _private prototype_ `void StartRundownServerCommand(const TArray<FString>& Args);` — Command handlers
- L85 _private prototype_ `void StopRundownServerCommand(const TArray<FString>& Args);`
- L86 _private prototype_ `void StartPlaybackServerCommand(const TArray<FString>& InArgs);`
- L87 _private prototype_ `void StopPlaybackServerCommand(const TArray<FString>& InArgs);`
- L88 _private prototype_ `void StartPlaybackClientCommand(const TArray<FString>& InArgs);`
- L89 _private prototype_ `void StopPlaybackClientCommand(const TArray<FString>& InArgs);`
- L90 _private function_ `void LaunchLocalPlaybackServerCommand(const TArray<FString>& InArgs)`
- L91 _private function_ `void StopLocalPlaybackServerCommand(const TArray<FString>& InArgs)`
- L93 _private prototype_ `void StartHttpPlaybackServerCommand(const TArray<FString>& InArgs);`
- L94 _private prototype_ `void StopHttpPlaybackServerCommand(const TArray<FString>& InArgs);`
- L96 _private prototype_ `void SaveDeviceProvidersCommand(const TArray<FString>& InArgs);`
- L97 _private prototype_ `void LoadDeviceProvidersCommand(const TArray<FString>& InArgs);`
- L98 _private prototype_ `void UnloadDeviceProvidersCommand(const TArray<FString>& InArgs);`
- L99 _private prototype_ `void ListDeviceProvidersCommand(const TArray<FString>& InArgs);`
- L100 _private prototype_ `void HandleStatCommand(const TArray<FString>& InArgs);`
- L103 _private prototype_ `void OnAvaPlaybackClientConnectionEvent(IAvaPlaybackClient& InPlaybackClient, const UE::AvaPlaybackClient::Delegates::FConnectionEventArgs& InArgs);` — Event Handlers
- L107 _private member_ `FAvaBroadcastDisplayDeviceProvider AvaDisplayDeviceProvider;`
- L108 _private member_ `FAvaBroadcastDeviceProviderProxyManager DeviceProviderProxyManager;`
- L109 _private member_ `TUniquePtr<FAvaMediaSync> AvaMediaSync;`
- L111 _private member_ `TArray<IConsoleObject*> ConsoleCmds;`
- L113 _private member_ `TSharedPtr<FAvaPlayableGroupSceneViewExtension> PlayableGroupSceneViewExtension;`
- L131 _private member_ `FLocalBroadcastSettings LocalBroadcastSettings;`
- L157 _private member_ `FBroadcastSettingsBridge BroadcastSettingsBridge;`
- L159 _private member_ `TSharedPtr<FAvaRundownServer> RundownServer;`
- L160 _private member_ `TSharedPtr<FAvaPlaybackServer> AvaPlaybackServer;`
- L161 _private member_ `TSharedPtr<FAvaPlaybackClient> AvaPlaybackClient;`
- L162 _private member_ `TSharedPtr<FAvaPlaybackServerProcess> LocalPlaybackServerProcess;`
- L163 _private member_ `TSharedPtr<FAvaPlaybackManager> LocalPlaybackManager;`
- L164 _private member_ `TSharedPtr<FAvaRundownManagedInstanceCache> ManagedInstanceCache;`
- L165 _private member_ `TSharedPtr<FAvaPlayableRemoteControlPresetInfoCache> RemoteControlPresetInfoCache;`
- L167 _private member_ `TSharedPtr<FAvaPlaybackHttpServer> AvaPlaybackHttpPlaybackServer;`
- L169 _private member_ `FOnAvaMediaSyncProviderChanged OnAvaMediaSyncProviderChanged;`
- L170 _private member_ `FOnAvaMediaSyncPackageModified OnAvaMediaSyncPackageModified;`
- L171 _private member_ `FOnMapChangedEvent OnMapChangedEvent;`
- L172 _private member_ `FOnAvaPlaybackClientStarted OnAvaPlaybackClientStarted;`
- L173 _private member_ `FOnAvaPlaybackClientStopped OnAvaPlaybackClientStopped;`
- L174 _private member_ `FOnAvaPlaybackServerStarted OnAvaPlaybackServerStarted;`
- L175 _private member_ `FOnAvaPlaybackServerStopped OnAvaPlaybackServerStopped;`
- L176 _private member_ `FOnRundownServerEvent OnRundownServerStarted;`
- L177 _private member_ `FOnRundownServerEvent OnRundownServerStopping;`
- L178 _private member_ `FGetEditorViewportClient GetEditorViewportClient;`

#### class `FAvaMediaModule::FLocalBroadcastSettings`  
`class FLocalBroadcastSettings : public IAvaBroadcastSettings`  
_L118-130_
- inherits: `IAvaBroadcastSettings`
- desc: Wraps the local default UAvaMediaSettings.
- L121 _public prototype_ `virtual ~FLocalBroadcastSettings() override = default;`
- L124 _public prototype_ `virtual const FLinearColor& GetChannelClearColor() const override;`
- L125 _public prototype_ `virtual EPixelFormat GetDefaultPixelFormat() const override;`
- L126 _public prototype_ `virtual const FIntPoint& GetDefaultResolution() const override;`
- L127 _public prototype_ `virtual bool IsDrawPlaceholderWidget() const override;`
- L128 _public prototype_ `virtual const FSoftObjectPath& GetPlaceholderWidgetClass() const override;`

#### class `FAvaMediaModule::FBroadcastSettingsBridge`  
`class FBroadcastSettingsBridge final : public IAvaBroadcastSettings`  
_L138-156_
- inherits: `IAvaBroadcastSettings`
- desc: The purpose of the settings bridge is to provide a valid object even if a client disconnects, it will either switch to another client or use the local settings.
- L141 _public function_ `explicit FBroadcastSettingsBridge(FAvaMediaModule* Module) : ParentModule(Module)`
- L142 _public prototype_ `virtual ~FBroadcastSettingsBridge() override = default;`
- L145 _public prototype_ `virtual const FLinearColor& GetChannelClearColor() const override;`
- L146 _public prototype_ `virtual EPixelFormat GetDefaultPixelFormat() const override;`
- L147 _public prototype_ `virtual const FIntPoint& GetDefaultResolution() const override;`
- L148 _public prototype_ `virtual bool IsDrawPlaceholderWidget() const override;`
- L149 _public prototype_ `virtual const FSoftObjectPath& GetPlaceholderWidgetClass() const override;`
- L153 _private prototype_ `const IAvaBroadcastSettings& GetSettings() const;`
- L155 _private member_ `FAvaMediaModule* ParentModule = nullptr;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMedia/Private/AvaMediaStyle.h` (Private)


#### class `FAvaMediaStyle`  
`class FAvaMediaStyle final : public FSlateStyleSet`  
_L7-18_
- inherits: `FSlateStyleSet`
- L10 _public function_ `static FAvaMediaStyle& Get()`
- L16 _public prototype_ `FAvaMediaStyle();`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMedia/Private/Broadcast/AvaBroadcastComponent.h` (Private)


#### class `UAvaBroadcastComponent`  
`class UAvaBroadcastComponent : public UActorComponent`  
_L14-46_
- reflection: `UCLASS(BlueprintType, Blueprintable, ClassGroup = "Motion Design Broadcast", meta = (Displayname = "Motion Design Broadcast Component", BlueprintSpawnableComponent))`
- inherits: `UActorComponent`
- desc: Add this actor component to blueprint actor to expose the API to control the broadcasting of channels in game.
- L19 _public prototype_ `UAvaBroadcastComponent(const FObjectInitializer& ObjectInitializer);`
- L25 _public member_ `bool bStopBroadcastOnTearDown = true;` — `UPROPERTY(EditDefaultsOnly, Category = "Motion Design Media")` — Automatically stop broadcast when the world this component is part of is torn down.
- L33 _public prototype_ `bool StartBroadcasting(FString& OutErrorMessage);` — `UFUNCTION(BlueprintCallable, Category = "Motion Design Media")` — Start broadcasting all channels. Returns true on partial success, i.e. will be true even if some channels didn't start. Outputs error messages related to outputs that caused problems.
- L39 _public prototype_ `bool StopBroadcasting();` — `UFUNCTION(BlueprintCallable, Category = "Motion Design Media")` — Stop broadcasting all channels.
- L41 _public prototype_ `virtual void InitializeComponent() override;`
- L42 _public prototype_ `virtual void UninitializeComponent() override;`
- L45 _protected prototype_ `void OnWorldBeginTearDown(UWorld* InWorld);`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMedia/Private/Broadcast/AvaBroadcastSerialization.h` (Private)


#### struct `FAvaBroadcastSerialization`  
`struct FAvaBroadcastSerialization`  
_L9-16_
- L11 _public prototype_ `static bool SaveBroadcastToJson(const UAvaBroadcast* InBroadcast, const FString& InFilename);`
- L12 _public prototype_ `static bool LoadBroadcastFromJson(const FString& InFilename, UAvaBroadcast* OutBroadcast);`
- L14 _public prototype_ `static bool SaveBroadcastToXml(UAvaBroadcast* InBroadcast, const FString& InFilename);`
- L15 _public prototype_ `static bool LoadBroadcastFromXml(const FString& InFilename, UAvaBroadcast* OutBroadcast);`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMedia/Private/Broadcast/Channel/Slate/SAvaBroadcastPlaceholderWidget.h` (Private)


#### class `SAvaBroadcastPlaceholderWidget`  
`class SAvaBroadcastPlaceholderWidget : public SCompoundWidget`  
_L11-24_
- inherits: `SCompoundWidget`
- L14 _public function_ `SLATE_BEGIN_ARGS(SAvaBroadcastPlaceholderWidget)`
- L15 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L20 _public prototype_ `void SetChannelName(const FText& InChannelName);`
- L23 _protected member_ `TSharedPtr<STextBlock> ChannelText;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMedia/Private/Broadcast/OutputDevices/AvaBroadcastDeviceProviderProxy.h` (Private)


#### class `FAvaBroadcastDeviceProviderProxy`  
`class FAvaBroadcastDeviceProviderProxy : public IMediaIOCoreDeviceProvider`  
_L14-53_
- inherits: `IMediaIOCoreDeviceProvider`
- desc: Implements a proxy for the device provider of another system.
- L17 _public prototype_ `FAvaBroadcastDeviceProviderProxy(FAvaBroadcastDeviceProviderProxyManager* InManager, const FAvaBroadcastDeviceProviderData& InData);`
- L18 _public prototype_ `virtual ~FAvaBroadcastDeviceProviderProxy() = default;`
- L21 _public function_ `void ApplyServerName(const FString& InServerName)` — This will add the server name to all device names.
- L24 _public function_ `virtual FName GetFName() override` — IMediaIOCoreDeviceProvider
- L26 _public function_ `virtual TArray<FMediaIOConnection> GetConnections() const override`
- L27 _public function_ `virtual TArray<FMediaIOConfiguration> GetConfigurations() const override`
- L28 _public prototype_ `virtual TArray<FMediaIOConfiguration> GetConfigurations(bool bAllowInput, bool bAllowOutput) const override;`
- L29 _public function_ `virtual TArray<FMediaIODevice> GetDevices() const override`
- L30 _public prototype_ `virtual TArray<FMediaIOMode> GetModes(const FMediaIODevice& InDevice, bool bInOutput) const override;`
- L31 _public function_ `virtual TArray<FMediaIOInputConfiguration> GetInputConfigurations() const override`
- L32 _public function_ `virtual TArray<FMediaIOOutputConfiguration> GetOutputConfigurations() const override`
- L33 _public function_ `virtual TArray<FMediaIOVideoTimecodeConfiguration> GetTimecodeConfigurations() const override`
- L35 _public function_ `virtual FMediaIOConfiguration GetDefaultConfiguration() const override`
- L36 _public function_ `virtual FMediaIOMode GetDefaultMode() const override`
- L37 _public function_ `virtual FMediaIOInputConfiguration GetDefaultInputConfiguration() const override`
- L38 _public function_ `virtual FMediaIOOutputConfiguration GetDefaultOutputConfiguration() const override`
- L39 _public function_ `virtual FMediaIOVideoTimecodeConfiguration GetDefaultTimecodeConfiguration() const override`
- L42 _public function_ `virtual bool ShowInputTransportInSelector() const override`
- L43 _public function_ `virtual bool ShowOutputTransportInSelector() const override`
- L44 _public function_ `virtual bool ShowInputKeyInSelector() const override`
- L45 _public function_ `virtual bool ShowOutputKeyInSelector() const override`
- L46 _public function_ `virtual bool ShowReferenceInSelector() const override`
- L51 _private member_ `FAvaBroadcastDeviceProviderProxyManager* Manager;`
- L52 _private member_ `FAvaBroadcastDeviceProviderData Data;`

#### class `FAvaBroadcastDeviceProviderWrapper`  
`class FAvaBroadcastDeviceProviderWrapper : public IMediaIOCoreDeviceProvider`  
_L58-149_
- inherits: `IMediaIOCoreDeviceProvider`
- desc: Implements a wrapper of multiple other providers of the same device type from different systems.
- L65 _public prototype_ `FAvaBroadcastDeviceProviderWrapper(FName InName, FAvaBroadcastDeviceProviderProxyManager* InManager);` — @param InName Device Provider Name (ex: Blackmagic, AJA, etc). @param InManager Parent Manager.
- L66 _public prototype_ `virtual ~FAvaBroadcastDeviceProviderWrapper() = default;`
- L69 _public prototype_ `void AddProvider(const FString& InServerName, IMediaIOCoreDeviceProvider* InProvider, bool bInIsLocal);` — Add a provider for the given server name.
- L70 _public prototype_ `void AddProvider(const FString& InServerName, TUniquePtr<FAvaBroadcastDeviceProviderProxy>&& InProvider);`
- L73 _public prototype_ `void RemoveProvider(IMediaIOCoreDeviceProvider* InProvider);` — Removes the provider from the list.
- L74 _public prototype_ `void RemoveProvider(const FString& InServerName);`
- L76 _public function_ `bool HasLocalProvider() const`
- L78 _public function_ `IMediaIOCoreDeviceProvider* GetLocalProvider() const`
- L79 _public prototype_ `const IMediaIOCoreDeviceProvider* GetProviderForDeviceName(const FName& InDeviceName) const;`
- L80 _public prototype_ `const IMediaIOCoreDeviceProvider* GetProviderForServer(const FString& InServerName) const;`
- L85 _public prototype_ `FString GetServerNameForDevice(const FName& InDeviceName) const;` — Search in the list of all wrapped proxies to find the device and returns the corresponding server name. If the provider is local, the server name is FAvaBroadcastDeviceProviderProxyManager::LocalServerName.
- L88 _public prototype_ `bool ShouldRemove() const;` — Check if the wrapper is still wrapping something.
- L91 _public function_ `virtual FName GetFName() override` — IMediaIOCoreDeviceProvider
- L93 _public prototype_ `virtual TArray<FMediaIOConnection> GetConnections() const override;`
- L94 _public prototype_ `virtual TArray<FMediaIOConfiguration> GetConfigurations() const override;`
- L95 _public prototype_ `virtual TArray<FMediaIOConfiguration> GetConfigurations(bool bInAllowInput, bool bInAllowOutput) const override;`
- L96 _public prototype_ `virtual TArray<FMediaIODevice> GetDevices() const override;`
- L97 _public prototype_ `virtual TArray<FMediaIOMode> GetModes(const FMediaIODevice& InDevice, bool bInOutput) const override;`
- L98 _public prototype_ `virtual TArray<FMediaIOInputConfiguration> GetInputConfigurations() const override;`
- L99 _public prototype_ `virtual TArray<FMediaIOOutputConfiguration> GetOutputConfigurations() const override;`
- L100 _public prototype_ `virtual TArray<FMediaIOVideoTimecodeConfiguration> GetTimecodeConfigurations() const override;`
- L103 _public function_ `virtual FMediaIOConfiguration GetDefaultConfiguration() const override`
- L104 _public function_ `virtual FMediaIOMode GetDefaultMode() const override`
- L105 _public function_ `virtual FMediaIOInputConfiguration GetDefaultInputConfiguration() const override`
- L106 _public function_ `virtual FMediaIOOutputConfiguration GetDefaultOutputConfiguration() const override`
- L107 _public function_ `virtual FMediaIOVideoTimecodeConfiguration GetDefaultTimecodeConfiguration() const override`
- L110 _public function_ `virtual bool ShowInputTransportInSelector() const override`
- L111 _public function_ `virtual bool ShowOutputTransportInSelector() const override`
- L112 _public function_ `virtual bool ShowInputKeyInSelector() const override`
- L113 _public function_ `virtual bool ShowOutputKeyInSelector() const override`
- L114 _public function_ `virtual bool ShowReferenceInSelector() const override`
- L119 _private function_ `const IMediaIOCoreDeviceProvider* GetDefault() const`
- L124 _private function_ `void OnRemoveProvider(IMediaIOCoreDeviceProvider* InProviderToRemove)`
- L133 _private member_ `FAvaBroadcastDeviceProviderProxyManager* Manager = nullptr;`
- L135 _private member_ `FName Name;`
- L138 _private member_ `IMediaIOCoreDeviceProvider* LocalProvider = nullptr;` — We need to keep track of the local provider because it is a special snowflake.
- L140 _private member_ `FAvaBroadcastDeviceProviderProxy DummyProxy;`
- L148 _private member_ `TArray<FProviderInfo> Providers;`

#### struct `FAvaBroadcastDeviceProviderWrapper::FProviderInfo`  
`struct FProviderInfo`  
_L142-147_
- L144 _public member_ `FString ServerName;`
- L145 _public member_ `IMediaIOCoreDeviceProvider* Provider;`
- L146 _public member_ `TUniquePtr<FAvaBroadcastDeviceProviderProxy> Proxy;`

#### class `FAvaBroadcastDeviceProviderProxyManager`  
`class FAvaBroadcastDeviceProviderProxyManager : public IAvaBroadcastDeviceProviderProxyManager`  
_L151-193_
- inherits: `IAvaBroadcastDeviceProviderProxyManager`
- L154 _public function_ `virtual ~FAvaBroadcastDeviceProviderProxyManager()`
- L157 _public prototype_ `const FAvaBroadcastDeviceProviderWrapper* GetDeviceProviderWrapper(FName InDeviceProviderName) const override;`
- L158 _public prototype_ `TArray<const IMediaIOCoreDeviceProvider*> GetDeviceProvidersForServer(const FString& InServerName) const override;`
- L159 _public prototype_ `FString FindServerNameForDevice(const FName& InDeviceProviderName, const FName& InDeviceName) const override;`
- L160 _public prototype_ `bool IsLocalDevice(const FName& InDeviceProviderName, const FName& InDeviceName) const override;`
- L162 _public prototype_ `virtual void Install(const FString& InServerName, const FAvaBroadcastDeviceProviderDataList& InDeviceProviderDataList) override;`
- L163 _public prototype_ `virtual void Uninstall(const FString& InServerName) override;`
- L165 _public prototype_ `virtual TSet<FString> GetServerNames() const override;`
- L166 _public prototype_ `virtual const TSharedPtr<const FAvaBroadcastDeviceProviderDataList> GetDeviceProviderDataListForServer(const FString& InServerName) const override;`
- L167 _public function_ `virtual FString GetLocalServerName() const override`
- L171 _public prototype_ `static void ListAllProviders();` — Lists all the devices from all device providers from all the media output classes.
- L173 _public prototype_ `void TestInstall();`
- L174 _public prototype_ `void TestUninstall();`
- L177 _public prototype_ `static bool IsDevicePresent(const IMediaIOCoreDeviceProvider* InProvider, const FName& InDeviceName);` — Returns true if the given device name can be found in the device provider.
- L179 _public member_ `static FString LocalServerName;`
- L183 _private prototype_ `void ReorderWrappedLocalProviders();` — Ensure all the wrapped local providers are at the end of IMediaIOCoreModule's array.
- L186 _private prototype_ `static const IMediaIOCoreDeviceProvider* GetLocalDeviceProvider(const FName& InDeviceProviderName);` — Returns the given local provider.
- L189 _private member_ `TMap<FName, TUniquePtr<FAvaBroadcastDeviceProviderWrapper>> DeviceProviderWrappers;`
- L192 _private member_ `TMap<FString, TSharedPtr<FAvaBroadcastDeviceProviderDataList>> DeviceProviderDataListByServer;` — Keep a copy of the device provider data list last received for each server.

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMedia/Private/Broadcast/OutputDevices/AvaBroadcastDeviceProviderRegistry.h` (Private)


#### struct `FAvaBroadcastDeviceProviderRegistryData`  
`struct FAvaBroadcastDeviceProviderRegistryData`  
_L13-23_
- reflection: `USTRUCT()`
- L19 _public member_ `TMap<FName, FName> DeviceProviderNames;` — `UPROPERTY()` — Maps output class name to the device provider.
- L22 _public member_ `TMap<FName, FText> OutputClassDisplayNames;` — `UPROPERTY()`

#### class `FAvaBroadcastDeviceProviderRegistry`  
`class FAvaBroadcastDeviceProviderRegistry`  
_L25-40_
- L28 _public prototype_ `static const FAvaBroadcastDeviceProviderRegistry& Get();`
- L30 _public prototype_ `bool HasDeviceProviderName(const UClass* InMediaOutputClass) const;`
- L31 _public prototype_ `FName GetDeviceProviderName(const UClass* InMediaOutputClass) const;`
- L32 _public prototype_ `const FText& GetOutputClassDisplayText(const UClass* InMediaOutputClass) const;`
- L35 _protected prototype_ `FAvaBroadcastDeviceProviderRegistry();`
- L36 _protected prototype_ `~FAvaBroadcastDeviceProviderRegistry() = default;`
- L39 _private member_ `FAvaBroadcastDeviceProviderRegistryData Data;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMedia/Private/Broadcast/OutputDevices/AvaBroadcastDisplayDeviceManager.h` (Private)


#### struct `FAvaBroadcastDisplayAdapterInfo`  
`struct FAvaBroadcastDisplayAdapterInfo`  
_L14-22_
- desc: Contains information on physical display adapter, a.k.a. graphics card.
- L16 _public member_ `FString Description;` — ex: "Nvidia GeForce RTX ..."
- L17 _public member_ `uint32 VendorId = 0;`
- L18 _public member_ `uint32 DeviceId = 0;`
- L19 _public member_ `uint32 SubSysId = 0;`
- L20 _public member_ `uint32 Revision = 0;`
- L21 _public member_ `uint64 DedicatedVideoMemory = 0;`

#### struct `FAvaBroadcastMonitorInfo`  
`struct FAvaBroadcastMonitorInfo`  
_L29-39_
- desc: Contains info on a physical monitor connected to the display device. Similar to FMonitorInfo, except we have the adapter description and display frequency.
- L31 _public member_ `FAvaBroadcastDisplayAdapterInfo AdapterInfo;`
- L32 _public member_ `FString Name;` — ex: DISPLAY1, DISPLAY2, etc (not manufacturer name)
- L33 _public member_ `int32 Width = 0;` — Horizontal resolution in pixels.
- L34 _public member_ `int32 Height = 0;` — Vertical resolution in pixels.
- L35 _public member_ `FFrameRate DisplayFrequency = FFrameRate(0, 0);` — Default invalid.
- L36 _public member_ `FPlatformRect DisplayRect;`
- L37 _public member_ `FPlatformRect WorkArea;`
- L38 _public member_ `bool bIsPrimary = false;`

#### class `FAvaBroadcastDisplayDeviceManager`  
`class FAvaBroadcastDisplayDeviceManager`  
_L45-59_
- desc: Provides additional information on the display devices that is not available in FDisplayMetrics.
- L48 _public prototype_ `static void EnumMonitors(TArray<FAvaBroadcastMonitorInfo>& OutMonitorInfo);`
- L50 _public prototype_ `static const TArray<FAvaBroadcastMonitorInfo>& GetCachedMonitors(bool bForceUpdate = false);`
- L55 _public prototype_ `static FString GetMonitorDisplayName(const FAvaBroadcastMonitorInfo& InMonitorInfo);` — Returns a string with a display name for the monitor.
- L58 _private member_ `static TArray<FAvaBroadcastMonitorInfo> CachedMonitorInfo;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMedia/Private/Broadcast/OutputDevices/AvaBroadcastDisplayDeviceProvider.h` (Private)


#### class `FAvaBroadcastDisplayDeviceProvider`  
`class FAvaBroadcastDisplayDeviceProvider : public IMediaIOCoreDeviceProvider`  
_L20-53_
- inherits: `IMediaIOCoreDeviceProvider`
- desc: Implementation of IMediaIOCoreDeviceProvider for UAvaBroadcastDisplayMediaOutput.
- L23 _public prototype_ `static FName GetProviderName();`
- L24 _public prototype_ `static FName GetProtocolName();`
- L27 _public prototype_ `virtual FName GetFName() override;`
- L29 _public prototype_ `virtual TArray<FMediaIOConnection> GetConnections() const override;`
- L30 _public prototype_ `virtual TArray<FMediaIOConfiguration> GetConfigurations() const override;`
- L31 _public prototype_ `virtual TArray<FMediaIOConfiguration> GetConfigurations(bool bInAllowInput, bool bInAllowOutput) const override;`
- L32 _public prototype_ `virtual TArray<FMediaIODevice> GetDevices() const override;`
- L33 _public prototype_ `virtual TArray<FMediaIOMode> GetModes(const FMediaIODevice& InDevice, bool bInOutput) const override;`
- L34 _public prototype_ `virtual TArray<FMediaIOInputConfiguration> GetInputConfigurations() const override;`
- L35 _public prototype_ `virtual TArray<FMediaIOOutputConfiguration> GetOutputConfigurations() const override;`
- L36 _public prototype_ `virtual TArray<FMediaIOVideoTimecodeConfiguration> GetTimecodeConfigurations() const override;`
- L38 _public prototype_ `virtual FMediaIOConfiguration GetDefaultConfiguration() const override;`
- L39 _public prototype_ `virtual FMediaIOMode GetDefaultMode() const override;`
- L40 _public prototype_ `virtual FMediaIOInputConfiguration GetDefaultInputConfiguration() const override;`
- L41 _public prototype_ `virtual FMediaIOOutputConfiguration GetDefaultOutputConfiguration() const override;`
- L42 _public prototype_ `virtual FMediaIOVideoTimecodeConfiguration GetDefaultTimecodeConfiguration() const override;`
- L44 _public prototype_ `virtual FText ToText(const FMediaIOConfiguration& InConfiguration, bool bInIsAutoDetected = false) const override;`
- L45 _public prototype_ `virtual FText ToText(const FMediaIOConnection& InConnection) const override;`
- L46 _public prototype_ `virtual FText ToText(const FMediaIOOutputConfiguration& InConfiguration) const override;`
- L49 _public function_ `virtual bool ShowInputTransportInSelector() const override`
- L50 _public function_ `virtual bool ShowInputKeyInSelector() const override`
- L51 _public function_ `virtual bool ShowOutputKeyInSelector() const override`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMedia/Private/Broadcast/OutputDevices/AvaBroadcastDisplayMediaCapture.h` (Private)


#### class `UAvaBroadcastDisplayMediaCapture`  
`class UAvaBroadcastDisplayMediaCapture : public UMediaCapture`  
_L12-39_
- reflection: `UCLASS()`
- inherits: `UMediaCapture`
- L20 _protected function_ `virtual bool ShouldCaptureRHIResource() const override`
- L21 _protected prototype_ `virtual void OnRHIResourceCaptured_RenderingThread(FRHICommandListImmediate& RHICmdList, const FCaptureBaseData& InBaseData, TSharedPtr<FMediaCaptureUserData, ESPMode::ThreadSafe> InUserData, FTextureRHIRef InTexture) override;`
- L23 _protected prototype_ `virtual bool InitializeCapture() override;`
- L24 _protected prototype_ `virtual bool PostInitializeCaptureViewport(TSharedPtr<FSceneViewport>& InSceneViewport) override;`
- L25 _protected prototype_ `virtual bool PostInitializeCaptureRenderTarget(UTextureRenderTarget2D* InRenderTarget) override;`
- L26 _protected prototype_ `virtual void StopCaptureImpl(bool bAllowPendingFrameToBeProcess) override;`
- L29 _protected member_ `TObjectPtr<UTextureRenderTarget2D> RenderTarget;` — `UPROPERTY(Transient)`
- L32 _private prototype_ `bool StartNewCapture(const FIntPoint& InSourceTargetSize, EPixelFormat InSourceTargetFormat);`
- L34 _private member_ `FCriticalSection CaptureInstanceCriticalSection;`
- L38 _private member_ `FCaptureInstance* CaptureInstance = nullptr;` — lazy pimpl

#### Free symbols / members of external scopes

- L9 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogAvaBroadcastDisplayMedia, Log, All);`
- L9 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogAvaBroadcastDisplayMedia, Log, All);`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMedia/Private/Broadcast/OutputDevices/AvaBroadcastOutputClassItem.h` (Private)


#### class `FAvaBroadcastOutputClassItem`  
`class FAvaBroadcastOutputClassItem : public FAvaBroadcastOutputTreeItem`  
_L9-35_
- inherits: `FAvaBroadcastOutputTreeItem`
- L12 _public prototype_ `UE_AVA_INHERITS_WITH_SUPER(FAvaBroadcastOutputClassItem, FAvaBroadcastOutputTreeItem);`
- L14 _public function_ `FAvaBroadcastOutputClassItem(const TSharedPtr<FAvaBroadcastOutputTreeItem>& InParent, UClass* InOutputClass) : Super(InParent) , OutputClass(InOutputClass)`
- L20 _public function_ `UClass* GetOutputClass() const`
- L26 _public prototype_ `virtual FText GetDisplayName() const override;`
- L27 _public prototype_ `virtual const FSlateBrush* GetIconBrush() const override;`
- L28 _public prototype_ `virtual void RefreshChildren(const FRefreshChildrenParams& InParams) override;`
- L29 _public prototype_ `virtual TSharedPtr<SWidget> GenerateRowWidget() override;`
- L30 _public prototype_ `virtual UMediaOutput* AddMediaOutputToChannel(FName InTargetChannel, const FAvaBroadcastMediaOutputInfo& InOutputInfo) override;`
- L34 _protected member_ `TWeakObjectPtr<UClass> OutputClass;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMedia/Private/Broadcast/OutputDevices/AvaBroadcastOutputDeviceItem.h` (Private)


#### class `FAvaBroadcastOutputDeviceItem`  
`class FAvaBroadcastOutputDeviceItem : public FAvaBroadcastOutputTreeItem`  
_L10-37_
- inherits: `FAvaBroadcastOutputTreeItem`
- L13 _public prototype_ `UE_AVA_INHERITS_WITH_SUPER(FAvaBroadcastOutputDeviceItem, FAvaBroadcastOutputTreeItem);`
- L15 _public function_ `FAvaBroadcastOutputDeviceItem(const TSharedPtr<FAvaBroadcastOutputTreeItem>& InParent, const FAvaBroadcastDevice& InDevice) : Super(InParent) , Device(InDevice)`
- L21 _public function_ `const FAvaBroadcastDevice& GetDevice() const`
- L27 _public prototype_ `virtual FText GetDisplayName() const override;`
- L28 _public prototype_ `virtual const FSlateBrush* GetIconBrush() const override;`
- L29 _public prototype_ `virtual void RefreshChildren(const FRefreshChildrenParams& InParams) override;`
- L30 _public prototype_ `virtual TSharedPtr<SWidget> GenerateRowWidget() override;`
- L31 _public prototype_ `virtual bool IsValidToDropInChannel(FName InTargetChannelName) override;`
- L32 _public prototype_ `virtual UMediaOutput* AddMediaOutputToChannel(FName InTargetChannel, const FAvaBroadcastMediaOutputInfo& InOutputInfo) override;`
- L36 _protected member_ `FAvaBroadcastDevice Device;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMedia/Private/Broadcast/OutputDevices/AvaBroadcastOutputServerItem.h` (Private)


#### class `FAvaBroadcastOutputServerItem`  
`class FAvaBroadcastOutputServerItem : public FAvaBroadcastOutputTreeItem`  
_L10-37_
- inherits: `FAvaBroadcastOutputTreeItem`
- L13 _public prototype_ `UE_AVA_INHERITS_WITH_SUPER(FAvaBroadcastOutputServerItem, FAvaBroadcastOutputTreeItem);`
- L15 _public function_ `FAvaBroadcastOutputServerItem(const FString& InServerName, const TSharedPtr<const FAvaBroadcastDeviceProviderDataList>& InDeviceProviderDataList) : Super(nullptr) , ServerName(InServerName) , DeviceProviderDataList(InDeviceProviderDataList)`
- L22 _public prototype_ `FString GetServerName() const;`
- L23 _public prototype_ `const FAvaBroadcastDeviceProviderData* GetDeviceProviderData(FName InDeviceProviderName) const;`
- L26 _public prototype_ `virtual FText GetDisplayName() const override;`
- L27 _public prototype_ `virtual const FSlateBrush* GetIconBrush() const override;`
- L28 _public prototype_ `virtual void RefreshChildren(const FRefreshChildrenParams& InParams) override;`
- L29 _public prototype_ `virtual TSharedPtr<SWidget> GenerateRowWidget() override;`
- L30 _public function_ `virtual bool IsValidToDropInChannel(FName InTargetChannelName) override`
- L31 _public prototype_ `virtual UMediaOutput* AddMediaOutputToChannel(FName InTargetChannel, const FAvaBroadcastMediaOutputInfo& InOutputInfo) override;`
- L35 _protected member_ `FString ServerName;`
- L36 _protected member_ `const TSharedPtr<const FAvaBroadcastDeviceProviderDataList> DeviceProviderDataList;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMedia/Private/Broadcast/OutputDevices/AvaBroadcastRenderTargetMediaCapture.h` (Private)


#### class `UAvaBroadcastRenderTargetMediaCapture`  
`class UAvaBroadcastRenderTargetMediaCapture : public UMediaCapture`  
_L12-33_
- reflection: `UCLASS()`
- inherits: `UMediaCapture`
- L17 _protected function_ `virtual bool ShouldCaptureRHIResource() const override`
- L18 _protected prototype_ `virtual void OnRHIResourceCaptured_RenderingThread(FRHICommandListImmediate& RHICmdList, const FCaptureBaseData& InBaseData, TSharedPtr<FMediaCaptureUserData, ESPMode::ThreadSafe> InUserData, FTextureRHIRef InTexture) override;`
- L20 _protected prototype_ `virtual bool InitializeCapture() override;`
- L21 _protected prototype_ `virtual bool PostInitializeCaptureViewport(TSharedPtr<FSceneViewport>& InSceneViewport) override;`
- L22 _protected prototype_ `virtual bool PostInitializeCaptureRenderTarget(UTextureRenderTarget2D* InRenderTarget) override;`
- L23 _protected prototype_ `virtual bool PostInitializeCaptureRHIResource(const FRHICaptureResourceDescription& InResourceDescription) override;`
- L24 _protected prototype_ `virtual void StopCaptureImpl(bool bAllowPendingFrameToBeProcess) override;`
- L27 _protected member_ `TObjectPtr<UTextureRenderTarget2D> RenderTarget;` — `UPROPERTY(Transient)`
- L30 _private prototype_ `bool StartNewCapture(const FIntPoint& InSourceTargetSize, EPixelFormat InSourceTargetFormat);`
- L32 _private member_ `FCriticalSection RenderTargetCriticalSection;`

#### Free symbols / members of external scopes

- L9 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogAvaBroadcastRenderTargetMedia, Log, All);`
- L9 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogAvaBroadcastRenderTargetMedia, Log, All);`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMedia/Private/Broadcast/OutputDevices/AvaBroadcastRenderTargetMediaOutput.h` (Private)


#### class `UAvaBroadcastRenderTargetMediaOutput`  
`class UAvaBroadcastRenderTargetMediaOutput : public UMediaOutput`  
_L16-52_
- reflection: `UCLASS(BlueprintType, ClassGroup = "Motion Design Broadcast", meta = (DisplayName = "Motion Design Render Target Media Output", MediaIOCustomLayout = "AvaRenderTarget"))`
- inherits: `UMediaOutput`
- desc: Capture a Media to a render target.
- L23 _public member_ `bool bInvertKeyOutput = true;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Media")` — Invert the key (alpha channel).
- L29 _public member_ `TSoftObjectPtr<UTextureRenderTarget2D> RenderTarget;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Media")` — Specify the render target to be capturing to.
- L36 _public member_ `FString SourceName;` — `UPROPERTY()` — The source name is a property that exists to provide the "device name" for displaying in the broadcast editor. It is derived from the specified render target path.
- L40 _public prototype_ `virtual bool Validate(FString& FailureReason) const override;`
- L41 _public prototype_ `virtual FIntPoint GetRequestedSize() const override;`
- L42 _public prototype_ `virtual EPixelFormat GetRequestedPixelFormat() const override;`
- L43 _public prototype_ `virtual EMediaCaptureConversionOperation GetConversionOperation(EMediaCaptureSourceType InSourceType) const override;`
- L46 _public prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;`
- L50 _protected prototype_ `virtual UMediaCapture* CreateMediaCaptureImpl() override;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMedia/Private/Broadcast/OutputDevices/AvaGameViewportMediaCapture.h` (Private)


#### class `UAvaGameViewportMediaCapture`  
`class UAvaGameViewportMediaCapture : public UMediaCapture`  
_L11-22_
- reflection: `UCLASS()`
- inherits: `UMediaCapture`
- L17 _protected function_ `virtual bool ShouldCaptureRHIResource() const override`
- L18 _protected prototype_ `virtual bool InitializeCapture() override;`
- L19 _protected prototype_ `virtual bool PostInitializeCaptureViewport(TSharedPtr<FSceneViewport>& InSceneViewport) override;`
- L20 _protected prototype_ `virtual bool PostInitializeCaptureRenderTarget(UTextureRenderTarget2D* InRenderTarget) override;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMedia/Private/Broadcast/OutputDevices/AvaGameViewportMediaOutput.h` (Private)


#### class `UAvaGameViewportMediaOutput`  
`class UAvaGameViewportMediaOutput : public UMediaOutput`  
_L12-32_
- reflection: `UCLASS(BlueprintType, ClassGroup = "Motion Design Broadcast", meta = (DisplayName = "Motion Design Game Viewport Media Output", MediaIOCustomLayout = "AvaGameViewport"))`
- inherits: `UMediaOutput`
- L18 _public function_ `virtual FIntPoint GetRequestedSize() const override`
- L19 _public function_ `virtual EPixelFormat GetRequestedPixelFormat() const override`
- L20 _public function_ `virtual EMediaCaptureConversionOperation GetConversionOperation(EMediaCaptureSourceType InSourceType) const override`
- L22 _protected prototype_ `virtual UMediaCapture* CreateMediaCaptureImpl() override;`
- L31 _public member_ `FString SourceName = TEXT("Gam` — `UPROPERTY()` — The source name is a property that exists to provide the "device name" for displaying in the broadcast editor.

#### Free symbols / members of external scopes

- L8 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogAvaGameViewportMedia, Log, All);`
- L8 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogAvaGameViewportMedia, Log, All);`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMedia/Private/Broadcast/OutputDevices/Slate/SAvaBroadcastOutputTreeItem.h` (Private)


#### class `SAvaBroadcastOutputTreeItem`  
`class SAvaBroadcastOutputTreeItem : public SCompoundWidget`  
_L9-19_
- inherits: `SCompoundWidget`
- L12 _public function_ `SLATE_BEGIN_ARGS(SAvaBroadcastOutputTreeItem)`
- L13 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedPtr<FAvaBroadcastOutputTreeItem>& InOutputTreeItem);`
- L18 _protected member_ `TWeakPtr<FAvaBroadcastOutputTreeItem> OutputTreeItemWeak;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMedia/Private/ModularFeature/AvaMediaSync.h` (Private)


#### class `FAvaMediaSync`  
`class FAvaMediaSync`  
_L18-66_
- desc: Helper class for modular feature IAvaMediaSyncProvider's events. The purpose of this class is to maintain a relay with the currently available IAvaMediaSyncProvider's events and the corresponding IAvaMediaModule's events. The complexity of maintaining proper event registration with IAvaMediaSyncProvider is encapsulated in this class.
- L21 _public prototype_ `FAvaMediaSync();`
- L22 _public prototype_ `~FAvaMediaSync();`
- L28 _public function_ `bool IsFeatureEnabled() const` — Returns true if the feature is enabled. This is independent than the feature available.
- L35 _public prototype_ `void SetFeatureEnabled(bool bInIsFeatureEnabled);` — The feature is enabled by default, but can be disabled even if it is available. The use case of disabling the media sync feature is if a local server process is launched in game mode from the same folder as the client.
- L40 _public prototype_ `IAvaMediaSyncProvider* GetCurrentProvider();` — Returns the currently available Media Sync Provider or null if feature is disabled.
- L46 _public function_ `bool IsFeatureAvailable() const` — Returns true if the IAvaMediaSyncProvider feature is available, i.e. if it has at least one implementation.
- L52 _public prototype_ `static int32 GetModularFeatureImplementationCount();` — Returns the number of IAvaMediaSyncProvider implementations registered. remark: This call is thread safe.
- L55 _private prototype_ `void UseProvider(IAvaMediaSyncProvider* InSyncProvider);`
- L56 _private prototype_ `void RefreshFeatureAvailability();`
- L59 _private prototype_ `void HandleModularFeatureRegistered(const FName& InFeatureName, IModularFeature* InFeature);` — Delegate handlers
- L60 _private prototype_ `void HandleModularFeatureUnregistered(const FName& InFeatureName, IModularFeature* InFeature);`
- L61 _private prototype_ `void HandleAvaSyncPackageModified(const FName& InPackageName);`
- L63 _private member_ `IAvaMediaSyncProvider* CurrentProvider = nullptr;`
- L64 _private member_ `bool bIsFeatureAvailable = false;`
- L65 _private member_ `bool bIsFeatureEnabled = true;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMedia/Private/Playable/AvaPlayableAssetUserData.h` (Private)


#### class `UAvaPlayableAssetUserData`  
`class UAvaPlayableAssetUserData : public UAssetUserData`  
_L17-23_
- reflection: `UCLASS()`
- inherits: `UAssetUserData`
- desc: AssetUserData for AvaPlayable. This is strategically injected in asset instances to be able to retrieve the corresponding playable directly.
- L22 _public member_ `TWeakObjectPtr<UAvaPlayable> PlayableWeak;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMedia/Private/Playable/AvaPlayableGroupAssetUserData.h` (Private)


#### class `UAvaPlayableGroupAssetUserData`  
`class UAvaPlayableGroupAssetUserData : public UAssetUserData`  
_L17-29_
- reflection: `UCLASS()`
- inherits: `UAssetUserData`
- desc: AssetUserData for AvaPlayableGroup. This is strategically injected in asset instances to be able to retrieve the corresponding playable group directly.
- L28 _public member_ `TArray<TWeakObjectPtr<UAvaPlayableGroup>> PlayableGroupsWeak;` — A playable group being loosely defined in the playable framework, an asset instance may be associated with more than one playable group. The intent is to be injecting this in asset instances that are associated with just one playable group.

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMedia/Private/Playable/AvaPlayableGroupManager.h` (Private)


#### class `UAvaPlayableGroupChannelManager`  
`class UAvaPlayableGroupChannelManager : public UObject`  
_L21-52_
- reflection: `UCLASS()`
- inherits: `UObject`
- desc: Manager for the shared playable groups per channel.
- L26 _public prototype_ `UAvaPlayableGroup* GetOrCreatePlayableGroup(UGameInstance* InExistingGameInstance, bool bInIsRemoteProxy);`
- L28 _public prototype_ `UAvaPlayableGroupManager* GetPlayableGroupManager() const;`
- L30 _public prototype_ `void GetPlayableGroups(TArray<TWeakObjectPtr<UAvaPlayableGroup>>& OutGroups) const;`
- L32 _public prototype_ `UAvaPlayableGroup* FindPlayableGroupForWorld(const UWorld* InWorld) const;`
- L36 _protected prototype_ `virtual void BeginDestroy() override;`
- L39 _protected prototype_ `void Shutdown();`
- L42 _protected member_ `FName ChannelName;`
- L49 _protected member_ `TArray<TWeakObjectPtr<UAvaPlayableGroup>> PlayableGroupsWeak;` — Shared playable groups for this channel. The manager only keeps weak pointers. Groups are owned by their respective playables.

#### class `UAvaPlayableGroupManager`  
`class UAvaPlayableGroupManager : public UObject`  
_L60-132_
- reflection: `UCLASS()`
- inherits: `UObject`
- desc: Manager for the shared playable groups. The scope of this manager is either global (in the global playback manager) or for a given playback manager.
- L65 _public prototype_ `void Init();`
- L67 _public prototype_ `void Shutdown();`
- L69 _public prototype_ `void Tick(double InDeltaSeconds);`
- L71 _public prototype_ `void PushSynchronizedEvent(FString&& InEventSignature, TUniqueFunction<void()> InFunction);`
- L73 _public prototype_ `bool IsSynchronizedEventPushed(const FString& InEventSignature) const;`
- L75 _public function_ `UAvaPlayableGroupChannelManager* FindChannelManager(const FName& InChannelName) const`
- L81 _public prototype_ `UAvaPlayableGroupChannelManager* FindOrAddChannelManager(const FName& InChannelName);`
- L89 _public prototype_ `UAvaPlayableGroup* GetOrCreateSharedPlayableGroup(const FName& InChannelName, bool bInIsRemoteProxy);` — @brief Returns the playable group for the given channel. @param InChannelName Channel name, should correspond to a configured broadcast channel. @param bInIsRemoteProxy Indicate if the implementation is local or remote. @return Playable group.
- L91 _public prototype_ `void RegisterForLevelStreamingUpdate(UAvaPlayableGroup* InPlayableGroup);`
- L92 _public prototype_ `void UnregisterFromLevelStreamingUpdate(UAvaPlayableGroup* InPlayableGroup);`
- L94 _public prototype_ `void RegisterForTransitionTicking(UAvaPlayableGroup* InPlayableGroup);`
- L95 _public prototype_ `void UnregisterFromTransitionTicking(UAvaPlayableGroup* InPlayableGroup);`
- L100 _public prototype_ `TArray<TWeakObjectPtr<UAvaPlayableGroup>> GetPlayableGroups(FName InChannelName = NAME_None) const;` — Returns playable groups part of the given channel, or all playable groups if channel is None.
- L105 _public prototype_ `UAvaPlayableGroup* FindPlayableGroupForWorld(const UWorld* InWorld) const;` — Return the playable group corresponding to the given world.
- L109 _protected prototype_ `virtual void BeginDestroy() override;`
- L113 _protected prototype_ `void OnGameInstanceEndPlay(UAvaGameInstance* InGameInstance, FName InChannelName);` — Move to UAvaGameInstancePlayableGroup
- L115 _protected prototype_ `void UpdateLevelStreaming();`
- L117 _protected prototype_ `void TickTransitions(double InDeltaSeconds);`
- L121 _protected member_ `TMap<FName, TObjectPtr<UAvaPlayableGroupChannelManager>> ChannelManagers;` — `UPROPERTY(Transient)`
- L123 _protected member_ `bool bIsUpdatingStreaming = false;`
- L124 _protected member_ `TSet<TWeakObjectPtr<UAvaPlayableGroup>> GroupsToUpdateStreaming;`
- L126 _protected member_ `bool bIsTickingTransitions = false;`
- L127 _protected member_ `TSet<TWeakObjectPtr<UAvaPlayableGroup>> GroupsToTickTransitions;`
- L129 _protected member_ `TArray<TWeakObjectPtr<UAvaPlayableGroup>> GroupsToTickEvents;`
- L131 _protected member_ `TSharedPtr<IAvaMediaSynchronizedEventDispatcher> SynchronizedEventDispatcher;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMedia/Private/Playable/AvaPlayableGroupSceneViewExtension.h` (Private)


#### class `FAvaPlayableGroupSceneViewExtension`  
`class FAvaPlayableGroupSceneViewExtension final : public FSceneViewExtensionBase`  
_L9-16_
- inherits: `FSceneViewExtensionBase`
- L12 _public prototype_ `FAvaPlayableGroupSceneViewExtension(const FAutoRegister& InAutoReg);`
- L13 _public prototype_ `virtual ~FAvaPlayableGroupSceneViewExtension() override = default;`
- L15 _public prototype_ `void SetupView(FSceneViewFamily& InViewFamily, FSceneView& InView) override;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMedia/Private/Playable/AvaPlayableGroupSubsystem.h` (Private)


#### class `UAvaPlayableGroupSubsystem`  
`class UAvaPlayableGroupSubsystem : public UGameInstanceSubsystem`  
_L12-24_
- reflection: `UCLASS()`
- inherits: `UGameInstanceSubsystem`
- L18 _public prototype_ `virtual void Initialize(FSubsystemCollectionBase& Collection) override;`
- L19 _public prototype_ `virtual void Deinitialize() override;`
- L23 _public member_ `TObjectPtr<UAvaPlayableGroupManager> PlayableGroupManager;` — `UPROPERTY()`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMedia/Private/Playable/AvaPlayableRemoteControlPresetInfoCache.h` (Private)


#### class `FAvaPlayableRemoteControlPresetInfoCache`  
`class FAvaPlayableRemoteControlPresetInfoCache final : public IAvaPlayableRemoteControlPresetInfoCache`  
_L15-46_
- inherits: `IAvaPlayableRemoteControlPresetInfoCache`
- desc: Implementation of a RCP info cache. Similar to FAvaRundownManagedInstanceCache in terms of invalidation. Given this is relatively lightweight auxiliary data, we could mark as dirty instead of deleting.
- L19 _public prototype_ `virtual TSharedPtr<FAvaPlayableRemoteControlPresetInfo> GetRemoteControlPresetInfo(const FSoftObjectPath& InAssetPath, const URemoteControlPreset* InRemoteControlPreset) override;`
- L20 _public prototype_ `virtual void Flush(const FSoftObjectPath& InAssetPath) override;`
- L21 _public prototype_ `virtual void Flush() override;`
- L27 _public prototype_ `static int32 GetMaximumCacheSize();` — Get the maximum size of the cache beyond witch it will start flushing elements.
- L32 _public prototype_ `void TrimCache();` — Trim the cache elements that exceed the cache capacity according to LRU replacement policy.
- L35 _private prototype_ `void RemoveEntry(const FSoftObjectPath& InAssetPath);`
- L36 _private prototype_ `void RemoveEntries(TFunctionRef<bool(const FSoftObjectPath&, const TSharedPtr<FAvaPlayableRemoteControlPresetInfo>&)> InRemovePredicate);`
- L38 _private prototype_ `void OnPackageSaved(const FString& InPackageFileName, UPackage* InPackage, FObjectPostSaveContext InObjectSaveContext);`
- L39 _private prototype_ `void OnAvaSyncPackageModified(IAvaMediaSyncProvider* InAvaMediaSyncProvider, const FName& InPackageName);`
- L40 _private prototype_ `void OnAssetRemoved(const FAssetData& InAssetData);`
- L41 _private prototype_ `void OnPackageModified(const FName& InPackageName);`
- L44 _private member_ `TMap<FSoftObjectPath, TSharedPtr<FAvaPlayableRemoteControlPresetInfo>> PresetInfoCache;`
- L45 _private member_ `TArray<FSoftObjectPath> OrderQueue;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMedia/Private/Playable/AvaPlayableRemoteControlValuesPrivate.h` (Private)


#### struct `FAvaPlayableRemoteControlValueCustomVersion`  
`struct FAvaPlayableRemoteControlValueCustomVersion`  
_L9-29_
- desc: Custom serialization version for FAvaPlayableRemoteControlValue
- L25 _public member_ `static const FGuid Key;` — The GUID for this custom version number
- L28 _private prototype_ `FAvaPlayableRemoteControlValueCustomVersion() = delete;`

#### enum `FAvaPlayableRemoteControlValueCustomVersion::Type`  
`enum Type`  
_L11-22_
- L14 _public enumerator_ `BeforeCustomVersionWasAdded = 0` — Initial version had the values stored as raw bytes.
- L17 _public enumerator_ `ValueAsString` — Values are stored as strings (json formatted).
- L20 _public enumerator_ `VersionPlusOne` — -----<new versions can be added above this line>-------------------------------------------------
- L21 _public enumerator_ `LatestVersion = VersionPlusOne - 1`

#### struct `FAvaPlayableRemoteControlValueAsBytes_Legacy`  
`struct FAvaPlayableRemoteControlValueAsBytes_Legacy`  
_L32-41_
- reflection: `USTRUCT()`
- L37 _public member_ `TArray<uint8> Bytes;` — `UPROPERTY()`
- L40 _public member_ `bool bIsDefault = false;` — `UPROPERTY()`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMedia/Private/Playable/AvaPlayableUtils.h` (Private)


#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace AvaMedia` (scope `UE`)
- L11 _namespace_ `namespace PlayableUtils` (scope `UE::AvaMedia`)
- L13 _prototype_ `void AddPrimitiveComponentIds(const AActor* InActor, TSet<FPrimitiveComponentId>& InComponentIds);` (scope `UE::AvaMedia::PlayableUtils`)
- L16 _prototype_ `bool HasLocalPlay(const UAvaBroadcast& InBroadcast, FName InChannelName);` (scope `UE::AvaMedia::PlayableUtils`) — Returns true if the broadcast's current profile for the given channel is configured to have local play
- L19 _prototype_ `bool HasRemotePlay(const UAvaBroadcast& InBroadcast, FName InChannelName);` (scope `UE::AvaMedia::PlayableUtils`) — Returns true if the broadcast's current profile for the given channel is configured to have remote play

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMedia/Private/Playable/PlayableGroups/AvaGameInstancePlayableGroup.h` (Private)


#### class `UAvaGameInstancePlayableGroup`  
`class UAvaGameInstancePlayableGroup : public UAvaPlayableGroup`  
_L21-43_
- reflection: `UCLASS()`
- inherits: `UAvaPlayableGroup`
- desc: This playable group implements a container that owns a motion design game instance. It is intended to be used for broadcast only self contained world simulation and rendering. Render Target: The render target provided as argument of BeginPlay is used to override the game viewport's canvas. So the game will render in the provided render target directly.
- L26 _public prototype_ `static UAvaGameInstancePlayableGroup* Create(UObject* InOuter, const FPlayableGroupCreationInfo& InPlayableGroupInfo);`
- L28 _public prototype_ `UAvaGameInstance* GetAvaGameInstance() const;`
- L31 _public prototype_ `virtual bool ConditionalCreateWorld() override;`
- L32 _public prototype_ `virtual bool ConditionalBeginPlay(const FAvaInstancePlaySettings& InWorldPlaySettings) override;`
- L33 _public prototype_ `virtual void RequestEndPlayWorld(bool bInForceImmediate) override;`
- L34 _public prototype_ `virtual bool ConditionalRequestUnloadWorld(bool bForceImmediate) override;`
- L35 _public prototype_ `virtual bool IsWorldPlaying() const override;`
- L36 _public prototype_ `virtual bool IsRenderTargetReady() const override;`
- L37 _public prototype_ `virtual UTextureRenderTarget2D* GetRenderTarget() const override;`
- L38 _public prototype_ `virtual UWorld* GetPlayWorld() const override;`
- L42 _public member_ `TObjectPtr<UPackage> GameInstancePackage;` — `UPROPERTY(Transient)`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMedia/Private/Playable/PlayableGroups/AvaGameViewportPlayableGroup.h` (Private)


#### class `UAvaGameViewportPlayableGroup`  
`class UAvaGameViewportPlayableGroup : public UAvaPlayableGroup`  
_L22-57_
- reflection: `UCLASS()`
- inherits: `UAvaPlayableGroup`
- desc: This playable group implements a wrapper for a pre-existing game instance. It is intended to be used for injecting motion design's playable in an existing game instance that is not specifically implemented for motion design playback. Render Target: The render target provided as argument of BeginPlay is used to copy the viewport render in when the viewport is rendered, but before EndFrame, so it can still be used with media captures for chaining outputs to other devices.
- L27 _public prototype_ `static UAvaGameViewportPlayableGroup* Create( UObject* InOuter, UGameInstance* InGameInstance, UAvaPlayableGroupManager* InPlayableGroupManager);`
- L34 _public prototype_ `void DetachGameInstance();`
- L37 _public prototype_ `virtual bool ConditionalBeginPlay(const FAvaInstancePlaySettings& InWorldPlaySettings) override;`
- L38 _public prototype_ `virtual void RequestEndPlayWorld(bool bInForceImmediate) override;`
- L39 _public prototype_ `virtual UTextureRenderTarget2D* GetRenderTarget() const override;`
- L43 _private prototype_ `void RegisterViewportDelegates();`
- L44 _private prototype_ `void UnregisterViewportDelegates();`
- L45 _private prototype_ `void CopyViewportRenderTarget(FViewport* InViewport) const;`
- L46 _private prototype_ `void OnViewportRendered(FViewport* InViewport);`
- L50 _private member_ `TWeakObjectPtr<UTextureRenderTarget2D> ViewportRenderTargetWeak;` — Internal copy of the viewport render target.
- L56 _private member_ `bool bIsPlaying = false;` — Keep track if the playable group is "playing". ConditionalBeginPlay will return true only if the group was not already playing.

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMedia/Private/Playable/PlayableGroups/AvaRemoteProxyPlayableGroup.h` (Private)


#### class `UAvaRemoteProxyPlayableGroup`  
`class UAvaRemoteProxyPlayableGroup : public UAvaPlayableGroup`  
_L12-23_
- reflection: `UCLASS()`
- inherits: `UAvaPlayableGroup`
- desc: Remote Proxy Playable Group doesn't have a game instance because it is executed remotely.
- L18 _public prototype_ `virtual bool ConditionalBeginPlay(const FAvaInstancePlaySettings& InWorldPlaySettings) override;`
- L19 _public prototype_ `virtual void RequestEndPlayWorld(bool bInForceImmediate) override;`
- L22 _public member_ `bool bIsPlaying = false;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMedia/Private/Playable/Playables/AvaPlayableLevelStreaming.h` (Private)


#### class `UAvaPlayableLevelStreaming`  
`class UAvaPlayableLevelStreaming : public UAvaPlayable`  
_L17-158_
- reflection: `UCLASS(NotBlueprintable, BlueprintType, ClassGroup = "Motion Design Playable", meta = (DisplayName = "Motion Design Level Streaming Playable"))`
- inherits: `UAvaPlayable`
- L32 _public prototype_ `virtual bool LoadAsset(const FAvaSoftAssetPtr& InSourceAsset, bool bInInitiallyVisible, const FString& InLoadOptions) override;`
- L33 _public prototype_ `virtual bool UnloadAsset() override;`
- L34 _public function_ `virtual const FSoftObjectPath& GetSourceAssetPath() const override`
- L35 _public function_ `virtual EAvaPlayableStatus GetPlayableStatus() const override`
- L36 _public prototype_ `virtual IAvaSceneInterface* GetSceneInterface() const override;`
- L37 _public prototype_ `virtual bool GetShouldBeVisible() const override;`
- L38 _public prototype_ `virtual void SetShouldBeVisible(bool bInShouldBeVisible) override;`
- L39 _public prototype_ `virtual void SetupView(FSceneViewFamily& InViewFamily, FSceneView& InView) override;`
- L40 _public prototype_ `virtual bool IsReadyToPlay() const override;`
- L43 _protected prototype_ `virtual bool InitPlayable(const FPlayableCreationInfo& InPlayableInfo) override;`
- L44 _protected prototype_ `virtual void OnPlay() override;`
- L45 _protected prototype_ `virtual void OnEndPlay() override;`
- L46 _protected prototype_ `virtual void OnRemoteControlValuesApplied() override;`
- L50 _protected prototype_ `virtual void BeginDestroy() override;`
- L54 _public function_ `ULevelStreamingDynamic* GetLevelStreaming() const`
- L56 _public function_ `void SetShouldBeHidden(bool bInShouldBeHidden)`
- L57 _public function_ `bool GetShouldBeHidden() const`
- L60 _protected prototype_ `bool LoadLevel(const TSoftObjectPtr<UWorld>& InSourceLevel, const FTransform& InTransform, bool bInInitiallyVisible);`
- L62 _protected prototype_ `void HandleTransitionEvent(UAvaPlayable* InPlayable, UAvaPlayableTransition* InTransition, EAvaPlayableTransitionEventFlags InTransitionFlags);`
- L64 _protected prototype_ `void OnLevelStreamingStateChanged(UWorld* InWorld , const ULevelStreaming* InLevelStreaming , ULevel* InLevelIfLoaded , ELevelStreamingState InPreviousState , ELevelStreamingState InNewState);`
- L70 _protected prototype_ `void OnLevelStreamingStateChanged_Synchronized(ELevelStreamingState InNewState);`
- L72 _protected prototype_ `void UpdatePlayableStatus(ELevelStreamingState InNewState);`
- L73 _protected prototype_ `void NotifyPlayableStatusChanged();`
- L75 _protected prototype_ `void BindDelegates();`
- L76 _protected prototype_ `void UnbindDelegates();`
- L77 _protected prototype_ `ULevel* GetLoadedLevel() const;`
- L78 _protected prototype_ `void ResolveScene(const ULevel* InLevel);`
- L80 _protected prototype_ `void LoadSubPlayables(const UWorld* InLevelInstance);`
- L81 _protected prototype_ `void UnloadSubPlayables();`
- L83 _protected prototype_ `void GetOrLoadSubPlayable(const ULevelStreaming* InLevelStreaming);`
- L89 _protected prototype_ `static UAvaPlayableLevelStreaming* CreateSubPlayable(UAvaPlayableGroup* InPlayableGroup, const FSoftObjectPath& InSourceAssetPath);` — Creates a level streaming playable from the given level streaming information. A new level streaming object is created, wrapped in the returned playable.
- L91 _protected prototype_ `void AddSubPlayable(UAvaPlayableLevelStreaming* InSubPlayable);`
- L92 _protected prototype_ `void RemoveSubPlayable(UAvaPlayableLevelStreaming* InSubPlayable);`
- L95 _protected prototype_ `bool HasParentPlayables() const;` — For shared playables (loaded through streaming dependencies), returns true if the playable is still part of other dependencies.
- L97 _protected prototype_ `void UpdateVisibilityFromParents();`
- L101 _protected member_ `TSoftObjectPtr<UWorld> SourceLevel;` — `UPROPERTY(Transient)`
- L104 _protected member_ `TObjectPtr<ULevelStreamingDynamic> LevelStreaming;` — `UPROPERTY(Transient)`
- L107 _protected member_ `TObjectPtr<AAvaScene> Scene;` — `UPROPERTY(Transient)`
- L109 _protected member_ `bool bLoadSubPlayables = false;`
- L111 _protected member_ `EAvaPlayableStatus PlayableStatus = EAvaPlayableStatus::Unloaded;`
- L114 _protected member_ `ELevelStreamingState SynchronizedLevelStreamingState = ELevelStreamingState::Unloaded;` — Keep track of the synchronized level streaming state.
- L122 _protected member_ `TArray<TObjectPtr<UAvaPlayableLevelStreaming>> SubPlayables;` — `UPROPERTY(Transient)` — Dependent playables loaded from secondary streaming levels. Those playables are shared by the parent playable(s) and will be unloaded when the last parent playable is unloaded.
- L128 _protected member_ `TSet<TObjectKey<UAvaPlayableLevelStreaming>> ParentPlayables;` — Keep track of the dependencies this playable is part of. This helps determine when the playable should be unloaded.
- L131 _protected member_ `ECacheShadersOnLevelLoadMethod CacheShadersOnLevelLoadMethod = ECacheShadersOnLevelLoadMethod::None;` — The method of caching shaders when loading the level
- L133 _protected member_ `bool bOnPlayQueued = false;`
- L136 _protected member_ `bool bWaitingForShowPlayable = true;` — Enter Playables should be hidden until the transition has started.
- L139 _protected member_ `bool bShouldBeHidden = false;` — If true, all primitives from the playable will hidden.
- L142 _protected member_ `bool bCachingShaders = false;` — True if shaders are currently being compiled
- L145 _protected member_ `bool bHasEverCachedShaders = false;` — True if shaders have been cached for the level at some point in the past
- L148 _protected member_ `bool bHasTransform = false;` — True if the load command specified a transform.
- L151 _protected member_ `bool bTransformApplied = false;` — Keep track if the transform was applied to avoid doing it multiple times during level streaming.
- L154 _protected member_ `TWeakObjectPtr<AActor> PivotActorForTransform;` — Keep a pointer to the pivot actor used for transform in case we want to change the transform later on (for reuse).
- L157 _protected member_ `FTransform LevelTransform;` — Transform to apply to the actors at the end of level streaming.

#### enum `UAvaPlayableLevelStreaming::ECacheShadersOnLevelLoadMethod`  
`enum class ECacheShadersOnLevelLoadMethod : uint8`  
_L21-29_
- L24 _public enumerator_ `None` — No shaders will be cached on load
- L26 _public enumerator_ `FirstLoad` — Shaders will be cached only on the first level load. Subsequent level loads will not cache shaders
- L28 _public enumerator_ `EveryLoad` — Shaders will be cached every load

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMedia/Private/Playable/Playables/AvaPlayableRemoteProxy.h` (Private)


#### class `UAvaPlayableRemoteProxy`  
`class UAvaPlayableRemoteProxy : public UAvaPlayable`  
_L18-69_
- reflection: `UCLASS(NotBlueprintable, BlueprintType, ClassGroup = "Motion Design Playable", meta = (DisplayName = "Motion Design Remote Proxy Playable"))`
- inherits: `UAvaPlayable`
- L22 _public function_ `FName GetPlayingChannelFName() const`
- L25 _public prototype_ `virtual bool LoadAsset(const FAvaSoftAssetPtr& InSourceAsset, bool bInInitiallyVisible, const FString& InLoadOptions) override;`
- L26 _public prototype_ `virtual bool UnloadAsset() override;`
- L27 _public function_ `virtual const FSoftObjectPath& GetSourceAssetPath() const override`
- L28 _public prototype_ `virtual EAvaPlayableStatus GetPlayableStatus() const override;`
- L29 _public prototype_ `virtual IAvaSceneInterface* GetSceneInterface() const override;`
- L30 _public prototype_ `virtual EAvaPlayableCommandResult ExecuteAnimationCommand(EAvaPlaybackAnimAction InAnimAction, const FAvaPlaybackAnimPlaySettings& InAnimPlaySettings) override;`
- L31 _public prototype_ `virtual EAvaPlayableCommandResult UpdateRemoteControlCommand(const TSharedRef<FAvaPlayableRemoteControlValues>& InRemoteControlValues, EAvaPlayableRCUpdateFlags InFlags) override;`
- L32 _public function_ `virtual bool IsRemoteProxy() const override`
- L33 _public prototype_ `virtual void SetUserData(const FString& InUserData) override;`
- L36 _protected prototype_ `virtual bool InitPlayable(const FPlayableCreationInfo& InPlayableInfo) override;`
- L37 _protected prototype_ `virtual void OnPlay() override;`
- L38 _protected prototype_ `virtual void OnEndPlay() override;`
- L42 _protected prototype_ `virtual void BeginDestroy() override;`
- L45 _protected prototype_ `void RegisterClientEventHandlers();`
- L46 _protected prototype_ `void UnregisterClientEventHandlers() const;`
- L48 _protected prototype_ `void HandlePlaybackSequenceEvent(IAvaPlaybackClient& InPlaybackClient, const UE::AvaPlaybackClient::Delegates::FPlaybackSequenceEventArgs& InEventArgs);`
- L51 _protected prototype_ `void HandlePlaybackStatusChanged(IAvaPlaybackClient& InPlaybackClient, const UE::AvaPlaybackClient::Delegates::FPlaybackStatusChangedArgs& InEventArgs);`
- L56 _protected member_ `FName PlayingChannelFName;` — Channel name this playable is playing on.
- L57 _protected member_ `FString PlayingChannelName;`
- L59 _protected member_ `FSoftObjectPath SourceAssetPath;`
- L68 _protected member_ `bool bShouldBeLoaded = false;` — Internal forked channel's status reconciling needs to keep track of the expected series of events. If should be loaded, expected sequence is: loading, loaded, making visible, visible. If it should be unloaded the sequence is inverted. The reconciling logic will select the "slowest" node. Example: for loading process, the status is loading as long as there is one node still loading.

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace AvaPlaybackClient` (scope `UE`)
- L10 _namespace_ `namespace Delegates` (scope `UE::AvaPlaybackClient`)

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMedia/Private/Playable/Transition/AvaPlayableLocalTransition.h` (Private)


#### class `UAvaPlayableLocalTransition`  
`class UAvaPlayableLocalTransition : public UAvaPlayableTransition`  
_L21-56_
- reflection: `UCLASS()`
- inherits: `UAvaPlayableTransition`
- desc: Implements the transition tree execution for all playables with one. It also implements the "hardcoded" TL for playables with no transition tree. The hardcoded TL rules are: - "exit" playables are stopped with "out" sequences defines in transition tree if there is one, otherwise nothing is done. - "enter" playables have their animation triggered after the transition tree is finished, letting the exit pages animated out as they should.
- L27 _public prototype_ `virtual bool Start() override;`
- L28 _public prototype_ `virtual void Stop() override;`
- L29 _public prototype_ `virtual bool IsRunning() const override;`
- L30 _public prototype_ `virtual void Tick(double InDeltaSeconds) override;`
- L34 _protected prototype_ `void OnTransitionExecutorEnded();`
- L36 _protected prototype_ `void PostTransitionExecutorPhase();`
- L38 _protected prototype_ `void OnPlayableSequenceEvent(UAvaPlayable* InPlayable, FName InSequenceLabel, EAvaPlayableSequenceEventType InEventType);`
- L40 _protected prototype_ `void NotifyTransitionFinished();`
- L42 _protected prototype_ `void StartWaitOnPostExecutorSequences();`
- L43 _protected prototype_ `void FinishWaitOnPostExecutorSequences();`
- L45 _protected prototype_ `FString GetInstanceName() const;`
- L49 _protected member_ `TSharedPtr<IAvaTransitionExecutor> TransitionExecutor;` — Transition tree executor.
- L52 _protected member_ `TArray<TWeakObjectPtr<UAvaPlayable>> PostExecutorSequencePlayablesWeak;` — List of enter playables that have no TL and need to play the animations after the transition tree.
- L55 _protected member_ `bool bWaitOnPostExecutorSequences = false;` — Indicate the transition is waiting on sequences.

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMedia/Private/Playable/Transition/AvaPlayableRemoteTransition.h` (Private)


#### class `UAvaPlayableRemoteTransition`  
`class UAvaPlayableRemoteTransition : public UAvaPlayableTransition`  
_L17-104_
- reflection: `UCLASS()`
- inherits: `UAvaPlayableTransition`
- L24 _public function_ `void SetChannelName(const FName& InChannelName)`
- L27 _public prototype_ `virtual bool Start() override;`
- L28 _public prototype_ `virtual void Stop() override;`
- L29 _public prototype_ `virtual bool IsRunning() const override;`
- L33 _protected prototype_ `void HandlePlaybackTransitionEvent(IAvaPlaybackClient& InPlaybackClient, const UE::AvaPlaybackClient::Delegates::FPlaybackTransitionEventArgs& InArgs);`
- L36 _protected prototype_ `void HandleRemoteConnectionEvent(IAvaPlaybackClient& InPlaybackClient, const UE::AvaPlaybackClient::Delegates::FConnectionEventArgs& InArgs);`
- L39 _protected prototype_ `void RegisterToPlaybackClientDelegates();`
- L40 _protected prototype_ `void UnregisterFromPlaybackClientDelegates() const;`
- L50 _protected prototype_ `ERemoteStatus GetRemoteStatus(const FString& InServer) const;`
- L51 _protected prototype_ `void SetRemoteStatus(const FString& InServer, ERemoteStatus InStatus);`
- L52 _protected prototype_ `void SetRemoteStartFrame(const FString& InServer, int32 InFrameNumber);`
- L53 _protected prototype_ `void SetRemoteFinishFrame(const FString& InServer, int32 InFrameNumber);`
- L55 _protected prototype_ `bool IsTransitionFinishedOnAllServers() const;`
- L57 _protected prototype_ `void MarkPlayableForStop(const FString& InServer, const FGuid& InInstanceId);`
- L58 _protected prototype_ `bool IsPlayableMarkedForStopOnAllServers(const FGuid& InInstanceId) const;`
- L60 _protected prototype_ `FString GetInstanceName() const;`
- L63 _protected function_ `void MarkEventsBroadcast(const FGuid& InInstanceId, EAvaPlayableTransitionEventFlags InFlags)` — Mark the given events as broadcast for the given instance.
- L76 _protected function_ `bool HasEventBeenBroadcast(const FGuid& InInstanceId, EAvaPlayableTransitionEventFlags InFlags) const` — Returns true if the given events were marked as broadcast for the given instance.
- L86 _protected member_ `FName ChannelName;`
- L100 _protected member_ `TMap<FString, FRemoteStatusInfo> RemoteStatusPerServer;`
- L103 _protected member_ `TMap<FGuid, EAvaPlayableTransitionEventFlags> InstanceBroadcastEvent;` — Keep track of the events that were locally broadcast to avoid sending them more than once.

#### enum `UAvaPlayableRemoteTransition::ERemoteStatus`  
`enum class ERemoteStatus : uint8`  
_L42-48_
- L44 _public enumerator_ `Unknown`
- L45 _public enumerator_ `StartRequest`
- L46 _public enumerator_ `Started`
- L47 _public enumerator_ `Finished`

#### struct `UAvaPlayableRemoteTransition::FRemoteStatusInfo`  
`struct FRemoteStatusInfo`  
_L92-98_
- desc: Forked channel support: tracking the status of the transition per server to be able to reconcile local event propagation.
- L94 _public member_ `ERemoteStatus Status = ERemoteStatus::Unknown;`
- L95 _public member_ `int32 StartFrameNumber = 0;`
- L96 _public member_ `int32 FinishFrameNumber = 0;`
- L97 _public member_ `TSet<FGuid> PlayablesMarkedForStop;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace AvaPlaybackClient` (scope `UE`)
- L10 _namespace_ `namespace Delegates` (scope `UE::AvaPlaybackClient`)

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMedia/Private/Playable/Transition/AvaPlayableTransitionPrivate.h` (Private)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace AvaPlayableTransition` (scope `UE`)
- L7 _namespace_ `namespace Private` (scope `UE::AvaPlayableTransition`)
- L10 _prototype_ `TArray<UAvaPlayable*> Pin(const TArray<TWeakObjectPtr<UAvaPlayable>>& InPlayablesWeak);` (scope `UE::AvaPlayableTransition::Private`) — Convert the array of weak objects to an array of objects than can be used (hasn't expired).
- L13 _prototype_ `TArray<FGuid> GetInstanceIds(const TArray<TWeakObjectPtr<UAvaPlayable>>& InPlayablesWeak);` (scope `UE::AvaPlayableTransition::Private`) — Returns the array of playable instance ids.
- L16 _prototype_ `bool AreAllPlayablesRemote(const TArray<TWeakObjectPtr<UAvaPlayable>>& InPlayablesWeak);` (scope `UE::AvaPlayableTransition::Private`) — Returns true if all the given playables are remote.
- L19 _prototype_ `void GetChannelNamesFromPlayables(const TArray<TWeakObjectPtr<UAvaPlayable>>& InPlayablesWeak, TArray<FName>& OutChannelNames);` (scope `UE::AvaPlayableTransition::Private`) — Collects all the channel names from the given playables. Only remote playables have channel.
- L22 _prototype_ `FString GetPrettyPlayableInfo(const UAvaPlayable* InPlayable);` (scope `UE::AvaPlayableTransition::Private`) — Returns a string with prettified information about the playable suitable for logging.

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMedia/Private/Playable/Transition/AvaPlayableTransitionScene.h` (Private)


#### struct `FAvaPlayableTransitionScene`  
`struct FAvaPlayableTransitionScene : public FAvaTransitionScene`  
_L13-33_
- reflection: `USTRUCT()`
- inherits: `FAvaTransitionScene`
- L17 _public prototype_ `FAvaPlayableTransitionScene() = default;`
- L19 _public prototype_ `explicit FAvaPlayableTransitionScene(UAvaPlayable* InPlayable, UAvaPlayableTransition* InPlayableTransition);`
- L21 _public prototype_ `explicit FAvaPlayableTransitionScene(const FAvaTagHandle& InTransitionLayer, UAvaPlayableTransition* InPlayableTransition);`
- L24 _public prototype_ `virtual EAvaTransitionComparisonResult Compare(const FAvaTransitionScene& InOther) const override;`
- L25 _public prototype_ `virtual ULevel* GetLevel() const override;`
- L26 _public prototype_ `virtual void GetOverrideTransitionLayer(FAvaTagHandle& OutTransitionLayer) const override;`
- L27 _public prototype_ `virtual void OnFlagsChanged() override;`
- L30 _public member_ `TWeakObjectPtr<UAvaPlayableTransition> PlayableTransitionWeak;`
- L32 _public member_ `TOptional<FAvaTagHandle> OverrideTransitionLayer;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMedia/Private/Playback/AvaPlaybackClient.h` (Private)


#### class `FAvaPlaybackClient`  
`class FAvaPlaybackClient : public IAvaPlaybackClient`  
_L16-488_
- inherits: `IAvaPlaybackClient`
- desc: Listens to command to play and broadcast
- L19 _public prototype_ `FAvaPlaybackClient(IAvaMediaModule* InParentModule);`
- L22 _public prototype_ `void Init();`
- L25 _public prototype_ `virtual int32 GetNumConnectedServers() const override;` — IAvaPlaybackClient
- L26 _public prototype_ `virtual TArray<FString> GetServerNames() const override;`
- L27 _public prototype_ `virtual FMessageAddress GetServerAddress(const FString& InServerName) const override;`
- L28 _public prototype_ `virtual bool HasServerUserData(const FString& InServerName, const FString& InKey) const override;`
- L29 _public prototype_ `virtual const FString& GetServerUserData(const FString& InServerName, const FString& InKey) const override;`
- L30 _public prototype_ `virtual bool HasUserData(const FString& InKey) const override;`
- L31 _public prototype_ `virtual const FString& GetUserData(const FString& InKey) const override;`
- L32 _public prototype_ `virtual void SetUserData(const FString& InKey, const FString& InData) override;`
- L33 _public prototype_ `virtual void RemoveUserData(const FString& InKey) override;`
- L34 _public prototype_ `virtual void BroadcastStatCommand(const FString& InCommand, bool bInBroadcastLocalState) override;`
- L35 _public prototype_ `virtual void RequestPlaybackAssetStatus(const FSoftObjectPath& InAssetPath, const FString& InChannelOrServerName, bool bInForceRefresh) override;`
- L36 _public prototype_ `virtual void RequestPlayback(const FGuid& InInstanceId, const FSoftObjectPath& InAssetPath, const FString& InChannelName, EAvaPlaybackAction InAction, const FString& InArguments = FString()) override;`
- L37 _public prototype_ `virtual void RequestAnimPlayback(const FGuid& InInstanceId, const FSoftObjectPath& InAssetPath, const FString& InChannelName, const FAvaPlaybackAnimPlaySettings& InAnimSettings) override;`
- L38 _public prototype_ `virtual void RequestAnimAction(const FGuid& InInstanceId, const FSoftObjectPath& InAssetPath, const FString& InChannelName, const FString& InAnimationName, EAvaPlaybackAnimAction InAction) override;`
- L39 _public prototype_ `virtual void RequestRemoteControlUpdate(const FGuid& InInstanceId, const FSoftObjectPath& InAssetPath, const FString& InChannelName, const FAvaPlayableRemoteControlValues& InRemoteControlValues, EAvaPlayableRCUpdateFlags InFlags) override;`
- L40 _public prototype_ `virtual void RequestPlayableTransitionStart(const FGuid& InTransitionId, TArray<FGuid>&& InEnterInstanceIds, TArray<FGuid>&& InPlayingInstanceIds, TArray<FGuid>&& InExitInstanceIds, TArray<FAvaPlayableRemoteControlValues>&& InEnterValues, const FName& InChannelName, EAvaPlayableTransitionFlags InTransitionFlags) override;`
- L41 _public prototype_ `virtual void RequestPlayableTransitionStop(const FGuid& InTransitionId, const FName& InChannelName) override;`
- L42 _public prototype_ `virtual void RequestBroadcast(const FString& InProfile, const FName& InChannel, const TArray<UMediaOutput*>& InRemoteMediaOutputs, EAvaBroadcastAction InAction, const FString& InServerName = FString()) override;`
- L43 _public prototype_ `virtual bool IsMediaOutputRemoteFallback(const UMediaOutput* InMediaOutput) override;`
- L44 _public prototype_ `virtual EAvaBroadcastIssueSeverity GetMediaOutputIssueSeverity(const FString& InServerName, const FString& InChannelName, const FGuid& InOutputGuid) const override;`
- L45 _public prototype_ `virtual const TArray<FString>& GetMediaOutputIssueMessages(const FString& InServerName, const FString& InChannelName, const FGuid& InOutputGuid) const override;`
- L46 _public prototype_ `virtual EAvaBroadcastOutputState GetMediaOutputState(const FString& InServerName, const FString& InChannelName, const FGuid& InOutputGuid) const override;`
- L47 _public prototype_ `virtual bool HasAnyServerOnlineForChannel(const FName& InChannelName) const override;`
- L48 _public prototype_ `virtual TArray<FString> GetOnlineServersForChannel(const FName& InChannelName) const override;`
- L49 _public prototype_ `virtual TOptional<EAvaPlaybackStatus> GetRemotePlaybackStatus(const FGuid& InInstanceId, const FSoftObjectPath& InAssetPath, const FString& InChannelName, const FString& InServerName) const override;`
- L50 _public prototype_ `virtual const FString* GetRemotePlaybackUserData(const FGuid& InInstanceId, const FSoftObjectPath& InAssetPath, const FString& InChannelName, const FString& InServerName) const override;`
- L51 _public prototype_ `virtual TOptional<EAvaPlaybackAssetStatus> GetRemotePlaybackAssetStatus(const FSoftObjectPath& InAssetPath, const FString& InServerName) const override;`
- L54 _public prototype_ `FString GetServerProjectContentPath(const FString& InServerName) const;`
- L55 _public prototype_ `uint32 GetServerProcessId(const FString& InServerName) const;`
- L57 _public function_ `FString GetProjectContentPath() const`
- L60 _protected prototype_ `TOptional<EAvaPlaybackStatus> GetPlaybackStatusForServer(const FString& InServerName, const FString& InChannelName, const FGuid& InInstanceId, const FSoftObjectPath& InAssetPath) const;`
- L61 _protected prototype_ `const FString* GetPlaybackUserDataForServer(const FString& InServerName, const FString& InChannelName, const FGuid& InInstanceId, const FSoftObjectPath& InAssetPath) const;`
- L62 _protected prototype_ `void RequestPlaybackAssetStatusForServer(const FSoftObjectPath& InAssetPath, const FString& InServerName, bool bInForceRefresh);`
- L64 _protected prototype_ `void Tick();`
- L66 _protected prototype_ `bool HandlePingTicker(float InDeltaTime);`
- L69 _protected prototype_ `void HandlePlaybackPongMessage(const FAvaPlaybackPong& InMessage, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& InContext);` — Message handlers
- L70 _protected prototype_ `void HandlePlaybackLogMessage(const FAvaPlaybackLog& InMessage, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& InContext);`
- L71 _protected prototype_ `void HandleUpdateServerUserData(const FAvaPlaybackUpdateServerUserData& InMessage, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& InContext);`
- L72 _protected prototype_ `void HandleStatStatus(const FAvaPlaybackStatStatus& InMessage, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& InContext);`
- L73 _protected prototype_ `void HandleDeviceProviderDataListMessage(const FAvaBroadcastDeviceProviderDataList& InMessage, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& InContext);`
- L74 _protected prototype_ `void HandleBroadcastStatusMessage(const FAvaBroadcastStatus& InMessage, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& InContext);`
- L75 _protected prototype_ `void HandlePlaybackAssetStatusMessage(const FAvaPlaybackAssetStatus& InMessage, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& InContext);`
- L76 _protected prototype_ `void HandlePlaybackStatusMessage(const FAvaPlaybackStatus& InMessage, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& InContext);`
- L77 _protected prototype_ `void HandlePlaybackStatusesMessage(const FAvaPlaybackStatuses& InMessage, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& InContext);`
- L78 _protected prototype_ `void HandlePlaybackSequenceEventMessage(const FAvaPlaybackSequenceEvent& InMessage, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& InContext);`
- L79 _protected prototype_ `void HandlePlaybackTransitionEventMessage(const FAvaPlaybackTransitionEvent& InMessage, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& InContext);`
- L80 _protected prototype_ `void HandlePlaybackTransitionEventMultiMessage(const FAvaPlaybackTransitionEventMulti& InMessage, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& InContext);`
- L85 _private prototype_ `void HandlePlaybackStatus(FServerInfo& InServerInfo, const FGuid& InInstanceId, const FSoftObjectPath& InAssetPath, const FString& InChannelName, EAvaPlaybackStatus InStatus, const FString& InUserData = FString(), bool bInValidUserData = false);`
- L90 _protected prototype_ `void RegisterCommands();`
- L93 _protected function_ `void PingServersCommand(const TArray<FString>& InArgs)` — Command handlers
- L94 _protected prototype_ `void RequestPlaybackAssetStatusCommand(const TArray<FString>& InArgs);`
- L95 _protected prototype_ `void RequestPlaybackCommand(const TArray<FString>& InArgs);`
- L96 _protected prototype_ `void RequestBroadcastCommand(const TArray<FString>& InArgs);`
- L97 _protected prototype_ `void SetUserDataCommand(const TArray<FString>& InArgs);`
- L98 _protected prototype_ `void ShowStatusCommand(const TArray<FString>& InArgs);`
- L101 _protected prototype_ `void OnBroadcastChanged(EAvaBroadcastChange InChange);` — Event handlers
- L102 _protected prototype_ `void OnChannelChanged(const FAvaBroadcastOutputChannel& InChannel, EAvaBroadcastChannelChange InChange);`
- L103 _protected prototype_ `void OnAvaMediaSettingsChanged(UObject*, struct FPropertyChangedEvent&);`
- L104 _protected prototype_ `void OnPreSavePackage(UPackage* InPackage, FObjectPreSaveContext InObjectSaveContext);`
- L105 _protected prototype_ `void OnPackageSaved(const FString& InPackageFileName, UPackage* InPackage, FObjectPostSaveContext InObjectSaveContext);`
- L106 _protected prototype_ `void OnAssetRemoved(const FAssetData& InAssetData);`
- L108 _protected prototype_ `void ApplyAvaMediaSettings();`
- L111 _protected function_ `void FillClientInfo(FAvaPlaybackClientMessageBase& InMessage)`
- L119 _protected function_ `template<typename MessageType> void PublishRequest(MessageType* InMessage)`
- L126 _protected function_ `template<typename MessageType> void SendRequest(MessageType* InMessage, const FMessageAddress& InRecipient, EMessageFlags flags = EMessageFlags::None)`
- L134 _protected function_ `template<typename MessageType> void SendRequest(MessageType* InMessage, const TArray<FMessageAddress>& InRecipients, EMessageFlags flags = EMessageFlags::None)`
- L141 _protected prototype_ `void PublishPlaybackPing(const FDateTime& InCurrentTime, bool bInAutoPing);`
- L142 _protected prototype_ `void SendUserDataUpdate(const TArray<FMessageAddress>& InRecipients);`
- L143 _protected prototype_ `void SendBroadcastSettingsUpdate(const TArray<FMessageAddress>& InRecipients);`
- L144 _protected prototype_ `void SendAvaInstanceSettingsUpdate(const TArray<FMessageAddress>& InRecipients);`
- L145 _protected prototype_ `void SendPlayableSettingsUpdate(const TArray<FMessageAddress>& InRecipients);`
- L146 _protected prototype_ `void SendBroadcastChannelSettingsUpdate(const TArray<FMessageAddress>& InRecipients, const FAvaBroadcastOutputChannel& InChannel);`
- L147 _protected prototype_ `void SendPackageEvent(const TArray<FMessageAddress>& InRecipients, const FName& InPackageName, EAvaPlaybackPackageEvent InEvent);`
- L148 _protected prototype_ `void SendStatCommand(const FString& InCommand, bool bInBroadcastLocalState, const TArray<FMessageAddress>& InRecipients);`
- L149 _protected prototype_ `void SendClientInfo(const FMessageAddress& InRecipient);`
- L150 _protected prototype_ `void RemoveDeadServers(const FDateTime& InCurrentTime);`
- L151 _protected prototype_ `void UpdateServerAddresses();`
- L158 _protected prototype_ `TArray<FMessageAddress> GetServerAddressesForChannel(const FName& InChannelName) const;` — Get the server addresses for the given channel in the current broadcast profile. This is based on the channel's MediaOutputInfos. It will properly work even if the channel is idle (but not offline).
- L159 _protected function_ `TArray<FMessageAddress> GetServerAddressesForChannel(const FString& InChannelName) const`
- L169 _protected prototype_ `TArray<FString> GetServerNamesForChannel(const FName& InChannelName, bool bInOnlineOnly = false) const;` — Get the server names for the given channel in the current broadcast profile. This is based on the channel's MediaOutputInfos. It will properly work regardless of the channel's status (idle or even offline).
- L171 _protected prototype_ `FString GetServerNameForMediaOutputFallback(const UMediaOutput* InMediaOutput) const;`
- L174 _private member_ `IAvaMediaModule* ParentModule;`
- L176 _private member_ `TArray<IConsoleObject*> ConsoleCommands;`
- L179 _private member_ `TSharedPtr<FMessageEndpoint, ESPMode::ThreadSafe> MessageEndpoint;` — Holds the messaging endpoint.
- L182 _private member_ `FTickerDelegate PingTickDelegate;` — Holds a delegate to be invoked when the widget ticks.
- L185 _private member_ `FTSTicker::FDelegateHandle PingTickDelegateHandle;` — Handle to the registered TickDelegate.
- L187 _private member_ `FDelegateHandle BroadcastChangedHandle;`
- L189 _private member_ `FString ComputerName;`
- L190 _private member_ `FString ProjectContentPath;`
- L191 _private member_ `uint32 ProcessId = 0;`
- L192 _private member_ `TMap<FString, FString> UserDataEntries;`
- L460 _private member_ `TMap<FString, TSharedPtr<FServerInfo>> Servers;` — Key is ServerName
- L461 _private member_ `TArray<FMessageAddress> AllServerAddresses;`
- L463 _private prototype_ `FServerInfo& GetOrCreateServerInfo(const FString& InServerName, const FMessageAddress& InSenderAddress, bool* bOutCreated = nullptr);`
- L464 _private function_ `FServerInfo* GetServerInfo(const FString& InServerName)`
- L469 _private function_ `const FServerInfo* GetServerInfo(const FString& InServerName) const`
- L475 _private prototype_ `void ForAllServers(TFunctionRef<void(FServerInfo& )> InFunction);`
- L476 _private prototype_ `void ForAllServers(TFunctionRef<void(const FServerInfo& )> InFunction) const;`
- L477 _private prototype_ `void OnServerAdded(const FServerInfo& InServerInfo);`
- L478 _private prototype_ `void OnServerRemoved(const FServerInfo& InRemovedServer);`
- L479 _private prototype_ `const FBroadcastChannelInfo* GetChannelInfo(const FString& InServerName, const FString& InChannelName) const;`
- L482 _private member_ `TMap<FString, FDateTime> PendingPlaybackStatusRequests;` — Map using "playback status request" key to keep track of pending playback status requests.
- L484 _private function_ `static FString GetPlaybackStatusRequestKey(const FGuid& InInstanceId, const FSoftObjectPath& InAssetPath, const FString& InChannelName)`

#### struct `FAvaPlaybackClient::FPendingPlaybackAssetStatusRequest`  
`struct FPendingPlaybackAssetStatusRequest`  
_L195-199_
- desc: Structure holding information on pending playback asset status requests.
- L197 _public member_ `FDateTime ExpirationTime;`
- L198 _public member_ `bool bForceRefresh = false;`

#### struct `FAvaPlaybackClient::FBroadcastChannelInfo`  
`struct FBroadcastChannelInfo`  
_L202-207_
- desc: Remote Broadcast Channel Info
- L204 _public member_ `EAvaBroadcastChannelState ChannelState;`
- L205 _public member_ `EAvaBroadcastIssueSeverity ChannelIssueSeverity;`
- L206 _public member_ `TMap<FGuid, FAvaBroadcastOutputStatus> MediaOutputStatuses;`

#### struct `FAvaPlaybackClient::FPlaybackInstanceInfo`  
`struct FPlaybackInstanceInfo`  
_L210-214_
- desc: Remote Playback Instance Info
- L212 _public member_ `EAvaPlaybackStatus Status;`
- L213 _public member_ `TOptional<FString> UserData;`

#### struct `FAvaPlaybackClient::FPlaybackAssetInfo`  
`struct FPlaybackAssetInfo`  
_L217-268_
- desc: Remote playback for multiple instances of a given asset.
- L219 _public member_ `TMap<FGuid, FPlaybackInstanceInfo> InstanceByIds;`
- L221 _public function_ `TOptional<EAvaPlaybackStatus> GetInstanceStatus(const FGuid& InInstanceId) const`
- L227 _public function_ `const FPlaybackInstanceInfo* GetInstanceInfo(const FGuid& InInstanceId) const`
- L232 _public function_ `void RemoveInstanceInfo(const FGuid& InInstanceId)`
- L237 _public function_ `FPlaybackInstanceInfo* GetOrAddInstanceInfo(const FGuid& InInstanceId)`
- L243 _public function_ `void SetInstanceStatus(const FGuid& InInstanceId, EAvaPlaybackStatus InStatus)`
- L251 _public function_ `const FString* GetInstanceUserData(const FGuid& InInstanceId) const`
- L261 _public function_ `void SetInstanceUserData(const FGuid& InInstanceId, const FString& InUserData)`

#### struct `FAvaPlaybackClient::FPlaybackChannelInfo`  
`struct FPlaybackChannelInfo`  
_L271-325_
- desc: Playback Asset Info for a given channel.
- L273 _public member_ `TMap<FSoftObjectPath, TUniquePtr<FPlaybackAssetInfo>> AssetInfoByPaths;`
- L275 _public function_ `FPlaybackAssetInfo* GetAssetInfo(const FSoftObjectPath& InAssetPath) const`
- L281 _public function_ `FPlaybackAssetInfo* GetOrAddAssetInfo(const FSoftObjectPath& InAssetPath)`
- L290 _public function_ `void RemoveInstanceInfo(const FGuid& InInstanceId, const FSoftObjectPath& InAssetPath)`
- L298 _public function_ `TOptional<EAvaPlaybackStatus> GetInstanceStatus(const FGuid& InInstanceId, const FSoftObjectPath& InAssetPath) const`
- L304 _public function_ `void SetInstanceStatus(const FGuid& InInstanceId, const FSoftObjectPath& InAssetPath, EAvaPlaybackStatus InStatus)`
- L312 _public function_ `const FString* GetInstanceUserData(const FGuid& InInstanceId, const FSoftObjectPath& InAssetPath) const`
- L318 _public function_ `void SetInstanceUserData(const FGuid& InInstanceId, const FSoftObjectPath& InAssetPath, const FString& InUserData)`

#### class `FAvaPlaybackClient::FServerInfo`  
`class FServerInfo`  
_L328-459_
- desc: Remote Server Info
- L331 _public member_ `FMessageAddress Address;`
- L332 _public member_ `FString ServerName;`
- L333 _public member_ `FString ProjectContentPath;`
- L334 _public member_ `uint32 ProcessId = 0;`
- L335 _public member_ `TMap<FString, FString> UserDataEntries;`
- L336 _public member_ `TOptional<FDateTime> PingTimeout;`
- L337 _public member_ `bool bDeviceProviderInstalled = false;`
- L340 _public member_ `TMap<FString, TUniquePtr<FBroadcastChannelInfo>> BroadcastChannelInfosByName;` — Key ChannelName.
- L341 _public member_ `TMap<FString, TUniquePtr<FPlaybackChannelInfo>> PlaybackChannelInfosByName;`
- L344 _public member_ `TMap<FSoftObjectPath, EAvaPlaybackAssetStatus> PlaybackAssetStatuses;` — Asset statuses (on disk) are not per-channel.
- L347 _public member_ `TMap<FSoftObjectPath, FPendingPlaybackAssetStatusRequest> PendingPlaybackAssetStatusRequests;` — Map using "playback asset status request" key to keep track of pending playback asset status requests.
- L350 _public member_ `TArray<FAvaPlaybackCommand> PendingPlaybackCommands;` — Accumulate all the playback commands and send them all in one message on the next tick.
- L352 _public function_ `FBroadcastChannelInfo& GetOrCreateBroadcastChannelInfo(const FString& InChannelName)`
- L358 _public function_ `const FBroadcastChannelInfo* GetBroadcastChannelInfo(const FString& InChannelName) const`
- L364 _public function_ `FPlaybackChannelInfo* GetOrCreatePlaybackChannelInfo(const FString& InChannelName)`
- L370 _public function_ `const FPlaybackChannelInfo* GetPlaybackChannelInfo(const FString& InChannelName) const`
- L376 _public function_ `FPlaybackChannelInfo* GetPlaybackChannelInfo(const FString& InChannelName)`
- L383 _public function_ `TOptional<EAvaPlaybackStatus> GetInstanceStatus( const FString& InChannelName, const FGuid& InInstanceId, const FSoftObjectPath& InAssetPath) const`
- L390 _public function_ `void RemoveInstanceInfo(const FString& InChannelName, const FGuid& InInstanceId, const FSoftObjectPath& InAssetPath)`
- L398 _public function_ `void SetInstanceStatus( const FString& InChannelName, const FGuid& InInstanceId, const FSoftObjectPath& InAssetPath, EAvaPlaybackStatus InStatus)`
- L407 _public function_ `const FString* GetInstanceUserData(const FString& InChannelName, const FGuid& InInstanceId, const FSoftObjectPath& InAssetPath) const`
- L413 _public function_ `void SetInstanceUserData(const FString& InChannelName, const FGuid& InInstanceId, const FSoftObjectPath& InAssetPath, const FString& InUserData)`
- L421 _public function_ `TOptional<EAvaPlaybackAssetStatus> GetPlaybackAssetStatus(const FSoftObjectPath& InAssetPath) const`
- L427 _public function_ `void SetPlaybackAssetStatus(const FSoftObjectPath& InAssetPath, EAvaPlaybackAssetStatus InStatus)`
- L435 _public function_ `void AddTimeout(const FDateTime& InNewTimeout)` — Add a time by which a ping response should arrive
- L446 _public function_ `bool HasTimedOut(const FDateTime& InNow) const` — Check if ping response arrived on time
- L455 _public function_ `void ResetPingTimeout()` — Resets the ping timeout. This is done when the ping response is received.

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMedia/Private/Playback/AvaPlaybackClientDummy.h` (Private)


#### class `FAvaPlaybackClientDummy`  
`class FAvaPlaybackClientDummy : public IAvaPlaybackClient`  
_L7-56_
- inherits: `IAvaPlaybackClient`
- L9 _private member_ `static const FString EmptyString;`
- L10 _private member_ `static const TArray<FString> EmptyStringArray;`
- L14 _public function_ `virtual int32 GetNumConnectedServers() const override`
- L15 _public function_ `virtual TArray<FString> GetServerNames() const override`
- L16 _public function_ `virtual FMessageAddress GetServerAddress(const FString& InServerName) const override`
- L22 _public function_ `virtual bool HasServerUserData(const FString& InServerName, const FString& InKey) const override`
- L23 _public function_ `virtual const FString& GetServerUserData(const FString& InServerName, const FString& InKey) const override`
- L24 _public function_ `virtual bool HasUserData(const FString& InKey) const override`
- L25 _public function_ `virtual const FString& GetUserData(const FString& InKey) const override`
- L26 _public function_ `virtual void SetUserData(const FString& InKey, const FString& InData) override`
- L27 _public function_ `virtual void RemoveUserData(const FString& InKey) override`
- L28 _public function_ `virtual void BroadcastStatCommand(const FString& InCommand, bool bInBroadcastLocalState) override`
- L29 _public function_ `virtual void RequestPlaybackAssetStatus(const FSoftObjectPath& InAssetPath, const FString& InChannelOrServerName, bool bInForceRefresh) override`
- L30 _public function_ `virtual void RequestPlayback(const FGuid& InInstanceId, const FSoftObjectPath& InAssetPath, const FString& InChannelName, EAvaPlaybackAction InAction, const FString& InArguments) override`
- L31 _public function_ `virtual void RequestAnimPlayback(const FGuid& InInstanceId, const FSoftObjectPath& InAssetPath, const FString& InChannelName, const FAvaPlaybackAnimPlaySettings& InAnimSettings) override`
- L32 _public function_ `virtual void RequestAnimAction(const FGuid& InInstanceId, const FSoftObjectPath& InAssetPath, const FString& InChannelName, const FString& InAnimationName, EAvaPlaybackAnimAction InAction) override`
- L33 _public function_ `virtual void RequestRemoteControlUpdate(const FGuid& InInstanceId, const FSoftObjectPath& InAssetPath, const FString& InChannelName, const FAvaPlayableRemoteControlValues& InRemoteControlValues, EAvaPlayableRCUpdateFlags InFlags) override`
- L34 _public function_ `virtual void RequestPlayableTransitionStart(const FGuid& InTransitionId, TArray<FGuid>&& InEnterInstanceIds, TArray<FGuid>&& InPlayingInstanceIds, TArray<FGuid>&& InExitInstanceIds, TArray<FAvaPlayableRemoteControlValues>&& InEnterValues, const FName& InChannelName, EAvaPlayableTransitionFlags InTransitionFlags) override`
- L35 _public function_ `virtual void RequestPlayableTransitionStop(const FGuid& InTransitionId, const FName& InChannelName) override`
- L36 _public function_ `virtual void RequestBroadcast(const FString& InProfile, const FName& InChannel, const TArray<UMediaOutput*>& InRemoteMediaOutputs, EAvaBroadcastAction InAction, const FString& InServerName) override`
- L37 _public function_ `virtual bool IsMediaOutputRemoteFallback(const UMediaOutput* InMediaOutput) override`
- L38 _public function_ `virtual EAvaBroadcastIssueSeverity GetMediaOutputIssueSeverity(const FString& InServerName, const FString& InChannelName, const FGuid& InOutputGuid) const override`
- L39 _public function_ `virtual const TArray<FString>& GetMediaOutputIssueMessages(const FString& InServerName, const FString& InChannelName, const FGuid& InOutputGuid) const override`
- L40 _public function_ `virtual EAvaBroadcastOutputState GetMediaOutputState(const FString& InServerName, const FString& InChannelName, const FGuid& InOutputGuid) const override`
- L41 _public function_ `virtual bool HasAnyServerOnlineForChannel(const FName& InChannelName) const override`
- L42 _public function_ `virtual TArray<FString> GetOnlineServersForChannel(const FName& InChannelName) const override`
- L43 _public function_ `virtual TOptional<EAvaPlaybackStatus> GetRemotePlaybackStatus(const FGuid& InInstanceId, const FSoftObjectPath& InAssetPath, const FString& InChannelName, const FString& InServerName) const override`
- L47 _public function_ `virtual const FString* GetRemotePlaybackUserData(const FGuid& InInstanceId, const FSoftObjectPath& InAssetPath, const FString& InChannelName, const FString& InServerName) const override`
- L51 _public function_ `virtual TOptional<EAvaPlaybackAssetStatus> GetRemotePlaybackAssetStatus(const FSoftObjectPath& InAssetPath, const FString& InServerName) const override`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMedia/Private/Playback/AvaPlaybackMessages.h` (Private)


#### struct `FAvaPlaybackClientMessageBase`  
`struct FAvaPlaybackClientMessageBase`  
_L17-23_
- reflection: `USTRUCT()`
- L22 _public member_ `FString ClientName;` — `UPROPERTY()`

#### struct `FAvaPlaybackServerMessageBase`  
`struct FAvaPlaybackServerMessageBase`  
_L34-40_
- reflection: `USTRUCT()`
- desc: Notes: - ServerName vs HostName The Host name is the physical computer device the playback server runs on. A Server name is what the playback server is called and it is not necessarily the Host name. If there are multiple servers on the same host, then each server must have a different name. The Server name is a unique key to identify a server, while the host name is not.
- L39 _public member_ `FString ServerName;` — `UPROPERTY()`

#### struct `FAvaPlaybackPing`  
`struct FAvaPlaybackPing : public FAvaPlaybackClientMessageBase`  
_L46-57_
- reflection: `USTRUCT()`
- inherits: `FAvaPlaybackClientMessageBase`
- desc: Request published by client to discover servers.
- L52 _public member_ `bool bAutoPing = true;` — `UPROPERTY()` — Indicate if the ping was generated on a timer (auto) or manually sent through a user command.
- L56 _public member_ `float PingIntervalSeconds = 0.0f;` — `UPROPERTY()` — Defines the interval in seconds between each client's pings.

#### struct `FAvaPlaybackPong`  
`struct FAvaPlaybackPong : public FAvaPlaybackServerMessageBase`  
_L63-82_
- reflection: `USTRUCT()`
- inherits: `FAvaPlaybackServerMessageBase`
- desc: Response sent by server to client to be discovered.
- L69 _public member_ `bool bAutoPong = true;` — `UPROPERTY()` — Indicate if this is a reply from an auto ping.
- L73 _public member_ `bool bRequestClientInfo = false;` — `UPROPERTY()` — Server may request client info in case of a reconnection event.
- L77 _public member_ `FString ProjectContentPath;` — `UPROPERTY()` — Server's project content path.
- L81 _public member_ `uint32 ProcessId = 0;` — `UPROPERTY()` — Server's process id on the current host.

#### struct `FAvaPlaybackLog`  
`struct FAvaPlaybackLog : public FAvaPlaybackServerMessageBase`  
_L88-103_
- reflection: `USTRUCT()`
- inherits: `FAvaPlaybackServerMessageBase`
- desc: Replicate server's log messages.
- L93 _public member_ `FString Text;` — `UPROPERTY()`
- L96 _public member_ `uint8 Verbosity = 0;` — `UPROPERTY()`
- L99 _public member_ `FName Category;` — `UPROPERTY()`
- L102 _public member_ `double Time = 0.0;` — `UPROPERTY()`

#### struct `FAvaPlaybackUpdateClientInfo`  
`struct FAvaPlaybackUpdateClientInfo : public FAvaPlaybackClientMessageBase`  
_L109-121_
- reflection: `USTRUCT()`
- inherits: `FAvaPlaybackClientMessageBase`
- desc: Request sent by client to replicate it's information on the destination server.
- L114 _public member_ `FString ComputerName;` — `UPROPERTY()`
- L117 _public member_ `FString ProjectContentPath;` — `UPROPERTY()`
- L120 _public member_ `uint32 ProcessId = 0;` — `UPROPERTY()`

#### struct `FAvaPlaybackUpdateClientUserData`  
`struct FAvaPlaybackUpdateClientUserData : public FAvaPlaybackClientMessageBase`  
_L127-133_
- reflection: `USTRUCT()`
- inherits: `FAvaPlaybackClientMessageBase`
- desc: Request sent by client to replicate it's user data on the destination server.
- L132 _public member_ `TMap<FString, FString> UserDataEntries;` — `UPROPERTY()`

#### struct `FAvaPlaybackUpdateServerUserData`  
`struct FAvaPlaybackUpdateServerUserData : public FAvaPlaybackServerMessageBase`  
_L139-145_
- reflection: `USTRUCT()`
- inherits: `FAvaPlaybackServerMessageBase`
- desc: Request sent by server to replicate it's user data to the client.
- L144 _public member_ `TMap<FString, FString> UserDataEntries;` — `UPROPERTY()`

#### struct `FAvaPlaybackStatCommand`  
`struct FAvaPlaybackStatCommand : public FAvaPlaybackClientMessageBase`  
_L148-169_
- reflection: `USTRUCT()`
- inherits: `FAvaPlaybackClientMessageBase`
- L153 _public member_ `FString Command;` — `UPROPERTY()`
- L160 _public member_ `bool bClientStateReliable = false;` — `UPROPERTY()` — If the local client couldn't get a viewport client to run the stat command, the local state will not be reliable. In this case, the server state will be used.
- L168 _public member_ `TArray<FString> ClientEnabledRuntimeStats;` — `UPROPERTY()` — Because the commands are toggles, there may be desync of states between client and server(s). In order to correct that we also send a list of enabled states on the client so that servers can ensure they have the same states enabled.

#### struct `FAvaPlaybackStatStatus`  
`struct FAvaPlaybackStatStatus : public FAvaPlaybackServerMessageBase`  
_L175-194_
- reflection: `USTRUCT()`
- inherits: `FAvaPlaybackServerMessageBase`
- desc: Server's response when a stat command is received.
- L185 _public member_ `bool bClientStateReliable = false;` — `UPROPERTY()` — Replication of the same field from the command. This is used by the client to replicate the server state in case the command succeeded on the server and it had an unreliable state.
- L189 _public member_ `bool bCommandSucceeded = false;` — `UPROPERTY()` — Indicate if the server could execute the command.
- L193 _public member_ `TArray<FString> EnabledRuntimeStats;` — `UPROPERTY()` — Resulting enabled stats from the command.

#### struct `FAvaPlaybackDeviceProviderDataRequest`  
`struct FAvaPlaybackDeviceProviderDataRequest : public FAvaPlaybackClientMessageBase`  
_L202-205_
- reflection: `USTRUCT()`
- inherits: `FAvaPlaybackClientMessageBase`
- desc: Request sent by client to obtain the device provider data from destination server. The device provider data contains all available devices and their configuration installed on the server.

#### struct `FAvaPlaybackInstanceSettingsUpdate`  
`struct FAvaPlaybackInstanceSettingsUpdate : public FAvaPlaybackClientMessageBase`  
_L211-217_
- reflection: `USTRUCT()`
- inherits: `FAvaPlaybackClientMessageBase`
- desc: Request for the client to replicate it's Motion Design instance settings to the server.
- L216 _public member_ `FAvaInstanceSettings InstanceSettings;` — `UPROPERTY()`

#### struct `FAvaPlaybackPlayableSettingsUpdate`  
`struct FAvaPlaybackPlayableSettingsUpdate : public FAvaPlaybackClientMessageBase`  
_L223-229_
- reflection: `USTRUCT()`
- inherits: `FAvaPlaybackClientMessageBase`
- desc: Request for the client to replicate it's Motion Design instance settings to the server.
- L228 _public member_ `FAvaPlayableSettings PlayableSettings;` — `UPROPERTY()`

#### enum `EAvaPlaybackPackageEvent`  
`enum class EAvaPlaybackPackageEvent`  
_L232-238_
- reflection: `UENUM()`
- L234 _public enumerator_ `None`
- L235 _public enumerator_ `PreSave`
- L236 _public enumerator_ `PostSave`
- L237 _public enumerator_ `AssetDeleted`

#### struct `FAvaPlaybackPackageEvent`  
`struct FAvaPlaybackPackageEvent : public FAvaPlaybackClientMessageBase`  
_L244-253_
- reflection: `USTRUCT()`
- inherits: `FAvaPlaybackClientMessageBase`
- desc: Message sent by the client to inform servers that a local package has been modified by an event.
- L249 _public member_ `FName PackageName;` — `UPROPERTY()`
- L252 _public member_ `EAvaPlaybackPackageEvent Event = EAvaPlaybackPackageEvent::None;` — `UPROPERTY()`

#### struct `FAvaPlaybackAssetStatusRequest`  
`struct FAvaPlaybackAssetStatusRequest : public FAvaPlaybackClientMessageBase`  
_L260-273_
- reflection: `USTRUCT()`
- inherits: `FAvaPlaybackClientMessageBase`
- desc: Request by a client to obtain the status of an asset with the given path. Note: since this is an asset on disk, there is no channel name.
- L265 _public member_ `FSoftObjectPath AssetPath;` — `UPROPERTY()`
- L272 _public member_ `bool bForceRefresh = false;` — `UPROPERTY()` — If this is true, the server will perform a full asset status compare with the client. Otherwise, the server may use locally cached status for the given asset.

#### struct `FAvaPlaybackAssetStatus`  
`struct FAvaPlaybackAssetStatus : public FAvaPlaybackServerMessageBase`  
_L277-286_
- reflection: `USTRUCT()`
- inherits: `FAvaPlaybackServerMessageBase`
- desc: Response from the server to a playback asset status request.
- L282 _public member_ `FSoftObjectPath AssetPath;` — `UPROPERTY()`
- L285 _public member_ `EAvaPlaybackAssetStatus Status = EAvaPlaybackAssetStatus::Unknown;` — `UPROPERTY()`

#### struct `FAvaPlaybackCommand`  
`struct FAvaPlaybackCommand`  
_L292-315_
- reflection: `USTRUCT()`
- desc: Playback command for a given asset.
- L298 _public member_ `FGuid InstanceId;` — `UPROPERTY()` — Playback's instance Id.
- L302 _public member_ `FSoftObjectPath AssetPath;` — `UPROPERTY()` — Reference to the asset to playback.
- L306 _public member_ `FString ChannelName;` — `UPROPERTY()` — Broadcast channel the action will apply to.
- L310 _public member_ `EAvaPlaybackAction Action = EAvaPlaybackAction::None;` — `UPROPERTY()` — Action to do: Load, Play, Stop, Unload, etc.
- L314 _public member_ `FString Arguments;` — `UPROPERTY()` — Command additional arguments.

#### struct `FAvaPlaybackRequest`  
`struct FAvaPlaybackRequest : public FAvaPlaybackClientMessageBase`  
_L321-327_
- reflection: `USTRUCT()`
- inherits: `FAvaPlaybackClientMessageBase`
- desc: Request by a client to execute a batch playback of commands on the connected servers.
- L326 _public member_ `TArray<FAvaPlaybackCommand> Commands;` — `UPROPERTY()`

#### struct `FAvaPlaybackStatus`  
`struct FAvaPlaybackStatus : public FAvaPlaybackServerMessageBase`  
_L331-353_
- reflection: `USTRUCT()`
- inherits: `FAvaPlaybackServerMessageBase`
- desc: Response from the server to a playback request.
- L337 _public member_ `FGuid InstanceId;` — `UPROPERTY()` — Playback's instance Id.
- L340 _public member_ `FSoftObjectPath AssetPath;` — `UPROPERTY()`
- L343 _public member_ `FString ChannelName;` — `UPROPERTY()`
- L346 _public member_ `EAvaPlaybackStatus Status = EAvaPlaybackStatus::Unknown;` — `UPROPERTY()`
- L349 _public member_ `bool bValidUserData = false;` — `UPROPERTY()`
- L352 _public member_ `FString UserData;` — `UPROPERTY()`

#### struct `FAvaPlaybackStatuses`  
`struct FAvaPlaybackStatuses : public FAvaPlaybackServerMessageBase`  
_L360-377_
- reflection: `USTRUCT()`
- inherits: `FAvaPlaybackServerMessageBase`
- desc: Message batching the status of many assets per channel/host. Used to reduce message overhead.
- L365 _public member_ `FString ChannelName;` — `UPROPERTY()`
- L369 _public member_ `TArray<FGuid> InstanceIds;` — `UPROPERTY()` — Playback's instance Id.
- L372 _public member_ `TArray<FSoftObjectPath> AssetPaths;` — `UPROPERTY()`
- L376 _public member_ `EAvaPlaybackStatus Status = EAvaPlaybackStatus::Unknown;` — `UPROPERTY()` — Batches all assets with the same status.

#### struct `FAvaPlaybackAnimActionInfo`  
`struct FAvaPlaybackAnimActionInfo`  
_L380-389_
- reflection: `USTRUCT()`
- L385 _public member_ `FString AnimationName;` — `UPROPERTY()`
- L388 _public member_ `EAvaPlaybackAnimAction AnimationAction = EAvaPlaybackAnimAction::None;` — `UPROPERTY()`

#### struct `FAvaPlaybackAnimPlaybackRequest`  
`struct FAvaPlaybackAnimPlaybackRequest : public FAvaPlaybackClientMessageBase`  
_L396-415_
- reflection: `USTRUCT()`
- inherits: `FAvaPlaybackClientMessageBase`
- desc: Request by a client to execute an animation on a playback asset on a connected server.
- L402 _public member_ `FGuid InstanceId;` — `UPROPERTY()` — Playback's instance Id.
- L405 _public member_ `FSoftObjectPath AssetPath;` — `UPROPERTY()`
- L408 _public member_ `FString ChannelName;` — `UPROPERTY()`
- L411 _public member_ `TArray<FAvaPlaybackAnimPlaySettings> AnimPlaySettings;` — `UPROPERTY()`
- L414 _public member_ `TArray<FAvaPlaybackAnimActionInfo> AnimActionInfos;` — `UPROPERTY()`

#### struct `FAvaPlaybackSequenceEvent`  
`struct FAvaPlaybackSequenceEvent : public FAvaPlaybackServerMessageBase`  
_L419-441_
- reflection: `USTRUCT()`
- inherits: `FAvaPlaybackServerMessageBase`
- desc: Server replication of playback sequence events.
- L425 _public member_ `FGuid InstanceId;` — `UPROPERTY()` — Playback's instance Id.
- L428 _public member_ `FSoftObjectPath AssetPath;` — `UPROPERTY()`
- L431 _public member_ `FString ChannelName;` — `UPROPERTY()`
- L434 _public member_ `FString SequenceLabel;` — `UPROPERTY()`
- L437 _public member_ `EAvaPlayableSequenceEventType EventType = EAvaPlayableSequenceEventType::None;` — `UPROPERTY()`
- L440 _public member_ `int32 FrameNumber = 0;` — `UPROPERTY()`

#### struct `FAvaPlaybackRemoteControlUpdateRequest`  
`struct FAvaPlaybackRemoteControlUpdateRequest : public FAvaPlaybackClientMessageBase`  
_L444-463_
- reflection: `USTRUCT()`
- inherits: `FAvaPlaybackClientMessageBase`
- L450 _public member_ `FGuid InstanceId;` — `UPROPERTY()` — Playback's instance Id.
- L453 _public member_ `FSoftObjectPath AssetPath;` — `UPROPERTY()`
- L456 _public member_ `FString ChannelName;` — `UPROPERTY()`
- L459 _public member_ `FAvaPlayableRemoteControlValues RemoteControlValues;` — `UPROPERTY()`
- L462 _public member_ `EAvaPlayableRCUpdateFlags UpdateFlags = EAvaPlayableRCUpdateFlags::None;` — `UPROPERTY()`

#### struct `FAvaPlaybackTransitionStartRequest`  
`struct FAvaPlaybackTransitionStartRequest : public FAvaPlaybackClientMessageBase`  
_L466-498_
- reflection: `USTRUCT()`
- inherits: `FAvaPlaybackClientMessageBase`
- L471 _public member_ `FString ChannelName;` — `UPROPERTY()`
- L474 _public member_ `FGuid TransitionId;` — `UPROPERTY()`
- L477 _public member_ `TArray<FGuid> EnterInstanceIds;` — `UPROPERTY()`
- L480 _public member_ `TArray<FGuid> PlayingInstanceIds;` — `UPROPERTY()`
- L483 _public member_ `TArray<FGuid> ExitInstanceIds;` — `UPROPERTY()`
- L486 _public member_ `TArray<FAvaPlayableRemoteControlValues> EnterValues;` — `UPROPERTY()`
- L489 _public member_ `bool bUnloadDiscardedInstances = false;` — `UPROPERTY()`
- L493 _public member_ `uint8 TransitionFlags = 0;` — `UPROPERTY()` — See EAvaPlayableTransitionFlags.
- L495 _public function_ `EAvaPlayableTransitionFlags GetTransitionFlags() const`
- L496 _public function_ `void SetTransitionFlags(EAvaPlayableTransitionFlags InTransitionFlags)`

#### struct `FAvaPlaybackTransitionStopRequest`  
`struct FAvaPlaybackTransitionStopRequest : public FAvaPlaybackClientMessageBase`  
_L501-513_
- reflection: `USTRUCT()`
- inherits: `FAvaPlaybackClientMessageBase`
- L506 _public member_ `FString ChannelName;` — `UPROPERTY()`
- L509 _public member_ `FGuid TransitionId;` — `UPROPERTY()`
- L512 _public member_ `bool bUnloadDiscardedInstances = false;` — `UPROPERTY()`

#### struct `FAvaPlaybackTransitionEventEntry`  
`struct FAvaPlaybackTransitionEventEntry`  
_L520-541_
- reflection: `USTRUCT()`
- desc: Defines a single transition event entry. This is the payload for the transition events messages.
- L525 _public member_ `FGuid InstanceId;` — `UPROPERTY()`
- L528 _public member_ `uint8 EventFlags = static_cast<uint8>(EAvaPlayableTransitionEventFlags::None);` — `UPROPERTY()`
- L530 _public prototype_ `FAvaPlaybackTransitionEventEntry() = default;`
- L532 _public function_ `FAvaPlaybackTransitionEventEntry(const FGuid& InInstanceId, EAvaPlayableTransitionEventFlags InFlags) : InstanceId(InInstanceId) , EventFlags(static_cast<uint8>(InFlags))`
- L539 _public function_ `EAvaPlayableTransitionEventFlags GetEventFlags() const` — Because the enum is used as flags, we need to convert to uint8 manually. (Can't use TEnumAsByte for this apparently.)
- L540 _public function_ `void SetEventFlags(EAvaPlayableTransitionEventFlags InFlags)`

#### struct `FAvaPlaybackTransitionEvent`  
`struct FAvaPlaybackTransitionEvent : public FAvaPlaybackServerMessageBase`  
_L547-562_
- reflection: `USTRUCT()`
- inherits: `FAvaPlaybackServerMessageBase`
- desc: Single entry transition event message.
- L552 _public member_ `FString ChannelName;` — `UPROPERTY()`
- L555 _public member_ `FGuid TransitionId;` — `UPROPERTY()`
- L558 _public member_ `FAvaPlaybackTransitionEventEntry Entry;` — `UPROPERTY()`
- L561 _public member_ `int32 FrameNumber = 0;` — `UPROPERTY()`

#### struct `FAvaPlaybackTransitionEventMulti`  
`struct FAvaPlaybackTransitionEventMulti : public FAvaPlaybackServerMessageBase`  
_L569-584_
- reflection: `USTRUCT()`
- inherits: `FAvaPlaybackServerMessageBase`
- desc: Multi-entries transition event message. We use this to group the events in a one message to ensure correct order on reception.
- L574 _public member_ `FString ChannelName;` — `UPROPERTY()`
- L577 _public member_ `FGuid TransitionId;` — `UPROPERTY()`
- L580 _public member_ `TArray<FAvaPlaybackTransitionEventEntry> Entries;` — `UPROPERTY()`
- L583 _public member_ `int32 FrameNumber = 0;` — `UPROPERTY()`

#### struct `FAvaBroadcastOutputData`  
`struct FAvaBroadcastOutputData`  
_L593-610_
- reflection: `USTRUCT()`
- desc: Encapsulates a UMediaOutput object in binary form to be able to serialize it nested within the broadcast request.
- L598 _public member_ `FAvaBroadcastMediaOutputInfo OutputInfo;` — `UPROPERTY()`
- L601 _public member_ `TSoftClassPtr<UMediaOutput> MediaOutputClass;` — `UPROPERTY()`
- L604 _public member_ `TArray<uint8> SerializedData;` — `UPROPERTY()`
- L607 _public member_ `uint64 ObjectFlags = 0;` — `UPROPERTY()`
- L609 _public function_ `EObjectFlags GetObjectFlags() const`

#### struct `FAvaBroadcastRequest`  
`struct FAvaBroadcastRequest : public FAvaPlaybackClientMessageBase`  
_L614-632_
- reflection: `USTRUCT()`
- inherits: `FAvaPlaybackClientMessageBase`
- desc: Request by a client to execute an action on broadcast channel(s).
- L620 _public member_ `FString Profile;` — `UPROPERTY()` — Profile to select for broadcast.
- L624 _public member_ `FString Channel;` — `UPROPERTY()` — Channel name. If empty, command is for all channels.
- L627 _public member_ `TArray<FAvaBroadcastOutputData> MediaOutputs;` — `UPROPERTY()`
- L631 _public member_ `EAvaBroadcastAction Action = EAvaBroadcastAction::None;` — `UPROPERTY()` — Action to do on channel: Start, Stop, Disable, etc.

#### struct `FAvaBroadcastChannelSettingsUpdate`  
`struct FAvaBroadcastChannelSettingsUpdate : public FAvaPlaybackClientMessageBase`  
_L636-650_
- reflection: `USTRUCT()`
- inherits: `FAvaPlaybackClientMessageBase`
- desc: Request by a client to update a broadcast channel's settings.
- L642 _public member_ `FString Profile;` — `UPROPERTY()` — Profile to select for broadcast.
- L646 _public member_ `FString Channel;` — `UPROPERTY()` — Channel name. If empty, command is for all channels.
- L649 _public member_ `FAvaViewportQualitySettings QualitySettings;` — `UPROPERTY(meta = (HideHeader, ShowPresets))`

#### struct `FAvaBroadcastStatusRequest`  
`struct FAvaBroadcastStatusRequest : public FAvaPlaybackClientMessageBase`  
_L661-667_
- reflection: `USTRUCT()`
- inherits: `FAvaPlaybackClientMessageBase`
- desc: Client sends this request to have a status of broadcast. This is used by the client when it connects to a server which might be already broadcasting. This happens if the client disconnects and reconnects. It needs to query the full status of the server upon connection.
- L666 _public member_ `bool bIncludeMediaOutputData = false;` — `UPROPERTY()`

#### struct `FAvaBroadcastSettings`  
`struct FAvaBroadcastSettings`  
_L670-696_
- reflection: `USTRUCT()`
- L676 _public member_ `FLinearColor ChannelClearColor = FLinearColor::Black;` — `UPROPERTY()` — Specifies the background clear color for the channel.
- L680 _public member_ `TEnumAsByte<EPixelFormat> ChannelDefaultPixelFormat = EPixelFormat::PF_B8G8R8A8;` — `UPROPERTY()` — Pixel format used if no media output has specific format requirement.
- L684 _public member_ `FIntPoint ChannelDefaultResolution = FIntPoint(1920, 1080);` — `UPROPERTY()` — Resolution used if no media output has specific resolution requirement.
- L691 _public member_ `bool bDrawPlaceholderWidget = false;` — `UPROPERTY()` — Enables drawing the placeholder widget when there is no Motion Design asset playing. If false, the channel is cleared to the background color.
- L695 _public member_ `FSoftObjectPath PlaceholderWidgetClass;` — `UPROPERTY()` — Specify a place holder widget to render when no Motion Design asset is playing.

#### struct `FAvaBroadcastSettingsUpdate`  
`struct FAvaBroadcastSettingsUpdate : public FAvaPlaybackClientMessageBase`  
_L702-708_
- reflection: `USTRUCT()`
- inherits: `FAvaPlaybackClientMessageBase`
- desc: Request for the client to replicate it's broadcast settings to the server.
- L707 _public member_ `FAvaBroadcastSettings BroadcastSettings;` — `UPROPERTY()`

#### struct `FAvaBroadcastOutputStatus`  
`struct FAvaBroadcastOutputStatus`  
_L714-726_
- reflection: `USTRUCT()`
- desc: Encapsulate the complete status of a media output.
- L719 _public member_ `EAvaBroadcastOutputState MediaOutputState = EAvaBroadcastOutputState::Invalid;` — `UPROPERTY()`
- L722 _public member_ `EAvaBroadcastIssueSeverity MediaIssueSeverity = EAvaBroadcastIssueSeverity::None;` — `UPROPERTY()`
- L725 _public member_ `TArray<FString> MediaIssueMessages;` — `UPROPERTY()`

#### struct `FAvaBroadcastStatus`  
`struct FAvaBroadcastStatus : public FAvaPlaybackServerMessageBase`  
_L732-772_
- reflection: `USTRUCT()`
- inherits: `FAvaPlaybackServerMessageBase`
- desc: Server's response when channel's broadcast status changes
- L738 _public member_ `FString Profile;` — `UPROPERTY()` — Profile to select for broadcast.
- L742 _public member_ `FString ChannelName;` — `UPROPERTY()` — Channel name. If empty, command is for all channels of the profile.
- L746 _public member_ `int32 ChannelIndex = 0;` — `UPROPERTY()` — Index of the channel in the profile.
- L750 _public member_ `int32 NumChannels = 0;` — `UPROPERTY()` — Number of channels in the profile.
- L753 _public member_ `EAvaBroadcastChannelState ChannelState = EAvaBroadcastChannelState::Idle;` — `UPROPERTY()`
- L756 _public member_ `EAvaBroadcastIssueSeverity ChannelIssueSeverity = EAvaBroadcastIssueSeverity::None;` — `UPROPERTY()`
- L759 _public member_ `TMap<FGuid, FAvaBroadcastOutputStatus> MediaOutputStatuses;` — `UPROPERTY()`
- L767 _public member_ `bool bIncludeMediaOutputData = false;` — `UPROPERTY()` — This is required to know if the MediaOutputs is empty because the data was not included or if it is because the data was included and there is actually no outputs defined on that channel.
- L771 _public member_ `TArray<FAvaBroadcastOutputData> MediaOutputs;` — `UPROPERTY()` — Remark: this is only included if bIncludeMediaOutputData == true in the request.

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMedia/Private/Playback/AvaPlaybackServer.h` (Private)


#### class `FAvaPlaybackServer`  
`class FAvaPlaybackServer : public TSharedFromThis<FAvaPlaybackServer>, public IAvaPlaybackServer`  
_L35-380_
- inherits: `TSharedFromThis<FAvaPlaybackServer>,IAvaPlaybackServer`
- desc: Playback (and Broadcast) Server The playback server implements the commands for broadcast (channels and outputs) and playback. Playback assets are either "playables" or "playback graphs", however the playback server will create playback graphs for everything. If the asset to play is a "playable" (e.g. a level), it will create a transient playback graph for it. A lot of the playback commands are geared toward running a playback graph with a single playable node, mostly because this system is only used with rundowns or playback graphs run on the client side. So, it will emulate a client-side playable with a local transient playback graph with one player node. The use case of running a more complex playback graph asset on the server side has not occured yet.
- L38 _public prototype_ `FAvaPlaybackServer();`
- L41 _public prototype_ `void Init(const FString& InAssignedServerName);`
- L47 _public prototype_ `TArray<FString> GetAllChannelsFromPlayingPlaybacks(const FSoftObjectPath& InAssetPath = FSoftObjectPath()) const;` — Returns a list of channel names from all the playing playback instances. Optionally filter for a given asset.
- L52 _public prototype_ `void StartShuttingDown();` — Indicate the manager is in a shutdown sequence and will force game instances to destroy worlds right away.
- L56 _public prototype_ `virtual TArray<FPlaybackInstanceReference> StopPlaybacks(const FString& InChannelName = FString(), const FSoftObjectPath& InAssetPath = FSoftObjectPath(), bool bInUnload = true) override;`
- L57 _public prototype_ `virtual TArray<FPlaybackInstanceReference> StartPlaybacks() override;`
- L59 _public prototype_ `virtual void StartBroadcast() override;`
- L60 _public prototype_ `virtual void StopBroadcast() override;`
- L62 _public function_ `virtual const FString& GetName() const override`
- L64 _public function_ `virtual bool HasUserData(const FString& InKey) const override`
- L66 _public prototype_ `virtual const FString& GetUserData(const FString& InKey) const override;`
- L68 _public prototype_ `virtual void SetUserData(const FString& InKey, const FString& InData) override;`
- L70 _public prototype_ `virtual void RemoveUserData(const FString& InKey) override;`
- L72 _public prototype_ `virtual TArray<FString> GetClientNames() const override;`
- L74 _public prototype_ `virtual FMessageAddress GetClientAddress(const FString& InClientName) const override;`
- L76 _public prototype_ `virtual bool HasClientUserData(const FString& InClientName, const FString& InKey) const override;`
- L78 _public prototype_ `virtual const FString& GetClientUserData(const FString& InClientName, const FString& InKey) const override;`
- L80 _public prototype_ `virtual const IAvaBroadcastSettings* GetBroadcastSettings() const override;`
- L82 _public prototype_ `virtual const FAvaInstanceSettings* GetAvaInstanceSettings() const override;`
- L84 _public prototype_ `virtual const FAvaPlayableSettings* GetPlayableSettings() const override;`
- L86 _public function_ `virtual const FAvaPlaybackManager& GetPlaybackManager() const override`
- L87 _public function_ `virtual FAvaPlaybackManager& GetPlaybackManager() override`
- L91 _public function_ `TSharedPtr<FAvaPlaybackInstance> FindActivePlaybackInstance(const FGuid& InInstanceId) const`
- L97 _public function_ `bool RemoveActivePlaybackInstance(const FGuid& InInstanceId)`
- L102 _public prototype_ `bool RemovePlaybackInstanceTransition(const FGuid& InTransitionId);`
- L104 _public prototype_ `void SendPlayableTransitionEvent( const FGuid& InTransitionId, const FAvaPlaybackTransitionEventEntry& InEntry, const FName& InChannelName, const FString& InClientName);`
- L108 _public prototype_ `void SendPlayableTransitionEventMulti( const FGuid& InTransitionId, TArray<FAvaPlaybackTransitionEventEntry>&& InEntries, const FName& InChannelName, const FString& InClientName);`
- L114 _public prototype_ `void HandlePlaybackPing(const FAvaPlaybackPing& InMessage, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& InContext);` — Message handlers
- L115 _public prototype_ `void HandleUpdateClientUserData(const FAvaPlaybackUpdateClientUserData& InMessage, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& InContext);`
- L116 _public prototype_ `void HandleStatCommand(const FAvaPlaybackStatCommand& InMessage, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& InContext);`
- L117 _public prototype_ `void HandleDeviceProviderDataRequest(const FAvaPlaybackDeviceProviderDataRequest& InMessage, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& InContext);`
- L118 _public prototype_ `void HandleUpdateClientInfo(const FAvaPlaybackUpdateClientInfo& InMessage, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& InContext);`
- L119 _public prototype_ `void HandleAvaInstanceSettingsUpdate(const FAvaPlaybackInstanceSettingsUpdate& InMessage, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& InContext);`
- L120 _public prototype_ `void HandlePlayableSettingsUpdate(const FAvaPlaybackPlayableSettingsUpdate& InMessage, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& InContext);`
- L121 _public prototype_ `void HandlePackageEvent(const FAvaPlaybackPackageEvent& InMessage, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& InContext);`
- L122 _public prototype_ `void HandlePlaybackAssetStatusRequest(const FAvaPlaybackAssetStatusRequest& InMessage, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& InContext);`
- L123 _public prototype_ `void HandlePlaybackRequest(const FAvaPlaybackRequest& InMessage, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& InContext);`
- L124 _public prototype_ `void HandleAnimPlaybackRequest(const FAvaPlaybackAnimPlaybackRequest& InMessage, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& InContext);`
- L125 _public prototype_ `void HandleRemoteControlUpdateRequest(const FAvaPlaybackRemoteControlUpdateRequest& InMessage, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& InContext);`
- L126 _public prototype_ `void HandlePlayableTransitionStartRequest(const FAvaPlaybackTransitionStartRequest& InMessage, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& InContext);`
- L127 _public prototype_ `void HandlePlayableTransitionStopRequest(const FAvaPlaybackTransitionStopRequest& InMessage, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& InContext);`
- L128 _public prototype_ `void HandleBroadcastSettingsUpdate(const FAvaBroadcastSettingsUpdate& InMessage, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& InContext);`
- L129 _public prototype_ `void HandleBroadcastRequest(const FAvaBroadcastRequest& InMessage, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& InContext);`
- L130 _public prototype_ `void HandleBroadcastChannelSettingsUpdate(const FAvaBroadcastChannelSettingsUpdate& InMessage, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& InContext);`
- L131 _public prototype_ `void HandleBroadcastStatusRequest(const FAvaBroadcastStatusRequest& InMessage, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& InContext);`
- L134 _public prototype_ `FString GetMessageEndpointAddressId() const;` — Returns underlying message bus endpoint address id
- L137 _protected prototype_ `void Tick();`
- L139 _protected prototype_ `void RegisterCommands();`
- L142 _protected prototype_ `void StartPlaybackCommand(const TArray<FString>& InArgs);` — Command handlers
- L143 _protected prototype_ `void StopPlaybackCommand(const TArray<FString>& InArgs);`
- L144 _protected prototype_ `void StartBroadcastCommand(const TArray<FString>& InArgs);`
- L145 _protected prototype_ `void StopBroadcastCommand(const TArray<FString>& InArgs);`
- L146 _protected prototype_ `void SetUserDataCommand(const TArray<FString>& InArgs);`
- L147 _protected prototype_ `void ShowStatusCommand(const TArray<FString>& InArgs);`
- L150 _protected prototype_ `void OnAvaMediaSettingsChanged(UObject*, struct FPropertyChangedEvent&);` — Event handlers
- L151 _protected prototype_ `void OnChannelChanged(const FAvaBroadcastOutputChannel& InChannel, EAvaBroadcastChannelChange InChange);`
- L152 _protected prototype_ `void OnMediaOutputStateChanged(const FAvaBroadcastOutputChannel& InChannel, const UMediaOutput* InMediaOutput);`
- L153 _protected prototype_ `void OnAvaAssetSyncStatusReceived(const FAvaPlaybackAssetSyncStatusReceivedParams& InParams);`
- L154 _protected prototype_ `void OnPlaybackInstanceInvalidated(const FAvaPlaybackInstance& InPlaybackInstance);`
- L155 _protected prototype_ `void OnPlaybackInstanceStatusChanged(const FAvaPlaybackInstance& InPlaybackInstance);`
- L156 _protected prototype_ `void OnPlaybackAssetRemoved(const FSoftObjectPath& InAssetPath);`
- L157 _protected prototype_ `void OnPlayableSequenceEvent(UAvaPlayable* InPlayable, FName InSequenceLabel, EAvaPlayableSequenceEventType InEventType);`
- L159 _protected prototype_ `void ApplyAvaMediaSettings();`
- L162 _protected function_ `template<typename MessageType> void FillServerInfo(MessageType* InMessage)`
- L168 _protected function_ `template<typename MessageType> void SendResponse(MessageType* InMessage, const FMessageAddress& InRecipient, EMessageFlags flags = EMessageFlags::None)`
- L176 _protected function_ `template<typename MessageType> void SendResponse(MessageType* InMessage, const TArray<FMessageAddress>& InRecipients, EMessageFlags flags = EMessageFlags::None)`
- L183 _protected prototype_ `void SendUserDataUpdate(const TArray<FMessageAddress>& InRecipients);`
- L185 _protected prototype_ `void SendChannelStatusUpdate(const FString& InChannelName, const FAvaBroadcastOutputChannel& InChannel, const FMessageAddress& InSender, bool bInIncludeOutputData = false);`
- L186 _protected prototype_ `void SendAllChannelStatusUpdate(const FMessageAddress& InSender, bool bInIncludeOutputData = false);`
- L187 _protected prototype_ `void SendLogMessage(const TCHAR* V, ELogVerbosity::Type Verbosity, const FName& Category, double Time);`
- L190 _protected prototype_ `void ExecutePendingPlaybackCommands(const FDateTime& InUtcNow);` — Playback Commands
- L192 _protected prototype_ `TSharedPtr<FAvaPlaybackInstance> GetOrLoadPlaybackInstance(const FGuid& InInstanceId, const FString& InChannelName, const FSoftObjectPath& InAssetPath, const FString& InLoadOptions);`
- L193 _protected prototype_ `void LoadPlayback(const FMessageAddress& InReplyToAddress, const FGuid& InInstanceId, const FString& InChannelName, const FSoftObjectPath& InAssetPath, const FString& InLoadOptions);`
- L194 _protected prototype_ `void StartPlayback(const FMessageAddress& InReplyToAddress, const FGuid& InInstanceId, const FString& InChannelName, const FSoftObjectPath& InAssetPath, const FString& InLoadOptions);`
- L195 _protected prototype_ `void StopPlayback(const FMessageAddress& InReplyToAddress, const FGuid& InInstanceId, const FString& InChannelName, const FSoftObjectPath& InAssetPath);`
- L196 _protected prototype_ `void UnloadPlayback(const FMessageAddress& InReplyToAddress, const FGuid& InInstanceId, const FString& InChannelName, const FSoftObjectPath& InAssetPath);`
- L197 _protected prototype_ `bool SetPlaybackUserData(const FMessageAddress& InReplyToAddress, const FGuid& InInstanceId, const FString& InUserData);`
- L198 _protected prototype_ `bool SendPlaybackUserData(const FMessageAddress& InReplyToAddress, const FGuid& InInstanceId);`
- L199 _protected prototype_ `void SendPlaybackStatus(const FMessageAddress& InReplyToAddress, const FGuid& InInstanceId, const FString& InChannelName, const FSoftObjectPath& InAssetPath);`
- L201 _protected prototype_ `void SendPlaybackStatus(const FMessageAddress& InSendTo, const FGuid& InInstanceId, const FString& InChannelName, const FSoftObjectPath& InAssetPath, EAvaPlaybackStatus InStatus);`
- L202 _protected prototype_ `void SendPlaybackStatus(const TArray<FMessageAddress>& InRecipients, const FGuid& InInstanceId, const FString& InChannelName, const FSoftObjectPath& InAssetPath, EAvaPlaybackStatus InStatus);`
- L203 _protected prototype_ `void SendPlaybackStatuses(const FMessageAddress& InSendTo, const FString& InChannelName, const TArray<FPlaybackInstanceReference>& InInstances, EAvaPlaybackStatus InStatus);`
- L204 _protected prototype_ `void SendAllPlaybackStatusesForChannelAndAssetPath(const FMessageAddress& InSendTo, const FString& InChannelName, const FSoftObjectPath& InAssetPath);`
- L205 _protected prototype_ `void SendPlaybackAssetStatus(const FMessageAddress& InSendTo, const FSoftObjectPath& InAssetPath, EAvaPlaybackAssetStatus InStatus);`
- L207 _protected function_ `EAvaPlaybackStatus GetUnloadedPlaybackStatus(const FSoftObjectPath& InAssetPath)`
- L212 _protected prototype_ `bool UpdateChannelOutputConfig(FAvaBroadcastOutputChannel& InChannel, const TArray<FAvaBroadcastOutputData>& InMediaOutputs, bool bInRefreshState);`
- L215 _private member_ `FString ComputerName;`
- L216 _private member_ `FString ServerName;`
- L217 _private member_ `FString ProjectContentPath;`
- L218 _private member_ `uint32 ProcessId = 0;`
- L219 _private member_ `TMap<FString, FString> UserDataEntries;`
- L222 _private member_ `TSharedPtr<FMessageEndpoint, ESPMode::ThreadSafe> MessageEndpoint;` — Holds the messaging endpoint.
- L224 _private member_ `TArray<IConsoleObject*> ConsoleCommands;`
- L227 _private member_ `TSharedPtr<FAvaPlaybackManager> Manager;` — The playback server has its own playback manager to not interfere with the local one.
- L232 _private member_ `bool bBlockChannelStatusUpdate = false;` — This is used to block sending status update from the channel event while the channels are refreshing state on media output state changes. This avoid sending spurious channel states while the update is not completed for all outputs.
- L248 _private member_ `TArray<TSharedPtr<FPendingPlaybackCommand>> PendingPlaybackCommands;` — Accumulate all the playback commands and execute them all in one batch on the next tick.
- L251 _private member_ `TMap<FGuid, TSharedPtr<FAvaPlaybackInstance>> ActivePlaybackInstances;` — Keep an map of active instances per id for fast lookup.
- L254 _private member_ `TUniquePtr<FServerPlaybackInstanceTransitionCollection> PlaybackInstanceTransitions;`
- L278 _private member_ `TUniquePtr<FReplicationOutputDevice> ReplicationOutputDevice;`
- L280 _private member_ `TOptional<ELogVerbosity::Type> LogReplicationVerbosityFromCommandLine;`
- L354 _private member_ `TMap<FString, TSharedPtr<FClientInfo>> Clients;` — Key is ClientName
- L356 _private prototype_ `FClientInfo& GetOrCreateClientInfo(const FString& InClientName, const FMessageAddress& InClientAddress);`
- L357 _private prototype_ `FClientInfo* GetClientInfo(const FMessageAddress& InClientAddress) const;`
- L358 _private function_ `FClientInfo* GetClientInfo(const FString& InClientName) const`
- L363 _private prototype_ `const FString& GetClientNameSafe(const FMessageAddress& InClientAddress) const;`
- L364 _private prototype_ `const FMessageAddress& GetClientAddressSafe(const FString& InClientName) const;`
- L365 _private prototype_ `TArray<FMessageAddress> GetAllClientAddresses(bool bInExcludeClientOnLocalProcess = false) const;`
- L366 _private prototype_ `void RemoveDeadClients(const FDateTime& InCurrentTime);`
- L367 _private prototype_ `void OnClientAdded(const FClientInfo& InClientInfo);`
- L368 _private prototype_ `void OnClientRemoved(const FClientInfo& InRemovedClient);`
- L370 _private prototype_ `bool IsLocalClient(const FClientInfo& ClientInfo) const;` — A local client will run from the same computer and project folder as the current server.
- L371 _private function_ `bool IsLocalClient(const FMessageAddress& InClientAddress) const`
- L376 _private function_ `bool IsClientOnLocalProcess(const FClientInfo& ClientInfo) const`

#### struct `FAvaPlaybackServer::FPendingPlaybackCommand`  
`struct FPendingPlaybackCommand`  
_L234-245_
- L236 _public member_ `FDateTime ReceivedUtc;`
- L237 _public member_ `uint32 ReceivedFrameNumber;`
- L238 _public member_ `int32 Priority;`
- L239 _public member_ `FMessageAddress ReplyTo;`
- L240 _public member_ `FAvaPlaybackCommand Command;`
- L242 _public function_ `FPendingPlaybackCommand(const FDateTime& InReceivedUtc, uint32 InReceivedFrameNumber, int32 InPriority, const FMessageAddress& InReplyTo, const FAvaPlaybackCommand& InCommand) : ReceivedUtc(InReceivedUtc), ReceivedFrameNumber(InReceivedFrameNumber), Priority(InPriority), ReplyTo(InReplyTo), Command(InCommand)`

#### class `FAvaPlaybackServer::FReplicationOutputDevice`  
`class FReplicationOutputDevice : public FOutputDevice`  
_L259-276_
- inherits: `FOutputDevice`
- desc: Routes the log messages to the server for replication over the message bus.
- L262 _public prototype_ `FReplicationOutputDevice(FAvaPlaybackServer* InServer);`
- L266 _public prototype_ `void SetVerbosityThreshold(ELogVerbosity::Type InVerbosityThreshold);` — Set the minimum verbosity that will be replicated to the client.
- L270 _protected prototype_ `virtual void Serialize(const TCHAR* InText, ELogVerbosity::Type InVerbosity, const FName& InCategory) override;`
- L271 _protected prototype_ `virtual void Serialize(const TCHAR* InText, ELogVerbosity::Type InVerbosity, const FName& InCategory, double InTime) override;`
- L274 _private member_ `FAvaPlaybackServer* Server;`
- L275 _private member_ `ELogVerbosity::Type VerbosityThreshold = ELogVerbosity::Type::NoLogging;`

#### class `FAvaPlaybackServer::FClientBroadcastSettings`  
`class FClientBroadcastSettings : public IAvaBroadcastSettings`  
_L282-295_
- inherits: `IAvaBroadcastSettings`
- L285 _public member_ `FAvaBroadcastSettings Settings;`
- L286 _public prototype_ `virtual ~FClientBroadcastSettings() override = default;`
- L289 _public function_ `virtual const FLinearColor& GetChannelClearColor() const override` — IAvaBroadcastSettings
- L290 _public function_ `virtual EPixelFormat GetDefaultPixelFormat() const override`
- L291 _public function_ `virtual const FIntPoint& GetDefaultResolution() const override`
- L292 _public function_ `virtual bool IsDrawPlaceholderWidget() const override`
- L293 _public function_ `virtual const FSoftObjectPath& GetPlaceholderWidgetClass() const override`

#### class `FAvaPlaybackServer::FClientInfo`  
`class FClientInfo`  
_L298-353_
- desc: Remote Client Info
- L301 _public member_ `FMessageAddress Address;`
- L302 _public member_ `FString ClientName;`
- L303 _public member_ `FString ComputerName;`
- L304 _public member_ `FString ProjectContentPath;`
- L305 _public member_ `uint32 ProcessId = 0;`
- L306 _public member_ `TMap<FString, FString> UserDataEntries;`
- L307 _public member_ `FClientBroadcastSettings BroadcastSettings;`
- L308 _public member_ `FAvaInstanceSettings AvaInstanceSettings;`
- L309 _public member_ `FAvaPlayableSettings PlayableSettings;`
- L311 _public member_ `bool bClientInfoReceived = false;`
- L318 _public member_ `TSharedPtr<FAvaPlaybackSyncManager> MediaSyncManager;` — The status of the server's asset compared to the remote is tracked on the server side. For now, the remote client is considered to have the reference asset. But in the future, a hub may hold the reference asset instead.
- L320 _public member_ `TOptional<FDateTime> PingTimeout;`
- L322 _public prototype_ `FClientInfo(const FMessageAddress& InClientAddress, const FString& InClientName);`
- L323 _public prototype_ `~FClientInfo();`
- L329 _public function_ `void AddTimeout(const FDateTime& InNewTimeout)` — Add a time by which a new ping should arrive
- L340 _public function_ `bool HasTimedOut(const FDateTime& InNow) const` — Check if new ping arrived on time
- L349 _public function_ `void ResetPingTimeout()` — Resets the ping timeout. This is done when the ping response is received.

#### Free symbols / members of external scopes

- L20 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogAvaPlaybackServer, Log, All);`
- L20 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogAvaPlaybackServer, Log, All);`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMedia/Private/Playback/AvaPlaybackServerProcess.h` (Private)


#### class `FAvaPlaybackServerProcess`  
`class FAvaPlaybackServerProcess`  
_L13-48_
- desc: Helper class wrapping and managing a process handle to the game mode local playback server process.
- L16 _public prototype_ `FAvaPlaybackServerProcess() = default;`
- L22 _public prototype_ `explicit FAvaPlaybackServerProcess(FProcHandle&& InProcessHandle);` — @brief Construct from an already running process handle. @param InProcessHandle Existing process handle.
- L24 _public prototype_ `bool IsLaunched();`
- L25 _public prototype_ `bool Launch();`
- L26 _public prototype_ `void Stop();`
- L33 _public prototype_ `static TSharedPtr<FAvaPlaybackServerProcess> Find(const FAvaPlaybackClient& InPlaybackClient);` — @brief Returns a playback server process object wrapping the process handle of an existing server process. @param InPlaybackClient Playback client instance to use for finding the server. @return A new object wrapping the process handle of the existing server process. It will return null if no existing server is found.
- L44 _public prototype_ `static TSharedPtr<FAvaPlaybackServerProcess> FindOrCreate(const FAvaPlaybackClient& InPlaybackClient);` — @brief Returns a playback server process object that wraps the process handle of either the existing server process or a newly created one. The playback server may be running in a separate process already. If so, it will be detected by the playback client. The playback client will also know it's process id so a handle to the process can be opened. @param InPlaybackClient Playback client instance to use for finding the server. @return A new object wrapping the process handle of the server process.
- L47 _private member_ `FProcHandle ProcessHandle;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMedia/Private/Playback/AvaPlaybackSyncManager.h` (Private)


#### struct `FAvaPlaybackAssetSyncStatusReceivedParams`  
`struct FAvaPlaybackAssetSyncStatusReceivedParams`  
_L12-17_
- L14 _public member_ `const FString& RemoteName;`
- L15 _public member_ `const FSoftObjectPath& AssetPath;`
- L16 _public member_ `bool bNeedsSync;`

#### class `FAvaPlaybackSyncManager`  
`class FAvaPlaybackSyncManager : public TSharedFromThis<FAvaPlaybackSyncManager>`  
_L24-83_
- inherits: `TSharedFromThis<FAvaPlaybackSyncManager>`
- desc: Implements tracking and caching the status of local assets compared to the corresponding assets on a given remote. The remote assets are considered to be the reference. For each tracked assets, a status of "need sync" (true) or "up to date" (false) is kept.
- L27 _public prototype_ `FAvaPlaybackSyncManager(const FString& InRemoteName);`
- L28 _public prototype_ `~FAvaPlaybackSyncManager();`
- L30 _public function_ `bool IsEnabled() const`
- L31 _public prototype_ `void SetEnable(bool bInEnabled);`
- L33 _public prototype_ `void Tick();`
- L43 _public prototype_ `TOptional<bool> GetAssetSyncStatus(const FSoftObjectPath& InAssetPath, bool bInForceRefresh);` — Returns the last cached asset sync status for the given asset if available. The sync status can be true (i.e. need sync) or false (i.e. up to date). If it is not available, a sync compare request is made with the specified remote and the result is posted through OnAvaAssetSyncStatusReceived event when it is received. If bInForceRefresh is true, a request will be made even if the status was already cached.
- L48 _public prototype_ `void EnumerateAllTrackedPackages(TFunctionRef<void(const FName& , bool )> InFunction) const;` — Enumerate all tracked packages in the manager.
- L50 _public prototype_ `TArray<FName> GetPendingRequests() const;`
- L55 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnAvaAssetSyncStatusReceived, const FAvaPlaybackAssetSyncStatusReceivedParams&);` — Delegate called when an asset sync status changed.
- L56 _public member_ `FOnAvaAssetSyncStatusReceived OnAvaAssetSyncStatusReceived;`
- L59 _private prototype_ `void RegisterEventHandlers();`
- L60 _private prototype_ `void UnregisterEventHandlers();`
- L62 _private prototype_ `void RequestPackageSyncStatus(const FName& InPackageName);`
- L63 _private prototype_ `void HandleExpiredRequest(const FName& InPackageName);`
- L64 _private prototype_ `void HandleFailedRequest(const FName& InPackageName, const FString& InErrorMessage);`
- L65 _private prototype_ `void HandleSyncStatusReceived(const FName& InPackageName, bool bInNeedsSynchronization);`
- L68 _private prototype_ `void HandleAvaSyncPackageModified(IAvaMediaSyncProvider* InAvaMediaSyncProvider, const FName& InPackageName);` — Event handlers
- L69 _private prototype_ `void HandlePackageSaved(const FString& InPackageFileName, UPackage* InPackage, FObjectPostSaveContext InObjectSaveContext);`
- L70 _private prototype_ `void HandleAssetRemoved(const FAssetData& InAssetData);`
- L73 _private member_ `FString RemoteName;` — Corresponding remote to be comparing with.
- L76 _private member_ `bool bEnabled = true;` — Determines if the sync manager is going to be used for the corresponding remote.
- L79 _private member_ `TMap<FName, bool> PackageStatuses;` — Maps package names and sync status.
- L82 _private member_ `TMap<FName, FDateTime> CompareRequests;` — Currently pending sync compare requests. Key is long package names.

#### Free symbols / members of external scopes

- L55 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnAvaAssetSyncStatusReceived, const FAvaPlaybackAssetSyncStatusReceivedParams&);` — Delegate called when an asset sync status changed.

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMedia/Private/Playback/Http/AvaPlaybackHttpServer.h` (Private)


#### class `FAvaPlaybackEmptyMessageContext`  
`class FAvaPlaybackEmptyMessageContext : public IMessageContext`  
_L25-55_
- inherits: `IMessageContext`
- desc: Required by Messaging API which this wraps, so a dummy context is required
- L29 _public prototype_ `FAvaPlaybackEmptyMessageContext() = default;`
- L30 _public prototype_ `virtual ~FAvaPlaybackEmptyMessageContext() override = default;`
- L34 _public function_ `virtual const TMap<FName, FString>& GetAnnotations() const override`
- L35 _public function_ `virtual TSharedPtr<IMessageAttachment, ESPMode::ThreadSafe> GetAttachment() const override`
- L36 _public function_ `virtual const FDateTime& GetExpiration() const override`
- L37 _public function_ `virtual const void* GetMessage() const override`
- L38 _public function_ `virtual const TWeakObjectPtr<UScriptStruct>& GetMessageTypeInfo() const override`
- L39 _public function_ `virtual TSharedPtr<IMessageContext, ESPMode::ThreadSafe> GetOriginalContext() const override`
- L40 _public function_ `virtual const TArray<FMessageAddress>& GetRecipients() const override`
- L41 _public function_ `virtual EMessageScope GetScope() const override`
- L42 _public function_ `virtual EMessageFlags GetFlags() const override`
- L43 _public function_ `virtual const FMessageAddress& GetSender() const override`
- L44 _public function_ `virtual const FMessageAddress& GetForwarder() const override`
- L45 _public function_ `virtual ENamedThreads::Type GetSenderThread() const override`
- L46 _public function_ `virtual const FDateTime& GetTimeForwarded() const override`
- L47 _public function_ `virtual const FDateTime& GetTimeSent() const override`
- L50 _private member_ `TMap<FName, FString> EmptyMap;`
- L51 _private member_ `FDateTime EmptyDate;`
- L52 _private member_ `TWeakObjectPtr<UScriptStruct> EmptyTypeInfo;`
- L53 _private member_ `TArray<FMessageAddress> EmptyRecipients;`
- L54 _private member_ `FMessageAddress EmptyAddress;`

#### struct `FAvaPlaybackHttpRouteInfo`  
`struct FAvaPlaybackHttpRouteInfo`  
_L58-83_
- reflection: `USTRUCT()`
- L62 _public member_ `FName RouteName;`
- L63 _public member_ `FHttpPath RoutePath;`
- L64 _public member_ `EHttpServerRequestVerbs RequestVerbs;`
- L65 _public member_ `FString InputContentType;`
- L66 _public member_ `FString InputExpectedFormat;`
- L67 _public function_ `FAvaPlaybackHttpRouteInfo()`
- L75 _public function_ `FAvaPlaybackHttpRouteInfo(FName InRouteName, FHttpPath InRoutePath, EHttpServerRequestVerbs InRequestVerbs, FString InContentType = TEXT(""), FString InExpectedFormat = TEXT(""))`

#### struct `FAvaPlaybackHttpRouteDesc`  
`struct FAvaPlaybackHttpRouteDesc`  
_L86-103_
- reflection: `USTRUCT()`
- L90 _public member_ `FHttpRouteHandle Handle;`
- L91 _public member_ `FString InputContentType;`
- L92 _public member_ `FString InputExpectedFormat;`
- L93 _public function_ `FAvaPlaybackHttpRouteDesc()`
- L97 _public function_ `FAvaPlaybackHttpRouteDesc(FHttpRouteHandle InHandle, FString InContentType, FString InExpectedFormat)`

#### struct `FAvaPlaybackHttpRouteBuilder`  
`struct FAvaPlaybackHttpRouteBuilder`  
_L109-128_
- L119 _public prototype_ `FAvaPlaybackHttpRouteBuilder(const TSharedPtr<FAvaPlaybackHttpServer>& InHttpServer, const TSharedPtr<FAvaPlaybackServer>& InPlaybackServer);`
- L123 _public prototype_ `template <typename MessageType> FAvaPlaybackHttpRouteBuilder& Route(const FString& InPath, const EHttpServerRequestVerbs& InVerb, typename TMessageHandler<MessageType, FAvaPlaybackServer>::FuncType InHandlerFunc);`
- L126 _private member_ `TSharedPtr<FAvaPlaybackHttpServer> HttpServer;`
- L127 _private member_ `TSharedPtr<FAvaPlaybackServer> PlaybackServer;`
- L204 _function_ `template <typename MessageType> FAvaPlaybackHttpRouteBuilder& FAvaPlaybackHttpRouteBuilder::Route( const FString& InPath, const EHttpServerRequestVerbs& InVerb, typename TMessageHandler<MessageType, FAvaPlaybackServer>::FuncType InHandlerFunc)`

#### struct `FAvaPlaybackHttpRouteBuilder::TMessageHandler`  
`template <typename MessageType, typename HandlerType> struct TMessageHandler`  
_L113-116_
- L115 _public typedef_ `typedef void (HandlerType::* FuncType)(const MessageType&, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>&);`

#### class `FAvaPlaybackHttpServer`  
`class FAvaPlaybackHttpServer : public TSharedFromThis<FAvaPlaybackHttpServer>`  
_L130-173_
- inherits: `TSharedFromThis<FAvaPlaybackHttpServer>`
- L133 _public typedef_ `using FBuilder = FAvaPlaybackHttpRouteBuilder;`
- L135 _public prototype_ `FAvaPlaybackHttpServer() = default;`
- L136 _public prototype_ `virtual ~FAvaPlaybackHttpServer() = default;`
- L138 _public prototype_ `void Start(const TSharedPtr<FAvaPlaybackServer>& InPlaybackServer, int32 InPortToUse = 10123);`
- L140 _public prototype_ `void RegisterRoutes(const TSharedPtr<FAvaPlaybackServer>& InPlaybackServer);`
- L145 _public prototype_ `bool GetRegisteredRoute(FName RouteName, FAvaPlaybackHttpRouteInfo& OutRouteInfo);` — Try to get a route registered under given friendly name. Returns false if could not be found.
- L147 _public prototype_ `void RegisterNewRoute(FAvaPlaybackHttpRouteInfo InRouteInfo, const FHttpRequestHandler& Handler, bool bOverrideIfBound = false);`
- L153 _public prototype_ `void RegisterNewRoute(FName RouteName, const FHttpPath& HttpPath, const EHttpServerRequestVerbs& RequestVerbs, const FHttpRequestHandler& Handler, bool bOverrideIfBound = false, FString OptionalContentType = TEXT(""), FString OptionalExpectedFormat = TEXT(""));` — Register a new route. Will override existing routes if option is set, otherwise will error and fail to bind.
- L159 _public prototype_ `void CleanUpRoute(FName RouteName, bool bFailIfUnbound = false);` — Clean up a route. Can be set to fail if trying to unbind an unbound route.
- L165 _public prototype_ `bool HttpListOpenRoutes(const FHttpServerRequest& Request, const FHttpResultCallback& OnComplete);` — Default Route Listing http call. Spits out all registered routes and describes them via a REST API call. Always registered at /listroutes GET by default
- L167 _public function_ `bool IsRunning() const`
- L170 _protected member_ `int PortToUse = 10123;`
- L171 _protected member_ `TSharedPtr<IHttpRouter> HttpRouter;`
- L172 _protected member_ `TMap<FName, FAvaPlaybackHttpRouteDesc> RegisteredRoutes;`

#### Free symbols / members of external scopes

- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace Ava` (scope `UE`)
- L18 _namespace_ `namespace Web` (scope `UE::Ava`)
- L18 _namespace_ `namespace Private` (scope `UE::Ava::Web`)
- L21 _prototype_ `template <typename MessageType> [[nodiscard]] bool DeserializeRequest(const FHttpServerRequest& InRequest, const FHttpResultCallback* InCompleteCallback, MessageType& OutDeserializedRequest);` (scope `UE::Ava::Web::Private`)
- L105 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogAvaPlaybackHttpServer, Log, All);`
- L105 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogAvaPlaybackHttpServer, Log, All);`
- L176 _function_ `template <typename MessageType> bool UE::Ava::Web::Private::DeserializeRequest( const FHttpServerRequest& InRequest, const FHttpResultCallback* InCompleteCallback, MessageType& OutDeserializedRequest)` (scope `UE::Ava::Web::Private`)
- L215 _function_ `` (scope `FAvaPlaybackHttpRouteBuilder::Route`)

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMedia/Private/Playback/Nodes/AvaPlaybackNodeCombiner.h` (Private)


#### class `UAvaPlaybackNodeCombiner`  
`class UAvaPlaybackNodeCombiner : public UAvaPlaybackNode`  
_L16-36_
- reflection: `UCLASS()`
- inherits: `UAvaPlaybackNode`
- L20 _private prototype_ `virtual FText GetNodeDisplayNameText() const override;`
- L22 _private function_ `virtual int32 GetMinChildNodes() const override`
- L23 _private function_ `virtual int32 GetMaxChildNodes() const override`
- L25 _private prototype_ `virtual void CreateStartingConnectors() override;`
- L27 _private prototype_ `virtual void Tick(float DeltaTime, FAvaPlaybackChannelParameters& ChannelParameters) override;`
- L30 _private prototype_ `virtual FName GetInputPinName(int32 InputPinIndex) const override;`
- L35 _protected member_ `TArray<bool> EnabledIndices;` — `UPROPERTY(EditAnywhere, Category = "Motion Design")`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMedia/Private/Playback/Nodes/AvaPlaybackNodeSwitcher.h` (Private)


#### class `UAvaPlaybackNodeSwitcher`  
`class UAvaPlaybackNodeSwitcher : public UAvaPlaybackNode`  
_L13-36_
- reflection: `UCLASS()`
- inherits: `UAvaPlaybackNode`
- L17 _private prototype_ `virtual FText GetNodeDisplayNameText() const override;`
- L19 _private function_ `virtual int32 GetMinChildNodes() const override`
- L20 _private function_ `virtual int32 GetMaxChildNodes() const override`
- L22 _private prototype_ `virtual void CreateStartingConnectors() override;`
- L24 _private prototype_ `virtual void Tick(float DeltaTime, FAvaPlaybackChannelParameters& ChannelParameters) override;`
- L27 _private prototype_ `virtual FName GetInputPinName(int32 InputPinIndex) const override;`
- L32 _protected member_ `bool bEnabled = true;` — `UPROPERTY(EditAnywhere, Category = "Motion Design")`
- L35 _protected member_ `int32 SelectedIndex = 0;` — `UPROPERTY(EditAnywhere, Category = "Motion Design", meta=(ClampMin = "0"))`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMedia/Private/Playback/Nodes/Events/Actions/AvaPlaybackNode_PlayAnim.h` (Private)


#### class `UAvaPlaybackNode_PlayAnim`  
`class UAvaPlaybackNode_PlayAnim : public UAvaPlaybackNodeAction`  
_L19-38_
- reflection: `UCLASS()`
- inherits: `UAvaPlaybackNodeAction`
- L24 _public prototype_ `virtual FText GetNodeDisplayNameText() const override;`
- L25 _public prototype_ `virtual FText GetNodeTooltipText() const override;`
- L26 _public prototype_ `virtual void OnEventTriggered(const FAvaPlaybackEventParameters& InEventParameters) override;`
- L28 _public prototype_ `virtual void PreDryRun() override;`
- L29 _public prototype_ `virtual void DryRun(const TArray<UAvaPlaybackNode*>& InAncestors) override;`
- L30 _public prototype_ `virtual void PostDryRun() override;`
- L34 _protected member_ `TMap<FSoftObjectPath, FAvaPlaybackAnimations> AnimationMap;` — `UPROPERTY(VisibleAnywhere, Category = "Motion Design")`
- L37 _protected member_ `TSet<FSoftObjectPath> SeenAssetsInDryRun;` — All the assets connected to this Node from the Dry Run (only populated while Dry Running!)

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMedia/Private/Playback/Nodes/Events/Actions/AvaPlaybackNode_PreloadPlayer.h` (Private)


#### class `UAvaPlaybackNode_PreloadPlayer`  
`class UAvaPlaybackNode_PreloadPlayer : public UAvaPlaybackNodeAction`  
_L12-20_
- reflection: `UCLASS()`
- inherits: `UAvaPlaybackNodeAction`
- L17 _public prototype_ `virtual FText GetNodeDisplayNameText() const override;`
- L18 _public prototype_ `virtual FText GetNodeTooltipText() const override;`
- L19 _public prototype_ `virtual void OnEventTriggered(const FAvaPlaybackEventParameters& InEventParameters) override;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMedia/Private/Playback/Nodes/Events/FlowControl/AvaPlaybackNode_Hub.h` (Private)


#### class `UAvaPlaybackNode_Hub`  
`class UAvaPlaybackNode_Hub : public UAvaPlaybackNodeFlow`  
_L12-22_
- reflection: `UCLASS()`
- inherits: `UAvaPlaybackNodeFlow`
- L17 _public prototype_ `virtual FText GetNodeDisplayNameText() const override;`
- L18 _public prototype_ `virtual FText GetNodeTooltipText() const override;`
- L19 _public function_ `virtual int32 GetMaxChildNodes() const override`
- L21 _public prototype_ `virtual void TickEvent(float DeltaTime, FAvaPlaybackEventParameters& OutEventParameters) override;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMedia/Private/Playback/Nodes/Events/Triggers/AvaPlaybackNode_BeginPlay.h` (Private)


#### class `UAvaPlaybackNode_BeginPlay`  
`class UAvaPlaybackNode_BeginPlay : public UAvaPlaybackNodeTrigger`  
_L11-19_
- reflection: `UCLASS()`
- inherits: `UAvaPlaybackNodeTrigger`
- L16 _public prototype_ `virtual FText GetNodeDisplayNameText() const override;`
- L17 _public prototype_ `virtual FText GetNodeTooltipText() const override;`
- L18 _public prototype_ `virtual void NotifyPlaybackStateChanged(bool bPlaying) override;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMedia/Private/Playback/Nodes/Events/Triggers/AvaPlaybackNode_KeyInput.h` (Private)


#### class `UAvaPlaybackNode_KeyInput`  
`class UAvaPlaybackNode_KeyInput : public UAvaPlaybackNodeTrigger`  
_L17-46_
- reflection: `UCLASS()`
- inherits: `UAvaPlaybackNodeTrigger`
- L33 _public prototype_ `virtual void PostAllocateNode() override;`
- L34 _public prototype_ `virtual void BeginDestroy() override;`
- L36 _public prototype_ `virtual FText GetNodeDisplayNameText() const override;`
- L37 _public prototype_ `virtual FText GetNodeTooltipText() const override;`
- L39 _public prototype_ `bool HandleKeyDownEvent(FSlateApplication& SlateApp, const FKeyEvent& InKeyEvent);`
- L42 _protected member_ `TSharedPtr<UAvaPlaybackNode_KeyInput::FEventInputProcessor> InputProcessor;`
- L45 _protected member_ `FInputChord InputChord;` — `UPROPERTY(EditAnywhere, Category = "Motion Design", meta = (ShowOnlyInnerProperties))`

#### class `UAvaPlaybackNode_KeyInput::FEventInputProcessor`  
`class FEventInputProcessor: public IInputProcessor`  
_L21-30_
- inherits: `IInputProcessor`
- L24 _public function_ `FEventInputProcessor(UAvaPlaybackNode_KeyInput* InNode) : Node(InNode)`
- L25 _public function_ `virtual void Tick(const float DeltaTime, FSlateApplication& SlateApp, TSharedRef<ICursor> Cursor) override`
- L26 _public prototype_ `virtual bool HandleKeyDownEvent(FSlateApplication& SlateApp, const FKeyEvent& InKeyEvent) override;`
- L29 _protected member_ `UAvaPlaybackNode_KeyInput* Node = nullptr;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMedia/Private/Playback/Transition/AvaPlaybackServerTransition.h` (Private)


#### class `UAvaPlaybackServerTransition`  
`class UAvaPlaybackServerTransition : public UAvaPlaybackTransition`  
_L29-122_
- reflection: `UCLASS()`
- inherits: `UAvaPlaybackTransition`
- desc: Class for creating and tracking playback graph instance transitions on the server. It is responsible for creating the playable transition object when requested from the playback graphs. This class handles each playback graph instance as a single playable. It is meant to be used by the playback server primarily.
- L34 _public prototype_ `static UAvaPlaybackServerTransition* MakeNew(const TSharedPtr<FAvaPlaybackServer>& InPlaybackServer);`
- L36 _public function_ `void SetChannelName(const FName& InChannelName)`
- L37 _public function_ `void SetTransitionId(const FGuid& InTransitionId)`
- L38 _public function_ `void SetClientName(const FString& InClientName)`
- L39 _public function_ `void SetUnloadDiscardedInstances(bool bInUnloadDiscardedInstances)`
- L40 _public function_ `void SetTransitionFlags(EAvaPlayableTransitionFlags InTransitionFlags)`
- L41 _public prototype_ `void AddPendingEnterInstanceIds(const TArray<FGuid>& InInstanceIds);`
- L42 _public prototype_ `void AddPendingPlayingInstanceId(const FGuid& InInstanceId);`
- L43 _public prototype_ `void AddPendingExitInstanceId(const FGuid& InInstanceId);`
- L44 _public prototype_ `void SetEnterValues(const TArray<FAvaPlayableRemoteControlValues>& InEnterValues);`
- L45 _public prototype_ `bool AddEnterInstance(const TSharedPtr<FAvaPlaybackInstance>& InPlaybackInstance);`
- L46 _public prototype_ `bool AddPlayingInstance(const TSharedPtr<FAvaPlaybackInstance>& InPlaybackInstance);`
- L47 _public prototype_ `bool AddExitInstance(const TSharedPtr<FAvaPlaybackInstance>& InPlaybackInstance);`
- L49 _public prototype_ `void TryResolveInstances(const FAvaPlaybackServer& InPlaybackServer);`
- L51 _public prototype_ `bool ContainsInstance(const FGuid& InInstanceId) const;`
- L54 _public prototype_ `virtual bool IsVisibilityConstrained(const UAvaPlayable* InPlayable) const override;`
- L58 _public prototype_ `virtual bool CanStart(bool& bOutShouldDiscard) override;`
- L59 _public prototype_ `virtual void Start() override;`
- L60 _public prototype_ `virtual void Stop() override;`
- L61 _public prototype_ `virtual bool IsRunning() const override;`
- L65 _public function_ `FName GetChannelName() const` — Returns the channel this transition is happening in. A transition can only have instances within the same channel.
- L67 _public prototype_ `FString GetPrettyTransitionInfo() const;`
- L68 _public prototype_ `FString GetBriefTransitionDescription() const;`
- L72 _protected prototype_ `void Start_Synchronized();` — Implementation of the Start function intended to be synchronized on cluster.
- L74 _protected prototype_ `TSharedPtr<FAvaPlaybackInstance> FindInstanceForPlayable(const UAvaPlayable* InPlayable);`
- L76 _protected prototype_ `void OnTransitionEvent(UAvaPlayable* InPlayable, UAvaPlayableTransition* InTransition, EAvaPlayableTransitionEventFlags InTransitionFlags);`
- L77 _protected prototype_ `void OnPlayableCreated(UAvaPlaybackGraph* InPlayback, UAvaPlayable* InPlayable);`
- L79 _protected prototype_ `void MakePlayableTransition();`
- L81 _protected prototype_ `void LogDetailedTransitionInfo() const;`
- L83 _protected prototype_ `void RegisterToPlayableTransitionEvent();`
- L84 _protected prototype_ `void UnregisterFromPlayableTransitionEvent() const;`
- L86 _protected prototype_ `bool AddPlaybackInstance(const TSharedPtr<FAvaPlaybackInstance>& InPlaybackInstance, TArray<TWeakPtr<FAvaPlaybackInstance>>& OutPlaybackInstancesWeak);`
- L87 _protected prototype_ `void UpdateChannelName(const FAvaPlaybackInstance* InPlaybackInstance);`
- L89 _protected prototype_ `void SendFinishTransitionEvent(FAvaPlaybackServer& InPlaybackServer, EAvaPlayableTransitionEventFlags InTransitionFlags);`
- L92 _protected member_ `TWeakPtr<FAvaPlaybackServer> PlaybackServerWeak;`
- L94 _protected member_ `FString ClientName;`
- L95 _protected member_ `FName ChannelName;`
- L96 _protected member_ `bool bUnloadDiscardedInstances = false;`
- L97 _protected member_ `EAvaPlayableTransitionFlags TransitionFlags = EAvaPlayableTransitionFlags::None;`
- L100 _protected member_ `TArray<FGuid> PendingEnterInstanceIds;` — Instance Ids pending resolve.
- L101 _protected member_ `TArray<FGuid> PendingPlayingInstanceIds;`
- L102 _protected member_ `TArray<FGuid> PendingExitInstanceIds;`
- L104 _protected member_ `TArray<TWeakPtr<FAvaPlaybackInstance>> EnterPlaybackInstancesWeak;`
- L105 _protected member_ `TArray<TWeakPtr<FAvaPlaybackInstance>> PlayingPlaybackInstancesWeak;`
- L106 _protected member_ `TArray<TWeakPtr<FAvaPlaybackInstance>> ExitPlaybackInstancesWeak;`
- L107 _protected member_ `TArray<TSharedPtr<FAvaPlayableRemoteControlValues>> EnterValues;`
- L109 _protected member_ `TSharedPtr<UE::AvaPlayback::Utils::FAsyncAssetLoader> AsyncAssetLoader;`
- L112 _protected member_ `TObjectPtr<UAvaPlayableTransition> PlayableTransition;` — `UPROPERTY(Transient)`
- L115 _protected member_ `TArray<FAvaPlaybackTransitionEventEntry> InstanceEventEntries;` — Keep track of all instance event entries so we can all send them in a single message to ensure order.
- L118 _protected member_ `bool bIsStopping = false;` — Re-entry guard for stop() function.
- L121 _protected member_ `bool bIsFinishedSent = false;` — Indicate if the "finish" event has been sent. There is 2 possible paths to send the finish event, but we only want to send once.

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace AvaPlayback` (scope `UE`)
- L15 _namespace_ `namespace Utils` (scope `UE::AvaPlayback`)

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMedia/Private/Playback/Transition/AvaPlaybackTransition.h` (Private)


#### class `UAvaPlaybackTransition`  
`class UAvaPlaybackTransition : public UObject, public IAvaPlayableVisibilityConstraint`  
_L14-47_
- reflection: `UCLASS()`
- inherits: `UObject,IAvaPlayableVisibilityConstraint`
- desc: Abstract base class for playback transitions that can be queued in the playback manager's commands.
- L24 _public function_ `virtual bool CanStart(bool& bOutShouldDiscard)` — @brief Evaluate the status of loading playables to determine if the transition can start. @param bOutShouldDiscard indicate if the pending start transition command should be discarded. @return true if the transition can start, false otherwise.
- L30 _public function_ `virtual void Start()` — Start the transition. @remark Transition start is synchronized on clusters, but it is implemented by the derived classes.
- L33 _public function_ `virtual void Stop()` — Stop transition
- L36 _public function_ `virtual bool IsRunning() const` — Returns true if the transition is running, false otherwise.
- L39 _public function_ `virtual bool IsVisibilityConstrained(const UAvaPlayable* InPlayable) const override`
- L43 _public function_ `const FGuid& GetTransitionId() const` — Returns the TransitionId, a unique identifier (replicated on server) for this transition.
- L46 _protected member_ `FGuid TransitionId;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMedia/Private/Rundown/AvaRundownComponent.h` (Private)


#### class `UAvaRundownComponent`  
`class UAvaRundownComponent : public UActorComponent`  
_L16-43_
- reflection: `UCLASS(BlueprintType, Blueprintable, ClassGroup = "Motion Design Rundown", meta = (DisplayName = "Motion Design Rundown Component", BlueprintSpawnableComponent))`
- inherits: `UActorComponent`
- desc: Add this actor component to blueprint actor to expose the API to control an Motion Design Rundown in game.
- L21 _public prototype_ `UAvaRundownComponent(const FObjectInitializer& ObjectInitializer);`
- L24 _public member_ `TObjectPtr<UAvaRundown> Rundown = nullptr;` — `UPROPERTY(EditAnywhere, Category = "Motion Design Media", meta = (DisplayName = "Motion Design Rundown"))`
- L27 _public prototype_ `bool PlayPage(int32 InPageId);` — `UFUNCTION(BlueprintCallable, Category = "Motion Design Media")`
- L30 _public prototype_ `bool StopPage(int32 InPageId);` — `UFUNCTION(BlueprintCallable, Category = "Motion Design Media")`
- L33 _public prototype_ `int32 GetNumberOfPages() const;` — `UFUNCTION(BlueprintCallable, Category = "Motion Design Media")`
- L36 _public prototype_ `int32 GetPageIdForIndex(int32 InPageIndex) const;` — `UFUNCTION(BlueprintCallable, Category = "Motion Design Media")`
- L38 _public prototype_ `virtual void InitializeComponent() override;`
- L39 _public prototype_ `virtual void UninitializeComponent() override;`
- L42 _protected prototype_ `void OnWorldBeginTearDown(UWorld* InWorld);`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMedia/Private/Rundown/AvaRundownManagedInstanceLevel.h` (Private)


#### class `FAvaRundownManagedInstanceLevel`  
`class FAvaRundownManagedInstanceLevel : public FAvaRundownManagedInstance`  
_L12-42_
- inherits: `FAvaRundownManagedInstance`
- L15 _public prototype_ `UE_AVA_INHERITS(FAvaRundownManagedInstanceLevel, FAvaRundownManagedInstance);`
- L17 _public prototype_ `FAvaRundownManagedInstanceLevel(FAvaRundownManagedInstanceCache* InParentCache, const FSoftObjectPath& InAssetPath);`
- L21 _public prototype_ `virtual void AddReferencedObjects( FReferenceCollector& Collector ) override;`
- L22 _public prototype_ `virtual FString GetReferencerName() const override;`
- L26 _public function_ `virtual bool IsValid() const override`
- L27 _public function_ `virtual URemoteControlPreset* GetRemoteControlPreset() const override`
- L28 _public prototype_ `virtual IAvaSceneInterface* GetSceneInterface() const override;`
- L32 _private prototype_ `void DiscardSourceLevel();`
- L33 _private prototype_ `void OnMapChangedEvent(UWorld* InWorld, EAvaMediaMapChangeType InEventType);`
- L37 _private member_ `TWeakObjectPtr<UWorld> SourceLevelWeak;` — Keep a weak pointer to the loaded source level. This is used to unregister delegates if needed.
- L39 _private member_ `TObjectPtr<UWorld> ManagedLevel;`
- L40 _private member_ `TObjectPtr<UPackage> ManagedLevelPackage;`
- L41 _private member_ `TObjectPtr<URemoteControlPreset> ManagedRemoteControlPreset;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMedia/Private/Rundown/AvaRundownManagedInstanceUtils.h` (Private)


#### class `FAvaRundownManagedInstanceUtils`  
`class FAvaRundownManagedInstanceUtils`  
_L12-17_
- desc: Common utility functions for implementing Managed Instance.
- L15 _public prototype_ `static UPackage* MakeManagedInstancePackage(const FSoftObjectPath& InAssetPath);`
- L16 _public prototype_ `static void PreventWorldFromBeingSeenAsLeakingByLevelEditor(UWorld* InWorld);`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMedia/Private/Rundown/AvaRundownPageAssetUtils.h` (Private)


#### class `FAvaRundownPageAssetUtils`  
`class FAvaRundownPageAssetUtils`  
_L20-25_
- desc: Common utility functions to query information about loaded Motion Design assets. This is intended to work on "inactive" assets, i.e. either source assets directly or managed ones that don't have an active world. For "runtime" (fully initialized) instances, UAvaPlayable should be used instead.
- L23 _public prototype_ `static const IAvaSceneInterface* GetSceneInterface(const UObject* InLoadedAsset);`
- L24 _public prototype_ `static const IAvaTransitionBehavior* FindTransitionBehavior(const IAvaSceneInterface* InSceneInterface);`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMedia/Private/Rundown/AvaRundownPageLoadingManager.h` (Private)


#### class `FAvaRundownPageLoadingManager`  
`class FAvaRundownPageLoadingManager final : public IAvaRundownPageLoadingManager`  
_L18-79_
- inherits: `IAvaRundownPageLoadingManager`
- desc: Manager for page loading requests. The main problem this class is solving right now is the throttling of page loading. We don't want to start loading all the pages at the same time because it leads to main thread bottleneck both when the requests are made and when the levels are loaded. To alleviate that we make the operations more granular by loading a subset of levels at any given time.
- L21 _public prototype_ `explicit FAvaRundownPageLoadingManager(UAvaRundown* InRundown);`
- L25 _public prototype_ `virtual bool RequestLoadPage(int32 InPageId, bool bInIsPreview, const FName& InPreviewChannelName) override;`
- L29 _private prototype_ `bool RequestLoadPageInternal(const FAvaRundownPage& InPage, bool bInIsPreview, const FName& InPreviewChannelName);`
- L31 _private prototype_ `void HandlePlaybackInstanceStatusChanged(const FAvaPlaybackInstance& InPlaybackInstance);`
- L32 _private prototype_ `void HandlePlaybackManagerBeginTick(float InDeltaSeconds);`
- L35 _private prototype_ `TSharedPtr<FAvaPlaybackInstance> FindInstance(const FInstanceInfo& InInstanceInfo) const;`
- L38 _private member_ `UAvaRundown* Rundown = nullptr;`
- L39 _private member_ `TWeakPtr<FAvaPlaybackManager> PlaybackManagerWeak;`
- L52 _private function_ `FORCEINLINE friend uint32 GetTypeHash(FPageLoadRequest const& This)`
- L62 _private member_ `TQueue<FPageLoadRequest> PendingRequestQueue;` — Ordered queue. Requests are executed in order.
- L64 _private member_ `TSet<FPageLoadRequest> PendingRequestSet;` — Unordered set to ensure uniqueness of requests.
- L75 _private member_ `TArray<FInstanceInfo> LoadingInstances;`
- L78 _private member_ `int32 MaxLoadingInstances = 1;` — Maximum concurrent instance to load.

#### struct `FAvaRundownPageLoadingManager::FPageLoadRequest`  
`struct FPageLoadRequest`  
_L41-60_
- L43 _public member_ `int32 PageId;`
- L44 _public member_ `bool bIsPreview;`
- L45 _public member_ `FName PreviewChannelName;`
- L47 _public function_ `bool operator==(FPageLoadRequest const& Other) const`

#### struct `FAvaRundownPageLoadingManager::FInstanceInfo`  
`struct FInstanceInfo`  
_L67-74_
- desc: Instances currently loading.
- L69 _public member_ `FGuid InstanceId;`
- L70 _public member_ `FSoftObjectPath AssetPath;`
- L71 _public member_ `FString ChannelName;`
- L72 _public member_ `EAvaPlaybackStatus Status = EAvaPlaybackStatus::Unknown;`
- L73 _public member_ `FDateTime SubmitTime;` — Time stamp when the load request was submitted.

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMedia/Private/Rundown/AvaRundownPlaybackClientWatcher.h` (Private)


#### class `FAvaRundownPlaybackClientWatcher`  
`class FAvaRundownPlaybackClientWatcher`  
_L18-43_
- desc: Playback Client Watcher ensures external playback events are reconciled. Cases covered: 1 - if a remote playable is stopped (server reset), the corresponding page in the rundown will be stopped 2 - if a remote playable is playing (server side), the corresponding page's state will be restored, i.e. rebuilding the proxies. to be continued...
- L21 _public prototype_ `FAvaRundownPlaybackClientWatcher(UAvaRundown* InRundown);`
- L22 _public prototype_ `~FAvaRundownPlaybackClientWatcher();`
- L24 _public prototype_ `void TryRestorePlaySubPage(int InPageId, const UE::AvaPlaybackClient::Delegates::FPlaybackStatusChangedArgs& InEventArgs) const;`
- L26 _public function_ `static bool IsAnyOf(EAvaPlaybackStatus InStatus, const TArray<EAvaPlaybackStatus>& InStatuses)`
- L38 _public prototype_ `void HandlePlaybackStatusChanged(IAvaPlaybackClient& InPlaybackClient, const UE::AvaPlaybackClient::Delegates::FPlaybackStatusChangedArgs& InEventArgs);`
- L42 _private member_ `UAvaRundown* Rundown;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMedia/Private/Rundown/AvaRundownServer.h` (Private)


#### class `FAvaRundownServer`  
`class FAvaRundownServer : public TSharedFromThis<FAvaRundownServer>, public FGCObject, public IAvaRundownServer`  
_L24-371_
- inherits: `TSharedFromThis<FAvaRundownServer>,FGCObject,IAvaRundownServer`
- desc: Implements a rundown server that listens to commands on message bus. The intention is to run a web socket transport bridge so the messages can come from external applications.
- L27 _public prototype_ `FAvaRundownServer();`
- L31 _public function_ `virtual const FString& GetName() const override`
- L32 _public prototype_ `virtual const FMessageAddress& GetMessageAddress() const override;`
- L33 _public function_ `virtual TArray<FMessageAddress> GetClientAddresses() const override`
- L37 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& InCollector) override;`
- L38 _public prototype_ `virtual FString GetReferencerName() const override;`
- L41 _public prototype_ `void Init(const FString& InAssignedHostName);`
- L43 _public prototype_ `void SetupPlaybackDelegates();`
- L44 _public prototype_ `void SetupBroadcastDelegates(UAvaBroadcast* InBroadcast);`
- L45 _public prototype_ `void SetupEditorDelegates();`
- L46 _public prototype_ `void RemovePlaybackDelegates() const;`
- L47 _public prototype_ `void RemoveBroadcastDelegates(UAvaBroadcast* InBroadcast) const;`
- L48 _public prototype_ `void RemoveEditorDelegates() const;`
- L50 _public prototype_ `void OnPagesChanged(const UAvaRundown* InRundown, const FAvaRundownPage& InPage, EAvaRundownPageChanges InChange) const;`
- L51 _public prototype_ `void OnPageListChanged(const FAvaRundownPageListChangeParams& InParams) const;`
- L52 _public prototype_ `void PageBlueprintChanged(const UAvaRundown* InRundown, const FAvaRundownPage& InPage, const FString& InBlueprintPath) const;`
- L53 _public prototype_ `void PageStatusChanged(const UAvaRundown* InRundown, const FAvaRundownPage& InPage) const;`
- L54 _public prototype_ `void PageChannelChanged(const UAvaRundown* InRundown, const FAvaRundownPage& InPage, const FString& InChannelName) const;`
- L55 _public prototype_ `void PageNameChanged(const UAvaRundown* InRundown, const FAvaRundownPage& InPage, bool bInFriendlyName) const;`
- L56 _public prototype_ `void PageAnimSettingsChanged(const UAvaRundown* InRundown, const FAvaRundownPage& InPage) const;`
- L57 _public prototype_ `void OnBroadcastChannelListChanged(const FAvaBroadcastProfile& InProfile) const;`
- L58 _public prototype_ `void OnBroadcastChannelChanged(const FAvaBroadcastOutputChannel& InChannel, EAvaBroadcastChannelChange InChange) const;`
- L59 _public prototype_ `void OnAssetAdded(const FAssetData& InAssetData) const;`
- L60 _public prototype_ `void OnAssetRemoved(const FAssetData& InAssetData) const;`
- L61 _public prototype_ `void OnAssetsPreDelete(const TArray<UObject*>& InObjects);`
- L62 _public prototype_ `void OnPlaybackInstanceStatusChanged(const FAvaPlaybackInstance& InPlaybackInstance);`
- L63 _public prototype_ `void OnPlayableSequenceEvent(UAvaPlayable* InPlayable, FName InSequenceLabel, EAvaPlayableSequenceEventType InSequenceEvent);`
- L64 _public prototype_ `void OnPlayableTransitionEvent(UAvaPlayable* InPlayable, UAvaPlayableTransition* InPlayableTransition, EAvaPlayableTransitionEventFlags InTransitionFlags);`
- L65 _public prototype_ `void OnPageTransitionRemoved(UAvaRundown* InRundown, UAvaRundownPageTransition* InPageTransition);`
- L66 _public prototype_ `void OnCanClosePlaybackContext(const UAvaRundown* InRundown, bool& bOutResult) const;`
- L69 _public prototype_ `void HandleRundownPing(const FAvaRundownPing& InMessage, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& InContext);` — Rundown message handlers
- L70 _public prototype_ `void HandleGetRundownServerInfo(const FAvaRundownGetServerInfo& InMessage, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& InContext);`
- L71 _public prototype_ `void HandleGetPlayableAssets(const FAvaRundownGetPlayableAssets& InMessage, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& InContext);`
- L72 _public prototype_ `void HandleGetRundowns(const FAvaRundownGetRundowns& InMessage, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& InContext);`
- L73 _public prototype_ `void HandleLoadRundown(const FAvaRundownLoadRundown& InMessage, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& InContext);`
- L74 _public prototype_ `void HandleCreateRundown(const FAvaRundownCreateRundown& InMessage, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& InContext);`
- L75 _public prototype_ `void HandleDeleteRundown(const FAvaRundownDeleteRundown& InMessage, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& InContext);`
- L76 _public prototype_ `void HandleImportRundown(const FAvaRundownImportRundown& InMessage, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& InContext);`
- L77 _public prototype_ `void HandleExportRundown(const FAvaRundownExportRundown& InMessage, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& InContext);`
- L78 _public prototype_ `void HandleSaveRundown(const FAvaRundownSaveRundown& InMessage, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& InContext);`
- L79 _public prototype_ `void HandleGetPages(const FAvaRundownGetPages& InMessage, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& InContext);`
- L80 _public prototype_ `void HandleCreatePage(const FAvaRundownCreatePage& InMessage,const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& InContext);`
- L81 _public prototype_ `void HandleCreateTemplate(const FAvaRundownCreateTemplate& InMessage, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& InContext);`
- L82 _public prototype_ `void HandleCreateComboTemplate(const FAvaRundownCreateComboTemplate& InMessage, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& InContext);`
- L83 _public prototype_ `void HandleDeletePage(const FAvaRundownDeletePage& InMessage,const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& InContext);`
- L84 _public prototype_ `void HandleDeleteTemplate(const FAvaRundownDeleteTemplate& InMessage,const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& InContext);`
- L85 _public prototype_ `void HandleChangeTemplateBP(const FAvaRundownChangeTemplateBP& InMessage, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& InContext);`
- L86 _public prototype_ `void HandleGetPageDetails(const FAvaRundownGetPageDetails& InMessage, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& InContext);`
- L87 _public prototype_ `void HandleChangePageChannel(const FAvaRundownPageChangeChannel& InMessage, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& InContext);`
- L88 _public prototype_ `void HandleChangePageName(const FAvaRundownChangePageName& InMessage, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& InContext);`
- L89 _public prototype_ `void HandleUpdatePageFromRCP(const FAvaRundownUpdatePageFromRCP& InMessage, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& InContext);`
- L90 _public prototype_ `void HandlePageAction(const FAvaRundownPageAction& InMessage, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& InContext);`
- L91 _public prototype_ `void HandlePagePreviewAction(const FAvaRundownPagePreviewAction& InMessage, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& InContext);`
- L92 _public prototype_ `void HandlePageActions(const FAvaRundownPageActions& InMessage, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& InContext);`
- L93 _public prototype_ `void HandlePagePreviewActions(const FAvaRundownPagePreviewActions& InMessage, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& InContext);`
- L94 _public prototype_ `void HandleTransitionAction(const FAvaRundownTransitionAction& InMessage, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& InContext);`
- L95 _public prototype_ `void HandleTransitionLayerAction(const FAvaRundownTransitionLayerAction& InMessage, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& InContext);`
- L98 _public prototype_ `void HandleGetProfiles(const FAvaRundownGetProfiles& InMessage, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& InContext);` — Broadcast message handlers
- L99 _public prototype_ `void HandleCreateProfile(const FAvaRundownCreateProfile& InMessage, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& InContext);`
- L100 _public prototype_ `void HandleDuplicateProfile(const FAvaRundownDuplicateProfile& InMessage, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& InContext);`
- L101 _public prototype_ `void HandleRenameProfile(const FAvaRundownRenameProfile& InMessage, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& InContext);`
- L102 _public prototype_ `void HandleDeleteProfile(const FAvaRundownDeleteProfile& InMessage, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& InContext);`
- L103 _public prototype_ `void HandleSetCurrentProfile(const FAvaRundownSetCurrentProfile& InMessage, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& InContext);`
- L104 _public prototype_ `void HandleGetChannel(const FAvaRundownGetChannel& InMessage, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& InContext);`
- L105 _public prototype_ `void HandleGetChannels(const FAvaRundownGetChannels& InMessage, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& InContext);`
- L106 _public prototype_ `void HandleChannelAction(const FAvaRundownChannelAction& InMessage, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& InContext);`
- L107 _public prototype_ `void HandleChannelEditAction(const FAvaRundownChannelEditAction& InMessage, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& InContext);`
- L108 _public prototype_ `void HandleRenameChannel(const FAvaRundownRenameChannel& InMessage, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& InContext);`
- L109 _public prototype_ `void HandleAddChannelDevice(const FAvaRundownAddChannelDevice& InMessage, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& InContext);`
- L110 _public prototype_ `void HandleEditChannelDevice(const FAvaRundownEditChannelDevice& InMessage, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& InContext);`
- L111 _public prototype_ `void HandleRemoveChannelDevice(const FAvaRundownRemoveChannelDevice& InMessage, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& InContext);`
- L112 _public prototype_ `void HandleGetChannelImage(const FAvaRundownGetChannelImage& InMessage, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& InContext);`
- L113 _public prototype_ `void HandleGetChannelQualitySettings(const FAvaRundownGetChannelQualitySettings& InMessage, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& InContext);`
- L114 _public prototype_ `void HandleSetChannelQualitySettings(const FAvaRundownSetChannelQualitySettings& InMessage, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& InContext);`
- L115 _public prototype_ `void HandleSaveBroadcast(const FAvaRundownSaveBroadcast& InMessage, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& InContext);`
- L117 _public prototype_ `void HandleGetDevices(const FAvaRundownGetDevices& InMessage, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& InContext);`
- L119 _public prototype_ `void LogAndSendMessage(const FMessageAddress& InSender, int32 InRequestId, ELogVerbosity::Type InVerbosity, const TCHAR* InFormat, ...) const;`
- L120 _public prototype_ `void SendMessage(const FMessageAddress& InSender, int32 InRequestId, ELogVerbosity::Type InVerbosity, const TCHAR* InFormat, ...) const;`
- L121 _public prototype_ `void SendMessageImpl(const FMessageAddress& InSender, int32 InRequestId, ELogVerbosity::Type InVerbosity, const TCHAR* InMsg) const;`
- L123 _public prototype_ `void RegisterConsoleCommands();`
- L125 _public prototype_ `void ShowStatusCommand(const TArray<FString>& InArgs);`
- L128 _public prototype_ `void NotifyPlaybackContextSwitch(const FSoftObjectPath& InPreviousRundownPath, const FSoftObjectPath& InNewRundownPath) const;` — Broadcast a rundown playback context switch to all connected clients.
- L130 _public prototype_ `void NotifyAssetEvent(const FAssetData& InAssetData, const EAvaRundownAssetEvent InEventType) const;`
- L140 _protected prototype_ `void FinishGetChannelImage(const FRequestInfo& InRequestInfo, const TSharedPtr<FChannelImage>& InChannelImage);`
- L142 _protected prototype_ `void HandlePageActions(const FRequestInfo& InRequestInfo, const TArray<int32>& InPageIds, bool bInIsPreview, FName InPreviewChannelName, EAvaRundownPageActions InAction) const;`
- L145 _protected prototype_ `UAvaRundownPagePlayer* FindPagePlayerForInstance(const FAvaPlaybackInstance& InPlaybackInstance) const;`
- L150 _protected prototype_ `UAvaRundown* GetOrLoadRundownForEdit(const FMessageAddress& InSender, int32 InRequestId, const FString& InRundownPath);` — Helper function to retrieve the appropriate rundown for editing commands.
- L153 _protected function_ `template<typename MessageType> void SendResponse(MessageType* InMessage, const FMessageAddress& InRecipient, EMessageFlags InFlags = EMessageFlags::None) const`
- L162 _protected function_ `template<typename MessageType> void SendResponse(MessageType* InMessage, const TArray<FMessageAddress>& InRecipients, EMessageFlags InFlags = EMessageFlags::None) const`
- L171 _protected prototype_ `void OnMessageBusNotification(const FMessageBusNotification& InNotification);`
- L174 _private member_ `FString HostName;`
- L175 _private member_ `TSharedPtr<FMessageEndpoint, ESPMode::ThreadSafe> MessageEndpoint;`
- L176 _private member_ `TArray<IConsoleObject*> ConsoleCommands;`
- L189 _private member_ `TMap<FMessageAddress, TSharedPtr<FClientInfo>> Clients;` — Keep track of remote clients context information.
- L192 _private member_ `TArray<FMessageAddress> ClientAddresses;` — Array of just the client addresses for sending responses.
- L194 _private function_ `FClientInfo* GetClientInfo(const FMessageAddress& InAddress) const`
- L200 _private function_ `FClientInfo& GetOrAddClientInfo(const FMessageAddress& InAddress)`
- L213 _private prototype_ `void RefreshClientAddresses();`
- L216 _private member_ `TArray<TSharedPtr<FChannelImage>> AvailableChannelImages;` — Pool of images that can be recycled.
- L247 _private member_ `TMap<FSoftObjectPath, TWeakPtr<FRundownEntry>> LoadedRundownCache;` — Cache of loaded rundowns currently referenced by the command contexts. There is one entry per loaded asset (shared by command contexts). Key is the rundown's asset path.
- L250 _private prototype_ `void CompactLoadedRundownCache();` — Remove stale rundown entries.
- L257 _private prototype_ `TSharedPtr<FRundownEntry> GetOrLoadRundown(const FSoftObjectPath& InRundownPath);` — Returns requested rundown specified by InRundownPath. Will load it if necessary or return the cached one. If the new rundown fails to load, the returned value is nullptr.
- L322 _private prototype_ `UAvaRundown* GetOrLoadRundownForContext(const FSoftObjectPath& InRundownPath, FCommandContext& InContext);` — Returns requested rundown specified by InRundownPath. Will load it if necessary or returned the cached one if it is the same. If the new rundown fails to load, the return value is nullptr, and the previous rundown will remain loaded. Only one rundown entry can be loaded per context (for now). @param InRundownPath	Requested rundown path. @param InContext Command context (either edit or playback).
- L349 _private member_ `FEditCommandContext EditCommandContext;` — TODO: it is likely we will need an edit command context per client connection (i.e. move to FClientInfo).
- L367 _private member_ `FPlaybackCommandContext PlaybackCommandContext;` — TODO: Will likely need to split playback context between preview (per client) and program (per rundown).
- L370 _private member_ `TMap<FSoftObjectPath, TObjectPtr<UAvaRundown>> ManagedRundowns;` — Keep a map of created transient rundowns.

#### struct `FAvaRundownServer::FRequestInfo`  
`struct FRequestInfo`  
_L133-137_
- L135 _public member_ `int32 RequestId;`
- L136 _public member_ `FMessageAddress Sender;`

#### struct `FAvaRundownServer::FClientInfo`  
`struct FClientInfo`  
_L179-186_
- desc: Keep information on connected clients.
- L181 _public member_ `FMessageAddress Address;`
- L183 _public member_ `int32 ApiVersion = -1;` — Api version for communication with this client.
- L185 _public function_ `explicit FClientInfo(const FMessageAddress& InAddress) : Address(InAddress)`

#### class `FAvaRundownServer::FRundownEntry`  
`class FRundownEntry`  
_L221-240_
- desc: Manages rundown delegates binding with the rundown server handlers.
- L224 _public prototype_ `FRundownEntry(const TSharedPtr<FAvaRundownServer>& InRundownServer, const FSoftObjectPath& InRundownPath);`
- L225 _public prototype_ `~FRundownEntry();`
- L227 _public function_ `bool IsValid() const`
- L228 _public function_ `UAvaRundown* GetRundown() const`
- L230 _public function_ `void AddReferencedObjects(FReferenceCollector& InCollector)`
- L236 _private member_ `TObjectPtr<UAvaRundown> Rundown;`
- L239 _private member_ `FAvaRundownServer* RundownServerRaw = nullptr;` — Keep a raw ptr for unregistering delegates only.

#### struct `FAvaRundownServer::FCommandContext`  
`struct FCommandContext`  
_L264-312_
- desc: Associates a rundown entry with it's contextual resources needed to execute commands. There is only one "current" rundown per context. Changing the rundown will flush previous resources and allocate new ones of the new rundown.
- L266 _public prototype_ `virtual ~FCommandContext() = default;`
- L268 _public function_ `const FSoftObjectPath& GetCurrentRundownPath() const`
- L273 _public function_ `UAvaRundown* GetCurrentRundown() const`
- L278 _public function_ `void Flush(const TSharedPtr<FAvaRundownServer>& InRundownServer)`
- L283 _public function_ `void ConditionalFlush(const TSharedPtr<FAvaRundownServer>& InRundownServer, const FSoftObjectPath& InRundownPath)`
- L291 _public function_ `void ConditionalFlush(const TSharedPtr<FAvaRundownServer>& InRundownServer, const UAvaRundown* InRundown)`
- L300 _public function_ `virtual void SetCurrentRundown(const TSharedPtr<FAvaRundownServer>& InRundownServer, const FSoftObjectPath& InRundownPath, const TSharedPtr<FRundownEntry>& InRundownEntry)` — Set a new current rundown for the context. Derived classes will handle context switching implementation.
- L308 _protected member_ `FSoftObjectPath CurrentRundownPath;` — Currently loaded/cached rundown's path.
- L311 _protected member_ `TSharedPtr<FRundownEntry> CurrentRundownEntry;` — Currently loaded/cached rundown object.

#### struct `FAvaRundownServer::FEditCommandContext`  
`struct FEditCommandContext : public FCommandContext`  
_L327-346_
- inherits: `FCommandContext`
- desc: Context for page editing commands (i.e. GetPages, GetPageDetails, etc).
- L330 _public member_ `int32 ManagedPageId = FAvaRundownPage::InvalidPageId;` — PageId of the current managed ava asset.
- L331 _public member_ `FAvaRundownManagedInstanceHandles ManagedHandles;`
- L336 _public prototype_ `virtual void SetCurrentRundown(const TSharedPtr<FAvaRundownServer>& InRundownServer, const FSoftObjectPath& InRundownPath, const TSharedPtr<FRundownEntry>& InRundownEntry) override;`
- L345 _public prototype_ `void SaveCurrentRemoteControlPresetToPage(bool bInUnregister);` — Checks if previous RCP was registered. If so, save modified values to corresponding page. This may result in the Rundown to be modified. Will also unregister RCP from RC Module if requested.

#### struct `FAvaRundownServer::FPlaybackCommandContext`  
`struct FPlaybackCommandContext : public FCommandContext`  
_L354-364_
- inherits: `FCommandContext`
- desc: Context for playback commands (i.e. LoadRundown, PageAction, etc).
- L359 _public prototype_ `virtual void SetCurrentRundown(const TSharedPtr<FAvaRundownServer>& InRundownServer, const FSoftObjectPath& InRundownPath, const TSharedPtr<FRundownEntry>& InRundownEntry) override;`
- L362 _public prototype_ `void InitializePlaybackContext();`
- L363 _public prototype_ `static void ClosePlaybackContext(UAvaRundown* InRundownToClose);`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMedia/Private/Rundown/Commands/AvaRundownPageCommandSetSpawnPoint.h` (Private)


#### struct `FAvaRundownPageCommandSetSpawnPoint`  
`struct FAvaRundownPageCommandSetSpawnPoint : public FAvaRundownPageCommand`  
_L15-30_
- reflection: `USTRUCT(BlueprintType, meta = (DisplayName = "Set Spawn Point"))`
- inherits: `FAvaRundownPageCommand`
- desc: Specify a reference null actor to use the position to load the graphic at. This can be used to position a null actor with the given tag in the base level and have the graphics load at those positions.
- L20 _public prototype_ `virtual FText GetDescription() const override;`
- L21 _public prototype_ `virtual bool HasTransitionLogic() const override;`
- L22 _public prototype_ `virtual FString GetTransitionLayerString(const FString& InSeparator) const override;`
- L23 _public prototype_ `virtual bool CanExecuteOnLoad(FAvaRundownPageCommandContext& InContext, FString* OutFailureReason) const override;`
- L24 _public prototype_ `virtual bool ExecuteOnLoad(FAvaRundownPageCommandContext& InContext, FString& OutLoadOptions) const override;`
- L29 _public member_ `FName SpawnPointTag;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Page Data")` — Indicate which spawn point, by tag, to search for.

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMedia/Private/Rundown/Commands/AvaRundownPageCommandSetTransform.h` (Private)


#### struct `FAvaRundownPageCommandSetTransform`  
`struct FAvaRundownPageCommandSetTransform : public FAvaRundownPageCommand`  
_L15-30_
- reflection: `USTRUCT(BlueprintType, meta = (DisplayName = "Set Transform"))`
- inherits: `FAvaRundownPageCommand`
- desc: Page Command to specify the transform when loading the graphic. For streaming levels, this is applied when the level is loaded.
- L20 _public prototype_ `virtual FText GetDescription() const override;`
- L21 _public prototype_ `virtual bool HasTransitionLogic() const override;`
- L22 _public prototype_ `virtual FString GetTransitionLayerString(const FString& InSeparator) const override;`
- L23 _public prototype_ `virtual bool CanExecuteOnLoad(FAvaRundownPageCommandContext& InContext, FString* OutFailureReason) const override;`
- L24 _public prototype_ `virtual bool ExecuteOnLoad(FAvaRundownPageCommandContext& InContext, FString& OutLoadOptions) const override;`
- L29 _public member_ `FTransform Transform;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Page Data")` — Specify the root transform to apply at load time.

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMedia/Private/Rundown/Commands/AvaRundownPageCommandStopLayers.h` (Private)


#### struct `FAvaRundownPageCommandStopLayers`  
`struct FAvaRundownPageCommandStopLayers : public FAvaRundownPageCommand`  
_L11-26_
- reflection: `USTRUCT(BlueprintType, meta = (DisplayName = "Stop Layers"))`
- inherits: `FAvaRundownPageCommand`
- L16 _public prototype_ `virtual FText GetDescription() const override;`
- L17 _public prototype_ `virtual bool HasTransitionLogic() const override;`
- L18 _public prototype_ `virtual FString GetTransitionLayerString(const FString& InSeparator) const override;`
- L19 _public prototype_ `virtual bool CanExecuteOnPlay(FAvaRundownPageCommandContext& InContext, FString* OutFailureReason) const override;`
- L20 _public prototype_ `virtual bool ExecuteOnPlay(FAvaRundownPageTransitionBuilder& InTransitionBuilder, FAvaRundownPageCommandContext& InContext) const override;`
- L25 _public member_ `FAvaTagHandleContainer Layers;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Page Data")` — Layers to stop.

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMedia/Private/Rundown/Transition/AvaRundownPageTransition.h` (Private)


#### class `UAvaRundownPageTransition`  
`class UAvaRundownPageTransition : public UAvaPlaybackTransition`  
_L30-132_
- reflection: `UCLASS()`
- inherits: `UAvaPlaybackTransition`
- desc: Class for creating and tracking page transitions in the rundown. It is responsible for creating the playable transition object when requested from the playback graphs.
- L35 _public prototype_ `static UAvaRundownPageTransition* MakeNew(UAvaRundown* InRundown);`
- L37 _public prototype_ `bool AddEnterPage(UAvaRundownPagePlayer* InPagePlayer);`
- L38 _public prototype_ `bool AddPlayingPage(UAvaRundownPagePlayer* InPagePlayer);`
- L39 _public prototype_ `bool AddExitPage(UAvaRundownPagePlayer* InPagePlayer);`
- L41 _public function_ `TConstArrayView<TWeakObjectPtr<UAvaRundownPagePlayer>> GetEnterPlayers() const`
- L42 _public function_ `TConstArrayView<TWeakObjectPtr<UAvaRundownPagePlayer>> GetPlayingPlayers() const`
- L43 _public function_ `TConstArrayView<TWeakObjectPtr<UAvaRundownPagePlayer>> GetExitPlayers() const`
- L46 _public prototype_ `virtual bool IsVisibilityConstrained(const UAvaPlayable* InPlayable) const override;`
- L50 _public prototype_ `virtual bool CanStart(bool& bOutShouldDiscard) override;`
- L51 _public prototype_ `virtual void Start() override;`
- L52 _public prototype_ `virtual void Stop() override;`
- L53 _public prototype_ `virtual bool IsRunning() const override;`
- L57 _public function_ `FName GetChannelName() const` — Returns the channel this transition is happening in. A transition can only have pages within the same channel.
- L59 _public function_ `bool HasEnterPages() const`
- L61 _public prototype_ `bool HasEnterPagesWithNoTransitionLogic() const;`
- L63 _public prototype_ `bool HasPagePlayer(const UAvaRundownPagePlayer* InPagePlayer) const;`
- L65 _public prototype_ `bool ContainsTransitionLayer(const FAvaTagId& InTagId) const;`
- L67 _public prototype_ `UAvaRundown* GetRundown() const;`
- L69 _public prototype_ `FString GetBriefTransitionDescription() const;`
- L73 _public member_ `TSet<FGuid> InstancesBypassingTransition;` — `UPROPERTY(Transient)` — Instances will not be added to the playable transition.
- L77 _public member_ `TSet<FGuid> ReusedInstances;` — `UPROPERTY(Transient)` — Reused existing instance player. Will be added both as "entering" and "playing" in the playable transition.
- L80 _public member_ `TArray<FAvaTagHandle> ExitLayers;` — Layers to kick out as part of this transition command.
- L86 _public member_ `bool bIsPreviewFrameTransition = false;` — Special mark if any of the enter playables where issued with a PreviewFrame play type. Current logic will mark the whole transition.
- L90 _protected prototype_ `void Start_Synchronized();` — Implementation of the Start function intended to be synchronized on cluster.
- L92 _protected prototype_ `UAvaRundownPlaybackInstancePlayer* FindInstancePlayerForPlayable(const UAvaPlayable* InPlayable) const;`
- L93 _protected prototype_ `UAvaRundownPagePlayer* FindPagePlayerForPlayable(const UAvaPlayable* InPlayable) const;`
- L95 _protected prototype_ `void OnTransitionEvent(UAvaPlayable* InPlayable, UAvaPlayableTransition* InTransition, EAvaPlayableTransitionEventFlags InTransitionFlags);`
- L96 _protected prototype_ `void OnPlayableCreated(UAvaPlaybackGraph* InPlayback, UAvaPlayable* InPlayable);`
- L98 _protected prototype_ `void AddPlayersToBuilder(FAvaPlayableTransitionBuilder& InOutBuilder, const TArray<TWeakObjectPtr<UAvaRundownPagePlayer>>& InPlayersWeak, const TCHAR* InCategory, EAvaPlayableTransitionEntryRole InEntryRole) const;`
- L99 _protected prototype_ `void AddPlayablesToBuilder(FAvaPlayableTransitionBuilder& InOutBuilder, const UAvaRundownPagePlayer* InPlayer, const TCHAR* InCategory, EAvaPlayableTransitionEntryRole InEntryRole) const;`
- L101 _protected prototype_ `void MakePlayableTransition();`
- L103 _protected prototype_ `FString GetInstanceName() const;`
- L104 _protected prototype_ `void LogDetailedTransitionInfo() const;`
- L106 _protected prototype_ `void RegisterToPlayableTransitionEvent();`
- L107 _protected prototype_ `void UnregisterFromPlayableTransitionEvent() const;`
- L109 _protected prototype_ `void RegisterEnterPagePlayerEvents(UAvaRundownPagePlayer* InPagePlayer);`
- L110 _protected prototype_ `void UnregisterEnterPagePlayerEvents(UAvaRundownPagePlayer* InPagePlayer);`
- L112 _protected prototype_ `bool AddPagePlayer(UAvaRundownPagePlayer* InPagePlayer, TArray<TWeakObjectPtr<UAvaRundownPagePlayer>>& OutPagePlayersWeak);`
- L113 _protected prototype_ `void UpdateChannelName(const UAvaRundownPagePlayer* InPagePlayer);`
- L116 _protected member_ `FName ChannelName;`
- L118 _protected member_ `TArray<TWeakObjectPtr<UAvaRundownPagePlayer>> EnterPlayersWeak;`
- L119 _protected member_ `TArray<TWeakObjectPtr<UAvaRundownPagePlayer>> PlayingPlayersWeak;`
- L120 _protected member_ `TArray<TWeakObjectPtr<UAvaRundownPagePlayer>> ExitPlayersWeak;`
- L122 _protected member_ `TSet<FAvaTagId> CachedTransitionLayers;`
- L124 _protected member_ `TSet<FGuid> InstancesMarkedForDiscard;`
- L126 _protected member_ `TSharedPtr<UE::AvaPlayback::Utils::FAsyncAssetLoader> AsyncAssetLoader;`
- L129 _protected member_ `TObjectPtr<UAvaPlayableTransition> PlayableTransition;` — `UPROPERTY(Transient)`

#### Free symbols / members of external scopes

- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace AvaPlayback` (scope `UE`)
- L19 _namespace_ `namespace Utils` (scope `UE::AvaPlayback`)

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMedia/Private/Rundown/Transition/AvaRundownPageTransitionBuilder.h` (Private)


#### class `FAvaRundownPageTransitionBuilder`  
`class FAvaRundownPageTransitionBuilder`  
_L33-80_
- desc: Page Transition Builder to batch pages appropriately in page transitions to provide support for multiple pages being played at the same time. Summary of the page batching rules (as of yet): - For enter pages, the batching requires all enter pages (of any TL Layer) of a given channel to be in the same transition. - (*) There can only be one enter page of a particular layer in the transition. This rule should be implemented by TL itself, but it is not atm. It is thus a hard coded rule by the rundown transition system for now. The rule for now is to keep only the first page being added. - For exit pages, when they are part of a transition that has enter pages, we can add all the currently playing pages (in the given channel) as "exit" pages. - If the transition is a "take out" only transition, then we need to batch the exit pages per layers (on top of per channel) since the whole transition has an override that allows only one layer to be specified. This is not done at the moment. For take out, there is no batching at all atm, all pages are added in a separate transition. Note: for now, FAvaRundownPageTransitionBuilder is not used for stopping pages. This may change depending on refactor of the underlying TL and transition system. Some traces of this case are left in this class for that reason, so it is easy to adapt it for the "take out" case.
- L36 _public function_ `FAvaRundownPageTransitionBuilder(UAvaRundown* InRundown) : Rundown(InRundown)`
- L38 _public prototype_ `~FAvaRundownPageTransitionBuilder();`
- L45 _public prototype_ `UAvaRundownPageTransition* FindTransition(FName InChannelName) const;` — @brief Finds a suitable page transition object for the channel. @param InChannel channel we are requesting the transition object for. @return the requested page transition object or null if not found.
- L52 _public prototype_ `UAvaRundownPageTransition* FindTransition(const UAvaRundownPagePlayer* InPlayer) const;` — @brief Finds a suitable page transition object for the given page player. @param InPlayer Page player we are requesting the transition object for. @return the requested page transition object or null if not found.
- L61 _public prototype_ `UAvaRundownPageTransition* FindOrAddTransition(FName InChannelName);` — @brief Retrieves a suitable page transition object for the given channel. @param InChannel Channel we are requesting the transition object for. @return the requested page transition object. This is where the batching occurs according to criteria.
- L70 _public prototype_ `UAvaRundownPageTransition* FindOrAddTransition(const UAvaRundownPagePlayer* InPlayer);` — @brief Retrieves a suitable page transition object for the given page player. @param InPlayer Page player we are requesting the transition object for. @return the requested page transition object. This is where the batching occurs according to criteria.
- L73 _private prototype_ `UAvaRundownPageTransition* AddTransition(FName InChannelName);`
- L76 _private member_ `UAvaRundown* Rundown;`
- L79 _private member_ `TArray<UAvaRundownPageTransition*> PageTransitions;` — There will be a transition for each channel.

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMedia/Public/AvaMediaDefines.h` (Public)


#### enum `EAvaBroadcastChannelState`  
`enum class EAvaBroadcastChannelState : uint8`  
_L13-23_
- reflection: `UENUM()`
- desc: Channel state is a union summary of the output's states.
- L16 _public enumerator_ `Offline` — Indicates that all channel outputs are offline.
- L18 _public enumerator_ `Idle` — Indicates that at least some of the channel outputs are idle (but none are live).
- L20 _public enumerator_ `Live` — Indicates that at least some of the channel outputs are live.
- L22 _public enumerator_ `Max UMETA(Hidden)`

#### enum `EAvaBroadcastChannelType`  
`enum class EAvaBroadcastChannelType : uint8`  
_L41-45_
- reflection: `UENUM()`
- desc: The channel type defines what it is used for in the broadcast framework. Primarily, the channel type is intended to resolve channel collisions between simultaneous "program" and "preview" playbacks on a given system. In other words: - Channel selection for rundown pages is restricted to "program" channels. - Channel selection for preview is restricted to "preview" channels. It is thus not possible for a user to mistakenly select the same channel for both preview and program. Some additional restrictions are applied according to channel type: - preview channels must only have outputs local to the process. "Remote" previews are not supported. - [backend] playback request type (program or preview) must match with the channel type. This is a safety net for any other extended code paths that are not in the Motion Design plugin.
- L43 _public enumerator_ `Program`
- L44 _public enumerator_ `Preview`

#### enum `EAvaBroadcastOutputState`  
`enum class EAvaBroadcastOutputState : uint8`  
_L51-65_
- reflection: `UENUM()`
- desc: Status of the media output.
- L54 _public enumerator_ `Invalid` — Invalid/Uninitialized state.
- L56 _public enumerator_ `Offline` — For remote output that is not connected, output disabled.
- L58 _public enumerator_ `Idle` — Server Connected or Local (MediaCapture Status: Stopped)
- L60 _public enumerator_ `Preparing` — MediaCapture Status: Preparing
- L62 _public enumerator_ `Live` — Broadcasting (MediaCapture Status: Capturing)
- L64 _public enumerator_ `Error` — MediaCapture Error (unrecoverable)

#### enum `EAvaBroadcastIssueSeverity`  
`enum class EAvaBroadcastIssueSeverity : uint8`  
_L72-79_
- reflection: `UENUM()`
- desc: In case the broadcast device is Live (see EAvaBroadcastOutputState), this extra status indicates if the device is operating normally.
- L74 _public enumerator_ `None`
- L75 _public enumerator_ `Warnings`
- L76 _public enumerator_ `Errors`
- L78 _public enumerator_ `Max UMETA(Hidden)`

#### enum `EAvaBroadcastChange`  
`enum class EAvaBroadcastChange : uint8`  
_L82-91_
- desc: An enum indicating what changed in Broadcast
- L84 _public enumerator_ `None = 0`
- L85 _public enumerator_ `CurrentProfile = 1 << 0` — When the Current Profile Changed
- L86 _public enumerator_ `ChannelGrid = 1 << 1` — When a Channel has been Added/Removed
- L87 _public enumerator_ `ChannelRename = 1 << 2` — When a Channel has been Renamed
- L88 _public enumerator_ `ChannelType = 1 << 3` — When a Channel has changed type.
- L89 _public enumerator_ `OutputDevices = 1 << 4` — When output devices have changed
- L90 _public enumerator_ `All = 0xFF`

#### enum `EAvaBroadcastChannelChange`  
`enum class EAvaBroadcastChannelChange : uint8`  
_L95-102_
- desc: An enum indicating what changed in Channel
- L97 _public enumerator_ `None = 0`
- L98 _public enumerator_ `State = 1 << 0`
- L99 _public enumerator_ `RenderTarget = 1 << 1`
- L100 _public enumerator_ `MediaOutputs = 1 << 2`
- L101 _public enumerator_ `Settings = 1 << 3`

#### enum `EAvaBroadcastOutputOverrunAction`  
`enum class EAvaBroadcastOutputOverrunAction : uint8`  
_L109-115_
- reflection: `UENUM()`
- desc: Action to perform when a media capture overrun (main vs render thread) occurs on a broadcast channel.
- L112 _public enumerator_ `Flush` — Flush rendering thread such that all scheduled commands are executed.
- L114 _public enumerator_ `Skip` — Skip capturing a frame if readback is trailing too much.

#### enum `EAvaPlayableStatus`  
`enum class EAvaPlayableStatus : uint8`  
_L125-133_
- reflection: `UENUM()`
- desc: The status of a playable object. This is related to the status of the transient playable object which is duplicated from the source asset. The transient playable object is also referred to as the "runtime" asset instance.
- L127 _public enumerator_ `Unknown`
- L128 _public enumerator_ `Error`
- L129 _public enumerator_ `Unloaded`
- L130 _public enumerator_ `Loading`
- L131 _public enumerator_ `Loaded`
- L132 _public enumerator_ `Visible`

#### enum `EAvaPlayableSequenceEventType`  
`enum class EAvaPlayableSequenceEventType : uint8`  
_L136-142_
- reflection: `UENUM()`
- L138 _public enumerator_ `None UMETA(Hidden)`
- L139 _public enumerator_ `Started`
- L140 _public enumerator_ `Paused`
- L141 _public enumerator_ `Finished`

#### enum `EAvaPlayableTransitionFlags`  
`enum class EAvaPlayableTransitionFlags : uint8`  
_L147-156_
- desc: Transition flags carry additional context to help resolve the behaviors.
- L149 _public enumerator_ `None = 0`
- L151 _public enumerator_ `TreatPlayingAsExiting = 1 << 0` — Playing playables will be treated as exit playables.
- L153 _public enumerator_ `HasReusedPlayables = 1 << 1` — Transition contains some reused playables (i.e. both enter and playing).
- L155 _public enumerator_ `PlayEnterPlayablesAtPreviewFrame = 1 << 2` — Special logic to override the enter playables behaviors for the "PreviewFrame".

#### enum `EAvaPlayableTransitionEventFlags`  
`enum class EAvaPlayableTransitionEventFlags : uint8`  
_L159-172_
- L161 _public enumerator_ `None = 0`
- L163 _public enumerator_ `Starting = 1 << 0` — The transition is starting.
- L165 _public enumerator_ `ShowPlayable = 1 << 1` — The enter playable can be shown.
- L167 _public enumerator_ `StopPlayable = 1 << 2` — The playable needs to be stopped.
- L169 _public enumerator_ `MarkPlayableDiscard = 1 << 3` — The playable needs to be discarded at the end of the transition.
- L171 _public enumerator_ `Finished = 1 << 4` — The transition is finished and can be cleaned up.

#### enum `EAvaPlayableRCUpdateFlags`  
`enum class EAvaPlayableRCUpdateFlags : uint8`  
_L177-187_
- reflection: `UENUM(meta=(Bitflags, UseEnumValuesAsMaskValuesInEditor = "true"))`
- desc: Flags for the remote control values update command.
- L179 _public enumerator_ `None = 0`
- L181 _public enumerator_ `ExecuteControllerBehaviors = 1 << 0` — Execute Controller Behaviors
- L186 _public enumerator_ `ControllerValuesAsEvents = 1 << 1` — The controller values are to be considered as events and will only apply to the event controllers. Non-event controllers and entity values are ignored during the execution of this update.

#### struct `FAvaPlaybackPlayerParameters`  
`struct FAvaPlaybackPlayerParameters`  
_L193-197_
- desc: Parameters of a player entry for active player nodes in playback graph.
- L195 _public member_ `TWeakObjectPtr<class UAvaPlaybackNode> Node;`
- L196 _public member_ `FAvaSoftAssetPtr Asset;`

#### struct `FAvaPlaybackChannelParameters`  
`struct FAvaPlaybackChannelParameters`  
_L202-217_
- desc: Parameters used to tell a Channel its Playback Settings
- L205 _public member_ `int32 ChannelIndex = -1;` — Channel index for the current playback setting.
- L211 _public member_ `TArray<FAvaPlaybackPlayerParameters> Players;` — If a playback node is reached during tick traversal, it is going to add an entry.
- L213 _public function_ `bool HasAssets() const`

#### struct `FAvaPlaybackEventParameters`  
`struct FAvaPlaybackEventParameters`  
_L222-252_
- desc: Parameters for Event/Action
- L225 _public member_ `TArray<int32> ChannelIndices;` — List of channel indices that this event originates from.
- L227 _public member_ `FAvaSoftAssetPtr Asset;`
- L229 _public function_ `bool IsAssetValid() const`
- L234 _public function_ `const FSoftObjectPath& GetAssetPath() const`
- L239 _public function_ `void RequestTriggerEventAction()`
- L244 _public function_ `bool ShouldTriggerEventAction() const`
- L251 _protected member_ `bool bTriggerEventAction = false;`

#### enum `EAvaRundownPageListChange`  
`enum class EAvaRundownPageListChange : uint8`  
_L255-267_
- L257 _public enumerator_ `None = 0`
- L259 _public enumerator_ `AddedPages = 1 << 0`
- L260 _public enumerator_ `RemovedPages = 1 << 1`
- L261 _public enumerator_ `RenumberedPageId = 1 << 2`
- L262 _public enumerator_ `SubListAddedOrRemoved = 1 << 3`
- L263 _public enumerator_ `SubListRenamed = 1 << 4`
- L264 _public enumerator_ `ReorderedPageView = 1 << 5`
- L266 _public enumerator_ `All = 0xFF`

#### enum `EAvaRundownPageChanges`  
`enum class EAvaRundownPageChanges : uint8`  
_L270-284_
- L272 _public enumerator_ `None = 0`
- L274 _public enumerator_ `AnimationSettings = 1 << 0`
- L275 _public enumerator_ `RemoteControlValues = 1 << 1`
- L276 _public enumerator_ `Blueprint = 1 << 2`
- L277 _public enumerator_ `Channel = 1 << 3`
- L278 _public enumerator_ `Status = 1 << 4`
- L279 _public enumerator_ `Name = 1 << 5`
- L280 _public enumerator_ `FriendlyName = 1 << 6`
- L281 _public enumerator_ `Commands = 1 << 7`
- L283 _public enumerator_ `All = 0xFF`

#### enum `EAvaPlaybackAssetStatus`  
`enum class EAvaPlaybackAssetStatus`  
_L295-310_
- reflection: `UENUM()`
- desc: The status of the playback asset on disk. This is also sometimes referred to as the "source" asset, by contrast to the runtime (or managed) transient asset for runtime playback. It will also refer to the source Motion Design asset, rather than a playback object.
- L298 _public enumerator_ `Unknown` — Invalid status.
- L300 _public enumerator_ `Missing` — Missing asset
- L305 _public enumerator_ `MissingDependencies` — Missing asset dependencies Note: An Motion Design asset can run even with missing dependencies.
- L307 _public enumerator_ `NeedsSync` — Asset is out of date from compare with remote.
- L309 _public enumerator_ `Available` — Asset is fully available and up to date.

#### enum `EAvaPlaybackStatus`  
`enum class EAvaPlaybackStatus`  
_L320-344_
- reflection: `UENUM()`
- desc: The status of the playback object. This is related to the status of the transient playback object which is duplicated from the source asset. The transient playback object is also referred to as the "managed" or "runtime" asset.
- L323 _public enumerator_ `Unknown` — Invalid status.
- L325 _public enumerator_ `Missing` — Missing asset (or out of date?).
- L327 _public enumerator_ `Syncing` — Asset is being downloaded.
- L329 _public enumerator_ `Available` — Asset is available, not loaded.
- L331 _public enumerator_ `Loading` — Load has been requested.
- L333 _public enumerator_ `Loaded` — Asset is loaded in memory and ready to play.
- L335 _public enumerator_ `Starting` — Start has been requested.
- L337 _public enumerator_ `Started` — Currently playing.
- L339 _public enumerator_ `Stopping` — Stop has been requested. After stopping, status goes back to Loaded.
- L341 _public enumerator_ `Unloading` — Unload has been requested. After unloaded, status goes back to Available.
- L343 _public enumerator_ `Error` — Something bad happened.

#### enum `EAvaRundownPageListType`  
`enum class EAvaRundownPageListType : uint8`  
_L350-355_
- reflection: `UENUM(BlueprintType, DisplayName = "Motion Design Rundown Page List Type")`
- desc: Rundown's page list type.
- L352 _public enumerator_ `Template`
- L353 _public enumerator_ `Instance`
- L354 _public enumerator_ `View`

#### struct `FAvaRundownPageListReference`  
`struct FAvaRundownPageListReference`  
_L358-384_
- reflection: `USTRUCT(BlueprintType, DisplayName = "Motion Design Rundown Page List Reference")`
- L363 _public member_ `EAvaRundownPageListType Type = EAvaRundownPageListType::Instance;` — `UPROPERTY()`
- L366 _public member_ `FGuid SubListId;` — `UPROPERTY()`
- L368 _public function_ `bool operator==(const FAvaRundownPageListReference& InOther) const`
- L383 _public function_ `bool operator!=(const FAvaRundownPageListReference& InOther) const`

#### Free symbols / members of external scopes

- L92 _prototype_ `ENUM_CLASS_FLAGS(EAvaBroadcastChange);`
- L103 _prototype_ `ENUM_CLASS_FLAGS(EAvaBroadcastChannelChange);`
- L157 _prototype_ `ENUM_CLASS_FLAGS(EAvaPlayableTransitionFlags);`
- L173 _prototype_ `ENUM_CLASS_FLAGS(EAvaPlayableTransitionEventFlags);`
- L188 _prototype_ `ENUM_CLASS_FLAGS(EAvaPlayableRCUpdateFlags);`
- L268 _prototype_ `ENUM_CLASS_FLAGS(EAvaRundownPageListChange);`
- L285 _prototype_ `ENUM_CLASS_FLAGS(EAvaRundownPageChanges);`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMedia/Public/AvaMediaSettings.h` (Public)


#### enum `EAvaMediaLogVerbosity`  
`enum class EAvaMediaLogVerbosity : uint8`  
_L28-38_
- reflection: `UENUM()`
- desc: Defines the verbosity level of the logging system. This enum mirrors ELogVerbosity but can be used directly as a configuration property.
- L30 _public enumerator_ `NoLogging = 0`
- L31 _public enumerator_ `Fatal`
- L32 _public enumerator_ `Error`
- L33 _public enumerator_ `Warning`
- L34 _public enumerator_ `Display`
- L35 _public enumerator_ `Log`
- L36 _public enumerator_ `Verbose`
- L37 _public enumerator_ `VeryVerbose`

#### struct `FAvaPlaybackServerLoggingEntry`  
`struct FAvaPlaybackServerLoggingEntry`  
_L41-50_
- reflection: `USTRUCT()`
- L46 _public member_ `FName Category;` — `UPROPERTY(config, EditAnywhere, Category=Settings)`
- L49 _public member_ `EAvaMediaLogVerbosity VerbosityLevel = EAvaMediaLogVerbosity::VeryVerbose;` — `UPROPERTY(config, EditAnywhere, Category=Settings)`

#### struct `FAvaMediaLocalPlaybackServerSettings`  
`struct FAvaMediaLocalPlaybackServerSettings`  
_L53-85_
- reflection: `USTRUCT()`
- L59 _public member_ `FString ServerName = TEXT("Loc` — `UPROPERTY(config, EditAnywhere, Category = Settings)` — Name given to the game mode local playback server started as a separate process.
- L63 _public member_ `FIntPoint Resolution = FIntPoint(960, 540);` — `UPROPERTY(config, EditAnywhere, Category = Settings)` — Main window resolution of the local playback server.
- L67 _public member_ `bool bEnableLogConsole = false;` — `UPROPERTY(config, EditAnywhere, Category = Settings)` — Enable a log console for the local server process.
- L74 _public member_ `bool bDisablePython = true;` — `UPROPERTY(config, EditAnywhere, DisplayName="Disable Python (Performance)", Category = Settings)` — Disables python with the -DisablePython command. This is recommended for performance, as Python garbage collection call could impact the overall performance of a garbage collection pass.
- L78 _public member_ `FString ExtraCommandLineArguments;` — `UPROPERTY(config, EditAnywhere, Category = Settings)` — Extra command line arguments.
- L84 _public member_ `TArray<FAvaPlaybackServerLoggingEntry> Logging;` — `UPROPERTY(Config, EditAnywhere, Category="Settings")` — Which logs to include and with which verbosity level

#### class `UAvaMediaSettings`  
`class UAvaMediaSettings : public UDeveloperSettings`  
_L88-271_
- reflection: `UCLASS(MinimalAPI, config=Engine, meta=(DisplayName="Playback & Broadcast"))`
- inherits: `UDeveloperSettings`
- L93 _public prototype_ `UAvaMediaSettings();`
- L95 _public function_ `static const UAvaMediaSettings& Get()`
- L96 _public function_ `static UAvaMediaSettings& GetMutable()`
- L98 _public prototype_ `static ELogVerbosity::Type ToLogVerbosity(EAvaMediaLogVerbosity InAvaMediaLogVerbosity);`
- L101 _public prototype_ `FString GenerateLocalPlaybackServerCommandLine() const;` — Generates the command line arguments for the local playback server
- L104 _public prototype_ `virtual void PostInitProperties() override;`
- L105 _public prototype_ `virtual void PostReloadConfig(FProperty* InPropertyThatWasLoaded) override;`
- L107 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& InPropertyChangedEvent) override;`
- L113 _public member_ `FLinearColor ChannelClearColor = FLinearColor::Black;` — `UPROPERTY(config, EditAnywhere, Category = "Broadcast")` — Specifies the background clear color for the channel.
- L117 _public member_ `TEnumAsByte<EPixelFormat> ChannelDefaultPixelFormat = EPixelFormat::PF_B8G8R8A8;` — `UPROPERTY(config, EditAnywhere, Category = "Broadcast")` — Pixel format used if no media output has specific format requirement.
- L121 _public member_ `FIntPoint ChannelDefaultResolution = FIntPoint(1920, 1080);` — `UPROPERTY(config, EditAnywhere, Category = "Broadcast")` — Resolution used if no media output has specific resolution requirement.
- L127 _public member_ `EAvaBroadcastOutputOverrunAction ChannelOutputOverrunAction = EAvaBroadcastOutputOverrunAction::Skip;` — `UPROPERTY(config, EditAnywhere, Category = "Broadcast")` — Action to perform when game thread overruns render thread and all frames are in flights being captured / readback.
- L134 _public member_ `bool bDrawPlaceholderWidget = false;` — `UPROPERTY(config, EditAnywhere, Category = "Broadcast")` — Enables drawing the placeholder widget when there is no Motion Design asset playing. If false, the channel is cleared to the background color.
- L138 _public member_ `TSoftClassPtr<UUserWidget> PlaceholderWidgetClass;` — `UPROPERTY(config, EditAnywhere, Category = "Broadcast")` — Specify a place holder widget to render when no Motion Design asset is playing.
- L145 _public member_ `FIntPoint PreviewDefaultResolution = FIntPoint(960, 540);` — `UPROPERTY(config, EditAnywhere, Category = "Rundown")` — Default resolution for rundown preview. This resolution may be lower than the broadcast resolution to improve gpu performance.
- L148 _public member_ `FString PreviewChannelName;` — `UPROPERTY(config, EditAnywhere, Category = "Rundown")`
- L155 _public member_ `bool bAllowReuseInPreviewFrame = false;` — `UPROPERTY(config, EditAnywhere, Category = "Rundown")` — Whether to allow re-using the instances of a page when doing preview frame. Default to false as preview frame kicks everything existing in the layer of the page to preview.
- L162 _public member_ `bool bEnableComboTemplateSpecialLogic = true;` — `UPROPERTY(config, EditAnywhere, Category = "Rundown")` — Special logic will not play any transition if the RC values are the same. This applies to combo templates.
- L169 _public member_ `bool bEnableSingleTemplateSpecialLogic = false;` — `UPROPERTY(config, EditAnywhere, Category = "Rundown")` — Special logic will not play any transition if the RC values are the same. This applies to single (non-combo) templates.
- L175 _public member_ `bool bRundownPushControllerEventsToProgram = true;` — `UPROPERTY(config, EditAnywhere, Category = "Rundown")` — Enables the propagation of controller events to pages playing in program channels.
- L181 _public member_ `bool bRundownPushControllerEventsToPreview = true;` — `UPROPERTY(config, EditAnywhere, Category = "Rundown")` — Enables the propagation of controller events to pages playing in preview channels.
- L185 _public member_ `bool bAutoStartPlaybackClient = false;` — `UPROPERTY(config, EditAnywhere, Category = "Playback Client")` — Whether playback client is started automatically.
- L189 _public member_ `bool bVerbosePlaybackClientLogging = false;` — `UPROPERTY(config, EditAnywhere, Category = "Playback Client")` — Enable verbose logging for playback client.
- L193 _public member_ `float PingInterval = 2.5f;` — `UPROPERTY(config, EditAnywhere, Category = "Playback Client")` — Defines the interval in seconds in which servers are being pinged by the client.
- L197 _public member_ `float PingTimeoutInterval = 3*2.5f;` — `UPROPERTY(config, EditAnywhere, Category = "Playback Client")` — If servers do not respond after the ping timeout interval in seconds, they are disconnected.
- L201 _public member_ `float ClientPendingStatusRequestTimeout = 5.0f;` — `UPROPERTY(config, EditAnywhere, Category = "Playback Client")` — Defines the timeout, in seconds, after which a pending status request is dropped and issued again.
- L205 _public member_ `bool bAutoStartPlaybackServer = false;` — `UPROPERTY(config, EditAnywhere, Category = "Playback Server")` — Whether playback server is started automatically.
- L209 _public member_ `FString PlaybackServerName;` — `UPROPERTY(config, EditAnywhere, Category = "Playback Server")` — Name given to the playback server. If empty, the server name will be the computer name.
- L216 _public member_ `EAvaMediaLogVerbosity PlaybackServerLogReplicationVerbosity = EAvaMediaLogVerbosity::Error;` — `UPROPERTY(config, EditAnywhere, Category = "Playback Server")` — Determines the verbosity level of the playback server's log replication. The server is not going to replicate any log event that is below this log level.
- L220 _public member_ `float ServerPendingStatusRequestTimeout = 5.0f;` — `UPROPERTY(config, EditAnywhere, Category = "Playback Server")` — Defines the timeout, in seconds, after which a pending status request is dropped and issued again.
- L224 _public member_ `float ServerPendingPlaybackCommandTimeout = 5.0f;` — `UPROPERTY(config, EditAnywhere, Category = "Playback Server")` — Defines the timeout, in seconds, after which pending playback commands are discarded.
- L228 _public member_ `FAvaMediaLocalPlaybackServerSettings LocalPlaybackServerSettings;` — `UPROPERTY(config, EditAnywhere, Category = "Playback Server")` — Settings for the local playback server process. See "Launch Local Server" in the broadcast editor toolbar.
- L232 _public member_ `bool bKeepPagesLoaded = false;` — `UPROPERTY(Config, EditAnywhere, Category = "Playback Manager")` — If true, the playback objects are kept in memory after pages are stopped. They are unloaded otherwise.
- L235 _public member_ `FAvaInstanceSettings AvaInstanceSettings;` — `UPROPERTY(Config, EditAnywhere, Category = "Playback Manager")`
- L238 _public member_ `FAvaPlayableSettings PlayableSettings;` — `UPROPERTY(Config, EditAnywhere, Category = "Playback Manager")`
- L245 _public member_ `int32 ManagedInstanceCacheMaximumSize = 20;` — `UPROPERTY(Config, EditAnywhere, Category = "Managed Motion Design Instance Cache", meta = (DisplayName = "Maximum Cache Size"))` — Maximum cached Managed Motion Design assets used for rundown editor's page details. A value of 0 indicate the cache will grow without limit.
- L249 _public member_ `bool bAutoStartWebServer = true;` — `UPROPERTY(config, EditAnywhere, Category = "Web Server")` — Whether web server is started automatically.
- L253 _public member_ `uint32 HttpServerPort = 10123;` — `UPROPERTY(config, EditAnywhere, Category = "Web Server")` — The web remote control HTTP server's port.
- L256 _public member_ `static const FName SynchronizedEventsFeatureSelection_Default;` — Default value of the synchronized events feature selection.
- L259 _private prototype_ `static UAvaMediaSettings* GetSingletonInstance();`
- L263 _private prototype_ `void UpdateLocalPlaybackServerCommandLinePreview();` — Updates the command line preview to reflect the latest local playback server settings
- L269 _private member_ `FString LocalPlaybackServerCommandLinePreview;` — `UPROPERTY(Transient, VisibleAnywhere, Category = "Playback Server", meta=(MultiLine, DisplayAfter="LocalPlaybackServerSettings"))` — Preview command line arguments from the playback server settings

#### Free symbols / members of external scopes

- L21 _macro_ `#define UE_API AVALANCHEMEDIA_API`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMedia/Public/Broadcast/AvaBroadcast.h` (Public)


#### class `UAvaBroadcast`  
`class UAvaBroadcast : public UObject`  
_L24-206_
- reflection: `UCLASS(NotBlueprintable)`
- inherits: `UObject`
- desc: Single Instance Class that manages all the Output Channels
- L29 _public prototype_ `static UAvaBroadcast& Get();`
- L31 _public prototype_ `virtual void BeginDestroy() override;`
- L34 _public prototype_ `static UAvaBroadcast* GetBroadcast();` — `UFUNCTION(BlueprintCallable, Category = "Motion Design Broadcast")`
- L37 _public prototype_ `void StartBroadcast();` — `UFUNCTION(BlueprintCallable, Category = "Motion Design Broadcast")`
- L40 _public prototype_ `void StopBroadcast();` — `UFUNCTION(BlueprintCallable, Category = "Motion Design Broadcast")`
- L43 _public prototype_ `bool IsBroadcastingAnyChannel() const;` — `UFUNCTION(BlueprintCallable, Category = "Motion Design Broadcast")`
- L46 _public prototype_ `bool IsBroadcastingAllChannels() const;` — `UFUNCTION(BlueprintCallable, Category = "Motion Design Broadcast")`
- L53 _public prototype_ `bool ConditionalStartBroadcastChannel(const FName& InChannelName);` — @brief Starts the channel if not started. Does nothing if already started. @param InChannelName Name of the channel to conditionally start. @return true if the channel is started (including if it was already started), false if the channel couldn't be started.
- L55 _public prototype_ `TArray<FName> GetProfileNames() const;`
- L57 _public prototype_ `const TMap<FName, FAvaBroadcastProfile>& GetProfiles() const;`
- L60 _public prototype_ `FName CreateProfile(FName InProfileName, bool bMakeCurrentProfile = true);` — Returns the actual name of the profile created. Defers in Number from InProfileName if it is an already existing Profile
- L62 _public prototype_ `bool DuplicateProfile(FName InNewProfile, FName InTemplateProfile, bool bMakeCurrentProfile = true);`
- L64 _public prototype_ `bool DuplicateCurrentProfile(FName InNewProfileName = NAME_None, bool bMakeCurrentProfile = true);`
- L66 _public prototype_ `bool RemoveProfile(FName InProfileName);`
- L68 _public prototype_ `bool CanRenameProfile(FName InProfileName, FName InNewProfileName, FText* OutErrorMessage = nullptr) const;`
- L70 _public prototype_ `bool RenameProfile(FName InProfileName, FName InNewProfileName);`
- L72 _public prototype_ `bool SetCurrentProfile(FName InProfileName);`
- L74 _public function_ `FName GetCurrentProfileName() const`
- L76 _public prototype_ `FAvaBroadcastProfile& GetProfile(FName InProfileName);`
- L78 _public prototype_ `const FAvaBroadcastProfile& GetProfile(FName InProfileName) const;`
- L80 _public function_ `FAvaBroadcastProfile& GetCurrentProfile()`
- L82 _public function_ `const FAvaBroadcastProfile& GetCurrentProfile() const`
- L84 _public prototype_ `void LoadBroadcast();`
- L85 _public prototype_ `void SaveBroadcast();`
- L86 _public prototype_ `FString GetBroadcastSaveFilepath() const;`
- L89 _public prototype_ `void QueueNotifyChange(EAvaBroadcastChange InChange);` — Rather than Immediately calling the Broadcast Event change, it will queue all the multiple calls and dispatch it once to avoid redundancy
- L91 _public prototype_ `FDelegateHandle AddChangeListener(FOnAvaBroadcastChanged::FDelegate&& InDelegate);`
- L92 _public prototype_ `void RemoveChangeListener(FDelegateHandle InDelegateHandle);`
- L93 _public prototype_ `void RemoveChangeListener(FDelegateUserObjectConst InUserObject);`
- L96 _public prototype_ `int32 GetChannelNameCount() const;`
- L102 _public prototype_ `int32 GetChannelIndex(FName InChannelName) const;` — Returns the index of the channel in the channel name array. Remark: don't use this index to lookup in a profile's channel array.
- L104 _public prototype_ `FName GetChannelName(int32 ChannelIndex) const;`
- L105 _public prototype_ `FName GetOrAddChannelName(int32 ChannelIndex);`
- L112 _public prototype_ `int32 AddChannelName(FName InChannelName);` — Add the given channel name to the array of channel names. The channel name must be unique, if it already exists, the existing index is returned instead. @return the index in the array where the name was added.
- L114 _public prototype_ `void UpdateChannelNames();`
- L116 _public prototype_ `bool CanRenameChannel(FName InChannelName, FName InNewChannelName) const;`
- L117 _public prototype_ `bool CanRenameChannel(FName InChannelName, FName InNewChannelName, FText& OutErrorMessage) const;`
- L119 _public prototype_ `bool RenameChannel(FName InChannelName, FName InNewChannelName);`
- L120 _public prototype_ `bool RenameChannel(FName InChannelName, FName InNewChannelName, FText& OutErrorMessage);`
- L126 _public prototype_ `void SetChannelType(FName InChannelName, EAvaBroadcastChannelType InChannelType);` — Sets the type (ex: Program or Preview) of the given channel across all profiles. Channel type for a given channel is the same in all profiles.
- L128 _public prototype_ `EAvaBroadcastChannelType GetChannelType(FName InChannelName) const;`
- L133 _public prototype_ `void PinChannel(FName InChannelName, FName InProfileName);` — Pins the given channel from the given profile to persist across all the profiles.
- L138 _public prototype_ `void UnpinChannel(FName InChannelName);` — Unpins the given channel (if it was pinned) so that is no longer persists across all profiles.
- L140 _public function_ `bool IsChannelPinned(FName InChannelName) const`
- L145 _public prototype_ `FName GetPinnedChannelProfileName(FName InChannelName) const;` — If the given channel was pinned, returns the profile it was pinned in, returns Name_None otherwise.
- L152 _public prototype_ `void RebuildProfiles();` — Rebuilds the channel lists that might include pinned channels from other profiles. This is necessary for functions such as GetChannels(). @remark This relies on the channel names being updated (UpdateChannelNames) prior to this call.
- L154 _public function_ `FOnAvaBroadcastChannelsListChanged& GetOnChannelsListChanged()`
- L159 _protected member_ `FOnAvaBroadcastChanged OnBroadcastChanged;` — Todo: Proposal - make the events static and pass in the UAvaBroadcast that caused the event. Reason: Attempt at gradually getting rid of the global UAvaBroadcast object. Channel events are also global.
- L160 _protected member_ `FOnAvaBroadcastChannelsListChanged OnChannelsListChanged;`
- L162 _protected member_ `EAvaBroadcastChange QueuedBroadcastChanges;`
- L166 _public function_ `void SetCanShowPreview(bool bInCanShowPreview)`
- L167 _public function_ `bool CanShowPreview() const`
- L168 _public prototype_ `virtual void PostEditUndo() override;`
- L173 _protected prototype_ `FAvaBroadcastProfile& CreateProfileInternal(FName InProfileName);`
- L175 _protected prototype_ `void EnsureValidCurrentProfile();`
- L176 _protected prototype_ `void UpdateProfileNames();`
- L177 _protected prototype_ `TArray<int32> BuildChannelIndices() const;`
- L181 _protected member_ `FName CurrentProfile;` — `UPROPERTY()`
- L184 _protected member_ `TArray<FName> ChannelNames;` — `UPROPERTY()`
- L187 _protected member_ `TMap<FName, FAvaBroadcastProfile> Profiles;` — `UPROPERTY()`
- L194 _protected member_ `TMap<FName, EAvaBroadcastChannelType> ChannelTypes;` — `UPROPERTY()` — List of channels types. Backward compatibility: if not present in the map, defaults to "program" type.
- L198 _protected member_ `TMap<FName, FName> PinnedChannels;` — `UPROPERTY()` — Maps a channel name to a profile. Indicating which profile to use for a pinned channel.
- L201 _protected member_ `FString LoadedConfigFilepath;` — Full path to the last loaded config file.
- L204 _protected member_ `bool bCanShowPreview = true;`

#### Free symbols / members of external scopes

- L15 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnAvaBroadcastChanged, EAvaBroadcastChange) DECLARE_MULTICAST_DELEGATE_OneParam(FOnAvaBroadcastChannelsListChanged, const FAvaBroadcastProfile& );`
- L15 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnAvaBroadcastChanged, EAvaBroadcastChange) DECLARE_MULTICAST_DELEGATE_OneParam(FOnAvaBroadcastChannelsListChanged, const FAvaBroadcastProfile& );`
- L16 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnAvaBroadcastChannelsListChanged, const FAvaBroadcastProfile& );`
- L18 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogAvaBroadcast, Log, All);`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMedia/Public/Broadcast/AvaBroadcastDefines.h` (Public)


#### enum `EAvaBroadcastAction`  
`enum class EAvaBroadcastAction`  
_L8-15_
- reflection: `UENUM()`
- L10 _public enumerator_ `None`
- L11 _public enumerator_ `Start`
- L12 _public enumerator_ `Stop`
- L13 _public enumerator_ `UpdateConfig`
- L14 _public enumerator_ `DeleteChannel`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMedia/Public/Broadcast/AvaBroadcastLibrary.h` (Public)


#### class `UAvaBroadcastLibrary`  
`class UAvaBroadcastLibrary : public UBlueprintFunctionLibrary`  
_L10-30_
- reflection: `UCLASS(MinimalAPI, DisplayName = "Motion Design Broadcast Library", meta=(ScriptName = "MotionDesignBroadcastLibrary"))`
- inherits: `UBlueprintFunctionLibrary`
- L17 _public prototype_ `static FVector2D GetChannelViewportSize(const UObject* InWorldContextObject);` — `UFUNCTION(BlueprintCallable, Category = "Motion Design|broadcast", meta=(WorldContext = "InWorldContextObject"))` — Returns the current channel's viewport size.
- L21 _public prototype_ `static FName GetChannelName(const UObject* InWorldContextObject);` — `UFUNCTION(BlueprintCallable, Category = "Motion Design|broadcast", meta=(WorldContext = "InWorldContextObject"))` — Returns the current channel's name. Will return "None" if not running as part of the broadcast framework.
- L25 _public prototype_ `static EAvaBroadcastChannelState GetChannelStatus(const FName InChannelName);` — `UFUNCTION(BlueprintCallable, Category = "Motion Design|broadcast")` — Returns the channel status.
- L29 _public prototype_ `static EAvaBroadcastChannelType GetChannelType(const FName InChannelName);` — `UFUNCTION(BlueprintCallable, Category = "Motion Design|broadcast")` — Returns the channel type.

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMedia/Public/Broadcast/AvaBroadcastProfile.h` (Public)


#### struct `FAvaBroadcastProfile`  
`struct FAvaBroadcastProfile`  
_L11-135_
- reflection: `USTRUCT()`
- L18 _public prototype_ `static FAvaBroadcastProfile& GetNullProfile();`
- L19 _public function_ `FAvaBroadcastProfile() : FAvaBroadcastProfile(nullptr, NAME_None)`
- L20 _public prototype_ `FAvaBroadcastProfile(UAvaBroadcast* InBroadcast, FName InProfileName);`
- L22 _public prototype_ `void BeginDestroy();`
- L24 _public function_ `FName GetName() const`
- L25 _public prototype_ `UAvaBroadcast& GetBroadcast() const;`
- L27 _public prototype_ `void SetProfileName(FName InProfileName);`
- L29 _public prototype_ `static void CopyProfiles(const FAvaBroadcastProfile& InSourceProfile, FAvaBroadcastProfile& OutTargetProfile);`
- L31 _public prototype_ `bool StartChannelBroadcast();`
- L32 _public prototype_ `void StopChannelBroadcast();`
- L34 _public prototype_ `bool IsBroadcastingAnyChannel() const;`
- L35 _public prototype_ `bool IsBroadcastingAllChannels() const;`
- L37 _public prototype_ `bool IsValidProfile() const;`
- L39 _public prototype_ `void PostLoadProfile(bool bInIsProfileActive, UAvaBroadcast* InParentBroadcast);`
- L41 _public prototype_ `void UpdateChannels(bool bInIsProfileActive);`
- L46 _public prototype_ `FAvaBroadcastOutputChannel& AddChannel(FName InChannelName = NAME_None);` — Add a channel with the given name. If NAME_None, a default name is given to the channel.
- L53 _public prototype_ `bool RemoveChannel(FName InChannelName);` — @brief Removes the channel with given name. @param InChannelName Name of the channel to remove. @return true if the channel was removed, false otherwise.
- L61 _public prototype_ `int32 GetChannelIndexInProfile(FName InChannelName) const;` — Finds the corresponding index of the channel with the given name in the current array of channels (including pinned channels) for this profile. @remark This index can be used to lookup directly in the profile's channel array. @return INDEX_NONE if not found.
- L70 _public prototype_ `const FAvaBroadcastOutputChannel& GetChannel(FName InChannelName) const;` — @brief Finds the channel (including pinned channels) with the given name. @remark	Pinned channels have priority, i.e. if the profile defines a local channel of the given name, it will be overriden by the pinned channel. @param InChannelName Name of the channel to find. @return reference to requested channel or invalid channel if not found.
- L79 _public prototype_ `FAvaBroadcastOutputChannel& GetChannelMutable(FName InChannelName);` — @brief Finds the channel (including pinned channels) with the given name. @remark	Pinned channels have priority, i.e. if the profile defines a local channel of the given name, it will be overriden by the pinned channel. @param InChannelName Name of the channel to find. @return reference to requested channel or invalid channel if not found.
- L86 _public prototype_ `FAvaBroadcastOutputChannel& GetOrAddChannel(FName InChannelName);` — @brief Finds the existing channel with given name, or create it if missing. @param InChannelName Name of the channel to find or create. @return Reference to the requested or created channel.
- L88 _public function_ `const TArray<FAvaBroadcastOutputChannel*>& GetChannels() const`
- L89 _public function_ `TArray<FAvaBroadcastOutputChannel*>& GetChannels()`
- L91 _public prototype_ `UMediaOutput* AddChannelMediaOutput(FName InChannelName, const UClass* InMediaOutputClass, const FAvaBroadcastMediaOutputInfo& InOutputInfo);`
- L92 _public prototype_ `int32 RemoveChannelMediaOutputs(FName InChannelName, const TArray<UMediaOutput*>& InMediaOutputs);`
- L101 _protected prototype_ `int32 GetLocalChannelIndexInProfile(FName InChannelName) const;` — Finds the corresponding index of the channel with the given name in the current array of local channels (not including pinned channels) for this profile. @remark This index can be used to lookup directly in the profile's channel array. @return INDEX_NONE if not found.
- L108 _protected prototype_ `const FAvaBroadcastOutputChannel& GetLocalChannel(FName InChannelName) const;` — @brief Finds the local channel (not including pinned channels) with the given name. @param InChannelName Name of the channel to find. @return reference to requested channel or invalid channel if not found.
- L115 _protected prototype_ `FAvaBroadcastOutputChannel& GetLocalChannelMutable(FName InChannelName);` — @brief Finds the local channel (not including pinned channels) with the given name. @param InChannelName Name of the channel to find. @return reference to requested channel or invalid channel if not found.
- L117 _protected function_ `const TArray<FAvaBroadcastOutputChannel>& GetLocalChannels() const`
- L118 _protected function_ `TArray<FAvaBroadcastOutputChannel>& GetLocalChannels()`
- L121 _protected prototype_ `void ResolveChannels();` — Resolve pinned channels.
- L125 _protected member_ `TWeakObjectPtr<UAvaBroadcast> ParentBroadcastWeak;` — `UPROPERTY(Transient)`
- L128 _protected member_ `FName ProfileName;` — `UPROPERTY(Transient)`
- L131 _protected member_ `TArray<FAvaBroadcastOutputChannel> Channels;` — `UPROPERTY()`
- L134 _protected member_ `TArray<FAvaBroadcastOutputChannel*> ResolvedChannels;` — This array contains all resolved channels, including pinned ones from other profiles.

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMedia/Public/Broadcast/Channel/AvaBroadcastMediaOutputInfo.h` (Public)


#### struct `FAvaBroadcastMediaOutputInfo`  
`struct FAvaBroadcastMediaOutputInfo`  
_L15-59_
- reflection: `USTRUCT()`
- desc: Extra information about the Media Output object. This is used to determine the status of server hosting the device.
- L25 _public member_ `FGuid Guid;` — `UPROPERTY()` — Unique identifier for this output. Allows easier management for client/server status and configuration replication.
- L32 _public member_ `FString ServerName;` — `UPROPERTY()` — The server name if the media output was from a remote server. This will be empty if the device was local.
- L38 _public member_ `FName DeviceProviderName;` — `UPROPERTY()` — The device provider name, ex: BlackMagic, for this device (if any).
- L46 _public member_ `FName DeviceName;` — `UPROPERTY()` — Device name from the Device Provider. For device that have no provider (like NDI for instance), this is the name of the source or equivalent.
- L48 _public function_ `bool IsValid() const`
- L53 _public function_ `bool IsRemote() const`
- L55 _public prototype_ `void PostLoad();`
- L58 _public prototype_ `static bool IsRemote(const FString& InServerName);` — Determines if the given server name is considered "remote", i.e. from a different instance.

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMedia/Public/Broadcast/Channel/AvaBroadcastOutputChannel.h` (Public)


#### struct `FAvaBroadcastCapture`  
`struct FAvaBroadcastCapture`  
_L35-64_
- reflection: `USTRUCT()`
- desc: Creates a bridge between the UMediaCapture's event and our events.
- L40 _public member_ `TObjectPtr<UMediaCapture> MediaCapture = nullptr;` — `UPROPERTY()`
- L43 _public member_ `TObjectPtr<UMediaOutput> MediaOutput = nullptr;` — `UPROPERTY()`
- L48 _public member_ `TWeakObjectPtr<UTextureRenderTarget2D> RenderTarget;` — Keep track of the render target the MediaCapture is capturing. We need to do this because the UMediaCapture doesn't have a public function to know what RT it is capturing.
- L50 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnMediaCaptureStateChanged, const UMediaCapture* InMediaCapture, const UMediaOutput* InMediaOutput);`
- L51 _public member_ `FOnMediaCaptureStateChanged OnMediaCaptureStateChanged;`
- L53 _public prototype_ `FAvaBroadcastCapture() = default;`
- L54 _public function_ `~FAvaBroadcastCapture()`
- L59 _public prototype_ `void Reset(UMediaCapture* InMediaCapture = nullptr, UMediaOutput* InMediaOutput = nullptr, UTextureRenderTarget2D* InRenderTarget = nullptr);`
- L63 _private prototype_ `void OnStateChangedNative();` — Handler for MediaCapture's OnStateChangedNative event.

#### struct `FAvaBroadcastOutputChannel`  
`struct FAvaBroadcastOutputChannel`  
_L67-307_
- reflection: `USTRUCT()`
- L72 _public prototype_ `FAvaBroadcastOutputChannel() = default;`
- L73 _public prototype_ `FAvaBroadcastOutputChannel(ENoInit NoInit);`
- L76 _public prototype_ `explicit FAvaBroadcastOutputChannel(FAvaBroadcastProfile* InProfile);` — `UE_DEPRECATED(5.6, "Use constructor with profile name and broadcast.")`
- L78 _public prototype_ `explicit FAvaBroadcastOutputChannel(FName InProfileName, UAvaBroadcast* InBroadcast);`
- L79 _public prototype_ `~FAvaBroadcastOutputChannel();`
- L81 _public prototype_ `void ReleasePlaceholderResources();`
- L82 _public prototype_ `void ReleasePlaceholderRenderTargets();`
- L83 _public prototype_ `void ReleaseOutputs();`
- L85 _public prototype_ `static FAvaBroadcastOutputChannel& GetNullChannel();`
- L87 _public prototype_ `static void DuplicateChannel(const FAvaBroadcastOutputChannel& InSourceChannel, FAvaBroadcastOutputChannel& OutTargetChannel);`
- L93 _public prototype_ `void SetChannelIndex(int32 InIndex);` — Set this channel's index in the broadcast's channel names array. Remark: don't use this index to lookup directly in the profile's channel array.
- L99 _public function_ `int32 GetChannelIndex() const` — Index of this channel in the broadcast's channel names array. Remark: don't use this index to lookup directly in the profile's channel array.
- L101 _public prototype_ `FName GetChannelName() const;`
- L103 _public prototype_ `EAvaBroadcastChannelType GetChannelType() const;`
- L105 _public prototype_ `FName GetProfileName() const;`
- L107 _public prototype_ `FAvaBroadcastProfile& GetProfile() const;`
- L109 _public prototype_ `EAvaBroadcastChannelState RefreshState();`
- L111 _public function_ `EAvaBroadcastChannelState GetState() const`
- L112 _public function_ `EAvaBroadcastIssueSeverity GetIssueSeverity() const`
- L114 _public prototype_ `EAvaBroadcastIssueSeverity GetMediaOutputIssueSeverity(EAvaBroadcastOutputState InOutputState, const UMediaOutput* InMediaOutput) const;`
- L115 _public prototype_ `const TArray<FString>& GetMediaOutputIssueMessages(const UMediaOutput* InMediaOutput) const;`
- L116 _public prototype_ `EAvaBroadcastOutputState GetMediaOutputState(const UMediaOutput* InMediaOutput) const;`
- L117 _public prototype_ `const FAvaBroadcastMediaOutputInfo& GetMediaOutputInfo(const UMediaOutput* InMediaOutput) const;`
- L118 _public prototype_ `FAvaBroadcastMediaOutputInfo* GetMediaOutputInfoMutable(const UMediaOutput* InMediaOutput);`
- L120 _public prototype_ `bool IsEditingEnabled() const;`
- L123 _protected prototype_ `void SetState(EAvaBroadcastChannelState InState, EAvaBroadcastIssueSeverity InIssueSeverity);`
- L125 _protected prototype_ `void UpdatePlaceholder();`
- L126 _protected prototype_ `void UpdatePlaceholderRenderTargets();`
- L127 _protected prototype_ `void UpdateOverridePlaceholder();`
- L128 _protected prototype_ `void DrawPlaceholderWidget() const;`
- L131 _public prototype_ `bool IsValidChannel() const;`
- L133 _public prototype_ `bool StartChannelBroadcast();`
- L134 _public prototype_ `void StopChannelBroadcast();`
- L136 _public prototype_ `UMediaOutput* AddMediaOutput(const UClass* InMediaOutputClass, const FAvaBroadcastMediaOutputInfo& InOutputInfo);`
- L137 _public prototype_ `void AddMediaOutput(UMediaOutput* InMediaOutput, const FAvaBroadcastMediaOutputInfo& InOutputInfo);`
- L138 _public prototype_ `int32 RemoveMediaOutput(UMediaOutput* InMediaOutput);`
- L144 _public prototype_ `void OnMediaOutputModified(UMediaOutput* InMediaOutput);` — Called when the output is modified. Propagates the configuration change accordingly.
- L146 _public prototype_ `void SetProfileName(FName InProfileName);`
- L149 _public prototype_ `void PostLoadMediaOutputs(bool bInIsProfileActive, FAvaBroadcastProfile* InProfile);` — `UE_DEPRECATED(5.6, "Use version with profile name and broadcast.")`
- L151 _public prototype_ `void PostLoadMediaOutputs(bool bInIsProfileActive, FName InProfileName, UAvaBroadcast* InBroadcast);`
- L153 _public prototype_ `void UpdateRenderTarget(UAvaPlayableGroup* InPlayableGroup, UTextureRenderTarget2D* InRenderTarget);`
- L154 _public prototype_ `void UpdateAudioDevice(const FAudioDeviceHandle& InAudioDeviceHandle);`
- L155 _public prototype_ `UAvaPlayableGroup* GetLastActivePlayableGroup() const;`
- L157 _public prototype_ `UTextureRenderTarget2D* GetCurrentRenderTarget(bool bInFallbackToPlaceholder) const;`
- L158 _public prototype_ `UTextureRenderTarget2D* GetPlaceholderRenderTarget() const;`
- L160 _public function_ `const TArray<UMediaOutput*>& GetMediaOutputs() const`
- L163 _public prototype_ `bool HasAnyLocalMediaOutputs() const;` — Returns true if this channel has a least one local media output.
- L166 _public prototype_ `bool HasAnyRemoteMediaOutputs() const;` — Returns true if this channel has a least one remote media output.
- L169 _public prototype_ `bool IsMediaOutputRemote(const UMediaOutput* InMediaOutput) const;` — Returns true if the Media Output object is associated to a remote server.
- L172 _public prototype_ `const FString& GetMediaOutputServerName(const UMediaOutput* InMediaOutput) const;` — Returns the server name associated with the Media Output object.
- L175 _public prototype_ `TArray<UMediaOutput*> GetRemoteMediaOutputs() const;` — Returns the Media Output objects that are associated to a remote server.
- L177 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnAvaChannelChanged, const FAvaBroadcastOutputChannel&, EAvaBroadcastChannelChange);`
- L178 _public function_ `static FOnAvaChannelChanged& GetOnChannelChanged()`
- L184 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FMediaOutputStateChanged, const FAvaBroadcastOutputChannel& InChannel, const UMediaOutput* InMediaOutput);` — Called when the state of the capture changed. The callback is called on the game thread. The change may occur on the rendering thread.
- L185 _public function_ `static FMediaOutputStateChanged& GetOnMediaOutputStateChanged()`
- L189 _protected member_ `static FOnAvaChannelChanged OnChannelChanged;`
- L190 _protected member_ `static FMediaOutputStateChanged OnMediaOutputStateChanged;`
- L194 _protected prototype_ `bool IsMediaOutputCompatible(UMediaOutput* InMediaOutput, UTextureRenderTarget2D* InRenderTarget) const;`
- L195 _protected prototype_ `void UpdateViewportTarget();`
- L197 _protected prototype_ `UMediaCapture* GetMediaCaptureForOutput(const UMediaOutput* InMediaOutput) const;`
- L198 _protected prototype_ `void StopCaptureForOutput(const UMediaOutput* InMediaOutput);`
- L200 _protected prototype_ `void TickPlaceholder(float);`
- L201 _protected prototype_ `void StartPlaceholderTick();`
- L202 _protected prototype_ `void StopPlaceholderTick();`
- L204 _protected prototype_ `void OnAvaMediaCaptureStateChanged(const UMediaCapture* InMediaCapture, const UMediaOutput* InMediaOutput);`
- L214 _public prototype_ `void UpdateChannelResources(bool bInIsProfileActive);` — Updates Channel's Data and Resources. The resources are going to be allocated if the profile is active or released if not. This will also update the render targets according to the current configuration. @param bInIsProfileActive Indicate if the parent profile is active.
- L216 _public prototype_ `FIntPoint DetermineRenderTargetSize() const;`
- L217 _public prototype_ `EPixelFormat DetermineRenderTargetFormat() const;`
- L219 _public prototype_ `static FIntPoint GetDefaultMediaOutputSize(EAvaBroadcastChannelType InChannelType);`
- L220 _public prototype_ `static EPixelFormat GetDefaultMediaOutputFormat();`
- L222 _public function_ `const FAvaViewportQualitySettings& GetViewportQualitySettings() const`
- L223 _public prototype_ `void SetViewportQualitySettings(const FAvaViewportQualitySettings& InQualitySettings);`
- L229 _protected member_ `int32 ChannelIndex = INDEX_NONE;` — `UPROPERTY()` — Index of this channel in the broadcast's channel names array.
- L232 _protected member_ `TArray<TObjectPtr<UMediaOutput>> MediaOutputs;` — `UPROPERTY(Instanced)`
- L235 _protected member_ `TArray<FAvaBroadcastMediaOutputInfo> MediaOutputInfos;` — `UPROPERTY()`
- L238 _protected member_ `FAvaViewportQualitySettings QualitySettings;` — `UPROPERTY(EditAnywhere, Category = "Motion Design", meta = (HideHeader, ShowPresets))`
- L245 _protected member_ `TMap<TObjectPtr<UMediaOutput>, FAvaBroadcastCapture> MediaCaptures;` — `UPROPERTY(Transient)` — A Map of Media Outputs with their Media Captures when Broadcast Starts, and deleted when Broadcast Stops. Only succeeded Captures are added.
- L251 _protected member_ `TObjectPtr<UUserWidget> OverridePlaceholderUserWidget;` — `UPROPERTY(Transient)` — Optional UMG Widget that is used to replace the Default Placeholder Widget
- L254 _protected member_ `TObjectPtr<UTextureRenderTarget2D> PlaceholderRenderTarget;` — `UPROPERTY(Transient)`
- L258 _protected member_ `TObjectPtr<UTextureRenderTarget2D> PlaceholderRenderTargetTmp;` — `UPROPERTY(Transient)` — Extra render target to perform alpha inversion needed to mimic scene rendering.
- L262 _protected member_ `FName ProfileName;` — `UPROPERTY(Transient)` — Profile name owning this channel.
- L266 _protected member_ `TWeakObjectPtr<UAvaBroadcast> ParentBroadcastWeak;` — `UPROPERTY(Transient)` — Broadcast object owning this channel.
- L273 _protected member_ `TWeakObjectPtr<UAvaPlayableGroup> LastActivePlayableGroup;` — Last Active Playable group associated with the current render target. In the current design, there can be only one playable group associated to the currently active render target for a channel.
- L280 _protected member_ `TWeakObjectPtr<UTextureRenderTarget2D> CurrentRenderTarget;` — Keep track of the active render target associated with the current playable group. This is most likely the internal channel's "placeholder" render target, but it could also be one owned by the given playable group.
- L282 _protected member_ `TSharedPtr<SAvaBroadcastPlaceholderWidget> PlaceholderWidget;`
- L284 _protected member_ `TSharedPtr<SWidget> OverridePlaceholderWidget;`
- L286 _protected member_ `FDelegateHandle PlaceholderTickHandle;`
- L288 _protected member_ `TSharedPtr<FWidgetRenderer> WidgetRenderer;`
- L290 _protected member_ `FText ChannelNameText;`
- L292 _protected member_ `EAvaBroadcastChannelState ChannelState = EAvaBroadcastChannelState::Idle;`
- L293 _protected member_ `EAvaBroadcastIssueSeverity ChannelIssueSeverity = EAvaBroadcastIssueSeverity::None;`
- L302 _protected member_ `mutable TMap<const UMediaOutput*, FLocalMediaOutputStatus> LocalMediaOutputStatuses;`
- L304 _protected prototype_ `FString& EmplaceMessageForOutput(const UMediaOutput* InMediaOutput, EAvaBroadcastIssueSeverity InSeverity) const;`
- L305 _protected prototype_ `EAvaBroadcastIssueSeverity GetLocalSeverityForOutput(const UMediaOutput* InMediaOutput) const;`
- L306 _protected prototype_ `void ResetLocalMediaOutputStatus(const UMediaOutput* InMediaOutput);`

#### struct `FAvaBroadcastOutputChannel::FLocalMediaOutputStatus`  
`struct FLocalMediaOutputStatus`  
_L297-301_
- desc: Keep track of the media capture/output status while starting the broadcast.
- L299 _public member_ `TArray<FString> Messages;`
- L300 _public member_ `EAvaBroadcastIssueSeverity Severity = EAvaBroadcastIssueSeverity::None;`

#### Free symbols / members of external scopes

- L50 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnMediaCaptureStateChanged, const UMediaCapture* InMediaCapture, const UMediaOutput* InMediaOutput);`
- L177 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnAvaChannelChanged, const FAvaBroadcastOutputChannel&, EAvaBroadcastChannelChange);`
- L184 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FMediaOutputStateChanged, const FAvaBroadcastOutputChannel& InChannel, const UMediaOutput* InMediaOutput);` — Called when the state of the capture changed. The callback is called on the game thread. The change may occur on the rendering thread.

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMedia/Public/Broadcast/Channel/IAvaBroadcastOutputChannelViewInterface.h` (Public)


#### class `UAvaBroadcastOutputChannelViewInterface`  
`class UAvaBroadcastOutputChannelViewInterface : public UInterface`  
_L9-12_
- reflection: `UINTERFACE(MinimalAPI, Blueprintable)`
- inherits: `UInterface`

#### class `IAvaBroadcastOutputChannelViewInterface`  
`class IAvaBroadcastOutputChannelViewInterface`  
_L14-22_
- L21 _public prototype_ `void SetChannelName(const FText& InChannelName);` — `UFUNCTION(BlueprintNativeEvent, Category = "Motion Design Output Channel")`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMedia/Public/Broadcast/IAvaBroadcastSettings.h` (Public)


#### class `IAvaBroadcastSettings`  
`class IAvaBroadcastSettings`  
_L15-26_
- desc: Interface for the broadcast settings. Broadcast settings can either be local to the client, or if running on a playback server, they may be replicated from a connected remote client.
- L18 _public prototype_ `virtual const FLinearColor& GetChannelClearColor() const = 0;`
- L19 _public prototype_ `virtual EPixelFormat GetDefaultPixelFormat() const = 0;`
- L20 _public prototype_ `virtual const FIntPoint& GetDefaultResolution() const = 0;`
- L21 _public prototype_ `virtual bool IsDrawPlaceholderWidget() const = 0;`
- L22 _public prototype_ `virtual const FSoftObjectPath& GetPlaceholderWidgetClass() const = 0;`
- L25 _protected prototype_ `virtual ~IAvaBroadcastSettings() = default;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMedia/Public/Broadcast/OutputDevices/AvaBroadcastDisplayMediaOutput.h` (Public)


#### class `UAvaBroadcastDisplayMediaOutput`  
`class UAvaBroadcastDisplayMediaOutput : public UMediaOutput`  
_L14-35_
- reflection: `UCLASS(MinimalAPI, ClassGroup = "Motion Design Broadcast", meta = (DisplayName = "Motion Design Broadcast Display Media Output", MediaIOCustomLayout = "AvaDisplay"))`
- inherits: `UMediaOutput`
- desc: Output Media to a display adapter.
- L19 _public prototype_ `UAvaBroadcastDisplayMediaOutput(const FObjectInitializer& ObjectInitializer);`
- L23 _public member_ `FMediaIOOutputConfiguration OutputConfiguration;` — `UPROPERTY(EditAnywhere, Category = "AvaDisplay", meta = (DisplayName = "Configuration"))` — The device, port and video settings that correspond to the output.
- L27 _public prototype_ `virtual bool Validate(FString& FailureReason) const override;`
- L28 _public prototype_ `virtual FIntPoint GetRequestedSize() const override;`
- L29 _public prototype_ `virtual EPixelFormat GetRequestedPixelFormat() const override;`
- L30 _public prototype_ `virtual EMediaCaptureConversionOperation GetConversionOperation(EMediaCaptureSourceType InSourceType) const override;`
- L33 _protected prototype_ `virtual UMediaCapture* CreateMediaCaptureImpl() override;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMedia/Public/Broadcast/OutputDevices/IAvaBroadcastDeviceProviderProxyManager.h` (Public)


#### class `IAvaBroadcastDeviceProviderProxyManager`  
`class IAvaBroadcastDeviceProviderProxyManager`  
_L12-42_
- L15 _public prototype_ `virtual ~IAvaBroadcastDeviceProviderProxyManager() = default;`
- L17 _public prototype_ `virtual const FAvaBroadcastDeviceProviderWrapper* GetDeviceProviderWrapper(FName InDeviceProviderName) const = 0;`
- L20 _public prototype_ `virtual TArray<const IMediaIOCoreDeviceProvider*> GetDeviceProvidersForServer(const FString& InServerName) const = 0;` — Collects all the device providers related to the given server.
- L23 _public prototype_ `virtual FString FindServerNameForDevice(const FName& InDeviceProviderName, const FName& InDeviceName) const = 0;` — Finds the server name of the given device.
- L26 _public prototype_ `virtual bool IsLocalDevice(const FName& InDeviceProviderName, const FName& InDeviceName) const = 0;` — Returns true if the device can be found in a local provider.
- L29 _public prototype_ `virtual void Install(const FString& InServerName, const FAvaBroadcastDeviceProviderDataList& InDeviceProviderDataList) = 0;` — Install the given server's proxy data, installing wrappers as necessary.
- L32 _public prototype_ `virtual void Uninstall(const FString& InServerName) = 0;` — Remove the given server from all the wrappers.
- L35 _public prototype_ `virtual TSet<FString> GetServerNames() const = 0;` — Returns the set of all server names.
- L38 _public prototype_ `virtual const TSharedPtr<const FAvaBroadcastDeviceProviderDataList> GetDeviceProviderDataListForServer(const FString& InServerName) const = 0;` — Returns device provider data list (all device providers) for a specific server.
- L41 _public prototype_ `virtual FString GetLocalServerName() const = 0;` — Returns the default local server name.

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMedia/Public/IAvaMediaModule.h` (Public)


#### enum `EAvaMediaMapChangeType`  
`enum class EAvaMediaMapChangeType : uint8`  
_L29-36_
- desc: Maps one to one with the editor's map changed type (for now).
- L31 _public enumerator_ `None`
- L32 _public enumerator_ `LoadMap`
- L33 _public enumerator_ `SaveMap`
- L34 _public enumerator_ `NewMap`
- L35 _public enumerator_ `TearDownWorld`

#### class `IAvaMediaModule`  
`class IAvaMediaModule : public IModuleInterface`  
_L38-234_
- inherits: `IModuleInterface`
- L41 _public function_ `static bool IsModuleLoaded()`
- L47 _public function_ `static IAvaMediaModule& Get()`
- L56 _public prototype_ `virtual bool IsPlaybackClientStarted() const = 0;` — @brief Returns true if the playback client is started.
- L62 _public prototype_ `virtual void StartPlaybackClient() = 0;` — @brief Starts the playback client (if not already started). @remark In editor mode, this will stop the playback server.
- L67 _public prototype_ `virtual void StopPlaybackClient() = 0;` — @brief Stops the playback client.
- L72 _public prototype_ `virtual bool IsPlaybackServerStarted() const = 0;` — @brief Returns true if the playback server is started.
- L78 _public prototype_ `virtual void StartPlaybackServer(const FString& InPlaybackServerName) = 0;` — @brief Starts the playback server (if not already started). @param InPlaybackServerName Optional server name. If empty, the host (computer) name will be used.
- L83 _public prototype_ `virtual void StopPlaybackServer() = 0;` — @brief Stops the playback server.
- L85 _public prototype_ `virtual IAvaPlaybackClient& GetPlaybackClient() = 0;`
- L86 _public prototype_ `virtual IAvaPlaybackServer* GetPlaybackServer() const = 0;`
- L87 _public prototype_ `virtual const IMediaIOCoreDeviceProvider* GetDeviceProvider(FName InProviderName, const FMediaIOOutputConfiguration* InMediaIOOutputConfiguration) const = 0;`
- L88 _public prototype_ `virtual TArray<const IMediaIOCoreDeviceProvider*> GetDeviceProvidersForServer(const FString& InServerName) const = 0;`
- L89 _public prototype_ `virtual FString GetServerNameForDevice(const FName& InDeviceProviderName, const FName& InDeviceName) const = 0;`
- L90 _public prototype_ `virtual bool IsLocalDevice(const FName& InDeviceProviderName, const FName& InDeviceName) const = 0;`
- L95 _public prototype_ `virtual void LaunchGameModeLocalPlaybackServer() = 0;` — @brief Launches a separate process in game mode to run a local playback server.
- L100 _public prototype_ `virtual void StopGameModeLocalPlaybackServer() = 0;` — @brief Stops currently running game mode local playback server.
- L105 _public prototype_ `virtual bool IsGameModeLocalPlaybackServerLaunched() const = 0;` — @brief Returns true if the game mode local playback server process is launched.
- L110 _public prototype_ `virtual const IAvaBroadcastSettings& GetBroadcastSettings() const = 0;` — Access the global broadcast settings.
- L120 _public prototype_ `virtual const FAvaInstanceSettings& GetAvaInstanceSettings() const = 0;` — Access the global Motion Design instance settings. Remark: lifetime of the returned reference is not guaranteed beyond the current call context. If the settings are replicated from a client, it could get deleted if the client disconnects. If the use of the settings is deferred, the caller must make a local copy of the settings or call GetAvaInstanceSettings() in the deferred call instead.
- L126 _public prototype_ `virtual const FAvaPlayableSettings& GetPlayableSettings() const = 0;` — Access global Playable Settings. @remark These settings a replicated from connected the playback client (if connected).
- L131 _public prototype_ `virtual bool IsLocalPlaybackManagerAvailable() const = 0;` — Returns true if the local playback manager is (still) available.
- L136 _public prototype_ `virtual FAvaPlaybackManager& GetLocalPlaybackManager() const = 0;` — This is the backend for playing Motion Design assets locally.
- L141 _public prototype_ `virtual bool IsManagedInstanceCacheAvailable() const = 0;` — Returns true if the managed instance cache is (still) available.
- L146 _public prototype_ `virtual FAvaRundownManagedInstanceCache& GetManagedInstanceCache() const = 0;` — Access the "managed" Motion Design Asset Instance cache.
- L151 _public prototype_ `virtual bool IsAvaMediaSyncProviderFeatureAvailable() const = 0;` — Returns true if the AvaMediaSyncProvider modular feature is available.
- L156 _public prototype_ `virtual IAvaMediaSyncProvider* GetAvaMediaSyncProvider() const = 0;` — Access the currently used Ava Media Sync Provider.
- L161 _public prototype_ `virtual void NotifyMapChangedEvent(UWorld* InWorld, EAvaMediaMapChangeType InEventType) = 0;` — @brief Propagate a map changed event (from the level editor).
- L166 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnAvaMediaSyncProviderChanged, IAvaMediaSyncProvider* );` — Delegate called when a new IAvaMediaSyncProvider modular feature is used.
- L167 _public prototype_ `virtual FOnAvaMediaSyncProviderChanged& GetOnAvaMediaSyncProviderChanged() = 0;`
- L172 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnAvaMediaSyncPackageModified, IAvaMediaSyncProvider* , const FName& );` — Delegate called when a package has been touched by a sync operation from the given sync provider.
- L173 _public prototype_ `virtual FOnAvaMediaSyncPackageModified& GetOnAvaMediaSyncPackageModified() = 0;`
- L175 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnMapChangedEvent, UWorld* , EAvaMediaMapChangeType );`
- L176 _public prototype_ `virtual FOnMapChangedEvent& GetOnMapChangedEvent() = 0;`
- L178 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnAvaPlaybackClientStarted);`
- L179 _public prototype_ `virtual FOnAvaPlaybackClientStarted& GetOnAvaPlaybackClientStarted() = 0;`
- L181 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnAvaPlaybackClientStopped);`
- L182 _public prototype_ `virtual FOnAvaPlaybackClientStopped& GetAvaPlaybackClientStopped() = 0;`
- L184 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnAvaPlaybackServerStarted);`
- L185 _public prototype_ `virtual FOnAvaPlaybackServerStarted& GetOnAvaPlaybackServerStarted() = 0;`
- L187 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnAvaPlaybackServerStopped);`
- L188 _public prototype_ `virtual FOnAvaPlaybackServerStopped& GetAvaPlaybackServerStopped() = 0;`
- L191 _public prototype_ `DECLARE_DELEGATE_OneParam(FGetEditorViewportClient, FCommonViewportClient** );` — Use to query the current editor viewport from the corresponding editor module.
- L192 _public prototype_ `virtual FGetEditorViewportClient& GetEditorViewportClientDelegate() = 0;`
- L194 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnRundownServerEvent, TSharedPtr<IAvaRundownServer>);`
- L195 _public prototype_ `virtual FOnRundownServerEvent& GetOnRundownServerStarted() = 0;`
- L196 _public prototype_ `virtual FOnRundownServerEvent& GetOnRundownServerStopping() = 0;`
- L201 _public prototype_ `virtual bool IsRundownServerStarted() const = 0;` — @brief Returns true if the rundown server is started.
- L207 _public prototype_ `virtual void StartRundownServer(const FString& InServerName) = 0;` — @brief Starts the rundown server (if not already started). @param InServerName Optional server name. If empty, the host (computer) name will be used.
- L212 _public prototype_ `virtual void StopRundownServer() = 0;` — @brief Stops the rundown server.
- L217 _public prototype_ `virtual TSharedPtr<IAvaRundownServer> GetRundownServer() const = 0;` — @brief Returns currently running rundown server.
- L225 _public prototype_ `virtual TSharedPtr<IAvaRundownServer> MakeDetachedRundownServer(const FString& InServerName) = 0;` — Creates a rundown server that is not managed by the module. @param InServerName Optional server name. if empty, the host name will be used.d @return Created server. @remark For internal use only (testing). Detached servers will interfere with the managed one.
- L230 _public prototype_ `virtual IAvaBroadcastDeviceProviderProxyManager& GetDeviceProviderProxyManager() = 0;` — Access the device provider proxy manager.
- L233 _public prototype_ `virtual IAvaPlayableRemoteControlPresetInfoCache& GetPlayableRemoteControlPresetInfoCache() const = 0;` — Access the global remote control preset info cache.

#### Free symbols / members of external scopes

- L9 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogAvaMedia, Log, All);`
- L9 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogAvaMedia, Log, All);`
- L166 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnAvaMediaSyncProviderChanged, IAvaMediaSyncProvider* );` — Delegate called when a new IAvaMediaSyncProvider modular feature is used.
- L172 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnAvaMediaSyncPackageModified, IAvaMediaSyncProvider* , const FName& );` — Delegate called when a package has been touched by a sync operation from the given sync provider.
- L175 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnMapChangedEvent, UWorld* , EAvaMediaMapChangeType );`
- L178 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnAvaPlaybackClientStarted);`
- L181 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnAvaPlaybackClientStopped);`
- L184 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnAvaPlaybackServerStarted);`
- L187 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnAvaPlaybackServerStopped);`
- L191 _delegate_ `DECLARE_DELEGATE_OneParam(FGetEditorViewportClient, FCommonViewportClient** );` — Use to query the current editor viewport from the corresponding editor module.
- L194 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnRundownServerEvent, TSharedPtr<IAvaRundownServer>);`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMedia/Public/ModularFeature/AvaMediaSyncProviderFeatureTypes.h` (Public)


#### enum `EAvaMediaSyncResponseResult`  
`enum class EAvaMediaSyncResponseResult : uint8`  
_L8-18_
- reflection: `UENUM()`
- L11 _public enumerator_ `Error` — Indicates an Error happened
- L14 _public enumerator_ `Success` — Indicates successful completion
- L17 _public enumerator_ `Unknown` — Should not happen

#### enum `EAvaMediaSyncEngineType`  
`enum class EAvaMediaSyncEngineType : uint8`  
_L22-30_
- reflection: `UENUM()`
- desc: Engine type values for a sync connected device
- L24 _public enumerator_ `Server`
- L25 _public enumerator_ `Commandlet`
- L26 _public enumerator_ `Editor`
- L27 _public enumerator_ `Game`
- L28 _public enumerator_ `Other`
- L29 _public enumerator_ `Unknown`

#### struct `FAvaMediaSyncConnectionInfo`  
`struct FAvaMediaSyncConnectionInfo`  
_L34-70_
- reflection: `USTRUCT()`
- desc: Holds data about local project (such as Message Address Ids, Project Name, Hostname, InstanceId, etc.)
- L39 _public member_ `int32 EngineVersion = 0;` — Holds the engine version checksum
- L42 _public member_ `FGuid InstanceId;` — Holds the instance identifier
- L45 _public member_ `EAvaMediaSyncEngineType InstanceType = EAvaMediaSyncEngineType::Unknown;` — Holds the type of the engine instance
- L48 _public member_ `FGuid SessionId;` — Holds the identifier of the session that the application belongs to
- L51 _public member_ `FString HostName;` — The hostname this message was generated from
- L54 _public member_ `FString ProjectName;` — The unreal project name this message was generated from
- L57 _public member_ `FString ProjectDir;` — The unreal project directory this message was generated from
- L60 _public prototype_ `FAvaMediaSyncConnectionInfo();` — Default constructor
- L63 _public prototype_ `FString ToString() const;` — Returns debug string for this message
- L66 _public prototype_ `static FString GetBasename(const FString& InPath);` — Internal helper to return the last portion of a path, similar to the Unix basename command. Trailing directory separators are ignored
- L69 _public prototype_ `FText GetHumanReadableInstanceType() const;` — Returns user friendly instance type for display

#### struct `FAvaMediaSyncResponse`  
`struct FAvaMediaSyncResponse`  
_L74-116_
- reflection: `USTRUCT()`
- desc: Base sync response with Status and Error information
- L79 _public member_ `EAvaMediaSyncResponseResult Status = EAvaMediaSyncResponseResult::Unknown;` — Status of the response, error or success
- L82 _public member_ `FText ErrorText;` — In case of error, a localized text describing what went wrong
- L85 _public member_ `FText StatusText;` — In case of success, an optional localized text describing status of the operation
- L88 _public member_ `FAvaMediaSyncConnectionInfo ConnectionInfo;` — Holds data about local project and send to remote for it to display as result status
- L91 _public prototype_ `FAvaMediaSyncResponse() = default;` — Default constructor
- L94 _public function_ `bool IsValid() const` — Returns whether Status is in Success state
- L100 _public function_ `bool HasError() const` — Returns whether Status is in Error State and ErrorText is filled with error information
- L106 _public function_ `FString ToString() const` — Returns string representation

#### struct `FAvaMediaSyncCompareResponse`  
`struct FAvaMediaSyncCompareResponse : public FAvaMediaSyncResponse`  
_L120-140_
- reflection: `USTRUCT()`
- inherits: `FAvaMediaSyncResponse`
- desc: Payload for a comparison request
- L125 _public member_ `bool bNeedsSynchronization = false;` — Whether the two remotes have differing state
- L128 _public prototype_ `FAvaMediaSyncCompareResponse() = default;` — Default constructor
- L131 _public function_ `FString ToString() const` — Returns string representation

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMedia/Public/ModularFeature/AvaMediaSynchronizedEvent.h` (Public)


#### struct `FAvaMediaSynchronizedEvent`  
`struct FAvaMediaSynchronizedEvent`  
_L11-29_
- desc: @brief Base class for synchronized events
- L13 _public member_ `FString Signature;`
- L14 _public member_ `TUniqueFunction<void()> Function;`
- L16 _public function_ `FAvaMediaSynchronizedEvent(const FString& InSignature, TUniqueFunction<void()> InFunction) : Signature(InSignature) , Function(MoveTemp(InFunction))`
- L22 _public function_ `FAvaMediaSynchronizedEvent(FString&& InSignature, TUniqueFunction<void()> InFunction) : Signature(MoveTemp(InSignature)) , Function(MoveTemp(InFunction))`
- L28 _public prototype_ `virtual ~FAvaMediaSynchronizedEvent() = default;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMedia/Public/ModularFeature/IAvaMediaSyncProvider.h` (Public)


#### class `IAvaMediaSyncProvider`  
`class IAvaMediaSyncProvider : public IModularFeature`  
_L24-88_
- inherits: `IModularFeature`
- desc: Base Sync feature interface TODO: - Proper completion delegates handling for push and pull - Handle errors and respond with error state (with error case either from local or remote)
- L27 _public prototype_ `virtual ~IAvaMediaSyncProvider() = default;`
- L29 _public function_ `static FName GetModularFeatureName()`
- L36 _public prototype_ `static IAvaMediaSyncProvider* Get();` — Returns the first registered implementation based on GetModularFeatureName(), if there is one available
- L39 _public prototype_ `virtual FName GetName() const = 0;` — Returns underlying feature implementation name
- L47 _public prototype_ `virtual void SyncToAll(const TArray<FName>& InPackageNames) = 0;` — Broadcasts a "sync" request to all connected remotes on the local network. @param InPackageNames The list of "top level" package names (without inner dependencies / referencers) to base the synchronization on
- L58 _public prototype_ `virtual void PushToRemote(const FString& InRemoteName, const TArray<FName>& InPackageNames, const FOnAvaMediaSyncResponse& DoneDelegate = FOnAvaMediaSyncResponse()) = 0;` — Sends a "push" request to a specific remote (either a playback server or client name) The remote name can be either a playback server name or a playback client name, depending on where the request is being triggered. @param InRemoteName The playback client or server name to push to @param InPackageNames The list of "top level" package names (without inner dependencies / referencers) to send on remote @param DoneDelegate A completion delegate called when receiving a response with a `FOnAvaMediaSyncResponse` payload
- L69 _public prototype_ `virtual void PullFromRemote(const FString& InRemoteName, const TArray<FName>& InPackageNames, const FOnAvaMediaSyncResponse& DoneDelegate = FOnAvaMediaSyncResponse()) = 0;` — Sends a "pull" request to a specific remote (either a playback server or client name) The remote name can be either a playback server name or a playback client name, depending on where the request is being triggered. @param InRemoteName The playback client or server name to push to @param InPackageNames The list of "top level" package names (without inner dependencies / referencers) to send on remote @param DoneDelegate A completion delegate called when receiving a response with a `FOnAvaMediaSyncResponse` payload
- L84 _public prototype_ `virtual void CompareWithRemote(const FString& InRemoteName, const TArray<FName>& InPackageNames, const FOnAvaMediaSyncCompareResponse& DoneDelegate = FOnAvaMediaSyncCompareResponse()) = 0;` — Issue a "compare" request to a given remote, and calls back the completion delegate with status payload. The remote name can be either a playback server name or a playback client name, depending on where the request is being triggered, eg. - When local editor instance is a playback client, remote name is considered to be a server name. - When local editor instance is a playback server, remote name is considered to be a client name. - If local editor instance if both a playback client and server, remote name is considered to be a server name. @param InRemoteName The playback client or server name to compare with @param InPackageNames The list of "top level" package names (without inner dependencies / referencers) to base the comparison on @param DoneDelegate A completion delegate called when receiving a response with a `FAvaMediaSyncCompareResponse` payload
- L87 _public prototype_ `virtual FOnAvaMediaSyncPackageModified& GetOnAvaSyncPackageModified() = 0;` — Delegate called when a package is modified by a sync write operation, either being added or modified.

#### Free symbols / members of external scopes

- L9 _delegate_ `DECLARE_DELEGATE_OneParam(FOnAvaMediaSyncResponse, const TSharedPtr<FAvaMediaSyncResponse>&);` — Generic delegate response handler
- L9 _prototype_ `DECLARE_DELEGATE_OneParam(FOnAvaMediaSyncResponse, const TSharedPtr<FAvaMediaSyncResponse>&);` — Generic delegate response handler
- L12 _delegate_ `DECLARE_DELEGATE_OneParam(FOnAvaMediaSyncCompareResponse, const TSharedPtr<FAvaMediaSyncCompareResponse>&);` — Delegate with a comparison response. Payload is a FAvaMediaSyncCompareResponse shared ptr
- L12 _prototype_ `DECLARE_DELEGATE_OneParam(FOnAvaMediaSyncCompareResponse, const TSharedPtr<FAvaMediaSyncCompareResponse>&);` — Delegate with a comparison response. Payload is a FAvaMediaSyncCompareResponse shared ptr
- L15 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnAvaMediaSyncPackageModified, const FName& );` — Delegate called when a package is modified by a sync operation, either added or modified.
- L15 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnAvaMediaSyncPackageModified, const FName& );` — Delegate called when a package is modified by a sync operation, either added or modified.

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMedia/Public/ModularFeature/IAvaMediaSynchronizedEventDispatcher.h` (Public)


#### enum `EAvaMediaSynchronizedEventState`  
`enum class EAvaMediaSynchronizedEventState : uint8`  
_L8-28_
- L13 _public enumerator_ `NotFound` — The requested event signature is not tracked by the dispatcher.
- L17 _public enumerator_ `Tracked` — Has been seen on other nodes, but has not been pushed locally yet.
- L21 _public enumerator_ `Pending` — Has been pushed locally and is waiting on other nodes.
- L27 _public enumerator_ `Ready` — Has been marked from all node and will be invoke on next dispatch call. This state can only been seen on "late" dispatch implementation. Ready events should be dispatched asap and not linger in the ready queue.

#### class `IAvaMediaSynchronizedEventDispatcher`  
`class IAvaMediaSynchronizedEventDispatcher`  
_L33-54_
- desc: Queue and Dispatcher for Synchronized events.
- L41 _public prototype_ `virtual bool PushEvent(FString&& InEventSignature, TUniqueFunction<void()> InFunction) = 0;` — Push a new punctual event in the queue. @param InEventSignature unique signature for the event. @param InFunction function to invoke when the event is signaled on all nodes.
- L46 _public prototype_ `virtual EAvaMediaSynchronizedEventState GetEventState(const FString& InEventSignature) const = 0;` — Retrieve the given event state.
- L51 _public prototype_ `virtual void DispatchEvents() = 0;` — Let the implementation update and dispatch the queued events.
- L53 _public prototype_ `virtual ~IAvaMediaSynchronizedEventDispatcher() = default;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMedia/Public/ModularFeature/IAvaMediaSynchronizedEventsFeature.h` (Public)


#### class `IAvaMediaSynchronizedEventsFeature`  
`class IAvaMediaSynchronizedEventsFeature : public IModularFeature`  
_L20-63_
- inherits: `IModularFeature`
- desc: Interface for synchronized events implementation in a distributed environment such as the Display Cluster or forked channels. For a given event signature across a distributed environment, i.e. the event itself is distributed (one instance per node), the event will be fired when all nodes raise the signal for that event. In other word, the event is invoked at the same time on all nodes only when it has been raised on all nodes.
- L23 _public function_ `static FName GetModularFeatureName()`
- L30 _public prototype_ `virtual FName GetName() const = 0;` — Returns underlying feature implementation name
- L33 _public prototype_ `virtual FText GetDisplayName() const = 0;` — Returns the localized feature implementation name for display.
- L36 _public prototype_ `virtual FText GetDisplayDescription() const = 0;` — Returns the feature implementation description.
- L42 _public prototype_ `virtual int32 GetPriority() const = 0;` — Returns the feature implementation priority for automatic selection of most appropriate default. Implementations with higher priority will take precedence over lower ones.
- L45 _public function_ `static int32 GetDefaultPriority()` — Returns a default implementation priority.
- L59 _public prototype_ `virtual TSharedPtr<IAvaMediaSynchronizedEventDispatcher> CreateDispatcher(const FString& InSignature) = 0;` — Factory method to create an event dispatcher. @param InSignature signature given to the dispatcher. This should match on all clustered/forked channel. @remark Current implementation does not use the signature to automatically add scope to all pushed events. @todo Investigate the convenience of using dispatcher signature to automatically add scope to all pushed events.
- L62 _protected prototype_ `virtual ~IAvaMediaSynchronizedEventsFeature() = default;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMedia/Public/Playable/AvaPlayable.h` (Public)


#### enum `EAvaPlayableEndPlayOptions`  
`enum class EAvaPlayableEndPlayOptions : uint8`  
_L32-39_
- reflection: `UENUM()`
- desc: Option flags for the EndPlay function.
- L34 _public enumerator_ `None = 0`
- L36 _public enumerator_ `ConditionalEndPlayWorld = 1 << 0` — End play world if no more assets are playing.
- L38 _public enumerator_ `ForceImmediate = 1 << 1` — Perform the request immediately instead of waiting on the next tick.

#### enum `EAvaPlayableCommandResult`  
`enum class EAvaPlayableCommandResult : uint8`  
_L42-50_
- L45 _public enumerator_ `Executed = 0` — The command was executed successfully.
- L47 _public enumerator_ `ErrorDiscard = 1` — The command failed and should be discarded.
- L49 _public enumerator_ `KeepPending = 2` — The command couldn't be executed but should be kept and attempted again.

#### class `UAvaPlayable`  
`class UAvaPlayable : public UObject`  
_L72-213_
- reflection: `UCLASS(Abstract, NotBlueprintable, BlueprintType, ClassGroup = "Motion Design Playable", meta = (DisplayName = "Motion Design Playable"))`
- inherits: `UObject`
- desc: Base class for a Motion Design playable. A playable (a.k.a. graphic or page) is the basic element that can be rendered and controlled through the animations and remote control. Design goal: The design goal is to abstract the implementation of a playable. So far we have one concrete implementation: - Level Streaming that can be streamed with other levels in the same game instance. To support multiple playable in the same channel/output, there are 2 ways: - rendering in the same world which can only be done with the level streaming playables. - compositing different renders. This is not yet supported, but the playable abstraction should help. Distributed rendering is implemented using playable and playable group remote proxies.
- L98 _public prototype_ `static UAvaPlayable* Create(UObject* InOuter, const FPlayableCreationInfo& InPlayableInfo);` — Factory method for the playables. This will create the appropriate playable object and initialize it (calling InitPlayable). This will setup the playable group appropriately, but will not load the asset.
- L100 _public prototype_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnSequenceEvent, UAvaPlayable*, FName , EAvaPlayableSequenceEventType);`
- L101 _public function_ `static FOnSequenceEvent& OnSequenceEvent()`
- L103 _public prototype_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnTransitionEvent, UAvaPlayable*, UAvaPlayableTransition*, EAvaPlayableTransitionEventFlags);`
- L104 _public function_ `static FOnTransitionEvent& OnTransitionEvent()`
- L106 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnPlayableStatusChanged, UAvaPlayable*);`
- L107 _public function_ `FOnPlayableStatusChanged& OnPlayableStatusChanged()`
- L109 _public function_ `virtual bool LoadAsset(const FAvaSoftAssetPtr& InSourceAsset, bool bInInitiallyVisible, const FString& InLoadOptions = FString())`
- L110 _public function_ `virtual bool UnloadAsset()`
- L111 _public prototype_ `virtual const FSoftObjectPath& GetSourceAssetPath() const;`
- L112 _public function_ `virtual EAvaPlayableStatus GetPlayableStatus() const`
- L113 _public function_ `virtual IAvaSceneInterface* GetSceneInterface() const`
- L114 _public prototype_ `virtual EAvaPlayableCommandResult ExecuteAnimationCommand(EAvaPlaybackAnimAction InAnimAction, const FAvaPlaybackAnimPlaySettings& InAnimPlaySettings);`
- L115 _public prototype_ `virtual EAvaPlayableCommandResult UpdateRemoteControlCommand(const TSharedRef<FAvaPlayableRemoteControlValues>& InRemoteControlValues, EAvaPlayableRCUpdateFlags InFlags = EAvaPlayableRCUpdateFlags::None);`
- L116 _public function_ `virtual bool IsRemoteProxy() const`
- L117 _public function_ `virtual bool GetShouldBeVisible() const`
- L118 _public function_ `virtual void SetShouldBeVisible(bool bInShouldBeVisible)`
- L119 _public function_ `virtual void SetupView(FSceneViewFamily& InViewFamily, FSceneView& InView)`
- L125 _public function_ `virtual bool IsReadyToPlay() const` — Called when the playable is visible, to determine if the playable is ready to transition and be shown. Should return true when all the elements are loaded/ready after becoming visible.
- L135 _public prototype_ `void BeginPlay(const FAvaInstancePlaySettings& InWorldPlaySettings);` — @brief Ensures the given asset is playing (visible) with the given parameters. @param InWorldPlaySettings World settings (render target) to render this asset with. @remark This doesn't trigger the animations.
- L140 _public prototype_ `void EndPlay(EAvaPlayableEndPlayOptions InOptions);` — @brief Make this asset not play anymore (will end up hidden)
- L142 _public function_ `bool IsPlaying() const`
- L144 _public function_ `UAvaPlayableGroup* GetPlayableGroup() const`
- L146 _public function_ `UWorld* GetPlayWorld() const`
- L148 _public prototype_ `bool HasSequence(const UAvaSequence* InSequence) const;`
- L150 _public function_ `virtual void SetInstanceId(const FGuid& InInstanceId )`
- L151 _public function_ `const FGuid& GetInstanceId() const`
- L153 _public function_ `virtual void SetUserData(const FString& InUserData)`
- L154 _public function_ `const FString& GetUserData() const`
- L156 _public function_ `TSharedPtr<FAvaPlayableRemoteControlValues> GetLatestRemoteControlValues() const`
- L168 _protected prototype_ `virtual bool InitPlayable(const FPlayableCreationInfo& InPlayableInfo);` — @brief Performs derived initialization of the playable. Does not load the asset. @remark Playable Group is setup by the derived classes. @param InPlayableInfo Necessary information to setup the playable. @return true if the playable group and derived initialization was successful.
- L171 _protected function_ `virtual void OnPlay()` — Called by BeginPlay for derived classes implementation.
- L174 _protected function_ `virtual void OnEndPlay()` — Called by EndPlay for derived classes implementation.
- L177 _protected function_ `virtual void OnRemoteControlValuesApplied()` — Called by UpdateRemoteControlCommand for derived classes implementation.
- L179 _protected prototype_ `void HandleOnSequenceStarted(UAvaSequencePlayer* InSequencePlayer, UAvaSequence* InSequence);`
- L180 _protected prototype_ `void HandleOnSequencePaused(UAvaSequencePlayer* InSequencePlayer, UAvaSequence* InSequence);`
- L181 _protected prototype_ `void HandleOnSequenceFinished(UAvaSequencePlayer* InSequencePlayer, UAvaSequence* InSequence);`
- L183 _protected prototype_ `static UAvaPlayable* CreateLocalPlayable(UObject* InOuter, const FPlayableCreationInfo& InPlayableInfo);`
- L184 _protected prototype_ `static UAvaPlayable* CreateRemoteProxyPlayable(UObject* InOuter, const FPlayableCreationInfo& InPlayableInfo);`
- L192 _protected member_ `TObjectPtr<UAvaPlayableGroup> PlayableGroup;` — `UPROPERTY(Transient)` — Playable "instancing container" group. Defines the interface for what a playable can do to it's container.
- L194 _protected member_ `bool bIsPlaying = false;`
- L200 _protected member_ `FGuid InstanceId;` — Unique identifier for this playable instance. This is used for the playback client and server's playable replication.
- L206 _protected member_ `FString UserData;` — User data that is replicated to and from the playback server. This can be used to transport additional information for this playable.
- L208 _protected member_ `TSharedPtr<FAvaPlayableRemoteControlValues> LatestRemoteControlValues;`
- L210 _protected member_ `static FOnSequenceEvent OnSequenceEventDelegate;`
- L211 _protected member_ `static FOnTransitionEvent OnTransitionEventDelegate;`
- L212 _protected member_ `FOnPlayableStatusChanged OnPlayableStatusChangedDelegate;`

#### struct `UAvaPlayable::FPlayableCreationInfo`  
`struct FPlayableCreationInfo`  
_L81-91_
- desc: Playable creation information contains the necessary information to create an instance of a playable and it's playable group.
- L84 _public member_ `UAvaPlayableGroupManager* PlayableGroupManager = nullptr;` — Container for shared playable groups.
- L86 _public member_ `FAvaSoftAssetPtr SourceAsset;` — Information about the asset type and path.
- L88 _public member_ `FName ChannelName;` — Channel name this playable will be instanced in.
- L90 _public member_ `UAvaPlayableGroup* PlayableGroup = nullptr;` — Provided Playable Group, if not provided, the channel name will be used.

#### Free symbols / members of external scopes

- L28 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogAvaPlayable, Log, All);`
- L40 _prototype_ `ENUM_CLASS_FLAGS(EAvaPlayableEndPlayOptions);`
- L100 _delegate_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnSequenceEvent, UAvaPlayable*, FName , EAvaPlayableSequenceEventType);`
- L103 _delegate_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnTransitionEvent, UAvaPlayable*, UAvaPlayableTransition*, EAvaPlayableTransitionEventFlags);`
- L106 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnPlayableStatusChanged, UAvaPlayable*);`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMedia/Public/Playable/AvaPlayableGroup.h` (Public)


#### class `UAvaPlayableGroup`  
`class UAvaPlayableGroup : public UObject`  
_L41-253_
- reflection: `UCLASS()`
- inherits: `UObject`
- desc: This class defines the interface and base of a playable group. A playable group is intended to group playables according to the underlying rendering implementation. In most cases, it corresponds to a game instance, either owned or not, local to the process or remote. It tracks and manage the playables state, transitions and visibility constraints. The design goal of this class is to allow hooking the playable framework to any game instance, including PIE so it can work with any work flow (editor, PIE, game, nDisplay, etc). Ideally, the playable class itself should be "game instance" agnostic and do all it's bidding on it's container through this class.
- L66 _public prototype_ `static UAvaPlayableGroup* MakePlayableGroup(UObject* InOuter, const FPlayableGroupCreationInfo& InPlayableGroupInfo);`
- L69 _public prototype_ `void RegisterPlayable(UAvaPlayable* InPlayable);` — Register a playable to this group when it is created.
- L72 _public prototype_ `void UnregisterPlayable(UAvaPlayable* InPlayable);` — Unregister a playable when it is about to be deleted.
- L75 _public prototype_ `bool HasPlayables() const;` — Returns true if there are any valid registered playables.
- L78 _public prototype_ `bool HasPlayingPlayables() const;` — Returns true if there are any valid registered playables that are currently playing.
- L81 _public prototype_ `void FindPlayablesBySourceAssetPath(const FSoftObjectPath& InSourceAssetPath, TArray<UAvaPlayable*>& OutFoundPlayables) const;` — Finds all the playables that are instances of the given source asset.
- L83 _public prototype_ `void RegisterPlayableTransition(UAvaPlayableTransition* InPlayableTransition);`
- L85 _public prototype_ `void UnregisterPlayableTransition(UAvaPlayableTransition* InPlayableTransition);`
- L88 _public prototype_ `void TickTransitions(double InDeltaSeconds);` — Tick transitions that have been registered. Returns the number of transitions that where ticked.
- L90 _public prototype_ `bool HasTransitions() const;`
- L92 _public prototype_ `void PushSynchronizedEvent(FString&& InEventSignature, TUniqueFunction<void()> InFunction);`
- L94 _public prototype_ `bool IsSynchronizedEventPushed(const FString& InEventSignature) const;`
- L100 _public function_ `virtual bool ConditionalCreateWorld()` — Creates the game instance's world if it wasn't already. @return true if the world was created. false if nothing was done.
- L106 _public function_ `virtual bool ConditionalBeginPlay(const FAvaInstancePlaySettings& InWorldPlaySettings)` — Begin playing the game instance's world if it wasn't already. @return true if the BeginPlay was done (i.e. on the state transition only), false otherwise.
- L108 _public function_ `virtual void RequestEndPlayWorld(bool bInForceImmediate)`
- L111 _public prototype_ `void SetLastAppliedCameraPlayable(UAvaPlayable* InPlayable);` — Keep track of the last playable that applied it's camera in the viewport/controller.
- L113 _public function_ `virtual bool IsWorldPlaying() const`
- L115 _public function_ `virtual bool IsRenderTargetReady() const`
- L120 _public prototype_ `virtual UTextureRenderTarget2D* GetRenderTarget() const;` — Current logic for the render target: use the game instance's if present, fallback to internal one if not.
- L125 _public prototype_ `virtual UTextureRenderTarget2D* GetManagedRenderTarget() const;` — Returns the currently managed render target.
- L135 _public prototype_ `virtual void SetManagedRenderTarget(UTextureRenderTarget2D* InManageRenderTarget);` — The playback graph determines if this playable group will render in a broadcast channel's render target or an offscreen one. In the later case, the playable group keeps track of that render target. @remark The playable group does not automatically render in the current "managed" render target. The render target this group will render into is determined by the arguments of ConditionalBeginPlay.
- L140 _public function_ `UGameInstance* GetGameInstance() const` — Returns this group's game instance, if it has one.
- L145 _public prototype_ `virtual UWorld* GetPlayWorld() const;` — Returns this group's play world, if it has one.
- L150 _public prototype_ `FName GetChannelName() const;` — Returns the broadcast channel name this playable group is part of.
- L156 _public function_ `virtual bool ConditionalRequestUnloadWorld(bool bForceImmediate)` — Unloads the game instance's world if no more playables are loaded. @return true if the world was unloaded. false if nothing was done.
- L162 _public prototype_ `void NotifyLevelStreaming(UAvaPlayable* InPlayable);` — @brief Notify the playable group that a playable is loading an asset. @param InPlayable Source of the event.
- L164 _public function_ `UAvaPlayableGroupManager* GetPlayableGroupManager() const`
- L166 _public prototype_ `void RegisterVisibilityConstraint(const TWeakInterfacePtr<IAvaPlayableVisibilityConstraint>& InVisibilityConstraint);`
- L167 _public prototype_ `void UnregisterVisibilityConstraint(const IAvaPlayableVisibilityConstraint* InVisibilityConstraint);`
- L169 _public prototype_ `void RequestSetVisibility(UAvaPlayable* InPlayable, bool bInShouldBeVisible);`
- L171 _public prototype_ `virtual void SetupView(FSceneViewFamily& InViewFamily, FSceneView& InView);`
- L173 _public prototype_ `void ForEachPlayable(TFunctionRef<bool(UAvaPlayable*)> InFunction);`
- L175 _public prototype_ `void ForEachPlayableTransition(TFunctionRef<bool(UAvaPlayableTransition*)> InFunction);`
- L182 _public prototype_ `static UAvaPlayableGroup* FindPlayableGroupForWorld(const UWorld* InWorld, bool bInFallbackToGlobalSearch = true);` — Search for the first playable group associated to the given world. @param InWorld	Play world to search the playable group of. @param bInFallbackToGlobalSearch If the direct link from world to the playable group is not found, fallback to a global search of the whole system.
- L185 _protected prototype_ `bool IsVisibilityConstrained(const UAvaPlayable* InPlayable) const;`
- L187 _protected prototype_ `void OnPlayableStatusChanged(UAvaPlayable* InPlayable);`
- L189 _protected prototype_ `void ConditionalRegisterWorldDelegates(UWorld* InWorld);`
- L190 _protected prototype_ `void UnregisterWorldDelegates(UWorld* InWorld);`
- L192 _protected prototype_ `bool DisplayLoadedAssets(FText& OutText, FLinearColor& OutColor);`
- L193 _protected prototype_ `bool DisplayPlayingAssets(FText& OutText, FLinearColor& OutColor);`
- L194 _protected prototype_ `bool DisplayTransitions(FText& OutText, FLinearColor& OutColor);`
- L196 _protected prototype_ `void HidePawnsForView(const UWorld* InPlayWorld, FSceneView& InView) const;`
- L203 _protected member_ `TObjectPtr<UTextureRenderTarget2D> ManagedRenderTarget;` — `UPROPERTY(Transient)` — Managed Render Target for this playable group.
- L206 _protected member_ `TObjectPtr<UGameInstance> GameInstance;` — `UPROPERTY(Transient)`
- L209 _protected member_ `FName ChannelName;` — Broadcast channel name this playable group is part of.
- L212 _protected member_ `TWeakObjectPtr<UAvaPlayableGroupManager> ParentPlayableGroupManagerWeak;` — PlayableGroup Manager handling this playable group.
- L215 _protected member_ `TSet<TObjectKey<UAvaPlayable>> Playables;` — List of playables for this group.
- L218 _protected member_ `TWeakObjectPtr<UAvaPlayable> LastAppliedCameraPlayableWeak;` — Last playable that applied a camera.
- L221 _protected member_ `TSet<TObjectKey<UAvaPlayableTransition>> PlayableTransitions;` — Set of registered playable transitions for this group. Remark: used for ticking.
- L224 _protected member_ `bool bIsTickingTransitions = false;` — If transitions are added or removed while ticking, we need to protect transition iterator.
- L227 _protected member_ `TSet<TObjectKey<UAvaPlayableTransition>> PlayableTransitionsToRemove;` — Set of transitions to remove accumulated during transition ticking.
- L230 _protected member_ `TSet<TObjectKey<UAvaPlayableTransition>> PlayableTransitionsToAdd;` — Set of transitions to add accumulated during transition ticking.
- L237 _protected member_ `TWeakObjectPtr<UWorld> LastWorldBoundToDisplayDelegates;` — Since the UViewportStatsSubsystem delegation mechanism does not allow us to verify if it is bound to this world or another one. We need this auxiliary binding tracking to compensate.
- L240 _protected member_ `TArray<int32> DisplayDelegateIndices;` — UViewportStatsSubsystem display delegate indices.
- L250 _protected member_ `TArray<FVisibilityRequest> VisibilityRequests;`
- L252 _protected member_ `TArray<TWeakInterfacePtr<IAvaPlayableVisibilityConstraint>> VisibilityConstraints;`

#### struct `UAvaPlayableGroup::FPlayableGroupCreationInfo`  
`struct FPlayableGroupCreationInfo`  
_L50-64_
- desc: PlayableGroup creation information contains the necessary information to create an instance of a playable group.
- L53 _public member_ `UAvaPlayableGroupManager* PlayableGroupManager = nullptr;` — Container for shared playable groups.
- L55 _public member_ `FSoftObjectPath SourceAssetPath;` — Source asset path.
- L57 _public member_ `FName ChannelName;` — Channel name this playable will be instanced in.
- L59 _public member_ `bool bIsRemoteProxy = false;` — Indicate if the group is for remote proxy playables.
- L61 _public member_ `bool bIsSharedGroup = false;` — Indicate if the group is shared for multiple playables. If so, it will be registered in the given playable group manager.
- L63 _public member_ `UGameInstance* GameInstance = nullptr;` — Existing Game Instance. In this case, the playable group will not own the game instance.

#### struct `UAvaPlayableGroup::FVisibilityRequest`  
`struct FVisibilityRequest`  
_L242-248_
- L244 _public member_ `TWeakObjectPtr<UAvaPlayable> PlayableWeak;`
- L245 _public member_ `bool bShouldBeVisible;`
- L247 _public prototype_ `void Execute(const UAvaPlayableGroup* InPlayableGroup) const;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMedia/Public/Playable/AvaPlayableLibrary.h` (Public)


#### class `UAvaPlayableLibrary`  
`class UAvaPlayableLibrary : public UBlueprintFunctionLibrary`  
_L12-59_
- reflection: `UCLASS(MinimalAPI, DisplayName = "Motion Design Playable Library", meta=(ScriptName = "MotionDesignPlayableLibrary"))`
- inherits: `UBlueprintFunctionLibrary`
- L18 _public prototype_ `static UAvaPlayable* GetPlayable(const UObject* InWorldContextObject);` — Returns the playable corresponding to that world object.
- L21 _public prototype_ `static UAvaPlayableTransition* GetPlayableTransition(const UAvaPlayable* InPlayable);` — Returns the transition this playable is part of.
- L30 _public prototype_ `static bool UpdatePlayableRemoteControlValues(const UObject* InWorldContextObject);` — `UFUNCTION(BlueprintCallable, Category = "Motion Design|Playable", meta=(WorldContext = "InWorldContextObject"))` — Injects the remote control values from current transition for the current playable. @remark This does nothing if there is no current transition the current playable is part of or if the current level is not managed by a playable. @return true if the values have been injected, false otherwise.
- L38 _public prototype_ `static bool IsPlayableHidden(const UObject* InWorldContextObject);` — `UFUNCTION(BlueprintCallable, Category = "Motion Design|Playable", meta=(WorldContext = "InWorldContextObject"))` — Returns the current hidden state of this playable. @remark This only works if current level is managed by a playable (i.e. in a rundown or playback graph). @return true if the hidden state is set, false otherwise or if not managed by a playable.
- L46 _public prototype_ `static bool SetPlayableHidden(const UObject* InWorldContextObject, bool bInShouldBeHidden);` — `UFUNCTION(BlueprintCallable, Category = "Motion Design|Playable", meta=(WorldContext = "InWorldContextObject"))` — Sets the hidden state of all primitives under this playable. Hidden primitives will not be rendered. @remark This only works if current level is managed by a playable (i.e. in a rundown or playback graph). @return true if the value was set, false otherwise (if not managed by a playable).
- L58 _public prototype_ `static void PlayableSyncEventLatent(const UObject* InWorldContextObject, FLatentActionInfo InLatentInfo, const FString& InEventSignature, bool& bInSuccess);` — `UFUNCTION(BlueprintCallable, Category = "Motion Design|Playable", meta=(Latent, LatentInfo="InLatentInfo", WorldContext="InWorldContextObject"))` — Push a playable sync event with the given signature on the cluster. The action will complete when the event has occured on all nodes of the cluster. The event signature includes the playable id as well. Therefore, the given signature need only be unique in terms of any sequence of synchronized events for the given playable. @param InEventSignature Event signature, must be unique in terms of sequence of events for the given playable. @param bInSuccess If true upon completion, the event has been synchronized successfully.

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMedia/Public/Playable/AvaPlayableRemoteControlPresetInfo.h` (Public)


#### struct `FAvaPlayableRemoteControlControlledEntityInfo`  
`struct FAvaPlayableRemoteControlControlledEntityInfo`  
_L15-22_
- reflection: `USTRUCT()`
- desc: Container for the controlled entities extra information.
- L21 _public member_ `TArray<FGuid> ControlledBy;` — `UPROPERTY()` — Controller ids that are controlling the entity.

#### struct `FAvaPlayableRemoteControlPresetInfo`  
`struct FAvaPlayableRemoteControlPresetInfo`  
_L28-84_
- reflection: `USTRUCT()`
- desc: Container for the remote control preset extra information used for playable.
- L32 _public prototype_ `FAvaPlayableRemoteControlPresetInfo() = default;`
- L38 _public prototype_ `void Refresh(const URemoteControlPreset* InRemoteControlPreset);` — Refreshes from given remote control preset. @remark will reset bDirty flag.
- L44 _public function_ `void MarkDirty()` — Call this whenever the source RCP is modified (or is likely to be) to invalidate the information and trigger a refresh on the next access.
- L50 _public function_ `bool IsDirty() const` — Indicates if the data needs to be refreshed.
- L60 _public function_ `bool IsControllerOverlapping(const FGuid& InControllerId) const` — Returns true if the given controller is considered "overlapping", i.e. it's set of controlled entities overlap with other controllers. An overlapping controller can't safely be updating its behaviors when the end result needs to be deterministic.
- L67 _public member_ `FGuid PresetId;` — `UPROPERTY()` — Id of the RemoteControlPreset
- L71 _public member_ `TMap<FGuid, FAvaPlayableRemoteControlControlledEntityInfo> EntitiesControlledByController;` — `UPROPERTY()` — Contains a set of entity guids that are bound to a controller action.
- L79 _public member_ `TSet<FGuid> OverlappingControllers;` — `UPROPERTY()` — Contains a set of controllers that are "overlapping". The term "overlapping controllers" defines the scenario where multiple controllers influence a shared subset of controlled entities.
- L83 _protected member_ `bool bDirty = true;` — When the source asset is modified (or likely to be), we mark as dirty to trigger a refresh on next access.

#### class `IAvaPlayableRemoteControlPresetInfoCache`  
`class IAvaPlayableRemoteControlPresetInfoCache`  
_L89-112_
- desc: Global Cache for remote control preset info
- L92 _public prototype_ `static IAvaPlayableRemoteControlPresetInfoCache& Get();`
- L98 _public prototype_ `virtual TSharedPtr<FAvaPlayableRemoteControlPresetInfo> GetRemoteControlPresetInfo(const FSoftObjectPath& InAssetPath, const URemoteControlPreset* InRemoteControlPreset) = 0;` — Request the RCP info cached for the given asset path. If not available, will be created from the given RCP.
- L103 _public prototype_ `virtual void Flush(const FSoftObjectPath& InAssetPath) = 0;` — Flush specified entry from the cache.
- L108 _public prototype_ `virtual void Flush() = 0;` — Flush all unused entries from the cache.
- L111 _protected prototype_ `virtual ~IAvaPlayableRemoteControlPresetInfoCache() = default;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMedia/Public/Playable/AvaPlayableRemoteControlValues.h` (Public)


#### enum `EAvaPlayableRemoteControlChanges`  
`enum class EAvaPlayableRemoteControlChanges : uint8`  
_L14-21_
- reflection: `UENUM()`
- desc: Flags indicating which component of the remote control values have been modified by an operation.
- L16 _public enumerator_ `None = 0`
- L17 _public enumerator_ `EntityValues = 1 << 0`
- L18 _public enumerator_ `ControllerValues = 1 << 1`
- L20 _public enumerator_ `All = 0xFF`

#### struct `FAvaPlayableRemoteControlValue`  
`struct FAvaPlayableRemoteControlValue`  
_L25-62_
- reflection: `USTRUCT()`
- L29 _public prototype_ `FAvaPlayableRemoteControlValue() = default;`
- L31 _public function_ `FAvaPlayableRemoteControlValue(const FString& InValue, bool bInIsDefault = false) : Value(InValue), bIsDefault(bInIsDefault)`
- L34 _public function_ `void SetValueFrom(const FAvaPlayableRemoteControlValue& InOther)`
- L40 _public function_ `bool IsSameValueAs(const FAvaPlayableRemoteControlValue& InOther) const` — Returns true if the given value is the same. Ignores the default flag.
- L45 _public prototype_ `bool Serialize(FArchive& Ar);`
- L51 _public member_ `FString Value;` — `UPROPERTY()` — The Remote Control Entity or Controller's Value stored as a Json formatted string.
- L61 _public member_ `bool bIsDefault = false;` — `UPROPERTY()` — Indicate if the value is a default value from a template. This is used to know which values to update when updating the page's values from the template (reimport page). This is set to true only when the values are from the template. If values are modified by an edit operation, it will be set to false.

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FAvaPlayableRemoteControlValue> : public TStructOpsTypeTraitsBase2<FAvaPlayableRemoteControlValue>`  
_L65-71_
- inherits: `TStructOpsTypeTraitsBase2<FAvaPlayableRemoteControlValue>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L68-70_

#### struct `FAvaPlayableRemoteControlValues`  
`struct FAvaPlayableRemoteControlValues`  
_L75-208_
- reflection: `USTRUCT()`
- desc: Container for the remote control values of a playable.
- L79 _public prototype_ `FAvaPlayableRemoteControlValues() = default;`
- L83 _public member_ `TMap<FGuid, FAvaPlayableRemoteControlValue> EntityValues;` — `UPROPERTY()` — Value as a binary array of the Remote Control Entity.
- L87 _public member_ `TMap<FGuid, FAvaPlayableRemoteControlValue> ControllerValues;` — `UPROPERTY()` — Controller values.
- L90 _public prototype_ `void CopyFrom(const URemoteControlPreset* InRemoteControlPreset, bool bInIsDefault);` — Copies the values (properties and controllers) from the given RemoteControlPreset.
- L96 _public prototype_ `bool HasSameEntityValues(const FAvaPlayableRemoteControlValues& InOther) const;` — Compares the remote control EntityValues with another instance @return true if the other instance has the exact same EntityValues (count and value), false otherwise
- L102 _public prototype_ `bool HasSameControllerValues(const FAvaPlayableRemoteControlValues& InOther) const;` — Compares the remote control ControllerValues with another instance @return true if the other instance has the exact same ControllerValues (count and value), false otherwise
- L108 _public prototype_ `EAvaPlayableRemoteControlChanges PruneRemoteControlValues(const FAvaPlayableRemoteControlValues& InReferenceValues);` — Removes the extra values compared to the given reference values. @return flags indicating what changed.
- L118 _public prototype_ `EAvaPlayableRemoteControlChanges UpdateRemoteControlValues(const FAvaPlayableRemoteControlValues& InReferenceValues, bool bInUpdateDefaults);` — Update the property/controller values (i.e. add missing, remove extras) from the given reference values. If bInUpdateDefaults is true, the existing values flagged as "default" will be updated, i.e. the reference values will be applied. Otherwise, the existing values are not modified. Also, when adding the missing values from reference default values, the default flag is also set in the destination value. For a full copy of all properties and controllers, use CopyFrom instead. @return flags indicating what changed.
- L126 _public prototype_ `EAvaPlayableRemoteControlChanges ResetRemoteControlValues(const FAvaPlayableRemoteControlValues& InReferenceValues, bool bInIsDefaults);` — Reset the values to the reference. @param InReferenceValues Values to be reset to. @param bInIsDefaults If true, consider all values as "default". Otherwise, preserves the "default" status from reference. @return
- L134 _public prototype_ `EAvaPlayableRemoteControlChanges ResetRemoteControlControllerValue(const FGuid& InId , const FAvaPlayableRemoteControlValue& InReferenceValue, bool bInIsDefaults);` — Reset the controller value to the reference. @param InReferenceValue Value to be reset to. @param bInIsDefaults If true, consider all values as "default". Otherwise, preserves the "default" status from reference. @return
- L143 _public prototype_ `EAvaPlayableRemoteControlChanges ResetRemoteControlEntityValue(const FGuid& InId , const FAvaPlayableRemoteControlValue& InReferenceValue, bool bInIsDefaults);` — Reset the entity value to the reference. @param InReferenceValue Value to be reset to. @param bInIsDefaults If true, consider all values as "default". Otherwise, preserves the "default" status from reference. @return
- L150 _public prototype_ `bool SetEntityValue(const FGuid& InId, const URemoteControlPreset* InRemoteControlPreset, bool bInIsDefault);` — Set the entity value from the given preset. @return true if the value was set.
- L151 _public function_ `bool HasEntityValue(const FGuid& InId) const`
- L152 _public function_ `const FAvaPlayableRemoteControlValue* GetEntityValue(const FGuid& InId) const`
- L153 _public function_ `void SetEntityValue(const FGuid& InId, const FAvaPlayableRemoteControlValue& InValue)`
- L155 _public prototype_ `bool SetControllerValue(const FGuid& InId, const URemoteControlPreset* InRemoteControlPreset, bool bInIsDefault);`
- L156 _public function_ `bool HasControllerValue(const FGuid& InId) const`
- L157 _public function_ `const FAvaPlayableRemoteControlValue* GetControllerValue(const FGuid& InId) const`
- L158 _public function_ `void SetControllerValue(const FGuid& InId, const FAvaPlayableRemoteControlValue& InValue)`
- L165 _public prototype_ `void ApplyEntityValuesToRemoteControlPreset(URemoteControlPreset* InRemoteControlPreset, const TSet<FGuid>& InSkipEntities = TSet<FGuid>()) const;` — Apply the entity values to the given remote control preset. @param InRemoteControlPreset RemoteControlPreset @param InSkipEntities set of entities to skip (will not be updated)
- L171 _public prototype_ `void ApplyControllerValuesToRemoteControlPreset(URemoteControlPreset* InRemoteControlPreset, bool bInForceDisableBehaviors = false) const;` — Apply the controller values to the given remote control preset. Remark: controller actions are executed by this operation.
- L177 _public prototype_ `bool HasIdCollisions(const FAvaPlayableRemoteControlValues& InOtherValues) const;` — Return true if there are key collisions with the other set of values.
- L184 _public prototype_ `bool Merge(const FAvaPlayableRemoteControlValues& InOtherValues);` — @brief Merge the other values with current ones, combining the keys. @param InOtherValues Other values to merge with. @return true if the merge was clean with no collisions. false indicate there was some key collisions and information is lost.
- L187 _public prototype_ `static bool HasIdCollisions(const TMap<FGuid, FAvaPlayableRemoteControlValue>& InValues, const TMap<FGuid, FAvaPlayableRemoteControlValue>& InOtherValues);` — Returns true if the given maps have id collisions.
- L189 _public prototype_ `static const FAvaPlayableRemoteControlValues& GetDefaultEmpty();`
- L194 _public prototype_ `static void CollectReferencedAssetPaths(const TMap<FGuid, FAvaPlayableRemoteControlValue>& InValues,TSet<FSoftObjectPath>& OutReferencedPaths);` — Collect the referenced asset paths from the given values.
- L201 _public prototype_ `static bool ShouldIgnoreController(const URCVirtualPropertyBase* InController);` — Utility function to determine if a controller should be ignored by the playable management layer. @param InController Controller @return true if the controller should be ignored.
- L207 _public prototype_ `static bool IsRuntimeEventController(const URCVirtualPropertyBase* InController);` — Utility function to determine if a controller is considered an "event" controller, i.e. it doesn't carry a value to be used to set or restore state, but rather is runtime event based.

#### Free symbols / members of external scopes

- L22 _prototype_ `ENUM_CLASS_FLAGS(EAvaPlayableRemoteControlChanges);`
- L69 _enumerator_ `WithSerializer = true` (scope `TStructOpsTypeTraits::__anond6feff840103`)

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMedia/Public/Playable/AvaPlayableSettings.h` (Public)


#### struct `FAvaSynchronizedEventsFeatureSelection`  
`struct FAvaSynchronizedEventsFeatureSelection`  
_L8-18_
- reflection: `USTRUCT()`
- L17 _public member_ `FString Implementation;` — `UPROPERTY(Config, EditAnywhere, Category = Settings)` — Select the implementation for synchronizing events. "Default" will select the most appropriate implementation available.

#### struct `FAvaPlayableSettings`  
`struct FAvaPlayableSettings`  
_L24-46_
- reflection: `USTRUCT()`
- desc: Settings applied when instancing a Motion Design Playable.
- L32 _public member_ `FAvaSynchronizedEventsFeatureSelection SynchronizedEventsFeature;` — `UPROPERTY(Config, EditAnywhere, Category = Settings)` — Select the implementation for synchronizing events.
- L38 _public member_ `bool bHidePawnActors = true;` — `UPROPERTY(Config, EditAnywhere, Category = Settings)` — Automatically hide pawn actor in playables.
- L45 _public member_ `TArray<FString> IgnoredControllerPostfix;` — `UPROPERTY(Config, EditAnywhere, Category = Settings)` — List of postfix that can be added to controllers to be ignored by playable, playback and rundown implementation. Those controllers can be used by other control systems at runtime.

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMedia/Public/Playable/IAvaPlayableVisibilityConstraint.h` (Public)


#### class `UAvaPlayableVisibilityConstraint`  
`class UAvaPlayableVisibilityConstraint : public UInterface`  
_L14-17_
- reflection: `UINTERFACE(MinimalAPI, meta = (CannotImplementInterfaceInBlueprint))`
- inherits: `UInterface`
- desc: Interface for the Playable visibility constraint.

#### class `IAvaPlayableVisibilityConstraint`  
`class IAvaPlayableVisibilityConstraint`  
_L19-33_
- L32 _public prototype_ `virtual bool IsVisibilityConstrained(const UAvaPlayable* InPlayable) const = 0;` — @brief Verify if a visibility constraint apply to the given playable. @param InPlayable Playable to evaluate visibility constraint for. @return true if the playable's visibility is constrained, false otherwise. If the visibility is constrained, it means it has to wait for something else to be ready and therefore can't be made visible just yet.

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMedia/Public/Playable/Transition/AvaPlayableTransition.h` (Public)


#### enum `EAvaPlayableTransitionEntryRole`  
`enum class EAvaPlayableTransitionEntryRole : uint8`  
_L17-25_
- desc: @brief Defines the playable entry role in the transition.
- L20 _public enumerator_ `Enter` — The playable corresponding to this entry is a entering the scene.
- L22 _public enumerator_ `Playing` — The playable corresponding to this entry is already in the scene and may react to the transition, but is otherwise neutral.
- L24 _public enumerator_ `Exit` — The playable corresponding to this entry is already in the scene but is commanded to exit.

#### class `UAvaPlayableTransition`  
`class UAvaPlayableTransition : public UObject`  
_L28-88_
- reflection: `UCLASS()`
- inherits: `UObject`
- L33 _public prototype_ `virtual bool Start();`
- L34 _public prototype_ `virtual void Stop();`
- L35 _public function_ `virtual bool IsRunning() const`
- L36 _public function_ `virtual void Tick(double InDeltaSeconds)`
- L38 _public prototype_ `void SetTransitionId(const FGuid& InTransitionId);`
- L39 _public prototype_ `void SetTransitionFlags(EAvaPlayableTransitionFlags InFlags);`
- L40 _public prototype_ `void SetEnterPlayables(TArray<TWeakObjectPtr<UAvaPlayable>>&& InPlayablesWeak);`
- L41 _public prototype_ `void SetPlayingPlayables(TArray<TWeakObjectPtr<UAvaPlayable>>&& InPlayablesWeak);`
- L42 _public prototype_ `void SetExitPlayables(TArray<TWeakObjectPtr<UAvaPlayable>>&& InPlayablesWeak);`
- L44 _public prototype_ `bool IsEnterPlayable(const UAvaPlayable* InPlayable) const;`
- L45 _public prototype_ `bool IsPlayingPlayable(const UAvaPlayable* InPlayable) const;`
- L46 _public prototype_ `bool IsExitPlayable(const UAvaPlayable* InPlayable) const;`
- L48 _public prototype_ `void SetEnterPlayableValues(TArray<TSharedPtr<FAvaPlayableRemoteControlValues>>&& InPlayableValues);`
- L56 _public prototype_ `TSharedPtr<FAvaPlayableRemoteControlValues> GetValuesForPlayable(const UAvaPlayable* InPlayable, bool bInIsEnterPlayable);` — Finds the stored values for a given playable @param InPlayable the playable to look for @param bInIsEnterPlayable whether to look for the Enter Playable Values @return the remote control values for the playable if found. null otherwise
- L59 _public prototype_ `void MarkPlayableAsDiscard(UAvaPlayable* InPlayable);` — This is called during the transition evaluation to indicate discarded playables.
- L62 _public prototype_ `virtual FString GetPrettyInfo() const;` — Returns information on this transition suitable for logging.
- L64 _public function_ `EAvaPlayableTransitionFlags GetTransitionFlags() const`
- L66 _public function_ `const FGuid& GetTransitionId() const`
- L69 _protected prototype_ `UAvaPlayable* FindPlayable(const FGuid& InstanceId) const;`
- L72 _protected member_ `FGuid TransitionId;`
- L73 _protected member_ `EAvaPlayableTransitionFlags TransitionFlags = EAvaPlayableTransitionFlags::None;`
- L75 _protected member_ `TArray<TSharedPtr<FAvaPlayableRemoteControlValues>> EnterPlayableValues;`
- L78 _protected member_ `TMap<TObjectKey<UAvaPlayable>, TSharedPtr<FAvaPlayableRemoteControlValues>> OtherPlayableValues;` — Other Playable Values that are not the Enter Playable's (i.e. Exiting or Playing Playable Values)
- L80 _protected member_ `TArray<TWeakObjectPtr<UAvaPlayable>> EnterPlayablesWeak;`
- L81 _protected member_ `TArray<TWeakObjectPtr<UAvaPlayable>> PlayingPlayablesWeak;`
- L82 _protected member_ `TArray<TWeakObjectPtr<UAvaPlayable>> ExitPlayablesWeak;`
- L85 _protected member_ `TArray<TWeakObjectPtr<UAvaPlayable>> DiscardPlayablesWeak;` — Keep track of the discarded playables so events can be sent when the transition ends.
- L87 _protected member_ `TSet<TWeakObjectPtr<UAvaPlayableGroup>> PlayableGroupsWeak;`

#### class `FAvaPlayableTransitionBuilder`  
`class FAvaPlayableTransitionBuilder`  
_L90-123_
- L93 _public prototype_ `FAvaPlayableTransitionBuilder();`
- L95 _public prototype_ `void AddEnterPlayableValues(const TSharedPtr<FAvaPlayableRemoteControlValues>& InValues);`
- L97 _public prototype_ `bool AddEnterPlayable(UAvaPlayable* InPlayable, bool bInAllowMultipleAdd = false);`
- L98 _public prototype_ `bool AddPlayingPlayable(UAvaPlayable* InPlayable, bool bInAllowMultipleAdd = false);`
- L99 _public prototype_ `bool AddExitPlayable(UAvaPlayable* InPlayable, bool bInAllowMultipleAdd = false);`
- L101 _public function_ `bool AddPlayable(UAvaPlayable* InPlayable, EAvaPlayableTransitionEntryRole InPlayableRole, bool bInAllowMultipleAdd = false)`
- L115 _public prototype_ `UAvaPlayableTransition* MakeTransition(UObject* InOuter, const FGuid& InTransitionId = FGuid());`
- L118 _private member_ `TArray<TSharedPtr<FAvaPlayableRemoteControlValues>> EnterPlayableValues;`
- L120 _private member_ `TArray<TWeakObjectPtr<UAvaPlayable>> EnterPlayablesWeak;`
- L121 _private member_ `TArray<TWeakObjectPtr<UAvaPlayable>> PlayingPlayablesWeak;`
- L122 _private member_ `TArray<TWeakObjectPtr<UAvaPlayable>> ExitPlayablesWeak;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMedia/Public/Playback/AvaPlaybackClientDelegates.h` (Public)


#### struct `UE::AvaPlaybackClient::Delegates::FPlaybackStatusChangedArgs`  
`struct FPlaybackStatusChangedArgs`  
_L20-28_
- L22 _public member_ `const FGuid& InstanceId;`
- L23 _public member_ `const FSoftObjectPath& AssetPath;`
- L24 _public member_ `const FString& ChannelName;`
- L25 _public member_ `const FString& ServerName;`
- L26 _public member_ `EAvaPlaybackStatus PrevStatus;`
- L27 _public member_ `EAvaPlaybackStatus NewStatus;`

#### struct `UE::AvaPlaybackClient::Delegates::FPlaybackAssetStatusChangedArgs`  
`struct FPlaybackAssetStatusChangedArgs`  
_L30-35_
- L32 _public member_ `const FSoftObjectPath& AssetPath;`
- L33 _public member_ `const FString& ServerName;`
- L34 _public member_ `EAvaPlaybackAssetStatus Status;`

#### struct `UE::AvaPlaybackClient::Delegates::FPlaybackSequenceEventArgs`  
`struct FPlaybackSequenceEventArgs`  
_L37-46_
- L39 _public member_ `const FGuid& InstanceId;`
- L40 _public member_ `const FSoftObjectPath& AssetPath;`
- L41 _public member_ `const FString& ChannelName;`
- L42 _public member_ `const FString& ServerName;`
- L43 _public member_ `const FString& SequenceName;`
- L44 _public member_ `EAvaPlayableSequenceEventType EventType;`
- L45 _public member_ `int32 ServerFrameNumber;`

#### struct `UE::AvaPlaybackClient::Delegates::FPlaybackTransitionEventArgs`  
`struct FPlaybackTransitionEventArgs`  
_L48-56_
- L50 _public member_ `const FGuid& TransitionId;`
- L51 _public member_ `const FGuid& InstanceId;`
- L52 _public member_ `const FString& ChannelName;`
- L53 _public member_ `const FString& ServerName;`
- L54 _public member_ `EAvaPlayableTransitionEventFlags EventFlags;`
- L55 _public member_ `int32 ServerFrameNumber;`

#### enum `UE::AvaPlaybackClient::Delegates::EConnectionEvent`  
`enum class EConnectionEvent : uint8`  
_L58-62_
- L60 _public enumerator_ `ServerConnected = 0`
- L61 _public enumerator_ `ServerDisconnected`

#### struct `UE::AvaPlaybackClient::Delegates::FConnectionEventArgs`  
`struct FConnectionEventArgs`  
_L64-68_
- L66 _public member_ `const FString& ServerName;`
- L67 _public member_ `EConnectionEvent Event;`

#### Free symbols / members of external scopes

- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace AvaPlaybackClient` (scope `UE`)
- L18 _namespace_ `namespace Delegates` (scope `UE::AvaPlaybackClient`)
- L73 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnConnectionEvent, IAvaPlaybackClient&, const FConnectionEventArgs&);` — Delegate called when a server connection event occurs.
- L73 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnConnectionEvent, IAvaPlaybackClient&, const FConnectionEventArgs&);` (scope `UE::AvaPlaybackClient::Delegates`) — Delegate called when a server connection event occurs.
- L74 _prototype_ `FOnConnectionEvent& GetOnConnectionEvent();` (scope `UE::AvaPlaybackClient::Delegates`)
- L79 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnPlaybackStatusChanged, IAvaPlaybackClient&, const FPlaybackStatusChangedArgs&);` — Delegate called when a playback status changed message is received.
- L79 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnPlaybackStatusChanged, IAvaPlaybackClient&, const FPlaybackStatusChangedArgs&);` (scope `UE::AvaPlaybackClient::Delegates`) — Delegate called when a playback status changed message is received.
- L80 _prototype_ `FOnPlaybackStatusChanged& GetOnPlaybackStatusChanged();` (scope `UE::AvaPlaybackClient::Delegates`)
- L85 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnPlaybackAssetStatusChanged, IAvaPlaybackClient&, const FPlaybackAssetStatusChangedArgs&);` — Delegate called when a playback asset status changed message is received.
- L85 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnPlaybackAssetStatusChanged, IAvaPlaybackClient&, const FPlaybackAssetStatusChangedArgs&);` (scope `UE::AvaPlaybackClient::Delegates`) — Delegate called when a playback asset status changed message is received.
- L86 _prototype_ `FOnPlaybackAssetStatusChanged& GetOnPlaybackAssetStatusChanged();` (scope `UE::AvaPlaybackClient::Delegates`)
- L91 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnPlaybackSequenceEvent, IAvaPlaybackClient&, const FPlaybackSequenceEventArgs&);` — Delegate called when a playback status changed message is received.
- L91 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnPlaybackSequenceEvent, IAvaPlaybackClient&, const FPlaybackSequenceEventArgs&);` (scope `UE::AvaPlaybackClient::Delegates`) — Delegate called when a playback status changed message is received.
- L92 _prototype_ `FOnPlaybackSequenceEvent& GetOnPlaybackSequenceEvent();` (scope `UE::AvaPlaybackClient::Delegates`)
- L97 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnPlaybackTransitionEvent, IAvaPlaybackClient&, const FPlaybackTransitionEventArgs&);` — Delegate called when a playback status changed message is received.
- L97 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnPlaybackTransitionEvent, IAvaPlaybackClient&, const FPlaybackTransitionEventArgs&);` (scope `UE::AvaPlaybackClient::Delegates`) — Delegate called when a playback status changed message is received.
- L98 _prototype_ `FOnPlaybackTransitionEvent& GetOnPlaybackTransitionEvent();` (scope `UE::AvaPlaybackClient::Delegates`)

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMedia/Public/Playback/AvaPlaybackDefines.h` (Public)


#### enum `EAvaPlaybackAction`  
`enum class EAvaPlaybackAction`  
_L8-26_
- reflection: `UENUM()`
- L11 _public enumerator_ `None` — No op
- L13 _public enumerator_ `Load` — Load the given asset. Used for pre-loading assets.
- L15 _public enumerator_ `Start` — Start (i.e. start ticking world and rendering) the given asset, loading it if not pre-loaded.
- L17 _public enumerator_ `Stop` — Stop ticking and rendering the world.
- L19 _public enumerator_ `Unload` — Unload the given asset, i.e. destroy the world, etc.
- L21 _public enumerator_ `Status` — Request the status of the asset. No action is actually performed on the asset.
- L23 _public enumerator_ `SetUserData` — Request to set the user data of the playback instance.
- L25 _public enumerator_ `GetUserData` — Request the user data of the playback instance. No action is actually performed on the asset.

#### enum `EAvaPlaybackAnimAction`  
`enum class EAvaPlaybackAnimAction`  
_L29-37_
- reflection: `UENUM()`
- L31 _public enumerator_ `None`
- L32 _public enumerator_ `Play`
- L33 _public enumerator_ `Continue`
- L34 _public enumerator_ `Stop`
- L35 _public enumerator_ `PreviewFrame`
- L36 _public enumerator_ `CameraCut`

#### Free symbols / members of external scopes

- L39 _namespace_ `namespace UE`
- L39 _namespace_ `namespace AvaMedia` (scope `UE`)
- L39 _namespace_ `namespace Playback` (scope `UE::AvaMedia`)
- L45 _variable_ `static inline const FLazyName DefaultPreviewChannelName = FLazyName(TEXT("_Pre` (scope `UE::AvaMedia::Playback`) — Playback manager needs a channel name as a key. The default key for a preview channel that may not have a defined broadcast channel.

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMedia/Public/Playback/AvaPlaybackGraph.h` (Public)


#### enum `EAvaPlaybackStopOptions`  
`enum class EAvaPlaybackStopOptions : uint8`  
_L32-50_
- reflection: `UENUM()`
- L37 _public enumerator_ `None = 0` — Default option allows for deferred execution of the request when it is safe to do so.
- L41 _public enumerator_ `ForceImmediate = 1 << 1` — Forces the execution of the request when it is called. Typically during shut down.
- L45 _public enumerator_ `Unload = 1 << 2` — Unload from memory after being stopped.
- L49 _public enumerator_ `Default = None` — Default option allows for deferred execution of the request when it is safe to do so.

#### enum `EAvaPlaybackUnloadOptions`  
`enum class EAvaPlaybackUnloadOptions : uint8`  
_L54-68_
- reflection: `UENUM()`
- L59 _public enumerator_ `None = 0` — Default option allows for deferred execution of the request when it is safe to do so.
- L63 _public enumerator_ `ForceImmediate = 1 << 1` — Forces the execution of the request when it is called. Typically during shut down.
- L67 _public enumerator_ `Default = None` — Default option allows for deferred execution of the request when it is safe to do so.

#### struct `FAvaPlaybackPlayableGroup`  
`struct FAvaPlaybackPlayableGroup`  
_L76-137_
- reflection: `USTRUCT()`
- desc: Owns a group of playables. Used to group playables per channels, but can be extended to any conceptual grouping.
- L84 _public member_ `TMap<FSoftObjectPath, TObjectPtr<UAvaPlayable>> Playables;` — `UPROPERTY(Transient)` — TODO: For transition logic within the playback graph, we can't simply index the playables by asset path since we may have to instance the same asset twice for a transition between pages using the same template. For now, rundown does transition with multiple playback graph instances instead.
- L86 _public function_ `UAvaPlayable* FindPlayable(const FSoftObjectPath& InSourceAssetPath) const`
- L92 _public function_ `bool HasPlayable(const UAvaPlayable* InPlayable) const`
- L104 _public function_ `UAvaPlayable* GetFirstPlayable() const`
- L116 _public function_ `void GetAllPlayables(TArray<UAvaPlayable*>& OutPlayables) const`
- L127 _public function_ `void ForEachPlayable(TFunctionRef<void(const UAvaPlayable*)> InFunction) const`

#### class `UAvaPlaybackGraph`  
`class UAvaPlaybackGraph : public UObject`  
_L146-448_
- reflection: `UCLASS(NotBlueprintable, BlueprintType, ClassGroup = "Motion Design Playback", meta = (DisplayName = "Motion Design Playback Graph"))`
- inherits: `UObject`
- desc: A Playback Graph is used for playing Motion Design assets integrated with the broadcast framework. It allows the creation of a playback graph with some logic and inputs routed to player nodes, the results of which can be routed to broadcast channels. This is the lowest implementation layer that supports distributed playback (over message bus).
- L154 _public prototype_ `void Play();` — `UFUNCTION(BlueprintCallable, Category = "Motion Design Playback")`
- L157 _public prototype_ `void Stop(EAvaPlaybackStopOptions InStopOptions);` — `UFUNCTION(BlueprintCallable, Category = "Motion Design Playback")`
- L160 _public prototype_ `void LoadInstances();` — `UFUNCTION(BlueprintCallable, Category = "Motion Design Playback")`
- L164 _public prototype_ `void UnloadInstances(EAvaPlaybackUnloadOptions InUnloadOptions);` — `UFUNCTION(BlueprintCallable, Category = "Motion Design Playback")` — Unload all game instance's worlds from this playback.
- L167 _public function_ `bool IsPlaying() const` — `UFUNCTION(BlueprintCallable, Category = "Motion Design Playback")`
- L172 _public prototype_ `void SetPlaybackManager(const TSharedPtr<FAvaPlaybackManager>& InPlaybackManager);` — Sets the parent playback manager that will handle ticking.
- L174 _public function_ `bool IsManaged() const`
- L176 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnPlaybackStateChanged, bool);`
- L177 _public member_ `FOnPlaybackStateChanged OnPlaybackStateChanged;`
- L180 _public prototype_ `UAvaPlayable* GetFirstPlayable() const;` — Quick access to the first playable in the playback graph.
- L182 _public prototype_ `void GetAllPlayables(TArray<UAvaPlayable*>& OutPlayables) const;`
- L184 _public prototype_ `void ForEachPlayable(TFunctionRef<void(const UAvaPlayable*)> InFunction) const;`
- L187 _public prototype_ `bool HasPlayable(const UAvaPlayable* InPlayable) const;` — Returns true if the given playable is part of this playback graph.
- L189 _public prototype_ `UAvaPlayable* FindPlayable(const FSoftObjectPath& InSourceAssetPath, const FName& InChannelName) const;`
- L190 _public prototype_ `UAvaPlayable* FindOrLoadPlayable(const FAvaSoftAssetPtr& InSourceAsset, const FName& InChannelName, const FString& InLoadOptions = FString());`
- L191 _public prototype_ `void RemovePlayable(const FSoftObjectPath& InSourceAssetPath, const FName& InChannelName);`
- L192 _public prototype_ `bool UnloadAndRemovePlayable(UAvaPlayable* InPlayable, const FSoftObjectPath& InSourceAssetPath, const FName& InChannelName, bool bInForceImmediate);`
- L193 _public prototype_ `bool UnloadAndRemovePlayable(const FSoftObjectPath& InSourceAssetPath, const FName& InChannelName, bool bInForceImmediate);`
- L195 _public prototype_ `TArray<UAvaGameInstance*> GetActiveGameInstances() const;`
- L201 _public prototype_ `bool HasPlayerNodeForSourceAsset(const FSoftObjectPath& InSourceAssetPath) const;` — Determines if the graph contains a node with the given source Motion Design Asset. This works even if the Motion Design asset running.
- L203 _public prototype_ `void SetPlayableGroupManager(UAvaPlayableGroupManager* InPlayableGroupManager);`
- L205 _public function_ `UAvaPlayableGroupManager* GetPlayableGroupManager() const`
- L210 _public prototype_ `static UAvaPlayableGroupManager* GetGlobalPlayableGroupManager();`
- L213 _public function_ `FName ResolveChannelName(const FName InPlaybackChannelName) const` — Resolve the channel name for a playback settings entry.
- L221 _public function_ `bool IsDryRunningGraph() const`
- L222 _public prototype_ `void DryRunGraph(bool bDeferredExecution = false);`
- L231 _public function_ `void SetPreviewChannelName(const FName& InPreviewChannelName)` — Sets the preview channel this playback object is dedicated to. By doing this, the playback object will render in only that channel regardless of the internal playback graph. The specified channel may not exist in the broadcast configuration, in which case the preview playback will fallback to a channel-less render target.
- L233 _public function_ `FName GetPreviewChannelName() const`
- L238 _public function_ `bool IsPreviewOnly() const` — Returns true if the playback object is dedicated to a local preview.
- L244 _public prototype_ `TArray<FName> GetChannelNamesForIndices(const TArray<int32>& InChannelIndices) const;` — Helper function to implement some of the event nodes logic. It will return the list of channel names that correspond this the indices.
- L247 _private prototype_ `void DryRunGraphInternal();`
- L248 _private prototype_ `void RegisterTickDelegate();`
- L249 _private prototype_ `void UnregisterTickDelegate();`
- L250 _private prototype_ `void OnEndFrameTick();`
- L251 _private prototype_ `void ConditionalResolvePlaybackSettings();`
- L254 _public prototype_ `void SetRootNode(UAvaPlaybackNodeRoot* InRoot);`
- L255 _public prototype_ `void AddPlayerNode(UAvaPlaybackNodePlayer* InPlayer);`
- L257 _public prototype_ `UAvaPlaybackNodeRoot* GetRootNode() const;`
- L259 _public prototype_ `void AddPlaybackNode(UAvaPlaybackNode* Node);`
- L260 _public prototype_ `void RemovePlaybackNode(UAvaPlaybackNode* Node);`
- L265 _public prototype_ `void StopPlayable(const FSoftObjectPath& InSourceAssetPath, const FName& InChannelName);` — Stops the playable corresponding to the given asset in the given channel.
- L270 _public prototype_ `void LoadAsset(const FAvaSoftAssetPtr& InSourceAsset, const FName& InChannelName, const FString& InLoadOptions);` — Start streaming the asset in a game instance.
- L272 _public prototype_ `virtual void Tick(float DeltaTime);`
- L274 _public prototype_ `void PushAnimationCommand(const FSoftObjectPath& InSourceAssetPath, const FString& InChannelName, EAvaPlaybackAnimAction InAnimAction, const FAvaPlaybackAnimPlaySettings& InAnimSettings);`
- L275 _public prototype_ `void PushRemoteControlValues(const FSoftObjectPath& InSourceAssetPath, const FString& InChannelName, const TSharedRef<FAvaPlayableRemoteControlValues>& InRemoteControlValues, EAvaPlayableRCUpdateFlags InFlags = EAvaPlayableRCUpdateFlags::None);`
- L277 _public prototype_ `void SetupPlaybackNode(UAvaPlaybackNode* InPlaybackNode, bool bSelectNewNode = true);`
- L280 _public prototype_ `const TArray<TObjectPtr<UAvaPlaybackNode>>& GetPlaybackNodes() const;`
- L283 _public prototype_ `void CreateGraph();` — Create the basic sound graph
- L286 _public prototype_ `void ClearGraph();` — Clears all nodes from the graph
- L288 _public prototype_ `void RefreshPlaybackNode(UAvaPlaybackNode* InPlaybackNode);`
- L290 _public prototype_ `void CompilePlaybackNodesFromGraphNodes();`
- L293 _public prototype_ `UEdGraph* GetGraph();` — Get the Playback EdGraph
- L296 _public prototype_ `void ResetGraph();` — Resets all graph data and nodes
- L298 _public prototype_ `void SetGraphEditor(TSharedPtr<IAvaPlaybackGraphEditor> InGraphEditor);`
- L300 _public prototype_ `TSharedPtr<IAvaPlaybackGraphEditor> GetGraphEditor() const;`
- L304 _public function_ `template<typename InPlaybackNodeType, typename = typename TEnableIf<TIsDerivedFrom<InPlaybackNodeType, UAvaPlaybackNode>::IsDerived>::Type> InPlaybackNodeType* ConstructPlaybackNode(TSubclassOf<InPlaybackNodeType> NodeClass = nullptr, bool bSelectNewNode = true)`
- L335 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnPlayableCreated, UAvaPlaybackGraph* , UAvaPlayable* );` — Delegate called when a playable is created in this playback graph.
- L336 _public member_ `FOnPlayableCreated OnPlayableCreated;`
- L339 _protected prototype_ `void ExecutePendingAnimationCommands();`
- L340 _protected prototype_ `void ExecutePendingRemoteControlCommands();`
- L342 _protected prototype_ `void OnChannelChanged(const FAvaBroadcastOutputChannel& InChannel, EAvaBroadcastChannelChange InChange);`
- L343 _protected prototype_ `void OnChannelBroadcastStateChanged(const FAvaBroadcastOutputChannel& InChannel);`
- L345 _protected prototype_ `void SetIsPlaying(bool bInIsPlaying);`
- L347 _protected prototype_ `bool CanRefreshPlayback(const FAvaSoftAssetPtr& InSourceAsset, const FAvaBroadcastOutputChannel& InChannel) const;`
- L349 _protected prototype_ `bool RefreshPlayback(const FAvaSoftAssetPtr& InSourceAsset, const FString& InLoadOptions, FAvaBroadcastOutputChannel& InChannel, const FName& InChannelName);`
- L351 _protected prototype_ `bool CanRefreshPreview(const FAvaSoftAssetPtr& InSourceAsset) const;`
- L353 _protected prototype_ `bool RefreshPreview(const FAvaSoftAssetPtr& InSourceAsset, const FString& InLoadOptions, FAvaBroadcastOutputChannel& InChannel, const FName& InChannelName);`
- L355 _protected prototype_ `static UTextureRenderTarget2D* UpdatePlaybackRenderTarget(const UAvaPlayable* InPlayable, const FAvaBroadcastOutputChannel& InChannel);`
- L362 _protected member_ `TWeakPtr<FAvaPlaybackManager> PlaybackManagerWeak;` — Keep track of the parent manager that handles ticking. If the playback graph is an asset (not managed), it will handle it's own ticking.
- L364 _protected member_ `TMap<FName, FAvaPlaybackChannelParameters> PlaybackSettings;`
- L365 _protected member_ `TMap<FName, FAvaPlaybackChannelParameters> PreviousPlaybackSettings;`
- L368 _protected member_ `TObjectPtr<UAvaPlaybackNodeRoot> RootNode;` — `UPROPERTY(Transient)`
- L371 _protected member_ `TArray<TObjectPtr<UAvaPlaybackNodePlayer>> PlayerNodes;` — `UPROPERTY(Transient)`
- L374 _protected member_ `TWeakPtr<IAvaPlaybackGraphEditor> GraphEditorWeak;`
- L377 _protected member_ `TObjectPtr<UEdGraph> EdGraph;` — `UPROPERTY()`
- L384 _protected member_ `TArray<TObjectPtr<UAvaPlaybackNode>> PlaybackNodes;` — `UPROPERTY()` — An array of all the Playback Nodes, Only available in Editor (Playback doesn't need to know disconnected nodes, unless we support runtime changes as well).
- L399 _protected member_ `TObjectPtr<UAvaPlayableGroupManager> PlayableGroupManager;` — `UPROPERTY(Transient)` — Playback Group Manager for this Playback object. This manager defines the scope with which this playback object's playables can share their group with. In other words, the playables of this playback (that support sharing a group) can have a shared group (for the given channel) cached in this given manager. So far, the PlayableGroupManager has the same scope as the playable manager, i.e. global (a.k.a local) or per playback server.
- L410 _protected member_ `TMap<FName, FAvaPlaybackPlayableGroup> ChannelPlayableGroups;` — `UPROPERTY(Transient)` — Keep track of the playables per channel. The Playback object owns it's playables. However, the playables can share a playable group from other playback objects. This is necessary for the playback server that is always creating just one playback object per playable (atm).
- L412 _protected member_ `bool bIsPlaying = false;`
- L413 _protected member_ `bool bIsDryRunningGraph = false;`
- L414 _protected member_ `bool bAsyncDryRunRequested = false;`
- L415 _protected member_ `bool bIsTicking = false;` — Tick reentrancy guard.
- L416 _protected member_ `FDelegateHandle TickDelegateHandle;`
- L419 _protected member_ `FName PreviewChannelName;` — Name of the preview channel this playback object is dedicated to.
- L446 _protected member_ `TArray<FAnimationCommand> PendingAnimationCommands;`
- L447 _protected member_ `TArray<FRemoteControlCommand> PendingRemoteControlCommands;`

#### struct `UAvaPlaybackGraph::FPlaybackCommand`  
`struct FPlaybackCommand`  
_L421-434_
- L424 _public member_ `FDateTime Timeout;` — If the command has been pending for too long, it will be discarded.
- L426 _public member_ `FSoftObjectPath SourcePath;`
- L427 _public member_ `FString ChannelName;`
- L428 _public member_ `FName ChannelFName;`
- L430 _public function_ `bool HasTimedOut(const FDateTime& InNow) const`

#### struct `UAvaPlaybackGraph::FAnimationCommand`  
`struct FAnimationCommand : public FPlaybackCommand`  
_L435-439_
- inherits: `FPlaybackCommand`
- L437 _public member_ `EAvaPlaybackAnimAction AnimAction;`
- L438 _public member_ `FAvaPlaybackAnimPlaySettings AnimPlaySettings;`

#### struct `UAvaPlaybackGraph::FRemoteControlCommand`  
`struct FRemoteControlCommand : public FPlaybackCommand`  
_L440-444_
- inherits: `FPlaybackCommand`
- L442 _public member_ `TSharedRef<FAvaPlayableRemoteControlValues> Values;`
- L443 _public member_ `EAvaPlayableRCUpdateFlags Flags;`

#### class `FAvaPlaybackGraphBuilder`  
`class FAvaPlaybackGraphBuilder`  
_L453-487_
- desc: Somewhat reusable helper class to build a playback graph.
- L456 _public prototype_ `FAvaPlaybackGraphBuilder(UAvaPlayableGroupManager* InPlayableGroupManager);`
- L457 _public prototype_ `~FAvaPlaybackGraphBuilder();`
- L464 _public prototype_ `bool ConnectToRoot(const FString& InChannelName, UAvaPlaybackNode* InNodeToConnect);` — @brief Connect the given node to the root node's pin corresponding to the given channel name. @param InChannelName Channel name to connect to. @param InNodeToConnect Node (already constructed) to connect.
- L466 _public prototype_ `int32 GetPinIndexForChannel(const FString& InChannelName) const;`
- L468 _public prototype_ `UAvaPlaybackGraph* FinishBuilding();`
- L472 _public function_ `template<typename InPlaybackNodeType, typename = typename TEnableIf<TIsDerivedFrom<InPlaybackNodeType, UAvaPlaybackNode>::IsDerived>::Type> InPlaybackNodeType* ConstructPlaybackNode(TSubclassOf<InPlaybackNodeType> InNodeClass = nullptr, bool bInSelectNewNode = true)` — Helper function to construct a playback node. This will add the node in the playback's node list.
- L484 _private member_ `bool bFinished = false;`
- L485 _private member_ `UAvaPlaybackGraph* Playback = nullptr;`
- L486 _private member_ `UAvaPlaybackNodeRoot* RootNode = nullptr;`

#### Free symbols / members of external scopes

- L15 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogAvaPlayback, Log, All);`
- L15 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogAvaPlayback, Log, All);`
- L51 _prototype_ `ENUM_CLASS_FLAGS(EAvaPlaybackStopOptions);`
- L69 _prototype_ `ENUM_CLASS_FLAGS(EAvaPlaybackUnloadOptions);`
- L176 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnPlaybackStateChanged, bool);`
- L335 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnPlayableCreated, UAvaPlaybackGraph* , UAvaPlayable* );` — Delegate called when a playable is created in this playback graph.

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMedia/Public/Playback/AvaPlaybackManager.h` (Public)


#### class `FAvaPlaybackInstance`  
`class FAvaPlaybackInstance : public FGCObject`  
_L18-75_
- inherits: `FGCObject`
- desc: Handle to a playback instance for recycling.
- L21 _public prototype_ `FAvaPlaybackInstance() = default;`
- L22 _public prototype_ `FAvaPlaybackInstance(const FGuid& InInstanceId, const FSoftObjectPath& InSourcePath, const FString& InChannelName, UAvaPlaybackGraph* InPlayback);`
- L26 _public prototype_ `virtual void AddReferencedObjects( FReferenceCollector& Collector ) override;`
- L27 _public prototype_ `virtual FString GetReferencerName() const override;`
- L34 _public prototype_ `void SetInstanceId(const FGuid& InInstanceId);` — This is used by the server to track the client's id. It can also be used when reconciling the client state from the server.
- L40 _public prototype_ `void SetInstanceUserData(const FString& InUserData);` — Set the instance's user data. This is propagate to the server and can be used when reconciling the client state.
- L42 _public function_ `const FGuid& GetInstanceId() const`
- L43 _public function_ `const FString& GetInstanceUserData() const`
- L44 _public function_ `const FString& GetChannelName() const`
- L45 _public function_ `const FName& GetChannelFName() const`
- L46 _public function_ `const FSoftObjectPath& GetSourcePath() const`
- L47 _public function_ `UAvaPlaybackGraph* GetPlayback() const`
- L48 _public function_ `EAvaPlaybackStatus GetStatus() const`
- L49 _public function_ `bool IsPlaying() const`
- L51 _public prototype_ `bool UpdateStatus();`
- L52 _public function_ `void SetStatus(EAvaPlaybackStatus InStatus)`
- L54 _public prototype_ `void Unload();`
- L55 _public prototype_ `void Recycle();`
- L57 _public prototype_ `TSharedPtr<FAvaPlaybackManager> GetManager() const;`
- L60 _private prototype_ `void OnPlayableCreated(UAvaPlaybackGraph* InPlayback, UAvaPlayable* InPlayable);`
- L64 _private member_ `TWeakPtr<FAvaPlaybackSourceAssetEntry> AssetEntryWeak;` — If the cache slot becomes invalid, it means this instance will be discarded instead of being recycled.
- L66 _private member_ `FGuid InstanceId;`
- L67 _private member_ `FString ChannelName;`
- L68 _private member_ `FName ChannelFName;`
- L69 _private member_ `FSoftObjectPath SourcePath;`
- L70 _private member_ `TObjectPtr<UAvaPlaybackGraph> Playback;`
- L71 _private member_ `EAvaPlaybackStatus Status = EAvaPlaybackStatus::Unknown;`
- L72 _private member_ `FString InstanceUserData;`

#### class `FAvaPlaybackSourceAssetEntry`  
`class FAvaPlaybackSourceAssetEntry`  
_L81-129_
- desc: For each playback instance, a source asset entry is kept track of to allow the entry to be invalidated and prevent the instance to be recycled.
- L84 _public function_ `FAvaPlaybackSourceAssetEntry(const TSharedPtr<FAvaPlaybackManager>& InParentManager) : ParentManagerWeak(InParentManager.ToWeakPtr())`
- L85 _public prototype_ `~FAvaPlaybackSourceAssetEntry() = default;`
- L87 _public function_ `TSharedPtr<FAvaPlaybackInstance> AcquirePlaybackInstance(const FString& InChannelName)`
- L104 _public prototype_ `TSharedPtr<FAvaPlaybackInstance> FindPlaybackInstance(const FGuid& InInstanceId, bool bInAvailableInstances = true, bool bInUsedInstances = true) const;`
- L107 _public prototype_ `TSharedPtr<FAvaPlaybackInstance> FindPlaybackInstanceForChannel(const FString& InChannelName, bool bInAvailableInstances = true, bool bInUsedInstances = true) const;`
- L110 _public prototype_ `TSharedPtr<FAvaPlaybackInstance> FindPlaybackInstanceByPredicate(TFunctionRef<bool(const FAvaPlaybackInstance& )> InPredicate, bool bInAvailableInstances = true, bool bInUsedInstances = true) const;`
- L113 _public prototype_ `void ForAllPlaybackInstances(TFunctionRef<void(FAvaPlaybackInstance& )> InFunction, bool bInAvailableInstances = true, bool bInUsedInstances = true);`
- L116 _public function_ `TSharedPtr<FAvaPlaybackManager> GetManager() const`
- L118 _public prototype_ `void DiscardInstance(FAvaPlaybackInstance* InInstanceToRemove);`
- L119 _public prototype_ `void RecycleInstance(FAvaPlaybackInstance* InInstanceToRecycle);`
- L123 _private member_ `TWeakPtr<FAvaPlaybackManager> ParentManagerWeak;` — Keeping a weak reference to the manager to recycle the instance.
- L125 _private member_ `TArray<TSharedPtr<FAvaPlaybackInstance>> AvailableInstances;`
- L126 _private member_ `TArray<TWeakPtr<FAvaPlaybackInstance>> UsedInstances;`

#### enum `EAvaPlaybackPackageEventFlags`  
`enum class EAvaPlaybackPackageEventFlags : uint8`  
_L133-140_
- reflection: `UENUM()`
- desc: Flags indicating what changed in the package event.
- L135 _public enumerator_ `None = 0`
- L136 _public enumerator_ `External = 1 << 0`
- L137 _public enumerator_ `Saved = 1 << 1`
- L138 _public enumerator_ `AssetDeleted = 1 << 2`
- L139 _public enumerator_ `All = 0xFF`

#### class `FAvaPlaybackManager`  
`class FAvaPlaybackManager : public TSharedFromThis<FAvaPlaybackManager>`  
_L143-415_
- inherits: `TSharedFromThis<FAvaPlaybackManager>`
- L146 _public prototype_ `FAvaPlaybackManager();`
- L147 _public prototype_ `virtual ~FAvaPlaybackManager();`
- L149 _public prototype_ `void Tick();`
- L151 _public function_ `void SetEnablePlaybackCommandsBuffering(bool bInEnable)`
- L153 _public function_ `UAvaPlayableGroupManager* GetPlayableGroupManager() const`
- L160 _public prototype_ `TSharedPtr<FAvaPlaybackInstance> AcquirePlaybackInstance(const FSoftObjectPath& InAssetPath, const FString& InChannelName) const;` — Acquire (recycle) a cached playback instance. Will return null if none available in the cache. @param InAssetPath Soft object path to the asset to load. This can either be a playback graph itself or a playable asset. @param InChannelName For a playable asset, specifying the channel name will indicate where to connect the player node in the playback graph
- L169 _public prototype_ `TSharedPtr<FAvaPlaybackInstance> LoadPlaybackInstance(const FSoftObjectPath& InAssetPath, const FString& InChannelName, const FString& InLoadOptions = FString());` — Load a new (recyclable) playback instance for the given asset in the given channel. @remark This function only loads (or creates) the playback graph. The playable assets should be loaded only once the graph is playing. @param InAssetPath Soft object path to the asset to load. This can either be a playback graph itself or a playable asset. @param InChannelName For a playable asset, specifying the channel name will indicate where to connect the player node in the playback graph @param InLoadOptions Optional parameters to be used when loading the playable.
- L179 _public prototype_ `TSharedPtr<FAvaPlaybackInstance> AcquireOrLoadPlaybackInstance(const FSoftObjectPath& InAssetPath, const FString& InChannelName, const FString& InLoadOptions = FString());` — Attempts to acquire (recycle) an existing playback instance. If none available, will load a new one. @param InAssetPath Soft object path to the asset to load. This can either be a playback graph itself or a playable asset. @param InChannelName For a playable asset, specifying the channel name will indicate where to connect the player node in the playback graph @param InLoadOptions Optional parameters to be used when loading the playable. @remark Load options will not be applied for recycled instances. (todo) @see LoadPlaybackInstance, AcquirePlaybackInstance
- L185 _public prototype_ `TSharedPtr<FAvaPlaybackInstance> FindPlaybackInstance(const FGuid& InInstanceId, const FSoftObjectPath& InAssetPath, const FString& InChannelName) const;` — Finds an existing (either available or used) playback instance. This will not acquire it (i.e. if available, it will remain so).
- L191 _public prototype_ `bool UnloadPlaybackInstances(const FSoftObjectPath& InAssetPath, const FString& InChannelName);` — Unload and discard any available (i.e. not used) instances for this asset/channel entry. If specified channel name is empty, it will discard all instances of the asset.
- L193 _public prototype_ `void ForAllPlaybackInstances(TFunctionRef<void(FAvaPlaybackInstance& )> InFunction);`
- L198 _public prototype_ `EAvaPlaybackAssetStatus GetLocalAssetStatus(const FName& InPackageName);` — Determines the local status of the given asset on this local instance of the playback manager.
- L203 _public prototype_ `void InvalidateCachedLocalAssetStatus(const FName& InPackageName);` — Invalidates the cached local asset status.
- L211 _public function_ `bool IsLocalAssetAvailable(const FName& InPackageName)` — Utility function to determine if an asset is locally available. Remark: Determining the presence of dependencies is somewhat unreliable i.e. an asset can playback fine even with some dependencies missing and it is hard to figure it out. Because of that, for now, we consider the asset available even if it is missing some dependencies.
- L217 _public function_ `bool IsLocalAssetAvailable(const FSoftObjectPath& InAssetPath)`
- L223 _public function_ `EAvaPlaybackStatus GetUnloadedPlaybackStatus(const FSoftObjectPath& InAssetPath)` — Utility function to determine the playback status of an unloaded asset.
- L233 _public prototype_ `void InvalidatePlaybackAssetEntry(const FSoftObjectPath& InAssetPath);` — Invalidate the asset entry. All cached instances will be invalidated along with it.
- L243 _public prototype_ `UAvaPlaybackGraph* LoadPlaybackObject(const FSoftObjectPath& InAssetPath, const FString& InChannelName, const FString& InLoadOptions = FString()) const;` — Loads a new playback graph for the given asset with the given channel as context. @remark The playback graph is either loaded or created. The referenced assets (playables) are not loaded yet. @param InAssetPath Soft object path to the asset to load. This can either be a playback graph itself or a playable asset. @param InChannelName For a playable asset, specifying the channel name will indicate where to connect the player node in the playback graph @param InLoadOptions Optional parameters to be used when loading the playable. @remark Direct loading of playback graphs is not fully supported yet. Experimental use only.
- L251 _public prototype_ `UAvaPlaybackGraph* BuildPlaybackFromWorld(const TSoftObjectPtr<UWorld>& InWorld, const FString& InChannelName, const FString& InLoadOptions = FString()) const;` — Utility function to create a new playback graph instance for the given world asset with the given channel as context. @param InWorld Soft object path to the world asset to load. @param InChannelName For a playable asset, specifying the channel name will indicate where to connect the player node in the playback graph @param InLoadOptions Optional parameters to be used when loading the playable.
- L258 _public prototype_ `TArray<FSoftObjectPath> StopAllPlaybacks(bool bInUnload);` — Stops all currently playing playback objects. @param bInUnload if true, will also unload the objects. @return Returns the list of all source assets that were stopped.
- L260 _public prototype_ `bool PushAnimationCommand(const FGuid& InInstanceId, const FSoftObjectPath& InSourcePath, const FString& InChannelName, EAvaPlaybackAnimAction InAction, const FAvaPlaybackAnimPlaySettings& InAnimSettings);`
- L261 _public prototype_ `bool PushRemoteControlCommand(const FGuid& InInstanceId, const FSoftObjectPath& InSourcePath, const FString& InChannelName, const TSharedRef<FAvaPlayableRemoteControlValues>& InRemoteControlValues, EAvaPlayableRCUpdateFlags InFlags = EAvaPlayableRCUpdateFlags::None);`
- L262 _public prototype_ `bool PushPlaybackTransitionStartCommand(UAvaPlaybackTransition* InTransitionToStart);`
- L265 _public prototype_ `void ApplyPendingCommands(UAvaPlaybackGraph* InPlaybackObject, const FGuid& InInstanceId, const FSoftObjectPath& InSourcePath, const FString& InChannelName);` — This is used on the playback server to apply any pending commands to a playback instance.
- L270 _public function_ `void StartShuttingDown()` — Indicate the manager is in a shutdown sequence and will force game instances to destroy worlds right away.
- L272 _public function_ `bool IsShuttingDown() const`
- L274 _public function_ `EAvaPlaybackStopOptions GetPlaybackStopOptions(bool bInUnload) const`
- L281 _public function_ `EAvaPlaybackUnloadOptions GetPlaybackUnloadOptions() const`
- L287 _public prototype_ `void OnPackageModified(const FName& InPackageName, EAvaPlaybackPackageEventFlags InFlags = EAvaPlaybackPackageEventFlags::None);` — Let the Playback manager know that a package has been modified.
- L298 _public prototype_ `void OnParentWorldBeginTearDown();` — TearDown the whole Motion Design Playback system. When Motion Design Playback is used within a game, we need to tear down everything as the parent world is being teared down. The game tear down process will forcibly mark as garbage (and GCs) all the GameInstances, including those held by the playback objects, despite playback objects holding strong references to them. To avoid issues we preemptively destroy all the playback objects.
- L304 _public prototype_ `bool HandleStatCommand(const TArray<FString>& InArgs);` — Implements a similar command to Engine::HandleStatCommand, except it will fetch Motion Design's game viewport client if everything else fails.
- L307 _public prototype_ `static bool IsPlaybackAsset(const FAssetData& InAssetData);` — Returns true if the given asset is a playback asset, i.e. either a "playable" asset or a playback graph.
- L309 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnPlaybackInstanceInvalidated, const FAvaPlaybackInstance&);`
- L310 _public member_ `FOnPlaybackInstanceInvalidated OnPlaybackInstanceInvalidated;`
- L312 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnPlaybackInstanceStatusChanged, const FAvaPlaybackInstance&);`
- L313 _public member_ `FOnPlaybackInstanceStatusChanged OnPlaybackInstanceStatusChanged;`
- L315 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnLocalPlaybackAssetRemoved, const FSoftObjectPath&);`
- L316 _public member_ `FOnLocalPlaybackAssetRemoved OnLocalPlaybackAssetRemoved;`
- L318 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnBeginTick, float);`
- L319 _public member_ `FOnBeginTick OnBeginTick;`
- L323 _protected prototype_ `FAvaPlaybackManager(const FAvaPlaybackManager&) = delete;` — Non-copyable (because copy of CachedAssetStatusExtra is not defined)
- L324 _protected prototype_ `FAvaPlaybackManager& operator=(const FAvaPlaybackManager&) = delete;`
- L326 _protected prototype_ `void OnPackageSaved(const FString& InPackageFileName, UPackage* InPackage, FObjectPostSaveContext InObjectSaveContext);`
- L327 _protected prototype_ `void OnAvaSyncPackageModified(IAvaMediaSyncProvider* InAvaMediaSyncProvider, const FName& InPackageName);`
- L328 _protected prototype_ `void OnAssetRemoved(const FAssetData& InAssetData);`
- L330 _protected function_ `TSharedPtr<FAvaPlaybackSourceAssetEntry> FindPlaybackAssetEntry(const FSoftObjectPath& InAssetPath) const`
- L336 _protected function_ `TSharedPtr<FAvaPlaybackSourceAssetEntry> GetPlaybackAssetEntry(const FSoftObjectPath& InAssetPath)`
- L351 _private member_ `bool bIsShuttingDown = false;`
- L354 _private member_ `TStrongObjectPtr<UAvaPlayableGroupManager> PlayableGroupManager;` — This is the shared pool of shared playable groups for all the playback objects.
- L357 _private member_ `TMap<FSoftObjectPath, TSharedPtr<FAvaPlaybackSourceAssetEntry>> PlaybackAssetEntries;` — TODO: Refactor this to support cache capacity with eviction (LRU) like FAvaRundownManagedInstanceCache.
- L360 _private member_ `TMap<FName, EAvaPlaybackAssetStatus> CachedAssetStatus;` — Cached asset status.
- L362 _private member_ `TArray<TWeakObjectPtr<UAvaPlaybackTransition>> PendingStartTransitions;`
- L372 _private member_ `bool bEnablePlaybackCommandsBuffering = false;` — Enables the playback command buffering. This is enabled on the playback server to handle the Remote control and animation commands being received/processed before the playback command itself (where the playback object is created). If the commands can't be executed because the object is not yet created the playback manager will buffer the commands and apply them to the object once it is loaded.
- L391 _private member_ `TMap<FString, FPlaybackObjectCommandBuffers> PlaybackObjectCommandBuffers;` — Use FAvaPlaybackManager::MakePlaybackKey for Map key.
- L393 _private function_ `FString MakeCommandBufferKey(const FSoftObjectPath& InAssetPath, const FString& InChannelName) const`
- L403 _private function_ `FString MakeCommandBufferKey(const FGuid& InInstanceId) const`
- L408 _private function_ `FString MakeCommandBufferKey(const FGuid& InInstanceId, const FSoftObjectPath& InAssetPath, const FString& InChannelName) const`
- L413 _private prototype_ `FPlaybackObjectCommandBuffers& GetOrCreatePlaybackCommandBuffers(FString&& InCommandBufferKey);`
- L414 _private prototype_ `const FPlaybackObjectCommandBuffers* GetPlaybackCommandBuffers(const FString& InCommandBufferKey) const;`

#### struct `FAvaPlaybackManager::FPlaybackObjectCommandBuffers`  
`struct FPlaybackObjectCommandBuffers`  
_L374-389_
- L387 _public member_ `TArray<FAnimationCommand> AnimationCommands;`
- L388 _public member_ `TArray<FRemoteControlCommand> RemoteControlCommands;`

#### struct `FAvaPlaybackManager::FPlaybackObjectCommandBuffers::FAnimationCommand`  
`struct FAnimationCommand`  
_L376-380_
- L378 _public member_ `EAvaPlaybackAnimAction AnimAction;`
- L379 _public member_ `FAvaPlaybackAnimPlaySettings AnimPlaySettings;`

#### struct `FAvaPlaybackManager::FPlaybackObjectCommandBuffers::FRemoteControlCommand`  
`struct FRemoteControlCommand`  
_L381-385_
- L383 _public member_ `TSharedRef<FAvaPlayableRemoteControlValues> Values;`
- L384 _public member_ `EAvaPlayableRCUpdateFlags UpdateFlags;`

#### Free symbols / members of external scopes

- L91 _function_ `` (scope `FAvaPlaybackSourceAssetEntry::AcquirePlaybackInstance`)
- L141 _prototype_ `ENUM_CLASS_FLAGS(EAvaPlaybackPackageEventFlags);`
- L309 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnPlaybackInstanceInvalidated, const FAvaPlaybackInstance&);`
- L312 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnPlaybackInstanceStatusChanged, const FAvaPlaybackInstance&);`
- L315 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnLocalPlaybackAssetRemoved, const FSoftObjectPath&);`
- L318 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnBeginTick, float);`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMedia/Public/Playback/IAvaPlaybackClient.h` (Public)


#### class `IAvaPlaybackClient`  
`class IAvaPlaybackClient`  
_L14-113_
- L17 _public prototype_ `IAvaPlaybackClient() = default;`
- L18 _public prototype_ `virtual ~IAvaPlaybackClient() = default;`
- L20 _public prototype_ `virtual int32 GetNumConnectedServers() const = 0;`
- L22 _public prototype_ `virtual TArray<FString> GetServerNames() const = 0;`
- L25 _public prototype_ `virtual FMessageAddress GetServerAddress(const FString& InServerName) const = 0;` — Returns the corresponding server address for the given server name. If server name is not found, returns invalid address.
- L28 _public prototype_ `virtual bool HasServerUserData(const FString& InServerName, const FString& InUserDataKey) const = 0;` — Returns true if the corresponding server user data for the given server name is found.
- L31 _public prototype_ `virtual const FString& GetServerUserData(const FString& InServerName, const FString& InUserDataKey) const = 0;` — Returns the corresponding server user data for the given server name and key. Returns empty array if not found.
- L34 _public prototype_ `virtual bool HasUserData(const FString& InKey) const = 0;` — Returns true if the corresponding client user data for the given key is found.
- L37 _public prototype_ `virtual const FString& GetUserData(const FString& InKey) const = 0;` — Returns the corresponding client user data for the given key. Returns empty container if not found.
- L40 _public prototype_ `virtual void SetUserData(const FString& InKey, const FString& InData) = 0;` — Add user data to this client. This is replicated and accessible to the servers.
- L43 _public prototype_ `virtual void RemoveUserData(const FString& InKey) = 0;` — Remove the client's user data entry from the given key.
- L46 _public prototype_ `virtual void BroadcastStatCommand(const FString& InCommand, bool bInBroadcastLocalState) = 0;` — Send a stat command to all connected servers.
- L48 _public prototype_ `virtual void RequestPlaybackAssetStatus(const FSoftObjectPath& InAssetPath, const FString& InChannelOrServerName, bool bInForceRefresh) = 0;`
- L49 _public prototype_ `virtual void RequestPlayback(const FGuid& InInstanceId, const FSoftObjectPath& InAssetPath, const FString& InChannelName, EAvaPlaybackAction InAction, const FString& InArguments = FString()) = 0;`
- L50 _public prototype_ `virtual void RequestAnimPlayback(const FGuid& InInstanceId, const FSoftObjectPath& InAssetPath, const FString& InChannelName, const FAvaPlaybackAnimPlaySettings& InAnimSettings) = 0;`
- L51 _public prototype_ `virtual void RequestAnimAction(const FGuid& InInstanceId, const FSoftObjectPath& InAssetPath, const FString& InChannelName, const FString& InAnimationName, EAvaPlaybackAnimAction InAction) = 0;`
- L52 _public prototype_ `virtual void RequestRemoteControlUpdate(const FGuid& InInstanceId, const FSoftObjectPath& InAssetPath, const FString& InChannelName, const FAvaPlayableRemoteControlValues& InRemoteControlValues, EAvaPlayableRCUpdateFlags InFlags = EAvaPlayableRCUpdateFlags::None) = 0;`
- L53 _public prototype_ `virtual void RequestPlayableTransitionStart(const FGuid& InTransitionId, TArray<FGuid>&& InEnterInstanceIds, TArray<FGuid>&& InPlayingInstanceIds, TArray<FGuid>&& InExitInstanceIds, TArray<FAvaPlayableRemoteControlValues>&& InEnterValues, const FName& InChannelName, EAvaPlayableTransitionFlags InTransitionFlags) = 0;`
- L54 _public prototype_ `virtual void RequestPlayableTransitionStop(const FGuid& InTransitionId, const FName& InChannelName) = 0;`
- L55 _public prototype_ `virtual void RequestBroadcast(const FString& InProfile, const FName& InChannel, const TArray<UMediaOutput*>& InRemoteMediaOutputs, EAvaBroadcastAction InAction, const FString& InServerName = FString()) = 0;`
- L60 _public prototype_ `virtual bool IsMediaOutputRemoteFallback(const UMediaOutput* InMediaOutput) = 0;` — Use the device provider to determine if the media output is remote. This function should only be used as fallback if the channel's media output info is not valid.
- L61 _public prototype_ `virtual EAvaBroadcastIssueSeverity GetMediaOutputIssueSeverity(const FString& InServerName, const FString& InChannelName, const FGuid& InOutputGuid) const = 0;`
- L62 _public prototype_ `virtual const TArray<FString>& GetMediaOutputIssueMessages(const FString& InServerName, const FString& InChannelName, const FGuid& InOutputGuid) const = 0;`
- L63 _public prototype_ `virtual EAvaBroadcastOutputState GetMediaOutputState(const FString& InServerName, const FString& InChannelName, const FGuid& InOutputGuid) const = 0;`
- L70 _public prototype_ `virtual bool HasAnyServerOnlineForChannel(const FName& InChannelName) const = 0;` — Returns true if the client has at least one connected server for the given channel. This does not care if the channel is live or idle. This is needed to send preload commands to server even if they are not live yet (but connected).
- L75 _public prototype_ `virtual TArray<FString> GetOnlineServersForChannel(const FName& InChannelName) const = 0;` — Returns a list of all connected servers having outputs in the given channel.
- L92 _public prototype_ `virtual TOptional<EAvaPlaybackStatus> GetRemotePlaybackStatus(const FGuid& InInstanceId, const FSoftObjectPath& InAssetPath, const FString& InChannelName, const FString& InServerName = FString()) const = 0;` — Returns the status of the playback asset on the given channel on the remote server. If the return value is not set, it is because it is not yet available, in which case a status request can be made to make it available. This supports forked channels by allowing to specify the optional server to further precise the request. In a forked channel situation, a channel will be hosted by multiple servers and therefore, have a playback status per server. If the server name is left empty, the playback status of the first server hosting the given channel will be returned. @param InInstanceId Specify instance. If not specified, it will look for the most relevant status for the given asset. @param InAssetPath Full path of the playback asset to fetch the status of. @param InChannelName Servers can be running different channels, so need to identify the channel as well. @param InServerName Identifies the server to fetch the status from.
- L102 _public prototype_ `virtual const FString* GetRemotePlaybackUserData(const FGuid& InInstanceId, const FSoftObjectPath& InAssetPath, const FString& InChannelName, const FString& InServerName = FString()) const = 0;` — @brief Returns the user data of the specified playback instance. @param InInstanceId Specify instance of the given asset. @param InAssetPath Full path of the playback asset. Must be valid. @param InChannelName Servers can be running different channels, so need to identify the channel as well. @param InServerName Identifies the server to fetch the status from. @return
- L112 _public prototype_ `virtual TOptional<EAvaPlaybackAssetStatus> GetRemotePlaybackAssetStatus(const FSoftObjectPath& InAssetPath, const FString& InServerName) const = 0;` — Returns the status of the playback asset on the given remote server. If the return value is not set, it is because it is not yet available, in which case a status request must be made explicitly, using RequestPlaybackAssetStatus to make it available. @param InAssetPath Full path of the playback asset to fetch the status of. @param InServerName Identifies the server to fetch the status from.

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMedia/Public/Playback/IAvaPlaybackGraphEditor.h` (Public)


#### class `IAvaPlaybackGraphEditor`  
`class IAvaPlaybackGraphEditor`  
_L17-46_
- L20 _public prototype_ `virtual ~IAvaPlaybackGraphEditor() = default;`
- L22 _public prototype_ `virtual UEdGraph* CreatePlaybackGraph(UAvaPlaybackGraph* InPlayback) = 0;`
- L24 _public prototype_ `virtual void SetupPlaybackNode(UEdGraph* InGraph, UAvaPlaybackNode* InPlaybackNode, bool bSelectNewNode) = 0;`
- L27 _public prototype_ `virtual void CompilePlaybackNodesFromGraphNodes(UAvaPlaybackGraph* InPlayback) = 0;` — Compiles Playback nodes from graph nodes.
- L29 _public prototype_ `virtual void CreateInputPin(UEdGraphNode* InGraphNode) = 0;`
- L31 _public prototype_ `virtual void RefreshNode(UEdGraphNode& InGraphNode) = 0;`
- L40 _public prototype_ `virtual bool GetBoundsForSelectedNodes(FSlateRect& Rect, float Padding) = 0;` — Get the bounding area for the currently selected nodes @param Rect Final output bounding area, including padding @param Padding An amount of padding to add to all sides of the bounds @return false if nothing is selected
- L42 _public prototype_ `virtual TSet<UObject*> GetSelectedNodes() const = 0;`
- L44 _public prototype_ `virtual bool CanPasteNodes() const = 0;`
- L45 _public prototype_ `virtual void PasteNodesHere(const FVector2D& Location) = 0;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMedia/Public/Playback/IAvaPlaybackServer.h` (Public)


#### class `IAvaPlaybackServer`  
`class IAvaPlaybackServer`  
_L13-81_
- L23 _public prototype_ `virtual TArray<FPlaybackInstanceReference> StopPlaybacks(const FString& InChannelName = FString(), const FSoftObjectPath& InAssetPath = FSoftObjectPath(), bool bInUnload = true) = 0;`
- L24 _public prototype_ `virtual TArray<FPlaybackInstanceReference> StartPlaybacks() = 0;`
- L26 _public prototype_ `virtual void StartBroadcast() = 0;`
- L27 _public prototype_ `virtual void StopBroadcast() = 0;`
- L30 _public prototype_ `virtual const FString& GetName() const = 0;` — Returns the server's name.
- L32 _public prototype_ `virtual bool HasUserData(const FString& InKey) const = 0;`
- L34 _public prototype_ `virtual const FString& GetUserData(const FString& InKey) const = 0;`
- L37 _public prototype_ `virtual void SetUserData(const FString& InKey, const FString& InData) = 0;` — Add user data to this server. This is replicated and accessible to the client.
- L40 _public prototype_ `virtual void RemoveUserData(const FString& InKey) = 0;` — Remove the server's user data entry from the given key.
- L43 _public prototype_ `virtual TArray<FString> GetClientNames() const = 0;` — Returns the list of connected clients.
- L46 _public prototype_ `virtual FMessageAddress GetClientAddress(const FString& InClientName) const = 0;` — Returns the client address.
- L49 _public prototype_ `virtual bool HasClientUserData(const FString& InClientName, const FString& InKey) const = 0;` — Returns true if the corresponding client user data for the given client name is found.
- L55 _public prototype_ `virtual const FString& GetClientUserData(const FString& InClientName, const FString& InKey) const = 0;` — Returns the corresponding client user data for the given client name and key. Returns empty string if not found.
- L61 _public prototype_ `virtual const IAvaBroadcastSettings* GetBroadcastSettings() const = 0;` — Access broadcast settings replicated from connected client. Will return nullptr if no clients are connected.
- L67 _public prototype_ `virtual const FAvaInstanceSettings* GetAvaInstanceSettings() const = 0;` — Access Motion Design Instance settings replicated from connected client(s). Will return nullptr if no clients are connected.
- L73 _public prototype_ `virtual const FAvaPlayableSettings* GetPlayableSettings() const = 0;` — Access Motion Design Playable settings replicated from connected client(s). Will return nullptr if no clients are connected.
- L76 _public prototype_ `virtual const FAvaPlaybackManager& GetPlaybackManager() const = 0;` — Access the server's playback manager.
- L77 _public prototype_ `virtual FAvaPlaybackManager& GetPlaybackManager() = 0;`
- L80 _protected prototype_ `virtual ~IAvaPlaybackServer() = default;`

#### struct `IAvaPlaybackServer::FPlaybackInstanceReference`  
`struct FPlaybackInstanceReference`  
_L17-21_
- L19 _public member_ `FGuid Id;`
- L20 _public member_ `FSoftObjectPath Path;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMedia/Public/Playback/Nodes/AvaPlaybackNode.h` (Public)


#### class `UAvaPlaybackNode`  
`class UAvaPlaybackNode : public UObject`  
_L23-172_
- reflection: `UCLASS(Abstract)`
- inherits: `UObject`
- desc: Base Class for all the Nodes found in the Motion Design Playback Graph
- L36 _public member_ `static const int32 MaxAllowedChildNodes = 32;`
- L41 _public prototype_ `virtual void PostAllocateNode();` — Called either when the Node has been Constructed (new node) or from Post Load
- L43 _public prototype_ `virtual void BeginDestroy() override;`
- L45 _public prototype_ `UAvaPlaybackGraph* GetPlayback() const;`
- L50 _public prototype_ `virtual FText GetNodeDisplayNameText() const;` — Gets the Display Name of the Node
- L55 _public prototype_ `virtual FText GetNodeCategoryText() const;` — Gets the Display Category of the Node
- L61 _public prototype_ `virtual FText GetNodeTooltipText() const;` — Gets the ToolTip of the Node
- L67 _public function_ `virtual void NotifyPlaybackStateChanged(bool bPlaying)` — Called when the UAvaPlaybackGraph changes its state from Playing <-> Stopped @param  bPlaying The new state of Playback
- L69 _public prototype_ `double GetLastTimeTicked() const;`
- L70 _public prototype_ `double GetChildLastTimeTicked(int32 ChildIndex) const;`
- L77 _public prototype_ `void DryRunNode(TArray<UAvaPlaybackNode*>& InAncestors);` — Handles the 'Dry' run of the Node. This is called when Compiling the Graph. @param  InAncestors A list showing the Ancestors of this Node in order from Root to Parent (e.g. [Root, Grandparent, Parent] )
- L80 _public function_ `virtual void PreDryRun()` — Called before Dry Running the Graph. This is called once per node
- L83 _public function_ `virtual void DryRun(const TArray<UAvaPlaybackNode*>& InAncestors)` — Called while Dry Running the Graph. This can be called multiple times for nodes that are connected to multiple nodes.
- L86 _public function_ `virtual void PostDryRun()` — Called after Dry Running the Graph. This is called once per node
- L95 _public prototype_ `virtual void Tick(float DeltaTime, FAvaPlaybackChannelParameters& ChannelParameters);` — Handles the 'Raw' ticking of the Node. This shouldn't be called directly for ChildNodes. Instead 'TickChild' should be called to feed in extra information about the Tick @param  DeltaTime         Delta Time, in Seconds @param  ChannelParameters The aggregate group of parameters that the child nodes and this node set for Playback
- L104 _public prototype_ `void TickChild(float DeltaTime, int32 ChildIndex, FAvaPlaybackChannelParameters& ChannelParameters);` — Ticks Childs as well as checking if the Child actually made connection to a Player Node If the Ticking results in valid Channel Parameters, then it calls 'NotifyChildNodeSucceeded' @param  DeltaTime         Delta Time, in Seconds @param  ChildIndex        The Index of the Child Node to Tick @param  ChannelParameters The aggregate group of parameters that the child nodes set for Playback
- L111 _public prototype_ `void NotifyChildNodeSucceeded(int32 ChildIndex);` — Called when the Child at ChildIndex, made a connection to a Player Node successfully This updates the Last Ticked Times and stores them both in This Node and the Child Node that caused the connection @param ChildIndex The Index of the Child Node that succeeded
- L116 _public prototype_ `void GetAllNodes(TArray<UAvaPlaybackNode*>& OutPlaybackNodes);` — Recursive call to get all the Nodes connected to this Node (inclusive)
- L119 _public prototype_ `virtual void PostLoad() override;` — UObject interface
- L122 _public prototype_ `static void AddReferencedObjects(UObject* InThis, FReferenceCollector& Collector);`
- L123 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L126 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L127 _public function_ `virtual bool CanBeClusterRoot() const override`
- L128 _public function_ `virtual bool CanBeInCluster() const override`
- L132 _public prototype_ `void SetGraphNode(UEdGraphNode* InGraphNode);`
- L133 _public prototype_ `UEdGraphNode* GetGraphNode() const;`
- L137 _public function_ `virtual bool EditorDryRunGraphOnNodeRefresh(FPropertyChangedEvent& PropertyChangedEvent) const`
- L140 _public prototype_ `void SetChildNodes(TArray<UAvaPlaybackNode*>&& InChildNodes);`
- L142 _public prototype_ `virtual void ReconstructNode();`
- L143 _public prototype_ `virtual void RefreshNode(bool bDryRunGraph = false);`
- L145 _public prototype_ `const TArray<TObjectPtr<UAvaPlaybackNode>>& GetChildNodes() const;`
- L147 _public prototype_ `virtual void CreateStartingConnectors();`
- L148 _public prototype_ `virtual void InsertChildNode(int32 Index);`
- L149 _public prototype_ `virtual void RemoveChildNode(int32 Index);`
- L151 _public function_ `virtual int32 GetMinChildNodes() const`
- L152 _public function_ `virtual int32 GetMaxChildNodes() const`
- L155 _public prototype_ `virtual FName GetInputPinName(int32 InputPinIndex) const;`
- L160 _protected member_ `TArray<TObjectPtr<UAvaPlaybackNode>> ChildNodes;` — `UPROPERTY()`
- L164 _protected member_ `TObjectPtr<UEdGraphNode> GraphNode;` — `UPROPERTY()`
- L167 _protected member_ `FDelegateHandle PlaybackStateChangedHandle;`
- L169 _protected member_ `TMap<int32, double> ChildLastValidTicks;`
- L171 _protected member_ `double LastValidTick = -1.0;`

#### struct `UAvaPlaybackNode::NodeCategory`  
`struct NodeCategory`  
_L29-35_
- L31 _public member_ `static const FText Default;`
- L32 _public member_ `static const FText EventTrigger;`
- L33 _public member_ `static const FText EventAction;`
- L34 _public member_ `static const FText EventFlowControl;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMedia/Public/Playback/Nodes/AvaPlaybackNodePlayer.h` (Public)


#### class `UAvaPlaybackNodePlayer`  
`class UAvaPlaybackNodePlayer : public UAvaPlaybackNode`  
_L16-70_
- reflection: `UCLASS(Abstract)`
- inherits: `UAvaPlaybackNode`
- L21 _public prototype_ `UAvaPlaybackNodePlayer();`
- L23 _public prototype_ `virtual void PostAllocateNode() override;`
- L25 _public function_ `virtual int32 GetMinChildNodes() const override`
- L26 _public function_ `virtual int32 GetMaxChildNodes() const override`
- L29 _public prototype_ `virtual void Tick(float DeltaTime, FAvaPlaybackChannelParameters& ChannelParameters) override;` — Channel Ticking
- L32 _public prototype_ `void TickEventFeed(float DeltaTime);` — Event Ticking
- L33 _public prototype_ `void ResetEvents();`
- L35 _public prototype_ `virtual FText GetNodeDisplayNameText() const override;`
- L36 _public prototype_ `virtual FText GetNodeTooltipText() const override;`
- L39 _public prototype_ `UTextureRenderTarget2D* GetPreviewRenderTarget() const;`
- L42 _public function_ `virtual bool EditorDryRunGraphOnNodeRefresh(FPropertyChangedEvent& PropertyChangedEvent) const override` — Always Dry Run Graph on Changes in Player Node
- L45 _public prototype_ `virtual const FSoftObjectPath& GetAssetPath() const;`
- L47 _public function_ `virtual FAvaSoftAssetPtr GetAssetPtr() const`
- L49 _public function_ `virtual const FString& GetLoadOptions() const`
- L52 _public function_ `const TArray<int32>& GetLastTickChannelIndices() const` — Get the channel indices from the last time this node was traversed.
- L55 _public prototype_ `virtual void SetLoadOptions(const FString& InLoadOptions);` — Set current load options for the asset.
- L60 _protected member_ `FString LoadOptions;` — `UPROPERTY(EditAnywhere, Category = "Motion Design")` — Additional information necessary to load an asset.
- L62 _protected member_ `FText DisplayNameText;`
- L68 _protected member_ `TArray<int32> ChannelIndices;` — Keep track of the channel indices that reach this node during tick traversal. This is then propagated on the event triggers to know which channel(s) the events are coming from.
- L69 _protected member_ `TArray<int32> LastTickChannelIndices;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMedia/Public/Playback/Nodes/AvaPlaybackNodeRoot.h` (Public)


#### class `UAvaPlaybackNodeRoot`  
`class UAvaPlaybackNodeRoot : public UAvaPlaybackNode`  
_L13-46_
- reflection: `UCLASS()`
- inherits: `UAvaPlaybackNode`
- L19 _public prototype_ `virtual void PostAllocateNode() override;`
- L20 _public prototype_ `virtual void BeginDestroy() override;`
- L22 _public prototype_ `void TickRoot(float InDeltaTime, TMap<FName, FAvaPlaybackChannelParameters>& OutPlaybackSettings);`
- L24 _public prototype_ `virtual FText GetNodeDisplayNameText() const override;`
- L25 _public prototype_ `virtual FText GetNodeTooltipText() const override;`
- L27 _public prototype_ `void OnBroadcastChanged(EAvaBroadcastChange InChange);`
- L28 _public prototype_ `void OnChannelChanged(const FAvaBroadcastOutputChannel& InChannel, EAvaBroadcastChannelChange InChange);`
- L30 _public prototype_ `virtual int32 GetMinChildNodes() const override;`
- L31 _public prototype_ `virtual int32 GetMaxChildNodes() const override;`
- L34 _public prototype_ `virtual FName GetInputPinName(int32 InputPinIndex) const override;`
- L37 _public prototype_ `FName GetChannelName(int32 InChannelNameIndex) const;`
- L41 _protected member_ `FDelegateHandle BroadcastChangedHandle;`
- L42 _protected member_ `FDelegateHandle ChannelChangedHandle;`
- L45 _protected member_ `TArray<TObjectPtr<UTextureRenderTarget2D>> RenderTargets;` — `UPROPERTY()`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMedia/Public/Playback/Nodes/Events/Actions/AvaPlaybackAnimations.h` (Public)


#### struct `FAvaPlaybackAnimPlaySettings`  
`struct FAvaPlaybackAnimPlaySettings`  
_L12-63_
- reflection: `USTRUCT()`
- L16 _public function_ `FAvaPlaybackAnimPlaySettings() : FAvaPlaybackAnimPlaySettings(NAME_None)`
- L17 _public function_ `FAvaPlaybackAnimPlaySettings(FName InAnimationName) : AnimationName(InAnimationName)`
- L20 _public member_ `EAvaPlaybackAnimAction Action = EAvaPlaybackAnimAction::None;` — `UPROPERTY(EditAnywhere, Category = "Motion Design")`
- L23 _public member_ `FName AnimationName = NAME_None;` — `UPROPERTY(VisibleAnywhere, Category = "Motion Design")`
- L26 _public member_ `float StartAtTime = 0.0f;` — `UPROPERTY(EditAnywhere, Category = "Motion Design")`
- L29 _public member_ `int32 LoopCount = 0;` — `UPROPERTY(EditAnywhere, Category = "Motion Design")`
- L32 _public member_ `EAvaSequencePlayMode PlayMode = EAvaSequencePlayMode::Forward;` — `UPROPERTY(EditAnywhere, Category = "Motion Design")`
- L35 _public member_ `float PlaybackSpeed = 1.0f;` — `UPROPERTY(EditAnywhere, Category = "Motion Design")`
- L38 _public member_ `bool bRestoreState = false;` — `UPROPERTY(EditAnywhere, Category = "Motion Design")`
- L45 _public function_ `bool operator==(const FAvaPlaybackAnimPlaySettings& Other) const`
- L50 _public function_ `FAvaSequencePlayParams AsPlayParams() const`

#### struct `FAvaPlaybackAnimations`  
`struct FAvaPlaybackAnimations`  
_L66-72_
- reflection: `USTRUCT()`
- L71 _public member_ `TSet<FAvaPlaybackAnimPlaySettings> AvailableAnimations;` — `UPROPERTY(EditAnywhere, Category = "Motion Design")`

#### Free symbols / members of external scopes

- L40 _function_ `friend uint32 GetTypeHash(const FAvaPlaybackAnimPlaySettings& InPlaySettings)`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMedia/Public/Playback/Nodes/Events/AvaPlaybackNodeAction.h` (Public)


#### class `UAvaPlaybackNodeAction`  
`class UAvaPlaybackNodeAction : public UAvaPlaybackNodeEvent`  
_L14-23_
- reflection: `UCLASS(Abstract)`
- inherits: `UAvaPlaybackNodeEvent`
- desc: Node part of the Event Nodes that handles Logic Execution
- L19 _public prototype_ `virtual FText GetNodeCategoryText() const override final;`
- L21 _public function_ `virtual int32 GetMinChildNodes() const override final`
- L22 _public function_ `virtual int32 GetMaxChildNodes() const override final`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMedia/Public/Playback/Nodes/Events/AvaPlaybackNodeEvent.h` (Public)


#### class `UAvaPlaybackNodeEvent`  
`class UAvaPlaybackNodeEvent : public UAvaPlaybackNode`  
_L15-27_
- reflection: `UCLASS(Abstract)`
- inherits: `UAvaPlaybackNode`
- desc: Base Class for all Event Nodes
- L21 _public function_ `virtual void Tick(float DeltaTime, FAvaPlaybackChannelParameters& ChannelParameters) override final` — UAvaPlaybackNode Interface
- L24 _public prototype_ `virtual void TickEvent(float DeltaTime, FAvaPlaybackEventParameters& OutEventParameters);`
- L25 _public function_ `virtual void OnEventTriggered(const FAvaPlaybackEventParameters& InEventParameters)`
- L26 _public function_ `virtual void Reset()`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMedia/Public/Playback/Nodes/Events/AvaPlaybackNodeFlow.h` (Public)


#### class `UAvaPlaybackNodeFlow`  
`class UAvaPlaybackNodeFlow : public UAvaPlaybackNodeEvent`  
_L14-23_
- reflection: `UCLASS(Abstract)`
- inherits: `UAvaPlaybackNodeEvent`
- desc: Node part of the Event Nodes that Controls the Flow of Events
- L19 _public prototype_ `virtual FText GetNodeCategoryText() const override final;`
- L21 _public function_ `virtual int32 GetMinChildNodes() const override final`
- L22 _public function_ `virtual int32 GetMaxChildNodes() const override`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMedia/Public/Playback/Nodes/Events/AvaPlaybackNodeTrigger.h` (Public)


#### class `UAvaPlaybackNodeTrigger`  
`class UAvaPlaybackNodeTrigger : public UAvaPlaybackNodeEvent`  
_L15-31_
- reflection: `UCLASS(Abstract)`
- inherits: `UAvaPlaybackNodeEvent`
- desc: Node part of the Event Nodes that Listens to an Event and Triggers the Event Flow
- L20 _public prototype_ `virtual FText GetNodeCategoryText() const override final;`
- L22 _public function_ `virtual int32 GetMinChildNodes() const override final`
- L23 _public function_ `virtual int32 GetMaxChildNodes() const override final`
- L25 _public prototype_ `virtual void TriggerEvent();`
- L26 _public prototype_ `virtual void Reset() override final;`
- L27 _public prototype_ `virtual void TickEvent(float DeltaTime, FAvaPlaybackEventParameters& OutEventParameters) override;`
- L30 _private member_ `bool bEventTriggered = false;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMedia/Public/Rundown/AvaRundown.h` (Public)


#### struct `FAvaRundownPageInsertPosition`  
`struct FAvaRundownPageInsertPosition`  
_L24-52_
- desc: @brief Defines the insertion position in a page list.
- L31 _public member_ `int32 AdjacentId;` — The position is defined with a page id because it is coupled with the id generation. For the id generator, if an insertion position is defined, we also want the generated ids to be in relation to that.
- L34 _public member_ `bool bAddBelow;` — Defines the insertion position relative to the reference page i.e. above or below the adjacent page.
- L36 _public function_ `explicit FAvaRundownPageInsertPosition(int32 InAdjacentId = FAvaRundownPage::InvalidPageId, bool bInAddBelow = true) : AdjacentId(InAdjacentId), bAddBelow(bInAddBelow)`
- L38 _public function_ `bool IsValid() const`
- L40 _public function_ `bool IsAddAbove() const`
- L42 _public function_ `bool IsAddBelow() const`
- L45 _public function_ `void ConditionalUpdateAdjacentId(int32 InNewAdjacentId)` — Update the id only if it was initially valid.

#### struct `FAvaRundownPageIdGeneratorParams`  
`struct FAvaRundownPageIdGeneratorParams`  
_L59-87_
- desc: Defines the parameters for the page id generator algorithm. The Id generator uses a sequence strategy to search for an unused id. It is defined by a starting id and a search direction.
- L62 _public member_ `int32 ReferenceId;` — Starting Id for the search.
- L69 _public member_ `int32 Increment;` — @brief (Initial) Search increment. @remark For negative increment search, the limit of the search space can be reached. If no unique id is found, the search will continue in the positive direction instead.
- L71 _public function_ `explicit FAvaRundownPageIdGeneratorParams(int32 InReferenceId = FAvaRundownPage::InvalidPageId, int32 InIncrement = 1) : ReferenceId(InReferenceId), Increment(InIncrement)`
- L75 _public function_ `static FAvaRundownPageIdGeneratorParams FromInsertPosition(const FAvaRundownPageInsertPosition& InInsertPosition)` — Operation helper: Determines id generation from the insert parameters.
- L83 _public function_ `static FAvaRundownPageIdGeneratorParams FromInsertPositionOrSourceId(int32 InSourceId, const FAvaRundownPageInsertPosition& InInsertPosition)` — Operation helper: Id generation prefers using insertion parameters (if specified) over source id.

#### struct `FAvaRundownPageListChangeParams`  
`struct FAvaRundownPageListChangeParams`  
_L89-95_
- L91 _public member_ `UAvaRundown* Rundown;`
- L92 _public member_ `FAvaRundownPageListReference PageListReference;`
- L93 _public member_ `EAvaRundownPageListChange ChangeType;`
- L94 _public member_ `TArray<int32> AffectedPages;`

#### struct `FAvaRundownPageCollection`  
`struct FAvaRundownPageCollection`  
_L101-141_
- reflection: `USTRUCT()`
- L106 _public member_ `TArray<FAvaRundownPage> Pages;` — `UPROPERTY()`
- L109 _public member_ `TMap<int32, int32> PageIndices;` — Cache mapping the Page Id to the index where the Page with such Page Id is at
- L111 _public function_ `int32 GetPageIndex(const int32 InPageId) const`
- L121 _public prototype_ `void Empty(UAvaRundown* InRundown, const FAvaRundownPageListReference& InPageListReference);`
- L124 _public function_ `void RefreshPageIndices()` — Complete refresh of the page indices.
- L134 _public function_ `void PostInsertRefreshPageIndices(const int32 InStartAtIndex)` — Refresh page indices after a new page has been inserted at the given index.

#### struct `FAvaRundownSubList`  
`struct FAvaRundownSubList`  
_L144-163_
- reflection: `USTRUCT()`
- L150 _public member_ `FGuid Id;` — `UPROPERTY()` — Unique identifier for the page list.
- L153 _public member_ `TArray<int32> PageIds;` — `UPROPERTY()`
- L157 _public member_ `FText Name;` — `UPROPERTY()` — Display Name
- L159 _public function_ `bool IsValid() const`

#### struct `FAvaRundownPageListPlaybackContext`  
`struct FAvaRundownPageListPlaybackContext`  
_L181-185_
- desc: Carries the context for the playback of a page list. In particular, what is the current play head to be able to move to the next page in the page list. Note: a "rundown" has many page lists and each page lists has 2 play type (preview or program), therefore, we have many instances of this page list context for each page lists and play type within a "rundown" object.
- L184 _public member_ `int32 PlayHeadPageId = FAvaRundownPage::InvalidPageId;` — Keeps track of the page id the play head is on, i.e. this is the last played page.

#### struct `FAvaRundownPageListPlaybackContextCollection`  
`struct FAvaRundownPageListPlaybackContextCollection`  
_L194-227_
- desc: This class is a container for all the page list contexts are rundown can have. The current implementation only keeps track of the play type, i.e. preview vs program. The design for this is not settle yet. The requirement for a page list context per preview channel comes from the rundown server as it may have a preview channel dedicated per client connection, which implies a page list context for each one of them. There is only one "program" page list context for now.
- L196 _public function_ `TSharedPtr<FAvaRundownPageListPlaybackContext> GetContext(bool bInIsPreview, const FName& InPreviewChannelName) const`
- L206 _public function_ `FAvaRundownPageListPlaybackContext& GetOrCreateContext(bool bInIsPreview, const FName& InPreviewChannelName)`
- L213 _protected function_ `TSharedPtr<FAvaRundownPageListPlaybackContext> CreateContext(bool bInIsPreview, const FName& InPreviewChannelName)`
- L225 _protected member_ `TSharedPtr<FAvaRundownPageListPlaybackContext> ProgramContext;`
- L226 _protected member_ `TMap<FName, TSharedPtr<FAvaRundownPageListPlaybackContext>> PreviewContexts;`

#### enum `EAvaRundownPageStopOptions`  
`enum class EAvaRundownPageStopOptions : uint8`  
_L230-244_
- reflection: `UENUM()`
- L235 _public enumerator_ `None = 0` — Default option will stop the page with transitions if available.
- L239 _public enumerator_ `ForceNoTransition = 1 << 1` — Forces the page to stop without transitions.
- L243 _public enumerator_ `Default = None` — Default option will stop the page with transitions if available.

#### class `IAvaRundownPageLoadingManager`  
`class IAvaRundownPageLoadingManager`  
_L250-257_
- desc: @brief Manages page pre-loading.
- L253 _public prototype_ `IAvaRundownPageLoadingManager() = default;`
- L254 _public prototype_ `virtual ~IAvaRundownPageLoadingManager() = default;`
- L256 _public prototype_ `virtual bool RequestLoadPage(int32 InPageId, bool bInIsPreview, const FName& InPreviewChannelName) = 0;`

#### class `UAvaRundown`  
`class UAvaRundown : public UObject`  
_L296-858_
- reflection: `UCLASS(NotBlueprintable, BlueprintType, ClassGroup = "Motion Design Rundown", meta = (DisplayName = "Motion Design Rundown"))`
- inherits: `UObject`
- desc: This class is a container for what could be described as a "show" for broadcast purposes. It goes beyond a simple list of items. It contains the following: - a list of Motion Design Template Pages (or just Templates). - a list of Motion Design Instanced Pages (or just Pages). - a list of page views (or just Views). Workflow: 1- Templates The first step in the work flow consist in importing templates. The source asset is not actually imported in the "show" container, it is just soft referenced. However, the import process will load and cache some information about the template (exposed properties, default values, animations, transition logic layer, etc). Given that this information is cached, it may become stale if the source asset is updated. Therefore, reimporting the templates may be necessary within the normal work flow. Todo: keep a hash of the source asset to determine if it has changed. 2- Pages The pages are instances of the templates, allowing to change the exposed properties and controllers, also selecting an output program channel for the given page. Only one program channel is allowed per page. 3- Page Views Separate page views can be made in order to create "rundowns" for separate segments/parts of a show. "Page Groups" Discussion: "Page Groups" are not implemented. It would be different than page views, i.e. pages could be grouped in either of the page list or page views. Other applications support page grouping to emulate MOS's hierarchy. In the MOS/NCS hierarch
- L301 _public prototype_ `UAvaRundown();`
- L305 _public member_ `static const FAvaRundownPageListReference TemplatePageList;`
- L306 _public member_ `static const FAvaRundownPageListReference InstancePageList;`
- L308 _public function_ `static FAvaRundownPageListReference CreateSubListReference(const FGuid& InSubListId)`
- L313 _public function_ `static FAvaRundownPageListReference CreateSubListReference(const FAvaRundownSubList& InSubList)`
- L319 _protected function_ `bool IsPageIdUnique(int32 InPageId) const`
- L320 _protected prototype_ `int32 GenerateUniquePageId(int32 InReferencePageId = FAvaRundownPage::InvalidPageId, int32 InIncrement = 1) const;`
- L321 _protected prototype_ `int32 GenerateUniquePageId(const FAvaRundownPageIdGeneratorParams& InParams) const;`
- L324 _protected prototype_ `void RefreshPageIndices();` — Caches the Page's Id to its Index in the Pages Array
- L326 _protected prototype_ `void RefreshSubListIndices();`
- L329 _public member_ `static const FAvaRundownSubList InvalidSubList;`
- L330 _public member_ `static FAvaRundownSubList InvalidSubListMutable;`
- L333 _public prototype_ `virtual void BeginDestroy() override;`
- L334 _public prototype_ `virtual void PostLoad() override;`
- L336 _public prototype_ `virtual void PreEditUndo() override;`
- L337 _public prototype_ `virtual void PostEditUndo() override;`
- L338 _public prototype_ `virtual void OnCookEvent(UE::Cook::ECookEvent InCookEvent, UE::Cook::FCookEventContext& InCookContext) override;`
- L343 _public prototype_ `bool IsEmpty() const;` — Returns true if the rundown is empty, i.e. no pages and no templates.
- L349 _public prototype_ `bool Empty();` — Clear the rundown of all it's content. @remark Will be prevented if the rundown is playing.
- L351 _public prototype_ `int32 AddTemplateInternal(const FAvaRundownPageIdGeneratorParams& InIdGeneratorParams, const TFunctionRef<bool(FAvaRundownPage&)> InSetupTemplateFunction);`
- L354 _public prototype_ `int32 AddTemplate(const FAvaRundownPageIdGeneratorParams& InIdGeneratorParams = FAvaRundownPageIdGeneratorParams());` — Add empty template.
- L360 _public prototype_ `int32 AddComboTemplate(const TArray<int32>& InTemplateIds, const FAvaRundownPageIdGeneratorParams& InIdGeneratorParams = FAvaRundownPageIdGeneratorParams());` — Creates a combination template which combines other templates. @remark This function does not validate the templates, use ValidateTemplateIdsForComboTemplate independently.
- L372 _public prototype_ `TArray<int32> ValidateTemplateIdsForComboTemplate(const TArray<int32>& InTemplateIds, FOutputDevice& InErrorLog);` — Combo Templates have specific requirement for the sub-templates. This function validates a given list of templates to use as sub-templates for a combo template. A combination template can only be created using transition logic templates that are on different transition layers. @param InTemplateIds Templates to validate. @param InErrorLog Used to log the reasons for invalid templates. @return validated template Ids.
- L383 _public prototype_ `TArray<int32> AddTemplates(const TArray<FAvaRundownPage>& InSourceTemplates);` — @brief Add templates from existing source. @param InSourceTemplates Source template to add. @return The new template Ids created. For the id generation, it will attempt to reuse the source ids, but in case of collision, new ids are generated with the positive increment sequence search method.
- L390 _public prototype_ `TArray<int32> AddPagesFromTemplates(const TArray<int32>& InTemplateIds);` — @brief Create new pages in the page list for teh given template Ids. @param InTemplateIds Templates to use for each page. A new page is created for each entry in that array. @return The new page Ids created.
- L399 _public prototype_ `int32 AddPageFromTemplate(int32 InTemplateId, const FAvaRundownPageIdGeneratorParams& InIdGeneratorParams = FAvaRundownPageIdGeneratorParams(), const FAvaRundownPageInsertPosition& InInsertAt = FAvaRundownPageInsertPosition());` — @brief Creates a new page in the page list using the given template. @param InTemplateId Reference to the template to use for that page. @param InIdGeneratorParams Defines how the page id is going to be generated. @param InInsertAt Specifies the insertion location in the page list (i.e. the index in the page list). @return Returns the page Id of the created page.
- L401 _public prototype_ `bool CanAddPage() const;`
- L403 _public prototype_ `bool CanChangePageOrder() const;`
- L405 _public prototype_ `bool ChangePageOrder(const FAvaRundownPageListReference& InPageListReference, const TArray<int32>& InPageIndices);` — Reorders the pages, swapping the old indices for the new ones.
- L407 _public prototype_ `bool RemovePage(int32 InPageId);`
- L408 _public prototype_ `bool CanRemovePage(int32 InPageId) const;`
- L411 _public prototype_ `int32 RemovePages(const TArray<int32>& InPageIds);` — Remove all the Pages in the Array. Returns the number of Pages removed.
- L412 _public prototype_ `bool CanRemovePages(const TArray<int32>& InPageIds) const;`
- L414 _public prototype_ `bool RenumberPageIds(const TArray<int32>& InPageIds, const FAvaRundownPageIdGeneratorParams& InIdParams);`
- L415 _public prototype_ `bool RenumberPageId(int32 InPageId, int32 InNewPageId);`
- L416 _public prototype_ `bool CanRenumberPageId(int32 InPageId) const;`
- L417 _public prototype_ `bool CanRenumberPageId(int32 InPageId, int32 InNewPageId) const;`
- L419 _public prototype_ `bool SetRemoteControlEntityValue(int32 InPageId, const FGuid& InId, const FAvaPlayableRemoteControlValue& InValue);`
- L420 _public prototype_ `bool SetRemoteControlControllerValue(int32 InPageId, const FGuid& InId,const FAvaPlayableRemoteControlValue& InValue);`
- L421 _public prototype_ `EAvaPlayableRemoteControlChanges UpdateRemoteControlValues(int32 InPageId, const FAvaPlayableRemoteControlValues& InRemoteControlValues, bool bInUpdateDefaults);`
- L423 _public prototype_ `EAvaPlayableRemoteControlChanges ResetRemoteControlValues(int32 InPageId, bool bInUseTemplateValues, bool bInIsDefault);`
- L424 _public prototype_ `EAvaPlayableRemoteControlChanges ResetRemoteControlControllerValue(int32 InPageId, const FGuid& InControllerId, bool bInUseTemplateValues, bool bInIsDefault);`
- L425 _public prototype_ `EAvaPlayableRemoteControlChanges ResetRemoteControlEntityValue(int32 InPageId, const FGuid& InEntityId, bool bInUseTemplateValues, bool bInIsDefault);`
- L427 _public prototype_ `void InvalidateManagedInstanceCacheForPages(const TArray<int32>& InPageIds) const;`
- L429 _public prototype_ `void UpdateAssetForPages(const TArray<int32>& InPageIds, bool bInReimportPage);`
- L431 _public prototype_ `const FAvaRundownPage& GetPage(int32 InPageId) const;`
- L432 _public prototype_ `FAvaRundownPage& GetPage(int32 InPageId);`
- L433 _public function_ `const FAvaRundownPageCollection& GetTemplatePages() const`
- L434 _public function_ `const FAvaRundownPageCollection& GetInstancedPages() const`
- L435 _public function_ `static const FAvaRundownPage& GetPageSafe(const UAvaRundown* InRundown, int32 InPageId)`
- L443 _public prototype_ `const FAvaRundownPage& GetNextPage(int32 InPageId, const FAvaRundownPageListReference& InPageListReference) const;` — Gets the page following the page with the given page id in the given page list. If the given page is not in the given list, the returned page is invalid.
- L449 _public prototype_ `FAvaRundownPage& GetNextPage(int32 InPageId, const FAvaRundownPageListReference& InPageListReference);` — Gets the page following the page with the given page id in the given page list. If the given page is not in the given list, the returned page is invalid.
- L452 _public function_ `const FAvaRundownPage& GetNextPage(int32 InPageId) const` — Gets the page following the page with the given page id. Using current active page list.
- L455 _public function_ `FAvaRundownPage& GetNextPage(int32 InPageId)` — Gets the page following the page with the given page id. Using current active page list.
- L457 _public function_ `FOnAvaRundownPageListChanged& GetOnPageListChanged()`
- L458 _public function_ `FOnAvaRundownPagesChanged& GetOnPagesChanged()`
- L461 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnCanClosePlaybackContext, const UAvaRundown*, bool& );` — Delegate called to determine if the playback context can be closed.
- L462 _public function_ `FOnCanClosePlaybackContext::RegistrationType& GetOnCanClosePlaybackContext() const`
- L470 _public prototype_ `void InitializePlaybackContext();` — Since the playback context is part of the asset for now, there is an explicit call to initialize it. This would be done by the editor (or server). A future refactor will extract the rundown "player" functionality in another class and it will be possible to create multiple instance of a rundown player for the same rundown.
- L475 _public prototype_ `bool CanClosePlaybackContext() const;` — Determines if the playback context can be closed.
- L481 _public prototype_ `void ClosePlaybackContext(bool bInStopAllPages);` — Similarly, when the editor is done, it can close the playback context. This will clean up the internal structures for playback and optionally stop all the pages.
- L486 _public prototype_ `bool IsPlaying() const;` — Returns true if the any page is either playing or previewing.
- L489 _public prototype_ `bool IsPagePreviewing(int32 InPageId) const;` — Returns true if the page with the given page Id is being previewed (in any preview channel).
- L492 _public prototype_ `bool IsPagePlaying(int32 InPageId) const;` — Returns true if the page is playing in it's assigned program channel.
- L494 _public function_ `bool IsPagePlaying(const FAvaRundownPage& InPage) const`
- L496 _public prototype_ `bool IsPagePlayingOrPreviewing(int32 InPageId) const;`
- L498 _public prototype_ `bool UnloadPage(int32 InPageId, const FString& InChannelName);`
- L510 _public prototype_ `TArray<FLoadedInstanceInfo> LoadPage(int32 InPageId, bool bInPreview, const FName& InPreviewChannelName);` — @brief Preload the given page so it has an asset ready for playback. @return UUIDs (and asset paths) of the playback instances that where loaded (or are scheduled for loading).
- L520 _public prototype_ `TArray<int32> PlayPages(const TArray<int32>& InPageIds, EAvaRundownPagePlayType InPlayType, EAvaRundownPagePlaySource InSource = EAvaRundownPagePlaySource::Default);` — @brief Start the playback of the asset defined in the given pages. @remark If the play type is a preview, the default preview channel is used. @param InPageIds Rundown's pages to play out. @param InPlayType Either play on program or preview @param InSource the source that requested to play pages @return page Ids that where started.
- L531 _public prototype_ `TArray<int32> PlayPages(const TArray<int32>& InPageIds, EAvaRundownPagePlayType InPlayType, const FName& InPreviewChannelName, EAvaRundownPagePlaySource InSource = EAvaRundownPagePlaySource::Default);` — @brief Start the playback of the asset defined in the given pages. @remark If the play type is a preview, the given preview channel is used. @param InPageIds Rundown's pages to play out. @param InPlayType Either play on program or preview @param InPreviewChannelName Channel to use for preview. Only used if play type is preview. @param InSource the source that requested to play pages @return page Ids that where started.
- L533 _public prototype_ `bool PlayPage(int32 InPageId, EAvaRundownPagePlayType InPlayType, EAvaRundownPagePlaySource InSource = EAvaRundownPagePlaySource::Default);`
- L534 _public prototype_ `bool PlayPage(int32 InPageId, EAvaRundownPagePlayType InPlayType, const FName& InPreviewChannelName, EAvaRundownPagePlaySource InSource = EAvaRundownPagePlaySource::Default);`
- L536 _public prototype_ `bool CanPlayPage(int32 InPageId, bool bInPreview) const;`
- L537 _public prototype_ `bool CanPlayPage(int32 InPageId, bool bInPreview, const FName& InPreviewChannelName, FString* OutFailureReason) const;`
- L539 _public prototype_ `TArray<int32> StopPages(const TArray<int32>& InPageIds, EAvaRundownPageStopOptions InOptions, bool bInPreview);`
- L540 _public prototype_ `TArray<int32> StopPages(const TArray<int32>& InPageIds, EAvaRundownPageStopOptions InOptions, bool bInPreview, const FName& InPreviewChannelName);`
- L542 _public function_ `bool StopPage(int32 InPageId, EAvaRundownPageStopOptions InOptions, bool bInPreview)`
- L543 _public function_ `bool StopPage(int32 InPageId, EAvaRundownPageStopOptions InOptions, bool bInPreview, const FName& InPreviewChannelName)`
- L545 _public prototype_ `bool CanStopPage(int32 InPageId, EAvaRundownPageStopOptions InOptions, bool bInPreview) const;`
- L546 _public prototype_ `bool CanStopPage(int32 InPageId, EAvaRundownPageStopOptions InOptions, bool bInPreview, const FName& InPreviewChannelName, FString* OutFailureReason) const;`
- L554 _public prototype_ `TArray<int32> StopLayers(FName InChannelName, const TArray<FAvaTagHandle>& InLayers, EAvaRundownPageStopOptions InOptions);` — Stop the layers of a given channel. If using transition, it will produce a special transition that has only kick out layers. returns the pages that will be affected (totally or partially stopped).
- L557 _public prototype_ `bool CanStopLayer(FName InChannelName, const FAvaTagHandle& InLayer) const;` — Determines if a given layer has something playing that can be stopped.
- L559 _public prototype_ `bool StopChannel(const FString& InChannelName);`
- L560 _public prototype_ `bool CanStopChannel(const FString& InChannelName) const;`
- L562 _public prototype_ `bool ContinuePage(int32 InPageId, bool bInPreview);`
- L563 _public prototype_ `bool ContinuePage(int32 InPageId, bool bInPreview, const FName& InPreviewChannelName);`
- L565 _public prototype_ `bool CanContinuePage(int32 InPageId, bool bInPreview) const;`
- L566 _public prototype_ `bool CanContinuePage(int32 InPageId, bool bInPreview, const FName& InPreviewChannelName) const;`
- L569 _public prototype_ `bool RestorePlaySubPage(int32 InPageId, int32 InSubPageIndex, const FGuid& InExistingInstanceId, bool bInIsPreview, const FName& InPreviewChannelName);` — Used to reconcile playing state with a remote playback if connection was lost.
- L571 _public prototype_ `FAvaRundownPageListReference AddSubList();`
- L573 _public prototype_ `bool RemoveSubList(const FAvaRundownPageListReference& InPageListReference);`
- L575 _public prototype_ `bool RenameSubList(const FAvaRundownPageListReference& InPageListReference, const FText& InNewName);`
- L581 _public prototype_ `TArray<int32> GetPlayingPageIds(const FName InProgramChannelName = NAME_None) const;` — Return the current playing Page Ids on the specified program channel. If program channel is none, returns all playing pages on all program channels.
- L587 _public prototype_ `TArray<int32> GetPreviewingPageIds(const FName InPreviewChannelName = NAME_None) const;` — Return the current previewing Page Ids on the specified preview channel. If preview channel is none, returns all previewing pages on all channels.
- L589 _public function_ `const FAvaRundownPageListReference& GetActivePageListReference() const`
- L591 _public prototype_ `bool SetActivePageList(const FAvaRundownPageListReference& InPageListReference);`
- L594 _public prototype_ `bool HasActiveSubList() const;` — Returns true only if a sub list, not the main list, is active.
- L596 _public function_ `const FAvaRundownSubList& GetActiveSubList() const`
- L597 _public function_ `FAvaRundownSubList& GetActiveSubList()`
- L599 _public prototype_ `const FAvaRundownSubList& GetSubList(int32 InSubListIndex) const;`
- L600 _public prototype_ `FAvaRundownSubList& GetSubList(int32 InSubListIndex);`
- L602 _public prototype_ `const FAvaRundownSubList& GetSubList(const FGuid& InSubListId) const;`
- L603 _public prototype_ `FAvaRundownSubList& GetSubList(const FGuid& InSubListId);`
- L605 _public function_ `const FAvaRundownSubList& GetSubList(const FAvaRundownPageListReference& InPageListReference) const`
- L610 _public function_ `FAvaRundownSubList& GetSubList(const FAvaRundownPageListReference& InPageListReference)`
- L615 _public prototype_ `int32 GetSubListIndex(const FAvaRundownSubList& InSubList) const;`
- L617 _public prototype_ `bool IsValidSubList(const FAvaRundownPageListReference& InPageListReference) const;`
- L619 _public function_ `const TArray<FAvaRundownSubList>& GetSubLists() const`
- L621 _public prototype_ `bool AddPageToSubList(const FAvaRundownPageListReference& InPageListReference, int32 InPageId, const FAvaRundownPageInsertPosition& InInsertPosition = FAvaRundownPageInsertPosition());`
- L622 _public prototype_ `bool AddPagesToSubList(const FAvaRundownPageListReference& InPageListReference, const TArray<int32>& InPages);`
- L624 _public prototype_ `int32 RemovePagesFromSubList(const FAvaRundownPageListReference& InPageListReference, const TArray<int32>& InPages);`
- L626 _public function_ `DECLARE_MULTICAST_DELEGATE(FOnActiveListChanged) FOnActiveListChanged& GetOnActiveListChanged()`
- L629 _public function_ `UTextureRenderTarget2D* GetPreviewRenderTarget() const`
- L630 _public prototype_ `UTextureRenderTarget2D* GetPreviewRenderTarget(const FName& InPreviewChannel) const;`
- L633 _public prototype_ `static FName GetDefaultPreviewChannelName();` — Returns the currently selected preview channel (from the settings).
- L636 _public prototype_ `void OnParentWordBeginTearDown();` — Clean up playing status on a system tear down.
- L649 _public prototype_ `bool PushRuntimeRemoteControlEvents(TConstArrayView<FGuid> InControllerIds, int32 InPageId, bool bInPushToProgram, bool bInPushToPreview, FName InPreviewChannelName = NAME_None);` — Push an RC event on the given controllers for the given page. The propagation to channels in determined by rundown settings. @param InControllerIds List of rc controller ids that should be triggered. @param InPageId Page id these events apply to. @param bInPushToProgram if true, the command will be pushed to page's program channel (if currently playing). @param bInPushToPreview if true, the command will be pushed to preview channel(s). @param InPreviewChannelName Allow to specify a specific preview channel to push to. If left none, will push to all preview channel this page is playing in. @return true if the event command was pushed to the corresponding playback instance.
- L655 _public prototype_ `bool PushRuntimeRemoteControlValues(int32 InPageId, bool bInIsPreview, const FName& InPreviewChannelName = NAME_None) const;` — Push the page's RC values to the runtime playback instances. @remark If updating preview, will update all preview channels by default.
- L657 _public prototype_ `void NotifyPageRemoteControlValueChanged(int32 InPageId, EAvaPlayableRemoteControlChanges InRemoteControlChanges);`
- L659 _public function_ `void NotifyPageStopped(int32 InPageId) const`
- L664 _public function_ `void NotifyPageSequenceFinished(int32 InPageId)`
- L670 _public prototype_ `void NotifyPIEEnded(const bool);`
- L673 _public prototype_ `FAvaPlaybackManager& GetPlaybackManager() const;`
- L676 _public function_ `IAvaRundownPageLoadingManager& GetPageLoadingManager()` — Access the page loading manager for this rundown.
- L682 _protected prototype_ `int32 AddPageFromTemplateInternal(int32 InTemplateId, const FAvaRundownPageIdGeneratorParams& InIdGeneratorParams = FAvaRundownPageIdGeneratorParams(), const FAvaRundownPageInsertPosition& InInsertAt = FAvaRundownPageInsertPosition());`
- L684 _protected prototype_ `void InitializePage(FAvaRundownPage& InOutPage, int32 InPageId, int32 InTemplateId) const;`
- L690 _protected prototype_ `bool IsChannelTypeCompatibleForRequest(const FAvaRundownPage& InSelectedPage, bool bInIsPreview, const FName& InPreviewChannelName, FString* OutFailureReason) const;` — Returns true if the selected page can play on the given channel. This enforces that the channel type (program or preview) is compatible with the requested operation.
- L693 _private prototype_ `void OnPlayPages(const TArray<int32>& InPlayedPageIds, EAvaRundownPagePlayType InPlayType, FName InPreviewChannelName, EAvaRundownPagePlaySource InSource);`
- L695 _private prototype_ `IAvaRundownPageLoadingManager& MakePageLoadingManager();`
- L697 _private prototype_ `bool PlayPageWithTransition(FAvaRundownPageTransitionBuilder& InBuilder, const FAvaRundownPage& InPage, EAvaRundownPagePlayType InPlayType, bool bInIsPreview, const FName& InPreviewChannelName);`
- L698 _private prototype_ `bool StopPageNoTransition(const FAvaRundownPage& InPage, bool bInPreview, const FName& InPreviewChannelName);`
- L699 _private prototype_ `bool StopPageWithTransition(FAvaRundownPageTransitionBuilder& InBuilder, const FAvaRundownPage& InPage, bool bInPreview, const FName& InPreviewChannelName);`
- L701 _private prototype_ `const FAvaRundownPage& GetNextFromPages(const TArray<FAvaRundownPage>& InPages, int32 InStartingIndex) const;`
- L702 _private prototype_ `FAvaRundownPage& GetNextFromPages(TArray<FAvaRundownPage>& InPages, int32 InStartingIndex) const;`
- L704 _private prototype_ `const FAvaRundownPage& GetNextFromSubList(const TArray<int32>& InSubListIds, int32 InStartingIndex) const;`
- L705 _private prototype_ `FAvaRundownPage& GetNextFromSubList(const TArray<int32>& InSubListIds, int32 InStartingIndex);`
- L709 _protected member_ `TArray<FAvaRundownPage> Pages_DEPRECATED;` — `UPROPERTY()`
- L712 _protected member_ `FAvaRundownPageCollection TemplatePages;` — `UPROPERTY()`
- L715 _protected member_ `FAvaRundownPageCollection InstancedPages;` — `UPROPERTY()`
- L718 _protected member_ `TArray<FAvaRundownSubList> SubLists;` — `UPROPERTY()`
- L722 _protected member_ `FAvaRundownPageListReference ActivePageList = InstancePageList;` — `UPROPERTY(Transient, DuplicateTransient, TextExportTransient)` — ==InstancePageList Indicates that the entire list is being played, rather than a specific view.
- L732 _protected member_ `TArray<TObjectPtr<UAvaRundownPagePlayer>> PagePlayers;` — `UPROPERTY(Transient, DuplicateTransient, TextExportTransient)` — Keeping track of playing pages. Note: For the rundown editor, we can only preview one page on the selected preview channel, however, rundown server will eventually require that more than one page is previewed on different preview channels for different connected clients.
- L735 _protected member_ `TArray<TObjectPtr<UAvaRundownPageTransition>> PageTransitions;` — `UPROPERTY(Transient, DuplicateTransient, TextExportTransient)`
- L737 _protected member_ `TUniquePtr<FAvaRundownPageListPlaybackContextCollection> PageListPlaybackContextCollection;`
- L739 _protected member_ `TUniquePtr<IAvaRundownPageLoadingManager> PageLoadingManager;`
- L745 _protected member_ `TPimplPtr<FAvaRundownPlaybackClientWatcher> PlaybackClientWatcher;`
- L748 _protected prototype_ `void AddPagePlayer(UAvaRundownPagePlayer* InPagePlayer);`
- L751 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnPagePlayerEvent, UAvaRundown*, UAvaRundownPagePlayer*);`
- L756 _public member_ `FOnPagePlayerEvent OnPagePlayerAdded;` — Rundown Player Event - Called when a new page player is added to the playback context.
- L761 _public member_ `FOnPagePlayerEvent OnPagePlayerRemoving;` — Rundown Player Event - Called when a stopped page player is about to be removed from the playback context.
- L763 _public function_ `FOnPagePlayerEvent& GetOnPagePlayerAdded()`
- L764 _public function_ `FOnPagePlayerEvent& GetOnPagePlayerRemoving()`
- L766 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnPageTransitionEvent, UAvaRundown*, UAvaRundownPageTransition*);`
- L771 _public member_ `FOnPageTransitionEvent OnPageTransitionAdded;` — Rundown Transition Event - Called when a new page transition is added to the playback context.
- L776 _public member_ `FOnPageTransitionEvent OnPageTransitionRemoving;` — Rundown Transition Event - Called when a completed page transition is about to be removed from the playback context.
- L778 _public function_ `FOnPageTransitionEvent& GetOnPageTransitionAdded()`
- L779 _public function_ `FOnPageTransitionEvent& GetOnPageTransitionRemoving()`
- L781 _public function_ `void AddPageTransition(UAvaRundownPageTransition* InPageTransition)`
- L787 _public function_ `void RemovePageTransition(UAvaRundownPageTransition* InPageTransition)`
- L793 _public prototype_ `UAvaRundownPageTransition* GetPageTransition(const FGuid& InTransitionId) const;`
- L795 _public prototype_ `bool CanStartTransitionForPage(const FAvaRundownPage& InPage, bool bInIsPreview, const FName& InPreviewChannelName, FString* OutFailureReason) const;`
- L801 _public prototype_ `int32 StopPageTransitionsForPage(const FAvaRundownPage& InPage, bool bInIsPreview, const FName& InPreviewChannelName);` — Stop transitions involving the given page playing in the specified channel. @return number of transitions stopped.
- L807 _public prototype_ `int32 StopPageTransitionsForChannel(const FName InChannelName);` — Stop all current transitions in the specified channel. @return number of transitions stopped.
- L813 _public prototype_ `int32 StopPageTransitionsByPredicate(TFunctionRef<bool(UAvaRundownPageTransition*)> InPredicate);` — Stop transitions that return true for the given predicate. @return number of transitions stopped.
- L815 _public function_ `const TArray<TObjectPtr<UAvaRundownPagePlayer>>& GetPagePlayers() const`
- L817 _public prototype_ `UAvaRundownPagePlayer* FindPlayerForProgramPage(int32 InPageId) const;`
- L819 _public prototype_ `UAvaRundownPagePlayer* FindPlayerForPreviewPage(int32 InPageId, const FName& InPreviewChannelFName) const;`
- L821 _public function_ `UAvaRundownPagePlayer* FindPlayerForPage(int32 InPageId, bool bInIsPreview, const FName& InPreviewChannelName) const`
- L827 _public prototype_ `UAvaRundownPagePlayer* FindPagePlayer(int32 InPageId, FName InChannelName) const;` — Finds the page player for the given pageId and channel name.
- L829 _public prototype_ `void RemoveStoppedPagePlayers();`
- L831 _public function_ `FAvaRundownPageListPlaybackContextCollection* GetPageListPlaybackContextCollection() const`
- L836 _public function_ `FAvaRundownPageListPlaybackContextCollection& GetOrCreatePageListPlaybackContextCollection()`
- L847 _protected member_ `FOnAvaRundownPagesChanged OnPagesChanged;`
- L848 _protected member_ `FOnAvaRundownPageListChanged OnPageListChanged;`
- L849 _protected member_ `FOnActiveListChanged OnActiveListChanged;`
- L850 _protected member_ `mutable FOnCanClosePlaybackContext OnCanClosePlaybackContext;`
- L852 _protected member_ `TMap<FGuid, int32> SubListIndices;`
- L856 _protected member_ `TPimplPtr<FPreUndoBackup> PreUndoBackup;`

#### struct `UAvaRundown::FLoadedInstanceInfo`  
`struct FLoadedInstanceInfo`  
_L500-504_
- L502 _public member_ `FGuid InstanceId;`
- L503 _public member_ `FSoftObjectPath AssetPath;`

#### Free symbols / members of external scopes

- L11 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogAvaRundown, Log, All);`
- L97 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnAvaRundownPageListChanged, const FAvaRundownPageListChangeParams&) DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnAvaRundownPagesChanged, const UAvaRundown*, const FAvaRundownPage&, EAvaRundownPageChanges) USTRUCT() struct FAvaRundownPageCollection { GENERATED_BODY() UPROPERTY() TArray<FAvaRundownPage> Pages; TMap<int32, int32> PageIndices; int32 GetPageIndex(const int32 InPageId) const { if (InPageId != FAvaRundownPage::InvalidPageId) { const int32* PageIndex = PageIndices.Find(InPageId); return PageIndex ? *PageIndex : INDEX_NONE; } return INDEX_NONE; } void Empty(UAvaRundown* InRundown, const FAvaRundownPageListReference& InPageListReference); void RefreshPageIndices() { PageIndices.Empty(Pages.Num()); for (int32 Index = 0; Index < Pages.Num(); ++Index) { PageIndices.Add(Pages[Index].GetPageId(), Index); } } void PostInsertRefreshPageIndices(const int32 InStartAtIndex) { for (int32 Index = InStartAtIndex; Index < Pages.Num(); ++Index)`
- L98 _delegate_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnAvaRundownPagesChanged, const UAvaRundown*, const FAvaRundownPage&, EAvaRundownPageChanges) USTRUCT() struct FAvaRundownPageCollection { GENERATED_BODY() UPROPERTY() TArray<FAvaRundownPage> Pages; TMap<int32, int32> PageIndices; int32 GetPageIndex(const int32 InPageId) const { if (InPageId != FAvaRundownPage::InvalidPageId) { const int32* PageIndex = PageIndices.Find(InPageId); return PageIndex ? *PageIndex : INDEX_NONE; } return INDEX_NONE; } void Empty(UAvaRundown* InRundown, const FAvaRundownPageListReference& InPageListReference); void RefreshPageIndices() { PageIndices.Empty(Pages.Num()); for (int32 Index = 0; Index < Pages.Num(); ++Index) { PageIndices.Add(Pages[Index].GetPageId(), Index); } } void PostInsertRefreshPageIndices(const int32 InStartAtIndex) { for (int32 Index = InStartAtIndex; Index < Pages.Num(); ++Index) {`
- L165 _namespace_ `namespace UE`
- L165 _namespace_ `namespace AvaRundown` (scope `UE`)
- L167 _function_ `inline bool IsPreviewPlayType(EAvaRundownPagePlayType InPlayType)` (scope `UE::AvaRundown`)
- L245 _prototype_ `ENUM_CLASS_FLAGS(EAvaRundownPageStopOptions);`
- L461 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnCanClosePlaybackContext, const UAvaRundown*, bool& );` — Delegate called to determine if the playback context can be closed.
- L626 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnActiveListChanged) FOnActiveListChanged& GetOnActiveListChanged() { return OnActiveListChanged; } UTextureRenderTarget2D* GetPreviewRenderTarget() const { return GetPreviewRenderTarget(GetDefaultPreviewChannelName());} UTextureRenderTarget2D* GetPreviewRenderTarget(const FName& InPreviewChannel) const;`
- L751 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnPagePlayerEvent, UAvaRundown*, UAvaRundownPagePlayer*);`
- L766 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnPageTransitionEvent, UAvaRundown*, UAvaRundownPageTransition*);`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMedia/Public/Rundown/AvaRundownDefines.h` (Public)


#### enum `EAvaRundownPagePlayType`  
`enum class EAvaRundownPagePlayType : uint8`  
_L8-13_
- reflection: `UENUM(BlueprintType, DisplayName = "Motion Design Rundown Page Play Type")`
- L10 _public enumerator_ `PlayFromStart`
- L11 _public enumerator_ `PreviewFromStart`
- L12 _public enumerator_ `PreviewFromFrame`

#### enum `EAvaRundownPagePlaySource`  
`enum class EAvaRundownPagePlaySource : uint8`  
_L17-29_
- reflection: `UENUM()`
- desc: Indicates the source that initiated play pages
- L20 _public enumerator_ `Undefined` — Undefined source
- L22 _public enumerator_ `Editor` — The rundown editor initiated the request
- L24 _public enumerator_ `Server` — The rundown server initiated the request
- L26 _public enumerator_ `Component` — The rundown component initiated the request
- L28 _public enumerator_ `Default = Undefined`

#### enum `UE::AvaMedia::Rundown::(anonymous)`  
`enum`  
_L33-33_

#### Free symbols / members of external scopes

- L31 _namespace_ `namespace UE`
- L31 _namespace_ `namespace AvaMedia` (scope `UE`)
- L31 _namespace_ `namespace Rundown` (scope `UE::AvaMedia`)
- L33 _enumerator_ `enum { InvalidPageId = -1};` (scope `UE::AvaMedia::Rundown::__anon99d348eb0103`)

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMedia/Public/Rundown/AvaRundownMacroCollection.h` (Public)


#### struct `FAvaRundownMacroCommand`  
`struct FAvaRundownMacroCommand`  
_L10-19_
- reflection: `USTRUCT()`
- L15 _public member_ `FName Name;` — `UPROPERTY(EditAnywhere, Category="Command")`
- L18 _public member_ `FString Arguments;` — `UPROPERTY(EditAnywhere, Category="Command")`

#### struct `FAvaRundownMacroKeyBinding`  
`struct FAvaRundownMacroKeyBinding`  
_L25-40_
- reflection: `USTRUCT()`
- desc: Defines a macro (list of commands) that is assigned to a shortcut key.
- L31 _public member_ `FString Description;` — `UPROPERTY(EditAnywhere, Category="Macro")` — Macro description
- L35 _public member_ `FInputChord InputChord;` — `UPROPERTY(EditAnywhere, Category="Key")` — Input Key this Macro is bound to.
- L39 _public member_ `TArray<FAvaRundownMacroCommand> Commands;` — `UPROPERTY(EditAnywhere, Category="Commands")` — List of commands this macro will run.

#### class `UAvaRundownMacroCollection`  
`class UAvaRundownMacroCollection : public UObject`  
_L47-60_
- reflection: `UCLASS(NotBlueprintable, BlueprintType, ClassGroup = "Motion Design Rundown", meta = (DisplayName = "Motion Design Rundown Macro Collection"))`
- inherits: `UObject`
- desc: Collection of rundown commands and bindings (either keys or other).
- L52 _public prototype_ `bool HasBindingFor(const FInputChord& InInputChord) const;`
- L54 _public prototype_ `int32 ForEachBinding(const FInputChord& InInputChord, TFunctionRef<bool(const FAvaRundownMacroKeyBinding&)> InCallback) const;`
- L55 _public prototype_ `int32 ForEachCommand(const FInputChord& InInputChord, TFunctionRef<bool(const FAvaRundownMacroCommand&)> InCallback) const;`
- L59 _protected member_ `TArray<FAvaRundownMacroKeyBinding> KeyBindings;` — `UPROPERTY(EditAnywhere, Category="Marcos")`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMedia/Public/Rundown/AvaRundownPage.h` (Public)


#### enum `EAvaRundownPageStatus`  
`enum class EAvaRundownPageStatus : uint8`  
_L18-42_
- reflection: `UENUM()`
- L21 _public enumerator_ `Unknown = 0` — Invalid page status.
- L23 _public enumerator_ `Offline` — Output is offline.
- L25 _public enumerator_ `Missing` — When the page is not available, i.e. the asset is not present in the local content.
- L27 _public enumerator_ `NeedsSync` — Out of date
- L29 _public enumerator_ `Syncing` — Asset is being downloaded.
- L31 _public enumerator_ `Available` — When the page is present in local content, but not loaded.
- L33 _public enumerator_ `Loading` — Load/Start has been requested.
- L35 _public enumerator_ `Loaded` — Page is loaded in memory and ready to play.
- L37 _public enumerator_ `Playing` — Page is currently playing in an output channel.
- L39 _public enumerator_ `Previewing` — Page is currently playing as local preview.
- L41 _public enumerator_ `Error` — Something bad happened.

#### struct `FAvaRundownChannelPageStatus`  
`struct FAvaRundownChannelPageStatus`  
_L45-57_
- reflection: `USTRUCT()`
- L50 _public member_ `EAvaBroadcastChannelType Type = EAvaBroadcastChannelType::Program;` — `UPROPERTY()`
- L53 _public member_ `EAvaRundownPageStatus Status = EAvaRundownPageStatus::Unknown;` — `UPROPERTY()`
- L56 _public member_ `bool bNeedsSync = false;` — `UPROPERTY()`

#### struct `FAvaRundownPageCommandData`  
`struct FAvaRundownPageCommandData`  
_L61-72_
- reflection: `USTRUCT()`
- desc: Page command data is stored in json serialized string in the page to be compatible with external apps.
- L67 _public member_ `FString Name;` — `UPROPERTY(VisibleAnywhere, Category = "Motion Design")` — Command name: string.
- L71 _public member_ `FString Payload;` — `UPROPERTY(VisibleAnywhere, Category = "Motion Design")` — Command payload: json formatted string.

#### struct `FAvaRundownPage`  
`struct FAvaRundownPage`  
_L75-372_
- reflection: `USTRUCT(BlueprintType, DisplayName = "Motion Design Rundown Page")`
- L81 _public member_ `static FAvaRundownPage NullPage;`
- L82 _public member_ `static const int32 InvalidPageId;`
- L84 _public function_ `static bool StatusesContainsStatus(const TArray<FAvaRundownChannelPageStatus>& InStatuses, const TArray<EAvaRundownPageStatus>& InStatusEnums)`
- L97 _public prototype_ `FAvaRundownPage(int32 InPageId = InvalidPageId, int32 InTemplateId = InvalidPageId);`
- L99 _public prototype_ `bool IsValidPage() const;`
- L101 _public prototype_ `void Rename(const FString& InNewName);`
- L102 _public prototype_ `void RenameFriendlyName(const FString& InNewName);`
- L104 _public function_ `int32 GetPageId() const`
- L105 _public function_ `void SetPageId(int32 InPageId)` — Do not use lightly.
- L107 _public function_ `int32 GetTemplateId() const`
- L108 _public function_ `void SetTemplateId(int32 InTemplateId)` — Do not use lightly.
- L109 _public function_ `bool IsTemplate() const`
- L111 _public function_ `const TArray<int32>& GetCombinedTemplateIds() const`
- L112 _public function_ `bool IsComboTemplate() const`
- L114 _public function_ `const TSet<int32>& GetInstancedIds() const`
- L116 _public function_ `void ResetInstancedIds()` — For internal use only.
- L118 _public function_ `const FString& GetPageName() const`
- L119 _public function_ `void SetPageName(const FString& InPageName)`
- L121 _public function_ `bool HasPageSummary() const`
- L122 _public function_ `FText GetPageSummary() const`
- L124 _public function_ `bool HasPageFriendlyName() const`
- L125 _public function_ `void SetPageFriendlyName(const FText& InPageFriendlyName)`
- L126 _public function_ `FText GetPageFriendlyName() const`
- L128 _public prototype_ `FText GetPageDescription() const;`
- L135 _public prototype_ `bool UpdatePageSummary(const UAvaRundown* InRundown);` — @brief Update the page summary (only if summary is empty) @param InRundown Owning rundown. @return true if the summary was generated, false otherwise (either because of an error or it was not needed).
- L138 _public prototype_ `bool UpdatePageSummary(const TArray<const URemoteControlPreset*>& InPresets, bool bInIsPresetChanged = false);` — `UE_DEPRECATED(5.6, "Use the version that provides the rundown.")`
- L147 _public prototype_ `bool UpdatePageSummary(const UAvaRundown* InRundown, const TArray<const URemoteControlPreset*>& InPresets, bool bInForceUpdate = false);` — @brief Update the page summary from controller values or commands. @param InRundown Owning rundown. Necessary to resolve templates. @param InPresets Input presets to get the value from. @param bInForceUpdate Forces the update of the summary even if there is already one. If false, summary is generated only if empty. @return true if the summary was generated, false otherwise (either because of an error or it was not needed).
- L149 _public prototype_ `bool UpdateTransitionLogic();`
- L150 _public prototype_ `bool HasTransitionLogic(const UAvaRundown* InRundown) const;`
- L152 _public prototype_ `FAvaTagHandle GetTransitionLayer(const UAvaRundown* InRundown, int32 InTemplateIndex = 0) const;`
- L153 _public prototype_ `TArray<FAvaTagHandle> GetTransitionLayers(const UAvaRundown* InRundown) const;`
- L155 _public prototype_ `EAvaTransitionInstancingMode GetTransitionMode( const UAvaRundown* InRundown, int32 InTemplateIndex = 0) const;`
- L156 _public prototype_ `TArray<EAvaTransitionInstancingMode> GetTransitionModes(const UAvaRundown* InRundown) const;`
- L165 _public prototype_ `int32 AppendPageProgramStatuses(const UAvaRundown* InParentRundown, TArray<FAvaRundownChannelPageStatus>& OutPageStatuses) const;` — Appends the page's program status(es). Supports multiple statuses per page for forked channels (one status per server including local). The order of the statuses is the same as the outputs (but only once per server) in the channel. @remark Nothing is added if the page is a template. @return The number of program statuses added.
- L174 _public prototype_ `int32 AppendPagePreviewStatuses(const UAvaRundown* InParentRundown, const FName& InPreviewChannelName, TArray<FAvaRundownChannelPageStatus>& OutPageStatuses) const;` — Appends the page's preview status(es) for the given preview channel. Remote channels are not yet supported for preview channels, only local for now. @remark If the preview channel is not specified, it will use the rundown's default preview channel. @remark this api is intended to query extra preview channels (for rundown server). @return The number of preview statuses added.
- L182 _public prototype_ `TArray<FAvaRundownChannelPageStatus> GetPageStatuses(const UAvaRundown* InParentRundown) const;` — Returns all the page's "standard" (program and preview) playback statuses. The order of the status is the same as the outputs in the channel and the preview status is always last. Template pages only have the preview status added.
- L188 _public prototype_ `TArray<FAvaRundownChannelPageStatus> GetPageContextualStatuses(const UAvaRundown* InParentRundown) const;` — Returns either the program statuses or preview statuses only depending if the page is instanced (has a program channel), or a template respectively.
- L194 _public prototype_ `TArray<FAvaRundownChannelPageStatus> GetPageProgramStatuses(const UAvaRundown* InParentRundown) const;` — Returns the page's program statuses. Returns nothing for template pages.
- L200 _public prototype_ `TArray<FAvaRundownChannelPageStatus> GetPagePreviewStatuses(const UAvaRundown* InParentRundown, const FName& InPreviewChannelName = NAME_None) const;` — Returns the page's preview statuses for the given preview channel. If the preview channel is not specified, it will use the rundown's default preview channel.
- L202 _public function_ `bool IsEnabled() const`
- L203 _public function_ `void SetEnabled(bool bInEnabled)`
- L205 _public prototype_ `FSoftObjectPath GetAssetPath(const UAvaRundown* InRundown, int32 InTemplateIndex = 0) const;`
- L206 _public prototype_ `TArray<FSoftObjectPath> GetAssetPaths(const UAvaRundown* InRundown) const;`
- L207 _public function_ `FSoftObjectPath GetAssetPathDirect() const`
- L210 _public prototype_ `bool HasAssets(const UAvaRundown& InRundown) const;` — Returns true if the page has some valid assets.
- L212 _public prototype_ `bool UpdateAsset(const FSoftObjectPath& InAssetPath, bool bInReimportPage = false);`
- L215 _public prototype_ `bool HasCommands(const UAvaRundown* InRundown) const;` — Returns true if the page (or it's template(s)) has commands.
- L217 _public prototype_ `FName GetChannelName() const;`
- L218 _public function_ `int32 GetChannelIndex() const`
- L219 _public prototype_ `void SetChannelName(FName InChannelName);`
- L221 _public prototype_ `EAvaPlayableRemoteControlChanges PruneRemoteControlValues(const FAvaPlayableRemoteControlValues& InRemoteControlValues);`
- L222 _public prototype_ `EAvaPlayableRemoteControlChanges UpdateRemoteControlValues(const FAvaPlayableRemoteControlValues& InRemoteControlValues, bool bInUpdateDefaults);`
- L224 _public function_ `bool HasRemoteControlEntityValue(const FGuid& InId) const`
- L225 _public function_ `const FAvaPlayableRemoteControlValue* GetRemoteControlEntityValue(const FGuid& InId) const`
- L226 _public prototype_ `void SetRemoteControlEntityValue(const FGuid& InId, const FAvaPlayableRemoteControlValue& InValue);`
- L228 _public function_ `bool HasRemoteControlControllerValue(const FGuid& InId) const`
- L229 _public function_ `const FAvaPlayableRemoteControlValue* GetRemoteControlControllerValue(const FGuid& InId) const`
- L230 _public prototype_ `void SetRemoteControlControllerValue(const FGuid& InId, const FAvaPlayableRemoteControlValue& InValue);`
- L232 _public function_ `const FAvaPlayableRemoteControlValues& GetRemoteControlValues() const`
- L233 _public prototype_ `bool GetDefaultRemoteControlValues(const UAvaRundown* InRundown, bool bInUseTemplateValues, FAvaPlayableRemoteControlValues& OutValues) const;`
- L234 _public prototype_ `bool GetDefaultEntityValue(const UAvaRundown* InRundown, const FGuid& InId, bool bInUseTemplateValues, FAvaPlayableRemoteControlValue& OutValue) const;`
- L235 _public prototype_ `bool GetDefaultControllerValue(const UAvaRundown* InRundown, const FGuid& InId, bool bInUseTemplateValues, FAvaPlayableRemoteControlValue& OutValue) const;`
- L237 _public prototype_ `bool IsDefaultEntityValue(const UAvaRundown* InRundown, const FGuid& InId, bool bInUseTemplateValues) const;`
- L238 _public prototype_ `bool IsDefaultControllerValue(const UAvaRundown* InRundown, const FGuid& InId, bool bInUseTemplateValues) const;`
- L240 _public prototype_ `EAvaPlayableRemoteControlChanges ResetRemoteControlValues(const UAvaRundown* InRundown, bool bInUseTemplateValues, bool bInIsDefault);`
- L241 _public prototype_ `EAvaPlayableRemoteControlChanges ResetRemoteControlEntityValue(const UAvaRundown* InRundown, const FGuid& InId, bool bInUseTemplateValues, bool bInIsDefault);`
- L242 _public prototype_ `EAvaPlayableRemoteControlChanges ResetRemoteControlControllerValue(const UAvaRundown* InRundown, const FGuid& InId, bool bInUseTemplateValues, bool bInIsDefault);`
- L249 _public function_ `bool operator<(const FAvaRundownPage& InOther) const`
- L254 _public prototype_ `void PostLoad();`
- L257 _public prototype_ `int32 GetNumTemplates(const UAvaRundown* InRundown) const;` — Returns the number of templates this page/combo template has.
- L263 _public prototype_ `const FAvaRundownPage& GetTemplate(const UAvaRundown* InRundown, int32 InIndex) const;` — Returns the template at given index. This will first resolve the direct template, then lookup combined templates.
- L270 _public prototype_ `const FAvaRundownPage& ResolveTemplate(const UAvaRundown* InRundown) const;` — Resolves a page's templates. For a page, it returns its (direct) template. For a template, it returns itself.
- L277 _public prototype_ `bool IsTemplateMatchingByValue(const FAvaRundownPage& InTemplatePage) const;` — @brief Compare the values from another template and determines if there is a match. @param InTemplatePage Other template page to compare to. @return true if the templates are matching (ignores ids).
- L283 _public prototype_ `void LoadInstancedCommands(const TArray<FAvaRundownPageCommandData>& InCommands);` — Load the instanced commands from the given command data (from web api). @todo Needed until all json serializer can support FInstancedStruct.
- L289 _public prototype_ `TArray<FAvaRundownPageCommandData> SaveInstancedCommands() const;` — Save the instanced commands to command data (suitable for web api). @todo Needed until all json serializer can support FInstancedStruct.
- L295 _public function_ `const TArray<FInstancedStruct>& GetInstancedCommands() const` — @brief Get the instanced page commands. @return array of instanced page commands that can be executed.
- L304 _public prototype_ `void SetInstancedCommands(const TArray<FInstancedStruct>& InInstancedCommands);` — @brief Set the instanced commands. @param InInstancedCommands new instance commands to copy in the page.
- L312 _public prototype_ `void ForEachInstancedCommands(TFunctionRef<void(const FAvaRundownPageCommand&, const FAvaRundownPage&)> InFunction, const UAvaRundown* InRundown, bool bInDirectOnly) const;` — @brief Calls the given function for each commands in the page. @param InFunction Function to call for each command. The Page parameter is the direct page the command is on, i.e. may be the template. @param InRundown Owning rundown (used to resolve templates) @param bInDirectOnly If true, only the current page's command is traversed, otherwise, the templates commands are included as well.
- L316 _protected member_ `bool bEnabled = true;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Motion Design")`
- L319 _protected member_ `int32 PageId = InvalidPageId;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Motion Design")`
- L323 _protected member_ `int32 TemplateId;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Motion Design")` — Page Instance Property: Template Id for this page.
- L331 _protected member_ `TArray<int32> CombinedTemplateIds;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Motion Design")` — Template property: For combination template, lists the templates that are combined. A combination template can only be created using transition logic templates. In order to create a combination template, the templates must be in different transition layers.
- L334 _protected member_ `FString PageName;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Motion Design")`
- L338 _protected member_ `FSoftObjectPath AssetPath;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Motion Design", meta=(AllowedClasses="/Script/Engine.World"))` — Template property: path for this template.
- L342 _protected member_ `TSet<int32> Instances;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Motion Design")` — Template property: List the Ids of all instances.
- L345 _protected member_ `int32 OutputChannel = 0;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Motion Design")`
- L348 _protected member_ `FAvaPlayableRemoteControlValues RemoteControlValues;` — `UPROPERTY(EditAnywhere, Category = "Motion Design")`
- L351 _protected member_ `FText PageSummary = FText::GetEmpty();` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Motion Design")`
- L354 _protected member_ `FText FriendlyName = FText::GetEmpty();` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Motion Design")`
- L358 _protected member_ `bool bHasTransitionLogic = false;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Motion Design")` — Indicate if the template asset has transition logic.
- L362 _protected member_ `FAvaTagHandle TransitionLayerTag;` — `UPROPERTY(VisibleAnywhere, Category = "Motion Design")` — Transition Layer Tag cached from the transition tree. Cached for fast display in page/template list.
- L365 _protected member_ `EAvaTransitionInstancingMode TransitionMode = EAvaTransitionInstancingMode::New;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Motion Design")`
- L371 _protected member_ `TArray<FInstancedStruct> InstancedCommands;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Motion Design", meta = (ExcludeBaseStruct, BaseStruct = "/Script/AvalancheMedia.AvaRundownPageCommand"))` — Page command that can be executed when playing this page.

#### Free symbols / members of external scopes

- L244 _function_ `friend FORCEINLINE uint32 GetTypeHash(const FAvaRundownPage& InPage)`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMedia/Public/Rundown/AvaRundownPageCommand.h` (Public)


#### struct `FAvaRundownPageCommandContext`  
`struct FAvaRundownPageCommandContext`  
_L16-21_
- desc: Base context carrying parameters for page commands execution.
- L18 _public member_ `const UAvaRundown& Rundown;`
- L19 _public member_ `const FAvaRundownPage& Page;`
- L20 _public member_ `const FName ChannelName;`

#### struct `FAvaRundownPageCommand`  
`struct FAvaRundownPageCommand`  
_L28-54_
- reflection: `USTRUCT(BlueprintType)`
- desc: Base class for page commands. @remark this API is experimental.
- L32 _public prototype_ `virtual ~FAvaRundownPageCommand() = default;`
- L35 _public function_ `virtual FText GetDescription() const` — Returns this command's description. Used for page summary.
- L38 _public function_ `virtual bool HasTransitionLogic() const` — Returns true if the command will act as transition logic.
- L41 _public function_ `virtual FString GetTransitionLayerString(const FString& InSeparator) const` — Returns a string representing the transition layers. This is used for the page list "layer" column.
- L44 _public function_ `virtual bool CanExecuteOnPlay(FAvaRundownPageCommandContext& InContext, FString* OutFailureReason) const` — Returns true if the command can be executed. Used by UI for button status.
- L47 _public function_ `virtual bool ExecuteOnPlay(FAvaRundownPageTransitionBuilder& InTransitionBuilder, FAvaRundownPageCommandContext& InContext) const` — Execute the command when a page is played.
- L50 _public function_ `virtual bool CanExecuteOnLoad(FAvaRundownPageCommandContext& InContext, FString* OutFailureReason) const` — Returns true if the command can be executed. Used by UI for button status.
- L53 _public function_ `virtual bool ExecuteOnLoad(FAvaRundownPageCommandContext& InContext, FString& OutLoadOptions) const` — Execute the command when a page is loaded.

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMedia/Public/Rundown/AvaRundownPagePlayer.h` (Public)


#### class `UAvaRundownPlaybackInstancePlayer`  
`class UAvaRundownPlaybackInstancePlayer : public UObject`  
_L23-71_
- reflection: `UCLASS()`
- inherits: `UObject`
- desc: To support combo templates, a page is now potentially composed of a number of playback instances that each have their own player.
- L28 _public prototype_ `UAvaRundownPlaybackInstancePlayer();`
- L31 _public prototype_ `bool Load(const UAvaRundownPagePlayer& InPagePlayer, const UAvaRundown* InRundown, const FAvaRundownPage& InPage, int32 InSubPageIndex, const FGuid& InInstanceId);`
- L32 _public prototype_ `bool IsLoaded() const;`
- L35 _public function_ `void Play(const UAvaRundownPagePlayer& InPagePlayer, const UAvaRundown* InRundown, EAvaRundownPagePlayType InPlayType, bool bInIsUsingTransitionLogic)` — `UE_DEPRECATED(5.6, "Playing a page without a transition is no longuer supported.")`
- L40 _public prototype_ `void Play(const UAvaRundownPagePlayer& InPagePlayer, const UAvaRundown* InRundown, EAvaRundownPagePlayType InPlayType);`
- L41 _public prototype_ `bool IsPlaying() const;`
- L43 _public prototype_ `bool Continue(const FString& InChannelName);`
- L44 _public prototype_ `bool Stop();`
- L46 _public function_ `FAvaPlaybackInstance* GetPlaybackInstance() const`
- L48 _public function_ `FGuid GetPlaybackInstanceId() const`
- L50 _public prototype_ `bool HasPlayable(const UAvaPlayable* InPlayable) const;`
- L52 _public prototype_ `UAvaPlayable* GetFirstPlayable() const;`
- L54 _public prototype_ `UAvaRundownPagePlayer* GetPagePlayer() const;`
- L56 _public prototype_ `void SetPagePlayer(UAvaRundownPagePlayer* InPagePlayer);`
- L60 _public member_ `FAvaTagHandle TransitionLayer;` — `UPROPERTY()`
- L63 _public member_ `FSoftObjectPath SourceAssetPath;` — `UPROPERTY()`
- L66 _public member_ `TObjectPtr<UAvaPlaybackGraph> Playback;` — `UPROPERTY()`
- L68 _public member_ `TSharedPtr<FAvaPlaybackInstance> PlaybackInstance;`
- L70 _public member_ `TWeakObjectPtr<UAvaRundownPagePlayer> ParentPagePlayer;`

#### class `UAvaRundownPagePlayer`  
`class UAvaRundownPagePlayer : public UObject`  
_L74-202_
- reflection: `UCLASS()`
- inherits: `UObject`
- L79 _public prototype_ `UAvaRundownPagePlayer();`
- L83 _public prototype_ `bool Initialize(UAvaRundown* InRundown, const FAvaRundownPage& InPage, bool bInIsPreview, const FName& InPreviewChannel);` — Initialize Page player without loading any playback instances.
- L86 _public prototype_ `bool InitializeAndLoad(UAvaRundown* InRundown, const FAvaRundownPage& InPage, bool bInIsPreview, const FName& InPreviewChannel);` — Initialize the Page player and loads all playback instances.
- L92 _public prototype_ `UAvaRundownPlaybackInstancePlayer* LoadInstancePlayer(int32 InSubPageIndex, const FGuid& InInstanceId);` — Load an instance player for the "sub page" at the given index. The index is the template index in the combo template.
- L95 _public prototype_ `void AddInstancePlayer(UAvaRundownPlaybackInstancePlayer* InExistingInstancePlayer);` — Add a pre-existing instance player to this page player.
- L98 _public prototype_ `bool IsLoaded() const;` — Returns true if at least one of the instance player is loaded, false otherwise.
- L101 _public function_ `bool Play(EAvaRundownPagePlayType InPlayType, bool bInIsUsingTransitionLogic)` — `UE_DEPRECATED(5.6, "Playing a page without a transition is no longuer supported.")`
- L110 _public prototype_ `bool Play(EAvaRundownPagePlayType InPlayType);` — Ensure all the playback instances are playing. Returns true if at least one playback instance is playing, false otherwise.
- L113 _public prototype_ `bool IsPlaying() const;` — Returns true if at least one of the instance player is playing, false otherwise.
- L115 _public prototype_ `bool Continue();`
- L116 _public prototype_ `bool Stop();`
- L118 _public function_ `int32 GetNumInstancePlayers() const`
- L120 _public function_ `FAvaPlaybackInstance* GetPlaybackInstance(int32 InIndex = 0) const`
- L125 _public function_ `FGuid GetPlaybackInstanceId(int32 InIndex = 0) const`
- L130 _public function_ `UAvaPlaybackGraph* GetPlayback(int32 InIndex = 0) const`
- L135 _public function_ `FSoftObjectPath GetSourceAssetPath(int32 InIndex = 0) const`
- L140 _public function_ `UAvaRundownPlaybackInstancePlayer* GetInstancePlayer(int32 InIndex) const`
- L145 _public function_ `void ForEachInstancePlayer(TFunctionRef<void(UAvaRundownPlaybackInstancePlayer*)> InFunction)`
- L153 _public function_ `void ForEachInstancePlayer(TFunctionRef<void(const UAvaRundownPlaybackInstancePlayer*)> InFunction) const`
- L161 _public function_ `UAvaRundown* GetRundown() const`
- L163 _public prototype_ `static int32 GetPageIdFromInstanceUserData(const FString& InUserData);`
- L165 _public prototype_ `static void SetInstanceUserDataFromPage(FAvaPlaybackInstance& InPlaybackInstance, const FAvaRundownPage& InPage);`
- L167 _public prototype_ `bool HasPlayable(const UAvaPlayable* InPlayable) const;`
- L169 _public prototype_ `UAvaRundownPlaybackInstancePlayer* FindInstancePlayerForPlayable(const UAvaPlayable* InPlayable) const;`
- L171 _public prototype_ `UAvaRundownPlaybackInstancePlayer* FindInstancePlayerByInstanceId(const FGuid& InInstanceId) const;`
- L173 _public prototype_ `UAvaRundownPlaybackInstancePlayer* FindInstancePlayerByAssetPath(const FSoftObjectPath& InAssetPath) const;`
- L176 _protected prototype_ `UAvaRundownPlaybackInstancePlayer* CreateAndLoadInstancePlayer(UAvaRundown* InRundown, const FAvaRundownPage& InPage, int32 InSubPageIndex, const FGuid& InInstanceId);`
- L178 _protected prototype_ `void RemoveInstancePlayer(UAvaRundownPlaybackInstancePlayer* InInstancePlayer);`
- L180 _protected prototype_ `void HandleOnPlayableSequenceEvent(UAvaPlayable* InPlayable, FName InSequenceLabel, EAvaPlayableSequenceEventType InEventType);`
- L184 _public member_ `int32 PageId = INDEX_NONE;` — `UPROPERTY()`
- L187 _public member_ `bool bIsPreview = false;` — `UPROPERTY()`
- L191 _public member_ `FName ChannelFName;` — `UPROPERTY()` — @remark For previews, the channel name will not be the one set in the page.
- L195 _public member_ `FString ChannelName;` — `UPROPERTY()` — @remark For previews, the channel name will not be the one set in the page.
- L198 _public member_ `TArray<TObjectPtr<UAvaRundownPlaybackInstancePlayer>> InstancePlayers;` — `UPROPERTY()`
- L201 _protected member_ `TWeakObjectPtr<UAvaRundown> RundownWeak;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMedia/Public/Rundown/IAvaRundownServer.h` (Public)


#### class `IAvaRundownServer`  
`class IAvaRundownServer`  
_L7-20_
- L10 _public prototype_ `virtual ~IAvaRundownServer() = default;`
- L13 _public prototype_ `virtual const FString& GetName() const = 0;` — Returns the server's name.
- L16 _public prototype_ `virtual const FMessageAddress& GetMessageAddress() const = 0;` — Returns the endpoint's message address.
- L19 _public prototype_ `virtual TArray<FMessageAddress> GetClientAddresses() const = 0;` — Returns the list of connected client addresses.
