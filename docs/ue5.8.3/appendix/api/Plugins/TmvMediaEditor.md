# Plugins / TmvMediaEditor

- module root: `Plugins/Media/TmvMedia/Source/TmvMediaEditor`
- headers: 17; symbols: 236
- symbol kinds: class=16, delegate=6, function=34, member=50, namespace=6, prototype=123, struct=1
- PrivateDependencyModuleNames: ApplicationCore, AssetRegistry, ContentBrowserData, Core, CoreUObject, DesktopWidgets, EditorWidgets, InputCore, MediaAssets, Projects, PropertyEditor, Slate, SlateCore, TmvMedia, UnrealEd, WorkspaceMenuStructure

### `Plugins/Media/TmvMedia/Source/TmvMediaEditor/Private/Customizations/TmvMediaDirectoryPathCustomization.h` (Private)


#### class `FTmvMediaDirectoryPathCustomization`  
`class FTmvMediaDirectoryPathCustomization : public IPropertyTypeCustomization`  
_L18-60_
- inherits: `IPropertyTypeCustomization`
- desc: Implements a customization for the FDirectoryPath class for Tmv transcoder. Details: - The picked path is either made absolute if outside the project or relative to the project. - Implements drag and drop of files from the explorer.
- L22 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();` — Make an instance of this property type customization.
- L25 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> InPropertyHandle, FDetailWidgetRow& InHeaderRow, IPropertyTypeCustomizationUtils& InCustomizationUtils) override;`
- L27 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> InPropertyHandle, IDetailChildrenBuilder& InChildBuilder, IPropertyTypeCustomizationUtils& InCustomizationUtils) override;`
- L35 _private prototype_ `FString GetDirectoryPath(bool bReturnEmptyOnMultiSelect) const;` — Gets the directory path from the property handle.
- L40 _private prototype_ `void HandleDirectoryPickerDirectoryChanged(const FString& InPickedDirectory, bool bInContentDir);` — Called when a directory is selected.
- L45 _private prototype_ `bool HandleVerifyDrag(TSharedPtr<FDragDropOperation> InDragOperation);` — Called when a drag operation enters the widget.
- L50 _private prototype_ `FReply HandleDropEvent(const FGeometry& InGeometry, const FDragDropEvent& InDropEvent);` — Called on a drag drop event.
- L53 _private prototype_ `bool IsEnabled() const;` — Returns true if the widget is enabled (editable).
- L56 _private member_ `TSharedPtr<IPropertyHandle> PathStringProperty;` — Pointer to the string that will be set when changing the path
- L59 _private member_ `bool bContentDir = false;` — Indicates that the path will be picked using the Slate-style directory picker inside the game Content dir.

### `Plugins/Media/TmvMedia/Source/TmvMediaEditor/Private/Customizations/TmvMediaEncoderOptionsEnumCustomization.h` (Private)


#### class `FTmvMediaEncoderOptionsEnumIdentifier`  
`class FTmvMediaEncoderOptionsEnumIdentifier : public IPropertyTypeIdentifier`  
_L14-18_
- inherits: `IPropertyTypeIdentifier`
- desc: Identifies the DestinationColorSpace / DestinationEncoding properties of FTmvMediaEncoderOptions so that the customization below only applies to those two properties and leaves any other use of the same enums alone.
- L17 _public prototype_ `virtual bool IsPropertyTypeCustomized(const IPropertyHandle& InHandle) const override;`

#### class `FTmvMediaEncoderOptionsEnumCustomization`  
`class FTmvMediaEncoderOptionsEnumCustomization : public IPropertyTypeCustomization`  
_L26-41_
- inherits: `IPropertyTypeCustomization`
- desc: Property type customization for the DestinationColorSpace (ETextureColorSpace) and DestinationEncoding (ETmvMediaEncoderEncoding) properties on FTmvMediaEncoderOptions. Adds an FPropertyRestriction that hides enum values not returned by the encoder-specific GetSupportedDestination... virtuals, then defers to the default property combo box so the widget matches every other enum dropdown in the panel.
- L29 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L32 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> InPropertyHandle, FDetailWidgetRow& InHeaderRow, IPropertyTypeCustomizationUtils& InCustomizationUtils) override;`
- L34 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> InPropertyHandle, IDetailChildrenBuilder& InChildBuilder, IPropertyTypeCustomizationUtils& InCustomizationUtils) override;`
- L40 _private prototype_ `void ApplySupportedValuesRestriction(const TSharedRef<IPropertyHandle>& InPropertyHandle);` — Adds an FPropertyRestriction hiding every enum value not in the encoder's supported subset.

### `Plugins/Media/TmvMedia/Source/TmvMediaEditor/Private/Customizations/TmvMediaFilePathCustomization.h` (Private)


#### class `FTmvMediaFilePathCustomization`  
`class FTmvMediaFilePathCustomization : public IPropertyTypeCustomization`  
_L18-54_
- inherits: `IPropertyTypeCustomization`
- desc: Implements a customization for the FFilePath class for Tmv transcoder. Details: - The picked path is either made absolute if outside the project or relative to the project. - Implements drag and drop of files from the explorer.
- L22 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();` — Make an instance of this property type customization.
- L25 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> InPropertyHandle, FDetailWidgetRow& InHeaderRow, IPropertyTypeCustomizationUtils& InCustomizationUtils) override;`
- L27 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> InPropertyHandle, IDetailChildrenBuilder& InChildBuilder, IPropertyTypeCustomizationUtils& InCustomizationUtils) override;`
- L35 _private prototype_ `FString HandleFilePathPickerFilePath(bool bReturnEmptyOnMultiSelect) const;` — Gets the file path.
- L40 _private prototype_ `void HandleFilePathPickerPathPicked(const FString& InPickedPath);` — Called when a path is selected.
- L45 _private prototype_ `bool HandleVerifyDrag(TSharedPtr<FDragDropOperation> InDragOperation);` — Called when a drag operation enters the widget.
- L50 _private prototype_ `FReply HandleDropEvent(const FGeometry& InGeometry, const FDragDropEvent& InDropEvent);` — Called on a drag drop event.
- L53 _private member_ `TSharedPtr<IPropertyHandle> PathStringProperty;` — Pointer to the string that will be set when changing the path

### `Plugins/Media/TmvMedia/Source/TmvMediaEditor/Private/Customizations/TmvMediaMuxerSettingsCustomization.h` (Private)


#### class `FTmvMediaMuxerSettingsCustomization`  
`class FTmvMediaMuxerSettingsCustomization : public IPropertyTypeCustomization`  
_L13-44_
- inherits: `IPropertyTypeCustomization`
- desc: Implements a property type customization for FTmvMediaTranscodeMuxerSettings. The Name field is displayed as a combo box populated from registered ITmvMediaMuxerFactory instances.
- L17 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();` — Make an instance of this property type customization.
- L20 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> InPropertyHandle, FDetailWidgetRow& InHeaderRow, IPropertyTypeCustomizationUtils& InCustomizationUtils) override;`
- L22 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> InPropertyHandle, IDetailChildrenBuilder& InChildBuilder, IPropertyTypeCustomizationUtils& InCustomizationUtils) override;`
- L28 _private prototype_ `void RefreshMuxerOptions();` — Refresh the list of available muxer factories.
- L31 _private prototype_ `void OnMuxerSelectionChanged(TSharedPtr<FString> InNewSelection, ESelectInfo::Type InSelectInfo);` — Called when the combo box selection changes.
- L34 _private prototype_ `FText GetSelectedMuxerDisplayName() const;` — Returns the currently selected muxer display name.
- L37 _private member_ `TSharedPtr<IPropertyHandle> NameProperty;` — Handle to the Name property of FTmvMediaTranscodeMuxerSettings.
- L40 _private member_ `TArray<TSharedPtr<FString>> MuxerDisplayNames;` — Available muxer option strings for the combo box (display names).
- L43 _private member_ `TMap<FString, FName> DisplayNameToFactoryName;` — Mapping from display name to factory FName.

### `Plugins/Media/TmvMedia/Source/TmvMediaEditor/Private/TmvMediaEditorLog.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogTmvMediaEditor, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogTmvMediaEditor, Log, All);`

### `Plugins/Media/TmvMedia/Source/TmvMediaEditor/Private/TmvMediaEditorStyle.h` (Private)


#### class `FTmvMediaEditorStyle`  
`class FTmvMediaEditorStyle final : public FSlateStyleSet`  
_L7-15_
- inherits: `FSlateStyleSet`
- L10 _public prototype_ `static FTmvMediaEditorStyle& Get();`
- L12 _public prototype_ `FTmvMediaEditorStyle();`

### `Plugins/Media/TmvMedia/Source/TmvMediaEditor/Private/Widgets/STmvMediaDirectoryPicker.h` (Private)


#### class `STmvMediaDirectoryPicker`  
`class STmvMediaDirectoryPicker : public SCompoundWidget`  
_L23-126_
- inherits: `SCompoundWidget`
- desc: A directory path box, with a button for picking a new path. Reimplementation of SDirectoryPicker. Differences: - Made the text box display a delegate to allow user class to intercept and sanitize the picked path. - Made it match the look, feel and functionality of SFilePathPicker (font, style, title, etc).
- L27 _public prototype_ `DECLARE_DELEGATE_TwoParams(FOnDirectoryChanged, const FString& , bool );` — Declares a delegate that is executed when a directory was picked.
- L29 _public function_ `SLATE_BEGIN_ARGS(STmvMediaDirectoryPicker) : _BrowseButtonToolTip(NSLOCTEXT("STmvMediaDirectoryPicker", "BrowseButtonToolTip", "Choose a directory from this computer")) , _Font() , _IsReadOnly(false) , _ContentDir(false) , _ForceShowPluginContent(false) , _ForceShowEngineContent(false)`
- L78 _public prototype_ `void Construct(const FArguments& InArgs);`
- L82 _private prototype_ `void OnDirectoryTextCommited(const FText& InText, ETextCommit::Type InCommitType);` — DirectoryTextBox - OnTextCommitted event handler.
- L85 _private prototype_ `FText GetDirectoryTextBoxText() const;` — DirectoryTextBox - Text attribute handler.
- L88 _private prototype_ `FReply OnBrowseButtonClicked();` — Browse Button - OnClicked event handler.
- L91 _private prototype_ `bool OpenPlatformDirectoryPicker(FString& OutDirectory, const FString& InDefaultPath) const;` — Utility function to open a directory picker dialog.
- L94 _private prototype_ `void OpenContentPathPicker(const FString& InDefaultPath);` — Utility function to open a content path picker drop down menu.
- L97 _private prototype_ `void OnContentPathPicked(const FString& InPickedPath);` — Content Picker Menu - Called when a content path is picked.
- L101 _private member_ `TAttribute<FString> BrowseDirectory;` — Holds the directory path to browse by default.
- L104 _private member_ `TAttribute<FText> BrowseTitle;` — Holds the title for the browse dialog window.
- L107 _private member_ `TAttribute<FString> DirectoryPath;` — Holds the currently selected directory path.
- L110 _private member_ `FOnDirectoryChanged OnDirectoryChanged;` — Holds a delegate that is executed when a directory was picked.
- L113 _private member_ `TSharedPtr<SEditableTextBox> DirectoryTextBox;` — Editable text box for the directory path.
- L116 _private member_ `TSharedPtr<IMenu> ContentPickerMenu;` — The content pick button popup menu
- L119 _private member_ `bool bContentDir = false;` — Indicates that the path will be picked using the Slate-style directory picker inside the game Content dir.
- L122 _private member_ `bool bForceShowPluginContent = false;` — Indicates that the asset pickers should always show plugin content
- L125 _private member_ `bool bForceShowEngineContent = false;` — Indicates that the asset pickers should always show engine content

#### Free symbols / members of external scopes

- L27 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnDirectoryChanged, const FString& , bool );` — Declares a delegate that is executed when a directory was picked.

### `Plugins/Media/TmvMedia/Source/TmvMediaEditor/Private/Widgets/STmvMediaTranscodeJobMonitor.h` (Private)


#### class `STmvMediaTranscodeJobMonitor`  
`class STmvMediaTranscodeJobMonitor : public SCompoundWidget`  
_L16-56_
- inherits: `SCompoundWidget`
- desc: Monitors (and partially manages) active transcode jobs from the global job manager.
- L19 _public function_ `SLATE_BEGIN_ARGS(STmvMediaTranscodeJobMonitor)`
- L20 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L25 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L31 _private prototype_ `TSharedRef<ITableRow> OnGenerateRow(TSharedPtr<FTmvMediaTranscodeJobMonitorItem> InItem, const TSharedRef<STableViewBase>& InOwnerTable) const;` — SListView row generation handler.
- L34 _private prototype_ `void RefreshTranscodeJobList();` — Refresh the list of transcode jobs from the job manager.
- L37 _private function_ `void OnTranscodeJobAdded(UTmvMediaTranscodeJob* InJob)` — Called when a job is added to the job manager.
- L43 _private function_ `void OnTranscodeJobRemoved(UTmvMediaTranscodeJob* InJob)` — Called when a job is removed from the job manager.
- L49 _private member_ `TSharedPtr<SListView<TSharedPtr<FTmvMediaTranscodeJobMonitorItem>>> JobListView;` — Job list View
- L52 _private member_ `TArray<TSharedPtr<FTmvMediaTranscodeJobMonitorItem>> JobList;` — Job list View items, reflect the active jobs in the job manager.
- L55 _private member_ `double LastJobListRefreshTime = 0.0;` — Keep track of the refresh time to throttle UI updates.

### `Plugins/Media/TmvMedia/Source/TmvMediaEditor/Private/Widgets/STmvMediaTranscodeList.h` (Private)


#### class `STmvMediaTranscodeList`  
`class STmvMediaTranscodeList : public SCompoundWidget`  
_L20-94_
- inherits: `SCompoundWidget`
- desc: Tmv Media Transcoder Job List widget
- L23 _public function_ `SLATE_BEGIN_ARGS(STmvMediaTranscodeList)`
- L25 _public prototype_ `SLATE_ARGUMENT(TSharedPtr<FTmvMediaTranscodeListHandle>, ListHandle) SLATE_ARGUMENT(TSharedPtr<FUICommandList>, CommandList) SLATE_END_ARGS() virtual ~STmvMediaTranscodeList() override;` — Handle to the transcode list object.
- L32 _public prototype_ `void Construct(const FArguments& InArgs);`
- L35 _public prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;`
- L40 _private prototype_ `void BindCommands(const TSharedPtr<FUICommandList>& InCommandList);` — Bind this widget's commands to the command list.
- L43 _private prototype_ `TSharedRef<ITableRow> OnGenerateRow(TSharedPtr<FTmvMediaTranscodeJobListItem> InItem, const TSharedRef<STableViewBase>& InOwnerTable) const;` — JobListView (SListView) row widget generation handler.
- L46 _private prototype_ `void OnSelectionChanged(TSharedPtr<FTmvMediaTranscodeJobListItem> InItem, ESelectInfo::Type InSelectInfo);` — JobListView (SListView) selection change handler.
- L49 _private prototype_ `bool IsSelectionValid() const;` — Returns true if the job view is valid and current item selection is not empty.
- L52 _private prototype_ `bool CanAddJob() const;` — AddJob Button handlers
- L53 _private prototype_ `FReply OnAddJob();`
- L56 _private function_ `bool CanDuplicateSelectedJobs() const` — Duplicate Job Button handlers
- L57 _private prototype_ `FReply OnDuplicateSelectedJobs();`
- L60 _private function_ `bool CanRemoveSelectedJobs() const` — Remove Job Button handlers
- L61 _private prototype_ `FReply OnRemoveSelectedJobs();`
- L64 _private prototype_ `bool CanRenameSelectedJob() const;` — Rename Jobs Action handlers
- L65 _private prototype_ `void RenameSelectedJob();`
- L68 _private function_ `bool CanCutSelectedJobs() const` — Cut Jobs Action handlers
- L69 _private prototype_ `void CutSelectedJobs();`
- L72 _private function_ `bool CanCopySelectedJobs() const` — Copy Jobs Action handlers
- L73 _private prototype_ `void CopySelectedJobs();`
- L76 _private prototype_ `bool CanPaste() const;` — Paste Jobs Action handlers
- L77 _private prototype_ `void Paste();`
- L80 _private prototype_ `void OnTranscodeListItemEvent(const UTmvMediaTranscodeList* InList, const FTmvMediaTranscodeListItemEventArgs& InArgs);` — Transcode List Item Event Handler.
- L84 _private member_ `TSharedPtr<FTmvMediaTranscodeListHandle> ListHandle;` — Transcode list being edited.
- L87 _private member_ `TSharedPtr<SListView<TSharedPtr<FTmvMediaTranscodeJobListItem>>> JobListView;` — Job List View widget.
- L90 _private member_ `TArray<TSharedPtr<FTmvMediaTranscodeJobListItem>> JobList;` — Job List View items (widget's backing array), reflect the transcode list elements.
- L93 _private member_ `TSharedPtr<FUICommandList> CommandList;` — Shared Bound Command list for menus, toolbars and buttons.

### `Plugins/Media/TmvMedia/Source/TmvMediaEditor/Private/Widgets/STmvMediaTranscoder.h` (Private)


#### class `STmvMediaTranscoder`  
`class STmvMediaTranscoder : public SCompoundWidget`  
_L17-110_
- inherits: `SCompoundWidget`
- desc: Tmv Media Transcoder Panel This widget is the main panel widget.
- L20 _public function_ `SLATE_BEGIN_ARGS(STmvMediaTranscoder)`
- L23 _public prototype_ `virtual ~STmvMediaTranscoder() override;`
- L25 _public prototype_ `void Construct(const FArguments& InArgs);`
- L28 _public prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;`
- L33 _private prototype_ `int32 GetDetailsViewWidgetIndex() const;` — Details View Widget switcher handler. Returns which widget index to view.
- L40 _private prototype_ `void BindCommands(const TSharedPtr<FUICommandList>& InCommandBindings);` — Allows the editors to bind commands. @param InCommandBindings The existing command bindings to map to.
- L43 _private prototype_ `bool CanCreateNewJobList() const;` — Job List Command handlers
- L44 _private prototype_ `void OnCreateNewJobList();`
- L45 _private prototype_ `void OnOpenJobList();`
- L46 _private prototype_ `bool CanLoadJobList() const;`
- L47 _private prototype_ `void OnLoadJobList();`
- L48 _private prototype_ `bool CanSaveJobList() const;`
- L49 _private prototype_ `void OnSaveJobList();`
- L50 _private prototype_ `void OnSaveJobListAs();`
- L51 _private prototype_ `void OnImportJobItemFrom();`
- L52 _private prototype_ `void OnExportJobItemAs();`
- L55 _private prototype_ `FString GetJobListPath() const;` — Returns the current job list file path.
- L58 _private prototype_ `void SetJobListPath(const FString& InPath);` — Sets the current job list file path. This will persist in the transcoder config settings.
- L61 _private prototype_ `void ResetJobListPath();` — Reset the current job list file path. This will persist in the transcoder config settings.
- L64 _private prototype_ `FString GetJobListBrowseDirectory() const;` — Returns the default browse directory for the job list file dialog(s).
- L67 _private prototype_ `bool LoadJobList(const FString& InPath);` — Load a job list from the given file path. Only support json for now.
- L70 _private prototype_ `int32 GetFirstSelectedItem() const;` — Utility function to retrieve the first selected item.
- L73 _private function_ `bool IsItemSelectionValid() const` — Determines if the selection is valid.
- L79 _private prototype_ `FString GetLastJobItemPath() const;` — Returns the file path of the last exported job item.
- L82 _private prototype_ `void SetLastJobItemPath(const FString& InPath);` — Set the file path of the last exported job item. This will persist in the transcoder config settings.
- L85 _private prototype_ `FString GetJobItemBrowseDirectory() const;` — Returns the default browse directory for the job item file dialog(s).
- L88 _private prototype_ `bool LoadJobItem(int32 InItemIndex, const FString& InJobItemPath);` — Load (import) a job item in the current list from the given file path (support json format only for now).
- L91 _private prototype_ `bool SaveJobItem(int32 InItemIndex, const FString& InJobItemPath);` — Save (export) a job item from the current list to the given file path (support json format only for now).
- L94 _private member_ `FString TranscodeListPath;` — File path to save or load the job settings to or from
- L97 _private member_ `FString LastJobItemPath;` — Keep track of the last (imported or exported) job item path.
- L100 _private member_ `TStrongObjectPtr<UTmvMediaTranscodeList> TranscodeList;` — Currently loaded transcode list.
- L103 _private member_ `TSharedPtr<FTmvMediaTranscodeListHandle> TranscodeListHandle;` — Backing handle for all editing operations on the transcode list. (this should be the "asset editor" object normally)
- L106 _private member_ `TSharedPtr<STmvMediaTranscoderJobControls> JobControls;` — Job Controls (start, stop) toolbar widget.
- L109 _private member_ `TSharedPtr<FUICommandList> CommandList;` — Shared Bound Command list for menus, toolbars and buttons.

### `Plugins/Media/TmvMedia/Source/TmvMediaEditor/Private/Widgets/STmvMediaTranscoderJobControls.h` (Private)


#### class `STmvMediaTranscoderJobControls`  
`class STmvMediaTranscoderJobControls : public SCompoundWidget`  
_L17-62_
- inherits: `SCompoundWidget`
- desc: Tmv Transcoder job controls widget
- L20 _public function_ `SLATE_BEGIN_ARGS(STmvMediaTranscoderJobControls)`
- L23 _public prototype_ `virtual ~STmvMediaTranscoderJobControls() override;`
- L25 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedPtr<FTmvMediaTranscodeListHandle>& InListHandle);`
- L28 _public prototype_ `bool IsProcessing() const;` — Returns true if at least one job submitted by this widget is still active or pending.
- L32 _private prototype_ `bool IsJobProcessingOrPending(const FGuid& InJobId) const;` — Returns true if the given job is one we submitted and the runner still has it active or pending.
- L35 _private prototype_ `FText GetStartJobsToolTip() const;` — Returns the Start Jobs button tool tip.
- L38 _private prototype_ `bool CanStartJobItem(const FTmvMediaTranscodeListItem& InJobItem) const;` — Returns true if the given job item can be started.
- L41 _private prototype_ `bool CanStartJobs() const;` — Returns true if the currently selected set of jobs can be started.
- L44 _private prototype_ `FReply OnStartJobs();` — Called when we click on the start jobs button.
- L47 _private prototype_ `bool CanCancelJobs() const;` — Returns true if the current set of running or pending jobs can be cancelled.
- L50 _private prototype_ `FReply OnCancelJobs();` — Called when we click on the cancel button.
- L52 _private prototype_ `void OnRunnerJobFinished(UTmvMediaTranscodeJob* InJob);`
- L55 _private member_ `TSharedPtr<FTmvMediaTranscodeListHandle> ListHandle;` — Reference to the transcode list
- L61 _private member_ `TSet<FGuid> SubmittedJobIds;` — Ids of jobs this widget enqueued in the global runner. Used to scope can-start / cancel queries to jobs we own, so we ignore (and don't cancel) jobs from other callers.

### `Plugins/Media/TmvMedia/Source/TmvMediaEditor/Private/Widgets/STmvMediaTranscoderJobDetails.h` (Private)


#### class `STmvMediaTranscoderJobDetails`  
`class STmvMediaTranscoderJobDetails : public SCompoundWidget, public FNotifyHook`  
_L18-99_
- inherits: `SCompoundWidget,FNotifyHook`
- desc: Transcoder Job Settings and Encoder Options Detail views for the Tmv transcoder list editor.
- L21 _public function_ `SLATE_BEGIN_ARGS(STmvMediaTranscoderJobDetails)`
- L24 _public prototype_ `virtual ~STmvMediaTranscoderJobDetails() override;`
- L26 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedPtr<FTmvMediaTranscodeListHandle>& InListHandle);`
- L30 _private prototype_ `bool IsDetailsEnabled() const;` — Returns true if the detail panel should be enabled for editing.
- L33 _private prototype_ `void OnJobItemSelectionChanged(const UTmvMediaTranscodeList* InList, TConstArrayView<int32> InSelectedItems);` — Handles transcode list selection changed to update the details view.
- L36 _private prototype_ `void OnTranscodeListItemEvent(const UTmvMediaTranscodeList* InList, const FTmvMediaTranscodeListItemEventArgs& InArgs);` — Handles transcode list event (add, remove, modified, etc) to update the details view.
- L39 _private prototype_ `void OnTranscodeListChanged(UTmvMediaTranscodeList* InPreviousList, UTmvMediaTranscodeList* InNewList);` — Handles transcode list changed (i.e. a new list is loaded) to update the details view.
- L42 _private prototype_ `void OnFinishedChangingProperties(const FPropertyChangedEvent& InChangedEvent);` — Details View event handling. Propagates the detail view event.
- L45 _private prototype_ `virtual void NotifyPreChange(FEditPropertyChain* InPropertyAboutToChange) override;`
- L46 _private prototype_ `virtual void NotifyPostChange(const FPropertyChangedEvent& InPropertyChangedEvent, FEditPropertyChain* InPropertyThatChanged) override;`
- L50 _private prototype_ `void RefreshJobSettingsDetailsView();` — Refresh (create or update) the Job Setting Details View.
- L53 _private prototype_ `void RefreshEncoderOptionsDetailsView();` — Refresh (create or update) the Encoder Options Details View.
- L56 _private prototype_ `void RefreshEncoderOptionsCombo();` — Encoder Options Combo Box - Make sure the encoder option combo box is reflecting the current job item.
- L59 _private prototype_ `void SetupEncoderOptionsSelection();` — Encoder Options Combo Box - Populate Encoder Options Structs list for Combo Box.
- L65 _private prototype_ `const UScriptStruct* GetEncoderOptionsItem() const;` — Encoder Options Combo Box - Returns the selected "item" from the backing list. @return the currently selected struct or null if multiple different values.
- L68 _private prototype_ `FText GetEncoderOptionsContent() const;` — Encoder Options Combo Box - Returns the text to display in the combo box content.
- L71 _private prototype_ `TSharedRef<SWidget> MakeEncoderOptionsItemWidget(const UScriptStruct* InItem);` — Encoder Options Combo Box - Returns the widget (a text box) for the given item.
- L74 _private prototype_ `void OnEncoderOptionsSelectionChanged(const UScriptStruct* InNewSelection, ESelectInfo::Type InSelectInfo);` — Encoder Options Combo Box - Handles updating the job item and details view when selection change.
- L77 _private member_ `TSharedPtr<FTmvMediaTranscodeListHandle> ListHandle;` — Handle to the currently opened Transcode List.
- L80 _private member_ `TArray<int32> CurrentSelection;` — Currently selected Job Item Indices (in the job list) that is reflected by this detail view.
- L83 _private member_ `TSharedPtr<FScopedTransaction> CurrentTransaction;` — Current property editing transaction (from any of the details view).
- L86 _private member_ `bool bIgnoreModifiedItemEvents = false;` — Flag indicating the modified items events are coming from the detail panel itself and should be ignored.
- L89 _private member_ `TSharedPtr<IStructureDetailsView> JobDetailsView;` — Holds the "Job Settings" details view.
- L92 _private member_ `TSharedPtr<IStructureDetailsView> EncoderDetailsView;` — Holds the "Encoder Options" details view.
- L95 _private member_ `TSharedPtr<SComboBox<const UScriptStruct*>> EncoderOptionsComboBox;` — Reference to Encoder Options ComboBox widget to propagate "refresh" events.
- L98 _private member_ `TArray<const UScriptStruct*> EncoderOptionsStructs;` — Cached list of the child ScriptStruct of EncoderOptions struct to the encoder options combo box.

### `Plugins/Media/TmvMedia/Source/TmvMediaEditor/Private/Widgets/TmvMediaEditorTranscodeUtils.h` (Private)


#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace TmvMediaEditor` (scope `UE`)
- L13 _namespace_ `namespace Transcode` (scope `UE::TmvMediaEditor`)
- L16 _prototype_ `TArray<const UScriptStruct*> GetAllDerivedStruct(const UScriptStruct* InBaseStruct);` (scope `UE::TmvMediaEditor::Transcode`) — Enumerate all the derived struct.
- L19 _prototype_ `TSharedPtr<IStructureDetailsView> CreateStructureDetailView(const TSharedPtr<IStructureDataProvider>& InStructProvider, FNotifyHook* InNotifyHook);` (scope `UE::TmvMediaEditor::Transcode`) — Helper function to create a struct detail view for transcode job details panel.

### `Plugins/Media/TmvMedia/Source/TmvMediaEditor/Private/Widgets/TmvMediaTranscodeListCommands.h` (Private)


#### class `FTmvMediaTranscodeListCommands`  
`class FTmvMediaTranscodeListCommands : public TCommands<FTmvMediaTranscodeListCommands>`  
_L10-38_
- inherits: `TCommands<FTmvMediaTranscodeListCommands>`
- desc: Set of Transcode List Editor Commands.
- L13 _public prototype_ `FTmvMediaTranscodeListCommands();`
- L16 _public prototype_ `virtual void RegisterCommands() override;` — Initialize commands
- L19 _public member_ `TSharedPtr<FUICommandInfo> CreateNewJobList;` — Create a new Transcode Job List.
- L22 _public member_ `TSharedPtr<FUICommandInfo> OpenJobList;` — Open a Transcode Job List from a new file or asset.
- L25 _public member_ `TSharedPtr<FUICommandInfo> LoadJobList;` — Load Transcode Job List from current file.
- L28 _public member_ `TSharedPtr<FUICommandInfo> SaveJobList;` — Save Transcode Job List to current file.
- L31 _public member_ `TSharedPtr<FUICommandInfo> SaveJobListAs;` — Save Transcode Job Lis to a new file (from browser).
- L34 _public member_ `TSharedPtr<FUICommandInfo> ImportJobItem;` — Import/Load selected item from specified file (from browser).
- L37 _public member_ `TSharedPtr<FUICommandInfo> ExportJobItem;` — Export/Save selected item to specified existing or new file.

### `Plugins/Media/TmvMedia/Source/TmvMediaEditor/Private/Widgets/TmvMediaTranscodeListHandle.h` (Private)


#### struct `FTmvMediaTranscodeListHandle`  
`struct FTmvMediaTranscodeListHandle : TSharedFromThis<FTmvMediaTranscodeListHandle>`  
_L17-83_
- inherits: `TSharedFromThis<FTmvMediaTranscodeListHandle>`
- desc: Keeps an indirect reference to the edited transcode list so it can be changed, on reload for instance, and avoid reconstructing all widgets. Note: In a MVC pattern, this object would be the "controller", but that word is already used for other concepts in UE so it is avoided. Using "handle" for now, might change later. As this is likely to be refactored into an asset editor, the post fix "editor" is typically used for what this class is.
- L20 _public function_ `bool IsValid() const` — Returns true if this handle has a valid reference to the edited transcode list.
- L26 _public function_ `UTmvMediaTranscodeList* Get() const` — Returns the edited transcode list.
- L32 _public function_ `TStrongObjectPtr<UTmvMediaTranscodeList> Pin() const` — Returns a strong reference to the edited transcode list.
- L38 _public prototype_ `void SetTranscodeList(UTmvMediaTranscodeList* InTranscodeList);` — Assigned a new transcode list object to this handle. This will broadcast OnListChanged event for widgets to update.
- L41 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnListChanged, UTmvMediaTranscodeList* , UTmvMediaTranscodeList* );` — Multicast Delegate called when the transcode list object is changed.
- L42 _public function_ `FOnListChanged& GetOnTranscodeListChanged()`
- L48 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnSelectionChanged, const UTmvMediaTranscodeList*, TConstArrayView<int32> );` — Multicast Delegate called when the JobItem Selection changes.
- L49 _public function_ `FOnSelectionChanged& GetOnSelectionChanged()`
- L55 _public prototype_ `DECLARE_DELEGATE_RetVal(TArray<int32>, FOnGetCurrentSelection) FOnGetCurrentSelection OnGetCurrentSelectionDelegate;` — Delegate implemented by the job list widget to query the current selection.
- L59 _public function_ `TArray<int32> GetCurrentSelection() const` — Returns currently selected job items in the list view.
- L65 _public prototype_ `DECLARE_DELEGATE_RetVal(int32, FOnGetNumSelected) FOnGetNumSelected OnGetNumSelectedDelegate;` — Delegate implemented by the job list widget to query the current number of selected items.
- L69 _public function_ `int32 GetNumSelected() const` — Returns number of currently selected job items in the list view.
- L76 _private member_ `TWeakObjectPtr<UTmvMediaTranscodeList> TranscodeListWeak;` — This handle keeps a weak pointer to the edited transcode list. The owner should be the top level parent widget.
- L79 _private member_ `FOnListChanged OnListChanged;` — OnListChanged Delegate.
- L82 _private member_ `FOnSelectionChanged OnSelectionChanged;` — OnSelectionChanged Delegate.

#### Free symbols / members of external scopes

- L41 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnListChanged, UTmvMediaTranscodeList* , UTmvMediaTranscodeList* );` — Multicast Delegate called when the transcode list object is changed.
- L48 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnSelectionChanged, const UTmvMediaTranscodeList*, TConstArrayView<int32> );` — Multicast Delegate called when the JobItem Selection changes.
- L55 _delegate_ `DECLARE_DELEGATE_RetVal(TArray<int32>, FOnGetCurrentSelection) FOnGetCurrentSelection OnGetCurrentSelectionDelegate;` — Delegate implemented by the job list widget to query the current selection.
- L65 _delegate_ `DECLARE_DELEGATE_RetVal(int32, FOnGetNumSelected) FOnGetNumSelected OnGetNumSelectedDelegate;` — Delegate implemented by the job list widget to query the current number of selected items.

### `Plugins/Media/TmvMedia/Source/TmvMediaEditor/Private/Widgets/TmvMediaTranscodeNotification.h` (Private)


#### class `FTmvMediaTranscodeNotification`  
`class FTmvMediaTranscodeNotification : public ITmvMediaTranscodeNotification`  
_L16-70_
- inherits: `ITmvMediaTranscodeNotification`
- desc: Implementation of a transcode notification using SNotificationItem. This class is not meant to be used directly, but rather, wrapped by another object that will make sure the functions are called from the main thread.
- L19 _public function_ `FTmvMediaTranscodeNotification()`
- L27 _public function_ `virtual ~FTmvMediaTranscodeNotification() override`
- L37 _public function_ `virtual void SetText(const FText& InText) override`
- L45 _public function_ `virtual void Close(bool bInSuccess) override`
- L53 _private function_ `void CloseImpl(bool bInSuccess)` — Closes the notification.
- L69 _private member_ `TSharedPtr<SNotificationItem> NotificationItem;`

#### class `FTmvMediaTranscodeNotificationWrapper`  
`class FTmvMediaTranscodeNotificationWrapper : public ITmvMediaTranscodeNotification`  
_L76-142_
- inherits: `ITmvMediaTranscodeNotification`
- desc: Transcode Notification implementation that takes a shared ptr to another implementation and makes sure that the functions are called in the main thread.
- L79 _public function_ `FTmvMediaTranscodeNotificationWrapper(const TSharedPtr<ITmvMediaTranscodeNotification>& InInternal) : Internal(InInternal)`
- L83 _public function_ `virtual ~FTmvMediaTranscodeNotificationWrapper() override`
- L96 _public function_ `virtual void SetText(const FText& InText) override`
- L110 _public function_ `virtual void Close(bool bInSuccess) override`
- L128 _private function_ `template <typename CallableType> void ExecuteOnGameThread(CallableType&& Callable)` — Call a callable on the game thread.
- L141 _private member_ `TSharedPtr<ITmvMediaTranscodeNotification> Internal;` — Internal object that implements the functions that must be called from the main thread.

#### class `FTmvMediaTranscodeNotificationSafe`  
`class FTmvMediaTranscodeNotificationSafe : public FTmvMediaTranscodeNotificationWrapper`  
_L144-150_
- inherits: `FTmvMediaTranscodeNotificationWrapper`
- L147 _public function_ `FTmvMediaTranscodeNotificationSafe() : FTmvMediaTranscodeNotificationWrapper(MakeShared<FTmvMediaTranscodeNotification>())`

#### Free symbols / members of external scopes

- L89 _function_ `` (scope `FTmvMediaTranscodeNotificationWrapper::~FTmvMediaTranscodeNotificationWrapper`)
- L101 _function_ `` (scope `FTmvMediaTranscodeNotificationWrapper::SetText`)
- L115 _function_ `` (scope `FTmvMediaTranscodeNotificationWrapper::Close`)

### `Plugins/Media/TmvMedia/Source/TmvMediaEditor/Private/Widgets/TmvMediaTranscodeTaskMakeMediaSource.h` (Private)


#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace TmvMediaEditor` (scope `UE`)
- L9 _namespace_ `namespace TranscodeTask` (scope `UE::TmvMediaEditor`)
- L15 _prototype_ `void AddMakeOrUpdateMediaSourceTask(UTmvMediaTranscodeJob* InTranscodeJob);` (scope `UE::TmvMediaEditor::TranscodeTask`) — Adds a task that will create/update a MediaSource asset for the output sequence when the job is finished. @param InTranscodeJob Transcode job to add the task to.
