# Plugins / WorldConditionsEditor

- module root: `Plugins/Runtime/WorldConditions/Source/WorldConditionsEditor`
- headers: 5; symbols: 70
- symbol kinds: class=5, function=2, member=18, prototype=45

### `Plugins/Runtime/WorldConditions/Source/WorldConditionsEditor/Private/Customizations/WorldConditionContextDataRefDetails.h` (Private)


#### class `FWorldConditionContextDataRefDetails`  
`class FWorldConditionContextDataRefDetails : public IPropertyTypeCustomization`  
_L17-42_
- inherits: `IPropertyTypeCustomization`
- L21 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L25 _private prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;` — IPropertyTypeCustomization interface
- L26 _private prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> StructPropertyHandle, IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L28 _private prototype_ `void CacheContextData();`
- L29 _private prototype_ `TSharedRef<SWidget> OnGetContent() const;`
- L30 _private prototype_ `FText GetCurrentDesc() const;`
- L32 _private prototype_ `void OnSetContextData(const FName ContextDataName) const;`
- L33 _private prototype_ `FWorldConditionContextDataRef* GetCommonContextDataRef() const;`
- L35 _private member_ `TArray<FName> CachedContextData;`
- L37 _private member_ `const UWorldConditionSchema* Schema = nullptr;`
- L38 _private member_ `TArray<const UStruct*> BaseStructs;`
- L40 _private member_ `IPropertyUtilities* PropUtils = nullptr;`
- L41 _private member_ `TSharedPtr<IPropertyHandle> StructProperty;`

### `Plugins/Runtime/WorldConditions/Source/WorldConditionsEditor/Private/Customizations/WorldConditionEditableDetails.h` (Private)


#### class `FWorldConditionEditableDetails`  
`class FWorldConditionEditableDetails : public IPropertyTypeCustomization`  
_L21-81_
- inherits: `IPropertyTypeCustomization`
- desc: Type customization for FWorldConditionEditable.
- L25 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L29 _private prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;` — IPropertyTypeCustomization interface
- L30 _private prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> StructPropertyHandle, IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L32 _private prototype_ `void CacheSchema();`
- L34 _private prototype_ `bool ShouldResetToDefault(TSharedPtr<IPropertyHandle> PropertyHandle) const;`
- L35 _private prototype_ `void ResetToDefault(TSharedPtr<IPropertyHandle> PropertyHandle);`
- L37 _private prototype_ `EVisibility GetInvertVisibility() const;`
- L39 _private prototype_ `FOptionalSize GetIndentSize() const;`
- L40 _private prototype_ `TSharedRef<SWidget> OnGetIndentContent() const;`
- L42 _private prototype_ `int32 GetExpressionDepth() const;`
- L43 _private prototype_ `void SetExpressionDepth(const int32 Depth) const;`
- L44 _private prototype_ `bool IsExpressionDepth(const int32 Depth) const;`
- L46 _private prototype_ `FText GetOperatorText() const;`
- L47 _private prototype_ `FSlateColor GetOperatorColor() const;`
- L48 _private prototype_ `TSharedRef<SWidget> OnGetOperatorContent() const;`
- L49 _private prototype_ `bool IsOperatorEnabled() const;`
- L51 _private prototype_ `void SetOperator(const EWorldConditionOperator Operator) const;`
- L52 _private prototype_ `bool IsOperator(const EWorldConditionOperator Operator) const;`
- L54 _private prototype_ `bool IsFirstItem() const;`
- L55 _private prototype_ `int32 GetCurrExpressionDepth() const;`
- L56 _private prototype_ `int32 GetNextExpressionDepth() const;`
- L58 _private prototype_ `FText GetOpenParens() const;`
- L59 _private prototype_ `FText GetCloseParens() const;`
- L61 _private prototype_ `FText GetDisplayValueString() const;`
- L63 _private prototype_ `TSharedRef<SWidget> GeneratePicker();`
- L64 _private prototype_ `void OnStructPicked(const UScriptStruct* InStruct) const;`
- L66 _private prototype_ `void OnCopyCondition() const;`
- L67 _private prototype_ `bool CanPasteCondition() const;`
- L68 _private prototype_ `void OnPasteCondition() const;`
- L70 _private prototype_ `const FWorldConditionEditable* GetCommonCondition() const;`
- L72 _private member_ `const UWorldConditionSchema* Schema = nullptr;`
- L74 _private member_ `TSharedPtr<class SComboButton> ComboButton;`
- L75 _private member_ `TSharedPtr<IPropertyHandle> StructProperty;`
- L76 _private member_ `TSharedPtr<IPropertyHandle> ConditionProperty;`
- L77 _private member_ `TSharedPtr<IPropertyHandle> ExpressionDepthProperty;`
- L78 _private member_ `TSharedPtr<IPropertyHandle> OperatorProperty;`
- L79 _private member_ `TSharedPtr<IPropertyHandle> InvertProperty;`
- L80 _private member_ `IPropertyUtilities* PropUtils = nullptr;`

### `Plugins/Runtime/WorldConditions/Source/WorldConditionsEditor/Private/Customizations/WorldConditionQueryDefinitionDetails.h` (Private)


#### class `FWorldConditionQueryDefinitionDetails`  
`class FWorldConditionQueryDefinitionDetails : public IPropertyTypeCustomization`  
_L14-30_
- inherits: `IPropertyTypeCustomization`
- desc: Type customization for FWorldConditionQueryDefinition.
- L18 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L22 _private prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;` — IPropertyTypeCustomization interface
- L23 _private prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> StructPropertyHandle, IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L25 _private prototype_ `void InitializeDefinition() const;`
- L27 _private member_ `IPropertyUtilities* PropUtils = nullptr;`
- L28 _private member_ `TSharedPtr<IPropertyHandle> StructProperty;`
- L29 _private member_ `TSharedPtr<IPropertyHandle> EditableConditionsProperty;`

### `Plugins/Runtime/WorldConditions/Source/WorldConditionsEditor/Private/WorldConditionEditorStyle.h` (Private)


#### class `FWorldConditionEditorStyle`  
`class FWorldConditionEditorStyle final : public FSlateStyleSet`  
_L7-20_
- inherits: `FSlateStyleSet`
- L12 _public prototype_ `static FWorldConditionEditorStyle& Get();`
- L13 _public prototype_ `static void Shutdown();`
- L15 _public member_ `static FColor TypeColor;`
- L17 _private prototype_ `FWorldConditionEditorStyle();`
- L19 _private member_ `static TUniquePtr<FWorldConditionEditorStyle> Instance;`

### `Plugins/Runtime/WorldConditions/Source/WorldConditionsEditor/Public/WorldConditionsEditorModule.h` (Public)


#### class `IWorldConditionsEditorModule`  
`class IWorldConditionsEditorModule : public IModuleInterface`  
_L10-35_
- inherits: `IModuleInterface`
- desc: The public interface to this module
- L21 _public function_ `static inline IWorldConditionsEditorModule& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L31 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use
