# Plugins / ImgMediaEditor

- module root: `Plugins/Media/ImgMedia/Source/ImgMediaEditor`
- headers: 11; symbols: 126
- symbol kinds: class=11, delegate=2, function=7, member=51, prototype=53, struct=2
- PrivateDependencyModuleNames: AssetDefinition, ContentBrowser, Core, CoreUObject, DesktopWidgets, EditorFramework, Engine, ImageCore, ImageWrapper, ImgMedia, InputCore, MediaAssets, MediaPlayerEditor, MediaUtils, OpenExrWrapper, RenderCore, Slate, SlateCore, TmvMedia, ToolMenus, UnrealEd, WorkspaceMenuStructure

### `Plugins/Media/ImgMedia/Source/ImgMediaEditor/Private/AssetDefinition/AssetDefinition_ImgMediaSource.h` (Private)


#### class `UAssetDefinition_ImgMediaSource`  
`class UAssetDefinition_ImgMediaSource : public UAssetDefinition_MediaSource`  
_L9-22_
- reflection: `UCLASS()`
- inherits: `UAssetDefinition_MediaSource`
- L14 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L15 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L16 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`

### `Plugins/Media/ImgMedia/Source/ImgMediaEditor/Private/Customizations/ImgMediaFilePathCustomization.h` (Private)


#### class `FImgMediaFilePathCustomization`  
`class FImgMediaFilePathCustomization : public IPropertyTypeCustomization`  
_L15-41_
- inherits: `IPropertyTypeCustomization`
- desc: Implements a customization for the FFilePath class. This will preserve the file path when closing.
- L18 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L20 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L22 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> PropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L29 _private prototype_ `FString HandleFilePathPickerFilePath() const;` — Gets the file path.
- L34 _private prototype_ `void HandleFilePathPickerPathPicked(const FString& PickedPath);` — Called when a path is selected.
- L37 _private member_ `TSharedPtr<IPropertyHandle> PathStringProperty;` — Pointer to the string that will be seet when changing the path
- L40 _private member_ `FString ConfigSettingName;` — Name to save the file path to.

### `Plugins/Media/ImgMedia/Source/ImgMediaEditor/Private/Customizations/ImgMediaSourceCustomization.h` (Private)


#### class `FImgMediaSourceCustomization`  
`class FImgMediaSourceCustomization : public IPropertyTypeCustomization`  
_L20-85_
- inherits: `IPropertyTypeCustomization`
- desc: Implements a details view customization for the UImgMediaSource class.
- L26 _public prototype_ `virtual void CustomizeHeader(TSharedRef<class IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;` — IPropertyTypeCustomization interface
- L27 _public prototype_ `virtual void CustomizeChildren(TSharedRef<class IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L36 _public function_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance()` — Creates an instance of this class. @return The new instance.
- L48 _public prototype_ `static FString GetSequencePathFromChildProperty(const TSharedPtr<IPropertyHandle>& InPropertyHandle);` — Get the path to the currently selected image sequence. @param InPropertyHandle A property that is a child of the top level ImgMediaSource property. @return Sequence path string.
- L57 _protected prototype_ `FString GetSequencePath() const;` — Get the path to the currently selected image sequence. @return Sequence path string.
- L62 _protected prototype_ `FString GetSequenceFullPath() const;` — Returns the fully resolved path to the sequence directory of the currently selected media source.
- L67 _private prototype_ `void HandleSequencePathPickerPathPicked(const FString& PickedPath);` — Callback for picking a path in the source directory picker.
- L70 _private prototype_ `EVisibility HandleSequencePathWarningIconVisibility() const;` — Callback for getting the visibility of warning icon for invalid SequencePath paths.
- L73 _private prototype_ `static TSharedPtr<IPropertyHandle> GetSequencePathProperty(const TSharedPtr<IPropertyHandle>& InPropertyHandle);` — Returns the property for SequencePath.
- L76 _private prototype_ `static TSharedPtr<IPropertyHandle> GetSequencePathPathProperty(const TSharedPtr<IPropertyHandle>& InPropertyHandle);` — Returns the property for SequencePath->Path.
- L81 _private member_ `TSharedPtr<SEditableTextBox> ProxiesTextBlock;` — Text block widget showing the found proxy directories.
- L84 _private member_ `TSharedPtr<IPropertyHandle> PropertyHandle;` — Stores our property.

### `Plugins/Media/ImgMedia/Source/ImgMediaEditor/Private/Factories/ImgMediaSourceFactory.h` (Private)


#### class `UImgMediaSourceFactory`  
`class UImgMediaSourceFactory : public UFactory`  
_L14-24_
- reflection: `UCLASS(hidecategories=Object)`
- inherits: `UFactory`
- desc: Implements a factory for UImgMediaSource objects.
- L23 _public prototype_ `virtual UObject* FactoryCreateFile(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, const FString& Filename, const TCHAR* Parms, FFeedbackContext* Warn, bool& bOutOperationCanceled) override;`

### `Plugins/Media/ImgMedia/Source/ImgMediaEditor/Private/Factories/ImgMediaSourceFactoryNew.h` (Private)


#### class `UImgMediaSourceFactoryNew`  
`class UImgMediaSourceFactoryNew : public UFactory`  
_L13-25_
- reflection: `UCLASS(hidecategories=Object)`
- inherits: `UFactory`
- desc: Implements a factory for UImgMediaSource objects.
- L22 _public prototype_ `virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;`
- L23 _public prototype_ `virtual uint32 GetMenuCategories() const override;`
- L24 _public prototype_ `virtual bool ShouldShowInNewMenu() const override;`

### `Plugins/Media/ImgMedia/Source/ImgMediaEditor/Private/Factories/TmvFileMediaSourceFactory.h` (Private)


#### class `UTmvFileMediaSourceFactory`  
`class UTmvFileMediaSourceFactory : public UFactory`  
_L14-27_
- reflection: `UCLASS(hidecategories=Object)`
- inherits: `UFactory`
- desc: Implements a factory for importing Tmv container files as UFileMediaSource objects.
- L20 _public prototype_ `virtual bool FactoryCanImport(const FString& InFilename) override;`
- L21 _public prototype_ `virtual UObject* FactoryCreateFile(UClass* InClass, UObject* InParent, FName InName, EObjectFlags InFlags, const FString& InFilename, const TCHAR* InParms, FFeedbackContext* InWarn, bool& bOutOperationCanceled) override;`
- L26 _private prototype_ `void InitializeFormats();` — Populate the Formats array from registered demuxer factories. Safe to call multiple times.

### `Plugins/Media/ImgMedia/Source/ImgMediaEditor/Private/ImgMediaEditorModule.h` (Private)


#### class `IImgMediaEditorModule`  
`class IImgMediaEditorModule : public IModuleInterface`  
_L21-33_
- inherits: `IModuleInterface`
- desc: Interface for the ImgMediaEditor module.
- L29 _public prototype_ `virtual const TArray<TWeakPtr<FImgMediaPlayer>>& GetMediaPlayers() = 0;` — Call this to get a list of all the players. *
- L32 _public member_ `FOnImgMediaEditorPlayersUpdated OnImgMediaEditorPlayersUpdated;` — Add to this to get a callback when the list of players gets updated.

#### Free symbols / members of external scopes

- L12 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogImgMediaEditor, Log, All);` — Log category for this module.
- L12 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogImgMediaEditor, Log, All);` — Log category for this module.
- L15 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnImgMediaEditorPlayersUpdated);` — Callback for when the list of players is updated.
- L15 _prototype_ `DECLARE_MULTICAST_DELEGATE(FOnImgMediaEditorPlayersUpdated);` — Callback for when the list of players is updated.

### `Plugins/Media/ImgMedia/Source/ImgMediaEditor/Private/Widgets/ImgMediaProcessEXROptions.h` (Private)


#### class `UImgMediaProcessEXROptions`  
`class UImgMediaProcessEXROptions : public UObject`  
_L14-63_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- L20 _public member_ `FFilePath InputPath;` — `UPROPERTY(EditAnywhere, Category = Sequence)` — The directory that contains the image sequence files.
- L24 _public member_ `FDirectoryPath OutputPath;` — `UPROPERTY(EditAnywhere, Category = Sequence)` — The directory to output the processed image sequence files to.
- L28 _public member_ `bool bEnableMipMapping = true;` — `UPROPERTY(EditAnywhere, Category = Sequence)` — If checked, then enable mip mapping.
- L32 _public member_ `bool bEnableTiling = true;` — `UPROPERTY(EditAnywhere, Category = Tiles)` — If checked, then enable tiling.
- L36 _public member_ `int32 TileSizeX = 256;` — `UPROPERTY(EditAnywhere, Transient, Category = Tiles, meta = (EditCondition = "bEnableTiling", ClampMin = "0.0"))` — Width of a tile in pixels. If 0, then do not make tiles.
- L40 _public member_ `int32 TileSizeY = 256;` — `UPROPERTY(EditAnywhere, Transient, Category = Tiles, meta = (EditCondition = "bEnableTiling", ClampMin = "0.0"))` — Height of a tile in pixels. If 0, then do not make tiles.
- L44 _public member_ `int32 NumThreads = 0;` — `UPROPERTY(EditAnywhere, Transient, Category = Processing, meta = (ClampMin = "0.0"))` — Number of threads to use when processing. If 0 then this number is set automatically.
- L48 _public member_ `bool bUsePlayer = false;` — `UPROPERTY(EditAnywhere, Transient, Category = Processing)` — Use a player to read in the image.
- L54 _public member_ `bool bRemoveAlphaChannel = false;` — `UPROPERTY(EditAnywhere, Category = Channels)` — This option removes alpha channel. Since alpha channel adds 25% reading cost, it is suggested to have alpha channel removed if it is not used.
- L58 _public member_ `bool bEnableMipLevelTint = false;` — `UPROPERTY(EditAnywhere, Transient, Category = Debug)` — Tint each mip level a different colour to help with debugging.
- L62 _public member_ `TArray<FLinearColor> MipLevelTints;` — `UPROPERTY(EditAnywhere, Transient, Category = Debug)` — Colour to tint each mip level.

### `Plugins/Media/ImgMedia/Source/ImgMediaEditor/Private/Widgets/SImgMediaBandwidth.h` (Private)


#### class `SImgMediaBandwidth`  
`class SImgMediaBandwidth : public SCompoundWidget`  
_L16-52_
- inherits: `SCompoundWidget`
- desc: SImgMediaCache manages caching for image sequences.
- L19 _public function_ `SLATE_BEGIN_ARGS(SImgMediaBandwidth)`
- L20 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L25 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L32 _private prototype_ `void RefreshPlayersContainer();` — Update our list of players and the widgets accordingly.
- L45 _private member_ `TArray<FPlayerInfo> PlayerInfos;` — Array of all players.
- L47 _private member_ `TSharedPtr<SVerticalBox> PlayersContainer;` — Widget to hold all widgets for all the players.
- L49 _private member_ `double LastBandwidthUpdateTime = 0.0;` — Timestamp to slow down bandwidth updates.
- L51 _private member_ `static constexpr double BANDWIDTH_REFRESH_RATE = 0.25;` — Bandwidth refresh rate in seconds.

#### struct `SImgMediaBandwidth::FPlayerInfo`  
`struct FPlayerInfo`  
_L35-42_
- desc: Info for a single player.
- L37 _public member_ `TWeakPtr<FImgMediaPlayer> Player;`
- L38 _public member_ `TSharedPtr<STextBlock> UrlTextBlock;`
- L39 _public member_ `TSharedPtr<STextBlock> CurrentBandwidthTextBlock;`
- L40 _public member_ `TSharedPtr<STextBlock> EffectiveBandwidthTextBlock;`
- L41 _public member_ `TSharedPtr<STextBlock> RequiredBandwidthTextBlock;`

### `Plugins/Media/ImgMedia/Source/ImgMediaEditor/Private/Widgets/SImgMediaCache.h` (Private)


#### class `SImgMediaCache`  
`class SImgMediaCache : public SCompoundWidget`  
_L14-45_
- inherits: `SCompoundWidget`
- desc: SImgMediaCache manages caching for image sequences.
- L17 _public function_ `SLATE_BEGIN_ARGS(SImgMediaCache)`
- L20 _public prototype_ `virtual ~SImgMediaCache();`
- L22 _public prototype_ `void Construct(const FArguments& InArgs);`
- L25 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;` — SWidget interface
- L30 _private prototype_ `FReply OnClearGlobalCacheClicked();` — Called when we click on the clear global cache button.
- L39 _private prototype_ `FText ConvertMemorySizeToText(SIZE_T Size);` — Converts a number to a text with KB, MB, etc dependnig on the size. @param Size		Size in bytes. @return Text representing the number.
- L42 _private member_ `TSharedPtr<STextBlock> CurrentSizeTextBlock;` — Widget to show curent size of cache.
- L44 _private member_ `TSharedPtr<STextBlock> MaxSizeTextBlock;` — Widget to show max size of cache.

### `Plugins/Media/ImgMedia/Source/ImgMediaEditor/Private/Widgets/SImgMediaProcessEXR.h` (Private)


#### class `SImgMediaProcessEXR`  
`class SImgMediaProcessEXR : public SCompoundWidget`  
_L25-249_
- inherits: `SCompoundWidget`
- desc: SImgMediaProcessEXR provides processing of image sequences.
- L28 _public function_ `SLATE_BEGIN_ARGS(SImgMediaProcessEXR)`
- L31 _public prototype_ `virtual ~SImgMediaProcessEXR();`
- L33 _public prototype_ `void Construct(const FArguments& InArgs);`
- L38 _public prototype_ `void SetInputPath(const FString& Path);` — Call this to set what the input path should be.
- L41 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime);` — SWidget interface
- L60 _private member_ `FImageParameters GlobalImageParameters;` — Contains parameters to be applied to all images.
- L65 _private prototype_ `void UpdateWidgets();` — Updates our widgets based on the current state.
- L68 _private prototype_ `FReply OnProcessImagesClicked();` — Called when we click on the process images button.
- L70 _private prototype_ `FReply OnCancelClicked();` — Called when we click on the cancel button.
- L75 _private prototype_ `void ProcessAllImages();` — Processes all images in the sequence and generate tiles/mips.
- L84 _private prototype_ `void GetImageParameters(const FString& Ext, const FString& File, FImageParameters& ImageParameters);` — Gets information on the file, e.g does it have an alpha channel. @param Ext				File extension. @param File				Full path to file. @param ImageParameters	Will be filled in with information from the file.
- L89 _private prototype_ `void GetGlobalImageParameters();` — Gets parameters that can be applied to all files.
- L104 _private prototype_ `void ProcessImageCustom(const FImage& InImage, int32 InTileWidth, int32 InTileHeight, int32 InTileBorder, bool bInEnableMips, const FImageParameters& ImageParameters, const FString& InName);` — Processess a single image and writes out a file. Tiles and mips may be generated. This does NOT run on the game thread. @param InImage			FImage of the source image. @param InTileWidth		Desired width of tiles. @param InTileHeight		Desired height of tiles. @param InTileBorder		Number of pixels to duplicate along a tile edge. @param bInEnableMips		Turn on mip mapping. @param ImageParameters	Contains information on the image. @param InName			Full path and name of file to write.
- L123 _private prototype_ `void ProcessImageCustomRawData(TArray64<uint8>& RawData, int32 Width, int32 Height, int32 InTileWidth, int32 InTileHeight, int32 InTileBorder, bool bInEnableMips, const FImageParameters& ImageParameters, const FString& InName);` — Processess a single image and writes out a file. Tiles and mips may be generated. This might not run on the game thread. @param RawData			Image pixel data (RGBA FFloat16). @param Width				Width of image. @param Height			Height of image. @param InTileWidth		Desired width of tiles. @param InTileHeight		Desired height of tiles. @param InTileBorder		Number of pixels to duplicate along a tile edge. @param bInEnableMips		Turn on mip mapping. @param ImageParameters	Contains information on the image. @param InName			Full path and name of file to write.
- L135 _private prototype_ `void RemoveAlphaChannel(TArray64<uint8>& Buffer);` — Removes the alpha channel from a buffer. This will be done in place. Assumes 2 bytes per channel, 4 channels, alpha is the last channel. @param Buffer			Buffer to remove alpha from.
- L147 _private prototype_ `void TintData(uint8* SourceData, TArray64<uint8>& DestArray, int32 InMipLevel, int32 InWidth, int32 InHeight, int32 InNumChannels);` — Tints a source buffer and outputs it to a destination. @param SourceData		Source image. @param DestArray			Destination image. @param InMipLevel		The mip level of this image. @param InWidth			Width of source in pixels. @param InHeight			Height of source in pixels. @param InNumChannels		Number of channels in the image.
- L167 _private prototype_ `void TileData(uint8* SourceData, TArray64<uint8>& DestArray, int32 SourceWidth, int32 SourceHeight, int32 DestWidth, int32 DestHeight, int32 NumTilesX, int32 NumTilesY, int32 TileWidth, int32 TileHeight, int32 InTileBorder, int32 BytesPerPixel);` — Creates tiles from a source and outputs it to a destination. @param SourceData		Source image. @param DestArray			Destination image. @param SourceWidth		Width of source in pixels. @param SourceHeight		Height of source in pixels. @param DestWidth			Width of destination in pixels. @param DestHeight		Height of destination in pixels. @param NumTilesX			Number of tiles in X direction. @param NumTilesY			Number of tiles in Y direction. @param TileWidth			Width of a tile (without borders) in pixels. @param TileHeight		Height of a tile (without borders) in pixels. @param InTileBorder		Size of border in pixels. @param BytesPerPixel		Number of bytes per pixel.
- L176 _private prototype_ `void HandleProcessing();` — Call this every frame to handle processing.
- L183 _private prototype_ `void HandleMediaPlayerEvent(EMediaEvent InEvent);` — Handles media events from the player (e.g. MediaOpenFailed). @param InEvent The media event received from the player.
- L190 _private prototype_ `void CancelWithError(const FText& InMessage);` — Cancels processing and reports an error in the notification and log. @param InMessage Human-readable error message.
- L195 _private prototype_ `void CreateRenderTarget();` — Creates a render target.
- L200 _private prototype_ `void DrawTextureToRenderTarget();` — Draws the media texture to our render target.
- L205 _private prototype_ `void CleanUp();` — Clean up after processing is done.
- L208 _private member_ `TSharedPtr<class IDetailsView> DetailsView;` — Holds our details view.
- L210 _private member_ `TStrongObjectPtr<UImgMediaProcessEXROptions> Options;` — Object that holds our options.
- L212 _private member_ `TSharedPtr<SButton> StartButton;` — Holds the button to start processing.
- L214 _private member_ `TSharedPtr<SButton> CancelButton;` — Holds the button to cancel processing.
- L216 _private member_ `TSharedPtr<SNotificationItem> ConfirmNotification;` — Notification to update user on our progress.
- L219 _private member_ `TObjectPtr<UMediaPlayer> MediaPlayer;` — Used to read in media.
- L221 _private member_ `FDelegateHandle MediaEventHandle;` — Handle for OnMediaEvent subscription on MediaPlayer.
- L223 _private member_ `TObjectPtr<UMediaTexture> MediaTexture;` — Texture for the player.
- L225 _private member_ `TObjectPtr<UMediaSource> MediaSource;` — Source for the player.
- L227 _private member_ `TObjectPtr<UTextureRenderTarget2D> RenderTarget;` — Render target to render the media texture to.
- L229 _private member_ `FTimespan CurrentTime;` — The current time we are processing.
- L231 _private member_ `FTimespan FrameDuration;` — How long a frame is.
- L233 _private member_ `int32 CurrentFrameIndex = 0;` — Current frame index we are processing.
- L235 _private member_ `double LastProgressTimeSeconds = 0.0;` — Wall-clock time of the last forward progress (frame processed or player ready). Used to time out stuck players.
- L238 _private member_ `bool bIsProcessing = false;` — True if we are currently processing.
- L240 _private member_ `bool bIsCancelling = false;` — True if we want to cancel processing.
- L242 _private member_ `bool bUsePlayer = false;` — True if we are using a player to read in the images.
- L248 _private member_ `std::atomic<int32> NumAsyncTasks = 0;` — Counter for the number of "async tasks" that are currently running. This used by the main thread to protect against the widget being deleted while in use by the async tasks.

#### struct `SImgMediaProcessEXR::FImageParameters`  
`struct FImageParameters`  
_L46-58_
- desc: Contains info not contained in the image data.
- L49 _public member_ `FIntRect DataWindow;` — This window is inclusive, so (0, 0, 0, 0) is a 1 pixel rectangle at 0, 0.
- L51 _public member_ `FIntRect DisplayWindow;` — This window is inclusive, so(0, 0, 0, 0) is a 1 pixel rectangle at 0, 0.
- L53 _public member_ `bool bHasAlphaChannel = false;` — True if the image has an alpha channel.
- L55 _public member_ `bool bIsDataWindowValid = false;` — True if DataWindow can be used.
- L57 _public member_ `bool bIsDisplayWindowValid = false;` — True if DisplayWindow can be used.
