# Plugins / VertexDeltaModelEditor

- module root: `Plugins/Animation/MLDeformer/VertexDeltaModel/Source/VertexDeltaModelEditor`
- headers: 4; symbols: 21
- symbol kinds: class=4, function=2, namespace=6, prototype=9
- PrivateDependencyModuleNames: ComputeFramework, CoreUObject, EditorFramework, EditorStyle, EditorWidgets, Engine, GeometryCache, MLDeformerFramework, MLDeformerFrameworkEditor, NNE, NNERuntimeORT, PropertyEditor, Slate, SlateCore, ToolWidgets, UnrealEd, VertexDeltaModel
- PrivateIncludePathModuleNames: 
- PublicDependencyModuleNames: Core

### `Plugins/Animation/MLDeformer/VertexDeltaModel/Source/VertexDeltaModelEditor/Public/VertexDeltaEditorModel.h` (Public)


#### class `UE::VertexDeltaModel::FVertexDeltaEditorModel`  
`class FVertexDeltaEditorModel : public UE::MLDeformer::FMLDeformerGeomCacheEditorModel`  
_L19-38_
- inherits: `UE::MLDeformer::FMLDeformerGeomCacheEditorModel`
- desc: The editor model for a UVertexDeltaModel.
- L24 _public prototype_ `static FMLDeformerEditorModel* MakeInstance();` — We need to implement this static MakeInstance method.
- L27 _public function_ `virtual FString GetReferencerName() const override` — FGCObject overrides.
- L31 _public prototype_ `virtual ETrainingResult Train() override;` — FMLDeformerEditorModel overrides.
- L32 _public prototype_ `virtual bool LoadTrainedNetwork() const override;`
- L33 _public prototype_ `virtual FString GetHeatMapDeformerGraphPath() const override;`
- L36 _public prototype_ `TObjectPtr<UNNEModelData> LoadNeuralNetworkFromOnnx(const FString& Filename) const;`
- L37 _public prototype_ `UVertexDeltaModel* GetVertexDeltaModel() const;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace VertexDeltaModel` (scope `UE`)

### `Plugins/Animation/MLDeformer/VertexDeltaModel/Source/VertexDeltaModelEditor/Public/VertexDeltaModelDetails.h` (Public)


#### class `UE::VertexDeltaModel::FVertexDeltaModelDetails`  
`class FVertexDeltaModelDetails : public UE::MLDeformer::FMLDeformerGeomCacheModelDetails`  
_L16-26_
- inherits: `UE::MLDeformer::FMLDeformerGeomCacheModelDetails`
- desc: The detail customization for the vertex delta model. This basically just adds the properties specific to the vertex delta model to the trainings settings. But as we inherit from the FMLDeformerGeomCacheModelDetails class, it directly creates all the other properties for us as well, and inserts error messages when something is wrong, creates some groups, etc.
- L21 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it.
- L24 _public prototype_ `void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;` — ILayoutDetails overrides.

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace VertexDeltaModel` (scope `UE`)

### `Plugins/Animation/MLDeformer/VertexDeltaModel/Source/VertexDeltaModelEditor/Public/VertexDeltaModelVizSettingsDetails.h` (Public)


#### class `UE::VertexDeltaModel::FVertexDeltaModelVizSettingsDetails`  
`class FVertexDeltaModelVizSettingsDetails : public UE::MLDeformer::FMLDeformerGeomCacheVizSettingsDetails`  
_L15-24_
- inherits: `UE::MLDeformer::FMLDeformerGeomCacheVizSettingsDetails`
- desc: The detail customization for the vertex delta model visualization settings. We inherit from a base class as that already takes care of some nice grouping of properties, some error reporting in case of issues, and some nice grouping of settings.
- L20 _public function_ `static TSharedRef<IDetailCustomization> MakeInstance()` — Makes a new instance of this detail layout class for a specific detail view requesting it.

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace VertexDeltaModel` (scope `UE`)

### `Plugins/Animation/MLDeformer/VertexDeltaModel/Source/VertexDeltaModelEditor/Public/VertexDeltaTrainingModel.h` (Public)


#### class `UVertexDeltaTrainingModel`  
`class UVertexDeltaTrainingModel : public UMLDeformerGeomCacheTrainingModel`  
_L14-27_
- reflection: `UCLASS(Blueprintable)`
- inherits: `UMLDeformerGeomCacheTrainingModel`
- desc: The training model for the vertex delta model. This class is our link to the Python training.
- L26 _public prototype_ `int32 Train() const;` — `UFUNCTION(BlueprintImplementableEvent, Category = "Python")` — Main training function, with implementation in python. You need to implement this method. See the UMLDeformerTrainingModel documentation for more details. @see UMLDeformerTrainingModel
