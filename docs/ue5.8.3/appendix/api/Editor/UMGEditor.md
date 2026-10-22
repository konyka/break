# Editor / UMGEditor

- module root: `Source/Editor/UMGEditor`
- headers: 127; symbols: 2698
- symbol kinds: class=151, delegate=29, enum=19, enumerator=76, externvar=1, function=238, macro=32, member=591, namespace=42, prototype=1464, struct=40, typedef=15
- PrivateDependencyModuleNames: ApplicationCore, AssetDefinition, AssetRegistry, AssetTools, BlueprintGraph, Blutility, ClassViewer, ContentBrowser, ContentBrowserData, Core, CoreUObject, DetailCustomizations, DeveloperSettings, EditorConfig, EditorFramework, EditorStyle, EditorSubsystem, EditorWidgets, Engine, GameProjectGeneration, GraphEditor, ImageWrapper, InputCore, InteractiveToolsFramework, Kismet, KismetCompiler, KismetWidgets, MessageLog, MovieScene, MovieSceneTools, MovieSceneTracks, Projects, PropertyEditor, PropertyPath, RenderCore, Settings, Slate, SlateCore, SlateRHIRenderer, SlateReflector, StatusBar, StructUtilsEditor, StructViewer, TargetPlatform, TimeManagement, ToolMenus, ToolWidgets, UMG, UnrealEd, WorkspaceMenuStructure
- PublicDependencyModuleNames: FieldNotification, Sequencer, SequencerCore

### `Source/Editor/UMGEditor/Classes/K2Node_WidgetAnimationEvent.h` (Public)


#### class `UK2Node_WidgetAnimationEvent`  
`class UK2Node_WidgetAnimationEvent : public UK2Node_Event`  
_L20-70_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UK2Node_Event`
- L28 _public member_ `EWidgetAnimationEvent Action;` — `UPROPERTY()` — The action to bind to.
- L32 _public member_ `FName AnimationPropertyName;` — `UPROPERTY()` — Name of property in Blueprint class that pointer to component we want to bind to
- L36 _public member_ `FName UserTag;` — `UPROPERTY(EditAnywhere, Category = "Animation")` — Binds this to a specific user action.
- L39 _public member_ `TObjectPtr<const UWidgetBlueprint> SourceWidgetBlueprint;` — `UPROPERTY()`
- L41 _public prototype_ `virtual void PostDuplicate(bool bDuplicateForPIE) override;`
- L44 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L45 _public prototype_ `virtual FText GetTooltipText() const override;`
- L46 _public prototype_ `virtual bool IsCompatibleWithGraph(const UEdGraph* TargetGraph) const override;`
- L47 _public prototype_ `virtual bool IsActionFilteredOut(FBlueprintActionFilter const& Filter) override;`
- L51 _public prototype_ `virtual void ValidateNodeDuringCompilation(class FCompilerResultsLog& MessageLog) const override;`
- L52 _public function_ `virtual bool ShouldShowNodeProperties() const override`
- L53 _public prototype_ `virtual UClass* GetDynamicBindingClass() const override;`
- L54 _public prototype_ `virtual void RegisterDynamicBinding(UDynamicBlueprintBinding* BindingObject) const override;`
- L55 _public prototype_ `virtual void HandleVariableRenamed(UBlueprint* InBlueprint, UClass* InVariableClass, UEdGraph* InGraph, const FName& InOldVarName, const FName& InNewVarName) override;`
- L56 _public prototype_ `virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;`
- L57 _public prototype_ `virtual FText GetMenuCategory() const override;`
- L58 _public prototype_ `virtual FBlueprintNodeSignature GetSignature() const override;`
- L61 _public prototype_ `void MarkDirty();`
- L64 _private prototype_ `void Initialize(const UWidgetBlueprint* InSourceBlueprint, UWidgetAnimation* InAnimation, EWidgetAnimationEvent InAction);`
- L68 _private member_ `FNodeTextCache CachedTooltip;` — Constructing FText strings can be costly, so we cache the node's title/tooltip
- L69 _private member_ `FNodeTextCache CachedNodeTitle;`

### `Source/Editor/UMGEditor/Classes/WidgetBlueprintFactory.h` (Public)


#### class `UWidgetBlueprintFactory`  
`class UWidgetBlueprintFactory : public UFactory`  
_L13-35_
- reflection: `UCLASS(HideCategories=Object, MinimalAPI)`
- inherits: `UFactory`
- L23 _private member_ `TSubclassOf<class UUserWidget> ParentClass;` — `UPROPERTY(EditAnywhere, Category=WidgetBlueprintFactory, meta=(AllowAbstract = ""))` — The parent class of the created blueprint
- L26 _private prototype_ `virtual bool ConfigureProperties() override;`
- L27 _private prototype_ `virtual bool ShouldShowInNewMenu() const override;`
- L28 _private prototype_ `virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn, FName CallingContext) override;`
- L29 _private prototype_ `virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;`
- L34 _private member_ `TObjectPtr<UClass> RootWidgetClass;` — `UPROPERTY(Transient)`

### `Source/Editor/UMGEditor/Classes/WidgetGraphSchema.h` (Public)


#### class `UWidgetGraphSchema`  
`class UWidgetGraphSchema : public UEdGraphSchema_K2`  
_L14-31_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UEdGraphSchema_K2`
- L19 _public prototype_ `virtual void BackwardCompatibilityNodeConversion(UEdGraph* Graph, bool bOnlySafeChanges) const override;`
- L22 _private prototype_ `void ConvertAnimationEventNodes(UEdGraph* Graph) const;`
- L24 _private prototype_ `void ConvertAddAnimationDelegate(UEdGraph* Graph) const;`
- L25 _private prototype_ `void ConvertRemoveAnimationDelegate(UEdGraph* Graph) const;`
- L26 _private prototype_ `void ConvertClearAnimationDelegate(UEdGraph* Graph) const;`
- L28 _private prototype_ `void ReplaceAnimationFunctionAndAllocateDefaultPins(UEdGraph* Graph, UK2Node* OldNode, UK2Node_CallFunction* NewFunctionNode) const;`
- L30 _private prototype_ `void FixDefaultToSelfForAnimation(UEdGraph* Graph) const;`

### `Source/Editor/UMGEditor/Classes/WidgetPaletteFavorites.h` (Public)


#### class `UWidgetPaletteFavorites`  
`class UWidgetPaletteFavorites : public UObject`  
_L16-34_
- reflection: `UCLASS(MinimalAPI, config = EditorPerProjectUserSettings)`
- inherits: `UObject`
- L21 _public prototype_ `void Add(const FString& InWidgetTemplateName);`
- L22 _public prototype_ `void Remove(const FString& InWidgetTemplateName);`
- L24 _public function_ `TArray<FString> GetFavorites() const`
- L26 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnFavoritesUpdated) FOnFavoritesUpdated OnFavoritesUpdated;`
- L33 _private member_ `TArray<FString> Favorites;` — `UPROPERTY(config)`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API UMGEDITOR_API`
- L26 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnFavoritesUpdated) FOnFavoritesUpdated OnFavoritesUpdated;`

### `Source/Editor/UMGEditor/Private/Animation/MarginTrackEditor.h` (Private)


#### class `FMarginTrackEditor`  
`class FMarginTrackEditor : public FPropertyTrackEditor<UMovieSceneMarginTrack>`  
_L23-68_
- inherits: `FPropertyTrackEditor<UMovieSceneMarginTrack>`
- L33 _public function_ `FMarginTrackEditor( TSharedRef<ISequencer> InSequencer ) : FPropertyTrackEditor( InSequencer, GetAnimatedPropertyTypes() )` — Constructor @param InSequencer The sequencer instance to be used by this tool
- L41 _public function_ `static TArray<FAnimatedPropertyKey, TInlineAllocator<1>> GetAnimatedPropertyTypes()` — Retrieve a list of all property types that this track editor animates
- L54 _public prototype_ `static TSharedRef<ISequencerTrackEditor> CreateTrackEditor( TSharedRef<ISequencer> OwningSequencer );` — Creates an instance of this class.  Called by a sequencer @param OwningSequencer The sequencer instance to be used by this tool @return The new instance of this class
- L59 _protected prototype_ `virtual FText GetDisplayName() const override;`
- L60 _protected prototype_ `virtual void GenerateKeysFromPropertyChanged( const FPropertyChangedParams& PropertyChangedParams, UMovieSceneSection* SectionToKey, FGeneratedTrackKeys& OutGeneratedKeys) override;`
- L64 _private member_ `static FName LeftName;`
- L65 _private member_ `static FName TopName;`
- L66 _private member_ `static FName RightName;`
- L67 _private member_ `static FName BottomName;`

### `Source/Editor/UMGEditor/Private/Animation/MovieSceneSequenceEditor_WidgetAnimation.h` (Private)


#### struct `FMovieSceneSequenceEditor_WidgetAnimation`  
`struct FMovieSceneSequenceEditor_WidgetAnimation : FMovieSceneSequenceEditor`  
_L14-41_
- inherits: `FMovieSceneSequenceEditor`
- L16 _public function_ `virtual bool CanCreateEvents(UMovieSceneSequence* InSequence) const`
- L21 _public function_ `virtual bool CanCreateDirectorBlueprint(UMovieSceneSequence* Sequence) const override`
- L37 _public function_ `virtual UBlueprint* GetBlueprintForSequence(UMovieSceneSequence* InSequence) const override`

### `Source/Editor/UMGEditor/Private/Animation/Sequencer2DTransformSection.h` (Private)


#### class `F2DTransformSection`  
`class F2DTransformSection : public FSequencerSection`  
_L18-46_
- inherits: `FSequencerSection`
- desc: An implementation of 2d transform property sections.
- L28 _public function_ `F2DTransformSection(UMovieSceneSection& InSection, TWeakPtr<ISequencer> InSequencer) : FSequencerSection(InSection), WeakSequencer(InSequencer)` — Creates a new 2d transform property section. @param InSection The section object which is being displayed and edited. @param InSequencer The sequencer which is controlling this property section.
- L35 _public prototype_ `virtual void BuildSectionContextMenu(FMenuBuilder& MenuBuilder, const FGuid& InObjectBinding) override;`
- L39 _public prototype_ `virtual bool RequestDeleteCategory(const TArray<FName>& CategoryNamePath) override;`
- L40 _public prototype_ `virtual bool RequestDeleteKeyArea(const TArray<FName>& KeyAreaNamePath) override;`
- L45 _protected member_ `TWeakPtr<ISequencer> WeakSequencer;` — The sequencer which is controlling this section.

### `Source/Editor/UMGEditor/Private/Animation/Sequencer2DTransformTrackEditor.h` (Private)


#### class `F2DTransformTrackEditor`  
`class F2DTransformTrackEditor : public FPropertyTrackEditor<UMovieScene2DTransformTrack>`  
_L32-84_
- inherits: `FPropertyTrackEditor<UMovieScene2DTransformTrack>`
- L42 _public function_ `F2DTransformTrackEditor( TSharedRef<ISequencer> InSequencer ) : FPropertyTrackEditor( InSequencer, GetAnimatedPropertyTypes() )` — Constructor @param InSequencer The sequencer instance to be used by this tool
- L50 _public function_ `static TArray<FAnimatedPropertyKey, TInlineAllocator<1>> GetAnimatedPropertyTypes()` — Retrieve a list of all property types that this track editor animates
- L61 _public prototype_ `static TSharedRef<ISequencerTrackEditor> CreateTrackEditor( TSharedRef<ISequencer> OwningSequencer );` — Creates an instance of this class.  Called by a sequencer @param OwningSequencer The sequencer instance to be used by this tool @return The new instance of this class
- L66 _protected prototype_ `virtual FText GetDisplayName() const override;` — ISequencerTrackEditor interface
- L67 _protected prototype_ `virtual TSharedRef<ISequencerSection> MakeSectionInterface( UMovieSceneSection& SectionObject, UMovieSceneTrack& Track, FGuid ObjectBinding ) override;`
- L68 _protected prototype_ `virtual void ProcessKeyOperation(FFrameNumber InKeyTime, const UE::Sequencer::FKeyOperation& Operation, ISequencer& InSequencer, TArray<UE::Sequencer::FAddKeyResult>* OutResults = nullptr) override;`
- L71 _protected prototype_ `virtual void GenerateKeysFromPropertyChanged( const FPropertyChangedParams& PropertyChangedParams, UMovieSceneSection* SectionToKey, FGeneratedTrackKeys& OutGeneratedKeys ) override;`
- L73 _protected prototype_ `FWidgetTransform RecomposeTransform(const FWidgetTransform& InTransform, UObject* AnimatedObject, UMovieSceneSection* Section);`
- L75 _protected prototype_ `void ProcessKeyOperation(UObject* ObjectToKey, TArrayView<const UE::Sequencer::FKeySectionOperation> SectionsToKey, ISequencer& InSequencer, FFrameNumber KeyTime, TArray<UE::Sequencer::FAddKeyResult>* OutResults = nullptr);`
- L78 _private member_ `static FName TranslationName;`
- L79 _private member_ `static FName ScaleName;`
- L80 _private member_ `static FName ShearName;`
- L81 _private member_ `static FName AngleName;`
- L82 _private member_ `static FName ChannelXName;`
- L83 _private member_ `static FName ChannelYName;`

#### Free symbols / members of external scopes

- L26 _namespace_ `namespace UE`
- L26 _namespace_ `namespace Sequencer` (scope `UE`)
- L27 _namespace_ `namespace UE`
- L27 _namespace_ `namespace Sequencer` (scope `UE`)
- L28 _namespace_ `namespace UE`
- L28 _namespace_ `namespace Sequencer` (scope `UE`)

### `Source/Editor/UMGEditor/Private/Animation/UMGDetailKeyframeHandler.h` (Private)


#### class `FUMGDetailKeyframeHandler`  
`class FUMGDetailKeyframeHandler : public IDetailKeyframeHandler`  
_L11-28_
- inherits: `IDetailKeyframeHandler`
- L14 _public prototype_ `FUMGDetailKeyframeHandler( TSharedPtr<class FWidgetBlueprintEditor> InBlueprintEditor );`
- L16 _public prototype_ `virtual bool IsPropertyKeyable(const UClass* InObjectClass, const class IPropertyHandle& PropertyHandle) const override;`
- L18 _public prototype_ `virtual bool IsPropertyKeyingEnabled() const override;`
- L20 _public prototype_ `virtual void OnKeyPropertyClicked(const IPropertyHandle& KeyedPropertyHandle) override;`
- L22 _public prototype_ `virtual bool IsPropertyAnimated(const class IPropertyHandle& PropertyHandle, UObject *ParentObject) const override;`
- L24 _public prototype_ `virtual EPropertyKeyedStatus GetPropertyKeyedStatus(const IPropertyHandle& PropertyHandle) const override;`
- L27 _private member_ `TWeakPtr<class FWidgetBlueprintEditor> BlueprintEditor;`

### `Source/Editor/UMGEditor/Private/Animation/WidgetMaterialTrackEditor.h` (Private)


#### class `FWidgetMaterialTrackEditor`  
`class FWidgetMaterialTrackEditor : public FMaterialTrackEditor`  
_L19-39_
- inherits: `FMaterialTrackEditor`
- desc: A specialized material track editor for widget materials
- L24 _public prototype_ `FWidgetMaterialTrackEditor( TSharedRef<ISequencer> InSequencer );`
- L26 _public prototype_ `static TSharedRef<ISequencerTrackEditor> CreateTrackEditor( TSharedRef<ISequencer> OwningSequencer );`
- L32 _public prototype_ `virtual bool SupportsType( TSubclassOf<UMovieSceneTrack> Type ) const override;`
- L38 _protected prototype_ `virtual UMaterialInterface* GetMaterialInterfaceForTrack( FGuid ObjectBinding, UMovieSceneMaterialTrack* MaterialTrack ) override;`

### `Source/Editor/UMGEditor/Private/AssetDefinition_SlateVectorArtData.h` (Private)


#### class `UAssetDefinition_SlateVectorArtData`  
`class UAssetDefinition_SlateVectorArtData : public UAssetDefinitionDefault`  
_L9-23_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L14 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L15 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L16 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L17 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`

### `Source/Editor/UMGEditor/Private/AssetDefinition_WidgetBlueprint.h` (Private)


#### class `UAssetDefinition_WidgetBlueprint`  
`class UAssetDefinition_WidgetBlueprint : public UAssetDefinitionDefault`  
_L11-28_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L16 _public prototype_ `UAssetDefinition_WidgetBlueprint();`
- L20 _public prototype_ `virtual FText GetAssetDisplayName() const override;` — UAssetDefinition Begin
- L21 _public prototype_ `virtual FLinearColor GetAssetColor() const override;`
- L22 _public prototype_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override;`
- L23 _public prototype_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override;`
- L24 _public prototype_ `virtual EAssetCommandResult OpenAssets(const FAssetOpenArgs& OpenArgs) const override;`
- L25 _public prototype_ `virtual EAssetCommandResult PerformAssetDiff(const FAssetDiffArgs& DiffArgs) const override;`
- L26 _public prototype_ `virtual FText GetAssetDescription(const FAssetData& AssetData) const override;`

### `Source/Editor/UMGEditor/Private/AssetDefinition_WidgetBlueprintGeneratedClass.h` (Private)


#### class `UAssetDefinition_WidgetBlueprintGeneratedClass`  
`class UAssetDefinition_WidgetBlueprintGeneratedClass : public UAssetDefinitionDefault`  
_L11-25_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L16 _public prototype_ `UAssetDefinition_WidgetBlueprintGeneratedClass();`
- L20 _public prototype_ `virtual FText GetAssetDisplayName() const override;` — UAssetDefinition Begin
- L21 _public prototype_ `virtual FLinearColor GetAssetColor() const override;`
- L22 _public prototype_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override;`
- L23 _public prototype_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override;`

### `Source/Editor/UMGEditor/Private/BlueprintModes/WidgetDesignerApplicationMode.h` (Private)


#### class `FWidgetDesignerApplicationMode`  
`class FWidgetDesignerApplicationMode : public FWidgetBlueprintApplicationMode`  
_L11-21_
- inherits: `FWidgetBlueprintApplicationMode`
- L14 _public prototype_ `FWidgetDesignerApplicationMode(TSharedPtr<FWidgetBlueprintEditor> InWidgetEditor);`
- L17 _public prototype_ `virtual void RegisterTabFactories(TSharedPtr<FTabManager> InTabManager) override;` — FApplicationMode interface
- L18 _public prototype_ `virtual void PreDeactivateMode() override;`
- L19 _public prototype_ `virtual void PostActivateMode() override;`

### `Source/Editor/UMGEditor/Private/BlueprintModes/WidgetGraphApplicationMode.h` (Private)


#### class `FWidgetGraphApplicationMode`  
`class FWidgetGraphApplicationMode : public FWidgetBlueprintApplicationMode`  
_L11-20_
- inherits: `FWidgetBlueprintApplicationMode`
- L14 _public prototype_ `FWidgetGraphApplicationMode(TSharedPtr<FWidgetBlueprintEditor> InWidgetEditor);`
- L17 _public prototype_ `virtual void RegisterTabFactories(TSharedPtr<FTabManager> InTabManager) override;` — FApplicationMode interface
- L18 _public prototype_ `virtual void PostActivateMode() override;`

### `Source/Editor/UMGEditor/Private/BlueprintModes/WidgetPreviewApplicationMode.h` (Private)


#### class `UE::UMG::Editor::FWidgetPreviewApplicationMode`  
`class FWidgetPreviewApplicationMode : public FWidgetBlueprintApplicationMode`  
_L11-22_
- inherits: `FWidgetBlueprintApplicationMode`
- L14 _public prototype_ `FWidgetPreviewApplicationMode(TSharedPtr<FWidgetBlueprintEditor> InWidgetEditor);`
- L16 _public prototype_ `static bool IsDebugModeEnabled();`
- L19 _public prototype_ `virtual void RegisterTabFactories(TSharedPtr<FTabManager> InTabManager) override;` — FApplicationMode interface
- L20 _public prototype_ `virtual void PostActivateMode() override;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace UMG` (scope `UE`)
- L8 _namespace_ `namespace Editor` (scope `UE::UMG`)

### `Source/Editor/UMGEditor/Private/Customizations/CanvasSlotCustomization.h` (Private)


#### class `FCanvasSlotCustomization`  
`class FCanvasSlotCustomization : public IPropertyTypeCustomization`  
_L18-51_
- inherits: `IPropertyTypeCustomization`
- L22 _public function_ `static TSharedRef<class IPropertyTypeCustomization> MakeInstance(UBlueprint* Blueprint)` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L27 _public function_ `FCanvasSlotCustomization(UBlueprint* InBlueprint) : Blueprint(Cast<UWidgetBlueprint>(InBlueprint))`
- L32 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L34 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> PropertyHandle, class IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L38 _private prototype_ `void CustomizeLayoutData(TSharedRef<IPropertyHandle> PropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils);`
- L39 _private prototype_ `void CustomizeAnchors(TSharedPtr<IPropertyHandle> PropertyHandle, class IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils);`
- L40 _private prototype_ `void CustomizeOffsets(TSharedPtr<IPropertyHandle> PropertyHandle, class IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils);`
- L42 _private prototype_ `void FillOutChildren(TSharedRef<IPropertyHandle> PropertyHandle, class IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils);`
- L44 _private prototype_ `void CreateEditorWithDynamicLabel(IDetailPropertyRow& PropertyRow, TAttribute<FText> TextAttribute);`
- L46 _private prototype_ `static FText GetOffsetLabel(TSharedPtr<IPropertyHandle> AnchorStructureHandle, EOrientation Orientation, FText NonStretchingLabel, FText StretchingLabel);`
- L49 _private member_ `UWidgetBlueprint* Blueprint;`

### `Source/Editor/UMGEditor/Private/Customizations/DynamicEntryBoxDetails.h` (Private)


#### class `FDynamicEntryBoxBaseDetails`  
`class FDynamicEntryBoxBaseDetails : public FDynamicEntryWidgetDetailsBase`  
_L14-30_
- inherits: `FDynamicEntryWidgetDetailsBase`
- L17 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L20 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailLayout) override;` — Main customization of details
- L23 _protected member_ `TWeakObjectPtr<UDynamicEntryBoxBase> EntryBox;`
- L26 _private prototype_ `bool CanEditSpacingPattern() const;`
- L27 _private prototype_ `bool CanEditEntrySpacing() const;`
- L28 _private prototype_ `bool CanEditAlignment() const;`
- L29 _private prototype_ `bool CanEditMaxElementSize() const;`

#### class `FDynamicEntryBoxDetails`  
`class FDynamicEntryBoxDetails : public FDynamicEntryBoxBaseDetails`  
_L36-43_
- inherits: `FDynamicEntryBoxBaseDetails`
- L39 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L42 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailLayout) override;` — Main customization of details

### `Source/Editor/UMGEditor/Private/Customizations/DynamicEntryWidgetDetailsBase.h` (Private)


#### class `FDynamicEntryWidgetDetailsBase`  
`class FDynamicEntryWidgetDetailsBase : public IDetailCustomization`  
_L12-74_
- inherits: `IDetailCustomization`
- desc: Base helper for customizations on widget classes that dynamically generate entries of a given widget class
- L16 _protected function_ `template <typename WidgetT> void AddEntryClassPicker(WidgetT& WidgetInstance, IDetailCategoryBuilder& CategoryBuilder, TSharedRef<IPropertyHandle> InEntryClassHandle)`
- L68 _private prototype_ `void AddEntryClassPickerInternal(const UClass* EntryBaseClass, const UClass* RequiredEntryInterface, IDetailCategoryBuilder& CategoryBuilder) const;`
- L70 _private prototype_ `const UClass* GetSelectedEntryClass() const;`
- L71 _private prototype_ `void HandleNewEntryClassSelected(const UClass* NewEntryClass) const;`
- L73 _private member_ `TSharedPtr<IPropertyHandle> EntryClassHandle;`

### `Source/Editor/UMGEditor/Private/Customizations/HorizontalAlignmentCustomization.h` (Private)


#### class `FHorizontalAlignmentCustomization`  
`class FHorizontalAlignmentCustomization : public IPropertyTypeCustomization`  
_L12-36_
- inherits: `IPropertyTypeCustomization`
- L16 _public function_ `static TSharedRef<class IPropertyTypeCustomization> MakeInstance()` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L21 _public function_ `FHorizontalAlignmentCustomization()`
- L25 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L27 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> PropertyHandle, class IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L29 _public prototype_ `void HandleCheckStateChanged(ECheckBoxState InCheckboxState, TSharedRef<IPropertyHandle> PropertyHandle, EHorizontalAlignment ToAlignment);`
- L31 _public prototype_ `ECheckBoxState GetCheckState(TSharedRef<IPropertyHandle> PropertyHandle, EHorizontalAlignment ForAlignment) const;`
- L33 _public prototype_ `EHorizontalAlignment GetCurrentAlignment(TSharedRef<IPropertyHandle> PropertyHandle) const;`
- L35 _public prototype_ `void OnCurrentAlignmentChanged(EHorizontalAlignment NewAlignment, TSharedRef<IPropertyHandle> PropertyHandle);`

### `Source/Editor/UMGEditor/Private/Customizations/ListViewBaseDetails.h` (Private)


#### class `FListViewBaseDetails`  
`class FListViewBaseDetails : public FDynamicEntryWidgetDetailsBase`  
_L7-13_
- inherits: `FDynamicEntryWidgetDetailsBase`
- L10 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L12 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailLayout) override;`

### `Source/Editor/UMGEditor/Private/Customizations/SlateChildSizeCustomization.h` (Private)


#### class `FSlateChildSizeCustomization`  
`class FSlateChildSizeCustomization : public IPropertyTypeCustomization`  
_L14-40_
- inherits: `IPropertyTypeCustomization`
- L18 _public function_ `static TSharedRef<class IPropertyTypeCustomization> MakeInstance()` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L23 _public function_ `FSlateChildSizeCustomization()`
- L27 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L29 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> PropertyHandle, class IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L31 _public prototype_ `void OnSizeRuleChanged(ESlateSizeRule::Type ToRule, TSharedPtr<IPropertyHandle> PropertyHandle);`
- L33 _public prototype_ `ESlateSizeRule::Type GetCurrentSizeRule(TSharedPtr<IPropertyHandle> PropertyHandle) const;`
- L35 _public prototype_ `TOptional<float> GetValue(TSharedPtr<IPropertyHandle> ValueHandle) const;`
- L37 _public prototype_ `void HandleValueComitted(float NewValue, ETextCommit::Type CommitType, TSharedPtr<IPropertyHandle> ValueHandle);`
- L39 _public prototype_ `EVisibility GetValueVisiblity(TSharedPtr<IPropertyHandle> RuleHandle) const;`

### `Source/Editor/UMGEditor/Private/Customizations/TextJustifyCustomization.h` (Private)


#### class `FTextJustifyCustomization`  
`class FTextJustifyCustomization : public IPropertyTypeCustomization`  
_L11-30_
- inherits: `IPropertyTypeCustomization`
- L15 _public function_ `static TSharedRef<class IPropertyTypeCustomization> MakeInstance()` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L20 _public function_ `FTextJustifyCustomization()`
- L24 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L26 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> PropertyHandle, class IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L28 _public prototype_ `void OnJustificationChanged(ETextJustify::Type NewState, TSharedRef<IPropertyHandle> PropertyHandle);`
- L29 _public prototype_ `ETextJustify::Type GetCurrentJustification(TSharedRef<IPropertyHandle> PropertyHandle) const;`

### `Source/Editor/UMGEditor/Private/Customizations/UIComponentCustomizationExtender.h` (Private)


#### class `FUIComponentCustomizationExtender`  
`class FUIComponentCustomizationExtender : public IBlueprintWidgetCustomizationExtender`  
_L12-26_
- inherits: `IBlueprintWidgetCustomizationExtender`
- L15 _public prototype_ `static TSharedPtr<FUIComponentCustomizationExtender> MakeInstance();`
- L16 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& InDetailLayout, const TArrayView<UWidget*> InWidgets, const TSharedRef<FWidgetBlueprintEditor>& InWidgetBlueprintEditor) override;`
- L20 _private prototype_ `void CustomizeComponentPropertyTypes(TSharedPtr<IDetailsView> InDetailView);`
- L23 _private member_ `TWeakObjectPtr<class UWidget> Widget;` — The selected widget in the details panel.
- L24 _private member_ `TWeakPtr<FWidgetBlueprintEditor> WidgetBlueprintEditor;`
- L25 _private member_ `TArray<TWeakPtr<IDetailsView>> UpdateQueuedForDetailsView;`

### `Source/Editor/UMGEditor/Private/Customizations/UMGDetailCustomizations.h` (Private)


#### class `FBlueprintWidgetCustomization`  
`class FBlueprintWidgetCustomization : public IDetailCustomization`  
_L17-72_
- inherits: `IDetailCustomization`
- desc: Provides the customization for all UWidgets.  Bindings, style disabling...etc.
- L21 _public function_ `static TSharedRef<class IDetailCustomization> MakeInstance(TSharedRef<FWidgetBlueprintEditor> InEditor, UBlueprint* InBlueprint)` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L26 _public function_ `FBlueprintWidgetCustomization(TSharedRef<FWidgetBlueprintEditor> InEditor, UBlueprint* InBlueprint) : Editor(InEditor) , Blueprint(CastChecked<UWidgetBlueprint>(InBlueprint))`
- L33 _public prototype_ `virtual void CustomizeDetails( IDetailLayoutBuilder& DetailLayout ) override;` — IDetailCustomization interface
- L41 _public prototype_ `static TSharedRef<SWidget> MakePropertyBindingWidget(TWeakPtr<FWidgetBlueprintEditor> InEditor, UFunction* SignatureFunction, TSharedRef<IPropertyHandle> InDelegatePropertyHandle, TWeakPtr<IDetailsView> InDetailsView, bool bInGeneratePureBindings, bool bAllowDetailsPanelLegacyBinding, EPropertyBindingMode Mode = EPropertyBindingMode::Extension);`
- L47 _public prototype_ `static bool HasPropertyBindings(TWeakPtr<FWidgetBlueprintEditor> InEditor, const TSharedRef<IPropertyHandle>& InPropertyHandle, bool bOnlyEditableValue = false);` — Whether the property (or its parent property, if this is an array/struct element) currently has bindings. When bOnlyCompilableBindingsFilter is set to true, only bindings which have there Compile flag enable will be considered.
- L49 _public prototype_ `static bool IsBindableEvent(const FProperty* Property);`
- L52 _private prototype_ `void PerformBindingCustomization(IDetailLayoutBuilder& DetailLayout, const TArrayView<UWidget*> Widgets);`
- L54 _private prototype_ `void CreateEventCustomization( IDetailLayoutBuilder& DetailLayout, FDelegateProperty* Property, UWidget* Widget );`
- L56 _private prototype_ `void CreateMulticastEventCustomization(IDetailLayoutBuilder& DetailLayout, FName ThisComponentName, UClass* PropertyClass, FMulticastDelegateProperty* Property);`
- L58 _private prototype_ `void ResetToDefault_RemoveBinding(TSharedPtr<IPropertyHandle> PropertyHandle);`
- L60 _private prototype_ `FReply HandleAddOrViewEventForVariable(const FName EventName, FName PropertyName, TWeakObjectPtr<UClass> PropertyClass);`
- L62 _private prototype_ `int32 HandleAddOrViewIndexForButton(const FName EventName, FName PropertyName) const;`
- L64 _private prototype_ `void PerformAccessibilityCustomization(IDetailLayoutBuilder& DetailLayout);`
- L65 _private prototype_ `void CustomizeAccessibilityProperty(IDetailLayoutBuilder& DetailLayout, const FName& BehaviorPropertyName, const FName& TextPropertyName);`
- L66 _private prototype_ `void PerformCustomizationExtenders(IDetailLayoutBuilder& DetailLayout, const TArrayView<UWidget*> Widgets);`
- L69 _private member_ `TWeakPtr<FWidgetBlueprintEditor> Editor;`
- L70 _private member_ `TWeakObjectPtr<UWidgetBlueprint> Blueprint;`
- L71 _private member_ `bool bCreateMulticastEventCustomizationErrorAdded = false;`

#### enum `FBlueprintWidgetCustomization::EPropertyBindingMode`  
`enum class EPropertyBindingMode`  
_L36-40_
- desc: Make a property binding widget
- L38 _public enumerator_ `Value`
- L39 _public enumerator_ `Extension`

### `Source/Editor/UMGEditor/Private/Customizations/VerticalAlignmentCustomization.h` (Private)


#### class `FVerticalAlignmentCustomization`  
`class FVerticalAlignmentCustomization : public IPropertyTypeCustomization`  
_L14-34_
- inherits: `IPropertyTypeCustomization`
- L18 _public function_ `static TSharedRef<class IPropertyTypeCustomization> MakeInstance()` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L23 _public function_ `FVerticalAlignmentCustomization()`
- L27 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L29 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> PropertyHandle, class IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L31 _public prototype_ `EVerticalAlignment GetCurrentAlignment(TSharedRef<IPropertyHandle> PropertyHandle) const;`
- L33 _public prototype_ `void OnCurrentAlignmentChanged(EVerticalAlignment NewAlignment, TSharedRef<IPropertyHandle> PropertyHandle);`

### `Source/Editor/UMGEditor/Private/Customizations/WidgetChildTypeCustomization.h` (Private)


#### class `FWidgetChildTypeCustomization`  
`class FWidgetChildTypeCustomization : public IPropertyTypeCustomization`  
_L19-58_
- inherits: `IPropertyTypeCustomization`
- L23 _public function_ `static TSharedRef<class IPropertyTypeCustomization> MakeInstance(TSharedRef<FWidgetBlueprintEditor> InEditor)` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L28 _public function_ `FWidgetChildTypeCustomization(TSharedRef<FWidgetBlueprintEditor> InEditor) : Editor(InEditor)`
- L33 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L34 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> PropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L38 _private prototype_ `void SetWidgetChild(UUserWidget* OwnerUserWidget, FName WidgetChildName);`
- L40 _private prototype_ `void OnWidgetSelectionChanged(FName SelectedName, ESelectInfo::Type SelectionType);`
- L42 _private prototype_ `TSharedRef<SWidget> GetPopupContent();`
- L43 _private prototype_ `void HandleMenuOpen();`
- L45 _private prototype_ `UWidget* GetCurrentValue() const;`
- L46 _private prototype_ `FText GetCurrentValueText() const;`
- L50 _private member_ `TWeakPtr<FWidgetBlueprintEditor> Editor;`
- L51 _private member_ `TSharedPtr<SComboButton> WidgetListComboButton;`
- L52 _private member_ `TSharedPtr<SListView<TWeakObjectPtr<UWidget>>> WidgetListView;`
- L53 _private member_ `TSharedPtr<SSearchBox> SearchBox;`
- L55 _private member_ `TWeakPtr<IPropertyHandle> PropertyHandlePtr;`
- L57 _private member_ `TArray<TWeakObjectPtr<UWidget>> ReferenceableWidgets;`

### `Source/Editor/UMGEditor/Private/Customizations/WidgetNavigationCustomization.h` (Private)


#### class `FWidgetNavigationCustomization`  
`class FWidgetNavigationCustomization : public IPropertyTypeCustomization`  
_L15-72_
- inherits: `IPropertyTypeCustomization`
- L19 _public function_ `static TSharedRef<class IPropertyTypeCustomization> MakeInstance(TSharedRef<FWidgetBlueprintEditor> InEditor)` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L24 _public function_ `FWidgetNavigationCustomization(TSharedRef<FWidgetBlueprintEditor> InEditor) : Editor(InEditor)`
- L29 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L31 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> PropertyHandle, class IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L35 _private prototype_ `EUINavigationRule GetNavigationRule(TWeakPtr<IPropertyHandle> PropertyHandle, EUINavigation Nav) const;`
- L36 _private prototype_ `FText GetNavigationText(TWeakPtr<IPropertyHandle> PropertyHandle, EUINavigation Nav) const;`
- L38 _private prototype_ `void MakeNavRow(TWeakPtr<IPropertyHandle> PropertyHandle, IDetailChildrenBuilder& ChildBuilder, EUINavigation Nav, FText NavName);`
- L40 _private prototype_ `TSharedRef<class SWidget> MakeNavMenu(TWeakPtr<IPropertyHandle> PropertyHandle, EUINavigation Nav);`
- L42 _private prototype_ `void HandleNavMenuEntryClicked(TWeakPtr<IPropertyHandle> PropertyHandle, EUINavigation Nav, EUINavigationRule Rule);`
- L44 _private prototype_ `TSharedRef<SWidget> OnGenerateWidgetList(TWeakPtr<IPropertyHandle> PropertyHandle, EUINavigation Nav);`
- L46 _private prototype_ `void HandleSelectedCustomNavigationFunction(FName SelectedFunction, TWeakPtr<IPropertyHandle> PropertyHandle, EUINavigation Nav);`
- L47 _private prototype_ `void HandleResetCustomNavigationFunction(TWeakPtr<IPropertyHandle> PropertyHandle, EUINavigation Nav);`
- L49 _private prototype_ `FText GetExplictWidget(TWeakPtr<IPropertyHandle> PropertyHandle, EUINavigation Nav) const;`
- L50 _private prototype_ `TOptional<FName> GetUniformNavigationTargetOrFunction(TWeakPtr<IPropertyHandle> PropertyHandle, EUINavigation Nav) const;`
- L51 _private prototype_ `void OnWidgetSelectedForExplicitNavigation(FName ExplictWidgetOrFunction, TWeakPtr<IPropertyHandle> PropertyHandle, EUINavigation Nav);`
- L52 _private prototype_ `EVisibility GetCustomWidgetFieldVisibility(TWeakPtr<IPropertyHandle> PropertyHandle, EUINavigation Nav) const;`
- L53 _private prototype_ `EVisibility GetExplictWidgetFieldVisibility(TWeakPtr<IPropertyHandle> PropertyHandle, EUINavigation Nav) const;`
- L55 _private prototype_ `void SetNav(UWidget* Widget, EUINavigation Nav, TOptional<EUINavigationRule> Rule, TOptional<FName> WidgetToFocus);`
- L57 _private prototype_ `bool DoesWidgetSupportRoutingPolicy(TWeakPtr<IPropertyHandle> PropertyHandle) const;`
- L58 _private prototype_ `EWidgetNavigationRoutingPolicy GetRoutingPolicy(TWeakPtr<IPropertyHandle> PropertyHandle) const;`
- L59 _private prototype_ `FText GetRoutingPolicyText(TWeakPtr<IPropertyHandle> PropertyHandle) const;`
- L60 _private prototype_ `TSharedRef<class SWidget> MakeRoutingPolicyMenu(TWeakPtr<IPropertyHandle> PropertyHandle);`
- L61 _private prototype_ `void HandleRoutingPolicyMenuEntryClicked(TWeakPtr<IPropertyHandle> PropertyHandle, EWidgetNavigationRoutingPolicy Policy);`
- L62 _private prototype_ `void SetRoutingPolicy(UWidget* Widget, EWidgetNavigationRoutingPolicy Policy);`
- L64 _private prototype_ `void OnNavigationMethodPrePropertyChange(TWeakPtr<IPropertyHandle> PropertyHandle);`
- L65 _private prototype_ `void MakeNavigationMethodStructPicker(TWeakPtr<IPropertyHandle> PropertyHandle, IDetailChildrenBuilder& ChildBuilder);`
- L66 _private prototype_ `void HandleNavigationMethodStructPicked(TWeakPtr<IPropertyHandle> PropertyHandle, const UScriptStruct* InStruct);`
- L67 _private prototype_ `void SetNavigationMethodStruct(UWidget* Widget, const UScriptStruct* NavigationMethodStruct);`
- L70 _private member_ `TWeakPtr<FWidgetBlueprintEditor> Editor;`
- L71 _private member_ `TSharedPtr<IPropertyUtilities> PropertyUtilities;`

### `Source/Editor/UMGEditor/Private/Customizations/WidgetThumbnailCustomization.h` (Private)


#### class `FWidgetThumbnailCustomization`  
`class FWidgetThumbnailCustomization : public IDetailCustomization`  
_L11-26_
- inherits: `IDetailCustomization`
- desc: UI customization for WidgetBlueprint thumbnail
- L14 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L16 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`
- L20 _private prototype_ `FReply LoadThumbnailFromFile();`
- L21 _private prototype_ `void ClearThumbnail();`
- L22 _private prototype_ `bool IsThumbnailAutomatic() const;`
- L23 _private prototype_ `bool IsThumbnailAutomaticAndCustom() const;`
- L25 _private member_ `TWeakObjectPtr<UWidgetBlueprint> WidgetBlueprint;`

### `Source/Editor/UMGEditor/Private/Customizations/WidgetTypeCustomization.h` (Private)


#### class `FWidgetTypeCustomization`  
`class FWidgetTypeCustomization : public IPropertyTypeCustomization`  
_L18-60_
- inherits: `IPropertyTypeCustomization`
- L22 _public function_ `static TSharedRef<class IPropertyTypeCustomization> MakeInstance(TSharedRef<FWidgetBlueprintEditor> InEditor)` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L27 _public function_ `FWidgetTypeCustomization(TSharedRef<FWidgetBlueprintEditor> InEditor) : Editor(InEditor)`
- L32 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L34 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> PropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L38 _private prototype_ `TSharedRef<SWidget> GetPopupContent();`
- L39 _private prototype_ `void HandleMenuOpen();`
- L41 _private prototype_ `TSharedRef<ITableRow> OnGenerateListItem(TWeakObjectPtr<UWidget> InItem, const TSharedRef<STableViewBase>& OwnerTable);`
- L43 _private prototype_ `void OnSelectionChanged(TWeakObjectPtr<UWidget> InItem, ESelectInfo::Type SelectionInfo);`
- L45 _private prototype_ `UWidget* GetCurrentValue() const;`
- L46 _private prototype_ `FText GetCurrentValueText() const;`
- L48 _private prototype_ `void OnFilterTextChanged(const FText& InFilterText);`
- L52 _private member_ `TWeakPtr<FWidgetBlueprintEditor> Editor;`
- L53 _private member_ `TSharedPtr<SComboButton> WidgetListComboButton;`
- L54 _private member_ `TSharedPtr<SListView<TWeakObjectPtr<UWidget>>> WidgetListView;`
- L55 _private member_ `TSharedPtr<SSearchBox> SearchBox;`
- L57 _private member_ `TWeakPtr<IPropertyHandle> PropertyHandlePtr;`
- L59 _private member_ `TArray<TWeakObjectPtr<UWidget>> ReferenceableWidgets;`

### `Source/Editor/UMGEditor/Private/Designer/DesignTimeUtils.h` (Private)


#### class `FDesignTimeUtils`  
`class FDesignTimeUtils`  
_L15-21_
- desc: A set of utility functions used at design time for the widget blueprint editor.
- L18 _public prototype_ `static bool GetArrangedWidget(TSharedRef<SWidget> Widget, FArrangedWidget& ArrangedWidget);`
- L20 _public prototype_ `static bool GetArrangedWidgetRelativeToWindow(TSharedRef<SWidget> Widget, FArrangedWidget& ArrangedWidget);`

### `Source/Editor/UMGEditor/Private/Designer/DesignerCommands.h` (Private)


#### class `FDesignerCommands`  
`class FDesignerCommands : public TCommands<FDesignerCommands>`  
_L18-56_
- inherits: `TCommands<FDesignerCommands>`
- L21 _public function_ `FDesignerCommands() : TCommands<FDesignerCommands> ( TEXT("WidgetDesigner"),`
- L33 _public member_ `TSharedPtr< FUICommandInfo > LayoutTransform;` — Layout Mode
- L36 _public member_ `TSharedPtr< FUICommandInfo > RenderTransform;` — Render Mode
- L39 _public member_ `TSharedPtr< FUICommandInfo > LocationGridSnap;` — Enables or disables snapping to the grid when dragging objects around
- L42 _public member_ `TSharedPtr< FUICommandInfo > RotationGridSnap;` — Enables or disables snapping to a grid when rotating objects
- L45 _public member_ `TSharedPtr< FUICommandInfo > ToggleOutlines;` — Toggle Showing Outlines
- L48 _public member_ `TSharedPtr< FUICommandInfo > ToggleRespectLocks;` — Toggle if we care about locking
- L51 _public member_ `TSharedPtr< FUICommandInfo > ToggleLocalizationPreview;` — Toggle the localization preview on/off
- L55 _public prototype_ `virtual void RegisterCommands() override;` — Registers our commands with the binding system

### `Source/Editor/UMGEditor/Private/Designer/SDesignerToolBar.h` (Private)


#### class `SDesignerToolBar`  
`class SDesignerToolBar : public SViewportToolBar`  
_L23-62_
- inherits: `SViewportToolBar`
- L26 _public function_ `SLATE_BEGIN_ARGS( SDesignerToolBar )`
- L27 _public prototype_ `SLATE_ARGUMENT( TSharedPtr<FUICommandList>, CommandList ) SLATE_ARGUMENT( TSharedPtr<FExtender>, Extenders ) SLATE_END_ARGS() void Construct( const FArguments& InArgs );`
- L38 _public prototype_ `TSharedRef< SWidget > MakeToolBar( const TSharedPtr< FExtender > InExtenders );` — Static: Creates a widget for the main tool bar @return	New widget
- L42 _private prototype_ `ECheckBoxState IsLocationGridSnapChecked() const;`
- L43 _private prototype_ `void HandleToggleLocationGridSnap(ECheckBoxState InState);`
- L44 _private prototype_ `FText GetLocationGridLabel() const;`
- L45 _private prototype_ `TSharedRef<SWidget> FillLocationGridSnapMenu();`
- L46 _private prototype_ `static void SetGridSize(int32 InGridSize);`
- L47 _private prototype_ `static bool IsGridSizeChecked(int32 InGridSnapSize);`
- L51 _private prototype_ `ECheckBoxState IsLocalizationPreviewChecked() const;`
- L52 _private prototype_ `void HandleToggleLocalizationPreview(ECheckBoxState InState);`
- L53 _private prototype_ `FText GetLocalizationPreviewLabel() const;`
- L54 _private prototype_ `TSharedRef<SWidget> FillLocalizationPreviewMenu();`
- L55 _private prototype_ `static void SetLocalizationPreviewLanguage(FString InCulture);`
- L56 _private prototype_ `static bool IsLocalizationPreviewLanguageChecked(FString InCulture);`
- L57 _private prototype_ `static void OpenRegionAndLanguageSettings();`
- L61 _private member_ `TSharedPtr<FUICommandList> CommandList;` — Command list

### `Source/Editor/UMGEditor/Private/Designer/SDisappearingBar.h` (Private)


#### class `SDisappearingBar`  
`class SDisappearingBar : public SCompoundWidget`  
_L20-43_
- inherits: `SCompoundWidget`
- desc: A widget that shows another widget as long as the mouse isn't hovering over it.
- L24 _public function_ `SLATE_BEGIN_ARGS(SDisappearingBar)`
- L30 _public prototype_ `SLATE_DEFAULT_SLOT(FArguments, Content) SLATE_END_ARGS() void Construct(const FArguments& InArgs);` — Slot for this designers content (optional)
- L36 _public prototype_ `virtual void OnDragEnter( const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent ) override;`
- L37 _public prototype_ `virtual void OnDragLeave( const FDragDropEvent& DragDropEvent ) override;`
- L40 _private prototype_ `FLinearColor GetFadeColorAndOpacity() const;`
- L42 _private member_ `FCurveSequence FadeCurve;`

### `Source/Editor/UMGEditor/Private/Designer/SPaintSurface.h` (Private)


#### struct `FOnPaintHandlerParams`  
`struct FOnPaintHandlerParams`  
_L13-32_
- L15 _public member_ `const FPaintArgs& Args;`
- L16 _public member_ `const FGeometry& Geometry;`
- L17 _public member_ `const FSlateRect& ClippingRect;`
- L18 _public member_ `FSlateWindowElementList& OutDrawElements;`
- L19 _public member_ `const int32 Layer;`
- L20 _public member_ `const bool bEnabled;`
- L22 _public function_ `FOnPaintHandlerParams(const FPaintArgs& InArgs, const FGeometry& InGeometry, const FSlateRect& InClippingRect, FSlateWindowElementList& InOutDrawElements, int32 InLayer, bool bInEnabled ) : Args(InArgs) , Geometry( InGeometry ) , ClippingRect( InClippingRect ) , OutDrawElements( InOutDrawElements ) , Layer( InLayer ) , bEnabled( bInEnabled )`

#### class `SPaintSurface`  
`class SPaintSurface : public SCompoundWidget`  
_L44-92_
- inherits: `SCompoundWidget`
- desc: Widget with a handler for OnPaint, allows the designer to insert painting on different layers of the overlay when drawing widgets and effects intermixed.
- L47 _public function_ `SLATE_BEGIN_ARGS( SPaintSurface ) : _OnPaintHandler()`
- L53 _public function_ `SLATE_EVENT( FOnPaintHandler, OnPaintHandler ) SLATE_END_ARGS() void Construct(const FArguments& InArgs)`
- L66 _public function_ `virtual FVector2D ComputeDesiredSize(float) const override`
- L71 _public function_ `virtual int32 OnPaint( const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled ) const override`
- L91 _private member_ `FOnPaintHandler OnPaintHandler;`

#### Free symbols / members of external scopes

- L35 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam( int32, FOnPaintHandler, const FOnPaintHandlerParams& );` — Delegate type for allowing custom OnPaint handlers
- L35 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam( int32, FOnPaintHandler, const FOnPaintHandlerParams& );` — Delegate type for allowing custom OnPaint handlers

### `Source/Editor/UMGEditor/Private/Designer/SRuler.h` (Private)


#### class `SRuler`  
`class SRuler : public SCompoundWidget`  
_L22-106_
- inherits: `SCompoundWidget`
- L26 _public function_ `SLATE_BEGIN_ARGS(SRuler) : _Orientation(Orient_Horizontal) , _OnMouseButtonDown()`
- L33 _public prototype_ `SLATE_ARGUMENT(EOrientation, Orientation) SLATE_EVENT(FPointerEventHandler, OnMouseButtonDown) SLATE_END_ARGS() void Construct( const FArguments& InArgs );`
- L56 _public prototype_ `float DetermineOptimalSpacing(float InPixelsPerInput, uint32 MinTick, float MinTickSpacing) const;` — Determines the optimal spacing between tick marks in the slider for a given pixel density Increments until a minimum amount of slate units specified by MinTick is reached @param InPixelsPerInput	The density of pixels between each input @param MinTick			The minimum slate units per tick allowed @param MinTickSpacing	The minimum tick spacing in time units allowed @return the optimal spacing in time units
- L65 _public prototype_ `void SetRuling(FVector2D AbsoluteOrigin, float SlateToUnitScale);` — Sets the rules to use when rendering the ruler. @param AbsoluteOrigin The origin of the ruler in absolute window space. @param SlateToUnitScale The scaler applied to slate units to get the same number of units currently being displayed by the rule marks.
- L72 _public prototype_ `void SetCursor(TOptional<FVector2D> AbsoluteCursor);` — Sets the cursor position in window absolute space. @param AbsoluteCursor The position of the cursor in absolute window space.
- L76 _protected prototype_ `virtual FVector2D ComputeDesiredSize(float) const override;` — SWidget interface
- L77 _protected prototype_ `virtual int32 OnPaint( const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled ) const override;`
- L78 _protected prototype_ `virtual FReply OnMouseButtonDown( const FGeometry& MyGeometry, const FPointerEvent& MouseEvent ) override;`
- L79 _protected prototype_ `virtual FReply OnMouseButtonUp( const FGeometry& MyGeometry, const FPointerEvent& MouseEvent ) override;`
- L80 _protected prototype_ `virtual FReply OnMouseMove( const FGeometry& MyGeometry, const FPointerEvent& MouseEvent ) override;`
- L81 _protected prototype_ `virtual FReply OnMouseWheel( const FGeometry& MyGeometry, const FPointerEvent& MouseEvent ) override;`
- L89 _private prototype_ `int32 DrawTicks(FSlateWindowElementList& OutDrawElements, const FScrubRangeToScreen& RangeToScreen, FDrawTickArgs& InArgs) const;` — Draws the ticks on the track
- L93 _private member_ `EOrientation Orientation;` — The orientation of the ruler
- L96 _private member_ `FVector2D AbsoluteOrigin;` — The absolute origin of the document being measured.  The 0 on the ruler will start here.
- L99 _private member_ `TOptional<FVector2D> AbsoluteCursor;` — The absolute position of the cursor so that little lines can be drawn showing the cursors position on the ruler.
- L102 _private member_ `float SlateToUnitScale;` — The current conversion from Slate Pixel To Unit Size.
- L105 _private member_ `FPointerEventHandler MouseButtonDownHandler;` — The public event we expose when the mouse button is pressed onto the ruler.

### `Source/Editor/UMGEditor/Private/Designer/STransformHandle.h` (Private)


#### enum `ETransformDirection::Type`  
`enum Type`  
_L21-35_
- L23 _public enumerator_ `TopLeft = 0`
- L24 _public enumerator_ `TopCenter`
- L25 _public enumerator_ `TopRight`
- L27 _public enumerator_ `CenterLeft`
- L28 _public enumerator_ `CenterRight`
- L30 _public enumerator_ `BottomLeft`
- L31 _public enumerator_ `BottomCenter`
- L32 _public enumerator_ `BottomRight`
- L34 _public enumerator_ `MAX`

#### enum `ETransformAction`  
`enum class ETransformAction`  
_L39-44_
- L41 _public enumerator_ `None`
- L42 _public enumerator_ `Primary`
- L43 _public enumerator_ `Secondary`

#### class `STransformHandle`  
`class STransformHandle : public SCompoundWidget`  
_L46-86_
- inherits: `SCompoundWidget`
- L50 _public function_ `SLATE_BEGIN_ARGS(STransformHandle)`
- L51 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, IUMGDesigner* InDesigner, ETransformDirection::Type InTransformDirection);`
- L56 _public prototype_ `virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;` — SWidget interface
- L57 _public prototype_ `virtual FReply OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L58 _public prototype_ `virtual FReply OnMouseMove(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L59 _public prototype_ `virtual FCursorReply OnCursorQuery(const FGeometry& MyGeometry, const FPointerEvent& CursorEvent) const override;`
- L63 _protected prototype_ `EVisibility GetHandleVisibility() const;`
- L65 _protected prototype_ `bool CanResize(UPanelSlot* Slot, const FVector2D& Direction) const;`
- L66 _protected prototype_ `void Resize(UCanvasPanelSlot* Slot, const FVector2D& Direction, const FVector2D& Amount);`
- L68 _protected prototype_ `ETransformAction ComputeActionAtLocation(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) const;`
- L71 _protected prototype_ `FVector2D ComputeDragDirection(ETransformDirection::Type InTransformDirection) const;`
- L72 _protected prototype_ `FVector2D ComputeOrigin(ETransformDirection::Type InTransformDirection) const;`
- L75 _protected member_ `IUMGDesigner* Designer;`
- L76 _protected member_ `ETransformDirection::Type TransformDirection;`
- L77 _protected member_ `ETransformAction Action;`
- L79 _protected member_ `FVector2D DragDirection;`
- L80 _protected member_ `FVector2D DragOrigin;`
- L82 _protected member_ `FVector2D MouseDownPosition;`
- L83 _protected member_ `FMargin StartingOffsets;`
- L85 _protected member_ `class FScopedTransaction* ScopedTransaction;`

#### Free symbols / members of external scopes

- L19 _namespace_ `namespace ETransformDirection`

### `Source/Editor/UMGEditor/Private/Details/DetailWidgetExtensionHandler.h` (Private)


#### class `FDetailWidgetExtensionHandler`  
`class FDetailWidgetExtensionHandler : public IDetailPropertyExtensionHandler`  
_L10-25_
- inherits: `IDetailPropertyExtensionHandler`
- L13 _public prototype_ `FDetailWidgetExtensionHandler(TSharedPtr<FWidgetBlueprintEditor> InBlueprintEditor);`
- L15 _public prototype_ `virtual bool IsPropertyExtendable(const UClass* InObjectClass, const IPropertyHandle& PropertyHandle) const override;`
- L17 _public prototype_ `virtual void ExtendWidgetRow( FDetailWidgetRow& InWidgetRow, const IDetailLayoutBuilder& InDetailBuilder, const UClass* InObjectClass, TSharedPtr<IPropertyHandle> PropertyHandle) override;`
- L24 _private member_ `TWeakPtr<FWidgetBlueprintEditor> BlueprintEditor;`

### `Source/Editor/UMGEditor/Private/Details/SFunctionSelector.h` (Private)


#### class `SFunctionSelector`  
`class SFunctionSelector : public SCompoundWidget`  
_L20-81_
- inherits: `SCompoundWidget`
- L23 _public prototype_ `DECLARE_DELEGATE_OneParam(FFunctionDelegate, FName );`
- L24 _public prototype_ `DECLARE_DELEGATE(FResetDelegate);`
- L26 _public function_ `SLATE_BEGIN_ARGS(SFunctionSelector)`
- L29 _public prototype_ `SLATE_ATTRIBUTE(TOptional<FName>, CurrentFunction) SLATE_EVENT(FFunctionDelegate, OnSelectedFunction) SLATE_EVENT(FResetDelegate, OnResetFunction) SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedRef<FWidgetBlueprintEditor> InEditor, UFunction* InAllowedSignature);`
- L50 _protected prototype_ `TSharedRef<SWidget> OnGenerateDelegateMenu();`
- L51 _protected prototype_ `void FillPropertyMenu(FMenuBuilder& MenuBuilder, UStruct* OwnerStruct);`
- L53 _protected prototype_ `FText GetCurrentBindingText() const;`
- L55 _protected prototype_ `bool CanReset();`
- L56 _protected prototype_ `void HandleRemoveBinding();`
- L58 _protected prototype_ `void HandleAddFunctionBinding(TSharedPtr<FFunctionInfo> SelectedFunction);`
- L60 _protected prototype_ `void HandleCreateAndAddBinding();`
- L61 _protected prototype_ `void GotoFunction(UEdGraph* FunctionGraph);`
- L63 _protected prototype_ `EVisibility GetGotoBindingVisibility() const;`
- L65 _protected prototype_ `FReply HandleGotoBindingClicked();`
- L70 _private prototype_ `template <typename Predicate> void ForEachBindableFunction(UClass* FromClass, Predicate Pred) const;`
- L72 _private member_ `TAttribute<TOptional<FName>> CurrentFunction;`
- L74 _private member_ `FFunctionDelegate SelectedFunctionEvent;`
- L75 _private member_ `FResetDelegate ResetFunctionEvent;`
- L77 _private member_ `TWeakPtr<FWidgetBlueprintEditor> Editor;`
- L78 _private member_ `UWidgetBlueprint* Blueprint;`
- L80 _private member_ `UFunction* BindableSignature;`

#### struct `SFunctionSelector::FFunctionInfo`  
`struct FFunctionInfo`  
_L39-48_
- L41 _public function_ `FFunctionInfo()`
- L45 _public member_ `FName FuncName;`
- L46 _public member_ `FText DisplayName;`
- L47 _public member_ `FString Tooltip;`

#### Free symbols / members of external scopes

- L23 _delegate_ `DECLARE_DELEGATE_OneParam(FFunctionDelegate, FName );`
- L24 _delegate_ `DECLARE_DELEGATE(FResetDelegate);`

### `Source/Editor/UMGEditor/Private/Details/SUIComponentView.h` (Private)


#### class `SUIComponentView`  
`class SUIComponentView final : public SCompoundWidget`  
_L17-51_
- inherits: `SCompoundWidget`
- L20 _public function_ `SLATE_BEGIN_ARGS(SUIComponentView)`
- L23 _public prototype_ `~SUIComponentView();`
- L25 _public prototype_ `void Construct(const FArguments& InArgs, TSharedPtr<FWidgetBlueprintEditor> InBlueprintEditor);`
- L26 _public prototype_ `void CreateCommandList();`
- L28 _public prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;`
- L31 _private prototype_ `void OnEditorSelectionChanged();`
- L32 _private prototype_ `void OnWidgetPreviewReady();`
- L33 _private prototype_ `void OnWidgetBlueprintTransaction();`
- L35 _private prototype_ `FReply OnAddComponentButtonClicked();`
- L37 _private prototype_ `TSharedPtr<SWidget> OnContextMenuOpening();`
- L39 _private prototype_ `bool CanExecuteDeleteSelectedComponent() const;`
- L40 _private prototype_ `void OnDeleteSelectedComponent();`
- L42 _private prototype_ `TSharedRef<ITableRow> OnGenerateWidgetForComponent(TSharedPtr<FUIComponentListItem> InListItem, const TSharedRef< STableViewBase >& InOwnerTableView);`
- L44 _private prototype_ `UWidget* GetSelectedWidget() const;`
- L45 _private prototype_ `void UpdateComponentList();`
- L47 _private member_ `TSharedPtr<FUICommandList> CommandList;`
- L48 _private member_ `TWeakPtr<FWidgetBlueprintEditor> BlueprintEditor;`
- L49 _private member_ `TSharedPtr<SUIComponentListView> ComponentListView;`
- L50 _private member_ `TArray<TSharedPtr<FUIComponentListItem> > Components;`

#### Free symbols / members of external scopes

- L15 _typedef_ `typedef SListView<TSharedPtr<FUIComponentListItem> > SUIComponentListView;`

### `Source/Editor/UMGEditor/Private/Details/SWidgetDetailsView.h` (Private)


#### class `SWidgetDetailsView`  
`class SWidgetDetailsView : public SCompoundWidget, public FNotifyHook`  
_L19-100_
- inherits: `SCompoundWidget,FNotifyHook`
- desc: The details view used in the designer section of the widget blueprint editor.
- L22 _public function_ `SLATE_BEGIN_ARGS( SWidgetDetailsView )`
- L23 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedPtr<FWidgetBlueprintEditor> InBlueprintEditor);`
- L26 _public prototype_ `virtual ~SWidgetDetailsView();`
- L29 _public function_ `TSharedPtr<class IDetailsView> GetPropertyView() const` — Gets the property view for this details panel
- L32 _public prototype_ `virtual void NotifyPreChange(FEditPropertyChain* PropertyAboutToChange) override;` — FNotifyHook interface
- L33 _public prototype_ `virtual void NotifyPostChange(const FPropertyChangedEvent& PropertyChangedEvent, FEditPropertyChain* PropertyThatChanged) override;`
- L38 _private prototype_ `void RegisterCustomizations();` — Registers the designer specific customizations
- L41 _private prototype_ `void OnEditorSelectionChanging();` — Handles the widget selection changing event in the editor, updates the details panel accordingly.
- L44 _private prototype_ `void OnEditorSelectionChanged();` — Handles the widget selection changed event in the editor, updates the details panel accordingly.
- L47 _private prototype_ `void OnPropertyViewObjectArrayChanged(const FString& InTitle, const TArray<UObject*>& InObjects);` — Handles the callback from the property detail view confirming the list of objects being edited has changed
- L49 _private prototype_ `bool IsDetailsPanelEditingAllowed() const;`
- L51 _private prototype_ `bool IsWidgetNameFieldEnabled() const;`
- L53 _private prototype_ `void ClearFocusIfOwned();`
- L55 _private prototype_ `bool IsPropertyVisible(const FPropertyAndParent& PropertyAndParent) const;`
- L57 _private prototype_ `bool IsWidgetCDOSelected() const;`
- L59 _private prototype_ `EVisibility GetNameAreaVisibility() const;`
- L61 _private prototype_ `EVisibility GetComponentAreaVisibility() const;`
- L63 _private prototype_ `const FSlateBrush* GetNameIcon() const;`
- L65 _private prototype_ `FText GetNameText() const;`
- L67 _private prototype_ `bool IsSingleObjectSelected() const;`
- L69 _private prototype_ `bool HandleVerifyNameTextChanged(const FText& InText, FText& OutErrorMessage);`
- L71 _private prototype_ `void HandleNameTextChanged(const FText& Text);`
- L72 _private prototype_ `void HandleNameTextCommitted(const FText& Text, ETextCommit::Type CommitType);`
- L74 _private prototype_ `ECheckBoxState GetIsVariable() const;`
- L76 _private prototype_ `void HandleIsVariableChanged(ECheckBoxState CheckState);`
- L78 _private prototype_ `EVisibility GetCategoryAreaVisibility() const;`
- L79 _private prototype_ `FText GetCategoryText() const;`
- L80 _private prototype_ `void HandleCategoryTextCommitted(const FText& Text, ETextCommit::Type CommitType);`
- L84 _private member_ `TWeakPtr<class FWidgetBlueprintEditor> BlueprintEditor;` — The editor that owns this details view
- L87 _private member_ `TSharedPtr<SWidget> BorderArea;` — The container widget for the class link users can click to open another asset
- L90 _private member_ `TSharedPtr<SEditableTextBox> NameTextBox;` — The name text box that users can use to rename their widgets
- L93 _private member_ `TSharedPtr<SBox> ClassLinkArea;` — The container widget for the class link users can click to open another asset
- L96 _private member_ `TSharedPtr<class IDetailsView> PropertyView;` — Property viewing widget
- L99 _private member_ `TArray< TWeakObjectPtr<UObject> > SelectedObjects;` — Selected objects for this detail view

### `Source/Editor/UMGEditor/Private/Details/WidgetPropertyDragDropHandler.h` (Private)


#### class `FWidgetPropertyDragDropHandler`  
`class FWidgetPropertyDragDropHandler : public IDetailDragDropHandler`  
_L15-32_
- inherits: `IDetailDragDropHandler`
- desc: Handler for customizing the drag-and-drop behavior for function entry/result pins, allowing parameters to be reordered
- L18 _public prototype_ `FWidgetPropertyDragDropHandler(UWidget* InWidget, TSharedPtr<IPropertyHandle> InPropertyHandle, UWidgetBlueprint* InWidgetBP);`
- L20 _public prototype_ `virtual TSharedPtr<FDragDropOperation> CreateDragDropOperation() const override;`
- L22 _public prototype_ `static int32 ComputeNewIndex(int32 OriginalIndex, int32 DropOntoIndex, EItemDropZone DropZone);`
- L24 _public prototype_ `virtual bool AcceptDrop(const FDragDropEvent& DragDropEvent, EItemDropZone DropZone) const override;`
- L26 _public prototype_ `virtual TOptional<EItemDropZone> CanAcceptDrop(const FDragDropEvent& DragDropEvent, EItemDropZone DropZone) const override;`
- L29 _private member_ `TSharedPtr<IPropertyHandle> PropertyHandle;`
- L30 _private member_ `TWeakObjectPtr<UWidget> OwnerWidget;`
- L31 _private member_ `TWeakObjectPtr<UWidgetBlueprint> WidgetBP;`

### `Source/Editor/UMGEditor/Private/DragDrop/SelectedWidgetDragDropOp.h` (Private)


#### class `FSelectedWidgetDragDropOp`  
`class FSelectedWidgetDragDropOp : public FDecoratedDragDropOp`  
_L18-65_
- inherits: `FDecoratedDragDropOp`
- desc: This drag drop operation allows widget Selected in the viewport to be dragged and dropped into the designer.
- L21 _public prototype_ `DRAG_DROP_OPERATOR_TYPE(FSelectedWidgetDragDropOp, FDecoratedDragDropOp);`
- L23 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnDragDropEnded);`
- L24 _public member_ `FOnDragDropEnded OnDragDropEnded;`
- L26 _public prototype_ `virtual ~FSelectedWidgetDragDropOp();`
- L28 _public prototype_ `virtual void OnDrop(bool bDropWasHandled, const FPointerEvent& MouseEvent) override;`
- L58 _public member_ `TArray<FItem> DraggedWidgets;`
- L60 _public member_ `bool bShowingMessage;`
- L62 _public member_ `IUMGDesigner* Designer;`
- L64 _public prototype_ `static TSharedRef<FSelectedWidgetDragDropOp> New(TSharedPtr<FWidgetBlueprintEditor> Editor, IUMGDesigner* InDesigner, const TArray<FDraggingWidgetReference>& InWidgets);`

#### struct `FSelectedWidgetDragDropOp::FDraggingWidgetReference`  
`struct FDraggingWidgetReference`  
_L30-35_
- L32 _public member_ `FWidgetReference Widget;`
- L34 _public member_ `FVector2D DraggedOffset;`

#### struct `FSelectedWidgetDragDropOp::FItem`  
`struct FItem`  
_L37-56_
- L40 _public member_ `TMap<FName, FString> ExportedSlotProperties;` — The slot properties for the old slot the widget was in, is used to attempt to reapply the same layout information
- L43 _public member_ `UWidget* Template;` — The widget being dragged
- L46 _public member_ `UWidget* Preview;` — The preview widget being dragged
- L49 _public member_ `bool bStayingInParent;` — Can the drag drop change the widget's parent?
- L52 _public member_ `FWidgetReference ParentWidget;` — The original parent of the widget.
- L55 _public member_ `FVector2D DraggedOffset;` — The offset of the original click location, as a percentage of the widget's size.

#### Free symbols / members of external scopes

- L23 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnDragDropEnded);`

### `Source/Editor/UMGEditor/Private/Extensions/CanvasSlotExtension.h` (Private)


#### enum `EAnchorWidget`  
`enum class EAnchorWidget : uint8`  
_L19-32_
- desc: Set of anchor widget types
- L21 _public enumerator_ `Center`
- L22 _public enumerator_ `Left`
- L23 _public enumerator_ `Right`
- L24 _public enumerator_ `Top`
- L25 _public enumerator_ `Bottom`
- L26 _public enumerator_ `TopLeft`
- L27 _public enumerator_ `TopRight`
- L28 _public enumerator_ `BottomLeft`
- L29 _public enumerator_ `BottomRight`
- L31 _public enumerator_ `Count`

#### class `FCanvasSlotExtension`  
`class FCanvasSlotExtension : public FDesignerExtension`  
_L37-90_
- inherits: `FDesignerExtension`
- desc: The canvas slot extension provides design time widgets for widgets that are selected in the canvas.
- L40 _public prototype_ `FCanvasSlotExtension();`
- L42 _public prototype_ `virtual ~FCanvasSlotExtension() = default;`
- L44 _public prototype_ `virtual bool CanExtendSelection(const TArray< FWidgetReference >& Selection) const override;`
- L46 _public prototype_ `virtual void ExtendSelection(const TArray< FWidgetReference >& Selection, TArray< TSharedRef<FDesignerSurfaceElement> >& SurfaceElements) override;`
- L47 _public prototype_ `virtual void Paint(const TSet< FWidgetReference >& Selection, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId) const override;`
- L51 _private prototype_ `FReply HandleAnchorBeginDrag(const FGeometry& Geometry, const FPointerEvent& Event, EAnchorWidget AnchorType);`
- L52 _private prototype_ `FReply HandleAnchorEndDrag(const FGeometry& Geometry, const FPointerEvent& Event, EAnchorWidget AnchorType);`
- L53 _private prototype_ `FReply HandleAnchorDragging(const FGeometry& Geometry, const FPointerEvent& Event, EAnchorWidget AnchorType);`
- L55 _private prototype_ `TSharedRef<SWidget> MakeAnchorWidget(EAnchorWidget AnchorType, float Width, float Height);`
- L57 _private prototype_ `void OnMouseEnterAnchor();`
- L58 _private prototype_ `void OnMouseLeaveAnchor();`
- L60 _private prototype_ `const FSlateBrush* GetAnchorBrush(EAnchorWidget AnchorType) const;`
- L61 _private prototype_ `EVisibility GetAnchorVisibility(EAnchorWidget AnchorType) const;`
- L62 _private prototype_ `FVector2D GetAnchorAlignment(EAnchorWidget AnchorType) const;`
- L64 _private prototype_ `static bool GetCollisionSegmentsForSlot(UCanvasPanel* Canvas, int32 SlotIndex, TArray<FVector2D>& Segments);`
- L65 _private prototype_ `static bool GetCollisionSegmentsForSlot(UCanvasPanel* Canvas, UCanvasPanelSlot* Slot, TArray<FVector2D>& Segments);`
- L66 _private prototype_ `static void GetCollisionSegmentsFromGeometry(FGeometry ArrangedGeometry, TArray<FVector2D>& Segments);`
- L68 _private prototype_ `void PaintCollisionLines(const TSet< FWidgetReference >& Selection, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId) const;`
- L69 _private prototype_ `void PaintDragPercentages(const TSet< FWidgetReference >& Selection, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId) const;`
- L70 _private prototype_ `void PaintLineWithText(FVector2D Start, FVector2D End, FText Text, FVector2D TextTransform, bool InHorizontalLine, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId) const;`
- L72 _private prototype_ `void ProximitySnapValue(float SnapFrequency, float SnapProximity, FVector2D::FReal& Value);`
- L77 _private member_ `TArray< TSharedPtr<SWidget> > AnchorWidgets;`
- L80 _private member_ `bool bMovingAnchor;`
- L83 _private member_ `bool bHoveringAnchor;`
- L86 _private member_ `FVector2D MouseDownPosition;`
- L89 _private member_ `FAnchors BeginAnchors;`

### `Source/Editor/UMGEditor/Private/Extensions/GridSlotExtension.h` (Private)


#### class `FGridSlotExtension`  
`class FGridSlotExtension : public FDesignerExtension`  
_L14-32_
- inherits: `FDesignerExtension`
- L17 _public prototype_ `FGridSlotExtension();`
- L19 _public prototype_ `virtual ~FGridSlotExtension() = default;`
- L21 _public prototype_ `virtual bool CanExtendSelection(const TArray< FWidgetReference >& Selection) const override;`
- L23 _public prototype_ `virtual void ExtendSelection(const TArray< FWidgetReference >& Selection, TArray< TSharedRef<FDesignerSurfaceElement> >& SurfaceElements) override;`
- L27 _private prototype_ `FReply HandleShiftRow(int32 ShiftAmount);`
- L28 _private prototype_ `FReply HandleShiftColumn(int32 ShiftAmount);`
- L30 _private prototype_ `void ShiftRow(UWidget* Widget, int32 ShiftAmount);`
- L31 _private prototype_ `void ShiftColumn(UWidget* Widget, int32 ShiftAmount);`

### `Source/Editor/UMGEditor/Private/Extensions/HorizontalSlotExtension.h` (Private)


#### class `FHorizontalSlotExtension`  
`class FHorizontalSlotExtension : public FDesignerExtension`  
_L10-28_
- inherits: `FDesignerExtension`
- L13 _public prototype_ `FHorizontalSlotExtension();`
- L15 _public prototype_ `virtual ~FHorizontalSlotExtension() = default;`
- L17 _public prototype_ `virtual bool CanExtendSelection(const TArray< FWidgetReference >& Selection) const override;`
- L19 _public prototype_ `virtual void ExtendSelection(const TArray< FWidgetReference >& Selection, TArray< TSharedRef<FDesignerSurfaceElement> >& SurfaceElements) override;`
- L23 _private prototype_ `bool CanShift(int32 ShiftAmount) const;`
- L25 _private prototype_ `FReply HandleShift(int32 ShiftAmount);`
- L27 _private prototype_ `void ShiftHorizontal(UWidget* Widget, int32 ShiftAmount);`

### `Source/Editor/UMGEditor/Private/Extensions/StackBoxSlotExtension.h` (Private)


#### class `FStackBoxSlotExtension`  
`class FStackBoxSlotExtension : public FDesignerExtension`  
_L10-23_
- inherits: `FDesignerExtension`
- L13 _public prototype_ `FStackBoxSlotExtension();`
- L15 _public prototype_ `virtual ~FStackBoxSlotExtension() = default;`
- L17 _public prototype_ `virtual bool CanExtendSelection(const TArray< FWidgetReference >& Selection) const override;`
- L18 _public prototype_ `virtual void ExtendSelection(const TArray< FWidgetReference >& Selection, TArray< TSharedRef<FDesignerSurfaceElement> >& SurfaceElements) override;`
- L21 _private prototype_ `FReply HandleShiftDirection(int32 ShiftAmount);`
- L22 _private prototype_ `void ShiftDirection(UWidget* Widget, int32 ShiftAmount);`

### `Source/Editor/UMGEditor/Private/Extensions/UIComponentContainerDesignerExtension.h` (Private)


#### class `FUIComponentContainerDesignerExtensionFactory`  
`class FUIComponentContainerDesignerExtensionFactory : public IDesignerExtensionFactory, public TSharedFromThis<FUIComponentContainerDesignerExtensionFactory>`  
_L8-15_
- inherits: `IDesignerExtensionFactory,TSharedFromThis<FUIComponentContainerDesignerExtensionFactory>`
- L11 _public prototype_ `FUIComponentContainerDesignerExtensionFactory() = default;`
- L12 _public prototype_ `virtual ~FUIComponentContainerDesignerExtensionFactory() = default;`
- L14 _public prototype_ `virtual TSharedRef<FDesignerExtension> CreateDesignerExtension() const override;`

#### class `FUIComponentContainerDesignerExtension`  
`class FUIComponentContainerDesignerExtension : public FDesignerExtension`  
_L17-22_
- inherits: `FDesignerExtension`
- L20 _public prototype_ `virtual void PreviewContentCreated(UUserWidget* PreviewWidget) override;`
- L21 _public prototype_ `virtual void PreviewContentChanged(TSharedRef<SWidget> NewContent) override;`

### `Source/Editor/UMGEditor/Private/Extensions/UIComponents/NavigationUIComponentCustomization.h` (Private)


#### class `FNavigationUIComponentCustomization`  
`class FNavigationUIComponentCustomization : public IPropertyTypeCustomization`  
_L15-43_
- inherits: `IPropertyTypeCustomization`
- L18 _public function_ `static TSharedRef<class IPropertyTypeCustomization> MakeInstance(TWeakPtr<FWidgetBlueprintEditor> InEditor, FName InWidgetName)`
- L23 _public function_ `FNavigationUIComponentCustomization(TWeakPtr<FWidgetBlueprintEditor> InEditor, FName InWidgetName) : Editor(InEditor) , WidgetName(InWidgetName)`
- L28 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L29 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> PropertyHandle, class IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L33 _private prototype_ `UNavigationUIComponent* GetNavigationComponent() const;`
- L35 _private prototype_ `void CustomizeNavigationTransitionFunction(class IDetailChildrenBuilder& ChildBuilder, bool bIsEnteredFunction);`
- L37 _private prototype_ `TOptional<FName> GetNavigationTransitionFunction(bool bIsEnteredFunction) const;`
- L38 _private prototype_ `void HandleSelectedNavigationTransitionFunction(FName SelectedFunction, bool bIsEnteredFunction);`
- L39 _private prototype_ `void HandleResetNavigationTransitionFunction(bool bIsEnteredFunction);`
- L41 _private member_ `TWeakPtr<FWidgetBlueprintEditor> Editor;`
- L42 _private member_ `FName WidgetName;`

### `Source/Editor/UMGEditor/Private/Extensions/UniformGridSlotExtension.h` (Private)


#### class `FUniformGridSlotExtension`  
`class FUniformGridSlotExtension : public FDesignerExtension`  
_L14-32_
- inherits: `FDesignerExtension`
- L17 _public prototype_ `FUniformGridSlotExtension();`
- L19 _public prototype_ `virtual ~FUniformGridSlotExtension() = default;`
- L21 _public prototype_ `virtual bool CanExtendSelection(const TArray< FWidgetReference >& Selection) const override;`
- L23 _public prototype_ `virtual void ExtendSelection(const TArray< FWidgetReference >& Selection, TArray< TSharedRef<FDesignerSurfaceElement> >& SurfaceElements) override;`
- L27 _private prototype_ `FReply HandleShiftRow(int32 ShiftAmount);`
- L28 _private prototype_ `FReply HandleShiftColumn(int32 ShiftAmount);`
- L30 _private prototype_ `void ShiftRow(UWidget* Widget, int32 ShiftAmount);`
- L31 _private prototype_ `void ShiftColumn(UWidget* Widget, int32 ShiftAmount);`

### `Source/Editor/UMGEditor/Private/Extensions/VerticalSlotExtension.h` (Private)


#### class `FVerticalSlotExtension`  
`class FVerticalSlotExtension : public FDesignerExtension`  
_L10-28_
- inherits: `FDesignerExtension`
- L13 _public prototype_ `FVerticalSlotExtension();`
- L15 _public prototype_ `virtual ~FVerticalSlotExtension() = default;`
- L17 _public prototype_ `virtual bool CanExtendSelection(const TArray< FWidgetReference >& Selection) const override;`
- L19 _public prototype_ `virtual void ExtendSelection(const TArray< FWidgetReference >& Selection, TArray< TSharedRef<FDesignerSurfaceElement> >& SurfaceElements) override;`
- L23 _private prototype_ `bool CanShift(int32 ShiftAmount) const;`
- L25 _private prototype_ `FReply HandleShiftVertical(int32 ShiftAmount);`
- L27 _private prototype_ `void ShiftVertical(UWidget* Widget, int32 ShiftAmount);`

### `Source/Editor/UMGEditor/Private/Graph/GraphFunctionDetailsCustomization.h` (Private)


#### class `FGraphFunctionDetailsCustomization`  
`class FGraphFunctionDetailsCustomization : public IDetailCustomization`  
_L17-30_
- inherits: `IDetailCustomization`
- L21 _public prototype_ `static TSharedPtr<IDetailCustomization> MakeInstance(TSharedPtr<IBlueprintEditor> InBlueprintEditor);` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L23 _public prototype_ `FGraphFunctionDetailsCustomization(UWidgetBlueprint* InBlueprint);`
- L26 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailLayout) override;`
- L29 _private member_ `TPimplPtr<UE::FieldNotification::FCustomizationHelper> Helper;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace FieldNotification` (scope `UE`)

### `Source/Editor/UMGEditor/Private/Graph/GraphVariableDetailsCustomization.h` (Private)


#### class `FGraphVariableDetailsCustomization`  
`class FGraphVariableDetailsCustomization : public IDetailCustomization`  
_L17-30_
- inherits: `IDetailCustomization`
- L21 _public prototype_ `static TSharedPtr<IDetailCustomization> MakeInstance(TSharedPtr<IBlueprintEditor> InBlueprintEditor);` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L23 _public prototype_ `FGraphVariableDetailsCustomization(UWidgetBlueprint* InBlueprint);`
- L26 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailLayout) override;`
- L29 _private member_ `TPimplPtr<UE::FieldNotification::FCustomizationHelper> Helper;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace FieldNotification` (scope `UE`)

### `Source/Editor/UMGEditor/Private/Graph/UMGGraphPanelPinFactory.h` (Private)


#### class `FUMGGraphPanelPinFactory`  
`class FUMGGraphPanelPinFactory : public FGraphPanelPinFactory`  
_L14-31_
- inherits: `FGraphPanelPinFactory`
- L16 _private function_ `virtual TSharedPtr<class SGraphPin> CreatePin(class UEdGraphPin* InPin) const override`

### `Source/Editor/UMGEditor/Private/Hierarchy/SHierarchyView.h` (Private)


#### class `SHierarchyView`  
`class SHierarchyView : public SCompoundWidget`  
_L25-168_
- inherits: `SCompoundWidget`
- desc: The tree view presenting the widget hierarchy.  This allows users to edit the hierarchy of widgets easily by dragging and dropping them logically, which in some cases may be significantly easier than doing it visually in the widget designer.
- L28 _public typedef_ `typedef TTextFilter< TSharedPtr<FHierarchyModel> > WidgetTextFilter;`
- L31 _public function_ `SLATE_BEGIN_ARGS( SHierarchyView )`
- L32 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedPtr<FWidgetBlueprintEditor> InBlueprintEditor, USimpleConstructionScript* InSCS);`
- L36 _public prototype_ `virtual ~SHierarchyView();`
- L39 _public prototype_ `virtual void Tick( const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime ) override;`
- L40 _public prototype_ `virtual void OnMouseEnter(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L41 _public prototype_ `virtual void OnMouseLeave(const FPointerEvent& MouseEvent) override;`
- L42 _public prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;`
- L46 _private prototype_ `void BuildWrapWithMenu(FMenuBuilder& Menu);`
- L47 _private prototype_ `TSharedPtr<SWidget> WidgetHierarchy_OnContextMenuOpening();`
- L48 _private prototype_ `void WidgetHierarchy_OnGetChildren(TSharedPtr<FHierarchyModel> InParent, TArray< TSharedPtr<FHierarchyModel> >& OutChildren);`
- L49 _private prototype_ `TSharedRef< ITableRow > WidgetHierarchy_OnGenerateRow(TSharedPtr<FHierarchyModel> InItem, const TSharedRef<STableViewBase>& OwnerTable);`
- L50 _private prototype_ `void WidgetHierarchy_OnSelectionChanged(TSharedPtr<FHierarchyModel> SelectedItem, ESelectInfo::Type SelectInfo);`
- L51 _private prototype_ `void WidgetHierarchy_OnExpansionChanged(TSharedPtr<FHierarchyModel> Item, bool bExpanded);`
- L52 _private prototype_ `void WidgetHierarchy_OnMouseClick(TSharedPtr<FHierarchyModel> InItem);`
- L55 _private prototype_ `void BeginRename();`
- L56 _private prototype_ `bool CanRename() const;`
- L59 _private prototype_ `UWidgetBlueprint* GetBlueprint() const;` — @returns the current blueprint being edited
- L62 _private prototype_ `void OnBlueprintChanged(UBlueprint* InBlueprint);` — Called when the blueprint is structurally changed.
- L65 _private prototype_ `void OnEditorSelectionChanged();` — Called when the selected widget has changed.  The treeview then needs to match the new selection.
- L68 _private prototype_ `void ShowDetailsForObjects(TArray<UWidget*> Widgets);` — Notifies the details panel that new widgets have been selected.
- L71 _private prototype_ `void RefreshTree();` — Rebuilds the tree structure based on the current filter options
- L74 _private prototype_ `void RebuildTreeView();` — Completely regenerates the treeview
- L77 _private prototype_ `FReply HandleDeleteSelected();` — Handles the menu clicking to delete the selected widgets.
- L80 _private prototype_ `void DeleteSelected();` — Deletes the selected widgets from the hierarchy
- L83 _private prototype_ `void WrapSelectedWidgets(UClass* WidgetClass);` — Wraps the selected widget using a user selected panel
- L86 _private prototype_ `void OnSearchChanged(const FText& InFilterText);` — Called when the filter text is changed.
- L89 _private prototype_ `FText GetSearchText() const;` — Gets the search text currently being used to filter the list, also used to highlight text
- L92 _private prototype_ `void GetWidgetFilterStrings(TSharedPtr<FHierarchyModel> Widget, TArray<FString>& OutStrings);` — Gets an array of strings used for filtering/searching the specified widget.
- L95 _private prototype_ `void OnObjectsReplaced(const TMap<UObject*, UObject*>& ReplacementMap);` — Called when a Blueprint is recompiled and live objects are swapped out for replacements
- L98 _private prototype_ `void UpdateItemsExpansionFromModel();` — Sets the expansion state of hierarchy view items based on their model.
- L101 _private prototype_ `void SaveItemsExpansion();` — Stores the names of all currently expanded nodes in the hierarchy view.
- L104 _private prototype_ `void RestoreItemsExpansion();` — Sets the expansion state of hierarchy view items based on the state saved by SaveItemsExpansion.
- L115 _private prototype_ `void RecursiveExpand(TSharedPtr<FHierarchyModel>& Model, EExpandBehavior ExpandBehavior);` — Recursively expands the models based on the expansion set.
- L118 _private prototype_ `void RestoreSelectedItems();`
- L121 _private prototype_ `void RecursiveSelection(TSharedPtr<FHierarchyModel>& Model);`
- L124 _private prototype_ `void SetItemExpansionRecursive(TSharedPtr<FHierarchyModel> Model, bool bInExpansionState);` — Handler for recursively expanding/collapsing items
- L126 _private prototype_ `void SetItemExpansionRecursive_SelectedItems(const bool bInExpansionState);`
- L131 _private member_ `TWeakPtr<class FWidgetBlueprintEditor> BlueprintEditor;` — Cached pointer to the blueprint editor that owns this tree.
- L134 _private member_ `TSharedPtr<FUICommandList> CommandList;` — Commands specific to the hierarchy.
- L137 _private member_ `TSharedPtr< TreeFilterHandler< TSharedPtr<FHierarchyModel> > > FilterHandler;` — Handles filtering the hierarchy based on an IFilter.
- L140 _private member_ `TArray< TSharedPtr<FHierarchyModel> > RootWidgets;` — The source root widgets for the tree.
- L143 _private member_ `TArray< TSharedPtr<FHierarchyModel> > TreeRootWidgets;` — The root widgets which are actually displayed by the TreeView which will be managed by the TreeFilterHandler.
- L146 _private member_ `TSharedPtr<SBorder> TreeViewArea;` — The widget containing the treeview
- L149 _private member_ `TSharedPtr< STreeView< TSharedPtr<FHierarchyModel> > > WidgetTreeView;` — The widget hierarchy slate treeview widget
- L152 _private member_ `TSet< FName > ExpandedItemNames;` — The unique names of all nodes expanded in the tree view
- L155 _private member_ `TSharedPtr<class SSearchBox> SearchBoxPtr;` — The search box used to update the filter text
- L158 _private member_ `TSharedPtr<WidgetTextFilter> SearchBoxWidgetFilter;` — The filter used by the search box
- L161 _private member_ `bool bRefreshRequested;` — Has a full refresh of the tree been requested?  This happens when the user is filtering the tree
- L164 _private member_ `bool bRebuildTreeRequested;` — Is the tree in such a changed state that the whole widget needs rebuilding?
- L167 _private member_ `bool bIsUpdatingSelection;` — Flag to ignore selections while the hierarchy view is updating the selection.

#### enum `SHierarchyView::EExpandBehavior`  
`enum class EExpandBehavior : uint8`  
_L106-112_
- L108 _public enumerator_ `NeverExpand`
- L109 _public enumerator_ `AlwaysExpand`
- L110 _public enumerator_ `RestoreFromPrevious`
- L111 _public enumerator_ `FromModel`

### `Source/Editor/UMGEditor/Private/Hierarchy/SHierarchyViewItem.h` (Private)


#### class `FHierarchyModel`  
`class FHierarchyModel : public IHierarchyModel, public TSharedFromThis < FHierarchyModel >`  
_L16-120_
- inherits: `IHierarchyModel,TSharedFromThis<FHierarchyModel>`
- L19 _public prototype_ `FHierarchyModel(TSharedPtr<FWidgetBlueprintEditor> InBlueprintEditor);`
- L20 _public prototype_ `virtual ~FHierarchyModel() = default;`
- L23 _public prototype_ `virtual FName GetUniqueName() const = 0;` — Gets the unique name of the item used to restore item expansion.
- L26 _public prototype_ `virtual FText GetText() const = 0;` — @returns the widget name to use for the tree item
- L29 _public function_ `virtual FText GetImageToolTipText() const` — @return The tooltip for the tree item image
- L32 _public function_ `virtual FText GetLabelToolTipText() const` — @return The tooltip for the tree item label
- L35 _public function_ `virtual void GetFilterStrings(TArray<FString>& OutStrings) const` — @param OutStrings - Returns an array of strings used for filtering/searching this item.
- L37 _public prototype_ `virtual const FSlateBrush* GetImage() const = 0;`
- L39 _public prototype_ `virtual FSlateFontInfo GetFont() const = 0;`
- L41 _public prototype_ `FReply HandleDragDetected(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent);`
- L42 _public prototype_ `virtual void HandleDragEnter(const FDragDropEvent& DragDropEvent);`
- L43 _public prototype_ `virtual void HandleDragLeave(const FDragDropEvent& DragDropEvent);`
- L45 _public prototype_ `virtual TOptional<EItemDropZone> HandleCanAcceptDrop(const FDragDropEvent& DragDropEvent, EItemDropZone DropZone);`
- L46 _public prototype_ `virtual FReply HandleAcceptDrop(FDragDropEvent const& DragDropEvent, EItemDropZone DropZone);`
- L48 _public prototype_ `virtual bool OnVerifyNameTextChanged(const FText& InText, FText& OutErrorMessage);`
- L50 _public prototype_ `virtual void OnNameTextCommited(const FText& InText, ETextCommit::Type CommitInfo);`
- L52 _public prototype_ `virtual void GatherChildren(TArray< TSharedPtr<FHierarchyModel> >& Children);`
- L54 _public prototype_ `virtual void OnSelection() = 0;`
- L56 _public function_ `virtual void OnMouseEnter()`
- L57 _public function_ `virtual void OnMouseLeave()`
- L59 _public prototype_ `void RefreshSelection();`
- L60 _public prototype_ `bool ContainsSelection();`
- L61 _public prototype_ `bool IsSelected() const;`
- L63 _public function_ `virtual bool IsHovered() const override`
- L64 _public function_ `virtual bool IsVisible() const override`
- L65 _public function_ `virtual bool CanControlVisibility() const override`
- L66 _public function_ `virtual void SetIsVisible(bool IsVisible)`
- L68 _public function_ `virtual bool CanControlLockedInDesigner() const override`
- L69 _public function_ `virtual bool IsLockedInDesigner() const override`
- L70 _public function_ `virtual void SetIsLockedInDesigner(bool NewIsLocked, bool bRecursive)`
- L86 _public function_ `virtual bool DoesWidgetOverrideNavigation() const`
- L87 _public function_ `virtual bool DoesWidgetOverrideFlowDirection() const`
- L89 _public function_ `virtual bool IsExpanded() const`
- L90 _public function_ `virtual void SetExpanded(bool bIsExpanded)`
- L92 _public function_ `virtual bool CanRename() const`
- L93 _public function_ `virtual void RequestBeginRename()`
- L95 _public function_ `virtual void OnBeginEditing()`
- L96 _public function_ `virtual void OnEndEditing()`
- L98 _public function_ `virtual bool IsRoot() const`
- L101 _public member_ `FSimpleDelegate RenameEvent;`
- L104 _protected prototype_ `virtual void GetChildren(TArray< TSharedPtr<FHierarchyModel> >& Children) = 0;`
- L105 _protected prototype_ `virtual void UpdateSelection() = 0;`
- L106 _protected function_ `virtual FWidgetReference AsDraggedWidgetReference() const`
- L107 _protected prototype_ `virtual bool HasCircularReferences(class UWidgetBlueprint* Blueprint, class UWidget* Widget, TSharedPtr<class FDragDropOperation>& DragDropOp);`
- L108 _protected prototype_ `void DetermineDragDropPreviewWidgets(TArray<class UWidget*>& OutWidgets, const FDragDropEvent& DragDropEvent);`
- L109 _protected prototype_ `void RemovePreviewWidget(class UWidgetBlueprint* Blueprint, class UWidget* Widget);`
- L112 _private prototype_ `void InitializeChildren();`
- L116 _protected member_ `bool bInitialized;`
- L117 _protected member_ `bool bIsSelected;`
- L118 _protected member_ `TWeakPtr<FWidgetBlueprintEditor> BlueprintEditor;`
- L119 _protected member_ `TArray< TSharedPtr<FHierarchyModel> > Models;`

#### class `FHierarchyRoot`  
`class FHierarchyRoot : public FHierarchyModel`  
_L122-154_
- inherits: `FHierarchyModel`
- L125 _public prototype_ `FHierarchyRoot(TSharedPtr<FWidgetBlueprintEditor> InBlueprintEditor);`
- L127 _public prototype_ `virtual ~FHierarchyRoot() = default;`
- L129 _public prototype_ `virtual FName GetUniqueName() const override;`
- L132 _public prototype_ `virtual FText GetText() const override;` — @returns the widget name to use for the tree item
- L134 _public prototype_ `virtual const FSlateBrush* GetImage() const override;`
- L136 _public prototype_ `virtual FSlateFontInfo GetFont() const override;`
- L138 _public prototype_ `virtual void OnSelection() override;`
- L140 _public prototype_ `virtual bool DoesWidgetOverrideFlowDirection() const override;`
- L141 _public function_ `virtual bool DoesWidgetOverrideNavigation() const override`
- L143 _public prototype_ `virtual TOptional<EItemDropZone> HandleCanAcceptDrop(const FDragDropEvent& DragDropEvent, EItemDropZone DropZone) override;`
- L144 _public prototype_ `virtual FReply HandleAcceptDrop(FDragDropEvent const& DragDropEvent, EItemDropZone DropZone) override;`
- L146 _public function_ `virtual bool IsRoot() const override`
- L149 _protected prototype_ `virtual void GetChildren(TArray< TSharedPtr<FHierarchyModel> >& Children) override;`
- L150 _protected prototype_ `virtual void UpdateSelection() override;`
- L153 _private member_ `FText RootText;`

#### class `FNamedSlotModelBase`  
`class FNamedSlotModelBase : public FHierarchyModel`  
_L156-187_
- inherits: `FHierarchyModel`
- L159 _public prototype_ `FNamedSlotModelBase(FName InSlotName, TSharedPtr<FWidgetBlueprintEditor> InBlueprintEditor);`
- L161 _public prototype_ `virtual ~FNamedSlotModelBase() = default;`
- L163 _public prototype_ `virtual FName GetUniqueName() const = 0;`
- L164 _public prototype_ `virtual FText GetText() const override;`
- L166 _public prototype_ `virtual const FSlateBrush* GetImage() const override;`
- L167 _public prototype_ `virtual FSlateFontInfo GetFont() const override;`
- L169 _public prototype_ `virtual void OnSelection() override;`
- L171 _public prototype_ `virtual TOptional<EItemDropZone> HandleCanAcceptDrop(const FDragDropEvent& DragDropEvent, EItemDropZone DropZone) override;`
- L172 _public prototype_ `virtual FReply HandleAcceptDrop(FDragDropEvent const& DragDropEvent, EItemDropZone DropZone) override;`
- L175 _protected prototype_ `virtual INamedSlotInterface* GetNamedSlotHost() const = 0;`
- L176 _protected prototype_ `virtual UWidget* GetNamedSlotHostWidget() const = 0;`
- L178 _protected prototype_ `virtual void GetChildren(TArray< TSharedPtr<FHierarchyModel> >& Children) override;`
- L179 _protected prototype_ `virtual void UpdateSelection() override;`
- L180 _protected prototype_ `virtual FWidgetReference AsDraggedWidgetReference() const override;`
- L182 _protected prototype_ `virtual void DoDrop(INamedSlotInterface* NamedSlotHost, UWidget* DroppingWidget);`
- L186 _protected member_ `FName SlotName;`

#### class `FNamedSlotModel`  
`class FNamedSlotModel : public FNamedSlotModelBase`  
_L189-206_
- inherits: `FNamedSlotModelBase`
- L192 _public prototype_ `FNamedSlotModel(FWidgetReference InItem, FName InSlotName, TSharedPtr<FWidgetBlueprintEditor> InBlueprintEditor);`
- L194 _public prototype_ `virtual ~FNamedSlotModel() = default;`
- L196 _public prototype_ `virtual FName GetUniqueName() const override;`
- L197 _public prototype_ `virtual INamedSlotInterface* GetNamedSlotHost() const override;`
- L198 _public prototype_ `virtual UWidget* GetNamedSlotHostWidget() const override;`
- L201 _protected prototype_ `virtual void OnSelection() override;`
- L205 _protected member_ `FWidgetReference Item;`

#### class `FNamedSlotModelSubclass`  
`class FNamedSlotModelSubclass : public FNamedSlotModelBase`  
_L208-224_
- inherits: `FNamedSlotModelBase`
- L211 _public prototype_ `FNamedSlotModelSubclass(UWidgetBlueprint* Blueprint, FName InSlotName, TSharedPtr<FWidgetBlueprintEditor> InBlueprintEditor);`
- L213 _public prototype_ `virtual ~FNamedSlotModelSubclass() = default;`
- L215 _public prototype_ `virtual FName GetUniqueName() const override;`
- L216 _public prototype_ `virtual INamedSlotInterface* GetNamedSlotHost() const override;`
- L217 _public prototype_ `virtual UWidget* GetNamedSlotHostWidget() const override;`
- L220 _protected prototype_ `virtual void OnSelection() override;`
- L223 _protected member_ `TWeakObjectPtr<UWidgetBlueprint> Blueprint;`

#### class `FHierarchyWidget`  
`class FHierarchyWidget : public FHierarchyModel`  
_L226-369_
- inherits: `FHierarchyModel`
- L229 _public prototype_ `FHierarchyWidget(FWidgetReference InItem, TSharedPtr<FWidgetBlueprintEditor> InBlueprintEditor);`
- L231 _public prototype_ `virtual ~FHierarchyWidget() = default;`
- L233 _public prototype_ `virtual FName GetUniqueName() const override;`
- L236 _public prototype_ `virtual FText GetText() const override;` — @returns the widget name to use for the tree item
- L237 _public prototype_ `virtual FText GetImageToolTipText() const override;`
- L238 _public prototype_ `virtual FText GetLabelToolTipText() const override;`
- L240 _public prototype_ `virtual void GetFilterStrings(TArray<FString>& OutStrings) const override;`
- L242 _public prototype_ `virtual const FSlateBrush* GetImage() const override;`
- L244 _public prototype_ `virtual FSlateFontInfo GetFont() const override;`
- L246 _public prototype_ `virtual TOptional<EItemDropZone> HandleCanAcceptDrop(const FDragDropEvent& DragDropEvent, EItemDropZone DropZone) override;`
- L248 _public prototype_ `virtual void HandleDragLeave(const FDragDropEvent& DragDropEvent) override;`
- L249 _public prototype_ `virtual FReply HandleAcceptDrop(FDragDropEvent const& DragDropEvent, EItemDropZone DropZone) override;`
- L251 _public prototype_ `virtual bool OnVerifyNameTextChanged(const FText& InText, FText& OutErrorMessage) override;`
- L253 _public prototype_ `virtual void OnNameTextCommited(const FText& InText, ETextCommit::Type CommitInfo) override;`
- L255 _public prototype_ `virtual void OnSelection() override;`
- L257 _public prototype_ `virtual void OnMouseEnter() override;`
- L258 _public prototype_ `virtual void OnMouseLeave() override;`
- L260 _public prototype_ `virtual bool IsHovered() const override;`
- L262 _public function_ `virtual bool IsVisible() const override`
- L272 _public function_ `virtual bool CanControlVisibility() const override`
- L277 _public function_ `virtual void SetIsVisible(bool IsVisible) override`
- L287 _public function_ `virtual bool CanControlLockedInDesigner() const override`
- L292 _public function_ `virtual bool IsLockedInDesigner() const override`
- L303 _public function_ `virtual void SetIsLockedInDesigner(bool NewIsLocked, bool bRecursive) override`
- L314 _public function_ `virtual bool DoesWidgetOverrideFlowDirection() const override`
- L325 _public function_ `virtual bool DoesWidgetOverrideNavigation() const override`
- L336 _public function_ `virtual bool IsExpanded() const override`
- L346 _public function_ `virtual void SetExpanded(bool bIsExpanded) override`
- L354 _public prototype_ `virtual bool CanRename() const override;`
- L355 _public prototype_ `virtual void RequestBeginRename() override;`
- L357 _public prototype_ `virtual void OnBeginEditing() override;`
- L358 _public prototype_ `virtual void OnEndEditing() override;`
- L361 _protected prototype_ `virtual void GetChildren(TArray< TSharedPtr<FHierarchyModel> >& Children) override;`
- L362 _protected prototype_ `virtual void UpdateSelection() override;`
- L363 _protected function_ `virtual FWidgetReference AsDraggedWidgetReference() const override`
- L366 _private member_ `FWidgetReference Item;`
- L367 _private member_ `bool bEditing;`
- L368 _private member_ `bool bNameTextValid;`

#### class `SHierarchyViewItem`  
`class SHierarchyViewItem : public IHierarchyViewItem< FHierarchyModel >`  
_L374-452_
- inherits: `IHierarchyViewItem<FHierarchyModel>`
- desc: An widget item in the hierarchy tree view.
- L377 _public function_ `SLATE_BEGIN_ARGS( SHierarchyViewItem )`
- L380 _public prototype_ `SLATE_ATTRIBUTE( FText, HighlightText ) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef< STableViewBase >& InOwnerTableView, TSharedPtr<FHierarchyModel> InModel);` — The current text to highlight
- L385 _public prototype_ `virtual ~SHierarchyViewItem();`
- L388 _public prototype_ `virtual void OnMouseEnter(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L389 _public prototype_ `virtual void OnMouseLeave(const FPointerEvent& MouseEvent) override;`
- L393 _public prototype_ `virtual FReply HandleDragDetected(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L394 _public prototype_ `void HandleDragEnter(const FDragDropEvent& DragDropEvent);`
- L395 _public prototype_ `void HandleDragLeave(const FDragDropEvent& DragDropEvent);`
- L397 _public prototype_ `TOptional<EItemDropZone> HandleCanAcceptDrop(const FDragDropEvent& DragDropEvent, EItemDropZone DropZone, TSharedPtr<FHierarchyModel> TargetItem);`
- L398 _public prototype_ `FReply HandleAcceptDrop(const FDragDropEvent& DragDropEvent, EItemDropZone DropZone, TSharedPtr<FHierarchyModel> TargetItem);`
- L402 _private prototype_ `void OnBeginNameTextEdit();`
- L403 _private prototype_ `void OnEndNameTextEdit();`
- L406 _private prototype_ `bool OnVerifyNameTextChanged(const FText& InText, FText& OutErrorMessage);` — Called when text is being committed to check for validity
- L409 _private prototype_ `void OnNameTextCommited(const FText& InText, ETextCommit::Type CommitInfo);` — Called when text is committed on the node
- L411 _private prototype_ `bool IsReadOnly() const;`
- L412 _private prototype_ `void OnRequestBeginRename();`
- L413 _private prototype_ `virtual bool ShouldAppearHovered() const override;`
- L416 _private prototype_ `FSlateFontInfo GetItemFont() const;` — Gets the font to use for the text item, bold for customized named items
- L419 _private prototype_ `FText GetItemText() const;` — @returns the widget name to use for the tree item
- L422 _private prototype_ `FReply OnToggleVisibility();` — Handles clicking the visibility toggle
- L425 _private prototype_ `virtual void ToggleLockedInDesigner(const bool bRecursive) override;` — Toggles lock status
- L428 _private prototype_ `FReply OnToggleLockedInDesigner();` — Handles clicking the locked toggle
- L431 _private prototype_ `FText GetLockBrushForWidget() const;` — Returns a brush representing the lock item of the widget's lock button
- L434 _private prototype_ `FText GetVisibilityBrushForWidget() const;` — Returns a brush representing the visibility item of the widget's visibility button
- L439 _private member_ `TWeakPtr<SInlineEditableTextBlock> EditBox;` — Edit box for the name.
- L442 _private member_ `TSharedPtr<FHierarchyModel> Model;` — The mode that this tree item represents
- L445 _private member_ `FText InitialText;` — Text when we start editing.
- L448 _private member_ `bool bHovered = false;` — Keep an internal IsHovered flag
- L451 _private member_ `TSharedPtr<FActiveTimerHandle> DragHoverExpandTimer;` — If the user is dragging over a collapsed item, wait before expanding it

### `Source/Editor/UMGEditor/Private/Library/SLibraryView.h` (Private)


#### class `SLibraryViewItem`  
`class SLibraryViewItem : public SCompoundWidget`  
_L22-68_
- inherits: `SCompoundWidget`
- desc: Widget used to show a single row of the Library and Library favorite panel.
- L26 _public function_ `SLATE_BEGIN_ARGS(SLibraryViewItem)`
- L29 _public prototype_ `SLATE_ATTRIBUTE(FText, HighlightText) SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedPtr<FWidgetTemplateViewModel> InWidgetViewModel);` — The current text to highlight
- L46 _private prototype_ `FText GetFavoriteToggleToolTipText() const;` — Retrieves tooltip that describes the current favorited state @return Text describing what this toggle will do when you click on it.
- L54 _private prototype_ `ECheckBoxState GetFavoritedState() const;` — Checks on the associated action's favorite state, and returns a corresponding checkbox state to match. @return ECheckBoxState::Checked if the associated action is already favorited, ECheckBoxState::Unchecked if not.
- L62 _private prototype_ `void OnFavoriteToggled(ECheckBoxState InNewState);` — Triggers when the user clicks this toggle, adds or removes the associated action to the user's favorites. @param  InNewState	The new state that the user set the checkbox to.
- L64 _private prototype_ `EVisibility GetFavoritedStateVisibility() const;`
- L67 _private member_ `TSharedPtr<FWidgetTemplateViewModel> WidgetViewModel;`

#### class `SLibraryView`  
`class SLibraryView : public SCompoundWidget`  
_L71-158_
- inherits: `SCompoundWidget`
- L74 _public typedef_ `typedef TDelegateFilter<TSharedPtr<FWidgetViewModel>> WidgetViewModelDelegateFilter;`
- L77 _public function_ `SLATE_BEGIN_ARGS( SLibraryView )`
- L78 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedPtr<FWidgetBlueprintEditor> InBlueprintEditor);`
- L81 _public prototype_ `virtual ~SLibraryView();`
- L83 _public prototype_ `virtual void Tick( const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime ) override;`
- L86 _public prototype_ `void WidgetLibrary_OnClick(TSharedPtr<FWidgetViewModel> SelectedItem);` — On item clicked in palette view
- L91 _private prototype_ `TSharedRef<SWidget> ConstructViewOptions();` — Builds settings menu.
- L93 _private prototype_ `void OnGetChildren(TSharedPtr<FWidgetViewModel> Item, TArray< TSharedPtr<FWidgetViewModel> >& Children);`
- L94 _private prototype_ `TSharedRef<ITableRow> OnGenerateWidgetTemplateLibrary(TSharedPtr<FWidgetViewModel> Item, const TSharedRef<STableViewBase>& OwnerTable);`
- L97 _private prototype_ `void OnSearchChanged(const FText& InFilterText);` — Called when the filter text is changed.
- L99 _private prototype_ `void OnViewModelUpdating();`
- L100 _private prototype_ `void OnViewModelUpdated();`
- L104 _private prototype_ `void LoadItemExpansion();` — Load the expansion state for the TreeView
- L107 _private prototype_ `void SaveItemExpansion();` — Save the expansion state for the TreeView
- L110 _private prototype_ `bool HandleFilterWidgetView(TSharedPtr<FWidgetViewModel> WidgetViewModel);` — Callback to determine if a particular library view passes filtering
- L113 _private prototype_ `void SetCurrentViewTypeFromMenu(EAssetViewType::Type ViewType);` — Callback to set library asset view type
- L116 _private prototype_ `bool IsCurrentViewType(EAssetViewType::Type ViewType);` — Callback to determine library asset view type
- L119 _private prototype_ `void OnThumbnailSizeChanged(EThumbnailSize InThumbnailSize);` — Callback to set library asset thumbnail size
- L122 _private prototype_ `bool IsThumbnailSizeChecked(EThumbnailSize InThumbnailSize);` — Callback to determine library asset thumbnail size
- L124 _private member_ `TWeakPtr<class FWidgetBlueprintEditor> BlueprintEditor;`
- L125 _private member_ `TSharedPtr<FLibraryViewModel> LibraryViewModel;`
- L128 _private typedef_ `typedef TreeFilterHandler<TSharedPtr<FWidgetViewModel>> LibraryFilterHandler;` — Handles filtering the Library based on an IFilter.
- L129 _private member_ `TSharedPtr<LibraryFilterHandler> FilterHandler;`
- L131 _private typedef_ `typedef TArray<TSharedPtr<FWidgetViewModel>> ViewModelsArray;`
- L133 _private member_ `ViewModelsArray TreeWidgetViewModels;` — The root view models which are actually displayed by the TreeView which will be managed by the TreeFilterHandler.
- L135 _private member_ `TSharedPtr< STreeView< TSharedPtr<FWidgetViewModel> > > WidgetTemplatesView;`
- L138 _private member_ `TSharedPtr<class SSearchBox> SearchBoxPtr;` — The search box used to update the filter text
- L141 _private member_ `TSharedPtr<WidgetViewModelDelegateFilter> WidgetFilter;` — The filter instance which is used by the TreeFilterHandler to filter the TreeView.
- L144 _private member_ `TSet<TSharedPtr<FWidgetViewModel>> ExpandedItems;` — Expended Items in the Tree view
- L147 _private member_ `bool bRefreshRequested;` — Set to true to force a refresh of the treeview
- L150 _private member_ `bool bAllowEditorWidget;` — Are editor widgets supported.
- L153 _private member_ `EAssetViewType::Type LastViewType;` — Last view type set by user
- L156 _private member_ `EThumbnailSize LastThumbnailSize;` — Last view type set by user

### `Source/Editor/UMGEditor/Private/Library/SLibraryViewModel.h` (Private)


#### class `FWidgetTemplateListViewModel`  
`class FWidgetTemplateListViewModel : public FWidgetViewModel`  
_L20-69_
- inherits: `FWidgetViewModel`
- L23 _public prototype_ `FWidgetTemplateListViewModel();`
- L26 _public prototype_ `void ConstructListView(TArray<TSharedPtr<FWidgetTemplate>> InTemplates);` — Builds list view for given templates
- L29 _public prototype_ `virtual FText GetName() const override;`
- L30 _public prototype_ `virtual bool IsTemplate() const override;`
- L31 _public prototype_ `virtual void GetFilterStrings(TArray<FString>& OutStrings) const override;`
- L32 _public prototype_ `virtual bool HasFilteredChildTemplates() const override;`
- L33 _public prototype_ `virtual TSharedRef<ITableRow> BuildRow(const TSharedRef<STableViewBase>& OwnerTable) override;`
- L36 _public prototype_ `void SetViewType(EAssetViewType::Type ViewType);`
- L38 _public prototype_ `void SetThumbnailSize(EThumbnailSize ThumbnailSize);`
- L40 _public prototype_ `void SetSearchText(const FText& InSearchText);`
- L41 _public prototype_ `FText GetSearchText() const;`
- L43 _public member_ `TArray<TSharedPtr<FWidgetTemplate>> Templates;`
- L44 _public member_ `TSharedPtr<FAssetFilterCollectionType> TemplatesFilter;`
- L47 _private prototype_ `bool EnumerateCustomSourceItemDatas(TFunctionRef<bool(FContentBrowserItemData&&)> InCallback);`
- L50 _private member_ `TSharedPtr<SAssetView> AssetViewPtr;` — The asset view widget
- L53 _private member_ `TSharedPtr<class FAssetTextFilter> SearchFilter;` — Filter we forward our search text to for the asset view
- L56 _private member_ `TSharedPtr<struct FAssetViewContentSources> LibraryContentSources;` — Source data for the asset view
- L59 _private member_ `TArray<FContentBrowserItemPath> SourceItemPaths;` — Source item path storage for asset view, accessed via delegate
- L62 _private member_ `FString CachedLowercaseWidgetFilter;` — Lowercase string representing widget text filter
- L65 _private member_ `uint32 NumAssets = 0;` — Number of widget assets in view
- L68 _private member_ `uint32 NumClasses = 0;` — Number of widget classes in view

#### class `FLibraryViewModel`  
`class FLibraryViewModel : public FWidgetCatalogViewModel`  
_L71-90_
- inherits: `FWidgetCatalogViewModel`
- L74 _public function_ `FLibraryViewModel(TSharedPtr<FWidgetBlueprintEditor> InBlueprintEditor) : FWidgetCatalogViewModel(InBlueprintEditor)`
- L77 _public prototype_ `virtual void BuildWidgetTemplateCategory(FString& Category, TArray<TSharedPtr<FWidgetTemplate>>& Templates, TArray<FString>& FavoritesList) override;`
- L78 _public prototype_ `virtual void SetSearchText(const FText& InSearchText) override;`
- L81 _public function_ `ViewModelsArray& GetWidgetTemplateListViewModels()`
- L85 _protected prototype_ `virtual void BuildWidgetList() override;`
- L89 _protected member_ `ViewModelsArray WidgetTemplateListViewModels;` — Widget template list view models associated with each root.

### `Source/Editor/UMGEditor/Private/Navigation/SWidgetDesignerNavigation.h` (Private)


#### struct `FNavigationSimulationArguments`  
`struct FNavigationSimulationArguments`  
_L22-40_
- reflection: `USTRUCT()`
- L27 _public member_ `int32 UserIndex = 0;` — `UPROPERTY(EditAnywhere, Category = "Simulation Options")`
- L30 _public member_ `ENavigationGenesis NavigationGenesis = ENavigationGenesis::Controller;` — `UPROPERTY(EditAnywhere, Category = "Simulation Options")`
- L33 _public member_ `EUINavigation UINavigation = EUINavigation::Left;` — `UPROPERTY(EditAnywhere, Category = "Simulation Options", meta = (EditCondition = "bOverrideUINavigation"))`
- L36 _public member_ `bool bOverrideUINavigation = false;` — `UPROPERTY(EditAnywhere, Category = "Simulation", meta = (InlineEditConditionToggle))`
- L39 _public member_ `bool bShowPreview = true;` — `UPROPERTY(EditAnywhere, Category = "Display")`

#### class `SWidgetDesignerNavigation`  
`class SWidgetDesignerNavigation : public SCompoundWidget`  
_L44-87_
- inherits: `SCompoundWidget`
- L47 _public function_ `SLATE_BEGIN_ARGS(SWidgetDesignerNavigation)`
- L48 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedPtr<FWidgetBlueprintEditor> InBlueprintEditor);`
- L51 _public prototype_ `virtual ~SWidgetDesignerNavigation();`
- L53 _public prototype_ `static TSharedRef<IDesignerExtensionFactory> MakeDesignerExtension();`
- L56 _private prototype_ `UWidgetBlueprint* GetBlueprint() const;`
- L57 _private prototype_ `void RunNewSimulation(TSharedRef<SWidget> NewContent);`
- L58 _private prototype_ `void ClearSimulationResult();`
- L60 _private prototype_ `void HandleWidgetPreviewUpdated(TSharedRef<SWidget> NewContent);`
- L61 _private prototype_ `void HandleEditorSelectionChanged();`
- L62 _private prototype_ `void HandleSelectWidget(TWeakPtr<const SWidget> Widget);`
- L63 _private prototype_ `void HandlePaint(const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId);`
- L64 _private prototype_ `FReply HandleRefreshClicked();`
- L65 _private prototype_ `bool HandleRefreshEnabled() const;`
- L69 _private member_ `TWeakPtr<FWidgetBlueprintEditor> BlueprintEditor;` — Cached pointer to the blueprint editor.
- L72 _private member_ `TSharedPtr<INavigationEventSimulationView> NavigationEventSimulationView;` — The simulation result view.
- L75 _private member_ `TAtomic<int32> SimulationWidgetRequested;` — A simulation is requested.
- L78 _private member_ `TWeakPtr<SWidget> LastSimulationContent;` — Last widget the simulation was executed from.
- L81 _private member_ `FNavigationSimulationArguments SimulationArguments;` — Simulation Arguments
- L84 _private member_ `bool bIsInSelection;` — In selection

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace WidgetDesignerNavigation`

### `Source/Editor/UMGEditor/Private/Nodes/K2Node_CreateDragDropOperation.h` (Private)


#### class `UK2Node_CreateDragDropOperation`  
`class UK2Node_CreateDragDropOperation : public UK2Node_ConstructObjectFromClass`  
_L15-36_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UK2Node_ConstructObjectFromClass`
- L20 _private prototype_ `virtual void AllocateDefaultPins() override;`
- L21 _private prototype_ `virtual void ExpandNode(class FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph) override;`
- L25 _private prototype_ `virtual FText GetMenuCategory() const override;`
- L26 _private prototype_ `virtual FName GetCornerIcon() const override;`
- L31 _protected prototype_ `virtual FText GetBaseNodeTitle() const override;` — Gets the default node title when no class is selected
- L33 _protected prototype_ `virtual FText GetNodeTitleFormat() const override;` — Gets the node title when a class has been selected.
- L35 _protected prototype_ `virtual UClass* GetClassPinBaseClass() const override;` — Gets base class to use for the 'class' pin.  UObject by default.

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API UMGEDITOR_API`

### `Source/Editor/UMGEditor/Private/Nodes/K2Node_CreateWidget.h` (Private)


#### class `UK2Node_CreateWidget`  
`class UK2Node_CreateWidget : public UK2Node_ConstructObjectFromClass`  
_L15-42_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UK2Node_ConstructObjectFromClass`
- L20 _private prototype_ `virtual void AllocateDefaultPins() override;`
- L21 _private prototype_ `virtual void ExpandNode(class FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph) override;`
- L22 _private prototype_ `virtual TSharedPtr<SGraphNode> CreateVisualWidget() override;`
- L26 _private prototype_ `virtual FText GetMenuCategory() const override;`
- L27 _private prototype_ `virtual FName GetCornerIcon() const override;`
- L31 _private prototype_ `UEdGraphPin* GetOwningPlayerPin() const;` — Get the owning player pin
- L35 _protected prototype_ `virtual FText GetBaseNodeTitle() const override;` — Gets the default node title when no class is selected
- L37 _protected prototype_ `virtual FText GetNodeTitleFormat() const override;` — Gets the node title when a class has been selected.
- L39 _protected prototype_ `virtual UClass* GetClassPinBaseClass() const override;` — Gets base class to use for the 'class' pin.  UObject by default.
- L41 _protected prototype_ `virtual bool IsSpawnVarPin(UEdGraphPin* Pin) const override;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API UMGEDITOR_API`

### `Source/Editor/UMGEditor/Private/Nodes/K2Node_PlayAnimation.h` (Private)


#### class `UK2Node_PlayAnimation`  
`class UK2Node_PlayAnimation : public UK2Node_BaseAsyncTask`  
_L9-12_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UK2Node_BaseAsyncTask`

#### class `UK2Node_PlayAnimationTimeRange`  
`class UK2Node_PlayAnimationTimeRange : public UK2Node_BaseAsyncTask`  
_L15-18_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UK2Node_BaseAsyncTask`

#### class `UK2Node_PlayAnimation2`  
`class UK2Node_PlayAnimation2 : public UK2Node_BaseAsyncTask`  
_L21-24_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UK2Node_BaseAsyncTask`

#### class `UK2Node_PlayAnimationTimeRange2`  
`class UK2Node_PlayAnimationTimeRange2 : public UK2Node_BaseAsyncTask`  
_L27-30_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UK2Node_BaseAsyncTask`

### `Source/Editor/UMGEditor/Private/Palette/SPaletteView.h` (Private)


#### class `SPaletteViewItem`  
`class SPaletteViewItem : public SCompoundWidget`  
_L21-69_
- inherits: `SCompoundWidget`
- desc: Widget used to show a single row of the Palette and Palette favorite panel.
- L25 _public function_ `SLATE_BEGIN_ARGS(SPaletteViewItem)`
- L28 _public prototype_ `SLATE_ATTRIBUTE(FText, HighlightText) SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedPtr<FWidgetTemplateViewModel> InWidgetViewModel);` — The current text to highlight
- L45 _private prototype_ `FText GetFavoriteToggleToolTipText() const;` — Retrieves tooltip that describes the current favorited state @return Text describing what this toggle will do when you click on it.
- L53 _private prototype_ `ECheckBoxState GetFavoritedState() const;` — Checks on the associated action's favorite state, and returns a corresponding checkbox state to match. @return ECheckBoxState::Checked if the associated action is already favorited, ECheckBoxState::Unchecked if not.
- L61 _private prototype_ `void OnFavoriteToggled(ECheckBoxState InNewState);` — Triggers when the user clicks this toggle, adds or removes the associated action to the user's favorites. @param  InNewState	The new state that the user set the checkbox to.
- L63 _private prototype_ `EVisibility GetFavoritedStateVisibility() const;`
- L65 _private prototype_ `virtual FReply OnMouseButtonDoubleClick(const FGeometry& InMyGeometry, const FPointerEvent& InMouseEvent) override;`
- L68 _private member_ `TSharedPtr<FWidgetTemplateViewModel> WidgetViewModel;`

#### class `SPaletteView`  
`class SPaletteView : public SCompoundWidget`  
_L72-146_
- inherits: `SCompoundWidget`
- L75 _public typedef_ `typedef TTextFilter<TSharedPtr<FWidgetViewModel>> WidgetViewModelTextFilter;`
- L78 _public function_ `SLATE_BEGIN_ARGS( SPaletteView )`
- L79 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedPtr<FWidgetBlueprintEditor> InBlueprintEditor);`
- L82 _public prototype_ `virtual ~SPaletteView();`
- L84 _public prototype_ `virtual void Tick( const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime ) override;`
- L87 _public prototype_ `FText GetSearchText() const;` — Gets the text currently displayed in the search box.
- L90 _public prototype_ `void WidgetPalette_OnClick(TSharedPtr<FWidgetViewModel> SelectedItem);` — On item clicked in palette view
- L93 _public prototype_ `void WidgetPalette_OnSelectionChanged(TSharedPtr<FWidgetViewModel> SelectedItem, ESelectInfo::Type SelectInfo);` — On Selected template widget changed in palette view
- L96 _public prototype_ `TSharedPtr<FWidgetTemplate> GetSelectedTemplateWidget() const;` — Gets the selected template widget in palette
- L100 _private prototype_ `void OnGetChildren(TSharedPtr<FWidgetViewModel> Item, TArray< TSharedPtr<FWidgetViewModel> >& Children);`
- L101 _private prototype_ `TSharedRef<ITableRow> OnGenerateWidgetTemplateItem(TSharedPtr<FWidgetViewModel> Item, const TSharedRef<STableViewBase>& OwnerTable);`
- L104 _private prototype_ `void OnSearchChanged(const FText& InFilterText);` — Called when the filter text is changed.
- L106 _private prototype_ `void OnViewModelUpdating();`
- L107 _private prototype_ `void OnViewModelUpdated();`
- L111 _private prototype_ `void LoadItemExpansion();` — Load the expansion state for the TreeView
- L114 _private prototype_ `void SaveItemExpansion();` — Save the expansion state for the TreeView
- L117 _private prototype_ `void GetWidgetFilterStrings(TSharedPtr<FWidgetViewModel> WidgetViewModel, TArray<FString>& OutStrings);` — Gets an array of strings used for filtering/searching the specified widget.
- L119 _private member_ `TWeakPtr<class FWidgetBlueprintEditor> BlueprintEditor;`
- L120 _private member_ `TSharedPtr<FPaletteViewModel> PaletteViewModel;`
- L123 _private typedef_ `typedef TreeFilterHandler<TSharedPtr<FWidgetViewModel>> PaletteFilterHandler;` — Handles filtering the palette based on an IFilter.
- L124 _private member_ `TSharedPtr<PaletteFilterHandler> FilterHandler;`
- L126 _private typedef_ `typedef TArray<TSharedPtr<FWidgetViewModel>> ViewModelsArray;`
- L128 _private member_ `ViewModelsArray TreeWidgetViewModels;` — The root view models which are actually displayed by the TreeView which will be managed by the TreeFilterHandler.
- L130 _private member_ `TSharedPtr< STreeView< TSharedPtr<FWidgetViewModel> > > WidgetTemplatesView;`
- L133 _private member_ `TSharedPtr<class SSearchBox> SearchBoxPtr;` — The search box used to update the filter text
- L136 _private member_ `TSharedPtr<WidgetViewModelTextFilter> WidgetFilter;` — The filter instance which is used by the TreeFilterHandler to filter the TreeView.
- L139 _private member_ `TSet<TSharedPtr<FWidgetViewModel>> ExpandedItems;` — Expended Items in the Tree view
- L142 _private member_ `bool bRefreshRequested;` — Set to true to force a refresh of the treeview
- L145 _private member_ `bool bAllowEditorWidget;` — Are editor widgets supported.

### `Source/Editor/UMGEditor/Private/Palette/SPaletteViewModel.h` (Private)


#### class `FWidgetViewModel`  
`class FWidgetViewModel : public TSharedFromThis<FWidgetViewModel>`  
_L19-56_
- inherits: `TSharedFromThis<FWidgetViewModel>`
- desc: View model for the items in the widget template list
- L22 _public prototype_ `virtual ~FWidgetViewModel() = default;`
- L24 _public prototype_ `virtual FText GetName() const = 0;`
- L26 _public prototype_ `virtual bool IsTemplate() const = 0;`
- L28 _public function_ `virtual bool IsCategory() const`
- L34 _public prototype_ `virtual void GetFilterStrings(TArray<FString>& OutStrings) const = 0;` — @param OutStrings - Returns an array of strings used for filtering/searching this item.
- L36 _public function_ `virtual bool HasFilteredChildTemplates() const`
- L41 _public prototype_ `virtual TSharedRef<ITableRow> BuildRow(const TSharedRef<STableViewBase>& OwnerTable) = 0;`
- L43 _public function_ `virtual void GetChildren(TArray< TSharedPtr<FWidgetViewModel> >& OutChildren)`
- L48 _public function_ `virtual bool IsFavorite() const` — Return true if the widget is a favorite
- L51 _public function_ `virtual void SetFavorite()` — Set the favorite flag
- L55 _public function_ `virtual bool ShouldForceExpansion() const`

#### class `FWidgetTemplateViewModel`  
`class FWidgetTemplateViewModel : public FWidgetViewModel`  
_L58-90_
- inherits: `FWidgetViewModel`
- L61 _public prototype_ `FWidgetTemplateViewModel();`
- L63 _public prototype_ `virtual FText GetName() const override;`
- L65 _public prototype_ `virtual bool IsTemplate() const override;`
- L67 _public prototype_ `virtual void GetFilterStrings(TArray<FString>& OutStrings) const override;`
- L69 _public prototype_ `virtual TSharedRef<ITableRow> BuildRow(const TSharedRef<STableViewBase>& OwnerTable) override;`
- L71 _public prototype_ `FReply OnDraggingWidgetTemplateItem(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent);`
- L74 _public prototype_ `void AddToFavorites();` — Add the widget template to the list of favorites
- L77 _public prototype_ `void RemoveFromFavorites();` — Remove the widget template from the list of favorites
- L80 _public function_ `virtual bool IsFavorite() const override` — Return true if the widget is a favorite
- L83 _public function_ `virtual void SetFavorite() override` — Set the favorite flag
- L85 _public member_ `TSharedPtr<FWidgetTemplate> Template;`
- L86 _public member_ `FWidgetCatalogViewModel* FavortiesViewModel;`
- L89 _private member_ `bool bIsFavorite;` — True is the widget is a favorite. It's keep as a state to prevent a search in the favorite list.

#### class `FWidgetHeaderViewModel`  
`class FWidgetHeaderViewModel : public FWidgetViewModel`  
_L92-144_
- inherits: `FWidgetViewModel`
- L95 _public prototype_ `virtual ~FWidgetHeaderViewModel() = default;`
- L97 _public function_ `virtual FText GetName() const override`
- L102 _public function_ `virtual bool IsTemplate() const override`
- L107 _public function_ `virtual bool IsCategory() const override`
- L112 _public function_ `virtual void GetFilterStrings(TArray<FString>& OutStrings) const override`
- L118 _public function_ `virtual bool HasFilteredChildTemplates() const override`
- L130 _public prototype_ `virtual TSharedRef<ITableRow> BuildRow(const TSharedRef<STableViewBase>& OwnerTable) override;`
- L132 _public prototype_ `virtual void GetChildren(TArray< TSharedPtr<FWidgetViewModel> >& OutChildren) override;`
- L134 _public function_ `virtual bool ShouldForceExpansion() const`
- L136 _public function_ `void SetForceExpansion(bool bInForceExpansion)`
- L138 _public member_ `FText GroupName;`
- L139 _public member_ `TArray< TSharedPtr<FWidgetViewModel> > Children;`
- L143 _private member_ `bool bForceExpansion = false;`

#### class `FWidgetCatalogViewModel`  
`class FWidgetCatalogViewModel : public TSharedFromThis<FWidgetCatalogViewModel>`  
_L146-228_
- inherits: `TSharedFromThis<FWidgetCatalogViewModel>`
- L154 _public prototype_ `FWidgetCatalogViewModel(TSharedPtr<FWidgetBlueprintEditor> InBlueprintEditor);`
- L155 _public prototype_ `virtual ~FWidgetCatalogViewModel();`
- L158 _public prototype_ `void RegisterToEvents();` — Register the View Model to events that should trigger a update
- L161 _public prototype_ `void Update();` — Update the view model if needed and returns true if it did.
- L164 _public function_ `bool NeedUpdate() const` — Returns true if the view model needs to be updated
- L167 _public prototype_ `static void AddToFavorites(const FWidgetTemplateViewModel* WidgetTemplateViewModel);` — Add the widget template to the list of favorites
- L170 _public prototype_ `static void RemoveFromFavorites(const FWidgetTemplateViewModel* WidgetTemplateViewModel);` — Remove the widget template to the list of favorites
- L172 _public typedef_ `typedef TArray< TSharedPtr<FWidgetViewModel> > ViewModelsArray;`
- L173 _public function_ `ViewModelsArray& GetWidgetViewModels()`
- L176 _public member_ `FOnUpdating OnUpdating;` — Fires before the view model is updated
- L179 _public member_ `FOnUpdated OnUpdated;` — Fires after the view model is updated
- L181 _public function_ `virtual void SetSearchText(const FText& InSearchText)`
- L182 _public function_ `FText GetSearchText() const`
- L185 _protected prototype_ `virtual void BuildWidgetList();`
- L187 _protected prototype_ `void AddHeader(TSharedPtr<FWidgetHeaderViewModel>& Header);`
- L188 _protected prototype_ `void AddToFavoriteHeader(TSharedPtr<FWidgetTemplateViewModel>& Favorite);`
- L191 _private function_ `FWidgetCatalogViewModel()`
- L193 _private prototype_ `UWidgetBlueprint* GetBlueprint() const;`
- L194 _private prototype_ `virtual void BuildWidgetTemplateCategory(FString& Category, TArray<TSharedPtr<FWidgetTemplate>>& Templates, TArray<FString>& FavoritesList) = 0;`
- L195 _private prototype_ `void BuildClassWidgetList();`
- L197 _private prototype_ `void AddWidgetTemplate(TSharedPtr<FWidgetTemplate> Template);`
- L200 _private prototype_ `void OnObjectsReplaced(const TMap<UObject*, UObject*>& ReplacementMap);` — Called when a Blueprint is recompiled and live objects are swapped out for replacements
- L203 _private prototype_ `void OnBlueprintReinstanced();` — Requests a rebuild of the widget list if a widget blueprint was compiled
- L206 _private prototype_ `void OnFavoritesUpdated();` — Called when the favorite list is changed
- L209 _private prototype_ `void OnReloadComplete(EReloadCompleteReason Reason);` — Requests a rebuild of the widget list
- L212 _private prototype_ `void HandleOnAssetsDeleted(const TArray<UClass*>& DeletedAssetClasses);` — Requests a rebuild of the widget list if a widget blueprint was deleted
- L214 _private member_ `TWeakPtr<class FWidgetBlueprintEditor> BlueprintEditor;`
- L216 _private typedef_ `typedef TArray<TSharedPtr<FWidgetTemplate>> WidgetTemplateArray;`
- L217 _private member_ `TMap<FString, WidgetTemplateArray> WidgetTemplateCategories;`
- L220 _private member_ `ViewModelsArray WidgetViewModels;` — The source root view models for the tree.
- L223 _private member_ `bool bRebuildRequested;` — Controls rebuilding the list of spawnable widgets
- L225 _private member_ `TSharedPtr<FWidgetHeaderViewModel> FavoriteHeader;`
- L227 _private member_ `FText SearchText;`

#### class `FPaletteViewModel`  
`class FPaletteViewModel : public FWidgetCatalogViewModel`  
_L230-238_
- inherits: `FWidgetCatalogViewModel`
- L233 _public function_ `FPaletteViewModel(TSharedPtr<FWidgetBlueprintEditor> InBlueprintEditor) : FWidgetCatalogViewModel(InBlueprintEditor)`
- L236 _public prototype_ `virtual void BuildWidgetTemplateCategory(FString& Category, TArray<TSharedPtr<FWidgetTemplate>>& Templates, TArray<FString>& FavoritesList) override;`

#### Free symbols / members of external scopes

- L150 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnUpdating) DECLARE_MULTICAST_DELEGATE(FOnUpdated) public: FWidgetCatalogViewModel(TSharedPtr<FWidgetBlueprintEditor> InBlueprintEditor);`
- L151 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnUpdated) public: FWidgetCatalogViewModel(TSharedPtr<FWidgetBlueprintEditor> InBlueprintEditor);`

### `Source/Editor/UMGEditor/Private/Preview/SPreviewDetails.h` (Private)


#### class `UE::UMG::Editor::SPreviewDetails`  
`class SPreviewDetails : public SCompoundWidget, public FNotifyHook`  
_L14-29_
- inherits: `SCompoundWidget,FNotifyHook`
- L16 _private function_ `SLATE_BEGIN_ARGS(SPreviewDetails)`
- L17 _private prototype_ `SLATE_END_ARGS() void Construct(const FArguments& Args, TSharedPtr<FWidgetBlueprintEditor> InBlueprintEditor);`
- L21 _private prototype_ `virtual void NotifyPostChange(const FPropertyChangedEvent& PropertyChangedEvent, class FEditPropertyChain* PropertyThatChanged) override;`
- L24 _private prototype_ `void HandleSelectedObjectChanged();`
- L27 _private member_ `TWeakPtr<FWidgetBlueprintEditor> WeakEditor;`
- L28 _private member_ `TSharedPtr<IDetailsView> DetailsView;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace UMG` (scope `UE`)
- L11 _namespace_ `namespace Editor` (scope `UE::UMG`)

### `Source/Editor/UMGEditor/Private/Preview/SWidgetPreview.h` (Private)


#### class `UE::UMG::Editor::SWidgetPreview`  
`class SWidgetPreview : public SCompoundWidget`  
_L15-29_
- inherits: `SCompoundWidget`
- L18 _public function_ `SLATE_BEGIN_ARGS(SWidgetPreview)`
- L21 _public prototype_ `~SWidgetPreview();`
- L23 _public prototype_ `void Construct(const FArguments& Args, TSharedPtr<FWidgetBlueprintEditor> InWidgetBlueprintEditor);`
- L27 _private member_ `TWeakPtr<FWidgetBlueprintEditor> WeakEditor;`
- L28 _private member_ `TStrongObjectPtr<UUserWidget> CreatedWidget;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace UMG` (scope `UE`)
- L12 _namespace_ `namespace Editor` (scope `UE::UMG`)

### `Source/Editor/UMGEditor/Private/TabFactory/AnimationTabSummoner.h` (Private)


#### struct `FAnimationTabSummoner`  
`struct FAnimationTabSummoner : public FWorkflowTabFactory`  
_L12-27_
- inherits: `FWorkflowTabFactory`
- L15 _public member_ `static const FName TabID;`
- L16 _public member_ `static const FName WidgetAnimSequencerDrawerID;`
- L19 _public prototype_ `FAnimationTabSummoner(TSharedPtr<class FWidgetBlueprintEditor> InBlueprintEditor, bool bInIsDrawerTab = false);`
- L21 _public prototype_ `virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& Info) const override;`
- L22 _public prototype_ `virtual TSharedRef<SDockTab> SpawnTab(const FWorkflowTabSpawnInfo& Info) const override;`
- L25 _protected member_ `TWeakPtr<class FWidgetBlueprintEditor> BlueprintEditor;`
- L26 _protected member_ `bool bIsDrawerTab;`

### `Source/Editor/UMGEditor/Private/TabFactory/BindWidgetTabSummoner.h` (Private)


#### struct `FBindWidgetTabSummoner`  
`struct FBindWidgetTabSummoner : public FWorkflowTabFactory`  
_L12-24_
- inherits: `FWorkflowTabFactory`
- L15 _public member_ `static const FName TabID;`
- L18 _public prototype_ `FBindWidgetTabSummoner(TSharedPtr<FWidgetBlueprintEditor> InBlueprintEditor);`
- L20 _public prototype_ `virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& Info) const override;`
- L23 _protected member_ `TWeakPtr<FWidgetBlueprintEditor> BlueprintEditor;`

### `Source/Editor/UMGEditor/Private/TabFactory/DesignerTabSummoner.h` (Private)


#### struct `FDesignerTabSummoner`  
`struct FDesignerTabSummoner : public FWorkflowTabFactory`  
_L10-23_
- inherits: `FWorkflowTabFactory`
- L13 _public member_ `static const FName ToolPaletteTabID;`
- L14 _public member_ `static const FName TabID;`
- L17 _public prototype_ `FDesignerTabSummoner(TSharedPtr<class FWidgetBlueprintEditor> InBlueprintEditor);`
- L19 _public prototype_ `virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& Info) const override;`
- L22 _protected member_ `TWeakPtr<class FWidgetBlueprintEditor> BlueprintEditor;`

### `Source/Editor/UMGEditor/Private/TabFactory/DetailsTabSummoner.h` (Private)


#### struct `FDetailsTabSummoner`  
`struct FDetailsTabSummoner : public FWorkflowTabFactory`  
_L10-22_
- inherits: `FWorkflowTabFactory`
- L13 _public member_ `static const FName TabID;`
- L16 _public prototype_ `FDetailsTabSummoner(TSharedPtr<class FWidgetBlueprintEditor> InBlueprintEditor);`
- L18 _public prototype_ `virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& Info) const override;`
- L21 _protected member_ `TWeakPtr<class FWidgetBlueprintEditor> BlueprintEditor;`

### `Source/Editor/UMGEditor/Private/TabFactory/HierarchyTabSummoner.h` (Private)


#### struct `FHierarchyTabSummoner`  
`struct FHierarchyTabSummoner : public FWorkflowTabFactory`  
_L10-22_
- inherits: `FWorkflowTabFactory`
- L13 _public member_ `static const FName TabID;`
- L16 _public prototype_ `FHierarchyTabSummoner(TSharedPtr<class FWidgetBlueprintEditor> InBlueprintEditor);`
- L18 _public prototype_ `virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& Info) const override;`
- L21 _protected member_ `TWeakPtr<class FWidgetBlueprintEditor> BlueprintEditor;`

### `Source/Editor/UMGEditor/Private/TabFactory/LibraryTabSummoner.h` (Private)


#### struct `FLibraryTabSummoner`  
`struct FLibraryTabSummoner : public FWorkflowTabFactory`  
_L10-22_
- inherits: `FWorkflowTabFactory`
- L13 _public member_ `static const FName TabID;`
- L16 _public prototype_ `FLibraryTabSummoner(TSharedPtr<class FWidgetBlueprintEditor> InBlueprintEditor);`
- L18 _public prototype_ `virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& Info) const override;`
- L21 _protected member_ `TWeakPtr<class FWidgetBlueprintEditor> BlueprintEditor;`

### `Source/Editor/UMGEditor/Private/TabFactory/NavigationTabSummoner.h` (Private)


#### struct `FNavigationTabSummoner`  
`struct FNavigationTabSummoner : public FWorkflowTabFactory`  
_L10-22_
- inherits: `FWorkflowTabFactory`
- L13 _public member_ `static const FName TabID;`
- L16 _public prototype_ `FNavigationTabSummoner(TSharedPtr<class FWidgetBlueprintEditor> InBlueprintEditor);`
- L18 _public prototype_ `virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& Info) const override;`
- L21 _protected member_ `TWeakPtr<class FWidgetBlueprintEditor> BlueprintEditor;`

### `Source/Editor/UMGEditor/Private/TabFactory/PaletteTabSummoner.h` (Private)


#### struct `FPaletteTabSummoner`  
`struct FPaletteTabSummoner : public FWorkflowTabFactory`  
_L10-22_
- inherits: `FWorkflowTabFactory`
- L13 _public member_ `static const FName TabID;`
- L16 _public prototype_ `FPaletteTabSummoner(TSharedPtr<class FWidgetBlueprintEditor> InBlueprintEditor);`
- L18 _public prototype_ `virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& Info) const override;`
- L21 _protected member_ `TWeakPtr<class FWidgetBlueprintEditor> BlueprintEditor;`

### `Source/Editor/UMGEditor/Private/TabFactory/PreviewDetailsTabSummoner.h` (Private)


#### struct `UE::UMG::Editor::FPreviewDetailsTabSummoner`  
`struct FPreviewDetailsTabSummoner : public FWorkflowTabFactory`  
_L13-25_
- inherits: `FWorkflowTabFactory`
- L16 _public member_ `static const FName TabID;`
- L19 _public prototype_ `FPreviewDetailsTabSummoner(TSharedPtr<FWidgetBlueprintEditor> InBlueprintEditor);`
- L21 _public prototype_ `virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& Info) const override;`
- L24 _protected member_ `TWeakPtr<FWidgetBlueprintEditor> BlueprintEditor;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace UMG` (scope `UE`)
- L10 _namespace_ `namespace Editor` (scope `UE::UMG`)

### `Source/Editor/UMGEditor/Private/TabFactory/PreviewTabSummoner.h` (Private)


#### struct `UE::UMG::Editor::FWidgetPreviewTabSummoner`  
`struct FWidgetPreviewTabSummoner : public FWorkflowTabFactory`  
_L12-24_
- inherits: `FWorkflowTabFactory`
- L15 _public member_ `static const FName TabID;`
- L18 _public prototype_ `FWidgetPreviewTabSummoner(TSharedPtr<FWidgetBlueprintEditor> InBlueprintEditor);`
- L20 _public prototype_ `virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& Info) const override;`
- L23 _protected member_ `TWeakPtr<FWidgetBlueprintEditor> BlueprintEditor;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace UMG` (scope `UE`)
- L9 _namespace_ `namespace Editor` (scope `UE::UMG`)

### `Source/Editor/UMGEditor/Private/ToolPalette/WidgetEditorModeUILayer.h` (Private)


#### class `UWidgetEditorModeUISubsystem`  
`class UWidgetEditorModeUISubsystem : public UAssetEditorUISubsystem`  
_L9-17_
- reflection: `UCLASS()`
- inherits: `UAssetEditorUISubsystem`
- L14 _public prototype_ `virtual void Initialize(FSubsystemCollectionBase& Collection) override;`
- L15 _public prototype_ `virtual void Deinitialize() override;`
- L16 _public prototype_ `virtual void RegisterLayoutExtensions(FLayoutExtender& Extender) override;`

#### class `FWidgetEditorModeUILayer`  
`class FWidgetEditorModeUILayer : public FAssetEditorModeUILayer`  
_L20-30_
- inherits: `FAssetEditorModeUILayer`
- L24 _public prototype_ `FWidgetEditorModeUILayer(const IToolkitHost* InToolkitHost);`
- L26 _public prototype_ `void OnToolkitHostingStarted(const TSharedRef<IToolkit>& Toolkit) override;`
- L27 _public prototype_ `void OnToolkitHostingFinished(const TSharedRef<IToolkit>& Toolkit) override;`
- L29 _public prototype_ `TSharedPtr<FWorkspaceItem> GetModeMenuCategory() const override;`

### `Source/Editor/UMGEditor/Private/UIComponentClipboardExtension.h` (Private)


#### class `UUIComponentWidgetPair`  
`class UUIComponentWidgetPair : public UObject`  
_L14-27_
- reflection: `UCLASS()`
- inherits: `UObject`
- L20 _public function_ `UUIComponentWidgetPair()`
- L23 _public member_ `FName WidgetName;` — `UPROPERTY()`
- L26 _public member_ `TObjectPtr<UUIComponent> Component;` — `UPROPERTY(instanced)`

#### class `FUIComponentClipboardExtension`  
`class FUIComponentClipboardExtension : public IClipboardExtension`  
_L29-70_
- inherits: `IClipboardExtension`
- L33 _private prototype_ `virtual void AppendToClipboard(const UWidget* Widget, const FExportArgs& ExportArgs) override;`
- L34 _private prototype_ `virtual bool CanAppendToClipboard(const UWidget* Widget) const override;`
- L35 _private prototype_ `virtual void ProcessImportedText(const UWidgetBlueprint* WidgetBlueprint, const FString& TextToImport, UPackage*& TempPackage) override;`
- L36 _private prototype_ `virtual bool CanImportFromClipboard(const UWidget* Widget) const override;`
- L37 _private prototype_ `virtual void ImportDataToWidget(const UWidget* Widget, FName OldWidgetName) override;`
- L38 _private prototype_ `virtual bool CanWidgetAcceptPaste(const UWidget* Widget) const override;`
- L69 _private member_ `FExtensionTextFactory Factory;`

#### class `FUIComponentClipboardExtension::FExtensionTextFactory`  
`class FExtensionTextFactory : public FCustomizableTextObjectFactory`  
_L43-67_
- inherits: `FCustomizableTextObjectFactory`
- L46 _public prototype_ `FExtensionTextFactory();`
- L49 _public prototype_ `virtual bool CanCreateClass(UClass* ObjectClass, bool& bOmitSubObjs) const override;`
- L50 _public prototype_ `virtual void ProcessConstructedObject(UObject* NewObject) override;`
- L53 _public prototype_ `void AddProcessedComponentsTo(const UWidget* Widget, FName OldWidgetName);`
- L55 _public function_ `void Reinit()`
- L60 _public function_ `bool IsEmpty() const`
- L66 _private member_ `TArray<UUIComponentWidgetPair*> NewComponentWidgetPairs;`

### `Source/Editor/UMGEditor/Private/UMGEditorActions.h` (Private)


#### class `FUMGEditorCommands`  
`class FUMGEditorCommands : public TCommands<FUMGEditorCommands>`  
_L16-55_
- inherits: `TCommands<FUMGEditorCommands>`
- desc: Unreal UMG editor actions
- L20 _public function_ `FUMGEditorCommands() : TCommands<FUMGEditorCommands> ( "UMGEditor",`
- L33 _public member_ `TSharedPtr< FUICommandInfo > CreateNativeBaseClass;` — UMG Editor Commands
- L34 _public member_ `TSharedPtr< FUICommandInfo > ExportAsPNG;`
- L35 _public member_ `TSharedPtr< FUICommandInfo > SetImageAsThumbnail;`
- L36 _public member_ `TSharedPtr< FUICommandInfo > ClearCustomThumbnail;`
- L37 _public member_ `TSharedPtr< FUICommandInfo > OpenAnimDrawer;`
- L39 _public member_ `TSharedPtr< FUICommandInfo > DismissOnCompile_ErrorsAndWarnings;`
- L40 _public member_ `TSharedPtr< FUICommandInfo > DismissOnCompile_Errors;`
- L41 _public member_ `TSharedPtr< FUICommandInfo > DismissOnCompile_Warnings;`
- L42 _public member_ `TSharedPtr< FUICommandInfo > DismissOnCompile_Never;`
- L44 _public member_ `TSharedPtr< FUICommandInfo > CreateOnCompile_ErrorsAndWarnings;`
- L45 _public member_ `TSharedPtr< FUICommandInfo > CreateOnCompile_Errors;`
- L46 _public member_ `TSharedPtr< FUICommandInfo > CreateOnCompile_Warnings;`
- L47 _public member_ `TSharedPtr< FUICommandInfo > CreateOnCompile_Never;`
- L52 _public prototype_ `virtual void RegisterCommands() override;` — Initialize commands

### `Source/Editor/UMGEditor/Private/Utility/WidgetSlotPair.h` (Private)


#### class `UWidgetSlotPair`  
`class UWidgetSlotPair : public UObject`  
_L13-38_
- reflection: `UCLASS()`
- inherits: `UObject`
- L19 _public prototype_ `UWidgetSlotPair();`
- L21 _public prototype_ `void SetWidget(UWidget* Widget);`
- L23 _public prototype_ `void SetWidgetName(FName WidgetName);`
- L24 _public prototype_ `FName GetWidgetName() const;`
- L26 _public prototype_ `void GetSlotProperties(TMap<FName, FString>& OutSlotProperties) const;`
- L31 _private member_ `FName WidgetName;` — `UPROPERTY()`
- L34 _private member_ `TArray<FName> SlotPropertyNames;` — `UPROPERTY()`
- L37 _private member_ `TArray<FString> SlotPropertyValues;` — `UPROPERTY()`

### `Source/Editor/UMGEditor/Private/WidgetBlueprintEditorToolbar.h` (Private)


#### class `FWidgetBlueprintEditorToolbar`  
`class FWidgetBlueprintEditorToolbar : public TSharedFromThis<FWidgetBlueprintEditorToolbar>`  
_L15-36_
- inherits: `TSharedFromThis<FWidgetBlueprintEditorToolbar>`
- desc: Handles all of the toolbar related construction for the widget blueprint editor.
- L20 _public prototype_ `FWidgetBlueprintEditorToolbar(TSharedPtr<FWidgetBlueprintEditor>& InWidgetEditor);` — Constructor
- L25 _public prototype_ `void AddWidgetBlueprintEditorModesToolbar(TSharedPtr<FExtender> Extender);` — Builds the modes toolbar for the widget blueprint editor.
- L27 _public prototype_ `void AddWidgetReflector(UToolMenu* InMenu);`
- L29 _public prototype_ `void AddToolPalettes(UToolMenu* InMenu);`
- L33 _public prototype_ `void FillWidgetBlueprintEditorModesToolbar(FToolBarBuilder& ToolbarBuilder);`
- L35 _public member_ `TWeakPtr<FWidgetBlueprintEditor> WidgetEditor;`

### `Source/Editor/UMGEditor/Private/Widgets/SBindWidgetView.h` (Private)


#### class `FBindWidgetCommands`  
`class FBindWidgetCommands : public TCommands<FBindWidgetCommands>`  
_L24-36_
- inherits: `TCommands<FBindWidgetCommands>`
- L27 _public function_ `FBindWidgetCommands() : TCommands<FBindWidgetCommands>(TEXT("BindWidget"), NSLOCTEXT("Contexts", "Bind Widget", "Bind Widget"), NAME_None, FAppStyle::GetAppStyleSetName())`
- L33 _public prototype_ `virtual void RegisterCommands() override;` — Initialize commands
- L35 _public member_ `TSharedPtr<FUICommandInfo> GotoNativeVarDefinition;`

#### class `SBindWidgetView`  
`class SBindWidgetView : public SCompoundWidget`  
_L41-60_
- inherits: `SCompoundWidget`
- L44 _public function_ `SLATE_BEGIN_ARGS(SBindWidgetView)`
- L45 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedPtr<FWidgetBlueprintEditor> InBlueprintEditor);`
- L48 _public prototype_ `virtual ~SBindWidgetView();`
- L50 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L53 _private prototype_ `void HandleBlueprintChanged(UBlueprint* InBlueprint);`
- L54 _private prototype_ `void HandleObjectsReplaced(const TMap<UObject*, UObject*>& ReplacementMap);`
- L57 _private member_ `TWeakPtr<FWidgetBlueprintEditor> BlueprintEditor;`
- L58 _private member_ `TWeakPtr<UE::UMG::SBindWidgetView> ListView;`
- L59 _private member_ `bool bRefreshRequested;`

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace UE`
- L18 _namespace_ `namespace UMG` (scope `UE`)

### `Source/Editor/UMGEditor/Private/Widgets/SFieldNotificationGraphPin.h` (Private)


#### class `UE::FieldNotification::SFieldNotificationGraphPin`  
`class SFieldNotificationGraphPin : public SGraphPin`  
_L17-38_
- inherits: `SGraphPin`
- L20 _public prototype_ `DECLARE_DELEGATE_OneParam(FFieldNotificationGraphPinSetValue, FFieldNotificationId);`
- L22 _public function_ `SLATE_BEGIN_ARGS(SFieldNotificationGraphPin)`
- L23 _public prototype_ `SLATE_EVENT(FFieldNotificationGraphPinSetValue, OnSetValue) SLATE_END_ARGS() void Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj);`
- L29 _public prototype_ `virtual TSharedRef<SWidget> GetDefaultValueWidget() override;`
- L33 _private prototype_ `FFieldNotificationId GetValue() const;`
- L34 _private prototype_ `void SetValue(FFieldNotificationId NewValue);`
- L37 _private member_ `FFieldNotificationGraphPinSetValue OnSetValue;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace FieldNotification` (scope `UE`)
- L20 _delegate_ `DECLARE_DELEGATE_OneParam(FFieldNotificationGraphPinSetValue, FFieldNotificationId);`

### `Source/Editor/UMGEditor/Private/Widgets/SFieldNotificationPicker.h` (Private)


#### class `UE::FieldNotification::SFieldNotificationPicker`  
`class SFieldNotificationPicker : public SCompoundWidget`  
_L33-62_
- inherits: `SCompoundWidget`
- desc: A widget which allows the user to enter a FieldNotificationId or discover it from a drop menu.
- L36 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnValueChanged, FFieldNotificationId);`
- L38 _public function_ `SLATE_BEGIN_ARGS(SFieldNotificationPicker)`
- L40 _public prototype_ `SLATE_ATTRIBUTE(FFieldNotificationId, Value) SLATE_EVENT(FOnValueChanged, OnValueChanged) SLATE_ATTRIBUTE(UClass*, FromClass) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L48 _public prototype_ `FFieldNotificationId GetCurrentValue() const;`
- L51 _private prototype_ `void HandleComboBoxChanged(TSharedPtr<FFieldNotificationId> InItem, ESelectInfo::Type InSeletionInfo);`
- L52 _private prototype_ `TSharedRef<SWidget> HandleGenerateWidget(TSharedPtr<FFieldNotificationId> InItem);`
- L53 _private prototype_ `void HandleComboOpening();`
- L54 _private prototype_ `FText HandleComboBoxValueAsText() const;`
- L57 _private member_ `TSharedPtr<SComboBox<TSharedPtr<FFieldNotificationId>>> PickerBox;`
- L58 _private member_ `TArray<TSharedPtr<FFieldNotificationId>> FieldNotificationIdsSource;`
- L59 _private member_ `FOnValueChanged OnValueChangedDelegate;`
- L60 _private member_ `TAttribute<FFieldNotificationId> ValueAttribute;`
- L61 _private member_ `TAttribute<UClass*> FromClassAttribute;`

#### Free symbols / members of external scopes

- L27 _namespace_ `namespace UE`
- L27 _namespace_ `namespace FieldNotification` (scope `UE`)
- L36 _delegate_ `DECLARE_DELEGATE_OneParam(FOnValueChanged, FFieldNotificationId);`

### `Source/Editor/UMGEditor/Private/Widgets/SGraphNodeCreateWidget.h` (Private)


#### class `SGraphNodeCreateWidget`  
`class SGraphNodeCreateWidget : public SGraphNodeK2Default`  
_L11-17_
- inherits: `SGraphNodeK2Default`
- L15 _public prototype_ `virtual TSharedPtr<SGraphPin> CreatePinWidget(UEdGraphPin* Pin) const override;` — SGraphNode interface

### `Source/Editor/UMGEditor/Public/BlueprintModes/WidgetBlueprintApplicationMode.h` (Public)


#### class `FWidgetBlueprintApplicationMode`  
`class FWidgetBlueprintApplicationMode : public FBlueprintEditorApplicationMode`  
_L19-44_
- inherits: `FBlueprintEditorApplicationMode`
- L22 _public prototype_ `FWidgetBlueprintApplicationMode(TSharedPtr<class FWidgetBlueprintEditor> InWidgetEditor, FName InModeName);`
- L25 _public prototype_ `virtual void PreDeactivateMode() override;` — FApplicationMode interface
- L26 _public prototype_ `virtual void PostActivateMode() override;`
- L30 _public member_ `mutable FOnWidgetBlueprintModeTransition OnPostActivateMode;` — Called at start of PostActivateMode
- L33 _public member_ `mutable FOnWidgetBlueprintModeTransition OnPreDeactivateMode;` — Called at end of PreDeactivateMode
- L36 _public prototype_ `TSharedPtr<class FWidgetBlueprintEditor> GetBlueprintEditor() const;`
- L37 _public prototype_ `UWidgetBlueprint* GetBlueprint() const;`
- L40 _protected member_ `TWeakPtr<class FWidgetBlueprintEditor> MyWidgetBlueprintEditor;`
- L43 _protected member_ `FWorkflowAllowedTabSet TabFactories;` — Set of spawnable tabs in the mode

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API UMGEDITOR_API`
- L17 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnWidgetBlueprintModeTransition, class FWidgetBlueprintApplicationMode&);`
- L17 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnWidgetBlueprintModeTransition, class FWidgetBlueprintApplicationMode&);`

### `Source/Editor/UMGEditor/Public/BlueprintModes/WidgetBlueprintApplicationModes.h` (Public)


#### struct `FWidgetBlueprintApplicationModes`  
`struct FWidgetBlueprintApplicationModes`  
_L15-32_
- desc: This is the list of IDs for widget blueprint editor modes
- L18 _public member_ `static const FName DesignerMode;` — Mode constants
- L19 _public member_ `static const FName GraphMode;`
- L21 _public member_ `static const FName DebugMode;` — `UE_DEPRECATED(5.3, "DebugMode is deprecated. Use PreviewMode instead.")`
- L22 _public member_ `static const FName PreviewMode;`
- L24 _public prototype_ `static FText GetLocalizedMode(const FName InMode);`
- L27 _public prototype_ `static bool IsDebugModeEnabled();` — `UE_DEPRECATED(5.3, "IsDebugModeEnabled is deprecated. Use IsPreviewModeEnabled instead.")`
- L28 _public prototype_ `static bool IsPreviewModeEnabled();`
- L31 _private prototype_ `FWidgetBlueprintApplicationModes() = delete;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API UMGEDITOR_API`

### `Source/Editor/UMGEditor/Public/Components/AssetThumbnailWidget.h` (Public)


#### enum `EThumbnailLabelType_BlueprintType`  
`enum class EThumbnailLabelType_BlueprintType : uint8`  
_L17-22_
- reflection: `UENUM(BlueprintType, meta = (DisplayName = "EThumbnailLabelType"))`
- L19 _public enumerator_ `ClassName`
- L20 _public enumerator_ `AssetName`
- L21 _public enumerator_ `NoLabel`

#### enum `EThumbnailColorStripOrientation_BlueprintType`  
`enum class EThumbnailColorStripOrientation_BlueprintType : uint8`  
_L25-31_
- reflection: `UENUM(BlueprintType, meta = (DisplayName = "EThumbnailColorStripOrientation"))`
- L28 _public enumerator_ `HorizontalBottomEdge` — Display the color strip as a horizontal line along the bottom edge
- L30 _public enumerator_ `VerticalRightEdge` — Display the color strip as a vertical line along the right edge

#### struct `FAssetThumbnailWidgetSettings`  
`struct FAssetThumbnailWidgetSettings`  
_L37-88_
- reflection: `USTRUCT(BlueprintType)`
- desc: Copied mostly from FAssetThumbnailConfig
- L42 _public member_ `bool bForceGenericThumbnail = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appearance")`
- L45 _public member_ `bool bAllowHintText = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appearance")`
- L48 _public member_ `bool bAllowRealTimeOnHovered = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appearance")`
- L51 _public member_ `bool bAllowAssetSpecificThumbnailOverlay = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appearance")`
- L54 _public member_ `EThumbnailLabelType_BlueprintType ThumbnailLabel = EThumbnailLabelType_BlueprintType::ClassName;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appearance")`
- L57 _public member_ `FGetHighlightTextDelegate HighlightedTextDelegate;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appearance")`
- L60 _public member_ `FLinearColor HintColorAndOpacity = FLinearColor(0.0f, 0.0f, 0.0f, 0.0f);` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appearance", meta = (EditCondition = "bAllowHintText", EditConditionHides))`
- L64 _public member_ `bool bOverrideAssetTypeColor = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appearance")` — Whether to override the asset type's colour
- L67 _public member_ `FLinearColor AssetTypeColorOverride = FLinearColor(0.0f, 0.0f, 0.0f, 0.0f);` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appearance", meta = (EditCondition = "bOverrideAssetTypeColor", EditConditionHides))`
- L71 _public member_ `FMargin Padding;` — `UE_DEPRECATED(5.6, "Border padding is handled by the thumbnail internally, this will no longer have any effect in future release.")` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appearance", meta = (ToolTip = "Warning: Border padding is handled by the thumbnail internally, this will no longer have any effect in future release"))`
- L74 _public member_ `int32 GenericThumbnailSize = 64;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appearance")`
- L77 _public member_ `EThumbnailColorStripOrientation_BlueprintType ColorStripOrientation = EThumbnailColorStripOrientation_BlueprintType::HorizontalBottomEdge;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appearance")`
- L79 _public prototype_ `FAssetThumbnailConfig ToThumbnailConfig() const;`
- L82 _public prototype_ `FAssetThumbnailWidgetSettings() = default;`
- L83 _public prototype_ `FAssetThumbnailWidgetSettings(const FAssetThumbnailWidgetSettings&) = default;`
- L84 _public prototype_ `FAssetThumbnailWidgetSettings& operator=(const FAssetThumbnailWidgetSettings&) = default;`
- L85 _public prototype_ `FAssetThumbnailWidgetSettings(FAssetThumbnailWidgetSettings&&) = default;`
- L86 _public prototype_ `FAssetThumbnailWidgetSettings& operator=(FAssetThumbnailWidgetSettings&&) = default;`

#### class `UAssetThumbnailWidget`  
`class UAssetThumbnailWidget : public UWidget`  
_L92-143_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UWidget`
- desc: This widget can be given an asset and it will render its thumbnail. Editor-only.
- L98 _public prototype_ `void SetThumbnailSettings(const FAssetThumbnailWidgetSettings& InThumbnailSettings);` — `UFUNCTION(BlueprintCallable, Category = "Appearance")`
- L99 _public function_ `FAssetThumbnailWidgetSettings GetThumbnailSettings() const`
- L102 _public prototype_ `void SetAsset(const FAssetData& AssetData);` — `UFUNCTION(BlueprintCallable, Category = "Appearance")`
- L104 _public prototype_ `void SetAssetByObject(UObject* Object);` — `UFUNCTION(BlueprintCallable, Category = "Appearance")`
- L108 _public prototype_ `void SetResolution(const FIntPoint& InResolution);` — `UFUNCTION(Blueprintcallable, Category = "Appearance")` — Sets the resolution for the rendered thumbnail.
- L112 _public function_ `FIntPoint GetResolution() const` — `UFUNCTION(BlueprintPure, Category = "Appearance")` — Gets the resolution of the rendered thumbnail.
- L115 _public prototype_ `virtual void SynchronizeProperties() override;`
- L116 _public prototype_ `virtual void ReleaseSlateResources(bool bReleaseChildren) override;`
- L117 _public prototype_ `virtual TSharedRef<SWidget> RebuildWidget() override;`
- L118 _public prototype_ `virtual const FText GetPaletteCategory() override;`
- L125 _private member_ `FAssetData AssetToShow;` — `UPROPERTY(EditAnywhere, Category = "Appearance")` — The asset of which to show the thumbnail.
- L129 _private member_ `FIntPoint Resolution = { 64, 64};` — `UPROPERTY(EditAnywhere, BlueprintGetter = "GetResolution", BlueprintSetter = "SetResolution", Category = "Appearance", meta = (ClampMin = "1", ClampMax = "1024"))` — Desired size of the thumbnail
- L133 _private member_ `FAssetThumbnailWidgetSettings ThumbnailSettings;` — `UPROPERTY(EditAnywhere, Getter, Setter, BlueprintSetter = "SetThumbnailSettings", Category = "Appearance")` — Behaviour and style of the widget
- L136 _private member_ `TSharedPtr<FAssetThumbnail> ThumbnailRenderer;` — Creates ThumbnailAssetWidget.
- L139 _private member_ `TSharedPtr<SBorder> DisplayedWidget;` — Wraps either an error widget or the contents of FAssetThumbnail::MakeThumbnailWidget.
- L142 _private prototype_ `void UpdateNativeAssetThumbnailWidget();` — Updates or creates ThumbnailRenderer and sets the contents of DisplayedWidget.

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API UMGEDITOR_API`
- L33 _delegate_ `DECLARE_DYNAMIC_DELEGATE_RetVal(FText, FGetHighlightTextDelegate);`
- L33 _prototype_ `DECLARE_DYNAMIC_DELEGATE_RetVal(FText, FGetHighlightTextDelegate);`

### `Source/Editor/UMGEditor/Public/Customizations/IBlueprintWidgetCustomizationExtender.h` (Public)


#### class `IBlueprintWidgetCustomizationExtender`  
`class IBlueprintWidgetCustomizationExtender : public TSharedFromThis<IBlueprintWidgetCustomizationExtender>`  
_L14-26_
- inherits: `TSharedFromThis<IBlueprintWidgetCustomizationExtender>`
- desc: Details customization extender for UWidgets.
- L17 _public prototype_ `virtual ~IBlueprintWidgetCustomizationExtender() = default;`
- L25 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& InDetailLayout, const TArrayView<UWidget*> InWidgets, const TSharedRef<FWidgetBlueprintEditor>& InWidgetBlueprintEditor) = 0;` — Customizes given widgets. @param InDetailLayout				detail layout builder for customization. @param InWidget						widgets to be customized. @param InWidgetBlueprintEditor		widget blueprint editor that is used for widgets being customized.

### `Source/Editor/UMGEditor/Public/Designer/SDesignSurface.h` (Public)


#### class `SDesignSurface`  
`class SDesignSurface : public SCompoundWidget`  
_L34-166_
- inherits: `SCompoundWidget`
- L38 _public function_ `SLATE_BEGIN_ARGS( SDesignSurface ) : _AllowContinousZoomInterpolation(false)`
- L43 _public prototype_ `SLATE_DEFAULT_SLOT(FArguments, Content) SLATE_ATTRIBUTE(bool, AllowContinousZoomInterpolation) SLATE_END_ARGS() void Construct(const FArguments& InArgs);` — Slot for this designers content (optional)
- L51 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;` — SWidget interface
- L52 _public prototype_ `virtual FCursorReply OnCursorQuery(const FGeometry& MyGeometry, const FPointerEvent& CursorEvent) const override;`
- L53 _public prototype_ `virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L54 _public prototype_ `virtual FReply OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L55 _public prototype_ `virtual FReply OnMouseMove(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L56 _public prototype_ `virtual FReply OnMouseWheel(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L57 _public prototype_ `virtual FReply OnTouchGesture(const FGeometry& MyGeometry, const FPointerEvent& GestureEvent) override;`
- L58 _public prototype_ `virtual FReply OnTouchEnded(const FGeometry& MyGeometry, const FPointerEvent& InTouchEvent) override;`
- L59 _public prototype_ `virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;`
- L60 _public function_ `virtual bool SupportsKeyboardFocus() const override`
- L64 _public prototype_ `float GetZoomAmount() const;` — Gets the current zoom factor.
- L66 _public prototype_ `FVector2D GraphCoordToPanelCoord(const FVector2D& GraphSpaceCoordinate) const;`
- L67 _public prototype_ `FVector2D PanelCoordToGraphCoord(const FVector2D& PanelSpaceCoordinate) const;`
- L70 _protected prototype_ `virtual void OnPaintBackground(const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId) const;`
- L72 _protected prototype_ `void PaintBackgroundAsLines(const FSlateBrush* BackgroundImage, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32& DrawLayerId) const;`
- L74 _protected prototype_ `void ChangeZoomLevel(int32 ZoomLevelDelta, const FVector2D& WidgetSpaceZoomOrigin, bool bOverrideZoomLimiting);`
- L76 _protected prototype_ `void PostChangedZoom();`
- L78 _protected prototype_ `bool ScrollToLocation(const FGeometry& MyGeometry, FVector2D DesiredCenterPosition, const float InDeltaTime);`
- L80 _protected prototype_ `bool ZoomToLocation(const FVector2D& CurrentSizeWithoutZoom, const FVector2D& DesiredSize, bool bDoneScrolling);`
- L82 _protected prototype_ `void ZoomToFit(bool bInstantZoom);`
- L84 _protected prototype_ `FText GetZoomText() const;`
- L85 _protected prototype_ `FSlateColor GetZoomTextColorAndOpacity() const;`
- L87 _protected prototype_ `FVector2D GetViewOffset() const;`
- L89 _protected prototype_ `FSlateRect ComputeSensibleBounds() const;`
- L92 _protected prototype_ `virtual FSlateRect ComputeAreaBounds() const;`
- L93 _protected prototype_ `virtual float GetGridScaleAmount() const;`
- L94 _protected prototype_ `virtual int32 GetGraphRulePeriod() const;`
- L95 _protected prototype_ `virtual int32 GetSnapGridSize() const = 0;`
- L99 _protected member_ `FVector2D ViewOffset;` — The position within the graph at which the user is looking
- L102 _protected member_ `FVector2D GridOrigin;` — The position in the grid to begin drawing at.
- L105 _protected member_ `bool bDrawGridLines;` — Should we render the grid lines?
- L108 _protected member_ `int32 PreviousZoomLevel;` — Previous Zoom Level
- L111 _protected member_ `int32 ZoomLevel;` — How zoomed in/out we are. e.g. 0.25f results in quarter-sized nodes.
- L114 _protected member_ `bool bIsPanning;` — Are we panning the view at the moment?
- L117 _protected member_ `bool bIsZooming;` — Are we zooming the view with trackpad at the moment?
- L120 _protected member_ `TAttribute<bool> AllowContinousZoomInterpolation;` — Allow continuous zoom interpolation?
- L123 _protected member_ `FCurveSequence ZoomLevelGraphFade;` — Fade on zoom for graph
- L126 _protected member_ `FCurveSequence ZoomLevelFade;` — Curve that handles fading the 'Zoom +X' text
- L129 _protected member_ `TUniquePtr<FZoomLevelsContainer> ZoomLevels;` — The interface for mapping ZoomLevel values to actual node scaling values
- L131 _protected member_ `bool bAllowContinousZoomInterpolation;`
- L133 _protected member_ `bool bTeleportInsteadOfScrollingWhenZoomingToFit;`
- L135 _protected member_ `FVector2D ZoomTargetTopLeft;`
- L136 _protected member_ `FVector2D ZoomTargetBottomRight;`
- L137 _protected member_ `FVector2D ZoomToFitPadding;`
- L140 _protected member_ `double TotalMouseDelta;` — The Y component of mouse drag (used when zooming)
- L143 _protected member_ `FVector2D ZoomStartOffset;` — Offset in the panel the user started the LMB+RMB zoom from
- L146 _protected member_ `FVector2D ViewOffsetStart;`
- L149 _protected member_ `FVector2D MouseDownPositionAbsolute;`
- L152 _protected member_ `float TotalGestureMagnify;` — Cumulative magnify delta from trackpad gesture
- L155 _protected member_ `bool bRequireControlToOverZoom;` — Does the user need to press Control in order to over-zoom.
- L159 _private prototype_ `EActiveTimerReturnType HandleZoomToFit(double InCurrentTime, float InDeltaTime);` — Active timer that handles deferred zooming until the target zoom is reached
- L162 _private member_ `TWeakPtr<FActiveTimerHandle> ActiveTimerHandle;` — The handle to the active timer
- L165 _private member_ `bool bDeferredZoomToExtents;` — A flag noting if we have a pending zoom to extents operation to perform next tick.

#### Free symbols / members of external scopes

- L23 _macro_ `#define UE_API UMGEDITOR_API`

### `Source/Editor/UMGEditor/Public/Designer/SDesignerView.h` (Public)


#### class `SDesignerView`  
`class SDesignerView : public SDesignSurface, public FGCObject, public IUMGDesigner`  
_L48-446_
- inherits: `SDesignSurface,FGCObject,IUMGDesigner`
- desc: The designer for widgets.  Allows for laying out widgets in a drag and drop environment.
- L52 _public function_ `SLATE_BEGIN_ARGS( SDesignerView )`
- L53 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedPtr<class FWidgetBlueprintEditor> InBlueprintEditor);`
- L56 _public prototype_ `virtual ~SDesignerView();`
- L58 _public prototype_ `EActiveTimerReturnType EnsureTick(double InCurrentTime, float InDeltaTime);`
- L60 _public prototype_ `TSharedRef<SWidget> CreateOverlayUI();`
- L63 _public prototype_ `virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;` — SWidget interface
- L64 _public prototype_ `virtual FReply OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L65 _public prototype_ `virtual FReply OnMouseMove(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L66 _public prototype_ `virtual void OnMouseEnter(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L67 _public prototype_ `virtual void OnMouseLeave(const FPointerEvent& MouseEvent) override;`
- L69 _public prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;`
- L70 _public prototype_ `virtual FReply OnKeyUp(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;`
- L72 _public prototype_ `virtual void Tick( const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime ) override;`
- L74 _public prototype_ `virtual FReply OnDragDetected(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L75 _public prototype_ `virtual void OnDragEnter(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;`
- L76 _public prototype_ `virtual void OnDragLeave(const FDragDropEvent& DragDropEvent) override;`
- L77 _public prototype_ `virtual FReply OnDragOver(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;`
- L78 _public prototype_ `virtual FReply OnDrop(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;`
- L81 _public prototype_ `void Register(TSharedRef<FDesignerExtension> Extension);`
- L82 _public prototype_ `void Unregister(TSharedRef<FDesignerExtension> Extension);`
- L85 _public prototype_ `virtual float GetPreviewScale() const override;` — IUMGDesigner interface
- L86 _public prototype_ `virtual const TSet<FWidgetReference>& GetSelectedWidgets() const override;`
- L87 _public prototype_ `virtual FWidgetReference GetSelectedWidget() const override;`
- L88 _public prototype_ `virtual ETransformMode::Type GetTransformMode() const override;`
- L89 _public prototype_ `virtual FGeometry GetDesignerGeometry() const override;`
- L90 _public prototype_ `virtual FVector2D GetWidgetOriginAbsolute() const;`
- L91 _public prototype_ `virtual bool GetWidgetGeometry(const FWidgetReference& Widget, FGeometry& Geometry) const override;`
- L92 _public prototype_ `virtual bool GetWidgetGeometry(const UWidget* PreviewWidget, FGeometry& Geometry) const override;`
- L93 _public prototype_ `virtual bool GetWidgetParentGeometry(const FWidgetReference& Widget, FGeometry& Geometry) const override;`
- L94 _public prototype_ `virtual FGeometry MakeGeometryWindowLocal(const FGeometry& WidgetGeometry) const override;`
- L95 _public prototype_ `virtual void MarkDesignModifed(bool bRequiresRecompile) override;`
- L96 _public prototype_ `virtual void PushDesignerMessage(const FText& Message) override;`
- L97 _public prototype_ `virtual void PopDesignerMessage() override;`
- L101 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;` — FGCObject interface
- L102 _public function_ `virtual FString GetReferencerName() const override`
- L111 _public prototype_ `FOptionalSize GetPreviewAreaWidth() const;` — The width of the preview screen for the UI
- L114 _public prototype_ `FOptionalSize GetPreviewAreaHeight() const;` — The height of the preview screen for the UI
- L117 _public prototype_ `FOptionalSize GetPreviewSizeWidth() const;` — The width of the preview widget for the UI
- L120 _public prototype_ `FOptionalSize GetPreviewSizeHeight() const;` — The height of the preview widget for the UI
- L123 _public prototype_ `float GetPreviewDPIScale() const;` — Gets the DPI scale that would be applied given the current preview width and height
- L126 _public prototype_ `void SetPreviewAreaSize(int32 Width, int32 Height);` — Set the size of the preview screen for the UI
- L128 _public prototype_ `void BeginResizingArea();`
- L129 _public prototype_ `void EndResizingArea();`
- L131 _public prototype_ `const UWidgetEditingProjectSettings* GetRelevantSettings() const;`
- L134 _protected prototype_ `virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;`
- L135 _protected prototype_ `virtual void OnPaintBackground(const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId) const override;`
- L136 _protected prototype_ `void DrawResolution(const FDebugResolution& Resolution, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId) const;`
- L138 _protected prototype_ `virtual FSlateRect ComputeAreaBounds() const override;`
- L139 _protected prototype_ `virtual int32 GetGraphRulePeriod() const override;`
- L140 _protected prototype_ `virtual float GetGridScaleAmount() const override;`
- L141 _protected prototype_ `virtual int32 GetSnapGridSize() const override;`
- L144 _private prototype_ `void RegisterExtensions();`
- L147 _private prototype_ `void SetStartupResolution();` — Establishes the resolution and aspect ratio to use on construction from config settings
- L149 _private prototype_ `FVector2D GetAreaResizeHandlePosition() const;`
- L150 _private prototype_ `EVisibility GetAreaResizeHandleVisibility() const;`
- L152 _private prototype_ `const FSlateBrush* GetPreviewBackground() const;`
- L155 _private prototype_ `void ResolvePendingSelectedWidgets();` — Adds any pending selected widgets to the selection set
- L158 _private prototype_ `void UpdatePreviewWidget(bool bForceUpdate);` — Updates the designer to display the latest preview widget
- L160 _private prototype_ `void BroadcastDesignerChanged();`
- L162 _private prototype_ `void ClearExtensionWidgets();`
- L163 _private prototype_ `void CreateExtensionWidgetsForSelection();`
- L165 _private prototype_ `EVisibility GetInfoBarVisibility() const;`
- L166 _private prototype_ `FText GetInfoBarText() const;`
- L169 _private prototype_ `void ShowContextMenu(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent);` — Displays the context menu when you right click
- L171 _private prototype_ `void OnEditorSelectionChanged();`
- L174 _private prototype_ `void OnHoveredWidgetSet(const FWidgetReference& InHoveredWidget);` — Called when a new widget is being hovered
- L177 _private prototype_ `void OnHoveredWidgetCleared();` — Called when a widget is no longer being hovered
- L180 _private prototype_ `UWidgetBlueprint* GetBlueprint() const;` — Gets the blueprint being edited by the designer
- L183 _private prototype_ `void OnPreviewNeedsRecreation();` — Called whenever the blueprint is recompiled or the preview is updated
- L185 _private prototype_ `void PopulateWidgetGeometryCache(FArrangedWidget& Root);`
- L186 _private prototype_ `void PopulateWidgetGeometryCache_Loop(FArrangedWidget& Parent);`
- L189 _private prototype_ `FText GetResolutionText(int32 Width, int32 Height, const FString& AspectRatio) const;` — @return Formatted text for the given resolution params
- L192 _private prototype_ `FReply NudgeSelectedWidget(FVector2D Nudge);` — Move the selected widget by the nudge amount.
- L194 _private prototype_ `FText GetCurrentResolutionText() const;`
- L195 _private prototype_ `FText GetCurrentDPIScaleText() const;`
- L196 _private prototype_ `FSlateColor GetCurrentDPIScaleColor() const;`
- L197 _private prototype_ `FText GetCurrentScaleFactorText() const;`
- L198 _private prototype_ `FText GetCurrentSafeZoneText() const;`
- L199 _private prototype_ `FSlateColor GetResolutionTextColorAndOpacity() const;`
- L200 _private prototype_ `EVisibility GetResolutionTextVisibility() const;`
- L202 _private prototype_ `TOptional<int32> GetCustomResolutionWidth() const;`
- L203 _private prototype_ `TOptional<int32> GetCustomResolutionHeight() const;`
- L204 _private prototype_ `void OnCustomResolutionWidthChanged(int32 InValue);`
- L205 _private prototype_ `void OnCustomResolutionHeightChanged(int32 InValue);`
- L206 _private prototype_ `EVisibility GetCustomResolutionEntryVisibility() const;`
- L209 _private prototype_ `void HandleOnCommonResolutionSelected(const FPlayScreenResolution InResolution);` — Handles selecting a common screen resolution.
- L210 _private prototype_ `bool HandleIsCommonResolutionSelected(const FPlayScreenResolution InResolution) const;`
- L211 _private prototype_ `FUIAction GetResolutionMenuAction( const FPlayScreenResolution& ScreenResolution );`
- L212 _private prototype_ `TSharedRef<SWidget> GetResolutionsMenu();`
- L214 _private prototype_ `TSharedRef<SWidget> GetScreenSizingFillMenu();`
- L215 _private prototype_ `void CreateScreenFillEntry(FMenuBuilder& MenuBuilder, EDesignPreviewSizeMode SizeMode);`
- L216 _private prototype_ `FText GetScreenSizingFillText() const;`
- L217 _private prototype_ `bool GetIsScreenFillRuleSelected(EDesignPreviewSizeMode SizeMode) const;`
- L218 _private prototype_ `void OnScreenFillRuleSelected(EDesignPreviewSizeMode SizeMode);`
- L220 _private prototype_ `const FSlateBrush* GetAspectRatioSwitchImage() const;`
- L221 _private prototype_ `bool GetAspectRatioSwitchEnabled() const;`
- L222 _private prototype_ `bool GetFlipDeviceEnabled() const;`
- L223 _private prototype_ `EVisibility GetDesignerOutlineVisibility() const;`
- L224 _private prototype_ `FSlateColor GetDesignerOutlineColor() const;`
- L225 _private prototype_ `FText GetDesignerOutlineText() const;`
- L227 _private prototype_ `FText GetCursorPositionText() const;`
- L228 _private prototype_ `EVisibility GetCursorPositionTextVisibility() const;`
- L230 _private prototype_ `FText GetSelectedWidgetDimensionsText() const;`
- L231 _private prototype_ `EVisibility GetSelectedWidgetDimensionsVisibility() const;`
- L234 _private prototype_ `int32 HandleEffectsPainting(const FOnPaintHandlerParams& PaintArgs);` — Handles drawing selection and other effects a SPaintSurface widget injected into the hierarchy.
- L235 _private prototype_ `void DrawSelectionAndHoverOutline(const FOnPaintHandlerParams& PaintArgs);`
- L236 _private prototype_ `void DrawSafeZone(const FOnPaintHandlerParams& PaintArgs);`
- L238 _private prototype_ `FReply HandleDPISettingsClicked();`
- L240 _private prototype_ `UUserWidget* GetDefaultWidget() const;`
- L242 _private prototype_ `void BeginTransaction(const FText& SessionName);`
- L243 _private prototype_ `bool InTransaction() const;`
- L244 _private prototype_ `void EndTransaction(bool bCancel);`
- L246 _private prototype_ `UWidget* GetWidgetInDesignScopeFromSlateWidget(TSharedRef<SWidget>& InWidget);`
- L248 _private prototype_ `EVisibility GetExtensionCanvasVisibility() const;`
- L264 _private prototype_ `bool FindWidgetUnderCursor(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent, TSubclassOf<UWidget> FindType, FWidgetHitResult& HitResult);` — @returns Gets the widget under the cursor based on a mouse pointer event.
- L267 _private prototype_ `FReply HandleZoomToFitClicked();`
- L268 _private prototype_ `FReply HandleSwapAspectRatioClicked();`
- L269 _private prototype_ `FReply HandleFlipSafeZonesClicked();`
- L270 _private prototype_ `EVisibility GetRulerVisibility() const;`
- L273 _private member_ `static const FString ConfigSectionName;`
- L274 _private member_ `static const FString DefaultPreviewOverrideName;`
- L277 _private member_ `TArray< TSharedRef<FDesignerExtension> > DesignerExtensions;` — Extensions for the designer to allow for custom widgets to be inserted onto the design surface as selection changes.
- L280 _private prototype_ `void BindCommands();`
- L282 _private prototype_ `void SetTransformMode(ETransformMode::Type InTransformMode);`
- L283 _private prototype_ `bool CanSetTransformMode(ETransformMode::Type InTransformMode) const;`
- L284 _private prototype_ `bool IsTransformModeActive(ETransformMode::Type InTransformMode) const;`
- L286 _private prototype_ `void ToggleShowingOutlines();`
- L287 _private prototype_ `bool IsShowingOutlines() const;`
- L289 _private prototype_ `void ToggleRespectingLocks();`
- L290 _private prototype_ `bool IsRespectingLocks() const;`
- L292 _private prototype_ `void ProcessDropAndAddWidget(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent, const bool bIsPreview);`
- L293 _private prototype_ `void MoveWidgets(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent, const bool bIsPreview, UWidget* Target, const bool bAnyWidgetChangingParent);`
- L295 _private prototype_ `FVector2D GetExtensionPosition(TSharedRef<FDesignerSurfaceElement> ExtensionElement) const;`
- L297 _private prototype_ `FVector2D GetExtensionSize(TSharedRef<FDesignerSurfaceElement> ExtensionElement) const;`
- L299 _private prototype_ `void ClearDropPreviews();`
- L301 _private prototype_ `void DetermineDragDropPreviewWidgets(TArray<UWidget*>& OutWidgets, const FDragDropEvent& DragDropEvent, UWidgetTree* RootWidgetTree);`
- L303 _private prototype_ `void SwapSafeZoneTypes();`
- L305 _private prototype_ `bool IsSelectableInSequencer(UWidget* const InWidget) const;`
- L307 _private prototype_ `void OnSelectedAnimationChanged();`
- L309 _private prototype_ `void OnSelectionLimitedChanged(const bool bInEnabled);`
- L311 _private prototype_ `void DeselectNonSequencerWidgets();`
- L313 _private prototype_ `void ToggleViewportSelectionLimited();`
- L315 _private prototype_ `bool CanToggleViewportSelectionLimited() const;`
- L317 _private prototype_ `bool IsViewportSelectionLimited() const;`
- L321 _private member_ `TWeakPtr<FWidgetBlueprintEditor> BlueprintEditor;` — A reference to the BP Editor that owns this designer
- L324 _private member_ `TSharedPtr<FUICommandList> CommandList;` — The designer command list
- L327 _private member_ `FScopedTransaction* ScopedTransaction;` — The transaction used to commit undoable actions from resize, move...etc
- L330 _private member_ `TObjectPtr<UUserWidget> PreviewWidget;` — The current preview widget
- L333 _private member_ `TWeakPtr<SWidget> PreviewSlateWidget;` — The current preview widget's slate widget
- L336 _private member_ `FVector2D CachedMousePosition;` — Cache last mouse position to be used as a paste drop location
- L345 _private member_ `TArray<FDropPreview> DropPreviews;`
- L347 _private member_ `TSharedPtr<SWidget> PreviewHitTestRoot;`
- L348 _private member_ `TSharedPtr<SBox> PreviewAreaConstraint;`
- L349 _private member_ `TSharedPtr<SDPIScaler> PreviewSurface;`
- L350 _private member_ `TSharedPtr<SBox> PreviewSizeConstraint;`
- L352 _private member_ `TSharedPtr<SCanvas> DesignerControls;`
- L353 _private member_ `TSharedPtr<SCanvas> DesignerWidgetCanvas;`
- L354 _private member_ `TSharedPtr<SCanvas> ExtensionWidgetCanvas;`
- L355 _private member_ `TSharedPtr<SPaintSurface> EffectsLayer;`
- L358 _private member_ `TSet< FWidgetReference > SelectedWidgetsCache;` — The currently selected preview widgets in the preview GUI, just a cache used to determine changes between selection changes.
- L361 _private member_ `FVector2D SelectedWidgetContextMenuLocation;` — The location in selected widget local space where the context menu was summoned.
- L367 _private member_ `FWidgetReference PendingSelectedWidget;` — Holds onto a temporary widget that the user may be getting ready to select, or may just be the widget that got hit on the initial mouse down before moving the parent.
- L370 _private member_ `FVector2D DraggingStartPositionScreenSpace;` — The position in screen space where the user began dragging a widget
- L373 _private member_ `bool bMovingExistingWidget;` — An existing widget is being moved in its current container, or in to a new container.
- L376 _private member_ `int32 PreviewWidth;` — The configured Width of the preview area, simulates screen size.
- L379 _private member_ `int32 PreviewHeight;` — The configured Height of the preview area, simulates screen size.
- L382 _private member_ `int32 WidthReadFromSettings;` — The original Width of the preview area, read from the settings file.
- L385 _private member_ `int32 HeightReadFromSettings;` — The original Height of the preview area, read from the settings file.
- L388 _private member_ `bool bCommonResolutionSelected;` — Whether we have selected one of the common resolutions for the preview.
- L391 _private member_ `bool bShowResolutionOutlines;` — /
- L394 _private member_ `mutable FSlateBrush BackgroundImage;` — The slate brush we use to hold the background image shown in the designer.
- L397 _private member_ `FVector2D CachedPreviewDesiredSize;` — We cache the desired preview desired size to maintain the same size between compiles when it lags a frame behind and no widget is available.
- L400 _private member_ `FString PreviewAspectRatio;` — Resolution Info
- L403 _private member_ `bool bCanPreviewSwapAspectRatio;` — Whether or not the resolution can flip between portrait and landscape
- L405 _private member_ `FString PreviewOverrideName;`
- L407 _private member_ `float ScaleFactor;`
- L409 _private member_ `bool bSafeZoneFlipped;`
- L412 _private member_ `bool bPreviewIsPortrait;` — Whether the preview is currently in portrait mode
- L415 _private member_ `FCurveSequence ResolutionTextFade;` — Curve to handle fading of the resolution
- L418 _private member_ `FCurveSequence HoveredWidgetOutlineFade;` — Curve to handle the fade-in of the border around the hovered widget
- L421 _private member_ `FWeakWidgetPath SelectedWidgetPath;`
- L424 _private member_ `TSharedPtr<SRuler> TopRuler;` — The ruler bar at the top of the designer.
- L427 _private member_ `TSharedPtr<SRuler> SideRuler;` — The ruler bar on the left side of the designer.
- L430 _private member_ `ETransformMode::Type TransformMode;`
- L433 _private member_ `TMap<TSharedRef<SWidget>, FArrangedWidget> CachedWidgetGeometry;`
- L436 _private member_ `TSharedPtr<FHittestGrid> DesignerHittestGrid;`
- L439 _private member_ `TArray<FText> DesignerMessageStack;` — The message stack to display the last item to the user in a non-modal fashion.
- L441 _private member_ `TArray<FVector2D> CustomSafeZoneStarts;`
- L443 _private member_ `TArray<FVector2D> CustomSafeZoneDimensions;`
- L445 _private member_ `FMargin DesignerSafeZoneOverride;`

#### struct `SDesignerView::FWidgetHitResult`  
`struct FWidgetHitResult`  
_L251-261_
- L254 _public member_ `FWidgetReference Widget;`
- L255 _public member_ `FArrangedWidget WidgetArranged;`
- L257 _public member_ `FName NamedSlot;`
- L260 _public prototype_ `FWidgetHitResult();`

#### struct `SDesignerView::FDropPreview`  
`struct FDropPreview`  
_L338-343_
- L340 _public member_ `TObjectPtr<UWidget> Widget;`
- L341 _public member_ `TObjectPtr<UPanelWidget> Parent;`
- L342 _public member_ `TWeakPtr<FDragDropOperation> DragOperation;`

#### Free symbols / members of external scopes

- L29 _macro_ `#define UE_API UMGEDITOR_API`

### `Source/Editor/UMGEditor/Public/Designer/SZoomPan.h` (Public)


#### class `SZoomPan`  
`class SZoomPan : public SCompoundWidget`  
_L16-47_
- inherits: `SCompoundWidget`
- L19 _public function_ `SLATE_BEGIN_ARGS(SZoomPan)`
- L21 _public prototype_ `SLATE_DEFAULT_SLOT(FArguments, Content) SLATE_ATTRIBUTE(FVector2D, ViewOffset) SLATE_ATTRIBUTE(float, ZoomAmount) SLATE_END_ARGS() void Construct(const FArguments& InArgs);` — Slot for this designers content (optional)
- L35 _public prototype_ `void SetContent( const TSharedRef< SWidget >& InContent );` — Sets the content for this border @param	InContent	The widget to use as content for the border
- L38 _protected prototype_ `void OnArrangeChildren(const FGeometry& AllottedGeometry, FArrangedChildren& ArrangedChildren) const override;`
- L40 _protected prototype_ `virtual float GetRelativeLayoutScale(int32 ChildIndex, float LayoutScaleMultiplier) const override;`
- L43 _protected member_ `TAttribute<FVector2D> ViewOffset;` — The position within the panel at which the user is looking
- L46 _protected member_ `TAttribute<float> ZoomAmount;` — How zoomed in/out we are. e.g. 0.25f results in quarter-sized widgets.

### `Source/Editor/UMGEditor/Public/DesignerExtension.h` (Public)


#### enum `EExtensionLayoutLocation`  
`enum class EExtensionLayoutLocation : uint8`  
_L32-48_
- desc: The location where the widget should appear
- L35 _public enumerator_ `RelativeFromParent` — Slate unit position relative from the parent.
- L37 _public enumerator_ `TopLeft`
- L38 _public enumerator_ `TopCenter`
- L39 _public enumerator_ `TopRight`
- L41 _public enumerator_ `CenterLeft`
- L42 _public enumerator_ `CenterCenter`
- L43 _public enumerator_ `CenterRight`
- L45 _public enumerator_ `BottomLeft`
- L46 _public enumerator_ `BottomCenter`
- L47 _public enumerator_ `BottomRight`

#### class `FDesignerSurfaceElement`  
`class FDesignerSurfaceElement : public TSharedFromThis < FDesignerSurfaceElement >`  
_L55-110_
- inherits: `TSharedFromThis<FDesignerSurfaceElement>`
- desc: The basic element returned for extending the design surface.
- L58 _public function_ `FDesignerSurfaceElement(TSharedRef<SWidget> InWidget, EExtensionLayoutLocation InLocation, TAttribute<FVector2D> InOffset = FVector2D(0, 0), TAttribute<FVector2D> InAlignment = FVector2D(0, 0)) : Widget(InWidget) , Location(InLocation) , Offset(InOffset) , Alignment(InAlignment)`
- L67 _public function_ `TSharedRef<SWidget> GetWidget() const` — Gets the widget that will be laid out in the design surface for extending the capability of the selected widget
- L73 _public function_ `EExtensionLayoutLocation GetLocation() const` — Gets the location where the widget will appear
- L79 _public function_ `void SetOffset(TAttribute<FVector2D> InOffset)` — Sets the offset after laid out in that location
- L85 _public function_ `FVector2D GetOffset() const` — Gets the offset after being laid out.
- L91 _public function_ `void SetAlignment(TAttribute<FVector2D> InAlignment)` — Sets the alignment to use, a normalized value representing position inside the parent.
- L97 _public function_ `FVector2D GetAlignment() const` — Gets the alignment to use, a normalized value representing position inside the parent.
- L103 _protected member_ `TSharedRef<SWidget> Widget;`
- L105 _protected member_ `EExtensionLayoutLocation Location;`
- L107 _protected member_ `TAttribute<FVector2D> Offset;`
- L109 _protected member_ `TAttribute<FVector2D> Alignment;`

#### class `FDesignerExtension`  
`class FDesignerExtension : public TSharedFromThis<FDesignerExtension>`  
_L116-182_
- inherits: `TSharedFromThis<FDesignerExtension>`
- desc: The Designer extension allows developers to provide additional widgets and custom painting to the designer surface for specific widgets.  Allowing for a more customized and specific editors for the different widgets.
- L120 _public prototype_ `FDesignerExtension();` — Constructor
- L121 _public prototype_ `virtual ~FDesignerExtension();`
- L124 _public prototype_ `virtual void Initialize(IUMGDesigner* InDesigner, UWidgetBlueprint* InBlueprint);` — Initializes the designer extension, this is called the first time a designer extension is registered
- L127 _public prototype_ `virtual void Uninitialize();` — Uninitializes the designer extension, this is called when the designer is removed.
- L130 _public function_ `virtual bool CanExtendSelection(const TArray< FWidgetReference >& Selection) const` — Returns true if the designer extension can extend the current selection.
- L136 _public function_ `virtual void ExtendSelection(const TArray< FWidgetReference >& Selection, TArray< TSharedRef<FDesignerSurfaceElement> >& SurfaceElements)` — Called every time a element the designer can extend is selected.
- L141 _public function_ `virtual void PreviewContentCreated(UUserWidget* PreviewWidget)` — Called every time the designer creates new preview.
- L146 _public function_ `virtual void PreviewContentChanged(TSharedRef<SWidget> NewContent)` — Called every time the content of the designer changed.
- L151 _public function_ `virtual void Tick( const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime )` — Called each frames to tick the extension.
- L156 _public function_ `virtual void Paint(const TSet< FWidgetReference >& Selection, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId) const` — Called to paint the extension.
- L161 _public prototype_ `FName GetExtensionId() const;` — Gets the ID identifying this extension.
- L163 _public function_ `bool operator==(const FDesignerExtension& Other) const`
- L169 _protected prototype_ `void BeginTransaction(const FText& SessionName);`
- L171 _protected prototype_ `void EndTransaction();`
- L174 _protected member_ `FName ExtensionId;`
- L175 _protected member_ `TWeakObjectPtr<UWidgetBlueprint> Blueprint;`
- L176 _protected member_ `IUMGDesigner* Designer;`
- L178 _protected member_ `TArray< FWidgetReference > SelectionCache;`
- L181 _private member_ `FScopedTransaction* ScopedTransaction;`

#### Free symbols / members of external scopes

- L17 _macro_ `#define UE_API UMGEDITOR_API`

### `Source/Editor/UMGEditor/Public/Details/WidgetPropertyDragDropOp.h` (Public)


#### class `FWidgetPropertyDragDropOp`  
`class FWidgetPropertyDragDropOp : public FDecoratedDragDropOp`  
_L16-29_
- inherits: `FDecoratedDragDropOp`
- desc: Drag-and-drop operation that stores data about the a widget property being dragged on.
- L19 _public prototype_ `DRAG_DROP_OPERATOR_TYPE(FWidgetPropertyDragDropOp, FDecoratedDragDropOp);`
- L21 _public prototype_ `FWidgetPropertyDragDropOp();`
- L22 _public prototype_ `virtual void OnDrop(bool bDropWasHandled, const FPointerEvent& MouseEvent) override;`
- L23 _public prototype_ `static TSharedRef<FWidgetPropertyDragDropOp> New(UWidget* InOwnerWidget, FName InPropertyName, TArray<FFieldVariant> InPropertyPath, UWidgetBlueprint* InWidgetBP);`
- L25 _public member_ `TWeakObjectPtr<UWidget> OwnerWidget;`
- L26 _public member_ `TArray<FFieldVariant> DraggedPropertyPath;`
- L27 _public member_ `TWeakObjectPtr<UWidgetBlueprint> WidgetBP;`
- L28 _public member_ `TUniquePtr<FScopedTransaction> Transaction;`

#### Free symbols / members of external scopes

- L14 _macro_ `#define LOCTEXT_NAMESPACE "WidgetPropertyDragDropOp"`

### `Source/Editor/UMGEditor/Public/DragDrop/WidgetTemplateDragDropOp.h` (Public)


#### class `FWidgetTemplateDragDropOp`  
`class FWidgetTemplateDragDropOp : public FDecoratedDragDropOp`  
_L19-29_
- inherits: `FDecoratedDragDropOp`
- desc: This drag drop operation allows widget templates from the palate to be dragged and dropped into the designer or the widget hierarchy in order to spawn new widgets.
- L22 _public prototype_ `DRAG_DROP_OPERATOR_TYPE(FWidgetTemplateDragDropOp, FDecoratedDragDropOp) TSharedPtr<FWidgetTemplate> Template;`
- L28 _public prototype_ `static TSharedRef<FWidgetTemplateDragDropOp> New(const TSharedPtr<FWidgetTemplate>& InTemplate);` — Constructs the drag drop operation

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API UMGEDITOR_API`

### `Source/Editor/UMGEditor/Public/FieldNotification/CustomizationHelper.h` (Public)


#### class `UE::FieldNotification::FCustomizationHelper`  
`class FCustomizationHelper`  
_L21-50_
- L24 _public member_ `static const FName MetaData_FieldNotify;`
- L26 _public function_ `FCustomizationHelper(UWidgetBlueprint* InBlueprint) : Blueprint(InBlueprint)`
- L30 _public prototype_ `void CustomizeVariableDetails(IDetailLayoutBuilder& DetailLayout);`
- L31 _public prototype_ `void CustomizeFunctionDetails(IDetailLayoutBuilder& DetailLayout);`
- L34 _private prototype_ `ECheckBoxState IsPropertyFieldNotifyChecked() const;`
- L35 _private prototype_ `void HandlePropertyFieldNotifyCheckStateChanged(ECheckBoxState CheckBoxState);`
- L36 _private prototype_ `ECheckBoxState IsFunctionFieldNotifyChecked() const;`
- L37 _private prototype_ `void HandleFunctionFieldNotifyCheckStateChanged(ECheckBoxState CheckBoxState);`
- L39 _private prototype_ `UK2Node_FunctionEntry* FindFunctionEntry(UObject* Obj) const;`
- L43 _private member_ `TWeakObjectPtr<UWidgetBlueprint> Blueprint;` — The blueprint we are editing
- L46 _private member_ `TArray<TWeakFieldPtr<FProperty>> PropertiesBeingCustomized;` — The property we are editing
- L49 _private member_ `TArray<TWeakObjectPtr<UK2Node_FunctionEntry>> FunctionsBeingCustomized;` — The function we are editing

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API UMGEDITOR_API`
- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace FieldNotification` (scope `UE`)

### `Source/Editor/UMGEditor/Public/Hierarchy/HierarchyWidgetDragDropOp.h` (Public)


#### class `FHierarchyWidgetDragDropOp`  
`class FHierarchyWidgetDragDropOp : public FDecoratedDragDropOp`  
_L15-29_
- inherits: `FDecoratedDragDropOp`
- desc: This drag drop operation allows widgets from the hierarchy rows to be dragged and dropped around the editor.
- L18 _public prototype_ `DRAG_DROP_OPERATOR_TYPE(FHierarchyWidgetDragDropOp, FDecoratedDragDropOp) bool HasOriginatedFrom(const TSharedPtr<FWidgetBlueprintEditor>& BlueprintEditor) const;`
- L22 _public prototype_ `const TArrayView<const FWidgetReference> GetWidgetReferences() const;`
- L25 _public prototype_ `static TSharedRef<FHierarchyWidgetDragDropOp> New(UWidgetBlueprint* Blueprint, const TArray<FWidgetReference>& InWidgets);` — Constructs a new drag/drop operation
- L28 _private member_ `TArray<FWidgetReference> WidgetReferences;`

### `Source/Editor/UMGEditor/Public/Hierarchy/IHierarchyViewItem.h` (Public)


#### class `IHierarchyModel`  
`class IHierarchyModel`  
_L7-16_
- L10 _public prototype_ `virtual ~IHierarchyModel() = default;`
- L11 _public prototype_ `virtual bool IsHovered() const = 0;`
- L12 _public prototype_ `virtual bool IsVisible() const = 0;`
- L13 _public prototype_ `virtual bool CanControlVisibility() const = 0;`
- L14 _public prototype_ `virtual bool CanControlLockedInDesigner() const = 0;`
- L15 _public prototype_ `virtual bool IsLockedInDesigner() const = 0;`

#### class `IHierarchyViewItem`  
`template <typename HierarchyModel> class IHierarchyViewItem : public STableRow< TSharedPtr<HierarchyModel> >`  
_L19-26_
- inherits: `STableRow<TSharedPtr<HierarchyModel>>`
- L22 _public prototype_ `virtual ~IHierarchyViewItem() = default;`
- L23 _public prototype_ `virtual FReply HandleDragDetected(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) = 0;`
- L24 _public prototype_ `virtual void ToggleLockedInDesigner(const bool bRecursive) = 0;`
- L25 _public prototype_ `virtual bool ShouldAppearHovered() const = 0;`

### `Source/Editor/UMGEditor/Public/Hierarchy/SReadOnlyHierarchyView.h` (Public)


#### enum `ERootSelectionMode`  
`enum class ERootSelectionMode : uint8`  
_L26-36_
- reflection: `UENUM()`
- L29 _public enumerator_ `Disabled` — The Root Widget is not selectable
- L32 _public enumerator_ `Enabled` — The Root Widget is selectable and will show it's name as the display text
- L35 _public enumerator_ `Self` — The Root Widget is selectable and it will show Self as the display text

#### enum `EInheritedNamedSlotSelectionMode`  
`enum class EInheritedNamedSlotSelectionMode : uint8`  
_L39-46_
- reflection: `UENUM()`
- L42 _public enumerator_ `Disabled` — Inherited Named slots are not selectable
- L45 _public enumerator_ `Enabled` — Inherited Named slots are selectable

#### class `SReadOnlyHierarchyView`  
`class SReadOnlyHierarchyView : public SCompoundWidget`  
_L48-134_
- inherits: `SCompoundWidget`
- L67 _public typedef_ `using FOnSelectionChanged = typename TSlateDelegates<FName>::FOnSelectionChanged;`
- L69 _public function_ `SLATE_BEGIN_ARGS(SReadOnlyHierarchyView)`
- L70 _public prototype_ `SLATE_ARGUMENT_DEFAULT(bool, ShowSearch) = true;`
- L71 _public prototype_ `SLATE_ARGUMENT_DEFAULT(ERootSelectionMode, RootSelectionMode) = ERootSelectionMode::Enabled;`
- L72 _public prototype_ `SLATE_ARGUMENT_DEFAULT(EInheritedNamedSlotSelectionMode, InheritedNamedSlotSelectionMode) = EInheritedNamedSlotSelectionMode::Enabled;`
- L73 _public prototype_ `SLATE_ARGUMENT_DEFAULT(ESelectionMode::Type, SelectionMode) = ESelectionMode::Single;`
- L74 _public prototype_ `SLATE_EVENT(FOnSelectionChanged, OnSelectionChanged) SLATE_ARGUMENT(TArray<FName>, ShowOnly) SLATE_ARGUMENT_DEFAULT(bool, ExpandAll) = true;`
- L79 _public prototype_ `virtual ~SReadOnlyHierarchyView();`
- L81 _public prototype_ `void Construct(const FArguments& InArgs, const UWidgetBlueprint* WidgetBlueprint);`
- L82 _public prototype_ `void Refresh();`
- L84 _public prototype_ `void SetSelectedWidget(FName WidgetName);`
- L85 _public prototype_ `void SetRawFilterText(const FText& Text);`
- L87 _public prototype_ `TArray<FName> GetSelectedWidgets() const;`
- L88 _public prototype_ `void ClearSelection();`
- L92 _private prototype_ `TSharedRef<ITableRow> GenerateRow(TSharedPtr<FItem> Item, const TSharedRef<STableViewBase>& OwnerTable) const;`
- L94 _private prototype_ `void GetItemChildren(TSharedPtr<FItem> Item, TArray<TSharedPtr<FItem>>& OutChildren) const;`
- L95 _private prototype_ `FText GetItemText(TSharedPtr<FItem> Item) const;`
- L96 _private prototype_ `const FSlateBrush* GetIconBrush(TSharedPtr<FItem> Item) const;`
- L97 _private prototype_ `FText GetIconToolTipText(TSharedPtr<FItem> Item) const;`
- L98 _private prototype_ `FText GetWidgetToolTipText(TSharedPtr<FItem> Item) const;`
- L99 _private prototype_ `void GetFilterStringsForItem(TSharedPtr<FItem> Item, TArray<FString>& OutStrings) const;`
- L100 _private prototype_ `TSharedPtr<FItem> FindItem(const TArray<TSharedPtr<FItem>>& RootItems, FName Name) const;`
- L101 _private prototype_ `void OnSelectionChanged(TSharedPtr<FItem> Selected, ESelectInfo::Type SelectionType);`
- L103 _private prototype_ `void RebuildTree();`
- L104 _private prototype_ `void BuildWidgetChildren(const UWidget* Widget, TSharedPtr<FItem> Parent);`
- L106 _private prototype_ `void SetItemExpansionRecursive(TSharedPtr<FItem> Item, bool bShouldBeExpanded);`
- L107 _private prototype_ `void ExpandAll();`
- L109 _private prototype_ `FName GetItemName(const TSharedPtr<FItem>& Item) const;`
- L113 _private member_ `TWeakObjectPtr<const UWidgetBlueprint> WidgetBlueprint;`
- L114 _private member_ `TArray<FName> ShowOnly;`
- L116 _private member_ `TArray<TSharedPtr<FItem>> RootWidgets;`
- L117 _private member_ `TArray<TSharedPtr<FItem>> FilteredRootWidgets;`
- L119 _private member_ `ERootSelectionMode RootSelectionMode;`
- L120 _private member_ `EInheritedNamedSlotSelectionMode InheritedNamedSlotSelectionMode;`
- L122 _private member_ `FOnSelectionChanged OnSelectionChangedDelegate;`
- L124 _private member_ `TSharedPtr<SSearchBox> SearchBox;`
- L126 _private typedef_ `using FTextFilter = TTextFilter<TSharedPtr<FItem>>;`
- L127 _private member_ `TSharedPtr<FTextFilter> SearchFilter;`
- L128 _private typedef_ `using FTreeFilterHandler = TreeFilterHandler<TSharedPtr<FItem>>;`
- L129 _private member_ `TSharedPtr<FTreeFilterHandler> FilterHandler;`
- L131 _private member_ `TSharedPtr<STreeView<TSharedPtr<FItem>>> TreeView;`
- L133 _private member_ `bool bExpandAll;`

#### struct `SReadOnlyHierarchyView::FItem`  
`struct FItem`  
_L52-63_
- L54 _public function_ `FItem(const UWidget* InWidget) : Widget(InWidget)`
- L55 _public function_ `FItem(const UWidgetBlueprint* InWidgetBlueprint) : WidgetBlueprint(InWidgetBlueprint)`
- L56 _public function_ `FItem(const FName InInheritedNamedSlotName) : InheritedNamedSlotName(InInheritedNamedSlotName)`
- L58 _public member_ `TWeakObjectPtr<const UWidget> Widget;`
- L59 _public member_ `TWeakObjectPtr<const UWidgetBlueprint> WidgetBlueprint;`
- L60 _public member_ `const FName InheritedNamedSlotName;`
- L62 _public member_ `TArray<TSharedPtr<FItem>> Children;`

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API UMGEDITOR_API`

### `Source/Editor/UMGEditor/Public/IHasClipboardExtensibility.h` (Public)


#### class `IClipboardExtension`  
`class IClipboardExtension`  
_L15-38_
- L30 _public prototype_ `virtual void AppendToClipboard(const UWidget* Widget, const FExportArgs& ExportArgs) = 0;`
- L31 _public prototype_ `virtual bool CanAppendToClipboard(const UWidget* Widget) const = 0;`
- L32 _public prototype_ `virtual void ProcessImportedText(const UWidgetBlueprint* WidgetBlueprint, const FString& TextToImport, UPackage*& TempPackage) = 0;`
- L33 _public prototype_ `virtual bool CanImportFromClipboard(const UWidget* Widget) const = 0;`
- L34 _public prototype_ `virtual void ImportDataToWidget(const UWidget* Widget, FName OldWidgetName) = 0;`
- L35 _public prototype_ `virtual bool CanWidgetAcceptPaste(const UWidget* Widget) const = 0;`
- L37 _public prototype_ `virtual ~IClipboardExtension() = default;`

#### struct `IClipboardExtension::FExportArgs`  
`struct FExportArgs`  
_L18-28_
- L20 _public member_ `const FExportObjectInnerContext* Context = nullptr;`
- L21 _public member_ `UExporter* Exporter = nullptr;`
- L22 _public member_ `FOutputDevice* Out = nullptr;`
- L23 _public member_ `const TCHAR* FileType = nullptr;`
- L24 _public member_ `int32 Indent = 0;`
- L25 _public member_ `uint32 PortFlags = PPF_None;`
- L26 _public member_ `bool bSelectedOnly = false;`
- L27 _public member_ `UObject* ExportRootScope = nullptr;`

#### class `FClipboardExtensibilityManager`  
`class FClipboardExtensibilityManager`  
_L43-67_
- desc: Clipboard extensibility manager holds a list of registered clipboard extensions.
- L46 _public function_ `void AddExtension(const TSharedRef<IClipboardExtension>& Extension)`
- L54 _public function_ `void RemoveExtension(const TSharedRef<IClipboardExtension>& Extension)`
- L60 _public function_ `const TArrayView<const TSharedPtr<IClipboardExtension>> GetExtensions() const`
- L66 _private member_ `TArray<TSharedPtr<IClipboardExtension>> Extensions;`

#### class `IHasClipboardExtensibility`  
`class IHasClipboardExtensibility`  
_L70-74_
- desc: Indicates that a class has data to append to clipboard
- L73 _public prototype_ `virtual TSharedPtr<FClipboardExtensibilityManager> GetClipboardExtensibilityManager() = 0;`

### `Source/Editor/UMGEditor/Public/IHasDesignerExtensibility.h` (Public)


#### class `IDesignerExtensionFactory`  
`class IDesignerExtensionFactory`  
_L11-16_
- desc: Factory that creates a unique DesignerExtension when a UMG designer is created.
- L14 _public prototype_ `virtual ~IDesignerExtensionFactory() = default;`
- L15 _public prototype_ `virtual TSharedRef<FDesignerExtension> CreateDesignerExtension() const = 0;`

#### class `IHasDesignerExtensibility`  
`class IHasDesignerExtensibility`  
_L21-26_
- desc: Indicates that a class has a designer that is extensible
- L24 _public prototype_ `virtual ~IHasDesignerExtensibility() = default;`
- L25 _public prototype_ `virtual TSharedPtr<FDesignerExtensibilityManager> GetDesignerExtensibilityManager() = 0;`

#### class `FDesignerExtensibilityManager`  
`class FDesignerExtensibilityManager`  
_L31-70_
- desc: Designer Extensibility Manager keep a series of Designer Extensions. See FDesignerExtension class for more information.
- L35 _public function_ `void AddDesignerExtension(const TSharedRef<FDesignerExtension>& Extension)` — `UE_DEPRECATED(4.26, "AddDesignerExtension is deprecated, use the IDesignerExtensibilityFactory instead.")`
- L41 _public function_ `void RemoveDesignerExtension(const TSharedRef<FDesignerExtension>& Extension)` — `UE_DEPRECATED(4.26, "RemoveDesignerExtension is deprecated, use the IDesignerExtensibilityFactory instead.")`
- L47 _public function_ `const TArray<TSharedRef<FDesignerExtension>>& GetExternalDesignerExtensions() const` — `UE_DEPRECATED(4.26, "RemoveDesignerExtension is deprecated, use the IDesignerExtensibilityFactory instead.")`
- L52 _public function_ `void AddDesignerExtensionFactory(const TSharedRef<IDesignerExtensionFactory>& Extension)`
- L57 _public function_ `void RemoveDesignerExtensionFactory(const TSharedRef<IDesignerExtensionFactory>& Extension)`
- L62 _public function_ `const TArray<TSharedRef<IDesignerExtensionFactory>>& GetExternalDesignerExtensionFactories() const`
- L68 _private member_ `TArray<TSharedRef<FDesignerExtension>> ExternalExtensions;`
- L69 _private member_ `TArray<TSharedRef<IDesignerExtensionFactory>> ExternalExtensionFactories;`

### `Source/Editor/UMGEditor/Public/IHasPropertyBindingExtensibility.h` (Public)


#### class `IPropertyBindingExtension`  
`class IPropertyBindingExtension`  
_L18-51_
- L29 _public prototype_ `virtual bool CanExtend(const UWidgetBlueprint* WidgetBlueprint, const UWidget* Widget, TSharedPtr<const IPropertyHandle> PropertyHandle) const = 0;` — Does this extension want to extend this property in the widget?
- L30 _public prototype_ `virtual TSharedPtr<FExtender> CreateMenuExtender(const UWidgetBlueprint* WidgetBlueprint, UWidget* Widget, TSharedPtr<IPropertyHandle> PropertyHandle) = 0;`
- L31 _public prototype_ `virtual void ClearCurrentValue(const UWidgetBlueprint* WidgetBlueprint, const UWidget* Widget, TSharedPtr<IPropertyHandle> PropertyHandle) = 0;`
- L32 _public prototype_ `virtual TOptional<FName> GetCurrentValue(const UWidgetBlueprint* WidgetBlueprint, const UWidget* Widget, TSharedPtr<IPropertyHandle> PropertyHandle) const = 0;`
- L33 _public prototype_ `virtual const FSlateBrush* GetCurrentIcon(const UWidgetBlueprint* WidgetBlueprint, const UWidget* Widget, TSharedPtr<IPropertyHandle> PropertyHandle) const = 0;`
- L34 _public prototype_ `virtual TOptional<FLinearColor> GetCurrentIconColor(const UWidgetBlueprint* WidgetBlueprint, const UWidget* Widget, TSharedPtr<IPropertyHandle> PropertyHandle) const = 0;`
- L35 _public prototype_ `virtual EDropResult OnDrop(const FGeometry& Geometry, const FDragDropEvent& DragDropEvent, UWidgetBlueprint* WidgetBlueprint, UWidget* Widget, TSharedPtr<IPropertyHandle> PropertyHandle) = 0;`
- L36 _public function_ `virtual TSharedRef<SWidget> OnGenerateMenu(const UWidgetBlueprint* WidgetBlueprint, UWidget* Widget, TSharedPtr<IPropertyHandle> PropertyHandle, TWeakPtr<IDetailsView> DetailsView)`
- L37 _public function_ `virtual bool ShouldAllowEditingValue(const UWidgetBlueprint* WidgetBlueprint, const UWidget* Widget, TSharedPtr<IPropertyHandle> PropertyHandle) const`
- L40 _public function_ `virtual TSharedPtr<FExtender> CreateMenuExtender(const UWidgetBlueprint* WidgetBlueprint, const UWidget* Widget, const FProperty* Property)` — `UE_DEPRECATED(5.3, "The function CreateMenuExtender with FProperty parameter is deprecated. Please pass the property handler as the parameter instead.")`
- L42 _public function_ `virtual bool CanExtend(const UWidgetBlueprint* WidgetBlueprint, const UWidget* Widget, const FProperty* Property) const` — `UE_DEPRECATED(5.6, "The function CanExtend with FProperty parameter is deprecated. Please pass the property handler as the parameter instead.")`
- L44 _public function_ `virtual void ClearCurrentValue(const UWidgetBlueprint* WidgetBlueprint, const UWidget* Widget, const FProperty* Property)` — `UE_DEPRECATED(5.6, "The function ClearCurrentValue with FProperty parameter is deprecated. Please pass the property handler as the parameter instead.")`
- L46 _public function_ `virtual TOptional<FName> GetCurrentValue(const UWidgetBlueprint* WidgetBlueprint, const UWidget* Widget, const FProperty* Property) const` — `UE_DEPRECATED(5.6, "The function GetCurrentValue with FProperty parameter is deprecated. Please pass the property handler as the parameter instead.")`
- L48 _public function_ `virtual const FSlateBrush* GetCurrentIcon(const UWidgetBlueprint* WidgetBlueprint, const UWidget* Widget, const FProperty* Property) const` — `UE_DEPRECATED(5.6, "The function GetCurrentIcon with FProperty parameter is deprecated. Please pass the property handler as the parameter instead.")`
- L50 _public function_ `virtual TOptional<FLinearColor> GetCurrentIconColor(const UWidgetBlueprint* WidgetBlueprint, const UWidget* Widget, const FProperty* Property) const` — `UE_DEPRECATED(5.6, "The function GetCurrentIconColor with FProperty parameter is deprecated. Please pass the property handler as the parameter instead.")`

#### enum `IPropertyBindingExtension::EDropResult`  
`enum class EDropResult`  
_L21-26_
- L23 _public enumerator_ `HandledContinue` — The drop event was handled by the OnDrop call and it can still be re-used for OnDrop calls in other extensions.
- L24 _public enumerator_ `HandledBreak` — The drop event was handled by the OnDrop call but it is not reusable for OnDrop calls in other extensions (e.g. it was modified).
- L25 _public enumerator_ `Unhandled` — The drop event was not handled by this extension.

#### class `FPropertyBindingExtensibilityManager`  
`class FPropertyBindingExtensibilityManager`  
_L56-76_
- desc: Bindings menu extensibility manager holds a list of registered bindings menu extensions.
- L59 _public function_ `void AddExtension(const TSharedRef<IPropertyBindingExtension>& Extension)`
- L64 _public function_ `void RemoveExtension(const TSharedRef<IPropertyBindingExtension>& Extension)`
- L69 _public function_ `const TArray<TSharedPtr<IPropertyBindingExtension>>& GetExtensions() const`
- L75 _private member_ `TArray<TSharedPtr<IPropertyBindingExtension>> Extensions;`

#### class `IHasPropertyBindingExtensibility`  
`class IHasPropertyBindingExtensibility`  
_L79-83_
- desc: Indicates that a class has a bindings menu that is extensible
- L82 _public prototype_ `virtual TSharedPtr<FPropertyBindingExtensibilityManager> GetPropertyBindingExtensibilityManager() = 0;`

### `Source/Editor/UMGEditor/Public/IHasWidgetContextMenuExtensibility.h` (Public)


#### class `IWidgetContextMenuExtension`  
`class IWidgetContextMenuExtension`  
_L10-16_
- L13 _public prototype_ `virtual ~IWidgetContextMenuExtension() = default;`
- L15 _public prototype_ `virtual void ExtendContextMenu(FMenuBuilder& MenuBuilder, TSharedRef<FWidgetBlueprintEditor> BlueprintEditor, FVector2D TargetLocation) const = 0;`

#### class `FWidgetContextMenuExtensibilityManager`  
`class FWidgetContextMenuExtensibilityManager`  
_L21-45_
- desc: Widget Context Menu extensibility manager holds a list of registered widget context menu extensions.
- L24 _public function_ `void AddExtension(const TSharedRef<IWidgetContextMenuExtension>& Extension)`
- L32 _public function_ `void RemoveExtension(const TSharedRef<IWidgetContextMenuExtension>& Extension)`
- L38 _public function_ `TArrayView<const TSharedPtr<IWidgetContextMenuExtension>> GetExtensions() const`
- L44 _private member_ `TArray<TSharedPtr<IWidgetContextMenuExtension>> Extensions;`

#### class `IHasWidgetContextMenuExtensibility`  
`class IHasWidgetContextMenuExtensibility`  
_L48-52_
- desc: Indicates that a class can extend drag & drop functionality
- L51 _public prototype_ `virtual TSharedPtr<FWidgetContextMenuExtensibilityManager> GetWidgetContextMenuExtensibilityManager() = 0;`

### `Source/Editor/UMGEditor/Public/IHasWidgetDragDropExtensibility.h` (Public)


#### class `IWidgetDragDropExtension`  
`class IWidgetDragDropExtension`  
_L10-17_
- L13 _public prototype_ `virtual ~IWidgetDragDropExtension() = default;`
- L15 _public prototype_ `virtual bool ShouldPreventDropOnTarget(const UWidget* Target, const TSharedPtr<FDragDropOperation>& DragDropOp) const = 0;`
- L16 _public prototype_ `virtual FText GetDropFailureText(const UWidget* Target, const TSharedPtr<FDragDropOperation>& DragDropOp) const = 0;`

#### class `FWidgetDragDropExtensibilityManager`  
`class FWidgetDragDropExtensibilityManager`  
_L22-46_
- desc: Drag & drop extensibility manager holds a list of registered drag and drop extensions.
- L25 _public function_ `void AddExtension(const TSharedRef<IWidgetDragDropExtension>& Extension)`
- L33 _public function_ `void RemoveExtension(const TSharedRef<IWidgetDragDropExtension>& Extension)`
- L39 _public function_ `TArrayView<const TSharedPtr<IWidgetDragDropExtension>> GetExtensions() const`
- L45 _private member_ `TArray<TSharedPtr<IWidgetDragDropExtension>> Extensions;`

#### class `IHasWidgetDragDropExtensibility`  
`class IHasWidgetDragDropExtensibility`  
_L49-53_
- desc: Indicates that a class can extend drag & drop functionality
- L52 _public prototype_ `virtual TSharedPtr<FWidgetDragDropExtensibilityManager> GetWidgetDragDropExtensibilityManager() = 0;`

### `Source/Editor/UMGEditor/Public/IUMGDesigner.h` (Public)


#### enum `ETransformMode::Type`  
`enum Type`  
_L14-20_
- L17 _public enumerator_ `Layout` — Allows parent transfers
- L19 _public enumerator_ `Render` — Only effects the rendered appearance of the widget

#### class `IUMGDesigner`  
`class IUMGDesigner`  
_L27-79_
- desc: The public interface implemented by the UMG Designer to allow extensions to call methods on the designer.
- L31 _public prototype_ `virtual float GetPreviewScale() const = 0;` — @return the effective preview scale after both the DPI and Zoom scale has been applied.
- L34 _public prototype_ `virtual const TSet<FWidgetReference>& GetSelectedWidgets() const = 0;` — @return The currently selected widgets
- L37 _public prototype_ `virtual FWidgetReference GetSelectedWidget() const = 0;` — @return The currently selected widget.
- L40 _public prototype_ `virtual ETransformMode::Type GetTransformMode() const = 0;` — @return Get the transform mode currently in use in the designer.
- L43 _public prototype_ `virtual FGeometry GetDesignerGeometry() const = 0;` — @return The Geometry representing the designer area, useful for when you need to convert mouse into designer space.
- L48 _public prototype_ `virtual bool GetWidgetGeometry(const FWidgetReference& Widget, FGeometry& Geometry) const = 0;` — Gets the previous frames widget geometry.
- L53 _public prototype_ `virtual bool GetWidgetGeometry(const UWidget* PreviewWidget, FGeometry& Geometry) const = 0;` — Gets the previous frames widget geometry.
- L58 _public prototype_ `virtual FGeometry MakeGeometryWindowLocal(const FGeometry& WidgetGeometry) const = 0;` — Takes geometry and adds the inverse of the window transform to get the geometry in the space of the window.
- L63 _public prototype_ `virtual bool GetWidgetParentGeometry(const FWidgetReference& Widget, FGeometry& Geometry) const = 0;` — Gets the previous frames widget geometry of the parent of the provided widget.
- L68 _public prototype_ `virtual void MarkDesignModifed(bool bRequiresRecompile) = 0;` — Marks the designer content as being modified.
- L73 _public prototype_ `virtual void PushDesignerMessage(const FText& Message) = 0;` — Push a new designer message to show at the bottom of the screen.  Don't forget to call PopDesignerMessage when complete.
- L78 _public prototype_ `virtual void PopDesignerMessage() = 0;` — Removes the last message from the message stack.

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace ETransformMode`

### `Source/Editor/UMGEditor/Public/Preview/PreviewMode.h` (Public)


#### class `UE::UMG::Editor::FPreviewMode`  
`class FPreviewMode`  
_L16-45_
- L19 _public prototype_ `void SetSelectedObject(TArray<TWeakObjectPtr<UObject>> Objects);`
- L20 _public prototype_ `void SetSelectedObject(TArrayView<UObject*> Objects);`
- L21 _public prototype_ `TArray<UObject*> GetSelectedObjectList() const;`
- L23 _public function_ `FSimpleMulticastDelegate& OnSelectedObjectChanged()`
- L28 _public prototype_ `void SetPreviewWidget(UUserWidget* Widget);`
- L30 _public function_ `UUserWidget* GetPreviewWidget() const`
- L35 _public function_ `FSimpleMulticastDelegate& OnPreviewWidgetChanged()`
- L41 _private member_ `TArray<TWeakObjectPtr<UObject>> SelectedObjects;`
- L42 _private member_ `TWeakObjectPtr<UUserWidget> PreviewWidget;`
- L43 _private member_ `FSimpleMulticastDelegate SelectedObjectChangedDelegate;`
- L44 _private member_ `FSimpleMulticastDelegate PreviewWidgetChangedDelegate;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API UMGEDITOR_API`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace UMG` (scope `UE`)
- L13 _namespace_ `namespace Editor` (scope `UE::UMG`)

### `Source/Editor/UMGEditor/Public/Settings/WidgetDesignerSettings.h` (Public)


#### enum `EDisplayOnCompile`  
`enum EDisplayOnCompile : int`  
_L24-30_
- reflection: `UENUM()`
- L26 _public enumerator_ `DoC_ErrorsOrWarnings`
- L27 _public enumerator_ `DoC_ErrorsOnly`
- L28 _public enumerator_ `DoC_WarningsOnly`
- L29 _public enumerator_ `DoC_Never`

#### class `UWidgetDesignerSettings`  
`class UWidgetDesignerSettings : public UDeveloperSettings`  
_L36-104_
- reflection: `UCLASS(MinimalAPI, config=EditorPerProjectUserSettings)`
- inherits: `UDeveloperSettings`
- desc: Implements the settings for the Widget Blueprint Designer.
- L41 _public prototype_ `UWidgetDesignerSettings();`
- L44 _public prototype_ `virtual FText GetSectionText() const override;`
- L45 _public prototype_ `virtual FText GetSectionDescription() const override;`
- L52 _public member_ `uint32 GridSnapEnabled:1;` — `UPROPERTY(EditAnywhere, config, Category = GridSnapping, meta = (DisplayName = "Enable Grid Snapping"))` — If enabled, actor positions will snap to the grid.
- L58 _public member_ `int32 GridSnapSize;` — `UPROPERTY(config)`
- L64 _public member_ `bool bLockToPanelOnDragByDefault;` — `UPROPERTY(EditAnywhere, config, Category = Dragging)`
- L68 _public member_ `FUintVector2 DefaultPreviewResolution;` — `UPROPERTY(EditAnywhere, config, Category = Visuals)` — The default preview resolution in the designer.
- L74 _public member_ `bool bShowOutlines;` — `UPROPERTY(EditAnywhere, config, Category = Visuals, meta = ( DisplayName = "Show Dashed Outlines By Default" ))` — Should the designer show outlines by default?
- L81 _public member_ `bool bExecutePreConstructEvent;` — `UPROPERTY(EditAnywhere, config, Category = Visuals)` — Should the designer run the design event?  Disable this if you're seeing crashes in the designer, you may have some unsafe code running in the designer.
- L88 _public member_ `bool bRespectLocks;` — `UPROPERTY(EditAnywhere, config, Category = Interaction)` — Should the designer respect locked widgets?  If true, the designer by default will not allow you to select locked widgets in the designer view.
- L92 _public member_ `TEnumAsByte<EDisplayOnCompile> CreateOnCompile;` — `UPROPERTY(EditAnywhere, config, Category = Interaction)` — Setting to automatically create compile tab based on compile results
- L96 _public member_ `TEnumAsByte<EDisplayOnCompile> DismissOnCompile;` — `UPROPERTY(EditAnywhere, config, Category = Interaction)` — Setting to automatically dismiss compile tab based on compile results
- L102 _public member_ `TObjectPtr<UWidgetPaletteFavorites> Favorites;` — `UPROPERTY()` — List of Favorites widgets used to populate the Favorites Palette

#### Free symbols / members of external scopes

- L18 _macro_ `#define UE_API UMGEDITOR_API`

### `Source/Editor/UMGEditor/Public/SlateVectorArtDataFactory.h` (Public)


#### class `USlateVectorArtDataFactory`  
`class USlateVectorArtDataFactory : public UFactory`  
_L18-25_
- reflection: `UCLASS(hidecategories = Object, collapsecategories, MinimalAPI)`
- inherits: `UFactory`
- L23 _private prototype_ `virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;`

### `Source/Editor/UMGEditor/Public/Templates/WidgetTemplateBlueprintClass.h` (Public)


#### class `FWidgetTemplateBlueprintClass`  
`class FWidgetTemplateBlueprintClass : public FWidgetTemplateClass`  
_L21-62_
- inherits: `FWidgetTemplateClass`
- desc: A template for classes generated by UWidgetBlueprint assets Accounts for the possibility that a the blueprint may not be loaded when the palette is created
- L30 _public prototype_ `FWidgetTemplateBlueprintClass(const FAssetData& InWidgetAssetData, TSubclassOf<UUserWidget> InUserWidgetClass = {});` — Constructor @param InWidgetAssetData The FAssetData for the widget blueprint asset @param InUserWidgetClass The user-created widget class that will be created by this template @param bCacheParentClass True means we will search for parent class and cache, this is a slow operation, but useful for BPGCs.
- L36 _public prototype_ `virtual ~FWidgetTemplateBlueprintClass();` — Destructor
- L39 _public prototype_ `virtual FText GetCategory() const override;` — Gets the category for the widget
- L42 _public prototype_ `virtual UWidget* Create(UWidgetTree* Tree) override;` — Creates an instance of the widget for the tree.
- L45 _public prototype_ `virtual const FSlateBrush* GetIcon() const override;` — The icon coming from the default object of the class
- L48 _public prototype_ `virtual TSharedRef<IToolTip> GetToolTip() const override;` — Gets the tooltip widget for this palette item.
- L51 _public prototype_ `virtual FReply OnDoubleClicked() override;` — Opens the widget blueprint for edit
- L54 _public prototype_ `static bool Supports(UClass* InClass);` — Returns true if the supplied class is supported by this template
- L58 _protected member_ `TWeakObjectPtr<UClass> CachedParentClass;` — Parent Class of this widget template, may not be valid
- L61 _protected member_ `bool bIsBlueprintGeneratedClass;` — True if this template is for a cooked BP generated class

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API UMGEDITOR_API`

### `Source/Editor/UMGEditor/Public/Templates/WidgetTemplateClass.h` (Public)


#### class `FWidgetTemplateClass`  
`class FWidgetTemplateClass : public FWidgetTemplate`  
_L19-73_
- inherits: `FWidgetTemplate`
- desc: A template that can spawn any widget derived from the UWidget class.
- L23 _public prototype_ `explicit FWidgetTemplateClass(TSubclassOf<UWidget> InWidgetClass);` — Constructor
- L25 _public prototype_ `explicit FWidgetTemplateClass(const FAssetData& InWidgetAssetData, TSubclassOf<UWidget> InWidgetClass);`
- L28 _public prototype_ `virtual ~FWidgetTemplateClass();` — Destructor
- L31 _public prototype_ `virtual FText GetCategory() const override;` — Gets the category for the widget
- L34 _public prototype_ `virtual UWidget* Create(UWidgetTree* Tree) override;` — Creates an instance of the widget for the tree.
- L37 _public prototype_ `virtual const FSlateBrush* GetIcon() const override;` — The icon coming from the default object of the class
- L40 _public prototype_ `virtual TSharedRef<IToolTip> GetToolTip() const override;` — Gets the tooltip widget for this palette item.
- L43 _public prototype_ `virtual FText GetToolTipText() const;` — Gets the tooltip text for this palette item (the text that GetToolTip wraps into an IToolTip widget).
- L46 _public prototype_ `virtual void GetFilterStrings(TArray<FString>& OutStrings) const override;` — @param OutStrings - Returns an array of strings used for filtering/searching this widget template.
- L49 _public function_ `TWeakObjectPtr<UClass> GetWidgetClass() const` — Gets the WidgetClass which might be null.
- L52 _public function_ `const FAssetData& GetWidgetAssetData()` — Returns the asset data for this widget which might be invalid.
- L56 _protected prototype_ `FWidgetTemplateClass();` — Creates a widget template class without any class reference
- L59 _protected prototype_ `void OnObjectsReplaced(const TMap<UObject*, UObject*>& ReplacementMap);` — Called when objects need to be swapped out for new versions, like after a blueprint recompile.
- L62 _protected prototype_ `UWidget* CreateNamed(class UWidgetTree* Tree, FName NameOverride);` — Constructs the widget template with an overridden object name.
- L66 _protected member_ `TWeakObjectPtr<UClass> WidgetClass;` — The widget class that will be created by this template
- L69 _protected member_ `FAssetData WidgetAssetData;` — The asset data for the widget blueprint
- L72 _protected member_ `TWeakObjectPtr<UClass> CachedParentClass;` — Parent Class of this widget template, may not be valid

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API UMGEDITOR_API`

### `Source/Editor/UMGEditor/Public/Templates/WidgetTemplateImageClass.h` (Public)


#### class `FWidgetTemplateImageClass`  
`class FWidgetTemplateImageClass : public FWidgetTemplateClass`  
_L17-34_
- inherits: `FWidgetTemplateClass`
- L25 _public prototype_ `FWidgetTemplateImageClass(const FAssetData& InAssetData);` — Constructor. @param	InAssetData		The asset data used to create the widget
- L27 _public prototype_ `virtual ~FWidgetTemplateImageClass();`
- L30 _public prototype_ `virtual UWidget* Create(UWidgetTree* WidgetTree) override;` — Creates an instance of the widget for the tree
- L33 _public prototype_ `static bool Supports(UClass* InClass);` — Returns true if the supplied class is supported by this template

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API UMGEDITOR_API`

### `Source/Editor/UMGEditor/Public/UIComponentUtils.h` (Public)


#### class `FUIComponentUtils`  
`class FUIComponentUtils`  
_L15-63_
- L36 _public prototype_ `static FClassViewerInitializationOptions CreateClassViewerInitializationOptions(const TSet<const UClass*>& ExistingComponentClasses = TSet<const UClass*>());`
- L38 _public prototype_ `static void OnWidgetRenamed(FWidgetBlueprintEditor* BlueprintEditor, UWidgetBlueprint* WidgetBlueprint, const FName& OldVarName, const FName& NewVarName);`
- L41 _public function_ `static void OnWidgetRenamed(const TSharedRef<FWidgetBlueprintEditor>& BlueprintEditor, UWidgetBlueprint* WidgetBlueprint, const FName& OldVarName, const FName& NewVarName)` — `UE_DEPRECATED(5.9, "Use the FWidgetBlueprintEditor* overload instead.")`
- L46 _public prototype_ `static void ReplaceComponentVariableReferences(UWidgetBlueprint* WidgetBlueprint, const FName& OldWidgetName, const FName& NewWidgetName);`
- L48 _public prototype_ `static UWidget* AddComponent(FWidgetBlueprintEditor* BlueprintEditor, UWidgetBlueprint* WidgetBlueprint, const UClass* ComponentClass, const FName WidgetName, FText& OutErrorMessage);`
- L51 _public prototype_ `static void AddComponent(const TSharedRef<FWidgetBlueprintEditor>& BlueprintEditor, const UClass* ComponentClass, const FName WidgetName);` — `UE_DEPRECATED(5.9, "Use the FWidgetBlueprintEditor* overload instead.")`
- L53 _public prototype_ `static bool RemoveComponent(FWidgetBlueprintEditor* BlueprintEditor, UWidgetBlueprint* WidgetBlueprint, const UClass* ComponentClass, const FName WidgetName, FText& OutErrorMessage);`
- L56 _public prototype_ `static void RemoveComponent(const TSharedRef<FWidgetBlueprintEditor>& BlueprintEditor, const UClass* ComponentClass, const FName WidgetName);` — `UE_DEPRECATED(5.9, "Use the FWidgetBlueprintEditor* overload instead.")`
- L58 _public prototype_ `static bool MoveComponent(FWidgetBlueprintEditor* BlueprintEditor, UWidgetBlueprint* WidgetBlueprint, const UClass* ComponentClassToMove, const UClass* RelativeToComponentClass, const FName WidgetName, bool bMoveAfter, FText& OutErrorMessage);`
- L61 _public prototype_ `static void MoveComponent(const TSharedRef<FWidgetBlueprintEditor>& BlueprintEditor, const UClass* ComponentClassToMove, const UClass* RelativeToComponentClass, const FName WidgetName, bool bMoveAfter);` — `UE_DEPRECATED(5.9, "Use the FWidgetBlueprintEditor* overload instead.")`

#### class `FUIComponentUtils::FUIComponentClassFilter`  
`class FUIComponentClassFilter : public IClassViewerFilter`  
_L18-34_
- inherits: `IClassViewerFilter`
- L22 _public member_ `TSet <const UClass*> AllowedChildrenOfClasses;` — All children of these classes will be included unless filtered out by another setting.
- L23 _public member_ `TSet<const UClass*> ExcludedChildrenOfClasses;`
- L26 _public member_ `TSet<const UClass*> ExcludedHierarchyClasses;` — Classes in the same hierarchy as any of these will be excluded (both ancestors and descendants).
- L29 _public member_ `EClassFlags DisallowedClassFlags;` — Disallowed class flags.
- L31 _public prototype_ `virtual bool IsClassAllowed(const FClassViewerInitializationOptions& InInitOptions, const UClass* InClass, TSharedRef< FClassViewerFilterFuncs > InFilterFuncs) override;`
- L33 _public prototype_ `virtual bool IsUnloadedClassAllowed(const FClassViewerInitializationOptions& InInitOptions, const TSharedRef< const IUnloadedBlueprintData > InUnloadedClassData, TSharedRef< FClassViewerFilterFuncs > InFilterFuncs) override;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API UMGEDITOR_API`

### `Source/Editor/UMGEditor/Public/UIComponentWidgetBlueprintExtension.h` (Public)


#### class `UUIComponentWidgetBlueprintExtension`  
`class UUIComponentWidgetBlueprintExtension : public UWidgetBlueprintExtension`  
_L23-64_
- inherits: `UWidgetBlueprintExtension`
- desc: Extension to the Widget Blueprint that will save the Components and will be used in the editor for compilation.
- L27 _private prototype_ `explicit UUIComponentWidgetBlueprintExtension(const FObjectInitializer& ObjectInitializer = FObjectInitializer());`
- L30 _public member_ `static const FName MD_ComponentVariable;`
- L32 _public prototype_ `UUIComponent* AddComponent(const UClass* ComponentClass, FName OwnerName, FText& OutErrorMessage);`
- L33 _public prototype_ `UUIComponent* AddOrReplaceComponent(UUIComponent* Component, FName OwnerName);`
- L34 _public prototype_ `void RemoveComponent(const UClass* ComponentClass, FName OwnerName);`
- L35 _public prototype_ `void MoveComponent(FName OwnerName, const UClass* ComponentClass, const UClass* RelativeToComponentClass, bool bMoveAfter);`
- L36 _public prototype_ `TArray<UUIComponent*> GetComponentsFor(const UWidget* Target) const;`
- L37 _public prototype_ `UUIComponent* GetComponent(const UClass* ComponentClass, FName OwnerName) const;`
- L38 _public prototype_ `EDataValidationResult ValidateComponents(FDataValidationContext& Context) const;`
- L40 _public prototype_ `UUIComponentUserWidgetExtension* GetOrCreateExtension(UUserWidget* PreviewWidget);`
- L41 _public prototype_ `void RenameWidget(const FName& OldVarName, const FName& NewVarName);`
- L42 _public prototype_ `void ReplaceComponentVariableReferences(const FName& OldWidgetName, const FName& NewWidgetName);`
- L44 _public prototype_ `bool VerifyContainer(UUserWidget* UserWidget) const;`
- L47 _protected prototype_ `virtual void HandleBeginCompilation(FWidgetBlueprintCompilerContext& InCreationContext) override;`
- L48 _protected prototype_ `virtual void HandleCleanAndSanitizeClass(UWidgetBlueprintGeneratedClass* ClassToClean, UObject* OldCDO) override;`
- L49 _protected prototype_ `virtual void HandlePopulateGeneratedVariables(const FWidgetBlueprintCompilerContext::FPopulateGeneratedVariablesContext& Context) override;`
- L50 _protected prototype_ `virtual void HandleFinishCompilingClass(UWidgetBlueprintGeneratedClass* Class) override;`
- L51 _protected prototype_ `virtual bool HandleValidateGeneratedClass(UWidgetBlueprintGeneratedClass* Class) override;`
- L53 _protected prototype_ `virtual void HandleEndCompilation() override;`
- L56 _private prototype_ `UUIComponentContainer* DuplicateContainer(UObject* Outer) const;`
- L58 _private member_ `FWidgetBlueprintCompilerContext* CompilerContext = nullptr;`
- L62 _private member_ `TObjectPtr<UUIComponentContainer> ComponentContainer;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API UMGEDITOR_API`

### `Source/Editor/UMGEditor/Public/UMGEditorModule.h` (Public)


#### class `IUMGEditorModule`  
`class IUMGEditorModule : public IModuleInterface, public IHasMenuExtensibility, public IHasToolBarExtensibility, public IHasDesignerExtensibility, public IHasPropertyBindingExtensibility, public IHasClipboardExtensibility, public IHasWidgetDragDropExtensibility, public IHasWidgetContextMenuExtensibility`  
_L25-88_
- inherits: `IModuleInterface,IHasMenuExtensibility,IHasToolBarExtensibility,IHasDesignerExtensibility,IHasPropertyBindingExtensibility,IHasClipboardExtensibility,IHasWidgetDragDropExtensibility,IHasWidgetContextMenuExtensibility`
- desc: The public interface of the UMG editor module.
- L36 _public prototype_ `virtual class FWidgetBlueprintCompiler* GetRegisteredCompiler() = 0;`
- L38 _public prototype_ `DECLARE_EVENT_TwoParams(IUMGEditorModule, FOnRegisterTabs, const FWidgetBlueprintApplicationMode&, FWorkflowAllowedTabSet&);`
- L39 _public prototype_ `virtual FOnRegisterTabs& OnRegisterTabsForEditor() = 0;`
- L41 _public prototype_ `DECLARE_DELEGATE_RetVal_TwoParams(TSharedRef<FExtender>, FWidgetEditorToolbarExtender, const TSharedRef<FUICommandList>, TSharedRef<FWidgetBlueprintEditor>);`
- L44 _public prototype_ `virtual void AddWidgetEditorToolbarExtender(FWidgetEditorToolbarExtender&& InToolbarExtender) = 0;` — Add Toolbar extender for widget editor, used by widget tool palette.
- L47 _public prototype_ `virtual TArrayView<FWidgetEditorToolbarExtender> GetAllWidgetEditorToolbarExtenders() = 0;` — Get current toolbar extenders for widget editor
- L50 _public prototype_ `virtual void AddWidgetCustomizationExtender(const TSharedRef<IBlueprintWidgetCustomizationExtender>& WidgetCustomizationExtender) = 0;` — Add customization for widget
- L53 _public prototype_ `virtual void RemoveWidgetCustomizationExtender(const TSharedRef<IBlueprintWidgetCustomizationExtender>& WidgetCustomizationExtender) = 0;` — Remove customization for widget
- L56 _public prototype_ `virtual TArrayView<TSharedRef<IBlueprintWidgetCustomizationExtender>> GetAllWidgetCustomizationExtenders() = 0;` — Get current customization extenders for widget
- L59 _public prototype_ `DECLARE_EVENT_OneParam(IUMGEditorModule, FOnRegisterLayoutExtensions, FLayoutExtender&);` — Support for general layout extenders
- L60 _public prototype_ `virtual FOnRegisterLayoutExtensions& OnRegisterLayoutExtensions() = 0;`
- L62 _public prototype_ `DECLARE_DELEGATE_RetVal_OneParam(TSharedRef<IPropertyTypeCustomization>, FOnGetInstancePropertyTypeCustomizationInstance, TWeakPtr<FWidgetBlueprintEditor> Editor);`
- L64 _public prototype_ `virtual void RegisterInstancedCustomPropertyTypeLayout(FTopLevelAssetPath Type, FOnGetInstancePropertyTypeCustomizationInstance) = 0;` — Add an instance customization to the widget property view.
- L67 _public prototype_ `virtual void UnregisterInstancedCustomPropertyTypeLayout(FTopLevelAssetPath Type) = 0;` — Remove an instance customization to the widget property view.
- L76 _public prototype_ `virtual TArrayView<const FCustomPropertyTypeLayout> GetAllInstancedCustomPropertyTypeLayout() const = 0;` — Remove an instance customization to the widget property view.
- L84 _public prototype_ `DECLARE_EVENT_OneParam(IUMGEditorModule, FOnWidgetBlueprintCreated, FWidgetBlueprintCreatedArgs);`
- L87 _public prototype_ `virtual FOnWidgetBlueprintCreated& OnWidgetBlueprintCreated() = 0;` — Callback when a WidgetBlueprint is created by the factory.

#### struct `IUMGEditorModule::FCustomPropertyTypeLayout`  
`struct FCustomPropertyTypeLayout`  
_L69-73_
- L71 _public member_ `FTopLevelAssetPath Type;`
- L72 _public member_ `FOnGetInstancePropertyTypeCustomizationInstance Delegate;`

#### struct `IUMGEditorModule::FWidgetBlueprintCreatedArgs`  
`struct FWidgetBlueprintCreatedArgs`  
_L79-83_
- desc: Arguments for the OnBlueprintCreated callback.
- L81 _public member_ `UClass* ParentClass = nullptr;`
- L82 _public member_ `UWidgetBlueprint* Blueprint = nullptr;`

#### Free symbols / members of external scopes

- L14 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogUMGEditor, Log, All);`
- L14 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogUMGEditor, Log, All);`
- L16 _externvar_ `extern const FName UMGEditorAppIdentifier;`
- L38 _delegate_ `DECLARE_EVENT_TwoParams(IUMGEditorModule, FOnRegisterTabs, const FWidgetBlueprintApplicationMode&, FWorkflowAllowedTabSet&);`
- L41 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(TSharedRef<FExtender>, FWidgetEditorToolbarExtender, const TSharedRef<FUICommandList>, TSharedRef<FWidgetBlueprintEditor>);`
- L59 _delegate_ `DECLARE_EVENT_OneParam(IUMGEditorModule, FOnRegisterLayoutExtensions, FLayoutExtender&);` — Support for general layout extenders
- L62 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(TSharedRef<IPropertyTypeCustomization>, FOnGetInstancePropertyTypeCustomizationInstance, TWeakPtr<FWidgetBlueprintEditor> Editor);`
- L84 _delegate_ `DECLARE_EVENT_OneParam(IUMGEditorModule, FOnWidgetBlueprintCreated, FWidgetBlueprintCreatedArgs);`

### `Source/Editor/UMGEditor/Public/UMGEditorProjectSettings.h` (Public)


#### class `UUMGEditorProjectSettings`  
`class UUMGEditorProjectSettings : public UWidgetEditingProjectSettings`  
_L27-45_
- reflection: `UCLASS(MinimalAPI, config=Editor, defaultconfig)`
- inherits: `UWidgetEditingProjectSettings`
- desc: Implements the settings for the UMG Editor Project Settings
- L32 _public prototype_ `UUMGEditorProjectSettings();`
- L35 _public prototype_ `virtual FText GetSectionText() const override;`
- L36 _public prototype_ `virtual FText GetSectionDescription() const override;`
- L41 _public prototype_ `virtual void PostEditChangeChainProperty(struct FPropertyChangedChainEvent& PropertyChangedEvent) override;`

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API UMGEDITOR_API`

### `Source/Editor/UMGEditor/Public/WidgetBlueprint.h` (Public)


#### class `FWidgetBlueprintDelegates`  
`class FWidgetBlueprintDelegates`  
_L34-43_
- desc: Widget Delegates
- L38 _public prototype_ `DECLARE_TS_MULTICAST_DELEGATE_TwoParams(FGetAssetTagsWithContext, const UWidgetBlueprint*, FAssetRegistryTagsContext);` — delegate for generating widget asset registry tags.
- L39 _public prototype_ `DECLARE_TS_MULTICAST_DELEGATE_TwoParams(FGetAssetTags, const UWidgetBlueprint*, TArray<UObject::FAssetRegistryTag>&);`
- L42 _public member_ `static FGetAssetTagsWithContext GetAssetTagsWithContext;` — called by UWdgetBlueprint::GetAssetRegistryTags()

#### struct `FEditorPropertyPathSegment`  
`struct FEditorPropertyPathSegment`  
_L48-88_
- reflection: `USTRUCT()`
- L53 _public prototype_ `FEditorPropertyPathSegment();`
- L54 _public prototype_ `FEditorPropertyPathSegment(const FProperty* InProperty);`
- L55 _public prototype_ `FEditorPropertyPathSegment(const UFunction* InFunction);`
- L56 _public prototype_ `FEditorPropertyPathSegment(const UEdGraph* InFunctionGraph);`
- L58 _public function_ `UStruct* GetStruct() const`
- L59 _public prototype_ `FFieldVariant GetMember() const;`
- L61 _public prototype_ `void Rebase(UBlueprint* SegmentBase);`
- L62 _public prototype_ `bool ValidateMember(FDelegateProperty* DelegateProperty, FText& OutError) const;`
- L64 _public prototype_ `FName GetMemberName() const;`
- L65 _public prototype_ `FText GetMemberDisplayText() const;`
- L66 _public prototype_ `FGuid GetMemberGuid() const;`
- L72 _private member_ `TObjectPtr<UStruct> Struct;` — `UPROPERTY()` — The owner of the path segment (ie. What class or structure was this property from)
- L76 _private member_ `FName MemberName;` — `UPROPERTY()` — The member name in the structure this segment represents.
- L83 _private member_ `FGuid MemberGuid;` — `UPROPERTY()` — The member guid in this structure this segment represents.  If this is valid it should be used instead of Name to get the true name.
- L87 _private member_ `bool IsProperty;` — `UPROPERTY()` — true if property, false if function

#### struct `FEditorPropertyPath`  
`struct FEditorPropertyPath`  
_L93-125_
- reflection: `USTRUCT()`
- L100 _public prototype_ `FEditorPropertyPath();`
- L103 _public prototype_ `FEditorPropertyPath(const TArray<FFieldVariant>& BindingChain);`
- L106 _public prototype_ `bool Rebase(UBlueprint* SegmentBase);`
- L109 _public function_ `bool IsEmpty() const`
- L112 _public prototype_ `bool Validate(FDelegateProperty* Destination, FText& OutError) const;`
- L115 _public prototype_ `FText GetDisplayText() const;`
- L118 _public prototype_ `FDynamicPropertyPath ToPropertyPath() const;`
- L124 _public member_ `TArray<FEditorPropertyPathSegment> Segments;` — `UPROPERTY()` — The path of properties.

#### struct `FDelegateEditorBinding`  
`struct FDelegateEditorBinding`  
_L129-174_
- reflection: `USTRUCT()`
- L135 _public member_ `FString ObjectName;` — `UPROPERTY()` — The member widget the binding is on, must be a direct variable of the UUserWidget.
- L139 _public member_ `FName PropertyName;` — `UPROPERTY()` — The property on the ObjectName that we are binding to.
- L143 _public member_ `FName FunctionName;` — `UPROPERTY()` — The function that was generated to return the SourceProperty
- L147 _public member_ `FName SourceProperty;` — `UPROPERTY()` — The property we are bindings to directly on the source object.
- L151 _public member_ `FEditorPropertyPath SourcePath;` — `UPROPERTY()`
- L155 _public member_ `FGuid MemberGuid;` — `UPROPERTY()` — If it's an actual Function Graph in the blueprint that we're bound to, there's a GUID we can use to lookup that function, to deal with renames better.  This is that GUID.
- L158 _public member_ `EBindingKind Kind = EBindingKind::Property;` — `UPROPERTY()`
- L160 _public function_ `bool operator==( const FDelegateEditorBinding& Other ) const`
- L167 _public prototype_ `bool IsAttributePropertyBinding(class UWidgetBlueprint* Blueprint) const;`
- L169 _public prototype_ `bool DoesBindingTargetExist(UWidgetBlueprint* Blueprint) const;`
- L171 _public prototype_ `bool IsBindingValid(UClass* Class, class UWidgetBlueprint* Blueprint, FCompilerResultsLog& MessageLog) const;`
- L173 _public prototype_ `FDelegateRuntimeBinding ToRuntimeBinding(class UWidgetBlueprint* Blueprint) const;`

#### enum `EWidgetSupportsDynamicCreation`  
`enum class EWidgetSupportsDynamicCreation : uint8`  
_L177-182_
- reflection: `UENUM()`
- L179 _public enumerator_ `Default`
- L180 _public enumerator_ `Yes`
- L181 _public enumerator_ `No`

#### enum `EThumbnailPreviewSizeMode`  
`enum class EThumbnailPreviewSizeMode : uint8`  
_L186-192_
- reflection: `UENUM()`
- L188 _public enumerator_ `MatchDesignerMode`
- L189 _public enumerator_ `FillScreen`
- L190 _public enumerator_ `Custom`
- L191 _public enumerator_ `Desired`

#### enum `EWidgetCompileTimeTickPrediction`  
`enum class EWidgetCompileTimeTickPrediction : uint8`  
_L202-212_
- reflection: `UENUM()`
- desc: This represents the tickability of a widget computed at compile time It is designed as a hint so the runtime can determine if ticking needs to be enabled A lot of widgets set to WillTick means you might have a performance problem
- L205 _public enumerator_ `WontTick` — The widget is manually set to never tick or we dont detect any animations, latent actions, and/or script or possible native tick methods
- L208 _public enumerator_ `OnDemand` — This widget is set to auto tick and we detect animations, latent actions but not script or native tick methods
- L211 _public enumerator_ `WillTick` — This widget has an implemented script tick or native tick

#### class `UWidgetBlueprint`  
`class UWidgetBlueprint : public UBaseWidgetBlueprint`  
_L218-381_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UBaseWidgetBlueprint`
- desc: The widget blueprint enables extending UUserWidget the user extensible UWidget.
- L226 _public member_ `TArray< FDelegateEditorBinding > Bindings;` — `UPROPERTY()`
- L229 _public member_ `TArray<TObjectPtr<UWidgetAnimation>> Animations;` — `UPROPERTY()`
- L239 _public member_ `TMap<FName, FGuid> WidgetVariableNameToGuidMap;` — `UPROPERTY()` — Saved Guids for variables generated by this blueprint (Widgets and Animations). Used to fixup external references to renamed widgets/animations in this blueprint See: OnVariableAdded, OnVariableRenamed, OnVariableRemoved
- L247 _public member_ `FString PaletteCategory;` — `UPROPERTY(AssetRegistrySearchable)` — Don't directly modify this property to change the palette category.  The actual value is stored in the CDO of the UUserWidget, but a copy is stored here so that it's available in the serialized Tag data in the asset header for access in the FAssetData.
- L255 _public member_ `bool bCanCallInitializedWithoutPlayerContext;` — `UPROPERTY(EditAnywhere, Category="Widget")` — Determines whether this widget blueprint can be initialized without a valid player context (PlayerController, etc.). Required to be true for use with UMG Widget Preview.
- L257 _public prototype_ `void OnVariableAdded(const FName& VariableName);`
- L258 _public prototype_ `void OnVariableRenamed(const FName& OldName, const FName& NewName);`
- L259 _public prototype_ `void OnVariableRemoved(const FName& VariableName);`
- L265 _public prototype_ `virtual void PostLoad() override;` — UObject interface
- L266 _public prototype_ `virtual void PostDuplicate(bool bDuplicateForPIE) override;`
- L269 _public prototype_ `virtual void PreSave(FObjectPreSaveContext ObjectSaveContext) override;`
- L273 _public prototype_ `virtual void GetAssetRegistryTags(FAssetRegistryTagsContext Context) const override;`
- L274 _public prototype_ `virtual void NotifyGraphRenamed(class UEdGraph* Graph, FName OldName, FName NewName) override;`
- L275 _public prototype_ `virtual EDataValidationResult IsDataValid(class FDataValidationContext& Context) const override;`
- L276 _public prototype_ `bool DetectSlateWidgetLeaks(class FDataValidationContext& Context) const;`
- L277 _public prototype_ `virtual bool FindDiffs(const UBlueprint* OtherBlueprint, FDiffResults& Results) const override;`
- L280 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L282 _public prototype_ `UPackage* GetWidgetTemplatePackage() const;`
- L284 _public prototype_ `virtual void ReplaceDeprecatedNodes() override;`
- L287 _public prototype_ `virtual UClass* GetBlueprintClass() const override;`
- L289 _public prototype_ `virtual bool AllowsDynamicBinding() const override;`
- L291 _public prototype_ `virtual bool SupportsInputEvents() const override;`
- L293 _public function_ `virtual bool SupportedByDefaultBlueprintFactory() const override`
- L298 _public prototype_ `virtual void GetReparentingRules(TSet< const UClass* >& AllowedChildrenOfClasses, TSet< const UClass* >& DisallowedChildrenOfClasses) const override;`
- L301 _public function_ `virtual bool AlwaysCompileOnLoad() const override` — UWidget blueprints are never data only, should always compile on load (data only blueprints cannot declare new variables)
- L304 _public prototype_ `virtual void GatherDependencies(TSet<TWeakObjectPtr<UBlueprint>>& InDependencies) const override;`
- L307 _public prototype_ `bool IsWidgetFreeFromCircularReferences(UUserWidget* UserWidget) const;` — Returns true if the supplied user widget will not create a circular reference when added to this blueprint
- L310 _public prototype_ `TValueOrError<void, UWidget*> HasCircularReferences() const;`
- L312 _public prototype_ `TValueOrError<void, TSet<UWidget*>> HasConflictingWidgetNamesFromInheritance() const;`
- L315 _public prototype_ `static bool ValidateGeneratedClass(const UClass* InClass);`
- L317 _public prototype_ `static TSharedPtr<FKismetCompilerContext> GetCompilerForWidgetBP(UBlueprint* BP, FCompilerResultsLog& InMessageLog, const FKismetCompilerOptions& InCompileOptions);`
- L320 _public prototype_ `void UpdateTickabilityStats(bool& OutHasLatentActions, bool& OutHasAnimations, bool& OutClassRequiresNativeTick);` — `UE_DEPRECATED(5.8, "Use UpdateTickabilityStatsAndInputRegistration instead.")`
- L323 _public prototype_ `void UpdateTickabilityStatsAndInputRegistration(bool& OutHasLatentActions, bool& OutHasAnimations, bool& OutClassRequiresNativeTick, bool& OutClassRequiresInputReg);` — Queries the parent widget chain to determine which features we can enable/disable based on what is needed.
- L325 _public prototype_ `bool ArePropertyBindingsAllowed() const;`
- L328 _public prototype_ `TArray<FName> GetInheritedAvailableNamedSlots() const;` — Gets any named slots exposed by the parent generated class that can be slotted into by the subclass.
- L331 _public prototype_ `TSet<FName> GetInheritedNamedSlotsWithContentInSameTree() const;` — Gets named slots exposed by the parent generated class that already have content in the parent widget tree.
- L333 _public prototype_ `virtual UWidgetEditingProjectSettings* GetRelevantSettings();`
- L334 _public prototype_ `virtual const UWidgetEditingProjectSettings* GetRelevantSettings() const;`
- L338 _protected prototype_ `virtual void LoadModulesRequiredForCompilation() override;`
- L342 _private prototype_ `void FixupLegacySequencePlayerCalls();`
- L349 _private member_ `EWidgetTickFrequency TickFrequency;` — `UPROPERTY(AssetRegistrySearchable)` — The desired tick frequency set by the user on the UserWidget's CDO.
- L356 _private member_ `EWidgetCompileTimeTickPrediction TickPrediction;` — `UPROPERTY(AssetRegistrySearchable)` — The computed frequency that the widget will need to be ticked at.  You can find the reasons for this decision by looking at TickPredictionReason.
- L362 _private member_ `FString TickPredictionReason;` — `UPROPERTY(AssetRegistrySearchable)` — The reasons we may need to tick this widget.
- L370 _public member_ `int32 PropertyBindings;` — `UPROPERTY(AssetRegistrySearchable)` — The total number of property bindings.  Consider this as a performance warning.
- L373 _public member_ `EThumbnailPreviewSizeMode ThumbnailSizeMode;` — `UPROPERTY(EditDefaultsOnly, Category = ThumbnailSettings)`
- L376 _public member_ `FVector2D ThumbnailCustomSize;` — `UPROPERTY(EditDefaultsOnly, Category = ThumbnailSettings)`
- L379 _public member_ `TObjectPtr<UTexture2D> ThumbnailImage;` — `UPROPERTY(EditDefaultsOnly, Category = ThumbnailSettings)`

#### Free symbols / members of external scopes

- L17 _macro_ `#define UE_API UMGEDITOR_API`
- L38 _delegate_ `DECLARE_TS_MULTICAST_DELEGATE_TwoParams(FGetAssetTagsWithContext, const UWidgetBlueprint*, FAssetRegistryTagsContext);` — delegate for generating widget asset registry tags.
- L39 _delegate_ `DECLARE_TS_MULTICAST_DELEGATE_TwoParams(FGetAssetTags, const UWidgetBlueprint*, TArray<UObject::FAssetRegistryTag>&);`

### `Source/Editor/UMGEditor/Public/WidgetBlueprintCompiler.h` (Public)


#### class `FWidgetBlueprintCompiler`  
`class FWidgetBlueprintCompiler : public IBlueprintCompiler`  
_L25-48_
- inherits: `IBlueprintCompiler`
- L29 _public prototype_ `FWidgetBlueprintCompiler();`
- L31 _public prototype_ `bool CanCompile(const UBlueprint* Blueprint) override;`
- L32 _public prototype_ `void PreCompile(UBlueprint* Blueprint, const FKismetCompilerOptions& CompileOptions) override;`
- L33 _public prototype_ `void Compile(UBlueprint* Blueprint, const FKismetCompilerOptions& CompileOptions, FCompilerResultsLog& Results) override;`
- L34 _public prototype_ `void PostCompile(UBlueprint* Blueprint, const FKismetCompilerOptions& CompileOptions) override;`
- L35 _public prototype_ `bool GetBlueprintTypesForClass(UClass* ParentClass, UClass*& OutBlueprintClass, UClass*& OutBlueprintGeneratedClass) const override;`
- L40 _private member_ `TComponentReregisterContext<UWidgetComponent>* ReRegister;` — The temporary variable that captures and reinstances components after compiling finishes.
- L46 _private member_ `int32 CompileCount;` — The current count on the number of compiles that have occurred.  We don't want to re-register components until all compiling has stopped.

#### class `FWidgetBlueprintCompilerContext`  
`class FWidgetBlueprintCompilerContext : public FKismetCompilerContext`  
_L54-171_
- inherits: `FKismetCompilerContext`
- L57 _protected typedef_ `typedef FKismetCompilerContext Super;`
- L60 _public prototype_ `FWidgetBlueprintCompilerContext(UWidgetBlueprint* SourceSketch, FCompilerResultsLog& InMessageLog, const FKismetCompilerOptions& InCompilerOptions);`
- L61 _public prototype_ `virtual ~FWidgetBlueprintCompilerContext();`
- L68 _protected prototype_ `void ValidateWidgetAnimations();` — Checks if the animations' bindings are valid. Shows a compiler warning if any of the animations have a null track, urging the user to delete said track to avoid performance hitches when playing said null tracks in large user widgets.
- L71 _protected prototype_ `void ValidateDesiredFocusWidgetName();` — Validates the Desired Focus name to make sure it's part of the Widget Tree.
- L74 _protected prototype_ `virtual UEdGraphSchema_K2* CreateSchema() override;`
- L75 _protected prototype_ `virtual void CreateFunctionList() override;`
- L76 _protected prototype_ `virtual void SpawnNewClass(const FString& NewClassName) override;`
- L77 _protected prototype_ `virtual void OnNewClassSet(UBlueprintGeneratedClass* ClassToUse) override;`
- L78 _protected prototype_ `virtual void PrecompileFunction(FKismetFunctionContext& Context, EInternalCompilerFlags InternalFlags) override;`
- L79 _protected prototype_ `virtual void CleanAndSanitizeClass(UBlueprintGeneratedClass* ClassToClean, UObject*& InOutOldCDO) override;`
- L80 _protected prototype_ `virtual void SaveSubObjectsFromCleanAndSanitizeClass(FSubobjectCollection& SubObjectsToSave, UBlueprintGeneratedClass* ClassToClean) override;`
- L81 _protected prototype_ `virtual void EnsureProperGeneratedClass(UClass*& TargetClass) override;`
- L82 _protected prototype_ `virtual void PopulateBlueprintGeneratedVariables() override;`
- L83 _protected prototype_ `virtual void CreateClassVariablesFromBlueprint() override;`
- L84 _protected prototype_ `virtual void CopyTermDefaultsToDefaultObject(UObject* DefaultObject);`
- L85 _protected prototype_ `virtual void FinishCompilingClass(UClass* Class) override;`
- L86 _protected prototype_ `virtual bool ValidateGeneratedClass(UBlueprintGeneratedClass* Class) override;`
- L87 _protected prototype_ `virtual void OnPostCDOCompiled(const UObject::FPostCDOCompiledContext& Context) override;`
- L90 _protected prototype_ `void SanitizeBindings(UBlueprintGeneratedClass* Class);`
- L91 _protected prototype_ `void ValidateAndFixUpVariableGuids();`
- L93 _protected prototype_ `void VerifyEventReplysAreNotEmpty(FKismetFunctionContext& Context);`
- L94 _protected prototype_ `void VerifyFieldNotifyFunction(FKismetFunctionContext& Context);`
- L97 _public function_ `UWidgetBlueprint* WidgetBlueprint() const`
- L99 _public prototype_ `void AddExtension(UWidgetBlueprintGeneratedClass* Class, UWidgetBlueprintGeneratedClassExtension* Extension);`
- L100 _public prototype_ `void AddGeneratedVariable(FBPVariableDescription&& VariableDescription) const;`
- L147 _public prototype_ `void static UpdateGeneratedClassWidgetTree(UWidgetBlueprint* WidgetBP, UWidgetBlueprintGeneratedClass* BPGClass, UWidgetTree* OldWidgetTree, FCompilerResultsLog* MessageLog);` — Duplicate the widget tree of the passed widget blueprint and assign it as the widget tree of the passed generated class.
- L148 _public prototype_ `void static ClearGeneratedClassWidgetTree(UWidgetBlueprintGeneratedClass* WBC_ToClean, bool bRecompilingOnLoad);`
- L151 _protected prototype_ `void static FixAbandonedWidgetTree(UWidgetBlueprint* WidgetBP);`
- L153 _protected member_ `UWidgetBlueprintGeneratedClass* NewWidgetBlueprintClass;`
- L155 _protected member_ `UWidgetTree* OldWidgetTree;`
- L157 _protected member_ `TArray<UWidgetAnimation*> OldWidgetAnimations;`
- L159 _protected member_ `UWidgetGraphSchema* WidgetSchema;`
- L162 _protected member_ `TMap<UWidget*, FProperty*> WidgetToMemberVariableMap;` — Map of properties created for widgets; to aid in debug data generation
- L165 _protected member_ `TMap<UWidget*, FProperty*> ParentWidgetToBindWidgetMap;` — Map of properties created in parent widget for bind widget validation
- L168 _protected member_ `TMap<UWidgetAnimation*, FProperty*> WidgetAnimToMemberVariableMap;` — Map of properties created for widget animations; to aid in debug data generation

#### struct `FWidgetBlueprintCompilerContext::FPopulateGeneratedVariablesContext`  
`struct FPopulateGeneratedVariablesContext`  
_L102-112_
- L105 _public prototype_ `void AddGeneratedVariable(FBPVariableDescription&& VariableDescription) const;`
- L106 _public prototype_ `UWidgetBlueprint* GetWidgetBlueprint() const;`
- L110 _private prototype_ `FPopulateGeneratedVariablesContext(FWidgetBlueprintCompilerContext& InContext);`
- L111 _private member_ `FWidgetBlueprintCompilerContext& Context;`

#### struct `FWidgetBlueprintCompilerContext::FCreateVariableContext`  
`struct FCreateVariableContext`  
_L114-131_
- L117 _public prototype_ `FProperty* CreateVariable(const FName Name, const FEdGraphPinType& Type) const;`
- L118 _public prototype_ `FMulticastDelegateProperty* CreateMulticastDelegateVariable(const FName Name, const FEdGraphPinType& Type) const;`
- L119 _public prototype_ `FMulticastDelegateProperty* CreateMulticastDelegateVariable(const FName Name) const;`
- L120 _public prototype_ `void AddGeneratedFunctionGraph(UEdGraph* Graph) const;`
- L121 _public prototype_ `UWidgetBlueprint* GetWidgetBlueprint() const;`
- L123 _public prototype_ `UWidgetBlueprintGeneratedClass* GetSkeletonGeneratedClass() const;` — `UE_DEPRECATED(5.4, "GetSkeletonGeneratedClass renamed to GetGeneratedClass")`
- L124 _public prototype_ `UWidgetBlueprintGeneratedClass* GetGeneratedClass() const;`
- L125 _public prototype_ `EKismetCompileType::Type GetCompileType() const;`
- L129 _private prototype_ `FCreateVariableContext(FWidgetBlueprintCompilerContext& InContext);`
- L130 _private member_ `FWidgetBlueprintCompilerContext& Context;`

#### struct `FWidgetBlueprintCompilerContext::FCreateFunctionContext`  
`struct FCreateFunctionContext`  
_L133-144_
- L136 _public prototype_ `void AddGeneratedFunctionGraph(UEdGraph* Graph) const;`
- L137 _public prototype_ `void AddGeneratedUbergraphPage(UEdGraph* Graph) const;`
- L138 _public prototype_ `UWidgetBlueprintGeneratedClass* GetGeneratedClass() const;`
- L142 _private prototype_ `FCreateFunctionContext(FWidgetBlueprintCompilerContext& InContext);`
- L143 _private member_ `FWidgetBlueprintCompilerContext& Context;`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API UMGEDITOR_API`

### `Source/Editor/UMGEditor/Public/WidgetBlueprintEditor.h` (Public)


#### struct `FNamedSlotSelection`  
`struct FNamedSlotSelection`  
_L33-37_
- L35 _public member_ `FWidgetReference NamedSlotHostWidget;`
- L36 _public member_ `FName SlotName;`

#### class `FWidgetBlueprintEditor`  
`class FWidgetBlueprintEditor : public FBlueprintEditor`  
_L42-565_
- inherits: `FBlueprintEditor`
- desc: widget blueprint editor (extends Blueprint editor)
- L45 _private typedef_ `using Super = FBlueprintEditor;`
- L48 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnHoveredWidgetSet, const FWidgetReference&) DECLARE_MULTICAST_DELEGATE(FOnHoveredWidgetCleared);`
- L69 _public prototype_ `FWidgetBlueprintEditor();`
- L71 _public prototype_ `virtual ~FWidgetBlueprintEditor();`
- L73 _public prototype_ `void InitWidgetBlueprintEditor(const EToolkitMode::Type Mode, const TSharedPtr< IToolkitHost >& InitToolkitHost, const TArray<UBlueprint*>& InBlueprints, bool bShouldOpenInDefaultsMode);`
- L76 _public prototype_ `virtual void Tick(float DeltaTime) override;`
- L77 _public prototype_ `virtual void PostUndo(bool bSuccessful) override;`
- L78 _public prototype_ `virtual void PostRedo(bool bSuccessful) override;`
- L79 _public prototype_ `virtual void Compile() override;`
- L83 _public prototype_ `virtual bool OnRequestClose(EAssetEditorCloseReason InCloseReason) override;`
- L87 _public prototype_ `virtual void AddReferencedObjects( FReferenceCollector& Collector ) override;`
- L91 _public prototype_ `virtual FName GetToolkitContextFName() const override;`
- L92 _public prototype_ `virtual FName GetToolkitFName() const override;`
- L93 _public prototype_ `virtual FText GetBaseToolkitName() const override;`
- L94 _public prototype_ `virtual FString GetWorldCentricTabPrefix() const override;`
- L95 _public prototype_ `virtual FLinearColor GetWorldCentricTabColorScale() const override;`
- L96 _public prototype_ `virtual void InitToolMenuContext(FToolMenuContext& MenuContext) override;`
- L97 _public prototype_ `void OnToolkitHostingStarted(const TSharedRef<IToolkit>& Toolkit) override;`
- L98 _public prototype_ `void OnToolkitHostingFinished(const TSharedRef<IToolkit>& Toolkit) override;`
- L102 _public prototype_ `class UWidgetBlueprint* GetWidgetBlueprintObj() const;` — @return The widget blueprint currently being edited in this editor
- L105 _public prototype_ `UUserWidget* GetPreview() const;` — @return The preview widget.
- L108 _public prototype_ `FPreviewScene* GetPreviewScene();` — @return The preview scene that owns the preview widget.
- L111 _public prototype_ `bool IsSimulating() const;`
- L114 _public prototype_ `void SetIsSimulating(bool bSimulating);`
- L117 _public prototype_ `void InvalidatePreview(bool bViewOnly = false);` — Causes the preview to be destroyed and a new one to be created next tick
- L120 _public prototype_ `void RefreshPreview();` — Immediately rebuilds the preview widget.
- L123 _public prototype_ `FWidgetReference GetReferenceFromTemplate(UWidget* TemplateWidget);` — Creates a widget reference using the template.
- L126 _public prototype_ `FWidgetReference GetReferenceFromPreview(UWidget* PreviewWidget);` — Creates a widget reference using the preview.  Which is used to lookup the stable template pointer.
- L129 _public prototype_ `TSharedPtr<ISequencer>& GetSequencer();` — @return The currently active sequencer used to create widget animations
- L132 _public prototype_ `TSharedPtr<ISequencer>& GetTabSequencer();` — @return The sequencer used to create widget animations
- L135 _public prototype_ `TSharedPtr<ISequencer>& GetDrawerSequencer();` — @return The sequencer used to create widget animations in drawer
- L138 _public prototype_ `void DockInLayoutClicked();` — Callback to dock anim tab into layout
- L141 _public prototype_ `void ChangeViewedAnimation( UWidgetAnimation& InAnimationToView );` — Changes the currently viewed animation in Sequencer to the new one
- L144 _public function_ `UWidgetAnimation* GetCurrentAnimation()` — Get the current animation
- L147 _public prototype_ `const UWidgetAnimation* RefreshCurrentAnimation();` — Updates the current animation if it is invalid
- L150 _public prototype_ `void SelectWidgets(const TSet<FWidgetReference>& Widgets, bool bAppendOrToggle);` — Sets the currently selected set of widgets
- L153 _public prototype_ `void SelectObjects(const TSet<UObject*>& Objects);` — Sets the currently selected set of objects
- L156 _public prototype_ `bool IsBindingSelected(const FMovieSceneBinding& InBinding);` — Called to determine whether a binding is selected in the tree view
- L159 _public prototype_ `void SetSelectedNamedSlot(TOptional<FNamedSlotSelection> SelectedNamedSlot);` — Sets the selected named slot
- L162 _public prototype_ `void CleanSelection();` — Removes removed widgets from the selection set.
- L165 _public prototype_ `const TSet<FWidgetReference>& GetSelectedWidgets() const;` — @return The selected set of widgets
- L168 _public prototype_ `TOptional<FNamedSlotSelection> GetSelectedNamedSlot() const;` — @return The selected named slot
- L171 _public prototype_ `const TSet< TWeakObjectPtr<UObject> >& GetSelectedObjects() const;` — @return The selected set of Objects
- L174 _public function_ `const TWeakObjectPtr<UClass> GetSelectedTemplate() const` — @return the selected template widget
- L177 _public function_ `const FAssetData GetSelectedUserWidget() const` — @return the selected user widget
- L180 _public function_ `void SetSelectedTemplate(TWeakObjectPtr<UClass> TemplateClass)` — Set the selected template widget
- L183 _public function_ `void SetSelectedUserWidget(FAssetData InSelectedUserWidget)` — Set the selected user widget
- L185 _public function_ `TSharedPtr<class FWidgetBlueprintEditorToolbar> GetWidgetToolbarBuilder()`
- L188 _public prototype_ `void MigrateFromChain(const FPropertyChangedEvent* PropertyChangedEvent, FEditPropertyChain* PropertyThatChanged, bool bIsModify);` — Migrate a property change from the preview GUI to the template GUI.
- L191 _public function_ `DECLARE_EVENT(FWidgetBlueprintEditor, FOnWidgetBlueprintTransaction) FOnWidgetBlueprintTransaction& GetOnWidgetBlueprintTransaction()` — Event called when an undo/redo transaction occurs
- L195 _public prototype_ `TSharedRef<SWidget> CreateSequencerTabWidget();` — Creates a sequencer widget
- L198 _public prototype_ `TSharedRef<SWidget> CreateSequencerDrawerWidget();` — Creates a sequencer widget, for anim drawer
- L201 _public prototype_ `TSharedRef<SWidget> OnGetWidgetAnimSequencer();` — Gets sequencer widget, for anim drawer
- L204 _public prototype_ `void AddExternalEditorWidget(FName ID, TSharedRef<SWidget> InExternalWidget);` — Adds external widget whose lifetime should be managed by this editor
- L207 _public prototype_ `int32 RemoveExternalEditorWidget(FName ID);` — Removes external widget whose lifetime should be managed by this editor
- L210 _public prototype_ `TSharedPtr<SWidget> GetExternalEditorWidget(FName ID);` — Gets external widget whose lifetime should be managed by this editor, NullWidget if not found
- L213 _public prototype_ `void ToggleAnimDrawer();` — Toggles Anim Drawer, only used for keyboard shortcut
- L216 _public prototype_ `void NotifyWidgetAnimListChanged();` — Callback for when widget animation list has been updated
- L219 _public prototype_ `void OnWidgetAnimSequencerOpened(FName StatusBarWithDrawerName);` — `UE_DEPRECATED(5.2, "OnWidgetAnimSequencerOpened is deprecated, please use OnWidgetAnimDrawerSequencerOpened instead.")`
- L222 _public prototype_ `void OnWidgetAnimSequencerDismissed(const TSharedPtr<SWidget>& NewlyFocusedWidget);` — `UE_DEPRECATED(5.2, "OnWidgetAnimSequencerDismissed is deprecated, please use OnWidgetAnimDrawerSequencerDismissed instead.")`
- L225 _public prototype_ `void OnWidgetAnimDrawerSequencerOpened(FName StatusBarWithDrawerName);` — Callback for anim drawer opening
- L228 _public prototype_ `void OnWidgetAnimDrawerSequencerDismissed(const TSharedPtr<SWidget>& NewlyFocusedWidget);` — Callback for anim drawer closing
- L231 _public prototype_ `void OnWidgetAnimTabSequencerClosed(TSharedRef<SDockTab> ClosedTab);` — Callback for anim tab closing
- L234 _public prototype_ `void OnWidgetAnimTabSequencerOpened();` — Callback for anim tab opening
- L240 _public prototype_ `void SetHoveredWidget(FWidgetReference& InHoveredWidget);` — The widget we're now hovering over in any particular context, allows multiple views to synchronize feedback on where that widget is in their representation.
- L242 _public prototype_ `void ClearHoveredWidget();`
- L245 _public prototype_ `const FWidgetReference& GetHoveredWidget() const;` — @return The widget that is currently being hovered over (either in the designer or hierarchy)
- L247 _public prototype_ `void AddPostDesignerLayoutAction(TFunction<void()> Action);`
- L249 _public prototype_ `void OnEnteringDesigner();`
- L251 _public prototype_ `TArray< TFunction<void()> >& GetQueuedDesignerActions();`
- L254 _public prototype_ `EWidgetDesignFlags GetCurrentDesignerFlags() const;` — Get the current designer flags that are in effect for the current user widget we're editing.
- L256 _public prototype_ `bool GetShowDashedOutlines() const;`
- L257 _public prototype_ `void SetShowDashedOutlines(bool Value);`
- L259 _public prototype_ `bool GetIsRespectingLocks() const;`
- L260 _public prototype_ `void SetIsRespectingLocks(bool Value);`
- L262 _public function_ `TSharedPtr<FPaletteViewModel> GetPaletteViewModel()`
- L263 _public function_ `TSharedPtr<FLibraryViewModel> GetLibraryViewModel()`
- L265 _public prototype_ `void CreateEditorModeManager() override;`
- L268 _public function_ `TSharedPtr<UE::UMG::Editor::FPreviewMode> GetPreviewMode() const` — Get the relative info for the Debug mode.
- L272 _public member_ `FOnHoveredWidgetSet OnHoveredWidgetSet;` — Fires whenever a new widget is being hovered over
- L275 _public member_ `FOnHoveredWidgetCleared OnHoveredWidgetCleared;` — Fires when there is no longer any widget being hovered over
- L278 _public member_ `FOnSelectedWidgetsChanged OnSelectedWidgetsChanging;` — Fires whenever the selected set of widgets changing
- L281 _public member_ `FOnSelectedWidgetsChanged OnSelectedWidgetsChanged;` — Fires whenever the selected set of widgets changes
- L284 _public member_ `FOnSelectedAnimationChanged OnSelectedAnimationChanged;` — Fires whenever the selected animation changes
- L287 _public member_ `FOnWidgetPreviewUpdated OnWidgetPreviewUpdated;` — Notification for when the preview widget has been updated
- L290 _public member_ `FOnWidgetAnimationsUpdated OnWidgetAnimationsUpdated;` — Notification for when animations have been updated
- L293 _public member_ `FOnWidgetPreviewReady OnWidgetPreviewReady;` — Notification for when the preview widget has been fully recreated
- L296 _public member_ `FOnEnterWidgetDesigner OnEnterWidgetDesigner;` — Fires after the mode change to Designer
- L299 _public member_ `TSharedPtr< FUICommandList > DesignerCommandList;` — Command list for handling widget actions in the WidgetBlueprintEditor
- L302 _public member_ `TArray< TSharedPtr<FUICommandInfo>> ToolPaletteCommands;` — Commands for switching between tool palettes
- L305 _public member_ `FVector2D PasteDropLocation;` — Paste Metadata
- L308 _protected prototype_ `virtual void InitalizeExtenders() override;`
- L309 _protected prototype_ `TSharedPtr<FExtender> CreateMenuExtender();`
- L310 _protected prototype_ `void FillFileMenu(FMenuBuilder& MenuBuilder);`
- L311 _protected prototype_ `void FillAssetMenu(FMenuBuilder& MenuBuilder);`
- L312 _protected prototype_ `void BindToolkitCommands();`
- L314 _protected prototype_ `void TakeSnapshot();`
- L315 _protected prototype_ `void CaptureThumbnail();`
- L316 _protected prototype_ `void ClearThumbnail();`
- L317 _protected prototype_ `bool IsImageUsedAsThumbnail();`
- L318 _protected prototype_ `bool IsPreviewWidgetInitialized();`
- L320 _protected prototype_ `void CustomizeWidgetCompileOptions(FMenuBuilder& InMenuBuilder);`
- L322 _protected prototype_ `static void AddCreateCompileTabSubMenu(FMenuBuilder& InMenuBuilder);`
- L323 _protected prototype_ `static void AddDismissCompileTabSubMenu(FMenuBuilder& InMenuBuilder);`
- L324 _protected prototype_ `static void SetDismissOnCompileSetting(EDisplayOnCompile InDismissOnCompile);`
- L325 _protected prototype_ `static void SetCreateOnCompileSetting(EDisplayOnCompile InCreateOnCompile);`
- L326 _protected prototype_ `static bool IsDismissOnCompileSet(EDisplayOnCompile InDismissOnCompile);`
- L327 _protected prototype_ `static bool IsCreateOnCompileSet(EDisplayOnCompile InCreateOnCompile);`
- L329 _protected prototype_ `void OpenCreateNativeBaseClassDialog();`
- L330 _protected prototype_ `void OnCreateNativeBaseClassSuccessfully(const FString& InClassName, const FString& InClassPath, const FString& InModuleName);`
- L331 _protected prototype_ `TSharedPtr<ISequencer> CreateSequencerWidgetInternal();`
- L334 _protected prototype_ `virtual void RegisterApplicationModes(const TArray<UBlueprint*>& InBlueprints, bool bShouldOpenInDefaultsMode, bool bNewlyCreated = false) override;`
- L335 _protected prototype_ `virtual FGraphAppearanceInfo GetGraphAppearance(class UEdGraph* InGraph) const override;`
- L336 _protected prototype_ `virtual TSubclassOf<UEdGraphSchema> GetDefaultSchemaClass() const override;`
- L340 _private prototype_ `bool CanDeleteSelectedWidgets();`
- L341 _private prototype_ `void DeleteSelectedWidgets();`
- L343 _private prototype_ `bool CanCopySelectedWidgets();`
- L344 _private prototype_ `void CopySelectedWidgets();`
- L346 _private prototype_ `bool CanPasteWidgets();`
- L347 _private prototype_ `void PasteWidgets();`
- L349 _private prototype_ `bool CanCutSelectedWidgets();`
- L350 _private prototype_ `void CutSelectedWidgets();`
- L352 _private prototype_ `bool CanDuplicateSelectedWidgets();`
- L353 _private prototype_ `void DuplicateSelectedWidgets();`
- L355 _private prototype_ `void OnFindWidgetReferences(bool bSearchAllBlueprints, const EGetFindReferenceSearchStringFlags Flags);`
- L356 _private prototype_ `bool CanFindWidgetReferences() const;`
- L359 _private prototype_ `bool CanCreateNativeBaseClass() const;` — Is creating a native base class for the current widget blueprint allowed
- L362 _private prototype_ `bool IsCreateNativeBaseClassVisible() const;` — Whether menu to create a native base class is visible
- L366 _private prototype_ `virtual void OnBlueprintChangedImpl(UBlueprint* InBlueprint, bool bIsJustBeingCompiled = false ) override;` — Called whenever the blueprint is structurally changed.
- L369 _private prototype_ `void OnObjectsReplaced(const TMap<UObject*, UObject*>& ReplacementMap);` — Called when objects need to be swapped out for new versions, like after a blueprint recompile.
- L372 _private prototype_ `void DestroyPreview();` — Destroy the current preview GUI object
- L375 _private prototype_ `void UpdatePreview(UBlueprint* InBlueprint, bool bInForceFullUpdate);` — Tick the current preview GUI object
- L378 _private prototype_ `void OnGetAnimationAddMenuContent(FMenuBuilder& MenuBuilder, TSharedRef<ISequencer> Sequencer);` — Populates the sequencer add menu.
- L382 _private prototype_ `void OnBuildCustomContextMenuForGuid(FMenuBuilder& MenuBuilder,FGuid ObjectBinding);` — Populates sequencer menu when added with objects. Used to handle case where widget is deleted so it's Object * is null.
- L385 _private prototype_ `void OnGetAnimationAddMenuContentAllWidgets(FMenuBuilder& MenuBuilder);` — Populates the sequencer add submenu for the big list of widgets.
- L388 _private prototype_ `void AddObjectToAnimation(UObject* ObjectToAnimate);` — Adds the supplied UObject to the current animation.
- L391 _private prototype_ `TSharedRef<FExtender> GetAddTrackSequencerExtender(const TSharedRef<FUICommandList> CommandList, const TArray<UObject*> ContextSensitiveObjects);` — Gets the extender to use for sequencers context sensitive menus and toolbars.
- L394 _private prototype_ `void ExtendSequencerAddTrackMenu( FMenuBuilder& AddTrackMenuBuilder, const TArray<UObject*> ContextObjects );` — Extends the sequencer add track menu.
- L397 _private prototype_ `void AddWidgetsToTrack(const TArray<FWidgetReference> Widgets, FGuid ObjectId);` — Binds additional widgets to a track of the same type
- L400 _private prototype_ `void RemoveWidgetsFromTrack(const TArray<FWidgetReference> Widgets, FGuid ObjectId);` — Unbind widgets from a track
- L403 _private prototype_ `void RemoveAllWidgetsFromTrack(FGuid ObjectId);` — Remove all bindings from a track
- L406 _private prototype_ `void RemoveMissingWidgetsFromTrack(FGuid ObjectId);` — Remove any missing bindings from a track
- L409 _private prototype_ `void ReplaceTrackWithWidgets(const TArray<FWidgetReference> Widgets, FGuid ObjectId);` — Replace current widget bindings on a track with new widget bindings
- L412 _private prototype_ `bool CanAddDynamicPossessionMenu();` — Dynamic binding
- L413 _private prototype_ `void AddDynamicPossessionMenu(FMenuBuilder& MenuBuilder, FGuid ObjectId);`
- L416 _private prototype_ `void AddSlotTrack( UPanelSlot* Slot );` — Add an animation track for the supplied slot to the current animation.
- L419 _private function_ `void AddSlotTrack(TObjectPtr<UPanelSlot> Slot)` — Add an animation track for the supplied slot to the current animation.
- L422 _private prototype_ `void AddMaterialTrack( UWidget* Widget, TArray<FProperty*> MaterialPropertyPath, FText MaterialPropertyDisplayName );` — Add an animation track for the supplied material property path to the current animation.
- L425 _private prototype_ `void OnMovieSceneDataChanged(EMovieSceneDataChangeType DataChangeType);` — Handler which is called whenever sequencer movie scene data changes.
- L428 _private prototype_ `void OnMovieSceneBindingsPasted(const TArray<FMovieSceneBinding>& BindingsPasted);` — Handler which is called whenever sequencer binding is pasted.
- L431 _private prototype_ `void SyncSelectedWidgetsWithSequencerSelection(TArray<FGuid> ObjectGuids);` — Fire off when sequencer selection changed
- L434 _private prototype_ `void SyncSequencerSelectionToSelectedWidgets();` — Tell sequencer the selected widgets changed
- L437 _private prototype_ `void SyncSequencersMovieSceneData();` — Tell sequencers movie data changed
- L440 _private function_ `UObject* GetAnimationPlaybackContext() const` — Get the animation playback context
- L443 _private function_ `TArray<UObject*> GetAnimationEventContexts() const` — Get the animation playback event contexts
- L446 _private prototype_ `void UpdateTrackName(FGuid ObjectId);` — Update the name of a track to reflect changes in bindings
- L449 _private prototype_ `void OnFinishedChangingDynamicBindingProperties(const FPropertyChangedEvent& ChangeEvent, TSharedPtr<FStructOnScope> ValueStruct, FGuid ObjectId);` — Called after changing dynamic binding properties
- L452 _private prototype_ `void OnDebugObjectAccess(UObject* DebugObject);` — If editing the matching widget blueprint, sets the blueprint's current debug instance to the given object.
- L456 _private member_ `FPreviewScene PreviewScene;` — The preview scene that owns the preview GUI
- L459 _private member_ `TMap<FName, TSharedPtr<SWidget>> ExternalEditorWidgets;` — For external widgets to have lifetimes bound to this editor instance
- L462 _private member_ `TArray<TWeakPtr<ISequencer>> Sequencers;` — List of created sequencers
- L465 _private member_ `TSharedPtr<ISequencer> TabSequencer;` — Sequencer for creating and previewing widget animations in tabs
- L468 _private member_ `TWeakPtr<SOverlay> TabSequencerOverlay;` — Overlay used to display UI on top of tab sequencer
- L471 _private member_ `TSharedPtr<ISequencer> DrawerSequencer;` — Sequencer for creating and previewing widget animations in drawer
- L474 _private member_ `TWeakPtr<SOverlay> DrawerSequencerOverlay;` — Overlay used to display UI on top of drawer sequencer
- L477 _private member_ `TSharedPtr<SWidget> AnimDrawerWidget;` — Widget created for anim drawer
- L480 _private member_ `TWeakPtr<STextBlock> NoAnimationTextBlockTab;` — A text block which is displayed in the overlay when no animation is selected.
- L483 _private member_ `TWeakPtr<STextBlock> NoAnimationTextBlockDrawer;` — A text block which is displayed in the overlay when no animation is selected in drawer.
- L486 _private member_ `UWidgetBlueprint* PreviewBlueprint;` — The Blueprint associated with the current preview
- L489 _private member_ `TSet< FWidgetReference > SelectedWidgets;` — The currently selected preview widgets in the preview GUI
- L492 _private member_ `TSet< TWeakObjectPtr<UObject> > SelectedObjects;` — The currently selected objects in the designer
- L495 _private member_ `TWeakObjectPtr<UClass> SelectedTemplate;` — The last selected template widget in the palette view
- L498 _private member_ `FAssetData SelectedUserWidget;` — AssetData of Selected UserWidget
- L501 _private member_ `TOptional<FNamedSlotSelection> SelectedNamedSlot;` — The currently selected named slot
- L504 _private member_ `mutable TWeakObjectPtr<UUserWidget> PreviewWidgetPtr;` — The preview GUI object
- L507 _private member_ `FOnWidgetBlueprintTransaction OnWidgetBlueprintTransaction;` — Delegate called when a undo/redo transaction happens
- L510 _private member_ `TSharedPtr<class FWidgetBlueprintEditorToolbar> WidgetToolbar;` — The toolbar builder associated with this editor
- L513 _private member_ `TSharedPtr<class FWidgetEditorModeUILayer> ModeUILayer;` — Used to spawn sidebar tool palette
- L516 _private member_ `TArray< TWeakPtr<FWidgetHandle> > WidgetHandlePool;` — The widget references out in the ether that may need to be updated after being issued.
- L519 _private member_ `FWidgetReference HoveredWidget;` — The widget currently being hovered over
- L522 _private member_ `bool bPreviewInvalidated;` — The preview becomes invalid and needs to be rebuilt on the next tick.
- L525 _private member_ `bool bIsSimulateEnabled;`
- L528 _private member_ `bool bIsRealTime;`
- L531 _private member_ `bool bShowDashedOutlines;` — Should the designer show outlines when it creates widgets?
- L534 _private member_ `bool bRespectLocks;`
- L536 _private member_ `TArray< TFunction<void()> > QueuedDesignerActions;`
- L539 _private member_ `TWeakObjectPtr<UWidgetAnimation> CurrentAnimation;` — The currently viewed animation, if any.
- L541 _private member_ `FDelegateHandle SequencerAddTrackExtenderHandle;`
- L544 _private member_ `bool bIsSequencerDrawerOpen;` — True if sequencer drawer is open
- L547 _private member_ `bool bRefreshGeneratedClassAnimations;` — When true the animation data in the generated class should be replaced with the current animation data.
- L550 _private member_ `TSharedPtr<FPaletteViewModel> PaletteViewModel;` — ViewModel used by the Palette and Palette Favorite Views
- L553 _private member_ `TSharedPtr<FLibraryViewModel> LibraryViewModel;` — ViewModel used by the Library View
- L555 _private member_ `TSharedPtr<UE::UMG::Editor::FPreviewMode> PreviewMode;`
- L558 _private member_ `bool bUpdatingSequencerSelection;` — When true the sequencer selection is being updated from changes to the external selection.
- L561 _private member_ `bool bUpdatingExternalSelection;` — When true the external selection is being updated from changes to the sequencer selection.
- L564 _private member_ `bool bIsPreviewWidgetSelected;` — True when the selected object is the preview widget. Used to restore selection after refreshing the preview.

#### Free symbols / members of external scopes

- L19 _macro_ `#define UE_API UMGEDITOR_API`
- L31 _namespace_ `namespace UE`
- L31 _namespace_ `namespace UMG` (scope `UE`)
- L31 _namespace_ `namespace Editor` (scope `UE::UMG`)
- L48 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnHoveredWidgetSet, const FWidgetReference&) DECLARE_MULTICAST_DELEGATE(FOnHoveredWidgetCleared);`
- L49 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnHoveredWidgetCleared);`
- L51 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnSelectedWidgetsChanging) DECLARE_MULTICAST_DELEGATE(FOnSelectedWidgetsChanged) DECLARE_MULTICAST_DELEGATE(FOnWidgetPreviewUpdated) DECLARE_MULTICAST_DELEGATE(FOnWidgetAnimationsUpdated) DECLARE_MULTICAST_DELEGATE(FOnSelectedAnimationChanged) DECLARE_EVENT(FWidgetBlueprintEditor, FOnEnterWidgetDesigner) DECLARE_MULTICAST_DELEGATE(FOnWidgetPreviewReady) public: FWidgetBlueprintEditor();`
- L52 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnSelectedWidgetsChanged) DECLARE_MULTICAST_DELEGATE(FOnWidgetPreviewUpdated) DECLARE_MULTICAST_DELEGATE(FOnWidgetAnimationsUpdated) DECLARE_MULTICAST_DELEGATE(FOnSelectedAnimationChanged) DECLARE_EVENT(FWidgetBlueprintEditor, FOnEnterWidgetDesigner) DECLARE_MULTICAST_DELEGATE(FOnWidgetPreviewReady) public: FWidgetBlueprintEditor();`
- L55 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnWidgetPreviewUpdated) DECLARE_MULTICAST_DELEGATE(FOnWidgetAnimationsUpdated) DECLARE_MULTICAST_DELEGATE(FOnSelectedAnimationChanged) DECLARE_EVENT(FWidgetBlueprintEditor, FOnEnterWidgetDesigner) DECLARE_MULTICAST_DELEGATE(FOnWidgetPreviewReady) public: FWidgetBlueprintEditor();` — Called after the widget preview has been updated
- L58 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnWidgetAnimationsUpdated) DECLARE_MULTICAST_DELEGATE(FOnSelectedAnimationChanged) DECLARE_EVENT(FWidgetBlueprintEditor, FOnEnterWidgetDesigner) DECLARE_MULTICAST_DELEGATE(FOnWidgetPreviewReady) public: FWidgetBlueprintEditor();` — Called when animation list changes
- L61 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnSelectedAnimationChanged) DECLARE_EVENT(FWidgetBlueprintEditor, FOnEnterWidgetDesigner) DECLARE_MULTICAST_DELEGATE(FOnWidgetPreviewReady) public: FWidgetBlueprintEditor();` — Called when animation selection changes
- L63 _delegate_ `DECLARE_EVENT(FWidgetBlueprintEditor, FOnEnterWidgetDesigner) DECLARE_MULTICAST_DELEGATE(FOnWidgetPreviewReady) public: FWidgetBlueprintEditor();`
- L66 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnWidgetPreviewReady) public: FWidgetBlueprintEditor();` — Called after the widget preview has fully recreated
- L191 _delegate_ `DECLARE_EVENT(FWidgetBlueprintEditor, FOnWidgetBlueprintTransaction) FOnWidgetBlueprintTransaction& GetOnWidgetBlueprintTransaction() { return OnWidgetBlueprintTransaction; } TSharedRef<SWidget> CreateSequencerTabWidget();` — Event called when an undo/redo transaction occurs

### `Source/Editor/UMGEditor/Public/WidgetBlueprintEditorUtils.h` (Public)


#### class `FWidgetBlueprintEditorUtils`  
`class FWidgetBlueprintEditorUtils`  
_L28-214_
- L45 _public prototype_ `static bool VerifyWidgetRename(TSharedRef<class FWidgetBlueprintEditor> BlueprintEditor, FWidgetReference Widget, const FText& NewName, FText& OutErrorMessage);`
- L47 _public prototype_ `static bool RenameWidget(TSharedRef<class FWidgetBlueprintEditor> BlueprintEditor, const FName& OldObjectName, const FString& NewDisplayName);`
- L49 _public prototype_ `static void ReplaceDesiredFocus(TSharedRef<FWidgetBlueprintEditor> BlueprintEditor, const FName& OldName, const FName& NewName);`
- L50 _public prototype_ `static void ReplaceDesiredFocus(UWidgetBlueprint* Blueprint, const FName& OldName, const FName& NewName);`
- L52 _public prototype_ `static void SetDesiredFocus(TSharedRef<FWidgetBlueprintEditor> BlueprintEditor, const FName DesiredFocusWidgetName);`
- L53 _public prototype_ `static void SetDesiredFocus(UWidgetBlueprint* Blueprint, const FName& DesiredFocusWidgetName);`
- L55 _public prototype_ `static void CreateWidgetContextMenu(FMenuBuilder& MenuBuilder, TSharedRef<FWidgetBlueprintEditor> BlueprintEditor, FVector2D TargetLocation);`
- L57 _public prototype_ `static void CopyWidgets(UWidgetBlueprint* BP, TSet<FWidgetReference> Widgets);`
- L59 _public prototype_ `static TArray<UWidget*> PasteWidgets(TSharedRef<FWidgetBlueprintEditor> BlueprintEditor, UWidgetBlueprint* BP, FWidgetReference ParentWidget, FName SlotName, FVector2D PasteLocation);`
- L73 _public prototype_ `static void ReplaceWidgets(UWidgetBlueprint* BP, TSet<UWidget*> Widgets, UClass* WidgetClass, EReplaceWidgetNamingMethod NewWidgetNamingMethod);`
- L76 _public prototype_ `static void DeleteWidgets(TSharedRef<FWidgetBlueprintEditor> BlueprintEditor, UWidgetBlueprint* BP, TSet<FWidgetReference> Widgets, bool bSilentDelete = false);` — `UE_DEPRECATED(5.6, "FWidgetBlueprintEditorUtils::DeleteWidgets no longer takes in the BlueprintEditor, use the version without it instead")`
- L85 _public prototype_ `static void DeleteWidgets(UWidgetBlueprint* BP, TSet<UWidget*> Widgets, EDeleteWidgetWarningType WarningType);`
- L87 _public prototype_ `static void CutWidgets(TSharedRef<FWidgetBlueprintEditor> BlueprintEditor, UWidgetBlueprint* BP, TSet<FWidgetReference> Widgets);`
- L89 _public prototype_ `static TArray<UWidget*> DuplicateWidgets(TSharedRef<FWidgetBlueprintEditor> BlueprintEditor, UWidgetBlueprint* BP, TSet<FWidgetReference> Widgets);`
- L91 _public prototype_ `static UUserWidget* CreateUserWidgetFromBlueprint(UObject* Outer, UWidgetBlueprint* BP, const FCreateWidgetFromBlueprintParams& Params);`
- L94 _public prototype_ `static void DestroyUserWidget(UUserWidget* UserWidget);` — Performs cleanup on the specified UserWidget.
- L96 _public prototype_ `static bool IsAnySelectedWidgetLocked(TSet<FWidgetReference> SelectedWidgets);`
- L98 _public prototype_ `static bool CanPasteWidgetsExtension(TSet<FWidgetReference> SelectedWidgets);`
- L100 _public prototype_ `static UWidget* GetWidgetTemplateFromDragDrop(UWidgetBlueprint* Blueprint, UWidgetTree* RootWidgetTree, TSharedPtr<FDragDropOperation>& DragDropOp);`
- L102 _public prototype_ `static bool ShouldPreventDropOnTargetExtensions(const UWidget* Target, const TSharedPtr<FDragDropOperation>& DragDropOp, FText& OutFailureText);`
- L104 _public prototype_ `static bool IsBindWidgetProperty(const FProperty* InProperty);`
- L105 _public prototype_ `static bool IsBindWidgetProperty(const FProperty* InProperty, bool& bIsOptional);`
- L107 _public prototype_ `static bool IsBindWidgetAnimProperty(const FProperty* InProperty);`
- L108 _public prototype_ `static bool IsBindWidgetAnimProperty(const FProperty* InProperty, bool& bIsOptional);`
- L117 _public prototype_ `static bool IsUsableWidgetClass(const UClass* WidgetClass);` — `UE_DEPRECATED(5.3, "This function has been deprecated. Use the version of IsUsableWidgetClass that takes a second argument of TSharedRef<FWidgetBlueprintEditor>.")`
- L119 _public prototype_ `static TValueOrError<FUsableWidgetClassResult, void> IsUsableWidgetClass(const FAssetData& WidgetAsset);` — `UE_DEPRECATED(5.3, "This function has been deprecated. Use the version of IsUsableWidgetClass that takes a second argument of TSharedRef<FWidgetBlueprintEditor>.")`
- L121 _public prototype_ `static bool IsUsableWidgetClass(const UClass* WidgetClass, TSharedRef<FWidgetBlueprintEditor> InCurrentActiveBlueprintEditor);`
- L122 _public prototype_ `static TValueOrError<FUsableWidgetClassResult, void> IsUsableWidgetClass(const FAssetData& WidgetAsset, TSharedRef<FWidgetBlueprintEditor> InCurrentActiveBlueprintEditor);`
- L124 _public prototype_ `static void ExportWidgetsToText(TArray<UWidget*> WidgetsToExport, FString& ExportedText);`
- L126 _public prototype_ `static void ImportWidgetsFromText(UWidgetBlueprint* BP, const FString& TextToImport, TSet<UWidget*>& ImportedWidgetSet, TMap<FName, UWidgetSlotPair*>& PastedExtraSlotData);`
- L129 _public prototype_ `static void ExportPropertiesToText(UObject* Object, TMap<FName, FString>& ExportedProperties);` — Exports the individual properties of an object to text and stores them in a map.
- L132 _public prototype_ `static void ImportPropertiesFromText(UObject* Object, const TMap<FName, FString>& ExportedProperties);` — Attempts to import any property in the map and apply it to a property with the same name on the object.
- L134 _public prototype_ `static bool DoesClipboardTextContainWidget(UWidgetBlueprint* BP);`
- L136 _public prototype_ `static TScriptInterface<INamedSlotInterface> FindNamedSlotHostForContent(UWidget* WidgetTemplate, UWidgetTree* WidgetTree);`
- L138 _public prototype_ `static UWidget* FindNamedSlotHostWidgetForContent(UWidget* WidgetTemplate, UWidgetTree* WidgetTree);`
- L140 _public prototype_ `static void FindAllAncestorNamedSlotHostWidgetsForContent(TArray<FWidgetReference>& OutSlotHostWidgets, UWidget* WidgetTemplate, TSharedRef<FWidgetBlueprintEditor> BlueprintEditor);`
- L142 _public prototype_ `static bool RemoveNamedSlotHostContent(UWidget* WidgetTemplate, TScriptInterface<INamedSlotInterface> NamedSlotHost);`
- L144 _public prototype_ `static bool ReplaceNamedSlotHostContent(UWidget* WidgetTemplate, TScriptInterface<INamedSlotInterface> NamedSlotHost, UWidget* NewContentWidget);`
- L146 _public prototype_ `static UWidgetTree* FindLatestWidgetTree(UWidgetBlueprint* Blueprint, UUserWidget* UserWidget);`
- L148 _public prototype_ `static int32 UpdateHittestGrid(FHittestGrid& HitTestGrid, TSharedRef<SWindow> Window, float Scale, FVector2D DrawSize, float DeltaTime);`
- L150 _public prototype_ `static TTuple<FVector2D, FVector2D> GetWidgetPreviewAreaAndSize(UUserWidget* UserWidget, FVector2D DesiredSize, FVector2D PreviewSize, EDesignPreviewSizeMode ThumbnailSizeMode, TOptional<FVector2D> ThumbnailCustomSize);`
- L152 _public prototype_ `static float GetWidgetPreviewDPIScale(UUserWidget* UserWidget, FVector2D PreviewSize);`
- L154 _public prototype_ `static EDesignPreviewSizeMode ConvertThumbnailSizeModeToDesignerSizeMode(EThumbnailPreviewSizeMode ThumbnailSizeMode, UUserWidget* WidgetInstance);`
- L156 _public prototype_ `static FVector2D GetWidgetPreviewUnScaledCustomSize(FVector2D DesiredSize, UUserWidget* UserWidget, TOptional<FVector2D> ThumbnailCustomSize, EThumbnailPreviewSizeMode ThumbnailSizeMode = EThumbnailPreviewSizeMode::MatchDesignerMode);`
- L158 _public prototype_ `static TTuple<float, FVector2D> GetThumbnailImageScaleAndOffset(FVector2D WidgetSize, FVector2D ThumbnailSize);`
- L160 _public prototype_ `static void SetTextureAsAssetThumbnail(UWidgetBlueprint* WidgetBlueprint, UTexture2D* ThumbnailTexture);`
- L162 _public prototype_ `static FText GetPaletteCategory(const TSubclassOf<UWidget> Widget);`
- L163 _public prototype_ `static FText GetPaletteCategory(const FAssetData& WidgetAsset, const TSubclassOf<UWidget> NativeClass);`
- L165 _public prototype_ `static TOptional<FWidgetThumbnailProperties> DrawSWidgetInRenderTargetForThumbnail(UUserWidget* WidgetInstance, FRenderTarget* RenderTarget2D, FVector2D ThumbnailSize, TOptional<FVector2D> ThumbnailCustomSize, EThumbnailPreviewSizeMode ThumbnailSizeMode = EThumbnailPreviewSizeMode::MatchDesignerMode);`
- L167 _public prototype_ `static TOptional<FWidgetThumbnailProperties> DrawSWidgetInRenderTargetForThumbnail(UUserWidget* WidgetInstance, UTextureRenderTarget2D* RenderTarget2D, FVector2D ThumbnailSize, TOptional<FVector2D> ThumbnailCustomSize, EThumbnailPreviewSizeMode ThumbnailSizeMode);`
- L169 _public prototype_ `static TOptional<FWidgetThumbnailProperties> DrawSWidgetInRenderTarget(UUserWidget* WidgetInstance, UTextureRenderTarget2D* RenderTarget2D);`
- L171 _public prototype_ `static UWidgetEditingProjectSettings* GetRelevantMutableSettings(TWeakPtr<FWidgetBlueprintEditor> CurrentEditor);`
- L172 _public prototype_ `static const UWidgetEditingProjectSettings* GetRelevantSettings(TWeakPtr<FWidgetBlueprintEditor> CurrentEditor);`
- L174 _public prototype_ `static UWidgetBlueprint* GetWidgetBlueprintFromWidget(const UWidget* Widget);`
- L176 _public prototype_ `static TSet<UWidget*> ResolveWidgetTemplates(const TSet<FWidgetReference>& Widgets);`
- L180 _private prototype_ `static FString CopyWidgetsInternal(UWidgetBlueprint* BP, TSet<FWidgetReference> Widgets);`
- L182 _private prototype_ `static TArray<UWidget*> PasteWidgetsInternal(TSharedRef<FWidgetBlueprintEditor> BlueprintEditor, UWidgetBlueprint* BP, const FString& TextToImport, FWidgetReference ParentWidget, FName SlotName, FVector2D PasteLocation, bool bForceSibling, bool& TransactionSuccesful);`
- L184 _private prototype_ `static bool DisplayPasteWarningAndEarlyExit();`
- L186 _private prototype_ `static void ExecuteOpenSelectedWidgetsForEdit( TSet<FWidgetReference> SelectedWidgets );`
- L188 _private prototype_ `static bool FindAndRemoveNamedSlotContent(UWidget* WidgetTemplate, UWidgetTree* WidgetTree);`
- L190 _private prototype_ `static bool CanOpenSelectedWidgetsForEdit( TSet<FWidgetReference> SelectedWidgets );`
- L192 _private prototype_ `static void BuildWrapWithMenu(FMenuBuilder& Menu, TSharedRef<FWidgetBlueprintEditor> BlueprintEditor, UWidgetBlueprint* BP, TSet<FWidgetReference> Widgets);`
- L194 _private prototype_ `static void BuildReplaceWithMenu(FMenuBuilder& Menu, TSharedRef<FWidgetBlueprintEditor> BlueprintEditor, UWidgetBlueprint* BP, TSet<FWidgetReference> Widgets);`
- L196 _private prototype_ `static void ReplaceWidgetWithSelectedTemplate(TSharedRef<FWidgetBlueprintEditor> BlueprintEditor, UWidgetBlueprint* BP, FWidgetReference Widget);`
- L198 _private prototype_ `static bool CanBeReplacedWithTemplate(TSharedRef<FWidgetBlueprintEditor> BlueprintEditor, UWidgetBlueprint* BP, FWidgetReference Widget);`
- L200 _private prototype_ `static FString FindNextValidName(UWidgetTree* WidgetTree, const FString& Name);`
- L202 _private prototype_ `static void FindUsedVariablesForWidgets(const TSet<UWidget*>& Widgets, const UWidgetBlueprint* BP, TArray<UWidget*>& UsedVariables, TArray<FText>& WidgetNames, bool bIncludeVariablesOnChildren);`
- L204 _private prototype_ `static bool ShouldContinueDeleteOperation(UWidgetBlueprint* BP, const TArray<FText>& WidgetNames);`
- L206 _private prototype_ `static bool ShouldContinueReplaceOperation(UWidgetBlueprint* BP, const TArray<FText>& WidgetNames);`
- L208 _private prototype_ `static TOptional<FWidgetThumbnailProperties> DrawSWidgetInRenderTargetInternal(UUserWidget* WidgetInstance, FRenderTarget* RenderTarget2D, UTextureRenderTarget2D* TextureRenderTarget,FVector2D ThumbnailSize, bool bIsForThumbnail, TOptional<FVector2D> ThumbnailCustomSize, EThumbnailPreviewSizeMode ThumbnailSizeMode);`
- L210 _private prototype_ `static bool IsDesiredFocusWidget(TSharedRef<FWidgetBlueprintEditor> BlueprintEditor, UWidget* Widget);`
- L211 _private prototype_ `static bool IsDesiredFocusWidget(UWidgetBlueprint* Blueprint, UWidget* Widget);`
- L213 _private prototype_ `static FWidgetObjectTextFactory ProcessImportedText(UWidgetBlueprint* BP, const FString& TextToImport, UPackage*& TempPackage);`

#### struct `FWidgetBlueprintEditorUtils::FWidgetThumbnailProperties`  
`struct FWidgetThumbnailProperties`  
_L33-37_
- L35 _public member_ `FVector2D ScaledSize;`
- L36 _public member_ `FVector2D Offset;`

#### struct `FWidgetBlueprintEditorUtils::FCreateWidgetFromBlueprintParams`  
`struct FCreateWidgetFromBlueprintParams`  
_L39-43_
- L41 _public member_ `EWidgetDesignFlags FlagsToApply;`
- L42 _public member_ `ULocalPlayer* LocalPlayer = nullptr;` — Optionally specify if available

#### enum `FWidgetBlueprintEditorUtils::EReplaceWidgetNamingMethod`  
`enum class EReplaceWidgetNamingMethod`  
_L61-72_
- L65 _public enumerator_ `MaintainNameAndReferences` — Will give the new widget the same name as the replaced widget if the widget classes are compatible If it's using a generated name, the new generated name will be used and FBlueprintEditorUtils::ReplaceVariableReferences will be called
- L68 _public enumerator_ `MaintainNameAndReferencesForUnmatchingClass` — Same as MaintainNameAndReferences but doesn't check for matching classes or generated names
- L71 _public enumerator_ `UseNewGeneratedName` — Will use the new widget's generated name and not make an effort to maintain references

#### enum `FWidgetBlueprintEditorUtils::EDeleteWidgetWarningType`  
`enum class EDeleteWidgetWarningType`  
_L78-84_
- L81 _public enumerator_ `WarnAndAskUser` — If the widget being deleted is referenced in the graph, ask the user if the deletion should continue
- L83 _public enumerator_ `DeleteSilently` — Don't notify the user at all and delete the widget even if it is referenced

#### struct `FWidgetBlueprintEditorUtils::FUsableWidgetClassResult`  
`struct FUsableWidgetClassResult`  
_L110-114_
- L112 _public member_ `const UClass* NativeParentClass = nullptr;`
- L113 _public member_ `EClassFlags AssetClassFlags = EClassFlags::CLASS_None;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API UMGEDITOR_API`

### `Source/Editor/UMGEditor/Public/WidgetBlueprintExtension.h` (Public)


#### class `UWidgetBlueprintExtension`  
`class UWidgetBlueprintExtension : public UBlueprintExtension`  
_L20-159_
- reflection: `UCLASS(MinimalAPI, Within=WidgetBlueprint)`
- inherits: `UBlueprintExtension`
- desc: Extension that allows per-system data to be held on the widget blueprint, and per-system logic to be executed during compilation
- L30 _public function_ `template<typename ExtensionType> static ExtensionType* RequestExtension(UWidgetBlueprint* InWidgetBlueprint)` — Request an WidgetBlueprintExtension for an WidgetBlueprint. @note It is illegal to perform this operation once compilation has commenced, use GetExtension instead.
- L39 _public prototype_ `static UWidgetBlueprintExtension* RequestExtension(UWidgetBlueprint* InWidgetBlueprint, TSubclassOf<UWidgetBlueprintExtension> InExtensionType);` — Request an WidgetBlueprintExtension for an WidgetBlueprint. @note It is illegal to perform this operation once compilation has commenced, use GetExtension instead.
- L43 _public function_ `template<typename ExtensionType> static ExtensionType* GetExtension(const UWidgetBlueprint* InWidgetBlueprint)` — Get an already-requested extension for an WidgetBlueprint.
- L49 _public prototype_ `static UWidgetBlueprintExtension* GetExtension(const UWidgetBlueprint* InWidgetBlueprint, TSubclassOf<UWidgetBlueprintExtension> InExtensionType);` — Get an already-requested extension for an WidgetBlueprint.
- L52 _public prototype_ `static TArray<UWidgetBlueprintExtension*> GetExtensions(const UWidgetBlueprint* InWidgetBlueprint);` — Get all subsystems currently present on an WidgetBlueprint
- L56 _public function_ `template<typename Predicate> static void ForEachExtension(const UWidgetBlueprint* InWidgetBlueprint, Predicate Pred)` — Iterate over all registered WidgetBlueprintExtensions in an WidgetBlueprint
- L68 _public prototype_ `UWidgetBlueprint* GetWidgetBlueprint() const;` — Get the WidgetBlueprint that hosts this extension
- L71 _public function_ `virtual void FindDiffs(const UWidgetBlueprint* OwningBlueprint, const UWidgetBlueprint* OtherBlueprint, FDiffResults& Results) const`
- L81 _public function_ `virtual void GatherWidgetMemberReferences(FName WidgetVariableName, const UClass* WidgetClass, TSet<FName>& OutReferencedProperties, TSet<FName>& OutReferencedFunctions) const` — Report references that this extension is holding into a specific widget's class members. @param WidgetVariableName       Variable name of the widget on the owning blueprint. @param WidgetClass              Current class of the widget (use to resolve member kind). @param OutReferencedProperties  Property/delegate names on WidgetClass that this extension references. @param OutReferencedFunctions   Function names on WidgetClass that this extension references.
- L89 _protected function_ `virtual void HandleBeginCompilation(FWidgetBlueprintCompilerContext& InCreationContext)` — Override point called when a compiler context is created for the WidgetBlueprint @param	InCreationContext	The compiler context for the current compilation
- L91 _protected function_ `virtual void HandleCreateFunctionList(const FWidgetBlueprintCompilerContext::FCreateFunctionContext& InCreationContext)`
- L92 _protected function_ `virtual void HandleCleanAndSanitizeClass(UWidgetBlueprintGeneratedClass* ClassToClean, UObject* OldCDO)`
- L93 _protected function_ `virtual TArray<UObject*> HandleSaveSubObjectsFromCleanAndSanitizeClass(UWidgetBlueprintGeneratedClass* ClassToClean)`
- L94 _protected function_ `virtual void HandlePopulateGeneratedVariables(const FWidgetBlueprintCompilerContext::FPopulateGeneratedVariablesContext& Context)`
- L95 _protected function_ `virtual void HandleCreateClassVariablesFromBlueprint(const FWidgetBlueprintCompilerContext::FCreateVariableContext& Context)`
- L96 _protected function_ `virtual void HandleCopyTermDefaultsToDefaultObject(UObject* DefaultObject)`
- L97 _protected function_ `virtual void HandleFinishCompilingClass(UWidgetBlueprintGeneratedClass* Class)`
- L98 _protected function_ `virtual bool HandleValidateGeneratedClass(UWidgetBlueprintGeneratedClass* Class)`
- L104 _protected function_ `virtual void HandleEndCompilation()` — Override point called when a compiler context is destroyed for the WidgetBlueprint. Can be used to clean up resources.
- L110 _private function_ `void BeginCompilation(FWidgetBlueprintCompilerContext& InCreationContext)`
- L115 _private function_ `void CreateFunctionList(const FWidgetBlueprintCompilerContext::FCreateFunctionContext& InCreationContext)`
- L120 _private function_ `void CleanAndSanitizeClass(UWidgetBlueprintGeneratedClass* ClassToClean, UObject* OldCDO)`
- L125 _private function_ `TArray<UObject*> SaveSubObjectsFromCleanAndSanitizeClass(UWidgetBlueprintGeneratedClass* ClassToClean)`
- L130 _private function_ `void PopulateGeneratedVariables(const FWidgetBlueprintCompilerContext::FPopulateGeneratedVariablesContext& Context)`
- L135 _private function_ `void CreateClassVariablesFromBlueprint(const FWidgetBlueprintCompilerContext::FCreateVariableContext& Context)`
- L140 _private function_ `void CopyTermDefaultsToDefaultObject(UObject* DefaultObject)`
- L145 _private function_ `void FinishCompilingClass(UWidgetBlueprintGeneratedClass* Class)`
- L150 _private function_ `bool ValidateGeneratedClass(UWidgetBlueprintGeneratedClass* Class)`
- L155 _private function_ `void EndCompilation()`

#### Free symbols / members of external scopes

- L16 _macro_ `#define UE_API UMGEDITOR_API`

### `Source/Editor/UMGEditor/Public/WidgetBlueprintOperationUtils.h` (Public)


#### class `FWidgetBlueprintOperationUtils`  
`class FWidgetBlueprintOperationUtils`  
_L21-217_
- desc: Utility functions for programmatic Widget Blueprint manipulation.
- L41 _public prototype_ `static UWidgetBlueprint* CreateWidgetBlueprint(UObject* InParent, FName Name, EBlueprintType BlueprintType, TSubclassOf<UUserWidget> ParentClass, TSubclassOf<UWidget> RootWidgetClass = nullptr, FName CallingContext = NAME_None, bool bRegisterAndCompile = true);` — Lower-level overload that creates a Widget Blueprint directly into InParent with the given Name. Intended for asset factories that have already resolved the package and name. @param InParent            Package or outer object to create the blueprint in. @param Name                Name for the blueprint UObject. @param BlueprintType       Type of blueprint (typically BPTYPE_Normal). @param ParentClass         The parent UUserWidget class. @param RootWidgetClass     Optional root panel widget class. Pass null to leave the root unset. @param CallingContext      Opaque context name passed to FKismetEditorUtilities (used for analytics). @param bRegisterAndCompile When true (default), marks the package dirty, registers missing GUIDs, compiles the blueprint, and notifies the asset registry. Pass false when the calling framework (e.g. UFactory) already handles these steps.
- L49 _public prototype_ `static bool AddWidget(UWidgetBlueprint* WidgetBlueprint, UWidget* NewWidget, UWidget* ParentWidget, int32 ChildIndex, FText& OutErrorMessage);` — Adds a widget to the blueprint's widget tree. - If ParentWidget is null and the tree has no root, sets the new widget as the root. - Otherwise adds to ParentWidget at ChildIndex. Returns true on success, false on failure (OutErrorMessage will contain details).
- L52 _public prototype_ `static bool CanAddToParent(UWidgetBlueprint* WidgetBlueprint, UWidget* ParentWidget, FText& OutErrorMessage);` — Returns true if a widget can be added to the specified parent in the given blueprint.
- L55 _public prototype_ `static UWidget* CreateWidgetFromAsset(UWidgetBlueprint* WidgetBlueprint, const FAssetData& AssetData, UWidgetTree* RootWidgetTree, FText& OutErrorMessage);` — Creates a widget instance based on the class of the asset.
- L58 _public prototype_ `static bool IsParentChildCycleFree(UWidgetBlueprint* WidgetBlueprint, UWidget* ChildWidget, UWidget* ParentWidget);` — Returns true if making ChildWidget a child of ParentWidget would not create a cycle in the widget hierarchy.
- L64 _public prototype_ `static bool MoveWidget(UWidgetBlueprint* WidgetBlueprint, UWidget* Widget, UPanelWidget* NewParent, int32 ChildIndex, FText& OutErrorMessage);` — Moves a widget to a new parent panel at the specified child index (-1 appends). Returns true on success.
- L70 _public prototype_ `static bool RemoveWidget(UWidgetBlueprint* WidgetBlueprint, UWidget* Widget, FText& OutErrorMessage);` — Removes a widget and all of its children from the blueprint's widget tree. Returns true if the widget was found and removed.
- L76 _public prototype_ `static bool RenameWidget(UWidgetBlueprint* WidgetBlueprint, UWidget* Widget, const FString& NewDisplayName);` — Renames a widget in the blueprint. Returns true on success.
- L79 _public prototype_ `static bool VerifyWidgetRename(UWidgetBlueprint* WidgetBlueprint, UWidget* TemplateWidget, const FText& NewName, FText& OutErrorMessage);` — Validates that a widget can be renamed to NewName. Returns true if the rename is valid; fills OutErrorMessage on failure.
- L82 _public prototype_ `static void ToggleWidgetAsVariable(UWidgetBlueprint* WidgetBlueprint, UWidget* Widget, bool bIsVariable, bool bMarkBlueprintModified = true);` — Sets the bIsVariable flag on a widget.
- L88 _public prototype_ `static bool BindToEventProperty(UWidgetBlueprint* WidgetBlueprint, FName EventName, FName PropertyName, UClass* PropertyClass, bool bShouldJumpToNode, FText& OutErrorMessage);` — Adds a Blueprint event handler graph node bound to a widget's multicast delegate event, equivalent to clicking an event button on a widget variable in the Details panel.
- L109 _public prototype_ `static bool ReplaceWidgetWithTemplate(UWidgetBlueprint* WidgetBlueprint, UWidget* WidgetToReplace, TSubclassOf<UWidget> TemplateClass, FText& OutErrorMessage);` — Replaces a widget instance in the blueprint's widget tree with a new instance created from a different template widget class. Performs hard validations (params, widget identity in the tree, circular blueprint reference, BindWidget contract on the parent class chain, panel rules and child-capacity for panel-to-panel swaps) and aborts without mutating on failure. On success, references to compatible members on the new class are retargeted; references to members that don't exist on the new class are left pointing at the old class so the user sees them as orphaned in the graph. Panel handling: if WidgetToReplace is a panel with children, TemplateClass must also be a panel widget that can hold every existing child. Slot properties are preserved across the move where the new slot accepts them. @param WidgetBlueprint    The widget blueprint containing the widget to replace. @param WidgetToReplace    The widget instance to replace (must be in WidgetBlueprint's tree). @param TemplateClass      The widget class to create the replacement from. @param OutErrorMessage    Filled on failure with a description of what went wrong. @return true on success, false on hard failure (no side effects on failure).
- L115 _public prototype_ `static void RemoveTransientWidgetFromTree(UWidgetBlueprint* WidgetBlueprint, UWidget* Widget);` — Removes a widget instance that was freshly added to the tree. Use RemoveWidget for any delete operations after a widget has been added. RemoveTransientWidgetFromTree assumes the widget has no references. RemoveWidget is a complete version that cleans all references.
- L121 _public prototype_ `static UWidget* AddUIComponent(UWidgetBlueprint* WidgetBlueprint, UClass* ComponentClass, FName WidgetName, FText& OutErrorMessage);` — Adds a UI component of the given class to the named widget. Returns the UWidget the component was added to.
- L127 _public prototype_ `static bool RemoveUIComponent(UWidgetBlueprint* WidgetBlueprint, UClass* ComponentClass, FName WidgetName, FText& OutErrorMessage);` — Removes a UI component of the given class from the named widget. Returns true on success.
- L133 _public prototype_ `static bool MoveUIComponent(UWidgetBlueprint* WidgetBlueprint, UClass* ComponentClassToMove, UClass* RelativeToComponentClass, FName WidgetName, bool bMoveAfter, FText& OutErrorMessage);` — Moves a UI component before or after another component on the same widget. Returns true on success.
- L142 _public prototype_ `static bool DoesPropertyExistInClass(UClass* Class, FProperty* Property, FText& OutError);` — Returns true if Class declares (or inherits) a property with Property's name and a compatible type. On failure OutError is populated with the reason ("no member of that name on the new class" vs "name exists but the type is incompatible"). On success OutError is left untouched. Used both internally by FixupWidgetBlueprintReferences and by higher layers (e.g. UMG toolset) that need to audit member compatibility ahead of a widget replacement.
- L150 _public prototype_ `static bool DoesFunctionExistInClass(UClass* Class, UFunction* Function, FText& OutError);` — Returns true if Class declares (or inherits) a function with Function's name and a signature compatible with Function. On failure OutError is populated with the reason ("no function of that name on the new class" vs "name exists but the signature is incompatible"). On success OutError is left untouched.
- L156 _public prototype_ `static TArray<UWidget*> WrapWidgets(UWidgetBlueprint* BP, TArray<UWidget*> Widgets, UClass* WidgetClass);` — Wraps selected widgets in a new parent widget of the specified class. Returns the newly created wrapper widget(s).
- L167 _public prototype_ `static bool ReplaceWidgetWithChild(UWidgetBlueprint* WidgetBlueprint, UWidget* WidgetToReplace, FText& OutErrorMessage);` — Replaces a single-child panel widget with its child, preserving named-slot host wiring and parent linkage. The widget to replace must be a UPanelWidget with exactly one child. @param WidgetBlueprint    The widget blueprint containing the panel widget. @param WidgetToReplace    The panel widget (must be a UPanelWidget with exactly one child and in WidgetBlueprint's tree). @param OutErrorMessage    Filled on failure with a description of what went wrong. @return true on success, false if validation failed (no side effects on failure).
- L183 _public prototype_ `static bool ReplaceWidgetWithNamedSlot(UWidgetBlueprint* WidgetBlueprint, UWidget* WidgetToReplace, FName NamedSlot, FWidgetBlueprintEditorUtils::EDeleteWidgetWarningType DeleteWarningType, FText& OutErrorMessage);` — Replaces a host widget with the content of one of its named slots, preserving parent linkage and root-widget wiring. Validates inputs and aborts without side effects on failure. @param WidgetBlueprint    The widget blueprint containing the host widget. @param WidgetToReplace    The host widget (must implement INamedSlotInterface and be in WidgetBlueprint's tree). @param NamedSlot          The slot whose content will replace WidgetToReplace. @param OutErrorMessage    Filled on failure with a description of what went wrong. @param DeleteWarningType  Controls whether the user is prompted when the replaced host is referenced as a Blueprint variable. Defaults to DeleteSilently (suitable for headless / toolset callers); the editor menu path passes WarnAndAskUser. @return true on success, false if validation failed (no side effects on failure).
- L198 _public prototype_ `static void WalkWidgetTree( const UWidgetBlueprint* WidgetBlueprint, const UWidget* StartWidget, int32 MaxDepth, TFunctionRef<void(const UWidget* Widget, int32 Depth, FName SlotName)> Visitor);` — Depth-first walk of a widget tree. Calls Visitor once per widget in order. Handles panel children and named slot content. Cycle-safe. @param WidgetBlueprint  Blueprint to traverse. @param StartWidget      nullptr = walk from root widget. @param MaxDepth         -1 = no limit; 0 = StartWidget only; N = N levels of descent. @param Visitor          Called per widget: (Widget, Depth, SlotName). Depth is 0 at StartWidget. SlotName is NAME_None for panel children; the named slot name for named slot content.
- L209 _public prototype_ `static int32 ComputeWidgetTreeDepth( const UWidgetBlueprint* WidgetBlueprint, const UWidget* StartWidget = nullptr);` — Returns the maximum depth of the widget tree from StartWidget. A leaf = 0; a node with one level of children = 1. Returns -1 if WidgetBlueprint or its WidgetTree is null.
- L214 _private prototype_ `static void FixupWidgetBlueprintReferences(UWidgetBlueprint* WidgetBlueprint, UClass* OldClass, UClass* NewWidgetClass, FName VariableName);`
- L216 _private prototype_ `static bool ReplaceWidgetsWithTemplateClass(UWidgetBlueprint* BP, TSet<UWidget*> Widgets, TSharedPtr<FWidgetTemplateClass> TemplateClass, FWidgetBlueprintEditorUtils::EReplaceWidgetNamingMethod NewWidgetNamingMethod);`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API UMGEDITOR_API`

### `Source/Editor/UMGEditor/Public/WidgetBlueprintThumbnailRenderer.h` (Public)


#### class `UWidgetBlueprintThumbnailRenderer`  
`class UWidgetBlueprintThumbnailRenderer : public UDefaultSizedThumbnailRenderer`  
_L17-40_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UDefaultSizedThumbnailRenderer`
- L21 _private prototype_ `UWidgetBlueprintThumbnailRenderer();`
- L22 _private prototype_ `virtual ~UWidgetBlueprintThumbnailRenderer();`
- L25 _private prototype_ `virtual bool CanVisualizeAsset(UObject* Object) override;`
- L26 _private prototype_ `virtual void Draw(UObject* Object, int32 X, int32 Y, uint32 Width, uint32 Height, FRenderTarget* RenderTarget, FCanvas* Canvas, bool bAdditionalViewFamily) override;`
- L27 _private prototype_ `virtual EThumbnailRenderFrequency GetThumbnailRenderFrequency(UObject* Object) const override;`
- L31 _private prototype_ `void OnBlueprintUnloaded(UBlueprint* Blueprint);`
- L39 _private member_ `TUniquePtr<FWidgetBlueprintThumbnailPool, FWidgetBlueprintThumbnailPoolDeleter> ThumbnailPool;`

#### struct `UWidgetBlueprintThumbnailRenderer::FWidgetBlueprintThumbnailPoolDeleter`  
`struct FWidgetBlueprintThumbnailPoolDeleter`  
_L34-37_
- L36 _public prototype_ `void operator()(FWidgetBlueprintThumbnailPool* Pointer);`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API UMGEDITOR_API`

### `Source/Editor/UMGEditor/Public/WidgetBlueprintToolMenuContext.h` (Public)


#### class `UWidgetBlueprintToolMenuContext`  
`class UWidgetBlueprintToolMenuContext : public UObject`  
_L12-18_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- L17 _public member_ `TWeakPtr<FWidgetBlueprintEditor> WidgetBlueprintEditor;`

### `Source/Editor/UMGEditor/Public/WidgetCompilerRule.h` (Public)


#### class `UWidgetCompilerRule`  
`class UWidgetCompilerRule : public UObject`  
_L22-29_
- reflection: `UCLASS(MinimalAPI, Abstract)`
- inherits: `UObject`
- L26 _public prototype_ `UWidgetCompilerRule();`
- L28 _public prototype_ `virtual void ExecuteRule(UWidgetBlueprint* WidgetBlueprint, FCompilerResultsLog& MessageLog);`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API UMGEDITOR_API`

### `Source/Editor/UMGEditor/Public/WidgetEditingProjectSettings.h` (Public)


#### struct `FDebugResolution`  
`struct FDebugResolution`  
_L23-38_
- reflection: `USTRUCT()`
- L28 _public member_ `int32 Width = 0;` — `UPROPERTY(EditAnywhere, Category = Resolution)`
- L31 _public member_ `int32 Height = 0;` — `UPROPERTY(EditAnywhere, Category = Resolution)`
- L34 _public member_ `FString Description;` — `UPROPERTY(EditAnywhere, Category=Resolution)`
- L37 _public member_ `FLinearColor Color = FLinearColor::Black;` — `UPROPERTY(EditAnywhere, Category = Resolution)`

#### enum `EPropertyBindingPermissionLevel`  
`enum class EPropertyBindingPermissionLevel : uint8`  
_L42-59_
- reflection: `UENUM()`
- desc: Controls the level of support you want to have for widget property binding.
- L45 _public enumerator_ `Allow` — Freely allow the use of property binding.
- L50 _public enumerator_ `Prevent` — Prevent any new property binding, will still allow you to edit widgets with property binding, but the buttons will be missing on all existing widgets that don't have bindings.
- L54 _public enumerator_ `PreventAndWarn` — Prevent any new property binding, and warn when compiling any existing bindings.
- L58 _public enumerator_ `PreventAndError` — Prevent any new property binding, and error when compiling any existing bindings.

#### struct `FWidgetCompilerOptions`  
`struct FWidgetCompilerOptions`  
_L62-95_
- reflection: `USTRUCT()`
- L72 _public member_ `bool bAllowBlueprintTick = true;` — `UPROPERTY(EditAnywhere, Category = Compiler)` — If you disable this, these widgets these compiler options apply to will not be allowed to implement Tick.
- L78 _public member_ `bool bAllowBlueprintPaint = true;` — `UPROPERTY(EditAnywhere, Category = Compiler)` — If you disable this, these widgets these compiler options apply to will not be allowed to implement Paint.
- L84 _public member_ `EPropertyBindingPermissionLevel PropertyBindingRule = EPropertyBindingPermissionLevel::Allow;` — `UPROPERTY(EditAnywhere, Category = Compiler)` — Controls if you allow property bindings in widgets.  They can have a large performance impact if used.
- L90 _public member_ `TArray<TSoftClassPtr<UWidgetCompilerRule>> Rules;` — `UPROPERTY(EditAnywhere, Category = Compiler)` — Custom rules.

#### struct `FDirectoryWidgetCompilerOptions`  
`struct FDirectoryWidgetCompilerOptions`  
_L100-119_
- reflection: `USTRUCT()`
- L108 _public member_ `FDirectoryPath Directory;` — `UPROPERTY(EditAnywhere, Category = Compiler, meta = (ContentDir))` — The directory to limit the rules effects to.
- L113 _public member_ `TArray<TSoftObjectPtr<UWidgetBlueprint>> IgnoredWidgets;` — `UPROPERTY(EditAnywhere, Category = Compiler)` — These widgets are ignored, and they will use the next most applicable directory to determine their rules.
- L118 _public member_ `FWidgetCompilerOptions Options;` — `UPROPERTY(EditAnywhere, Category = Compiler)` — The directory specific compiler options for these widgets.

#### class `UWidgetEditingProjectSettings`  
`class UWidgetEditingProjectSettings : public UDeveloperSettings`  
_L125-278_
- reflection: `UCLASS(MinimalAPI, Abstract, config=Editor, defaultconfig)`
- inherits: `UDeveloperSettings`
- desc: Implements the settings for the UMG Editor Project Settings
- L130 _public prototype_ `UWidgetEditingProjectSettings();`
- L132 _public prototype_ `virtual void PostInitProperties() override;`
- L136 _public member_ `FWidgetCompilerOptions DefaultCompilerOptions;` — `UPROPERTY(EditAnywhere, config, Category = "Compiler")`
- L140 _protected member_ `TArray<FDirectoryWidgetCompilerOptions> DirectoryCompilerOptions;` — `UPROPERTY(EditAnywhere, config, Category = "Compiler")`
- L145 _public member_ `bool bShowWidgetsFromEngineContent;` — `UPROPERTY(EditAnywhere, config, Category="Class Filtering")`
- L148 _public member_ `bool bShowWidgetsFromDeveloperContent;` — `UPROPERTY(EditAnywhere, config, Category="Class Filtering")`
- L151 _public member_ `TArray<FString> CategoriesToHide;` — `UPROPERTY(EditAnywhere, config, AdvancedDisplay, Category="Class Filtering")`
- L154 _public member_ `TArray<FSoftClassPath> WidgetClassesToHide;` — `UPROPERTY(EditAnywhere, config, Category = "Class Filtering", meta = (MetaClass = "/Script/UMG.Widget"))`
- L160 _public member_ `bool bUseWidgetTemplateSelector;` — `UPROPERTY(EditAnywhere, config, Category = "Designer")` — Enables a dialog that lets you select a root widget before creating a widget blueprint
- L164 _public member_ `TArray<TSoftClassPtr<UPanelWidget>> CommonRootWidgetClasses;` — `UPROPERTY(EditAnywhere, config, Category = "Designer", meta = (EditCondition = "bUseWidgetTemplateSelector"))` — This list populates the common class section of the root widget selection dialog
- L168 _public member_ `TSubclassOf<UPanelWidget> DefaultRootWidget;` — `UPROPERTY(EditAnywhere, config, Category = "Designer")` — The panel widget to place at the root of all newly constructed widget blueprints. Can be empty.
- L172 _public member_ `bool bUseEditorConfigPaletteFiltering;` — `UPROPERTY(EditAnywhere, config, Category = "Designer")` — Set true to filter all categories and widgets out in the palette, selectively enabling them later via permission lists.
- L176 _public member_ `bool bUseUserWidgetParentClassViewerSelector;` — `UPROPERTY(EditAnywhere, config, Category = "Designer")` — Enables a dialog that lets you select the parent class in a tree view.
- L180 _public member_ `bool bUseUserWidgetParentDefaultClassViewerSelector;` — `UPROPERTY(EditAnywhere, config, Category = "Designer")` — Enables a dialog that lets you select the parent class in a default view.
- L184 _public member_ `bool bEnableMakeVariable;` — `UPROPERTY(EditAnywhere, Category = "Designer|Window")` — Set true to enable the Is Variable checkbox in the UMG editor DetailView.
- L188 _public member_ `bool bEnableWidgetAnimationEditor;` — `UPROPERTY(EditAnywhere, Category = "Designer|Window")` — Set true to hide widget animation related elements in the UMG editor.
- L192 _public member_ `bool bEnablePaletteWindow;` — `UPROPERTY(EditAnywhere, Category = "Designer|Window")` — Set true to enabled the Palette window in the UMG editor.
- L196 _public member_ `bool bEnableLibraryWindow;` — `UPROPERTY(EditAnywhere, Category = "Designer|Window")` — Set true to enabled the Library window in the UMG editor.
- L200 _public member_ `bool bEnableHierarchyWindow;` — `UPROPERTY(EditAnywhere, Category = "Designer|Window")` — Set true to enabled the Widget Hierarchy window in the UMG editor.
- L204 _public member_ `bool bEnableBindWidgetWindow;` — `UPROPERTY(EditAnywhere, Category = "Designer|Window")` — Set true to enabled the Bind Widget window in the UMG editor.
- L208 _public member_ `bool bEnableNavigationSimulationWindow;` — `UPROPERTY(EditAnywhere, Category = "Designer|Window")` — Set true to enabled the Navigation Simulation window in the UMG editor.
- L212 _public member_ `bool bCanCallInitializedWithoutPlayerContext;` — `UPROPERTY(EditAnywhere, Category = "Class Settings")` — The default value of bCanCallInitializedWithoutPlayerContext.
- L215 _public member_ `bool bEnableUIComponentsProperty;` — `UPROPERTY(EditAnywhere, Category = "Class Settings")`
- L218 _public member_ `bool bUseNewBindingFromDetailsView = false;` — Use the new version of the binding in the details view.
- L221 _public member_ `bool bUseCompactLinkButtonInExtension = false;` — Use compact link button (just display the link) or complete one (with info about the current binding in the extension part of the detail view.
- L225 _public member_ `int32 DefaultWidgetAnimationFrameRate;` — `UPROPERTY(EditAnywhere, config, Category = "Designer|Animation", meta = (ClampMin = "1", UIMin = "1"))` — Set the default widget animation display frame rate's numerator.
- L232 _public member_ `TArray<TSoftClassPtr<UUserWidget>> FavoriteWidgetParentClasses;` — `UPROPERTY(EditAnywhere, config, Category = Designer, meta = (AllowAbstract = "", EditCondition="bUseUserWidgetParentDefaultClassViewerSelector"))` — The list of parent classes to choose from for newly constructed widget blueprints. The classes must have empty widget hierarchies.
- L235 _public member_ `TArray<FDebugResolution> DebugResolutions;` — `UPROPERTY(EditAnywhere, config, Category=Designer)`
- L237 _public prototype_ `bool CompilerOption_AllowBlueprintTick(const class UWidgetBlueprint* WidgetBlueprint) const;`
- L238 _public prototype_ `bool CompilerOption_AllowBlueprintPaint(const class UWidgetBlueprint* WidgetBlueprint) const;`
- L239 _public prototype_ `EPropertyBindingPermissionLevel CompilerOption_PropertyBindingRule(const class UWidgetBlueprint* WidgetBlueprint) const;`
- L240 _public prototype_ `TArray<UWidgetCompilerRule*> CompilerOption_Rules(const class UWidgetBlueprint* WidgetBlueprint) const;`
- L243 _public prototype_ `FNamePermissionList& GetAllowedPaletteCategories();` — Get the permission list that controls which categories are exposed in config palette filtering
- L244 _public prototype_ `const FNamePermissionList& GetAllowedPaletteCategories() const;`
- L247 _public prototype_ `FPathPermissionList& GetAllowedPaletteWidgets();` — Get the permission list that controls which widgets are exposed in config palette filtering
- L248 _public prototype_ `const FPathPermissionList& GetAllowedPaletteWidgets() const;`
- L252 _private function_ `template<typename ReturnType, typename T> ReturnType GetFirstCompilerOption(const class UWidgetBlueprint* WidgetBlueprint, T FWidgetCompilerOptions::* OptionMember, ReturnType bDefaultValue) const`
- L262 _private prototype_ `void GetCompilerOptionsForWidget(const class UWidgetBlueprint* WidgetBlueprint, TFunctionRef<bool(const FWidgetCompilerOptions&)> Operator) const;`
- L265 _protected prototype_ `virtual void PerformUpgradeStepForVersion(int32 ForVersion);`
- L268 _protected member_ `int32 Version;` — `UPROPERTY(config)`
- L271 _protected member_ `int32 CurrentVersion;` — This one is unsaved, we compare it on post init to see if the save matches real
- L274 _protected member_ `FNamePermissionList AllowedPaletteCategories;` — Palette categories to allow all widgets within when using permission list palette filtering
- L277 _protected member_ `FPathPermissionList AllowedPaletteWidgets;` — Individual widgets to always allow when using permission list palette filtering, regardless of category

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API UMGEDITOR_API`
- L255 _function_ `GetCompilerOptionsForWidget(WidgetBlueprint, [&bValue, OptionMember](const FWidgetCompilerOptions& Options) { bValue = Options.*OptionMember; return true; });` (scope `UWidgetEditingProjectSettings::GetFirstCompilerOption`)

### `Source/Editor/UMGEditor/Public/WidgetReference.h` (Public)


#### struct `FWidgetHandle`  
`struct FWidgetHandle`  
_L13-22_
- L19 _private prototype_ `FWidgetHandle(UWidget* Widget);`
- L21 _private member_ `TWeakObjectPtr<UWidget> Widget;`

#### struct `FWidgetReference`  
`struct FWidgetReference`  
_L28-83_
- desc: The Widget reference is a useful way to hold onto the selection in a way that allows for up to date access to the current preview object. Because the designer could end up rebuilding the preview, it's best to hold onto an FWidgetReference.
- L33 _public prototype_ `FWidgetReference();`
- L36 _public prototype_ `bool IsValid() const;` — @returns true if both the template and the preview pointers are valid.
- L39 _public prototype_ `UWidget* GetTemplate() const;` — @returns The template widget.  This is the widget that is serialized to disk
- L42 _public prototype_ `UWidget* GetPreview() const;` — @returns the preview widget.  This is the transient representation of the template.  Constantly being destroyed and recreated.  Do not cache this pointer.
- L45 _public function_ `TSharedPtr<SWidget> GetPreviewSlate() const` — @returns the preview slate widget.  This is the transient representation of the template.  Constantly being destroyed and recreated.  Do not cache this pointer.
- L55 _public function_ `TSharedPtr<FWidgetBlueprintEditor> GetWidgetEditor() const`
- L58 _public function_ `bool operator==( const FWidgetReference& Other ) const` — Checks if widget reference is the same as another widget reference, based on the template pointers.
- L69 _public function_ `bool operator!=( const FWidgetReference& Other ) const` — Checks if widget reference is the different from another widget reference, based on the template pointers.
- L75 _private prototype_ `FWidgetReference(TSharedPtr<FWidgetBlueprintEditor> WidgetEditor, TSharedPtr< FWidgetHandle > TemplateHandle);`
- L77 _private prototype_ `void OnObjectsReplaced(const TMap<UObject*, UObject*>& ReplacementMap);`
- L80 _private member_ `TWeakPtr<FWidgetBlueprintEditor> WidgetEditor;`
- L82 _private member_ `TSharedPtr< FWidgetHandle > TemplateHandle;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API UMGEDITOR_API`
- L85 _function_ `inline uint32 GetTypeHash(const struct FWidgetReference& WidgetRef)`

### `Source/Editor/UMGEditor/Public/WidgetTemplate.h` (Public)


#### class `FWidgetTemplate`  
`class FWidgetTemplate : public TSharedFromThis<FWidgetTemplate>`  
_L25-57_
- inherits: `TSharedFromThis<FWidgetTemplate>`
- desc: The widget template represents a widget or a set of widgets to create and spawn into the widget tree. More complicated defaults could be created by deriving from this class and registering new templates with the module.
- L29 _public prototype_ `FWidgetTemplate();` — Constructor
- L30 _public prototype_ `virtual ~FWidgetTemplate() = default;`
- L33 _public prototype_ `virtual FText GetCategory() const = 0;` — The category this template fits into.
- L36 _public prototype_ `virtual UWidget* Create(class UWidgetTree* Tree) = 0;` — Constructs the widget template.
- L39 _public function_ `virtual const FSlateBrush* GetIcon() const` — Gets the icon to display for this widget template.
- L46 _public prototype_ `virtual TSharedRef<IToolTip> GetToolTip() const = 0;` — Gets tooltip widget for this widget template.
- L49 _public function_ `virtual void GetFilterStrings(TArray<FString>& OutStrings) const` — @param OutStrings - Returns an array of strings used for filtering/searching this widget template.
- L52 _public function_ `virtual FReply OnDoubleClicked()` — The the action to perform when the template item is double clicked
- L56 _public member_ `FText Name;` — The name of the widget template.

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API UMGEDITOR_API`
