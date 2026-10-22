# Plugins / TakeRecorderEditor

- module root: `Plugins/VirtualProduction/Takes/Source/TakeRecorderEditor`
- headers: 44; symbols: 657
- symbol kinds: class=31, delegate=5, enum=2, enumerator=8, function=73, member=145, namespace=72, prototype=302, struct=16, variable=3
- PrivateDependencyModuleNames: AppFramework, AssetDefinition, AssetRegistry, ClassViewer, ContentBrowser, Core, CoreUObject, EditorFramework, EditorStyle, EditorWidgets, Engine, InputCore, LevelEditor, LevelSequence, MessageLog, MovieScene, MovieSceneTools, MovieSceneTracks, NamingTokens, NamingTokensUI, Projects, PropertyEditor, SequencerCore, Slate, SlateCore, TakeMovieScene, TakeRecorder, TakeTrackRecorders, TakesCore, TimeManagement, ToolMenus, ToolWidgets, UnrealEd, WorkspaceMenuStructure
- PublicDependencyModuleNames: EditorSubsystem, Sequencer

### `Plugins/VirtualProduction/Takes/Source/TakeRecorderEditor/Private/AssetDefinition_TakePreset.h` (Private)


#### class `UAssetDefinition_TakePreset`  
`class UAssetDefinition_TakePreset : public UAssetDefinitionDefault`  
_L11-28_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L17 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L18 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L19 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L20 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`
- L25 _public prototype_ `virtual FAssetOpenSupport GetAssetOpenSupport(const FAssetOpenSupportArgs& OpenSupportArgs) const override;`
- L26 _public prototype_ `virtual EAssetCommandResult OpenAssets(const FAssetOpenArgs& OpenArgs) const override;`

### `Plugins/VirtualProduction/Takes/Source/TakeRecorderEditor/Private/Customization/AudioInputChannelPropertyCustomization.h` (Private)


#### class `UE::TakeRecorder::FAudioInputChannelPropertyCustomization`  
`class FAudioInputChannelPropertyCustomization : public IPropertyTypeCustomization`  
_L17-37_
- inherits: `IPropertyTypeCustomization`
- L22 _public function_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& )`
- L23 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> PropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils);`
- L28 _private member_ `TSharedPtr<IPropertyHandle> InputDeviceChannelHandle;`
- L29 _private member_ `TArray<TSharedPtr<int32>> InputDeviceChannelArray;`
- L30 _private member_ `TSharedPtr<STextBlock> InputChannelTitleBlock;`
- L31 _private member_ `TSharedPtr<SComboBox<TSharedPtr<int32>>> ChannelComboBox;`
- L33 _private prototype_ `void BuildInputChannelArray();`
- L34 _private prototype_ `void RebuildInputChannelArray();`
- L36 _private prototype_ `TSharedRef<SWidget> MakeInputChannelSelectorWidget();`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace TakeRecorder` (scope `UE`)

### `Plugins/VirtualProduction/Takes/Source/TakeRecorderEditor/Private/Customization/NamingTokenDirectoryPathCustomization.h` (Private)


#### class `FNamingTokenDirectoryPathStructCustomization`  
`class FNamingTokenDirectoryPathStructCustomization : public IPropertyTypeCustomization`  
_L25-67_
- inherits: `IPropertyTypeCustomization`
- desc: A Naming Tokens version of the FDirectoryPathStructCustomization, mostly identical apart from using the NamingTokens box instead of a normal text box. We may want to move this under the NamingTokens plugin for use with other plugins.
- L28 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L31 _public prototype_ `virtual void CustomizeHeader( TSharedRef<class IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils ) override;` — IPropertyTypeCustomization interface
- L33 _public prototype_ `virtual void CustomizeChildren( TSharedRef<class IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils ) override;`
- L38 _private prototype_ `FReply OnPickContent(TSharedRef<IPropertyHandle> PropertyHandle, const bool bForceShowPluginContent, const bool bForceShowEngineContent);` — Delegate used to display a directory picker
- L41 _private prototype_ `FReply OnPickDirectory(TSharedRef<IPropertyHandle> PropertyHandle, const bool bRelativeToGameContentDir, const bool bUseRelativePaths) const;` — Delegate used to display a directory picker
- L44 _private prototype_ `bool IsValidPath(const FString& AbsolutePath, const bool bRelativeToGameContentDir, FText* const OutReason = nullptr) const;` — Check whether that the chosen path is valid
- L47 _private prototype_ `void OnPathPicked(const FString& Path, TSharedRef<IPropertyHandle> PropertyHandle);` — Called when a path is picked from the path picker
- L50 _private prototype_ `bool IsBrowseEnabled(TSharedRef<IPropertyHandle> PropertyHandle) const;` — Delegate to determine whether the browse button should be enabled
- L54 _private member_ `TSharedPtr<SButton> BrowseButton;` — The browse button widget
- L57 _private member_ `TSharedPtr<SButton> PickerButton;` — The pick button widget
- L60 _private member_ `TSharedPtr<IMenu> PickerMenu;` — The pick button popup menu
- L63 _private member_ `TSharedPtr<SNamingTokensEditableTextBox> NamingTokensEditableTextBox;` — The naming tokens text box
- L66 _private member_ `FString AbsoluteGameContentDir;` — Absolute path to the game content directory

### `Plugins/VirtualProduction/Takes/Source/TakeRecorderEditor/Private/Customization/RecordedPropertyCustomization.h` (Private)


#### class `UE::TakeRecorder::FRecordedPropertyCustomization`  
`class FRecordedPropertyCustomization : public IPropertyTypeCustomization`  
_L10-21_
- inherits: `IPropertyTypeCustomization`
- L12 _private member_ `static const FString PropertyPathDelimiter;`
- L15 _private prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils );`
- L16 _private function_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> PropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils )`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace TakeRecorder` (scope `UE`)

### `Plugins/VirtualProduction/Takes/Source/TakeRecorderEditor/Private/Customization/RecorderPropertyMapCustomization.h` (Private)


#### class `UE::TakeRecorder::FRecorderPropertyMapCustomization`  
`class FRecorderPropertyMapCustomization : public IPropertyTypeCustomization`  
_L16-35_
- inherits: `IPropertyTypeCustomization`
- L20 _public member_ `static const FString PropertyPathDelimiter;`
- L23 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils);`
- L24 _public prototype_ `virtual IDetailGroup& GetOrCreateDetailGroup(IDetailChildrenBuilder& ChildBuilder, TMap<FString, IDetailGroup*>& GroupMap, TSharedPtr<IPropertyHandleArray> PropertiesArray, FString& GroupName);`
- L25 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> PropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils);`
- L30 _private prototype_ `void OnGroupCheckStateChanged( ECheckBoxState InNewState, TSharedPtr<IPropertyHandleArray> RecordedPropertiesArrayHandle, FString GroupName) const;`
- L31 _private prototype_ `ECheckBoxState OnGroupGetCheckState( TSharedPtr<IPropertyHandleArray> RecordedPropertiesArrayHandle, FString GroupName) const;`
- L33 _private prototype_ `void OnCheckStateChanged( ECheckBoxState InNewState, TSharedRef<IPropertyHandle> PropertyHandle );`
- L34 _private prototype_ `ECheckBoxState OnGetCheckState( TSharedRef<IPropertyHandle> PropertyHandle ) const;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace TakeRecorder` (scope `UE`)

### `Plugins/VirtualProduction/Takes/Source/TakeRecorderEditor/Private/Customization/RecorderSourceObjectCustomization.h` (Private)


#### class `UE::TakeRecorder::FRecorderSourceObjectCustomization`  
`class FRecorderSourceObjectCustomization : public IDetailCustomization`  
_L10-21_
- inherits: `IDetailCustomization`
- L15 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`
- L20 _private prototype_ `FText ComputeTitle(const TSharedPtr<const IDetailsView>& DetailsView) const;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace TakeRecorder` (scope `UE`)

### `Plugins/VirtualProduction/Takes/Source/TakeRecorderEditor/Private/Customization/TakePresetRecorderCustomization.h` (Private)


#### class `UE::TakeRecorder::FTakePresetRecorderCustomization`  
`class FTakePresetRecorderCustomization : public IPropertyTypeCustomization`  
_L14-31_
- inherits: `IPropertyTypeCustomization`
- desc: Asks the user whether they're sure they want to change the UTakePresetSettings::TargetRecordClass, as that usually requires clearing the pending change.
- L18 _public function_ `explicit FTakePresetRecorderCustomization(FPromptChangeTargetRecordClass PromptUserDelegate) : PromptChangeTargetRecordClassDelegate(MoveTemp(PromptUserDelegate))`
- L23 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L24 _public function_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> PropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils) override`
- L30 _private member_ `FPromptChangeTargetRecordClass PromptChangeTargetRecordClassDelegate;` — Possibly asks the user whether they are sure they want to change TargetRecordClass. Returns whether the change can be made.

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace TakeRecorder` (scope `UE`)
- L11 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FPromptChangeTargetRecordClass, const UClass* );` — Possibly asks the user whether they are sure they want to change TargetRecordClass. Returns whether the change can be made.
- L11 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FPromptChangeTargetRecordClass, const UClass* );` (scope `UE::TakeRecorder`) — Possibly asks the user whether they are sure they want to change TargetRecordClass. Returns whether the change can be made.

### `Plugins/VirtualProduction/Takes/Source/TakeRecorderEditor/Private/Customization/TakeRecorderAudioSettingsCustomization.h` (Private)


#### class `FAudioInputDevicePropertyCustomization`  
`class FAudioInputDevicePropertyCustomization : public IPropertyTypeCustomization`  
_L12-49_
- inherits: `IPropertyTypeCustomization`
- L16 _public function_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override`
- L18 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> PropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L22 _private prototype_ `static FString GetDeviceNameFromInfoProperty(const TSharedPtr<IPropertyHandle>& InDeviceInfoHandle);`
- L24 _private prototype_ `FString GetDeviceIdFromInfoProperty(const TSharedPtr<IPropertyHandle>& InDeviceInfoHandle);`
- L25 _private prototype_ `int32 GetChannelCountFromInfoProperty(const TSharedPtr<IPropertyHandle>& InDeviceInfoHandle);`
- L27 _private prototype_ `bool GetIsDefaultFromInfoProperty(const TSharedPtr<IPropertyHandle>& InDeviceInfoHandle);`
- L28 _private prototype_ `void BuildAudioInputDeviceList();`
- L29 _private prototype_ `TSharedRef<SWidget> CreateDeviceListComboButton();`
- L31 _private prototype_ `void RequestsDeviceListRefresh();`
- L32 _private prototype_ `TSharedRef<SWidget> OnGenerateDeviceMenu();`
- L33 _private prototype_ `void MenuItemRefreshSelected();`
- L34 _private prototype_ `void MenuItemDeviceSelected(TSharedPtr<IPropertyHandle> InDeviceInfoHandle);`
- L36 _private prototype_ `void OnDeviceListChanged();`
- L37 _private prototype_ `void UpdateDeviceCombobxEnabled();`
- L38 _private prototype_ `void SynchronizeWidgetStates();`
- L40 _private member_ `TSharedPtr<IPropertyHandle> UseSystemDefaultHandle;`
- L41 _private member_ `TSharedPtr<IPropertyHandle> InputDeviceHandle;`
- L42 _private member_ `TSharedPtr<IPropertyHandle> BufferSizeHandle;`
- L43 _private member_ `TSharedPtr<IPropertyHandleArray> DeviceInfoArrayHandle;`
- L45 _private member_ `TSharedPtr<IPropertyHandle> SelectedAudioInputDevice;`
- L46 _private member_ `TArray<TSharedPtr<IPropertyHandle>> AudioInputDevices;`
- L47 _private member_ `TSharedPtr<SSimpleComboButton> DeviceListComboButton;`
- L48 _private member_ `FString DefaultDeviceId;`

#### class `TakeRecorderAudioSettingsUtils`  
`class TakeRecorderAudioSettingsUtils`  
_L51-57_
- L55 _public prototype_ `static UTakeRecorderAudioInputSettings* GetTakeRecorderAudioInputSettings();`
- L56 _public prototype_ `static void RefreshAudioInputSettings();`

### `Plugins/VirtualProduction/Takes/Source/TakeRecorderEditor/Private/Customization/TakeRecorderNamingTokenCustomizationUtilities.h` (Private)


#### class `UE::TakeRecorder::NamingTokens::FDirectoryPathPropertyTypeIdentifier`  
`class FDirectoryPathPropertyTypeIdentifier : public IPropertyTypeIdentifier`  
_L19-25_
- inherits: `IPropertyTypeIdentifier`
- desc: Scopes our directory path customization to naming token directory paths only.
- L21 _private function_ `virtual bool IsPropertyTypeCustomized(const IPropertyHandle& PropertyHandle) const override`

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace TakeRecorder` (scope `UE`)
- L16 _namespace_ `namespace NamingTokens` (scope `UE::TakeRecorder`)
- L28 _function_ `inline TSharedRef<SNamingTokensEditableTextBox> CreateNamingTokensWidgetForProperty(const TSharedPtr<IPropertyHandle>& InPropertyHandle)` (scope `UE::TakeRecorder::NamingTokens`) — Creates a naming tokens widget which will respond to a property handle.
- L39 _function_ `` (scope `UE::TakeRecorder::NamingTokens::CreateNamingTokensWidgetForProperty`)
- L89 _function_ `inline void HandleNamingTokensRow(IDetailPropertyRow& InPropertyRow)` (scope `UE::TakeRecorder::NamingTokens`) — Given a detail property row create a custom naming tokens widget.

### `Plugins/VirtualProduction/Takes/Source/TakeRecorderEditor/Private/Customization/TakeRecorderProjectSettingsCustomization.h` (Private)


#### class `FTakeRecorderProjectSettingsCustomization`  
`class FTakeRecorderProjectSettingsCustomization : public IDetailCustomization`  
_L16-195_
- inherits: `IDetailCustomization`
- L18 _private function_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailLayout) override`
- L119 _private function_ `void CustomizeHitchProtection(IDetailLayoutBuilder& DetailLayout)`
- L151 _private function_ `void AddHitchProtectionEnabledProperty(IDetailCategoryBuilder& HitchProtectionCategory, const TSharedRef<IPropertyHandle> HitchProtectionSettings)`
- L180 _private function_ `template<typename TCallback> static void ForEachChild(SWidget& Widget, TCallback&& Callback)`

#### Free symbols / members of external scopes

- L136 _function_ `` (scope `FTakeRecorderProjectSettingsCustomization::CustomizeHitchProtection`)
- L139 _function_ `` (scope `FTakeRecorderProjectSettingsCustomization::CustomizeHitchProtection::__anonb338d5200102`)
- L159 _function_ `` (scope `FTakeRecorderProjectSettingsCustomization::AddHitchProtectionEnabledProperty`)
- L168 _function_ `` (scope `FTakeRecorderProjectSettingsCustomization::AddHitchProtectionEnabledProperty::__anonb338d5200402`)
- L191 _function_ `` (scope `FTakeRecorderProjectSettingsCustomization::ForEachChild`)

### `Plugins/VirtualProduction/Takes/Source/TakeRecorderEditor/Private/ScopedSequencerPanel.h` (Private)


#### struct `FScopedSequencerPanel`  
`struct FScopedSequencerPanel : public TSharedFromThis<FScopedSequencerPanel>`  
_L20-58_
- inherits: `TSharedFromThis<FScopedSequencerPanel>`
- desc: Scoped object that manages opening and closing an externally supplied level sequence based on user-settings. This class will invoke the sequencer tab for the sequence on construction if the user settings state that it should be open. It also closes the sequence on destruction, and keeps track of whether the sequence should or should not be open when toggled.
- L23 _public prototype_ `FScopedSequencerPanel(const TAttribute<ULevelSequence*>& InLevelSequenceAttribute);` — Constructor that opens the level sequence if UTakeRecorderUserSettings::bIsSequencerOpen is true
- L26 _public prototype_ `~FScopedSequencerPanel();` — Destructor that closes the level sequence if it's currently open
- L31 _public prototype_ `bool IsOpen() const;` — Check whether the sequence is currently open
- L36 _public prototype_ `void Open();` — Open the level sequence in sequencer without changing bIsSequencerOpen
- L41 _public prototype_ `void Close();` — Close the level sequence in sequencer if it's open, without changing bIsSequencerOpen
- L46 _public prototype_ `TSharedRef<SWidget> MakeToggleButton();` — Make a standard button for toggling the sequence
- L50 _private prototype_ `void Toggle(ECheckBoxState CheckState);`
- L51 _private prototype_ `ECheckBoxState GetToggleCheckState() const;`
- L53 _private prototype_ `static bool IsOpen(ULevelSequence* InSequence);`
- L54 _private prototype_ `static void Open(ULevelSequence* InSequence);`
- L55 _private prototype_ `static void Close(ULevelSequence* InSequence);`
- L57 _private member_ `TAttribute<ULevelSequence*> LevelSequenceAttribute;`

### `Plugins/VirtualProduction/Takes/Source/TakeRecorderEditor/Private/TakePresetToolkit.h` (Private)


#### class `FTakePresetToolkit`  
`class FTakePresetToolkit : public FAssetEditorToolkit , public FGCObject`  
_L9-64_
- inherits: `FAssetEditorToolkit,FGCObject`
- L23 _public prototype_ `void Initialize(const EToolkitMode::Type Mode, const TSharedPtr<IToolkitHost>& InitToolkitHost, UTakePreset* TakePreset);` — Initialize this asset editor. @param Mode Asset editing mode for this editor (standalone or world-centric). @param InitToolkitHost When Mode is WorldCentric, this is the level editor instance to spawn this editor within. @param LevelSequence The animation to edit. @param TrackEditorDelegates Delegates to call to create auto-key handlers for this sequencer.
- L25 _public function_ `UTakePreset* GetTakePreset() const`
- L30 _public function_ `const FSlateBrush* GetTabIcon() const`
- L36 _public prototype_ `DECLARE_EVENT(FTakePresetToolkit, FTakePresetToolkitClosed);` — Called when the tab manager is changed
- L37 _public function_ `FTakePresetToolkitClosed& OnClosed()`
- L41 _private prototype_ `virtual FText GetBaseToolkitName() const override;`
- L42 _private prototype_ `virtual FName GetToolkitFName() const override;`
- L43 _private prototype_ `virtual FLinearColor GetWorldCentricTabColorScale() const override;`
- L44 _private prototype_ `virtual FString GetWorldCentricTabPrefix() const override;`
- L45 _private function_ `virtual void RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager) override`
- L46 _private function_ `virtual void UnregisterTabSpawners(const TSharedRef<FTabManager>& InTabManager) override`
- L47 _private prototype_ `virtual void OnClose() override;`
- L49 _private prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;`
- L50 _private function_ `virtual FString GetReferencerName() const override`
- L58 _private member_ `TObjectPtr<UTakePreset> TakePreset;`
- L60 _private member_ `static const FName TabId;`
- L63 _private member_ `FTakePresetToolkitClosed OnClosedEvent;` — Event that is called when this toolkit is closed

#### Free symbols / members of external scopes

- L36 _delegate_ `DECLARE_EVENT(FTakePresetToolkit, FTakePresetToolkitClosed);` — Called when the tab manager is changed

### `Plugins/VirtualProduction/Takes/Source/TakeRecorderEditor/Private/TakeRecorderCommands.h` (Private)


#### class `FTakeRecorderCommands`  
`class FTakeRecorderCommands : public TCommands<FTakeRecorderCommands>`  
_L8-20_
- inherits: `TCommands<FTakeRecorderCommands>`
- L11 _public prototype_ `FTakeRecorderCommands();`
- L13 _public member_ `TSharedPtr<FUICommandInfo> StartRecording;`
- L14 _public member_ `TSharedPtr<FUICommandInfo> StopRecording;`
- L16 _public member_ `TSharedPtr<FUICommandInfo> ClearRecordingIntegrityData;`
- L19 _public prototype_ `virtual void RegisterCommands() override;` — Initialize commands

### `Plugins/VirtualProduction/Takes/Source/TakeRecorderEditor/Private/TakeRecorderEditorModule.h` (Private)


#### class `FTakeRecorderEditorModule`  
`class FTakeRecorderEditorModule : public IModuleInterface, public FGCObject`  
_L23-111_
- inherits: `IModuleInterface,FGCObject`
- L26 _public prototype_ `FTakeRecorderEditorModule();`
- L29 _public prototype_ `virtual void StartupModule() override;`
- L30 _public prototype_ `virtual void ShutdownModule() override;`
- L36 _private prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;`
- L37 _private function_ `virtual FString GetReferencerName() const override`
- L40 _private prototype_ `void RegisterDetailCustomizations();`
- L41 _private prototype_ `void UnregisterDetailCustomizations();`
- L43 _private prototype_ `void RegisterLevelEditorExtensions();`
- L44 _private prototype_ `void UnregisterLevelEditorExtensions() const;`
- L46 _private prototype_ `void RegisterSettings();`
- L47 _private prototype_ `void UnregisterSettings();`
- L51 _private prototype_ `void RegisterMessageLogListing();` — Register / unregister the "TakeRecorder" listing with the editor Message Log so messages written via FMessageLog("TakeRecorder") get a labelled entry in the Message Log UI.
- L52 _private prototype_ `void UnregisterMessageLogListing();`
- L54 _private prototype_ `void RegisterMenus();`
- L56 _private prototype_ `void OnEditorClose();`
- L59 _private prototype_ `void OnRecordingInitialized(UTakeRecorder* InRecorder);` — Callback when a new recording is initialized.
- L61 _private prototype_ `void OnRecordingFinished(UTakeRecorder* InRecorder);` — Callback triggered when a recording is finished - either stopped or canceled.
- L64 _private prototype_ `void ConfigureSequencerViewForRecording(UTakeRecorder* InRecorder);` — Configure the sequencer view for recording for the given recorder.
- L67 _private prototype_ `void RevertSequencerViewForRecording(UTakeRecorder* InRecorder);` — Revert the sequencer view to its pre recording state.
- L73 _private prototype_ `bool TrySetSequencerSimpleView(TSharedRef<ISequencer> InSequencer, bool bInShowSimple);` — Try and set the sequencer simple view state. This will only return true if the view type was changed.
- L76 _private prototype_ `void HandleOnPostEngineInit();` — Function called when the engine has finished initialzing.
- L80 _private member_ `bool bWasSequencerSimpleViewBeforeRecording = false;` — If the sequencer was in simple view when recording started.
- L82 _private member_ `FDelegateHandle LevelEditorLayoutExtensionHandle;`
- L83 _private member_ `FDelegateHandle LevelEditorTabManagerChangedHandle;`
- L84 _private member_ `FDelegateHandle ModulesChangedHandle;`
- L86 _private member_ `TSharedPtr<FSerializedRecorder> SerializedRecorder;`
- L95 _private member_ `TUniquePtr<UE::TakeRecorder::FHitchlessProtectionRootLogic> TimecodeManagement;` — Sets up all sub-systems related to managing timecode in Take Recorder For future maintainers: this could totally live in a separate module / plugin / whatever. There's no technical reason to have this live in TakeRecorder. The reason it's here is that we probably always want hitching to be handled gracefully.
- L97 _private member_ `TUniquePtr<UE::TakeRecorder::FSequencerHitchVisualizer> SequencerHitchVisualizer;`
- L101 _private member_ `TArray<TWeakObjectPtr<>> ExternalObjects;` — Extra class default objects that should appear in the Take Recorder panel.
- L104 _private member_ `TObjectPtr<USequencerSettings> SequencerSettings;` — The settings object registers with the Settings module.
- L107 _private member_ `bool bMenusRegisteredAtModuleStartup = false;` — If the menus were registered at module startup.
- L110 _private member_ `TWeakObjectPtr<UTakeRecorder> WeakActiveRecorder = nullptr;` — Weak pointer to the active Take Recorder.

### `Plugins/VirtualProduction/Takes/Source/TakeRecorderEditor/Private/TakeRecorderStyle.h` (Private)


#### class `FTakeRecorderStyle`  
`class FTakeRecorderStyle : public FSlateStyleSet`  
_L11-24_
- inherits: `FSlateStyleSet`
- desc: Slate style set that defines all the styles for the take recorder UI
- L15 _public member_ `static FName StyleName;`
- L18 _public prototype_ `static FTakeRecorderStyle& Get();` — Access the singleton instance for this style set
- L22 _private prototype_ `FTakeRecorderStyle();`
- L23 _private prototype_ `~FTakeRecorderStyle();`

### `Plugins/VirtualProduction/Takes/Source/TakeRecorderEditor/Private/Timecode/HitchProtectionFrameRateModel.h` (Private)


#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace TakeRecorder` (scope `UE`)
- L13 _namespace_ `namespace HitchProtectionFrameRateModel` (scope `UE::TakeRecorder`)
- L16 _prototype_ `bool ShouldShowFrameRateWarning();` (scope `UE::TakeRecorder::HitchProtectionFrameRateModel`) — @return Whether to show the warning icon.
- L19 _prototype_ `FText GetMismatchedFrameRateWarningTooltipText();` (scope `UE::TakeRecorder::HitchProtectionFrameRateModel`) — @return The tooltip text to show when the user hovers the warning icon.

### `Plugins/VirtualProduction/Takes/Source/TakeRecorderEditor/Private/Timecode/HitchProtectionModel.h` (Private)


#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace TakeRecorder` (scope `UE`)
- L10 _namespace_ `namespace HitchProtectionModel` (scope `UE::TakeRecorder`)
- L13 _prototype_ `bool CanInitializeHitchProtection();` (scope `UE::TakeRecorder::HitchProtectionModel`) — @return Whether hitch protection can be initialized. False if there is an incompatible engine timestep set.
- L16 _prototype_ `FText GetHitchProtectionDisabledReasonText();` (scope `UE::TakeRecorder::HitchProtectionModel`) — @return Returns why hitch protection cannot be initialized

### `Plugins/VirtualProduction/Takes/Source/TakeRecorderEditor/Private/Timecode/HitchlessProtectionRootLogic.h` (Private)


#### class `UE::TakeRecorder::FHitchlessProtectionRootLogic`  
`class FHitchlessProtectionRootLogic : public FNoncopyable`  
_L18-57_
- inherits: `FNoncopyable`
- desc: Sets up all systems related to managing timecode in Take Recorder and dealing with engine hitches, such as timecode correction during recording and visualization of hitches in Sequencer. This is the root object class that handles injecting all dependencies into the subsystems. It acts a mediator between the systems ensuring the correct order of operations during recording & reviewing a take.
- L22 _public prototype_ `FHitchlessProtectionRootLogic();`
- L23 _public prototype_ `~FHitchlessProtectionRootLogic();`
- L33 _private member_ `FTimecodeRegressionRecordSetup TimecodeRegressor;` — Overrides the global FApp's timecode by estimating the timecode the frame has using linear regression. E.g. when a 1s hitch occurs at time 14:11:06:01, then the next frame should be 14:11:06:02 even though the real timecode is 14:11:07:02 meaning that the engine has to catch up. This sets up the relevant systems.
- L45 _private member_ `TOptional<FRecordingState> RecordingState;` — Set while recording.
- L48 _private prototype_ `void SetupTakeRecorderDelegates();` — Starts listening for UTakeRecorder events.
- L50 _private prototype_ `void OnInitializeRecording(UTakeRecorder* TakeRecorder);` — Sets up hitchless recording.
- L52 _private prototype_ `void OnFinishRecording(UTakeRecorder* TakeRecorder);` — Creates timecode tracks requireds for visualization of timecode hitches.
- L54 _private prototype_ `void OnCancelRecording(UTakeRecorder* TakeRecorder);` — Clears any state
- L56 _private prototype_ `void CleanupRecording();`

#### struct `UE::TakeRecorder::FHitchlessProtectionRootLogic::FRecordingState`  
`struct FRecordingState`  
_L35-43_
- L38 _public member_ `FFrameHitchDecorationRecorder TimecodeRecording;` — Records the underlying timecode provider and the one that is estimated by UTimecodeRegressionProvider.
- L40 _public function_ `explicit FRecordingState(TNotNull<UTimecodeRegressionProvider*> InEstimator, TNotNull<UTakeRecorder*> InTakeRecorder) : TimecodeRecording(InEstimator, InTakeRecorder)`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace TakeRecorder` (scope `UE`)

### `Plugins/VirtualProduction/Takes/Source/TakeRecorderEditor/Private/Timecode/Recording/FrameHitchDecorationRecorder.h` (Private)


#### class `UE::TakeRecorder::FFrameHitchDecorationRecorder`  
`class FFrameHitchDecorationRecorder : public FNoncopyable`  
_L22-50_
- inherits: `FNoncopyable`
- desc: Records target and actual per-frame timecode and attached the data as UFrameHitchSceneDecoration to the root UMovieScene. Target timecode: Holds the unestimated timecode of the UTimecodeProvider underlying UTimecodeRegressionProvider. Actual timecode: Holds the timecode of FApp::CurrentFrameTime, which would usually (if the engine is set up) be what UTimecodeRegressionProvider estimates.
- L26 _public prototype_ `explicit FFrameHitchDecorationRecorder(TNotNull<UTimecodeRegressionProvider*> InTimecodeEstimator, TNotNull<UTakeRecorder*> InTakeRecorder);`
- L27 _public prototype_ `~FFrameHitchDecorationRecorder();`
- L32 _private member_ `const TWeakObjectPtr<UTimecodeRegressionProvider> WeakTimecodeEstimator;` — The timecode provider that's doing the estimation of frame times.
- L35 _private member_ `const TWeakObjectPtr<UTakeRecorder> WeakTakeRecorder;` — Take recorder for which we are recording.
- L43 _private member_ `TakesCore::FArrayOfRecordedTimePairs TargetTimecodeValues;` — Passed in to TakeRecorderSourceHelpers::ProcessRecordedTimes to generate the track for original timecode. We make sure this has equal length as UTakeRecorderSources::RecordedTimes. We achieve this by sampling TargetTimecodeValues whenever UTakeRecorderSources::RecordedTimes is sampled which is when UTakeRecorder::OnTickRecording is invoked.
- L46 _private prototype_ `void OnTickRecording(UTakeRecorder* InTakeRecorder, const FQualifiedFrameTime& InCurrentFrameTime);` — Called when InTakeRecorder ticks during recording.
- L49 _private prototype_ `void OnRecordingStopped(UTakeRecorder* TakeRecorder) const;` — Creates the tracks and adds them to UTakeRecorder.

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace TakeRecorder` (scope `UE`)

### `Plugins/VirtualProduction/Takes/Source/TakeRecorderEditor/Private/Timecode/Regression/GuardTimecodeProvider.h` (Private)


#### class `UE::TakeRecorder::FGuardTimecodeProvider`  
`class FGuardTimecodeProvider : public FNoncopyable`  
_L13-35_
- inherits: `FNoncopyable`
- desc: Overrides the engine's timecode provider for the lifetime of the instance.
- L16 _private member_ `TStrongObjectPtr<UTimecodeProvider> RestoreProvider = nullptr;`
- L19 _public function_ `explicit FGuardTimecodeProvider(UTimecodeProvider* Override)`
- L28 _public function_ `~FGuardTimecodeProvider()`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace TakeRecorder` (scope `UE`)

### `Plugins/VirtualProduction/Takes/Source/TakeRecorderEditor/Private/Timecode/Regression/GuardTimestep.h` (Private)


#### class `UE::TakeRecorder::FGuardTimestep`  
`class FGuardTimestep : public FNoncopyable`  
_L13-35_
- inherits: `FNoncopyable`
- desc: Overrides the engine's timestep for the lifetime of the instance.
- L16 _private member_ `TStrongObjectPtr<UEngineCustomTimeStep> RestoreTimestep = nullptr;`
- L19 _public function_ `explicit FGuardTimestep(UEngineCustomTimeStep* Override)`
- L28 _public function_ `~FGuardTimestep()`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace TakeRecorder` (scope `UE`)

### `Plugins/VirtualProduction/Takes/Source/TakeRecorderEditor/Private/Timecode/Regression/TimecodeNotifications.h` (Private)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace TakeRecorder` (scope `UE`)
- L11 _prototype_ `void ShowNoTimecodeProviderNotification();` (scope `UE::TakeRecorder`) — Shows a notification that the user has not set up any timecode provider.
- L14 _prototype_ `void ShowNoTimeStepClassNotification();` (scope `UE::TakeRecorder`) — Shows a notification that the configured time step class could not be resolved.

### `Plugins/VirtualProduction/Takes/Source/TakeRecorderEditor/Private/Timecode/Regression/TimecodeRegressionRecordSetup.h` (Private)


#### struct `UE::TakeRecorder::FTimecodeEstimationSetupResult`  
`struct FTimecodeEstimationSetupResult`  
_L17-24_
- desc: Holds info about when the engine environment has been set up to estimate timecode.
- L20 _public member_ `UTimecodeRegressionProvider* Estimator = nullptr;` — The timecode estimator that was set up.
- L22 _public function_ `bool IsSuccess() const`
- L23 _public function_ `operator bool() const`

#### class `UE::TakeRecorder::FTimecodeRegressionRecordSetup`  
`class FTimecodeRegressionRecordSetup : public FNoncopyable`  
_L30-62_
- inherits: `FNoncopyable`
- desc: Sets up the UEngine::TimecodeProvider so timecode is not skipped when an engine frame takes longer than expected ("hitches"). This is root class is responsible for setting up this for this workflow and acts as a mediator for setting up relevant systems.
- L39 _public prototype_ `FTimecodeEstimationSetupResult SetupEngineEnvironmentForRecording(const FTakeRecorderHitchProtectionParameters& InParams);` — Sets up timecode and optionally the custom time step. @param InParams Settings for setting up recording. @return The real timecode provider that we will be estimating. Unset if initialization failed.
- L42 _public function_ `void CleanupRecording()` — Clears the time step and timecode provider overrides.
- L61 _private member_ `TOptional<FRecordOverrides> RecordData;` — Set while the recording and if the user did not disable this feature.

#### struct `UE::TakeRecorder::FTimecodeRegressionRecordSetup::FRecordOverrides`  
`struct FRecordOverrides`  
_L47-59_
- desc: State to save for the duration of a recording. Cleans up engine state after recording.
- L52 _public member_ `TOptional<FGuardTimestep> TimestepOverride;` — Set if there was no custom timestep and the user chose one in the pop-up dialogue.
- L54 _public member_ `FGuardTimecodeProvider TimecodeOverride;` — Set while the recording and if the user did not disable it.
- L56 _public function_ `FRecordOverrides(UTimecodeProvider* InOverride) : TimecodeOverride(InOverride)`
- L57 _public function_ `FRecordOverrides(UEngineCustomTimeStep* InTimestep, UTimecodeRegressionProvider* InTimecode) : TimestepOverride(InPlace, InTimestep), TimecodeOverride(InTimecode)`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace TakeRecorder` (scope `UE`)

### `Plugins/VirtualProduction/Takes/Source/TakeRecorderEditor/Private/Timecode/Visualization/Drawing/AnalyzedHitchUIDrawingUtils.h` (Private)


#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace TakeRecorder` (scope `UE`)
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace TakeRecorder` (scope `UE`)
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace TakeRecorder` (scope `UE`)
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace TakeRecorder` (scope `UE`)
- L15 _namespace_ `namespace HitchVisualizationUI` (scope `UE::TakeRecorder`)
- L18 _prototype_ `int32 DrawTimeSliderArea( const FTimecodeHitchData& InData, const FAnalyzedHitchUIHoverInfo& InHoverInfo, const FScrubRangeToScreen& InRangeToScreen, const FGeometry& InAllottedGeometry, FSlateWindowElementList& OutDrawElements, int32 InLayerId, EHitchDrawFlags InFlags = EHitchDrawFlags::All );` (scope `UE::TakeRecorder::HitchVisualizationUI`) — Draws the top part (markers, etc.) of InData.
- L25 _prototype_ `int32 DrawTrackArea( const FTimecodeHitchData& InData, const FAnalyzedHitchUIHoverInfo& InHoverInfo, const FScrubRangeToScreen& InRangeToScreen, const FGeometry& InAllottedGeometry, FSlateWindowElementList& OutDrawElements, int32 InLayerId, EHitchDrawFlags InFlags = EHitchDrawFlags::All );` (scope `UE::TakeRecorder::HitchVisualizationUI`) — Draws the bottom part (markers, etc.) of InData.
- L32 _prototype_ `FAnalyzedHitchUIHoverInfo ComputeHoverStateForTimeSliderArea( const FVector2f& InAbsoluteCursorPos, const FTimecodeHitchData& InData, const FScrubRangeToScreen& InRangeToScreen, const FGeometry& InAllottedGeometry, EHitchDrawFlags InFlags = EHitchDrawFlags::All );` (scope `UE::TakeRecorder::HitchVisualizationUI`) — Determines the hovered geometry in the time slider area.

### `Plugins/VirtualProduction/Takes/Source/TakeRecorderEditor/Private/Timecode/Visualization/Drawing/AnalyzedHitchUIHoverInfo.h` (Private)


#### struct `UE::TakeRecorder::FAnalyzedHitchUIHoverInfo`  
`struct FAnalyzedHitchUIHoverInfo`  
_L15-50_
- desc: Information about which hitch visualization geometry is hovered. This is relevant only for when there is hitch analysis data. Only one of the optionals is set at any time.
- L18 _public member_ `TOptional<int32> SkippedMarkerIndex;` — Index to the FTimecodeHitchData::SkippedTimecodeMarkers that should be drawn as set.
- L21 _public member_ `TOptional<int32> RepeatedMarkerIndex;` — Index to the FTimecodeHitchData::RepeatedTimecodeMarkers that should be drawn as set.
- L24 _public member_ `TOptional<int32> CatchupTimeIndex;` — Index to the FTimecodeHitchData::RepeatedTimecodeMarkers that should be drawn as hovered.
- L27 _public function_ `void Reset()` — Resets this info so nothing is hovered.
- L35 _public function_ `bool IsHovered() const` — @return Whether anything is hovered
- L37 _public function_ `operator bool() const` — @return Whether anything is hovered

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace TakeRecorder` (scope `UE`)
- L39 _function_ `friend bool operator==(const FAnalyzedHitchUIHoverInfo& Left, const FAnalyzedHitchUIHoverInfo& Right)` (scope `UE::TakeRecorder`)
- L46 _function_ `friend bool operator!=(const FAnalyzedHitchUIHoverInfo& Left, const FAnalyzedHitchUIHoverInfo& Right)` (scope `UE::TakeRecorder`)

### `Plugins/VirtualProduction/Takes/Source/TakeRecorderEditor/Private/Timecode/Visualization/Drawing/EHitchDrawFlags.h` (Private)


#### enum `UE::TakeRecorder::EHitchDrawFlags`  
`enum class EHitchDrawFlags : uint8`  
_L10-19_
- L12 _public enumerator_ `None = 0`
- L14 _public enumerator_ `DrawSkippedTimecodeMarkers = 1 << 0`
- L15 _public enumerator_ `DrawRepeatedTimecodeMarkers = 1 << 1`
- L16 _public enumerator_ `DrawCatchupRanges = 1 << 2`
- L18 _public enumerator_ `All = DrawSkippedTimecodeMarkers | DrawRepeatedTimecodeMarkers | DrawCatchupRanges`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace TakeRecorder` (scope `UE`)
- L20 _prototype_ `ENUM_CLASS_FLAGS(EHitchDrawFlags);` (scope `UE::TakeRecorder`)

### `Plugins/VirtualProduction/Takes/Source/TakeRecorderEditor/Private/Timecode/Visualization/Drawing/HitchVisualizationStyle.h` (Private)


#### struct `UE::TakeRecorder::FMarkerStyle`  
`struct FMarkerStyle`  
_L10-23_
- L13 _public member_ `FLinearColor NormalTint = FTakeRecorderStyle::Get().GetColor("Hit` — Color that the marker vertical line & warning icon should have when drawn normally.
- L16 _public member_ `FLinearColor HoveredTint = FTakeRecorderStyle::Get().GetColor("Hit` — Color that the marker vertical line & warning icon should have when drawn hovered.
- L19 _public member_ `const FSlateBrush* IconBrush = FTakeRecorderStyle::Get().GetBrush("Hit` — Brush to drawn next to vertical line on marker.
- L22 _public member_ `FVector2f MarkerBrushOffset{ 4.f, 4.f };` — Offset that marker icon should have from its vertical line.

#### struct `UE::TakeRecorder::FCatchupZoneStyle`  
`struct FCatchupZoneStyle`  
_L25-35_
- L28 _public member_ `FLinearColor CatchupZone_Normal = FTakeRecorderStyle::Get().GetColor("Hit` — Color that the catchup zone vertical lines & box brush should have when drawn normally.
- L31 _public member_ `FLinearColor CatchupZone_Hovered = FTakeRecorderStyle::Get().GetColor("Hit` — Color that the catchup zone vertical lines & box brush should have when drawn hovered.
- L34 _public member_ `const FSlateBrush* CatchupZoneBrush = FTakeRecorderStyle::Get().GetBrush("Hit` — Brush to drawn between left and right vertical line in catchup zone.

#### struct `UE::TakeRecorder::FHitchVisualizationStyle`  
`struct FHitchVisualizationStyle`  
_L37-52_
- L40 _public member_ `FMarkerStyle SkipMarkerStyle;` — How to draw markers for when the engine skipped timecode on a frame.
- L43 _public member_ `FMarkerStyle RepeatMarkerStyle { FTakeRecorderStyle::Get().GetColor("Hitching.SkipMarker.Normal"), FTakeRecorderStyle::Get().GetColor("Hitching.SkipMarker.Hovered"), FTakeRecorderStyle::Get().GetBrush("Hitching.SkipMarker.Icon") };` — How to draw markers for when the engine repeated timecode.
- L51 _public member_ `FCatchupZoneStyle CatchupZoneStyle;` — How to draw the catchup zone, i.e. an area in which the engine was trailing target timecode.

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace TakeRecorder` (scope `UE`)

### `Plugins/VirtualProduction/Takes/Source/TakeRecorderEditor/Private/Timecode/Visualization/Drawing/MismatchedFrameRateDrawingUtils.h` (Private)


#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace TakeRecorder` (scope `UE`)
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace TakeRecorder` (scope `UE`)
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace TakeRecorder` (scope `UE`)
- L14 _namespace_ `namespace MismatchedFrameRateUI` (scope `UE::TakeRecorder`)
- L17 _prototype_ `int32 DrawWarningIcon( const ISequencer& InSequencer, const FMismatchedFrameRateUIHoverInfo& InHoverInfo, const FScrubRangeToScreen& InRangeToScreen, const FGeometry& InAllottedGeometry, FSlateWindowElementList& OutDrawElements, int32 InLayerId );` (scope `UE::TakeRecorder::MismatchedFrameRateUI`) — Draws the icon for warning the user about mismatched frame rates.
- L23 _prototype_ `FMismatchedFrameRateUIHoverInfo ComputeHoverStateForTimeSliderArea( const ISequencer& InSequencer, const FVector2f& InAbsoluteCursorPos, const FScrubRangeToScreen& InRangeToScreen, const FGeometry& InAllottedGeometry );` (scope `UE::TakeRecorder::MismatchedFrameRateUI`) — Determines the hovered geometry in the time slider area.

### `Plugins/VirtualProduction/Takes/Source/TakeRecorderEditor/Private/Timecode/Visualization/Drawing/MismatchedFrameRateUIHoverInfo.h` (Private)


#### struct `UE::TakeRecorder::FMismatchedFrameRateUIHoverInfo`  
`struct FMismatchedFrameRateUIHoverInfo`  
_L11-26_
- desc: This is hover information about the UI that is displayed when no analysis was performed due to mismatched frames.
- L14 _public member_ `bool bIsWarningMarkerHovered = false;` — Whether the warning marker which tells the user that analysis was skipped is hovered.
- L17 _public function_ `void Reset()` — Resets this info so nothing is hovered.
- L23 _public function_ `bool IsHovered() const` — @return Whether anything is hovered
- L25 _public function_ `operator bool() const` — @return Whether anything is hovered

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace TakeRecorder` (scope `UE`)

### `Plugins/VirtualProduction/Takes/Source/TakeRecorderEditor/Private/Timecode/Visualization/Drawing/ScrubRangeToScreen.h` (Private)


#### struct `UE::TakeRecorder::FScrubRangeToScreen`  
`struct FScrubRangeToScreen : FSequencerTimeSliderController::FScrubRangeToScreen`  
_L12-33_
- inherits: `FSequencerTimeSliderController::FScrubRangeToScreen`
- desc: Helps convert FFrameTime to coordinates in widget space for finding the X-coordinate of vertical lines in Sequencer.
- L14 _public member_ `const FFrameRate FrameRate;`
- L16 _public function_ `explicit FScrubRangeToScreen(const FFrameRate& InFrameRate, const TRange<double>& InViewInput, const FVector2D& InWidgetSize) : FSequencerTimeSliderController::FScrubRangeToScreen(InViewInput, InWidgetSize) , FrameRate(InFrameRate)`
- L22 _public function_ `float FrameToLocalX(const FFrameTime& InFrameTime) const` — FrameTime -> local Widget Space
- L28 _public function_ `float FrameToLocalX(const FFrameNumber& InFrameNumber) const` — FrameTime -> local Widget Space

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace TakeRecorder` (scope `UE`)

### `Plugins/VirtualProduction/Takes/Source/TakeRecorderEditor/Private/Timecode/Visualization/HitchAnalysis.h` (Private)


#### struct `UE::TakeRecorder::FCatchupTimeRange`  
`struct FCatchupTimeRange`  
_L14-34_
- desc: A section of time where the engine fell behind and tried to catchup.
- L17 _public member_ `FFrameNumber StartTime;` — The first frame at which the timecode started being behind
- L19 _public member_ `FFrameNumber EndTime;` — The last frame at which the timecode was still behind
- L27 _public member_ `TOptional<FFrameNumber> FirstOkFrame;` — The frame at which the timecode has caught up again. That's the frame immediately after EndTime. Unset if the recording ended with a frame at which timecode was behind.
- L29 _public function_ `explicit FCatchupTimeRange(const FFrameNumber& InStartTime, const FFrameNumber& InEndTime, const TOptional<FFrameNumber>& InFirstOkFrame = {}) : StartTime(InStartTime) , EndTime(InEndTime) , FirstOkFrame(InFirstOkFrame)`

#### struct `UE::TakeRecorder::FUnexpectedTimecodeMarker`  
`struct FUnexpectedTimecodeMarker`  
_L37-52_
- desc: Data about a frame at which timecode was skipped
- L40 _public member_ `FFrameNumber Frame;` — The frame at which the timecode did not match.
- L43 _public member_ `FTimecode ActualTimecode;` — The actual timecode the frame had.
- L45 _public member_ `FTimecode ExpectedFrame;` — The timecode that was expected at this frame.
- L47 _public function_ `explicit FUnexpectedTimecodeMarker(const FFrameNumber& InFrame, const FTimecode& InActualTimecode, const FTimecode& InExpectedFrame) : Frame(InFrame) , ActualTimecode(InActualTimecode) , ExpectedFrame(InExpectedFrame)`

#### struct `UE::TakeRecorder::FTimecodeHitchData`  
`struct FTimecodeHitchData`  
_L55-71_
- desc: All data required to draw
- L58 _public member_ `TArray<FUnexpectedTimecodeMarker> SkippedTimecodeMarkers;` — Frames at which the timecode was skipped (previous frame was not current frame - 1).
- L61 _public member_ `TArray<FUnexpectedTimecodeMarker> RepeatedTimecodeMarkers;` — Frames at which timecode was repeated (previous frame had the same timecode).
- L64 _public member_ `TArray<FCatchupTimeRange> CatchupTimes;` — Sections at which the engine fell behind timecode.
- L66 _public function_ `void Reset()`

#### enum `UE::TakeRecorder::EHitchAnalysisError`  
`enum class EHitchAnalysisError : uint8`  
_L73-92_
- L76 _public enumerator_ `NoData` — There was no UFrameHitchSceneDecoration attached, so we skipped analysis.
- L89 _public enumerator_ `FrameRateMismatch` — Take Recorder's record frame rate did not match the frame rate of underlying timecode provider. For now, analysis is only supported when the frame rates are equal. It's technically possible to implement but we just didn't implement it, yet. To implement, we need to change the timecode that is expected each frame. For example, if the timecode provider is 48 FPS and TR 24 FPS, example frames we may expect would be - frame 1 -> 17:42:42:05, - frame 2 -> 17:42:42:07, - frame 3 -> 17:42:42:09, etc.
- L91 _public enumerator_ `Num`

#### struct `UE::TakeRecorder::FFrameRateMismatchData`  
`struct FFrameRateMismatchData`  
_L94-100_
- L97 _public member_ `FFrameRate TakeRecorderRate;` — Frame rate that TR recorded at.
- L99 _public member_ `FFrameRate TimecodeRate;` — Frame rate that the timecode provider had during recording.

#### struct `UE::TakeRecorder::FHitchAnalysisErrorInfo`  
`struct FHitchAnalysisErrorInfo`  
_L102-109_
- L105 _public member_ `EHitchAnalysisError Reason;` — The reason why analysis failed.
- L108 _public member_ `TOptional<FFrameRateMismatchData> MismatchInfo;` — Set if Reason == FrameRateMismatch.

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace TakeRecorder` (scope `UE`)
- L115 _prototype_ `TValueOrError<FTimecodeHitchData, FHitchAnalysisErrorInfo> AnalyseHitches(ISequencer& InSequencer);` (scope `UE::TakeRecorder`) — Tries to find the required tracks for analysing hitches, and then analyses them. @return Analyzed hitch data if required tracks were found.
- L118 _prototype_ `bool HasHitchData(ISequencer& InSequencer);` (scope `UE::TakeRecorder`) — @return Whether there is any hitch data that can be analyzed.

### `Plugins/VirtualProduction/Takes/Source/TakeRecorderEditor/Private/Timecode/Visualization/HitchViewOptionUtils.h` (Private)


#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace TakeRecorder` (scope `UE`)
- L22 _prototype_ `void ExtendSequencerViewOptionsWithHitchVisualization();` (scope `UE::TakeRecorder`) — Extends Sequencer view options adding: - Show Frame Drop Markers - Show Catchup Ranges - Clear Recording Integrity Markers and Ranges
- L28 _prototype_ `void ExtendSequencerTimeSliderContextMenu();` (scope `UE::TakeRecorder`) — Extends the top-time slider context menu with: - Clear Recording Integrity Markers and Ranges
- L31 _prototype_ `void Execute_ClearRecordingIntegrityData(TWeakPtr<ISequencer> InSequencer);` (scope `UE::TakeRecorder`) — Handles the FTakeRecorderCommands::Get().ClearRecordingIntegrityData.
- L33 _prototype_ `bool CanExecute_ClearRecordingIntegrityData(TWeakPtr<ISequencer> InSequencer);` (scope `UE::TakeRecorder`) — Whether FTakeRecorderCommands::Get().ClearRecordingIntegrityData can be executed, i.e. movie scene is not read-only.

### `Plugins/VirtualProduction/Takes/Source/TakeRecorderEditor/Private/Timecode/Visualization/Sequencer/HitchTooltipShower.h` (Private)


#### class `UE::TakeRecorder::THitchTooltipShower`  
`template<typename THoverState> class THitchTooltipShower : public FNoncopyable`  
_L23-94_
- inherits: `FNoncopyable`
- desc: Responsible for showing and hiding a tooltip based on the currently hovered visualization UI.
- L28 _public function_ `bool CanShowTooltips() const` — @return Whether tooltips are allowed to be shown currently.
- L35 _public function_ `void UpdateTooltipState(const THoverState& InHoverInfo, const TAttribute<FText>& InTooltipText)` — Shows a visualization tooltip if currently hovering
- L48 _public function_ `void ClearTooltip()` — Ensures the tooltip is hidden.
- L83 _private member_ `TOptional<FTooltipState> TooltipState;` — Active tooltip override. Cleans up the tooltip on destruction.
- L86 _private function_ `void RecreateIfContentChanged(const THoverState& InHoverInfo, const TAttribute<FText>& InTooltipText)` — (Re-)creates the tooltip if the hover a UI element is hovered. If the hovered UI has changed since last time, the tooltip is recreated.

#### struct `UE::TakeRecorder::THitchTooltipShower::FTooltipState`  
`struct FTooltipState`  
_L55-80_
- L58 _public member_ `const THoverState HoverInfo;` — The hovered UI elements when the tooltip was overriden.
- L61 _public member_ `const TSharedPtr<IToolTip> OurTooltip;` — The hitch visualization tooltip we've temporarily spawned.
- L63 _public function_ `explicit FTooltipState(const THoverState& InHoverInfo, const TAttribute<FText>& InTooltipText) : HoverInfo(InHoverInfo) , OurTooltip(SNew(SToolTip) .Text(InTooltipText) .IsInteractive(true)`
- L68 _public function_ `.OnSetInteractiveWindowLocation_Lambda([](FVector2D& OutPosition){ OutPosition = FSlateApplication::Get().GetCursorPos(); }) )`
- L75 _public function_ `~FTooltipState()`

#### Free symbols / members of external scopes

- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace TakeRecorder` (scope `UE`)

### `Plugins/VirtualProduction/Takes/Source/TakeRecorderEditor/Private/Timecode/Visualization/Sequencer/HitchViewModel_AnalyzedData.h` (Private)


#### class `UE::TakeRecorder::FHitchViewModel_AnalyzedData`  
`class FHitchViewModel_AnalyzedData : public Sequencer::FViewModel , public Sequencer::ITopTimeSliderOverlayExtension , public Sequencer::ITrackAreaOverlayExtension`  
_L30-87_
- inherits: `Sequencer::FViewModel,Sequencer::ITopTimeSliderOverlayExtension,Sequencer::ITrackAreaOverlayExtension`
- desc: Draws analyzed hitch data: - Timecode skip & repeats draw a vertical line and a warning icon (in red ), - Catch up zones, when the engine was behind the target timecode (in yellow), - Draws a tooltip when UI in the timeslider section is hovered. The content is also drawn brighter. @see TooltipShowerHack. This is set up by FSequencerHitchVisualizer. @see FSequencerHitchVisualizer
- L37 _public prototype_ `UE_SEQUENCER_DECLARE_CASTABLE(FHitchViewModel_AnalyzedData, ITopTimeSliderOverlayExtension, ITrackAreaOverlayExtension);`
- L39 _public function_ `explicit FHitchViewModel_AnalyzedData( TWeakPtr<ISequencer> InWeakOwningSequencer, FTimecodeHitchData InHitchData, TAttribute<bool> InCanPaintAttr = true ) : WeakOwningSequencer(MoveTemp(InWeakOwningSequencer)) , CanPaintAttr(MoveTemp(InCanPaintAttr)) , ViewModelData(MoveTemp(InHitchData))`
- L48 _public prototype_ `virtual int32 OnPaintTimeSliderOverlay(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle) override;`
- L52 _public prototype_ `virtual int32 OnPaintTrackAreaOverlay(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle) override;`
- L58 _private member_ `const TWeakPtr<ISequencer> WeakOwningSequencer;` — The sequencer that this model is saved in.
- L61 _private member_ `const TAttribute<bool> CanPaintAttr;` — Decides whether we can paint.
- L64 _private member_ `const FTimecodeHitchData ViewModelData;` — The hitch data that is being visualized.
- L66 _private member_ `FAnalyzedHitchUIHoverInfo TimeSliderHoverInfo;` — In time slider area, info about which of HitchData should be drawn has hovered. Also used for determining what tooltip to show.
- L77 _private member_ `THitchTooltipShower<FAnalyzedHitchUIHoverInfo> TooltipShowerHack;` — Handles showing and hiding the tooltip for our hitch visualization UI. This is a "hack" because we should prefer be using Sequencer's hotspot API: ideally, we'd tell the hotspot API what the user is currently focusing. Then, the API would ask what the tooltip should be and handle showing it. However, the API is limited: - the hotspot API is limited to track areas but we need it for the time slider area as well, and - the hotspot API provides not way to show tooltips for now. Once the hotspot API supports those operations, this hack should be replaced.
- L80 _private prototype_ `void UpdateHoverState_TimeSlider(const FPaintArgs& InArgs, const FGeometry& InAllottedGeometry, EHitchDrawFlags InFlags);` — Updates TimeSliderHoverInfo and the resulting tooltip state.
- L83 _private prototype_ `FScrubRangeToScreen MakeScrubRangeToScreen(const FGeometry& AllottedGeometry) const;` — @return Utility for converting FFrameTime to widget paint positions.
- L86 _private function_ `bool CanPaint() const` — @return Whether this model should paint itself.

#### Free symbols / members of external scopes

- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace TakeRecorder` (scope `UE`)

### `Plugins/VirtualProduction/Takes/Source/TakeRecorderEditor/Private/Timecode/Visualization/Sequencer/HitchViewModel_MismatchedFrameRate.h` (Private)


#### class `UE::TakeRecorder::FHitchViewModel_MismatchedFrameRate`  
`class FHitchViewModel_MismatchedFrameRate : public Sequencer::FViewModel , public Sequencer::ITopTimeSliderOverlayExtension`  
_L27-79_
- inherits: `Sequencer::FViewModel,Sequencer::ITopTimeSliderOverlayExtension`
- desc: Draws a warning icon in the time slider area. The warning tells the user that hitch analysis did not take place because the frame rate that Take Recorder recorded at was different from that frame rate that the underlying timecode provider sampled at.
- L33 _public prototype_ `UE_SEQUENCER_DECLARE_CASTABLE(FHitchViewModel_MismatchedFrameRate, ITopTimeSliderOverlayExtension);`
- L35 _public function_ `explicit FHitchViewModel_MismatchedFrameRate( TWeakPtr<ISequencer> InWeakOwningSequencer, FFrameRateMismatchData InHitchData, TAttribute<bool> InCanPaintAttr = true ) : WeakOwningSequencer(MoveTemp(InWeakOwningSequencer)) , CanPaintAttr(MoveTemp(InCanPaintAttr)) , ViewModelData(MoveTemp(InHitchData))`
- L44 _public prototype_ `virtual int32 OnPaintTimeSliderOverlay(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle) override;`
- L50 _private member_ `const TWeakPtr<ISequencer> WeakOwningSequencer;` — The sequencer that this model is saved in.
- L53 _private member_ `const TAttribute<bool> CanPaintAttr;` — Decides whether we can paint.
- L56 _private member_ `const FFrameRateMismatchData ViewModelData;` — The hitch data that is being visualized.
- L58 _private member_ `FMismatchedFrameRateUIHoverInfo TimeSliderHoverInfo;` — In time slider area, info about which of HitchData should be drawn has hovered. Also used for determining what tooltip to show.
- L69 _private member_ `THitchTooltipShower<FMismatchedFrameRateUIHoverInfo> TooltipShowerHack;` — Handles showing and hiding the tooltip for our hitch visualization UI. This is a "hack" because we should prefer be using Sequencer's hotspot API: ideally, we'd tell the hotspot API what the user is currently focusing. Then, the API would ask what the tooltip should be and handle showing it. However, the API is limited: - the hotspot API is limited to track areas but we need it for the time slider area as well, and - the hotspot API provides not way to show tooltips for now. Once the hotspot API supports those operations, this hack should be replaced.
- L72 _private prototype_ `void UpdateHoverState_TimeSlider(const FPaintArgs& InArgs, const FGeometry& InAllottedGeometry, EHitchDrawFlags InFlags);` — Updates TimeSliderHoverInfo and the resulting tooltip state.
- L75 _private prototype_ `FScrubRangeToScreen MakeScrubRangeToScreen(const FGeometry& AllottedGeometry) const;` — @return Utility for converting FFrameTime to widget paint positions.
- L78 _private function_ `bool CanPaint() const` — @return Whether this model should paint itself.

#### Free symbols / members of external scopes

- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace TakeRecorder` (scope `UE`)

### `Plugins/VirtualProduction/Takes/Source/TakeRecorderEditor/Private/Timecode/Visualization/Sequencer/SequencerHitchVisualizer.h` (Private)


#### class `UE::TakeRecorder::FSequencerHitchVisualizer`  
`class FSequencerHitchVisualizer : public FNoncopyable`  
_L18-38_
- inherits: `FNoncopyable`
- desc: Hooks into Sequencer and extends the UI to visualize hitches.
- L22 _public prototype_ `FSequencerHitchVisualizer();`
- L23 _public prototype_ `~FSequencerHitchVisualizer();`
- L28 _private member_ `FDelegateHandle OnSequencerCreatedHandle;` — Handles for OnSequencerCreated.
- L31 _private member_ `const TSharedPtr<FExtender> ViewOptionsExtender;` — Extends Sequencer's view options
- L34 _private member_ `TArray<TWeakPtr<ISequencer>> CustomizedSequencers;` — The sequencers we have customized thus far.
- L37 _private prototype_ `void OnSequencerCreated(TSharedRef<ISequencer> InSequencer);` — Invoked when a sequencer is created: extends the UI with visualization UI, if needed.

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace TakeRecorder` (scope `UE`)

### `Plugins/VirtualProduction/Takes/Source/TakeRecorderEditor/Private/Timecode/Visualization/TakeRecorderHitchVisualizationSettings.h` (Private)


#### class `UTakeRecorderHitchVisualizationSettings`  
`class UTakeRecorderHitchVisualizationSettings : public UObject`  
_L11-50_
- reflection: `UCLASS(Config = EditorSettings)`
- inherits: `UObject`
- L16 _public function_ `static UTakeRecorderHitchVisualizationSettings* Get()`
- L21 _public prototype_ `bool GetShowFrameDropMarkers() const;`
- L22 _public prototype_ `void ToggleShowFrameDropMarkers();`
- L24 _public prototype_ `bool GetShowFrameRepeatMarkers() const;`
- L25 _public prototype_ `void ToggleShowFrameRepeatMarkers();`
- L27 _public prototype_ `bool GetShowCatchupRanges() const;`
- L28 _public prototype_ `void ToggleShowCatchupRanges();`
- L30 _public prototype_ `UE::TakeRecorder::EHitchDrawFlags GetFlagsForUI() const;`
- L32 _public prototype_ `virtual void PostInitProperties() override;`
- L34 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L41 _private member_ `bool bShowFrameDropMarkers = true;` — `UPROPERTY(Config)` — Whether to place markers on frames where a timecode frame was skipped.
- L45 _private member_ `bool bShowFrameRepeatMarkers = true;` — `UPROPERTY(Config)` — Whether to place markers on frames where a timecode frame was repeated.
- L49 _private member_ `bool bShowCatchupRanges = false;` — `UPROPERTY(Config)` — Whether to show areas in which the engine could not keep up, i.e. was running behind.

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace TakeRecorder` (scope `UE`)

### `Plugins/VirtualProduction/Takes/Source/TakeRecorderEditor/Private/Widgets/SLevelSequenceTakeEditor.h` (Private)


#### class `SLevelSequenceTakeEditor`  
`class SLevelSequenceTakeEditor : public SCompoundWidget`  
_L26-124_
- inherits: `SCompoundWidget`
- desc: Widget used by both the take preset asset editor, and take recorder panel that allows editing the take information for an externally provided level sequence
- L29 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnDetailsPropertiesChanged, const FPropertyChangedEvent&);`
- L30 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnDetailsViewAdded, const TWeakPtr<IDetailsView>&);`
- L32 _public function_ `SLATE_BEGIN_ARGS(SLevelSequenceTakeEditor) : _LevelSequence(nullptr)`
- L36 _public prototype_ `SLATE_ATTRIBUTE(ULevelSequence*, LevelSequence) SLATE_EVENT(FOnDetailsPropertiesChanged, OnDetailsPropertiesChanged) SLATE_EVENT(FOnDetailsViewAdded, OnDetailsViewAdded) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L47 _public prototype_ `TSharedRef<SWidget> MakeAddSourceButton();` — Construct a button that can add sources to this widget's preset
- L52 _public prototype_ `void AddExternalSettingsObject(UObject* InObject);` — Add a new externally controlled settings object to the details UI on this widget
- L58 _public prototype_ `bool RemoveExternalSettingsObject(UObject* InObject);` — Removes an externally controlled settings object from the details UI on this widget @return True if it was removed, false otherwise
- L62 _private prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L69 _private prototype_ `void CheckForNewLevelSequence();` — Check to see whether the level sequence ptr has changed, and propagate that change if necessary
- L75 _private prototype_ `void InitializeAudioSettings();` — Initialize the audio settings object so that microphone sources can build their input channel menus based on the current audio device
- L77 _private prototype_ `void AddDetails(const TPair<const UClass*, TArray<UObject*> >& Pair, TArray<FObjectKey>& PreviousClasses);`
- L82 _private prototype_ `void UpdateDetails();` — Update the details panel for the current selection
- L86 _private prototype_ `TSharedRef<SWidget> OnGenerateSourcesMenu();`
- L88 _private prototype_ `void AddSourceFromClass(TSubclassOf<UTakeRecorderSource> SourceClass);`
- L89 _private prototype_ `bool CanAddSourceFromClass(TSubclassOf<UTakeRecorderSource> SourceClass);`
- L91 _private prototype_ `void OnSourcesSelectionChanged(TSharedPtr<ITakeRecorderSourceTreeItem>, ESelectInfo::Type);`
- L95 _private prototype_ `void OnSearchTextChanged(const FText& InFilterText);` — When the search text changes, propagate to all details views.
- L96 _private prototype_ `void OnSearchTextCommitted(const FText& InFilterText, ETextCommit::Type CommitType);`
- L101 _private prototype_ `void OnDetailsPropertiesChanged(const FPropertyChangedEvent& InEvent);` — When a details box has a property changed.
- L104 _private prototype_ `bool PromptUserForTargetRecordClassChange(const UClass* NewClass) const;` — Asks the user whether they want to really change UTakePresetSettings::TargetRecordClass.
- L108 _private member_ `bool bRequestDetailsRefresh;`
- L109 _private member_ `TAttribute<ULevelSequence*> LevelSequenceAttribute;`
- L110 _private member_ `TWeakObjectPtr<ULevelSequence> CachedLevelSequence;`
- L112 _private member_ `TSharedPtr<STakeRecorderSources> SourcesWidget;`
- L113 _private member_ `TSharedPtr<SSearchBox> SearchBox;`
- L114 _private member_ `TSharedPtr<SScrollBox> DetailsBox;`
- L115 _private member_ `FText CurrentSearchText;`
- L116 _private member_ `TMap<FObjectKey, TSharedPtr<IDetailsView>> ClassToDetailsView;`
- L118 _private member_ `TArray<TWeakObjectPtr<>> ExternalSettingsObjects;`
- L121 _private member_ `FOnDetailsPropertiesChanged OnDetailsPropertiesChangedEvent;` — Called when properties in the details panel have changed.
- L123 _private member_ `FOnDetailsViewAdded OnDetailsViewAddedEvent;` — Called when a details view has been added.

#### Free symbols / members of external scopes

- L29 _delegate_ `DECLARE_DELEGATE_OneParam(FOnDetailsPropertiesChanged, const FPropertyChangedEvent&);`
- L30 _delegate_ `DECLARE_DELEGATE_OneParam(FOnDetailsViewAdded, const TWeakPtr<IDetailsView>&);`

### `Plugins/VirtualProduction/Takes/Source/TakeRecorderEditor/Private/Widgets/STakePresetAssetEditor.h` (Private)


#### class `STakePresetAssetEditor`  
`class STakePresetAssetEditor : public SCompoundWidget`  
_L17-48_
- inherits: `SCompoundWidget`
- desc: Outermost widget used for editing UTakePreset assets
- L21 _public function_ `SLATE_BEGIN_ARGS(STakePresetAssetEditor)`
- L24 _public prototype_ `~STakePresetAssetEditor();`
- L29 _public prototype_ `void Construct(const FArguments& InArgs, TSharedPtr<FTakePresetToolkit> InToolkit, TWeakPtr<STakeRecorderTabContent> OuterTabContent);` — Construct the widget from the asset's toolkit and the owning tab content
- L31 _public prototype_ `ULevelSequence* GetLevelSequence() const;`
- L35 _private prototype_ `FReply OnSavePreset();`
- L36 _private prototype_ `FReply NewRecordingFromThis();`
- L41 _private member_ `TWeakPtr<STakeRecorderTabContent> WeakTabContent;` — Weak-ptr back to the owning tab content so we can switch out the content for a take recorder panel if necessary
- L44 _private member_ `TSharedPtr<FTakePresetToolkit> Toolkit;` — The asset toolkit for the editing preset asset. This widget keeps the editor alive so that it can be invoked by the asset editor manager if necessary.
- L47 _private member_ `TSharedPtr<FScopedSequencerPanel> SequencerPanel;` — Scoped panel that handles opening and closing the sequencer pane for this preset

### `Plugins/VirtualProduction/Takes/Source/TakeRecorderEditor/Private/Widgets/STakeRecorderCockpit.h` (Private)


#### class `STakeRecorderCockpit`  
`class STakeRecorderCockpit : public SCompoundWidget`  
_L31-227_
- inherits: `SCompoundWidget`
- desc: Cockpit UI for defining take meta-data. Interacts with UTakeMetaData stored on the level sequence, if present, otherwise uses its own transient meta-data
- L35 _public function_ `SLATE_BEGIN_ARGS(STakeRecorderCockpit)`
- L39 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L43 _public prototype_ `~STakeRecorderCockpit();`
- L45 _public prototype_ `UTakeMetaData* GetMetaData() const;`
- L46 _public prototype_ `UTakeMetaData* GetMetaDataChecked() const;`
- L48 _public prototype_ `FFrameRate GetFrameRate() const;`
- L50 _public prototype_ `void SetFrameRate(FFrameRate InFrameRate, bool bFromTimecode);`
- L52 _public prototype_ `bool IsSameFrameRate(FFrameRate InFrameRate) const;`
- L54 _public prototype_ `bool Reviewing() const;`
- L56 _public prototype_ `bool Recording() const;`
- L58 _public prototype_ `TSharedRef<SWidget> MakeLockButton();`
- L60 _public prototype_ `bool CanStartRecording(FText& OutErrorText) const;`
- L62 _public prototype_ `void StartRecording();`
- L64 _public prototype_ `void StopRecording();`
- L66 _public prototype_ `void CancelRecording();`
- L68 _public prototype_ `void Refresh();`
- L71 _public prototype_ `void NotifyPropertyUpdated(const FPropertyChangedEvent& InPropertyChangedEvent);` — Externally called when a property has been updated.
- L73 _public prototype_ `void NotifyDetailsViewAdded(const TWeakPtr<IDetailsView>& InDetailsView);` — Externally called when a details view has been added related to this take recorder.
- L76 _private prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L78 _private prototype_ `void PostUndoRedo();`
- L83 _private prototype_ `TSharedRef<SWidget> MakeHitchProtectionMismatchedFrameRateWarningIcon();` — @return When Hitch Protection is enabled, the widget that warns the user when recorded at FPS mismatches the timecode provider's FPS
- L85 _private prototype_ `EVisibility GetTakeWarningVisibility() const;`
- L86 _private prototype_ `FText GetTakeWarningText() const;`
- L88 _private prototype_ `EVisibility GetRecordErrorVisibility() const;`
- L89 _private prototype_ `FText GetRecordErrorText() const;`
- L91 _private prototype_ `void UpdateRecordError();`
- L92 _private prototype_ `void UpdateTakeError();`
- L94 _private prototype_ `EVisibility GetCountdownVisibility() const;`
- L95 _private prototype_ `FText GetCountdownText() const;`
- L97 _private prototype_ `TSharedRef<SWidget> OnRecordingOptionsMenu();`
- L99 _private prototype_ `FText GetTimecodeText() const;`
- L101 _private prototype_ `FText GetUserDescriptionText() const;`
- L102 _private prototype_ `void SetUserDescriptionText(const FText& InNewText, ETextCommit::Type);`
- L104 _private prototype_ `FText GetFrameRateText() const;`
- L105 _private prototype_ `FText GetFrameRateTooltipText() const;`
- L106 _private prototype_ `bool IsFrameRateCompatible(FFrameRate InFrameRate) const;`
- L107 _private prototype_ `bool IsSetFromTimecode() const;`
- L109 _private prototype_ `FText GetSlateText() const;`
- L110 _private prototype_ `void SetSlateText(const FText& InNewText, ETextCommit::Type InCommitType);`
- L112 _private prototype_ `FText GetTimestampText() const;`
- L113 _private prototype_ `FText GetTimestampTooltipText() const;`
- L116 _private prototype_ `FText GetEvaluatedTakeSaveDirText() const;` — Fully evaluated text of the take save dir.
- L118 _private prototype_ `int32 GetTakeNumber() const;`
- L120 _private prototype_ `FReply OnSetNextTakeNumber();`
- L122 _private prototype_ `void OnBeginSetTakeNumber();`
- L124 _private prototype_ `void SetTakeNumber(int32 InNewTakeNumber);`
- L126 _private prototype_ `void SetTakeNumber_FromCommit(int32 InNewTakeNumber, ETextCommit::Type InCommitType);`
- L128 _private prototype_ `void OnEndSetTakeNumber(int32 InFinalValue);`
- L130 _private prototype_ `float GetEngineTimeDilation() const;`
- L132 _private prototype_ `void SetEngineTimeDilation(float InEngineTimeDilation);`
- L134 _private prototype_ `FReply OnAddMarkedFrame();`
- L136 _private prototype_ `void OnToggleRecording(ECheckBoxState);`
- L138 _private prototype_ `FReply NewRecordingFromThis();`
- L140 _private prototype_ `ECheckBoxState IsRecording() const;`
- L142 _private prototype_ `bool CanRecord() const;`
- L144 _private prototype_ `bool IsLocked() const;`
- L146 _private prototype_ `bool EditingMetaData() const;`
- L148 _private prototype_ `void BindCommands();`
- L150 _private prototype_ `void OnToggleEditPreviousRecording(ECheckBoxState CheckState);`
- L152 _private prototype_ `TSharedRef<SWidget> OnCreateMenu();`
- L155 _private prototype_ `UTakeRecorderNamingTokensData* GetNamingTokensData() const;` — Retrieve data relating to naming tokens.
- L158 _private prototype_ `FText GetCustomTokenTextValue(FString InTokenKey) const;` — Find a user defined text value for our custom tokens.
- L160 _private prototype_ `void SetCustomTokenTextValue(const FText& InNewText, ETextCommit::Type InCommitType, FString InTokenKey);` — Set a user defined text value for a custom token.
- L163 _private prototype_ `void OnTokenValueUpdated();` — When a token value has been updated by the user, such as for slate, take, or custom tokens.
- L166 _private prototype_ `void EvaluateTakeSaveDirTokens();` — Evaluate the take dir tokens for our example display.
- L169 _private prototype_ `void RefreshUndefinedTokens();` — Iterate all cached details views refreshing all undefined tokens.
- L172 _private prototype_ `void UpdateUndefinedTokensFromDetailsView(const TWeakPtr<IDetailsView>& InDetailsView);` — Process all properties in the details view.
- L175 _private prototype_ `void UpdateUndefinedTokensFromTemporaryDetailsView();` — Create and use temporary details view for key data for the case where no details views are available.
- L183 _private prototype_ `void EvaluateTokensFromProperty(const FProperty* InProperty, const void* InContainer, bool bForce = false);` — Evaluate naming tokens given a property. @param InProperty The property we need the value from. @param InContainer Container of the property which holds the value. @param bForce Whether to force an evaluation even if the property isn't flagged as a NamingToken. Property still must be a supported type.
- L186 _private prototype_ `void CreateUserTokensUI();` — Configure any user tokens in the UI.
- L191 _private member_ `int32 TransactionIndex;` — The index of a pending transaction initiated by this widget, or INDEX_NONE if none is pending
- L194 _private member_ `FText RecordErrorText;` — Text that describes why the user cannot record with the current settings
- L197 _private member_ `FText TakeErrorText;` — Text that describes why the user cannot record with the current settings
- L199 _private member_ `TSharedPtr<FDigitsTypeInterface> DigitsTypeInterface;`
- L202 _private member_ `TArray<TWeakPtr<IDetailsView>> DetailViews;` — All known detail views.
- L205 _private member_ `TArray<TSharedPtr<IDetailsView>> TemporaryDetailsViews;` — Details views we manage so we know what tokens are available in case the user has hidden the normal details.
- L208 _private member_ `bool bRefreshUndefinedTokens = false;` — Signal that undefined tokens should be refreshed on the next tick.
- L211 _private member_ `TSharedPtr<SHorizontalBox> UserTokensBox;` — Tokens added by the user
- L214 _private member_ `int32 CachedTakeNumber;` — Cached take numbers and slate used to UpdateTakeError() only when necessary
- L215 _private member_ `FString CachedTakeSlate;`
- L218 _private member_ `TWeakFieldPtr<const FProperty> CachedTakeSaveDirProperty;` — Our cached Take Save Dir Property.
- L220 _private member_ `const void* CachedTakeSaveDirContainer = nullptr;` — Our cached object container, holding our Take Save Dir property value.
- L223 _private member_ `TWeakObjectPtr<UTakeRecorderSubsystem> TakeRecorderSubsystem;` — Weak ptr to take recorder subsystem.
- L226 _private member_ `FDelegateHandle PostUndoRedoDelegateHandle;` — Handle for binding to the post undo/redo editor delegate.

### `Plugins/VirtualProduction/Takes/Source/TakeRecorderEditor/Private/Widgets/STakeRecorderPanel.h` (Private)


#### class `STakeRecorderPanel`  
`class STakeRecorderPanel : public SCompoundWidget`  
_L34-160_
- inherits: `SCompoundWidget`
- desc: Outermost widget that is used for setting up a new take recording. Operates on a transient UTakePreset that is internally owned and maintained
- L38 _public prototype_ `~STakeRecorderPanel();`
- L40 _public function_ `SLATE_BEGIN_ARGS(STakeRecorderPanel) : _BasePreset(nullptr) , _BaseSequence(nullptr) , _RecordIntoSequence(nullptr) , _SequenceToView(nullptr)`
- L50 _public prototype_ `SLATE_ARGUMENT(UTakePreset*, BasePreset) SLATE_ARGUMENT(ULevelSequence*, BaseSequence) SLATE_ARGUMENT(ULevelSequence*, RecordIntoSequence) SLATE_ARGUMENT(ULevelSequence*, SequenceToView) SLATE_END_ARGS() void Construct(const FArguments& InArgs);` — A preset asset to base the recording off
- L66 _public prototype_ `ULevelSequence* GetLevelSequence() const;`
- L68 _public prototype_ `ULevelSequence* GetLastRecordedLevelSequence() const;`
- L70 _public prototype_ `ETakeRecorderMode GetTakeRecorderMode() const;`
- L72 _public prototype_ `UTakeMetaData* GetTakeMetaData() const;`
- L74 _public function_ `TSharedPtr<STakeRecorderCockpit> GetCockpitWidget() const`
- L76 _public prototype_ `void ClearPendingTake();`
- L77 _public prototype_ `void ResetToPendingTake();`
- L79 _public prototype_ `TOptional<ETakeRecorderPanelMode> GetMode() const;`
- L86 _private prototype_ `void RefreshPanel();` — Refresh this panel after a change to its preset or levelsequence
- L91 _private prototype_ `bool GetSavePresetPackageName(FString& OutName);` — Prompt for a package name to save the current setup as a preset
- L95 _private prototype_ `TSharedRef<SWidget> OnGeneratePresetsMenu();`
- L97 _private prototype_ `void OnImportPreset(const FAssetData& InPreset);`
- L99 _private prototype_ `void OnSaveAsPreset();`
- L101 _private prototype_ `FReply OnRevertChanges();`
- L103 _private prototype_ `FReply OnBackToPendingTake();`
- L105 _private prototype_ `FReply OnClearPendingTake();`
- L107 _private prototype_ `FReply OnReviewLastRecording();`
- L110 _private prototype_ `void OnTakePresetSettingsChanged();` — Handles the UTakePresetSettings::RecordTargetClass changing. Recreates the object if recording a transaction or refreshes sequencer if undo / redoing.
- L112 _private prototype_ `void OnBeforeRedoUndo(const FTransactionContext& TransactionContext) const;` — If the transaction changes the UTakePresetSettings::RecordTargetClass, temporarily closes the sequencer in order to refresh it.
- L114 _private prototype_ `TSharedRef<SWidget> OnOpenSequenceToRecordIntoMenu();`
- L116 _private prototype_ `void OnOpenSequenceToRecordInto(const FAssetData& InAsset);`
- L118 _private prototype_ `ECheckBoxState GetSettingsCheckState() const;`
- L119 _private prototype_ `void ToggleSettings(ECheckBoxState CheckState);`
- L121 _private prototype_ `void OnLevelSequenceChanged();`
- L123 _private prototype_ `void OnLevelSequenceDetailsChanged(const FPropertyChangedEvent& InPropertyChangedEvent);` — When properties in a level sequence details have been changed.
- L125 _private prototype_ `void OnLevelSequenceDetailsViewAdded(const TWeakPtr<IDetailsView>& InDetailsView);` — When a level sequence has a details view added.
- L127 _private prototype_ `ECheckBoxState GetTakeBrowserCheckState() const;`
- L128 _private prototype_ `void ToggleTakeBrowserCheckState(ECheckBoxState CheckState);`
- L131 _private prototype_ `void ReconfigureExternalSettings(UObject* InExternalObject, bool bIsAdd);`
- L133 _private prototype_ `void OnRecordingInitialized(UTakeRecorder* Recorder);`
- L135 _private prototype_ `void OnRecordingFinished(UTakeRecorder* Recorder);`
- L137 _private prototype_ `void OnRecordingCancelled(UTakeRecorder* Recorder);`
- L139 _private prototype_ `TSharedRef<SWidget> MakeToolBar();`
- L141 _private prototype_ `TSharedRef<SWidget> MakeSimpleViewToggleButton();`
- L144 _private prototype_ `bool CanReviewLastLevelSequence() const;`
- L147 _private member_ `TWeakObjectPtr<UTakeRecorderSubsystem> TakeRecorderSubsystem;` — Weak ptr to subsystem.
- L150 _private member_ `TSharedPtr<SLevelSequenceTakeEditor> LevelSequenceTakeWidget;` — The main level sequence take editor widget
- L152 _private member_ `TSharedPtr<STakeRecorderCockpit> CockpitWidget;` — The recorder cockpit
- L154 _private member_ `TSharedPtr<FScopedSequencerPanel> SequencerPanel;` — Scoped panel that handles opening and closing the sequencer pane for this preset
- L156 _private member_ `FDelegateHandle OnWidgetExternalObjectChangedHandle;`
- L157 _private member_ `FDelegateHandle OnLevelSequenceChangedHandle;`
- L159 _private member_ `FDelegateHandle OnRecordingInitializedHandle, OnRecordingFinishedHandle, OnRecordingCancelledHandle;`
- L159 _private member_ `FDelegateHandle OnRecordingInitializedHandle, OnRecordingFinishedHandle, OnRecordingCancelledHandle;`
- L159 _private member_ `FDelegateHandle OnRecordingInitializedHandle, OnRecordingFinishedHandle, OnRecordingCancelledHandle;`

### `Plugins/VirtualProduction/Takes/Source/TakeRecorderEditor/Private/Widgets/STakeRecorderSources.h` (Private)


#### class `STakeRecorderSources`  
`class STakeRecorderSources : public SCompoundWidget`  
_L28-73_
- inherits: `SCompoundWidget`
- desc: Main widget for the take recorder sources panel
- L32 _public function_ `SLATE_BEGIN_ARGS(STakeRecorderSources)`
- L33 _public prototype_ `SLATE_EVENT(FOnSourcesSelectionChanged, OnSelectionChanged) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L38 _public prototype_ `void SetSourceObject(UTakeRecorderSources* InSources);`
- L40 _public prototype_ `void GetSelectedSources(TArray<UTakeRecorderSource*>& OutSources) const;`
- L44 _private prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;`
- L45 _private prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L49 _private prototype_ `void ReconstructTree();`
- L51 _private prototype_ `TSharedRef<ITableRow> OnGenerateRow(TSharedPtr<ITakeRecorderSourceTreeItem> Item, const TSharedRef<STableViewBase>& Tree);`
- L53 _private prototype_ `void OnGetChildren(TSharedPtr<ITakeRecorderSourceTreeItem> Item, TArray<TSharedPtr<ITakeRecorderSourceTreeItem>>& OutChildItems);`
- L55 _private prototype_ `FReply OnDragDropTarget(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent);`
- L57 _private prototype_ `bool CanDragDropTarget(TSharedPtr<FDragDropOperation> InOperation);`
- L59 _private prototype_ `void OnDeleteSelected();`
- L61 _private prototype_ `bool IsLocked() const;`
- L65 _private member_ `uint32 CachedSourcesSerialNumber;`
- L66 _private member_ `TWeakObjectPtr<UTakeRecorderSources> WeakSources;`
- L68 _private member_ `TArray<TSharedPtr<ITakeRecorderSourceTreeItem>> RootNodes;`
- L69 _private member_ `TMap<FObjectKey, TSharedPtr<FTakeRecorderSourceTreeItem>> SourceToTreeItem;`
- L70 _private member_ `TSharedPtr<STreeView<TSharedPtr<ITakeRecorderSourceTreeItem>>> TreeView;`
- L72 _private member_ `TSharedPtr<FUICommandList> CommandList;`

#### Free symbols / members of external scopes

- L21 _delegate_ `DECLARE_DELEGATE_TwoParams( FOnSourcesSelectionChanged, TSharedPtr<ITakeRecorderSourceTreeItem>, ESelectInfo::Type ) class STakeRecorderSources : public SCompoundWidget { public: SLATE_BEGIN_ARGS(STakeRecorderSources){} SLATE_EVENT(FOnSourcesSelectionChanged, OnSelectionChanged) SLATE_END_ARGS() void Construct(const FArguments& InArgs); void SetSourceObject(UTakeRecorderSources* InSources); void GetSelectedSources(TArray<UTakeRecorderSource*>& OutSources) const; private: virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override; virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override; private: void ReconstructTree(); TSharedRef<ITableRow> OnGenerateRow(TSharedPtr<ITakeRecorderSourceTreeItem> Item, const TSharedRef<STableViewBase>& Tree); void OnGetChildren(TSharedPtr<ITakeRecorderSourceTreeItem> Item, TArray<TSharedPtr<ITakeRecorderSourceTreeItem>>& OutChildItems); FReply OnDragDropTarget(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent); bool CanDragDropTarget(TSharedPtr<FDragDropOperation> InOperation); void OnDeleteSelected();`

### `Plugins/VirtualProduction/Takes/Source/TakeRecorderEditor/Private/Widgets/STakeRecorderTabContent.h` (Private)


#### class `STakeRecorderTabContent`  
`class STakeRecorderTabContent : public ITakeRecorderTabContent`  
_L16-65_
- inherits: `ITakeRecorderTabContent`
- L20 _public function_ `SLATE_BEGIN_ARGS(STakeRecorderTabContent)`
- L23 _public prototype_ `virtual ~STakeRecorderTabContent() override;`
- L25 _public prototype_ `void Construct(const FArguments& InArgs);`
- L28 _public prototype_ `virtual FText GetTitle() const override;`
- L29 _public prototype_ `virtual const FSlateBrush* GetIcon() const override;`
- L30 _public prototype_ `virtual TOptional<ETakeRecorderPanelMode> GetMode() const override;`
- L31 _public prototype_ `virtual void SetupForRecording(ULevelSequence* LevelSequenceAsset) override;`
- L32 _public prototype_ `virtual void SetupForRecording(UTakePreset* BasePreset) override;`
- L33 _public prototype_ `virtual void SetupForRecordingInto(ULevelSequence* LevelSequenceAsset) override;`
- L34 _public prototype_ `virtual void SetupForEditing(UTakePreset* Preset) override;`
- L36 _public prototype_ `virtual void SetupForEditing(TSharedPtr<FTakePresetToolkit> InToolkit) override;` — WITH_EDITOR
- L38 _public prototype_ `virtual void SetupForViewing(ULevelSequence* LevelSequence) override;` — WITH_EDITOR
- L39 _public prototype_ `virtual ULevelSequence* GetLevelSequence() const override;`
- L40 _public prototype_ `virtual ULevelSequence* GetLastRecordedLevelSequence() const override;`
- L41 _public prototype_ `virtual UTakeMetaData* GetTakeMetaData() const override;`
- L42 _public prototype_ `virtual FFrameRate GetFrameRate() const override;`
- L43 _public prototype_ `virtual void SetFrameRate(FFrameRate InFrameRate) override;`
- L44 _public prototype_ `virtual void SetFrameRateFromTimecode(bool bInFromTimecode) override;`
- L45 _public prototype_ `virtual UTakeRecorderSources* GetSources() const override;`
- L46 _public prototype_ `virtual void StartRecording() const override;`
- L47 _public prototype_ `virtual void StopRecording() const override;`
- L48 _public prototype_ `virtual void ClearPendingTake() override;`
- L49 _public prototype_ `virtual bool CanStartRecording(FText& ErrorText) const override;`
- L50 _public function_ `virtual const TWeakPtr<STakeRecorderPanel>& GetTakeRecorderPanel() const override`
- L55 _private prototype_ `EActiveTimerReturnType OnActiveTimer(double InCurrentTime, float InDeltaTime);`
- L57 _private prototype_ `void OnPresetClosed();`
- L61 _private member_ `TAttribute<FText> TitleAttribute;`
- L62 _private member_ `TAttribute<const FSlateBrush*> IconAttribute;`
- L63 _private member_ `TWeakPtr<STakeRecorderPanel> WeakPanel;`
- L64 _private member_ `TWeakPtr<STakePresetAssetEditor> WeakAssetEditor;`

### `Plugins/VirtualProduction/Takes/Source/TakeRecorderEditor/Private/Widgets/TakeRecorderWidgetConstants.h` (Private)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace TakeRecorder`
- L10 _variable_ `static FMargin ButtonOffset(FMargin(0.f, 0.f, 4.f, 0.f));` (scope `TakeRecorder`) — Button offset to apply to buttons on take recorder panel toolbars
- L13 _variable_ `static FMargin ButtonPadding(4.f);` (scope `TakeRecorder`) — Button padding to apply to buttons inside take recorder panel toolbars
- L16 _variable_ `static FMargin ToolbarPadding(FMargin(0.f, 2.f));` (scope `TakeRecorder`) — Outer padding to used for toolbars on the take preset asset editor and take recorder UI
