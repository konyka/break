# Plugins / SVGImporterEditor

- module root: `Plugins/VirtualProduction/SVGImporter/Source/SVGImporterEditor`
- headers: 23; symbols: 265
- symbol kinds: class=22, delegate=1, enum=1, enumerator=2, function=21, macro=1, member=32, prototype=178, struct=6, typedef=1
- PrivateDependencyModuleNames: ApplicationCore, AssetDefinition, AssetTools, ContentBrowser, CoreUObject, DetailCustomizations, EditorFramework, Engine, InputCore, LevelEditor, Projects, PropertyEditor, RHI, RenderCore, SVGImporter, Slate, SlateCore, ToolMenus, TypedElementRuntime, UnrealEd, XmlParser, pugixml
- PublicDependencyModuleNames: Core

### `Plugins/VirtualProduction/SVGImporter/Source/SVGImporterEditor/Private/AssetDefinition_SVGData.h` (Private)


#### class `UAssetDefinition_SVGData`  
`class UAssetDefinition_SVGData : public UAssetDefinitionDefault`  
_L11-25_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L17 _public prototype_ `static void ExecuteReimportSVG(const FToolMenuContext& InContext);` — Menu Extension statics
- L20 _public prototype_ `virtual FText GetAssetDisplayName() const override;`
- L21 _public prototype_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override;`
- L22 _public prototype_ `virtual FLinearColor GetAssetColor() const override;`
- L23 _public prototype_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override;`

### `Plugins/VirtualProduction/SVGImporter/Source/SVGImporterEditor/Private/Customizations/JoinedSVGDynamicMeshComponentCustomization.h` (Private)


#### class `FJoinedSVGDynamicMeshComponentCustomization`  
`class FJoinedSVGDynamicMeshComponentCustomization : public IDetailCustomization`  
_L14-34_
- inherits: `IDetailCustomization`
- desc: Customizing JoinedSVGDynamicMeshComponent
- L17 _public function_ `static TSharedRef<IDetailCustomization> MakeInstance()`
- L23 _public prototype_ `~FJoinedSVGDynamicMeshComponentCustomization();`
- L26 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& InDetailBuilder) override;`
- L27 _public prototype_ `virtual void CustomizeDetails(const TSharedPtr<IDetailLayoutBuilder>& InDetailBuilder) override;`
- L31 _private prototype_ `void OnMeshColoringChanged() const;`
- L33 _private member_ `TWeakPtr<IDetailLayoutBuilder> DetailLayoutBuilderWeak;`

#### class `FSVGShapeParametersColorPropertyTypeIdentifier`  
`class FSVGShapeParametersColorPropertyTypeIdentifier : public IPropertyTypeIdentifier`  
_L39-58_
- inherits: `IPropertyTypeIdentifier`
- desc: Property identifier for the Color property found within FSVGShapeParameters
- L42 _public function_ `virtual bool IsPropertyTypeCustomized(const IPropertyHandle& InPropertyHandle) const override`

#### class `FSVGShapeParametersColorDetails`  
`class FSVGShapeParametersColorDetails : public FColorStructCustomization`  
_L65-73_
- inherits: `FColorStructCustomization`
- desc: Customization for the color in FSVGShapeParameters. This combined with the JoinedSVGDynamicMeshComponent customization above allows us to Properly expose the color to RC, despite it being in a struct handled by a TSet
- L68 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L71 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> InStructPropertyHandle, FDetailWidgetRow& InHeaderRow, IPropertyTypeCustomizationUtils& InStructCustomizationUtils) override;`

### `Plugins/VirtualProduction/SVGImporter/Source/SVGImporterEditor/Private/Customizations/SVGCategoryTypeCustomization.h` (Private)


#### class `FSVGCategoryTypeCustomization`  
`class FSVGCategoryTypeCustomization : public IDetailCustomization`  
_L7-18_
- inherits: `IDetailCustomization`
- L10 _public function_ `static TSharedRef<IDetailCustomization> MakeInstance()`
- L16 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& InDetailBuilder) override;`

### `Plugins/VirtualProduction/SVGImporter/Source/SVGImporterEditor/Private/Customizations/SVGShapeParametersDetails.h` (Private)


#### class `FSVGShapeParametersDetails`  
`class FSVGShapeParametersDetails : public IPropertyTypeCustomization`  
_L9-21_
- inherits: `IPropertyTypeCustomization`
- L12 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L15 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> InStructPropertyHandle, FDetailWidgetRow& InHeaderRow, IPropertyTypeCustomizationUtils& InStructCustomizationUtils) override;`
- L16 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> InStructPropertyHandle, IDetailChildrenBuilder& InStructBuilder, IPropertyTypeCustomizationUtils& InStructCustomizationUtils) override;`
- L20 _private member_ `TSharedPtr<SBox> HeaderValueContentBox;`

### `Plugins/VirtualProduction/SVGImporter/Source/SVGImporterEditor/Private/Factories/SVGFactory.h` (Private)


#### class `USVGFactory`  
`class USVGFactory : public UFactory`  
_L9-25_
- reflection: `UCLASS()`
- inherits: `UFactory`
- L15 _public prototype_ `virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags InFlags, UObject* InContext, FFeedbackContext* InWarn) override;`
- L16 _public prototype_ `virtual bool FactoryCanImport(const FString& InFilename) override;`
- L20 _protected prototype_ `USVGFactory(const FObjectInitializer& ObjectInitializer);`
- L23 _protected prototype_ `virtual UObject* FactoryCreateText(UClass* InClass, UObject* InParent, FName InName, EObjectFlags InFlags, UObject* InContext, const TCHAR* InType, const TCHAR*& InBuffer, const TCHAR* InBufferEnd, FFeedbackContext* InWarn) override;`

### `Plugins/VirtualProduction/SVGImporter/Source/SVGImporterEditor/Private/Factories/SVGReimportFactory.h` (Private)


#### class `USVGReimportFactory`  
`class USVGReimportFactory : public USVGFactory, public FReimportHandler`  
_L10-19_
- reflection: `UCLASS()`
- inherits: `USVGFactory,FReimportHandler`
- L15 _private prototype_ `virtual bool CanReimport(UObject* Obj, TArray<FString>& OutFilenames) override;`
- L16 _private prototype_ `virtual void SetReimportPaths(UObject* Obj, const TArray<FString>& NewReimportPaths) override;`
- L17 _private prototype_ `virtual EReimportResult::Type Reimport(UObject* Obj) override;`

### `Plugins/VirtualProduction/SVGImporter/Source/SVGImporterEditor/Private/SVGActorContextMenu.h` (Private)


#### class `FSVGActorContextMenu`  
`class FSVGActorContextMenu`  
_L12-28_
- L15 _public prototype_ `static void AddSVGActorMenuEntries(UToolMenu* InToolMenu, const TSet<TWeakObjectPtr<AActor>>& InSelectedActors);`
- L18 _private prototype_ `static bool CanAddSVGMenuEntries(const TSet<TWeakObjectPtr<AActor>>& InActors);`
- L20 _private prototype_ `static bool CanExecuteSVGActorAction(TSet<TWeakObjectPtr<AActor>> InActors);`
- L21 _private prototype_ `static void ExecuteSplitAction(TSet<TWeakObjectPtr<AActor>> InActors);`
- L23 _private prototype_ `static void ExecuteConsolidateAction(TSet<TWeakObjectPtr<AActor>> InActors);`
- L24 _private prototype_ `static bool CanExecuteConsolidateAction(TSet<TWeakObjectPtr<AActor>> InActors);`
- L26 _private prototype_ `static void ExecuteJoinAction(TSet<TWeakObjectPtr<AActor>> InActors);`
- L27 _private prototype_ `static bool CanExecuteJoinAction(TSet<TWeakObjectPtr<AActor>> InActors);`

### `Plugins/VirtualProduction/SVGImporter/Source/SVGImporterEditor/Private/SVGActorEditorComponentVisualizer.h` (Private)


#### class `FSVGActorEditorComponentVisualizer`  
`class FSVGActorEditorComponentVisualizer : public FComponentVisualizer`  
_L10-39_
- inherits: `FComponentVisualizer`
- L13 _public prototype_ `static void UpdateMinMaxExtrudeValues();`
- L15 _public prototype_ `FSVGActorEditorComponentVisualizer();`
- L18 _public prototype_ `virtual void DrawVisualization(const UActorComponent* InComponent, const FSceneView* InView, FPrimitiveDrawInterface* InPDI) override;`
- L19 _public prototype_ `virtual bool VisProxyHandleClick(FEditorViewportClient* InViewportClient, HComponentVisProxy* InVisProxy, const FViewportClick& InClick) override;`
- L20 _public prototype_ `virtual bool GetWidgetLocation(const FEditorViewportClient* InViewportClient, FVector& OutLocation) const override;`
- L21 _public prototype_ `virtual bool HandleInputDelta(FEditorViewportClient* InViewportClient, FViewport* InViewport, FVector& InDeltaTranslate, FRotator& InDeltaRotate, FVector& InDeltaScale) override;`
- L22 _public prototype_ `virtual void EndEditing() override;`
- L23 _public prototype_ `virtual void TrackingStopped(FEditorViewportClient* InViewportClient, bool bInDidMove) override;`
- L24 _public prototype_ `virtual UActorComponent* GetEditedComponent() const override;`
- L28 _private prototype_ `FVector GetExtrudeWidgetLocation() const;`
- L29 _private prototype_ `FVector GetExtrudeSurfaceLocation() const;`
- L31 _private member_ `static float FillsExtrudeMin;`
- L32 _private member_ `static float FillsExtrudeMax;`
- L33 _private member_ `static float StrokesExtrudeMin;`
- L34 _private member_ `static float StrokesExtrudeMax;`
- L36 _private member_ `TWeakObjectPtr<USVGActorEditorComponent> SVGEditorComponentWeak;`
- L37 _private member_ `TWeakObjectPtr<ASVGActor> SVGActorWeak;`
- L38 _private member_ `bool bIsExtruding = false;`

### `Plugins/VirtualProduction/SVGImporter/Source/SVGImporterEditor/Private/SVGDynamicMeshVisualizer.h` (Private)


#### class `FSVGDynamicMeshVisualizer`  
`class FSVGDynamicMeshVisualizer : public FComponentVisualizer`  
_L7-11_
- inherits: `FComponentVisualizer`
- L10 _public prototype_ `virtual void DrawVisualization(const UActorComponent* InComponent, const FSceneView* InView, FPrimitiveDrawInterface* InPDI) override;`

### `Plugins/VirtualProduction/SVGImporter/Source/SVGImporterEditor/Private/SVGImporterEditorModule.h` (Private)


#### class `FSVGImporterEditorModule`  
`class FSVGImporterEditorModule : public ISVGImporterEditorModule`  
_L14-52_
- inherits: `ISVGImporterEditorModule`
- L17 _public prototype_ `static void AddSVGActorFromClipboardMenuEntry(UToolMenu* InMenu);`
- L18 _public prototype_ `static void AddSVGActorEntriesToLevelEditorContextMenu(UToolMenu* InMenu);`
- L21 _public prototype_ `virtual void StartupModule() override;`
- L22 _public prototype_ `virtual void ShutdownModule() override;`
- L27 _public function_ `virtual const FName GetStyleName() const override`
- L32 _public function_ `virtual FName GetSVGImporterMenuCategoryName() const override`
- L37 _public prototype_ `virtual void AddSVGActorMenuEntries(UToolMenu* InMenu, TSet<TWeakObjectPtr<AActor>> InActors) override;`
- L41 _protected prototype_ `static void CreateSVGActorFromClipboard(ULevel* InLevel);`
- L42 _protected prototype_ `static void RegisterContextMenuExtender();`
- L43 _protected prototype_ `static bool CanCreateSVGActorFromClipboard(ULevel* InLevel);`
- L44 _protected prototype_ `static FUIAction CreatePasteSVGActorAction(ULevel* InLevel);`
- L45 _protected function_ `static FName GetMenuCategoryName()`
- L47 _protected prototype_ `void PostEngineInit();`
- L49 _protected prototype_ `USVGData* OnDefaultSVGDataRequested();`
- L51 _protected member_ `static FName SVGImporterCategoryName;`

#### Free symbols / members of external scopes

- L12 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(SVGImporterEditorLog, Log, All);`
- L12 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(SVGImporterEditorLog, Log, All);`

### `Plugins/VirtualProduction/SVGImporter/Source/SVGImporterEditor/Private/SVGImporterEditorStyle.h` (Private)


#### class `FSVGImporterEditorStyle`  
`class FSVGImporterEditorStyle : public FSlateStyleSet`  
_L7-19_
- inherits: `FSlateStyleSet`
- L10 _public prototype_ `FSVGImporterEditorStyle();`
- L14 _public function_ `static FSVGImporterEditorStyle& Get()`

### `Plugins/VirtualProduction/SVGImporter/Source/SVGImporterEditor/Private/SVGImporterEditorUtils.h` (Private)


#### class `FSVGImporterEditorUtils`  
`class FSVGImporterEditorUtils`  
_L27-275_
- L103 _public prototype_ `static USVGData* CreateSVGDataFromTextBuffer(const FString& InSVGTextBuffer, UObject* InOuter, const FName InName, EObjectFlags InFlags, const FString& InSVGFileName = TEXT(""));` — Creates a new SVGData from the specified Text Buffer @param InSVGTextBuffer Text buffer containing the SVG text @param InOuter Outer for the newly created SVGData @param InName Name for the SVGData Object @param InFlags Desired Object Flags @param InSVGFileName If the SVG Text buffer is taken from a file, it is possible specify here its name @return the newly created SVGData. Can be nullptr if parsing of SVG text buffer fails.
- L111 _public prototype_ `static bool RefreshSVGDataFromTextBuffer(USVGData* InSVGData, const FString& InSVGTextBuffer);` — Refresh an existing SVGData using the specified Text Buffer @param InSVGData The SVGData object to update @param InSVGTextBuffer Text buffer containing the SVG text @return the newly created SVGData. Can be nullptr if parsing of SVG text buffer fails.
- L120 _public prototype_ `static TSharedPtr<FSVGDataInitializer> GetInitializerFromSVGData(const FString& InSVGTextBuffer, const FString& InSVGFileName = TEXT(""));` — Creates a SVGDataInitializer struct which can be used to initialize a new SVGData, or refresh a new one @param InSVGTextBuffer Text buffer containing the SVG text @param InSVGFileName If the SVG Text buffer is taken from a file, it is possible specify here its name @return the FSVGDataInitializer. It will contain the hierarchy of SVG Elements needed to properly setup SVGData objects, the content of the SVG, and the filename, when available.
- L127 _public prototype_ `static void ParseRootRawElement(const TSharedRef<FSVGRawElement>& InRootElement, FSVGParsedElements& OutParsedElements);` — Converts the hierarchy starting from the specified SVG Raw Element to a list of more specialized SVG Base Elements which can be used to generate geometry @param InRootElement the SVG root element obtained after parsing an SVG Text Buffer @param OutParsedElements the output struct of SVG Parsed Elements. New Elements and required data (e.g. style information) will be added to this list.
- L136 _private prototype_ `static void ParseSVGElement(const TSharedRef<FSVGRawElement>& InElement, FSVGParsedElements& OutParsedElements, TSharedPtr<FSVGBaseElement> InParent);` — Converts the hierarchy starting from the specified SVG Raw Element to a list of more specialized SVG Base Elements which can be used to generate geometry @param InElement the SVG element to parse @param OutParsedElements the output struct of SVG Parsed Elements. New Elements and required data (e.g. style information) will be added to this list. @param InParent the parent of the specified Element. Can be null (e.g. when parsing root elements)
- L143 _private prototype_ `static TSharedRef<FSVGBaseElement> CreateSVGElement(const TSharedRef<FSVGRawElement>& InElement);` — Will create a specialized SVG Base Element. Specialization will be based on the current arguments of the specified Raw Element. @param InElement the SVG element from which the specialized Element will be created @return the newly created Base Element
- L151 _private prototype_ `static void SetGraphicsElementCommonValues(const TSharedPtr<FSVGGraphicsElement>& InGraphicalElement, const FSVGAttributesMap& InAttributesMap);` — Graphical SVG Elements share a common set of attributes. This function will set those attributes, where possible, using the specified Attributes Map @param InGraphicalElement the element to update @param InAttributesMap the attributes used to update the Graphical Element
- L154 _private prototype_ `static bool IsValidGroup(const TSharedRef<FSVGRawElement>& InElement);` — Is this Raw Element a Group?
- L157 _private prototype_ `static bool IsValidSVG(const TSharedRef<FSVGRawElement>& InElement);` — Is this Raw Element an SVG?
- L160 _private prototype_ `static bool IsValidStyle(const TSharedRef<FSVGRawElement>& InElement);` — Is this Raw Element a Style?
- L163 _private prototype_ `static bool IsValidClipPath(const TSharedRef<FSVGRawElement>& InElement);` — Is this Raw Element a Clip Path?
- L166 _private prototype_ `static bool IsValidLinearGradient(const TSharedRef<FSVGRawElement>& InElement);` — Is this Raw Element a Linear Gradient?
- L169 _private prototype_ `static bool IsValidRadialGradient(const TSharedRef<FSVGRawElement>& InElement);` — Is this Raw Element a Radial Gradient?
- L172 _private prototype_ `static bool IsValidCircle(const TSharedRef<FSVGRawElement>& InElement);` — Is this Raw Element a Circle?
- L175 _private prototype_ `static bool IsValidEllipse(const TSharedRef<FSVGRawElement>& InElement);` — Is this Raw Element an Ellipse?
- L178 _private prototype_ `static bool IsValidRectangle(const TSharedRef<FSVGRawElement>& InElement);` — Is this Raw Element a Rectangle?
- L181 _private prototype_ `static bool IsValidLine(const TSharedRef<FSVGRawElement>& InElement);` — Is this Raw Element a Line?
- L184 _private prototype_ `static bool IsValidPolyLine(const TSharedRef<FSVGRawElement>& InElement);` — Is this Raw Element a Poly Line?
- L187 _private prototype_ `static bool IsValidPolygon(const TSharedRef<FSVGRawElement>& InElement);` — Is this Raw Element a Polygon?
- L190 _private prototype_ `static bool IsValidPath(const TSharedRef<FSVGRawElement>& InElement);` — Is this Raw Element a Path?
- L193 _private prototype_ `static TSharedRef<FSVGMainElement> CreateSVG();` — Creates an SVG Element
- L196 _private prototype_ `static TSharedRef<FSVGGroupElement> CreateGroup(const FSVGAttributesMap& InAttributesMap);` — Creates a Group Element using the specified Attributes and Outer
- L199 _private prototype_ `static TSharedRef<FSVGClipPath> CreateClipPath();` — Creates a Path Element
- L202 _private prototype_ `static TSharedRef<FSVGStyleElement> CreateStyle(const FString& InCSS_String);` — Creates a Style Element using the specified CSS String and Outer
- L205 _private prototype_ `static TArray<FSVGGradientStop> GetGradientStops(const TSharedRef<FSVGRawElement>& InElement);` — Retrieve the list of gradient stops from the specified Elements, if any
- L208 _private prototype_ `static TSharedRef<FSVGGradientElement> CreateGradient(const FSVGAttributesMap& InAttributesMap, const TArray<FSVGGradientStop>& InGradientStops);` — Creates a Gradient Element
- L211 _private prototype_ `static TSharedRef<FSVGCircle> CreateCircle(const FSVGAttributesMap& InAttributesMap);` — Creates a Circle Element using the specified Attributes and Outer
- L214 _private prototype_ `static TSharedRef<FSVGEllipse> CreateEllipse(const FSVGAttributesMap& InAttributesMap);` — Creates an Ellipse Element using the specified Attributes and Outer
- L217 _private prototype_ `static TSharedRef<FSVGRectangle> CreateRectangle(const FSVGAttributesMap& InAttributesMap);` — Creates a Rectangle Element using the specified Attributes and Outer
- L220 _private prototype_ `static TSharedRef<FSVGLine> CreateLine(const FSVGAttributesMap& InAttributesMap);` — Creates a Line Element using the specified Attributes and Outer
- L223 _private prototype_ `static TSharedRef<FSVGPolyLine> CreatePolyLine(const FSVGAttributesMap& InAttributesMap);` — Creates a Poly Line Elemen using the specified Attributes and Outer
- L226 _private prototype_ `static TSharedRef<FSVGPolygon> CreatePolygon(const FSVGAttributesMap& InAttributesMap);` — Creates a Polygon Element using the specified Attributes and Outer
- L229 _private prototype_ `static TSharedRef<FSVGPath> CreatePath(const FSVGAttributesMap& InAttributesMap);` — Creates a Path Element using the specified Attributes and Outer
- L232 _private prototype_ `static bool HasAttribute(const FName InAttributeName, const FSVGAttributesMap& InAttributes);` — Checks if the specified Attributes map contains an Attribute
- L235 _private prototype_ `static TSharedPtr<FSVGRawAttribute> GetAttribute(const FName InAttributeName, const FSVGAttributesMap& InAttributes);` — Returns the specified Attribute from the specified Attributes Map
- L244 _private prototype_ `static void GetRxAndRy(const FSVGAttributesMap& InAttributesMap, float& OutRx, float& OutRy);` — Get Horizontal and Vertical Radius Values from the specified AttributesMap, if available. Rx and Ry default value is auto When Rx is auto, the used radius is equal to the absolute length used for Ry (generates a circular arc) If both Rx and Ry are auto, used value is 0
- L247 _private prototype_ `static void GetCxAndCy(const FSVGAttributesMap& InAttributesMap, float& OutCx, float& OutCy);` — Get both Cx and Cy Coordinates from the specified AttributesMap, if available
- L250 _private prototype_ `static void GetXAndY(const FSVGAttributesMap& InAttributesMap, float& OutX, float& OutY);` — Get both X and Y Coordinates from the specified AttributesMap, if available
- L253 _private prototype_ `static void GetWidthAndHeight(const FSVGAttributesMap& InAttributesMap, float& OutWidth, float& OutHeight);` — Get both Width and Height Coordinates from the specified AttributesMap, if available
- L256 _private prototype_ `static float GetCx(const FSVGAttributesMap& InAttributesMap);` — Get Horizontal Center Value from the specified AttributesMap, if available
- L259 _private prototype_ `static float GetCy(const FSVGAttributesMap& InAttributesMap);` — Get Vertical Center Value from the specified AttributesMap, if available
- L262 _private prototype_ `static float GetR(const FSVGAttributesMap& InAttributesMap);` — Get Radius Value from the specified AttributesMap, if available
- L265 _private prototype_ `static float GetX(const FSVGAttributesMap& InAttributesMap);` — Get Horizontal Coordinate Value from the specified AttributesMap, if available
- L268 _private prototype_ `static float GetY(const FSVGAttributesMap& InAttributesMap);` — Get Vertical Coordinate Value from the specified AttributesMap, if available
- L271 _private prototype_ `static float GetWidth(const FSVGAttributesMap& InAttributesMap);` — Get Width Value from the specified AttributesMap, if available
- L274 _private prototype_ `static float GetHeight(const FSVGAttributesMap& InAttributesMap);` — Get Height Value from the specified AttributesMap, if available

#### struct `FSVGImporterEditorUtils::FSVGParsedElements`  
`struct FSVGParsedElements : public TSharedFromThis<FSVGParsedElements>`  
_L32-91_
- inherits: `TSharedFromThis<FSVGParsedElements>`
- desc: Struct used to hold and store data during XML --> SVG parsing
- L35 _public prototype_ `const TArray<TSharedRef<FSVGBaseElement>>& GetOutElements() const;` — Get all parsed SVG elements. Will also call ApplyStyle() if needed, so that CSS style classes are applied to elements requiring it
- L38 _public prototype_ `void AddElement(const TSharedRef<FSVGBaseElement>& InElement);` — Register a parsed SVG Element. If needed, style class info can be applied at the end of parsing by calling ApplyStyles()
- L41 _public prototype_ `void AddStyleElement(const TSharedRef<FSVGStyleElement>& InStyle);` — Register a Style Element to be applied later via ApplyStyles()
- L44 _public prototype_ `void AddGradientElement(const TSharedRef<FSVGGradientElement>& InGradientElement);` — Register a Gradient Element to be applied later
- L48 _protected prototype_ `void ApplyStyles();` — Apply Style Elements to Parsed Graphics Elements, as needed
- L51 _protected prototype_ `void ApplyGradients();` — Apply gradients, as needed
- L54 _protected prototype_ `void MarkHiddenElements();` — Marks shapes as non visible, based on the "Display" attribute
- L57 _protected prototype_ `void ApplyPendingData();` — Applies all pending data (e.g. styles, gradients, visibility)
- L60 _protected prototype_ `bool HasStyleClass(const FString& InClassName) const;` — Checks whether the specified Class is available
- L63 _protected prototype_ `bool HasGradient(const FString& InGradientID) const;` — Checks whether the specified Gradient is available
- L66 _protected prototype_ `void MarkIfMissingStyle(const TSharedRef<FSVGGraphicsElement>& InGraphicElement);` — If the specified Element needs a style class which is not available yet, let's register it for later update
- L69 _protected prototype_ `void MarkIfMissingGradients(const TSharedRef<FSVGGraphicsElement>& InGraphicElement);` — If the specified Element needs a gradient which is not available yet, let's register it for later update
- L72 _protected member_ `TArray<TSharedRef<FSVGStyleElement>> StyleElements;` — Style Elements containing style classes which should be applied to StyledGraphicsElementsMap once parsing is finished
- L75 _protected member_ `TArray<TSharedRef<FSVGGradientElement>> GradientElements;` — Gradient Elements containing gradients to be applied once parsing is finished
- L78 _protected member_ `TArray<TSharedRef<FSVGBaseElement>> OutElements;` — The elements needed to generate the 3D geometry for this SVG Data
- L81 _protected member_ `TMap<FString, TArray<TSharedRef<FSVGGraphicsElement>>> StyledGraphicsElementsMap;` — Graphics elements needing style from style classes
- L84 _protected member_ `TMap<FString, TArray<TSharedRef<FSVGGraphicsElement>>> GradientGraphicsElementsMap;` — Graphics elements needing gradient info
- L87 _protected member_ `bool bStyleHaveBeenApplied = false;` — Set to true after calling ApplyStyle, set to false when Graphic Elements or StyleElements are updated.
- L90 _protected member_ `bool bGradientsHaveBeenApplied = false;` — Set to true after calling ApplyGradients, set to false when Graphic Elements or GradientElements are updated.

#### Free symbols / members of external scopes

- L25 _typedef_ `typedef TMap<FName, TSharedPtr<FSVGRawAttribute>> FSVGAttributesMap;`

### `Plugins/VirtualProduction/SVGImporter/Source/SVGImporterEditor/Private/SVGParser_Base.h` (Private)


#### class `FSVGParser_Base`  
`class FSVGParser_Base : public TSharedFromThis<FSVGParser_Base>`  
_L21-64_
- inherits: `TSharedFromThis<FSVGParser_Base>`
- desc: Base class used to implement specialized XML parsers to parse SVG Text Buffers. Parser outputs the Root of a hierarchy of SVG Raw Elements. From that root, it is possible to explore all Elements.
- L24 _public prototype_ `FSVGParser_Base() = delete;`
- L30 _public function_ `FSVGParser_Base(const FString& InStringToParse) :SVGString(InStringToParse)` — Creates the SVG Parser @param InStringToParse the string to be parsed
- L34 _public prototype_ `virtual ~FSVGParser_Base() = default;`
- L40 _public prototype_ `virtual bool Parse(bool bInTryImportAnyway = true) = 0;` — Parse the stored string. Returns true if parsing is successful. @param bInTryImportAnyway if parser fails, ask the user if they want to try importing the SVG anyway
- L43 _public prototype_ `virtual bool IsValidSVG() = 0;` — Returns true if the stored string is a valid SVG string (it has an SVG xml tag)
- L46 _public function_ `const TSharedPtr<FSVGRawElement>& GetRootElement()` — Return the Root of the Parsed SVG Hierarchy. Root Element will be set after a successful parsing
- L49 _protected function_ `static EAppReturnType::Type ShowErrorMessageDialog(const FFormatNamedArguments& InArgs)`
- L57 _protected member_ `FString SVGString;` — The string to be parsed
- L60 _protected member_ `TSharedPtr<FSVGRawElement> RootSVGElement;` — The root of the SVG hierarchy, stored so that we can build it throughout XML/SVG parser callbacks
- L63 _protected member_ `TArray<TSharedPtr<FSVGRawElement>> SVGElements;` — Array containing all the SVG elements found by the parser

#### Free symbols / members of external scopes

- L14 _macro_ `#define LOCTEXT_NAMESPACE "SVGParser_Base"`

### `Plugins/VirtualProduction/SVGImporter/Source/SVGImporterEditor/Private/SVGParser_FastXml.h` (Private)


#### class `FSVGParser_FastXml`  
`class FSVGParser_FastXml : public FSVGParser_Base, public IFastXmlCallback`  
_L11-43_
- inherits: `FSVGParser_Base,IFastXmlCallback`
- desc: SVG Parser based on FastXml parser
- L19 _public function_ `FSVGParser_FastXml(const FString& InStringToParse, bool bInCheckForSVGTagOnly = false) : FSVGParser_Base(InStringToParse) , bCheckForSVGTagOnly(bInCheckForSVGTagOnly)` — @param InStringToParse the string to be parsed @param bInCheckForSVGTagOnly if true, when the parser will run, it will only check for the presence of an SVG Tag. Useful to use the parser to quickly check if parsed string contains SVG info
- L26 _public prototype_ `virtual bool Parse(bool bInTryToImportWithError = true) override;`
- L27 _public prototype_ `virtual bool IsValidSVG() override;`
- L32 _protected prototype_ `virtual bool ProcessXmlDeclaration(const TCHAR* InElementData, int32 InXmlFileLineNumber) override;`
- L33 _protected prototype_ `virtual bool ProcessElement(const TCHAR* InElementName, const TCHAR* InElementData, int32 InXmlFileLineNumber) override;`
- L34 _protected prototype_ `virtual bool ProcessAttribute(const TCHAR* InAttributeName, const TCHAR* InAttributeValue) override;`
- L35 _protected prototype_ `virtual bool ProcessClose(const TCHAR* InElementName) override;`
- L36 _protected function_ `virtual bool ProcessComment(const TCHAR* InComment) override`
- L40 _private member_ `bool bHasBeenParsed = false;`
- L41 _private member_ `bool bCheckForSVGTagOnly = false;`
- L42 _private member_ `bool bHasSVGTag = false;`

### `Plugins/VirtualProduction/SVGImporter/Source/SVGImporterEditor/Private/SVGParser_PugiXml.h` (Private)


#### class `FSVGParser_PugiXml`  
`class FSVGParser_PugiXml : public FSVGParser_Base`  
_L12-36_
- inherits: `FSVGParser_Base`
- desc: SVG Parser based on pugi xml parser
- L15 _public function_ `FSVGParser_PugiXml(const FString& InStringToParse) : FSVGParser_Base(InStringToParse)`
- L20 _public prototype_ `virtual bool Parse(bool bInTryToImportWithError = true) override;`
- L21 _public prototype_ `virtual bool IsValidSVG() override;`
- L26 _protected prototype_ `void ParseXML();` — Parse the XML text buffer. This will not populate the SVG hierarchy yet.
- L29 _protected prototype_ `void ParseNode(const pugi::xml_node& InNode, const TSharedPtr<FSVGRawElement>& InParent);` — Recursively parse a node and its children nodes
- L32 _protected member_ `TSharedPtr<pugi::xml_document> XmlDoc;` — The pugi xml document which will be used for parsing
- L35 _protected member_ `pugi::xml_parse_result XmlParseResult;` — Result of xml parsing

### `Plugins/VirtualProduction/SVGImporter/Source/SVGImporterEditor/Private/SVGParsingUtils.h` (Private)


#### class `FSVGParsingUtils`  
`class FSVGParsingUtils`  
_L12-146_
- L29 _public prototype_ `static TSharedRef<FSVGParser_Base> CreateSVGParser(const FString& InStringToParse, ESVGParserType InParserType = ESVGParserType::SVGPugiXml);` — Create SVGParser to parse svg strings @param InStringToParse the SVG String to parse @param InParserType the type of parser to use @return the SVG Parser
- L32 _public prototype_ `static bool IsValidSVGString(const FString& InStringToParse);` — Does the specified string correspond to a valid SVG?
- L35 _public prototype_ `static float FloatFromString(const FString& InFloatString);` — Parse the provided SVG String as a float
- L38 _public prototype_ `static TArray<float> FloatsFromString(FString InFloatsString, bool bApplyScaling = true);` — Parse the provided SVG String as a list of float values
- L44 _public prototype_ `static bool FloatFromStringWithSuffix(const FString& InFloatString, const FString& InSuffix, float& OutValue);` — Parse the provided SVG String as a float, removing the specified suffix. Useful for numbers with a suffix (e.g. percentage for some gradients)
- L47 _public prototype_ `static void PointsFromString(FString InPointsString, TArray<FVector2D>& OutPoints);` — Parse the provided SVG String as a list of 2D Points
- L50 _public prototype_ `static int32 ParseIntoCommandsArrayKeepDelimiters(const FString& InSourceString, TArray<FString>& OutArray, const TCHAR* const * DelimArray, int32 NumDelims, bool InCullEmpty);` — Parses the SVG String as a list of SVG Commands, keeping the inner delimiters for each Command
- L60 _public prototype_ `static FVector2D PathMoveTo(TArray<FSVGPathCommand>& OutCommands, FVector2D& InOutCursorPos, const TArray<FVector2D>& InArguments, bool bInIsRelative);` — Adds a Move To instruction to the provided Commands list. @param OutCommands required command will be added to this list @param InOutCursorPos cursor position to be used and updated while parsing the arguments @param InArguments instruction arguments @param bInIsRelative instruction can be relative or absolute @return the initial position of the sub path starting with this MoveTo operation. Should be used to later perform a ClosePath if needed.
- L69 _public prototype_ `static void PathLineTo(TArray<FSVGPathCommand>& OutCommands, FVector2D& InOutCursorPos, const TArray<FVector2D>& InArguments, bool bInIsRelative);` — Adds a Line To instruction to the provided Commands list. @param OutCommands required command will be added to this list @param InOutCursorPos cursor position to be used and updated while parsing the arguments @param InArguments instruction arguments @param bInIsRelative instruction can be relative or absolute
- L78 _public prototype_ `static void PathHorizontalLineTo(TArray<FSVGPathCommand>& OutCommands, FVector2D& InOutCursorPos, const TArray<float>& InArguments, bool bInIsRelative);` — Adds a Horizontal Line To instruction to the provided Commands list. @param OutCommands required command will be added to this list @param InOutCursorPos cursor position to be used and updated while parsing the arguments @param InArguments instruction arguments @param bInIsRelative instruction can be relative or absolute
- L87 _public prototype_ `static void PathVerticalLineTo(TArray<FSVGPathCommand>& OutCommands, FVector2D& InOutCursorPos, const TArray<float>& InArguments, bool bInIsRelative);` — Adds a Vertical Line To instruction to the provided Commands list. @param OutCommands required command will be added to this list @param InOutCursorPos cursor position to be used and updated while parsing the arguments @param InArguments instruction arguments @param bInIsRelative instruction can be relative or absolute
- L97 _public prototype_ `static void PathCubicBezierTo(TArray<FSVGPathCommand>& OutCommands, FVector2D& InOutCursorPos, FVector2D& InOutCursorPos2, const TArray<FVector2D>& InArguments, bool bInIsRelative);` — Adds a Cubic Bezier To instruction to the provided Commands list. @param OutCommands required command will be added to this list @param InOutCursorPos first cursor position to be used and updated while parsing the arguments @param InOutCursorPos2 second cursor position to be used and updated while parsing the arguments @param InArguments instruction arguments @param bInIsRelative instruction can be relative or absolute
- L107 _public prototype_ `static void PathCubicBezierSmoothTo(TArray<FSVGPathCommand>& OutCommands, FVector2D& InOutCursorPos, FVector2D& InOutCursorPos2, const TArray<FVector2D>& InArguments, bool bInIsRelative);` — Adds a Smooth Cubic Bezier To instruction to the provided Commands list. @param OutCommands required command will be added to this list @param InOutCursorPos first cursor position to be used and updated while parsing the arguments @param InOutCursorPos2 second cursor position to be used and updated while parsing the arguments @param InArguments instruction arguments @param bInIsRelative instruction can be relative or absolute
- L117 _public prototype_ `static void PathQuadraticBezierTo(TArray<FSVGPathCommand>& OutCommands, FVector2D& InOutCursorPos, FVector2D& InOutCursorPos2, const TArray<FVector2D>& InArguments, bool bInIsRelative);` — Adds a Quadratic Bezier To instruction to the provided Commands list. @param OutCommands required command will be added to this list @param InOutCursorPos first cursor position to be used and updated while parsing the arguments @param InOutCursorPos2 second cursor position to be used and updated while parsing the arguments @param InArguments instruction arguments @param bInIsRelative instruction can be relative or absolute
- L127 _public prototype_ `static void PathQuadraticBezierSmoothTo(TArray<FSVGPathCommand>& OutCommands, FVector2D& InOutCursorPos, FVector2D& InOutCursorPos2, const TArray<FVector2D>& InArguments, bool bInIsRelative);` — Adds a Smooth Quadratic Bezier To instruction to the provided Commands list. @param OutCommands required command will be added to this list @param InOutCursorPos first cursor position to be used and updated while parsing the arguments @param InOutCursorPos2 second cursor position to be used and updated while parsing the arguments @param InArguments instruction arguments @param bInIsRelative instruction can be relative or absolute
- L136 _public prototype_ `static void PathArcTo(TArray<FSVGPathCommand>& OutCommands, FVector2D& InOutCursorPos, const TArray<float>& InArguments, bool bInIsRelative);` — Adds a Path Arc To instruction to the provided Commands list. @param OutCommands required command will be added to this list @param InOutCursorPos cursor position to be used and updated while parsing the arguments @param InArguments instruction arguments @param bInIsRelative instruction can be relative or absolute
- L139 _public prototype_ `static TArray<TArray<FSVGPathCommand>> ParseStringAsPathCommands(const FString& InString);` — Parses the specified SVG string as a list of path commands
- L141 _public prototype_ `static bool IsURLString(const FString& InString);`
- L143 _public prototype_ `static FString ExtractURL(const FString& InString);`
- L145 _public prototype_ `static bool IsVisible(const TSharedRef<FSVGRawAttribute>& InAttribute);`

#### enum `FSVGParsingUtils::ESVGParserType`  
`enum class ESVGParserType : uint8`  
_L17-21_
- desc: List of available SVG Parsers
- L19 _public enumerator_ `SVGFastXml`
- L20 _public enumerator_ `SVGPugiXml`

### `Plugins/VirtualProduction/SVGImporter/Source/SVGImporterEditor/Private/SVGThumbnailRenderer.h` (Private)


#### class `USVGThumbnailRenderer`  
`class USVGThumbnailRenderer : public UDefaultSizedThumbnailRenderer`  
_L10-18_
- reflection: `UCLASS()`
- inherits: `UDefaultSizedThumbnailRenderer`
- L15 _private prototype_ `virtual bool CanVisualizeAsset(UObject* Object) override;`
- L16 _private prototype_ `virtual void Draw(UObject* Object, int32 X, int32 Y, uint32 Width, uint32 Height, FRenderTarget*, FCanvas* Canvas, bool bAdditionalViewFamily) override;`

### `Plugins/VirtualProduction/SVGImporter/Source/SVGImporterEditor/Private/Types/SVGRawAttribute.h` (Private)


#### struct `FSVGRawAttribute`  
`struct FSVGRawAttribute : public FSVGRawItem`  
_L14-49_
- inherits: `FSVGRawItem`
- desc: Specialization of SVG Items, representing SVG Attributes
- L18 _public prototype_ `static TSharedRef<FSVGRawAttribute> NewSVGAttribute(const TSharedPtr<FSVGRawElement>& InParentElement, const FName& InName, const FString& InValue);` — Create a Raw Attribute shared ref
- L21 _public prototype_ `void AsPoints(TArray<FVector2D>& OutPoints) const;` — Converts this Attribute Value to a list of FVector2D points
- L24 _public prototype_ `void PrintDebugInfo() const;` — Prints the name and value of this Attribute
- L27 _public prototype_ `float AsFloat() const;` — Convert this Attribute Value to a float
- L30 _public prototype_ `bool AsFloatWithSuffix(const FString& InSuffix, float& OutValue) const;` — Convert this Attribute Value to a float. Useful for numbers with a suffix (e.g. percentage for some gradients)
- L33 _public prototype_ `FString AsString() const;` — Returns the plain String Attribute Value
- L36 _public prototype_ `TArray<TArray<FSVGPathCommand>> AsPathCommands() const;` — Parse the SVG String as a path. Returns the list of commands describing the path
- L41 _public function_ `FSVGRawAttribute(FPrivateToken, const TSharedRef<FSVGRawItem>& InParent, const FName& InName, const FString& InValue)`
- L48 _public prototype_ `FSVGRawAttribute() = default;`

#### struct `FSVGRawAttribute::FPrivateToken`  
`struct FPrivateToken`  
_L39-39_
- L39 _public prototype_ `struct FPrivateToken`

### `Plugins/VirtualProduction/SVGImporter/Source/SVGImporterEditor/Private/Types/SVGRawElement.h` (Private)


#### struct `FSVGRawElement`  
`struct FSVGRawElement : public FSVGRawItem`  
_L17-62_
- inherits: `FSVGRawItem`
- desc: FSVGRawElement: Elements, directly as parsed by the SVG parser (string values). - They have references to their children elements. - They can contain FSVGAttributes
- L21 _public prototype_ `static TSharedRef<FSVGRawElement> NewSVGElement(const TSharedPtr<FSVGRawElement>& InParentElement, const FName& InName, const FString& InValue);` — Create a Raw Element Shared Ref
- L24 _public prototype_ `void AddChild(const TSharedRef<FSVGRawElement>& InChild);` — Adds a child Element to this Element
- L27 _public prototype_ `void AddAttribute(const TSharedRef<FSVGRawAttribute>& InAttribute);` — Adds an Attribute to this Element
- L30 _public prototype_ `void PrintDebugInfo();` — Prints information about this Element (own Attributes and Children)
- L33 _public prototype_ `bool HasAttribute(const FName& InAttributeName) const;` — Checks if this Element has the specified Attribute
- L36 _public prototype_ `TSharedPtr<FSVGRawAttribute> GetAttribute(const FName& InAttributeName);` — Retrieves the specified Attribute
- L39 _public function_ `const TArray<TSharedPtr<FSVGRawElement>>& GetChildren() const` — Get Children attached to this Element
- L42 _public function_ `const TMap<FName, TSharedPtr<FSVGRawAttribute>>& GetAttributes() const` — Get Attributes of this Element
- L46 _private member_ `TArray<TSharedPtr<FSVGRawElement>> ChildrenElements;` — A list of Children Elements
- L49 _private member_ `TMap<FName, TSharedPtr<FSVGRawAttribute>> AttributesMap;` — A Map containing all the Attributes of this Element, indexed by name
- L54 _public function_ `FSVGRawElement(FPrivateToken, const TSharedRef<FSVGRawItem>& InParent, const FName& InName, const FString& InValue)`
- L61 _public prototype_ `FSVGRawElement() = default;`

#### struct `FSVGRawElement::FPrivateToken`  
`struct FPrivateToken`  
_L51-51_
- L51 _public prototype_ `struct FPrivateToken`

### `Plugins/VirtualProduction/SVGImporter/Source/SVGImporterEditor/Private/Types/SVGRawItem.h` (Private)


#### struct `FSVGRawItem`  
`struct FSVGRawItem`  
_L12-31_
- desc: Base for non-converted SVG Elements and Attributes SVGRawItems store the parsed information from the SVG as it is. Therefore, they need to be converted in order to be used in engine.
- L16 _public function_ `FSVGRawItem()`
- L19 _public function_ `FSVGRawItem(const TSharedRef<FSVGRawItem>& InParent, const FName& InName, const FString& InValue) : Parent(InParent), Name(InName), Value(InValue)`
- L24 _public member_ `TSharedPtr<FSVGRawItem> Parent = nullptr;` — The parent of this Item
- L27 _public member_ `FName Name = NAME_None;` — The name of this Item
- L30 _public member_ `FString Value = TEXT("");` — The value of this item, as taken from the SVG text buffer

### `Plugins/VirtualProduction/SVGImporter/Source/SVGImporterEditor/Public/Factories/SVGActorFactory.h` (Public)


#### class `USVGActorFactory`  
`class USVGActorFactory : public UActorFactory`  
_L9-22_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UActorFactory`
- L13 _private prototype_ `USVGActorFactory(const FObjectInitializer& ObjectInitializer);`
- L17 _protected prototype_ `virtual bool CanCreateActorFrom(const FAssetData& AssetData, FText& OutErrorMsg) override;`
- L18 _protected prototype_ `virtual AActor* GetDefaultActor(const FAssetData& AssetData) override;`
- L19 _protected prototype_ `virtual AActor* SpawnActor(UObject* InAsset, ULevel* InLevel, const FTransform& InTransform, const FActorSpawnParameters& InSpawnParams) override;`
- L20 _protected prototype_ `virtual void PostPlaceAsset(TArrayView<const FTypedElementHandle> InHandle, const FAssetPlacementInfo& InPlacementInfo, const FPlacementOptions& InPlacementOptions) override;`

### `Plugins/VirtualProduction/SVGImporter/Source/SVGImporterEditor/Public/ISVGImporterEditorModule.h` (Public)


#### class `ISVGImporterEditorModule`  
`class ISVGImporterEditorModule : public IModuleInterface`  
_L12-32_
- inherits: `IModuleInterface`
- L14 _private member_ `static constexpr const TCHAR* ModuleName = TEXT("SVG`
- L17 _public function_ `static bool IsLoaded()`
- L22 _public function_ `static ISVGImporterEditorModule& Get()`
- L27 _public prototype_ `virtual const FName GetStyleName() const = 0;`
- L29 _public prototype_ `virtual FName GetSVGImporterMenuCategoryName() const = 0;`
- L31 _public prototype_ `virtual void AddSVGActorMenuEntries(UToolMenu* InMenu, TSet<TWeakObjectPtr<AActor>> InActors) = 0;`

### `Plugins/VirtualProduction/SVGImporter/Source/SVGImporterEditor/Public/SVGImporterEditorCommands.h` (Public)


#### class `FSVGImporterEditorCommands`  
`class FSVGImporterEditorCommands : public TCommands<FSVGImporterEditorCommands>`  
_L7-25_
- inherits: `TCommands<FSVGImporterEditorCommands>`
- L10 _public prototype_ `static const FSVGImporterEditorCommands& GetExternal();`
- L12 _public prototype_ `static const FSVGImporterEditorCommands& GetInternal();`
- L14 _public prototype_ `FSVGImporterEditorCommands();`
- L17 _public prototype_ `virtual void RegisterCommands() override;`
- L20 _public member_ `TSharedPtr<FUICommandInfo> SpawnSVGActor;`
