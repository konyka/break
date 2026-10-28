# Plugins / UserToolBoxBasicCommand

- module root: `Plugins/Experimental/UserToolBoxBasicCommand/Source/UserToolBoxBasicCommand`
- headers: 30; symbols: 182
- symbol kinds: class=40, delegate=1, enum=2, enumerator=6, function=11, member=50, prototype=70, struct=2
- DynamicallyLoadedModuleNames: 
- PrivateDependencyModuleNames: Blutility, CoreUObject, DatasmithContent, EditorInteractiveToolsFramework, EditorScriptingUtilities, EditorStyle, EditorWidgets, Engine, GeometryFramework, GeometryScriptingCore, InputCore, PropertyEditor, Slate, SlateCore, StaticMeshEditor, ToolWidgets, UnrealEd, UserToolBoxCore
- PublicDependencyModuleNames: AssetTools, Core

### `Plugins/Experimental/UserToolBoxBasicCommand/Source/UserToolBoxBasicCommand/Private/Customization/BaseCompositeCommandCustomization.h` (Private)


#### class `FBaseCompositeCommandCustomization`  
`class FBaseCompositeCommandCustomization : public IDetailCustomization`  
_L16-28_
- inherits: `IDetailCustomization`
- L19 _public function_ `static TSharedRef<IDetailCustomization> MakeInstance()`
- L25 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`
- L26 _public prototype_ `virtual void CustomizeDetails(const TSharedPtr<IDetailLayoutBuilder>& DetailBuilder) override;`
- L27 _public prototype_ `void GenerateArrayChildren(TSharedRef<IPropertyHandle> PropertyHandle, int32 ArrayIndex, IDetailChildrenBuilder& ChildrenBuilder);`

### `Plugins/Experimental/UserToolBoxBasicCommand/Source/UserToolBoxBasicCommand/Private/Customization/BindableActionCustomization.h` (Private)


#### class `FBindableActionPropertyCustomization`  
`class FBindableActionPropertyCustomization : public IPropertyTypeCustomization`  
_L17-44_
- inherits: `IPropertyTypeCustomization`
- L20 _public function_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance()`
- L25 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L27 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> PropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L30 _public prototype_ `TSharedRef<SWidget> OnGenerateContextComboWidget(TSharedPtr<FBindingContext> Item) const;`
- L31 _public prototype_ `void OnSelectContext(TSharedPtr<FBindingContext> Item, ESelectInfo::Type SelectInfo);`
- L32 _public prototype_ `TSharedRef<SWidget> OnGenerateCommandComboWidget(TSharedPtr<FUICommandInfo> Item) const;`
- L33 _public prototype_ `void OnSelectCommand(TSharedPtr<FUICommandInfo> Item, ESelectInfo::Type SelectInfo);`
- L35 _private member_ `TSharedPtr<FBindingContext> SelectedContext;`
- L36 _private member_ `TSharedPtr<FUICommandInfo> CurrentCommand;`
- L38 _private member_ `TArray<TSharedPtr<FBindingContext>> BindingContexts;`
- L39 _private member_ `TArray<TSharedPtr<FUICommandInfo>> CurrentCommandInfos;`
- L41 _private prototype_ `void RefreshCommandList();`
- L42 _private member_ `TSharedPtr<IPropertyHandle> StructPropertyHandle;`

### `Plugins/Experimental/UserToolBoxBasicCommand/Source/UserToolBoxBasicCommand/Public/ActorFilter/BaseActorFilter.h` (Public)


#### class `UBaseActorFilter`  
`class UBaseActorFilter : public UObject`  
_L15-53_
- reflection: `UCLASS(Blueprintable,EditInlineNew, Abstract)`
- inherits: `UObject`
- L21 _public prototype_ `TArray<AActor*> Filter(const TArray<AActor*>& Source);` — `UFUNCTION(BlueprintNativeEvent)`
- L23 _public prototype_ `bool FilterUnit(AActor* Source);` — `UFUNCTION(BlueprintNativeEvent)`
- L25 _public member_ `bool bShouldRunGlobalFilter=true;` — `UPROPERTY(EditAnywhere,Category="FilterCommand")`
- L27 _public member_ `bool bShouldRunUnitFilter=true;` — `UPROPERTY(EditAnywhere,Category="FilterCommand")`
- L28 _public function_ `virtual TArray<AActor*> FilterImpl(const TArray<AActor*>& Source)`

#### class `UGetAllDescendants`  
`class UGetAllDescendants : public UBaseActorFilter`  
_L57-62_
- reflection: `UCLASS(Blueprintable)`
- inherits: `UBaseActorFilter`
- L61 _public prototype_ `virtual TArray<AActor*> FilterImpl(const TArray<AActor*>& Source) override;`

#### class `UGetParents`  
`class UGetParents : public UBaseActorFilter`  
_L67-72_
- reflection: `UCLASS(Blueprintable)`
- inherits: `UBaseActorFilter`
- L71 _public prototype_ `virtual TArray<AActor*> FilterImpl(const TArray<AActor*>& Source) override;`

#### class `UHasAttachedActor`  
`class UHasAttachedActor : public UBaseActorFilter`  
_L74-79_
- reflection: `UCLASS(Blueprintable)`
- inherits: `UBaseActorFilter`
- L78 _public prototype_ `virtual TArray<AActor*> FilterImpl(const TArray<AActor*>& Source) override;`

#### class `UHasComponentOfClass`  
`class UHasComponentOfClass : public UBaseActorFilter`  
_L82-89_
- reflection: `UCLASS(Blueprintable)`
- inherits: `UBaseActorFilter`
- L87 _public member_ `TSubclassOf<UActorComponent> ComponentClass;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Filter")`
- L88 _public prototype_ `virtual TArray<AActor*> FilterImpl(const TArray<AActor*>& Source) override;`

#### class `UHasMetadataByKey`  
`class UHasMetadataByKey : public UBaseActorFilter`  
_L91-98_
- reflection: `UCLASS(Blueprintable)`
- inherits: `UBaseActorFilter`
- L96 _public member_ `FName Key;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Filter")`
- L97 _public prototype_ `virtual TArray<AActor*> FilterImpl(const TArray<AActor*>& Source) override;`

#### class `UHasMetadataByKeyAndValue`  
`class UHasMetadataByKeyAndValue : public UBaseActorFilter`  
_L100-109_
- reflection: `UCLASS(Blueprintable)`
- inherits: `UBaseActorFilter`
- L105 _public member_ `FName Key;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Filter")`
- L107 _public member_ `FString Value;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Filter")`
- L108 _public prototype_ `virtual TArray<AActor*> FilterImpl(const TArray<AActor*>& Source) override;`

#### class `UIsClassOf`  
`class UIsClassOf : public UBaseActorFilter`  
_L111-120_
- reflection: `UCLASS(Blueprintable)`
- inherits: `UBaseActorFilter`
- L116 _public member_ `TSubclassOf<AActor> ActorClass;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Filter")`
- L118 _public member_ `bool ChildClass=false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Filter")`
- L119 _public prototype_ `virtual TArray<AActor*> FilterImpl(const TArray<AActor*>& Source) override;`

#### class `UGetNDescendants`  
`class UGetNDescendants : public UBaseActorFilter`  
_L122-131_
- reflection: `UCLASS(Blueprintable)`
- inherits: `UBaseActorFilter`
- L127 _public member_ `int N;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Filter")`
- L129 _public member_ `bool AddIntermediaries;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Filter")`
- L130 _public prototype_ `virtual TArray<AActor*> FilterImpl(const TArray<AActor*>& Source) override;`

#### class `UHasMetadataByKeyAndValueDropDown`  
`class UHasMetadataByKeyAndValueDropDown : public UBaseActorFilter`  
_L133-139_
- reflection: `UCLASS(Blueprintable)`
- inherits: `UBaseActorFilter`
- L138 _public prototype_ `virtual TArray<AActor*> FilterImpl(const TArray<AActor*>& Source) override;`

#### class `UEmptyStaticMeshActor`  
`class UEmptyStaticMeshActor : public UBaseActorFilter`  
_L141-147_
- reflection: `UCLASS(Blueprintable)`
- inherits: `UBaseActorFilter`
- L146 _public prototype_ `virtual TArray<AActor*> FilterImpl(const TArray<AActor*>& Source) override;`

### `Plugins/Experimental/UserToolBoxBasicCommand/Source/UserToolBoxBasicCommand/Public/AssignToLayer.h` (Public)


#### class `UAssignToLayer`  
`class UAssignToLayer : public UUTBBaseCommand`  
_L14-22_
- reflection: `UCLASS()`
- inherits: `UUTBBaseCommand`
- L19 _public prototype_ `void Execute() override;`
- L20 _public prototype_ `virtual FName GetLayerName(TWeakObjectPtr<ULayer> Layer);`
- L21 _public prototype_ `UAssignToLayer();`

### `Plugins/Experimental/UserToolBoxBasicCommand/Source/UserToolBoxBasicCommand/Public/AssignToLevel.h` (Public)


#### class `UAssignToLevel`  
`class UAssignToLevel : public UUTBBaseCommand`  
_L13-20_
- reflection: `UCLASS()`
- inherits: `UUTBBaseCommand`
- L18 _public prototype_ `virtual void Execute() override;`
- L19 _public prototype_ `UAssignToLevel();`

### `Plugins/Experimental/UserToolBoxBasicCommand/Source/UserToolBoxBasicCommand/Public/BaseCompositeCommand.h` (Public)


#### class `UBaseCompositeCommand`  
`class UBaseCompositeCommand : public UUTBBaseCommand`  
_L13-30_
- reflection: `UCLASS(Abstract)`
- inherits: `UUTBBaseCommand`
- L19 _public member_ `TArray<TObjectPtr<UUTBBaseCommand>> Commands;` — `UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="Composite Commands")`
- L21 _public function_ `UBaseCompositeCommand()`
- L28 _public prototype_ `virtual UUTBBaseCommand* CopyCommand(UObject* Owner) const override;`

### `Plugins/Experimental/UserToolBoxBasicCommand/Source/UserToolBoxBasicCommand/Public/BaseCompositeInlineCommand.h` (Public)


#### class `UBaseCompositeInlineCommand`  
`class UBaseCompositeInlineCommand : public UUTBBaseCommand`  
_L13-30_
- reflection: `UCLASS(Abstract, EditInlineNew)`
- inherits: `UUTBBaseCommand`
- L19 _public member_ `TArray<TObjectPtr<UUTBBaseCommand>> Commands;` — `UPROPERTY(EditAnywhere,BlueprintReadWrite,Instanced,Category="CompositeCommand")`
- L21 _public function_ `UBaseCompositeInlineCommand()`

### `Plugins/Experimental/UserToolBoxBasicCommand/Source/UserToolBoxBasicCommand/Public/ChangeViewMode.h` (Public)


#### class `UChangeViewMode`  
`class UChangeViewMode : public UUTBBaseCommand`  
_L13-22_
- reflection: `UCLASS()`
- inherits: `UUTBBaseCommand`
- L19 _public member_ `TEnumAsByte<EViewModeIndex> ViewMode=EViewModeIndex::VMI_Lit;` — `UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="ChangeViewCommand")`
- L20 _public prototype_ `virtual void Execute() override;`
- L21 _public prototype_ `UChangeViewMode();`

### `Plugins/Experimental/UserToolBoxBasicCommand/Source/UserToolBoxBasicCommand/Public/CleanHierarchy.h` (Public)


#### class `UCleanHierarchy`  
`class UCleanHierarchy : public UUTBBaseCommand`  
_L13-25_
- reflection: `UCLASS()`
- inherits: `UUTBBaseCommand`
- L18 _public member_ `TArray<FString> DSMetadataToPreserve;` — `UPROPERTY(EditAnywhere,Category="CleanHierarchyCommand")`
- L20 _public member_ `bool RemoveEmptyBranches;` — `UPROPERTY(EditAnywhere,Category="CleanHierarchyCommand")`
- L22 _public member_ `bool RemoveIntermediaryActorsWithoutGeometry;` — `UPROPERTY(EditAnywhere,Category="CleanHierarchyCommand")`
- L23 _public prototype_ `UCleanHierarchy();`
- L24 _public prototype_ `virtual void Execute() override;`

### `Plugins/Experimental/UserToolBoxBasicCommand/Source/UserToolBoxBasicCommand/Public/CompositeCommand.h` (Public)


#### class `UCompositeCommand`  
`class UCompositeCommand : public UBaseCompositeCommand`  
_L15-30_
- reflection: `UCLASS(Blueprintable)`
- inherits: `UBaseCompositeCommand`
- L21 _public prototype_ `virtual void Execute() override;`
- L22 _public function_ `UCompositeCommand()`

### `Plugins/Experimental/UserToolBoxBasicCommand/Source/UserToolBoxBasicCommand/Public/CompositeInlineCommand.h` (Public)


#### class `UCompositeInlineCommand`  
`class UCompositeInlineCommand : public UBaseCompositeInlineCommand`  
_L15-30_
- reflection: `UCLASS(Blueprintable)`
- inherits: `UBaseCompositeInlineCommand`
- L21 _public prototype_ `virtual void Execute() override;`
- L22 _public function_ `UCompositeInlineCommand()`

### `Plugins/Experimental/UserToolBoxBasicCommand/Source/UserToolBoxBasicCommand/Public/ConsoleVariable.h` (Public)


#### class `UConsoleVariable`  
`class UConsoleVariable : public UUTBBaseCommand`  
_L13-28_
- reflection: `UCLASS()`
- inherits: `UUTBBaseCommand`
- L18 _public member_ `TArray<FString> ConsoleCommands;` — `UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Console Command")`
- L20 _public prototype_ `virtual void Execute() override;`
- L22 _public function_ `UConsoleVariable()`

### `Plugins/Experimental/UserToolBoxBasicCommand/Source/UserToolBoxBasicCommand/Public/EngineCommand.h` (Public)


#### class `UEngineCommand`  
`class UEngineCommand : public UUTBBaseCommand`  
_L13-27_
- reflection: `UCLASS()`
- inherits: `UUTBBaseCommand`
- L19 _public member_ `FString Command;` — `UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="EngineCommand")`
- L20 _public prototype_ `virtual void Execute() override;`
- L21 _public function_ `UEngineCommand()`

### `Plugins/Experimental/UserToolBoxBasicCommand/Source/UserToolBoxBasicCommand/Public/ExecuteBindableAction.h` (Public)


#### struct `FBindableActionInfo`  
`struct FBindableActionInfo`  
_L11-18_
- reflection: `USTRUCT()`
- L15 _public member_ `FString Context;` — `UPROPERTY()`
- L17 _public member_ `FString CommandName;` — `UPROPERTY()`

#### class `UExecuteBindableAction`  
`class UExecuteBindableAction : public UUTBBaseCommand`  
_L24-37_
- reflection: `UCLASS()`
- inherits: `UUTBBaseCommand`
- L28 _public prototype_ `UExecuteBindableAction() ;`
- L31 _public member_ `FBindableActionInfo CommandInfo;` — `UPROPERTY(EditAnywhere,Category="Bindable Command")`
- L35 _public prototype_ `virtual void Execute() override;`

### `Plugins/Experimental/UserToolBoxBasicCommand/Source/UserToolBoxBasicCommand/Public/ExecutePythonScript.h` (Public)


#### class `UExecutePythonScript`  
`class UExecutePythonScript : public UUTBBaseCommand`  
_L14-28_
- reflection: `UCLASS()`
- inherits: `UUTBBaseCommand`
- L18 _public prototype_ `UExecutePythonScript() ;`
- L21 _private member_ `FFilePath ScriptPath;` — `UPROPERTY(EditAnywhere,Category="Python Command")`
- L24 _private member_ `FString Args;` — `UPROPERTY(EditAnywhere,Category="Python Command")`
- L27 _public prototype_ `virtual void Execute() override;`

### `Plugins/Experimental/UserToolBoxBasicCommand/Source/UserToolBoxBasicCommand/Public/FillStaticMeshActor.h` (Public)


#### class `UFillStaticMeshActor`  
`class UFillStaticMeshActor : public UUTBBaseCommand`  
_L13-26_
- reflection: `UCLASS()`
- inherits: `UUTBBaseCommand`
- L19 _public member_ `TArray<FString> RootPaths;` — `UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="FillStaticMeshActor")`
- L22 _public member_ `bool bAffectOnlyEmptyStaticMeshActor=true;` — `UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="FillStaticMeshActor")`
- L24 _public prototype_ `void Execute() override;`
- L25 _public prototype_ `UFillStaticMeshActor();`

### `Plugins/Experimental/UserToolBoxBasicCommand/Source/UserToolBoxBasicCommand/Public/FlipNormals.h` (Public)


#### class `UFlipNormals`  
`class UFlipNormals : public UUTBBaseCommand`  
_L13-20_
- reflection: `UCLASS()`
- inherits: `UUTBBaseCommand`
- L18 _public prototype_ `virtual void Execute() override;`
- L19 _public prototype_ `UFlipNormals();`

### `Plugins/Experimental/UserToolBoxBasicCommand/Source/UserToolBoxBasicCommand/Public/IsolateSelection.h` (Public)


#### class `UIsolateSelection`  
`class UIsolateSelection : public UUTBBaseCommand`  
_L13-21_
- reflection: `UCLASS()`
- inherits: `UUTBBaseCommand`
- L18 _public member_ `bool bShouldOnlyAffectStaticMeshActor=false;` — `UPROPERTY(EditAnywhere,Category="Isolate Command")`
- L19 _public prototype_ `UIsolateSelection();`
- L20 _public prototype_ `virtual void Execute() override;`

### `Plugins/Experimental/UserToolBoxBasicCommand/Source/UserToolBoxBasicCommand/Public/MergeCommand.h` (Public)


#### class `UMerge`  
`class UMerge : public UUTBBaseCommand`  
_L13-22_
- reflection: `UCLASS()`
- inherits: `UUTBBaseCommand`
- L19 _public member_ `bool Advanced;` — `UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Merge Command")`
- L20 _public prototype_ `UMerge();`
- L21 _public prototype_ `virtual void Execute() override;`

### `Plugins/Experimental/UserToolBoxBasicCommand/Source/UserToolBoxBasicCommand/Public/MirrorActorCommand.h` (Public)


#### class `UMirrorActorCommand`  
`class UMirrorActorCommand : public UUTBBaseCommand`  
_L13-25_
- reflection: `UCLASS()`
- inherits: `UUTBBaseCommand`
- L18 _public member_ `bool XAxis=false;` — `UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="MirrorCommand")`
- L20 _public member_ `bool YAxis=false;` — `UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="MirrorCommand")`
- L22 _public member_ `bool ZAxis=false;` — `UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="MirrorCommand")`
- L23 _public prototype_ `UMirrorActorCommand();`
- L24 _public prototype_ `virtual void Execute() override;`

### `Plugins/Experimental/UserToolBoxBasicCommand/Source/UserToolBoxBasicCommand/Public/PushComponentMaterialIntoMesh.h` (Public)


#### class `UPushComponentMaterialIntoMesh`  
`class UPushComponentMaterialIntoMesh : public UUTBBaseCommand`  
_L13-21_
- reflection: `UCLASS()`
- inherits: `UUTBBaseCommand`
- L18 _public prototype_ `void Execute() override;`
- L20 _public prototype_ `UPushComponentMaterialIntoMesh();`

### `Plugins/Experimental/UserToolBoxBasicCommand/Source/UserToolBoxBasicCommand/Public/SelectActorByFilter.h` (Public)


#### enum `EActorFilterRule`  
`enum class EActorFilterRule : uint8`  
_L12-18_
- reflection: `UENUM()`
- L14 _public enumerator_ `Add =0`
- L15 _public enumerator_ `Intersect =2`
- L16 _public enumerator_ `Substract =3`
- L17 _public enumerator_ `Replace= 4`

#### enum `EActorFilterSource`  
`enum class EActorFilterSource : uint8`  
_L20-24_
- reflection: `UENUM()`
- L22 _public enumerator_ `OriginalSelection =0`
- L23 _public enumerator_ `PreviousResult =1`

#### struct `FActorFilterOptions`  
`struct FActorFilterOptions`  
_L28-40_
- reflection: `USTRUCT(BlueprintType)`
- L32 _public member_ `TObjectPtr<UBaseActorFilter> Filter;` — `UPROPERTY(EditAnywhere, Category="Actor Filter",Instanced)`
- L34 _public member_ `EActorFilterRule Rule=EActorFilterRule::Replace;` — `UPROPERTY(EditAnywhere, Category="Actor Filter")`
- L36 _public member_ `EActorFilterSource Source=EActorFilterSource::PreviousResult;` — `UPROPERTY(EditAnywhere, Category="Actor Filter")`
- L39 _public member_ `bool ShowProperties=false;` — `UPROPERTY(EditAnywhere, Category="Actor Filter")`

#### class `USelectActorByFilter`  
`class USelectActorByFilter : public UUTBBaseCommand`  
_L44-56_
- reflection: `UCLASS(Blueprintable)`
- inherits: `UUTBBaseCommand`
- L49 _public member_ `bool ApplyToCurrentSelection;` — `UPROPERTY(EditAnywhere,BlueprintReadOnly, Category="Actor Filter")`
- L51 _public member_ `TArray<FActorFilterOptions> FilterStack;` — `UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="Actor Filter")`
- L52 _public prototype_ `virtual void Execute() override;`
- L53 _public prototype_ `USelectActorByFilter();`

### `Plugins/Experimental/UserToolBoxBasicCommand/Source/UserToolBoxBasicCommand/Public/SelectActorBySize.h` (Public)


#### class `USelectActorBySize`  
`class USelectActorBySize : public UUTBBaseCommand`  
_L13-22_
- reflection: `UCLASS()`
- inherits: `UUTBBaseCommand`
- L19 _public member_ `float SizeThreshold;` — `UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="SelectActorBySizeCommand")`
- L20 _public prototype_ `USelectActorBySize();`
- L21 _public prototype_ `virtual void Execute() override;`

### `Plugins/Experimental/UserToolBoxBasicCommand/Source/UserToolBoxBasicCommand/Public/SetHighPrecisionOnMesh.h` (Public)


#### class `USetHighPrecisionOnMesh`  
`class USetHighPrecisionOnMesh : public UUTBBaseCommand`  
_L13-24_
- reflection: `UCLASS()`
- inherits: `UUTBBaseCommand`
- L19 _public member_ `bool bHighPrecisionTangent=true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="HighPrecisionCommand")`
- L21 _public member_ `bool bHighPrecisionUV=true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="HighPrecisionCommand")`
- L22 _public prototype_ `USetHighPrecisionOnMesh();`
- L23 _public prototype_ `virtual void Execute() override;`

### `Plugins/Experimental/UserToolBoxBasicCommand/Source/UserToolBoxBasicCommand/Public/ShowLayersCommand.h` (Public)


#### class `UShowLayersCommand`  
`class UShowLayersCommand : public UUTBBaseCommand`  
_L13-25_
- reflection: `UCLASS()`
- inherits: `UUTBBaseCommand`
- L18 _public member_ `TArray<FName> Layers;` — `UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="LayerCommand")`
- L21 _public member_ `bool bIsolate=false;` — `UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="LayerCommand")`
- L22 _public prototype_ `UShowLayersCommand();`
- L23 _public prototype_ `virtual bool DisplayParameters() override;`
- L24 _public prototype_ `virtual void Execute() override;`

### `Plugins/Experimental/UserToolBoxBasicCommand/Source/UserToolBoxBasicCommand/Public/TabSpawner.h` (Public)


#### class `UTabSpawner`  
`class UTabSpawner : public UUTBBaseCommand`  
_L13-21_
- reflection: `UCLASS()`
- inherits: `UUTBBaseCommand`
- L16 _private prototype_ `UTabSpawner();`
- L18 _private member_ `FName TabName;` — `UPROPERTY(EditAnywhere,Category="TabSpawnerCommand")`
- L20 _public prototype_ `virtual void Execute() override;`

### `Plugins/Experimental/UserToolBoxBasicCommand/Source/UserToolBoxBasicCommand/Public/ToggleCommand.h` (Public)


#### class `UToggleCommand`  
`class UToggleCommand : public UBaseCompositeCommand`  
_L18-34_
- reflection: `UCLASS(Blueprintable)`
- inherits: `UBaseCompositeCommand`
- L22 _public function_ `UToggleCommand()`
- L31 _private member_ `int CurrentIndex=0;`
- L32 _private prototype_ `virtual void Execute() override;`

### `Plugins/Experimental/UserToolBoxBasicCommand/Source/UserToolBoxBasicCommand/Public/ToggleCommandInline.h` (Public)


#### class `UToggleCommandInline`  
`class UToggleCommandInline : public UUTBBaseCommand`  
_L17-37_
- reflection: `UCLASS(Blueprintable)`
- inherits: `UUTBBaseCommand`
- L23 _public member_ `TArray<TObjectPtr<UUTBBaseCommand>> Commands;` — `UPROPERTY(EditAnywhere,BlueprintReadWrite,Instanced,Category="ToggleCommand")`
- L25 _public function_ `UToggleCommandInline()`
- L34 _private member_ `int CurrentIndex=0;`
- L35 _private prototype_ `virtual void Execute() override;`

### `Plugins/Experimental/UserToolBoxBasicCommand/Source/UserToolBoxBasicCommand/Public/UserToolBoxBasicCommand.h` (Public)


#### class `FUserToolBox_BasicCommandModule`  
`class FUserToolBox_BasicCommandModule : public IModuleInterface`  
_L9-16_
- inherits: `IModuleInterface`
- L14 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L15 _public prototype_ `virtual void ShutdownModule() override;`

#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogUserToolBoxBasicCommand, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogUserToolBoxBasicCommand, Log, All);`

### `Plugins/Experimental/UserToolBoxBasicCommand/Source/UserToolBoxBasicCommand/Public/ZoomAll.h` (Public)


#### class `UZoomAll`  
`class UZoomAll : public UUTBBaseCommand`  
_L13-20_
- reflection: `UCLASS()`
- inherits: `UUTBBaseCommand`
- L17 _public prototype_ `UZoomAll();`
- L18 _public prototype_ `virtual void Execute() override;`
