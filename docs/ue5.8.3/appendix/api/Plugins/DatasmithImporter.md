# Plugins / DatasmithImporter

- module root: `Plugins/Enterprise/DatasmithImporter/Source/DatasmithImporter`
- headers: 37; symbols: 1134
- symbol kinds: class=61, delegate=2, enum=5, enumerator=30, function=122, macro=1, member=194, namespace=13, prototype=684, struct=19, typedef=3
- PrivateDependencyModuleNames: Analytics, ApplicationCore, CinematicCamera, ContentBrowser, Core, CoreUObject, DesktopPlatform, DirectLinkExtension, EditorFramework, EditorScriptingUtilities, EditorStyle, Engine, Foliage, FreeImage, HTTP, InputCore, InterchangeCore, InterchangeEngine, InterchangeFactoryNodes, InterchangeNodes, Json, Kismet, Landscape, LandscapeEditor, LandscapeEditorUtilities, LevelSequence, MainFrame, MaterialEditor, MeshDescription, MeshUtilities, MeshUtilitiesCommon, MessageLog, MovieScene, MovieSceneTracks, PropertyEditor, RHI, RawMesh, RenderCore, Slate, SlateCore, SourceControl, StaticMeshDescription, ToolMenus, UnrealEd, VariantManager, VariantManagerContent
- PublicDependencyModuleNames: DataprepCore, DatasmithContent, DatasmithContentEditor, DatasmithCore, DatasmithTranslator, DirectLinkExtensionEditor, ExternalSource

### `Plugins/Enterprise/DatasmithImporter/Source/DatasmithImporter/Private/DatasmithConsumer.h` (Private)


#### class `UDatasmithConsumer`  
`class UDatasmithConsumer : public UDataprepContentConsumer`  
_L27-130_
- reflection: `UCLASS(Experimental, config = EditorSettings, HideCategories = (DatasmithConsumerInternal))`
- inherits: `UDataprepContentConsumer`
- L32 _public prototype_ `UDatasmithConsumer();`
- L35 _public prototype_ `virtual void PostLoad() override;` — UObject interface
- L36 _public prototype_ `virtual void PostInitProperties() override;`
- L41 _public member_ `TSoftObjectPtr<UDatasmithScene> DatasmithScene_DEPRECATED;` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "Use GetDatasmithScene method to obtain the associated UDatasmithScene."))` — DEPRECATED: Removing use of TSoftObjectPtr
- L45 _public member_ `FString UniqueID;` — `UPROPERTY(BlueprintReadOnly, Category = DatasmithConsumerInternal)` — Stores the level used on the last call to UDatasmithConsumer::Run
- L49 _public member_ `static const FString ConsumerMarkerID;` — Marker to tag levels, assets and actors processed by the consumer
- L52 _public prototype_ `virtual const FText& GetLabel() const override;`
- L53 _public prototype_ `virtual const FText& GetDescription() const override;`
- L56 _public function_ `UDatasmithScene* GetDatasmithScene()` — `UFUNCTION(BlueprintCallable, Category = DatasmithConsumerInternal)`
- L60 _protected function_ `FString GetOutputLevelPath() const` — Getter/setter on consumer's output level
- L61 _protected prototype_ `bool SetOutputLevel(const FString& LevelName);`
- L63 _protected prototype_ `virtual bool SetLevelNameImplementation(const FString& InLevelName, FText& OutFailureReason, const bool bIsAutomated) override;`
- L64 _protected prototype_ `virtual bool SetTargetContentFolderImplementation(const FString& InTargetContentFolder, FText& OutFailureReason, const bool bIsAutomated) override;`
- L66 _protected prototype_ `virtual bool Initialize() override;`
- L67 _protected prototype_ `virtual bool Run() override;`
- L68 _protected prototype_ `virtual void Reset() override;`
- L73 _protected member_ `FString DatasmithSceneObjectPath;` — `UPROPERTY(BlueprintReadOnly, Category = DatasmithConsumerInternal)` — Path to UDatasmithScene potentially linked to
- L77 _protected member_ `FString OutputLevelObjectPath;` — `UPROPERTY(BlueprintReadOnly, Category = DatasmithConsumerInternal)` — Path to ULevel potentially linked to
- L81 _private prototype_ `bool BuildContexts();` — Temporary code to work with UDataprepContentConsumer
- L84 _private prototype_ `void UpdateScene();` — Move assets if destination package path has changed since last call to UDatasmithConsumer::Run
- L87 _private prototype_ `void ApplySubLevelDirective(const TArray<UPackage*>& PackagesToCheck);` — Process actors which have been marked with a UDataprepConsumerUserData
- L90 _private prototype_ `ULevel* FindOrAddLevel(const FString& InLevelName);` — Find or add a new level to the target world
- L98 _private prototype_ `bool ValidateAssets();` — Check if output directives set on assets or actors can be honored If some issues are identified, the user is asked to proceed with execution of consumer or not. @return True if no issue or user has accepted to continue with execution of consumer If in command mode, the default behavior is to continue.
- L101 _private prototype_ `bool CreateWorld();` — Create the world which will be used to execute the consumer
- L104 _private prototype_ `void ClearWorld();` — Delete the world which was used to execute the consumer
- L107 _private prototype_ `bool FinalizeRun();` — Save all assets and levels
- L110 _private prototype_ `bool CanCreateLevel( const FString& RequestedFolder, const FString& RequestedName, const bool bShowDialog);` — Returns true if a umap file can be saved in specified folder with specified name
- L113 _private member_ `TUniquePtr< FDatasmithImportContext > ImportContextPtr;`
- L114 _private member_ `TUniquePtr< FDataprepWorkReporter > ProgressTaskPtr;`
- L117 _private member_ `TStrongObjectPtr<UWorld> WorkingWorld;` — World used by the consumer to create new output levels
- L120 _private member_ `FSoftObjectPath OutputLevelSoftObject_DEPRECATED;` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = ""))`
- L123 _private member_ `TWeakObjectPtr<UDatasmithScene> DatasmithSceneWeakPtr;` — `UPROPERTY(Transient)`
- L126 _private member_ `ULevel* PrimaryLevel;` — Level associated with the consumer
- L129 _private member_ `ULevel* OriginalCurrentLevel;` — Current level used by the global world before executing the consumer

#### Free symbols / members of external scopes

- L17 _namespace_ `namespace DatasmithConsumerDetailsUtil`

### `Plugins/Enterprise/DatasmithImporter/Source/DatasmithImporter/Private/DatasmithDataprepFetcher.h` (Private)


#### enum `EMetadataKeyMatchingCriteria`  
`enum EMetadataKeyMatchingCriteria : int`  
_L12-16_
- reflection: `UENUM()`
- L14 _public enumerator_ `ExactMatch`
- L15 _public enumerator_ `Contains`

#### class `UDatasmithStringMetadataValueFetcher`  
`class UDatasmithStringMetadataValueFetcher final : public UDataprepStringsArrayFetcher`  
_L19-38_
- reflection: `UCLASS(BlueprintType, NotBlueprintable, Meta = (DisplayName="Metadata Value", ToolTip="Filter objects based on the key value of their metadata."))`
- inherits: `UDataprepStringsArrayFetcher`
- L24 _public prototype_ `virtual TArray<FString> Fetch_Implementation(const UObject* Object, bool& bOutFetchSucceded) const override;`
- L28 _public prototype_ `virtual FText GetNodeDisplayFetcherName_Implementation() const;`
- L29 _public prototype_ `virtual bool IsThreadSafe() const final;`
- L33 _public member_ `TEnumAsByte<EMetadataKeyMatchingCriteria> KeyMatch;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Key")`
- L37 _public member_ `FName Key;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Key")` — The key for the for the string

### `Plugins/Enterprise/DatasmithImporter/Source/DatasmithImporter/Private/DatasmithDataprepOperation.h` (Private)


#### class `UDataprepSetupStaticLightingOperation`  
`class UDataprepSetupStaticLightingOperation : public UDataprepOperation`  
_L12-41_
- reflection: `UCLASS(Experimental, Category = LightmapOptions, Meta = (DisplayName = "Setup Static Lighting", ToolTip = "For each static mesh to process, setup the settings to enable lightmap UVs generation and compute the lightmap resolution."))`
- inherits: `UDataprepOperation`
- L16 _private function_ `UDataprepSetupStaticLightingOperation() : bEnableLightmapUVGeneration(true), LightmapResolutionIdealRatio(0.2f)`
- L25 _public member_ `bool bEnableLightmapUVGeneration;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LightmapOptions, meta = (DisplayName = "Enable Lightmap UV Generation", ToolTip = "Enable the lightmap UV generation."))` — The value to set for the generate lightmap uvs flag on each static mesh
- L28 _public member_ `float LightmapResolutionIdealRatio;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LightmapOptions, meta = (DisplayName = "Resolution Ideal Ratio", ToolTip = "The ratio used to compute the resolution of the lightmap."))`
- L33 _public function_ `virtual FText GetCategory_Implementation() const override`
- L39 _protected prototype_ `virtual void OnExecution_Implementation(const FDataprepContext& InContext) override;`

### `Plugins/Enterprise/DatasmithImporter/Source/DatasmithImporter/Private/DatasmithFileProducer.h` (Private)


#### class `UDatasmithFileProducer`  
`class UDatasmithFileProducer : public UDataprepContentProducer`  
_L28-120_
- reflection: `UCLASS(Experimental, HideCategories = (DatasmithProducer_Internal))`
- inherits: `UDataprepContentProducer`
- L34 _public prototype_ `virtual void PostEditUndo() override;` — UObject interface
- L35 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L39 _public prototype_ `void SetFilePath( const FString& InFilePath );` — Update producer with the desired file
- L41 _public function_ `const FString& GetFilePath() const`
- L44 _public prototype_ `static void LoadDefaultSettings();` — Load default settings for file producer in DatasmithImporter.ini
- L47 _public function_ `void SetFilename(const FString& InFilename)` — `UE_DEPRECATED(4.26, "SetFilename was renamed to SetFilePath")`
- L52 _public prototype_ `void OnChangeImportSettings();`
- L54 _public prototype_ `TArray<TObjectPtr<UDatasmithOptionsBase>> GetTranslatorImportOptions();`
- L56 _public function_ `void SetTranslatorImportOptions(TArray<TObjectPtr<UDatasmithOptionsBase>> InOptions)`
- L62 _public prototype_ `virtual const FText& GetLabel() const override;`
- L63 _public prototype_ `virtual const FText& GetDescription() const override;`
- L64 _public prototype_ `virtual FString GetNamespace() const override;`
- L65 _public prototype_ `virtual bool Supersede(const UDataprepContentProducer* OtherProducer) const override;`
- L66 _public prototype_ `virtual bool CanAddToProducersArray(bool bIsAutomated) override;`
- L69 _protected prototype_ `virtual bool Initialize() override;`
- L70 _protected prototype_ `virtual bool Execute(TArray< TWeakObjectPtr< UObject > >& OutAssets) override;`
- L71 _protected prototype_ `virtual void Reset() override;`
- L75 _protected member_ `FString FilePath;` — `UPROPERTY(EditAnywhere, Category = DatasmithProducer)`
- L77 _protected member_ `TWeakObjectPtr<ADatasmithSceneActor> ImportSceneActor;`
- L81 _private prototype_ `void SceneElementToWorld();` — Fill up world with content of Datasmith scene element
- L84 _private prototype_ `void PreventNameCollision();` — Fill up world with content of Datasmith scene element
- L87 _private prototype_ `void OnFilePathChanged();` — Does what is required after setting a new FilePath
- L90 _private prototype_ `void UpdateName();` — Update the name of the producer based on the filename
- L92 _private prototype_ `bool InitTranslator();`
- L95 _private member_ `TUniquePtr< FDatasmithImportContext > ImportContextPtr;`
- L96 _private member_ `TUniquePtr< FDataprepWorkReporter > ProgressTaskPtr;`
- L97 _private member_ `TSharedPtr< UE::DatasmithImporter::FExternalSource > ExternalSourcePtr;`
- L99 _private member_ `TArray<TObjectPtr<UDatasmithOptionsBase>> ImportOptionsOverride;`
- L102 _private member_ `TObjectPtr<UDatasmithScene> DatasmithScene;` — `UPROPERTY(Transient, DuplicateTransient)`
- L105 _private member_ `TObjectPtr<UPackage> TransientPackage = nullptr;` — `UPROPERTY(Transient, DuplicateTransient)`
- L107 _private member_ `TArray< TWeakObjectPtr< UObject > > Assets;`
- L110 _private member_ `TArray<TObjectPtr<UDatasmithOptionsBase>> TranslatorImportOptions;` — `UPROPERTY()`
- L113 _private member_ `bool bTranslatorImportOptionsInitialized = false;` — `UPROPERTY()`
- L115 _private member_ `static FDatasmithTessellationOptions DefaultTessellationOptions;`
- L116 _private member_ `static FDatasmithImportBaseOptions DefaultImportOptions;`

#### class `FDataprepContentProducerDetails`  
`class FDataprepContentProducerDetails : public IDetailCustomization`  
_L122-133_
- inherits: `IDetailCustomization`
- L125 _public prototype_ `virtual void CustomizeDetails( IDetailLayoutBuilder& DetailBuilder ) override;`
- L126 _public prototype_ `FSlateColor GetStatusColorAndOpacity() const;`
- L127 _public prototype_ `bool IsProducerSuperseded() const;`
- L130 _protected member_ `class UDataprepAssetProducers* AssetProducers = nullptr;`
- L131 _protected member_ `UDataprepContentProducer* Producer = nullptr;`
- L132 _protected member_ `int32 ProducerIndex = INDEX_NONE;` — This index does not change for the lifetime of the property widget

#### class `FDatasmithFileProducerDetails`  
`class FDatasmithFileProducerDetails : public FDataprepContentProducerDetails`  
_L136-143_
- inherits: `FDataprepContentProducerDetails`
- desc: Customization of the details of the Datasmith Scene for the data prep editor.
- L139 _public function_ `static TSharedRef< IDetailCustomization > MakeDetails()`
- L142 _public prototype_ `virtual void CustomizeDetails( IDetailLayoutBuilder& DetailBuilder ) override;` — Called when details should be customized

#### class `UDatasmithDirProducer`  
`class UDatasmithDirProducer : public UDataprepContentProducer`  
_L146-254_
- reflection: `UCLASS(Experimental, HideCategories = (DatasmithDirProducer_Internal))`
- inherits: `UDataprepContentProducer`
- L151 _protected prototype_ `UDatasmithDirProducer();`
- L155 _public prototype_ `void SetFolderPath(const FString& InFolderPath);` — Update producer with the selected folder name
- L156 _public prototype_ `FString GetFolderPath() const;`
- L158 _public prototype_ `void SetExtensionString(const FString& InExtensionString);`
- L159 _public prototype_ `FString GetExtensionString() const;`
- L161 _public prototype_ `void SetIsRecursive(bool bInRecursive);`
- L162 _public prototype_ `bool IsRecursive() const;`
- L165 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L166 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L170 _public function_ `void SetFolderName(const FString& InFolderName)` — `UE_DEPRECATED(4.26, "SetFolderName was renamed to SetFolderPath")`
- L176 _public prototype_ `virtual const FText& GetLabel() const override;`
- L177 _public prototype_ `virtual const FText& GetDescription() const override;`
- L178 _public prototype_ `virtual FString GetNamespace() const override;`
- L179 _public prototype_ `virtual bool Supersede(const UDataprepContentProducer* OtherProducer) const override;`
- L180 _public prototype_ `virtual bool CanAddToProducersArray(bool bIsAutomated) override;`
- L183 _protected prototype_ `virtual bool Initialize() override;`
- L184 _protected prototype_ `virtual bool Execute(TArray< TWeakObjectPtr< UObject > >& OutAssets) override;`
- L185 _protected prototype_ `virtual void Reset() override;`
- L188 _protected prototype_ `void OnChangeImportSettings();`
- L189 _protected prototype_ `void SetFileProducerSettings();`
- L195 _private member_ `FString FolderPath;` — `UPROPERTY(EditAnywhere, Category = DatasmithDirProducer_Internal)` — The folder were datasmith will look for files to import
- L199 _private member_ `FString ExtensionString;` — `UPROPERTY(EditAnywhere, Category = DatasmithDirProducer)` — Semi-column separated string containing the extensions to consider. By default, set to * to get all extensions.
- L203 _private member_ `bool bRecursive;` — `UPROPERTY(EditAnywhere, Category = DatasmithDirProducer, meta = (ToolTip = "If checked, sub-directories will be traversed"))` — If true the producer will look for the files in the sub-directories.
- L206 _private prototype_ `void OnFolderPathChanged();` — Called if the folder path has changed
- L209 _private prototype_ `void OnExtensionsChanged();` — Called if ExtensionString has changed
- L212 _private prototype_ `void OnRecursivityChanged();` — Called if bRecursive has changed
- L215 _private prototype_ `void UpdateExtensions();` — Helper function to extract set of extensions based on content of ExtensionString and supported formats
- L218 _private prototype_ `TSet<FString> GetSetOfFiles() const;` — Helper function to get all matching files in FolderPath based on extensions set
- L221 _private prototype_ `void UpdateName();` — Update the name of the producer based on the directory name
- L224 _private prototype_ `bool ImportAsPlmXml(UPackage* RootPackage, TArray< TWeakObjectPtr< UObject > >& OutAssets, TArray<FString>& FilesCouldntBeProcessedWithPlmXml);` — Try import files in the FolderPath as parts of constructed PLMXML file
- L233 _private prototype_ `void FixPlmXmlHierarchy();` — Make resulting scene hierarchy look the way it looks when each of files is imported individually Which means each separate CAD file should have DatasmithSceneActor as root actor In order to have this 1. Root ImportSceneActor is removed 2. Every child of this ImportSceneActor is converted into DatasmithSceneActor, filling RelatedChildren from this child's subtree
- L236 _private member_ `bool bHasWildCardSearch;` — Indicates if ExtensionString contains "*.*"
- L239 _private member_ `TSet< FString > FixedExtensionSet;` — Set of extensions to look for
- L242 _private member_ `TSet< FString > FilesToProcess;` — Set of files matching folder and extensions
- L245 _private member_ `TObjectPtr<UDatasmithFileProducer> FileProducer;` — `UPROPERTY(Transient, DuplicateTransient)`
- L248 _private member_ `TObjectPtr<UDatasmithCommonTessellationOptions> TessellationOptions;` — `UPROPERTY()`
- L250 _private member_ `static TSet< FString > SupportedFormats;`

#### class `FDatasmithDirProducerDetails`  
`class FDatasmithDirProducerDetails : public FDataprepContentProducerDetails`  
_L257-264_
- inherits: `FDataprepContentProducerDetails`
- desc: Customization of the details of the Datasmith Scene for the data prep editor.
- L260 _public function_ `static TSharedRef< IDetailCustomization > MakeDetails()`
- L263 _public prototype_ `virtual void CustomizeDetails( IDetailLayoutBuilder& DetailBuilder ) override;` — Called when details should be customized

#### Free symbols / members of external scopes

- L22 _namespace_ `namespace UE`
- L22 _namespace_ `namespace DatasmithImporter` (scope `UE`)

### `Plugins/Enterprise/DatasmithImporter/Source/DatasmithImporter/Private/ObjectElements/DatasmithUElementsUtils.h` (Private)


#### class `FDatasmithUElementsUtils`  
`class FDatasmithUElementsUtils`  
_L11-168_
- L34 _public function_ `static UElement* FindOrAddElement(UObject* Outer, TMap<TWeakPtr<IElement>, TMapValue>& Map, const TSharedPtr<IElement>& InElement, SetOp Assign)`
- L71 _public function_ `template<typename TargetType, typename Func> static inline bool ForVariantElement(const TSharedPtr<IDatasmithScene>& RootObject, Func Function)` — Utility to help iterating over the nested structure of the variant objects Examples: ForVariantElement<IDatasmithVariantElement>(SceneElement, [](TSharedPtr<IDatasmithVariantElement> Var) { // Do something with all variants in the scene return true; // It will keep iterating while the lambda returns true }); ForVariantElement<IDatasmithBasePropertyCaptureElement>(SomeVariantSet, [](TSharedPtr<IDatasmithBasePropertyCaptureElement> Prop) { // Do something with all properties of a variant set return true; // It will keep iterating while the lambda returns true });
- L92 _public function_ `template<typename TargetType, typename Func> static inline bool ForVariantElement(const TSharedPtr<IDatasmithLevelVariantSetsElement>& RootObject, Func Function)`
- L114 _public function_ `template<typename TargetType, typename Func> static inline bool ForVariantElement(const TSharedPtr<IDatasmithVariantSetElement>& RootObject, Func Function)`
- L135 _public function_ `template<typename TargetType, typename Func> static inline bool ForVariantElement(const TSharedPtr<IDatasmithVariantElement>& RootObject, Func Function)`
- L156 _public function_ `template<typename TargetType, typename Func> static inline typename TEnableIf<std::is_same_v<TargetType, IDatasmithBasePropertyCaptureElement>, bool>::Type ForVariantElement(const TSharedPtr<IDatasmithActorBindingElement>& RootObject, Func Function)`

#### struct `FDatasmithUElementsUtils::TFindOrAddTraits`  
`template <typename T> struct TFindOrAddTraits<T*>`  
_L18-21_
- L20 _public typedef_ `using TElement = T;`

#### struct `FDatasmithUElementsUtils::TFindOrAddTraits`  
`template <typename T> struct TFindOrAddTraits<TObjectPtr<T>>`  
_L24-27_
- L20 _public typedef_ `using TElement = T;`

### `Plugins/Enterprise/DatasmithImporter/Source/DatasmithImporter/Private/UI/DatasmithConsumerDetails.h` (Private)


#### class `FDatasmithConsumerDetails`  
`class FDatasmithConsumerDetails : public IDetailCustomization`  
_L12-19_
- inherits: `IDetailCustomization`
- desc: Customization of the details of the Datasmith Consumer for the data prep editor.
- L15 _public function_ `static TSharedRef< IDetailCustomization > MakeDetails()`
- L18 _public prototype_ `virtual void CustomizeDetails( IDetailLayoutBuilder& DetailBuilder ) override;` — Called when details should be customized

### `Plugins/Enterprise/DatasmithImporter/Source/DatasmithImporter/Private/UVTools/UVGenerationDataprepOperation.h` (Private)


#### enum `EUnwrappedUVDatasmithOperationChannelSelection`  
`enum class EUnwrappedUVDatasmithOperationChannelSelection : uint8`  
_L11-15_
- reflection: `UENUM()`
- L13 _public enumerator_ `FirstEmptyChannel UMETA(Tooltip = "Generate the unwrapped UV in the first UV channel that is empty.")`
- L14 _public enumerator_ `SpecifyChannel UMETA(Tooltip = "Manually select the target UV channel for the unwrapped UV generation.")`

#### class `UUVGenerationFlattenMappingOperation`  
`class UUVGenerationFlattenMappingOperation : public UDataprepOperation`  
_L18-49_
- reflection: `UCLASS(Experimental, Category = MeshOperation, Meta = (DisplayName = "Generate Unwrapped UVs", ToolTip = "For each static mesh to process, generate an unwrapped UV map in the specified channel"))`
- inherits: `UDataprepOperation`
- L22 _private function_ `UUVGenerationFlattenMappingOperation() : ChannelSelection(EUnwrappedUVDatasmithOperationChannelSelection::FirstEmptyChannel), UVChannel(0), AngleThreshold(66.f)`
- L31 _public member_ `EUnwrappedUVDatasmithOperationChannelSelection ChannelSelection;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UV Generation Settings")`
- L34 _public member_ `int UVChannel;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UV Generation Settings", meta = (DisplayName = "UV Channel", ToolTip = "The UV channel where to generate the flatten mapping", ClampMin = "0", ClampMax = "7", EditCondition = "ChannelSelection == EUnwrappedUVDatasmithOperationChannelSelection::SpecifyChannel"))`
- L37 _public member_ `float AngleThreshold;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UV Generation Settings", meta = (ClampMin = "1", ClampMax = "90"))`
- L41 _public function_ `virtual FText GetCategory_Implementation() const override`
- L47 _protected prototype_ `virtual void OnExecution_Implementation(const FDataprepContext& InContext) override;`

### `Plugins/Enterprise/DatasmithImporter/Source/DatasmithImporter/Private/Utility/DatasmithImportFactoryHelper.h` (Private)


#### Free symbols / members of external scopes

- L13 _namespace_ `namespace DatasmithImportFactoryHelper`
- L15 _prototype_ `TSharedPtr<FJsonObject> LoadJsonFile(const FString& JsonFilename);` (scope `DatasmithImportFactoryHelper`)
- L17 _prototype_ `void ComputeBounds( USceneComponent* ActorComponent, FBox& Bounds );` (scope `DatasmithImportFactoryHelper`)
- L19 _prototype_ `void SetupSceneViewport(AActor* SceneActor, TArray<FAssetData>& AssetDataList);` (scope `DatasmithImportFactoryHelper`)

### `Plugins/Enterprise/DatasmithImporter/Source/DatasmithImporter/Private/Utility/DatasmithImporterImpl.h` (Private)


#### class `FDatasmithImporterImpl`  
`class FDatasmithImporterImpl`  
_L24-102_
- L27 _public prototype_ `static void ReportProgress(FScopedSlowTask* SlowTask, const float ExpectedWorkThisFrame, const FText& Text);`
- L29 _public prototype_ `static bool HasUserCancelledTask(FFeedbackContext* FeedbackContext);`
- L31 _public prototype_ `static UObject* PublicizeAsset( UObject* SourceAsset, const TCHAR* DestinationPath, UObject* ExistingAsset );`
- L39 _public prototype_ `static bool CheckAssetPersistenceValidity(const FString& PackageName, FDatasmithImportContext& ImportContext, const FString& Extension, FText& OutReason);` — Verifies the input asset can successfully be saved and/or cooked. The code below is heavily inspired from: - ContentBrowserUtils::IsValidPackageForCooking #ueent_todo Make ContentBrowserUtils::IsValidPackageForCooking public. Not game to do it so late in 4.22
- L40 _public prototype_ `static bool CheckAssetPersistenceValidity(const FString& PackageName, FDatasmithImportContext& ImportContext, const FString& Extension);`
- L42 _public prototype_ `static void CheckAssetPersistenceValidity(UObject* Asset, FDatasmithImportContext& ImportContext);`
- L45 _public prototype_ `static void SetTexturesMode( FDatasmithImportContext& ImportContext );` — Set the texture mode on each texture element based on its usage in the materials
- L47 _public prototype_ `static void CompileMaterial( UObject* Material, FMaterialUpdateContext* MaterialUpdateContext = nullptr);`
- L49 _public prototype_ `static void FixReferencesForObject( UObject* Object, const TMap< UObject*, UObject* >& ReferencesToRemap );`
- L51 _public typedef_ `typedef TPair< TStrongObjectPtr< UDatasmithObjectTemplate >, TStrongObjectPtr< UDatasmithObjectTemplate > > FMigratedTemplatePairType;`
- L59 _public prototype_ `static TArray< FMigratedTemplatePairType > MigrateTemplates( UObject* SourceObject, UObject* DestinationObject, const TMap< UObject*, UObject* >* ReferencesToRemap, bool bIsForActor );` — Creates templates to apply the values from the SourceObject on the DestinationObject. @returns An array of template pairs. The key is the template for the object, the value is a template to force apply to the object, it contains the values from the key and any overrides that were present on the DestinationObject.
- L69 _public prototype_ `static void ApplyMigratedTemplates( TArray< FMigratedTemplatePairType >& MigratedTemplates, UObject* DestinationObject );` — Applies the templates created from MigrateTemplates to DestinationObject. For an Object A that should be duplicated over an existing A', for which we want to keep the Datasmith overrides: - Call MigrateTemplates(A, A') - Duplicate A over A' - ApplyMigratedTemplates(A')
- L71 _public prototype_ `static UObject* FinalizeAsset( UObject* SourceAsset, const TCHAR* AssetPath, UObject* ExistingAsset, TMap< UObject*, UObject* >* ReferencesToRemap );`
- L73 _public prototype_ `static void DeleteImportSceneActorIfNeeded(FDatasmithActorImportContext& ActorContext, bool bForce = false);`
- L75 _public prototype_ `static UActorComponent* PublicizeComponent(UActorComponent& SourceComponent, UActorComponent* DestinationComponent, AActor& DestinationActor, TMap< UObject*, UObject* >& ReferencesToRemap, TArray<uint8>& ReusableBuffer);`
- L77 _public prototype_ `static USceneComponent* FinalizeSceneComponent(FDatasmithImportContext& ImportContext, USceneComponent& SourceComponent, AActor& DestinationActor, USceneComponent* DestinationParent, TMap<UObject *, UObject *>& ReferencesToRemap, TArray<uint8>& ReusableBuffer, TArray<TPair<USceneComponent&, TArray<FMigratedTemplatePairType>>>& ComponentsToApplyMigratedTemplat);`
- L79 _public prototype_ `static void FinalizeComponents(FDatasmithImportContext& ImportContext, AActor& SourceActor, AActor& DestinationActor, TMap<UObject *, UObject *>& ReferencesToRemap, TArray<uint8>& ReusableBuffer, TArray<TPair<USceneComponent&, TArray<FMigratedTemplatePairType>>>& ComponentsToApplyMigratedTemplat);`
- L81 _public prototype_ `static void PublicizeSubObjects(UObject& SourceObject, UObject& DestinationObject, TMap< UObject*, UObject* >& ReferencesToRemap, TArray<uint8>& ReusableBuffer);`
- L83 _public prototype_ `static void CopyObject(UObject& Source, UObject& Destination, TArray<uint8>& TempBuffer);`
- L85 _public prototype_ `static void GatherUnsupportedVirtualTexturesAndMaterials(const TMap<TSharedRef< IDatasmithBaseMaterialElement >, UMaterialInterface*>& ImportedMaterials, TSet<UTexture2D*>& VirtualTexturesToConvert, TArray<UMaterial*>& MaterialsToRefreshAfterVirtualTextureConversion);`
- L87 _public prototype_ `static void ConvertUnsupportedVirtualTexture(FDatasmithImportContext& ImportContext, TSet<UTexture2D*>& VirtualTexturesToConvert, const TMap<UObject*, UObject*>& ReferencesToRemap);`

#### struct `FDatasmithImporterImpl::FScopedFinalizeActorChanges`  
`struct FScopedFinalizeActorChanges`  
_L92-101_
- desc: Helper struct used to manage and validate the actor's state when modifying it during the finalization.
- L94 _public member_ `FDatasmithImportContext& ImportContext;`
- L95 _public member_ `TSet<UActorComponent*> ComponentsToValidate;`
- L96 _public member_ `AActor* FinalizedActor;`
- L98 _public prototype_ `FScopedFinalizeActorChanges(AActor* InFinalizedActor, FDatasmithImportContext& InImportContext);`
- L100 _public prototype_ `~FScopedFinalizeActorChanges();`

### `Plugins/Enterprise/DatasmithImporter/Source/DatasmithImporter/Public/ActorFactoryDatasmithScene.h` (Public)


#### class `UActorFactoryDatasmithScene`  
`class UActorFactoryDatasmithScene : public UActorFactory`  
_L12-25_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UActorFactory`
- L17 _public prototype_ `static void SpawnRelatedActors( class ADatasmithSceneActor* DatasmithSceneActor, bool bReimportDeletedActors );`
- L20 _public prototype_ `virtual bool CanCreateActorFrom( const FAssetData& AssetData, FText& OutErrorMsg ) override;`
- L23 _protected prototype_ `virtual AActor* SpawnActor( UObject* Asset, ULevel* InLevel, const FTransform& Transform, const FActorSpawnParameters& InSpawnParams) override;`

### `Plugins/Enterprise/DatasmithImporter/Source/DatasmithImporter/Public/DatasmithActorImporter.h` (Public)


#### class `FDatasmithActorImporter`  
`class FDatasmithActorImporter`  
_L33-154_
- L47 _public prototype_ `static AActor* ImportActor( UClass* ActorClass, const TSharedRef< IDatasmithActorElement >& ActorElement, FDatasmithImportContext& ImportContext, EDatasmithImportActorPolicy ImportActorPolicy, TFunction< void( AActor* ) > PostSpawnFunc = TFunction< void( AActor* ) >() );` — Imports an actor of class ActorClass based on ActorElement @param ActorClass		The class of the actor to import @param ActorElement		The Datasmith element containing the data for the actor @param ImportContext		The context in which we're importing @param ImportActorPolicy	How to handle existing and deleted actors @param PostSpawnFunc		Function to invoke right after spawning a new actor, before any additional setup is performed @return	Returns the imported actor. The root component is not registered to allow edits. The caller needs to register it when the setup is complete.
- L61 _public prototype_ `static USceneComponent* ImportSceneComponent( UClass* ComponentClass, const TSharedRef< IDatasmithActorElement >& ActorElement, FDatasmithImportContext& ImportContext, UObject* Outer, FDatasmithActorUniqueLabelProvider& UniqueNameProvider );` — Imports a scene component of class ComponentClass based on ActorElement Will add the component as an instance component of Outer if Outer is an Actor @param ComponentClass	The class of the scene component to import. Needs to be a USceneComponent or a child of USceneComponent @param ActorElement		The Datasmith element containing the data for the component @param ImportContext		The context in which we're importing @param Outer				The outer that will contain the component @return	Returns the importer scene component. The component is not registered to allow edits. The caller needs to register it when the setup is complete.
- L66 _public prototype_ `static AActor* ImportBaseActor( FDatasmithImportContext& ImportContext, const TSharedRef< IDatasmithActorElement >& ActorElement );` — Spawns an actor with a SceneComponent
- L67 _public prototype_ `static USceneComponent* ImportBaseActorAsComponent( FDatasmithImportContext& ImportContext, const TSharedRef< IDatasmithActorElement >& ActorElement, UObject* Outer, FDatasmithActorUniqueLabelProvider& UniqueNameProvider );`
- L72 _public prototype_ `static AStaticMeshActor* ImportStaticMeshActor( FDatasmithImportContext& ImportContext, const TSharedRef< IDatasmithMeshActorElement >& MeshActorElement );` — Spawns a static mesh actor
- L73 _public prototype_ `static UStaticMeshComponent* ImportStaticMeshComponent( FDatasmithImportContext& ImportContext, const TSharedRef< IDatasmithMeshActorElement >& MeshActorElement, UObject* Outer, FDatasmithActorUniqueLabelProvider& UniqueNameProvider );`
- L77 _public prototype_ `static AActor* ImportClothActor( FDatasmithImportContext& ImportContext, const TSharedRef< IDatasmithClothActorElement >& ClothActorElement );` — `UE_DEPRECATED(5.5, "The experimental Cloth importer is no longer supported.")`
- L83 _public prototype_ `static AActor* ImportCameraActor( FDatasmithImportContext& ImportContext, const TSharedRef< IDatasmithCameraActorElement >& CameraActorElement );` — Spawns a cine camera actor
- L88 _public prototype_ `static AActor* ImportLightActor( FDatasmithImportContext& ImportContext, const TSharedRef< IDatasmithLightActorElement >& LightActorElement );` — Spawns a light actor. The light class depends on the LightActorElement type.
- L93 _public prototype_ `static AActor* ImportEnvironment( FDatasmithImportContext& ImportContext, const TSharedRef< IDatasmithEnvironmentElement >& EnvironmentElement );` — Spawns a cine camera actor
- L98 _public prototype_ `static AActor* ImportCustomActor( FDatasmithImportContext& ImportContext, const TSharedRef< IDatasmithCustomActorElement >& CustomActorElement, FDatasmithActorUniqueLabelProvider& UniqueNameProvider );` — Spawns an actor with a class defined by the CustomActorElement class name
- L103 _public prototype_ `static AActor* ImportDecalActor( FDatasmithImportContext& ImportContext, const TSharedRef< IDatasmithDecalActorElement >& DecalActorElement, FDatasmithActorUniqueLabelProvider& UniqueNameProvider );` — Spawns a Decal actor
- L108 _public prototype_ `static AActor* ImportLandscapeActor( FDatasmithImportContext& ImportContext, const TSharedRef< IDatasmithLandscapeElement >& LandscapeActorElement );` — Spawns a landscape actor
- L113 _public prototype_ `static AActor* ImportHierarchicalInstancedStaticMeshAsActor( FDatasmithImportContext& ImportContext, const TSharedRef< IDatasmithHierarchicalInstancedStaticMeshActorElement >& HierarchicalInstancedStatictMeshActorElement, FDatasmithActorUniqueLabelProvider& UniqueNameProvider );` — Spawns an actor with a hierarchical instanced static mesh component
- L115 _public prototype_ `static UHierarchicalInstancedStaticMeshComponent* ImportHierarchicalInstancedStaticMeshComponent( FDatasmithImportContext& ImportContext, const TSharedRef< IDatasmithHierarchicalInstancedStaticMeshActorElement >& HierarchicalInstancedStaticMeshActorElement, UObject* Outer, FDatasmithActorUniqueLabelProvider& UniqueNameProvider );`
- L125 _public prototype_ `static void SetupActorProperties(AActor* ImportedActor, const TSharedRef< IDatasmithActorElement >& ActorElement, FDatasmithImportContext& ImportContext);` — Handle Actor common properties (Layers, Tags) @param ImportedActor	    The actual actor being imported @param ActorElement	    The Datasmith element containing the data for the component @param ImportContext	    The context in which we're importing
- L126 _public prototype_ `static void SetupSceneComponent( USceneComponent* SceneComponent, const TSharedRef< IDatasmithActorElement >& ActorElement, USceneComponent* Parent );`
- L131 _public prototype_ `static void SetupStaticMeshComponent( FDatasmithImportContext& ImportContext, UStaticMeshComponent* StaticMeshComponent, const TSharedRef< IDatasmithMeshActorElement >& MeshActorElement );` — Sets the properties of a static mesh component based on the MeshActorElement values
- L136 _public prototype_ `static void SetupHierarchicalInstancedStaticMeshComponent( FDatasmithImportContext& ImportContext, UHierarchicalInstancedStaticMeshComponent* HierarchicalInstancedStaticMeshComponent, const TSharedRef< IDatasmithHierarchicalInstancedStaticMeshActorElement >& HierarchicalInstancedStatictMeshActorElement );` — Sets the properties of a hierarchical instanced static mesh component based on the HierarchicalInstancedStatictMeshActorElement values
- L147 _protected prototype_ `static TSet<FName> ParseCsvLayers(const TCHAR* CsvLayersNames);` — Parse Layer names to a Set of FNames @param CsvLayerNames		Comma separated string containing the list of names of the layers the actor pertains to. @return Returns the Set of valid Layer names
- L152 _protected prototype_ `static void OverrideStaticMeshActorMaterials( const FDatasmithImportContext& ImportContext, const TSharedRef< IDatasmithMeshActorElement >& MeshActorElement, const UStaticMesh* StaticMesh, UDatasmithStaticMeshComponentTemplate* StaticMeshComponentTemplate );` — Sets the materials on a static mesh actor to override the ones from the static mesh
- L153 _protected prototype_ `static void OverrideStaticMeshActorMaterial( const FDatasmithImportContext& ImportContext, const TSharedRef< IDatasmithMaterialIDElement >& SubMaterial, UDatasmithStaticMeshComponentTemplate* StaticMeshComponentTemplate, int32 MeshSubMaterialIdx );`

### `Plugins/Enterprise/DatasmithImporter/Source/DatasmithImporter/Public/DatasmithBlueprintLibrary.h` (Public)


#### struct `FDatasmithImportFactoryCreateFileResult`  
`struct FDatasmithImportFactoryCreateFileResult`  
_L22-42_
- reflection: `USTRUCT(BlueprintType)`
- L25 _public prototype_ `FDatasmithImportFactoryCreateFileResult();`
- L27 _public prototype_ `void FillFromImportContext(const FDatasmithImportContext& ImportContext);`
- L31 _public member_ `TArray<TObjectPtr<class AActor>> ImportedActors;` — `UPROPERTY(BlueprintReadWrite, Transient, Category = Imported)` — List of all created actors if user requires to use multiple actors. The root actor will be the first element of the array.
- L35 _public member_ `TArray<TObjectPtr<class UObject>> ImportedMeshes;` — `UPROPERTY(BlueprintReadWrite, Transient, Category = Imported)` — Meshes created during the import process
- L38 _public member_ `bool bImportSucceed;` — `UPROPERTY(BlueprintReadWrite, Transient, Category = Result)`
- L41 _public member_ `TObjectPtr<UDatasmithScene> Scene;` — `UPROPERTY(BlueprintReadWrite, Transient, Category = Result)`

#### class `UDatasmithSceneElement`  
`class UDatasmithSceneElement : public UDatasmithSceneElementBase`  
_L46-146_
- reflection: `UCLASS()`
- inherits: `UDatasmithSceneElementBase`
- L57 _public prototype_ `static UDatasmithSceneElement* ConstructDatasmithSceneFromFile(const FString& FilePath);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Datasmith")` — Open an existing UDatasmith file from disk. @param	FilePath UDatasmith file path to open. ie: c:/MyFolder/MyFiles.udatasmith @return	The opened DatasmithScene, that can be modified and can be imported.
- L65 _public prototype_ `static UDatasmithSceneElement* ConstructDatasmithSceneFromSourceUri(const FString& SourceUri);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Datasmith")` — Open an existing Datasmith source from the SourceUri. @param	SourceUri Uri of the datasmith scene to open. ie: file://c:/MyFolder/MyFiles.udatasmith @return	The opened DatasmithScene, that can be modified and can be imported.
- L73 _public prototype_ `static UDatasmithSceneElement* ConstructDatasmithSceneFromCADFiles(const TArray<FString>& FilePaths);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Datasmith")` — Open set of CAD files as actors in a single datasmith scene Importing set of files into single DatasmithScene asset(with ImportScene) is supported only for CAD files @return	The opened DatasmithScene, that can be modified and can be imported.
- L81 _public prototype_ `static UDatasmithSceneElement* GetExistingDatasmithScene(const FString& AssetPath);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Datasmith")` — Open an existing DatasmithScene asset file from disk. @param   AssetPath Path of the DFatasmithScene asset (eg. "/Game/MyAsset") @return  The opened DatasmithScene, that can be modified and can be reimported.
- L88 _public prototype_ `bool TranslateScene();` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Datasmith")` — Trigger the translation phase, which populates the DatasmithScene. note that options should have been set before that and any modification to the scene made prior will be lost.
- L96 _public prototype_ `FDatasmithImportFactoryCreateFileResult ImportScene(const FString& DestinationFolder);` — `UFUNCTION(BlueprintCallable, Category = "Datasmith | Scene")` — Import a Datasmith Scene created with ConstructDatasmithSceneFromFile. @param	DestinationFolder	Destination of where you want the asset to be imported. ie: /Game/MyFolder1 @return	A structure that contains the created actor or the blueprint actor depending of the options specified at the import.
- L104 _public prototype_ `TArray<FDatasmithImportFactoryCreateFileResult> ImportScenes(const FString& DestinationFolder);` — `UFUNCTION(BlueprintCallable, Category = "Datasmith | Scene")` — Import a Datasmith Scene created with ConstructDatasmithSceneFromFiles into an array of scenes. @param	DestinationFolder	Destination of where you want the asset to be imported. ie: /Game/MyFolder1 @return	An array of import results corresponding to array of input files
- L111 _public prototype_ `FDatasmithImportFactoryCreateFileResult ReimportScene();` — `UFUNCTION(BlueprintCallable, Category = "Datasmith | Scene")` — Reimport a scene opened with GetExistingDatasmithScene @return	A structure that contains the created actor or the blueprint actor depending of the options specified at the import.
- L119 _public prototype_ `UObject* GetOptions(UClass* OptionType=nullptr);` — `UFUNCTION(BlueprintCallable, Category = "Datasmith | Scene", meta = (DeterminesOutputType = "OptionType"))` — Fetch the typed options for this scene @param OptionType	Type of the option structure to get @return The option structure found
- L126 _public prototype_ `TMap<UClass*, UObject*> GetAllOptions();` — `UFUNCTION(BlueprintCallable, Category = "Datasmith | Scene")` — List all the options structures applicable on this scene @return A map of options type to option object
- L130 _public prototype_ `UDatasmithImportOptions* GetImportOptions();` — `UE_DEPRECATED(4.23, "GetImportOptions is deprecated, use GetOptions instead.")` — `UFUNCTION(BlueprintCallable, Category = "Datasmith | Scene", meta=(DeprecatedFunction, DeprecationMessage="GetImportOptions is deprecated, use GetOptions instead."))`
- L137 _public prototype_ `void DestroyScene();` — `UFUNCTION(BlueprintCallable, Category = "Datasmith | Scene")` — Destroy reference to the udatasmith file. The Scene will no longer be available. DestroyScene is called automatically after ImportScene.
- L140 _private member_ `TSharedPtr<UE::DatasmithImporter::FExternalSource> ExternalSourcePtr;`
- L141 _private member_ `TUniquePtr<FDatasmithImportContext> ImportContextPtr;`
- L142 _private member_ `bool bTranslated = false;`
- L144 _private member_ `bool bMultifile = false;`
- L145 _private member_ `TArray<FString> FilePaths;`

#### class `UDatasmithStaticMeshBlueprintLibrary`  
`class UDatasmithStaticMeshBlueprintLibrary : public UBlueprintFunctionLibrary`  
_L150-180_
- reflection: `UCLASS(MinimalAPI, meta=(ScriptName="DatasmithStaticMeshLibrary"))`
- inherits: `UBlueprintFunctionLibrary`
- L163 _public prototype_ `static void ComputeLightmapResolution( const TArray< UObject* >& Objects, bool bApplyChanges, float IdealRatio = 0.2f );` — `UFUNCTION(BlueprintCallable, Category = "Datasmith | Static Mesh")` — Sets the proper lightmap resolution to get the desired lightmap density ratio @param	Objects					List of static meshes and static mesh actors to update. @param	bApplyChanges			Indicates if changes must be apply or not. @param	IdealRatio				The desired lightmap density ratio
- L174 _public prototype_ `static void SetupStaticLighting(const TArray< UObject* >& Objects, bool bApplyChanges, bool bGenerateLightmapUVs, float LightmapResolutionIdealRatio = 0.2f );` — `UFUNCTION(BlueprintCallable, Category = "Datasmith | Static Mesh")` — Setup the Lightmap UVs settings to enable or disable the lightmap generation on the static meshes found in the Assets list @param	Assets							List of objects to set the generate lightmap uvs flag on. Only Static Meshes and Static Mesh Components will be affected. @param	bApplyChanges					Indicates if changes must be apply or not. @param	bGenerateLightmapUVs			The value to set for the generate lightmap uvs flag. @param	LightmapResolutionIdealRatio	The desired lightmap density ratio
- L177 _private prototype_ `static void ComputeLightmapResolution(const TMap< UStaticMesh*, TSet< UStaticMeshComponent* > >& StaticMeshMap, bool bApplyChanges, float IdealRatio = 0.2f);`
- L179 _private prototype_ `static int32 ComputeLightmapResolution(UStaticMesh* StaticMesh, float IdealRatio, const FVector& StaticMeshScale);`

### `Plugins/Enterprise/DatasmithImporter/Source/DatasmithImporter/Public/DatasmithCameraImporter.h` (Public)


#### class `FDatasmithCameraImporter`  
`class FDatasmithCameraImporter`  
_L13-24_
- L16 _public prototype_ `static AActor* ImportCameraActor( const TSharedRef< IDatasmithCameraActorElement >& CameraElement, FDatasmithImportContext& ImportContext );`
- L17 _public prototype_ `static void PostImportCameraActor( const TSharedRef< IDatasmithCameraActorElement >& CameraElement, FDatasmithImportContext& ImportContext );`
- L19 _public prototype_ `static UCineCameraComponent* ImportCineCameraComponent( const TSharedRef< IDatasmithCameraActorElement >& CameraElement, FDatasmithImportContext& ImportContext, UObject* Outer, FDatasmithActorUniqueLabelProvider& UniqueNameProvider );`
- L22 _protected prototype_ `static void SetupCineCameraComponent( UCineCameraComponent* CineCameraComponent, const TSharedRef< IDatasmithCameraActorElement >& CameraElement );`

### `Plugins/Enterprise/DatasmithImporter/Source/DatasmithImporter/Public/DatasmithImportContext.h` (Public)


#### class `FDatasmithActorUniqueLabelProvider`  
`class FDatasmithActorUniqueLabelProvider : public FDatasmithUniqueNameProvider`  
_L58-63_
- inherits: `FDatasmithUniqueNameProvider`
- desc: Provides unique actor label. @note: Use a cache of known labels and a LUT of indices to speedup that step. Replaces FActorLabelUtilities::SetActorLabelUnique.
- L61 _public prototype_ `explicit FDatasmithActorUniqueLabelProvider(UWorld* World=nullptr);`
- L62 _public prototype_ `void PopulateLabelFrom(UWorld* World);`

#### class `FScopedLogger`  
`class FScopedLogger`  
_L69-98_
- desc: Helper class that handle Messaging service and formating. The instance destructor will display all messages pushed during its lifetime.
- L72 _public prototype_ `FScopedLogger(FName LogTitle, const FText& LogLabel);`
- L73 _public prototype_ `~FScopedLogger();`
- L75 _public prototype_ `FScopedLogger(const FScopedLogger&) = delete;`
- L76 _public prototype_ `FScopedLogger& operator = (const FScopedLogger&) = delete;`
- L77 _public prototype_ `FScopedLogger(FScopedLogger&&) = delete;`
- L78 _public prototype_ `FScopedLogger& operator = (FScopedLogger&&) = delete;`
- L81 _public prototype_ `TSharedRef<FTokenizedMessage> Push(EMessageSeverity::Type Severity, const FText& Message);` — Append a message
- L84 _public prototype_ `void Dump(bool bClearPrevious = false);` — Display pending messages, show the log window
- L87 _public prototype_ `void ClearLog();` — Clear log window
- L90 _private prototype_ `void ClearPending();`
- L93 _private member_ `FName Title;`
- L94 _private member_ `FMessageLogModule& MessageLogModule;`
- L95 _private member_ `TSharedPtr<IMessageLogListing> LogListing;`
- L96 _private member_ `TArray<TSharedRef<FTokenizedMessage>> TokenizedMessages;`
- L97 _private member_ `FCriticalSection TokenizedMessageCS;`

#### struct `FDatasmithActorImportContext`  
`struct FDatasmithActorImportContext`  
_L100-122_
- L102 _public prototype_ `explicit FDatasmithActorImportContext(UWorld* World = nullptr);`
- L104 _public prototype_ `bool Init();`
- L106 _public member_ `FDatasmithActorUniqueLabelProvider UniqueNameProvider;`
- L109 _public member_ `TObjectPtr<ADatasmithSceneActor> ImportSceneActor;` — The Scene actor on which the actors will be imported
- L112 _public member_ `TSet< ADatasmithSceneActor* > FinalSceneActors;` — The targeted scene actors for the finalize
- L115 _public member_ `ADatasmithSceneActor* CurrentTargetedScene;` — The targeted scene that the importer is currently finalizing
- L117 _public member_ `TObjectPtr<UWorld> ImportWorld;`
- L118 _public member_ `TObjectPtr<UWorld> FinalWorld;`
- L121 _public member_ `TSet< FName > NonImportedDatasmithActors;` — List of the datasmith actor element id that aren't imported because of the imports settings

#### struct `FDatasmithAssetsImportContext`  
`struct FDatasmithAssetsImportContext`  
_L124-209_
- L126 _public prototype_ `FDatasmithAssetsImportContext( FDatasmithImportContext& ImportContext );`
- L131 _public prototype_ `bool Init();` — Inits the context by setting the paths and creating the packages to be ready to import assets.
- L136 _public prototype_ `void ReInit(const FString& NewRootFolder);` — Updates all package paths based on a new root folder path e.g. "/Game/NewScene"
- L139 _public member_ `FDatasmithImportContext* ParentContext;` — The parent context that this context is a part of
- L140 _public function_ `const FDatasmithImportContext& GetParentContext() const`
- L141 _public function_ `FDatasmithImportContext& GetParentContext()`
- L145 _public member_ `FString RootFolderPath;` — Root folder path, used to derive the other paths
- L148 _public member_ `TStrongObjectPtr< UPackage > StaticMeshesFinalPackage;` — Package where new static meshes will be stored
- L151 _public member_ `TStrongObjectPtr< UPackage > MaterialsFinalPackage;` — Package where new materials will be stored
- L154 _public member_ `TStrongObjectPtr< UPackage > TexturesFinalPackage;` — Package where new textures will be stored
- L157 _public member_ `TStrongObjectPtr< UPackage > LightPackage;` — Package where new lights will be stored
- L160 _public member_ `TStrongObjectPtr< UPackage > LevelSequencesFinalPackage;` — Package where new level sequences will be stored
- L163 _public member_ `TStrongObjectPtr< UPackage > LevelVariantSetsFinalPackage;` — Package where new level sequences will be stored
- L166 _public member_ `FString TransientFolderPath;` — Transient folder path, used to derive the other transient paths
- L169 _public member_ `TStrongObjectPtr< UPackage > StaticMeshesImportPackage;` — Package where the static meshes are stored until they are finalized
- L172 _public member_ `TStrongObjectPtr< UPackage > TexturesImportPackage;` — Package where the textures are stored until they are finalized
- L175 _public member_ `TStrongObjectPtr< UPackage > MaterialsImportPackage;` — Package where the materials are stored until they are finalized
- L178 _public member_ `TStrongObjectPtr< UPackage > ReferenceMaterialsImportPackage;` — Package where the reference/parent materials are stored until they are finalized
- L181 _public member_ `TStrongObjectPtr< UPackage > MaterialFunctionsImportPackage;` — Package where the material functions are stored until they are finalized
- L184 _public member_ `TStrongObjectPtr< UPackage > LevelSequencesImportPackage;` — Package where the level sequences are stored until they are finalized
- L187 _public member_ `TStrongObjectPtr< UPackage > LevelVariantSetsImportPackage;` — Package where the level variant sets are stored until they are finalized
- L190 _public member_ `FDatasmithUniqueNameProvider MaterialNameProvider;` — Ensures uniqueness of the name of the materials being imported
- L193 _public member_ `FDatasmithUniqueNameProvider MaterialInstanceNameProvider;` — Ensures uniqueness of the name of the materials being imported in the reference material package
- L196 _public member_ `FDatasmithUniqueNameProvider MaterialFunctionNameProvider;` — Ensures uniqueness of the name of the material functions being imported in the material function material package
- L199 _public member_ `FDatasmithUniqueNameProvider StaticMeshNameProvider;` — Ensures uniqueness of the name of the static meshes being imported
- L202 _public member_ `FDatasmithUniqueNameProvider TextureNameProvider;` — Ensures uniqueness of the name of the textures being imported
- L205 _public member_ `TMap<FString, int32> MaterialsRequirements;` — Map of requirements on mesh building for each material
- L208 _public member_ `TSet<UTexture2D*> VirtualTexturesToConvert;` — Set of virtual textures that needs to be converted back to non-virtual texture because not all feature support them yet.

#### struct `FDatasmithImportContext`  
`struct FDatasmithImportContext`  
_L211-427_
- L214 _public prototype_ `FDatasmithImportContext(const FString& InFileName, bool bLoadConfig, const FName& LoggerName, const FText& LoggerLabel, TSharedPtr<IDatasmithTranslator> InSceneTranslator = nullptr);` — `UE_DEPRECATED(5.0, "Please use constructor using ExternalSource")`
- L216 _public prototype_ `FDatasmithImportContext(const TSharedPtr<UE::DatasmithImporter::FExternalSource>& InExternalSource, bool bLoadConfig, const FName& LoggerName, const FText& LoggerLabel);`
- L219 _public member_ `FMD5Hash FileHash;` — Cached MD5 hash value for faster processing
- L222 _public member_ `FString SceneName;` — Name of the scene being created
- L225 _public member_ `TSharedPtr<IDatasmithTranslator> SceneTranslator;` — Name of the scene being created
- L228 _public member_ `EObjectFlags ObjectFlags;` — Object flags to apply to newly imported objects
- L231 _public member_ `TObjectPtr<UDatasmithImportOptions> Options;` — Settings related to the import of a Datasmith scene
- L234 _public member_ `TArray<TObjectPtr<UDatasmithOptionsBase>> AdditionalImportOptions;` — Per-Translator settings related to the import of a Datasmith scene
- L237 _public member_ `TArray< USceneComponent* > Hierarchy;` — Stack of parent components we're currently importing under
- L240 _public member_ `TObjectPtr<UDatasmithScene> SceneAsset;` — Scene asset
- L243 _public member_ `TSet<FString> ParsedIesFiles;` — List of previously parsed IES files
- L246 _public member_ `TAtomic<bool> bUserCancelled;` — Indicates if the user has canceled the import process
- L248 _public member_ `bool bIsAReimport;`
- L249 _public member_ `bool bImportedViaScript;`
- L252 _public member_ `TSharedPtr< IDatasmithScene > Scene;` — IDatasmithScene object requested to be imported to UE editor
- L255 _public member_ `TSharedPtr< IDatasmithScene > FilteredScene;` — IDatasmithScene object filtered with only what will actually go through the import process
- L258 _public member_ `TMap< TSharedRef< IDatasmithMeshElement >, TObjectPtr<UStaticMesh> > ImportedStaticMeshes;` — Map of imported mesh for each mesh element
- L262 _public member_ `TMap< TSharedRef< IDatasmithClothElement >, TObjectPtr<UObject> > ImportedClothes;` — `UE_DEPRECATED(5.5, "The experimental Cloth importer is no longer supported.")`
- L265 _public member_ `TArray< UObject* > ImportedClothPresets;` — `UE_DEPRECATED(5.5, "The experimental Cloth importer is no longer supported.")`
- L269 _public member_ `TMap< FString, TSharedRef < IDatasmithMeshElement > > ImportedStaticMeshesByName;` — Register IDatasmithMeshElement by their name so they can be searched faster
- L272 _public member_ `TMap< TSharedRef< IDatasmithTextureElement >, UE::Interchange::FAssetImportResultRef > ImportedTextures;` — Map of imported texture for each texture element
- L275 _public member_ `TMap< TSharedRef< IDatasmithBaseMaterialElement >, TObjectPtr<UMaterialInterface> > ImportedMaterials;` — Map of imported material for each material element
- L278 _public member_ `TMap< TSharedRef< IDatasmithBaseMaterialElement >, UMaterialFunction* > ImportedMaterialFunctions;` — Map of imported material function for each material element, they are only imported as a per-required basis
- L281 _public member_ `TMap< FString, TSharedRef < IDatasmithBaseMaterialElement > > ImportedMaterialFunctionsByName;` — Register IDatasmithMeshElement by their name so they can be searched faster
- L284 _public member_ `TMap< uint32, TObjectPtr<UMaterialInterface> > ImportedParentMaterials;` — List of potential parent materials with their hash. Used to create material instances from.
- L287 _public member_ `TMap< TSharedRef< IDatasmithLevelSequenceElement >, TObjectPtr<ULevelSequence> > ImportedLevelSequences;` — Map of imported level sequences for each level sequence element
- L290 _public member_ `TMap< TSharedRef< IDatasmithLevelVariantSetsElement >, TObjectPtr<ULevelVariantSets> > ImportedLevelVariantSets;` — Map of imported level variant sets for each level variant set element
- L293 _public member_ `FFeedbackContext* FeedbackContext;` — Feedback context provided by ImportFactory. Used to display import progress
- L296 _public member_ `FDatasmithActorImportContext ActorsContext;` — Actors specific import context
- L299 _public member_ `FDatasmithAssetsImportContext AssetsContext;` — Assets specific import context
- L302 _public member_ `TSharedPtr< void > ContextExtension;` — Generic extension
- L313 _public prototype_ `bool Init(TSharedRef< IDatasmithScene > InScene, const FString& InImportPath, EObjectFlags InFlags, FFeedbackContext* InWarn, const TSharedPtr<FJsonObject>& ImportSettingsJson, bool bSilent);` — `UE_DEPRECATED(5.0, "The options initialization should not require a scene. Please use other implemetantion of Init() and call InitScene() individually.")` — Initialize members required before loading anything @param Scene		The IDatasmithScene that we will be importing @param InParent	The package in which we are @param bSilent	Doesn't display the options dialog and skips other user input requests
- L324 _public prototype_ `bool Init(const FString& InImportPath, EObjectFlags InFlags, FFeedbackContext* InWarn, const TSharedPtr<FJsonObject>& ImportSettingsJson, bool bSilent);` — Initialize members required before loading anything, must call InitScene() independendly when using this function. @param InImportPath			The path where the scene will be imported @param InFlags				Flags applied to all generated objects during the following import @param InWarn				Feedback context for the following import @param ImportSettingsJson	When bSilent, options as json @param bSilent				Doesn't display the options dialog and skips other user input requests
- L337 _public prototype_ `bool InitOptions(TSharedRef< IDatasmithScene > InScene, const TSharedPtr<FJsonObject>& ImportSettingsJson, bool bSilent);` — `UE_DEPRECATED(5.0, "Please use other InitOptions() implementations, having a valid scene should not be a requirement for initializing the options.")` — First part of the Init process, replaces Init, requires a call to SetupDestination and InitScene after that. Displays the options to the end-user (blocking call), and updates translator accordingly. When silent, Json options are parsed instead. @param InScene              Scene that the context will use for the translation and import @param ImportSettingsJson   When bSilent, options as json @param bSilent              Flag that prevents options to be displayed and edited @return false if the user canceled -> import should not occurs in that case.
- L349 _public prototype_ `bool InitOptions(const TSharedPtr<FJsonObject>& ImportSettingsJson, const TOptional<FString>& InImportPath, bool bSilent);` — First part of the Init process, requires a call to SetupDestination and InitScene after that. Displays the options to the end-user (blocking call), and updates translator accordingly. When silent, Json options are parsed instead. @param ImportSettingsJson   When bSilent, options as json @param InImportPath         Optional import path displayed when bSilent is false. @param bSilent              Flag that prevents options to be displayed and edited @return false if the user canceled -> import should not occurs in that case.
- L361 _public prototype_ `bool SetupDestination(const FString& InImportPath, EObjectFlags InFlags, FFeedbackContext* InWarn, bool bSilent);` — Second part of the Init process, replaces Init, requires a call to InitOptions before that. Setup destination packages @param InImportPath   Destination package's name @param InFlags        Flags applied to all generated objects during the following import @param InWarn         Feedback context for the following import @param bSilent        When false, prompt the user to save dirty packages @return false if the user canceled -> import should not occurs in that case.
- L368 _public prototype_ `void InitScene(const TSharedRef<IDatasmithScene>& InScene);` — Set the scene and initialize related members. Should be called before starting the import process. @param InScene	Scene that will be used for the import, it should already be translated/loaded.
- L373 _public prototype_ `void UpdateImportOption(UDatasmithOptionsBase* Option);` — Replace or add options based on it's UClass.
- L376 _public prototype_ `TSharedRef<FTokenizedMessage> LogError(const FText& InErrorMessage);` — Push messages for display to the end-user
- L377 _public prototype_ `TSharedRef<FTokenizedMessage> LogWarning(const FText& InWarningMessage, bool bPerformance = false);`
- L378 _public prototype_ `TSharedRef<FTokenizedMessage> LogInfo(const FText& InInfoMessage);`
- L380 _public prototype_ `bool ShouldImportActors() const;`
- L383 _public prototype_ `void AddImportedActor(AActor* InActor);` — Add newly created Actor to context's map
- L385 _public prototype_ `TArray<AActor*> GetImportedActors() const;`
- L388 _public prototype_ `void AddSceneComponent(const FString& InName, USceneComponent* InMeshComponent);` — Add newly created SceneComponent to context's map
- L391 _public prototype_ `void DisplayMessages();` — Displays all the messages that were added through AddMessage in the MessageLogModule
- L394 _private prototype_ `void SetupBaseOptionsVisibility();`
- L395 _private prototype_ `void ResetBaseOptionsVisibility();`
- L400 _private member_ `FScopedLogger Logger;` — Handles messages logged during the import process
- L403 _private member_ `TMap<FString, TObjectPtr<AActor>> ImportedActorMap;` — Map of StaticMeshActor objects added to the World at import
- L406 _private member_ `TMap<FString, TObjectPtr<USceneComponent>> ImportedSceneComponentMap;` — Map of SceneComponent objects added to the World at import
- L408 _private member_ `int32 CurrentSceneActorIndex;`
- L425 _private member_ `FInternalReferenceCollector ReferenceCollector;`

#### struct `FDatasmithImportContext::FInternalReferenceCollector`  
`struct FInternalReferenceCollector : FGCObject`  
_L412-424_
- inherits: `FGCObject`
- desc: GC UObject own by DatasmithImportContext
- L414 _public prototype_ `FInternalReferenceCollector(FDatasmithImportContext* InImportContext);`
- L417 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;`
- L418 _public function_ `virtual FString GetReferencerName() const override`
- L423 _private member_ `FDatasmithImportContext* ImportContext;`

#### Free symbols / members of external scopes

- L49 _namespace_ `namespace UE`
- L49 _namespace_ `namespace DatasmithImporter` (scope `UE`)

### `Plugins/Enterprise/DatasmithImporter/Source/DatasmithImporter/Public/DatasmithImportFactory.h` (Public)


#### class `UDatasmithImportFactory`  
`class UDatasmithImportFactory : public USceneImportFactory, public IImportSettingsParser, public FReimportHandler`  
_L35-101_
- reflection: `UCLASS()`
- inherits: `USceneImportFactory,IImportSettingsParser,FReimportHandler`
- L40 _public prototype_ `UDatasmithImportFactory();`
- L43 _public prototype_ `virtual bool FactoryCanImport(const FString& Filename) override;`
- L44 _public prototype_ `virtual FText GetDisplayName() const override;`
- L46 _public prototype_ `virtual bool DoesSupportClass(UClass* InClass) override;` — Used on import path edition to select factories that can produce InClass type of asset.
- L47 _public prototype_ `virtual UClass* ResolveSupportedClass() override;`
- L48 _public prototype_ `virtual void CleanUp() override;`
- L49 _public prototype_ `virtual UObject* FactoryCreateFile(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, const FString& Filename, const TCHAR* InParms, FFeedbackContext* Warn, bool& bOutOperationCanceled) override;`
- L50 _public prototype_ `UObject* CreateFromExternalSource(UClass* InClass, UObject* InParent, FName InName, EObjectFlags InFlags, const TSharedRef<UE::DatasmithImporter::FExternalSource>& InExternalSource, const TCHAR* InParms, FFeedbackContext* InWarn, bool& bOutOperationCanceled);`
- L51 _public function_ `virtual IImportSettingsParser* GetImportSettingsParser() override`
- L55 _public prototype_ `virtual void ParseFromJson(TSharedRef<FJsonObject> InImportSettingsJson) override;`
- L59 _public prototype_ `virtual bool CanReimport(UObject* Obj, TArray<FString>& OutFilenames) override;`
- L60 _public prototype_ `virtual void SetReimportPaths(UObject* Obj, const TArray<FString>& NewReimportPaths) override;`
- L61 _public prototype_ `virtual EReimportResult::Type Reimport(UObject* Obj) override;`
- L62 _public prototype_ `virtual int32 GetPriority() const override;`
- L63 _public function_ `virtual TObjectPtr<UObject>* GetFactoryObject() const override`
- L71 _private prototype_ `bool Import(FDatasmithImportContext& ImportContext);` — Imports the Datasmith Scene
- L74 _private function_ `FName GetLoggerName() const` — Log Listing which holds import messages. Note: Displayed as GetDisplayName() in the UI.
- L77 _private prototype_ `bool IsExtensionSupported(const FString& Filename);` — @return true when the file extension is on the supported extension list.
- L80 _private prototype_ `void ValidateFilesForReimport(TArray<FString>& Filenames);` — filter filenames to keep files currently accessible
- L82 _private prototype_ `EReimportResult::Type ReimportMaterial(UMaterialInterface* Material);`
- L83 _private prototype_ `EReimportResult::Type ReimportScene(UDatasmithScene* SceneAsset);`
- L84 _private prototype_ `EReimportResult::Type ReimportStaticMesh(UStaticMesh* Mesh);`
- L87 _private prototype_ `void OnObjectReimported(UObject* Object, UStaticMesh* StaticMesh);` — Callback used to complete re-import of static mesh if it was edited
- L90 _private member_ `TSharedPtr<FJsonObject> ImportSettingsJson;`
- L92 _private member_ `bool bShowOptions;`
- L98 _private member_ `bool bOperationCanceled;` — Register that the user has canceled the import. Useful when multiple files have been selected.
- L100 _private member_ `mutable TObjectPtr<UObject> GCMark{this};`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace DatasmithImporter` (scope `UE`)
- L20 _namespace_ `namespace DatasmithImportFactoryImpl`
- L29 _prototype_ `bool ImportDatasmithScene(FDatasmithImportContext& InContext, bool& bOutOperationCancelled);` (scope `DatasmithImportFactoryImpl`) — Imports the content described in the DatasmithScene object held by the incoming FDatasmithImportContext This is a helper to allow other import plugin to use the same mechanism to import content into UE @return true on successful import

### `Plugins/Enterprise/DatasmithImporter/Source/DatasmithImporter/Public/DatasmithImporter.h` (Public)


#### struct `FDatasmithImporter`  
`struct FDatasmithImporter`  
_L34-211_
- L39 _public prototype_ `static void ImportStaticMeshes( FDatasmithImportContext& ImportContext );` — Imports the meshes associated with the mesh elements
- L42 _public prototype_ `static void ImportClothes( FDatasmithImportContext& ImportContext );` — `UE_DEPRECATED(5.5, "The experimental Cloth importer is no longer supported.")`
- L47 _public prototype_ `static UStaticMesh* ImportStaticMesh( FDatasmithImportContext& ImportContext, TSharedRef< IDatasmithMeshElement > MeshElement, UStaticMesh* ExistingStaticMesh, FDatasmithMeshElementPayload* MeshPayload = nullptr);` — @return The imported Static Mesh
- L60 _public prototype_ `static UStaticMesh* FinalizeStaticMesh( UStaticMesh* SourceStaticMesh, const TCHAR* StaticMeshesFolderPath, UStaticMesh* ExistingStaticMesh, TMap< UObject*, UObject* >* ReferencesToRemap = nullptr, bool bBuild = true );` — Copy a static mesh from its transient package into its final public package and builds it. @param SourceStaticMesh			The static mesh to finalize. @param StaticMeshesFolderPath	The path where to put the final static mesh, if we don't have an ExistingStaticMesh @param ExistingStaticMesh		An optional existing static mesh on which we will finalize over. @param ReferencesToRemap			A map of migrated objects. If SourceStaticMesh refers to any key objects, those references will be replaced by the corresponding map value. @param bBuild					Specify if the static mesh building should be performed. @return The resulting static mesh
- L63 _public prototype_ `static UObject* FinalizeCloth( UObject* SourceCloth, const TCHAR* FolderPath, UObject* ExistingCloth, TMap<UObject*, UObject*>* ReferencesToRemap = nullptr);` — `UE_DEPRECATED(5.5, "The experimental Cloth importer is no longer supported.")`
- L68 _public prototype_ `static void CreateStaticMeshAssetImportData( FDatasmithImportContext& InContext, TSharedRef< IDatasmithMeshElement > MeshElement, UStaticMesh* ImportedStaticMesh, TArray<UDatasmithAdditionalData*>& AdditionalData );` — Creates the AssetImportData associated with a UStaticMesh. Used when reimporting.
- L73 _public prototype_ `static void ImportTextures( FDatasmithImportContext& ImportContext );` — Imports the textures
- L78 _public prototype_ `static UTexture* ImportTexture( FDatasmithImportContext& ImportContext, class FDatasmithTextureImporter& DatasmithTextureImporter, TSharedRef< IDatasmithTextureElement > TextureElement, UTexture* ExistingTexture, const TArray<uint8>& TextureData, const FString& Extension );` — @return The imported texture
- L90 _public prototype_ `static UTexture* FinalizeTexture( UTexture* SourceTexture, const TCHAR* TexturesFolderPath, UTexture* ExistingTexture, TMap< UObject*, UObject* >* ReferencesToRemap = nullptr );` — Copy a texture from its transient package into its final public package and builds it. @param SourceTexture			The texture to finalize. @param TexturesFolderPath	The path where to put the final texture, if we don't have an ExistingTexture @param ExistingTexture		An optional existing texture on which we will finalize over. @param ReferencesToRemap		A map of migrated objects. If SourceTexture refers to any key objects, those references will be replaced by the corresponding map value. @return The resulting texture
- L95 _public prototype_ `static void ImportMaterials( FDatasmithImportContext& ImportContext );` — Imports the materials
- L100 _public prototype_ `static UMaterialFunction* ImportMaterialFunction( FDatasmithImportContext& ImportContext, TSharedRef< IDatasmithBaseMaterialElement > MaterialElement );` — @return The imported MaterialFunction
- L112 _public prototype_ `static UMaterialFunction* FinalizeMaterialFunction(UObject* SourceMaterialFunction, const TCHAR* MaterialFunctionsFolderPath, UMaterialFunction* ExistingMaterialFunction, TMap< UObject*, UObject* >* ReferencesToRemap);` — Copy a material function from its transient package into its final public package. @param SourceMaterialFunction		The material function to finalize. @param MaterialFunctionFolderPath	The path where to put the final material function, if we don't have an ExistingMaterialFunction. @param ExistingMaterialFunction		An optional existing material function on which we will finalize over. @param ReferencesToRemap				A map of migrated objects. If SourceMaterialFunction refers to any key objects those references will be replaced by the corresponding map value. @return The resulting material function.
- L117 _public prototype_ `static UMaterialInterface* ImportMaterial( FDatasmithImportContext& ImportContext, TSharedRef< IDatasmithBaseMaterialElement > MaterialElement, UMaterialInterface* ExistingMaterial );` — @return The imported material
- L133 _public prototype_ `static UObject* FinalizeMaterial( UObject* SourceMaterial, const TCHAR* MaterialFolderPath, const TCHAR* TransientFolderPath, const TCHAR* RootFolderPath, UMaterialInterface* ExistingMaterial, TMap< UObject*, UObject* >* ReferencesToRemap = nullptr, FMaterialUpdateContext* MaterialUpdateContext = nullptr);` — Copy a material from its transient package into its final public package and builds it. Also finalizes the parent material for instances when it's under the same path as the SourceMaterial. @param SourceMaterial		The material to finalize. @param MaterialFolderPath	The path where to put the final material, if we don't have an ExistingMaterial @param MaterialFolderPath	The transient path of the imported scene, used to finalize parent materials. @param MaterialFolderPath	The root folder where we want to import the scene, used to finalize parent materials. @param ExistingMaterial		An optional existing material on which we will finalize over. @param ReferencesToRemap		A map of migrated objects. If SourceMaterial refers to any key objects, those references will be replaced by the corresponding map value. @param MaterialUpdateContext		An optional material update context to batch updates and improve performance. @return The resulting material
- L138 _public prototype_ `static void ImportActors( FDatasmithImportContext& ImportContext );` — Imports the actors
- L143 _public prototype_ `static AActor* ImportActor( FDatasmithImportContext& ImportContext, const TSharedRef< IDatasmithActorElement >& ActorElement );` — Imports the given actor element with its hierarchy
- L152 _public prototype_ `static void ImportActorAsComponent( FDatasmithImportContext& ImportContext, const TSharedRef< IDatasmithActorElement >& ActorElement, AActor* InRootActor, FDatasmithActorUniqueLabelProvider& UniqueNameProvider );` — Adds a new component to the root actor. The component class is determined by the ActorElement type. @param ImportContext		The context in which we're importing @param ActorElement		The Datasmith element containing the data for the component @param RootActor			The actor in which to add the component
- L157 _public prototype_ `static void FinalizeActors( FDatasmithImportContext& ImportContext, TMap< UObject*, UObject* >* AssetReferencesToRemap );` — Finalizes all the actors
- L170 _public prototype_ `static AActor* FinalizeActor( FDatasmithImportContext& ImportContext, AActor& SourceActor, AActor* ExistingActor, TMap< UObject*, UObject* >& ReferencesToRemap, TArray<uint8>& ReusableBuffer );` — Migrates an actor from the import world to the final world. Generating templates based on their current values. @param ImportContext			The context used by the import process. @param SourceActor			The actor to finalize. @param ExistingActor			An optional existing actor on which we will finalize over. @param ReferencesToRemap		A map of migrated objects. If SourceActor refers to any key objects, those references will be replaced by the corresponding map value. @param ReusableBuffer		An array that will be used for the migration of the data from the temp actor to the final actor. The array doesn't have to be empty the function will clean it before using it and it will try to keep it's existing allocation. @return The resulting actor
- L175 _public prototype_ `static void ImportLevelSequences( FDatasmithImportContext& ImportContext );` — Imports the level sequences
- L180 _public prototype_ `static ULevelSequence* FinalizeLevelSequence( ULevelSequence* SourceLevelSequence, const TCHAR* AnimationsFolderPath, ULevelSequence* ExistingLevelSequence );` — Copy a level sequence from its transient package into its final public package and builds it.
- L185 _public prototype_ `static void ImportLevelVariantSets( FDatasmithImportContext& ImportContext );` — Imports the level variant sets
- L190 _public prototype_ `static ULevelVariantSets* FinalizeLevelVariantSets( ULevelVariantSets* SourceLevelVariantSets, const TCHAR* VariantsFolderPath, ULevelVariantSets* ExistingLevelVariantSets );` — Copy a level sequence from its transient package into its final public package and builds it.
- L195 _public prototype_ `static void ImportMetaDataForObject( FDatasmithImportContext& ImportContext, const TSharedRef< IDatasmithElement >& DatasmithElement, UObject* Object );` — Imports the meta data associated to a DatasmithElement and sets it on the Object.
- L200 _public prototype_ `static void FilterElementsToImport( FDatasmithImportContext& ImportContext );` — Filter elements in the scene that needs to be imported
- L205 _public prototype_ `static void FinalizeImport( FDatasmithImportContext& ImportContext, const TSet<UObject*>& ValidAssets );` — Publicize the import and fix the references on the assets and actors. Also, update the final datasmith scenes.
- L210 _private prototype_ `FDatasmithImporter() = delete;` — This class is designed not to have state. Instance are meaningless

### `Plugins/Enterprise/DatasmithImporter/Source/DatasmithImporter/Public/DatasmithImporterEditorSettings.h` (Public)


#### class `UDatasmithImporterEditorSettings`  
`class UDatasmithImporterEditorSettings : public UObject`  
_L8-18_
- reflection: `UCLASS(config=EditorSettings, MinimalAPI)`
- inherits: `UObject`
- L13 _public prototype_ `UDatasmithImporterEditorSettings();`
- L16 _public member_ `bool bOfflineImporter;` — `UPROPERTY(config)`

### `Plugins/Enterprise/DatasmithImporter/Source/DatasmithImporter/Public/DatasmithImporterHelper.h` (Public)


#### class `FDatasmithImporterHelper`  
`class FDatasmithImporterHelper`  
_L12-58_
- L22 _public function_ `template <class TFactory> static void Import()` — Start the import process for the given factory type. The importer helper will pop up a file dialog to pick the file to import. Next, it will prompt for the folder where the imported assets will be saved. The Datasmith import options then appears and finally the factory import starts.
- L28 _public function_ `template <class TFactory> static void Import(const TSharedRef<UE::DatasmithImporter::FExternalSource>& ExternalSource)`
- L34 _public function_ `template <class TFactory> static FString GetFilter()`
- L41 _public function_ `template <class TFactory> static TArray<FString> GetFormats()`
- L50 _private function_ `template <class T> static T* GetTypedDefaultObject()`
- L55 _private prototype_ `static void ImportInternal(UFactory* Factory);`
- L56 _private prototype_ `static void ImportInternal(UFactory* Factory, const TSharedRef<UE::DatasmithImporter::FExternalSource>& ExternalSource);`
- L57 _private prototype_ `static FString GetFilterStringInternal(UFactory* Factory);`

#### Free symbols / members of external scopes

- L5 _namespace_ `namespace UE`
- L5 _namespace_ `namespace DatasmithImporter` (scope `UE`)

### `Plugins/Enterprise/DatasmithImporter/Source/DatasmithImporter/Public/DatasmithImporterModule.h` (Public)


#### class `IDatasmithImporterModule`  
`class IDatasmithImporterModule : public IModuleInterface`  
_L17-48_
- inherits: `IModuleInterface`
- desc: The public interface of the DatasmithImporter module
- L26 _public function_ `static inline IDatasmithImporterModule& Get()` — Singleton-like access to IDatasmithImporter @return Returns DatasmithImporter singleton instance, loading the module on demand if needed
- L36 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use
- L44 _public prototype_ `virtual void ResetOverrides( UObject* Object ) = 0;` — Restores the Datasmith imported values on an object
- L46 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnGenerateDatasmithImportMenu, struct FToolMenuSection&);`
- L47 _public prototype_ `virtual FOnGenerateDatasmithImportMenu& OnGenerateDatasmithImportMenu() = 0;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define DATASMITHIMPORTER_MODULE_NAME TEXT("DatasmithImporter")`
- L46 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnGenerateDatasmithImportMenu, struct FToolMenuSection&);`

### `Plugins/Enterprise/DatasmithImporter/Source/DatasmithImporter/Public/DatasmithLandscapeImporter.h` (Public)


#### class `FDatasmithLandscapeImporter`  
`class FDatasmithLandscapeImporter`  
_L13-17_
- L16 _public prototype_ `static AActor* ImportLandscapeActor( const TSharedRef< IDatasmithLandscapeElement >& LandscapeActorElement, FDatasmithImportContext& ImportContext, EDatasmithImportActorPolicy ImportActorPolicy );`

### `Plugins/Enterprise/DatasmithImporter/Source/DatasmithImporter/Public/DatasmithLevelSequenceImporter.h` (Public)


#### class `FDatasmithLevelSequenceImporter`  
`class FDatasmithLevelSequenceImporter`  
_L10-18_
- L13 _public prototype_ `static ULevelSequence* ImportLevelSequence(const TSharedRef<IDatasmithLevelSequenceElement>& LevelSequenceElement, FDatasmithImportContext& InImportContext, ULevelSequence* ExistingLevelSequence);`
- L17 _public prototype_ `static bool CanImportLevelSequence(const TSharedRef<IDatasmithLevelSequenceElement>& LevelSequenceElement, const FDatasmithImportContext& InImportContext);` — Checks if we parsed and created all necessary ULevelSequence assets that need to be used as subsequences by the IDatasmithSubsequenceAnimationElements contained in LevelSequenceElement

### `Plugins/Enterprise/DatasmithImporter/Source/DatasmithImporter/Public/DatasmithLevelVariantSetsImporter.h` (Public)


#### class `FDatasmithLevelVariantSetsImporter`  
`class FDatasmithLevelVariantSetsImporter`  
_L10-14_
- L13 _public prototype_ `static ULevelVariantSets* ImportLevelVariantSets(const TSharedRef<IDatasmithLevelVariantSetsElement>& LevelVariantSets, FDatasmithImportContext& InImportContext, ULevelVariantSets* ExistingLevelVariantSets);`

### `Plugins/Enterprise/DatasmithImporter/Source/DatasmithImporter/Public/DatasmithLightImporter.h` (Public)


#### class `FDatasmithLightImporter`  
`class FDatasmithLightImporter`  
_L38-63_
- L41 _public prototype_ `static AActor* ImportLightActor( const TSharedRef< IDatasmithLightActorElement >& LightElement, FDatasmithImportContext& ImportContext );`
- L42 _public prototype_ `static USceneComponent* ImportLightComponent( const TSharedRef< IDatasmithLightActorElement >& LightElement, FDatasmithImportContext& ImportContext, UObject* Outer, FDatasmithActorUniqueLabelProvider& UniqueNameProvider );`
- L44 _public prototype_ `static AActor* CreateHDRISkyLight(const TSharedPtr< IDatasmithShaderElement >& ShaderElement, FDatasmithImportContext& ImportContext);`
- L46 _public prototype_ `static AActor* CreatePhysicalSky(FDatasmithImportContext& ImportContext);`
- L49 _private prototype_ `static void SetTextureLightProfile( const TSharedRef< IDatasmithLightActorElement >& LightElement, class UDatasmithLightComponentTemplate* LightComponentTemplate, FDatasmithAssetsImportContext& AssetsContext );`
- L51 _private prototype_ `static void SetupLightComponent( ULightComponent* LightComponent, const TSharedPtr< IDatasmithLightActorElement >& LightElement, FDatasmithAssetsImportContext& AssetsContext );`
- L52 _private prototype_ `static void SetupPointLightComponent( UPointLightComponent* PointLightComponent, const TSharedRef< IDatasmithPointLightElement >& PointLightElement, FDatasmithAssetsImportContext& AssetsContext );`
- L53 _private prototype_ `static void SetupSpotLightComponent( USpotLightComponent* SpotLightComponent, const TSharedRef< IDatasmithSpotLightElement >& SpotLightElement, FDatasmithAssetsImportContext& AssetsContext );`
- L55 _private prototype_ `static AActor* ImportAreaLightActor( const TSharedRef< IDatasmithAreaLightElement >& AreaLightElement, FDatasmithImportContext& ImportContext );`
- L56 _private prototype_ `static USceneComponent* ImportAreaLightComponent( const TSharedRef< IDatasmithAreaLightElement >& AreaLightElement, FDatasmithImportContext& ImportContext, UObject* Outer, FDatasmithActorUniqueLabelProvider& UniqueNameProvider );`
- L58 _private prototype_ `static AActor* CreateAreaLightActor( const TSharedRef< IDatasmithAreaLightElement >& AreaLightElement, FDatasmithImportContext& ImportContext );`
- L59 _private prototype_ `static void SetupAreaLightActor( const TSharedRef< IDatasmithAreaLightElement >& AreaLightElement, FDatasmithImportContext& ImportContext, ADatasmithAreaLightActor* LightShapeActor );`
- L60 _private prototype_ `static ULightmassPortalComponent* ImportLightmassPortalComponent( const TSharedRef< IDatasmithLightmassPortalElement >& LightElement, FDatasmithImportContext& ImportContext, UObject* Outer, FDatasmithActorUniqueLabelProvider& UniqueNameProvider );`
- L61 _private prototype_ `static AActor* CreateSkyLight(const TSharedPtr< IDatasmithShaderElement >& ShaderElement, FDatasmithImportContext& ImportContext, bool bUseHDRMat);`

### `Plugins/Enterprise/DatasmithImporter/Source/DatasmithImporter/Public/DatasmithMaterialExpressions.h` (Public)


#### enum `EDatasmithTextureSlot`  
`enum class EDatasmithTextureSlot`  
_L39-59_
- L41 _public enumerator_ `DIFFUSE`
- L42 _public enumerator_ `METALLIC`
- L43 _public enumerator_ `SPECULAR`
- L44 _public enumerator_ `ROUGHNESS`
- L45 _public enumerator_ `EMISSIVECOLOR`
- L46 _public enumerator_ `OPACITY`
- L47 _public enumerator_ `OPACITYMASK`
- L48 _public enumerator_ `NORMAL`
- L49 _public enumerator_ `WORLDPOSITIONOFFSET`
- L50 _public enumerator_ `SUBSURFACECOLOR`
- L51 _public enumerator_ `COATSPECULAR`
- L52 _public enumerator_ `COATROUGHNESS`
- L53 _public enumerator_ `AMBIANTOCCLUSION`
- L54 _public enumerator_ `REFRACTION`
- L55 _public enumerator_ `PIXELDEPTHOFFSET`
- L56 _public enumerator_ `SHADINGMODEL`
- L57 _public enumerator_ `MATERIALATTRIBUTES`
- L58 _public enumerator_ `NOSLOT`

#### class `FDatasmithMaterialExpressions`  
`class FDatasmithMaterialExpressions`  
_L61-171_
- L64 _public prototype_ `static UMaterialInterface* CreateDatasmithMaterial(UPackage* Package, const TSharedPtr< IDatasmithMaterialElement >& MaterialElement, FDatasmithAssetsImportContext& AssetsContext, UMaterial* ExistingMaterial, EObjectFlags ObjectFlags);`
- L65 _public prototype_ `static UMaterialFunction* CreateUEPbrMaterialFunction(UPackage* Package, const TSharedPtr< IDatasmithUEPbrMaterialElement >& MaterialElement, FDatasmithAssetsImportContext& AssetsContext, UMaterial* ExistingMaterial, EObjectFlags ObjectFlags);`
- L66 _public prototype_ `static UMaterialInterface* CreateUEPbrMaterial(UPackage* Package, const TSharedPtr< IDatasmithUEPbrMaterialElement >& MaterialElement, FDatasmithAssetsImportContext& AssetsContext, UMaterial* ExistingMaterial, EObjectFlags ObjectFlags);`
- L67 _public prototype_ `static UMaterialInterface* CreateUEPbrMaterialInstance(UPackage* Package, const TSharedPtr< IDatasmithUEPbrMaterialElement >& MaterialElement, FDatasmithAssetsImportContext& AssetsContext, UMaterialInterface* ParentMaterial, EObjectFlags ObjectFlags);`
- L68 _public prototype_ `static UMaterialInterface* CreateDatasmithEnvironmentMaterial(UPackage* Package, const TSharedPtr< IDatasmithShaderElement >& ShaderElement, FDatasmithAssetsImportContext& AssetsContext, UMaterial* ExistingMaterial);`
- L71 _public prototype_ `static UMaterialExpression* AddCompExpression(const TSharedPtr<IDatasmithCompositeTexture>& Comp, UObject* UnrealMaterial, EDatasmithTextureSlot Slot, const FDatasmithAssetsImportContext& AssetsContext);`
- L73 _public prototype_ `static void ForEachParamsNameInMaterial(const TSharedPtr<IDatasmithUEPbrMaterialElement>& MaterialElement, const TFunctionRef<void (FName Expression, const EDatasmithMaterialExpressionType& ExpressionType, int32 Index)>& CallbackForEach);`
- L75 _private prototype_ `static FLinearColor TemperatureToColor(float Kelvin);`
- L77 _private prototype_ `static UMaterialExpressionMakeMaterialAttributes* FindOrAddAttributesFromMatFunc(UMaterialFunction* Func);`
- L78 _private prototype_ `static UMaterialExpressionFunctionOutput* FindOrAddOutputFromMatFunc(UMaterialFunction* Func);`
- L80 _private prototype_ `static void GetSamplersRecursive(UMaterialExpression* Expression, TArray<UMaterialExpressionTextureSample*>& TextureSamplers);`
- L83 _private function_ `template<typename ExpressionsArrayType> static void GetSamplers(const ExpressionsArrayType& Expressions, TArray<FExpressionInput*> ExpressionInputs, TArray<UMaterialExpressionTextureSample*>& TextureSamplers)`
- L91 _private prototype_ `static void GetTextureSamplersMaterial(UMaterialInterface* MaterialInterface, TArray<UMaterialExpressionTextureSample*>& TextureSamplers);`
- L92 _private prototype_ `static void GetTextureSamplersFunc(UMaterialFunction* MaterialFunc, TArray<UMaterialExpressionTextureSample*>& TextureSamplers);`
- L93 _private prototype_ `static void GetTextureSamplers(UObject* UnrealMatOrFunc, TArray<UMaterialExpressionTextureSample*>& TextureSamplers);`
- L95 _private prototype_ `static bool MatOrFuncDelExpression(UObject* Object, UMaterialExpression* ToBeConnected);`
- L97 _private prototype_ `static UMaterialExpression* Constant(UObject* UnrealMaterial, double Value);`
- L98 _private prototype_ `static UMaterialExpression* Multiply(UObject* UnrealMaterial, UMaterialExpression* ToBeConnectedA, double ValueA, UMaterialExpression* ToBeConnectedB, double ValueB);`
- L99 _private prototype_ `static UMaterialExpression* Divide(UObject* UnrealMaterial, UMaterialExpression* ToBeConnectedA, double ValueA, UMaterialExpression* ToBeConnectedB, double ValueB);`
- L100 _private prototype_ `static UMaterialExpression* Add(UObject* UnrealMaterial, UMaterialExpression* ToBeConnectedA, double ValueA, UMaterialExpression* ToBeConnectedB, double ValueB);`
- L101 _private prototype_ `static UMaterialExpression* Subtract(UObject* UnrealMaterial, UMaterialExpression* ToBeConnectedA, double ValueA, UMaterialExpression* ToBeConnectedB, double ValueB);`
- L102 _private prototype_ `static UMaterialExpression* Lerp(UObject* UnrealMaterial, UMaterialExpression* ToBeConnectedA, double ValueA, bool bAllowCleanUpA, UMaterialExpression* ToBeConnectedB, double ValueB, bool bAllowCleanUpB, UMaterialExpression* Alpha, double ValueAlpha);`
- L105 _private prototype_ `static UMaterialExpression* HsvExpression(UObject* UnrealMaterial, UMaterialExpression* ToBeConnectedA, const TArray<double>& Hsv);`
- L106 _private prototype_ `static UMaterialExpression* HsvExpression(UObject* UnrealMaterial, UMaterialExpression* ToBeConnectedA, UMaterialExpression* ToBeConnectedB);`
- L107 _private prototype_ `static UMaterialExpression* HsvExpressionCustom(UObject* UnrealMaterial, UMaterialExpression* ToBeConnectedA, UMaterialExpression* ToBeConnectedB);`
- L109 _private prototype_ `static UMaterialExpression* Fresnel(UObject* UnrealMaterial, UMaterialExpression* ToBeConnectedA, double ValueA, UMaterialExpression* ToBeConnectedB, double ValueB);`
- L110 _private prototype_ `static UMaterialExpression* Power(UObject* UnrealMaterial, UMaterialExpression* ToBeConnectedA, UMaterialExpression* ToBeConnectedB, double ValueB);`
- L111 _private prototype_ `static UMaterialExpression* Desaturate(UObject* UnrealMaterial, UMaterialExpression* ToBeConnected);`
- L112 _private prototype_ `static UMaterialExpression* OneMinus(UObject* UnrealMaterial, UMaterialExpression* ToBeConnected);`
- L114 _private prototype_ `static UMaterialExpression* CalcIORComplex(double IORn, double IORk, UObject* UnrealMaterial, UMaterialExpression* ToBeConnected90, bool bAllowCleanUpExpr90 = true, UMaterialExpression* ToBeConnected0 = nullptr, bool bAllowCleanUpExpr0 = true);`
- L115 _private prototype_ `static UMaterialExpression* CalcIORSimple(double IORn, double IORk, UObject* UnrealMaterial, UMaterialExpression* ToBeConnected90, bool bAllowCleanUpExpr90 = true, UMaterialExpression* ToBeConnected0 = nullptr, bool bAllowCleanUpExpr0 = true);`
- L116 _private prototype_ `static UMaterialExpression* CalcIOR(double IORn, double IORk, UObject* UnrealMaterial, UMaterialExpression* ToBeConnected90, bool bAllowCleanUpExpr90 = true, UMaterialExpression* ToBeConnected0 = nullptr, bool bAllowCleanUpExpr0 = true);`
- L117 _private prototype_ `static UMaterialExpression* RefractionIOR(double IOR, UObject* UnrealMaterial);`
- L119 _private prototype_ `static UMaterialExpression* AddCroppedUVMappingExpression(UObject* UnrealMaterial, const FDatasmithTextureSampler& UV, UMaterialExpressionTextureCoordinate* ToBeConnected);`
- L121 _private prototype_ `static void CreateUEPbrMaterialGraph(const TSharedPtr< IDatasmithUEPbrMaterialElement >& MaterialElement, FDatasmithAssetsImportContext& AssetsContext, UObject* UnrealMaterialOrFunction);`
- L122 _private prototype_ `static EBlendMode GetUEPbrImportBlendMode(const TSharedPtr< IDatasmithUEPbrMaterialElement >& MaterialElement, const FDatasmithAssetsImportContext& AssetsContext);`
- L123 _private prototype_ `static EMaterialProperty DatasmithTextureSlotToMaterialProperty(EDatasmithTextureSlot InSlot);`
- L124 _private prototype_ `static FExpressionInput* GetMaterialOrFunctionSlot(UObject* UnrealMatOrFunc, EDatasmithTextureSlot InSlot);`
- L125 _private prototype_ `static void ConnectToSlot(UMaterialExpression* ToBeConnected, UObject* UnrealMatOrFunc, EDatasmithTextureSlot Slot, int32 InputChannel = 0);`
- L127 _private prototype_ `static UMaterialExpressionTextureObject* AddTextureObjectExpression(UTexture* Texture, UObject* UnrealMaterial);`
- L128 _private prototype_ `static UMaterialExpression* AddTextureExpression(UTexture* Texture, FDatasmithTextureSampler uv, double IOR, double IORk, UObject* UnrealMaterial, EDatasmithTextureSlot Slot, UMaterialExpressionTextureSample** OutTextureSample = nullptr);`
- L129 _private prototype_ `static UMaterialExpression* AddUVMirrorExpression(UObject* UnrealMaterial, UMaterialExpression* Expression, int XTile, int YTile);`
- L130 _private prototype_ `static UMaterialExpression* AddConstExpression(double Val, double IOR, double IORk, UObject* UnrealMaterial, EDatasmithTextureSlot Slot);`
- L131 _private prototype_ `static UMaterialExpression* AddRGBExpression(FLinearColor Col, double IOR, double IORk, UObject* UnrealMaterial, EDatasmithTextureSlot Slot, bool bForceEvenIfBlack = false);`
- L132 _private prototype_ `static UMaterialExpression* AddRGBAExpression(FLinearColor Col, double IOR, double IORk, UObject* UnrealMaterial, EDatasmithTextureSlot Slot, bool bForceEvenIfBlack = false);`
- L133 _private prototype_ `static UMaterialExpression* AddRegularExpression(const TSharedPtr<IDatasmithCompositeTexture>& Comp, UObject* UnrealMaterial, EDatasmithTextureSlot Slot, const FDatasmithAssetsImportContext& AssetsContext);`
- L134 _private prototype_ `static UMaterialExpression* AddHueTintExpression(UObject* UnrealMaterial, UMaterialExpression* Expression, float Amount, FLinearColor Color);`
- L135 _private prototype_ `static UMaterialExpression* AddCCorrectExpression(const TSharedPtr<IDatasmithCompositeTexture>& Comp, bool bUseGamma, UObject* UnrealMaterial, EDatasmithTextureSlot Slot, const FDatasmithAssetsImportContext& AssetsContext);`
- L136 _private prototype_ `static UMaterialExpression* AddMultiplyExpression(const TSharedPtr<IDatasmithCompositeTexture>& Comp, UObject* UnrealMaterial, EDatasmithTextureSlot Slot, const FDatasmithAssetsImportContext& AssetsContext);`
- L137 _private prototype_ `static UMaterialExpression* AddMixExpression(const TSharedPtr<IDatasmithCompositeTexture>& Comp, UObject* UnrealMaterial, EDatasmithTextureSlot Slot, const FDatasmithAssetsImportContext& AssetsContext);`
- L138 _private prototype_ `static UMaterialExpression* AddCompositeExpression(const TSharedPtr<IDatasmithCompositeTexture>& Comp, UObject* UnrealMaterial, EDatasmithTextureSlot Slot, const FDatasmithAssetsImportContext& AssetsContext);`
- L139 _private prototype_ `static UMaterialExpression* AddIorExpression(const TSharedPtr<IDatasmithCompositeTexture>& Comp, UObject* UnrealMaterial, EDatasmithTextureSlot Slot, const FDatasmithAssetsImportContext& AssetsContext);`
- L140 _private prototype_ `static UMaterialExpression* AddFresnelExpression(const TSharedPtr<IDatasmithCompositeTexture>& Comp, UObject* UnrealMaterial, EDatasmithTextureSlot Slot, const FDatasmithAssetsImportContext& AssetsContext);`
- L143 _private prototype_ `static void AddGlassNode(UMaterialExpression* RefleExpression, UMaterialExpression* OpacityExpression, double IOR, double IORRefra, UObject* UnrealMaterial);` — glass node includes custom reflection
- L145 _private prototype_ `static void CreateDatasmithMaterialHelper(UPackage* Package, const TSharedPtr< IDatasmithShaderElement >& ShaderElement, const FDatasmithAssetsImportContext& AssetsContext, UObject* UnrealMaterial);`
- L146 _private prototype_ `static UMaterialInterface* CreateDatasmithMaterial(UPackage* Package, const TSharedPtr< IDatasmithShaderElement >& ShaderElement, FDatasmithAssetsImportContext& AssetsContext, UMaterial* ExistingMaterial, EObjectFlags ObjectFlags);`
- L147 _private prototype_ `static UMaterialFunction* CreateDatasmithMaterialFunc(UPackage* Package, const TSharedPtr< IDatasmithMaterialElement >& MaterialElement, const TSharedPtr< IDatasmithShaderElement >& ShaderElement, const FDatasmithAssetsImportContext& AssetsContext, UMaterialFunction* FindMaterialFunc, EObjectFlags ObjectFlags);`
- L150 _private prototype_ `static void GatherConnectedExpressions(UMaterialExpression* Expression, TArray<UMaterialExpression*>& ThisRowExpressions, int32 ChildNumber);`
- L151 _private prototype_ `static UMaterialExpression* GetCorrectExpressionFromComp(const TSharedPtr<IDatasmithCompositeTexture>& Comp, UObject* UnrealMaterial, const FDatasmithAssetsImportContext& AssetsContext, int32 Index, bool bMask, bool bRgbNoAlpha);`
- L152 _private prototype_ `static void CreateDatasmithMaterialCoat(const FDatasmithAssetsImportContext& AssetsContext, const TSharedPtr< IDatasmithShaderElement >& ShaderElement, UObject* UnrealMaterial);`
- L153 _private prototype_ `static void ModulateNormalAmount(UObject* UnrealMatOrFunc, double Amount);`
- L154 _private prototype_ `static void CreateParallaxOffset(UObject* UnrealMatOrFunc, UMaterialExpressionTextureObject* TextureObject, FDatasmithTextureSampler UV, float Amount);`
- L155 _private prototype_ `static UMaterialExpressionMaterialFunctionCall* BlendFunctions(UMaterial* UnrealMaterial, const FDatasmithAssetsImportContext& AssetsContext, const TSharedPtr< IDatasmithShaderElement >& ShaderTop, UMaterialExpressionMaterialFunctionCall* CallTop, UMaterialExpressionMaterialFunctionCall* CallBase, UMaterialFunction* BlendFunc);`
- L158 _private prototype_ `static UMaterialExpression* CreateExpression( class IDatasmithMaterialExpression* MaterialExpression, const FDatasmithAssetsImportContext& AssetsContext, UObject* UnrealMaterialOrFunction );`
- L159 _private prototype_ `static UMaterialExpression* CreateTextureExpression( class IDatasmithMaterialExpressionTexture& DatasmithTextureExpression, const FDatasmithAssetsImportContext& AssetsContext, UObject* UnrealMaterialOrFunction);`
- L160 _private prototype_ `static UMaterialExpression* CreateTextureCoordinateExpression( class IDatasmithMaterialExpressionTextureCoordinate& DatasmithTextureCoordinateExpression, const FDatasmithAssetsImportContext& AssetsContext, UObject* UnrealMaterialOrFunction);`
- L161 _private prototype_ `static UMaterialExpression* CreateFlattenNormalExpression( class IDatasmithMaterialExpressionFlattenNormal& DatasmithFlattenNormal, const FDatasmithAssetsImportContext& AssetsContext, UObject* UnrealMaterialOrFunction);`
- L162 _private prototype_ `static UMaterialExpression* CreateBoolExpression( class IDatasmithMaterialExpressionBool& DatasmithBool, const FDatasmithAssetsImportContext& AssetsContext, UObject* UnrealMaterialOrFunction);`
- L163 _private prototype_ `static UMaterialExpression* CreateColorExpression( class IDatasmithMaterialExpressionColor& DatasmithColor, const FDatasmithAssetsImportContext& AssetsContext, UObject* UnrealMaterialOrFunction);`
- L164 _private prototype_ `static UMaterialExpression* CreateScalarExpression( class IDatasmithMaterialExpressionScalar& DatasmithScalar, const FDatasmithAssetsImportContext& AssetsContext, UObject* UnrealMaterialOrFunction);`
- L165 _private prototype_ `static UMaterialExpression* CreateGenericExpression( class IDatasmithMaterialExpressionGeneric& DatasmithGeneric, const FDatasmithAssetsImportContext& AssetsContext, UObject* UnrealMaterialOrFunction);`
- L166 _private prototype_ `static UMaterialExpression* CreateFunctionCallExpression( class IDatasmithMaterialExpressionFunctionCall& DatasmithFunctionCall, const FDatasmithAssetsImportContext& AssetsContext, UObject* UnrealMaterialOrFunction);`
- L167 _private prototype_ `static UMaterialExpression* CreateCustomExpression( class IDatasmithMaterialExpressionCustom& DatasmithCustom, const FDatasmithAssetsImportContext& AssetsContext, UObject* UnrealMaterialOrFunction);`
- L169 _private prototype_ `static void ConnectExpression( const TSharedRef< IDatasmithUEPbrMaterialElement >& MaterialElement, TArray< TStrongObjectPtr< UMaterialExpression > >& MaterialExpressions, class IDatasmithMaterialExpression* MaterialExpression, FExpressionInput* MaterialInput, int32 OutputIndex);`
- L170 _private prototype_ `static void ConnectAnyExpression( const TSharedRef< IDatasmithUEPbrMaterialElement >& MaterialElement, TArray< TStrongObjectPtr< UMaterialExpression > >& MaterialExpressions, class IDatasmithMaterialExpression& DatasmithExpression, FExpressionInput* ExpressionInput, int32 OutputIndex);`

### `Plugins/Enterprise/DatasmithImporter/Source/DatasmithImporter/Public/DatasmithMaterialImporter.h` (Public)


#### enum `EMaterialRequirements::Type`  
`enum Type`  
_L19-24_
- L21 _public enumerator_ `RequiresNothing = 0x00`
- L22 _public enumerator_ `RequiresNormals = 0x01`
- L23 _public enumerator_ `RequiresTangents = 0x02`

#### class `FDatasmithMaterialImporter`  
`class FDatasmithMaterialImporter`  
_L27-39_
- L30 _public prototype_ `static UMaterialFunction* CreateMaterialFunction( FDatasmithImportContext& ImportContext, const TSharedRef< IDatasmithBaseMaterialElement >& MaterialElement );`
- L32 _public prototype_ `static UMaterialInterface* CreateMaterial( FDatasmithImportContext& ImportContext, const TSharedRef< IDatasmithBaseMaterialElement >& BaseMaterialElement, UMaterialInterface* ExistingMaterial );`
- L34 _public prototype_ `static int32 GetMaterialRequirements(UMaterialInterface* MaterialInterface);`
- L37 _private prototype_ `static UMaterialInterface* ImportMaterialInstance( FDatasmithImportContext& ImportContext, const TSharedRef< IDatasmithMaterialInstanceElement >& MaterialElement, UMaterialInterface* ExistingMaterial );`
- L38 _private prototype_ `static UMaterialInterface* ImportDecalMaterial( FDatasmithImportContext& ImportContext, const TSharedRef< IDatasmithDecalMaterialElement >& MaterialElement, UMaterialInterface* ExistingMaterial );`

#### Free symbols / members of external scopes

- L17 _namespace_ `namespace EMaterialRequirements`

### `Plugins/Enterprise/DatasmithImporter/Source/DatasmithImporter/Public/DatasmithPostProcessImporter.h` (Public)


#### class `FDatasmithPostProcessImporter`  
`class FDatasmithPostProcessImporter`  
_L13-18_
- L16 _public prototype_ `static FDatasmithPostProcessSettingsTemplate CopyDatasmithPostProcessToUEPostProcess(const TSharedPtr< IDatasmithPostProcessElement >& Src);`
- L17 _public prototype_ `static AActor* ImportPostProcessVolume( const TSharedRef< IDatasmithPostProcessVolumeElement >& PostProcessVolumeElement, FDatasmithImportContext& ImportContext, EDatasmithImportActorPolicy ImportActorPolicy );`

### `Plugins/Enterprise/DatasmithImporter/Source/DatasmithImporter/Public/DatasmithStaticMeshImporter.h` (Public)


#### class `FDatasmithStaticMeshImporter`  
`class FDatasmithStaticMeshImporter`  
_L27-76_
- L31 _public prototype_ `static UStaticMesh* ImportStaticMesh( const TSharedRef< IDatasmithMeshElement > MeshElement, FDatasmithMeshElementPayload& Payload, EObjectFlags ObjectFlags, const FDatasmithStaticMeshImportOptions& ImportOptions, FDatasmithAssetsImportContext& AssetsContext, UStaticMesh* ExistingMesh );` — Imports a static mesh from a Mesh Element
- L33 _public prototype_ `static bool ShouldRecomputeNormals( const FMeshDescription& MeshDescription, int32 BuildRequirements );`
- L34 _public prototype_ `static bool ShouldRecomputeTangents( const FMeshDescription& MeshDescription, int32 BuildRequirements );`
- L37 _public prototype_ `static TMap< TSharedRef< IDatasmithMeshElement >, float > CalculateMeshesLightmapWeights( const TSharedRef< IDatasmithScene >& SceneElement );` — Calculates a lightmap density ratio for each IDatasmithMeshElement in the IDatasmithScene.
- L40 _public prototype_ `static void SetupStaticMesh( FDatasmithAssetsImportContext& AssetsContext, TSharedRef< IDatasmithMeshElement > MeshElement, UStaticMesh* StaticMesh, const FDatasmithStaticMeshImportOptions& StaticMeshImportOptions, float LightmapWeight );` — Setup a UStaticMesh from an IDatasmithMeshElement.
- L43 _public prototype_ `static void CleanupMeshDescriptions(TArray< FMeshDescription >& MeshDescriptions);` — Cleanup any invalid data in mesh descriptions that might cause the editor to crash or behave erratically (i.e. Having vertex position with NaN values).
- L46 _public prototype_ `static void PreBuildStaticMeshes( FDatasmithImportContext& ImportContext );` — Builds the lightmap UVs and tangents for all the imported meshes.
- L54 _public prototype_ `static bool PreBuildStaticMesh( UStaticMesh* StaticMesh );` — Performs threadable build step on the static mesh, to be called before BuildStaticMesh @param StaticMesh        Mesh to process @return false if the mesh has no triangles or all its triangles are degenerated. True otherwise
- L59 _public prototype_ `static void BuildStaticMesh( UStaticMesh* StaticMesh );` — Performs the actual building of the static mesh
- L67 _public prototype_ `static void BuildStaticMeshes(const TArray< UStaticMesh* >& StaticMeshes, TFunction<bool(UStaticMesh*)> ProgressCallback = nullptr);` — Performs the actual building of the static meshes in batch for better efficiency @param		StaticMeshes		The list of all static meshes to build. @param		ProgressCallback	If provided, will be used to abort task and report progress to higher level functions (should return true to continue, false to abort).
- L70 _private prototype_ `static void ProcessCollision( UStaticMesh* StaticMesh, const TArray< FVector3f >& VertexPositions );`
- L75 _private prototype_ `static void ApplyMaterialsToStaticMesh( const FDatasmithAssetsImportContext& AssetsContext, const TSharedRef< IDatasmithMeshElement >& MeshElement, class UDatasmithStaticMeshTemplate* StaticMeshTemplate );` — Applies the UMaterialInterfaces related to the IDatasmithMeshElement to the UStaticMesh.

### `Plugins/Enterprise/DatasmithImporter/Source/DatasmithImporter/Public/DatasmithTextureImporter.h` (Public)


#### class `FDatasmithTextureImporter`  
`class FDatasmithTextureImporter : private FNoncopyable`  
_L22-41_
- inherits: `FNoncopyable`
- L25 _public prototype_ `FDatasmithTextureImporter(FDatasmithImportContext& InImportContext);`
- L26 _public prototype_ `~FDatasmithTextureImporter();`
- L28 _public prototype_ `UTexture* CreateTexture(const TSharedPtr<IDatasmithTextureElement>& TextureElement, const TArray<uint8>& TextureData, const FString& Extension);`
- L29 _public prototype_ `bool GetTextureData(const TSharedPtr<IDatasmithTextureElement>& TextureElement, TArray<uint8>& TextureData, FString& Extension);`
- L30 _public prototype_ `UTexture* CreateIESTexture(const TSharedPtr<IDatasmithTextureElement>& TextureElement);`
- L32 _public prototype_ `UE::Interchange::FAssetImportResultRef CreateTextureAsync(const TSharedPtr<IDatasmithTextureElement>& TextureElement);`
- L35 _private prototype_ `bool ResizeTextureElement(const TSharedPtr<IDatasmithTextureElement>& TextureElement, FString& ResizedFilename);`
- L38 _private member_ `FDatasmithImportContext& ImportContext;`
- L39 _private member_ `TStrongObjectPtr< UTextureFactory > TextureFact;`
- L40 _private member_ `FString TempDir;`

#### class `UDatasmithTexturePipeline`  
`class UDatasmithTexturePipeline : public UInterchangePipelineBase`  
_L44-56_
- reflection: `UCLASS()`
- inherits: `UInterchangePipelineBase`
- L49 _public prototype_ `virtual void ExecutePipeline(UInterchangeBaseNodeContainer* BaseNodeContainer, const TArray<UInterchangeSourceData*>& SourceDatas, const FString& ContentBasePath) override;`
- L51 _public function_ `bool IsScripted() override`
- L55 _public member_ `TSharedPtr< IDatasmithTextureElement > TextureElement;`

### `Plugins/Enterprise/DatasmithImporter/Source/DatasmithImporter/Public/ObjectElements/DatasmithUObjectElements.h` (Public)


#### class `UDatasmithObjectElement`  
`class UDatasmithObjectElement : public UObject`  
_L18-46_
- reflection: `UCLASS(Abstract, BlueprintType, Transient)`
- inherits: `UObject`
- desc: UDatasmithObjectElement
- L25 _public prototype_ `FString GetElementName() const;` — `UFUNCTION(BlueprintCallable, Category="Datasmith | Element")` — Gets the element name
- L29 _public prototype_ `FString GetLabel() const;` — `UFUNCTION(BlueprintCallable, Category="Datasmith | Element")` — Gets the element label used in the UI
- L33 _public prototype_ `void SetLabel(const FString& InLabel);` — `UFUNCTION(BlueprintCallable, Category="Datasmith | Element")` — Sets the element label used in the UI
- L37 _public prototype_ `virtual bool IsElementValid() const;` — `UFUNCTION(BlueprintCallable, Category="Datasmith | Element")` — Is the Element still valid for the Datasmith Scene
- L45 _protected prototype_ `virtual TWeakPtr<IDatasmithElement> GetIDatasmithElement() const PURE_VIRTUAL(UDatasmithObjectElement::GetIDatasmithElement, return nullptr;);` — TODO: They are not covariant because of the TWeakPtr, can't override in child

#### class `UDatasmithKeyValueProperty`  
`class UDatasmithKeyValueProperty : public UDatasmithObjectElement`  
_L52-85_
- reflection: `UCLASS()`
- inherits: `UDatasmithObjectElement`
- desc: UDatasmithKeyValueProperty
- L59 _public prototype_ `EDatasmithKeyValuePropertyType GetPropertyType() const;` — `UFUNCTION(BlueprintCallable, Category="Datasmith | Element")` — Get the type of this property
- L63 _public prototype_ `void SetPropertyType(EDatasmithKeyValuePropertyType InType);` — `UFUNCTION(BlueprintCallable, Category="Datasmith | Element")` — Set the type of this property
- L67 _public prototype_ `FString GetValue() const;` — `UFUNCTION(BlueprintCallable, Category="Datasmith | Element")` — Get the value of this property
- L71 _public prototype_ `void SetValue(const FString& Value);` — `UFUNCTION(BlueprintCallable, Category="Datasmith | Element")` — Sets the value of this property
- L74 _public function_ `TWeakPtr<IDatasmithKeyValueProperty> GetDatasmithKeyValueProperty() const`
- L75 _public function_ `void SetDatasmithKeyValueProperty(const TSharedPtr<IDatasmithKeyValueProperty>& InElement)`
- L78 _public prototype_ `virtual bool IsElementValid() const override;` — Is the Element still valid for the Datasmith Scene
- L81 _protected function_ `virtual TWeakPtr<IDatasmithElement> GetIDatasmithElement() const override`
- L84 _private member_ `TWeakPtr<IDatasmithKeyValueProperty> KeyValueProperty;`

#### class `UDatasmithActorElement`  
`class UDatasmithActorElement : public UDatasmithObjectElement`  
_L91-162_
- reflection: `UCLASS(Abstract)`
- inherits: `UDatasmithObjectElement`
- desc: UDatasmithActorElement
- L98 _public prototype_ `FVector GetTranslation() const;` — `UFUNCTION(BlueprintCallable, Category="Datasmith | Element")` — Get absolute translation of this entity
- L102 _public prototype_ `void SetTranslation(FVector Value);` — `UFUNCTION(BlueprintCallable, Category="Datasmith | Element")` — Set absolute translation of this entity
- L106 _public prototype_ `FVector GetScale() const;` — `UFUNCTION(BlueprintCallable, Category="Datasmith | Element")` — Get absolute scale of this entity
- L110 _public prototype_ `void SetScale(FVector Value);` — `UFUNCTION(BlueprintCallable, Category="Datasmith | Element")` — Set absolute scale of this entity
- L114 _public prototype_ `FQuat GetRotation() const;` — `UFUNCTION(BlueprintCallable, Category="Datasmith | Element")` — Get rotation (in quaternion format) of this entity
- L118 _public prototype_ `void SetRotation(FQuat Value);` — `UFUNCTION(BlueprintCallable, Category="Datasmith | Element")` — Set rotation (in quaternion format) of this entity
- L122 _public prototype_ `FString GetLayer() const;` — `UFUNCTION(BlueprintCallable, Category="Datasmith | Element")` — Get the the name of the layer that contains this entity
- L126 _public prototype_ `void SetLayer(const FString& InLayer);` — `UFUNCTION(BlueprintCallable, Category="Datasmith | Element")` — Set the the the layer that contains this entity, layer will be auto-created from its name
- L130 _public prototype_ `TArray<FString> GetTags() const;` — `UFUNCTION(BlueprintCallable, Category="Datasmith | Element")` — Get the tags of an Actor element
- L134 _public prototype_ `void SetTags(const TArray<FString>& InTags);` — `UFUNCTION(BlueprintCallable, Category="Datasmith | Element")` — Set the tags of an Actor element
- L138 _public prototype_ `void AddChild(UDatasmithActorElement* InChild);` — `UFUNCTION(BlueprintCallable, Category="Datasmith | Element")` — Adds a child to the Actor Element
- L142 _public prototype_ `int32 GetChildrenCount() const;` — `UFUNCTION(BlueprintCallable, Category="Datasmith | Element")` — Get the number of children on this actor
- L146 _public prototype_ `TArray<UDatasmithActorElement*> GetChildren() const;` — `UFUNCTION(BlueprintCallable, Category="Datasmith | Element")` — Get the children of the mesh actor. Use AddChild -or- RemoveChild to modify the actor's children
- L150 _public prototype_ `void RemoveChild(UDatasmithActorElement* InChild);` — `UFUNCTION(BlueprintCallable, Category="Datasmith | Element")` — Remove a new child from the Actor Element
- L154 _public prototype_ `bool GetVisibility() const;` — `UFUNCTION(BlueprintCallable, Category="Datasmith | Element")` — Get the actor's visibility
- L158 _public prototype_ `void SetVisibility(bool bInVisibility);` — `UFUNCTION(BlueprintCallable, Category="Datasmith | Element")` — Set the actor's visibility
- L161 _public prototype_ `virtual TWeakPtr<IDatasmithActorElement> GetIDatasmithActorElement() const PURE_VIRTUAL(UDatasmithActorElement::GetIDatasmithActorElement, return nullptr;);`

#### class `UDatasmithMeshElement`  
`class UDatasmithMeshElement : public UDatasmithObjectElement`  
_L169-237_
- reflection: `UCLASS()`
- inherits: `UDatasmithObjectElement`
- desc: UDatasmithMeshElement defines an actual geometry.
- L176 _public prototype_ `FString GetFile() const;` — `UFUNCTION(BlueprintCallable, Category="Datasmith | Element")` — Get the output filename, it can be absolute or relative to the scene file
- L180 _public prototype_ `float GetBoundingBoxWidth() const;` — `UFUNCTION(BlueprintCallable, Category="Datasmith | Element")` — Get the bounding box width
- L184 _public prototype_ `float GetBoundingBoxHeight() const;` — `UFUNCTION(BlueprintCallable, Category="Datasmith | Element")` — Get the bounding box height
- L188 _public prototype_ `float GetBoundingBoxDepth() const;` — `UFUNCTION(BlueprintCallable, Category="Datasmith | Element")` — Get the bounding box depth
- L192 _public prototype_ `FVector GetBoundingBoxSize() const;` — `UFUNCTION(BlueprintCallable, Category = "Datasmith | Element")` — Get the bounding box represented by a Vector. X is Width, Y is Height, Z is Depth.
- L196 _public prototype_ `float GetLightMapArea() const;` — `UFUNCTION(BlueprintCallable, Category="Datasmith | Element")` — Get the total surface area
- L200 _public prototype_ `int32 GetLightmapCoordinateIndex() const;` — `UFUNCTION(BlueprintCallable, Category = "Datasmith | Element")` — Get the UV channel that will be used for the lightmap
- L207 _public prototype_ `void SetLightmapCoordinateIndex(int32 UVChannel);` — `UFUNCTION(BlueprintCallable, Category = "Datasmith | Element")` — Set the UV channel that will be used for the lightmap Note: If the lightmap coordinate index is something greater than -1 it will make the importer skip the lightmap generation
- L211 _public prototype_ `int32 GetLightmapSourceUV() const;` — `UFUNCTION(BlueprintCallable, Category="Datasmith | Element")` — Get the source UV channel that will be used at import to generate the lightmap UVs
- L215 _public prototype_ `void SetLightmapSourceUV(int32 UVChannel);` — `UFUNCTION(BlueprintCallable, Category = "Datasmith | Element")` — Set the source UV channel that will be used at import to generate the lightmap UVs
- L219 _public prototype_ `void SetMaterial(const FString& MaterialName, int32 SlotId);` — `UFUNCTION(BlueprintCallable, Category="Datasmith | Element")` — Set the material name to associate with slot SlotId
- L223 _public prototype_ `FString GetMaterial(int32 SlotId);` — `UFUNCTION(BlueprintCallable, Category = "Datasmith | Element")` — Get the material name in the material slot SlotId
- L226 _public function_ `TWeakPtr<IDatasmithMeshElement> GetDatasmithMeshElement() const`
- L227 _public function_ `void SetDatasmithMeshElement(const TSharedPtr<IDatasmithMeshElement>& InElement)`
- L230 _public prototype_ `virtual bool IsElementValid() const override;` — Is the Element still valid for the Datasmith Scene
- L233 _protected function_ `virtual TWeakPtr<IDatasmithElement> GetIDatasmithElement() const override`
- L236 _private member_ `TWeakPtr<IDatasmithMeshElement> MeshElement;`

#### class `UDatasmithMeshActorElement`  
`class UDatasmithMeshActorElement : public UDatasmithActorElement`  
_L244-302_
- reflection: `UCLASS()`
- inherits: `UDatasmithActorElement`
- desc: UDatasmithMeshActorElement
- L251 _public prototype_ `void AddMaterialOverride(class UDatasmithMaterialIDElement* Material);` — `UFUNCTION(BlueprintCallable, Category="Datasmith | Element")` — Adds a new material to the Actor Element
- L255 _public prototype_ `int32 GetMaterialOverridesCount() const;` — `UFUNCTION(BlueprintCallable, Category="Datasmith | Element")` — Get the amount of materials on this mesh
- L259 _public prototype_ `TArray<UDatasmithMaterialIDElement*> GetMaterials() const;` — `UFUNCTION(BlueprintCallable, Category="Datasmith | Element")` — Get the i-th material of this actor
- L263 _public prototype_ `void RemoveMaterialOverride(class UDatasmithMaterialIDElement* Material);` — `UFUNCTION(BlueprintCallable, Category="Datasmith | Element")` — Get the amount of materials on this mesh
- L267 _public prototype_ `FString GetStaticMeshPathName() const;` — `UFUNCTION(BlueprintCallable, Category="Datasmith | Element")` — Get the path name of the StaticMesh associated with the actor
- L274 _public prototype_ `void SetStaticMeshPathName(const FString& InStaticMeshName);` — `UFUNCTION(BlueprintCallable, Category="Datasmith | Element")` — Set the path name of the StaticMesh that the actor is using It can be either a package path to refer to an existing mesh or a mesh name to refer to a MeshElement in the DatasmithScene
- L276 _public prototype_ `bool IsStaticMeshPathRelative() const;`
- L280 _public prototype_ `UDatasmithMeshElement* GetMeshElement();` — `UFUNCTION(BlueprintCallable, Category = "Datasmith | Element")` — Get the Datasmith MeshElement associated with the actor. The Mesh can be a direct reference to an Unreal Mesh. If it's the case it will return an invalid MeshElement.
- L288 _public prototype_ `FVector GetBoundingBoxSize() const;` — `UFUNCTION(BlueprintCallable, Category = "Datasmith | Element")` — Get the Bounding Box of the Actor as a Vector. X is Width, Y is Height, Z is Depth. The value will are taken from the MeshElement and are factored by the Actor Scale. Bounding Box size can only be calculated if the Mesh can be found.
- L291 _public function_ `TWeakPtr<IDatasmithMeshActorElement> GetDatasmithMeshActorElement() const`
- L292 _public function_ `void SetDatasmithMeshActorElement(const TSharedPtr<IDatasmithMeshActorElement>& InElement)`
- L295 _public prototype_ `virtual bool IsElementValid() const override;` — Is the Element still valid for the Datasmith Scene
- L297 _public function_ `virtual TWeakPtr<IDatasmithElement> GetIDatasmithElement() const override`
- L298 _public function_ `virtual TWeakPtr<IDatasmithActorElement> GetIDatasmithActorElement() const override`
- L301 _private member_ `TWeakPtr<IDatasmithMeshActorElement> MeshActorElemement;`

#### class `UDatasmithLightActorElement`  
`class UDatasmithLightActorElement : public UDatasmithActorElement`  
_L309-398_
- reflection: `UCLASS()`
- inherits: `UDatasmithActorElement`
- desc: UDatasmithLightActorElement
- L316 _public prototype_ `bool IsEnabled() const;` — `UFUNCTION(BlueprintCallable, Category = "Datasmith | Element")` — Return true on light enabled, false otherwise
- L320 _public prototype_ `void SetEnabled(bool bIsEnabled);` — `UFUNCTION(BlueprintCallable, Category = "Datasmith | Element")` — Set enable property of the light
- L324 _public prototype_ `float GetIntensity() const;` — `UFUNCTION(BlueprintCallable, Category = "Datasmith | Element")` — Get light intensity
- L328 _public prototype_ `void SetIntensity(float Intensity);` — `UFUNCTION(BlueprintCallable, Category = "Datasmith | Element")` — Set light intensity
- L332 _public prototype_ `FLinearColor GetColor() const;` — `UFUNCTION(BlueprintCallable, Category = "Datasmith | Element")` — Get light color on linear mode
- L336 _public prototype_ `void SetColor(FLinearColor Color);` — `UFUNCTION(BlueprintCallable, Category = "Datasmith | Element")` — Set light color on linear mode
- L340 _public prototype_ `float GetTemperature() const;` — `UFUNCTION(BlueprintCallable, Category = "Datasmith | Element")` — Get the light temperature in Kelvin
- L344 _public prototype_ `void SetTemperature(float Temperature);` — `UFUNCTION(BlueprintCallable, Category = "Datasmith | Element")` — Set the light temperature in Kelvin
- L348 _public prototype_ `bool GetUseTemperature() const;` — `UFUNCTION(BlueprintCallable, Category = "Datasmith | Element")` — Get if the light color is controlled by temperature
- L352 _public prototype_ `void SetUseTemperature(bool bUseTemperature);` — `UFUNCTION(BlueprintCallable, Category = "Datasmith | Element")` — Set if the light color is controlled by temperature
- L356 _public prototype_ `FString GetIesFile() const;` — `UFUNCTION(BlueprintCallable, Category = "Datasmith | Element")` — Get the path of the Ies definition file
- L360 _public prototype_ `void SetIesFile(const FString& IesFile);` — `UFUNCTION(BlueprintCallable, Category = "Datasmith | Element")` — Set the path of the Ies definition file
- L364 _public prototype_ `bool GetUseIes() const;` — `UFUNCTION(BlueprintCallable, Category = "Datasmith | Element")` — Set if this light is controlled by Ies definition file
- L368 _public prototype_ `void SetUseIes(bool bUseIes);` — `UFUNCTION(BlueprintCallable, Category = "Datasmith | Element")` — Get if this light is controlled by Ies definition file
- L372 _public prototype_ `float GetIesBrightnessScale() const;` — `UFUNCTION(BlueprintCallable, Category = "Datasmith | Element")` — Get the Ies brightness multiplier
- L376 _public prototype_ `void SetIesBrightnessScale(float IesBrightnessScale);` — `UFUNCTION(BlueprintCallable, Category = "Datasmith | Element")` — Set the Ies brightness multiplier
- L380 _public prototype_ `bool GetUseIesBrightness() const;` — `UFUNCTION(BlueprintCallable, Category = "Datasmith | Element")` — Get if the emissive amount of the ies is controlled by the brightness scale
- L384 _public prototype_ `void SetUseIesBrightness(bool bUseIesBrightness);` — `UFUNCTION(BlueprintCallable, Category = "Datasmith | Element")` — Set if the emissive amount of the ies is controlled by the brightness scale
- L387 _public function_ `TWeakPtr<IDatasmithLightActorElement> GetDatasmithLightActorElement() const`
- L388 _public function_ `void SetDatasmithLightActorElement(const TSharedPtr<IDatasmithLightActorElement>& InElement)`
- L391 _public prototype_ `virtual bool IsElementValid() const override;` — Is the Element still valid for the Datasmith Scene
- L393 _public function_ `virtual TWeakPtr<IDatasmithElement> GetIDatasmithElement() const override`
- L394 _public function_ `virtual TWeakPtr<IDatasmithActorElement> GetIDatasmithActorElement() const override`
- L397 _private member_ `TWeakPtr<IDatasmithLightActorElement> LightActorElement;`

#### class `UDatasmithCameraActorElement`  
`class UDatasmithCameraActorElement : public UDatasmithActorElement`  
_L405-482_
- reflection: `UCLASS()`
- inherits: `UDatasmithActorElement`
- desc: UDatasmithCameraActorElement
- L412 _public prototype_ `float GetSensorWidth() const;` — `UFUNCTION(BlueprintCallable, Category = "Datasmith | Element")` — Get camera sensor width in millimeters
- L416 _public prototype_ `void SetSensorWidth(float SensorWidth);` — `UFUNCTION(BlueprintCallable, Category = "Datasmith | Element")` — Set camera sensor width in millimeters
- L420 _public prototype_ `float GetSensorAspectRatio() const;` — `UFUNCTION(BlueprintCallable, Category = "Datasmith | Element")` — Get framebuffer aspect ratio (width/height)
- L424 _public prototype_ `void SetSensorAspectRatio(float SensorAspectRatio);` — `UFUNCTION(BlueprintCallable, Category = "Datasmith | Element")` — Set framebuffer aspect ratio (width/height)
- L428 _public prototype_ `float GetFocusDistance() const;` — `UFUNCTION(BlueprintCallable, Category = "Datasmith | Element")` — Get camera focus distance in centimeters
- L432 _public prototype_ `void SetFocusDistance(float FocusDistance);` — `UFUNCTION(BlueprintCallable, Category = "Datasmith | Element")` — Set camera focus distance in centimeters
- L436 _public prototype_ `float GetFStop() const;` — `UFUNCTION(BlueprintCallable, Category = "Datasmith | Element")` — Get camera FStop also known as FNumber
- L440 _public prototype_ `void SetFStop(float FStop);` — `UFUNCTION(BlueprintCallable, Category = "Datasmith | Element")` — Set camera FStop also known as FNumber
- L444 _public prototype_ `float GetFocalLength() const;` — `UFUNCTION(BlueprintCallable, Category = "Datasmith | Element")` — Get camera focal length in millimeters
- L448 _public prototype_ `void SetFocalLength(float FocalLength);` — `UFUNCTION(BlueprintCallable, Category = "Datasmith | Element")` — Set camera focal length in millimeters
- L452 _public prototype_ `UDatasmithPostProcessElement* GetPostProcess();` — `UFUNCTION(BlueprintCallable, Category = "Datasmith | Element")` — Get camera's postprocess
- L456 _public prototype_ `FString GetLookAtActor() const;` — `UFUNCTION(BlueprintCallable, Category = "Datasmith | Element")` — Get camera look at actor name
- L460 _public prototype_ `void SetLookAtActor(const FString& ActorPathName);` — `UFUNCTION(BlueprintCallable, Category = "Datasmith | Element")` — Set camera look at actor name
- L464 _public prototype_ `bool GetLookAtAllowRoll() const;` — `UFUNCTION(BlueprintCallable, Category = "Datasmith | Element")` — Get camera look at allow roll state
- L468 _public prototype_ `void SetLookAtAllowRoll(bool bAllow);` — `UFUNCTION(BlueprintCallable, Category = "Datasmith | Element")` — Set camera look at allow roll state
- L471 _public function_ `TWeakPtr<IDatasmithCameraActorElement> GetDatasmithCameraActorElement() const`
- L472 _public function_ `void SetDatasmithCameraActorElement(const TSharedPtr<IDatasmithCameraActorElement>& InElement)`
- L475 _public prototype_ `virtual bool IsElementValid() const override;` — Is the Element still valid for the Datasmith Scene
- L477 _public function_ `virtual TWeakPtr<IDatasmithElement> GetIDatasmithElement() const override`
- L478 _public function_ `virtual TWeakPtr<IDatasmithActorElement> GetIDatasmithActorElement() const override`
- L481 _private member_ `TWeakPtr<IDatasmithCameraActorElement> CameraActorElement;`

#### class `UDatasmithCustomActorElement`  
`class UDatasmithCustomActorElement : public UDatasmithActorElement`  
_L488-538_
- reflection: `UCLASS()`
- inherits: `UDatasmithActorElement`
- desc: UDatasmithCustomActorElement
- L495 _public prototype_ `FString GetClassOrPathName() const;` — `UFUNCTION(BlueprintCallable, Category="Datasmith | Element")` — The blueprint to instantiate.
- L498 _public prototype_ `void SetClassOrPathName(const FString& InPathName);` — `UFUNCTION(BlueprintCallable, Category="Datasmith | Element")`
- L502 _public prototype_ `int32 GetPropertiesCount() const;` — `UFUNCTION(BlueprintCallable, Category="Datasmith | Element")` — Get the total amount of properties in this blueprint actor
- L506 _public prototype_ `UDatasmithKeyValueProperty* GetProperty(int32 i);` — `UFUNCTION(BlueprintCallable, Category="Datasmith | Element")` — Get the property i-th of this blueprint actor
- L510 _public prototype_ `UDatasmithKeyValueProperty* GetPropertyByName(const FString& InName);` — `UFUNCTION(BlueprintCallable, Category="Datasmith | Element")` — Get a property by its name if it exists
- L514 _public prototype_ `void AddProperty(UDatasmithKeyValueProperty* Property);` — `UFUNCTION(BlueprintCallable, Category="Datasmith | Element")` — Add a property to this blueprint actor
- L518 _public prototype_ `void RemoveProperty(UDatasmithKeyValueProperty* Property);` — `UFUNCTION(BlueprintCallable, Category="Datasmith | Element")` — Removes a property from this blueprint actor, doesn't preserve ordering
- L521 _public function_ `TWeakPtr<IDatasmithCustomActorElement> GetDatasmithCustomActorElement() const`
- L522 _public function_ `void SetDatasmithCustomActorElement(const TSharedPtr<IDatasmithCustomActorElement>& InElement)`
- L525 _public prototype_ `virtual bool IsElementValid() const override;` — Is the Element still valid for the Datasmith Scene
- L526 _public prototype_ `bool IsElementValid(const TWeakPtr<IDatasmithKeyValueProperty>& Element) const;`
- L528 _public prototype_ `UDatasmithKeyValueProperty* FindOrAddElement(const TSharedPtr<IDatasmithKeyValueProperty>& InElement);`
- L531 _protected function_ `virtual TWeakPtr<IDatasmithElement> GetIDatasmithElement() const override`
- L532 _protected function_ `virtual TWeakPtr<IDatasmithActorElement> GetIDatasmithActorElement() const override`
- L534 _protected member_ `TMap< TWeakPtr< IDatasmithKeyValueProperty >, UDatasmithKeyValueProperty* > Properties;`
- L537 _private member_ `TWeakPtr<IDatasmithCustomActorElement> CustomActorElement;`

#### class `UDatasmithBaseMaterialElement`  
`class UDatasmithBaseMaterialElement : public UDatasmithObjectElement`  
_L544-560_
- reflection: `UCLASS()`
- inherits: `UDatasmithObjectElement`
- desc: UDatasmithBaseMaterialElement
- L549 _public function_ `TWeakPtr<IDatasmithBaseMaterialElement> GetDatasmithBaseMaterialElement() const`
- L550 _public function_ `void SetDatasmithBaseMaterialElement(const TSharedPtr<IDatasmithBaseMaterialElement>& InElement)`
- L553 _public prototype_ `virtual bool IsElementValid() const override;` — Is the Element still valid for the Datasmith Scene
- L556 _protected function_ `virtual TWeakPtr<IDatasmithElement> GetIDatasmithElement() const override`
- L559 _private member_ `TWeakPtr<IDatasmithBaseMaterialElement> BaseMaterialElemement;`

#### class `UDatasmithMaterialIDElement`  
`class UDatasmithMaterialIDElement : public UDatasmithObjectElement`  
_L566-586_
- reflection: `UCLASS()`
- inherits: `UDatasmithObjectElement`
- desc: UDatasmithMaterialIDElement
- L572 _public prototype_ `int32 GetId() const;` — `UFUNCTION(BlueprintCallable, Category="Datasmith | Element")`
- L575 _public function_ `TWeakPtr<IDatasmithMaterialIDElement> GetDatasmithMaterialIDElement() const`
- L576 _public function_ `void SetDatasmithMaterialIDElement(const TSharedPtr<IDatasmithMaterialIDElement>& InElement)`
- L579 _public prototype_ `virtual bool IsElementValid() const override;` — Is the Element still valid for the Datasmith Scene
- L582 _protected function_ `virtual TWeakPtr<IDatasmithElement> GetIDatasmithElement() const override`
- L585 _private member_ `TWeakPtr<IDatasmithMaterialIDElement> MaterialElemement;`

#### class `UDatasmithPostProcessElement`  
`class UDatasmithPostProcessElement : public UDatasmithObjectElement`  
_L593-674_
- reflection: `UCLASS()`
- inherits: `UDatasmithObjectElement`
- desc: UDatasmithPostProcessElement
- L600 _public prototype_ `float GetTemperature() const;` — `UFUNCTION(BlueprintCallable, Category="Datasmith | Element")` — Get color filter temperature in Kelvin
- L604 _public prototype_ `void SetTemperature(float Temperature);` — `UFUNCTION(BlueprintCallable, Category="Datasmith | Element")` — Set color filter temperature in Kelvin
- L608 _public prototype_ `FLinearColor GetColorFilter() const;` — `UFUNCTION(BlueprintCallable, Category="Datasmith | Element")` — Set color filter in linear color scale
- L612 _public prototype_ `void SetColorFilter(FLinearColor ColorFilter);` — `UFUNCTION(BlueprintCallable, Category="Datasmith | Element")` — Get color filter in linear color scale
- L616 _public prototype_ `float GetVignette() const;` — `UFUNCTION(BlueprintCallable, Category="Datasmith | Element")` — Get vignette amount
- L620 _public prototype_ `void SetVignette(float Vignette);` — `UFUNCTION(BlueprintCallable, Category="Datasmith | Element")` — Set vignette amount
- L624 _public prototype_ `float GetDof() const;` — `UFUNCTION(BlueprintCallable, Category="Datasmith | Element")` — Get depth of field multiplier
- L628 _public prototype_ `void SetDof(float Dof);` — `UFUNCTION(BlueprintCallable, Category="Datasmith | Element")` — Set depth of field multiplier
- L632 _public prototype_ `float GetMotionBlur() const;` — `UFUNCTION(BlueprintCallable, Category="Datasmith | Element")` — Get motion blur multiplier
- L636 _public prototype_ `void SetMotionBlur(float MotionBlur);` — `UFUNCTION(BlueprintCallable, Category="Datasmith | Element")` — Set motion blur multiplier
- L640 _public prototype_ `float GetSaturation() const;` — `UFUNCTION(BlueprintCallable, Category="Datasmith | Element")` — Get color saturation
- L644 _public prototype_ `void SetSaturation(float Saturation);` — `UFUNCTION(BlueprintCallable, Category="Datasmith | Element")` — Set color saturation
- L648 _public prototype_ `float GetCameraISO() const;` — `UFUNCTION(BlueprintCallable, Category="Datasmith | Element")` — Get camera ISO
- L652 _public prototype_ `void SetCameraISO(float CameraISO);` — `UFUNCTION(BlueprintCallable, Category="Datasmith | Element")` — Set camera ISO
- L656 _public prototype_ `float GetCameraShutterSpeed() const;` — `UFUNCTION(BlueprintCallable, Category = "Datasmith | Element")` — Get camera shutter speed in 1/seconds (ie: 60 = 1/60s)
- L660 _public prototype_ `void SetCameraShutterSpeed(float CameraShutterSpeed);` — `UFUNCTION(BlueprintCallable, Category = "Datasmith | Element")` — Set camera shutter speed in 1/seconds (ie: 60 = 1/60s)
- L663 _public function_ `TWeakPtr<IDatasmithPostProcessElement> GetDatasmithPostProcessElement() const`
- L664 _public function_ `void SetDatasmithPostProcessElement(const TSharedPtr<IDatasmithPostProcessElement>& InElement)`
- L667 _public prototype_ `virtual bool IsElementValid() const override;` — Is the Element still valid for the Datasmith Scene
- L670 _protected function_ `virtual TWeakPtr<IDatasmithElement> GetIDatasmithElement() const override`
- L673 _private member_ `TWeakPtr<IDatasmithPostProcessElement> PostProcessElemement;`

#### class `UDatasmithTextureElement`  
`class UDatasmithTextureElement : public UDatasmithObjectElement`  
_L681-738_
- reflection: `UCLASS()`
- inherits: `UDatasmithObjectElement`
- desc: UDatasmithTextureElement
- L688 _public prototype_ `FString GetFile() const;` — `UFUNCTION(BlueprintCallable, Category="Datasmith | Element")` — Get texture filename
- L692 _public prototype_ `void SetFile(const FString& File);` — `UFUNCTION(BlueprintCallable, Category="Datasmith | Element")` — Set texture filename
- L696 _public prototype_ `EDatasmithTextureMode GetTextureMode() const;` — `UFUNCTION(BlueprintCallable, Category="Datasmith | Element")` — Get texture usage
- L700 _public prototype_ `void SetTextureMode(EDatasmithTextureMode Mode);` — `UFUNCTION(BlueprintCallable, Category="Datasmith | Element")` — Set texture usage
- L704 _public prototype_ `bool GetAllowResize() const;` — `UFUNCTION(BlueprintCallable, Category="Datasmith | Element")` — Get allow texture resizing
- L708 _public prototype_ `void SetAllowResize(bool bAllowResize);` — `UFUNCTION(BlueprintCallable, Category="Datasmith | Element")` — Set allow texture resizing
- L712 _public prototype_ `float GetRGBCurve() const;` — `UFUNCTION(BlueprintCallable, Category="Datasmith | Element")` — Get texture gamma <= 0 for auto
- L716 _public prototype_ `void SetRGBCurve(float InRGBCurve);` — `UFUNCTION(BlueprintCallable, Category="Datasmith | Element")` — Set texture gamma <= 0 for auto
- L720 _public prototype_ `EDatasmithColorSpace GetColorSpace() const;` — `UFUNCTION(BlueprintCallable, Category="Datasmith | Element")` — Gets the color space of the texture
- L724 _public prototype_ `void SetColorSpace(EDatasmithColorSpace Option);` — `UFUNCTION(BlueprintCallable, Category="Datasmith | Element")` — Sets the color space of the texture
- L727 _public function_ `TWeakPtr<IDatasmithTextureElement> GetDatasmithTextureElement() const`
- L728 _public function_ `void SetDatasmithTextureElement(const TSharedPtr<IDatasmithTextureElement>& InElement)`
- L731 _public prototype_ `virtual bool IsElementValid() const override;` — Is the Element still valid for the Datasmith Scene
- L734 _protected function_ `virtual TWeakPtr<IDatasmithElement> GetIDatasmithElement() const override`
- L737 _private member_ `TWeakPtr<IDatasmithTextureElement> TextureElemement;`

#### class `UDatasmithMetaDataElement`  
`class UDatasmithMetaDataElement : public UDatasmithObjectElement`  
_L744-785_
- reflection: `UCLASS()`
- inherits: `UDatasmithObjectElement`
- desc: UDatasmithMetaDataElement
- L750 _public prototype_ `int32 GetPropertiesCount() const;` — `UFUNCTION(BlueprintCallable, Category="Datasmith | Element")`
- L754 _public prototype_ `UDatasmithKeyValueProperty* GetProperty(int32 i);` — `UFUNCTION(BlueprintCallable, Category="Datasmith | Element")` — Get the property i-th of this meta data
- L758 _public prototype_ `UDatasmithKeyValueProperty* GetPropertyByName(const FString& InName);` — `UFUNCTION(BlueprintCallable, Category="Datasmith | Element")` — Get a property by its name if it exists
- L762 _public prototype_ `UDatasmithObjectElement* GetAssociatedElement() const;` — `UFUNCTION(BlueprintCallable, Category = "Datasmith | Element")` — Get the element that is associated with this meta data
- L766 _public prototype_ `void GetProperties(TArray<FString>& OutKeys, TArray<FString>& OutValues);` — `UFUNCTION(BlueprintCallable, Category = "Datasmith | Element")` — Get this metadata element properties as a map of keys and values
- L769 _public function_ `TWeakPtr<IDatasmithMetaDataElement> GetDatasmithMetaDataElement() const`
- L770 _public function_ `void SetDatasmithMetaDataElement(const TSharedPtr<IDatasmithMetaDataElement>& InElement)`
- L773 _public prototype_ `virtual bool IsElementValid() const override;` — Is the Element still valid for the Datasmith Scene
- L774 _public prototype_ `bool IsElementValid(const TWeakPtr<IDatasmithKeyValueProperty>& Element) const;`
- L776 _public prototype_ `UDatasmithKeyValueProperty* FindOrAddElement(const TSharedPtr<IDatasmithKeyValueProperty>& InElement);`
- L779 _protected function_ `virtual TWeakPtr<IDatasmithElement> GetIDatasmithElement() const override`
- L781 _protected member_ `TMap< TWeakPtr< IDatasmithKeyValueProperty >, UDatasmithKeyValueProperty* > Properties;`
- L784 _private member_ `TWeakPtr<IDatasmithMetaDataElement> MetaDataElement;`

#### class `UDatasmithBasePropertyCaptureElement`  
`class UDatasmithBasePropertyCaptureElement : public UDatasmithObjectElement`  
_L791-821_
- reflection: `UCLASS()`
- inherits: `UDatasmithObjectElement`
- desc: UDatasmithBasePropertyCaptureElement
- L798 _public prototype_ `void SetPropertyPath(const FString& Path) const;` — `UFUNCTION(BlueprintCallable, Category="Datasmith | Element")` — Sets the path used when attempting to capture a generic property
- L802 _public prototype_ `FString GetPropertyPath() const;` — `UFUNCTION(BlueprintCallable, Category="Datasmith | Element")` — Gets the path used when attempting to capture a generic property
- L806 _public prototype_ `void SetCategory(EDatasmithPropertyCategory Category);` — `UFUNCTION(BlueprintCallable, Category="Datasmith | Element")` — Sets the category of this property capture
- L810 _public prototype_ `EDatasmithPropertyCategory GetCategory() const;` — `UFUNCTION(BlueprintCallable, Category="Datasmith | Element")` — Gets the category of this property capture
- L813 _public function_ `TWeakPtr<IDatasmithBasePropertyCaptureElement> GetBasePropertyCaptureElement() const`
- L816 _public prototype_ `virtual bool IsElementValid() const override;` — Is the Element still valid for the Datasmith Scene
- L819 _protected function_ `virtual TWeakPtr<IDatasmithElement> GetIDatasmithElement() const override`
- L820 _protected member_ `TWeakPtr<IDatasmithBasePropertyCaptureElement> DatasmithElement;`

#### class `UDatasmithPropertyCaptureElement`  
`class UDatasmithPropertyCaptureElement : public UDatasmithBasePropertyCaptureElement`  
_L827-967_
- reflection: `UCLASS()`
- inherits: `UDatasmithBasePropertyCaptureElement`
- desc: UDatasmithPropertyCaptureElement
- L837 _public prototype_ `bool GetValueBool();` — `UFUNCTION(BlueprintCallable, Category="Datasmith | Element")` — Get the recorded value for this property as a boolean. Returned value is meaningless if the property is not of boolean type.
- L841 _public prototype_ `void SetValueBool(bool InValue);` — `UFUNCTION(BlueprintCallable, Category="Datasmith | Element")` — Set the recorded value for this capture
- L848 _public prototype_ `int32 GetValueInt();` — `UFUNCTION(BlueprintCallable, Category="Datasmith | Element")` — Get the recorded value for this property as an int32. Returned value is meaningless if the property is not of int32 type.
- L852 _public prototype_ `void SetValueInt(int32 InValue);` — `UFUNCTION(BlueprintCallable, Category="Datasmith | Element")` — Set the recorded value for this capture
- L859 _public prototype_ `float GetValueFloat();` — `UFUNCTION(BlueprintCallable, Category="Datasmith | Element")` — Get the recorded value for this property as a float. Returned value is meaningless if the property is not of float type.
- L863 _public prototype_ `void SetValueFloat(float InValue);` — `UFUNCTION(BlueprintCallable, Category="Datasmith | Element")` — Set the recorded value for this capture
- L870 _public prototype_ `FString GetValueString();` — `UFUNCTION(BlueprintCallable, Category="Datasmith | Element")` — Get the recorded value for this property as a string. Returned value is meaningless if the property is not of string type.
- L874 _public prototype_ `void SetValueString(const FString& InValue);` — `UFUNCTION(BlueprintCallable, Category="Datasmith | Element")` — Set the recorded value for this capture
- L881 _public prototype_ `FRotator GetValueRotator();` — `UFUNCTION(BlueprintCallable, Category="Datasmith | Element")` — Get the recorded value for this property as a rotator. Returned value is meaningless if the property is not of rotator type.
- L885 _public prototype_ `void SetValueRotator(FRotator InValue);` — `UFUNCTION(BlueprintCallable, Category="Datasmith | Element")` — Set the recorded value for this capture
- L892 _public prototype_ `FColor GetValueColor();` — `UFUNCTION(BlueprintCallable, Category="Datasmith | Element")` — Get the recorded value for this property as a color. Returned value is meaningless if the property is not of color type.
- L896 _public prototype_ `void SetValueColor(FColor InValue);` — `UFUNCTION(BlueprintCallable, Category="Datasmith | Element")` — Set the recorded value for this capture
- L903 _public prototype_ `FLinearColor GetValueLinearColor();` — `UFUNCTION(BlueprintCallable, Category="Datasmith | Element")` — Get the recorded value for this property as a linear color. Returned value is meaningless if the property is not of linear color type.
- L907 _public prototype_ `void SetValueLinearColor(FLinearColor InValue);` — `UFUNCTION(BlueprintCallable, Category="Datasmith | Element")` — Set the recorded value for this capture
- L914 _public prototype_ `FVector GetValueVector();` — `UFUNCTION(BlueprintCallable, Category="Datasmith | Element")` — Get the recorded value for this property as a vector. Returned value is meaningless if the property is not of vector type.
- L918 _public prototype_ `void SetValueVector(FVector InValue);` — `UFUNCTION(BlueprintCallable, Category="Datasmith | Element")` — Set the recorded value for this capture
- L925 _public prototype_ `FQuat GetValueQuat();` — `UFUNCTION(BlueprintCallable, Category="Datasmith | Element")` — Get the recorded value for this property as a quat. Returned value is meaningless if the property is not of quat type.
- L929 _public prototype_ `void SetValueQuat(FQuat InValue);` — `UFUNCTION(BlueprintCallable, Category="Datasmith | Element")` — Set the recorded value for this capture
- L936 _public prototype_ `FVector4 GetValueVector4();` — `UFUNCTION(BlueprintCallable, Category="Datasmith | Element")` — Get the recorded value for this property as a vector4. Returned value is meaningless if the property is not of vector4 type.
- L940 _public prototype_ `void SetValueVector4(FVector4 InValue);` — `UFUNCTION(BlueprintCallable, Category="Datasmith | Element")` — Set the recorded value for this capture
- L947 _public prototype_ `FVector2D GetValueVector2D();` — `UFUNCTION(BlueprintCallable, Category="Datasmith | Element")` — Get the recorded value for this property as a vector2d. Returned value is meaningless if the property is not of vector2 type.
- L951 _public prototype_ `void SetValueVector2D(FVector2D InValue);` — `UFUNCTION(BlueprintCallable, Category="Datasmith | Element")` — Set the recorded value for this capture
- L958 _public prototype_ `FIntPoint GetValueIntPoint();` — `UFUNCTION(BlueprintCallable, Category="Datasmith | Element")` — Get the recorded value for this property as an int point. Returned value is meaningless if the property is not of int point type.
- L962 _public prototype_ `void SetValueIntPoint(FIntPoint InValue);` — `UFUNCTION(BlueprintCallable, Category="Datasmith | Element")` — Set the recorded value for this capture
- L965 _public function_ `TWeakPtr<IDatasmithPropertyCaptureElement> GetPropertyCaptureElement() const`
- L966 _public function_ `void SetPropertyCaptureElement(const TSharedPtr<IDatasmithPropertyCaptureElement>& InElement)`

#### class `UDatasmithObjectPropertyCaptureElement`  
`class UDatasmithObjectPropertyCaptureElement : public UDatasmithBasePropertyCaptureElement`  
_L973-989_
- reflection: `UCLASS()`
- inherits: `UDatasmithBasePropertyCaptureElement`
- desc: UDatasmithObjectPropertyCaptureElement
- L980 _public prototype_ `void SetRecordedObject(UDatasmithObjectElement* Object);` — `UFUNCTION(BlueprintCallable, Category="Datasmith | Element")` — Gets the category of this property capture
- L984 _public prototype_ `UDatasmithObjectElement* GetRecordedObject() const;` — `UFUNCTION(BlueprintCallable, Category="Datasmith | Element")` — Gets the category of this property capture
- L987 _public function_ `TWeakPtr<IDatasmithObjectPropertyCaptureElement> GetObjectPropertyCaptureElement() const`
- L988 _public function_ `void SetObjectPropertyCaptureElement(const TSharedPtr<IDatasmithObjectPropertyCaptureElement>& InElement)`

#### class `UDatasmithActorBindingElement`  
`class UDatasmithActorBindingElement : public UDatasmithObjectElement`  
_L995-1044_
- reflection: `UCLASS()`
- inherits: `UDatasmithObjectElement`
- desc: UDatasmithActorBindingElement
- L1002 _public prototype_ `void SetActor(UDatasmithActorElement* Actor);` — `UFUNCTION(BlueprintCallable, Category="Datasmith | Element")` — Sets the actor that this binding will try capturing
- L1006 _public prototype_ `UDatasmithActorElement* GetActor() const;` — `UFUNCTION(BlueprintCallable, Category="Datasmith | Element")` — Gets the actor that this binding will try capturing
- L1010 _public prototype_ `UDatasmithPropertyCaptureElement* CreatePropertyCapture();` — `UFUNCTION(BlueprintCallable, Category = "Datasmith | Scene")` — Create a new property capture and add it to this binding
- L1014 _public prototype_ `UDatasmithObjectPropertyCaptureElement* CreateObjectPropertyCapture();` — `UFUNCTION(BlueprintCallable, Category = "Datasmith | Scene")` — Create a new object property capture and add it to this binding
- L1018 _public prototype_ `void AddPropertyCapture(const UDatasmithBasePropertyCaptureElement* Prop);` — `UFUNCTION(BlueprintCallable, Category="Datasmith | Element")` — Adds an existing property capture to this binding
- L1022 _public prototype_ `int32 GetPropertyCapturesCount() const;` — `UFUNCTION(BlueprintCallable, Category="Datasmith | Element")` — Gets how many properties will be captured from the bound actor
- L1026 _public prototype_ `UDatasmithBasePropertyCaptureElement* GetPropertyCapture(int32 Index);` — `UFUNCTION(BlueprintCallable, Category="Datasmith | Element")` — Gets property that will be captured from the bound actor
- L1030 _public prototype_ `void RemovePropertyCapture(const UDatasmithBasePropertyCaptureElement* Prop);` — `UFUNCTION(BlueprintCallable, Category="Datasmith | Element")` — Removes one of the properties that will be captured from the bound actor
- L1033 _public function_ `TWeakPtr<IDatasmithActorBindingElement> GetActorBindingElement() const`
- L1034 _public function_ `void SetActorBindingElement(const TSharedPtr<IDatasmithActorBindingElement>& InElement)`
- L1037 _public prototype_ `virtual bool IsElementValid() const override;` — Is the Element still valid for the Datasmith Scene
- L1040 _protected function_ `virtual TWeakPtr<IDatasmithElement> GetIDatasmithElement() const override`
- L1043 _private member_ `TWeakPtr<IDatasmithActorBindingElement> DatasmithElement;`

#### class `UDatasmithVariantElement`  
`class UDatasmithVariantElement : public UDatasmithObjectElement`  
_L1050-1087_
- reflection: `UCLASS()`
- inherits: `UDatasmithObjectElement`
- desc: UDatasmithVariantElement
- L1057 _public prototype_ `UDatasmithActorBindingElement* CreateActorBinding();` — `UFUNCTION(BlueprintCallable, Category = "Datasmith | Scene")` — Create a new actor binding and add it to this variant
- L1061 _public prototype_ `void AddActorBinding(const UDatasmithActorBindingElement* Binding);` — `UFUNCTION(BlueprintCallable, Category="Datasmith | Element")` — Adds an existing actor binding to this variant
- L1065 _public prototype_ `int32 GetActorBindingsCount() const;` — `UFUNCTION(BlueprintCallable, Category="Datasmith | Element")` — Gets how many actor bindings are in this variant
- L1069 _public prototype_ `UDatasmithActorBindingElement* GetActorBinding(int32 Index);` — `UFUNCTION(BlueprintCallable, Category="Datasmith | Element")` — Gets an actor binding from this variant
- L1073 _public prototype_ `void RemoveActorBinding(const UDatasmithActorBindingElement* Binding);` — `UFUNCTION(BlueprintCallable, Category="Datasmith | Element")` — Removes an actor binding from this variant
- L1076 _public function_ `TWeakPtr<IDatasmithVariantElement> GetVariantElement() const`
- L1077 _public function_ `void SetVariantElement(const TSharedPtr<IDatasmithVariantElement>& InElement)`
- L1080 _public prototype_ `virtual bool IsElementValid() const override;` — Is the Element still valid for the Datasmith Scene
- L1083 _protected function_ `virtual TWeakPtr<IDatasmithElement> GetIDatasmithElement() const override`
- L1086 _private member_ `TWeakPtr<IDatasmithVariantElement> DatasmithElement;`

#### class `UDatasmithVariantSetElement`  
`class UDatasmithVariantSetElement : public UDatasmithObjectElement`  
_L1093-1130_
- reflection: `UCLASS()`
- inherits: `UDatasmithObjectElement`
- desc: UDatasmithVariantSetElement
- L1100 _public prototype_ `UDatasmithVariantElement* CreateVariant(FName InElementName);` — `UFUNCTION(BlueprintCallable, Category = "Datasmith | Scene")` — Create a new variant and add it to the parent variant set
- L1104 _public prototype_ `void AddVariant(const UDatasmithVariantElement* Variant);` — `UFUNCTION(BlueprintCallable, Category="Datasmith | Element")` — Adds an existing variant to this variant set
- L1108 _public prototype_ `int32 GetVariantsCount() const;` — `UFUNCTION(BlueprintCallable, Category="Datasmith | Element")` — Gets how many variants are in this variant set
- L1112 _public prototype_ `UDatasmithVariantElement* GetVariant(int32 Index);` — `UFUNCTION(BlueprintCallable, Category="Datasmith | Element")` — Gets a variant from this variant set
- L1116 _public prototype_ `void RemoveVariant(const UDatasmithVariantElement* Variant);` — `UFUNCTION(BlueprintCallable, Category="Datasmith | Element")` — Removes a variant from this variant set
- L1119 _public function_ `TWeakPtr<IDatasmithVariantSetElement> GetVariantSetElement() const`
- L1120 _public function_ `void SetVariantSetElement(const TSharedPtr<IDatasmithVariantSetElement>& InElement)`
- L1123 _public prototype_ `virtual bool IsElementValid() const override;` — Is the Element still valid for the Datasmith Scene
- L1126 _protected function_ `virtual TWeakPtr<IDatasmithElement> GetIDatasmithElement() const override`
- L1129 _private member_ `TWeakPtr<IDatasmithVariantSetElement> DatasmithElement;`

#### class `UDatasmithLevelVariantSetsElement`  
`class UDatasmithLevelVariantSetsElement : public UDatasmithObjectElement`  
_L1136-1173_
- reflection: `UCLASS()`
- inherits: `UDatasmithObjectElement`
- desc: UDatasmithLevelVariantSetsElement
- L1143 _public prototype_ `UDatasmithVariantSetElement* CreateVariantSet(FName InElementName);` — `UFUNCTION(BlueprintCallable, Category = "Datasmith | Scene")` — Create a new variant set and add it to the parent level variant sets
- L1147 _public prototype_ `void AddVariantSet(const UDatasmithVariantSetElement* VariantSet);` — `UFUNCTION(BlueprintCallable, Category="Datasmith | Element")` — Adds an existing variant set to this level variant sets
- L1151 _public prototype_ `int32 GetVariantSetsCount() const;` — `UFUNCTION(BlueprintCallable, Category="Datasmith | Element")` — Gets how many variant sets are in this level variant sets
- L1155 _public prototype_ `UDatasmithVariantSetElement* GetVariantSet(int32 Index);` — `UFUNCTION(BlueprintCallable, Category="Datasmith | Element")` — Gets a variant set from this level variant sets
- L1159 _public prototype_ `void RemoveVariantSet(const UDatasmithVariantSetElement* VariantSet);` — `UFUNCTION(BlueprintCallable, Category="Datasmith | Element")` — Removes a variant set from this level variant sets
- L1162 _public function_ `TWeakPtr<IDatasmithLevelVariantSetsElement> GetLevelVariantSetsElement() const`
- L1163 _public function_ `void SetLevelVariantSetsElement(const TSharedPtr<IDatasmithLevelVariantSetsElement>& InElement)`
- L1166 _public prototype_ `virtual bool IsElementValid() const override;` — Is the Element still valid for the Datasmith Scene
- L1169 _protected function_ `virtual TWeakPtr<IDatasmithElement> GetIDatasmithElement() const override`
- L1172 _private member_ `TWeakPtr<IDatasmithLevelVariantSetsElement> DatasmithElement;`

### `Plugins/Enterprise/DatasmithImporter/Source/DatasmithImporter/Public/ObjectElements/DatasmithUSceneElement.h` (Public)


#### class `UDatasmithSceneElementBase`  
`class UDatasmithSceneElementBase : public UObject`  
_L14-339_
- reflection: `UCLASS(BlueprintType, Transient)`
- inherits: `UObject`
- L33 _public prototype_ `FString GetHost() const;` — `UFUNCTION(BlueprintCallable, Category = "Datasmith | Scene")` — Sets the name of the host application which created the scene
- L37 _public prototype_ `FString GetExporterVersion() const;` — `UFUNCTION(BlueprintCallable, Category = "Datasmith | Scene")` — Returns the Datasmith version used to export the scene
- L41 _public prototype_ `FString GetVendor() const;` — `UFUNCTION(BlueprintCallable, Category = "Datasmith | Scene")` — Returns the vendor name of the application used to export the scene
- L45 _public prototype_ `FString GetProductName() const;` — `UFUNCTION(BlueprintCallable, Category = "Datasmith | Scene")` — Returns the product name of the application used to export the scene
- L49 _public prototype_ `FString GetProductVersion() const;` — `UFUNCTION(BlueprintCallable, Category = "Datasmith | Scene")` — Returns the product version of the application used to export the scene
- L53 _public prototype_ `FString GetUserID() const;` — `UFUNCTION(BlueprintCallable, Category = "Datasmith | Scene")` — Returns the user identifier who exported the scene
- L57 _public prototype_ `FString GetUserOS() const;` — `UFUNCTION(BlueprintCallable, Category = "Datasmith | Scene")` — Returns the OS name used by user who exported the scene
- L61 _public prototype_ `int32 GetExportDuration() const;` — `UFUNCTION(BlueprintCallable, Category = "Datasmith | Scene")` — Returns the time taken to export the scene
- L69 _public prototype_ `bool GetUsePhysicalSky() const;` — `UFUNCTION(BlueprintCallable, Category = "Datasmith | Scene")` — Physical Sky could be generated in a large amount of modes, like material, lights etc that's why it has been added as static, just enable it and it is done. Notice that if a HDRI environment is used this gets disabled.
- L74 _public prototype_ `UDatasmithMeshElement* CreateMesh(FName InElementName);` — `UFUNCTION(BlueprintCallable, Category = "Datasmith | Scene")` — Create a new Mesh and add it to the Datasmith scene
- L78 _public prototype_ `TArray<UDatasmithMeshElement*> GetMeshes();` — `UFUNCTION(BlueprintCallable, Category = "Datasmith | Scene")` — Create an array with all the Mesh in the Datasmith scene. Use CreateMesh -or- RemoveMesh to modify the Datasmith scene.
- L85 _public prototype_ `UDatasmithMeshElement* GetMeshByPathName(const FString& MeshPathName);` — `UFUNCTION(BlueprintCallable, Category = "Datasmith | Scene")` — Find in the Datasmith scene the MeshElement that correspond to the mesh path name. The function will return an invalid MeshElement, if the MeshPathName is empty or if it's not relative to the Datasmith scene or if it's not found.
- L89 _public prototype_ `void RemoveMesh(UDatasmithMeshElement* InMesh);` — `UFUNCTION(BlueprintCallable, Category = "Datasmith | Scene")` — Remove the mesh from the Datasmith scene
- L94 _public prototype_ `UDatasmithMeshActorElement* CreateMeshActor(FName InElementName);` — `UFUNCTION(BlueprintCallable, Category = "Datasmith | Scene")` — Create a new MeshActor and add it to the Datasmith scene
- L101 _public prototype_ `TArray<UDatasmithMeshActorElement*> GetMeshActors();` — `UFUNCTION(BlueprintCallable, Category = "Datasmith | Scene")` — Create an array with the MeshActor in the Datasmith scene that are at the root level of the hierarchy. Use CreateMeshActor -or- RemoveMeshActor to modify the Datasmith scene.
- L108 _public prototype_ `TArray<UDatasmithMeshActorElement*> GetAllMeshActors();` — `UFUNCTION(BlueprintCallable, Category = "Datasmith | Scene")` — Create an array with all the MeshActor in the Datasmith scene without taking into account the hierarchy. Use CreateMeshActor -or- RemoveMeshActor to modify the Datasmith scene.
- L112 _public prototype_ `void RemoveMeshActor(UDatasmithMeshActorElement* InMeshActor, EDatasmithActorRemovalRule RemoveRule = EDatasmithActorRemovalRule::RemoveChildren);` — `UFUNCTION(BlueprintCallable, Category = "Datasmith | Scene")` — Remove the MeshActor from the Datasmith scene
- L120 _public prototype_ `TArray<UDatasmithLightActorElement*> GetLightActors();` — `UFUNCTION(BlueprintCallable, Category = "Datasmith | Scene")` — Create an array with the LightActor in the Datasmith scene that are at the root level of the hierarchy. Use RemoveLightActor to modify the Datasmith scene.
- L127 _public prototype_ `TArray<UDatasmithLightActorElement*> GetAllLightActors();` — `UFUNCTION(BlueprintCallable, Category = "Datasmith | Scene")` — Create an array with all the LightActor in the Datasmith scene without taking into account the hierarchy. Use RemoveLightActor to modify the Datasmith scene.
- L131 _public prototype_ `void RemoveLightActor(UDatasmithLightActorElement* InLightActor, EDatasmithActorRemovalRule RemoveRule = EDatasmithActorRemovalRule::RemoveChildren);` — `UFUNCTION(BlueprintCallable, Category = "Datasmith | Scene")` — Remove the LightActor from the Datasmith scene
- L136 _public prototype_ `UDatasmithCameraActorElement* CreateCameraActor(FName InElementName);` — `UFUNCTION(BlueprintCallable, Category = "Datasmith | Scene")` — Create a new Camera Actor and add it to the Datasmith scene
- L143 _public prototype_ `TArray<UDatasmithCameraActorElement*> GetCameraActors();` — `UFUNCTION(BlueprintCallable, Category = "Datasmith | Scene")` — Create an array with the CameraActor in the Datasmith scene that are at the root level of the hierarchy. Use CreateCameraActor -or- RemoveCameraActor to modify the Datasmith scene.
- L150 _public prototype_ `TArray<UDatasmithCameraActorElement*> GetAllCameraActors();` — `UFUNCTION(BlueprintCallable, Category = "Datasmith | Scene")` — Create an array with all the CameraActor in the Datasmith scene without taking into account the hierarchy. Use CreateCameraActor -or- RemoveCameraActor to modify the Datasmith scene.
- L154 _public prototype_ `void RemoveCameraActor(UDatasmithCameraActorElement* InMeshActor, EDatasmithActorRemovalRule RemoveRule = EDatasmithActorRemovalRule::RemoveChildren);` — `UFUNCTION(BlueprintCallable, Category = "Datasmith | Scene")` — Remove the Camera actor from the Datasmith scene
- L162 _public prototype_ `TArray<UDatasmithCustomActorElement*> GetCustomActors();` — `UFUNCTION(BlueprintCallable, Category = "Datasmith | Scene")` — Create an array with the CustomActor in the Datasmith scene that are at the root level of the hierarchy. Use RemoveCustomActor to modify the Datasmith scene.
- L169 _public prototype_ `TArray<UDatasmithCustomActorElement*> GetAllCustomActors();` — `UFUNCTION(BlueprintCallable, Category = "Datasmith | Scene")` — Create an array with all the CustomActor in the Datasmith scene without taking into account the hierarchy. Use RemoveCustomActor to modify the Datasmith scene.
- L173 _public prototype_ `void RemoveCustomActor(UDatasmithCustomActorElement* InCustomActor, EDatasmithActorRemovalRule RemoveRule = EDatasmithActorRemovalRule::RemoveChildren);` — `UFUNCTION(BlueprintCallable, Category = "Datasmith | Scene")` — Remove the LightActor from the Datasmith scene
- L178 _public prototype_ `UDatasmithTextureElement* CreateTexture(FName InElementName);` — `UFUNCTION(BlueprintCallable, Category = "Datasmith | Scene")` — Create a new Texture and add it to the Datasmith scene
- L182 _public prototype_ `TArray<UDatasmithTextureElement*> GetTextures();` — `UFUNCTION(BlueprintCallable, Category = "Datasmith | Scene")` — Create an array with all the Textures in the Datasmith scene. Call CreateTexture -or- RemoveTexture to modify the Datasmith scene.
- L186 _public prototype_ `void RemoveTexture(UDatasmithTextureElement* InElement);` — `UFUNCTION(BlueprintCallable, Category = "Datasmith | Scene")` — Remove the Texture from the Datasmith scene
- L191 _public prototype_ `TArray<UDatasmithBaseMaterialElement*> GetAllMaterials();` — `UFUNCTION(BlueprintCallable, Category = "Datasmith | Scene")` — Create an array with all the Materials in the Datasmith scene
- L195 _public prototype_ `void RemoveMaterial(UDatasmithBaseMaterialElement* InElement);` — `UFUNCTION(BlueprintCallable, Category = "Datasmith | Scene")` — Remove the material from the Datasmith scene
- L200 _public prototype_ `UDatasmithPostProcessElement* GetPostProcess();` — `UFUNCTION(BlueprintCallable, Category = "Datasmith | Scene")` — Get the Postprocess used by the scene. Can be invalid.
- L203 _private prototype_ `TArray<UDatasmithMetaDataElement*> GetMetaData();`
- L208 _public prototype_ `UDatasmithMetaDataElement* GetMetaDataForObject(UDatasmithObjectElement* Object);` — `UFUNCTION(BlueprintCallable, Category = "Datasmith | Scene", meta = (ScriptName = "GetMetadataForObject", DisplayName = "Get Metadata For Object"))`
- L217 _public prototype_ `FString GetMetaDataValueForKey(UDatasmithObjectElement* Object, const FString& Key);` — `UFUNCTION(BlueprintCallable, Category = "Datasmith | Scene", meta = (ScriptName = "GetMetadataValueForKey", DisplayName = "Get Metadata Value For Key"))` — Get the value associated with the given key of the metadata element associated with the given object. @param	Object	The Object that is associated with the metadata element of interest. @param	Key		The key to find in the metadata element. @return			The string value associated with the given key
- L227 _public prototype_ `void GetMetaDataKeysAndValuesForValue(UDatasmithObjectElement* Object, const FString& StringToMatch, TArray<FString>& OutKeys, TArray<FString>& OutValues);` — `UFUNCTION(BlueprintCallable, Category = "Datasmith | Scene", meta = (ScriptName = "GetMetadataKeysAndValuesForValue", DisplayName = "Get Metadata Keys And Values For Value"))` — Get the keys and values for which the associated value contains the string to match for the metadata element associated with the given object. @param	Object			The Object that is associated with the metadata element of interest. @param	StringToMatch	The string to match in the values. @param	OutKeys			Output array of keys for which the associated values contain the string to match. @param	OutValues		Output array of values associated to the keys.
- L235 _public prototype_ `void GetAllMetaData(TSubclassOf<UDatasmithObjectElement> ObjectClass, TArray<UDatasmithMetaDataElement*>& OutMetadatas);` — `UFUNCTION(BlueprintCallable, Category = "Datasmith | Scene", meta = (ScriptName = "GetAllMetadata", DisplayName = "Get All Metadata"))` — Find all metadata elements associated with objects of the given type. @param	ObjectClass		Class of the object on which to filter, if specificed; otherwise there's no filtering @param	OutMetadatas	Output array of metadata elements.
- L245 _public prototype_ `void GetAllObjectsAndValuesForKey(const FString& Key, TSubclassOf<UDatasmithObjectElement> ObjectClass, TArray<UDatasmithObjectElement*>& OutObjects, TArray<FString>& OutValues);` — `UFUNCTION(BlueprintCallable, Category = "Datasmith | Scene", meta = (DeterminesOutputType = "ObjectClass", DynamicOutputParam = "OutObjects"))` — Find all objects of the given type that have a metadata element that contains the given key and their associated values. @param	Key			The key to find in the metadata element. @param	ObjectClass	Class of the object on which to filter, if specificed; otherwise there's no filtering @param	OutObjects	Output array of objects for which the metadata element contains the given key. @param	OutValues	Output array of values associated with each object in OutObjects.
- L250 _public prototype_ `UDatasmithLevelVariantSetsElement* CreateLevelVariantSets(FName InElementName);` — `UFUNCTION(BlueprintCallable, Category = "Datasmith | Scene")` — Create a new level variant sets and add it to the Datasmith scene
- L257 _public prototype_ `TArray<UDatasmithLevelVariantSetsElement*> GetAllLevelVariantSets();` — `UFUNCTION(BlueprintCallable, Category = "Datasmith | Scene")` — Create an array with all the level variants sets from the Datasmith scene Use CreateLevelVariantSets -or- RemoveLevelVariantSets to modify the Datasmith scene.
- L261 _public prototype_ `void RemoveLevelVariantSets(UDatasmithLevelVariantSetsElement* InElement);` — `UFUNCTION(BlueprintCallable, Category = "Datasmith | Scene")` — Remove the level variant sets from the Datasmith scene
- L266 _public prototype_ `void AttachActor(UDatasmithActorElement* NewParent, UDatasmithActorElement* Child, EDatasmithActorAttachmentRule AttachmentRule);` — `UFUNCTION(BlueprintCallable, Category = "Datasmith | Scene")` — Attach the actor to its new parent. Detach the actor if it was already attached.
- L270 _public prototype_ `void AttachActorToSceneRoot(UDatasmithActorElement* NewParent, EDatasmithActorAttachmentRule AttachmentRule);` — `UFUNCTION(BlueprintCallable, Category = "Datasmith | Scene")` — Attach the actor to the scene root. Detach the actor if it was already attached.
- L273 _public prototype_ `void SetDatasmithSceneElement(TSharedPtr<class IDatasmithScene> InElement);`
- L274 _public function_ `TSharedPtr<class IDatasmithScene> GetSceneElement()`
- L276 _public prototype_ `bool IsElementValid(const TWeakPtr<IDatasmithBaseMaterialElement>& Element) const;`
- L277 _public prototype_ `bool IsElementValid(const TWeakPtr<IDatasmithMaterialIDElement>& Element) const;`
- L278 _public prototype_ `bool IsElementValid(const TWeakPtr<IDatasmithMeshElement>& Element) const;`
- L279 _public prototype_ `bool IsElementValid(const TWeakPtr<IDatasmithMeshActorElement>& Element) const;`
- L280 _public prototype_ `bool IsElementValid(const TWeakPtr<IDatasmithLightActorElement>& Element) const;`
- L281 _public prototype_ `bool IsElementValid(const TWeakPtr<IDatasmithCameraActorElement>& Element) const;`
- L282 _public prototype_ `bool IsElementValid(const TWeakPtr<IDatasmithTextureElement>& Element) const;`
- L283 _public prototype_ `bool IsElementValid(const TWeakPtr<IDatasmithPostProcessElement>& Element) const;`
- L284 _public prototype_ `bool IsElementValid(const TWeakPtr<IDatasmithMetaDataElement>& Element) const;`
- L285 _public prototype_ `bool IsElementValid(const TWeakPtr<IDatasmithCustomActorElement>& Element) const;`
- L286 _public prototype_ `bool IsElementValid(const TWeakPtr<IDatasmithBasePropertyCaptureElement>& Element) const;`
- L287 _public prototype_ `bool IsElementValid(const TWeakPtr<IDatasmithActorBindingElement>& Element) const;`
- L288 _public prototype_ `bool IsElementValid(const TWeakPtr<IDatasmithVariantElement>& Element) const;`
- L289 _public prototype_ `bool IsElementValid(const TWeakPtr<IDatasmithVariantSetElement>& Element) const;`
- L290 _public prototype_ `bool IsElementValid(const TWeakPtr<IDatasmithLevelVariantSetsElement>& Element) const;`
- L292 _public prototype_ `UDatasmithActorElement* FindOrAddActorElement(const TSharedPtr<IDatasmithActorElement>& InElement);`
- L294 _public prototype_ `UDatasmithObjectElement* FindOrAddElement(const TSharedPtr<IDatasmithElement>& InElement);`
- L295 _public prototype_ `UDatasmithBaseMaterialElement* FindOrAddElement(const TSharedPtr<IDatasmithBaseMaterialElement>& InElement);`
- L296 _public prototype_ `UDatasmithMaterialIDElement* FindOrAddElement(const TSharedPtr<IDatasmithMaterialIDElement>& InElement);`
- L297 _public prototype_ `UDatasmithMeshElement* FindOrAddElement(const TSharedPtr<IDatasmithMeshElement>& InElement);`
- L298 _public prototype_ `UDatasmithMeshActorElement* FindOrAddElement(const TSharedPtr<IDatasmithMeshActorElement>& InElement);`
- L299 _public prototype_ `UDatasmithLightActorElement* FindOrAddElement(const TSharedPtr<IDatasmithLightActorElement>& InElement);`
- L300 _public prototype_ `UDatasmithCameraActorElement* FindOrAddElement(const TSharedPtr<IDatasmithCameraActorElement>& InElement);`
- L301 _public prototype_ `UDatasmithPostProcessElement* FindOrAddElement(const TSharedPtr<IDatasmithPostProcessElement>& InElement);`
- L302 _public prototype_ `UDatasmithTextureElement* FindOrAddElement(const TSharedPtr<IDatasmithTextureElement>& InElement);`
- L303 _public prototype_ `UDatasmithMetaDataElement* FindOrAddElement(const TSharedPtr<IDatasmithMetaDataElement>& InElement);`
- L304 _public prototype_ `UDatasmithCustomActorElement* FindOrAddElement(const TSharedPtr<IDatasmithCustomActorElement>& InElement);`
- L305 _public prototype_ `UDatasmithPropertyCaptureElement* FindOrAddElement(const TSharedPtr<IDatasmithPropertyCaptureElement>& InElement);`
- L306 _public prototype_ `UDatasmithObjectPropertyCaptureElement* FindOrAddElement(const TSharedPtr<IDatasmithObjectPropertyCaptureElement>& InElement);`
- L307 _public prototype_ `UDatasmithActorBindingElement* FindOrAddElement(const TSharedPtr<IDatasmithActorBindingElement>& InElement);`
- L308 _public prototype_ `UDatasmithVariantElement* FindOrAddElement(const TSharedPtr<IDatasmithVariantElement>& InElement);`
- L309 _public prototype_ `UDatasmithVariantSetElement* FindOrAddElement(const TSharedPtr<IDatasmithVariantSetElement>& InElement);`
- L310 _public prototype_ `UDatasmithLevelVariantSetsElement* FindOrAddElement(const TSharedPtr<IDatasmithLevelVariantSetsElement>& InElement);`
- L313 _protected prototype_ `virtual void Reset();`
- L316 _private prototype_ `void ExternalAddReferencedObjects(FReferenceCollector& Collector);`
- L318 _private member_ `FDatasmithSceneCollector DatasmithSceneCollector;`
- L321 _protected member_ `TSharedPtr<class IDatasmithScene> SceneElement;`
- L323 _protected member_ `TMap<TWeakPtr<IDatasmithBaseMaterialElement>, TObjectPtr<UDatasmithBaseMaterialElement>> Materials;`
- L324 _protected member_ `TMap<TWeakPtr<IDatasmithMaterialIDElement>, TObjectPtr<UDatasmithMaterialIDElement>> MaterialIDs;`
- L325 _protected member_ `TMap<TWeakPtr<IDatasmithMeshElement>, TObjectPtr<UDatasmithMeshElement>> Meshes;`
- L326 _protected member_ `TMap<TWeakPtr<IDatasmithMeshActorElement>, TObjectPtr<UDatasmithMeshActorElement>> MeshActors;`
- L327 _protected member_ `TMap<TWeakPtr<IDatasmithLightActorElement>, TObjectPtr<UDatasmithLightActorElement>> LightActors;`
- L328 _protected member_ `TMap<TWeakPtr<IDatasmithCameraActorElement>, TObjectPtr<UDatasmithCameraActorElement>> CameraActors;`
- L329 _protected member_ `TMap<TWeakPtr<IDatasmithPostProcessElement>, TObjectPtr<UDatasmithPostProcessElement>> PostProcesses;`
- L330 _protected member_ `TMap<TWeakPtr<IDatasmithTextureElement>, TObjectPtr<UDatasmithTextureElement>> Textures;`
- L331 _protected member_ `TMap<TWeakPtr<IDatasmithMetaDataElement>, UDatasmithMetaDataElement*> MetaData;`
- L332 _protected member_ `TMap<TWeakPtr<IDatasmithCustomActorElement>, UDatasmithCustomActorElement*> CustomActors;`
- L333 _protected member_ `TMap<TWeakPtr<IDatasmithPropertyCaptureElement>, TObjectPtr<UDatasmithPropertyCaptureElement>> PropertyCaptures;`
- L334 _protected member_ `TMap<TWeakPtr<IDatasmithObjectPropertyCaptureElement>, TObjectPtr<UDatasmithObjectPropertyCaptureElement>> ObjectPropertyCaptures;`
- L335 _protected member_ `TMap<TWeakPtr<IDatasmithActorBindingElement>, TObjectPtr<UDatasmithActorBindingElement>> ActorBindings;`
- L336 _protected member_ `TMap<TWeakPtr<IDatasmithVariantElement>, TObjectPtr<UDatasmithVariantElement>> Variants;`
- L337 _protected member_ `TMap<TWeakPtr<IDatasmithVariantSetElement>, TObjectPtr<UDatasmithVariantSetElement>> VariantSets;`
- L338 _protected member_ `TMap<TWeakPtr<IDatasmithLevelVariantSetsElement>, TObjectPtr<UDatasmithLevelVariantSetsElement>> LevelVariantSets;`

#### struct `UDatasmithSceneElementBase::FDatasmithSceneCollector`  
`struct FDatasmithSceneCollector : public FGCObject`  
_L18-27_
- inherits: `FGCObject`
- L20 _public prototype_ `FDatasmithSceneCollector();`
- L21 _public member_ `UDatasmithSceneElementBase* DatasmithSceneElement;`
- L22 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;`
- L23 _public function_ `virtual FString GetReferencerName() const override`

### `Plugins/Enterprise/DatasmithImporter/Source/DatasmithImporter/Public/UI/DatasmithDisplayHelper.h` (Public)


#### struct `Datasmith::FDisplayParameters`  
`struct FDisplayParameters`  
_L11-24_
- L13 _public member_ `bool bAskForSameOption = false;`
- L14 _public member_ `FText WindowTitle;`
- L15 _public member_ `FText FileLabel;`
- L16 _public member_ `FText FileTooltip;` — eg. file full path
- L17 _public member_ `FText PackageLabel;`
- L18 _public member_ `FText ProceedButtonLabel;`
- L19 _public member_ `FText ProceedButtonTooltip;`
- L20 _public member_ `FText CancelButtonLabel;`
- L21 _public member_ `FText CancelButtonTooltip;`
- L22 _public member_ `float MinDetailHeight = 0;`
- L23 _public member_ `float MinDetailWidth = 0;`

#### struct `Datasmith::FDisplayResult`  
`struct FDisplayResult`  
_L26-30_
- L28 _public member_ `bool bValidated = true;`
- L29 _public member_ `bool bUseSameOption = false;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace Datasmith`
- L38 _prototype_ `FDisplayResult DisplayOptions(const TArray<TStrongObjectPtr<UObject>>& Options, const FDisplayParameters& Parameters={});` (scope `Datasmith`) — Display custom objects as options for user inputs @param Options Objects to be displayed for user inputs @return bool   true if workflow should continue, false on cancellation
- L39 _prototype_ `FDisplayResult DisplayOptions(const TArray<UObject*>& Options, const FDisplayParameters& Parameters={});` (scope `Datasmith`)
- L40 _prototype_ `FDisplayResult DisplayOptions(const TStrongObjectPtr<UObject>& Options, const FDisplayParameters& Parameters={});` (scope `Datasmith`)

### `Plugins/Enterprise/DatasmithImporter/Source/DatasmithImporter/Public/UI/DatasmithImportOptionsWindow.h` (Public)


#### class `SDatasmithOptionsWindow`  
`class SDatasmithOptionsWindow : public SCompoundWidget`  
_L13-98_
- inherits: `SCompoundWidget`
- L16 _public function_ `SLATE_BEGIN_ARGS(SDatasmithOptionsWindow) : _FileFormatVersion(0.f) , _bAskForSameOption(false)`
- L38 _public prototype_ `void Construct(const FArguments& InArgs);`
- L40 _public function_ `virtual bool SupportsKeyboardFocus() const override`
- L42 _public function_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override`
- L52 _public function_ `bool ShouldImport() const`
- L57 _public function_ `bool UseSameOptions() const`
- L62 _public function_ `static const FString& GetDocumentationURL()`
- L65 _private function_ `FReply OnProceed()`
- L75 _private function_ `FReply OnCancel()`
- L86 _private prototype_ `FReply OnHelp(const FGeometry& SenderGeometry, const FPointerEvent& MouseEvent);`
- L88 _private prototype_ `void OnSameOptionToggle(ECheckBoxState InCheckState);`
- L90 _private prototype_ `TSharedRef< class SCompoundWidget > ConstructWarningWidget( float FileVersion, FText FileSDKVersion );`
- L93 _private member_ `TArray<UObject*> ImportOptions;`
- L94 _private member_ `TWeakPtr< SWindow > Window;`
- L95 _private member_ `bool bShouldProceed;`
- L96 _private member_ `bool bUseSameOptions;`
- L97 _private member_ `static FString DocumentationURL;`

### `Plugins/Enterprise/DatasmithImporter/Source/DatasmithImporter/Public/UI/DatasmithStyle.h` (Public)


#### class `FDatasmithStyle`  
`class FDatasmithStyle`  
_L10-25_
- desc: Manages the style that provides resources for Datasmith plugins widgets.
- L13 _public prototype_ `static void Initialize();`
- L14 _public prototype_ `static void Shutdown();`
- L15 _public prototype_ `static const ISlateStyle& Get();`
- L16 _public prototype_ `static FName GetStyleSetName();`
- L17 _public prototype_ `static FName GetContextName();`
- L20 _public prototype_ `static void SetIcon(const FString& StyleName, const FString& ResourcePath);` — Adds an icon (.png in the given ResourcePath) with the given style name to this style set
- L23 _private prototype_ `static TUniquePtr< class FSlateStyleSet > Create();`
- L24 _private member_ `static TUniquePtr< class FSlateStyleSet > DatasmithStyleInstance;`

### `Plugins/Enterprise/DatasmithImporter/Source/DatasmithImporter/Public/UVTools/UVGenerationFlattenMapping.h` (Public)


#### class `UUVGenerationFlattenMapping`  
`class UUVGenerationFlattenMapping : public UBlueprintFunctionLibrary`  
_L14-27_
- reflection: `UCLASS()`
- inherits: `UBlueprintFunctionLibrary`
- L20 _public prototype_ `static void GenerateFlattenMappingUVs(UStaticMesh* InStaticMesh, int32 UVChannel, float AngleThreshold = 66.f);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | StaticMesh", meta = (DisplayName = "Generate Unwrapped UVs"))`
- L22 _public prototype_ `static void GenerateUVs(FMeshDescription& InMesh, int32 UVChannel, bool bRemoveDegenerate, float AngleThreshold = 66.f);`
- L26 _private prototype_ `static TArray<int32> GetOverlappingCornersRemapping(const FMeshDescription& InMeshDescription, bool bRemoveDegenerates);`

### `Plugins/Enterprise/DatasmithImporter/Source/DatasmithImporter/Public/UVTools/UVGenerationUtils.h` (Public)


#### class `UVGenerationUtils`  
`class UVGenerationUtils`  
_L9-25_
- L16 _public prototype_ `static int32 GetNextOpenUVChannel(UStaticMesh* StaticMesh, int32 LODIndex);` — Returns the index of the next open UV channel, existing channels filled with default values are considered open. If no open channel is found, returns -1.
- L24 _public prototype_ `static void SetupGeneratedLightmapUVResolution(UStaticMesh* StaticMesh, int32 LODIndex);` — Setup the a good lightmap minimal resolution for the given static mesh LOD in its build settings. @param StaticMesh	The StaticMesh being set up @param LODIndex		The LOD being set up.

### `Plugins/Enterprise/DatasmithImporter/Source/DatasmithImporter/Public/Utility/DatasmithImporterUtils.h` (Public)


#### class `FDatasmithImporterUtils`  
`class FDatasmithImporterUtils`  
_L24-240_
- L37 _public prototype_ `static TSharedPtr< IDatasmithScene > LoadDatasmithScene( UDatasmithScene* DatasmithSceneAsset );` — Loads an IDatasmithScene from a UDatasmithScene
- L40 _public prototype_ `static void SaveDatasmithScene( TSharedRef< IDatasmithScene > DatasmithScene, UDatasmithScene* DatasmithSceneAsset );` — Saves an IDatasmithScene into a UDatasmithScene
- L43 _public prototype_ `static ADatasmithSceneActor* CreateImportSceneActor( FDatasmithImportContext& ImportContext, FTransform WorldTransform );` — Spawns a ADatasmithSceneActor and adds it to the ImportContext
- L50 _public prototype_ `static TArray< ADatasmithSceneActor* > FindSceneActors( UWorld* World, UDatasmithScene* DatasmithScene );` — Finds all the ADatasmithSceneActor in the world that refers to the given scene @param World			    Scope of the search @param DatasmithScene    SceneActor must reference this scene to be included
- L59 _public prototype_ `static void DeleteNonImportedDatasmithElementFromSceneActor(ADatasmithSceneActor& SourceSceneActor, ADatasmithSceneActor& DestinationSceneActor, const TSet< FName >& IgnoredDatasmithElements);` — Delete non imported datasmith elements (actors and components) from a Datasmith Scene Actor hierarchy @param SourceSceneActor           The scene on which the actors where imported @param DestinationSceneActor      The scene on which the actors will be deleted @param IgnoredDatasmithElements   The Datasmith actors that shouldn't be deleted if they aren't imported
- L66 _public prototype_ `static void DeleteActor( AActor& Actor );` — Delete an actor Remove it from the it's level, mark it pending kill and move it the transient package to avoid any potential name collision @param Actor The actor to delete
- L74 _public prototype_ `template< typename ObjectType > static ObjectType* FindAsset( const FDatasmithAssetsImportContext& AssetsContext, const TCHAR* ObjectPathName );` — Finds a UStaticMesh, UTexture or UMaterialInterface. Relative paths are resolved based on the AssetsContext. Absolute paths are sent through FDatasmithImporterUtils::FindObject.
- L85 _public prototype_ `template< class ObjectType > inline static ObjectType* FindObject( const UPackage* ParentPackage, const FString& ObjectName );` — Find an object with a given name in a package Use FSoftObjectPath to perform the search Load the package /ParentPackage/ObjectName if it exists and is not in memory yet @param	ParentPackage				Parent package to look in @param	ObjectName					Name of object to look for
- L93 _public prototype_ `static void AddUniqueLayersToWorld( UWorld* World, const TSet< FName >& LayerNames );` — Add a layer to the world if there is no other layer with the same name @param World			The world to which the layers will be added @param LayerNames	The name of the layers to be added
- L102 _public prototype_ `static int32 GetAssetNameMaxCharCount(const UPackage* ParentPackage);` — Try to compute a char budget for asset names, including FNames constraints, OS constraints, parent package, and user defined limitation. @param ParentPackage destination of the asset (Package path consume a part of the budget) @return An estimation of the budget for asset names
- L112 _public prototype_ `template< class ObjectType > static bool CanCreateAsset(const UPackage* Package, const FString& AssetName, FText& OutFailReason);` — @param Package			Package to create the asset in @param AssetName			The name of the asset to create @param OutFailReason		Text containing explanation about failure Given a package, a name and a class, check if an existing asset with a different class would not prevent the creation of such asset. A special report is done for object redirector
- L122 _public function_ `template< class ObjectType > static bool CanCreateAsset(const FString& AssetPathName, FText& OutFailReason)` — @param AssetPathName		Full path name of the asset to create @param OutFailReason		Text containing explanation about failure Returns true if the asset can be safely created Given a path and a class, check if an existing asset with a different class would not prevent the creation of such asset. A special report is done for object redirector
- L135 _public prototype_ `static bool CanCreateAsset(const FString& AssetPathName, const UClass* AssetClass, FText& OutFailReason);` — @param AssetPathName		Full path name of the asset to create @param AssetClass		Class of the asset to create @param OutFailReason		Text containing explanation about failure Returns true if the asset can be safely created Given a path and a class, check if an existing asset with a different class would not prevent the creation of such asset. A special report is done for object redirector
- L144 _public prototype_ `static EAssetCreationStatus CanCreateAsset(const FString& AssetPathName, const UClass* AssetClass);` — @param AssetPathName		Full path name of the asset to create @param AssetClass		Class of the asset to create Returns a state from the creation enumeration, EAssetCreationStatus. Given a path and a class, check if an existing asset with a different class would not prevent the creation of such asset.
- L151 _public function_ `template< class ObjectType > static EAssetCreationStatus CanCreateAsset(const FString& AssetPathName)` — @param AssetPathName		Full path name of the asset to create Calls CanCreateAsset(const FString&, const UClass*) with the instantiating class
- L159 _public prototype_ `static UDatasmithScene* FindDatasmithSceneForAsset( UObject* Asset );` — Finds the UDatasmithScene for which the Asset belongs to.
- L161 _public prototype_ `static FName GetDatasmithElementId( UObject* Object );`
- L162 _public prototype_ `static FString GetDatasmithElementIdString( UObject* Object );`
- L169 _public prototype_ `static void FillSceneElement( TSharedPtr< IDatasmithScene >& SceneElement, const TArray<AActor*>& RootActors );` — Converts AActor objects into DatasmithActorElement objects and add them to a DatasmithScene @param SceneElement		DatasmithScene to populate @param RootActors		Array of root actors to convert and add to the DatasmithScene
- L172 _public typedef_ `using FFunctionAndMaterialsThatUseIt = TPair< TSharedPtr< IDatasmithUEPbrMaterialElement >, TArray< TSharedPtr< IDatasmithUEPbrMaterialElement > > >;`
- L181 _public prototype_ `static TArray< FFunctionAndMaterialsThatUseIt > GetOrderedListOfMaterialsReferencedByMaterials(TSharedPtr< IDatasmithScene >& SceneElement);` — Finds all materials that are referenced by other materials in the scene and returns a list ordered by dependencies, making sure that materials referencing other materials in the list will come after. The list also include the direct parents (materials or functions) that are using the functions. @param SceneElement		DatasmithScene holding the materials.
- L218 _public prototype_ `static UObject* StaticDuplicateObject(UObject* SourceObject, UObject* Outer, const FName Name = NAME_None);` — Convenience function duplicating an object specifically optimized for datasmith use cases @param SourceObject the object being copied @param Outer the outer to use for the object @param Name the optional name of the object @return the copied object or null if it failed for some reason
- L231 _public prototype_ `static UStaticMesh* DuplicateStaticMesh(UStaticMesh* SourceStaticMesh, UObject* Outer, const FName Name = NAME_None, bool bIgnoreBulkData = false);` — Specialization of the duplication of a StaticMesh object specifically optimized for datasmith use case. This operation invalidate the duplicated SourceStaticMesh and mark it as PendingKill, unless bIgnoreBulkData is True. @param SourceStaticMesh	the UStaticMesh being copied @param Outer				the outer to use for the object @param Name				the optional name of the object @param bIgnoreBulkData	if True, the SourceStaticMesh's SourceModels BulkDatas won't be copied and SourceStaticMesh will stay valid after the operation. @return the copied StaticMesh or null if it failed for some reason
- L234 _public function_ `template< class T > static T* DuplicateObject(T* SourceObject, UObject* Outer, const FName Name = NAME_None)`
- L239 _public prototype_ `static bool CreatePlmXmlSceneFromCADFiles(FString PlmXmlFileName, const TSet<FString>& FilesToProcess, TArray<FString>& FilesNotProcessed);`
- L382 _function_ `template< typename ObjectType > inline ObjectType* FDatasmithImporterUtils::FindAsset( const FDatasmithAssetsImportContext& AssetsContext, const TCHAR* ObjectPathName )`
- L435 _function_ `template<> inline UTexture* FDatasmithImporterUtils::FindAsset< UTexture >( const FDatasmithAssetsImportContext& AssetsContext, const TCHAR* ObjectPathName )`
- L493 _function_ `template< class ObjectType > inline ObjectType* FDatasmithImporterUtils::FindObject( const UPackage* ParentPackage, const FString& ObjectName )`
- L541 _function_ `template< class ObjectType > bool FDatasmithImporterUtils::CanCreateAsset(const UPackage* Package, const FString& AssetName, FText& OutFailReason)`

#### enum `FDatasmithImporterUtils::EAssetCreationStatus`  
`enum class EAssetCreationStatus : uint8`  
_L27-34_
- L29 _public enumerator_ `CS_CanCreate`
- L30 _public enumerator_ `CS_HasRedirector`
- L31 _public enumerator_ `CS_ClassMismatch`
- L32 _public enumerator_ `CS_NameTooLong` — asset paths are store in FName, which have an internal limitation.
- L33 _public enumerator_ `CS_NameTooShort`

#### class `FDatasmithImporterUtils::FDatasmithMaterialImportIterator`  
`class FDatasmithMaterialImportIterator`  
_L183-207_
- L186 _public prototype_ `explicit FDatasmithMaterialImportIterator(const FDatasmithImportContext& InImportContext);`
- L189 _public prototype_ `FDatasmithMaterialImportIterator& operator++();` — Advances the iterator to the next element.
- L192 _public prototype_ `explicit operator bool() const;` — conversion to "bool" returning true if the iterator is valid.
- L195 _public function_ `bool operator !() const` — inverse of the "bool" operator
- L201 _public prototype_ `const TSharedPtr<IDatasmithBaseMaterialElement>& Value() const;` — Const Accessor.
- L204 _private member_ `const FDatasmithImportContext& ImportContext;`
- L205 _private member_ `int32 CurrentIndex;`
- L206 _private member_ `TArray<TSharedPtr<IDatasmithBaseMaterialElement>> SortedMaterials;`

#### struct `FDatasmithFindAssetTypeHelper`  
`template< typename ObjectType > struct FDatasmithFindAssetTypeHelper`  
_L243-245_
- L250 _public function_ `static const TMap< TSharedRef< IDatasmithMeshElement >, UStaticMesh* >& GetImportedAssetsMap( const FDatasmithAssetsImportContext& AssetsContext )`
- L255 _public function_ `static UPackage* GetFinalPackage( const FDatasmithAssetsImportContext& AssetsContext )`
- L260 _public function_ `static const TMap< FName, TSoftObjectPtr< UStaticMesh > >* GetAssetsMap( const UDatasmithScene* SceneAsset )`
- L265 _public function_ `static const TSharedRef<IDatasmithMeshElement>* GetImportedElementByName( const FDatasmithAssetsImportContext& AssetsContext, const TCHAR* ObjectPathName )`
- L274 _public function_ `static const TMap< TSharedRef< IDatasmithTextureElement >, UE::Interchange::FAssetImportResultRef >& GetImportedAssetsMap( const FDatasmithAssetsImportContext& AssetsContext )`
- L284 _public function_ `static const TMap< FName, TSoftObjectPtr< UTexture > >* GetAssetsMap( const UDatasmithScene* SceneAsset )`
- L289 _public function_ `static const TSharedRef<IDatasmithTextureElement>* GetImportedElementByName( const FDatasmithAssetsImportContext& AssetsContext, const TCHAR* ObjectPathName )`
- L298 _public function_ `static const TMap< TSharedRef< IDatasmithBaseMaterialElement >, UMaterialFunction* >& GetImportedAssetsMap(const FDatasmithAssetsImportContext& AssetsContext)`
- L308 _public function_ `static const TMap< FName, TSoftObjectPtr< UMaterialFunction > >* GetAssetsMap(const UDatasmithScene* SceneAsset)`
- L313 _public function_ `static const TSharedRef<IDatasmithBaseMaterialElement>* GetImportedElementByName( const FDatasmithAssetsImportContext& AssetsContext, const TCHAR* ObjectPathName )`
- L322 _public function_ `static const TMap< TSharedRef< IDatasmithBaseMaterialElement >, UMaterialInterface* >& GetImportedAssetsMap( const FDatasmithAssetsImportContext& AssetsContext )`
- L332 _public function_ `static const TMap< FName, TSoftObjectPtr< UMaterialInterface > >* GetAssetsMap( const UDatasmithScene* SceneAsset )`
- L346 _public function_ `static UPackage* GetImportPackage( const FDatasmithAssetsImportContext& AssetsContext )`
- L356 _public function_ `static const TMap< FName, TSoftObjectPtr< ULevelSequence > >* GetAssetsMap( const UDatasmithScene* SceneAsset )`
- L375 _public function_ `static const TMap< FName, TSoftObjectPtr< ULevelVariantSets > >* GetAssetsMap( const UDatasmithScene* SceneAsset )`

#### struct `FDatasmithFindAssetTypeHelper`  
`template<> struct FDatasmithFindAssetTypeHelper< UStaticMesh >`  
_L248-269_
- L250 _public function_ `static const TMap< TSharedRef< IDatasmithMeshElement >, UStaticMesh* >& GetImportedAssetsMap( const FDatasmithAssetsImportContext& AssetsContext )`
- L255 _public function_ `static UPackage* GetFinalPackage( const FDatasmithAssetsImportContext& AssetsContext )`
- L260 _public function_ `static const TMap< FName, TSoftObjectPtr< UStaticMesh > >* GetAssetsMap( const UDatasmithScene* SceneAsset )`
- L265 _public function_ `static const TSharedRef<IDatasmithMeshElement>* GetImportedElementByName( const FDatasmithAssetsImportContext& AssetsContext, const TCHAR* ObjectPathName )`
- L274 _public function_ `static const TMap< TSharedRef< IDatasmithTextureElement >, UE::Interchange::FAssetImportResultRef >& GetImportedAssetsMap( const FDatasmithAssetsImportContext& AssetsContext )`
- L284 _public function_ `static const TMap< FName, TSoftObjectPtr< UTexture > >* GetAssetsMap( const UDatasmithScene* SceneAsset )`
- L289 _public function_ `static const TSharedRef<IDatasmithTextureElement>* GetImportedElementByName( const FDatasmithAssetsImportContext& AssetsContext, const TCHAR* ObjectPathName )`
- L298 _public function_ `static const TMap< TSharedRef< IDatasmithBaseMaterialElement >, UMaterialFunction* >& GetImportedAssetsMap(const FDatasmithAssetsImportContext& AssetsContext)`
- L308 _public function_ `static const TMap< FName, TSoftObjectPtr< UMaterialFunction > >* GetAssetsMap(const UDatasmithScene* SceneAsset)`
- L313 _public function_ `static const TSharedRef<IDatasmithBaseMaterialElement>* GetImportedElementByName( const FDatasmithAssetsImportContext& AssetsContext, const TCHAR* ObjectPathName )`
- L322 _public function_ `static const TMap< TSharedRef< IDatasmithBaseMaterialElement >, UMaterialInterface* >& GetImportedAssetsMap( const FDatasmithAssetsImportContext& AssetsContext )`
- L332 _public function_ `static const TMap< FName, TSoftObjectPtr< UMaterialInterface > >* GetAssetsMap( const UDatasmithScene* SceneAsset )`
- L346 _public function_ `static UPackage* GetImportPackage( const FDatasmithAssetsImportContext& AssetsContext )`
- L356 _public function_ `static const TMap< FName, TSoftObjectPtr< ULevelSequence > >* GetAssetsMap( const UDatasmithScene* SceneAsset )`
- L375 _public function_ `static const TMap< FName, TSoftObjectPtr< ULevelVariantSets > >* GetAssetsMap( const UDatasmithScene* SceneAsset )`

#### struct `FDatasmithFindAssetTypeHelper`  
`template<> struct FDatasmithFindAssetTypeHelper< UTexture >`  
_L272-293_
- L250 _public function_ `static const TMap< TSharedRef< IDatasmithMeshElement >, UStaticMesh* >& GetImportedAssetsMap( const FDatasmithAssetsImportContext& AssetsContext )`
- L255 _public function_ `static UPackage* GetFinalPackage( const FDatasmithAssetsImportContext& AssetsContext )`
- L260 _public function_ `static const TMap< FName, TSoftObjectPtr< UStaticMesh > >* GetAssetsMap( const UDatasmithScene* SceneAsset )`
- L265 _public function_ `static const TSharedRef<IDatasmithMeshElement>* GetImportedElementByName( const FDatasmithAssetsImportContext& AssetsContext, const TCHAR* ObjectPathName )`
- L274 _public function_ `static const TMap< TSharedRef< IDatasmithTextureElement >, UE::Interchange::FAssetImportResultRef >& GetImportedAssetsMap( const FDatasmithAssetsImportContext& AssetsContext )`
- L284 _public function_ `static const TMap< FName, TSoftObjectPtr< UTexture > >* GetAssetsMap( const UDatasmithScene* SceneAsset )`
- L289 _public function_ `static const TSharedRef<IDatasmithTextureElement>* GetImportedElementByName( const FDatasmithAssetsImportContext& AssetsContext, const TCHAR* ObjectPathName )`
- L298 _public function_ `static const TMap< TSharedRef< IDatasmithBaseMaterialElement >, UMaterialFunction* >& GetImportedAssetsMap(const FDatasmithAssetsImportContext& AssetsContext)`
- L308 _public function_ `static const TMap< FName, TSoftObjectPtr< UMaterialFunction > >* GetAssetsMap(const UDatasmithScene* SceneAsset)`
- L313 _public function_ `static const TSharedRef<IDatasmithBaseMaterialElement>* GetImportedElementByName( const FDatasmithAssetsImportContext& AssetsContext, const TCHAR* ObjectPathName )`
- L322 _public function_ `static const TMap< TSharedRef< IDatasmithBaseMaterialElement >, UMaterialInterface* >& GetImportedAssetsMap( const FDatasmithAssetsImportContext& AssetsContext )`
- L332 _public function_ `static const TMap< FName, TSoftObjectPtr< UMaterialInterface > >* GetAssetsMap( const UDatasmithScene* SceneAsset )`
- L346 _public function_ `static UPackage* GetImportPackage( const FDatasmithAssetsImportContext& AssetsContext )`
- L356 _public function_ `static const TMap< FName, TSoftObjectPtr< ULevelSequence > >* GetAssetsMap( const UDatasmithScene* SceneAsset )`
- L375 _public function_ `static const TMap< FName, TSoftObjectPtr< ULevelVariantSets > >* GetAssetsMap( const UDatasmithScene* SceneAsset )`

#### struct `FDatasmithFindAssetTypeHelper`  
`template<> struct FDatasmithFindAssetTypeHelper< UMaterialFunction >`  
_L296-317_
- L250 _public function_ `static const TMap< TSharedRef< IDatasmithMeshElement >, UStaticMesh* >& GetImportedAssetsMap( const FDatasmithAssetsImportContext& AssetsContext )`
- L255 _public function_ `static UPackage* GetFinalPackage( const FDatasmithAssetsImportContext& AssetsContext )`
- L260 _public function_ `static const TMap< FName, TSoftObjectPtr< UStaticMesh > >* GetAssetsMap( const UDatasmithScene* SceneAsset )`
- L265 _public function_ `static const TSharedRef<IDatasmithMeshElement>* GetImportedElementByName( const FDatasmithAssetsImportContext& AssetsContext, const TCHAR* ObjectPathName )`
- L274 _public function_ `static const TMap< TSharedRef< IDatasmithTextureElement >, UE::Interchange::FAssetImportResultRef >& GetImportedAssetsMap( const FDatasmithAssetsImportContext& AssetsContext )`
- L284 _public function_ `static const TMap< FName, TSoftObjectPtr< UTexture > >* GetAssetsMap( const UDatasmithScene* SceneAsset )`
- L289 _public function_ `static const TSharedRef<IDatasmithTextureElement>* GetImportedElementByName( const FDatasmithAssetsImportContext& AssetsContext, const TCHAR* ObjectPathName )`
- L298 _public function_ `static const TMap< TSharedRef< IDatasmithBaseMaterialElement >, UMaterialFunction* >& GetImportedAssetsMap(const FDatasmithAssetsImportContext& AssetsContext)`
- L308 _public function_ `static const TMap< FName, TSoftObjectPtr< UMaterialFunction > >* GetAssetsMap(const UDatasmithScene* SceneAsset)`
- L313 _public function_ `static const TSharedRef<IDatasmithBaseMaterialElement>* GetImportedElementByName( const FDatasmithAssetsImportContext& AssetsContext, const TCHAR* ObjectPathName )`
- L322 _public function_ `static const TMap< TSharedRef< IDatasmithBaseMaterialElement >, UMaterialInterface* >& GetImportedAssetsMap( const FDatasmithAssetsImportContext& AssetsContext )`
- L332 _public function_ `static const TMap< FName, TSoftObjectPtr< UMaterialInterface > >* GetAssetsMap( const UDatasmithScene* SceneAsset )`
- L346 _public function_ `static UPackage* GetImportPackage( const FDatasmithAssetsImportContext& AssetsContext )`
- L356 _public function_ `static const TMap< FName, TSoftObjectPtr< ULevelSequence > >* GetAssetsMap( const UDatasmithScene* SceneAsset )`
- L375 _public function_ `static const TMap< FName, TSoftObjectPtr< ULevelVariantSets > >* GetAssetsMap( const UDatasmithScene* SceneAsset )`

#### struct `FDatasmithFindAssetTypeHelper`  
`template<> struct FDatasmithFindAssetTypeHelper< UMaterialInterface >`  
_L320-341_
- L250 _public function_ `static const TMap< TSharedRef< IDatasmithMeshElement >, UStaticMesh* >& GetImportedAssetsMap( const FDatasmithAssetsImportContext& AssetsContext )`
- L255 _public function_ `static UPackage* GetFinalPackage( const FDatasmithAssetsImportContext& AssetsContext )`
- L260 _public function_ `static const TMap< FName, TSoftObjectPtr< UStaticMesh > >* GetAssetsMap( const UDatasmithScene* SceneAsset )`
- L265 _public function_ `static const TSharedRef<IDatasmithMeshElement>* GetImportedElementByName( const FDatasmithAssetsImportContext& AssetsContext, const TCHAR* ObjectPathName )`
- L274 _public function_ `static const TMap< TSharedRef< IDatasmithTextureElement >, UE::Interchange::FAssetImportResultRef >& GetImportedAssetsMap( const FDatasmithAssetsImportContext& AssetsContext )`
- L284 _public function_ `static const TMap< FName, TSoftObjectPtr< UTexture > >* GetAssetsMap( const UDatasmithScene* SceneAsset )`
- L289 _public function_ `static const TSharedRef<IDatasmithTextureElement>* GetImportedElementByName( const FDatasmithAssetsImportContext& AssetsContext, const TCHAR* ObjectPathName )`
- L298 _public function_ `static const TMap< TSharedRef< IDatasmithBaseMaterialElement >, UMaterialFunction* >& GetImportedAssetsMap(const FDatasmithAssetsImportContext& AssetsContext)`
- L308 _public function_ `static const TMap< FName, TSoftObjectPtr< UMaterialFunction > >* GetAssetsMap(const UDatasmithScene* SceneAsset)`
- L313 _public function_ `static const TSharedRef<IDatasmithBaseMaterialElement>* GetImportedElementByName( const FDatasmithAssetsImportContext& AssetsContext, const TCHAR* ObjectPathName )`
- L322 _public function_ `static const TMap< TSharedRef< IDatasmithBaseMaterialElement >, UMaterialInterface* >& GetImportedAssetsMap( const FDatasmithAssetsImportContext& AssetsContext )`
- L332 _public function_ `static const TMap< FName, TSoftObjectPtr< UMaterialInterface > >* GetAssetsMap( const UDatasmithScene* SceneAsset )`
- L346 _public function_ `static UPackage* GetImportPackage( const FDatasmithAssetsImportContext& AssetsContext )`
- L356 _public function_ `static const TMap< FName, TSoftObjectPtr< ULevelSequence > >* GetAssetsMap( const UDatasmithScene* SceneAsset )`
- L375 _public function_ `static const TMap< FName, TSoftObjectPtr< ULevelVariantSets > >* GetAssetsMap( const UDatasmithScene* SceneAsset )`

#### struct `FDatasmithFindAssetTypeHelper`  
`template<> struct FDatasmithFindAssetTypeHelper< ULevelSequence >`  
_L344-360_
- L250 _public function_ `static const TMap< TSharedRef< IDatasmithMeshElement >, UStaticMesh* >& GetImportedAssetsMap( const FDatasmithAssetsImportContext& AssetsContext )`
- L255 _public function_ `static UPackage* GetFinalPackage( const FDatasmithAssetsImportContext& AssetsContext )`
- L260 _public function_ `static const TMap< FName, TSoftObjectPtr< UStaticMesh > >* GetAssetsMap( const UDatasmithScene* SceneAsset )`
- L265 _public function_ `static const TSharedRef<IDatasmithMeshElement>* GetImportedElementByName( const FDatasmithAssetsImportContext& AssetsContext, const TCHAR* ObjectPathName )`
- L274 _public function_ `static const TMap< TSharedRef< IDatasmithTextureElement >, UE::Interchange::FAssetImportResultRef >& GetImportedAssetsMap( const FDatasmithAssetsImportContext& AssetsContext )`
- L284 _public function_ `static const TMap< FName, TSoftObjectPtr< UTexture > >* GetAssetsMap( const UDatasmithScene* SceneAsset )`
- L289 _public function_ `static const TSharedRef<IDatasmithTextureElement>* GetImportedElementByName( const FDatasmithAssetsImportContext& AssetsContext, const TCHAR* ObjectPathName )`
- L298 _public function_ `static const TMap< TSharedRef< IDatasmithBaseMaterialElement >, UMaterialFunction* >& GetImportedAssetsMap(const FDatasmithAssetsImportContext& AssetsContext)`
- L308 _public function_ `static const TMap< FName, TSoftObjectPtr< UMaterialFunction > >* GetAssetsMap(const UDatasmithScene* SceneAsset)`
- L313 _public function_ `static const TSharedRef<IDatasmithBaseMaterialElement>* GetImportedElementByName( const FDatasmithAssetsImportContext& AssetsContext, const TCHAR* ObjectPathName )`
- L322 _public function_ `static const TMap< TSharedRef< IDatasmithBaseMaterialElement >, UMaterialInterface* >& GetImportedAssetsMap( const FDatasmithAssetsImportContext& AssetsContext )`
- L332 _public function_ `static const TMap< FName, TSoftObjectPtr< UMaterialInterface > >* GetAssetsMap( const UDatasmithScene* SceneAsset )`
- L346 _public function_ `static UPackage* GetImportPackage( const FDatasmithAssetsImportContext& AssetsContext )`
- L356 _public function_ `static const TMap< FName, TSoftObjectPtr< ULevelSequence > >* GetAssetsMap( const UDatasmithScene* SceneAsset )`
- L375 _public function_ `static const TMap< FName, TSoftObjectPtr< ULevelVariantSets > >* GetAssetsMap( const UDatasmithScene* SceneAsset )`

#### struct `FDatasmithFindAssetTypeHelper`  
`template<> struct FDatasmithFindAssetTypeHelper< ULevelVariantSets >`  
_L363-379_
- L250 _public function_ `static const TMap< TSharedRef< IDatasmithMeshElement >, UStaticMesh* >& GetImportedAssetsMap( const FDatasmithAssetsImportContext& AssetsContext )`
- L255 _public function_ `static UPackage* GetFinalPackage( const FDatasmithAssetsImportContext& AssetsContext )`
- L260 _public function_ `static const TMap< FName, TSoftObjectPtr< UStaticMesh > >* GetAssetsMap( const UDatasmithScene* SceneAsset )`
- L265 _public function_ `static const TSharedRef<IDatasmithMeshElement>* GetImportedElementByName( const FDatasmithAssetsImportContext& AssetsContext, const TCHAR* ObjectPathName )`
- L274 _public function_ `static const TMap< TSharedRef< IDatasmithTextureElement >, UE::Interchange::FAssetImportResultRef >& GetImportedAssetsMap( const FDatasmithAssetsImportContext& AssetsContext )`
- L284 _public function_ `static const TMap< FName, TSoftObjectPtr< UTexture > >* GetAssetsMap( const UDatasmithScene* SceneAsset )`
- L289 _public function_ `static const TSharedRef<IDatasmithTextureElement>* GetImportedElementByName( const FDatasmithAssetsImportContext& AssetsContext, const TCHAR* ObjectPathName )`
- L298 _public function_ `static const TMap< TSharedRef< IDatasmithBaseMaterialElement >, UMaterialFunction* >& GetImportedAssetsMap(const FDatasmithAssetsImportContext& AssetsContext)`
- L308 _public function_ `static const TMap< FName, TSoftObjectPtr< UMaterialFunction > >* GetAssetsMap(const UDatasmithScene* SceneAsset)`
- L313 _public function_ `static const TSharedRef<IDatasmithBaseMaterialElement>* GetImportedElementByName( const FDatasmithAssetsImportContext& AssetsContext, const TCHAR* ObjectPathName )`
- L322 _public function_ `static const TMap< TSharedRef< IDatasmithBaseMaterialElement >, UMaterialInterface* >& GetImportedAssetsMap( const FDatasmithAssetsImportContext& AssetsContext )`
- L332 _public function_ `static const TMap< FName, TSoftObjectPtr< UMaterialInterface > >* GetAssetsMap( const UDatasmithScene* SceneAsset )`
- L346 _public function_ `static UPackage* GetImportPackage( const FDatasmithAssetsImportContext& AssetsContext )`
- L356 _public function_ `static const TMap< FName, TSoftObjectPtr< ULevelSequence > >* GetAssetsMap( const UDatasmithScene* SceneAsset )`
- L375 _public function_ `static const TMap< FName, TSoftObjectPtr< ULevelVariantSets > >* GetAssetsMap( const UDatasmithScene* SceneAsset )`

#### Free symbols / members of external scopes

- L22 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN( LogDatasmithImport, Log, All );`
- L22 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN( LogDatasmithImport, Log, All );`

### `Plugins/Enterprise/DatasmithImporter/Source/DatasmithImporter/Public/Utility/DatasmithTextureResize.h` (Public)


#### class `FDatasmithTextureResize`  
`class FDatasmithTextureResize`  
_L9-70_
- L16 _public prototype_ `static void Initialize();` — Must be called from the main thread before doing any parallel work.
- L22 _public prototype_ `static bool IsSupportedTextureExtension(const FString& Extension);` — Returns true if image extension is supported by Unreal Engine IMPORTANT: Extension is expected with the starting dot
- L28 _public prototype_ `static bool GetBestTextureExtension(const TCHAR* Source, FString& Extension);` — Returns true if image extension is supported by Unreal Engine or image can be converted to a supported format IMPORTANT: Extension is expected with the starting dot
- L37 _public prototype_ `static EDSTextureUtilsError ResizeTexture( const TCHAR* Source, const TCHAR* Destination, EDSResizeTextureMode Mode, uint32 MaxSize, bool bGenerateNormalMap );` — Resizes texture according to resizing method @param Source				The source file of the texture to resize @param Destination			The path where to save the resized texture file @param Mode					The resize mode @param bGenerateNormalMap	Generate or not the normal map
