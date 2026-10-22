# Plugins / MutableValidation

- module root: `Plugins/Mutable/Source/MutableValidation`
- headers: 13; symbols: 65
- symbol kinds: class=12, enum=1, enumerator=6, macro=1, member=13, prototype=32
- PrivateDependencyModuleNames: Core, CoreUObject, CustomizableObject, CustomizableObjectEditor, DataValidation, Engine, MutableTools, UnrealEd
- PublicDependencyModuleNames: Engine, MutableRuntime, RHI, Settings

### `Plugins/Mutable/Source/MutableValidation/Private/MuV/AssetValidator_CustomizableObjects.h` (Private)


#### class `UAssetValidator_CustomizableObjects`  
`class UAssetValidator_CustomizableObjects : public UEditorValidatorBase`  
_L18-49_
- reflection: `UCLASS()`
- inherits: `UEditorValidatorBase`
- L23 _public prototype_ `UAssetValidator_CustomizableObjects();`
- L31 _public prototype_ `static EDataValidationResult IsCustomizableObjectValid(UCustomizableObject* InCustomizableObject, TArray<FText>& OutValidationErrors, TArray<FText>& OutValidationWarnings);` — Checks the validity of the provided CustomizableObject by compiling and recalling the compilation status and the raised compilation warning and error messages. @param InCustomizableObject The mutable customizable object to test. @param OutValidationErrors A list of error messages produced during the provided customizable object's compilation. @param OutValidationWarnings A list of warning messages produced during the provided customizable object's compilation. @return Validation result for the provided object.
- L35 _protected prototype_ `virtual bool CanValidateAsset_Implementation(const FAssetData& InAssetData, UObject* InAsset, FDataValidationContext& InContext) const override;` — UEditorValidatorBase
- L36 _protected prototype_ `virtual EDataValidationResult ValidateLoadedAsset_Implementation(const FAssetData& InAssetData, UObject* InAsset, FDataValidationContext& InContext) override;`
- L42 _private member_ `inline static FDelegateHandle OnPostCOValidationHandle;` — Cached handle to be able later to remove the bound method from the FEditorDelegates::OnPostAssetValidation delegate
- L45 _private member_ `inline static TSet<UCustomizableObject*> AlreadyValidatedRootObjects;` — Collection with all root objects tested during this IsDataValidRun. Shared with all COs
- L48 _private prototype_ `static void OnPostCOsValidation();` — Method invoked once the validation of all assets has been completed.

### `Plugins/Mutable/Source/MutableValidation/Private/MuV/AssetValidator_ReferencedCustomizableObjects.h` (Private)


#### class `UAssetValidator_ReferencedCustomizableObjects`  
`class UAssetValidator_ReferencedCustomizableObjects : public UEditorValidatorBase`  
_L17-54_
- reflection: `UCLASS()`
- inherits: `UEditorValidatorBase`
- L22 _public prototype_ `UAssetValidator_ReferencedCustomizableObjects();`
- L27 _protected prototype_ `virtual bool CanValidateAsset_Implementation(const FAssetData& InAssetData, UObject* InAsset, FDataValidationContext& InContext) const override;` — UEditorValidatorBase
- L28 _protected prototype_ `virtual EDataValidationResult ValidateLoadedAsset_Implementation(const FAssetData& InAssetData, UObject* InAsset, FDataValidationContext& InContext) override;`
- L38 _private prototype_ `TSet<FName> GetAllAssetReferencers(const UObject* InAsset,const IAssetRegistry& InAssetRegistry) const;` — Get a set of referencer objects to a provided UObject. @param InAsset A Pointer to the asset to get all referencers of. @param InAssetRegistry AssetRegistry object to be used to perform the referencers search. @return A set with all the referencing packages.
- L45 _private prototype_ `TSet<UCustomizableObject*> FindCustomizableObjects(const TSet<FName>& InPackagesToCheck,const IAssetRegistry& InAssetRegistry) const;` — Returns a set of customizable objects from the provided collection of packages. @param InPackagesToCheck List of packages to scan for CustomizableObjects. @param InAssetRegistry AssetRegistry object used to perform the asset search. @return A collection of unique Customizable Objets found in the provided packages.
- L52 _private prototype_ `void ValidateCustomizableObjects(UObject* InAsset, const TSet<UCustomizableObject*>& InCustomizableObjectsToValidate);` — Validates all the customizable objects provided and sets the validator status accordingly. It will not make the validator fail. @param InAsset Input asset provided to the validator. @param InCustomizableObjectsToValidate Customizable Objects we want to validate with IsDataValid() @param InValidationErrors List to fill with the warnings and errors generated during the validation of the Customizable objects

### `Plugins/Mutable/Source/MutableValidation/Private/MuV/COIBakingTestCommandlet.h` (Private)


#### class `UCOIBakingTestCommandlet`  
`class UCOIBakingTestCommandlet : public UCommandlet`  
_L21-33_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UCommandlet`
- desc: Commandlet designed to test the baking of instances. It expects an instance UAsset being provided to it so it can later compile it's CO, update the instance itself, and then bake it. EX : -Run=COIBakingTest -EnablePlugins=MutableTesting -CustomizableObjectInstance="/MutableTesting/Cyborg_Character/Character_Inst" -AllowCommandletRendering
- L26 _public prototype_ `virtual int32 Main(const FString& Params) override;`
- L32 _private member_ `TObjectPtr<UCustomizableObjectInstance> TargetInstance = nullptr;` — `UPROPERTY()` — Instance targeted for baking

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MUTABLEVALIDATION_API`

### `Plugins/Mutable/Source/MutableValidation/Private/MuV/COIBulkUpdateTestCommandlet.h` (Private)


#### class `UCOIBulkUpdateTestCommandlet`  
`class UCOIBulkUpdateTestCommandlet : public UCommandlet`  
_L18-24_
- reflection: `UCLASS()`
- inherits: `UCommandlet`
- desc: Testing commandlet designed to allow the mass update of instances in a given project path. It will run in sequence where each of the instances will get updated after their CO gets compiled. Example commandline that updates all instances found in the plugin content directory (and all subdirectories): -run=COIBulkUpdateTest -EnablePlugins=MutableTesting -InstancesPackagePath="/MutableTesting" -AllowCommandletRendering
- L23 _public prototype_ `virtual int32 Main(const FString& Params) override;`

### `Plugins/Mutable/Source/MutableValidation/Private/MuV/COMultiPluginBulkValidationCommandlet.h` (Private)


#### class `UCOMultiPluginBulkValidationCommandlet`  
`class UCOMultiPluginBulkValidationCommandlet : public UCommandlet`  
_L10-16_
- reflection: `UCLASS()`
- inherits: `UCommandlet`
- L15 _public prototype_ `virtual int32 Main(const FString& Params) override;`

### `Plugins/Mutable/Source/MutableValidation/Private/MuV/CacheAssetRegistryCommandlet.h` (Private)


#### class `UCacheAssetRegistryCommandlet`  
`class UCacheAssetRegistryCommandlet : public UCommandlet`  
_L11-17_
- reflection: `UCLASS()`
- inherits: `UCommandlet`
- desc: Simple commandlet used to fill-up the asset registry cache for the execution of the mutable tests
- L16 _public prototype_ `virtual int32 Main(const FString& Params) override;`

### `Plugins/Mutable/Source/MutableValidation/Private/MuV/CustomizableObjectBulkValidationCommandlet.h` (Private)


#### class `UCustomizableObjectBulkValidationCommandlet`  
`class UCustomizableObjectBulkValidationCommandlet : public UCommandlet`  
_L13-19_
- reflection: `UCLASS()`
- inherits: `UCommandlet`
- desc: Commandlet similar to "UCustomizableObjectValidationCommandlet" but in this case it performs the same tests as in the mentioned commandlet but over a series of COs located at a given path.
- L18 _public prototype_ `virtual int32 Main(const FString& Params) override;`

### `Plugins/Mutable/Source/MutableValidation/Private/MuV/CustomizableObjectCompilationUtility.h` (Private)


#### class `FCustomizableObjectCompilationUtility`  
`class FCustomizableObjectCompilationUtility : public TSharedFromThis<FCustomizableObjectCompilationUtility>`  
_L14-31_
- inherits: `TSharedFromThis<FCustomizableObjectCompilationUtility>`
- desc: Helper class that allows the calling commandlet to treat the asynchronous compilation of a CO as a synchronous operation.
- L25 _public prototype_ `bool CompileCustomizableObject(UCustomizableObject& InCustomizableObject, const bool bShouldLogMutableLogs = true, const FCompilationOptions* InCompilationOptionsOverride = nullptr );` — Run the asyncronous compilation of the provided CO but as part of this sync method. @param InCustomizableObject The Customizable Object we want to synchronously compile @param bShouldLogMutableLogs Enables or disables the logging of Log category logs relevant to the CO compilation. Required to avoid a MongoDB limitation with the duplication of MongoDB document names. @param InCompilationOptionsOverride The configuration for the compilation of the CO we want to use instead of the one part of the CO. @return True if the compilation was successful and false if it failed.
- L30 _private member_ `TStrongObjectPtr<UCustomizableObject> CustomizableObject;` — The CO that is currently being compiled.

### `Plugins/Mutable/Source/MutableValidation/Private/MuV/CustomizableObjectInstanceUpdateUtility.h` (Private)


#### class `FCustomizableObjectInstanceUpdateUtility`  
`class FCustomizableObjectInstanceUpdateUtility : public TSharedFromThis<FCustomizableObjectInstanceUpdateUtility>`  
_L14-45_
- inherits: `TSharedFromThis<FCustomizableObjectInstanceUpdateUtility>`
- desc: Helping class that handles the async update of the provided instance. It will also wait for the mips of it so they get streamed.
- L23 _public prototype_ `bool UpdateInstance(UCustomizableObjectInstance& InInstance);` — Updates the provided customizable object instance. @param InInstance Instance to be compiled @return True if the update was successful and false otherwise
- L32 _private prototype_ `void OnInstanceUpdateResult(const FUpdateContext& Result);` — Callback executed when the instance being updated finishes it's mesh update. @param Result The result of the updating operation
- L35 _private member_ `TStrongObjectPtr<UCustomizableObjectInstance> Instance = nullptr;` — The instance that is currently being handled by this class.
- L38 _private member_ `TArray<TStrongObjectPtr<USkeletalMeshComponent>> ComponentsBeingUpdated;` — The components of the Instance that we are currently waiting for their mips to be streamed in
- L41 _private member_ `bool bIsInstanceBeingUpdated = false;` — Flag used to control if we are updating and instance or not. Once it gets set to false then the update gets halted and the program continues
- L44 _private member_ `bool bInstanceFailedUpdate = false;` — False if the instance did update successfully, true if it failed

### `Plugins/Mutable/Source/MutableValidation/Private/MuV/CustomizableObjectValidationCommandlet.h` (Private)


#### class `UCustomizableObjectValidationCommandlet`  
`class UCustomizableObjectValidationCommandlet : public UCommandlet`  
_L13-19_
- reflection: `UCLASS()`
- inherits: `UCommandlet`
- desc: Commandlet designed to compile and then update a deterministically random set of instances.
- L18 _public prototype_ `virtual int32 Main(const FString& Params) override;`

### `Plugins/Mutable/Source/MutableValidation/Private/MuV/MutableValidationSettings.h` (Private)


#### class `UMutableValidationSettings`  
`class UMutableValidationSettings : public UObject`  
_L8-22_
- reflection: `UCLASS(config = Editor)`
- inherits: `UObject`
- L16 _public member_ `bool bEnableDirectCOValidation = false;` — `UPROPERTY(meta=(DisplayName="Enable Direct Customizable Object Validation"),config, EditAnywhere, Category = Validation)` — If set to true the checked out Customizable Objects will get validated.
- L21 _public member_ `bool bEnableIndirectCOValidation = false;` — `UPROPERTY(meta=(DisplayName="Enable Indirect Customizable Object Validation"), config, EditAnywhere, Category = Validation)` — If set to true the Customizable Objects referenced by the checked out resources will get validated. This validation is resource intensive and will require more time to run than the Direct Customizable Object Validation.

### `Plugins/Mutable/Source/MutableValidation/Private/MuV/ScopedLogSection.h` (Private)


#### enum `EMutableLogSection`  
`enum class EMutableLogSection : uint8`  
_L14-25_
- desc: Names for the possible sections used during the logging of this module commandlets. Do not change the name of them before consulting the Mutable team
- L16 _public enumerator_ `Undefined = 0`
- L18 _public enumerator_ `Compilation`
- L19 _public enumerator_ `Update`
- L20 _public enumerator_ `Bake`
- L22 _public enumerator_ `Object`
- L24 _public enumerator_ `Plugin`

#### class `FScopedLogSection`  
`class FScopedLogSection`  
_L31-50_
- desc: Object that handles the logging of scope based log sections that we can later parse out and interpret externally
- L34 _public prototype_ `FScopedLogSection(EMutableLogSection Section, const FName& SectionTarget = FName());`
- L35 _public prototype_ `~FScopedLogSection();`
- L40 _private prototype_ `FString GetLogSectionName(EMutableLogSection Section) const;` — Get the name of the context as a string of characters
- L43 _private member_ `EMutableLogSection CurrentSection = EMutableLogSection::Undefined;` — Section that this object is currently representing
- L46 _private member_ `static inline FName SectionObject;` — The object the current section is representing
- L49 _private member_ `static inline FName SectionPlugin;` — The object the current section is representing

### `Plugins/Mutable/Source/MutableValidation/Private/MuV/ValidationUtils.h` (Private)


#### Free symbols / members of external scopes

- L18 _prototype_ `uint32 GetTargetAmountOfInstances(const FString& Params);` — Get the amount of instances we want to generate. @param Params The parameters fed to this commandlet. @return The amount of instances to be generated for a given CO and state.
- L27 _prototype_ `ITargetPlatform* GetCompilationPlatform(const FString& Params);` — Extracts the targeted compilation platform provided by the user. It will look for "-CompilationPlatformName="PlatformName". Examples : -CompilationPlatformName=WindowsEditor or -CompilationPlatformName=Switch @param Params The arguments provided to this commandlet. @return The target platform to be used for the CO compilation.
- L34 _prototype_ `bool GetIfOnlyRootCOsShouldBeUsed(const FString& Params);` — Determines, based on the provided commandline, if the non-root COs should be compiled or not. @param Params The arguments provided to this commandlet. @return True if only root objects should be compiled, false otherwise.
- L42 _prototype_ `void PrepareAssetRegistry();` — Prepare the asset registry so we can later use it to search assets. It is required by Mutable to compile.
- L49 _prototype_ `void Wait(const double ToWaitSeconds);` — Hold the thread for the time specified while ticking the engine. @param ToWaitSeconds The time in seconds we want to hold the execution of the thread
- L57 _prototype_ `void LogGlobalSettings();` — Logs some configuration data related to how mutable will compile and then generate instances. We do this so we can later Isolate tests using different configurations. @note Add new logs each time you add a way to change the configuration of the test from the .xml testing file
- L66 _prototype_ `FCompilationOptions GetCompilationOptionsForBenchmarking (const UCustomizableObject& ReferenceCustomizableObject);` — Returns the settings used by CIS based on the compilation options of the provided CO. @param ReferenceCustomizableObject CO used to get the base FCompilationOptions we want. @return The FCompilationOptions for the provided CO but with some settings changed to be adecuate for a benchmark oriented compilation.
- L77 _prototype_ `TArray<FAssetData> FindAllAssetsAtPath(FName SearchPath, const UClass* TargetObjectClass);` — Get a list of AssetData objects filled with the objets of the class specified found at the provided path. @param SearchPath The path where the search should be conducted. @param TargetObjectClass The class to be searching for in the provided path. @return An array of AssetData objects. Each one will represent one of the found assets. The names of the objects may be repeated, but the paths not.
- L87 _prototype_ `bool TestCustomizableObject(UCustomizableObject& InTargetCustomizableObject, const ITargetPlatform& TargetCompilationPlatform, const uint32 InstancesToGenerate);` — Compiles and then generates a series of instances while reporting the performance of all the processes involved. @param InTargetCustomizableObject The Customizable Object to be compiled and used as the base for the generated instances. @param TargetCompilationPlatform The target platform used to compile the Customizable Object against. @param InstancesToGenerate The amount of instances to generate per state. @return True if all went well and false if the testing operation did throw errors.
