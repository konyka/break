# Plugins / SlateIMInGame

- module root: `Plugins/Experimental/SlateIM/Source/SlateIMInGame`
- headers: 6; symbols: 64
- symbol kinds: class=6, externvar=1, function=6, macro=4, member=14, namespace=1, prototype=32
- PublicDependencyModuleNames: Core, CoreUObject, Engine, Slate, SlateCore, SlateIM

### `Plugins/Experimental/SlateIM/Source/SlateIMInGame/Private/SlateIMInGameWidgetCheatManager.h` (Private)


#### class `USlateIMInGameWidgetCheatManager`  
`class USlateIMInGameWidgetCheatManager : public UCheatManagerExtension`  
_L10-23_
- reflection: `UCLASS()`
- inherits: `UCheatManagerExtension`
- L15 _public prototype_ `USlateIMInGameWidgetCheatManager();`
- L18 _public prototype_ `void ToggleSlateIMInGameWidget(const FString& Path) const;` — `UFUNCTION(Exec)`
- L22 _private prototype_ `void EnableInGameWidgetFromClass(const FString& ClassPath, const bool bEnable) const;` — `UFUNCTION(Exec)`

### `Plugins/Experimental/SlateIM/Source/SlateIMInGame/Public/SlateIMInGameNomadTab.h` (Public)


#### class `ASlateIMInGameNomadTab`  
`class ASlateIMInGameNomadTab : public ASlateIMInGameWidgetBase`  
_L12-34_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `ASlateIMInGameWidgetBase`
- L17 _protected prototype_ `void Init(const FName& InTabName, const FStringView& InTabTitle, const FSlateIcon& InTabIcon);`
- L18 _protected function_ `virtual void DrawContent(const float DeltaTime)`
- L19 _protected prototype_ `virtual void OnWidgetStarted() override;`
- L20 _protected prototype_ `virtual void OnWidgetStopped() override;`
- L23 _private prototype_ `virtual void DrawWidget(const float DeltaTime) override;`
- L25 _private prototype_ `void OnTabActivated();`
- L26 _private prototype_ `void OnTabDeactivated();`
- L28 _private member_ `FName TabName;`
- L29 _private member_ `FText TabTitle;`
- L30 _private member_ `FSlateIcon TabIcon;`
- L31 _private member_ `TWeakPtr<SDockTab> RootTab;`
- L32 _private member_ `TWeakPtr<SWidget> TabContent;`
- L33 _private member_ `bool bDestroyRequested = false;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API SLATEIMINGAME_API`

### `Plugins/Experimental/SlateIM/Source/SlateIMInGame/Public/SlateIMInGameWidgetBase.h` (Public)


#### class `ASlateIMInGameWidgetBase`  
`class ASlateIMInGameWidgetBase : public AActor`  
_L15-56_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `AActor`
- L20 _public prototype_ `ASlateIMInGameWidgetBase();`
- L22 _public prototype_ `virtual void BeginPlay() override;`
- L23 _public prototype_ `virtual void EndPlay(EEndPlayReason::Type Reason) override;`
- L25 _public prototype_ `virtual void OnRep_Owner() override;`
- L26 _public prototype_ `virtual void PreReplication(IRepChangedPropertyTracker& ChangedPropertyTracker) override;`
- L27 _public prototype_ `virtual bool IsNetRelevantFor(const AActor* RealViewer, const AActor* ViewTarget, const FVector& SrcLocation) const override;`
- L29 _public prototype_ `APlayerController* GetPlayerController() const;`
- L30 _public prototype_ `bool IsLocallyControlled() const;`
- L32 _public prototype_ `static ASlateIMInGameWidgetBase* GetInGameWidget(const APlayerController* Owner, const TSubclassOf<ASlateIMInGameWidgetBase>& InGameWidgetClass);`
- L33 _public prototype_ `static void EnableInGameWidget(APlayerController* Owner, const bool bEnable, const TSubclassOf<ASlateIMInGameWidgetBase>& InGameWidgetClass);`
- L37 _protected function_ `virtual void GenerateServerSnapshot()`
- L40 _protected function_ `virtual void DrawWidget(const float DeltaTime)`
- L42 _protected prototype_ `void StartWidget();`
- L43 _protected prototype_ `void StopWidget();`
- L44 _protected prototype_ `void TickWidget(const float DeltaTime);`
- L46 _protected function_ `virtual void OnWidgetStarted()`
- L47 _protected function_ `virtual void OnWidgetStopped()`
- L49 _protected prototype_ `static ASlateIMInGameWidgetBase* GetOrOpenInGameWidget(APlayerController* Owner, const TSubclassOf<ASlateIMInGameWidgetBase>& InGameWidgetClass);`
- L50 _protected prototype_ `static void DestroyInGameWidget(const APlayerController* Owner, const TSubclassOf<ASlateIMInGameWidgetBase>& InGameWidgetClass);`
- L52 _protected member_ `FDelegateHandle WidgetTickHandle;`
- L55 _protected prototype_ `void Server_Destroy();` — `UFUNCTION(Reliable, Server)`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API SLATEIMINGAME_API`

### `Plugins/Experimental/SlateIM/Source/SlateIMInGame/Public/SlateIMInGameWidgetModularFeature.h` (Public)


#### class `FSlateIMInGameWidgetModularFeature`  
`class FSlateIMInGameWidgetModularFeature : public IModularFeature`  
_L19-32_
- inherits: `IModularFeature`
- L22 _public prototype_ `FSlateIMInGameWidgetModularFeature(const FString& InPath, const TSubclassOf<ASlateIMInGameWidgetBase>& InWidgetClass);`
- L24 _public prototype_ `static TSoftClassPtr<ASlateIMInGameWidgetBase> FindWidgetClass(const FName Type, const FString& InPath);`
- L27 _protected prototype_ `void ToggleWidget(UWorld* World);`
- L29 _protected member_ `FString Path;`
- L30 _protected member_ `TSoftClassPtr<ASlateIMInGameWidgetBase> WidgetClass;`
- L31 _protected member_ `FAutoConsoleCommandWithWorld WidgetCommand;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API SLATEIMINGAME_API`
- L14 _namespace_ `namespace SlateIMInGameWidget`
- L16 _externvar_ `extern const FLazyName ModularFeatureName;` (scope `SlateIMInGameWidget`)

### `Plugins/Experimental/SlateIM/Source/SlateIMInGame/Public/SlateIMInGameWindow.h` (Public)


#### class `ASlateIMInGameWindow`  
`class ASlateIMInGameWindow : public ASlateIMInGameWidgetBase`  
_L12-28_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `ASlateIMInGameWidgetBase`
- L17 _protected prototype_ `void Init(const FName& InWindowName, const FStringView& InWindowTitle);`
- L19 _protected function_ `virtual void DrawContent(const float DeltaTime)`
- L22 _private prototype_ `virtual void DrawWidget(const float DeltaTime) override;`
- L24 _private member_ `FName WindowName;`
- L25 _private member_ `FString WindowTitle;`
- L26 _private member_ `FVector2f WindowSize = FVector2f(500,500);`
- L27 _private member_ `bool bDestroyRequested = false;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API SLATEIMINGAME_API`

### `Plugins/Experimental/SlateIM/Source/SlateIMInGame/SlateIMInGameModule.h` (Other)


#### class `FSlateIMInGameModule`  
`class FSlateIMInGameModule : public IModuleInterface`  
_L7-12_
- inherits: `IModuleInterface`
- L10 _public prototype_ `virtual void StartupModule() override;`
- L11 _public prototype_ `virtual void ShutdownModule() override;`
