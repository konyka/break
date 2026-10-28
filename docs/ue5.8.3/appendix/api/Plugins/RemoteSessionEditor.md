# Plugins / RemoteSessionEditor

- module root: `Plugins/Experimental/RemoteSession/Source/RemoteSessionEditor`
- headers: 3; symbols: 62
- symbol kinds: class=4, function=5, member=22, namespace=1, prototype=30
- PrivateDependencyModuleNames: AssetRegistry, EditorFramework, Engine, LevelEditor, MediaIOCore, RenderCore, Slate, SlateCore, UnrealEd, WorkspaceMenuStructure
- PublicDependencyModuleNames: Core, CoreUObject, FieldNotification, RemoteSession, UMG, UMGEditor

### `Plugins/Experimental/RemoteSession/Source/RemoteSessionEditor/Private/RemoteSessionEditorModule.h` (Private)
_(no declarations extracted)_

### `Plugins/Experimental/RemoteSession/Source/RemoteSessionEditor/Private/RemoteSessionEditorStyle.h` (Private)


#### class `FRemoteSessionEditorStyle`  
`class FRemoteSessionEditorStyle`  
_L13-22_
- L16 _public prototype_ `static void Register();`
- L17 _public prototype_ `static void Unregister();`
- L19 _public prototype_ `static FName GetStyleSetName();`
- L21 _public prototype_ `static const ISlateStyle& Get();`

### `Plugins/Experimental/RemoteSession/Source/RemoteSessionEditor/Private/Widgets/SRemoteSessionStream.h` (Private)


#### class `URemoteSessionStreamSettings`  
`class URemoteSessionStreamSettings : public UObject`  
_L43-55_
- reflection: `UCLASS(MinimalAPI, config = EditorPerProjectUserSettings)`
- inherits: `UObject`
- desc: Settings for the remote session stream tab.
- L48 _public member_ `bool bIsVerticalSplitterOrientation = true;` — `UPROPERTY(config)`
- L51 _public member_ `bool bShowCheckered = false;` — `UPROPERTY(config)`
- L54 _public member_ `bool bScaleToFit = true;` — `UPROPERTY(config)`

#### class `URemoteSessionStreamWidgetUserData`  
`class URemoteSessionStreamWidgetUserData : public UAssetUserData`  
_L62-80_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAssetUserData`
- desc: URemoteSessionStreamWidgetUserData
- L67 _public prototype_ `URemoteSessionStreamWidgetUserData();`
- L70 _public member_ `TSubclassOf<UUserWidget> WidgetClass;` — `UPROPERTY(EditAnywhere, Category = "Remote Session")`
- L73 _public member_ `FVector2D Size;` — `UPROPERTY(EditAnywhere, Category = "Remote Session")`
- L76 _public member_ `TObjectPtr<UTextureRenderTarget2D> RenderTarget;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Category = "Remote Session")`
- L79 _public member_ `int16 Port;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Category = "Remote Session")`

#### class `SRemoteSessionStream`  
`class SRemoteSessionStream : public SCompoundWidget, FGCObject, FTickableEditorObject`  
_L86-163_
- inherits: `SCompoundWidget,FGCObject,FTickableEditorObject`
- desc: SRemoteSessionStream
- L89 _public prototype_ `static void RegisterNomadTabSpawner(TSharedRef<FWorkspaceItem> InWorkspaceItem);`
- L90 _public prototype_ `static void UnregisterNomadTabSpawner();`
- L91 _public prototype_ `static TSharedPtr<SRemoteSessionStream> GetPanelInstance();`
- L94 _private member_ `static TWeakPtr<SRemoteSessionStream> WidgetInstance;`
- L97 _public function_ `SLATE_BEGIN_ARGS(SRemoteSessionStream)`
- L100 _public prototype_ `~SRemoteSessionStream();`
- L101 _public prototype_ `void Construct(const FArguments& InArgs);`
- L102 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L105 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;`
- L106 _public function_ `virtual FString GetReferencerName() const override`
- L113 _public prototype_ `virtual void Tick(float DeltaTime) override;`
- L114 _public function_ `virtual ETickableTickType GetTickableTickType() const override`
- L115 _public function_ `virtual bool IsTickable() const override`
- L116 _public prototype_ `virtual TStatId GetStatId() const override;`
- L119 _public function_ `bool IsStreaming() const`
- L120 _public prototype_ `bool CanStream() const;`
- L121 _public prototype_ `void EnabledStreaming(bool bStreaming);`
- L124 _private prototype_ `TSharedRef<class SWidget> MakeToolBar();`
- L125 _private prototype_ `TSharedRef<SWidget> CreateSettingsMenu();`
- L126 _private prototype_ `void GenerateBackgroundMenuContent(FMenuBuilder& MenuBuilder);`
- L127 _private prototype_ `const FSlateBrush* GetImageBorderImage() const;`
- L128 _private prototype_ `EStretch::Type GetViewportStretch() const;`
- L130 _private prototype_ `void ResetUObject();`
- L132 _private prototype_ `void OnRemoteSessionChannelChange(IRemoteSessionRole* Role, TWeakPtr<IRemoteSessionChannel> Channel, ERemoteSessionChannelChange Change);`
- L133 _private prototype_ `void OnImageChannelCreated(TWeakPtr<IRemoteSessionChannel> Instance);`
- L134 _private prototype_ `void OnInputChannelCreated(TWeakPtr<IRemoteSessionChannel> Instance);`
- L136 _private prototype_ `void OnBlueprintPreCompile(UBlueprint* Blueprint);`
- L137 _private prototype_ `void OnPrepareToCleanseEditorObject(UObject* Object);`
- L138 _private prototype_ `void HandleAssetRemoved(const FAssetData& AssetData);`
- L139 _private prototype_ `void OnMapChanged(UWorld* World, EMapChangeType ChangeType);`
- L140 _private prototype_ `void CanDeleteAssets(const TArray<UObject*>& InAssetsToDelete, FCanDeleteAssetResult& CanDeleteResult);`
- L143 _private member_ `TSharedPtr<IDetailsView> DetailView;`
- L144 _private member_ `TSharedPtr<SSplitter> Splitter;`
- L146 _private member_ `FSlateBrush RenderTargetBrush;` — TSharedPtr<SImage> RenderTargetImage;
- L149 _private member_ `TObjectPtr<URemoteSessionStreamWidgetUserData> WidgetUserData;`
- L150 _private member_ `TObjectPtr<UTextureRenderTarget2D> RenderTarget2D;`
- L151 _private member_ `TObjectPtr<UUserWidget> UserWidget;`
- L152 _private member_ `TObjectPtr<UWorld> WidgetWorld;`
- L153 _private member_ `TObjectPtr<URemoteSessionMediaOutput> MediaOutput;`
- L154 _private member_ `TObjectPtr<URemoteSessionMediaCapture> MediaCapture;`
- L157 _private member_ `TSharedPtr<IRemoteSessionUnmanagedRole> RemoteSessionHost;`
- L158 _private member_ `TSharedPtr<SVirtualWindow> VirtualWindow;`
- L159 _private member_ `FWidgetRenderer* WidgetRenderer;`
- L160 _private member_ `FVector2D WidgetSize;`
- L162 _private member_ `bool bIsStreaming;`

#### Free symbols / members of external scopes

- L18 _namespace_ `namespace EStretch`
