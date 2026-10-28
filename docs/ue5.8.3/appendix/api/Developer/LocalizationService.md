# Developer / LocalizationService

- module root: `Source/Developer/LocalizationService`
- headers: 11; symbols: 208
- symbol kinds: class=13, delegate=3, enum=6, enumerator=12, function=40, macro=3, member=21, namespace=6, prototype=99, struct=1, typedef=4
- PrivateDependencyModuleNames: EditorFramework, MessageLog, PropertyEditor, Slate, SlateCore, UnrealEd
- PublicDependencyModuleNames: Core, CoreUObject, Engine, InputCore

### `Source/Developer/LocalizationService/Private/DefaultLocalizationServiceProvider.h` (Private)


#### class `FDefaultLocalizationServiceProvider`  
`class FDefaultLocalizationServiceProvider : public ILocalizationServiceProvider`  
_L18-40_
- inherits: `ILocalizationServiceProvider`
- desc: Default localization service provider implementation - "None"
- L22 _public prototype_ `virtual void Init(bool bForceConnection = true) override;` — ILocalizationServiceProvider implementation
- L23 _public prototype_ `virtual void Close() override;`
- L24 _public prototype_ `virtual FText GetStatusText() const override;`
- L25 _public prototype_ `virtual bool IsAvailable() const override;`
- L26 _public prototype_ `virtual bool IsEnabled() const override;`
- L27 _public prototype_ `virtual const FName& GetName(void) const override;`
- L28 _public prototype_ `virtual const FText GetDisplayName() const override;`
- L29 _public prototype_ `virtual ELocalizationServiceOperationCommandResult::Type GetState(const TArray<FLocalizationServiceTranslationIdentifier>& InTranslationIds, TArray< TSharedRef<ILocalizationServiceState, ESPMode::ThreadSafe> >& OutState, ELocalizationServiceCacheUsage::Type InStateCacheUsage) override;`
- L30 _public prototype_ `virtual ELocalizationServiceOperationCommandResult::Type Execute(const TSharedRef<ILocalizationServiceOperation, ESPMode::ThreadSafe>& InOperation, const TArray<FLocalizationServiceTranslationIdentifier>& InTranslationIds, ELocalizationServiceOperationConcurrency::Type InConcurrency = ELocalizationServiceOperationConcurrency::Synchronous, const FLocalizationServiceOperationComplete& InOperationCompleteDelegate = FLocalizationServiceOperationComplete()) override;`
- L31 _public prototype_ `virtual bool CanCancelOperation( const TSharedRef<ILocalizationServiceOperation, ESPMode::ThreadSafe>& InOperation ) const override;`
- L32 _public prototype_ `virtual void CancelOperation( const TSharedRef<ILocalizationServiceOperation, ESPMode::ThreadSafe>& InOperation ) override;`
- L33 _public prototype_ `virtual void Tick() override;`
- L35 _public prototype_ `virtual void CustomizeSettingsDetails(IDetailCategoryBuilder& DetailCategoryBuilder) const override;`
- L36 _public prototype_ `virtual void CustomizeTargetDetails(IDetailCategoryBuilder& DetailCategoryBuilder, TWeakObjectPtr<ULocalizationTarget> LocalizationTarget) const override;`
- L37 _public prototype_ `virtual void CustomizeTargetToolbar(TSharedRef<FExtender>& MenuExtender, TWeakObjectPtr<ULocalizationTarget> LocalizationTarget) const override;`
- L38 _public prototype_ `virtual void CustomizeTargetSetToolbar(TSharedRef<FExtender>& MenuExtender, TWeakObjectPtr<ULocalizationTargetSet> LocalizationTargetSet) const override;`

### `Source/Developer/LocalizationService/Private/LocalizationServiceModule.h` (Private)


#### class `FLocalizationServiceModule`  
`class FLocalizationServiceModule : public ILocalizationServiceModule`  
_L15-88_
- inherits: `ILocalizationServiceModule`
- L18 _public prototype_ `FLocalizationServiceModule();`
- L21 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L22 _public prototype_ `virtual void ShutdownModule() override;`
- L25 _public prototype_ `virtual void Tick() override;` — ILocalizationServiceModule implementation
- L26 _public prototype_ `virtual bool IsEnabled() const override;`
- L27 _public prototype_ `virtual ILocalizationServiceProvider& GetProvider() const override;`
- L28 _public prototype_ `virtual void SetProvider( const FName& InName ) override;`
- L29 _public prototype_ `virtual bool GetUseGlobalSettings() const override;`
- L30 _public prototype_ `virtual void SetUseGlobalSettings(bool bIsUseGlobalSettings) override;`
- L33 _public prototype_ `void SaveSettings();` — Save the settings to the ini file
- L38 _public prototype_ `int32 GetNumLocalizationServiceProviders();` — Get the number of currently registered translation service providers.
- L43 _public prototype_ `void SetCurrentLocalizationServiceProvider(int32 ProviderIndex);` — Set the current translation service provider by index.
- L48 _public prototype_ `FName GetLocalizationServiceProviderName(int32 ProviderIndex);` — Get the name of the translation service provider at the specified index.
- L55 _public function_ `static FLocalizationServiceModule& Get()` — Gets a reference to the translation service module instance. @return A reference to the translation service module.
- L62 _private prototype_ `void InitializeLocalizationServiceProviders();` — Refresh & initialize the current translation service provider
- L65 _private prototype_ `void ClearCurrentLocalizationServiceProvider();` — Close the current translation service provider & set the current to default - 'None'
- L68 _private prototype_ `void SetCurrentLocalizationServiceProvider(ILocalizationServiceProvider& InProvider);` — Set the current translation service provider to the passed-in value
- L71 _private prototype_ `void HandleModularFeatureRegistered(const FName& Type, IModularFeature* ModularFeature);` — Delegate handling when translation service features are registered
- L74 _private prototype_ `void HandleModularFeatureUnregistered(const FName& Type, IModularFeature* ModularFeature);` — Delegate handling when translation service features are unregistered
- L78 _private member_ `FLocalizationServiceSettings LocalizationServiceSettings;` — The settings object
- L81 _private member_ `ILocalizationServiceProvider* CurrentLocalizationServiceProvider;` — Current translation service provider
- L84 _private member_ `FDefaultLocalizationServiceProvider DefaultLocalizationServiceProvider;` — Source control provider we use if there are none registered

### `Source/Developer/LocalizationService/Private/LocalizationServiceSettings.h` (Private)


#### class `FLocalizationServiceSettings`  
`class FLocalizationServiceSettings`  
_L7-39_
- L10 _public function_ `FLocalizationServiceSettings() : bUseGlobalSettings(false)`
- L16 _public prototype_ `const FString& GetProvider() const;` — Get the provider we want to use
- L19 _public prototype_ `void SetProvider(const FString& InString);` — Set the provider we want to use
- L22 _public prototype_ `bool GetUseGlobalSettings() const;` — Get whether we should use global or per-project settings
- L25 _public prototype_ `void SetUseGlobalSettings(bool bInUseGlobalSettings);` — Set whether we should use global or per-project settings
- L28 _public prototype_ `void LoadSettings();` — Load settings from ini file
- L31 _public prototype_ `void SaveSettings() const;` — Save settings to ini file
- L35 _private member_ `FString Provider;` — The preferred Localization service provider
- L38 _private member_ `bool bUseGlobalSettings;` — Whether we should use global or per-project settings

### `Source/Developer/LocalizationService/Public/ILocalizationServiceModule.h` (Public)


#### enum `ELocalizationServiceLoginWindowMode::Type`  
`enum Type`  
_L21-25_
- L23 _public enumerator_ `Modal`
- L24 _public enumerator_ `Modeless`

#### enum `ELocalizationServiceOnLoginWindowStartup::Type`  
`enum Type`  
_L34-38_
- L36 _public enumerator_ `ResetProviderToNone`
- L37 _public enumerator_ `PreserveProvider`

#### class `ILocalizationServiceModule`  
`class ILocalizationServiceModule : public IModuleInterface`  
_L45-100_
- inherits: `IModuleInterface`
- desc: Interface for talking to localization service providers
- L53 _public prototype_ `virtual void Tick() = 0;` — Tick the localization service module. This is responsible for dispatching batched/queued status requests & for calling ILocalizationServiceProvider::Tick()
- L64 _public prototype_ `virtual bool IsEnabled() const = 0;` — Check whether localization service is enabled.
- L69 _public prototype_ `virtual ILocalizationServiceProvider& GetProvider() const = 0;` — Get the localization service provider that is currently in use.
- L76 _public prototype_ `virtual void SetProvider( const FName& InName ) = 0;` — Set the current localization service provider to the one specified here by name. This will assert if the provider does not exist. @param	InName	The name of the provider
- L82 _public prototype_ `virtual bool GetUseGlobalSettings() const = 0;` — Get whether we should use global or per-project settings @return true if we should use global settings
- L88 _public prototype_ `virtual void SetUseGlobalSettings(bool bIsUseGlobalSettings) = 0;` — Set whether we should use global or per-project settings @param bIsUseGlobalSettings	Whether we should use global settings
- L95 _public function_ `static inline ILocalizationServiceModule& Get()` — Gets a reference to the localization service module instance. @return A reference to the localization service module.

#### Free symbols / members of external scopes

- L11 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogLocalizationService, Log, All);`
- L14 _delegate_ `DECLARE_DELEGATE_OneParam( FLocalizationServiceLoginClosed, bool );` — Delegate called when the localization service login window is closed. Parameter determines if service is enabled or not
- L14 _prototype_ `DECLARE_DELEGATE_OneParam( FLocalizationServiceLoginClosed, bool );` — Delegate called when the localization service login window is closed. Parameter determines if service is enabled or not
- L19 _namespace_ `namespace ELocalizationServiceLoginWindowMode`
- L32 _namespace_ `namespace ELocalizationServiceOnLoginWindowStartup`

### `Source/Developer/LocalizationService/Public/ILocalizationServiceOperation.h` (Public)


#### class `ILocalizationServiceOperation`  
`class ILocalizationServiceOperation : public TSharedFromThis<ILocalizationServiceOperation, ESPMode::ThreadSafe>`  
_L7-30_
- inherits: `TSharedFromThis<ILocalizationServiceOperation,ESPMode::ThreadSafe>`
- L13 _public prototype_ `virtual ~ILocalizationServiceOperation() = default;` — Virtual destructor
- L16 _public prototype_ `virtual FName GetName() const = 0;` — Get the name of this operation, used as a unique identifier
- L19 _public function_ `virtual FText GetInProgressString() const` — Get the string to display when this operation is in progress
- L26 _public function_ `template<typename Type> static TSharedRef<Type, ESPMode::ThreadSafe> Create()` — Factory method for easier operation creation

#### Free symbols / members of external scopes

- L32 _typedef_ `typedef TSharedRef<class ILocalizationServiceOperation, ESPMode::ThreadSafe> FLocalizationServiceOperationRef;`

### `Source/Developer/LocalizationService/Public/ILocalizationServiceProvider.h` (Public)


#### enum `ELocalizationServiceOperationConcurrency::Type`  
`enum Type`  
_L30-36_
- L33 _public enumerator_ `Synchronous` — Force the operation to be issued on the same thread, blocking until complete.
- L35 _public enumerator_ `Asynchronous` — Run the command on another thread, returning immediately.

#### enum `ELocalizationServiceCacheUsage::Type`  
`enum Type`  
_L44-50_
- L47 _public enumerator_ `ForceUpdate` — Force a synchronous update of the state of the file.
- L49 _public enumerator_ `Use` — Use the cached state if possible

#### enum `ELocalizationServiceOperationCommandResult::Type`  
`enum Type`  
_L58-66_
- L61 _public enumerator_ `Failed` — Command failed to execute correctly or was not supported by the provider.
- L63 _public enumerator_ `Succeeded` — Command executed successfully
- L65 _public enumerator_ `Cancelled` — Command was canceled before completion

#### class `ILocalizationServiceProvider`  
`class ILocalizationServiceProvider : public IModularFeature`  
_L79-230_
- inherits: `IModularFeature`
- desc: Interface to talking with localization service providers.
- L85 _public prototype_ `virtual ~ILocalizationServiceProvider() = default;` — Virtual destructor
- L91 _public prototype_ `virtual void Init(bool bForceConnection = true) = 0;` — Initialize localization service provider. @param	bForceConnection	If set, this flag forces the provider to attempt a connection to its server.
- L96 _public prototype_ `virtual void Close() = 0;` — Shut down localization service provider.
- L99 _public prototype_ `virtual const FName& GetName() const = 0;` — Get the localization service provider name
- L102 _public prototype_ `virtual const FText GetDisplayName() const = 0;` — Get the localization service provider display name
- L105 _public prototype_ `virtual FText GetStatusText() const = 0;` — Get the localization service status as plain, human-readable text
- L108 _public prototype_ `virtual bool IsEnabled() const = 0;` — Quick check if localization service is enabled
- L116 _public prototype_ `virtual bool IsAvailable() const = 0;` — Quick check if localization service is available for use (server-based providers can use this to return whether the server is available or not) @return	true if localization service is available, false if it is not
- L126 _public function_ `virtual ELocalizationServiceOperationCommandResult::Type Login(const FString& InPassword = FString(), ELocalizationServiceOperationConcurrency::Type InConcurrency = ELocalizationServiceOperationConcurrency::Synchronous, const FLocalizationServiceOperationComplete& InOperationCompleteDelegate = FLocalizationServiceOperationComplete())` — Login to the localization service server (if any). This is just a wrapper around Execute(). @param	InPassword						The password (if required) to use when logging in. @param	InConcurrency					How to execute the operation, blocking or asynchronously on another thread. @param	InOperationCompleteDelegate		Delegate to call when the operation is completed. This is called back internal to this call when executed on the main thread, or from Tick() when queued for asynchronous execution. @return the result of the operation.
- L140 _public prototype_ `virtual ELocalizationServiceOperationCommandResult::Type GetState(const TArray<FLocalizationServiceTranslationIdentifier>& InTranslationIds, TArray< TSharedRef<ILocalizationServiceState, ESPMode::ThreadSafe> >& OutState, ELocalizationServiceCacheUsage::Type InStateCacheUsage) = 0;` — Get the state of each of the passed-in files. State may be cached for faster queries. Note states can be NULL! @param	InTranslationIds	The translations to retrieve state for. @param	OutState			The states of the files. This will be empty if the operation fails. Note states can be NULL! @param	InStateCacheUsage	Whether to use the state cache or to force a (synchronous) state retrieval. @return the result of the operation.
- L145 _public function_ `virtual TSharedPtr<ILocalizationServiceState, ESPMode::ThreadSafe> GetState(const FLocalizationServiceTranslationIdentifier& InTranslationId, ELocalizationServiceCacheUsage::Type InStateCacheUsage)` — Helper overload for state retrieval, see GetState().
- L166 _public prototype_ `virtual ELocalizationServiceOperationCommandResult::Type Execute(const TSharedRef<ILocalizationServiceOperation, ESPMode::ThreadSafe>& InOperation, const TArray<FLocalizationServiceTranslationIdentifier>& InTranslationIds, ELocalizationServiceOperationConcurrency::Type InConcurrency = ELocalizationServiceOperationConcurrency::Synchronous, const FLocalizationServiceOperationComplete& InOperationCompleteDelegate = FLocalizationServiceOperationComplete()) = 0;` — Attempt to execute an operation on the passed-in files (if any are required). @param	InTranslationIds				The translations in question @param	InOperation						The operation to perform. @param	InConcurrency					How to execute the operation, blocking or asynchronously on another thread. @param	InOperationCompleteDelegate		Delegate to call when the operation is completed. This is called back internal to this call when executed on the main thread, or from Tick() when queued for asynchronous execution. @return the result of the operation.
- L171 _public function_ `virtual ELocalizationServiceOperationCommandResult::Type Execute(const TSharedRef<ILocalizationServiceOperation, ESPMode::ThreadSafe>& InOperation, const ELocalizationServiceOperationConcurrency::Type InConcurrency = ELocalizationServiceOperationConcurrency::Synchronous, const FLocalizationServiceOperationComplete& InOperationCompleteDelegate = FLocalizationServiceOperationComplete())` — Helper overload for operation execution, see Execute().
- L179 _public function_ `virtual ELocalizationServiceOperationCommandResult::Type Execute(const TSharedRef<ILocalizationServiceOperation, ESPMode::ThreadSafe>& InOperation, const FLocalizationServiceTranslationIdentifier& InTranslationId, const ELocalizationServiceOperationConcurrency::Type InConcurrency = ELocalizationServiceOperationConcurrency::Synchronous, const FLocalizationServiceOperationComplete& InOperationCompleteDelegate = FLocalizationServiceOperationComplete())` — Helper overload for operation execution, see Execute().
- L191 _public prototype_ `virtual bool CanCancelOperation( const TSharedRef<ILocalizationServiceOperation, ESPMode::ThreadSafe>& InOperation ) const = 0;` — Check to see if we can cancel an operation. @param	InOperation		The operation to check. @return true if the operation was cancelled.
- L197 _public prototype_ `virtual void CancelOperation( const TSharedRef<ILocalizationServiceOperation, ESPMode::ThreadSafe>& InOperation ) = 0;` — Attempt to cancel an operation in progress. @param	InOperation		The operation to attempt to cancel.
- L202 _public prototype_ `virtual void Tick() = 0;` — Called every update.
- L209 _public prototype_ `virtual void CustomizeSettingsDetails(IDetailCategoryBuilder& DetailCategoryBuilder) const = 0;` — Create a settings widget for display in the localization dashboard. @returns a widget used to edit project-specific localization service settings.
- L215 _public prototype_ `virtual void CustomizeTargetDetails(IDetailCategoryBuilder& DetailCategoryBuilder, TWeakObjectPtr<ULocalizationTarget> LocalizationTarget) const = 0;` — Create a settings widget for display in the localization target editor. @returns a widget used to edit target-specific localization service settings.
- L221 _public prototype_ `virtual void CustomizeTargetToolbar(TSharedRef<FExtender>& MenuExtender, TWeakObjectPtr<ULocalizationTarget> LocalizationTarget) const = 0;` — Create a settings widget for display in the localization target editor. @returns a widget used to edit target-specific localization service settings.
- L227 _public prototype_ `virtual void CustomizeTargetSetToolbar(TSharedRef<FExtender>& MenuExtender, TWeakObjectPtr<ULocalizationTargetSet> LocalizationTargetSet) const = 0;` — Create a settings widget for display in the localization target set editor. @returns a widget used to edit target set-specific localization service settings.

#### Free symbols / members of external scopes

- L22 _macro_ `#define LOCALIZATION_SERVICES_WITH_SLATE (!(PLATFORM_LINUX && IS_PROGRAM))`
- L28 _namespace_ `namespace ELocalizationServiceOperationConcurrency`
- L42 _namespace_ `namespace ELocalizationServiceCacheUsage`
- L56 _namespace_ `namespace ELocalizationServiceOperationCommandResult`
- L70 _delegate_ `DECLARE_DELEGATE_TwoParams(FLocalizationServiceOperationComplete, const FLocalizationServiceOperationRef&, ELocalizationServiceOperationCommandResult::Type);` — Delegate used by providers for when operations finish
- L70 _prototype_ `DECLARE_DELEGATE_TwoParams(FLocalizationServiceOperationComplete, const FLocalizationServiceOperationRef&, ELocalizationServiceOperationCommandResult::Type);` — Delegate used by providers for when operations finish
- L73 _typedef_ `typedef TSharedRef<class ILocalizationServiceOperation, ESPMode::ThreadSafe> FLocalizationServiceOperationSharedRef;` — Delegate used by providers to create localization service operations
- L74 _delegate_ `DECLARE_DELEGATE_RetVal(FLocalizationServiceOperationSharedRef, FGetLocalizationServiceOperation);`
- L74 _prototype_ `DECLARE_DELEGATE_RetVal(FLocalizationServiceOperationSharedRef, FGetLocalizationServiceOperation);`

### `Source/Developer/LocalizationService/Public/ILocalizationServiceRevision.h` (Public)


#### class `ILocalizationServiceRevision`  
`class ILocalizationServiceRevision : public TSharedFromThis<ILocalizationServiceRevision, ESPMode::ThreadSafe>`  
_L10-29_
- inherits: `TSharedFromThis<ILocalizationServiceRevision,ESPMode::ThreadSafe>`
- desc: Abstraction of a localization revision from a localization service provider.
- L16 _public prototype_ `virtual ~ILocalizationServiceRevision() = default;` — Virtual destructor
- L19 _public prototype_ `virtual int32 GetRevisionNumber() const = 0;` — Number of the revision
- L22 _public prototype_ `virtual const FString& GetRevision() const = 0;` — String representation of the revision
- L25 _public prototype_ `virtual const FString& GetUserName() const = 0;` — User name of the submitter
- L28 _public prototype_ `virtual const FDateTime& GetDate() const = 0;` — Date of the revision

### `Source/Developer/LocalizationService/Public/ILocalizationServiceState.h` (Public)


#### struct `FLocalizationServiceTranslationIdentifier`  
`struct FLocalizationServiceTranslationIdentifier`  
_L14-33_
- desc: : TSharedFromThis<FLocalizationServiceTranslationIdentifier, ESPMode::ThreadSafe>
- L16 _public function_ `FLocalizationServiceTranslationIdentifier() : Culture(nullptr), Namespace(""), Source("")`
- L20 _public function_ `FLocalizationServiceTranslationIdentifier(FCulturePtr InCulturePtr, const FString& InNamespace, const FString& InSource) : LocalizationTargetGuid() , Culture(InCulturePtr) , Namespace(InNamespace) , Source(InSource)`
- L29 _public member_ `FGuid LocalizationTargetGuid;`
- L30 _public member_ `FCulturePtr Culture;`
- L31 _public member_ `FString Namespace;`
- L32 _public member_ `FString Source;`

#### class `ILocalizationServiceState`  
`class ILocalizationServiceState : public TSharedFromThis<ILocalizationServiceState, ESPMode::ThreadSafe>`  
_L38-128_
- inherits: `TSharedFromThis<ILocalizationServiceState,ESPMode::ThreadSafe>`
- desc: An abstraction of the state of a file under localization service
- L46 _public prototype_ `virtual ~ILocalizationServiceState() = default;` — Virtual destructor
- L54 _public prototype_ `virtual int32 GetHistorySize() const = 0;` — Get the size of the history. If an FUpdateStatus operation has been called with the ShouldUpdateHistory() set, there should be history present if the file has been committed to localization service. @returns the number of items in the history
- L59 _public prototype_ `virtual const FString& GetSourceString() const = 0;` — Get the text in question
- L64 _public prototype_ `virtual const FString& GetTranslationString() const = 0;` — Get the text in question
- L69 _public prototype_ `virtual const FCulturePtr GetCulture() const = 0;` — Get the culture for which the localization of the text is for
- L76 _public prototype_ `virtual TSharedPtr<class ILocalizationServiceRevision, ESPMode::ThreadSafe> GetHistoryItem( int32 HistoryIndex ) const = 0;` — Get an item from the history @param	HistoryIndex	the index of the history item @returns a history item or NULL if none exist
- L82 _public prototype_ `virtual FName GetIconName() const = 0;` — Get the name of the icon graphic we should use to display the state in a UI. @returns the name of the icon to display
- L88 _public prototype_ `virtual FName GetSmallIconName() const = 0;` — Get the name of the small icon graphic we should use to display the state in a UI. @returns the name of the icon to display
- L94 _public prototype_ `virtual FText GetDisplayName() const = 0;` — Get a text representation of the state @returns	the text to display for this state
- L100 _public prototype_ `virtual FText GetDisplayTooltip() const = 0;` — Get a tooltip to describe this state @returns	the text to display for this states tooltip
- L106 _public prototype_ `virtual const FLocalizationServiceTranslationIdentifier& GetTranslationIdentifier() const = 0;` — * Get a unique identifier for the translation this state represents * @returns	the unique identifier
- L112 _public prototype_ `virtual const FDateTime& GetTimeStamp() const = 0;` — Get the timestamp of the last update that was made to this state. @returns	the timestamp of the last update
- L115 _public prototype_ `virtual bool IsCurrent() const = 0;` — Get whether this translation is up-to-date with the version in localization service
- L118 _public prototype_ `virtual bool IsKnownToLocalizationService() const = 0;` — Get whether this text is known to the localization service
- L121 _public prototype_ `virtual bool CanEdit() const = 0;` — Get whether localization service allows this translation to be edited
- L124 _public prototype_ `virtual bool IsUnknown() const = 0;` — Get whether we know anything about this files localization service state
- L127 _public prototype_ `virtual bool IsModified() const = 0;` — Get whether this file is modified compared to the version we have from localization service

#### enum `ILocalizationServiceState::(anonymous)`  
`enum`  
_L41-41_

#### Free symbols / members of external scopes

- L11 _typedef_ `typedef TSharedRef<class ILocalizationServiceState, ESPMode::ThreadSafe> FLocalizationServiceStateRef;`
- L12 _typedef_ `typedef TSharedPtr<class ILocalizationServiceState, ESPMode::ThreadSafe> FLocalizationServiceStatePtr;`
- L41 _enumerator_ `enum { INVALID_REVISION = -1 }; /** * Virtual destructor */ virtual ~ILocalizationServiceState() = default; /**` (scope `ILocalizationServiceState::__anon691f33fc0103`)

### `Source/Developer/LocalizationService/Public/LocalizationServiceHelpers.h` (Public)


#### class `FScopedLocalizationService`  
`class FScopedLocalizationService`  
_L36-47_
- desc: Helper class that ensures FLocalizationService is properly initialized and shutdown by calling Init/Close in its constructor/destructor respectively.
- L40 _public prototype_ `FScopedLocalizationService();` — Constructor; Initializes localization service Provider
- L43 _public prototype_ `~FScopedLocalizationService();` — Destructor; Closes localization service Provider
- L46 _public prototype_ `ILocalizationServiceProvider& GetProvider();` — Get the provider we are using

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API LOCALIZATIONSERVICE_API`
- L12 _namespace_ `namespace LocalizationServiceHelpers`
- L18 _prototype_ `extern const FString& GetSettingsIni();` (scope `LocalizationServiceHelpers`) — Helper function to get the ini filename for storing localization service settings @return the filename
- L24 _prototype_ `extern const FString& GetGlobalSettingsIni();` (scope `LocalizationServiceHelpers`) — Helper function to get the ini filename for storing global localization service settings @return the filename

### `Source/Developer/LocalizationService/Public/LocalizationServiceOperations.h` (Public)


#### class `FConnectToProvider`  
`class FConnectToProvider : public ILocalizationServiceOperation`  
_L14-54_
- inherits: `ILocalizationServiceOperation`
- desc: Operation used to connect (or test a connection) to localization service
- L18 _public function_ `virtual FName GetName() const override` — ILocalizationServiceOperation interface
- L23 _public function_ `virtual FText GetInProgressString() const override`
- L28 _public function_ `const FString& GetPassword() const`
- L33 _public function_ `void SetPassword(const FString& InPassword)`
- L38 _public function_ `const FText& GetErrorText() const`
- L43 _public function_ `void SetErrorText(const FText& InErrorText)`
- L50 _protected member_ `FString Password;` — Password we use for this operation
- L53 _protected member_ `FText OutErrorText;` — Error text for easy diagnosis

#### class `FDownloadLocalizationTargetFile`  
`class FDownloadLocalizationTargetFile : public ILocalizationServiceOperation`  
_L59-129_
- inherits: `ILocalizationServiceOperation`
- desc: Operation used to download a localization target file from a localization service
- L64 _public function_ `virtual FName GetName() const override` — ILocalizationServiceOperation interface
- L69 _public function_ `virtual FText GetInProgressString() const override`
- L75 _public function_ `void SetInTargetGuid(const FGuid& NewInTargetGuid)`
- L80 _public function_ `const FGuid& GetInTargetGuid() const`
- L85 _public function_ `void SetInRelativeOutputFilePathAndName(const FString& NewInRelativeOutputFilePathAndName)`
- L90 _public function_ `const FString& GetInRelativeOutputFilePathAndName() const`
- L95 _public function_ `FString GetInLocale()`
- L100 _public function_ `void SetInLocale(FString NewLocale)`
- L105 _public function_ `FText GetOutErrorText()`
- L110 _public function_ `void SetOutErrorText(const FText& NewOutErrorText)`
- L119 _protected member_ `FGuid InTargetGuid;` — The GUID of the Localization Target
- L122 _protected member_ `FString InLocale;` — The locale (culture code, for example "fr" or "en-us" or "ja-jp") to download the translations for
- L125 _protected member_ `FString InRelativeOutputFilePathAndName;` — The path and name to the file downloaded, relative to project directory
- L128 _protected member_ `FText OutErrorText;` — Place to easily store and access error message

#### class `FUploadLocalizationTargetFile`  
`class FUploadLocalizationTargetFile : public ILocalizationServiceOperation`  
_L135-220_
- inherits: `ILocalizationServiceOperation`
- desc: Operation used to upload a localization file to a localization service
- L139 _public function_ `FUploadLocalizationTargetFile() : bPreserveAllText(true)`
- L142 _public function_ `virtual FName GetName() const override` — ILocalizationServiceOperation interface
- L147 _public function_ `virtual FText GetInProgressString() const override`
- L153 _public function_ `void SetInTargetGuid(const FGuid& NewInTargetGuid)`
- L158 _public function_ `const FGuid& GetInTargetGuid() const`
- L163 _public function_ `void SetInRelativeInputFilePathAndName(const FString& NewInRelativeInputFilePathAndName)`
- L168 _public function_ `const FString& GetInRelativeInputFilePathAndName() const`
- L173 _public function_ `FString GetInLocale()`
- L178 _public function_ `void SetInLocale(FString NewLocale)`
- L183 _public function_ `FText GetOutErrorText()`
- L188 _public function_ `void SetOutErrorText(const FText& NewOutErrorText)`
- L193 _public function_ `bool GetPreserveAllText()`
- L198 _public function_ `void SetPreserveAllText(bool NewPreserveAllText)`
- L207 _protected member_ `FGuid InTargetGuid;` — The GUID of the Localization Target
- L210 _protected member_ `FString InLocale;` — The locale (culture code, for example "fr" or "en-us" or "ja-jp") to download the translations for
- L213 _protected member_ `FString InRelativeInputFilePathAndName;` — The path and name to the file to upload, relative to project directory
- L216 _protected member_ `FText OutErrorText;` — Place to easily store and access error message
- L219 _protected member_ `bool bPreserveAllText;` — Ask the translations service to keep all text, even if not present in the current upload file.

#### Free symbols / members of external scopes

- L9 _macro_ `#define LOCTEXT_NAMESPACE "LocalizationService"`

### `Source/Developer/LocalizationService/Public/ScopedLocalizationServiceProgress.h` (Public)


#### class `FScopedLocalizationServiceProgress`  
`class FScopedLocalizationServiceProgress`  
_L8-30_
- L18 _public prototype_ `FScopedLocalizationServiceProgress(const FText& InText, const FSimpleDelegate& InOnCancelled = FSimpleDelegate());` — Constructor. Progress dialog is shown immediately (if possible) and is closed when this object goes out of scope. @param	InText			The text to display in the progress dialog. If this is empty the dialog will not be shown. @param	InOnCancelled	The delegate to call when the cancel button is clicked.
- L21 _public prototype_ `~FScopedLocalizationServiceProgress();` — Destructor - closes the dialog
- L24 _public prototype_ `void Tick();` — Makes sure the dialog is ticked
- L29 _private member_ `TWeakPtr<class SWindow> WindowPtr;` — The window containing this progress window
