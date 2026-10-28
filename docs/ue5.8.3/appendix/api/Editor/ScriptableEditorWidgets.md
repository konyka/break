# Editor / ScriptableEditorWidgets

- module root: `Source/Editor/ScriptableEditorWidgets`
- headers: 5; symbols: 70
- symbol kinds: class=4, delegate=1, function=2, macro=3, member=29, prototype=30, struct=1
- PrivateDependencyModuleNames: Core, Engine, Slate, SlateCore
- PublicDependencyModuleNames: CoreUObject, UMG

### `Source/Editor/ScriptableEditorWidgets/Private/Components/PropertyViewHelper.h` (Private)


#### struct `FPropertyViewHelper`  
`struct FPropertyViewHelper`  
_L7-17_
- L9 _public member_ `static const FText UndefinedObjectText;`
- L10 _public member_ `static const FText UnloadedObjectText;`
- L11 _public member_ `static const FText UnknownErrorText;`
- L12 _public member_ `static const FText EditorOnlyText;`
- L13 _public member_ `static const FText UndefinedPropertyText;`
- L14 _public member_ `static const FText UnknownPropertyText;`
- L15 _public member_ `static const FText InvalidPropertyText;`
- L16 _public member_ `static const FText UnsupportedPropertyText;`

### `Source/Editor/ScriptableEditorWidgets/Public/Components/DetailsView.h` (Public)


#### class `UDetailsView`  
`class UDetailsView : public UPropertyViewBase, public FNotifyHook`  
_L28-108_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UPropertyViewBase,FNotifyHook`
- desc: The details view allows you to display the value of an object properties.
- L35 _public member_ `bool bAllowFiltering = false;` — `UPROPERTY(EditAnywhere, Category = "View")` — True if we allow filtering through search and the filter dropdown menu.
- L39 _public member_ `bool bAllowFavoriteSystem = false;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Category = "View")` — If false, the current properties editor will never display the favorite system
- L43 _public member_ `bool bShowModifiedPropertiesOption = false;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Category = "View", meta = (EditCondition = "bAllowFiltering"))` — True if you want to show the 'Show Only Modified Properties'. Only valid in conjunction with bAllowFiltering
- L47 _public member_ `bool bShowKeyablePropertiesOption = true;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Category = "View", meta = (EditCondition = "bAllowFiltering"))` — True if you want to show the 'Show Only Keyable Properties'. Only valid in conjunction with bAllowFiltering
- L51 _public member_ `bool bShowAnimatedPropertiesOption = true;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Category = "View", meta = (EditCondition = "bAllowFiltering"))` — True if you want to show the 'Show Only Animated Properties'. Only valid in conjunction with bAllowFiltering
- L55 _public member_ `float ColumnWidth = 0.65f;` — `UPROPERTY(EditAnywhere, Category = "View", meta=(ClampMin="0.0", ClampMax="1.0"))` — The default column width
- L59 _public member_ `bool bShowScrollBar = true;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Category = "View")` — If false, the details panel's scrollbar will always be hidden. Useful when embedding details panels in widgets that either grow to accommodate them, or with scrollbars of their own.
- L63 _public member_ `bool bForceHiddenPropertyVisibility = false;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Category = "View")` — If true, all properties will be visible, not just those with CPF_Edit
- L67 _public member_ `FName ViewIdentifier = NAME_None;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Category = "View")` — Identifier for this details view; NAME_None if this view is anonymous
- L71 _public member_ `TArray<FName> CategoriesToShow;` — `UPROPERTY(EditAnywhere, Category = "View")` — Which categories to show in the details panel. If both this and the Properties To Show lists are empty, all properties will show.
- L75 _public member_ `TArray<FName> PropertiesToShow;` — `UPROPERTY(EditAnywhere, Category = "View")` — Which properties to show in the details panel. If both this and the Categories To Show lists are empty, all properties will show.
- L79 _protected prototype_ `virtual void BuildContentWidget() override;`
- L80 _protected prototype_ `virtual void OnObjectChanged() override;`
- L85 _public prototype_ `virtual void ReleaseSlateResources(bool bReleaseChildren) override;`
- L89 _public prototype_ `virtual void NotifyPostChange(const FPropertyChangedEvent& PropertyChangedEvent, FProperty* PropertyThatChanged) override;`
- L93 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L97 _protected prototype_ `void ToggleShowingOnlyAllowedProperties();`
- L98 _protected prototype_ `virtual bool IsRowVisibilityFiltered() const;`
- L99 _protected prototype_ `virtual bool GetIsPropertyVisible(const FPropertyAndParent& PropertyAndParent) const;`
- L100 _protected prototype_ `virtual bool GetIsRowVisible(FName InRowName, FName InParentName) const;`
- L103 _private member_ `TSharedPtr<IDetailsView> DetailViewWidget;`
- L107 _private member_ `bool bShowOnlyAllowed = true;` — `UPROPERTY()` — Showing properties in this details panel works by allowing only specific categories and properties. This flag enables you to show all properties without needing to specify.

#### Free symbols / members of external scopes

- L16 _macro_ `#define UE_API SCRIPTABLEEDITORWIDGETS_API`

### `Source/Editor/ScriptableEditorWidgets/Public/Components/PropertyViewBase.h` (Public)


#### class `UPropertyViewBase`  
`class UPropertyViewBase : public UWidget`  
_L24-75_
- reflection: `UCLASS(MinimalAPI, Abstract)`
- inherits: `UWidget`
- desc: Base of property view allows you to display the value of an object properties.
- L31 _protected member_ `TSoftObjectPtr<UObject> Object;` — `UPROPERTY(meta = (DisplayName="Object"))` — The object to view.
- L34 _protected member_ `FSoftObjectPath SoftObjectPath_DEPRECATED;` — `UPROPERTY()`
- L38 _protected member_ `bool bAutoLoadAsset = true;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Category = "View")` — Load the object (if it's an asset) when the widget is created.
- L42 _protected member_ `FOnPropertyValueChanged OnPropertyChanged;` — `UPROPERTY(BlueprintAssignable, Category = "View|Event")` — Sets a delegate called when the property value changes
- L47 _public prototype_ `UObject* GetObject() const;` — `UFUNCTION(BlueprintCallable, Category = "View")`
- L50 _public prototype_ `void SetObject(UObject* NewObject);` — `UFUNCTION(BlueprintCallable, Category = "View")`
- L53 _protected prototype_ `virtual void BuildContentWidget() PURE_VIRTUAL(UPropertyViewBase::BuildContentWidget, );`
- L54 _protected function_ `virtual void OnObjectChanged()`
- L55 _protected function_ `TSharedPtr<SBorder> GetDisplayWidget() const`
- L56 _protected prototype_ `void OnPropertyChangedBroadcast(FName PropertyName);`
- L60 _public prototype_ `virtual void ReleaseSlateResources(bool bReleaseChildren) override;`
- L61 _public prototype_ `virtual const FText GetPaletteCategory() override;`
- L64 _protected prototype_ `virtual TSharedRef<SWidget> RebuildWidget() override;`
- L69 _public prototype_ `virtual void PostLoad() override;`
- L70 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L74 _private member_ `TSharedPtr<SBorder> DisplayedWidget;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API SCRIPTABLEEDITORWIDGETS_API`
- L17 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPropertyValueChanged, FName, PropertyName);` — Sets a delegate called when the property value changes
- L17 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPropertyValueChanged, FName, PropertyName);` — Sets a delegate called when the property value changes

### `Source/Editor/ScriptableEditorWidgets/Public/Components/SinglePropertyView.h` (Public)


#### class `USinglePropertyView`  
`class USinglePropertyView : public UPropertyViewBase`  
_L24-71_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UPropertyViewBase`
- desc: The single property view allows you to display the value of an object's property.
- L31 _private member_ `FName PropertyName;` — `UPROPERTY(EditAnywhere, Category = "View")` — The name of the property to display.
- L35 _private member_ `FText NameOverride;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Category = "View")` — Override for the property name that will be displayed instead of the property name.
- L39 _public prototype_ `FName GetPropertyName() const;` — `UFUNCTION(BlueprintCallable, Category = "View")`
- L42 _public prototype_ `void SetPropertyName(FName NewPropertyName);` — `UFUNCTION(BlueprintCallable, Category = "View")`
- L45 _public prototype_ `FText GetNameOverride() const;` — `UFUNCTION(BlueprintCallable, Category = "View")`
- L48 _public prototype_ `void SetNameOverride(FText NewPropertyName);` — `UFUNCTION(BlueprintCallable, Category = "View")`
- L51 _private prototype_ `void InternalSinglePropertyChanged();`
- L55 _protected prototype_ `virtual void BuildContentWidget() override;`
- L56 _protected prototype_ `virtual void OnObjectChanged() override;`
- L61 _public prototype_ `virtual void ReleaseSlateResources(bool bReleaseChildren) override;`
- L66 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L70 _private member_ `TSharedPtr<ISinglePropertyView> SinglePropertyViewWidget;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API SCRIPTABLEEDITORWIDGETS_API`

### `Source/Editor/ScriptableEditorWidgets/Public/ScriptableEditorWidgetsModule.h` (Public)


#### class `FScriptableEditorWidgetsModule`  
`class FScriptableEditorWidgetsModule : public IModuleInterface`  
_L7-15_
- inherits: `IModuleInterface`
- L12 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface interface
- L13 _public prototype_ `virtual void ShutdownModule() override;`
