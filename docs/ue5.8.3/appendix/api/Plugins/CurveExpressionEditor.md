# Plugins / CurveExpressionEditor

- module root: `Plugins/Experimental/Animation/CurveExpression/Source/Editor`
- headers: 8; symbols: 78
- symbol kinds: class=10, function=9, macro=1, member=8, namespace=3, prototype=47

### `Plugins/Experimental/Animation/CurveExpression/Source/Editor/Private/AssetDefinition_CurveExpressionsDataAsset.h` (Private)


#### class `UAssetDefinition_CurveExpressionsDataAsset`  
`class UAssetDefinition_CurveExpressionsDataAsset : public UAssetDefinitionDefault`  
_L12-30_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L18 _public function_ `virtual FText GetAssetDisplayName() const override`
- L19 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L20 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L21 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`
- L26 _public prototype_ `virtual EAssetCommandResult PerformAssetDiff(const FAssetDiffArgs& DiffArgs) const override;`
- L27 _public prototype_ `virtual bool CanMerge() const override;`
- L28 _public prototype_ `virtual EAssetCommandResult Merge(const FAssetAutomaticMergeArgs& MergeArgs) const override;`
- L29 _public prototype_ `virtual EAssetCommandResult Merge(const FAssetManualMergeArgs& MergeArgs) const override;`

### `Plugins/Experimental/Animation/CurveExpression/Source/Editor/Private/CurveExpressionDetailsCustomization.h` (Private)


#### class `FAnimGraphNode_RemapCurvesDebuggingCustomization`  
`class FAnimGraphNode_RemapCurvesDebuggingCustomization : public IDetailCustomization`  
_L13-21_
- inherits: `IDetailCustomization`
- L17 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L20 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& InDetailBuilder) override;` — IDetailCustomization overrides

#### class `FCurveExpressionListCustomization`  
`class FCurveExpressionListCustomization : public IPropertyTypeCustomization`  
_L24-48_
- inherits: `IPropertyTypeCustomization`
- L28 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L31 _public prototype_ `virtual void CustomizeHeader( TSharedRef<IPropertyHandle> InPropertyHandle, FDetailWidgetRow& InHeaderRow, IPropertyTypeCustomizationUtils& InCustomizationUtils) override;` — IPropertyTypeCustomization overrides
- L36 _public function_ `virtual void CustomizeChildren( TSharedRef<IPropertyHandle> InPropertyHandle, IDetailChildrenBuilder& InChildBuilder, IPropertyTypeCustomizationUtils& InCustomizationUtils) override`
- L42 _private member_ `TSharedPtr<IPropertyHandle> AssignmentExpressionsProperty;`
- L44 _private member_ `TSharedPtr<SScrollBar> HorizontalScrollbar;`
- L45 _private member_ `TSharedPtr<SScrollBar> VerticalScrollbar;`
- L47 _private member_ `TSharedPtr<SMultiLineEditableTextBox> TextEditor;`

### `Plugins/Experimental/Animation/CurveExpression/Source/Editor/Private/CurveExpressionEditorStyle.h` (Private)


#### class `FCurveExpressionEditorStyle`  
`class FCurveExpressionEditorStyle : public FSlateStyleSet`  
_L7-18_
- inherits: `FSlateStyleSet`
- L11 _public prototype_ `static FCurveExpressionEditorStyle& Get();`
- L13 _public prototype_ `static void Register();`
- L14 _public prototype_ `static void Unregister();`
- L17 _private prototype_ `FCurveExpressionEditorStyle();`

### `Plugins/Experimental/Animation/CurveExpression/Source/Editor/Private/CurveExpressionsDataAssetFactory.h` (Private)


#### class `UCurveExpressionsDataAssetFactory`  
`class UCurveExpressionsDataAssetFactory : public UFactory`  
_L10-19_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UFactory`
- L15 _public prototype_ `UCurveExpressionsDataAssetFactory();`
- L18 _public prototype_ `virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags InFlags, UObject* InContext, FFeedbackContext* InWarn) override;` — UFactory overrides

### `Plugins/Experimental/Animation/CurveExpression/Source/Editor/Public/AnimGraphNode_RemapCurves.h` (Public)


#### class `UAnimGraphNode_RemapCurves`  
`class UAnimGraphNode_RemapCurves : public UAnimGraphNode_Base, public IRemapCurvesDebuggingProvider`  
_L17-48_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAnimGraphNode_Base,IRemapCurvesDebuggingProvider`
- L25 _public member_ `FAnimNode_RemapCurves Node;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Settings)`
- L27 _public prototype_ `bool CanVerifyExpressions() const override;`
- L28 _public prototype_ `void VerifyExpressions() override;`
- L31 _public prototype_ `FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;` — UEdGraphNode interface
- L32 _public prototype_ `FText GetTooltipText() const override;`
- L33 _public prototype_ `FText GetMenuCategory() const override;`
- L37 _public function_ `bool UsingCopyPoseFromMesh() const override` — UAnimGraphNode_Base interface
- L38 _public prototype_ `void GetOutputLinkAttributes(FNodeAttributeArray& OutAttributes) const override;`
- L39 _public prototype_ `void CustomizePinData(UEdGraphPin* Pin, FName SourcePropertyName, int32 ArrayIndex) const override;`
- L43 _public prototype_ `void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;` — UObject override
- L46 _private prototype_ `USkeletalMeshComponent* GetDebuggedComponent() const;`
- L47 _private prototype_ `FAnimNode_RemapCurves* GetDebuggedNode() const;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace ENodeTitleType`

### `Plugins/Experimental/Animation/CurveExpression/Source/Editor/Public/AnimGraphNode_RemapCurvesFromMesh.h` (Public)


#### class `UAnimGraphNode_RemapCurvesFromMesh`  
`class UAnimGraphNode_RemapCurvesFromMesh : public UAnimGraphNode_Base, public IRemapCurvesDebuggingProvider`  
_L16-47_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAnimGraphNode_Base,IRemapCurvesDebuggingProvider`
- L24 _public member_ `FAnimNode_RemapCurvesFromMesh Node;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Settings)`
- L26 _public prototype_ `bool CanVerifyExpressions() const override;`
- L27 _public prototype_ `void VerifyExpressions() override;`
- L30 _public prototype_ `FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;` — UEdGraphNode interface
- L31 _public prototype_ `FText GetTooltipText() const override;`
- L32 _public prototype_ `FText GetMenuCategory() const override;`
- L36 _public function_ `bool UsingCopyPoseFromMesh() const override` — UAnimGraphNode_Base interface
- L37 _public prototype_ `void GetOutputLinkAttributes(FNodeAttributeArray& OutAttributes) const override;`
- L38 _public prototype_ `void CustomizePinData(UEdGraphPin* Pin, FName SourcePropertyName, int32 ArrayIndex) const override;`
- L42 _public prototype_ `void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;` — UObject override
- L45 _private prototype_ `USkeletalMeshComponent* GetDebuggedComponent() const;`
- L46 _private prototype_ `FAnimNode_RemapCurvesFromMesh* GetDebuggedNode() const;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace ENodeTitleType`

### `Plugins/Experimental/Animation/CurveExpression/Source/Editor/Public/IRemapCurvesDebuggingProvider.h` (Public)


#### class `URemapCurvesDebuggingProvider`  
`class URemapCurvesDebuggingProvider : public UInterface`  
_L10-14_
- reflection: `UINTERFACE()`
- inherits: `UInterface`

#### class `IRemapCurvesDebuggingProvider`  
`class IRemapCurvesDebuggingProvider`  
_L19-29_
- desc: Helper interface to allow the details customization to work on both Remap Curves and Remap Curves from Mesh.
- L25 _public prototype_ `virtual bool CanVerifyExpressions() const = 0;` — Returns true if the expressions can be verified against an actively debugged anim graph instance
- L28 _public prototype_ `virtual void VerifyExpressions() = 0;` — Trigger expression verification against an actively debugged anim graph instance

### `Plugins/Experimental/Animation/CurveExpression/Source/Editor/Public/K2Node_MakeCurveExpressionMap.h` (Public)


#### class `UK2Node_MakeCurveExpressionMap`  
`class UK2Node_MakeCurveExpressionMap : public UK2Node`  
_L19-51_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UK2Node`
- L25 _public prototype_ `UK2Node_MakeCurveExpressionMap();`
- L27 _public prototype_ `UEdGraphPin* GetOutputPin() const;`
- L28 _public prototype_ `TMap<FName, FString> GetExpressionMap() const;`
- L31 _public prototype_ `virtual void AllocateDefaultPins() override;` — UEdGraphNode interface
- L32 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L33 _public prototype_ `virtual FText GetTooltipText() const override;`
- L34 _public prototype_ `virtual FSlateIcon GetIconAndTint(FLinearColor& OutColor) const override;`
- L35 _public prototype_ `virtual void ValidateNodeDuringCompilation(FCompilerResultsLog& MessageLog) const override;`
- L39 _public prototype_ `virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& InActionRegistrar) const override;` — UK2Node interface
- L40 _public prototype_ `virtual FNodeHandlingFunctor* CreateNodeHandler(FKismetCompilerContext& CompilerContext) const override;`
- L41 _public prototype_ `virtual FText GetMenuCategory() const override;`
- L42 _public function_ `virtual bool ShouldShowNodeProperties() const override`
- L43 _public function_ `virtual bool IsNodePure() const override`
- L47 _public member_ `FCurveExpressionList Expressions;` — `UPROPERTY(EditAnywhere, Category="Expressions")`
- L50 _private member_ `static const FName OutputPinName;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API CURVEEXPRESSIONEDITOR_API`
- L15 _namespace_ `namespace ENodeTitleType`
