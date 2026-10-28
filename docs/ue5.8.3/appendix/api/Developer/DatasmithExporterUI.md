# Developer / DatasmithExporterUI

- module root: `Source/Developer/Datasmith/DatasmithExporterUI`
- headers: 5; symbols: 72
- symbol kinds: class=5, delegate=2, function=2, member=24, namespace=1, prototype=35, typedef=3
- PrivateDependencyModuleNames: Core, CoreUObject, DatasmithCore, DatasmithExporter, DesktopPlatform, DirectLink, InputCore, Slate, SlateCore

### `Source/Developer/Datasmith/DatasmithExporterUI/Private/DatasmithExporterUIModule.h` (Private)


#### class `FDatasmithExporterUIModule`  
`class FDatasmithExporterUIModule final : public IModuleInterface, public IDatasmithExporterUIModule`  
_L11-25_
- inherits: `IModuleInterface,IDatasmithExporterUIModule`
- L14 _public function_ `virtual bool SupportsDynamicReloading()`
- L19 _public prototype_ `virtual void StartupModule() override;`
- L21 _public prototype_ `virtual IDirectLinkUI* GetDirectLinkExporterUI() const override;`
- L24 _private member_ `TUniquePtr<IDirectLinkUI> DirectLinkUI;`

### `Source/Developer/Datasmith/DatasmithExporterUI/Private/DirectLinkUI.h` (Private)


#### class `FDirectLinkUI`  
`class FDirectLinkUI : public IDirectLinkUI`  
_L14-48_
- inherits: `IDirectLinkUI`
- L18 _public prototype_ `FDirectLinkUI();`
- L20 _public prototype_ `virtual void SetStreamWindowCenter( int InCenterX, int InCenterY ) override;`
- L22 _public prototype_ `virtual void OpenDirectLinkStreamWindow() override;`
- L23 _public prototype_ `virtual const TCHAR* GetDirectLinkCacheDirectory() override;`
- L26 _private prototype_ `void OnCacheDirectoryChanged(const FString& InNewCacheDirectory);`
- L27 _private prototype_ `FString OnCacheDirectoryReset();`
- L29 _private prototype_ `void SaveCacheDirectory( const FString& InCacheDir, bool bInDefaultCacheDir );`
- L31 _private prototype_ `void WindowClosed( const TSharedRef<SWindow>& WindowArg );`
- L34 _private member_ `TWeakPtr<SWindow> DirectLinkWindow;` — To accessed from the game thread only
- L36 _private member_ `FCriticalSection CriticalSectionCacheDirectory;`
- L37 _private member_ `FString DirectLinkCacheDirectory;`
- L38 _private member_ `FString DefaultDirectLinkCacheDirectory;`
- L41 _private member_ `FString LastReturnedCacheDirectory;` — Used to protect the caller to GetDirectLinkCacheDirectory from a pontential race condition
- L43 _private member_ `bool StreamWindowCenterSet = false;`
- L44 _private member_ `bool StreamWindowClosedBefore = false;`
- L45 _private member_ `static FVector2D StreamWindowDefaultSize;`
- L46 _private member_ `FVector2D StreamWindowSize;`
- L47 _private member_ `FVector2D StreamWindowPosition;`

### `Source/Developer/Datasmith/DatasmithExporterUI/Private/Widgets/SDirectLinkStreamManager.h` (Private)


#### class `SDirectLinkStreamManager`  
`class SDirectLinkStreamManager : public SCompoundWidget`  
_L30-109_
- inherits: `SCompoundWidget`
- L33 _public prototype_ `DECLARE_DELEGATE_OneParam( FOnCacheDirectoryChanged, const FString& );`
- L34 _public prototype_ `DECLARE_DELEGATE_RetVal( FString, FOnCacheDirectoryReset );`
- L36 _public function_ `SLATE_BEGIN_ARGS(SDirectLinkStreamManager)`
- L37 _public prototype_ `SLATE_EVENT( FOnCacheDirectoryChanged, OnCacheDirectoryChanged ) SLATE_EVENT( FOnCacheDirectoryReset, OnCacheDirectoryReset ) SLATE_ARGUMENT( FString, DefaultCacheDirectory ) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<DirectLink::FEndpoint, ESPMode::ThreadSafe>& InEndpoint);`
- L44 _public prototype_ `virtual ~SDirectLinkStreamManager();`
- L46 _public prototype_ `void UpdateData(const DirectLink::FRawInfo& RawInfo);`
- L49 _private typedef_ `using FSourceId = FGuid;`
- L50 _private typedef_ `using FDestinationId = FGuid;`
- L51 _private typedef_ `using FStreamID = TPair<FSourceId,FDestinationId>;`
- L53 _private prototype_ `TSharedRef<ITableRow> OnGenerateRow(TSharedRef<FStreamData> Item, const TSharedRef<STableViewBase>& Owner) const;`
- L55 _private prototype_ `EColumnSortMode::Type GetColumnSortMode(const FName InColumnId) const;`
- L57 _private prototype_ `void OnColumnSortModeChanged(const EColumnSortPriority::Type SortPriority, const FName& ColumnId, const EColumnSortMode::Type InSortMode);`
- L59 _private prototype_ `void SortStreamList();`
- L61 _private prototype_ `FText GetCacheDirectory() const;`
- L63 _private prototype_ `FReply OnChangeCacheDirectoryClicked();`
- L64 _private prototype_ `FReply OnResetCacheDirectoryClicked();`
- L66 _private prototype_ `EVisibility GetNoConnectionHintVisibility() const;`
- L68 _private prototype_ `float GetNoConnectionHintFillHeight() const;`
- L70 _private prototype_ `EVisibility GetConnectionViewVisibility() const;`
- L72 _private prototype_ `EVisibility GetAdavancedSettingVisibility() const;`
- L74 _private prototype_ `FReply OnShowAdavancedSettingClicked();`
- L76 _private prototype_ `FText GetShowAdavancedSettingToolTipText() const;`
- L79 _private member_ `TSharedPtr<SListView<TSharedRef<FStreamData>>> ConnectionsView;`
- L82 _private member_ `TArray<TSharedRef<FStreamData>> Streams;` — The list of streams connection
- L85 _private member_ `TMap<FStreamID, TSharedRef<FStreamData>> StreamMap;` — A map to update the stream data quickly
- L88 _private member_ `TSharedPtr<DirectLink::FEndpoint, ESPMode::ThreadSafe> Endpoint;` — The endpoint managed by this widget
- L91 _private member_ `TSharedPtr<FEndpointObserver> Observer;` — The registered observer to the endpoint
- L94 _private member_ `FName SortedColumn;` — The currently sorted column
- L97 _private member_ `EColumnSortMode::Type SortMode;` — The current sort mode for the sorted column
- L100 _private member_ `FString DirectLinkCacheDirectory;` — The path to the cache directory
- L102 _private member_ `FOnCacheDirectoryChanged OnCacheDirectoryChanged;`
- L103 _private member_ `FOnCacheDirectoryReset OnCacheDirectoryReset;`
- L105 _private member_ `TSharedPtr<class SButton> ShowAdavancedSettingButton;`
- L106 _private member_ `TSharedPtr<class SImage> ShowAdavancedSettingImage;`
- L108 _private member_ `bool bShowingAdavancedSetting;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace DirectLink`
- L33 _delegate_ `DECLARE_DELEGATE_OneParam( FOnCacheDirectoryChanged, const FString& );`
- L34 _delegate_ `DECLARE_DELEGATE_RetVal( FString, FOnCacheDirectoryReset );`

### `Source/Developer/Datasmith/DatasmithExporterUI/Public/IDatasmithExporterUIModule.h` (Public)


#### class `IDatasmithExporterUIModule`  
`class IDatasmithExporterUIModule`  
_L12-27_
- desc: Static interface for the datasmith exporter UI module
- L18 _public prototype_ `static IDatasmithExporterUIModule* Get();` — This will return nullptr if the datasmith exporter manager initialization wasn't done with the datasmith ui argument at true
- L24 _public prototype_ `virtual IDirectLinkUI* GetDirectLinkExporterUI() const = 0;` — Return the Direct Link UI interface @return A valid pointer if the exporter was initialized with the messaging argument being true
- L26 _public prototype_ `virtual ~IDatasmithExporterUIModule() = default;`

### `Source/Developer/Datasmith/DatasmithExporterUI/Public/IDirectLinkUI.h` (Public)


#### class `IDirectLinkUI`  
`class IDirectLinkUI`  
_L7-22_
- L13 _public prototype_ `virtual void SetStreamWindowCenter(int InCenterX, int InCenterY) = 0;` — Open the direct link connections window or move it up front if it's already open
- L14 _public prototype_ `virtual void OpenDirectLinkStreamWindow() = 0;`
- L19 _public prototype_ `virtual const TCHAR* GetDirectLinkCacheDirectory() = 0;` — Get the user defined cache directory for direct link
- L21 _public prototype_ `virtual ~IDirectLinkUI() = default;`
