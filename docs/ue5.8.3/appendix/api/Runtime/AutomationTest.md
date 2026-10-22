# Runtime / AutomationTest

- module root: `Source/Runtime/AutomationTest`
- headers: 4; symbols: 115
- symbol kinds: class=4, enum=3, enumerator=12, function=28, member=24, namespace=1, prototype=41, struct=2
- PrivateDependencyModuleNames: Core, SourceControl
- PublicDependencyModuleNames: CoreUObject

### `Source/Runtime/AutomationTest/Public/AutomationState.h` (Public)


#### enum `EAutomationState`  
`enum class EAutomationState : uint8`  
_L14-21_
- reflection: `UENUM()`
- desc: Enumeration of unit test status for special dialog
- L16 _public enumerator_ `NotRun` — Automation test was not run
- L17 _public enumerator_ `InProcess` — Automation test is running now
- L18 _public enumerator_ `Fail` — Automation test was run and failed
- L19 _public enumerator_ `Success` — Automation test was run and succeeded
- L20 _public enumerator_ `Skipped` — Automation test was skipped

#### Free symbols / members of external scopes

- L24 _function_ `inline const FString AutomationStateToString(EAutomationState InValue)`

### `Source/Runtime/AutomationTest/Public/AutomationTestExcludelist.h` (Public)


#### enum `ETEST_RHI_Options`  
`enum class ETEST_RHI_Options`  
_L12-19_
- reflection: `UENUM()`
- L14 _public enumerator_ `DirectX11`
- L15 _public enumerator_ `DirectX12`
- L16 _public enumerator_ `Vulkan`
- L17 _public enumerator_ `Metal`
- L18 _public enumerator_ `Null`

#### enum `ETEST_RHI_FeatureLevel_Options`  
`enum class ETEST_RHI_FeatureLevel_Options`  
_L35-39_
- reflection: `UENUM()`
- L37 _public enumerator_ `SM5`
- L38 _public enumerator_ `SM6`

#### class `UAutomationTestExcludelistSettings`  
`class UAutomationTestExcludelistSettings : public UAutomationTestPlatformSettings`  
_L90-103_
- reflection: `UCLASS(config = Engine, defaultconfig, MinimalAPI)`
- inherits: `UAutomationTestPlatformSettings`
- L97 _public member_ `TArray<FName> SupportedRHIs;` — `UPROPERTY(Config)`
- L100 _protected function_ `virtual void InitializeSettingsDefault()`
- L101 _protected function_ `virtual FString GetSectionName()`

#### struct `FAutomationTestExcludeOptions`  
`struct FAutomationTestExcludeOptions`  
_L106-185_
- reflection: `USTRUCT()`
- L111 _public function_ `template<typename EnumType> static const TSet<FName>& GetAllRHIOptionNames()`
- L131 _public function_ `static const TSet<FName>& GetAllRHIOptionNamesFromSettings()`
- L147 _public function_ `static const TSet<FName>& GetPlatformRHIOptionNamesFromSettings(const FName& Platform)`
- L163 _public prototype_ `void UpdateReason(const FString& BeautifiedReason, const FString& TaskTrackerTicketId);`
- L168 _public member_ `FName Test;` — `UPROPERTY(VisibleAnywhere, Category = ExcludeTestOptions)` — Name of the target test
- L172 _public member_ `FName Reason;` — `UPROPERTY(EditAnywhere, Category = ExcludeTestOptions)` — Reason to why the test is excluded
- L176 _public member_ `TSet<FName> RHIs;` — `UPROPERTY(EditAnywhere, Category = ExcludeTestOptions)` — Options to target specific RHI. No option means it should be applied to all RHIs
- L180 _public member_ `TSet<FName> Platforms;` — `UPROPERTY(EditAnywhere, Category = ExcludeTestOptions)` — Options to target specific platform. No option means it should be applied to all platforms
- L184 _public member_ `bool Warn = false;` — `UPROPERTY(EditAnywhere, Category = ExcludeTestOptions)` — Should the Reason be reported as a warning in the log

#### struct `FAutomationTestExcludelistEntry`  
`struct FAutomationTestExcludelistEntry`  
_L188-320_
- reflection: `USTRUCT()`
- L192 _public function_ `FAutomationTestExcludelistEntry()`
- L194 _public function_ `FAutomationTestExcludelistEntry(const FAutomationTestExcludeOptions& Options) : Platforms(Options.Platforms) , Test(Options.Test) , Reason(Options.Reason) , RHIs(Options.RHIs) , Warn(Options.Warn)`
- L202 _public function_ `TSharedPtr<FAutomationTestExcludeOptions> GetOptions() const`
- L215 _public function_ `int8 NumRHIType() const` — Return the number of RHI types that needs to be matched for exclusion
- L234 _public function_ `void SetPropagation(const FString& ForTestName)` — Determine if exclusion entry is propagated based on test name - used for management in test automation window
- L240 _public function_ `bool IsEmpty() const` — Return true if the entry is not specific
- L246 _public function_ `void Reset()` — Reset entry to be un-specific
- L253 _public prototype_ `void Finalize();` — Make the entry specific
- L256 _public prototype_ `FString GetStringForHash() const;` — Output string used to generate hash
- L259 _public function_ `bool HasConditions() const` — Has conditional exclusion
- L265 _public function_ `bool RemoveConditions(const FAutomationTestExcludelistEntry& Entry)` — Remove overlapping exclusion conditions, return true if at least one condition was removed
- L293 _public member_ `FString FullTestName;` — Hold full test name/path
- L295 _public member_ `bool bIsPropagated = false;` — Is the entry comes from propagation
- L297 _public member_ `TSet<FName> Platforms;` — Platforms to which the entry applies
- L303 _public member_ `FName Map;` — `UPROPERTY(Config)` — Hold the name of the target functional test map
- L307 _public member_ `FName Test;` — `UPROPERTY(Config)` — Hold the name of the target test - full test name is require here unless for functional tests
- L311 _public member_ `FName Reason;` — `UPROPERTY(Config)` — Reason to why the test is excluded
- L315 _public member_ `TSet<FName> RHIs;` — `UPROPERTY(Config)` — Option to target specific RHI. Empty array means it should be applied to all RHI
- L319 _public member_ `bool Warn = false;` — `UPROPERTY(Config)` — Should the Reason be reported as a warning in the log

#### class `UAutomationTestExcludelistConfig`  
`class UAutomationTestExcludelistConfig : public UAutomationTestPlatformSettings`  
_L323-360_
- reflection: `UCLASS(config = Engine, defaultconfig, MinimalAPI)`
- inherits: `UAutomationTestPlatformSettings`
- L328 _public prototype_ `void Reset();`
- L329 _public prototype_ `void AddEntry(const FAutomationTestExcludelistEntry& Entry);`
- L330 _public prototype_ `const TArray<FAutomationTestExcludelistEntry>& GetEntries() const;`
- L331 _public function_ `FString GetTaskTrackerURLHashtag() const`
- L332 _public function_ `FString GetTaskTrackerURLBase() const`
- L334 _public prototype_ `void SaveConfig();`
- L336 _public prototype_ `void LoadTaskTrackerProperties();`
- L339 _protected prototype_ `virtual void PostInitProperties() override;`
- L340 _protected prototype_ `virtual void InitializeSettingsDefault() override;`
- L341 _protected function_ `virtual FString GetSectionName() override`
- L344 _private prototype_ `void UpdateHash(const FAutomationTestExcludelistEntry& Entry);`
- L347 _private member_ `FString TaskTrackerURLHashtag;` — `UPROPERTY(Transient)`
- L350 _private member_ `FString TaskTrackerURLBase;` — `UPROPERTY(Transient)`
- L353 _private member_ `TArray<FAutomationTestExcludelistEntry> ExcludeTest;` — `UPROPERTY(Config)`
- L355 _private member_ `FString PlatformName;`
- L357 _private member_ `FSHAHash EntriesHash;` — Keep track of any changes
- L359 _private member_ `FSHAHash SavedEntriesHash;` — Hash of what was last saved

#### class `UAutomationTestExcludelist`  
`class UAutomationTestExcludelist : public UObject`  
_L363-520_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- L368 _public function_ `UAutomationTestExcludelist()`
- L370 _public prototype_ `static UAutomationTestExcludelist* Get();`
- L378 _public prototype_ `void AddToExcludeTest(const FString& TestName, const FAutomationTestExcludelistEntry& ExcludelistEntry);` — Add an Entry to the exclusion list for TestName @param TestName The full test name to be added. @param Entry The FAutomationTestExcludelistEntry to be excluded.
- L385 _public prototype_ `void RemoveFromExcludeTest(const FString& TestName);` — Remove the Entry from the exclusion list for TestName @param TestName The full test name to be removed.
- L393 _public prototype_ `bool IsTestExcluded(const FString& TestName) const;` — Is the TestName excluded? @param TestName The full test name to be tested. @return True if the test is excluded
- L404 _public prototype_ `bool IsTestExcluded(const FString& TestName, const TSet<FName>& RHI, FName* OutReason, bool* OutWarn) const;` — Is the TestName excluded? @param TestName The full test name to be tested. @param RHI The RHI the test is being evaluated against. @param OutReason The reason why it is excluded. @param OutWarn Whether a warning is going to be returned if the test is to be excluded. @return True if the test is excluded
- L416 _public prototype_ `bool IsTestExcluded(const FString& TestName, const FName& Platform, const TSet<FName>& RHI, FName* OutReason, bool* OutWarn) const;` — Is the TestName excluded? @param TestName The full test name to be tested. @param Platform The Platform the test is being evaluated against. @param RHI The RHI the test is being evaluated against. @param OutReason The reason why it is excluded. @param OutWarn Whether a warning is going to be returned if the test is to be excluded. @return True if the test is excluded
- L424 _public prototype_ `const FAutomationTestExcludelistEntry* GetExcludeTestEntry(const FString& TestName) const;` — Get the Entry object of the TestName if excluded @param TestName The full test name to be tested. @return Return the corresponding FAutomationTestExcludelistEntry if excluded otherwise nullptr
- L433 _public prototype_ `const FAutomationTestExcludelistEntry* GetExcludeTestEntry(const FString& TestName, const TSet<FName>& RHI) const;` — Get the Entry object of the TestName if excluded @param TestName The full test name to be tested. @param Platform The Platform the test is being evaluated against. @return Return the corresponding FAutomationTestExcludelistEntry if excluded otherwise nullptr
- L443 _public prototype_ `const FAutomationTestExcludelistEntry* GetExcludeTestEntry(const FString& TestName, const FName& Platform, const TSet<FName>& RHI) const;` — Get the Entry object of the TestName if excluded @param TestName The full test name to be tested. @param Platform The Platform the test is being evaluated against. @param RHI The RHI the test is being evaluated against. @return Return the corresponding FAutomationTestExcludelistEntry if excluded otherwise nullptr
- L446 _public prototype_ `FString GetConfigFilename() const;` — `UE_DEPRECATED(5.4, "Please use GetConfigFilenameForEntry instead.")`
- L454 _public prototype_ `FString GetConfigFilenameForEntry(const FAutomationTestExcludelistEntry& Entry) const;` — Get the path to the config from which the exclusion was defined from @param Entry The FAutomationTestExcludelistEntry that is referenced. @return Return the path to the corresponding config
- L463 _public prototype_ `FString GetConfigFilenameForEntry(const FAutomationTestExcludelistEntry& Entry, const FName& Platform) const;` — Get the path to the config from which the exclusion was defined from @param Entry The FAutomationTestExcludelistEntry that is referenced. @param Platform The Platform the test is being evaluated against. @return Return the path to the corresponding config
- L470 _public prototype_ `FString GetTaskTrackerURLBase() const;` — Get URL base that is used while restoring a task tracker task's URL. @return Return the URL base.
- L477 _public prototype_ `FString GetConfigTaskTrackerHashtag() const;` — Get non-beautified task tracker's hashtag suffix (from the loaded configs). @return Return the string that contains non-beautified task tracker's hashtag suffix.
- L484 _public prototype_ `FString GetTaskTrackerName() const;` — Get Task tracker's name if task tracker information is configured. @return Return task tracker's name if it is configured or empty string otherwise.
- L491 _public prototype_ `FString GetTaskTrackerTicketTag() const;` — Get hashtag that is used for referencing tasks if task tracker information is configured. @return Return hashtag that is used for referencing task tracker tasks if it is configured or empty string otherwise.
- L494 _public prototype_ `void SaveToConfigs();` — Save all the required configs
- L497 _public function_ `void SaveConfig()` — `UE_DEPRECATED(5.4, "Please use SaveToConfigs instead.")`
- L501 _private prototype_ `void Initialize();` — Initiate the loading of the configs
- L504 _private prototype_ `void LoadPlatformConfigs();` — Load all possible platform configs
- L507 _private prototype_ `void PopulateEntries();` — Populate the exclusion entries from the loaded configs
- L510 _private prototype_ `FString GetBeautifiedTaskTrackerTicketTagSuffix() const;` — Get beautified hashtag suffix (starts after leading#) that is used for referencing tasks if task tracker information is configured
- L513 _private member_ `TMap<FString, FAutomationTestExcludelistEntry> Entries;` — Exclusion entries
- L516 _private member_ `TObjectPtr<UAutomationTestExcludelistConfig> DefaultConfig;` — `UPROPERTY(Transient)`
- L519 _private member_ `TMap<FName, TObjectPtr<UAutomationTestExcludelistConfig>> PlatformConfigs;` — `UPROPERTY(Transient)`

#### Free symbols / members of external scopes

- L21 _function_ `inline FString LexToString(ETEST_RHI_Options Option)`
- L41 _function_ `inline FString LexToString(ETEST_RHI_FeatureLevel_Options Option)`
- L51 _function_ `inline FString SetToString(const TSet<FName>& Set)`
- L68 _function_ `inline FString SetToShortString(const TSet<FName>& Set)`
- L141 _function_ `NameSet.Sort([](const FName& A, const FName& B) { return A.ToString() < B.ToString(); });` (scope `FAutomationTestExcludeOptions::GetAllRHIOptionNamesFromSettings`)

### `Source/Runtime/AutomationTest/Public/AutomationTestModule.h` (Public)


#### Free symbols / members of external scopes

- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogAutomationTest, Log, All);`

### `Source/Runtime/AutomationTest/Public/AutomationTestPlatform.h` (Public)


#### class `UAutomationTestPlatformSettings`  
`class UAutomationTestPlatformSettings : public UObject`  
_L11-35_
- reflection: `UCLASS(Abstract, MinimalAPI)`
- inherits: `UObject`
- L16 _public function_ `UAutomationTestPlatformSettings()`
- L18 _public prototype_ `static UAutomationTestPlatformSettings* Create(TSubclassOf<UAutomationTestPlatformSettings> SettingsClass, const FString PlatformName);`
- L21 _public prototype_ `virtual void OverrideConfigSection(FString& SectionName) override;`
- L22 _public prototype_ `virtual const TCHAR* GetConfigOverridePlatform() const override;`
- L25 _public prototype_ `void LoadConfig();`
- L26 _public prototype_ `FString GetConfigFilename() const;`
- L27 _public prototype_ `const FString& GetPlatformName() const;`
- L30 _protected function_ `virtual void InitializeSettingsDefault()`
- L31 _protected function_ `virtual FString GetSectionName()`
- L34 _private member_ `FString PlatformName;`

#### Free symbols / members of external scopes

- L37 _namespace_ `namespace AutomationTestPlatform`
- L40 _prototype_ `const TSet<FName>& GetAllAvailablePlatformNames();` (scope `AutomationTestPlatform`) — Return the names of all available platforms
- L43 _prototype_ `TArray<UAutomationTestPlatformSettings*>& GetAllPlatformsSettings(TSubclassOf<UAutomationTestPlatformSettings> SettingsClass);` (scope `AutomationTestPlatform`) — Load and return target automation test settings collection of all platforms
