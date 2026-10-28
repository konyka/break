# Editor / PIEPreviewDeviceProfileSelector

- module root: `Source/Editor/PIEPreviewDeviceProfileSelector`
- headers: 8; symbols: 208
- symbol kinds: class=8, delegate=1, function=43, macro=1, member=55, namespace=1, prototype=98, struct=1
- PrivateDependencyModuleNames: ApplicationCore, EditorFramework, Engine, JsonUtilities, MaterialShaderQualitySettings, PIEPreviewDeviceSpecification, RHI, Slate, SlateCore, UnrealEd
- PrivateIncludePathModuleNames: Engine
- PublicDependencyModuleNames: Core, CoreUObject, Json

### `Source/Editor/PIEPreviewDeviceProfileSelector/Private/PIEPreviewDevice.h` (Private)


#### class `FPIEPreviewDevice`  
`class UE_DEPRECATED(5.8, "PIEPreviewDeviceProfileSelector is deprecated and will be removed. Please use the new Preview Json System to preview Devices") FPIEPreviewDevice`  
_L15-125_
- desc: FPIEPreviewDevice class stores specific device settings (FPIEPreviewDeviceSpecifications) and, on request, applies them to the Unreal runtime system
- L18 _private member_ `TSharedPtr<FPIEPreviewDeviceSpecifications> DeviceSpecs;`
- L21 _private member_ `int32 WindowWidth = 0;` — the required size of the display window
- L22 _private member_ `int32 WindowHeight = 0;`
- L25 _private member_ `int32 WindowTitleBarSize = 0;` — window title bar size, needed to compute the final window size
- L28 _private member_ `FMargin ViewportMargin;` — margins used to correctly position the viewport widget inside the provided bezel
- L31 _private member_ `bool bAllowRotation = true;` — whether or not this device can rotate its screen
- L34 _private member_ `bool bDeviceFlipped = false;` — true if we are in a 'rotated' state from the original orientation as provided in the json file
- L37 _private member_ `float ResolutionScaleFactor = 1.0f;` — global scaling factor applied to the whole window
- L40 _private member_ `float DPIScaleFactor = 1.0f;` — DPI scale factor used in window size computations
- L43 _private member_ `bool bShowBezel = true;` — when true extra window space will be allocated and the phone bezel will be rendered
- L46 _private member_ `bool bIgnoreContentScaleFactor = false;` — when true r.MobileContentScaleFactor is ignored
- L48 _private member_ `class UTexture2D* BezelTexture = nullptr;`
- L52 _private prototype_ `void DetermineScreenOrientationRequirements(bool& bNeedPortrait, bool& bNeedLandscape);` — utility function that will attempt to determine the supported device orientations
- L55 _private prototype_ `ERHIFeatureLevel::Type GetPreviewDeviceFeatureLevel() const;` — this should provide the needed RHI feature level based on specified json parameters and Unreal system settings
- L59 _public prototype_ `void ApplyRHIOverrides() const;`
- L62 _public prototype_ `void ComputeViewportSize(const bool bClampWindowSize);` — function that computes the viewport widget offset and needed window size
- L65 _public prototype_ `FPIEPreviewDevice();`
- L68 _public prototype_ `void SetupDevice(const int32 InWindowTitleBarSize);` — call this to run device setup -> load the bezel texture, compute appropriate orientation and apply device specific RHI settings
- L70 _public prototype_ `void ShutdownDevice();`
- L73 _public prototype_ `void ApplyRHIPrerequisitesOverrides() const;` — call this before RHI creation to apply needed setup overrides
- L75 _public prototype_ `TSharedPtr<FPIEPreviewDeviceSpecifications> GetDeviceSpecs();`
- L78 _public prototype_ `FMargin GetViewportMargin() const;` — call this to retrieve the viewport widget padding inside the bezel
- L81 _public prototype_ `int32 GetWindowWidth() const;` — functions to retrieve the needed window size
- L82 _public prototype_ `int32 GetWindowHeight() const;`
- L85 _public prototype_ `int32 GetWindowClientWidth() const;` — functions to retrieve the window client area size
- L86 _public prototype_ `int32 GetWindowClientHeight() const;`
- L89 _public prototype_ `bool IsDeviceFlipped() const;` — returns true if the current device was rotated from the original orientation
- L93 _public prototype_ `void SwitchOrientation(const bool bClampWindowSize);` — call these functions to flag device rotation and specific windows scaling a call to ComputeViewportSize() is necessary to update the window size
- L94 _public prototype_ `void ScaleResolution(const float ScreenFactor, const float DPIFactor, const bool bClampWindowSize);`
- L95 _public prototype_ `void SetBezelVisibility(const bool bBezelVisible, const bool bClampWindowSize);`
- L97 _public prototype_ `bool GetBezelVisibility() const;`
- L100 _public prototype_ `float GetResolutionScale() const;` — returns the current resolution scale factor (float ResolutionScaleFactor)
- L103 _public prototype_ `void GetDeviceDefaultResolution(int32& ScreenWidth, int32& ScreenHeight);` — returns the default device resolution, as specified in the json file
- L106 _public prototype_ `bool IsRotationAllowed() const;` — if true the device supports rotations
- L109 _public prototype_ `void SetIgnoreMobileContentScaleFactor(bool bIgnore);` — call this to enable or disable mobile content scale factor effects
- L112 _public prototype_ `bool GetIgnoreMobileContentScaleFactor() const;` — call to check if the mobile content scale factor is taken into account
- L115 _public prototype_ `void ComputeDeviceResolution(int32& ScreenWidth, int32& ScreenHeight);` — utility function that computes the viewport resolution
- L118 _public prototype_ `void ComputeContentScaledResolution(int32& ScreenWidth, int32& ScreenHeight);` — utility function that computes the resolution after applying r.MobileContentScaleFactor
- L120 _public prototype_ `FString GetProfile() const;`
- L122 _public prototype_ `bool GetSelectorPropertyValue(const FName& PropertyType, FString& PropertyValueOUT) const;`
- L124 _public prototype_ `UTexture2D *GetBezelTexture();`
- L127 _function_ `FORCEINLINE TSharedPtr<FPIEPreviewDeviceSpecifications> FPIEPreviewDevice::GetDeviceSpecs()`
- L132 _function_ `FORCEINLINE FMargin FPIEPreviewDevice::GetViewportMargin() const`
- L137 _function_ `FORCEINLINE int32 FPIEPreviewDevice::GetWindowWidth() const`
- L142 _function_ `FORCEINLINE int32 FPIEPreviewDevice::GetWindowHeight() const`
- L147 _function_ `FORCEINLINE int32 FPIEPreviewDevice::GetWindowClientWidth() const`
- L152 _function_ `FORCEINLINE bool FPIEPreviewDevice::IsDeviceFlipped() const`
- L157 _function_ `FORCEINLINE bool FPIEPreviewDevice::IsRotationAllowed() const`
- L162 _function_ `FORCEINLINE void FPIEPreviewDevice::SwitchOrientation(const bool bClampWindowSize)`
- L169 _function_ `FORCEINLINE void FPIEPreviewDevice::ScaleResolution(const float ScreenFactor, const float DPIFactor, const bool bClampWindowSize)`
- L177 _function_ `FORCEINLINE void FPIEPreviewDevice::SetBezelVisibility(const bool bBezelVisible, const bool bClampWindowSize)`
- L184 _function_ `FORCEINLINE bool FPIEPreviewDevice::GetBezelVisibility() const`
- L189 _function_ `FORCEINLINE float FPIEPreviewDevice::GetResolutionScale() const`
- L194 _function_ `FORCEINLINE UTexture2D *FPIEPreviewDevice::GetBezelTexture()`
- L199 _function_ `FORCEINLINE void FPIEPreviewDevice::SetIgnoreMobileContentScaleFactor(bool bIgnore)`
- L204 _function_ `FORCEINLINE bool FPIEPreviewDevice::GetIgnoreMobileContentScaleFactor() const`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace ERHIFeatureLevel`

### `Source/Editor/PIEPreviewDeviceProfileSelector/Private/PIEPreviewSettings.h` (Private)


#### class `UPIEPreviewSettings`  
`class UE_DEPRECATED(5.8, "PIEPreviewDeviceProfileSelector is deprecated and will be removed. Please use the new Preview Json System to preview Devices") UPIEPreviewSettings : public UObject`  
_L18-31_
- reflection: `UCLASS(MinimalAPI, hidecategories = Object, config = PIEPreviewSettings)`
- inherits: `UObject`
- L24 _public member_ `int32 WindowPosX;` — `UPROPERTY(config)`
- L27 _public member_ `int32 WindowPosY;` — `UPROPERTY(config)`
- L30 _public member_ `float WindowScalingFactor;` — `UPROPERTY(config)`

### `Source/Editor/PIEPreviewDeviceProfileSelector/Private/PIEPreviewWindow.h` (Private)


#### class `SPIEPreviewWindow`  
`class UE_DEPRECATED(5.8, "PIEPreviewDeviceProfileSelector is deprecated and will be removed. Please use the new Preview Json System to preview Devices") SPIEPreviewWindow : public SWindow`  
_L13-140_
- inherits: `SWindow`
- L20 _public prototype_ `SPIEPreviewWindow();` — Default constructor. Use SNew(SPIEPreviewWindow) instead.
- L22 _public prototype_ `~SPIEPreviewWindow();`
- L25 _public prototype_ `void PrepareWindow(FVector2D WindowPosition, const float InitialScaleFactor, TSharedPtr<FPIEPreviewDevice> PreviewDevice);` — call this function set the 'preview device' and set initial values for the position and resolution scaling factor
- L28 _public prototype_ `void PrepareShutdown();` — call this function to perform cleanup
- L31 _public prototype_ `TSharedPtr<class FPIEPreviewDevice> GetDevice();` — retrieves the display device
- L34 _public prototype_ `float GetWindowScaleFactor() const;` — call to retrieve the window current resolution scale factor
- L37 _public prototype_ `void SetWindowScaleFactor(const float ScaleFactor, const bool bStore = true);` — call to set the window resolution scale factor
- L40 _public prototype_ `void RotateWindow();` — call to rotate the window emulating a rotation of the physical device
- L43 _public prototype_ `bool IsRotationAllowed() const;` — wrapper function that will query the same functionality on the device
- L46 _public prototype_ `void FlipBezelVisibility();` — call to enable/disable bezel visibility
- L49 _public prototype_ `bool GetBezelVisibility() const;` — call to determine whether or not the phone bezel is displayed
- L51 _public prototype_ `static int32 GetDefaultTitleBarSize();`
- L54 _public prototype_ `void SetClampWindowSize(const bool bClamp);` — call with a true argument to restrict the window size to the desktop size
- L55 _public prototype_ `bool IsClampingWindowSize() const;`
- L58 _public prototype_ `TSharedRef<SWidget> BuildSettingsMenu();` — creates and returns the settings menu
- L61 _public prototype_ `void SetGameLayerManagerWidget(TSharedPtr<class SGameLayerManager> GameLayerManager);` — we need the game layer manager to control the DPI scaling behavior and this function can be called should be called when the manager is available
- L64 _private prototype_ `virtual EHorizontalAlignment GetTitleAlignment() override;`
- L65 _private prototype_ `virtual TSharedRef<SWidget> MakeWindowTitleBar(const TSharedRef<SWindow>& Window, const TSharedPtr<SWidget>& CenterContent, EHorizontalAlignment CenterContentAlignment) override;`
- L68 _private prototype_ `void SetDevice(TSharedPtr<class FPIEPreviewDevice> InDevice);` — sets the device displayed by this window
- L71 _private prototype_ `bool IsScalingToDeviceSizeFactor(const float ScaleFactor) const;` — returns whether or not the provided ScaleFactor is a 'scale to physical device size' factor
- L74 _private prototype_ `float GetScaleToDeviceSizeFactor() const;` — returns the scaling value reserved for 'scale to physical device size' factor
- L77 _private prototype_ `void ValidatePosition(FVector2D& WindowPos);` — utility function used to correct a given window position if it's out of the display area
- L80 _private prototype_ `void ScaleWindow(float ScaleFactor);` — call to perform resolution scaling on the device
- L83 _private prototype_ `void ComputeBezelOrientation();` — this will properly scale and rotate the bezel to match the orientation of the device
- L86 _private prototype_ `void CreatePIEPreviewBezelOverlay(UTexture2D* pBezelImage);` — function that adds a widget to display the device's bezel
- L91 _private prototype_ `void CreateMenuEntry(class FMenuBuilder& MenuBuilder, FText&& TextEntry, TFunction<ECheckBoxState()>&& IsCheckedFunction, TFunction<void()>&& ExecuteActionFunction);` — @ ExecuteActionFunction - function to be called when this menu item is clicked
- L95 _private prototype_ `void CreateTextMenuEntry(class FMenuBuilder& MenuBuilder, TFunction<FText()>&& CreateTextFunction);` — @ CreateTextFunction - function should return the menu text that we want to display
- L98 _private prototype_ `void UpdateWindow();` — call to compute window size, position on screen and bezel orientation
- L101 _private prototype_ `float ComputeScaleToDeviceSizeFactor() const;` — utility function that will compute a screen and DPI scale factor needed to scale the display window to the physical device size
- L104 _private prototype_ `float ComputeDPIScaleFactor();` — utility function used to retrieve the DPI scaling factor based on window's position
- L107 _private prototype_ `void OnWindowMoved(const TSharedRef<SWindow>& Window);` — callback used when DPI value varies, useful when we need to constrain the window to the physical device size
- L110 _private prototype_ `void OnDisplayDPIChanged(TSharedRef<SWindow> Window);` — callback used when DPI value varies, useful when we need to constrain the window to the physical device size
- L114 _private prototype_ `void UpdateGameLayerManagerDefaultViewport();` — utility function used to control game layer manager's DPI scaling behavior this should be called every time the window is rotated
- L118 _protected member_ `FSlateBrush BezelBrush;` — brush created to display the bezel
- L121 _protected member_ `TSharedPtr<SImage> BezelImage;` — pointer to the actual bezel image
- L124 _protected member_ `TSharedPtr<class FPIEPreviewDevice> Device;` — pointer to the device that this window will display
- L126 _protected member_ `float CachedScaleToDeviceFactor = 0.0f;`
- L127 _protected member_ `float CachedDPIScaleFactor = 0.0f;`
- L130 _protected member_ `bool bClampWindowSizeState = true;` — when true the window size will be restricted to the desktop size
- L132 _protected member_ `float WindowScalingFactor = 0.0f;`
- L134 _protected member_ `TSharedPtr<SPIEPreviewWindowTitleBar> WindowTitleBar;`
- L136 _protected member_ `FDelegateHandle HandleDPIChange;`
- L139 _protected member_ `TSharedPtr<SGameLayerManager> GameLayerManagerWidget;` — Pointer to the game layer manager widget. This is needed because we want to control the DPI scaling behavior
- L142 _function_ `FORCEINLINE bool SPIEPreviewWindow::IsRotationAllowed() const`
- L152 _function_ `FORCEINLINE TSharedPtr<class FPIEPreviewDevice> SPIEPreviewWindow::GetDevice()`
- L157 _function_ `FORCEINLINE void SPIEPreviewWindow::SetClampWindowSize(const bool bClamp)`
- L162 _function_ `FORCEINLINE bool SPIEPreviewWindow::IsClampingWindowSize() const`
- L167 _function_ `FORCEINLINE bool SPIEPreviewWindow::IsScalingToDeviceSizeFactor(const float ScaleFactor) const`
- L173 _function_ `FORCEINLINE float SPIEPreviewWindow::GetWindowScaleFactor() const`
- L178 _function_ `FORCEINLINE float SPIEPreviewWindow::GetScaleToDeviceSizeFactor() const`

### `Source/Editor/PIEPreviewDeviceProfileSelector/Private/PIEPreviewWindowCoreStyle.h` (Private)


#### class `FPIEPreviewWindowCoreStyle`  
`class UE_DEPRECATED(5.8, "PIEPreviewDeviceProfileSelector is deprecated and will be removed. Please use the new Preview Json System to preview Devices") FPIEPreviewWindowCoreStyle`  
_L9-28_
- L14 _public prototype_ `static TSharedRef<class ISlateStyle> Create(const FName& InStyleSetName = "FPI`
- L16 _public prototype_ `static void InitializePIECoreStyle();`
- L20 _public function_ `static const ISlateStyle& Get()` — @return the singleton instance.
- L27 _private member_ `static TSharedPtr< class ISlateStyle > Instance;`

### `Source/Editor/PIEPreviewDeviceProfileSelector/Private/PIEPreviewWindowStyle.h` (Private)


#### struct `FPIEPreviewWindowStyle`  
`struct UE_DEPRECATED(5.8, "PIEPreviewDeviceProfileSelector is deprecated and will be removed. Please use the new Preview Json System to preview Devices") FPIEPreviewWindowStyle : public FSlateWidgetStyle`  
_L13-48_
- reflection: `USTRUCT()`
- inherits: `FSlateWidgetStyle`
- desc: Represents the appearance of an SPIEWindow
- L17 _public prototype_ `FPIEPreviewWindowStyle();`
- L19 _public prototype_ `virtual ~FPIEPreviewWindowStyle() = default;`
- L21 _public prototype_ `virtual void GetResources(TArray< const FSlateBrush* >& OutBrushes) const override;`
- L23 _public member_ `static const FName TypeName;`
- L24 _public function_ `virtual const FName GetTypeName() const override`
- L26 _public prototype_ `static const FPIEPreviewWindowStyle& GetDefault();`
- L30 _public member_ `FButtonStyle ScreenRotationButtonStyle;` — `UPROPERTY()` — Style used to draw the window ScreenRotationButton button
- L31 _public function_ `FPIEPreviewWindowStyle& SetScreenRotationButtonStyle(const FButtonStyle& InScreenRotationButtonStyle)`
- L35 _public member_ `FButtonStyle QuarterMobileContentScaleFactorButtonStyle;` — `UPROPERTY()` — Style used to draw the window 0.25x button
- L36 _public function_ `FPIEPreviewWindowStyle& SetQuarterMobileContentScaleFactorButtonStyle(const FButtonStyle& InQuarterMobileContentScaleFactorButtonStyle)`
- L40 _public member_ `FButtonStyle HalfMobileContentScaleFactorButtonStyle;` — `UPROPERTY()` — Style used to draw the window 0.5x button
- L41 _public function_ `FPIEPreviewWindowStyle& SetHalfMobileContentScaleFactorButtonStyle(const FButtonStyle& InHalfMobileContentScaleFactorButtonStyle)`
- L45 _public member_ `FButtonStyle FullMobileContentScaleFactorButtonStyle;` — `UPROPERTY()` — Style used to draw the window 1X button
- L46 _public function_ `FPIEPreviewWindowStyle& SetFullMobileContentScaleFactorButtonStyle(const FButtonStyle& InFullMobileContentScaleFactorButtonStyle)`

### `Source/Editor/PIEPreviewDeviceProfileSelector/Private/PIEPreviewWindowTitleBar.h` (Private)


#### class `SPIEPreviewWindowTitleBar`  
`class UE_DEPRECATED(5.8, "PIEPreviewDeviceProfileSelector is deprecated and will be removed. Please use the new Preview Json System to preview Devices") SPIEPreviewWindowTitleBar : public SWindowTitleBar`  
_L16-35_
- inherits: `SWindowTitleBar`
- desc: Implements a window PIE title bar widget.
- L23 _private prototype_ `virtual void MakeTitleBarContentWidgets(TSharedPtr< SWidget >& OutLeftContent, TSharedPtr< SWidget >& OutRightContent) override;` — Creates widgets for this window's title bar area.
- L25 _private prototype_ `const FSlateBrush* GetScreenRotationButtonImage() const;`
- L27 _private prototype_ `TSharedPtr<class SPIEPreviewWindow> GetOwnerWindow() const;`
- L31 _private member_ `TSharedPtr<SButton> ScreenRotationButton;` — Holds the screen rotation button.
- L34 _private member_ `TSharedPtr<class SCheckBox> ClampWindowSizeCheckBox;` — Holds the clamp button.
- L37 _function_ `FORCEINLINE TSharedPtr<class SPIEPreviewWindow> SPIEPreviewWindowTitleBar::GetOwnerWindow() const`

### `Source/Editor/PIEPreviewDeviceProfileSelector/Public/PIEPreviewDeviceEnumeration.h` (Public)


#### class `FPIEPreviewDeviceContainerCategory`  
`class UE_DEPRECATED(5.8, "PIEPreviewDeviceProfileSelector is deprecated and will be removed. Please use the new Preview Json System to preview Devices") FPIEPreviewDeviceContainerCategory`  
_L18-41_
- L21 _public function_ `FPIEPreviewDeviceContainerCategory(const FString& InSubDirectoryPath, FText DisplayName) : CategoryDisplayName(DisplayName), SubDirectoryPath(InSubDirectoryPath)`
- L27 _public prototype_ `FName GetCategoryName();`
- L28 _public prototype_ `FText GetCategoryToolTip();`
- L29 _public function_ `const FText& GetCategoryDisplayName() const`
- L30 _public function_ `const FString& GetSubDirectoryPath() const`
- L31 _public function_ `const TArray<TSharedPtr<FPIEPreviewDeviceContainerCategory>>& GetSubCategories() const`
- L32 _public function_ `int GetDeviceStartIndex() const`
- L33 _public function_ `int GetDeviceCount() const`
- L35 _protected member_ `int32 DeviceStartIndex;`
- L36 _protected member_ `int32 DeviceCount;`
- L37 _protected member_ `FText CategoryDisplayName;`
- L38 _protected member_ `FString SubDirectoryPath;`
- L39 _protected member_ `TArray<TSharedPtr<FPIEPreviewDeviceContainerCategory>> SubCategories;`

#### class `FPIEPreviewDeviceContainer`  
`class UE_DEPRECATED(5.8, "PIEPreviewDeviceProfileSelector is deprecated and will be removed. Please use the new Preview Json System to preview Devices") FPIEPreviewDeviceContainer`  
_L43-69_
- L48 _public prototype_ `void EnumerateDeviceSpecifications(const FString& RootDir);` — Recursively iterate through 'RootDir' for all device json files. Sub directories are recorded as categories.
- L50 _public function_ `const TSharedPtr<FPIEPreviewDeviceContainerCategory> GetRootCategory() const`
- L52 _public function_ `const TArray<FString>& GetDeviceSpecifications() const`
- L54 _public function_ `const TArray<FString>& GetDeviceSpecificationsLocalizedName() const`
- L57 _public prototype_ `const TSharedPtr<FPIEPreviewDeviceContainerCategory> FindDeviceContainingCategory(int32 DeviceIndex) const;` — return the category that contains DeviceIndex.
- L60 _private member_ `FString DeviceSpecificationRootDir;`
- L61 _private function_ `FString GetDeviceSpecificationRootDir() const`
- L62 _private member_ `TSharedPtr<FPIEPreviewDeviceContainerCategory> RootCategory;`
- L65 _private member_ `TArray<FString> DeviceSpecifications;` — All device specifications found.
- L66 _private member_ `TArray<FString> DeviceSpecificationsLocalizedName;`
- L67 _private prototype_ `void EnumerateDeviceSpecifications(TSharedPtr<FPIEPreviewDeviceContainerCategory> SubCategory);`
- L68 _private prototype_ `void EnumerateDeviceLocalizedNames();`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API PIEPREVIEWDEVICEPROFILESELECTOR_API`

### `Source/Editor/PIEPreviewDeviceProfileSelector/Public/PIEPreviewDeviceProfileSelectorModule.h` (Public)


#### class `FPIEPreviewDeviceModule`  
`class UE_DEPRECATED(5.8, "PIEPreviewDeviceProfileSelector is deprecated and will be removed. Please use the new Preview Json System to preview Devices") FPIEPreviewDeviceModule : public IPIEPreviewDeviceModule`  
_L16-109_
- inherits: `IPIEPreviewDeviceModule`
- desc: Implements the Preview Device Profile Selector module.
- L20 _public function_ `FPIEPreviewDeviceModule() : bInitialized(false)`
- L25 _public prototype_ `virtual const FString GetRuntimeDeviceProfileName() override;`
- L26 _public prototype_ `virtual bool GetSelectorPropertyValue(const FName& PropertyType, FString& PropertyValueOUT) override;`
- L30 _public prototype_ `virtual void StartupModule() override;`
- L31 _public prototype_ `virtual void ShutdownModule() override;`
- L37 _public prototype_ `virtual ~FPIEPreviewDeviceModule() = default;` — Virtual destructor.
- L39 _public prototype_ `virtual FName GetPreviewPlatformName() override;`
- L41 _public prototype_ `virtual void ApplyPreviewDeviceState() override;`
- L43 _public prototype_ `virtual TSharedRef<SWindow> CreatePIEPreviewDeviceWindow(FVector2D ClientSize, FText WindowTitle, EAutoCenter AutoCenterType, FVector2D ScreenPosition, TOptional<float> MaxWindowWidth, TOptional<float> MaxWindowHeight) override;`
- L46 _public prototype_ `virtual void OnWindowReady(TSharedRef<SWindow> Window) override;` — call this after the window is created and registered to the application to setup display related parameters
- L48 _public prototype_ `virtual const FPIEPreviewDeviceContainer& GetPreviewDeviceContainer() ;`
- L49 _public function_ `TSharedPtr<FPIEPreviewDeviceContainerCategory> GetPreviewDeviceRootCategory() const`
- L51 _public function_ `static bool IsRequestingPreviewDevice()`
- L58 _public prototype_ `virtual void SetGameLayerManagerWidget(TSharedPtr<class SGameLayerManager> GameLayerManager) override;` — we need the game layer manager to control the DPI scaling behavior and this function can be called should be called when the manager is available
- L60 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FAddToDevicePreviewMenu, const FText& DeviceCategoryName, class FMenuBuilder& MenuBuilder);`
- L61 _public member_ `FAddToDevicePreviewMenu AddToDevicePreviewMenuDelegates;`
- L63 _public prototype_ `virtual void SetPreviewDevice(const FString& DeviceName) override;`
- L66 _private function_ `static const TCHAR* GetPreviewDeviceCommandSwitch()`
- L72 _private prototype_ `void OnViewportCreated();` — callback function registered in UGameViewportClient::OnViewportCreated needed to disable mouse capture/lock
- L75 _private prototype_ `void OnEngineInitComplete();` — callback function registered in FCoreDelegates::OnFEngineLoopInitComplete needed to position and show the window
- L77 _private prototype_ `void InitPreviewDevice();`
- L78 _private prototype_ `static FString GetDeviceSpecificationContentDir();`
- L79 _private prototype_ `bool ReadDeviceSpecification();`
- L80 _private prototype_ `FString FindDeviceSpecificationFilePath(const FString& SearchDevice);`
- L82 _private prototype_ `void UpdateDisplayResolution();`
- L85 _private prototype_ `bool ReadWindowConfig();` — this function will attempt to load the last known window position and scaling factor
- L88 _private member_ `bool bInitialized;`
- L89 _private member_ `FString DeviceProfile;`
- L90 _private member_ `FString PreviewDevice;`
- L91 _private member_ `TSharedPtr<FJsonObject> JsonRootObject;`
- L94 _private member_ `FDelegateHandle ViewportCreatedDelegate;` — delegate handle that will be obtained from UGameViewportClient::OnViewportCreated
- L97 _private member_ `FDelegateHandle EngineInitCompleteDelegate;` — delegate handle that will be obtained from FCoreDelegates::OnFEngineLoopInitComplete
- L99 _private member_ `FPIEPreviewDeviceContainer EnumeratedDevices;`
- L101 _private member_ `TSharedPtr<class FPIEPreviewDevice> Device;`
- L103 _private member_ `TWeakPtr<class SPIEPreviewWindow> WindowWPtr;`
- L105 _private member_ `FVector2D InitialWindowPosition;`
- L106 _private member_ `float InitialWindowScaleValue;`
- L108 _private member_ `TSharedPtr<class SGameLayerManager> GameLayerManagerWidget;`

#### Free symbols / members of external scopes

- L60 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FAddToDevicePreviewMenu, const FText& DeviceCategoryName, class FMenuBuilder& MenuBuilder);`
