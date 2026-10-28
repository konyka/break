# Plugins / OneSkyLocalizationService

- module root: `Plugins/Developer/OneSkyLocalizationService/Source/OneSkyLocalizationService`
- headers: 11; symbols: 727
- symbol kinds: class=37, delegate=2, enum=1, enumerator=6, function=239, macro=1, member=260, namespace=1, prototype=122, struct=52, typedef=6
- PrivateDependencyModuleNames: Core, CoreUObject, Engine, HTTP, InputCore, Json, Localization, LocalizationCommandletExecution, LocalizationService, MainFrame, Serialization, Slate, SlateCore

### `Plugins/Developer/OneSkyLocalizationService/Source/OneSkyLocalizationService/Private/IOneSkyLocalizationServiceWorker.h` (Private)


#### class `IOneSkyLocalizationServiceWorker`  
`class IOneSkyLocalizationServiceWorker`  
_L7-26_
- L13 _public prototype_ `virtual FName GetName() const = 0;` — Name describing the work that this worker does. Used for factory method hookup.
- L18 _public prototype_ `virtual bool Execute( class FOneSkyLocalizationServiceCommand& InCommand ) = 0;` — Function that actually does the work. Can be executed on another thread.
- L24 _public prototype_ `virtual bool UpdateStates() const = 0;` — Updates the state of any items after completion (if necessary). This is always executed on the main thread. @returns true if states were updated

#### Free symbols / members of external scopes

- L28 _typedef_ `typedef TSharedRef<IOneSkyLocalizationServiceWorker, ESPMode::ThreadSafe> FOneSkyLocalizationServiceWorkerRef;`

### `Plugins/Developer/OneSkyLocalizationService/Source/OneSkyLocalizationService/Private/OneSkyConnection.h` (Private)


#### class `FOneSkyConnection`  
`class FOneSkyConnection`  
_L9-35_
- L14 _public prototype_ `FOneSkyConnection(const FOneSkyConnectionInfo& InConnectionInfo);`
- L16 _public prototype_ `~FOneSkyConnection();` — API Specific close of localization service project
- L20 _public prototype_ `bool IsValidConnection();` — Returns true if connection is currently active
- L23 _public prototype_ `void Disconnect();` — If the connection is valid, disconnect from the server
- L29 _public prototype_ `bool EstablishConnection(const FOneSkyConnectionInfo& InConnectionInfo);` — Make a valid connection if possible @param InConnectionInfo		Connection credentials
- L34 _public member_ `bool bEstablishedConnection;` — true if connection was successfully established

#### class `FScopedOneSkyConnection`  
`class FScopedOneSkyConnection`  
_L40-85_
- desc: Connection that is used within specific scope
- L49 _public prototype_ `FScopedOneSkyConnection( const class FOneSkyLocalizationServiceCommand& InCommand );` — Constructor - establish a connection. The concurrency of the passed in command determines whether the persistent connection is used or another connection is established (connections cannot safely be used across different threads).
- L56 _public prototype_ `FScopedOneSkyConnection( ELocalizationServiceOperationConcurrency::Type InConcurrency, const FOneSkyConnectionInfo& InConnectionInfo );` — Constructor - establish a connection. The concurrency passed in determines whether the persistent connection is used or another connection is established (connections cannot safely be used across different threads).
- L61 _public prototype_ `~FScopedOneSkyConnection();` — Destructor - disconnect if this is a temporary connection
- L64 _public function_ `FOneSkyConnection& GetConnection() const` — Get the connection wrapped by this class
- L70 _public function_ `bool IsValid() const` — Check if this connection is valid
- L77 _private prototype_ `void Initialize( const FOneSkyConnectionInfo& InConnectionInfo );` — Set up the connection
- L81 _private member_ `FOneSkyConnection* Connection;` — The OneSky connection we are using
- L84 _private member_ `ELocalizationServiceOperationConcurrency::Type Concurrency;` — The concurrency of this connection

### `Plugins/Developer/OneSkyLocalizationService/Source/OneSkyLocalizationService/Private/OneSkyConnectionInfo.h` (Private)


#### struct `FOneSkyConnectionInfo`  
`struct FOneSkyConnectionInfo`  
_L10-20_
- desc: Helper struct defining parameters we need to establish a connection
- L13 _public member_ `FString Name;` — Name of this connection configuration
- L16 _public member_ `FString ApiKey;` — OneSky ApiKey
- L19 _public member_ `FString ApiSecret;` — OneSky ApiSecret

### `Plugins/Developer/OneSkyLocalizationService/Source/OneSkyLocalizationService/Private/OneSkyLocalizationServiceCommand.h` (Private)


#### class `FOneSkyLocalizationServiceCommand`  
`class FOneSkyLocalizationServiceCommand : public IQueuedWork`  
_L14-91_
- inherits: `IQueuedWork`
- desc: Used to execute OneSky commands multi-threaded.
- L18 _public prototype_ `FOneSkyLocalizationServiceCommand(const TSharedRef<class ILocalizationServiceOperation, ESPMode::ThreadSafe>& InOperation, const TSharedRef<class IOneSkyLocalizationServiceWorker, ESPMode::ThreadSafe>& InWorker, const FLocalizationServiceOperationComplete& InOperationCompleteDelegate = FLocalizationServiceOperationComplete() );`
- L24 _public prototype_ `bool DoWork();` — This is where the real thread work is done. All work that is done for this queued object should be done from within the call to this function.
- L32 _public prototype_ `virtual void Abandon() override;` — Tells the queued work that it is being abandoned so that it can do per object clean up as needed. This will only be called if it is being abandoned before completion. NOTE: This requires the object to delete itself using whatever heap it was allocated in.
- L38 _public prototype_ `virtual void DoThreadedWork() override;` — This method is also used to tell the object to cleanup but not before the object has finished it's work.
- L41 _public prototype_ `void Cancel();` — Attempt to cancel the operation
- L44 _public prototype_ `bool IsCanceled() const;` — Is the operation canceled?
- L48 _public member_ `FOneSkyConnectionInfo ConnectionInfo;` — Connection parameters, reproduced here because if is not safe to access the provider's settings from another thread
- L51 _public member_ `TSharedRef<class ILocalizationServiceOperation, ESPMode::ThreadSafe> Operation;` — Operation we want to perform - contains outward-facing parameters & results
- L54 _public member_ `TSharedRef<class IOneSkyLocalizationServiceWorker, ESPMode::ThreadSafe> Worker;` — The object that will actually do the work
- L57 _public member_ `FLocalizationServiceOperationComplete OperationCompleteDelegate;` — Delegate to notify when this operation completes
- L60 _public member_ `volatile int32 bExecuteProcessed;` — If true, this command has been processed by the Localization service thread
- L63 _public member_ `volatile int32 bCancelled;` — If true, this command has been cancelled
- L66 _public member_ `bool bCommandSuccessful;` — If true, the Localization service command succeeded
- L69 _public member_ `bool bConnectionDropped;` — If true, the Localization service connection was dropped while this command was being executed
- L72 _public member_ `bool bAutoDelete;` — If true, this command will be automatically cleaned up in Tick()
- L75 _public member_ `ELocalizationServiceOperationConcurrency::Type Concurrency;` — Whether we are running multi-treaded or not
- L78 _public member_ `FGuid TargetGuid;` — The GUID of the Localization Target we are working with
- L81 _public member_ `TArray< FString > Files;` — Files to perform this operation on
- L84 _public member_ `TArray< FLocalizationServiceTranslationIdentifier > Translations;` — Translations to perform this operation on
- L87 _public member_ `TArray< FText > InfoMessages;` — Info and/or warning message message storage
- L90 _public member_ `TArray< FText > ErrorMessages;` — Potential error message storage

#### Free symbols / members of external scopes

- L9 _delegate_ `DECLARE_DELEGATE_RetVal(bool, FOnIsCancelled);`
- L9 _prototype_ `DECLARE_DELEGATE_RetVal(bool, FOnIsCancelled);`

### `Plugins/Developer/OneSkyLocalizationService/Source/OneSkyLocalizationService/Private/OneSkyLocalizationServiceModule.h` (Private)


#### class `FOneSkyLocalizationServiceModule`  
`class FOneSkyLocalizationServiceModule : public IModuleInterface`  
_L9-45_
- inherits: `IModuleInterface`
- L13 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L14 _public prototype_ `virtual void ShutdownModule() override;`
- L17 _public prototype_ `FOneSkyLocalizationServiceSettings& AccessSettings();` — Access the OneSky Localization service settings
- L20 _public prototype_ `void SaveSettings();` — Save the OneSky Localization service settings
- L23 _public function_ `FOneSkyLocalizationServiceProvider& GetProvider()` — Access the one and only Perforce provider
- L34 _public function_ `static inline FOneSkyLocalizationServiceModule& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L41 _private member_ `FOneSkyLocalizationServiceProvider OneSkyLocalizationServiceProvider;` — The one and only OneSky Localization service provider
- L44 _private member_ `FOneSkyLocalizationServiceSettings OneSkyLocalizationServiceSettings;` — The settings for OneSky Localization service

### `Plugins/Developer/OneSkyLocalizationService/Source/OneSkyLocalizationService/Private/OneSkyLocalizationServiceOperations.h` (Private)


#### class `FOneSkyConnect`  
`class FOneSkyConnect : public IOneSkyLocalizationServiceWorker`  
_L19-29_
- inherits: `IOneSkyLocalizationServiceWorker`
- L22 _public function_ `virtual ~FOneSkyConnect()`
- L24 _public prototype_ `virtual FName GetName() const override;` — IOneSkyLocalizationServiceWorker interface
- L25 _public prototype_ `virtual bool Execute(class FOneSkyLocalizationServiceCommand& InCommand) override;`
- L26 _public function_ `virtual bool UpdateStates() const override`

#### class `FOneSkyListProjectGroupsOperation`  
`class FOneSkyListProjectGroupsOperation : public ILocalizationServiceOperation`  
_L37-77_
- inherits: `ILocalizationServiceOperation`
- desc: Operation used to list project groups in one sky
- L41 _public function_ `virtual FName GetName() const override` — ILocalizationServiceOperation interface
- L46 _public function_ `virtual FText GetInProgressString() const override`
- L51 _public function_ `FOneSkyListProjectGroupsOperation() : InStartPage(-1), InItemsPerPage(-1)`
- L53 _public function_ `void SetInStartPage(int32 NewStartPage)`
- L58 _public function_ `int32 GetInStartPage()`
- L63 _public function_ `void SetInItemsPerPage(int32 NewItemsPerPage)`
- L68 _public function_ `int32 GetInItemsPerPage()`
- L75 _protected member_ `int32 InStartPage;`
- L76 _protected member_ `int32 InItemsPerPage;`

#### class `FOneSkyListProjectGroupsWorker`  
`class FOneSkyListProjectGroupsWorker : public IOneSkyLocalizationServiceWorker`  
_L79-94_
- inherits: `IOneSkyLocalizationServiceWorker`
- L82 _public function_ `virtual ~FOneSkyListProjectGroupsWorker()`
- L84 _public prototype_ `virtual FName GetName() const override;` — IOneSkyLocalizationServiceWorker interface
- L85 _public prototype_ `virtual bool Execute(class FOneSkyLocalizationServiceCommand& InCommand) override;`
- L86 _public function_ `virtual bool UpdateStates() const override`
- L87 _public prototype_ `void Query_HttpRequestComplete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded);`
- L90 _public member_ `FOneSkyLocalizationServiceCommand* Command;`
- L93 _public member_ `FOneSkyListProjectGroupsResponse OutListProjectGroupsResponse;` — Response to the  command

#### class `FOneSkyShowProjectGroupOperation`  
`class FOneSkyShowProjectGroupOperation : public ILocalizationServiceOperation`  
_L105-134_
- inherits: `ILocalizationServiceOperation`
- desc: Operation used to show a project group in one sky
- L109 _public function_ `virtual FName GetName() const override` — ILocalizationServiceOperation interface
- L114 _public function_ `virtual FText GetInProgressString() const override`
- L119 _public function_ `FOneSkyShowProjectGroupOperation() : InProjectGroupId(-1)`
- L121 _public function_ `int32 GetInProjectGroupId()`
- L126 _public function_ `void SetInProjectGroupId(int32 NewProjectGroupId)`
- L133 _protected member_ `int32 InProjectGroupId;`

#### class `FOneSkyShowProjectGroupWorker`  
`class FOneSkyShowProjectGroupWorker : public IOneSkyLocalizationServiceWorker`  
_L136-151_
- inherits: `IOneSkyLocalizationServiceWorker`
- L139 _public function_ `virtual ~FOneSkyShowProjectGroupWorker()`
- L141 _public prototype_ `virtual FName GetName() const override;` — IOneSkyLocalizationServiceWorker interface
- L142 _public prototype_ `virtual bool Execute(class FOneSkyLocalizationServiceCommand& InCommand) override;`
- L143 _public function_ `virtual bool UpdateStates() const override`
- L144 _public prototype_ `void Query_HttpRequestComplete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded);`
- L147 _public member_ `FOneSkyLocalizationServiceCommand* Command;`
- L150 _public member_ `FOneSkyShowProjectGroupResponse OutShowProjectGroupResponse;` — Response to the command

#### class `FOneSkyCreateProjectGroupOperation`  
`class FOneSkyCreateProjectGroupOperation : public ILocalizationServiceOperation`  
_L161-202_
- inherits: `ILocalizationServiceOperation`
- desc: Operation used to create a project group in one sky
- L165 _public function_ `virtual FName GetName() const override` — ILocalizationServiceOperation interface
- L170 _public function_ `virtual FText GetInProgressString() const override`
- L175 _public function_ `FOneSkyCreateProjectGroupOperation() : InProjectGroupName(""), InProjectGroupBaseLocale("")`
- L177 _public function_ `FString GetInProjectGroupName()`
- L182 _public function_ `void SetInProjectGroupName(FString NewProjectGroupName)`
- L187 _public function_ `FString GetInProjectGroupBaseLocale()`
- L192 _public function_ `void SetInInProjectGroupBaseLocale(FString NewProjectGroupBaseLocale)`
- L199 _protected member_ `FString InProjectGroupName;`
- L200 _protected member_ `FString InProjectGroupBaseLocale;`

#### class `FOneSkyCreateProjectGroupWorker`  
`class FOneSkyCreateProjectGroupWorker : public IOneSkyLocalizationServiceWorker`  
_L204-219_
- inherits: `IOneSkyLocalizationServiceWorker`
- L207 _public function_ `virtual ~FOneSkyCreateProjectGroupWorker()`
- L209 _public prototype_ `virtual FName GetName() const override;` — IOneSkyLocalizationServiceWorker interface
- L210 _public prototype_ `virtual bool Execute(class FOneSkyLocalizationServiceCommand& InCommand) override;`
- L211 _public function_ `virtual bool UpdateStates() const override`
- L212 _public prototype_ `void Query_HttpRequestComplete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded);`
- L215 _public member_ `FOneSkyLocalizationServiceCommand* Command;`
- L218 _public member_ `FOneSkyCreateProjectGroupResponse OutCreateProjectGroupResponse;` — Response to the command

#### class `FOneSkyListProjectGroupLanguagesOperation`  
`class FOneSkyListProjectGroupLanguagesOperation : public ILocalizationServiceOperation`  
_L229-258_
- inherits: `ILocalizationServiceOperation`
- desc: Operation used to list the languages supported by a project group in one sky
- L233 _public function_ `virtual FName GetName() const override` — ILocalizationServiceOperation interface
- L238 _public function_ `virtual FText GetInProgressString() const override`
- L243 _public function_ `FOneSkyListProjectGroupLanguagesOperation() : InProjectGroupId(-1)`
- L245 _public function_ `int32 GetInProjectGroupId()`
- L250 _public function_ `void SetInProjectGroupId(int32 NewProjectGroupId)`
- L257 _protected member_ `int32 InProjectGroupId;`

#### class `FOneSkyListProjectGroupLanguagesWorker`  
`class FOneSkyListProjectGroupLanguagesWorker : public IOneSkyLocalizationServiceWorker`  
_L260-275_
- inherits: `IOneSkyLocalizationServiceWorker`
- L263 _public function_ `virtual ~FOneSkyListProjectGroupLanguagesWorker()`
- L265 _public prototype_ `virtual FName GetName() const override;` — IOneSkyLocalizationServiceWorker interface
- L266 _public prototype_ `virtual bool Execute(class FOneSkyLocalizationServiceCommand& InCommand) override;`
- L267 _public function_ `virtual bool UpdateStates() const override`
- L268 _public prototype_ `void Query_HttpRequestComplete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded);`
- L271 _public member_ `FOneSkyLocalizationServiceCommand* Command;`
- L274 _public member_ `FOneSkyListProjectGroupLanguagesResponse OutListProjectGroupLanguagesResponse;` — Response to the command

#### class `FOneSkyListProjectsInGroupOperation`  
`class FOneSkyListProjectsInGroupOperation : public ILocalizationServiceOperation`  
_L285-314_
- inherits: `ILocalizationServiceOperation`
- desc: Operation used to list projects in a project group in one sky
- L289 _public function_ `virtual FName GetName() const override` — ILocalizationServiceOperation interface
- L294 _public function_ `virtual FText GetInProgressString() const override`
- L299 _public function_ `FOneSkyListProjectsInGroupOperation() : InProjectGroupId(-1)`
- L301 _public function_ `int32 GetInProjectGroupId()`
- L306 _public function_ `void SetInProjectGroupId(int32 NewProjectGroupId)`
- L313 _protected member_ `int32 InProjectGroupId;`

#### class `FOneSkyListProjectsInGroupWorker`  
`class FOneSkyListProjectsInGroupWorker : public IOneSkyLocalizationServiceWorker`  
_L316-331_
- inherits: `IOneSkyLocalizationServiceWorker`
- L319 _public function_ `virtual ~FOneSkyListProjectsInGroupWorker()`
- L321 _public prototype_ `virtual FName GetName() const override;` — IOneSkyLocalizationServiceWorker interface
- L322 _public prototype_ `virtual bool Execute(class FOneSkyLocalizationServiceCommand& InCommand) override;`
- L323 _public function_ `virtual bool UpdateStates() const override`
- L324 _public prototype_ `void Query_HttpRequestComplete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded);`
- L327 _public member_ `FOneSkyLocalizationServiceCommand* Command;`
- L330 _public member_ `FOneSkyListProjectsInGroupResponse OutListProjectsInGroupResponse;` — Response to the get project groups command

#### class `FOneSkyShowProjectOperation`  
`class FOneSkyShowProjectOperation : public ILocalizationServiceOperation`  
_L340-369_
- inherits: `ILocalizationServiceOperation`
- desc: Operation used to show a project in one sky
- L344 _public function_ `virtual FName GetName() const override` — ILocalizationServiceOperation interface
- L349 _public function_ `virtual FText GetInProgressString() const override`
- L354 _public function_ `FOneSkyShowProjectOperation() : InProjectId(-1)`
- L356 _public function_ `int32 GetInProjectId()`
- L361 _public function_ `void SetInProjectId(int32 NewProjectId)`
- L368 _protected member_ `int32 InProjectId;`

#### class `FOneSkyShowProjectWorker`  
`class FOneSkyShowProjectWorker : public IOneSkyLocalizationServiceWorker`  
_L371-386_
- inherits: `IOneSkyLocalizationServiceWorker`
- L374 _public function_ `virtual ~FOneSkyShowProjectWorker()`
- L376 _public prototype_ `virtual FName GetName() const override;` — IOneSkyLocalizationServiceWorker interface
- L377 _public prototype_ `virtual bool Execute(class FOneSkyLocalizationServiceCommand& InCommand) override;`
- L378 _public function_ `virtual bool UpdateStates() const override`
- L379 _public prototype_ `void Query_HttpRequestComplete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded);`
- L382 _public member_ `FOneSkyLocalizationServiceCommand* Command;`
- L385 _public member_ `FOneSkyShowProjectResponse OutShowProjectResponse;` — Response to the command

#### class `FOneSkyCreateProjectOperation`  
`class FOneSkyCreateProjectOperation : public ILocalizationServiceOperation`  
_L397-460_
- inherits: `ILocalizationServiceOperation`
- desc: Operation used to create a project in one sky
- L401 _public function_ `virtual FName GetName() const override` — ILocalizationServiceOperation interface
- L406 _public function_ `virtual FText GetInProgressString() const override`
- L411 _public function_ `FOneSkyCreateProjectOperation() : InProjectGroupId(-1), InProjectType(""), InProjectName(""), InProjectDescription("")`
- L413 _public function_ `FString GetInProjectGroupName()`
- L418 _public function_ `void SetInProjectGroupName(FString NewProjectName)`
- L423 _public function_ `FString GetInProjectDescription()`
- L428 _public function_ `void SetInInProjectDescription(FString NewProjectDescription)`
- L433 _public function_ `FString GetInProjectType()`
- L438 _public function_ `void SetInInProjectType(FString NewProjectType)`
- L443 _public function_ `int32 GetInProjectGroupId()`
- L448 _public function_ `void SetInProjectGroupId(int32 NewProjectGroupId)`
- L455 _protected member_ `int32 InProjectGroupId;` — Project Group this project will belong to
- L456 _protected member_ `FString InProjectType;` — See https://github.com/onesky/api-documentation-platform/blob/master/resources/project_type.md
- L457 _protected member_ `FString InProjectName;`
- L458 _protected member_ `FString InProjectDescription;`

#### class `FOneSkyCreateProjectWorker`  
`class FOneSkyCreateProjectWorker : public IOneSkyLocalizationServiceWorker`  
_L462-477_
- inherits: `IOneSkyLocalizationServiceWorker`
- L465 _public function_ `virtual ~FOneSkyCreateProjectWorker()`
- L467 _public prototype_ `virtual FName GetName() const override;` — IOneSkyLocalizationServiceWorker interface
- L468 _public prototype_ `virtual bool Execute(class FOneSkyLocalizationServiceCommand& InCommand) override;`
- L469 _public function_ `virtual bool UpdateStates() const override`
- L470 _public prototype_ `void Query_HttpRequestComplete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded);`
- L473 _public member_ `FOneSkyLocalizationServiceCommand* Command;`
- L476 _public member_ `FOneSkyCreateProjectResponse OutCreateProjectResponse;` — Response to the command

#### class `FOneSkyListProjectLanguagesOperation`  
`class FOneSkyListProjectLanguagesOperation : public ILocalizationServiceOperation`  
_L488-517_
- inherits: `ILocalizationServiceOperation`
- desc: Operation used to list the languages supported by a project in one sky
- L492 _public function_ `virtual FName GetName() const override` — ILocalizationServiceOperation interface
- L497 _public function_ `virtual FText GetInProgressString() const override`
- L502 _public function_ `FOneSkyListProjectLanguagesOperation() : InProjectId(-1)`
- L504 _public function_ `int32 GetInProjectId()`
- L509 _public function_ `void SetInProjectId(int32 NewProjectGroupId)`
- L516 _protected member_ `int32 InProjectId;`

#### class `FOneSkyListProjectLanguagesWorker`  
`class FOneSkyListProjectLanguagesWorker : public IOneSkyLocalizationServiceWorker`  
_L519-534_
- inherits: `IOneSkyLocalizationServiceWorker`
- L522 _public function_ `virtual ~FOneSkyListProjectLanguagesWorker()`
- L524 _public prototype_ `virtual FName GetName() const override;` — IOneSkyLocalizationServiceWorker interface
- L525 _public prototype_ `virtual bool Execute(class FOneSkyLocalizationServiceCommand& InCommand) override;`
- L526 _public function_ `virtual bool UpdateStates() const override`
- L527 _public prototype_ `void Query_HttpRequestComplete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded);`
- L530 _public member_ `FOneSkyLocalizationServiceCommand* Command;`
- L533 _public member_ `FOneSkyListProjectLanguagesResponse OutListProjectLanguagesResponse;` — Response to the command

#### class `FOneSkyTranslationStatusOperation`  
`class FOneSkyTranslationStatusOperation : public ILocalizationServiceOperation`  
_L544-606_
- inherits: `ILocalizationServiceOperation`
- desc: Operation used to list the languages supported by a project in one sky
- L548 _public function_ `virtual FName GetName() const override` — ILocalizationServiceOperation interface
- L553 _public function_ `virtual FText GetInProgressString() const override`
- L558 _public function_ `FOneSkyTranslationStatusOperation() : InProjectId(-1)`
- L560 _public function_ `int32 GetInProjectId()`
- L565 _public function_ `void SetInProjectId(int32 NewProjectGroupId)`
- L570 _public function_ `FString GetInFileName()`
- L575 _public function_ `void SetInFileName(FString NewFileName)`
- L580 _public function_ `FString GetInLocale()`
- L585 _public function_ `void SetInLocale(FString NewLocale)`
- L590 _public function_ `FString GetOutPercentComplete()`
- L595 _public function_ `void SetOutPercentComplete(FString NewOutPercentComplete)`
- L602 _protected member_ `int32 InProjectId;`
- L603 _protected member_ `FString InFileName;`
- L604 _protected member_ `FString InLocale;`
- L605 _protected member_ `FString OutPercentComplete;`

#### class `FOneSkyTranslationStatusWorker`  
`class FOneSkyTranslationStatusWorker : public IOneSkyLocalizationServiceWorker`  
_L608-623_
- inherits: `IOneSkyLocalizationServiceWorker`
- L611 _public function_ `virtual ~FOneSkyTranslationStatusWorker()`
- L613 _public prototype_ `virtual FName GetName() const override;` — IOneSkyLocalizationServiceWorker interface
- L614 _public prototype_ `virtual bool Execute(class FOneSkyLocalizationServiceCommand& InCommand) override;`
- L615 _public function_ `virtual bool UpdateStates() const override`
- L616 _public prototype_ `void Query_HttpRequestComplete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded);`
- L619 _public member_ `FOneSkyLocalizationServiceCommand* Command;`
- L622 _public member_ `FOneSkyTranslationStatusResponse OutTranslationStatusResponse;` — Response to the command

#### class `FOneSkyTranslationExportWorker`  
`class FOneSkyTranslationExportWorker : public IOneSkyLocalizationServiceWorker`  
_L630-645_
- inherits: `IOneSkyLocalizationServiceWorker`
- L633 _public function_ `virtual ~FOneSkyTranslationExportWorker()`
- L635 _public prototype_ `virtual FName GetName() const override;` — IOneSkyLocalizationServiceWorker interface
- L636 _public prototype_ `virtual bool Execute(class FOneSkyLocalizationServiceCommand& InCommand) override;`
- L637 _public function_ `virtual bool UpdateStates() const override`
- L638 _public prototype_ `void Query_HttpRequestComplete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded);`
- L641 _public member_ `FOneSkyLocalizationServiceCommand* Command;`

#### class `FOneSkyListUploadedFilesOperation`  
`class FOneSkyListUploadedFilesOperation : public ILocalizationServiceOperation`  
_L655-706_
- inherits: `ILocalizationServiceOperation`
- desc: Operation used to list uploaded files for a project in one sky
- L659 _public function_ `virtual FName GetName() const override` — ILocalizationServiceOperation interface
- L664 _public function_ `virtual FText GetInProgressString() const override`
- L669 _public function_ `FOneSkyListUploadedFilesOperation() : InProjectId(-1), InStartPage(-1), InItemsPerPage(-1)`
- L671 _public function_ `void SetInStartPage(int32 NewStartPage)`
- L676 _public function_ `int32 GetInStartPage()`
- L681 _public function_ `void SetInItemsPerPage(int32 NewItemsPerPage)`
- L686 _public function_ `int32 GetInItemsPerPage()`
- L691 _public function_ `int32 GetInProjectId()`
- L696 _public function_ `void SetInProjectId(int32 NewProjectGroupId)`
- L703 _protected member_ `int32 InProjectId;`
- L704 _protected member_ `int32 InStartPage;`
- L705 _protected member_ `int32 InItemsPerPage;`

#### class `FOneSkyListUploadedFilesWorker`  
`class FOneSkyListUploadedFilesWorker : public IOneSkyLocalizationServiceWorker`  
_L708-723_
- inherits: `IOneSkyLocalizationServiceWorker`
- L711 _public function_ `virtual ~FOneSkyListUploadedFilesWorker()`
- L713 _public prototype_ `virtual FName GetName() const override;` — IOneSkyLocalizationServiceWorker interface
- L714 _public prototype_ `virtual bool Execute(class FOneSkyLocalizationServiceCommand& InCommand) override;`
- L715 _public function_ `virtual bool UpdateStates() const override`
- L716 _public prototype_ `void Query_HttpRequestComplete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded);`
- L719 _public member_ `FOneSkyLocalizationServiceCommand* Command;`
- L722 _public member_ `FOneSkyListUploadedFilesResponse OutListUploadedFilesResponse;` — Response to the  command

#### class `FOneSkyUploadFileWorker`  
`class FOneSkyUploadFileWorker : public IOneSkyLocalizationServiceWorker`  
_L730-745_
- inherits: `IOneSkyLocalizationServiceWorker`
- L733 _public function_ `virtual ~FOneSkyUploadFileWorker()`
- L735 _public prototype_ `virtual FName GetName() const override;` — IOneSkyLocalizationServiceWorker interface
- L736 _public prototype_ `virtual bool Execute(class FOneSkyLocalizationServiceCommand& InCommand) override;`
- L737 _public function_ `virtual bool UpdateStates() const override`
- L738 _public prototype_ `void Query_HttpRequestComplete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded);`
- L741 _public member_ `FOneSkyLocalizationServiceCommand* Command;`
- L744 _public member_ `FOneSkyUploadFileResponse OutUploadFileResponse;` — Response to the  command

#### class `FOneSkyListPhraseCollectionsOperation`  
`class FOneSkyListPhraseCollectionsOperation : public ILocalizationServiceOperation`  
_L755-806_
- inherits: `ILocalizationServiceOperation`
- desc: Operation used to list phrase collections for a project in one sky
- L759 _public function_ `virtual FName GetName() const override` — ILocalizationServiceOperation interface
- L764 _public function_ `virtual FText GetInProgressString() const override`
- L769 _public function_ `FOneSkyListPhraseCollectionsOperation() : InProjectId(-1), InPage(-1), InItemsPerPage(-1)`
- L771 _public function_ `void SetInPage(int32 NewPage)`
- L776 _public function_ `int32 GetInPage()`
- L781 _public function_ `void SetInItemsPerPage(int32 NewItemsPerPage)`
- L786 _public function_ `int32 GetInItemsPerPage()`
- L791 _public function_ `int32 GetInProjectId()`
- L796 _public function_ `void SetInProjectId(int32 NewProjectGroupId)`
- L803 _protected member_ `int32 InProjectId;`
- L804 _protected member_ `int32 InPage;`
- L805 _protected member_ `int32 InItemsPerPage;`

#### class `FOneSkyListPhraseCollectionsWorker`  
`class FOneSkyListPhraseCollectionsWorker : public IOneSkyLocalizationServiceWorker`  
_L808-823_
- inherits: `IOneSkyLocalizationServiceWorker`
- L811 _public function_ `virtual ~FOneSkyListPhraseCollectionsWorker()`
- L813 _public prototype_ `virtual FName GetName() const override;` — IOneSkyLocalizationServiceWorker interface
- L814 _public prototype_ `virtual bool Execute(class FOneSkyLocalizationServiceCommand& InCommand) override;`
- L815 _public function_ `virtual bool UpdateStates() const override`
- L816 _public prototype_ `void Query_HttpRequestComplete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded);`
- L819 _public member_ `FOneSkyLocalizationServiceCommand* Command;`
- L822 _public member_ `FOneSkyListPhraseCollectionsResponse OutListPhraseCollectionsResponse;` — Response to the  command

#### class `FOneSkyShowImportTaskOperation`  
`class FOneSkyShowImportTaskOperation : public ILocalizationServiceOperation`  
_L833-895_
- inherits: `ILocalizationServiceOperation`
- desc: Operation used to show a project in one sky
- L837 _public function_ `virtual FName GetName() const override` — ILocalizationServiceOperation interface
- L842 _public function_ `virtual FText GetInProgressString() const override`
- L847 _public function_ `FOneSkyShowImportTaskOperation() : InProjectId(-1)`
- L849 _public function_ `int32 GetInProjectId()`
- L854 _public function_ `void SetInProjectId(int32 NewProjectId)`
- L859 _public function_ `int32 GetInImportId()`
- L864 _public function_ `void SetInImportId(int32 NewImportId)`
- L869 _public function_ `int32 GetInExecutionDelayInSeconds()`
- L874 _public function_ `void SetInExecutionDelayInSeconds(int32 NewInExecutionDelayInSeconds)`
- L879 _public function_ `FDateTime GetInCreationTimestamp()`
- L884 _public function_ `void SetInCreationTimestamp(FDateTime NewInCreationTimestamp)`
- L891 _protected member_ `int32 InProjectId;`
- L892 _protected member_ `int32 InImportId;`
- L893 _protected member_ `int32 InExecutionDelayInSeconds;`
- L894 _protected member_ `FDateTime InCreationTimestamp;`

#### class `FOneSkyShowImportTaskWorker`  
`class FOneSkyShowImportTaskWorker : public IOneSkyLocalizationServiceWorker`  
_L897-912_
- inherits: `IOneSkyLocalizationServiceWorker`
- L900 _public function_ `virtual ~FOneSkyShowImportTaskWorker()`
- L902 _public prototype_ `virtual FName GetName() const override;` — IOneSkyLocalizationServiceWorker interface
- L903 _public prototype_ `virtual bool Execute(class FOneSkyLocalizationServiceCommand& InCommand) override;`
- L904 _public function_ `virtual bool UpdateStates() const override`
- L905 _public prototype_ `void Query_HttpRequestComplete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded);`
- L908 _public member_ `FOneSkyLocalizationServiceCommand* Command;`
- L911 _public member_ `FOneSkyShowImportTaskResponse OutShowImportTaskResponse;` — Response to the command

#### Free symbols / members of external scopes

- L10 _macro_ `#define LOCTEXT_NAMESPACE "LocalizationService"`
- L16 _typedef_ `typedef TSharedPtr<IHttpRequest, ESPMode::ThreadSafe> FHttpRequestPtr;`
- L17 _typedef_ `typedef TSharedPtr<class IHttpResponse, ESPMode::ThreadSafe> FHttpResponsePtr;`

### `Plugins/Developer/OneSkyLocalizationService/Source/OneSkyLocalizationService/Private/OneSkyLocalizationServiceProvider.h` (Private)


#### struct `FLocalizationServiceTranslationIdentifierKeyFuncs`  
`template <typename ValueType> struct FLocalizationServiceTranslationIdentifierKeyFuncs : BaseKeyFuncs < TPair< FLocalizationServiceTranslationIdentifier, ValueType>, FLocalizationServiceTranslationIdentifier, false >`  
_L24-58_
- inherits: `BaseKeyFuncs<TPair<FLocalizationServiceTranslationIdentifier,ValueType>,FLocalizationServiceTranslationIdentifier,false>`
- desc: Define how the TMap from FLocalizationServiceTranslationIdentifier works
- L29 _public typedef_ `> Super;`
- L30 _public typedef_ `typedef typename Super::ElementInitType ElementInitType;`
- L31 _public typedef_ `typedef typename Super::KeyInitType KeyInitType;`
- L32 _public function_ `static FORCEINLINE KeyInitType GetSetKey(ElementInitType Element)`
- L36 _public function_ `static FORCEINLINE bool Matches(const FLocalizationServiceTranslationIdentifier& A, const FLocalizationServiceTranslationIdentifier& B)`
- L44 _public function_ `static FORCEINLINE uint32 GetKeyHash(const FLocalizationServiceTranslationIdentifier& Key)`

#### struct `FShowImportTaskQueueItem`  
`struct FShowImportTaskQueueItem`  
_L61-67_
- desc: Struct representing a show import task in our queue
- L63 _public member_ `int32 ProjectId;`
- L64 _public member_ `int32 ImportId;`
- L65 _public member_ `FDateTime CreatedTimestamp;`
- L66 _public member_ `int32 ExecutionDelayInSeconds;`

#### class `FOneSkyLocalizationServiceProvider`  
`class FOneSkyLocalizationServiceProvider : public ILocalizationServiceProvider`  
_L69-198_
- inherits: `ILocalizationServiceProvider`
- L73 _public function_ `FOneSkyLocalizationServiceProvider() : bServerAvailable(false) , PersistentConnection(NULL)` — Constructor
- L80 _public prototype_ `virtual void Init(bool bForceConnection = true) override;` — ILocalizationServiceProvider implementation
- L81 _public prototype_ `virtual void Close() override;`
- L82 _public prototype_ `virtual FText GetStatusText() const override;`
- L83 _public prototype_ `virtual bool IsEnabled() const override;`
- L84 _public prototype_ `virtual bool IsAvailable() const override;`
- L85 _public prototype_ `virtual const FName& GetName(void) const override;`
- L86 _public prototype_ `virtual const FText GetDisplayName() const override;`
- L87 _public prototype_ `virtual ELocalizationServiceOperationCommandResult::Type GetState(const TArray<FLocalizationServiceTranslationIdentifier>& InTranslationIds, TArray< TSharedRef<ILocalizationServiceState, ESPMode::ThreadSafe> >& OutState, ELocalizationServiceCacheUsage::Type InStateCacheUsage) override;`
- L88 _public prototype_ `virtual ELocalizationServiceOperationCommandResult::Type Execute(const TSharedRef<ILocalizationServiceOperation, ESPMode::ThreadSafe>& InOperation, const TArray<FLocalizationServiceTranslationIdentifier>& InTranslationIds, ELocalizationServiceOperationConcurrency::Type InConcurrency = ELocalizationServiceOperationConcurrency::Synchronous, const FLocalizationServiceOperationComplete& InOperationCompleteDelegate = FLocalizationServiceOperationComplete()) override;`
- L89 _public prototype_ `virtual bool CanCancelOperation( const TSharedRef<ILocalizationServiceOperation, ESPMode::ThreadSafe>& InOperation ) const override;`
- L90 _public prototype_ `virtual void CancelOperation( const TSharedRef<ILocalizationServiceOperation, ESPMode::ThreadSafe>& InOperation ) override;`
- L91 _public prototype_ `virtual void Tick() override;`
- L93 _public prototype_ `virtual void CustomizeSettingsDetails(IDetailCategoryBuilder& DetailCategoryBuilder) const override;`
- L94 _public prototype_ `virtual void CustomizeTargetDetails(IDetailCategoryBuilder& DetailCategoryBuilder, TWeakObjectPtr<ULocalizationTarget> LocalizationTarget) const override;`
- L95 _public prototype_ `virtual void CustomizeTargetToolbar(TSharedRef<FExtender>& MenuExtender, TWeakObjectPtr<ULocalizationTarget> LocalizationTarget) const override;`
- L96 _public prototype_ `virtual void CustomizeTargetSetToolbar(TSharedRef<FExtender>& MenuExtender, TWeakObjectPtr<ULocalizationTargetSet> ULocalizationTargetSet) const override;`
- L103 _public prototype_ `void RegisterWorker( const FName& InName, const FGetOneSkyLocalizationServiceWorker& InDelegate );` — Register a worker with the provider. This is used internally so the provider can maintain a map of all available operations.
- L106 _public prototype_ `TSharedRef<FOneSkyLocalizationServiceState, ESPMode::ThreadSafe> GetStateInternal(const FLocalizationServiceTranslationIdentifier& InTranslationId);` — Helper function used to update state cache
- L113 _public prototype_ `bool EstablishPersistentConnection();` — Connects to the Localization service server if the persistent connection is not already established. @return true if the connection is established or became established and false if the connection failed.
- L116 _public function_ `class FOneSkyConnection* GetPersistentConnection()` — Get the persistent connection, if any
- L122 _public function_ `void EnqueShowImportTask(FShowImportTaskQueueItem QueueItem)` — Enqueue a show import task for later exection
- L130 _private prototype_ `TSharedPtr<class IOneSkyLocalizationServiceWorker, ESPMode::ThreadSafe> CreateWorker(const FName& InOperationName) const;` — Helper function used to create a worker for a particular operation
- L135 _private prototype_ `void OutputCommandMessages(const class FOneSkyLocalizationServiceCommand& InCommand) const;` — Logs any messages that a command needs to output.
- L142 _private prototype_ `ELocalizationServiceOperationCommandResult::Type ExecuteSynchronousCommand(class FOneSkyLocalizationServiceCommand& InCommand, const FText& Task, bool bSuppressResponseMsg);` — Helper function for running command 'synchronously'. This really doesn't execute synchronously; rather it adds the command to the queue & does not return until the command is completed.
- L147 _private prototype_ `ELocalizationServiceOperationCommandResult::Type IssueCommand(class FOneSkyLocalizationServiceCommand& InCommand, const bool bSynchronous);` — Run a command synchronously or asynchronously.
- L150 _private prototype_ `void AddTargetToolbarButtons(FToolBarBuilder& ToolbarBuilder, TWeakObjectPtr<ULocalizationTarget> InLocalizationTarget, TSharedRef< FUICommandList > CommandList);` — Add the buttons to the toolbar for this localization target
- L153 _private prototype_ `void AddTargetSetToolbarButtons(FToolBarBuilder& ToolbarBuilder, TWeakObjectPtr<ULocalizationTargetSet> InLocalizationTargetSet, TSharedRef< FUICommandList > CommandList);` — Add the buttons to the toolbar for this set of localization targets
- L156 _private prototype_ `void ImportAllCulturesForTargetFromOneSky(TWeakObjectPtr<ULocalizationTarget> LocalizationTarget, bool bIsTargetSet);` — Download and import all translations for all cultures for the specified target from OneSky
- L159 _private prototype_ `void ImportCultureForTargetFromOneSky_Callback(const FLocalizationServiceOperationRef& Operation, ELocalizationServiceOperationCommandResult::Type Result, bool yes);` — Called when done downloading localization data for culture for a target from OneSky
- L162 _private prototype_ `void ExportAllCulturesForTargetToOneSky(TWeakObjectPtr<ULocalizationTarget> LocalizationTarget, bool bIsTargetSet);` — Export and upload all cultures for a localization target to OneSky
- L165 _private prototype_ `void ExportCultureForTargetToOneSky_Callback(const FLocalizationServiceOperationRef& Operation, ELocalizationServiceOperationCommandResult::Type Result, bool bIsTargetSet);` — Called when done uploading localization data for a culture for a target from OnSky
- L168 _private prototype_ `void ImportAllTargetsForTargetSetFromOneSky(TWeakObjectPtr<ULocalizationTargetSet> LocalizationTargetSet);` — Download and import all translations for all cultures for all targets for the specified target set from OneSky
- L171 _private prototype_ `void ExportAllTargetsForTargetSetToOneSky(TWeakObjectPtr<ULocalizationTargetSet> LocalizationTargetSet);` — Export and upload all cultures for all targets for a localization target set to OneSky
- L176 _private member_ `bool bServerAvailable;` — Indicates if Localization service integration is available or not.
- L179 _private member_ `class FOneSkyConnection* PersistentConnection;` — A pointer to the persistent P4 connection for synchronous operations
- L182 _private member_ `TMap<FLocalizationServiceTranslationIdentifier, TSharedRef<class FOneSkyLocalizationServiceState, ESPMode::ThreadSafe>, FDefaultSetAllocator, FLocalizationServiceTranslationIdentifierKeyFuncs<TSharedRef<class FOneSkyLocalizationServiceState, ESPMode::ThreadSafe>> > StateCache;` — State cache
- L185 _private member_ `TMap<FName, FGetOneSkyLocalizationServiceWorker> WorkersMap;` — The currently registered Localization service operations
- L188 _private member_ `TArray < FOneSkyLocalizationServiceCommand* > CommandQueue;` — Queue for commands given by the main thread
- L191 _private member_ `TQueue < FShowImportTaskQueueItem, EQueueMode::Mpsc > ShowImportTaskQueue;` — Queue for import status tasks
- L194 _private member_ `TArray < FString > FilesDownloadingForImportFromOneSky;` — Array of file names being downloaded for import from OneSky
- L197 _private member_ `TArray < FString > FilesUploadingForExportToOneSky;` — Array of file names being uploaded for export into OneSky

#### Free symbols / members of external scopes

- L20 _delegate_ `DECLARE_DELEGATE_RetVal(FOneSkyLocalizationServiceWorkerRef, FGetOneSkyLocalizationServiceWorker)`

### `Plugins/Developer/OneSkyLocalizationService/Source/OneSkyLocalizationService/Private/OneSkyLocalizationServiceResponseTypes.h` (Private)


#### struct `FOneSkyListProjectGroupsResponseMeta`  
`struct FOneSkyListProjectGroupsResponseMeta`  
_L11-49_
- reflection: `USTRUCT()`
- L16 _public member_ `int32 status;` — `UPROPERTY()`
- L19 _public member_ `int32 record_count;` — `UPROPERTY()`
- L22 _public member_ `int32 page_count;` — `UPROPERTY()`
- L25 _public member_ `FString next_page;` — `UPROPERTY()`
- L28 _public member_ `FString prev_page;` — `UPROPERTY()`
- L31 _public member_ `FString first_page;` — `UPROPERTY()`
- L34 _public member_ `FString last_page;` — `UPROPERTY()`
- L37 _public function_ `FOneSkyListProjectGroupsResponseMeta() : status(-1) , record_count(-1) , page_count(-1) , next_page(TEXT("")) , prev_page(TEXT("")) , first_page(TEXT("")) , last_page(TEXT(""))` — Default constructor.
- L48 _public function_ `FOneSkyListProjectGroupsResponseMeta(ENoInit)` — Creates an uninitialized instance.

#### struct `FOneSkyListProjectGroupsResponseDataItem`  
`struct FOneSkyListProjectGroupsResponseDataItem`  
_L53-71_
- reflection: `USTRUCT()`
- L58 _public member_ `FString id;` — `UPROPERTY()`
- L61 _public member_ `FString name;` — `UPROPERTY()`
- L64 _public function_ `FOneSkyListProjectGroupsResponseDataItem() : id("-1") , name(TEXT(""))` — Default constructor.
- L70 _public function_ `FOneSkyListProjectGroupsResponseDataItem(ENoInit)` — Creates an uninitialized instance.

#### struct `FOneSkyListProjectGroupsResponse`  
`struct FOneSkyListProjectGroupsResponse`  
_L78-96_
- reflection: `USTRUCT()`
- desc: Response from a List Project Groups query on OneSky //https://github.com/onesky/api-documentation-platform/blob/master/resources/project_group.md
- L83 _public member_ `FOneSkyListProjectGroupsResponseMeta meta;` — `UPROPERTY()`
- L86 _public member_ `TArray<FOneSkyListProjectGroupsResponseDataItem> data;` — `UPROPERTY()`
- L89 _public function_ `FOneSkyListProjectGroupsResponse() : meta() , data()` — Default constructor.
- L95 _public function_ `FOneSkyListProjectGroupsResponse(ENoInit)` — Creates an uninitialized instance.

#### struct `FOneSkyShowProjectGroupResponseMeta`  
`struct FOneSkyShowProjectGroupResponseMeta`  
_L104-118_
- reflection: `USTRUCT()`
- L109 _public member_ `int32 status;` — `UPROPERTY()`
- L112 _public function_ `FOneSkyShowProjectGroupResponseMeta() : status(-1)` — Default constructor.
- L117 _public function_ `FOneSkyShowProjectGroupResponseMeta(ENoInit)` — Creates an uninitialized instance.

#### struct `FOneSkyShowProjectGroupResponseData`  
`struct FOneSkyShowProjectGroupResponseData`  
_L121-147_
- reflection: `USTRUCT()`
- L126 _public member_ `FString id;` — `UPROPERTY()`
- L129 _public member_ `FString name;` — `UPROPERTY()`
- L132 _public member_ `int32 description;` — `UPROPERTY()`
- L135 _public member_ `FString project_count;` — `UPROPERTY()`
- L138 _public function_ `FOneSkyShowProjectGroupResponseData() : id("-1") , name(TEXT("")) , description(-1) , project_count("-1")` — Default constructor.
- L146 _public function_ `FOneSkyShowProjectGroupResponseData(ENoInit)` — Creates an uninitialized instance.

#### struct `FOneSkyShowProjectGroupResponse`  
`struct FOneSkyShowProjectGroupResponse`  
_L154-172_
- reflection: `USTRUCT()`
- desc: Response from a Show Project Group query on OneSky //https://github.com/onesky/api-documentation-platform/blob/master/resources/project_group.md
- L159 _public member_ `FOneSkyShowProjectGroupResponseMeta meta;` — `UPROPERTY()`
- L162 _public member_ `FOneSkyShowProjectGroupResponseData data;` — `UPROPERTY()`
- L165 _public function_ `FOneSkyShowProjectGroupResponse() : meta() , data()` — Default constructor.
- L171 _public function_ `FOneSkyShowProjectGroupResponse(ENoInit)` — Creates an uninitialized instance.

#### struct `FOneSkyCreateProjectGroupResponseMeta`  
`struct FOneSkyCreateProjectGroupResponseMeta`  
_L180-194_
- reflection: `USTRUCT()`
- L185 _public member_ `int32 status;` — `UPROPERTY()`
- L188 _public function_ `FOneSkyCreateProjectGroupResponseMeta() : status(-1)` — Default constructor.
- L193 _public function_ `FOneSkyCreateProjectGroupResponseMeta(ENoInit)` — Creates an uninitialized instance.

#### struct `FOneSkyCreateProjectGroupResponseBaseLanguage`  
`struct FOneSkyCreateProjectGroupResponseBaseLanguage`  
_L197-227_
- reflection: `USTRUCT()`
- L202 _public member_ `FString code;` — `UPROPERTY()`
- L205 _public member_ `FString english_name;` — `UPROPERTY()`
- L208 _public member_ `FString local_name;` — `UPROPERTY()`
- L211 _public member_ `FString locale;` — `UPROPERTY()`
- L214 _public member_ `FString region;` — `UPROPERTY()`
- L217 _public function_ `FOneSkyCreateProjectGroupResponseBaseLanguage() : code("") , english_name("") , local_name("") , locale("") , region("")` — Default constructor.
- L226 _public function_ `FOneSkyCreateProjectGroupResponseBaseLanguage(ENoInit)` — Creates an uninitialized instance.

#### struct `FOneSkyCreateProjectGroupResponseData`  
`struct FOneSkyCreateProjectGroupResponseData`  
_L230-252_
- reflection: `USTRUCT()`
- L235 _public member_ `int32 id;` — `UPROPERTY()`
- L238 _public member_ `FString name;` — `UPROPERTY()`
- L241 _public member_ `FOneSkyCreateProjectGroupResponseBaseLanguage base_language;` — `UPROPERTY()`
- L244 _public function_ `FOneSkyCreateProjectGroupResponseData() : id(-1) , name(TEXT("")) , base_language()` — Default constructor.
- L251 _public function_ `FOneSkyCreateProjectGroupResponseData(ENoInit)` — Creates an uninitialized instance.

#### struct `FOneSkyCreateProjectGroupResponse`  
`struct FOneSkyCreateProjectGroupResponse`  
_L259-277_
- reflection: `USTRUCT()`
- desc: Response from a Create Project Group query on OneSky //https://github.com/onesky/api-documentation-platform/blob/master/resources/project_group.md
- L264 _public member_ `FOneSkyCreateProjectGroupResponseMeta meta;` — `UPROPERTY()`
- L267 _public member_ `FOneSkyCreateProjectGroupResponseData data;` — `UPROPERTY()`
- L270 _public function_ `FOneSkyCreateProjectGroupResponse() : meta() , data()` — Default constructor.
- L276 _public function_ `FOneSkyCreateProjectGroupResponse(ENoInit)` — Creates an uninitialized instance.

#### struct `FOneSkyListProjectGroupLanguagesResponseMeta`  
`struct FOneSkyListProjectGroupLanguagesResponseMeta`  
_L285-303_
- reflection: `USTRUCT()`
- L290 _public member_ `int32 status;` — `UPROPERTY()`
- L293 _public member_ `int32 record_count;` — `UPROPERTY()`
- L296 _public function_ `FOneSkyListProjectGroupLanguagesResponseMeta() : status(-1) , record_count(-1)` — Default constructor.
- L302 _public function_ `FOneSkyListProjectGroupLanguagesResponseMeta(ENoInit)` — Creates an uninitialized instance.

#### struct `FOneSkyListProjectGroupLanguagesResponseDataItem`  
`struct FOneSkyListProjectGroupLanguagesResponseDataItem`  
_L306-340_
- reflection: `USTRUCT()`
- L311 _public member_ `FString code;` — `UPROPERTY()`
- L314 _public member_ `FString english_name;` — `UPROPERTY()`
- L317 _public member_ `FString local_name;` — `UPROPERTY()`
- L320 _public member_ `FString locale;` — `UPROPERTY()`
- L323 _public member_ `FString region;` — `UPROPERTY()`
- L326 _public member_ `bool is_base_language;` — `UPROPERTY()`
- L329 _public function_ `FOneSkyListProjectGroupLanguagesResponseDataItem() : code("") , english_name("") , local_name("") , locale("") , region("") , is_base_language(false)` — Default constructor.
- L339 _public function_ `FOneSkyListProjectGroupLanguagesResponseDataItem(ENoInit)` — Creates an uninitialized instance.

#### struct `FOneSkyListProjectGroupLanguagesResponse`  
`struct FOneSkyListProjectGroupLanguagesResponse`  
_L347-365_
- reflection: `USTRUCT()`
- desc: Response from a List Project Group Languages query on OneSky //https://github.com/onesky/api-documentation-platform/blob/master/resources/project_group.md
- L352 _public member_ `FOneSkyListProjectGroupLanguagesResponseMeta meta;` — `UPROPERTY()`
- L355 _public member_ `TArray<FOneSkyListProjectGroupLanguagesResponseDataItem> data;` — `UPROPERTY()`
- L358 _public function_ `FOneSkyListProjectGroupLanguagesResponse() : meta() , data()` — Default constructor.
- L364 _public function_ `FOneSkyListProjectGroupLanguagesResponse(ENoInit)` — Creates an uninitialized instance.

#### struct `FOneSkyListProjectsInGroupResponseMeta`  
`struct FOneSkyListProjectsInGroupResponseMeta`  
_L373-391_
- reflection: `USTRUCT()`
- L378 _public member_ `int32 status;` — `UPROPERTY()`
- L381 _public member_ `int32 record_count;` — `UPROPERTY()`
- L384 _public function_ `FOneSkyListProjectsInGroupResponseMeta() : status(-1) , record_count(-1)` — Default constructor.
- L390 _public function_ `FOneSkyListProjectsInGroupResponseMeta(ENoInit)` — Creates an uninitialized instance.

#### struct `FOneSkyListProjectsInGroupResponseDataItem`  
`struct FOneSkyListProjectsInGroupResponseDataItem`  
_L394-412_
- reflection: `USTRUCT()`
- L399 _public member_ `int32 id;` — `UPROPERTY()`
- L402 _public member_ `FString name;` — `UPROPERTY()`
- L405 _public function_ `FOneSkyListProjectsInGroupResponseDataItem() : id(-1) , name(TEXT(""))` — Default constructor.
- L411 _public function_ `FOneSkyListProjectsInGroupResponseDataItem(ENoInit)` — Creates an uninitialized instance.

#### struct `FOneSkyListProjectsInGroupResponse`  
`struct FOneSkyListProjectsInGroupResponse`  
_L419-437_
- reflection: `USTRUCT()`
- desc: Response from a List Projects in Group query on OneSky //https://github.com/onesky/api-documentation-platform/blob/master/resources/project.md
- L424 _public member_ `FOneSkyListProjectsInGroupResponseMeta meta;` — `UPROPERTY()`
- L427 _public member_ `TArray<FOneSkyListProjectsInGroupResponseDataItem> data;` — `UPROPERTY()`
- L430 _public function_ `FOneSkyListProjectsInGroupResponse() : meta() , data()` — Default constructor.
- L436 _public function_ `FOneSkyListProjectsInGroupResponse(ENoInit)` — Creates an uninitialized instance.

#### struct `FOneSkyShowProjectResponseMeta`  
`struct FOneSkyShowProjectResponseMeta`  
_L445-459_
- reflection: `USTRUCT()`
- L450 _public member_ `int32 status;` — `UPROPERTY()`
- L453 _public function_ `FOneSkyShowProjectResponseMeta() : status(-1)` — Default constructor.
- L458 _public function_ `FOneSkyShowProjectResponseMeta(ENoInit)` — Creates an uninitialized instance.

#### struct `FOneSkyShowProjectResponseProjectType`  
`struct FOneSkyShowProjectResponseProjectType`  
_L463-481_
- reflection: `USTRUCT()`
- L468 _public member_ `FString code;` — `UPROPERTY()`
- L471 _public member_ `FString name;` — `UPROPERTY()`
- L474 _public function_ `FOneSkyShowProjectResponseProjectType() : code("") , name("")` — Default constructor.
- L480 _public function_ `FOneSkyShowProjectResponseProjectType(ENoInit)` — Creates an uninitialized instance.

#### struct `FOneSkyShowProjectResponseData`  
`struct FOneSkyShowProjectResponseData`  
_L484-517_
- reflection: `USTRUCT()`
- L489 _public member_ `int32 id;` — `UPROPERTY()`
- L492 _public member_ `FString name;` — `UPROPERTY()`
- L495 _public member_ `FString description;` — `UPROPERTY()`
- L498 _public member_ `FOneSkyShowProjectResponseProjectType project_type;` — `UPROPERTY()`
- L501 _public member_ `int32 string_count;` — `UPROPERTY()`
- L504 _public member_ `int32 word_count;` — `UPROPERTY()`
- L507 _public function_ `FOneSkyShowProjectResponseData() : id(-1) , name(TEXT("")) , description("") , string_count(-1) , word_count(-1)` — Default constructor.
- L516 _public function_ `FOneSkyShowProjectResponseData(ENoInit)` — Creates an uninitialized instance.

#### struct `FOneSkyShowProjectResponse`  
`struct FOneSkyShowProjectResponse`  
_L524-542_
- reflection: `USTRUCT()`
- desc: Response from a Show Project query on OneSky //https://github.com/onesky/api-documentation-platform/blob/master/resources/project.md
- L529 _public member_ `FOneSkyShowProjectResponseMeta meta;` — `UPROPERTY()`
- L532 _public member_ `FOneSkyShowProjectResponseData data;` — `UPROPERTY()`
- L535 _public function_ `FOneSkyShowProjectResponse() : meta() , data()` — Default constructor.
- L541 _public function_ `FOneSkyShowProjectResponse(ENoInit)` — Creates an uninitialized instance.

#### struct `FOneSkyCreateProjectResponseMeta`  
`struct FOneSkyCreateProjectResponseMeta`  
_L550-564_
- reflection: `USTRUCT()`
- L555 _public member_ `int32 status;` — `UPROPERTY()`
- L558 _public function_ `FOneSkyCreateProjectResponseMeta() : status(-1)` — Default constructor.
- L563 _public function_ `FOneSkyCreateProjectResponseMeta(ENoInit)` — Creates an uninitialized instance.

#### struct `FOneSkyCreateProjectResponseProjectType`  
`struct FOneSkyCreateProjectResponseProjectType`  
_L568-586_
- reflection: `USTRUCT()`
- L573 _public member_ `FString code;` — `UPROPERTY()`
- L576 _public member_ `FString name;` — `UPROPERTY()`
- L579 _public function_ `FOneSkyCreateProjectResponseProjectType() : code("") , name("")` — Default constructor.
- L585 _public function_ `FOneSkyCreateProjectResponseProjectType(ENoInit)` — Creates an uninitialized instance.

#### struct `FOneSkyCreateProjectResponseData`  
`struct FOneSkyCreateProjectResponseData`  
_L589-614_
- reflection: `USTRUCT()`
- L594 _public member_ `int32 id;` — `UPROPERTY()`
- L597 _public member_ `FString name;` — `UPROPERTY()`
- L600 _public member_ `FString description;` — `UPROPERTY()`
- L603 _public member_ `FOneSkyShowProjectResponseProjectType project_type;` — `UPROPERTY()`
- L606 _public function_ `FOneSkyCreateProjectResponseData() : id(-1) , name(TEXT("")) , description("")` — Default constructor.
- L613 _public function_ `FOneSkyCreateProjectResponseData(ENoInit)` — Creates an uninitialized instance.

#### struct `FOneSkyCreateProjectResponse`  
`struct FOneSkyCreateProjectResponse`  
_L621-639_
- reflection: `USTRUCT()`
- desc: Response from a Create Project query on OneSky //https://github.com/onesky/api-documentation-platform/blob/master/resources/project.md
- L626 _public member_ `FOneSkyCreateProjectResponseMeta meta;` — `UPROPERTY()`
- L629 _public member_ `FOneSkyCreateProjectResponseData data;` — `UPROPERTY()`
- L632 _public function_ `FOneSkyCreateProjectResponse() : meta() , data()` — Default constructor.
- L638 _public function_ `FOneSkyCreateProjectResponse(ENoInit)` — Creates an uninitialized instance.

#### struct `FOneSkyListProjectLanguagesResponseMeta`  
`struct FOneSkyListProjectLanguagesResponseMeta`  
_L647-665_
- reflection: `USTRUCT()`
- L652 _public member_ `int32 status;` — `UPROPERTY()`
- L655 _public member_ `int32 record_count;` — `UPROPERTY()`
- L658 _public function_ `FOneSkyListProjectLanguagesResponseMeta() : status(-1) , record_count(-1)` — Default constructor.
- L664 _public function_ `FOneSkyListProjectLanguagesResponseMeta(ENoInit)` — Creates an uninitialized instance.

#### struct `FOneSkyListProjectLanguagesResponseDataItem`  
`struct FOneSkyListProjectLanguagesResponseDataItem`  
_L668-710_
- reflection: `USTRUCT()`
- L673 _public member_ `FString code;` — `UPROPERTY()`
- L676 _public member_ `FString english_name;` — `UPROPERTY()`
- L679 _public member_ `FString local_name;` — `UPROPERTY()`
- L682 _public member_ `FString locale;` — `UPROPERTY()`
- L685 _public member_ `FString region;` — `UPROPERTY()`
- L688 _public member_ `bool is_base_language;` — `UPROPERTY()`
- L691 _public member_ `bool is_ready_to_publish;` — `UPROPERTY()`
- L694 _public member_ `FString translation_progress;` — `UPROPERTY()`
- L697 _public function_ `FOneSkyListProjectLanguagesResponseDataItem() : code("") , english_name("") , local_name("") , locale("") , region("") , is_base_language(false) , is_ready_to_publish(false) , translation_progress("")` — Default constructor.
- L709 _public function_ `FOneSkyListProjectLanguagesResponseDataItem(ENoInit)` — Creates an uninitialized instance.

#### struct `FOneSkyListProjectLanguagesResponse`  
`struct FOneSkyListProjectLanguagesResponse`  
_L717-735_
- reflection: `USTRUCT()`
- desc: Response from a List Project Languages query on OneSky //https://github.com/onesky/api-documentation-platform/blob/master/resources/project.md
- L722 _public member_ `FOneSkyListProjectLanguagesResponseMeta meta;` — `UPROPERTY()`
- L725 _public member_ `TArray<FOneSkyListProjectLanguagesResponseDataItem> data;` — `UPROPERTY()`
- L728 _public function_ `FOneSkyListProjectLanguagesResponse() : meta() , data()` — Default constructor.
- L734 _public function_ `FOneSkyListProjectLanguagesResponse(ENoInit)` — Creates an uninitialized instance.

#### struct `FOneSkyTranslationStatusResponseMeta`  
`struct FOneSkyTranslationStatusResponseMeta`  
_L743-757_
- reflection: `USTRUCT()`
- L748 _public member_ `int32 status;` — `UPROPERTY()`
- L751 _public function_ `FOneSkyTranslationStatusResponseMeta() : status(-1)` — Default constructor.
- L756 _public function_ `FOneSkyTranslationStatusResponseMeta(ENoInit)` — Creates an uninitialized instance.

#### struct `FOneSkyTranslationStatusResponseLocale`  
`struct FOneSkyTranslationStatusResponseLocale`  
_L761-791_
- reflection: `USTRUCT()`
- L766 _public member_ `FString code;` — `UPROPERTY()`
- L769 _public member_ `FString english_name;` — `UPROPERTY()`
- L772 _public member_ `FString local_name;` — `UPROPERTY()`
- L775 _public member_ `FString locale;` — `UPROPERTY()`
- L778 _public member_ `FString region;` — `UPROPERTY()`
- L781 _public function_ `FOneSkyTranslationStatusResponseLocale() : code("") , english_name("") , local_name("") , locale("") , region("")` — Default constructor.
- L790 _public function_ `FOneSkyTranslationStatusResponseLocale(ENoInit)` — Creates an uninitialized instance.

#### struct `FOneSkyTranslationStatusResponseData`  
`struct FOneSkyTranslationStatusResponseData`  
_L794-824_
- reflection: `USTRUCT()`
- L799 _public member_ `FString file_name;` — `UPROPERTY()`
- L802 _public member_ `FOneSkyTranslationStatusResponseLocale locale;` — `UPROPERTY()`
- L805 _public member_ `FString progress;` — `UPROPERTY()`
- L808 _public member_ `int32 string_count;` — `UPROPERTY()`
- L811 _public member_ `int32 word_count;` — `UPROPERTY()`
- L814 _public function_ `FOneSkyTranslationStatusResponseData() : file_name("") , locale() , progress("") , string_count(-1) , word_count(-1)` — Default constructor.
- L823 _public function_ `FOneSkyTranslationStatusResponseData(ENoInit)` — Creates an uninitialized instance.

#### struct `FOneSkyTranslationStatusResponse`  
`struct FOneSkyTranslationStatusResponse`  
_L831-849_
- reflection: `USTRUCT()`
- desc: Response from a Translation Status query on OneSky //https://github.com/onesky/api-documentation-platform/blob/master/resources/translation.md#status---translations-status
- L836 _public member_ `FOneSkyTranslationStatusResponseMeta meta;` — `UPROPERTY()`
- L839 _public member_ `FOneSkyTranslationStatusResponseData data;` — `UPROPERTY()`
- L842 _public function_ `FOneSkyTranslationStatusResponse() : meta() , data()` — Default constructor.
- L848 _public function_ `FOneSkyTranslationStatusResponse(ENoInit)` — Creates an uninitialized instance.

#### struct `FOneSkyListUploadedFilesResponseMeta`  
`struct FOneSkyListUploadedFilesResponseMeta`  
_L857-895_
- reflection: `USTRUCT()`
- L862 _public member_ `int32 status;` — `UPROPERTY()`
- L865 _public member_ `int32 record_count;` — `UPROPERTY()`
- L868 _public member_ `int32 page_count;` — `UPROPERTY()`
- L871 _public member_ `FString next_page;` — `UPROPERTY()`
- L874 _public member_ `FString prev_page;` — `UPROPERTY()`
- L877 _public member_ `FString first_page;` — `UPROPERTY()`
- L880 _public member_ `FString last_page;` — `UPROPERTY()`
- L883 _public function_ `FOneSkyListUploadedFilesResponseMeta() : status(-1) , record_count(-1) , page_count(-1) , next_page(TEXT("")) , prev_page(TEXT("")) , first_page(TEXT("")) , last_page(TEXT(""))` — Default constructor.
- L894 _public function_ `FOneSkyListUploadedFilesResponseMeta(ENoInit)` — Creates an uninitialized instance.

#### struct `FOneSkyListUploadedFilesResponseLastImport`  
`struct FOneSkyListUploadedFilesResponseLastImport`  
_L898-916_
- reflection: `USTRUCT()`
- L903 _public member_ `int32 id;` — `UPROPERTY()`
- L906 _public member_ `FString status;` — `UPROPERTY()`
- L909 _public function_ `FOneSkyListUploadedFilesResponseLastImport() : id(-1) , status("")` — Default constructor.
- L915 _public function_ `FOneSkyListUploadedFilesResponseLastImport(ENoInit)` — Creates an uninitialized instance.

#### struct `FOneSkyListUploadedFilesResponseDataItem`  
`struct FOneSkyListUploadedFilesResponseDataItem`  
_L920-950_
- reflection: `USTRUCT()`
- L925 _public member_ `FString file_name;` — `UPROPERTY()`
- L928 _public member_ `int32 string_count;` — `UPROPERTY()`
- L931 _public member_ `FOneSkyListUploadedFilesResponseLastImport last_import;` — `UPROPERTY()`
- L934 _public member_ `FString uploaded_at;` — `UPROPERTY()`
- L937 _public member_ `int32 uploaded_at_timestamp;` — `UPROPERTY()`
- L940 _public function_ `FOneSkyListUploadedFilesResponseDataItem() : file_name("") , string_count(-1) , last_import() , uploaded_at("") , uploaded_at_timestamp(-1)` — Default constructor.
- L949 _public function_ `FOneSkyListUploadedFilesResponseDataItem(ENoInit)` — Creates an uninitialized instance.

#### struct `FOneSkyListUploadedFilesResponse`  
`struct FOneSkyListUploadedFilesResponse`  
_L957-975_
- reflection: `USTRUCT()`
- desc: Response from a List Uploaded Files query on OneSky //https://github.com/onesky/api-documentation-platform/blob/master/resources/file.md
- L962 _public member_ `FOneSkyListUploadedFilesResponseMeta meta;` — `UPROPERTY()`
- L965 _public member_ `TArray<FOneSkyListUploadedFilesResponseDataItem> data;` — `UPROPERTY()`
- L968 _public function_ `FOneSkyListUploadedFilesResponse() : meta() , data()` — Default constructor.
- L974 _public function_ `FOneSkyListUploadedFilesResponse(ENoInit)` — Creates an uninitialized instance.

#### struct `FOneSkyUploadFileResponseMeta`  
`struct FOneSkyUploadFileResponseMeta`  
_L982-996_
- reflection: `USTRUCT()`
- L987 _public member_ `int32 status;` — `UPROPERTY()`
- L990 _public function_ `FOneSkyUploadFileResponseMeta() : status(-1)` — Default constructor.
- L995 _public function_ `FOneSkyUploadFileResponseMeta(ENoInit)` — Creates an uninitialized instance.

#### struct `FOneSkyUploadFileResponseLanguage`  
`struct FOneSkyUploadFileResponseLanguage`  
_L1000-1030_
- reflection: `USTRUCT()`
- L1005 _public member_ `FString code;` — `UPROPERTY()`
- L1008 _public member_ `FString english_name;` — `UPROPERTY()`
- L1011 _public member_ `FString local_name;` — `UPROPERTY()`
- L1014 _public member_ `FString locale;` — `UPROPERTY()`
- L1017 _public member_ `FString region;` — `UPROPERTY()`
- L1020 _public function_ `FOneSkyUploadFileResponseLanguage() : code("") , english_name("") , local_name("") , locale("") , region("")` — Default constructor.
- L1029 _public function_ `FOneSkyUploadFileResponseLanguage(ENoInit)` — Creates an uninitialized instance.

#### struct `FOneSkyUploadedFileResponseImport`  
`struct FOneSkyUploadedFileResponseImport`  
_L1033-1055_
- reflection: `USTRUCT()`
- L1038 _public member_ `int32 id;` — `UPROPERTY()`
- L1041 _public member_ `FString created_at;` — `UPROPERTY()`
- L1044 _public member_ `int32 created_at_timestamp;` — `UPROPERTY()`
- L1047 _public function_ `FOneSkyUploadedFileResponseImport() : id(-1) , created_at("") , created_at_timestamp(-1)` — Default constructor.
- L1054 _public function_ `FOneSkyUploadedFileResponseImport(ENoInit)` — Creates an uninitialized instance.

#### struct `FOneSkyUploadFileResponseData`  
`struct FOneSkyUploadFileResponseData`  
_L1058-1084_
- reflection: `USTRUCT()`
- L1063 _public member_ `FString name;` — `UPROPERTY()`
- L1066 _public member_ `FString format;` — `UPROPERTY()`
- L1069 _public member_ `FOneSkyUploadFileResponseLanguage language;` — `UPROPERTY()`
- L1072 _public member_ `FOneSkyUploadedFileResponseImport import;` — `UPROPERTY()`
- L1075 _public function_ `FOneSkyUploadFileResponseData() : name("") , format("") , language() , import()` — Default constructor.
- L1083 _public function_ `FOneSkyUploadFileResponseData(ENoInit)` — Creates an uninitialized instance.

#### struct `FOneSkyUploadFileResponse`  
`struct FOneSkyUploadFileResponse`  
_L1091-1109_
- reflection: `USTRUCT()`
- desc: Response from an Upload File post to OneSky //https://github.com/onesky/api-documentation-platform/blob/master/resources/file.md
- L1096 _public member_ `FOneSkyUploadFileResponseMeta meta;` — `UPROPERTY()`
- L1099 _public member_ `FOneSkyUploadFileResponseData data;` — `UPROPERTY()`
- L1102 _public function_ `FOneSkyUploadFileResponse() : meta() , data()` — Default constructor.
- L1108 _public function_ `FOneSkyUploadFileResponse(ENoInit)` — Creates an uninitialized instance.

#### struct `FOneSkyListPhraseCollectionsResponseMeta`  
`struct FOneSkyListPhraseCollectionsResponseMeta`  
_L1117-1155_
- reflection: `USTRUCT()`
- L1122 _public member_ `int32 status;` — `UPROPERTY()`
- L1125 _public member_ `int32 record_count;` — `UPROPERTY()`
- L1128 _public member_ `int32 page_count;` — `UPROPERTY()`
- L1131 _public member_ `FString next_page;` — `UPROPERTY()`
- L1134 _public member_ `FString prev_page;` — `UPROPERTY()`
- L1137 _public member_ `FString first_page;` — `UPROPERTY()`
- L1140 _public member_ `FString last_page;` — `UPROPERTY()`
- L1143 _public function_ `FOneSkyListPhraseCollectionsResponseMeta() : status(-1) , record_count(-1) , page_count(-1) , next_page(TEXT("")) , prev_page(TEXT("")) , first_page(TEXT("")) , last_page(TEXT(""))` — Default constructor.
- L1154 _public function_ `FOneSkyListPhraseCollectionsResponseMeta(ENoInit)` — Creates an uninitialized instance.

#### struct `FOneSkyListPhraseCollectionsResponseDataItem`  
`struct FOneSkyListPhraseCollectionsResponseDataItem`  
_L1158-1180_
- reflection: `USTRUCT()`
- L1163 _public member_ `FString key;` — `UPROPERTY()`
- L1166 _public member_ `FString created_at;` — `UPROPERTY()`
- L1169 _public member_ `int32 created_at_timestamp;` — `UPROPERTY()`
- L1172 _public function_ `FOneSkyListPhraseCollectionsResponseDataItem() : key("") , created_at("") , created_at_timestamp(-1)` — Default constructor.
- L1179 _public function_ `FOneSkyListPhraseCollectionsResponseDataItem(ENoInit)` — Creates an uninitialized instance.

#### struct `FOneSkyListPhraseCollectionsResponse`  
`struct FOneSkyListPhraseCollectionsResponse`  
_L1187-1205_
- reflection: `USTRUCT()`
- desc: Response from a List Uploaded Files query on OneSky //https://github.com/onesky/api-documentation-platform/blob/master/resources/file.md
- L1192 _public member_ `FOneSkyListPhraseCollectionsResponseMeta meta;` — `UPROPERTY()`
- L1195 _public member_ `TArray<FOneSkyListPhraseCollectionsResponseDataItem> data;` — `UPROPERTY()`
- L1198 _public function_ `FOneSkyListPhraseCollectionsResponse() : meta() , data()` — Default constructor.
- L1204 _public function_ `FOneSkyListPhraseCollectionsResponse(ENoInit)` — Creates an uninitialized instance.

#### struct `FOneSkyShowImportTaskResponseMeta`  
`struct FOneSkyShowImportTaskResponseMeta`  
_L1213-1227_
- reflection: `USTRUCT()`
- L1218 _public member_ `int32 status;` — `UPROPERTY()`
- L1221 _public function_ `FOneSkyShowImportTaskResponseMeta() : status(-1)` — Default constructor.
- L1226 _public function_ `FOneSkyShowImportTaskResponseMeta(ENoInit)` — Creates an uninitialized instance.

#### struct `FOneSkyShowImportTaskResponseLocale`  
`struct FOneSkyShowImportTaskResponseLocale`  
_L1230-1260_
- reflection: `USTRUCT()`
- L1235 _public member_ `FString code;` — `UPROPERTY()`
- L1238 _public member_ `FString english_name;` — `UPROPERTY()`
- L1241 _public member_ `FString local_name;` — `UPROPERTY()`
- L1244 _public member_ `FString locale;` — `UPROPERTY()`
- L1247 _public member_ `FString region;` — `UPROPERTY()`
- L1250 _public function_ `FOneSkyShowImportTaskResponseLocale() : code("") , english_name("") , local_name("") , locale("") , region("")` — Default constructor.
- L1259 _public function_ `FOneSkyShowImportTaskResponseLocale(ENoInit)` — Creates an uninitialized instance.

#### struct `FOneSkyShowImportTaskResponseFile`  
`struct FOneSkyShowImportTaskResponseFile`  
_L1264-1286_
- reflection: `USTRUCT()`
- L1269 _public member_ `FString name;` — `UPROPERTY()`
- L1272 _public member_ `FString format;` — `UPROPERTY()`
- L1275 _public member_ `FOneSkyShowImportTaskResponseLocale locale;` — `UPROPERTY()`
- L1278 _public function_ `FOneSkyShowImportTaskResponseFile() : name("") , format("") , locale()` — Default constructor.
- L1285 _public function_ `FOneSkyShowImportTaskResponseFile(ENoInit)` — Creates an uninitialized instance.

#### struct `FOneSkyShowImportTaskResponseData`  
`struct FOneSkyShowImportTaskResponseData`  
_L1289-1327_
- reflection: `USTRUCT()`
- L1294 _public member_ `int32 id;` — `UPROPERTY()`
- L1297 _public member_ `FOneSkyShowImportTaskResponseFile file;` — `UPROPERTY()`
- L1300 _public member_ `int32 string_count;` — `UPROPERTY()`
- L1303 _public member_ `int32 word_count;` — `UPROPERTY()`
- L1306 _public member_ `FString status;` — `UPROPERTY()`
- L1309 _public member_ `FString created_at;` — `UPROPERTY()`
- L1312 _public member_ `int32 created_at_timestamp;` — `UPROPERTY()`
- L1315 _public function_ `FOneSkyShowImportTaskResponseData() : id(-1) , file() , string_count(-1) , word_count(-1) , status("") , created_at("") , created_at_timestamp(-1)` — Default constructor.
- L1326 _public function_ `FOneSkyShowImportTaskResponseData(ENoInit)` — Creates an uninitialized instance.

#### struct `FOneSkyShowImportTaskResponse`  
`struct FOneSkyShowImportTaskResponse`  
_L1334-1352_
- reflection: `USTRUCT()`
- desc: Response from a Show Import Task query on OneSky //https://github.com/onesky/api-documentation-platform/blob/master/resources/import_task.md
- L1339 _public member_ `FOneSkyShowImportTaskResponseMeta meta;` — `UPROPERTY()`
- L1342 _public member_ `FOneSkyShowImportTaskResponseData data;` — `UPROPERTY()`
- L1345 _public function_ `FOneSkyShowImportTaskResponse() : meta() , data()` — Default constructor.
- L1351 _public function_ `FOneSkyShowImportTaskResponse(ENoInit)` — Creates an uninitialized instance.

### `Plugins/Developer/OneSkyLocalizationService/Source/OneSkyLocalizationService/Private/OneSkyLocalizationServiceRevision.h` (Private)


#### class `FOneSkyLocalizationServiceRevision`  
`class FOneSkyLocalizationServiceRevision : public ILocalizationServiceRevision`  
_L8-36_
- inherits: `ILocalizationServiceRevision`
- L11 _public function_ `FOneSkyLocalizationServiceRevision() : RevisionNumber(0) , Date(0)`
- L18 _public prototype_ `virtual int32 GetRevisionNumber() const override;` — ILocalizationServiceRevision interface
- L19 _public prototype_ `virtual const FString& GetRevision() const override;`
- L20 _public prototype_ `virtual const FString& GetUserName() const override;`
- L21 _public prototype_ `virtual const FDateTime& GetDate() const override;`
- L26 _public member_ `int32 RevisionNumber;` — The revision number of this file
- L29 _public member_ `FString Revision;` — The revision to display to the user
- L32 _public member_ `FString UserName;` — THe user that made the change for this revision
- L35 _public member_ `FDateTime Date;` — The date of this revision

### `Plugins/Developer/OneSkyLocalizationService/Source/OneSkyLocalizationService/Private/OneSkyLocalizationServiceSettings.h` (Private)


#### struct `FOneSkyLocalizationTargetSetting`  
`struct FOneSkyLocalizationTargetSetting`  
_L12-36_
- reflection: `USTRUCT()`
- desc: Holds the OneSky settings for a Localization Target.
- L16 _public function_ `FOneSkyLocalizationTargetSetting() : OneSkyProjectId(INDEX_NONE)`
- L22 _public member_ `FGuid TargetGuid;` — `UPROPERTY()` — The GUID of the LocalizationTarget that these OneSky settings are for
- L28 _public member_ `int32 OneSkyProjectId;` — `UPROPERTY()` — The id of the OneSky Project  this target belongs to
- L34 _public member_ `FString OneSkyFileName;` — `UPROPERTY()` — The name of the file that corresponds to this target

#### class `UOneSkyLocalizationTargetSettings`  
`class UOneSkyLocalizationTargetSettings : public UObject`  
_L39-50_
- reflection: `UCLASS(config = LocalizationServiceSettings)`
- inherits: `UObject`
- L48 _public member_ `TArray<struct FOneSkyLocalizationTargetSetting> TargetSettings;` — `UPROPERTY(config)` — The array of settings for each target of this project

#### class `FOneSkyLocalizationServiceSettings`  
`class FOneSkyLocalizationServiceSettings`  
_L52-123_
- L56 _public function_ `FOneSkyLocalizationServiceSettings() : bSaveSecretKey(false)`
- L62 _public prototype_ `const FString& GetConnectionName() const;` — Get the OneSky connection name
- L65 _public prototype_ `void LoadSettings();` — Load settings from ini file
- L68 _public prototype_ `void SaveSettings() const;` — Save settings to ini file
- L71 _public prototype_ `FOneSkyConnectionInfo GetConnectionInfo() const;` — Get the credentials we use to access the server - only call on the game thread
- L74 _public function_ `void SetApiKey(FString InApiKey)` — Set the public API key we use to access the server - only call on the game thread
- L81 _public function_ `void SetApiSecret(FString InApiSecret)` — Set the secret API key we use to access the server - only call on the game thread
- L88 _public function_ `void SetSaveSecretKey(bool InSaveSecretKey)` — Set whether or not to save the secret API key (WARNING: saved unencrypted)
- L95 _public function_ `bool GetSaveSecretKey()` — Get whether or not to save the secret API Key
- L105 _public prototype_ `FOneSkyLocalizationTargetSetting* GetSettingsForTarget(FGuid TargetGuid, bool bCreateIfNotFound = false);` — Get settings for a specific localization target by it's Guid @param TargetGuid - the GUID to search for @param bCreateIfNotFound - Add a new blank settings entry to the array if not found
- L108 _public prototype_ `void SetSettingsForTarget(FGuid TargetGuid, int32 ProjectId, FString FileName);` — Set settings for a specific localization target by it's Guid
- L112 _public member_ `UOneSkyLocalizationTargetSettings* TargetSettingsObject;` — Object that contains array of OneSky settings for a given targets, used to serialize to .ini file
- L116 _private member_ `mutable FCriticalSection CriticalSection;` — A critical section for settings access
- L119 _private member_ `FOneSkyConnectionInfo ConnectionInfo;` — The credentials we use to access the server
- L122 _private member_ `bool bSaveSecretKey;` — Whether or not we remember the secret key for the user (WARNING: saved unencrypted)

### `Plugins/Developer/OneSkyLocalizationService/Source/OneSkyLocalizationService/Private/OneSkyLocalizationServiceState.h` (Private)


#### enum `EOneSkyState::Type`  
`enum Type`  
_L12-31_
- L15 _public enumerator_ `Unknown = 0` — Text unknown to OneSky
- L18 _public enumerator_ `Untranslated = 1` — OneSky has an entry for this text, but no translation for this culture
- L21 _public enumerator_ `NotAccepted = 2` — One sky has an entry for this text and a translation, but the translation has not been accepted
- L24 _public enumerator_ `NotFinalized = 3` — One sky has an entry for this text and an accepted translation, but the translation is not finalized
- L27 _public enumerator_ `Finalized = 4` — One sky has an entry for this text and a finalized translation
- L30 _public enumerator_ `Deprecated = 5` — One sky has an entry for this text, and a translation, but that translation is deprecated

#### class `FOneSkyLocalizationServiceState`  
`class FOneSkyLocalizationServiceState : public ILocalizationServiceState`  
_L34-114_
- inherits: `ILocalizationServiceState`
- L37 _public function_ `FOneSkyLocalizationServiceState(const FLocalizationServiceTranslationIdentifier InTranslationId, EOneSkyState::Type InState = EOneSkyState::Unknown) : TranslationId(InTranslationId) , State(InState) , OneSkyLatestRevNumber(INVALID_REVISION) , LocalRevNumber(INVALID_REVISION) , bModifed(false) , TimeStamp(0)`
- L48 _public prototype_ `virtual int32 GetHistorySize() const override;` — ILocalizationServiceState interface
- L49 _public prototype_ `virtual TSharedPtr<class ILocalizationServiceRevision, ESPMode::ThreadSafe> GetHistoryItem( int32 HistoryIndex ) const override;`
- L50 _public prototype_ `virtual FName GetIconName() const override;`
- L51 _public prototype_ `virtual FName GetSmallIconName() const override;`
- L52 _public prototype_ `virtual FText GetDisplayName() const override;`
- L53 _public prototype_ `virtual FText GetDisplayTooltip() const override;`
- L54 _public prototype_ `virtual const FString& GetSourceString() const override;`
- L55 _public prototype_ `virtual const FCulturePtr GetCulture() const override;`
- L56 _public prototype_ `virtual const FDateTime& GetTimeStamp() const override;`
- L57 _public prototype_ `virtual bool IsCurrent() const override;`
- L58 _public prototype_ `virtual bool IsKnownToLocalizationService() const override;`
- L59 _public prototype_ `virtual bool IsUnknown() const override;`
- L60 _public prototype_ `virtual bool CanEdit() const override;`
- L61 _public prototype_ `virtual bool IsModified() const override;`
- L62 _public function_ `virtual const FLocalizationServiceTranslationIdentifier& GetTranslationIdentifier() const override`
- L68 _public function_ `EOneSkyState::Type GetState() const` — Get the state of a file
- L74 _public function_ `void SetState( EOneSkyState::Type InState )` — Set the state of the translation
- L80 _public function_ `void SetTranslation (const FString& InTranslation)` — Update the translation
- L85 _public function_ `virtual const FString& GetTranslationString() const override`
- L92 _public member_ `TArray< TSharedRef<FOneSkyLocalizationServiceRevision, ESPMode::ThreadSafe> > History;` — History of the item, if any
- L95 _public member_ `FLocalizationServiceTranslationIdentifier TranslationId;` — Translation identifier
- L98 _public member_ `FString Translation;` — Current translation
- L101 _public member_ `EOneSkyState::Type State;` — Status of the file
- L104 _public member_ `int OneSkyLatestRevNumber;` — Latest revision number of the text in OneSky
- L107 _public member_ `int LocalRevNumber;` — Latest rev number at which the text was synced to before being edited
- L110 _public member_ `bool bModifed;` — Modified from depot version
- L113 _public member_ `FDateTime TimeStamp;` — The timestamp of the last update

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace EOneSkyState`
