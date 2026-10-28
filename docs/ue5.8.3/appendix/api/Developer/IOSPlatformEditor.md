# Developer / IOSPlatformEditor

- module root: `Source/Developer/IOS/IOSPlatformEditor`
- headers: 5; symbols: 155
- symbol kinds: class=7, delegate=2, function=21, macro=1, member=64, prototype=56, typedef=4
- PrivateDependencyModuleNames: AudioSettingsEditor, Core, CoreUObject, DesktopPlatform, Engine, FreeImage, GameProjectGeneration, IOSRuntimeSettings, InputCore, MacTargetPlatformControls, MacTargetPlatformSettings, MainFrame, MaterialShaderQualitySettings, PropertyEditor, RHI, RenderCore, ShaderPlatformConfigEditor, SharedSettingsWidgets, Slate, SlateCore, SourceControl, TargetPlatform
- PrivateIncludePathModuleNames: GameProjectGeneration, Settings, TurnkeySupport

### `Source/Developer/IOS/IOSPlatformEditor/Private/IOSCustomIconProjectBuildMutatorFeature.h` (Private)


#### class `FIOSCustomIconProjectBuildMutatorFeature`  
`class FIOSCustomIconProjectBuildMutatorFeature : public IProjectBuildMutatorFeature`  
_L7-11_
- inherits: `IProjectBuildMutatorFeature`
- L10 _public prototype_ `virtual bool RequiresProjectBuild(const FName& InPlatformInfoName, FText& OutReason) const override;`

### `Source/Developer/IOS/IOSPlatformEditor/Private/IOSPlatformEditorModule.h` (Private)


#### class `FIOSPlatformEditorModule`  
`class FIOSPlatformEditorModule : public IModuleInterface`  
_L13-27_
- inherits: `IModuleInterface`
- desc: Module for iOS as a target platform
- L17 _public prototype_ `virtual void StartupModule();`
- L18 _public prototype_ `virtual void ShutdownModule();`
- L20 _public prototype_ `virtual void HandleSelectIOSSection();`
- L23 _public member_ `static FSimpleMulticastDelegate OnSelect;` — Delegate to notify interested parties when the client sources have changed
- L26 _private member_ `FIOSCustomIconProjectBuildMutatorFeature ProjectBuildMutator;`

### `Source/Developer/IOS/IOSPlatformEditor/Private/IOSTargetSettingsCustomization.h` (Private)


#### class `FProvision`  
`class FProvision`  
_L24-33_
- desc: FProvision structure
- L27 _public member_ `FString Name;`
- L28 _public member_ `FString FileName;`
- L29 _public member_ `FString Status;`
- L30 _public member_ `bool bDistribution;`
- L31 _public member_ `bool bSelected;`
- L32 _public member_ `bool bManuallySelected;`

#### class `FCertificate`  
`class FCertificate`  
_L39-47_
- desc: FCertificate structure
- L42 _public member_ `FString Name;`
- L43 _public member_ `FString Status;`
- L44 _public member_ `FString Expires;`
- L45 _public member_ `bool bSelected;`
- L46 _public member_ `bool bManuallySelected;`

#### class `FIOSTargetSettingsCustomization`  
`class FIOSTargetSettingsCustomization : public IDetailCustomization`  
_L54-252_
- inherits: `IDetailCustomization`
- L57 _public prototype_ `~FIOSTargetSettingsCustomization();`
- L60 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L63 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailLayout) override;` — IDetailCustomization interface
- L66 _public prototype_ `EVisibility ShouldShowGenerateButtonForIcon(bool bCannotBeGenerated, FString ImageToCheck) const;`
- L69 _private member_ `TArray<struct FPlatformIconInfo> IconNames;`
- L70 _private member_ `TArray<struct FPlatformIconInfo> LaunchImageNames;`
- L71 _private member_ `TArray<struct FPlatformIconInfo> TvOSImageNames;`
- L73 _private member_ `const FString EngineInfoPath;`
- L74 _private member_ `const FString GameInfoPath;`
- L76 _private member_ `const FString EngineGraphicsPath;`
- L77 _private member_ `const FString GameGraphicsPath;`
- L79 _private member_ `const FString TVOSEngineGraphicsPath;`
- L80 _private member_ `const FString TVOSGameGraphicsPath;`
- L82 _private member_ `IDetailLayoutBuilder* SavedLayoutBuilder;`
- L85 _private member_ `TAttribute<bool> SetupForPlatformAttribute;` — Is the manifest writable?
- L87 _private member_ `bool bProvisionInstalled;`
- L88 _private member_ `bool bCertificateInstalled;`
- L89 _private member_ `bool bShowAllProvisions;`
- L90 _private member_ `bool bShowAllCertificates;`
- L91 _private member_ `bool bManuallySelected;`
- L93 _private member_ `TSharedPtr<FMonitoredProcess> IPPProcess;`
- L94 _private member_ `FTSTicker::FDelegateHandle TickerHandle;`
- L95 _private member_ `TSharedPtr<TArray<ProvisionPtr>> ProvisionList;`
- L96 _private member_ `TArray<ProvisionPtr> FilteredProvisionList;`
- L97 _private member_ `TSharedPtr<SListView<ProvisionPtr> > ProvisionListView;`
- L98 _private member_ `TSharedPtr<SWidgetSwitcher > ProvisionInfoSwitcher;`
- L99 _private member_ `TSharedPtr<TArray<CertificatePtr>> CertificateList;`
- L100 _private member_ `TArray<CertificatePtr> FilteredCertificateList;`
- L101 _private member_ `TSharedPtr<SListView<CertificatePtr> > CertificateListView;`
- L102 _private member_ `TSharedPtr<SWidgetSwitcher > CertificateInfoSwitcher;`
- L103 _private member_ `TAttribute<bool> RunningIPPProcess;`
- L104 _private member_ `TSharedPtr<IPropertyHandle> MobileProvisionProperty;`
- L105 _private member_ `TSharedPtr<IPropertyHandle> SignCertificateProperty;`
- L106 _private member_ `TSharedPtr<IPropertyHandle> ShaderVersionPropertyHandle;`
- L107 _private member_ `TSharedPtr<IPropertyHandle> MinOSPropertyHandle;`
- L108 _private member_ `TSharedPtr<IPropertyHandle> MRTPropertyHandle;`
- L109 _private member_ `TSharedPtr<IPropertyHandle> SM6PropertyHandle;`
- L110 _private member_ `TSharedPtr<IPropertyHandle> AutomaticSigningProperty;`
- L112 _private member_ `FString SelectedProvision;`
- L113 _private member_ `FString SelectedFile;`
- L114 _private member_ `FString SelectedCert;`
- L117 _private prototype_ `FIOSTargetSettingsCustomization();`
- L119 _private prototype_ `void BuildPListSection(IDetailLayoutBuilder& DetailLayout);`
- L120 _private prototype_ `void BuildIconSection(IDetailLayoutBuilder& DetailLayout);`
- L121 _private prototype_ `void BuildRemoteBuildingSection(IDetailLayoutBuilder& DetailLayout);`
- L122 _private prototype_ `void BuildSecondaryRemoteMacBuildingSection(IDetailLayoutBuilder& DetailLayout);`
- L125 _private prototype_ `FReply OpenPlistFolder();` — Navigates to the plist in explorer or finder
- L128 _private prototype_ `void CopySetupFilesIntoProject();` — Copies the setup files for the platform into the project
- L131 _private prototype_ `void BuildImageRow(class IDetailLayoutBuilder& DetailLayout, class IDetailCategoryBuilder& Category, const struct FPlatformIconInfo& Info, const FVector2D& MaxDisplaySize, bool bIsTVOS = false);` — Builds an image row
- L134 _private prototype_ `FReply OnInstallProvisionClicked();` — Install the provision
- L137 _private prototype_ `FReply OnInstallCertificateClicked();` — Install the provision
- L140 _private prototype_ `FReply OnCertificateRequestClicked();` — certificate request
- L142 _private prototype_ `FReply OnGenerateImageClicked(const FString SourceImagePath, const FString TargetImagePath, FIntPoint IconRequiredSize);`
- L145 _private prototype_ `FReply OnGenerateSSHKey(bool IsPrimary);` — ssh key request
- L148 _private prototype_ `const FSlateBrush* GetProvisionStatus() const;` — Get the image to display for the provision status
- L151 _private prototype_ `const FSlateBrush* GetCertificateStatus() const;` — Get the image to display for the certificate status
- L154 _private prototype_ `void FindRequiredFiles();` — find the installed certificates and provisions
- L157 _private prototype_ `void UpdateStatus();` — Update the provision status
- L160 _private prototype_ `void UpdateSSHStatus();` — Update the ssh key status
- L163 _private prototype_ `bool UpdateStatusDelegate(float delay);` — status tick delay
- L166 _private prototype_ `TSharedRef<ITableRow> HandleProvisionListGenerateRow( ProvisionPtr Provision, const TSharedRef<STableViewBase>& OwnerTable );` — handle provision list generate row
- L169 _private prototype_ `TSharedRef<ITableRow> HandleCertificateListGenerateRow( CertificatePtr Certificate, const TSharedRef<STableViewBase>& OwnerTable );` — handle certificate list generate row
- L172 _private prototype_ `void HandleAllProvisionsHyperlinkNavigate( bool AllProvisions );` — handle which set of provisions to view
- L175 _private prototype_ `void HandleAllCertificatesHyperlinkNavigate( bool AllCertificates );` — handle which set of provisions to view
- L178 _private prototype_ `void FilterLists();` — filter the lists based on the settings
- L181 _private prototype_ `bool IsImportEnabled() const;` — returns whether we are importing or not
- L184 _private prototype_ `bool IsAutomaticSigningEnabled() const;` — returns whether we are importing or not
- L187 _private prototype_ `void OnBundleIdentifierChanged(const FText& NewText, ETextCommit::Type, TSharedRef<IPropertyHandle> InPropertyHandle);` — updates the bundle identifier if it is valid and checks for a matching provision/certificate
- L190 _private prototype_ `void OnBundleIdentifierTextChanged(const FText& NewText, ETextCommit::Type, TSharedRef<IPropertyHandle> InPropertyHandle);` — posts an error if the bundle identifier has become invalid
- L193 _private prototype_ `void OnIOSTeamIDTextChanged(const FText& NewText, ETextCommit::Type, TSharedRef<IPropertyHandle> InPropertyHandle);` — posts an error if the bundle identifier has become invalid
- L196 _private prototype_ `bool IsBundleIdentifierValid(const FString& inIdentifier);` — returns true if the given string is a valid bundle identifier
- L199 _private prototype_ `void OnRemoteServerChanged(const FText& NewText, ETextCommit::Type, TSharedRef<IPropertyHandle> InPropertyHandle);` — updates the text in the ini file and checks for a valid provision/certificate
- L201 _private prototype_ `void HandleProvisionChanged(FString Provision);`
- L203 _private prototype_ `void HandleCertificateChanged(FString Certificate);`
- L206 _private prototype_ `TSharedRef<SWidget> OnGetShaderVersionContent();` — Delegate handler to get the list of shader standards
- L209 _private prototype_ `FText GetShaderVersionDesc() const;` — Delegate handler to get the description of the shader standard
- L212 _private prototype_ `TSharedRef<SWidget> OnGetMinVersionContent();` — Delegate handler to get the list of shader standards
- L215 _private prototype_ `FText GetMinVersionDesc() const;` — Delegate handler to get the description of the shader standard
- L217 _private prototype_ `void SetShaderStandard(int32 Value);`
- L219 _private prototype_ `void UpdateShaderStandardWarning();`
- L221 _private prototype_ `void UpdateOSVersionWarning();`
- L223 _private prototype_ `void UpdateMetalMobileWarning();`
- L225 _private prototype_ `void UpdateGLVersionWarning();`
- L227 _private prototype_ `void SetMinVersion(int32 Value);`
- L230 _private prototype_ `FText GetBundleText(TSharedRef<IPropertyHandle> InPropertyHandle) const;`
- L233 _private prototype_ `FText GetIOSTeamIDText(TSharedRef<IPropertyHandle> InPropertyHandle) const;`
- L236 _private prototype_ `void OnSelect();` — Module callback for when the iOS settings tab is selected
- L238 _private member_ `TSharedPtr< SEditableTextBox > BundleIdTextBox;`
- L240 _private member_ `TSharedPtr< SEditableTextBox > IOSTeamIDTextBox;`
- L243 _private member_ `TSharedPtr< SErrorText > ShaderVersionWarningTextBox;` — Reference to the shader version property warning text box.
- L246 _private member_ `TSharedPtr< SErrorText > IOSVersionWarningTextBox;` — Reference to the shader version property warning text box.
- L249 _private member_ `TSharedPtr< SErrorText > GLVersionWarningTextBox;` — Reference to the os version property warning text box.
- L251 _private member_ `FAudioPluginWidgetManager AudioPluginWidgetManager;` — Structure used to manage audio plugin platform settings

#### Free symbols / members of external scopes

- L34 _typedef_ `typedef TSharedPtr<class FProvision> ProvisionPtr;`
- L35 _typedef_ `typedef TSharedPtr<TArray<ProvisionPtr>> ProvisionListPtr;`
- L48 _typedef_ `typedef TSharedPtr<class FCertificate> CertificatePtr;`
- L49 _typedef_ `typedef TSharedPtr<TArray<CertificatePtr>> CertificateListPtr;`

### `Source/Developer/IOS/IOSPlatformEditor/Private/SCertificateListRow.h` (Private)


#### class `SCertificateListRow`  
`class SCertificateListRow : public SMultiColumnTableRow<CertificatePtr>`  
_L26-188_
- inherits: `SMultiColumnTableRow<CertificatePtr>`
- desc: Implements a row widget for the certificate list view.
- L31 _public function_ `SLATE_BEGIN_ARGS(SCertificateListRow)`
- L44 _public function_ `void Construct( const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTableView )` — Constructs the widget. @param InArgs The arguments.
- L62 _public function_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn( const FName& ColumnName ) override`
- L112 _private function_ `FText HandleNameText( ) const` — Callback for getting the text in the 'Name' column.
- L118 _private function_ `FText HandleStatusTextBlockText( ) const` — Callback for getting the status text.
- L128 _private function_ `FSlateColor HandleStatusTextColorAndOpacity( ) const` — Callback for getting the status text color.
- L142 _private function_ `FSlateColor HandleSelectedColorAndOpacity( ) const` — Callback for getting the status text color.
- L152 _private function_ `FText HandleExpiresText( ) const` — Callback for getting the text in the 'Expires' column.
- L157 _private function_ `ECheckBoxState HandleChecked() const`
- L162 _private function_ `void HandleCheckStateChanged(ECheckBoxState InState)`
- L185 _private member_ `CertificatePtr Certificate;` — Holds the target device service used to populate this row.
- L186 _private member_ `CertificateListPtr CertificateList;`
- L187 _private member_ `FOnCertificateChanged OnCertificateChanged_Handler;`

#### Free symbols / members of external scopes

- L21 _delegate_ `DECLARE_DELEGATE_OneParam(FOnCertificateChanged, FString);`
- L21 _prototype_ `DECLARE_DELEGATE_OneParam(FOnCertificateChanged, FString);`

### `Source/Developer/IOS/IOSPlatformEditor/Private/SProvisionListRow.h` (Private)


#### class `SProvisionListRow`  
`class SProvisionListRow : public SMultiColumnTableRow<ProvisionPtr>`  
_L31-244_
- inherits: `SMultiColumnTableRow<ProvisionPtr>`
- desc: Implements a row widget for the provision list view.
- L36 _public function_ `SLATE_BEGIN_ARGS(SProvisionListRow)`
- L49 _public function_ `void Construct( const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTableView )` — Constructs the widget. @param InArgs The arguments.
- L85 _public function_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn( const FName& ColumnName ) override`
- L147 _private function_ `FText HandleNameText( ) const` — Callback for getting the text in the 'Name' column.
- L153 _private function_ `FText HandleFileText( ) const` — Callback for getting the text in the 'File' column.
- L159 _private function_ `FText HandleStatusTextBlockText( ) const` — Callback for getting the status text.
- L177 _private function_ `FSlateColor HandleStatusTextColorAndOpacity( ) const` — Callback for getting the status text color.
- L195 _private function_ `FSlateColor HandleSelectedColorAndOpacity( ) const` — Callback for getting the status text color.
- L205 _private function_ `ECheckBoxState HandleDistribution( ) const` — Callback to determine distribution
- L210 _private function_ `ECheckBoxState HandleChecked() const`
- L215 _private function_ `void HandleCheckStateChanged(ECheckBoxState InState)`
- L238 _private member_ `ProvisionPtr Provision;` — Holds the target device service used to populate this row.
- L239 _private member_ `ProvisionListPtr ProvisionList;`
- L240 _private member_ `FOnProvisionChanged OnProvisionChanged_Handler;`
- L242 _private member_ `static bool bInitialized;`
- L243 _private member_ `static FCheckBoxStyle ProvisionCheckBoxStyle;`

#### Free symbols / members of external scopes

- L24 _macro_ `#define IMAGE_BRUSH( RelativePath, ... ) FSlateImageBrush( FPaths::EngineContentDir() / TEXT("Editor/Slate") / RelativePath + TEXT(".png"), __VA_ARGS__ )`
- L26 _delegate_ `DECLARE_DELEGATE_OneParam(FOnProvisionChanged, FString);`
- L26 _prototype_ `DECLARE_DELEGATE_OneParam(FOnProvisionChanged, FString);`
