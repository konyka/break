# Plugins / VariantManagerContentEditor

- module root: `Plugins/Enterprise/VariantManagerContent/Source/VariantManagerContentEditor`
- headers: 10; symbols: 86
- symbol kinds: class=8, delegate=2, enum=1, enumerator=4, function=5, macro=2, member=25, prototype=38, struct=1
- PrivateDependencyModuleNames: InputCore, Projects, Slate, SlateCore, VariantManagerContent, WorkspaceMenuStructure
- PublicDependencyModuleNames: AssetDefinition, ContentBrowser, Core, CoreUObject, EditorFramework, Engine, ToolMenus, UnrealEd

### `Plugins/Enterprise/VariantManagerContent/Source/VariantManagerContentEditor/Private/AssetDefinition_LevelVariantSets.h` (Private)


#### class `UAssetDefinition_LevelVariantSets`  
`class UAssetDefinition_LevelVariantSets : public UAssetDefinitionDefault`  
_L12-29_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L19 _public prototype_ `virtual FText GetAssetDisplayName() const override;` — UAssetDefinition Begin
- L20 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L21 _public prototype_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override;`
- L22 _public prototype_ `virtual EAssetCommandResult OpenAssets(const FAssetOpenArgs& OpenArgs) const override;`
- L23 _public prototype_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override;`
- L24 _public function_ `virtual bool CanImport() const override`
- L25 _public prototype_ `virtual FAssetSupportResponse CanLocalize(const FAssetData& InAsset) const override;`
- L26 _public prototype_ `virtual FAssetOpenSupport GetAssetOpenSupport(const FAssetOpenSupportArgs& OpenSupportArgs) const override;`
- L27 _public prototype_ `virtual const FSlateBrush* GetThumbnailBrush(const FAssetData& InAssetData, const FName InClassName) const override;`

### `Plugins/Enterprise/VariantManagerContent/Source/VariantManagerContentEditor/Private/LevelVariantSetsActorCustomization.h` (Private)


#### class `FLevelVariantSetsActorCustomization`  
`class FLevelVariantSetsActorCustomization : public IDetailCustomization`  
_L11-24_
- inherits: `IDetailCustomization`
- L14 _public prototype_ `FLevelVariantSetsActorCustomization();`
- L15 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L18 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailLayout) override;` — IDetailCustomization interface
- L22 _private prototype_ `FReply OnOpenVariantManagerButtonClicked(ALevelVariantSetsActor* Actor);`
- L23 _private prototype_ `FReply OnCreateLevelVarSetsButtonClicked();`

### `Plugins/Enterprise/VariantManagerContent/Source/VariantManagerContentEditor/Private/SwitchActorCustomization.h` (Private)


#### class `FSwitchActorCustomization`  
`class FSwitchActorCustomization : public IDetailCustomization`  
_L11-32_
- inherits: `IDetailCustomization`
- L14 _public prototype_ `FSwitchActorCustomization();`
- L15 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L18 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailLayout) override;` — IDetailCustomization interface
- L19 _public prototype_ `virtual void CustomizeDetails(const TSharedPtr<IDetailLayoutBuilder>& DetailBuilder) override;`
- L23 _private prototype_ `void OnComboBoxOpening();`
- L24 _private prototype_ `void OnComboBoxOptionChanged(TSharedPtr<FString> NewOption, ESelectInfo::Type SelectType);`
- L25 _private prototype_ `FText GetComboBoxSelectedOptionText() const;`
- L26 _private prototype_ `void ForceRefreshDetails(int32 NewOption);`
- L28 _private member_ `ASwitchActor* CurrentActor;`
- L29 _private member_ `TWeakPtr<IDetailLayoutBuilder> DetailBuilderWeakPtr;`
- L30 _private member_ `TSharedPtr<SComboBox<TSharedPtr<FString>>> ComboBox;`
- L31 _private member_ `TArray<TSharedPtr<FString>> Options;`

### `Plugins/Enterprise/VariantManagerContent/Source/VariantManagerContentEditor/Private/VariantManagerContentEditorLog.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogVariantManagerContentEditor, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogVariantManagerContentEditor, Log, All);`

### `Plugins/Enterprise/VariantManagerContent/Source/VariantManagerContentEditor/Private/VariantManagerContentStyle.h` (Private)


#### struct `FVariantManagerContentStyle`  
`struct FVariantManagerContentStyle : public FSlateStyleSet`  
_L8-24_
- inherits: `FSlateStyleSet`
- L11 _public prototype_ `FVariantManagerContentStyle();`
- L13 _public prototype_ `static void Initialize();`
- L15 _public prototype_ `static void Shutdown();`
- L17 _public prototype_ `static const FName GetAppStyleSetName();`
- L19 _public function_ `static FVariantManagerContentStyle& Get()`

### `Plugins/Enterprise/VariantManagerContent/Source/VariantManagerContentEditor/Public/LevelVariantSetsActorFactory.h` (Public)


#### class `ULevelVariantSetsActorFactory`  
`class ULevelVariantSetsActorFactory : public UActorFactory`  
_L15-24_
- reflection: `UCLASS()`
- inherits: `UActorFactory`
- L20 _private prototype_ `virtual AActor* SpawnActor(UObject* InAsset, ULevel* InLevel, const FTransform& InTransform, const FActorSpawnParameters& InSpawnParams) override;`
- L21 _private prototype_ `virtual bool CanCreateActorFrom( const FAssetData& AssetData, FText& OutErrorMsg ) override;`
- L22 _private prototype_ `virtual UObject* GetAssetFromActorInstance(AActor* ActorInstance) override;`

### `Plugins/Enterprise/VariantManagerContent/Source/VariantManagerContentEditor/Public/SwitchActorFactory.h` (Public)


#### class `USwitchActorFactory`  
`class USwitchActorFactory : public UActorFactory`  
_L13-16_
- reflection: `UCLASS(MinimalAPI, config=Editor, collapsecategories, hidecategories=Object)`
- inherits: `UActorFactory`
- desc: The only purpose of this class is to trigger a slightly different code path within FLevelEditorViewportClient::TryPlacingActorFromObject when dragging and dropping a SwitchActor into the viewport, so that the SwitchActor labels get sanitized by FActorLabelUtilities::SetActorLabelUnique and don't repeatedly increment

### `Plugins/Enterprise/VariantManagerContent/Source/VariantManagerContentEditor/Public/VariantManagerContentEditorModule.h` (Public)


#### class `IVariantManagerContentEditorModule`  
`class IVariantManagerContentEditorModule : public IModuleInterface`  
_L15-37_
- inherits: `IModuleInterface`
- L18 _public function_ `static inline IVariantManagerContentEditorModule& Get()`
- L23 _public function_ `static inline bool IsAvailable()`
- L30 _public prototype_ `virtual void RegisterOnLevelVariantSetsDelegate(FOnLevelVariantSetsEditor Delegate) = 0;` — This will be executed whenever FLevelVariantSetsAssetActions::OpenAssetEditor is called with a valid asset. This so that the editor toolkit can be on the VariantManager plugin and the AssetActions can be on this module
- L31 _public prototype_ `virtual void UnregisterOnLevelVariantSetsDelegate() = 0;`
- L32 _public prototype_ `virtual FOnLevelVariantSetsEditor GetOnLevelVariantSetsEditorOpened() const = 0;`
- L34 _public prototype_ `virtual UObject* CreateLevelVariantSetsAssetWithDialog() = 0;`
- L35 _public prototype_ `virtual UObject* CreateLevelVariantSetsAsset(const FString& AssetName, const FString& PackagePath, bool bForceOverwrite = false) = 0;`
- L36 _public prototype_ `virtual AActor* GetOrCreateLevelVariantSetsActor(UObject* LevelVariantSetsAsset, bool bForceCreate=false) = 0;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define VARIANTMANAGERCONTENTEDITORMODULE_MODULE_NAME TEXT("VariantManagerContentEditor")`
- L13 _delegate_ `DECLARE_DELEGATE_ThreeParams( FOnLevelVariantSetsEditor, const EToolkitMode::Type, const TSharedPtr< class IToolkitHost >&, class ULevelVariantSets*);`
- L13 _prototype_ `DECLARE_DELEGATE_ThreeParams( FOnLevelVariantSetsEditor, const EToolkitMode::Type, const TSharedPtr< class IToolkitHost >&, class ULevelVariantSets*);`

### `Plugins/Enterprise/VariantManagerContent/Source/VariantManagerContentEditor/Public/VariantManagerFactoryNew.h` (Public)


#### class `UVariantManagerFactoryNew`  
`class UVariantManagerFactoryNew : public UFactory`  
_L10-19_
- reflection: `UCLASS(hidecategories=Object)`
- inherits: `UFactory`
- L16 _public prototype_ `virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;` — UFactory Interface
- L17 _public prototype_ `virtual bool ShouldShowInNewMenu() const override;`

### `Plugins/Enterprise/VariantManagerContent/Source/VariantManagerContentEditor/Public/VariantManagerTestActor.h` (Public)


#### enum `EVariantManagerTestEnum`  
`enum class EVariantManagerTestEnum : uint8`  
_L12-18_
- reflection: `UENUM(BlueprintType)`
- L14 _public enumerator_ `None = 0 UMETA(Hidden)`
- L15 _public enumerator_ `FirstOption = 1`
- L16 _public enumerator_ `SecondOption = 3`
- L17 _public enumerator_ `ThirdOption = 45`

#### class `AVariantManagerTestActor`  
`class AVariantManagerTestActor : public AActor`  
_L21-112_
- reflection: `UCLASS(MinimalAPI, hideCategories=(Rendering, Physics, HLOD, Activation, Input, Actor, Cooking))`
- inherits: `AActor`
- L27 _public prototype_ `AVariantManagerTestActor(const FObjectInitializer& Init);`
- L30 _public member_ `EVariantManagerTestEnum EnumWithNoDefault;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Template", meta=(ToolTip="Captured byte property"))`
- L33 _public member_ `EVariantManagerTestEnum EnumWithSecondDefault = EVariantManagerTestEnum::SecondOption;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Template", meta=(ToolTip="Captured byte property"))`
- L36 _public member_ `uint8 CapturedByteProperty;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Template", meta=(ToolTip="Captured byte property"))`
- L54 _public member_ `int32 CapturedIntProperty = 7;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Template", meta=(ToolTip="Captured int32 property"))`
- L60 _public member_ `float CapturedFloatProperty = 2.3f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Template", meta=(ToolTip="Captured float property"))`
- L66 _public member_ `bool bCapturedBoolProperty;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Template", meta=(ToolTip="Captured boolean property"))`
- L69 _public member_ `TObjectPtr<UObject> CapturedObjectProperty;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Template", meta=(ToolTip="Captured UObject property"))`
- L72 _public member_ `FScriptInterface CapturedInterfaceProperty;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Template", meta=(ToolTip="Captured UInterface property"))`
- L75 _public member_ `FName CapturedNameProperty;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Template", meta=(ToolTip="Captured FName property"))`
- L78 _public member_ `FString CapturedStrProperty;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Template", meta=(ToolTip="Captured FString property"))`
- L81 _public member_ `FText CapturedTextProperty;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Template", meta=(ToolTip="Captured FText property"))`
- L84 _public member_ `FRotator CapturedRotatorProperty;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Template", meta=(ToolTip="Captured FRotator property"))`
- L87 _public member_ `FColor CapturedColorProperty;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Template", meta=(ToolTip="Captured FColor property"))`
- L90 _public member_ `FLinearColor CapturedLinearColorProperty;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Template", meta=(ToolTip="Captured FLinearColor property"))`
- L93 _public member_ `FVector CapturedVectorProperty;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Template", meta=(ToolTip="Captured FVector property"))`
- L96 _public member_ `FQuat CapturedQuatProperty;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Template", meta=(ToolTip="Captured FQuat property"))`
- L99 _public member_ `FVector4 CapturedVector4Property;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Template", meta=(ToolTip="Captured FVector4 property"))`
- L102 _public member_ `FVector2D CapturedVector2DProperty;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Template", meta=(ToolTip="Captured FVector2D property"))`
- L105 _public member_ `FIntPoint CapturedIntPointProperty;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Template", meta=(ToolTip="Captured FIntPoint property"))`
- L108 _public member_ `TArray<TObjectPtr<UObject>> CapturedUObjectArrayProperty;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Template", meta=(ToolTip="Captured UObject array property"))`
- L111 _public member_ `TArray<FVector> CapturedVectorArrayProperty;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Template", meta=(ToolTip="Captured FVector array property"))`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API VARIANTMANAGERCONTENTEDITOR_API`
