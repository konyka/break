# Plugins / ChangelistReview

- module root: `Plugins/Editor/ChangelistReview/Source`
- headers: 4; symbols: 214
- symbol kinds: class=5, delegate=2, enum=3, enumerator=11, function=6, macro=1, member=58, namespace=2, prototype=113, struct=4, typedef=6, variable=3
- PrivateDependencyModuleNames: EditorFramework, EditorStyle, HTTP, InputCore, Json, Kismet, Slate, SlateCore, SourceControl, ToolMenus, UnrealEd
- PublicDependencyModuleNames: Core, CoreUObject, Engine

### `Plugins/Editor/ChangelistReview/Source/Private/FSwarmCommentsAPI.h` (Private)


#### class `FSwarmUserdataComment`  
`class FSwarmUserdataComment`  
_L7-24_
- desc: helper class that stores likes and Read comments as an archived comment in a review
- L10 _public prototype_ `FSwarmUserdataComment(FString User, FReviewTopic Topic);`
- L11 _public prototype_ `FSwarmUserdataComment(const FReviewComment& InUserDataComment);`
- L12 _public prototype_ `operator FReviewComment&();`
- L13 _public prototype_ `bool ReflectCommentLikes(const FReviewComment& ReviewComment);`
- L14 _public prototype_ `bool ReflectCommentReads(const FReviewComment& ReviewComment);`
- L15 _public prototype_ `TSet<FString> GetLikedComments() const;`
- L16 _public prototype_ `TSet<FString> GetReadComments() const;`
- L18 _public prototype_ `static bool IsUserdataComment(const FReviewComment& Comment);`
- L21 _private prototype_ `bool ToggleSetItem(const FString& SetName, const FString& SetKey, EUserdataSetToggleVal ToggleVal);`
- L22 _private member_ `FReviewComment UserDataComment;`
- L23 _private member_ `TMap<FString,FString> DataMap;`

#### enum `FSwarmUserdataComment::EUserdataSetToggleVal`  
`enum class EUserdataSetToggleVal`  
_L20-20_
- L20 _public enumerator_ `enum class EUserdataSetToggleVal { ToggleSet, ToggleUnset }; bool ToggleSetItem(const FString& SetName, const FString& SetKey, EUserdataSetToggleVal ToggleVal); FReviewComment UserDataComment; TMap<FString`
- L20 _public enumerator_ `enum class EUserdataSetToggleVal { ToggleSet, ToggleUnset }; bool ToggleSetItem(const FString& SetName, const FString& SetKey, EUserdataSetToggleVal ToggleVal); FReviewComment UserDataComment; TMap<FString`

#### class `FSwarmCommentsAPI`  
`class FSwarmCommentsAPI : public IReviewCommentAPI`  
_L26-89_
- inherits: `IReviewCommentAPI`
- L31 _public prototype_ `FSwarmCommentsAPI(const FString& AuthTicket, const FString& SwarmURL);` — prefer TryConnect over calling constructor directly
- L32 _public prototype_ `FSwarmCommentsAPI(const FAuthTicket& AuthTicket, const FString& SwarmURL);`
- L33 _public prototype_ `static TSharedPtr<FSwarmCommentsAPI> TryConnect();`
- L35 _public prototype_ `virtual FString GetUsername() const override;`
- L37 _public prototype_ `virtual void GetComments(const FReviewTopic& Topic, const OnGetCommentsComplete& OnComplete) const override;`
- L39 _public prototype_ `virtual void PostComment(FReviewComment& Comment, const OnPostCommentComplete& OnComplete, bool bSilenceNotification = false) const override;` — Body must be set
- L41 _public prototype_ `virtual void EditComment(const FReviewComment& Comment, const OnEditCommentComplete& OnComplete, bool bSilenceNotification = false) const override;` — all unset members will be left unchanged.
- L44 _public prototype_ `virtual void GetReviewTopicForCL(const FString &ChangelistNum, const OnGetReviewTopicForCLComplete& OnComplete) const override;` — retrieves the review associated with a CL.
- L47 _public prototype_ `virtual void GetOrCreateReviewTopicForCL(const FString& ChangelistNum, const OnGetReviewTopicForCLComplete& OnComplete) const override;` — retrieves the review associated with a CL. If there is none, it creates a new review and returns that.
- L51 _private prototype_ `void CreateReviewTopicForCL(const FString &ChangelistNum, const OnGetReviewTopicForCLComplete& OnComplete) const;`
- L53 _private prototype_ `FString CommentsURL() const;`
- L54 _private prototype_ `FString ReviewsURL() const;`
- L56 _private prototype_ `DECLARE_DELEGATE_TwoParams(OnGetUserData, FSwarmUserdataComment*, const FString& ) void GetUserdata(const FReviewTopic& Topic, const OnGetUserData& OnComplete) const;`
- L58 _private prototype_ `void PostNewUserdataComment(const FReviewTopic& Topic) const;`
- L59 _private prototype_ `void UpdateUserdata(const FReviewComment& ReviewComment) const;`
- L61 _private prototype_ `TWeakPtr<const FSwarmCommentsAPI> AsWeak() const;`
- L62 _private prototype_ `TWeakPtr<FSwarmCommentsAPI> AsWeak();`
- L64 _private prototype_ `static void PutMetadataInBody(FReviewComment& Comment);`
- L65 _private prototype_ `static void TakeMetadataFromBody(FReviewComment& Comment);`
- L67 _private prototype_ `static FAuthTicket RetrieveAuthorizationTicket();`
- L68 _private prototype_ `static FString RetrieveSwarmURL(const FString& Username);`
- L81 _private member_ `} AuthTicket;`
- L84 _private member_ `FString SwarmURL;` — base url for all swarm api requests
- L88 _private member_ `mutable TMap<FReviewTopic, FSwarmUserdataComment> UserdataCache;` — maps user to the comment that stores the users data like their likes and views this is necessary because the swarm api unfortunately has incomplete support for updating like and view state

#### struct `FSwarmCommentsAPI::FAuthTicket`  
`struct FAuthTicket`  
_L71-81_
- desc: used to authorize http requests to swarm
- L73 _public prototype_ `FAuthTicket() = default;`
- L74 _public prototype_ `FAuthTicket(const FString& Username, const FString& Password);`
- L75 _public prototype_ `FAuthTicket(FStringView TicketString);`
- L76 _public prototype_ `operator FString() const;`
- L77 _public prototype_ `bool IsValid() const;`
- L78 _public member_ `FString Username;`
- L80 _private member_ `FString Password;`

#### Free symbols / members of external scopes

- L56 _delegate_ `DECLARE_DELEGATE_TwoParams(OnGetUserData, FSwarmUserdataComment*, const FString& ) void GetUserdata(const FReviewTopic& Topic, const OnGetUserData& OnComplete) const;`

### `Plugins/Editor/ChangelistReview/Source/Private/SSourceControlReviewEntry.h` (Private)


#### class `SSourceControlReviewEntry`  
`class SSourceControlReviewEntry : public SMultiColumnTableRow<TSharedPtr<SourceControlReview::FChangelistFileData>>`  
_L15-148_
- inherits: `SMultiColumnTableRow<TSharedPtr<SourceControlReview::FChangelistFileData>>`
- L18 _public typedef_ `using ESourceControlAction = SourceControlReview::ESourceControlAction;`
- L19 _public typedef_ `using EChangelistState = SourceControlReview::EChangelistState;`
- L20 _public typedef_ `using FChangelistFileData = SourceControlReview::FChangelistFileData;`
- L22 _public function_ `SLATE_BEGIN_ARGS(SSourceControlReviewEntry)`
- L23 _public prototype_ `SLATE_ARGUMENT(FChangelistFileData, FileData);`
- L24 _public prototype_ `SLATE_ARGUMENT(TWeakPtr<IReviewCommentAPI>, CommentsAPI);`
- L25 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTableView);`
- L30 _public prototype_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& ColumnName) override;`
- L36 _public prototype_ `void SetEntryData(const FChangelistFileData& InChangelistFileData);` — Sets needed data to show diff and browse to asset @param InChangelistFileData changelist entry information
- L42 _private prototype_ `FReply OnDiffClicked() const;` — Hooks into built in engine diff functionality to show differences between supplied file revisions
- L47 _private prototype_ `FReply OnBrowseToAssetClicked() const;` — Uses engine sync to browse to asset functionality to navigate the content window to file
- L52 _private prototype_ `FText GetBrowseToAssetTooltip() const;` — Uses engine sync to browse to asset functionality to navigate the content window to file
- L57 _private prototype_ `bool CanBrowseToAsset() const;` — Checks if we have a valid local file for this entry to sync content window to
- L62 _private prototype_ `void TryBindDiffMethod();` — if this file is diffable, bind the diff method to this->DiffMethod
- L67 _private prototype_ `bool CanDiff() const;` — Checks if this asset is diffable
- L72 _private prototype_ `void TryBindUAssetDiff();` — Runs logic to do the diff for UAsset objects
- L77 _private prototype_ `void TryBindTextDiff();` — Runs logic to do the diff for text based objects
- L82 _private prototype_ `FRevisionInfo GetReviewFileRevisionInfo() const;` — Gets revision information for review file
- L87 _private prototype_ `FRevisionInfo GetPreviousFileRevisionInfo() const;` — Gets revision information for previous file (Currently Limited to only revision num)
- L92 _private prototype_ `const FSlateBrush* GetSourceControlIcon() const;` — return an icon reflecting this entry's source control action (i.e. add, edit, delete, etc...)
- L97 _private prototype_ `FSlateColor GetSourceControlIconColor() const;` — return the color associated with this entry's source control action (i.e. add, edit, delete, etc...)
- L102 _private prototype_ `const FSlateBrush* GetAssetTypeIcon();` — return an icon that indicates the type of the asset being displayed
- L107 _private prototype_ `FText GetAssetType();` — return an icon that indicates the type of the asset being displayed
- L112 _private prototype_ `FText GetAssetNameText() const;` — Name of the asset being displayed
- L117 _private prototype_ `FText GetLocalAssetPathText() const;` — Path of the asset being displayed (relative to the changelist path)
- L119 _private prototype_ `const TArray<FReviewComment>* GetReviewComments() const;`
- L121 _private prototype_ `FString GetReviewerUsername() const;`
- L123 _private prototype_ `EVisibility GetUnreadCommentsIconVisibility() const;`
- L125 _private prototype_ `FText GetUnreadCommentsTooltip() const;`
- L130 _private prototype_ `const FString& GetSearchableString() const;` — Returns asset name to be used for search/filter
- L135 _private prototype_ `UBlueprint* GetOrCreateBlueprintForDiff(UClass* InGeneratedClass, EBlueprintType InBlueprintType) const;` — Gets or creates a new blueprint of the same class as file about to be diffed to be used for diffing class defaults when there is no previous revision
- L139 _private member_ `FChangelistFileData ChangelistFileData;` — File associated with this entry
- L140 _private member_ `TWeakPtr<IReviewCommentAPI> CommentsAPI;`
- L143 _private prototype_ `DECLARE_DELEGATE(FDiffMethod);` — Called to diff this file against it's previous revision
- L144 _private member_ `FDiffMethod DiffMethod;`
- L147 _private member_ `TSharedPtr<SImage> AssetTypeIcon;` — Sub-Widgets

#### Free symbols / members of external scopes

- L143 _delegate_ `DECLARE_DELEGATE(FDiffMethod);` — Called to diff this file against it's previous revision

### `Plugins/Editor/ChangelistReview/Source/Public/ChangelistReviewModule.h` (Public)


#### class `FChangelistReviewModule`  
`class FChangelistReviewModule : public FDefaultModuleImpl`  
_L17-44_
- inherits: `FDefaultModuleImpl`
- L20 _public prototype_ `virtual void StartupModule() override;`
- L21 _public prototype_ `virtual void ShutdownModule() override;`
- L22 _public prototype_ `void ShowReviewTab();`
- L23 _public prototype_ `bool CanShowReviewTab() const;`
- L24 _public prototype_ `TWeakPtr<SSourceControlReview> GetActiveReview();`
- L32 _public prototype_ `bool OpenChangelistReview(const FString& Changelist);` — Opens review tool and loads the provided change list. @param[in] Changelist The change list to load. @return @c true if changelist review tool was opened and change list is put to be loaded, @c false otherwise.
- L34 _public function_ `static FChangelistReviewModule& Get()`
- L39 _private prototype_ `TSharedRef<SDockTab> CreateReviewTab(const FSpawnTabArgs& Args);`
- L40 _private prototype_ `TSharedPtr<SWidget> CreateReviewUI();`
- L42 _private member_ `TWeakPtr<SDockTab> ReviewTab;`
- L43 _private member_ `TWeakPtr<SSourceControlReview> ReviewWidget;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API CHANGELISTREVIEW_API`

### `Plugins/Editor/ChangelistReview/Source/Public/SSourceControlReview.h` (Public)


#### enum `SourceControlReview::ESourceControlAction`  
`enum class ESourceControlAction : uint8`  
_L23-34_
- L25 _public enumerator_ `Add`
- L26 _public enumerator_ `Edit`
- L27 _public enumerator_ `Delete`
- L28 _public enumerator_ `Branch`
- L29 _public enumerator_ `Integrate`
- L30 _public enumerator_ `Unset`
- L33 _public enumerator_ `ActionCount` — keep this last

#### enum `SourceControlReview::EChangelistState`  
`enum class EChangelistState : uint8`  
_L36-40_
- L38 _public enumerator_ `Submitted`
- L39 _public enumerator_ `Pending`

#### struct `SourceControlReview::FChangelistFileData`  
`struct FChangelistFileData`  
_L42-100_
- L44 _public prototype_ `FChangelistFileData() = default;`
- L46 _public function_ `bool IsDataValidForEntry() const`
- L64 _public member_ `FString AssetName;`
- L67 _public member_ `FString ReviewFileTempPath;` — path where the temporary asset was downloaded to
- L69 _public member_ `FString ReviewFileRevisionNum;`
- L71 _public member_ `FDateTime ReviewFileDateTime;`
- L73 _public member_ `FString PreviousAssetName;`
- L76 _public member_ `FString PreviousFileTempPath;` — path where the temporary asset was downloaded to
- L78 _public member_ `FString PreviousFileRevisionNum;`
- L80 _public member_ `FDateTime PreviousFileDateTime;`
- L82 _public member_ `FString RelativeFilePath;`
- L84 _public member_ `FString AssetFilePath;`
- L86 _public member_ `FString AssetDepotPath;`
- L88 _public member_ `int32 ChangelistNum = INDEX_NONE;`
- L90 _public member_ `int32 PreviousChangelistNum = INDEX_NONE;`
- L92 _public member_ `EChangelistState ChangelistState = EChangelistState::Submitted;`
- L94 _public member_ `ESourceControlAction FileSourceControlAction = ESourceControlAction::Unset;`
- L96 _public prototype_ `const UClass* GetIconClass();`
- L99 _private member_ `TOptional<const UClass*> CachedIconClass;`

#### struct `SourceControlReview::FChangelistLightInfo`  
`struct FChangelistLightInfo`  
_L109-121_
- L111 _public function_ `explicit FChangelistLightInfo(const FText& Number) : Number(Number)`
- L114 _public function_ `FChangelistLightInfo(const FText& Number, const FText& Author, const FText& Description) : Number(Number), Author(Author), Description(Description)`
- L118 _public member_ `FText Number;`
- L119 _public member_ `FText Author;`
- L120 _public member_ `FText Description;`

#### class `SSourceControlReview`  
`class SSourceControlReview : public SCompoundWidget`  
_L128-306_
- inherits: `SCompoundWidget`
- desc: Used to select a changelist and diff it's changes
- L131 _public typedef_ `using ESourceControlAction = SourceControlReview::ESourceControlAction;`
- L132 _public typedef_ `using EChangelistState = SourceControlReview::EChangelistState;`
- L133 _public typedef_ `using FChangelistFileData = SourceControlReview::FChangelistFileData;`
- L135 _public function_ `SLATE_BEGIN_ARGS(SSourceControlReview)`
- L136 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L147 _public prototype_ `void LoadChangelist(const FString& Changelist);` — Pulls up changelist record from source control @param Changelist Changelist number to get
- L155 _public prototype_ `bool OpenChangelist(const FString& Changelist);` — Open changelist for review together with filling in the UI as if it was loaded for review by user. @param Changelist CL number to review @return @c true if changelist was open for review and is loaded, @c false otherwise.
- L162 _public prototype_ `const TArray<FReviewComment>* GetReviewCommentsForFile(const FString& FilePath);` — Returns an array of review comments that are @param FilePath the file to retrieve comments from. (supports AssetDepotPaths and temp local file paths)
- L165 _public prototype_ `void UpdateReviewComments();`
- L166 _public prototype_ `void PostComment(FReviewComment& Comment);`
- L167 _public prototype_ `void EditComment(FReviewComment& Comment);`
- L168 _public prototype_ `FString GetReviewerUsername() const;`
- L169 _public prototype_ `bool IsFileInReview(const FString& File) const;`
- L173 _private prototype_ `FString AsDepotPath(const FString& FilePath);`
- L178 _private prototype_ `void OnGetChangelistDetails(const FSourceControlOperationRef& InOperation, ECommandResult::Type InResult, FString Changelist);` — Called when FGetChangelistDetails completes
- L183 _private prototype_ `void OnGetReviewTopic(const FReviewTopic& Topic, const FString& ErrorMessage);` — Called when FSwarmCommentsAPI::GetReviewTopicForCL completes
- L188 _private prototype_ `void OnGetReviewComments(const TArray<FReviewComment>& Comments, const FString& ErrorMessage);` — Called when FSwarmCommentsAPI::OnGetReviewComments completes
- L189 _private prototype_ `void OnInitReviewComments(const TArray<FReviewComment>& Comments, const FString& ErrorMessage);`
- L195 _private prototype_ `void OnGetFileFromSourceControl(TSharedPtr<FChangelistFileData> ChangelistFileData);` — Called when file is retrieved from source control @param ChangelistFileData carried through worker to be filled with information about retrieved file from source control
- L200 _private prototype_ `void OnLoadComplete();` — Called when changelist details, changelist files, and changelist review info has all been retrieved
- L202 _private prototype_ `FReply OnLoadChangelistClicked();`
- L203 _private prototype_ `bool IsSourceControlActive() const;`
- L204 _private prototype_ `FText LoadChangelistTooltip() const;`
- L205 _private prototype_ `void OnChangelistNumChanged(const FText& Text);`
- L206 _private prototype_ `void OnChangelistNumCommitted(const FText& Text, ETextCommit::Type CommitMethod);`
- L208 _private prototype_ `FReply OnEnableCommentsButtonClicked();`
- L209 _private prototype_ `EVisibility EnableCommentsButtonVisibility() const;`
- L211 _private prototype_ `TSharedRef<SWidget> MakeCLComboOption(TSharedPtr<SourceControlReview::FChangelistLightInfo>Item) const;`
- L212 _private prototype_ `void OnCLComboSelection(TSharedPtr<SourceControlReview::FChangelistLightInfo> Item, ESelectInfo::Type SelectInfo) const;`
- L213 _private prototype_ `void SaveCLHistory();`
- L214 _private prototype_ `void LoadCLHistory();`
- L220 _private prototype_ `void SetLoading(bool bInLoading);` — Sets bChangelistLoading and then fires the BP_SetLoading event @param bInLoading when true flips visibility on loading bar and is also blocking from loading multiple changelists at the same time until loading is finished
- L225 _private prototype_ `bool IsLoading() const;` — True if the tool is currently loading a changelist
- L231 _private prototype_ `bool IsChangelistRecordValid(const TArray<TMap<FString, FString>>& InRecord) const;` — Checks changelist information to make sure it's valid for the diff tool @param InRecord changelist record
- L238 _private prototype_ `static void SetFileSourceControlAction(TSharedPtr<FChangelistFileData> ChangelistFileData, const FString& SourceControlAction);` — Sets the source control action type for the loaded file @param ChangelistFileData carried through worker to be filled with information about retrieved file from source control @param SourceControlAction source action operation type retrieved from source control
- L244 _private prototype_ `void SetChangelistInfo(const TMap<FString, FString>& InChangelistRecord, const FString& ChangelistNum);` — Sets changelist information Author, Description, Status and Depot name that changelist is going to
- L246 _private prototype_ `TSharedRef<ITableRow> OnGenerateFileRow(TSharedPtr<FChangelistFileData> FileData, const TSharedRef<STableViewBase>& Table) const;`
- L251 _private prototype_ `FString TrimSharedPath(FString FullCLPath) const;` — Removes CurrentChangelistInfo.SharedPath from the beginning of FullCLPath
- L253 _private prototype_ `void FixupRedirectors();`
- L255 _private prototype_ `static SHeaderRow::FColumn::FArguments HeaderColumn(FName HeaderName);`
- L260 _private prototype_ `static FString AsAssetPath(const FString& FullCLPath);` — Removes the game directory from the beginning of the FullCLPath
- L263 _private prototype_ `void CommitTempChangelistNumToHistory();` — helper function that sets bUncommittedChangelistNum to false and upgrades CLHistory[0] from a entry to an official one
- L266 _private prototype_ `void RemoveUncommittedChangelistNumFromHistory();` — helper function that sets bUncommittedChangelistNum to false and removes CLHistory[0] if it's uncommitted
- L269 _private member_ `bool bChangelistLoading = false;` — used for asynchronous changelist loading
- L271 _private prototype_ `void IncrementItemsLoaded();`
- L272 _private member_ `uint32 NumItemsToLoad = 0;` — counts the number of API calls (swarm, p4, etc) that need to be loaded.
- L273 _private member_ `uint32 NumItemsLoaded = 0;` — counts the number of API calls (swarm, p4, etc) that have been loaded
- L274 _private member_ `TArray<TSharedPtr<FChangelistFileData>> ChangelistFiles;`
- L275 _private member_ `TSharedPtr<FGetChangelistDetails> GetChangelistDetailsCommand;`
- L276 _private member_ `TArray<TSharedPtr<SourceControlReview::FChangelistLightInfo>> CLHistory;`
- L277 _private member_ `bool bUncommittedChangelistNum = false;`
- L279 _private member_ `TSharedPtr<SComboBox<TSharedPtr<SourceControlReview::FChangelistLightInfo>>> ChangelistNumComboBox;`
- L280 _private member_ `TSharedPtr<SEditableText> ChangelistNumText;`
- L281 _private member_ `TSharedPtr<STextBlock> EnterChangelistTextBlock;`
- L282 _private member_ `TSharedPtr<STextBlock> LoadingTextBlock;`
- L283 _private member_ `TSharedPtr<SProgressBar> LoadingProgressBar;`
- L284 _private member_ `TSharedPtr<SWidget> ChangelistInfoWidget;`
- L285 _private member_ `TSharedPtr<SListView<TSharedPtr<FChangelistFileData>>> ChangelistEntriesWidget;`
- L295 _private member_ `} CurrentChangelistInfo;`
- L297 _private member_ `TSharedPtr<IReviewCommentAPI> CommentsAPI;`
- L298 _private member_ `TOptional<FReviewTopic> ReviewTopic;`
- L300 _private member_ `TArray<FReviewComment> GlobalReviewComments;` — review comments that aren't attached to a specific file
- L302 _private member_ `TMap<FString, TArray<FReviewComment>> FileReviewComments;` — review comments mapped by the file they're attached to (keyed by both repository path and temp local path)
- L303 _private member_ `bool bReviewCommentsDirty = false;`
- L305 _private member_ `TMap<FString, FString> TempLocalPathToDepotPath;`

#### struct `SSourceControlReview::FChangelistInfo`  
`struct FChangelistInfo`  
_L288-295_
- desc: Info about the current chagnelist
- L290 _public member_ `FText Author;`
- L291 _public member_ `FText SharedPath;`
- L292 _public member_ `FText Status;`
- L293 _public member_ `FText Description;`
- L294 _public member_ `FString ChangelistNum;`

#### Free symbols / members of external scopes

- L21 _namespace_ `namespace SourceControlReview`
- L102 _namespace_ `namespace ColumnIds` (scope `SourceControlReview`)
- L104 _variable_ `inline const FName Status = TEXT("Sta` (scope `SourceControlReview::ColumnIds`)
- L105 _variable_ `inline const FName File = TEXT("Fil` (scope `SourceControlReview::ColumnIds`)
- L106 _variable_ `inline const FName Tools = TEXT("Too` (scope `SourceControlReview::ColumnIds`)
