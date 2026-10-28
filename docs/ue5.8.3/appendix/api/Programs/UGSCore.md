# Programs / UGSCore

- module root: `Source/Programs/UGSCore`
- headers: 15; symbols: 772
- symbol kinds: class=20, delegate=1, enum=12, enumerator=67, function=2, member=288, namespace=15, prototype=337, struct=29, typedef=1
- PrivateDependencyModuleNames: Core, Json
- PublicDependencyModuleNames: Core

### `Source/Programs/UGSCore/BuildStep.h` (Other)


#### enum `UGSCore::EBuildStepType`  
`enum class EBuildStepType`  
_L12-17_
- L14 _public enumerator_ `Compile`
- L15 _public enumerator_ `Cook`
- L16 _public enumerator_ `Other`

#### struct `UGSCore::FBuildStep`  
`struct FBuildStep`  
_L22-49_
- L24 _public member_ `static const TCHAR* UniqueIdKey;`
- L26 _public member_ `FGuid UniqueId;`
- L27 _public member_ `int OrderIndex;`
- L28 _public member_ `FString Description;`
- L29 _public member_ `FString StatusText;`
- L30 _public member_ `int EstimatedDuration;`
- L31 _public member_ `EBuildStepType Type;`
- L32 _public member_ `FString Target;`
- L33 _public member_ `FString Platform;`
- L34 _public member_ `FString Configuration;`
- L35 _public member_ `FString FileName;`
- L36 _public member_ `FString Arguments;`
- L37 _public member_ `bool bUseLogWindow;`
- L38 _public member_ `bool bNormalSync;`
- L39 _public member_ `bool bScheduledSync;`
- L40 _public member_ `bool bShowAsTool;`
- L42 _public prototype_ `FBuildStep(const FGuid& InUniqueId, int InOrderIndex, const FString& InDescription, const FString& InStatusText, int InEstimatedDuration, const FString& InTarget, const FString& InPlatform, const FString& InConfiguration, const FString& InArguments, bool bInSyncDefault);`
- L43 _public prototype_ `FBuildStep(const FCustomConfigObject& Object);`
- L45 _public prototype_ `static void MergeBuildStepObjects(TMap<FGuid, FCustomConfigObject>& BuildStepObjects, const TArray<FCustomConfigObject>& ModifyObjects);`
- L47 _public prototype_ `FCustomConfigObject ToConfigObject() const;`
- L48 _public prototype_ `FCustomConfigObject ToConfigObject(const FCustomConfigObject* DefaultObject) const;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UGSCore`
- L19 _prototype_ `bool TryParse(const TCHAR* Text, EBuildStepType& OutType);` (scope `UGSCore`)
- L20 _prototype_ `const TCHAR* ToString(EBuildStepType Type);` (scope `UGSCore`)

### `Source/Programs/UGSCore/CreateClientTask.h` (Other)


#### class `UGSCore::FCreateClientTask`  
`class FCreateClientTask : public IModalTask`  
_L13-34_
- inherits: `IModalTask`
- L16 _public member_ `TSharedRef<FPerforceConnection> Perforce;`
- L18 _public prototype_ `FCreateClientTask( TSharedRef<FPerforceConnection> InPerforce, TSharedRef<FLineBasedTextWriter> InLog, const FPerforceClientRecord& InClientRecord, const FString& InStream);`
- L25 _public prototype_ `virtual TSharedRef<FModalTaskResult> Run(FEvent* AbortEvent) override;`
- L28 _private member_ `TSharedRef<FLineBasedTextWriter> Log;`
- L30 _private member_ `const FPerforceClientRecord& ClientRecord;`
- L31 _private member_ `const FString& Stream;`
- L33 _private prototype_ `TSharedRef<FModalTaskResult> RunInternal(FEvent* AbortEvent) const;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UGSCore`

### `Source/Programs/UGSCore/CustomConfigFile.h` (Other)


#### struct `UGSCore::FCustomConfigObject`  
`struct FCustomConfigObject`  
_L12-47_
- L14 _public member_ `TArray<TTuple<FString, FString>> Pairs;`
- L16 _public prototype_ `FCustomConfigObject();`
- L17 _public prototype_ `FCustomConfigObject(const TCHAR* Text);`
- L18 _public prototype_ `FCustomConfigObject(const FCustomConfigObject& BaseObject, const TCHAR* Text);`
- L20 _public prototype_ `void ParseConfigString(const TCHAR* Text);`
- L21 _public prototype_ `FString ParseConfigToken(const TCHAR* Text, int& Idx);`
- L23 _public prototype_ `bool HasKey(const TCHAR* Key) const;`
- L24 _public prototype_ `bool HasValue(const TCHAR* Key, const TCHAR* Value) const;`
- L26 _public prototype_ `bool TryGetValue(const TCHAR* Key, const TCHAR*& OutValue) const;`
- L27 _public prototype_ `bool TryGetValue(const TCHAR* Key, FString& OutValue) const;`
- L28 _public prototype_ `bool TryGetValue(const TCHAR* Key, FGuid& OutValue) const;`
- L29 _public prototype_ `bool TryGetValue(const TCHAR* Key, int& OutValue) const;`
- L30 _public prototype_ `bool TryGetValue(const TCHAR* Key, bool& OutValue) const;`
- L32 _public prototype_ `const TCHAR* GetValueOrDefault(const TCHAR* Key, const TCHAR* DefaultValue) const;`
- L33 _public prototype_ `FGuid GetValueOrDefault(const TCHAR* Key, const FGuid& DefaultValue) const;`
- L34 _public prototype_ `int GetValueOrDefault(const TCHAR* Key, int DefaultValue) const;`
- L35 _public prototype_ `bool GetValueOrDefault(const TCHAR* Key, bool DefaultValue) const;`
- L37 _public prototype_ `void SetValue(const TCHAR* Key, const TCHAR* Value);`
- L38 _public prototype_ `void SetValue(const TCHAR* Key, const FGuid& Value);`
- L39 _public prototype_ `void SetValue(const TCHAR* Key, int Value);`
- L40 _public prototype_ `void SetValue(const TCHAR* Key, bool Value);`
- L42 _public prototype_ `void SetDefaults(const FCustomConfigObject& Other);`
- L43 _public prototype_ `void AddOverrides(const FCustomConfigObject& Object, const FCustomConfigObject* DefaultObject);`
- L45 _public prototype_ `FString ToString(const FCustomConfigObject* BaseObject) const;`
- L46 _public prototype_ `FString ToString() const;`

#### struct `UGSCore::FCustomConfigSection`  
`struct FCustomConfigSection`  
_L49-73_
- L51 _public member_ `const FString Name;`
- L52 _public member_ `TMap<FString, FString> Pairs;`
- L54 _public prototype_ `FCustomConfigSection(FString&& InName);`
- L55 _public prototype_ `void Clear();`
- L56 _public prototype_ `void SetValue(const TCHAR* Key, int Value);`
- L57 _public prototype_ `void SetValue(const TCHAR* Key, bool Value);`
- L58 _public prototype_ `void SetValue(const TCHAR* Key, const TCHAR* Value);`
- L59 _public prototype_ `void SetValues(const TCHAR* Key, const TArray<FString>& Values);`
- L60 _public prototype_ `void SetValues(const TCHAR* Key, const TArray<FGuid>& Values);`
- L61 _public prototype_ `void SetValues(const TCHAR* Key, const TArray<int>& Values);`
- L62 _public prototype_ `void AppendValue(const TCHAR* Key, const TCHAR* Value);`
- L63 _public prototype_ `void RemoveValue(const TCHAR* Key);`
- L64 _public prototype_ `int GetValue(const TCHAR* Key, int DefaultValue) const;`
- L65 _public prototype_ `bool GetValue(const TCHAR* Key, bool DefaultValue) const;`
- L66 _public prototype_ `const TCHAR* GetValue(const TCHAR* Key, const TCHAR* DefaultValue = nullptr) const;`
- L68 _public prototype_ `bool TryGetValue(const TCHAR* Key, FString& OutValue) const;`
- L69 _public prototype_ `bool TryGetValue(const TCHAR* Key, int32& OutValue) const;`
- L70 _public prototype_ `bool TryGetValues(const TCHAR* Key, TArray<FString>& Values) const;`
- L71 _public prototype_ `bool TryGetValues(const TCHAR* Key, TArray<FGuid>& Values) const;`
- L72 _public prototype_ `bool TryGetValues(const TCHAR* Key, TArray<int>& Values) const;`

#### struct `UGSCore::FCustomConfigFile`  
`struct FCustomConfigFile`  
_L75-101_
- L77 _public member_ `TArray<TSharedPtr<FCustomConfigSection>> Sections;`
- L79 _public prototype_ `FCustomConfigFile();`
- L80 _public prototype_ `void Load(const TCHAR* FileName);`
- L81 _public prototype_ `void Parse(const TArray<FString>& Lines);`
- L82 _public prototype_ `void Save(const TCHAR* FileName);`
- L83 _public prototype_ `TSharedPtr<FCustomConfigSection> FindSection(const TCHAR* Name);`
- L84 _public prototype_ `TSharedPtr<const FCustomConfigSection> FindSection(const TCHAR* Name) const;`
- L85 _public prototype_ `TSharedRef<FCustomConfigSection> FindOrAddSection(const TCHAR* Name);`
- L87 _public prototype_ `void SetValue(const TCHAR* Key, int Value);`
- L88 _public prototype_ `void SetValue(const TCHAR* Key, bool Value);`
- L89 _public prototype_ `void SetValue(const TCHAR* Key, const TCHAR* Value);`
- L91 _public prototype_ `void SetValues(const TCHAR* Key, const TArray<FString>& Values);`
- L93 _public prototype_ `bool GetValue(const TCHAR* Key, bool DefaultValue) const;`
- L94 _public prototype_ `int32 GetValue(const TCHAR* Key, int32 DefaultValue) const;`
- L95 _public prototype_ `const TCHAR* GetValue(const TCHAR* Key, const TCHAR* DefaultValue) const;`
- L97 _public prototype_ `bool TryGetValue(const TCHAR* Key, FString& OutValue) const;`
- L98 _public prototype_ `bool TryGetValue(const TCHAR* Key, int32& OutValue) const;`
- L99 _public prototype_ `bool TryGetValues(const TCHAR* Key, TArray<FString>& Values) const;`
- L100 _public prototype_ `bool TryGetValues(const TCHAR* Key, TArray<FGuid>& Value) const;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UGSCore`

### `Source/Programs/UGSCore/DetectProjectSettingsTask.h` (Other)


#### class `UGSCore::FDetectProjectSettingsTask`  
`class FDetectProjectSettingsTask : public IModalTask`  
_L13-39_
- inherits: `IModalTask`
- L16 _public member_ `const FString NewSelectedFileName;`
- L17 _public member_ `TSharedRef<FPerforceConnection> Perforce;`
- L18 _public member_ `TSharedPtr<FPerforceConnection> PerforceClient;`
- L19 _public member_ `FString NewSelectedProjectIdentifier;`
- L20 _public member_ `FString NewProjectEditorTarget;`
- L21 _public member_ `FString BranchClientPath;`
- L22 _public member_ `FString BranchDirectoryName;`
- L23 _public member_ `FString NewSelectedClientFileName;`
- L24 _public member_ `FString StreamName;`
- L26 _public member_ `FTimespan ServerTimeZone;` — public Image ProjectLogo;
- L29 _public prototype_ `FDetectProjectSettingsTask(TSharedRef<FPerforceConnection> InPerforce, const FString& InNewSelectedFileName, TSharedRef<FLineBasedTextWriter> InLog);`
- L30 _public prototype_ `~FDetectProjectSettingsTask();`
- L32 _public prototype_ `virtual TSharedRef<FModalTaskResult> Run(FEvent* AbortEvent) override;`
- L35 _private member_ `TSharedRef<FLineBasedTextWriter> Log;`
- L37 _private prototype_ `TSharedRef<FModalTaskResult> RunInternal(FEvent* AbortEvent);`
- L38 _private prototype_ `static bool TryGetStreamPrefix(TSharedRef<FPerforceConnection> Perforce, const FString& StreamName, FEvent* AbortEvent, FLineBasedTextWriter& Log, FString& OutStreamPrefix);`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UGSCore`

### `Source/Programs/UGSCore/EventMonitor.h` (Other)


#### enum `UGSCore::EEventType`  
`enum class EEventType`  
_L13-31_
- L15 _public enumerator_ `Syncing`
- L18 _public enumerator_ `Compiles` — Reviews
- L19 _public enumerator_ `DoesNotCompile`
- L20 _public enumerator_ `Good`
- L21 _public enumerator_ `Bad`
- L22 _public enumerator_ `Unknown`
- L25 _public enumerator_ `Starred` — Starred builds
- L26 _public enumerator_ `Unstarred`
- L29 _public enumerator_ `Investigating` — Investigating events
- L30 _public enumerator_ `Resolved`

#### struct `UGSCore::FEventData`  
`struct FEventData`  
_L33-43_
- L35 _public member_ `int64 Id;`
- L36 _public member_ `int32 ChangeNumber;`
- L37 _public member_ `FString UserName;`
- L38 _public member_ `EEventType Type;`
- L39 _public member_ `FString Project;`
- L41 _public prototype_ `FEventData(int32 InChangeNumber, const FString& InUserName, EEventType InType, const FString& InProject);`
- L42 _public prototype_ `FEventData(int64 InId, int32 InChangeNumber, const FString& InUserName, EEventType InType, const FString& InProject);`

#### struct `UGSCore::FCommentData`  
`struct FCommentData`  
_L45-55_
- L47 _public member_ `int64 Id;`
- L48 _public member_ `int32 ChangeNumber;`
- L49 _public member_ `FString UserName;`
- L50 _public member_ `FString Text;`
- L51 _public member_ `FString Project;`
- L53 _public prototype_ `FCommentData(int32 InChangeNumber, const FString& InUserName, const FString& InText, const FString& InProject);`
- L54 _public prototype_ `FCommentData(int64 InId, int32 InChangeNumber, const FString& InUserName, const FString& InText, const FString& InProject);`

#### enum `UGSCore::EBuildDataResult`  
`enum class EBuildDataResult`  
_L57-63_
- L59 _public enumerator_ `Starting`
- L60 _public enumerator_ `Failure`
- L61 _public enumerator_ `Warning`
- L62 _public enumerator_ `Success`

#### struct `UGSCore::FBuildData`  
`struct FBuildData`  
_L65-83_
- L67 _public member_ `long Id;`
- L68 _public member_ `int ChangeNumber;`
- L69 _public member_ `FString BuildType;`
- L70 _public member_ `EBuildDataResult Result;`
- L71 _public member_ `FString Url;`
- L72 _public member_ `FString Project;`
- L74 _public function_ `bool IsSuccess() const`
- L79 _public function_ `bool IsFailure() const`

#### enum `UGSCore::EReviewVerdict`  
`enum class EReviewVerdict`  
_L85-91_
- L87 _public enumerator_ `Unknown`
- L88 _public enumerator_ `Good`
- L89 _public enumerator_ `Bad`
- L90 _public enumerator_ `Mixed`

#### struct `UGSCore::FEventSummary`  
`struct FEventSummary`  
_L93-105_
- L95 _public member_ `int ChangeNumber;`
- L96 _public member_ `EReviewVerdict Verdict;`
- L97 _public member_ `TArray<TSharedRef<FEventData>> SyncEvents;`
- L98 _public member_ `TArray<TSharedRef<FEventData>> Reviews;`
- L99 _public member_ `TArray<FString> CurrentUsers;`
- L100 _public member_ `TSharedPtr<FEventData> LastStarReview;`
- L101 _public member_ `TArray<TSharedRef<FBuildData>> Builds;`
- L102 _public member_ `TArray<TSharedRef<FCommentData>> Comments;`
- L104 _public prototype_ `FEventSummary(int InChangeNumber);`

#### class `UGSCore::FEventMonitor`  
`class FEventMonitor : FRunnable`  
_L107-183_
- inherits: `FRunnable`
- L110 _public member_ `TFunction<void()> OnUpdatesReady;`
- L112 _public prototype_ `FEventMonitor(const FString& InSqlConnectionString, const FString& InProject, const FString& InCurrentUserName, const FString& InLogFileName);`
- L113 _public prototype_ `~FEventMonitor();`
- L115 _public prototype_ `void Start();`
- L116 _public prototype_ `void FilterChanges(const TArray<int>& ChangeNumbers);`
- L118 _public prototype_ `FString GetLastStatusMessage() const;`
- L120 _public prototype_ `void ApplyUpdates();`
- L121 _public prototype_ `void PostEvent(int ChangeNumber, EEventType Type);`
- L122 _public prototype_ `void PostComment(int ChangeNumber, const FString& Text);`
- L124 _public prototype_ `bool TryGetCommentByCurrentUser(int ChangeNumber, FString& OutCommentText) const;`
- L125 _public prototype_ `bool TryGetReviewByCurrentUser(int ChangeNumber, TSharedPtr<FEventData>& OutReview) const;`
- L126 _public prototype_ `bool TryGetSummaryForChange(int ChangeNumber, TSharedPtr<FEventSummary>& OutSummary) const;`
- L128 _public prototype_ `static bool IsReview(EEventType Type);`
- L129 _public prototype_ `static bool IsPositiveReview(EEventType Type);`
- L130 _public prototype_ `static bool IsNegativeReview(EEventType Type);`
- L132 _public prototype_ `bool WasSyncedByCurrentUser(int ChangeNumber) const;`
- L134 _public prototype_ `void StartInvestigating(int ChangeNumber);`
- L135 _public prototype_ `void FinishInvestigating(int ChangeNumber);`
- L136 _public prototype_ `bool IsUnderInvestigation(int ChangeNumber);`
- L137 _public prototype_ `bool IsUnderInvestigationByCurrentUser(int ChangeNumber);`
- L138 _public prototype_ `TArray<FString> GetInvestigatingUsers(int ChangeNumber);`
- L139 _public prototype_ `int GetInvestigationStartChangeNumber(int LastChangeNumber);`
- L142 _private member_ `const FString SqlConnectionString;`
- L143 _private member_ `const FString Project;`
- L144 _private member_ `const FString CurrentUserName;`
- L145 _private member_ `FRunnableThread* WorkerThread;`
- L146 _private member_ `mutable FCriticalSection CriticalSection;`
- L147 _private member_ `FEvent* RefreshEvent;`
- L148 _private member_ `TArray<TSharedRef<FEventData>> OutgoingEvents;`
- L149 _private member_ `TArray<TSharedRef<FEventData>> IncomingEvents;`
- L150 _private member_ `TArray<TSharedRef<FCommentData>> OutgoingComments;`
- L151 _private member_ `TArray<TSharedRef<FCommentData>> IncomingComments;`
- L152 _private member_ `TArray<TSharedRef<FBuildData>> IncomingBuilds;`
- L153 _private member_ `TMap<int, TSharedRef<FEventSummary>> ChangeNumberToSummary;`
- L154 _private member_ `TMap<FString, TSharedRef<FEventData>> UserNameToLastSyncEvent;`
- L155 _private member_ `FBoundedLogWriter LogWriter;`
- L156 _private member_ `long LastEventId;`
- L157 _private member_ `long LastCommentId;`
- L158 _private member_ `long LastBuildId;`
- L159 _private member_ `bool bDisposing;`
- L160 _private member_ `FString LastStatusMessage;`
- L161 _private member_ `TSet<int> FilterChangeNumbers;`
- L162 _private member_ `TArray<TSharedRef<FEventData>> InvestigationEvents;`
- L163 _private member_ `bool bUpdateActiveInvestigations;`
- L164 _private member_ `TArray<TSharedRef<FEventData>> ActiveInvestigations;`
- L166 _private prototype_ `TSharedRef<FEventSummary> FindOrAddSummary(int ChangeNumber);`
- L167 _private prototype_ `void ApplyEventUpdate(const TSharedRef<FEventData>& Event);`
- L168 _private prototype_ `void ApplyBuildUpdate(const TSharedRef<FBuildData>& Build);`
- L169 _private prototype_ `void ApplyCommentUpdate(const TSharedRef<FCommentData>& Comment);`
- L171 _private prototype_ `static EReviewVerdict GetVerdict(const TArray<TSharedRef<FEventData>>& Events, const TArray<TSharedRef<FBuildData>>& Builds);`
- L172 _private prototype_ `static EReviewVerdict GetVerdict(int NumPositive, int NumNegative);`
- L174 _private prototype_ `void ApplyFilteredUpdate(const TSharedRef<FEventData>& Event);`
- L175 _private prototype_ `uint32 Run();`
- L176 _private prototype_ `bool SendEventToBackend(const TSharedRef<FEventData>& Event);`
- L177 _private prototype_ `bool SendCommentToBackend(const TSharedRef<FCommentData>& Comment);`
- L178 _private prototype_ `bool ReadEventsFromBackend();`
- L180 _private prototype_ `static bool MatchesWildcard(const FString& Wildcard, const FString& Project);`
- L182 _private prototype_ `void UpdateActiveInvestigations();`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UGSCore`

### `Source/Programs/UGSCore/FileFilter.h` (Other)


#### enum `UGSCore::EFileFilterType`  
`enum class EFileFilterType`  
_L15-19_
- desc: <summary> Indicates whether files which match a pattern should be included or excluded </summary>
- L17 _public enumerator_ `Include`
- L18 _public enumerator_ `Exclude`

#### class `UGSCore::FFileFilter`  
`class FFileFilter`  
_L26-124_
- desc: <summary> Stores a set of rules, similar to p4 path specifications, which can be used to efficiently filter files in or out of a set. The rules are merged into a tree with nodes for each path fragments and rule numbers in each leaf, allowing tree traversal in an arbitrary order to how they are applied. </summary>
- L32 _public prototype_ `FFileFilter(EFileFilterType DefaultType = EFileFilterType::Exclude);` — <summary> Default constructor </summary>
- L38 _public prototype_ `FFileFilter(const FFileFilter& Other);` — <summary> Copy constructor </summary> <param name="Other">Filter to copy from</param>
- L44 _public prototype_ `FFileFilter(const TArray<FString>& Lines);` — <summary> Constructs a file filter from a p4-style filespec. Exclude lines are prefixed with a - character. </summary> <param name="Lines">Lines to parse rules from</param>
- L49 _public prototype_ `~FFileFilter();` — <summary> Destructor </summary>
- L57 _public prototype_ `void ReadRulesFromFile(const FString& FileName, const FString& SectionName);` — <summary> Reads a configuration file split into sections </summary> <param name="Filter"></param> <param name="RulesFileName"></param> <param name="Conditions"></param>
- L64 _public prototype_ `void AddRule(const FString& Pattern);` — <summary> Adds an include or exclude rule to the filter, treating anything with a '-' prefix as an exclude rule, and anything else as an include rule. </summary> <param name="Pattern">The pattern which the rule should match</param> <param name="bInclude">Whether to include or exclude files matching this rule</param>
- L71 _public prototype_ `void AddRule(const FString& Pattern, EFileFilterType Type);` — <summary> Adds an include or exclude rule to the filter </summary> <param name="Pattern">The pattern which the rule should match</param> <param name="bInclude">Whether to include or exclude files matching this rule</param>
- L78 _public prototype_ `bool Matches(const FString& FileName) const;` — <summary> Determines whether the given file matches the filter </summary> <param name="FileName">File to match</param> <returns>True if the file passes the filter</returns>
- L85 _public prototype_ `bool PossiblyMatches(const FString& FolderName) const;` — <summary> Determines whether it's possible for anything within the given folder name to match the filter. Useful to early out of recursive file searches. </summary> <param name="FolderName">File to match</param> <returns>True if the file passes the filter</returns>
- L93 _private member_ `FNode* RootNode;` — <summary> Root node for the tree. </summary>
- L98 _private member_ `FNode* DefaultNode;` — <summary> The default node, which will match any path </summary>
- L103 _private member_ `TArray<FNode*> Rules;` — <summary> Terminating nodes for each rule added to the filter </summary>
- L113 _private prototype_ `static const FNode* FindMatchingNode(const FNode* CurrentNode, const TArray<FString>& Tokens, int TokenIdx, const FNode* CurrentBestNode);` — <summary> Finds the node which matches a given list of tokens. </summary> <param name="CurrentNode"></param> <param name="Tokens"></param> <param name="TokenIdx"></param> <param name="CurrentBestNode"></param> <returns></returns>
- L123 _private prototype_ `static int HighestPossibleIncludeMatch(const FNode* CurrentNode, const TArray<FString>& Tokens, int TokenIdx, int CurrentBestRuleNumber);` — <summary> Returns the highest possible rule number which can match the given list of input tokens, assuming that the list of input tokens is incomplete. </summary> <param name="CurrentNode">The current node being checked</param> <param name="Tokens">The tokens to match</param> <param name="TokenIdx">Current token index</param> <param name="CurrentBestRuleNumber">The highest rule number seen so far. Used to optimize tree traversals.</param> <returns>New highest rule number</returns>

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UGSCore`

### `Source/Programs/UGSCore/FindStreamsTask.h` (Other)


#### class `UGSCore::FFindStreamsTask`  
`class FFindStreamsTask : public IModalTask`  
_L13-34_
- inherits: `IModalTask`
- L16 _public member_ `TSharedRef<FPerforceConnection> Perforce;`
- L18 _public prototype_ `FFindStreamsTask( TSharedRef<FPerforceConnection> InPerforce, TSharedRef<FLineBasedTextWriter> InLog, TArray<FString>& OutStreams, const FString& StreamFilter);`
- L25 _public prototype_ `virtual TSharedRef<FModalTaskResult> Run(FEvent* AbortEvent) override;`
- L28 _private member_ `TSharedRef<FLineBasedTextWriter> Log;`
- L30 _private member_ `TArray<FString>& Streams;`
- L31 _private member_ `FString Filter;`
- L33 _private prototype_ `TSharedRef<FModalTaskResult> RunInternal(FEvent* AbortEvent);`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UGSCore`

### `Source/Programs/UGSCore/ModalTask.h` (Other)


#### class `UGSCore::FModalTaskResult`  
`class FModalTaskResult`  
_L11-28_
- L14 _public prototype_ `FModalTaskResult(bool bSucceeded, const FText& Message);`
- L15 _public prototype_ `~FModalTaskResult();`
- L17 _public prototype_ `bool Succeeded() const;`
- L18 _public prototype_ `bool Failed() const;`
- L19 _public prototype_ `const FText& GetMessage() const;`
- L21 _public prototype_ `static TSharedRef<FModalTaskResult> Success();`
- L22 _public prototype_ `static TSharedRef<FModalTaskResult> Failure(const FText& Message);`
- L23 _public prototype_ `static TSharedRef<FModalTaskResult> Aborted();`
- L26 _private member_ `const bool bSucceeded;`
- L27 _private member_ `const FText Message;`

#### class `UGSCore::IModalTask`  
`class IModalTask`  
_L30-35_
- L33 _public prototype_ `virtual ~IModalTask();`
- L34 _public prototype_ `virtual TSharedRef<FModalTaskResult> Run(FEvent* AbortEvent) = 0;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UGSCore`

### `Source/Programs/UGSCore/OutputAdapters.h` (Other)


#### class `UGSCore::FLineBasedTextWriter`  
`class FLineBasedTextWriter : public FOutputDevice`  
_L10-22_
- inherits: `FOutputDevice`
- L13 _public prototype_ `FLineBasedTextWriter();`
- L14 _public prototype_ `virtual ~FLineBasedTextWriter();`
- L15 _public prototype_ `void Write(TCHAR Character);`
- L16 _public prototype_ `void WriteLine(const FString& Line);`
- L17 _public prototype_ `virtual void Serialize(const TCHAR* V, ELogVerbosity::Type Verbosity, const class FName& Category) override final;`
- L18 _public prototype_ `virtual void FlushLine(const FString& Line) = 0;`
- L21 _private member_ `FString CurrentLine;`

#### class `UGSCore::FNullTextWriter`  
`class FNullTextWriter : public FLineBasedTextWriter`  
_L24-28_
- inherits: `FLineBasedTextWriter`
- L27 _public prototype_ `virtual void FlushLine(const FString& Line) override;`

#### class `UGSCore::FBufferedTextWriter`  
`class FBufferedTextWriter : public FLineBasedTextWriter`  
_L30-44_
- inherits: `FLineBasedTextWriter`
- L33 _public prototype_ `FBufferedTextWriter();`
- L34 _public prototype_ `virtual ~FBufferedTextWriter();`
- L36 _public prototype_ `void Attach(const TSharedRef<FLineBasedTextWriter>& InInner);`
- L37 _public prototype_ `void Detach();`
- L39 _public prototype_ `virtual void FlushLine(const FString& Line) override;`
- L42 _private member_ `TArray<FString> BufferedLines;`
- L43 _private member_ `TSharedPtr<FLineBasedTextWriter> Inner;`

#### class `UGSCore::FPrefixedTextWriter`  
`class FPrefixedTextWriter : public FLineBasedTextWriter`  
_L46-56_
- inherits: `FLineBasedTextWriter`
- L49 _public prototype_ `FPrefixedTextWriter(const TCHAR* InPrefix, TSharedRef<FLineBasedTextWriter> InInner);`
- L51 _public prototype_ `virtual void FlushLine(const FString& Line) override;`
- L54 _private member_ `FString Prefix;`
- L55 _private member_ `TSharedRef<FLineBasedTextWriter> Inner;`

#### class `UGSCore::FBoundedLogWriter`  
`class FBoundedLogWriter : public FLineBasedTextWriter`  
_L58-73_
- inherits: `FLineBasedTextWriter`
- L61 _public prototype_ `FBoundedLogWriter(const TCHAR* InFileName, int32 InMaxSize);`
- L63 _public prototype_ `virtual void FlushLine(const FString& Line) override;`
- L66 _private member_ `FString FileName;`
- L67 _private member_ `FString BackupFileName;`
- L68 _private member_ `int32 MaxSize;`
- L69 _private member_ `FArchive* Inner;`
- L71 _private prototype_ `void OpenInner();`
- L72 _private prototype_ `void CloseInner();`

#### class `UGSCore::FComposedTextWriter`  
`class FComposedTextWriter : public FLineBasedTextWriter`  
_L75-84_
- inherits: `FLineBasedTextWriter`
- L78 _public prototype_ `FComposedTextWriter(const TArray<TSharedRef<FLineBasedTextWriter>>& InInners);`
- L80 _public prototype_ `virtual void FlushLine(const FString& Line) override;`
- L83 _private member_ `TArray<TSharedRef<FLineBasedTextWriter>> Inners;`

#### class `UGSCore::FProgressValue`  
`class FProgressValue`  
_L86-106_
- L89 _public prototype_ `FProgressValue();`
- L90 _public prototype_ `~FProgressValue();`
- L92 _public prototype_ `void Clear();`
- L93 _public prototype_ `TTuple<FString, float> GetCurrent() const;`
- L94 _public prototype_ `void Set(const TCHAR* Message);`
- L95 _public prototype_ `void Set(const TCHAR* Message, float Fraction);`
- L96 _public prototype_ `void Set(float Fraction);`
- L97 _public prototype_ `void Increment(float Fraction);`
- L98 _public prototype_ `void Push(float MaxFraction);`
- L99 _public prototype_ `void Pop();`
- L102 _private member_ `TTuple<FString, float> State;`
- L103 _private member_ `TArray<TTuple<float, float>> Ranges;`
- L105 _private prototype_ `float RelativeToAbsoluteFraction(float Fraction);`

#### class `UGSCore::FProgressTextWriter`  
`class FProgressTextWriter : public FLineBasedTextWriter`  
_L108-125_
- inherits: `FLineBasedTextWriter`
- L111 _public prototype_ `FProgressTextWriter(const FProgressValue& InValue, const TSharedRef<FLineBasedTextWriter>& InInner);`
- L114 _public prototype_ `virtual void FlushLine(const FString& Line) override;`
- L117 _private member_ `static const FString DirectivePrefix;`
- L119 _private member_ `FProgressValue Value;`
- L120 _private member_ `TSharedRef<FLineBasedTextWriter> Inner;`
- L122 _private prototype_ `void ProcessInternal(const FString& Line, bool& bSkipLine);`
- L123 _private prototype_ `static TArray<FString> ParseTokens(const FString& Line);`
- L124 _private prototype_ `static bool ReadFraction(const TArray<FString>& Tokens, int& TokenIdx, float& Fraction);`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UGSCore`

### `Source/Programs/UGSCore/Perforce.h` (Other)


#### struct `UGSCore::FPerforceChangeSummary`  
`struct FPerforceChangeSummary`  
_L13-22_
- L15 _public member_ `int Number;`
- L16 _public member_ `FDateTime Date;`
- L17 _public member_ `FString User;`
- L18 _public member_ `FString Client;`
- L19 _public member_ `FString Description;`
- L21 _public prototype_ `FPerforceChangeSummary();`

#### struct `UGSCore::FPerforceFileChangeSummary`  
`struct FPerforceFileChangeSummary`  
_L24-36_
- L26 _public member_ `int Revision;`
- L27 _public member_ `int ChangeNumber;`
- L28 _public member_ `FString Action;`
- L29 _public member_ `FDateTime Date;`
- L30 _public member_ `FString User;`
- L31 _public member_ `FString Client;`
- L32 _public member_ `FString Type;`
- L33 _public member_ `FString Description;`
- L35 _public prototype_ `FPerforceFileChangeSummary();`

#### struct `UGSCore::FPerforceClientRecord`  
`struct FPerforceClientRecord`  
_L38-46_
- L40 _public member_ `FString Name;`
- L41 _public member_ `FString Owner;`
- L42 _public member_ `FString Host;`
- L43 _public member_ `FString Root;`
- L45 _public prototype_ `FPerforceClientRecord(const TMap<FString, FString>& Tags);`

#### struct `UGSCore::FPerforceDescribeFileRecord`  
`struct FPerforceDescribeFileRecord`  
_L48-58_
- L50 _public member_ `FString DepotFile;`
- L51 _public member_ `FString Action;`
- L52 _public member_ `FString Type;`
- L53 _public member_ `int Revision;`
- L54 _public member_ `int FileSize;`
- L55 _public member_ `FString Digest;`
- L57 _public prototype_ `FPerforceDescribeFileRecord();`

#### struct `UGSCore::FPerforceDescribeRecord`  
`struct FPerforceDescribeRecord`  
_L60-73_
- L62 _public member_ `int ChangeNumber;`
- L63 _public member_ `FString User;`
- L64 _public member_ `FString Client;`
- L65 _public member_ `int64 Time;`
- L66 _public member_ `FString Description;`
- L67 _public member_ `FString Status;`
- L68 _public member_ `FString ChangeType;`
- L69 _public member_ `FString Path;`
- L70 _public member_ `TArray<FPerforceDescribeFileRecord> Files;`
- L72 _public prototype_ `FPerforceDescribeRecord(const TMap<FString, FString>& Tags);`

#### struct `UGSCore::FPerforceInfoRecord`  
`struct FPerforceInfoRecord`  
_L75-84_
- L77 _public member_ `FString UserName;`
- L78 _public member_ `FString HostName;`
- L79 _public member_ `FString ClientAddress;`
- L80 _public member_ `FString ServerAddress;`
- L81 _public member_ `FTimespan ServerTimeZone;`
- L83 _public prototype_ `FPerforceInfoRecord(const TMap<FString, FString>& Tags);`

#### struct `UGSCore::FPerforceFileRecord`  
`struct FPerforceFileRecord`  
_L86-97_
- L88 _public member_ `FString DepotPath;`
- L89 _public member_ `FString ClientPath;`
- L90 _public member_ `FString Path;`
- L91 _public member_ `FString Action;`
- L92 _public member_ `int Revision;`
- L93 _public member_ `bool IsMapped;`
- L94 _public member_ `bool Unmap;`
- L96 _public prototype_ `FPerforceFileRecord(const TMap<FString, FString>& Tags);`

#### struct `UGSCore::FPerforceTagRecordParser`  
`struct FPerforceTagRecordParser`  
_L99-109_
- L101 _public member_ `TFunction<void(const TMap<FString, FString>&)> OutputRecord;`
- L102 _public member_ `TMap<FString, FString> Tags;`
- L104 _public prototype_ `FPerforceTagRecordParser(TFunction<void(const TMap<FString, FString>&)> InOutputRecord);`
- L105 _public prototype_ `~FPerforceTagRecordParser();`
- L107 _public prototype_ `void OutputLine(const FString& Line);`
- L108 _public prototype_ `void Flush();`

#### struct `UGSCore::FPerforceWhereRecord`  
`struct FPerforceWhereRecord`  
_L111-116_
- L113 _public member_ `FString LocalPath;`
- L114 _public member_ `FString ClientPath;`
- L115 _public member_ `FString DepotPath;`

#### struct `UGSCore::FPerforceSyncOptions`  
`struct FPerforceSyncOptions`  
_L118-125_
- L120 _public member_ `int NumRetries;`
- L121 _public member_ `int NumThreads;`
- L122 _public member_ `int TcpBufferSize;`
- L124 _public prototype_ `FPerforceSyncOptions();`

#### struct `UGSCore::FPerforceSpec`  
`struct FPerforceSpec`  
_L127-161_
- L129 _public member_ `TArray<TTuple<FString, FString>> Sections;`
- L137 _public prototype_ `const TCHAR* GetField(const TCHAR* Name) const;` — Gets the current value of a field with the given name @param Name Name of the field to search for @return The value of the field, or null if it does not exist.
- L145 _public prototype_ `void SetField(const TCHAR* Name, const TCHAR* Value);` — Sets the value of an existing field, or adds a new one with the given name @param Name of the field to set @param New value of the field
- L153 _public prototype_ `static bool TryParse(const TArray<FString>& Lines, TSharedPtr<FPerforceSpec>& OutSpec, FOutputDevice& Log);` — Parses a spec (clientspec, branchspec, changespec) from an array of lines @param Lines Text split into separate lines @return Array of section names and values
- L160 _public prototype_ `FString ToString() const;` — Formats a P4 specification as a block of text @return Spec as a single string

#### enum `UGSCore::EPerforceOutputChannel`  
`enum class EPerforceOutputChannel`  
_L163-172_
- L165 _public enumerator_ `Unknown`
- L166 _public enumerator_ `Text`
- L167 _public enumerator_ `Info`
- L168 _public enumerator_ `TaggedInfo`
- L169 _public enumerator_ `Warning`
- L170 _public enumerator_ `Error`
- L171 _public enumerator_ `Exit`

#### struct `UGSCore::FPerforceOutputLine`  
`struct FPerforceOutputLine`  
_L174-181_
- L176 _public member_ `EPerforceOutputChannel Channel;`
- L177 _public member_ `FString Text;`
- L179 _public prototype_ `FPerforceOutputLine();`
- L180 _public prototype_ `FPerforceOutputLine(EPerforceOutputChannel InChannel, const FString& InText);`

#### class `UGSCore::FPerforceConnection`  
`class FPerforceConnection`  
_L183-271_
- L199 _public member_ `const FString ServerAndPort;`
- L200 _public member_ `const FString UserName;`
- L201 _public member_ `const FString ClientName;`
- L203 _public prototype_ `FPerforceConnection(const TCHAR* InUserName, const TCHAR* InClientName, const TCHAR* InServerAndPort);`
- L204 _public prototype_ `TSharedRef<FPerforceConnection> OpenClient(const FString& NewClientName) const;`
- L206 _public prototype_ `bool Info(TSharedPtr<FPerforceInfoRecord>& OutInfo, FEvent* AbortEvent, FOutputDevice& Log) const;`
- L207 _public prototype_ `bool GetSetting(const FString& Name, FString& Value, FEvent* AbortEvent, FOutputDevice& Log) const;`
- L208 _public prototype_ `bool FindClients(TArray<FPerforceClientRecord>& Clients, FEvent* AbortEvent, FOutputDevice& Log) const;`
- L209 _public prototype_ `bool FindClients(TArray<FPerforceClientRecord>& Clients, const FString& ForUserName, FEvent* AbortEvent, FOutputDevice& Log) const;`
- L210 _public prototype_ `bool CreateClient(const FPerforceClientRecord& Client, const FString& Stream, FEvent* AbortEvent, FOutputDevice& Log) const;`
- L211 _public prototype_ `bool TryGetClientSpec(const FString& ClientName, TSharedPtr<FPerforceSpec>& OutSpec, FEvent* AbortEvent, FOutputDevice& Log) const;`
- L212 _public prototype_ `bool TryGetStreamSpec(const FString& StreamName, TSharedPtr<FPerforceSpec>& OutSpec, FEvent* AbortEvent, FOutputDevice& Log) const;`
- L213 _public prototype_ `bool FindFiles(const FString& Filter, TArray<FPerforceFileRecord>& FileRecords, FEvent* AbortEvent, FOutputDevice& Log) const;`
- L214 _public prototype_ `bool Print(const FString& DepotPath, TArray<FString>& Lines, FEvent* AbortEvent, FOutputDevice& Log) const;`
- L215 _public prototype_ `bool PrintToFile(const FString& DepotPath, const FString& OutputFileName, FEvent* AbortEvent, FOutputDevice& Log) const;`
- L216 _public prototype_ `bool FileExists(const FString& Filter, bool& bExists, FEvent* AbortEvent, FOutputDevice& Log) const;`
- L217 _public prototype_ `bool FindChanges(const FString& Filter, int MaxResults, TArray<FPerforceChangeSummary>& OutChanges, FEvent* AbortEvent, FOutputDevice& Log) const;`
- L218 _public prototype_ `bool FindChanges(const TArray<FString>& Filters, int MaxResults, TArray<FPerforceChangeSummary>& OutChanges, FEvent* AbortEvent, FOutputDevice& Log) const;`
- L219 _public prototype_ `bool TryParseChangeSummary(const FString& Line, FPerforceChangeSummary& Change) const;`
- L220 _public prototype_ `bool FindFileChanges(const FString& FilePath, int MaxResults, TArray<FPerforceFileChangeSummary>& Changes, FEvent* AbortEvent, FOutputDevice& Log) const;`
- L221 _public prototype_ `bool TryParseFileChangeSummary(const TArray<FString>& Lines, int& LineIdx, FPerforceFileChangeSummary& OutChange) const;`
- L222 _public prototype_ `bool ConvertToClientPath(const FString& FileName, FString& OutClientFileName, FEvent* AbortEvent, FOutputDevice& Log) const;`
- L223 _public prototype_ `bool ConvertToDepotPath(const FString& FileName, FString& OutDepotFileName, FEvent* AbortEvent, FOutputDevice& Log) const;`
- L224 _public prototype_ `bool ConvertToLocalPath(const FString& FileName, FString& OutLocalFileName, FEvent* AbortEvent, FOutputDevice& Log) const;`
- L225 _public prototype_ `bool FindStreams(const FString& Filter, TArray<FString>& OutStreamNames, FEvent* AbortEvent, FOutputDevice& Log) const;`
- L226 _public prototype_ `bool HasOpenFiles(FEvent* AbortEvent, FOutputDevice& Log) const;`
- L227 _public prototype_ `bool SwitchStream(const FString& NewStream, FEvent* AbortEvent, FOutputDevice& Log) const;`
- L228 _public prototype_ `bool Describe(int ChangeNumber, TSharedPtr<FPerforceDescribeRecord>& OutRecord, FEvent* AbortEvent, FOutputDevice& Log) const;`
- L229 _public prototype_ `bool Where(const FString& Filter, TSharedPtr<FPerforceWhereRecord>& OutWhereRecord, FEvent* AbortEvent, FOutputDevice& Log) const;`
- L230 _public prototype_ `bool Have(const FString& Filter, TArray<FPerforceFileRecord>& OutFileRecords, FEvent* AbortEvent, FOutputDevice& Log) const;`
- L231 _public prototype_ `bool Stat(const FString& Filter, TArray<FPerforceFileRecord>& OutFileRecords, FEvent* AbortEvent, FOutputDevice& Log) const;`
- L232 _public prototype_ `bool Sync(const FString& Filter, FEvent* AbortEvent, FOutputDevice& Log) const;`
- L233 _public prototype_ `bool Sync(const TArray<FString>& DepotPaths, int ChangeNumber, TFunction<void(const FPerforceFileRecord&)> SyncOutput, TArray<FString>& OutTamperedFiles, const FPerforceSyncOptions* Options, FEvent* AbortEvent, FOutputDevice& Log) const;`
- L234 _public prototype_ `bool LatestChangeList(int& OutChangeList, FEvent* AbortEvent, FOutputDevice& Log) const;`
- L236 _public prototype_ `void OpenP4V(const FString& AdditionalArgs = FString()) const;`
- L237 _public prototype_ `void OpenP4VC(const FString& AdditionalArgs = FString()) const;`
- L240 _private prototype_ `static bool FilterSyncOutput(const FPerforceOutputLine& Line, FPerforceTagRecordParser& Parser, TArray<FString>& OutTamperedFiles, FOutputDevice& Log);`
- L241 _private prototype_ `static void ParseTamperedFile(const FString& Line, TArray<FString>& OutTamperedFiles);`
- L244 _public prototype_ `bool SyncPreview(const FString& Filter, int ChangeNumber, bool bOnlyFilesInThisChange, TArray<FPerforceFileRecord>& OutFileRecords, FEvent* AbortEvent, FOutputDevice& Log) const;`
- L245 _public prototype_ `bool ForceSync(const FString& Filter, int ChangeNumber, FEvent* AbortEvent, FOutputDevice& Log) const;`
- L246 _public prototype_ `bool GetOpenFiles(const FString& Filter, TArray<FPerforceFileRecord>& OutFileRecords, FEvent* AbortEvent, FOutputDevice& Log) const;`
- L247 _public prototype_ `bool GetUnresolvedFiles(const FString& Filter, TArray<FPerforceFileRecord>& OutFileRecords, FEvent* AbortEvent, FOutputDevice& Log) const;`
- L248 _public prototype_ `bool AutoResolveFile(const FString& Filter, FEvent* AbortEvent, FOutputDevice& Log) const;`
- L249 _public prototype_ `bool GetActiveStream(FString& OutStreamName, FEvent* AbortEvent, FOutputDevice& Log) const;`
- L252 _private prototype_ `bool RunCommand(const FString& CommandLine, TArray<FPerforceFileRecord>& OutFileRecords, ECommandOptions Options, FEvent* AbortEvent, FOutputDevice& Log) const;`
- L253 _private prototype_ `bool RunCommand(const FString& CommandLine, TArray<FPerforceClientRecord>& OutClientRecords, ECommandOptions Options, FEvent* AbortEvent, FOutputDevice& Log) const;`
- L254 _private prototype_ `bool RunCommand(const FString& CommandLine, TArray<TMap<FString, FString>>& OutTagRecords, ECommandOptions Options, FEvent* AbortEvent, FOutputDevice& Log) const;`
- L255 _private prototype_ `bool RunCommand(const FString& CommandLine, ECommandOptions Options, FEvent* AbortEvent, FOutputDevice& Log, const FString& WritePipeText = FString()) const;`
- L256 _private prototype_ `bool RunCommand(const FString& CommandLine, TArray<FString>& OutLines, ECommandOptions Options, FEvent* AbortEvent, FOutputDevice& Log, const FString& WritePipeText = FString()) const;`
- L257 _private prototype_ `bool RunCommand(const FString& CommandLine, EPerforceOutputChannel Channel, TArray<FString>& OutLines, ECommandOptions Options, FEvent* AbortEvent, FOutputDevice& Log, const FString& WritePipeText = FString()) const;`
- L258 _private prototype_ `bool RunCommand(const FString& CommandLine, const TCHAR* Input, TFunction<bool(const FPerforceOutputLine&)> HandleOutput, ECommandOptions Options, FEvent* AbortEvent, FOutputDevice& Log) const;`
- L259 _private prototype_ `FString GetFullCommandLine(const FString& CommandLine, ECommandOptions Options) const;`
- L260 _private prototype_ `bool ParseCommandOutput(const FString& Text, TFunction<bool(const FPerforceOutputLine&)> HandleOutput, ECommandOptions Options) const;`
- L261 _private prototype_ `static bool IsValidTag(const FString& Line, int StartIndex);`
- L262 _private prototype_ `static bool IgnoreCommandOutput(const FString& Text, ECommandOptions Options);`
- L264 _private prototype_ `static const uint8* ReadBinaryField(const uint8* Pos, const uint8* End, FString* OutField);`
- L265 _private prototype_ `static const uint8* ReadBinaryRecord(const uint8* Pos, const uint8* End, TMap<FString, FString>* OutRecord);`
- L267 _private prototype_ `bool RunCommandWithBinaryOutput(const FString& CommandLine, TArray<TMap<FString, FString>>& OutRecords, ECommandOptions Options, FEvent* AbortEvent, FOutputDevice& Log) const;`
- L268 _private prototype_ `bool RunCommandWithBinaryOutput(const FString& CommandLine, TFunction<void(const TMap<FString, FString>&)> HandleOutput, ECommandOptions Options, FEvent* AbortEvent, FOutputDevice& Log) const;`
- L270 _private prototype_ `FString GetArgumentsForExternalProgram(bool bIncludeClient = true) const;`

#### enum `UGSCore::FPerforceConnection::ECommandOptions`  
`enum class ECommandOptions`  
_L186-197_
- L188 _public enumerator_ `None = 0x0`
- L189 _public enumerator_ `NoClient = 0x1`
- L190 _public enumerator_ `NoFailOnErrors = 0x2`
- L191 _public enumerator_ `NoChannels = 0x4`
- L192 _public enumerator_ `IgnoreFilesUpToDateError = 0x8`
- L193 _public enumerator_ `IgnoreNoSuchFilesError = 0x10`
- L194 _public enumerator_ `IgnoreFilesNotOpenedOnThisClientError = 0x20`
- L195 _public enumerator_ `IgnoreExitCode = 0x40`
- L196 _public enumerator_ `IgnoreFilesNotInClientViewError = 0x80`

#### struct `UGSCore::FPerforceUtils`  
`struct FPerforceUtils`  
_L277-281_
- L279 _public prototype_ `static FString GetClientOrDepotDirectoryName(const TCHAR* ClientFile);`
- L280 _public prototype_ `static bool TryParseDateTime(const FString& Date, const FString& Time, FDateTime& OutDate);`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UGSCore`

### `Source/Programs/UGSCore/PerforceMonitor.h` (Other)


#### struct `UGSCore::FChangeType`  
`struct FChangeType`  
_L15-19_
- L17 _public member_ `bool bContainsCode = false;`
- L18 _public member_ `bool bContainsContent = false;`

#### class `UGSCore::FPerforceMonitor`  
`class FPerforceMonitor : FRunnable`  
_L21-81_
- inherits: `FRunnable`
- L24 _public typedef_ `typedef TSharedRef<FPerforceChangeSummary, ESPMode::ThreadSafe> FChangeSharedRef;`
- L26 _public member_ `TFunction<void()> OnUpdate;`
- L27 _public member_ `TFunction<void()> OnUpdateMetadata;`
- L28 _public member_ `TFunction<void()> OnChangeTypeQueryFinished;`
- L29 _public member_ `TFunction<void()> OnStreamChange;`
- L31 _public prototype_ `FPerforceMonitor(const TSharedRef<FPerforceConnection>& InPerforce, const FString& InBranchClientPath, const FString& InSelectedClientFileName, const FString& InSelectedProjectIdentifier, const FString& InLogPath);`
- L32 _public prototype_ `~FPerforceMonitor();`
- L34 _public prototype_ `void Start();`
- L36 _public prototype_ `FString GetLastStatusMessage() const;`
- L37 _public prototype_ `int GetCurrentMaxChanges() const;`
- L38 _public prototype_ `int GetPendingMaxChanges() const;`
- L39 _public prototype_ `TArray<FString> GetOtherStreamNames() const;`
- L40 _public prototype_ `int GetLastChangeByCurrentUser() const;`
- L41 _public prototype_ `int GetLastCodeChangeByCurrentUser() const;`
- L42 _public prototype_ `bool HasZippedBinaries() const;`
- L44 _public prototype_ `TArray<FChangeSharedRef> GetChanges() const;`
- L45 _public prototype_ `bool TryGetChangeType(int ChangeNumber, FChangeType& OutType) const;`
- L46 _public prototype_ `bool TryGetArchivePathForChangeNumber(int ChangeNumber, FString& OutArchivePath) const;`
- L47 _public prototype_ `TSet<int> GetPromotedChangeNumbers() const;`
- L49 _public prototype_ `void Refresh();`
- L52 _private member_ `TSharedRef<FPerforceConnection> Perforce;`
- L53 _private member_ `const FString BranchClientPath;`
- L54 _private member_ `const FString SelectedClientFileName;`
- L55 _private member_ `const FString SelectedProjectIdentifier;`
- L56 _private member_ `FBoundedLogWriter LogWriter;`
- L57 _private member_ `FRunnableThread* WorkerThread;`
- L58 _private member_ `TArray<FChangeSharedRef> Changes;` — Sorted
- L59 _private member_ `TMap<int, FChangeType> ChangeNumberToType;`
- L60 _private member_ `TSet<int> PromotedChangeNumbers;`
- L61 _private member_ `int ZippedBinariesConfigChangeNumber;`
- L62 _private member_ `FString ZippedBinariesPath;`
- L63 _private member_ `TMap<int, FString> ChangeNumberToZippedBinaries;`
- L64 _private member_ `FEvent* RefreshEvent;`
- L65 _private member_ `FEvent* AbortEvent;`
- L66 _private member_ `FString LastStatusMessage;`
- L67 _private member_ `int CurrentMaxChanges;`
- L68 _private member_ `int PendingMaxChanges;`
- L69 _private member_ `int LastChangeByCurrentUser;`
- L70 _private member_ `int LastCodeChangeByCurrentUser;`
- L71 _private member_ `TArray<FString> OtherStreamNames;`
- L72 _private member_ `bool bDisposing;`
- L73 _private member_ `mutable FCriticalSection CriticalSection;`
- L75 _private prototype_ `virtual uint32 Run() override;`
- L76 _private prototype_ `void RunInternal();`
- L78 _private prototype_ `bool UpdateChanges();`
- L79 _private prototype_ `bool UpdateChangeTypes();`
- L80 _private prototype_ `bool UpdateZippedBinaries();`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UGSCore`

### `Source/Programs/UGSCore/Telemetry.h` (Other)


#### class `UGSCore::FTelemetryStopwatch`  
`class FTelemetryStopwatch`  
_L11-26_
- L14 _public prototype_ `FTelemetryStopwatch(const FString& InAction, const FString& InProject);`
- L15 _public prototype_ `~FTelemetryStopwatch();`
- L17 _public prototype_ `FTimespan Stop(const FString& InResult);`
- L18 _public prototype_ `FTimespan GetElapsed() const;`
- L21 _private member_ `const FString Action;`
- L22 _private member_ `const FString Project;`
- L23 _private member_ `const FDateTime StartTime;`
- L24 _private member_ `FString Result;`
- L25 _private member_ `FDateTime EndTime;`

#### class `UGSCore::FTelemetryWriter`  
`class FTelemetryWriter`  
_L28-33_
- L31 _public prototype_ `FTelemetryWriter(const FString& InSqlConnectionString, const FString& InLogFileName);`
- L32 _public prototype_ `~FTelemetryWriter();`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UGSCore`

### `Source/Programs/UGSCore/UserSettings.h` (Other)


#### enum `UGSCore::EBuildConfig`  
`enum class EBuildConfig`  
_L14-19_
- L16 _public enumerator_ `Debug`
- L17 _public enumerator_ `DebugGame`
- L18 _public enumerator_ `Development`

#### enum `UGSCore::ETabLabels`  
`enum class ETabLabels`  
_L24-30_
- L26 _public enumerator_ `Stream`
- L27 _public enumerator_ `WorkspaceName`
- L28 _public enumerator_ `WorkspaceRoot`
- L29 _public enumerator_ `ProjectFile`

#### enum `UGSCore::ELatestChangeType`  
`enum class ELatestChangeType`  
_L35-40_
- L37 _public enumerator_ `Any`
- L38 _public enumerator_ `Good`
- L39 _public enumerator_ `Starred`

#### struct `UGSCore::FUserWorkspaceSettings`  
`struct FUserWorkspaceSettings`  
_L45-69_
- L48 _public member_ `FString CurrentProjectIdentifier;` — Settings for the currently synced project in this workspace. CurrentChangeNumber is only valid for this workspace if CurrentProjectPath is the current project.
- L49 _public member_ `int CurrentChangeNumber;`
- L50 _public member_ `TArray<int> AdditionalChangeNumbers;`
- L53 _public member_ `int LastSyncChangeNumber;` — Settings for the last attempted sync. These values are set to persist error messages between runs.
- L54 _public member_ `EWorkspaceUpdateResult LastSyncResult;`
- L55 _public member_ `FString LastSyncResultMessage;`
- L56 _public member_ `TOptional<FDateTime> LastSyncTime;`
- L57 _public member_ `int LastSyncDurationSeconds;`
- L60 _public member_ `int LastBuiltChangeNumber;` — The last successful build, regardless of whether a failed sync has happened in the meantime. Used to determine whether to force a clean due to entries in the project config file.
- L63 _public member_ `TArray<FString> ExpandedArchiveTypes;` — Expanded archives in the workspace
- L66 _public member_ `TArray<FString> SyncView;` — Workspace specific SyncFilters
- L67 _public member_ `TArray<FGuid> SyncIncludedCategories;`
- L68 _public member_ `TArray<FGuid> SyncExcludedCategories;`

#### struct `UGSCore::FUserProjectSettings`  
`struct FUserProjectSettings`  
_L71-74_
- L73 _public member_ `TArray<FCustomConfigObject> BuildSteps;`

#### struct `UGSCore::FUserSettings`  
`struct FUserSettings`  
_L76-137_
- L78 _public member_ `const FString FileName;`
- L79 _public member_ `FCustomConfigFile ConfigFile;`
- L82 _public member_ `bool bBuildAfterSync;` — General settings
- L83 _public member_ `bool bRunAfterSync;`
- L84 _public member_ `bool bSyncPrecompiledEditor;`
- L85 _public member_ `bool bOpenSolutionAfterSync;`
- L86 _public member_ `bool bShowLogWindow;`
- L87 _public member_ `bool bAutoResolveConflicts;`
- L88 _public member_ `bool bUseIncrementalBuilds;`
- L89 _public member_ `bool bShowLocalTimes;`
- L90 _public member_ `bool bShowAllStreams;`
- L91 _public member_ `bool bKeepInTray;`
- L92 _public member_ `int FilterIndex;`
- L93 _public member_ `FString LastProjectFileName;`
- L94 _public member_ `TArray<FString> OpenProjectFileNames;`
- L95 _public member_ `TArray<FString> OtherProjectFileNames;`
- L96 _public member_ `TArray<FString> SyncView;`
- L97 _public member_ `TArray<FGuid> SyncIncludedCategories;`
- L98 _public member_ `TArray<FGuid> SyncExcludedCategories;`
- L99 _public member_ `ELatestChangeType SyncType;`
- L100 _public member_ `EBuildConfig CompiledEditorBuildConfig;` — NB: This assumes not using precompiled editor. See CurrentBuildConfig.
- L101 _public member_ `ETabLabels TabLabels;`
- L104 _public member_ `bool bHasWindowSettings;` — Window settings
- L106 _public member_ `TMap<FString, int> ColumnWidths;` — Rectangle WindowRectangle;
- L107 _public member_ `bool bWindowVisible;`
- L110 _public member_ `bool bScheduleEnabled;` — Schedule settings
- L111 _public member_ `FTimespan ScheduleTime;`
- L112 _public member_ `ELatestChangeType ScheduleChange;`
- L115 _public member_ `TArray<TTuple<FString, bool>> EditorArguments;` — Run configuration
- L118 _public member_ `TMap<FString, TSharedRef<FUserWorkspaceSettings>> WorkspaceKeyToSettings;` — Project settings
- L119 _public member_ `TMap<FString, TSharedRef<FUserProjectSettings>> ProjectKeyToSettings;`
- L122 _public member_ `FPerforceSyncOptions SyncOptions;` — Perforce settings
- L124 _public prototype_ `FUserSettings(const FString& InFileName);`
- L125 _public prototype_ `TSharedRef<FUserWorkspaceSettings> FindOrAddWorkspace(const TCHAR* ClientBranchPath);`
- L126 _public prototype_ `TSharedRef<FUserProjectSettings> FindOrAddProject(const TCHAR* ClientProjectFileName);`
- L127 _public prototype_ `void Save();`
- L129 _public prototype_ `static TArray<FString> GetCombinedSyncFilter(const TMap<FGuid, FWorkspaceSyncCategory>& UniqueIdToFilter, const TArray<FString>& GlobalView, const TArray<FGuid>& GlobalExcludedCategories, const TArray<FString>& WorkspaceView, const TArray<FGuid>& WorkspaceExcludedCategories);`
- L131 _public prototype_ `static FString EscapeText(const FString& Text);`
- L132 _public prototype_ `static FString UnescapeText(const FString& Text);`
- L135 _private prototype_ `void LoadGlobalSettings();`
- L136 _private prototype_ `void SaveGlobalSettings();`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UGSCore`
- L21 _prototype_ `FString ToString(EBuildConfig BuildConfig);` (scope `UGSCore`)
- L22 _prototype_ `bool TryParse(const TCHAR* Text, EBuildConfig& OutBuildConfig);` (scope `UGSCore`)
- L32 _prototype_ `FString ToString(ETabLabels Lables);` (scope `UGSCore`)
- L33 _prototype_ `bool TryParse(const TCHAR* Text, ETabLabels& OutTabLabels);` (scope `UGSCore`)
- L42 _prototype_ `FString ToString(ELatestChangeType LatestChangeType);` (scope `UGSCore`)
- L43 _prototype_ `bool TryParse(const TCHAR* Text, ELatestChangeType& OutLatestChangeType);` (scope `UGSCore`)

### `Source/Programs/UGSCore/Utility.h` (Other)


#### struct `UGSCore::FAbortException`  
`struct FAbortException`  
_L13-15_

#### struct `UGSCore::FUtility`  
`struct FUtility`  
_L17-40_
- L19 _public prototype_ `static bool TryParse(const TCHAR* Text, int32& OutValue);`
- L20 _public prototype_ `static bool TryParse(const TCHAR* Text, int64& OutValue);`
- L22 _public prototype_ `static bool IsFileUnderDirectory(const TCHAR* FileName, const TCHAR* DirectoryName);`
- L23 _public prototype_ `static FString GetPathWithCorrectCase(const FString& Path);`
- L25 _public prototype_ `static FString FormatUserName(const TCHAR* UserName);`
- L27 _public prototype_ `static int ExecuteProcess(const TCHAR* FileName, const TCHAR* CommandLine, const TCHAR* Input, FEvent* AbortEvent, FLineBasedTextWriter& Log);`
- L28 _public prototype_ `static int ExecuteProcess(const TCHAR* FileName, const TCHAR* CommandLine, const TCHAR* Input, FEvent* AbortEvent, TArray<FString>& OutLines);`
- L29 _public prototype_ `static int ExecuteProcess(const TCHAR* FileName, const TCHAR* CommandLine, const TCHAR* Input, FEvent* AbortEvent, const TFunction<void(const FString&)>& OutputLine);`
- L39 _public prototype_ `static FString ExpandVariables(const TCHAR* InputString, const TMap<FString, FString>* AdditionalVariables = nullptr);` — Expands variables in $(VarName) format in the given string. Variables are retrieved from the given dictionary, or through the environment of the current process. Any unknown variables are ignored. @param InputString String to search for variable names @param Variables Lookup of variable names to values @return String with all variables replaced

#### Free symbols / members of external scopes

- L8 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogUGSCore, Log, All);`
- L8 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogUGSCore, Log, All);`
- L10 _namespace_ `namespace UGSCore`

### `Source/Programs/UGSCore/Workspace.h` (Other)


#### enum `UGSCore::EWorkspaceUpdateOptions`  
`enum class EWorkspaceUpdateOptions`  
_L16-29_
- L18 _public enumerator_ `Sync = 0x01`
- L19 _public enumerator_ `SyncSingleChange = 0x02`
- L20 _public enumerator_ `AutoResolveChanges = 0x04`
- L21 _public enumerator_ `GenerateProjectFiles = 0x08`
- L22 _public enumerator_ `SyncArchives = 0x10`
- L23 _public enumerator_ `Build = 0x20`
- L24 _public enumerator_ `UseIncrementalBuilds = 0x40`
- L25 _public enumerator_ `ScheduledBuild = 0x80`
- L26 _public enumerator_ `RunAfterSync = 0x100`
- L27 _public enumerator_ `OpenSolutionAfterSync = 0x200`
- L28 _public enumerator_ `ContentOnly = 0x400`

#### enum `UGSCore::EWorkspaceUpdateResult`  
`enum class EWorkspaceUpdateResult`  
_L33-42_
- L35 _public enumerator_ `Canceled`
- L36 _public enumerator_ `FailedToSync`
- L37 _public enumerator_ `FilesToResolve`
- L38 _public enumerator_ `FilesToClobber`
- L39 _public enumerator_ `FailedToCompile`
- L40 _public enumerator_ `FailedToCompileWithCleanWorkspace`
- L41 _public enumerator_ `Success`

#### struct `UGSCore::FWorkspaceUpdateContext`  
`struct FWorkspaceUpdateContext`  
_L47-62_
- L49 _public member_ `FDateTime StartTime;`
- L50 _public member_ `int ChangeNumber;`
- L51 _public member_ `EWorkspaceUpdateOptions Options;`
- L52 _public member_ `TArray<FString> SyncFilter;`
- L53 _public member_ `TMap<FString, FString> ArchiveTypeToDepotPath;`
- L54 _public member_ `TMap<FString, bool> ClobberFiles;`
- L55 _public member_ `TMap<FGuid,FCustomConfigObject> DefaultBuildSteps;`
- L56 _public member_ `TArray<FCustomConfigObject> UserBuildStepObjects;`
- L57 _public member_ `TSet<FGuid> CustomBuildSteps;`
- L58 _public member_ `TMap<FString, FString> Variables;`
- L59 _public member_ `FPerforceSyncOptions PerforceSyncOptions;`
- L61 _public prototype_ `FWorkspaceUpdateContext(int InChangeNumber, EWorkspaceUpdateOptions InOptions, const TArray<FString>& InSyncFilter, const TMap<FGuid, FCustomConfigObject>& InDefaultBuildSteps, const TArray<FCustomConfigObject>& InUserBuildSteps, const TSet<FGuid>& InCustomBuildSteps, const TMap<FString, FString>& InVariables);`

#### struct `UGSCore::FWorkspaceSyncCategory`  
`struct FWorkspaceSyncCategory`  
_L64-73_
- L66 _public member_ `FGuid UniqueId;`
- L67 _public member_ `bool bEnable;`
- L68 _public member_ `FString Name;`
- L69 _public member_ `TArray<FString> Paths;`
- L71 _public prototype_ `FWorkspaceSyncCategory(const FGuid& InUniqueId);`
- L72 _public prototype_ `FWorkspaceSyncCategory(const FGuid& InUniqueId, const TCHAR* InName, const TCHAR* InPaths);`

#### class `UGSCore::FWorkspace`  
`class FWorkspace : FRunnable`  
_L75-151_
- inherits: `FRunnable`
- L78 _public member_ `const TSharedRef<FPerforceConnection> Perforce;`
- L79 _public member_ `const TArray<FString> SyncPaths;`
- L80 _public member_ `const FString LocalRootPath;`
- L81 _public member_ `const FString SelectedLocalFileName;`
- L82 _public member_ `const FString ClientRootPath;`
- L83 _public member_ `const FString SelectedClientFileName;`
- L84 _public member_ `const FString SelectedProjectIdentifier;`
- L85 _public member_ `const FString TelemetryProjectPath;`
- L87 _public member_ `TFunction<void(TSharedRef<FWorkspaceUpdateContext, ESPMode::ThreadSafe>, EWorkspaceUpdateResult, const FString&)> OnUpdateComplete;`
- L89 _public prototype_ `FWorkspace(TSharedRef<FPerforceConnection> InPerforce, const FString& InLocalRootPath, const FString& InSelectedLocalFileName, const FString& InClientRootPath, const FString& InSelectedClientFileName, const FString& InSelectedProjectIdentifier, int InInitialChangeNumber, int InLastBuiltChangeNumber, const FString& InTelemetryProjectPath, TSharedRef<FLineBasedTextWriter> InLog);`
- L90 _public prototype_ `~FWorkspace();`
- L92 _public prototype_ `TMap<FGuid, FWorkspaceSyncCategory> GetSyncCategories() const;`
- L93 _public prototype_ `TSharedPtr<FCustomConfigFile, ESPMode::ThreadSafe> GetProjectConfigFile() const;`
- L94 _public prototype_ `void GetProjectStreamFilter(TArray<FString>& Filter);`
- L95 _public prototype_ `bool IsBusy() const;`
- L96 _public prototype_ `TTuple<FString, float> GetCurrentProgress() const;`
- L97 _public prototype_ `int GetCurrentChangeNumber() const;`
- L98 _public prototype_ `int GetPendingChangeNumber() const;`
- L99 _public prototype_ `int GetLastBuiltChangeNumber() const;`
- L100 _public prototype_ `FString GetClientName() const;`
- L102 _public prototype_ `void Update(const TSharedRef<FWorkspaceUpdateContext, ESPMode::ThreadSafe>& Context);`
- L103 _public prototype_ `void CancelUpdate();`
- L105 _public prototype_ `FString GetPanelColor() const;`
- L106 _public prototype_ `FString GetAlertMessage() const;`
- L109 _private member_ `static const TCHAR* DefaultBuildTargets[];`
- L110 _private member_ `static const FWorkspaceSyncCategory DefaultSyncCategories[];`
- L111 _private member_ `static const TCHAR* BuildVersionFileName;`
- L112 _private member_ `static const TCHAR* VersionHeaderFileName;`
- L113 _private member_ `static const TCHAR* ObjectVersionFileName;`
- L115 _private member_ `int CurrentChangeNumber;`
- L116 _private member_ `int PendingChangeNumber;`
- L117 _private member_ `int LastBuiltChangeNumber;`
- L118 _private member_ `TSharedRef<FLineBasedTextWriter> Log;`
- L119 _private member_ `bool bSyncing;`
- L120 _private member_ `mutable FCriticalSection CriticalSection;`
- L121 _private member_ `TSharedRef<FCustomConfigFile, ESPMode::ThreadSafe> ProjectConfigFile;`
- L122 _private member_ `TArray<FString> ProjectStreamFilter;`
- L123 _private member_ `TSharedPtr<FWorkspaceUpdateContext, ESPMode::ThreadSafe> WorkerThreadContext;`
- L124 _private member_ `FEvent* AbortEvent;`
- L125 _private member_ `FRunnableThread* WorkerThread;`
- L126 _private member_ `FProgressValue Progress;`
- L128 _private member_ `FString PanelColor;`
- L129 _private member_ `FString AlertMessage;`
- L131 _private member_ `static FWorkspace* ActiveWorkspace;`
- L133 _private prototype_ `virtual uint32 Run() override;`
- L134 _private prototype_ `void UpdateWorkspace(FWorkspaceUpdateContext& Context);`
- L135 _private prototype_ `EWorkspaceUpdateResult UpdateWorkspaceInternal(FWorkspaceUpdateContext& Context, FString& OutStatusMessage);`
- L137 _private prototype_ `static TArray<FString> GetSyncPaths(const FString& ClientRootPath, const FString& SelectedClientFileName);`
- L138 _private prototype_ `static TSharedRef<FCustomConfigFile, ESPMode::ThreadSafe> ReadProjectConfigFile(const FString& LocalRootPath, const FString& SelectedLocalFileName, FLineBasedTextWriter& Log);`
- L139 _private prototype_ `static TArray<FString> ReadProjectStreamFilter(FPerforceConnection& Perforce, const FCustomConfigFile& ProjectConfigFile, FEvent* AbortEvent, FLineBasedTextWriter& Log);`
- L140 _private prototype_ `static FString FormatTime(long Seconds);`
- L142 _private prototype_ `void UpdateStatusPanel();`
- L144 _private prototype_ `bool HasModifiedSourceFiles() const;`
- L145 _private prototype_ `bool FindUnresolvedFiles(TArray<FPerforceFileRecord>& OutUnresolvedFiles) const;`
- L146 _private prototype_ `void UpdateSyncProgress(const FPerforceFileRecord& Record, TSet<FString>& RemainingFiles, int NumFiles);`
- L147 _private prototype_ `bool UpdateVersionFile(const TCHAR* LocalPath, const TMap<FString, FString>& VersionStrings, int ChangeNumber) const;`
- L148 _private prototype_ `bool WriteVersionFile(const FPerforceWhereRecord& WhereRecord, const FString& NewText) const;`
- L149 _private prototype_ `static bool UpdateVersionLine(FString& Line, const FString& Prefix, const FString& Suffix);`
- L150 _private prototype_ `static bool ReadToken(const FString& Line, int32& LineIdx, FString &OutToken);`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UGSCore`
- L44 _prototype_ `FString ToString(EWorkspaceUpdateResult WorkspaceUpdateResult);` (scope `UGSCore`)
- L45 _prototype_ `bool TryParse(const TCHAR* Text, EWorkspaceUpdateResult& OutWorkspaceUpdateResult);` (scope `UGSCore`)
