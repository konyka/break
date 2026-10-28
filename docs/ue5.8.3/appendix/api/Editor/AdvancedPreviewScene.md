# Editor / AdvancedPreviewScene

- module root: `Source/Editor/AdvancedPreviewScene`
- headers: 9; symbols: 250
- symbol kinds: class=11, delegate=5, enum=2, enumerator=6, function=21, macro=4, member=94, namespace=5, prototype=97, struct=5
- PrivateDependencyModuleNames: CommonMenuExtensions, Core, CoreUObject, EditorInteractiveToolsFramework, Engine, InputCore, Slate, SlateCore, ToolMenus, UnrealEd
- PublicIncludePathModuleNames: PropertyEditor

### `Source/Editor/AdvancedPreviewScene/Public/AdvancedPreviewScene.h` (Public)


#### class `FAdvancedPreviewScene`  
`class FAdvancedPreviewScene : public FPreviewScene, public FTickableEditorObject`  
_L30-158_
- inherits: `FPreviewScene,FTickableEditorObject`
- L34 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnProfileChanged, const FPreviewSceneProfile&, FName);` — An event for when a profile changes. Includes the changed profile and (optionally) the name of the property in the profile that changed.
- L36 _public prototype_ `FAdvancedPreviewScene(ConstructionValues CVS, float InFloorOffset = 0.0f);`
- L37 _public prototype_ `~FAdvancedPreviewScene();`
- L39 _public prototype_ `void UpdateScene(FPreviewSceneProfile& Profile, bool bUpdateSkyLight = true, bool bUpdateEnvironment = true, bool bUpdatePostProcessing = true, bool bUpdateDirectionalLight = true);`
- L42 _public prototype_ `virtual FLinearColor GetBackgroundColor() const override;` — Begin FPreviewScene
- L46 _public prototype_ `virtual void Tick(float DeltaTime) override;` — Begin FTickableEditorObject
- L47 _public function_ `virtual ETickableTickType GetTickableTickType() const override`
- L48 _public prototype_ `virtual TStatId GetStatId() const override;`
- L51 _public function_ `FOnProfileChanged& OnProfileChanged()`
- L53 _public prototype_ `const bool HandleViewportInput(FViewport* InViewport, FInputDeviceId DeviceId, FKey Key, float Delta, float DeltaTime, int32 NumSamples, bool bGamepad);`
- L54 _public prototype_ `const bool HandleInputKey(const FInputKeyEventArgs& EventArgs);`
- L56 _public prototype_ `void SetSkyRotation(const float SkyRotation);`
- L58 _public prototype_ `bool GetFloorVisibility() const;` — Sets the visiblity state for the floor/environment by storing it in the scene profile and refreshing the scene, in case bDirect is true it sets the visibility directly and leaves the profile untouched.
- L59 _public prototype_ `void SetFloorVisibility(const bool bVisible, const bool bDirect = false);`
- L60 _public prototype_ `void SetEnvironmentVisibility(const bool bVisible, const bool bDirect = false);`
- L61 _public prototype_ `float GetFloorOffset() const;`
- L62 _public prototype_ `void SetFloorOffset(const float InFloorOffset);`
- L63 _public prototype_ `void SetProfileIndex(const int32 InProfileIndex);`
- L64 _public prototype_ `FPreviewSceneProfile* GetCurrentProfile() const;`
- L66 _public prototype_ `const UStaticMeshComponent* GetFloorMeshComponent() const;`
- L67 _public prototype_ `const float GetSkyRotation() const;`
- L68 _public prototype_ `const int32 GetCurrentProfileIndex() const;`
- L69 _public prototype_ `const bool IsUsingPostProcessing() const;`
- L71 _public function_ `TSharedPtr<FUICommandList> GetCommandList() const`
- L74 _public prototype_ `void HandleToggleEnvironment();` — Toggle the sky sphere on and off
- L77 _public prototype_ `bool IsEnvironmentEnabled() const;` — Whether the sky sphere is on.
- L80 _public prototype_ `void HandleToggleFloor();` — Toggle the floor mesh on and off
- L83 _public prototype_ `bool IsFloorEnabled() const;` — Whether the floor is on
- L87 _public prototype_ `void HandleToggleGrid();` — `UE_DEPRECATED(5.8, "bShowGrid is deprecated, this function does nothing")` — Toggle the grid on and off.
- L91 _public prototype_ `bool IsGridEnabled() const;` — `UE_DEPRECATED(5.8, "bShowGrid is deprecated, this function returns false")` — Whether the grid is enabled.
- L94 _public prototype_ `void HandleTogglePostProcessing();` — Toggle post processing on and off
- L97 _public prototype_ `bool IsPostProcessingEnabled() const;` — Whether post processing is enabled
- L100 _public prototype_ `void SetFloorMesh(UStaticMesh* InFloorMesh);` — Sets the mesh for the floor
- L103 _public prototype_ `void SetFloorMaterial(UMaterialInterface* InFloorMaterial, int32 InIndex = -1);` — Sets the floor material on a specific slot, or -1 for all slots
- L106 _public prototype_ `void SetFloorMeshRotation(const FRotator& InRotation);` — Sets the floor mesh rotation
- L109 _public prototype_ `void SetFloorMeshScale(const FVector& InScale);` — Sets the floor mesh scale
- L112 _public prototype_ `static void AddPreviewSceneInteractions(class UViewportInteractionsBehaviorSource* InBehaviorSource);` — Register sky rotation and light rotation viewport interactions on the given behavior source.
- L116 _protected prototype_ `virtual void BindCommands();` — Create and map the command list.
- L119 _protected prototype_ `virtual TSharedRef<FUICommandList> CreateCommandList();` — Add commands to a provided command list.
- L122 _protected prototype_ `void OnAssetViewerSettingsRefresh(const FName& InPropertyName);` — Handle refreshing the scene when settings change
- L124 _protected prototype_ `bool UsesViewportInteractions(const FEditorViewportClient* InViewportClient) const;`
- L132 _protected prototype_ `void NavigateProfile(ENavigationDirection InDirection);`
- L135 _protected member_ `FOnProfileChanged OnProfileChangedDelegate;`
- L137 _protected member_ `UStaticMeshComponent* SkyComponent;`
- L138 _protected member_ `UMaterialInstanceConstant* InstancedSkyMaterial;`
- L139 _protected member_ `UPostProcessComponent* PostProcessComponent;`
- L140 _protected member_ `UStaticMeshComponent* FloorMeshComponent;`
- L141 _protected member_ `UAssetViewerSettings* DefaultSettings;`
- L142 _protected member_ `bool bRotateLighting;`
- L144 _protected member_ `float CurrentRotationSpeed;`
- L145 _protected member_ `float PreviousRotation;`
- L146 _protected member_ `float UILightingRigRotationDelta;`
- L148 _protected member_ `bool bSkyChanged;`
- L149 _protected member_ `bool bPostProcessing;`
- L151 _protected member_ `int32 CurrentProfileIndex;`
- L154 _protected member_ `TSharedPtr<FUICommandList> UICommandList;` — Command list for input handling
- L157 _protected member_ `FDelegateHandle RefreshDelegate;` — Delegate handle used to refresh the scene when settings change

#### enum `FAdvancedPreviewScene::ENavigationDirection`  
`enum class ENavigationDirection : uint8`  
_L127-131_
- desc: Navigate to the next or previous profile
- L129 _public enumerator_ `Forward`
- L130 _public enumerator_ `Backward`

#### Free symbols / members of external scopes

- L17 _macro_ `#define UE_API ADVANCEDPREVIEWSCENE_API`
- L34 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnProfileChanged, const FPreviewSceneProfile&, FName);` — An event for when a profile changes. Includes the changed profile and (optionally) the name of the property in the profile that changed.

### `Source/Editor/AdvancedPreviewScene/Public/AdvancedPreviewSceneCommands.h` (Public)


#### class `FAdvancedPreviewSceneCommands`  
`class FAdvancedPreviewSceneCommands : public TCommands<FAdvancedPreviewSceneCommands>`  
_L16-53_
- inherits: `TCommands<FAdvancedPreviewSceneCommands>`
- L21 _public function_ `FAdvancedPreviewSceneCommands() : TCommands<FAdvancedPreviewSceneCommands> ( "AdvancedPreviewScene", NSLOCTEXT("Contexts", "AdvancedPreviewScene", "Advanced Preview Scene"), NAME_None, FAppStyle::Get().GetStyleSetName() )`
- L31 _public member_ `TSharedPtr< FUICommandInfo > ToggleEnvironment;` — Toggles environment (sky sphere) visibility
- L34 _public member_ `TSharedPtr< FUICommandInfo > ToggleFloor;` — Toggles floor visibility
- L37 _public member_ `TSharedPtr< FUICommandInfo > TogglePostProcessing;` — Toggles post processing
- L41 _public member_ `TSharedPtr< FUICommandInfo > ToggleGrid;` — `UE_DEPRECATED(5.8, "No longer in use, will be removed")` — Toggles the grid
- L44 _public member_ `TSharedPtr<FUICommandInfo> NextProfile;` — Navigate to next profile
- L47 _public member_ `TSharedPtr<FUICommandInfo> PreviousProfile;` — Navigate to previous profile
- L52 _public prototype_ `virtual void RegisterCommands() override;` — Initialize commands

### `Source/Editor/AdvancedPreviewScene/Public/AdvancedPreviewSceneMenus.h` (Public)


#### struct `UE::AdvancedPreviewScene::Menus::FSettingsOptions`  
`struct FSettingsOptions`  
_L16-47_
- L18 _public member_ `bool bShowToggleEnvironment = true;`
- L20 _public member_ `bool bShowToggleGrid = true;` — `UE_DEPRECATED(5.8, "No longer in use, will be removed")`
- L21 _public member_ `bool bShowToggleFloor = true;`
- L22 _public member_ `bool bShowTogglePostProcessing = true;`
- L24 _public function_ `FSettingsOptions& ShowToggleEnvironment(bool bInShowToggleEnvironment)`
- L31 _public function_ `FSettingsOptions& ShowToggleGrid(bool bInShowToggleGrid)` — `UE_DEPRECATED(5.8, "No longer in use, will be removed")`
- L36 _public function_ `FSettingsOptions& ShowToggleFloor(bool bInShowToggleFloor)`
- L42 _public function_ `FSettingsOptions& ShowTogglePostProcessing(bool bInShowTogglePostProcessing)`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace AdvancedPreviewScene` (scope `UE`)
- L13 _namespace_ `namespace Menus` (scope `UE::AdvancedPreviewScene`)
- L49 _prototype_ `void ExtendAdvancedPreviewSceneSettings(FName InAssetViewerProfileSubmenuName, const FSettingsOptions& InSettingsOptions = {});` (scope `UE::AdvancedPreviewScene::Menus`)
- L53 _namespace_ `namespace UE`
- L53 _namespace_ `namespace AdvancedPreviewScene` (scope `UE`)
- L59 _prototype_ `void DefaultOnSettingsChangedHandler(const FPreviewSceneProfile& Profile, FName PropertyName, TWeakPtr<FEditorViewportClient> Client);` (scope `UE::AdvancedPreviewScene`) — A default handler for `FAdvancedPreviewScene::OnProfileChanged()`. Syncs the profile to the provided client's show flags and other settings.
- L65 _prototype_ `void BindDefaultOnSettingsChangedHandler(const TSharedPtr<FAdvancedPreviewScene>& Scene, const TSharedPtr<FEditorViewportClient>& Client);` (scope `UE::AdvancedPreviewScene`) — Attaches `DefaultOnSettingsChangedHandler()` to the provided scene's `OnProfileChanged` delegate & calls the function with the current profile to syncronize the client. This is a convenience that alleviates the annoyance of having to manually downcast subtypes of FEditorViewporClient.

### `Source/Editor/AdvancedPreviewScene/Public/AdvancedPreviewSceneModule.h` (Public)


#### class `FAdvancedPreviewSceneModule`  
`class FAdvancedPreviewSceneModule : public IModuleInterface`  
_L18-58_
- inherits: `IModuleInterface`
- L35 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnPreviewSceneChanged, TSharedRef<FAdvancedPreviewScene>);`
- L44 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L45 _public prototype_ `virtual void ShutdownModule() override;`
- L57 _public prototype_ `virtual TSharedRef<SWidget> CreateAdvancedPreviewSceneSettingsWidget(const TSharedRef<FAdvancedPreviewScene>& InPreviewScene, UObject* InAdditionalSettings = nullptr, const TArray<FDetailCustomizationInfo>& InDetailCustomizations = TArray<FDetailCustomizationInfo>(), const TArray<FPropertyTypeCustomizationInfo>& InPropertyTypeCustomizations = TArray<FPropertyTypeCustomizationInfo>(), const TArray<FDetailDelegates>& InDelegates = TArray<FDetailDelegates>());` — Create an advanced preview scene settings widget. @param	InPreviewScene					The preview scene to create the widget for @param	InAdditionalSettings			Additional settings object to display in the view @param	InDetailCustomizations			Customizations to use for this details tab @param	InPropertyTypeCustomizations	Customizations to use for this details tab @param	InDelegates						Delegates to use for this details tab. Array to match other args @return a new widget

#### struct `FAdvancedPreviewSceneModule::FDetailCustomizationInfo`  
`struct FDetailCustomizationInfo`  
_L22-26_
- desc: Info about a per-instance details customization
- L24 _public member_ `UStruct* Struct;`
- L25 _public member_ `FOnGetDetailCustomizationInstance OnGetDetailCustomizationInstance;`

#### struct `FAdvancedPreviewSceneModule::FPropertyTypeCustomizationInfo`  
`struct FPropertyTypeCustomizationInfo`  
_L29-33_
- desc: Info about a per-instance property type customization
- L31 _public member_ `FName StructName;`
- L32 _public member_ `FOnGetPropertyTypeCustomizationInstance OnGetPropertyTypeCustomizationInstance;`

#### struct `FAdvancedPreviewSceneModule::FDetailDelegates`  
`struct FDetailDelegates`  
_L38-41_
- desc: Info about a Delegates to subscribe to
- L40 _public member_ `FOnPreviewSceneChanged& OnPreviewSceneChangedDelegate;`

#### Free symbols / members of external scopes

- L35 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnPreviewSceneChanged, TSharedRef<FAdvancedPreviewScene>);`

### `Source/Editor/AdvancedPreviewScene/Public/AssetViewerSettings.h` (Public)


#### enum `EProfileConfigVersion`  
`enum class EProfileConfigVersion : uint8`  
_L19-26_
- reflection: `UENUM()`
- L21 _public enumerator_ `PreVersioning = 0`
- L23 _public enumerator_ `ApplyNewGridMaterial` — New Material M_Grid applied on shared engine profiles
- L24 _public enumerator_ `VersionPlusOne`
- L25 _public enumerator_ `LatestVersion = VersionPlusOne - 1`

#### struct `FPreviewSceneProfile`  
`struct FPreviewSceneProfile`  
_L33-251_
- reflection: `USTRUCT()`
- desc: Preview scene profile settings structure.
- L37 _public function_ `FPreviewSceneProfile()`
- L74 _public member_ `FString ProfileName;` — `UPROPERTY(EditAnywhere, config, Category=Profile)` — Name to identify the profile
- L78 _public member_ `bool bSharedProfile;` — `UPROPERTY(EditAnywhere, config, Category = Profile)` — Whether or not this profile should be stored in the Project ini file
- L82 _public member_ `bool bIsEngineDefaultProfile;` — `UPROPERTY(config)` — Whether or not this profile is one of the default profiles included with the engine
- L86 _public member_ `bool bUseSkyLighting;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, config, Category = Lighting)` — Whether or not image based lighting is enabled for the environment cube map
- L90 _public member_ `float DirectionalLightIntensity;` — `UPROPERTY(EditAnywhere, config, Category = Lighting, meta = (UIMin = "0.0", UIMax = "20.0"))` — Manually set the directional light intensity (0.0 - 20.0)
- L94 _public member_ `FLinearColor DirectionalLightColor;` — `UPROPERTY(EditAnywhere, config, Category = Lighting)` — Manually set the directional light colour
- L98 _public member_ `float SkyLightIntensity;` — `UPROPERTY(EditAnywhere, config, Category = Lighting, meta = (UIMin = "0.0", UIMax = "20.0"))` — Manually set the sky light intensity (0.0 - 20.0)
- L102 _public member_ `bool bRotateLightingRig;` — `UPROPERTY(EditAnywhere, config, Category = Lighting, meta = (DisplayName = "Rotate Sky and Directional Lighting"))` — Toggle rotating of the sky and directional lighting, press K and drag for manual rotating of Sky and L for Directional lighting
- L106 _public member_ `bool bShowEnvironment;` — `UPROPERTY(EditAnywhere, config, Category = Environment)` — Toggle visibility of the environment sphere
- L110 _public member_ `bool bShowFloor;` — `UPROPERTY(EditAnywhere, config, Category = Environment, meta=(DisplayAfter="EnvironmentCubeMap"))` — Toggle visibility of the floor mesh
- L115 _public member_ `bool bShowGrid = false;` — `UE_DEPRECATED(5.8, "Removed from preview scene profile since it's not relevant to every viewport")` — `UPROPERTY(config)` — Toggle visibility of floor grid on/off
- L119 _public member_ `FLinearColor EnvironmentColor;` — `UPROPERTY(EditAnywhere, config, Category = Environment, meta=(EditCondition="!bShowEnvironment"))` — The environment color, used if Show Environment is false.
- L123 _public member_ `float EnvironmentIntensity;` — `UPROPERTY(EditAnywhere, config, Category = Lighting, meta = (UIMin = "0.0", UIMax = "20.0", EditCondition="!bShowEnvironment"))` — The environment intensity (0.0 - 20.0), used if Show Environment is false.
- L127 _public member_ `TSoftObjectPtr<UTextureCube> EnvironmentCubeMap;` — `UPROPERTY(EditAnywhere, transient, Category = Environment, meta=(EditCondition="bShowEnvironment", AssetViewInitialViewType=1, AssetViewInitialThumbnailSize=4, AssetViewSettingsName="", ForceShowPluginContent, ForceShowEngineContent))` — Sets environment cube map used for sky lighting and reflections
- L131 _public member_ `FString EnvironmentCubeMapPath;` — `UPROPERTY(config)` — Storing path to environment cube to prevent it from getting cooked
- L135 _public member_ `TSoftObjectPtr<UStaticMesh> EnvironmentFloorMesh;` — `UPROPERTY(EditAnywhere, transient, Category = Environment, meta=(EditCondition="bShowFloor", AssetViewInitialViewType=1, AssetViewInitialThumbnailSize=4, AssetViewSettingsName="", ForceShowPluginContent, ForceShowEngineContent))` — Sets the environment floor mesh
- L139 _public member_ `FString EnvironmentFloorMeshPath;` — `UPROPERTY(config)` — Storing path to the environment floor mesh to prevent it from getting cooked
- L143 _public member_ `FRotator EnvironmentFloorRotation;` — `UPROPERTY(EditAnywhere, config, Category = Environment, meta=(EditCondition="bShowFloor"))` — Sets the rotation of the floor mesh
- L147 _public member_ `FVector EnvironmentFloorScale;` — `UPROPERTY(EditAnywhere, config, Category = Environment, meta=(EditCondition="bShowFloor"))` — Sets the scale of the floor mesh
- L151 _public member_ `TSoftObjectPtr<UMaterialInterface> EnvironmentFloorMaterial;` — `UPROPERTY(EditAnywhere, transient, Category = Environment, meta=(EditCondition="bShowFloor", AssetViewInitialViewType=1, AssetViewInitialThumbnailSize=4, AssetViewSettingsName="", ForceShowPluginContent, ForceShowEngineContent))` — Sets the environment floor material
- L155 _public member_ `FString EnvironmentFloorMaterialPath;` — `UPROPERTY(config)` — Storing path to the environment floor material to prevent it from getting cooked
- L159 _public member_ `bool bPostProcessingEnabled;` — `UPROPERTY(EditAnywhere, config, Category = PostProcessing, AdvancedDisplay)` — Whether or not the Post Processing should influence the scene
- L163 _public member_ `FPostProcessSettings PostProcessingSettings;` — `UPROPERTY(EditAnywhere, config, Category = PostProcessing, AdvancedDisplay, meta=(ShowOnlyInnerProperties))` — Manual set post processing settings
- L167 _public member_ `float LightingRigRotation;` — `UPROPERTY(EditAnywhere, config, Category = Lighting, meta = (UIMin = "0", UIMax = "360"), AdvancedDisplay)` — Current rotation value of the sky in degrees (0 - 360)
- L171 _public member_ `float RotationSpeed;` — `UPROPERTY(EditAnywhere, config, Category = Lighting, AdvancedDisplay)` — Speed at which the sky rotates when rotating is toggled
- L175 _public member_ `FRotator DirectionalLightRotation;` — `UPROPERTY(config)` — Rotation for directional light
- L179 _public member_ `bool bEnableToneMapping;` — `UPROPERTY(EditAnywhere, config, Category = Editing)` — Useful when editing in an unlit view, prevents colors from being adjusted by the tonemapping
- L183 _public member_ `bool bShowMeshEdges;` — `UPROPERTY(EditAnywhere, config, Category = Editing)` — Show wireframes composited on top of the shaded view
- L186 _public function_ `void LoadEnvironmentMap()` — Retrieve the environment map texture using the saved path
- L204 _public function_ `void SetShowFlags(FEngineShowFlags& ShowFlags) const`
- L226 _public prototype_ `UStaticMesh* GetEnvironmentFloorMesh() const;` — Loads and returns the environment floor mesh
- L229 _public prototype_ `UMaterialInterface* GetEnvironmentFloorMaterial() const;` — Loads and returns the environment floor material
- L232 _public prototype_ `void LoadProfileObjects();` — Loads required objects for this profile
- L235 _public prototype_ `void PostEditChangeProperty(FPropertyChangedEvent& InEvent);` — Called when a profile property has been changed
- L237 _public function_ `bool operator==(const FPreviewSceneProfile& InOther) const`
- L242 _public function_ `bool operator!=(const FPreviewSceneProfile& InOther) const`

#### class `UDefaultEditorProfiles`  
`class UDefaultEditorProfiles : public UObject`  
_L256-307_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- L261 _public function_ `UDefaultEditorProfiles()`
- L298 _public prototype_ `const FPreviewSceneProfile* GetProfile(const FString& ProfileName);`
- L300 _public member_ `static FName DefaultProfileName;`
- L301 _public member_ `static FName EditingProfileName;`
- L302 _public member_ `static FName GreyAmbientProfileName;`
- L306 _public member_ `TArray<FPreviewSceneProfile> Profiles;` — `UPROPERTY()` — Collection of default engine-provided profiles used in various editing environments

#### class `ULocalProfiles`  
`class ULocalProfiles : public UObject`  
_L310-317_
- reflection: `UCLASS(config = Editor)`
- inherits: `UObject`
- L316 _public member_ `TArray<FPreviewSceneProfile> Profiles;` — `UPROPERTY(config)` — Collection of local scene profiles

#### class `USharedProfiles`  
`class USharedProfiles : public UObject`  
_L320-335_
- reflection: `UCLASS(config = Editor, defaultconfig)`
- inherits: `UObject`
- L324 _public prototype_ `EProfileConfigVersion GetVersion() const;`
- L325 _public prototype_ `void SetVersionToLatest();`
- L329 _public member_ `TArray<FPreviewSceneProfile> Profiles;` — `UPROPERTY(config)` — Collection of shared scene profiles
- L334 _private member_ `EProfileConfigVersion Version = EProfileConfigVersion::PreVersioning;` — `UPROPERTY(Config)` — Used for auto migrations when new changes are introduced

#### class `UAssetViewerSettings`  
`class UAssetViewerSettings : public UObject, public FEditorUndoClient`  
_L341-395_
- reflection: `UCLASS(MinimalAPI, config=Editor, meta=(DisplayName = "Asset Viewer"))`
- inherits: `UObject,FEditorUndoClient`
- desc: Default asset viewer settings.
- L345 _public prototype_ `UAssetViewerSettings();`
- L348 _public prototype_ `static UAssetViewerSettings* Get();`
- L350 _public prototype_ `static FPreviewSceneProfile& GetCurrentUserProjectProfile();`
- L356 _public prototype_ `void Save(bool bWarnIfFail = true);` — Saves the config data out to the ini files @param bWarnIfFail Should we log a warning if a ini file couldn't be saved.
- L358 _public prototype_ `DECLARE_EVENT_OneParam(UAssetViewerSettings, FOnAssetViewerSettingsChangedEvent, const FName&);`
- L359 _public function_ `FOnAssetViewerSettingsChangedEvent& OnAssetViewerSettingsChanged()`
- L361 _public prototype_ `DECLARE_EVENT(UAssetViewerSettings, FOnAssetViewerProfileAddRemovedEvent);`
- L362 _public function_ `FOnAssetViewerProfileAddRemovedEvent& OnAssetViewerProfileAddRemoved()`
- L364 _public prototype_ `DECLARE_EVENT(UAssetViewerSettings, FOnAssetViewerSettingsPostUndo);`
- L365 _public function_ `FOnAssetViewerSettingsPostUndo& OnAssetViewerSettingsPostUndo()`
- L368 _public prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& InPropertyChangedEvent) override;` — Begin UObject
- L369 _public prototype_ `virtual void PostEditChangeChainProperty(struct FPropertyChangedChainEvent& InPropertyChangedEvent) override;`
- L370 _public prototype_ `virtual void PostInitProperties() override;`
- L374 _public prototype_ `virtual void PostUndo(bool bSuccess) override;` — Begin FEditorUndoClient
- L375 _public prototype_ `virtual void PostRedo(bool bSuccess) override;`
- L380 _public member_ `TArray<FPreviewSceneProfile> Profiles;` — `UPROPERTY(EditAnywhere, transient, Category = Settings, meta=(ShowOnlyInnerProperties))` — Collection of scene profiles
- L383 _public member_ `int32 NumProfiles;` — Cached value to determine whether or not a profile was added or removed
- L386 _protected member_ `FOnAssetViewerSettingsChangedEvent OnAssetViewerSettingsChangedEvent;` — Broadcasts after an scene profile was added or deleted from the asset viewer singleton instance
- L388 _protected member_ `FOnAssetViewerProfileAddRemovedEvent OnAssetViewerProfileAddRemovedEvent;`
- L390 _protected member_ `FOnAssetViewerSettingsPostUndo OnAssetViewerSettingsPostUndoEvent;`
- L394 _protected member_ `bool bFakeConfigValue_HACK;` — `UPROPERTY(Config)` — This will enforce mutable CDO of UAssetViewerSettings transacted

#### Free symbols / members of external scopes

- L16 _macro_ `#define UE_API ADVANCEDPREVIEWSCENE_API`
- L247 _function_ `friend uint32 GetTypeHash(const FPreviewSceneProfile& InItem)`
- L358 _delegate_ `DECLARE_EVENT_OneParam(UAssetViewerSettings, FOnAssetViewerSettingsChangedEvent, const FName&);`
- L361 _delegate_ `DECLARE_EVENT(UAssetViewerSettings, FOnAssetViewerProfileAddRemovedEvent);`
- L364 _delegate_ `DECLARE_EVENT(UAssetViewerSettings, FOnAssetViewerSettingsPostUndo);`

### `Source/Editor/AdvancedPreviewScene/Public/PreviewProfileController.h` (Public)


#### class `FPreviewProfileController`  
`class FPreviewProfileController : public IPreviewProfileController`  
_L20-66_
- inherits: `IPreviewProfileController`
- desc: Controls the access to the preview profiles. It serves as a bridge between the AdvancedPreviewScene and the UnrealEd modules and enable UnrealEd to change or observe change to the active profile. @note This class was created to decouple UnrealEd from AdvancedPreviewScene and prevent circular dependencies between the modules.
- L23 _public prototype_ `FPreviewProfileController();`
- L24 _public prototype_ `virtual ~FPreviewProfileController();`
- L27 _public prototype_ `virtual TArray<FString> GetPreviewProfiles(int32& OutCurrentProfileIndex) const override;` — Returns the list of available preview profiles names.
- L30 _public prototype_ `virtual bool SetActiveProfile(const FString& ProfileName) override;` — Set the specified preview profiles as the active one.
- L33 _public prototype_ `virtual FString GetActiveProfile() const override;` — Returns the preview profiles currently active.
- L36 _public prototype_ `virtual bool HasAnyUserProfiles() const override;` — Returns true if user has added one or more of their own profiles
- L39 _public function_ `virtual FOnPreviewProfileListChanged& OnPreviewProfileListChanged() override` — Invoked after the list of available profiles has changed.
- L42 _public function_ `virtual FOnPreviewProfileChanged& OnPreviewProfileChanged() override` — Invoked after the active preview profile changed.
- L45 _private prototype_ `void UpdateAssetViewerProfiles();`
- L46 _private prototype_ `void EnsureProfilesStateCoherence() const;`
- L50 _private member_ `UAssetViewerSettings* AssetViewerSettings = nullptr;` — Provides the list of available preview profiles along with the profile change delegates (to update the profile combo box selection)
- L53 _private member_ `UEditorPerProjectUserSettings* PerProjectSettings = nullptr;` — Holds the asset viewer profile currently used by the project.
- L56 _private member_ `TArray<FString> AssetViewerProfileNames;` — The list of available profiles.
- L59 _private member_ `int32 CurrentProfileIndex = 0;` — Holds the current profile index in the list. This is kept consistent with the cache list of names.
- L61 _private member_ `FOnPreviewProfileListChanged OnPreviewProfileListChangedDelegate;`
- L62 _private member_ `FOnPreviewProfileChanged OnPreviewSettingChangedDelegate;`
- L64 _private member_ `FDelegateHandle AssetViewerSettingsProfileAddRemoveHandle;`
- L65 _private member_ `FDelegateHandle AssetViewerSettingsChangedHandle;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API ADVANCEDPREVIEWSCENE_API`

### `Source/Editor/AdvancedPreviewScene/Public/SAdvancedPreviewDetailsTab.h` (Public)


#### class `SAdvancedPreviewDetailsTab`  
`class SAdvancedPreviewDetailsTab : public SCompoundWidget`  
_L20-84_
- inherits: `SCompoundWidget`
- L23 _public function_ `SLATE_BEGIN_ARGS(SAdvancedPreviewDetailsTab) : _AdditionalSettings(nullptr)`
- L28 _public prototype_ `SLATE_ARGUMENT(UObject*, AdditionalSettings) SLATE_ARGUMENT(TArray<FAdvancedPreviewSceneModule::FDetailCustomizationInfo>, DetailCustomizations) SLATE_ARGUMENT(TArray<FAdvancedPreviewSceneModule::FPropertyTypeCustomizationInfo>, PropertyTypeCustomizations) SLATE_ARGUMENT(TArray<FAdvancedPreviewSceneModule::FDetailDelegates>, Delegates) SLATE_END_ARGS() SAdvancedPreviewDetailsTab();` — Additional settings object to display in the view
- L45 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<FAdvancedPreviewScene>& InPreviewScene);` — SWidget functions
- L47 _public prototype_ `void Refresh();`
- L50 _protected prototype_ `void CreateSettingsView();`
- L51 _protected prototype_ `void ComboBoxSelectionChanged(TSharedPtr<FString> NewSelection, ESelectInfo::Type );`
- L52 _protected prototype_ `void UpdateSettingsView();`
- L53 _protected prototype_ `void UpdateProfileNames();`
- L54 _protected prototype_ `FReply AddProfileButtonClick();`
- L55 _protected prototype_ `FReply CloneProfileButtonClick();`
- L56 _protected prototype_ `FReply RemoveOrResetProfileButtonClick();`
- L58 _protected prototype_ `void OnAssetViewerSettingsRefresh(const FName& InPropertyName);`
- L59 _protected prototype_ `void OnAssetViewerSettingsPostUndo();`
- L62 _protected member_ `TSharedPtr<IDetailsView> SettingsView;` — Property viewing widget
- L63 _protected member_ `TSharedPtr<STextComboBox> ProfileComboBox;`
- L64 _protected member_ `TWeakPtr<FAdvancedPreviewScene> PreviewScenePtr;`
- L65 _protected member_ `UAssetViewerSettings* DefaultSettings;`
- L66 _protected member_ `UObject* AdditionalSettings;`
- L68 _protected member_ `TArray<TSharedPtr<FString>> ProfileNames;`
- L69 _protected member_ `int32 ProfileIndex;`
- L71 _protected prototype_ `void OnPreviewSceneChanged(TSharedRef<FAdvancedPreviewScene> PreviewScene);`
- L73 _protected member_ `FDelegateHandle RefreshDelegate;`
- L74 _protected member_ `FDelegateHandle AddRemoveProfileDelegate;`
- L75 _protected member_ `FDelegateHandle PostUndoDelegate;`
- L77 _protected member_ `UEditorPerProjectUserSettings* PerProjectSettings;`
- L79 _protected member_ `TArray<FAdvancedPreviewSceneModule::FDetailCustomizationInfo> DetailCustomizations;`
- L81 _protected member_ `TArray<FAdvancedPreviewSceneModule::FPropertyTypeCustomizationInfo> PropertyTypeCustomizations;`
- L83 _protected member_ `TArray<FAdvancedPreviewSceneModule::FDetailDelegates> Delegates;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API ADVANCEDPREVIEWSCENE_API`

### `Source/Editor/AdvancedPreviewScene/Public/ViewportInteractions/ViewportLightRotationInteraction.h` (Public)


#### class `UViewportLightRotationInteraction`  
`class UViewportLightRotationInteraction : public UViewportDragInteraction`  
_L18-35_
- reflection: `UCLASS(MinimalAPI, Transient)`
- inherits: `UViewportDragInteraction`
- desc: Viewport interaction that rotates the directional light. Used in editors with an FAdvancedPreviewScene (e.g., Static Mesh Editor, Persona).
- L23 _public prototype_ `UViewportLightRotationInteraction();`
- L25 _public prototype_ `virtual void Render(IToolsContextRenderAPI* InRenderAPI) override;`
- L27 _public prototype_ `virtual bool CanBeActivated() const override;`
- L28 _public prototype_ `virtual void OnDrag(const FDragArgs& InDrag) override;`
- L29 _public prototype_ `virtual void OnDragDelta(float InMouseDeltaX, float InMouseDeltaY) override;`
- L32 _private member_ `FVector2D ScreenPosition;`
- L34 _private prototype_ `FAdvancedPreviewScene* GetAdvancedPreviewScene() const;`

### `Source/Editor/AdvancedPreviewScene/Public/ViewportInteractions/ViewportSkyRotationInteraction.h` (Public)


#### class `UViewportSkyRotationInteraction`  
`class UViewportSkyRotationInteraction : public UViewportDragInteraction`  
_L16-28_
- reflection: `UCLASS(MinimalAPI, Transient)`
- inherits: `UViewportDragInteraction`
- desc: Viewport interaction that rotates the sky environment. Used in editors with an FAdvancedPreviewScene (e.g., Static Mesh Editor, Persona).
- L21 _public prototype_ `UViewportSkyRotationInteraction();`
- L23 _public prototype_ `virtual bool CanBeActivated() const override;`
- L24 _public prototype_ `virtual void OnDragDelta(float InMouseDeltaX, float InMouseDeltaY) override;`
- L27 _private prototype_ `FAdvancedPreviewScene* GetAdvancedPreviewScene() const;`
